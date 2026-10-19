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

    # include-transitive reach: this codebase's .c files pass structs via
    # parameters and never name the typedef - the type appears only in the
    # headers they include (the gsm_decoder lesson). A file REACHES a type if
    # it or its transitive includes declare/mention it.
    INC = re.compile(r'#include\s+"([^"]+)"')

    def resolve(rel, inc):
        # resolve relative to the includer's dir (flat style), then the roots
        base = os.path.dirname(rel)
        cands = [os.path.normpath(os.path.join(base, inc))]
        for root in ("", "src/", "include/"):
            cands.append(os.path.normpath(os.path.join(root, inc)))
        for c in cands:
            if c in idents_per_file:
                return c
        for c in cands:
            if os.path.exists(os.path.join(REPO, c)):
                return os.path.relpath(os.path.join(REPO, c), REPO)
        return None

    direct = {}
    texts = {}
    for rel in idents_per_file:
        if rel not in texts:
            texts[rel] = open(os.path.join(REPO, rel), errors="replace").read()
    for rel in idents_per_file:
        incs = set()
        for m in INC.finditer(texts[rel]):
            r = resolve(rel, m.group(1))
            if r and r != rel:
                incs.add(r)
        direct[rel] = incs

    def closure(rel, _cache={}):
        if rel in _cache:
            return _cache[rel]
        seen = {rel}
        stack = list(direct.get(rel, ()))
        while stack:
            h = stack.pop()
            if h in seen:
                continue
            seen.add(h)
            stack.extend(direct.get(h, ()))
        _cache[rel] = seen
        return seen

    type_reach = defaultdict(set)  # typedef -> files whose closure mentions it
    for rel in idents_per_file:
        cl = closure(rel)
        cl_texts = texts[rel] + "".join(texts.get(h, "") for h in cl if h != rel)
        cl_idents = set(IDENT.findall(cl_texts))
        for tn in types & cl_idents:
            type_reach[tn].add(rel)

    scopes = {}
    safe_names = set()  # (typedef, field name) pairs that passed BOTH checks
    parked_unknown_owner = []
    # users(X): files with `.X`/`->X` accesses - the owner is knowable only if
    # the file's include-closure reaches EXACTLY ONE of the sharing typedefs
    user_pat = {fn: re.compile(r"[.>]" + re.escape(fn) + r"(?![A-Za-z0-9_])")
                for fn in shared}
    name_users = {fn: {rel for rel in idents_per_file
                       if user_pat[fn].search(texts[rel])}
                  for fn in shared}
    for fname, locs in sorted(shared.items()):
        owners = {tn for tn, _ in locs}
        unknown = set()
        for uf in name_users[fname]:
            hits = [tn for tn in owners if uf in type_reach.get(tn, set())]
            if len(hits) != 1:
                unknown.add(uf)
        if unknown:
            parked_unknown_owner.append(fname)
            continue
        per_type = defaultdict(set)
        for tn, _ in locs:
            per_type[tn] |= type_reach.get(tn, set())
        sets = list(per_type.values())
        if all(not (a & b) for i, a in enumerate(sets) for b in sets[i + 1:]):
            for tn in per_type:
                safe_names.add((tn, fname))
            for tn, fs in per_type.items():
                if len(fs) >= args.min_files:
                    scopes[tn] = sorted(set(fs) | set(scopes.get(tn, [])))
    with open(OUT, "w") as f:
        for tn in sorted(scopes):
            f.write(f"{tn}\t{','.join(scopes[tn])}\n")
    with open(OUT.replace("field_scopes.tsv", "field_safe_names.tsv"), "w") as f:
        for tn, fn in sorted(safe_names):
            f.write(f"{tn}\t{fn}\n")
    n_fields = sum(len(v) for v in shared.values())
    print(f"shared unk_ names: {len(shared)} ({n_fields} fields); "
          f"parked (unknown owner): {len(parked_unknown_owner)}; "
          f"scopes written for {len(scopes)} struct types; "
          f"safe (type, name) pairs: {len(safe_names)} -> {OUT}")


if __name__ == "__main__":
    main()
