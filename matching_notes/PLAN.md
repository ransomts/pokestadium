# Plan to finish the Pokemon Stadium (US) decomp -- handoff for AI agents

Written 2026-10-07 on Palmetto (node2044, branch `match-round-1`). Read this file first, then
`NOTES.md` (per-function state, process lessons) and `IDO_TRICKS.md` (what has worked). Those two
files are the ground truth for per-function details; this file is the work breakdown, the agent
protocol, and the cluster recipe.

## 0. Where the project stands (2026-10-07, end of round 6)

| Item | State |
|---|---|
| Code matched (`progress.py -v us`, "all") | 94.79% (was 93.13% when matching rounds began, 93.95% this morning) |
| Functions still `#pragma GLOBAL_ASM` | 40 (Appendix A has the original 54; rounds 5-6 matched 14) |
| Drafts | 37 of the 40 have an `#ifdef NON_MATCHING` draft with a `//` state comment; 3 have none (func_8120572C, func_80045FF0, func_80049DF0/func_8004A474 share a file with one draft) |
| Parked | func_860005B8 + func_86100C30: byte-identical only via a linker alias, branch `round6-gfxhead-alias`, owner decision pending |
| ROM | builds byte-identical (`make` -> `OK`) on `match-round-1` (local branch, never pushed) |
| Data still in asm (`asm/us/data/**/*.s`) | 184 files, 2.3 MB, mostly one .data + one .rodata stub per fragment; fragments/1 has 12 |
| Hand-written asm by design | `boot`, `entry`, `libleo/bootstrap` (yaml `asm`/`hasm` segments) - not "undecompiled" |
| Permuter farm | job 16781081, 8 open tier-2 functions, 3-day limit, candidates in `/scratch/$USER/permuter_best` |
| Tooling (2026-10-07) | corpus.py (idiom search, near, siblings), accessmap.py, symcheck.py, ido_bisect.py, round.sh; permuter `sizeof` parse fix (patch + PR draft) |

What rounds 5-6 taught (see NOTES.md and IDO_TRICKS.md): the remaining code falls into three kinds
of problem, and each needs a different tool. (1) One compiler temp whose creation point we cannot
steer: brute force (farm) + occasional insight. (2) A wrong premise in the draft - wrong struct
type, wrong symbol, a cursor local the compiler owned, a nested loop that was one loop: insight only,
and this is where every big win came from. (3) Data/bss layout: needs data migration, not matching.

## Roadmap

| Phase | Scope | Who | Wall time (est.) | Exit criterion |
|---|---|---|---|---|
| A (now) | farm on the 8 open tier-2 functions; owner decides the alias pair | farm job + owner | runs 3 days unattended | candidates validated with fd.sh, or farm stopped |
| B | round 7-9: tier 4 structural functions (26) in subsystem groups | 8 Opus agents/round, 3.5 h time-box | 3 rounds, ~1 day each incl. integration | <= 10 functions left, all with a precise "what is wrong" model |
| C | tier 3 data-layout blockers (4) + the fragment1/16 data migration they need | 2 agents, long session | 1 round | 4 functions matched or proven to need upstream changes |
| D | Layer 2: migrate the 184 asm data files to C | 4-6 Sonnet agents, mechanical, build gate | 1-2 days | `asm/us/data` empty, ROM OK |
| E | finish: scaffolding removal, squash/rebase, PR to master, upstream permuter PR, final docs | 1 agent + owner | half a day | PR open, `progress.py` 100% code |

Rounds 5-6 ran 12-15 functions per round with 6-8 agents and matched 9 and 5. Tier 4 functions are
bigger and need real reverse engineering, so expect 3-6 matches per round, not 9.

