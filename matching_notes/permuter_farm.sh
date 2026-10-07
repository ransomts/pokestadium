#!/bin/bash
# Run decomp-permuter on several functions in parallel, seeded from the best known source.
#
# usage: matching_notes/permuter_farm.sh <repo> <workers_per_func> <hours> func_X:src/a.c [func_Y:src/b.c ...]
#
# - <repo> must be a full checkout with .venv, asm/, tools/permuter (symlinks are fine).
# - Each function's #ifdef NON_MATCHING draft must be enabled with a bare `#if 1` in <repo>
#   before calling (import.py reads the function body from the C file as compiled).
# - Work dir: $FARM_DIR (default $TMPDIR/permuter, the job-private local SSD). Improved candidates
#   land in $FARM_DIR/nonmatchings/<func>/output-<score>-<n>/source.c and are rsynced to
#   $SAVE_DIR (default /scratch/$USER/permuter_best) every $SYNC_SECS (600) and at the end.
# - Checkpoint/restart: the saved candidates ARE the checkpoint (the search itself is memoryless).
#   On start, if $SAVE_DIR/<func>/output-*/source.c exists, the lowest-scoring one replaces the
#   imported base.c (RESEED=0 disables). Delete $SAVE_DIR/<func> to start from the draft again.
# - Observability: each <func>.log has timestamped improvement lines plus a STATUS snapshot
#   every $SNAP_SECS (300) with iterations, errors and it/s. Summarise with farm_status.sh.
# - Judge candidates with matching_notes/fd.sh, not the permuter score (statics inflate it).
set -u
REPO=$(readlink -f "$1"); WORKERS=$2; HOURS=$3; shift 3
FARM_DIR=${FARM_DIR:-${TMPDIR:-/tmp}/permuter}
SAVE_DIR=${SAVE_DIR:-/scratch/$USER/permuter_best}
SYNC_SECS=${SYNC_SECS:-600}
SNAP_SECS=${SNAP_SECS:-300}
RESEED=${RESEED:-1}
HERE=$(cd "$(dirname "$0")" && pwd)
PY="$REPO/.venv/bin/python3"
export PATH="$REPO/.venv/bin:$HOME/local/bin:/usr/local/bin:/usr/bin:/bin"
export PYTHONUNBUFFERED=1
mkdir -p "$FARM_DIR" "$SAVE_DIR"
cd "$FARM_DIR" || exit 1
ln -sfn "$REPO/tools" tools 2>/dev/null
shopt -s nullglob

best_saved() {  # print path of the lowest-scoring saved source.c for $1, if any
    local best= bestv=
    for s in "$SAVE_DIR/$1"/output-*/score.txt; do
        v=$(cat "$s")
        if [ -z "$bestv" ] || [ "$v" -lt "$bestv" ]; then bestv=$v; best=${s%score.txt}source.c; fi
    done
    [ -n "$best" ] && [ -f "$best" ] && echo "$best"
}

pids=()
for spec in "$@"; do
    func=${spec%%:*}; src=${spec#*:}
    asm=$(find "$REPO/asm/us/nonmatchings" -name "$func.s" | head -1)
    if [ -z "$asm" ]; then echo "no asm for $func, skipping"; continue; fi
    rm -rf "nonmatchings/$func" "$REPO/nonmatchings/$func"   # else import.py appends -1, -2, ...
    (cd "$REPO" && "$PY" tools/permuter/import.py "$src" "$asm") || { echo "import failed: $func"; continue; }
    # import.py writes into $REPO/nonmatchings/<func>; move it next to the farm.
    mkdir -p nonmatchings; mv "$REPO/nonmatchings/$func" "nonmatchings/$func"
    # preprocess.sh needs -o before the input (see IDO_TRICKS.md).
    sed -i 's/-O2 "$INPUT" -o "$OUTPUT"/-O2 -o "$OUTPUT" "$INPUT"/' "nonmatchings/$func/compile.sh"
    rm -f "nonmatchings/$func/-I"
    seed=$( [ "$RESEED" != 0 ] && best_saved "$func" )
    if [ -n "$seed" ]; then
        cp "nonmatchings/$func/base.c" "nonmatchings/$func/base.draft.c"
        cp "$seed" "nonmatchings/$func/base.c"
        echo "$func: re-seeded from $seed"
    fi
    echo "starting $func with $WORKERS workers"
    ( timeout "${HOURS}h" "$PY" "$REPO/tools/permuter/permuter.py" "nonmatchings/$func" \
          --stack-diffs --best-only --stop-on-zero -j"$WORKERS" 2>&1 \
      | "$PY" "$HERE/farm_logfilter.py" "$SNAP_SECS" > "nonmatchings/$func.log" ) &
    pids+=($!)
done
[ ${#pids[@]} -eq 0 ] && { echo "nothing started"; exit 1; }

sync_best() {
    for d in nonmatchings/*/; do
        f=$(basename "$d")
        mkdir -p "$SAVE_DIR/$f"
        rsync -a --include='output-*/***' --include='base.c' --include='base.draft.c' --exclude='*' \
            "$d" "$SAVE_DIR/$f/" 2>/dev/null
        cp -f "nonmatchings/$f.log" "$SAVE_DIR/$f/" 2>/dev/null
    done
    touch "$SAVE_DIR"
}
any_alive() { for p in "${pids[@]}"; do kill -0 "$p" 2>/dev/null && return 0; done; return 1; }
# Preemption / scancel / time limit: Slurm sends TERM (KillWait 30 s before KILL). Sync what we have.
on_term() { echo "$(date '+%F %T') TERM received, final sync"; kill "${pids[@]}" 2>/dev/null; sync_best; exit 143; }
trap on_term TERM INT HUP
while any_alive; do sleep "$SYNC_SECS" & wait $!; any_alive && sync_best; done
sync_best
echo "farm done; best candidates in $SAVE_DIR"
bash "$HERE/farm_status.sh" "$SAVE_DIR"
