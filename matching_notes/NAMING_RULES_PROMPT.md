# Symbol Naming Rules (Model Prompt)

You are naming symbols in a decompiled Nintendo 64 game. Replace
placeholder names (func_XXXXXXXX, D_XXXXXXXX) with human-readable names.

## STEP 1: Read the code

Read the function body and 2-3 callers. Find:
- What values it writes, reads, or compares
- What known functions it calls
- What tables it indexes

## STEP 2: Pick a name using these rules IN ORDER

### Casing (apply always):
- Game-wide global variable → prefix `g` + CamelCase: `gPlayerHp`
- File-scoped static variable → prefix `s` + CamelCase: `sFrameCount`
- Function → `Domain_VerbOrNoun`: `Battle_ApplyDamage`
- If unsure of scope, use no prefix for functions

### Banned words (REJECT the name if it contains):
- yaw, pitch, roll → use rotationY, rotationX, rotationZ
- AI (outside BattleAi) → use COM
- party (for Pokemon team) → use brought or picked
- VictoryPalace → use HallOfFame
- KidsClub → use Minigames
- PokeCup → use NintendoCup
- Custom, Variant, Type (without a differentiator after them)
- colour, centre, behaviour, favour (British spellings)
- Any non-ASCII character

### Suffix rules (CRITICAL — most common failure):
- NEVER end a name with a bare digit or letter (Foo2, BarB)
- If siblings differ, the suffix must SAY what's different:
  - Different palette index? → `Palette1B` (the index IS semantic)
  - Different texture? → `Texture9` (the ID is semantic)
  - Different behavior? → `AnimWait` vs `DelayedFade` (describe it)
  - You cannot determine the difference? → SKIP the symbol entirely

### Content rules:
- If the function plays a sound → name includes what sound or when
- If the function draws something → name includes what it draws
- If the function initializes a system → name includes which system
- If the function handles a game event → name includes the event
- If the function body is empty (just `{ }` or `return;`) → name it
  `Domain_Noop` or SKIP it entirely

### Script/table entry naming:
- If it references one handler → name by that handler's behavior
- If it references multiple handlers → describe what they accomplish
  TOGETHER, not a list of what each does
  - BAD: `TriggerDefault4AndSpecialSetupA` (two things concatenated)
  - GOOD: `TintRampsWithBurstEmitter` (one combined concept)
- NEVER include the raw address of a handler in the name
  - BAD: `RegisterHandler_49628` (address fragment)
  - GOOD: `RegisterModelAnim` (what the handler does)

### Hex ID rules:
- If a hex ID is a dispatch-table index or palette index → KEEP it
  (it's semantic, like `StartEffect47`)
- If you know the move name or content that the ID refers to → DROP the
  ID and use the name (like `LoadGfxToxic` not `LoadGfx28_Toxic`)
- If you don't know what the ID refers to → keep the ID, skip adding
  a semantic you can't verify

## STEP 3: Self-check before proposing

Ask yourself:
1. Does the name tell me what this does WITHOUT reading the code? If
   no, it's not specific enough.
2. Is there a number or letter at the end? If yes, does it say WHAT is
   different from siblings? If no, investigate more or skip.
3. Would a speedrunner or romhacker understand this name? If no,
   it's too jargon-y.
4. Is the name over 50 characters? If yes, find a shorter form that
   keeps the meaning.
5. Can I cite the line of code that proves this name? If no, SKIP.

## STEP 4: Output format

For each symbol you rename, provide:
- old placeholder name
- new name
- one-sentence justification citing specific evidence

Example output:
```
func_8430FC10  BattleHud_Noop  function body is empty at line 172
func_8430AB50  Battle_ApplyDamageAnimation  called in ProcessBattleTurn case 6 after damage calc at line 7114
D_80075E40  gCamDistances  array of camera distances indexed by zoom level in Camera_Update
```

## WHEN TO SKIP (output nothing for this symbol)

- Function body is empty AND there's no existing Noop naming convention
- The function is only called by other placeholder-named functions
- You cannot determine what any parameter or return value means
- The name would require guessing at game-specific terminology
- The symbol is in linker_scripts (never-touch files)

Skipping is CORRECT. A parked placeholder is better than a wrong name.
