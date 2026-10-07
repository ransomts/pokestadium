#!/home/tsranso/Code/pokestadium/.venv/bin/python3
"""transplant.py - turn a matched near-copy ("sibling") into a draft for an unmatched function.

USAGE (repo root; repo venv python; needs build/corpus/index.json from `corpus.py build`)
  PY=/home/tsranso/Code/pokestadium/.venv/bin/python3
  $PY matching_notes/transplant.py TARGET SIBLING                 # draft -> stdout, + scratch compile/diff
  $PY matching_notes/transplant.py TARGET SIBLING --out d.c       # draft -> d.c, + scratch compile/diff
  $PY matching_notes/transplant.py TARGET SIBLING --no-check      # just the draft, no compile
  $PY matching_notes/transplant.py TARGET --check d.c              # scratch compile + diff an edited draft
  $PY matching_notes/transplant.py TARGET SIBLING --apply <worktree>/src/.../file.c
                                                                  # ALSO write the draft into that C file
  $PY matching_notes/transplant.py --suggest [-j 4] [--per 1] [--min-score 0.45]
        every unmatched function of the index with a STRONG sibling (corpus.py siblings score >= 0.45):
        transplant its best sibling(s) in scratch, table: target, sibling, similarity, diff score, compile ok
  options: --lines N (differing lines to print, default 20), --keep (keep the scratch mirror),
           --full (diff.py without -s, i.e. past the first jr ra)

WHAT IT DOES
  1. Sibling C: the definition of SIBLING in its current source file (located via the index record's
     file; falls back to the index's stored C text). Sibling asm: the index (= build/src/**/*.o
     objdump, relocations resolved); falls back to objdump of expected/build/src/<file>.o.
     Target asm: asm/us/nonmatchings/**/TARGET.s (splat).
  2. Symbol map: both listings are aligned with difflib on corpus.py's norm form (symbols -> SYM,
     regs -> class), and every aligned instruction pair that carries a symbol on both sides (`jal`/`j`
     targets, %hi/%lo of lui/addiu/loads/stores) votes sibling-symbol -> target-symbol. Unequal
     `replace` hunks vote positionally only when both sides have the same kinds of refs in the same
     order. Addends are folded: sibling `D_A+0x8` vs target `D_B+0xC` maps D_A -> D_(B+4) when both are
     address-named (D_/func_ + hex), so a struct base maps to the target's struct base. A sibling
     symbol with one candidate is renamed; one candidate with >= 75% of the votes is renamed with a
     `majority` note; anything else stays and gets `// TRANSPLANT: ambiguous ...` (header + the first
     line using it). SIBLING -> TARGET is always renamed. Renaming is token-wise outside comments/strings.
  3. Declarations: identifiers of the renamed body that the target file's include closure never
     mentions, but that the sibling's closure declares at file scope (column 0), get an `extern` stub
     (data) or prototype (function) built from the sibling's declaration; typedef names missing from
     the target closure get their typedef copied from the sibling closure (dependencies first). All of
     it goes inside the #ifdef NON_MATCHING block, marked TRANSPLANT - the matcher must resolve it
     (declare the real data in the target file, or include the right header).
  4. Prototypes: column-0 prototypes of TARGET elsewhere in the target closure that differ from the
     transplanted signature are rewritten in the scratch copy (and, with --apply, in the applied .c
     file; header ones are only reported).
  5. Scratch check (default): mirror the repo under scratch/transplant_dev/mirror/<TARGET>/ (symlinks;
     only the target .c, the touched headers and the object dir are real - the ido_bisect.py mirror),
     replace TARGET's block (the #ifdef NON_MATCHING..#else GLOBAL_ASM..#endif, or the bare GLOBAL_ASM)
     by the transplant with a bare `#if 1`, compile with exactly the command `make -n -B
     build/src/<file>.o` prints, and diff with `tools/asm-differ/diff.py -o TARGET -s --format plain`
     (as fd.sh). Prints the score and the first --lines differing lines. Nothing in src/ or build/ of
     the repo is touched; the full diff is kept as scratch/transplant_dev/diff_<TARGET>.txt (the mirror
     is removed afterwards unless --keep).

OUTPUT (draft)
  #ifdef NON_MATCHING
  // TRANSPLANT: from SIBLING (file:line), symbol map, notes, stubs
  <renamed C>
  #else
  #pragma GLOBAL_ASM("asm/us/nonmatchings/.../TARGET.s")
  #endif

LIMITATIONS
  Struct types are NOT translated: the body keeps the sibling's parameter types and field accesses.
  That is right when the sibling's types are visible in the target file (the usual case: shared
  fragment headers); otherwise their typedefs are copied in, which compiles but is a duplicate the
  matcher should fold into the real type. Symbols the sibling C uses that never show up in its asm
  (e.g. only through sizeof or folded constants) cannot be mapped. Address-arithmetic mapping assumes
  the same field layout around a data symbol. --suggest only considers unmatched functions that are
  in the index (files that build with GLOBAL_ASM), like `corpus.py siblings --all-unmatched`.
"""

