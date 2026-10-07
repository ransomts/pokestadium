#!/home/tsranso/Code/pokestadium/.venv/bin/python3
"""ido_bisect: which IDO 7.1 pass made this compiler temp?  (pass-switch bisection for drafts)

USAGE (repo root; repo venv python)
  .venv/bin/python3 matching_notes/ido_bisect.py src/path/file.c func_XXXXXXXX   # default switch set (~30)
  .venv/bin/python3 matching_notes/ido_bisect.py src/... func_X --all            # every catalogued switch (~50)
  .venv/bin/python3 matching_notes/ido_bisect.py src/... func_X --only uopt-nordstore   # one switch, full diff
  .venv/bin/python3 matching_notes/ido_bisect.py src/... func_X --only "-Wo,-rege,6"    # any raw cc flag(s)
  .venv/bin/python3 matching_notes/ido_bisect.py --list                          # switch catalogue
  options: -j N parallel compiles (default 6; ~45 s for the default set at -j 8), --switches a,b,c,
           --full (diff.py without -s, i.e. past the first jr ra), --show N (detail lines, default 8),
           --keep (keep the scratch mirror).

WHAT IT DOES
  * Builds private mirrors of the repo under scratch/ido_bisect_XXXX/w<N>/ (symlinks; only the
    target .c and its build/ object dir are real files), so the repo's src/ and build/ are never
    touched, nothing needs restoring, and runs can go in parallel with other work. In the mirrored
    .c the `#ifdef NON_MATCHING` guarding the function (the block whose #else holds
    `#pragma GLOBAL_ASM(".../<func>.s")`) becomes a bare `#if 1`. Removed on exit (also on ^C).
  * The compile command is exactly what `make -n -B build/src/<file>.o` prints (asm-processor +
    preprocess.sh + IDO, with the file's own per-file OPTFLAGS, e.g. src/C030.c keeps its
    -Wo,-loopunroll,0). A variant inserts its flags right after OPTFLAGS (-O1 replaces -O2). This
    equals `make build/src/<file>.o OPTFLAGS="-O2 <switch>"` (verified: the Makefile takes OPTFLAGS
    from the command line), minus the per-file flags that a command-line OPTFLAGS would drop.
  * Diffs with `tools/asm-differ/diff.py -o <func> -s --format plain` (as fd.sh) and objdumps our
    function (with source lines) and the target (expected/build/...) for the slot maps.

OUTPUT
  Header: baseline score, then "stores per stack slot" for TARGET and OURS: `0x24:v1@L1294` = the
  slot 0x24 is written from v1 by code of source line 1294 (arg homes / callee-saved saves left out;
  the target has no usable line info). A slot in the frame that nobody stores = a never-stored temp.
  Table, one row per switch:
    score, lines  diff.py score / number of differing lines vs the TARGET with that switch
    -van, +app    baseline diff lines that vanished / new diff lines (offset- and line-number-blind).
                  Only meaningful when dOurs is small: a switch that rewrites the function makes
                  every old line "vanish".
    dOurs         how many of OUR instructions the switch changed vs the baseline build
    hit           how many baseline diff lines sit on instructions the switch changed
    stack         frame-size change and stack slots no longer / newly used
  Then, for switches with hit > 0 (smallest dOurs first): the slot map, vanished lines and the
  baseline -> switch hunks of our code. Finally: switches that changed code only elsewhere, and
  switches giving identical code.

READING IT (no switch is ever the answer - the target was built with the normal flags; a switch
tells you WHICH PASS owns the mismatching temp, then you change the SOURCE so that pass does what
it did for the original)
  * Look first for a switch with small dOurs and full hit: that pass alone owns the diff.
  * A switch that changes the NUMBER of temps (stack column shows a slot appearing/disappearing, or
    a slot in the frame becomes never-stored) tells you the class of the missing/extra temp:
      - uopt-nokpicopt / uopt-no_const_in_reg: constant/%hi-%lo address temps. Constants are (likely)
        rematerialised instead of spilled, so such a temp can own a slot that is NEVER STORED.
        Remedy: change where the address/constant is first formed (base pointer local
        `T *base = D_x;` vs `D_x[i]` at every use, `&D_x[i]` once vs repeated), which array base
        is CSE'd, or make the global a function static (IDO_TRICKS).
      - uopt-nordstore / uopt-norlodrstropt: register promotion of a memory variable (load at
        region entry, store at exit). Remedy: change aliasing - local copy of a global, take/drop
        the address of a local, move the store into/out of the loop, function static.
      - uopt-Olimit1 / cc-O1 (uopt off) only: a global-optimizer temp from PRE/CSE/strength
        reduction/LICM, which IDO 7.1 cannot switch off one by one (no -nocse, no -nostrength:
        uopt reports them as unrecognized). If the -O1 code matches the target at that spot, the
        original computed it where -O1 does: write it inline at the use, not in a named temp.
        A walking pointer in a stack slot for `arr[i]` (IDO_TRICKS func_80044EA4) is strength
        reduction: write `arr[i]` everywhere and drop the cursor local.
  * Compiler-temp slots are handed out top-down in order of each expression's FIRST appearance in
    the source (func_84367660), so once you know which expression owns the extra/missing slot,
    move its first appearance (a dead early copy works) to move the slot.
  * Register-only diffs that only big perturbations touch (uopt-rege*/regr*/doassoc/varref) while
    uopt-noprecolor/noheurAB/do_opt_saved_regs/no_r23 give identical code: a pure colouring
    priority tie in uopt. Priorities come from use counts, loop depth and live-range length: add or
    remove one use, reuse one variable for two values (func_80049A60), reorder independent
    statements (func_80013D34), swap operand order / association (doassoc touching it = the
    expression's association matters: try (a*2)+b vs b+(a*2), a+a vs a*2).
  * beql/bnel vs branch+nop owned by as1-nobopt / as1-no_branch_target: as1 delay-slot filling from
    the branch target. The CFG differs: invert the if, swap if/else, `if (x) {} else {...}`, or
    change the first statement of the target block.
  * Instruction ORDER owned by as1-noxbb / aggr_xbb / noglobal / nopeep / noswpipe: as1 scheduling;
    almost always a downstream effect of a register or dependency difference - fix registers first;
    statement order inside a basic block also reschedules.
  * Nothing touches the line: cfe/ugen level (types, casts, signedness, operand order, literal
    types 1 vs 1.0f, struct layout) - look at the C, not the optimizer.
  * Even a switch that makes the function match does not prove the file used it: only a per-file
    Makefile flag (like src/C030.c's -Wo,-loopunroll,0) can, and that needs the whole file to match.

WORKED EXAMPLES (2026-10-07)
  func_8430506C (score 16, slots one too low): target temps 0x28 sp28val, 0x24 sp40*4, 0x20 never
  stored, 0x1c &D_84390010[sp40]; ours 0x24/0x20/0x1c. Only uopt-nordstore and uopt-nokpicopt add a
  temp (stack "-0x20 +0x18": the extra slot is NEVER STORED, like the target's 0x20); everything
  else is identical or unrelated. So the target's unused temp is a rematerialisable constant/address
  temp (kpic: guess, %hi/%lo address handling), not a boolean temp: try making the D_84384570 /
  D_84390010 bases separate expressions (base locals, different first appearance) so the extra
  address temp is created between sp40*4 and the D address.
  func_84367660 (score 85, ft4/fa0 swap of a3_z and 2*a3_y, sp128 loads ft4 vs ft5): no narrow
  switch touches it (no_const_in_reg/nokpicopt/noprecolor/heurAB/saved_regs: identical or elsewhere;
  as1 switches only reorder); only rege/regr/doassoc/varref/Olimit reach it, and doassoc removes 6
  of the 14 lines -> it is a uopt colouring tie sensitive to how the a3_* * 2.0f sums associate.

SWITCH DISCOVERY. The binaries are ido-static-recomp builds whose MIPS data is word-swapped, so
plain `strings` shows "tpoubati" for "uoptitab"; scratch/bisect_dev/swapstrings.py un-swaps them.
`cc -show` gives the pass mapping: -Wo, = uopt, -Wc, = ugen, -Wb, (and -Wa) = as1. uopt answers an
unknown flag with "Warning: unrecognized option" and EXIT 0, so acceptance = exit 0 + object + no
such warning (scratch/bisect_dev/probe.py, probe function scratch/bisect_dev/t.c). -Wc,-O*/-Wb,-O*
are overridden by the driver's later -O2. See --list for the catalogue with what each did where.

LIMITATIONS: one .c per run; diff.py -s stops at the first jr ra (use --full for early-return
functions); the slot map only sees sp-relative stores with constant offsets; -van/+app are textual
and noisy for big rewrites; descriptions marked "guess" are inferred from names and observed
codegen, not from IDO documentation.
"""
import argparse
import concurrent.futures
import difflib
import os
import re
import shlex
import shutil
import signal
import subprocess
import sys
import tempfile
import threading

