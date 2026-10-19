#include "fragment15.h"
#include "src/1CF30.h"
#include "src/20470.h"
#include "src/2E110.h"
#include "src/6A40.h"
#include "src/6BC0.h"
#include "src/F420.h"

const char gCupNameFreeBattle[] = "FREE BATTLE";
const char gCupNamePokeCup[] = "POK\xE9 CUP";
const char gCupNamePokeCup2[] = "POK\xE9 CUP2";
const char gCupNamePetitCup[] = "PETIT CUP";
const char gCupNamePikaCup[] = "PIKA CUP";
const char gCupNamePrimeCup[] = "PRIME CUP";
const char gCupNamePewterGym[] = "PEWTER GYM";
const char gCupNameCeruleanGym[] = "CERULEAN GYM";
const char gCupNameVermilionGym[] = "VERMILION GYM";
const char gCupNameCeladonGym[] = "CELADON GYM";
const char gCupNameFuchsiaGym[] = "FUCHSIA GYM";
const char gCupNameSaffronGym[] = "SAFFRON GYM";
const char gCupNameCinnabarGym[] = "CINNABAR GYM";
const char gCupNameViridianGym[] = "VIRIDIAN GYM";
const char gCupNameEliteFour[] = "VS ELITE FOUR";
const char gCupNameMewtwo[] = "VS MEWTWO";

extern u8 D_50002A0[];
extern u8 D_50003F0[];
extern u8 D_5000BA0[];
extern u8 D_5000C90[];
extern u8 D_50011D0[];
extern u8 D_5001680[];
extern u8 D_50017E8[];

