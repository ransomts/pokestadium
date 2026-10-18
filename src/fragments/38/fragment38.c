#include "fragment38.h"
#include "src/1AB70.h"
#include "src/1CF30.h"
#include "src/20330.h"
#include "src/20470.h"
#include "src/22630.h"
#include "src/2C1C0.h"
#include "src/2E110.h"
#include "src/3FB0.h"
#include "src/49790.h"
#include "src/4CBC0.h"
#include "src/6A40.h"
#include "src/DDC0.h"
#include "src/F420.h"
#include "src/memory.h"
#include "src/stage_loader.h"
#include "src/232C0.h"

static char** gMessageBankMain;
static char** gMessageBankSecondary;
static unk_D_82305A28 D_82305A28;
static unk_D_82305A30 gPanelAnimState;
static unk_D_82305A30 gStatBarAnimState;
static unk_D_82305A40 gBattleSettingsState;
static unk_D_82305A50 gMenuItems[6];
static unk_D_82305AF8 gTrainerPanels[2];
static unk_D_8230F528 gResultPanels[3];

static unk_D_82305920 gPanelRects[] = {
    {
        68,
        132,
        248,
        56,
        3,
    },
    {
        324,
        132,
        248,
        56,
        4,
    },
    {
        68,
        200,
        248,
        56,
        6,
    },
    {
        324,
        200,
        248,
        56,
        5,
    },
    {
        68,
        268,
        248,
        56,
        254,
    },
    {
        324,
        268,
        248,
        56,
        255,
    },
    {
        80,
        385,
        152,
        48,
        1,
    },
    {
        244,
        385,
        152,
        48,
        2,
    },
};
static s16 D_82305970[] = {
    0x0198, 0x0181, 0x0098, 0x0030, 0, 0,
};
static unk_D_82305978 gStatThresholds[] = {
    {
        50,
        55,
        155,
        1,
    },
    {
        50,
        55,
        155,
        1,
    },
    {
        50,
        55,
        155,
        1,
    },
    {
        25,
        30,
        80,
        8,
    },
    {
        15,
        20,
        50,
        16,
    },
    {
        1,
        100,
        300,
        32,
    },
};

void DrawAnimatedBorder(s16 arg0, s16 arg1, s16 arg2, s16 arg3) {
    static s16 D_823059AC = 0;

    s16 temp_ft3 = SINS(D_823059AC) * 2;
    UNUSED s32 pad[2];

    gSPDisplayList(gDisplayListHead++, gPrefDL_Border);
    gDPSetEnvColor(gDisplayListHead++, 240, 212, 104, 255);

    Gfx_DrawSpriteIA8(arg0 + temp_ft3, arg1 + temp_ft3, 0x10, 0x10, D_2000C80, 0x10, 0);
    Gfx_DrawSpriteIA8(arg0 + temp_ft3, ((arg1 + arg3) - temp_ft3) - 0x10, 0x10, 0x10, D_2000F80, 0x10, 0);
    Gfx_DrawSpriteIA8(((arg0 + arg2) - temp_ft3) - 0x10, arg1 + temp_ft3, 0x10, 0x10, D_2000D80, 0x10, 0);
    Gfx_DrawSpriteIA8(((arg0 + arg2) - temp_ft3) - 0x10, ((arg1 + arg3) - temp_ft3) - 0x10, 0x10, 0x10, D_2000E80, 0x10, 0);

    gSPDisplayList(gDisplayListHead++, gPrefDL_End);

    D_823059AC += 0x2000;
}

void DrawBorder(s16 arg0, s16 arg1, s16 arg2, s16 arg3) {
    gSPDisplayList(gDisplayListHead++, gPrefDL_Border);

    Gfx_DrawSpriteIA8(arg0 - 3, arg1 - 3, 8, 8, D_2000340, 8, 0);
    Gfx_DrawSpriteIA8((arg0 + arg2) - 5, arg1 - 3, 8, 8, D_2000380, 8, 0);
    Gfx_DrawTextureRect(arg0 + 4, arg1 - 3, arg2 - 8, 8, 0, 0, 0, 0x400, 0);
    Gfx_DrawSpriteIA8(arg0 - 3, (arg1 + arg3) - 5, 8, 8, D_20002C0, 8, 0);
    Gfx_DrawTextureRect(arg0 - 3, arg1 + 4, 8, arg3 - 8, 0, 0, 0x400, 0, 0);
    Gfx_DrawSpriteIA8((arg0 + arg2) - 5, (arg1 + arg3) - 5, 8, 8, D_2000300, 8, 0);
    Gfx_DrawTextureRect(arg0 + 4, (arg1 + arg3) - 5, arg2 - 8, 8, 0, 0, 0, 0x400, 0);
    Gfx_DrawTextureRect((arg0 + arg2) - 5, arg1 + 4, 8, arg3 - 8, 0, 0, 0x400, 0, 0);

    gSPDisplayList(gDisplayListHead++, gPrefDL_End);
}

void DrawFilledRectWithBorder(s16 arg0, s16 arg1, s16 arg2, s16 arg3, u8 arg4, u8 arg5, u8 arg6, u8 arg7) {
    s16 var_s2;
    s16 var_s3;
    s16 temp_a2;
    s16 temp_s0_32;

    if (arg2 >= 0x20) {
        var_s3 = 0x10;
    } else {
        var_s3 = arg2 / 2;
    }

    if (arg3 >= 0x20) {
        var_s2 = 0x10;
    } else {
        var_s2 = arg3 / 2;
    }

    temp_a2 = arg2 - (var_s3 * 2);
    temp_s0_32 = arg3 - (var_s2 * 2);

    gSPDisplayList(gDisplayListHead++, gPrefDL_Border);
    gDPSetEnvColor(gDisplayListHead++, arg4, arg5, arg6, arg7);
    gDPLoadTextureBlock_4b(gDisplayListHead++, D_20288E0, G_IM_FMT_I, 16, 16, 0, G_TX_NOMIRROR | G_TX_WRAP,
                           G_TX_NOMIRROR | G_TX_WRAP, 5, 5, G_TX_NOLOD, G_TX_NOLOD);

    Gfx_DrawTextureRect(arg0, arg1, var_s3, var_s2, 0, 0, 0x4000 / var_s3, 0x4000 / var_s2, 0);

    gDPLoadTextureBlock_4b(gDisplayListHead++, D_2028960, G_IM_FMT_I, 16, 16, 0, G_TX_NOMIRROR | G_TX_WRAP,
                           G_TX_NOMIRROR | G_TX_WRAP, 5, 5, G_TX_NOLOD, G_TX_NOLOD);

    Gfx_DrawTextureRect((arg0 + arg2) - var_s3, arg1, var_s3, var_s2, 0, 0, 0x4000 / var_s3, 0x4000 / var_s2, 0);

    gDPLoadTextureBlock_4b(gDisplayListHead++, D_20287E0, G_IM_FMT_I, 16, 16, 0, G_TX_NOMIRROR | G_TX_WRAP,
                           G_TX_NOMIRROR | G_TX_WRAP, 5, 5, G_TX_NOLOD, G_TX_NOLOD);

    Gfx_DrawTextureRect(arg0, (arg1 + arg3) - var_s2, var_s3, var_s2, 0, 0, 0x4000 / var_s3, 0x4000 / var_s2, 0);

    gDPLoadTextureBlock_4b(gDisplayListHead++, D_2028860, G_IM_FMT_I, 16, 16, 0, G_TX_NOMIRROR | G_TX_WRAP,
                           G_TX_NOMIRROR | G_TX_WRAP, 5, 5, G_TX_NOLOD, G_TX_NOLOD);

    Gfx_DrawTextureRect((arg0 + arg2) - var_s3, (arg1 + arg3) - var_s2, var_s3, var_s2, 0, 0, 0x4000 / var_s3,
                  0x4000 / var_s2, 0);

    gSPDisplayList(gDisplayListHead++, gPrefDL_Fill);

    if ((temp_a2 > 0) && (temp_s0_32 > 0)) {
        Gfx_FillRectRGBA(arg0 + var_s3, arg1, temp_a2, var_s2, arg4, arg5, arg6, arg7);
        Gfx_FillRectRGBA(arg0, arg1 + var_s3, arg2, temp_s0_32, arg4, arg5, arg6, arg7);
        Gfx_FillRectRGBA(arg0 + var_s3, arg1 + var_s3 + temp_s0_32, temp_a2, var_s2, arg4, arg5, arg6, arg7);
    } else if (temp_a2 > 0) {
        Gfx_FillRectRGBA(arg0 + var_s3, arg1, temp_a2, arg3, arg4, arg5, arg6, arg7);
    } else if (temp_s0_32 > 0) {
        Gfx_FillRectRGBA(arg0, arg1 + var_s2, arg2, temp_s0_32, arg4, arg5, arg6, arg7);
    }

    gSPDisplayList(gDisplayListHead++, gPrefDL_End);
}

