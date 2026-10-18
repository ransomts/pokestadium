#!/usr/bin/env python3
"""Tier C field-rename agent: propose struct field renames via the RCD gateway.

Usage: rename_field_agent.py --header src/x.h --batch cN [--model gpt-5.6-sol] [--out DIR]

Reads matching_notes/rename_fields_inventory.tsv for the safe (globally-unique) field
names of each typedef in the header, assembles a prompt with the typedef declarations
plus usage excerpts, and writes <DIR>/<batch>_<header>.tsv of ledger field rows:
  Typedef.unk_XX<TAB>newField<TAB>BATCH<TAB><TAB>justification<TAB>pending
Field rows rewrite member accesses globally, so ONLY inventory-listed fields may be
proposed - the integrator enforces this again at fixup time. Proposals only; nothing
is applied without rename.py preflight + gate.
"""
import argparse
import json
import os
import re
import sys
import urllib.request

GATEWAY = "https://llm.rcd.clemson.edu/v1/chat/completions"
KEY_PATH = os.path.expanduser("~/.config/rcd-llm/api-key")
HERE = os.path.dirname(os.path.abspath(__file__))
REPO = os.path.dirname(HERE)
INVENTORY = os.path.join(HERE, "rename_fields_inventory.tsv")

SYSTEM = """You are helping decompile Pokemon Stadium (N64). You PROPOSE struct field renames;
another process verifies and applies them. You cannot rename anything yourself.

TASK: for each typedef listed below, propose human-readable names for its `unk_XX`
placeholder fields, based on how the fields are USED (values stored/loaded, adjacent
fields, call arguments, struct name) and the declaration context given.

RULES:
- Field names: lowerCamelCase nouns matching the project's existing style
  (baseHP, monId, catchRate, baseExp, type1, growthRate). No prefixes, no hungarian.
- ONLY propose fields from the SAFE LIST. Other fields of the same struct are out of
  scope (their names are shared with other structs and cannot be renamed safely).
- The justification MUST cite concrete evidence from the usage excerpts or declaration
  (what value is stored, which function consumes it, what the neighbours are).
  If the evidence is weak, SKIP the field. A skipped field costs nothing; a wrong name
  costs a revert. Quality over quantity.
- Do NOT propose renaming the typedef itself, and do NOT touch arrays' element counts.

OUTPUT FORMAT: exactly one TSV line per proposal, SIX tab-separated fields, no header,
no code fences, no commentary. Field 1 is `TypedefName.unk_XX`, field 2 the new field
name, field 3 is the literal batch tag, field 4 empty, field 6 the literal word pending.
Example of ONE line (with real tabs):
GbAudioChannelState.unk_0194<TAB>noiseChannelActive<TAB>BATCH<TAB><TAB>set to 1 when the noise channel is enabled in GbAudio_StepNoiseChannel and cleared on reset<TAB>pending
Justifications must be one sentence, ASCII only."""


def call_model(model, system, user, temperature=None, max_tokens=8192, retries=2):
    key = open(KEY_PATH).read().strip()
    body = {
        "model": model,
        "messages": [{"role": "system", "content": system},
                     {"role": "user", "content": user}],
        "max_completion_tokens": max_tokens,
    }
    if temperature is not None:
        body["temperature"] = temperature
    req = urllib.request.Request(GATEWAY, data=json.dumps(body).encode(), method="POST",
                                 headers={"Authorization": "Bearer " + key,
                                          "Content-Type": "application/json"})
    last = None
    for _ in range(retries):
        try:
            with urllib.request.urlopen(req, timeout=600) as r:
                data = json.load(r)
            content = data["choices"][0]["message"]["content"]
            if content is None:
                last = f"no content (finish={data['choices'][0].get('finish_reason')})"
                continue
            return content
        except Exception as e:  # noqa: BLE001
            last = f"{type(e).__name__}: {e}"
    raise RuntimeError(f"gateway call failed after {retries} attempts: {last}")


