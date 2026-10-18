#!/usr/bin/env python3
"""port_agent.py - adapt a REFERENCE implementation (e.g. Team Hippodrome's tree) of a
matched function into OUR tree, via an LLM loop (RCD gateway, openweight models) with
fd.sh verification. Proposes nothing else; every splice is verified by a real build.

Usage (repo root or anywhere; --worktree is where builds run):
  port_agent.py --func func_8004A89C --src src/4A3E0.c \
      --their /tmp/opencode/hippo_bodies/func_8004A89C.c \
      --worktree .claude/worktrees/r10b-4a89c [--model gptoss-120b] [--rounds 12]

Flow per round: build a prompt (reference body + our draft body + last attempt's fd.sh
feedback), get a candidate body back, splice via try_candidate.py (worktree file restored),
capture score + differing lines, repeat. Tracks the best candidate in
<worktree>/scratch_port/<func>/. On fd 0 runs adopt_candidate.py (full make gate).
The API key is read from ~/.config/rcd-llm/api-key at runtime and never printed.
"""
import argparse
import json
import os
import re
import subprocess
import sys
import urllib.request

GATEWAY = "https://llm.rcd.clemson.edu/v1/chat/completions"
KEY_PATH = os.path.expanduser("~/.config/rcd-llm/api-key")

SYSTEM = """You are porting a byte-exact-matching C implementation of one Nintendo 64 function
between two decompilation trees of the SAME ROM. The REFERENCE body below is known to compile
to the exact target code in its tree. Your job: write the equivalent function for OUR tree.

RULES
- Map every identifier: the reference uses the other tree's symbol/type/macro names; our tree's
  names appear in OUR CURRENT DRAFT (same logic, placeholder names). Prefer our draft's names,
  types and spellings for everything you reference.
- Preserve the reference's STATEMENT ORDER, expression shapes, temp-vs-literal spelling and
  control flow EXACTLY - that structure is what makes it match. Only rename identifiers and
  adapt types. If our tree lacks a needed type, use our draft's closest equivalent.
- ASCII only. No #include, no comments unless marking a mapping you are unsure about.
- OUTPUT: the complete function definition only, starting at the return type, no code fences,
  no commentary. It must be valid C that compiles inside our file.
"""


def call_model(model, system, user, temperature, max_tokens, retries=3):
    key = open(KEY_PATH).read().strip()
    last = None
    for _ in range(retries):
        body = {
            "model": model,
            "messages": [{"role": "system", "content": system}, {"role": "user", "content": user}],
            "temperature": temperature,
            "max_tokens": max_tokens,
        }
        req = urllib.request.Request(GATEWAY, data=json.dumps(body).encode(), method="POST",
                                     headers={"Authorization": "Bearer " + key,
                                              "Content-Type": "application/json"})
        try:
            with urllib.request.urlopen(req, timeout=900) as r:
                return json.load(r)["choices"][0]["message"]["content"]
        except Exception as e:  # noqa: BLE001
            last = f"{type(e).__name__}: {e}"
    raise RuntimeError(f"gateway call failed after {retries} attempts: {last}")


def func_span(text, func):
    m = re.search(r"^[^\n;{}#]*\b%s\s*\([^;{]*\)\s*\{" % re.escape(func), text, re.M)
    if not m:
        sys.exit(f"{func} definition not found")
    i = m.end() - 1
    d = 0
    j = i
    while j < len(text):
        d += {"{": 1, "}": -1}.get(text[j], 0)
        if d == 0:
            break
        j += 1
    return m.start(), j + 1


def extract_code(resp):
    if "```" in resp:
        parts = resp.split("```")
        for k in range(1, len(parts), 2):
            c = parts[k].split("\n", 1)[1] if "\n" in parts[k] else parts[k]
            if "{" in c:
                return c
    return resp


def balanced(code):
    d = 0
    for ch in code:
        d += {"{": 1, "}": -1}.get(ch, 0)
        if d < 0:
            return False
    return d == 0