void DrawFilledRectWithBorderSmall(s16 arg0, s16 arg1, s16 arg2, s16 arg3, u8 arg4, u8 arg5, u8 arg6, u8 arg7) {
    s16 sp48;
    s16 sp44;
    s16 var_s2;
    s16 var_s3;

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

    sp48 = arg2 - (var_s3 * 2);
    sp44 = arg3 - (var_s2 * 2);

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

    if ((sp48 > 0) && (sp44 > 0)) {
        Gfx_FillRectRGBA(arg0 + var_s3, arg1, sp48, var_s2, arg4, arg5, arg6, arg7);
        Gfx_FillRectRGBA(arg0, arg1 + var_s3, arg2, sp44, arg4, arg5, arg6, arg7);
        Gfx_FillRectRGBA(arg0 + var_s3, (arg1 + var_s3) + sp44, sp48, var_s2, arg4, arg5, arg6, arg7);
    } else if (sp48 > 0) {
        Gfx_FillRectRGBA(arg0 + var_s3, arg1, sp48, arg3, arg4, arg5, arg6, arg7);
    } else if (sp44 > 0) {
        Gfx_FillRectRGBA(arg0, arg1 + var_s2, arg2, sp44, arg4, arg5, arg6, arg7);
    }

    gSPDisplayList(gDisplayListHead++, gPrefDL_End);
}

void DrawFilledRectWithBorderThin(s16 arg0, s16 arg1, s16 arg2, s16 arg3, u8 arg4, u8 arg5, u8 arg6, u8 arg7) {
    gSPDisplayList(gDisplayListHead++, gPrefDL_Border);
    gDPSetEnvColor(gDisplayListHead++, arg4, arg5, arg6, arg7);

    Gfx_DrawSpriteIA8(arg0, arg1, 8, 8, D_2000B40, 8, 0);
    Gfx_DrawSpriteIA8((arg0 + arg2) - 8, arg1, 8, 8, D_2000B80, 8, 0);
    Gfx_DrawTextureRect(arg0 + 8, arg1, arg2 - 0x10, 8, 0, 0, 0, 0x400, 0);
    Gfx_DrawSpriteIA8(arg0, (arg1 + arg3) - 8, 8, 8, D_2000BC0, 8, 0);
    Gfx_DrawTextureRect(arg0, arg1 + 8, 8, arg3 - 0x10, 0, 0, 0x400, 0, 0);
    Gfx_DrawSpriteIA8((arg0 + arg2) - 8, (arg1 + arg3) - 8, 8, 8, D_2000C00, 8, 0);
    Gfx_DrawTextureRect(arg0 + 8, (arg1 + arg3) - 8, arg2 - 0x10, 8, 0, 0, 0, 0x400, 0);
    Gfx_DrawTextureRect((arg0 + arg2) - 8, arg1 + 8, 8, arg3 - 0x10, 0, 0, 0x400, 0, 0);

    gSPDisplayList(gDisplayListHead++, gPrefDL_Fill);

    Gfx_FillRectRGBA(arg0 + 8, arg1 + 8, arg2 - 0x10, arg3 - 0x10, arg4, arg5, arg6, arg7);

    gSPDisplayList(gDisplayListHead++, gPrefDL_End);
}

void DrawMenuHeaderIcons(s16 arg0, s16 arg1) {
    gSPDisplayList(gDisplayListHead++, gPrefDL_Border);

    Gfx_DrawSpriteRGBA16(arg0, arg1, 0x30, 0x18, D_2006C00, 0x30, 0);
    Gfx_DrawSpriteRGBA16(arg0, arg1 + 0x18, 0x30, 0x18, D_2007500, 0x30, 0);

    gSPDisplayList(gDisplayListHead++, gPrefDL_End);
}

void DrawMenuTopBar(s16 arg0, s16 arg1, s16 arg2, Color_RGBA8* arg3, Color_RGBA8* arg4) {
    gSPDisplayList(gDisplayListHead++, gDL_XluBorder);

    gDPSetEnvColor(gDisplayListHead++, arg3->r, arg3->g, arg3->b, 255);
    gDPSetPrimColor(gDisplayListHead++, 0, 0, arg4->r, arg4->g, arg4->b, 255);

    Gfx_DrawSpriteIA8(arg0, arg1, 0x10, 0x20, D_20003C0, 0x10, 0);
    Gfx_DrawSpriteIA8((arg0 + arg2) - 0x10, arg1, 0x10, 0x20, D_20005C0, 0x10, 0);
    Gfx_DrawTextureRect(arg0 + 0x10, arg1, arg2 - 0x20, 0x20, 0, 0, 0, 0x400, 0);

    gSPDisplayList(gDisplayListHead++, gPrefDL_End);
}

void InitMainMenuUI(void) {
    Color_RGBA8 sp2C;
    Color_RGBA8 sp28;

    GfxColor_SetRGB(&sp2C, 0x64, 0x64, 0xC8);
    GfxColor_SetRGB(&sp28, 0x28, 0x28, 0x8C);
    DrawMenuTopBar(0x48, 0x28, 0x208, &sp2C, &sp28);
    DrawMenuHeaderIcons(0x30, 0x20);
    Text_ResetState();
    Text_SetFont(0x10, 0);
    Text_SetEnvColor(0, 0, 0, 0xFF);
    Text_Print(0x6A, 0x2C, GetMessageString(NULL, 0, gMessageBankMain, 8));
    Text_SetEnvColor(0xFF, 0xFF, 0x77, 0xFF);
    Text_Print(0x68, 0x2A, GetMessageString(NULL, 0, gMessageBankMain, 8));
    Text_SetupDL();
}

void DrawMenuPanelAnimated(unk_D_82305A30* arg0) {
    s16 tmp1;
    s16 tmp2;
    s16 sp3A;

    if (arg0->unk_02 >= 0x10) {
        tmp1 = arg0->unk_02;
        tmp2 = arg0->unk_04;
        sp3A = arg0->unk_06 + ((0x3C - tmp1) / 2);

        DrawFilledRectWithBorderSmall(tmp2, sp3A, 0x210, tmp1, 0x1E, 0x1E, 0x82, 0x96);
        if (((0x3C - tmp1) == 0) && (D_82305A28.unk_02 < 8)) {
            Text_ResetState();
            Text_SetFont(8, 0);
            Text_SetLineHeight(0x18);
            Text_Print(tmp2 + 0x20, sp3A + 8,
                          GetMessageString(NULL, 0, gMessageBankMain, gMenuItems[D_82305A28.unk_02].unk_18));
            Text_SetupDL();
        }
    }
}

void UpdatePanelAnimation(unk_D_82305A30* arg0) {
    switch (arg0->unk_00) {
        case 1:
            arg0->unk_02 += 6;
            if (arg0->unk_02 == 0x3C) {
                arg0->unk_00 = 0;
            }
            break;

        case 2:
            arg0->unk_02 -= 6;
            if (arg0->unk_02 == 0) {
                arg0->unk_00 = 0;
            }
            break;
    }
}

void InitPanelAnimation(unk_D_82305A30* arg0, s16 arg1, s16 arg2) {
    arg0->unk_00 = 0;
    arg0->unk_02 = 0;
    arg0->unk_04 = arg1;
    arg0->unk_06 = arg2;
}

