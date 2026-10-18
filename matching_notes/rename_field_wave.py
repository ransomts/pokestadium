#!/usr/bin/env python3
"""Tier C field-wave driver: run rename_field_agent.py over headers, fixup, apply.

Usage (from repo root): rename_field_wave.py <batch-tag> <header> [header ...]
                     [--model gpt-5.6-sol] [--concurrency 8]

Per batch: launch one field agent per header (concurrent), merge + fixup the rows,
append to the ledger, plan/fixup until clean, apply with the full gate, commit,
mark-committed, amend. Fixup enforces the safety rules: old must be `T.f` with f in
the inventory's safe list for T; new field name must not collide with an existing
field of T; duplicates dropped; justifications >= 15 chars.
"""
import argparse
import concurrent.futures
import os
import re
import subprocess
import sys
import time

HERE = os.path.dirname(os.path.abspath(__file__))
REPO = os.path.dirname(HERE)
PY = f"{REPO}/.venv/bin/python3"
LEDGER = os.path.join(HERE, "renames.tsv")
INVENTORY = os.path.join(HERE, "rename_fields_inventory.tsv")
ERROR_LINE_RE = re.compile(r"ledger:(\d+) \(([^)]+)\): (.+)")


def sh(cmd, timeout, **kw):
    return subprocess.run(cmd, cwd=REPO, capture_output=True, text=True, timeout=timeout, **kw)


def safe_fields_by_typedef():
    out = {}
    for line in open(INVENTORY):
        if line.startswith("#"):
            continue
        parts = line.rstrip("\n").split("\t")
        if len(parts) >= 3:
            out[(parts[0], parts[2])] = parts[1]  # (typedef, field) -> header
    return out


def struct_fields(header):
    """field names declared in every struct of the header (collision check)."""
    text = open(os.path.join(REPO, header), errors="replace").read()
    return set(re.findall(r"(?:/\*[^*]*\*/\s*)?[A-Za-z_][A-Za-z0-9_ ]*?\s\**\s*"
                          r"([A-Za-z_][A-Za-z0-9_]*)\s*(?:\[[^\]]*\])*\s*;", text))


def ledger_rows():
    rows = []
    for i, raw in enumerate(open(LEDGER), 1):
        line = raw.rstrip("\n")
        if not line.strip() or line.lstrip().startswith("#") or line.split("\t")[0] == "old":
            continue
        parts = line.split("\t")
        if len(parts) >= 6:
            rows.append((i, parts))
    return rows


def write_ledger_drop(linenos):
    out, dropped = [], []
    for i, raw in enumerate(open(LEDGER), 1):
        line = raw.rstrip("\n")
        if i in linenos:
            dropped.append(line)
            continue
        out.append(line)
    open(LEDGER, "w").write("\n".join(out) + "\n")
    return dropped


def fixup(rows, batch, log):
    safe = safe_fields_by_typedef()
    applied_news = {p[1] for _i, p in ledger_rows()
                    if p[5].startswith("applied") or p[5] in ("tested", "noop")}
    seen = set()
    kept = []
    for old, new, b, also, just in rows:
        m = re.fullmatch(r"([A-Za-z_][A-Za-z0-9_]*)\.(unk_[0-9A-Fa-f]+w?)", old)
        if not m:
            log(f"  drop {old!r}: malformed field row")
            continue
        tname, field = m.group(1), m.group(2)
        if (tname, field) not in safe:
            log(f"  drop {old}: {field} not in the safe list of {tname}")
            continue
        header = safe[(tname, field)]
        if new in struct_fields(header):
            log(f"  drop {old} -> {new}: name already a field of a struct in {header}")
            continue
        if new in applied_news or (tname, new) in seen:
            log(f"  drop {old} -> {new}: duplicate new field name")
            continue
        if len(just) < 15:
            log(f"  drop {old}: justification too short")
            continue
        seen.add((tname, new))
        kept.append((old, new, batch, "", just))
    return kept


def plan_fixup_loop(batch, log, max_rounds=6):
    for _ in range(max_rounds):
        r = sh([PY, os.path.join(HERE, "rename.py"), "plan", LEDGER, "--batch", batch], 300)
        out = r.stdout + r.stderr
        if r.returncode == 0:
            return True
        bad = {int(m.group(1)) for m in (ERROR_LINE_RE.search(l) for l in out.splitlines()) if m}
        if not bad:
            log("  plan failed with no parseable errors:\n" + out[-1200:])
            return False
        log(f"  plan round: dropping {len(bad)} row(s)")
        write_ledger_drop(bad)
    return False


