#!/home/tsranso/Code/pokestadium/.venv/bin/python3
"""accessmap: what memory did the ORIGINAL code actually touch?  (ground truth for struct types)

USAGE (repo root; repo venv python)
  .venv/bin/python3 matching_notes/accessmap.py FUNC                     # every base, target asm
  .venv/bin/python3 matching_notes/accessmap.py FUNC --base arg0         # one base only
  .venv/bin/python3 matching_notes/accessmap.py FUNC --struct NAME [--base B] [--at OFF]
        overlay the declared layout of struct/typedef NAME on base B (default: the base with the
        most accesses); the struct starts at B+OFF (default 0); --array overlays NAME[] instead
  .venv/bin/python3 matching_notes/accessmap.py FUNC --draft             # + compile the draft and compare
  .venv/bin/python3 matching_notes/accessmap.py FUNC --draft-s FILE.s    # draft asm given as splat/.s text
  .venv/bin/python3 matching_notes/accessmap.py FUNC --draft-o FILE.o    # draft from an existing object
  options: --src FILE.c (C file for --struct/--draft; default: found by grep),
           --all-addrs (every instruction address, not just the first 4),
           --obj FILE.o (analyse FUNC from this object instead of the target asm).

INPUT
  Target = asm/us/nonmatchings/**/FUNC.s (splat). A MATCHED function has no .s there; then the
  function is disassembled from expected/build/src/<file>.o (falls back to build/src/<file>.o).
  --draft copies the function's C file to scratch/accessmap_dev/draft/, flips the `#ifdef
  NON_MATCHING` guarding FUNC to `#if 1`, compiles it with the exact `make -n -B` IDO command into
  scratch/accessmap_dev/draft/ (src/, build/ are never touched) and analyses the result.

WHAT IT TRACKS (one linear pass, plus a second pass that knows the loop headers)
  Bases: argN (a0-a3 = arg0-3, caller-frame stack words = arg4.. in 4-byte slots), globals
  (lui/addiu %hi/%lo(D_x), %lo(D_x)(rY), D_x+off), pointers loaded from memory ("[arg0+0x10]" =
  the word loaded from arg0+0x10), return values ("ret f(...)"), spilled/reloaded registers.
  Values are linear forms: base + const + sum(coeff*var). `sll/subu/addu/mult` build index
  scales (sll 4; subu; sll 2 = *0x3C), sign-extension pairs cancel, `addiu r,r,imm` inside a loop
  is a pointer walk. A coefficient shows as "+0x3Cn" = array element, stride 0x3C.

OUTPUT
  One table per base, sorted by offset. Columns: offset (+ stride terms), observed type
  (s8/u8/s16/u16/w32/ptr/f32/f64; plain 8/16/32 = stores only, signedness unknown), R/W,
  instruction addresses, written values ("=arg2", "=0x3F800000(1f)", "=[arg0+0x2].h") and notes
  ("&0xff@addr" = the loaded value was masked right after: the field is probably narrower or
  unsigned; "sext8@addr" = sign-extended: narrower and signed). Flags:
    MIXED-WIDTH  two widths at the same offset (union, or a wrong field type)
    MIXED-SIGN   lb and lbu (lh and lhu) at the same offset
    OVERLAP      an access starts inside another one at a different offset
    -- gap --    unaccessed bytes between two accessed fields (only shown for gaps < 0x40)
  --struct adds the declared layout next to the observed accesses for one base and flags
    NO-FIELD (hole / past end), INSIDE (access starts within a field), PAD-FIELD (access into a
    char/pad filler array), WIDTH, SIGN (lbu on s8 etc), KIND (float vs int), and a consistent
    shift: "FIELDS APPEAR SHIFTED BY k BYTES" when moving every declared offset by k fits clearly
    more accesses than k=0 (or: the struct starts k bytes into the base -> rerun with --at).
  --draft prints the draft's tables and a TARGET vs DRAFT comparison per base: accesses only in
    one side, width/sign differences, and a store-provenance check: the same value (e.g. arg2)
    stored at different offsets in target and draft -> "DRAFT STORES SHIFTED BY k BYTES".

LIMITS
  No real data-flow merging at labels (state just flows through in address order), no jump
  tables, no double-word register pairs, args assumed 4-byte words (a double arg shifts the
  numbering). Treat a missing access as "not seen", not as proof.
"""
import argparse
import collections
import glob
import os
import re
import shlex
import shutil
import struct as pystruct
import subprocess
import sys

REPO = os.path.abspath(os.path.join(os.path.dirname(os.path.abspath(__file__)), ".."))
PY = os.path.join(REPO, ".venv", "bin", "python3")
OBJDUMP = shutil.which("mips-linux-gnu-objdump") or os.path.expanduser("~/local/bin/mips-linux-gnu-objdump")
ENV = dict(os.environ)
ENV["PATH"] = ":".join([os.path.join(REPO, ".venv/bin"), os.path.expanduser("~/local/bin"),
                        "/usr/local/bin", "/usr/bin", "/bin", ENV.get("PATH", "")])
DRAFT_DIR = os.path.join(REPO, "scratch", "accessmap_dev", "draft")

# --------------------------------------------------------------------------------------
# Instruction input (splat .s or objdump of an .o) -> [Insn]
# --------------------------------------------------------------------------------------

GPRS = (["zero", "at", "v0", "v1", "a0", "a1", "a2", "a3"] + ["t%d" % i for i in range(10)]
        + ["s%d" % i for i in range(8)] + ["k0", "k1", "gp", "sp", "fp", "ra"])
GPRSET = set(GPRS)
FPR_ALIAS = {}
for _i, _n in enumerate(["fv0", "fv1", "ft0", "ft1", "ft2", "ft3", "fa0", "fa1", "ft4", "ft5",
                         "fs0", "fs1", "fs2", "fs3", "fs4", "fs5"]):
    FPR_ALIAS[_n] = "f%d" % (2 * _i)
    FPR_ALIAS[_n + "f"] = "f%d" % (2 * _i + 1)


def creg(r):
    r = r.strip().lstrip("$")
    if r == "s8":
        return "fp"
    if re.fullmatch(r"\d+", r):  # numeric GPR
        return GPRS[int(r)] if int(r) < 32 and int(r) != 30 else ("fp" if r == "30" else r)
    return FPR_ALIAS.get(r, r)


def is_gpr(r):
    return r in GPRSET


def is_fpr(r):
    return bool(re.fullmatch(r"f\d+", r))


class Insn:
    __slots__ = ("addr", "mn", "ops")

    def __init__(self, addr, mn, ops):
        self.addr, self.mn, self.ops = addr, mn, ops

    def __repr__(self):
        return "%08X %s %s" % (self.addr, self.mn, self.ops)


# operand forms: ('r', name) ('i', int) ('hi', sym, amount) ('lo', sym, amount)
#                ('m', disp, reg) where disp is int or ('lo', sym, amount)
#                ('t', addr) branch target, ('f', name) call target

def split_ops(s):
    out, depth, cur = [], 0, []
    for ch in s:
        if ch == "(":
            depth += 1
        elif ch == ")":
            depth -= 1
        if ch == "," and depth == 0:
            out.append("".join(cur).strip())
            cur = []
        else:
            cur.append(ch)
    if "".join(cur).strip():
        out.append("".join(cur).strip())
    return out


def eval_const(s):
    s = s.strip()
    if not re.fullmatch(r"[0-9a-fA-FxX\s()+\-*/%<>&|~^]+", s):
        return None
    s = re.sub(r"(?<!/)/(?!/)", "//", s)  # C integer division
    try:
        return int(eval(s, {"__builtins__": {}}, {}))
    except Exception:
        return None


SYMOFF_RE = re.compile(r"^\s*([A-Za-z_.$][\w.$]*)\s*(?:([+-])\s*(0x[0-9A-Fa-f]+|\d+))?\s*$")


def sym_split(s):
    m = SYMOFF_RE.match(s)
    if not m:
        return s.strip(), 0
    add = int(m.group(3), 0) if m.group(3) else 0
    return m.group(1), (-add if m.group(2) == "-" else add)


LIKELY = {"beql", "bnel", "beqzl", "bnezl", "blezl", "bgtzl", "bltzl", "bgezl", "bc1tl", "bc1fl"}
BRANCHES = {"b", "beq", "bne", "beql", "bnel", "beqz", "bnez", "beqzl", "bnezl", "blez", "bgtz",
            "bltz", "bgez", "blezl", "bgtzl", "bltzl", "bgezl", "bc1t", "bc1f", "bc1tl", "bc1fl",
            "bltzal", "bgezal", "bal", "j"}


def parse_operand_splat(op, labels):
    op = op.strip()
    m = re.match(r"^%(hi|lo)\((.*)\)\((\$\w+)\)$", op) or re.match(r"^%(hi|lo)\((.*)\)()$", op)
    if m:
        sym, add = sym_split(m.group(2))
        if m.group(1) == "hi":
            return ("hi", sym, 0)
        lo = ("lo", sym, add)
        return ("m", lo, creg(m.group(3))) if m.group(3) else lo
    m = re.match(r"^(.*)\((\$?\w+)\)$", op)
    if m and m.group(1).strip() and eval_const(m.group(1)) is not None:
        return ("m", eval_const(m.group(1)), creg(m.group(2)))
    if m and not m.group(1).strip():
        return ("m", 0, creg(m.group(2)))
    if op.startswith("$"):
        return ("r", creg(op))
    if op.startswith(".L"):
        return ("t", labels.get(op, int(op[2:], 16) if re.fullmatch(r"\.L[0-9A-Fa-f]+", op) else -1))
    v = eval_const(op)
    if v is not None:
        return ("i", v)
    return ("f", op)


