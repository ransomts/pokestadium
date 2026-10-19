#!/usr/bin/env python3
"""Type-aware member-access resolver - the Tier C endgame tool.

Resolves every `base->field` / `base.field` access site to its owning struct
type, so shared unk_ names become renamable even in files that mention several
structs (where file-scoping had to park them).

Resolution model (per .c file):
  1. function signatures -> param types (params named in the body's signature)
  2. local declarations inside the function body -> local types
  3. file-scope global/extern declarations (with the include closure) -> types
  4. nested chains: var->f1.f2 - f1's declared type inside var's struct is
     looked up (struct layouts come from the offset-comment declarations)
  5. typedef chasing: TYPE name; where TYPE is itself a typedef alias

Output: matching_notes/field_resolved_sites.tsv:
  fieldname<TAB>file<TAB>owner1,owner2...
(one row per (name, file); files whose sites all resolve to ONE owner are
usable for scoped rewrites even when other structs share the name).

Usage: field_resolver.py [--out FILE]
"""
import argparse
import glob
import os
import re
import sys
from collections import defaultdict

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
IDENT = r"[A-Za-z_][A-Za-z0-9_]*"
TYPE_RE = re.compile(
    r"(?:const\s+|unsigned\s+|signed\s+|struct\s+|union\s+|enum\s+)*"
    r"(?:" + IDENT + r"\s*\*+\s*|" + IDENT + r"\s+)")
ACCESS_RE = re.compile(
    r"\b(" + IDENT + r")((?:->|\.)(" + IDENT + r"))+\b")

import importlib.util
_spec = importlib.util.spec_from_file_location(
    "hfg", os.path.join(REPO, "matching_notes", "rename_hippo_field_gen.py"))
hfg = importlib.util.module_from_spec(_spec)
_spec.loader.exec_module(hfg)


def load_structs():
    """{typedef: {offset: (type, name)}} across .h and .c struct blocks."""
    structs = {}
    for p in (glob.glob(os.path.join(REPO, "src", "**", "*.h"), recursive=True)
              + glob.glob(os.path.join(REPO, "include", "**", "*.h"), recursive=True)
              + glob.glob(os.path.join(REPO, "src", "**", "*.c"), recursive=True)):
        t = open(p, errors="replace").read()
        for name, body in hfg.struct_blocks(t):
            if name in structs:
                continue
            flds = {}
            for m in hfg.FIELD_RE.finditer(body):
                flds[m.group(3)] = (m.group(2).strip(), m.group(3))
            # also map plain (non-offset) declarations inside the block
            for m in re.finditer(r"^(?:\s*)([A-Za-z_][A-Za-z0-9_ \t\*]*?)\b(" + IDENT + r")\s*(?:\[[^\]]*\])*\s*;", body, re.M):
                if m.group(2) not in flds and m.group(1).strip():
                    flds[m.group(2)] = (m.group(1).strip(), m.group(2))
            if flds:
                structs[name] = flds
    return structs


def split_functions(text):
    """[(header_span, body_start, body_end)] for top-level function definitions."""
    out = []
    sig_re = re.compile(r"^((?:" + TYPE_RE.pattern + r")?" + IDENT + r"\s*\([^;{}]*\))\s*\{", re.M)
    for m in sig_re.finditer(text):
        start = m.start(1)
        ob = m.end() - 1
        depth, j = 0, ob
        while j < len(text):
            if text[j] == "{":
                depth += 1
            elif text[j] == "}":
                depth -= 1
                if depth == 0:
                    break
            j += 1
        if j < len(text):
            out.append((text[start:ob], ob + 1, j))
    return out


