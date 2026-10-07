#!/usr/bin/env python3
"""digest.py - run the five matching oracles on a function and write ONE compact Markdown digest.

USAGE (repo root; repo venv python)
  .venv/bin/python3 matching_notes/digest.py FUNC [--src src/file.c] [--out FILE] [--fast]
  .venv/bin/python3 matching_notes/digest.py --all-unmatched [--out-dir DIR] [--fast] [-j N]
  options: --repo DIR        run the oracles of (and analyse) this checkout (default: the one holding
                             this script). round.sh start passes the agent worktree.
           --score N         score to show when no draft build is possible (e.g. from an assignment)
           --timeout S       per-oracle timeout (default 30 s; draft-compiling oracles get 1.5x)
           --bisect-timeout S  ido_bisect default-set timeout (default 90 s; the default set of ~30
                             switches takes ~60 s at -j 6 on an idle machine)
           --bisect-jobs N   ido_bisect -j (default 6; 3 under --all-unmatched)
           --limit N, --funcs a,b   (--all-unmatched) only the first N / only these functions

WHAT IT RUNS (each in its own subprocess, cwd = repo; nothing under src/ or build/ is edited - the
oracles that need the draft enabled do that in their own scratch copies)
  siblings    corpus.py siblings FUNC --limit 3 --c
  near        corpus.py near FUNC --draft --c        (draft exists; falls back to plain near if the
              corpus.py near FUNC --c                 draft does not compile)  (no draft: uses
                                                      /tmp/fd_last_FUNC.txt or the rarest windows)
  accessmap   accessmap.py FUNC --src SRC            (table of the 2 busiest bases + all flags)
              accessmap.py FUNC --src SRC --draft    (draft exists: TARGET vs DRAFT diff, SHIFTED)
  symcheck    symcheck.py FUNC --src SRC             (H/M flags)
  ido_bisect  ido_bisect.py SRC FUNC -j N            (draft exists and not --fast: rows with hit > 0
                                                      and a one-line reading of them, made by THIS
                                                      script from ido_bisect's READING IT rules)
              ido_bisect.py SRC FUNC --switches uopt-nounroll   (--fast, or default set timed out:
                                                      baseline build only, for the current score)

OUTPUT
  FILE (default build/digests/FUNC.md): header (function, file, size, draft?, current score) and one
  short section per oracle with only the actionable lines, capped at ~150 lines. The full output of
  every oracle (and the exact commands, exit codes, times) goes to FILE.d/.
  --all-unmatched: one DIR/FUNC.md (+ .d/) per GLOBAL_ASM function, 4 at a time (-j), at most 2
  ido_bisect runs at once, plus DIR/INDEX.md (one line per function: best sibling, draft?, score,
  flag count). DIR defaults to build/digests/.
  Exit status: 0 when the digest was written (failed/timed-out oracles are reported inside it),
  2 on bad arguments / unknown function.

CONCURRENCY: corpus.py near --draft compiles into build/corpus/draft/<file>.c and accessmap.py --draft
into scratch/accessmap_dev/draft/<path>; two runs on functions of the same file would clobber each
other, so those two oracles take a per-(repo, tool, file) flock in $TMPDIR/digest_locks/.
"""
import argparse
import concurrent.futures
import datetime
import fcntl
import glob
import hashlib
import os
import re
import signal
import subprocess
import sys
import tempfile
import threading
import time

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)
import round_prompts  # noqa: E402  (draft detection + open-function scan)

MAX_LINES = 150
LINE_W = 150
SCORE_SWITCH = "uopt-nounroll"   # cheapest switch: baseline build + one identical-code variant

# ido_bisect switch -> what owning a diff line means (condensed from ido_bisect.py "READING IT")
SWITCH_CLASSES = [
    (("uopt-nokpicopt", "uopt-no_const_in_reg"),
     "constant/%hi-%lo address temp: change where the address/constant is first formed "
     "(base-pointer local vs D_x[i] at each use, &D_x[i] once, function static)"),
    (("uopt-nordstore", "uopt-norlodrstropt"),
     "register promotion of a memory variable: change aliasing (local copy of a global, "
     "take/drop a local's address, move the store into/out of the loop)"),
    (("uopt-Olimit1", "cc-O1"),
     "global-optimizer temp (PRE/CSE/strength reduction/LICM): write it inline at the use, drop cursor locals"),
    (("uopt-rege4", "uopt-rege16", "uopt-regr4", "uopt-regr16", "uopt-doassoc", "uopt-varref", "uopt-moremotion",
      "uopt-docodehoist"),
     "uopt colouring-priority tie: add/remove one use, reuse a variable, reorder independent statements, "
     "re-associate (a*2)+b vs b+(a*2)"),
    (("as1-nobopt", "as1-no_branch_target"),
     "as1 delay-slot fill from the branch target: invert the if, swap if/else, change the target block's first statement"),
    (("as1-noxbb", "as1-aggr_xbb", "as1-noglobal", "as1-nopeep", "as1-noswpipe", "as1-multi_issue"),
     "as1 scheduling: usually downstream of a register/dependency diff - fix registers first"),
    (("ugen-nooffsetopt",), "ugen base+offset folding: how the address expression / struct access is written (guess)"),
    (("uopt-createbb",), "basic-block formation (guess)"),
]


