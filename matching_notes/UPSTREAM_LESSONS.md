# Upstream PR Lessons (michiiik/pokestadium #308)

## Process lessons

1. **Do a name-quality audit BEFORE pushing the first PR.** We pushed 627
   names with ~180 placeholder-quality entries (indexed suffixes, address
   fragments, "Custom" labels) that the reviewer immediately flagged. The
   audit should run: indexed suffixes, address fragments, non-semantic
   numbers, "Custom/Alt/Variant/Empty" without differentiators, and hex
   patterns that aren't known effect IDs.

2. **Read the CONTRIBUTING.md BEFORE proposing names.** The reviewer's
   first comment was about style guide compliance (s-prefix, domain
   prefixes, terminology). A pre-push lint against the style guide would
   have caught 90% of it. We built this lint AFTER the review.

3. **Their "s" prefix convention** (fragment-scoped statics) — we used "g"
   for everything. Their guide distinguishes game-wide (g) from
   fragment-local (s) globals. This was ~235 symbols to fix.

4. **Terminology is specific and non-obvious**: rotationX/Y/Z (not
   yaw/pitch/roll), COM (not AI for trainers), brought/picked (not
   party), Hall of Fame (not Victory Palace), BattleAi (specific casing).

5. **Don't rename empty-body functions.** The reviewer explicitly said
   "don't rename functions with no body since we can't make any
   determination on what they mean." We had 17.

6. **Be upfront about AI vs human contribution.** The reviewer asked
   directly and appreciated the honest answer (LLM-proposed, human-gated,
   deterministic joins for cross-refs). This calibrates their trust.

7. **Multi-version linker scripts**: each ROM version has its own
   symbol_addrs files. Renames must be applied to ALL versions, not just
   `us`. The ROM gate builds all 10 versions. We could only verify 3
   locally (us, us_rev1, us_rev2) — non-US builds need their Docker infra.

## Naming lessons

8. **Numbers in names must be semantic.** Effect IDs, file IDs, palette
   indices are semantic (they index real tables). Trailing digits without
   differentiators (SimpleBurst2, TriggerDefault1) are not — the number
   must tell you WHAT is different, not just THAT it's different.

9. **Strip hex IDs when you have the semantic replacement.** 
   LoadGfx28_Toxic → LoadGfxToxic. The ID is an implementation detail
   tied to archive layout. If you have the move name or behavior, the
   ID is noise.

10. **Multi-effect scripts need combined semantics, not concatenation.**
    "RegisterPaletteVariantsAndInitializeGroup" (two things listed) →
    "PaletteVariantsWithMotionGroup" (one combined concept). The "And"
    pattern is a code smell — it means you haven't found the combined
    semantic yet.

11. **"Custom" is never a name.** If you can't articulate what's
    different, you haven't investigated enough. Read the function body
    and describe the actual behavior.

12. **The reviewer's existing naming IS the convention.** We initially
    used our own patterns (Fragment62_Byte04) instead of following
    theirs (BattleAnim_StartEffectNN). Look at how they name siblings
    before proposing new names.

13. **Move names are the best semantic for move-associated data.**
    Cross-referencing sMoveAnimEffectScripts[moveId] with the Gen 1
    moveset turned LoadGfx34 into LoadGfxSmog. Always trace data back
    to what it's FOR.

## Technical lessons

14. **The michiiik tree builds all 10 ROM versions** from the same
    shared source. Each version has its own linker_scripts/{version}/
    directory with its own symbol_addrs files. The non-US builds need
    Docker infrastructure we can't replicate locally.

15. **The battle script VM is byte lists, not word-opcode programs.**
    Each byte is an independent effect ID dispatched through four tables
    (start/end × init/update). 879 ROM pointers verified against C
    symbol references with zero mismatches. Dead pool data after the
    0x00 terminator is common and misleading in source arrays.

16. **Their CI uses persistent pre-built Docker baselines**, not
    from-scratch builds. The multi-version gate reuses cached asm/
    assets/build/ per version. Local non-US builds need this
    infrastructure.

17. **make extract must run before linking after symbol renames.**
    The auto-generated linker script references symbol names; renaming
    without re-extracting causes "cannot find build/...o" errors.
