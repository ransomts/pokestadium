#!/usr/bin/env python3
"""Splice a permuter candidate's function into its draft and diff it (file restored unless --keep).

usage: try_candidate.py src/path/file.c func_XXXXXXXX path/to/output-N/source.c [--keep]

Copies only the function definition from the candidate (the farm strips data into externs, so
nothing else in source.c is usable), turns the draft's `#ifdef NON_MATCHING` into a bare `#if 1`,
and runs fd.sh. A 0 here is not a match: the full `make` must print OK (fd.sh uses -s).
"""
import os
import re
import subprocess
import sys

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))


def func_span(text, func):
    """(start, end) of `<type> func(...) { ... }`, end just past the closing brace."""
    m = re.search(r"^[^\n;{}#]*\b%s\s*\([^;{]*\)\s*\{" % re.escape(func), text, re.M)
    if not m:
        sys.exit(f"{func} definition not found")
    depth, i = 0, m.end() - 1
    while i < len(text):
        depth += {"{": 1, "}": -1}.get(text[i], 0)
        if depth == 0:
            return m.start(), i + 1
        i += 1
    sys.exit(f"unbalanced braces in {func}")


src, func, cand = sys.argv[1:4]
path = os.path.join(REPO, src)
orig = open(path).read()
c = open(cand).read()
a, b = func_span(c, func)
new_fn = c[a:b]
s, e = func_span(orig, func)
_m = [m for m in re.finditer(r"^#ifdef NON_MATCHING[ \t]*$", orig[:s], re.M)]
j = _m[-1].start() if _m else -1
if j < 0 or "#endif" in orig[j:s]:
    sys.exit(f"{func} has no NON_MATCHING draft")
t = orig[:j] + "#if 1" + orig[j + len("#ifdef NON_MATCHING"):s] + new_fn + orig[e:]
open(path, "w").write(t)
try:
    subprocess.run([os.path.join(REPO, "matching_notes", "fd.sh"), src, func, "40"])
finally:
    if "--keep" not in sys.argv:
        open(path, "w").write(orig)