void DrawPanelBackground(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    FramebufferImage* temp_s1 = Gfx_GetCurrentFramebuffer();
    Vtx* temp_s2 = GfxAlloc(sizeof(Vtx) * 4);
    Mtx* sp84 = GfxAlloc(sizeof(Mtx) * 1);
    Vp* sp80 = GfxAlloc(sizeof(Vp) * 1);

    SetViewport(sp80, temp_s1->width, temp_s1->height);

    gSPViewport(gDisplayListHead++, (u32)sp80 & 0x1FFFFFFF);

    guOrtho(sp84, 0.5f, temp_s1->width - 0.5f, temp_s1->height - 0.5f, 0.5f, -2.0f, 2.0f, 1.0f);

    SetTileVertex(&temp_s2[0], arg0, arg1, -1, 0, 0, 0, 0, 0, arg4);
    SetTileVertex(&temp_s2[1], arg0 + arg2, arg1, -1, 0, 0, 0, 0, 0, arg4);
    SetTileVertex(&temp_s2[2], arg0, arg1 + arg3, -1, 0, 0, 0, 0, 0, arg4);
    SetTileVertex(&temp_s2[3], arg0 + arg2, arg1 + arg3, -1, 0, 0, 0, 0, 0, arg4);

    gDPPipeSync(gDisplayListHead++);
    gDPSetCycleType(gDisplayListHead++, G_CYC_1CYCLE);
    gSPClearGeometryMode(gDisplayListHead++, G_ZBUFFER | G_FOG | G_LIGHTING);
    gSPSetGeometryMode(gDisplayListHead++, G_SHADE);
    gDPSetCombineMode(gDisplayListHead++, G_CC_SHADE, G_CC_SHADE);
    gDPSetRenderMode(gDisplayListHead++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
    gSPPerspNormalize(gDisplayListHead++, 0xFFFF);
    gSPMatrix(gDisplayListHead++, (u32)sp84 & 0x1FFFFFFF, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
    gSPMatrix(gDisplayListHead++, (u32)&gCamProjectionMatrix & 0x1FFFFFFF, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPVertex(gDisplayListHead++, (u32)temp_s2 & 0x1FFFFFFF, 4, 0);
    gSP2Triangles(gDisplayListHead++, 0, 2, 3, 0, 0, 3, 1, 0);
}

void StagePanel_Init(void) {
}

void DrawBorderedRect(s16 arg0, s16 arg1, s16 arg2, s16 arg3, u8 arg4, u8 arg5, u8 arg6, u8 arg7) {
    s16 var_s2;
    s16 var_s3;
    s16 sp4C;
    s16 sp48;

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

    sp4C = arg2 - (var_s3 * 2);
    sp48 = arg3 - (var_s2 * 2);

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

    if ((sp4C > 0) && (sp48 > 0)) {
        Gfx_FillRectRGBA(arg0 + var_s3, arg1, sp4C, var_s2, arg4, arg5, arg6, arg7);
        Gfx_FillRectRGBA(arg0, (arg1 + var_s3), arg2, sp48, arg4, arg5, arg6, arg7);
        Gfx_FillRectRGBA(arg0 + var_s3, (arg1 + var_s3) + sp48, sp4C, var_s2, arg4, arg5, arg6, arg7);
    } else if (sp4C > 0) {
        Gfx_FillRectRGBA(arg0 + var_s3, arg1, sp4C, arg3, arg4, arg5, arg6, arg7);
    } else if (sp48 > 0) {
        Gfx_FillRectRGBA(arg0, arg1 + var_s2, arg2, sp48, arg4, arg5, arg6, arg7);
    }

    gSPDisplayList(gDisplayListHead++, gPrefDL_End);
}

void StagePanel_Update(void) {
}

void DrawClippedTextureRect(s16 arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5, s16 arg6, s16 arg7) {
    ClipRect sp30;

    Gfx_MakeClipRect(&sp30, arg0, arg1, (arg0 + arg2) - 1, (arg1 + arg3) - 1);

    if (Gfx_IntersectClip(&sp30) != 0) {
        if (arg6 != 0) {
            arg4 += ((sp30.x1 - arg0) * arg6) >> 5;
        }

        if (arg7 != 0) {
            arg5 += ((sp30.y2 - arg1) * arg7) >> 5;
        }

        sp30.y1 += 1;
        sp30.x2 += 1;

        gSPTextureRectangle(gDisplayListHead++, sp30.x1 << 2, sp30.y2 << 2, sp30.y1 << 2, sp30.x2 << 2, G_TX_RENDERTILE,
                            arg4, arg5, arg6, arg7);
    }
}

void LoadTextureTileAndDrawRect(s16 arg0, s16 arg1, s16 arg2, s16 arg3, u8* arg4, s16 arg5) {
    gDPLoadTextureTile(gDisplayListHead++, arg4, G_IM_FMT_IA, G_IM_SIZ_8b, arg2, 0, 0, 0, arg2 - 1, arg3 - 1, 0,
                       G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, 3, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

    DrawClippedTextureRect(arg0, arg1, arg2, arg3, gStagePanelAnimState.unk_02 << 5, 0, 0x400, 0x400);
}

void DrawTexture2Cycle(u8* arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4) {
    gDPPipeSync(gDisplayListHead++);

    gDPSetCycleType(gDisplayListHead++, G_CYC_2CYCLE);
    gSPClearGeometryMode(gDisplayListHead++, G_ZBUFFER | G_FOG | G_LIGHTING);
    gDPSetTexturePersp(gDisplayListHead++, G_TP_NONE);
    gDPSetRenderMode(gDisplayListHead++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
    gDPSetCombineLERP(gDisplayListHead++, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0,
                      COMBINED, 0, 0, 0, COMBINED);
    gDPSetEnvColor(gDisplayListHead++, 0, 0, 0, 255);
    gDPSetPrimColor(gDisplayListHead++, 0, 0, 95, 55, 0, 255);
    gDPSetTextureFilter(gDisplayListHead++, G_TF_BILERP);

    LoadTextureTileAndDrawRect(arg1, arg2, arg3, arg4, arg0, arg3);

    gSPDisplayList(gDisplayListHead++, gPrefDL_End);
}

void DrawSpriteRotated(u8* arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4) {
    Vec3s spD8;
    Vec3f spCC;
    Vec3f spC0;
    UNUSED s32 pad;
    FramebufferImage* spB8;
    Vtx* spB4;
    MtxF* spB0;
    Mtx* spAC;
    MtxF* spA8;
    Vp* spA4;

    spB8 = Gfx_GetCurrentFramebuffer();
    spB4 = GfxAlloc(sizeof(Vtx) * 4);
    spB0 = GfxAlloc(sizeof(MtxF) * 1);
    spAC = GfxAlloc(sizeof(Mtx) * 1);
    spA8 = GfxAlloc(sizeof(MtxF) * 1);
    spA4 = GfxAlloc(sizeof(Vp) * 1);

    Vec3s_Set(&spD8, 0, 0, gStagePanelAnimState.unk_06);

    Vec3f_Set(&spCC, (f32)arg1 + (arg3 / 2), (f32)arg2 + arg4, 0.0f);
    Vec3f_Set(&spC0, 1.0f, 1.0f, 1.0f);
    Matrix_RotateTranslate(spA8, &spCC, &spD8);
    Matrix_Scale(spA8, spA8, &spC0);
    Matrix_ConvertToMtx(spB0, spA8);
    SetViewport(spA4, spB8->width, spB8->height);

    gSPViewport(gDisplayListHead++, (u32)spA4 & 0x1FFFFFFF);

    guOrtho(spAC, 0.5f, spB8->width - 0.5f, spB8->height - 0.5f, 0.5f, -2.0f, 2.0f, 1.0f);

    SetTileVertex(&spB4[0], -(arg3 / 2), -arg4, -1, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF);
    SetTileVertex(&spB4[1], (arg3 / 2), -arg4, -1, arg3 << 5, 0, 0xFF, 0xFF, 0xFF, 0xFF);
    SetTileVertex(&spB4[2], -(arg3 / 2), 0, -1, 0, arg4 << 5, 0xFF, 0xFF, 0xFF, 0xFF);
    SetTileVertex(&spB4[3], (arg3 / 2), 0, -1, arg3 << 5, arg4 << 5, 0xFF, 0xFF, 0xFF, 0xFF);

    gSPDisplayList(gDisplayListHead++, gPrefDL_Border);
    gSPClearGeometryMode(gDisplayListHead++, G_ZBUFFER | G_LIGHTING);

    if (gStagePanelAnimState.unk_06 == 0) {
        gDPSetTextureFilter(gDisplayListHead++, G_TF_POINT);
        gDPSetRenderMode(gDisplayListHead++, G_RM_TEX_EDGE, G_RM_TEX_EDGE2);
    } else {
        gDPSetTextureFilter(gDisplayListHead++, G_TF_BILERP);
        gDPSetRenderMode(gDisplayListHead++, G_RM_AA_TEX_EDGE, G_RM_AA_TEX_EDGE2);
    }

    gDPSetTexturePersp(gDisplayListHead++, G_TP_PERSP);
    gSPTexture(gDisplayListHead++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);

    gDPLoadTextureTile(gDisplayListHead++, arg0, G_IM_FMT_RGBA, G_IM_SIZ_16b, arg3, 0, 0, 0, arg3 - 1, arg4 - 1, 0,
                       G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                       G_TX_NOLOD);

    gSPPerspNormalize(gDisplayListHead++, 0xFFFF);
    gSPMatrix(gDisplayListHead++, (u32)spAC & 0x1FFFFFFF, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
    gSPMatrix(gDisplayListHead++, (u32)spB0 & 0x1FFFFFFF, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPVertex(gDisplayListHead++, (u32)spB4 & 0x1FFFFFFF, 4, 0);
    gSP2Triangles(gDisplayListHead++, 0, 2, 3, 0, 0, 3, 1, 0);
    gSPDisplayList(gDisplayListHead++, gPrefDL_End);
    gSPTexture(gDisplayListHead++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF);
}

void DrawRotatedSprite(u8* arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5, u8 arg6) {
    s32 a1;
    s32 a2;
    s16 spF8[4];
    s16 spF0[4];
    FramebufferImage* spEC;
    Vtx* spE8;
    Mtx* spE4;
    Vp* spE0;

    spEC = Gfx_GetCurrentFramebuffer();
    spE8 = GfxAlloc(sizeof(Vtx) * 4);
    spE4 = GfxAlloc(sizeof(Mtx) * 1);
    spE0 = GfxAlloc(sizeof(Vp) * 1);
    a1 = arg1;
    a2 = arg2;

    spF8[0] = ((-(arg3 / 2) * COSS(arg5)) - (SINS(arg5) * -arg4)) + a1;
    spF0[0] = ((-(arg3 / 2) * SINS(arg5)) + (COSS(arg5) * -arg4)) + a2;
    spF8[1] = (((arg3 / 2) * COSS(arg5)) - (SINS(arg5) * -arg4)) + a1;
    spF0[1] = (((arg3 / 2) * SINS(arg5)) + (COSS(arg5) * -arg4)) + a2;
    spF8[2] = (-(arg3 / 2) * COSS(arg5)) + a1;
    spF0[2] = (-(arg3 / 2) * SINS(arg5)) + a2;
    spF8[3] = ((arg3 / 2) * COSS(arg5)) + a1;
    spF0[3] = ((arg3 / 2) * SINS(arg5)) + a2;

    SetViewport(spE0, spEC->width, spEC->height);

    gSPViewport(gDisplayListHead++, (u32)spE0 & 0x1FFFFFFF);

    guOrtho(spE4, 0.5f, spEC->width - 0.5f, spEC->height - 0.5f, 0.5f, -2.0f, 2.0f, 1.0f);
    SetTileVertex(&spE8[0], spF8[0], spF0[0], -1, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF);
    SetTileVertex(&spE8[1], spF8[1], spF0[1], -1, arg3 << 5, 0, 0xFF, 0xFF, 0xFF, 0xFF);
    SetTileVertex(&spE8[2], spF8[2], spF0[2], -1, 0, arg4 << 5, 0xFF, 0xFF, 0xFF, 0xFF);
    SetTileVertex(&spE8[3], spF8[3], spF0[3], -1, arg3 << 5, arg4 << 5, 0xFF, 0xFF, 0xFF, 0xFF);

    if (arg6 == 0) {
        gDPLoadTextureBlock(gDisplayListHead++, arg0, G_IM_FMT_IA, G_IM_SIZ_8b, arg3, arg4, 0,
                            G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK,
                            G_TX_NOLOD, G_TX_NOLOD);
    }

    gSPDisplayList(gDisplayListHead++, gPrefDL_Border);

    gDPPipeSync(gDisplayListHead++);

    gDPSetCycleType(gDisplayListHead++, G_CYC_2CYCLE);
    gSPClearGeometryMode(gDisplayListHead++, G_ZBUFFER | G_FOG | G_LIGHTING);
    gDPSetTexturePersp(gDisplayListHead++, G_TP_NONE);
    gDPSetRenderMode(gDisplayListHead++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
    gDPSetCombineLERP(gDisplayListHead++, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0,
                      COMBINED, 0, 0, 0, COMBINED);
    gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255);
    gDPSetPrimColor(gDisplayListHead++, 0, 0, 255, 255, 255, 255);
    gDPSetTextureFilter(gDisplayListHead++, G_TF_BILERP);
    gDPSetTexturePersp(gDisplayListHead++, G_TP_PERSP);
    gSPTexture(gDisplayListHead++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);

    gSPPerspNormalize(gDisplayListHead++, 0xFFFF);
    gSPMatrix(gDisplayListHead++, (u32)spE4 & 0x1FFFFFFF, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
    gSPMatrix(gDisplayListHead++, (u32)&gCamProjectionMatrix & 0x1FFFFFFF, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    gSPVertex(gDisplayListHead++, (u32)spE8 & 0x1FFFFFFF, 4, 0);
    gSP2Triangles(gDisplayListHead++, 0, 2, 3, 0, 0, 3, 1, 0);

    gSPDisplayList(gDisplayListHead++, gPrefDL_End);

    gSPTexture(gDisplayListHead++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF);
}

void DrawRotatedSpriteAlt(u8* arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5, u8 arg6) {
    f32 a1;
    f32 a2;
    s16 spE0[4];
    s16 spD8[4];
    FramebufferImage* spD4;
    Vtx* spD0;
    Mtx* spCC;
    Vp* spC8;

    spD4 = Gfx_GetCurrentFramebuffer();
    spD0 = GfxAlloc(sizeof(Vtx) * 4);
    spCC = GfxAlloc(sizeof(Mtx) * 1);
    spC8 = GfxAlloc(sizeof(Vp) * 1);

    a1 = arg1;
    a2 = arg2;

    spE0[0] = (COSS(arg5) * -12.0f) + a1;
    spD8[0] = (SINS(arg5) * -12.0f) + a2;

    spE0[1] = (COSS(arg5) * 12.0f) + a1;
    spD8[1] = (SINS(arg5) * 12.0f) + a2;

    spE0[2] = ((COSS(arg5) * -12.0f) - (SINS(arg5) * 56.0f)) + a1;
    spD8[2] = (((SINS(arg5) * -12.0f) + COSS(arg5) * 56.0f)) + a2;

    spE0[3] = ((COSS(arg5) * 12.0f) - (SINS(arg5) * 56.0f)) + a1;
    spD8[3] = (((SINS(arg5) * 12.0f) + COSS(arg5) * 56.0f)) + a2;

    SetViewport(spC8, spD4->width, spD4->height);

    gSPViewport(gDisplayListHead++, (u32)spC8 & 0x1FFFFFFF);

    guOrtho(spCC, 0.5f, spD4->width - 0.5f, spD4->height - 0.5f, 0.5f, -2.0f, 2.0f, 1.0f);

    SetTileVertex(&spD0[0], spE0[0], spD8[0], -1, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF);
    SetTileVertex(&spD0[1], spE0[1], spD8[1], -1, arg3 << 5, 0, 0xFF, 0xFF, 0xFF, 0xFF);
    SetTileVertex(&spD0[2], spE0[2], spD8[2], -1, 0, arg4 << 5, 0xFF, 0xFF, 0xFF, 0xFF);
    SetTileVertex(&spD0[3], spE0[3], spD8[3], -1, arg3 << 5, arg4 << 5, 0xFF, 0xFF, 0xFF, 0xFF);

    if (arg6 == 0) {
        gDPLoadTextureBlock(gDisplayListHead++, arg0, G_IM_FMT_IA, G_IM_SIZ_8b, arg3, arg4, 0,
                            G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK,
                            G_TX_NOLOD, G_TX_NOLOD);
    }

    gSPDisplayList(gDisplayListHead++, gPrefDL_Border);

    gDPPipeSync(gDisplayListHead++);

    gDPSetCycleType(gDisplayListHead++, G_CYC_2CYCLE);
    gSPClearGeometryMode(gDisplayListHead++, G_ZBUFFER | G_FOG | G_LIGHTING);
    gDPSetTexturePersp(gDisplayListHead++, G_TP_NONE);
    gDPSetRenderMode(gDisplayListHead++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
    gDPSetCombineLERP(gDisplayListHead++, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0,
                      COMBINED, 0, 0, 0, COMBINED);
    gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255);
    gDPSetPrimColor(gDisplayListHead++, 0, 0, 255, 255, 255, 255);
    gDPSetTextureFilter(gDisplayListHead++, G_TF_BILERP);
    gDPSetTexturePersp(gDisplayListHead++, G_TP_PERSP);
    gSPTexture(gDisplayListHead++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);
    gSPPerspNormalize(gDisplayListHead++, 0xFFFF);

    gSPMatrix(gDisplayListHead++, (u32)spCC & 0x1FFFFFFF, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
    gSPMatrix(gDisplayListHead++, (u32)&gCamProjectionMatrix & 0x1FFFFFFF, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    gSPVertex(gDisplayListHead++, (u32)spD0 & 0x1FFFFFFF, 4, 0);
    gSP2Triangles(gDisplayListHead++, 0, 2, 3, 0, 0, 3, 1, 0);

    gSPDisplayList(gDisplayListHead++, gPrefDL_End);

    gSPTexture(gDisplayListHead++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF);
}

void DrawRotatedSpriteOffset(u8* arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5, u8 arg6) {
    f32 temp_fv0;
    f32 temp_fv1;
    s16 spE0[4];
    s16 spD8[4];
    FramebufferImage* spD4;
    Vtx* spD0;
    Mtx* spCC;
    Vp* spC8;

    spD4 = Gfx_GetCurrentFramebuffer();
    spD0 = GfxAlloc(sizeof(Vtx) * 4);
    spCC = GfxAlloc(sizeof(Mtx) * 1);
    spC8 = GfxAlloc(sizeof(Vp) * 1);

    temp_fv0 = arg1;
    temp_fv1 = arg2;

    spE0[0] = (COSS(arg5 + 0xC000) * -12.0f) + temp_fv0;
    spD8[0] = (SINS(arg5 + 0xC000) * -12.0f) + temp_fv1;

    spE0[1] = (COSS(arg5 + 0xC000) * 12.0f) + temp_fv0;
    spD8[1] = (SINS(arg5 + 0xC000) * 12.0f) + temp_fv1;

    spE0[2] = ((COSS(arg5 + 0xC000) * -12.0f) - (SINS(arg5 + 0xC000) * 56.0f)) + temp_fv0;
    spD8[2] = ((SINS(arg5 + 0xC000) * -12.0f) + (COSS(arg5 + 0xC000) * 56.0f)) + temp_fv1;

    spE0[3] = ((COSS(arg5 + 0xC000) * 12.0f) - (SINS(arg5 + 0xC000) * 56.0f)) + temp_fv0;
    spD8[3] = ((SINS(arg5 + 0xC000) * 12.0f) + (COSS(arg5 + 0xC000) * 56.0f)) + temp_fv1;

    SetViewport(spC8, spD4->width, spD4->height);

    gSPViewport(gDisplayListHead++, (u32)spC8 & 0x1FFFFFFF);

    guOrtho(spCC, 0.5f, spD4->width - 0.5f, spD4->height - 0.5f, 0.5f, -2.0f, 2.0f, 1.0f);

    SetTileVertex(&spD0[0], spE0[0], spD8[0], -1, arg3 << 5, 0, 0xFF, 0xFF, 0xFF, 0xFF);
    SetTileVertex(&spD0[1], spE0[1], spD8[1], -1, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF);
    SetTileVertex(&spD0[2], spE0[2], spD8[2], -1, arg3 << 5, arg4 << 5, 0xFF, 0xFF, 0xFF, 0xFF);
    SetTileVertex(&spD0[3], spE0[3], spD8[3], -1, 0, arg4 << 5, 0xFF, 0xFF, 0xFF, 0xFF);

    if (arg6 == 0) {
        gDPLoadTextureBlock(gDisplayListHead++, arg0, G_IM_FMT_IA, G_IM_SIZ_8b, arg3, arg4, 0,
                            G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK,
                            G_TX_NOLOD, G_TX_NOLOD);
    }

    gSPDisplayList(gDisplayListHead++, gPrefDL_Border);

    gDPPipeSync(gDisplayListHead++);

    gDPSetCycleType(gDisplayListHead++, G_CYC_2CYCLE);
    gSPClearGeometryMode(gDisplayListHead++, G_ZBUFFER | G_FOG | G_LIGHTING);
    gDPSetTexturePersp(gDisplayListHead++, G_TP_NONE);
    gDPSetRenderMode(gDisplayListHead++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
    gDPSetCombineLERP(gDisplayListHead++, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0,
                      COMBINED, 0, 0, 0, COMBINED);
    gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255);
    gDPSetPrimColor(gDisplayListHead++, 0, 0, 255, 255, 255, 255);
    gDPSetTextureFilter(gDisplayListHead++, G_TF_BILERP);
    gDPSetTexturePersp(gDisplayListHead++, G_TP_PERSP);
    gSPTexture(gDisplayListHead++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);
    gSPPerspNormalize(gDisplayListHead++, 0xFFFF);

    gSPMatrix(gDisplayListHead++, (u32)spCC & 0x1FFFFFFF, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
    gSPMatrix(gDisplayListHead++, (u32)&gCamProjectionMatrix & 0x1FFFFFFF, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    gSPVertex(gDisplayListHead++, (u32)spD0 & 0x1FFFFFFF, 4, 0);
    gSP2Triangles(gDisplayListHead++, 0, 2, 3, 0, 0, 3, 1, 0);

    gSPDisplayList(gDisplayListHead++, gPrefDL_End);
    gSPTexture(gDisplayListHead++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF);
}

void DrawTexturedPanel(u8* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, u8 arg5, u8 arg6, u8 arg7, u8 arg8, u8 arg9,
                   u8 argA, u8 argB, u8 argC) {
    FramebufferImage* temp_s1 = Gfx_GetCurrentFramebuffer();
    Vtx* temp_s2 = GfxAlloc(sizeof(Vtx) * 4);
    Mtx* spAC = GfxAlloc(sizeof(Mtx) * 1);
    Vp* spA8 = GfxAlloc(sizeof(Vp));

    SetViewport(spA8, temp_s1->width, temp_s1->height);

    gSPViewport(gDisplayListHead++, (u32)spA8 & 0x1FFFFFFF);

    guOrtho(spAC, 0.5f, temp_s1->width - 0.5f, temp_s1->height - 0.5f, 0.5f, -2.0f, 2.0f, 1.0f);

    SetTileVertex(&temp_s2[0], arg1, arg2, -1, argC << 5, 0, 0xFF, 0xFF, 0xFF, 0xFF);
    SetTileVertex(&temp_s2[1], arg1 + arg3, arg2, -1, argB << 5, 0, 0xFF, 0xFF, 0xFF, 0xFF);
    SetTileVertex(&temp_s2[2], arg1, arg2 + arg4, -1, argC << 5, arg6 << 5, 0xFF, 0xFF, 0xFF, 0xFF);
    SetTileVertex(&temp_s2[3], arg1 + arg3, arg2 + arg4, -1, argB << 5, arg6 << 5, 0xFF, 0xFF, 0xFF, 0xFF);

    gSPDisplayList(gDisplayListHead++, gPrefDL_Border);
    gDPSetRenderMode(gDisplayListHead++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
    gDPSetTextureFilter(gDisplayListHead++, G_TF_POINT);
    gDPSetTexturePersp(gDisplayListHead++, G_TP_PERSP);
    gSPTexture(gDisplayListHead++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);

    gDPLoadTextureTile(gDisplayListHead++, arg0, G_IM_FMT_RGBA, G_IM_SIZ_16b, arg5, 0, arg7, arg8, arg9 - 1, argA - 1,
                       0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                       G_TX_NOLOD);

    gSPPerspNormalize(gDisplayListHead++, 0xFFFF);
    gSPMatrix(gDisplayListHead++, (u32)spAC & 0x1FFFFFFF, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
    gSPMatrix(gDisplayListHead++, (u32)&gCamProjectionMatrix & 0x1FFFFFFF, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPVertex(gDisplayListHead++, (u32)temp_s2 & 0x1FFFFFFF, 4, 0);
    gSP2Triangles(gDisplayListHead++, 0, 2, 3, 0, 0, 3, 1, 0);
    gSPDisplayList(gDisplayListHead++, gPrefDL_End);
    gSPTexture(gDisplayListHead++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF);
}

void RenderMessageBox(char* arg0) {
    Color_RGB8 sp4C;
    Color_RGB8 sp48;
    s32 sp44;
    UNUSED s16 pad2;
    s16 sp40;

    if (gCameraParams->unk_014 != 0) {
        sp44 = MeasureTextWidth(0x10, 0, arg0);

        if (gCameraParams->unk_014 == 1) {
            DrawTexturedPanel(&D_5001950, 0x3C, 0xAE, 0x22, 0x2B, 0x64, 0x2B, 0, 0, 0x22, 0x2B, 0x21, 0);
            DrawTexturedPanel(&D_5001950, 0x5E, 0xAE, 0x22, 0x2B, 0x64, 0x2B, 0x22, 0, 0x44, 0x2B, 0x43, 0x22);
            DrawTexturedPanel(&D_5001950, 0x80, 0xAE, 0x20, 0x2B, 0x64, 0x2B, 0x44, 0, 0x64, 0x2B, 0x63, 0x44);
            DrawTexturedPanel(&D_5001950, 0xE2, 0xAE, 0x22, 0x2B, 0x64, 0x2B, 0, 0, 0x22, 0x2B, 0, 0x21);
            DrawTexturedPanel(&D_5001950, 0xC0, 0xAE, 0x22, 0x2B, 0x64, 0x2B, 0x22, 0, 0x44, 0x2B, 0x22, 0x43);
            DrawTexturedPanel(&D_5001950, 0xA0, 0xAE, 0x20, 0x2B, 0x64, 0x2B, 0x44, 0, 0x64, 0x2B, 0x44, 0x63);
            // clang-format off
            sp4C.r = 0xF0; sp4C.g = 0x78; sp4C.b = 0x6E;
            sp48.r = 0xF0; sp48.g = 0xF0; sp48.b = 0x78;
            // clang-format on
            sp40 = 5;
        } else {
            DrawTexturedPanel(&D_5003AE8, 0x4C, 0xAE, 0x20, 0x28, 0x20, 0x28, 0, 0, 0x20, 0x28, 0x1F, 0);
            DrawTexturedPanel(&D_5003AE8, 0x6C, 0xAE, 0x68, 0x28, 0x20, 0x28, 0x1C, 0, 0x20, 0x2B, 0x87, 0x20);
            DrawTexturedPanel(&D_5003AE8, 0xD4, 0xAE, 0x20, 0x28, 0x20, 0x28, 0, 0, 0x20, 0x28, 0, 0x20);
            // clang-format off
            sp4C.r = 0xDC; sp4C.g = 0xFF; sp4C.b = 0xDC;
            sp48.r = 0x78; sp48.g = 0xB4; sp48.b = 0xFF;
            // clang-format on
            sp40 = 7;
        }

        Text_ResetState();
        Text_BeginRender();
        Text_SetFont(0x10, 0);
        Text_SetEnvColor(sp4C.r, sp4C.g, sp4C.b, 0xFF);
        Text_SetPrimColor(sp48.r, sp48.g, sp48.b, 0xFF);
        Text_Print(0xA0 - (sp44 / 2), sp40 + 0xAE, arg0);
        Text_EndRender();
        Text_SetupDL();
        DrawPanelBackground(0x50, 0xAC, 0xA0, 0x2D, 0);
    }
}

void RenderMainMenu(UNUSED s32 arg0) {
    s32 i;
    s32 var_v1;

    if (gCameraNavActiveFlag != 0) {
        DrawBorderedRect(0x55, 0x20, 0x96, 0x8C, 0, 0, 0x8C, 0x64);

        gSPDisplayList(gDisplayListHead++, gPrefDL_Border);

        if (gCameraNavSubIndex != 0) {
            var_v1 = 0xFF;
        } else {
            var_v1 = 0x37;
        }

        gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, var_v1);

        Gfx_DrawSpriteIA8(0x93, 0x20, 0x18, 0xF, &D_50017E8, 0x18, 0);

        if ((gCameraNavMaxIndex - 4) != gCameraNavSubIndex) {
            var_v1 = 0xFF;
        } else {
            var_v1 = 0x37;
        }

        gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, var_v1);

        Gfx_DrawSpriteIA8(0x93, 0x9C, 0x18, 0xF, &D_5001680, 0x18, 0);

        gSPDisplayList(gDisplayListHead++, gPrefDL_End);
        gSPDisplayList(gDisplayListHead++, gDL_PalettedIcon);

        Gfx_DrawSpriteRGBA16Paletted(0x59, (gCameraNavTransition * 0x14) + 0x35, 0x18, 0xE, D_5000000, &D_50002A0, 0x18, 0x100000);

        gSPDisplayList(gDisplayListHead++, gPrefDL_End);

        Text_ResetState();
        Text_SetFont(4, 0);

        for (i = gCameraNavSubIndex; i < gCameraNavSubIndex + 5; i++) {
            if (gCameraNavTransition == (i - gCameraNavSubIndex)) {
                Text_SetEnvColor(0xFF, 0xFF, 0, 0xFF);
            } else {
                Text_SetEnvColor(0xFF, 0xFF, 0xFF, 0xFF);
            }
            Text_Print(0xA0 - (MeasureTextWidth(4, 0, gStagePanelLabelStrings[i]) / 2), ((i - gCameraNavSubIndex) * 0x14) + 0x36,
                          gStagePanelLabelStrings[i]);
        }

        Text_SetupDL();
        DrawPanelBackground(0x4D, 0x34, 0xA6, 0x88, 0);
    }
}

void RenderGradientPanel(void) {
    s32 sp3C;
    s32 sp38;
    Color_RGB8 sp34 = gStagePanelGradientStartColor;
    Color_RGB8 sp30 = gStagePanelGradientEndColor;

    if (gStagePanelStateIndex >= 3) {
        DrawPanelBackground(0, 0, 0x140, 0xF0, gStagePanelFadeData.unk_04);
    }

    if (gStagePanelStateIndex == 4) {
        if (gStagePanelFadeData.unk_0E < 0x15) {
            DrawGradientPanel(gStagePanelFadeData.unk_08, gStagePanelFadeData.unk_0A - (gStagePanelFadeData.unk_0E / 2), gStagePanelFadeData.unk_0C,
                          gStagePanelFadeData.unk_0E, &sp34, &sp34);
        } else {
            DrawGradientPanel(gStagePanelFadeData.unk_08, gStagePanelFadeData.unk_0A - (gStagePanelFadeData.unk_0E / 2), gStagePanelFadeData.unk_0C,
                          gStagePanelFadeData.unk_0E, &sp34, &sp30);
        }

        if (gStagePanelFadeData.unk_0E >= 0x1F) {
            Text_ResetState();
            Text_SetFont(4, 0);
            sp3C = MeasureTextWidth(4, 0, GetMessageString(NULL, 0, gMessageBankPtr, 0));
            sp38 = GetMessageString(NULL, 0, gMessageBankPtr, 0);
            Text_Print((gStagePanelFadeData.unk_08 - (sp3C / 2)) + (gStagePanelFadeData.unk_0C / 2), gStagePanelFadeData.unk_0A - 8, sp38);
            Text_SetupDL();
        }
    }
}

s16 GetUIElementXPosOrMax(s16 arg0) {
    if ((arg0 - gStagePanelAnimState.unk_04) <= (gStagePanelAnimState.unk_0C + 15.0f)) {
        return 1000;
    }
    return arg0 - gStagePanelAnimState.unk_04;
}

void RenderHPBar(void) {
    s16 sp4E = gStagePanelAnimState.unk_0C;
    char sp40[12];
    char sp34[12];
    s16 sp32;
    s16 sp24 = sp4E + 0x17;

    if (gStagePanelStateIndex >= 2) {
        return;
    }

    DrawTexture2Cycle(D_5000BA0, GetUIElementXPosOrMax(sp24 + 8), 0x18, 8, 0x1E);
    DrawTexture2Cycle(D_5000BA0, GetUIElementXPosOrMax(sp24 + 0x10), 0x18, 8, 0x1E);

    if (gStagePanelStateIndex == 0) {
        if (gStagePanelAnimState.unk_00 == 0) {
            sprintf(&sp40, "%d", 0x18 - gStageSnapshotCount);

            Text_ResetState();
            Text_SetFont(2, 0);

            if ((0x18 - gStageSnapshotCount) >= 0xB) {
                Text_SetEnvColor(0xFF, 0xFF, 0xFF, 0xFF);
            } else {
                Text_SetEnvColor(0xFF, 0, 0, 0xFF);
            }

            sp32 = 0;
            if ((0x18 - gStageSnapshotCount) < 0xA) {
                sp32 = 3;
            }

            Text_Print(sp24 + sp32 + 9, 0x21, &sp40);
            Text_SetupDL();
        } else {
            sprintf(&sp40, "%d", 0x19 - gStageSnapshotCount);
            sprintf(&sp34, "%d", 0x18 - gStageSnapshotCount);

            Text_ResetState();
            Text_SetFont(2, 0);

            if ((0x19 - gStageSnapshotCount) >= 0xB) {
                Text_SetEnvColor(0xFF, 0xFF, 0xFF, 0xFF);
            } else {
                Text_SetEnvColor(0xFF, 0, 0, 0xFF);
            }

            sp32 = 0;
            if ((0x18 - gStageSnapshotCount) < 0xA) {
                sp32 = 3;
            }

            Text_Print((sp24 - gStagePanelAnimState.unk_00) + sp32 + 0x1D, 0x21, &sp40);

            if ((0x18 - gStageSnapshotCount) >= 0xB) {
                Text_SetEnvColor(0xFF, 0xFF, 0xFF, 0xFF);
            } else {
                Text_SetEnvColor(0xFF, 0, 0, 0xFF);
            }

            sp32 = 0;
            if ((0x18 - gStageSnapshotCount) < 0xA) {
                sp32 = 3;
            }

            Text_Print((sp24 - gStagePanelAnimState.unk_00) + sp32 + 9, 0x21, &sp34);
            Text_SetupDL();
        }
    } else if (gStagePanelAnimState.unk_00 == 0) {
        if (gStageSnapshotCount != 0) {
            sprintf(&sp40, "%d", 0x18 - gStageSnapshotCount);

            Text_ResetState();
            Text_SetFont(2, 0);

            if ((0x18 - gStageSnapshotCount) >= 0xB) {
                Text_SetEnvColor(0xFF, 0xFF, 0xFF, 0xFF);
            } else {
                Text_SetEnvColor(0xFF, 0, 0, 0xFF);
            }

            sp32 = 0;
            if ((0x18 - gStageSnapshotCount) < 0xA) {
                sp32 = 3;
            }

            Text_Print(sp24 + sp32 + 9, 0x21, &sp40);
            Text_SetupDL();
        }
    } else {
        sprintf(&sp40, "%d", 0x17 - gStageSnapshotCount);
        sprintf(&sp34, "%d", 0x18 - gStageSnapshotCount);

        Text_ResetState();
        Text_SetFont(2, 0);

        if ((0x19 - gStageSnapshotCount) >= 0xB) {
            Text_SetEnvColor(0xFF, 0xFF, 0xFF, 0xFF);
        } else {
            Text_SetEnvColor(0xFF, 0, 0, 0xFF);
        }

        sp32 = 0;
        if ((0x18 - gStageSnapshotCount) < 0xA) {
            sp32 = 3;
        }

        Text_Print((sp24 + gStagePanelAnimState.unk_00 + sp32) - 0xB, 0x21, &sp40);

        if ((0x18 - gStageSnapshotCount) >= 0xB) {
            Text_SetEnvColor(0xFF, 0xFF, 0xFF, 0xFF);
        } else {
            Text_SetEnvColor(0xFF, 0, 0, 0xFF);
        }

        sp32 = 0;
        if ((0x18 - gStageSnapshotCount) < 0xA) {
            sp32 = 3;
        }

        Text_Print(sp24 + gStagePanelAnimState.unk_00 + sp32 + 9, 0x21, &sp34);
        Text_SetupDL();
    }

    DrawSpriteRotated(D_50003F0, sp4E, 0x13, 0x18, 0x29);
    DrawTexture2Cycle(D_5000BA0, GetUIElementXPosOrMax(sp24), 0x18, 8, 0x1E);
    DrawTexture2Cycle(D_5000BA0, GetUIElementXPosOrMax(sp24 + 0x18), 0x18, 8, 0x1E);
    DrawTexture2Cycle(D_5000BA0, GetUIElementXPosOrMax(sp24 + 0x20), 0x18, 8, 0x1E);
    DrawTexture2Cycle(D_5000BA0, GetUIElementXPosOrMax(sp24 + 0x28), 0x18, 8, 0x1E);
}

void Gallery_DrawPhotoCounterReelExit(void) {
    s16 sp30 = gStagePanelAnimState.unk_0C;
    s16 sp2E;

    if (gStagePanelStateIndex < 2) {
        return;
    }

    sp2E = sp30 + 0x17;

    if (GetUIElementXPosOrMax(sp2E + 0) != 0x3E8) {
        DrawTexture2Cycle(D_5000BA0, GetUIElementXPosOrMax(sp2E + 0), 0x18, 8, 0x1E);
    }

    if (GetUIElementXPosOrMax(sp2E + 8) != 0x3E8) {
        DrawTexture2Cycle(D_5000BA0, GetUIElementXPosOrMax(sp2E + 8), 0x18, 8, 0x1E);
    }

    if (GetUIElementXPosOrMax(sp2E + 0x10) != 0x3E8) {
        DrawTexture2Cycle(D_5000BA0, GetUIElementXPosOrMax(sp2E + 0x10), 0x18, 8, 0x1E);
    }

    if (GetUIElementXPosOrMax(sp2E + 0x18) != 0x3E8) {
        DrawTexture2Cycle(D_5000BA0, GetUIElementXPosOrMax(sp2E + 0x18), 0x18, 8, 0x1E);
    }

    if (GetUIElementXPosOrMax(sp2E + 0x20) != 0x3E8) {
        DrawTexture2Cycle(D_5000BA0, GetUIElementXPosOrMax(sp2E + 0x20), 0x18, 8, 0x1E);
    }

    if (GetUIElementXPosOrMax(sp2E + 0x28) != 0x3E8) {
        DrawTexture2Cycle(D_5000BA0, GetUIElementXPosOrMax(sp2E + 0x28), 0x18, 8, 0x1E);
    }

    DrawSpriteRotated(D_50003F0, sp30, 0x13, 0x18, 0x29);
}

void Gallery_DrawFrameMarkers(void) {
    if (gStagePanelStateIndex == 0) {
        DrawRotatedSprite(&D_50011D0, gStagePanelAnimData.unk_00[0], gStagePanelAnimData.unk_00[4], 0x30, 0x19, 0, 0);
        DrawRotatedSprite(&D_50011D0, gStagePanelAnimData.unk_00[1], gStagePanelAnimData.unk_00[5], 0x30, 0x19, 0x4000, 1);
        DrawRotatedSprite(&D_50011D0, gStagePanelAnimData.unk_00[2], gStagePanelAnimData.unk_00[6], 0x30, 0x19, -0x8000, 1);
        DrawRotatedSprite(&D_50011D0, gStagePanelAnimData.unk_00[3], gStagePanelAnimData.unk_00[7], 0x30, 0x19, -0x4000, 1);
        DrawRotatedSpriteAlt(&D_5000C90, gStagePanelAnimData.unk_10, gStagePanelAnimData.unk_20, 0x18, 0x38, 0, 0);
        DrawRotatedSpriteOffset(&D_5000C90, gStagePanelAnimData.unk_10, gStagePanelAnimData.unk_20, 0x18, 0x38, 0, 1);
        DrawRotatedSpriteAlt(&D_5000C90, gStagePanelAnimData.unk_14, gStagePanelAnimData.unk_24, 0x18, 0x38, 0x4000, 1);
        DrawRotatedSpriteOffset(&D_5000C90, gStagePanelAnimData.unk_14, gStagePanelAnimData.unk_24, 0x18, 0x38, 0x4000, 1);
        DrawRotatedSpriteAlt(&D_5000C90, gStagePanelAnimData.unk_18, gStagePanelAnimData.unk_28, 0x18, 0x38, -0x8000, 1);
        DrawRotatedSpriteOffset(&D_5000C90, gStagePanelAnimData.unk_18, gStagePanelAnimData.unk_28, 0x18, 0x38, -0x8000, 1);
        DrawRotatedSpriteAlt(&D_5000C90, gStagePanelAnimData.unk_1C, gStagePanelAnimData.unk_2C, 0x18, 0x38, -0x4000, 1);
        DrawRotatedSpriteOffset(&D_5000C90, gStagePanelAnimData.unk_1C, gStagePanelAnimData.unk_2C, 0x18, 0x38, -0x4000, 1);
    }
}

void Gallery_DrawTutorialTextBox(void) {
    if (gTutorialTextBoxState.unk_00 != 0xFF) {
        DrawBorderedRect(0x3C, 0x9B - (gTutorialTextBoxState.unk_0C / 2), gTutorialTextBoxState.unk_08, gTutorialTextBoxState.unk_0C, 0, 0, 0x9B, 0x7D);
        Text_ResetState();
        Text_SetFont(2, 0);
        Text_SetLineHeight(0xC);
        Text_Print(0x46, 0x9F - (gTutorialTextBoxState.unk_0C / 2), gTutorialTextBoxCharBuffer);
        Text_SetupDL();
    }
}
