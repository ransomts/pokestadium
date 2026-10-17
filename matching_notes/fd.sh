#!/bin/bash
# Build one object and diff one function against the target.
# usage: matching_notes/fd.sh src/path/file.c func_XXXXXXXX [max_lines]
# The function's block must be enabled for the build (temporarily change its
# `#ifdef NON_MATCHING` to a bare `#if 1` -- NOT `#if 1 // comment`, IDO's cpp mishandles that).
# Prints the score line and only the differing lines (r=reg, i=imm, s=stack, |/</> = other).
#
# Score policy (2026-10-17, after three "cap illusion" incidents): FULL score only --
# NO -s (stop-at-ret hides diffs after early returns) and --max-lines 30000 (diff.py's
# 1000-line default silently truncates big functions, and the truncation is not monotone:
# a regression can look like an improvement). The canonical numbers in NOTES.md are full
# scores; never rank against a capped/stop-at-ret number. A 0 here is NOT proof of a match
# (sym+off relocations compare equal): only a full `make` printing OK is.
cd "$(dirname "$0")/.." || exit 1
REPO=$PWD
o=build/${1%.c}.o
rm -f "$o"   # NFS stale-object trap (2026-10-17): make on NFS sometimes skips a needed rebuild
             # and fd.sh then diffs a stale .o -- always force it.
env PATH="$REPO/.venv/bin:$HOME/local/bin:/usr/local/bin:/usr/bin:/bin" make "$o" PYTHON="$REPO/.venv/bin/python3" 2>&1 \
    | grep -v "cfe: Warning" | grep -E "rror" | head
"$REPO/.venv/bin/python3" -W ignore tools/asm-differ/diff.py -o "$2" --format plain --max-lines 30000 > /tmp/fd_last_"$2".txt 2>&1
grep -E "Score|CURRENT \(|^\S*\s*[0-9a-f]+:\s.*\s(r|i|s|<|>|\|)\s" /tmp/fd_last_"$2".txt | head -"${3:-40}"
grep -q "CURRENT (0)" /tmp/fd_last_"$2".txt && \
    echo ">> score 0 is NOT proof of a match (relocations compare equal): run the full make and require ': OK'"
