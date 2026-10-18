# F6 parked symbols - what is NOT renamed and why (2026-10-17 night session)

Ledger: matching_notes/renames.tsv (3,713 applied rows, resumable). Report of everything
deliberately left as a placeholder, so the next session can pick targets deliberately.

## 1. Farm-merge closure (blocked on the 5 open functions)
- 67 symbols in renames_protected.txt + the 5 functions themselves (func_8004A89C,
  func_80034348, func_8437B0CC, func_88304850, func_88805AEC).
- ~140 struct-field rows on the open drafts' structs (fragment24/61/62 headers etc.)
  were dropped by preflight during batch c1. After the functions match: harvest,
  unprotect, re-propose (rename_fields_inventory.tsv + rename_field_agent.py).

## 2. Species-stats follow-ups (from the s1 consolidation analysis, NOTES ROUND 11)
- PokemonStats (22630.h) field names are ROTATED by one relative to the true byte
  columns: baseSpecial(+7)=baseAttack, baseSpeed(+8)=baseDefense, baseDefense(+9)=baseSpeed,
  baseAttack(+0xA)=baseSpecial. Evidence: jump table at 0x8007C0D8 + 40-species
  byte-verified table + the HP-DV formula. Gameplay-observable -> owner decision.
- STAT_* defines in the same headers are likewise rotated (true order: ATTACK 2,
  DEFENSE 3, SPEED 4, SPECIAL 5); relabeling needs case-body reordering for byte-identity.
- D_8006FEE8 ("pmname_151" string) and D_80070F84 (folded alias base): dual-source
  (symbol_addrs + undefined_syms.ld) - never-touch, out of scope forever.
- D_8006FF00 was renamed gSpeciesDisplayTable (s1); its row 151 is the id-152 dummy row,
  not Mew (datamig_overrides.txt comment says otherwise - off by one).

## 3. Struct fields (Tier C remainder)
- Only globally-unique field names are renamable with today's rename.py (345 of 4,312
  fields across 652 typedefs; c1 applied 26, the rest either weak evidence or protected).
- ~2,500+ (typedef, field) pairs share names across 2+ structs (unk_00 in 475!). Needs
  struct-scoped field rows: extend rename.py with pycparser-based type-aware member
  rewriting, or per-file scoping. This is the main Tier C follow-up.
- Structs declared in .c files cannot take field rows today (decl rewrite is .h-only).

## 4. Locals (argN/spXX/temp_/var_)
- Parked by owner decision 2026-10-17 evening. Pure C-text rewrites, ROM-neutral;
  would need a --func-scoped row mode in rename.py.

## 5. Weak-evidence symbols (the bulk)
- ~4,500 func_ + ~4,650 D_ placeholders remain referenced in src/ (many are: symbols
  only in symbol_addrs with no src evidence, C statics, protected, or out-of-scope).
- Every wave's agents skipped what they could not name with evidence; re-running
  rename_agent.py on a file re-proposes only what still looks nameable. The RENAME
  recipe and driver are in matching_notes/rename_wave.py + RENAME_PLAN.md.

## 6. Out-of-scope classes (hard, by spec)
- undefined_syms.ld-defined symbols (639 assignments; renaming needs .ld edits on the
  never-touch list). Examples: D_80073267 (GetPokemonBaseStat table view).
- Asset VRAM anchors (D_[0-9A-F]000xxx).
- jtbl_*, fragment header/binary stubs, by-design names.
