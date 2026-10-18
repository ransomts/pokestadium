# Matching session notes (for the next AI session)

## PICK UP HERE (2026-10-18 morning update, same day as the night handoff below)
Farm restructure mid-round (see "Round 10 morning addendum" at the bottom for detail):
- **farm11-a/b/c** replace farm10-a/b/c at their phase boundaries (farm11-c submitted 08:45
  job 17564010; farm11-a/b at ~11:50 when farm10 phase 2 ends, before their chains fire).
  FUNCS_OVERRIDE drops **func_80034348** (permuting proven dead: every ordering >= 40) and
  keeps 88805AEC/8437B0CC/88304850/8004A89C with copies 5/5/5/6, RUN_TAGs ga/gb/gc,
  FARM_PHASES=2 x 11 h. 34348 is now an agent/hand-only function.
- **Focus files REMOVED** (88805AEC, 88304850): overnight data showed focused copies (fc,
  17274-1816) far behind plain diversity copies (fa/fb, 4929/1642) — the stale-focus problem
  plus window restriction. All farm11 functions now use plain re-seed + diversity (empirically
  best). A rebuilt 4929-based 88805AEC focus file sits in `scratch/r10-focus/` if wanted.
- **func_8004A89C new basin injected**: `permuter_best/func_8004A89C/output-350-sf1/`
  (the r10-4a89c agent's domain rewrite, permuter-validated at an honest 350; 6 copies on
  farm11 so diversity reaches it). Two agents ran this morning — **neither matched**, but
  both produced breakthroughs (see the addendum): 34348's register-web ranking is fully
  mapped (next lever: comma-expression / statement-emitting-macro emission order, material
  in `scratch/r10-34348/`, worktree `.claude/worktrees/r10-34348`), 4A89C's tail mechanism
  is structurally solved (`scratch/r10-4a89c/notes.md` has the ranked next steps: make uopt
  propagate the +0x10 so the sample chain dies before the call args).

