#!/usr/bin/env python3
"""Helpers for matching_notes/round.sh (prompt generation, NOTES lookup, open-function list).

  round_prompts.py parse <assignments-file>
      Validate an assignments file and print one line per agent: "agent-k<TAB>spec spec ...".
      Line format: `agent-k: func_A[@score]:src/a.c func_B[@score]:src/b.c ...` (# comments ok).
  round_prompts.py prompt --agent agent-k --worktree W --main M --base B SPEC...
      Print the filled PROMPT.md for one agent (template: matching_notes/round_prompt_template.md).
  round_prompts.py notes func_X
      Print the NOTES.md blocks (bullet / ### section / paragraph) that mention func_X.
  round_prompts.py open [--plain]
      Print the open functions (one per GLOBAL_ASM line in src/) as `func:src/file.c`,
      annotated with tier (from PLAN.md sections 0-3) and whether a NON_MATCHING draft exists.
"""
import argparse
import os
import re
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
# src/ is scanned in ROUND_MAIN (set by round.sh) or this script's checkout; docs come from here.
REPO = os.environ.get("ROUND_MAIN") or os.path.dirname(HERE)
NOTES = os.path.join(HERE, "NOTES.md")
PLAN = os.path.join(HERE, "PLAN.md")
TEMPLATE = os.path.join(HERE, "round_prompt_template.md")
FUNC_RE = re.compile(r"func_[0-9A-Fa-f]{8}")
SPEC_RE = re.compile(r"^(func_[0-9A-Fa-f]{8})(?:@([0-9]+))?:(\S+\.c)$")
AGENT_RE = re.compile(r"^(agent-[A-Za-z0-9_]+):\s*(.*)$")
GLOBAL_ASM_RE = re.compile(r'^#pragma GLOBAL_ASM\("asm/us/nonmatchings/\S+/(func_[0-9A-Fa-f]{8})\.s"\)')
NOTES_MAX_LINES = 80


def die(msg):
    print(f"round_prompts.py: error: {msg}", file=sys.stderr)
    sys.exit(2)


def read_lines(path):
    with open(path, encoding="utf-8") as f:
        return f.read().split("\n")


def parse_spec(spec):
    m = SPEC_RE.match(spec)
    if not m:
        die(f"bad function spec {spec!r}; expected func_XXXXXXXX[@score]:src/path.c")
    func, score, src = m.groups()
    return func, score, src


def open_functions():
    """[(func, src)] for every GLOBAL_ASM line under src/, in file order."""
    out = []
    for root, dirs, files in os.walk(os.path.join(REPO, "src")):
        dirs.sort()
        for name in sorted(files):
            if not name.endswith(".c"):
                continue
            path = os.path.join(root, name)
            rel = os.path.relpath(path, REPO)
            with open(path, encoding="utf-8", errors="replace") as f:
                for line in f:
                    m = GLOBAL_ASM_RE.match(line)
                    if m:
                        out.append((m.group(1), rel))
    return out


def has_draft(src, func):
    """True if func's GLOBAL_ASM sits in the #else of a NON_MATCHING block with a definition."""
    lines = read_lines(os.path.join(REPO, src))
    for i, line in enumerate(lines):
        m = GLOBAL_ASM_RE.match(line)
        if not m or m.group(1) != func:
            continue
        # walk back to the #else, then to the #ifdef NON_MATCHING / #if 1
        j = i - 1
        while j >= 0 and not lines[j].startswith("#"):
            j -= 1
        if j < 0 or not lines[j].startswith("#else"):
            return False
        k = j - 1
        while k >= 0 and not re.match(r"#if(def NON_MATCHING|\s+1)\b", lines[k]):
            if lines[k].startswith("#endif"):
                return False
            k -= 1
        return k >= 0 and any(func + "(" in l for l in lines[k:j])
    return False


