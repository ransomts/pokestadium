#include "fragment37.h"
#include "src/1CF30.h"
#include "src/20330.h"
#include "src/29BA0.h"
#include "src/26820.h"
#include "src/2E110.h"
#include "src/3FB0.h"
#include "src/49790.h"
#include "src/4F410.h"
#include "src/6A40.h"
#include "src/DDC0.h"
#include "src/F420.h"
#include "src/controller.h"
#include "src/memory.h"
#include "src/stage_loader.h"
#include "src/math_util.h"

typedef struct AreaConfig {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s8 unk_06;
    /* 0x07 */ s8 unk_07;
    /* 0x08 */ s8 unk_08;
    /* 0x09 */ s8 unk_09;
    /* 0x0A */ Color_RGBA8 unk_0A;
} AreaConfig; // size = 0xE

typedef struct ParticlePos {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s16 unk_04;
} ParticlePos; // size = 0x6

typedef struct ParticleTrail {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ s16 unk_08;
    /* 0x0A */ s16 unk_0A;
    /* 0x0C */ ParticlePos unk_0C[4];
} ParticleTrail; // size = 0x24

typedef struct TileOverlay {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ Color_RGBA8 unk_08;
} TileOverlay; // size >= 0xC

static s16 gOverlayAlpha = 0;

static s16 gFadeStepCounter = 0;

static s16 gStateTransitionTable[] = {
    STATE_STADIUM_MENU,   STATE_FREE_BATTLE, STATE_GYM_LEADER_CASTLE, STATE_VS_MEWTWO,   STATE_KIDS_CLUB,
    STATE_VICTORY_PALACE, STATE_POKEMON_LAB, STATE_GB_TOWER,          STATE_MENU_SELECT,
};

static u8* gBackgroundTexturePtrs[] = {
    0x03006E60, 0x0300D060, 0x03013260, 0x03019460, 0x0301F660,
    0x03025860, 0x0302BA60, 0x03031C60, 0x03037E60, 0x0303E060,
};

static AreaConfig gTileConfigTable[9] = {
    { 0x012C, 0x00B9, 0x004B, 0x03, 0x04, 0x06, 0x07, { 0x32, 0x50, 0x96, 0x00 } },
    { 0x0208, 0x0118, 0x004B, 0x07, 0x08, 0x04, 0x08, { 0x32, 0x50, 0x96, 0x00 } },
    { 0x006E, 0x005A, 0x0041, 0x08, 0x06, 0x08, 0x03, { 0x32, 0x50, 0x96, 0x00 } },
    { 0x012C, 0x0041, 0x0041, 0x08, 0x00, 0x02, 0x07, { 0x32, 0x50, 0x96, 0x00 } },
    { 0x015E, 0x013B, 0x0050, 0x00, 0x08, 0x05, 0x01, { 0x32, 0x50, 0x96, 0x00 } },
    { 0x00BE, 0x014A, 0x0046, 0x06, 0x08, 0x08, 0x04, { 0x32, 0x50, 0x96, 0x00 } },
    { 0x0078, 0x00E6, 0x0041, 0x02, 0x05, 0x08, 0x00, { 0x32, 0x50, 0x96, 0x00 } },
    { 0x01FE, 0x0096, 0x0041, 0x03, 0x01, 0x00, 0x08, { 0x32, 0x50, 0x96, 0x00 } },
    { 0x012C, 0x00B9, 0x000A, 0x08, 0x08, 0x08, 0x08, { 0x32, 0x50, 0x96, 0x00 } },
};

static u8* gParticleTextures[] = { 0x03005000, 0x03005A20, 0x03006440, 0x03005A20 };

static char** gAreaMessageBank;
static BinArchive* gAreaAssetArchive;
static Vp gAreaViewport;
static Mtx gAreaProjMatrix;
static u8* gBgTexturePrimary;
static u8* gBgTextureSecondary;
static TileOverlay gTileOverlayState;
static ParticleTrail gParticleTrailState[3];
static s32 pad_D_822031D0[0x2];
static s16 gCurrentAreaIndex;
static s16 gPreviousAreaIndex;
static s16 gTransitionFrame;
static unk_func_80027FA0 gAreaAudioState;
static PlayerName gAreaPlayerName;

s32 GetControllerInputMask(s32 arg0) {
    u32 temp_a0 = osSetIntMask(1);

    if (!(HW_REG(PI_STATUS_REG, u32) & 3) && ((*(u32*)0xB0000D10 & 0xFFFF) != 0x400)) {
        arg0 = -0x40;
    }

    osSetIntMask(temp_a0);
    return arg0;
}