void DrawMenuItem(unk_D_82305A50* arg0) {
    s16 temp_s1;
    s16 temp_s2;

    if (arg0->unk_00 != 0) {
        temp_s1 = arg0->unk_08;
        temp_s2 = arg0->unk_0A;

        DrawBorder(temp_s1, temp_s2, 0xF8, 0x38);

        gSPDisplayList(gDisplayListHead++, gMenuDL_BackgroundFill);

        if (arg0->unk_0C != NULL) {
            if (arg0->unk_01 != 0) {
                Gfx_FillRect(temp_s1 + 4, temp_s2 + 4, 0xF0, 0x30, 0x1E, 0x1E, 0x64);
            } else {
                Gfx_FillRect(temp_s1 + 4, temp_s2 + 4, 0xF0, 0x30, 0x64, 0x1E, 0x1E);
            }

            gSPDisplayList(gDisplayListHead++, gPrefDL_Border);

            Gfx_DrawSpriteRGBA16(temp_s1 + 8, temp_s2 + 8, 0x28, 0x28, arg0->unk_0C, 0x28, 0);
        } else {
            Gfx_FillRect(temp_s1 + 4, temp_s2 + 4, 0xF0, 0x30, 0x1E, 0x5A, 0x1E);
        }

        gSPDisplayList(gDisplayListHead++, gPrefDL_End);

        Text_ResetState();
        if (arg0->unk_0C != NULL) {
            s32 sp3C = temp_s2 + 8;
            char sp44[64];

            Text_SetFont(8, 0);

            if (arg0->unk_01 != 0) {
                Text_SetEnvColor(0xFF, 0xFF, 0xFF, 0xFF);
            } else {
                Text_SetEnvColor(0xDC, 0x37, 0x37, 0xFF);
            }

            Text_Print(temp_s1 + 0x34, sp3C, arg0->unk_10);
            Text_SetFont(4, 0);
            Text_SetEnvColor(0x92, 0xC1, 0xFF, 0xFF);
            sprintf(sp44, "%s%d~%d", GetMessageString(NULL, 0, gMessageBankSecondary, 0x15), arg0->unk_14, arg0->unk_16);
            Text_Print((temp_s1 - (s16)MeasureTextWidth(4, 0, sp44)) + 0xEA, temp_s2 + 0x20, sp44);
        } else {
            Text_SetFont(8, 0);
            Text_Print((temp_s1 - ((s16)MeasureTextWidth(8, 0, arg0->unk_10) / 2)) + 0x7A, temp_s2 + 0x12,
                          arg0->unk_10);
        }
        Text_SetupDL();
    }
}

void UpdateMenuItemAnimation(unk_D_82305A50* arg0) {
    switch (arg0->unk_00) {
        case 2:
            arg0->unk_02 -= 1;
            if (arg0->unk_02 == 0) {
                arg0->unk_00 = 1;
            }

            if (arg0->unk_04 < 0x140) {
                arg0->unk_08 = arg0->unk_04 - (arg0->unk_02 << 5);
            } else {
                arg0->unk_08 = arg0->unk_04 + (arg0->unk_02 << 5);
            }
            break;

        case 3:
            arg0->unk_02 += 1;
            if (arg0->unk_02 == 0xA) {
                arg0->unk_00 = 0;
            }

            if (arg0->unk_04 < 0x140) {
                arg0->unk_08 = arg0->unk_04 - (arg0->unk_02 << 5);
            } else {
                arg0->unk_08 = arg0->unk_04 + (arg0->unk_02 << 5);
            }
            break;
    }
}

void InitMenuItem(unk_D_82305A50* arg0, s16 arg1, s16 arg2, u8* arg3, s8* arg4, s16 arg5, s16 arg6) {
    arg0->unk_00 = 0;
    arg0->unk_02 = 0xA;
    arg0->unk_04 = arg1;
    arg0->unk_06 = arg2;
    arg0->unk_08 = arg1;
    arg0->unk_0A = arg2;
    arg0->unk_0C = arg3;
    arg0->unk_10 = arg4;
    arg0->unk_14 = 0;
    arg0->unk_16 = 0;
    arg0->unk_18 = arg6;
    arg0->unk_01 = 1;

    if (arg5 != 0) {
        arg0->unk_14 = gStatThresholds[arg5 - 1].unk_00;
        arg0->unk_16 = gStatThresholds[arg5 - 1].unk_02;
        arg0->unk_01 = CalculateStatThresholds(&gTrainerPanels[0], arg5);
        arg0->unk_01 &= CalculateStatThresholds(&gTrainerPanels[1], arg5);
    }
}

void DrawStatIcon(s16 arg0, s16 arg1, s16 arg2, s32 arg3) {
    if (arg3 != 0) {
        DrawFilledRectWithBorderThin(arg1, arg2, 0x84, 0x2C, 0x64, 0x1E, 0x1E, 0xFF);
    } else if (arg0 == 0) {
        DrawFilledRectWithBorderThin(arg1, arg2, 0x84, 0x2C, 0x3C, 0x3C, 0xA0, 0xFF);
    } else {
        DrawFilledRectWithBorderThin(arg1, arg2, 0x84, 0x2C, 0x1E, 0x64, 0x1E, 0xFF);
    }
}

static s16 gIconXOffsets[] = { 0x78, 0xFC, 0x180, 0x78, 0xFC, 0x180 };
static s16 gIconYOffsets[] = { 4, 4, 4, 0x30, 0x30, 0x30 };

void DrawTrainerStatPanel(unk_D_82305AF8* arg0, s16 arg1, s16 arg2) {
    s16 i;
    s16 tmp1;
    s16 tmp2;
    s16 tmp3;

    DrawBorder(arg1, arg2, 0x208, 0x60);
    if (arg0->unk_0001 == 0) {
        DrawFilledRectWithBorderThin(arg1 + 4, arg2 + 4, 0x74, 0x58, 0x64, 0x64, 0xC8, 0xFF);
    } else {
        DrawFilledRectWithBorderThin(arg1 + 4, arg2 + 4, 0x74, 0x58, 0x1E, 0x82, 0x1E, 0xFF);
    }

    for (i = 0; i < 6; i++) {
        tmp1 = arg0->unk_0001;
        tmp2 = gIconXOffsets[i] + arg1;
        tmp3 = gIconYOffsets[i] + arg2;
        DrawStatIcon(tmp1, tmp2, tmp3, arg0->unk_0020[i].unk_25);
    }
}

void DrawStatThresholdWindow(unk_D_82305AF8* arg0, s16 arg1, s16 arg2) {
    char sp40[256];
    s16 sp3E;

    if (arg0->unk_0003 == 0) {
        sp3E = (arg0->unk_0010 >= 0) ? (s16)(SINS((s16)(SINS(arg0->unk_0010) * 16384.0f)) * 127.0f) + 0x7F
                                     : (s16)(SINS(arg0->unk_0010) * 127.0f) + 0x7F;

        Text_DrawWindowRect(arg1 + 0x78, arg2 + 4, 0x18C, 0x58, 0x64, 0x1E, 0x1E, (sp3E * 2) / 3);
        Text_ResetState();
        Text_SetFont(0x10, 0);
        Text_SetEnvColor(0xFF, 0xFF, 0, sp3E);
        Text_SetLineHeight(0x20);
        MessageBank_SetPointer_1_9(3, gStatThresholds[arg0->unk_0004 - 1].unk_04);
        Text_Print(arg1 + 0x88, arg2 + 0x14, GetMessageString(sp40, 0x100, gMessageBankMain, 9));
        Text_SetupDL();
        arg0->unk_0010 += 0x300;
    }
}