## PICK UP HERE (2026-10-17 night handoff)
State: **5 open functions** (post-rename-p11/waves; 97.9%+ of the game matched): func_8437B0CC
(giant, regalloc+stack), func_88805AEC (spill-slot ORDER problem), func_88304850 (pure
regalloc), func_8004A89C (GB APU, coupled regalloc chains), func_80034348 (fd 40 = one
v0<->a0 swap, 8 instructions). `farm10-a/b/c` are running a 3-phase x 11 h chained permuter
farm on all five (jobs farm10-*, ~01:00/12:00 phase boundaries); phase 2 auto-enables
diversity seeding, the metric-era gate, and FOCUS files for 88805AEC + 88304850.
Morning routine: `bash matching_notes/morning_check.sh`. Read the "Round 10" sections below
for: per-function diff diagnosis (which class each function's remaining error is),
what search spaces are already EXHAUSTED for func_80034348 (all statement orders/anchors/
local-reuse — needs shape understanding, not enumeration), the farm's new knobs
(permuter_farm.sh header), the scoring quarantine protocol (rename waves make fd.sh lie —
use a worktree + baseline-reproduction gate), and the uopt/ugen probe result (no debug
surface in the recompiled IDO). Suggested next round, by value: (1) hand analysis of
func_80034348's register swap, (2) GB APU domain rewrite of func_8004A89C, (3) focus-file
feedback from farm10 phase 2 results. Ops: permuter_best backup at
~/permuter_backup_20261017 (refresh occasionally — /scratch is not backed up).

Last updated 2026-10-07 (round 3). Branch `match-round-1` (local only, not pushed). Companion files
in this folder: `IDO_TRICKS.md` (every IDO 7.1 trick that produced a match — read it first), `fd.sh`
(build one object + diff one function), `var.py` (batch-test text variants of a function),
`agent_setup.sh <worktree>` (one-time setup for parallel agent worktrees: resets to match-round-1,
symlinks .venv/asm/expected/permuter/yaml/baserom.z64, private build/ copy).

## Status
- Code decompiled: 93.13% at start → **93.84%** after round 1 → **93.9x%** after round 3. 55 functions
  remain as `#pragma GLOBAL_ASM` (29 as of 2026-10-07 after round 7; list: `grep -rn GLOBAL_ASM src`). ROM builds byte-identical
  (`make` → `OK`).
- Round 1 (8 parallel agents, ~1 h): 15 matched. Round 2 (8 agents, ~12 min, stopped early): 1 matched
  (func_82F10BB4) + 2 drafts improved. Round 3 (8 parallel fork agents in worktrees + parent): 2
  matched so far (func_81002830, func_80034824) + func_80044EA4 draft rewritten from scratch
  (24743 → 6744; see its entry below). Round 4 (overnight 2026-10-06/07, GLM model in 9 worktree
  agents): 1 match (func_82F0BEF8, found uncommitted in a leftover worktree), nothing else usable.
  Round 5 (2026-10-07, Palmetto, 6 Opus 5.5 agents x 2 tier-1 functions, ~1 h wall): **9 matched**
  (func_80034BD4, func_86B09F64, func_81002530, func_81003A54, func_8436C6A4, func_88206110,
  func_8250281C, func_86A01CF0, func_87804320), func_80044EA4 6744 -> 396, func_84372670 4308 -> 2860,
  func_8437FD74 unchanged at 350 (mapped). Code 93.95% -> 94.33%. A 24-function permuter farm
  (jobs 16777856 + 16777947, 3-day limit) is running alongside; check `matching_notes/farm_status.sh`.
- Round 6 (2026-10-07, 8 Opus agents, tier 2 + survivors, ~1.5 h): **5 matched** (func_8003DB84,
  func_882111F8, func_80044EA4, func_86800B38, func_84372670), 2 solved only via a linker alias and
  PARKED on branch `round6-gfxhead-alias` pending the owner's decision (func_860005B8, func_86100C30),
  drafts improved: func_8437FD74 350 -> 90, func_84367660 229 -> 85, func_838043F8 56 -> 8,
  func_84302658 11 -> 7 lines (uncommitted idea in notes). Code 94.33% -> 94.79%, 40 functions left.
  Farm restarted (job list = the 8 open tier-1/2 functions).
- Round 7 (2026-10-07 evening, 15 Opus agents on all 26 tier-4 functions, ~3 h incl. a rate-limit
  interruption at 17:00 that killed 4 agents mid-work, all resumed): **11 matched** (func_80045FF0,
  func_88209B54, func_810010BC, func_88216000, func_84362084, func_885065E0, func_80041A98,
  func_88305F28, func_88203ED8, func_88201488, func_8120572C - three of them 960-1600 instructions,
  two with no prior draft), 13 drafts improved or mapped (func_80033D44 8071 -> 80, func_8437B0CC
  55319 -> 13175, func_86803C6C 5033 -> 2375, func_88304850 5776 -> 3777, func_8820BE14 3156 ->
  1755, GB APU trio typed + drafted, ...). Code 94.79% -> **96.40%**, **29 functions left**. New
  tools used for the first time: siblings (decisive for func_88216000, func_885065E0, func_88203ED8),
  accessmap (func_80033D44), ido_bisect (func_88209B54), transplant. Farm restarted on 16 functions
  (job 16792584, 6 x 12 h phases). Lessons: understanding the function beats the decompiler for
  repetitive code (three giants matched by hand-written C); diff.py `-s` false zeros; m2c was never
  installed (the venv's `m2c` is an unrelated package).
- Nearly every remaining function already has an `#ifdef NON_MATCHING` draft with a `//` comment
  saying what still differs. Trust those comments over this list if they disagree.

## Environment / setup (one-time per machine or worktree)
- Base ROM: `baseroms/us/baserom.z64` (US 1.0, md5 ed1378bc12115f71209a77844965ba50). It came from
  `~/Downloads/pokemon-stadium.zip`, which holds a **byte-swapped .n64**; convert with
  `dd conv=swab`. The Rev 1 / Rev 2 / EU ROMs in Downloads are the wrong versions.
- `.venv/` (gitignored) has requirements.txt + m2c + diff deps. `tools/permuter/` (gitignored) is
  decomp-permuter. `binutils-mips-linux-gnu` is installed system-wide.
- **Palmetto (RHEL8, no sudo):** system python3 is 3.6 -> venv built with `python3.12 -m venv .venv`
  (+ `pip install -r requirements.txt m2c cxxfilt python-Levenshtein ansiwrap pycparser toml`).
  MIPS binutils 2.42 built from source into `~/local/bin` (`configure --target=mips-linux-gnu
  --prefix=$HOME/local`); fd.sh puts `$HOME/local/bin` on PATH. Set up 2026-10-07 via
  `make setup && make extract && make diff-init` (skip `make init`: its distclean is unnecessary).
- Build: `env PATH=$PWD/.venv/bin:$HOME/local/bin:$PATH make -j8` → must print `build/pokestadium-us.z64: OK`.
- Diff: repo-root `diff.py` is broken on Python 3.12 → use `tools/asm-differ/diff.py -o <func> -s --format plain`
  or `matching_notes/fd.sh`.
- `progress.py -v us` counts a function as undecompiled while `asm/us/nonmatchings/.../<func>.s`
  exists; those are only regenerated by `make init`. After matching, delete the stale `.s` (or run
  `make init`) before reading progress.

## Process lessons (important)
- **Resumed agents lose their worktree cwd** (after a session restart, SendMessage-resume may run
  them with cwd = the main repo). They then edit main instead of their worktree. Tell every resumed
  agent to run `pwd` and re-cd to `.claude/worktrees/agent-<id>` before continuing.
- **fd.sh writes a shared /tmp/fd_last_<func>.txt** — an agent running fd.sh for the same function
  in another tree overwrites your copy. Judge fd.sh by its stdout, not by re-reading the /tmp file.
- **No em-dashes (—) or other non-ASCII in src/ comments**: preprocess.sh converts UTF-8→EUC-JP and
  iconv fails on U+2014 (breaks the whole file's build). Use ASCII `-` or `->`.
- Permuter import: `./.venv/bin/python3 tools/permuter/import.py src/<file>.c asm/us/nonmatchings/<ovl>/<func>.s`
  then fix compile.sh arg order (`-O2 -o "$OUTPUT" "$INPUT"`), run
  `./.venv/bin/python3 tools/permuter/permuter.py nonmatchings/<func> --stack-diffs -jN`.
- **Worktree base bug:** round-2 agents spawned with `isolation: worktree` were based on `master`
  (6995f32), NOT on `match-round-1`, so they worked on stale round-0 drafts. That largely explains the
  weak round 2. Next time either merge the branch first, or tell agents to
  `git checkout match-round-1 -- src/` (or `git reset --hard match-round-1`) at the start, and verify.
- Agents in worktrees: the sandbox refuses Bash with `$VAR` paths, heredocs, `source`, long `&&`
  chains. Have them write scripts with the Write tool and call by absolute path; call
  `<MAIN>/.venv/bin/python3` directly.
- **Agents must commit their own matches** (`git commit` in the worktree, then cherry-pick to
  match-round-1). Round 4 left its only match uncommitted in a worktree that was nearly deleted.
  Never leave `#if 1` (forced-on NON_MATCHING drafts) in src/ outside a scratch worktree - it breaks
  the checksum build for everyone. Clean up worktrees (`git worktree remove`) and `nonmatchings/`
  (permuter output, ~1 GB per long run) when done.
- Give each agent its own scratch subfolder (they overwrote each other's helper scripts).
- **Shared `asm/` symlink:** agent worktrees symlink the main repo's `asm/`, so deleting a matched
  function's `nonmatchings/*.s` breaks the full `make` in every OTHER worktree whose source still has
  that GLOBAL_ASM. During a round, leave the `.s` files alone (progress.py will undercount) and delete
  them all once the round is merged. Agent 1 regenerated deleted ones with splat into a scratch dir
  (`.claude/worktrees/agent-1/scratch_agent/split`) - that copy was verified byte-identical.
- **Session restarts leave zombie agents:** after a Claude Code restart on a new node, the old node's
  agents kept running and editing the same worktrees as the resumed ones. Cancel the old interactive
  job before resuming agents.
- Insight beat brute force: every round-1 win came from recognising the original source shape
  (64-bit math, recursion, function statics, CSE temps, arrays). The permuter almost never closed a
  gap; it is only worth long runs on pure register-allocation near misses (candidate for the Palmetto
  cluster: needs repo + tools/ido + mips-linux-gnu-as).
- Permuter gotchas: always `--stack-diffs`; fix generated compile.sh arg order if it uses
  preprocess.sh; scores are inflated by a constant when the file has static data/bss (statics become
  section-relative relocs) — judge by the real `fd.sh` diff instead.
- Quick bisection trick: disable chunks of a function with `if (0)` and watch only the target lines
  to find which part of the code is perturbing them.

### func_81002830 — MATCHED (round 3, agent). Winning shape (see final source):
- `ptr = arg1;` as FIRST statement inside the if; `var_a4 = 1;` before it; a flag-conditioned empty
  `if (var_a4) {}` replacing `if (1) {}`; copy the global value out (`var_a4 = var_a3`) and REUSE
  var_a3 as the macro height arg. Makes IDO split arg1 across a1 (param) + a2 (copy) and puts
  D_800AF7AE's address+value in a3 so the gfx `_g` temps rotate from t0. Permuter lesson:
  RE-SEED the permuter from the current best source, not the original draft (run 1 from the 165
  draft only reached 30 in 45 min; re-imported 30-source hit 0 within minutes).

### func_80034824 — MATCHED (round 3, agent). Winning shape:
- DELAY the cursor assignment (`vtx = vertices;`) until after the last pre-loop computation,
  index the remap table directly (`spA0[i]`, no `spA0++` walk), keep `vertices` itself as the
  loop pointer. Combined with temp_fs0-2 reuse from round 1. Likely applies to siblings.

### func_82F0BEF8 — MATCHED (round 4, a5dc305). Winning shape:
- Drop the `(u32)(u64)` on `func_8002D600`'s argument and instead put `(u32)(u64)` on BOTH
  `func_8002D7C0(...)` return values passed to `func_8001F1E8` (cases 0 and 1). Same hidden-temp
  trick as before, applied to the call results rather than the argument.

### func_80034BD4 — MATCHED (round 5, Opus agent, c31b4e2). Winning shape:
- func_80034824's shape (direct `temp_s1[i]` remap indexing, no pointer walk, `var_s0 = vertices;`
  delayed until just before the loop) fixed the integer s-regs; dropping the unused locals and
  moving the `s16* temp_s1` decl between spCA and spC0 fixed the frame; the loop's x/y/z FPU regs
  needed a block-scoped `ModelBlendWeight* wt = &var_s0->cmd.weights[index];` with `w0 = wt->w0;`
  etc. instead of indexing `weights[index]` three times (30 -> 0).
- Trap: a first-match text replace of `f32 w0, w1, w2;` in 33FE0.c hits func_80034824 first.

### func_86B09F64 — MATCHED (round 5, Opus agent, 8c69b81). Winning shape:
- It is SM64's `mtxf_rotate_zxy_and_translate` with by-value args: declare `sx, cx, sy, cy, sz, cz`
  in that order, each set directly from SINS/COSS; write `sx * sy * sz` and `sx * cy * cz` inline
  (IDO CSEs and spills to 0(sp) itself); `mf[0][3] = mf[1][3] = mf[2][3] = 0.0f; mf[3][3] = 1.0f;`
  and `UNUSED s32 pad[2];` as the first local for the 0x28 frame. The draft's `temp[10]` hack was
  the problem. Lesson: before fighting FPU regalloc, look for a known SM64/libultra equivalent.

### Round 5 matches (2026-10-07, Opus 5.5 agents in worktrees, 2 functions each)
- **func_81002530** (01670a4): drop the redundant `& 0xFF` from the condition and write
  `temp_t3 = 0x4000 - (u16)(D_81004B60 >> 4);`. The `(u16)` cast uses one hidden temp AFTER the lbu
  instead of before it, so the lbu lands in t7 and the body temps rotate back. `(s16)` uses two temps
  and overshoots; the result is stored to an s16 anyway.
- **func_81003A54** (e30dad4): make temp_t0 `u8` (was u32) - that removes the whole `(u32)(u64)` chain
  hack and gives `t0` + `move a3,t0`; `pad[3]` -> `pad[4]` to keep the 0x50 frame; texture address as
  `D_3000000 + ((sp4D & 0xF) << 4) + ((((sp4D & 0xF0) >> 4) << 4) * 256)` (hidden temp between the
  andi and the sra). `(row * 16) << 8` also matches; `<< 0xC` and `* 16 * 256` give 840.
- **func_8436C6A4** (46967b9): the TRIANGLES macro's j<2 / k<4 nested loops were ONE loop of 8:
  `for (j = 0; j < 8; j++) gSP2Triangles(arg0++, j, j+9, j+1, 0, j+9, j+10, j+1, 0);` - IDO unrolls
  it by 4 and 0x06000000 lands in s4. Lesson: a 2-iteration outer loop around a 4x-unrolled body
  means a single loop of 8 in the source.
- **func_88206110** (9e7a76e): `arg0->unk_00.unk_00 = func_8002816C() & 0xFF;` (returns 9 bits; same
  idiom in fragment17) and `arg0->unk_1E = guRandom() & 0xFFFF;` - each mask burns one hidden temp,
  fixing the t-register offset through the whole function; the 4-byte copy is `u8 unk_08[4]` in
  unk_D_88217D10 plus `for (j = 0; j < 4; j++) arg0->unk_09[j] = temp_a1[i].unk_08[j];` (fully
  unrolled). One fake copy `var_a2_copy = var_a2;` in the not-found reset is still needed.
- **func_8250281C** (a2d8938): reuse `var_a2_2` (u32, first declared) for the D_8780FA48 copy so it
  lands at sp+0x44 (a new local grows the frame); pass `-1 - (s32)var_a2_2` (the cast stops the -1
  being shared with the gDPSetEnvColor constant); cases 1/2/4 compute sp38 in ONE expression
  (`sp38 = X * 0x58 + 0xBA;`); `if (1) {}` after case 5's sp38 keeps sp30 in a2; `D_8780FA48 += 0;`
  in case 2 still required. Dead ends: dropping inner `break;`s, changing sp30's type.
- **func_86A01CF0** (bd46d36; written by a now-dead duplicate of agent 6, see process lessons): the `D_86A03C98` reference was really `D_86A03D40[arg5][arg6 - 6]`
  (splat named the -0xA8 address after the preceding symbol); with the right index both register
  hacks disappear. Lesson: a negative-offset access to a splat-named symbol is probably an indexed
  access into the NEXT symbol.
- **func_87804320** (agent 5): `spAC` is a plain `Vtx*` indexed as `&spAC[var_s4 * 4 + k]` instead of the
  `Vtx4` struct (275 -> 150; moves the s3 copy to the loop top), and the loop tail is
  `spA4[var_s4 + 1] = spA4[var_s4++] + 0x36;` (-> 0). That line is unsequenced in C but is the only
  form found that matches; the well-defined `j = var_s4++` version scores 1248.
- Also this round: func_80034BD4, func_86B09F64 (entries above).

### Round 7 matches (2026-10-07, 15 Opus 5.5 agents; tier 4 structural, with siblings/accessmap/digest tools)
- **func_80045FF0** (f0ab161; 960 instr, no draft existed; matched in ~5 min of agent time): it is the
  per-frame bitstream decoder of the speech codec (func_80045780 in 45720.c calls it per 160-sample
  frame). LSB-first bit reader over a 0x400-word ring at `arg0+0x1598` (read as `((u32*)...)[]`, the
  header's 8-byte-stride DMA struct type kept), position in unk_25BC; a 1 bit starts a silence run
  (4 bits + 1 frames, unk_18C -> `bzero(out, 0x140)`), a 0 bit a voiced run (7 bits + 1, unk_18A ->
  8 header fields of 6,6,5,5,4,4,3,3 bits, 4 subframes of 7,2,2,6 bits + 13 x 3 bits, then
  func_80045C78; same layout func_80045D60 unpacks). Written as a `READ_BITS(dst, n)` macro used 77
  times; locals `i, left, bits, pad[2]`... the 1-bit flag is read into the otherwise-unused loop
  counter `i` (puts the flag in t3 and the constant in a0). Lesson: skipping m2c and writing the
  obvious source for a repetitive pattern matched in 4 cycles; the oracles cannot run without a draft.

- **func_88209B54** (1190 instr, 580 -> 0): (1) the 0x30000 constant cached in s1 - ido_bisect showed
  `-Wo,-no_const_in_reg` removed those lines, i.e. uopt CSE'd the constant across two calls; the fix is
  in a CALLEE's prototype: `func_88217018`'s 3rd parameter is `s32` not `u32` (fragment23.h and its
  definition in fragment23_1BCF10.c; its sibling func_88217060 already took s32), so the two calls pass
  the constant as different types and IDO stops sharing it. (2) arg1/arg2 swapped s-regs: a fake
  `if (arg1) {}` as the first statement (commented as fake) gives arg1 s0; swapping the two unk_10
  stores also fixes the regs but reorders the stores. The two "contrived" temps (`temp_s1 = 0x10000`,
  twice-reloaded temp_s0_8) are real - removing either breaks the else branch. Lesson: a constant
  CSE'd into an s-register can mean a callee's prototype used a different int type.

- **func_810010BC** (965 instr, 13345 -> 0 in ~1 h, three commits): arg2 is really `DisplayListAddresses*`
  (fragment31.h: `segments[2]`, `textures[]`; same type func_81002530 uses) and the texture is
  `arg2->textures[arg1->misc / 2]`; the hand-expanded texture loads are `gDPLoadTextureBlock_4b(gfx++,
  tex, G_IM_FMT_I, 32, 32, ...)` and, for case 0x86/0x90, `gDPLoadTextureBlock(..., G_IM_FMT_IA,
  G_IM_SIZ_16b, 32, 32, ...)` (13345 -> 8305); raw words were gSPMatrix(PUSH|LOAD|MODELVIEW),
  gSPPopMatrix, gDPSetPrimColor; the second switch needs a LOCAL copy of D_8006F09C (else reloaded
  after every store) and `position.y += k * var->unk_030.y` before `misc++`; an `f32 temp_f` (in
  pad2's place) holds `D_810040DC[misc % 12]` for the three scale stores (the chained `a = b = c =`
  form adds 8 bytes of stack); CASE LABEL ORDER `case 0x92: case 0x4D: case 0x4E:` moved the arg2
  reload to the right case and fixed the whole t-rotation (1850 -> 85); the last v0/v1 swap: one
  function-scope `var_v0 = D_8006F09C` assigned twice (before the 0xFE guScale if, and again inside
  `if (func_800325AC() == 0)`). Oracles found none of this: all of it was source shape.

- **func_88216000** (629 instr, 18415 -> 0): it is the matched func_88507DBC (fragment26.c) copied
  verbatim except `(arg0->unk_2C->unk_00.unk_2C->unk_08 + 1)` - the one extra `addiu`. Signature
  `s32 func_88216000(unk_func_88507D4C* arg0, s32 arg1, s32 arg2)` (fragment23.h prototype updated).
  Found by `corpus.py siblings` (0.997) and confirmed by `transplant.py`; the "custom load-block
  macro" theory in the old notes was wrong - the DXT was computed at runtime because the twin does so.
- **func_8820BE14** (447 instr, 3156 -> 1755, draft 92b38a1): root cause - the target uses SEVEN
  callee-saved regs (s0-s6), keeping `ptr2` (`&var_s4_2->unk_04`) in s0 in the inner loops, so the
  func_8850068C address gets s4 instead of a spill to 0x54(sp). `j = 0;` hoisted above the
  `func_882062E4` call with `for (; j < count; j++)` makes j live across the call and take the 7th
  register (u32 j gives 2365). Remaining: target strength-reduces j (v0 = j*4) and keeps ptr2 in s0
  (ours j in s2, ptr2 in a0); s0/s2 swapped in the first three loops, var_s1 in s0; the
  `unk_30.unk_00/unk_02` halfword store order; FRAGMENT_LOAD relocs name different (probably aliased)
  symbols. ~40 dead ends in the draft comment. Regalloc-only now -> permuter farm from this draft.

- **func_84362084** (1559 instr, 65017 -> 0 over 9 commits; fd.sh showed 11867 because diff.py caps at
  1000 lines): the straight-line `gSP2Triangles` runs were LOOPS IDO unrolled 4x - case 6/7
  `for (j = 0; j < 5; j++) gSP2Triangles(arg0++, j, j+6, j+1, 0, j+1, j+6, j+7, 0);` (one peeled
  iteration + 4x unroll leaves `j = 1` stored and `v0 = j*2` unfolded), case 2/4 `j < 14` (2 peeled +
  3-trip loop) - 65017 -> 9911 and frame 0x210 -> 0x1c8; case-8 strips `u8 idx = j * 3`; outer loop
  `if (unk_000 == 1) { ... } sp1B4++;` with only `i++` in the for-increment instead of `continue`
  (4642 -> 1402); `var_s2++` as the LAST body statement in the 2-3-vertex loops; final case-8 block
  as a one-case `switch (sp1B4->unk_008) { case 8: ... break; }` instead of `if` (1280 -> 0: D_84389290
  address in a3, t-regs, and the sp1B4 reload per iteration). `M_PI` -> `M_PI_F` in two double
  expressions: diff.py scored 0 either way but the ROM differed ((double)(float)pi) - only the full
  make caught it. No sibling (0.14), no bisect switch helped.
- **func_885065E0** (391 instr, 5850 -> 0): the weak sibling func_8850C3B8 (same file) is the same
  function with renamed fields; the row/column cursors are `sp4C`/`sp50` themselves (no var_t1/var_a3
  copies); decl order `sp5C, sp58, sp54, sp50, sp4C, sp48, i, j, temp_v0_3, sp24, var_t4` with var_t4
  LAST (frame 0x70 -> 0x60); in the 0x100/0x200 cases `j` is the OUTER counter (1695 -> 835); comma
  initialisers `for (i = 0, sp4C = sp54; ...)` (-> 685); the 0x400 compare is `if (sp4C + 1 == sp48)`.
- **func_88305F28** (391 instr, 612 -> 0): delete the fake `if ((!arg0) && (!arg0)) {}` (it split a
  basic block and pushed unk_0AC into a1 not t0); `spD8` indexed with `arg0->unk_034->unk_00.unk_38`
  directly and spD0 assigned after it (spD0 spills where assigned); `sp34` was a compiler temp
  (`&spD8->unk_08` / `spD8 + spC0`) -> write `spD8->unk_08.unk_09[spC0]` + `UNUSED s32 pad;`;
  `if (1) {}` at the top of the else of `if (spC0 < 4)` fixed the beqz delay slot.
- **func_80041A98** (118 instr): `D_800FCCA0 = D_800FCCA1 = 0;` (chained) instead of a volatile store
  + plain store, and both externs u8 not s8: the chained form re-reads the inner variable so
  `&D_800FCCA1` has two uses and uopt keeps the address in a0 (fixing the a0/a1 swap in the last
  loop); s8 leaves a real `sb` reload. Remaining diff.py lines are `D_800FCB48` vs `D_800FCB38+0x10`
  (same address).

- **func_88203ED8** (825 instr, 4159 -> 0): the sibling func_882121E0's first-loop shape -
  `arg0->unk_44[j]` and `D_88217C6C[j].field` indexed directly (call args in the right order,
  target's `move a0,v0` appears); loop test `j < 5U` with `s32 j` (unsigned compare gives `sltiu`
  and keeps a plain counter; `j < 5` makes IDO swap the counter for a pointer or j*4; u32 j spills);
  the unrolled unk_18 loop reuses j, the string loop needs its own `x` (`li 5; bne`);
  `temp->unk_44 = temp->unk_44;` between the unk_30 and unk_34 stores as in the sibling;
  `UNUSED s32 pad[6]` at the top of the locals and `pad2[4]` at the bottom.
- **func_88201488** (582 instr, 5805 -> 0): raw Gfx word stores rewritten as macros (style of
  func_88214A58 / func_886002A8): a 40x40 RGBA16 block from `arg2->unk_08` and an 8x10 IA8 block from
  `D_4006A08` (now `u8[]`); arg2 retyped as a new struct whose field 0 points to the old type with the
  texture at offset 8 (old struct gained `unk_30`, the string); fill rects 1/2 need
  `(arg0 - 2) + arg5->unk_3C` for the add order; the four same-colour border rects split into three
  blocks each re-declaring `u32 color = GPACK(...)` (rect 1 | rects 2+3 | rect 4) to reproduce the
  recompute of `(color<<16)|color`; `pad[2]`.

- **func_8120572C** (1436 instr, no draft existed; 5624 -> 0 over 7 commits, hand-written, no m2c):
  Transfer Pak / GB emulator control switch. `case 1` first; the shared exit block (`stop:`/`reset:`)
  INSIDE the switch after case 6; case 5 `goto case2` on a failed checksum; inner switches
  `i = emu->unk_548E; switch (i)` with `case 1: default:` first and `switch (D_8122C4E2)` listing
  case 2 before case 1; a `btn` local holding `emu->unk_53F6`, reassigned from it inside the 0x2000
  block (partial reload); `D_8122C4F0 = -0x40` after the `D_8122C4E4 < D_8122C4E6` check; frame 0x48
  only with the struct pointer kept IN THE PARAMETER (`#define emu ((unk_D_8122B2C0*) arg0)` +
  `arg0 = (s32)(&D_8122B2C0)[arg0];`, `#undef` after - a commented shape hack; a separate local
  pushes the frame to 0x50); ROM-header bounds `< 8U` / `< 5U`; unk_5394/unk_5398 as ternaries in the
  `== 0xFF` block (last scheduling diff); the 0x100-entry 549C fill as a `while`; abs as
  `(F0 <= 0) ? -F0 : F0`; chained `[0] = [1] = [2] = [3] = 0xFF`. Shared-file changes: global.h
  `unk_D_8122B2C0` filler split into named fields (unk_53A4..unk_5490), `unk_53FC` u8 -> s8 (target
  `lb`); fragment1_7F9A0.c `unk_D_8122B1E8` gained unk_28/unk_2C/unk_40..unk_58. Remaining diff.py
  line is `SP_STATUS_REG` symbol vs constant (same bytes). Oracles did not help (456/1436 identical
  at the first draft; no bisect switch); fd-style diffs + a variant script did it.

### Round 7 drafts improved / mapped (no match yet)
- **func_80033D44** (33FE0, 8071 -> 80, 84edf49): accessmap was right - stores were one field late;
  `StadiumTransform.unk_00` is `s16 unk_00; s16 pad02;` (target writes it with `sh`; 33FE0.h);
  plain `xf->field = argN` stores; the spD8/spD4/spD0 vector must be initialised with DOUBLE literals
  (`-1.0`, `0.0`): with `0.0f` uopt folds the x*0 terms of the dot product to one multiply (confirmed
  in a standalone IDO test); normalise dx/dy/dz in place; `len != 0.0f`; locals ordered to the target
  stack map; `s32 pad[2]` last. Remaining: s2/s3 swapped (target idx in s2, i in s3) - 15 dead ends in
  the draft comment -> farm.
- **func_80034348** (33FE0, 3485 -> 2905, 74b3a64): frame, first loop and start of the triangle loop
  match; left: FPU regalloc in the cross product - the target saves fs3 but never uses it, so every
  later float reg is shifted by one (probably a named local like ax/cx given fs3 then spilled).
  Target stack map: i 0xF4, ax 0xF0 (spilled), cx 0xD8 (spilled), ia/ib/ic 0xBE/BC/BA, remap 0x84,
  temps 0x58 (c.y-b.y), 0x5C (b.z-a.z), 0x60 (c.z-b.z) = nine named coordinates + nx/ny/nz/len with
  edges inline. Dead ends: clean rewrite in that form 9500-11000 (spills ay/az/nx); pointer loads
  13193; nx before ny ~3600; inlined edge terms 3280-5172.
- **func_88500A74** (frag26, 3031 -> 2991, cd5c312): locals `sp34, y, x, sp88` give the exact target
  stack layout; left: the two sums (`arg0+arg2`, `arg1+arg3`) go to t8/v0 and spill immediately in
  the target (freeing s2/s3 for gfx constants, s1 for the scissor `_g`), ours s4/s2 with earlier adds.
  ~12 dead ends in the draft comment; no bisect switch -> farm.
- **func_88304850** (frag24, 5776 -> 3777, bb62be5): stack layout now exact: sp50 (`arg0 + 0x84`) and
  sp58 (`arg1 + 4`) were compiler temps (`pad[2]` keeps 0xC0); `temp_v1 = D_883172CC[arg3 & 1]`
  hoisted before the first loop (shares `(arg3 & 1) << 3`); `var_s4 = arg1 + 2` assigned inside the
  func_8001F1E8 argument list; cases 2/10-15 compute the text offset into a variable. Left:
  first-half regalloc (gDisplayListHead in t0, colours a3/a0, s1=var_s1 s2=arg2 s3=x, `arg0+0x84`
  spilled to 0x50 vs our s0, late `li a3,3`/`lui ra,0xF600`) -> farm with --stack-diffs.
- **func_86803C6C** (frag14, 5033 -> 2375, 8c13980): hoist `tmp = SQ(unk_074.x) + SQ(unk_074.z)`
  before `if (unk_060 == 0)`; spell the threshold `1e-6f` not `0.000001f` (otherwise uopt shares the
  constant's register with the ABS_NORMALIZED literals; late_rodata then lines up: seven 1e-6 before
  1e-4). Left: one more integer temp in L1003-1011 (every later t-reg off by one) and `mtc1 zero`
  per ABS_NORMALIZED branch in the target -> farm.
- **func_80012870** (12D80, 60, one line, 3ebfc8f): the as1 scheduler places `sw t8(0xFF),0x24(sp)`
  one slot before `sra a2` instead of after; registers, FPU code and pre-scheduling order are all
  identical; ~35 variants and every bisect switch failed -> farm (as1 scheduling).
- **func_88807D04** (frag28, 705, 6 lines, 6c9fbad): `cc -S` order already equals the target, so the
  whole diff is as1 cross-block scheduling (only as1-noxbb changes it): as1 hoists two `lui %hi`
  above the `bltz` and puts `addu s0` in the jal delay slot where the target has `sll s4,s1,2`.
  Near misses `!= -1` (530, wrong branch) and `if (1) { temp_s0 = ...; }` (350). ~30 dead ends -> farm.
- **func_88805AEC** (frag28, 14747, frame 0x230 vs 0x228): structure right incl. the switch default
  precomputing the join rectangle; diff is regalloc/spills everywhere: target keeps arg2 in t4 for
  the whole function (we reload 8x), arg5 in v1, stores arg1+arg3 to 0x44 and reloads at once,
  arg2+arg4 to 0x30 at first use after the D_888236A0 block. Sweep of tmp/tmp2 inlining and pads
  all worse (table in the draft comment).
- **func_86905734** (frag15, 1952 unchanged; twin func_86905F24 shape already in place): all diffs are
  in the 8 corner-coordinate lines (FPU reg choice + which subexpressions go to stack temps). Target
  temps: (f32)arg1 at 0x64 (then spilled to 0x30), -h*sin 0x60, (f32)arg2 0x5C, h*cos 0x58, h*sin
  0x54, (f32)h 0x50, cos*-arg4 0x3C (h = arg3/2); in regs: cos, sin, (f32)-h, (f32)-arg4, -h*cos,
  sin*-arg4. Using arg1/arg2 directly + pad[4] = 2552; all 66 a1/a2 local pairings tried; named h/-h/
  -arg4/cos/sin >= 4000; operand swaps identical -> farm with --stack-diffs.
- **func_8130337C** (frag33, 13923, 166/553 identical): the pipesync constant 0xE7000000 lives in the
  draft's s3 for the whole function; the target has it in v1 for the first two pipesyncs only,
  reloads it fresh in both loops, and holds it in s2 only between the switch and loop 2; loop 2
  keeps only E45E8000/3E8000/FD100000(fp)/F5100000(ra) in regs with all six counters in s-regs.
  `if (0)` probes removing loop 1 / loop 2 / the switch / the first pipesync all still keep E7 in a
  register, so the source shape differs somewhere unfound. No corpus function keeps E7 in v1.
- **GB APU trio, src/4A3E0.c** (agent 1, five commits, no match): the struct's missing `;` is fixed
  (7294c7c); `D_800FD008` is now `GbSoundReg D_800FD008[0x20]` = `{u8 value; u8 dirty;}` per register
  (NR10..NR52 = 0xFF10+index; matched users func_8004980C/800498A8/80049A60 re-indexed, ROM unchanged);
  D_800FCF60 (channel 1, 0x30 bytes) and D_800FCF90 (channel 2, 0x28) have real layouts from the asm
  (`u16 unk_04` frequency, `u16 unk_18[2]`/`unk_10[2]` duty half-periods, u8 phase at 0x1E/0x16).
  Scores (measured WITHOUT diff.py's `-s`, which stops at the first `jr ra` and under-reports these
  early-return functions - fd.sh showed ~185 for func_80049DF0 and ido_bisect showed 0 for
  func_8004A474): func_8004A89C channel 4 noise 5415 -> 3355 (integer literal `unk_10 = 0` stops a
  single 0.0f register; read unk_04 and `NR42 & 8` into locals before the unk_20 test; take
  `&D_800FC6CC[sample]` after the value load; left: unk_0C store addressing/order, trigger-block order,
  NR42 reread); func_80049DF0 channel 1 square+sweep new draft 3565 (`default:` last with no break,
  one temp reused for duty/NR12/NR10, s32 NR11 local reused for the swept frequency,
  `(u8)(nr14 & 7) << 8`, fail-first range test, `unk_14 = unk_10 = x` then separate -1 stores; left:
  sweep-block regalloc); func_8004A474 channel 2 square new draft 1420 (same shape minus sweep,
  `(u8)(nr24 & 7) << 8`, NR21 read twice; left: one-step temp offset from the trigger block on, 0x800
  not kept in a register, NR22 read via a base register) -> farm candidate.
- **func_8437B0CC** (frag62_361050, 3346 instr, 55319 -> 13175 full-diff score with `--max-size 20000`;
  fd.sh under-reports): removed ~120 unused m2c locals (frame 0x260 -> 0x120); **`CLAMP_MAX`/`CLAMP_MIN`
  in include/macros.h are INVERTED** (`CLAMP_MAX(x,max)` returns the larger value) - the draft used
  explicit ternaries instead (6 other files use the macros; they match because the names are
  misleading, not wrong); m2c spXX copies (sp50/54/5C/64/68/6C/70) are compiler temps, written
  inline; unk_09/unk_0F u8; decls in target stack order; `var_s5` u8 and `temp_s6 = &temp_fp->unk_12`
  hoisted out of the loop (s5/s6/s7 right); dropped `!= (spB6 * 0)`; case 0x9C goto-condition as one
  `if`; case 0x19 reads `temp_s6->unk_15` once for both switches. Target stack: every local has a slot
  0x107 (i) down to 0x84 in decl order; spills below in 0x50-0x80 (copied unk_09/0A/0F, the arg2
  bound, `unk_0A*0x11`, `unk_0B*0x14`). Left: frame 0x110 vs 0x108 (15 spill slots vs 13, shifting
  every local by 8 = ~250 stack lines); case 0x2 `unk_00 == 0x5C` block (target keeps unk_0A in s5
  across the first call via 0x68 and spills spBA to 0x64; we spill spB7 and reload unk_0A); end-of-loop
  clamps (t5/t9 swapped for unk_01/sp58 - visible in every break's delay slot; unk_06/unk_08 in s2/t1
  reversed); case 0x19 missing `move v1,v0` after the 0/8 compares; prologue arg2 load order. NOT a
  permuter candidate yet: case 0x2 and the frame need source changes. Dead ends in the draft comment.
- **func_8820BE14**: see Round 7 matches section (1755).

### Round 6 matches (2026-10-07, 8 Opus 5.5 agents; tier 2 stack-layout + survivors)
- **func_8003DB84** (3051084): declare `D_800FCB28` as `u32` (was s32; extern in 3D140_2.c and the
  definition in 3D140.c) - that removes one hidden temp and moves the a0 spill from 0x18 to 0x1C.
  Came straight from the permuter's score-10 candidate. fd.sh still shows `D_800FCC50` vs
  `D_800FCB48+0x108`: same address, ROM matches. Lesson: with an exactly-full frame, the SIGNEDNESS
  of a global can shift compiler temp slots without touching locals.
- **func_86800B38** (b921a5a): ONE pointer `unk_D_86807558* ptr;` declared at switch scope next to
  var_s4/var_s7, used as `for (i = 0, ptr = D_86807558; i < 4; i++, ptr++)` in BOTH the case 2/3 loop
  and the case 5/6 loop (all `D_86807558[i].` in case 2/3 -> `ptr->`). Fixes the increment order and
  the &spC4 spill (0x50) at once. Scope matters: function-scope ptr 1100-1400; only in case 5/6 1304;
  also in the function's first loop breaks it. Cleanup: `Color_RGB8 spB8[2][4]` replaces the
  out-of-bounds `spB8[i + 4]`; `if (pad1) {}` still needed.
- **func_84372670** (agent 7): the unk_4F retry jump no longer targets `case_6` directly but a new
  label `loop_4F:` inside case 5, after `switch (unk_01) { case 7: break; }` and just before its
  `goto case_6;` (same behaviour). The back-edge now forms a loop with TWO entries, so uopt stops
  treating it as a loop and no longer caches `&D_843C5238` in s0; plain `D_843C5238->` accesses then
  give the target's v1 CSE and `beqzl` exactly. The `p = &D_843C5238` hack is gone; `UNUSED s32 pad;`
  before sp2C for the 0x38 frame. fd.sh shows 10 = `D_80072AFE` vs `D_80072B00-0x2` (same address),
  ROM OK. Retargeting the back-edge to `case_5` also drops s0 but branches wrong (1705). Lesson: an
  s-register-cached global address caused by a goto loop goes away if the loop gets a second entry.
- **func_882111F8** (e9ec242): delete the named pointer locals sp20/sp1C and index directly
  (`sp30 = ptr[arg1]; sp2C = ptr[arg2]; ... ptr[arg1] = sp2C; ptr[arg2] = sp30;`) with one
  `UNUSED s32 pad;` after var_v1 for the 0x38 frame; the CSE'd addresses become the 0x20/0x1C
  spill temps. Lesson: register-held pointer locals spilled one slot too low are CSE'd index
  expressions in the original, not named locals.

### func_80044EA4 — MATCHED (round 6, agent 8; was 24743 at project start, 6744 -> 396 -> 0)
- The `u8* p` cursor local was the whole remaining problem. The original indexes `D_800FCEF0[i]`
  directly at every site (the `== 2` continue, the `!= 0 && != 3` test, the 2/4/0/1 stores and
  `switch (D_800FCEF0[i])`); IDO strength-reduces that into its OWN stepping pointer - a compiler
  temp, which is what lives at 0x5c. Drop `p` and one pad (8 named locals): the pointer lands at
  0x5c, the D_800FCED8[i] spill moves to 0x44, AND the case-0 `beqzl` becomes `beqz` - both diffs
  had this one cause. Lesson (also in IDO_TRICKS): a pointer in a stack slot right below the named
  locals may be the compiler's own strength-reduced pointer; write plain `arr[i]` and drop a pad.
- History of what got the structure right is below (still useful for the sibling audio code).

### func_80044EA4 history (45720; structure SOLVED in round 3, regalloc in rounds 5-6)
- Round 5 (agent 6, commits on match-round-1): `(j << 1)` instead of `j * 2` in both store indices
  (IDO made `j*2` an induction variable; the target recomputes it per unrolled step - this was the
  meaning of the permuter's `u8 new_var` hint; 6744 -> 1886); `sample * D_800FCF00[i]` operand order
  (1071); `u32 i` stops the constant 2 living in v1 (716); `if (*p == 2) continue;` lets the skip
  path bypass the i/p reloads (396).
- Remaining: the D_800FCED8[i] spill is at 0x40 but should be at 0x44 (one extra compiler temp slot
  between p and the spill; a pad local after p fixes the position but grows the frame to 0x88), and
  `if (D_800FCED0 != 0)` in case 0 compiles to `beqzl` where the target has `beqz` with `lui at` in
  the delay slot. Dead ends for both are in the draft's // comment.
- Earlier history:
- The draft was fundamentally wrong: the target's inner loop is MONO→STEREO duplication — per j:
  `temp = (s16)((D_800FCF00[i] * D_800FCEE0[i][(base + j) % 2560]) >> 7);` then TWO stores:
  `unk_000[(F38 + j*2 + 1) % 2208] = temp; unk_000[(F38 + j*2) % 2208] = temp;` (+1 store first).
- Keys that got the structure right: `u32 D_800FCF38[2]` (divu not div — signed % blocked the 4x
  unroll), `(u8)` cast on unk_25D1 reads (lbu), a `u8* p` cursor LOCAL for D_800FCEF0 (`*p`
  everywhere, `p++` in the for-increment; slot 0x5c), `UNUSED` pads to place i at slot 0x70 and
  frame 0x80 (9 locals: 3 before i, p 9th), all array accesses written out per use (no caching
  locals — IDO CSEs the addresses into s-regs).
- Remaining: systematic one-slot rotations — mine {s1=FCF20, s2=FCF38, s3=FCF28, s4=2208, s5=j}
  vs target {s1=j, s2=FCF20, s3=FCF38, s4=FCF28, s5=2208}; the FCED8[i] CSE temp at 0x40 vs
  0x44 (mine has one extra temp slot); and a one-step t-lag. j's decl position and `!=` vs `<`
  loop bound don't change it; a while-loop form kills the unroll (much worse).
- Permuter (14 h, 6 workers, seeded from the in-tree draft) best = 3201 (permuter score), saved
  as `matching_notes/func_80044EA4_permuter_3201.c` (full permuter source.c - re-seed from it).
  Its key change: inside the inner loop, `unsigned char new_var = j;` and index both stores with
  `new_var * 2`. That truncates j to u8, which is probably NOT the real source (j can exceed 255) -
  treat it as a hint about which temp/register the target wants for `j*2`, then find a
  semantically valid form.

## Per-function state and dead ends (most promising first)

### Near misses — register allocation only
- **func_8437FD74** (frag62_361050, score 350): compare regs v1/a2 vs v0/v1; `if ((arg2 && arg2) && arg2) {}`
  is load-bearing (changing the number of `&&` gives 1300-3900). arg1 is `u8*`. Round 5 findings: i spills
  to 0xbf and j to 0xbe, so `spBF` is not a real local; `sp5C` is the compiler temp for the `temp_v0_2 - 2`
  bound, not a local; removing `u8 pad` changes nothing. The min result (target a1, ours s0) is a separate
  s32 `n = var_s2; if (var_a0_3 < var_s2) n = var_a0_3;` (u8/u16 add a mask). Any extra s32 local grows
  the frame 0xc0 -> 0xc8; the only 0xc0 layout found is `i j k l m spBA, two u8s, s32 n, sp94 sp90 sp78
  spBF sp76, two u8s, s32 var_s0` with sp5C inlined and pad removed - that fixes the min code but inlining
  sp5C swaps v0/v1 at the unk_04/unk_01 compare (score 880). Dead ends: reusing temp_v0_2/var_a0_3/var_s2/
  j/k/l/m for unk_04[i]; `unk_01[i] > unk_04[i]`; ~9 else-branch m-loop rewrites; reordering the arg2 sum;
  sibling-style ternaries (350, only with the `&&` line kept). The var_s0-top / n-bottom / no-spBF
  layout was then tried (agent 3, second pass): it puts n in a1 like the target but scores 495
  (var_a0_3 stays in v1 not a0, target's `b` missing; plain if/else 805) - that file is saved as
  `matching_notes/func_8437FD74_best495.c`. The arg2 no-op needs arg2 as the first of exactly three
  `&&` operands and can sit anywhere before the sp94 loop; from that loop on our temps run one ahead
  of the target's (t9 vs t8), apparently because the no-op allocates a temp that emits no code.
  More dead ends in the draft's // comment (567dd19).
  **Round 6 (agent 7): 350 -> 90** (b40b3ad, dddb096). Separate `s32 n` for the min result (in a1),
  its input reusing `j` (permuter output-230 hint), frame stays 0xc0 (layout in the draft comment);
  the else-branch copy loop uses `j` not `m`; `if (sp5C != 3) continue;` followed by `if (1) { body }`
  fixes the unk_04/unk_01 compare regs (bare block 305); the arg2 `&&` no-op moved from inside
  `if (i)` to just before `sp5C = ...` fixes the sp94-loop temps; `if (1) {}` at the top of the
  innermost loop places the i spill (0xbf). Remaining (90): the innermost-loop arg2 reload goes to v1
  (target t2) and t-regs run one ahead between the compare and that reload - single root cause left.
  Dead ends: all six sum orders, no-op elsewhere or as 2/4-term chains, switch for `== 3`, other sp5C
  types, sp5C as k/l/temp_v0_2/var_s2, copy-loop rewrites. Re-seed the farm from this draft.

### Near misses — stack layout
- **func_84367660** (frag62_351F20, 229 -> 85 in round 6, d221a56): stack layout now matches (six spills
  at 0x8C..0x78) but via a FAKE: a dead early copy of the six 1.2/0.2 expressions right after
  `a3_z = arg4 * sp128;` (from the farm's 205 hint). This shows compiler-temp slot order follows where
  each expression FIRST APPEARS in the source; the target's 3 never-stored slots sit below them, so
  those temps (probably the `a3_* * 2.0f` subexpressions) first appear later. Moving the six real
  assignments earlier wrecks the schedule (4600-9400). Remaining: pure regalloc - a3_z in fa0, 2*a3_y
  in ft4, both sp128 loads to ft4 not ft5. `if (a3_z) {}` still required; tmp1 hack worth 25. Dead
  ends: `sp128 * arg4` order, named 2*a3 temps / `(a3_y + a3_y)`, extra tmpN for vertex 8/9, moving
  the if, reordering the dead copies, indexed vertex writes (1466), loop forms, named temps for the
  func_80031A94 args, block-scoped pads. Good permuter candidate (re-seed from the 85 draft).
- **func_8850B2D4** (frag26, score 84, 4 stack lines): two spilled temps, the first rectangle's lry
  `(arg2+1)<<2 & 0xFFF` and its ulx<<12, reused by the last rectangle; target has lry at 8 and ulx at
  0x10 (nothing at 0xC), ours lry 0x10 / ulx 0xC. Round 6 dead ends: commuting operands; (u32)/(s16)
  casts or `* 4` on coords; every w/h type (16-bit -> 0xF8 frame), order, init; literal 8 in one
  LoadTextureBlock; function-level `color`; `if (1) {}` anywhere (reschedules everything); the farm's
  `(w = arg2 + 1)` (rotates reload regs only). A pad moves both slots but keeps the order.
- **func_82F04604** (frag41, score 318, 7 lines): partial fix NOT committed - delete named `sp68`,
  write `(s16)(spEE * spF8)` at every use, add an unused `s32 pad3;` in the block: that puts the
  `&D_8006F630`/`&D_8006F518` spills at 0x50/0x54 and orders the loop-end stores right, but the
  strength-reduced induction temp then sits one slot below `sp64` (target: above) -> 10 stack-only
  lines. No placement of the `sp64` decl fixes it. Next lead: make `sp64` a compiler temp still
  computed before the `func_82F022DC` call while var_s2 stays in s2. Dead ends: inlining sp64 (var_s2
  spills, 209 lines); for/do-while/swapped increments; function-level sp68; `s16 sp68`; inlining
  temp_s3/temp_lo. Observed: unused locals in any block get slots above the used ones.
- **func_8430506C** (frag62_2EC3C0, score 16, 4 stack lines): compiler temps sit right below the lowest
  named local, assigned top-down in a fixed order (sp28 value, sp40*4, &D_84390010[sp40]); moving the
  `sp28 =` assignment does not reorder them. Target: 9 named slots (0x2C..0x4C) + 4 temps (0x28, 0x24,
  an unused one at 0x20, 0x1C); draft: 10 named + 3 temps. Dropping pad2 (ptr2 moved into its place)
  gives identical code at frame 0x48, so the original has one fewer local and one extra never-stored
  temp. `sp40 = !func_84307F00(arg0);` or `!(x & 1) != 0` adds such a temp (frame back to 0x50) but it
  always takes the TOP slot (0x28) wherever it appears; the missing temp must be created at regalloc
  time and ordered between sp40*4 and the D address. Round-6 dead ends in the draft comment (6c8de07).
- **func_84302658** (frag62_2EC3C0, 11 lines, permuter base 64): target slot order var_a1 (0x2C),
  var_a1+0x20 (0x28), sp68*4 (0x24), &D_84384578[sp68] (0x20); draft has sp68*4 first. Best found
  (11 -> 7 lines, NOT committed as code): pass `arg0->unk_000.unk_01A * 0` as the 4th arg of the
  D_84384570 call only, AND `tmp = (u32)_70D3A0_ROM_START;` at the top used as `tmp + (...)` in the
  two D_80075BD0 lines, the else-branch D_6E910 line and the ptr2->unk_10 line (also removes the
  `(tmp = 2)` hack) -> order [a1, sp68*4, a2], only a2 and sp68*4 still swapped. Dead ends in the
  draft comment (662a5cc).
- **func_838043F8** (frag47, 56 -> 8 in round 6, e6e5825): named locals take slots top-down in
  declaration order (including each gfx macro's `_g`); compiler temps go from 0x48 upward with the
  8-byte alignment hole at 0x48. Target has 27 named words (block 4 has `s32 pad;`, not `pad[2]`) and
  one never-used temp slot (0x50) from a constant local live across the `func_800060E0` call and used
  in `temp_s2_2 + 0x24` (the farm's `new_var = 0x24` hint). The score-8 draft is a HACK (`i = 0x24;`
  before the call -> two unused slots, X at 0x48 not 0x4c). A real `new_var = 0x24` used in X, the
  second func_83803F34 call and loop 1 gives exactly one unused slot and the right temps (score 12,
  saved as `matching_notes/func_838043F8_newvar_12.c`) but adds a named word above sp80 (-> 0x7c).
  Dead ends: `ptr->` as `D_838067F0.`; inlining temp_s2_2/var_s0; new_var in a nested scope (slots
  still follow source order); constant local in block 4; operand order; s16 casts; `if (1) {}`.
  Dropping `ptr` puts &D_838067F0 in s5 not s0.
- **func_83501718** (frag44, score 60, bbbfc04): the 0xa4 slot is the compiler temp for `arg1 + tmp2`,
  not x's slot. Draft and target have the same 7 unused temp slots in a different order: in the target
  five of them are allocated BEFORE x (x at 0x90), in the draft after (x at 0xa4). The `ROUND_MAX`
  ternaries look responsible (replacing one pre-loop ROUND_MAX with a plain value moves x's slot).
  Dead ends: x in a nested block anywhere; inlining x/tmp2; moving `a = 1024.0f / arg5`, `tmp = 0xC`
  or the x/tmp2/spE8 statements; tmp2/x decl order; operand order; (s16) casts; a loop copy of x.
  `tmp` and `temp_ft0` are real copies. Reference: matched func_8340144C (frag43) is a simpler
  version of the same loop. The farm's output-51 had the same body as base.c (no hint). spill-slot ordering / one slot off; see draft comments. Lesson from
  func_82F10BB4's match: frame too big with identical offsets ⇒ too many named locals — turn an
  induction variable `v += k` into `base + i*k` (IDO strength-reduces it back).

### Shared pattern: gDisplayListHead in a register (frag6 func_860005B8, frag7 func_86100C30)
- **Round 6 (agent 6): ROOT CAUSE FOUND, match needs a linker alias - DECISION PENDING.** IDO keeps
  one register range per global SYMBOL. Because the top block uses `gDisplayListHead`, the end
  block's uses belong to the same range, which gets split for the top block and dropped. An end
  block that uses a DIFFERENT symbol gets its own range and compiles exactly like the target
  (`lui/addiu a3` before the `bnez`, then `lw v1,0(a3)` / `sw 0(a3)`); confirmed in a standalone IDO
  test and in both functions. No C form of the same symbol does it (casts/puns, `&head[0]`,
  block-scope extern, local `Gfx** p` in any placement; `(*(Gfx* volatile*)&gDisplayListHead)++`
  gives the shape but regs t5/v0). The agent's match adds `extern Gfx* D_800A7420;` plus
  `D_800A7420 = gDisplayListHead;` in undefined_syms.ld and uses the alias in the end blocks; ROM
  byte-identical. The repo has no other symbol aliases, so this is kept on branch
  `round6-gfxhead-alias` (commits 7c03eb6, 204a7de) and NOT merged until the owner decides.
  Also found: frag7's two UNUSED struct copies used the wrong source symbols
  (`sp60 = D_86104B5C; sp5C = D_86104B60;` is right; the old form differed by 2 ROM bytes).
  gDisplayListHead is a standalone bss at 0x800A7420 (first symbol of 6A40), used by 114 files, so a
  struct-field access through another base is not an available explanation.
- Final `if (arg0 == 0) { gSPDisplayList(gDisplayListHead++, ...) }` — target hoists
  `&gDisplayListHead` into a3. Bisection proved the end block compiles right on its own; it only goes
  wrong because the EARLIER `if (arg0 != 0) { gSPDisplayList; gDPSetEnvColor; loop; gSPDisplayList }`
  block also uses gDisplayListHead. Fix must change how the top block's accesses look to IDO, not the
  end block. Dead ends: ~15 end-block rewrites (local Gfx*, &head[0], switch, if(1){}), Gfx** alias for
  the top macros (303/573). `lw t4,0x34(sp)` there is the switch's saved copy of arg0, not a local.

### Blocked on data/bss layout (function statics)
- **func_86A013C8** (frag16_158A00): code is byte-identical with in-function `static char** D_86A06218`,
  but IDO places it at bss 0x90/0x94, target 0xA8. In small tests IDO lays bss out in plain source
  order (function statics where their function sits), but in the real file the static's position
  moves when *other functions* are deleted (→ 0x84, 0x80, 0x68): order depends on which statics get
  referenced where (symbol-table/bucket or reference order — unconfirmed). Next step: `cc -S` and read
  the `.lcomm`/`.comm` directive order. The `pad_*` arrays in the file are splat filler, not original
  vars. D_86A06210/11 can't become static (extern in fragment16.h, used by 15A2B0.c).
  Don't break func_86A01490 (matched via file-scope D_86A0621C).
- **func_81207DF8**: MATCHED 2026-10-16 after the fragment1_data_8E3E0 migration. Recipe: the in-function
  static is initialized (`static s32 D_8120EB6C = 0;` -> .data, not .bss) and IDO emits function statics
  in source order with the file's other data, so the data after its slot is defined below the function.
- **func_81209374** (frag1_86CB0, 225): same recipe puts `static u32 D_8122869C = 0` in its real slot (the
  #else branch defines the global for the asm build). Left: t6-t9 rotation from the numSamples reload in the
  unrolled loop remainder; 10 loop-shape variants did not move it. Farm.
  Farm 2026-10-16: `(unsigned long long)` (or s64/u64) cast on the `out[i * 2 + 1]` store -> 65 (verified with
  fd.sh via matching_notes/try_candidate.py); s32/u32/s16/s8/long casts, sum/diff temps, swapped stores do not.
- **func_81209078** (320): `if (bufPtr) {}` is load-bearing (removing it ~4000). `+=` on the last
  D_812346F4 store fixes the base register but swaps addu operands (330). Dead ends in the draft comment. Farm.

### Large / far off (need real work)
- Not yet attempted seriously: func_8437B0CC (3345 instr), func_84362084 (1597), func_8120572C (1449),
   func_88805AEC (945), func_88203ED8, func_88201488,
  func_86803C6C, func_86905734, func_8130337C, func_885065E0, func_88500A74, func_88304850,
  func_88305F28, func_88807D04, func_80012870 (one store scheduled 1 instr early), func_80034348,
  func_80041A98.

## Handoff (2026-10-07)
Work plan for the next rounds is in `PLAN.md` (tiers, agent protocol, Palmetto hardware recipe).
Cluster helpers: `palmetto_job.sh` (sbatch: stage repo to /local_scratch, verify build, run
permuter farm on tier-1 functions) and `permuter_farm.sh` (parallel permuter runs re-seeded from
the current drafts, best candidates synced to /scratch/$USER/permuter_best).

## Parked for the owner (2026-10-16 night)
- func_86A013C8: matched on branch `round8-86A013C8-labels` (f793ca9 picked there; agent-7 verified the full
  make OK in its worktree). IDO emits .lcomm (bss) in symbol-table hash order; the original
  needed ~7+ extra symbols before the function, supplied there by eight unused labels in func_86A00ED8.
  No code change, but the labels are a stand-in. Same kind of decision as the gDisplayListHead alias pair.

## Round 8 (2026-10-16 night, 12 Opus agents in two passes + farm + Phase D)
Code 96.40% -> 96.60% (progress.py). 29 -> 12 functions open. Matched and integrated (ROM OK):
func_81207DF8, func_80033D44, func_8850B2D4, func_8437FD74, func_838043F8, func_88500A74 (the last
three were permuter zeros from 10-07/10-10 that were never adopted: always scan permuter_best for
zeros, matching_notes/adopt_candidate.py), func_82F04604, func_8130337C, func_81209078, func_8820BE14,
func_84302658, func_80012870, func_86803C6C, func_83501718, func_88807D04, func_81209374,
func_8430506C. Parked on branches: func_86A013C8 (round8-86A013C8-labels), the gDisplayListHead pair.
Open, all register allocation with drafts much closer (scores without -s):
func_8004A474 30 (one register: tail value a2 vs t1), func_84367660 85, func_8004A89C 955,
func_80049DF0 975, func_86905734 1386, func_80034348 2582, func_88304850 3364, func_88805AEC 4687,
func_8437B0CC 7934. Each draft's // comment has the model of what still differs and the dead ends.
Farm (tags p2 GB APU, q 86905734, r 88805AEC/88304850, s 84367660, j 80034348) keeps running.
Tools added: adopt_candidate.py, try_candidate.py, ccs.py (cc -S for one function), datamig.py,
phased_job.sh; agent_setup.sh now links assets/.
Round 8 late passes (01:45-04:45): matched func_8004A474, func_84367660 (agent-13, uopt copy-propagation
model in IDO_TRICKS.md), func_80049DF0 (agent-14). Open (non-parked) at 04:45, scores without -s:
func_8004A89C 345, func_80034348 705, func_86905734 1386, func_88304850 2834, func_88805AEC 4600,
func_8437B0CC 7809. Farm jobs v (8004A89C, 80034348) and w (86905734, 88304850, 88805AEC), 10 h.

## Round 9 (2026-10-17 morning)
F1 harvest (integrator, farm v/w candidates; all real scores = diff.py WITHOUT -s, --max-lines 30000,
forced rebuilds - see the NFS lesson below): no score-0 candidates (the func_80049DF0__t1/t2/t3 zeros
predate its round-8 match). Drafts improved by carrying the farm leads in as plausible C:
- func_88805AEC 4600 -> 3093: `if (!arg1) {}` empty-if boundary after the (arg1+2)/(y5+7) rect in the
  arg6==1 block (farm w1's only load-bearing edit; split-assignment and comma noise did nothing).
- func_88304850 2834 -> 1716: `x0 = arg0 + 0x84` as a named local (decl between color and var_s4,
  assigned BEFORE the var_s6 load, used as both for-inits): x0 now spills to 0x50 as predicted and the
  switch t-rotation fixed itself. Decl position matters (wrong position 3011).
- func_80034348 705 -> 390: `by2 = by` copy used in nx + both nz statements, nz split into
  `nz = (by2 - ay) * (cx - bx); nz = ((bx - ax) * (cy - by2)) - nz;`, AND a dead `cx` reload after
  `len = 120.0f / len;`. All three required together (subsets: 2417-6761).
- func_8004A89C 345 -> 320: explicit `(unk_20 < unk_00) != 0` on the wrap test.
- func_86905734 1386 -> 1355: `cos2 = COSS(arg5)` between spF8[0] and spF0[0] (used only in spF0[0]),
  `w2 = arg3` before the first func_8001E680 (second call's `w2 << 5`), `if (!spF0) {}` after
  gDPSetTexturePersp(G_TP_NONE); all required.
- func_8437B0CC 7809: no farm run exists (round 9 farm adds it).
**NFS stale-object lesson**: var.py/fd.sh scores can be STALE - make on NFS sometimes sees a
just-rewritten .c as older than the .o and skips the rebuild, so a variant scores the PREVIOUS
variant's number (cost an hour on 86905734: a "1355" that was really 2137). Always
`rm -f build/<file>.o && touch src/<file>.c` before trusting a score. draft_score.py-style forced
rebuilds verified all round-9 commits at their recorded scores.
7E0D0 re-check: still waits for func_8004A89C (sole C/asm user of D_8007D4D0/D_8007D4D4); the two
trailing zero floats (7E0D8/7E0DC) are referenced by nothing and are probably this function's 0.0f
literals. Nothing to migrate yet.
Round 9 farm: scancel v/w, fresh job (tag x, COPIES=3) on all six from the improved drafts.



Owner decisions 2026-10-17 (round 9): ACCEPT the gDisplayListHead alias pair (merged
round6-gfxhead-alias, undefined_syms conflict resolved by keeping both sides + D_800A7420) and
ACCEPT func_86A013C8 via the eight unused labels (merged round8-86A013C8-labels); ROM stayed
byte-identical (ed1378bc), 9 -> 6 GLOBAL_ASM, code 96.60% -> 96.78%. FAKE-but-load-bearing C
(`if (x) {}`, dead reloads): try to clean FIRST, only accept if no clean form is found this round.

## Round 9 matches
- func_86905734 MATCHED (agent-3, 8e1aad4): the two arg copies were s32, not f32
  (`s32 a1 = arg1; s32 a2 = arg2;` - uopt keeps the int values in t0/t1 and converts once into the
  0x64/0x5C memory temps), and spF0[0] is the natural rotation `((-h * SINS) + (COSS * -arg4)) + a2`.
  Starts from the round-8 1386 shape; the round-9 F1 farm edits (w2/cos2/empty-if, 1355) grew the
  frame to 0x110 and were reverted. LESSON: a wrong-type local copy can be closer than every
  regalloc trick - check whether a copied variable's TYPE matches how the target uses it.

Round 9 integrator addendum: the -s FALSE ZERO nearly cost func_8004A89C - `value = idx` before the
idx boundary test took fd.sh (with -s, early returns!) to 0, the unwrap shifted the whole ROM 0x10
(ultralib -0x10: the compiled function is 4 instructions short in the tail), and only the full make
caught it. The no-s score at that state was 300 (tail sample/`move t5,a0` rows remain). fd.sh 0 on an
early-return function is meaningless; always draft_score (no -s, uncapped, forced rebuild) before
believing any zero. Restored, kept as draft 300.

## Round 9 close-out (integrator, 2026-10-17 ~10:00)
State: code 97.92%, 5 functions open (FULL scores; see IDO_TRICKS SCORE TRUST RULES):
func_8004A89C 300, func_80034348 60, func_88304850 1716, func_88805AEC 2337, func_8437B0CC 6584.
The 5 Opus agents died on the weekly API limit ~07:45 (resets Oct 19 7pm; worktrees kept clean at
match-round-1 for resuming with SendMessage). Three farm jobs keep exploring (x: 8004A89C/8437B0CC
from node0457, y2: 88304850/88805AEC from node0452, z: 80034348 from node0435; all seeded from the
current drafts after moving the stale saved candidates to permuter_best_backup_20261017 - the
re-seed-from-best-saved mechanism backfires once a draft improves past the saved pool because
permuter scores are not comparable across imports; when a draft improves, move its save dir aside).
KNOWN BAD: the permuter's own scoring RANKING disagrees with the real fd score for
fragment28_2190D0.c (candidates that improve the permuter score real-score WORSE: 20543-base runs
saved 10043-permuter candidates at 9914 real vs the 2337 draft) - cand_score EVERY candidate before
trusting it. For 33FE0.c the z-farm's 105-permuter candidate real-scores 105 (draft is 60) - also
do not trust permuter numbers there.
THREE-TIME LESSON (now in IDO_TRICKS): fd.sh's -s + 1000-line cap shows fantasy scores on
early-return/big functions. The 8437B0CC u64#2 edit looked like 4213 and was actually 10054 (full).
Always: rm the .o, no -s, --max-lines 30000. cand_score.py/draft_score.py do this; var.py now
force-rebuilds but still uses fd.sh for the diff - read its output as CAPPED ONLY.
F5 prep done: 8-branch PR series (up/tools-data2c -> up/main-segment -> up/fragment1 ->
up/fragments-a -> up/fragments-b -> up/fragment62 -> up/frag67-gfxhead-alias ->
up/fragment16-labels), each gated with a standalone make OK; the tip's upstreamable content equals
match-round-1. NOT pushed (owner approval required). Permuter sizeof PR doc unchanged
(UPSTREAM_PR_permuter_sizeof.md). Open follow-ups: decompose matching_notes/func_8437B0CC_best5479.c
(5479 real, paren-grouping + third-u64-AND edits), 80034348's pointer-colour conflict model,
clang-format-vs-.loc tidy trap (line numbers must be preserved when reformatting matched files).

Post-close-out (10:2x): adopted the 8437B0CC farm candidate verbatim (6584 -> 5479, 53f383c) and
started the cleanup bisect. The first cleanup step (removing the candidate's second u64 AND) looked
like 5479 -> 2873 and was committed - that was the CAP ILLUSION in its inverted form (var.py was
still ranking with fd.sh's capped output): the FULL score of the removal is 7809, i.e. the u64 AND
is load-bearing noise. Reverted (ba3b0d6). Hardening so this cannot recur (b5c1cc6 + this commit):
fd.sh = full diff + forced rebuild + a loud "0 is not a match" reminder; var.py = full scoring with
forced rebuild; draft_score.py/cand_score.py promoted into matching_notes (known-state validated:
8437B0CC 5479, 88805AEC draft 2337, y23 candidate 9914); IDO_TRICKS gained a SCORE TRUST RULES
section; PLAN matcher rules updated. 8437B0CC now 5479, cleanup bisect continues from there.

## F6 start (2026-10-17 ~12:40): farms wrapped
Final farm state at wrap: 8437B0CC x1 best 4724 (ADOPTED, 091c6fa); w2 copies (9) seeded from
5349-level reached 4944-5339 (no adoption - worse than 4724); 8004A89C x-runs no improvement over
the adopted 300. All farm jobs cancelled (17519735 x, 17523026/17523027 w2) per the F6 start
condition (single-builder rule). Round-9 open functions parked at: 8004A89C 300, 80034348 60,
88304850 1716, 88805AEC 2337, 8437B0CC 4724. The 8437B0CC lesson (u64 perturbation placement
dominates form, IDO_TRICKS) is the standing lead for the next round / post-API-reset agents.

## F6 test sequence complete (2026-10-17 ~13:45)
rename.py built per rename_spec.md and the mandatory sequence passed in order:
1 no-op (0 changes, gate OK); 2 round-trip tmp_RenameRoundTrip (make OK both ways, empty diff);
3 single (GbAudio_StepNoiseChannel + gGbAudioNoiseChannel + symbol_addrs entry, 19611f0; typedef
fixup cf9fb88); 4 batch of 10 (GB APU channel family, a5ddc79); 5 re-extract invariance in a
scratch copy (/tmp copy): all 12 new names survive make extract (symbol_addrs + dlabels), zero
old-name hits, ROM OK. Tool fixes found by the sequence: header-row parsing, 0x/0X address check,
also-pairs for symbol rows, typedef-row preflight/map checks, dlabel-only symbols need a
symbol_addrs entry ADDED so extraction does not revert the name (the gate caught this live).
Next: Tier A waves, one commit per batch, spot-check + owner approval between batches.

## F6 Tier A complete (2026-10-17 ~16:30)
108 renames applied across 10 gated batches (a1-a10, ROM md5-OK + map cross-check + progress
97.9197% after every batch; expected/ refreshed at wave end - byte-identical, as expected for
ROM-neutral renames). Clusters named: Gen-1 battle math + item/move/species tables (a1), the
message/string core - GetMessageString/Bank, DecompressString, RegisterPlayer (a2), the Gen-1
string codec + name slots + BE I/O (a3), the GB APU driver core (a4/a5), the text/UI rendering
core (a6), the gfx/stage/sound hubs - GfxAlloc/PlaySoundEffect/Stage_*/gCurrentStage (a7), the
state-pool allocator + fragment/asset loading (a8), the scheduler/frame + text state (a9), video
mode + menu input (a10). Tool hardening during the wave: C-static symbols (no symbol_addrs, no
dlabel, no linker-map presence - skipped in the map check), typedef rows, also-pairs for symbol
rows. NOT renamed (deliberate): the species-stats alias triple D_8006FF00/D_80070F84/D_8006FEE8
(overlapping splat views + the partially-named PokemonStats typedef in 22630.h - needs a
consolidation decision); func_80022734 (unknown tier semantics); the 19840.c Fragment loader
family (Tier B: needs per-function call-graph evidence).
Next: Tier B (per-fragment-group sweeps, 50-100 symbols/batch, call graphs + accessmap), then
Tier C (struct fields + locals via dotted-path rows).

## F6 Tier B (2026-10-17 ~13:15)
Tier A closed at 108 renames (a1-a10); Tier B ran 12 more gated batches (b1-b12, 120 symbols;
228 total applied, ledger matching_notes/renames.tsv). Clusters named this wave: the 2D
sprite/clip library (Gfx_DrawTextureRect/FillRect/DrawSprite* family, gClipRect, Text_DrawGlyph),
fragment loaders (Fragment_LoadPersSzp/PresJpeg/Raw/FromArchive* + JpegDecodePres/SzpDecompress),
GB-save block system (Gbs* family + gGbsSaveBanks + Mon_InitFromSaveEntry/WriteToSaveEntry),
game-state handlers (Game_Run* for all 13 dispatcher states + Game_GoToTitle/Game_UpdateInputs),
sticker station (IsStickerStationConnected + command RW), mon-info UI helpers + menu scroll,
matrix stack (Matrix_ResetStack/PushMultiply/PushScale/GetRelative/GetAbsolute + the F420 math
library: Identity/Multiply/Scale/ConvertToMtx/FromSRT/LookAt*/Decompose), graph nodes
(Init/SetCallback/AllocInit/AddChild/RemoveChild/GetNthChild, roots, traversal, quad/scale
rendering), the List container library (List_Init/Append/Insert/RemoveAt/GetCopy/Set), stage
lifecycle (Stage_BeginDisplayList/GetFrameBuffer/ClearScreen/Destroy), Vec3f constructors,
mem_pool_resize_block. Gates never tripped a revert in Tier B; two tool fixes: C-statics
unconditionally excluded from the map check (b3), and the earlier header/no-op fixes.
expected/ refreshed at both wave ends (byte-identical each time - renames are ROM-neutral).
Remaining for the next session: Tier B continuation (30640/3D camera, 2E460 remainder,
per-fragment sweeps 50-100/batch with call graphs), then Tier C (struct fields + locals via
dotted-path rows).

## Round 10 support session (2026-10-17 ~15:00, opencode): farm10 + method search
Pipeline (full docs in the scripts' headers; summary): farm10 = 3 nodes x 21 permuter instances
on the last 5 open functions (job names farm10-a/b/c), sharing permuter_best via distinct
RUN_TAGs (fa/fb/fc), FARM_PHASES=3 x 11 h chains (ends Sunday night). New in
permuter_farm.sh: per-function `func:src:W:C` specs (small funcs want many copies x 2-3
workers, compile-heavy giants few copies x 5-6); mid-run re-seed (a copy trailing its
function's global best — across all copies AND jobs sharing SAVE_DIR — by RESEED_PCT% +
RESEED_ABS points is restarted from that candidate, at most once per RESEED_COOLDOWN, never
the copy holding the best, never in the last RESEED_MIN_LEFT; a global best of 0 stops that
function's other copies); kills/restarts target permuter processes by the
"nonmatchings/<run> " cmdline pattern. Measured again: permuter main caps ~80 it/s; on
contended work1 nodes per-worker compile latency binds, so copies ~= workers per CPU-hour
and only ~30-40 cores/node are effectively used -> scale by nodes, not workers. To hand a
better source to a RUNNING farm: drop permuter_best/<func>/output-<score>-sfN/{source.c,
score.txt} — the next mid-run re-seed or phase restart seeds from it (stack_perm.py --inject
does this).

Method search (fd.sh FULL diffs of each function's best candidate, via try_candidate.py):
- func_80034348 (fd 40): ONE localized v0<->a0 swap, 8 instructions at 0x1090-0x10fc (the best
  candidate already hoists `by = (vertices + ib)->position.base.y;`). One-shot agent or hand
  fix; random permuting rarely flips both register blocks together.
- func_8004A89C (fd ~300): coupled regalloc chains (v0<->a1/a3), small schedule shift at
  0x13cc; permuter territory, wants a FOCUS_DIR run.
- func_88805AEC (fd 1772 at permuter 1228): 28 of 34 diffs are stack; slots shift -4 almost
  everywhere but one shifts +4 => spill-slot ORDER problem, not frame size. Declaration
  surgery is provably useless here: stack_perm.py swept every insert/delete/swap, best move
  costs +112. The fix must reorder CSE discovery (statement order, temps-vs-literals spelling,
  per IDO_TRICKS "Stack layout"), or a FOCUS run on the early statements where the spilled
  CSEs are discovered.
- func_88304850 (fd ~1716): 35 pure regalloc sites; FOCUS candidate.
- func_8437B0CC (fd 4377 at permuter 4347): 28 regalloc + 8 stack.
New tool matching_notes/stack_perm.py: declaration-surgery hill-climb (delete unused locals,
insert s32/s16/u8 padding at any gap, adjacent declaration swaps; early swap-moves had a
dropped-line bug, fixed) scored via try_candidate (~4 s/eval for mid functions, ~2.5 s for the
giant, sequential — it splices the repo file). Applies to named-local-rich frames; useless on
spill-dominated ones (88805AEC). Winner can be written to a FOCUS_DIR or --inject'ed into
permuter_best as a live re-seed.
Ops lessons: `pkill -f <pat>` self-matches the caller's own cmdline (detached targets with
setsid + careful patterns); the rename batches' git add -A sweeps uncommitted working-tree
files into their commits — commit your own work before a wave runs; asm/ is regenerated by
`make extract`, don't census it mid-extract (file counts change by the second).

### Addendum (same evening): scoring during rename waves produces MIRAGES — quarantine protocol
Two false scores today, both measured while a rename wave was applying/extracting on the main
tree: a statement permutation of func_80034348's vertex-load block "scored 0" (really 144 on
the settled tree), and stack_perm's `ins s32 @29` on func_8437B0CC "took 4377 -> 30" (really
6781; the padding insert makes the frame worse). Root cause: fd.sh/try_candidate compare
against asm/ and build/ that the wave is concurrently rewriting, and the splice races the
agents' edits. Protocol that works: (1) `git worktree add` at a settled commit; (2) symlink
.venv/ expected/ etc. but COPY asm/ (the main asm/ is re-extracted by waves — note asm/asm
is a symlink to another mount, ignore it); (3) copy build/; (4) score the KNOWN baseline
first and only trust numbers if the baseline reproduces (40 / 4377 both reproduced in the
quarantine worktree while the main tree churned). Enumeration itself parallelizes cleanly
across clones of the quarantined worktree (~2.5 s/eval each, 8 clones).
Exhaustive result on func_80034348: ALL 1440 safe statement permutations of its vertex-load
block (5 loads + the `if (0) {}` spill trick, pre-ib hoist both ways) score >= 40; the draft's
own order is optimal. The v0<->a0 swap therefore needs a SHAPE change, not an order change —
next lever: named vertex-pointer temps (`ModelVertex* va = vertices + ia;`, the func_80044EA4
recipe), or permuter FOCUS around that block.

### Round 10 addendum 2 (same evening): flag archaeology + diversity/focus deployed
- Compile-flag archaeology (farm-fetched nonmatchings dirs, flags swapped in compile.sh,
  permuter "base score" as oracle): all five open functions are confirmed -O2. -O1 is
  catastrophic everywhere (40 -> 56063 on func_80034348); -O3 == -O2 on the small ones and
  clearly worse on the big ones. No hidden flag mismatches; that door is closed.
- func_80034348 statement order is optimal in BOTH spaces tried: the 1440 load-block
  permutations AND all 660 valid placements of the anchor statements (ia/ib remap reads,
  the hoisted by-load, `if (0) {}`, the ic read) among the fixed load sequence. Nothing
  beats 40; the fix must change expression shape (pointer temps) or spelling, not order.
- permuter_farm.sh now ALSO does diversity seeding (DIVERSITY=1 default, 0 disables): copies
  past the first start from the k-th best DISTINCT saved candidate (ties count as separate
  basins, content-identical duplicates skipped) instead of everyone on the global best;
  mid-run re-seed still pulls a copy over once it trails by RESEED_PCT/RESEED_ABS.
  FOCUS_DIR now defaults to matching_notes/focus/ — dropping <func>.c there opts that
  function into a focused start at the next farm phase; focus/func_88805AEC.c wraps the
  statements where its spilled CSEs are discovered (validated: standalone permuter run
  improved 31361 -> 30351 in 90 s on 2 workers). Both changes are smoke-tested end-to-end
  (3-copy farm, 3 min, scratch SAVE_DIR) and go live at the phase-2 boundary (~01:00).
- Note: stack_perm.py results are only meaningful in a quarantined worktree; the main-tree
  run through a rename wave produced the mirage above.

### uopt/ugen dump probe (2026-10-17 evening): no debug surface in the recompiled IDO
Goal: see uopt/ugen's register-allocation reasoning directly (why the v0<->a0 pair in
func_80034348 flips). Method: `cc -v` exposes the phase chain — `cfe ... -X<symtab> ... -O2 >
in.B` (ucode, binary), `uopt -v -G 0 -mips2 -EB -g0 -O2 in.B out.B -t symtab tmp`,
`ugen -v ... out.B -o ug.bin -t symtab -temp dir`, `as1 -t5_ll_sc_bug -elf ... ug.bin -o x.o`.
Findings: the recompiled tools have NO dump/trace flags — uopt prints "unrecognized option"
for every unknown single-letter flag (and aborts with no args), ugen silently ignores unknown
flags (byte-identical output for -d/-x/-y/... sweeps), and ltrace shows only USR_LIB /
USR_INCLUDE / _XPG env lookups. Register assignment happens in ugen (its output is a BINARY
intermediate, not asm text — as1 assembles it); the ucode files (in.B/out.B) are binary.
The deep path for seeing allocation decisions is reversing the ucode/ugen formats — a
research project, not an evening. Practical oracles stay: asm-differ on the .o, and the
manual pipeline above (kept at /tmp/opencode/uoptprobe/run_uopt.sh while it lasts) lets you
byte-diff uopt/ugen outputs across source variants as a pre-assembler equivalence check.

## F6 agent waves (2026-10-17 ~14:00-18:00): 1026 renames total
After Tier A (108) + Tier B (120), two parallelization changes took the total to 1026:
(1) gptoss-120b researcher agents via the RCD gateway (matching_notes/rename_agent.py): each
reads one source file and emits ledger proposal rows (old, new, batch, also, justification);
the integrator merges fragments, dedupes, preflights, applies and gates - agents never write
the repo. (2) MERGED BATCHES: one apply/gate cycle per wave regardless of symbol count
(w1: 105, w2: 134, w3: 176, w4: 179) - the gate cost is per-batch, so wave shape is the
throughput lever (wave p was 11 tiny batches for 204; waves w are one gate for 100-180).
Waves: p1-p11 (204, main-segment files), w1 (105: 3D140_2/26820/1C720/2FEA0/6BC0/37370/
1CF30/46680), w2 (134: 4CBC0/4F410/48C60/49790/2E110/3FB0/22630/232C0 + first fragments),
w3 (176: fragments 2,3,10,11,13,14,15,17,23,31,34,37,39,44,47,55), w4 (179: fragments
2,3,11,14,15,17,23,31,34,40,42,45,48,56,59,63).
Agent-output quality controls that mattered: justification >= 15 chars or dropped; dedupe by
old AND new across waves; mis-prefixed func_/D_ rows re-prefixed (agents confuse D_80078FXX
variables with functions); collision-with-applied rows dropped by preflight; asset-VRAM anchors
(D_[0-9A-F]000xxx, e.g. D_3000000, D_2000B40) and dual-source symbols (defined in BOTH
symbol_addrs.txt and linker_scripts/us/undefined_syms.ld, e.g. D_30242C0) are OUT OF SCOPE -
renaming them needs undefined_syms.ld edits, which the spec's never-touch list forbids; the
gate caught both classes (map check) and auto-reverted, which is the system working.
Tool fixes this session: is_c_static + c_definition_count match function-local statics and
multi-dim arrays; field-row struct-prefix protection (farm closure); also-column single-name
fold; terminal ledger rows skipped.
Farm (aa-tag) kept grinding throughout: 88805AEC candidate adopted 2337 -> 1844 (e28cc3d);
80034348 permuter-best 40 (real 40 vs draft 60 - NOT better, permuter scale for this file is
its own; cand_score gate held it out); 8004A89C 290 real = worse than 300; 88304850 1666
(worse than 1716); 8437B0CC 4572 (worse than 4724). Only 88805AEC's adopted.
F6 totals: 1026 renames applied, 22 gated commits + 13 agent-wave commits, ROM byte-identical
after every batch, progress 97.9197% throughout. Next session: wave 5+ on the remaining
~5,700 referenced placeholder symbols (fragment files are the bulk), Tier C struct fields.

## ROUND 10 PICKUP (handoff written 2026-10-17 ~18:00, end of session)
Read PLAN.md section 0 first, then this. Everything below is the current truth.

### Where things stand
- Branch match-round-1, HEAD 341d4fc, tree clean, ROM builds byte-identical (make -> OK),
  progress 97.9197%, 6 GLOBAL_ASM lines: the 5 open functions + (none parked - both parked
  decisions were merged 2026-10-17 morning).
- Open functions (FULL fd scores - no -s, --max-lines 30000, forced rebuild):
  func_8004A89C 300, func_80034348 60, func_88304850 1716, func_88805AEC 1844 (farm candidate
  adopted 17:5x, e28cc3d), func_8437B0CC 4724. Each draft's // comment has the model + dead ends.
- F5 upstream: 8-branch series up/tools-data2c..up/fragment16-labels, all build OK standalone,
  NOTHING pushed (owner approval required per push). UPSTREAM_PR_plan.md has the split;
  UPSTREAM_PR_permuter_sizeof.md the permuter PR. The rename work (F6) should be folded into
  that series before pushing (rename commits are cherry-pickable; ask the owner how to sequence).
- F6: 1026 renames applied (Tier A 108, Tier B 120, agent waves 798). Ledger
  matching_notes/renames.tsv (resumable, applied@<commit> per row). All waves gated: ROM md5-OK,
  map cross-checked, progress unchanged.

### Farm: DEAD since 14:57 Oct 17 (job 17528911 cancelled ~1.5h in - not by an scancel I
remember running; likely fallout from an aborted command block). Pools are CHECKPOINTED in
/scratch/$USER/permuter_best/func_*__aa*/ (best permuter scores: 80034348 40, 8004A89C 290,
8437B0CC 4572, 88304850 1626, 88805AEC 1340 - all real-verified WORSE than current drafts
except 88805AEC which was adopted). To relaunch (single-builder rule means do this when no
rename gate is mid-flight; the farm builds in its own staged copy so it can run alongside
renaming, just not during an in-progress apply):
  sbatch --time=11:00:00 --export=ALL,RUN_TAG=ab,COPIES=3,FUNCS_OVERRIDE="<five funcs>" \
    matching_notes/palmetto_job.sh
Pre-rename pools (pre-gptoss naming) are in permuter_best_backup_20261017/ and
permuter_best_prerename_20261017/ - DO NOT re-seed from those; candidates in them reference
symbol names that no longer exist. The aa pools reference the CURRENT names (post-w4) EXCEPT
the 88805AEC pool (pre-e28cc3d - its best is what we adopted; harmless).

### F6 continuation: the agent-wave recipe (fastest path to readable code)
1. Pick 12-16 fresh files (fragment files without open NON_MATCHING drafts; check
   `grep -l "NON_MATCHING" src/fragments/<n>/*.c`). Done so far: fragments 2,3,10,11,13,14,
   15,17,23,31 (partial),34,37,39,40,41(partial),42,44,45,47,48,55,56,59,63 (partial) +
   most main-segment files. REMAINING main files: 11BA0 remainder, 19840 remainder, 2E460
   remainder, 30640 remainder, 32D10 remainder, 45720 remainder, 46680 remainder, 4CBC0/49790
   remainders, dp_intro remainder, crash_screen, profiler, gb_tower, gb_mbc, rsp, dma,
   heap, geo_layout, jpeg*, util, memory_main.
2. Launch: for each file, `setsid nohup .venv/bin/python3 matching_notes/rename_agent.py
   --file <f> --batch <b> --model gptoss-120b --max 15 --out <dir> &` (8-16 concurrent is
   fine on the gateway; they finish in ~5-8 min each).
3. Salvage: `.venv/bin/python3 matching_notes/rename_salvage.py <batch> '<dir>/<prefix>_*.raw'
   <merged.tsv>` (normalizes literal-\t output, dedupes, drops <15-char justifications).
4. `cat merged.tsv >> matching_notes/renames.tsv` then FIX what preflight flags:
   - mis-prefixed D_ vars written as func_ (agents confuse D_80078FXX): re-prefix the row.
   - new-name collisions with applied rows: drop the later row.
   - asset-VRAM anchors (D_[0-9A-F]000xxx like D_3000000) and dual-source symbols (in BOTH
     symbol_addrs.txt and linker_scripts/us/undefined_syms.ld, e.g. D_30242C0): DROP BOTH
     CLASSES - out of scope (undefined_syms.ld is on the spec's never-touch list).
   Then `.venv/bin/python3 matching_notes/rename.py apply matching_notes/renames.tsv --batch <b>`
   (plan first if paranoid), git add+commit, mark-committed, amend. ONE gate per wave.
5. Wave end: make diff-init (expected/ should stay byte-identical).
Gate costs ~4-6 min regardless of batch size; waves of 100-200 symbols are the sweet spot.

### API / agents
- Anthropic weekly limit resets Oct 19 7pm (America/New_York). After that: agent worktrees
  agent-1..6 are parked clean at match-round-1 for SendMessage resume, OR relaunch the
  round.sh flow (round9_assignments.txt has the file groups).
- RCD gateway (llm.rcd.clemson.edu, key at ~/.config/rcd-llm/api-key - never print it):
  121 models incl. gptoss-120b (used for rename agents), gpt-5.6-*, o3-pro, qwen3.6-35b.
  rename_agent.py is model-agnostic (--model).

### The standing caveats (unchanged, all deliberate)
- SCORE TRUST RULES (IDO_TRICKS): full diff only; permuter numbers never ranked.
- Farm-merge closure (67 symbols in renames_protected.txt + field rows on those structs):
  do not rename until the five open functions match; then harvest, unprotect, rename,
  relaunch farm. Cycle costs one farm restart.
- Species-stats alias triple D_8006FF00/D_80070F84/D_8006FEE8: needs an owner consolidation
  decision (overlapping splat views + partially-named PokemonStats typedef in 22630.h).
- func_80022734 (move-power tier semantics unknown), 19840 loader family (named in b2),
  Tier C struct fields (dotted-path rows; struct prefixes in the closure are protected).

## ROUND 11 PICKUP (handoff written 2026-10-17 ~23:59, end of the rename-execution session)

### What happened tonight
F6 continuation executed per matching_notes/RENAME_PLAN.md (owner-approved: fields-only Tier C,
gptoss-120b bulk, 4-wave review cadence, alias triple consolidated). 2,686 renames applied in
batches w5-w25 + s1 + c1 (ledger total 3,713). Every batch gated: ROM md5-OK, map cross-check,
progress 97.9197% unchanged, expected/ byte-identical at every 4th wave; final make -j24 -> OK,
make diff-init refreshed. Tree clean, branch match-round-1, nothing pushed.

### Tooling hardened this session (all committed, see git log)
- rename.py: hard preflight refusal for undefined_syms.ld-defined symbols (the D_80073267
  class: extern-decl in C + definition in the never-touch .ld; c_definition_count counted
  externs as definitions - the loophole).
- rename.py: C-defined globals with no symbol_addrs entry now get a SIZELESS `defined:true`
  entry added at rename time (map-derived address). Without it, spimdisasm re-derives the old
  placeholder name from fragment relocs at every make extract (the D_800758E0 failure: it
  resurrected in the map through auto/undefined_syms_auto.ld). Splat's .splat/*.csv files are
  pure OUTPUT - scrubbing them does nothing.
- rename.py: field-row declaration rewrite now handles `/* offset */` comments, pointer-typed
  fields (GbEmuState* unk_01D8) and array suffixes; gate failures dump full build output to
  scratch/gate_full.log.
- rename_wave.py: end-to-end wave driver (agents 16x concurrent -> salvage -> fixup ->
  plan/fixup loop -> apply+gate -> commit -> mark-committed -> amend; idempotent re-runs;
  per-batch veto.txt). rename_field_agent.py + rename_field_wave.py: Tier C field renames via
  gpt-5.6-sol (needs max_completion_tokens, no temperature!). rename_agent.py chunks files
  >1200 lines (fragment27/28_214920 sized giants exceed gptoss-120b context; gpt-4.1 worked
  as fallback when gptoss-120b returned empty content late in the night).

### The alias triple is RESOLVED (s1, from the smart-agent analysis)
Two DISJOINT tables, not aliases: gSpeciesDisplayTable (0x8006FF00, 152 rows x 0x1C: pmname
model-name ptr, scale, flags, packed angles - consumed as sprite scale in 1AB70) ends exactly
where gSpeciesBaseStats (0x80070FA0, 152 x 0x17, byte-verified canonical Gen-1 stats, renamed in
p2) begins. D_8006FEE8 is the string "pmname_151"; D_80070F84 is an IDO constant-folded alias
base (gSpeciesBaseStats - 0x1C) - both dual-source, parked forever. unk_D_80070F84 typedef
renamed SpeciesStats (the true 0x17 row type). Follow-ups + evidence in rename_parked.md.

### Still open
1. The 5 open functions (unchanged scores; farm relaunch recipe in ROUND 10 PICKUP; Anthropic
   API resets Oct 19 7pm). The farm-merge closure (67 symbols + protected field rows) unlocks
   when they match.
2. Tier C remainder: shared field names need struct-scoped rows (see rename_parked.md).
3. PokemonStats field rotation + STAT_* define relabel: evidence documented, owner decision.
4. F5 upstream: fold the 40+ rename commits into the up/* series (they are cherry-pickable;
   export-upstream emits the curated subset).

### Session recipe (proven, 2686 renames / ~5h wall, ~0 owner interventions)
`.venv/bin/python3 matching_notes/rename_wave.py run <queue-wave> [count]` - queue in
matching_notes/rename_queue.txt (21 waves + regen via rename_queue_gen.py). Field waves:
`rename_field_wave.py cN <headers...>`. Veto: scratch/rename_waves/<batch>/veto.txt.

### Round 10 morning addendum (2026-10-18, opencode support session)
Farm status at pickup: all three farm10 tracks healthy through phase 2 (a/b chained at
01:31 as jobs 17559397/17559400); overnight permuter bests: 88805AEC 18419 -> 4929
(real fd 4202 via cand_score), 8437B0CC 4724 -> 3882, 88304850 1936 -> 1642,
8004A89C 300 -> 270, 34348 flat at 40 all night (as predicted).

Repo incident + fix: an interrupted `make init` had left `linker_scripts/us/auto/` empty
between 15:00-17:20 on 10-17 — that killed the original farm10-c chain (fresh stagings
rsync the broken tree; the build gate still passes because the build/ copies are complete).
`make extract` repairs it; a/b's phase-2 chain (01:31) staged AFTER the repair and is fine.
Round 11's renames (2686+3713, commits 8490553..de50807) did NOT rename any of the 5 open
functions. If a chained farm phase ever dies in <1 min with "No rule to make target
'build/linker_scripts/us/auto/undefined_syms_auto.ld'", run `make extract` and resubmit.

Morning actions taken (this session):
1. Two one-shot agents (worktrees r10-34348, r10-4a89c; reports in scratch/r10-*/notes.md):
   - func_80034348 NOT matched (still 40). Root cause fully mapped via ccs.py ugen dumps:
     ugen ranks the three vertex-pointer webs (single-block > block-spanning, ties by first
     textual appearance); the draft's structure can never demote vc from v0. The register
     side IS solved in `scratch/r10-34348/m1_candidate.c` (fd 1326, worse schedule) — the
     remaining problem is making the ay/by/bz/az loads EMIT early while sitting in block B
     (comma expressions / statement-emitting macros). Pointer temps: dead end (web order).
   - func_8004A89C NOT matched (best 350, was 300; permuter bests 270). Tail mechanism
     (`move t5,a0` + late `sll t8,t5,0x3`) understood and reproduced structurally; the
     remaining error is ONE regalloc chain: target has no 4th local (sample chain runs on
     temps + value's home a0); getting uopt to propagate the +0x10 assignment is the key
     lever (matched sibling evidence: `dir = duty & 8` propagates, `(u8)(x + c)` doesn't).
     fa4-270 keeps the old tail; 350 keeps the sample local — the naive hybrid is a KNOWN
     450 dead end (spec7 v0). 350 injected as output-350-sf1 (permuter-validated).
2. Farm swap to farm11 (timed script, log /tmp/opencode/farm_swap.log): FUNCS trimmed to
   88805AEC:5:5, 8437B0CC:5:5, 88304850:4:5, 8004A89C:4:6; 34348 dropped. FARM_PHASES=2.
3. Focus files removed (both were stale-draft-based and underperformed plain diversity
   copies overnight); rebuilt-but-unvalidated 88805AEC focus kept in scratch/r10-focus/.
4. Cross-basin recombination: only worth it where basins are KNOWN complementary — for
   88805AEC/8437B0CC the diversity seeding (k-th best distinct starts) already spans
   basins, so no manual splicing. 4A89C handled by the injection above.
5. permuter_best backup refreshed (~/permuter_backup_20261017, 328 MB).

Next session, by value: (1) 34348 comma-expression emission-order experiment from
m1_candidate.c (the whole function is two ideas away); (2) 4A89C uopt +0x10 propagation
ideas from the ranked list in scratch/r10-4a89c/notes.md; (3) harvest farm11 phase results
(morning_check.sh; farm11-c phase 1 ends ~19:20, a/b phase 2 ends ~22:30 tonight); (4) the
agent worktrees hold commits/notes — cherry-pick nothing (no matches), but read their
scratch notes first.

### Round 10b follow-up agents (2026-10-18 ~09:30, worktrees r10b-*)
- **func_8004A89C: 350 -> 330** (new best; committed in worktree r10b-4a89c, c26d7c0..ac23815;
  scratch/r10b-4a89c/source_330.c, injected as permuter_best output-330-sf1, farm-validated).
  The 330 win composes fa4's top tricks with the new tail (do{}while(0) between `if (value) {}`
  and the idx re-read; inline width test `D_800FD008[0x12].value & 8`; exactly three `if (1) {}`
  after the unk_0C store) — idx/col/value/stage coloring now ALL match; remaining is ONE swap:
  ours rowptr-temp=v0 + sample-home=a3 vs target a3/v0. Core mechanism learned: ugen assigns
  local homes first-def-order a0-a3, THEN uopt CSE/copy-propagation frees homes for temps;
  idx propagates because the double NR43 read CSEs into a named temp making `idx = temp` a
  copy. Dead stores cannot reserve homes (uopt DCE runs before ugen). TWO TRAPS for future
  sessions: (a) a disabled NON_MATCHING wrapper makes tools diff the GLOBAL_ASM .o -> 0;
  (b) draft_score/cand_score can print 0 via an NFS stale-.o race — always `rm -f` the .o
  first and demand the full make `: OK`. Also noted: the target emits one extra instruction
  (`move t5,a0`) our C currently lacks — invisible in diff score, would shift the ROM.
  Ranked next steps in scratch/r10b-4a89c/notes.md.
- **func_80034348: follow-up agent died mid-exploration without a report.** Its last edit
  (fd 3416, uncommitted in worktree r10b-34348) is a failed shape — do NOT adopt. The useful
  output is its draft-comment conclusion: the comma-expression / emission-order lead hits a
  DIRECT CONFLICT between the colouring and the pointer-priority constraints (interleaved
  emission order that fixes the schedule breaks the web ranking that fixes registers, and
  vice versa). Its proposed next lead: a struct/tail change that alters what 'single block'
  means for the pointer temps (e.g. -Wo,-doassoc-style grouping of the address math) — i.e.
  change the ADDRESS EXPRESSIONS' association, not the statement order. Best remains fd 40
  (output-40-1); m1_candidate.c still holds the register-solved half.

### Round 10c: permuter metric is DIRECTIONALLY BROKEN for 88805AEC + 88304850 (2026-10-18 ~11:40)
Evidence (cand_score fd vs the permuter's own base scores, same files):
- func_88805AEC: aa3/output-1228-1 (old-metric seed) real fd **1732** (BEST) but permuter 18419
  (draft-level); fb2/output-4929-1 (farm10 phase-2 "improvement") real fd **4202** but permuter 4929.
  The farm has been walking AWAY from the best candidate while improving its score.
- func_88304850: aa1 (fd 1666, best) permuter 1936; fa1 (fd 1822) permuter 1642. Same inversion.
- func_8437B0CC (3882=3882) and func_8004A89C (270/330/350 all exact) are HONEST - unaffected.
Actions taken: farm11-c cancelled mid-phase (it was burning 10 of 21 copies counterproductively
on the two broken functions); farm11-c3 (17572774, RUN_TAG=ge) resubmitted with ONLY the two
honest functions (8437B0CC:5:8, 4A89C:4:8); the 11:50 a/b swap FUNCS file (/tmp/opencode/
farm11_funcs.txt) likewise. 88805AEC + 88304850 stay OFF the farm until this is fixed.
Ruled out: statics inflation (stripped the 11 big static arrays from the aa3 candidate to
externs - still 18419). Diagnostic harness kept: /tmp/opencode/p888 (import of 88805AEC with
stripped-aa3 base.c, permuter prints 18419; ground truth via cand_score = 1732).
Next session should: diff the PERMUTER's own diff (its target.s + scoring) against asm-differ
for the same candidate on these two functions - suspect the imported target/compile context
post-rename-extract (symbol-era). Compare the fresh-import DRAFT's permuter score vs the draft's
fd to see if the import itself is skewed. Until fixed, judge those two functions ONLY by
cand_score/fd.sh, and do not trust farm_status numbers for them.
Ops note: farm11-c2 died in 56s to wave churn (w26's distclean left linker_scripts/us/auto empty
11:24); healed with `make extract`. The 11:50 swap has a tree_ok pre-flight guard (farm_swap2.sh);
if a wave is mid-apply, it waits up to 1h then aborts (leaving a/b to chain untrimmed phase 3).

### Round 10d: michiiik/pokestadium harvest - 2 of 5 open functions MATCHED (2026-10-18 ~15:00)
DISCOVERY: github.com/michiiik/pokestadium (Team Hippodrome; fork of pret, same AI-assisted
last-mile approach, very active) has ALL FIVE of our open functions decompiled. Their US is
100% (7437/7437, zero GLOBAL_ASM; us_rev1/2 also done); their remaining backlog is the other
versions (~17k functions: jp 4552, it 2381, es/fr 2359 each, de 2197, eu_rev1 1891, eu 1281).
They have 5,787 placeholder symbols left in US src. Full clone at /tmp/opencode/hippo (shallow;
their bodies extracted to /tmp/opencode/hippo_bodies/).
OUR side of the trade: the matching industrial base (permuter_farm.sh, corpus.py oracles,
ido_bisect, ccs/regprobe, IDO_TRICKS.md, quarantine protocol, port_agent.py below) + the
rename automation (6,441 applied; waves at 2,400-row scale).
NEW TOOL: matching_notes/port_agent.py - an LLM port loop (RCD gateway, gptoss-120b, unlimited
tokens; usage: --func --src --their <hippo body> --worktree <wt> --rounds N). Round = prompt
(our draft + their reference + best-candidate fd feedback) -> candidate -> try_candidate ->
fd.sh feedback; on fd 0 it unwraps + full-makes. Patched mid-session to feed back the BEST
candidate (models drift away from good attempts otherwise) and to hint that `i` diffs on jal
lines are symbol-name-era mismatches.
RESULTS: func_80034348 MATCHED (2 gateway rounds, adopted, ROM OK - worktree r10b-34348).
func_88805AEC MATCHED (fd 5 = one jal name-era artifact; unwrapped, ROM OK - worktree
r10c-888; its asm was re-extracted inside the worktree to fix era skew). Remaining runs in
/tmp/opencode/portlogs/*_r3.log: func_8004A89C (16 rounds), func_88304850 (16), func_8437B0CC
(16, slow: ~7 min/round for the 1223-line body).
TOOL BUGS FIXED (real, old): try_candidate.py + splice_draft.py used rfind("#ifdef
NON_MATCHING") which matches the LITERAL INSIDE COMMENTS - the r10b-4a89c draft comment
contains it, so every enable inserted #if 1 into the comment, the draft stayed disabled, and
fd.sh scored the GLOBAL_ASM .o = PHANTOM 0s (this is what the round-10b agent warned about;
now line-anchored regex in both tools). adopt_candidate.py still needs the same audit if it
misbehaves; the manual unwrap (splice + keep preamble decls + delete wrapper lines + full
make) is the proven path - see the 88805AEC close above.
INTEGRATOR: the two matches sit UNCOMMITTED in their worktrees; cherry-pick both files onto
match-round-1, run make init to drop the stale nonmatchings .s, re-check progress.py -v us
(should pass 97.92%), full make OK. Attribution: ported from michiiik/pokestadium (Team
Hippodrome) - credit them in the commit messages.
