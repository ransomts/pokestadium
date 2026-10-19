#include "fragment62.h"

s32 RenderPanelBackground(ParticleEffectInstance* arg0, CameraStruct* arg1) {
    Gfx_SetPrimAndEnvColor(arg0->prim_r, arg0->prim_g, arg0->prim_b, arg0->env_r, arg0->env_g, arg0->env_b, arg0->prim_a);
    Matrix_SubmitBillboard(arg1, arg0->unk_2C, arg0->unk_1C);

    gSPDisplayList(gDisplayListHead++, gDL_PanelBackground);
}

void RenderIconMasked(ParticleEffectInstance* arg0, CameraStruct* arg1) {
    Gfx_LoadTextureBlockIA8_Clamp(gWaterTexture[0x76] + (arg0->unk_C7 << 0xB), 0x20, 0x40);
    Gfx_LoadMultiBlockI4b_WrapCustom(gWaterTexture[0x77], 0x40, 0x40, 2, 1);
    Gfx_ScrollTexture1(0, 0xA, 0x40, 0x40);
    Gfx_SetPrimAndEnvColorLODSimple(0x80, arg0->prim_r, arg0->prim_g, arg0->prim_b, arg0->prim_a, arg0->env_r, arg0->env_g, arg0->env_b);
    Gfx_DrawQuadBillboard(arg1, arg0->unk_2C, arg0->unk_1C, gVtx_UI_Square);
}

void RenderPanelWithIcon(ParticleEffectInstance* arg0, CameraStruct* arg1) {
    gSPDisplayList(gDisplayListHead++, gDL_BaseUI);

    RenderIconMasked(arg0, arg1);
}

void RenderOverlayWithIcon(ParticleEffectInstance* arg0, CameraStruct* arg1) {
    gSPDisplayList(gDisplayListHead++, gDL_OverlayUI);

    RenderIconMasked(arg0, arg1);
}

void BattleAnim_DrawAsset1FAnimatedI4WithAsset20DisplayList(ParticleEffectInstance* arg0, CameraStruct* arg1) {
    Matrix_SubmitBillboard(arg1, arg0->unk_2C, arg0->unk_1C);

    gSPDisplayList(gDisplayListHead++, gDL_OverlayUI);

    Gfx_LoadTextureBlockI4b_Wrap(gWaterTexture[0x1F], 0x20, 0x40);
    Gfx_ScrollTexture(0, 8, 0x20, 0x40);
    Gfx_SetPrimAndEnvColorRGBA(0xFF, 0xFF, 0xFF, arg0->prim_a, 0xFF, 0xFF, 0xFF, 0xFF);

    gDPSetRenderMode(gDisplayListHead++, G_RM_PASS, G_RM_AA_ZB_XLU_SURF2);
    gSPDisplayList(gDisplayListHead++, gWaterTexture[0x20]);
}

s32 RenderItemIcon(ParticleEffectInstance* arg0, UNUSED CameraStruct* arg1) {
    Matrix_SubmitRotateTranslateScale(arg0->unk_2C, arg0->unk_94, arg0->unk_1C);

    gSPDisplayList(gDisplayListHead++, gDL_ItemIcon);

    Gfx_LoadTextureBlockRGBA16_Clamp(gWaterTexture[0xBC], 0x20, 0x20);

    gSPDisplayList(gDisplayListHead++, gWaterTexture[0xBD]);
}

void RenderStatusBar(ParticleEffectInstance* arg0, UNUSED CameraStruct* arg1) {
    Matrix_Submit2DRotateTranslateScale(arg0->unk_2C.x, arg0->unk_2C.y, arg0->unk_94.z, arg0->unk_1C);

    gSPDisplayList(gDisplayListHead++, gDL_BaseUI);

    Gfx_SetPrimAndEnvColorLOD(0x80, arg0->prim_r, arg0->prim_g, arg0->prim_b, arg0->prim_a, arg0->env_r, arg0->env_g, arg0->env_b);
    Gfx_LoadTextureBlockI4b_Wrap(gWaterTexture[0x27], 0x40, 0x40);
    Gfx_ScrollTexture(2, -2, 0x40, 0x40);
    Gfx_LoadMultiBlockI4b_Wrap(gWaterTexture[0x28], 0x40, 0x40);
    Gfx_ScrollTexture1(0, -1, 0x40, 0x40);
    Gfx_DrawQuad(gPanelBgVerts);
}

