#!/usr/bin/env python3
"""Generate matching_notes/field_scopes.tsv: struct-scoped file sets for
SHARED field names whose struct file-sets are provably disjoint.

rename.py's member rewrite is name-global; field_scopes.tsv scopes it per
struct type, unlocking shared unk_XX names (the Tier C shared-name class).
A scope is emitted ONLY when every struct sharing that field name has a file
set disjoint from all the others - a scoped rewrite then cannot touch another
struct's members. Overlapping names stay parked (need type-aware parsing).

Usage: field_scope_gen.py [--min-files 1]   (writes field_scopes.tsv)
"""
import argparse
import glob
import os
import re
import sys
from collections import defaultdict

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
OUT = os.path.join(REPO, "matching_notes", "field_scopes.tsv")
IDENT = re.compile(r"[A-Za-z_][A-Za-z0-9_]*")

import importlib.util
_spec = importlib.util.spec_from_file_location(
    "hfg", os.path.join(REPO, "matching_notes", "rename_hippo_field_gen.py"))
hfg = importlib.util.module_from_spec(_spec)
_spec.loader.exec_module(hfg)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--min-files", type=int, default=1)
    args = ap.parse_args()

    paths = (glob.glob(os.path.join(REPO, "src", "**", "*.c"), recursive=True)
             + glob.glob(os.path.join(REPO, "src", "**", "*.h"), recursive=True)
             + glob.glob(os.path.join(REPO, "include", "**", "*.h"), recursive=True))
    idents_per_file = {}
    fields = defaultdict(list)  # field name -> [(typedef, file)]
    for path in paths:
        rel = os.path.relpath(path, REPO)
        t = open(path, errors="replace").read()
        idents_per_file[rel] = set(IDENT.findall(t))
        for name, body in hfg.struct_blocks(t):
            for m in hfg.FIELD_RE.finditer(body):
                fields[m.group(3)].append((name, rel))

    shared = {f: locs for f, locs in fields.items()
              if len(locs) > 1 and f.startswith("unk_")}
    types = {tn for locs in shared.values() for tn, _ in locs}
    type_files = defaultdict(set)
    for rel, idents in idents_per_file.items():
        for tn in types & idents:
            type_files[tn].add(rel)

    scopes = {}
    for fname, locs in sorted(shared.items()):
        per_type = defaultdict(set)
        for tn, _ in locs:
            per_type[tn] |= type_files.get(tn, set())
        sets = list(per_type.values())
        if all(not (a & b) for i, a in enumerate(sets) for b in sets[i + 1:]):
            for tn, fs in per_type.items():
                if len(fs) >= args.min_files:
                    scopes[tn] = sorted(set(fs) | set(scopes.get(tn, [])))
    with open(OUT, "w") as f:
        for tn in sorted(scopes):
            f.write(f"{tn}\t{','.join(scopes[tn])}\n")
    n_fields = sum(len(v) for v in shared.values())
    print(f"shared unk_ names: {len(shared)} ({n_fields} fields); "
          f"scopes written for {len(scopes)} struct types -> {OUT}")


if __name__ == "__main__":
    main()
