#include "fragment34.h"

static Gfx gDL_Default3DState[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_2CYCLE),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTextureConvert(G_TC_FILT),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_PASS2),
    gsDPSetCombineKey(G_CK_NONE),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPSetRenderMode(G_RM_OPA_SURF, G_RM_OPA_SURF2),
    gsDPNoOp(),
    gsSPSetGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK),
    gsSPClearGeometryMode(G_FOG | G_LIGHTING),
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsSPEndDisplayList(),
};

Gfx gDL_End3D[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_2CYCLE),
    gsDPSetColorDither(G_CD_MAGICSQ),
    gsDPSetAlphaDither(G_AD_PATTERN),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPSetTextureLUT(G_TT_NONE),
    gsSPSetGeometryMode(G_SHADE | G_CULL_BACK),
    gsSPEndDisplayList(),
};

Gfx gDL_Begin3D[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_2CYCLE),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_OFF),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsSPSetGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK),
    gsSPClearGeometryMode(G_FOG | G_LIGHTING),
    gsSPEndDisplayList(),
};

static Gfx gDL_TextureBasicState[] = {
    gsDPPipeSync(),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTextureLUT(G_TT_NONE),
    gsSPEndDisplayList(),
};

Gfx gDL_ItemIcon[] = {
    gsSPDisplayList(gDL_TextureBasicState),
    gsDPSetRenderMode(G_RM_PASS, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineMode(G_CC_MODULATEIA, G_CC_PASS2),
    gsSPSetGeometryMode(G_SHADE | G_CULL_BACK | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};

static Gfx gDL_UI_DecalState[] = {
    gsDPPipeSync(),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_PASS2),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsSPEndDisplayList(),
};

Gfx gDL_BaseUI2[] = {
    gsSPDisplayList(gDL_UI_DecalState),
    gsDPSetRenderMode(G_RM_PASS, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsSPEndDisplayList(),
};

static Gfx gDL_UI_ModulateState[] = {
    gsDPPipeSync(),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPSetCombineMode(G_CC_MODULATEIA, G_CC_PASS2),
    gsSPClearGeometryMode(G_LIGHTING),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsSPEndDisplayList(),
};

Gfx D_8140DC58[] = {
    gsSPDisplayList(gDL_UI_ModulateState),
    gsDPSetTextureFilter(G_TF_POINT),
    gsDPSetRenderMode(G_RM_PASS, G_RM_XLU_SURF2),
    gsSPEndDisplayList(),
};

Gfx gDL_OverlayUI2[] = {
    gsSPDisplayList(gDL_UI_ModulateState),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetRenderMode(G_RM_PASS, G_RM_XLU_SURF2),
    gsSPEndDisplayList(),
};

Gfx D_8140DC98[] = {
    gsSPDisplayList(gDL_UI_ModulateState),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetRenderMode(G_RM_PASS, G_RM_CLD_SURF2),
    gsSPEndDisplayList(),
};

Gfx D_8140DCB8[] = {
    gsSPDisplayList(gDL_UI_ModulateState),
    gsDPSetTextureFilter(G_TF_POINT),
    gsDPSetRenderMode(G_RM_PASS, G_RM_AA_XLU_SURF2),
    gsSPEndDisplayList(),
};

Gfx gDL_BaseUI[] = {
    gsSPDisplayList(gDL_UI_ModulateState),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetRenderMode(G_RM_PASS, G_RM_AA_XLU_SURF2),
    gsSPEndDisplayList(),
};

Gfx D_8140DCF8[] = {
    gsSPDisplayList(gDL_UI_ModulateState),
    gsDPSetTextureFilter(G_TF_POINT),
    gsDPSetRenderMode(G_RM_PASS, G_RM_ZB_XLU_SURF2),
    gsSPEndDisplayList(),
};

Gfx D_8140DD18[] = {
    gsSPDisplayList(gDL_UI_ModulateState),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetRenderMode(G_RM_PASS, G_RM_ZB_XLU_SURF2),
    gsSPEndDisplayList(),
};

Gfx D_8140DD38[] = {
    gsSPDisplayList(gDL_UI_ModulateState),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetRenderMode(G_RM_PASS, G_RM_ZB_CLD_SURF2),
    gsSPEndDisplayList(),
};

Gfx gDL_OverlayUI[] = {
    gsSPDisplayList(gDL_UI_ModulateState),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetRenderMode(G_RM_PASS, G_RM_AA_ZB_XLU_SURF2),
    gsSPEndDisplayList(),
};

Gfx gDL_BeginUIOverlay[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_2CYCLE),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPSetTexturePersp(G_TP_NONE),
    gsDPSetRenderMode(G_RM_NOOP, G_RM_NOOP2),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPSetColorDither(G_CD_DISABLE),
    gsDPSetAlphaDither(G_AD_DISABLE),
    gsDPSetTextureFilter(G_TF_POINT),
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_OFF),
    gsSPClearGeometryMode(G_CULL_BACK),
    gsSPEndDisplayList(),
};

Gfx gDL_EndColorFill[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_2CYCLE),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsSPEndDisplayList(),
};

Gfx gDL_BeginColorFill[] = {
    gsDPPipeSync(),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPSetTexturePersp(G_TP_NONE),
    gsDPSetCombineMode(G_CC_PRIMITIVE, G_CC_PASS2),
    gsDPSetRenderMode(G_RM_PASS, G_RM_AA_XLU_SURF2),
    gsDPSetTextureFilter(G_TF_POINT),
    gsSPEndDisplayList(),
};

static Gfx gDL_CycleCopy[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_COPY),
    gsSPEndDisplayList(),
};

static Gfx gDL_Cycle1[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPEndDisplayList(),
};

static Gfx gDL_Cycle2[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_2CYCLE),
    gsSPEndDisplayList(),
};

