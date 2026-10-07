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
# permuter farm on the tier-1 functions, and leave a ready tree for Claude Code agents.
# Edit FUNCS below (func:src pairs) before submitting. For a supervised session use
# `salloc` with the same resources (see PLAN.md section 2) and run the steps by hand.
# QoS normal is preemptable (PreemptType=preempt/qos, mode REQUEUE): on preemption Slurm requeues
# the job, which re-stages and re-seeds from /scratch/$USER/permuter_best. Logs append across restarts.
# Shorter run: sbatch --time=1-00:00:00 --export=ALL,FARM_HOURS=22 matching_notes/palmetto_job.sh
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

# Permuter farm: tier 1 + 2 near misses. Enable each draft with a bare `#if 1` in the staged
# copy only (never commit that). The permuter's main process caps each function at ~80 it/s
# regardless of workers, so spread cores thin: 6 workers x 15 funcs = 90 cores.
FUNCS=(
  # round 6 (2026-10-07): the 15 still-unmatched tier 1/2/2b functions
  func_8437FD74:src/fragments/62/fragment62_361050.c
  func_84372670:src/fragments/62/fragment62_359F90.c
  func_80044EA4:src/45720.c
  func_8430506C:src/fragments/62/fragment62_2EC3C0.c
  func_8003DB84:src/3D140_2.c
  func_84367660:src/fragments/62/fragment62_351F20.c
  func_86800B38:src/fragments/14/fragment14_144300.c
  func_84302658:src/fragments/62/fragment62_2EC3C0.c
  func_838043F8:src/fragments/47/fragment47_2AFDB0.c
  func_83501718:src/fragments/44/fragment44.c
  func_8850B2D4:src/fragments/26/fragment26.c
  func_882111F8:src/fragments/23/fragment23_1B4EA0.c
  func_82F04604:src/fragments/41/fragment41_289240.c
  func_860005B8:src/fragments/6/fragment6.c
  func_86100C30:src/fragments/7/fragment7.c
)
# FUNCS_OVERRIDE="func_X:src/a.c func_Y:src/b.c" replaces the list (e.g. a small side job).
[ -n "${FUNCS_OVERRIDE:-}" ] && read -r -a FUNCS <<< "$FUNCS_OVERRIDE"
for spec in "${FUNCS[@]}"; do
  f=${spec%%:*}; s=${spec#*:}
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
WORKERS=$(( SLURM_CPUS_PER_TASK / ${#FUNCS[@]} ))
bash "$STAGE/matching_notes/permuter_farm.sh" "$STAGE" "$WORKERS" "${FARM_HOURS:-70}" "${FUNCS[@]}"
# Undo the #if 1 edits so the staged tree is clean for agents / cherry-picks.
(cd "$STAGE" && git checkout -- src/)
echo "done: $(date)"
