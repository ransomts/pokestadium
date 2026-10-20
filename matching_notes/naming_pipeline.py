#!/usr/bin/env python3
"""Multi-stage symbol naming pipeline for decompilation projects.

Architecture:
  1. gemma-4-12b drafts names for all symbols (fast, ~200 sym/min)
  2. gemma-4-31b revises only symbols that need it (~60 sym/min)
  3. Flags symbols for human review when game-specific knowledge is needed

Usage:
  python3 naming_pipeline.py --file src/fragments/battle_engine/foo.c [--out DIR]
  python3 naming_pipeline.py --symbols func_84306968 D_80075E40 [--out DIR]
  python3 naming_pipeline.py --queue matching_notes/rename_queue.txt [--out DIR]

Output: TSV file with old_name, new_name, justification, stage, confidence
"""
import argparse
import concurrent.futures
import json
import os
import re
import subprocess
import sys
import time
import urllib.request

GATEWAY = "https://llm.rcd.clemson.edu/v1/chat/completions"
TOKEN_FILE = os.path.expanduser("~/.config/rcd-llm/api-key")

DRAFT_MODEL = "gemma-4-12b"
REVISE_MODEL = "gemma-4-31b"

RULES = """# Symbol Naming Rules (michiiik/pokestadium CONTRIBUTING.md + conventions)

## FORMAT
- Function: Domain_VerbOrNoun (e.g., Battle_ApplyDamage)
- Global var (game-wide): gCamelCase (e.g., gPlayerHp)
- Static var (fragment-scoped): sCamelCase (e.g., sFrameCount)
- Struct: TitleCase (e.g., HallOfFameSlot)

## DOMAIN (pick from michiiik's most common, by frequency)
Battle(2019) | Particle(513) | Lab(506) | Gb(374) | Gallery(308)
Audio(209) | Trade(205) | Widget(178) | Rental(154) | Team(146)
Geo(112) | Mini(98) | Model(86) | Gfx(47) | Storage(34)

## VERB CONVENTIONS (michiiik's actual usage frequency)
- Draw (699) for rendering — NOT Render, Paint, Display
- Set (408) for setting values
- Update (373) for per-frame changes
- Init (329) for initialization — NOT Initialize (only 48)
- Get (252) for simple retrieval — NOT Fetch, Retrieve
- Load (249) for IO/complex retrieval
- Build (109) for constructing structures
- Reset (103) for restoring initial state
- Is (97) for boolean checks
- Handle (84) for input/commands
- Approach (58) for gradual/lamped changes — NOT Lerp, Interpolate
- Queue (54) for deferred operations
- Advance (54) for state progression
- Play (52) for audio/animation — NOT Start
- Show (49) for UI display — NOT Draw (Show is higher-level)

## NOUN CONVENTIONS
- Table (364) for lookup arrays — NOT Array, List
- State (206) for state machines
- Count (82) for quantities — NOT Size, Length, Num
- Flag (73) for boolean variables
- Alpha (73) for opacity — NOT FadeLevel
- Speed (86) for velocity — NOT Vel
- Rot in fields, Rotation in function names
- Pos in fields, Position in function names
- Callback (385) — NOT Handler (only 9 uses in entire codebase)

## BANNED
- yaw/pitch/roll (use rotationX/Y/Z)
- AI outside BattleAi (use COM)
- party for team (use brought/picked)
- VictoryPalace→HallOfFame | KidsClub→Minigames
- PokeCup→NintendoCup | PokemonLab→ProfessorOaksLab
- Custom, Variant, Type without differentiator
- Bare digits/letters at end (see rules below)
- Address fragments (_49628)
- Non-ASCII | British spellings
- Handler suffix (use Callback)
- Initialize (use Init)
- Render (use Draw)
- Fetch/Retrieve (use Get or Load)

## DIGIT RULES
Allowed digits (semantic):
- Bit widths: BE16, LE32
- Pixel formats: RGBA16, I4, IA8, CI4
- Audio channels: Square1, Square2, Pulse1, Pulse2
- Player indices: Player1, Player2
- Effect table indices: Effect47, Descriptor34
- Texture dimensions: 32x32, 64x64
- Vertex indices: Vtx0, Vertices1
- State phases: Phase0, Phase1, Step1, Level2

NOT allowed (non-semantic):
- Variant counters: Load2, Call2, Handler3
- Raw addresses: _5F92, _BC20
- If you can't say what the digit MEANS, skip

## METHOD
1. Read the code snippet
2. Identify 2+ facts about what it does
3. Name by BEHAVIOR (what it does) not by CALLER (who calls it)
4. Check verb: Draw/Init/Get/Set/Update (not Render/Initialize/Fetch)
5. Skip if <2 facts or body is empty

## OUTPUT
placeholder_name<TAB>new_name<TAB>justification

If you cannot name a symbol, output NOTHING for it.
"""

