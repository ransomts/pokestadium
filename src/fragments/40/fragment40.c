#include "fragment40.h"
#include "src/12D80.h"
#include "src/1C720.h"
#include "src/1CF30.h"
#include "src/20330.h"
#include "src/20470.h"
#include "src/3FB0.h"
#include "src/6A40.h"
#include "src/6BC0.h"
#include "src/F420.h"
#include "src/controller.h"
#include "src/memmap.h"
#include "src/memory.h"
#include "src/stage_loader.h"

s32 DrawNodeEffect(s32, GraphNode*);
s32 DrawNodeGeometry(s32, GraphNode*);

typedef struct unk_D_83101E6C {
    /* 0x00 */ s16 unk_00;
    /* 0x04 */ f32 unk_04;
    /* 0x08 */ s16 unk_08;
    /* 0x0A */ s16 unk_0A;
    /* 0x0C */ s16 unk_0C;
    /* 0x0E */ s16 unk_0E;
    /* 0x10 */ s16 unk_10;
    /* 0x12 */ s16 unk_12;
} unk_D_83101E6C; // size = 0x14

typedef struct unk_D_83102218 {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s16 unk_04;
    /* 0x08 */ f32 unk_08;
} unk_D_83102218; // size = 0xC

typedef struct unk_D_83102224 {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s16 unk_04;
} unk_D_83102224; // size = 0x8

static BinArchive* D_83101EE0;
static u8* D_83101EE4;
static s16 gClearScreenState;
static s16 gClearScreenTimer;
static s16 gShowCursorFlag;
static s16 gCursorX;
static s16 gCursorY;
static GraphNode* gClearScreenRoot;
static GraphNode* gClearScreenNode1;
static GraphNode* gClearScreenNode2;
static unk_D_83101F00 D_83101F00[2];
static unk_D_83101F00* gNode1State;
static unk_D_83101F00* gNode2State;
static unk_D_83102218 gBorderAnimState;
static unk_D_83102224 gFadeAnimState;

static Vtx gClearScreenVerts1[] = {
    VTX(-100, 14, 0, 0, 0, 0x78, 0x32, 0xFF, 0xFF),      VTX(-100, 0, 0, 0, 448, 0xBB, 0x28, 0x8E, 0xFF),
    VTX(100, 0, 0, 6400, 448, 0xBB, 0x28, 0x8E, 0xFF),   VTX(100, 14, 0, 6400, 0, 0x78, 0x32, 0xFF, 0xFF),
    VTX(-100, 0, 0, 0, 0, 0xBB, 0x28, 0x8E, 0xFF),       VTX(-100, -14, 0, 0, 448, 0xFF, 0x1E, 0x1E, 0xFF),
    VTX(100, -14, 0, 6400, 448, 0xFF, 0x1E, 0x1E, 0xFF), VTX(100, 0, 0, 6400, 0, 0xBB, 0x28, 0x8E, 0xFF),
};

