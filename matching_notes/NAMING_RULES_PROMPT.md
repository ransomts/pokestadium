# Symbol Naming Rules (Model Prompt v3 — michiiik/pokestadium CONTRIBUTING.md compliant)

You are naming symbols in a decompiled Nintendo 64 game (Pokemon Stadium).
Replace placeholder names (func_XXXXXXXX, D_XXXXXXXX) with human-readable
names. You MUST follow every rule below.

## DOMAIN GLOSSARY

These terms appear throughout the codebase. Learn them before naming:

- **effect** = a visual particle animation (sparkles, explosions, fades)
- **effect slot** = one particle instance with position, palette, and callbacks
- **descriptor** = a struct describing particle appearance (ID like 0x34)
- **palette index** = which color palette a particle uses (ID like 0x1B)
- **owner model** = the 3D Pokemon model the particles attach to
- **tint ramp** = gradual color change on the model over time
- **display list (DL)** = a series of GPU commands
- **move** = a Pokemon battle move (Thunder, Toxic, Fire Blast)
- **brought Pokemon** = the 6 in your party; **picked** = the 3 you choose
- **COM** = computer-controlled trainer (NOT "AI")
- **anim** = animation state (idle, attack, hit, faint)
- **nop** = a function that does nothing (empty body)
- **GB record** = Game Boy cartridge save data structure
- **Kangaskid** = the creature in Kangaskhan's pouch

## STEP 1: Find and read the code

For a function placeholder:
```
grep -n "func_XXXXXXXX" src/
```
Read the function body. Then find callers:
```
grep -n "func_XXXXXXXX" src/ --include="*.c" | grep -v "void func_"
```
Read 2-3 call sites to understand context.

For a data placeholder:
```
grep -n "D_XXXXXXXX" src/ --include="*.c" --include="*.h"
```
Read where it's declared and where it's used.

## STEP 2: Extract facts (write these down mentally)

