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
    """(segment_renames, subseg_renames, problems) for one group of ours."""
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
    ours = parse_yaml(OUR_YAML)
    theirs = parse_yaml(os.path.join(HIPPO, "yamls/us/rom.yaml"))
    seg_ren, sub_ren, problems = join_group(ours, theirs, group)
    if sub_ren is None:
        print("\n".join(problems))
        return 1
    moves = plan_files(sub_ren)
    print(f"group {group}: {len(sub_ren)} subsegment renames, {len(moves)} file moves, "
          f"{len(seg_ren)} segment renames, {len(problems)} problems")
    for p in problems:
        print(f"  ! {p}")
    manifest = {"seg": seg_ren, "sub": sub_ren, "moves": moves}
    open(os.path.join(REPO, "scratch", "reorg_manifest.json"), "w").write(json.dumps(manifest))

    yaml = open(OUR_YAML).read()
    for oname, tname in seg_ren:
        yaml = yaml.replace(f"- name: {oname}\n", f"- name: {tname}\n")
    for op, tp, _on, _tn in sub_ren:
        yaml = yaml.replace(f"{op}]", f"{tp}]").replace(f"{op},", f"{tp},")
        yaml = re.sub(re.escape(op) + r"(?=[\],\s#}])", tp, yaml)
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

    # include rewrites: old fragment headers -> new names, everywhere
    # (group header: fragments/N/fragmentN.h -> <their dir>/<semantic>.h; michiiik
    # keeps segment NAMES numeric - only subsegment paths are semantic)
    header_moves = []
    group_dirs = {tuple(op.split("/")[:-1]): tuple(tp.split("/")[:-1])
                  for op, tp, _on, _tn in sub_ren}
    for ourdir, theirdir in group_dirs.items():
        oldh_base = "fragment" + ourdir[-1] + ".h"  # fragment16.h
        newh_base = theirdir[-1] + ".h"             # credits.h
        oldh_path = "/".join(["src"] + list(ourdir) + [oldh_base])
        newh_path = "/".join(["src"] + list(theirdir) + [newh_base])
        if oldh_base == newh_base or not os.path.exists(os.path.join(REPO, oldh_path)):
            continue
        os.makedirs(os.path.dirname(os.path.join(REPO, newh_path)), exist_ok=True)
        r = sh(["git", "mv", oldh_path, newh_path])
        if r.returncode != 0:
            print(f"  ! header mv failed {oldh_path}: {r.stderr.strip()}")
        else:
            header_moves.append((oldh_path, newh_path))
            manifest["moves"].append((oldh_path, newh_path))
            pat = re.compile(r'(#include\s+")' + re.escape(oldh_base) + r'(")')
            n = 0
            for root in ("src", "include"):
                for dp, _d, fs in os.walk(os.path.join(REPO, root)):
                    for fn in fs:
                        if not fn.endswith((".c", ".h")):
                            continue
                        p = os.path.join(dp, fn)
                        t = open(p, errors="replace").read()
                        t2, k = pat.subn(r"\g<1>" + newh_base + r"\g<2>", t)
                        if k:
                            open(p, "w").write(t2)
                            n += k
            print(f"  header {oldh_base} -> {newh_base}: moved, {n} include rewrites")
    open(os.path.join(REPO, "scratch", "reorg_manifest.json"), "w").write(json.dumps(manifest))

    for op, tp, _on, _tn in sub_ren:
        oldh = os.path.basename(op) + ".h"
        newh = os.path.basename(tp) + ".h"
        if oldh == newh:
            continue
        pat = re.compile(r'(#include\s+")' + re.escape(oldh) + r'(")')
        for root in ("src", "include"):
            for dp, _d, fs in os.walk(os.path.join(REPO, root)):
                for fn in fs:
                    if not fn.endswith((".c", ".h")):
                        continue
                    p = os.path.join(dp, fn)
                    t = open(p, errors="replace").read()
                    t2, k = pat.subn(r"\g<1>" + newh + r"\g<2>", t)
                    if k:
                        open(p, "w").write(t2)
                        print(f"  includes: {os.path.relpath(p, REPO)}: {oldh} -> {newh} ({k})")

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
    print("reverted (includes restored from git)")


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("cmd", choices=["plan", "apply"])
    ap.add_argument("--group", default=None)
    ap.add_argument("--no-gate", action="store_true")
    args = ap.parse_args()
    ours = parse_yaml(OUR_YAML)
    theirs = parse_yaml(os.path.join(HIPPO, "yamls/us/rom.yaml"))
    if args.cmd == "plan":
        groups = [args.group] if args.group else (
            [s["name"][len("fragment"):] for s in ours if s["name"].startswith("fragment")] + ["main"])
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