void BattleAnim_DrawAssets27And28LayeredI4QuadVariantB(ParticleEffectInstance* arg0, UNUSED CameraStruct* arg1) {
    Matrix_Submit2DRotateTranslateScale(arg0->unk_2C.x, arg0->unk_2C.y, arg0->unk_94.z, arg0->unk_1C);

    gSPDisplayList(gDisplayListHead++, gDL_BaseUI);

    Gfx_SetPrimAndEnvColorLOD(0x80, arg0->prim_r, arg0->prim_g, arg0->prim_b, arg0->prim_a, arg0->env_r, arg0->env_g, arg0->env_b);
    Gfx_LoadTextureBlockI4b_Wrap(gWaterTexture[0x27], 0x40, 0x40);
    Gfx_ScrollTexture(1, -3, 0x40, 0x40);
    Gfx_LoadMultiBlockI4b_Wrap(gWaterTexture[0x28], 0x40, 0x40);
    Gfx_ScrollTexture1(-2, -2, 0x40, 0x40);
    Gfx_DrawQuad(gPanelBgLargeVerts);
}

void RenderMultiBlockIcon(ParticleEffectInstance* arg0, UNUSED CameraStruct* arg1) {
    Matrix_Submit2DRotateTranslateScale(arg0->unk_2C.x, arg0->unk_2C.y, arg0->unk_94.z, arg0->unk_1C);

    gSPDisplayList(gDisplayListHead++, gDL_BaseUI);

    Gfx_SetPrimAndEnvColorLOD(0x80, arg0->prim_r, arg0->prim_g, arg0->prim_b, arg0->prim_a, arg0->env_r, arg0->env_g, arg0->env_b);
    Gfx_LoadMultiBlock4b(gWaterTexture[0x29], 0, 0, 4, 0x20, 0x20, 1, 1, 5, 5, 2, 0);
    Gfx_ScrollTexture(1, 1, 0x20, 0x20);
    Gfx_LoadMultiBlock4b(gWaterTexture[0x29], 0x100, 1, 4, 0x20, 0x20, 1, 1, 5, 5, 1, 0xF);
    Gfx_ScrollTexture1(-1, 1, 0x20, 0x20);
    Gfx_DrawQuad(gFullscreenQuadVtx);
}

void BattleAnim_DrawAsset87AnimatedI4Quad(ParticleEffectInstance* arg0, UNUSED CameraStruct* arg1) {
    Matrix_Submit2DRotateTranslateScale(arg0->unk_2C.x, arg0->unk_2C.y, arg0->unk_94.z, arg0->unk_1C);

    gSPDisplayList(gDisplayListHead++, gDL_BaseUI);

    Gfx_SetPrimAndEnvColor(arg0->prim_r, arg0->prim_g, arg0->prim_b, arg0->env_r, arg0->env_g, arg0->env_b, arg0->prim_a);
    Gfx_LoadTextureBlockI4b_Wrap(gWaterTexture[0x87], 0x20, 0x20);
    Gfx_ScrollTexture(0, 2, 0x20, 0x20);
    Gfx_DrawQuad(gFullscreenQuadVtx);
}

void BattleAnim_DrawI4AtlasYScaled(ParticleEffectInstance* arg0, u8* arg1) {
    Matrix_Submit2DRotateTranslateScaleY(arg0->unk_2C.x, arg0->unk_2C.y, arg0->unk_94.z, arg0->unk_1C);

    gSPDisplayList(gDisplayListHead++, gDL_BaseUI);

    Gfx_SetPrimAndEnvColor(arg0->prim_r, arg0->prim_g, arg0->prim_b, arg0->env_r, arg0->env_g, arg0->env_b, arg0->prim_a);
    Gfx_DrawTiledTextureI4b(arg1, gPanelQuadVerts, 0x40, 0x40, 0x40, 0x40);
}

void BattleAnim_DrawAsset19I4AtlasYScaled(ParticleEffectInstance* arg0, UNUSED CameraStruct* arg1) {
    BattleAnim_DrawI4AtlasYScaled(arg0, gWaterTexture[0x19]);
}

void BattleAnim_DrawAsset5EI4AtlasYScaled(ParticleEffectInstance* arg0, UNUSED CameraStruct* arg1) {
    BattleAnim_DrawI4AtlasYScaled(arg0, gWaterTexture[0x5E]);
}

