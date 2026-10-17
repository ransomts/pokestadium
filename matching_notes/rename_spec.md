# Symbol rename sweep — spec & runbook (phase F6)

Owner-approved 2026-10-17. Numbers measured against `match-round-1` at 97.92% code,
319 commits ahead of `origin/master`. Execute only after the current roadmap reaches
its F5 stop-for-approval point.

## 0. When to run / coordination
- Start condition: round 9 fully wrapped (F2 exit + integration + F4/F5 reached their
  stop), farm jobs and agent worktrees closed out.
- While renaming runs, THIS is the only builder: no parallel `make` from anything else
  (sessions share `build/`).
- Protected set (hard refuse, see `matching_notes/renames_protected.txt`): the round-9
  open functions until they match — `func_8004A89C func_80034348 func_8437B0CC
  func_88304850 func_88805AEC` — plus every already-named symbol (the ~438 named
  entries in `symbol_addrs_code.txt`, all of `symbol_addrs_ultralib.txt`, and the
  non-`D_`/non-`func_` names of `symbol_addrs.txt`). Never rename what upstream
  already named; follow its style (`Memmap_GetSegmentVaddr`, `gDisplayListHead`,
  `LEOcur_command`).
- By-design names never touched: `jtbl_*`, fragment headers/binary blobs, splat stubs.

## 1. Scale (measured)
| Category | Count |
|---|---|
| `func_*` in `symbol_addrs_code.txt` | 7,348 (of 7,787; 7,002 already referenced in `src/`) |
| `D_*` in `symbol_addrs.txt` | 1,227 (of 2,076); ~5,880 distinct `D_` used across `src/` |
| struct fields (`unk_XX`) + locals (`new_var*`, `spXX`, `argN`) | large; Tier C |

## 2. Safety argument
Symbol names never appear in the ROM. The only authority is `make` → exit 0 with the
`md5sum -c baseroms/us/checksum.md5` OK line (Makefile:318-319). A rename cannot break
byte-identity; it can only break the build, which the gate catches.
`expected/` is a diff-init reference, not a gate — refresh with `make diff-init` at each
wave end. `make extract` regenerates `asm/` from `yamls/` + `symbol_addrs*` (Makefile:353),
so `symbol_addrs` is the source of truth; keeping it and the `.s` files in sync makes
renames survive a future re-extract (verified by test 5).

## 3. Exact formats to handle
- `linker_scripts/us/symbol_addrs_code.txt`: `func_80034348 = 0x80034348; // type:func`
- `linker_scripts/us/symbol_addrs.txt`: `LEOPiInfo = 0x80100710; // defined:true size:0x4`
- nonmatchings asm: `glabel func_80034348`, refs as `jal NAME`, `%hi(NAME)`/`%lo(NAME)`,
  `.word NAME`; address/hex comment columns never contain `func_`/`D_` strings
- data asm (`asm/us/data/**`): `dlabel rspbootTextStart`
- C: prototypes, externs, typedefs (e.g. `unk_D_800FD008`), and
  `#pragma GLOBAL_ASM("asm/us/nonmatchings/33FE0/func_80034348.s")` path strings
- whole-word regex everywhere: `(?<![A-Za-z0-9_])NAME(?![A-Za-z0-9_])`

## 4. The tool: `matching_notes/rename.py`
Runtime `.venv/bin/python` (system python is 3.6 — unusable), stdlib only, ~400 lines,
matching_notes conventions (sys.exit diagnostics).

**Ledger** `matching_notes/renames.tsv` (TSV, resumable state):
`old<TAB>new<TAB>batch<TAB>also<TAB>justification<TAB>status` where `also` carries
cluster pairs (`unk_D_800FD008:MeshVerts`) and field rows use dotted paths
(`unk_D_800FD008.unk_00:BattleMon.monId`). Status becomes `applied@<commit>`.

