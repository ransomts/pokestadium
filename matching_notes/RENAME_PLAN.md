# F6 rename sweep - continuation plan (wave 5+ through Tier C)

Written 2026-10-17 evening; owner-approved scope decisions inline. Supersedes the "next session"
paragraphs of NOTES.md ROUND 10 PICKUP for wave shape; the recipe itself (NOTES.md "F6
continuation") stays authoritative. Companion files: rename_spec.md (the spec), renames.tsv
(the ledger), renames_protected.txt (the hard-refused set).

## Owner decisions (2026-10-17)

| Question | Decision |
|---|---|
| Locals in Tier C | NO - fields only (struct fields + unk_ typedefs); locals parked |
| Models | gptoss-120b for bulk waves; smarter models (gpt-5.6-*/o3-pro, sub-agents) for Tier C struct analysis |
| Approval cadence | `--sample 5` spot-check printouts per wave; owner review checkpoint every 4 waves |
| Species-stats alias triple | Consolidate and rename NOW (was parked) |

## Scope (measured 2026-10-17 ~19:00)

| Class | Remaining | Notes |
|---|---|---|
| func_XXXXXXXX | 6,622 in symbol_addrs_code.txt (6,277 referenced in src/) | 726 applied so far |
| D_XXXXXXXX | ~5,496 distinct referenced in src/ | ~1,694 linker symbols + ~3,800 C-statics |
| Struct fields | ~609 | Tier C, dotted-path rows |
| Locals | parked | owner decision above |
| Protected | 5 open functions + 67 farm-closure symbols + field rows on those structs | frozen until the 5 functions match (P4) |

281 files still contain placeholders; minus the 5 NON_MATCHING files -> ~276-file wave queue.
Out of scope forever: VRAM anchors (D_[0-9A-F]000xxx), dual-source symbols (in both
symbol_addrs.txt and linker_scripts/us/undefined_syms.ld), jtbl_*, by-design names,
already-named symbols.

## Phases

### P0 - Preflight + queue (30 min)
1. git clean, make -j24 -> OK, ledger 0 pending.
2. Build matching_notes/rename_queue.txt: src files still containing placeholders, minus the
   5 NON_MATCHING files, main-segment first then fragments in numeric order, ~14 files/wave.

### P1 - Species-stats alias triple consolidation (early)
Region 0x8006FEE8-0x80072AF4: D_8006FEE8 (fake offset symbol into D_8006FF00),
D_8006FF00[152] overlapping D_80070F84 (= &D_8006FF00[151], PokemonStats[], runs into 71BA1),
partial PokemonStats typedef in 22630.h. Analyze (smart-model sub-agent), propose one canonical
owner + reconciled typedef, execute as one gated special batch (may touch symbol_addrs.txt
structure by hand), rename cluster in same or following wave. Ambiguous pieces get parked, not
guessed.

### P2 - Tier B continuation waves (bulk, ~20 waves)
Per wave (recipe NOTES.md "F6 continuation"):
1. 12-16 fresh files from the queue.
2. 16 concurrent: setsid nohup .venv/bin/python3 matching_notes/rename_agent.py --file <f>
   --batch wN --model gptoss-120b --max 15 --out scratch/rename_waves/wN/
3. rename_salvage.py -> merged.tsv -> append renames.tsv.
4. Preflight fixups (automated in the wave driver): re-prefix mis-prefixed rows, drop
   new-name collisions with applied rows, drop VRAM anchors + dual-source symbols; NEW:
   consistency check of proposed names against the applied-ledger vocabulary (align before
   apply - renaming already-applied names is out of scope).
5. rename.py plan (dry) -> apply --batch wN --sample 5 (gate: make, md5-OK, map cross-check,
   progress 97.9197%) -> commit "rename: wave wN (N symbols)" -> mark-committed -> amend.
6. Every 4th wave: make diff-init (expected/ byte-identical) + owner review checkpoint.
~30-45 min/wave; expected yield ~3,000-4,000 renames; weak-evidence symbols accumulate into
the parked report.

### P3 - Tier C struct fields (~609)
Enumerate structs with unk_ fields (exclude protected type prefixes). Batches of 5-10
structs: one smart agent (RCD gpt-5.6-*/o3-pro or Task sub-agent) per struct reads the
struct + all users (accessmap.py optional), proposes the FULL field set as dotted-path rows
(unk_D_800FD008.unk_00:BattleMon.monId). Agents propose only; integrator preflights. Same
gate/commit cycle; field rows rewrite header decls + member accesses only. Consistency
checkpoint per batch across related structs.

### P4 - Farm-merge closure harvest (blocked on the 5 open functions)
Trigger: 5 open functions match (Anthropic reset Oct 19 7pm; farm relaunch recipe in NOTES;
agent worktrees parked). Rename waves proceed meanwhile (farm builds in a staged copy; never
during an in-progress apply; never score during a wave - mirage protocol). On trigger:
harvest/adopt candidates -> unprotect the 67 symbols + protected field rows -> one gated
rename wave -> relaunch farm only if anything remains open.

### P5 - Finish
1. Parked-symbols report: every unrenamed symbol + reason (weak evidence / out-of-scope /
   owner decision); flag func_80022734 (unknown tier semantics) for the owner.
2. Final make diff-init, full make -> OK, progress.py -v us = 97.9197%.
3. Fold rename commits into the up/* series per UPSTREAM_PR_plan.md; export-upstream emits
   the evidence-rich subset as curated name-only PRs. NO PUSH without owner approval.

## Resource mapping (24 cores / 32 GB)
- Gateway agents (gptoss-120b): 16 concurrent, ~5-8 min each; ~0 local CPU (throughput driver).
- Gate builds: make -j24, ~4-6 min/wave (the only heavy local CPU use).
- Smart sub-agents: Tier C, alias-triple analysis, consistency audits; read-only proposals.
- Anthropic API: reserved for matching the 5 open functions (P4 trigger), not renames.

## Invariants (all proven, all unchanged)
Single-builder during gates; one gate + one commit per wave; auto-revert on any gate failure;
protected set enforced by rename.py; out-of-scope classes dropped; expected/ byte-identical at
wave ends; commit your own work BEFORE a wave runs (git add -A sweep hazard); ASCII-only
justifications; ledger resumable at every boundary.

## Round 12 addendum (2026-10-18 midday, same sessions)

Follow-up pass completed: **w26 (2,382 symbols, top-20 concentrated files via --max 100 /
--max-tokens 16384 gptoss-120b, chunked) + h1 (346 symbols, header pass over
fragment62/16/34/23/24.h via file-writing sub-agents)**. Ledger total 6,441 applied.
Remaining distinct placeholders in src/: 6,807. ROM byte-identical, progress 97.9197%.

New tooling during this pass: continuation turns past output caps; one-pass caches in
rename.py (content cache, def classifiers, header tags, asm index, pragma index,
joined grep blob) - 2,400-row batches went from timing out to minutes; the remaining
slow path is the per-row rewrite_word scan (O(rows x repo text) ~50 min at w26 scale;
batch into one alternation-regex pass if waves get bigger).

Cross-session: the farm/matching session (farm11) runs concurrently; its uncommitted
NOTES.md/focus work is left alone (driver commits only rename outputs). Messages:
/tmp/opencode/FROM_RENAME_SESSION.md. farm11-c pools saved pre-w26 reference old names;
farm11-a/b (submitted after w26) import post-rename source cleanly.

## Round 12 final addendum (2026-10-18 ~20:40)

Post-resume batches: w27 (1,479) + w28 (1,100) + w29 (463) + w30 (219) + **hp1 (1,438:
michiiik/pokestadium cross-reference - deterministic address join against Team Hippodrome's
complete decomp of the same ROM; generator matching_notes/rename_hippo_gen.py; their clone
at /tmp/opencode/hippo, re-clone shallow from github)** + c2 (61 struct fields).
**Ledger total: 11,201 applied; 2,306 placeholders remain in src/.**

Pipeline speed (user question "make it faster"):
- batched single-pass rewrites + post-checks: 300-row apply 237s -> 27s; -j24 gate;
  batched map check. Waves of 1,000-1,500 rows now ~10-12 min end-to-end.
- openweight models (user directive: unlimited tokens): benchmarked on
  fragment62_32B680.c --max 100: gpt-4.1 112 rows/47s (proprietary, metered);
  **gemma-4-31b 116 rows/2m46s (chosen)**; qwen3.6-35b-a3b 116/4m57s; qwen3.6-27b
  117/15m42s; gptoss-120b 64/2m14s; glm-5.3 starved at 16k tokens.
- the REAL accelerator was the michiiik cross-reference: no LLM, one gate cycle, 1,438 rows.
- reasoning models (gpt-5.6-*) need max_completion_tokens + no temperature.

Bug ledger this stretch: batched header-decl member rewrite dropped semicolons (c2);
has_c_definition vs extern declarations (w29 phantoms); farm-merge closure LIFTED (all
five functions matched - 9b0aa38, code complete); progress expectation now 98.8837.
Cross-session incidents: e7dfcab swept w29's files mid-flight (marked applied@e7dfcab);
w29's first gate failure was a concurrent-make collision (their fd.sh builds in the main
tree) - the gate self-heals on retry.

Remaining 2,306: mostly C statics in fragment files (their tree is semantically
reorganized - a statics cross-ref needs structural matching, not worth it), the
michiiik-nameless overlap (~498), undefined_syms.ld-blocked (~530), weak evidence.
Next: another LLM wave pass on the tail, Tier C shared-name field scoping (pycparser),
and the F5 upstream fold (rename commits are cherry-pickable; credit Team Hippodrome for
hp1 rows in PRs).

## PIVOT (owner decision, 2026-10-18 ~21:10): michiiik is the target, not pret

pret/pokestadium is no longer the upstream; michiiik/pokestadium (Team Hippodrome) is.
What was done immediately:
- ma1: 5,139 alignment renames - michiiik's name replaces ours wherever we diverged
  (of 5,175 divergent; 36 dropped as collisions/vetoes). Ledger total: 16,340.
  NOTE: a few of their names are narrower than ours (e.g. our GetItemName -> their
  Text_GetTmHmName for func_80021CE0) - reversal is one ledger row if the owner wants.
- The pret F5/up-* PR series is DEAD. Future contributions go TO michiiik: our value
  is the rename automation + matching tooling + the 4,550 symbols we named that they
  have not + the other-version (jp/it/es/fr/de/eu) backlog.
- The other session was notified (/tmp/opencode/FROM_RENAME_SESSION.md).

## Next: the semantic reorg (staged, ready to execute)

Goal: adopt michiiik's tree layout. Everything needed is in place:
1. matching_notes/hippo_file_map.md - the address-join map (288/304 files 1:1;
   13 splits listed at the bottom; 1 of theirs spans several of ours).
2. Reorg recipe per fragment group, gated: rewrite the yaml subsegment paths
   (fragments/N/fragmentN_XXXX -> fragments/<semantic>/<name> per the map) + git mv
   the .c/.h + fix #includes (check the include style first: flat vs path-qualified)
   + make extract + full make OK + re-extract invariance + diff-init. One commit per
   group, ~15-30 gated batches. Reuse rename.py's gate discipline; the ROM is the
   safety net (byte-identical through everything).
3. After the reorg: file-level diffs against michiiik become meaningful - the nameless
   2,306 tail (statics etc.) can then cross-reference their SRC directly
   (their tree at /tmp/opencode/hippo or re-clone shallow).
4. Tier C shared-name field scoping (pycparser) remains open, unchanged.

## Reorg execution state (2026-10-18 23:50 handoff)

DONE: 23 gated reorg commits (pilot 16->credits + 21 batch commits; groups 9-15, 17-60,
62-76 as yaml joins allowed). ROM byte-identical, full make OK at HEAD (3e53b9db).
Tooling: matching_notes/reorg.py (apply/plan per group) + reorg_batch.py (batch driver,
bisect-on-failure, skips problem groups). File+header moves + include rewrites + yaml
path rewrites incl. dict-form bss entries and relocs segments.

REMAINING for the next session:
1. Residual `fragments/N/` yaml entries per group (grep yamls/us/rom.yaml): the moves
   and gates passed, but each group has some un-joined subsegment entries left at old
   paths - a consistent class; inspect one group (e.g. 16 post-commit) to identify the
   entry kinds that never join and extend join_group.
2. Isolated gate failures: groups 5, 6, 7, 8, 61 (apply ok, gate failed) - investigate
   individually; likely the same residual-class root cause.
3. Skipped problem groups (join problems): 1, 31, 77 (and 16's residuals).
4. The main segment (src/*.c hex names -> semantic, 113 files, 18 join problems).
5. rev1: 95 OURS-BETTER reversion rows in matching_notes/hippo_name_conflicts.md -
   append to ledger + apply when no reorg gate is mid-flight.
6. 21 re-resolvable name collisions (report has the list).

## Placeholder continuation (2026-10-19 morning)

rev1 applied+committed (22ea8a0d, 95 ours-better reversions; ledger 16,435). Remaining
placeholders ~2,306, overwhelmingly C statics.

NEXT BIG LEVER - the statics cross-reference (now unlocked by the reorg): our files sit
on michiiik's exact paths, so BUILD THEIR TREE (re-clone shallow to /tmp/opencode/hippo -
/tmp gets cleaned overnight; symlink our baseroms/us/baserom.z64 into theirs; check
their build system - pret-style make with their own tools/ido) and use THEIR
build/pokestadium-us.map as {address: name} for THEIR statics (file-scope statics appear
in maps as local symbols). Our map has the same addresses for the same ROM -> a
deterministic address join renames our placeholder statics (incl. D_-named ones the LLM
waves skipped). Then: LLM/gemma tail pass for whatever remains + the reorg residual
cleanup (failed groups 5/6/7/8/61, problem groups 1/31/77, main segment).

## Statics cross-ref attempt (2026-10-19 midday)
Re-cloned hippo (symlinked our baserom + reused our .venv python + our tools/ido) - their
build FAILS with our toolchain (6 errors, see /tmp/opencode/hippo_build.log; likely an
IDO/binutils version pin - check their ci/ config or ask them). Next session options:
fix the toolchain match, or fall back to gemma LLM waves for the statics tail.

## Toolchain-pin findings (2026-10-19 evening, read-only while waves run)
Fresh shallow clone at /tmp/opencode/hippo (old one + hippo_build.log were /tmp-cleaned).
Compared against our tree - the "version pin" is NOT IDO and NOT python deps:
- IDO: BOTH trees ship tools/ido/linux/{5.3,7.1} (CC=7.1, CC_OLD=5.3 for ultralib).
- requirements.txt: identical.
- Their CI (ci/Dockerfile): debian:bookworm-slim + binutils-mips-linux-gnu (~2.40);
  our node has ~/local/bin mips-linux-gnu-* 2.42. Prime suspect for the 6 errors.
- Their Makefile defaults that differ from ours: RUN_CC_CHECK=1 (host gcc syntax check),
  KEEP_MDEBUG=1, COMPARE=1; ultralib sub-build passes COMPARE=0 + IDO_PREPROCESS
  (windows-only) on top of our FIXUPS=1 CROSS=... shape.
- No submodules; baseroms/us/baserom.z64 layout identical to ours.
RETRY RECIPE (after the wave driver finishes - never during gates, CPU contention):
cd /tmp/opencode/hippo && ln -sf ~/Code/pokestadium/baseroms/us/baserom.z64 baseroms/us/
make -j24 PYTHON=~/Code/pokestadium/.venv/bin/python3 2>&1 | tee /tmp/opencode/hippo_build.log
Fallbacks by failure class: RUN_CC_CHECK=0 if host-gcc syntax noise; a bookworm-era
binutils-mips-linux-gnu (2.40) in ~/local if 2.42-only assembler behavior trips them;
ask michiiik which binutils they pin if neither.
STATIC-JOIN TOOL READY: matching_notes/rename_hippo_statics_gen.py (batch hs1) - like
hp1 but joins the two trees' LINKER MAPS (file-scope statics appear as local symbols
there, never in symbol_addrs). Our side parsed today: 1,907 map locals, 1,408 still
placeholder-named - the addressable pool. Run it the moment their map exists; smoke-
tested our-side parsing only (their map requires the build above).

## CURRENT STATE (2026-10-19 afternoon, latest)
Statics-tail waves 1-6 RUNNING (driver PID 2131856, gemma-4-31b, log
scratch/rename_waves/driver_statics.log; queue regenerated: 170 files, 13 waves).
Check "committed" lines in the log; run waves 7-13 with the same command if needed.
Open items: michiiik toolchain pin (ask them; then statics address-join), reorg
residuals (groups 5/6/7/8/61, 1/31/77, main segment, un-joined yaml entries),
michiiik-nameless tail after all waves. Ledger 16,435 + wave commits as they land.

CORRECTION: statics waves STOPPED at w5 - post-rewrite check failure (rows pending in
ledger, auto-reverted, no damage). Next session: read the failure block above the STOP
in scratch/rename_waves/driver_statics.log (likely an old-name-still-present or orphan
class specific to statics rows), fix, re-run `run 1 6`.

## w5 failure diagnosis + fix (2026-10-19 evening session)

Root cause (preserved log: scratch/rename_waves/driver_statics_w5fail.log): three
typedef rows (`unk_func_80003680_sp300 -> JpegStreamInfo`, `..._sp90 -> JpegDspTaskData`,
`unk_func_800041C0 -> StorageRange`) carried an agent-filed type annotation
`old:Struct` in the ALSO column. rename.py's do_rewrites applied also-pairs AFTER the
main mapping into the same last-writer-wins word map, so `Struct` clobbered the real
new name - every occurrence of the old typedef became the literal word `Struct`, the
orphan post-check (correctly) failed, and the batch auto-reverted. Repro confirmed via
importlib on the pending rows (word map said `Struct`).

Fixes (both committed before relaunch):
1. rename.py do_rewrites: also-pairs first, main-row word mappings after - the main
   row owns the symbol; annotations can never win a collision again.
2. rename_wave.py fixup: drop also-pairs whose old equals any kept row's main old
   (the `old:Struct` class never reaches the ledger now).

Verified: repro maps all three olds to their intended names; fixup on w5/merged.tsv
yields 54 kept rows with clean also columns; wave-1 agent results all reusable;
make extract + make -j24 green (ROM OK) at HEAD. Relaunch: `run 1 6 --model gemma-4-31b`.

## CURRENT STATE (2026-10-19 evening, latest)
w5-w9 LANDED after the also-pair fix: 766 symbols in 5 gated commits (de0c75fc, 3270c92b,
6637d5ff, 2d22aedb, e22fa23d); diff-init byte-identical at w8. w10 STOPPED on a NEW
annotation-noise class: `typedef:Name` also-pairs (keyword SOURCE instead of `old:Struct`)
rewrote the word `typedef` itself - geo_layout.c compile errors, build gate caught it,
auto-reverted, rows pending. Fixes: also-pair sources are now blocklisted (C keywords +
annotation tokens) at three layers (wave fixup drop / preflight warn / do_rewrites skip);
row always survives with the pair dropped.

NOTE: statics batch tags (w5-w17) COLLIDE with the Oct-17/18 era tags (w1-w30) in the
ledger - benign: select_batch/mark-committed only touch status-'applied' rows, and the
driver's symbol count now keys on exact 'applied' (old-era rows are applied@sha), so
commit messages count only this run's rows. Revert --batch wN must never be used on a
colliding tag (it would invert old+new rows together).

RELAUNCH: `run 6 8` (queue waves 6-13, batches w10-w17) - same gemma-4-31b driver.

## Server-restart recovery (2026-10-19 late evening)
Waves w10-w15 landed (66+71+58+13+113 = 321 symbols; de0c75fc..c54c53b4). The opencode
server restarted MID-w16-apply: rewrite on disk, gate interrupted, rows pending, no
auto-revert (that only fires on gate FAILURE). Recovery: git checkout the 28 dirty
src/include/linker files (asm was clean; matching_notes kept), relaunch `run 12 2` -
the driver's idempotent w16 redo reuses all agent outputs. LESSON: a killed apply leaves
half-state; the re-run path is the recovery path.

## Statics address-join EXECUTED (2026-10-19 late evening) - SMALL yield, plan corrected
michiiik build SOLVED: no toolchain pin. Their tree builds green with our IDO 5.3/7.1 +
binutils 2.42 + our .venv - the earlier failure was a missing `make extract` step, not
a version mismatch (first attempt skipped it; with extract: full build, ROM OK, ~25 min
on a /scratch/tsranso/hippo Slurm job - build off-node, never during gates).
THE JOIN RESULT KILLS THE BIG-LEVER THEORY: of our 1,408 placeholder map locals,
1,030 are PLACEHOLDER-NAMED IN THEIR TREE TOO (their statics tail is as unrenamed as
ours; the "_empty" stub style and func_/D_ placeholders are theirs - we adopted them in
ma1). Join yield: 18 clean deterministic rows, staged at scratch/hs1_rows.tsv
(ParticleGfx_NoopStub3-9, Minigame2SampleViewer_*, GalleryDebugger_*CPak, battle nops,
JigglypuffGame_UpdateEffects). Apply as gated batch hs1 when the waves drain.
=> the statics tail is LLM-wave territory (as w5-w17 have been doing); michiiik has
nothing more to give us for statics. Tool: matching_notes/rename_hippo_statics_gen.py.

## Tier C status (2026-10-19 late evening)
Field cross-ref via michiiik (rename_hippo_field_gen.py): DEAD END - their headers are
also unk_-dominated (deterministic join yields ~12 rows, not worth a batch alone; could
fold into hs1). Real path = smart-subagent analysis: inventory regenerated post-reorg
(258 safe fields / 55 typedefs, matching_notes/rename_fields_inventory.tsv), 11
subagents launched over all 26 headers (scratch/tierc/*.tsv, batch c3). First result:
fragment61 22/22 fields proposed with evidence (RegisteredTeamMenu cursor/repeat/paging
semantics, deck-card ring cache, carousel). Apply gated after w17.