Vtx gVtx_UI_SmallQuad[] = {
    VTX(-4, -4, 0, 0, 224, 0xFF, 0xFF, 0xFF, 0xFF), VTX(3, -4, 0, 224, 224, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(3, 3, 0, 224, 0, 0xFF, 0xFF, 0xFF, 0xFF),   VTX(-4, 3, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(-4, -8, 0, 0, 480, 0xFF, 0xFF, 0xFF, 0xFF), VTX(3, -8, 0, 224, 480, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(3, 7, 0, 224, 0, 0xFF, 0xFF, 0xFF, 0xFF),   VTX(-4, 7, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF),
};

Vtx gVtx_UI_LargeQuad[] = {
    VTX(-8, -8, 0, 0, 480, 0xFF, 0xFF, 0xFF, 0xFF),   VTX(7, -8, 0, 480, 480, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(7, 7, 0, 480, 0, 0xFF, 0xFF, 0xFF, 0xFF),     VTX(-8, 7, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(-8, -8, 0, 480, 480, 0xFF, 0xFF, 0xFF, 0xFF), VTX(7, -8, 0, 0, 480, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(7, 7, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF),       VTX(-8, 7, 0, 480, 0, 0xFF, 0xFF, 0xFF, 0xFF),
};

Vtx gVtx_UI_TriangleSmall[] = {
    VTX(0, 0, 0, 224, 0, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(7, 255, 0, 480, 8160, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(-8, 255, 0, 0, 8160, 0xFF, 0xFF, 0xFF, 0xFF),
};

Vtx gVtx_UI_TriangleLarge[] = {
    VTX(0, 0, 0, 224, 0, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(31, 255, 0, 480, 8160, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(-32, 255, 0, 0, 8160, 0xFF, 0xFF, 0xFF, 0xFF),
};

Vtx gVtx_UI_MediumQuad[] = {
    VTX(-12, -12, 0, 0, 736, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(11, -12, 0, 736, 736, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(11, 11, 0, 736, 0, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(-12, 11, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF),
};

Vtx gMatrix_UITransform[] = {
    VTX(-16, -16, 0, 0, 992, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(15, -16, 0, 992, 992, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(15, 15, 0, 992, 0, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(-16, 15, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF),
};

Vtx gVtx_UI_RectHorizontal[] = {
    VTX(-16, 0, 0, 0, 992, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(15, 0, 0, 992, 992, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(15, 31, 0, 992, 0, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(-16, 31, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF),
};

Vtx gVtx_UI_RectVertical[] = {
    VTX(0, -16, 0, 0, 992, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(31, -16, 0, 992, 992, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(31, 15, 0, 992, 0, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(0, 15, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF),
};

Vtx gVtx_UI_TriangleDown[] = {
    VTX(0, 18, 0, 480, 0, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(-16, -9, 0, 992, 992, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(16, -9, 0, 0, 992, 0xFF, 0xFF, 0xFF, 0xFF),
};

Vtx gVtx_UI_ColorQuad[] = {
    VTX(-16, -16, 0, 0, 992, 0xFF, 0x00, 0x00, 0xFF),
    VTX(15, -16, 0, 992, 992, 0xFF, 0xFF, 0x00, 0xFF),
    VTX(15, 15, 0, 992, 0, 0x00, 0xFF, 0x00, 0xFF),
    VTX(-16, 15, 0, 0, 0, 0x00, 0xFF, 0xFF, 0xFF),
};

Vtx gVtx_UI_PanelQuad[] = {
    VTX(0, 18, 0, 480, 0, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(-16, -9, 0, 992, 992, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(16, -9, 0, 0, 992, 0xFF, 0xFF, 0xFF, 0xFF),
};

Vtx gVtx_UI_RectTall[] = {
    VTX(-16, -32, 0, 0, 2016, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(15, -32, 0, 992, 2016, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(15, 31, 0, 992, 0, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(-16, 31, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF),
};

Vtx gVtx_UI_RectWide[] = {
    VTX(-16, 0, 0, 0, 2016, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(15, 0, 0, 992, 2016, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(15, 63, 0, 992, 0, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(-16, 63, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF),
};

Vtx gVtx_UI_Square[] = {
    VTX(-16, -16, 0, 0, 2016, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(15, -16, 0, 992, 2016, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(15, 15, 0, 992, 0, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(-16, 15, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF),
};

Vtx gVtx_UI_ComplexQuad[] = {
    VTX(-16, -48, 0, 0, 3040, 0xFF, 0xFF, 0xFF, 0xFF), VTX(15, -48, 0, 992, 3040, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(15, 47, 0, 992, 0, 0xFF, 0xFF, 0xFF, 0xFF),    VTX(-16, 47, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(-32, -16, 0, 0, 992, 0xFF, 0xFF, 0xFF, 0xFF),  VTX(31, -16, 0, 2016, 992, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(31, 15, 0, 2016, 0, 0xFF, 0xFF, 0xFF, 0xFF),   VTX(-32, 15, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF),
};

Vtx gVtx_UI_GridQuad[] = {
    VTX(-32, -32, 0, 0, 2016, 0xFF, 0xFF, 0xFF, 0xFF), VTX(31, -32, 0, 2016, 2016, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(31, 31, 0, 2016, 0, 0xFF, 0xFF, 0xFF, 0xFF),   VTX(-32, 31, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(-32, 0, 0, 0, 992, 0xFF, 0xFF, 0xFF, 0xFF),    VTX(31, 0, 0, 2016, 992, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(31, 31, 0, 2016, 0, 0xFF, 0xFF, 0xFF, 0xFF),   VTX(-32, 31, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(-32, -31, 0, 0, 992, 0xFF, 0xFF, 0xFF, 0xFF),  VTX(31, -31, 0, 2016, 992, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(31, 0, 0, 2016, 0, 0xFF, 0xFF, 0xFF, 0xFF),    VTX(-32, 0, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF),
};

Vtx gGroundQuadVtx[] = {
    VTX(-64, 0, 63, 0, 0, 0x00, 0x00, 0x78, 0xFF),
    VTX(63, 0, 63, 4064, 0, 0x00, 0x00, 0x78, 0xFF),
    VTX(63, 0, -64, 4064, 4064, 0x00, 0x00, 0x78, 0xFF),
    VTX(-64, 0, -64, 0, 4064, 0x00, 0x00, 0x78, 0xFF),
};

Vtx gFullscreenQuadVtx[] = {
    VTX(-160, -120, 0, 0, 1024, 0x00, 0x00, 0x78, 0xFF),
    VTX(160, -120, 0, 1024, 1024, 0x00, 0x00, 0x78, 0xFF),
    VTX(160, 120, 0, 1024, 0, 0x00, 0x00, 0x78, 0xFF),
    VTX(-160, 120, 0, 0, 0, 0x00, 0x00, 0x78, 0xFF),
};

static Gfx gDL_DrawTriangle[] = {
    gsSP1Triangle(0, 1, 2, 0),
    gsSPEndDisplayList(),
};

static Gfx gDL_DrawQuad[] = {
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSPEndDisplayList(),
};

Gfx gDL_PanelBackground[] = {
    gsSPVertex(gVtx_UI_PanelQuad, 4, 0),
    gsSPDisplayList(gDL_DrawTriangle),
    gsSPEndDisplayList(),
};

Gfx gDL_PanelQuad[] = {
    gsSPVertex(gVtx_UI_LargeQuad, 4, 0),
    gsSPDisplayList(gDL_DrawQuad),
    gsSPEndDisplayList(),
};

Gfx gDL_UITransformQuad[] = {
    gsSPVertex(gMatrix_UITransform, 4, 0),
    gsSPDisplayList(gDL_DrawQuad),
    gsSPEndDisplayList(),
};

void Gfx_PipeSync(void) {
    gDPPipeSync(gDisplayListHead++);
}

void Gfx_SetCycle1_NoTexture(void) {
    gDPPipeSync(gDisplayListHead++);
    gDPSetCycleType(gDisplayListHead++, G_CYC_1CYCLE);
    gSPTexture(gDisplayListHead++, 0x0001, 0x0001, 0, G_TX_RENDERTILE, G_OFF);
}

s32 GetLog2(s32 size) {
    s32 size_log2 = 0;

    do {
        size_log2++;
        size /= 2;
    } while (size != 1);

    return size_log2;
}

void ParticleGfx_NoopStub2(void) {
}

void func_814024C8(void) {
}

void func_814024D0(void) {
}

void func_814024D8(void) {
}

void func_814024E0(void) {
}

void func_814024E8(void) {
}

void func_814024F0(void) {
}

void func_814024F8(void) {
}

void Gfx_LoadTextureBlockRGBA32(u8* texture, s32 fmt, s32 width, s32 height, s32 cms, s32 cmt, s32 masks, s32 maskt, s32 shifts,
                   s32 shiftt) {
    gDPLoadTextureBlock(gDisplayListHead++, texture, fmt, G_IM_SIZ_32b, width, height, 0, cms, cmt, masks, maskt,
                        shifts, shiftt);
}

void Gfx_LoadTextureTileRGBA32(u8* texture, s32 fmt, s32 width, s32 height, s32 cms, s32 cmt, s32 masks, s32 maskt, s32 shifts,
                   s32 shiftt) {
    gDPLoadTextureTile(gDisplayListHead++, texture, fmt, G_IM_SIZ_32b, width, 0, 0, 0, width - 1, height - 1, 0, cms,
                       cmt, masks, maskt, shifts, shiftt);
}

void Gfx_LoadTextureBlockRGBA16(u8* texture, s32 fmt, s32 width, s32 height, s32 cms, s32 cmt, s32 masks, s32 maskt, s32 shifts,
                   s32 shiftt) {
    gDPLoadTextureBlock(gDisplayListHead++, texture, fmt, G_IM_SIZ_16b, width, height, 0, cms, cmt, masks, maskt,
                        shifts, shiftt);
}

void Gfx_LoadTextureTileRGBA16(u8* texture, s32 fmt, s32 width, s32 height, s32 cms, s32 cmt, s32 masks, s32 maskt, s32 shifts,
                   s32 shiftt) {
    gDPLoadTextureTile(gDisplayListHead++, texture, fmt, G_IM_SIZ_16b, width, 0, 0, 0, width - 1, height - 1, 0, cms,
                       cmt, masks, maskt, shifts, shiftt);
}

void Gfx_LoadTextureBlockIA8(u8* texture, s32 fmt, s32 width, s32 height, s32 cms, s32 cmt, s32 masks, s32 maskt, s32 shifts,
                   s32 shiftt) {
    gDPLoadTextureBlock(gDisplayListHead++, texture, fmt, G_IM_SIZ_8b, width, height, 0, cms, cmt, masks, maskt, shifts,
                        shiftt);
}

void Gfx_LoadTextureTileIA8(u8* texture, s32 fmt, s32 width, s32 height, s32 cms, s32 cmt, s32 masks, s32 maskt, s32 shifts,
                   s32 shiftt) {
    gDPLoadTextureTile(gDisplayListHead++, texture, fmt, G_IM_SIZ_8b, width, 0, 0, 0, width - 1, height - 1, 0, cms,
                       cmt, masks, maskt, shifts, shiftt);
}

void Gfx_LoadTextureBlock4b(u8* texture, s32 fmt, s32 width, s32 height, s32 cms, s32 cmt, s32 masks, s32 maskt, s32 shifts,
                   s32 shiftt) {
    gDPLoadTextureBlock_4b(gDisplayListHead++, texture, fmt, width, height, 0, cms, cmt, masks, maskt, shifts, shiftt);
}

void Gfx_LoadTextureTile4b(u8* texture, s32 fmt, s32 width, s32 height, s32 cms, s32 cmt, s32 masks, s32 maskt, s32 shifts,
                   s32 shiftt) {
    gDPLoadTextureTile_4b(gDisplayListHead++, texture, fmt, width, 0, 0, 0, width - 1, height - 1, 0, cms, cmt, masks,
                          maskt, shifts, shiftt);
}

void Gfx_LoadMultiBlock4b(u8* texture, s32 tmem, s32 rtile, s32 fmt, s32 width, s32 height, s32 cms, s32 cmt, s32 masks,
                   s32 maskt, s32 shifts, s32 shiftt) {
    gDPLoadMultiBlock_4b(gDisplayListHead++, texture, tmem, rtile, fmt, width, height, 0, cms, cmt, masks, maskt,
                         shifts, shiftt);
}

void Gfx_LoadTextureBlockRGBA32_Clamp(u8* texture, s32 width, s32 height) {
    Gfx_LoadTextureBlockRGBA32(texture, G_IM_FMT_RGBA, width, height, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                  G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
}

void Gfx_LoadTextureTileRGBA32_Clamp(u8* texture, s32 width, s32 height) {
    Gfx_LoadTextureTileRGBA32(texture, G_IM_FMT_RGBA, width, height, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                  G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
}

void Gfx_LoadTextureBlockRGBA16_Clamp(u8* texture, s32 width, s32 height) {
    Gfx_LoadTextureBlockRGBA16(texture, G_IM_FMT_RGBA, width, height, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                  G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
}

void Gfx_LoadMultiTextureRGBA16(u8* texture1, u8* texture2, s32 width, s32 height) {
    gDPLoadMultiTile(gDisplayListHead++, texture1, 0x000, G_TX_RENDERTILE, G_IM_FMT_RGBA, G_IM_SIZ_16b, width, height,
                     0, 0, width - 1, height - 1, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                     G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

    gDPLoadMultiTile(gDisplayListHead++, texture2, 0x100, 1, G_IM_FMT_RGBA, G_IM_SIZ_16b, width, height, 0, 0,
                     width - 1, height - 1, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK,
                     G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
}

void Gfx_LoadTextureBlockRGBA16_MirrorWrapS(u8* texture, s32 width, s32 height) {
    s32 masks = GetLog2(width);

    Gfx_LoadTextureBlockRGBA16(texture, G_IM_FMT_RGBA, width, height, G_TX_MIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_CLAMP, masks,
                  G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
}

void Gfx_LoadTextureBlockRGBA16_MirrorWrapT(u8* texture, s32 width, s32 height) {
    s32 maskt = GetLog2(height);

    Gfx_LoadTextureBlockRGBA16(texture, G_IM_FMT_RGBA, width, height, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_MIRROR | G_TX_WRAP,
                  G_TX_NOMASK, maskt, G_TX_NOLOD, G_TX_NOLOD);
}

void Gfx_LoadTextureBlockRGBA16_MirrorWrapST(u8* texture, s32 width, s32 height) {
    s32 masks = GetLog2(width);
    s32 maskt = GetLog2(height);

    Gfx_LoadTextureBlockRGBA16(texture, G_IM_FMT_RGBA, width, height, G_TX_MIRROR | G_TX_WRAP, G_TX_MIRROR | G_TX_WRAP, masks, maskt,
                  G_TX_NOLOD, G_TX_NOLOD);
}

void Gfx_LoadTextureBlockRGBA16_MaskS(u8* texture, s32 width, s32 height, s32 masks) {
    Gfx_LoadTextureBlockRGBA16(texture, G_IM_FMT_RGBA, width, height, G_TX_MIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_CLAMP, masks,
                  G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
}

void Gfx_LoadTextureTileRGBA16_Clamp(u8* texture, s32 width, s32 height) {
    Gfx_LoadTextureTileRGBA16(texture, G_IM_FMT_RGBA, width, height, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                  G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
}

void Gfx_LoadTextureBlockIA16_Clamp(u8* texture, s32 width, s32 height) {
    Gfx_LoadTextureBlockRGBA16(texture, G_IM_FMT_IA, width, height, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                  G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
}

void Gfx_LoadTextureTileIA16_Clamp(u8* texture, s32 width, s32 height) {
    Gfx_LoadTextureTileRGBA16(texture, G_IM_FMT_IA, width, height, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                  G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
}

void Gfx_LoadTextureBlockIA8_Clamp(u8* texture, s32 width, s32 height) {
    Gfx_LoadTextureBlockIA8(texture, G_IM_FMT_IA, width, height, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                  G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
}

void Gfx_LoadTextureTileIA8_Clamp(u8* texture, s32 width, s32 height) {
    Gfx_LoadTextureTileIA8(texture, G_IM_FMT_IA, width, height, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                  G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
}

void Gfx_LoadTextureBlockIA8_MirrorWrap(u8* texture, s32 width, s32 height) {
    s32 masks = GetLog2(width);
    s32 maskt = GetLog2(height);

    Gfx_LoadTextureBlockIA8(texture, G_IM_FMT_IA, width, height, G_TX_MIRROR | G_TX_WRAP, G_TX_MIRROR | G_TX_WRAP, masks, maskt,
                  G_TX_NOLOD, G_TX_NOLOD);
}

void Gfx_LoadTextureBlockI_Clamp(u8* texture, s32 width, s32 height) {
    Gfx_LoadTextureBlockIA8(texture, G_IM_FMT_I, width, height, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                  G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
}

void Gfx_LoadTextureBlockI_MirrorWrap(u8* texture, s32 width, s32 height) {
    s32 masks = GetLog2(width);
    s32 maskt = GetLog2(height);

    Gfx_LoadTextureBlockIA8(texture, G_IM_FMT_I, width, height, G_TX_MIRROR | G_TX_WRAP, G_TX_MIRROR | G_TX_WRAP, masks, maskt,
                  G_TX_NOLOD, G_TX_NOLOD);
}

void Gfx_LoadTextureTileI_Clamp(u8* texture, s32 width, s32 height) {
    Gfx_LoadTextureTileIA8(texture, G_IM_FMT_I, width, height, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                  G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
}

void Gfx_LoadTextureBlockI_ClampWrapper(u8* texture, s32 width, s32 height) {
    Gfx_LoadTextureBlockI_Clamp(texture, width, height);
}

void Gfx_LoadTextureTileI_ClampWrapper(u8* texture, s32 width, s32 height) {
    Gfx_LoadTextureTileI_Clamp(texture, width, height);
}

void Gfx_LoadTextureTileIA4b_Clamp(u8* texture, s32 width, s32 height) {
    Gfx_LoadTextureTile4b(texture, G_IM_FMT_IA, width, height, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                  G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
}

void Gfx_LoadTextureTileI4b_Clamp(u8* texture, s32 width, s32 height) {
    Gfx_LoadTextureTile4b(texture, G_IM_FMT_I, width, height, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                  G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
}

void Gfx_LoadTextureBlockIA4b_Clamp(u8* texture, s32 width, s32 height) {
    Gfx_LoadTextureBlock4b(texture, G_IM_FMT_IA, width, height, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                  G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
}

void Gfx_LoadTextureBlockI4b_Clamp(u8* texture, s32 width, s32 height) {
    Gfx_LoadTextureBlock4b(texture, G_IM_FMT_I, width, height, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                  G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
}

void Gfx_LoadTextureBlockI4b_MirrorWrap(u8* texture, s32 width, s32 height) {
    s32 masks = GetLog2(width);
    s32 maskt = GetLog2(height);

    Gfx_LoadTextureBlock4b(texture, G_IM_FMT_I, width, height, G_TX_MIRROR | G_TX_WRAP, G_TX_MIRROR | G_TX_WRAP, masks, maskt,
                  G_TX_NOLOD, G_TX_NOLOD);
}

void Gfx_LoadTextureBlockI4b_ClampWrapper(u8* texture, s32 width, s32 height) {
    Gfx_LoadTextureBlockI4b_Clamp(texture, width, height);
}

void Gfx_LoadTextureTileI4b_ClampWrapper(u8* texture, s32 width, s32 height) {
    Gfx_LoadTextureTileI4b_Clamp(texture, width, height);
}

void Gfx_LoadTextureBlockI4b_MirrorWrapS(u8* texture, s32 width, s32 height) {
    s32 masks = GetLog2(width);

    Gfx_LoadTextureBlock4b(texture, G_IM_FMT_I, width, height, G_TX_MIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_CLAMP, masks,
                  G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
}

void Gfx_LoadTextureBlockI4b_Wrap(u8* texture, s32 width, s32 height) {
    s32 masks = GetLog2(width);
    s32 maskt = GetLog2(height);

    Gfx_LoadTextureBlock4b(texture, G_IM_FMT_I, width, height, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, masks,
                  maskt, G_TX_NOLOD, G_TX_NOLOD);
}

void Gfx_LoadMultiBlockI4b_Wrap(u8* texture, s32 width, s32 height) {
    s32 tmem = 0x100;
    s32 rtile = 1;
    s32 masks = GetLog2(width);
    s32 maskt = GetLog2(height);

    Gfx_LoadMultiBlock4b(texture, tmem, rtile, G_IM_FMT_I, width, height, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP,
                  masks, maskt, G_TX_NOLOD, G_TX_NOLOD);
}

void Gfx_LoadMultiBlockI4b_WrapCustom(u8* texture, s32 width, s32 height, s32 shifts, s32 shiftt) {
    s32 tmem = 0x100;
    s32 rtile = 1;
    s32 masks = GetLog2(width);
    s32 maskt = GetLog2(height);

    Gfx_LoadMultiBlock4b(texture, tmem, rtile, G_IM_FMT_I, width, height, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP,
                  masks, maskt, shifts, shiftt);
}

void Gfx_LoadTextureBlockCI_Clamp(u8* texture, s32 width, s32 height) {
    Gfx_LoadTextureBlockIA8(texture, G_IM_FMT_CI, width, height, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                  G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
}

void Gfx_LoadTextureBlockCI_MirrorWrapS(u8* texture, s32 width, s32 height, s32 masks) {
    Gfx_LoadTextureBlockIA8(texture, G_IM_FMT_CI, width, height, G_TX_MIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_CLAMP, masks,
                  G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
}

void Gfx_LoadTextureTileCI_Clamp(u8* texture, s32 width, s32 height) {
    Gfx_LoadTextureTileIA8(texture, G_IM_FMT_CI, width, height, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                  G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
}

void Gfx_SetupMultiTextureCI_RGBA16(u8* texture1, u8* texture2, s32 width, s32 height) {
    gDPSetCombineLERP(gDisplayListHead++, 0, 0, 0, TEXEL0, 0, 0, 0, TEXEL1, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED);

    gDPLoadMultiBlock(gDisplayListHead++, texture2, 0x100, G_TX_RENDERTILE, G_IM_FMT_I, G_IM_SIZ_8b, width, height, 0,
                      G_TX_MIRROR | G_TX_CLAMP, G_TX_MIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                      G_TX_NOLOD);

    gDPLoadTextureBlock(gDisplayListHead++, texture1, G_IM_FMT_RGBA, G_IM_SIZ_16b, width, height, 0,
                        G_TX_MIRROR | G_TX_CLAMP, G_TX_MIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                        G_TX_NOLOD);

    gDPSetTile(gDisplayListHead++, G_IM_FMT_I, G_IM_SIZ_8b, ((width) + 7) >> 3, 0x0100, 1, 0, G_TX_NOMIRROR | G_TX_WRAP,
               G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD);

    gDPSetTileSize(gDisplayListHead++, 1, 0, 0, (width - 1) << 2, (height - 1) << 2);
}

void Gfx_DrawQuad(Vtx* arg0) {
    gSPVertex(gDisplayListHead++, arg0, 4, 0);
    gSPDisplayList(gDisplayListHead++, gDL_DrawQuad);
}

void ParticleGfx_NoopStub10(void) {
}

void Gfx_DrawQuadRotated(Vec3f arg0, Vec3s arg1, f32 arg2, Vtx* arg3) {
    Matrix_SubmitRotateTranslateScale(arg0, arg1, arg2);

    gSPVertex(gDisplayListHead++, arg3, 4, 0);
    gSPDisplayList(gDisplayListHead++, gDL_DrawQuad);
}

void Gfx_DrawQuadRotatedScaleY(Vec3f arg0, Vec3s arg1, f32 arg3, Vtx* arg4) {
    Matrix_SubmitRotateTranslateScaleY(arg0, arg1, arg3);

    gSPVertex(gDisplayListHead++, arg4, 4, 0);
    gSPDisplayList(gDisplayListHead++, gDL_DrawQuad);
}

void Gfx_DrawQuadRotatedXY(Vec3f arg0, Vec3s arg1, f32 arg2, f32 arg3, Vtx* arg4) {
    Matrix_SubmitRotateTranslateScaleXY(arg0, arg1, arg2, arg3);

    gSPVertex(gDisplayListHead++, arg4, 4, 0);
    gSPDisplayList(gDisplayListHead++, gDL_DrawQuad);
}

void Gfx_DrawTriangleRotated(Vec3f arg0, Vec3s arg1, f32 arg2, Vtx* arg3) {
    Matrix_SubmitRotateTranslateScale(arg0, arg1, arg2);

    gSPVertex(gDisplayListHead++, arg3, 3, 0);
    gSPDisplayList(gDisplayListHead++, gDL_DrawTriangle);
}

void Gfx_DrawQuadBillboard(CameraStruct* arg0, Vec3f arg1, f32 arg2, Vtx* arg3) {
    Matrix_SubmitBillboard(arg0, arg1, arg2);

    gSPVertex(gDisplayListHead++, arg3, 4, 0);
    gSPDisplayList(gDisplayListHead++, gDL_DrawQuad);
}

void Gfx_DrawQuadBillboardRoll(CameraStruct* arg0, Vec3f arg1, f32 arg2, Vtx* arg3, s16 arg4) {
    Matrix_SubmitBillboardRoll(arg0, arg1, arg2, arg4);

    gSPVertex(gDisplayListHead++, arg3, 4, 0);
    gSPDisplayList(gDisplayListHead++, gDL_DrawQuad);
}

void Gfx_DrawQuadBillboardY(CameraStruct* arg0, Vec3f arg1, f32 arg2, Vtx* arg3) {
    Matrix_SubmitBillboardY(arg0, arg1, arg2);

    gSPVertex(gDisplayListHead++, arg3, 4, 0);
    gSPDisplayList(gDisplayListHead++, gDL_DrawQuad);
}

void Gfx_DrawQuadBillboardRollScaleY(CameraStruct* arg0, Vec3f arg1, f32 arg2, Vtx* arg3, s16 arg4) {
    Matrix_SubmitBillboardRollY(arg0, arg1, arg2, arg4);

    gSPVertex(gDisplayListHead++, arg3, 4, 0);
    gSPDisplayList(gDisplayListHead++, gDL_DrawQuad);
}

void Gfx_DrawTriangleBillboard(CameraStruct* arg0, Vec3f arg1, f32 arg2, Vtx* arg3) {
    Matrix_SubmitBillboard(arg0, arg1, arg2);

    gSPVertex(gDisplayListHead++, arg3, 3, 0);
    gSPDisplayList(gDisplayListHead++, gDL_DrawTriangle);
}

void Gfx_DrawTriangleBillboardRoll(CameraStruct* arg0, Vec3f arg1, f32 arg2, Vtx* arg3, s16 arg4) {
    Matrix_SubmitBillboardRoll(arg0, arg1, arg2, arg4);

    gSPVertex(gDisplayListHead++, arg3, 3, 0);
    gSPDisplayList(gDisplayListHead++, gDL_DrawTriangle);
}

void Gfx_DrawTiledTextureI(u8* texture, Vtx* vtx, s32 arg2, s32 arg3, s32 width, s32 height) {
    s32 i;
    s32 j;
    s32 var_s4 = 0;
    u8* var_s3 = texture;

    for (i = 0; i < arg3 / height; i++) {
        for (j = 0; j < arg2 / width; j++) {
            Gfx_LoadTextureBlockI_Clamp(var_s3, width, height);

            gSPVertex(gDisplayListHead++, &vtx[var_s4], 4, 0);
            gSPDisplayList(gDisplayListHead++, gDL_DrawQuad);

            var_s3 += width * height;
            var_s4 += 4;
        }
    }

    gSPTexture(gDisplayListHead++, 0x0001, 0x0001, 0, G_TX_RENDERTILE, G_OFF);
}

void Gfx_DrawTiledTextureIA16(u8* texture, Vtx* vtx, s32 arg2, s32 arg3, s32 width, s32 height) {
    s32 i;
    s32 j;
    s32 var_s4 = 0;
    u8* var_s3 = texture;

    for (i = 0; i < arg3 / height; i++) {
        for (j = 0; j < arg2 / width; j++) {
            Gfx_LoadTextureBlockIA16_Clamp(var_s3, width, height);

            gSPVertex(gDisplayListHead++, &vtx[var_s4], 4, 0);
            gSPDisplayList(gDisplayListHead++, gDL_DrawQuad);

            var_s3 += (width * height) * 2;
            var_s4 += 4;
        }
    }

    gSPTexture(gDisplayListHead++, 0x0001, 0x0001, 0, G_TX_RENDERTILE, G_OFF);
}

void Gfx_DrawTiledTextureIA8(u8* texture, Vtx* vtx, s32 arg2, s32 arg3, s32 width, s32 height) {
    s32 i;
    s32 j;
    s32 var_s4 = 0;
    u8* var_s3 = texture;

    for (i = 0; i < arg3 / height; i++) {
        for (j = 0; j < arg2 / width; j++) {
            Gfx_LoadTextureBlockIA8_Clamp(var_s3, width, height);

            gSPVertex(gDisplayListHead++, &vtx[var_s4], 4, 0);
            gSPDisplayList(gDisplayListHead++, gDL_DrawQuad);

            var_s3 += width * height;
            var_s4 += 4;
        }
    }

    gSPTexture(gDisplayListHead++, 0x0001, 0x0001, 0, G_TX_RENDERTILE, G_OFF);
}

void Gfx_DrawTiledTextureI4b(u8* texture, Vtx* vtx, s32 arg2, s32 arg3, s32 width, s32 height) {
    s32 i;
    s32 j;
    s32 var_s4 = 0;
    u8* var_s3 = texture;

    for (i = 0; i < arg3 / height; i++) {
        for (j = 0; j < arg2 / width; j++) {
            Gfx_LoadTextureBlockI4b_Clamp(var_s3, width, height);

            gSPVertex(gDisplayListHead++, &vtx[var_s4], 4, 0);
            gSPDisplayList(gDisplayListHead++, gDL_DrawQuad);

            var_s3 += (width * height) / 2;
            var_s4 += 4;
        }
    }

    gSPTexture(gDisplayListHead++, 0x0001, 0x0001, 0, G_TX_RENDERTILE, G_OFF);
}

void Gfx_DrawTiledTextureI4bTile(u8* texture, Vtx* vtx, s32 arg2, s32 arg3, s32 width, s32 height) {
    s32 i;
    s32 j;
    s32 var_s4 = 0;
    u8* var_s3 = texture;

    for (i = 0; i < arg3 / height; i++) {
        for (j = 0; j < arg2 / width; j++) {
            Gfx_LoadTextureTileI4b_Clamp(var_s3, width, height);

            gSPVertex(gDisplayListHead++, &vtx[var_s4], 4, 0);
            gSPDisplayList(gDisplayListHead++, gDL_DrawQuad);

            var_s3 += (width * height) / 2;
            var_s4 += 4;
        }
    }

    gSPTexture(gDisplayListHead++, 0x0001, 0x0001, 0, G_TX_RENDERTILE, G_OFF);
}

void Gfx_SetPrimColor(u8 r, u8 g, u8 b, u8 a) {
    gDPSetPrimColor(gDisplayListHead++, 0, 0, r, g, b, a);
}

void Gfx_SetEnvColor(u8 r, u8 g, u8 b, u8 a) {
    gDPPipeSync(gDisplayListHead++);
    gDPSetEnvColor(gDisplayListHead++, r, g, b, a);
}

void Gfx_SetFogColor(u8 r, u8 g, u8 b, u8 a) {
    gDPPipeSync(gDisplayListHead++);
    gDPSetFogColor(gDisplayListHead++, r, g, b, a);
}

void Gfx_SetBlendColor(u8 r, u8 g, u8 b, u8 a) {
    gDPPipeSync(gDisplayListHead++);
    gDPSetBlendColor(gDisplayListHead++, r, g, b, a);
}

void Gfx_SetPrimColorCombinePrimitive(u8 r, u8 g, u8 b, u8 a) {
    gDPPipeSync(gDisplayListHead++);
    gDPSetPrimColor(gDisplayListHead++, 0, 0, r, g, b, a);
    gDPSetCombineLERP(gDisplayListHead++, 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED, 0, 0, 0,
                      COMBINED);
}

void Gfx_SetPrimColorAlpha(u8 a) {
    gDPPipeSync(gDisplayListHead++);
    gDPSetPrimColor(gDisplayListHead++, 0, 0, 255, 255, 255, a);
    gDPSetCombineLERP(gDisplayListHead++, SHADE, 0, TEXEL0, 0, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED, 0, 0, 0,
                      COMBINED);
}

void Gfx_SetPrimAndEnvColor(u8 prim_r, u8 prim_g, u8 prim_b, u8 env_r, u8 env_g, u8 env_b, u8 prim_a) {
    gDPPipeSync(gDisplayListHead++);
    gDPSetPrimColor(gDisplayListHead++, 0, 0, prim_r, prim_g, prim_b, prim_a);
    gDPSetEnvColor(gDisplayListHead++, env_r, env_g, env_b, 0);
    gDPSetCombineLERP(gDisplayListHead++, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0,
                      COMBINED, 0, 0, 0, COMBINED);
}

void Gfx_SetPrimAndEnvColorNoise(u8 prim_r, u8 prim_g, u8 prim_b, u8 env_r, u8 env_g, u8 env_b, u8 prim_a) {
    gDPPipeSync(gDisplayListHead++);
    gDPSetPrimColor(gDisplayListHead++, 0, 0, prim_r, prim_g, prim_b, prim_a);
    gDPSetEnvColor(gDisplayListHead++, env_r, env_g, env_b, 255);
    gDPSetCombineLERP(gDisplayListHead++, NOISE, 0, ENV_ALPHA, 0, 0, 0, 0, TEXEL0, PRIMITIVE, ENVIRONMENT, COMBINED,
                      ENVIRONMENT, COMBINED, 0, PRIMITIVE, 0);
}

void Gfx_SetPrimAndEnvColorRGBA(u8 prim_r, u8 prim_g, u8 prim_b, u8 prim_a, u8 env_r, u8 env_g, u8 env_b, u8 env_a) {
    gDPPipeSync(gDisplayListHead++);
    gDPSetPrimColor(gDisplayListHead++, 0, 0, prim_r, prim_g, prim_b, prim_a);
    gDPSetEnvColor(gDisplayListHead++, env_r, env_g, env_b, env_a);
    gDPSetCombineLERP(gDisplayListHead++, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0,
                      COMBINED, 0, SHADE, 0, COMBINED, 0, SHADE, 0);
}

void Gfx_SetPrimAndEnvColorLOD(u8 l, u8 prim_r, u8 prim_g, u8 prim_b, u8 prim_a, u8 env_r, u8 env_g, u8 env_b) {
    gDPPipeSync(gDisplayListHead++);
    gDPSetPrimColor(gDisplayListHead++, 0, l, prim_r, prim_g, prim_b, prim_a);
    gDPSetEnvColor(gDisplayListHead++, env_r, env_g, env_b, 0);
    gDPSetCombineLERP(gDisplayListHead++, TEXEL1, TEXEL0, PRIM_LOD_FRAC, TEXEL0, TEXEL1, TEXEL0, PRIM_LOD_FRAC, TEXEL0,
                      PRIMITIVE, ENVIRONMENT, COMBINED, ENVIRONMENT, COMBINED, 0, PRIMITIVE, 0);
}

void Gfx_SetPrimAndEnvColorLODSimple(u8 l, u8 prim_r, u8 prim_g, u8 prim_b, u8 prim_a, u8 env_r, u8 env_g, u8 env_b) {
    gDPPipeSync(gDisplayListHead++);
    gDPSetPrimColor(gDisplayListHead++, 0, l, prim_r, prim_g, prim_b, prim_a);
    gDPSetEnvColor(gDisplayListHead++, env_r, env_g, env_b, 0);
    gDPSetCombineLERP(gDisplayListHead++, TEXEL1, TEXEL0, PRIM_LOD_FRAC, TEXEL0, 0, 0, 0, TEXEL0, PRIMITIVE,
                      ENVIRONMENT, COMBINED, ENVIRONMENT, COMBINED, 0, PRIMITIVE, 0);
}

u32 GetTileSizeByIndex(s32 arg0) {
    u32 ret = gTimerCounter;

    switch (arg0) {
        case 2:
            ret = gTimerShift1;
            break;

        case 3:
            ret = gTimerDiv3;
            break;

        case 4:
            ret = gTimerShift2;
            break;
    }

    return ret;
}

void Gfx_ScrollTexture(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    gDPSetTileSize(gDisplayListHead++, G_TX_RENDERTILE, arg0 * gTimerCounter, -arg1 * gTimerCounter,
                   (((arg0 * gTimerCounter) + arg2) - 1) << 2, (((-arg1 * gTimerCounter) + arg3) - 1) << 2);
}

void Gfx_ScrollTexture1(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    gDPSetTileSize(gDisplayListHead++, 1, arg0 * gTimerCounter, -arg1 * gTimerCounter,
                   (((arg0 * gTimerCounter) + arg2) - 1) << 2, (((-arg1 * gTimerCounter) + arg3) - 1) << 2);
}

void Gfx_ScrollTextureToDL(Gfx* gfx, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    gDPSetTileSize(gfx, G_TX_RENDERTILE, arg1 * gTimerCounter, -arg2 * gTimerCounter, (((arg1 * gTimerCounter) + arg3) - 1) << 2,
                   (((-arg2 * gTimerCounter) + arg4) - 1) << 2);
}

void Gfx_ScrollTexture1ToDL(Gfx* gfx, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    gDPSetTileSize(gfx, 1, arg1 * gTimerCounter, -arg2 * gTimerCounter, (((arg1 * gTimerCounter) + arg3) - 1) << 2,
                   (((-arg2 * gTimerCounter) + arg4) - 1) << 2);
}

void Gfx_ScrollTextureY(Gfx* gfx, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    gDPSetTileSize(gfx, G_TX_RENDERTILE, arg1, -arg2 * gTimerCounter, ((arg3 + arg1) - 1) << 2,
                   (((-arg2 * gTimerCounter) + arg4) - 1) << 2);
}

void Gfx_ScrollTextureY1(Gfx* gfx, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    gDPSetTileSize(gfx, 1, arg1, -arg2 * gTimerCounter, ((arg3 + arg1) - 1) << 2,
                   (((-arg2 * gTimerCounter) + arg4) - 1) << 2);
}

void Gfx_SetTileSizeDynamic(Gfx* gfx, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7) {
    u32 temp_v0 = GetTileSizeByIndex(arg7);
    s32 temp_v1 = arg1 + (arg3 * temp_v0);
    s32 temp_a0 = arg2 - (arg4 * temp_v0);

    gDPSetTileSize(gfx, G_TX_RENDERTILE, temp_v1, temp_a0, ((temp_v1 + arg5) - 1) << 2, ((temp_a0 + arg6) - 1) << 2);
}

void Gfx_SetTileSizeDynamic1(Gfx* gfx, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7) {
    u32 temp_v0 = GetTileSizeByIndex(arg7);
    s32 temp_v1 = arg1 + (arg3 * temp_v0);
    s32 temp_a0 = arg2 - (arg4 * temp_v0);

    gDPSetTileSize(gfx, 1, arg1 + (arg3 * temp_v0), arg2 - (arg4 * temp_v0), ((temp_v1 + arg5) - 1) << 2,
                   ((temp_a0 + arg6) - 1) << 2);
}

Gfx* Gfx_LoadTextureBlock4bGeneric(Gfx* gfx, u8* texture, s32 fmt, s32 width, s32 height, s32 cms, s32 cmt, s32 masks, s32 maskt,
                   s32 shifts, s32 shiftt) {
    gDPLoadTextureBlock_4b(gfx++, texture, fmt, width, height, 0, cms, cmt, masks, maskt, shifts, shiftt);
    return gfx;
}

void Gfx_LoadTextureBlockI_ClampGeneric(Gfx* gfx, u8* texture, s32 width, s32 height) {
    Gfx_LoadTextureBlock4bGeneric(gfx, texture, G_IM_FMT_I, width, height, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                  G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
}

Gfx* Gfx_LoadMultiTileGeneric(Gfx* arg0, u8* texture, arg1_func_81407874_014_004* arg2, s32 tmem, s32 rtile) {
    switch (arg2->unk_04->fmt) {
        case G_IM_FMT_RGBA:
            switch (arg2->unk_04->size) {
                case G_IM_SIZ_16b:
                    gDPLoadMultiTile(arg0++, texture, tmem, rtile, G_IM_FMT_RGBA, G_IM_SIZ_16b, arg2->unk_04->width,
                                     arg2->unk_04->height, 0, 0, arg2->unk_04->width - 1, arg2->unk_04->height - 1, 0,
                                     arg2->unk_04->cms, arg2->unk_04->cmt, arg2->unk_04->masks, arg2->unk_04->maskt,
                                     arg2->unk_04->shfits, arg2->unk_04->shiftt);
                    break;
            }
            break;

        case G_IM_FMT_IA:
            switch (arg2->unk_04->size) {
                case G_IM_SIZ_8b:
                    gDPLoadMultiTile(arg0++, texture, tmem, rtile, G_IM_FMT_IA, G_IM_SIZ_8b, arg2->unk_04->width,
                                     arg2->unk_04->height, 0, 0, arg2->unk_04->width - 1, arg2->unk_04->height - 1, 0,
                                     arg2->unk_04->cms, arg2->unk_04->cmt, arg2->unk_04->masks, arg2->unk_04->maskt,
                                     arg2->unk_04->shfits, arg2->unk_04->shiftt);
                    break;

                case G_IM_SIZ_16b:
                    gDPLoadMultiTile(arg0++, texture, tmem, rtile, G_IM_FMT_IA, G_IM_SIZ_16b, arg2->unk_04->width,
                                     arg2->unk_04->height, 0, 0, arg2->unk_04->width - 1, arg2->unk_04->height - 1, 0,
                                     arg2->unk_04->cms, arg2->unk_04->cmt, arg2->unk_04->masks, arg2->unk_04->maskt,
                                     arg2->unk_04->shfits, arg2->unk_04->shiftt);
                    break;
            }
            break;

        case G_IM_FMT_I:
            switch (arg2->unk_04->size) {
                case G_IM_SIZ_4b:
                    gDPLoadMultiTile_4b(arg0++, texture, tmem, rtile, G_IM_FMT_I, arg2->unk_04->width,
                                        arg2->unk_04->height, 0, 0, arg2->unk_04->width - 1, arg2->unk_04->height - 1,
                                        0, arg2->unk_04->cms, arg2->unk_04->cmt, arg2->unk_04->masks,
                                        arg2->unk_04->maskt, arg2->unk_04->shfits, arg2->unk_04->shiftt);
                    break;

                case G_IM_SIZ_8b:
                    gDPLoadMultiTile(arg0++, texture, tmem, rtile, G_IM_FMT_I, G_IM_SIZ_8b, arg2->unk_04->width,
                                     arg2->unk_04->height, 0, 0, arg2->unk_04->width - 1, arg2->unk_04->height - 1, 0,
                                     arg2->unk_04->cms, arg2->unk_04->cmt, arg2->unk_04->masks, arg2->unk_04->maskt,
                                     arg2->unk_04->shfits, arg2->unk_04->shiftt);
                    break;
            }
            break;
    }

    return arg0;
}

Gfx* Gfx_SetupTextureAndTiling(Gfx* arg0, arg1_func_81407874_014_004* arg1, s32 tmem, s32 rtile) {
    u8* texture;
    u32 ret;

    texture = NULL;
    if (arg1->unk_0C != NULL) {
        ret = GetTileSizeByIndex(arg1->unk_0C->unk_06) % arg1->unk_0C->unk_04;
        texture = arg1->unk_0C->unk_00.texture[ret];
    } else if (arg1->unk_00 != NULL) {
        texture = arg1->unk_00;
    }

    if (texture != NULL) {
        arg0 = Gfx_LoadMultiTileGeneric(arg0, texture, arg1, tmem, rtile);
    }

    if (arg1->unk_08 != NULL) {
        switch (rtile) {
            case G_TX_RENDERTILE:
                Gfx_SetTileSizeDynamic(arg0++, arg1->unk_08->unk_00, arg1->unk_08->unk_02, arg1->unk_08->unk_04,
                              arg1->unk_08->unk_06, arg1->unk_04->width, arg1->unk_04->height, arg1->unk_08->unk_08);
                break;

            case 1:
                Gfx_SetTileSizeDynamic1(arg0++, arg1->unk_08->unk_00, arg1->unk_08->unk_02, arg1->unk_08->unk_04,
                              arg1->unk_08->unk_06, arg1->unk_04->width, arg1->unk_04->height, arg1->unk_08->unk_08);
                break;
        }
    }

    return arg0;
}

Gfx* Gfx_SetupTexturePrimary(Gfx* arg0, arg1_func_81407874_014* arg1) {
    return Gfx_SetupTextureAndTiling(arg0, arg1->unk_00, 0, G_TX_RENDERTILE);
}

Gfx* Gfx_SetupTextureSecondary(Gfx* arg0, arg1_func_81407874_014* arg1) {
    s32 var_a2 = 0;

    if (arg1->unk_04->unk_00 != arg1->unk_00->unk_00) {
        var_a2 = 0x100;
    }
    return Gfx_SetupTextureAndTiling(arg0, arg1->unk_04, var_a2, 1);
}

void Gfx_SetCombineModeCustom(Gfx* arg0, arg1_func_81407874_014_000_010* arg1) {
    gDPSetCombine(arg0++,
                  GCCc0w0(arg1->unk_00, arg1->unk_02, arg1->unk_04, arg1->unk_06) | GCCc1w0(arg1->unk_08, arg1->unk_0A),

                  GCCc0w1(arg1->unk_01, arg1->unk_03, arg1->unk_05, arg1->unk_07) |
                      GCCc1w1(arg1->unk_09, arg1->unk_0C, arg1->unk_0E, arg1->unk_0B, arg1->unk_0D, arg1->unk_0F));
}

Gfx* Gfx_ApplyTextureState(Gfx* arg0, arg1_func_81407874_014* arg1) {
    arg1_func_81407874_014_000* var_a3;
    arg1_func_81407874_014_004* sp20;
    arg1_func_81407874_014_000_018_000_000* temp_v0;
    arg1_func_81407874_014_000_014_000_000* temp_v1;
    Color_RGBA8_u32 color;
    u32 ret;
    s16 sp1c;
    s16 sp18;
    s16 sp14;
    s16 sp10;

    var_a3 = arg1->unk_00;
    sp20 = arg1->unk_04;

    if (var_a3 != NULL) {
        if (var_a3->unk_10 != NULL) {
            Gfx_SetCombineModeCustom(arg0++, var_a3->unk_10);
        }

        if (var_a3->unk_14 != NULL) {
            if (var_a3->unk_14->unk_04 == 0) {
                color.rgba = var_a3->unk_14->unk_00.color.rgba;
                sp1c = color.rgba >> 0x18;
                sp18 = color.rgba >> 0x10;
                sp14 = color.rgba >> 0x8;
                sp10 = color.rgba;

                gDPPipeSync(arg0++);
                gDPSetPrimColor(arg0++, 0, 0xFF, sp1c, sp18, sp14, sp10);
            } else {
                ret = GetTileSizeByIndex(var_a3->unk_14->unk_06) % var_a3->unk_14->unk_04;
                temp_v1 = &var_a3->unk_14->unk_00.ptr5[ret];

                gDPPipeSync(arg0++);
                gDPSetPrimColor(arg0++, 0, temp_v1->l, temp_v1->color.r, temp_v1->color.g, temp_v1->color.b,
                                temp_v1->color.a);
            }
        }

        if (var_a3->unk_18 != NULL) {
            if (var_a3->unk_18->unk_04 == 0) {
                gDPSetColor(arg0++, G_SETENVCOLOR, var_a3->unk_18->unk_00.color.rgba);
            } else {
                ret = GetTileSizeByIndex(var_a3->unk_18->unk_06) % var_a3->unk_18->unk_04;
                temp_v0 = &var_a3->unk_18->unk_00.ptr4[ret];

                gDPSetEnvColor(arg0++, temp_v0->color.r, temp_v0->color.g, temp_v0->color.b, temp_v0->color.a);
            }
        }

        if (var_a3->unk_1C != NULL) {
            gSPSetGeometryMode(arg0++, G_TEXTURE_GEN);
            gSPTexture(arg0++, var_a3->unk_1C->unk_00, var_a3->unk_1C->unk_02, 0, G_TX_RENDERTILE, G_ON);
        } else if (var_a3->unk_04 != 0) {
            gSPTexture(arg0++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);
        }

        if (var_a3->unk_04 != 0) {
            gDPSetTextureLUT(arg0++, G_TT_NONE);
        }

        arg0 = Gfx_SetupTexturePrimary(arg0, arg1);
    }

    if (sp20 != NULL) {
        arg0 = Gfx_SetupTextureSecondary(arg0, arg1);
    }

    return arg0;
}

void Gfx_ApplyColorLerp(s32 arg0, ColorLerpHook* arg1) {
    if (arg0 == 5) {
        arg1_func_81407874_014* tmp = arg1->unk_14;

        gDisplayListHead = Gfx_ApplyTextureState(gDisplayListHead, tmp);
    }
}
