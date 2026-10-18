#include "fragment31.h"
#include "src/fragments/7/fragment7.h"
#include "src/fragments/8/fragment8.h"
#include "src/fragments/50/fragment50.h"
#include "src/6A40.h"
#include "src/12D80.h"
#include "src/32D10.h"

typedef struct {
    /* 0x00 */ u8 rgb0[3];      // start color
    /* 0x03 */ u8 frameStart;   // frame where this keyframe begins
} Keyframe;  // size = 0x04

// .bss
static s32 gFragment31_Tex0Counter;
static u8 pad_D_81004B78[0x8];
static s32 gFragment31_Tex1Counter;
static u8 pad_D_81004B88[0x8];
static s32 gFragment31_Tex2Counter;
static u8 pad_D_81004B98[0x8];
static s32 gFragment31_Tex3Counter;
static u8 pad_D_81004BA8[0x8];
static s32 gFragment31_NumberDrawPhase;
static char gFragment31_NumberStringBuffer[0x28];

void Fragment31_LoadTexture0(Gfx* gfx, u16* arg1, u8* arg2) {
    gDPPipeSync(gfx++);
    gSPTexture(gfx++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);
    gDPSetTextureLUT(gfx++, G_TT_RGBA16);
    gDPLoadTLUT_pal256(gfx++, arg1);
    gDPLoadTextureTile(gfx++, (arg2 + ((gRacePlayerScreenY[0] * 4) & ~0x1F) + ((gFragment31_Tex0Counter & 3) << 0xB)), G_IM_FMT_CI, G_IM_SIZ_8b, 0x20, 0x40, 0, 0, 0x20 - 1, 0x40 - 1, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, 5, 6, G_TX_NOLOD, G_TX_NOLOD);
    gSPEndDisplayList(gfx++);
}

void Fragment31_Tex0StateHandler(s32 arg0, DisplayListState* state) {
    Gfx* gfx;
    DisplayListAddresses* addresses;

    addresses = state->addresses;
    switch (arg0) {
    case 0:
        gFragment31_Tex0Counter = 0;
        return;
    case 2:
        gfx = GfxAlloc(0xA0);
        state->gfx = gfx;
        Fragment31_LoadTexture0(gfx, addresses->segments[0], addresses->segments[1]);
        gFragment31_Tex0Counter += 1;
        return;
    }
}

void Fragment31_LoadTexture1(Gfx* gfx, u16* arg1, u8* arg2) {
    gDPPipeSync(gfx++);
    gSPTexture(gfx++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);
    gDPSetTextureLUT(gfx++, G_TT_RGBA16);
    gDPLoadTLUT_pal256(gfx++, arg1);
    gDPLoadTextureTile(gfx++, (arg2 + ((gRacePlayerScreenY[1] * 4) & ~0x1F) + ((gFragment31_Tex1Counter & 3) << 0xB)), G_IM_FMT_CI, G_IM_SIZ_8b, 0x20, 0x40, 0, 0, 0x20 - 1, 0x40 - 1, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, 5, 6, G_TX_NOLOD, G_TX_NOLOD);
    gSPEndDisplayList(gfx++);
}

void Fragment31_Tex1StateHandler(s32 arg0, DisplayListState* state) {
    Gfx* gfx;
    DisplayListAddresses* addresses;

    addresses = state->addresses;
    switch (arg0) {                                 /* irregular */
    case 0:
        gFragment31_Tex1Counter = 0;
        return;
    case 2:
        gfx = GfxAlloc(0xA0);
        state->gfx = gfx;
        Fragment31_LoadTexture1(gfx, addresses->segments[0], addresses->segments[1]);
        gFragment31_Tex1Counter += 1;
        return;
    }
}

