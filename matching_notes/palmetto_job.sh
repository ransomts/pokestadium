#!/bin/bash
#SBATCH --job-name=pokestadium-match
#SBATCH --partition=work1
#SBATCH --account=cuuser_cpsc_ads_s27
#SBATCH --constraint="cpu_gen_genoa|cpu_gen_sapphirerapids"
#SBATCH --nodes=1 --ntasks=1 --cpus-per-task=96 --mem=128G
#SBATCH --time=3-00:00:00
#SBATCH --requeue
#SBATCH --open-mode=append
#SBATCH --signal=B:TERM@120
#SBATCH --output=/scratch/%u/pokestadium_%j.out
#
# Unattended Palmetto job: stage the repo to node-local SSD, verify the build, run the
# permuter farm on the open near misses, and leave a ready tree for Claude Code agents.
# Edit FUNCS below before submitting (func:src[:workers[:copies]] specs). For a supervised
# session use `salloc` with the same resources (see PLAN.md section 2) and run steps by hand.
# QoS normal is preemptable (PreemptType=preempt/qos, mode REQUEUE): on preemption Slurm requeues
# the job, which re-stages and re-seeds from /scratch/$USER/permuter_best. Logs append across restarts.
# Phased runs (no 3-day job needed): the saved candidates are the checkpoint and every start
# re-seeds from them, so chain short jobs. FARM_HOURS defaults to the job's time limit minus 30 min;
# FARM_PHASES=N makes the job resubmit itself N-1 more times with the same resources and time limit:
#   sbatch --time=06:00:00 --export=ALL,FARM_PHASES=4 matching_notes/palmetto_job.sh   # 4 x 6 h
# Stop the chain early with `scancel` (the queued successor is submitted only at the end of each phase).
set -eu
SRC_REPO=${SRC_REPO:-$HOME/Code/pokestadium}
STAGE=${TMPDIR:-/tmp}/pokestadium
export PATH="$HOME/local/bin:$HOME/.local/bin:/usr/local/bin:/usr/bin:/bin"

echo "node: $(hostname)  cpus: $SLURM_CPUS_PER_TASK  start: $(date)"
mkdir -p "$(dirname "$STAGE")"
# Stage: everything the build needs, including gitignored inputs (venv, asm, permuter, roms).
rsync -a --delete --exclude '/nonmatchings/' --exclude '.claude/worktrees/' "$SRC_REPO/" "$STAGE/"
cd "$STAGE"
find build -exec touch {} + 2>/dev/null || true

# Gate: the staged tree must build byte-identical before anyone works on it.
env PATH="$STAGE/.venv/bin:$PATH" make -j"$SLURM_CPUS_PER_TASK" PYTHON="$STAGE/.venv/bin/python3" 2>&1 | tail -3
grep -q OK <(env PATH="$STAGE/.venv/bin:$PATH" make PYTHON="$STAGE/.venv/bin/python3" 2>&1 | tail -1) || { echo "BUILD NOT OK"; exit 1; }

# Permuter farm: open near misses. Enable each draft with a bare `#if 1` in the staged
# copy only (never commit that). Spec is func:src[:workers[:copies]]: the permuter's main
# process caps each function at ~80 it/s regardless of workers, so scale by adding copies
# (independent permuters), not workers — small/fast functions want many copies x 2-3 workers,
# slow-compiling giants want few copies x 5-6 workers. Fields left off default to the
# WORKERS computed below and $COPIES. Several jobs may farm the same or different lists
# sharing permuter_best: give each a distinct RUN_TAG, e.g.
#   sbatch --job-name=farm-a --export=ALL,RUN_TAG=fa,FUNCS_OVERRIDE="..." matching_notes/palmetto_job.sh
# Mid-run re-seed (permuter_farm.sh) merges their best candidates automatically.
FUNCS=(
  # 2026-10-17 farm10 default (single node; live submissions use FUNCS_OVERRIDE per node)
  func_8437B0CC:src/fragments/62/fragment62_361050.c:5:6
  func_88805AEC:src/fragments/28/fragment28_2190D0.c:5:6
  func_88304850:src/fragments/24/fragment24_1CEA00.c:4:6
)
# FUNCS_OVERRIDE="func_X:src/a.c:3:8 func_Y:src/b.c" replaces the list (e.g. a side job).
[ -n "${FUNCS_OVERRIDE:-}" ] && read -r -a FUNCS <<< "$FUNCS_OVERRIDE"
for spec in "${FUNCS[@]}"; do
  IFS=: read -r f s _ <<< "$spec"
  "$STAGE/.venv/bin/python3" - "$s" "$f" <<'EOF'
import re, sys
path, func = sys.argv[1:3]
t = open(path).read()
i = t.find(func + "(")
j = t.rfind("#ifdef NON_MATCHING", 0, i)
if j >= 0:
    t = t[:j] + "#if 1" + t[j + len("#ifdef NON_MATCHING"):]
    open(path, "w").write(t)
EOF
done
# Default workers for FUNCS entries without an explicit :W (see the FUNCS comment above).
WORKERS=$(( SLURM_CPUS_PER_TASK / (${#FUNCS[@]} * ${COPIES:-1}) ))
# Farm duration: explicit FARM_HOURS, else the job's time limit minus 30 min (staging + final sync).
LIMIT=$(squeue -h -j "$SLURM_JOB_ID" -o %l)          # D-HH:MM:SS or HH:MM:SS
if [ -z "${FARM_HOURS:-}" ]; then
  FARM_HOURS=$(python3 -c "
import sys; t=sys.argv[1]; d=0
if '-' in t: d,t=t.split('-'); d=int(d)
h,m,s=(list(map(int,t.split(':')))+[0,0])[:3]
print(max(0.5, round(d*24+h+m/60-0.5,2)))" "$LIMIT")
fi
echo "farm hours: $FARM_HOURS (job limit $LIMIT), phases left: ${FARM_PHASES:-1}"
bash "$STAGE/matching_notes/permuter_farm.sh" "$STAGE" "$WORKERS" "$FARM_HOURS" "${FUNCS[@]}"
# Chain the next phase (same script, same #SBATCH resources, same time limit).
if [ "${FARM_PHASES:-1}" -gt 1 ]; then
  next=$(sbatch --time="$LIMIT" --export=ALL,FARM_PHASES=$((FARM_PHASES-1)),FARM_HOURS="$FARM_HOURS" "$SRC_REPO/matching_notes/palmetto_job.sh" | tail -1)
  echo "next phase: $next"
fi
# Undo the #if 1 edits so the staged tree is clean for agents / cherry-picks.
(cd "$STAGE" && git checkout -- src/)
echo "done: $(date)"
