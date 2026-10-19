#include "fragment63.h"
#include "src/12D80.h"
#include "src/1C720.h"
#include "src/1CF30.h"
#include "src/20470.h"
#include "src/26820.h"
#include "src/49790.h"
#include "src/F420.h"
#include "src/math_util.h"
#include "src/memmap.h"
#include "src/memory.h"

static unk_D_84B17550 gMenuPanelDefs[] = {
    {
        78,
        84,
        164,
        72,
        2,
        8481,
        0,
        -1,
        44,
    },
    {
        78,
        91,
        164,
        58,
        2,
        8481,
        0,
        -1,
        44,
    },
    {
        77,
        122,
        166,
        92,
        5,
        8481,
        0,
        -1,
        9362,
    },
    {
        77,
        142,
        166,
        52,
        3,
        8481,
        0,
        -1,
        146,
    },
    {
        77,
        144,
        166,
        52,
        3,
        8481,
        0,
        -1,
        146,
    },
    {
        77,
        149,
        166,
        38,
        2,
        8481,
        0,
        -1,
        18,
    },
    {
        60,
        40,
        200,
        64,
        1,
        8481,
        0,
        -1,
        2,
    },
    {
        60,
        40,
        200,
        64,
        1,
        8481,
        0,
        -1,
        2,
    },
    {
        68,
        32,
        184,
        104,
        1,
        8481,
        1,
        -1,
        2,
    },
    {
        60,
        38,
        200,
        164,
        2,
        26889,
        0,
        -1,
        13,
    },
};

void BattlePrep_DrawCursorArrow(unk_D_84B2665C* arg0, s16 arg1, s16 arg2) {
    static s16 D_84B17604 = 0;

    if (D_84B17604 < 6) {
        arg1 = (arg1 + (D_84B17604 / 2));
    } else {
        arg1 = ((arg1 - (D_84B17604 / 2)) + 6);
    }

    gSPDisplayList(gDisplayListHead++, gPrefDL_Border);

    gDPLoadTextureBlock(gDisplayListHead++, D_10031D0, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 22, 0,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                        G_TX_NOLOD);

    Gfx_DrawTextureRect(arg1, arg2 + (arg0->unk_04 * 0xE) + 1, 0x10, 0xB, 0, 0, 0x800, 0x800, 0);

    gSPDisplayList(gDisplayListHead++, gPrefDL_End);

    D_84B17604 = (D_84B17604 + 1) % 12;
}

void MenuItem_Print(unk_D_84B2665C* arg0, s16 arg1, s16 arg2, s16 arg3, s32 arg4, s8* arg5) {
    if (arg4 == 0) {
        Text_SetEnvColor(0x64, 0x64, 0x64, 0xFF);
    } else if (arg3 == arg0->unk_04) {
        Text_SetEnvColor(0xFF, 0xFF, 0, 0xFF);
    } else {
        Text_SetEnvColor(0xFF, 0xFF, 0xFF, 0xFF);
    }
    Text_Print(arg1, arg2 + (arg3 * 0xE), arg5);
}

void RenderBattleStatusPanel(unk_D_84B2665C* arg0, unk_D_84B17550* arg1) {
    BattlePrep_DrawCursorArrow(arg0, arg1->unk_00 + 0xC, arg1->unk_02 + 0x18);
    Text_ResetState();
    Text_SetFont(2, 0);
    Text_Print(arg1->unk_00 + 0x10, arg1->unk_02 + 6, Battle_GetMessageString(0x29));
    MenuItem_Print(arg0, arg1->unk_00 + 0x22, arg1->unk_02 + 0x18, 0, 1, Battle_GetMessageString(0x2A));
    MenuItem_Print(arg0, arg1->unk_00 + 0x22, arg1->unk_02 + 0x18, 1, 1, Battle_GetMessageString(0x2B));

    if (arg1->unk_06 == 0x48) {
        Text_SetFont(1, 0);
        Text_SetEnvColor(0xFF, 0xFF, 0xFF, 0xFF);
        Text_Print(arg1->unk_00 + 0x4A, arg1->unk_02 + 0x36, "%s%d", Battle_GetMessageString(0x2C), gBattleContext.unk_11F3);
    }

    Text_SetupDL();
}

