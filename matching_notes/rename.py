#!/usr/bin/env python3
"""Symbol rename sweep tool (phase F6). See matching_notes/rename_spec.md.

Usage:
  rename.py plan   <ledger.tsv> [--batch B]         # pre-flight preview, zero writes
  rename.py apply  <ledger.tsv> [--batch B] [--sample N] [--no-make]
  rename.py revert <ledger.tsv> [--batch B]
  rename.py check  <symbol>
  rename.py export-upstream [--batch B] <ledger.tsv>
  rename.py mark-committed <ledger.tsv> <sha> [--batch B]   # set applied@<sha>, then amend yourself

Run with .venv/bin/python3. stdlib only. The ledger is matching_notes/renames.tsv:
  old<TAB>new<TAB>batch<TAB>also<TAB>justification<TAB>status
Field rows use dotted paths in old/new (unk_D_800FD008.unk_00 -> BattleMon.monId); the `also`
column carries cluster pairs (unk_D_800FD008:MeshVerts). Status becomes `applied@<commit>`.
"""
import argparse
import os
import random
import re
import subprocess
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
REPO = os.path.dirname(HERE)
SA_FILES = [
    os.path.join(REPO, "linker_scripts/us/symbol_addrs_code.txt"),
    os.path.join(REPO, "linker_scripts/us/symbol_addrs_ultralib.txt"),
    os.path.join(REPO, "linker_scripts/us/symbol_addrs.txt"),
]
PROTECTED_FILE = os.path.join(HERE, "renames_protected.txt")
REWRITE_ROOTS = [os.path.join(REPO, "src"), os.path.join(REPO, "include"), os.path.join(REPO, "asm/us")]
AUTO_LDS = [
    os.path.join(REPO, "linker_scripts/us/auto/undefined_funcs_auto.ld"),
    os.path.join(REPO, "linker_scripts/us/auto/undefined_syms_auto.ld"),
    os.path.join(REPO, "build/linker_scripts/us/auto/undefined_funcs_auto.ld"),
    os.path.join(REPO, "build/linker_scripts/us/auto/undefined_syms_auto.ld"),
]
MAKE_ENV = dict(
    os.environ,
    PATH=f"{REPO}/.venv/bin:{os.path.expanduser('~')}/local/bin:/usr/local/bin:/usr/bin:/bin",
)
PLACEHOLDER_PREFIXES = ("func_", "D_", "jtbl_", "pad_", "unk_D_", "unk_func_")
EXPECT_PROGRESS = "97.9197"


def die(msg):
    print(f"rename.py: error: {msg}", file=sys.stderr)
    sys.exit(1)


def warn(msg):
    print(f"rename.py: warning: {msg}", file=sys.stderr)


# ---------------------------------------------------------------- ledger

class Row:
    __slots__ = ("old", "new", "batch", "also", "justification", "status", "lineno")

    def __init__(self, old, new, batch, also, justification, status, lineno):
        self.old, self.new, self.batch = old, new, batch
        self.also, self.justification, self.status = also, justification, status
        self.lineno = lineno

    def is_field_row(self):
        return "." in self.old or ":" in self.old


def read_ledger(path):
    rows = []
    if not os.path.exists(path):
        die(f"ledger not found: {path}")
    for lineno, raw in enumerate(open(path), 1):
        line = raw.rstrip("\n")
        if not line.strip() or line.lstrip().startswith("#"):
            continue
        if line.split("\t")[0].strip() == "old":  # header row
            continue
        parts = line.split("\t")
        if len(parts) < 6:
            die(f"{path}:{lineno}: expected 6 TSV fields, got {len(parts)}")
        old, new, batch, also, justification, status = (p.strip() for p in parts[:6])
        rows.append(Row(old, new, batch, also, justification, status, lineno))
    return rows


