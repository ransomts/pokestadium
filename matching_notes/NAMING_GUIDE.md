# Symbol Naming Guide for Decompilation Projects

Synthesized from the michiiik/pokestadium PR #308 experience (615 renames,
multiple review iterations, ~30 tool-hardening cycles). This is the
methodology for going from `func_84306968` to a name a maintainer will
accept on first review.

## The One Rule

**A name should be as useful as possible.** Every character either adds
information or is noise. If you can remove a character without losing
meaning, remove it. If you can add a character that adds meaning, add it.

## Format Rules (from michiiik's CONTRIBUTING.md)

| Object | Style | Example |
|---|---|---|
| Game-wide globals | `gCamelCase` | `gPlayerController` |
| Fragment-scoped statics | `sCamelCase` | `sSideHpBar` |
| Functions | `{Domain}_{Purpose}` | `RentalHub_MenuLoop` |
| Structs | `TitleCase` | `HallOfFameSlot` |
| Local variables | `snake_case` | `cpu_pokemon` |

Additional rules:
- American English (color, mom)
- `BattleAi` domain casing (not BattleAI)
- COM for non-player trainers (not AI)
- rotationX/Y/Z (not yaw/pitch/roll — world-relative)
- brought/picked Pokemon (not party — "bring 6 pick 3" convention)
- Hall of Fame (not Victory Palace), Professor Oak's Lab, Minigames
- No non-ASCII in identifiers
- Up to ~50 characters tolerated ("more specific naming than most good practice")

## Methodology: How to Name a Symbol

### Level 1: Trace the usage
Read the function/data's body and every caller. Note:
- What values are written, read, compared
- What functions call it and in what context
- What tables it indexes into
- What parameters it passes to known functions

This gives you the BEHAVIOR. The name should describe the behavior.

### Level 2: Decode the dispatch
If the symbol is a table entry or script:
- Find the dispatch table it indexes into
- Read the handler at that index
- Name the entry by what the handler does, not by the index

Example: `gBattleScriptCmd_47` → read `gStateFunctionTable[47]` →
the handler plays a sound effect → `gBattleScript_Start47PlaySound`.

### Level 3: Cross-reference with domain data
If the symbol is associated with a game entity (move, Pokemon, item):
- Trace which game entity uses it
- Name it after the entity

Example: `LoadGfx34` → used only by Smog's animation script →
`LoadGfxSmog`.

### Level 4: Find the combined semantic
If a symbol dispatches multiple effects or does two things:
- Describe what the COMBINATION accomplishes, not the parts

Bad: `RegisterPaletteVariantsAndInitializeGroup` (two things listed)
Good: `PaletteVariantsWithMotionGroup` (one combined concept)

The "And" pattern is a code smell — it means you haven't found the
combined semantic yet.

## Anti-Patterns (all found and fixed in PR #308)

### 1. Trailing digits/letters without meaning
```
BAD:  ParticleEffect_SimpleBurst2    (what's different from 1?)
GOOD: ParticleEffect_SimpleBurstAnimWaitDelayedTintFade (the delay)
```
The number/letter must tell you WHAT is different, not just THAT it's
different. If you can't articulate the difference, investigate more.

### 2. Address fragments in names
```
BAD:  ParticleEffect_RegisterHandler_47448  (address of the function)
GOOD: BattleAnim_StartEffect72ModelAnimWait  (what it does)
```
The address is an implementation detail tied to ROM layout. If you
have the semantic, the address is noise.

### 3. Hex file IDs when you have the semantic
```
BAD:  LoadGfx28_Toxic  (28 is the archive file ID)
GOOD: LoadGfxToxic      (Toxic is what it's for)
```
Exception: generic/shared files used by many moves keep their IDs
(there's no single semantic to replace the ID with).

### 4. "Custom" or "Variant" without differentiation
```
BAD:  BattleAnim_EffectEnd_Custom  (what's custom about it?)
GOOD: BattleAnim_EndEffect58ModelAnimAndDescriptorSequence (this)
```
"Custom" means you haven't investigated enough. Read the function body
and describe the actual behavior.

### 5. "And" concatenation for multi-effect scripts
```
BAD:  TriggerDefault4AndSpecialSetupA  (two behaviors listed)
GOOD: TintRampsWithBurstEmitter        (combined concept)
```

### 6. Renaming empty-body functions
If the function body is `{ }` or just `return;`, you cannot determine
semantics from usage. Leave it as a placeholder or use an honest `Noop`
name following the codebase's convention.

## Quality Checklist (run before pushing any PR)

- [ ] No trailing digits/letters without semantic differentiators
- [ ] No address fragments (hex sequences that are ROM addresses)
- [ ] No hex file IDs where a move name or behavior is known
- [ ] No "Custom" / "Variant" / "Type" without saying what's different
- [ ] No "And" concatenation that could be a combined semantic
- [ ] No yaw/pitch/roll (use rotationX/Y/Z)
- [ ] No "AI" outside the BattleAi domain (use COM)
- [ ] No "party" (use brought/picked)
- [ ] No "Victory Palace" / "Kid's Club" (use Hall of Fame / Minigames)
- [ ] No British spellings
- [ ] No non-ASCII characters
- [ ] Correct casing (g/s for scope, Domain_Purpose for functions)
- [ ] Empty-body functions left as placeholders or honest Nop names

## Evidence Standard

Every name should be justifiable with:
- A specific code citation (function name + line number)
- A table decode (dispatch table index → handler behavior)
- A cross-reference (move data → animation → gfx file)
- A deterministic join (address-matched between trees)

If you can't cite evidence for a name, you're guessing. A parked
symbol (left as placeholder) is better than a guessed name.

## The Multi-Effect Naming Pattern

When a script/data dispatches multiple effects:

1. Read each effect's handler
2. Ask: "what do these TOGETHER accomplish that neither does alone?"
3. Name the combined outcome, not the parts

If there's no combined outcome (they're truly independent), consider
whether the combination itself is the semantic unit (a "setup sequence")
and name that.
