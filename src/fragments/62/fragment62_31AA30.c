#include "fragment62.h"

s32 RenderPanelBackground(unk_D_8140E720* arg0, CameraStruct* arg1) {
    func_81405C70(arg0->prim_r, arg0->prim_g, arg0->prim_b, arg0->env_r, arg0->env_g, arg0->env_b, arg0->prim_a);
    func_8140213C(arg1, arg0->unk_2C, arg0->unk_1C);

    gSPDisplayList(gDisplayListHead++, gDL_PanelBackground);
}

void RenderIconMasked(unk_D_8140E720* arg0, CameraStruct* arg1) {
    Gfx_LoadTextureBlockIA8_Clamp(gWaterTexture[0x76] + (arg0->unk_C7 << 0xB), 0x20, 0x40);
    func_814044FC(gWaterTexture[0x77], 0x40, 0x40, 2, 1);
    func_81406168(0, 0xA, 0x40, 0x40);
    func_81405FAC(0x80, arg0->prim_r, arg0->prim_g, arg0->prim_b, arg0->prim_a, arg0->env_r, arg0->env_g, arg0->env_b);
    func_81404DB4(arg1, arg0->unk_2C, arg0->unk_1C, D_8140E1F8);
}

void RenderPanelWithIcon(unk_D_8140E720* arg0, CameraStruct* arg1) {
    gSPDisplayList(gDisplayListHead++, gDL_BaseUI);

    RenderIconMasked(arg0, arg1);
}

void RenderOverlayWithIcon(unk_D_8140E720* arg0, CameraStruct* arg1) {
    gSPDisplayList(gDisplayListHead++, gDL_OverlayUI);

    RenderIconMasked(arg0, arg1);
}

void func_84330388(unk_D_8140E720* arg0, CameraStruct* arg1) {
    func_8140213C(arg1, arg0->unk_2C, arg0->unk_1C);

    gSPDisplayList(gDisplayListHead++, gDL_OverlayUI);

    func_8140441C(gWaterTexture[0x1F], 0x20, 0x40);
    func_814060D4(0, 8, 0x20, 0x40);
    func_81405E04(0xFF, 0xFF, 0xFF, arg0->prim_a, 0xFF, 0xFF, 0xFF, 0xFF);

    gDPSetRenderMode(gDisplayListHead++, G_RM_PASS, G_RM_AA_ZB_XLU_SURF2);
    gSPDisplayList(gDisplayListHead++, gWaterTexture[0x20]);
}

s32 RenderItemIcon(unk_D_8140E720* arg0, UNUSED CameraStruct* arg1) {
    func_81401FC0(arg0->unk_2C, arg0->unk_94, arg0->unk_1C);

    gSPDisplayList(gDisplayListHead++, gDL_ItemIcon);

    Gfx_LoadTextureBlockRGBA16_Clamp(gWaterTexture[0xBC], 0x20, 0x20);

    gSPDisplayList(gDisplayListHead++, gWaterTexture[0xBD]);
}

void RenderStatusBar(unk_D_8140E720* arg0, UNUSED CameraStruct* arg1) {
    func_814015A0(arg0->unk_2C.x, arg0->unk_2C.y, arg0->unk_94.z, arg0->unk_1C);

    gSPDisplayList(gDisplayListHead++, gDL_BaseUI);

    func_81405ED8(0x80, arg0->prim_r, arg0->prim_g, arg0->prim_b, arg0->prim_a, arg0->env_r, arg0->env_g, arg0->env_b);
    func_8140441C(gWaterTexture[0x27], 0x40, 0x40);
    func_814060D4(2, -2, 0x40, 0x40);
    func_81404484(gWaterTexture[0x28], 0x40, 0x40);
    func_81406168(0, -1, 0x40, 0x40);
    func_81404A6C(D_84385DC0);
}

void func_84330688(unk_D_8140E720* arg0, UNUSED CameraStruct* arg1) {
    func_814015A0(arg0->unk_2C.x, arg0->unk_2C.y, arg0->unk_94.z, arg0->unk_1C);

    gSPDisplayList(gDisplayListHead++, gDL_BaseUI);

    func_81405ED8(0x80, arg0->prim_r, arg0->prim_g, arg0->prim_b, arg0->prim_a, arg0->env_r, arg0->env_g, arg0->env_b);
    func_8140441C(gWaterTexture[0x27], 0x40, 0x40);
    func_814060D4(1, -3, 0x40, 0x40);
    func_81404484(gWaterTexture[0x28], 0x40, 0x40);
    func_81406168(-2, -2, 0x40, 0x40);
    func_81404A6C(D_84385E00);
}