def parse_field(row):
    """old=TYPE.field or TYPE:field -> (old_type, old_field); same for new."""
    sep = ":" if ":" in row.old else "."
    a, b = row.old.split(sep, 1) if sep in row.old else (row.old, None)
    sep2 = ":" if ":" in row.new else "."
    c, d = row.new.split(sep2, 1) if sep2 in row.new else (row.new, None)
    if not b or not d:
        die(f"ledger:{row.lineno}: field row needs TYPE.field on both sides")
    return a, b, c, d


# ---------------------------------------------------------------- repo facts

def sa_definitions(name):
    """[(file, line_no, full_line)] for definition lines `name = 0x...`."""
    out = []
    for f in SA_FILES:
        if not os.path.exists(f):
            continue
        for i, line in enumerate(open(f), 1):
            if line.startswith(name + " ") and "=" in line:
                out.append((f, i, line.rstrip("\n")))
    return out


def already_named():
    """Every non-func_/non-D_ symbol defined in any symbol_addrs file (upstream-owned names)."""
    names = set()
    for f in SA_FILES:
        if not os.path.exists(f):
            continue
        for line in open(f):
            m = re.match(r"(\S+)\s*=", line)
            if m:
                n = m.group(1)
                if not n.startswith(("func_", "D_", "jtbl_", "pad_")):
                    names.add(n)
    return names


def load_protected():
    prot = set()
    if os.path.exists(PROTECTED_FILE):
        for line in open(PROTECTED_FILE):
            line = line.strip()
            if line and not line.startswith("#"):
                prot.add(line)
    return prot


_UNDEF_SYMS_CACHE = None


def undefined_syms_names():
    """Symbols assigned in linker_scripts/us/undefined_syms.ld (the never-touch file)."""
    global _UNDEF_SYMS_CACHE
    if _UNDEF_SYMS_CACHE is None:
        _UNDEF_SYMS_CACHE = set()
        p = os.path.join(REPO, "linker_scripts/us/undefined_syms.ld")
        if os.path.exists(p):
            for m in re.finditer(r"([A-Za-z_][A-Za-z0-9_]*)\s*=", open(p).read()):
                _UNDEF_SYMS_CACHE.add(m.group(1))
    return _UNDEF_SYMS_CACHE


def rewrite_files():
    out = []
    for root in REWRITE_ROOTS:
        for dirpath, _dirs, files in os.walk(root):
            for fn in sorted(files):
                if fn.endswith((".c", ".h", ".s")):
                    out.append(os.path.join(dirpath, fn))
    return out


def word_sub(name, new):
    return re.compile(r"(?<![A-Za-z0-9_])" + re.escape(name) + r"(?![A-Za-z0-9_])"), new


def repo_grep_count(name, files):
    """Word-boundary count of `name` across files."""
    pat = re.compile(r"(?<![A-Za-z0-9_])" + re.escape(name) + r"(?![A-Za-z0-9_])")
    n = 0
    for f in files:
        try:
            n += len(pat.findall(open(f, errors="replace").read()))
        except OSError:
            pass
    return n


def git(args, **kw):
    return subprocess.run(["git", "-C", REPO] + args, capture_output=True, text=True, **kw)


def git_status_dirty():
    r = git(["status", "--porcelain"])
    dirty = [l for l in r.stdout.splitlines()
             if l and not l.startswith("??") and "matching_notes/" not in l]
    return dirty


def s_path_for(func):
    """The nonmatchings .s path for an unmatched function, or None."""
    hits = []
    base = os.path.join(REPO, "asm/us/nonmatchings")
    for dirpath, _dirs, files in os.walk(base):
        if func + ".s" in files:
            hits.append(os.path.join(dirpath, func + ".s"))
    return hits[0] if len(hits) == 1 else (hits or None)


def dlabel_files(sym):
    """asm .s files containing a `dlabel sym` definition line."""
    hits = []
    base = os.path.join(REPO, "asm/us")
    pat = re.compile(r"^dlabel\s+" + re.escape(sym) + r"\s*$", re.M)
    for dirpath, _dirs, files in os.walk(base):
        for fn in files:
            if fn.endswith(".s"):
                p = os.path.join(dirpath, fn)
                if pat.search(open(p, errors="replace").read()):
                    hits.append(p)
    return hits


