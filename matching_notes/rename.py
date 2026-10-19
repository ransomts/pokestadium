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
# also-pair sources that can never be real symbols: C keywords + the annotation
# tokens agents emit (`typedef:Name`). Rewriting these words would corrupt every
# declaration in the tree (the w10 build-gate lesson).
ALSO_PAIR_SOURCE_BLOCKLIST = {
    "auto", "break", "case", "char", "const", "continue", "default", "do",
    "double", "else", "enum", "extern", "float", "for", "goto", "if", "int",
    "long", "register", "return", "short", "signed", "sizeof", "static",
    "struct", "switch", "typedef", "union", "unsigned", "void", "volatile",
    "while", "type", "Type", "Struct", "Union", "Enum", "Callback", "Func",
}
EXPECT_PROGRESS = "98.8837"


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

_TEXT_CACHE = {}
_GREP_BLOB = None
_DEF_CLASSES = None
_HEADER_TAGS = None


def file_text(path):
    """Cached file read - preflight re-reads the whole repo per row otherwise.
    Invalidated by Rewriter.commit() after any write."""
    if path not in _TEXT_CACHE:
        _TEXT_CACHE[path] = open(path, errors="replace").read()
    return _TEXT_CACHE[path]


def _invalidate_text_cache():
    global _GREP_BLOB, _DEF_CLASSES, _HEADER_TAGS, _ASM_INDEX, _PRAGMA_INDEX
    _TEXT_CACHE.clear()
    _GREP_BLOB = None
    _DEF_CLASSES = None
    _HEADER_TAGS = None
    _ASM_INDEX = None
    _PRAGMA_INDEX = None


def sa_definitions(name):
    """[(file, line_no, full_line)] for definition lines `name = 0x...`."""
    out = []
    for f in SA_FILES:
        if not os.path.exists(f):
            continue
        for i, line in enumerate(file_text(f).splitlines(), 1):
            if line.startswith(name + " ") and "=" in line:
                out.append((f, i, line))
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
    """Word-boundary count of `name` across files (single joined-blob search)."""
    global _GREP_BLOB
    pat = re.compile(r"(?<![A-Za-z0-9_])" + re.escape(name) + r"(?![A-Za-z0-9_])")
    if _GREP_BLOB is None:
        chunks = []
        for f in files:
            try:
                chunks.append(file_text(f))
            except OSError:
                pass
        _GREP_BLOB = "\n".join(chunks)
    return len(pat.findall(_GREP_BLOB))


def git(args, **kw):
    return subprocess.run(["git", "-C", REPO] + args, capture_output=True, text=True, **kw)


def git_status_dirty():
    r = git(["status", "--porcelain"])
    dirty = [l for l in r.stdout.splitlines()
             if l and not l.startswith("??") and "matching_notes/" not in l]
    return dirty


_ASM_INDEX = None


def _asm_index():
    """{filename -> [paths]} under asm/us, built once (was: os.walk per call)."""
    global _ASM_INDEX
    if _ASM_INDEX is None:
        idx = {}
        for dirpath, _dirs, files in os.walk(os.path.join(REPO, "asm/us")):
            for fn in files:
                idx.setdefault(fn, []).append(os.path.join(dirpath, fn))
        _ASM_INDEX = idx
    return _ASM_INDEX


def s_path_for(func):
    """The nonmatchings .s path for an unmatched function, or None."""
    hits = _asm_index().get(func + ".s", [])
    return hits[0] if len(hits) == 1 else (hits or None)


def dlabel_files(sym):
    """asm .s files containing a `dlabel sym` definition line."""
    hits = []
    pat = re.compile(r"^dlabel\s+" + re.escape(sym) + r"\s*$", re.M)
    for dirpath, _dirs, files in os.walk(os.path.join(REPO, "asm/us")):
        for fn in files:
            if fn.endswith(".s"):
                p = os.path.join(dirpath, fn)
                if pat.search(file_text(p)):
                    hits.append(p)
    return hits


