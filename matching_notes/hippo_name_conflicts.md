# ma1 name-conflict review: ours vs michiiik (Team Hippodrome)

**What this is:** verdicts on the 5,139 ma1 alignment renames (2026-10-18, applied @3477349),
where michiiik/pokestadium's name replaced ours for the same address-joined symbol. This report
triages every pair, judges which name better matches the code, and lists recommended reversions.

**Context:** ma1 was the owner-decision pivot to michiiik as the target tree (RENAME_PLAN.md
"PIVOT, 2026-10-18 ~21:10"). Their name now wins wherever we diverged — this review is the
counter-check: where their name asserts something the code contradicts, or where their name is a
raw offset placeholder and ours was a validated semantic name, a one-row ledger reversion is
offered. Analysis date: 2026-10-18. Evidence sources: our tree at HEAD, the michiiik clone at
`/tmp/opencode/hippo` (complete decomp, C source for everything), and the address join in
`/tmp/opencode/name_conflicts_input.tsv`.

---

## 1. Method

1. Automated triage of all 5,139 pairs (tokenize → synonym-normalize → module-prefix strip →
   content-token compare), then a **full manual read of every non-trivial pair** (~1,000 rows
   read line-by-line; the BattleAnim-effect block dominates the synonym remainder).
2. For every family or single that looked contradictory, the truth was read out of the code in
   the michiiik clone (their names annotate their C) and cross-checked in our tree at HEAD.
3. Collision reconstruction for the dropped ma1 rows: address-join of both trees' symbol tables at
   HEAD minus the applied ledger.

## 2. Summary counts

| Category | Rows | Meaning |
|---|---:|---|
| Synonym / vocabulary | **~4,355** (85%) | Same assertion, different words: verb synonyms (Step→Update), module regrouping (ParticleEffect_→BattleAnim_), perspective differences (FireworksState vs CallbackStartEffect8ModelBurstEmitter), casing/plural/ordering. Judgment-neutral. |
| Semantic conflicts | **~310** (6%) | The two names assert different behavior/referents; one is wrong. 240 whole-module misattributions + 34 enumerated core pairs + ~38 verified one-offs. Verdicts below. |
| Suspicious (vagueness asymmetry) | **~475** (9%) | One side specific, the other generic. 311 rows ours-vague (State/Handler/Update/FragmentN names) — theirs better; 160 rows theirs-raw (`Particle_FieldXX_..._0ADDR` offset names) — ours better for the validated field subset. |
| **Total** | **5,139** | |

(Counts are pattern-based on top of the manual read; boundary rows shift by a few between
"synonym" and "suspicious" depending on how strict vagueness is judged. The verdicts below are
per-row/per-family code-checked, not estimated.)

## 3. Semantic-conflict verdicts

### 3.1 Verified one-offs (code-checked)

