# Plan to finish the Pokemon Stadium (US) decomp -- handoff for AI agents

Rewritten 2026-10-17 06:30 after round 8 (branch `match-round-1`). Read this file first, then
`NOTES.md` (per-function state and history; the "Round 8" sections are the latest) and
`IDO_TRICKS.md` (what has worked; the end of the file has round 8's compiler lessons). Each open
function's `#ifdef NON_MATCHING` draft has a `//` comment with the model of what still differs and
every dead end: read it before touching the function.

## 0. Where the project stands (2026-10-17 morning)

| Item | State |
|---|---|
| ROM | builds byte-identical (`make` -> `OK`) on `match-round-1`, 280 commits ahead of `master`, never pushed |
| Upstream | `origin/master` unchanged since 2026-10-03 (#283); open upstream PRs #284 (audio tools), #282 (progress.py stops counting hand-written asm) |
| Code (`progress.py -v us`, all) | 96.60% (93.13% when matching began; 96.40% before round 8) |
| `#pragma GLOBAL_ASM` left | 9 = 6 open + 3 parked (list in section 3) |
| Parked (owner decision) | func_860005B8 + func_86100C30 (linker alias, branch `round6-gfxhead-alias`); func_86A013C8 (unused-label symbol padding, branch `round8-86A013C8-labels`) |
| Data still asm | by design: F3DEX2 blobs, 66BC0, fragment1 hand-written asm data; open: 7E0D0, 7D110, 7A1C0, unk_bin_7F670 (Phase D section) |
| Farm (running) | Slurm 17512644 (tag v: func_8004A89C, func_80034348) and 17512996 (tag w: func_86905734, func_88304850, func_88805AEC), both end ~14:45 on 10-17; candidates in `/scratch/$USER/permuter_best/<func>__<tag><k>/` |
| Tools | datamig.py + phased_job.sh (data migration with sbatch build gate), adopt_candidate.py / try_candidate.py (permuter candidates), ccs.py (IDO `cc -S` for one function: uopt's registers before as1), corpus.py, accessmap.py, symcheck.py, ido_bisect.py, var.py, fd.sh |

Round 8 (night of 10-16, 17 Opus agents in four passes + farm) matched 20 functions; see NOTES.md.
What finally cracked the hard register-allocation cases was a model of uopt, not brute force:
uopt copy-propagates assignments built only from register variables, so one source variable becomes
several live ranges; a dead redefinition or a separate early local blocks that (IDO_TRICKS.md end).
`ccs.py` shows uopt's choices directly and is the fastest way to test a hypothesis.

## Finish roadmap

| Step | Scope | Who | Exit criterion |
|---|---|---|---|
| F1 harvest (first hour) | Check the farm for every open function; adopt zeros; splice the best candidates into the drafts when they are plausible C; re-check 7E0D0 now that 2 of 3 GB APU functions match | integrator alone | farm candidates triaged; drafts at their best known score |
| F2 round 9 | The 6 open functions (table in section 3), one agent per file group, applying the uopt model with ccs.py | 4-6 Opus agents + farm | each matched, or a draft whose comment names the exact remaining copy/colouring difference |
| F3 owner decisions | Alias pair, func_86A013C8 labels; accept (merge the branch) or keep GLOBAL_ASM with a comment | owner | decided |
| F4 data leftovers | 7E0D0 (literals of the GB APU functions), 7D110, 7A1C0, unk_bin_7F670 | integrator or 1 agent | migrated or documented as by-design |
| F5 upstream | Tidy, rebase onto `origin/master`, split into PRs, file the permuter PR | integrator + owner approval for every push | PRs open |

### F2 detail: the six open functions
| Function (file) | Draft | Farm best (permuter score, unverified) | What is left (details in the draft comment) |
|---|---|---|---|
| func_8004A89C (src/4A3E0.c) | 345 | 320 (v1) | colouring among a0-a3 at the top (idx/row/sample) and a tail `move t5,a0`; siblings matched with the `dir[1]` array and pointer-read tricks |
| func_80034348 (src/33FE0.c) | 705 | 390 (v2) | float colouring in the triangle loop; the fs3 "phantom" is `len`; agent-15's basic-block-boundary approach got 2582 -> 705 |
| func_86905734 (src/fragments/15/fragment15_150AC0.c) | 1386 | 1298 (i1, older) | ugen makes 2 fewer int temps before -h (t-register shift), two reloads of (f32)arg1/arg2, one swapped slot pair |
| func_88304850 (src/fragments/24/fragment24_1CEA00.c) | 2834 | 1676 (w1) | arg0 split into three register groups, gDisplayListHead should be t0, x0 = arg0+0x84 should spill to 0x50 (fixes a switch-wide t-register rotation) |
| func_88805AEC (src/fragments/28/fragment28_2190D0.c) | 4600 | 2177 (w1) | one extra compiler temp (frame 0x230 vs 0x228), (arg2-5)<<2 should live in t0, arg5 in v1 |
| func_8437B0CC (src/fragments/62/fragment62_361050.c) | 7809 | none | two copies the target keeps and we propagate: the case-2 0x5C-block copy X (spilled before the first call, reloaded into s5) and `move v1,v0` in case 0x19; everything else follows. Consider a Fable agent here (decision 2) |
Scores: diff.py WITHOUT `-s` (fd.sh's `-s` under-reports early-return functions); farm numbers are the
permuter's own scale and must be checked with try_candidate.py. Farm candidates often reach a lower
score with nonsense edits (`if (1)`, `x*0`, u64 casts); take the idea, write it as plausible C.

### F5 detail: getting the work upstream
1. `git fetch origin`; rebase or merge `match-round-1` onto `origin/master`, resolve conflicts, `make` -> OK.
2. Tidy: functions adopted verbatim from permuter output (func_838043F8, func_88500A74, func_88807D04)
   are in pycparser formatting; reformat to repo style and re-check with the full make. Remove
   `// FAKE?` hacks where a cleaner equivalent is known. No `#if 1`, no NON_MATCHING drafts for matched code.
3. Decide what goes upstream: src/ include/ yamls/ linker_scripts/ tools/data2c.py changes yes;
   `matching_notes/` probably not (ask the owner).
4. Split into reviewable PRs in the upstream style (one per fragment or subsystem for matches, one per
   data cluster for migrations), each building OK on its own. Draft them; the owner pushes or approves
   each push. File the decomp-permuter `sizeof` PR from `UPSTREAM_PR_permuter_sizeof.md`.

### Data migration reference (datamig.py + phased_job.sh; Phase D, 2026-10-16)
Real scope: **27 files** after 2026-10-16 (the "184" count included 153 fragment header/reloc
binary stubs, which stay binary by design). Done: rom_data_7A110, fragment1_rodata_AA8F0,
fragment1_data_8E3E0 (103 KB GB audio state + samples: the mid-.data static D_8120EB6C that the
tier-3 functions in fragment1_86CB0 need is now real C data; func_81207DF8 matched from it),
4A3E0 (GB APU tables) and rom_data_78990 (3D140 audio tables); overnight 2026-10-16: 703E0 (into
20470.c), 71BA1 + string rodata 7C1C0/7C220/7C750 (four data-only files src/data_*.c), 78220
(37370.c), 76A40 (30640.c, 334D0.c), fragment1 8D1A0. Status of the rest (survey 2026-10-16 night):
- by design (leave): F3DEX2.data, F3DEX2_data.rodata, unk_F3DEX2_68020/68C80, 66BC0 (microcode
  data next to the F3DEX2 blobs); fragment1 A8020, data_asm, rodata A8E80/A8F00/A9140/A9BE0/AA900 are
  the data of the hand-written fragment1_code_asm (hasm; jtbl_81229500 etc.), fragment1_bss.
- waits for a match: 7E0D0 = float literals of the GB APU functions in 4A3E0.c (GLOBAL_ASM).
- needs judgment: 7D110 (D_8007C570 = 65535.0 literal of 30640.c, then format strings "0x%08x ",
  "%10.4f  " that no C source contains: a print routine between 30640 and 33FE0), 7A1C0 (custom
  OSViMode used only by fragment1), unk_bin_7F670.
1. `.venv/bin/python3 matching_notes/datamig.py survey` (~1 min) lists every file, READY or not;
   `plan <file.s>` shows per label: span, declared type/size, C users, proposed owner, link-order check.
2. `datamig.py apply <file.s>` writes the definitions (values from the baserom, pointers by symbol
   from the .s, struct layouts from tools/data2c.py), forward-declares referenced symbols, rewrites the
   yaml line(s) to `.data/.rodata, <owner>` and marks the symbols `defined:true size:N` in whichever
   symbol_addrs*.txt already lists them (a second entry is a splat error).
3. Gate on a compute node, never in the main repo (`make extract` regenerates the shared asm/):
   `sbatch --chdir=$PWD/scratch/phased matching_notes/phased_job.sh <file.s> ...` (no args = all).
   It builds the base, tries each file in its own copy, then all passing patches together, and prints
   `git apply scratch/phased/<job>/combined.patch`. About 1 min per file on 32 cores.
   After applying, run `make extract` once in the main repo.
Rules learned:
- A `.rodata` float/double in the ROM is an anonymous literal: inline the value at its single use
  (datamig does this). A named `const f32 x = ...;` lands in IDO's .data and breaks the match.
- Extern arrays declared too short (`extern void (*D_80079520[5])(void)` for a 16-entry table)
  are grown to the label span automatically.
- Labels with no C user are resolved automatically: users inside GLOBAL_ASM functions count
  (asm/us/nonmatchings/<file>/), pointer targets join the owner of the table that points at them,
  unowned runs join the owner on their side, and a run between two owners splits at the only
  16-aligned label that fits (each C file's .data starts 16-aligned). Labels used by several files
  are constrained to those files; a run nobody anchors goes to the file used most (a guess, same bytes).
- IDO starts every data object on a 4-byte boundary. A label at an unaligned address is a field of
  the previous object: datamig folds it in, keeps its value in a `<prev>_tail` array, and gives the
  linker its address in undefined_syms.ld. Zero gaps beyond the 4-byte slack become
  `static s32 pad_D_X[n]` (upstream style); sub-word pad objects are impossible.
- gcc's syntax check compiles the NON_MATCHING drafts: definitions must match draft declarations.
  When only a draft declares a symbol, datamig uses the draft type and hoists the draft's typedef
  above the `#ifdef NON_MATCHING`.
- spimdisasm symbolizes sample words that look like addresses (D_102, D_5000000): only KSEG0 values
  are treated as pointers.
- Type repair, automated: a scalar placeholder (`extern u16 D_X;`) on a longer object that C only ever
  takes the address of (all uses `&D_X`, drafts included) is retyped to an array and `&D_X` -> `D_X`
  (same address constant). Covered 35 length-prefixed u16/u8 lists in 78990 and the u8[9] table in 4BDC0.
  Declared arrays that are too short are grown (D_80078410 [1][9] -> [17][9]).
- Definitions go after the owner's own extern; declarations are ranked owner > sized > unsized, and
  sources are walked in sorted order (placement once depended on filesystem order and differed by node).
- `survey` READY is optimistic (apply can still refuse: GLOBAL_ASM literals, nonzero slack bytes).
- Main-segment .rodata 7C1C0 + 7C220 + 7C750 (271 strings: "No"..., 165 x "skill", item names) are
  anonymous string literals of 22630.c's data tables: every string is pointed to exactly once from
  rom_data_71BA1 (D_80072338 move table -> "skill", D_80072EE0 char*[84] -> item names), and the
  blobs sit right before `.rodata, 22630` (0x7CCA0). IDO emits literals from data initializers into
  .rodata in source order, one copy per use, each padded to 4 (tested 2026-10-16), so defining the
  tables with inline literals before 22630's functions re-creates the blobs; yaml then starts
  `.rodata, 22630` at 0x7C1C0. Ownership of the .data side: 22630 owns 703E0 and 71BA1 up to
  D_80073230 (D_80072B00 too, used by 232C0 via extern: otherwise owners interleave); 232C0 owns
  D_80073230 on. datamig's inference picked fragment62 for D_80070FA0..D_80072AF4 because a fragment
  uses them: fragments cannot own main-segment data (fix: only same-segment users are candidates).
  Still manual: D_8006FF00[152] overlaps D_80070F84 (= &D_8006FF00[151], typed PokemonStats[]) and
  the table runs on into 71BA1; D_8006FEE8 is a fake offset symbol into D_8006FF00.
What blocks the remaining files (needs an agent, not the script): labels with no C user (only
referenced from other data or GLOBAL_ASM; owner = surrounding owner, decided by hand), externs with
the wrong type (`extern u16` on a 12-byte object: real type must be worked out from the users), and
owners that already have a .data/.rodata entry (definitions must be merged in address order).

### Definition of done
- `grep -rn "pragma GLOBAL_ASM" src` empty, or only owner-accepted exceptions with a comment.
- `asm/us/data` holds only by-design binaries (documented above); no `#ifdef NON_MATCHING` drafts left.
- `make clean && make -j` -> `OK`; `progress.py -v us` code 100% (with upstream #282's counting).
- Work merged or PRs open upstream; permuter PR filed; NOTES.md trimmed to lessons + short history.

### Decisions the owner must make
1. The gDisplayListHead linker alias (branch `round6-gfxhead-alias`, two functions).
2. func_86A013C8 via eight unused labels (branch `round8-86A013C8-labels`).
3. Model for a stalled giant: Opus 5.5 by default; Fable only for func_8437B0CC if round 9 stalls.
4. Whether `matching_notes/` and the helper scripts go upstream, and how to split the PRs.
5. Whether to accept fake-but-load-bearing C (`if (x) {}` boundaries, dead assignments) marked `// FAKE?`.

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

## 3. Function state (2026-10-17)

Open: the six in the F2 table above. Parked: func_860005B8, func_86100C30, func_86A013C8 (section 0).
All other functions match. Per-function history is in NOTES.md; the current truth is each draft's
`//` comment.

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
Since round 8 the prompt is: `matching_notes/round_setup.md` (worktree setup, private asm copy,
lessons) + a short per-round paragraph (pass number, farm candidates, deadline) + the output of
`round_prompts.py prompt --agent agent-k --worktree "(your current working directory; see SETUP)"
--main <repo> --base match-round-1 func_X@score:src/x.c ...`. Agents are launched with the Agent tool
(`isolation: worktree`); they commit on `worktree-agent-*` branches; the integrator cherry-picks with
`git log --cherry-pick --right-only match-round-1...<branch>` and runs the full make after each pick.
Older template:
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

### Round 8 process lessons
- Before every round, scan `/scratch/$USER/permuter_best` for score-0 outputs of open functions and run
  `adopt_candidate.py` on them: four real matches sat there unadopted for up to ten days.
- fd.sh uses `diff.py -s`, which gives false zeros and under-reports early-return functions; score
  those without `-s`, and count a match only after the full make prints OK.
- Agents work in Agent-tool worktrees with a private `asm/` copy (round_setup.md), so the integrator can
  run `make extract` in the main repo during a round. Pass job IDs to agents only after reading them
  from sbatch's output.
- When the API usage limit stops agents, they keep their worktree state: resume them with SendMessage
  after the reset rather than starting new ones.
- phased_job.sh stages the committed HEAD, so the working tree can hold experiments while it queues.

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
