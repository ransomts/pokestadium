#!/usr/bin/env python3
"""Batch-test text-replacement variants of one function and print each diff.

usage: matching_notes/var.py src/path/file.c func_XXXXXXXX specfile [max_lines] [--keep]

specfile: variants separated by lines "=====". Each variant is one or more edits
separated by "-----" lines; each edit is  <old text>\n@@@\n<new text>.
Old text is searched for starting at the function's definition. The file is
restored after each variant unless --keep is given (then the last one stays).
The function block must already be enabled with a bare `#if 1`.
"""
import os
import subprocess
import sys

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
FD = os.path.join(REPO, "matching_notes", "fd.sh")

f, func, spec = sys.argv[1:4]
lines = sys.argv[4] if len(sys.argv) > 4 and sys.argv[4] != "--keep" else "12"
path = os.path.join(REPO, f)
orig = open(path).read()
for vi, variant in enumerate(open(spec).read().split("=====\n")):
    if not variant.strip():
        continue
    s = orig
    ok = True
    for pair in variant.split("-----\n"):
        if not pair.strip():
            continue
        old, new = pair.split("@@@\n")
        j = s.find(old, s.index(func + "("))
        if j < 0:
            print("NOT FOUND:", old)
            ok = False
            break
        s = s[:j] + new + s[j + len(old):]
    if not ok:
        continue
    open(path, "w").write(s)
    os.utime(path, None)  # NFS: make the rewrite visible to make NOW
    obj = os.path.join(REPO, "build", f[:-2] + ".o")
    if os.path.exists(obj):
        os.remove(obj)  # NFS stale-object trap: never trust a cached .o (see IDO_TRICKS)
    print("=== variant", vi, variant.strip().splitlines()[0][:60], flush=True)
    subprocess.run([FD, f, func, lines])
    if "--keep" not in sys.argv:
        open(path, "w").write(orig)