void RenderBattleOptionsPanel(unk_D_84B2665C* arg0, unk_D_84B17550* arg1) {
    s32 sp2C;
    s32 sp28;

    sp2C = gBattleContext.unk_11F3 > 0;
    sp28 = !!(gBattleContext.unk_11F5 & 2);
    sp28 = !sp28;

    BattlePrep_DrawCursorArrow(arg0, arg1->unk_00 + 5, arg1->unk_02 + 6);
    Text_ResetState();
    Text_SetFont(2, 0);
    MenuItem_Print(arg0, arg1->unk_00 + 0x1A, arg1->unk_02 + 6, 0, sp2C, Battle_GetMessageString(0x2D));
    MenuItem_Print(arg0, arg1->unk_00 + 0x1A, arg1->unk_02 + 6, 1, sp2C, Battle_GetMessageString(0x2E));
    MenuItem_Print(arg0, arg1->unk_00 + 0x1A, arg1->unk_02 + 6, 2, sp28, Battle_GetMessageString(0x2F));
    MenuItem_Print(arg0, arg1->unk_00 + 0x1A, arg1->unk_02 + 6, 3, 1, Battle_GetMessageString(0x30));
    MenuItem_Print(arg0, arg1->unk_00 + 0x1A, arg1->unk_02 + 6, 4, 1, Battle_GetMessageString(0x31));
    Text_SetFont(1, 0);
    Text_SetEnvColor(0xFF, 0xFF, 0xFF, 0xFF);
    Text_Print(arg1->unk_00 + 0x4A, arg1->unk_02 + 0x4C, "%s%d", Battle_GetMessageString(0x2C), gBattleContext.unk_11F3);
    Text_SetupDL();
}

void RenderBattleSummaryPanel(unk_D_84B2665C* arg0, unk_D_84B17550* arg1) {
    s32 sp2C = !!(gBattleContext.unk_11F5 & 2);

    sp2C = !sp2C;
    BattlePrep_DrawCursorArrow(arg0, arg1->unk_00 + 5, arg1->unk_02 + 6);
    Text_ResetState();
    Text_SetFont(2, 0);
    MenuItem_Print(arg0, arg1->unk_00 + 0x1A, arg1->unk_02 + 6, 0, sp2C, Battle_GetMessageString(0x2F));
    MenuItem_Print(arg0, arg1->unk_00 + 0x1A, arg1->unk_02 + 6, 1, 1, Battle_GetMessageString(0x32));
    MenuItem_Print(arg0, arg1->unk_00 + 0x1A, arg1->unk_02 + 6, 2, 1, Battle_GetMessageString(0x31));
    Text_SetupDL();
}

void RenderBattleHPPanel(unk_D_84B2665C* arg0, unk_D_84B17550* arg1) {
    s32 sp2C = gBattleContext.unk_1194[0].unk_1E < 0x63 && gBattleContext.unk_1194[1].unk_1E < 0x63;

    BattlePrep_DrawCursorArrow(arg0, arg1->unk_00 + 5, arg1->unk_02 + 6);
    Text_ResetState();
    Text_SetFont(2, 0);
    MenuItem_Print(arg0, arg1->unk_00 + 0x1A, arg1->unk_02 + 6, 0, sp2C, Battle_GetMessageString(0x33));
    MenuItem_Print(arg0, arg1->unk_00 + 0x1A, arg1->unk_02 + 6, 1, 1, Battle_GetMessageString(0x34));
    MenuItem_Print(arg0, arg1->unk_00 + 0x1A, arg1->unk_02 + 6, 2, 1, Battle_GetMessageString(0x31));
    Text_SetupDL();
}

