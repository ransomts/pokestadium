#!/usr/bin/env python3
"""Semantic reorg: move our files onto michiiik/pokestadium's tree layout.

Usage (repo root, .venv python):
  reorg.py plan [--group N | --group main]     # show moves + join issues, no writes
  reorg.py apply <group> [--no-gate]           # do moves, gate (ROM must stay OK)

A "group" is one of our fragment numbers (fragments/N) or "main" (the root segment).
Join: every yaml subsegment of ours (same start address + same kind) -> michiiik's
exact path string; 1:1 only, mismatches are reported and skipped. The gate runs
make extract + full make; on failure everything reverts (files moved back, yaml
restored). One commit per apply (caller does the commit)."""
import argparse
import json
import os
import re
import subprocess
import sys

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
HIPPO = "/tmp/opencode/hippo"
OUR_YAML = os.path.join(REPO, "yamls/us/rom.yaml")
SEG_RE = re.compile(r"^  - name: (\S+)")
SUB_RE = re.compile(r"^(\s*)- \[(0x[0-9A-Fa-f]+),\s*([.\w]+),?\s*([^\]\s]*)[^\]]*\]\s*(#.*)?$")
DICT_RE = re.compile(r"^(\s*)- \{vram:\s*(0x[0-9A-Fa-f]+),\s*type:\s*([.\w]+),\s*name:\s*([^\s}]+)[^}]*\}")


def parse_yaml(path):
    """[{name, subsegs: [(addr, kind, path)], vrams: [(vram, kind, path)]}]"""
    segs, cur = [], None
    for line in open(path, errors="replace"):
        m = SEG_RE.match(line)
        if m:
            cur = {"name": m.group(1), "subsegs": [], "vrams": []}
            segs.append(cur)
            continue
        m = SUB_RE.match(line.rstrip())
        if m and cur is not None:
            cur["subsegs"].append((int(m.group(2), 16), m.group(3), m.group(4) or ""))
            continue
        m = DICT_RE.match(line.rstrip())
        if m and cur is not None:
            cur["vrams"].append((int(m.group(2), 16), m.group(3), m.group(4)))
    return segs


def join_group(ours, theirs, group):
    """(segment_renames, subseg_renames, problems) for one group of ours.
    Also fills the module-level _LAST_PATHLESS with (derived_name, their_path,
    addr, kind) for pathless entries michiiik has pathed."""
    global _LAST_PATHLESS
    _LAST_PATHLESS = []
    if group == "main":
        my_segs = [s for s in ours if s["name"] == "text"]
        their_segs = [s for s in theirs if s["name"] == "text"]
        prefix = None
    else:
        my_segs = [s for s in ours if s["name"] == f"fragment{group}"
                   or s["name"].startswith(f"fragment{group}_")]
        if not my_segs:
            return None, [], [f"no segment named fragment{group}"]
        prefix = f"fragments/{group}/"
        their_segs = theirs
    tmap = {}
    tvram = {}
    for s in their_segs:
        for addr, kind, p in s["subsegs"]:
            tmap[(addr, kind)] = (s["name"], p)
        for vram, kind, p in s.get("vrams", []):
            tvram[(vram, kind)] = p
    seg_ren, sub_ren, problems = [], [], []
    for s in my_segs:
        for addr, kind, p in s["subsegs"]:
            if group != "main" and not p.startswith(prefix):
                if p:
                    problems.append(f"odd path {p} in segment {s['name']}")
                continue
            hit = tmap.get((addr, kind))
            if hit is None:
                problems.append(f"no michiiik match for {p or hex(addr)} ({kind})")
                continue
            tname, tp = hit
            if not p:
                # pathless entry (`- [0xADDR, c]`): splat derives the file name
                # from the address. michiiik's entry is PATHED - converge by
                # ADDING the path (the flash landing proved this pattern).
                _LAST_PATHLESS.append((f"{addr:X}", tp, addr, kind))
                continue
            if tp and tp != p:
                sub_ren.append((p, tp, s["name"], tname))
        for vram, kind, p in s.get("vrams", []):
            if group != "main" and not p.startswith(prefix):
                continue
            tp = tvram.get((vram, kind))
            if tp and tp != p:
                sub_ren.append((p, tp, s["name"], s["name"]))
            elif not tp:
                problems.append(f"no michiiik vram match for {p} ({kind})")
    return seg_ren, sub_ren, problems


def sh(cmd, **kw):
    return subprocess.run(cmd, cwd=REPO, capture_output=True, text=True, **kw)