REPO = os.path.abspath(os.path.join(os.path.dirname(os.path.abspath(__file__)), ".."))
PY = os.path.join(REPO, ".venv", "bin", "python3")
OBJDUMP = os.path.expanduser("~/local/bin/mips-linux-gnu-objdump")
ENV = dict(os.environ)
ENV["PATH"] = ":".join([os.path.join(REPO, ".venv/bin"), os.path.expanduser("~/local/bin"),
                        "/usr/local/bin", "/usr/bin", "/bin"])

# name, cc flags, pass, effect (guess), where a codegen change was seen:
#   "t" = probe test function, "A" = func_8430506C, "B" = func_84367660, "" = nowhere
CATALOGUE = [
    # --- uopt (global optimizer), via -Wo, ---
    ("uopt-nounroll", "-Wo,-loopunroll,0", "uopt", "no loop unrolling (default factor 4); used per-file for src/C030.c", "t"),
    ("uopt-unroll2", "-Wo,-loopunroll,2", "uopt", "unroll by 2 instead of 4", "t"),
    ("uopt-unroll8", "-Wo,-loopunroll,8", "uopt", "unroll by 8 instead of 4", "t"),
    ("uopt-unrolllimit0", "-Wo,-unrolllimit,0", "uopt", "unrolled-body size limit 0 (= nounroll)", "t"),
    ("uopt-nomultibbunroll", "-Wo,-nomultibbunroll", "uopt", "do not unroll loops with a multi-block body", ""),
    ("uopt-nordstore", "-Wo,-nordstore", "uopt", "guess: no store elimination/sinking for register-promoted vars (more sw, different temps)", "tAB"),
    ("uopt-norlodrstropt", "-Wo,-norlodrstropt", "uopt", "guess: no rlod/rstr (register promotion load/store) optimisation", "tB"),
    ("uopt-no_const_in_reg", "-Wo,-no_const_in_reg", "uopt", "constants/%hi-%lo addresses are not CSE'd/hoisted into registers", "tAB"),
    ("uopt-do_opt_saved_regs", "-Wo,-do_opt_saved_regs", "uopt", "optimise callee-saved register use (s-reg vs spill choices)", "t"),
    ("uopt-doassoc", "-Wo,-doassoc", "uopt", "reassociate arithmetic for CSE/folding", "tB"),
    ("uopt-moremotion", "-Wo,-moremotion", "uopt", "more aggressive code motion (PRE / loop-invariant hoisting)", "tAB"),
    ("uopt-varref", "-Wo,-varref", "uopt", "guess: reference-based live ranges for colouring", "tAB"),
    ("uopt-no_r23", "-Wo,-no_r23", "uopt", "s7 (r23) not available to the allocator", "t"),
    ("uopt-nokpicopt", "-Wo,-nokpicopt", "uopt", "disable kpic opt (default on): address materialisation changes", "tA"),
    ("uopt-rege4", "-Wo,-rege,4", "uopt", "register budget 'e' = 4 (guess: expression/caller-saved regs)", "tAB"),
    ("uopt-rege16", "-Wo,-rege,16", "uopt", "register budget 'e' = 16 (every value >= 10 gives the same code, != default)", "tAB"),
    ("uopt-regr4", "-Wo,-regr,4", "uopt", "register budget 'r' = 4 (guess: callee-saved regs)", "tAB"),
    ("uopt-regr16", "-Wo,-regr,16", "uopt", "register budget 'r' = 16 (every value >= 10 gives the same code, != default)", "tAB"),
    ("uopt-Olimit1", "-Wo,-Olimit,1", "uopt", "function over Olimit -> uopt leaves it unoptimised (no CSE/PRE/SR/LICM/global colouring)", "tAB"),
    ("uopt-createbb", "-Wo,-createbb", "uopt", "guess: split blocks at calls/labels (changes CSE/temps across blocks)", "A"),
    ("uopt-docodehoist", "-Wo,-docodehoist", "uopt", "hoist code common to both arms of an if out of it", "A"),
    ("uopt-noPalias", "-Wo,-noPalias", "uopt", "pointer args may alias", ""),
    ("uopt-f77alias", "-Wo,-f77alias", "uopt", "Fortran aliasing rules", ""),
    ("uopt-domtag", "-Wo,-domtag", "uopt", "memory tags for alias analysis", ""),
    ("uopt-notail", "-Wo,-notail", "uopt", "no tail-recursion elimination", ""),
    ("uopt-nogenvreg", "-Wo,-nogenvreg", "uopt", "guess: no virtual-register generation", ""),
    ("uopt-norecur", "-Wo,-norecur", "uopt", "guess: assume no recursion", ""),
    ("uopt-noheurAB", "-Wo,-noheurAB", "uopt", "guess: colouring priority heuristic A/B off", ""),
    ("uopt-noprecolor", "-Wo,-noprecolor", "uopt", "no pre-colouring of args/results to a0-a3/v0", ""),
    ("uopt-docopy", "-Wo,-docopy", "uopt", "extra copy propagation", ""),
    ("uopt-strictIEEE", "-Wo,-strictIEEE", "uopt", "no unsafe FP folding", ""),
    # --- ugen (code generator), via -Wc, ---
    ("ugen-nooffsetopt", "-Wc,-nooffsetopt", "ugen", "no folding of constant offsets into base+offset addressing", "A"),
    ("ugen-notailopt", "-Wc,-notailopt", "ugen", "no tail-call/epilogue optimisation", ""),
    ("ugen-nocpalias", "-Wc,-nocpalias", "ugen", "guess: copy-propagation alias handling off", ""),
    ("ugen-nounsignedconv", "-Wc,-nounsignedconv", "ugen", "guess: no unsigned-conversion shortcut", ""),
    # --- as1 (assembler: scheduling, peephole, branch opt), via -Wb, ---
    ("as1-nobopt", "-Wb,-nobopt", "as1", "no branch optimisation (delay-slot fill from target / branch-likely)", "tAB"),
    ("as1-nopeep", "-Wb,-nopeep", "as1", "no peephole optimisation", "tAB"),
    ("as1-noswpipe", "-Wb,-noswpipe", "as1", "no software pipelining of loops", "t"),
    ("as1-noxbb", "-Wb,-noxbb", "as1", "no cross-basic-block scheduling", "tAB"),
    ("as1-aggr_xbb", "-Wb,-aggr_xbb", "as1", "aggressive cross-basic-block scheduling", "t"),
    ("as1-no_branch_target", "-Wb,-no_branch_target", "as1", "guess: do not pull instructions from branch targets", "tAB"),
    ("as1-nosymregs", "-Wb,-nosymregs", "as1", "guess: no register renaming during scheduling", "tB"),
    ("as1-noglobal", "-Wb,-noglobal", "as1", "no global (multi-block) scheduling", "tAB"),
    ("as1-multi_issue", "-Wb,-multi_issue", "as1", "schedule for a multi-issue CPU", "tAB"),
    ("as1-no_const_opts", "-Wb,-no_const_opts", "as1", "no constant-load optimisations", ""),
    ("as1-no_lui_opts", "-Wb,-no_lui_opts", "as1", "no lui merging", ""),
    ("as1-no_div_rem_opts", "-Wb,-no_div_rem_opts", "as1", "no div/rem expansion tricks", ""),
    ("as1-nopool", "-Wb,-nopool", "as1", "no literal pooling", ""),
    ("as1-newhilo", "-Wb,-newhilo", "as1", "new hi/lo hazard handling", ""),
    # --- whole driver (replace -O2) ---
    ("cc-O1", "-O1", "cc", "no uopt at all (ugen + as1 only)", "tAB"),
]
REJECTED = [
    ("-Wc,-fp32regs", "rejected (ugen: only legal for mips3)"),
    ("-noexpopt", "rejected (cc: malformed or unknown option)"),
    ("-O3 (cc)", "rejected by asm-processor (only -O0/-O1/-O2/-g); appended after -O2 it gave identical code"),
    ("-Wo,-nocse -nostrength -zcopy -zaloc ...", "uopt 'unrecognized option' (exit 0!) - no CSE / strength-reduction switch exists"),
    ("-Wc,-O0/-O1/-O3  -Wb,-O0/-O1/-O3", "accepted but no effect: the driver appends its own -O2 after -W args"),
    ("-Wc,-trapuv  -Wo,-trapuv", "accepted; ugen version adds uninitialised-var trap code (not useful)"),
    ("-Wo,-dowhyuncolor", "accepted; diagnostics only"),
    ("-Wo,-unrolllimit,N>=default  -Wo,-Olimit,N>=20", "accepted; same code as default on the probe"),
    ("-Wo,-static -kpicopt -fp32reg  -Wc,-cpalias -domtag  -Wb,-no_at_compression -fpstall_nop -force_branch_fixup",
     "accepted, no visible effect anywhere tested"),
    ("-noinline -nojmpopt -nouopt0 (cc)", "accepted, no effect on C at -O2"),
]
DEFAULT_SET = [c[0] for c in CATALOGUE if c[4] and c[0] != "uopt-unrolllimit0"]

