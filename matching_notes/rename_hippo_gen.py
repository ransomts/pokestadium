#!/usr/bin/env python3
"""Cross-reference our placeholder symbols against michiiik/pokestadium (Team Hippodrome).

Their US decomp is complete and independently named; we join by ADDRESS (same ROM) and
propose their name for every placeholder we still have. Deterministic - no LLM involved.

Usage: rename_hippo_gen.py [--min-refs 0] > rows.tsv
Output ledger rows: old<TAB>new<TAB>hippoN<TAB><TAB>justification<TAB>pending
"""
import argparse
import os
import re
import sys

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
HIPPO = "/tmp/opencode/hippo"
PLACEHOLDER = re.compile(r"^(func_|D_|jtbl_|pad_)")
BAD_NAMES = re.compile(r"^(func_|D_|jtbl_|pad_|unk_)")
SA_LINE = re.compile(r"^(\S+)\s*=\s*(0x[0-9A-Fa-f]+)\s*;")


def load_syms(repo):
    """{address: name} and {name: address} from the three symbol_addrs files."""
    by_addr, by_name = {}, {}
    for fn in ("symbol_addrs.txt", "symbol_addrs_code.txt", "symbol_addrs_ultralib.txt"):
        p = os.path.join(repo, "linker_scripts/us", fn)
        if not os.path.exists(p):
            continue
        for line in open(p, errors="replace"):
            m = SA_LINE.match(line)
            if not m:
                continue
            name, addr = m.group(1), int(m.group(2), 16)
            by_name[name] = addr
            # prefer human names if a placeholder and a name share an address
            if addr not in by_addr or (PLACEHOLDER.match(by_addr[addr]) and not PLACEHOLDER.match(name)):
                by_addr[addr] = name
    return by_addr, by_name


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--batch", default="hp1")
    ap.add_argument("--exclude-undefined", action="store_true", default=True)
    args = ap.parse_args()

    hippo_addr, hippo_name = load_syms(HIPPO)
    ours_addr, ours_name = load_syms(REPO)

    # our already-applied/known names (ledger applied + upstream-named) for collision checks
    applied_news, applied_olds = set(), set()
    for line in open(os.path.join(REPO, "matching_notes/renames.tsv"), errors="replace"):
        parts = line.rstrip("\n").split("\t")
        if len(parts) >= 6:
            applied_olds.add(parts[0])
            if parts[5].startswith("applied"):
                applied_news.add(parts[1])
    upstream_named = {n for n in ours_name if not PLACEHOLDER.match(n)}

    undef = set()
    p = os.path.join(REPO, "linker_scripts/us/undefined_syms.ld")
    for m in re.finditer(r"([A-Za-z_][A-Za-z0-9_]*)\s*=", open(p, errors="replace").read()):
        undef.add(m.group(1))

    rows, seen_new = [], set()
    skipped = {"named": 0, "placeholder-there": 0, "collision": 0, "undef": 0,
               "segment": 0, "not-ours-addr": 0}
    for name, addr in sorted(ours_name.items(), key=lambda kv: kv[1]):
        if not PLACEHOLDER.match(name):
            skipped["named"] += 1
            continue
        if name in applied_olds:
            continue  # already in the ledger (applied or pending)
        if name in undef:
            skipped["undef"] += 1
            continue
        if re.fullmatch(r"D_[0-9A-F]{7}", name):
            skipped["segment"] += 1
            continue
        theirs = hippo_addr.get(addr)
        if not theirs:
            skipped["not-ours-addr"] += 1
            continue
        if BAD_NAMES.match(theirs):
            skipped["placeholder-there"] += 1
            continue
        if theirs in upstream_named or theirs in applied_news or theirs in seen_new or theirs in ours_name:
            # a symbol of that name already exists on our side at a different address
            if ours_name.get(theirs) != addr:
                skipped["collision"] += 1
                continue
        seen_new.add(theirs)
        rows.append((name, theirs, args.batch,
                     f"matches michiiik/pokestadium (Team Hippodrome) symbol at 0x{addr:08X} - "
                     f"independent complete decomp of the same ROM, cross-referenced by address"))

    for old, new, b, just in rows:
        print(f"{old}\t{new}\t{b}\t\t{just}\tpending")
    print(f"# generated {len(rows)} rows; skipped: {skipped}", file=sys.stderr)


if __name__ == "__main__":
    main()