void RenderMultiBlockIcon(unk_D_8140E720* arg0, UNUSED CameraStruct* arg1) {
    func_814015A0(arg0->unk_2C.x, arg0->unk_2C.y, arg0->unk_94.z, arg0->unk_1C);

    gSPDisplayList(gDisplayListHead++, gDL_BaseUI);

    func_81405ED8(0x80, arg0->prim_r, arg0->prim_g, arg0->prim_b, arg0->prim_a, arg0->env_r, arg0->env_g, arg0->env_b);
    Gfx_LoadMultiBlock4b(gWaterTexture[0x29], 0, 0, 4, 0x20, 0x20, 1, 1, 5, 5, 2, 0);
    func_814060D4(1, 1, 0x20, 0x20);
    Gfx_LoadMultiBlock4b(gWaterTexture[0x29], 0x100, 1, 4, 0x20, 0x20, 1, 1, 5, 5, 1, 0xF);
    func_81406168(-1, 1, 0x20, 0x20);
    func_81404A6C(D_8140E3B8);
}

void func_84330934(unk_D_8140E720* arg0, UNUSED CameraStruct* arg1) {
    func_814015A0(arg0->unk_2C.x, arg0->unk_2C.y, arg0->unk_94.z, arg0->unk_1C);

    gSPDisplayList(gDisplayListHead++, gDL_BaseUI);

    func_81405C70(arg0->prim_r, arg0->prim_g, arg0->prim_b, arg0->env_r, arg0->env_g, arg0->env_b, arg0->prim_a);
    func_8140441C(gWaterTexture[0x87], 0x20, 0x20);
    func_814060D4(0, 2, 0x20, 0x20);
    func_81404A6C(D_8140E3B8);
}

void func_84330A18(unk_D_8140E720* arg0, u8* arg1) {
    func_814015F8(arg0->unk_2C.x, arg0->unk_2C.y, arg0->unk_94.z, arg0->unk_1C);

    gSPDisplayList(gDisplayListHead++, gDL_BaseUI);

    func_81405C70(arg0->prim_r, arg0->prim_g, arg0->prim_b, arg0->env_r, arg0->env_g, arg0->env_b, arg0->prim_a);
    func_81405660(arg1, D_84385C80, 0x40, 0x40, 0x40, 0x40);
}

void func_84330AF0(unk_D_8140E720* arg0, UNUSED CameraStruct* arg1) {
    func_84330A18(arg0, gWaterTexture[0x19]);
}

void func_84330B18(unk_D_8140E720* arg0, UNUSED CameraStruct* arg1) {
    func_84330A18(arg0, gWaterTexture[0x5E]);
}

void func_84330B40(unk_D_8140E720* arg0, UNUSED CameraStruct* arg1) {
    gSPDisplayList(gDisplayListHead++, gDL_OverlayUI);
    gSPClearGeometryMode(gDisplayListHead++, G_CULL_BACK);

    func_8140437C(gWaterTexture[0x1A] + (arg0->unk_C7 << 9), 0x20, 0x20);
    func_81405C70(arg0->prim_r, arg0->prim_g, arg0->prim_b, arg0->env_r, arg0->env_g, arg0->env_b, arg0->prim_a);
    func_81404ABC(arg0->unk_2C, arg0->unk_94, arg0->unk_1C, gMatrix_UITransform);

    gSPSetGeometryMode(gDisplayListHead++, G_CULL_BACK);
}

void func_84330C70(unk_D_8140E720* arg0, UNUSED CameraStruct* arg1) {
    gSPDisplayList(gDisplayListHead++, D_8140DC00);
    gSPClearGeometryMode(gDisplayListHead++, G_CULL_BACK);

    Gfx_LoadTextureBlockRGBA16_Clamp(gWaterTexture[0x1C], 0x20, 0x20);
    func_81404ABC(arg0->unk_2C, arg0->unk_94, arg0->unk_1C, gMatrix_UITransform);

    gSPSetGeometryMode(gDisplayListHead++, G_CULL_BACK);
}

void func_84330D64(unk_D_8140E720* arg0, UNUSED CameraStruct* arg1) {
    gSPDisplayList(gDisplayListHead++, D_8140DC00);
    gSPClearGeometryMode(gDisplayListHead++, G_CULL_BACK);

    Gfx_LoadTextureBlockRGBA16_Clamp(gWaterTexture[0x1E], 0x20, 0x20);
    func_81404ABC(arg0->unk_2C, arg0->unk_94, arg0->unk_1C, gMatrix_UITransform);

    gSPSetGeometryMode(gDisplayListHead++, G_CULL_BACK);
}

void func_84330E58(unk_D_8140E720* arg0, UNUSED CameraStruct* arg1) {
    gSPDisplayList(gDisplayListHead++, D_8140DC00);
    gSPClearGeometryMode(gDisplayListHead++, G_CULL_BACK);

    Gfx_LoadTextureBlockRGBA16_Clamp(gWaterTexture[0xC3], 0x20, 0x20);
    func_81404ABC(arg0->unk_2C, arg0->unk_94, arg0->unk_1C, gMatrix_UITransform);

    gSPSetGeometryMode(gDisplayListHead++, G_CULL_BACK);
}