def switch_class(name):
    for names, desc in SWITCH_CLASSES:
        if name in names:
            return desc
    return "see ido_bisect.py --list"


def clip(s, w=LINE_W):
    s = s.rstrip()
    return s if len(s) <= w else s[:w - 3] + "..."


# ---------------------------------------------------------------------------------- running
class Result:
    def __init__(self, name, cmd, out="", rc=None, secs=0.0, timed_out=False, skipped=None):
        self.name, self.cmd, self.out, self.rc, self.secs = name, cmd, out, rc, secs
        self.timed_out, self.skipped = timed_out, skipped

    @property
    def ok(self):
        return self.skipped is None and not self.timed_out and self.rc == 0

    def status(self):
        if self.skipped:
            return "skipped (%s)" % self.skipped
        if self.timed_out:
            return "TIMED OUT after %.0f s" % self.secs
        if self.rc != 0:
            last = [l for l in self.out.strip().splitlines() if l.strip()][-1:] or ["(no output)"]
            return "FAILED (exit %s): %s" % (self.rc, clip(last[0], 120))
        return "ok, %.1f s" % self.secs


class flocked:
    """Exclusive flock keyed by an arbitrary string (works across threads and processes)."""

    def __init__(self, key):
        d = os.path.join(tempfile.gettempdir(), "digest_locks")
        os.makedirs(d, exist_ok=True)
        self.path = os.path.join(d, hashlib.sha1(key.encode()).hexdigest()[:16] + ".lock")

    def __enter__(self):
        self.fd = open(self.path, "w")
        fcntl.flock(self.fd, fcntl.LOCK_EX)

    def __exit__(self, *a):
        fcntl.flock(self.fd, fcntl.LOCK_UN)
        self.fd.close()


def run(name, cmd, repo, timeout, lock=None):
    """Run cmd in its own process group; on timeout SIGTERM the group (ido_bisect cleans its
    scratch mirror on SIGTERM), then SIGKILL."""
    env = dict(os.environ)
    env["PATH"] = ":".join([os.path.join(repo, ".venv/bin"), os.path.expanduser("~/local/bin"), env.get("PATH", "")])
    env["PYTHONWARNINGS"] = "ignore"
    ctx = flocked(lock) if lock else None
    if ctx:
        ctx.__enter__()
    try:
        t0 = time.time()
        p = subprocess.Popen(cmd, cwd=repo, stdout=subprocess.PIPE, stderr=subprocess.STDOUT, text=True,
                             errors="replace", env=env, start_new_session=True)
        try:
            out, _ = p.communicate(timeout=timeout)
            return Result(name, cmd, out, p.returncode, time.time() - t0)
        except subprocess.TimeoutExpired:
            try:
                os.killpg(p.pid, signal.SIGTERM)
            except ProcessLookupError:
                pass
            try:
                out, _ = p.communicate(timeout=15)
            except subprocess.TimeoutExpired:
                try:
                    os.killpg(p.pid, signal.SIGKILL)
                except ProcessLookupError:
                    pass
                out, _ = p.communicate()
            return Result(name, cmd, out or "", p.returncode, time.time() - t0, timed_out=True)
    finally:
        if ctx:
            ctx.__exit__()


# ---------------------------------------------------------------------------------- parsers
SIB_ROW = re.compile(r"^\s+(\d+\.\d+)\s+([\d.]+)\s+([\d.]+)\s+([\d.]+)\s+(\d+)\s+(func_\w+)\s+(\S+:\d+)\s+(.*?)\s*$")


def parse_siblings(text):
    rows, ranges = [], {}
    cur = None
    for line in text.splitlines():
        m = SIB_ROW.match(line)
        if m and cur is None:
            score, qs, sq, al, n, f, loc, rest = m.groups()
            tag = ""
            for t in ("STRONG", "possible"):
                if rest.endswith(t):
                    tag, rest = t, rest[: -len(t)].rstrip()
            rows.append(dict(score=float(score), qs=qs, sq=sq, al=al, n=n, func=f, loc=loc, run=rest, tag=tag))
            continue
        m = re.match(r"^\s+== (func_\w+)\s+\(score", line)
        if m:
            cur = m.group(1)
            continue
        m = re.match(r"^\s+--- C (\S+):(\d+-\d+) ---", line)
        if m and cur and cur not in ranges:
            ranges[cur] = m.group(1) + ":" + m.group(2)
    for r in rows:
        r["range"] = ranges.get(r["func"], r["loc"])
    return rows


