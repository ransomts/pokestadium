#!/usr/bin/env python3
"""F6 rename wave driver - runs one or more waves of the agent rename recipe end-to-end.

Usage (from repo root, .venv/bin/python3):
  rename_wave.py run <queue_wave> [count] [--concurrency 16] [--model gptoss-120b]
                  [--stop-after-plan] [--max 15]

queue_wave: the wave number in matching_notes/rename_queue.txt (batch tag becomes w<+4>).
Per wave: launch rename_agent.py on each queue file (concurrent), salvage + fixup the
proposals, append to the ledger, plan/fixup until preflight is clean, apply with the full
build gate, commit, mark-committed, amend. Every 4th queue wave: make diff-init.

Fixup rules (the manual ones from NOTES.md, automated):
  - drop asset-VRAM anchors (D_[0-9A-F]000xxx) and dual-source symbols (in BOTH
    symbol_addrs.txt and linker_scripts/us/undefined_syms.ld)
  - drop protected symbols and rows whose old is already applied
  - re-prefix mis-prefixed rows (agents write D_80078FXX vars as func_...): if `old`
    exists nowhere, retry with func_<->D_ prefix swapped
  - drop new-name collisions with the ledger, with already-named symbol_addrs entries,
    and duplicates within the wave
  - on preflight error: drop the offending row (a dropped proposal is a parked symbol)
"""
import argparse
import concurrent.futures
import glob
import os
import re
import subprocess
import sys
import time

HERE = os.path.dirname(os.path.abspath(__file__))
REPO = os.path.dirname(HERE)
PY = f"{REPO}/.venv/bin/python3"
QUEUE = os.path.join(HERE, "rename_queue.txt")
LEDGER = os.path.join(HERE, "renames.tsv")
QUEUE_FILE_RE = re.compile(r"^(\d+)\t(\S+\.c)$")
ERROR_LINE_RE = re.compile(r"ledger:(\d+) \(([^)]+)\): (.+)")
VRAM_ANCHOR_RE = re.compile(r"D_[0-9A-F]000[0-9A-F]{3}$")
SEGMENT_ADDR_RE = re.compile(r"D_[0-9A-F]{7}$")  # 7-hex-digit = segment/VRAM space (D_4007B60 etc.)
BATCH_OFFSET = 4  # queue wave 1 -> batch w5
# C keywords + annotation tokens agents file as also-pair SOURCES (`typedef:Foo`,
# `struct:Bar`) - no symbol can be named these, so the pair is always noise and
# rewriting the word would corrupt every declaration in the tree (w10 lesson)
ALSO_SOURCE_BLOCKLIST = {
    "auto", "break", "case", "char", "const", "continue", "default", "do",
    "double", "else", "enum", "extern", "float", "for", "goto", "if", "int",
    "long", "register", "return", "short", "signed", "sizeof", "static",
    "struct", "switch", "typedef", "union", "unsigned", "void", "volatile",
    "while", "type", "Type", "Struct", "Union", "Enum", "Callback", "Func",
}


def sh(cmd, timeout, **kw):
    return subprocess.run(cmd, cwd=REPO, capture_output=True, text=True,
                          timeout=timeout, **kw)