# ---------------------------------------------------------------- NOTES lookup
def notes_blocks(func):
    """Distinct NOTES.md blocks mentioning func: a ### section (if the heading names it),
    otherwise the enclosing top-level `- ` bullet, otherwise the blank-delimited paragraph."""
    lines = read_lines(NOTES)
    word = re.compile(r"\b" + re.escape(func) + r"\b")
    blocks, seen = [], set()
    for i, line in enumerate(lines):
        if not word.search(line):
            continue
        if line.startswith("### "):
            start, end = i, i + 1
            while end < len(lines) and not lines[end].startswith("#"):
                end += 1
        else:
            start = i
            while start > 0 and not lines[start].startswith("- ") and lines[start - 1].strip() \
                    and not lines[start - 1].startswith("#"):
                start -= 1
            end = i + 1
            while end < len(lines) and lines[end].strip() and not lines[end].startswith("- ") \
                    and not lines[end].startswith("#"):
                end += 1
        # skip blocks fully inside an already-taken block
        if any(s <= start and end <= e for s, e in seen):
            continue
        seen.add((start, end))
        blocks.append((start, end))
    out = []
    for start, end in sorted(blocks):
        # heading context: nearest heading above the block
        h = start
        while h >= 0 and not lines[h].startswith("#"):
            h -= 1
        ctx = lines[h].strip() if h >= 0 and h != start else ""
        out.append((start + 1, ctx, lines[start:end]))
    return out


def notes_text(func):
    blocks = notes_blocks(func)
    if not blocks:
        return "(no NOTES.md entry mentions this function)"
    parts, total = [], 0
    for lineno, ctx, body in blocks:
        hdr = f"[NOTES.md line {lineno}" + (f", under `{ctx}`" if ctx else "") + "]"
        if total + len(body) > NOTES_MAX_LINES:
            body = body[: max(0, NOTES_MAX_LINES - total)] + [f"... (truncated; see NOTES.md line {lineno})"]
        parts.append(hdr + "\n" + "\n".join(body).rstrip())
        total += len(body)
        if total >= NOTES_MAX_LINES:
            break
    return "\n\n".join(parts)


# ---------------------------------------------------------------- PLAN extraction
def matcher_rules():
    lines = read_lines(PLAN)
    try:
        s = next(i for i, l in enumerate(lines) if l.startswith("### Matcher rules"))
    except StopIteration:
        die("PLAN.md has no '### Matcher rules' section")
    e = s + 1
    while e < len(lines) and not lines[e].startswith("#"):
        e += 1
    return "\n".join(lines[s + 1:e]).strip()


def tiers():
    """func -> tier label, from PLAN.md sections up to '## 4.' (cheap regex scan)."""
    lines = read_lines(PLAN)
    out = {}
    tier = None
    for line in lines:
        if line.startswith("## 4"):
            break
        m = re.search(r"\*\*Tier (\w+)", line)
        if m:
            tier = "tier " + m.group(1)
        elif line.startswith("### Phase B"):
            tier = "tier 4"
        elif line.startswith("### Phase C"):
            tier = "tier 3"
        elif line.startswith("#"):
            tier = None
        if tier:
            for f in FUNC_RE.findall(line):
                out.setdefault(f, tier)
    # fallback: NOTES.md per-function section headings
    heading_tier = [("register allocation", "tier 1"), ("stack layout", "tier 2"),
                    ("gDisplayListHead", "tier 2b"), ("data/bss", "tier 3"), ("Large", "tier 4")]
    tier = None
    for line in read_lines(NOTES):
        if line.startswith("#"):
            tier = next((t for k, t in heading_tier if k in line), None)
        if tier:
            for f in FUNC_RE.findall(line):
                out.setdefault(f, tier)
    return out