def section_siblings(res):
    out = []
    if not res.ok:
        return ["- siblings: " + res.status()], None, None
    rows = parse_siblings(res.out)
    if not rows:
        return ["- no sibling rows (see siblings.txt)"], None, None
    good = [r for r in rows if r["score"] >= 0.30]
    for r in good:
        out.append("- **%s %.3f** `%s` %s (q-in-s %s, s-in-q %s, aligned %s, %s insns)" % (
            r["tag"] or ("STRONG" if r["score"] >= 0.45 else "possible"), r["score"], r["func"], r["range"],
            r["qs"], r["sq"], r["al"], r["n"]))
        if r["run"]:
            out.append("  - longest common run: " + clip(r["run"], 110))
    if not good:
        b = rows[0]
        out.append("- none >= 0.30 (best %s %.3f %s: shared idioms only)" % (b["func"], b["score"], b["range"]))
    else:
        out.append("- full C of each sibling: siblings.txt (`corpus.py show FUNC` for asm + C side by side)")
    return out, rows[0]["score"], rows[0]["func"]


def parse_near(text):
    lines = text.splitlines()
    head, regions, cur, mode = [], [], None, None
    for line in lines:
        if line.startswith("===="):
            continue
        m = re.match(r"^target region (\+0x[0-9a-f]+\.\.\+0x[0-9a-f]+)\s+\(insns ([\d-]+)\)\s*(\[.*\])?", line)
        if m:
            cur = dict(span=m.group(1), insns=m.group(2), kind=(m.group(3) or "").strip("[]"), ndiff=0,
                       draft=[], corpus=None, hit=None, hitc=[], nohit=False, stack="stack-offset-only" in line)
            regions.append(cur)
            mode = None
            continue
        if cur is None:
            if line.strip() and not line.startswith("near "):
                head.append(line.strip())
            continue
        s = line.strip()
        m = re.match(r"^\s{3}[risv|<>+-]\s+[0-9a-f]+\s+(.*?)\s*(?:\| draft: (.*))?$", line)
        if m:
            cur["ndiff"] += 1
            cur.setdefault("first", (re.sub(r"\s+", " ", m.group(1)), re.sub(r"\s+", " ", m.group(2) or "-")))
        if s.startswith("draft C that emitted it"):
            mode = "draft"
            continue
        if s.startswith("corpus:"):
            cur["corpus"] = s
            mode = None
            continue
        if s.startswith("(no matched function"):
            cur["nohit"] = True
            continue
        if s.startswith("-- func_"):
            if cur["hit"] is None:
                cur["hit"] = s[3:]
                mode = "hit"
            else:
                mode = None
            continue
        if mode == "hit" and s.startswith("--- C"):
            mode = None
            continue
        m = re.match(r"^\s+(>?)\s*(\d+)\| ?(.*)$", line)
        if m:
            if mode == "draft":
                cur["draft"].append((m.group(2), m.group(3).strip()))
            elif mode == "hit" and m.group(1) == ">" and len(cur["hitc"]) < 3:
                cur["hitc"].append((m.group(2), m.group(3).strip()))
        elif mode == "draft" and s and not re.match(r"^\d+\|", s):
            mode = None
    return head, regions


def section_near(res, max_regions=10):
    out = []
    if not res.ok:
        return ["- near: " + res.status()]
    head, regions = parse_near(res.out)
    for h in head[:3]:
        out.append("- " + clip(h))
    if not regions:
        out.append("- no differing regions")
        return out
    stack = [r for r in regions if r["stack"]]
    other = [r for r in regions if not r["stack"]]
    for r in other[:max_regions]:
        out.append("- **%s** (insns %s, %d diff lines)%s" % (r["span"], r["insns"], r["ndiff"],
                                                             " [%s]" % r["kind"] if r["kind"] else ""))
        for ln, c in r["draft"][:2]:
            out.append("  - draft L%s: `%s`" % (ln, clip(c, 110)))
        if len(r["draft"]) > 2:
            out.append("  - draft: ... %d more C lines" % (len(r["draft"]) - 2))
        if r["hit"]:
            m = re.search(r"corpus: (\d+) matched functions contain an? (\w+ \d+-insn) window", r["corpus"] or "")
            extra = " (%s fn(s) share a %s window)" % m.groups() if m else ""
            out.append("  - top hit: %s%s" % (clip(re.sub(r"\s+", " ", r["hit"]), 100), extra))
            for ln, c in r["hitc"][:2]:
                out.append("    - hit L%s: `%s`" % (ln, clip(c, 110)))
        elif r["nohit"]:
            out.append("  - no matched function shares a 2..5-insn window here")
    if len(other) > max_regions:
        out.append("- ... %d more regions in near.txt" % (len(other) - max_regions))
    if stack:
        out.append("- stack-offset-only regions (%d; slot order, see IDO_TRICKS 'Stack layout'):" % len(stack))
        for r in stack[:8]:
            t, d = r.get("first", ("?", "?"))
            out.append("  - %s `%s` (draft `%s`)%s" % (r["span"].split("..")[0], t, clip(d, 40),
                                                        "  draft L" + ",".join(ln for ln, _ in r["draft"][:2])
                                                        if r["draft"] else ""))
        if len(stack) > 8:
            out.append("  - ... %d more" % (len(stack) - 8))
    return out