void RenderBattleScorePanel(unk_D_84B2665C* arg0, unk_D_84B17550* arg1) {
    BattlePrep_DrawCursorArrow(arg0, arg1->unk_00 + 5, arg1->unk_02 + 6);
    Text_ResetState();
    Text_SetFont(2, 0);
    MenuItem_Print(arg0, arg1->unk_00 + 0x1A, arg1->unk_02 + 6, 0, 1, Battle_GetMessageString(0x35));
    MenuItem_Print(arg0, arg1->unk_00 + 0x1A, arg1->unk_02 + 6, 1, 1, Battle_GetMessageString(0x31));
    Text_SetupDL();
}

void RenderBattleModeTitle(unk_D_84B2665C* arg0, unk_D_84B17550* arg1) {
    char* temp_v0;

    Text_ResetState();
    Text_BeginRender();
    Text_SetFont(4, 0);
    Text_SetPrimColor(0x32, 0xFF, 0x64, 0xFF);

    if ((gBattleContext.unk_0000 == 3) || (gBattleContext.unk_0000 == 6)) {
        temp_v0 = Battle_GetMessageString(gBattleContext.unk_0000 - 1);
        Text_Print((arg1->unk_00 - (MeasureTextWidth(4, 0, temp_v0) / 2)) + 0x64, arg1->unk_02 + 6, temp_v0);
        temp_v0 = Battle_GetMessageString(gBattleContext.unk_0002 + 7);
        Text_Print((arg1->unk_00 - (MeasureTextWidth(4, 0, temp_v0) / 2)) + 0x64, arg1->unk_02 + 0x18, temp_v0);
        temp_v0 = Battle_GetMessageString(gBattleContext.unk_0003 + 0xA);
        Text_Print((arg1->unk_00 - (MeasureTextWidth(4, 0, temp_v0) / 2)) + 0x64, arg1->unk_02 + 0x2A, temp_v0);
    } else {
        temp_v0 = Battle_GetMessageString(gBattleContext.unk_0000 - 1);
        Text_Print((arg1->unk_00 - (MeasureTextWidth(4, 0, temp_v0) / 2)) + 0x64, arg1->unk_02 + 0xA, temp_v0);
        temp_v0 = Battle_GetMessageString(gBattleContext.unk_0003 + 0xA);
        Text_Print((arg1->unk_00 - (MeasureTextWidth(4, 0, temp_v0) / 2)) + 0x64, arg1->unk_02 + 0x26, temp_v0);
    }

    Text_EndRender();
    Text_SetupDL();
}

void RenderBattleMatchupPanel(unk_D_84B2665C* arg0, unk_D_84B17550* arg1) {
    s32 sp12C;
    char sp2C[0x100];

    Text_ResetState();
    Text_BeginRender();
    Text_SetFont(4, 0);
    Text_SetPrimColor(0x32, 0xFF, 0x64, 0xFF);

    sprintf(sp2C, "%s %s", Battle_GetMessageString(gBattleContext.unk_0002 + 0x13), Battle_GetMessageString(0x36));
    sp12C = MeasureTextWidth(4, 0, sp2C);
    Text_Print((arg1->unk_00 - (sp12C / 2)) + 0x64, arg1->unk_02 + 0xA, sp2C);

    if (gBattleContext.unk_0002 < 9) {
        if (gBattleContext.unk_0002 == 8) {
            sprintf(sp2C, "%s %d", Battle_GetMessageString(0x1B), gBattleContext.unk_0003);
            sp12C = MeasureTextWidth(4, 0, sp2C);
            Text_Print((arg1->unk_00 - (sp12C / 2)) + 0x64, arg1->unk_02 + 0x26, sp2C);
        } else if (gBattleContext.unk_0003 < 4) {
            sprintf(&sp2C, "%s %d", Battle_GetMessageString(0x37), gBattleContext.unk_0003);
            sp12C = MeasureTextWidth(4, 0, sp2C);
            Text_Print((arg1->unk_00 - (sp12C / 2)) + 0x64, arg1->unk_02 + 0x26, sp2C);
        } else {
            sp12C = MeasureTextWidth(4, 0, Battle_GetMessageString(gBattleContext.unk_0002 + 0x1D));
            Text_Print((arg1->unk_00 - (sp12C / 2)) + 0x64, arg1->unk_02 + 0x26,
                          Battle_GetMessageString(gBattleContext.unk_0002 + 0x1D));
        }
    }

    Text_EndRender();
    Text_SetupDL();
}

