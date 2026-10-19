#!/usr/bin/env python3
"""Statics cross-reference against michiiik/pokestadium (Team Hippodrome) via MAP files.

hp1 (rename_hippo_gen.py) joined the symbol_addrs files - globals only. File-scope
statics never appear there; they DO appear in the linker map as local symbols. Both
trees build byte-identical ROMs of the same game, so static addresses align: join
OUR placeholder-named map locals against THEIR named map locals by address.

Requires: their build/pokestadium-us.map (build their tree first - see RENAME_PLAN
toolchain-pin findings) and OUR build/pokestadium-us.map (fresh from any wave gate).

Usage: rename_hippo_statics_gen.py [--batch hs1] [--dry-run] > rows.tsv
Output ledger rows: old<TAB>new<TAB>hsN<TAB><TAB>justification<TAB>pending
"""
import argparse
import os
import re
import sys

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
HIPPO = "/tmp/opencode/hippo"
OUR_MAP = os.path.join(REPO, "build/pokestadium-us.map")
HIPPO_MAP = os.path.join(HIPPO, "build/pokestadium-us.map")
PLACEHOLDER = re.compile(r"^(func_|D_|jtbl_|pad_|unk_)")
BAD_NAMES = re.compile(r"^(func_|D_|jtbl_|pad_|unk_|\$|\.|__)")
MAP_LINE = re.compile(r"^\s+(0x[0-9a-fA-F]+)\s+([A-Za-z_][A-Za-z0-9_.]*)"
                      r"(\s+=\s+0x[0-9a-fA-F]+)?\s*$")
SA_LINE = re.compile(r"^(\S+)\s*=\s*(0x[0-9A-Fa-f]+)\s*;")


def sa_names(repo):
    """Names defined in the tree's symbol_addrs files (globals - excluded: hp1 territory)."""
    names = set()
    for fn in ("symbol_addrs.txt", "symbol_addrs_code.txt", "symbol_addrs_ultralib.txt"):
        p = os.path.join(repo, "linker_scripts/us", fn)
        if os.path.exists(p):
            for m in re.finditer(r"^(\S+)\s*=", open(p, errors="replace").read(), re.M):
                names.add(m.group(1))
    return names


def map_locals(map_path, sa):
    """{address: name} for map symbols NOT in symbol_addrs (file-scope locals).
    If a placeholder and a human name share an address, prefer the human name."""
    by_addr = {}
    if not os.path.exists(map_path):
        sys.exit(f"rename_hippo_statics_gen.py: error: {map_path} missing (build first)")
    for line in open(map_path, errors="replace"):
        m = MAP_LINE.match(line)
        if not m:
            continue
        name = m.group(2)
        if name in sa:            # global (hp1 already covered it)
            continue
        addr = int(m.group(1), 16)
        prev = by_addr.get(addr)
        if prev is None or (PLACEHOLDER.match(prev) and not PLACEHOLDER.match(name)):
            by_addr[addr] = name
    return by_addr


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--batch", default="hs1")
    args = ap.parse_args()

    ours = map_locals(OUR_MAP, sa_names(REPO))
    theirs = map_locals(HIPPO_MAP, sa_names(HIPPO))

    applied_news, applied_olds = set(), set()
    for line in open(os.path.join(REPO, "matching_notes/renames.tsv"), errors="replace"):
        parts = line.rstrip("\n").split("\t")
        if len(parts) >= 6:
            applied_olds.add(parts[0])
            if parts[5].startswith("applied"):
                applied_news.add(parts[1])

    undef = set()
    p = os.path.join(REPO, "linker_scripts/us/undefined_syms.ld")
    for m in re.finditer(r"([A-Za-z_][A-Za-z0-9_]*)\s*=", open(p, errors="replace").read()):
        undef.add(m.group(1))

    rows, seen_new, seen_old = [], set(), set()
    skipped = {"theirs-placeholder": 0, "no-match": 0, "collision": 0,
               "undef": 0, "segment": 0, "applied": 0}
    for addr, old in sorted(ours.items()):
        if not PLACEHOLDER.match(old):
            continue                       # our side already named
        if old in applied_olds:
            skipped["applied"] += 1
            continue
        if old in undef:
            skipped["undef"] += 1
            continue
        if re.fullmatch(r"D_[0-9A-F]{7}", old) or re.fullmatch(r"D_[0-9A-F]000[0-9A-F]{3}", old):
            skipped["segment"] += 1
            continue
        if addr in (0x80000000,):
            continue
        new = theirs.get(addr)
        if not new:
            skipped["no-match"] += 1
            continue
        if BAD_NAMES.match(new):
            skipped["theirs-placeholder"] += 1
            continue
        if new in applied_news or new in seen_new:
            skipped["collision"] += 1
            continue
        seen_new.add(new)
        seen_old.add(old)
        rows.append((old, new, addr))

    for old, new, addr in rows:
        print(f"{old}\t{new}\t{args.batch}\t\t"
              f"michiiik/pokestadium (Team Hippodrome) map local at 0x{addr:08X} - "
              f"independent complete decomp of the same ROM, statics joined by address\t"
              f"pending")
    print(f"# generated {len(rows)} rows; skipped: {skipped}", file=sys.stderr)


if __name__ == "__main__":
    main()