def plan_files(sub_ren):
    """[(src, dst)] file moves for the .c/.h pairs implied by subsegment renames."""
    moves = []
    for op, tp, oname, tname in sub_ren:
        for ext in (".c", ".h"):
            src = os.path.join(REPO, "src", op + ext)
            if os.path.exists(src):
                moves.append((os.path.join("src", op + ext), os.path.join("src", tp + ext)))
    return moves


def apply_group(group, no_gate):
    # refuse to start from a desynced index: a previous failed apply + revert
    # leaves STAGED renames behind, and any later `git add && git commit`
    # (even of one unrelated file) sweeps them into that commit (the df9f2cde
    # lesson: 18 renames rode a reorg.py-only commit)
    r0 = sh(["git", "diff", "--cached", "--name-only"])
    if r0.stdout.strip():
        print("refusing: git index has staged changes - `git reset` first:")
        print("  " + "\n  ".join(r0.stdout.splitlines()[:5]))
        return 1
    ours = parse_yaml(OUR_YAML)
    theirs = parse_yaml(os.path.join(HIPPO, "yamls/us/rom.yaml"))
    seg_ren, sub_ren, problems = join_group(ours, theirs, group)
    if sub_ren is None:
        print("\n".join(problems))
        return 1
    # converge pathless entries (`- [0xADDR, c]` -> `- [0xADDR, c, flash]`):
    # splat derives the file name from the address, so the derived file renames
    # like any other (the flash landing proved this pattern). The pairs join
    # sub_ren FIRST so the collision/merge guards apply to them uniformly.
    pathless = [(d, tp) for d, tp, _a, _k in _LAST_PATHLESS]
    sub_ren.extend((d, tp, "text", "text") for d, tp in pathless)
    # park renames whose file move would land on an existing DIFFERENT file:
    # e.g. our 3D140_2 data-entry -> michiiik's "3D140" while our 3D140.c
    # exists (they attach that data range to a different file boundary).
    # Renaming the yaml path there drops the .c's symbols from the link.
    # ALSO park MERGE cases: multiple of our files mapping to one michiiik
    # file (their gb_data.c = our data_71BA0.c + 22630.c) - a path rename
    # cannot express a file merge.
    from collections import Counter as _C
    tp_ops = {}
    for _op, _tp, _on, _tn in sub_ren:
        tp_ops.setdefault(_tp, set()).add(_op)
    kept = []
    for op, tp, oname, tname in sub_ren:
        collide = [ext for ext in (".c", ".h")
                   if os.path.exists(os.path.join(REPO, "src", op + ext))
                   and os.path.exists(os.path.join(REPO, "src", tp + ext))]
        if collide:
            problems.append(f"parked {op} -> {tp}: file collision on {op}{collide[0]}"
                            f" (michiiik attaches the range differently)")
            continue
        if len(tp_ops[tp]) > 1:
            problems.append(f"parked {op} -> {tp}: michiiik merged these files"
                            f" ({len(tp_ops[tp])} of ours map there)")
            continue
        kept.append((op, tp, oname, tname))
    sub_ren = kept
    moves = plan_files(sub_ren)
    print(f"group {group}: {len(sub_ren)} subsegment renames, {len(moves)} file moves, "
          f"{len(seg_ren)} segment renames, {len(problems)} problems")
    for p in problems:
        print(f"  ! {p}")
    manifest = {"seg": seg_ren, "sub": sub_ren, "moves": moves}
    open(os.path.join(REPO, "scratch", "reorg_manifest.json"), "w").write(json.dumps(manifest))

    yaml = open(OUR_YAML).read()
    # surviving pathless pairs: ADD the path to the entry (`[0xADDR, c]` ->
    # `[0xADDR, c, flash]`) - these have no old path string to replace
    for d, tp, addr, kind in _LAST_PATHLESS:
        if (d, tp) not in {(o, t) for o, t, _on, _tn in sub_ren}:
            continue  # parked by the guards above
        old_entry = f"0x{addr:X}, {kind}]"
        if old_entry in yaml:
            yaml = yaml.replace(old_entry, f"0x{addr:X}, {kind}, {tp}]")
        else:
            problems.append(f"pathless 0x{addr:X}: entry shape not found")
    for oname, tname in seg_ren:
        yaml = yaml.replace(f"- name: {oname}\n", f"- name: {tname}\n")
    for op, tp, _on, _tn in sub_ren:
        # MAIN-SEGMENT LESSON: main stems are short hex names (6BC0) that occur
        # INSIDE address literals (0x6BC0) - the plain replace/lookahead forms
        # rewrote the addresses and corrupted the yaml. Anchor on a preceding
        # non-hex char so "0x6BC0" can never match, but ", 6BC0]" still does.
        yaml = re.sub(r'(?<![0-9A-Fa-fx])' + re.escape(op) + r'(?=[\],\s#}])',
                      lambda _m, tp=tp: tp, yaml)
    open(OUR_YAML, "w").write(yaml)

    done = []
    seen_moves = set()
    for src, dst in moves:
        if (src, dst) in seen_moves or src in {s for s, _ in seen_moves}:
            continue
        seen_moves.add((src, dst))
        os.makedirs(os.path.dirname(os.path.join(REPO, dst)), exist_ok=True)
        r = sh(["git", "mv", src, dst])
        if r.returncode != 0:
            print(f"  ! git mv failed {src} -> {dst}: {r.stderr.strip()}")
        else:
            done.append((src, dst))
    print(f"  moved {len(done)} file(s)")
    # stale objects at old paths would double-link (multiple definition): full src rebuild
    import shutil
    shutil.rmtree(os.path.join(REPO, "build/src"), ignore_errors=True)

    # include rewrites: michiiik's convention is ROOT-RELATIVE qualified includes
    # ("src/fragments/<dir>/<name>.h", resolved via -Isrc / -I.) - flat basenames
    # only resolve same-dir, which breaks partial joins (the 2026-10-19 lesson:
    # leftover .c at old numeric paths including a moved group header).
    def rewrite_header_includes(old_variants, new_inc):
        n = 0
        new_base = new_inc.rsplit("/", 1)[-1]
        pats = [(re.compile(r'(#include\s+")' + re.escape(v) + r'(")'), new_inc)
                for v in old_variants]
        # relative-path includes ("../45720.h" from src/libnaudio/): swap the
        # basename, keep the relative prefix (michiiik's own convention)
        bases = {v.rsplit("/", 1)[-1] for v in old_variants}
        rel_pat = re.compile(r'(#include\s+"[^"]*/)(' + "|".join(
            re.escape(b) for b in bases) + r')(")')
        for root in ("src", "include"):
            for dp, _d, fs in os.walk(os.path.join(REPO, root)):
                for fn in fs:
                    if not fn.endswith((".c", ".h")):
                        continue
                    p = os.path.join(dp, fn)
                    t = open(p, errors="replace").read()
                    t2 = t
                    for pat, repl in pats:
                        t2, k = pat.subn(r"\g<1>" + repl + r"\g<2>", t2)
                        n += k
                    t2, k = rel_pat.subn(
                        lambda m: m.group(1) + new_base + m.group(3), t2)
                    n += k
                    if t2 != t:
                        open(p, "w").write(t2)
        return n

    header_moves = []
    # a group's files may split across SEVERAL michiiik target dirs; the group
    # header goes to the dominant dir that has a dir-named header there
    # (michiiik sometimes keeps numeric .c dirs but moves the header out)
    from collections import Counter
    dir_targets = {}
    for op, tp, _on, _tn in sub_ren:
        k, v = tuple(op.split("/")[:-1]), tuple(tp.split("/")[:-1])
        dir_targets.setdefault(k, Counter())[v] += 1
    for ourdir, targets in dir_targets.items():
        if not ourdir:
            continue  # main segment: bare filenames, no group header to move
        oldh_base = "fragment" + ourdir[-1] + ".h"  # fragment16.h
        cands = [t for t in targets
                 if os.path.exists(os.path.join(HIPPO, "src", *t, t[-1] + ".h"))]
        if not cands:
            continue  # their tree kept no dir-named header home for this group
        theirdir = max(cands, key=lambda t: (targets[t], t))
        newh_base = theirdir[-1] + ".h"             # credits.h
        oldh_path = "/".join(["src"] + list(ourdir) + [oldh_base])
        newh_path = "/".join(["src"] + list(theirdir) + [newh_base])
        if oldh_base == newh_base or not os.path.exists(os.path.join(REPO, oldh_path)):
            continue
        os.makedirs(os.path.dirname(os.path.join(REPO, newh_path)), exist_ok=True)
        r = sh(["git", "mv", oldh_path, newh_path])
        if r.returncode != 0:
            print(f"  ! header mv failed {oldh_path}: {r.stderr.strip()}")
            continue
        header_moves.append((oldh_path, newh_path))
        manifest["moves"].append((oldh_path, newh_path))
        variants = [oldh_base,
                    "/".join(["src"] + list(ourdir) + [oldh_base]),
                    "/".join(list(ourdir) + [oldh_base])]
        n = rewrite_header_includes(variants, newh_path)
        print(f"  header {oldh_base} -> {newh_path}: moved, {n} include rewrites")
    open(os.path.join(REPO, "scratch", "reorg_manifest.json"), "w").write(json.dumps(manifest))

    for op, tp, _on, _tn in sub_ren:
        oldh = os.path.basename(op) + ".h"
        newh = os.path.basename(tp) + ".h"
        if oldh == newh:
            continue
        # per-file companion headers: qualified rewrite like the group header -
        # files that stay behind (partial joins) must still resolve the include
        variants = [oldh, "src/" + op + ".h", op + ".h"]
        n = rewrite_header_includes(variants, "src/" + tp + ".h")
        if n:
            print(f"  includes: {oldh} -> src/{tp}.h ({n})")
        # GLOBAL_ASM pragma paths: a main-segment rename moves the file's
        # nonmatchings dir (extract regenerates .s under the new path) - the
        # pragmas must follow (fragment groups never hit this: segments stay
        # numeric, only main renames change the nonmatchings dir name)
        pragma_pat = re.compile(r'(asm/us/nonmatchings/)' + re.escape(op) + r'(?=/)')
        pn = 0
        for root in ("src",):
            for dp, _d, fs in os.walk(os.path.join(REPO, root)):
                for fn in fs:
                    if not fn.endswith(".c"):
                        continue
                    p = os.path.join(dp, fn)
                    t = open(p, errors="replace").read()
                    t2, k = pragma_pat.subn(lambda _m, tp=tp: "asm/us/nonmatchings/" + tp, t)
                    if k:
                        open(p, "w").write(t2)
                        pn += k
        if pn:
            print(f"  pragmas: nonmatchings/{op} -> nonmatchings/{tp} ({pn})")

    if no_gate:
        print("applied without gate (tree dirty - run make yourself)")
        return 0
    env = dict(os.environ,
               PATH=f"{REPO}/.venv/bin:{os.path.expanduser('~')}/local/bin:/usr/local/bin:/usr/bin:/bin")
    for target in ("extract", "-j24"):
        r = subprocess.run(["make", target, f"PYTHON={REPO}/.venv/bin/python3"],
                           cwd=REPO, env=env, timeout=3600, capture_output=True, text=True)
        if target == "-j24":
            ok = r.returncode == 0 and "build/pokestadium-us.z64: OK" in (r.stdout + r.stderr)
            if not ok:
                open(os.path.join(REPO, "scratch", "reorg_gate.log"), "w").write(r.stdout + r.stderr)
        else:
            ok = r.returncode == 0
            if not ok:
                open(os.path.join(REPO, "scratch", "reorg_gate.log"), "w").write(r.stdout + r.stderr)
        print(f"  make {target}: {'OK' if ok else 'FAILED'}")
        if not ok:
            revert(manifest)
            return 1
    print("gate OK - commit with:")
    print(f'  git add yamls src && git commit -m "reorg: group {group} to michiiik layout"')
    return 0