def dlabel_info(sym):
    """(file, address, size) from the .s after `dlabel sym`: address from the /* ADDR */ comment,
    size from the following `.space 0xN` (or the next dlabel's address). None if unparseable."""
    for f in dlabel_files(sym):
        text = file_text(f)
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


_PRAGMA_INDEX = None


def _pragma_index():
    """{func name -> (count, [files])} for GLOBAL_ASM `func.s` path references, one pass."""
    global _PRAGMA_INDEX
    if _PRAGMA_INDEX is None:
        idx = {}
        pat = re.compile(r"([A-Za-z_][A-Za-z0-9_]*)\.s")
        for dirpath, _dirs, files in os.walk(os.path.join(REPO, "src")):
            for fn in files:
                if not fn.endswith(".c"):
                    continue
                p = os.path.join(dirpath, fn)
                for m in pat.finditer(file_text(p)):
                    name = m.group(1)
                    e = idx.setdefault(name, [0, []])
                    e[0] += 1
                    if p not in e[1]:
                        e[1].append(p)
        _PRAGMA_INDEX = idx
    return _PRAGMA_INDEX


def pragma_count(func):
    e = _pragma_index().get(func)
    return (e[0], e[1]) if e else (0, [])


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
        # placeholder check: for field rows the TYPE half may still be a
        # placeholder (its rename is a separate row); only the FIELD part
        # of the new name must be semantic
        new_tok = r.new.rsplit(".", 1)[-1] if r.is_field_row() else r.new
        if new_tok.startswith(PLACEHOLDER_PREFIXES):
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
        if r.new in header_tag_names():
            errors.append(f"{tag}: {r.new!r} collides with a typedef/tag in a header")
        if r.is_field_row():
            continue
        is_typedef = r.old in _def_classes()[3]
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
                if a.strip() in ALSO_PAIR_SOURCE_BLOCKLIST:
                    warnings.append(f"{tag}: ignoring also-pair source {a.strip()!r} - "
                                    "C keyword (agent annotation noise); the row itself stands")
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
    """Defers whole-word/member/sa-line rewrites and applies them as ONE pass per file
    (batched alternation regex) - per-row scanning was O(rows x repo text)."""

    def __init__(self):
        self.edits = {}       # path -> new content
        self.mvs = []         # (old_path, new_path)
        self.counts = {}      # symbol -> occurrences rewritten
        self._word_map = {}
        self._member_map = {}
        self._sa_map = {}
        self._sa_appends = []  # (new, addr, size_or_None)
        self._batch_files = set()

    def _load(self, path):
        if path not in self.edits:
            self.edits[path] = open(path, errors="replace").read()
        return self.edits[path]

    def _save(self, path, text):
        self.edits[path] = text

    @staticmethod
    def _alt(names):
        return "|".join(sorted((re.escape(n) for n in names), key=len, reverse=True))

    def rewrite_word(self, old, new, files, count_key=None):
        self._word_map[old] = new
        self._batch_files.update(files)
        return 0

    def rewrite_member(self, old_field, new_field, files):
        """`.field` / `->field` accesses only, plus `TYPE field;` declarations in headers."""
        self._member_map[old_field] = new_field
        self._batch_files.update(files)
        return 0

    def rewrite_sa_line(self, old, new):
        self._sa_map[old] = new
        return 0

    def add_sa_entry(self, new, addr, size):
        self._sa_appends.append((new, addr, size))
        return 1

    def add_sa_entry_no_size(self, new, addr):
        """Entry without size: splat infers the span from its neighbours/segment end.
        Used for C-defined globals where a map-derived size could cross segment ends."""
        self._sa_appends.append((new, addr, "nosize"))
        return 1

    def add_sa_entry_undef(self, new, addr):
        """No-flag entry (NOT defined:true). For extern-only phantoms whose only
        definition is the auto .ld assignment: defined:true would suppress that
        assignment and break the link (the gStadiumUILayout/w29 lesson)."""
        self._sa_appends.append((new, addr, "undef"))
        return 1

    def _apply_batch(self, path, text):
        changed = False
        if self._word_map:
            pat = re.compile(r"(?<![A-Za-z0-9_])(?:" + self._alt(self._word_map) + r")(?![A-Za-z0-9_])")
            wmap = self._word_map

            def wsub(m):
                self.counts[m.group(0)] = self.counts.get(m.group(0), 0) + 1
                return wmap[m.group(0)]

            text, k = pat.subn(wsub, text)
            changed |= bool(k)
        if self._member_map:
            mmap = self._member_map

            def mrepl(m):
                return m.group(1) + mmap[m.group(2)]

            for pre in (r"(\.)", r"(->)"):
                pat = re.compile(pre + "(" + self._alt(self._member_map) + r")(?![A-Za-z0-9_])")
                text, k = pat.subn(mrepl, text)
                changed |= bool(k)
            if path.endswith(".h"):
                pat = re.compile(r"^(\s*(?:/\*[^*]*\*/\s*)?[A-Za-z_][A-Za-z0-9_ ]*?\s*\**\s*)("
                                 + self._alt(self._member_map) + r")((?:\[[^\]]*\])*)\s*;", re.M)
                text, k = pat.subn(lambda m: m.group(1) + mmap[m.group(2)] + m.group(3) + ";", text)
                changed |= bool(k)
        if changed:
            self._save(path, text)
        return changed

    def commit(self):
        # 1. symbol_addrs definition lines (batched, before appends)
        if self._sa_map:
            pat = re.compile(r"^(" + self._alt(self._sa_map) + r")(\s*=\s*)", re.M)
            smap = self._sa_map
            for f in SA_FILES:
                if os.path.exists(f):
                    t = self._load(f)
                    t2, _k = pat.subn(lambda m: smap[m.group(1)] + m.group(2), t)
                    if t2 != t:
                        self._save(f, t2)
        # 2. appended entries (dlabel-only / C-defined globals / extern-only phantoms)
        for new, addr, kind in self._sa_appends:
            f = SA_FILES[2]
            t = self._load(f)
            if kind == "undef":
                entry = f"{new} = 0x{addr:08X};"
            elif kind == "nosize":
                entry = f"{new} = 0x{addr:08X}; // defined:true"
            else:
                entry = f"{new} = 0x{addr:08X}; // defined:true size:0x{kind:X}"
            if entry not in t:
                self._save(f, t.rstrip("\n") + "\n" + entry + "\n")
        # 3. one batched pass per source file
        for path in sorted(self._batch_files):
            if os.path.exists(path):
                self._apply_batch(path, self._load(path))
        for path, text in self.edits.items():
            open(path, "w").write(text)
        _invalidate_text_cache()  # rewritten files: drop cached contents
        return sorted(self.edits)

    def move_s(self, old_path, new_path):
        os.rename(old_path, new_path)
        self.mvs.append((old_path, new_path))