def dlabel_info(sym):
    """(file, address, size) from the .s after `dlabel sym`: address from the /* ADDR */ comment,
    size from the following `.space 0xN` (or the next dlabel's address). None if unparseable."""
    for f in dlabel_files(sym):
        text = open(f, errors="replace").read()
        lines = text.splitlines()
        for i, line in enumerate(lines):
            if re.match(r"^dlabel\s+" + re.escape(sym) + r"\s*$", line):
                addr = size = None
                rest = "\n".join(lines[i + 1:i + 6])
                m = re.search(r"/\*\s*([0-9A-Fa-f]{8})\s*\*/", rest)
                if m:
                    addr = int(m.group(1), 16)
                s = re.search(r"\.space\s+0x([0-9A-Fa-f]+)", rest)
                if s:
                    size = int(s.group(1), 16)
                if addr is not None and size is not None:
                    return f, addr, size
    return None


def pragma_count(func):
    pat = re.compile(re.escape(func) + r"\.s")
    n, files = 0, []
    for dirpath, _dirs, files_ in os.walk(os.path.join(REPO, "src")):
        for fn in files_:
            if fn.endswith(".c"):
                p = os.path.join(dirpath, fn)
                c = len(pat.findall(open(p, errors="replace").read()))
                if c:
                    n += c
                    files.append(p)
    return n, files


# ---------------------------------------------------------------- pre-flight