REVISE_RULES = """# Symbol Naming Review Rules (CONTRIBUTING.md compliant)

You are reviewing draft names from a fast model. Your job:

1. CHECK each name against ALL rules above
2. FIX violations: bare digits, address fragments, banned words,
   wrong casing, British spellings, non-ASCII
3. IMPROVE generic names (add domain and behavioral specificity)
4. VERIFY the justification cites actual code evidence
5. SKIP names you cannot verify (output nothing for that symbol)

Good revisions:
- "ProcessData" → "ProcessBattleTurn" (add domain)
- "UpdateState2" → "UpdateHPBar" (fix bare digit, say what)
- "Handler_49628" → "RegisterModelAnim" (remove address, add behavior)
- "fadeLevel" → "alpha" (prefer technically correct term)
- "PokemonLab" → "ProfessorOaksLab" (use area name convention)

Names that should be SKIPPED (left as placeholder):
- Function body is empty
- Code context is insufficient to determine behavior
- The name would require guessing at game mechanics you can't verify

Output: placeholder_name<TAB>new_name<TAB>justification
Only output rows for symbols you are confident about.
"""

# Game-specific knowledge flags (symbols that need human review)
GAME_SPECIFIC_PATTERNS = [
    r"Status.*Flag",       # Could be specific game mechanics
    r"Update.*Effect",     # Too generic for battle effects
    r"Register.*Handler",  # Might need dispatch table knowledge
    r"Init.*Data",         # Too generic for game data
    r"Kangaskhan|Nidoran|Jynx",  # Sensitive Pokemon terminology
    r"Fade.*Level",        # Should use "alpha" instead
]


def call_model(model, prompt, max_tokens=8192, timeout=300, temperature=0.1):
    token = open(TOKEN_FILE).read().strip()
    payload = {
        "model": model,
        "messages": [{"role": "user", "content": prompt}],
        "max_tokens": max_tokens,
        "temperature": temperature,
    }
    req = urllib.request.Request(GATEWAY,
        data=json.dumps(payload).encode(), method="POST",
        headers={"Authorization": f"Bearer {token}", "Content-Type": "application/json"})
    t0 = time.time()
    try:
        with urllib.request.urlopen(req, timeout=timeout) as r:
            result = json.load(r)
        elapsed = time.time() - t0
        content = result["choices"][0]["message"].get("content") or ""
        usage = result.get("usage", {})
        return content, elapsed, usage
    except Exception as e:
        return None, time.time() - t0, {"error": str(e)}


def find_placeholders_in_file(filepath):
    """Find all placeholder symbols in a source file."""
    text = open(filepath, errors="replace").read()
    placeholders = set()
    for m in re.finditer(r"\b(func_[0-9A-F]{8}|D_[0-9A-F]{8}|unk_func_\w+|unk_D_\w+)\b", text):
        placeholders.add(m.group(1))
    return sorted(placeholders)


def extract_symbol_context(symbol, source_text):
    """Extract code context around a symbol definition or usage."""
    # For functions
    pat = rf"(?:void|s32|u32|f32|s16|u16|u8|s8)\s+{re.escape(symbol)}\s*\("
    m = re.search(pat, source_text)
    if m:
        start = max(0, m.start() - 2)
        brace = source_text.find("{", m.start())
        if brace >= 0:
            depth, end = 0, brace
            while end < len(source_text) and end < brace + 600:
                if source_text[end] == "{":
                    depth += 1
                elif source_text[end] == "}":
                    depth -= 1
                    if depth == 0:
                        break
                end += 1
            end = min(end + 2, start + 800)
        else:
            end = start + 400
        lines = source_text[start:end].split("\n")[:18]
        return "```c\n" + "\n".join(lines) + "\n```"

    # For data
    idx = source_text.find(symbol)
    if idx >= 0:
        start = max(0, idx - 100)
        end = min(len(source_text), idx + 400)
        lines = source_text[start:end].split("\n")[:10]
        return "```c\n" + "\n".join(lines) + "\n```"

    return None