void func_84330F4C(unk_D_8140E720* arg0, UNUSED CameraStruct* arg1) {
    Vec3s sp40;

    gSPDisplayList(gDisplayListHead++, gDL_BaseUI);
    gSPClearGeometryMode(gDisplayListHead++, G_CULL_BACK);

    func_8140437C(gWaterTexture[0x1D], 0x20, 0x20);
    func_81405C70(arg0->prim_r, arg0->prim_g, arg0->prim_b, arg0->env_r, arg0->env_g, arg0->env_b, arg0->prim_a);
    sp40.x = arg0->unk_94.x + 0x4000;
    sp40.y = arg0->unk_94.y + 0x4000;
    sp40.z = arg0->unk_94.z;
    func_81404ABC(arg0->unk_2C, sp40, arg0->unk_1C, gMatrix_UITransform);

    gSPSetGeometryMode(gDisplayListHead++, G_CULL_BACK);
}

void func_84331094(UNUSED unk_D_8140E720* arg0, UNUSED CameraStruct* arg1) {
}

void RenderTimerDigits(unk_D_8140E720* arg0, UNUSED CameraStruct* arg1) {
    gSPDisplayList(gDisplayListHead++, gDL_OverlayUI);

    func_8140437C(gWaterTexture[0x13] + (gTimerMask3 * 0x600), 0x20, 0x60);
    func_81405C70(arg0->prim_r, arg0->prim_g, arg0->prim_b, arg0->env_r, arg0->env_g, arg0->env_b, arg0->prim_a);

    gSPClearGeometryMode(gDisplayListHead++, G_CULL_BACK);

    func_81404B78(arg0->unk_2C, arg0->unk_94, arg0->unk_1C, D_84385CC0);

    gSPSetGeometryMode(gDisplayListHead++, G_CULL_BACK);
}

void RenderTimerDigitsAlt(unk_D_8140E720* arg0, UNUSED CameraStruct* arg1) {
    gSPDisplayList(gDisplayListHead++, gDL_OverlayUI);
    gSPClearGeometryMode(gDisplayListHead++, G_CULL_BACK);

    func_8140437C(gWaterTexture[0x13] + (gTimerMask3 * 0x600), 0x20, 0x60);
    func_81405C70(arg0->prim_r, arg0->prim_g, arg0->prim_b, arg0->env_r, arg0->env_g, arg0->env_b, arg0->prim_a);
    func_81404B78(arg0->unk_2C, arg0->unk_94, arg0->unk_1C, D_84385D00);

    gSPSetGeometryMode(gDisplayListHead++, G_CULL_BACK);
}

void func_84331314(unk_D_8140E720* arg0, UNUSED CameraStruct* arg1) {
    gSPDisplayList(gDisplayListHead++, gDL_OverlayUI);
    gSPClearGeometryMode(gDisplayListHead++, G_CULL_BACK);

    func_8140437C(gWaterTexture[0x13] + (gTimerMask3 * 0x600), 0x20, 0x60);
    func_81405C70(arg0->prim_r, arg0->prim_g, arg0->prim_b, arg0->env_r, arg0->env_g, arg0->env_b, arg0->prim_a);
    func_81404B78(arg0->unk_2C, arg0->unk_94, arg0->unk_1C, D_84385D40);

    gSPSetGeometryMode(gDisplayListHead++, G_CULL_BACK);
}

void RenderTimerNumber(unk_D_8140E720* arg0, CameraStruct* arg1) {
    gSPDisplayList(gDisplayListHead++, gDL_OverlayUI);
    gSPClearGeometryMode(gDisplayListHead++, G_CULL_BACK);

    func_8140437C(gWaterTexture[0x13] + (gTimerMask3 * 0x600), 0x20, 0x60);
    func_81405C70(arg0->prim_r, arg0->prim_g, arg0->prim_b, arg0->env_r, arg0->env_g, arg0->env_b, arg0->prim_a);
    func_81404F84(arg1, arg0->unk_2C, arg0->unk_1C, D_84385CC0, arg0->unk_94.z);

    gSPSetGeometryMode(gDisplayListHead++, G_CULL_BACK);
}

void func_8433157C(unk_D_8140E720* arg0, CameraStruct* arg1) {
    gSPDisplayList(gDisplayListHead++, gDL_OverlayUI);
    gSPClearGeometryMode(gDisplayListHead++, G_CULL_BACK);

    func_8140437C(gWaterTexture[0x13] + (gTimerMask3 * 0x600), 0x20, 0x60);
    func_81405C70(arg0->prim_r, arg0->prim_g, arg0->prim_b, arg0->env_r, arg0->env_g, arg0->env_b, arg0->prim_a);
    func_81404F84(arg1, arg0->unk_2C, arg0->unk_1C, D_84385D00, arg0->unk_94.z);

    gSPSetGeometryMode(gDisplayListHead++, G_CULL_BACK);
}