Before naming, you must have at least 2 of these:
- What does the function DO (not what it's called from)?
- What values does it write/read/compare?
- What table does it index into?
- What known-named function does it call?

If you have fewer than 2 facts → SKIP this symbol.

## STEP 3: Build the name

### Start with the casing template:

```
Function:   {Domain}_{What}     e.g., Battle_ApplyDamage
Global var: g{What}             e.g., gPlayerHp
Static var: s{What}             e.g., sFrameCount
Struct:     {TitleCase}         e.g., HallOfFameSlot
Local var:  {snake_case}       e.g., cpu_pokemon
```

### Pick the Domain from this table (or find one nearby in the code):

| Domain | Use when |
|---|---|
| Battle | Battle logic, damage, turns |
| BattleScene | Scene setup, camera, rendering orchestration |
| BattleAnim | Particle effects, visual animations |
| BattleAi | AI procedures (exact casing, not BattleAI) |
| BattleHud | HP bars, status icons, in-battle UI |
| Particle | Particle system internals |
| Gfx | Direct GPU commands, display lists |
| Audio | Sound, music, sequencing |
| Pokemon | Per-Pokemon state, stats, types |
| Move | Move-specific behavior |
| Storage | Save/load, memory management |
| RentalHub | Rental system |
| Trade | Trade system |
| Gym | Gym Leader Castle |
| Gallery | Photo gallery |
| Lab | Pokemon Lab (Professor Oak's Lab) |
| Title | Title screen |

### Now apply these HARD RULES (check each one):

R1. Does the name end in a bare digit or have a digit suffix?
    → The digit MUST fall into one of these SEMANTIC categories:
      - Bit width: BE16, LE32 (I/O read/write sizes)
      - Pixel format: RGBA16, RGBA32, IA8, I4, CI4 (texture formats)
      - Texture dimension: 32x32, 64x64 (size in pixels)
      - Audio channel: Square1, Square2, Pulse1, Pulse2 (GBA channels)
      - Player/controller index: Player1, Player2 (game entities)
      - Effect/descriptor table index: Effect47, Descriptor34
      - Palette index: Palette1B (color table lookup)
      - Version/revision: Rev1, V2
      - Mode/phase: Phase0, Phase1 (state machine steps)
      - Mathematical: Log2, Sqrt2 (operations)
      
      NOT allowed (variant counters):
      - Load2, Call2 (what's different from 1?)
      - Handler3, Process4 (incrementing without meaning)
      - Type2, Kind3 (categorized without description)
      
      If the digit doesn't fit a semantic category above, investigate
      what differentiates the siblings. If you can't tell, SKIP.

R1b. Does the name contain a hex fragment (4+ hex digits)?
    → The fragment must be PREFIXED with what it indexes:
      - Palette5F92 (palette table index)
      - Descriptor34 (particle descriptor ID)
      - Effect47 (dispatch table index)
      
      NOT allowed (bare addresses):
      - _5F92 (raw address, no context)
      - Handler_49628 (function address)
      - ProcessBC20 (ROM address fragment)
      
      If you can't articulate what the hex indexes, remove it entirely
      and use the semantic name instead.

R3. Does the name contain "_" followed by 4+ hex digits? (_49628)
    → This is an ADDRESS FRAGMENT. Remove it. Replace with what the
      function at that address does.

R4. Does the name contain "Custom" or "Variant" or "Type" as a
    standalone word?
    → These are BANNED unless immediately followed by a specific
      differentiator. "CustomCallback" is banned. "CustomPaletteB"
      is allowed (it says what's custom).

R5. Does the name contain "yaw" or "pitch" or "roll" anywhere?
    → Replace with rotationY, rotationX, rotationZ. (Exception: "Rollout"
      is a legitimate Gen 1 move name. Use judgment for move names.)

R6. Does the name contain "AI" outside "BattleAi"?
    → Replace with "COM".

R7. Does the name contain "party" when referring to Pokemon?
    → Replace with "brought" (party of 6) or "picked" (chosen 3).

R8. Does the name contain "VictoryPalace" or "KidsClub" or "PokeCup"
    or "PokemonLab"?
    → Replace with HallOfFame, Minigames, NintendoCup, ProfessorOaksLab.

R9. Is the name over 50 characters?
    → Shorten it. Remove redundant words. "And" chains become a
      single concept.

R10. Does the name contain "And" connecting two behaviors?
    → Try to find ONE concept that covers both. If you can't,
      keep the "And" but make both sides specific (not "SetupA").
      If you can't make both sides specific, SKIP.

R11. Does the name contain "fadeLevel" or "fade_level"?
    → Replace with "alpha" (prefer technically correct obscure language).

R12. Does the name contain any non-ASCII character?
    → Remove it. No é, no ♂, no non-alphanumeric symbols even if
      lore accurate (Nidoran♂ should be NIDORAN_MALE).

R13. Does the name contain a British spelling?
    → Replace: colour→color, centre→center, behaviour→behavior,
      favour→favor, honour→honor.

### Content rules (what to name it):

- Plays a sound → include the sound name or trigger condition
- Draws something → include what it draws (texture, shape, effect)
- Initializes something → include what system it initializes
- Handles an input/event → include what triggers it
- Empty body ({ } or return;) → Domain_Noop or SKIP
- Loads a resource → include the resource name if known
- Gen 1 save data → include "Gb" prefix (GbRecord, GbSave, etc.)

### Sensitive language (in names AND justifications):

- Never use "blackface" or "purpleface" → "original color" / "purple color"
- For Nidoqueen documentation: use "breasts" (clinical term, not slang)

## STEP 4: Self-validate (answer YES to continue, NO to skip)

1. I can describe what this does in one sentence. [YES/NO]
2. My name would make sense to someone who hasn't read the code. [YES/NO]
3. The name passes all 13 hard rules above. [YES/NO]
4. I can cite a specific line number that proves my name. [YES/NO]

If ANY answer is NO → SKIP.

## STEP 5: Output

Format each rename as one line (tab-separated):
```
old_name<TAB>new_name<TAB>justification (one sentence with line citation)
```

### Worked example:

Code found:
```c
void func_8430AB50(void) {
    ApplyDamage(arg0, arg1->currentHP);
    QueueBattleMessage(MOVE_DAMAGE_DEALT);
    UpdateHPBar(arg1);
}
```
Called from ProcessBattleTurn case 6 (line 7114).

Facts: (1) applies damage to HP, (2) queues a damage message, (3) updates HP bar.
Domain: Battle (it's in the battle turn processing).
Name: Battle_ApplyDamageAnimation
Justification: Called in ProcessBattleTurn case 6 after damage calculation,
applies HP damage and updates the HP bar (battle_engine_2EC3C0.c:7114).

Output:
```
func_8430AB50	Battle_ApplyDamageAnimation	Applies HP damage and updates HP bar, called from ProcessBattleTurn case 6 at line 7114
```

### Another example (SKIP case):

Code found:
```c
void func_8430FC18(void) {
}
```
No callers with semantic names.

Facts: (0) the body is empty.
I have fewer than 2 facts → SKIP. Output nothing for this symbol.

## COMMON MISTAKES TO AVOID

1. Naming after the CALLER, not the BEHAVIOR
   BAD: "ProcessBattleTurnHelper" (says who calls it, not what it does)
   GOOD: "Battle_ApplyDamageAnimation" (says what it does)

2. Naming after the TYPE, not the PURPOSE
   BAD: "CalculateS32" (says the type, not what's calculated)
   GOOD: "ComputeAccuracyMultiplier" (says what)

3. Including the old placeholder in the new name
   BAD: "Func8430AB50_DamageHandler" (keeps the address)
   GOOD: "Battle_ApplyDamageAnimation" (pure semantics)

4. Using vague qualifiers
   BAD: "ProcessData", "HandleEvent", "UpdateState"
   GOOD: "ProcessBattleTurn", "HandleMoveEvent", "UpdateHPBar"

5. Concatenating behaviors with "And" when a single concept exists
   BAD: "FadeOutAndCleanUpAndReset"
   GOOD: "EndEffect" (one concept covering all three)

6. Using "fadeLevel" instead of "alpha"
   BAD: "Gfx_SetFadeLevel"
   GOOD: "Gfx_SetAlpha"

7. Using British spellings
   BAD: "Gfx_GetColour"
   GOOD: "Gfx_GetColor"

## WHEN TO SKIP (binary conditions)

Skip if ANY of these is true:
- [ ] Function body is `{ }` or `return;` and there's no nearby Noop convention
- [ ] All callers are also placeholder-named (func_XXX)
- [ ] You wrote down fewer than 2 facts in Step 2
- [ ] You answered NO to any self-validation question in Step 4
- [ ] The symbol is in linker_scripts/ or undefined_syms.ld

Skipping produces NO output for that symbol. This is the CORRECT
behavior. A parked placeholder is better than a wrong name.

## ADDITIONAL SEMANTIC PATTERNS (from full audit)

These patterns are SEMANTIC and should be allowed:

### N64 pixel formats (NOT bare digits or letters):
- I4, I8, IA4, IA8, RGBA16, RGBA32, CI4, CI8
- These are the actual N64 texture format names

### Vertex/array indices (NOT bare digits):
- Vtx0, Vtx1, Vertices0, Vertices1, PanelVtx0
- The digit indexes into an array of vertex data

### Indexed game entities (NOT bare digits):
- Root0, Root1, Node0, Node1, Entry0, Entry1
- Page0, Page1, Frame0, Frame1, Layer0, Layer1
- These number sequential instances of the same concept

### Compound suffixes (NOT bare letters):
- DMA, RGB, RGBA, RTC, BEA, LEA
- The final letter is part of a compound word, not a variant marker

### Audio channels (NOT bare digits):
- Square1, Square2, Pulse1, Pulse2, Noise1
- These are GBA sound channel names

### RGB color components:
- Color_R, Color_G, Color_B, Color_A
- The letter is the color channel (Red, Green, Blue, Alpha)