| our_old_name | their_live_name | verdict | evidence |
|---|---|---|---|
| GetItemName | Text_GetTmHmName | **OURS-BETTER** | Body: ids 1..0x53 index `D_80072EE0[]` → 84-entry table of Gen-1 **item** name strings (first entry "マスターボール", Master Ball); only ids 0xC4-0xFE sprintf TM/HM names — michiiik's own `status_icons.c:12` comment calls the table "item names, dead data"; function is an uncalled export in both trees. |
| GetNextPage | TeamSelection_RegisteredTeam_GetPrevious | **OURS-BETTER** | Chain is built `unk_4D24 = &nodes[(i+1)&3]` / `unk_4D28 = &nodes[(i-1)&3]` (rental_team_selection_2E5430.c:1102-1103) and `MoveListDown` increments the page index while walking `unk_4D24`; michiiik's GetPrevious walks unk_4D24 and their GetNext walks unk_4D28 — their pair is **direction-swapped**. |
| GetPrevPage | TeamSelection_RegisteredTeam_GetNext | **OURS-BETTER** | Same swap, opposite row (0x8420F1BC). |
| Audio_Pause / Audio_Unpause | Audio_Enable / Audio_Disable | THEIRS-BETTER | `Audio_Enable(){Audio_SetEnabled(1);}` / Disable sets 0; callers bracket the GB Tower emulation session in State_GbTower — enable/disable flag, not pause state. |
| GbPak_WriteDataAligned | GbPak_ReadRom | THEIRS-BETTER | Reads ROM across 0x4000-byte bank boundaries via GbPak_RawRead + bank select; no write path. |
| SetAudioVolume | GbApu_SelectRegionClock | THEIRS-BETTER | Sets APU clock constants 0x4578/0x8AF0 (region clock), nothing volume-related. |
| AllocateAudioBuffer | GbCpu_Execute | THEIRS-BETTER | GB CPU interpreter step; no allocation. |
| StartAudioPlayback | GbCpu_InitOpcodeTables | THEIRS-BETTER | Fills GB opcode dispatch tables. |
| Controller_ReadInput | GbSave_CopyPlayerIdentity | THEIRS-BETTER | Copies GB-save player identity struct to a destination; no controller I/O. |
| IsEntityGenderMale | BattleScene_IsParticipantModelVisible | THEIRS-BETTER | Returns `arg0->unk_000.node.flags & 1` — model visibility bit, no gender anywhere. |
| GetPokemonBaseStat | Species_ToInternalIndex | THEIRS-BETTER | Species→GB internal-index conversion used in Pokemon_ToGbRecord/FromGbRecord. |
| Mon_GetEvolutionLine | Species_GetMoveSlot | THEIRS-BETTER | Indexes the species learnset table `D_80070FA0[species-1]` fields 06/07 — move slots, not evolutions. |
| GbsGetPlayerMoney / GbsSetPlayerMoney | Save_Get/SetOptionsField02 | THEIRS-BETTER | Reads/writes options-record field 02 with dirty-marking on record 0x14; the money claim is unverifiable speculation. |
| GbsGetPlayerName / GbsSetPlayerName | Save_Get/SetOptions | THEIRS-BETTER | Returns the options record; ours asserted a name field the code doesn't show. |
| ResetAllStatFlags | Battle_InitializeMoveUsabilityMask | THEIRS-BETTER | Sets 4 move-usable flags then calls Battle_FilterUnusableMoves — move usability, not stats. |
| ProcessTurnEnd | Battle_ApplyDamage | THEIRS-BETTER | Applies gBattleDamage to gBattleTarget HP (substitute handling, faint checks, messages). |
| Audio_SetVolumeFade | AudioStream_Stop | THEIRS-BETTER | Sets stream state 1/5 under int mask; computes the fade-out rate only as the path to stop. |
| Audio_IsMusicEnabled | Cry_IsPlaying | THEIRS-BETTER | Returns `D_80077D90[0]`, set only by `Cry_SetEnabled` — the cry-stream flag, distinct from music flags. |
| Music_SetPanMode | Audio_SetMonoOutput | EQUIVALENT | Mono output ≈ pan-mode collapse; both defensible, theirs more literal. |
| UnusedFunction | BattleScene_IntroInitNop | THEIRS-BETTER | Empty function; theirs also says where it sits (intro-init state slot). |
| GetPlayerCount | DebugMenu_Exit | THEIRS-BETTER | Address 0x8F000020 is in the debug-menu fragment (michiiik debug_menu_* dirs); ours is a generic LLM-era name. |
| GetMoveEntry / gMoveStrings | Move_GetDisplayInfo / gMoveDisplayInfo | THEIRS-BETTER | Table entries are `{id, category, {pp, effect}, name, comment}` per move (166 rows) — display info, not just strings. |
| GetMoveBattleDataEntry | Move_GetData | EQUIVALENT | Same table, ours adds the "battle" qualifier; both fine. |
| MenuItem_GetHeldItemId / _GetPokemonGender / _GetPokemonLevel / _GetPokemonSpecies / _IsPokemonEgg / _IsPokemonShiny | GbSave_GetPortGame / _SavedAtPokemonCenter / _GetPartyCount / _GetSaveState / _HasProgressFlag1000 / _HasPokedex | THEIRS-BETTER | All six read GB-save port/status fields; the MenuItem_* claims (held item, gender, level, species, egg, shiny) are unsupported by the bodies. |
| MessageBank_SetPointer_0x14_0x2A / _1_9 | Text_SetStringToken / Text_SetNumberToken | THEIRS-BETTER | Called as `Text_SetStringToken(0x19, nickname)` before queueing messages — token substitution, and the ours-name leaks an address. |
| Text_SetupDL / Text_ResetState | Font_EndTexturedTextRendering / Font_BeginTranslucentTextRendering | THEIRS-BETTER | Adjacent begin/end bracket (0x8001F3F4/0x8001F444) — DL emit / translucent-render setup; ours missed the pairing. |
| GetPlayerNameLength | TransferPak_GetPresentationMode | THEIRS-BETTER | Different domain entirely; ours unsupported. |
| GetPokemonType1 | Move_GetIdFromTableIndex | THEIRS-BETTER | Table index→move id lookup. |
| GetRandomU8 / _Alt | Battle_Random / Battle_RandomAccuracy | THEIRS-BETTER | Wrapped RNG draws in battle context. |
| DrawExpBar | BattleHud_DrawHpBar16x5 | THEIRS-BETTER | Draws a 16x5 HP bar with red (<10/48) / yellow (<27/48) / green fill thresholds — HP, not EXP. |
| DrawBadgeIcon | Ui_Draw20x20Icon | EQUIVALENT | Both generic; theirs names the size. |