void Fragment31_LoadTexture2(Gfx* gfx, u16* arg1, u8* arg2) {
    gDPPipeSync(gfx++);
    gSPTexture(gfx++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);
    gDPSetTextureLUT(gfx++, G_TT_RGBA16);
    gDPLoadTLUT_pal256(gfx++, arg1);
    gDPLoadTextureTile(gfx++, (arg2 + ((gRacePlayerScreenY[2] * 4) & ~0x1F) + ((gFragment31_Tex2Counter & 3) << 0xB)), G_IM_FMT_CI, G_IM_SIZ_8b, 0x20, 0x40, 0, 0, 0x20 - 1, 0x40 - 1, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, 5, 6, G_TX_NOLOD, G_TX_NOLOD);
    gSPEndDisplayList(gfx++);
}

void Fragment31_Tex2StateHandler(s32 arg0, DisplayListState* state) {
    Gfx* gfx;
    DisplayListAddresses* addresses;

    addresses = state->addresses;
    switch (arg0) {                                 /* irregular */
    case 0:
        gFragment31_Tex2Counter = 0;
        return;
    case 2:
        gfx = GfxAlloc(0xA0);
        state->gfx = gfx;
        Fragment31_LoadTexture2(gfx, addresses->segments[0], addresses->segments[1]);
        gFragment31_Tex2Counter += 1;
        return;
    }
}

void Fragment31_LoadTexture3(Gfx* gfx, u16* arg1, u8* arg2) {
    gDPPipeSync(gfx++);
    gSPTexture(gfx++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);
    gDPSetTextureLUT(gfx++, G_TT_RGBA16);
    gDPLoadTLUT_pal256(gfx++, arg1);
    gDPLoadTextureTile(gfx++, (arg2 + ((gRacePlayerScreenY[3] * 4) & ~0x1F) + ((gFragment31_Tex3Counter & 3) << 0xB)), G_IM_FMT_CI, G_IM_SIZ_8b, 0x20, 0x40, 0, 0, 0x20 - 1, 0x40 - 1, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, 5, 6, G_TX_NOLOD, G_TX_NOLOD);
    gSPEndDisplayList(gfx++);
}

void Fragment31_Tex3StateHandler(s32 arg0, DisplayListState* state) {
    Gfx* gfx;
    DisplayListAddresses* addresses;

    addresses = state->addresses;
    switch (arg0) {                                 /* irregular */
    case 0:
        gFragment31_Tex3Counter = 0;
        return;
    case 2:
        gfx = GfxAlloc(0xA0);
        state->gfx = gfx;
        Fragment31_LoadTexture3(gfx, addresses->segments[0], addresses->segments[1]);
        gFragment31_Tex3Counter += 1;
        return;
    }
}

void Fragment31_DrawAnimatedTile(s32 arg0, DisplayListState* state) {
    static u8 gFragment31_AnimatedTileCounter = 0;
    s32 temp_a1;
    s32 temp_a2;
    Gfx* gfx;

    if (arg0 == 2) {
        gfx = GfxAlloc(0x10);
        temp_a1 = gFragment31_AnimatedTileCounter * 3;
        temp_a2 = gFragment31_AnimatedTileCounter * -6;
        state->gfx = gfx;
        {    Gfx *_gfx = (Gfx *)(gfx++); _gfx->words.w0 = (((temp_a1 & 0xFFF) << 0xC) | 0xF2000000 | (temp_a2 & 0xFFF));    _gfx->words.w1 = ((((0x27F << (temp_a1 + 2)) & 0xFFF) << 0xC) | ((0x7F << (temp_a2 + 2)) & 0xFFF));    }
        gSPEndDisplayList(gfx++);
        gFragment31_AnimatedTileCounter++;
        gFragment31_AnimatedTileCounter &= 0x7F;
    }
}