def parse_proposals(content):
    """Parse tab-separated proposals from model output."""
    proposals = {}
    for line in content.split("\n"):
        line = line.strip()
        if not line or line.startswith("#") or line.startswith("//"):
            continue
        parts = line.split("\t")
        if len(parts) >= 2:
            old, new = parts[0].strip(), parts[1].strip()
            if re.match(r"^(func_|D_|unk_)", old) and not re.match(r"^(func_|D_|unk_)", new):
                just = parts[2].strip() if len(parts) > 2 else ""
                proposals[old] = (new, just)
    return proposals


# Semantic digit suffix patterns (allowed)
SEMANTIC_DIGIT = re.compile(
    r"(?:BE|LE)[0-9]+$"                    # ReadBE16, WriteLE32 (bit widths)
    r"|RGBA[0-9]+$|IA[0-9]+$|CI[0-9]+$"    # RGBA16, IA8, CI4 (N64 pixel formats)
    r"|[0-9]+x[0-9]+$"                      # 32x32, 64x64 (dimensions)
    r"|(?:Square|Pulse|Noise|Wave)[0-9]$"   # GBA audio channels
    r"|(?:Player|Controller)[0-9]$"          # Player indices
    r"|(?:Effect|Start|End|Palette|Texture|Descriptor|Model)"
    r"[_]?[0-9A-F]{1,4}$"                   # Effect table indices (with optional _)
    r"|(?:Channel|Track|Voice|Bank|Archive)[0-9]$"  # Audio
    r"|(?:Version|Rev|Phase|Stage|Step|Level|Mode)[0-9]$"  # States
    r"|(?:Slot|Bank)[0-9]$"                 # Hardware slots
    r"|Log[0-9]$"                           # Log2, Log10 (math)
    r"|(?:Vtx|Vertices|PanelVtx|GfxVtx)[0-9]$"       # Vertex array indices
    r"|(?:Root|Node|Entry|Page|Frame|Layer)[0-9]$"   # Indexed entities
    r"|(?:Icon|Sprite|Tile)[0-9]$"                     # Indexed graphics
    r"|(?:Timer|Counter|Index|Buffer|Pool|List|Queue)[0-9]$"  # Data structures
    r"|(?:Address|Pointer|Handle|Flag|Bit|Mask)[0-9]$"  # Hardware
    r"|(?:Byte|Word|Long|Short)[0-9]$"                  # Data widths
    r"|(?:Object|Widget|Window)[0-9]$"                  # UI entities
    r"|NoopStub[0-9]$"                      # michiiik's convention for identical dead stubs (ParticleGfx_NoopStub1/2/10)
    r"|[0-9]x[0-9]$"                                   # 4x4, 8x8 (small dimensions)
    r"|^I[0-9]$"                                        # I4, I8 (pixel format)
)

# Known hex-fragment prefixes (allowed when followed by hex index)
HEX_PREFIX = re.compile(
    r"(?:Palette|Texture|Descriptor|Effect|Model)[_]?[0-9A-F]+$"
)

# Compound suffixes that end in A/B/C (NOT bare letters)
COMPOUND_SUFFIX = re.compile(
    r"(?:RGB|RGBA|DMA|RTC|BEA|LEA|LEA|DMA)$"
    r"|[Rr][Gg][Bb]$"                                    # RGB
    r"|[Dd][Mm][Aa]$"                                     # DMA
    r"|[Rr][Tt][Cc]$"                                     # RTC
)


def needs_revision(name):
    """Check if a draft name needs revision by the 31b model."""
    # Hex fragments: check FIRST (before digit check, since hex ends in digits)
    if re.search(r"_[0-9A-F]{4,}", name):
        if not HEX_PREFIX.search(name):
            return True  # raw address, not a prefixed table index
    # Bare digits at end — check against semantic patterns
    if re.search(r"[0-9]$", name):
        if not SEMANTIC_DIGIT.search(name):
            return True  # non-semantic digit
    # Bare letters at end (A/B/C without differentiator)
    # Skip compound suffixes (DMA, RGB, RTC) and pixel formats
    if re.search(r"[A-C]$", name) and not COMPOUND_SUFFIX.search(name):
        if not re.search(r"(?:Color|Config|Variant|Setup)[A-C]$", name):
            if not re.search(r"(?:Seed|Rng)[ABC]$", name):  # RNG variants are semantic
                return True
    # Banned terminology — check for yaw/pitch/roll ANYWHERE
    if re.search(r"yaw|pitch|roll", name, re.I) and not re.search(r"Rollout|Rolling", name, re.I):
        return True
    if re.search(r"Custom$|Variant$|Type$", name):
        return True
    if re.search(r"VictoryPalace|KidsClub|PokeCup|PokemonLab", name):
        return True
    # Non-ASCII
    if re.search(r"[^\x00-\x7F]", name):
        return True
    # British spellings
    if re.search(r"colour|centre|behaviour|favour|honour", name, re.I):
        return True
    # Too generic
    if re.match(r"^(Process|Update|Handle|Register|Init|Set|Get)\w*$", name):
        return True
    # Too long — calibrated to michiiik's practice (p99=72, max=94; their
    # multi-effect callback chains are deliberately long). Hard fail above
    # their demonstrated maximum; the multi-effect And-chains are sanctioned.
    if len(name) > 94:
        return True
    return False