DIFFLINE = re.compile(r"^\S*\s*[0-9a-f]+:\s.*\s(r|i|s|<|>|\|)\s")
SPREF = re.compile(r"(-?\d+)\(sp\)")


def run(cmd, cwd, **kw):
    return subprocess.run(cmd, cwd=cwd, env=ENV, capture_output=True, text=True, **kw)


def mirror(root, reldirs):
    """Make `root` a symlink mirror of REPO in which every directory on the way to each of `reldirs`
    is a real directory (so files can be replaced there) and everything else is a symlink."""
    real_dirs = {""}
    for rel in reldirs:
        parts = rel.split("/")
        for k in range(1, len(parts) + 1):
            real_dirs.add("/".join(parts[:k]))
    for d in sorted(real_dirs):
        os.makedirs(os.path.join(root, d), exist_ok=True)
        src = os.path.join(REPO, d)
        if not os.path.isdir(src):
            continue
        for e in os.listdir(src):
            rel = (d + "/" + e) if d else e
            if rel in real_dirs or e == ".git":
                continue
            dst = os.path.join(root, rel)
            if not os.path.lexists(dst):
                os.symlink(os.path.join(REPO, rel), dst)


def enable_draft(text, func):
    """Flip the `#ifdef NON_MATCHING` guarding `func` to a bare `#if 1`. Returns (text, how)."""
    m = re.search(r'#pragma\s+GLOBAL_ASM\("[^"]*/%s\.s"\)' % re.escape(func), text)
    if not m:
        return text, "no GLOBAL_ASM for this function: compiled as-is"
    head = text[: m.start()]
    j = max(head.rfind("#ifdef NON_MATCHING"), head.rfind("#if defined(NON_MATCHING)"))
    if j < 0 or not re.search(r"\b%s\s*\(" % re.escape(func), head[j:]):
        sys.exit("ido_bisect: no `#ifdef NON_MATCHING` draft of %s before its GLOBAL_ASM" % func)
    eol = text.index("\n", j)
    return text[:j] + "#if 1" + text[eol:], "draft enabled (#ifdef NON_MATCHING -> #if 1, in a scratch mirror only)"


