#!/bin/bash
# One-command morning verdict on the farm10 chain. usage: matching_notes/morning_check.sh
cd "$(dirname "$0")" || exit 1
echo "=== jobs"
squeue -u "$USER" -o "%.10i %.14j %.8T %.10M %R" | grep -E "JOBID|farm"
echo
echo "=== chain evidence (empty = phase 2 not started yet / nothing fired)"
grep -h "farm hours\|phases left\|diversity seed\|focused start" /scratch/$USER/pokestadium_*.out 2>/dev/null | tail -8
echo "--- mid-run re-seeds (era-gated; the 2026-10-17 pre-noon churn on 88805AEC is fixed)"
grep -h "re-seed " /scratch/$USER/pokestadium_*.out 2>/dev/null | grep -v "17:2[0-9]\|17:1[0-9]" | tail -6
echo
echo "=== bests (fd-metric caveats apply; judge survivors with fd.sh)"
bash farm_status.sh 2>/dev/null | grep -E "FUNC|func_(80034348|8004A89C|88304850|88805AEC|8437B0CC)__f[abc]" | awk '!seen[$1]++'
echo
echo "=== verdict hints"
n=$(squeue -h -u "$USER" -n farm10-a,farm10-b,farm10-c -t R | wc -l)
[ "$n" -eq 0 ] && echo "WARNING: no farm jobs running - the chain broke (check /scratch/\$USER/pokestadium_*.out tails, then resubmit)"
[ "$n" -gt 0 ] && echo "$n farm job(s) running; if a phase failed to chain, resubmit per NOTES.md farm10 recipe"
grep -l "BUILD NOT OK" /scratch/$USER/pokestadium_*.out 2>/dev/null | while read -r f; do echo "WARNING: build gate failed in $f (rename wave raced the phase start?)"; done
