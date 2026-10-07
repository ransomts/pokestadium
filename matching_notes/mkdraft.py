#!/home/tsranso/Code/pokestadium/.venv/bin/python3
"""mkdraft: m2c draft -> NON_MATCHING scaffold -> compile check -> diff score, all in scratch.

USAGE (repo root; repo venv python)
  .venv/bin/python3 matching_notes/mkdraft.py func_80049DF0
  .venv/bin/python3 matching_notes/mkdraft.py func_80033D44 --arg-types "a0=StadiumModel*"
  .venv/bin/python3 matching_notes/mkdraft.py func_80049DF0 --stack-structs        # one variant only
  .venv/bin/python3 matching_notes/mkdraft.py func_80049DF0 --flags "--no-casts"   # extra m2c flags
  .venv/bin/python3 matching_notes/mkdraft.py func_X --draft-file my.c             # skip m2c, check a draft
  .venv/bin/python3 matching_notes/mkdraft.py func_X --apply .claude/worktrees/w3/src/4A3E0.c
  .venv/bin/python3 matching_notes/mkdraft.py --missing                            # all draftless functions
  .venv/bin/python3 matching_notes/mkdraft.py --ctx-only src/4A3E0.c               # just build/repair the context
  options: --src src/file.c (default: the .c whose GLOBAL_ASM names FUNC), --out FILE (scaffold copy),
           --m2c PATH (m2c.py of matt-kempster/m2c; default scratch/mkdraft_dev/m2c/m2c.py or $MKDRAFT_M2C),
           --no-proto (do not give m2c the file's/draft's prototype), --keep (keep the scratch mirror),
           --show N (diff lines shown, default 15).

WHAT IT DOES
  1. Finds asm/us/nonmatchings/**/FUNC.s and the src/ .c that GLOBAL_ASMs it (never .claude/worktrees).
  2. Context: tools/m2ctx.py's import_c_file() (same cpp flags), written to
     scratch/mkdraft_dev/out/<FUNC>.ctx.c instead of the repo-root ctx.c. It is then parsed with
     pycparser the way m2c does (# lines dropped) and repaired from the parser's errors: a member line
     right before `}` without `;` (src/4A3E0.c `char unk2D[0x13]`) gets its `;`. Every repair and any
     unrepairable error is reported. The draft of FUNC itself is not in the context (NON_MATCHING is
     not defined for m2ctx), so a prototype is taken from the file/headers if one exists, else from
     the signature of FUNC's existing draft, and appended to the context (--no-proto: neither).
  3. --arg-types "a0=StadiumModel*,a1=s16,ret=void" (aN/argN = Nth parameter, not register):
     a prototype with those types is appended to the context (the arg count comes from the known
     prototype, else from a first m2c pass), so m2c types the accesses (field names) itself.
  4. m2c --target mips-ido-c --globals used --valid-syntax [--stack-structs] <flags> FUNC.s.
     Default: both with and without --stack-structs; the better score wins (both are reported).
     Post-processing: m2c's extern declarations of names the context already declares are dropped,
     the rest are kept and flagged; a guarded M2C_* macro block makes --valid-syntax output compile.
  5. Scaffold `#ifdef NON_MATCHING / // m2c draft <date>, flags ..., score N / ... / #else /
     #pragma GLOBAL_ASM(...) / #endif`, compiled in a scratch symlink mirror (ido_bisect.py's
     mirror(), with the exact `make -n -B build/src/<file>.o` command), the draft block enabled as
     `#if 1`. On compile errors, up to 4 fix rounds: `'X' undefined` -> `extern s32 X;` stub (flagged),
     jal targets with no declaration -> `s32 func_X();` (flagged). Then
     tools/asm-differ/diff.py -o FUNC -s --format plain -> score and number of differing lines.
     If FUNC already has a draft, that draft is compiled and scored too for comparison.
  6. --apply FILE writes the scaffold into FILE (replacing FUNC's GLOBAL_ASM line or its existing
     NON_MATCHING block; typedefs/comments before the old function stay; the old block is saved to
     scratch/mkdraft_dev/out/<FUNC>.prev.c). Never done by default.
  Outputs: scratch/mkdraft_dev/out/<FUNC>.{ctx.c, m2c.c, draft.c (scaffold), diff.txt}.

M2C. `.venv/bin/m2c` is NOT the decompiler: it is an unrelated PyPI package of the same name
(yangbinnnn/m2c, a Go swagger generator). The decompiler is https://github.com/matt-kempster/m2c,
used from a checkout (python3 m2c.py); point --m2c / $MKDRAFT_M2C at its m2c.py. It needs pycparser
(present in the venv).

LIMITATIONS: diff.py -s stops at the first jr ra; aN in --arg-types counts parameters, not argument
registers; auto-fixes only cover undefined identifiers and missing call prototypes, other cfe errors
are only reported; context repair only knows the missing-`;` pattern.
"""
import argparse
import datetime
import importlib.util
import os
import re
import shutil
import signal
import subprocess
import sys
import tempfile

