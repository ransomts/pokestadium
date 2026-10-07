#!/bin/bash
#SBATCH --job-name=pokestadium-match
#SBATCH --partition=work1
#SBATCH --account=cuuser_cpsc_ads_s27
#SBATCH --constraint="cpu_gen_genoa|cpu_gen_sapphirerapids"
#SBATCH --nodes=1 --ntasks=1 --cpus-per-task=96 --mem=128G
#SBATCH --time=3-00:00:00
#SBATCH --output=/scratch/%u/pokestadium_%j.out
#
# Unattended Palmetto job: stage the repo to node-local SSD, verify the build, run the
# permuter farm on the tier-1 functions, and leave a ready tree for Claude Code agents.
# Edit FUNCS below (func:src pairs) before submitting. For a supervised session use
# `salloc` with the same resources (see PLAN.md section 2) and run the steps by hand.
set -eu
SRC_REPO=${SRC_REPO:-$HOME/Code/pokestadium}
STAGE=/local_scratch/$USER/pokestadium
export PATH="$HOME/local/bin:$HOME/.local/bin:/usr/local/bin:/usr/bin:/bin"

echo "node: $(hostname)  cpus: $SLURM_CPUS_PER_TASK  start: $(date)"
mkdir -p "$(dirname "$STAGE")"
# Stage: everything the build needs, including gitignored inputs (venv, asm, permuter, roms).
rsync -a --delete --exclude 'nonmatchings/' --exclude '.claude/worktrees/' "$SRC_REPO/" "$STAGE/"
cd "$STAGE"
find build -exec touch {} + 2>/dev/null || true

# Gate: the staged tree must build byte-identical before anyone works on it.
env PATH="$STAGE/.venv/bin:$PATH" make -j"$SLURM_CPUS_PER_TASK" PYTHON="$STAGE/.venv/bin/python3" 2>&1 | tail -3
grep -q OK <(env PATH="$STAGE/.venv/bin:$PATH" make PYTHON="$STAGE/.venv/bin/python3" 2>&1 | tail -1) || { echo "BUILD NOT OK"; exit 1; }

# Permuter farm: tier-1 regalloc near misses. Enable each draft with a bare `#if 1` in the
# staged copy only (never commit that). 16 workers x 6 funcs = 96 cores.
FUNCS=(
  func_81002530:src/fragments/31/fragment31_2577F0.c
  func_81003A54:src/fragments/31/fragment31_258080.c
  func_88206110:src/fragments/23/fragment23_1AE680.c
  func_8436C6A4:src/fragments/62/fragment62_356730.c
  func_8437FD74:src/fragments/62/fragment62_361050.c
  func_80044EA4:src/45720.c
)
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
bash "$STAGE/matching_notes/permuter_farm.sh" "$STAGE" "$WORKERS" 70 "${FUNCS[@]}"
# Undo the #if 1 edits so the staged tree is clean for agents / cherry-picks.
(cd "$STAGE" && git checkout -- src/)
echo "done: $(date)"