def needs_human_review(name, justification):
    """Check if a symbol likely needs game-specific knowledge."""
    for pat in GAME_SPECIFIC_PATTERNS:
        if re.search(pat, name, re.I):
            return True
    # Very short justifications suggest the model wasn't confident
    if len(justification) < 30:
        return True
    # Check for style preference violations (should have been fixed by revise stage)
    if re.search(r"fadeLevel|fade_level", name, re.I):
        return True
    # Check casing: functions should be Domain_PascalCase
    if re.match(r"^[a-z]", name) and not re.match(r"^[gs][A-Z]", name):
        return True
    return False


def draft_stage(symbols, contexts, batch_size=10):
    """Stage 1: fast draft with gemma-4-12b."""
    proposals = {}
    total_time = 0

    for i in range(0, len(symbols), batch_size):
        batch = symbols[i:i + batch_size]
        ctx_block = "\n\n".join(
            f"### {sym}\n{contexts.get(sym, '(code not found)')}" for sym in batch
        )
        prompt = f"""{RULES}

## TASK: Name these {len(batch)} symbols

{ctx_block}

Output: placeholder_name<TAB>new_name<TAB>justification
Skip symbols you cannot name (output nothing).
"""
        content, elapsed, _ = call_model(DRAFT_MODEL, prompt, max_tokens=4096)
        total_time += elapsed
        if content:
            proposals.update(parse_proposals(content))

    return proposals, total_time


def revise_stage(proposals, contexts, batch_size=10):
    """Stage 2: revise only symbols that need it, with gemma-4-31b."""
    # Filter to symbols that need revision
    to_revise = {ph: val for ph, val in proposals.items() if needs_revision(val[0])}

    if not to_revise:
        return proposals, 0

    revised = dict(proposals)  # Start with all proposals
    total_time = 0

    symbols_to_revise = list(to_revise.keys())
    for i in range(0, len(symbols_to_revise), batch_size):
        batch = symbols_to_revise[i:i + batch_size]

        # Build context + current proposals
        ctx_block = "\n\n".join(
            f"### {ph}\n{contexts.get(ph, '(code not found)')}" for ph in batch
        )
        prev_block = "\n".join(
            f"{ph}\t{proposals[ph][0]}\t{proposals[ph][1]}" for ph in batch if ph in proposals
        )

        prompt = f"""{REVISE_RULES}

## CODE CONTEXT

{ctx_block}

## DRAFT PROPOSALS TO REVIEW

{prev_block}

## TASK

For each draft proposal above, either:
- KEEP it if it's good (output the same name)
- IMPROVE it if it violates a rule or is too generic
- SKIP it if you cannot verify (output nothing)

Output: placeholder_name<TAB>new_name<TAB>justification
"""
        content, elapsed, _ = call_model(REVISE_MODEL, prompt, max_tokens=4096)
        total_time += elapsed
        if content:
            new_proposals = parse_proposals(content)
            for ph, val in new_proposals.items():
                revised[ph] = val

    return revised, total_time


def classify_proposals(proposals):
    """Classify proposals into: high-confidence, needs-review, skipped."""
    high = {}
    review = {}
    for ph, (new, just) in proposals.items():
        if needs_human_review(new, just):
            review[ph] = (new, just, "REVIEW")
        else:
            high[ph] = (new, just, "OK")
    return high, review