### Phase B detail: tier-4 groups (one agent per row unless noted)
| Group | Functions (instr) | Notes |
|---|---|---|
| GB APU emulator, `src/4A3E0.c` | func_80049DF0 (417), func_8004A474 (266), func_8004A89C (256, draft ~170/256) | Transfer Pak Game Boy sound; D_800FD008 = {value, dirty} byte pairs. Fix the struct missing `;` (`char unk2D[0x13]`) first. One agent, 3.5 h, write the two missing drafts from the matched one. |
| Model/vertex, `src/33FE0.c` | func_80033D44 (326, struct type probably wrong - fields shifted by one), func_80034348 (311) | Siblings func_80034824/func_80034BD4 matched this week - reuse their shapes and the file's structs. |
| fragment23 cluster | func_88209B54 (1190), func_8820BE14 (447), func_88216000 (629), func_88203ED8 (825), func_88201488 (582) | 3 agents: {88209B54}, {8820BE14, 88216000}, {88203ED8, 88201488}. 88216000's load-block DXT is computed at runtime -> a custom/expanded texture-load macro; find it in the file's other matched functions. |
| fragment24 + 26 | func_88304850 (590), func_88305F28 (391); func_885065E0 (391), func_88500A74 (240) | 2 agents, one per fragment (shared helpers inside each). |
| fragment28 | func_88805AEC (945), func_88807D04 (275) | 1 agent. |
| Singles | func_86803C6C (639), func_86905734 (508), func_8130337C (553), func_80041A98 (118), func_80012870 (60: one store scheduled early) | 2 agents: {86803C6C, 80041A98, 80012870}, {86905734, 8130337C}. |
| Giants | func_8437B0CC (3346), func_84362084 (1598), func_8120572C (1450, no draft), func_810010BC (965), func_80045FF0 (960, no draft) | One agent each, full 3.5 h, deliverable may be "structure right, score X" + draft. Consider a Fable agent only for 8437B0CC if two Opus passes stall. |

### Phase C detail: data-layout blockers
- func_86A013C8 (frag16_158A00): code byte-identical with an in-function static; IDO places it at
  bss 0x90/0x94, target 0xA8. Do the `cc -S` experiment (read `.lcomm/.comm` order) to learn the
  rule, then either reorder statics or migrate the file's bss to C.
- func_81207DF8, func_81209374, func_81209078 (frag1_86CB0): match with a mid-.data static;
  D_8120EB94 is not 16-aligned, so the split means migrating ~100 KB of sample data to C with
  `tools/data2c.py`. This is the first real Phase D task; do it here and reuse the recipe.

### Phase D detail: data migration recipe (mechanical, cheap model is fine)
1. Pick a fragment; `ls asm/us/data/fragments/N/` (usually `*.data.s` + `*.rodata.s`).
2. Generate C with `tools/data2c.py` / `tools/print_decls.py`; place at the right spot in the C
   file (order = address order); rodata literals go next to the functions that use them.
3. Change the yaml segment from `.data`/`.rodata` asm to the C file; `make extract`-free rebuild;
   `make` must print `OK`. Commit per fragment.
4. Gate for an agent: never commit unless `OK`; never touch src/ of a function another agent owns.
Start with fragments/1 (12 files, biggest) only after Phase C has done its sample-data part.

### Phase E detail: definition of done
- `grep -rn GLOBAL_ASM src` is empty (or lists only owner-accepted exceptions with a comment).
- `asm/us/data` empty; `asm/us/nonmatchings` empty; `#ifdef NON_MATCHING` scaffolding gone.
- `make clean && make -j` -> `OK`; `progress.py -v us` code 100%.
- `match-round-1` rebased/squashed onto `master` and pushed; PR opened.
- decomp-permuter PR filed from `UPSTREAM_PR_permuter_sizeof.md`.
- NOTES.md trimmed to lessons (IDO_TRICKS.md) + a short history.

### Decisions the owner must make
1. The gDisplayListHead linker alias (two functions). Recommendation: keep parked; revisit if Phase D
   reveals how the original declared the variable in overlays.