_MAP_SPAN_CACHE = None


def map_symbol_span(name):
    """(addr, size) for `name` from build/pokestadium-us.map; size = gap to the next
    symbol address. None if absent. C-defined globals (no symbol_addrs entry, no dlabel)
    need a symbol_addrs entry after renaming, or every `make extract` re-derives the
    old placeholder name via spimdisasm auto-creation (fragment relocs etc.)."""
    global _MAP_SPAN_CACHE
    if _MAP_SPAN_CACHE is None:
        _MAP_SPAN_CACHE = {}
        sa_addrs = set()
        for f in SA_FILES:
            if os.path.exists(f):
                for m in re.finditer(r"^(\S+)\s*=\s*(0x[0-9a-fA-F]+)\s*;", file_text(f), re.M):
                    sa_addrs.add(int(m.group(2), 16))
        mp = os.path.join(REPO, "build/pokestadium-us.map")
        if os.path.exists(mp):
            entries = []
            for line in open(mp, errors="replace"):
                m = re.match(r"^\s+(0x[0-9a-fA-F]+)\s+([A-Za-z_][A-Za-z0-9_.]*)"
                            r"(\s+=\s+0x[0-9a-fA-F]+)?\s*$", line)
                if m:
                    entries.append((int(m.group(1), 16), m.group(2)))
            for i, (addr, sym) in enumerate(entries):
                if sym in _MAP_SPAN_CACHE:
                    continue
                nxt = next((a for a, _s in entries[i + 1:] if a > addr), None)
                sa_nxt = min((a for a in sa_addrs if a > addr), default=None)
                end = min(x for x in (nxt, sa_nxt) if x is not None) if (nxt or sa_nxt) else None
                _MAP_SPAN_CACHE[sym] = (addr, (end - addr) if end else 4)
    return _MAP_SPAN_CACHE.get(name)


