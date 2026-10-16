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
            cur = {"name": m.group(1), "rom": None, "vram": None, "relocs": {}, "dirs": set()}
            labels.append(cur)
            continue
        m = ITEM.search(s)
        if m and cur is not None:
            rom, vram, d, arg = int(m.group(1), 16), int(m.group(2), 16), m.group(3), m.group(4).strip()
            if cur["rom"] is None:
                cur["rom"], cur["vram"] = rom, vram
            cur["dirs"].add(d)
            if d == "word":
                r = SYMREF.match(arg)
                raw = struct.unpack(">I", ROM[rom:rom + 4])[0]
                # spimdisasm also symbolizes sample words that merely look like addresses
                # (D_102, D_5000000); only KSEG0 values are real pointers
                if r and 0x80000000 <= raw < 0xA0000000:
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
        m = re.match(r"^\s*-\s*\[\s*(0x[0-9A-Fa-f]+)\s*,\s*(c|hasm|asm)\s*(?:,\s*([\w/.]+))?", lines[i])
        if m:  # unnamed entries are named after their rom address by splat
            name = m.group(3) or "%X" % int(m.group(1), 16)
            order.setdefault("src/" + name + ".c", len(order))
    return order, start, end


def neighbours(lines, idx, sect, start, end, order=None):
    """Nearest C files (in `order`) whose .data/.rodata section sits before / after the entry;
    asm data blobs in between are skipped, they only widen the window."""
    pat = re.compile(r"^\s*-\s*\[\s*0x[0-9A-Fa-f]+\s*,\s*\.?(%s)\s*,\s*([\w/]+)" % sect)
    ok = lambda f: order is None or f in order
    prev = nxt = None
    for i in range(idx - 1, start, -1):
        m = pat.match(lines[i])
        if m and ok("src/" + m.group(2) + ".c"):
            prev = "src/" + m.group(2) + ".c"
            break
    for i in range(idx + 1, end + 1):
        m = pat.match(lines[i])
        if m and ok("src/" + m.group(2) + ".c"):
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


_DRAFTS = {}


def in_draft(f, t, pos):
    """True if pos lies in an `#ifdef NON_MATCHING` branch (a draft, not compiled in the real build)."""
    if f not in _DRAFTS:
        spans = []
        for m in re.finditer(r"^#ifdef NON_MATCHING\b.*$", t, re.M):
            e = re.compile(r"^#(else|endif)\b", re.M).search(t, m.end())
            spans.append((m.start(), e.start() if e else len(t)))
        _DRAFTS[f] = spans
    return any(a <= pos < b for a, b in _DRAFTS[f])


def find_decl(name):
    """-> list of (file, lineno, kind, type, dims, is_extern, text); definitions in drafts are skipped."""
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
            dr = in_draft(f, t, m.start())  # drafts: not in the IDO build, but gcc's check compiles them
            if dr and not m.group(1):
                continue
            out.append((f, t.count("\n", 0, m.start()) + 1, "var", ty, m.group(3), bool(m.group(1)), m.group(0).strip(),
                        dr))
        for m in fx.finditer(t):
            dr = in_draft(f, t, m.start())
            if dr and not m.group(1):
                continue
            out.append((f, t.count("\n", 0, m.start()) + 1, "fnptr", m.group(2).strip(), m.group(3), bool(m.group(1)),
                        m.group(0).strip(), dr))
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
    arrays = set()  # symbols defined as arrays in the current batch: referenced by bare name

    def __init__(self, lab):
        self.lab, self.relocs, self.problems = lab, lab["relocs"], []

    def ptr(self, vram):
        if vram in self.relocs:
            sym, add = self.relocs[vram]
            ref = f"(void*){sym}" if sym in Emit.arrays else f"&{sym}"
            return ref if add == 0 else f"(void*)((u8*){ref} + 0x{add:X})"
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


_ASM_CACHE = None


def asm_users(name):
    """C files whose GLOBAL_ASM functions (asm/us/nonmatchings/<file>/<func>.s) reference name."""
    global _ASM_CACHE
    if _ASM_CACHE is None:
        _ASM_CACHE = {}
        base = Path("asm/us/nonmatchings")
        for p in base.rglob("*.s") if base.exists() else []:
            src = "src/" + str(p.parent.relative_to(base)) + ".c"
            _ASM_CACHE[src] = _ASM_CACHE.get(src, "") + p.read_text(errors="replace")
    rx = re.compile(r"\b%s\b" % re.escape(name))
    return sorted(f for f, t in _ASM_CACHE.items() if rx.search(t))