void DrawFullScreenTextureBlend(u8* arg0, u8* arg1, u8 arg2) {
    s32 i;
    s32 j;

    gDPPipeSync(gDisplayListHead++);
    gDPSetCycleType(gDisplayListHead++, G_CYC_2CYCLE);
    gDPSetRenderMode(gDisplayListHead++, G_RM_OPA_SURF, G_RM_OPA_SURF2);
    gDPSetTexturePersp(gDisplayListHead++, G_TP_NONE);
    gDPSetScissor(gDisplayListHead++, G_SC_NON_INTERLACE, 0, 0, 640, 480);
    gDPSetCombineLERP(gDisplayListHead++, TEXEL1, TEXEL0, ENV_ALPHA, TEXEL0, TEXEL1, TEXEL0, ENVIRONMENT, TEXEL0, 0, 0,
                      0, COMBINED, 0, 0, 0, COMBINED);
    gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, arg2);
    gDPPipeSync(gDisplayListHead++);

    for (i = 0; i < 0x1E0; i += 0x20) {
        for (j = 0; j < 0x280; j += 0x20) {
            gDPLoadTextureBlock(gDisplayListHead++, arg0, G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 16, 0,
                                G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK,
                                G_TX_NOLOD, G_TX_NOLOD);
            gDPLoadMultiBlock(gDisplayListHead++, arg1, 0x0100, 1, G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 16, 0,
                              G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK,
                              G_TX_NOLOD, G_TX_NOLOD);
            gSPTextureRectangle(gDisplayListHead++, j << 2, i << 2, (j + 0x20) << 2, (i + 0x20) << 2, G_TX_RENDERTILE,
                                0, 0, 0x0200, 0x0200);

            arg0 += 0x200;
            arg1 += 0x200;
        }
    }
}

Vtx* CreateTileVertices(void) {
    Vtx* temp_v0;
    s16 temp_s0;
    s16 temp_s6;
    s16 temp_s7;
    u8 temp_s2;
    u8 temp_s3;
    u8 temp_s4;
    u8 temp_s5;

    temp_s6 = gTileOverlayState.unk_00;
    temp_s7 = gTileOverlayState.unk_02;
    temp_s0 = gTileOverlayState.unk_04;
    temp_s2 = gTileOverlayState.unk_08.r;
    temp_s3 = gTileOverlayState.unk_08.g;
    temp_s4 = gTileOverlayState.unk_08.b;
    temp_s5 = gTileOverlayState.unk_08.a;

    temp_v0 = GfxAlloc(sizeof(Vtx) * 8);

    if (temp_v0 != NULL) {
        SetTileVertex(&temp_v0[0], temp_s6 - temp_s0, temp_s7 - temp_s0, -1, 0, 0, temp_s2, temp_s3, temp_s4, temp_s5);
        SetTileVertex(&temp_v0[1], temp_s6 - temp_s0, temp_s7 + temp_s0, -1, 0, 0x7E0, temp_s2, temp_s3, temp_s4,
                      temp_s5);
        SetTileVertex(&temp_v0[2], temp_s6 + temp_s0, temp_s7 + temp_s0, -1, 0x7E0, 0x7E0, temp_s2, temp_s3, temp_s4,
                      temp_s5);
        SetTileVertex(&temp_v0[3], temp_s6 + temp_s0, temp_s7 - temp_s0, -1, 0x7E0, 0, temp_s2, temp_s3, temp_s4,
                      temp_s5);

        SetTileVertex(&temp_v0[4], temp_s6 - 0x7D0, temp_s7 - 0x7D0, -1, 0, 0, temp_s2, temp_s3, temp_s4, temp_s5);
        SetTileVertex(&temp_v0[5], temp_s6 - 0x7D0, temp_s7 + 0x7D0, -1, 0, 0, temp_s2, temp_s3, temp_s4, temp_s5);
        SetTileVertex(&temp_v0[6], temp_s6 + 0x7D0, temp_s7 + 0x7D0, -1, 0, 0, temp_s2, temp_s3, temp_s4, temp_s5);
        SetTileVertex(&temp_v0[7], temp_s6 + 0x7D0, temp_s7 - 0x7D0, -1, 0, 0, temp_s2, temp_s3, temp_s4, temp_s5);
    }

    return temp_v0;
}

