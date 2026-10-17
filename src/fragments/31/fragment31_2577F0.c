#include "fragment31.h"
#include "32D10.h"
#include "12D80.h"
#include "6A40.h"

// .data
static Gfx D_81004170[] = {
    gsDPPipeSync(),
    gsDPSetCombineLERP(TEXEL1, TEXEL0, ENV_ALPHA, TEXEL0, TEXEL1, TEXEL0, ENVIRONMENT, TEXEL0, COMBINED, 0, SHADE, 0, COMBINED, 0, PRIM_LOD_FRAC, 0),
    gsDPSetEnvColor(0xFF, 0xFF, 0xFF, 0x64),
    gsSPEndDisplayList(),
};

// .bss
static s16 D_81004B60;

void func_81002530(Gfx* gfx, DisplayListAddresses* addresses) {
    s16 temp_t3;
    s16 temp_t4;
    s16 temp_t2;
    u8 temp_v0;

    temp_v0 = func_800325B4();
    if (D_8006F09C->unk_01C == 0) {
        temp_t2 = (D_81004B60 >> 4);
        temp_t3 = 0x4000 - (u16)(D_81004B60 >> 4);
        temp_t4 = 0x4000 - (D_81004B60 >> 3);

        gSPDisplayList(gfx++, D_81004170);
        gDPLoadTextureTile(gfx++, addresses->segments[0], G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 0, 0, 0, 31, 31, 0,
                           G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, 5, 5, G_TX_NOLOD, G_TX_NOLOD);
        gDPSetTileSize(gfx++, 0, temp_t2, temp_t3, temp_t2 + 31, temp_t3 + 31);
        gDPLoadMultiTile(gfx++, addresses->segments[1], 0x0100, 1, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 0, 0, 0, 31, 31, 0,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, 5, 5, G_TX_NOLOD, G_TX_NOLOD);
        gDPSetTileSize(gfx++, 1, temp_t3, temp_t4, temp_t3, temp_t4 + 31);

        if (D_800AF7B0[temp_v0 & 1] == 0) {
            if (func_800325AC() == 0) {
                D_81004B60--;
            }
        }
    }
    gSPEndDisplayList(gfx++);
}

void func_810027E0(s32 arg0, DisplayListState* state) {
    Gfx* gfx;
    DisplayListAddresses* addresses;

    if (arg0 == 2) {
        addresses = state->addresses;
        gfx = GfxAlloc(0xF0);
        state->gfx = gfx;
        func_81002530(gfx, addresses);
    }
}