def revert(manifest):
    print("reverting...")
    import shutil
    shutil.rmtree(os.path.join(REPO, "build/src"), ignore_errors=True)
    sh(["git", "checkout", "--", "yamls/us/rom.yaml"])
    # move files back via the recorded pairs
    for src, dst in reversed(manifest["moves"]):
        if os.path.exists(os.path.join(REPO, dst)):
            sh(["git", "mv", dst, src])
    sh(["git", "checkout", "--", "src", "include", "yamls/us/rom.yaml"])
    # include rewrites: restore from git
    sh(["git", "reset", "-q"])  # clear the staged renames git mv left behind
    sh(["git", "clean", "-fdq", "src"])
    print("reverted (includes restored from git, index reset, leftovers cleaned)")


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("cmd", choices=["plan", "apply"])
    ap.add_argument("--group", default=None)
    ap.add_argument("--no-gate", action="store_true")
    args = ap.parse_args()
    ours = parse_yaml(OUR_YAML)
    theirs = parse_yaml(os.path.join(HIPPO, "yamls/us/rom.yaml"))
    if args.cmd == "plan":
        ids = []
        for s in ours:
            m = re.fullmatch(r"fragment(\d+)(?:_.*)?", s["name"])
            if m and int(m.group(1)) not in ids:
                ids.append(int(m.group(1)))
        groups = [args.group] if args.group else [str(i) for i in sorted(ids)] + ["main"]
        for g in groups:
            seg_ren, sub_ren, problems = join_group(ours, theirs, g)
            if sub_ren is None:
                print(f"{g}: " + "; ".join(problems))
                continue
            moves = plan_files(sub_ren)
            print(f"{g}: {len(sub_ren)} subs, {len(moves)} files, {len(problems)} problems")
    else:
        if not args.group:
            print("apply needs --group")
            return 1
        return apply_group(args.group, args.no_gate)


if __name__ == "__main__":
    sys.exit(main() or 0)