void DrawTileOverlay(void) {
    Vtx* temp_v0;

    if (gTileOverlayState.unk_08.a <= 0) {
        return;
    }

    temp_v0 = CreateTileVertices();

    if (temp_v0 != 0) {
        gDPPipeSync(gDisplayListHead++);

        gDPSetCycleType(gDisplayListHead++, G_CYC_1CYCLE);
        gSPClearGeometryMode(gDisplayListHead++, G_ZBUFFER | G_LIGHTING);
        gDPSetEnvColor(gDisplayListHead++, 0, 0, 0, gTileOverlayState.unk_06);
        gDPSetRenderMode(gDisplayListHead++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
        gDPSetCombineLERP(gDisplayListHead++, ENVIRONMENT, SHADE, ENV_ALPHA, SHADE, 0, 0, 0, SHADE, ENVIRONMENT, SHADE,
                          ENV_ALPHA, SHADE, 0, 0, 0, SHADE);

        gSPVertex(gDisplayListHead++, (u32)temp_v0 & 0x1FFFFFFF, 8, 0);
        gSP2Triangles(gDisplayListHead++, 0, 4, 1, 0, 1, 4, 5, 0);
        gSP2Triangles(gDisplayListHead++, 1, 5, 2, 0, 2, 5, 6, 0);
        gSP2Triangles(gDisplayListHead++, 2, 6, 7, 0, 2, 7, 3, 0);
        gSP2Triangles(gDisplayListHead++, 3, 4, 0, 0, 3, 7, 4, 0);

        gDPPipeSync(gDisplayListHead++);

        gDPSetCycleType(gDisplayListHead++, G_CYC_2CYCLE);
        gDPSetRenderMode(gDisplayListHead++, G_RM_PASS, G_RM_XLU_SURF2);
        gDPSetCombineLERP(gDisplayListHead++, ENVIRONMENT, SHADE, ENV_ALPHA, SHADE, 1, TEXEL0, ENVIRONMENT, TEXEL0, 0,
                          0, 0, COMBINED, COMBINED, 0, SHADE, 0);
        gDPSetTextureFilter(gDisplayListHead++, G_TF_BILERP);
        gDPSetTexturePersp(gDisplayListHead++, G_TP_PERSP);

        gSPTexture(gDisplayListHead++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);

        gDPLoadTextureBlock(gDisplayListHead++, D_3000000, G_IM_FMT_I, G_IM_SIZ_8b, 64, 32, 0, G_TX_MIRROR | G_TX_WRAP,
                            G_TX_MIRROR | G_TX_WRAP, 6, 5, G_TX_NOLOD, G_TX_NOLOD);
        gSPVertex(gDisplayListHead++, (u32)temp_v0 & 0x1FFFFFFF, 4, 0);
        gSP2Triangles(gDisplayListHead++, 0, 1, 2, 0, 0, 2, 3, 0);
        gSPTexture(gDisplayListHead++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF);
    }
}

void UpdateParticleTrailPositions(void) {
    s32 i;
    s32 j;
    s16 temp_fv0;
    s16 var_v0 = gParticleTrailState[0].unk_08;

    for (i = 0; i < 3; i++) {
        for (j = 4; j >= 0; j--) {
            gParticleTrailState[i].unk_0C[j + 1] = gParticleTrailState[i].unk_0C[j];
        }

        temp_fv0 = (gParticleTrailState[0].unk_06 * gParticleTrailState[0].unk_04) / 100;

        gParticleTrailState[i].unk_0C[0].unk_00 = gParticleTrailState[0].unk_00 + (COSS((var_v0)) * temp_fv0);
        gParticleTrailState[i].unk_0C[0].unk_02 = gParticleTrailState[0].unk_02 + (SINS((var_v0)) * temp_fv0);
        gParticleTrailState[i].unk_0C[0].unk_04 = (gParticleTrailState[0].unk_06 * 0x48) / 100;

        var_v0 -= 0x5555;
    }
}

void InitParticleTrail(s32 arg0) {
    s32 i;

    gParticleTrailState[0].unk_00 = gTileConfigTable[arg0].unk_00;
    gParticleTrailState[0].unk_02 = gTileConfigTable[arg0].unk_02;
    gParticleTrailState[0].unk_04 = gTileConfigTable[arg0].unk_04;
    gParticleTrailState[0].unk_06 = 0x64;
    gParticleTrailState[0].unk_0A = 0;
    gParticleTrailState[0].unk_08 = 0;

    for (i = 0; i < 6; i++) {
        UpdateParticleTrailPositions();
        gParticleTrailState[0].unk_08 -= 0x800;
    }
}

Vtx* CreateColoredQuad(s16 arg0, s16 arg1, s16 arg2, Color_RGBA8 arg3) {
    s16 sp44;
    Vtx* temp_v0;

    temp_v0 = GfxAlloc(sizeof(Vtx) * 8);
    if (temp_v0 != NULL) {
        sp44 = arg2 / 2;

        SetTileVertex(&temp_v0[0], arg0 - sp44, arg1 - sp44, -1, 0, 0, arg3.r, arg3.g, arg3.b, arg3.a);
        SetTileVertex(&temp_v0[1], arg0 - sp44, arg1 + sp44, -1, 0, 0x480, arg3.r, arg3.g, arg3.b, arg3.a);
        SetTileVertex(&temp_v0[2], arg0 + sp44, arg1 + sp44, -1, 0x480, 0x480, arg3.r, arg3.g, arg3.b, arg3.a);
        SetTileVertex(&temp_v0[3], arg0 + sp44, arg1 - sp44, -1, 0x480, 0, arg3.r, arg3.g, arg3.b, arg3.a);
    }

    return temp_v0;
}

void DrawTexturedQuad(s16 arg0, s16 arg1, s16 arg2, u8* arg3, Color_RGBA8 arg4) {
    Vtx* temp_v0 = CreateColoredQuad(arg0, arg1, arg2, arg4);

    if (temp_v0 != NULL) {
        gDPLoadTextureBlock(gDisplayListHead++, arg3, G_IM_FMT_RGBA, G_IM_SIZ_16b, 36, 36, 0,
                            G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK,
                            G_TX_NOLOD, G_TX_NOLOD);
        gSPVertex(gDisplayListHead++, (u32)temp_v0 & 0x1FFFFFFF, 4, 0);
        gSP2Triangles(gDisplayListHead++, 0, 1, 2, 0, 0, 2, 3, 0);
    }
}

void DrawParticleSprites(u8* arg0) {
    Color_RGBA8 sp5C;
    s16 i;
    s16 j;
    s16 temp_s1;
    s16 temp_s3;
    s16 temp_s4;

    for (i = 5; i >= 0; i--) {
        for (j = 0; j < 3; j++) {
            temp_s1 = gParticleTrailState[j].unk_0C[i].unk_04;
            temp_s3 = gParticleTrailState[j].unk_0C[i].unk_00;
            temp_s4 = gParticleTrailState[j].unk_0C[i].unk_02;

            if (temp_s1 != 0) {
                if (i == 0) {
                    GfxColor_SetRGBA(&sp5C, 0xFF, 0xFF, 0xFF, 0xFF);
                } else {
                    GfxColor_SetRGBA(&sp5C, 0xFF, 0xFF, 0x64, 0xA0 - (i * 30));
                }
                DrawTexturedQuad(temp_s3, temp_s4, temp_s1, arg0, sp5C);
            }
        }
    }
}

void DrawParticleTrail(void) {
    if (gCurrentAreaIndex != 8) {
        UpdateParticleTrailPositions();

        gDPPipeSync(gDisplayListHead++);
        gDPSetCycleType(gDisplayListHead++, G_CYC_1CYCLE);
        gSPClearGeometryMode(gDisplayListHead++, G_ZBUFFER | G_LIGHTING);
        gDPSetRenderMode(gDisplayListHead++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
        gDPSetCombineMode(gDisplayListHead++, G_CC_MODULATEIA, G_CC_MODULATEIA);
        gDPSetTextureFilter(gDisplayListHead++, G_TF_BILERP);
        gDPSetTexturePersp(gDisplayListHead++, G_TP_PERSP);
        gSPTexture(gDisplayListHead++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);

        DrawParticleSprites(gParticleTextures[gParticleTrailState->unk_0A / 2]);

        gSPDisplayList(gDisplayListHead++, gPrefDL_End);
        gSPTexture(gDisplayListHead++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF);

        gParticleTrailState->unk_08 -= 0x800;
        gParticleTrailState->unk_0A = (gParticleTrailState->unk_0A + 2) % 8;
    }
}

void DrawScrollingBackground(s16 arg0, s16 arg1, s16 arg2, s16 arg3) {
    s32 i;
    u8* var_s2;

    if (arg3 != 8) {
        if (arg3 == 7) {
            arg3 += gAreaPlayerName.unk_00;
        }
        var_s2 = gBackgroundTexturePtrs[arg3];

        gSPDisplayList(gDisplayListHead++, gPrefDL_Border);
        gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, arg2);

        for (i = 0; i < 16; i++) {
            Gfx_DrawSpriteRGBA16(arg0, arg1 + (i * 4), 0xC4, 4, var_s2 + (i * 0x620), 0xC4, 0);
        }

        if ((gBattleContext.unk_11F2 != 0) && ((arg3 == 0) || (arg3 == 2) || (arg3 == 3))) {
            Gfx_DrawSpriteRGBA16(arg0 - 0x20, arg1 + 0xD, 0x24, 0x24, D_20144E0, 0x24, 0);
        }

        gSPDisplayList(gDisplayListHead++, gPrefDL_End);
    }
}

void AreaSelect_Update(void) {
}

void UpdateBackgroundFade(s16 arg0, s16 arg1, s16 arg2) {
    static s16 D_82203074 = 1;
    static s16 D_82203078 = 1;

    s16 sp1E;

    if (arg0 == 2) {
        sp1E = (gTransitionFrame * 0x2A) + 3;
        DrawScrollingBackground(arg1, (arg2 + (D_82203074 / 4)) - 5, 0xFF - sp1E, gPreviousAreaIndex);
        DrawScrollingBackground(arg1, (arg2 + (D_82203074 / 4)) - 5, sp1E, gCurrentAreaIndex);
    } else if ((arg0 != 8) && (arg0 != 0)) {
        DrawScrollingBackground(arg1, (arg2 + (D_82203074 / 4)) - 5, 0xFF, gCurrentAreaIndex);
    }

    D_82203074 += D_82203078;
    if (D_82203074 == 0) {
        D_82203078 = 1;
    }

    if (D_82203074 == 0x2B) {
        D_82203078 = -1;
    }
}

void DrawAnimatedIcon(s16 arg0, s16 arg1) {
    static u32 D_8220307C[] = {
        0x03044C60, 0x03045020, 0x030453E0, 0x030457A0, 0x03045B60, 0x03045F20, 0x030462E0,
        0x030466A0, 0x03046A60, 0x03046E20, 0x030471E0, 0x030475A0, 0x03047960, 0x03047D20,
        0x030480E0, 0x030484A0, 0x03048860, 0x030493A0, 0x03048FE0, 0x03048C20,
    };
    static s16 D_822030CC = 0;

    if (gAreaAudioState.unk_07 != 0) {
        gDPPipeSync(gDisplayListHead++);
        gDPSetCycleType(gDisplayListHead++, G_CYC_1CYCLE);
        gDPSetRenderMode(gDisplayListHead++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
        gDPSetCombineLERP(gDisplayListHead++, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0,
                          PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0);
        gDPSetEnvColor(gDisplayListHead++, 0, 100, 255, 255);

        if (gBattleContext.unk_11F5 & 4) {
            gDPSetPrimColor(gDisplayListHead++, 0, 0xFF, 255, 255, 255, gOverlayAlpha);
        } else {
            gDPSetPrimColor(gDisplayListHead++, 0, 0xFF, 255, 255, 255, 255);
        }

        gDPLoadTextureBlock_4b(gDisplayListHead++, D_8220307C[D_822030CC], G_IM_FMT_I, 48, 40, 0,
                               G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK,
                               G_TX_NOLOD, G_TX_NOLOD);

        Gfx_DrawTextureRect(arg0 - 0x28, arg1 - 0x28, 0x50, 0x50, 0, 0, 0x200, 0x200, 0);

        D_822030CC = (D_822030CC + 1) % 20;
    }
}

void func_822018D4(s16 arg0, s16 arg1, s16 arg2) {
    if ((gAreaAudioState.unk_07 == 0) || (arg2 <= 0)) {
        return;
    }

    gSPDisplayList(gDisplayListHead++, gPrefDL_Border);
    gDPLoadTextureBlock_4b(gDisplayListHead++, D_3044260, G_IM_FMT_I, 64, 64, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                           G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

    if (1) {}

    Gfx_DrawTextureRect(arg0 - (arg2 / 2), arg1 - (arg2 / 2), arg2, arg2, 0, 0, 0x10000 / arg2, 0x10000 / arg2, 0);
}

void DrawBeveledPanel(s16 arg0, s16 arg1, s16 arg2, s16 arg3, u8 arg4, u8 arg5, u8 arg6, u8 arg7) {
    s16 sp54;
    s16 sp50;
    s16 var_s2;
    s16 var_s3;

    if (arg2 >= 0x10) {
        var_s3 = 8;
    } else {
        var_s3 = arg2 / 2;
    }

    if (arg3 >= 0x10) {
        var_s2 = 8;
    } else {
        var_s2 = arg3 / 2;
    }

    sp50 = arg2 - (var_s3 * 2);
    sp54 = arg3 - (var_s2 * 2);

    gSPDisplayList(gDisplayListHead++, gPrefDL_Border);
    gDPSetEnvColor(gDisplayListHead++, arg4, arg5, arg6, arg7);
    gDPLoadTextureBlock_4b(gDisplayListHead++, D_2028A60, G_IM_FMT_I, 16, 8, 0, G_TX_NOMIRROR | G_TX_WRAP,
                           G_TX_NOMIRROR | G_TX_WRAP, 5, 5, G_TX_NOLOD, G_TX_NOLOD);

    Gfx_DrawTextureRect(arg0, arg1, var_s3, var_s2, 0, 0, 0x2000 / var_s3, 0x2000 / var_s2, 0);

    gDPLoadTextureBlock_4b(gDisplayListHead++, D_2028AA0, G_IM_FMT_I, 16, 8, 0, G_TX_NOMIRROR | G_TX_WRAP,
                           G_TX_NOMIRROR | G_TX_WRAP, 5, 5, G_TX_NOLOD, G_TX_NOLOD);

    Gfx_DrawTextureRect((arg0 + arg2) - var_s3, arg1, var_s3, var_s2, 0, 0, 0x2000 / var_s3, 0x2000 / var_s2, 0);

    gDPLoadTextureBlock_4b(gDisplayListHead++, D_20289E0, G_IM_FMT_I, 16, 8, 0, G_TX_NOMIRROR | G_TX_WRAP,
                           G_TX_NOMIRROR | G_TX_WRAP, 5, 5, G_TX_NOLOD, G_TX_NOLOD);

    Gfx_DrawTextureRect(arg0, (arg1 + arg3) - var_s2, var_s3, var_s2, 0, 0, 0x2000 / var_s3, 0x2000 / var_s2, 0);

    gDPLoadTextureBlock_4b(gDisplayListHead++, D_2028A20, G_IM_FMT_I, 16, 8, 0, G_TX_NOMIRROR | G_TX_WRAP,
                           G_TX_NOMIRROR | G_TX_WRAP, 5, 5, G_TX_NOLOD, G_TX_NOLOD);

    Gfx_DrawTextureRect((arg0 + arg2) - var_s3, (arg1 + arg3) - var_s2, var_s3, var_s2, 0, 0, 0x2000 / var_s3,
                  0x2000 / var_s2, 0);

    gSPDisplayList(gDisplayListHead++, gPrefDL_Fill);

    if ((sp50 > 0) && (sp54 > 0)) {
        Gfx_FillRectRGBA(arg0 + var_s3, arg1, sp50, var_s2, arg4, arg5, arg6, arg7);
        Gfx_FillRectRGBA(arg0, arg1 + var_s3, arg2, sp54, arg4, arg5, arg6, arg7);
        Gfx_FillRectRGBA(arg0 + var_s3, arg1 + var_s3 + sp54, sp50, var_s2, arg4, arg5, arg6, arg7);
    } else if (sp50 > 0) {
        Gfx_FillRectRGBA(arg0 + var_s3, arg1, sp50, arg3, arg4, arg5, arg6, arg7);
    } else if (sp54 > 0) {
        Gfx_FillRectRGBA(arg0, arg1 + var_s2, arg2, sp54, arg4, arg5, arg6, arg7);
    }

    gSPDisplayList(gDisplayListHead++, gPrefDL_End);
}

void DrawAreaLabel(s32 arg0) {
    DrawBeveledPanel(0x38, 0x17C, 0x210, 0x3C, 0x1E, 0x1E, 0x82, 0x96);

    if (arg0 != 0) {
        Text_ResetState();
        Text_SetFont(8, 0);
        Text_SetLineHeight(0x18);
        Text_Print(0x5B, 0x182, GetMessageString(NULL, 0, gAreaMessageBank, gCurrentAreaIndex));
        Text_SetupDL();
    }
}

void AreaSelect_InitInput(void) {
    Cont_StartReadInputs();
    Cont_ReadInputs();
    MenuInput_Init();
}

s32 AreaSelect_HandleInput(void) {
    s8 var_s0 = 8;
    s32 var_t1 = 1;

    gParticleTrailState->unk_00 = gTileConfigTable[gCurrentAreaIndex].unk_00;
    gParticleTrailState->unk_02 = gTileConfigTable[gCurrentAreaIndex].unk_02;
    gParticleTrailState->unk_04 = gTileConfigTable[gCurrentAreaIndex].unk_04;
    gParticleTrailState->unk_06 = 0x64;

    gTileOverlayState.unk_00 = gTileConfigTable[gCurrentAreaIndex].unk_00;
    gTileOverlayState.unk_02 = gTileConfigTable[gCurrentAreaIndex].unk_02;
    gTileOverlayState.unk_08 = gTileConfigTable[gCurrentAreaIndex].unk_0A;
    gTileOverlayState.unk_06 = 0;
    gTileOverlayState.unk_04 = 0x12C;

    if (gPlayer1Controller->buttonPressed & 0x8000) {
        if (gCurrentAreaIndex == 3) {
            Audio_PlaySequence(0x96, 8);
        }
        PlaySoundEffect(0x33);
        PlaySoundEffect(0x16);
        var_t1 = 3;
    } else if (gPlayer1Controller->buttonPressed & 0x4000) {
        Music_SetTrack(0x28);
        PlaySoundEffect(3);
        var_t1 = 4;
    } else if (gPlayer1Controller->buttonPressed & 0x800) {
        var_s0 = gTileConfigTable[gCurrentAreaIndex].unk_06;
    } else if (gPlayer1Controller->buttonPressed & 0x400) {
        var_s0 = gTileConfigTable[gCurrentAreaIndex].unk_07;
    } else if (gPlayer1Controller->buttonPressed & 0x200) {
        var_s0 = gTileConfigTable[gCurrentAreaIndex].unk_08;
    } else if (gPlayer1Controller->buttonPressed & 0x100) {
        var_s0 = gTileConfigTable[gCurrentAreaIndex].unk_09;
    }

    if (var_s0 != 8) {
        PlaySoundEffect(0x32);
        var_t1 = 2;
        gPreviousAreaIndex = gCurrentAreaIndex;
        gCurrentAreaIndex = var_s0;
        gTransitionFrame = 0;
    }

    return var_t1;
}

s16 AreaSelect_AnimateTransition(void) {
    s32 var_v1;
    s32 v8_0;
    s32 v8_2;
    s32 v8_4;
    s32 vA_0;
    s32 vA_2;
    s32 vA_4;

    vA_0 = gTileConfigTable[gPreviousAreaIndex].unk_00;
    vA_2 = gTileConfigTable[gPreviousAreaIndex].unk_02;
    vA_4 = gTileConfigTable[gPreviousAreaIndex].unk_04;
    v8_0 = gTileConfigTable[gCurrentAreaIndex].unk_00;
    v8_2 = gTileConfigTable[gCurrentAreaIndex].unk_02;
    v8_4 = gTileConfigTable[gCurrentAreaIndex].unk_04;

    gTransitionFrame++;

    gParticleTrailState->unk_00 = (((v8_0 - vA_0) * gTransitionFrame) / 6) + vA_0;
    gParticleTrailState->unk_02 = (((v8_2 - vA_2) * gTransitionFrame) / 6) + vA_2;
    gParticleTrailState->unk_04 = (((v8_4 - vA_4) * gTransitionFrame) / 6) + vA_4;
    gParticleTrailState->unk_06 = 0x64;
    gParticleTrailState->unk_08 += 0x800;

    if (gTransitionFrame == 6) {
        var_v1 = 1;
    } else {
        var_v1 = 2;
    }

    return var_v1;
}

s32 AreaSelect_AnimateParticleOut(void) {
    s32 var_v1 = 3;

    if (gParticleTrailState->unk_06 >= 0xB) {
        gParticleTrailState->unk_06 -= 5;
    } else {
        gParticleTrailState->unk_06 = 0;
        if (gCurrentAreaIndex == 3) {
            Music_StopTrack(0x20);
            var_v1 = 6;
        } else {
            if (gCurrentAreaIndex != 7) {
                Music_StopTrack(0x28);
            }
            var_v1 = 5;
        }
    }
    return var_v1;
}

s32 AreaSelect_FadeInOverlay(void) {
    s16 var_a1 = 5;

    if (gTileOverlayState.unk_08.a < 0xFA) {
        gTileOverlayState.unk_08.a += 0x19;
    } else if (gTileOverlayState.unk_06 < 0xFF) {
        gTileOverlayState.unk_08.a = 0xFF;
        gTileOverlayState.unk_06 += 0x19;
        if (gTileOverlayState.unk_06 >= 0xFF) {
            gTileOverlayState.unk_06 = 0xFF;
            Stage_SetFillColor(1);
            Stage_FadeOut(1);
            var_a1 = 5;
        }
    } else {
        var_a1 = GetControllerInputMask(7);
    }
    return var_a1;
}

s32 AreaSelect_FadeOutSequence(void) {
    s16 var_a1 = 6;

    if (gFadeStepCounter < 0x200) {
        gFadeStepCounter += 0x40;
    } else if (gFadeStepCounter == 0x200) {
        gFadeStepCounter += 0x40;
        Stage_SetFillColor(0xFFFF);
        Stage_FadeOut(2);
        var_a1 = 6;
    } else if (gFadeStepCounter < 0x280) {
        gFadeStepCounter += 0x40;
        if (gFadeStepCounter == 0x280) {
            var_a1 = 7;
        }
    }
    return var_a1;
}

s32 AreaSelect_HandleFadeEnd(void) {
    s32 temp_v0 = Stage_GetFadeState();
    s16 var_v1 = 4;

    switch (temp_v0) {
        case 0:
            Stage_SetFillColor(0xFFFF);
            Stage_FadeOut(0x10);
            var_v1 = 4;
            break;

        case 1:
            gCurrentAreaIndex = 8;
            var_v1 = 7;
            break;
    }

    return var_v1;
}

void AreaSelect_SetupProjection(void) {
    guOrtho(&gAreaProjMatrix, 0.0f, 640.0f, 480.0f, 0.0f, -2.0f, 2.0f, 1.0f);
    SetViewport(&gAreaViewport, 0x280, 0x1E0);

    gSPClearGeometryMode(gDisplayListHead++, G_ZBUFFER | G_LIGHTING);
    gSPPerspNormalize(gDisplayListHead++, 0xFFFF);
    gSPViewport(gDisplayListHead++, (u32)&gAreaViewport & 0x1FFFFFFF);
    gSPMatrix(gDisplayListHead++, (u32)&gAreaProjMatrix & 0x1FFFFFFF, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
    gSPMatrix(gDisplayListHead++, (u32)&gCamProjectionMatrix & 0x1FFFFFFF, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
}

void AreaSelect_Render(s16 arg0) {
    Stage_BeginDisplayList();
    AreaSelect_SetupProjection();

    if (gOverlayAlpha == 0) {
        Gfx_DrawTextureAtlas(gBgTexturePrimary);
    } else if (gOverlayAlpha == 0xFF) {
        Gfx_DrawTextureAtlas(gBgTextureSecondary);
    } else {
        DrawFullScreenTextureBlend(gBgTexturePrimary, gBgTextureSecondary, gOverlayAlpha);
    }

    DrawAnimatedIcon(0x12C, 0x41);
    DrawParticleTrail();
    UpdateBackgroundFade(arg0, 0x194, 0x28);
    func_822018D4(0x12C, 0x41, gFadeStepCounter);
    DrawTileOverlay();

    if ((arg0 == 1) || (arg0 == 2)) {
        DrawAreaLabel(arg0 == 1);
    }

    Stage_Advance();
}

s32 AreaSelect_TransitionToGame(void) {
    s16 var_v1 = 8;

    gCurrentAreaIndex = 8;
    if (Stage_GetFadeState() == 0) {
        gOverlayAlpha += 4;
        if (gOverlayAlpha == 0x100) {
            gBattleContext.unk_11F5 &= 0xFFFB;
            gOverlayAlpha = 0xFF;
            gPreviousAreaIndex = 8;
            gCurrentAreaIndex = 0;
            var_v1 = 2;
        }
    }
    return var_v1;
}

void AreaSelect_StartAnimation(void) {
    InitParticleTrail(gCurrentAreaIndex);
    Music_ChangeTrack(0x50);
    Stage_FadeIn(0xA);

    while (Stage_GetFadeState() != 0) {
        AreaSelect_InitInput();
        AreaSelect_Render(0);
    }
}

void AreaSelect_MainLoop(void) {
    s16 i;

    i = 2;
    if (gBattleContext.unk_11F5 & 4) {
        Audio_PlaySequence(0x96, 7);
        i = 8;
    }

    if (gAreaAudioState.unk_07 == 0) {
        gTileConfigTable[0].unk_06 = 8;
        gTileConfigTable[2].unk_09 = 8;
        gTileConfigTable[7].unk_06 = 8;
    }

    gPreviousAreaIndex = 8;
    gCurrentAreaIndex = 0;

    while (i != 7) {
        AreaSelect_InitInput();

        switch (i) {
            case 1:
                i = AreaSelect_HandleInput();
                break;
            case 2:
                i = AreaSelect_AnimateTransition();
                break;

            case 3:
                i = AreaSelect_AnimateParticleOut();
                break;

            case 4:
                i = AreaSelect_HandleFadeEnd();
                break;

            case 5:
                i = AreaSelect_FadeInOverlay();
                break;

            case 6:
                i = AreaSelect_FadeOutSequence();
                break;

            case 8:
                i = AreaSelect_TransitionToGame();
                break;
        }

        AreaSelect_Render(i);
    }
}

void AreaSelect_LoadAssets(void) {
    gAreaAssetArchive = ASSET_LOAD2(backgrounds, 1, 1);

    if (gAreaPlayerName.unk_00 == 2) {
        if (gBattleContext.unk_11F2 == 0) {
            gBgTexturePrimary = BinArchive_GetFile(gAreaAssetArchive, 1);
            gBgTextureSecondary = BinArchive_GetFile(gAreaAssetArchive, 2);
        } else {
            gBgTextureSecondary = gBgTexturePrimary = BinArchive_GetFile(gAreaAssetArchive, 2);
        }
    } else if (gAreaPlayerName.unk_00 == 1) {
        gBgTextureSecondary = gBgTexturePrimary = BinArchive_GetFile(gAreaAssetArchive, 0x13);
    } else {
        gBgTextureSecondary = gBgTexturePrimary = BinArchive_GetFile(gAreaAssetArchive, 0x12);
    }
}

s32 AreaSelect_Main(UNUSED s32 arg0, UNUSED s32 arg1) {
    Stage* sp24;

    main_pool_push_state('LAND');

    Gfx_InitBuffers(0x10000, 0);
    sp24 = Stage_Create(1, 0, 2, 0, 2, 1);
    Text_Init(0x1C, 0);

    ASSET_LOAD(D_1000000, common_menu1_ui, 0);
    ASSET_LOAD(D_3000000, area_select_ui, 0);
    ASSET_LOAD(D_2000000, common_menu2_ui, 0);

    MessageBank_Init();
    gAreaMessageBank = GetMessageBank(0x17);
    GbsEnsureBankLoaded(2);
    GbsGetPlayerName(&gAreaPlayerName);
    GBAudio_ResetState(&gAreaAudioState, gBattleContext.unk_11F2);
    AreaSelect_LoadAssets();
    gCurrentAreaIndex = 8;

    if ((gAreaAudioState.unk_07 != 0) && !(gBattleContext.unk_11F5 & 4) && !(gAreaAudioState.unk_00 & 0x100)) {
        gOverlayAlpha = 0xFF;
    }

    Stage_Set(sp24);
    AreaSelect_StartAnimation();
    AreaSelect_MainLoop();
    Stage_Destroy();
    Gfx_FreeBuffers();

    main_pool_pop_state('LAND');

    return gStateTransitionTable[gCurrentAreaIndex];
}
