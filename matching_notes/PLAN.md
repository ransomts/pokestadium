# Plan to finish the Pokemon Stadium (US) decomp -- handoff for AI agents

Written 2026-10-07 on Palmetto (node2044, branch `match-round-1`). Read this file first, then
`NOTES.md` (per-function state, process lessons) and `IDO_TRICKS.md` (what has worked). Those two
files are the ground truth for per-function details; this file is the work breakdown, the agent
protocol, and the cluster recipe.

## 0. Where the project stands

| Item | State |
|---|---|
| Code matched (`progress.py -v us`, "all") | 94.79% after round 6 (was 93.95% at start of 2026-10-07) |
| Functions still `#pragma GLOBAL_ASM` | 40 (Appendix A lists the original 54; rounds 5-6 matched 14) |
| ROM | builds byte-identical (`make` prints `build/pokestadium-us.z64: OK`) |
| Data still in asm (`asm/us/data/**/*.s`) | 184 files, not yet migrated to C |
| `boot.o` | 0% -- verify whether it is hand-written asm (then it is not "undecompiled") |
| Uncommitted | `matching_notes/NOTES.md`, `matching_notes/fd.sh` (Palmetto PATH fixes), `.claude/`, `scratch/` |

"Finishing" has two layers. Layer 1 is matching the 54 functions (what every prior round worked
on). Layer 2 is data migration (asm/us/data -> C) and cleanup so the repo is a complete source
tree. Layer 2 is mechanical and large; start it only once Layer 1 is down to the handful of
functions blocked on data layout, because migrating data is also the fix for those.

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
  `/local_scratch`, launches the permuter farm, and leaves a ready tree for agents).

Why not more than one node: nothing here communicates across nodes, and a single Genoa node
already offers more permuter workers than there are candidate functions times a sensible per-
function worker count (8 functions x 16 workers = 128). A second node only helps if you want to
run the long-shot permuter on tier-3 functions too.

## 3. Work breakdown (Layer 1: the 54 functions)

Tiers below are from NOTES.md; sizes are instruction counts from the `.s` files (Appendix A).

**Tier 1 -- regalloc-only near misses.** Rounds 5-6 matched 11 of 12. Left: func_8437FD74 (90, one
reload register; see NOTES).

**Tier 2 -- stack-layout near misses.** Round 6 matched 3 of 10 (func_8003DB84, func_882111F8,
func_86800B38). Left: func_838043F8 (8), func_8430506C (16), func_84367660 (85, regalloc only now),
func_83501718 (60), func_8850B2D4 (84), func_84302658 (7 lines), func_82F04604 (318, partial fix
known). Each has a precise slot model in NOTES; the open question in most is one compiler temp
whose creation point we cannot yet steer. Read IDO_TRICKS "slot order follows first appearance".
Shared trick that worked before: frame too big with identical offsets => too many named locals;
turn `v += k` induction vars into `base + i*k`.

**Tier 2b -- shared gDisplayListHead-in-register pattern.** func_860005B8, func_86100C30. ROOT
CAUSE FOUND in round 6 (one register range per global symbol); a byte-identical match exists on
branch `round6-gfxhead-alias` but needs a linker alias (second name for gDisplayListHead). Owner
decision pending; not counted as matched.

**Tier 3 -- blocked on data/bss layout.** func_86A013C8 (code identical, static lands at wrong
bss offset), func_81207DF8, func_81209374 (need mid-.data static), func_81209078. Needs the
`cc -S` investigation of `.lcomm/.comm` ordering and/or migrating ~100 KB of sample data in
`fragment1_86CB0` to C. This is where Layer 2 (data migration) starts paying off.

**Tier 4 -- large / structural (one dedicated agent each, long session).**
func_88216000 (629, custom load-block macro), func_88209B54 (1190), func_8820BE14 (447),
func_8004A89C / func_80049DF0 / func_8004A474 (Game Boy APU emulator in `src/4A3E0.c`; fix the
missing `;` in the struct first), func_80033D44 (struct type wrong, fields shifted by one),
func_8437B0CC (3346, largest), func_84362084 (1598), func_8120572C (1450), func_810010BC (965),
func_80045FF0 (960), func_88805AEC (945), func_88203ED8, func_88201488, func_86803C6C,
func_86905734, func_8130337C, func_885065E0, func_88500A74, func_88304850, func_88305F28,
func_88807D04, func_80034348, func_80041A98, func_80012870 (60 instr, one store scheduled early).

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
1. `pwd` first; you must be inside your worktree `$TMPDIR/wt/agent-<k>`. If a resumed
   session dropped you into the main repo, `cd` back before touching anything.
2. Read `matching_notes/NOTES.md` entry and the `//` comment in the function's `#ifdef
   NON_MATCHING` draft before changing code. Do not retry listed dead ends.
3. Loop: enable the draft with a bare `#if 1` (no trailing comment), `matching_notes/fd.sh
   src/<file>.c func_X`, read only the differing lines, hypothesise what the *original source*
   looked like (IDO_TRICKS.md), edit, repeat. Use `var.py` with a spec file to test 5-20 textual
   variants per build. Bisect perturbations with `if (0)` chunks.
4. ASCII only in `src/` comments (the EUC-JP preprocess step dies on `—`).
5. When the diff is empty: restore `#ifdef NON_MATCHING` -> delete the `#pragma GLOBAL_ASM` and
   the `#ifdef`, delete `asm/us/nonmatchings/.../func_X.s`, run the full `make` in your worktree
   (must print `OK`), then `git commit -am "Match func_X"`. Report the commit hash. Never leave
   `#if 1` in a committed file.
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
for your functions before editing. Follow the matcher rules exactly. Commit each match in the
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

## 6. Layer 2: data migration and completion checklist

Start when tier 1-2 are exhausted or when working tier 3.

1. For each `asm/us/data/**/*.s` (184 files): identify the owning C file, generate C with
   `tools/data2c.py` / `tools/print_decls.py`, move it in, re-split the yaml if needed, rebuild.
   Start with `fragment1_86CB0` and `fragment16_158A00` because they unblock tier 3.
2. Confirm `boot.o`/`entry.o` are hand-written asm and mark them as such in the yaml/progress.
3. Remove `#ifdef NON_MATCHING` scaffolding and `pad_*` splat filler where real symbols exist.
4. Final gates: `make clean && make -j` -> `OK`; `progress.py -v us` code at 100%; no files in
   `asm/us/nonmatchings`; push `match-round-1` and open the PR to `master`.

## Appendix A: remaining functions (instruction counts)

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