def run_batch(batch, headers, args):
    wdir = os.path.join(REPO, "scratch", "rename_waves", batch)
    os.makedirs(wdir, exist_ok=True)
    logf = open(os.path.join(wdir, "driver.log"), "a")

    def log(msg):
        print(msg, flush=True)
        logf.write(msg + "\n")
        logf.flush()

    log(f"=== field batch {batch}: {len(headers)} headers ===")
    t0 = time.time()

    def run_agent(h):
        cmd = [PY, os.path.join(HERE, "rename_field_agent.py"), "--header", h,
               "--batch", batch, "--model", args.model, "--out", wdir]
        try:
            r = sh(cmd, 2400)
            return h, r.returncode, (r.stdout + r.stderr).strip()[-300:]
        except subprocess.TimeoutExpired:
            return h, 124, "TIMEOUT"

    results = []
    with concurrent.futures.ThreadPoolExecutor(max_workers=args.concurrency) as ex:
        futs = [ex.submit(run_agent, h) for h in headers]
        for fut in concurrent.futures.as_completed(futs):
            h, rc, tail = fut.result()
            results.append((h, rc))
            if rc != 0:
                log(f"  agent FAILED {h} (rc={rc}): {tail}")

    rows = []
    import glob
    for p in sorted(glob.glob(os.path.join(wdir, f"{batch}_*.tsv"))):
        for line in open(p):
            parts = line.rstrip("\n").split("\t")
            if len(parts) >= 6 and parts[0] != "TypedefName":
                rows.append((parts[0], parts[1], parts[2], parts[3], parts[4]))
    log(f"  agents done ({time.time()-t0:.0f}s): {len(rows)} field rows proposed")

    # idempotent re-run: strip this batch's pending rows first
    removed = 0
    out = []
    for i, raw in enumerate(open(LEDGER), 1):
        line = raw.rstrip("\n")
        parts = line.split("\t")
        if (len(parts) >= 6 and parts[2] == batch
                and not parts[5].startswith("applied") and parts[0] != "old"
                and not line.lstrip().startswith("#")):
            removed += 1
            continue
        out.append(line)
    open(LEDGER, "w").write("\n".join(out) + "\n")
    if removed:
        log(f"  idempotent re-run: replaced {removed} pending {batch} row(s)")

    kept = fixup(rows, batch, log)
    log(f"  fixup kept {len(kept)} of {len(rows)} rows")
    if not kept:
        log("  nothing to apply - batch skipped")
        return False
    with open(LEDGER, "a") as f:
        for old, new, b, also, just in kept:
            f.write(f"{old}\t{new}\t{b}\t{also}\t{just}\tpending\n")

    if not plan_fixup_loop(batch, log):
        log(f"  STOP: {batch} not resolvable - rows stay pending")
        return False

    r = subprocess.run([PY, os.path.join(HERE, "rename.py"), "apply", LEDGER,
                        "--batch", batch, "--sample", "5"], cwd=REPO, timeout=7200)
    if r.returncode != 0:
        log(f"  STOP: apply/gate FAILED for {batch} (auto-reverted; rows pending)")
        return False

    n = sum(1 for _i, p in ledger_rows() if p[2] == batch and p[5].startswith("applied"))
    short = ", ".join(os.path.basename(h) for h in headers[:4]) + (", ..." if len(headers) > 4 else "")
    sh(["git", "add", "-A", ":!.claude", ":!scratch"], 60)
    r = sh(["git", "commit", "-m", f"rename: {batch} ({n} struct fields; {short})"], 120)
    if r.returncode != 0:
        log(f"  STOP: git commit failed: {r.stdout}\n{r.stderr}")
        return False
    sha = sh(["git", "rev-parse", "--short", "HEAD"], 30).stdout.strip()
    sh([PY, os.path.join(HERE, "rename.py"), "mark-committed", LEDGER, sha, "--batch", batch], 60)
    sh(["git", "add", "-A", ":!.claude", ":!scratch"], 60)
    sh(["git", "commit", "--amend", "--no-edit"], 120)
    log(f"  committed {sha}: {n} field renames, {time.time()-t0:.0f}s total")
    return True


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("batch")
    ap.add_argument("headers", nargs="+")
    ap.add_argument("--model", default="gpt-5.6-sol")
    ap.add_argument("--concurrency", type=int, default=8)
    args = ap.parse_args()

    dirty = sh(["git", "status", "--porcelain"], 30).stdout.splitlines()
    bad = [l for l in dirty if not l.startswith("??") and "matching_notes/" not in l]
    if bad:
        print(f"refusing: tracked files dirty: {bad[:5]}")
        sys.exit(1)
    ok = run_batch(args.batch, args.headers, args)
    sys.exit(0 if ok else 1)


if __name__ == "__main__":
    main()