void BattleAnim_DrawAsset1AFrameI4Quad(ParticleEffectInstance* arg0, UNUSED CameraStruct* arg1) {
    gSPDisplayList(gDisplayListHead++, gDL_OverlayUI);
    gSPClearGeometryMode(gDisplayListHead++, G_CULL_BACK);

    Gfx_LoadTextureBlockI4b_ClampWrapper(gWaterTexture[0x1A] + (arg0->unk_C7 << 9), 0x20, 0x20);
    Gfx_SetPrimAndEnvColor(arg0->prim_r, arg0->prim_g, arg0->prim_b, arg0->env_r, arg0->env_g, arg0->env_b, arg0->prim_a);
    Gfx_DrawQuadRotated(arg0->unk_2C, arg0->unk_94, arg0->unk_1C, gMatrix_UITransform);

    gSPSetGeometryMode(gDisplayListHead++, G_CULL_BACK);
}

void BattleAnim_DrawAsset1CRgba16Quad(ParticleEffectInstance* arg0, UNUSED CameraStruct* arg1) {
    gSPDisplayList(gDisplayListHead++, gDL_BaseUI2);
    gSPClearGeometryMode(gDisplayListHead++, G_CULL_BACK);

    Gfx_LoadTextureBlockRGBA16_Clamp(gWaterTexture[0x1C], 0x20, 0x20);
    Gfx_DrawQuadRotated(arg0->unk_2C, arg0->unk_94, arg0->unk_1C, gMatrix_UITransform);

    gSPSetGeometryMode(gDisplayListHead++, G_CULL_BACK);
}

void BattleAnim_DrawAsset1ERgba16Quad(ParticleEffectInstance* arg0, UNUSED CameraStruct* arg1) {
    gSPDisplayList(gDisplayListHead++, gDL_BaseUI2);
    gSPClearGeometryMode(gDisplayListHead++, G_CULL_BACK);

    Gfx_LoadTextureBlockRGBA16_Clamp(gWaterTexture[0x1E], 0x20, 0x20);
    Gfx_DrawQuadRotated(arg0->unk_2C, arg0->unk_94, arg0->unk_1C, gMatrix_UITransform);

    gSPSetGeometryMode(gDisplayListHead++, G_CULL_BACK);
}

void BattleAnim_DrawAssetC3Rgba16Quad(ParticleEffectInstance* arg0, UNUSED CameraStruct* arg1) {
    gSPDisplayList(gDisplayListHead++, gDL_BaseUI2);
    gSPClearGeometryMode(gDisplayListHead++, G_CULL_BACK);

    Gfx_LoadTextureBlockRGBA16_Clamp(gWaterTexture[0xC3], 0x20, 0x20);
    Gfx_DrawQuadRotated(arg0->unk_2C, arg0->unk_94, arg0->unk_1C, gMatrix_UITransform);

    gSPSetGeometryMode(gDisplayListHead++, G_CULL_BACK);
}

void BattleAnim_DrawAsset1DRotatedI4Quad(ParticleEffectInstance* arg0, UNUSED CameraStruct* arg1) {
    Vec3s sp40;

    gSPDisplayList(gDisplayListHead++, gDL_BaseUI);
    gSPClearGeometryMode(gDisplayListHead++, G_CULL_BACK);

    Gfx_LoadTextureBlockI4b_ClampWrapper(gWaterTexture[0x1D], 0x20, 0x20);
    Gfx_SetPrimAndEnvColor(arg0->prim_r, arg0->prim_g, arg0->prim_b, arg0->env_r, arg0->env_g, arg0->env_b, arg0->prim_a);
    sp40.x = arg0->unk_94.x + 0x4000;
    sp40.y = arg0->unk_94.y + 0x4000;
    sp40.z = arg0->unk_94.z;
    Gfx_DrawQuadRotated(arg0->unk_2C, sp40, arg0->unk_1C, gMatrix_UITransform);

    gSPSetGeometryMode(gDisplayListHead++, G_CULL_BACK);
}

void BattleAnim_DrawParticleNoop(UNUSED ParticleEffectInstance* arg0, UNUSED CameraStruct* arg1) {
}

void RenderTimerDigits(ParticleEffectInstance* arg0, UNUSED CameraStruct* arg1) {
    gSPDisplayList(gDisplayListHead++, gDL_OverlayUI);

    Gfx_LoadTextureBlockI4b_ClampWrapper(gWaterTexture[0x13] + (gTimerMask3 * 0x600), 0x20, 0x60);
    Gfx_SetPrimAndEnvColor(arg0->prim_r, arg0->prim_g, arg0->prim_b, arg0->env_r, arg0->env_g, arg0->env_b, arg0->prim_a);

    gSPClearGeometryMode(gDisplayListHead++, G_CULL_BACK);

    Gfx_DrawQuadRotatedScaleY(arg0->unk_2C, arg0->unk_94, arg0->unk_1C, gPanelBarVerts);

    gSPSetGeometryMode(gDisplayListHead++, G_CULL_BACK);
}

