#include "src/ui_graphics.h"
#include "src/graphics_textures.h"
#include "src/text_system.h"
#include "src/gfx_buffer.h"
#include "src/gfx_rect.h"
#include "src/hal_libc.h"
#include "src/stage_loader.h"

extern u8 D_10025D0[];
extern u8 D_1002650[];
extern u8 D_10026D0[];
extern u8 D_1002750[];
extern u8 D_10027D0[];
extern u8 D_1002850[];
extern u8 D_10028D0[];
extern u8 D_1002950[];
extern u8 D_10029D0[];
extern u8 D_1002A50[];
extern u8 D_1002AD0[];
extern u8 D_1002B50[];
extern u8 D_1002BD0[];
extern u8 D_1002C50[];
extern u8 D_1002CD0[];
extern u8 D_1002D50[];
extern u8 D_1002DD0[];
extern u8 D_1002E50[];
extern u8 D_1002ED0[];
extern u8 D_1002F50[];
extern u8 D_1002FD0[];
extern u8 D_1003050[];
extern u8 D_10030D0[];
extern u8 D_1003150[];
extern u8 D_10031D0[];
extern u8 D_1003750[];
extern u8 D_1003890[];
extern u8 D_1003930[];
extern u8 D_10039F0[];
extern u8 D_1003AB0[];
extern u8 D_1003B70[];
extern u8 D_1003C30[];
extern u8 D_1003CF0[];
extern u8 D_1003DB0[];
extern u8 D_1003E50[];
extern u8 D_1003EA0[];
extern u8 D_1003EC8[];
extern u8 D_1003EF0[];
extern u8 D_2004000[];
extern u8 D_2004320[];

Gfx gMenuDL_BackgroundFill[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_OPA_SURF, G_RM_AA_OPA_SURF2),
    gsDPSetCombineMode(G_CC_PRIMITIVE, G_CC_PRIMITIVE),
    gsSPEndDisplayList(),
};

Gfx gPrefDL_Fill[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_XLU_SURF, G_RM_AA_XLU_SURF2),
    gsDPSetCombineMode(G_CC_PRIMITIVE, G_CC_PRIMITIVE),
    gsSPEndDisplayList(),
};

Gfx gDL_FillCycle[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_FILL),
    gsDPSetRenderMode(G_RM_NOOP, G_RM_NOOP2),
    gsSPEndDisplayList(),
};

Gfx gTransferPakErrorBorderDL[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_COPY),
    gsDPSetTexturePersp(G_TP_NONE),
    gsDPSetAlphaCompare(G_AC_THRESHOLD),
    gsDPSetRenderMode(G_RM_NOOP, G_RM_NOOP2),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsSPEndDisplayList(),
};

Gfx gPrefDL_Border[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetTexturePersp(G_TP_NONE),
    gsDPSetCombineLERP(TEXEL0, 0, ENVIRONMENT, 0, TEXEL0, 0, ENVIRONMENT, 0, TEXEL0, 0, ENVIRONMENT, 0, TEXEL0, 0,
                       ENVIRONMENT, 0),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetEnvColor(255, 255, 255, 255),
    gsSPClearGeometryMode(G_ZBUFFER | G_LIGHTING),
    gsSPEndDisplayList(),
};

Gfx gDL_XluBorder[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetTexturePersp(G_TP_NONE),
    gsDPSetCombineLERP(ENVIRONMENT, PRIMITIVE, TEXEL0, PRIMITIVE, TEXEL0, 0, ENVIRONMENT, 0, ENVIRONMENT, PRIMITIVE,
                       TEXEL0, PRIMITIVE, TEXEL0, 0, ENVIRONMENT, 0),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetEnvColor(255, 255, 255, 255),
    gsDPSetPrimColor(0, 0, 0, 0, 0, 255),
    gsSPClearGeometryMode(G_ZBUFFER | G_LIGHTING),
    gsSPEndDisplayList(),
};

Gfx gDL_PalettedIcon[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_2CYCLE),
    gsDPSetTexturePersp(G_TP_NONE),
    gsDPSetRenderMode(G_RM_PASS, G_RM_XLU_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, ENVIRONMENT, 0, TEXEL1, 0, ENVIRONMENT, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetEnvColor(255, 255, 255, 255),
    gsSPEndDisplayList(),
};

Gfx gDL_ExpBarPalCycle[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_2CYCLE),
    gsDPSetRenderMode(G_RM_PASS, G_RM_XLU_SURF2),
    gsDPSetCombineLERP(ENVIRONMENT, PRIMITIVE, TEXEL0, PRIMITIVE, TEXEL0, 0, ENVIRONMENT, 0, COMBINED, 0, TEXEL1, 0, 0,
                       0, 0, COMBINED),
    gsDPSetPrimColor(0, 0, 255, 255, 255, 255),
    gsSPEndDisplayList(),
};

Gfx gFontCharTableExtended[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetCombineLERP(TEXEL0, 0, ENVIRONMENT, 0, TEXEL0, 0, ENVIRONMENT, 0, TEXEL0, 0, ENVIRONMENT, 0, TEXEL0, 0,
                       ENVIRONMENT, 0),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsSPEndDisplayList(),
};

Gfx gPrefDL_End[] = {
    gsDPPipeSync(),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsSPEndDisplayList(),
};

static u8 gCharMapTable[] = {
    0x00, 0x34, 0x35, 0x0F, 0x00, 0x06, 0x0D, 0x37, 0x03, 0x04, 0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x10, 0x11,
    0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x3E, 0x42, 0x00, 0x3F, 0x00, 0x40, 0x00, 0x1A, 0x1B, 0x1C,
    0x1D, 0x1E, 0x1F, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E,
    0x2F, 0x30, 0x31, 0x32, 0x33, 0x07, 0x00, 0x08, 0x00, 0x00, 0x00, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4A, 0x4B,
    0x4C, 0x4D, 0x4E, 0x4F, 0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5A, 0x5B, 0x5C, 0x5D,
    0x5E, 0x00, 0x00, 0x00, 0x0E, 0x00, 0x00, 0x8F, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x02, 0x8D, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x8C, 0x00, 0x43, 0x44,
    0x41, 0x8E, 0x67, 0x66, 0x68, 0x00, 0x5F, 0x00, 0x00, 0x69, 0x6B, 0x6A, 0x6C, 0x6D, 0x7F, 0x7E, 0x80, 0x6F,
    0x00, 0x81, 0x83, 0x82, 0x6E, 0x00, 0x60, 0x36, 0x00, 0x70, 0x84, 0x71, 0x61, 0x00, 0x00, 0x65, 0x73, 0x72,
    0x74, 0x00, 0x62, 0x00, 0x00, 0x75, 0x77, 0x76, 0x78, 0x79, 0x86, 0x85, 0x87, 0x7B, 0x00, 0x88, 0x8A, 0x89,
    0x7A, 0x00, 0x63, 0x00, 0x00, 0x7C, 0x8B, 0x7D, 0x64, 0x00, 0x00, 0x00,
};

Gfx gDL_TextResetState[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPClearGeometryMode(G_ZBUFFER),
    gsDPSetTexturePersp(G_TP_NONE),
    gsDPSetCombineLERP(TEXEL0, 0, ENVIRONMENT, 0, TEXEL0, 0, ENVIRONMENT, 0, TEXEL0, 0, ENVIRONMENT, 0, TEXEL0, 0,
                       ENVIRONMENT, 0),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetEnvColor(255, 255, 255, 255),
    gsSPEndDisplayList(),
};

Gfx gDL_TextSetup[] = {
    gsDPPipeSync(),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsSPEndDisplayList(),
};

Gfx gDL_TextBegin[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_2CYCLE),
    gsDPSetRenderMode(G_RM_PASS, G_RM_XLU_SURF2),
    gsDPSetCombineLERP(ENVIRONMENT, PRIMITIVE, TEXEL1, PRIMITIVE, 0, 0, 0, 0, COMBINED, 0, TEXEL1, 0, TEXEL1, 0,
                       ENVIRONMENT, 0),
    gsDPSetPrimColor(0, 0, 255, 255, 255, 255),
    gsSPEndDisplayList(),
};