import argparse
import collections
import concurrent.futures
import difflib
import glob
import os
import re
import shutil
import subprocess
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)
import corpus as C  # noqa: E402
import ido_bisect as B  # noqa: E402

REPO = C.REPO
PY = os.path.join(REPO, ".venv", "bin", "python3")
SCRATCH = os.path.join(REPO, "scratch", "transplant_dev")
INC_DIRS = ["include", "src", "src/libnaudio", "assets/us", ".", "build", "lib/ultralib/include",
            "lib/ultralib/include/PR", "lib/ultralib/include/ido"]
IDENT_RE = re.compile(r"[A-Za-z_]\w*")
ADDR_NAME_RE = re.compile(r"^(D_|func_|jtbl_)([0-9A-Fa-f]{6,8})$")
REF_RE = re.compile(r"%(hi|lo)\(([^()]+)\)")
DIFFLINE = re.compile(r"^\S*\s*[0-9a-f]+:\s.*\s(r|i|s|<|>|\|)\s")
C_KEYWORDS = set("""auto break case char const continue default do double else enum extern float for goto if
int long register return short signed sizeof static struct switch typedef union unsigned void volatile while
NULL""".split())


# --------------------------------------------------------------------------------------
# index / sources
# --------------------------------------------------------------------------------------

_IDX = None


def index():
    global _IDX
    if _IDX is None:
        _IDX = C.load_index()
        _IDX["by_name"] = {}
        for f in _IDX["functions"]:
            _IDX["by_name"].setdefault(f["name"], f)
    return _IDX


def read(path):
    with open(path, encoding="utf-8", errors="replace") as fp:
        return fp.read()


def func_def(text, name):
    """-> (start_line, end_line) 1-based of the definition of name in text, or None."""
    for n, sl, el in C.parse_c_defs(text):
        if n == name:
            return sl, el
    return None


def sibling_info(name):
    """-> dict(name, file, line, c, raw)."""
    rec = index()["by_name"].get(name)
    if rec is None:
        sys.exit("transplant: %s is not in build/corpus/index.json (corpus.py build?)" % name)
    if not rec["matched"]:
        print("transplant: warning: sibling %s is itself unmatched in the index" % name, file=sys.stderr)
    cpath = os.path.join(REPO, rec["file"])
    ctext, line = rec["c"], rec["line"]
    if os.path.isfile(cpath):
        t = read(cpath)
        d = func_def(t, name)
        if d:
            ctext, line = "\n".join(t.split("\n")[d[0] - 1:d[1]]), d[0]
    if not ctext.strip():
        sys.exit("transplant: no C body for %s" % name)
    raw = rec["raw"]
    if not raw:
        raw = expected_raw(rec["file"], name)
    return {"name": name, "file": rec["file"], "line": line, "c": ctext, "raw": raw}


def expected_raw(cfile, name):
    obj = os.path.join(REPO, "expected", "build", cfile[:-2] + ".o")
    funcs = C.parse_objdump(C.objdump(obj))
    for i, f in enumerate(funcs):
        if f["name"] == name:
            fend = funcs[i + 1]["start"] if i + 1 < len(funcs) else f["insns"][-1][0] + 4
            return C.func_to_raw(f, fend - f["start"], C.symtab(obj))
    sys.exit("transplant: %s not found in %s" % (name, obj))


def target_info(name):
    tpath = C.find_target_asm(name)
    if not tpath:
        sys.exit("transplant: no asm/us/nonmatchings/**/%s.s" % name)
    _, raw = C.parse_splat(tpath, name)
    rec = index()["by_name"].get(name)
    src = os.path.join(REPO, rec["file"]) if rec else None
    if not src or ("/%s.s\"" % name) not in read(src):
        src = C.find_src_for(name)
    if not src:
        sys.exit("transplant: no src/**/*.c has GLOBAL_ASM for %s" % name)
    return {"name": name, "asm": os.path.relpath(tpath, REPO), "raw": raw, "src": os.path.relpath(src, REPO)}


# --------------------------------------------------------------------------------------
# include closure
# --------------------------------------------------------------------------------------

_CLOSURE = {}


def closure(relc):
    """-> ordered [(relpath, text)] of relc and every "local" header it includes, recursively."""
    if relc in _CLOSURE:
        return _CLOSURE[relc]
    out, seen = [], set()

    def visit(rel):
        if rel in seen:
            return
        seen.add(rel)
        try:
            text = read(os.path.join(REPO, rel))
        except OSError:
            return
        out.append((rel, text))
        for inc in re.findall(r'^\s*#\s*include\s+[<"]([^>"]+)[>"]', text, re.M):
            for d in [os.path.dirname(rel)] + INC_DIRS:
                p = os.path.normpath(os.path.join(d, inc))
                if os.path.isfile(os.path.join(REPO, p)):
                    visit(p)
                    break

    visit(relc)
    _CLOSURE[relc] = out
    return out


