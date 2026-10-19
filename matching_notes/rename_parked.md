# F6 parked symbols - what is NOT renamed and why (refreshed 2026-10-19)

Ledger: matching_notes/renames.tsv (16,435+ applied). Current truth: RENAME_PLAN.md
bottom sections. Old round-11 content is superseded - farm closure LIFTED (code 100%),
alias triple resolved (s1), func_80022734 renamed (ApplyPPUps).

## Blocked / by policy
- undefined_syms.ld-defined symbols (~530): renaming needs never-touch .ld edits.
- VRAM/segment addresses (7-hex D_ names): asset space, not symbols.
- Locals (argN/spXX/temp_): parked by owner decision 2026-10-17.
- jtbl_*, by-design binaries, already-named (upstream + our applied) symbols.

## Weak evidence / no source
- ~2,306 placeholders at last count, mostly C statics: statics-tail gemma waves are
  running (see RENAME_PLAN CURRENT STATE); the michiiik statics address-join is the
  bigger lever once their toolchain pin is answered.
- Symbols michiiik also lacks (~498 overlap): LLM-tail only.

## Follow-ups with decisions or work attached
- michiiik toolchain pin (build their tree for the statics map) - ask via the port
  channel; their ci/ dir didn't answer it from the clone.
- Reorg residuals: groups 5/6/7/8/61 (gate failures), 1/31/77 (join problems),
  main-segment semantic rename, per-group un-joined yaml entries.
- Tier C shared-name struct fields (~2.5k pairs): needs pycparser-scoped row tooling.
- 21 re-resolvable name collisions (list in hippo_name_conflicts.md).
- PokemonStats field rotation + STAT_* defines (evidence in NOTES round 11): owner call.
- MusyX family: OURS carries genuine SDK names vs their Audio_* - contribute upstream.