def preflight(rows, protected, named, allow_applied_skip=True):
    errors, warnings = [], []
    seen_old, seen_new = {}, {}
    for r in rows:
        tag = f"ledger:{r.lineno} ({r.old})"
        if allow_applied_skip and (r.status.startswith("applied") or r.status in ("tested", "noop")):
            continue
        if r.old == r.new:
            if r.status != "noop":
                errors.append(f"{tag}: old == new but status is not 'noop'")
            continue
        if r.is_field_row():
            for part in re.split(r"[.:]", r.old) + re.split(r"[.:]", r.new):
                if not re.fullmatch(r"[A-Za-z_][A-Za-z0-9_]*", part):
                    errors.append(f"{tag}: invalid field-path component {part!r} in {r.old!r} -> {r.new!r}")
        elif not re.fullmatch(r"[A-Za-z_][A-Za-z0-9_]*", r.new):
            errors.append(f"{tag}: invalid identifier {r.new!r}")
            continue
        if r.new.startswith(PLACEHOLDER_PREFIXES):
            errors.append(f"{tag}: new name {r.new!r} looks like a placeholder")
        if r.old in protected:
            errors.append(f"{tag}: {r.old} is protected (renames_protected.txt)")
        if r.old in undefined_syms_names():
            errors.append(f"{tag}: {r.old} is defined in linker_scripts/us/undefined_syms.ld"
                         " (never-touch; out of scope per rename_spec.md)")
        if r.is_field_row():
            # field rows are refused when their STRUCT type is protected (the farm-merge closure):
            # renaming members of a struct the open drafts use desyncs farm candidates.
            prefix = re.split(r"[.:]", r.old, 1)[0]
            if prefix in protected:
                errors.append(f"{tag}: field row on protected struct {prefix} (farm-merge closure)")
        if r.new in named or r.new in protected:
            errors.append(f"{tag}: new name {r.new!r} is already in use / protected")
        if r.old in seen_old:
            errors.append(f"{tag}: duplicate old {r.old} (also line {seen_old[r.old]})")
        seen_old[r.old] = r.lineno
        if r.new in seen_new:
            errors.append(f"{tag}: duplicate new {r.new!r} (also line {seen_new[r.new]})")
        seen_new[r.new] = r.lineno
        # typedef / struct-tag collision in include/
        for f in rewrite_files():
            if not f.endswith(".h"):
                continue
            t = open(f, errors="replace").read()
            if re.search(r"(typedef[^;{]*|struct\s+|union\s+|\}\s*)" + re.escape(r.new) + r"\s*[;{]", t):
                errors.append(f"{tag}: {r.new!r} collides with a typedef/tag in {os.path.relpath(f, REPO)}")
                break
        if r.is_field_row():
            continue
        is_typedef = False
        for f in rewrite_files():
            if not f.endswith((".c", ".h")):
                continue
            if re.search(r"\}\s*" + re.escape(r.old) + r"\s*;", open(f, errors="replace").read()):
                is_typedef = True
                break
        defs = sa_definitions(r.old)
        if is_typedef:
            pass  # C-level typedef: no symbol_addrs/dlabel expectations
        elif len(defs) == 0:
            # fragment bss/data symbols are dlabel-defined in asm, not in symbol_addrs:
            # the rewrite adds a symbol_addrs entry so the name survives `make extract`
            if len(dlabel_files(r.old)) == 0:
                # last fallback: C-defined file-scope statics (e.g. static pointers) - whole-word only
                if not r.is_field_row() and c_definition_count(r.old) == 0:
                    errors.append(f"{tag}: {r.old} not in symbol_addrs, no dlabel, no C definition")
            elif len(dlabel_files(r.old)) > 1:
                errors.append(f"{tag}: {r.old} dlabel'd in multiple asm files")
            else:
                info = dlabel_info(r.old)
                if info is None:
                    errors.append(f"{tag}: {r.old} dlabel present but unparseable")
        elif len(defs) > 1:
            errors.append(f"{tag}: {r.old} defined in multiple symbol_addrs files")
        if sa_definitions(r.new):
            errors.append(f"{tag}: {r.new!r} already defined in a symbol_addrs file")
        if r.also:
            for pair in r.also.split(","):
                if ":" not in pair:
                    errors.append(f"{tag}: malformed also-pair {pair!r} (need old:new)")
                    continue
                a, b = pair.split(":", 1)
                if sa_definitions(b.strip()) or b.strip() in named:
                    errors.append(f"{tag}: also-pair target {b.strip()!r} already named/defined")
                if not re.fullmatch(r"[A-Za-z_][A-Za-z0-9_]*", b.strip()):
                    errors.append(f"{tag}: also-pair target {b.strip()!r} is not a valid identifier")
                if not re.fullmatch(r"[A-Za-z_][A-Za-z0-9_]*", a.strip()):
                    errors.append(f"{tag}: also-pair source {a.strip()!r} is not a valid identifier")
        m = re.fullmatch(r"func_([0-9A-Fa-f]{8})", r.old)
        if m:
            if len(defs) == 1 and not re.search(r"0[xX]" + m.group(1), defs[0][2], re.I):
                errors.append(f"{tag}: func_ suffix does not match address line: {defs[0][2]}")
            sp = s_path_for(r.old)
            pc, pfiles = pragma_count(r.old)
            if sp and pc == 1:
                pass  # unmatched: fine
            elif sp is None and pc == 0:
                hits = []
                base = os.path.join(REPO, "asm/us/nonmatchings")
                for dirpath, _d, fs in os.walk(base):
                    if r.old + ".s" in fs:
                        hits.append(dirpath)
                if not hits:
                    pass  # matched: fine
                else:
                    errors.append(f"{tag}: matched but stale .s exists")
            elif sp and pc == 0:
                errors.append(f"{tag}: .s exists but no GLOBAL_ASM pragma references it (matched since ledger written)")
                warnings.append(f"{tag}: would do refs-only rewrite")
            else:
                errors.append(f"{tag}: {pc} pragmas reference it (expected exactly 1)")
    return errors, warnings


# ---------------------------------------------------------------- rewrite