REPO = os.path.abspath(os.path.join(os.path.dirname(os.path.abspath(__file__)), ".."))
DEV = os.path.join(REPO, "scratch", "mkdraft_dev")
OUT = os.path.join(DEV, "out")
NONM = os.path.join(REPO, "asm", "us", "nonmatchings")


def _load(name, path):
    spec = importlib.util.spec_from_file_location(name, path)
    mod = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(mod)
    return mod


IB = _load("ido_bisect", os.path.join(REPO, "matching_notes", "ido_bisect.py"))
PY = IB.PY

M2C_MACROS = """\
#ifndef M2C_FIELD /* mkdraft: m2c --valid-syntax helpers */
#define M2C_UNK s32
#define M2C_UNK8 s8
#define M2C_UNK16 s16
#define M2C_UNK32 s32
#define M2C_UNK64 s64
#define M2C_FIELD(expr, type, offset) (*(type)((u8*)(expr) + (offset)))
#define M2C_BITWISE(type, expr) ((type)(expr))
#define M2C_ERROR(desc) 0
#define M2C_TRAP_IF(cond) ((void)0)
#define M2C_BREAK() ((void)0)
#define M2C_SYNC() ((void)0)
#define M2C_CARRY 0
#define M2C_STRUCT_COPY(dst, src) ((dst) = (src))
#endif
"""


# ---------------------------------------------------------------- locating

def find_asm(func):
    for d, _, files in os.walk(NONM):
        if func + ".s" in files:
            return os.path.relpath(os.path.join(d, func + ".s"), REPO)
    return None


def src_files():
    for d, dirs, files in os.walk(os.path.join(REPO, "src")):
        dirs.sort()
        for f in sorted(files):
            if f.endswith(".c"):
                yield os.path.relpath(os.path.join(d, f), REPO)


def pragma_re(func):
    return re.compile(r'#pragma\s+GLOBAL_ASM\("([^"]*/%s\.s)"\)' % re.escape(func))


def find_src(func):
    r = pragma_re(func)
    for s in src_files():
        with open(os.path.join(REPO, s)) as f:
            if r.search(f.read()):
                return s
    return None


def draft_block(text, func):
    """-> (start, end, pragma_start, pragma_end, fn_start) of FUNC's `#ifdef NON_MATCHING ... #endif`
    block, or None if FUNC has only a bare GLOBAL_ASM. fn_start = start of the function definition."""
    m = pragma_re(func).search(text)
    if not m:
        return None
    head = text[: m.start()]
    # `#else` then only non-directive lines (prototypes the draft supplies otherwise) before the pragma
    em = re.search(r"#else[^\n]*\n((?:[ \t]*[^#\s][^\n]*\n|[ \t]*\n)*)[ \t]*$", head)
    if not em:
        return None
    extra = em.group(1)
    j = max(head.rfind("#ifdef NON_MATCHING"), head.rfind("#if defined(NON_MATCHING)"))
    if j < 0:
        return None
    fm = None
    for fm in re.finditer(r"^[^\n;#{}]*\b%s\s*\([^;{]*\)\s*\{" % re.escape(func), head[j:], re.M):
        break
    if not fm:
        return None
    e = text.find("#endif", m.end())
    e = text.index("\n", e) + 1 if e >= 0 else m.end()
    return j, e, m.start(), m.end(), j + fm.start(), extra