def params_from_sig(sig):
    """{param_name: type_string} from a function signature `ret name(T a, T b)`."""
    m = re.search(r"\((.*)\)\s*$", sig, re.S)
    if not m:
        return {}
    out = {}
    for part in re.split(r",(?![^()]*\))", m.group(1)):
        part = part.strip()
        pm = re.match(r"^(.*?)(?:\b|\*)(" + IDENT + r")$", part)
        if pm and pm.group(1).strip():
            ty = pm.group(1).strip()
            if ty not in ("void", "register", "static", "return", "if", "else"):
                out[pm.group(2)] = ty
    return out


def base_type_of(ty):
    """The struct typedef a declared type refers to (pointer stripped)."""
    ty = ty.strip()
    ty = re.sub(r"\b(const|unsigned|signed|struct|union|enum|register|volatile)\s+", "", ty)
    ty = ty.replace("*", " ").strip()
    return ty or None


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--out", default=os.path.join(
        REPO, "matching_notes", "field_resolved_sites.tsv"))
    args = ap.parse_args()

    structs = load_structs()
    typedef_names = set(structs)

    # globals across all files (file-scope declarations)
    globals_by_name = {}
    for p in (glob.glob(os.path.join(REPO, "src", "**", "*.c"), recursive=True)
              + glob.glob(os.path.join(REPO, "src", "**", "*.h"), recursive=True)
              + glob.glob(os.path.join(REPO, "include", "**", "*.h"), recursive=True)):
        t = open(p, errors="replace").read()
        for m in re.finditer(r"^(?:" + TYPE_RE.pattern + r")(" + IDENT + r")\s*(?:\[[^\]]*\])*\s*[;=]", t, re.M):
            ty = base_type_of(m.group(0).rsplit(m.group(1), 1)[0])
            if ty and (ty in typedef_names):
                globals_by_name.setdefault(m.group(1), set()).add(ty)

    sites = defaultdict(lambda: defaultdict(set))  # name -> file -> owners
    unresolved = Counter = 0
    for p in glob.glob(os.path.join(REPO, "src", "**", "*.c"), recursive=True):
        rel = os.path.relpath(p, REPO)
        t = open(p, errors="replace").read()
        # strip comments for resolution
        tc = re.sub(r"/\*.*?\*/", "", t, flags=re.S)
        tc = re.sub(r"//[^\n]*", "", tc)
        for sig, bstart, bend in split_functions(tc):
            body = tc[bstart:bend]
            scope = {}
            scope.update(params_from_sig(sig))
            # locals (typed, one per line)
            for m in re.finditer(r"^\s*(?:" + TYPE_RE.pattern + r")(" + IDENT + r")\s*(?:\[[^\]]*\])*\s*[;=]", body, re.M):
                ty = base_type_of(m.group(0).rsplit(m.group(1), 1)[0])
                if ty and ty in typedef_names:
                    scope[m.group(1)] = ty
            for m in ACCESS_RE.finditer(body):
                chain = re.findall(r"(?:->|\.)(" + IDENT + r")", m.group(0))
                base = m.group(1)
                ty = None
                if base in scope and isinstance(scope[base], str):
                    ty = scope[base]
                elif base in globals_by_name and len(globals_by_name[base]) == 1:
                    ty = next(iter(globals_by_name[base]))
                # walk the chain: each field's declared type inside ty's struct
                for i, f in enumerate(chain):
                    if ty and ty in structs and f in structs[ty]:
                        sites[f][rel].add(ty)
                        ty = base_type_of(structs[ty][f][0])
                    else:
                        ty = None
                        if f.startswith("unk_"):
                            sites[f][rel].add("?")  # unresolved base
    with open(args.out, "w") as f:
        f.write("# field<TAB>file<TAB>resolved owners (? = unresolved base)\n")
        for name in sorted(sites):
            for rel in sorted(sites[name]):
                f.write(f"{name}\t{rel}\t{','.join(sorted(sites[name][rel]))}\n")
    n_names = len(sites)
    n_rows = sum(len(v) for v in sites.values())
    print(f"resolved sites: {n_rows} (name, file) rows over {n_names} field names -> {args.out}")


if __name__ == "__main__":
    main()