def compile_command(obj):
    """The asm-processor + IDO command `make` runs for obj, as argv (cwd = repo root)."""
    p = run(["make", "-n", "-B", obj, "PYTHON=" + PY], REPO)
    src = obj[len("build/"):-2] + ".c"
    for line in p.stdout.splitlines():
        line = line.strip().lstrip("@")
        if "tools/ido/" in line and line.endswith(" " + src) and " -o " + obj + " " in line:
            return shlex.split(line)
    sys.exit("ido_bisect: no compile command for %s in `make -n`:\n%s%s" % (obj, p.stdout[-2000:], p.stderr[-2000:]))


def with_switch(argv, obj, flags):
    k = len(argv) - 1 - argv[::-1].index("-o")  # final "-o <obj>": the file's OPTFLAGS end right before it
    assert argv[k + 1] == obj
    head = list(argv[:k])
    extra = []
    for f in flags:
        if re.fullmatch(r"-O\d", f):  # optimisation level: replace, asm-processor allows only one
            i = max(i for i, t in enumerate(head) if re.fullmatch(r"-O\d", t))
            head[i] = f
        else:
            extra.append(f)
    return head + extra + argv[k:]


class Worker:
    def __init__(self, base, idx, src, obj, text):
        self.root = os.path.join(base, "w%d" % idx)
        os.makedirs(self.root)
        mirror(self.root, [os.path.dirname(src), os.path.dirname(obj)])
        srcpath = os.path.join(self.root, src)
        if os.path.lexists(srcpath):
            os.remove(srcpath)
        with open(srcpath, "w") as f:
            f.write(text)
        self.obj = obj

    def build_and_diff(self, argv, func, stop):
        """-> (plain diff.py output, our instructions [(addr, text)]) or (None, error text)"""
        objpath = os.path.join(self.root, self.obj)
        if os.path.exists(objpath):
            os.remove(objpath)
        p = run(argv, self.root)
        if p.returncode != 0 or not os.path.exists(objpath):
            errs = [l for l in (p.stdout + p.stderr).splitlines() if "Warning" not in l]
            return None, "\n".join(errs[-15:])
        cmd = [PY, "-W", "ignore", "tools/asm-differ/diff.py", "-o", func] + (["-s"] if stop else []) + ["--format", "plain"]
        d = run(cmd, self.root)
        return d.stdout + d.stderr, disasm(objpath, func)


