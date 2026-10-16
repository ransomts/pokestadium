#!/usr/bin/env python3
"""Phase D prototype: migrate a spimdisasm data file (asm/us/data/**.s) into the C files that own it.

  datamig.py plan  asm/us/data/rom_data_7A110.data.s      # table: label, size, users, decl, owner, verdict
  datamig.py apply asm/us/data/rom_data_7A110.data.s      # edit src/, yamls/us/rom.yaml, symbol_addrs.txt
  datamig.py survey                                        # plan summary for every real data file

Bytes come from the baserom (by ROM offset), symbol references from the .s (.word sym[+off]),
types from the existing extern/definition, struct layouts from tools/data2c.py. Nothing here
proves a match: `make extract && make` (run by phased_job.sh on a compute node) is the gate.
Run from the repo root.
"""
import os
import re
import struct
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
os.chdir(ROOT)
sys.path.insert(0, str(ROOT / "tools"))
_argv = sys.argv
sys.argv = [str(ROOT / "tools" / "data2c.py")]
import data2c  # noqa: E402  (parses every header at import; ~2 s)
sys.argv = _argv

ROM = (ROOT / "baseroms/us/baserom.z64").read_bytes()
YAML = ROOT / "yamls/us/rom.yaml"
SYMS = ROOT / "linker_scripts/us/symbol_addrs.txt"
SKIP_NAMES = ("_header.s", "_reloc.s")

ITEM = re.compile(r"/\* ([0-9A-F]+) ([0-9A-F]{8})(?: [0-9A-F]+)? \*/ \.(\w+)\s*(.*)")
LABEL = re.compile(r"^(?:dlabel|glabel|jlabel)\s+(\w+)")
SYMREF = re.compile(r"^([A-Za-z_]\w*)(?:\s*\+\s*(0x[0-9A-Fa-f]+|\d+))?$")
SCALARS = {"s8": "b", "u8": "B", "s16": "h", "u16": "H", "s32": "i", "u32": "I", "s64": "q", "u64": "Q",
           "f32": "f", "f64": "d", "float": "f", "double": "d", "char": "b", "short": "h", "int": "i",
           "long": "i", "OSPri": "i", "OSId": "i", "OSMesg": "P", "OSTime": "Q"}
for _q in list(SCALARS):
    if _q[0] in "su" and _q[1:].isdigit():
        SCALARS["v" + _q] = SCALARS[_q]


def parse_s(path):
    """-> section, [label dict(name, rom, vram, relocs{vram: (sym, addend)})] in address order."""
    section, labels, cur = None, [], None
    for line in Path(path).read_text(encoding="utf-8", errors="replace").splitlines():
        s = line.strip()
        if s.startswith(".section"):
            section = s.split()[1].rstrip(",").strip('"')
        m = LABEL.match(s)
        if m:
            cur = {"name": m.group(1), "rom": None, "vram": None, "relocs": {}}
            labels.append(cur)
            continue
        m = ITEM.search(s)
        if m and cur is not None:
            rom, vram, d, arg = int(m.group(1), 16), int(m.group(2), 16), m.group(3), m.group(4).strip()
            if cur["rom"] is None:
                cur["rom"], cur["vram"] = rom, vram
            if d == "word":
                r = SYMREF.match(arg)
                if r:
                    cur["relocs"][vram] = (r.group(1), int(r.group(2) or "0", 0))
    labels = [l for l in labels if l["rom"] is not None]
    return section, labels


def yaml_entry(stem):
    """Index of the yaml line `[0xROM, data|rodata|bss, <stem>]` plus all lines."""
    lines = YAML.read_text().splitlines()
    pat = re.compile(r"^\s*-\s*\[\s*(0x[0-9A-Fa-f]+)\s*,\s*(data|rodata|bss)\s*(?:,\s*([\w/]+)\s*)?\]")
    for i, l in enumerate(lines):
        m = pat.match(l)
        if m and (m.group(3) or "%X" % int(m.group(1), 16)) == stem:
            return i, int(m.group(1), 16), lines
    return None, None, lines