class Rewriter:
    def __init__(self):
        self.edits = {}       # path -> new content
        self.mvs = []         # (old_path, new_path)
        self.counts = {}      # symbol -> occurrences rewritten

    def _load(self, path):
        if path not in self.edits:
            self.edits[path] = open(path, errors="replace").read()
        return self.edits[path]

    def _save(self, path, text):
        self.edits[path] = text

    def rewrite_word(self, old, new, files, count_key=None):
        pat, repl = word_sub(old, new)
        n = 0
        for f in files:
            t = self._load(f)
            t2, k = pat.subn(repl, t)
            if k:
                self._save(f, t2)
                n += k
        self.counts[count_key or old] = self.counts.get(count_key or old, 0) + n
        return n

    def rewrite_member(self, old_field, new_field, files):
        """`.field` / `->field` accesses only, plus `TYPE field;` declarations in headers."""
        n = 0
        for f in files:
            t = self._load(f)
            t2, k1 = re.subn(r"(\.)" + re.escape(old_field) + r"(?![A-Za-z0-9_])", r"\g<1>" + new_field, t)
            t2, k2 = re.subn(r"(->)" + re.escape(old_field) + r"(?![A-Za-z0-9_])", r"\g<1>" + new_field, t2)
            if f.endswith(".h"):
                t2, k3 = re.subn(r"^(\s*[A-Za-z_][A-Za-z0-9_ ]*?\s)" + re.escape(old_field) + r"\s*;",
                                 r"\g<1>" + new_field + ";", t2, flags=re.M)
            else:
                k3 = 0
            if k1 + k2 + k3:
                self._save(f, t2)
                n += k1 + k2 + k3
        self.counts[old_field] = self.counts.get(old_field, 0) + n
        return n

    def rewrite_sa_line(self, old, new):
        for f in SA_FILES:
            if not os.path.exists(f):
                continue
            t = self._load(f)
            t2, k = re.subn(r"^" + re.escape(old) + r"(\s*=\s*)", new + r"\g<1>", t, flags=re.M)
            if k:
                self._save(f, t2)
                return k
        return 0

    def add_sa_entry(self, new, addr, size):
        """Append `new = 0xADDR; // defined:true size:0xSIZE` to symbol_addrs.txt (dlabel-only syms)."""
        f = SA_FILES[2]
        t = self._load(f)
        entry = f"{new} = 0x{addr:08X}; // defined:true size:0x{size:X}"
        if entry in t:
            return 0
        t = t.rstrip("\n") + "\n" + entry + "\n"
        self._save(f, t)
        return 1

    def commit(self):
        for path, text in self.edits.items():
            open(path, "w").write(text)
        return sorted(self.edits)

    def move_s(self, old_path, new_path):
        os.rename(old_path, new_path)
        self.mvs.append((old_path, new_path))


def do_rewrites(rows, files):
    rw = Rewriter()
    for r in rows:
        if r.is_field_row():
            ot, of, nt, nf = parse_field(r)
            if r.also:
                for pair in r.also.split(","):
                    a, b = pair.split(":")
                    rw.rewrite_word(a.strip(), b.strip(), files)
            rw.rewrite_member(of, nf, files)
            continue
        rw.rewrite_sa_line(r.old, r.new)
        rw.rewrite_word(r.old, r.new, files)
        if r.also:
            for pair in r.also.split(","):
                a, b = pair.split(":")
                rw.rewrite_word(a.strip(), b.strip(), files)
        if not sa_definitions(r.old):
            info = dlabel_info(r.old)
            if info:
                _f, addr, size = info
                rw.add_sa_entry(r.new, addr, size)
        sp = s_path_for(r.old)
        if sp and os.path.exists(sp):
            rw.move_s(sp, os.path.join(os.path.dirname(sp), r.new + ".s"))
    return rw


def undo(rw, touched):
    for p in touched:
        git(["checkout", "--", p])
    for old, new in rw.mvs:
        if os.path.exists(new) and not os.path.exists(old):
            os.rename(new, old)
    for p in AUTO_LDS:
        if os.path.exists(p):
            os.remove(p)


# ---------------------------------------------------------------- build gate