Gfx gDL_TextEnd[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetCombineLERP(TEXEL0, 0, ENVIRONMENT, 0, TEXEL0, 0, ENVIRONMENT, 0, TEXEL0, 0, ENVIRONMENT, 0, TEXEL0, 0,
                       ENVIRONMENT, 0),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsSPEndDisplayList(),
};

static s32 pad_D_8006F7C0[] = { 0, 0, 0, 0 };

void Ui_DrawTexturedRect8x8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u8* arg4) {
    s32 sp34 = (arg2 < 9) ? 0x400 : 0;
    s32 sp30 = (arg3 < 9) ? 0x400 : 0;

    gDPLoadTextureBlock(gDisplayListHead++, arg4, G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 8, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

    Gfx_DrawTexturedRectClipped(arg0, arg1, arg2, arg3, 0, 0, sp34, sp30, 0);
}

void Ui_DrawBorderStyleA(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    Ui_DrawTexturedRect8x8(arg0, arg1, 8, 8, D_10027D0);
    Ui_DrawTexturedRect8x8(arg0, (arg1 + arg3) - 8, 8, 8, D_1002850);
    Ui_DrawTexturedRect8x8((arg0 + arg2) - 8, (arg1 + arg3) - 8, 8, 8, D_10028D0);
    Ui_DrawTexturedRect8x8((arg0 + arg2) - 8, arg1, 8, 8, D_1002950);

    if (arg2 > 16) {
        Ui_DrawTexturedRect8x8(arg0 + 8, arg1, arg2 - 0x10, 8, D_10025D0);
        Ui_DrawTexturedRect8x8(arg0 + 8, (arg1 + arg3) - 8, arg2 - 0x10, 8, D_1002650);
    }

    if (arg3 > 16) {
        Ui_DrawTexturedRect8x8(arg0, arg1 + 8, 8, arg3 - 0x10, D_10026D0);
        Ui_DrawTexturedRect8x8((arg0 + arg2) - 8, arg1 + 8, 8, arg3 - 0x10, D_1002750);
    }
}

void Ui_DrawBorderStyleB(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    Ui_DrawTexturedRect8x8(arg0, arg1, 8, 8, D_1002BD0);
    Ui_DrawTexturedRect8x8(arg0, (arg1 + arg3) - 8, 8, 8, D_1002C50);
    Ui_DrawTexturedRect8x8((arg0 + arg2) - 8, (arg1 + arg3) - 8, 8, 8, D_1002CD0);
    Ui_DrawTexturedRect8x8((arg0 + arg2) - 8, arg1, 8, 8, D_1002D50);

    if (arg2 > 16) {
        Ui_DrawTexturedRect8x8(arg0 + 8, arg1, arg2 - 0x10, 8, D_10029D0);
        Ui_DrawTexturedRect8x8(arg0 + 8, (arg1 + arg3) - 8, arg2 - 0x10, 8, D_1002A50);
    }

    if (arg3 > 16) {
        Ui_DrawTexturedRect8x8(arg0, arg1 + 8, 8, arg3 - 0x10, D_1002AD0);
        Ui_DrawTexturedRect8x8((arg0 + arg2) - 8, arg1 + 8, 8, arg3 - 0x10, D_1002B50);
    }
}

void Ui_DrawBorderStyleC(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    Ui_DrawTexturedRect8x8(arg0, arg1, 8, 8, D_1002FD0);
    Ui_DrawTexturedRect8x8(arg0, (arg1 + arg3) - 8, 8, 8, D_1003050);
    Ui_DrawTexturedRect8x8((arg0 + arg2) - 8, (arg1 + arg3) - 8, 8, 8, D_10030D0);
    Ui_DrawTexturedRect8x8((arg0 + arg2) - 8, arg1, 8, 8, D_1003150);

    if (arg2 > 16) {
        Ui_DrawTexturedRect8x8(arg0 + 8, arg1, arg2 - 0x10, 8, D_1002DD0);
        Ui_DrawTexturedRect8x8(arg0 + 8, (arg1 + arg3) - 8, arg2 - 0x10, 8, D_1002E50);
    }

    if (arg3 > 16) {
        Ui_DrawTexturedRect8x8(arg0, arg1 + 8, 8, arg3 - 0x10, D_1002ED0);
        Ui_DrawTexturedRect8x8((arg0 + arg2) - 8, arg1 + 8, 8, arg3 - 0x10, D_1002F50);
    }
}

void Ui_FillInsetRectangleA(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u16 arg4) {
    gSPDisplayList(gDisplayListHead++, gDL_FillCycle);
    gDPSetFillColor(gDisplayListHead++, (arg4 << 0x10) | arg4);

    if (StageContext_IsHighResolution() != 0) {
        gDPFillRectangle(gDisplayListHead++, arg0 + 7, arg1 + 7, (arg0 + arg2) - 8, (arg1 + arg3) - 8);
    } else {
        gDPFillRectangle(gDisplayListHead++, arg0 + 3, arg1 + 3, (arg0 + arg2) - 4, (arg1 + arg3) - 4);
    }
}

void Ui_FillInsetRectangleB(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u16 arg4) {
    gSPDisplayList(gDisplayListHead++, gDL_FillCycle);
    gDPSetFillColor(gDisplayListHead++, (arg4 << 0x10) | arg4);

    if (StageContext_IsHighResolution() != 0) {
        gDPFillRectangle(gDisplayListHead++, arg0 + 5, arg1 + 5, (arg0 + arg2) - 6, (arg1 + arg3) - 6);
    } else {
        gDPFillRectangle(gDisplayListHead++, arg0 + 3, arg1 + 3, (arg0 + arg2) - 4, (arg1 + arg3) - 4);
    }
}

void Ui_DrawGradientRectangle(s32 arg0, s32 arg1, s32 arg2, s32 arg3, Color_RGB8* arg4, Color_RGB8* arg5) {
    Vtx* temp_s2;
    FramebufferImage* temp_s1;
    Mtx* sp7C;
    Vp* sp78;

    temp_s1 = GfxImage_GetCurrent();
    temp_s2 = Gfx_AllocDisplayList(sizeof(Vtx) * 4);
    sp7C = Gfx_AllocDisplayList(sizeof(Mtx) * 1);
    sp78 = Gfx_AllocDisplayList(sizeof(Vp) * 1);

    Gfx_SetViewportDimensions(sp78, temp_s1->width, temp_s1->height);

    gSPViewport(gDisplayListHead++, (u32)sp78 & 0x1FFFFFFF);

    guOrtho(sp7C, 0.5f, temp_s1->width - 0.5f, temp_s1->height - 0.5f, 0.5f, -2.0f, 2.0f, 1.0f);
    Gfx_SetVertexAttributes(&temp_s2[0], arg0, arg1, -1, 0, 0, arg4->r, arg4->g, arg4->b, 0xFF);
    Gfx_SetVertexAttributes(&temp_s2[1], arg0 + arg2, arg1, -1, 0, 0, arg4->r, arg4->g, arg4->b, 0xFF);
    Gfx_SetVertexAttributes(&temp_s2[2], arg0, arg1 + arg3, -1, 0, 0, arg5->r, arg5->g, arg5->b, 0xFF);
    Gfx_SetVertexAttributes(&temp_s2[3], arg0 + arg2, arg1 + arg3, -1, 0, 0, arg5->r, arg5->g, arg5->b, 0xFF);

    gDPPipeSync(gDisplayListHead++);

    gDPSetCycleType(gDisplayListHead++, G_CYC_1CYCLE);
    gSPClearGeometryMode(gDisplayListHead++, G_ZBUFFER | G_LIGHTING);
    gDPSetCombineMode(gDisplayListHead++, G_CC_SHADE, G_CC_SHADE);
    gDPSetRenderMode(gDisplayListHead++, G_RM_OPA_SURF, G_RM_OPA_SURF2);
    gSPPerspNormalize(gDisplayListHead++, 0xFFFF);

    gSPMatrix(gDisplayListHead++, (u32)sp7C & 0x1FFFFFFF, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
    gSPMatrix(gDisplayListHead++, (u32)&gCamProjectionMatrix & 0x1FFFFFFF, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    gSPVertex(gDisplayListHead++, (u32)temp_s2 & 0x1FFFFFFF, 4, 0);
    gSP2Triangles(gDisplayListHead++, 0, 2, 3, 0, 0, 3, 1, 0);
}

void Ui_DrawBorderedPanel(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u16 arg4) {
    gSPDisplayList(gDisplayListHead++, gPrefDL_Border);

    if (StageContext_IsHighResolution() != 0) {
        Ui_DrawBorderStyleA(arg0, arg1, arg2, arg3);
    } else {
        Ui_DrawBorderStyleC(arg0, arg1, arg2, arg3);
    }

    if ((arg2 >= 0xF) && (arg3 >= 0xF)) {
        Ui_FillInsetRectangleA(arg0, arg1, arg2, arg3, arg4);
    }

    gSPDisplayList(gDisplayListHead++, gPrefDL_End);
}

void Ui_DrawGradientPanel(s32 arg0, s32 arg1, s32 arg2, s32 arg3, Color_RGB8* arg4, Color_RGB8* arg5) {
    if ((arg2 >= 0xF) && (arg3 >= 0xF)) {
        if (StageContext_IsHighResolution() != 0) {
            Ui_DrawGradientRectangle(arg0 + 6, arg1 + 6, arg2 - 0xC, arg3 - 0xC, arg4, arg5);
        } else {
            Ui_DrawGradientRectangle(arg0 + 2, arg1 + 2, arg2 - 4, arg3 - 4, arg4, arg5);
        }
    }

    gSPDisplayList(gDisplayListHead++, gPrefDL_Border);

    if (StageContext_IsHighResolution() != 0) {
        Ui_DrawBorderStyleA(arg0, arg1, arg2, arg3);
    } else {
        Ui_DrawBorderStyleC(arg0, arg1, arg2, arg3);
    }

    gSPDisplayList(gDisplayListHead++, gPrefDL_End);
}

void Ui_DrawBorderedPanelStyleB(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u16 arg4) {
    gSPDisplayList(gDisplayListHead++, gPrefDL_Border);

    if (StageContext_IsHighResolution() != 0) {
        Ui_DrawBorderStyleB(arg0, arg1, arg2, arg3);
    } else {
        Ui_DrawBorderStyleC(arg0, arg1, arg2, arg3);
    }

    if ((arg2 >= 0xF) && (arg3 >= 0xF)) {
        Ui_FillInsetRectangleB(arg0, arg1, arg2, arg3, arg4);
    }

    gSPDisplayList(gDisplayListHead++, gPrefDL_End);
}

void Ui_DrawBorderedPanelNoFill(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    gSPDisplayList(gDisplayListHead++, gPrefDL_Border);

    if (StageContext_IsHighResolution() != 0) {
        Ui_DrawBorderStyleA(arg0, arg1, arg2, arg3);
    } else {
        Ui_DrawBorderStyleC(arg0, arg1, arg2, arg3);
    }

    gSPDisplayList(gDisplayListHead++, gPrefDL_End);
}

void Ui_DrawTextureMarker(s32 arg0, s32 arg1) {
    if (StageContext_IsHighResolution() != 0) {
        gSPDisplayList(gDisplayListHead++, gTransferPakErrorBorderDL);
        Gfx_DrawTextureRgba16(arg0, arg1, 0x20, 0x16, D_10031D0, 0x20, 0x200000);
    } else {
        gSPDisplayList(gDisplayListHead++, gDL_PalettedIcon);
        Gfx_DrawTextureRgba16Ia8(arg0, arg1, 0xC, 0xA, D_1003750, D_1003890, 0x10, 0x100000);
    }

    gSPDisplayList(gDisplayListHead++, gPrefDL_End);
}

void Ui_DrawAnimatedTextureMarker(s16 arg0, s16 arg1) {
    static s16 D_8006F7D0 = 0;

    if (D_8006F7D0 < 6) {
        arg0 += D_8006F7D0;
    } else {
        arg0 = (arg0 - D_8006F7D0) + 0xC;
    }
    Ui_DrawTextureMarker(arg0, arg1);
    D_8006F7D0 = (D_8006F7D0 + 1) % 12;
}

static s32 pad_D_8006F7E0[3] = { 0 };
u8 gPmName_001[12] = "pmname_001";
u8 gPmName_002[12] = "pmname_002";
u8 gPmName_003[12] = "pmname_003";
u8 gPmName_004[12] = "pmname_004";
u8 gPmName_005[12] = "pmname_005";
u8 gPmName_006[12] = "pmname_006";
u8 gPmName_007[12] = "pmname_007";
u8 gPmName_008[12] = "pmname_008";
u8 gPmName_009[12] = "pmname_009";
u8 gPmName_010[12] = "pmname_010";
u8 gPmName_011[12] = "pmname_011";
u8 gPmName_012[12] = "pmname_012";
u8 gPmName_013[12] = "pmname_013";
u8 gPmName_014[12] = "pmname_014";
u8 gPmName_015[12] = "pmname_015";
u8 gPmName_016[12] = "pmname_016";
u8 gPmName_017[12] = "pmname_017";
u8 gPmName_018[12] = "pmname_018";
u8 gPmName_019[12] = "pmname_019";
u8 gPmName_020[12] = "pmname_020";
u8 gPmName_021[12] = "pmname_021";
u8 gPmName_022[12] = "pmname_022";
u8 gPmName_023[12] = "pmname_023";
u8 gPmName_024[12] = "pmname_024";
u8 gPmName_025[12] = "pmname_025";
u8 gPmName_026[12] = "pmname_026";
u8 gPmName_027[12] = "pmname_027";
u8 gPmName_028[12] = "pmname_028";
u8 gPmName_029[12] = "pmname_029";
u8 gPmName_030[12] = "pmname_030";
u8 gPmName_031[12] = "pmname_031";
u8 gPmName_032[12] = "pmname_032";
u8 gPmName_033[12] = "pmname_033";
u8 gPmName_034[12] = "pmname_034";
u8 gPmName_035[12] = "pmname_035";
u8 gPmName_036[12] = "pmname_036";
u8 gPmName_037[12] = "pmname_037";
u8 gPmName_038[12] = "pmname_038";
u8 gPmName_039[12] = "pmname_039";
u8 gPmName_040[12] = "pmname_040";
u8 gPmName_041[12] = "pmname_041";
u8 gPmName_042[12] = "pmname_042";
u8 gPmName_043[12] = "pmname_043";
u8 gPmName_044[12] = "pmname_044";
u8 gPmName_045[12] = "pmname_045";
u8 gPmName_046[12] = "pmname_046";
u8 gPmName_047[12] = "pmname_047";
u8 gPmName_048[12] = "pmname_048";
u8 gPmName_049[12] = "pmname_049";
u8 gPmName_050[12] = "pmname_050";
u8 gPmName_051[12] = "pmname_051";
u8 gPmName_052[12] = "pmname_052";
u8 gPmName_053[12] = "pmname_053";
u8 gPmName_054[12] = "pmname_054";
u8 gPmName_055[12] = "pmname_055";
u8 gPmName_056[12] = "pmname_056";
u8 gPmName_057[12] = "pmname_057";
u8 gPmName_058[12] = "pmname_058";
u8 gPmName_059[12] = "pmname_059";
u8 gPmName_060[12] = "pmname_060";
u8 gPmName_061[12] = "pmname_061";
u8 gPmName_062[12] = "pmname_062";
u8 gPmName_063[12] = "pmname_063";
u8 gPmName_064[12] = "pmname_064";
u8 gPmName_065[12] = "pmname_065";
u8 gPmName_066[12] = "pmname_066";
u8 gPmName_067[12] = "pmname_067";
u8 gPmName_068[12] = "pmname_068";
u8 gPmName_069[12] = "pmname_069";
u8 gPmName_070[12] = "pmname_070";
u8 gPmName_071[12] = "pmname_071";
u8 gPmName_072[12] = "pmname_072";
u8 gPmName_073[12] = "pmname_073";
u8 gPmName_074[12] = "pmname_074";
u8 gPmName_075[12] = "pmname_075";
u8 gPmName_076[12] = "pmname_076";
u8 gPmName_077[12] = "pmname_077";
u8 gPmName_078[12] = "pmname_078";
u8 gPmName_079[12] = "pmname_079";
u8 gPmName_080[12] = "pmname_080";
u8 gPmName_081[12] = "pmname_081";
u8 gPmName_082[12] = "pmname_082";
u8 gPmName_083[12] = "pmname_083";
u8 gPmName_084[12] = "pmname_084";
u8 gPmName_085[12] = "pmname_085";
u8 gPmName_086[12] = "pmname_086";
u8 gPmName_087[12] = "pmname_087";
u8 gPmName_088[12] = "pmname_088";
u8 gPmName_089[12] = "pmname_089";
u8 gPmName_090[12] = "pmname_090";
u8 gPmName_091[12] = "pmname_091";
u8 gPmName_092[12] = "pmname_092";
u8 gPmName_093[12] = "pmname_093";
u8 gPmName_094[12] = "pmname_094";
u8 gPmName_095[12] = "pmname_095";
u8 gPmName_096[12] = "pmname_096";
u8 gPmName_097[12] = "pmname_097";
u8 gPmName_098[12] = "pmname_098";
u8 gPmName_099[12] = "pmname_099";
u8 gPmName_100[12] = "pmname_100";
u8 gPmName_101[12] = "pmname_101";
u8 gPmName_102[12] = "pmname_102";
u8 gPmName_103[12] = "pmname_103";
u8 gPmName_104[12] = "pmname_104";
u8 gPmName_105[12] = "pmname_105";
u8 gPmName_106[12] = "pmname_106";
u8 gPmName_107[12] = "pmname_107";
u8 gPmName_108[12] = "pmname_108";
u8 gPmName_109[12] = "pmname_109";
u8 gPmName_110[12] = "pmname_110";
u8 gPmName_111[12] = "pmname_111";
u8 gPmName_112[12] = "pmname_112";
u8 gPmName_113[12] = "pmname_113";
u8 gPmName_114[12] = "pmname_114";
u8 gPmName_115[12] = "pmname_115";
u8 gPmName_116[12] = "pmname_116";
u8 gPmName_117[12] = "pmname_117";
u8 gPmName_118[12] = "pmname_118";
u8 gPmName_119[12] = "pmname_119";
u8 gPmName_120[12] = "pmname_120";
u8 gPmName_121[12] = "pmname_121";
u8 gPmName_122[12] = "pmname_122";
u8 gPmName_123[12] = "pmname_123";
u8 gPmName_124[12] = "pmname_124";
u8 gPmName_125[12] = "pmname_125";
u8 gPmName_126[12] = "pmname_126";
u8 gPmName_127[12] = "pmname_127";
u8 gPmName_128[12] = "pmname_128";
u8 gPmName_129[12] = "pmname_129";
u8 gPmName_130[12] = "pmname_130";
u8 gPmName_131[12] = "pmname_131";
u8 gPmName_132[12] = "pmname_132";
u8 gPmName_133[12] = "pmname_133";
u8 gPmName_134[12] = "pmname_134";
u8 gPmName_135[12] = "pmname_135";
u8 gPmName_136[12] = "pmname_136";
u8 gPmName_137[12] = "pmname_137";
u8 gPmName_138[12] = "pmname_138";
u8 gPmName_139[12] = "pmname_139";
u8 gPmName_140[12] = "pmname_140";
u8 gPmName_141[12] = "pmname_141";
u8 gPmName_142[12] = "pmname_142";
u8 gPmName_143[12] = "pmname_143";
u8 gPmName_144[12] = "pmname_144";
u8 gPmName_145[12] = "pmname_145";
u8 gPmName_146[12] = "pmname_146";
u8 gPmName_147[12] = "pmname_147";
u8 gPmName_148[12] = "pmname_148";
u8 gPmName_149[12] = "pmname_149";
u8 gPmName_150_151[24] = { 0x70, 0x6D, 0x6E, 0x61, 0x6D, 0x65, 0x5F, 0x31, 0x35, 0x30, 0, 0, 0x70, 0x6D, 0x6E, 0x61, 0x6D, 0x65, 0x5F, 0x31, 0x35, 0x31, 0, 0 };
u8 gPmName_152[12] = "pmname_152";
SpeciesDisplayParams gSpeciesDisplayTable[152] = { { 1, 0, 1270, (void*)gPmName_001, (u32)(void*)gPmName_001, 0x3D, 7, 69, -45, 70, 0x3C73E2, (u32)(void*)gPmName_001 }, { 2, 0, 839, (void*)gPmName_002, (u32)(void*)gPmName_002, 0x35, 0xA, 130, -40, 45, 0x3D0046, (u32)(void*)gPmName_002 }, { 3, 0, 509, (void*)gPmName_003, (u32)(void*)gPmName_003, 0x31, 0x14, 1000, -30, 40, 0x3CFFC4, (u32)(void*)gPmName_003 }, { 4, 0xA, 1583, (void*)gPmName_004, (u32)(void*)gPmName_004, 0x3D, 6, 85, -25, 20, 0x3C6C42, (u32)(void*)gPmName_004 }, { 5, 0, 957, (void*)gPmName_005, (u32)(void*)gPmName_005, 0x35, 0xB, 190, -10, 55, 0x3BFFEC, (u32)(void*)gPmName_005 }, { 6, 0, 620, (void*)gPmName_006, (u32)(void*)gPmName_006, 0x35, 0x11, 905, -20, 15, 0x3BEC31, (u32)(void*)gPmName_006 }, { 7, 0, 1910, (void*)gPmName_007, (u32)(void*)gPmName_007, 0x3D, 5, 90, -50, 30, 0x3C9800, (u32)(void*)gPmName_007 }, { 8, 0, 1060, (void*)gPmName_008, (u32)(void*)gPmName_008, 0x35, 0xA, 225, -50, 30, 0x3BEC00, (u32)(void*)gPmName_008 }, { 9, 0, 730, (void*)gPmName_009, (u32)(void*)gPmName_009, 0x35, 0x10, 855, -30, 35, 0x3C6BCE, (u32)(void*)gPmName_009 }, { 0xA, 0, 5017, (void*)gPmName_010, (u32)(void*)gPmName_010, 0x3D, 3, 29, -30, 80, 0x3C1814, (u32)(void*)gPmName_010 }, { 0xB, 0, 1490, (void*)gPmName_011, (u32)(void*)gPmName_011, 0x35, 7, 99, -20, 60, 0x3CB000, (u32)(void*)gPmName_011 }, { 0xC, 4, 997, (void*)gPmName_012, (u32)(void*)gPmName_012, 0x35, 0xB, 320, -40, 50, 0x3E8464, (u32)(void*)gPmName_012 }, { 0xD, 0, 3380, (void*)gPmName_013, (u32)(void*)gPmName_013, 0x3D, 3, 32, 0, 50, 0x3BF414, (u32)(void*)gPmName_013 }, { 0xE, 0, 1729, (void*)gPmName_014, (u32)(void*)gPmName_014, 0x35, 6, 100, -25, 40, 0x3C045A, (u32)(void*)gPmName_014 }, { 0xF, 0, 910, (void*)gPmName_015, (u32)(void*)gPmName_015, 0x37, 0xA, 295, -20, 50, 0x3FC400, (u32)(void*)gPmName_015 }, { 0x10, 0, 3400, (void*)gPmName_016, (u32)(void*)gPmName_016, 0x3D, 3, 18, -30, 30, 0x3C7FF6, (u32)(void*)gPmName_016 }, { 0x11, 0, 900, (void*)gPmName_017, (u32)(void*)gPmName_017, 0x35, 0xB, 300, -30, 30, 0x3C401E, (u32)(void*)gPmName_017 }, { 0x12, 8, 693, (void*)gPmName_018, (u32)(void*)gPmName_018, 0x35, 0xF, 395, -35, 20, 0x3C6BEC, (u32)(void*)gPmName_018 }, { 0x13, 0, 1960, (void*)gPmName_019, (u32)(void*)gPmName_019, 0x3D, 3, 35, -40, 60, 0x3C8800, (u32)(void*)gPmName_019 }, { 0x14, 0, 1280, (void*)gPmName_020, (u32)(void*)gPmName_020, 0x35, 7, 185, -30, 30, 0x3C8400, (u32)(void*)gPmName_020 }, { 0x15, 0, 3090, (void*)gPmName_021, (u32)(void*)gPmName_021, 0x3D, 3, 20, -30, 20, 0x3C53E2, (u32)(void*)gPmName_021 }, { 0x16, 0x12, 897, (void*)gPmName_022, (u32)(void*)gPmName_022, 0x37, 0xC, 380, -25, 30, 0x3ECBA6, (u32)(void*)gPmName_022 }, { 0x17, 0, 1779, (void*)gPmName_023, (u32)(void*)gPmName_023, 0x3D, 0x14, 69, -30, 40, 0x3D0032, (u32)(void*)gPmName_023 }, { 0x18, 0, 730, (void*)gPmName_024, (u32)(void*)gPmName_024, 0x35, 0x23, 650, -70, 30, 0x3BC81E, (u32)(void*)gPmName_024 }, { 0x19, 0, 2400, (void*)gPmName_025, (u32)(void*)gPmName_025, 0x3F, 4, 60, -15, 25, 0x3BCC28, (u32)(void*)gPmName_025 }, { 0x1A, 0, 1350, (void*)gPmName_026, (u32)(void*)gPmName_026, 0x35, 8, 300, -15, 25, 0x3C4C00, (u32)(void*)gPmName_026 }, { 0x1B, 0, 1599, (void*)gPmName_027, (u32)(void*)gPmName_027, 0x3D, 6, 120, -40, 40, 0x3C9400, (u32)(void*)gPmName_027 }, { 0x1C, 0, 1040, (void*)gPmName_028, (u32)(void*)gPmName_028, 0x35, 0xA, 295, -20, 25, 0x3C2C46, (u32)(void*)gPmName_028 }, { 0x1D, 0, 2130, (void*)gPmName_029, (u32)(void*)gPmName_029, 0x3D, 4, 70, -60, 70, 0x3C1C32, (u32)(void*)gPmName_029 }, { 0x1E, 0, 1135, (void*)gPmName_030, (u32)(void*)gPmName_030, 0x35, 8, 200, -80, 80, 0x3C942D, (u32)(void*)gPmName_030 }, { 0x1F, 0, 795, (void*)gPmName_031, (u32)(void*)gPmName_031, 0x37, 0xD, 600, -60, 80, 0x3C43EC, (u32)(void*)gPmName_031 }, { 0x20, 0, 1550, (void*)gPmName_032, (u32)(void*)gPmName_032, 0x3D, 5, 90, -70, 20, 0x3D2FD8, (u32)(void*)gPmName_032 }, { 0x21, 0, 1100, (void*)gPmName_033, (u32)(void*)gPmName_033, 0x35, 9, 195, -70, 20, 0x3D57CE, (u32)(void*)gPmName_033 }, { 0x22, 0, 860, (void*)gPmName_034, (u32)(void*)gPmName_034, 0x37, 0xE, 620, -50, 30, 0x3C6F9C, (u32)(void*)gPmName_034 }, { 0x23, 0x15, 1540, (void*)gPmName_035, (u32)(void*)gPmName_035, 0x3D, 6, 75, -40, 50, 0x3BF428, (u32)(void*)gPmName_035 }, { 0x24, 0, 685, (void*)gPmName_036, (u32)(void*)gPmName_036, 0x35, 0xD, 400, -40, 50, 0x3B8400, (u32)(void*)gPmName_036 }, { 0x25, 0, 1523, (void*)gPmName_037, (u32)(void*)gPmName_037, 0x3D, 6, 99, -30, 35, 0x3C0C14, (u32)(void*)gPmName_037 }, { 0x26, 0, 950, (void*)gPmName_038, (u32)(void*)gPmName_038, 0x35, 0xB, 199, -30, 50, 0x3BBC00, (u32)(void*)gPmName_038 }, { 0x27, 0, 1620, (void*)gPmName_039, (u32)(void*)gPmName_039, 0x3D, 5, 55, -40, 40, 0x3CDBF6, (u32)(void*)gPmName_039 }, { 0x28, 0, 800, (void*)gPmName_040, (u32)(void*)gPmName_040, 0x35, 0xA, 120, -40, 40, 0x3BE7E2, (u32)(void*)gPmName_040 }, { 0x29, 0, 1080, (void*)gPmName_041, (u32)(void*)gPmName_041, 0x3D, 8, 75, -30, 30, 0x33280A, (u32)(void*)gPmName_041 }, { 0x2A, 0, 730, (void*)gPmName_042, (u32)(void*)gPmName_042, 0x35, 0x10, 550, -25, 30, 0x3C5400, (u32)(void*)gPmName_042 }, { 0x2B, 0xB, 1860, (void*)gPmName_043, (u32)(void*)gPmName_043, 0x3D, 5, 54, -40, 70, 0x3C2C28, (u32)(void*)gPmName_043 }, { 0x2C, 0, 1190, (void*)gPmName_044, (u32)(void*)gPmName_044, 0x35, 8, 86, -40, 65, 0x3C6000, (u32)(void*)gPmName_044 }, { 0x2D, 0, 637, (void*)gPmName_045, (u32)(void*)gPmName_045, 0x35, 0xC, 186, -25, 60, 0x3C5FEC, (u32)(void*)gPmName_045 }, { 0x2E, 0, 2160, (void*)gPmName_046, (u32)(void*)gPmName_046, 0x3D, 3, 54, -20, 30, 0x3D13EC, (u32)(void*)gPmName_046 }, { 0x2F, 0, 950, (void*)gPmName_047, (u32)(void*)gPmName_047, 0x35, 0xA, 295, -20, 35, 0x3CCBE2, (u32)(void*)gPmName_047 }, { 0x30, 0, 740, (void*)gPmName_048, (u32)(void*)gPmName_048, 0x35, 0xA, 300, -60, 60, 0x3CABEC, (u32)(void*)gPmName_048 }, { 0x31, 2, 763, (void*)gPmName_049, (u32)(void*)gPmName_049, 0x35, 0xF, 125, -60, 100, 0x3E9C18, (u32)(void*)gPmName_049 }, { 0x32, 0, 4000, (void*)gPmName_050, (u32)(void*)gPmName_050, 0x3D, 2, 8, -20, 35, 0x3D6800, (u32)(void*)gPmName_050 }, { 0x33, 0, 1150, (void*)gPmName_051, (u32)(void*)gPmName_051, 0x33, 7, 333, -20, 35, 0x3D1000, (u32)(void*)gPmName_051 }, { 0x34, 0, 2400, (void*)gPmName_052, (u32)(void*)gPmName_052, 0x3D, 4, 42, -40, 35, 0x3C2C00, (u32)(void*)gPmName_052 }, { 0x35, 0, 1040, (void*)gPmName_053, (u32)(void*)gPmName_053, 0x35, 0xA, 320, -20, 50, 0x3DB01E, (u32)(void*)gPmName_053 }, { 0x36, 0, 1230, (void*)gPmName_054, (u32)(void*)gPmName_054, 0x3D, 8, 196, -20, 30, 0x3C6800, (u32)(void*)gPmName_054 }, { 0x37, 0, 701, (void*)gPmName_055, (u32)(void*)gPmName_055, 0x35, 0x11, 766, -60, 50, 0x3C3800, (u32)(void*)gPmName_055 }, { 0x38, 0, 1600, (void*)gPmName_056, (u32)(void*)gPmName_056, 0x35, 5, 280, -35, 30, 0x3CD400, (u32)(void*)gPmName_056 }, { 0x39, 0, 880, (void*)gPmName_057, (u32)(void*)gPmName_057, 0x37, 0xA, 320, -35, 40, 0x3C5BE2, (u32)(void*)gPmName_057 }, { 0x3A, 0, 1350, (void*)gPmName_058, (u32)(void*)gPmName_058, 0x3D, 7, 190, -35, 10, 0x3C7432, (u32)(void*)gPmName_058 }, { 0x3B, 0, 491, (void*)gPmName_059, (u32)(void*)gPmName_059, 0x37, 0x13, 1550, -30, 20, 0x3C8C64, (u32)(void*)gPmName_059 }, { 0x3C, 0, 1300, (void*)gPmName_060, (u32)(void*)gPmName_060, 0x3D, 6, 124, -50, 50, 0x3D1FD8, (u32)(void*)gPmName_060 }, { 0x3D, 0, 930, (void*)gPmName_061, (u32)(void*)gPmName_061, 0x35, 0xA, 200, -50, 50, 0x3CA3EC, (u32)(void*)gPmName_061 }, { 0x3E, 0x41, 725, (void*)gPmName_062, (u32)(void*)gPmName_062, 0x35, 0xD, 540, -50, 50, 0x3C2FCE, (u32)(void*)gPmName_062 }, { 0x3F, 0, 1400, (void*)gPmName_063, (u32)(void*)gPmName_063, 0x3D, 9, 195, -20, 30, 0x3D83D8, (u32)(void*)gPmName_063 }, { 0x40, 0, 850, (void*)gPmName_064, (u32)(void*)gPmName_064, 0x35, 0xD, 565, -30, 30, 0x3C97CE, (u32)(void*)gPmName_064 }, { 0x41, 0, 733, (void*)gPmName_065, (u32)(void*)gPmName_065, 0x33, 0xF, 480, -30, 30, 0x3C1000, (u32)(void*)gPmName_065 }, { 0x42, 0, 1510, (void*)gPmName_066, (u32)(void*)gPmName_066, 0x3D, 8, 195, -40, 60, 0xFDBC3BD8, (u32)(void*)gPmName_066 }, { 0x43, 0, 882, (void*)gPmName_067, (u32)(void*)gPmName_067, 0x35, 0xF, 705, -70, 60, 0x3C67CE, (u32)(void*)gPmName_067 }, { 0x44, 0, 750, (void*)gPmName_068, (u32)(void*)gPmName_068, 0x37, 0x10, 1300, -70, 80, 0x3BCC00, (u32)(void*)gPmName_068 }, { 0x45, 0, 1761, (void*)gPmName_069, (u32)(void*)gPmName_069, 0x3D, 7, 40, -20, 25, 0x3B7028, (u32)(void*)gPmName_069 }, { 0x46, 0x23, 929, (void*)gPmName_070, (u32)(void*)gPmName_070, 0x35, 0xA, 64, -25, 40, 0x39A800, (u32)(void*)gPmName_070 }, { 0x47, 0, 550, (void*)gPmName_071, (u32)(void*)gPmName_071, 0x35, 0x11, 155, -30, 30, 0x6400, (u32)(void*)gPmName_071 }, { 0x48, 0, 909, (void*)gPmName_072, (u32)(void*)gPmName_072, 0x35, 9, 455, -40, 40, 0x14000, (u32)(void*)gPmName_072 }, { 0x49, 0, 620, (void*)gPmName_073, (u32)(void*)gPmName_073, 0x35, 0x10, 550, -40, 40, 0xF000, (u32)(void*)gPmName_073 }, { 0x4A, 0, 1090, (void*)gPmName_074, (u32)(void*)gPmName_074, 0x3D, 4, 200, -180, 180, 0x38D000, (u32)(void*)gPmName_074 }, { 0x4B, 0, 800, (void*)gPmName_075, (u32)(void*)gPmName_075, 0x35, 0xA, 1050, -180, 180, 0x3D23B0, (u32)(void*)gPmName_075 }, { 0x4C, 0, 700, (void*)gPmName_076, (u32)(void*)gPmName_076, 0x33, 0xE, 3000, -50, 20, 0x3C8BE7, (u32)(void*)gPmName_076 }, { 0x4D, 3, 880, (void*)gPmName_077, (u32)(void*)gPmName_077, 0x35, 0xA, 300, -25, 20, 0x3C2C3C, (u32)(void*)gPmName_077 }, { 0x4E, 0, 530, (void*)gPmName_078, (u32)(void*)gPmName_078, 0x35, 0x11, 950, -25, 20, 0x3C0432, (u32)(void*)gPmName_078 }, { 0x4F, 0, 767, (void*)gPmName_079, (u32)(void*)gPmName_079, 0x35, 0xC, 360, -40, 40, 0x3D2400, (u32)(void*)gPmName_079 }, { 0x50, 0, 590, (void*)gPmName_080, (u32)(void*)gPmName_080, 0x35, 0x10, 785, -40, 40, 0x3CEC64, (u32)(void*)gPmName_080 }, { 0x51, 0, 2087, (void*)gPmName_081, (u32)(void*)gPmName_081, 0x3D, 3, 60, -180, 180, 0x33A000, (u32)(void*)gPmName_081 }, { 0x52, 0, 1180, (void*)gPmName_082, (u32)(void*)gPmName_082, 0x33, 0xA, 600, -180, 180, 0xFC00, (u32)(void*)gPmName_082 }, { 0x53, 0, 1330, (void*)gPmName_083, (u32)(void*)gPmName_083, 0x3D, 8, 150, -30, 30, 0x3C43F6, (u32)(void*)gPmName_083 }, { 0x54, 0, 780, (void*)gPmName_084, (u32)(void*)gPmName_084, 0x35, 0xE, 392, -10, 40, 0x3C2C00, (u32)(void*)gPmName_084 }, { 0x55, 0, 614, (void*)gPmName_085, (u32)(void*)gPmName_085, 0x35, 0x12, 852, -10, 40, 0x3BBC00, (u32)(void*)gPmName_085 }, { 0x56, 0, 1107, (void*)gPmName_086, (u32)(void*)gPmName_086, 0x35, 0xB, 900, -40, 30, 0x3DFBD8, (u32)(void*)gPmName_086 }, { 0x57, 0, 1340, (void*)gPmName_087, (u32)(void*)gPmName_087, 0x35, 0x11, 1200, -10, 10, 0x5F67, (u32)(void*)gPmName_087 }, { 0x58, 0, 908, (void*)gPmName_088, (u32)(void*)gPmName_088, 0x35, 9, 300, -180, 180, 0x3D5800, (u32)(void*)gPmName_088 }, { 0x59, 0, 480, (void*)gPmName_089, (u32)(void*)gPmName_089, 0x35, 0xC, 300, -180, 180, 0x3D8C3C, (u32)(void*)gPmName_089 }, { 0x5A, 0, 2037, (void*)gPmName_090, (u32)(void*)gPmName_090, 0x3D, 3, 40, -70, 40, 0x3DBBD5, (u32)(void*)gPmName_090 }, { 0x5B, 0, 543, (void*)gPmName_091, (u32)(void*)gPmName_091, 0x37, 0xF, 1325, -70, 60, 0x3A3400, (u32)(void*)gPmName_091 }, { 0x5C, 0, 365, (void*)gPmName_092, (u32)(void*)gPmName_092, 0x3D, 0xD, 1, -80, 50, 0xA80A, (u32)(void*)gPmName_092 }, { 0x5D, 0, 460, (void*)gPmName_093, (u32)(void*)gPmName_093, 0x35, 0x10, 1, -70, 30, 0xE000, (u32)(void*)gPmName_093 }, { 0x5E, 0, 703, (void*)gPmName_094, (u32)(void*)gPmName_094, 0x33, 0xF, 405, -90, 30, 0x3C3000, (u32)(void*)gPmName_094 }, { 0x5F, 0x2D, 290, (void*)gPmName_095, (u32)(void*)gPmName_095, 0x37, 0x58, 2100, -180, 180, 0xE73CF7E2, (u32)(void*)gPmName_095 }, { 0x60, 0, 930, (void*)gPmName_096, (u32)(void*)gPmName_096, 0x35, 0xA, 324, -10, 30, 0x3C7814, (u32)(void*)gPmName_096 }, { 0x61, 0, 800, (void*)gPmName_097, (u32)(void*)gPmName_097, 0x33, 0x10, 756, -15, 30, 0x3BF3D8, (u32)(void*)gPmName_097 }, { 0x62, 0, 1100, (void*)gPmName_098, (u32)(void*)gPmName_098, 0x3D, 4, 65, -20, 30, 0x3E0FF6, (u32)(void*)gPmName_098 }, { 0x63, 0, 494, (void*)gPmName_099, (u32)(void*)gPmName_099, 0x35, 0xD, 600, -20, 25, 0x3D7C0F, (u32)(void*)gPmName_099 }, { 0x64, 0, 1840, (void*)gPmName_100, (u32)(void*)gPmName_100, 0x3D, 5, 104, -70, 10, 0x3C6400, (u32)(void*)gPmName_100 }, { 0x65, 0, 800, (void*)gPmName_101, (u32)(void*)gPmName_101, 0x33, 0xC, 666, -70, 10, 0x3C5000, (u32)(void*)gPmName_101 }, { 0x66, 0, 1160, (void*)gPmName_102, (u32)(void*)gPmName_102, 0x3D, 4, 25, -50, 40, 0x3E4400, (u32)(void*)gPmName_102 }, { 0x67, 0, 600, (void*)gPmName_103, (u32)(void*)gPmName_103, 0x33, 0x14, 1200, -30, 40, 0x3C2400, (u32)(void*)gPmName_103 }, { 0x68, 0, 2500, (void*)gPmName_104, (u32)(void*)gPmName_104, 0x3D, 4, 65, -25, 5, 0x3C2800, (u32)(void*)gPmName_104 }, { 0x69, 0, 1140, (void*)gPmName_105, (u32)(void*)gPmName_105, 0x35, 0xA, 450, -25, 5, 0x3C4000, (u32)(void*)gPmName_105 }, { 0x6A, 0, 723, (void*)gPmName_106, (u32)(void*)gPmName_106, 0x35, 0xF, 498, -20, 50, 0x3C5FE2, (u32)(void*)gPmName_106 }, { 0x6B, 0xA, 870, (void*)gPmName_107, (u32)(void*)gPmName_107, 0x35, 0xE, 502, -20, 50, 0x3BE800, (u32)(void*)gPmName_107 }, { 0x6C, 0x1C, 767, (void*)gPmName_108, (u32)(void*)gPmName_108, 0x35, 0xC, 655, -50, 30, 0x3C9C00, (u32)(void*)gPmName_108 }, { 0x6D, 0, 1500, (void*)gPmName_109, (u32)(void*)gPmName_109, 0x3D, 6, 10, -60, 90, 0x3FDC00, (u32)(void*)gPmName_109 }, { 0x6E, 0, 855, (void*)gPmName_110, (u32)(void*)gPmName_110, 0x35, 0xC, 95, -60, 90, 0x3FB800, (u32)(void*)gPmName_110 }, { 0x6F, 0, 860, (void*)gPmName_111, (u32)(void*)gPmName_111, 0x35, 0xA, 1150, -180, 180, 0x3D87EC, (u32)(void*)gPmName_111 }, { 0x70, 0, 523, (void*)gPmName_112, (u32)(void*)gPmName_112, 0x35, 0x13, 1200, -180, 180, 0x3C9832, (u32)(void*)gPmName_112 }, { 0x71, 0, 850, (void*)gPmName_113, (u32)(void*)gPmName_113, 0x33, 0xB, 346, -50, 60, 0x3C9C00, (u32)(void*)gPmName_113 }, { 0x72, 0, 1000, (void*)gPmName_114, (u32)(void*)gPmName_114, 0x35, 0xA, 350, -40, 20, 0x3C5400, (u32)(void*)gPmName_114 }, { 0x73, 0, 479, (void*)gPmName_115, (u32)(void*)gPmName_115, 0x33, 0x16, 800, -30, 50, 0x3CB85A, (u32)(void*)gPmName_115 }, { 0x74, 0, 2110, (void*)gPmName_116, (u32)(void*)gPmName_116, 0x3D, 4, 80, -40, 40, 0x3F2400, (u32)(void*)gPmName_116 }, { 0x75, 0, 827, (void*)gPmName_117, (u32)(void*)gPmName_117, 0x35, 0xC, 250, -30, 35, 0x3EBC00, (u32)(void*)gPmName_117 }, { 0x76, 0x16, 2340, (void*)gPmName_118, (u32)(void*)gPmName_118, 0x3D, 6, 150, -60, 40, 0x4CA0, (u32)(void*)gPmName_118 }, { 0x77, 2, 1000, (void*)gPmName_119, (u32)(void*)gPmName_119, 0x35, 0xD, 390, -50, 30, 0xDC32, (u32)(void*)gPmName_119 }, { 0x78, 0, 1430, (void*)gPmName_120, (u32)(void*)gPmName_120, 0x35, 8, 345, -10, 30, 0x3BF000, (u32)(void*)gPmName_120 }, { 0x79, 0, 1047, (void*)gPmName_121, (u32)(void*)gPmName_121, 0x33, 0xB, 800, -40, 50, 0x3BB800, (u32)(void*)gPmName_121 }, { 0x7A, 0, 895, (void*)gPmName_122, (u32)(void*)gPmName_122, 0x35, 0xD, 545, -30, 50, 0x3BDFE2, (u32)(void*)gPmName_122 }, { 0x7B, 0, 653, (void*)gPmName_123, (u32)(void*)gPmName_123, 0x37, 0xF, 560, -30, 50, 0x3CE324, (u32)(void*)gPmName_123 }, { 0x7C, 0, 691, (void*)gPmName_124, (u32)(void*)gPmName_124, 0x33, 0xE, 406, -10, 30, 0x3C6800, (u32)(void*)gPmName_124 }, { 0x7D, 0x17, 817, (void*)gPmName_125, (u32)(void*)gPmName_125, 0x35, 0xB, 300, -20, 30, 0x3C5000, (u32)(void*)gPmName_125 }, { 0x7E, 0, 700, (void*)gPmName_126, (u32)(void*)gPmName_126, 0x35, 0xD, 445, -15, 30, 0x3BFC64, (u32)(void*)gPmName_126 }, { 0x7F, 0, 703, (void*)gPmName_127, (u32)(void*)gPmName_127, 0x37, 0xF, 550, -60, 130, 0x3BE400, (u32)(void*)gPmName_127 }, { 0x80, 0, 670, (void*)gPmName_128, (u32)(void*)gPmName_128, 0x33, 0xE, 884, -10, 30, 0x3CE000, (u32)(void*)gPmName_128 }, { 0x81, 0, 1329, (void*)gPmName_129, (u32)(void*)gPmName_129, 0x3D, 9, 100, -30, 25, 0x3D2800, (u32)(void*)gPmName_129 }, { 0x82, 0, 380, (void*)gPmName_130, (u32)(void*)gPmName_130, 0x33, 0x41, 2350, -20, 50, 0x38B000, (u32)(void*)gPmName_130 }, { 0x83, 0, 400, (void*)gPmName_131, (u32)(void*)gPmName_131, 0x33, 0x19, 2200, -30, 20, 0x3AB014, (u32)(void*)gPmName_131 }, { 0x84, 0, 2200, (void*)gPmName_132, (u32)(void*)gPmName_132, 0x3B, 3, 40, -60, 20, 0x3D5800, (u32)(void*)gPmName_132 }, { 0x85, 0, 2600, (void*)gPmName_133, (u32)(void*)gPmName_133, 0x3D, 3, 65, -30, 30, 0x3D8C00, (u32)(void*)gPmName_133 }, { 0x86, 0, 980, (void*)gPmName_134, (u32)(void*)gPmName_134, 0x33, 0xA, 290, -20, 50, 0xF8BCCF6A, (u32)(void*)gPmName_134 }, { 0x87, 0, 1370, (void*)gPmName_135, (u32)(void*)gPmName_135, 0x33, 8, 245, -25, 20, 0x3C8FE2, (u32)(void*)gPmName_135 }, { 0x88, 0, 1148, (void*)gPmName_136, (u32)(void*)gPmName_136, 0x37, 9, 250, -20, 30, 0x3C401E, (u32)(void*)gPmName_136 }, { 0x89, 0, 960, (void*)gPmName_137, (u32)(void*)gPmName_137, 0x35, 8, 365, -40, 40, 0x366000, (u32)(void*)gPmName_137 }, { 0x8A, 0, 2240, (void*)gPmName_138, (u32)(void*)gPmName_138, 0x3D, 4, 75, -15, 60, 0x3D07AB, (u32)(void*)gPmName_138 }, { 0x8B, 0, 909, (void*)gPmName_139, (u32)(void*)gPmName_139, 0x35, 0xA, 350, -15, 60, 0x3CA7B5, (u32)(void*)gPmName_139 }, { 0x8C, 0, 2000, (void*)gPmName_140, (u32)(void*)gPmName_140, 0x3D, 5, 115, -20, 30, 0x3D5800, (u32)(void*)gPmName_140 }, { 0x8D, 0, 774, (void*)gPmName_141, (u32)(void*)gPmName_141, 0x35, 0xD, 405, -40, 50, 0x3C8C00, (u32)(void*)gPmName_141 }, { 0x8E, 0x22, 394, (void*)gPmName_142, (u32)(void*)gPmName_142, 0x37, 0x12, 590, -60, 60, 0x3E6800, (u32)(void*)gPmName_142 }, { 0x8F, 0, 510, (void*)gPmName_143, (u32)(void*)gPmName_143, 0x33, 0x15, 4600, -10, 60, 0x3D5829, (u32)(void*)gPmName_143 }, { 0x90, 0, 650, (void*)gPmName_144, (u32)(void*)gPmName_144, 0x31, 0x11, 554, -20, 30, 0x3BD400, (u32)(void*)gPmName_144 }, { 0x91, 6, 600, (void*)gPmName_145, (u32)(void*)gPmName_145, 0x31, 0x10, 526, -20, 25, 0x2800, (u32)(void*)gPmName_145 }, { 0x92, 0, 600, (void*)gPmName_146, (u32)(void*)gPmName_146, 0x35, 0x14, 600, -20, 20, 0x3BAC00, (u32)(void*)gPmName_146 }, { 0x93, 0, 1050, (void*)gPmName_147, (u32)(void*)gPmName_147, 0x3D, 0x12, 33, -40, 20, 0x1E3C7C00, (u32)(void*)gPmName_147 }, { 0x94, 0, 570, (void*)gPmName_148, (u32)(void*)gPmName_148, 0x35, 0x28, 165, -30, 10, 0x21FC3BC4, (u32)(void*)gPmName_148 }, { 0x95, 0, 473, (void*)gPmName_149, (u32)(void*)gPmName_149, 0x31, 0x16, 2100, -20, 25, 0x3C1FF6, (u32)(void*)gPmName_149 }, { 0x96, 0, 540, (void*)gPmName_150_151, (u32)(void*)gPmName_150_151, 0x20, 0x14, 1220, -70, 90, 0x3C2400, (u32)(void*)gPmName_150_151 }, { 0x97, 0, 2000, &D_8006FEE8, (u32)&D_8006FEE8, 0x20, 4, 40, -40, 60, 0x3F7400, (u32)&D_8006FEE8 }, { 0x98, 0, 1510, (void*)gPmName_152, -2147025164, 0, 0xA, 50, -50, 50, 0xFDBC3BD8, 0x8006FEF4 } };

void Ui_Draw20x20Icon(s32 arg0, s32 arg1, s32 arg2) {
    u8* var_t4;

    if (arg2 != 0) {
        var_t4 = D_2004320;
    } else {
        var_t4 = D_2004000;
    }

    gSPDisplayList(gDisplayListHead++, gTransferPakErrorBorderDL);
    gDPLoadTextureBlock(gDisplayListHead++, var_t4, G_IM_FMT_RGBA, G_IM_SIZ_16b, 20, 20, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    gSPTextureRectangle(gDisplayListHead++, arg0 << 2, arg1 << 2, (arg0 + 0x13) << 2, (arg1 + 0x13) << 2,
                        G_TX_RENDERTILE, 0, 0, 0x1000, 0x0400);
    gSPDisplayList(gDisplayListHead++, gPrefDL_End);
}

void BattleHud_DrawHpBarTexture(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    u8* spDC;
    s32 spD8 = arg2 - 4;
    s32 temp_lo = ((arg4 - arg3) * (arg2 - 4)) / arg4;
    s32 sp1C = (arg2 - temp_lo) - 4;

    if ((arg3 * 0x30) < (arg4 * 0xA)) {
        spDC = D_1003CF0;
    } else if ((arg3 * 0x30) < (arg4 * 0x1B)) {
        spDC = D_1003C30;
    } else {
        spDC = D_1003B70;
    }

    gSPDisplayList(gDisplayListHead++, gTransferPakErrorBorderDL);

    gDPLoadTextureBlock(gDisplayListHead++, D_1003930, G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 12, 0,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                        G_TX_NOLOD);
    gSPTextureRectangle(gDisplayListHead++, arg0 << 2, arg1 << 2, (arg0 + 1) << 2, (arg1 + 0xB) << 2, G_TX_RENDERTILE,
                        0, 0, 0x1000, 0x0400);

    gDPLoadTextureBlock(gDisplayListHead++, D_10039F0, G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 12, 0,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                        G_TX_NOLOD);
    gSPTextureRectangle(gDisplayListHead++, ((arg0 + spD8) + 2) << 2, arg1 << 2, ((arg0 + spD8) + 3) << 2,
                        (arg1 + 0xB) << 2, G_TX_RENDERTILE, 0, 0, 0x1000, 0x0400);

    if (sp1C > 0) {
        gDPLoadTextureBlock(gDisplayListHead++, spDC, G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 12, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                            G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
        gSPTextureRectangle(gDisplayListHead++, (arg0 + 2) << 2, arg1 << 2, (arg0 + sp1C + 1) << 2, (arg1 + 0xB) << 2,
                            G_TX_RENDERTILE, 0, 0, 0, 0x0400);
    }

    if (temp_lo > 0) {
        gDPLoadTextureBlock(gDisplayListHead++, D_1003AB0, G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 12, 0,
                            G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK,
                            G_TX_NOLOD, G_TX_NOLOD);
        gSPTextureRectangle(gDisplayListHead++, ((arg0 + sp1C) + 2) << 2, arg1 << 2, ((arg0 + sp1C) + temp_lo + 1) << 2,
                            (arg1 + 0xB) << 2, G_TX_RENDERTILE, 0, 0, 0, 0x0400);
    }

    gSPDisplayList(gDisplayListHead++, gPrefDL_End);
}

void BattleHud_DrawHpBar16x5(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    u8* spCC;
    s32 temp_lo = ((arg3 - arg2) * 0x30) / arg3;
    s32 sp14 = 0x30 - temp_lo;

    if ((arg2 * 0x30) < (arg3 * 0xA)) {
        spCC = D_1003EF0;
    } else if ((arg2 * 0x30) < (arg3 * 0x1B)) {
        spCC = D_1003EC8;
    } else {
        spCC = D_1003EA0;
    }

    gSPDisplayList(gDisplayListHead++, gPrefDL_Border);

    gDPLoadTextureBlock(gDisplayListHead++, D_1003DB0, G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 5, 0,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                        G_TX_NOLOD);
    gSPTextureRectangle(gDisplayListHead++, arg0 << 2, arg1 << 2, (arg0 + 0x10) << 2, (arg1 + 5) << 2, G_TX_RENDERTILE,
                        0, 0, 0x0400, 0x0400);
    gDPLoadTextureBlock(gDisplayListHead++, D_1003E50, G_IM_FMT_RGBA, G_IM_SIZ_16b, 4, 5, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    gSPTextureRectangle(gDisplayListHead++, (arg0 + 0x40) << 2, arg1 << 2, (arg0 + 0x41) << 2, (arg1 + 5) << 2,
                        G_TX_RENDERTILE, 0, 0, 0x0400, 0x0400);

    if (sp14 > 0) {
        gDPLoadTextureBlock(gDisplayListHead++, spCC, G_IM_FMT_RGBA, G_IM_SIZ_16b, 4, 5, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                            G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
        gSPTextureRectangle(gDisplayListHead++, (arg0 + 0x10) << 2, arg1 << 2, (arg0 + sp14 + 0x10) << 2,
                            (arg1 + 5) << 2, G_TX_RENDERTILE, 0, 0, 0, 0x0400);
    }

    if (temp_lo > 0) {
        gDPLoadTextureBlock(gDisplayListHead++, D_1003E78, G_IM_FMT_RGBA, G_IM_SIZ_16b, 4, 5, 0,
                            G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK,
                            G_TX_NOLOD, G_TX_NOLOD);
        gSPTextureRectangle(gDisplayListHead++, ((arg0 + sp14) + 0x10) << 2, arg1 << 2,
                            ((arg0 + sp14) + temp_lo + 0x10) << 2, (arg1 + 5) << 2, G_TX_RENDERTILE, 0, 0, 0, 0x0400);
    }

    gSPDisplayList(gDisplayListHead++, gPrefDL_End);
}

void Text_LoadNameTable(void) {
    char** temp_s2 = Text_GetStringTable(0x24);
    s32 i;

    for (i = 0; i < 151; i++) {
        HAL_Strcpy(gSpeciesDisplayTable[i].name, Text_GetString(NULL, 0, temp_s2, i));
    }
}
