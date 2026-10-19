#!/usr/bin/env python3
"""Expand the shared-name safety using per-file resolved owner sets.

Rule (v2, built on field_resolver.py output):
  For field X and owner T: X is renamable for T iff EVERY file whose resolved
  owner set O(F) contains T has O(F) == {T} exactly (no mixed-owner files for
  T - a mixed file cannot be file-scoped safely since T's decl rename makes
  ALL of T's sites need the new name).
  Unresolved (?) sites park the name only if their file's include-reach could
  see T (conservative; ? files that cannot reach T are ignored).

Outputs (overwrites what rename.py consumes):
  matching_notes/field_scopes.tsv     - {typedef: [files]} expanded scopes
  matching_notes/field_safe_names.tsv  - (typedef, name) safe pairs

Usage: field_safe_expander.py
"""
import glob
import os
import re
import sys
from collections import defaultdict

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
SITES = os.path.join(REPO, "matching_notes", "field_resolved_sites.tsv")
IDENT = re.compile(r"[A-Za-z_][A-Za-z0-9_]*")


def main():
    # 1. load resolved sites
    name_file_owners = defaultdict(dict)  # name -> file -> owners set
    for line in open(SITES, errors="replace"):
        if line.startswith("#"):
            continue
        p = line.rstrip("\n").split("\t")
        if len(p) != 3:
            continue
        name_file_owners[p[0]][p[1]] = set(p[2].split(","))

    # 2. struct layouts: who DECLARES each name (decl sites are unambiguous)
    import importlib.util
    spec = importlib.util.spec_from_file_location(
        "hfg", os.path.join(REPO, "matching_notes", "rename_hippo_field_gen.py"))
    hfg = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(hfg)
    decl_owners = defaultdict(set)  # name -> {typedef}
    decl_header = {}  # typedef -> header path
    for p in glob.glob(os.path.join(REPO, "src", "**", "*.h"), recursive=True) + \
              glob.glob(os.path.join(REPO, "include", "**", "*.h"), recursive=True):
        rel = os.path.relpath(p, REPO)
        t = open(p, errors="replace").read()
        for name, body in hfg.struct_blocks(t):
            for m in hfg.FIELD_RE.finditer(body):
                decl_owners[m.group(3)].add(name)
                decl_header.setdefault(name, rel)

    # 3. include-reach (for the ?-site park check)
    texts = {}
    for root in ("src", "include"):
        for dp, _d, fs in os.walk(os.path.join(REPO, root)):
            for fn in fs:
                if fn.endswith((".c", ".h")):
                    rel = os.path.relpath(os.path.join(dp, fn), REPO)
                    texts[rel] = open(os.path.join(dp, fn), errors="replace").read()
    INC = re.compile(r'#include\s+"([^"]+)"')

    def resolve_inc(rel, inc):
        base = os.path.dirname(rel)
        for c in (os.path.normpath(os.path.join(base, inc)), os.path.normpath(inc),
                  os.path.normpath("src/" + inc), os.path.normpath("include/" + inc)):
            if c in texts:
                return c
        return None

    direct = {}
    for rel in texts:
        incs = set()
        for m in INC.finditer(texts[rel]):
            r = resolve_inc(rel, m.group(1))
            if r and r != rel:
                incs.add(r)
        direct[rel] = incs

    def closure(rel, cache={}):
        if rel in cache:
            return cache[rel]
        seen, stack = {rel}, list(direct.get(rel, ()))
        while stack:
            h = stack.pop()
            if h in seen:
                continue
            seen.add(h)
            stack.extend(direct.get(h, ()))
        cache[rel] = seen
        return seen

    # 4. the v2 rule
    scopes = defaultdict(set)   # typedef -> files
    safe_pairs = set()
    for name in sorted(name_file_owners):
        files = name_file_owners[name]
        # candidate owners: any resolved non-? owner
        owners = set()
        for f, os_ in files.items():
            owners |= (os_ - {"?"})
        for t in sorted(owners):
            # files that must be rewritten for T: all where T in O(F)
            t_files = {f for f, os_ in files.items() if t in os_}
            ok = True
            for f in t_files:
                if files[f] != {t}:
                    ok = False  # mixed-owner file
                    break
            if not ok:
                continue
            # unresolved (?) files: park if they can reach T's decl header
            hdr = decl_header.get(t)
            for f, os_ in files.items():
                if "?" in os_ and hdr and hdr in closure(f):
                    ok = False
                    break
            if not ok:
                continue
            # decl sites: only T declares the name among header-declared structs?
            # (if two structs in DIFFERENT headers declare X, both decl sites
            # rename via their own header passes - that's fine; the header
            # decl regex only matches X inside T's block via _struct_spans)
            for f in t_files:
                scopes[t].add(f)
            if hdr:
                scopes[t].add(hdr)
            safe_pairs.add((t, name))

    with open(os.path.join(REPO, "matching_notes", "field_scopes.tsv"), "w") as f:
        for t in sorted(scopes):
            f.write(f"{t}\t{','.join(sorted(scopes[t]))}\n")
    with open(os.path.join(REPO, "matching_notes", "field_safe_names.tsv"), "w") as f:
        for t, n in sorted(safe_pairs):
            f.write(f"{t}\t{n}\n")
    print(f"v2 safe pairs: {len(safe_pairs)} (was 138); scoped types: {len(scopes)}")


if __name__ == "__main__":
    main()