def am_blocks(text):
    """Split accessmap output into (title, [BASE blocks]) per TARGET/DRAFT part."""
    parts, cur, blk = [], None, None
    for line in text.splitlines():
        if line.startswith("TARGET ") or line.startswith("DRAFT ") or line.startswith("TARGET vs DRAFT"):
            cur = dict(title=line.strip(), blocks=[], tail=[])
            parts.append(cur)
            blk = None
            continue
        if cur is None or line.startswith("===="):
            continue
        if line.startswith("BASE "):
            blk = [line]
            cur["blocks"].append(blk)
        elif blk is not None and line.strip():
            blk.append(line)
        elif line.strip():
            cur["tail"].append(line)
    return parts


AM_FLAG = re.compile(r"MIXED-WIDTH|MIXED-SIGN|OVERLAP|NO-FIELD|INSIDE|PAD-FIELD|SHIFTED|!!")


def section_accessmap(bare, draft):
    out, nflags = [], 0
    if not bare.ok:
        out.append("- accessmap: " + bare.status())
    else:
        parts = am_blocks(bare.out)
        tgt = parts[0] if parts else dict(title="", blocks=[])
        m = re.search(r"\((\d+ instructions.*?)\)", tgt["title"])
        if m:
            out.append("- target: " + m.group(1))
        out.append("- busiest bases (full table: accessmap.txt):")
        out.append("```")
        for blk in tgt["blocks"][:2]:
            rows = [l for l in blk[1:] if not l.strip().startswith("offset ")]
            out.append(clip(re.sub(r"\s{2,}", "  ", blk[0])))
            for l in rows[:8]:
                out.append(clip(l))
            if len(rows) > 8:
                out.append("  ... %d more rows" % (len(rows) - 8))
        out.append("```")
        flags, bname = [], "?"
        for l in bare.out.splitlines():
            if l.startswith("BASE "):
                m = re.match(r"^BASE (.+?)\s{2,}\[", l)
                bname = m.group(1) if m else l[5:].split()[0]
            elif AM_FLAG.search(l):
                flags.append("%s: %s" % (bname, l.strip()))
        nflags += len(flags)
        if flags:
            out.append("- flags (target):")
            for l in flags[:10]:
                out.append("  - `%s`" % clip(re.sub(r"\s{2,}", "  ", l.strip()), 130))
        else:
            out.append("- flags (target): none (no MIXED-WIDTH/MIXED-SIGN/OVERLAP)")
    if draft is None:
        return out, nflags
    if not draft.ok:
        out.append("- --draft: " + draft.status())
        return out, nflags
    parts = am_blocks(draft.out)
    diff = next((p for p in parts if p["title"].startswith("TARGET vs DRAFT")), None)
    lines = []
    if diff:
        lines = [l for blk in diff["blocks"] for l in blk] + diff["tail"]
        if not lines:
            # the comparison section is free text, not BASE blocks; take everything after its title
            txt = draft.out.split("TARGET vs DRAFT", 1)[1]
            lines = [l for l in txt.splitlines() if l.strip() and not l.startswith("====")]
    # store provenance rows are only interesting when some value moved
    same = next((i for i, l in enumerate(lines) if "every value is stored at the same offset" in l), None)
    prov = next((i for i, l in enumerate(lines) if "store provenance" in l), None)
    if same is not None and prov is not None and prov < same:
        lines = lines[:prov] + lines[same:]
    shifted = [l for l in draft.out.splitlines() if "SHIFTED" in l]
    nflags += len(shifted)
    if not lines:
        out.append("- target vs draft: no access differences")
    else:
        out.append("- target vs draft (%d lines; accessmap_draft.txt):" % len(lines))
        out.append("```")
        for l in lines[:18]:
            out.append(clip(l))
        if len(lines) > 18:
            out.append("... %d more" % (len(lines) - 18))
        out.append("```")
    for l in shifted:
        out.append("- **%s**" % clip(l.strip()))
    return out, nflags