void RenderBattleItemIcons(s16 arg0, s16 arg1, unk_D_800AE540_1194* arg2) {
    static u8* sItemIconTextures[] = { D_3025950, D_30260A0, D_30267F0, D_3026F40 };

    gSPDisplayList(gDisplayListHead++, gPrefDL_Border);

    if (arg2->unk_01 == 1) {
        if (arg2->unk_08[0]->unk_000 & 2) {
            Gfx_DrawSpriteRGBA16(arg0 + 0x1A, arg1 + 3, 0x24, 0x1A, D_3025200, 0x24, 0);
            if (0) {}
        } else {
            Gfx_DrawSpriteRGBA16(arg0 + 0x1A, arg1 + 3, 0x24, 0x1A, sItemIconTextures[arg2->unk_08[0]->unk_001], 0x24, 0);
        }

        gSPDisplayList(gDisplayListHead++, gPrefDL_End);
        return;
    }

    if (arg2->unk_08[0]->unk_001 < arg2->unk_08[1]->unk_001) {
        Gfx_DrawSpriteRGBA16(arg0 + 6, arg1 + 3, 0x24, 0x1A, sItemIconTextures[arg2->unk_08[0]->unk_001], 0x24, 0);
        Gfx_DrawSpriteRGBA16(arg0 + 0x30, arg1 + 3, 0x24, 0x1A, sItemIconTextures[arg2->unk_08[1]->unk_001], 0x24, 0);
    } else {
        Gfx_DrawSpriteRGBA16(arg0 + 6, arg1 + 3, 0x24, 0x1A, sItemIconTextures[arg2->unk_08[1]->unk_001], 0x24, 0);
        Gfx_DrawSpriteRGBA16(arg0 + 0x30, arg1 + 3, 0x24, 0x1A, sItemIconTextures[arg2->unk_08[0]->unk_001], 0x24, 0);
    }

    gSPDisplayList(gDisplayListHead++, gPrefDL_End);

    Text_ResetState();
    Text_SetFont(4, 0);
    Text_PutChar(arg0 + 0x24, arg1 + 8, 0x26);
    Text_SetupDL();
}

void UpdateFlashingTextColor(unk_D_800AE540_1194* arg0) {
    static s16 D_84B17618 = 0;

    if (arg0->unk_1C == 1) {
        Text_SetEnvColor(0xFF, (SINS((s32)(SINS(D_84B17618) * 16384.0f)) * 100.0f) + 155.0f, 0x37, 0xFF);
        D_84B17618 += 0x400;
    } else {
        Text_SetEnvColor(0xFF, 0x37, 0x37, 0xFF);
    }
}

void BattlePrep_DrawTeamPreview(unk_D_84B2665C* arg0, unk_D_84B17550* arg1) {
    Gfx_DrawPanel(arg1->unk_00 + 8, arg1->unk_02 + 0x14, 0xA8, 0x20, 0, 0, 0, 0xFF);
    Gfx_DrawPanel(arg1->unk_00 + 8, arg1->unk_02 + 0x44, 0xA8, 0x20, 0, 0, 0, 0xFF);
    RenderBattleItemIcons(arg1->unk_00 + 8, arg1->unk_02 + 0x14, gBattleContext.unk_1194);
    RenderBattleItemIcons(arg1->unk_00 + 8, arg1->unk_02 + 0x44, &gBattleContext.unk_1194[1]);
    Text_ResetState();
    Text_BeginRender();
    Text_SetFont(4, 0);
    Text_SetPrimColor(0x32, 0xFF, 0x64, 0xFF);
    Text_Print(arg1->unk_00 + 0x40, arg1->unk_02 + 2, Battle_GetMessageString(0x38));
    Text_EndRender();
    Text_SetFont(0x10, 0);
    UpdateFlashingTextColor(&gBattleContext.unk_1194[0]);
    Text_Print(arg1->unk_00 + 0x5C, arg1->unk_02 + 0x18, "%2d", gBattleContext.unk_1194[0].unk_1E);
    UpdateFlashingTextColor(&gBattleContext.unk_1194[1]);
    Text_Print(arg1->unk_00 + 0x5C, arg1->unk_02 + 0x48, "%2d", gBattleContext.unk_1194[1].unk_1E);
    Text_SetFont(4, 0);
    Text_SetEnvColor(0xFF, 0xFF, 0xFF, 0xFF);
    Text_Print(arg1->unk_00 + 0x82, arg1->unk_02 + 0x1F, Battle_GetMessageString(0x39));
    Text_Print(arg1->unk_00 + 0x82, arg1->unk_02 + 0x4F, Battle_GetMessageString(0x39));
    Text_SetupDL();
}

