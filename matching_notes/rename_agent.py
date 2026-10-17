#!/usr/bin/env python3
"""Rename-research agent: read a source file, propose ledger rows via an LLM (gateway).

Usage: rename_agent.py --file src/x.c --batch pX [--model gptoss-120b] [--max 15] [--out DIR]

Writes <DIR>/<batch>_<basename>.tsv with proposal rows (old, new, batch, also, justification,
status=pending) plus a .raw sibling with the full model response. PROPOSAL ONLY - nothing is
applied; the integrator runs rename.py preflight + apply + gate. The API key is read from
~/.config/rcd-llm/api-key at runtime and never printed or written anywhere.
"""
import argparse
import json
import os
import re
import sys
import urllib.request

GATEWAY = "https://llm.rcd.clemson.edu/v1/chat/completions"
KEY_PATH = os.path.expanduser("~/.config/rcd-llm/api-key")

SYSTEM = """You are helping decompile Pokemon Stadium (N64). You PROPOSE symbol renames; another
process verifies and applies them. You cannot rename anything yourself.

TASK: read the C file and propose renames for placeholder symbols (func_XXXXXXXX, D_XXXXXXXX) into
human-readable names, following the project's established conventions.

NAMING CONVENTIONS (from the project ledger - match this style):
  func_8002D7C0  -> GetMessageString     (buf, bufSize, bank, stringId: bank[str+1] offsets, decompresses)
  func_80005F5C  -> GfxAlloc             (allocates from the top of the active display-list buffer)
  D_80072EE0     -> gItemNames          (84-entry item-name table, char*)
  func_80007778  -> Stage_Advance        (submits the stage DL, runs the frame machinery)
  func_81208D7C  -> GbAudio_Reset        (zeroes GB APU regs, clears channel states)
  unk_func_81208D7C -> GbAudioChannel    (typedef, via the also column)
Rules:
- Functions: Verb or Domain_Verb in CamelCase (GetItemName, Stage_Create, MeasureTextWidth,
  PlaySoundEffect). Global data: g + Noun (gItemNames, gCurrentStage, gMoveStrings).
- Prefix globals with g. Domain prefixes: Text_, Gfx_, Stage_, GbAudio_, Game_, Matrix_, List_,
  Fragment_, Sched_, Gbs, MenuInput_, Sprite... reuse an existing domain prefix when the code
  clearly belongs to that subsystem.
- The justification column MUST cite concrete evidence visible in the code: call sites, string
  literals, magic constants, struct fields, table shapes, libultra calls. If the evidence is weak
  or you are guessing, SKIP the symbol entirely. A skipped symbol costs nothing; a wrong name
  costs a revert. Aim for 10-15 solid proposals, not 30 shaky ones.
- NEVER propose renames for: symbols already human-named (anything not matching func_XXXXXXXX /
  D_XXXXXXXX / unk_*), jtbl_*, the five open functions (func_8004A89C, func_80034348,
  func_8437B0CC, func_88304850, func_88805AEC) or anything inside their NON_MATCHING drafts.
- Prefer names a Pokemon Stadium modder would recognize (GB APU, HP, moves, items, save data,
  rental, gym leader, stadium modes).

OUTPUT FORMAT: exactly one TSV line per proposal, SIX tab-separated fields, no header, no code
fences, no commentary. Field 3 is the literal batch tag shown below, field 4 is empty unless a
typedef rename goes with it (unk_D_800FD008:MeshVerts style), field 6 is the literal word pending.
Example of ONE line (with real tabs):
func_80020B88<TAB>DrawHealthBar<TAB>BATCH<TAB><TAB>draws left cap, middle fill and right cap from the health bar textures D_1003CF0/D_1003C30/D_1003B70<TAB>pending
The justification must be one sentence with the evidence, ASCII characters only.
"""


def call_model(model, system, user, temperature=0.2, max_tokens=4096):
    key = open(KEY_PATH).read().strip()
    body = json.dumps({
        "model": model,
        "messages": [{"role": "system", "content": system},
                     {"role": "user", "content": user}],
        "temperature": temperature,
        "max_tokens": max_tokens,
    }).encode()
    req = urllib.request.Request(GATEWAY, data=body, method="POST",
                                 headers={"Authorization": "Bearer " + key,
                                          "Content-Type": "application/json"})
    with urllib.request.urlopen(req, timeout=300) as r:
        data = json.load(r)
    return data["choices"][0]["message"]["content"]


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--file", required=True)
    ap.add_argument("--batch", required=True)
    ap.add_argument("--model", default="gptoss-120b")
    ap.add_argument("--max", type=int, default=15)
    ap.add_argument("--out", required=True)
    args = ap.parse_args()

    src = open(args.file, errors="replace").read()
    lines = src.splitlines()
    # skip files with an open NON_MATCHING draft inside: tell the model to leave those functions alone
    protected_hint = ""
    if "NON_MATCHING" in src:
        protected_hint = ("\nNOTE: this file contains #ifdef NON_MATCHING draft(s). Do NOT propose "
                          "renames for any symbol referenced inside those draft blocks.\n")
    user = (f"Source file: {args.file} ({len(lines)} lines)\n"
            f"Propose up to {args.max} renames.\n{protected_hint}\n```c\n{src}\n```")

    print(f"[{args.batch}] {args.file}: {len(lines)} lines -> {args.model}", flush=True)
    out = call_model(args.model, SYSTEM.replace("BATCH", args.batch), user)
    os.makedirs(args.out, exist_ok=True)
    base = os.path.join(args.out, f"{args.batch}_{os.path.basename(args.file)}")
    open(base + ".raw", "w").write(out)

    rows = []
    for line in out.splitlines():
        line = line.strip()
        if not line or line.startswith(("#", "old\t", "```")):
            continue
        parts = [p.strip() for p in line.split("\t")]
        if len(parts) < 3:
            continue
        old, new = parts[0], parts[1]
        if not re.fullmatch(r"(func_|D_|unk_)[A-Za-z0-9_]+", old):
            continue
        if not re.fullmatch(r"[A-Za-z_][A-Za-z0-9_]*", new):
            continue
        batch = parts[2] if len(parts) >= 6 and parts[2] == args.batch else args.batch
        if len(parts) >= 6:
            also, just = parts[3], parts[4]
        elif len(parts) == 5:
            also, just = parts[2] if parts[2] != args.batch else "", parts[3]
        else:
            also, just = "", parts[2]
        just = just.encode("ascii", "replace").decode().strip()
        also = also.encode("ascii", "replace").decode().strip()
        rows.append((old, new, batch, also, just))
    with open(base + ".tsv", "w") as f:
        for old, new, batch, also, just in rows:
            f.write(f"{old}\t{new}\t{batch}\t{also}\t{just}\tpending\n")
    print(f"[{args.batch}] {len(rows)} proposal rows -> {base}.tsv", flush=True)


if __name__ == "__main__":
    main()