### 3.2 Whole-module misattributions (ours named the wrong feature; theirs verified)

| our module | their module | rows | verdict | evidence |
|---|---|---:|---|---|
| MenuBar_* / MenuPanel_* | TradeCable_* | 53 | THEIRS-BETTER | The "menu bar/panel" functions drive the trade-cable machine: ball travel, tube rails, sequence steps (TradeCable_UpdateSequence*, DrawTubeSparkBand*). |
| SnapSelect_* | Gallery_RentalViewer* | 34 | THEIRS-BETTER | Calls LoadPort/LoadDeckEntries/BoxPicker — the gallery's GB-pak rental viewer; "Snap" was a wrong feature association. |
| TrainerCard* | Pokedex_* | 33 | THEIRS-BETTER | michiiik has a `fragments/pokedex/` module (gPokedexAlphabeticalOrder, species list, data panel, cry playback, area map); the "TrainerCard" split misassigned the screens. |
| BattleIntroPanel_* | Completion_* | 25 | THEIRS-BETTER | Victory-palace/completion scene (logo banner, bonus pokemon, gift dialog). |
| ResultScreen_* | DrowzeeGame_* / DynamoGame_* | 21 | THEIRS-BETTER | Mini-game result/intro screens (Drowzee/Dynamo are michiiik's mini-game modules). |
| MiniHud_* | MagikarpGame_* | 29 | THEIRS-BETTER | Magikarp jump minigame loop (trick poses, splash ripple, countdown). |
| HealthBar_* | DynamoGame_* | 15 | THEIRS-BETTER | Dynamo mini-game (crank icon, AI charge bias, chain-link animations) — nothing health-bar about it. |
| Hud_* | DrowzeeGame_* | 6 | THEIRS-BETTER | Drowzee mini-game overlays (player overlays, elimination). |
| PictureQuiz_* | Pokedex_* (area map) | 14 | THEIRS-BETTER | Pokedex area-map screen (ShowAreaMapScreen, area map pool). |
| BattleModeMenu_* | RentalRules_* | 5 | THEIRS-BETTER | Rental-rules screens (rule list, species pages). |
| BattleResultScreen_* | Trade_* InfoBox | 5 | THEIRS-BETTER | Trade info-box open/close/choose. |
| DrawHPBarSegment / _Alt, SetHPBarCriticalFlag, SetDoubleBattleHPBarCriticalFlag, AnimateErrorScreen*, ErrorScreen_*, SetupErrorScreenGraphNodes, InitTransferPakErrorScreen, LoadTransferPakErrorImages, DrawTransferPakError, UpdateErrorScreenAnimation, ResetErrorScreenGraphNodes | BattlePrepTeamIcons_DrawBadgeIcon*, MarkFainted*, BattlePrep_Badge*, BattlePrep_*Carousel* | ~18 | THEIRS-BETTER | These draw PokeIcon species icons per roster slot and toggle the fainted "badge" marker (`unk_2C[i]`), and the badge carousel scene; HP bars in that screen are drawn by their DrawHpBars*/HpDrainStep* — ours misassigned the subsystem. |
| GSM codec (AnimHeader_ProcessScaled, AnimBlock_DecodeSubframe, AnimProcessor_ApplySubframe, AnimFrame_ProcessSubframes, AnimProcessor_FinishFrame, GbAudio_DecodeSpeechFrame, AnimData_DecodePacked) | Decoding_of_the_coded_Log_Area_Ratios, Gsm_RPE_Decoding, Gsm_Long_term_synthesis_filtering, Gsm_Short_Term_Synthesis_Filter, Gsm_Decoder, Gsm_Decode_Stream, Gsm_Decode | 7 | THEIRS-BETTER | michiiik ships `src/libgsm/libgsm.h` + `src/gsm_decoder.c` — these are the GSM 06.10 speech codec verbatim; ours thought they were animation/audio-frame processing. |
| List_* (Init/GetCopy/Set/RemoveAt/Free/Append/Insert) | ByteMatrix_* | 7 | THEIRS-BETTER | The structure is a fixed-stride byte matrix (rows of unk_0C bytes, AppendRow/InsertRow/RemoveRow), not a generic list — different kind claim. |
| GetSpeciesPrimaryEffect/GetSpeciesSecondaryEffect, GetPrimaryEffectNodePosition, GetPrimaryEntityScale, GetSecondaryEntity*, ComputePrimary/SecondaryEffectScale, GetSpeciesOfPlayerIndex, IsEntityASpecies, gCurrentBattleEntity→gBattleUser, gDefenderBattleEntity→gBattleTarget | BattleAnim_GetSecondaryOwner*/GetTertiaryOwner*/GetCurrentOwner*, gBattleUser/gBattleTarget | 15 | EQUIVALENT (ordinal shift) | Theirs has 3 slots set by the queue functions (QueueMoveEffect: current=secondary=attacker, tertiary=defender); ours had 2 roles (primary=user, secondary=target). Both map cleanly; ours matches standard user/target move semantics, theirs mirrors the queue bookkeeping where "secondary" aliases the user. No reversion — pick a convention and stay. |

### 3.3 Suspicious (vagueness asymmetry) — family verdicts

**Ours-vague, theirs-specific (~311 rows): theirs better.** Our old names here were
StateHandler/State/Main/Update/FragmentN_*/Execute/Process-style scaffolding where michiiik named
the actual screen, sequence step, or effect. Representative: `ParticleEffect_StateHandler_47D74 →
BattleAnim_CallbackStartEffects50And82CenterModelScalePaletteFade`,
`Fragment2_1_CalcAnimOffset → Widget_CountdownComputeScale`,
`UnusedFunction → BattleScene_IntroInitNop`. Verdicts follow the module families in 3.2 (all
theirs-better); no reversion candidates.

**Theirs-raw, ours-semantic (160 rows): ours better for ~94 of them.** michiiik left raw
`Particle_FieldXX_<op>_<addr>` names on the particle-struct accessors. Field semantics are
verified from michiiik's own code (their semantic functions read the same fields):

| field | meaning | michiiik's own evidence | our old prefix |
|---|---|---|---|
| 0x94 | rotation (Vec3s) | `Particle_ComputeVectorFromRotationY` does `SINS(arg0->unk_94.y)` | Set/Add/SubtractRotation* |
| 0x9A | rotation speed/delta | `Particle_SetRotationSpeed` writes `unk_9A` | SetRotationDelta* |
| 0xA0 | target rotation | `Particle_ApproachRotationTargetXY` | SetTargetRotation* |
| 0x50, 0x38 | velocity | `Particle_SetVelocityRandomDirection` writes `unk_50`; position = unk_68+unk_38+unk_50 | Set/AddVelocity* |
| 0x74 | speed scalar | `unk_7C = unk_74 * cos/sin(unk_94)` | Set/ApproachSpeed |
| 0x78 | approach rate (accel) | `Particle_Field74_ApproachUsingField78` | Set/ApproachAcceleration |
| 0x1C | scale | `unk_14->scale.x = arg0->unk_1C` in UpdateWorldTransform | Set/ApproachScaleFactor* |
| 0xA6, 0xA8 | timers (delay/phase) | `Particle_TickDelayAndAdvanceLifecycle(arg0, arg0->unk_A6)` | Set/Get/DecrementTimerA6/A8 |

Two of ours in this family were wrong and stay theirs: `Particle_SetAccelerationVector /
SetVelocityFromRotation*` (field 0x7C is the velocity-from-rotation/target vector, not
acceleration — michiiik's `Particle_SetVelocityImpulse`), and `Particle_RotateX` (it adds to the
**Z** rotation component; our axis label was wrong). Prim/Env color rows (ApproachPrimR etc. →
PrimR_Approach) are equivalent — michiiik's struct names those fields `prim_r/g/b`, `env_r/g/b`.

## 4. Collision analysis (the dropped ma1 rows)

No skip list was kept for the drops, so they were reconstructed by address-joining both trees at
HEAD: **124 name-divergent pairs remain**, which decompose as:

1. **22 true ma1 drops** (our name was pipeline-named, row rejected at preflight): 16 ledger-named
   + the JpegDecoder_* quartet + 2 MusyX-adjacent (below). **21 of the 22 michiiik names are now
   FREE in our tree** — the blocking holder was itself renamed within ma1 — so the rows can simply
   be re-run:

   | dropped row (ours → theirs) | status now |
   |---|---|
   | Vec3f_Sum → Vec3f_Add, Vec3s_Sum → Vec3s_Add | name free — re-runnable |
   | Gfx_DrawTextureRect2 → Gfx_DrawTexturedRect | free (our other DrawTextureRect became ...Clipped) — re-runnable |
   | Text_SetEnvColor → Gfx_SetEnvColor, Text_SetPrimColor → Gfx_SetPrimColor | free — re-runnable |
   | CountTextLines → Text_CountLines | free — re-runnable |
   | Gfx_SetCombineRaw → Gfx_SetCombineMode | free — re-runnable |
   | GbAudio_Reset → GbApu_ResetChannels | free — re-runnable |
   | Particle_SetVelocityScaledXYZ → Particle_SetPosition, Particle_ApplyB278AndCopyXZ → Particle_SetVelocityXZFromRotationY | free — re-runnable (but see §3.3: SetPosition-family naming is contested) |
   | gParticleDefs → gBattleAnimEffectSlots | free — re-runnable |
   | DetermineTurnOrder → Battle_StartTurn | free — re-runnable |
   | MenuInput_FrameUpdate → MiniGame_ReadInputs | free — re-runnable |
   | BoxPC_InitScreen → LabPC_BuildBoxScreenWidget | free — re-runnable |
   | TextObjectGraphics_Init → WidgetTree_InitMessagePanel | free — re-runnable |
   | JpegDecoder_Decode → Jpeg_DecodeMcus, JpegDecoder_ProcessMcu → Jpeg_DecodeBlock, JpegDecoder_ParseNextSymbol → Jpeg_DecodeHuffmanSymbol, JpegDecoder_ReadBits → Jpeg_ReadBits | free — re-runnable |
   | RemapBankPointers → Audio_RelocateSoundBankTable, ____MusLoadSongWithFade → Audio_PlayMusicSequenceLoopedHandler | free — but see MusyX note; recommend NOT adopting |

2. **1 unresolved collision: `gIdentityMtx`.** michiiik's `gIdentityMtx` (0x8006F010) was
   rejected because our tree already has `gIdentityMtx` at 0x80076270. Truth from the data: both
   are identity matrices — our 0x8006F010 symbol is misnamed `gCamProjectionMatrix` (defined in
   src/F420.c as a plain identity Mtx, only ever `gSPMatrix`-loaded as G_MTX_LOAD|MODELVIEW,
   never written a projection), and our 0x80076270 `gIdentityMtx` (src/334D0.c, used by the RSP
   display-list path) is also identity. **Recommended:** rename ours at 0x80076270 (e.g.
   `gIdentityMtxDisplay`) to make room, then adopt `gCamProjectionMatrix → gIdentityMtx`.

3. **102-row MusyX family — out of ma1 scope by policy, and OURS are the real library names.**
   The whole `Mus*` / `F*` / `__MusInt*` block (0x80037FB0-0x8003C408) diverges: michiiik renamed
   the vendored **numus/MusyX middleware** to `Audio_*` (their `src/libnumus/player.c` literally
   defines `Audio_InitializeVoiceManager(musConfig*)`). Our names (MusInitialize, MusStartSoundEffect,
   Fstop/Fwave/Fport…, __MusIntProcessEnvelope) are the genuine numus SDK API names inherited from
   the `Add libnumus` commit (969c424). **OURS-BETTER** — but these were never ma1 rows, so there
   is nothing to revert; the value is upstream (offering michiiik the real API names) rather than
   local. The remaining ~20 of the "36 dropped" in RENAME_PLAN are most likely style/typedef
   vetoes that leave no address divergence (no log was kept — flagged as a process gap).

## 5. Recommended reversions (ready-to-append ledger rows)

Direction: `their_live_name → our_old_name`. 95 rows: the 3 code-verified singles + 92
validated-field particle accessors (excludes `Particle_RotateX` — our axis label was wrong — and
`Particle_StartVerticalMotionTimer` — unverified semantics).

```tsv
Text_GetTmHmName	GetItemName	rev1		ma1 reversal: ids 1..0x53 index the item-name table (first entry Master Ball; michiiik comment: "item names, dead data"); their name describes only the TM/HM sprintf branches	pending
TeamSelection_RegisteredTeam_GetNext	GetPrevPage	rev1		ma1 reversal: michiiik GetNext/GetPrevious are direction-swapped vs the chain build (unk_4D24=(i+1)&3 is next; MoveListDown walks it with page index++)	pending
TeamSelection_RegisteredTeam_GetPrevious	GetNextPage	rev1		ma1 reversal: michiiik GetNext/GetPrevious are direction-swapped vs the chain build (unk_4D28=(i-1)&3 is previous; MoveListUp walks it)	pending
```

Plus these 92 particle-field rows (same justification for all:
`ma1 reversal: michiiik kept raw offset name; our semantic name is validated by michiiik's own semantic users of the same fields (rotation 0x94, rot-speed 0x9A, target 0xA0, velocity 0x50/0x38, speed 0x74, rate 0x78, scale 0x1C, timers 0xA6/0xA8)`):

```tsv
Particle_Field50_SetXScaled_098E8	Particle_SetVelocityX	rev1		<justification above>	pending
Particle_Field50_SetYScaled_09900	Particle_SetVelocityY	rev1		<justification above>	pending
Particle_Field50_SetZScaled_09918	Particle_SetVelocityZ	rev1		<justification above>	pending
Particle_Field50_AddVecScaled_09968	Particle_AddVelocity	rev1		<justification above>	pending
Particle_Field50_AddXScaled_099C0	Particle_AddScaledVelocityX	rev1		<justification above>	pending
Particle_Field50_AddYScaled_099E0	Particle_AddScaledVelocityY	rev1		<justification above>	pending
Particle_Field50_AddZScaled_09A00	Particle_AddScaledVelocityZ	rev1		<justification above>	pending
Particle_Field50_SubXScaled_09A78	Particle_SubtractScaledVelocityX	rev1		<justification above>	pending
Particle_Field50_SubYScaled_09A98	Particle_SubtractScaledVelocityY	rev1		<justification above>	pending
Particle_Field50_SubZScaled_09AB8	Particle_SubtractScaledVelocityZ	rev1		<justification above>	pending
Particle_Field50_SubVecScaled_09A20	Particle_SubtractScaledVelocityXYZ	rev1		<justification above>	pending
Particle_Field50_ApproachXToField5C_09AD8	Particle_ApproachVelocityX	rev1		<justification above>	pending
Particle_Field50_ApproachYToField5C_09B18	Particle_ApproachVelocityY	rev1		<justification above>	pending
Particle_Field50_ApproachZToField5C_09B58	Particle_ApproachVelocityZ	rev1		<justification above>	pending
Particle_Field50_SetVecFromField7C_09B98	Particle_CopyVelocityFromTarget	rev1		<justification above>	pending
Particle_Field50_SetXYFromField7C_09BC8	Particle_CopyVelocityXYFromTarget	rev1		<justification above>	pending
Particle_Field50_SetXZFromField7C_09BB4	Particle_CopyVelocityXZFromTarget	rev1		<justification above>	pending
Particle_Field50_AddVecFromField7C_09BDC	Particle_AddVelocityFromTarget	rev1		<justification above>	pending
Particle_Field50_AddXFromField7C_09C58	Particle_AddVelocityXFromTarget	rev1		<justification above>	pending
Particle_Field50_AddXYFromField7C_09C34	Particle_AddVelocityXYFromTarget	rev1		<justification above>	pending
Particle_Field50_AddXZFromField7C_09C10	Particle_AddVelocityXZFromTarget	rev1		<justification above>	pending
Particle_Field50_AddYFromField7C_09C6C	Particle_AddVelocityYFromTarget	rev1		<justification above>	pending
Particle_Field50_AddZFromField7C_09C80	Particle_AddVelocityZFromTarget	rev1		<justification above>	pending
Particle_Field50_AddNegField74Y_CheckField2CYNonPositive_09F84	Particle_FallAndCheckGround	rev1		<justification above>	pending
Particle_Field38_SetVec_08C68	Particle_SetVelocityDirectXYZ	rev1		<justification above>	pending
Particle_Field38_SetVecFromVec3fScaled_08C20	Particle_SetVelocityScaledVec	rev1		<justification above>	pending
Particle_Field38_SetXScaled_08C88	Particle_SetVelocityXScaled	rev1		<justification above>	pending
Particle_Field38_SetYScaled_08CA0	Particle_SetVelocityYScaled	rev1		<justification above>	pending
Particle_Field38_SetZScaled_08CB8	Particle_SetVelocityZScaled	rev1		<justification above>	pending
Particle_Field38_AddVecFromVec3f_08DD8	Particle_AddVelocityDirectVec	rev1		<justification above>	pending
Particle_Field38_AddVecScaledFromVec3f_08D78	Particle_AddVelocityScaledVec	rev1		<justification above>	pending
Particle_Field38_AddVecScaled_08E18	Particle_AddVelocityScaledXYZ	rev1		<justification above>	pending
Particle_Field38_AddXScaled_08E70	Particle_AddVelocityXScaled	rev1		<justification above>	pending
Particle_Field38_AddYScaled_08E90	Particle_AddVelocityYScaled	rev1		<justification above>	pending
Particle_Field38_AddZScaled_08EB0	Particle_AddVelocityZScaled	rev1		<justification above>	pending
Particle_Field38_AddXZFromField94Y_08ED0	Particle_AddVelocityForward	rev1		<justification above>	pending
Particle_Field38_AddXZFromField94YOffset180_08F38	Particle_AddVelocityBackward	rev1		<justification above>	pending
Particle_Field38_AddXZFromField94YOffsetMinus90_0901C	Particle_AddVelocityLeft	rev1		<justification above>	pending
Particle_Field38_AddXZFromField94YOffset90_08FAC	Particle_AddVelocityRight	rev1		<justification above>	pending
Particle_Field74_SetScaled_0AD8C	Particle_SetSpeed	rev1		<justification above>	pending
Particle_Field74_Approach_0ADBC	Particle_ApproachSpeedScaled	rev1		<justification above>	pending
Particle_Field74_ApproachUsingField78_0AE00	Particle_ApproachSpeed	rev1		<justification above>	pending
Particle_Field74_AdvanceAndAddNegY_CheckField2CYNonPositive_09FD8	Particle_FallAccelerateAndCheckGround	rev1		<justification above>	pending
Particle_Field78_SetScaled_0ADA4	Particle_SetAcceleration	rev1		<justification above>	pending
Particle_Field78_Approach_0AE40	Particle_ApproachAcceleration	rev1		<justification above>	pending
Particle_Field94_SetVecFromVec3s_0A24C	Particle_SetRotationFromVec3s	rev1		<justification above>	pending
Particle_Field94_SetX_0A2A4	Particle_SetRotationX	rev1		<justification above>	pending
Particle_Field94_SetY_0A2B8	Particle_SetRotationY	rev1		<justification above>	pending
Particle_Field94_SetZ_0A2CC	Particle_SetRotationZ	rev1		<justification above>	pending
Particle_Field94_AddXConstant_0A30C	Particle_AddRotationX	rev1		<justification above>	pending
Particle_Field94_AddYConstant_0A320	Particle_AddRotationY	rev1		<justification above>	pending
Particle_Field94_AddZConstant_0A334	Particle_AddRotationZ	rev1		<justification above>	pending
Particle_Field94_AddConstantAll_0A2E0	Particle_AddRotationAllAxes	rev1		<justification above>	pending
Particle_Field94_AddY_0A594	Particle_RotateY	rev1		<justification above>	pending
Particle_Field94_AddVec_0A52C	Particle_AddRotationDeltaXYZ	rev1		<justification above>	pending
Particle_Field94_AddVecFromVec3s_0A4F0	Particle_AddRotationDeltaVec	rev1		<justification above>	pending
Particle_Field94_AddVecFromField9A_0A480	Particle_AddRotationDelta	rev1		<justification above>	pending
Particle_Field94_AddXFromField9A_0A4B4	Particle_AddRotationDeltaX	rev1		<justification above>	pending
Particle_Field94_AddYFromField9A_0A4C8	Particle_AddRotationDeltaY	rev1		<justification above>	pending
Particle_Field94_AddZFromField9A_0A4DC	Particle_AddRotationDeltaZ	rev1		<justification above>	pending
Particle_Field94_SubVecFromVec3s_0A600	Particle_SubtractRotationDeltaVec	rev1		<justification above>	pending
Particle_Field94_SubX_0A63C	Particle_SubtractRotationDeltaX	rev1		<justification above>	pending
Particle_Field94_SubY_0A658	Particle_SubtractRotationDeltaY	rev1		<justification above>	pending
Particle_Field94_SubZ_0A674	Particle_SubtractRotationDeltaZ	rev1		<justification above>	pending
Particle_Field94_DecrementXTo_0A7DC	Particle_DecreaseRotationXTowards	rev1		<justification above>	pending
Particle_Field94_DecrementYTo_0A810	Particle_DecreaseRotationYTowards	rev1		<justification above>	pending
Particle_Field94_DecrementZTo_0A844	Particle_DecreaseRotationZTowards	rev1		<justification above>	pending
Particle_Field9A_SetVecFromVec3s_0A37C	Particle_SetRotationDeltaFromVec3s	rev1		<justification above>	pending
Particle_Field9A_SetXY_0A3A0	Particle_SetRotationDeltaXY	rev1		<justification above>	pending
Particle_Field9A_SetX_0A3C4	Particle_SetRotationDeltaX	rev1		<justification above>	pending
Particle_Field9A_SetY_0A3D8	Particle_SetRotationDeltaY	rev1		<justification above>	pending
Particle_Field9A_SetZ_0A3EC	Particle_SetRotationDeltaZ	rev1		<justification above>	pending
Particle_FieldA0_SetX_0A400	Particle_SetTargetRotationX	rev1		<justification above>	pending
Particle_FieldA0_SetY_0A414	Particle_SetTargetRotationY	rev1		<justification above>	pending
Particle_Field1C_SetScaled_0B938	Particle_SetScaleFactor1	rev1		<justification above>	pending
Particle_Field1C_Approach_0B98C	Particle_ApproachScaleFactor1	rev1		<justification above>	pending
Particle_Field1C_ApproachAndStepState_0B9D0	Particle_ApproachScaleFactor1WithCallback	rev1		<justification above>	pending
Particle_Field1C_ApproachField24ByField20_0BA1C	Particle_ApproachScaleFactor2	rev1		<justification above>	pending
Particle_Field1C_ApproachField24AndStepState_0BA48	Particle_ApproachScaleFactor2WithCallback	rev1		<justification above>	pending
Particle_FieldA6_SetS16_0BCA8	Particle_SetTimerA6	rev1		<justification above>	pending
Particle_FieldA6_GetS16_0BCBC	Particle_GetTimerA6	rev1		<justification above>	pending
Particle_FieldA6_DecrementTo_0BCC4	Particle_DecrementTimerA6Clamp	rev1		<justification above>	pending
Particle_FieldA6_DecrementToZero_0BD08	Particle_DecrementTimerA6By	rev1		<justification above>	pending
Particle_FieldA6_DecrementToZeroAndStepState_0BD34	Particle_DecrementTimerA6ByWithCallback	rev1		<justification above>	pending
Particle_FieldA6_DecrementToStep1_0BD80	Particle_DecrementTimerA6To	rev1		<justification above>	pending
Particle_FieldA6_DecrementToZeroStep1_0BDAC	Particle_DecrementTimerA6ToZero	rev1		<justification above>	pending
Particle_FieldA6_DecrementToZeroStep1AndStepState_0BDD0	Particle_DecrementTimerA6ToZeroWithCallback	rev1		<justification above>	pending
Particle_FieldA8_SetS16_0BE14	Particle_SetTimerA8	rev1		<justification above>	pending
Particle_FieldA8_GetS16_0BE28	Particle_GetTimerA8	rev1		<justification above>	pending
Particle_FieldA8_DecrementTo_0BE30	Particle_DecrementTimerA8Clamp	rev1		<justification above>	pending
Particle_FieldA8_DecrementToZeroStep1_0BE6C	Particle_DecrementTimerA8ToZero	rev1		<justification above>	pending
Particle_FieldA8_DecrementToZeroStep1AndStepState_0BE8C	Particle_DecrementTimerA8ToZeroWithCallback	rev1		<justification above>	pending
```

Owner note: these 95 reversions deliberately re-diverge from michiiik in exactly the spots where
their name is wrong (page direction) or raw (FieldXX). If pure convergence wins after all, only
the two page-direction rows really deserve to persist.

## 6. Five representative synonym examples (of ~4,355)

1. `GbAudio_StepSquare1 → GbApu_UpdateSquare1Channel` — Audio→Apu domain word + Step→Update verb, same function.
2. `Vec3f_Copy → ParticleMath_CopyVec3f` — module prefix + word order only.
3. `Game_RunTitleScreen → State_TitleScreen` — naming philosophy: our run-loop verb vs their state-machine noun for the same top-level handler.
4. `ParticleEffect_FireworksState → BattleAnim_CallbackStartEffect8ModelBurstEmitter` — same callback, theirs encodes the effect-table IDs (Effect8) where ours encoded the visual (fireworks); both true, different perspective.
5. `ApproachFloatUp → ParticleMath_ApproachFloatUp` — pure module-prefix addition.

## 7. Process notes

- The ma1 generator kept no skip log; the "36 dropped" figure had to be reconstructed (22
  address-divergent rows found; the rest were likely typedef/style vetoes that leave no trace).
  Recommend future waves log rejects with a reason code.
- The justification column of the ma1 ledger rows is boilerplate (address + both names) — fine for
  provenance, but it is not evidence; this report's verdicts come from reading the code.
- MusyX finding (§4.3) is the strongest "we know something they don't" artifact from this review:
  102 symbols where our tree carries the genuine numus SDK names and theirs are invented
  `Audio_*` descriptions — candidate material for the planned upstream contributions to michiiik.