def segment_bounds(lines, idx):
    """Rom end of the yaml entry at idx (next entry's start)."""
    for l in lines[idx + 1:]:
        m = re.match(r"^\s*-\s*\[\s*(0x[0-9A-Fa-f]+)", l)
        if m:
            return int(m.group(1), 16)
        if re.match(r"^\s*-\s*(name|\{)", l) or l.startswith("- "):
            break
    return None


def code_order(lines, idx):
    """Position of each `c` subsegment inside the yaml segment that contains line idx."""
    start = idx
    while start > 0 and not re.match(r"^\s*-\s*name:", lines[start]):
        start -= 1
    end = idx
    while end + 1 < len(lines) and not re.match(r"^\s*-\s*name:", lines[end + 1]):
        end += 1
    order = {}
    for i in range(start, end + 1):
        m = re.match(r"^\s*-\s*\[\s*0x[0-9A-Fa-f]+\s*,\s*(c|hasm|asm)\s*(?:,\s*([\w/.]+))?", lines[i])
        if m and m.group(2):
            order.setdefault("src/" + m.group(2) + ".c", len(order))
    return order, start, end


def neighbours(lines, idx, sect, start, end):
    """C files whose .data/.rodata section sits just before / after the entry."""
    pat = re.compile(r"^\s*-\s*\[\s*0x[0-9A-Fa-f]+\s*,\s*\.?(%s)\s*,\s*([\w/]+)" % sect)
    prev = nxt = None
    for i in range(idx - 1, start, -1):
        m = pat.match(lines[i])
        if m:
            prev = "src/" + m.group(2) + ".c"
            break
    for i in range(idx + 1, end + 1):
        m = pat.match(lines[i])
        if m:
            nxt = "src/" + m.group(2) + ".c"
            break
    return prev, nxt


_SRC_CACHE = None


def sources():
    global _SRC_CACHE
    if _SRC_CACHE is None:
        _SRC_CACHE = {}
        for p in list(Path("src").rglob("*.c")) + list(Path("include").rglob("*.h")) + \
                list(Path("src").rglob("*.h")):
            _SRC_CACHE[str(p)] = p.read_text(encoding="utf-8", errors="replace")
    return _SRC_CACHE


DECL = r"^\s*(extern\s+)?((?:const\s+|volatile\s+|static\s+)*[A-Za-z_][\w ]*?[\s*]+)\b%s\b\s*((?:\[[^\]]*\])*)\s*(=|;)"
FPDECL = r"^\s*(extern\s+)?([A-Za-z_][\w ]*?)\(\s*\*\s*%s\s*((?:\[[^\]]*\])*)\s*\)\s*(\([^;]*\))\s*;"


def find_decl(name):
    """-> list of (file, lineno, kind, type, dims, is_extern, text)."""
    out = []
    rx = re.compile(DECL % re.escape(name), re.M)
    fx = re.compile(FPDECL % re.escape(name), re.M)
    for f, t in sources().items():
        if name not in t:
            continue
        for m in rx.finditer(t):
            ty = " ".join(m.group(2).replace("*", " * ").split()).replace(" *", "*")
            if ty.split()[0] in ("return", "goto", "case", "else", "if"):
                continue
            out.append((f, t.count("\n", 0, m.start()) + 1, "var", ty, m.group(3), bool(m.group(1)), m.group(0).strip()))
        for m in fx.finditer(t):
            out.append((f, t.count("\n", 0, m.start()) + 1, "fnptr", m.group(2).strip(), m.group(3), bool(m.group(1)),
                        m.group(0).strip()))
    return out


def users(name):
    rx = re.compile(r"\b%s\b" % re.escape(name))
    return sorted(f for f, t in sources().items() if f.endswith(".c") and rx.search(t))


def dims_of(s):
    out = []
    for d in re.findall(r"\[([^\]]*)\]", s or ""):
        d = d.strip()
        if d == "":
            out.append(None)
        elif d in data2c.DEFINES:
            out.append(data2c.DEFINES[d])
        else:
            try:
                out.append(int(d, 0))
            except ValueError:
                out.append("?")
    return out