void func_843316A8(unk_D_8140E720* arg0, CameraStruct* arg1) {
    gSPDisplayList(gDisplayListHead++, gDL_OverlayUI);
    gSPClearGeometryMode(gDisplayListHead++, G_CULL_BACK);

    func_8140437C(gWaterTexture[0x13] + (gTimerMask3 * 0x600), 0x20, 0x60);
    func_81405C70(arg0->prim_r, arg0->prim_g, arg0->prim_b, arg0->env_r, arg0->env_g, arg0->env_b, arg0->prim_a);
    func_81404F84(arg1, arg0->unk_2C, arg0->unk_1C, D_84385D40, arg0->unk_94.z);

    gSPSetGeometryMode(gDisplayListHead++, G_CULL_BACK);
}

void func_843317D4(unk_D_8140E720* arg0, UNUSED CameraStruct* arg1) {
    gSPDisplayList(gDisplayListHead++, gDL_BaseUI);
    gSPClearGeometryMode(gDisplayListHead++, G_CULL_BACK);

    func_8140437C(gWaterTexture[0x1B], 0x10, 0x100);
    func_81405C70(0xFF, 0xFF, 0xFF, arg0->prim_r, arg0->prim_g, arg0->prim_b, arg0->prim_a);
    func_81404CF8(arg0->unk_2C, arg0->unk_94, arg0->unk_1C, D_8140DF78);

    gSPSetGeometryMode(gDisplayListHead++, G_CULL_BACK);
}

void func_843318F8(unk_D_8140E720* arg0, UNUSED CameraStruct* arg1) {
    gSPDisplayList(gDisplayListHead++, gDL_BaseUI);
    gSPClearGeometryMode(gDisplayListHead++, G_CULL_BACK);

    func_8140437C(gWaterTexture[0x1B], 0x10, 0x100);
    func_81405C70(0xFF, 0xFF, 0xFF, arg0->prim_r, arg0->prim_g, arg0->prim_b, arg0->prim_a);
    func_81404CF8(arg0->unk_2C, arg0->unk_94, arg0->unk_1C, D_8140DFA8);

    gSPSetGeometryMode(gDisplayListHead++, G_CULL_BACK);
}

void func_84331A1C(unk_D_8140E720* arg0, UNUSED CameraStruct* arg1) {
    gSPDisplayList(gDisplayListHead++, gDL_BaseUI);
    gSPClearGeometryMode(gDisplayListHead++, G_CULL_BACK);

    func_8140437C(gWaterTexture[0x13] + ((D_8140E6F0 & 7) * 0x600), 0x20, 0x60);
    func_81405C70(0xFF, 0xFF, 0xFF, 0, 0x64, 0xC8, 0xFF);
    func_81404ABC(arg0->unk_2C, arg0->unk_94, arg0->unk_1C, D_8140E238);

    gSPSetGeometryMode(gDisplayListHead++, G_CULL_BACK);
}

void func_84331B58(unk_D_8140E720* arg0, CameraStruct* arg1) {
    gSPDisplayList(gDisplayListHead++, gDL_OverlayUI);

    func_8140437C(gWaterTexture[0x18] + (arg0->unk_C7 << 9), 0x20, 0x20);
    func_81405C70(arg0->prim_r, arg0->prim_g, arg0->prim_b, arg0->env_r, arg0->env_g, arg0->env_b, arg0->prim_a);
    func_81404E4C(arg1, arg0->unk_2C, arg0->unk_1C, gMatrix_UITransform, arg0->unk_94.z);
}

void func_84331C34(unk_D_8140E720* arg0, UNUSED CameraStruct* arg1) {
    gSPDisplayList(gDisplayListHead++, gDL_OverlayUI);
    gSPClearGeometryMode(gDisplayListHead++, G_CULL_BACK);

    func_8140437C(gWaterTexture[0xA9], 0x20, 0x20);
    func_81405C70(arg0->prim_r, arg0->prim_g, arg0->prim_b, arg0->env_r, arg0->env_g, arg0->env_b, arg0->prim_a);
    func_81404C34(arg0->unk_2C, arg0->unk_94, arg0->unk_1C, arg0->unk_20, D_8140E098);

    gSPSetGeometryMode(gDisplayListHead++, G_CULL_BACK);
}

void func_84331D60(unk_D_8140E720* arg0, UNUSED CameraStruct* arg1) {
    RenderPrimColorRect(arg0->prim_r, arg0->prim_g, arg0->prim_b, arg0->prim_a);
}