class RepoFacts:
    """One-time loads for fixup decisions."""

    def __init__(self):
        self.sa_names = set()       # all symbol_addrs* entries
        self.sa_code = set()         # symbol_addrs_code.txt entries
        self.undefined_syms = set()  # undefined_syms.ld entries
        self.protected = set()
        for f in ["linker_scripts/us/symbol_addrs_code.txt",
                  "linker_scripts/us/symbol_addrs.txt",
                  "linker_scripts/us/symbol_addrs_ultralib.txt"]:
            p = os.path.join(REPO, f)
            if os.path.exists(p):
                for line in open(p):
                    m = re.match(r"(\S+)\s*=", line)
                    if m:
                        self.sa_names.add(m.group(1))
                        if "code" in f:
                            self.sa_code.add(m.group(1))
        ld = os.path.join(REPO, "linker_scripts/us/undefined_syms.ld")
        if os.path.exists(ld):
            for m in re.finditer(r"([A-Za-z_][A-Za-z0-9_]*)\s*=", open(ld).read()):
                self.undefined_syms.add(m.group(1))
        prot = os.path.join(HERE, "renames_protected.txt")
        for line in open(prot):
            line = line.strip()
            if line and not line.startswith("#"):
                self.protected.add(line)
        # one big blob of all C sources for existence checks
        self.src_blob = []
        for root in ("src", "include"):
            for dirpath, _dirs, files in os.walk(os.path.join(REPO, root)):
                for fn in sorted(files):
                    if fn.endswith((".c", ".h")):
                        self.src_blob.append(open(os.path.join(dirpath, fn),
                                                  errors="replace").read())
        self.src_blob = "\n".join(self.src_blob)

    def referenced(self, sym):
        if sym in self.sa_names:
            return True
        pat = re.compile(r"(?<![A-Za-z0-9_])" + re.escape(sym) + r"(?![A-Za-z0-9_])")
        return bool(pat.search(self.src_blob))


def read_queue_wave(n):
    files, wave = [], None
    for line in open(QUEUE):
        if line.startswith("## wave "):
            wave = int(line.split()[-1])
            continue
        m = QUEUE_FILE_RE.match(line.strip())
        if m and wave == n:
            files.append(m.group(2))
    return files


def ledger_rows():
    """(lineno, [fields]) for every data row; header/comment lines skipped."""
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


def remove_batch_pending(batch):
    """Strip pending (not applied) rows of `batch` - makes wave re-runs idempotent."""
    out, removed = [], 0
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
    return removed


def fixup(rows, facts, batch, log, vetoes):
    """rows: list of (old,new,batch,also,just) tuples from the wave's merged.tsv."""
    applied_olds, applied_news = set(), set()
    for _i, p in ledger_rows():
        if p[5].startswith("applied") or p[5] in ("tested", "noop"):
            applied_olds.add(p[0])
            applied_news.add(p[1])
    seen_old, seen_new = set(), set()
    kept = []
    for old, new, b, also, just in rows:
        if old in vetoes:
            log(f"  drop {old}: vetoed by {batch}/veto.txt")
            continue
        if VRAM_ANCHOR_RE.fullmatch(old) or SEGMENT_ADDR_RE.fullmatch(old):
            log(f"  drop {old}: asset-VRAM/segment address (out of scope)")
            continue
        if old in facts.undefined_syms:
            log(f"  drop {old}: defined in undefined_syms.ld (never-touch)")
            continue
        if old in facts.protected:
            log(f"  drop {old}: protected")
            continue
        if old in applied_olds:
            log(f"  drop {old}: already applied in an earlier batch")
            continue
        if old in seen_old:
            log(f"  drop {old}: duplicate old within wave")
            continue
        # mis-prefix repair
        if not facts.referenced(old):
            alt = ("D_" + old[5:]) if old.startswith("func_") else ("func_" + old[2:])
            if re.fullmatch(r"func_[0-9A-F]{8}|D_[0-9A-F]{8}", alt) and facts.referenced(alt):
                log(f"  fix  {old} -> {alt} (mis-prefixed by the agent)")
                old = alt
            else:
                log(f"  drop {old}: not defined or referenced anywhere")
                continue
        if old in facts.protected or old in applied_olds or old in seen_old:
            log(f"  drop {old}: protected/applied/dup after prefix fix")
            continue
        if new in applied_news or new in facts.sa_names or new in facts.protected:
            log(f"  drop {old} -> {new}: new name already in use")
            continue
        if new in seen_new:
            log(f"  drop {old} -> {new}: duplicate new within wave")
            continue
        # also column: keep only well-formed old:new pairs
        if also:
            pairs = [p.strip() for p in also.split(",") if ":" in p]
            pairs = [p for p in pairs
                     if re.fullmatch(r"[A-Za-z_][A-Za-z0-9_]*:[A-Za-z_][A-Za-z0-9_]*", p)]
            also = ",".join(pairs)
        seen_old.add(old)
        seen_new.add(new)
        kept.append((old, new, batch, also, just))
    # also-pair guards (w5 + w10 orphan/corruption lessons): agents file type
    # annotations as also pairs (`old:Struct`, `typedef:Name`); a pair whose
    # old is a main-row old would clobber that row's rename in the word map,
    # and a pair whose old is a C keyword would rewrite the keyword itself.
    # The main row owns the symbol - drop the pair.
    main_olds = {k[0] for k in kept}
    out = []
    for old, new, b, also, just in kept:
        if also:
            pairs = [p for p in also.split(",")
                     if p.split(":", 1)[0].strip() not in main_olds
                     and p.split(":", 1)[0].strip() not in ALSO_SOURCE_BLOCKLIST]
            also = ",".join(pairs)
        out.append((old, new, b, also, just))
    return out


