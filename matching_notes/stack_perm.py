#!/usr/bin/env python3
"""Frame-layout fuzzer: hill-climb a candidate's local declarations toward the target frame.

The permuter mutates statements, never declarations, but per IDO_TRICKS.md the frame is
laid out top-down in declaration order (named locals get home slots even when unused,
spill temps sit below them). So stack-dominant diffs (many `s` markers, slots shifted by
a constant) are best fixed by declaration surgery: delete an unused local, insert a
padding local, or reorder two adjacent ones.

usage: stack_perm.py src/path/file.c func_XXXXXXXX path/to/candidate/source.c
       [--evals N] [--out DIR] [--inject]

- Each variant is scored by splicing it into the repo via try_candidate.py (one object
  build + diff.py, ~10-20 s); the repo file is restored after every eval.
- Greedy hill-climb over: delete(unused first) > insert s32 > insert s16/u8 > adjacent swap.
- --out DIR writes the winner as DIR/<func>.c (FOCUS_DIR layout for the farm).
- --inject also drops the winner into $SAVE_DIR/<func>/output-<score>-sf1/ so every
  running farm copy re-seeds from it at its next mid-run re-seed.

Stack scores are only a proxy: judge the final source with fd.sh / a full make.
"""
import os
import re
import subprocess
import sys
import tempfile

HERE = os.path.dirname(os.path.abspath(__file__))
REPO = os.path.dirname(HERE)

src, func, cand = sys.argv[1:4]
EVALS = 40
OUT = None
INJECT = False
argv = sys.argv[4:]
for i, a in enumerate(argv):
    if a == "--evals":
        EVALS = int(argv[i + 1])
    elif a == "--out":
        OUT = argv[i + 1]
    elif a == "--inject":
        INJECT = True
SAVE_DIR = os.environ.get("SAVE_DIR", f"/scratch/{os.environ.get('USER')}/permuter_best")


def func_span(text, func):
    m = re.search(r"^[^\n;{}#]*\b%s\s*\([^;{]*\)\s*\{" % re.escape(func), text, re.M)
    if not m:
        sys.exit(f"{func} definition not found")
    depth, i = 0, m.end() - 1
    while i < len(text):
        depth += {"{": 1, "}": -1}.get(text[i], 0)
        if depth == 0:
            return m.start(), i + 1
        i += 1
    sys.exit(f"unbalanced braces in {func}")


base_text = open(cand).read()
fa, fb = func_span(base_text, func)
head, body, tail = base_text[:fa], base_text[fa:fb], base_text[fb:]

DECL = re.compile(r"^\s{2,}(?:const\s+)?(?:[A-Za-z_]\w*[ \t*]+)+?\**\s*([A-Za-z_]\w*)\s*(\[[^\]]*\])?\s*(=[^;]*)?;\s*$")


def decls(body):
    """(start, end, [(start, end, full_line, name)]) of the top declaration block."""
    ob = body.index("{") + 1
    out, i = [], ob
    while i < len(body):
        j = body.index("\n", i) + 1
        line = body[i:j]
        if line.strip() == "" or line.lstrip().startswith("//"):
            i = j
            continue
        m = DECL.match(line)
        if not m or re.match(r"^\s*(for|while|if|return|switch)", line):
            break
        out.append((i, j, line, m.group(1)))
        i = j
    return ob, i, out


def score(text, tag):
    """Splice variant into the repo and return (CURRENT score) or None on failure."""
    with tempfile.NamedTemporaryFile("w", suffix=".c", delete=False) as f:
        f.write(text)
        tmp = f.name
    try:
        r = subprocess.run(
            [os.path.join(REPO, ".venv", "bin", "python3"), "-W", "ignore",
             os.path.join(HERE, "try_candidate.py"), src, func, tmp],
            capture_output=True, text=True, timeout=600, cwd=REPO)
        m = re.search(r"CURRENT \((\d+)\)", r.stdout)
        return int(m.group(1)) if m else None
    except subprocess.TimeoutExpired:
        return None
    finally:
        os.unlink(tmp)


def variants(body):
    """Yield (label, new_body) for every declaration-surgery move."""
    ob, de, ds = decls(body)
    names_used = {d[3]: body.count(d[3]) - 1 for d in ds}  # occurrences minus the decl itself
    for k, (i, j, line, name) in enumerate(ds):
        yield (f"del {name} (x{names_used[name]})", body[:i] + body[j:])
    for pos in range(len(ds) + 1):
        at = ds[pos][0] if pos < len(ds) else de
        for ty in ("s32", "s16", "u8"):
            pad = f"    {ty} __sp{pos};\n"
            yield (f"ins {ty} @{pos}", body[:at] + pad + body[at:])
    for k in range(len(ds) - 1):
        i1, j1 = ds[k][0], ds[k][1]
        i2, j2 = ds[k + 1][0], ds[k + 1][1]
        yield (f"swap {ds[k][3]}~{ds[k + 1][3]}",
               body[:i1] + body[i2:j2] + body[j1:i2] + body[i1:j1] + body[j2:])


best = score(base_text, "base")
print(f"baseline: {best}  (decls: {len(decls(body)[2])})", flush=True)
if best is None:
    sys.exit("baseline failed to score")
spent, it = 1, 0
cur, cur_body = best, body
history = [best]
while spent < EVALS:
    improved = False
    for label, nb in variants(cur_body):
        if spent >= EVALS:
            break
        spent += 1
        s = score(head + nb + tail, label)
        mark = "" if s is None else f" ({s})"
        print(f"[{spent}/{EVALS}] {label}{mark}", flush=True)
        if s is not None and s < cur:
            cur, cur_body = s, nb
            history.append((s, label))
            print(f"  -> new best {s} via {label}", flush=True)
            improved = True
            break  # greedy: restart the move list from the improved state
    if not improved:
        break
print(f"\nhill-climb: {best} -> {cur}  ({' -> '.join(str(h[0]) for h in history[1:]) or 'no improvement'})")

winner = head + cur_body + tail
with open(f"/tmp/{func}_stackperm.c", "w") as f:
    f.write(winner)
if OUT:
    os.makedirs(OUT, exist_ok=True)
    with open(os.path.join(OUT, f"{func}.c"), "w") as f:
        f.write(winner)
    print(f"wrote {OUT}/{func}.c")
if INJECT and cur < best:
    d = os.path.join(SAVE_DIR, func, f"output-{cur}-sf1")
    os.makedirs(d, exist_ok=True)
    with open(os.path.join(d, "source.c"), "w") as f:
        f.write(winner)
    with open(os.path.join(d, "score.txt"), "w") as f:
        f.write(f"{cur}\n")
    print(f"injected {d}; farm copies re-seed from it at their next mid-run re-seed")