def load_inventory(header):
    per_typedef = {}
    for line in open(INVENTORY):
        if line.startswith("#"):
            continue
        parts = line.rstrip("\n").split("\t")
        if len(parts) < 5:
            continue
        tname, hdr, field, decl, users = parts[:5]
        if os.path.relpath(os.path.join(REPO, hdr)) != os.path.relpath(header):
            continue
        d = per_typedef.setdefault(tname, {"fields": [], "users": []})
        d["fields"].append((field, decl))
        if users:
            d["users"].extend(u for u in users.split(",") if u)
    for d in per_typedef.values():
        d["users"] = sorted(set(d["users"]))
    return per_typedef


def struct_decl(header, tname):
    text = open(header, errors="replace").read()
    m = re.search(r"typedef struct\s*\w*\s*\{([^}]*)\}\s*" + re.escape(tname) + r"\s*;", text, re.S)
    return m.group(0) if m else f"(declaration of {tname} not found)"


def excerpts(tname, field, users, cap=8):
    pats = [re.compile(re.escape(p) + re.escape(field) + r"(?![A-Za-z0-9_])") for p in (".", "->")]
    out = []
    for u in users:
        p = os.path.join(REPO, u)
        if not os.path.exists(p):
            continue
        try:
            lines = open(p, errors="replace").read().splitlines()
        except OSError:
            continue
        for i, line in enumerate(lines):
            if any(pat.search(line) for pat in pats):
                ctx = lines[max(0, i - 1):i + 2]
                out.append(f"{u}:{i + 1}: " + " | ".join(x.strip() for x in ctx))
                if len(out) >= cap:
                    return out
    return out


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--header", required=True)
    ap.add_argument("--batch", required=True)
    ap.add_argument("--model", default="gpt-5.6-sol")
    ap.add_argument("--out", required=True)
    args = ap.parse_args()

    inv = load_inventory(args.header)
    if not inv:
        print(f"[{args.batch}] {args.header}: no safe fields in inventory")
        return
    blocks = []
    for tname, d in sorted(inv.items()):
        safe = ", ".join(f for f, _ in d["fields"])
        fields = "\n".join(f"  {decl}" for _f, decl in d["fields"])
        ex = []
        for f, _decl in d["fields"]:
            hits = excerpts(tname, f, d["users"])
            ex.append(f"  {tname}.{f}:\n    " + ("\n    ".join(hits) if hits else "(no uses found)"))
        blocks.append(
            f"### typedef {tname} (header {args.header}; user files: {', '.join(d['users'][:10])})\n"
            f"SAFE LIST (the only fields you may rename): {safe}\n"
            f"Declaration:\n{struct_decl(args.header, tname)}\n"
            f"Usage excerpts per safe field:\n" + "\n".join(ex))
    user = (f"Propose field renames for these structs. Batch tag: {args.batch}\n\n" + "\n\n".join(blocks))

    print(f"[{args.batch}] {args.header}: {len(inv)} typedefs, {sum(len(d['fields']) for d in inv.values())} safe fields"
          f" -> {args.model}", flush=True)
    out = call_model(args.model, SYSTEM.replace("BATCH", args.batch), user)
    os.makedirs(args.out, exist_ok=True)
    base = os.path.join(args.out, f"{args.batch}_{os.path.basename(args.header)}")
    open(base + ".raw", "w").write(out)

    rows = []
    for line in out.splitlines():
        line = line.strip()
        if not line or line.startswith(("#", "TypedefName\t", "```")):
            continue
        parts = [p.strip() for p in line.split("\t")]
        if len(parts) < 6:
            continue
        old, new = parts[0], parts[1]
        if not re.fullmatch(r"[A-Za-z_][A-Za-z0-9_]*\.unk_[0-9A-Fa-f]+w?", old):
            continue
        if not re.fullmatch(r"[A-Za-z_][A-Za-z0-9_]*", new) or new.startswith("unk_"):
            continue
        just = parts[4].encode("ascii", "replace").decode().strip()
        rows.append((old, new, args.batch, "", just))
    with open(base + ".tsv", "w") as f:
        for old, new, b, also, just in rows:
            f.write(f"{old}\t{new}\t{b}\t{also}\t{just}\tpending\n")
    print(f"[{args.batch}] {len(rows)} field proposal rows -> {base}.tsv", flush=True)


if __name__ == "__main__":
    main()
