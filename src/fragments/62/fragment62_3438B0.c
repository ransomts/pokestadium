#include "fragment62.h"
#include "src/6A40.h"

void func_84358FF0(void) {
}

void func_84358FF8(void) {
}

void RenderPrimColorRect(u8 arg0, u8 arg1, u8 arg2, u8 arg3) {
    gSPDisplayList(gDisplayListHead++, D_8140DDF8);

    Gfx_SetPrimColor(arg0, arg1, arg2, arg3);

    gSPTextureRectangle(gDisplayListHead++, 0, 0, 0x04FC, 0x03BC, G_TX_RENDERTILE, 0, 0, 0x1000, 0x0400);
    gSPDisplayList(gDisplayListHead++, D_8140DDD8);
}

void Ui_DrawPanel(CameraStruct* arg0) {
    RunCameraCallbacks(arg0);
    gMatrixBuffer = GfxAlloc(sizeof(unk_D_8140E620));
    gMatrixBufferIdx = 0;
    gPanelDrawCount += 1;

    gSPDisplayList(gDisplayListHead++, D_8140DB30);

    Gfx_SetPrimColor(gPrimColorR, gPrimColorG, gPrimColorB, gPrimColorA);
    Gfx_SetFogColor(gFogColorR, gFogColorG, gFogColorB, gFogColorA);
    Gfx_SetEnvColor(gEnvColorR, gEnvColorG, gEnvColorB, gEnvColorA);
    func_81405B00(D_8439039A, D_8439039C, D_8439039E, D_843903A0);
    ColorRectNode_SetColor(D_8439037A, D_8439037C, D_8439037E);
    Particle_UpdateForCamera(arg0);
    guOrtho(&gMatrixBuffer->unk_5B80, 0.0f, 320.0f, 240.0f, 0.0f, -2.0f, 2.0f, 1.0f);

    gSPMatrix(gDisplayListHead++, (u32)&gMatrixBuffer->unk_5B80 & 0x1FFFFFFF,
              G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
    gSPDisplayList(gDisplayListHead++, D_8140DD78);

    Gfx_PipeSync();
    Particle_ProcessAllForCamera(arg0);

    gSPDisplayList(gDisplayListHead++, D_8140DAE0);
}