void Fragment31_AnimateColorCycle(s32 arg0, DisplayListState* state) {
    static u8 gFragment31_ColorCyclePhase = 0;
    static u8 gFragment31_ColorCycleFrame = 0;
    static Keyframe gFragment31_ColorCycleKeyframes[6] = {
        { { 0xFF, 0x32, 0x32 }, 0  },
        { { 0xC8, 0xC8, 0x00 }, 10 },
        { { 0x64, 0xFF, 0x00 }, 20 },
        { { 0x00, 0xC8, 0xFF }, 30 },
        { { 0x96, 0x32, 0xC8 }, 40 },
        { { 0xFF, 0x32, 0x32 }, 50 },
    };
    u8 i;
    u8 c;
    Keyframe* kf;
    Gfx* gfx;
    u8 sp48[3];
    
    if (arg0 == 2) {
        gfx = GfxAlloc(sizeof(Gfx) * 4);
        state->gfx = gfx;
        for (i = 0; i < 5; i++) {
            if (gFragment31_ColorCycleFrame == gFragment31_ColorCycleKeyframes[i].frameStart) {
                for(c = 0; c < 3; c++) {
                    sp48[c] = gFragment31_ColorCycleKeyframes[i].rgb0[c];
                }
                break;
            }
            if (gFragment31_ColorCycleKeyframes[i].frameStart < gFragment31_ColorCycleFrame && gFragment31_ColorCycleFrame < gFragment31_ColorCycleKeyframes[i + 1].frameStart) {
                for(c = 0; c < 3; c++) {
                    sp48[c] = (s32) (((f32) ((gFragment31_ColorCycleKeyframes[i + 1].rgb0[c] - gFragment31_ColorCycleKeyframes[i].rgb0[c]) * (gFragment31_ColorCycleFrame - gFragment31_ColorCycleKeyframes[i].frameStart)) / (f32) (gFragment31_ColorCycleKeyframes[i + 1].frameStart - gFragment31_ColorCycleKeyframes[i].frameStart)) + gFragment31_ColorCycleKeyframes[i].rgb0[c] + 0.5f);
                }
                break;
            }
        }
        gDPSetPrimColor(gfx++, 0, 0x80, sp48[0], sp48[1], sp48[2], 180);
        gDPSetTileSize(gfx++, 0, -2 * gFragment31_ColorCyclePhase, 0, (320 - 1) << ((-2 * gFragment31_ColorCyclePhase) + 2), (64 - 1) << 2);
        gDPSetTileSize(gfx++, 1, 2 * gFragment31_ColorCyclePhase, 0, (320 - 1) << ((2 * gFragment31_ColorCyclePhase) + 2), (64 - 1) << 2);
        gSPEndDisplayList(gfx++);
        gFragment31_ColorCyclePhase++;
        gFragment31_ColorCyclePhase &= 0x7F;
        gFragment31_ColorCycleFrame++;
        gFragment31_ColorCycleFrame &= 0xFF;
        if ((s32) gFragment31_ColorCycleFrame >= 0x32) {
            gFragment31_ColorCycleFrame = 0;
        }
    }
}

void Fragment31_DrawOverlay(Gfx* gfx) {
    s32 temp_a3;

    {    Gfx *_gfx = (Gfx *)(gfx++);    _gfx->words.w0 = 0xDE000000;    _gfx->words.w1 = &gCommonGfxInit;    }
    temp_a3 = ((s32) ((D_800AF770[5]) * 0x55) / 255) + 0xAA;
    {    Gfx *_gfx = (Gfx *)(gfx++);    _gfx->words.w0 = ((temp_a3 & 0xFF) | 0xFA000000);    _gfx->words.w1 = -0x3701;    }
    {    Gfx *_gfx = (Gfx *)(gfx++);    _gfx->words.w0 = 0xFB000000;    _gfx->words.w1 = 0x501E0AFF;    }
    {    Gfx *_gfx = (Gfx *)(gfx++);    _gfx->words.w0 = 0xFD700000;    _gfx->words.w1 = Util_ConvertAddrToVirtAddr(&D_3008000);    }
    {    Gfx *_gfx = (Gfx *)(gfx++);    _gfx->words.w0 = 0xF5700000;    _gfx->words.w1 = 0x07094260;    }
    {    Gfx *_gfx = (Gfx *)(gfx++);    _gfx->words.w0 = 0xE6000000;    _gfx->words.w1 = 0;    }
    {    Gfx *_gfx = (Gfx *)(gfx++);    _gfx->words.w0 = 0xF3000000;    _gfx->words.w1 = 0x070FF200;    }
    {    Gfx *_gfx = (Gfx *)(gfx++);    _gfx->words.w0 = 0xE7000000;    _gfx->words.w1 = 0;    }
    {    Gfx *_gfx = (Gfx *)(gfx++);    _gfx->words.w0 = 0xF5680800;    _gfx->words.w1 = 0x94260;    }
    {    Gfx *_gfx = (Gfx *)(gfx++);    _gfx->words.w0 = 0xF2000000;    _gfx->words.w1 = 0x7C03C;    }
    gSPEndDisplayList(gfx++);
    gFragment31_NumberDrawPhase = 0;
}