def section_symcheck(res):
    out, n = [], 0
    if not res.ok:
        return ["- symcheck: " + res.status()], 0
    lines = res.out.splitlines()
    flags, cur = [], None
    in_flags = False
    for line in lines:
        if line.strip() == "flags:":
            in_flags = True
            continue
        if not in_flags:
            continue
        m = re.match(r"^\s+\[([HMLI])\]\s+(\w+)\s+(.*)$", line)
        if m:
            cur = dict(sev=m.group(1), kind=m.group(2), where=m.group(3).strip(), body=[])
            flags.append(cur)
        elif cur is not None and line.strip():
            cur["body"].append(line.strip())
    hm = [f for f in flags if f["sev"] in "HM"]
    low = len(flags) - len(hm)
    n = len(hm)
    if not hm:
        out.append("- no H/M flags" + (" (%d low-severity; symcheck.txt / -v)" % low if low else ""))
        return out, n
    for f in hm[:6]:
        out.append("- **[%s] %s** %s" % (f["sev"], f["kind"], clip(f["where"], 90)))
        body = [b for b in f["body"] if not b.startswith("draft ")]
        keep = body[:1] + [b for b in body[1:] if b.startswith("suggest") or b.startswith("[draft]")][:3]
        for b in keep:
            out.append("  - " + clip(b, 140))
    if len(hm) > 6:
        out.append("- ... %d more H/M flags in symcheck.txt" % (len(hm) - 6))
    if low:
        out.append("- (+%d low-severity flags)" % low)
    return out, n


BIS_ROW = re.compile(r"^(?P<name>\S+)\s+(?P<flags>\S+(?: \S+)*?)\s+(?P<score>\d+)\s+(?P<lines>\d+)\s+(?P<van>\d+)\s+"
                     r"(?P<app>\d+)\s+(?P<d>\d+)\s+(?P<hit>\d+)/(?P<tot>\d+)\s*(?P<stack>.*)$")
BIS_BASE = re.compile(r"^baseline: score (\d+), (\d+) diff lines, (\d+) insns \(target (\d+)\), frame (\S+) \(target (\S+)\)")


def parse_bisect(text):
    base, rows, slots, tail = None, [], [], []
    for line in text.splitlines():
        m = BIS_BASE.match(line)
        if m:
            base = dict(score=int(m.group(1)), lines=int(m.group(2)), insns=int(m.group(3)), tinsns=int(m.group(4)),
                        frame=m.group(5), tframe=m.group(6), text=line.strip())
            continue
        if re.match(r"^\s+(target|ours):\s", line):
            slots.append(line.rstrip())
            continue
        m = BIS_ROW.match(line)
        if m and m.group("name") not in ("switch", "baseline"):
            r = m.groupdict()
            for k in ("score", "lines", "van", "app", "d", "hit", "tot"):
                r[k] = int(r[k])
            r["stack"] = r["stack"].strip()
            r["raw"] = line.rstrip()
            rows.append(r)
            continue
        if line.startswith("change code elsewhere") or line.startswith("identical code"):
            tail.append(line.strip())
    return base, rows, slots, tail


def interpret_bisect(base, rows):
    if base is None:
        return "no baseline (see ido_bisect.txt)"
    if base["lines"] == 0:
        return "baseline already matches (0 diff lines)"
    hits = [r for r in rows if r["hit"] > 0]
    if not hits:
        return ("no switch touches the baseline diff lines -> cfe/ugen level (types, casts, signedness, operand "
                "order, literal types, struct layout): look at the C, not the optimizer")
    full = [r for r in hits if r["hit"] == r["tot"]]
    best = min(full or hits, key=lambda r: (r["d"], -r["hit"]))
    broad = best["d"] > 0.5 * max(1, base["insns"])
    s = "%sowner: %s (dOurs %d, hit %d/%d%s) -> %s" % (
        "only broad rewrites reach it; " if broad else "", best["name"], best["d"], best["hit"], best["tot"],
        ", stack " + best["stack"] if best["stack"] and best["stack"] != "(identical code)" else "",
        switch_class(best["name"]))
    narrow = [r for r in hits if r is not best and r["d"] <= 0.25 * base["insns"]]
    if narrow:
        s += "; also narrow: " + ", ".join("%s (dOurs %d, hit %d/%d)" % (r["name"], r["d"], r["hit"], r["tot"])
                                         for r in sorted(narrow, key=lambda r: r["d"])[:3])
    slotchg = [r["name"] for r in hits if r["stack"] and r["stack"] != "(identical code)"]
    if slotchg:
        s += "; temp/slot count changes under: " + ", ".join(slotchg[:5])
    return s


