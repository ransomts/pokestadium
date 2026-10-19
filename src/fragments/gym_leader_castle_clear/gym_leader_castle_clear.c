#include "gym_leader_castle_clear.h"
#include "src/geo_render.h"
#include "src/model_renderer.h"
#include "src/graphics_textures.h"
#include "src/input.h"
#include "src/ui_graphics.h"
#include "src/3FB0.h"
#include "src/gfx_buffer.h"
#include "src/gfx_rect.h"
#include "src/matrix.h"
#include "src/controller.h"
#include "src/memmap.h"
#include "src/memory.h"
#include "src/stage_loader.h"

s32 Glc_GeoSpriteCallback(s32, GraphNode*);
s32 Glc_GeoBannerCallback(s32, GraphNode*);

typedef struct Glc_ColorKeyframe {
    /* 0x00 */ s16 posX;
    /* 0x04 */ f32 rotation;
    /* 0x08 */ s16 RentalSlotAnimData_PosePhase;
    /* 0x0A */ s16 unk_0A;
    /* 0x0C */ s16 unk_0C;
    /* 0x0E */ s16 unk_0E;
    /* 0x10 */ s16 unk_10;
    /* 0x12 */ s16 unk_12;
} Glc_ColorKeyframe; // size = 0x14

typedef struct Glc_CircleWipeState {
    /* 0x00 */ s16 posX;
    /* 0x02 */ s16 posY;
    /* 0x04 */ s16 rotation;
    /* 0x08 */ f32 RentalSlotAnimData_PosePhase;
} Glc_CircleWipeState; // size = 0xC

typedef struct Glc_FadeAnimState {
    /* 0x00 */ s16 posX;
    /* 0x02 */ s16 posY;
    /* 0x04 */ s16 rotation;
} Glc_FadeAnimState; // size = 0x8

static BinArchive* gClearScreenBgArchive;
static u8* gClearScreenBgImage;
static s16 gClearScreenState;
static s16 gClearScreenTimer;
static s16 gShowCursorFlag;
static s16 gCursorX;
static s16 gCursorY;
static GraphNode* gClearScreenRoot;
static GraphNode* gClearScreenNode1;
static GraphNode* gClearScreenNode2;
static unk_D_83101F00 gClearScreenNodes[2];
static unk_D_83101F00* gNode1State;
static unk_D_83101F00* gNode2State;
static Glc_CircleWipeState gBorderAnimState;
static Glc_FadeAnimState gFadeAnimState;

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
    0x00000000, 0x08000000, Glc_GeoBannerCallback, 0x00000000, 0x06000000, 0x01000000, 0x00000000,
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
    0x00000000, 0x08000000, Glc_GeoSpriteCallback, 0x00000000, 0x06000000, 0x01000000,
};

static u32 gClearScreenRootGeo[] = {
    0x0C000000,  0x05000000, 0x0B00002D, 0x00000000, 0x028001E0, 0x00000000, 0xFDBD0000,
    0x00000243,  0x05000000, 0x0D000000, 0x05000000, 0x0F000002, 0x05000000, 0x0A000000,
    &gGraphRoot0, 0x06000000, 0x06000000, 0x06000000, 0x06000000, 0x01000000,
};

static Glc_ColorKeyframe gNodeColorScaleTable[] = {
    { 0xC, 0.0f, 0, 0, 0, 0, 0, 0 },
    { 4, 2.4f, 0xFF, 0, 0, 0, 0, 0 },
    { 4, 2.0f, 0xFF, 0xFF, 0xFF, 0xC8, 0x64, 0 },
    { -1, 2.0f, 0xC8, 0xC8, 0x1E, 0, 0, 0 },
};