def missing_functions():
    """[(func, src)] for every GLOBAL_ASM in src/ that has no NON_MATCHING draft."""
    out = []
    for s in src_files():
        with open(os.path.join(REPO, s)) as f:
            text = f.read()
        for m in re.finditer(r'#pragma\s+GLOBAL_ASM\("[^"]*/(\w+)\.s"\)', text):
            if draft_block(text, m.group(1)) is None:
                out.append((m.group(1), s))
    return out


# ---------------------------------------------------------------- context

def build_context(src):
    """-> (ctx text, ast or None, [report lines])"""
    m2ctx = _load("m2ctx", os.path.join(REPO, "tools", "m2ctx.py"))
    old = os.getcwd()
    try:
        os.chdir(REPO)
        ctx = m2ctx.import_c_file(os.path.join(REPO, src))
    finally:
        os.chdir(old)
    return repair_context(ctx)


def strip_for_parse(ctx):
    # as m2c's parse_c: comments and preprocessor lines out (keep line numbering)
    def blank(m):
        s = m.group(0)
        return s if s[0] in "\"'" else re.sub(r"[^\n]", " ", s)
    ctx = re.sub(r'"(?:\\.|[^"\\\n])*"|\'(?:\\.|[^\'\\\n])*\'|/\*.*?\*/|//[^\n]*', blank, ctx, flags=re.S)
    return re.sub(r"^\s*#.*$", "", ctx, flags=re.M)


def repair_context(ctx):
    from pycparser import c_parser
    from pycparser.c_parser import ParseError
    notes = []
    lines = ctx.split("\n")
    for _ in range(50):
        try:
            ast = c_parser.CParser().parse(strip_for_parse("\n".join(lines)), "ctx.c")
            return "\n".join(lines), ast, notes
        except ParseError as e:
            msg = str(e)
            mm = re.match(r"[^:]*:(\d+):(\d+): (.*)", msg)
            if not mm:
                notes.append("context: UNREPAIRED parse error: " + msg)
                break
            ln = int(mm.group(1)) - 1
            fixed = False
            if 0 <= ln < len(lines) and (lines[ln].strip().startswith("}") or mm.group(3).strip() == "before: }"):
                k = ln - 1 if lines[ln].strip().startswith("}") else ln
                while k >= 0 and not lines[k].strip():
                    k -= 1
                prev = lines[k].rstrip()
                if k >= 0 and not prev.endswith((";", "{", "}", ",")) and re.search(r"[\w\]\)]$", prev):
                    lines[k] = prev + ";"
                    notes.append("context: repaired missing ';' after `%s` (ctx line %d)" % (prev.strip(), k + 1))
                    fixed = True
            if not fixed:
                bad = lines[ln].strip() if 0 <= ln < len(lines) else "?"
                notes.append("context: UNREPAIRED parse error: %s  [line: %s]" % (msg, bad[:120]))
                break
    return "\n".join(lines), None, notes


def ctx_names(ast):
    names = set()
    if ast is None:
        return names
    from pycparser import c_ast
    for n in ast.ext:
        if isinstance(n, c_ast.FuncDef):
            names.add(n.decl.name)
        elif getattr(n, "name", None):
            names.add(n.name)
    return names


def ctx_prototype(ast, func):
    """the context's declaration of func as C text, or None"""
    if ast is None:
        return None
    from pycparser import c_ast, c_generator
    for n in ast.ext:
        d = n.decl if isinstance(n, c_ast.FuncDef) else n
        if isinstance(d, c_ast.Decl) and d.name == func and isinstance(d.type, c_ast.FuncDecl):
            return c_generator.CGenerator().visit(d) + ";"
    return None