void DrawTrainerInfoPanel(unk_D_82305AF8* arg0) {
    u8* var_s0;
    s16 i;
    s16 sp58;
    s16 sp56;
    s16 tmp1;
    s16 tmp2;
    s16 tmp3;
    s16 tmp4;

    if (arg0->unk_0000 != 0) {
        sp58 = arg0->unk_000C;
        sp56 = arg0->unk_000E;

        if (arg0->unk_0001 == 0) {
            var_s0 = D_3024C80;
        } else {
            var_s0 = D_30260C0;
        }

        DrawTrainerStatPanel(arg0, sp58, sp56);

        gSPDisplayList(gDisplayListHead++, gPrefDL_Border);

        Gfx_DrawSpriteRGBA16(sp58 + 0x1A, sp56 + 8, 0x48, 0x12, var_s0, 0x48, 0);
        Gfx_DrawSpriteRGBA16(sp58 + 0x1A, sp56 + 0x1A, 0x48, 0x12, var_s0 + 0xA20, 0x48, 0);

        for (i = 0; i < 6; i++) {
            tmp1 = gIconXOffsets[i] + sp58 + 2;
            tmp2 = gIconYOffsets[i] + sp56 + 2;
            Gfx_DrawSpriteRGBA16(tmp1, tmp2, 0x28, 0x28, arg0->unk_0218[i], 0x28, 0);
        }

        gSPDisplayList(gDisplayListHead++, gPrefDL_End);

        Text_ResetState();
        Text_SetFont(8, 0);
        Text_Print((sp58 - (MeasureTextWidth(8, 0, arg0->unk_0014) / 2)) + 0x3E, sp56 + 0x2F, arg0->unk_0014);
        Text_SetFont(4, 0);
        Text_Print((sp58 - (MeasureTextWidth(4, 0, "ID  00000") / 2)) + 0x3E, sp56 + 0x46, "ID  %05d", arg0->unk_0012);
        Text_SetFont(4, 0);

        for (i = 0; i < 6; i++) {
            tmp1 = gIconXOffsets[i] + sp58 + 0x2C;
            tmp2 = gIconYOffsets[i] + sp56 + 5;
            Text_Print(tmp1, tmp2, arg0->unk_0020[i].unk_30);
        }

        Text_SetFont(4, 0);

        for (i = 0; i < 6; i++) {
            tmp3 = gIconXOffsets[i] + sp58 + 0x2C;
            tmp4 = gIconYOffsets[i] + sp56 + 0x17;
            Text_Print(tmp3, tmp4, "%s%d", GetMessageString(NULL, 0, gMessageBankSecondary, 0x15), arg0->unk_0020[i].unk_24);
        }

        Text_SetupDL();
        DrawStatThresholdWindow(arg0, sp58, sp56);
    }
}

void UpdateTrainerPanelAnimation(unk_D_82305AF8* arg0) {
    switch (arg0->unk_0000) {
        case 2:
            arg0->unk_0006 -= 1;
            if (arg0->unk_0006 == 0) {
                arg0->unk_0000 = 1;
            }

            if (arg0->unk_0001 == 0) {
                arg0->unk_000C = arg0->unk_0008 - (arg0->unk_0006 << 6);
            } else {
                arg0->unk_000C = arg0->unk_0008 + (arg0->unk_0006 << 6);
            }
            break;

        case 3:
            arg0->unk_0006 += 1;
            if (arg0->unk_0006 == 0xA) {
                arg0->unk_0000 = 0;
            }

            if (arg0->unk_0001 == 0) {
                arg0->unk_000C = arg0->unk_0008 - (arg0->unk_0006 << 6);
            } else {
                arg0->unk_000C = arg0->unk_0008 + (arg0->unk_0006 << 6);
            }
            break;
    }
}

void InitTrainerInfoPanel(unk_D_82305AF8* arg0, s16 arg1, s16 arg2, s16 arg3) {
    s16 i;

    arg0->unk_0000 = 0;
    arg0->unk_0001 = arg3;
    arg0->unk_0006 = 0xA;
    arg0->unk_0008 = arg1;
    arg0->unk_000A = arg2;
    arg0->unk_000C = arg1;
    arg0->unk_000E = arg2;
    arg0->unk_0012 = SaveSlot_GetPokemonId(arg3);
    SaveSlot_GetTrainerName(arg3, arg0->unk_0014);

    for (i = 0; i < 6; i++) {
        ReadSaveBlockEntry(0x20, arg3, 0, i, &arg0->unk_0020[i]);
        func_8001B0DC(arg0->unk_0218[i], 0, &arg0->unk_0020[i]);
    }
}

s32 CheckPokemonValidForStats(PokemonData* arg0) {
    s32 i;
    s32 var_v1 = 1;

    for (i = 0; i < 4; i++) {
        if (arg0->unk_09[i] == 0) {
            break;
        }

        if (arg0->unk_09[i] >= 0xA6) {
            var_v1 = 0;
        }
    }

    return var_v1;
}

u8 CalculateStatThresholds(unk_D_82305AF8* arg0, s16 arg1) {
    unk_D_82305978* ptr1;
    s16 sp54[3];
    PokemonData* var_s1;
    s16 i;
    s16 j;

    var_s1 = arg0->unk_0020;

    for (i = 0; i < 3; i++) {
        sp54[i] = 999;
    }

    for (i = 0; i < 6; i++, var_s1++) {
        var_s1->unk_25 = 1;
        if ((var_s1->unk_00.unk_00 > 0) && (var_s1->unk_00.unk_00 < 0x98)) {
            if (CheckPokemonValidForStats(var_s1) != 0) {
                ptr1 = &gStatThresholds[(arg1 - 1) & 0xFFFFFFFF];

                if (gSpeciesDisplayTable[var_s1->unk_00.unk_00 - 1].unk_0C & ptr1->unk_06) {
                    if ((var_s1->unk_24 >= ptr1->unk_00) && (ptr1->unk_02 >= var_s1->unk_24)) {
                        var_s1->unk_25 = 0;
                    }
                }

                for (j = 0; j < i; j++) {
                    if (var_s1->unk_00.unk_00 == arg0->unk_0020[j].unk_00.unk_00) {
                        var_s1->unk_25 = 1;
                        arg0->unk_0020[j].unk_25 = 1;
                    }
                }
            }
        }

        if (sp54[2] >= var_s1->unk_24) {
            sp54[2] = var_s1->unk_24;
        }

        if (sp54[1] >= var_s1->unk_24) {
            sp54[2] = sp54[1];
            sp54[1] = var_s1->unk_24;
        }

        if (sp54[0] >= var_s1->unk_24) {
            sp54[1] = sp54[0];
            sp54[0] = var_s1->unk_24;
        }
    }

    for (i = 0, j = 0; i < 6; i++) {
        if (arg0->unk_0020[i].unk_25 == 0) {
            j++;
        }
    }

    arg0->unk_0002 = j == 6;
    if (arg0->unk_0002) {
        arg0->unk_0003 = gStatThresholds[arg1 - 1].unk_04 >= (sp54[0] + sp54[1] + sp54[2]);
    } else {
        arg0->unk_0003 = 1;
    }
    return arg0->unk_0002;
}

u8 SetStatThresholds(unk_D_82305AF8* arg0, s16 arg1) {
    arg0->unk_0004 = arg1;
    arg0->unk_0010 = 0;
    arg0->unk_0000 = 2;
    return CalculateStatThresholds(arg0, arg1);
}

void DrawStatBarPanel(unk_D_82305A30* arg0) {
    s16 temp_s3;
    s16 temp_s2;
    s16 i;
    s16 sp58;

    if (arg0->unk_02 > 0) {
        temp_s2 = arg0->unk_02 / 4;
        temp_s3 = arg0->unk_04;
        sp58 = arg0->unk_06 + ((0x38 - arg0->unk_02) / 2);

        gSPDisplayList(gDisplayListHead++, gPrefDL_Border);

        for (i = 0; i < 4; i++) {
            gDPLoadTextureBlock(gDisplayListHead++, &D_302C000[i * 0xAF0], G_IM_FMT_RGBA, G_IM_SIZ_16b, 100, 14, 0,
                                G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK,
                                G_TX_NOLOD, G_TX_NOLOD);

            Gfx_DrawTextureRect(temp_s3, sp58 + (i * temp_s2), 0x64, temp_s2, 0, 0, 0x400, 0x3800 / temp_s2, 0);
        }

        if ((arg0->unk_01 == 0) && (arg0->unk_02 == 0x38)) {
            DrawFilledRectWithBorder(0x70, sp58 + 8, 0x1A0, 0x28, 0, 0, 0, 0x96);

            gSPDisplayList(gDisplayListHead++, gPrefDL_End);

            Text_ResetState();
            Text_SetFont(0x10, 0);
            Text_SetEnvColor(0xFF, 0x50, 0x64, 0xFF);
            Text_Print(0x90, sp58 + 0xE, GetMessageString(NULL, 0, gMessageBankMain, 0xA));
            Text_SetupDL();
        } else {
            gSPDisplayList(gDisplayListHead++, gPrefDL_End);
        }
    }
}