def plan_fixup_loop(batch, log, max_rounds=6):
    """Run rename.py plan; drop rows named in errors; repeat until clean or rounds out."""
    for rnd in range(max_rounds):
        r = sh([PY, os.path.join(HERE, "rename.py"), "plan", LEDGER, "--batch", batch], 1800)
        out = r.stdout + r.stderr
        if r.returncode == 0:
            log(f"  plan clean after {rnd} fixup round(s)")
            return True
        bad = set()
        for line in out.splitlines():
            m = ERROR_LINE_RE.search(line)
            if m:
                bad.add((int(m.group(1)), m.group(2), m.group(3)))
        if not bad:
            log("  plan failed with no parseable row errors:\n" + out[-1500:])
            return False
        linenos = set()
        for lineno, old, msg in sorted(bad):
            log(f"  drop {old} (ledger:{lineno}): {msg}")
            linenos.add(lineno)
        # only drop rows that belong to this batch (plan only errors on selected rows)
        victims = write_ledger_drop(linenos)
        assert victims, "plan named rows but drop found none - ledger changed underneath us"
    return False


def run_wave(qwave, args, facts):
    batch = f"w{qwave + BATCH_OFFSET}"
    wdir = os.path.join(REPO, "scratch", "rename_waves", batch)
    os.makedirs(wdir, exist_ok=True)
    logf = open(os.path.join(wdir, "driver.log"), "a")

    def log(msg):
        print(msg, flush=True)
        logf.write(msg + "\n")
        logf.flush()

    files = read_queue_wave(qwave)
    if not files:
        log(f"wave {qwave}: no files in queue - skipping")
        return False
    log(f"=== wave {qwave} (batch {batch}): {len(files)} files ===")
    t0 = time.time()

    # 1. agents (skip files that already produced a non-empty .tsv in an earlier attempt)
    def agent_outfile(f):
        return os.path.join(wdir, f"{batch}_{os.path.basename(f)}.tsv")

    todo = [f for f in files
            if not (os.path.exists(agent_outfile(f)) and os.path.getsize(agent_outfile(f)) > 0)]
    if len(todo) < len(files):
        log(f"  reusing {len(files) - len(todo)} agent result(s) from an earlier attempt")

    def run_agent(f):
        cmd = [PY, os.path.join(HERE, "rename_agent.py"), "--file", f,
               "--batch", batch, "--model", args.model, "--max", str(args.max),
               "--max-tokens", str(args.max_tokens), "--out", wdir]
        try:
            r = sh(cmd, 2400)
            return f, r.returncode, (r.stdout + r.stderr).strip()[-300:]
        except subprocess.TimeoutExpired:
            return f, 124, "TIMEOUT"

    results = []
    with concurrent.futures.ThreadPoolExecutor(max_workers=args.concurrency) as ex:
        futs = [ex.submit(run_agent, f) for f in todo]
        for fut in concurrent.futures.as_completed(futs):
            f, rc, tail = fut.result()
            results.append((f, rc))
            if rc != 0:
                log(f"  agent FAILED {f} (rc={rc}): {tail}")
    ok = [f for f, rc in results if rc == 0]
    log(f"  agents done in {time.time()-t0:.0f}s: {len(ok)}/{len(files)} ok")

    # 2. salvage
    merged = os.path.join(wdir, "merged.tsv")
    r = sh([PY, os.path.join(HERE, "rename_salvage.py"), batch,
            os.path.join(wdir, f"{batch}_*.raw"), merged], 120)
    if r.returncode != 0:
        log(f"  salvage failed: {r.stdout}\n{r.stderr}")
        return False
    rows = []
    for line in open(merged):
        parts = line.rstrip("\n").split("\t")
        if len(parts) >= 6 and parts[0] != "old":
            rows.append((parts[0], parts[1], parts[2], parts[3], parts[4]))
    log(f"  salvage: {len(rows)} proposal rows")

    # 3. fixup + append (idempotent: strip this batch's pending rows first)
    vetoes = set()
    veto_path = os.path.join(wdir, "veto.txt")
    if os.path.exists(veto_path):
        for line in open(veto_path):
            line = line.strip()
            if line and not line.startswith("#"):
                vetoes.add(line)
    removed = remove_batch_pending(batch)
    if removed:
        log(f"  idempotent re-run: replaced {removed} pending {batch} row(s)")
    kept = fixup(rows, facts, batch, log, vetoes)
    log(f"  fixup kept {len(kept)} of {len(rows)} rows")
    if not kept:
        log("  nothing to apply - wave skipped (no commit)")
        return False
    with open(LEDGER, "a") as f:
        for old, new, b, also, just in kept:
            f.write(f"{old}\t{new}\t{b}\t{also}\t{just}\tpending\n")

    # 4b. concurrent-session safety: drop rows whose old name appears in a
    # pre-dirty file (rewriting there would mix hunks / mixed naming)
    pre_dirty_paths = []
    r0 = sh(["git", "status", "--porcelain"], 30)
    for line in r0.stdout.splitlines():
        if line and not line.startswith("??") and "matching_notes/" not in line:
            pre_dirty_paths.append(line[3:].strip())
    if pre_dirty_paths and kept:
        dirty_text = "\n".join(
            open(os.path.join(REPO, p), errors="replace").read()
            for p in pre_dirty_paths if os.path.exists(os.path.join(REPO, p)))
        drop_rows = []
        for _i, p in ledger_rows():
            if p[2] == batch and not p[5].startswith("applied"):
                if re.search(r"(?<![A-Za-z0-9_])" + re.escape(p[0]) + r"(?![A-Za-z0-9_])", dirty_text):
                    drop_rows.append((_i, p[0]))
        if drop_rows:
            log(f"  dropping {len(drop_rows)} row(s) that touch a concurrently-dirty file "
                f"({[d[1] for d in drop_rows[:3]]}...)")
            write_ledger_drop({d[0] for d in drop_rows})

    # 4. plan / fixup until clean
    if not plan_fixup_loop(batch, log):
        log(f"  STOP: batch {batch} not resolvable - rows stay pending in the ledger")
        return False
    if args.stop_after_plan:
        log(f"  --stop-after-plan: {batch} rows pending; not applying")
        return True

    # 5. apply + gate (concurrent-session safe: scoped adds, mixed-hunk guard)
    pre_dirty = set()
    r0 = sh(["git", "status", "--porcelain"], 30)
    for line in r0.stdout.splitlines():
        if line and not line.startswith("??") and "matching_notes/" not in line:
            pre_dirty.add(line[3:].strip())
    env_allow = dict(os.environ, RENAME_ALLOW_DIRTY="1")
    if pre_dirty:
        env_allow["RENAME_EXCLUDE_FILES"] = "\n".join(pre_dirty)
    r = subprocess.run([PY, os.path.join(HERE, "rename.py"), "apply", LEDGER,
                        "--batch", batch, "--sample", "5"],
                       cwd=REPO, timeout=7200, env=env_allow)
    if r.returncode != 0:
        log(f"  STOP: apply/gate FAILED for {batch} (auto-reverted; rows pending)")
        return False
    try:
        touched = [t for t in open(os.path.join(REPO, "scratch", "last_apply_touched.txt")).read().splitlines() if t]
    except OSError:
        touched = []
    mixed = [t for t in touched if t in pre_dirty]
    if mixed:
        log(f"  STOP: rewrite touched files that were ALREADY dirty before this wave "
            f"(another session's WIP would ride into our commit): {mixed[:3]}")
        log(f"  the batch is applied+gated on disk; commit manually after coordinating")
        return False

    # 6. commit + mark + amend (scoped: only this wave's files + the ledger)
    # count ONLY this run's rows ("applied", not "applied@<old-era-sha>"):
    # batch tags w5+ collide with the Oct-17/18 era (w1-w30) in the ledger
    n = sum(1 for _i, p in ledger_rows() if p[2] == batch and p[5] == "applied")
    if n == 0:
        n = sum(1 for _i, p in ledger_rows() if p[2] == batch and p[5].startswith("applied"))
    short = ", ".join(os.path.basename(f) for f in files[:4]) + (", ..." if len(files) > 4 else "")
    add_cmd = ["git", "add"] + [t for t in touched if "/asm/" not in t] + [LEDGER]
    r = sh(add_cmd, 60)
    r = sh(["git", "commit", "-m", f"rename: {batch} ({n} symbols; {short})"], 120)
    if r.returncode != 0:
        log(f"  STOP: git commit failed: {r.stdout}\n{r.stderr}")
        return False
    sha = sh(["git", "rev-parse", "--short", "HEAD"], 30).stdout.strip()
    r = sh([PY, os.path.join(HERE, "rename.py"), "mark-committed", LEDGER, sha,
            "--batch", batch], 60)
    if r.returncode != 0:
        log(f"  STOP: mark-committed failed: {r.stdout}\n{r.stderr}")
        return False
    sh(add_cmd, 60)
    r = sh(["git", "commit", "--amend", "--no-edit"], 120)
    if r.returncode != 0:
        log(f"  STOP: amend failed: {r.stdout}\n{r.stderr}")
        return False
    log(f"  committed {sha}: {n} symbols, {time.time()-t0:.0f}s total")

    # 7. every 4th wave: diff-init
    if qwave % 4 == 0:
        env = dict(os.environ,
                   PATH=f"{REPO}/.venv/bin:{os.path.expanduser('~')}/local/bin:/usr/local/bin:/usr/bin:/bin")
        r = subprocess.run(["make", "diff-init", f"PYTHON={REPO}/.venv/bin/python3"],
                           cwd=REPO, env=env, timeout=3600, capture_output=True, text=True)
        log(f"  diff-init rc={r.returncode}" + ("" if r.returncode == 0
                                                else f": {r.stdout[-500:]} {r.stderr[-500:]}"))
    return True


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("cmd", choices=["run"])
    ap.add_argument("wave", type=int)
    ap.add_argument("count", nargs="?", type=int, default=1)
    ap.add_argument("--concurrency", type=int, default=16)
    ap.add_argument("--model", default="gptoss-120b")
    ap.add_argument("--max", type=int, default=15)
    ap.add_argument("--max-tokens", type=int, default=4096)
    ap.add_argument("--stop-after-plan", action="store_true")
    args = ap.parse_args()

    dirty = sh(["git", "status", "--porcelain"], 30).stdout.splitlines()
    bad = [l for l in dirty if not l.startswith("??") and "matching_notes/" not in l]
    if bad:
        print(f"NOTE: tracked files dirty (concurrent session? per-wave guards handle it): {bad[:3]}")

    facts = RepoFacts()
    done = 0
    for q in range(args.wave, args.wave + args.count):
        if not run_wave(q, args, facts):
            print(f"driver stopped at queue wave {q}")
            break
        done += 1
    print(f"{done} wave(s) completed")


if __name__ == "__main__":
    main()