def section_bisect(full, cheap, has_draft):
    out = []
    if not has_draft:
        return ["- skipped: no draft to bisect"], None
    res = full if (full is not None and full.ok) else None
    if res is None:
        if full is not None:
            out.append("- default set: " + full.status())
        else:
            out.append("- default set not run (--fast); `ido_bisect.py SRC FUNC` when the diff is register/temp-shaped")
        if cheap is not None and cheap.ok:
            base, _, slots, _ = parse_bisect(cheap.out)
            if base:
                out.append("- `%s`" % base["text"])
                for s in slots:
                    out.append("  - `%s`" % s.strip())
                return out, base
        elif cheap is not None:
            out.append("- baseline build: " + cheap.status())
        return out, None
    base, rows, slots, tail = parse_bisect(res.out)
    if base:
        out.append("- `%s`" % base["text"])
        for s in slots:
            out.append("  - `%s`" % clip(s.strip()))
    hits = sorted([r for r in rows if r["hit"] > 0], key=lambda r: r["d"])
    if hits:
        out.append("```")
        out.append("switch                 flags                 score lines -van +app dOurs   hit  stack")
        for r in hits[:14]:
            out.append(clip(r["raw"]))
        if len(hits) > 14:
            out.append("... %d more" % (len(hits) - 14))
        out.append("```")
    else:
        out.append("- no switch has hit > 0")
    out.append("- **reading:** " + interpret_bisect(base, rows))
    for t in tail:
        out.append("- " + clip(t, 140))
    return out, base


# ---------------------------------------------------------------------------------- one function
def find_src(repo, func):
    round_prompts.REPO = repo
    for f, src in round_prompts.open_functions():
        if f == func:
            return src
    return None


def target_asm(repo, func):
    hits = glob.glob(os.path.join(repo, "asm/us/nonmatchings/**", func + ".s"), recursive=True)
    return hits[0] if hits else None


def count_insns(path):
    n = 0
    with open(path, encoding="utf-8", errors="replace") as f:
        for line in f:
            if re.match(r"^\s*/\* [0-9A-F]+ [0-9A-F]{8} [0-9A-F]{8} \*/", line):
                n += 1
    return n


