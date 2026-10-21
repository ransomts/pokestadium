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
    r"|[1-9][0-9]*x[1-9][0-9]*$"                      # 32x32, 64x64 (dimensions)
    r"|(?:Square|Pulse|Noise|Wave)[0-9]$"   # GBA audio channels
    r"|(?:Player|Controller)[0-9]$"          # Player indices
    r"|(?:Effect|Start|End|Palette|Texture|Descriptor|Model)"
    r"[_]?[0-9A-F]{1,4}$"                   # Effect table indices (with optional _)
    r"|(?:Channel|Track|Voice|Bank|Archive)[0-9]$"  # Audio
    r"|(?:Version|Rev|Phase|Stage|Step|Level|Mode)[0-9]$"  # States
    r"|(?:Slot|Bank)[0-9]$"                 # Hardware slots
    r"|Log[0-9]$"                           # Log2, Log10 (math)
    r"|(?:Vtx|Vertices|PanelVtx|GfxVtx)[0-9]+$"     # vertex array indices incl. multi-digit (Vtx10)
    r"|WaveTable[0-9]$"                                 # GB wave channel tables (gGbWaveTable0)
    r"|(?:Root|Node|Entry|Page|Frame|Layer)[0-9]$"   # Indexed entities
    r"|(?:Icon|Sprite|Tile)[0-9]$"                     # Indexed graphics
    r"|(?:Timer|Counter|Index|Buffer|Pool|List|Queue)[0-9]$"  # Data structures
    r"|(?:Address|Pointer|Handle|Flag|Bit|Mask)[0-9]$"  # Hardware
    r"|(?:Byte|Word|Long|Short)[0-9]$"                  # Data widths
    r"|(?:Object|Widget|Window)[0-9]$"                  # UI entities
    r"|NoopStub[0-9]$"                      # michiiik's convention for identical dead stubs (ParticleGfx_NoopStub1/2/10)
    r"|NoopString[0-9]+$"                    # dead empty-string literals, NoopStubN analogue (gParticleNoopString1-3)
    r"|DL(?:8|16|32)$"                                    # G_IM_SIZ texture bit depths (gMinigameTileSetupDL16)
    r"|Type[0-9]+$"                                         # dispatch type indices (michiiik's GeoNode_CreateType3)
    r"|(?:_T|_InvT)[0-9]$"                             # spline exponents (T3 = t^3, InvT2 = (1-t)^2)
    r"|(?:Small|Large)_[0-9]+$"                       # paired texture indices (MoveTargetSmall_0-3)
    r"|GbGamePak_[0-9]+$"                              # GB game-category indices from GbSave_GameToCategoryIndex
    r"|Node[0-9]+$"                                        # multi-digit indexed entities (gChainLinkNode10)
    r"|N64$"                                                    # console name (gText_LeavingN64)
    r"|CreditsString[0-9]+$"                            # credits decompress-table string indices (bank 0x2D)
    r"|Vec[XYZ][0-9]+$"                                  # vector component literal magnitudes (gVecY10)
    r"|[1-9][0-9]*x[1-9][0-9]*$"                          # 4x4, 8x8 (dimensions; no leading 0 — blocks 0xNNN hex ids)
    r"|^I[0-9]$"                                        # I4, I8 (pixel format)
    r"|NoopStub[0-9]+$"                                # multi-digit dead stubs (NoopStub10)
    r"|[SU](?:8|16|32|64)$"                          # scalar widths: ApproachS8, BounceS16 (power-of-two, no underscore)
    r"|(?:Rgba|Ia|Ci)[0-9]+$"                          # pixel formats, mixed-case suffix (LoadTextureRgba32/Ia4/Ci8)
    r"|(?<!_)I[0-9]+$"                                 # I4/I8 as suffix (LoadTextureI4, DualRgba16I8)
    r"|Texture(?:Multi)?Block[0-9]+$"                   # texel-size texture loads (LoadTextureBlock32)
    r"|Moves[0-9]+To[0-9]+$"                            # ID-range endpoints (AnnouncerMoveDataMoves1To68)
    r"|Sub[0-9]+$"                                       # substate handlers (StatusIdleCase2Sub0, switch on animationSubstate)
    r"|State[0-9]+$"                                    # state IDs, multi-digit (CleanupAndEnterState18)
    r"|Row[0-9]+$|Seq[0-9]+$"                           # gMoveAnimData row/sequence IDs
    r"|Team[0-9]$|Framing[0-9]$|Anchor[0-9]$"           # side/camera indices
    r"|Timing[0-9]+$"                                    # camera-timing codes (gCameraShotPoolTiming20)
    r"|Patch[0-9]+$"                                     # vertex-limit split chunks (VtxSandPatch1..7)
    r"|Scheme[0-9]+$"                                    # color-scheme table indices
    r"|Variant[0-9]+$"                                  # variant/category IDs (CreateVariant47)
    r"|Radial[0-9]+$"                                   # radial burst param (cites existing StartEffect33Radial20)
    r"|Step[0-9]+Or[0-9]+$"                             # intro shot pairs (IntroCameraStep4Or5)
    r"|LoadGfx[0-9A-F]{1,4}(?:_[0-9A-F]{1,4})?(?:_Alt[0-9])?$"  # gfx file IDs (script resource lists)
    r"|Field[0-9A-F]{2}$|Offset[0-9A-F]{2}$"           # unresolved struct-field offsets (FieldB0, OffsetAC)
    r"|Case[0-9]+$"                                       # switch-dispatched handlers (StatusIdleCase2, key = animationMode)
    r"|(?:Title|Subtitle)_[0-9]+$"                         # mode strings keyed by switch ID (gBattleModeTitle_7)
    r"|(?:Camera|Fb|Graph)[0-9]$"                          # portrait buffers by player side (gBattlePortraitFb0)
    r"|Fragment[0-9]+$"                                  # fragment IDs (Fragment76_CallFragment67)
    r"|(?:ObjDef|TileAttr|TileMisc|GfxDL)[0-9]$"          # diorama/lab tile sets (gFragment17TileAttr0, gFragment22GfxDL2)
    r"|Trail[0-9]+$"                                      # michiiik's Trail40 water-trail family citations
    r"|EffectType$"                                       # effectType struct field setters (Particle_SetEffectType)
    r"|Motion[0-9]+$"                                   # motion switch-case indices (ConfigMotion6 = scale 1.5 case)
    r"|Round[0-9]+$"                                       # round numbers (NintendoCupRound2 = R2, battle rounds)
    r"|ByVariant$"                                        # tables indexed by variant (gCatASoundPitchOffsetByVariant)
    r"|RGB[0-9]+$"                                        # RGB5551, RGB8 pixel formats
    r"|F(?:32|64)$"                                        # float widths (Math_AbsF32)
    r"|Palette[0-9A-F]{1,2}$"                            # palette IDs (Descriptor34Palette17)
    r"|Sequence[0-9]+$"                                  # sequence IDs (PlaySpeciesSequence33)
    r"|Categor(?:y|ies)[0-9]+$"                           # particle category values (RetainingCategories47)
    r"|And[0-9]+$"                                        # compound indices (BadgeTextures2And3, Sequences14And21)
    r"|Owner[0-9]$|Record[0-9]$"                          # owner indices, anim record indices
    r"|Texel[0-9]+$"                                      # texel sizes (TintTexel16)
    r"|Tex_[0-9]+$"                                       # texture bank indices (gResultCubeTex_0)
    r"|(?:Div|Mod|Shift)[0-9]+$"                         # literal timer math (counter>>n, %3, /3)
    r"|TileAttrTable[0-9]$"                               # diorama tile attr tables
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
    r"|(?:Prim|Env)[RGBA]$"                         # color channel accessors incl. alpha (PrimA = alpha channel)
    r"|(?:AA|ZB)$"                                          # render mode abbreviations (G_RM_AA_XLU_SURF2)
    r"|_CB$"                                                    # spline cube macro CB(x)=x*x*x (gSplineD_CB)
    r"|TOC$"                                                    # table-of-contents acronym (gAudioSeqTOC)
    r"|LoadGfx[0-9A-F]{1,4}(?:_[0-9A-F]{1,4})?(?:_Alt[0-9])?$"  # gfx file IDs (script resource lists)
    r"|Palette[0-9A-F]{1,2}$"                            # palette IDs (TriggerDefaultPalette1B)
    r"|(?:Get|Set|Approach)FieldOffset[0-9A-F]{2}$"       # struct-field offset accessors (FieldOffsetAC)
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
    if re.search(r"[A-F]$", name) and not COMPOUND_SUFFIX.search(name):
        if not re.search(r"(?:Color|Config|Variant|Setup)[A-C]$", name):
            if not re.search(r"(?:Seed|Rng)[ABC]$", name):  # RNG variants are semantic
                return True
    # Banned terminology — check for yaw/roll ANYWHERE; pitch only outside audio domain
    # (Controller/Scroll contain the "roll" substring; audio pitch is a frequency term)
    if re.search(r"yaw|roll", name, re.I) and not re.search(r"Rollout|Rolling|Scroll|Controller", name, re.I):
        return True
    if re.search(r"pitch", name, re.I) and not re.search(r"(?:Sfx|Audio|Bgm|Music|Sound|Tone|Note|PitchTable|Cry|MenuPitch|PlayerPitch|ChannelPitch|TrackPitch|PitchModifier|PitchSlide)", name, re.I):
        return True
    if re.search(r"roll", name, re.I) and not re.search(r"Rollout|Rolling|Scroll|Controller|RollAi", name, re.I):
        return True
    if re.search(r"Custom$|Variant$|Type$", name) and not re.search(r"(?:Any|To|By|Of)Type$|SushiType$|EffectType$|TypeIndex$|ByVariant$|Trail40Variant$", name):
        return True
    if re.search(r"VictoryPalace|KidsClub|PokeCup|PokemonLab", name):
        return True
    # Non-ASCII
    if re.search(r"[^\x00-\x7F]", name):
        return True
    # British spellings
    if re.search(r"colour|centre|behaviour|favour|honour", name, re.I):
        return True
    # Too generic — verb-first with no domain prefix. "RegisteredTeam" is
    # michiiik's established domain (40+ uses), not the verb "Register".
    if re.match(r"^(Process|Update|Handle|Register|Init|Set|Get)\w*$", name) and not name.startswith("Registered"):
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