2. Model per phase: Opus 5.5 for matching (proven, 2.5x cheaper than Fable), Sonnet 5.5 for Phase D
   (mechanical, build-gated), Fable only for a stalled giant. The integrator session can be Opus too.
3. Whether to accept "unsequenced but matching" C (func_87804320's loop tail) or mark such lines.

## 1. Environment recipe (Palmetto, RHEL8, no sudo)

Everything below already works on the login/interactive nodes under `~/Code/pokestadium`.

- Python: `python3.12 -m venv .venv`; `pip install -r requirements.txt m2c cxxfilt
  python-Levenshtein ansiwrap pycparser toml`.
- MIPS binutils 2.42 built from source into `~/local/bin` (`--target=mips-linux-gnu`).
- IDO 7.1/5.3 are the native x86-64 recomp binaries in `tools/ido/linux/` -- no qemu, single
  threaded, ~0.3-0.5 s CPU per compile.
- Build: `env PATH=$PWD/.venv/bin:$HOME/local/bin:$PATH make -j<N>` -> must print
  `build/pokestadium-us.z64: OK`. One object: `make build/src/<path>.o` (~2.6 s wall on the current
  node, almost all of it make + asm-processor Python overhead, not IDO).
- Diff one function: `matching_notes/fd.sh src/<file>.c func_XXXXXXXX` (uses
  `tools/asm-differ/diff.py`; the repo-root `diff.py` is broken on 3.12).
- Batch variants: `matching_notes/var.py src/<file>.c func_X specfile` (see `scratch/*.spec`).
- **Corpus lookup** (`matching_notes/corpus.py`, built 2026-10-07): an index of all 7396 matched
  functions' asm paired with their C, with per-instruction C line numbers from the objects' debug
  info. `corpus.py build` (20 s, writes build/corpus/index.json, 26 MB; rebuild after each round),
  `corpus.py near FUNC --draft` (compiles the draft in a scratch copy, finds each diff region, shows
  the draft C line that emitted it and matched functions containing the same idiom with THEIR C),
  `corpus.py search '<regex over normalized asm>' --c` (e.g. `'beqzl .*\n.*lui'`), `corpus.py show
  FUNC`, `corpus.py selftest`. Register classes are normalized (t/s/a/v/f); end immediates with `$`.
- **Siblings** (`corpus.py siblings FUNC`, `--all-unmatched`): weighted n-gram similarity of an unmatched
  function to every matched one; STRONG >= 0.45 means a matched function contains most of it.
  Table for the current 40 saved as `matching_notes/SIBLINGS_2026-10-07.txt` (func_88216000 is a
  0.997 copy of func_88507DBC; func_86905734 0.77 of func_86905F24; six more STRONG).
- **Access map** (`matching_notes/accessmap.py FUNC [--base a0] [--struct NAME] [--draft]`): per-base
  tables of every memory access in the TARGET asm (offset, stride, width, sign, R/W, value origin),
  overlaid on a declared struct with NO-FIELD/WIDTH/SIGN verdicts and a shift test; `--draft`
  compiles the draft and diffs target-vs-draft accesses ("DRAFT STORES SHIFTED BY +4"). Run it first
  on any draft suspected of a wrong struct or wrong field width.
- **Symbol check** (`matching_notes/symcheck.py FUNC | --all`): flags references that are really
  offsets into a neighbouring symbol (negative addends, past-the-end, `alias`), with suggested
  rewrites like `D_86A03D40[i][j - 6]`; `--all` is clean on the current 40, so run it on NEW drafts
  (e.g. the four no-draft functions once drafted) and after any symbol/yaml change.
- **Round driver** (`matching_notes/round.sh start|status|integrate|finish|farm-list`): worktrees +
  PROMPT.md per agent from `round_prompt_template.md` (matcher rules pulled live from this file,
  NOTES entries per function), integration in commit order with `#if 1` and build gates, stale-.s
  cleanup only when no worktree remains, parking of unmerged work. Assignments file format:
  `agent-k: func_A@score:src/a.c func_B:src/b.c`.
- **Pass bisection** (`matching_notes/ido_bisect.py`, built 2026-10-07): rebuilds a draft with each of
  ~30 IDO optimizer switches (uopt/ugen/as1, e.g. `-Wo,-nordstore`, `-Wo,-no_const_in_reg`,
  `-Wo,-doassoc`, `-Wb,-nobopt`) in a scratch mirror and tables which diff lines vanish/appear per
  switch, with stack slot maps. `ido_bisect.py src/<file>.c func_X` (~45 s), `--only <switch>` for the
  full diff, `--list` for the catalogue. IDO has no standalone CSE/strength-reduction switch; the
  address-in-register switches (`nordstore`, `nokpicopt`, `no_const_in_reg`) are the useful probes
  for stray temps, `doassoc` for FPU/arith grouping, as1 switches for scheduling and branch-likely.
- Permuter: `tools/permuter/` (decomp-permuter, gitignored, upstream 059609d). On a fresh clone apply
  `matching_notes/permuter_sizeof_prec.patch` (fixes `sizeof(T) * N` being parsed as a cast; delete
  `perm_pycparser/yacctab.py` afterwards so PLY regenerates it). Import + run via
  `matching_notes/permuter_farm.sh` (Section 5).
- Outbound internet from compute nodes works (api.anthropic.com answers). `claude` CLI 2.1.292 is
  in `~/.local/bin`. `~/.claude` lives on shared home, so auth persists across nodes.
- Filesystems: `~` is NFS (slow for many small files). `/local_scratch` (= `$TMPDIR` = `/tmp`,
  2.8 TB local SSD per node) is where worktrees, `build/`, and permuter output should live.
  `/scratch` (500 TB parallel FS) is fine for results that must outlive the job.

## 2. Hardware: what actually makes this fast

Two different workloads, with different bottlenecks:

**(a) LLM agents (Claude Code sessions) doing insight-driven matching.** Bottleneck is model
latency and API throughput, not the node. Local footprint per agent: ~1 GB RAM, ~1 core in bursts
(each `make <obj>` is one IDO + one Python process for ~2-3 s), a private worktree + `build/`
copy (~140 MB). 12 agents fit comfortably in 16 cores / 32 GB. Faster single-thread CPU shortens
each build-diff cycle from ~2.6 s to ~1.2 s, which matters because an agent runs hundreds of
cycles per function.

**(b) decomp-permuter.** One IDO compile per iteration, embarrassingly parallel (`-j N`), scales
linearly with cores, ~100-200 MB RAM per worker. This is the only part that benefits from a big
node. Caveat from NOTES.md: the permuter almost never closes a gap by itself; it is only worth
long runs on the pure register-allocation near misses (Appendix A, tier 1), and it must be
re-seeded from the current best source, not the original draft.

Palmetto CPU-only inventory (from `sinfo`, 2026-10-07, same `work1`/`interact` partitions):

| Node class | Constraint | Cores | RAM | Count / state now | Notes |
|---|---|---|---|---|---|
| AMD EPYC 9654 Genoa | `cpu_gen_genoa` (sphase19) | 192 | 768 GB | 98 (78 mixed, 20 allocated) | fastest per-core and most cores; partial allocations available |
| Intel Xeon 8480CL Sapphire Rapids | `cpu_gen_sapphirerapids` (skyphase03) | 112 | 512 GB | 38 idle | easiest to get whole-node right now |
| Intel Icelake 8358/8360Y | `cpu_gen_icelake` | 64-72 | 256 GB | ~5 idle | fine fallback |
| E5-2660 Sandy Bridge (current node2044) | `cpu_gen_sandybridge` | 16 | 256 GB | hundreds | 2.2 GHz, 2012 era: what the 2.6 s build time was measured on |

Recommendation:

- **One job, one node, Sapphire Rapids or Genoa, 64-128 cores, 128 GB, local scratch.** Run the
  agent fleet (8-16 agents) and a permuter farm (the remaining cores) on the same node so they share
  the repo copy on `/local_scratch`. Expected speedup over the current 8-core Sandy Bridge job:
  ~2x per build-diff cycle for agents, ~30-50x permuter throughput (2x per-core plus 12-24x more
  workers). GPUs are useless here; never request them.
- **Partition:** `interact` (12 h max) while a human is supervising; `work1` (3 days max) via
  `sbatch` for unattended overnight runs. QoS `normal` has no CPU cap; avoid `nextlab200`
  (GrpTRES cpu=120).
- **Time:** request the partition maximum. Permuter runs are checkpoint-free, so a job that dies
  loses the search; `permuter_farm.sh` copies each best source to `/scratch` every few minutes.
- Example (interactive, 96 cores, 128 GB):

```
salloc --partition=interact --account=cuuser_cpsc_ads_s27 \
  --constraint="cpu_gen_genoa|cpu_gen_sapphirerapids" \
  --nodes=1 --ntasks=1 --cpus-per-task=96 --mem=128G --time=12:00:00
```

- Unattended: `sbatch matching_notes/palmetto_job.sh` (3-day `work1` job; it stages the repo to
  node-local disk, launches the permuter farm, and leaves a ready tree for agents).
- **Phased instead of one 3-day job:** `sbatch --time=06:00:00 --export=ALL,FARM_PHASES=4
  matching_notes/palmetto_job.sh` runs four 6-hour jobs back to back. Each phase re-seeds from the
  saved candidates, so the chain is lossless; the farm duration defaults to the time limit minus
  30 min. Short jobs also start sooner and are less exposed to preemption.

Why not more than one node: nothing here communicates across nodes, and a single Genoa node
already offers more permuter workers than there are candidate functions times a sensible per-
function worker count (8 functions x 16 workers = 128). A second node only helps if you want to
run the long-shot permuter on tier-3 functions too.

## 3. Function state by tier (details live in NOTES.md)

**Tier 1 -- regalloc-only.** 11 of 12 matched. Left: func_8437FD74 (90; one reload register in the
innermost loop; farm re-seeded from the 90 draft).

**Tier 2 -- stack layout.** 3 of 10 matched. Left: func_838043F8 (8), func_8430506C (16),
func_84367660 (85, regalloc only), func_83501718 (60), func_8850B2D4 (84), func_84302658 (7 lines),
func_82F04604 (318, partial fix known). Each has a precise slot model in NOTES; the open question in
most is one compiler temp whose creation point we cannot steer. Farm first; one agent pass per
round on the two best candidates only.

**Tier 2b -- gDisplayListHead pair.** Root cause known (one address register range per global
symbol). Parked on `round6-gfxhead-alias`; see decision 1.

**Tier 3 -- data/bss layout.** func_86A013C8, func_81207DF8, func_81209374, func_81209078. Phase C.

**Tier 4 -- large / structural.** 26 functions, Phase B groups above.

## 4. Agent protocol (one round)

Roles: 1 **integrator** (the parent session) + N **matchers** (8-16) + the permuter farm.

### Integrator, start of round
1. `git status` clean except known files; commit the pending `NOTES.md`/`fd.sh` edits.
2. Full build on the staged copy: `make -j32` -> `OK`. Delete stale
   `asm/us/nonmatchings/**/<matched>.s` for anything matched since the last `make init`, re-run
   `progress.py -v us`, record the number in NOTES.md.
3. Create worktrees **based on `match-round-1`** (never master):
   `git worktree add $TMPDIR/wt/agent-<k> match-round-1` then
   `MAIN=<staged repo> matching_notes/agent_setup.sh $TMPDIR/wt/agent-<k>`.
   Verify `git log -1` in each worktree shows the match-round-1 head.
4. Start the permuter farm (Section 5) on tier-1 functions with the remaining cores.
5. Hand each matcher 2-3 functions from the same tier plus the prompt in Section 4.3. Give each
   its own scratch dir (`$TMPDIR/scratch/agent-<k>`).

### Integrator, during/after the round
- Every ~hour: in each worktree `git log match-round-1..HEAD`; cherry-pick match commits onto
  `match-round-1`; rebuild full ROM; if `OK`, push the branch (it has never been pushed).
- A permuter "0" is not a match: copy the source into the real file, run `fd.sh`, then full `make`.
- Update NOTES.md per function: winning shape, or new dead ends. Remove worktrees
  (`git worktree remove --force`) and `nonmatchings/` output (~1 GB per long run) at the end.

### Matcher rules (put these verbatim in every agent prompt)
1. `pwd` first; you must be inside your worktree (`.claude/worktrees/agent-<k>` under the main repo,
   which survives job restarts, or `$TMPDIR/wt/agent-<k>` on a staged node). If a resumed
   session dropped you into the main repo, `cd` back before touching anything.
2. Read `matching_notes/NOTES.md` entry and the `//` comment in the function's `#ifdef
   NON_MATCHING` draft before changing code. Do not retry listed dead ends.
3. Before guessing, run the two oracles once and write their verdicts into your notes:
   `.venv/bin/python3 matching_notes/corpus.py near func_X --draft --c` (which C line emits each
   diff, and how matched siblings wrote the same idiom) and
   `.venv/bin/python3 matching_notes/ido_bisect.py src/<file>.c func_X` (which optimizer pass owns
   each diff line). Then loop: enable the draft with a bare `#if 1` (no trailing comment),
   `matching_notes/fd.sh src/<file>.c func_X`, read only the differing lines, hypothesise what the
   *original source* looked like (IDO_TRICKS.md), edit, repeat. Use `var.py` with a spec file to test 5-20 textual
   variants per build. Bisect perturbations with `if (0)` chunks.
4. ASCII only in `src/` comments (the EUC-JP preprocess step dies on `—`).
5. When the diff is empty: make the C unconditional (delete the `#pragma GLOBAL_ASM` line and the
   `#ifdef NON_MATCHING`/`#else`/`#endif` wrapper), run the full `make` in your worktree (must
   print `OK`), then `git commit -am "Match func_X"`. Report the commit hash. Never leave `#if 1`
   in a committed file. NEVER delete anything under `asm/` - it is a symlink shared with every
   other worktree; the integrator removes stale `.s` files after the round.
6. Write helper scripts with the Write tool into your own scratch dir and run them by absolute
   path; the sandbox refuses `$VAR` paths, heredocs, `source`, and long `&&` chains.
7. If the permuter is appropriate (pure regalloc near miss), hand the function to the integrator
   for the farm instead of running it yourself; keep working on insight.
8. Time-box: after ~90 minutes without a score drop, write your findings as a `//` comment in
   the draft and move to your next function. New dead ends are a deliverable.

### 4.2 Model choice
Matchers do not need the integrator's model. Start each worktree session with
`claude --model claude-opus-5-5` (or `export ANTHROPIC_MODEL=claude-opus-5-5`); Opus 5.5 is
$4/$20 per MTok vs Fable 5.1 at $10/$50. Raise effort to `high` or `xhigh` (Opus defaults to
medium). Subagents spawned with the Agent tool accept `model: "opus"`, but `fork` agents always
inherit the parent's model. Reserve Fable for tier-4 structural functions that resisted earlier rounds.

### 4.3 Agent prompt template
```
You are matching Pokemon Stadium (N64, IDO 7.1) functions to the original ROM.
Worktree: $TMPDIR/wt/agent-<k>   (run pwd; cd there if not)
Main repo (for .venv, asm, permuter): <staged repo>
Your functions, in order: func_A (src/x.c), func_B (src/y.c)
Read matching_notes/PLAN.md section 4, matching_notes/IDO_TRICKS.md, and the NOTES.md entries
for your functions before editing. Run corpus.py near --draft and ido_bisect.py on each function
before your first edit and keep their verdicts in your scratch notes. Follow the matcher rules exactly. Commit each match in the
worktree and report the hash. If you give up on a function, record the dead ends in its //
comment and commit that too.
```

## 5. Permuter farm

`matching_notes/permuter_farm.sh <repo> <workers_per_func> <func>:<src/file.c> ...` imports each
function from the *current* draft (so always re-seed from the best known source first), fixes the
compile.sh arg order, and runs one permuter per function with `--stack-diffs -j<workers>` under
`/local_scratch`, syncing `best/` to `/scratch/$USER/permuter_best/<func>/` every 10 min.

Observability: `matching_notes/farm_status.sh` (any node) prints per function the base score,
best saved score, candidate count, last improvement time and the latest STATUS snapshot
(iterations, errors, it/s; one per 5 min in `<func>.log`). Job stdout: `/scratch/$USER/pokestadium_<jobid>.out`.

Checkpoint/restart: the search is memoryless, so the saved best candidates ARE the checkpoint.
They sync to `/scratch/$USER/permuter_best/<func>/` every 10 min and on SIGTERM. A new farm run
re-seeds each function from its lowest-scoring saved candidate (`RESEED=0` to start from the
draft; delete the function's save dir to forget it). QoS `normal` is preemptable (requeue); the
sbatch script requeues, appends logs, and the restart re-seeds automatically. Candidates saved
by older runs with `--no-context-output` need `farm_splice.py` before they can seed.

Sizing (measured 2026-10-07): a shared 96-core Genoa allocation delivered ~480 it/s in total
whether run as 6 functions x 16 workers or 24 x 4; the cost is process spawning (four IDO
stages + objdump per iteration, ~30% system time), not compile CPU. So use ~4 workers per
function, cover as many functions as possible, and add nodes rather than cores to go faster.
Per-worker rate was ~2x higher on a lightly loaded node than on one shared with other heavy
jobs; consider `--exclusive` on an idle 112-core Sapphire Rapids node. A function whose draft
contains `sizeof(T) * N` is auto-repaired after import (pycparser mangles it); other base.c
compile failures show up as a log with no `base score` line - check `farm_status.sh` after the
first sync. Side jobs for a few functions:
`sbatch --job-name=pokestadium-side --cpus-per-task=8 --mem=16G --export=ALL,FUNCS_OVERRIDE="func_X:src/a.c func_Y:src/b.c" matching_notes/palmetto_job.sh`. Permuter scores are inflated by
a constant when the file has statics; judge candidates with `fd.sh`, not the permuter number.
Kill one run with `pkill -f "permuter[.]py nonmatchings/<func>"`.

## 6. Integration and hygiene (every round)
1. Integrator cherry-picks each agent's commits in the order the agent gives (a match commit may sit
   on an intermediate commit - pick both or the cherry-pick conflicts).
2. Full `make` after every pick; `grep -c "#if 1"` on touched files must be 0.
3. Do NOT delete `asm/us/nonmatchings/*.s` while agents run (shared symlink); delete all stale ones
   at round end: files present but no longer named by any GLOBAL_ASM.
4. Write every winning shape and every dead end into NOTES.md the same day; move generalisable rules
   to IDO_TRICKS.md.
5. Remove worktrees, keep any unmerged work on a named branch, update the farm list, resubmit.
6. Before resuming agents after a Claude Code restart, `scancel` the old interactive job - its
   agents keep running and edit the same worktrees.

## Appendix A: the 54 functions open at the start of 2026-10-07 (instruction counts; 14 since matched)

```
 3346 func_8437B0CC  fragments/62/fragment62_361050   tier 4
 1598 func_84362084  fragments/62/fragment62_34A420   tier 4
 1450 func_8120572C  fragments/1/fragment1_7F9A0      tier 4
 1190 func_88209B54  fragments/23/fragment23_1AE680   tier 4 (~580)
 1012 func_8003DB84  3D140_2                          tier 2 (18)
  965 func_810010BC  fragments/31/fragment31_2558B0   tier 4
  960 func_80045FF0  46680                            tier 4
  945 func_88805AEC  fragments/28/fragment28_2190D0   tier 4
  825 func_88203ED8  fragments/23/fragment23_1A9780   tier 4
  715 func_86800B38  fragments/14/fragment14_144300   tier 2 (81)
  639 func_86803C6C  fragments/14/fragment14_1462A0   tier 4
  631 func_82F04604  fragments/41/fragment41_289240   tier 2
  629 func_88216000  fragments/23/fragment23_1BCF10   tier 4 (18415)
  624 func_8850B2D4  fragments/26/fragment26          tier 2
  590 func_88304850  fragments/24/fragment24_1CEA00   tier 4
  582 func_88201488  fragments/23/fragment23_1A9780   tier 4
  558 func_838043F8  fragments/47/fragment47_2AFDB0   tier 2
  553 func_8130337C  fragments/33/fragment33          tier 4
  532 func_86100C30  fragments/7/fragment7            tier 2b
  508 func_86905734  fragments/15/fragment15_150AC0   tier 4
  492 func_87804320  fragments/2/fragment2_2          tier 1 (275)
  471 func_80044EA4  45720                            tier 1 (6744; permuter seed saved)
  447 func_8820BE14  fragments/23/fragment23_1AE680   tier 4 (~3156)
  417 func_84367660  fragments/62/fragment62_351F20   tier 2 (229)
  417 func_80049DF0  4A3E0                            tier 4 (GB APU, no draft)
  412 func_860005B8  fragments/6/fragment6            tier 2b
  391 func_885065E0  fragments/26/fragment26          tier 4
  391 func_88305F28  fragments/24/fragment24_1CEA00   tier 4
  326 func_80033D44  33FE0                            tier 4 (struct wrong)
  322 func_84372670  fragments/62/fragment62_359F90   tier 1
  311 func_80034348  33FE0                            tier 4
  309 func_83501718  fragments/44/fragment44          tier 2
  305 func_8436C6A4  fragments/62/fragment62_356730   tier 1
  285 func_86A01CF0  fragments/16/fragment16_15A2B0   tier 1
  275 func_88807D04  fragments/28/fragment28_2190D0   tier 4
  266 func_8004A474  4A3E0                            tier 4 (GB APU, no draft)
  256 func_8004A89C  4A3E0                            tier 4 (GB APU, ~170)
  254 func_8437FD74  fragments/62/fragment62_361050   tier 1
  240 func_88500A74  fragments/26/fragment26          tier 4
  235 func_8250281C  fragments/39/fragment39_27BCC0   tier 1
  229 func_80034BD4  33FE0                            tier 1 (sibling of matched func_80034824)
  222 func_84302658  fragments/62/fragment62_2EC3C0   tier 2
  197 func_81209374  fragments/1/fragment1_86CB0      tier 3
  185 func_81209078  fragments/1/fragment1_86CB0      tier 3 (~320)
  172 func_81002530  fragments/31/fragment31_2577F0   tier 1 (10)
  170 func_81003A54  fragments/31/fragment31_258080   tier 1 (110)
  157 func_81207DF8  fragments/1/fragment1_86CB0      tier 3
  149 func_8430506C  fragments/62/fragment62_2EC3C0   tier 2 (16)
  118 func_80041A98  3D140_2                          tier 4
  117 func_88206110  fragments/23/fragment23_1AE680   tier 1
   83 func_86B09F64  fragments/17/fragment17_169510   tier 1
   60 func_80012870  12D80                            tier 4 (one store early)
   59 func_882111F8  fragments/23/fragment23_1B4EA0   tier 2
   50 func_86A013C8  fragments/16/fragment16_158A00   tier 3 (code identical, bss offset)
```
Numbers in parentheses are the last recorded diff scores from NOTES.md.