def mentions(cl, ident, skip=None):
    """Does any file of the closure mention ident (outside the [a, b) char span `skip` of file 0)?"""
    r = re.compile(r"\b%s\b" % re.escape(ident))
    for k, (rel, text) in enumerate(cl):
        key = (rel, len(text))
        if key not in _MASKED:
            _MASKED[key] = C.mask_c(text)
        masked = _MASKED[key]
        if k == 0 and skip:
            masked = masked[:skip[0]] + masked[skip[1]:]
        if r.search(masked):
            return True
    return False


_MASKED = {}


def find_typedef(cl, name):
    """-> typedef text for name in the closure, or None."""
    for _rel, text in cl:
        m = re.search(r"\}\s*%s\s*;" % re.escape(name), text)
        if m:
            depth, i = 0, m.start()
            while i >= 0:
                if text[i] == "}":
                    depth += 1
                elif text[i] == "{":
                    depth -= 1
                    if depth == 0:
                        break
                i -= 1
            j = text.rfind("typedef", 0, i)
            if j >= 0 and ";" not in C.mask_c(text[j:i]):
                return text[j:m.end()]
        m = re.search(r"^typedef\b[^;{}]*?(?:\b%s\s*;|\(\s*\*\s*%s\s*\)[^;]*;)" % (re.escape(name), re.escape(name)),
                      text, re.M)
        if m:
            return m.group(0)
    return None


def find_file_decl(cl, name):
    """-> column-0 file-scope declaration/definition head of name in the closure (sibling side), or None."""
    pat = re.compile(r"^(?!return\b|else\b|case\b|typedef\b|#)[A-Za-z_][^\n;=(]*?[\s\*]%s\b[^\n]*" % re.escape(name),
                     re.M)
    for _rel, text in cl:
        m = pat.search(text)
        if m:
            # extend over a multi-line parameter list: up to ; { = at paren depth 0
            depth, i = 0, m.start()
            while i < len(text):
                ch = text[i]
                if ch == "(":
                    depth += 1
                elif ch == ")":
                    depth -= 1
                elif ch in ";{=" and depth == 0:
                    break
                i += 1
            return " ".join(text[m.start():i + 1].split())
    return None


def local_decls(body):
    """Names declared inside the function body (locals, local statics)."""
    masked = C.mask_c(body)
    i = masked.find("{")
    out = set()
    for m in re.finditer(r"^[ \t]+(?!return\b|goto\b|case\b|else\b)(?:static\s+|const\s+|volatile\s+|register\s+|struct\s+|unsigned\s+)*"
                         r"[A-Za-z_]\w*(?:[\s\*]+)([A-Za-z_]\w*)\s*(?=[=;\[,)])", masked[i + 1:], re.M):
        out.add(m.group(1))
    return out


def stub_from_decl(line, name):
    """`static u16 D_X[3] = {` -> `extern u16 D_X[];`; `s32 func_X(s32 a) {` -> `s32 func_X(s32 a);`."""
    s = line.strip()
    s = re.sub(r"\s*//.*$", "", s)
    if re.search(r"\b%s\s*\(" % re.escape(name), s):
        s = s.split("{")[0].rstrip().rstrip(";")
        s = re.sub(r"^(static|INLINE|inline)\s+", "", s)
        return s + ";"
    s = re.split(r"=|;|\{", s)[0].rstrip()
    s = re.sub(r"^(static|extern|const\s+static)\s+", "", s)
    s = re.sub(r"\b(%s)\s*\[[^\]]*\]" % re.escape(name), r"\1[]", s, count=1)
    return "extern " + s + ";"


# --------------------------------------------------------------------------------------
# symbol alignment
# --------------------------------------------------------------------------------------

def split_sym(s):
    m = re.match(r"^(.*?)([+-]0x[0-9a-fA-F]+|[+-]\d+)?$", s)
    return m.group(1), (int(m.group(2), 0) if m.group(2) else 0)


def insn_refs(raw):
    """raw line -> [(kind, name, addend)]"""
    out = []
    mn, _, ops = raw.partition(" ")
    if mn in ("jal", "j"):
        t = ops.strip()
        if t and not t.startswith(".L"):
            out.append(("jal", t, 0))
    for m in REF_RE.finditer(raw):
        n, a = split_sym(m.group(2))
        if not n.startswith("."):
            out.append((m.group(1), n, a))
    return out


def base_name(sname, sadd, tname, tadd):
    """Target name for the sibling's base symbol (addend-folded when both are address-named)."""
    ms, mt = ADDR_NAME_RE.match(sname), ADDR_NAME_RE.match(tname)
    if sadd == tadd or not (ms and mt):
        return tname
    v = int(mt.group(2), 16) + tadd - sadd
    return "%s%0*X" % (mt.group(1), len(mt.group(2)), v)


