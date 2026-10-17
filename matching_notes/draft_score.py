#!/usr/bin/env python3
"""Score a file's NON_MATCHING draft for one function with the FULL diff (no -s, uncapped,
forced rebuild), restoring the file. The only ranking scale used in this repo (2026-10-17):
capped/stop-at-ret numbers are not comparable and have inverted decisions before.

usage: draft_score.py src/path/file.c func_XXXXXXXX
"""
import os
import re
import subprocess
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
REPO = os.path.dirname(HERE)
src, func = sys.argv[1:3]
path = os.path.join(REPO, src)
orig = open(path).read()
if "#ifdef NON_MATCHING" in orig:
    m = re.search(r"^[^\n;{}#]*\b%s\s*\([^;{]*\)\s*\{" % re.escape(func), orig, re.M)
    if not m:
        sys.exit(f"{func} not found")
    j = orig.rfind("#ifdef NON_MATCHING", 0, m.start())
    t = orig[:j] + "#if 1" + orig[j + len("#ifdef NON_MATCHING"):]
else:
    t = orig
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