def do_rewrites(rows, files):
    rw = Rewriter()
    # also-pairs FIRST, main-row word mappings AFTER: the word map is
    # last-writer-wins, and an agent can file a type annotation as an also
    # pair (`old:Struct`) - the main row must own that symbol's rename
    # (the w5 orphan lesson: everything became the literal word "Struct").
    # Keyword-source pairs (`typedef:Name`, the w10 lesson) are impossible
    # symbols - skip them so the keyword itself is never rewritten.
    for r in rows:
        if r.also:
            for pair in r.also.split(","):
                a, b = pair.split(":")
                if a.strip() in ALSO_PAIR_SOURCE_BLOCKLIST:
                    continue
                rw.rewrite_word(a.strip(), b.strip(), files)
    for r in rows:
        if r.is_field_row():
            ot, of, nt, nf = parse_field(r)
            rw.rewrite_member(of, nf, files)
            continue
        rw.rewrite_sa_line(r.old, r.new)
        rw.rewrite_word(r.old, r.new, files)
        if not sa_definitions(r.old):
            info = dlabel_info(r.old)
            if info:
                _f, addr, size = info
                rw.add_sa_entry(r.new, addr, size)
            elif not is_typedef_row(r):
                span = map_symbol_span(r.old)
                if span:
                    if has_c_definition(r.old):
                        rw.add_sa_entry_no_size(r.new, span[0])
                    else:
                        # extern-only phantom: its only definition is the auto .ld
                        # assignment - must NOT be marked defined:true (w29 lesson)
                        rw.add_sa_entry_undef(r.new, span[0])
        sp = s_path_for(r.old)
        if sp and os.path.exists(sp):
            rw.move_s(sp, os.path.join(os.path.dirname(sp), r.new + ".s"))
    return rw


def undo(rw, touched):
    for p in touched:
        git(["checkout", "--", p])
    _invalidate_text_cache()  # reverted files: drop cached contents
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
    r = subprocess.run(["make", "-j24", f"PYTHON={REPO}/.venv/bin/python3"],
                       cwd=REPO, env=MAKE_ENV, capture_output=True, text=True, timeout=3600)
    out = r.stdout + r.stderr
    if r.returncode != 0 or "build/pokestadium-us.z64: OK" not in out:
        open(os.path.join(REPO, "scratch", "gate_full.log"), "w").write(out)
        print(out[-2000:])
        return fail_reason("make failed or checksum not OK")
    mp = os.path.join(REPO, "build/pokestadium-us.map")
    mtext = open(mp, errors="replace").read()

    def names_in(names):
        alt = "|".join(sorted((re.escape(n) for n in names), key=len, reverse=True))
        return set(re.findall(r"(?<![A-Za-z0-9_])(?:" + alt + r")(?![A-Za-z0-9_])", mtext))

    if old_names:
        left = names_in(old_names)
        if left:
            return fail_reason(f"map still contains old name(s): {sorted(left)[:3]}")
    if new_names:
        got = names_in(new_names)
        missing = [n for n in new_names if n not in got]
        if missing:
            return fail_reason(f"map does not contain new name(s): {missing[:3]}")
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
    return r.old in _def_classes()[3]


