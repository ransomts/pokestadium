#!/usr/bin/env python3
"""Curate the upstream contribution set for michiiik/pokestadium.

The contribution: symbols where WE have a human name and michiiik still has a
placeholder (measured: 991), joined with the ledger's evidence justifications,
plus struct fields our headers name that theirs still leave as unk_.

Includes a terminology lint against their CONTRIBUTING.md:
  - yaw/pitch/roll  -> rotationX/rotationY/rotationZ (world-relative rotations)
  - AI (trainer)    -> COM
  - Victory Palace  -> Hall of Fame
  - Pokemon Lab     -> Professor Oak's Lab
  - Kid's Club      -> Minigames
  - Poke Cup        -> Nintendo Cup
  - non-ASCII / non-alphanumeric in identifiers

Outputs (all under scratch/upstream/):
  symbols_curated.tsv   - address, our name, their placeholder, batch, justification
  lint_violations.tsv   - rows failing the terminology/charset lint
  fields_curated.tsv    - struct field names we have that they lack
"""
import glob
import os
import re
import sys
from collections import defaultdict

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
HIPPO = "/tmp/opencode/hippo"
OUT = os.path.join(REPO, "scratch", "upstream")
IDENT = r"[A-Za-z_][A-Za-z0-9_]*"
PH = re.compile(r"^(func_|D_|jtbl_|pad_|unk_)")

LINT_RULES = [
    (re.compile(r"(?<![A-Za-z])yaw(?![A-Za-z])", re.I), "yaw -> rotationY (world-relative rotations only)"),
    (re.compile(r"(?<![A-Za-z])roll(?![A-Za-z])", re.I), "roll -> rotationZ"),
    (re.compile(r"(?<![A-Za-z])pitch(?![A-Za-z])", re.I), "pitch -> rotationX (audio-frequency pitch is fine - adjudicate manually)"),
    (re.compile(r"VictoryPalace|victory_palace", re.I), "Victory Palace -> Hall of Fame"),
    (re.compile(r"PokemonLab|pokemon_lab", re.I), "Pokemon Lab -> Professor Oak's Lab"),
    (re.compile(r"KidsClub|kids_club|KidClub|KidsClub", re.I), "Kid's Club -> Minigames"),
    (re.compile(r"PokeCup|poke_cup", re.I), "Poke Cup -> Nintendo Cup"),
    (re.compile(r"(?<![A-Za-z])AI(?![A-Za-z])|(?<=[a-z])Ai(?=[A-Z_])|Ai(?=Type|Level|Difficult)"), "AI -> COM (non-player trainers)"),
    (re.compile(r"[^A-Za-z0-9_]"), "non-ASCII / non-alphanumeric in identifier"),
]


def load_addr_names(repo):
    out = {}
    for f in ("linker_scripts/us/symbol_addrs.txt", "linker_scripts/us/symbol_addrs_code.txt"):
        p = os.path.join(repo, f)
        if not os.path.exists(p):
            continue
        for m in re.finditer(r"^(\S+)\s*=\s*(0x[0-9A-Fa-f]+)", open(p, errors="replace").read(), re.M):
            out.setdefault(int(m.group(2), 16), m.group(1))
    return out


def main():
    os.makedirs(OUT, exist_ok=True)
    ours = load_addr_names(REPO)
    theirs = load_addr_names(HIPPO)

    # ledger: old name -> (new name, batch, justification); and new name -> old
    # (to find the justification for a CURRENT name, walk old->new chains)
    rows = []
    for line in open(os.path.join(REPO, "matching_notes", "renames.tsv"), errors="replace"):
        p = line.rstrip("\n").split("\t")
        if len(p) >= 6 and p[5].startswith("applied"):
            rows.append(p)

    contrib, lint_bad = [], []
    for addr, our_name in sorted(ours.items()):
        their_name = theirs.get(addr)
        if their_name is None or not PH.match(their_name) or PH.match(our_name):
            continue
        # find the ledger justification for our_name (last writer wins)
        just = ""
        for p in rows:
            if p[1] == our_name:
                just = p[4]
        reasons = [f"{our_name!r}: {msg}" for pat, msg in LINT_RULES
                   if pat.search(our_name)]
        entry = (f"0x{addr:08X}", our_name, their_name, just[:400])
        if reasons:
            lint_bad.append((*entry, "; ".join(reasons)))
        else:
            contrib.append(entry)

    with open(os.path.join(OUT, "symbols_curated.tsv"), "w") as f:
        f.write("address\tour_name\ttheir_placeholder\tjustification\n")
        for e in contrib:
            f.write("\t".join(e) + "\n")
    with open(os.path.join(OUT, "lint_violations.tsv"), "w") as f:
        f.write("address\tour_name\ttheir_placeholder\tjustification\tlint\n")
        for e in lint_bad:
            f.write("\t".join(e) + "\n")

    # field contribution: (struct, field) we name that they leave unk_
    import importlib.util
    spec = importlib.util.spec_from_file_location(
        "hfg", os.path.join(REPO, "matching_notes", "rename_hippo_field_gen.py"))
    hfg = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(hfg)

    def fields_of(root):
        out = {}  # (typedef, offset) -> field name
        for p in glob.glob(os.path.join(root, "src", "**", "*.h"), recursive=True) + \
                 glob.glob(os.path.join(root, "include", "**", "*.h"), recursive=True):
            t = open(p, errors="replace").read()
            for name, body in hfg.struct_blocks(t):
                for m in hfg.FIELD_RE.finditer(body):
                    out.setdefault((name, int(m.group(1), 16)), m.group(3))
        return out

    our_fields = fields_of(REPO)
    their_fields = fields_of(HIPPO)
    fcount = 0
    with open(os.path.join(OUT, "fields_curated.tsv"), "w") as f:
        f.write("struct\toffset\tour_field\ttheir_field\n")
        for (t, off), fname in sorted(our_fields.items()):
            if fname.startswith("unk_"):
                continue
            tf = their_fields.get((t, off))
            if tf and tf.startswith("unk_"):
                f.write(f"{t}\t0x{off:X}\t{fname}\t{tf}\n")
                fcount += 1

    print(f"symbols curated: {len(contrib)} clean, {len(lint_bad)} lint violations (fix first)")
    print(f"fields curated: {fcount}")
    print(f"-> {OUT}/")


if __name__ == "__main__":
    main()