def base_type(ty):
    t = " ".join(w for w in ty.split() if w not in ("const", "volatile", "static", "struct", "union", "unsigned",
                                                    "signed"))
    return t


def type_size(ty):
    t = base_type(ty)
    if t.endswith("*"):
        return 4
    if t in SCALARS:
        return struct.calcsize(">" + SCALARS[t].replace("P", "I"))
    if t in data2c.BASE_TYPES:
        return data2c.BASE_TYPES[t]
    s = data2c.STRUCTS.get(t)
    if s and "size" in s and "bad" not in s:
        return s["size"]
    return None


class Emit:
    def __init__(self, lab):
        self.lab, self.relocs, self.problems = lab, lab["relocs"], []

    def ptr(self, vram):
        if vram in self.relocs:
            sym, add = self.relocs[vram]
            return f"&{sym}" if add == 0 else f"(void*)((u8*)&{sym} + 0x{add:X})"
        v = struct.unpack(">I", ROM[self.rom(vram):self.rom(vram) + 4])[0]
        return "NULL" if v == 0 else f"(void*)0x{v:08X}"

    def rom(self, vram):
        return self.lab["rom"] + (vram - self.lab["vram"])

    def scalar(self, t, vram):
        code = SCALARS.get(t)
        if code is None:
            code = {1: "B", 2: "H", 4: "I", 8: "Q"}[data2c.BASE_TYPES[t]]
        if vram in self.relocs and code in "IiP":
            return self.ptr(vram) if code == "P" else f"(u32){self.ptr(vram)}"
        if code == "P":
            return self.ptr(vram)
        r = self.rom(vram)
        v = struct.unpack(">" + code, ROM[r:r + struct.calcsize(">" + code)])[0]
        if code == "f":
            # shortest decimal that round-trips through f32
            s = next(c for c in ("%%.%dg" % p % v for p in range(6, 10))
                     if struct.pack(">f", float(c)) == ROM[r:r + 4])
            if "inf" in s or "nan" in s:
                self.problems.append(f"non-finite float at {vram:08X}")
            return s + ("" if any(c in s for c in ".e") else ".0") + "f"
        if code == "d":
            s = next(c for c in ("%%.%dg" % p % v for p in range(15, 18))
                     if struct.pack(">d", float(c)) == ROM[r:r + 8])
            return s + ("" if any(c in s for c in ".e") else ".0")
        if code in "BHIQ":
            return f"0x{v:X}" if v > 9 else str(v)
        return str(v)

    def value(self, ty, dims, vram):
        """C initializer for an object of type ty[dims...] at vram."""
        if dims:
            n, rest = dims[0], dims[1:]
            esz = 4 if ty == "fnptr" else type_size(ty)
            for d in rest:
                esz *= d
            items = [self.value(ty, rest, vram + i * esz) for i in range(n)]
            return "{ " + ", ".join(items) + " }"
        t = base_type(ty)
        if t.endswith("*") or t == "fnptr":
            return self.ptr(vram)
        if t in SCALARS or t in data2c.BASE_TYPES:
            return self.scalar(t, vram)
        s = data2c.STRUCTS.get(t)
        if not s or "size" not in s or "bad" in s:
            self.problems.append(f"no layout for type {t}")
            return "/* ? */"
        members = s["data"]
        if s["union"]:
            members = members[:1]
            if members and members[0]["size"] != s["size"]:
                self.problems.append(f"union {t}: first member does not cover it")
        parts = []
        for m in members:
            mt = m["type"]
            if mt == "ptr":
                mt = "void*"
            parts.append(self.value(mt, m["counts"], vram + m["offset"]))
        return "{ " + ", ".join(parts) + " }"


