#!/usr/bin/env python3
"""Batch driver for the semantic reorg: apply N groups, one gate, one commit.

Usage: reorg_batch.py <group> <group> ... | --all [--batch-size 8]
Applies each group via reorg.py --no-gate (per-group manifests saved), then ONE
gate (extract + full make). On failure: reverts everything and re-applies in
halves to isolate the bad group. On success: one commit."""
import argparse
import json
import os
import subprocess
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
REPO = os.path.dirname(HERE)
PY = f"{REPO}/.venv/bin/python3"


def sh(cmd, **kw):
    return subprocess.run(cmd, cwd=REPO, capture_output=True, text=True, **kw)


def gate():
    env = dict(os.environ,
               PATH=f"{REPO}/.venv/bin:{os.path.expanduser('~')}/local/bin:/usr/local/bin:/usr/bin:/bin")
    for target in ("extract", "-j24"):
        r = subprocess.run(["make", target, f"PYTHON={PY}"], cwd=REPO, env=env,
                           timeout=3600, capture_output=True, text=True)
        ok = r.returncode == 0
        if target == "-j24":
            ok = ok and "build/pokestadium-us.z64: OK" in (r.stdout + r.stderr)
        print(f"  make {target}: {'OK' if ok else 'FAILED'}", flush=True)
        if not ok:
            open(f"{REPO}/scratch/reorg_gate.log", "w").write(r.stdout + r.stderr)
            return False
    return True


def apply_group(g):
    r = subprocess.run([PY, f"{HERE}/reorg.py", "apply", "--group", str(g), "--no-gate"],
                       cwd=REPO, capture_output=True, text=True)
    ok = r.returncode == 0
    src = os.path.join(REPO, "scratch", "reorg_manifest.json")
    dst = os.path.join(REPO, "scratch", f"reorg_manifest_{g}.json")
    if os.path.exists(src):
        os.replace(src, dst)
    print(f"group {g}: {'ok' if ok else 'FAILED'}\n" + r.stdout[-400:], flush=True)
    return ok


def revert_groups(groups):
    import reorg  # noqa: F401 - same dir import
    sys.path.insert(0, HERE)
    import importlib
    reorg = importlib.import_module("reorg")
    for g in reversed(groups):
        p = os.path.join(REPO, "scratch", f"reorg_manifest_{g}.json")
        if os.path.exists(p):
            reorg.revert(json.load(open(p)))
    print("reverted all", flush=True)


def run(groups):
    applied = []
    bad = []
    for g in groups:
        if not apply_group(g):
            print(f"group {g} failed to apply - reverting all")
            revert_groups(applied)
            return False
        applied.append(g)
    if gate():
        sh(["git", "add", "yamls", "src"])
        names = " ".join(str(g) for g in groups[:6]) + (" ..." if len(groups) > 6 else "")
        sh(["git", "commit", "-m", f"reorg: groups {names} to michiiik layout ({len(groups)} groups)"])
        print(f"committed {len(groups)} groups", flush=True)
        for g in groups:
            p = os.path.join(REPO, "scratch", f"reorg_manifest_{g}.json")
            if os.path.exists(p):
                os.remove(p)
        return True
    print("gate failed - reverting all, then bisecting", flush=True)
    revert_groups(applied)
    if len(groups) == 1:
        print(f"group {groups[0]} is the failure - needs manual attention", flush=True)
        return False
    # bisect, but ALWAYS continue with the remaining halves
    ok_first = run(groups[:len(groups) // 2])
    ok_second = run(groups[len(groups) // 2:])
    return ok_first and ok_second


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("groups", nargs="*")
    ap.add_argument("--all", action="store_true")
    ap.add_argument("--batch-size", type=int, default=8)
    args = ap.parse_args()
    if args.all:
        r = sh([PY, f"{HERE}/reorg.py", "plan"])
        clean, skipped = [], []
        for line in r.stdout.splitlines():
            line = line.strip()
            if not line or line.startswith("main"):
                continue
            gid, rest = line.split(":", 1)
            if not gid.isdigit():
                continue
            n_prob = int(rest.split("problems")[0].split(",")[-1])
            (clean if n_prob == 0 else skipped).append(int(gid))
        groups = [g for g in clean if g != 16]  # pilot done
        if skipped:
            print(f"SKIPPING problem groups (manual follow-up): {skipped}", flush=True)
    else:
        groups = [int(g) for g in args.groups]
    print(f"groups: {groups}", flush=True)
    for i in range(0, len(groups), args.batch_size):
        if not run(groups[i:i + args.batch_size]):
            print(f"BATCH FAILED at {groups[i:i + args.batch_size]} - stopping")
            return 1
    return 0


if __name__ == "__main__":
    sys.exit(main())