def align_symbols(sraw, traw):
    """-> (votes {sib: Counter{tgt: w}}, unmatched target refs Counter, sib ref names in order)."""
    snorm = [C.normalize(r) for r in sraw]
    tnorm = [C.normalize(r) for r in traw]
    sm = difflib.SequenceMatcher(None, snorm, tnorm, autojunk=False)
    votes = collections.defaultdict(collections.Counter)
    t_paired = set()

    def vote(sref, tref, w, tpos):
        (sk, sn, sa), (tk, tn, ta) = sref, tref
        if sk != tk:
            return
        votes[sn][base_name(sn, sa, tn, ta)] += w
        t_paired.add(tpos)

    for op, a1, a2, b1, b2 in sm.get_opcodes():
        if op == "equal":
            for i, j in zip(range(a1, a2), range(b1, b2)):
                for k, (sr, tr) in enumerate(zip(insn_refs(sraw[i]), insn_refs(traw[j]))):
                    vote(sr, tr, 1.0, (j, k))
        elif op == "replace":
            srefs = [r for i in range(a1, a2) for r in insn_refs(sraw[i])]
            trefs = [(r, (j, k)) for j in range(b1, b2) for k, r in enumerate(insn_refs(traw[j]))]
            if srefs and len(srefs) == len(trefs) and [r[0] for r in srefs] == [r[0][0] for r in trefs]:
                for sr, (tr, pos) in zip(srefs, trefs):
                    vote(sr, tr, 0.5, pos)
    t_unpaired = collections.Counter()
    for j, r in enumerate(traw):
        for k, (kind, n, a) in enumerate(insn_refs(r)):
            if (j, k) not in t_paired:
                t_unpaired[n] += 1
    sorder = []
    for r in sraw:
        for _k, n, _a in insn_refs(r):
            if n not in sorder:
                sorder.append(n)
    return votes, t_unpaired, sorder


def decide_map(votes, sorder, tnames=()):
    """-> (mapping {sib: tgt}, notes [str], ambiguous {sib: str}).
    A symbol both listings reference is the same symbol (identity, whatever the votes say), and a
    sibling symbol never maps onto another symbol the sibling itself references."""
    mapping, notes, amb = {}, [], {}
    sset = set(sorder)
    for s in sorder:
        if s in tnames:
            continue
        c = collections.Counter({t: w for t, w in votes.get(s, {}).items() if t == s or t not in sset})
        if not c:
            continue
        tot = sum(c.values())
        (best, bw), = c.most_common(1)
        if len(c) == 1:
            if best != s:
                mapping[s] = best
        elif bw / tot >= 0.75:
            if best != s:
                mapping[s] = best
            notes.append("majority %s -> %s (%d%% of votes; also %s)" % (
                s, best, 100 * bw / tot, ", ".join(n for n in c if n != best)))
        else:
            amb[s] = "%s aligns with %s" % (s, " / ".join("%s(%g)" % kv for kv in c.most_common()))
    inv = collections.defaultdict(list)
    for s, t in mapping.items():
        inv[t].append(s)
    for t, ss in inv.items():
        if len(ss) > 1:
            notes.append("many-to-one: %s all -> %s" % (", ".join(ss), t))
    return mapping, notes, amb


# --------------------------------------------------------------------------------------
# C rewriting
# --------------------------------------------------------------------------------------

def rename_c(text, mapping):
    masked = C.mask_c(text)
    out, last = [], 0
    for m in IDENT_RE.finditer(masked):
        new = mapping.get(m.group(0))
        if new is not None:
            out.append(text[last:m.start()])
            out.append(new)
            last = m.end()
    out.append(text[last:])
    return "".join(out)


def code_idents(text):
    """identifiers in code (not after . / ->), in order of first use."""
    masked = C.mask_c(text)
    seen = []
    for m in IDENT_RE.finditer(masked):
        pre = masked[:m.start()].rstrip()
        if pre.endswith(".") or pre.endswith("->"):
            continue
        n = m.group(0)
        if n not in seen and n not in C_KEYWORDS and not n[0].isdigit():
            seen.append(n)
    return seen


def signature(ctext):
    m = C.mask_c(ctext)
    i = m.index("{")
    return " ".join(ctext[:i].split())


def find_block(text, func):
    """-> (start, end) char span of func's #ifdef..#endif block (or of its bare GLOBAL_ASM line)."""
    lines = text.split("\n")
    p = next((i for i, l in enumerate(lines) if ("/%s.s\"" % func) in l and "GLOBAL_ASM" in l), None)
    if p is None:
        return None
    depth, k, else_at = 0, p - 1, None
    while k >= 0:
        s = lines[k].strip()
        if s.startswith("#endif"):
            depth += 1
        elif s.startswith("#if"):
            if depth == 0:
                break
            depth -= 1
        elif s.startswith("#else") and depth == 0:
            else_at = k
        k -= 1
    first, last = p, p
    if k >= 0 and else_at is not None and "NON_MATCHING" in lines[k]:
        depth, e = 0, p + 1
        while e < len(lines):
            s = lines[e].strip()
            if s.startswith("#if"):
                depth += 1
            elif s.startswith("#endif"):
                if depth == 0:
                    break
                depth -= 1
            e += 1
        first, last = k, e
    starts = [0]
    for l in lines:
        starts.append(starts[-1] + len(l) + 1)
    return starts[first], starts[last + 1] - 1


