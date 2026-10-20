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

RULES = """# Symbol Naming Rules (michiiik/pokestadium CONTRIBUTING.md compliant)

## FORMAT
- Function: Domain_VerbOrNoun (e.g., Battle_ApplyDamage)
- Global var (game-wide): gCamelCase (e.g., gPlayerHp)
- Static var (fragment-scoped): sCamelCase (e.g., sFrameCount)
- Struct: TitleCase (e.g., HallOfFameSlot)
- Local var: snake_case (e.g., cpu_pokemon)
- Function names up to 50 characters tolerated

## DOMAINS (non-exhaustive, look at callers for more)
Battle (logic/damage/turns) | BattleScene (setup/camera/render)
BattleAnim (particle effects) | BattleHud (HP bars/status UI)
BattleAi (AI procedures, note this exact casing)
Particle (particle internals) | Gfx (GPU commands/display lists)
Audio (sound/music) | Pokemon (per-Pokemon state/stats)
Move (move behavior) | Storage (save/load/memory)
RentalHub (rental system) | Trade (trade system)
Gym (gym leader castle) | Gallery (photo gallery)
Lab (Pokemon Lab) | Title (title screen)

## BANNED WORDS AND REPLACEMENTS
- yaw/pitch/roll → rotationY/rotationX/rotationZ (world-relative)
- AI (outside BattleAi domain) → COM
- party (for team) → brought (party of 6) or picked (battle 3)
- VictoryPalace → HallOfFame
- KidsClub → Minigames
- PokeCup → NintendoCup
- PokemonLab → ProfessorOaksLab
- Custom, Variant, Type (without specific differentiator after)
- colour, centre, behaviour, favour (British spellings)
- Any non-ASCII character (including é, ♂, etc.)

## STYLE PREFERENCES
- Prefer technically correct obscure language over ambiguous common
  (e.g., alpha NOT fadeLevel, descriptor NOT thing)
- Use English names for Pokemon and Characters
- Use "Kangaskid" for the creature in Kangaskhan's pouch
- Use "original color" / "purple color" for Jynx (never "blackface")
- Numbers in names must be semantic (palette index, effect ID, table index)
- NEVER end with a bare digit or letter without meaning
- NEVER include raw address fragments (_49628)
- American English spelling

## SENSITIVE LANGUAGE
- Never use "blackface" or "purpleface" → "original color" / "purple color"
- For Nidoqueen documentation: use "breasts" (clinical term, not slang)
- These rules apply to identifiers AND justifications

## METHOD
1. Read the code snippet
2. Identify 2+ facts about what it does
3. Name by BEHAVIOR (what it does) not by CALLER (who calls it)
4. Skip if <2 facts or function body is empty ({ } or return;)

## OUTPUT
placeholder_name<TAB>new_name<TAB>justification (cite evidence)

If you cannot name a symbol, output NOTHING for it.
Skipping is correct — a parked placeholder is better than a wrong name.
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


def needs_revision(name):
    """Check if a draft name needs revision by the 31b model."""
    # Bare digits at end (not semantic table/palette indices)
    if re.search(r"[0-9]$", name) and not re.search(r"(Effect|Start|End|Palette|Texture|Descriptor|Model)[0-9A-F]", name):
        return True
    # Bare letters at end
    if re.search(r"[A-C]$", name) and not re.search(r"(Color|Config|Variant|Setup)[A-C]$", name):
        return True
    # Address fragments
    if re.search(r"_[0-9A-F]{4,}", name):
        return True
    # Banned terminology — check for yaw/pitch/roll ANYWHERE (not just standalone)
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
    # Over 50 chars
    if len(name) > 55:
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