# ---------------------------------------------------------------- commands
def cmd_parse(args):
    agents = {}
    open_set = set(open_functions())
    for n, raw in enumerate(read_lines(args.file), 1):
        line = raw.split("#", 1)[0].strip()
        if not line:
            continue
        m = AGENT_RE.match(line)
        if not m:
            die(f"{args.file}:{n}: expected 'agent-k: func_A[@score]:src/a.c ...', got {raw!r}")
        agent, rest = m.groups()
        specs = rest.split()
        if not specs:
            die(f"{args.file}:{n}: {agent} has no functions")
        if agent in agents:
            die(f"{args.file}:{n}: {agent} listed twice")
        for spec in specs:
            func, _, src = parse_spec(spec)
            if not os.path.isfile(os.path.join(REPO, src)):
                die(f"{args.file}:{n}: {src} does not exist")
            if (func, src) not in open_set:
                print(f"round_prompts.py: warning: {func} has no GLOBAL_ASM in {src} (already matched?)",
                      file=sys.stderr)
        agents[agent] = specs
    if not agents:
        die(f"{args.file}: no agent lines")
    for agent, specs in agents.items():
        print(agent + "\t" + " ".join(specs))


def cmd_prompt(args):
    with open(TEMPLATE, encoding="utf-8") as f:
        tpl = f.read()
    parsed = [parse_spec(s) for s in args.specs]
    func_list = ", ".join(f"{f} ({src})" for f, _, src in parsed)
    oracles = "\n".join(
        f"  .venv/bin/python3 matching_notes/corpus.py near {f} --draft --c\n"
        f"  .venv/bin/python3 matching_notes/ido_bisect.py {src} {f}"
        for f, _, src in parsed)
    sections = []
    for i, (f, score, src) in enumerate(parsed, 1):
        draft = "yes (`#ifdef NON_MATCHING` block above the GLOBAL_ASM)" if has_draft(src, f) else \
            "NO draft yet - write one (start from m2c output)"
        sections.append(
            f"### {i}. {f} ({src})\n"
            f"- Current score (fd.sh): {score if score is not None else 'unknown - run fd.sh first'}\n"
            f"- Draft in tree: {draft}\n"
            f"- Score check: `matching_notes/fd.sh {src} {f}` (after enabling the draft with a bare `#if 1`)\n"
            f"- NOTES.md entries (read the draft's // comment too):\n\n"
            f"{notes_text(f)}\n")
    subs = {
        "WORKTREE": args.worktree, "MAIN": args.main, "BASE": args.base,
        "SCRATCH": os.path.join(args.worktree, "scratch_agent"), "FUNC_LIST": func_list,
        "ORACLES": oracles, "MATCHER_RULES": matcher_rules(), "FUNCTIONS": "\n".join(sections),
        "AGENT": args.agent,
    }
    out = re.sub(r"\{\{(\w+)\}\}", lambda m: subs.get(m.group(1), m.group(0)), tpl)
    left = re.findall(r"\{\{\w+\}\}", out)
    if left:
        die(f"unfilled template placeholders: {sorted(set(left))}")
    sys.stdout.write(out)


def cmd_notes(args):
    print(notes_text(args.func))


def cmd_open(args):
    t = tiers()
    funcs = open_functions()
    for f, src in funcs:
        if args.plain:
            print(f"{f}:{src}")
        else:
            notes = [t.get(f, "tier ?")]
            if not has_draft(src, f):
                notes.append("no draft")
            print(f"  {f}:{src}  # " + ", ".join(notes))
    if not args.plain:
        print(f"# {len(funcs)} open functions", file=sys.stderr)


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = ap.add_subparsers(dest="cmd", required=True)
    p = sub.add_parser("parse"); p.add_argument("file"); p.set_defaults(fn=cmd_parse)
    p = sub.add_parser("prompt")
    for a in ("--agent", "--worktree", "--main", "--base"):
        p.add_argument(a, required=True)
    p.add_argument("specs", nargs="+"); p.set_defaults(fn=cmd_prompt)
    p = sub.add_parser("notes"); p.add_argument("func"); p.set_defaults(fn=cmd_notes)
    p = sub.add_parser("open"); p.add_argument("--plain", action="store_true"); p.set_defaults(fn=cmd_open)
    args = ap.parse_args()
    args.fn(args)


if __name__ == "__main__":
    main()