void func_823031B0(unk_D_82305A30* arg0) {
    switch (arg0->unk_00) {
        case 1:
            arg0->unk_02 += 7;
            if (arg0->unk_02 == 0x38) {
                if (arg0->unk_01 == 0) {
                    PlaySoundEffect(8);
                }
                arg0->unk_00 = 0;
            }
            break;

        case 2:
            arg0->unk_02 -= 7;
            if (arg0->unk_02 == 0) {
                arg0->unk_00 = 0;
            }
            break;
    }
}

void InitStatBarPanel(unk_D_82305A30* arg0, s16 arg1, s16 arg2) {
    arg0->unk_00 = 0;
    arg0->unk_02 = 0;
    arg0->unk_04 = arg1;
    arg0->unk_06 = arg2;
}

void StartStatBarAnimation(unk_D_82305A30* arg0, s32 arg1) {
    arg0->unk_01 = arg1;
    arg0->unk_00 = 1;
}

void DrawResultPanel(unk_D_8230F528* arg0) {
    UNUSED s32 pad;
    s16 sp3A;
    s16 sp38;
    s16 sp36;

    if (arg0->unk_02 >= 0xA) {
        sp3A = arg0->unk_02;
        sp38 = arg0->unk_04;
        sp36 = arg0->unk_06 + ((0x30 - sp3A) / 2);
        DrawBorder(sp38, sp36, 0x98, sp3A);

        gSPDisplayList(gDisplayListHead++, gMenuDL_BackgroundFill);

        Gfx_FillRect(sp38 + 4, sp36 + 4, 0x90, sp3A - 8, 0x3C, 0x3C, 0xA0);

        gSPDisplayList(gDisplayListHead++, gPrefDL_End);

        if (arg0->unk_02 == 0x30) {
            Text_ResetState();
            Text_SetFont(0x10, 0);
            Text_Print((sp38 - ((s16)MeasureTextWidth(0x10, 0, arg0->unk_08) / 2)) + 0x4C, sp36 + 0xB, arg0->unk_08);
            Text_SetupDL();
        }
    }
}

void UpdateResultPanelAnimation(unk_D_8230F528* arg0) {
    switch (arg0->unk_00) {
        case 1:
            arg0->unk_02 += 6;
            if (arg0->unk_02 == 0x30) {
                arg0->unk_00 = 0;
            }
            break;

        case 2:
            arg0->unk_02 -= 6;
            if (arg0->unk_02 == 6) {
                arg0->unk_00 = 0;
            }
            break;
    }
}

void InitResultPanel(unk_D_8230F528* arg0, s16 arg1, s16 arg2, s8* arg3) {
    arg0->unk_00 = 0;
    arg0->unk_02 = 6;
    arg0->unk_04 = arg1;
    arg0->unk_06 = arg2;
    arg0->unk_08 = arg3;
}

void DrawMenuTextLine(unk_D_82305A40* arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4) {
    char sp30[64];
    UNUSED s32 pad;

    if (((arg1 == 1) || (arg1 == 2)) && (arg0->unk_01 == 0)) {
        Text_SetEnvColor(0x50, 0x50, 0xB4, 0xFF);
    } else if (arg1 == arg0->unk_0C) {
        Text_SetEnvColor(0xFF, 0xFF, 0, 0xFF);
    } else {
        Text_SetEnvColor(0xFF, 0xFF, 0xFF, 0xFF);
    }

    Text_Print(arg0->unk_08 + 0x34, arg0->unk_0A + arg1 * 0x21 + 0x2F, GetMessageString(NULL, 0, gMessageBankMain, arg2));

    if (arg3 >= 0) {
        MessageBank_SetPointer_1_9(2, arg4);
        GetMessageString(sp30, sizeof(sp30), gMessageBankMain, arg3);
        Text_Print((arg0->unk_08 - (MeasureTextWidth(0, 0, sp30) / 2)) + 0x158, arg0->unk_0A + arg1 * 0x21 + 0x2F, sp30,
                      arg4);
    }
}

void DrawBattleTimerBar(s16 arg0, s16 arg1, s16 arg2) {
    if (arg2 != 0) {
        Text_SetEnvColor(0x82, 0x1E, 0x1E, 0xFF);
    } else {
        Text_SetEnvColor(0x32, 0x32, 0x96, 0xFF);
    }

    Gfx_DrawSpriteI4(arg0, arg1, 0x10, 0x1C, D_30242C0, 0x10, 0);
    Gfx_DrawSpriteI4(arg0 + 0x68, arg1, 0x10, 0x1C, D_30243A0, 0x10, 0);
    Gfx_DrawTextureRect(arg0 + 0x10, arg1, 0x58, 0x1C, 0, 0, 0, 0x400, 0);
}

void DrawAnimatedTimerIcon(s16 arg0, s16 arg1, s16 arg2, s16 arg3) {
    static s16 D_823059C8 = 0;

    s16 sp36 = SINS(D_823059C8) * 2;

    if (arg2 == 1) {
        if (arg3 >= 6) {
            Gfx_DrawSpriteRGBA16(arg0 - sp36, arg1 + (arg2 * 0x21), 0x14, 0x20, D_302FBC0, 0x14, 0);
        }

        if (arg3 < 0x5A) {
            Gfx_DrawSpriteRGBA16(arg0 + sp36 + 0x94, arg1 + (arg2 * 0x21), 0x14, 0x20, D_30300C0, 0x14, 0);
        }
    } else {
        if (arg3 >= 0xB) {
            Gfx_DrawSpriteRGBA16(arg0 - sp36, arg1 + (arg2 * 0x21), 0x14, 0x20, D_302FBC0, 0x14, 0);
        }

        if (arg3 < 0x5A) {
            Gfx_DrawSpriteRGBA16(arg0 + sp36 + 0x94, arg1 + (arg2 * 0x21), 0x14, 0x20, D_30300C0, 0x14, 0);
        }
    }
    D_823059C8 += 0x2000;
}

void DrawBattleSettingsPanel(unk_D_82305A40* arg0) {
    char* sp54;
    s16 var_a3;
    s16 temp_s1;
    s16 temp_s2;
    UNUSED s16 pad;
    s16 sp4A;

    if (arg0->unk_06 >= 0xF) {
        sp4A = arg0->unk_06;
        temp_s2 = arg0->unk_08;
        temp_s1 = arg0->unk_0A + ((0xBA - sp4A) / 2);

        DrawSimplePanel(temp_s2, temp_s1, 0x1BE, sp4A);

        if (sp4A == 0xBA) {
            DrawFilledRectWithBorderThin(temp_s2 + 7, temp_s1 + 7, 0x1B0, 0x20, 0x82, 0x1E, 0x1E, 0xFF);
            DrawFilledRectWithBorderThin(temp_s2 + 7, temp_s1 + 0x27, 0x1B0, 0x8C, 0x1E, 0x1E, 0x64, 0xFF);
            AnimateIconOffset(temp_s2 + 0xE, temp_s1 + (arg0->unk_0C * 0x21) + 0x31);

            gSPDisplayList(gDisplayListHead++, gPrefDL_Border);

            if (arg0->unk_01 == 1) {
                if (arg0->unk_0C == 1) {
                    DrawAnimatedTimerIcon(temp_s2 + 0x104, temp_s1 + 0x2D, arg0->unk_0C, arg0->unk_02);
                }

                if (arg0->unk_0C == 2) {
                    DrawAnimatedTimerIcon(temp_s2 + 0x104, temp_s1 + 0x2D, arg0->unk_0C, arg0->unk_04);
                }
            }

            DrawBattleTimerBar(temp_s2 + 0x11C, temp_s1 + 0x2E, 1);
            DrawBattleTimerBar(temp_s2 + 0x11C, temp_s1 + 0x4F, arg0->unk_01);
            DrawBattleTimerBar(temp_s2 + 0x11C, temp_s1 + 0x70, arg0->unk_01);

            gSPDisplayList(gDisplayListHead++, gPrefDL_End);

            Text_ResetState();
            Text_SetFont(0x10, 0);
            sp54 = GetMessageString(NULL, 0, gMessageBankMain, 0xB);
            Text_Print((temp_s2 - (MeasureTextWidth(0x10, 0, sp54) / 2)) + 0xDF, temp_s1 + 0xA, sp54);

            if (arg0->unk_01 == 1) {
                var_a3 = 0xC;
            } else {
                var_a3 = 0xD;
            }

            DrawMenuTextLine(arg0, 0, 0xE, var_a3, 0);
            DrawMenuTextLine(arg0, 1, 0x10, 0xF, arg0->unk_02);
            DrawMenuTextLine(arg0, 2, 0x11, 0x12, arg0->unk_04);
            DrawMenuTextLine(arg0, 3, 0x13, -1, 0);
            Text_SetupDL();
        } else {
            DrawFilledRectWithBorderThin(temp_s2 + 7, temp_s1 + 7, 0x1B0, sp4A - 0xE, 0x1E, 0x1E, 0x64, 0xFF);
        }
    }
}