def build_gate(new_names, old_names, no_make=False, do_extract=True):
    if no_make:
        warn("--no-make: skipping the build gate (names NOT verified)")
        return True
    for p in AUTO_LDS:
        if os.path.exists(p):
            os.remove(p)
    if do_extract:
        r = subprocess.run(["make", "extract", f"PYTHON={REPO}/.venv/bin/python3"],
                           cwd=REPO, env=MAKE_ENV, capture_output=True, text=True, timeout=1800)
        if r.returncode != 0:
            print(r.stdout[-2000:], r.stderr[-1000:])
            return fail_reason("make extract failed")
    r = subprocess.run(["make", "-j8", f"PYTHON={REPO}/.venv/bin/python3"],
                       cwd=REPO, env=MAKE_ENV, capture_output=True, text=True, timeout=3600)
    out = r.stdout + r.stderr
    if r.returncode != 0 or "build/pokestadium-us.z64: OK" not in out:
        print(out[-2000:])
        return fail_reason("make failed or checksum not OK")
    mp = os.path.join(REPO, "build/pokestadium-us.map")
    mtext = open(mp, errors="replace").read()
    for n in old_names:
        if re.search(r"(?<![A-Za-z0-9_])" + re.escape(n) + r"(?![A-Za-z0-9_])", mtext):
            return fail_reason(f"map still contains old name {n}")
    for n in new_names:
        if not re.search(r"(?<![A-Za-z0-9_])" + re.escape(n) + r"(?![A-Za-z0-9_])", mtext):
            return fail_reason(f"map does not contain new name {n}")
    pr = subprocess.run([f"{REPO}/.venv/bin/python3", "progress.py", "-v", "us"],
                       cwd=REPO, capture_output=True, text=True, timeout=1200)
    if EXPECT_PROGRESS not in pr.stdout:
        print(pr.stdout[-1500:])
        return fail_reason(f"progress.py no longer reports {EXPECT_PROGRESS}%")
    print("gate: make OK (checksum verified), map cross-checked, progress.py unchanged")
    return True


def fail_reason(msg):
    print(f"gate: FAILED - {msg}")
    return False


# ---------------------------------------------------------------- commands

def select_batch(rows, batch):
    if not batch:
        return [r for r in rows if not r.status.startswith("applied")]
    return [r for r in rows if r.batch == batch and not r.status.startswith("applied")]


def cmd_plan(ledger, batch):
    rows = select_batch(read_ledger(ledger), batch)
    prot, named = load_protected(), already_named()
    errors, warnings = preflight(rows, prot, named)
    for w in warnings:
        warn(w)
    n_field = sum(1 for r in rows if r.is_field_row())
    print(f"{len(rows)} row(s) selected ({n_field} field rows); batch filter: {batch or '<all pending>'}")
    for r in rows:
        kind = "field" if r.is_field_row() else "sym  "
        print(f"  [{kind}] {r.old} -> {r.new}   ({r.justification[:60]})")
    if errors:
        print("\nPRE-FLIGHT ERRORS (no writes performed):")
        for e in errors:
            print("  " + e)
        sys.exit(1)
    print("\npre-flight clean; no writes performed (plan mode)")


def is_typedef_row(r, files=None):
    if r.is_field_row():
        return False
    for f in rewrite_files():
        if not f.endswith((".c", ".h")):
            continue
        if re.search(r"\}\s*" + re.escape(r.old) + r"\s*;", open(f, errors="replace").read()):
            return True
    return False


def c_definition_count(sym):
    """File-scope or local C definitions/declarations of `sym` (static or global, any array dims)."""
    pat = re.compile(
        r"^\s*(static\s+)?[A-Za-z_][A-Za-z0-9_ \t\*]*?\b" + re.escape(sym) +
        r"((\[[^\]]*\])*)\s*[;=]", re.M)
    n = 0
    for f in rewrite_files():
        if not f.endswith(".c"):
            continue
        if pat.search(open(f, errors="replace").read()):
            n += 1
    return n


