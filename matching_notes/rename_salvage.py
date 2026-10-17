#!/usr/bin/env python3
"""Salvage rename-agent fragments: normalize literal-\\t output, dedupe, quality-filter.

usage: rename_salvage.py <batch-id> '<frag-dir>/<prefix>_*.raw' <out-merged.tsv>
Writes TSV rows (old, new, batch, also, justification, pending) with justification >= 15 chars,
deduped by old and new. Feed the result into renames.tsv then run rename.py plan/apply.
"""
import glob
import re
import sys

BATCH = sys.argv[1]
pat_old = re.compile(r"(func_|D_|unk_)[A-Za-z0-9_]+")
merged = []
for raw_path in sorted(glob.glob(sys.argv[2])):
    text = open(raw_path).read().replace("\\t", "\t").replace("\\n", "\n")
    for line in text.splitlines():
        line = line.strip()
        if not line or line.startswith(("#", "old\t", "```")):
            continue
        parts = [p.strip() for p in line.split("\t")]
        if len(parts) < 3:
            continue
        old, new = parts[0], parts[1]
        if not pat_old.fullmatch(old) or not re.fullmatch(r"[A-Za-z_][A-Za-z0-9_]*", new):
            continue
        if len(parts) >= 6:
            also, just = parts[3], parts[4]
        elif len(parts) == 5:
            also, just = "", parts[3]
        else:
            also, just = "", parts[2]
        just = just.encode("ascii", "replace").decode().strip()
        if just.lower().endswith(" pending"):
            just = just[:-7].strip()
        also = also.encode("ascii", "replace").decode().strip()
        if len(just) < 15:
            continue  # quality bar
        merged.append(f"{old}\t{new}\t{BATCH}\t{also}\t{just}\tpending")

seen_old, seen_new, out = set(), set(), []
for line in merged:
    p = line.split("\t")
    if p[0] in seen_old or p[1] in seen_new:
        continue
    seen_old.add(p[0])
    seen_new.add(p[1])
    out.append(line)
open(sys.argv[3], "w").write("\n".join(out) + "\n")
print(f"{len(out)} rows merged (from {len(merged)} raw)")