void UpdateBattleSettingsInput(unk_D_82305A40* arg0) {
    s32 temp_v0_2;

    switch (arg0->unk_00) {
        case 1:
            temp_v0_2 = MenuInput_ReadDirection();
            if ((temp_v0_2 == 0x200) && (arg0->unk_01 == 1)) {
                if (arg0->unk_0C == 1) {
                    if (arg0->unk_02 >= 6) {
                        arg0->unk_02 -= 5;
                        PlaySoundEffect(1);
                    }
                }

                if (arg0->unk_0C == 2) {
                    if (arg0->unk_04 >= 0xB) {
                        arg0->unk_04 -= 0xA;
                        PlaySoundEffect(1);
                    }
                }
            } else if ((temp_v0_2 == 0x100) && (arg0->unk_01 == 1)) {
                if (arg0->unk_0C == 1) {
                    if (arg0->unk_02 < 0x5A) {
                        arg0->unk_02 += 5;
                        PlaySoundEffect(1);
                    }
                }

                if (arg0->unk_0C == 2) {
                    if (arg0->unk_04 < 0x5A) {
                        arg0->unk_04 += 0xA;
                        PlaySoundEffect(1);
                    }
                }
            } else {
                if (gPlayer1Controller->buttonPressed & 0x800) {
                    if (arg0->unk_0C > 0) {
                        arg0->unk_0C--;
                        PlaySoundEffect(1);
                    }
                } else if (gPlayer1Controller->buttonPressed & 0x400) {
                    if (arg0->unk_0C < 3) {
                        arg0->unk_0C++;
                        PlaySoundEffect(1);
                    }
                } else if (gPlayer1Controller->buttonPressed & 0x8000) {
                    if (arg0->unk_0C == 0) {
                        arg0->unk_01 ^= 1;
                        PlaySoundEffect(2);
                    }

                    if (arg0->unk_0C == 3) {
                        gBattleTimerLimits[0] = arg0->unk_01;
                        gBattleTimerLimits[1] = arg0->unk_02;
                        gBattleTimerLimits[2] = arg0->unk_04;
                        arg0->unk_00 = 3;
                        PlaySoundEffect(0x1D);
                    }
                } else {
                    if (gPlayer1Controller->buttonPressed & 0x4000) {
                        arg0->unk_01 = gBattleTimerLimits[0];
                        arg0->unk_02 = gBattleTimerLimits[1];
                        arg0->unk_04 = gBattleTimerLimits[2];
                        arg0->unk_00 = 3;
                        PlaySoundEffect(3);
                    }
                }
            }
            break;

        case 2:
            arg0->unk_06 += 0x16;
            if (arg0->unk_06 == 0xBA) {
                MenuInput_SetController(gPlayer1Controller);
                arg0->unk_00 = 1;
            }
            break;

        case 3:
            arg0->unk_06 -= 0x16;
            if (arg0->unk_06 == 0xA) {
                arg0->unk_00 = 0;
            }
            break;
    }
}

void InitBattleSettingsPanel(unk_D_82305A40* arg0, s16 arg1, s16 arg2, s32 arg3) {
    arg0->unk_00 = 0;
    arg0->unk_06 = 0xA;
    arg0->unk_08 = arg1;
    arg0->unk_0A = arg2;
    arg0->unk_0C = 0;

    if (arg3 != 0) {
        arg0->unk_01 = gBattleTimerLimits[0];
        arg0->unk_02 = gBattleTimerLimits[1];
        arg0->unk_04 = gBattleTimerLimits[2];
    }
}

void OpenBattleSettingsPanel(unk_D_82305A40* arg0) {
    PlaySoundEffect(4);
    arg0->unk_00 = 2;
    arg0->unk_0C = 0;
}

void DrawMenuBackground(void) {
    gDPPipeSync(gDisplayListHead++);

    gDPSetCycleType(gDisplayListHead++, G_CYC_1CYCLE);
    gDPSetTexturePersp(gDisplayListHead++, G_TP_NONE);
    gDPSetCombineLERP(gDisplayListHead++, ENVIRONMENT, PRIMITIVE, TEXEL0, PRIMITIVE, TEXEL0, 0, ENVIRONMENT, 0,
                      ENVIRONMENT, PRIMITIVE, TEXEL0, PRIMITIVE, TEXEL0, 0, ENVIRONMENT, 0);
    gDPSetRenderMode(gDisplayListHead++, G_RM_OPA_SURF, G_RM_OPA_SURF2);
    gDPSetEnvColor(gDisplayListHead++, 140, 190, 200, 255);
    gDPSetPrimColor(gDisplayListHead++, 0, 0, 110, 160, 170, 255);
    gSPClearGeometryMode(gDisplayListHead++, G_ZBUFFER | G_LIGHTING);

    gDPLoadTextureBlock_4b(gDisplayListHead++, D_302EBC0, G_IM_FMT_I, 128, 64, 0, G_TX_NOMIRROR | G_TX_WRAP,
                           G_TX_NOMIRROR | G_TX_WRAP, 7, 6, G_TX_NOLOD, G_TX_NOLOD);

    Gfx_DrawTextureRect(0, 0, 0x280, 0x1E0, 0, 0, 0x400, 0x400, 0);

    gSPDisplayList(gDisplayListHead++, gPrefDL_End);
}

void func_82304224(s16 arg0) {
    s16 i;

    Stage_BeginDisplayList();
    DrawMenuBackground();
    InitMainMenuUI();
    DrawMenuPanelAnimated(&gPanelAnimState);
    DrawStatBarPanel(&gStatBarAnimState);
    DrawBattleSettingsPanel(&gBattleSettingsState);
    DrawTrainerInfoPanel(&gTrainerPanels[0]);
    DrawTrainerInfoPanel(&gTrainerPanels[1]);

    for (i = 0; i < 6; i++) {
        DrawMenuItem(&gMenuItems[i]);
    }

    for (i = 0; i < 3; i++) {
        DrawResultPanel(&gResultPanels[i]);
    }

    if (arg0 >= 0) {
        DrawAnimatedBorder(gPanelRects[arg0].unk_00, gPanelRects[arg0].unk_02, gPanelRects[arg0].unk_04,
                      gPanelRects[arg0].unk_06);
    }

    Stage_Advance();
}

void UpdateMainMenu(void) {
    s16 i;

    Game_UpdateInputs();
    UpdatePanelAnimation(&gPanelAnimState);
    func_823031B0(&gStatBarAnimState);
    UpdateBattleSettingsInput(&gBattleSettingsState);
    UpdateTrainerPanelAnimation(&gTrainerPanels[0]);
    UpdateTrainerPanelAnimation(&gTrainerPanels[1]);

    for (i = 0; i < 6; i++) {
        UpdateMenuItemAnimation(&gMenuItems[i]);
    }

    for (i = 0; i < 3; i++) {
        UpdateResultPanelAnimation(&gResultPanels[i]);
    }
}

