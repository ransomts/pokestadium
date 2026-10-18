#!/usr/bin/env python3
"""Splice a permuter candidate's function into the NON_MATCHING draft (keeps the wrapper).
usage: splice_draft.py src/path/file.c func_XXXXXXXX path/to/source.c
"""
import re
import sys

src, func, cand = sys.argv[1:4]
orig = open(src).read()
c = open(cand).read()


def func_span(text, func):
    m = re.search(r"^[^\n;{}#]*\b%s\s*\([^;{]*\)\s*\{" % re.escape(func), text, re.M)
    if not m:
        sys.exit(f"{func} definition not found")
    depth, i = 0, m.end() - 1
    while i < len(text):
        depth += {"{": 1, "}": -1}.get(text[i], 0)
        if depth == 0:
            return m.start(), i + 1
        i += 1
    sys.exit("unbalanced braces")


a, b = func_span(c, func)
new_fn = c[a:b]
s, e = func_span(orig, func)
_m = [m for m in re.finditer(r"^#ifdef NON_MATCHING[ \t]*$", orig[:s], re.M)]
j = _m[-1].start() if _m else -1
if j < 0 or "#endif" in orig[j:s]:
    sys.exit(f"{func} has no NON_MATCHING draft")
open(src, "w").write(orig[:s] + new_fn + orig[e:])
print(f"spliced {func} ({b-a} chars) into {src}")