s32 StringLength(s8* arg0) {
    s32 var_v1;
    s8 temp_t7;
    s8* var_v0;

    var_v1 = 0;
    var_v0 = arg0;
    if (*arg0 != 0) {
        do {
            var_v1 += 1;
            var_v0 += 1;
        } while (var_v0[0] != 0);
    }
    return var_v1;
}

void Fragment31_DrawNumberDigit(Gfx* gfx) {
    u16 temp_v1;
    u8 sp4D;
    s32 pad[4];
    u8 var_v0 = gDefaultGraphRoot->modelPhase % 5;
    u8 temp_t0;
    char* sp34;
    Mtx* sp30;
    s32 sp2C;

    temp_t0 = D_800AF770[var_v0];
    switch (gFragment31_NumberDrawPhase) {
    case 0:
        sp4D = (((s32) (temp_t0 + 1) / 100) + 0x10) & 0xFF;
        break;
    case 1:
        sp4D = (((s32) ((s32) (temp_t0 + 1) % 100) / 10) + 0x10) & 0xFF;
        break;
    case 2:
        sp4D = (((s32) (temp_t0 + 1) % 10) + 0x10) & 0xFF;
        break;
    default:
        {
        sp34 = GetMessageString(0, 0, D_8267E760, temp_t0);
        sprintf(gFragment31_NumberStringBuffer, "%s     ", sp34);
        temp_v1 = gFragment31_NumberDrawPhase - 3;
        sp4D = GetCharIndexFromFontTables((u8) gFragment31_NumberStringBuffer[temp_v1]);
        sp2C = 0xA - StringLength((s8*)sp34);
        sp30 = GfxAlloc(sizeof(Mtx));
        guTranslate(sp30, (f32) sp2C * 32.0f, 0.0f, 0.0f);
        gSPMatrix(gfx++, sp30, G_MTX_NOPUSH | G_MTX_MUL | G_MTX_MODELVIEW);
        break;
        }
    }
    gDPLoadTextureTile(gfx++, Util_ConvertAddrToVirtAddr(D_3000000 + ((sp4D & 0xF) << 4) + ((((sp4D & 0xF0) >> 4) << 4) * 256)), G_IM_FMT_IA, G_IM_SIZ_8b, 256, 17, 0, 0, 16, 16, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, 5, 5, G_TX_NOLOD, G_TX_NOLOD);
    gSPEndDisplayList(gfx++);
    gFragment31_NumberDrawPhase++;
}

void Fragment31_CreateOverlay(s32 arg0, DisplayListState* state) {
    Gfx* gfx;

    if (arg0 == 2) {
        gfx = GfxAlloc(0xF0);
        state->gfx = gfx;
        Fragment31_DrawOverlay(gfx);
    }
}

void Fragment31_NumberDigitStateHandler(s32 arg0, DisplayListState* state) {
    Gfx* gfx;

    if (arg0 == 2) {
        gfx = GfxAlloc(0xA0);
        state->gfx = gfx;
        Fragment31_DrawNumberDigit(gfx);
    }
}