def is_c_static(sym):
    """True if `sym` has a `static` C definition (file- or function-scope, any array dims).
    Such symbols never appear in the linker map, so the gate's map check skips them."""
    pat = re.compile(
        r"^\s*static\s+[A-Za-z_][A-Za-z0-9_ \t\*]*?\b" + re.escape(sym) +
        r"((\[[^\]]*\])*)\s*[;=]", re.M)
    for f in rewrite_files():
        if f.endswith(".c") and pat.search(open(f, errors="replace").read()):
            return True
    return False


def cmd_apply(ledger, batch, sample, no_make):
    rows = read_ledger(ledger)
    todo = select_batch(rows, batch)
    if not todo:
        die("no pending rows for this batch")
    prot, named = load_protected(), already_named()
    errors, warnings = preflight(todo, prot, named)
    for w in warnings:
        warn(w)
    if errors:
        print("PRE-FLIGHT ERRORS (aborted before any edit):")
        for e in errors:
            print("  " + e)
        sys.exit(1)
    dirty = git_status_dirty()
    if dirty:
        die(f"working tree not clean (commit or stash first): {dirty[:3]}")
    files = rewrite_files()
    real = [r for r in todo if r.old != r.new]
    noops = [r for r in todo if r.old == r.new]
    print(f"applying {len(real)} rename(s) ({len(noops)} no-op row(s) skipped)")
    sym_rows = [r for r in real if not r.is_field_row() and not is_typedef_row(r)  # pre-rewrite check
                 and not is_c_static(r.old)]
    rw = do_rewrites(real, files)
    touched = rw.commit()
    # post-rewrite checks
    problems = []
    for r in real:
        if r.is_field_row():
            _ot, of, _nt, nf = parse_field(r)
            checks = [(of, nf)]
        else:
            checks = [(r.old, r.new)]
        for old, new in checks:
            if repo_grep_count(old, rewrite_files()) and not r.is_field_row():
                problems.append(f"old symbol {old} still referenced after rewrite")
            if not r.is_field_row() and repo_grep_count(new, rewrite_files()) == 0:
                problems.append(f"new symbol {new} has zero references (orphan)")
    if problems:
        for p in problems:
            print("  " + p)
        undo(rw, touched)
        die("post-rewrite checks failed; batch reverted")
    if not build_gate([r.new for r in sym_rows], [r.old for r in sym_rows], no_make):
        undo(rw, touched)
        die("build gate failed; batch reverted")
    # ledger status
    upd = {r.lineno: r for r in todo}
    out = []
    for i, raw in enumerate(open(ledger), 1):
        line = raw.rstrip("\n")
        if i in upd and upd[i].old != upd[i].new:
            parts = line.split("\t")
            parts[5] = "applied"
            line = "\t".join(parts)
        out.append(line)
    open(ledger, "w").write("\n".join(out) + "\n")
    print(f"ledger updated: {len(real)} row(s) applied")
    if sample:
        print(f"\nspot-check sample ({sample} of {len(real)}):")
        for r in random.sample(real, min(sample, len(real))):
            print(f"  {r.old} -> {r.new}")
            print(f"    justification: {r.justification}")
    print(f"\ncommit with: git add -A ':!.claude' ':!scratch' && git commit -m 'rename: {batch or 'batch'} ({len(real)} symbols)'")
    print(f"then: {sys.executable} {__file__} mark-committed {ledger} $(git rev-parse --short HEAD)"
          f" --batch {batch or ''}".rstrip())


def cmd_revert(ledger, batch):
    rows = read_ledger(ledger)
    todo = [r for r in rows if (not batch or r.batch == batch) and r.status.startswith("applied")]
    if not todo:
        die("no applied rows to revert")
    inv = [Row(r.new, r.old, r.batch, r.also, r.justification, "pending", r.lineno) for r in todo]
    files = rewrite_files()
    rw = do_rewrites(inv, files)
    touched = rw.commit()
    if not build_gate([r.old for r in todo if not r.is_field_row()],
                      [r.new for r in todo if not r.is_field_row()]):
        undo(rw, touched)
        die("revert build gate failed; reverted the revert")
    upd = {}
    for r in todo:
        upd[r.lineno] = True
    out = []
    for i, raw in enumerate(open(ledger), 1):
        line = raw.rstrip("\n")
        if i in upd:
            parts = line.split("\t")
            parts[5] = "pending"
            line = "\t".join(parts)
        out.append(line)
    open(ledger, "w").write("\n".join(out) + "\n")
    print(f"reverted {len(todo)} row(s); ledger set back to pending")