def plan(path, quiet=False):
    sect, labels = parse_s(path)
    stem = str(Path(path).relative_to("asm/us/data").with_suffix("")).rsplit(".", 1)[0]
    idx, yrom, lines = yaml_entry(stem)
    res = {"path": path, "section": sect, "stem": stem, "yaml_idx": idx, "labels": [], "blockers": []}
    if idx is None:
        res["blockers"].append("no yaml entry")
        return res
    end_rom = segment_bounds(lines, idx)
    order, s0, s1 = code_order(lines, idx)
    kind = sect.lstrip(".")
    prev, nxt = neighbours(lines, idx, kind, s0, s1)
    lo = order.get(prev, -1) if prev else -1
    hi = order.get(nxt, 10 ** 9) if nxt else 10 ** 9
    res.update(prev=prev, next=nxt)
    for i, l in enumerate(labels):
        nrom = labels[i + 1]["rom"] if i + 1 < len(labels) else end_rom
        span = (nrom - l["rom"]) if nrom else None
        decls = find_decl(l["name"])
        defs = [d for d in decls if not d[5]]
        ext = [d for d in decls if d[5]]
        us = users(l["name"])
        owner, why = None, ""
        if defs:
            owner, why = defs[0][0], "already defined"
        elif len(us) == 1:
            owner, why = us[0], "only user"
        elif us:
            inside = [u for u in us if lo < order.get(u, -2) < hi]
            if len(inside) == 1:
                owner, why = inside[0], "user between neighbours"
            else:
                why = f"{len(us)} users"
        else:
            why = "no C user"
        d = (ext or decls or [None])[0]
        ty, dims, size = None, [], None
        if d:
            ty = "fnptr" if d[2] == "fnptr" else d[3]
            dims = dims_of(d[4])
            es = 4 if ty == "fnptr" else type_size(ty)
            if es and all(isinstance(x, int) for x in dims):
                size = es
                for x in dims:
                    size *= x
            elif es and dims and dims[0] in (None, "?") and all(isinstance(x, int) for x in dims[1:]) and span:
                inner = es
                for x in dims[1:]:
                    inner *= x
                dims = [span // inner] + dims[1:]
                size = dims[0] * inner
        verdict = "ok"
        if owner and owner not in order:
            verdict = "owner not in this segment"
        elif owner and not (lo < order[owner] < hi):
            verdict = f"owner out of link order ({prev} < ? < {nxt})"
        if size is None:
            verdict = "type size unknown" if verdict == "ok" else verdict
        elif span is not None and size != span:
            tail = ROM[l["rom"] + size:l["rom"] + span] if size < span else b""
            if size > span:
                verdict = f"decl size 0x{size:X} > span 0x{span:X}"
            elif any(tail):
                # e.g. extern T x[5] for a 16-entry table; fix_short_arrays() grows dim 0.
                verdict = f"decl size 0x{size:X} < span 0x{span:X} (nonzero tail)"
        res["labels"].append(dict(l, span=span, size=size, type=ty, dims=dims, decl=d, users=us, owner=owner,
                                  why=why, verdict=verdict, fnargs=(d[3] if d and d[2] == "fnptr" else None),
                                  fnsig=(re.search(r"\)\s*(\([^;]*\))\s*;", d[6]).group(1) if d and d[2] == "fnptr" else None)))
    # Owners must appear in non-decreasing link order through the file.
    seq = [order.get(l["owner"], -1) for l in res["labels"] if l["owner"]]
    if seq != sorted(seq):
        res["blockers"].append("owners interleave in link order (data needs a different split)")
    for o in {l["owner"] for l in res["labels"] if l["owner"]}:
        if re.search(r"\[\s*0x[0-9A-Fa-f]+\s*,\s*\.%s\s*,\s*%s\s*\]" % (kind, re.escape(o[4:-2])), "\n".join(lines)):
            res["blockers"].append(f"{o} already has a .{kind} entry: defs must merge into its existing data")
    if not quiet:
        print(f"{path}: section {sect}, yaml line {idx + 1}, between .{kind} of {prev} and {nxt}")
        for l in res["labels"]:
            dims = "".join(f"[{x}]" for x in l["dims"])
            print(f"  {l['vram']:08X} {l['name']:<28} span {l['span'] if l['span'] is None else hex(l['span']):>7}"
                  f" size {hex(l['size']) if l['size'] else '?':>7}  {str(l['type']) + dims:<22}"
                  f" owner {l['owner'] or '-'} ({l['why']})  -> {l['verdict']}")
        for b in res["blockers"]:
            print("  BLOCKER:", b)
    return res


def fix_short_arrays(res):
    """Grow a too-short dim 0 (extern T x[5] for 16 entries) when the span is a whole number of elements."""
    for l in res["labels"]:
        if l["verdict"].startswith("decl size") and "nonzero tail" in l["verdict"] and l["dims"] and \
                isinstance(l["dims"][0], int) and l["dims"][0] > 0:
            per = l["size"] // l["dims"][0]
            # span includes up-to-16-byte alignment padding; strip trailing zeros only to the element grid
            n = l["span"] // per
            while n * per > l["size"] and not any(ROM[l["rom"] + (n - 1) * per:l["rom"] + n * per]) and \
                    (l["span"] - (n - 1) * per) < 16:
                n -= 1
            l["dims"] = [n] + l["dims"][1:]
            l["size"] = n * per
            l["verdict"] = "ok (array grown to %d)" % n


def definition(l, const):
    e = Emit(l)
    dims = "".join(f"[{x}]" for x in l["dims"])
    if l["type"] == "fnptr":
        ret = l["decl"][3]
        body = e.value("fnptr", l["dims"], l["vram"])
        text = f"{ret} (*{l['name']}{dims}){l['fnsig']} = {body};"
    else:
        ty = l["type"]
        if const and "const" not in ty:
            ty = "const " + ty
        text = f"{ty} {l['name']}{dims} = {e.value(l['type'], l['dims'], l['vram'])};"
    return text, e.problems


def apply(path):
    res = plan(path)
    fix_short_arrays(res)
    bad = [l for l in res["labels"] if not l["owner"] or not l["verdict"].startswith("ok")]
    if bad or res["blockers"]:
        print("REFUSING: unresolved labels/blockers above")
        return 2
    const = res["section"] == ".rodata"
    by_owner, inline = {}, []
    nonmatch = "\n".join(p.read_text(errors="replace") for p in Path("asm/us/nonmatchings").rglob("*.s")) \
        if Path("asm/us/nonmatchings").exists() else ""
    for l in res["labels"]:
        if const and not l["dims"] and base_type(l["type"] or "") in ("f32", "f64", "float", "double"):
            # IDO puts a named const scalar in .data; a .rodata float in the ROM was an anonymous
            # literal, so substitute the value at its use instead of defining a variable.
            if len(l["users"]) != 1 or re.search(r"\b%s\b" % l["name"], nonmatch):
                print(f"REFUSING: {l['name']} is a literal but used by {l['users']} / GLOBAL_ASM")
                return 2
            l["inline"] = Emit(l).scalar(base_type(l["type"]), l["vram"])
            inline.append(l)
            continue
        if const and not l["dims"] and base_type(l["type"] or "") in SCALARS:
            print(f"REFUSING: {l['name']}: named const scalar would land in .data, not .rodata")
            return 2
        text, probs = definition(l, const)
        if probs:
            print(f"REFUSING: {l['name']}: {probs}")
            return 2
        by_owner.setdefault(l["owner"], []).append((l, text))
    src = sources()
    for l in inline:
        f = l["users"][0]
        txt = src[f]
        if l["decl"] and l["decl"][0] == f and l["decl"][5]:
            txt = txt.replace(l["decl"][6] + "\n", "", 1)
        txt, n = re.subn(r"\b%s\b" % l["name"], l["inline"], txt)
        src[f] = txt
        Path(f).write_text(txt)
        print(f"inlined {l['name']} = {l['inline']} at {n} use(s) in {f}")
    for owner, items in by_owner.items():
        t = src[owner]
        block, pos = [], None
        for l, text in items:
            block.append(text)
            # drop the owner's own extern (headers keep theirs; extern + definition are compatible);
            # the block goes where the first such extern was, so local typedefs are already declared
            if l["decl"] and l["decl"][0] == owner and l["decl"][5]:
                i = t.find(l["decl"][6] + "\n")
                if i >= 0:
                    t = t[:i] + t[i + len(l["decl"][6]) + 1:]
                    pos = i if pos is None else min(pos, i)
        # forward-declare referenced symbols the owner cannot see (gcc's syntax check rejects them)
        fwd = []
        for l, _ in items:
            for sym, _a in l["relocs"].values():
                if sym in fwd or re.search(r"\b%s\b" % re.escape(sym), t):
                    continue
                hdr = any(re.search(r"\b%s\s*\(" % re.escape(sym), x) or
                          re.search(r"extern[^;]*\b%s\b" % re.escape(sym), x)
                          for f, x in src.items() if f.endswith(".h"))
                if not hdr:
                    fwd.append(sym)
        decls = []
        for sym in fwd:
            isfn = any(re.search(r"^[\w*][\w\s*]*\b%s\s*\([^;]*\)\s*\{" % re.escape(sym), x, re.M)
                       for f, x in src.items() if f.endswith(".c"))
            decls.append(f"void {sym}(void);" if isfn else f"extern u8 {sym}[];")
        if decls:
            block = decls + [""] + block
        ins = "\n".join(block) + "\n"
        if pos is None:
            incs = list(re.finditer(r"^#include .*\n", t, re.M))
            pos = incs[-1].end() if incs else 0
            ins = "\n" + ins + "\n"
        t = t[:pos] + ins + t[pos:]
        t = re.sub(r"\n{3,}", "\n\n", t)
        Path(owner).write_text(t)
        print(f"wrote {len(items)} definition(s) into {owner}")
    # yaml: one entry per owner run
    idx, yrom, lines = yaml_entry(res["stem"])
    indent = re.match(r"^(\s*)", lines[idx]).group(1)
    kind = res["section"].lstrip(".")
    new, last = [], None
    for l in res["labels"]:
        if l["owner"] != last:
            new.append(f"{indent}- [0x{l['rom']:X}, .{kind}, {l['owner'][4:-2]}]")
            last = l["owner"]
    lines[idx:idx + 1] = new
    YAML.write_text("\n".join(lines) + "\n")
    # symbol_addrs: mark as defined so splat stops emitting them as undefined symbols. Edit the
    # entry in whichever symbol_addrs*.txt already has it (a second entry is a splat error).
    changed = set()
    files = {f: f.read_text().splitlines() for f in sorted(SYMS.parent.glob("symbol_addrs*.txt"))}
    for l in res["labels"]:
        if "inline" in l:
            continue
        tag = f"{l['name']} = 0x{l['vram']:08X}; // defined:true size:0x{l['size']:X}"
        hit = None
        for f, syms in files.items():
            for i, s in enumerate(syms):
                if re.match(r"^%s\s*=" % re.escape(l["name"]), s):
                    syms[i] = tag
                    hit = f
                    break
            if hit:
                break
        if not hit:
            files[SYMS].append(tag)
            hit = SYMS
        changed.add(hit)
    for f in changed:
        f.write_text("\n".join(files[f]) + "\n")
    print("yaml + symbol_addrs updated; now: make extract && make  (phased_job.sh does this)")
    return 0


def survey():
    files = sorted(str(p) for p in Path("asm/us/data").rglob("*.s") if not str(p).endswith(SKIP_NAMES))
    for f in files:
        try:
            r = plan(f, quiet=True)
        except Exception as e:  # keep the survey going
            print(f"{f}: ERROR {e}")
            continue
        fix_short_arrays(r)
        n = len(r["labels"])
        ok = sum(1 for l in r["labels"] if l["owner"] and l["verdict"].startswith("ok"))
        size = sum(l["span"] or 0 for l in r["labels"])
        tag = "READY" if n and ok == n and not r["blockers"] else "     "
        print(f"{tag} {ok:>4}/{n:<4} labels ok  0x{size:>6X} bytes  {f}" +
              (f"  [{'; '.join(r['blockers'])}]" if r["blockers"] else ""))


if __name__ == "__main__":
    if len(sys.argv) < 2 or sys.argv[1] not in ("plan", "apply", "survey"):
        print(__doc__)
        sys.exit(1)
    if sys.argv[1] == "survey":
        survey()
    elif sys.argv[1] == "plan":
        plan(sys.argv[2])
    else:
        sys.exit(apply(sys.argv[2]))
