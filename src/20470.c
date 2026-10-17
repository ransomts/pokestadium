#include "20470.h"
#include "src/1CF30.h"
#include "src/2E110.h"
#include "src/6A40.h"
#include "src/6BC0.h"
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

Gfx D_8006F470[] = {
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

Gfx D_8006F4C0[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_FILL),
    gsDPSetRenderMode(G_RM_NOOP, G_RM_NOOP2),
    gsSPEndDisplayList(),
};

Gfx D_8006F4E0[] = {
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

Gfx D_8006F558[] = {
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

Gfx D_8006F5A0[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_2CYCLE),
    gsDPSetTexturePersp(G_TP_NONE),
    gsDPSetRenderMode(G_RM_PASS, G_RM_XLU_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, ENVIRONMENT, 0, TEXEL1, 0, ENVIRONMENT, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetEnvColor(255, 255, 255, 255),
    gsSPEndDisplayList(),
};

Gfx D_8006F5D8[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_2CYCLE),
    gsDPSetRenderMode(G_RM_PASS, G_RM_XLU_SURF2),
    gsDPSetCombineLERP(ENVIRONMENT, PRIMITIVE, TEXEL0, PRIMITIVE, TEXEL0, 0, ENVIRONMENT, 0, COMBINED, 0, TEXEL1, 0, 0,
                       0, 0, COMBINED),
    gsDPSetPrimColor(0, 0, 255, 255, 255, 255),
    gsSPEndDisplayList(),
};

Gfx D_8006F608[] = {
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

static u8 D_8006F650[] = {
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

Gfx D_8006F710[] = {
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

Gfx D_8006F750[] = {
    gsDPPipeSync(),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsSPEndDisplayList(),
};

Gfx D_8006F768[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_2CYCLE),
    gsDPSetRenderMode(G_RM_PASS, G_RM_XLU_SURF2),
    gsDPSetCombineLERP(ENVIRONMENT, PRIMITIVE, TEXEL1, PRIMITIVE, 0, 0, 0, 0, COMBINED, 0, TEXEL1, 0, TEXEL1, 0,
                       ENVIRONMENT, 0),
    gsDPSetPrimColor(0, 0, 255, 255, 255, 255),
    gsSPEndDisplayList(),
};

Gfx D_8006F798[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetCombineLERP(TEXEL0, 0, ENVIRONMENT, 0, TEXEL0, 0, ENVIRONMENT, 0, TEXEL0, 0, ENVIRONMENT, 0, TEXEL0, 0,
                       ENVIRONMENT, 0),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsSPEndDisplayList(),
};

static s32 pad_D_8006F7C0[] = { 0, 0, 0, 0 };

void DrawTileTextureRect(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u8* arg4) {
    s32 sp34 = (arg2 < 9) ? 0x400 : 0;
    s32 sp30 = (arg3 < 9) ? 0x400 : 0;

    gDPLoadTextureBlock(gDisplayListHead++, arg4, G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 8, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

    Gfx_DrawTextureRect(arg0, arg1, arg2, arg3, 0, 0, sp34, sp30, 0);
}

void DrawWindowBorder(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    DrawTileTextureRect(arg0, arg1, 8, 8, D_10027D0);
    DrawTileTextureRect(arg0, (arg1 + arg3) - 8, 8, 8, D_1002850);
    DrawTileTextureRect((arg0 + arg2) - 8, (arg1 + arg3) - 8, 8, 8, D_10028D0);
    DrawTileTextureRect((arg0 + arg2) - 8, arg1, 8, 8, D_1002950);

    if (arg2 > 16) {
        DrawTileTextureRect(arg0 + 8, arg1, arg2 - 0x10, 8, D_10025D0);
        DrawTileTextureRect(arg0 + 8, (arg1 + arg3) - 8, arg2 - 0x10, 8, D_1002650);
    }

    if (arg3 > 16) {
        DrawTileTextureRect(arg0, arg1 + 8, 8, arg3 - 0x10, D_10026D0);
        DrawTileTextureRect((arg0 + arg2) - 8, arg1 + 8, 8, arg3 - 0x10, D_1002750);
    }
}

void func_8001FB40(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    DrawTileTextureRect(arg0, arg1, 8, 8, D_1002BD0);
    DrawTileTextureRect(arg0, (arg1 + arg3) - 8, 8, 8, D_1002C50);
    DrawTileTextureRect((arg0 + arg2) - 8, (arg1 + arg3) - 8, 8, 8, D_1002CD0);
    DrawTileTextureRect((arg0 + arg2) - 8, arg1, 8, 8, D_1002D50);

    if (arg2 > 16) {
        DrawTileTextureRect(arg0 + 8, arg1, arg2 - 0x10, 8, D_10029D0);
        DrawTileTextureRect(arg0 + 8, (arg1 + arg3) - 8, arg2 - 0x10, 8, D_1002A50);
    }

    if (arg3 > 16) {
        DrawTileTextureRect(arg0, arg1 + 8, 8, arg3 - 0x10, D_1002AD0);
        DrawTileTextureRect((arg0 + arg2) - 8, arg1 + 8, 8, arg3 - 0x10, D_1002B50);
    }
}

void DrawWindowBorderThin(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    DrawTileTextureRect(arg0, arg1, 8, 8, D_1002FD0);
    DrawTileTextureRect(arg0, (arg1 + arg3) - 8, 8, 8, D_1003050);
    DrawTileTextureRect((arg0 + arg2) - 8, (arg1 + arg3) - 8, 8, 8, D_10030D0);
    DrawTileTextureRect((arg0 + arg2) - 8, arg1, 8, 8, D_1003150);

    if (arg2 > 16) {
        DrawTileTextureRect(arg0 + 8, arg1, arg2 - 0x10, 8, D_1002DD0);
        DrawTileTextureRect(arg0 + 8, (arg1 + arg3) - 8, arg2 - 0x10, 8, D_1002E50);
    }

    if (arg3 > 16) {
        DrawTileTextureRect(arg0, arg1 + 8, 8, arg3 - 0x10, D_1002ED0);
        DrawTileTextureRect((arg0 + arg2) - 8, arg1 + 8, 8, arg3 - 0x10, D_1002F50);
    }
}

void FillRectWithColor(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u16 arg4) {
    gSPDisplayList(gDisplayListHead++, D_8006F4C0);
    gDPSetFillColor(gDisplayListHead++, (arg4 << 0x10) | arg4);

    if (func_80007A58() != 0) {
        gDPFillRectangle(gDisplayListHead++, arg0 + 7, arg1 + 7, (arg0 + arg2) - 8, (arg1 + arg3) - 8);
    } else {
        gDPFillRectangle(gDisplayListHead++, arg0 + 3, arg1 + 3, (arg0 + arg2) - 4, (arg1 + arg3) - 4);
    }
}

void FillRectWithColorInset(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u16 arg4) {
    gSPDisplayList(gDisplayListHead++, D_8006F4C0);
    gDPSetFillColor(gDisplayListHead++, (arg4 << 0x10) | arg4);

    if (func_80007A58() != 0) {
        gDPFillRectangle(gDisplayListHead++, arg0 + 5, arg1 + 5, (arg0 + arg2) - 6, (arg1 + arg3) - 6);
    } else {
        gDPFillRectangle(gDisplayListHead++, arg0 + 3, arg1 + 3, (arg0 + arg2) - 4, (arg1 + arg3) - 4);
    }
}

void DrawGradientRect(s32 arg0, s32 arg1, s32 arg2, s32 arg3, Color_RGB8* arg4, Color_RGB8* arg5) {
    Vtx* temp_s2;
    FramebufferImage* temp_s1;
    Mtx* sp7C;
    Vp* sp78;

    temp_s1 = Gfx_GetCurrentFramebuffer();
    temp_s2 = GfxAlloc(sizeof(Vtx) * 4);
    sp7C = GfxAlloc(sizeof(Mtx) * 1);
    sp78 = GfxAlloc(sizeof(Vp) * 1);

    SetViewport(sp78, temp_s1->width, temp_s1->height);

    gSPViewport(gDisplayListHead++, (u32)sp78 & 0x1FFFFFFF);

    guOrtho(sp7C, 0.5f, temp_s1->width - 0.5f, temp_s1->height - 0.5f, 0.5f, -2.0f, 2.0f, 1.0f);
    SetTileVertex(&temp_s2[0], arg0, arg1, -1, 0, 0, arg4->r, arg4->g, arg4->b, 0xFF);
    SetTileVertex(&temp_s2[1], arg0 + arg2, arg1, -1, 0, 0, arg4->r, arg4->g, arg4->b, 0xFF);
    SetTileVertex(&temp_s2[2], arg0, arg1 + arg3, -1, 0, 0, arg5->r, arg5->g, arg5->b, 0xFF);
    SetTileVertex(&temp_s2[3], arg0 + arg2, arg1 + arg3, -1, 0, 0, arg5->r, arg5->g, arg5->b, 0xFF);

    gDPPipeSync(gDisplayListHead++);

    gDPSetCycleType(gDisplayListHead++, G_CYC_1CYCLE);
    gSPClearGeometryMode(gDisplayListHead++, G_ZBUFFER | G_LIGHTING);
    gDPSetCombineMode(gDisplayListHead++, G_CC_SHADE, G_CC_SHADE);
    gDPSetRenderMode(gDisplayListHead++, G_RM_OPA_SURF, G_RM_OPA_SURF2);
    gSPPerspNormalize(gDisplayListHead++, 0xFFFF);

    gSPMatrix(gDisplayListHead++, (u32)sp7C & 0x1FFFFFFF, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
    gSPMatrix(gDisplayListHead++, (u32)&D_8006F010 & 0x1FFFFFFF, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    gSPVertex(gDisplayListHead++, (u32)temp_s2 & 0x1FFFFFFF, 4, 0);
    gSP2Triangles(gDisplayListHead++, 0, 2, 3, 0, 0, 3, 1, 0);
}

void DrawPanel(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u16 arg4) {
    gSPDisplayList(gDisplayListHead++, gPrefDL_Border);

    if (func_80007A58() != 0) {
        DrawWindowBorder(arg0, arg1, arg2, arg3);
    } else {
        DrawWindowBorderThin(arg0, arg1, arg2, arg3);
    }

    if ((arg2 >= 0xF) && (arg3 >= 0xF)) {
        FillRectWithColor(arg0, arg1, arg2, arg3, arg4);
    }

    gSPDisplayList(gDisplayListHead++, gPrefDL_End);
}

void DrawGradientPanel(s32 arg0, s32 arg1, s32 arg2, s32 arg3, Color_RGB8* arg4, Color_RGB8* arg5) {
    if ((arg2 >= 0xF) && (arg3 >= 0xF)) {
        if (func_80007A58() != 0) {
            DrawGradientRect(arg0 + 6, arg1 + 6, arg2 - 0xC, arg3 - 0xC, arg4, arg5);
        } else {
            DrawGradientRect(arg0 + 2, arg1 + 2, arg2 - 4, arg3 - 4, arg4, arg5);
        }
    }

    gSPDisplayList(gDisplayListHead++, gPrefDL_Border);

    if (func_80007A58() != 0) {
        DrawWindowBorder(arg0, arg1, arg2, arg3);
    } else {
        DrawWindowBorderThin(arg0, arg1, arg2, arg3);
    }

    gSPDisplayList(gDisplayListHead++, gPrefDL_End);
}

void DrawPanelAlt(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u16 arg4) {
    gSPDisplayList(gDisplayListHead++, gPrefDL_Border);

    if (func_80007A58() != 0) {
        func_8001FB40(arg0, arg1, arg2, arg3);
    } else {
        DrawWindowBorderThin(arg0, arg1, arg2, arg3);
    }

    if ((arg2 >= 0xF) && (arg3 >= 0xF)) {
        FillRectWithColorInset(arg0, arg1, arg2, arg3, arg4);
    }

    gSPDisplayList(gDisplayListHead++, gPrefDL_End);
}

void DrawSimplePanel(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    gSPDisplayList(gDisplayListHead++, gPrefDL_Border);

    if (func_80007A58() != 0) {
        DrawWindowBorder(arg0, arg1, arg2, arg3);
    } else {
        DrawWindowBorderThin(arg0, arg1, arg2, arg3);
    }

    gSPDisplayList(gDisplayListHead++, gPrefDL_End);
}

void DrawStatusIcon(s32 arg0, s32 arg1) {
    if (func_80007A58() != 0) {
        gSPDisplayList(gDisplayListHead++, D_8006F4E0);
        Gfx_DrawSpriteRGBA16(arg0, arg1, 0x20, 0x16, D_10031D0, 0x20, 0x200000);
    } else {
        gSPDisplayList(gDisplayListHead++, D_8006F5A0);
        func_8001D560(arg0, arg1, 0xC, 0xA, D_1003750, D_1003890, 0x10, 0x100000);
    }

    gSPDisplayList(gDisplayListHead++, gPrefDL_End);
}

void AnimateIconOffset(s16 arg0, s16 arg1) {
    static s16 D_8006F7D0 = 0;

    if (D_8006F7D0 < 6) {
        arg0 += D_8006F7D0;
    } else {
        arg0 = (arg0 - D_8006F7D0) + 0xC;
    }
    DrawStatusIcon(arg0, arg1);
    D_8006F7D0 = (D_8006F7D0 + 1) % 12;
}

static s32 pad_D_8006F7E0[3] = { 0 };
u8 D_8006F7E0[12] = "pmname_001";
u8 D_8006F7EC[12] = "pmname_002";
u8 D_8006F7F8[12] = "pmname_003";
u8 D_8006F804[12] = "pmname_004";
u8 D_8006F810[12] = "pmname_005";
u8 D_8006F81C[12] = "pmname_006";
u8 D_8006F828[12] = "pmname_007";
u8 D_8006F834[12] = "pmname_008";
u8 D_8006F840[12] = "pmname_009";
u8 D_8006F84C[12] = "pmname_010";
u8 D_8006F858[12] = "pmname_011";
u8 D_8006F864[12] = "pmname_012";
u8 D_8006F870[12] = "pmname_013";
u8 D_8006F87C[12] = "pmname_014";
u8 D_8006F888[12] = "pmname_015";
u8 D_8006F894[12] = "pmname_016";
u8 D_8006F8A0[12] = "pmname_017";
u8 D_8006F8AC[12] = "pmname_018";
u8 D_8006F8B8[12] = "pmname_019";
u8 D_8006F8C4[12] = "pmname_020";
u8 D_8006F8D0[12] = "pmname_021";
u8 D_8006F8DC[12] = "pmname_022";
u8 D_8006F8E8[12] = "pmname_023";
u8 D_8006F8F4[12] = "pmname_024";
u8 D_8006F900[12] = "pmname_025";
u8 D_8006F90C[12] = "pmname_026";
u8 D_8006F918[12] = "pmname_027";
u8 D_8006F924[12] = "pmname_028";
u8 D_8006F930[12] = "pmname_029";
u8 D_8006F93C[12] = "pmname_030";
u8 D_8006F948[12] = "pmname_031";
u8 D_8006F954[12] = "pmname_032";
u8 D_8006F960[12] = "pmname_033";
u8 D_8006F96C[12] = "pmname_034";
u8 D_8006F978[12] = "pmname_035";
u8 D_8006F984[12] = "pmname_036";
u8 D_8006F990[12] = "pmname_037";
u8 D_8006F99C[12] = "pmname_038";
u8 D_8006F9A8[12] = "pmname_039";
u8 D_8006F9B4[12] = "pmname_040";
u8 D_8006F9C0[12] = "pmname_041";
u8 D_8006F9CC[12] = "pmname_042";
u8 D_8006F9D8[12] = "pmname_043";
u8 D_8006F9E4[12] = "pmname_044";
u8 D_8006F9F0[12] = "pmname_045";
u8 D_8006F9FC[12] = "pmname_046";
u8 D_8006FA08[12] = "pmname_047";
u8 D_8006FA14[12] = "pmname_048";
u8 D_8006FA20[12] = "pmname_049";
u8 D_8006FA2C[12] = "pmname_050";
u8 D_8006FA38[12] = "pmname_051";
u8 D_8006FA44[12] = "pmname_052";
u8 D_8006FA50[12] = "pmname_053";
u8 D_8006FA5C[12] = "pmname_054";
u8 D_8006FA68[12] = "pmname_055";
u8 D_8006FA74[12] = "pmname_056";
u8 D_8006FA80[12] = "pmname_057";
u8 D_8006FA8C[12] = "pmname_058";
u8 D_8006FA98[12] = "pmname_059";
u8 D_8006FAA4[12] = "pmname_060";
u8 D_8006FAB0[12] = "pmname_061";
u8 D_8006FABC[12] = "pmname_062";
u8 D_8006FAC8[12] = "pmname_063";
u8 D_8006FAD4[12] = "pmname_064";
u8 D_8006FAE0[12] = "pmname_065";
u8 D_8006FAEC[12] = "pmname_066";
u8 D_8006FAF8[12] = "pmname_067";
u8 D_8006FB04[12] = "pmname_068";
u8 D_8006FB10[12] = "pmname_069";
u8 D_8006FB1C[12] = "pmname_070";
u8 D_8006FB28[12] = "pmname_071";
u8 D_8006FB34[12] = "pmname_072";
u8 D_8006FB40[12] = "pmname_073";
u8 D_8006FB4C[12] = "pmname_074";
u8 D_8006FB58[12] = "pmname_075";
u8 D_8006FB64[12] = "pmname_076";
u8 D_8006FB70[12] = "pmname_077";
u8 D_8006FB7C[12] = "pmname_078";
u8 D_8006FB88[12] = "pmname_079";
u8 D_8006FB94[12] = "pmname_080";
u8 D_8006FBA0[12] = "pmname_081";
u8 D_8006FBAC[12] = "pmname_082";
u8 D_8006FBB8[12] = "pmname_083";
u8 D_8006FBC4[12] = "pmname_084";
u8 D_8006FBD0[12] = "pmname_085";
u8 D_8006FBDC[12] = "pmname_086";
u8 D_8006FBE8[12] = "pmname_087";
u8 D_8006FBF4[12] = "pmname_088";
u8 D_8006FC00[12] = "pmname_089";
u8 D_8006FC0C[12] = "pmname_090";
u8 D_8006FC18[12] = "pmname_091";
u8 D_8006FC24[12] = "pmname_092";
u8 D_8006FC30[12] = "pmname_093";
u8 D_8006FC3C[12] = "pmname_094";
u8 D_8006FC48[12] = "pmname_095";
u8 D_8006FC54[12] = "pmname_096";
u8 D_8006FC60[12] = "pmname_097";
u8 D_8006FC6C[12] = "pmname_098";
u8 D_8006FC78[12] = "pmname_099";
u8 D_8006FC84[12] = "pmname_100";
u8 D_8006FC90[12] = "pmname_101";
u8 D_8006FC9C[12] = "pmname_102";
u8 D_8006FCA8[12] = "pmname_103";
u8 D_8006FCB4[12] = "pmname_104";
u8 D_8006FCC0[12] = "pmname_105";
u8 D_8006FCCC[12] = "pmname_106";
u8 D_8006FCD8[12] = "pmname_107";
u8 D_8006FCE4[12] = "pmname_108";
u8 D_8006FCF0[12] = "pmname_109";
u8 D_8006FCFC[12] = "pmname_110";
u8 D_8006FD08[12] = "pmname_111";
u8 D_8006FD14[12] = "pmname_112";
u8 D_8006FD20[12] = "pmname_113";
u8 D_8006FD2C[12] = "pmname_114";
u8 D_8006FD38[12] = "pmname_115";
u8 D_8006FD44[12] = "pmname_116";
u8 D_8006FD50[12] = "pmname_117";
u8 D_8006FD5C[12] = "pmname_118";
u8 D_8006FD68[12] = "pmname_119";
u8 D_8006FD74[12] = "pmname_120";
u8 D_8006FD80[12] = "pmname_121";
u8 D_8006FD8C[12] = "pmname_122";
u8 D_8006FD98[12] = "pmname_123";
u8 D_8006FDA4[12] = "pmname_124";
u8 D_8006FDB0[12] = "pmname_125";
u8 D_8006FDBC[12] = "pmname_126";
u8 D_8006FDC8[12] = "pmname_127";
u8 D_8006FDD4[12] = "pmname_128";
u8 D_8006FDE0[12] = "pmname_129";
u8 D_8006FDEC[12] = "pmname_130";
u8 D_8006FDF8[12] = "pmname_131";
u8 D_8006FE04[12] = "pmname_132";
u8 D_8006FE10[12] = "pmname_133";
u8 D_8006FE1C[12] = "pmname_134";
u8 D_8006FE28[12] = "pmname_135";
u8 D_8006FE34[12] = "pmname_136";
u8 D_8006FE40[12] = "pmname_137";
u8 D_8006FE4C[12] = "pmname_138";
u8 D_8006FE58[12] = "pmname_139";
u8 D_8006FE64[12] = "pmname_140";
u8 D_8006FE70[12] = "pmname_141";
u8 D_8006FE7C[12] = "pmname_142";
u8 D_8006FE88[12] = "pmname_143";
u8 D_8006FE94[12] = "pmname_144";
u8 D_8006FEA0[12] = "pmname_145";
u8 D_8006FEAC[12] = "pmname_146";
u8 D_8006FEB8[12] = "pmname_147";
u8 D_8006FEC4[12] = "pmname_148";
u8 D_8006FED0[12] = "pmname_149";
u8 D_8006FEDC[24] = { 0x70, 0x6D, 0x6E, 0x61, 0x6D, 0x65, 0x5F, 0x31, 0x35, 0x30, 0, 0, 0x70, 0x6D, 0x6E, 0x61, 0x6D, 0x65, 0x5F, 0x31, 0x35, 0x31, 0, 0 };
u8 D_8006FEF4[12] = "pmname_152";
unk_D_8006FF00 D_8006FF00[152] = { { 1, 0, 1270, (void*)D_8006F7E0, (u32)(void*)D_8006F7E0, 0x3D, 7, 69, -45, 70, 0x3C73E2, (u32)(void*)D_8006F7E0 }, { 2, 0, 839, (void*)D_8006F7EC, (u32)(void*)D_8006F7EC, 0x35, 0xA, 130, -40, 45, 0x3D0046, (u32)(void*)D_8006F7EC }, { 3, 0, 509, (void*)D_8006F7F8, (u32)(void*)D_8006F7F8, 0x31, 0x14, 1000, -30, 40, 0x3CFFC4, (u32)(void*)D_8006F7F8 }, { 4, 0xA, 1583, (void*)D_8006F804, (u32)(void*)D_8006F804, 0x3D, 6, 85, -25, 20, 0x3C6C42, (u32)(void*)D_8006F804 }, { 5, 0, 957, (void*)D_8006F810, (u32)(void*)D_8006F810, 0x35, 0xB, 190, -10, 55, 0x3BFFEC, (u32)(void*)D_8006F810 }, { 6, 0, 620, (void*)D_8006F81C, (u32)(void*)D_8006F81C, 0x35, 0x11, 905, -20, 15, 0x3BEC31, (u32)(void*)D_8006F81C }, { 7, 0, 1910, (void*)D_8006F828, (u32)(void*)D_8006F828, 0x3D, 5, 90, -50, 30, 0x3C9800, (u32)(void*)D_8006F828 }, { 8, 0, 1060, (void*)D_8006F834, (u32)(void*)D_8006F834, 0x35, 0xA, 225, -50, 30, 0x3BEC00, (u32)(void*)D_8006F834 }, { 9, 0, 730, (void*)D_8006F840, (u32)(void*)D_8006F840, 0x35, 0x10, 855, -30, 35, 0x3C6BCE, (u32)(void*)D_8006F840 }, { 0xA, 0, 5017, (void*)D_8006F84C, (u32)(void*)D_8006F84C, 0x3D, 3, 29, -30, 80, 0x3C1814, (u32)(void*)D_8006F84C }, { 0xB, 0, 1490, (void*)D_8006F858, (u32)(void*)D_8006F858, 0x35, 7, 99, -20, 60, 0x3CB000, (u32)(void*)D_8006F858 }, { 0xC, 4, 997, (void*)D_8006F864, (u32)(void*)D_8006F864, 0x35, 0xB, 320, -40, 50, 0x3E8464, (u32)(void*)D_8006F864 }, { 0xD, 0, 3380, (void*)D_8006F870, (u32)(void*)D_8006F870, 0x3D, 3, 32, 0, 50, 0x3BF414, (u32)(void*)D_8006F870 }, { 0xE, 0, 1729, (void*)D_8006F87C, (u32)(void*)D_8006F87C, 0x35, 6, 100, -25, 40, 0x3C045A, (u32)(void*)D_8006F87C }, { 0xF, 0, 910, (void*)D_8006F888, (u32)(void*)D_8006F888, 0x37, 0xA, 295, -20, 50, 0x3FC400, (u32)(void*)D_8006F888 }, { 0x10, 0, 3400, (void*)D_8006F894, (u32)(void*)D_8006F894, 0x3D, 3, 18, -30, 30, 0x3C7FF6, (u32)(void*)D_8006F894 }, { 0x11, 0, 900, (void*)D_8006F8A0, (u32)(void*)D_8006F8A0, 0x35, 0xB, 300, -30, 30, 0x3C401E, (u32)(void*)D_8006F8A0 }, { 0x12, 8, 693, (void*)D_8006F8AC, (u32)(void*)D_8006F8AC, 0x35, 0xF, 395, -35, 20, 0x3C6BEC, (u32)(void*)D_8006F8AC }, { 0x13, 0, 1960, (void*)D_8006F8B8, (u32)(void*)D_8006F8B8, 0x3D, 3, 35, -40, 60, 0x3C8800, (u32)(void*)D_8006F8B8 }, { 0x14, 0, 1280, (void*)D_8006F8C4, (u32)(void*)D_8006F8C4, 0x35, 7, 185, -30, 30, 0x3C8400, (u32)(void*)D_8006F8C4 }, { 0x15, 0, 3090, (void*)D_8006F8D0, (u32)(void*)D_8006F8D0, 0x3D, 3, 20, -30, 20, 0x3C53E2, (u32)(void*)D_8006F8D0 }, { 0x16, 0x12, 897, (void*)D_8006F8DC, (u32)(void*)D_8006F8DC, 0x37, 0xC, 380, -25, 30, 0x3ECBA6, (u32)(void*)D_8006F8DC }, { 0x17, 0, 1779, (void*)D_8006F8E8, (u32)(void*)D_8006F8E8, 0x3D, 0x14, 69, -30, 40, 0x3D0032, (u32)(void*)D_8006F8E8 }, { 0x18, 0, 730, (void*)D_8006F8F4, (u32)(void*)D_8006F8F4, 0x35, 0x23, 650, -70, 30, 0x3BC81E, (u32)(void*)D_8006F8F4 }, { 0x19, 0, 2400, (void*)D_8006F900, (u32)(void*)D_8006F900, 0x3F, 4, 60, -15, 25, 0x3BCC28, (u32)(void*)D_8006F900 }, { 0x1A, 0, 1350, (void*)D_8006F90C, (u32)(void*)D_8006F90C, 0x35, 8, 300, -15, 25, 0x3C4C00, (u32)(void*)D_8006F90C }, { 0x1B, 0, 1599, (void*)D_8006F918, (u32)(void*)D_8006F918, 0x3D, 6, 120, -40, 40, 0x3C9400, (u32)(void*)D_8006F918 }, { 0x1C, 0, 1040, (void*)D_8006F924, (u32)(void*)D_8006F924, 0x35, 0xA, 295, -20, 25, 0x3C2C46, (u32)(void*)D_8006F924 }, { 0x1D, 0, 2130, (void*)D_8006F930, (u32)(void*)D_8006F930, 0x3D, 4, 70, -60, 70, 0x3C1C32, (u32)(void*)D_8006F930 }, { 0x1E, 0, 1135, (void*)D_8006F93C, (u32)(void*)D_8006F93C, 0x35, 8, 200, -80, 80, 0x3C942D, (u32)(void*)D_8006F93C }, { 0x1F, 0, 795, (void*)D_8006F948, (u32)(void*)D_8006F948, 0x37, 0xD, 600, -60, 80, 0x3C43EC, (u32)(void*)D_8006F948 }, { 0x20, 0, 1550, (void*)D_8006F954, (u32)(void*)D_8006F954, 0x3D, 5, 90, -70, 20, 0x3D2FD8, (u32)(void*)D_8006F954 }, { 0x21, 0, 1100, (void*)D_8006F960, (u32)(void*)D_8006F960, 0x35, 9, 195, -70, 20, 0x3D57CE, (u32)(void*)D_8006F960 }, { 0x22, 0, 860, (void*)D_8006F96C, (u32)(void*)D_8006F96C, 0x37, 0xE, 620, -50, 30, 0x3C6F9C, (u32)(void*)D_8006F96C }, { 0x23, 0x15, 1540, (void*)D_8006F978, (u32)(void*)D_8006F978, 0x3D, 6, 75, -40, 50, 0x3BF428, (u32)(void*)D_8006F978 }, { 0x24, 0, 685, (void*)D_8006F984, (u32)(void*)D_8006F984, 0x35, 0xD, 400, -40, 50, 0x3B8400, (u32)(void*)D_8006F984 }, { 0x25, 0, 1523, (void*)D_8006F990, (u32)(void*)D_8006F990, 0x3D, 6, 99, -30, 35, 0x3C0C14, (u32)(void*)D_8006F990 }, { 0x26, 0, 950, (void*)D_8006F99C, (u32)(void*)D_8006F99C, 0x35, 0xB, 199, -30, 50, 0x3BBC00, (u32)(void*)D_8006F99C }, { 0x27, 0, 1620, (void*)D_8006F9A8, (u32)(void*)D_8006F9A8, 0x3D, 5, 55, -40, 40, 0x3CDBF6, (u32)(void*)D_8006F9A8 }, { 0x28, 0, 800, (void*)D_8006F9B4, (u32)(void*)D_8006F9B4, 0x35, 0xA, 120, -40, 40, 0x3BE7E2, (u32)(void*)D_8006F9B4 }, { 0x29, 0, 1080, (void*)D_8006F9C0, (u32)(void*)D_8006F9C0, 0x3D, 8, 75, -30, 30, 0x33280A, (u32)(void*)D_8006F9C0 }, { 0x2A, 0, 730, (void*)D_8006F9CC, (u32)(void*)D_8006F9CC, 0x35, 0x10, 550, -25, 30, 0x3C5400, (u32)(void*)D_8006F9CC }, { 0x2B, 0xB, 1860, (void*)D_8006F9D8, (u32)(void*)D_8006F9D8, 0x3D, 5, 54, -40, 70, 0x3C2C28, (u32)(void*)D_8006F9D8 }, { 0x2C, 0, 1190, (void*)D_8006F9E4, (u32)(void*)D_8006F9E4, 0x35, 8, 86, -40, 65, 0x3C6000, (u32)(void*)D_8006F9E4 }, { 0x2D, 0, 637, (void*)D_8006F9F0, (u32)(void*)D_8006F9F0, 0x35, 0xC, 186, -25, 60, 0x3C5FEC, (u32)(void*)D_8006F9F0 }, { 0x2E, 0, 2160, (void*)D_8006F9FC, (u32)(void*)D_8006F9FC, 0x3D, 3, 54, -20, 30, 0x3D13EC, (u32)(void*)D_8006F9FC }, { 0x2F, 0, 950, (void*)D_8006FA08, (u32)(void*)D_8006FA08, 0x35, 0xA, 295, -20, 35, 0x3CCBE2, (u32)(void*)D_8006FA08 }, { 0x30, 0, 740, (void*)D_8006FA14, (u32)(void*)D_8006FA14, 0x35, 0xA, 300, -60, 60, 0x3CABEC, (u32)(void*)D_8006FA14 }, { 0x31, 2, 763, (void*)D_8006FA20, (u32)(void*)D_8006FA20, 0x35, 0xF, 125, -60, 100, 0x3E9C18, (u32)(void*)D_8006FA20 }, { 0x32, 0, 4000, (void*)D_8006FA2C, (u32)(void*)D_8006FA2C, 0x3D, 2, 8, -20, 35, 0x3D6800, (u32)(void*)D_8006FA2C }, { 0x33, 0, 1150, (void*)D_8006FA38, (u32)(void*)D_8006FA38, 0x33, 7, 333, -20, 35, 0x3D1000, (u32)(void*)D_8006FA38 }, { 0x34, 0, 2400, (void*)D_8006FA44, (u32)(void*)D_8006FA44, 0x3D, 4, 42, -40, 35, 0x3C2C00, (u32)(void*)D_8006FA44 }, { 0x35, 0, 1040, (void*)D_8006FA50, (u32)(void*)D_8006FA50, 0x35, 0xA, 320, -20, 50, 0x3DB01E, (u32)(void*)D_8006FA50 }, { 0x36, 0, 1230, (void*)D_8006FA5C, (u32)(void*)D_8006FA5C, 0x3D, 8, 196, -20, 30, 0x3C6800, (u32)(void*)D_8006FA5C }, { 0x37, 0, 701, (void*)D_8006FA68, (u32)(void*)D_8006FA68, 0x35, 0x11, 766, -60, 50, 0x3C3800, (u32)(void*)D_8006FA68 }, { 0x38, 0, 1600, (void*)D_8006FA74, (u32)(void*)D_8006FA74, 0x35, 5, 280, -35, 30, 0x3CD400, (u32)(void*)D_8006FA74 }, { 0x39, 0, 880, (void*)D_8006FA80, (u32)(void*)D_8006FA80, 0x37, 0xA, 320, -35, 40, 0x3C5BE2, (u32)(void*)D_8006FA80 }, { 0x3A, 0, 1350, (void*)D_8006FA8C, (u32)(void*)D_8006FA8C, 0x3D, 7, 190, -35, 10, 0x3C7432, (u32)(void*)D_8006FA8C }, { 0x3B, 0, 491, (void*)D_8006FA98, (u32)(void*)D_8006FA98, 0x37, 0x13, 1550, -30, 20, 0x3C8C64, (u32)(void*)D_8006FA98 }, { 0x3C, 0, 1300, (void*)D_8006FAA4, (u32)(void*)D_8006FAA4, 0x3D, 6, 124, -50, 50, 0x3D1FD8, (u32)(void*)D_8006FAA4 }, { 0x3D, 0, 930, (void*)D_8006FAB0, (u32)(void*)D_8006FAB0, 0x35, 0xA, 200, -50, 50, 0x3CA3EC, (u32)(void*)D_8006FAB0 }, { 0x3E, 0x41, 725, (void*)D_8006FABC, (u32)(void*)D_8006FABC, 0x35, 0xD, 540, -50, 50, 0x3C2FCE, (u32)(void*)D_8006FABC }, { 0x3F, 0, 1400, (void*)D_8006FAC8, (u32)(void*)D_8006FAC8, 0x3D, 9, 195, -20, 30, 0x3D83D8, (u32)(void*)D_8006FAC8 }, { 0x40, 0, 850, (void*)D_8006FAD4, (u32)(void*)D_8006FAD4, 0x35, 0xD, 565, -30, 30, 0x3C97CE, (u32)(void*)D_8006FAD4 }, { 0x41, 0, 733, (void*)D_8006FAE0, (u32)(void*)D_8006FAE0, 0x33, 0xF, 480, -30, 30, 0x3C1000, (u32)(void*)D_8006FAE0 }, { 0x42, 0, 1510, (void*)D_8006FAEC, (u32)(void*)D_8006FAEC, 0x3D, 8, 195, -40, 60, 0xFDBC3BD8, (u32)(void*)D_8006FAEC }, { 0x43, 0, 882, (void*)D_8006FAF8, (u32)(void*)D_8006FAF8, 0x35, 0xF, 705, -70, 60, 0x3C67CE, (u32)(void*)D_8006FAF8 }, { 0x44, 0, 750, (void*)D_8006FB04, (u32)(void*)D_8006FB04, 0x37, 0x10, 1300, -70, 80, 0x3BCC00, (u32)(void*)D_8006FB04 }, { 0x45, 0, 1761, (void*)D_8006FB10, (u32)(void*)D_8006FB10, 0x3D, 7, 40, -20, 25, 0x3B7028, (u32)(void*)D_8006FB10 }, { 0x46, 0x23, 929, (void*)D_8006FB1C, (u32)(void*)D_8006FB1C, 0x35, 0xA, 64, -25, 40, 0x39A800, (u32)(void*)D_8006FB1C }, { 0x47, 0, 550, (void*)D_8006FB28, (u32)(void*)D_8006FB28, 0x35, 0x11, 155, -30, 30, 0x6400, (u32)(void*)D_8006FB28 }, { 0x48, 0, 909, (void*)D_8006FB34, (u32)(void*)D_8006FB34, 0x35, 9, 455, -40, 40, 0x14000, (u32)(void*)D_8006FB34 }, { 0x49, 0, 620, (void*)D_8006FB40, (u32)(void*)D_8006FB40, 0x35, 0x10, 550, -40, 40, 0xF000, (u32)(void*)D_8006FB40 }, { 0x4A, 0, 1090, (void*)D_8006FB4C, (u32)(void*)D_8006FB4C, 0x3D, 4, 200, -180, 180, 0x38D000, (u32)(void*)D_8006FB4C }, { 0x4B, 0, 800, (void*)D_8006FB58, (u32)(void*)D_8006FB58, 0x35, 0xA, 1050, -180, 180, 0x3D23B0, (u32)(void*)D_8006FB58 }, { 0x4C, 0, 700, (void*)D_8006FB64, (u32)(void*)D_8006FB64, 0x33, 0xE, 3000, -50, 20, 0x3C8BE7, (u32)(void*)D_8006FB64 }, { 0x4D, 3, 880, (void*)D_8006FB70, (u32)(void*)D_8006FB70, 0x35, 0xA, 300, -25, 20, 0x3C2C3C, (u32)(void*)D_8006FB70 }, { 0x4E, 0, 530, (void*)D_8006FB7C, (u32)(void*)D_8006FB7C, 0x35, 0x11, 950, -25, 20, 0x3C0432, (u32)(void*)D_8006FB7C }, { 0x4F, 0, 767, (void*)D_8006FB88, (u32)(void*)D_8006FB88, 0x35, 0xC, 360, -40, 40, 0x3D2400, (u32)(void*)D_8006FB88 }, { 0x50, 0, 590, (void*)D_8006FB94, (u32)(void*)D_8006FB94, 0x35, 0x10, 785, -40, 40, 0x3CEC64, (u32)(void*)D_8006FB94 }, { 0x51, 0, 2087, (void*)D_8006FBA0, (u32)(void*)D_8006FBA0, 0x3D, 3, 60, -180, 180, 0x33A000, (u32)(void*)D_8006FBA0 }, { 0x52, 0, 1180, (void*)D_8006FBAC, (u32)(void*)D_8006FBAC, 0x33, 0xA, 600, -180, 180, 0xFC00, (u32)(void*)D_8006FBAC }, { 0x53, 0, 1330, (void*)D_8006FBB8, (u32)(void*)D_8006FBB8, 0x3D, 8, 150, -30, 30, 0x3C43F6, (u32)(void*)D_8006FBB8 }, { 0x54, 0, 780, (void*)D_8006FBC4, (u32)(void*)D_8006FBC4, 0x35, 0xE, 392, -10, 40, 0x3C2C00, (u32)(void*)D_8006FBC4 }, { 0x55, 0, 614, (void*)D_8006FBD0, (u32)(void*)D_8006FBD0, 0x35, 0x12, 852, -10, 40, 0x3BBC00, (u32)(void*)D_8006FBD0 }, { 0x56, 0, 1107, (void*)D_8006FBDC, (u32)(void*)D_8006FBDC, 0x35, 0xB, 900, -40, 30, 0x3DFBD8, (u32)(void*)D_8006FBDC }, { 0x57, 0, 1340, (void*)D_8006FBE8, (u32)(void*)D_8006FBE8, 0x35, 0x11, 1200, -10, 10, 0x5F67, (u32)(void*)D_8006FBE8 }, { 0x58, 0, 908, (void*)D_8006FBF4, (u32)(void*)D_8006FBF4, 0x35, 9, 300, -180, 180, 0x3D5800, (u32)(void*)D_8006FBF4 }, { 0x59, 0, 480, (void*)D_8006FC00, (u32)(void*)D_8006FC00, 0x35, 0xC, 300, -180, 180, 0x3D8C3C, (u32)(void*)D_8006FC00 }, { 0x5A, 0, 2037, (void*)D_8006FC0C, (u32)(void*)D_8006FC0C, 0x3D, 3, 40, -70, 40, 0x3DBBD5, (u32)(void*)D_8006FC0C }, { 0x5B, 0, 543, (void*)D_8006FC18, (u32)(void*)D_8006FC18, 0x37, 0xF, 1325, -70, 60, 0x3A3400, (u32)(void*)D_8006FC18 }, { 0x5C, 0, 365, (void*)D_8006FC24, (u32)(void*)D_8006FC24, 0x3D, 0xD, 1, -80, 50, 0xA80A, (u32)(void*)D_8006FC24 }, { 0x5D, 0, 460, (void*)D_8006FC30, (u32)(void*)D_8006FC30, 0x35, 0x10, 1, -70, 30, 0xE000, (u32)(void*)D_8006FC30 }, { 0x5E, 0, 703, (void*)D_8006FC3C, (u32)(void*)D_8006FC3C, 0x33, 0xF, 405, -90, 30, 0x3C3000, (u32)(void*)D_8006FC3C }, { 0x5F, 0x2D, 290, (void*)D_8006FC48, (u32)(void*)D_8006FC48, 0x37, 0x58, 2100, -180, 180, 0xE73CF7E2, (u32)(void*)D_8006FC48 }, { 0x60, 0, 930, (void*)D_8006FC54, (u32)(void*)D_8006FC54, 0x35, 0xA, 324, -10, 30, 0x3C7814, (u32)(void*)D_8006FC54 }, { 0x61, 0, 800, (void*)D_8006FC60, (u32)(void*)D_8006FC60, 0x33, 0x10, 756, -15, 30, 0x3BF3D8, (u32)(void*)D_8006FC60 }, { 0x62, 0, 1100, (void*)D_8006FC6C, (u32)(void*)D_8006FC6C, 0x3D, 4, 65, -20, 30, 0x3E0FF6, (u32)(void*)D_8006FC6C }, { 0x63, 0, 494, (void*)D_8006FC78, (u32)(void*)D_8006FC78, 0x35, 0xD, 600, -20, 25, 0x3D7C0F, (u32)(void*)D_8006FC78 }, { 0x64, 0, 1840, (void*)D_8006FC84, (u32)(void*)D_8006FC84, 0x3D, 5, 104, -70, 10, 0x3C6400, (u32)(void*)D_8006FC84 }, { 0x65, 0, 800, (void*)D_8006FC90, (u32)(void*)D_8006FC90, 0x33, 0xC, 666, -70, 10, 0x3C5000, (u32)(void*)D_8006FC90 }, { 0x66, 0, 1160, (void*)D_8006FC9C, (u32)(void*)D_8006FC9C, 0x3D, 4, 25, -50, 40, 0x3E4400, (u32)(void*)D_8006FC9C }, { 0x67, 0, 600, (void*)D_8006FCA8, (u32)(void*)D_8006FCA8, 0x33, 0x14, 1200, -30, 40, 0x3C2400, (u32)(void*)D_8006FCA8 }, { 0x68, 0, 2500, (void*)D_8006FCB4, (u32)(void*)D_8006FCB4, 0x3D, 4, 65, -25, 5, 0x3C2800, (u32)(void*)D_8006FCB4 }, { 0x69, 0, 1140, (void*)D_8006FCC0, (u32)(void*)D_8006FCC0, 0x35, 0xA, 450, -25, 5, 0x3C4000, (u32)(void*)D_8006FCC0 }, { 0x6A, 0, 723, (void*)D_8006FCCC, (u32)(void*)D_8006FCCC, 0x35, 0xF, 498, -20, 50, 0x3C5FE2, (u32)(void*)D_8006FCCC }, { 0x6B, 0xA, 870, (void*)D_8006FCD8, (u32)(void*)D_8006FCD8, 0x35, 0xE, 502, -20, 50, 0x3BE800, (u32)(void*)D_8006FCD8 }, { 0x6C, 0x1C, 767, (void*)D_8006FCE4, (u32)(void*)D_8006FCE4, 0x35, 0xC, 655, -50, 30, 0x3C9C00, (u32)(void*)D_8006FCE4 }, { 0x6D, 0, 1500, (void*)D_8006FCF0, (u32)(void*)D_8006FCF0, 0x3D, 6, 10, -60, 90, 0x3FDC00, (u32)(void*)D_8006FCF0 }, { 0x6E, 0, 855, (void*)D_8006FCFC, (u32)(void*)D_8006FCFC, 0x35, 0xC, 95, -60, 90, 0x3FB800, (u32)(void*)D_8006FCFC }, { 0x6F, 0, 860, (void*)D_8006FD08, (u32)(void*)D_8006FD08, 0x35, 0xA, 1150, -180, 180, 0x3D87EC, (u32)(void*)D_8006FD08 }, { 0x70, 0, 523, (void*)D_8006FD14, (u32)(void*)D_8006FD14, 0x35, 0x13, 1200, -180, 180, 0x3C9832, (u32)(void*)D_8006FD14 }, { 0x71, 0, 850, (void*)D_8006FD20, (u32)(void*)D_8006FD20, 0x33, 0xB, 346, -50, 60, 0x3C9C00, (u32)(void*)D_8006FD20 }, { 0x72, 0, 1000, (void*)D_8006FD2C, (u32)(void*)D_8006FD2C, 0x35, 0xA, 350, -40, 20, 0x3C5400, (u32)(void*)D_8006FD2C }, { 0x73, 0, 479, (void*)D_8006FD38, (u32)(void*)D_8006FD38, 0x33, 0x16, 800, -30, 50, 0x3CB85A, (u32)(void*)D_8006FD38 }, { 0x74, 0, 2110, (void*)D_8006FD44, (u32)(void*)D_8006FD44, 0x3D, 4, 80, -40, 40, 0x3F2400, (u32)(void*)D_8006FD44 }, { 0x75, 0, 827, (void*)D_8006FD50, (u32)(void*)D_8006FD50, 0x35, 0xC, 250, -30, 35, 0x3EBC00, (u32)(void*)D_8006FD50 }, { 0x76, 0x16, 2340, (void*)D_8006FD5C, (u32)(void*)D_8006FD5C, 0x3D, 6, 150, -60, 40, 0x4CA0, (u32)(void*)D_8006FD5C }, { 0x77, 2, 1000, (void*)D_8006FD68, (u32)(void*)D_8006FD68, 0x35, 0xD, 390, -50, 30, 0xDC32, (u32)(void*)D_8006FD68 }, { 0x78, 0, 1430, (void*)D_8006FD74, (u32)(void*)D_8006FD74, 0x35, 8, 345, -10, 30, 0x3BF000, (u32)(void*)D_8006FD74 }, { 0x79, 0, 1047, (void*)D_8006FD80, (u32)(void*)D_8006FD80, 0x33, 0xB, 800, -40, 50, 0x3BB800, (u32)(void*)D_8006FD80 }, { 0x7A, 0, 895, (void*)D_8006FD8C, (u32)(void*)D_8006FD8C, 0x35, 0xD, 545, -30, 50, 0x3BDFE2, (u32)(void*)D_8006FD8C }, { 0x7B, 0, 653, (void*)D_8006FD98, (u32)(void*)D_8006FD98, 0x37, 0xF, 560, -30, 50, 0x3CE324, (u32)(void*)D_8006FD98 }, { 0x7C, 0, 691, (void*)D_8006FDA4, (u32)(void*)D_8006FDA4, 0x33, 0xE, 406, -10, 30, 0x3C6800, (u32)(void*)D_8006FDA4 }, { 0x7D, 0x17, 817, (void*)D_8006FDB0, (u32)(void*)D_8006FDB0, 0x35, 0xB, 300, -20, 30, 0x3C5000, (u32)(void*)D_8006FDB0 }, { 0x7E, 0, 700, (void*)D_8006FDBC, (u32)(void*)D_8006FDBC, 0x35, 0xD, 445, -15, 30, 0x3BFC64, (u32)(void*)D_8006FDBC }, { 0x7F, 0, 703, (void*)D_8006FDC8, (u32)(void*)D_8006FDC8, 0x37, 0xF, 550, -60, 130, 0x3BE400, (u32)(void*)D_8006FDC8 }, { 0x80, 0, 670, (void*)D_8006FDD4, (u32)(void*)D_8006FDD4, 0x33, 0xE, 884, -10, 30, 0x3CE000, (u32)(void*)D_8006FDD4 }, { 0x81, 0, 1329, (void*)D_8006FDE0, (u32)(void*)D_8006FDE0, 0x3D, 9, 100, -30, 25, 0x3D2800, (u32)(void*)D_8006FDE0 }, { 0x82, 0, 380, (void*)D_8006FDEC, (u32)(void*)D_8006FDEC, 0x33, 0x41, 2350, -20, 50, 0x38B000, (u32)(void*)D_8006FDEC }, { 0x83, 0, 400, (void*)D_8006FDF8, (u32)(void*)D_8006FDF8, 0x33, 0x19, 2200, -30, 20, 0x3AB014, (u32)(void*)D_8006FDF8 }, { 0x84, 0, 2200, (void*)D_8006FE04, (u32)(void*)D_8006FE04, 0x3B, 3, 40, -60, 20, 0x3D5800, (u32)(void*)D_8006FE04 }, { 0x85, 0, 2600, (void*)D_8006FE10, (u32)(void*)D_8006FE10, 0x3D, 3, 65, -30, 30, 0x3D8C00, (u32)(void*)D_8006FE10 }, { 0x86, 0, 980, (void*)D_8006FE1C, (u32)(void*)D_8006FE1C, 0x33, 0xA, 290, -20, 50, 0xF8BCCF6A, (u32)(void*)D_8006FE1C }, { 0x87, 0, 1370, (void*)D_8006FE28, (u32)(void*)D_8006FE28, 0x33, 8, 245, -25, 20, 0x3C8FE2, (u32)(void*)D_8006FE28 }, { 0x88, 0, 1148, (void*)D_8006FE34, (u32)(void*)D_8006FE34, 0x37, 9, 250, -20, 30, 0x3C401E, (u32)(void*)D_8006FE34 }, { 0x89, 0, 960, (void*)D_8006FE40, (u32)(void*)D_8006FE40, 0x35, 8, 365, -40, 40, 0x366000, (u32)(void*)D_8006FE40 }, { 0x8A, 0, 2240, (void*)D_8006FE4C, (u32)(void*)D_8006FE4C, 0x3D, 4, 75, -15, 60, 0x3D07AB, (u32)(void*)D_8006FE4C }, { 0x8B, 0, 909, (void*)D_8006FE58, (u32)(void*)D_8006FE58, 0x35, 0xA, 350, -15, 60, 0x3CA7B5, (u32)(void*)D_8006FE58 }, { 0x8C, 0, 2000, (void*)D_8006FE64, (u32)(void*)D_8006FE64, 0x3D, 5, 115, -20, 30, 0x3D5800, (u32)(void*)D_8006FE64 }, { 0x8D, 0, 774, (void*)D_8006FE70, (u32)(void*)D_8006FE70, 0x35, 0xD, 405, -40, 50, 0x3C8C00, (u32)(void*)D_8006FE70 }, { 0x8E, 0x22, 394, (void*)D_8006FE7C, (u32)(void*)D_8006FE7C, 0x37, 0x12, 590, -60, 60, 0x3E6800, (u32)(void*)D_8006FE7C }, { 0x8F, 0, 510, (void*)D_8006FE88, (u32)(void*)D_8006FE88, 0x33, 0x15, 4600, -10, 60, 0x3D5829, (u32)(void*)D_8006FE88 }, { 0x90, 0, 650, (void*)D_8006FE94, (u32)(void*)D_8006FE94, 0x31, 0x11, 554, -20, 30, 0x3BD400, (u32)(void*)D_8006FE94 }, { 0x91, 6, 600, (void*)D_8006FEA0, (u32)(void*)D_8006FEA0, 0x31, 0x10, 526, -20, 25, 0x2800, (u32)(void*)D_8006FEA0 }, { 0x92, 0, 600, (void*)D_8006FEAC, (u32)(void*)D_8006FEAC, 0x35, 0x14, 600, -20, 20, 0x3BAC00, (u32)(void*)D_8006FEAC }, { 0x93, 0, 1050, (void*)D_8006FEB8, (u32)(void*)D_8006FEB8, 0x3D, 0x12, 33, -40, 20, 0x1E3C7C00, (u32)(void*)D_8006FEB8 }, { 0x94, 0, 570, (void*)D_8006FEC4, (u32)(void*)D_8006FEC4, 0x35, 0x28, 165, -30, 10, 0x21FC3BC4, (u32)(void*)D_8006FEC4 }, { 0x95, 0, 473, (void*)D_8006FED0, (u32)(void*)D_8006FED0, 0x31, 0x16, 2100, -20, 25, 0x3C1FF6, (u32)(void*)D_8006FED0 }, { 0x96, 0, 540, (void*)D_8006FEDC, (u32)(void*)D_8006FEDC, 0x20, 0x14, 1220, -70, 90, 0x3C2400, (u32)(void*)D_8006FEDC }, { 0x97, 0, 2000, &D_8006FEE8, (u32)&D_8006FEE8, 0x20, 4, 40, -40, 60, 0x3F7400, (u32)&D_8006FEE8 }, { 0x98, 0, 1510, (void*)D_8006FEF4, -2147025164, 0, 0xA, 50, -50, 50, 0xFDBC3BD8, 0x8006FEF4 } };

void DrawBadgeIcon(s32 arg0, s32 arg1, s32 arg2) {
    u8* var_t4;

    if (arg2 != 0) {
        var_t4 = D_2004320;
    } else {
        var_t4 = D_2004000;
    }

    gSPDisplayList(gDisplayListHead++, D_8006F4E0);
    gDPLoadTextureBlock(gDisplayListHead++, var_t4, G_IM_FMT_RGBA, G_IM_SIZ_16b, 20, 20, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    gSPTextureRectangle(gDisplayListHead++, arg0 << 2, arg1 << 2, (arg0 + 0x13) << 2, (arg1 + 0x13) << 2,
                        G_TX_RENDERTILE, 0, 0, 0x1000, 0x0400);
    gSPDisplayList(gDisplayListHead++, gPrefDL_End);
}

void DrawHealthBar(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
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

    gSPDisplayList(gDisplayListHead++, D_8006F4E0);

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

void DrawExpBar(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
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

void func_80021920(void) {
    char** temp_s2 = GetMessageBank(0x24);
    s32 i;

    for (i = 0; i < 151; i++) {
        HAL_Strcpy(D_8006FF00[i].name, GetMessageString(NULL, 0, temp_s2, i));
    }
}