S_INSN_RE = re.compile(r"^\s*/\*\s*([0-9A-Fa-f]+)\s+([0-9A-Fa-f]+)\s+([0-9A-Fa-f]+)\s*\*/\s+(\S+)\s*(.*)$")


def parse_splat(path, func):
    insns, name, in_text = [], None, True
    raw = []
    for line in open(path, encoding="utf-8", errors="replace"):
        s = line.strip()
        if s.startswith(".section"):
            in_text = ".text" in s
            continue
        if s.startswith("glabel") and in_text:
            lab = s.split()[1] if len(s.split()) > 1 else None
            if name is None and (func is None or lab == func):
                name = lab
            elif name is not None and lab != name:
                break
            continue
        if not in_text or name is None:
            continue
        m = S_INSN_RE.match(line)
        if not m or m.group(4).startswith("."):
            continue
        raw.append((int(m.group(2), 16), m.group(4), m.group(5).split("#")[0].strip()))
    labels = {}
    for vram, mn, opstr in raw:
        ops = [parse_operand_splat(o, labels) for o in split_ops(opstr)]
        insns.append(Insn(vram, mn, ops))
    return insns


def objdump_func(obj, func):
    p = subprocess.run([OBJDUMP, "-d", "-r", "-z", "--disassemble=" + func, obj],
                       capture_output=True, text=True, env=ENV)
    return objdump_text(p.stdout)


def objdump_text(text):
    """`objdump -dr` text (default MIPS register names) -> [Insn]"""
    insns = []
    pending = []
    cur = None
    for line in text.splitlines():
        m = re.match(r"^\s*([0-9a-f]+):\s+(R_MIPS_\w+)\s+(\S+)", line)
        if m and cur is not None:
            cur[2].append((m.group(2), m.group(3)))
            continue
        m = re.match(r"^\s*([0-9a-f]+):\t[0-9a-f]{8} \t(\S+)(?:\t(.*))?$", line)
        if m:
            cur = [int(m.group(1), 16), m.group(2), [], m.group(3) or ""]
            pending.append(cur)
    for addr, mn, relocs, opstr in pending:
        ops = []
        for o in split_ops(opstr):
            o = o.strip()
            mm = re.match(r"^(-?\d+)\((\w+)\)$", o)
            if mm:
                ops.append(("m", int(mm.group(1)), creg(mm.group(2))))
                continue
            mm = re.match(r"^([0-9a-f]+) <([^>]+)>$", o)
            if mm:
                if mn in ("jal", "j") and not any(r[0] == "R_MIPS_26" for r in relocs) and mn == "jal":
                    ops.append(("f", mm.group(2)))
                else:
                    ops.append(("t", int(mm.group(1), 16)))
                continue
            if re.fullmatch(r"\$?(f\d+|[a-z]\w*)", o) and (creg(o) in GPRSET or is_fpr(creg(o))):
                ops.append(("r", creg(o)))
                continue
            v = eval_const(o)
            ops.append(("i", v) if v is not None else ("f", o))
        for rtype, sym in relocs:
            sym = re.sub(r"^[^:()]*\.o:", "", sym)
            if rtype == "R_MIPS_26":
                ops[-1] = ("f", sym)
            elif rtype == "R_MIPS_HI16":
                imm = ops[-1][1] if ops[-1][0] == "i" else 0
                ops[-1] = ("hi", sym, (imm & 0xFFFF) << 16)
            elif rtype == "R_MIPS_LO16":
                last = ops[-1]
                if last[0] == "m":
                    d = last[1] if isinstance(last[1], int) else 0
                    ops[-1] = ("m", ("lo", sym, d), last[2])
                else:
                    imm = last[1] if last[0] == "i" else 0
                    imm = imm - 0x10000 if imm >= 0x8000 else imm
                    ops[-1] = ("lo", sym, imm)
        insns.append(Insn(addr, mn, ops))
    return insns


# --------------------------------------------------------------------------------------
# Symbolic values
# --------------------------------------------------------------------------------------

KIND_RANK = {"sym": 0, "sp": 0, "arg": 1, "ret": 2, "ptrload": 3, "load": 4, "walk": 9, "expr": 8, "clob": 8}


class V:
    """Linear form: off + sum(coeff * var).  hi: produced by lui %hi (a %lo is still to come)."""
    __slots__ = ("off", "terms", "hi", "desc", "conv")

    def __init__(self, off=0, terms=None, hi=False, desc=None, conv=""):
        self.off = off
        self.terms = dict(terms or {})
        self.hi = hi
        self.desc = desc
        self.conv = conv

    def const(self):
        return not self.terms

    def copy(self):
        return V(self.off, self.terms, self.hi, self.desc, self.conv)


