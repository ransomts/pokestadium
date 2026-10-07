#!/bin/bash
# Run decomp-permuter on several functions in parallel, re-seeded from the CURRENT draft.
#
# usage: matching_notes/permuter_farm.sh <repo> <workers_per_func> <hours> func_X:src/a.c [func_Y:src/b.c ...]
#
# - <repo> must be a full checkout with .venv, asm/, tools/permuter (symlinks are fine).
# - Each function's #ifdef NON_MATCHING draft must be enabled with a bare `#if 1` in <repo>
#   before calling (import.py reads the function body from the C file as compiled).
# - Work dir: $FARM_DIR (default /local_scratch/$USER/permuter). Improved candidates land in
#   $FARM_DIR/nonmatchings/<func>/output-<score>-<n>/source.c and are rsynced to
#   $SAVE_DIR (default /scratch/$USER/permuter_best) every 10 minutes and at the end.
# - Judge candidates with matching_notes/fd.sh, not the permuter score (statics inflate it).
set -u
REPO=$(readlink -f "$1"); WORKERS=$2; HOURS=$3; shift 3
FARM_DIR=${FARM_DIR:-/local_scratch/$USER/permuter}
SAVE_DIR=${SAVE_DIR:-/scratch/$USER/permuter_best}
PY="$REPO/.venv/bin/python3"
export PATH="$REPO/.venv/bin:$HOME/local/bin:/usr/local/bin:/usr/bin:/bin"
mkdir -p "$FARM_DIR" "$SAVE_DIR"
cd "$FARM_DIR" || exit 1
ln -sfn "$REPO/tools" tools 2>/dev/null

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
    echo "starting $func with $WORKERS workers"
    timeout "${HOURS}h" "$PY" "$REPO/tools/permuter/permuter.py" "nonmatchings/$func" \
        --stack-diffs --best-only --stop-on-zero --no-context-output -j"$WORKERS" \
        > "nonmatchings/$func.log" 2>&1 &
    pids+=($!)
done

sync_best() {
    for d in nonmatchings/*/; do
        f=$(basename "$d")
        mkdir -p "$SAVE_DIR/$f"
        rsync -a --include='output-*/***' --include='base.c' --include='*.log' --exclude='*' \
            "$d" "$SAVE_DIR/$f/" 2>/dev/null
        cp -f "nonmatchings/$f.log" "$SAVE_DIR/$f/" 2>/dev/null
    done
}
while kill -0 "${pids[@]}" 2>/dev/null; do sleep 600; sync_best; done
sync_best
echo "farm done; best candidates in $SAVE_DIR"
for d in nonmatchings/*/; do
    f=$(basename "$d"); best=$(ls -d "$d"output-* 2>/dev/null | sed 's/.*output-//' | sort -t- -k1,1n | head -1)
    echo "$f best=${best:-none}"
done