void BattlePrep_DrawStreakGiveUpPrompt(unk_D_84B2665C* arg0, unk_D_84B17550* arg1) {
    unk_func_800281D4 sp50;
    UNUSED s32 pad;
    s32 sp48;
    s32 temp_v0;

    DecodeBattleSaveData(&sp50, NULL);
    Gfx_DrawPanel(arg1->unk_00 + 0x10, arg1->unk_02 + 0x14, 0xA8, 0x3C, 0, 0, 0, 0xFF);
    Gfx_DrawPanel(arg1->unk_00 + 0x10, arg1->unk_02 + 0x60, 0xA8, 0x22, 0, 0, 0, 0xFF);
    BattlePrep_DrawCursorArrow(arg0, arg1->unk_00 + 0x14, arg1->unk_02 + 0x64);
    Text_ResetState();
    Text_SetFont(2, 0);
    Text_Print(arg1->unk_00 + 0x10, arg1->unk_02 + 6, Battle_GetMessageString(0x3A));
    Text_Print(arg1->unk_00 + 0x10, arg1->unk_02 + 0x52, Battle_GetMessageString(0x3B));
    MenuItem_Print(arg0, arg1->unk_00 + 0x2A, arg1->unk_02 + 0x64, 0, 1, Battle_GetMessageString(0x3C));
    MenuItem_Print(arg0, arg1->unk_00 + 0x2A, arg1->unk_02 + 0x64, 1, 1, Battle_GetMessageString(0x3D));
    Text_SetEnvColor(0xFF, 0x64, 0x64, 0xFF);

    if (sp50.unk_00 == 7) {
        Text_Print(arg1->unk_00 + 0x1E, arg1->unk_02 + 0x17, Battle_GetMessageString(sp50.unk_00 - 1));
        Text_Print(arg1->unk_00 + 0x1E, arg1->unk_02 + 0x26, Battle_GetMessageString(sp50.unk_01 + 0x13));
        if (sp50.unk_01 < 8) {
            if (sp50.unk_02 < 4) {
                Text_Print(arg1->unk_00 + 0x1E, arg1->unk_02 + 0x35, "%s %d", Battle_GetMessageString(0x37), sp50.unk_02);
            } else {
                Text_Print(arg1->unk_00 + 0x1E, arg1->unk_02 + 0x35, Battle_GetMessageString(0x3E));
            }
        } else {
            Text_Print(arg1->unk_00 + 0x1E, arg1->unk_02 + 0x35, "%s %d", Battle_GetMessageString(0x1B), sp50.unk_02);
        }
    } else if ((sp50.unk_00 == 3) || (sp50.unk_00 == 6)) {
        Text_Print(arg1->unk_00 + 0x1E, arg1->unk_02 + 0x17, Battle_GetMessageString(sp50.unk_00 - 1));
        Text_Print(arg1->unk_00 + 0x1E, arg1->unk_02 + 0x26, Battle_GetMessageString(sp50.unk_01 + 7));
        Text_Print(arg1->unk_00 + 0x1E, arg1->unk_02 + 0x35, Battle_GetMessageString(sp50.unk_02 + 0xA));
    } else {
        Text_Print(arg1->unk_00 + 0x1E, arg1->unk_02 + 0x17, Battle_GetMessageString(sp50.unk_00 - 1));
        Text_Print(arg1->unk_00 + 0x1E, arg1->unk_02 + 0x26, Battle_GetMessageString(sp50.unk_02 + 0xA));
    }

    if (sp50.unk_00 != 7) {
        Text_SetFont(1, 0);
        Text_SetEnvColor(0xFF, 0xFF, 0xFF, 0xFF);
        Text_Print(arg1->unk_00 + 0x64, arg1->unk_02 + 0x43, "%s %d", Battle_GetMessageString(0x2C), sp50.unk_04);
    }

    if (arg0->unk_04 == 0) {
        sp48 = (arg1->unk_04 - MeasureTextWidth(1, 0, Battle_GetMessageString(0x3F))) / 2;
        Text_SetFont(1, 0);
        Text_SetEnvColor(0xFF, 0xFF, 0, 0xFF);
        Text_SetLineHeight(0xC);
        Text_Print(arg1->unk_00 + sp48, arg1->unk_02 + 0x86, Battle_GetMessageString(0x3F));
    }

    Text_SetupDL();

    if (sp50.unk_03 == 1) {
        temp_v0 = MeasureTextWidth(1, 0, Battle_GetMessageString(sp50.unk_00 - 1));

        gSPDisplayList(gDisplayListHead++, gPrefDL_Border);

        Gfx_DrawSpriteRGBA16(arg1->unk_00 + temp_v0 + 0x20, arg1->unk_02 + 0x15, 0x10, 0x10, D_3027690, 0x10, 0);

        gSPDisplayList(gDisplayListHead++, gPrefDL_End);
    }
}