void RenderTimerDigitsAlt(ParticleEffectInstance* arg0, UNUSED CameraStruct* arg1) {
    gSPDisplayList(gDisplayListHead++, gDL_OverlayUI);
    gSPClearGeometryMode(gDisplayListHead++, G_CULL_BACK);

    Gfx_LoadTextureBlockI4b_ClampWrapper(gWaterTexture[0x13] + (gTimerMask3 * 0x600), 0x20, 0x60);
    Gfx_SetPrimAndEnvColor(arg0->prim_r, arg0->prim_g, arg0->prim_b, arg0->env_r, arg0->env_g, arg0->env_b, arg0->prim_a);
    Gfx_DrawQuadRotatedScaleY(arg0->unk_2C, arg0->unk_94, arg0->unk_1C, gPanelBarSmallVerts);

    gSPSetGeometryMode(gDisplayListHead++, G_CULL_BACK);
}

void BattleAnim_DrawAsset13FrameI4YScaledQuadC(ParticleEffectInstance* arg0, UNUSED CameraStruct* arg1) {
    gSPDisplayList(gDisplayListHead++, gDL_OverlayUI);
    gSPClearGeometryMode(gDisplayListHead++, G_CULL_BACK);

    Gfx_LoadTextureBlockI4b_ClampWrapper(gWaterTexture[0x13] + (gTimerMask3 * 0x600), 0x20, 0x60);
    Gfx_SetPrimAndEnvColor(arg0->prim_r, arg0->prim_g, arg0->prim_b, arg0->env_r, arg0->env_g, arg0->env_b, arg0->prim_a);
    Gfx_DrawQuadRotatedScaleY(arg0->unk_2C, arg0->unk_94, arg0->unk_1C, gPanelMiscVerts);

    gSPSetGeometryMode(gDisplayListHead++, G_CULL_BACK);
}

void RenderTimerNumber(ParticleEffectInstance* arg0, CameraStruct* arg1) {
    gSPDisplayList(gDisplayListHead++, gDL_OverlayUI);
    gSPClearGeometryMode(gDisplayListHead++, G_CULL_BACK);

    Gfx_LoadTextureBlockI4b_ClampWrapper(gWaterTexture[0x13] + (gTimerMask3 * 0x600), 0x20, 0x60);
    Gfx_SetPrimAndEnvColor(arg0->prim_r, arg0->prim_g, arg0->prim_b, arg0->env_r, arg0->env_g, arg0->env_b, arg0->prim_a);
    Gfx_DrawQuadBillboardRollScaleY(arg1, arg0->unk_2C, arg0->unk_1C, gPanelBarVerts, arg0->unk_94.z);

    gSPSetGeometryMode(gDisplayListHead++, G_CULL_BACK);
}

void BattleAnim_DrawAsset13FrameI4ModelQuadB(ParticleEffectInstance* arg0, CameraStruct* arg1) {
    gSPDisplayList(gDisplayListHead++, gDL_OverlayUI);
    gSPClearGeometryMode(gDisplayListHead++, G_CULL_BACK);

    Gfx_LoadTextureBlockI4b_ClampWrapper(gWaterTexture[0x13] + (gTimerMask3 * 0x600), 0x20, 0x60);
    Gfx_SetPrimAndEnvColor(arg0->prim_r, arg0->prim_g, arg0->prim_b, arg0->env_r, arg0->env_g, arg0->env_b, arg0->prim_a);
    Gfx_DrawQuadBillboardRollScaleY(arg1, arg0->unk_2C, arg0->unk_1C, gPanelBarSmallVerts, arg0->unk_94.z);

    gSPSetGeometryMode(gDisplayListHead++, G_CULL_BACK);
}

void BattleAnim_DrawAsset13FrameI4ModelQuadC(ParticleEffectInstance* arg0, CameraStruct* arg1) {
    gSPDisplayList(gDisplayListHead++, gDL_OverlayUI);
    gSPClearGeometryMode(gDisplayListHead++, G_CULL_BACK);

    Gfx_LoadTextureBlockI4b_ClampWrapper(gWaterTexture[0x13] + (gTimerMask3 * 0x600), 0x20, 0x60);
    Gfx_SetPrimAndEnvColor(arg0->prim_r, arg0->prim_g, arg0->prim_b, arg0->env_r, arg0->env_g, arg0->env_b, arg0->prim_a);
    Gfx_DrawQuadBillboardRollScaleY(arg1, arg0->unk_2C, arg0->unk_1C, gPanelMiscVerts, arg0->unk_94.z);

    gSPSetGeometryMode(gDisplayListHead++, G_CULL_BACK);
}