def disasm(objpath, func, lines=True):
    p = run([OBJDUMP, "-d", "-l", "-r", "-z", "-Mreg-names=32", "--disassemble=" + func, objpath], REPO)
    insns = []
    line = None
    for l in p.stdout.splitlines():
        m = re.match(r"\s+([0-9a-f]+):\t[0-9a-f]{8} \t(.*)$", l)
        if m:
            t = re.sub(r"\s+", " ", m.group(2)).strip()
            if t.split(" ")[0][0] in "bj" and t.split(" ")[0] not in ("jr", "jalr"):
                t = re.sub(r",?[0-9a-f]+ <[^>]*>$", "", t)  # branch/jump target address: position-dependent
                t = re.sub(r",?\b[0-9a-f]+$", "", t)
            insns.append([int(m.group(1), 16), t, line if lines else None])
            continue
        m = re.match(r"^\S+:(\d+)( \(discriminator \d+\))?$", l)
        if m:
            line = int(m.group(1))
            continue
        m = re.match(r"\s+[0-9a-f]+: (R_MIPS_\w+)\s+(\S+)", l)
        if m and insns:
            insns[-1][1] += " <%s %s>" % (m.group(1)[7:], m.group(2))
    return insns


def parse(out):
    m = re.search(r"CURRENT \((-?\d+)\)", out) or re.search(r"Score:\s*(-?\d+)", out)
    score = int(m.group(1)) if m else None
    return score, [l.rstrip() for l in out.splitlines() if DIFFLINE.match(l)]