def proto_re(func):
    return re.compile(r"^(?!return\b|else\b|case\b)(?:static\s+|extern\s+)?[A-Za-z_][\w \t\*]*?\b%s\s*\([^;{}]*\)\s*;"
                      % re.escape(func), re.M)


# --------------------------------------------------------------------------------------
# transplant
# --------------------------------------------------------------------------------------

def protos_to_fix(tcl, tg, span, sig):
    out = []
    for rel, text in tcl:
        for m in proto_re(tg["name"]).finditer(text):
            if span and rel == tg["src"] and span[0] <= m.start() < span[1]:
                continue
            if " ".join(m.group(0).split()).rstrip(";").strip() != sig:
                out.append((rel, m.group(0)))
    return out


def load_draft(target, path):
    """A hand-edited draft (scaffolded or bare C) -> the dict scratch_check()/--apply need."""
    tg = target_info(target)
    text = read(path).rstrip("\n")
    pragma = '#pragma GLOBAL_ASM("%s")' % tg["asm"]
    m = re.match(r"^\s*#ifdef NON_MATCHING\n(.*)\n#else\n.*\n#endif\s*$", text, re.S)
    inner = m.group(1) if m else text
    d = func_def(inner, target)
    if not d:
        sys.exit("transplant: %s defines no %s" % (path, target))
    sig = signature("\n".join(inner.split("\n")[d[0] - 1:]))
    tcl = closure(tg["src"])
    span = find_block(tcl[0][1], target)
    return {"tg": tg, "sig": sig, "proto_fix": protos_to_fix(tcl, tg, span, sig), "inner": inner,
            "pragma": pragma, "stubs": [], "types": [], "amb": {},
            "draft": "#ifdef NON_MATCHING\n%s\n#else\n%s\n#endif" % (inner, pragma),
            "scratch_block": "#if 1\n%s\n#else\n%s\n#endif" % (inner, pragma)}


def make_transplant(target, sibling, sim=None):
    tg = target_info(target)
    sb = sibling_info(sibling)
    votes, t_unpaired, sorder = align_symbols(sb["raw"], tg["raw"])
    tnames = {n for r in tg["raw"] for _k, n, _a in insn_refs(r)}
    mapping, notes, amb = decide_map(votes, sorder, tnames)
    mapping[sibling] = target
    body = rename_c(sb["c"], mapping)

    tcl = closure(tg["src"])
    scl = closure(sb["file"])
    ttext = tcl[0][1]
    span = find_block(ttext, target)
    used = set(code_idents(body))
    mapped_used = [(s, t) for s, t in mapping.items() if s != sibling and t in used]

    # declarations the target side lacks
    stubs, types, unresolved = [], [], []
    inv = {t: s for s, t in mapping.items()}

    def need_type(name, acc, depth=0):
        if name in acc or depth > 8 or find_typedef(tcl, name) is not None:
            return
        td = find_typedef(scl, name)
        if td is None:
            return
        for n in code_idents(td):
            if n != name:
                need_type(n, acc, depth + 1)
        acc[name] = td

    tdefs = collections.OrderedDict()
    locals_ = local_decls(body)
    for n in code_idents(body):
        if n in (target, sibling) or n in locals_ or mentions(tcl, n, span):
            continue
        if find_typedef(scl, n) is not None:
            continue
        src_name = inv.get(n, n)
        decl = find_file_decl(scl, src_name)
        if decl is None:
            if n in mapping.values() or ADDR_NAME_RE.match(n):
                unresolved.append(n)
            continue
        stub = stub_from_decl(rename_c(decl, mapping), n)
        stubs.append(stub)
    for n in code_idents(body + "\n" + "\n".join(stubs)):
        if n not in (target, sibling) and n not in locals_:
            need_type(n, tdefs)
    types = list(tdefs.items())

    sig = signature(body)
    proto_fix = protos_to_fix(tcl, tg, span, sig)

    # header comment
    hdr = ["// TRANSPLANT: from %s (%s:%d)%s by matching_notes/transplant.py"
           % (sibling, sb["file"], sb["line"], (", similarity %.3f" % sim) if sim is not None else "")]
    if mapped_used:
        hdr.append("// TRANSPLANT: renamed " + ", ".join("%s -> %s" % st for st in mapped_used))
    others = [(s, t) for s, t in mapping.items() if s != sibling and t not in used]
    if others:
        hdr.append("// TRANSPLANT: asm-only map (not in C) " + ", ".join("%s -> %s" % st for st in others[:12])
                   + (" ..." if len(others) > 12 else ""))
    for n in notes:
        hdr.append("// TRANSPLANT: " + n)
    for s, why in amb.items():
        hdr.append("// TRANSPLANT: ambiguous %s (kept)" % why)
    orphan_s = [s for s in sorder if s not in mapping and s not in tnames and s not in amb and s != sibling]
    if orphan_s:
        hdr.append("// TRANSPLANT: sibling-only refs (no aligned target ref, kept): " + ", ".join(orphan_s))
    orphan_t = [n for n in t_unpaired if n not in mapping.values() and n not in sorder]
    if orphan_t:
        hdr.append("// TRANSPLANT: target-only refs (unaligned; the C must produce these): " + ", ".join(orphan_t))
    for rel, old in proto_fix:
        hdr.append("// TRANSPLANT: prototype at %s differs, needs: %s;" % (rel, sig))
        hdr.append("//             was: %s" % " ".join(old.split()))
    if unresolved:
        hdr.append("// TRANSPLANT: undeclared and no sibling declaration found: " + ", ".join(unresolved))
    for name, td in types:
        hdr.append("// TRANSPLANT: type %s copied from the sibling's headers - use the target's real type" % name)
        hdr.append(td)
    if stubs:
        hdr.append("// TRANSPLANT: extern stubs (declare these properly in the target file):")
        hdr.extend(stubs)

    # inline ambiguity markers
    if amb:
        lines = body.split("\n")
        masked = C.mask_c(body).split("\n")
        for s, why in amb.items():
            for k, ml in enumerate(masked):
                if re.search(r"\b%s\b" % re.escape(s), ml):
                    lines[k] += "  // TRANSPLANT: ambiguous " + why
                    break
        body = "\n".join(lines)

    inner = "\n".join(hdr) + "\n" + body
    pragma = '#pragma GLOBAL_ASM("%s")' % tg["asm"]
    return {
        "tg": tg, "sb": sb, "mapping": mapping, "amb": amb, "notes": notes, "stubs": stubs, "types": types,
        "proto_fix": proto_fix, "sig": sig, "span": span, "inner": inner, "pragma": pragma,
        "draft": "#ifdef NON_MATCHING\n%s\n#else\n%s\n#endif" % (inner, pragma),
        "scratch_block": "#if 1\n%s\n#else\n%s\n#endif" % (inner, pragma),
    }