def digest(func, src, out, repo, fast=False, score=None, timeout=30, bisect_timeout=90, bisect_jobs=6,
           bisect_sem=None, inner_jobs=3, quiet=False):
    """Run the oracles and write `out` (+ out.d/). Returns a summary dict for INDEX.md."""
    t_start = time.time()
    py = os.path.join(repo, ".venv/bin/python3")
    if not os.path.exists(py):
        py = sys.executable
    mn = os.path.join(repo, "matching_notes")
    round_prompts.REPO = repo
    draft = round_prompts.has_draft(src, func)
    asm = target_asm(repo, func)
    insns = count_insns(asm) if asm else None
    side = out + ".d"
    os.makedirs(side, exist_ok=True)
    lock_base = "%s|%s" % (os.path.realpath(repo), os.path.basename(src))

    def tool(name):
        p = os.path.join(mn, name)
        return p if os.path.exists(p) else None

    def job(name, script, args, tmo, lock=None):
        p = tool(script)
        if p is None:
            return Result(name, [script] + args, skipped="%s not in %s" % (script, mn))
        return run(name, [py, p] + args, repo, tmo, lock)

    def near_job():
        if draft:
            r = job("near", "corpus.py", ["near", func, "--draft", "--c"], timeout * 1.5, "near|" + lock_base)
            if r.ok:
                return [r]
            r2 = job("near_nodraft", "corpus.py", ["near", func, "--c"], timeout)
            return [r, r2]
        return [job("near", "corpus.py", ["near", func, "--c"], timeout)]

    def bisect_job():
        if not draft:
            return []
        res = []
        if not fast:
            if bisect_sem:
                bisect_sem.acquire()
            try:
                res.append(job("ido_bisect", "ido_bisect.py", [src, func, "-j", str(bisect_jobs)], bisect_timeout))
            finally:
                if bisect_sem:
                    bisect_sem.release()
            if res[-1].ok:
                return res
        res.append(job("ido_bisect_score", "ido_bisect.py", [src, func, "--switches", SCORE_SWITCH], timeout * 1.5))
        return res

    tasks = {
        "siblings": lambda: [job("siblings", "corpus.py", ["siblings", func, "--limit", "3", "--c"], timeout)],
        "near": near_job,
        "accessmap": lambda: [job("accessmap", "accessmap.py", [func, "--src", src], timeout)],
        "accessmap_draft": lambda: ([job("accessmap_draft", "accessmap.py", [func, "--src", src, "--draft"],
                                         timeout * 1.5, "am|" + os.path.realpath(repo) + "|" + src)]
                                    if draft else []),
        "symcheck": lambda: [job("symcheck", "symcheck.py", [func, "--src", src], timeout)],
        "bisect": bisect_job,
    }
    results = {}
    with concurrent.futures.ThreadPoolExecutor(inner_jobs + 1) as ex:
        futs = {ex.submit(fn): k for k, fn in tasks.items()}
        for fut in concurrent.futures.as_completed(futs):
            for r in fut.result():
                results[r.name] = r
                if not quiet:
                    print("  %s %-16s %s" % (func, r.name, r.status()), file=sys.stderr)

    # sidecar: full outputs + commands
    with open(os.path.join(side, "commands.txt"), "w") as f:
        for name, r in sorted(results.items()):
            with open(os.path.join(side, name + ".txt"), "w") as g:
                g.write(r.out)
            f.write("%-17s %s\n    $ %s\n" % (name, r.status(), " ".join(os.path.relpath(c, repo) if c.startswith(repo)
                                                                       else c for c in r.cmd)))

    get = results.get
    sib_lines, best, best_f = section_siblings(get("siblings"))
    near_res = get("near")
    near_lines = []
    if near_res is not None and not near_res.ok and get("near_nodraft") is not None:
        near_lines.append("- near --draft: %s; showing plain near (fd_last diff or rarest windows)" % near_res.status())
        near_res = get("near_nodraft")
    near_lines += section_near(near_res) if near_res else ["- not run"]
    am_lines, am_flags = section_accessmap(get("accessmap"), get("accessmap_draft"))
    sym_lines, sym_flags = section_symcheck(get("symcheck"))
    bis_lines, base = section_bisect(get("ido_bisect"), get("ido_bisect_score"), draft)

    if base:
        cur = "%d (%d diff lines; %d insns vs target %d; frame %s vs %s)" % (
            base["score"], base["lines"], base["insns"], base["tinsns"], base["frame"], base["tframe"])
    elif score is not None:
        cur = "%s (as given; not rebuilt)" % score
    else:
        cur = "n/a (no draft)"
        if draft:
            fail = get("ido_bisect_score") or get("ido_bisect")
            cur = "unknown" + (" - draft build " + fail.status() if fail is not None and not fail.ok else "")
    side_rel = os.path.basename(side)
    L = []
    L.append("# Digest: %s" % func)
    L.append("")
    L.append("- file: `%s`   size: %s insns   draft: %s" % (src, insns if insns is not None else "?",
                                                         "yes" if draft else "NO (write one from m2c first)"))
    L.append("- current score: **%s**" % cur)
    L.append("- generated %s by digest.py (%s, %.0f s); full oracle outputs + commands: `%s/`" % (
        datetime.datetime.now().strftime("%Y-%m-%d %H:%M"), "fast" if fast else "full", time.time() - t_start, side_rel))
    L.append("- snapshot of the draft as it is NOW: re-run `corpus.py near %s --draft --c` after every significant edit"
             % func)
    for title, body in (("Siblings (corpus.py siblings --limit 3)", sib_lines),
                        ("Near: diff regions, emitting draft C, matched idiom (corpus.py near%s --c)"
                         % (" --draft" if draft else ""), near_lines),
                        ("Symbol premises (symcheck.py)", sym_lines),
                        ("Memory accesses (accessmap.py%s)" % (" + --draft" if draft else ""), am_lines),
                        ("Optimizer pass owning each diff (ido_bisect.py)", bis_lines)):
        L.append("")
        L.append("## " + title)
        L.extend(body)
    if len(L) > MAX_LINES:
        L = L[:MAX_LINES - 1] + ["... (digest capped at %d lines; see %s/)" % (MAX_LINES, side_rel)]
    tmp = out + ".tmp"
    with open(tmp, "w") as f:
        f.write("\n".join(L) + "\n")
    os.replace(tmp, out)
    return dict(func=func, src=src, insns=insns, draft=draft, score=base["score"] if base else score,
                best=best, best_func=best_f, flags=am_flags + sym_flags, out=out,
                failed=[r.name for r in results.values() if not r.ok and not r.skipped])