def cmd_check(sym):
    prot, named = load_protected(), already_named()
    defs = sa_definitions(sym)
    print(f"symbol: {sym}")
    print(f"  protected: {sym in prot}   already-named: {sym in named}")
    for f, i, line in defs:
        print(f"  defined: {os.path.relpath(f, REPO)}:{i}: {line.strip()}")
    if not defs:
        print("  defined: nowhere in symbol_addrs*")
    sp = s_path_for(sym)
    if isinstance(sp, list):
        print(f"  .s: {sp}")
    elif sp:
        print(f"  .s: {os.path.relpath(sp, REPO)}")
    else:
        print("  .s: none (matched or data symbol)")
    pc, pfiles = pragma_count(sym)
    print(f"  GLOBAL_ASM pragmas: {pc}")
    n = repo_grep_count(sym, rewrite_files())
    print(f"  references across src/include/asm: {n}")
    if pfiles:
        for p in pfiles[:5]:
            print(f"    e.g. {os.path.relpath(p, REPO)}")


def cmd_export(ledger, batch):
    rows = read_ledger(ledger)
    for r in rows:
        if batch and r.batch != batch:
            continue
        if not r.status.startswith("applied"):
            continue
        also = f" [also: {r.also}]" if r.also else ""
        print(f"{r.old}\t{r.new}\t{r.batch}\t{r.status}\t{r.justification}{also}")


def cmd_mark(ledger, sha, batch):
    rows = read_ledger(ledger)
    lines = open(ledger).read().splitlines()
    for r in rows:
        if (not batch or r.batch == batch) and r.status == "applied":
            lines[r.lineno - 1] = lines[r.lineno - 1].replace("\tapplied", f"\tapplied@{sha}")
    open(ledger, "w").write("\n".join(lines) + "\n")
    print(f"marked batch {batch or '<all>'} as applied@{sha}; amend the commit with: git add -A ':!.claude' ':!scratch' && git commit --amend --no-edit")


def main():
    ap = argparse.ArgumentParser()
    sub = ap.add_subparsers(dest="cmd", required=True)
    p = sub.add_parser("plan")
    p.add_argument("ledger")
    p.add_argument("--batch")
    a = sub.add_parser("apply")
    a.add_argument("ledger")
    a.add_argument("--batch")
    a.add_argument("--sample", type=int, default=0)
    a.add_argument("--no-make", action="store_true")
    v = sub.add_parser("revert")
    v.add_argument("ledger")
    v.add_argument("--batch")
    c = sub.add_parser("check")
    c.add_argument("symbol")
    e = sub.add_parser("export-upstream")
    e.add_argument("ledger")
    e.add_argument("--batch")
    m = sub.add_parser("mark-committed")
    m.add_argument("ledger")
    m.add_argument("sha")
    m.add_argument("--batch")
    args = ap.parse_args()
    if args.cmd == "plan":
        cmd_plan(args.ledger, args.batch)
    elif args.cmd == "apply":
        cmd_apply(args.ledger, args.batch, args.sample, args.no_make)
    elif args.cmd == "revert":
        cmd_revert(args.ledger, args.batch)
    elif args.cmd == "check":
        cmd_check(args.symbol)
    elif args.cmd == "export-upstream":
        cmd_export(args.ledger, args.batch)
    elif args.cmd == "mark-committed":
        cmd_mark(args.ledger, args.sha, args.batch)


if __name__ == "__main__":
    main()
