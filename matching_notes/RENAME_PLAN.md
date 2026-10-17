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