def run_fd(worktree, src, func, cand_path, max_lines):
    """Splice + build + diff one candidate in the worktree; returns (score, output)."""
    r = subprocess.run([sys.executable, os.path.join(worktree, "matching_notes", "try_candidate.py"),
                        src, func, cand_path], cwd=worktree, capture_output=True, text=True,
                       timeout=1800)
    out = r.stdout + r.stderr
    m = re.search(r"CURRENT \((\d+)\)", out)
    score = int(m.group(1)) if m else None
    return score, out


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--func", required=True)
    ap.add_argument("--src", required=True)
    ap.add_argument("--their", required=True)
    ap.add_argument("--worktree", required=True)
    ap.add_argument("--model", default="gptoss-120b")
    ap.add_argument("--rounds", type=int, default=12)
    ap.add_argument("--temperature", type=float, default=0.2)
    ap.add_argument("--max-tokens", type=int, default=16384)
    args = ap.parse_args()

    wt = os.path.abspath(args.worktree)
    their = open(args.their, errors="replace").read()
    our_path = os.path.join(wt, args.src)
    orig = open(our_path, errors="replace").read()
    s, e = func_span(orig, args.func)
    draft = orig[s:e]

    outdir = os.path.join(wt, "scratch_port", args.func)
    os.makedirs(outdir, exist_ok=True)
    print(f"[{args.func}] worktree={wt} rounds={args.rounds} model={args.model}", flush=True)

    best_score, best_file = None, None
    feedback = ""
    for rnd in range(1, args.rounds + 1):
        user = (f"OUR CURRENT DRAFT of {args.func} from {args.src} (our names/types; the "
                f"logic is close but NOT matching):\n\n```c\n{draft}\n```\n\n"
                f"REFERENCE IMPLEMENTATION (matched in the other tree; adapt this structure "
                f"to our names):\n\n```c\n{their}\n```\n")
        if feedback:
            user += (f"PREVIOUS ATTEMPT FEEDBACK (best candidate so far, round {rnd - 1}):\n{feedback}\n\n"
                     f"Produce the corrected full function. Keep what worked, fix what the "
                     f"feedback shows. Same output rules.\n")
        resp = call_model(args.model, SYSTEM, user, args.temperature, args.max_tokens)
        code = extract_code(resp).strip()
        if not balanced(code):
            # one continuation round for long bodies
            cont = call_model(args.model, SYSTEM,
                              user + "\nYour previous output was cut off. Continue EXACTLY where "
                                    "it stopped, no repetition, no fences:\n" + code[-2000:],
                              args.temperature, args.max_tokens)
            code = (code + "\n" + extract_code(cont)).strip()
        cand = os.path.join(outdir, f"attempt{rnd}.c")
        open(cand, "w").write(code)
        score, out = run_fd(wt, args.src, args.func, cand, 80)
        print(f"[{args.func}] round {rnd}: score={score}", flush=True)
        open(os.path.join(outdir, f"attempt{rnd}.out"), "w").write(out)
        if score is None:
            fb = [l for l in out.splitlines() if "rror" in l or "BUILD" in l][:6]
            feedback = "The candidate FAILED TO COMPILE:\n" + "\n".join(fb)
            continue
        if best_score is None or score < best_score:
            best_score, best_file = score, cand
            import shutil
            shutil.copy(cand, os.path.join(outdir, "best.c"))
            shutil.copy(os.path.join(outdir, f"attempt{rnd}.out"), os.path.join(outdir, "best.out"))
        # feedback always describes the BEST candidate, so the model never regresses away from it
        with open(os.path.join(outdir, "best.c")) as f:
            best_src = f.read()
        if score == 0:
            print(f"[{args.func}] fd 0 - adopting (full make gate)", flush=True)
            r = subprocess.run([sys.executable, os.path.join(wt, "matching_notes", "adopt_candidate.py"),
                               args.src, args.func, cand], cwd=wt, capture_output=True, text=True,
                              timeout=3600)
            tail = (r.stdout.strip().splitlines() or [""])[-1]
            print(f"[{args.func}] adopt: {tail}", flush=True)
            if tail.endswith(": OK"):
                print(f"[{args.func}] *** MATCHED AND ADOPTED (ROM OK) ***", flush=True)
                return 0
            feedback = "fd was 0 but the full ROM make did not print OK - check adopt_candidate output."
            continue
        bf = open(os.path.join(outdir, "best.c" if best_file else "attempt1.c")).read()
        blines = [l for l in open(os.path.join(outdir, "best.out")).read().splitlines()
                  if re.search(r"\s(r|i|s|<|>|\|)\s", l) or "CURRENT" in l] if os.path.exists(os.path.join(outdir, "best.out")) else []
        feedback = (f"fd score of the best candidate = {best_score}. Its source:\n```c\n{bf}\n```\n"
                    f"Its differing lines (r=register, i=immediate, s=stack; i on a jal/branch "
                    f"often means a symbol-name era difference - try the other spelling):\n"
                    + "\n".join(blines[:60]))
    print(f"[{args.func}] done. best fd = {best_score} ({best_file})", flush=True)
    return 1 if best_score else 0


if __name__ == "__main__":
    sys.exit(main())
