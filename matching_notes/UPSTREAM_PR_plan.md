# Upstream PR split plan (F5, 2026-10-17)

Base: `origin/master` (6995f32) is already an ancestor of `match-round-1` (308 commits ahead) -
no rebase needed unless upstream moves before we push.

## Rules
- `matching_notes/` does NOT go upstream (owner decision 4 pending; the scripts are Palmetto- and
  workflow-specific). Every PR branch must therefore drop the matching_notes parts of commits.
- Files with still-open functions (src/4A3E0.c, src/33FE0.c, fragments/15, /24, /28, /62
  (361050)) go in AS-IS with their GLOBAL_ASM pragmas for the open functions - the normal decomp
  state; amend those PRs if the functions match before the push.
- Each branch must build OK standalone (`make` prints `build/pokestadium-us.z64: OK`).
- Series order: tools/data first (they define symbols used later), then code, then the
  owner-decision merges last (they change the repo's conventions: first linker alias, first
  unused-label stand-in).

## Branch series (stacked, in order)
1. `up/tools-data2c` - tools/data2c.py changes (struct layout generation used by the data
   migrations).
2. `up/data-main` - main-segment data migrations: yaml/symbol_addrs/undefined_syms + the
   src/data_*.c files (71BA0/72950/72A10/73700/7A1C0) + 703E0/71BA1/78220/78990/76A40/8D1A0
   owner-file data + 4A3E0 GB APU tables + the string-rodata blobs (7C1C0/7C220/7C750).
3. `up/main-segment-matches` - matched functions in main-segment files (12D80, 30640, 33FE0,
   3D140_2, 46680, 45720, ...), with the open functions left as GLOBAL_ASM.
4. `up/fragment-matches-a` - fragments 1 (incl. the 8E3E0 audio-state migration feeding
   func_81207DF8), 15, 16, 31, 41, 44, 47.
5. `up/fragment-matches-b` - fragments 6, 7, 23, 24, 26, 28.
6. `up/fragment62-matches` - fragments/62 (all six files).
7. `up/gfxhead-alias` - the round6-gfxhead-alias merge (gDisplayListHead linker alias; first
   symbol alias in the repo - needs the PR description to justify it).
8. `up/86a013c8-labels` - the round8-86A013C8-labels merge (eight unused labels as bss-ordering
   stand-ins).
9. Separate: decomp-permuter `sizeof` PR (see UPSTREAM_PR_permuter_sizeof.md; filed against
   simonlindholm/decomp-permuter, not this repo).

## PR descriptions
Every PR: one-line summary + the matched-function list + "verified with a byte-identical build"
(`make` -> OK). The alias/labels PRs must explain WHY the C is correct but the symbol layout
needs the trick (see NOTES.md history: uopt's one-range-per-global-symbol rule; IDO's .lcomm
hash ordering).

## Open items before pushing
- The three permuter-formatted functions (func_838043F8, func_88500A74, func_88807D04) are
  still pycparser-style; reformatting must preserve statement LINE NUMBERS (as1 schedules by
  .loc - see IDO_TRICKS "clang-format reflow breaks the ROM"). Defer to per-PR final passes.
- Owner: approve/adjust the split + decide on matching_notes/ and the Fable question for
  func_8437B0CC (decision 3).
