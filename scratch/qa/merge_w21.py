#!/usr/bin/env python3
"""w21 merge: Phase A misname fixes + new names + Phase C (when landed).

Run after all qa_verify_* chunks have landed. Separates REVIEW rows,
validates (format/conflicts/collisions/lint/tree-shadow), and writes
the merged w21 batch + ledger append rows.
"""
import re, sys, subprocess, importlib.util

spec = importlib.util.spec_from_file_location("np", "matching_notes/naming_pipeline.py")
np = importlib.util.module_from_spec(spec); spec.loader.exec_module(np)

COMPONENTS = [
    "scratch/upstream/w21_michiiik_adoptions.tsv",
    "scratch/upstream/w21_funcs_fixes.tsv",
    "scratch/upstream/w21_data_fixes.tsv",
] + [f"scratch/upstream/qa_verify_{c}.tsv" for c in
     ["1", "2", "3a", "3b", "4", "5", "6", "7", "8"] if
     __import__("os").path.exists(f"scratch/upstream/qa_verify_{c}.tsv")] + \
    [f"scratch/upstream/qa_pc_{i}.tsv" for i in range(1, 18) if
     __import__("os").path.exists(f"scratch/upstream/qa_pc_{i}.tsv")]

reviews, fixes = [], []
pair_map, new_map, fails = {}, {}, set()
for path in COMPONENTS:
    for line in open(path, errors="replace"):
        p = line.rstrip("\n").split("\t")
        if len(p) < 6 or not p[0] or not p[1]:
            continue
        if p[1] == "REVIEW":
            reviews.append(line); continue
        if p[0] == p[1]:
            continue  # keep no-op
        fixes.append(line)
        pair_map.setdefault(p[0], set()).add(p[1])
        new_map.setdefault(p[1], set()).add(p[0])
        if np.needs_revision(p[1]): fails.add(p[1])

conflicts = {o: v for o, v in pair_map.items() if len(v) > 1}
dups = {n: o for n, o in new_map.items() if len(o) > 1}

# tree shadow check — ALLOWLIST: same-address overlay alignments (the C symbol
# at the overlay's address already carries this name; renaming the D_ label
# aligns them — verified: gStatThresholds static has type unk_D_82305978,
# gDefaultMusicVolume global is the 0x8007C7C0 data per map)
src_symbols = set(subprocess.run(["grep", "-rhoP", r"\b[A-Za-z_][A-Za-z0-9_]*\b", "src/",
                  "--include=*.c", "--include=*.h"], capture_output=True, text=True).stdout.split())
ALIGNMENTS = {"gStatThresholds", "gDefaultMusicVolume"}
shadow = [n for n in new_map if n in src_symbols and n not in pair_map and n not in ALIGNMENTS]

print(f"components: {len(COMPONENTS)}")
print(f"fix rows: {len(fixes)} | REVIEW rows: {len(reviews)}")
print(f"conflicts: {len(conflicts)} | name collisions: {len(dups)} | lint fails: {len(fails)} | tree shadow: {len(shadow)}")
for n in fails: print(f"  LINT {n}")
for o, v in conflicts.items(): print(f"  CONFLICT {o}: {v}")
for n, o in dups.items(): print(f"  DUP {n} <- {o}")
for n in shadow: print(f"  SHADOW {n}")

if conflicts or dups or fails or shadow:
    print("\nNOT CLEAN — resolve issues before apply")
    sys.exit(1)

with open("scratch/upstream/merged_batch_w21.tsv", "w") as f:
    f.write("".join(l if l.endswith("\n") else l + "\n" for l in fixes))
with open("scratch/upstream/w21_review_flags.tsv", "w") as f:
    f.write("".join(l if l.endswith("\n") else l + "\n" for l in reviews))
print(f"\nCLEAN. Wrote merged_batch_w21.tsv ({len(fixes)} rows) + w21_review_flags.tsv ({len(reviews)})")
print("next: append to ledger as w21, plan, apply")
