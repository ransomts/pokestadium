#include "fragment31.h"
#include "32D10.h"
#include "12D80.h"
#include "6A40.h"

// .data
static Gfx gFragment31SetupDL[] = {
    gsDPPipeSync(),
    gsDPSetCombineLERP(TEXEL1, TEXEL0, ENV_ALPHA, TEXEL0, TEXEL1, TEXEL0, ENVIRONMENT, TEXEL0, COMBINED, 0, SHADE, 0, COMBINED, 0, PRIM_LOD_FRAC, 0),
    gsDPSetEnvColor(0xFF, 0xFF, 0xFF, 0x64),
    gsSPEndDisplayList(),
};

// .bss
static s16 gFragment31ScrollOffset;

void Fragment31_BuildDisplayList(Gfx* gfx, DisplayListAddresses* addresses) {
    s16 temp_t3;
    s16 temp_t4;
    s16 temp_t2;
    u8 temp_v0;

    temp_v0 = GraphRoot_GetCurrentModelSlot();
    if (gDefaultGraphRoot->unk_01C == 0) {
        temp_t2 = (gFragment31ScrollOffset >> 4);
        temp_t3 = 0x4000 - (u16)(gFragment31ScrollOffset >> 4);
        temp_t4 = 0x4000 - (gFragment31ScrollOffset >> 3);

        gSPDisplayList(gfx++, gFragment31SetupDL);
        gDPLoadTextureTile(gfx++, addresses->segments[0], G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 0, 0, 0, 31, 31, 0,
                           G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, 5, 5, G_TX_NOLOD, G_TX_NOLOD);
        gDPSetTileSize(gfx++, 0, temp_t2, temp_t3, temp_t2 + 31, temp_t3 + 31);
        gDPLoadMultiTile(gfx++, addresses->segments[1], 0x0100, 1, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 0, 0, 0, 31, 31, 0,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, 5, 5, G_TX_NOLOD, G_TX_NOLOD);
        gDPSetTileSize(gfx++, 1, temp_t3, temp_t4, temp_t3, temp_t4 + 31);

        if (gModelUpdateFlag[temp_v0 & 1] == 0) {
            if (ModelPhase_IsIdle() == 0) {
                gFragment31ScrollOffset--;
            }
        }
    }
    gSPEndDisplayList(gfx++);
}

void Fragment31_Init(s32 arg0, DisplayListState* state) {
    Gfx* gfx;
    DisplayListAddresses* addresses;

    if (arg0 == 2) {
        addresses = state->addresses;
        gfx = GfxAlloc(0xF0);
        state->gfx = gfx;
        Fragment31_BuildDisplayList(gfx, addresses);
    }
}