void BattleAnim_DrawAsset1BI4TriangleA(ParticleEffectInstance* arg0, UNUSED CameraStruct* arg1) {
    gSPDisplayList(gDisplayListHead++, gDL_BaseUI);
    gSPClearGeometryMode(gDisplayListHead++, G_CULL_BACK);

    Gfx_LoadTextureBlockI4b_ClampWrapper(gWaterTexture[0x1B], 0x10, 0x100);
    Gfx_SetPrimAndEnvColor(0xFF, 0xFF, 0xFF, arg0->prim_r, arg0->prim_g, arg0->prim_b, arg0->prim_a);
    Gfx_DrawTriangleRotated(arg0->unk_2C, arg0->unk_94, arg0->unk_1C, gVtx_UI_TriangleSmall);

    gSPSetGeometryMode(gDisplayListHead++, G_CULL_BACK);
}

void BattleAnim_DrawAsset1BI4TriangleB(ParticleEffectInstance* arg0, UNUSED CameraStruct* arg1) {
    gSPDisplayList(gDisplayListHead++, gDL_BaseUI);
    gSPClearGeometryMode(gDisplayListHead++, G_CULL_BACK);

    Gfx_LoadTextureBlockI4b_ClampWrapper(gWaterTexture[0x1B], 0x10, 0x100);
    Gfx_SetPrimAndEnvColor(0xFF, 0xFF, 0xFF, arg0->prim_r, arg0->prim_g, arg0->prim_b, arg0->prim_a);
    Gfx_DrawTriangleRotated(arg0->unk_2C, arg0->unk_94, arg0->unk_1C, gVtx_UI_TriangleLarge);

    gSPSetGeometryMode(gDisplayListHead++, G_CULL_BACK);
}

void BattleAnim_DrawAsset13FrameDiv2I4Quad(ParticleEffectInstance* arg0, UNUSED CameraStruct* arg1) {
    gSPDisplayList(gDisplayListHead++, gDL_BaseUI);
    gSPClearGeometryMode(gDisplayListHead++, G_CULL_BACK);

    Gfx_LoadTextureBlockI4b_ClampWrapper(gWaterTexture[0x13] + ((gTimerShift1 & 7) * 0x600), 0x20, 0x60);
    Gfx_SetPrimAndEnvColor(0xFF, 0xFF, 0xFF, 0, 0x64, 0xC8, 0xFF);
    Gfx_DrawQuadRotated(arg0->unk_2C, arg0->unk_94, arg0->unk_1C, gVtx_UI_ComplexQuad);

    gSPSetGeometryMode(gDisplayListHead++, G_CULL_BACK);
}

void BattleAnim_DrawAsset18FrameI4ModelQuad(ParticleEffectInstance* arg0, CameraStruct* arg1) {
    gSPDisplayList(gDisplayListHead++, gDL_OverlayUI);

    Gfx_LoadTextureBlockI4b_ClampWrapper(gWaterTexture[0x18] + (arg0->unk_C7 << 9), 0x20, 0x20);
    Gfx_SetPrimAndEnvColor(arg0->prim_r, arg0->prim_g, arg0->prim_b, arg0->env_r, arg0->env_g, arg0->env_b, arg0->prim_a);
    Gfx_DrawQuadBillboardRoll(arg1, arg0->unk_2C, arg0->unk_1C, gMatrix_UITransform, arg0->unk_94.z);
}

void BattleAnim_DrawAssetA9I4XYScaledQuad(ParticleEffectInstance* arg0, UNUSED CameraStruct* arg1) {
    gSPDisplayList(gDisplayListHead++, gDL_OverlayUI);
    gSPClearGeometryMode(gDisplayListHead++, G_CULL_BACK);

    Gfx_LoadTextureBlockI4b_ClampWrapper(gWaterTexture[0xA9], 0x20, 0x20);
    Gfx_SetPrimAndEnvColor(arg0->prim_r, arg0->prim_g, arg0->prim_b, arg0->env_r, arg0->env_g, arg0->env_b, arg0->prim_a);
    Gfx_DrawQuadRotatedXY(arg0->unk_2C, arg0->unk_94, arg0->unk_1C, arg0->unk_20, gVtx_UI_RectVertical);

    gSPSetGeometryMode(gDisplayListHead++, G_CULL_BACK);
}

void BattleAnim_DrawParticleFullScreenColorOverlay(ParticleEffectInstance* arg0, UNUSED CameraStruct* arg1) {
    RenderPrimColorRect(arg0->prim_r, arg0->prim_g, arg0->prim_b, arg0->prim_a);
}