def infer_type(l, span, rodata):
    """Type from the spimdisasm directives when no C declaration exists: (type, dims, size)."""
    d = l["dirs"]
    arr = lambda n: [n] if (n != 1 or rodata) else []  # const scalars land in .data: keep arrays
    if d == {"float"} and span % 4 == 0:
        return "f32", arr(span // 4), span
    if d == {"double"} and span % 8 == 0:
        return "f64", arr(span // 8), span
    if span % 4 == 0 and l["vram"] % 4 == 0 and (d <= {"word", "float", "double"} or l["relocs"]):
        return "u32", arr(span // 4), span
    if l["relocs"]:
        return None, [], None
    if d == {"half"} and span % 2 == 0:
        return "u16", arr(span // 2), span
    return "u8", [span], span


def resolve_orphans(labs):
    """Give owners to labels nobody in C names: pointer targets, then runs between owned labels."""
    changed = True
    while changed:  # a label pointed to only by data labels of one owner joins that owner
        changed = False
        for l in labs:
            if l["owner"]:
                continue
            refs = {m["owner"] for m in labs if m is not l and any(s == l["name"] for s, _ in m["relocs"].values())}
            if len(refs) == 1 and None not in refs:
                l["owner"], l["why"] = refs.pop(), "pointed to by its data"
                changed = True
    i = 0
    while i < len(labs):
        if labs[i]["owner"]:
            i += 1
            continue
        j = i
        while j + 1 < len(labs) and not labs[j + 1]["owner"]:
            j += 1
        a = labs[i - 1]["owner"] if i > 0 else None
        b = labs[j + 1]["owner"] if j + 1 < len(labs) else None
        fits = lambda k, o: not labs[k]["cands"] or o in labs[k]["cands"]
        if not a and not b:
            # nothing anchors the run: take the candidate allowed everywhere and used most (ties: later
            # file). Any such choice gives the same bytes; it is a guess about the original file.
            pool = [c for k in range(i, j + 1) for c in labs[k]["cands"]]
            ok = [c for c in dict.fromkeys(pool) if all(fits(k, c) for k in range(i, j + 1))]
            if ok:
                best = max(ok, key=lambda c: (pool.count(c), ok.index(c)))
                for k in range(i, j + 1):
                    labs[k]["owner"], labs[k]["why"] = best, "guess: shared by all users"
                i = j + 1
                continue
        if a and (a == b or not b) and all(fits(k, a) for k in range(i, j + 1)):
            for k in range(i, j + 1):
                labs[k]["owner"], labs[k]["why"] = a, "inferred: run after its data"
        elif b and not a and all(fits(k, b) for k in range(i, j + 1)):
            for k in range(i, j + 1):
                labs[k]["owner"], labs[k]["why"] = b, "inferred: run before its data"
        elif a and b and a != b:
            # each C file's section starts 16-aligned: the split is a 16-aligned label start, with every
            # label before it allowed in a and every label after it allowed in b
            vram = lambda k: labs[k]["vram"] if k <= j else labs[j + 1]["vram"]
            cands = [k for k in range(i, j + 2) if vram(k) % 16 == 0
                     and all(fits(x, a) for x in range(i, k)) and all(fits(x, b) for x in range(k, j + 1))]
            if len(cands) == 1:
                for k in range(i, j + 1):
                    o = a if k < cands[0] else b
                    labs[k]["owner"], labs[k]["why"] = o, "inferred: 16-aligned split"
            else:
                for k in range(i, j + 1):
                    labs[k]["why"] = f"between {a} and {b}: {len(cands)} possible splits"
        i = j + 1


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
    prev, nxt = neighbours(lines, idx, kind, s0, s1, order)
    lo = order.get(prev, -1) if prev else -1
    hi = order.get(nxt, 10 ** 9) if nxt else 10 ** 9
    res.update(prev=prev, next=nxt)
    labs = []
    for i, l in enumerate(labels):
        nrom = labels[i + 1]["rom"] if i + 1 < len(labels) else end_rom
        span = (nrom - l["rom"]) if nrom else None
        decls = find_decl(l["name"])
        defs = [d for d in decls if not d[5]]
        ext = [d for d in decls if d[5]]
        us = sorted(set(users(l["name"])) | set(asm_users(l["name"])))
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
        cands = sorted({u for u in us if lo < order.get(u, -2) < hi}, key=order.get) if not owner else []
        labs.append(dict(l, span=span, decls=decls, ext=ext, users=us, owner=owner, why=why, cands=cands))
    # IDO aligns every data object to 4: a label at an unaligned address is a field of the previous
    # object. Fold it in; its symbol stays linker-defined (symbol_addrs without defined:true).
    k = 1
    while k < len(labs):
        if labs[k]["vram"] % 4 and labs[k - 1]["span"] is not None:
            p_, x = labs[k - 1], labs.pop(k)
            p_["span"] += x["span"] or 0
            p_["relocs"].update(x["relocs"])
            p_.setdefault("folded", []).append(x["name"])
            p_.setdefault("folded_at", []).append((x["name"], x["vram"] - p_["vram"]))
            p_["users"] = sorted(set(p_["users"]) | set(x["users"]))
            if not p_["owner"] and x["owner"]:
                p_["owner"], p_["why"] = x["owner"], f"via folded {x['name']}"
            continue
        k += 1
    # spimdisasm splits an array at every field the code touches (D_80070F84 PokemonStats[] ->
    # D_80070F8A, D_80070F8B, ...). An unsized array absorbs the following labels nobody names.
    referenced = {s for x in labs for s, _ in x["relocs"].values()}
    k = 0
    while k < len(labs):
        l = labs[k]
        d = ([x for x in (l["ext"] or l["decls"]) if not x[7]] or l["ext"] or l["decls"] or [None])[0]
        if d and d[2] == "var" and dims_of(d[4])[:1] == [None]:
            j = k
            while j + 1 < len(labs) and not labs[j + 1]["users"] and labs[j + 1]["name"] not in referenced \
                    and not find_decl(labs[j + 1]["name"]):
                j += 1
            if j > k:
                for x in labs[k + 1:j + 1]:
                    l["relocs"].update(x["relocs"])
                    l["dirs"] |= x["dirs"]
                l["span"] = sum(x["span"] or 0 for x in labs[k:j + 1])
                l["absorbed"] = [x["name"] for x in labs[k + 1:j + 1]]
                del labs[k + 1:j + 1]
        k += 1
    resolve_orphans([x for x in labs])
    for l in labs:
        span, decls, ext, owner = l["span"], l.pop("decls"), l.pop("ext"), l["owner"]
        real = [x for x in (ext or decls) if not x[7]]
        d = (real or ext or decls or [None])[0]
        if d and d[7]:
            # only a draft declares it: use the draft's type (gcc's check compiles drafts) and hoist the
            # draft's own typedef of that type out of the draft so the real build can see it
            tname = base_type(d[3]).rstrip("*")
            ft = sources()[d[0]]
            m = re.search(r"^typedef (struct|union) \w*\s*\{[^{}]*^\}\s*%s\s*;[^\n]*\n" % re.escape(tname), ft, re.M)
            if m and in_draft(d[0], ft, m.start()):
                l["hoist"] = (d[0], m.group(0))
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
                n = span // inner  # an unsized array owns its zeros; IDO pads arrays to 4 anyway
                dims = [n] + dims[1:]
                size = n * inner
        elif span:
            ty, dims, size = infer_type(l, span, kind == "rodata")
        verdict = "ok"
        if not owner:
            verdict = l["why"]
        elif owner not in order:
            verdict = "owner not in this segment"
        elif not (lo < order[owner] < hi):
            verdict = f"owner out of link order ({prev} < ? < {nxt})"
        if size is None:
            verdict = "type size unknown" if verdict == "ok" else verdict
        elif span is not None and size != span:
            tail = ROM[l["rom"] + size:l["rom"] + span] if size < span else b""
            if size > span:
                verdict = f"decl size 0x{size:X} > span 0x{span:X}"
            elif any(tail) and (not l.get("folded") or dims or
                                any(ROM[l["rom"] + size:l["rom"] + ((size + 3) & ~3)])):
                # (a folded tail is fine, but not one that starts inside the 4-byte alignment slack)
                # e.g. extern T x[5] for a 16-entry table; fix_short_arrays() grows dim 0.
                verdict = f"decl size 0x{size:X} < span 0x{span:X} (nonzero tail)"
        res["labels"].append(dict(l, size=size, type=ty, dims=dims, decl=d, verdict=verdict,
                                  fnargs=(d[3] if d and d[2] == "fnptr" else None),
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
        elif "nonzero tail" in l["verdict"] and not l["dims"] and l["type"] and \
                base_type(l["type"]) in SCALARS and address_only(l["name"]):
            # A scalar placeholder (`extern u16 D_X;`) on a longer object that C only ever takes the
            # address of (e.g. length-prefixed u16 lists passed as &D_X): retype it to an array.
            # `&D_X` -> `D_X` gives the same address constant, so codegen does not change.
            per = l["size"]
            n = l["span"] // per
            while n > 1 and not any(ROM[l["rom"] + (n - 1) * per:l["rom"] + n * per]) and \
                    ((n - 1) * per + 3) & ~3 == l["span"]:
                n -= 1  # trailing zeros that IDO's 4-byte object alignment re-creates anyway
            l["dims"], l["size"], l["retype"] = [n], n * per, True
            l["verdict"] = "ok (retyped to %s[%d])" % (base_type(l["type"]), n)


def address_only(name):
    """True if every C use of name (drafts included: gcc's check compiles them) is `&name`."""
    rx = re.compile(r"\b%s\b" % re.escape(name))
    for f, t in sources().items():
        if not f.endswith(".c"):
            continue
        for line in t.split("\n"):
            if not rx.search(line) or re.match(r"\s*(extern\b|//)", line):
                continue
            if len(rx.findall(line)) != len(re.findall(r"&\s*%s\b" % re.escape(name), line)):
                return False
    return True


def retype_uses(l, src):
    """Rewrite every extern of a retyped label to its array type and `&NAME` to `NAME`."""
    dims = "".join(f"[{x}]" for x in l["dims"])
    rx = re.compile(r"^(\s*extern\s+[^;]*?)\b%s\b\s*;" % re.escape(l["name"]), re.M)
    for f in list(src):
        t = src[f]
        if l["name"] not in t:
            continue
        n = rx.sub(lambda m: f"{m.group(1)}{l['name']}{dims};", t)
        if f.endswith(".c"):
            n = re.sub(r"&\s*%s\b" % re.escape(l["name"]), l["name"], n)
        if n != t:
            src[f] = n
            Path(f).write_text(n)
            if l["decl"] and l["decl"][0] == f:
                l["decl"] = l["decl"][:6] + (rx.search(n).group(0).strip() if rx.search(n) else l["decl"][6],) \
                    + l["decl"][7:]
            print(f"retyped {l['name']}{dims} in {f}")


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
    Emit.arrays = {l["name"] for l in res["labels"] if l["dims"]}
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
        # zero gap up to the next label: an explicit pad array (upstream style, e.g. src/20470.c),
        # unless it is just the 16-byte alignment that ends the owner's section anyway
        gap = (l["span"] or 0) - (l["size"] or 0)
        labs = res["labels"]
        k = labs.index(l)
        run_end = k + 1 == len(labs) or labs[k + 1]["owner"] != l["owner"]
        end = l["vram"] + l["size"]
        if gap > 0 and not (run_end and l["vram"] + l["span"] == (end + 15) & ~15):
            if any(ROM[l["rom"] + l["size"]:l["rom"] + l["span"]]) and not l.get("folded"):
                print(f"REFUSING: {l['name']}: nonzero bytes after its declared size")
                return 2
            # zero gaps are pads (upstream pad_D_ style); folded fields keep their values as a tail.
            # IDO aligns every array to 4, so sub-word pieces are scalars (aligned to their own size).
            q = "const " if const else ""
            stem = f"{l['name']}_tail" if l.get("folded") else f"pad_{l['name']}"
            e = Emit(l)
            stop = l["vram"] + l["span"]
            a = (end + 3) & ~3  # IDO starts every data object on a 4-byte boundary, zero-filling the slack
            if any(ROM[l["rom"] + l["size"]:l["rom"] + (min(a, stop) - l["vram"])]):
                print(f"REFUSING: {l['name']}: nonzero bytes in the alignment slack after it")
                return 2
            if l.get("folded"):
                text += f"  // tail holds {', '.join(l['folded'])} (linker-defined symbols)"
            if stop - a >= 4:
                n = (stop - a) // 4
                vals = ", ".join(e.scalar("u32", a + 4 * j) for j in range(n))
                text += f"\nstatic {q}u32 {stem}[{n}] = {{ {vals} }};"
                a += 4 * n
            if a < stop and any(ROM[l["rom"] + (a - l["vram"]):l["rom"] + l["span"]]):
                print(f"REFUSING: {l['name']}: unaligned nonzero tail")
                return 2
        by_owner.setdefault(l["owner"], []).append((l, text))
    src = sources()
    for l in res["labels"]:
        if l.get("retype"):
            retype_uses(l, src)
    for l in res["labels"]:
        if "grown" not in l["verdict"]:
            continue
        dims = "".join(f"[{x}]" for x in l["dims"])
        for f, _ln, _k, _ty, _dims, is_ext, text, *_ in find_decl(l["name"]):
            if is_ext:
                new = re.sub(r"\b(%s)\s*(\[[^\]]*\])+" % re.escape(l["name"]), r"\g<1>" + dims, text)
                src[f] = src[f].replace(text, new)
                Path(f).write_text(src[f])
                if l["decl"] and text == l["decl"][6]:
                    l["decl"] = l["decl"][:6] + (new,) + l["decl"][7:]
                print(f"resized extern {l['name']}{dims} in {f}")
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
        defined = {l["name"]: l for l, _ in items}
        for l, _ in items:
            if l.get("hoist") and l["hoist"][0] == owner and l["hoist"][1] in t:
                td = l["hoist"][1]
                i = t.index(td)
                j = t.rfind("#ifdef NON_MATCHING", 0, i)
                t = t[:i] + t[i + len(td):]
                t = t[:j] + td + "\n" + t[j:]
                hp = j + len(td) + 1
                pos = hp if pos is None else max(pos, hp)
                print(f"hoisted typedef of {l['name']} out of its draft in {owner}")
        for l, text in items:
            block.append(text)
            if l["decl"] and l["decl"][7]:
                continue  # never put the definition inside a draft
            # keep the owner's externs (extern + later definition is fine) and put the block after the
            # last of them: every type they use is declared there, and earlier uses still see a decl
            if l["decl"] and l["decl"][0] == owner and l["decl"][5]:
                i = t.find(l["decl"][6] + "\n")
                if i >= 0:
                    e = i + len(l["decl"][6]) + 1
                    pos = e if pos is None else max(pos, e)
        # forward-declare referenced symbols the owner cannot see (gcc's syntax check rejects them);
        # symbols of this batch defined later than their first use get a decl of their real type
        fwd, seen = [], set()
        for l, _ in items:
            seen.add(l["name"])
            for sym, _a in l["relocs"].values():
                if sym in fwd or (sym in defined and sym in seen):
                    continue
                if sym in defined:
                    fwd.append(sym)
                    continue
                if re.search(r"\b%s\b" % re.escape(sym), t):
                    continue
                hdr = any(re.search(r"\b%s\s*\(" % re.escape(sym), x) or
                          re.search(r"extern[^;]*\b%s\b" % re.escape(sym), x)
                          for f, x in src.items() if f.endswith(".h"))
                if not hdr:
                    fwd.append(sym)
        decls = []
        for sym in fwd:
            if sym in defined:
                d = defined[sym]
                if d["type"] == "fnptr":
                    decls.append(f"extern {d['decl'][3]} (*{sym}{''.join(f'[{x}]' for x in d['dims'])}){d['fnsig']};")
                else:
                    decls.append(f"extern {base_type(d['type'])} {sym}{''.join(f'[{x}]' for x in d['dims'])};")
                continue
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
        else:
            ins = "\n" + ins
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
    # folded fields are no C object: give the linker their address (asm-only users get no splat entry)
    ld = SYMS.parent / "undefined_syms.ld"
    have = ld.read_text()
    add = [f"{n} = 0x{l['vram'] + off:08X};" for l in res["labels"] for n, off in l.get("folded_at", [])
           if not re.search(r"^%s\s*=" % re.escape(n), have, re.M)]
    if add:
        ld.write_text(have.rstrip("\n") + "\n" + "\n".join(add) + "\n")
        print(f"undefined_syms.ld: +{len(add)} folded symbol(s)")
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