def main():
    ap = argparse.ArgumentParser(description="Multi-stage symbol naming pipeline")
    ap.add_argument("--file", help="Source file to scan for placeholders")
    ap.add_argument("--symbols", nargs="+", help="Specific symbols to name")
    ap.add_argument("--out", default="scratch/naming_pipeline", help="Output directory")
    ap.add_argument("--batch-size", type=int, default=10)
    ap.add_argument("--skip-revise", action="store_true", help="Skip stage 2 (revision)")
    ap.add_argument("--dry-run", action="store_true", help="Show plan without calling models")
    args = ap.parse_args()

    os.makedirs(args.out, exist_ok=True)

    # Gather symbols
    if args.file:
        source_text = open(args.file, errors="replace").read()
        symbols = find_placeholders_in_file(args.file)
        contexts = {sym: extract_symbol_context(sym, source_text) for sym in symbols}
    elif args.symbols:
        symbols = args.symbols
        # Try to find context in battle_engine files
        contexts = {}
        for sym in symbols:
            ctx = None
            for root, dirs, files in os.walk("src/fragments/battle_engine"):
                for fn in files:
                    if fn.endswith(".c"):
                        text = open(os.path.join(root, fn), errors="replace").read()
                        ctx = extract_symbol_context(sym, text)
                        if ctx:
                            break
                if ctx:
                    break
            contexts[sym] = ctx or "(code not found)"
    else:
        print("Specify --file or --symbols")
        sys.exit(1)

    if not symbols:
        print("No placeholder symbols found")
        sys.exit(0)

    print(f"Symbols to name: {len(symbols)}")
    found_ctx = sum(1 for c in contexts.values() if c and c != "(code not found)")
    print(f"  with code context: {found_ctx}")
    print(f"  without context: {len(symbols) - found_ctx}")

    if args.dry_run:
        for sym in symbols:
            print(f"  {sym}: {contexts[sym][:60]}...")
        sys.exit(0)

    # Stage 1: Draft
    print(f"\n{'='*60}")
    print(f"STAGE 1: DRAFT ({DRAFT_MODEL})")
    print(f"{'='*60}")
    draft_proposals, draft_time = draft_stage(symbols, contexts, args.batch_size)
    draft_count = len(draft_proposals)
    print(f"  proposed: {draft_count}/{len(symbols)}")
    print(f"  time: {draft_time:.1f}s")
    print(f"  throughput: {draft_count / draft_time * 60:.1f} sym/min")

    if not draft_proposals:
        print("No proposals from draft stage. Exiting.")
        sys.exit(0)

    # Show which need revision
    needs_rev = {ph: val for ph, val in draft_proposals.items() if needs_revision(val[0])}
    print(f"  need revision: {len(needs_rev)}")

    # Stage 2: Revise (optional)
    if not args.skip_revise and needs_rev:
        print(f"\n{'='*60}")
        print(f"STAGE 2: REVISE ({REVISE_MODEL})")
        print(f"{'='*60}")
        final_proposals, revise_time = revise_stage(draft_proposals, contexts, args.batch_size)
        print(f"  revised: {len(final_proposals)}/{len(symbols)}")
        print(f"  time: {revise_time:.1f}s")
    else:
        final_proposals = draft_proposals
        revise_time = 0
        if args.skip_revise:
            print("\n  (skipping revision stage)")

    # Classify
    high_conf, needs_review = classify_proposals(final_proposals)
    print(f"\n{'='*60}")
    print(f"RESULTS")
    print(f"{'='*60}")
    print(f"  high confidence: {len(high_conf)}")
    print(f"  needs human review: {len(needs_review)}")
    print(f"  total pipeline time: {draft_time + revise_time:.1f}s")

    # Write output TSV
    tsv_path = os.path.join(args.out, "proposals.tsv")
    with open(tsv_path, "w") as f:
        f.write("old_name\tnew_name\tjustification\tstage\tconfidence\n")
        for ph, (new, just, status) in sorted(high_conf.items()):
            f.write(f"{ph}\t{new}\t{just}\tdraft+revise\tHIGH\n")
        for ph, (new, just, status) in sorted(needs_review.items()):
            f.write(f"{ph}\t{new}\t{just}\tdraft+revise\tREVIEW\n")

    print(f"\n  Output: {tsv_path}")

    # Show samples
    print(f"\n  Sample high-confidence proposals:")
    for ph, (new, just, _) in sorted(high_conf.items())[:5]:
        print(f"    {ph[:18]} → {new[:35]}")
        print(f"      {just[:70]}")

    print(f"\n  Sample review-needed proposals:")
    for ph, (new, just, _) in sorted(needs_review.items())[:5]:
        print(f"    {ph[:18]} → {new[:35]}")
        print(f"      {just[:70]}")


if __name__ == "__main__":
    main()