def splice(text, tp, block):
    span = find_block(text, tp["tg"]["name"])
    if span is None:
        raise SystemExit("transplant: no GLOBAL_ASM for %s in the file" % tp["tg"]["name"])
    new = text[:span[0]] + block + text[span[1]:]
    return fix_protos(new, tp, skip=(span[0], span[0] + len(block)))


def fix_protos(text, tp, skip=None):
    out, last = [], 0
    for m in proto_re(tp["tg"]["name"]).finditer(text):
        if skip and skip[0] <= m.start() < skip[1]:
            continue
        if " ".join(m.group(0).split()).rstrip(";").strip() != tp["sig"]:
            out.append(text[last:m.start()])
            out.append(tp["sig"] + ";")
            last = m.end()
    out.append(text[last:])
    return "".join(out)


_CMD = {}


def rename_outside(text, name, new, skip=None):
    """Rename code occurrences of name outside the char span skip."""
    masked = C.mask_c(text)
    out, last = [], 0
    for m in re.finditer(r"\b%s\b" % re.escape(name), masked):
        if skip and skip[0] <= m.start() < skip[1]:
            continue
        out.append(text[last:m.start()])
        out.append(new)
        last = m.end()
    out.append(text[last:])
    return "".join(out)


def scratch_check(tp, keep=False, full=False, nlines=20):
    """-> dict(ok, isolated, score, err, difflines, root). Retries with the target's callers isolated when
    the plain build fails (see isolate)."""
    r = scratch_build(tp, keep, full, nlines, isolate=False)
    if not r["ok"]:
        r2 = scratch_build(tp, keep, full, nlines, isolate=True)
        if r2["ok"]:
            r2["plain_err"] = r["err"]
            return r2
    return r


