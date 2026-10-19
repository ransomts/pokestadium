#!/usr/bin/env python3
"""Tier C field cross-reference against michiiik/pokestadium (Team Hippodrome).

Both trees use the `/* 0xNN */ TYPE name;` offset-comment idiom in struct
typedefs. Join OUR placeholder fields (unk_XX) to THEIR named fields by
(typedef name, absolute field offset).

SAFETY: rename.py's member rewrite is scoped by FIELD NAME ONLY, so rows are
only emitted when our field name is globally unique across ALL our struct
fields (the rename_fields_inventory.tsv rule). Shared-name fields stay parked
until struct-scoped member rewriting exists (the pycparser item in P3).
Field renames do not change codegen, so the ROM gate cannot catch a bad one -
correctness comes from the deterministic join, not the gate.

Usage: HIPPO_REPO=/scratch/tsranso/hippo rename_hippo_field_gen.py [--batch hf1]
       [--report-only] > rows.tsv
Output ledger rows: TYPE.old<TAB>TYPE.new<TAB>hfN<TAB><TAB>justification<TAB>pending
"""
import argparse
import os
import re
import sys
from collections import Counter, defaultdict

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
HIPPO = os.environ.get("HIPPO_REPO", "/tmp/opencode/hippo")
PLACEHOLDER_FIELD = re.compile(r"^unk_")
IDENT = r"[A-Za-z_][A-Za-z0-9_]*"
FIELD_RE = re.compile(
    r"/\*\s*0x([0-9A-Fa-f]+)\s*\*/\s+((?:const\s+|unsigned\s+|signed\s+|struct\s+|union\s+|enum\s+)*"
    r"(?:" + IDENT + r"\s*\*+\s*|" + IDENT + r"\s*)+?)\b(" + IDENT + r")\s*((?:\[[^\]]*\])*)\s*;")
OPENER_NAME_RE = re.compile(r"(?:typedef\s+)?(?:struct|union)\s+(" + IDENT + r")\s*$")
CLOSER_NAME_RE = re.compile(r"\}\s*(" + IDENT + r")\s*;")


def struct_blocks(text):
    """[(typedef_name, body_text)] for every braced block, brace-matched.
    Name from the `} name;` closer, else the `struct name {` opener.
    Leaf fields of nested anonymous blocks appear in the outer body too -
    their offset comments are absolute, which is exactly what we join on."""
    out, i, n = [], 0, len(text)
    while i < n:
        ob = text.find("{", i)
        if ob < 0:
            break
        depth, j = 0, ob
        while j < n:
            if text[j] == "{":
                depth += 1
            elif text[j] == "}":
                depth -= 1
                if depth == 0:
                    break
            j += 1
        if j >= n:
            break
        name = None
        cm = CLOSER_NAME_RE.match(text[j:j + 80])
        if cm:
            name = cm.group(1)
        if name is None:
            head = re.sub(r"\s+", " ", text[max(0, ob - 160):ob]).strip()
            om = OPENER_NAME_RE.search(head)
            if om and "typedef" in head:
                name = om.group(1)
        if name:
            out.append((name, text[ob + 1:j]))
        i = j + 1
    return out


def parse_tree(*roots):
    """{typedef_name: [(offset, type, field_name)]}."""
    structs = {}
    for root in roots:
        for dirpath, _dirs, files in os.walk(root):
            for fn in sorted(files):
                if not fn.endswith(".h"):
                    continue
                text = open(os.path.join(dirpath, fn), errors="replace").read()
                for name, body in struct_blocks(text):
                    fields = []
                    for m in FIELD_RE.finditer(body):
                        fields.append((int(m.group(1), 16), m.group(2).strip(), m.group(3)))
                    if not fields:
                        continue
                    prev = structs.get(name)
                    if prev is None or len(fields) > len(prev):
                        structs[name] = fields
    return structs


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--batch", default="hf1")
    ap.add_argument("--report-only", action="store_true")
    args = ap.parse_args()

    ours = parse_tree(os.path.join(REPO, "src"), os.path.join(REPO, "include"))
    theirs = parse_tree(os.path.join(HIPPO, "src"), os.path.join(HIPPO, "include"))

    # global uniqueness of OUR field names (rename.py member rewrite is name-scoped)
    ours_count = Counter(f[2] for fields in ours.values() for f in fields)
    applied_old, applied_new = set(), set()
    for line in open(os.path.join(REPO, "matching_notes/renames.tsv"), errors="replace"):
        p = line.rstrip("\n").split("\t")
        if len(p) >= 6:
            if "." in p[0]:
                applied_old.add(p[0].split(".")[-1])
            if p[5].startswith("applied"):
                if "." in p[1]:
                    applied_new.add(p[1].split(".")[-1])

    stats = Counter()
    rows = []
    for tname, our_fields in sorted(ours.items()):
        their_fields = theirs.get(tname)
        if their_fields is None:
            stats["typedef-missing-there"] += 1
            continue
        their_by_off = defaultdict(list)
        for off, typ, name in their_fields:
            their_by_off[off].append((typ, name))
        for off, typ, name in our_fields:
            if not PLACEHOLDER_FIELD.match(name):
                stats["ours-named"] += 1
                continue
            cand = their_by_off.get(off)
            if not cand:
                stats["offset-missing-there"] += 1
                continue
            named = [c for c in cand if not PLACEHOLDER_FIELD.match(c[1])]
            if not named:
                stats["theirs-nameless"] += 1
                continue
            ttyp, tname_f = named[0]
            if ours_count[name] > 1:
                stats["shared-unsafe(parked)"] += 1
                continue
            if name in applied_old or tname_f in applied_new:
                stats["already-in-ledger"] += 1
                continue
            rows.append((tname, name, tname_f, off, typ, ttyp))
            stats["joined"] += 1

    print(f"# typedefs: ours {len(ours)}, theirs {len(theirs)}, "
          f"common {len(set(ours) & set(theirs))}", file=sys.stderr)
    print(f"# fields: {dict(stats)}", file=sys.stderr)
    if args.report_only:
        return
    for tname, old, new, off, typ, ttyp in rows:
        print(f"{tname}.{old}\t{tname}.{new}\t{args.batch}\t\t"
              f"michiiik/pokestadium (Team Hippodrome) {tname}+0x{off:02X} "
              f"(their `{ttyp} {new}`; ours `{typ} {old}`) - same ROM, "
              f"field joined by typedef+offset\tpending")


if __name__ == "__main__":
    main()
