# Naming Playbook — ROM Reference Data, Verification Techniques, and Batch Rules

Everything in this file was learned during the w19/w20 violation sweeps and is
not in NAMING_CONVENTIONS.md (conventions), NAMING_RULES_PROMPT.md (model
rules), or UPSTREAM_LESSONS.md (PR #308 process lessons).

## 1. ROM Knowledge Base (decoded, verified)

### Text banks (`assets/us/textdata/NN.bin`)

Format: u32 BE count, then count u32 BE offsets, then NUL-terminated strings.
All stored UNCOMPRESSED. The bank number is the file number (decimal in the
filename, hex in `Text_GetStringTable` calls).

| Bank | Strings | Content |
|---|---|---|
| 0x00 | 13 | Lab machine descriptions ("This is a sophisticated PC.") |
| 0x01 | 10 | PC top menu (PC / Organize / Pokémon / Items) |
| 0x02 | 68 | Storage PC UI (box actions, BOX 1-12, GB BOX, "PROF. OAK") |
| 0x03 | 26 | Item-box UI (ITEMS / Choose left BOX / Move item) |
| 0x04 | 52 | BOX management (BOXes / Move BOX / Re-order BOX / Exchange BOX) |
| 0x05 | 101 | List UI (LIST / Move Cursor / Page #01/3 / column headers) |
| 0x06 | 23 | Move-menu prompts (Check moves / Re-order moves / 'L' label) |
| 0x07 | 10 | Save prompts ("The data has been altered." / Saving...) |
| 0x08 | 18 | Data-display labels (DISPLAY ORDER / A to Z / 'ID/' / 'SEEN') |
| 0x09 | 115 | Pokédex AREA names (AREA 1 / CENTER AREA...) |
| 0x0A | 152 | Species dex descriptions |
| 0x0B | 165 | Move descriptions |
| 0x0C | 250 | Item descriptions |
| 0x0D | 3 | Transfer Pak errors |
| 0x0E | 71 | Mixed: cup names + 'Game Pak' / 'Check' labels |
| 0x0F | 16 | Free Battle rule selection |
| 0x10 | 32 | Event battle / cup descriptions |
| 0x11 | 4 | NINTEN / TRAINER / DEMO / COM |
| 0x12 | 15 | Battle order select prompts |
| 0x13 | 15 | Cup names (stadium select) |
| 0x14 | 1 | Controller warning ("Controller 1 is not connected...") |
| 0x15 | 14 | Options (STEREO / MONO / ON / OFF) |
| 0x17 | 8 | Stadium mode descriptions |
| 0x18 | 7 | Session mode names (FREE BATTLE / POKéMON STADIUM / GYM LEADER CASTLE / VS MEWTWO) |
| 0x19 | 16 | Gym names (PEWTER GYM...) |
| 0x1A | 80 | Team selection/registration UI (cup names, GB-Pak errors) |
| 0x1B | 64 | Cup names (battle prep) |
| 0x1C | 22 | Pikachu reward prompts (first-clear bonus dialogs are ALSO here: strings 0x91-0x94 = Doduo/Dodrio GB rewards) |
| 0x1D | 100 | Minigame select ("Who wants to play?" / COM LEVEL / minigame names incl. 'CLEFAIRY SAYS') |
| 0x1E | 171 | Battle messages + first-clear bonus dialogs (MIXED — check fetch indices!) |
| 0x1F | 21 | Mon summary labels (NAME / LEVEL / OT / RENTAL) |
| 0x20 | 81 | Rules check strings ("Check #38 Rules" / "#39 Rules") |
| 0x21 | 35 | Trade service UI |
| 0x22 | 43 | Gym castle room titles (COOL / BEAUTY / JR...) |
| 0x24 | 151 | Species names (BULBASAUR...) |
| 0x25 | 165 | Move names (POUND...) |
| 0x26 | 16 | Type names (Normal / Fighting...) |
| 0x27 | 250 | Item names (MASTER BALL...) |
| 0x28 | 151 | Species categories (SEED / LIZARD — the Gen 1 genus) |
| 0x29 | 7 | Status names (OK / FAINTED / SLEEP...) |
| 0x2A | 1 | 'ID' (the GB save-slot label) |
| 0x2B | 12 | Photo gallery how-to ("Out of film!") |
| 0x2C | 71 | Gallery UI (GALLERY / ALBUM / FILM) |
| 0x2D | 188 | Credits staff roll |

### MORT audio sequence bank (ROM 0x1A2AD20)

- Header rev 0x5331, **657 sequences** (IDs 0–0x290)
- IDs 1–0x22: core battle phrases; 0x23–0x4F: menu/battle music;
  0x50–0xC7: more phrases; **0xCC–0x162: the 151 species names**
  (`Audio_QueueSequenceId(species + 0xCB)`); 0x163–0x1A2: move-effect
  phrases; **0x1A3–0x246: move names** (`arg1 + 0x1A2`);
  0x248–0x291: idle color commentary
- `gSfxHandle_N` digits are **standard-SFX-bank IDs** (NOT MORT sequences):
  1 = menu cursor, 2 = accept, 3 = cancel, 4 = screen open, 8 = error buzzer,
  0x2C = gallery camera shutter, 0x2D/0x2E = camera exit
- The whole cue-table system is the **announcer** (credits: "STADIUM
  ANNOUNCER"); gated by the Options VOICE toggle via
  `Audio_SetVoiceEnabled` → `gAudioActiveFlag` inside `Audio_QueueSequenceId`
- Cue pools pick with `Audio_SelectSoundAvoidingRecent` (avoids the 20 most
  recent sequences so commentary doesn't repeat)
- `gPlayerActiveFlag[side]` = remaining Pokémon count; `gAudioQueueMode` =
  battle turn counter; `PokemonAudioInfo->unk_15` = status bitfield
  (bits 0–2 sleep counter, 0x08 poison, 0x10 burn, 0x20 freeze, 0x40 paralysis)

### Battle-script VM

- `BattleAnim_RunEffectList` (battle_engine_315D50.c:4675-4697) dispatches
  byte lists; each byte indexes `gStateFunctionTable` (start) or
  `gParticleStateFunctionTable` (end)
- Byte 0x66 = `BattleAnim_DisableEffectSpawningAlias` — effects started after
  it persist through the next cleanup (the "NoSpawn" lists)
- `gBattleAnimParticleDescriptors[NN]` = descriptor NN; effect numbers are
  DECIMAL in names (StartEffect44), opcodes are HEX (Start44 for 0x44) —
  0x2C = 44, so End2C scripts cite slot 44
- Chunk boundary checks like `gMenuSoundMap_T == &gMenuSoundMap_S[arg0 * 3]`
  are compiler artifacts; the entry access `&S[(moveId-1) * 3]` is 1-indexed

## 2. Verification Techniques (what worked)

1. **Decode the data, don't infer from names.** The bank sweep found ~30
   misnamed variables whose names claimed plausible content. Every "obvious"
   name was checked against the actual bytes. (`gItemMessageBank` → "ID"
   label; `gStageNames` → item names.)
2. **Check the fetched string INDICES, not just the bank.** Banks are mixed
   content — bank 0x1E is battle messages AND first-clear dialogs.
   `gFirstClearBonusStringTable` looked wrong (bank = battle messages) but
   fetches 0x91-0x93 = the Doduo/Dodrio reward dialogs — it was RIGHT.
3. **Yay0 text extraction.** Game text resolves UI labels with certainty
   (the letters agent implemented the decompressor from asm/us/yay0.s). The
   bin archives are at ROM 0x783760.
4. **Positive-control pointer scans for deadness.** To prove a stub is dead,
   scan the full ROM image for aligned pointers AND verify the scan works
   using a known-live symbol nearby (a false positive on
   `HallOfFame_EmptyFunc1` was a misaligned lui+jal pair spanning).
5. **Cross-reference three signals for textures**: selector code
   (`Move_NormalizeDisplayIndex`-style mappings), dominant pixel colors, and
   the gradient tables' own first fields.
6. **Sibling code diffs beat caller analysis.** "Differs from X by Y"
   justifications (citing both bodies) survived every review round.
7. **Address structure as evidence**: consecutive same-size symbols are
   array chunks split by symbol granularity; exact stride matches prove
   membership (`gZeroBuffer12` = 12 bytes = one `gMoveDisplayInfo` stride,
   closing the segment = the blank 166th entry).
8. **ROM-verified store-switches**: arg0==44 → `gSfxHandle_44` in a
   switch-on-constant at a known address is a solid ID mapping.

## 3. Batch Process Rules (learned the hard way in w19/w20)

1. **Chain-resolve the ledger before counting violations.** It's append-only:
   every stage-2 rename leaves the stage-1 row "applied" with a superseded
   name. Count only names not present as a later row's old_name (18,717 rows
   → 12,049 finals). The raw count overstates violations by ~50%.
2. **Collapse chained pending renames before apply.** Preflight fails on
   old names that are another pending row's new_name (they don't exist in the
   tree yet). Fold `A→B` + `B→C` into `A→C`.
3. **Citations must follow their referents.** If a name cites another symbol
   (handler names in script names, bank contents), and that symbol is renamed
   in the same batch, cascade the citation — or the batch lands
   self-inconsistent. Watch for lookbehind issues: citations follow hex
   opcodes that END IN LETTERS (Start5E + SimpleBurst2).
4. **Fix beats keep when merging agent outputs.** Multiple files may carry
   the same symbol (a "keep" row and a "fix" row); the fix wins. Among two
   fixes with different names: reconcile manually, preferring combined
   semantics (table slot + behavior per michiiik's StartEffectNN style).
5. **Preflight requires globally-unique new names, even for file-local
   statics.** Parallel sibling fragments each holding a same-purpose static
   need screen-scoped names (`gMessageBankBoxListGbSaveIdLabel` vs
   `...ItemScreen...`). Verify this with a 2-row plan test before batch
   assembly.
6. **Never rename michiiik-owned names unilaterally.** Check every candidate
   against michiiik's symbol files first (git show origin/master in the PR
   tree). Improvements to THEIR names go to the parked file for an upstream
   proposal. (w19/w20 parked 69+ rows this way.)
7. **The lint is calibrated to michiiik's practice, not abstract rules**:
   max length 94 (their p99=72), NoopStubN/NoopStringN numbered dead data,
   power-of-two scalar widths, `Controller` contains "roll" (false
   positive), audio Pitch is fine (their Audio_SetVoiceFinePitch API),
   `RegisteredTeam*` is a domain not the Register verb. When the lint flags
   something michiiik does themselves, fix the LINT.
8. **Ledger mechanics**: batch tags must be unique per wave (w18 was taken);
   appending needs explicit newlines (a `"\t".join()` without the line ending
   collapses rows — the w19 corruption, restored from backup). Take a
   `cp renames.tsv /tmp/opencode/renames_backup_<batch>.tsv` BEFORE appending.
   NOTE: /tmp/opencode is NOT durable — it gets wiped by the system reaper.
   Regenerable workloads and reference files (michi_syms, claim chunks) must
   be re-creatable from in-repo sources; the ledger itself is git-tracked, so
   git history is the real backup.
9. **Two-stage naming produces stage-1 intermediates** (`func_843490A8 →
   ParticleEffect_RegisterHandler_490A8` then `→ BattleAnim_StartEffect111...`).
   The intermediate stays in the ledger; that's fine — just remember audits
   must chain-resolve (rule 1).
10. **Screen-scoped naming for parallel statics**: identify the fragment's
    screen by its dominant functions (LabPC_BoxMenu → box menu screen) before
    differentiating same-purpose statics across siblings.

## 4. Game-Knowledge Discoveries (context for future names)

- **ERA CHECK (the #1 misname cause, ~22% of model-draft content claims)**: the
  model drafts applied modern-Pokémon vocabulary to a Gen 1 game — "items" for
  battle announcer pools (Stadium battles have no item events), "Ability"/
  "Ribbons" icons (neither concept exists in Gen 1), "TrainerCard" for Pokédex
  statics, item/seed/audio tables for GB-cart header tables (the "random seed
  table" literally contained ASCII "POKEMON RED"). Before accepting any
  domain word, verify the concept EXISTS in this game: no abilities, no
  ribbons, no held items, no natures, no genders in Gen 1.
- **The announcer**: entire cue-table system = announcer voice, VOICE toggle
  gated, mood-keyed pools (even match / low HP / both heavy damage / delayed
  freeze/sleep reactions via `gAudioPendingFreezeReaction`)
- **RNG**: `Battle_Random`/`Battle_RandomAccuracy` are LCG/LFSR pairs
  (`gBattleRngLcgSeed` / `gBattleRngLfsrSeed`)
- **Rental rules**: `Mode<N>` was the CUP and `S<M>` was the battle mode (the
  stage-1 names had them backwards); category 2 = hidden JP Nintendo Cup slot
  ('POKé CUP2' in the gallery); category 0/8 = any-number-of-Pokémon rules
- **GB emulator quirks**: `gMenuSoundMap_A/B/C/D/K` are u16 cue tables
  misdeclared as u8 (big-endian pairs); `D_800780B3 = gMenuSoundMap_S - 1`
  is the codegen's alternate base for the move table
- **Camera**: `gCameraYaw/Pitch` family = rotationY/rotationX (terminology);
  the marquee text draw double-renders for wraparound
- **First-clear bonus**: Doduo/Dodrio Game Boys speed up the GB Tower
  (strings 0x91-0x94 of bank 0x1E)