def scratch_build(tp, keep, full, nlines, isolate):
    """isolate=False: prototypes of TARGET are rewritten to the transplant's signature.
    isolate=True: every other mention of TARGET in the .c and its headers (callers, prototypes, function
    pointer stores) is renamed to TARGET_xcaller, so callers keep compiling against the OLD prototype and
    the transplant (whatever its parameters) is the only TARGET in the file. Only TARGET is diffed, so
    this does not change the score; the matcher still has to reconcile the callers."""
    src = tp["tg"]["src"]
    target = tp["tg"]["name"]
    obj = "build/" + src[:-2] + ".o"
    root = os.path.join(SCRATCH, "mirror", target)
    if os.path.lexists(root):
        shutil.rmtree(root)
    if isolate:
        hdrs = sorted({rel for rel, text in closure(src)[1:] if mentions([(rel, text)], target)})
    else:
        hdrs = sorted({rel for rel, _ in tp["proto_fix"] if rel != src})
    B.mirror(root, [os.path.dirname(src), os.path.dirname(obj)] + [os.path.dirname(h) for h in hdrs])
    for rel in [src] + hdrs:
        p = os.path.join(root, rel)
        text = read(os.path.join(REPO, rel))
        if isolate:
            if rel == src:
                span = find_block(text, target)
                text = text[:span[0]] + tp["scratch_block"] + text[span[1]:]
                text = rename_outside(text, target, target + "_xcaller", (span[0], span[0] + len(tp["scratch_block"])))
            else:
                text = rename_outside(text, target, target + "_xcaller")
        else:
            text = splice(text, tp, tp["scratch_block"]) if rel == src else fix_protos(text, tp)
        if os.path.lexists(p):
            os.remove(p)
        with open(p, "w", encoding="utf-8") as fp:
            fp.write(text)
    if obj not in _CMD:
        _CMD[obj] = B.compile_command(obj)
    objpath = os.path.join(root, obj)
    if os.path.lexists(objpath):
        os.remove(objpath)
    p = B.run(_CMD[obj], root)
    res = {"root": root, "ok": False, "isolated": isolate, "score": None, "err": "", "difflines": [], "ndiff": 0}
    if p.returncode != 0 or not os.path.exists(objpath):
        lines = (p.stdout + p.stderr).splitlines()
        errs = []
        for k, l in enumerate(lines):
            if "Error" in l:
                errs.append(re.sub(r"/tmp/tmp\.\w+/", "", l))
                errs.extend("    " + x.strip() for x in lines[k + 1:k + 2])
        if not errs:
            errs = [l for l in lines if "Warning" not in l and l.strip()][-15:]
        res["err"] = "\n".join(errs[:30])
    else:
        res["ok"] = True
        d = B.run([PY, "-W", "ignore", "tools/asm-differ/diff.py", "-o", target] + ([] if full else ["-s"])
                  + ["--format", "plain"], root)
        out = d.stdout + d.stderr
        with open(os.path.join(SCRATCH, "diff_%s.txt" % target), "w") as fp:
            fp.write(out)
        m = re.search(r"Score:\s*(\d+)", out) or re.search(r"^TARGET\s+CURRENT \((\d+)\)", out, re.M)
        res["score"] = int(m.group(1)) if m else None
        dl = [l for l in out.splitlines() if DIFFLINE.match(l)]
        res["ndiff"] = len(dl)
        res["difflines"] = dl[:nlines]
        if res["score"] is None:
            res["err"] = "\n".join(out.splitlines()[-10:])
    if not keep:
        shutil.rmtree(root, ignore_errors=True)
    return res


# --------------------------------------------------------------------------------------
# commands
# --------------------------------------------------------------------------------------

def cmd_one(args):
    if args.check:
        tp = load_draft(args.target, args.check)
        args.sibling = os.path.basename(args.check)
    else:
        tp = make_transplant(args.target, args.sibling)
    if args.check:
        pass
    elif args.out:
        with open(args.out, "w") as fp:
            fp.write(tp["draft"] + "\n")
        print("draft written to %s" % args.out, file=sys.stderr)
    else:
        print(tp["draft"])
    if args.apply:
        text = read(args.apply)
        new = splice(text, tp, tp["draft"])
        with open(args.apply, "w", encoding="utf-8") as fp:
            fp.write(new)
        print("applied to %s" % args.apply, file=sys.stderr)
        for rel, _old in tp["proto_fix"]:
            if rel != tp["tg"]["src"]:
                print("NOTE: prototype in %s must become: %s;" % (rel, tp["sig"]), file=sys.stderr)
    if args.no_check:
        return
    r = scratch_check(tp, keep=args.keep, full=args.full, nlines=args.lines)
    print("", file=sys.stderr)
    print("== scratch check: %s <- %s  (%s)" % (args.target, args.sibling, tp["tg"]["src"]), file=sys.stderr)
    if not r["ok"]:
        print("COMPILE FAILED:\n" + r["err"], file=sys.stderr)
        sys.exit(1)
    if r["isolated"]:
        print("NOTE: the plain build failed; compiled with the target's callers/prototypes renamed to %s_xcaller "
              "(they disagree with the transplanted signature). Plain-build error:" % args.target, file=sys.stderr)
        print("\n".join("    " + l for l in r.get("plain_err", "").splitlines()[:6]), file=sys.stderr)
    print("Score: %s   differing lines: %d   (full diff: %s)" % (
        r["score"], r["ndiff"], os.path.relpath(os.path.join(SCRATCH, "diff_%s.txt" % args.target), REPO)),
        file=sys.stderr)
    for l in r["difflines"]:
        print(l, file=sys.stderr)
    if r["err"]:
        print(r["err"], file=sys.stderr)


