#!/usr/bin/env python3
"""Adopt a permuter candidate as the real C: splice it into the draft, drop the NON_MATCHING wrapper,
and run the full make. Leaves the file changed only if the ROM prints OK (otherwise restores it).

usage: adopt_candidate.py src/path/file.c func_XXXXXXXX path/to/source.c
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
subprocess.run([sys.executable, os.path.join(HERE, "try_candidate.py"), src, func, cand, "--keep"],
               stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
t = open(path).read()
m = re.search(r"^[^\n;{}#]*\b%s\s*\([^;{]*\)\s*\{" % re.escape(func), t, re.M)
j = t.rfind("#if 1\n", 0, m.start())
e = re.compile(r"^#else\n.*?^#endif\n", re.M | re.S).search(t, m.start())
if j < 0 or not e or "GLOBAL_ASM" not in e.group(0) or func not in e.group(0):
    open(path, "w").write(orig)
    sys.exit("draft wrapper not found; file restored")
t = t[:j] + t[j + len("#if 1\n"):e.start()] + t[e.end():]
open(path, "w").write(t)
env = dict(os.environ, PATH=f"{REPO}/.venv/bin:{os.path.expanduser('~')}/local/bin:" + os.environ["PATH"])
r = subprocess.run(["make", "-j4", f"PYTHON={REPO}/.venv/bin/python3"], cwd=REPO, env=env,
                   capture_output=True, text=True)
last = (r.stdout.strip().splitlines() or [""])[-1]
print(last)
if not last.endswith(": OK"):
    open(path, "w").write(orig)
    print("not OK: file restored")
    sys.exit(1)
