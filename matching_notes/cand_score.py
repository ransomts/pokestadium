#!/usr/bin/env python3
"""Splice a permuter candidate's function into its draft and score it FULL (no -s, uncapped,
forced rebuild). Restores the file. Same rules as draft_score.py: the returned number is the only
ranking scale; do not compare it against the permuter's own score.

usage: cand_score.py src/path/file.c func_XXXXXXXX path/to/candidate/source.c
"""
import os
import re
import subprocess
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
REPO = os.path.dirname(HERE)
src, func, cand = sys.argv[1:4]
path = os.path.join(REPO, src)
orig = open(path).read()
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
j = orig.rfind("#ifdef NON_MATCHING", 0, s)
if j < 0 or "#endif" in orig[j:s]:
    sys.exit(f"{func} has no NON_MATCHING draft")
t = orig[:j] + "#if 1" + orig[j + len("#ifdef NON_MATCHING"):s] + new_fn + orig[e:]
open(path, "w").write(t)
try:
    o = os.path.join("build", src[:-2] + ".o")
    env = dict(os.environ,
               PATH=f"{REPO}/.venv/bin:{os.path.expanduser('~')}/local/bin:/usr/local/bin:/usr/bin:/bin")
    if os.path.exists(os.path.join(REPO, o)):
        os.remove(os.path.join(REPO, o))  # NFS stale-object trap
    r = subprocess.run(["make", o, f"PYTHON={REPO}/.venv/bin/python3"], cwd=REPO, env=env,
                       capture_output=True, text=True)
    err = [l for l in (r.stdout + r.stderr).splitlines() if "rror" in l and "cfe: Warning" not in l]
    if err:
        print("BUILD ERROR:", err[:3])
        sys.exit(1)
    d = subprocess.run([f"{REPO}/.venv/bin/python3", "-W", "ignore",
                        f"{REPO}/tools/asm-differ/diff.py", "-o", func, "--format", "plain",
                        "--max-lines", "30000"], cwd=REPO, capture_output=True, text=True)
    for l in d.stdout.splitlines():
        if l.startswith("TARGET") and "CURRENT" in l:
            print(l.strip())
finally:
    open(path, "w").write(orig)