class Analyzer:
    def __init__(self, insns, name):
        self.insns = insns
        self.name = name
        self.var_kind = {}
        self.accesses = []
        self.notes = collections.defaultdict(list)  # access index -> notes
        self.load_of = {}  # var -> access index
        self.ptr_vars = set()
        self.frame = 0
        self.nfresh = 0
        self.loops = []  # (start, end)
        self.walks = {}  # (loop_start, reg) -> (var, imm)
        self.walk_info = {}  # walk var -> (offset at the loop head, stride)

    # -- helpers --
    def var(self, name, kind):
        if name not in self.var_kind:
            self.var_kind[name] = kind
        return V(0, {name: 1}, desc=name)

    def fresh(self, addr, kind="expr", label=None):
        name = label or ("t@%X" % addr)
        if name in self.var_kind and label is None:
            pass
        self.var_kind.setdefault(name, kind)
        return V(0, {name: 1}, desc=name)

    def root_of(self, v):
        """-> (root, off, strides[sorted coeffs]) for an address value."""
        cands = [(KIND_RANK.get(self.var_kind.get(n, "expr"), 8), n) for n, c in v.terms.items() if c == 1]
        if not cands:
            if not v.terms:
                return ("abs", v.off, ())
            cands = [(9, sorted(v.terms)[0])]
        cands.sort()
        root = cands[0][1]
        strides = tuple(sorted(abs(c) for n, c in v.terms.items() if n != root and c != 0))
        if v.terms[root] != 1:
            strides = tuple(sorted(strides + (abs(v.terms[root]),)))
        return (root, v.off, strides)

    def vdesc(self, v):
        if v is None:
            return "?"
        if v.desc and v.terms == {v.desc: 1} and v.off == 0:
            return v.conv + v.desc
        if not v.terms:
            if v.desc and (v.desc.endswith("f") and v.desc[0] in "-0123456789"):
                return v.conv + v.desc
            x = v.off & 0xFFFFFFFF
            if x & 0xFFFF == 0 and (0x3000 <= x >> 16 < 0x5000 or 0xB000 <= x >> 16 < 0xD000):
                return v.conv + "0x%X(%s)" % (x, fmt_float(x))
            return v.conv + hexs(v.off)
        if len(v.terms) == 1 and v.desc and v.off == 0:
            return v.conv + v.desc
        r, off, strides = self.root_of(v)
        return v.conv + adesc(r, off, strides)

    # -- main --
    def run(self):
        for k, ins in enumerate(self.insns):
            if ins.mn in BRANCHES and ins.ops and ins.ops[-1][0] == "t":
                tgt = ins.ops[-1][1]
                if tgt <= ins.addr:
                    self.loops.append((tgt, ins.addr + 4))
        self.passno = 1
        self._scan()
        self.passno = 2
        self.accesses = []
        self.notes = collections.defaultdict(list)
        self.load_of = {}
        self.ptr_vars = set()
        self._scan()
        return self

    def in_loop(self, addr):
        return [lp for lp in self.loops if lp[0] <= addr < lp[1]]

    def walk_loop(self, ins, reg):
        """The innermost loop in which `addiu reg, reg, imm` is the only write to reg (a pointer /
        counter walk carried around the back edge), or None."""
        for lp in sorted(self.in_loop(ins.addr), key=lambda x: x[1] - x[0]):
            writers = [x for x in self.insns if lp[0] <= x.addr < lp[1] and self.writes(x) == reg]
            # every write in the loop is the same `addiu reg, reg, imm` (IDO duplicates the
            # increment into branch-likely delay slots)
            if ins in writers and all(x.mn == ins.mn and x.ops == ins.ops for x in writers):
                return lp
        return None

    def writes(self, x):
        if not x.ops or x.mn in self.STORES or x.mn in BRANCHES or x.mn.startswith("c.") or \
                x.mn in ("jr", "div", "divu", "mult", "multu", "ctc1", "mtc1", "teq"):
            return "f%s" % x.ops[1][1] if x.mn == "mtc1" else None
        return x.ops[0][1] if x.ops[0][0] == "r" else None

    def _scan(self):
        G = {}
        F = {}
        self.G, self.F = G, F
        for i, r in enumerate(["a0", "a1", "a2", "a3"]):
            G[r] = self.var("arg%d" % i, "arg")
        G["sp"] = self.var("sp", "sp")
        G["zero"] = V(0)
        F["f12"] = V(0, {"farg0": 1}, desc="f12@entry")
        F["f14"] = V(0, {"farg1": 1}, desc="f14@entry")
        self.slots = {}
        self.hilo = None
        pending_call = None
        loop_starts = {lp[0] for lp in self.loops}
        joins = collections.defaultdict(list)  # forward-branch target -> register states
        pending_branch = None
        likely_saved = None
        dead = False
        for k, ins in enumerate(self.insns):
            if ins.addr in joins:
                states = joins.pop(ins.addr) + ([] if dead else [(dict(G), dict(F))])
                self.merge(states, ins.addr)
                dead = False
            if self.passno == 2 and ins.addr in loop_starts:
                for (ls, reg), (wv, imm) in self.walks.items():
                    if ls == ins.addr and reg in G and wv not in G[reg].terms and G[reg].terms:
                        nv = G[reg].copy()
                        nv.terms[wv] = imm
                        G[reg] = nv
            self.step(ins)
            if pending_call is not None:
                self.clobber(pending_call)
                pending_call = None
            if pending_branch is not None:  # state after the delay slot = state on the taken path
                tgt, uncond = pending_branch
                if tgt is not None and tgt > pending_addr:
                    joins[tgt].append((dict(G), dict(F)))
                if uncond:
                    dead = True
                if likely_saved is not None:  # branch-likely: the delay slot only ran on the taken path
                    G.clear()
                    G.update(likely_saved[0])
                    F.clear()
                    F.update(likely_saved[1])
                    likely_saved = None
                pending_branch = None
            if ins.mn in ("jal", "jalr", "bal", "bgezal", "bltzal"):
                pending_call = ins
            elif ins.mn in BRANCHES or ins.mn == "jr":
                tgt = ins.ops[-1][1] if ins.ops and ins.ops[-1][0] == "t" else None
                uncond = ins.mn in ("b", "j", "jr") or (ins.mn == "beq" and ins.ops[0] == ins.ops[1])
                pending_branch = (tgt, uncond)
                pending_addr = ins.addr
                if ins.mn in LIKELY:
                    likely_saved = (dict(G), dict(F))

    def merge(self, states, addr):
        """Join point: keep a register only if every incoming path agrees on it."""
        if not states:
            return
        G, F = self.G, self.F
        for regs, idx in ((G, 0), (F, 1)):
            keys = set()
            for st in states:
                keys |= set(st[idx])
            new = {}
            for r in keys:
                vals = [st[idx].get(r) for st in states]
                v0 = vals[0]
                if all(v is not None and v.off == v0.off and v.terms == v0.terms for v in vals):
                    new[r] = v0
                elif r in ("sp", "zero"):
                    new[r] = v0
                else:
                    name = "phi@%X:%s" % (addr, r)
                    self.var_kind.setdefault(name, "expr")
                    new[r] = V(0, {name: 1}, desc=name)
            regs.clear()
            regs.update(new)

    def clobber(self, ins):
        G, F = self.G, self.F
        fname = ins.ops[-1][1] if ins.ops and ins.ops[-1][0] == "f" else "fnptr"
        a0 = self.vdesc(G.get("a0")) if fname != "fnptr" else ""
        for r in ["at", "v0", "v1", "a0", "a1", "a2", "a3"] + ["t%d" % i for i in range(10)] + ["ra"]:
            G[r] = self.fresh(ins.addr, "clob", "clob@%X" % ins.addr)
        for i in range(0, 20):
            F["f%d" % i] = V(0, {"fclob@%X" % ins.addr: 1}, desc="fclob")
        label = "ret %s(%s)" % (fname, a0 if len(a0) < 40 else "..")
        G["v0"] = self.var(label, "ret")
        G["v0"].desc = label
        F["f0"] = V(0, {"fret@%X" % ins.addr: 1}, desc="ret %s()" % fname)

    def gget(self, op):
        if op[0] == "r":
            v = self.G.get(op[1])
            if v is None:
                v = self.fresh(0, "expr", "init_" + op[1])
                self.G[op[1]] = v
            return v
        if op[0] == "i":
            return V(op[1])
        return None

    def fget(self, r):
        v = self.F.get(r)
        if v is None:
            v = V(0, {"finit_" + r: 1}, desc="finit_" + r)
        return v

    def gset(self, r, v):
        if r != "zero" and v is not None:
            self.G[r] = v

    def address(self, mop):
        """('m', disp, reg) -> V of the effective address"""
        disp, reg = mop[1], mop[2]
        base = self.gget(("r", reg)).copy()
        if isinstance(disp, tuple):  # ('lo', sym, amount)
            _, sym, amt = disp
            if base.hi or sym in base.terms:
                if sym not in base.terms:
                    base.terms[sym] = 1
                    self.var_kind.setdefault(sym, "sym")
                base.off += amt
            else:
                self.var_kind.setdefault(sym, "sym")
                base.terms[sym] = base.terms.get(sym, 0) + 1
                base.off += amt
            base.hi = False
        else:
            base.off += disp
        return base

    def record(self, ins, addrv, width, signed, rw, value=None, dest_var=None, fp=False):
        root, off, strides = self.root_of(addrv)
        if root == "sp":
            # stack: track spills/reloads, caller-frame words are args
            return root, off
        for n in addrv.terms:  # pointer walk: fold the offset into the walker's first element
            if n in self.walk_info and n != root:
                off0, S = self.walk_info[n]
                off = off0 + (off - off0) % S
                break
        idx = len(self.accesses)
        self.accesses.append(dict(addr=ins.addr, root=root, off=off, strides=strides, width=width,
                                  signed=signed, rw=rw, mn=ins.mn, fp=fp,
                                  value=self.vdesc(value) if value is not None else None))
        self.ptr_vars.add(root)
        if dest_var:
            self.load_of[dest_var] = idx
        return root, off

    def stack_load(self, off, ins, fp):
        if off in self.slots:
            return self.slots[off].copy()
        if self.frame and off >= self.frame:
            n = (off - self.frame) // 4
            return self.var("arg%d" % n, "arg")
        return self.fresh(ins.addr, "load", "sp+%X@%X" % (off, ins.addr))

    LOADS = {"lb": (1, True), "lbu": (1, False), "lh": (2, True), "lhu": (2, False), "lw": (4, None),
             "lwl": (4, None), "lwr": (4, None), "ld": (8, None), "lwc1": (4, "f"), "ldc1": (8, "f"),
             "ll": (4, None)}
    STORES = {"sb": 1, "sh": 2, "sw": 4, "swl": 4, "swr": 4, "sd": 8, "swc1": 4, "sdc1": 8, "sc": 4}

    def step(self, ins):
        mn, ops = ins.mn, ins.ops
        G, F = self.G, self.F
        o = ops

        if mn in self.LOADS:
            width, sg = self.LOADS[mn]
            fp = sg == "f"
            dst = o[0][1]
            av = self.address(o[1])
            root, off = self.root_of(av)[:2]
            if root == "sp" and not av.terms.keys() - {"sp"}:
                val = self.stack_load(off, ins, fp)
                if fp:
                    F[dst] = val
                else:
                    self.gset(dst, val)
                return
            adr = adesc(*self.root_of(av))
            sz = {1: ".b", 2: ".h", 4: "", 8: ".d"}[width]
            vname = "[%s]%s" % (adr, sz)
            kind = "ptrload" if (width == 4 and not fp) else "load"
            nv = self.var(vname, kind)
            self.record(ins, av, width, None if fp else sg, "R", dest_var=vname, fp=fp)
            if fp:
                F[dst] = nv
            else:
                self.gset(dst, nv)
            return

        if mn in self.STORES:
            width = self.STORES[mn]
            fp = mn in ("swc1", "sdc1")
            src = o[0][1]
            val = self.fget(src) if fp else self.gget(o[0])
            av = self.address(o[1])
            root, off, strides = self.root_of(av)
            if root == "sp" and not av.terms.keys() - {"sp"}:
                if val is not None:
                    self.slots[off] = val.copy()
                return
            self.record(ins, av, width, None, "W", value=val, fp=fp)
            return

        if mn == "addiu" and o[0] == ("r", "sp") and o[1] == ("r", "sp"):
            if o[2][0] == "i" and o[2][1] < 0 and not self.frame:
                self.frame = -o[2][1]
            return

        if mn in ("addiu", "addi", "daddiu"):
            src = self.gget(o[1]).copy()
            if o[2][0] == "lo":
                _, sym, amt = o[2]
                if sym not in src.terms:
                    src.terms[sym] = 1
                    self.var_kind.setdefault(sym, "sym")
                src.off += amt
                src.hi = False
                src.desc = None
            else:
                imm = o[2][1]
                lp = self.walk_loop(ins, o[0][1])
                if o[0] == o[1] and src.terms and lp is not None:
                    wv = "walk@%X:%s" % (lp[0], o[0][1])
                    self.var_kind.setdefault(wv, "walk")
                    if self.passno == 1 and (lp[0], o[0][1]) not in self.walks:
                        self.walks[(lp[0], o[0][1])] = (wv, imm)
                        self.walk_info[wv] = (src.off, abs(imm))  # offset at the loop head
                    src.terms[wv] = imm
                src.off += imm
                src.desc = None
            self.gset(o[0][1], src)
            return

        if mn in ("move", "or", "addu", "add", "daddu") and len(o) == 3 and o[2] == ("r", "zero"):
            self.gset(o[0][1], self.gget(o[1]).copy())
            return
        if mn in ("move",):
            self.gset(o[0][1], self.gget(o[1]).copy())
            return
        if mn in ("or", "addu") and len(o) == 3 and o[1] == ("r", "zero"):
            self.gset(o[0][1], self.gget(o[2]).copy())
            return

        if mn in ("addu", "add", "subu", "sub", "daddu"):
            a, b = self.gget(o[1]), self.gget(o[2])
            s = -1 if mn.startswith("sub") else 1
            nv = V(a.off + s * b.off, dict(a.terms), hi=a.hi or b.hi)
            for n, c in b.terms.items():
                nv.terms[n] = nv.terms.get(n, 0) + s * c
                if nv.terms[n] == 0:
                    del nv.terms[n]
            self.gset(o[0][1], nv)
            return

        if mn == "lui":
            if o[1][0] == "hi":
                _, sym, amt = o[1]
                self.var_kind.setdefault(sym, "sym")
                self.gset(o[0][1], V(amt, {sym: 1}, hi=True))
            else:
                self.gset(o[0][1], V((o[1][1] << 16) & 0xFFFFFFFF))
            return
        if mn == "li":
            self.gset(o[0][1], V(o[1][1] & 0xFFFFFFFF if o[1][0] == "i" else 0))
            return
        if mn in ("ori", "xori") and o[2][0] == "i":
            a = self.gget(o[1])
            if a.const():
                self.gset(o[0][1], V((a.off | o[2][1]) if mn == "ori" else (a.off ^ o[2][1])))
            else:
                self.gset(o[0][1], self.fresh(ins.addr))
            return
        if mn == "andi":
            a = self.gget(o[1])
            imm = o[2][1] if o[2][0] == "i" else 0
            if a.const():
                self.gset(o[0][1], V(a.off & imm))
                return
            lv = self.single_load(a)
            if lv is not None and imm in (0xFF, 0xFFFF):
                self.notes[self.load_of[lv]].append("&0x%X@%X" % (imm, ins.addr))
            nv = self.fresh(ins.addr)
            nv.desc = "%s&0x%X" % (self.vdesc(a), imm)
            self.gset(o[0][1], nv)
            return
        if mn in ("sll", "dsll") and o[2][0] == "i":
            a = self.gget(o[1])
            sh = o[2][1]
            nv = V(a.off << sh, {n: c << sh for n, c in a.terms.items()}, desc=None, conv=a.conv)
            nv.desc = a.desc if a.desc and a.terms == {a.desc: 1} else None
            self.gset(o[0][1], nv)
            return
        if mn in ("sra", "srl") and o[2][0] == "i":
            a = self.gget(o[1])
            sh = o[2][1]
            d = 1 << sh
            if a.terms and all(c % d == 0 for c in a.terms.values()) and a.off % d == 0:
                nv = V(a.off >> sh, {n: c // d for n, c in a.terms.items()})
                if mn == "sra" and sh in (16, 24):
                    lv = self.single_load(nv)
                    if lv is not None and self.accesses[self.load_of[lv]]["width"] * 8 > 32 - sh:
                        self.notes[self.load_of[lv]].append("sext%d@%X" % (32 - sh, ins.addr))
                    if mn == "sra" and nv.terms and len(nv.terms) == 1:
                        n = next(iter(nv.terms))
                        nv.desc = n if nv.terms[n] == 1 and nv.off == 0 else None
                if mn == "srl" and sh in (16, 24):
                    lv = self.single_load(nv)
                    if lv is not None and self.accesses[self.load_of[lv]]["width"] * 8 > 32 - sh:
                        self.notes[self.load_of[lv]].append("zext%d@%X" % (32 - sh, ins.addr))
                    if nv.terms and len(nv.terms) == 1:
                        n = next(iter(nv.terms))
                        nv.desc = n if nv.terms[n] == 1 and nv.off == 0 else None
                self.gset(o[0][1], nv)
            elif a.const():
                self.gset(o[0][1], V((a.off >> sh) if mn == "srl" else (sext32(a.off) >> sh)))
            else:
                nv = self.fresh(ins.addr)
                self.gset(o[0][1], nv)
            return
        if mn in ("mult", "multu"):
            a, b = self.gget(o[-2]), self.gget(o[-1])
            if a.const() and not b.const():
                a, b = b, a
            if b.const():
                self.hilo = V(a.off * b.off, {n: c * b.off for n, c in a.terms.items() if c * b.off})
            else:
                self.hilo = self.fresh(ins.addr)
            return
        if mn == "mflo":
            self.gset(o[0][1], self.hilo.copy() if self.hilo else self.fresh(ins.addr))
            return

        # FPU moves
        if mn == "mtc1":
            v = self.gget(o[0]).copy()
            if v.const():
                if v.off == 0:
                    v.desc = "0.0f"
                else:
                    v.desc = fmt_float(v.off)
                v.terms = {}
            F[o[1][1]] = v
            return
        if mn == "mfc1":
            self.gset(o[0][1], self.fget(o[1][1]).copy())
            return
        if mn in ("mov.s", "mov.d"):
            F[o[0][1]] = self.fget(o[1][1]).copy()
            return
        if mn.startswith("cvt.") or mn.startswith("trunc.") or mn.startswith("round.") or mn.startswith("floor.") or mn.startswith("ceil."):
            v = self.fget(o[1][1]).copy()
            v.conv = "(%s)" % mn + v.conv
            F[o[0][1]] = v
            return
        if mn in ("neg.s", "neg.d"):
            v = self.fget(o[1][1]).copy()
            v.conv = "-" + v.conv
            F[o[0][1]] = v
            return

        # generic writers
        if not o or mn in BRANCHES or mn.startswith("c.") or mn in ("jr", "div", "divu", "ctc1", "nop",
                                                                      "teq", "break", "syscall", "jal"):
            return
        if mn == "jalr":
            return
        if o[0][0] == "r":
            r = o[0][1]
            if is_fpr(r):
                F[r] = V(0, {"f@%X" % ins.addr: 1}, desc="f@%X" % ins.addr)
            elif is_gpr(r):
                self.gset(r, self.fresh(ins.addr))

    def single_load(self, v):
        if len(v.terms) == 1:
            n = next(iter(v.terms))
            if n in self.load_of:
                return n
        return None


def sext32(x):
    x &= 0xFFFFFFFF
    return x - (1 << 32) if x & 0x80000000 else x


def fmt_float(bits):
    try:
        f = pystruct.unpack(">f", pystruct.pack(">I", bits & 0xFFFFFFFF))[0]
        return "%gf" % f
    except Exception:
        return hexs(bits)


def hexs(v):
    return ("-0x%X" % -v) if v < 0 else ("0x%X" % v)


def strides_s(strides):
    return "".join(" +0x%Xn" % s for s in strides)


def adesc(root, off, strides):
    s = root
    if off:
        s += ("+" if off > 0 else "-") + "0x%X" % abs(off)
    return s + strides_s(strides).replace(" ", "")


# --------------------------------------------------------------------------------------
# Table output
# --------------------------------------------------------------------------------------

TYPE_OF = {"lb": "s8", "lbu": "u8", "lh": "s16", "lhu": "u16", "lw": "w32", "ll": "w32",
           "lwl": "w32?", "lwr": "w32?", "ld": "d64", "sb": "8", "sh": "16", "sw": "32", "sd": "d64",
           "swl": "32?", "swr": "32?", "lwc1": "f32", "swc1": "f32", "ldc1": "f64", "sdc1": "f64", "sc": "32"}


def acc_type(a):
    return TYPE_OF.get(a["mn"], a["mn"])


def group_rows(accs, an):
    rows = collections.OrderedDict()
    for i, a in sorted(enumerate(accs), key=lambda x: (x[1]["strides"], x[1]["off"], x[1]["addr"])):
        rows.setdefault((a["strides"], a["off"]), []).append((i, a))
    return rows


def summarize_types(items, ptrs, roots_used):
    types = []
    for i, a in items:
        t = acc_type(a)
        types.append(t)
    loads = {t for t in types if t[0] in "suwfd"}
    stores = {t for t in types if t[0].isdigit()}
    width_set = {a["width"] for _, a in items}
    out = set(loads)
    for st in stores:
        if not any(TYPE_W.get(l) == int(st.rstrip("?")) // 8 for l in loads):
            out.add(st)
    # w32 store and w32 load
    if "32" in out and ("w32" in out):
        out.discard("32")
    if any(a["rw"] == "R" and a["width"] == 4 and not a["fp"] and a.get("isptr") for _, a in items):
        out.discard("w32")
        out.add("ptr")
    return "/".join(sorted(out)), width_set


TYPE_W = {"s8": 1, "u8": 1, "s16": 2, "u16": 2, "w32": 4, "ptr": 4, "f32": 4, "f64": 8, "d64": 8, "w32?": 4}


def print_tables(an, title, only=None, show_stack=False, all_addrs=False, out=print):
    accs = an.accesses
    # mark pointer loads: any loaded word var used as a root
    used_roots = {a["root"] for a in accs}
    for i, a in enumerate(accs):
        a["isptr"] = False
    for vname, idx in an.load_of.items():
        if vname in used_roots:
            accs[idx]["isptr"] = True
    by_root = collections.OrderedDict()
    for a in accs:
        by_root.setdefault(a["root"], []).append(a)
    order = sorted(by_root, key=lambda r: (-len(by_root[r]), r))
    out("=" * 100)
    out("%s  (%d instructions, frame 0x%X, %d memory accesses, %d bases)"
        % (title, len(an.insns), an.frame, len(accs), len(by_root)))
    out("=" * 100)
    for root in order:
        if only and not base_match(root, only):
            continue
        print_table(an, root, by_root[root], all_addrs, out)
    neighbour_notes(an, by_root, out)


def base_match(root, sel):
    if root == sel:
        return True
    alias = {"a0": "arg0", "a1": "arg1", "a2": "arg2", "a3": "arg3"}
    return root == alias.get(sel, None)


def base_header(root, an):
    kind = an.var_kind.get(root, "?")
    extra = {"arg": "function argument", "sym": "global symbol", "ret": "return value",
             "ptrload": "pointer loaded from memory", "load": "value loaded from memory",
             "walk": "loop walker", "expr": "computed", "clob": "computed"}.get(kind, kind)
    m = re.fullmatch(r"arg(\d)", root)
    if m and int(m.group(1)) < 4:
        extra += " (a%s at entry)" % m.group(1)
    elif m:
        extra += " (stack word %s)" % m.group(1)
    return "%s   [%s]" % (root, extra)


def print_table(an, root, accs, all_addrs, out):
    out("")
    out("BASE %s   %d accesses" % (base_header(root, an), len(accs)))
    out("  %-16s %-12s %-3s %-30s %s" % ("offset", "type", "R/W", "insn addrs", "values written / notes / flags"))
    idx_of = {id(a): i for i, a in enumerate(an.accesses)}
    rows = group_rows(accs, an)
    prev = None  # (strides, end, off, width)
    for (strides, off), items in rows.items():
        tsum, wset = summarize_types(items, None, None)
        rw = ("R" if any(a["rw"] == "R" for _, a in items) else " ") + ("W" if any(a["rw"] == "W" for _, a in items) else " ")
        addrs = sorted({a["addr"] for _, a in items})
        ad = ",".join("%X" % x for x in (addrs if all_addrs else addrs[:4])) + ("" if all_addrs or len(addrs) <= 4 else ",+%d" % (len(addrs) - 4))
        vals = []
        for _, a in items:
            if a["rw"] == "W" and a["value"] and ("=" + a["value"]) not in vals:
                vals.append("=" + a["value"])
        notes = []
        for _, a in items:
            for n in an.notes.get(idx_of[id(a)], []):
                if n not in notes:
                    notes.append(n)
        flags = []
        if len(wset) > 1:
            flags.append("MIXED-WIDTH")
        sg = {a["signed"] for _, a in items if a["rw"] == "R" and a["signed"] is not None and not a["fp"]}
        if len(sg) > 1:
            flags.append("MIXED-SIGN")
        if any(a["fp"] for _, a in items) and any(not a["fp"] for _, a in items):
            flags.append("FP+INT")
        width = max(wset)
        if prev and prev[0] == strides:
            if off < prev[1]:
                flags.append("OVERLAP(0x%X..0x%X)" % (prev[2], prev[1]))
            elif off > prev[1] and off - prev[1] < 0x40:
                out("  %-16s %s" % ("", "-- gap 0x%X --" % (off - prev[1])))
        if prev is None or prev[0] != strides or off + width > prev[1]:
            prev = (strides, max(off + width, prev[1] if prev and prev[0] == strides else 0), off, width)
        offs = hexs(off) + strides_s(strides)
        tail = " ".join(vals[:6] + (["(+%d more)" % (len(vals) - 6)] if len(vals) > 6 else []) + notes + flags)
        out("  %-16s %-12s %-3s %-30s %s" % (offs, tsum, rw, ad, tail))


def neighbour_notes(an, by_root, out):
    syms = []
    for r, accs in by_root.items():
        m = re.fullmatch(r"D_([0-9A-Fa-f]{8})", r)
        if m:
            syms.append((int(m.group(1), 16), r, accs))
    syms.sort()
    lines = []
    for i in range(len(syms)):
        for j in range(i + 1, len(syms)):
            a_addr, a, aa = syms[i]
            b_addr, b, ba = syms[j]
            d = b_addr - a_addr
            if d <= 0 or d > 0x100:
                continue
            sa = {s for x in aa for s in x["strides"]}
            sb = {s for x in ba for s in x["strides"]}
            common = sorted(s for s in sa & sb if s > d)
            if common:
                lines.append("  %s = %s+0x%X and both are indexed with stride 0x%X: probably ONE array of 0x%X-byte"
                             " structs (%s[i] is field +0x%X of %s[i])" % (b, a, d, common[0], common[0], b, d, a))
            else:
                maxa = max((x["off"] + x["width"] for x in aa), default=0)
                if maxa > d:
                    lines.append("  %s is accessed up to %s+0x%X, past %s (= %s+0x%X): %s may be part of %s"
                                 % (a, a, maxa, b, a, d, b, a))
    if lines:
        out("")
        out("NEIGHBOURING GLOBALS")
        for l in lines:
            out(l)


# --------------------------------------------------------------------------------------
# Struct layout (cpp + a small tolerant declaration parser)
# --------------------------------------------------------------------------------------

CPP_FLAGS = ["-undef", "-D__sgi", "-DVERSION_US", "-DTARGET_N64", "-D_LANGUAGE_C", "-DF3DEX_GBI_2",
             "-D_MIPS_SZLONG=32", "-ffreestanding", "-nostdinc", "-Iinclude/ido", "-Iinclude", "-Ibuild",
             "-Iinclude/PR", "-Isrc", "-Isrc/libnaudio", "-I.", "-DM2C", "-DNON_MATCHING",
             "-Ilib/ultralib/include", "-Ilib/ultralib/include/PR", "-Ilib/ultralib/include/ido"]


class T:
    def __init__(self, kind, size, align, name="", signed=None, fields=None, elem=None, count=None):
        self.kind, self.size, self.align, self.name = kind, size, align, name
        self.signed, self.fields, self.elem, self.count = signed, fields, elem, count

    def tname(self):
        if self.kind == "array":
            return "%s[%s]" % (self.elem.tname(), self.count)
        if self.kind == "ptr":
            return (self.elem.tname() if self.elem else "void") + "*"
        return self.name or self.kind


def prim(spec):
    words = [w for w in spec if w not in ("const", "volatile", "register", "static", "extern", "inline", "auto")]
    s = " ".join(words)
    uns = "unsigned" in words
    sig = "signed" in words
    core = [w for w in words if w not in ("unsigned", "signed")]
    c = " ".join(core)
    if c == "char":
        return T("int", 1, 1, ("s8" if sig else "u8") if (uns or sig) else "char(u)", signed=sig)
    if c in ("short", "short int"):
        return T("int", 2, 2, "u16" if uns else "s16", signed=not uns)
    if c in ("long long", "long long int"):
        return T("int", 8, 8, "u64" if uns else "s64", signed=not uns)
    if c in ("", "int", "long", "long int"):
        return T("int", 4, 4, "u32" if uns else "s32", signed=not uns)
    if c == "float":
        return T("float", 4, 4, "f32")
    if c in ("double", "long double"):
        return T("float", 8, 8, "f64")
    if c == "void":
        return T("void", 0, 1, "void")
    return None


TOK_RE = re.compile(r"\s*(?:([A-Za-z_]\w*)|(0[xX][0-9A-Fa-f]+[uUlL]*|\d+[uUlL]*)|(\"(?:\\.|[^\"])*\"|'(?:\\.|[^'])*')|(\.\.\.|->|<<|>>|[{}()\[\];,*:=+\-/%&|^~<>?!.#]))")


def tokenize(text):
    toks = []
    pos = 0
    n = len(text)
    while pos < n:
        m = TOK_RE.match(text, pos)
        if not m:
            pos += 1
            continue
        pos = m.end()
        if m.group(1):
            toks.append(m.group(1))
        elif m.group(2):
            toks.append(re.sub(r"[uUlL]+$", "", m.group(2)))
        elif m.group(3):
            toks.append('""')
        elif m.group(4):
            toks.append(m.group(4))
    return toks


SPEC_WORDS = {"const", "volatile", "register", "static", "extern", "inline", "auto", "unsigned", "signed",
              "char", "short", "int", "long", "float", "double", "void", "__inline", "__volatile__"}


class CParser:
    def __init__(self, text):
        self.toks = tokenize(text)
        self.typedefs = {}
        self.tags = {}
        self.anon = 0

    def run(self):
        t = self.toks
        i = 0
        n = len(t)
        while i < n:
            tok = t[i]
            if tok == "typedef":
                i = self.parse_decl(i + 1, typedef=True)
            elif tok in ("struct", "union", "enum"):
                i = self.parse_decl(i, typedef=False)
            elif tok == "{":
                i = self.skip_block(i)
            elif tok == "__attribute__":
                i = self.skip_parens(i + 1)
            else:
                i += 1
        return self

    def skip_block(self, i):
        depth = 0
        while i < len(self.toks):
            if self.toks[i] == "{":
                depth += 1
            elif self.toks[i] == "}":
                depth -= 1
                if depth == 0:
                    return i + 1
            i += 1
        return i

    def skip_parens(self, i):
        if i < len(self.toks) and self.toks[i] == "(":
            depth = 0
            while i < len(self.toks):
                if self.toks[i] == "(":
                    depth += 1
                elif self.toks[i] == ")":
                    depth -= 1
                    if depth == 0:
                        return i + 1
                i += 1
        return i

    def parse_specs(self, i):
        """-> (base T or None, i)"""
        t = self.toks
        words = []
        base = None
        while i < len(t):
            tok = t[i]
            if tok in SPEC_WORDS:
                words.append(tok)
                i += 1
            elif tok == "__attribute__":
                i = self.skip_parens(i + 1)
            elif tok in ("struct", "union"):
                base, i = self.parse_su(i)
            elif tok == "enum":
                i += 1
                if i < len(t) and re.match(r"[A-Za-z_]", t[i]) and t[i] != "{":
                    i += 1
                if i < len(t) and t[i] == "{":
                    i = self.skip_block(i)
                base = T("int", 4, 4, "enum", signed=True)
            elif base is None and not words and tok in self.typedefs:
                base = self.typedefs[tok]
                i += 1
            elif base is None and tok in self.typedefs and all(w in ("const", "volatile", "static", "extern", "register") for w in words):
                base = self.typedefs[tok]
                i += 1
            else:
                break
        if base is None:
            if not words:
                return None, i
            base = prim(words)
        return base, i

    def parse_su(self, i):
        t = self.toks
        kw = t[i]
        i += 1
        tag = None
        while i < len(t) and t[i] == "__attribute__":
            i = self.skip_parens(i + 1)
        if i < len(t) and re.match(r"[A-Za-z_]\w*$", t[i]):
            tag = t[i]
            i += 1
        key = kw + " " + (tag or "")
        if i < len(t) and t[i] == "{":
            fields, i = self.parse_members(i + 1)
            ty = layout(kw, tag or "<anon>", fields)
            if tag:
                old = self.tags.get(key)
                if old is not None and old.kind == "incomplete":
                    old.__dict__.update(ty.__dict__)
                    ty = old
                self.tags[key] = ty
            return ty, i
        if key in self.tags:
            return self.tags[key], i
        ty = T("incomplete", 0, 1, key)
        self.tags[key] = ty
        return ty, i

    def parse_members(self, i):
        """after '{' -> ([(name, T, bits)], i after '}')"""
        t = self.toks
        fields = []
        while i < len(t) and t[i] != "}":
            if t[i] == ";":
                i += 1
                continue
            base, j = self.parse_specs(i)
            if base is None:
                # unknown type name: skip declaration
                while j < len(t) and t[j] not in (";", "}"):
                    j += 1
                i = j
                continue
            i = j
            if t[i] == ";":  # anonymous struct/union member
                fields.append(("", base, None))
                i += 1
                continue
            while True:
                name, build, i = self.parse_declarator(i)
                bits = None
                if i < len(t) and t[i] == ":":
                    k = i + 1
                    while t[k] not in (",", ";", "}"):
                        k += 1
                    bits = eval_const(" ".join(t[i + 1:k])) or 0
                    i = k
                fields.append((name, build(base), bits))
                if i < len(t) and t[i] == ",":
                    i += 1
                    continue
                break
            if i < len(t) and t[i] == ";":
                i += 1
            # tolerate a missing ';' before '}'
        return fields, i + 1

    def parse_declarator(self, i):
        t = self.toks
        nptr = 0
        while i < len(t) and t[i] in ("*", "const", "volatile"):
            if t[i] == "*":
                nptr += 1
            i += 1
        name = ""
        inner = None
        if i < len(t) and t[i] == "(" and i + 1 < len(t) and t[i + 1] in ("*", "(") :
            name, inner, i = self.parse_declarator(i + 1)
            if i < len(t) and t[i] == ")":
                i += 1
        elif i < len(t) and re.match(r"[A-Za-z_]\w*$", t[i]) and t[i] not in SPEC_WORDS:
            name = t[i]
            i += 1
        suffixes = []
        while i < len(t) and t[i] in ("[", "("):
            if t[i] == "[":
                k = i + 1
                depth = 1
                while depth:
                    if t[k] == "[":
                        depth += 1
                    elif t[k] == "]":
                        depth -= 1
                    k += 1
                expr = " ".join(t[i + 1:k - 1])
                suffixes.append(("arr", self.eval_size(expr)))
                i = k
            else:
                i = self.skip_parens(i)
                suffixes.append(("func", None))

        def build(base, nptr=nptr, suffixes=suffixes, inner=inner):
            ty = base
            for _ in range(nptr):
                ty = T("ptr", 4, 4, elem=ty)
            for kind, n in reversed(suffixes):
                if kind == "arr":
                    ty = T("array", ty.size * (n or 0), ty.align, elem=ty, count=n)
                else:
                    ty = T("func", 0, 1, "func")
            if inner is not None:
                ty = inner(ty)
            return ty
        return name, build, i

    def eval_size(self, expr):
        if not expr.strip():
            return 0
        expr = re.sub(r"sizeof \( ([A-Za-z_]\w*) \)", lambda m: str(self.typedefs[m.group(1)].size)
                      if m.group(1) in self.typedefs else "0", expr)
        v = eval_const(expr.replace(" ", ""))
        return v if v is not None else 0

    def parse_decl(self, i, typedef):
        t = self.toks
        base, i = self.parse_specs(i)
        if base is None:
            while i < len(t) and t[i] != ";":
                if t[i] == "{":
                    i = self.skip_block(i)
                    continue
                i += 1
            return i + 1
        while i < len(t) and t[i] not in (";",):
            if t[i] == "{":  # function body
                return self.skip_block(i)
            name, build, i = self.parse_declarator(i)
            if typedef and name:
                if base.kind in ("struct", "union") and base.name == "<anon>":
                    base.name = name
                ty = build(base)
                self.typedefs[name] = ty
            if i < len(t) and t[i] == "=":
                depth = 0
                while i < len(t):
                    if t[i] in "({[":
                        depth += 1
                    elif t[i] in ")}]":
                        depth -= 1
                    elif t[i] in (",", ";") and depth == 0:
                        break
                    i += 1
            if i < len(t) and t[i] == ",":
                i += 1
                continue
            if i < len(t) and t[i] == "{":
                return self.skip_block(i)
            if i < len(t) and t[i] != ";":
                i += 1
        return i + 1


def layout(kw, name, fields):
    """o32 / IDO rules: natural alignment; bitfields fill a bit cursor and never straddle a unit
    of their declared type; a zero-width bitfield aligns the cursor."""
    out = []
    bitcur = 0  # struct cursor in bits
    align = 1
    size = 0
    for fname, ty, bits in fields:
        a = max(ty.align, 1)
        if kw == "union":
            out.append((0, fname, ty))
            size = max(size, ty.size)
            align = max(align, a)
            continue
        if bits is not None:
            unit = max(ty.size, 1) * 8
            if bits == 0:
                bitcur = (bitcur + unit - 1) // unit * unit
                continue
            if bitcur // unit != (bitcur + bits - 1) // unit:
                bitcur = (bitcur + unit - 1) // unit * unit
            bt = T("bitfield", ty.size, a, "%s:%d" % (ty.tname(), bits), signed=ty.signed)
            if fname:
                out.append((bitcur // unit * ty.size, fname, bt))
            bitcur += bits
            align = max(align, a)
            continue
        off = (bitcur + 7) // 8
        off = (off + a - 1) // a * a
        out.append((off, fname, ty))
        bitcur = (off + ty.size) * 8
        align = max(align, a)
    if kw != "union":
        size = (bitcur + 7) // 8
    size = (size + align - 1) // align * align
    return T(kw, size, align, name, fields=out)


def preprocess(cfile):
    rel = os.path.relpath(cfile, REPO)
    cmd = ["gcc", "-E", "-P"] + CPP_FLAGS + ["-I" + os.path.dirname(rel), rel]
    p = subprocess.run(cmd, cwd=REPO, capture_output=True, text=True, env=ENV)
    return p.stdout


def find_struct(cfile, name):
    text = preprocess(cfile)
    cp = CParser(text).run()
    ty = cp.typedefs.get(name) or cp.tags.get("struct " + name) or cp.tags.get("union " + name)
    while ty is not None and ty.kind == "ptr" and False:
        ty = ty.elem
    return ty, cp


PAD_RE = re.compile(r"^_?(pad|filler|unused)|pad", re.I)


def resolve(ty, off, strides, path=""):
    """-> dict(path, leaf T, inner offset, field start (relative to the top), issues) or None"""
    strides = list(strides)
    base_off = 0
    cur = ty
    seen = [("<self>", ty)]

    def fin(d):
        notes = []
        for s in strides:  # index strides no declared array consumed
            cont = [p for p, t in seen if t.size == s]
            if cont and cont[-1] == "<self>":
                notes.append("+0x%Xn: array of %s" % (s, ty.tname()))
                continue
            notes.append("+0x%Xn walks %s (size 0x%X)" % (s, cont[-1], s) if cont
                         else "+0x%Xn: no array/struct of that size on this path" % s)
        d["rest"] = notes
        return d
    while True:
        if cur.kind in ("struct", "union"):
            best = None
            for foff, fname, fty in cur.fields:
                if foff <= off < foff + max(fty.size, 1):
                    if best is None or (cur.kind == "union" and fty.size > best[2].size):
                        best = (foff, fname, fty)
                    if cur.kind == "struct":
                        break
            if best is None:
                return fin(dict(path=path or "<top>", leaf=None, inner=off, start=base_off + off,
                                why="past end" if off >= cur.size or off < 0 else "hole/padding"))
            foff, fname, fty = best
            path += ("." if path else "") + fname
            off -= foff
            base_off += foff
            cur = fty
            seen.append((path, cur))
        elif cur.kind == "array":
            esz = cur.elem.size or 1
            if esz in strides:
                strides.remove(esz)
                k = off // esz
                off = off % esz
                path += "[i]" if k == 0 else "[i%+d]" % k  # start stays element-[i]-relative
            else:
                k = off // esz
                if cur.count and (k >= cur.count or k < 0):
                    path += "[%d!]" % k
                else:
                    path += "[%d]" % k
                off -= k * esz
                base_off += k * esz
            fname = path.split(".")[-1].split("[")[0]
            if cur.elem.kind == "int" and cur.elem.size == 1 and (
                    PAD_RE.search(fname) or (cur.elem.name == "char(u)" and fname.startswith("unk"))):
                return fin(dict(path=path, leaf=cur.elem, inner=off, start=base_off, pad=True))
            cur = cur.elem
            seen.append((path, cur))
        else:
            return fin(dict(path=path, leaf=cur, inner=off, start=base_off))


def check(a, r):
    """-> list of issue strings for access a resolved to r"""
    if r is None:
        return ["NO-FIELD"]
    if r.get("leaf") is None:
        return ["NO-FIELD(%s)" % r.get("why", "")]
    issues = []
    leaf = r["leaf"]
    if r.get("pad"):
        issues.append("PAD-FIELD")
    if leaf.kind == "bitfield":  # IDO reads bitfields with any width inside the unit
        if r["inner"] + a["width"] > leaf.size or a["fp"]:
            issues.append("WIDTH(%d-byte access at +0x%X of bitfield unit %s)" % (a["width"], r["inner"], leaf.tname()))
        return issues
    if r["inner"] != 0:
        issues.append("INSIDE(+0x%X of %s %s)" % (r["inner"], leaf.tname(), r["path"]))
        return issues
    if leaf.kind in ("struct", "union", "incomplete", "void", "func"):
        issues.append("KIND(%s)" % leaf.tname())
        return issues
    if a["width"] != leaf.size:
        issues.append("WIDTH(%d-byte access, field is %s)" % (a["width"], leaf.tname()))
        return issues
    if a["fp"] and leaf.kind != "float":
        issues.append("KIND(float access to %s)" % leaf.tname())
    elif not a["fp"] and leaf.kind == "float":
        issues.append("KIND(int access to %s; a copy?)" % leaf.tname())
    if a["rw"] == "R" and a["signed"] is not None and leaf.kind == "int" and a["width"] < 4:
        if leaf.signed is not None and bool(a["signed"]) != bool(leaf.signed):
            issues.append("SIGN(%s on %s)" % (a["mn"], leaf.tname()))
    return issues


def ok_access(a, ty, off, strides):
    r = resolve(ty, off, strides)
    iss = check(a, r)
    return not [x for x in iss if not x.startswith("KIND(int access")]


def struct_report(an, ty, sname, base, at, out=print):
    accs = [a for a in an.accesses if a["root"] == base]
    out("")
    out("STRUCT OVERLAY: %s (size 0x%X, align %d) at %s+0x%X   [%d accesses]"
        % (sname, ty.size, ty.align, base, at, len(accs)))
    if not accs:
        out("  (no accesses through this base)")
        return
    arr = [a for a in accs if ty.size in a["strides"]]
    if arr and len(arr) < len(accs):
        out("  base is indexed with stride 0x%X == sizeof(%s): overlaying only those %d accesses"
            " (an array of %s; the other %d accesses are left out)" % (ty.size, sname, len(arr), sname, len(accs) - len(arr)))
        accs = arr
    leaves = flatten(ty)
    rows = {}
    nbad = 0
    for a in accs:
        rel = a["off"] - at
        r = resolve(ty, rel, a["strides"])
        iss = check(a, r)
        if r and r.get("leaf") is not None:
            key = r["start"] if r["inner"] == 0 else r["start"] + r["inner"]
        else:
            key = rel
        row = rows.setdefault((key, r["path"] if r else "?"), dict(accs=[], issues=[], r=r))
        row["accs"].append(a)
        for x in iss:
            if x not in row["issues"]:
                row["issues"].append(x)
    # declared leaves within the observed span (normalised offsets) + observed rows
    keys = sorted(rows)
    lo = min(k[0] for k in keys)
    hi = max(k[0] for k in keys)
    shown = set()
    merged = []
    for off, path, lty in leaves:
        if lo - 0x10 <= off <= hi + 0x10 or len(leaves) <= 40:
            merged.append((off, 0, path, lty))
    for k in keys:
        merged.append((k[0], 1, k[1], None))
    merged.sort(key=lambda x: (x[0], x[1]))
    out("  %-8s %-34s %-10s | %-14s %-3s %-22s %s" % ("offset", "declared field", "type", "observed", "R/W", "insns", "verdict"))
    used_paths = {k[1] for k in keys}
    for off, isobs, path, lty in merged:
        if not isobs:
            if norm_path(path) in {norm_path(p) for p in used_paths}:
                continue
            out("  %-8s %-34s %-10s | %s" % (hexs(off), path[:34], lty.tname()[:10], "-"))
            continue
        row = rows[(off, path)]
        r = row["r"]
        a0 = row["accs"]
        tset = [summarize_types([(0, a) for a in a0], None, None)[0]]
        rw =("R" if any(a["rw"] == "R" for a in a0) else " ") + ("W" if any(a["rw"] == "W" for a in a0) else " ")
        addrs = sorted({a["addr"] for a in a0})
        st = sorted({s for a in a0 for s in a["strides"]})
        decl_t = r["leaf"].tname() if r and r.get("leaf") is not None else "-"
        vals = []
        for a in a0:
            if a["rw"] == "W" and a["value"] and ("=" + a["value"]) not in vals:
                vals.append("=" + a["value"])
        verdict = " ".join(row["issues"]) if row["issues"] else "ok"
        if row["issues"]:
            nbad += 1
        rest = sorted({n for a in a0 for n in (resolve(ty, a["off"] - at, a["strides"]) or {}).get("rest", [])})
        if rest:
            verdict += " [" + "; ".join(rest) + "]"
        out("  %-8s %-34s %-10s | %-14s %-3s %-22s %s %s" % (
            hexs(off) + ("*" if st else ""), path[:34], decl_t[:10], "/".join(tset)[:14], rw,
            ",".join("%X" % x for x in addrs[:3]) + ("+" if len(addrs) > 3 else ""), verdict, " ".join(vals[:4])))
    out("  (* = indexed access; offset shown for element [i])")
    out("  -> %d of %d observed offsets disagree with the declaration" % (nbad, len(keys)))
    # shift detection
    items = {}
    for a in accs:
        items.setdefault((a["off"] - at, a["strides"], a["width"], a["fp"], a["rw"] == "R" and a["signed"]), a)
    items = list(items.items())
    nitems = len(items)

    def score(k):
        return sum(1 for (off, strides, *_), a in items if ok_access(a, ty, off - k, strides))
    s0 = score(0)
    best = None
    for k in sorted(range(-0x20, 0x21), key=abs):
        if k == 0:
            continue
        s = score(k)
        if best is None or s > best[1]:
            best = (k, s)
    out("  shift test: k=0 fits %d/%d distinct accesses; best k=%+d fits %d/%d" % (s0, nitems, best[0], best[1], nitems))
    if best[1] > s0 and best[1] >= max(3, 0.8 * nitems) and best[1] - s0 >= 2:
        k = best[0]
        out("  !! FIELDS APPEAR SHIFTED BY %+d BYTES: observed offset = declared offset %+d for %d/%d accesses."
            % (k, k, best[1], nitems))
        out("     Either the declaration has a missing/extra %d-byte field before them, or the struct begins %d"
            " bytes into %s (rerun with --at %s)." % (abs(k), k, base, hexs(at + k)))
    else:
        out("  no consistent shift")


def norm_path(p):
    return re.sub(r"\[(i[+-]\d+|i|\d+!?)\]", "[]", p)


def flatten(ty, prefix="", base=0, depth=0):
    out = []
    if ty.kind in ("struct", "union") and depth < 6:
        for foff, fname, fty in ty.fields:
            out += flatten(fty, prefix + ("." if prefix else "") + fname, base + foff, depth + 1)
    elif ty.kind == "array" and ty.elem.kind in ("struct", "union") and depth < 6:
        out += flatten(ty.elem, prefix + "[0]", base, depth + 1)
    else:
        out.append((base, prefix or "<self>", ty))
    return out


# --------------------------------------------------------------------------------------
# Sources, draft compilation
# --------------------------------------------------------------------------------------

def find_target_asm(func):
    hits = glob.glob(os.path.join(REPO, "asm", "us", "nonmatchings", "**", func + ".s"), recursive=True)
    return hits[0] if hits else None


def find_src(func):
    pat_asm = re.compile(r'/%s\.s"' % re.escape(func))
    pat_def = re.compile(r"^[A-Za-z_][\w\s\*]*\b%s\s*\([^;]*$" % re.escape(func), re.M)
    hits = []
    for c in glob.glob(os.path.join(REPO, "src", "**", "*.c"), recursive=True):
        try:
            t = open(c, encoding="utf-8", errors="replace").read()
        except OSError:
            continue
        if func not in t:
            continue
        if pat_asm.search(t):
            return c
        if pat_def.search(t):
            hits.append(c)
    return hits[0] if hits else None


def enable_draft(text, func):
    m = re.search(r'#pragma\s+GLOBAL_ASM\("[^"]*/%s\.s"\)' % re.escape(func), text)
    if not m:
        return None
    head = text[: m.start()]
    j = max(head.rfind("#ifdef NON_MATCHING"), head.rfind("#if defined(NON_MATCHING)"))
    if j < 0 or not re.search(r"\b%s\s*\(" % re.escape(func), head[j:]):
        return None
    eol = text.index("\n", j)
    return text[:j] + "#if 1" + text[eol:]


def compile_draft(func, src):
    rel = os.path.relpath(src, REPO)
    text = enable_draft(open(src, encoding="utf-8").read(), func)
    if text is None:
        sys.exit("accessmap: no `#ifdef NON_MATCHING` draft of %s in %s" % (func, rel))
    obj = "build/" + rel[:-2] + ".o"
    p = subprocess.run(["make", "-n", "-B", obj, "PYTHON=" + PY], cwd=REPO, capture_output=True, text=True, env=ENV)
    argv = None
    for line in p.stdout.splitlines():
        line = line.strip().lstrip("@")
        if "tools/ido/" in line and line.endswith(" " + rel) and " -o " + obj + " " in line:
            argv = shlex.split(line)
    if argv is None:
        sys.exit("accessmap: no compile command for %s in `make -n`" % obj)
    dsrc = os.path.join(DRAFT_DIR, rel)
    dobj = os.path.join(DRAFT_DIR, obj)
    os.makedirs(os.path.dirname(dsrc), exist_ok=True)
    os.makedirs(os.path.dirname(dobj), exist_ok=True)
    with open(dsrc, "w", encoding="utf-8") as f:
        f.write(text)
    k = len(argv) - 1 - argv[::-1].index("-o")
    argv = argv[:k] + ["-I" + os.path.dirname(rel), "-o", dobj] + argv[k + 2:-1] + [dsrc]
    if os.path.exists(dobj):
        os.remove(dobj)
    p = subprocess.run(argv, cwd=REPO, capture_output=True, text=True, env=ENV)
    if p.returncode != 0 or not os.path.exists(dobj):
        errs = [l for l in (p.stdout + p.stderr).splitlines() if "Warning" not in l]
        sys.exit("accessmap: draft compile FAILED:\n" + "\n".join(errs[-20:]))
    return dobj


def matched_obj(func, src):
    rel = os.path.relpath(src, REPO)
    for cand in ("expected/build/" + rel[:-2] + ".o", "build/" + rel[:-2] + ".o"):
        p = os.path.join(REPO, cand)
        if os.path.exists(p):
            return p
    return None


def load_insns(path, func):
    if path.endswith(".o"):
        return objdump_func(path, func)
    txt = open(path, encoding="utf-8", errors="replace").read()
    if re.search(r"^\s*[0-9a-f]+:\t[0-9a-f]{8} \t", txt, re.M):  # saved `objdump -dr` text
        return objdump_text(txt)
    return parse_splat(path, func)


# --------------------------------------------------------------------------------------
# Target vs draft
# --------------------------------------------------------------------------------------

def norm_val(v):
    if v is None:
        return None
    v = re.sub(r"\([a-z0-9.]+\)", "", v)  # conversions
    v = v.lstrip("-")
    if re.fullmatch(r"(t|f|clob|fclob|fret|sp\+\w+)@[0-9A-F]+|-?0x[0-9A-F]+|[-0-9.e]+f|fclob|finit_\w+|init_\w+", v):
        return None  # not a stable identity
    if v.startswith("t@") or v.startswith("f@") or "@" in v:
        return None
    return v


def compare(tan, dan, out=print):
    out("")
    out("=" * 100)
    out("TARGET vs DRAFT")
    out("=" * 100)

    def keyset(an):
        d = collections.defaultdict(lambda: collections.defaultdict(set))
        for a in an.accesses:
            d[a["root"]][(a["strides"], a["off"])].add((acc_type(a), a["rw"]))
        return d
    tk, dk = keyset(tan), keyset(dan)
    any_diff = False
    for root in sorted(set(tk) | set(dk), key=lambda r: (-len(tk.get(r, {})), r)):
        t, d = tk.get(root, {}), dk.get(root, {})
        lines = []
        for key in sorted(set(t) | set(d)):
            st, off = key
            name = hexs(off) + strides_s(st)
            if key not in d:
                lines.append("    only TARGET  %-18s %s" % (name, fmt_ts(t[key])))
            elif key not in t:
                lines.append("    only DRAFT   %-18s %s" % (name, fmt_ts(d[key])))
            else:
                tt = {x[0] for x in t[key]}
                dt = {x[0] for x in d[key]}
                trw = {x[1] for x in t[key]}
                drw = {x[1] for x in d[key]}
                if tt != dt or trw != drw:
                    lines.append("    differs      %-18s target %s   draft %s" % (name, fmt_ts(t[key]), fmt_ts(d[key])))
        if lines:
            any_diff = True
            out("  base %s: %s" % (root, "missing in draft" if root not in dk else ("missing in target" if root not in tk else "")))
            for l in lines:
                out(l)
    if not any_diff:
        out("  same set of (base, offset, type, R/W) on both sides")
    # provenance: the same stored value at different offsets
    tw = collections.defaultdict(list)
    dw = collections.defaultdict(list)
    for a in tan.accesses:
        if a["rw"] == "W" and norm_val(a["value"]):
            tw[norm_val(a["value"])].append(a)
    for a in dan.accesses:
        if a["rw"] == "W" and norm_val(a["value"]):
            dw[norm_val(a["value"])].append(a)
    deltas = collections.Counter()
    pairs = []
    for v in tw:
        if v not in dw or len(tw[v]) != 1 or len(dw[v]) != 1:
            continue
        ta, da = tw[v][0], dw[v][0]
        if ta["root"] != da["root"] or ta["strides"] != da["strides"]:
            continue
        dlt = da["off"] - ta["off"]
        deltas[dlt] += 1
        pairs.append((ta["off"], v, ta, da, dlt))
    if pairs:
        out("")
        out("  store provenance (values stored exactly once on each side):")
        for off, v, ta, da, dlt in sorted(pairs, key=lambda x: (x[2]["root"], x[0])):
            flag = ("DELTA %+d" % dlt) if dlt else ""
            if acc_type(ta) != acc_type(da):
                flag += " TYPE %s->%s" % (acc_type(ta), acc_type(da))
            out("    %-18s target %s %-18s %-5s draft %s %-18s %-5s %s" % (
                v[:18], ta["root"][:10], hexs(ta["off"]) + strides_s(ta["strides"]), acc_type(ta),
                da["root"][:10], hexs(da["off"]) + strides_s(da["strides"]), acc_type(da), flag))
        k, n = deltas.most_common(1)[0]
        nonzero = sum(c for d, c in deltas.items() if d != 0)
        if k != 0 and n >= max(2, 0.5 * len(pairs)):
            out("  !! DRAFT STORES SHIFTED BY %+d BYTES vs target for %d/%d values: the draft writes each value"
                " %d bytes %s where the original did -> the field names / struct used in the draft are off by"
                " %d bytes." % (k, n, len(pairs), abs(k), "after" if k > 0 else "before", abs(k)))
        elif nonzero:
            out("  %d/%d values land at a different offset in the draft" % (nonzero, len(pairs)))
        else:
            out("  every value is stored at the same offset on both sides")


def fmt_ts(s):
    return " ".join(sorted("%s %s" % (t, rw) for t, rw in s))


# --------------------------------------------------------------------------------------

def main():
    ap = argparse.ArgumentParser(description="Memory access map of a function's target asm (see the doc at the top)",
                                 formatter_class=argparse.RawDescriptionHelpFormatter, epilog=__doc__.split("WHAT IT TRACKS")[0])
    ap.add_argument("func")
    ap.add_argument("--base", help="only this base (arg0 / a0 / D_xxx / \"[arg0+0x10]\" ...)")
    ap.add_argument("--struct", help="struct/typedef name to overlay on --base")
    ap.add_argument("--at", default="0", help="the struct starts at base+AT (default 0)")
    ap.add_argument("--array", action="store_true", help="overlay NAME[] (an array of the struct) instead of one NAME")
    ap.add_argument("--src", help="C file (for --struct / --draft); default: found by grep")
    ap.add_argument("--obj", help="analyse FUNC from this object file instead of the target asm")
    ap.add_argument("--draft", action="store_true", help="compile the NON_MATCHING draft into scratch/ and compare")
    ap.add_argument("--draft-s", help="draft asm (splat .s, or saved `objdump -dr` text)")
    ap.add_argument("--draft-o", help="draft object file")
    ap.add_argument("--all-addrs", action="store_true", help="list every instruction address")
    a = ap.parse_args()
    func = a.func
    src = a.src or find_src(func)

    if a.obj:
        tpath = a.obj
    else:
        tpath = find_target_asm(func)
        if tpath is None:
            if src is None:
                sys.exit("accessmap: no asm/us/nonmatchings/**/%s.s and no C file defines it" % func)
            tpath = matched_obj(func, src)
            if tpath is None:
                sys.exit("accessmap: %s is matched but no object found (build first)" % func)
    insns = load_insns(tpath, func)
    if not insns:
        sys.exit("accessmap: no instructions for %s in %s" % (func, tpath))
    tan = Analyzer(insns, func).run()
    print_tables(tan, "TARGET %s  <- %s" % (func, os.path.relpath(tpath, REPO)), only=a.base, all_addrs=a.all_addrs)

    if a.struct:
        if src is None:
            sys.exit("accessmap: --struct needs the C file (--src)")
        ty, cp = find_struct(src, a.struct)
        if ty is None:
            sys.exit("accessmap: struct %s not found in %s (+ headers)" % (a.struct, os.path.relpath(src, REPO)))
        if ty.kind == "ptr" and ty.elem is not None:
            ty = ty.elem
        base = a.base
        if base:
            base = {"a0": "arg0", "a1": "arg1", "a2": "arg2", "a3": "arg3"}.get(base, base)
        else:
            cnt = collections.Counter(x["root"] for x in tan.accesses)
            base = cnt.most_common(1)[0][0] if cnt else "arg0"
        if a.array:
            ty = T("array", 0, ty.align, elem=ty, count=None)
        struct_report(tan, ty, a.struct + ("[]" if a.array else ""), base, int(a.at, 0))

    dpath = None
    if a.draft:
        if src is None:
            sys.exit("accessmap: --draft needs the C file")
        dpath = compile_draft(func, src)
    elif a.draft_s:
        dpath = a.draft_s
    elif a.draft_o:
        dpath = a.draft_o
    if dpath:
        dins = load_insns(dpath, func)
        if not dins:
            sys.exit("accessmap: no instructions for %s in draft %s" % (func, dpath))
        dan = Analyzer(dins, func).run()
        print("")
        print_tables(dan, "DRAFT %s  <- %s" % (func, os.path.relpath(dpath, REPO)), only=a.base, all_addrs=a.all_addrs)
        compare(tan, dan)


if __name__ == "__main__":
    main()