def key(line):
    """A diff line without offsets, branch targets and the source line-number column."""
    toks = line.split()
    out = []
    for i, t in enumerate(toks):
        if re.fullmatch(r"[0-9a-f]+:|\d+|~>", t) or (i + 1 < len(toks) and toks[i + 1] == "~>"):
            continue
        out.append(re.sub(r",[0-9a-f]+$", "", t) if i + 1 < len(toks) and toks[i + 1] == "~>" else t)
    return " ".join(out)


def multiset_minus(a, b):
    rest = [key(y) for y in b]
    out = []
    for x in a:
        kx = key(x)
        if kx in rest:
            rest.remove(kx)
        else:
            out.append(x)
    return out


def our_addr(line):
    """Our-side .text address of a plain diff line (None for target-only '<' rows)."""
    if re.search(r"\s<\s*$", line):
        return None
    ms = re.findall(r"(?:^|\s)([0-9a-f]+):\s", line)
    return int(ms[-1], 16) if ms else None


def compare_ours(base, var):
    """difflib over our instruction texts -> (n changed, changed baseline indices, hunks)"""
    a = [x[1] for x in base]
    b = [x[1] for x in var]
    sm = difflib.SequenceMatcher(None, a, b, autojunk=False)
    changed, hunks, n = set(), [], 0
    for tag, i1, i2, j1, j2 in sm.get_opcodes():
        if tag == "equal":
            continue
        n += max(i2 - i1, j2 - j1)
        changed.update(range(i1, max(i2, i1 + 1)))
        hunks.append((i1, a[i1:i2], b[j1:j2]))
    return n, changed, hunks


def frame_and_slots(insns):
    frame = None
    slots = set()
    for _, t, _l in insns:
        m = re.match(r"addiu sp,sp,(-\d+)$", t)
        if m and frame is None:
            frame = -int(m.group(1))
        for s in SPREF.findall(t):
            slots.add(int(s))
    return frame, slots


def slot_map(insns):
    """'0x1c:t5@L1298 0x20:v1@L1294 ...' - what is stored to each stack slot (not ra/s-reg saves,
    not the arg home area), with the source line when the object has line info."""
    frame, _ = frame_and_slots(insns)
    m = {}
    for _, t, line in insns:
        mm = re.match(r"(sw|sh|sb|swc1|sdc1) (\$?\w+),(-?\d+)\(sp\)", t)
        if not mm or (frame is not None and int(mm.group(3)) >= frame):
            continue
        reg = mm.group(2)
        if re.fullmatch(r"ra|s[0-8]|fp|\$?f(2[0-9]|3[01])", reg):  # callee-saved register saves
            continue
        lst = m.setdefault(int(mm.group(3)), [])
        tag = reg + ("@L%d" % line if line else "")
        if tag not in lst:
            lst.append(tag)
    return "  ".join("%s:%s" % (hex(k), ",".join(v[:3]) + ("+" if len(v) > 3 else "")) for k, v in sorted(m.items()))


def slot_summary(binsns, vinsns):
    bf, bs = frame_and_slots(binsns)
    vf, vs = frame_and_slots(vinsns)
    parts = []
    if bf != vf:
        parts.append("frame %s->%s" % (hex(bf) if bf else bf, hex(vf) if vf else vf))
    gone = sorted(bs - vs)
    new = sorted(vs - bs)
    if gone:
        parts.append("-" + ",".join(hex(x) for x in gone))
    if new:
        parts.append("+" + ",".join(hex(x) for x in new))
    return " ".join(parts)


