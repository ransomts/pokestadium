#include "cup_select.h"
#include "src/geo_render.h"
#include "src/model_renderer.h"
#include "src/graphics_textures.h"
#include "src/input.h"
#include "src/save_data.h"
#include "src/3FB0.h"
#include "src/audio_sfx.h"
#include "src/matrix.h"
#include "src/controller.h"
#include "src/geo_layout.h"
#include "src/memmap.h"
#include "src/memory.h"
#include "src/stage_loader.h"

static BinArchive* gCupSelectBgArchive;
static void* gBackgroundTextureAtlas;
static GraphNode* gBackgroundGraphNode;
static GraphNode* gOverlayGraphNode;
static GraphNode* gUIGraphNode;
static Fragment2_1GraphNode gCupSelectEvenRowNodes[4];
static Fragment2_1GraphNode gCupSelectOddRowNodes[3];
static SessionModeSettings gCupSelectModeSettings;
static s16 gCupSelectCursor;
static s16 gCupSelectMaxIndex;

static u32 gCupSelectBgGeo[] = {
    0x0C000000, 0x05000000, 0x0B00002D,  0x00000000, 0x028001E0, 0x00000000, 0xFDBD0000, 0x00000243,
    0x05000000, 0x0D000000, 0x05000000,  0x14000000, 0x00000000, 0xFFFFFF32, 0x16FFFFFF, 0x0F000002,
    0x05000000, 0x0A000000, &gGraphRoot0, 0x06000000, 0x06000000, 0x06000000, 0x06000000, 0x01000000,
};
static u8* gCupSelectBgTextures[] = { D_3000000, D_3009000, D_3012000, D_301B000 };
static Vtx gCupSelectVtx_0[] = {
    VTX(-128, 36, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(-128, 12, 0, 0, 768, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(-64, 12, 0, 2048, 768, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(-64, 36, 0, 2048, 0, 0xFF, 0xFF, 0xFF, 0xFF),
};
static Vtx gCupSelectVtx_1[] = {
    VTX(-64, 36, 0, 2048, 0, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(-64, 12, 0, 2048, 768, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(0, 12, 0, 4096, 768, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(0, 36, 0, 4096, 0, 0xFF, 0xFF, 0xFF, 0xFF),
};
static Vtx gCupSelectVtx_2[] = {
    VTX(0, 36, 0, 4096, 0, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(0, 12, 0, 4096, 768, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(64, 12, 0, 6144, 768, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(64, 36, 0, 6144, 0, 0xFF, 0xFF, 0xFF, 0xFF),
};
static Vtx gCupSelectVtx_3[] = {
    VTX(64, 36, 0, 6144, 0, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(64, 12, 0, 6144, 768, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(128, 12, 0, 8192, 768, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(128, 36, 0, 8192, 0, 0xFF, 0xFF, 0xFF, 0xFF),
};
static Vtx gCupSelectVtx_4[] = {
    VTX(-128, 12, 0, 0, 768, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(-128, -12, 0, 0, 1536, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(-64, -12, 0, 2048, 1536, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(-64, 12, 0, 2048, 768, 0xFF, 0xFF, 0xFF, 0xFF),
};
static Vtx gCupSelectVtx_5[] = {
    VTX(-64, 12, 0, 2048, 768, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(-64, -12, 0, 2048, 1536, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(0, -12, 0, 4096, 1536, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(0, 12, 0, 4096, 768, 0xFF, 0xFF, 0xFF, 0xFF),
};
static Vtx gCupSelectVtx_6[] = {
    VTX(0, 12, 0, 4096, 768, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(0, -12, 0, 4096, 1536, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(64, -12, 0, 6144, 1536, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(64, 12, 0, 6144, 768, 0xFF, 0xFF, 0xFF, 0xFF),
};
static Vtx gCupSelectVtx_7[] = {
    VTX(64, 12, 0, 6144, 768, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(64, -12, 0, 6144, 1536, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(128, -12, 0, 8192, 1536, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(128, 12, 0, 8192, 768, 0xFF, 0xFF, 0xFF, 0xFF),
};
static Vtx gCupSelectVtx_8[] = {
    VTX(-128, -12, 0, 0, 1536, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(-128, -36, 0, 0, 2304, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(-64, -36, 0, 2048, 2304, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(-64, -12, 0, 2048, 1536, 0xFF, 0xFF, 0xFF, 0xFF),
};
static Vtx gCupSelectVtx_9[] = {
    VTX(-64, -12, 0, 2048, 1536, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(-64, -36, 0, 2048, 2304, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(0, -36, 0, 4096, 2304, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(0, -12, 0, 4096, 1536, 0xFF, 0xFF, 0xFF, 0xFF),
};
static Vtx gCupSelectVtx_10[] = {
    VTX(0, -12, 0, 4096, 1536, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(0, -36, 0, 4096, 2304, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(64, -36, 0, 6144, 2304, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(64, -12, 0, 6144, 1536, 0xFF, 0xFF, 0xFF, 0xFF),
};
static Vtx gCupSelectVtx_11[] = {
    VTX(64, -12, 0, 6144, 1536, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(64, -36, 0, 6144, 2304, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(128, -36, 0, 8192, 2304, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(128, -12, 0, 8192, 1536, 0xFF, 0xFF, 0xFF, 0xFF),
};
static Gfx gCupSelectBgDL[] = {
    gsSPSetGeometryMode(G_CULL_BACK),
    gsDPSetCombineLERP(0, 0, 0, TEXEL0, TEXEL0, 0, ENVIRONMENT, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPLoadTextureTile(0x0F000000, G_IM_FMT_RGBA, G_IM_SIZ_16b, 256, 0, 0, 0, 63, 23, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(gCupSelectVtx_0, 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsDPLoadTextureTile(0x0F000000, G_IM_FMT_RGBA, G_IM_SIZ_16b, 256, 0, 64, 0, 127, 23, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(gCupSelectVtx_1, 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsDPLoadTextureTile(0x0F000000, G_IM_FMT_RGBA, G_IM_SIZ_16b, 256, 0, 128, 0, 191, 23, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(gCupSelectVtx_2, 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsDPLoadTextureTile(0x0F000000, G_IM_FMT_RGBA, G_IM_SIZ_16b, 256, 0, 192, 0, 255, 23, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(gCupSelectVtx_3, 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsDPLoadTextureTile(0x0F000000, G_IM_FMT_RGBA, G_IM_SIZ_16b, 256, 0, 0, 24, 63, 47, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(gCupSelectVtx_4, 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsDPLoadTextureTile(0x0F000000, G_IM_FMT_RGBA, G_IM_SIZ_16b, 256, 0, 64, 24, 127, 47, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(gCupSelectVtx_5, 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsDPLoadTextureTile(0x0F000000, G_IM_FMT_RGBA, G_IM_SIZ_16b, 256, 0, 128, 24, 191, 47, 0,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                        G_TX_NOLOD),
    gsSPVertex(gCupSelectVtx_6, 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsDPLoadTextureTile(0x0F000000, G_IM_FMT_RGBA, G_IM_SIZ_16b, 256, 0, 192, 24, 255, 47, 0,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                        G_TX_NOLOD),
    gsSPVertex(gCupSelectVtx_7, 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsDPLoadTextureTile(0x0F000000, G_IM_FMT_RGBA, G_IM_SIZ_16b, 256, 0, 0, 48, 63, 71, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(gCupSelectVtx_8, 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsDPLoadTextureTile(0x0F000000, G_IM_FMT_RGBA, G_IM_SIZ_16b, 256, 0, 64, 48, 127, 71, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(gCupSelectVtx_9, 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsDPLoadTextureTile(0x0F000000, G_IM_FMT_RGBA, G_IM_SIZ_16b, 256, 0, 128, 48, 191, 71, 0,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                        G_TX_NOLOD),
    gsSPVertex(gCupSelectVtx_10, 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsDPLoadTextureTile(0x0F000000, G_IM_FMT_RGBA, G_IM_SIZ_16b, 256, 0, 192, 48, 255, 71, 0,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                        G_TX_NOLOD),
    gsSPVertex(gCupSelectVtx_11, 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSPEndDisplayList(),
};
static u32 gCupSelectOverlayGeo[] = {
    0x17000000, 0x00000000, 0x00000000,    0x00000000, gCupSelectVtx_0, 0x05000000, 0x22050000,
    0x00000000, 0x08000000, CupSelect_IconGeoPostCallback, 0x00000000, 0x06000000, 0x01000000, 0x00000000,
};
static Vtx gCupSelectOverlayVtx[] = {
    VTX(-38, 18, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF),      VTX(-38, 0, 0, 0, 576, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(38, 0, 0, 2432, 576, 0xFF, 0xFF, 0xFF, 0xFF),   VTX(38, 18, 0, 2432, 0, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(-38, 0, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF),       VTX(-38, -18, 0, 0, 576, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(38, -18, 0, 2432, 576, 0xFF, 0xFF, 0xFF, 0xFF), VTX(38, 0, 0, 2432, 0, 0xFF, 0xFF, 0xFF, 0xFF),
};
static Gfx gCupSelectOverlayDL[] = {
    gsSPSetGeometryMode(G_CULL_BACK),
    gsDPSetCombineLERP(0, 0, 0, TEXEL0, TEXEL0, 0, ENVIRONMENT, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsSPVertex(gCupSelectOverlayVtx, 8, 0),
    gsDPLoadTextureBlock(0x0F000000, G_IM_FMT_RGBA, G_IM_SIZ_16b, 76, 18, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                         G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsDPLoadTextureBlock(0x0F000AB0, G_IM_FMT_RGBA, G_IM_SIZ_16b, 76, 18, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                         G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP2Triangles(4, 5, 6, 0, 4, 6, 7, 0),
    gsSPEndDisplayList(),
};
static u32 gCupSelectUiGeo[] = {
    0x17000000, 0x00000000, 0x00000000,    0x00000000, gCupSelectOverlayVtx, 0x05000000, 0x22050000,
    0x00000000, 0x08000000, CupSelect_DividerGeoPostCallback, 0x00000000, 0x06000000, 0x01000000,
};

void CupSelect_PollController(void) {
    Cont_StartReadInputs();
    Cont_ReadInputs();
    Input_ResetRepeatState();
}

void CupSelect_EmptyFunc(void) {
}

void CupSelect_DrawSelectionCorners(s16 arg0, s16 arg1, s16 arg2, s16 arg3, u8 arg4, u8 arg5, u8 arg6, u8 arg7) {
    static s16 gBorderCornerAnimTimer = 0;

    s16 sp56 = SINS(gBorderCornerAnimTimer) * 2;
    UNUSED s32 pad[2];

    gSPDisplayList(gDisplayListHead++, gPrefDL_Border);
    gDPSetEnvColor(gDisplayListHead++, arg4, arg5, arg6, arg7);

    Gfx_DrawTextureIa8((arg0 + sp56) - 8, (arg1 + sp56) - 8, 0x10, 0x10, D_2000C80, 0x10, 0);
    Gfx_DrawTextureIa8((arg0 + sp56) - 8, ((arg1 + arg3) - sp56) - 8, 0x10, 0x10, D_2000F80, 0x10, 0);
    Gfx_DrawTextureIa8(((arg0 + arg2) - sp56) - 8, (arg1 + sp56) - 8, 0x10, 0x10, D_2000D80, 0x10, 0);
    Gfx_DrawTextureIa8(((arg0 + arg2) - sp56) - 8, ((arg1 + arg3) - sp56) - 8, 0x10, 0x10, D_2000E80, 0x10, 0);

    gSPDisplayList(gDisplayListHead++, gPrefDL_End);

    gBorderCornerAnimTimer += 0x2000;
}

s32 CupSelect_IconGeoPostCallback(s32 arg0, SimpleGfxNode* arg1) {
    s32 temp_a3;
    s32 var_t0;

    if (arg0 == 5) {
        temp_a3 = gDefaultGraphRoot->unk_000.unk_14;
        if (gCupSelectMaxIndex >= temp_a3) {
            var_t0 = 0xFF;
        } else {
            var_t0 = 0x80;
        }

        gDPPipeSync(gDisplayListHead++);
        gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, var_t0);
        gSPSegment(gDisplayListHead++, 0x0F, Memmap_GetSegmentVaddr(gCupSelectBgTextures[temp_a3]));
        gSPDisplayList(gDisplayListHead++, gCupSelectBgDL);

        GeoRender_ApplyMaterialState();
    }
    return 0;
}

s32 CupSelect_DividerGeoPostCallback(s32 arg0, SimpleGfxNode* arg1) {
    s32 var_a3;

    if (arg0 == 5) {
        s32 tmp = gDefaultGraphRoot->unk_000.unk_14;

        if (tmp < gCupSelectMaxIndex) {
            var_a3 = 0xFF;
        } else {
            var_a3 = 0x80;
        }

        gDPPipeSync(gDisplayListHead++);
        gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, var_a3);
        gSPSegment(gDisplayListHead++, 0x0F, Memmap_GetSegmentVaddr(D_3024000));
        gSPDisplayList(gDisplayListHead++, gCupSelectOverlayDL);

        GeoRender_ApplyMaterialState();
    }
    return 0;
}

void CupSelect_RenderFrame(s32 arg0, s32 arg1) {
    BgStage_DrawFrame();
    Gfx_DrawTiledRgba16Image(gBackgroundTextureAtlas);
    Geo_RenderRootNode(gBackgroundGraphNode);

    if (arg0 == 0) {
        if ((arg1 >= 0) && (arg1 < 0xB)) {
            gCupSelectEvenRowNodes[0].unk_01E.y = ((0xA - arg1) * -0x5000) / 10;
        }

        if ((arg1 >= 2) && (arg1 < 0xD)) {
            gCupSelectOddRowNodes[0].unk_01E.y = ((0xC - arg1) * -0x5000) / 10;
        }

        if ((arg1 >= 4) && (arg1 < 0xF)) {
            gCupSelectEvenRowNodes[1].unk_01E.y = ((0xE - arg1) * -0x5000) / 10;
        }

        if ((arg1 >= 6) && (arg1 < 0x11)) {
            gCupSelectOddRowNodes[1].unk_01E.y = ((0x10 - arg1) * -0x5000) / 10;
        }

        if ((arg1 >= 8) && (arg1 < 0x13)) {
            gCupSelectEvenRowNodes[2].unk_01E.y = ((0x12 - arg1) * -0x5000) / 10;
        }

        if ((arg1 >= 0xA) && (arg1 < 0x15)) {
            gCupSelectOddRowNodes[2].unk_01E.y = ((0x14 - arg1) * -0x5000) / 10;
        }

        if ((arg1 >= 0xC) && (arg1 < 0x17)) {
            gCupSelectEvenRowNodes[3].unk_01E.y = ((0x16 - arg1) * -0x5000) / 10;
        }
    }

    if (arg0 == 2) {
        if ((arg1 >= 0) && (arg1 < 0xB)) {
            gCupSelectEvenRowNodes[0].unk_01E.y = ((arg1 - 0) * 0x5000) / 10;
        }

        if ((arg1 >= 2) && (arg1 < 0xD)) {
            gCupSelectOddRowNodes[0].unk_01E.y = (((arg1 - 0x2) * 0x5000)) / 10;
        }

        if ((arg1 >= 4) && (arg1 < 0xF)) {
            gCupSelectEvenRowNodes[1].unk_01E.y = (((arg1 - 0x4) * 0x5000)) / 10;
        }

        if ((arg1 >= 6) && (arg1 < 0x11)) {
            gCupSelectOddRowNodes[1].unk_01E.y = (((arg1 - 0x6) * 0x5000)) / 10;
        }

        if ((arg1 >= 8) && (arg1 < 0x13)) {
            gCupSelectEvenRowNodes[2].unk_01E.y = (((arg1 - 0x8) * 0x5000)) / 10;
        }

        if ((arg1 >= 0xA) && (arg1 < 0x15)) {
            gCupSelectOddRowNodes[2].unk_01E.y = (((arg1 - 0xA) * 0x5000)) / 10;
        }

        if ((arg1 >= 0xC) && (arg1 < 0x17)) {
            gCupSelectEvenRowNodes[3].unk_01E.y = (((arg1 - 0xC) * 0x5000)) / 10;
        }
    }

    if (arg0 == 1) {
        CupSelect_DrawSelectionCorners(0xD0, (gCupSelectCursor * 0x6C) + 0x32, 0xE0, 0x38, 0xFF, 0xF0, 0x64, 0xFF);
    }
    BgStage_AdvanceFrame();
}

void CupSelect_BuildDivisionList(void) {
    s32 i;
    Fragment2_1GraphNode* var_s1;
    Fragment2_1GraphNode* var_s2;

    for (var_s1 = &gCupSelectEvenRowNodes[0], i = 0; i < 4; i++, var_s1++) {
        Model_InitDisplayObject(var_s1, 0, 0, gOverlayGraphNode);
        gCupSelectEvenRowNodes[i].unk_01E.y = -0x5000;
    }

    Vec3f_SetComponentsDuplicate(&gCupSelectEvenRowNodes[0].unk_024, 0.0f, 162.0f, -579.0f);
    Vec3f_SetComponentsDuplicate(&gCupSelectEvenRowNodes[1].unk_024, 0.0f, 54.0f, -579.0f);
    Vec3f_SetComponentsDuplicate(&gCupSelectEvenRowNodes[2].unk_024, 0.0f, -54.0f, -579.0f);
    Vec3f_SetComponentsDuplicate(&gCupSelectEvenRowNodes[3].unk_024, 0.0f, -162.0f, -579.0f);

    for (var_s2 = &gCupSelectOddRowNodes[0], i = 0; i < 3; i++, var_s2++) {
        Model_InitDisplayObject(var_s2, 0, 0, gUIGraphNode);
        gCupSelectOddRowNodes[i].unk_01E.y = -0x5000;
    }

    Vec3f_SetComponentsDuplicate(&gCupSelectOddRowNodes[0].unk_024, 0.0f, 108.0f, -579.0f);
    Vec3f_SetComponentsDuplicate(&gCupSelectOddRowNodes[1].unk_024, 0.0f, 0, -579.0f);
    Vec3f_SetComponentsDuplicate(&gCupSelectOddRowNodes[2].unk_024, 0.0f, -108.0f, -579.0f);
}

s32 CupSelect_HandleInput(void) {
    s32 var_v1 = 'exec';

    if (BTN_IS_PRESSED(gPlayer1Controller, BTN_A)) {
        Audio_PlaySoundEffectById(0x26);
        gSessionContext.unk_0002 = gCupSelectCursor;
        var_v1 = 'slct';
    } else if (BTN_IS_PRESSED(gPlayer1Controller, BTN_B)) {
        Audio_PlaySoundEffectById(3);
        var_v1 = 'quit';
    } else if (BTN_IS_PRESSED(gPlayer1Controller, BTN_DUP)) {
        if (gCupSelectCursor > 0) {
            Audio_PlaySoundEffectById(1);
            gCupSelectCursor--;
        }
    } else if (BTN_IS_PRESSED(gPlayer1Controller, BTN_DDOWN) && (gCupSelectCursor < gCupSelectMaxIndex)) {
        Audio_PlaySoundEffectById(1);
        gCupSelectCursor++;
    }
    return var_v1;
}

s32 CupSelect_Loop(void) {
    s16 i;
    s32 temp_v0 = 'exec';
    s32 temp_v1;

    CupSelect_BuildDivisionList();
    gCupSelectCursor = gCupSelectMaxIndex;

    for (i = 0; i < 23; i++) {
        CupSelect_PollController();
        CupSelect_RenderFrame(0, i);
    }

    while (temp_v0 == 'exec') {
        CupSelect_PollController();
        CupSelect_RenderFrame(1, 0);
        temp_v0 = CupSelect_HandleInput();
    }

    temp_v1 = temp_v0 == 'slct';
    if (temp_v1) {
        for (i = 0; i < 23; i++) {
            CupSelect_PollController();
            CupSelect_RenderFrame(2, i);
        }
    } else {
        StageContext_SetClearColor(0xFFFF);
        StageFade_StartFromTransparent(8);
        while (StageContext_GetFadeMode() != 1) {
            CupSelect_PollController();
            CupSelect_RenderFrame(1, 0);
        }
        StageLoader_RunFrames(2);
    }
    return temp_v1;
}

void CupSelect_InitGeoLayouts(void) {
    MemoryBlock* temp_v0 = MainPool_AllocState(main_pool_get_available(), 0);
    s32 i;
    Fragment2_1GraphNode* var_s2;

    gBackgroundGraphNode = process_geo_layout(temp_v0, &gCupSelectBgGeo);
    gOverlayGraphNode = process_geo_layout(temp_v0, &gCupSelectOverlayGeo);
    gUIGraphNode = process_geo_layout(temp_v0, &gCupSelectUiGeo);
    MainPool_FinalizeAllocation(temp_v0);
    ModelRenderer_InitDisplayRoots();

    for (var_s2 = &gCupSelectEvenRowNodes[0], i = 0; i < 4; var_s2++, i++) {
        ModelRenderer_AttachDisplayObject(var_s2);
        gCupSelectEvenRowNodes[i].unk_000.unk_14 = i;
    }

    for (var_s2 = &gCupSelectOddRowNodes[0], i = 0; i < 3; var_s2++, i++) {
        ModelRenderer_AttachDisplayObject(var_s2);
        gCupSelectOddRowNodes[i].unk_000.unk_14 = i;
    }
}

s32 CupSelect_Main(UNUSED s32 arg0, UNUSED s32 arg1) {
    s16 var_v1 = -1;
    s32 sp18 = 1;

    switch (gSessionContext.unk_0000) {
        case 3:
            var_v1 = 9;
            break;

        case 6:
            var_v1 = 0xC;
            break;
    }

    if (var_v1 != -1) {
        main_pool_push_state('LVSL');

        Font_Init(0x10, 0);
        Save_EnsureBankLoaded(2);
        Save_GetModeSettings(&gCupSelectModeSettings, gSessionContext.inRound2);
        if (gSessionContext.unk_0000 == 3) {
            gCupSelectMaxIndex = gCupSelectModeSettings.unk_05;
        } else {
            gCupSelectMaxIndex = gCupSelectModeSettings.unk_06;
        }
        if (gCupSelectMaxIndex == 4) {
            gCupSelectMaxIndex -= 1;
        }

        ASSET_LOAD(D_1000000, common_menu1_ui, 0);
        ASSET_LOAD(D_2000000, common_menu2_ui, 0);
        ASSET_LOAD(D_3000000, cup_ball_select_ui, 0);

        gCupSelectBgArchive = ASSET_LOAD2(backgrounds, 1, 1);
        gBackgroundTextureAtlas = BinArchive_GetFile(gCupSelectBgArchive, var_v1);

        CupSelect_InitGeoLayouts();
        StageLoader_UpdateSegments();
        sp18 = CupSelect_Loop();
        StageLoader_WaitForRetrace();

        main_pool_pop_state('LVSL');
    }
    return sp18;
}
