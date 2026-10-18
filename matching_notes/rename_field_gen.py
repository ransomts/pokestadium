#!/usr/bin/env python3
"""Generate matching_notes/rename_fields_inventory.tsv: struct fields safe to rename.

A field row in rename.py rewrites `.field`/`->field` GLOBALLY by name, so only fields
whose name is unique across every typedef in the codebase are safe. This script lists,
per typedef, those safe fields (plus declaration text and user files) for the Tier C
smart-model agents.

Output TSV columns: typedef<TAB>header<TAB>field<TAB>decl_line<TAB>user_files
"""
import os
import re
import sys
from collections import Counter

FIELD_RE = re.compile(
    r"^\s*(?:/\*[^*]*\*/\s*)?"
    r"(?:u8|u16|u32|s8|s16|s32|u64|s64|f32|f64|int|char|void|unsigned|short|long|"
    r"struct\s+\w+|[A-Za-z_][A-Za-z0-9_]*)\s*\**\s*(unk_[0-9A-Fa-f]+w?)\s*(?:\[[^\]]*\])*;",
    re.M)


def main():
    rows = []  # (header, typedef, field, decl_line, lineno)
    typedef_decls = {}
    for root in ("include", "src"):
        for dirpath, _dirs, files in os.walk(root):
            for fn in sorted(files):
                if not fn.endswith(".h"):
                    continue
                p = os.path.join(dirpath, fn)
                text = open(p, errors="replace").read()
                for m in re.finditer(r"typedef struct\s*\w*\s*\{([^}]*)\}\s*(\w+)\s*;", text, re.S):
                    body, tname = m.group(1), m.group(2)
                    base_lineno = text[:m.start()].count("\n") + 1
                    for fm in FIELD_RE.finditer(body):
                        line = fm.group(0).strip()
                        rows.append((p, tname, fm.group(1), line,
                                     base_lineno + body[:fm.start()].count("\n") + 1))
                    if FIELD_RE.search(body):
                        typedef_decls.setdefault(tname, (p, m.group(0).strip()))

    byname = Counter(r[2] for r in rows)
    safe = [r for r in rows if byname[r[2]] == 1]

    # user files per typedef (whole-word grep over src/include)
    src_files = []
    for root in ("include", "src"):
        for dirpath, _dirs, files in os.walk(root):
            for fn in sorted(files):
                if fn.endswith((".c", ".h")):
                    src_files.append(os.path.join(dirpath, fn))
    usage = {}
    for tname in sorted({r[1] for r in safe}):
        pat = re.compile(r"(?<![A-Za-z0-9_])" + re.escape(tname) + r"(?![A-Za-z0-9_])")
        hits = [os.path.relpath(f) for f in src_files
                if pat.search(open(f, errors="replace").read())]
        usage[tname] = hits

    out = ["# Tier C field inventory: globally-unique field names, safe for rename.py field rows",
           "# typedef\theader\tfield\tdecl_line\tuser_files"]
    n = 0
    for p, tname, field, line, lineno in sorted(safe, key=lambda r: (r[1], r[2])):
        out.append(f"{tname}\t{os.path.relpath(p)}\t{field}\t{line}\t{','.join(usage.get(tname, [])[:12])}")
        n += 1
    Path = open if False else None
    with open("matching_notes/rename_fields_inventory.tsv", "w") as f:
        f.write("\n".join(out) + "\n")
    print(f"{n} safe fields across {len(set(r[1] for r in safe))} typedefs"
          f" (of {len(rows)} fields / {len(typedef_decls)} typedefs total)")


if __name__ == "__main__":
    sys.exit(main())