# ---------------------------------------------------------------------------------- CLI
def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("func", nargs="?")
    ap.add_argument("--src", help="C file holding FUNC's GLOBAL_ASM (default: found by scanning src/)")
    ap.add_argument("--out", help="digest file (default build/digests/FUNC.md)")
    ap.add_argument("--fast", action="store_true", help="skip the ido_bisect default set (baseline score only)")
    ap.add_argument("--all-unmatched", action="store_true", help="one digest per GLOBAL_ASM function + INDEX.md")
    ap.add_argument("--out-dir", help="--all-unmatched output dir (default build/digests)")
    ap.add_argument("-j", type=int, default=4, help="--all-unmatched: functions in parallel (default 4)")
    ap.add_argument("--limit", type=int, help="--all-unmatched: only the first N functions")
    ap.add_argument("--funcs", help="--all-unmatched: comma-separated subset")
    ap.add_argument("--repo", default=os.path.dirname(HERE), help="checkout to analyse (default: this script's)")
    ap.add_argument("--score", help="score to report if the draft cannot be rebuilt")
    ap.add_argument("--timeout", type=float, default=30)
    ap.add_argument("--bisect-timeout", type=float, default=90)
    ap.add_argument("--bisect-jobs", type=int)
    a = ap.parse_args()
    repo = os.path.realpath(a.repo)

    if a.all_unmatched:
        if a.func or a.src or a.out:
            ap.error("--all-unmatched takes no FUNC/--src/--out")
        outdir = os.path.abspath(a.out_dir or os.path.join(repo, "build/digests"))
        os.makedirs(outdir, exist_ok=True)
        round_prompts.REPO = repo
        funcs = round_prompts.open_functions()
        if a.funcs:
            want = set(a.funcs.split(","))
            funcs = [x for x in funcs if x[0] in want]
        if a.limit:
            funcs = funcs[: a.limit]
        print("digest.py: %d functions -> %s (-j %d, %s)" % (len(funcs), outdir, a.j, "fast" if a.fast else "full"),
              file=sys.stderr)
        sem = threading.Semaphore(2)
        t0 = time.time()
        rows = []

        def one(fs):
            f, s = fs
            try:
                return digest(f, s, os.path.join(outdir, f + ".md"), repo, a.fast, None, a.timeout,
                              a.bisect_timeout, a.bisect_jobs or 3, sem, inner_jobs=2, quiet=True)
            except Exception as e:  # keep going
                return dict(func=f, src=s, error=repr(e))

        # warm the corpus siblings cache serially (it is rebuilt lazily when stale)
        if funcs:
            run("warm", [os.path.join(repo, ".venv/bin/python3"), os.path.join(repo, "matching_notes/corpus.py"),
                         "siblings", funcs[0][0], "--limit", "1"], repo, 120)
        with concurrent.futures.ThreadPoolExecutor(a.j) as ex:
            for r in ex.map(one, funcs):
                rows.append(r)
                print("  [%d/%d %.0fs] %s %s" % (len(rows), len(funcs), time.time() - t0, r["func"],
                                                 r.get("error") or ("failed: " + ",".join(r["failed"])
                                                                    if r["failed"] else "ok")), file=sys.stderr)
        idx = ["# Digest index (%s, %s, %d functions)" % (datetime.datetime.now().strftime("%Y-%m-%d %H:%M"),
                                                          "fast" if a.fast else "full", len(rows)), "",
               "| function | file | insns | draft | score | best sibling | flags | failed oracles |",
               "|---|---|---|---|---|---|---|---|"]
        for r in rows:
            if "error" in r:
                idx.append("| %s | %s | | | | | | ERROR %s |" % (r["func"], r["src"], r["error"]))
                continue
            idx.append("| [%s](%s.md) | %s | %s | %s | %s | %s | %d | %s |" % (
                r["func"], r["func"], r["src"], r["insns"], "y" if r["draft"] else "n",
                r["score"] if r["score"] is not None else "-",
                "%.3f %s" % (r["best"], r["best_func"]) if r["best"] is not None else "-", r["flags"],
                ",".join(r["failed"]) or "-"))
        with open(os.path.join(outdir, "INDEX.md"), "w") as f:
            f.write("\n".join(idx) + "\n")
        print("digest.py: wrote %s (%.0f s)" % (os.path.join(outdir, "INDEX.md"), time.time() - t0), file=sys.stderr)
        return 0

    if not a.func:
        ap.error("need FUNC (or --all-unmatched)")
    if not re.match(r"^func_[0-9A-Fa-f]{8}$", a.func):
        ap.error("FUNC must look like func_XXXXXXXX")
    src = a.src
    if src:
        if os.path.isabs(src):
            src = os.path.relpath(src, repo)
        if not os.path.isfile(os.path.join(repo, src)):
            print("digest.py: error: no such file %s in %s" % (src, repo), file=sys.stderr)
            return 2
    else:
        src = find_src(repo, a.func)
        if not src:
            print("digest.py: error: no GLOBAL_ASM for %s under %s/src (already matched?); pass --src"
                  % (a.func, repo), file=sys.stderr)
            return 2
    if not target_asm(repo, a.func):
        print("digest.py: error: no asm/us/nonmatchings/**/%s.s in %s" % (a.func, repo), file=sys.stderr)
        return 2
    out = os.path.abspath(a.out or os.path.join(repo, "build/digests", a.func + ".md"))
    os.makedirs(os.path.dirname(out), exist_ok=True)
    r = digest(a.func, src, out, repo, a.fast, a.score, a.timeout, a.bisect_timeout, a.bisect_jobs or 6)
    print("digest.py: wrote %s%s" % (out, ("  (failed oracles: %s)" % ", ".join(r["failed"])) if r["failed"] else ""),
          file=sys.stderr)
    return 0


if __name__ == "__main__":
    sys.exit(main())