void RenderMenuPanel(unk_D_84B2665C* arg0) {
    unk_D_84B17550* temp_s0;
    s16 temp_a1;
    s16 var_a3;

    if ((arg0->unk_00 != 0) && (arg0->unk_02 > 0)) {
        temp_s0 = &gMenuPanelDefs[arg0->unk_01 - 1];

        if (arg0->unk_02 < 4) {
            var_a3 = (temp_s0->unk_06 * arg0->unk_02) / 4;
            if (var_a3 < 0x10) {
                var_a3 = 0x10;
            }

            temp_a1 = temp_s0->unk_02 + ((temp_s0->unk_06 - var_a3) / 2);
            if (temp_s0->unk_0C == 0) {
                DrawPanel(temp_s0->unk_00, temp_a1, temp_s0->unk_04, var_a3, temp_s0->unk_0A);
            } else {
                Gfx_DrawPanel(temp_s0->unk_00, temp_a1, temp_s0->unk_04, var_a3, 0x1E, 0x1E, 0x82, 0xFF);
            }
        } else {
            if (temp_s0->unk_0C == 0) {
                DrawPanel(temp_s0->unk_00, temp_s0->unk_02, temp_s0->unk_04, temp_s0->unk_06, temp_s0->unk_0A);
            } else {
                Gfx_DrawPanel(temp_s0->unk_00, temp_s0->unk_02, temp_s0->unk_04, temp_s0->unk_06, 0x1E, 0x1E, 0x82,
                              0xFF);
            }

            switch (arg0->unk_01) {
                case 1:
                    RenderBattleStatusPanel(arg0, temp_s0);
                    break;

                case 2:
                    RenderBattleStatusPanel(arg0, temp_s0);
                    break;

                case 3:
                    RenderBattleOptionsPanel(arg0, temp_s0);
                    break;

                case 4:
                    RenderBattleSummaryPanel(arg0, temp_s0);
                    break;

                case 5:
                    RenderBattleHPPanel(arg0, temp_s0);
                    break;

                case 6:
                    RenderBattleScorePanel(arg0, temp_s0);
                    break;

                case 7:
                    RenderBattleModeTitle(arg0, temp_s0);
                    break;

                case 8:
                    RenderBattleMatchupPanel(arg0, temp_s0);
                    break;

                case 9:
                    BattlePrep_DrawTeamPreview(arg0, temp_s0);
                    break;

                case 10:
                    BattlePrep_DrawStreakGiveUpPrompt(arg0, temp_s0);
                    break;
            }
        }
    }
}