void Glc_UpdateSweepObject(Fragment2_1GraphNode* arg0) {
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

s32 Glc_GeoBannerCallback(s32 arg0, UNUSED GraphNode* arg1) {
    switch (arg0) {
        case 0:
            break;

        case 2:
            Glc_UpdateSweepObject(gDefaultGraphRoot);
            break;

        case 5:
            gDPPipeSync(gDisplayListHead++);

            gSPSegment(gDisplayListHead++, 0x0F, Memmap_GetSegmentVaddr(D_3000000));
            gSPDisplayList(gDisplayListHead++, gClearScreenDL1);

            GeoRender_ApplyMaterialState();
            break;
    }

    return 0;
}

void Glc_UpdateColorKeyframe(unk_D_83101F00* arg0) {
    Glc_ColorKeyframe* ptr1;
    Glc_ColorKeyframe* ptr2;
    f32 var_fv1;

    switch (arg0->unk_16A) {
        case 1:
            arg0->unk_16C--;
            ptr1 = &gNodeColorScaleTable[arg0->unk_170];
            ptr2 = &gNodeColorScaleTable[arg0->unk_170 + 1];

            arg0->unk_172 = ptr2->RentalSlotAnimData_PosePhase + (((ptr1->RentalSlotAnimData_PosePhase - ptr2->RentalSlotAnimData_PosePhase) * arg0->unk_16C) / arg0->unk_16E);
            arg0->unk_174 = ptr2->unk_0A + (((ptr1->unk_0A - ptr2->unk_0A) * arg0->unk_16C) / arg0->unk_16E);
            arg0->primColorB = ptr2->unk_0C + (((ptr1->unk_0C - ptr2->unk_0C) * arg0->unk_16C) / arg0->unk_16E);

            arg0->unk_178 = ptr2->unk_0E + (((ptr1->unk_0E - ptr2->unk_0E) * arg0->unk_16C) / arg0->unk_16E);
            arg0->unk_17A = ptr2->unk_10 + (((ptr1->unk_10 - ptr2->unk_10) * arg0->unk_16C) / arg0->unk_16E);
            arg0->unk_17C = ptr2->unk_12 + (((ptr1->unk_12 - ptr2->unk_12) * arg0->unk_16C) / arg0->unk_16E);

            var_fv1 = ptr2->rotation + (((ptr1->rotation - ptr2->rotation) * arg0->unk_16C) / arg0->unk_16E);

            if (arg0->unk_16C <= 0) {
                arg0->unk_170++;
                ptr1 = &gNodeColorScaleTable[arg0->unk_170];

                arg0->unk_16C = arg0->unk_16E = ptr1->posX;
                arg0->unk_172 = ptr1->RentalSlotAnimData_PosePhase;
                arg0->unk_174 = ptr1->unk_0A;
                arg0->primColorB = ptr1->unk_0C;
                arg0->unk_178 = ptr1->unk_0E;
                arg0->unk_17A = ptr1->unk_10;
                arg0->unk_17C = ptr1->unk_12;

                var_fv1 = ptr1->rotation;

                if (arg0->unk_16C == -1) {
                    arg0->unk_16E = 0;
                    arg0->unk_16A = 2;
                    arg0->unk_16C = arg0->unk_16E;
                }
            }

            Vec3f_SetComponentsDuplicate(&arg0->unk_000.unk_030, var_fv1, var_fv1, var_fv1);
            break;

        case 0:
        case 2:
        case 3:
            break;
    }
}

s32 Glc_GeoSpriteCallback(s32 arg0, GraphNode* arg1) {
    unk_D_83101F00* ptr = (unk_D_83101F00*)gDefaultGraphRoot;

    switch (arg0) {
        case 0:
            break;

        case 2:
            Glc_UpdateColorKeyframe(ptr);
            break;

        case 5:
            gDPPipeSync(gDisplayListHead++);

            gSPSegment(gDisplayListHead++, 0x0F, Memmap_GetSegmentVaddr(D_30015E0));
            gDPSetPrimColor(gDisplayListHead++, 0, 0, ptr->unk_172, ptr->unk_174, ptr->primColorB, 0xFF);
            gDPSetEnvColor(gDisplayListHead++, ptr->unk_178, ptr->unk_17A, ptr->unk_17C, 0xFF);
            gSPDisplayList(gDisplayListHead++, gClearScreenDL2);

            GeoRender_ApplyMaterialState();
            break;
    }
    return 0;
}

void Glc_InitCircleWipe(void) {
    gBorderAnimState.posX = 0;
    gBorderAnimState.posY = 0;
    gBorderAnimState.RentalSlotAnimData_PosePhase = 7.0f;
}

void Glc_UpdateCircleWipe(void) {
    s32 tmp;

    switch (gBorderAnimState.posX) {
        case 1:
            gBorderAnimState.posY--;
            gBorderAnimState.RentalSlotAnimData_PosePhase = (gBorderAnimState.posY * 7.0f) / gBorderAnimState.rotation;

            tmp = gBorderAnimState.posY <= 0;
            if (tmp) {
                gBorderAnimState.posX = 2;
                gBorderAnimState.posY = gBorderAnimState.rotation = 0;
                gBorderAnimState.RentalSlotAnimData_PosePhase = 0.0f;
            }
            break;

        case 0:
        case 2:
            break;
    }
}

void Glc_DrawCircleWipe(void) {
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
    if (gBorderAnimState.posX == 0) {
        return;
    }

    if ((gBorderAnimState.RentalSlotAnimData_PosePhase <= 0.0f) || (gBorderAnimState.posX == 2)) {
        gSPDisplayList(gDisplayListHead++, gDL_FillCycle);
        gDPSetFillColor(gDisplayListHead++, 0x00010001);
        gDPFillRectangle(gDisplayListHead++, 0, 0, 639, 479);
        return;
    }

    temp_ft2 = ROUND_MAX(1024.0f / gBorderAnimState.RentalSlotAnimData_PosePhase);
    sp9E = ROUND_MAX(128.0f * gBorderAnimState.RentalSlotAnimData_PosePhase);
    sp9C = ROUND_MAX(128.0f * gBorderAnimState.RentalSlotAnimData_PosePhase);

    sp38 = (0x280 - sp9E) / 2;
    sp40 = (0x1E0 - sp9C) / 2;

    gSPDisplayList(gDisplayListHead++, gPrefDL_Border);
    gDPSetCombineLERP(gDisplayListHead++, 1, TEXEL0, ENVIRONMENT, 0, 1, TEXEL0, ENVIRONMENT, 0, 1, TEXEL0, ENVIRONMENT,
                      0, 1, TEXEL0, ENVIRONMENT, 0);
    gDPSetEnvColor(gDisplayListHead++, 0, 0, 0, 255);
    gDPLoadTextureBlock_4b(gDisplayListHead++, D_3002C00, G_IM_FMT_I, 64, 64, 0, G_TX_MIRROR | G_TX_WRAP,
                           G_TX_MIRROR | G_TX_WRAP, 6, 6, G_TX_NOLOD, G_TX_NOLOD);

    Gfx_DrawTexturedRectClipped(sp38, sp40, sp9E, sp9C, 0, 0, temp_ft2, temp_ft2, 0);

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

void Glc_StartCircleWipe(s16 arg0) {
    if (arg0 > 0) {
        gBorderAnimState.posX = 1;
        gBorderAnimState.posY = gBorderAnimState.rotation = arg0;
        gBorderAnimState.RentalSlotAnimData_PosePhase = 7.0f;
    }
}

void Glc_InitBackgroundFade(void) {
    gFadeAnimState.posX = 0;
    gFadeAnimState.posY = 0;
    gFadeAnimState.rotation = 0xC0;
}

void Glc_UpdateBackgroundFade(void) {
    switch (gFadeAnimState.posX) {
        case 1:
            gFadeAnimState.posY--;
            gFadeAnimState.rotation = ((gFadeAnimState.posY * -0x3F) / 10) + 0xFF;
            if (gFadeAnimState.posY <= 0) {
                gFadeAnimState.posX = 2;
                gFadeAnimState.posY = 0;
                gFadeAnimState.rotation = 0xFF;
            }
            break;

        case 2:
            break;
    }
}

void Glc_DrawFadedBackground(u8* arg0, s16 arg1) {
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

void Glc_DrawBackground(void) {
    if (gFadeAnimState.rotation < 0xFF) {
        Glc_DrawFadedBackground(gClearScreenBgImage, gFadeAnimState.rotation);
    } else {
        Gfx_DrawTiledRgba16Image(gClearScreenBgImage);
    }
}

void Glc_StartBackgroundFade(s16 arg0) {
    gFadeAnimState.posX = arg0;
    if (gFadeAnimState.posX == 1) {
        gFadeAnimState.posY = 0xA;
        gFadeAnimState.rotation = 0xC0;
    }
}

void Glc_ReadInputs(void) {
    Cont_StartReadInputs();
    Cont_ReadInputs();
    Input_ResetRepeatState();
}

void Glc_InitObjectAnimation(unk_D_83101F00* arg0, s16 arg1) {
    Glc_ColorKeyframe* ptr;

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

                arg0->unk_16C = arg0->unk_16E = ptr->posX;
                arg0->unk_172 = ptr->RentalSlotAnimData_PosePhase;
                arg0->unk_174 = ptr->unk_0A;
                arg0->primColorB = ptr->unk_0C;
                arg0->unk_178 = ptr->unk_0E;
                arg0->unk_17A = ptr->unk_10;
                arg0->unk_17C = ptr->unk_12;

                Vec3f_SetComponentsDuplicate(&arg0->unk_000.unk_030, ptr->rotation, ptr->rotation, ptr->rotation);
                break;
        }
    }
}

void Glc_DrawScisRectangle(s16 arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5, s16 arg6, s16 arg7) {
    gSPScisTextureRectangle(gDisplayListHead++, arg0 << 2, arg1 << 2, ((arg0 + arg2) - 1) << 2,
                            ((arg1 + arg3) - 1) << 2, 0, arg4, arg5, arg6, arg7);
}

void Glc_DrawTrackingIcon(void) {
    f32 v = 1.8f;
    s16 temp_fa0;
    s16 temp_ft2;

    gSPDisplayList(gDisplayListHead++, gPrefDL_Border);

    temp_ft2 = ROUND_MAX(28 * v);
    temp_fa0 = ROUND_MAX(1024.0f / v);

    gDPLoadTextureBlock(gDisplayListHead++, D_30025E0, G_IM_FMT_RGBA, G_IM_SIZ_16b, 28, 28, 0,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                        G_TX_NOLOD);

    Glc_DrawScisRectangle(gCursorX, gCursorY, temp_ft2, temp_ft2, 0, 0, temp_fa0, temp_fa0);

    gSPDisplayList(gDisplayListHead++, gPrefDL_End);
}

void Glc_ClearInitState(void) {
    gClearScreenState = 0;
    if (gSessionContext.inRound2 != 0) {
        gShowCursorFlag = 1;
    } else {
        gShowCursorFlag = 0;
    }
    gCursorY = -0x64;
    gCursorX = gCursorY;
    Glc_InitCircleWipe();
    Glc_InitBackgroundFade();
}

void Glc_ClearDraw(void) {
    BgStage_DrawFrame();
    Glc_DrawBackground();
    Geo_RenderRootNode(gClearScreenRoot);
    if (gShowCursorFlag != 0) {
        Glc_DrawTrackingIcon();
    }
    Glc_DrawCircleWipe();
    BgStage_AdvanceFrame();
}

s32 Glc_ClearAdvanceState(void) {
    s32 sp1C = 1;

    switch (gClearScreenState) {
        case 0:
            if (StageContext_GetFadeMode() == 0) {
                gClearScreenState = 1;
                gClearScreenTimer = 0;
                Glc_InitObjectAnimation(gNode1State, 1);
            }
            break;

        case 1:
            if (gNode1State->unk_16A == 2) {
                switch (gNode2State->unk_16A) {
                    case 0:
                        Glc_InitObjectAnimation(gNode2State, 1);
                        break;

                    case 2:
                        gClearScreenTimer += 1;
                        if (gClearScreenTimer == 1) {
                            Glc_StartBackgroundFade(1);
                        }

                        if (gClearScreenTimer >= 0x1E) {
                            gClearScreenState = 2;
                            gClearScreenTimer = 0;
                            Glc_StartCircleWipe(0xF);
                            StageContext_SetClearColor(1);
                        }
                        break;
                }
            }
            break;

        case 2:
            if (gBorderAnimState.posX == 2) {
                sp1C = 0;
            }
            break;
    }

    return sp1C;
}

void Glc_ClearRunLoop(void) {
    Glc_ClearInitState();
    StageFade_StartFromOpaque(0xF);

    do {
        Glc_ReadInputs();
        Glc_UpdateCircleWipe();
        Glc_UpdateBackgroundFade();
        Glc_ClearDraw();
    } while (Glc_ClearAdvanceState() != 0);
}

void Glc_ClearInitGraphics(void) {
    unk_D_83101F00* ptr;
    MemoryBlock* temp_v0 = MainPool_AllocState(main_pool_get_available(), 0);
    s32 i;

    gClearScreenRoot = process_geo_layout(temp_v0, gClearScreenRootGeo);
    gClearScreenNode1 = process_geo_layout(temp_v0, gClearScreenGeo1);
    gClearScreenNode2 = process_geo_layout(temp_v0, gClearScreenGeo2);

    MainPool_FinalizeAllocation(temp_v0);
    ModelRenderer_InitDisplayRoots();

    for (i = 0; i < 2; i++) {
        ptr = &gClearScreenNodes[i];

        ModelRenderer_AttachDisplayObject(&ptr->unk_000);

        ptr->unk_172 = ptr->unk_174 = ptr->primColorB = 0;
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
                Vec3f_SetComponentsDuplicate(&ptr->unk_000.unk_024, -520.0f, 44.0f, -579.0f);
                Vec3f_SetComponentsDuplicate(&ptr->unk_000.unk_030, 2.0f, 2.0f, 2.0f);
                Model_InitDisplayObject(&ptr->unk_000, 0, 0, gClearScreenNode1);
                ptr->unk_168 = 1;
                gNode1State = ptr;
                break;

            case 1:
                Vec3f_SetComponentsDuplicate(&ptr->unk_000.unk_024, 0.0, -24.0f, -579.0f);
                Vec3f_SetComponentsDuplicate(&ptr->unk_000.unk_030, 0.0f, 0.0f, 0.0f);
                Model_InitDisplayObject(&ptr->unk_000, 0, 0, gClearScreenNode2);
                ptr->unk_168 = 2;
                gNode2State = ptr;
                break;
        }
    }
}

s32 GymLeaderCastleClear_Main(UNUSED s32 arg0, UNUSED s32 arg1) {
    Stage* sp24;

    main_pool_push_state('CLRG');

    Gfx_InitDisplayListBuffers(0x10000, 0);
    sp24 = StageContext_Allocate(1, 0, 2, 0, 2, 1);
    Font_Init(0x10, 0);

    ASSET_LOAD(D_1000000, common_menu1_ui, 0);
    ASSET_LOAD(D_3000000, gym_leader_castle_clear_gfx, 0);
    gClearScreenBgArchive = ASSET_LOAD2(backgrounds, 1, 1);
    gClearScreenBgImage = BinArchive_GetFile(gClearScreenBgArchive, 0xE);

    Glc_ClearInitGraphics();
    StageContext_Activate(sp24);
    Glc_ClearRunLoop();
    StageLoader_RunFrames(2);
    StageContext_Deactivate();
    Font_Free();
    Gfx_FreeDisplayListBuffers();

    main_pool_pop_state('CLRG');

    return 0;
}
