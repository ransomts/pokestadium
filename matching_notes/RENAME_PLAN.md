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