def c_definition_count(sym):
    """File-scope or local C definitions/declarations of `sym` (static or global, any array dims)."""
    statics, globals_, locals_, _closers, _strict = _def_classes()
    return (sym in statics) + (sym in globals_) + (sym in locals_)


_HEADER_TAGS = None


def header_tag_names():
    """All typedef/struct/union/} names declared in headers (one pass)."""
    global _HEADER_TAGS
    if _HEADER_TAGS is None:
        names = set()
        pats = [re.compile(r"typedef[^;{]*?([A-Za-z_][A-Za-z0-9_]*)\s*[;{]"),
                re.compile(r"(?:struct|union)\s+([A-Za-z_][A-Za-z0-9_]*)\s*[;{]"),
                re.compile(r"\}\s*([A-Za-z_][A-Za-z0-9_]*)\s*;")]
        for f in rewrite_files():
            if not f.endswith(".h"):
                continue
            t = file_text(f)
            for p in pats:
                for m in p.finditer(t):
                    names.add(m.group(1))
        _HEADER_TAGS = names
    return _HEADER_TAGS


_DEF_CLASSES = None


def _def_classes():
    """One pass over all .c files -> (statics, globals, locals, typedef_closers).
    globals = column-0 declarations (incl. extern); locals = indented declarations."""
    global _DEF_CLASSES
    if _DEF_CLASSES is not None:
        return _DEF_CLASSES
    statics, globals_, locals_, closers, strict_globals = set(), set(), set(), set(), set()
    p_static = re.compile(r"^\s*static\s+[A-Za-z_][A-Za-z0-9_ \t\*]*?\b"
                          r"([A-Za-z_][A-Za-z0-9_]*)((?:\[[^\]]*\])*)\s*[;=]", re.M)
    p_global = re.compile(r"^(?:static\s+|extern\s+)?[A-Za-z_][A-Za-z0-9_ \t\*]*?\b"
                          r"([A-Za-z_][A-Za-z0-9_]*)((?:\[[^\]]*\])*)\s*[;=]", re.M)
    p_strict_global = re.compile(r"^(?!extern\b)(?:static\s+)?[A-Za-z_][A-Za-z0-9_ \t\*]*?\b"
                                 r"([A-Za-z_][A-Za-z0-9_]*)((?:\[[^\]]*\])*)\s*[;=]", re.M)
    p_local = re.compile(r"^[ \t]+[A-Za-z_][A-Za-z0-9_ \t\*]*?\b"
                         r"([A-Za-z_][A-Za-z0-9_]*)((?:\[[^\]]*\])*)\s*[;=]", re.M)
    # file-scope FUNCTION definitions (`TYPE name(args) {`) - the hs1 lesson: a
    # decompiled-but-untracked function (not in symbol_addrs, no .s, no dlabel)
    # still has a real C definition; the variable-only patterns miss it.
    p_func_def = re.compile(r"^(?!extern\b)(?:static\s+)?[A-Za-z_][A-Za-z0-9_ \t\*]*?\b"
                            r"([A-Za-z_][A-Za-z0-9_]*)\s*\([^;{}]*\)\s*\{", re.M)
    p_close = re.compile(r"\}\s*([A-Za-z_][A-Za-z0-9_]*)\s*;")
    for f in rewrite_files():
        if not f.endswith(".c"):
            continue
        t = file_text(f)
        for m in p_static.finditer(t):
            statics.add(m.group(1))
        for m in p_global.finditer(t):
            globals_.add(m.group(1))
        for m in p_strict_global.finditer(t):
            strict_globals.add(m.group(1))
        for m in p_local.finditer(t):
            locals_.add(m.group(1))
        for m in p_func_def.finditer(t):
            globals_.add(m.group(1))
            strict_globals.add(m.group(1))
        for m in p_close.finditer(t):
            closers.add(m.group(1))
    closers |= {n for n in header_tag_names()}
    _DEF_CLASSES = (statics, globals_, locals_, closers, strict_globals)
    return _DEF_CLASSES