static Gfx gClearScreenDL1[] = {
    gsSPSetGeometryMode(G_CULL_BACK),
    gsDPSetCombineLERP(SHADE, 0, TEXEL0, 0, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsSPVertex(gClearScreenVerts1, 8, 0),
    gsDPLoadTextureBlock(0x0F000000, G_IM_FMT_IA, G_IM_SIZ_8b, 200, 14, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                         G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsDPLoadTextureBlock(0x0F000AF0, G_IM_FMT_IA, G_IM_SIZ_8b, 200, 14, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                         G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP2Triangles(4, 5, 6, 0, 4, 6, 7, 0),
    gsSPEndDisplayList(),
};

static u32 gClearScreenGeo1[] = {
    0x17000000, 0x00000000, 0x00000000,    0x00000000, gClearScreenVerts1, 0x05000000, 0x22050000,
    0x00000000, 0x08000000, DrawNodeGeometry, 0x00000000, 0x06000000, 0x01000000, 0x00000000,
};

static Vtx gClearScreenVerts2[] = {
    VTX(-64, 16, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(-64, -16, 0, 0, 1024, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(64, -16, 0, 4096, 1024, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(64, 16, 0, 4096, 0, 0xFF, 0xFF, 0xFF, 0xFF),
};

static Gfx gClearScreenDL2[] = {
    gsSPSetGeometryMode(G_CULL_BACK),
    gsDPSetCombineMode(G_CC_BLENDPEDECALA, G_CC_PASS2),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsSPVertex(gClearScreenVerts2, 4, 0),
    gsDPLoadTextureBlock(0x0F000000, G_IM_FMT_IA, G_IM_SIZ_8b, 128, 32, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                         G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSPEndDisplayList(),
};

static u32 gClearScreenGeo2[] = {
    0x17000000, 0x00000000, 0x00000000,    0x00000000, gClearScreenVerts2, 0x05000000, 0x22050000,
    0x00000000, 0x08000000, DrawNodeEffect, 0x00000000, 0x06000000, 0x01000000,
};

static u32 gClearScreenRootGeo[] = {
    0x0C000000,  0x05000000, 0x0B00002D, 0x00000000, 0x028001E0, 0x00000000, 0xFDBD0000,
    0x00000243,  0x05000000, 0x0D000000, 0x05000000, 0x0F000002, 0x05000000, 0x0A000000,
    &gGraphRoot0, 0x06000000, 0x06000000, 0x06000000, 0x06000000, 0x01000000,
};

static unk_D_83101E6C gNodeColorScaleTable[] = {
    { 0xC, 0.0f, 0, 0, 0, 0, 0, 0 },
    { 4, 2.4f, 0xFF, 0, 0, 0, 0, 0 },
    { 4, 2.0f, 0xFF, 0xFF, 0xFF, 0xC8, 0x64, 0 },
    { -1, 2.0f, 0xC8, 0xC8, 0x1E, 0, 0, 0 },
};

void UpdateNodePosition(Fragment2_1GraphNode* arg0) {
    unk_D_83101F00* ptr = (unk_D_83101F00*)arg0;
    f32 temp_fv0;
    s32 sp1C;
    f32 var_fv0;

    switch (ptr->unk_16A) {
        case 1:
            if (ptr->unk_180 >= 0.0f) {
                ptr->unk_184 -= 0.065f;
            } else {
                ptr->unk_184 += 0.065f;
            }

            sp1C = 0;
            temp_fv0 = ptr->unk_180;
            ptr->unk_180 += ptr->unk_184;

            if (((ptr->unk_180 * temp_fv0) < 0.0f) && (fabsf(ptr->unk_184) < 0.13f)) {
                sp1C = 1;
            }

            if (sp1C == 0) {
                ptr->unk_184 *= 0.75f;
                var_fv0 = (ptr->unk_180 * -520.0f) + 320.0f;
            } else {
                ptr->unk_16A = 2;
                ptr->unk_16C = 0;
                var_fv0 = 320.0f;
            }

            ptr->unk_000.unk_024.x = var_fv0 - 320.0f;
            gCursorX = (s16)var_fv0 + 0xC8;
            gCursorY = 0xAC;
            break;

        case 0:
        case 2:
        case 3:
            break;
    }
}

s32 DrawNodeGeometry(s32 arg0, UNUSED GraphNode* arg1) {
    switch (arg0) {
        case 0:
            break;

        case 2:
            UpdateNodePosition(gDefaultGraphRoot);
            break;

        case 5:
            gDPPipeSync(gDisplayListHead++);

            gSPSegment(gDisplayListHead++, 0x0F, Memmap_GetSegmentVaddr(D_3000000));
            gSPDisplayList(gDisplayListHead++, gClearScreenDL1);

            Gfx_ResetRenderState();
            break;
    }

    return 0;
}

void UpdateNodeColorAndScale(unk_D_83101F00* arg0) {
    unk_D_83101E6C* ptr1;
    unk_D_83101E6C* ptr2;
    f32 var_fv1;

    switch (arg0->unk_16A) {
        case 1:
            arg0->unk_16C--;
            ptr1 = &gNodeColorScaleTable[arg0->unk_170];
            ptr2 = &gNodeColorScaleTable[arg0->unk_170 + 1];

            arg0->unk_172 = ptr2->unk_08 + (((ptr1->unk_08 - ptr2->unk_08) * arg0->unk_16C) / arg0->unk_16E);
            arg0->unk_174 = ptr2->unk_0A + (((ptr1->unk_0A - ptr2->unk_0A) * arg0->unk_16C) / arg0->unk_16E);
            arg0->unk_176 = ptr2->unk_0C + (((ptr1->unk_0C - ptr2->unk_0C) * arg0->unk_16C) / arg0->unk_16E);

            arg0->unk_178 = ptr2->unk_0E + (((ptr1->unk_0E - ptr2->unk_0E) * arg0->unk_16C) / arg0->unk_16E);
            arg0->unk_17A = ptr2->unk_10 + (((ptr1->unk_10 - ptr2->unk_10) * arg0->unk_16C) / arg0->unk_16E);
            arg0->unk_17C = ptr2->unk_12 + (((ptr1->unk_12 - ptr2->unk_12) * arg0->unk_16C) / arg0->unk_16E);

            var_fv1 = ptr2->unk_04 + (((ptr1->unk_04 - ptr2->unk_04) * arg0->unk_16C) / arg0->unk_16E);

            if (arg0->unk_16C <= 0) {
                arg0->unk_170++;
                ptr1 = &gNodeColorScaleTable[arg0->unk_170];

                arg0->unk_16C = arg0->unk_16E = ptr1->unk_00;
                arg0->unk_172 = ptr1->unk_08;
                arg0->unk_174 = ptr1->unk_0A;
                arg0->unk_176 = ptr1->unk_0C;
                arg0->unk_178 = ptr1->unk_0E;
                arg0->unk_17A = ptr1->unk_10;
                arg0->unk_17C = ptr1->unk_12;

                var_fv1 = ptr1->unk_04;

                if (arg0->unk_16C == -1) {
                    arg0->unk_16E = 0;
                    arg0->unk_16A = 2;
                    arg0->unk_16C = arg0->unk_16E;
                }
            }

            Vec3f_Set(&arg0->unk_000.unk_030, var_fv1, var_fv1, var_fv1);
            break;

        case 0:
        case 2:
        case 3:
            break;
    }
}

s32 DrawNodeEffect(s32 arg0, GraphNode* arg1) {
    unk_D_83101F00* ptr = (unk_D_83101F00*)gDefaultGraphRoot;

    switch (arg0) {
        case 0:
            break;

        case 2:
            UpdateNodeColorAndScale(ptr);
            break;

        case 5:
            gDPPipeSync(gDisplayListHead++);

            gSPSegment(gDisplayListHead++, 0x0F, Memmap_GetSegmentVaddr(D_30015E0));
            gDPSetPrimColor(gDisplayListHead++, 0, 0, ptr->unk_172, ptr->unk_174, ptr->unk_176, 0xFF);
            gDPSetEnvColor(gDisplayListHead++, ptr->unk_178, ptr->unk_17A, ptr->unk_17C, 0xFF);
            gSPDisplayList(gDisplayListHead++, gClearScreenDL2);

            Gfx_ResetRenderState();
            break;
    }
    return 0;
}

void InitBorderAnimation(void) {
    gBorderAnimState.unk_00 = 0;
    gBorderAnimState.unk_02 = 0;
    gBorderAnimState.unk_08 = 7.0f;
}

void UpdateBorderAnimation(void) {
    s32 tmp;

    switch (gBorderAnimState.unk_00) {
        case 1:
            gBorderAnimState.unk_02--;
            gBorderAnimState.unk_08 = (gBorderAnimState.unk_02 * 7.0f) / gBorderAnimState.unk_04;

            tmp = gBorderAnimState.unk_02 <= 0;
            if (tmp) {
                gBorderAnimState.unk_00 = 2;
                gBorderAnimState.unk_02 = gBorderAnimState.unk_04 = 0;
                gBorderAnimState.unk_08 = 0.0f;
            }
            break;

        case 0:
        case 2:
            break;
    }
}

void DrawBorderEffect(void) {
    s16 var_t0;
    s16 var_t1;
    s16 var_t3;
    s16 var_t4;
    s16 sp9E;
    s16 sp9C;
    s16 sp40;
    s16 sp38;
    s32 temp_ft2;

    Gfx_SetScissorRect(&gDisplayListHead, 0, 0, 0x280, 0x1E0);
    if (gBorderAnimState.unk_00 == 0) {
        return;
    }

    if ((gBorderAnimState.unk_08 <= 0.0f) || (gBorderAnimState.unk_00 == 2)) {
        gSPDisplayList(gDisplayListHead++, gDL_FillCycle);
        gDPSetFillColor(gDisplayListHead++, 0x00010001);
        gDPFillRectangle(gDisplayListHead++, 0, 0, 639, 479);
        return;
    }

    temp_ft2 = ROUND_MAX(1024.0f / gBorderAnimState.unk_08);
    sp9E = ROUND_MAX(128.0f * gBorderAnimState.unk_08);
    sp9C = ROUND_MAX(128.0f * gBorderAnimState.unk_08);

    sp38 = (0x280 - sp9E) / 2;
    sp40 = (0x1E0 - sp9C) / 2;

    gSPDisplayList(gDisplayListHead++, gPrefDL_Border);
    gDPSetCombineLERP(gDisplayListHead++, 1, TEXEL0, ENVIRONMENT, 0, 1, TEXEL0, ENVIRONMENT, 0, 1, TEXEL0, ENVIRONMENT,
                      0, 1, TEXEL0, ENVIRONMENT, 0);
    gDPSetEnvColor(gDisplayListHead++, 0, 0, 0, 255);
    gDPLoadTextureBlock_4b(gDisplayListHead++, D_3002C00, G_IM_FMT_I, 64, 64, 0, G_TX_MIRROR | G_TX_WRAP,
                           G_TX_MIRROR | G_TX_WRAP, 6, 6, G_TX_NOLOD, G_TX_NOLOD);

    Gfx_DrawTextureRect(sp38, sp40, sp9E, sp9C, 0, 0, temp_ft2, temp_ft2, 0);

    var_t3 = sp38;
    var_t0 = sp40;

    gSPDisplayList(gDisplayListHead++, gDL_FillCycle);
    gDPSetFillColor(gDisplayListHead++, 0x00010001);

    var_t4 = sp38 + sp9E;
    var_t1 = sp40 + sp9C;

    if (sp38 < 0) {
        var_t3 = 0;
    }

    if (sp40 < 0) {
        var_t0 = 0;
    }

    if (var_t4 >= 0x281) {
        var_t4 = 0x280;
    }

    if (var_t1 >= 0x1E1) {
        var_t1 = 0x1E0;
    }

    if (var_t0 > 0) {
        gDPFillRectangle(gDisplayListHead++, 0, 0, 639, var_t0 - 1);
    }

    if (var_t1 < 0x1E0) {
        gDPFillRectangle(gDisplayListHead++, 0, var_t1, 639, 479);
    }

    if ((var_t3 > 0) && (var_t0 >= 0) && (var_t1 < 0x1E1)) {
        gDPFillRectangle(gDisplayListHead++, 0, var_t0, var_t3 - 1, var_t1 - 1);
    }

    if ((var_t4 < 0x281) && (var_t0 >= 0) && (var_t1 < 0x1E1)) {
        gDPFillRectangle(gDisplayListHead++, var_t4, var_t0, 639, var_t1 - 1);
    }
}

void StartBorderAnimation(s16 arg0) {
    if (arg0 > 0) {
        gBorderAnimState.unk_00 = 1;
        gBorderAnimState.unk_02 = gBorderAnimState.unk_04 = arg0;
        gBorderAnimState.unk_08 = 7.0f;
    }
}

void InitFadeAnimation(void) {
    gFadeAnimState.unk_00 = 0;
    gFadeAnimState.unk_02 = 0;
    gFadeAnimState.unk_04 = 0xC0;
}

void UpdateFadeAnimation(void) {
    switch (gFadeAnimState.unk_00) {
        case 1:
            gFadeAnimState.unk_02--;
            gFadeAnimState.unk_04 = ((gFadeAnimState.unk_02 * -0x3F) / 10) + 0xFF;
            if (gFadeAnimState.unk_02 <= 0) {
                gFadeAnimState.unk_00 = 2;
                gFadeAnimState.unk_02 = 0;
                gFadeAnimState.unk_04 = 0xFF;
            }
            break;

        case 2:
            break;
    }
}

void DrawTiledTexture(u8* arg0, s16 arg1) {
    s32 i;
    s32 j;

    gDPPipeSync(gDisplayListHead++);

    gDPSetCycleType(gDisplayListHead++, G_CYC_1CYCLE);
    gDPSetRenderMode(gDisplayListHead++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
    gDPSetTexturePersp(gDisplayListHead++, G_TP_NONE);
    gDPSetScissor(gDisplayListHead++, G_SC_NON_INTERLACE, 0, 0, 640, 480);
    gDPSetCombineLERP(gDisplayListHead++, 0, 0, 0, TEXEL0, TEXEL0, 0, ENVIRONMENT, 0, 0, 0, 0, TEXEL0, TEXEL0, 0,
                      ENVIRONMENT, 0);
    gDPSetEnvColor(gDisplayListHead++, 0, 0, 0, arg1);

    gDPPipeSync(gDisplayListHead++);

    for (i = 0; i < 0x1E0; i += 0x20) {
        for (j = 0; j < 0x280; j += 0x20) {
            gDPLoadTextureBlock(gDisplayListHead++, arg0, G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 16, 0,
                                G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK,
                                G_TX_NOLOD, G_TX_NOLOD);
            gSPTextureRectangle(gDisplayListHead++, j << 2, i << 2, (j + 0x20) << 2, (i + 0x20) << 2, G_TX_RENDERTILE,
                                0, 0, 0x0200, 0x0200);

            arg0 += 0x200;
        }
    }
}

void DrawScreenOverlay(void) {
    if (gFadeAnimState.unk_04 < 0xFF) {
        DrawTiledTexture(D_83101EE4, gFadeAnimState.unk_04);
    } else {
        Gfx_DrawTextureAtlas(D_83101EE4);
    }
}

void StartFadeAnimation(s16 arg0) {
    gFadeAnimState.unk_00 = arg0;
    if (gFadeAnimState.unk_00 == 1) {
        gFadeAnimState.unk_02 = 0xA;
        gFadeAnimState.unk_04 = 0xC0;
    }
}

void InitInput(void) {
    Cont_StartReadInputs();
    Cont_ReadInputs();
    MenuInput_Init();
}

void SetNodeState(unk_D_83101F00* arg0, s16 arg1) {
    unk_D_83101E6C* ptr;

    arg0->unk_16A = arg1;

    if (arg0->unk_16A == 1) {
        switch (arg0->unk_168) {
            case 1:
                arg0->unk_184 = 0.0f;
                arg0->unk_180 = 1.0f;
                break;

            case 2:
                arg0->unk_170 = 0;
                ptr = &gNodeColorScaleTable[arg0->unk_170];

                arg0->unk_16C = arg0->unk_16E = ptr->unk_00;
                arg0->unk_172 = ptr->unk_08;
                arg0->unk_174 = ptr->unk_0A;
                arg0->unk_176 = ptr->unk_0C;
                arg0->unk_178 = ptr->unk_0E;
                arg0->unk_17A = ptr->unk_10;
                arg0->unk_17C = ptr->unk_12;

                Vec3f_Set(&arg0->unk_000.unk_030, ptr->unk_04, ptr->unk_04, ptr->unk_04);
                break;
        }
    }
}

void DrawScissoredTexture(s16 arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5, s16 arg6, s16 arg7) {
    gSPScisTextureRectangle(gDisplayListHead++, arg0 << 2, arg1 << 2, ((arg0 + arg2) - 1) << 2,
                            ((arg1 + arg3) - 1) << 2, 0, arg4, arg5, arg6, arg7);
}

void DrawCursorEffect(void) {
    f32 v = 1.8f;
    s16 temp_fa0;
    s16 temp_ft2;

    gSPDisplayList(gDisplayListHead++, gPrefDL_Border);

    temp_ft2 = ROUND_MAX(28 * v);
    temp_fa0 = ROUND_MAX(1024.0f / v);

    gDPLoadTextureBlock(gDisplayListHead++, D_30025E0, G_IM_FMT_RGBA, G_IM_SIZ_16b, 28, 28, 0,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                        G_TX_NOLOD);

    DrawScissoredTexture(gCursorX, gCursorY, temp_ft2, temp_ft2, 0, 0, temp_fa0, temp_fa0);

    gSPDisplayList(gDisplayListHead++, gPrefDL_End);
}

void InitClearScreenState(void) {
    gClearScreenState = 0;
    if (gBattleContext.unk_11F2 != 0) {
        gShowCursorFlag = 1;
    } else {
        gShowCursorFlag = 0;
    }
    gCursorY = -0x64;
    gCursorX = gCursorY;
    InitBorderAnimation();
    InitFadeAnimation();
}

void RenderClearScreen(void) {
    Stage_BeginDisplayList();
    DrawScreenOverlay();
    Graph_SetTextureState(gClearScreenRoot);
    if (gShowCursorFlag != 0) {
        DrawCursorEffect();
    }
    DrawBorderEffect();
    Stage_Advance();
}

s32 UpdateClearScreenLogic(void) {
    s32 sp1C = 1;

    switch (gClearScreenState) {
        case 0:
            if (Stage_GetFadeState() == 0) {
                gClearScreenState = 1;
                gClearScreenTimer = 0;
                SetNodeState(gNode1State, 1);
            }
            break;

        case 1:
            if (gNode1State->unk_16A == 2) {
                switch (gNode2State->unk_16A) {
                    case 0:
                        SetNodeState(gNode2State, 1);
                        break;

                    case 2:
                        gClearScreenTimer += 1;
                        if (gClearScreenTimer == 1) {
                            StartFadeAnimation(1);
                        }

                        if (gClearScreenTimer >= 0x1E) {
                            gClearScreenState = 2;
                            gClearScreenTimer = 0;
                            StartBorderAnimation(0xF);
                            Stage_SetFillColor(1);
                        }
                        break;
                }
            }
            break;

        case 2:
            if (gBorderAnimState.unk_00 == 2) {
                sp1C = 0;
            }
            break;
    }

    return sp1C;
}

void RunClearScreenSequence(void) {
    InitClearScreenState();
    Stage_FadeIn(0xF);

    do {
        InitInput();
        UpdateBorderAnimation();
        UpdateFadeAnimation();
        RenderClearScreen();
    } while (UpdateClearScreenLogic() != 0);
}

void InitClearScreenGraph(void) {
    unk_D_83101F00* ptr;
    MemoryBlock* temp_v0 = state_pool_try_init(main_pool_get_available(), 0);
    s32 i;

    gClearScreenRoot = process_geo_layout(temp_v0, gClearScreenRootGeo);
    gClearScreenNode1 = process_geo_layout(temp_v0, gClearScreenGeo1);
    gClearScreenNode2 = process_geo_layout(temp_v0, gClearScreenGeo2);

    mem_pool_resize_block(temp_v0);
    Graph_InitRoots();

    for (i = 0; i < 2; i++) {
        ptr = &D_83101F00[i];

        Graph_AddToRootList0(&ptr->unk_000);

        ptr->unk_172 = ptr->unk_174 = ptr->unk_176 = 0;
        ptr->unk_178 = ptr->unk_17A = ptr->unk_17C = 0;
        ptr->unk_168 = 0;
        ptr->unk_16A = 0;
        ptr->unk_16C = 0;
        ptr->unk_16E = 0;
        ptr->unk_170 = 0;
        ptr->unk_180 = 0.0f;
        ptr->unk_184 = 0.0f;

        switch (i) {
            case 0:
                Vec3f_Set(&ptr->unk_000.unk_024, -520.0f, 44.0f, -579.0f);
                Vec3f_Set(&ptr->unk_000.unk_030, 2.0f, 2.0f, 2.0f);
                GraphNode_InitChild(&ptr->unk_000, 0, 0, gClearScreenNode1);
                ptr->unk_168 = 1;
                gNode1State = ptr;
                break;

            case 1:
                Vec3f_Set(&ptr->unk_000.unk_024, 0.0, -24.0f, -579.0f);
                Vec3f_Set(&ptr->unk_000.unk_030, 0.0f, 0.0f, 0.0f);
                GraphNode_InitChild(&ptr->unk_000, 0, 0, gClearScreenNode2);
                ptr->unk_168 = 2;
                gNode2State = ptr;
                break;
        }
    }
}

s32 ClearScreen_Main(UNUSED s32 arg0, UNUSED s32 arg1) {
    Stage* sp24;

    main_pool_push_state('CLRG');

    Gfx_InitBuffers(0x10000, 0);
    sp24 = Stage_Create(1, 0, 2, 0, 2, 1);
    Text_Init(0x10, 0);

    ASSET_LOAD(D_1000000, common_menu1_ui, 0);
    ASSET_LOAD(D_3000000, gym_leader_castle_clear_gfx, 0);
    D_83101EE0 = ASSET_LOAD2(backgrounds, 1, 1);
    D_83101EE4 = BinArchive_GetFile(D_83101EE0, 0xE);

    InitClearScreenGraph();
    Stage_Set(sp24);
    RunClearScreenSequence();
    Stage_AdvanceN(2);
    Stage_Destroy();
    FontManager_Free();
    Gfx_FreeBuffers();

    main_pool_pop_state('CLRG');

    return 0;
}