**CLI**
```
rename.py plan   <ledger.tsv> [--batch B]        # full preview, zero writes (default posture)
rename.py apply  <ledger.tsv> [--batch B] [--sample N] [--no-make]
rename.py revert <ledger.tsv> [--batch B]        # inverse-apply from ledger
rename.py check  <symbol>                        # defined/referenced report
rename.py export-upstream [--batch B]            # per-symbol commit plan for F5 PR series
```

**Pre-flight (all-or-nothing per batch; abort before any edit)**
1. `old` in exactly one `symbol_addrs*` file; `new` in none
2. `new` valid identifier; no typedef/struct-tag collision in `include/`; style check
3. `func_XXXXXXXX` name suffix ↔ `= 0xXXXXXXXX`
4. not protected; `old != new`; no duplicate rows
5. unmatched `old`: `.s` exists + exactly one matching GLOBAL_ASM pragma;
   matched `old`: neither exists (else error)

**Rewrite pass** (per rename): symbol_addrs definition line (preserve comment);
whole-word identifier rewrite across `src/**/*.c`, `include/**/*.h`, `asm/us/**/*.s`
(glabel/dlabel/jal/%hi/%lo/.word covered by the same whole-word rule); pragma path
strings; `git mv` of `asm/us/nonmatchings/<group>/<old>.s` → `<new>.s`. Field rows
rewrite the header declaration plus `.field`/`->field` member accesses only.
Never touched: `build/`, `expected/`, `yamls/`, `linker_scripts/us/auto/`,
`undefined_syms.ld`, `oldnotes/`, `matching_notes/NOTES.md` (historical record).

**Post-rewrite checks**: repo-wide grep for `\b<old>\b` over the rewrite set = 0 hits;
each `new` ≥ 1 site (warn if orphan); pragma path ↔ `.s` filename 1:1.

**Build gate**: if make alone doesn't flow name changes into
`build/linker_scripts/us/auto/*.ld`, delete those generated artifacts first (test 1
decides); run `make`, require exit 0 + checksum OK line; cross-check the regenerated
`build/pokestadium-us.map`: `\b<old>\b` = 0 hits, `\b<new>\b` present; `progress.py`
still prints 97.9197% `all`. Any failure → auto-revert batch (git checkout + inverse
git mv), print first error, exit 1.

**Spot-check hook** (`--sample N`): print N random renames with justification + 3 lines
of context (C signature or glabel block). Owner reviews before next batch proceeds.

**Failure modes**: collisions/protected/duplicates abort pre-edit; `.s` present but no
pragma (matched since ledger written) → refs-only rewrite + warn; symbol in two
symbol_addrs files → hard error; prose mentions in non-rewrite files → left, noted.

## 5. Naming waves
- **Tier A (first)**: evidence-rich — already-named neighbors, `oldnotes/stadium1` +
  `stadiumgs` constants (moves/pokemon/types → enums/tables), strings, GB APU/audio
  clusters, libleo/libultra names reused verbatim.
- **Tier B**: per-fragment-group sweep, ~50–100 symbols per verified batch, names from
  call graphs + `accessmap.py` struct analysis.
- **Tier C**: struct fields + locals per file (dotted-path rows / `--func` scoping).
One commit per batch: `rename: <batch> (N symbols)` — ROM-neutral, cherry-pickable.

## 6. Test sequence (mandatory, in order, before any real batch)
1. No-op (`old=new` row) → 0 changes, make OK
2. Round-trip on a low-risk leaf function → `tmp_x` and back; make OK both ways; empty diff
3. Single rename: one function + one `D_` + its typedef cluster; make OK; ledger updated
4. Batch: ~20 symbols across one file group; make OK
5. Re-extract invariance (in a scratch worktree copy): `make extract` carries new names
6. Wave end: `make diff-init`

## 7. Upstream packaging
`export-upstream` emits name/justification per symbol. Submit only the evidence-rich
subset as separate name-only PRs in the F5 series (upstream rename commits are curated);
the rest stays fork-local, recorded in the ledger.

## 8. Out of scope
Renaming already-named symbols; `oldnotes/`; NOTES.md history; anything listed as
protected or by-design in §0.