def cmd_suggest(args):
    idx = index()
    data = C.load_siblings(idx)
    fns = idx["functions"]
    jobs = []
    for qi, f in enumerate(fns):
        if f["matched"]:
            continue
        if ("/%s.s\"" % f["name"]) not in read(os.path.join(REPO, f["file"])):
            print("skip %s: no GLOBAL_ASM in %s any more (matched since the index was built; corpus.py build)"
                  % (f["name"], f["file"]), file=sys.stderr)
            continue
        tpath = C.find_target_asm(f["name"])
        qnorm = [C.normalize(r) for r in C.parse_splat(tpath, f["name"])[1]] if tpath else f["norm"]
        ranked = [r for r in C.sib_rank(qnorm, data, fns, skip=qi) if r[0] >= args.min_score][:args.per]
        for score, fi, *_ in ranked:
            jobs.append((f["name"], fns[fi]["name"], score, len(qnorm), len(fns[fi]["norm"])))
    # pre-warm caches serially (closures/compile commands are shared dicts)
    print("%d target/sibling pairs with score >= %.2f" % (len(jobs), args.min_score), file=sys.stderr)

    def run(job):
        t, s, score, _qn, _sn = job
        try:
            tp = make_transplant(t, s, score)
            r = scratch_check(tp, keep=args.keep, full=args.full, nlines=0)
            extra = len(tp["amb"])
            return job, r, tp, extra, None
        except SystemExit as e:
            return job, None, None, 0, str(e)
        except Exception as e:  # report and go on
            return job, None, None, 0, "%s: %s" % (type(e).__name__, e)

    results = []
    with concurrent.futures.ThreadPoolExecutor(max_workers=args.jobs) as ex:
        for res in ex.map(run, jobs):
            results.append(res)
    print("%-16s %-16s %5s %5s  %-6s %-10s %-6s %-5s %-5s %s" % (
        "target", "sibling", "tIns", "sIns", "sim", "diffscore", "ndiff", "comp", "amb", "notes"))
    for (t, s, score, qn, sn), r, tp, amb, err in sorted(results, key=lambda x: -x[0][2]):
        if r is None:
            print("%-16s %-16s %5d %5d  %-6.3f %-10s %-6s %-5s %-5s %s" % (t, s, qn, sn, score, "-", "-", "ERR", "-",
                                                                         err.splitlines()[0] if err else ""))
            continue
        note = ""
        if not r["ok"]:
            el = [l for l in r["err"].splitlines() if "rror" in l]
            note = "%d errors, first: %s" % (len(el), (el or r["err"].splitlines() or [""])[0][:100])
        else:
            bits = []
            if tp["stubs"]:
                bits.append("%d stubs" % len(tp["stubs"]))
            if tp["types"]:
                bits.append("%d typedefs" % len(tp["types"]))
            if tp["proto_fix"]:
                bits.append("proto changed")
            if r["isolated"]:
                bits.append("callers isolated (signature differs from callers)")
            note = ", ".join(bits)
        print("%-16s %-16s %5d %5d  %-6.3f %-10s %-6s %-5s %-5d %s" % (
            t, s, qn, sn, score, r["score"] if r["score"] is not None else "-", r["ndiff"] if r["ok"] else "-",
            ("ok*" if r["isolated"] else "ok") if r["ok"] else "FAIL", amb, note))
    print("(comp: ok = compiles as is (prototypes rewritten in scratch), ok* = compiles once the target's callers "
          "are isolated, FAIL = does not compile; diffscore = diff.py -s score vs the target, 0 = match)")


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter,
                                 usage="transplant.py TARGET SIBLING [--out FILE] [--apply FILE.c] | --suggest")
    ap.add_argument("target", nargs="?")
    ap.add_argument("sibling", nargs="?")
    ap.add_argument("--out", help="write the draft here (default stdout)")
    ap.add_argument("--apply", metavar="FILE.c", help="also splice the draft into this C file (a worktree copy)")
    ap.add_argument("--no-check", action="store_true", help="skip the scratch compile + diff")
    ap.add_argument("--check", metavar="DRAFT", help="TARGET --check DRAFT: scratch compile + diff a hand-edited "
                    "draft file (scaffolded or bare C) instead of transplanting (with --apply: splice it)")
    ap.add_argument("--suggest", action="store_true", help="transplant every STRONG sibling pair in scratch, table")
    ap.add_argument("--min-score", type=float, default=0.45, help="--suggest: sibling score threshold (0.45)")
    ap.add_argument("--per", type=int, default=1, help="--suggest: siblings per target (default 1, the best)")
    ap.add_argument("-j", "--jobs", type=int, default=4)
    ap.add_argument("--lines", type=int, default=20, help="differing lines to print (default 20)")
    ap.add_argument("--keep", action="store_true", help="keep the scratch mirror(s)")
    ap.add_argument("--full", action="store_true", help="diff.py without -s (past the first jr ra)")
    args = ap.parse_args()
    os.makedirs(SCRATCH, exist_ok=True)
    if args.suggest:
        cmd_suggest(args)
    elif args.target and (args.sibling or args.check):
        cmd_one(args)
    else:
        ap.print_help()
        sys.exit(2)


if __name__ == "__main__":
    main()