void HandleMenuNavigation(unk_D_82305A28* arg0) {
    if (arg0->unk_00 == 3) {
        do {
            UpdateMainMenu();
            if (gPlayer1Controller->buttonPressed & 0x800) {
                if (arg0->unk_02 >= 2) {
                    arg0->unk_02 -= 2;
                    PlaySoundEffect(1);
                }
            } else if (gPlayer1Controller->buttonPressed & 0x400) {
                if (arg0->unk_02 < 4) {
                    arg0->unk_02 += 2;
                    PlaySoundEffect(1);
                }
            } else if (gPlayer1Controller->buttonPressed & 0x200) {
                if ((arg0->unk_02 & 1) == 1) {
                    arg0->unk_02--;
                    PlaySoundEffect(1);
                }
            } else if (gPlayer1Controller->buttonPressed & 0x100) {
                if (!(arg0->unk_02 & 1)) {
                    arg0->unk_02++;
                    PlaySoundEffect(1);
                }
            } else if (gPlayer1Controller->buttonPressed & 0x8000) {
                switch (arg0->unk_02) {
                    case 4:
                        arg0->unk_00 = 5;
                        PlaySoundEffect(0x1C);
                        break;

                    case 5:
                        arg0->unk_00 = 2;
                        PlaySoundEffect(3);
                        break;

                    default:
                        arg0->unk_00 = 7;
                        PlaySoundEffect(0x1C);
                        break;
                }
            } else if (gPlayer1Controller->buttonPressed & 0x4000) {
                PlaySoundEffect(3);
                arg0->unk_00 = 2;
            }
            func_82304224(arg0->unk_02);
        } while (arg0->unk_00 == 3);
    }
    arg0->unk_06 = 4;
}

void EventBattle_EnterMenu(unk_D_82305A28* arg0) {
    s16 i;
    s16 j;

    Music_ChangeTrack(0x2D);
    Stage_FadeIn(8);

    for (i = 0; i < 6; i++) {
        UpdateMainMenu();
        func_82304224(-1);
    }

    gPanelAnimState.unk_00 = 1;
    PlayUISfx(0x01100001, 0, 0);

    for (j = 0; j < 6; j++) {
        gMenuItems[j].unk_00 = 2;
    }

    for (i = 0; i < 12; i++) {
        UpdateMainMenu();
        func_82304224(-1);
    }

    arg0->unk_00 = 3;
}

void EventBattle_ExitMenu(unk_D_82305A28* arg0) {
    s16 i;
    s16 j;

    gPanelAnimState.unk_00 = 2;

    for (i = 0; i < 6; i++) {
        gMenuItems[i].unk_00 = 3;
    }

    for (j = 0; j < 6; j++) {
        UpdateMainMenu();
        func_82304224(-1);
    }

    Music_StopTrack(0x10);
    Stage_SetFillColor(0xFFFF);
    Stage_FadeOut(8);

    while (Stage_GetFadeState() != 1) {
        UpdateMainMenu();
        func_82304224(-1);
    }

    arg0->unk_00 = 0;
}

void EventBattle_SelectOption(unk_D_82305A28* arg0) {
    s16 i;
    s16 j;
    u8 tmp1;

    gPanelAnimState.unk_00 = 2;

    for (i = 0; i < 6; i++) {
        gMenuItems[i].unk_00 = 3;
    }

    for (j = 0; j < 12; j++) {
        UpdateMainMenu();
        func_82304224(-1);
    }

    PlayUISfx(0x01100001, 0, 0);
    arg0->unk_01 = SetStatThresholds(&gTrainerPanels[0], gPanelRects[arg0->unk_02].unk_08);
    arg0->unk_01 &= SetStatThresholds(&gTrainerPanels[1], gPanelRects[arg0->unk_02].unk_08);
    StartStatBarAnimation(&gStatBarAnimState, arg0->unk_01);

    tmp1 = !arg0->unk_01;
    arg0->unk_04 = tmp1;

    for (i = tmp1; i < 3; i++) {
        gResultPanels[i].unk_00 = 1;
    }

    for (j = 0; j < 12; j++) {
        UpdateMainMenu();
        func_82304224(-1);
    }

    arg0->unk_00 = 4;
}

void EventBattle_ReturnToMenu(unk_D_82305A28* arg0) {
    u8 temp_v1;
    s16 i;
    s16 j;

    temp_v1 = !arg0->unk_01;
    gTrainerPanels[0].unk_0000 = 3;
    gTrainerPanels[1].unk_0000 = 3;
    gStatBarAnimState.unk_00 = 2;

    for (i = temp_v1; i < 3; i++) {
        gResultPanels[i].unk_00 = 2;
    }

    for (j = 0; j < 12; j++) {
        UpdateMainMenu();
        func_82304224(-1);
    }

    gPanelAnimState.unk_00 = 1;
    PlayUISfx(0x01100001, 0, 0);

    for (i = 0; i < 6; i++) {
        gMenuItems[i].unk_00 = 2;
    }

    for (j = 0; j < 12; j++) {
        UpdateMainMenu();
        func_82304224(-1);
    }

    arg0->unk_00 = 3;
}

void EventBattle_ConfirmSelection(unk_D_82305A28* arg0) {
    u8 temp_v1;
    s16 i;
    s16 j;

    PlayUISfx(0x01100001, 0, 0);
    arg0->unk_01 = SetStatThresholds(&gTrainerPanels[0], gPanelRects[arg0->unk_02].unk_08);
    arg0->unk_01 &= SetStatThresholds(&gTrainerPanels[1], gPanelRects[arg0->unk_02].unk_08);
    StartStatBarAnimation(&gStatBarAnimState, arg0->unk_01);

    temp_v1 = !arg0->unk_01;
    arg0->unk_04 = temp_v1;

    for (i = temp_v1; i < 3; i++) {
        gResultPanels[i].unk_00 = 1;
    }

    for (j = 0; j < 12; j++) {
        UpdateMainMenu();
        func_82304224(-1);
    }

    arg0->unk_00 = 4;
}

void EventBattle_CheckHeldItem(PokemonData* arg0, s16 arg1) {
    Gen1StringDecodeBuffer sp30;
    Gen1StringDecodeBuffer sp20;

    if ((MenuItem_GetHeldItemId(arg1) == 7) && (arg0->unk_00.unk_00 == 0x19)) {
        Controller_ReadInput(arg1, &sp20);
        _bcopy(arg0->unk_46, sp30.unk_02, 11);
        sp30.unk_00 = arg0->unk_0E;
        if (IsPokemonNameMatch(&sp30, &sp20)) {
            arg0->unk_52 |= 0x80;
        }
    }
}

void EventBattle_RegisterParty(unk_D_82305AF8* arg0) {
    s16 i;
    unk_D_800AE540_0004* temp_s4 = RegisterPlayer(arg0->unk_0001, arg0->unk_0012, arg0->unk_0014, GetNameSlot(1));

    for (i = 0; i < 6; i++) {
        EventBattle_CheckHeldItem(&arg0->unk_0020[i], arg0->unk_0001);
        Battle_AddPartyMon(temp_s4, &arg0->unk_0020[i]);
    }

    Battle_RegisterPlayerEntry(arg0->unk_0001, temp_s4);
}

void EventBattle_StartBattle(unk_D_82305A28* arg0) {
    s16 i;
    s16 j;

    Battle_Init(0xA, gPanelRects[arg0->unk_02].unk_08, 0);
    EventBattle_RegisterParty(&gTrainerPanels[0]);
    EventBattle_RegisterParty(&gTrainerPanels[1]);

    if (gBattleSettingsState.unk_01 == 1) {
        gBattleContext.unk_11ED = gBattleSettingsState.unk_01;
        gBattleContext.unk_11EE = gBattleSettingsState.unk_02;
        gBattleContext.unk_11EF = gBattleSettingsState.unk_04;
    }
    gTrainerPanels[0].unk_0000 = 3;
    gTrainerPanels[1].unk_0000 = 3;
    gStatBarAnimState.unk_00 = 2;

    for (i = 0; i < 3; i++) {
        gResultPanels[i].unk_00 = 2;
    }

    for (j = 0; j < 6; j++) {
        UpdateMainMenu();
        func_82304224(-1);
    }

    Music_StopTrack(0x10);
    Stage_SetFillColor(0xFFFF);
    Stage_FadeOut(8);

    while (Stage_GetFadeState() != 1) {
        UpdateMainMenu();
        func_82304224(-1);
    }

    arg0->unk_06 = 0x2A;
    arg0->unk_00 = 0;
}

