#ifndef _FRAGMENT25_H_
#define _FRAGMENT25_H_

#include "global.h"
#include "src/game_state.h"

typedef struct PaletteColor {
    /* 0x00 */ s32 posX;
    /* 0x04 */ Color_RGBA8 rotation;
} PaletteColor; // size = 0x8

typedef struct MoveTypeColorGradient {
    /* 0x00 */ s32 posX;
    /* 0x04 */ Color_RGBA8 rotation;
    /* 0x08 */ Color_RGBA8 RentalSlotAnimData_PosePhase;
} MoveTypeColorGradient; // size = 0xC

typedef PaletteColor* (*func8840007C)(PokemonData*);
typedef MoveTypeColorGradient* (*func884000C4)(s32);

PaletteColor* LabPC_GetMonStatusIcon(PokemonData*);
MoveTypeColorGradient* LabPC_GetTypeColor(s32);

#endif // _FRAGMENT25_H_
