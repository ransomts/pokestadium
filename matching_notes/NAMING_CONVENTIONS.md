# Symbol Naming Conventions (Derived from michiiik's 7,378 Existing Names)

## Domain Prefixes (by frequency in their tree)

| Domain | Count | Use for |
|---|---|---|
| Battle | 2019 | Battle logic, damage, turns, AI |
| Particle | 513 | Particle system internals |
| Lab | 506 | Pokemon Lab screens |
| Gb | 374 | Game Boy pak/transfer/emulation |
| Gallery | 308 | Photo gallery |
| Audio | 209 | Sound, music, sequencing |
| Trade | 205 | Trade system |
| Widget | 178 | UI widget framework |
| Rental | 154 | Rental system |
| Team | 146 | Team selection/management |
| Geo | 112 | Geometry, graphs, display nodes |
| Mini | 98 | Minigames (prefix Mini*Game) |
| Model | 86 | 3D model system |
| Sushi | 67 | Sushi Go Round minigame |
| Pokedex | 61 | Pokedex |
| Display | 57 | Display object system |
| Event | 57 | Event battle |
| Clefairy | 57 | Clefairy minigame |
| Gfx | 47 | Direct GPU commands |
| Poke | 46 | Pokemon icon system |
| Save | 44 | Save system |
| Intro | 44 | Intro sequence |
| Glc | 42 | Game Link Cable |
| Diorama | 39 | Diorama mode |
| Storage | 34 | Storage system |
| Ekans | 33 | Ekans minigame |
| Transfer | 33 | Transfer pak |
| Free | 33 | Free battle |

**RULE**: Check this table before choosing a domain. If your function
draws things → "Draw" (not "Render" or "Paint"). If it manages Pokemon Lab
screens → "Lab". If it's about the GB pak → "Gb".

## Verb Conventions (by frequency)

| Verb | Count | Use for | Don't use |
|---|---|---|---|
| Draw | 699 | Rendering/GPU output | NOT Render, Paint, Display |
| Set | 408 | Setting values | NOT Update (for values), Write |
| Update | 373 | Per-frame changes | NOT Set (for per-frame), Tick |
| Init | 329 | Initialization | NOT Initialize (Init is 7x more common) |
| Callback | 319 | Callback registration | NOT Handler (only 9 uses!) |
| Get | 252 | Simple retrieval | NOT Fetch, Retrieve, Read |
| Load | 249 | IO/complex retrieval | NOT Get (use for IO/decompression) |
| Start | 153 | Begin operation | NOT Begin, Enter |
| Build | 109 | Construct complex structures | NOT Create, Make |
| Reset | 103 | Restore to initial state | NOT Clear (use Clear for emptying) |
| Is | 97 | Boolean checks | NOT Check, Has, Should |
| Handle | 84 | Process input/commands | NOT Process, Execute |
| Apply | 74 | Apply computed values | NOT Set (for computed) |
| Add | 74 | Append to collection | NOT Push, Insert |
| Clear | 69 | Empty/remove all | NOT Reset (use Reset for restore) |
| Setup | 63 | Configure parameters | NOT Init (use Init for allocation) |
| Run | 65 | Execute main logic | NOT Execute, Perform |
| Approach | 58 | Gradual/lamped changes | NOT Lerp, Interpolate (use Approach) |
| Queue | 54 | Deferred operations | NOT Schedule, Post |
| Advance | 54 | State progression | NOT Next, Increment |
| Play | 52 | Audio/animation | NOT Start (use Play for media) |
| Show | 49 | Display UI element | NOT Draw (Show is higher-level) |

