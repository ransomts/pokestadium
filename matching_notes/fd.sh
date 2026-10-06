#!/bin/bash
# Build one object and diff one function against the target.
# usage: matching_notes/fd.sh src/path/file.c func_XXXXXXXX [max_lines]
# The function's block must be enabled for the build (temporarily change its
# `#ifdef NON_MATCHING` to a bare `#if 1` -- NOT `#if 1 // comment`, IDO's cpp mishandles that).
# Prints the score line and only the differing lines (r=reg, i=imm, s=stack, |/</> = other).
cd "$(dirname "$0")/.." || exit 1
REPO=$PWD
o=build/${1%.c}.o
env PATH="$REPO/.venv/bin:/usr/local/bin:/usr/bin:/bin" make "$o" PYTHON="$REPO/.venv/bin/python3" 2>&1 \
    | grep -v "cfe: Warning" | grep -E "rror" | head
"$REPO/.venv/bin/python3" -W ignore tools/asm-differ/diff.py -o "$2" -s --format plain > /tmp/fd_last_"$2".txt 2>&1
grep -E "Score|^\S*\s*[0-9a-f]+:\s.*\s(r|i|s|<|>|\|)\s" /tmp/fd_last_"$2".txt | head -"${3:-40}"