def split_proto(proto, func):
    """'T func(A a, B b);' -> (ret, [(type, name)]) ; name may be ''"""
    m = re.match(r"\s*(?:extern\s+)?(.*?)\s*\b%s\s*\((.*)\)\s*;?\s*$" % re.escape(func), proto, re.S)
    if not m:
        return None
    ret, params = m.group(1).strip(), m.group(2).strip()
    out = []
    if params and params != "void":
        for i, p in enumerate(split_commas(params)):
            p = p.strip()
            pm = re.match(r"(.*?[\s\*])(\w+)$", p)
            if pm and pm.group(1).strip() and pm.group(2) not in ("s8", "u8", "s16", "u16", "s32", "u32", "f32", "f64", "int", "char"):
                out.append((pm.group(1).strip(), pm.group(2)))
            else:
                out.append((p, "arg%d" % i))
    return ret, out


def split_commas(s):
    out, depth, cur = [], 0, ""
    for ch in s:
        if ch in "([":
            depth += 1
        elif ch in ")]":
            depth -= 1
        if ch == "," and depth == 0:
            out.append(cur)
            cur = ""
        else:
            cur += ch
    if cur.strip():
        out.append(cur)
    return out


def join_proto(ret, params, func):
    ps = ", ".join("%s %s" % (t, n) for t, n in params) if params else "void"
    return "%s %s(%s);" % (ret, func, ps)


def apply_arg_types(ret, params, spec):
    params = list(params)
    for item in [x for x in spec.split(",") if x.strip()]:
        k, v = item.split("=", 1)
        k, v = k.strip(), v.strip()
        if k == "ret":
            ret = v
            continue
        mm = re.fullmatch(r"(?:a|arg)(\d+)", k)
        if not mm:
            sys.exit("mkdraft: bad --arg-types key %r (use aN/argN/ret)" % k)
        i = int(mm.group(1))
        while len(params) <= i:
            params.append(("s32", "arg%d" % len(params)))
        params[i] = (v, params[i][1])
    return ret, params


# ---------------------------------------------------------------- m2c

def m2c_path(arg):
    p = arg or os.environ.get("MKDRAFT_M2C") or os.path.join(DEV, "m2c", "m2c.py")
    return p


def check_m2c(path):
    if not os.path.isfile(path):
        return ("m2c missing: no %s (clone https://github.com/matt-kempster/m2c there or pass --m2c; "
                ".venv/bin/m2c is an unrelated PyPI package)" % path)
    with open(path, errors="replace") as f:
        head = f.read(4000)
    if "yangbin" in head or "goswagger" in head:
        return "%s is the unrelated PyPI 'm2c' (yangbinnnn), not the decompiler" % path
    return None


def run_m2c(m2c, asm, ctxfile, stack_structs, flags):
    cmd = [PY, m2c, "--target", "mips-ido-c", "--context", ctxfile, "--globals", "used", "--valid-syntax"]
    if stack_structs:
        cmd.append("--stack-structs")
    cmd += flags + [os.path.join(REPO, asm)]
    p = subprocess.run(cmd, cwd=REPO, capture_output=True, text=True, env=IB.ENV)
    return p.returncode, p.stdout, p.stderr, cmd


def m2c_signature(code, func):
    m = re.search(r"^([^\n;]*\b%s\s*\([^)]*\))\s*\{" % re.escape(func), code, re.M)
    return m.group(1) + ";" if m else None


def postprocess(code, func, known):
    """drop m2c's extern decls of names the context declares; flag the others"""
    out, notes = [], []
    for line in code.split("\n"):
        s = re.sub(r"\s*(//.*|/\*.*?\*/)\s*$", "", line.strip())  # m2c tags decls `/* extern */`
        dm = None
        if s.endswith(";") and not line.startswith((" ", "\t")):
            dm = re.match(r"(?:extern\s+|static\s+)?[^=()]*?\b(\w+)\s*(?:\[[^\]]*\])*\s*;", s) or \
                re.match(r"(?:extern\s+|static\s+)?[^=]*?\b(\w+)\s*\([^)]*\)\s*;", s)
        if dm and dm.group(1) != func:
            if dm.group(1) in known:
                continue
            out.append(line + " /* mkdraft: m2c-inferred decl, not in context */")
            notes.append("kept m2c decl: " + s)
            continue
        out.append(line)
    code = "\n".join(out).strip("\n")
    code = code.replace("? ", "M2C_UNK ").replace("?*", "M2C_UNK*")
    return code, notes