def print_list():
    print("%-22s %-5s %-22s %-4s %s" % ("name", "pass", "flags", "seen", "effect (guess)   [* = in default set]"))
    for name, flags, pas, desc, seen in CATALOGUE:
        star = "*" if name in DEFAULT_SET else " "
        print("%-22s %-5s %-22s %-4s %s %s" % (name, pas, flags, seen or "-", star, desc + ("" if seen else "  [no visible effect seen]")))
    print("\nseen: t = probe function (scratch/bisect_dev/t.c), A = func_8430506C, B = func_84367660")
    print("\nrejected / not useful:")
    for f, why in REJECTED:
        print("  %-48s %s" % (f, why))


def main():
    ap = argparse.ArgumentParser(description="IDO pass-switch bisection (see the doc at the top of this file)")
    ap.add_argument("src", nargs="?")
    ap.add_argument("func", nargs="?")
    ap.add_argument("--list", action="store_true", help="print the switch catalogue")
    ap.add_argument("--only", help="one switch (catalogue name or raw cc flags), print the full diff")
    ap.add_argument("--all", action="store_true", help="every catalogued switch, not just the default set")
    ap.add_argument("--switches", help="comma-separated catalogue names")
    ap.add_argument("--full", action="store_true", help="do not pass -s (stop at first jr ra) to diff.py")
    ap.add_argument("--show", type=int, default=8, help="max lines per detail list")
    ap.add_argument("--keep", action="store_true", help="keep the scratch mirror")
    ap.add_argument("-j", type=int, default=6, help="parallel compiles")
    a = ap.parse_args()
    if a.list:
        print_list()
        return
    if not a.src or not a.func:
        ap.error("need <src/file.c> <func> (or --list)")
    src = os.path.relpath(os.path.abspath(a.src), REPO)
    if src.startswith("..") or not os.path.exists(os.path.join(REPO, src)):
        src = a.src
    if not os.path.exists(os.path.join(REPO, src)):
        sys.exit("ido_bisect: no such file " + src)
    obj = "build/" + src[:-2] + ".o"

    byname = {c[0]: c for c in CATALOGUE}
    if a.only:
        sel = [(a.only, (byname[a.only][1] if a.only in byname else a.only).split())]
    elif a.switches:
        sel = [(n, byname[n][1].split()) for n in a.switches.split(",")]
    elif a.all:
        sel = [(c[0], c[1].split()) for c in CATALOGUE]
    else:
        sel = [(n, byname[n][1].split()) for n in DEFAULT_SET]

    with open(os.path.join(REPO, src)) as f:
        text, how = enable_draft(f.read(), a.func)
    argv = compile_command(obj)
    os.makedirs(os.path.join(REPO, "scratch"), exist_ok=True)
    base = tempfile.mkdtemp(prefix="ido_bisect_", dir=os.path.join(REPO, "scratch"))

    def cleanup(*sig):
        if not a.keep:
            shutil.rmtree(base, ignore_errors=True)
        if sig:
            sys.exit(1)
    signal.signal(signal.SIGTERM, cleanup)
    signal.signal(signal.SIGINT, cleanup)
    try:
        nw = max(1, min(a.j, len(sel)))
        workers = [Worker(base, i, src, obj, text) for i in range(nw)]
        print("%s %s: %s" % (src, a.func, how))
        if a.keep:
            print("scratch mirror: " + base)
        bout, binsns = workers[0].build_and_diff(argv, a.func, not a.full)
        if bout is None:
            sys.exit("baseline build FAILED:\n" + binsns)
        bscore, blines = parse(bout)
        addr_index = {x[0]: i for i, x in enumerate(binsns)}
        bidx = [addr_index.get(our_addr(l)) for l in blines]

        free = list(workers)
        lock = threading.Lock()

        def job(item):
            with lock:
                w = free.pop()
            try:
                return item[0], w.build_and_diff(with_switch(argv, obj, item[1]), a.func, not a.full)
            finally:
                with lock:
                    free.append(w)

        with concurrent.futures.ThreadPoolExecutor(nw) as ex:
            results = dict(ex.map(job, sel))

        rows = []
        for name, flags in sel:
            out, vinsns = results[name]
            if out is None:
                rows.append((name, flags, None, vinsns))
                continue
            s, lines = parse(out)
            n, changed, hunks = compare_ours(binsns, vinsns)
            hit = sum(1 for i in bidx if i is not None and i in changed)
            van, app = multiset_minus(blines, lines), multiset_minus(lines, blines)
            rows.append((name, flags, dict(score=s, lines=lines, n=n, hunks=hunks, hit=hit, van=van, app=app,
                                           slots=slot_summary(binsns, vinsns), smap=slot_map(vinsns), out=out), None))

        if a.only:
            name, flags, r, err = rows[0]
            print("\n=== baseline: score %s, %d diff lines" % (bscore, len(blines)))
            for l in blines:
                print(l)
            if r is None:
                print("\n=== %s: BUILD FAILED\n%s" % (name, err))
                return
            print("\n=== %s (%s): score %s, %d diff lines; our code: %d insns changed, %d/%d baseline diff lines touched; stack %s"
                  % (name, " ".join(flags), r["score"], len(r["lines"]), r["n"], r["hit"], len(blines), r["slots"] or "same"))
            print(r["out"].rstrip())
            tinsns = disasm(os.path.join(REPO, "expected", obj), a.func, lines=False)
            print("\nstores per stack slot:\n  target:   %s\n  baseline: %s\n  switch:   %s"
                  % (slot_map(tinsns), slot_map(binsns), r["smap"]))
            print("\n--- VANISHED vs baseline (%d)" % len(r["van"]))
            for l in r["van"]:
                print("  " + l)
            print("--- APPEARED vs baseline (%d)" % len(r["app"]))
            for l in r["app"]:
                print("  " + l)
            print_hunks(r["hunks"], 10 ** 6)
            return

        tinsns = disasm(os.path.join(REPO, "expected", obj), a.func, lines=False)
        print("\nbaseline: score %s, %d diff lines, %d insns (target %d), frame %s (target %s)"
              % (bscore, len(blines), len(binsns), len(tinsns), hex(frame_and_slots(binsns)[0] or 0),
                 hex(frame_and_slots(tinsns)[0] or 0)))
        print("stores per stack slot (reg@source line; arg homes and callee-saved saves omitted):")
        print("  target: " + slot_map(tinsns))
        print("  ours:   " + slot_map(binsns))
        print("columns: score/lines = diff.py vs target; -van/+app = diff lines vanished/appeared vs baseline;")
        print("         dOurs = our instructions changed by the switch; hit = baseline diff lines among them; stack = slot changes\n")
        print("%-22s %-20s %6s %5s %4s %4s %5s %5s  %s" % ("switch", "flags", "score", "lines", "-van", "+app", "dOurs", "hit", "stack"))
        print("%-22s %-20s %6s %5d" % ("baseline", "(normal OPTFLAGS)", bscore, len(blines)))
        for name, flags, r, err in rows:
            if r is None:
                print("%-22s %-20s %6s" % (name, " ".join(flags), "FAIL"))
                continue
            tag = ""
            if r["n"] == 0:
                tag = "  (identical code)"
            elif r["score"] is not None and bscore is not None and r["score"] < bscore:
                tag = "  <-- better"
            print("%-22s %-20s %6s %5d %4d %4d %5d %2d/%-2d  %s%s" % (name, " ".join(flags), r["score"], len(r["lines"]),
                  len(r["van"]), len(r["app"]), r["n"], r["hit"], len(blines), r["slots"] if len(r["slots"]) <= 60 else r["slots"][:57] + "...", tag))
        # details: switches that touch the baseline diff, smallest change first
        touched = sorted([x for x in rows if x[2] is not None and x[2]["hit"]], key=lambda x: x[2]["n"])
        if touched:
            print("\n=== switches that change our code AT the baseline diff lines (smallest change first) ===")
        for name, flags, r, _ in touched[:6]:
            print("\n[%s %s] score %s, dOurs %d, hit %d/%d, stack %s" % (name, " ".join(flags), r["score"], r["n"], r["hit"],
                                                                     len(blines), r["slots"] or "same"))
            if r["slots"]:
                print("  slots: " + r["smap"])
            if r["van"]:
                print("  VANISHED:")
                for l in r["van"][: a.show]:
                    print("    - " + l)
            if r["app"] and len(r["app"]) <= a.show:
                print("  APPEARED:")
                for l in r["app"]:
                    print("    + " + l)
            elif r["app"]:
                print("  APPEARED: %d lines (run --only %s to see them)" % (len(r["app"]), name))
            print_hunks(r["hunks"], a.show)
        untouched = [x[0] for x in rows if x[2] is not None and x[2]["n"] and not x[2]["hit"]]
        if untouched:
            print("\nchange code elsewhere but not at the baseline diff lines: " + ", ".join(untouched))
        same = [x[0] for x in rows if x[2] is not None and not x[2]["n"]]
        if same:
            print("identical code: " + ", ".join(same))
    finally:
        cleanup()


def print_hunks(hunks, limit):
    shown = 0
    print("  our code, baseline -> with switch:")
    for i1, old, new in hunks:
        if shown >= limit:
            print("    ... %d more hunks" % (len(hunks) - hunks.index((i1, old, new))))
            break
        print("    @%d" % i1)
        for t in old:
            print("      - " + t)
        for t in new:
            print("      + " + t)
        shown += 1


if __name__ == "__main__":
    main()
