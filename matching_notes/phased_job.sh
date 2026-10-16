#!/bin/bash
#SBATCH --job-name=pokestadium-phased
#SBATCH --partition=work1
#SBATCH --account=cuuser_cpsc_ads_s27
#SBATCH --constraint="cpu_gen_genoa|cpu_gen_sapphirerapids|cpu_gen_icelake"
#SBATCH --nodes=1 --ntasks=1 --cpus-per-task=32 --mem=64G
#SBATCH --time=02:00:00
#SBATCH --output=%x_%j.out
#
# Phase D build gate: try each asm data file migration (datamig.py apply) in its own staged copy,
# `make extract && make`, keep the patches that print OK, then validate all of them together.
# Submit from the repo root (output lands in scratch/phased/):
#   sbatch --chdir=$PWD/scratch/phased matching_notes/phased_job.sh asm/us/data/rom_data_7A110.data.s ...
# No targets = every non-header/reloc file under asm/us/data (datamig refuses the unready ones fast).
# Results: scratch/phased/<jobid>/{summary.txt, <stem>.log, <stem>.patch, combined.patch}.
# Uses ~/Code/pokestadium on NFS only to read the tree and write results; all builds run on
# node-local $TMPDIR. /scratch is avoided because it gives stale file handles on some nodes.
set -u
SRC_REPO=${SRC_REPO:-$HOME/Code/pokestadium}
JOB=${SLURM_JOB_ID:-local$$}
OUT=$SRC_REPO/scratch/phased/$JOB
STAGE=${TMPDIR:-/tmp}/phased_$JOB
CPUS=${SLURM_CPUS_PER_TASK:-8}
PER=${PER_TARGET_J:-8}                      # make -j per target
PAR=$(( CPUS / PER )); [ "$PAR" -lt 1 ] && PAR=1
export PATH="$SRC_REPO/.venv/bin:$HOME/local/bin:$HOME/.local/bin:/usr/local/bin:/usr/bin:/bin"
mkdir -p "$OUT" "$STAGE"
echo "node $(hostname) cpus $CPUS par $PAR start $(date)" | tee "$OUT/summary.txt"

# Stage the working tree (incl. uncommitted edits and gitignored build inputs) once.
rsync -a --exclude '/scratch/' --exclude '.claude/' --exclude '/asm/us/nonmatchings/' \
  "$SRC_REPO/" "$STAGE/base/"
cd "$STAGE/base" || exit 1
rm -f .venv && ln -s "$SRC_REPO/.venv" .venv 2>/dev/null || true
git add -A >/dev/null 2>&1; git -c user.name=phased -c user.email=phased@local commit -qm "phased base" >/dev/null 2>&1
(make extract >/dev/null 2>&1 && make -j"$CPUS" 2>&1) > "$OUT/base_build.log"
if ! tail -1 "$OUT/base_build.log" | grep -q ': OK'; then
  echo "BASE BUILD NOT OK - see base_build.log" | tee -a "$OUT/summary.txt"; exit 1
fi
echo "base: OK" | tee -a "$OUT/summary.txt"

if [ $# -eq 0 ]; then
  set -- $(find asm/us/data -name '*.s' ! -name '*_header.s' ! -name '*_reloc.s' | sort)
fi

try_one() {  # $1 = asm data file (repo-relative)
  local t=$1 stem; stem=$(basename "$t" .s)
  local W="$STAGE/t_$stem"
  cp -a "$STAGE/base" "$W"; cd "$W" || return
  local log="$OUT/$stem.log"
  if ! .venv/bin/python3 matching_notes/datamig.py apply "$t" > "$log" 2>&1; then
    echo "REFUSED $t"; rm -rf "$W"; return
  fi
  git diff > "$OUT/$stem.patch"
  local t0=$SECONDS
  { make extract && make -j"$PER"; } >> "$log" 2>&1
  if tail -1 "$log" | grep -q ': OK'; then
    echo "OK      $t  ($((SECONDS - t0)) s)"
  else
    { echo "--- first diff:"; .venv/bin/python3 tools/first_diff.py 2>&1 | head -20; } >> "$log"
    mv "$OUT/$stem.patch" "$OUT/$stem.patch.failed"
    echo "FAILED  $t  ($((SECONDS - t0)) s; see $stem.log)"
  fi
  cd "$STAGE"; rm -rf "$W"
}
export -f try_one; export STAGE OUT PER
printf '%s\n' "$@" | xargs -P "$PAR" -I{} bash -c 'try_one {}' | tee -a "$OUT/summary.txt"

# All passing targets together: re-run datamig in sequence on the base (patches made against the same
# base collide on symbol_addrs.txt / undefined_syms.ld appends, and --3way leaves conflict markers).
cd "$STAGE/base" || exit 1
n=0
for p in "$OUT"/*.patch; do
  [ -e "$p" ] || continue
  t=$(grep -m1 -oE "^asm/us/data/[^:]+\.s" "${p%.patch}.log")
  if .venv/bin/python3 matching_notes/datamig.py apply "$t" >> "$OUT/combined_apply.log" 2>&1; then n=$((n + 1)); else echo "combine: $t refused on top of the others" | tee -a "$OUT/summary.txt"; fi
done
if [ "$n" -gt 0 ]; then
  git diff HEAD > "$OUT/combined.patch"
  (make extract >/dev/null 2>&1 && make -j"$CPUS" 2>&1) > "$OUT/combined_build.log"
  if tail -1 "$OUT/combined_build.log" | grep -q ': OK'; then
    echo "combined ($n patches): OK -> apply with: git apply $OUT/combined.patch" | tee -a "$OUT/summary.txt"
  else
    echo "combined ($n patches): NOT OK - see combined_build.log" | tee -a "$OUT/summary.txt"
  fi
fi
echo "end $(date)" | tee -a "$OUT/summary.txt"
rm -rf "$STAGE"