void EventBattle_HandleInput(unk_D_82305A28* arg0) {
    u8 temp_s7;

    temp_s7 = !arg0->unk_01;

    if (arg0->unk_00 == 4) {
        do {
            UpdateMainMenu();
            if (gPlayer1Controller->buttonPressed & 0x200) {
                if (temp_s7 < arg0->unk_04) {
                    arg0->unk_04--;
                    PlaySoundEffect(1);
                }
            } else if (gPlayer1Controller->buttonPressed & 0x100) {
                if (arg0->unk_04 < 2) {
                    arg0->unk_04++;
                    PlaySoundEffect(1);
                }
            } else if (gPlayer1Controller->buttonPressed & 0x8000) {
                switch (arg0->unk_04) {
                    case 0:
                        arg0->unk_00 = 6;
                        PlaySoundEffect(0x20);
                        break;

                    case 1:
                        arg0->unk_00 = 9;
                        PlaySoundEffect(0x1C);
                        break;

                    case 2:
                        arg0->unk_00 = 8;
                        PlaySoundEffect(3);
                        break;
                }
            } else if (gPlayer1Controller->buttonPressed & 0x4000) {
                PlaySoundEffect(3);
                arg0->unk_04 = 2;
                arg0->unk_00 = 8;
            }
            func_82304224(arg0->unk_04 + 6);
        } while (arg0->unk_00 == 4);
    }
}

void EventBattle_ProcessTransition(unk_D_82305A28* arg0) {
    s16 i;
    s16 j;

    gPanelAnimState.unk_00 = 2;

    for (i = 0; i < 6; i++) {
        gMenuItems[i].unk_00 = 3;
    }

    for (j = 0; j < 12; j++) {
        UpdateMainMenu();
        func_82304224(-1);
    }

    OpenBattleSettingsPanel(&gBattleSettingsState);

    while (gBattleSettingsState.unk_00 != 0) {
        UpdateMainMenu();
        func_82304224(-1);
    }

    gPanelAnimState.unk_00 = 1;
    PlayUISfx(0x01100001, 0, 0);

    for (i = 0; i < 6; i++) {
        gMenuItems[i].unk_00 = 2;
    }

    for (j = 0; j < 12; j++) {
        UpdateMainMenu();
        func_82304224(-1);
    }

    arg0->unk_00 = 3;
}

void EventBattle_CancelBattle(unk_D_82305A28* arg0) {
    s16 i;
    s16 j;

    Battle_Init(0xA, gPanelRects[arg0->unk_02].unk_08, 0);

    gTrainerPanels[0].unk_0000 = 3;
    gTrainerPanels[1].unk_0000 = 3;
    gStatBarAnimState.unk_00 = 2;

    for (i = 0; i < 3; i++) {
        gResultPanels[i].unk_00 = 2;
    }

    for (j = 0; j < 12; j++) {
        UpdateMainMenu();
        func_82304224(-1);
    }

    arg0->unk_06 = 0x12;
    arg0->unk_00 = 0;
}

void EventBattle_StateMachine(unk_D_82305A28* arg0) {
    while (arg0->unk_00 != 0) {
        switch (arg0->unk_00) {
            case 1:
                EventBattle_EnterMenu(arg0);
                break;

            case 2:
                EventBattle_ExitMenu(arg0);
                break;

            case 3:
                HandleMenuNavigation(arg0);
                break;

            case 4:
                EventBattle_HandleInput(arg0);
                break;

            case 7:
                EventBattle_SelectOption(arg0);
                break;

            case 8:
                EventBattle_ReturnToMenu(arg0);
                break;

            case 6:
                EventBattle_StartBattle(arg0);
                break;

            case 5:
                EventBattle_ProcessTransition(arg0);
                break;

            case 9:
                EventBattle_CancelBattle(arg0);
                break;

            case 10:
                EventBattle_ConfirmSelection(arg0);
                break;
        }
    }
}

void EventBattle_InitUI(unk_D_82305A28* arg0, s16 arg1) {
    s16 i;

    if (arg1 == -1) {
        arg0->unk_00 = 1;
        arg0->unk_02 = 2;
    } else {
        arg0->unk_00 = 0xA;
        arg0->unk_02 = arg1;
    }
    arg0->unk_06 = 0x12;

    InitPanelAnimation(&gPanelAnimState, 0x38, 0x17C);
    InitStatBarPanel(&gStatBarAnimState, 0x10E, 0xC0);
    InitBattleSettingsPanel(&gBattleSettingsState, 0x68, 0x93, (arg1 + 1) == 0);

    InitTrainerInfoPanel(&gTrainerPanels[0], 0x40, 0x5C, 0);
    InitTrainerInfoPanel(&gTrainerPanels[1], 0x40, 0xF8, 1);

    InitMenuItem(&gMenuItems[0], 0x44, 0x84, D_3028E00, GetMessageString(NULL, 0, gMessageBankMain, 0x15), 3, 0);
    InitMenuItem(&gMenuItems[1], 0x144, 0x84, D_3029A80, GetMessageString(NULL, 0, gMessageBankMain, 0x18), 4, 1);
    InitMenuItem(&gMenuItems[2], 0x44, 0xC8, D_302A700, GetMessageString(NULL, 0, gMessageBankMain, 0x1A), 6, 5);
    InitMenuItem(&gMenuItems[3], 0x144, 0xC8, D_302B380, GetMessageString(NULL, 0, gMessageBankMain, 0x19), 5, 3);
    InitMenuItem(&gMenuItems[4], 0x44, 0x10C, NULL, GetMessageString(NULL, 0, gMessageBankMain, 0x1B), 0, 6);
    InitMenuItem(&gMenuItems[5], 0x144, 0x10C, NULL, GetMessageString(NULL, 0, gMessageBankMain, 0x1C), 0, 7);

    InitResultPanel(&gResultPanels[0], 0x50, 0x181, GetMessageString(NULL, 0, gMessageBankMain, 0x1D));
    InitResultPanel(&gResultPanels[1], 0xF4, 0x181, GetMessageString(NULL, 0, gMessageBankMain, 0x1E));
    InitResultPanel(&gResultPanels[2], 0x198, 0x181, GetMessageString(NULL, 0, gMessageBankMain, 0x1F));

    if (arg1 == -1) {
        for (i = 2; i >= 0; i--) {
            if (gMenuItems[i].unk_01 != 0) {
                arg0->unk_02 = i;
            }
        }
    }
}

s16 EventBattleMainLoop(void) {
    static s16 D_823059CC = -1;

    main_pool_push_state('EVSL');

    Text_Init(0x1C, 0);

    ASSET_LOAD(D_1000000, common_menu1_ui, 0);
    ASSET_LOAD(D_2000000, common_menu2_ui, 0);
    ASSET_LOAD(D_3000000, menu_select_ui, 0);

    SpriteAssets_Load();
    SaveSlot_Load(0);
    SaveSlot_Load(1);
    func_80007754();
    EventBattle_InitUI(&D_82305A28, D_823059CC);
    EventBattle_StateMachine(&D_82305A28);
    D_823059CC = D_82305A28.unk_02;
    Stage_Terminate();
    Gfx_FreeBuffers();

    main_pool_pop_state('EVSL');

    return D_82305A28.unk_06;
}

s32 func_823057E4(UNUSED s32 arg0, UNUSED s32 arg1) {
    s16 temp_v0 = STATE_EVENT_BATTLE;

    main_pool_push_state('EBTL');

    Gfx_InitBuffers(0x10000, 0);
    Stage_Set(Stage_Create(1, 0, 2, 0, 2, 1));
    MessageBank_Init();
    gMessageBankMain = GetMessageBank(0x10);
    gMessageBankSecondary = GetMessageBank(6);

    while (temp_v0 == STATE_EVENT_BATTLE) {
        temp_v0 = EventBattleMainLoop();
        if (temp_v0 == STATE_EVENT_BATTLE) {
            FRAGMENT_LOAD_AND_CALL(fragment55, 0, 0);
        }
    }

    Stage_Destroy();
    Gfx_FreeBuffers();

    main_pool_pop_state('EBTL');

    return temp_v0;
}