# ---------------------------------------------------------------- compile + diff

class Mirror:
    def __init__(self, src, keep):
        os.makedirs(os.path.join(DEV, "runs"), exist_ok=True)
        self.base = tempfile.mkdtemp(prefix="run_", dir=os.path.join(DEV, "runs"))
        self.keep = keep
        self.src = src
        self.obj = "build/" + src[:-2] + ".o"
        IB.mirror(self.base, [os.path.dirname(src), os.path.dirname(self.obj)])
        self.argv = IB.compile_command(self.obj)

    def build(self, text, func):
        """-> (ok, errors[], diff output or None)"""
        sp = os.path.join(self.base, self.src)
        if os.path.lexists(sp):
            os.remove(sp)
        with open(sp, "w") as f:
            f.write(text)
        op = os.path.join(self.base, self.obj)
        if os.path.exists(op):
            os.remove(op)
        p = IB.run(self.argv, self.base)
        if p.returncode != 0 or not os.path.exists(op):
            raw = (p.stdout + p.stderr).splitlines()
            src_lines = text.split("\n")
            errs = []
            for l in raw:
                em = re.search(r"cfe: Error: [^,]*, line (\d+): (.*)", l)
                if em:
                    n = int(em.group(1))
                    code = src_lines[n - 1].strip() if 0 < n <= len(src_lines) else "?"
                    errs.append("line %d: %s   | %s" % (n, em.group(2).strip(), code[:100]))
            if not errs:
                errs = [l for l in raw if l.strip() and "Warning" not in l and not l.startswith("tools/ido")][-12:]
            return False, errs, None
        d = IB.run([PY, "-W", "ignore", "tools/asm-differ/diff.py", "-o", func, "-s", "--format", "plain"], self.base)
        return True, [], d.stdout + d.stderr

    def close(self):
        if not self.keep:
            shutil.rmtree(self.base, ignore_errors=True)


def insert_draft(text, func, block_body):
    """replace FUNC's GLOBAL_ASM line / NON_MATCHING block with `#if 1` + block_body + #else..."""
    m = pragma_re(func).search(text)
    pragma = m.group(0)
    blk = draft_block(text, func)
    new = "#if 1\n%s\n#else\n%s\n#endif\n" % (block_body, pragma)
    if blk:
        j, e, ps, pe, fs, extra = blk
        pre = text[text.index("\n", j) + 1: fs]  # typedefs/comments inside the old block
        return text[:j] + "#if 1\n" + pre + block_body + "\n#else\n" + extra + pragma + "\n#endif\n" + text[e:]
    eol = text.find("\n", m.end())
    eol = len(text) if eol < 0 else eol + 1
    return text[: m.start()] + new + text[eol:]


def jal_targets(asm):
    with open(os.path.join(REPO, asm)) as f:
        return sorted(set(re.findall(r"\bjal\s+(\w+)", f.read())))


def compile_draft(mir, base_text, func, draft, asm, known, verbose):
    """auto-fix loop. -> (ok, final draft, fixes[], errors[], diff output)"""
    fixes = []
    pre = []
    for t in jal_targets(asm):
        if t not in known and re.search(r"\b%s\s*\(" % re.escape(t), draft) and \
                not re.search(r"^(?!\s*return\b)[ \t]*[A-Za-z_][\w \t\*]*[\s\*]%s\s*\([^;{=]*\)\s*;" % re.escape(t),
                              draft, re.M):
            pre.append("s32 %s(); /* mkdraft: no prototype in context (jal target) */" % t)
            fixes.append("prototype stub for jal target " + t)
    errs = []
    for _ in range(5):
        body = (M2C_MACROS if "M2C_" in draft else "") + "\n".join(pre) + ("\n" if pre else "") + draft
        ok, errs, out = mir.build(insert_draft(base_text, func, body), func)
        if ok:
            return True, body, fixes, [], out
        new = []
        for e in errs:
            um = re.search(r"'(\w+)' undefined", e)
            if um and um.group(1) not in [x[1] for x in new]:
                n = um.group(1)
                stub = ("extern s32 %s; /* mkdraft stub: type unknown */" % n)
                if not any(("%s;" % n) in p for p in pre):
                    new.append((stub, n))
        if not new:
            break
        for stub, n in new:
            pre.append(stub)
            fixes.append("extern s32 stub for undefined " + n)
    return False, (M2C_MACROS if "M2C_" in draft else "") + "\n".join(pre) + ("\n" if pre else "") + draft, fixes, errs, None