def has_c_definition(sym):
    """True if sym has a non-extern C definition (static, file-scope or local).
    Extern-only declarations do NOT count - such symbols are linker phantoms."""
    statics, _globals_, _locals_, _closers, strict = _def_classes()
    return sym in statics or sym in strict or sym in _locals_


def is_typedef_row_fast(sym):
    return sym in _def_classes()[3]


def is_c_static(sym):
    """True if `sym` has a `static` C definition - absent from the linker map,
    so the gate's map check skips it."""
    return sym in _def_classes()[0]


def is_function_local(sym):
    """True if sym is declared ONLY inside function bodies (indented, non-static,
    no extern/file-scope definition) - also absent from the linker map."""
    statics, globals_, locals_, _closers, _strict = _def_classes()
    return sym in locals_ and sym not in globals_ and sym not in statics


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
        if no_make or os.environ.get("RENAME_ALLOW_DIRTY"):
            warn(f"working tree dirty (allowed): {dirty[:3]}")
        else:
            die(f"working tree not clean (commit or stash first): {dirty[:3]}")
    excl_env = os.environ.get("RENAME_EXCLUDE_FILES", "")
    exclude = {p for p in excl_env.splitlines() if p}
    if exclude:
        warn(f"excluding {len(exclude)} concurrently-dirty file(s) from the rewrite set")
    files = [f for f in rewrite_files() if f not in exclude] or rewrite_files()
    real = [r for r in todo if r.old != r.new]
    noops = [r for r in todo if r.old == r.new]
    print(f"applying {len(real)} rename(s) ({len(noops)} no-op row(s) skipped)")
    sym_rows = [r for r in real if not r.is_field_row() and not is_typedef_row(r)  # pre-rewrite check
                 and not is_c_static(r.old) and not is_function_local(r.old)]
    # extern-only phantoms (no linker definition anywhere - references are raw hex):
    # if the old name was not map-visible before the rewrite, don't map-check the new one
    if os.path.exists(os.path.join(REPO, "build/pokestadium-us.map")):
        sym_rows = [r for r in sym_rows if map_symbol_span(r.old) is not None]
    rw = do_rewrites(real, files)
    touched = rw.commit()
    # record the exact set so callers can scope their git add (concurrent sessions!)
    open(os.path.join(REPO, "scratch", "last_apply_touched.txt"), "w").write(
        "\n".join(touched) + "\n")
    # post-rewrite checks (batched: one blob scan for all olds, one for all news)
    blob_files = [f for f in rewrite_files() if f not in exclude] or rewrite_files()
    sym_real = [r for r in real if not r.is_field_row()]
    problems = []
    if sym_real:
        olds = {r.old for r in sym_real}
        news = {r.new for r in sym_real}

        def present(names):
            alt = "|".join(sorted((re.escape(n) for n in names), key=len, reverse=True))
            pat = re.compile(r"(?<![A-Za-z0-9_])(?:" + alt + r")(?![A-Za-z0-9_])")
            found = set()
            for f in blob_files:
                try:
                    found.update(pat.findall(file_text(f)))
                except OSError:
                    pass
                if found >= names:
                    break
            return found

        left = present(olds)
        for r in sym_real:
            if r.old in left:
                problems.append(f"old symbol {r.old} still referenced after rewrite")
        got = present(news)
        for r in sym_real:
            if r.new not in got:
                problems.append(f"new symbol {r.new} has zero references (orphan)")
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