**KEY RULES**:
- Use "Callback" not "Handler" (385 vs 9 uses)
- Use "Init" not "Initialize" (329 vs 48)
- Use "Draw" not "Render" (699 vs 0)
- Use "Approach" for gradual changes (it's their specific term)

## Noun Conventions

| Concept | Count | Convention | Example |
|---|---|---|---|
| state | 206 | State for state machines | gCurrentGameState |
| callback | 385 | Callback for function pointers | Fragment_FreeCallback |
| table | 364 | Table for lookup arrays | gDisplayListHead |
| color | 125 | Color for color values | ClearColor |
| rotation | 134 | Rot (abbreviated) | miniCameraXRot |
| position | 90 | Pos or Coord | posX, Coord |
| velocity | 86 | Speed or Vel | ModelAnim_SetSpeed |
| count | 82 | Count for quantities | count |
| buffer | 42 | Buffer for memory | LEO_TempBuffer |
| timer | 21 | Timer for time | leoReadTimer |
| flag | 73 | Flag for booleans | gStickerStationInitFlag |
| alpha | 73 | Alpha (not fadeLevel) | Model_SetMaterialAlpha |
| level | 34 | Level for progression | Pokemon_ExpForLevel |

**KEY RULES**:
- Use "Table" for lookup arrays (364 uses, not "Array" or "List")
- Use "Count" for quantities (not "Size" or "Length" or "Num")
- Use "Flag" for boolean indicators (73 uses)
- Use "Alpha" for opacity (not "Fade" or "FadeLevel")
- Use "Speed" for velocity magnitude (86 uses, "Speed" > "Vel")
- Use "Rot" abbreviation for rotation (134 uses)

## Anti-Patterns to Avoid

1. **Double domain prefix**: Battle_BattleScene_... (they have ZERO instances)
2. **"Handler" suffix**: Use "Callback" instead (9 vs 385 uses)
3. **"Initialize"**: Use "Init" (48 vs 329 uses)
4. **"Render"**: Use "Draw" (0 vs 699 uses)
5. **"Process"**: Not in top 25 verbs — use Handle, Update, or Run
6. **"Execute"**: Not used — use Run or Handle
7. **"Fetch"**: Not used — use Get or Load
8. **Abbreviation "Tex"**: Used 37 times, acceptable but "Texture" is clearer

## Common Abbreviation Conventions

| Abbreviation | Count | When to use |
|---|---|---|
| Tex | 37 | Texture (in struct field names) |
| Dma | 4 | DMA (in hardware contexts) |
| Init | 329 | Initialize (always) |
| Pos | ~90 | Position (in field names) |
| Rot | 134 | Rotation (in field names) |
| Coord | ~20 | Coordinate (in full function names) |

**RULE**: Abbreviations are fine in struct FIELDS (pos, rot, tex) but
spell out in FUNCTION names (Position, Rotation, Texture).

## Boolean Naming

| Pattern | Example | Use for |
|---|---|---|
| Is prefix | IsByteInArray | Checking a property |
| Has prefix | (not used) | Possession check |
| Can prefix | (not used) | Capability check |
| suffix Flag | gStickerStationInitFlag | State indicator |
| suffix Enabled | (not used) | Feature toggle |

**RULE**: Use "Is" prefix for boolean-returning functions (97 uses).
Use "Flag" suffix for boolean variables (73 uses).

## Event/Callback Naming

| Pattern | Count | Example |
|---|---|---|
| *Callback | 319 | Fragment_FreeCallback |
| On* | (not used) | — |
| *_*Handler | 9 | Audio_PlayMusicSequenceHandler |

**RULE**: Name callbacks by WHAT they do, not by "Callback" alone.
`Fragment_FreeCallback` (what it does + Callback suffix).
Use "Callback" suffix, not "Handler" (except in 9 rare cases where Handler
has a specific meaning in the Audio domain).

## State Machine Naming

| Pattern | Example |
|---|---|
| *State suffix | gCurrentGameState |
| State prefix | StateMachine_* |
| *Phase suffix | Intro_PhaseTitle |
| Mode in name | Camera_SetMode |

**RULE**: Use "State" for high-level game states (206 uses).
Use "Phase" for sub-states within a state. Use "Mode" for operational modes.