def scaffold(func, pragma, body, flags_desc, score):
    hdr = "// m2c draft %s, flags %s, score %s" % (datetime.date.today().isoformat(), flags_desc, score)
    return "#ifdef NON_MATCHING\n%s\n%s\n#else\n%s\n#endif\n" % (hdr, body, pragma)


# ---------------------------------------------------------------- driver

def process(func, a, quiet=False):
    """-> dict(func, src, m2c_ok, compiles, score, lines, ...)"""
    say = (lambda *x: None) if quiet else print
    res = dict(func=func, src=None, m2c_ok=False, compiles=False, score=None, lines=None, note="")
    asm = find_asm(func)
    if not asm:
        res["note"] = "no .s under asm/us/nonmatchings"
        return res
    src = a.src or find_src(func)
    if src:
        src = os.path.relpath(os.path.abspath(os.path.join(REPO, src)), REPO) if not os.path.isabs(src) else os.path.relpath(src, REPO)
    res["src"] = src
    if not src:
        res["note"] = "no src/ file GLOBAL_ASMs it"
        defre = re.compile(r"^[^\n;#{}]*\b%s\s*\([^;{]*\)\s*\{" % re.escape(func), re.M)
        for s in src_files():
            with open(os.path.join(REPO, s)) as f:
                if defre.search(f.read()):
                    res["note"] += " (already C in %s: matched?)" % s
                    break
        return res
    with open(os.path.join(REPO, src)) as f:
        text = f.read()
    pm = pragma_re(func).search(text)
    if not pm:
        res["note"] = "%s has no GLOBAL_ASM for %s" % (src, func)
        return res
    pragma = pm.group(0)
    os.makedirs(OUT, exist_ok=True)
    say("%s: asm %s, src %s" % (func, asm, src))

    ctx, ast, notes = build_context(src)
    for n in notes:
        say("  " + n)
    known = ctx_names(ast)
    proto = None if a.no_proto else ctx_prototype(ast, func)
    proto_from = "context"
    blk = draft_block(text, func)
    if proto is None and not a.no_proto and blk:
        sig = re.match(r"[^{]*", text[blk[4]:]).group(0).strip()
        proto = re.sub(r"\s+", " ", sig) + ";"
        proto_from = "existing draft"
    if proto:
        say("  prototype (%s): %s" % (proto_from, proto))

    # draft source: m2c or --draft-file
    variants = []
    if a.draft_file:
        with open(a.draft_file) as f:
            variants.append(("draft-file " + os.path.basename(a.draft_file), f.read().strip("\n"), []))
        res["m2c_ok"] = None
    else:
        m2c = m2c_path(a.m2c)
        bad = check_m2c(m2c)
        if bad:
            res["note"] = bad
            say("  m2c: " + bad)
        else:
            ss_opts = [True] if a.stack_structs else [False] if a.no_stack_structs else [False, True]
            extra = a.flags.split() if a.flags else []
            for ss in ss_opts:
                p = proto
                ctxfile = os.path.join(OUT, func + ".ctx.c")
                if a.arg_types:
                    base = split_proto(p, func) if p else None
                    if base is None:  # first pass to learn the arg count
                        with open(ctxfile, "w") as f:
                            f.write(ctx)
                        rc, so, se, _ = run_m2c(m2c, asm, ctxfile, ss, extra)
                        sig = m2c_signature(so, func) if rc == 0 else None
                        base = split_proto(sig.replace("?", "s32").replace("M2C_UNK", "s32"), func) if sig else ("s32", [])
                    p = join_proto(*apply_arg_types(base[0], base[1], a.arg_types), func)
                    say("  prototype (--arg-types): " + p)
                with open(ctxfile, "w") as f:
                    f.write(ctx + ("\n" + p + "\n" if p else ""))
                rc, so, se, cmd = run_m2c(m2c, asm, ctxfile, ss, extra)
                fl = " ".join(["--stack-structs"] if ss else []) + (" " if ss and extra else "") + " ".join(extra)
                fl = fl or "default"
                if rc != 0 or not so.strip():
                    say("  m2c (%s) FAILED rc=%d: %s" % (fl, rc, (se or so).strip()[-800:]))
                    continue
                code, pnotes = postprocess(so, func, known - {func})
                with open(os.path.join(OUT, func + (".ss" if ss else "") + ".m2c.c"), "w") as f:
                    f.write(so)
                for n in pnotes:
                    say("  " + n)
                variants.append((fl, code, pnotes))
            res["m2c_ok"] = bool(variants)
    if not variants:
        return res

    mir = Mirror(src, a.keep)
    try:
        best = None
        for fl, code, _ in variants:
            ok, body, fixes, errs, out = compile_draft(mir, text, func, code, asm, known, not quiet)
            n_err = len(re.findall(r"M2C_ERROR", code))
            if ok:
                score, lines = IB.parse(out)
                say("  [%s] compiles; score %s, %d diff lines%s%s" % (
                    fl, score, len(lines), ("; fixes: " + "; ".join(fixes)) if fixes else "",
                    ("; %d M2C_ERROR" % n_err) if n_err else ""))
                cand = (score if score is not None else 10 ** 9, fl, body, fixes, out, lines, True)
            else:
                say("  [%s] does NOT compile%s:" % (fl, ("; tried: " + "; ".join(fixes)) if fixes else ""))
                for e in errs[:12]:
                    say("      " + e)
                cand = (10 ** 10, fl, body, fixes, "\n".join(errs), [], False)
            if best is None or cand[0] < best[0]:
                best = cand
        _, fl, body, fixes, out, lines, ok = best
        score = IB.parse(out)[0] if ok else None
        res.update(compiles=ok, score=score, lines=len(lines) if ok else None, flags=fl)
        sc = scaffold(func, pragma, body, fl, score if ok else "n/a (does not compile)")
        res["scaffold"] = sc
        with open(os.path.join(OUT, func + ".draft.c"), "w") as f:
            f.write(sc)
        with open(os.path.join(OUT, func + ".diff.txt"), "w") as f:
            f.write(out or "")
        if ok and not quiet:
            for l in lines[: a.show]:
                print("      " + l)
            if len(lines) > a.show:
                print("      ... (%d more; full diff in %s)" % (len(lines) - a.show, os.path.join(OUT, func + ".diff.txt")))
        # existing draft for comparison
        if blk and not quiet:
            j, e, ps, pe, fs, extra = blk
            old = text[:j] + "#if 1" + text[text.index("\n", j):]
            ok2, errs2, out2 = mir.build(old, func)
            if ok2:
                s2, l2 = IB.parse(out2)
                print("  existing draft in %s: score %s, %d diff lines  (regenerated: %s, %s)" % (
                    src, s2, len(l2), score, len(lines) if ok else "-"))
                res["existing"] = s2
            else:
                print("  existing draft does not compile: " + "; ".join(errs2[:3]))
    finally:
        mir.close()
    say("  scaffold: " + os.path.join(OUT, func + ".draft.c"))
    if a.out:
        shutil.copyfile(os.path.join(OUT, func + ".draft.c"), a.out)
        say("  copied to " + a.out)
    if a.apply:
        apply_to(a.apply, func, sc)
    return res


