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
  channel; their ci/ dir didn't answer it from the clone. RESOLVED 2026-10-19: no pin -
  builds green with our toolchain once `make extract` runs first. Statics join executed:
  18 rows only; their statics tail is as nameless as ours (see RENAME_PLAN).
- Reorg residuals: groups 5/6/7/8/61 (gate failures), 1/31/77 (join problems),
  main-segment semantic rename, per-group un-joined yaml entries.
- Tier C shared-name struct fields: needs pycparser-scoped row tooling. As of c3
  (2026-10-19): 202 fields applied; the SHARED-NAME class now concretely includes
  11 fields dropped from c3 (old names also exist as members of structs declared
  INSIDE .c files, invisible to the .h-only inventory - e.g. MiniHudPlayerState in
  fragment6.c shares unk_176/unk_18A): otNames(box), currentMoveId, trainerLabel,
  next, cameraYaw, nicknameHeader, hurdleHitCount, finishRank, nameTagNode,
  voicedFramesRemaining, primColorB. Plus ~34 fields the Tier C agents skipped as
  unprovable (write-only counters, RSP-ucode-opaque constants, dead accessors -
  per-agent skip lists preserved in the session log summaries).
- 21 re-resolvable name collisions (list in hippo_name_conflicts.md).
- PokemonStats field rotation + STAT_* defines (evidence in NOTES round 11): owner call.
- MusyX family: OURS carries genuine SDK names vs their Audio_* - contribute upstream.