void BattlePrep_RunQuitMenu(unk_D_84B2665C* arg0) {
    unk_D_84B17550* sp24;
    s16 sp22;
    s32 tmp;

    sp24 = &gMenuPanelDefs[arg0->unk_01 - 1];
    sp22 = sp24->unk_08 - 1;

    if (BTN_IS_PRESSED(gPlayer1Controller, BTN_A)) {
        tmp = sp24->unk_10 >> (arg0->unk_04 * 3);
        switch (tmp & 7) {
            case 1:
                PlaySoundEffect(3);
                break;

            case 2:
                PlaySoundEffect(2);
                break;

            case 3:
                PlaySoundEffect(0x1C);
                break;

            case 4:
                PlaySoundEffect(0x20);
                break;

            case 5:
                PlaySoundEffect(0x1D);
                break;

            case 6:
                PlaySoundEffect(0x21);
                break;
        }
        arg0->unk_00 = 2;
    } else if (BTN_IS_PRESSED(gPlayer1Controller, BTN_DUP)) {
        PlaySoundEffect(1);
        do {
            arg0->unk_04--;
            if (arg0->unk_04 < 0) {
                arg0->unk_04 = sp22;
            }
        } while (!(sp24->unk_0E & (1 << arg0->unk_04)));
    } else if (BTN_IS_PRESSED(gPlayer1Controller, BTN_DDOWN)) {
        PlaySoundEffect(1);
        do {
            arg0->unk_04++;
            if (sp22 < arg0->unk_04) {
                arg0->unk_04 = 0;
            }
        } while (!(sp24->unk_0E & (1 << arg0->unk_04)));
    }
}

void BattlePrep_RuleWindowExpanding(unk_D_84B2665C* arg0) {
    arg0->unk_02++;
    if (arg0->unk_02 >= 5) {
        arg0->unk_02 = 4;
        arg0->unk_00 = 3;
    }
}

void BattlePrep_RuleWindowCollapsing(unk_D_84B2665C* arg0) {
    arg0->unk_02--;
    if (arg0->unk_02 < 0) {
        arg0->unk_02 = 0;
        arg0->unk_00 = 4;
    }
}

void UI_UpdatePanel(unk_D_84B2665C* arg0) {
    switch (arg0->unk_00) {
        case 1:
            BattlePrep_RuleWindowExpanding(arg0);
            break;

        case 2:
            BattlePrep_RuleWindowCollapsing(arg0);
            break;

        case 3:
            BattlePrep_RunQuitMenu(arg0);
            break;
    }
}

void Menu_SetOption(unk_D_84B2665C* arg0, s16 arg1) {
    unk_D_84B17550* ptr = &gMenuPanelDefs[arg1 - 1];

    arg0->unk_01 = arg1;
    arg0->unk_02 = 0;
    arg0->unk_04 = 0;
    arg0->unk_00 = 1;

    ptr->unk_0E = -1;

    PlaySoundEffect(4);

    if (arg1 - 1 == 2) {
        if (gBattleContext.unk_11F3 == 0) {
            ptr->unk_0E &= ~3;
        }
        if (gBattleContext.unk_11F5 & 2) {
            ptr->unk_0E &= ~4;
        }
    } else if (arg1 - 1 == 3) {
        if (gBattleContext.unk_11F5 & 2) {
            ptr->unk_0E &= ~1;
        }
    } else if ((arg1 - 1 == 4) &&
               ((gBattleContext.unk_1194[0].unk_1E >= 0x63) || (gBattleContext.unk_1194[1].unk_1E >= 0x63))) {
        ptr->unk_0E &= ~1;
    }

    while (!(ptr->unk_0E & (1 << arg0->unk_04))) {
        arg0->unk_04++;
    }
}

void BattleMenu_UpdateState(unk_D_84B2665C* arg0) {
    arg0->unk_00 = 0;
    arg0->unk_01 = 0;
    arg0->unk_02 = 0;
}

s32 Menu_GetInput(unk_D_84B2665C* arg0) {
    if (arg0->unk_00 == 4) {
        arg0->unk_00 = 0;
        return arg0->unk_04;
    }
    return -1;
}