def apply_to(path, func, sc):
    path = os.path.abspath(path)
    with open(path) as f:
        text = f.read()
    m = pragma_re(func).search(text)
    if not m:
        sys.exit("mkdraft: --apply: %s has no GLOBAL_ASM for %s" % (path, func))
    blk = draft_block(text, func)
    if blk:
        j, e, ps, pe, fs, extra = blk
        with open(os.path.join(OUT, func + ".prev.c"), "w") as f:
            f.write(text[j:e])
        pre = text[text.index("\n", j) + 1: fs]
        sc = sc.replace("#else\n" + m.group(0), "#else\n" + extra + m.group(0))  # keep prototypes in #else
        sc_lines = sc.split("\n", 1)
        text = text[:j] + sc_lines[0] + "\n" + pre + sc_lines[1] + text[e:]
        print("  --apply: replaced the existing draft block in %s (old block saved to %s)" % (
            path, os.path.join(OUT, func + ".prev.c")))
    else:
        eol = text.find("\n", m.end())
        eol = len(text) if eol < 0 else eol + 1
        text = text[: m.start()] + sc + text[eol:]
        print("  --apply: replaced the GLOBAL_ASM line in " + path)
    with open(path, "w") as f:
        f.write(text)


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("func", nargs="?")
    ap.add_argument("--src")
    ap.add_argument("--flags", help="extra m2c flags (one string)")
    ap.add_argument("--stack-structs", action="store_true", help="only the --stack-structs variant")
    ap.add_argument("--no-stack-structs", action="store_true", help="only the plain variant")
    ap.add_argument("--arg-types", help='e.g. "a0=StadiumModel*,a1=s16,ret=void"')
    ap.add_argument("--no-proto", action="store_true")
    ap.add_argument("--draft-file", help="use this C function instead of running m2c")
    ap.add_argument("--m2c")
    ap.add_argument("--out")
    ap.add_argument("--apply")
    ap.add_argument("--missing", action="store_true")
    ap.add_argument("--ctx-only", metavar="SRC")
    ap.add_argument("--keep", action="store_true")
    ap.add_argument("--show", type=int, default=15)
    a = ap.parse_args()
    signal.signal(signal.SIGINT, lambda *x: sys.exit(1))
    signal.signal(signal.SIGTERM, lambda *x: sys.exit(1))

    if a.ctx_only:
        ctx, ast, notes = build_context(a.ctx_only)
        os.makedirs(OUT, exist_ok=True)
        p = os.path.join(OUT, os.path.basename(a.ctx_only)[:-2] + ".ctx.c")
        with open(p, "w") as f:
            f.write(ctx)
        for n in notes:
            print(n)
        print("%s: %s, %d top-level decls -> %s" % (a.ctx_only, "parses" if ast else "DOES NOT PARSE",
                                                    len(ast.ext) if ast else 0, p))
        return
    if a.missing:
        if a.apply or a.draft_file:
            ap.error("--missing takes neither --apply nor --draft-file")
        todo = missing_functions()
        print("%d open functions without a NON_MATCHING draft" % len(todo))
        rows = []
        for func, src in todo:
            a.src = src
            r = process(func, a, quiet=False)
            rows.append(r)
            print()
        yn = lambda v: "-" if v is None else ("yes" if v else "no")
        print("%-16s %-48s %-6s %-9s %-6s %-6s %s" % ("function", "file", "m2c", "compiles", "score", "lines", "flags/note"))
        for r in rows:
            print("%-16s %-48s %-6s %-9s %-6s %-6s %s" % (r["func"], r["src"] or "?", yn(r["m2c_ok"]), yn(r["compiles"]),
                                                          "-" if r["score"] is None else r["score"],
                                                          "-" if r["lines"] is None else r["lines"],
                                                          (r.get("flags") or r["note"])[:60]))
        return
    if not a.func:
        ap.error("need FUNC (or --missing / --ctx-only)")
    r = process(a.func, a)
    if r["note"]:
        print("  note: " + r["note"])
    if not r["compiles"]:
        sys.exit(1)


if __name__ == "__main__":
    main()
