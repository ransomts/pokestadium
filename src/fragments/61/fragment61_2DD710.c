#include "fragment61.h"
#include "src/1AB70.h"
#include "src/1CF30.h"
#include "src/232C0.h"
#include "src/26820.h"
#include "src/49790.h"
#include "src/hal_libc.h"

s16 gSlotPosXOffsets[] = { 0x78, 0xFC, 0x180, 0x78, 0xFC, 0x180 };
s16 gSlotPosYOffsets[] = {
    4, 4, 4, 0x30, 0x30, 0x30,
};

void DrawSlotBackground(s16 arg0, s16 arg1, s32 arg2) {
    if (arg2 & 0x80000000) {
        DrawColoredBox(arg0, arg1, 0x84, 0x2C, 0x64, 0x64, 0xC8, 0xFF);
    } else {
        DrawColoredBox(arg0, arg1, 0x84, 0x2C, 0x3C, 0x3C, 0xA0, 0xFF);
    }
}

void DrawSlotGrid(gItemPanel* arg0, s16 arg1, s16 arg2) {
    s16 i;

    DrawBorderedBox(arg1, arg2, 0x208, 0x60);
    if (((gBattleContext.unk_0001 == 0) || (gBattleContext.unk_0001 == 8)) && (arg0->unk_0004 != 0) && (arg0->unk_0006 > 0) &&
        (arg0->unk_0006 < 6)) {
        DrawColoredBox(arg1 + 4, arg2 + 4, 0x74, 0x58, 0, 0, 0, 0xFF);

        gSPDisplayList(gDisplayListHead++, gPrefDL_Border);

        Gfx_DrawSpriteRGBA16(arg1 + 0x32, arg2 + 0x32, 0x14, 0x14, D_20068E0, 0x14, 0);

        gSPDisplayList(gDisplayListHead++, gPrefDL_End);
    } else {
        DrawColoredBox(arg1 + 4, arg2 + 4, 0x74, 0x58, 0x64, 0x64, 0xC8, 0xFF);
    }

    for (i = 0; i < 6; i++) {
        s16 tmp1 = gSlotPosXOffsets[i] + arg1;
        s16 tmp2 = gSlotPosYOffsets[i] + arg2;

        DrawSlotBackground(tmp1, tmp2, arg0->unk_0030[i].raw);
    }
}

void DrawSelectionRect(gItemPanel* arg0) {
    s16 temp_s0 = arg0->unk_0018 + (arg0->unk_0010 * 0x84) + 0x78;
    s16 temp_a1 = arg0->unk_001A + (arg0->unk_0012 * 0x2C) + 4;

    if (arg0->unk_0001 == 0xD) {
        if (arg0->unk_000C > 0) {
            temp_a1 = ((temp_a1 + ((arg0->unk_000C * 0x2C) / 4)) - 0x2C);
        } else {
            temp_a1 = (temp_a1 + ((arg0->unk_000C * 0x2C) / 4) + 0x2C);
        }
        DrawAnimatedGoldBorder(temp_s0, temp_a1, 0x84, 0x2C);
    } else if (arg0->unk_0001 == 0xC) {
        if (arg0->unk_000C > 0) {
            temp_s0 = ((temp_s0 + ((arg0->unk_000C * 0x84) / 4)) - 0x84);
        } else {
            temp_s0 = (temp_s0 + ((arg0->unk_000C * 0x84) / 4) + 0x84);
        }
        DrawAnimatedGoldBorder(temp_s0, temp_a1, 0x84, 0x2C);
    } else if (arg0->unk_0001 == 8) {
        DrawAnimatedGoldBorder(temp_s0, temp_a1, 0x84, 0x2C);
    }
}

void DrawItemInfoPanel(gItemPanel* arg0, s32 arg1) {
    char* temp_v0_10;
    char* temp_v0_4;
    char* temp_v0_5;
    char* temp_v0_6;
    char* temp_v0_7;
    char* temp_v0_8;
    s32 i;
    s16 sp42;
    s16 sp40;
    char* temp_v0_9;

    if ((arg0->unk_0001 != 1) && (arg0->unk_0001 != 0) && ((arg1 != 0) || (arg0->unk_0003 != 0))) {
        DrawSlotGrid(arg0, arg0->unk_0018, arg0->unk_001A);

        gSPDisplayList(gDisplayListHead++, gPrefDL_Border);

        for (i = 0; i < 6; i++) {
            if (arg0->unk_0030[i].unk_004.unk_00.unk_00 != 0) {
                s16 tmp1 = gSlotPosXOffsets[i] + arg0->unk_0018 + 2;
                s16 tmp2 = gSlotPosYOffsets[i] + arg0->unk_001A + 2;

                Gfx_DrawSpriteRGBA16(tmp1, tmp2, 0x28, 0x28, arg0->unk_0030[i].unk_058, 0x28, 0);
            }
        }

        gSPDisplayList(gDisplayListHead++, gPrefDL_End);

        Text_ResetState();

        if (((gBattleContext.unk_0001 == 0) || (gBattleContext.unk_0001 == 8)) && (arg0->unk_0004 != 0) &&
            (arg0->unk_0006 > 0) && (arg0->unk_0006 < 6)) {
            Text_SetFont(8, 0);
            temp_v0_4 = GetMessageBank1AString(arg0->unk_0006 + 0x2A);
            Text_Print((arg0->unk_0018 - (MeasureTextWidth(8, 0, temp_v0_4) / 2)) + 0x3C, arg0->unk_001A + 8,
                          temp_v0_4);
            if (arg0->unk_0000 == 0) {
                temp_v0_5 = GetMessageBank1AString(0x31);
                Text_Print((arg0->unk_0018 - (MeasureTextWidth(8, 0, temp_v0_5) / 2)) + 0x3C, arg0->unk_001A + 0x1C,
                              temp_v0_5);
            } else {
                temp_v0_6 = GetMessageBank1AString(0x32);
                Text_Print((arg0->unk_0018 - (MeasureTextWidth(8, 0, temp_v0_6) / 2)) + 0x3C, arg0->unk_001A + 0x1C,
                              temp_v0_6);
            }
            Text_SetFont(4, 0);
            temp_v0_7 = GetMessageBank1AString(0x33);
            Text_Print((arg0->unk_0018 - (MeasureTextWidth(4, 0, temp_v0_7) / 2)) + 0x3C, arg0->unk_001A + 0x46,
                          temp_v0_7);
        } else {
            Text_SetFont(4, 0);
            if (arg0->unk_0000 == 0) {
                temp_v0_8 = GetMessageBank1AString(0x34);
                Text_Print((arg0->unk_0018 - (MeasureTextWidth(4, 0, temp_v0_8) / 2)) + 0x3C, arg0->unk_001A + 9,
                              temp_v0_8);
            } else {
                temp_v0_9 = GetMessageBank1AString(0x35);
                Text_Print((arg0->unk_0018 - (MeasureTextWidth(4, 0, temp_v0_9) / 2)) + 0x3C, arg0->unk_001A + 9,
                              temp_v0_9);
            }
            temp_v0_10 = GetMessageBank1AString(0x36);
            Text_Print((arg0->unk_0018 - (MeasureTextWidth(4, 0, temp_v0_10) / 2)) + 0x3C, arg0->unk_001A + 0x1A,
                          temp_v0_10);
            Text_SetFont(8, 0);
            Text_Print((arg0->unk_0018 - (MeasureTextWidth(8, 0, arg0->unk_001E) / 2)) + 0x3C, arg0->unk_001A + 0x2F,
                          arg0->unk_001E);
            Text_SetFont(4, 0);
            Text_Print((arg0->unk_0018 - (MeasureTextWidth(4, 0, "ID  00000") / 2)) + 0x3C, arg0->unk_001A + 0x46,
                          "ID  %05d", arg0->unk_001C);
        }
        Text_SetFont(4, 0);

        for (i = 0; i < 6; i++) {
            if (arg0->unk_0030[i].unk_004.unk_00.unk_00 != 0) {
                s16 tmp1 = gSlotPosXOffsets[i] + arg0->unk_0018 + 0x2C;
                s16 tmp2 = gSlotPosYOffsets[i] + arg0->unk_001A + 5;

                Text_Print(tmp1, tmp2, arg0->unk_0030[i].unk_004.unk_30);
            }
        }

        Text_SetFont(4, 0);

        for (i = 0; i < 6; i++) {
            if (arg0->unk_0030[i].unk_004.unk_00.unk_00 != 0) {
                sp42 = gSlotPosXOffsets[i] + arg0->unk_0018 + 0x2C;
                sp40 = gSlotPosYOffsets[i] + arg0->unk_001A + 0x17;
                Text_Print(sp42, sp40, "%s %d", GetMessageBank06String(0x15), arg0->unk_0030[i].unk_004.unk_24);
            }
        }

        Text_SetupDL();
        DrawSelectionRect(arg0);

        if (arg0->unk_0003 > 0) {
            arg0->unk_0003--;
        }
    }
}

void ClearSlotItem(gItemPanel* arg0) {
    s16 temp_v0 = arg0->unk_0010 + (arg0->unk_0012 * 3);

    if (arg0->unk_0030[temp_v0].unk_004.unk_00.unk_00 != 0) {
        arg0->unk_0030[temp_v0].unk_004.unk_00.unk_00 = 0;
        arg0->unk_0030[temp_v0].raw = 0;
        arg0->unk_0006 -= 1;
    }
}

void MarkSlotForRemoval(gItemPanel* arg0) {
    s16 sp1E = arg0->unk_0010 + (arg0->unk_0012 * 3);

    if (RequestNextPokemon(arg0->pokemonPanel) != 0) {
        if (arg0->unk_0030[sp1E].unk_004.unk_00.unk_00 != 0) {
            arg0->unk_0030[sp1E].unk_004.unk_00.unk_00 = 0;
            arg0->unk_0030[sp1E].raw = 0;
            arg0->unk_0006--;
        }
        arg0->unk_0030[sp1E].raw |= 0x80000000;
        arg0->unk_0004 = 1;
        arg0->unk_0001 = 3;
    }
}

s32 GbsSyncItemData(gItemPanel* arg0) {
    s16 i;
    s16 temp_v0;
    s32 var_s0 = 0;
    unk_func_80022C28_ret* temp_s3;

    temp_v0 = Deck_FindFirstFreeTeamSlot();
    if (temp_v0 < 0xA) {
        temp_s3 = GbsBlock_CreateWithString(0x10, 0, temp_v0, arg0->unk_001E, arg0->unk_001E, arg0->unk_001C);

        for (i = 0; i < arg0->unk_0006; i++) {
            GbsBlock_WriteEntries(&arg0->unk_0030[i].unk_004.unk_00.unk_00, 1, temp_s3);
        }

        CommitAndFreeGbsBlock(temp_s3);
        GbsSyncAllBanks();
        var_s0 = 1;
    }
    return var_s0;
}

s32 CheckStatThresholdForMode(gItemPanel* arg0) {
    UNUSED s32 pad;
    s32 temp_v1;
    s16 i;
    s16 sp8[3];

    for (i = 0; i < 3; i++) {
        sp8[i] = 0x3E7;
    }

    for (i = 0; i < arg0->unk_0006; i++) {
        temp_v1 = arg0->unk_0030[i].unk_004.unk_24;
        if (sp8[2] >= temp_v1) {
            sp8[2] = temp_v1;
        }

        if (sp8[1] >= temp_v1) {
            sp8[2] = sp8[1];
            sp8[1] = temp_v1;
        }

        if (sp8[0] >= temp_v1) {
            sp8[1] = sp8[0];
            sp8[0] = temp_v1;
        }
    }

    switch (gBattleContext.unk_0001) {
        default:
            temp_v1 = 0;
            break;

        case 3:
            temp_v1 = (s16)(sp8[0] + sp8[1] + sp8[2]);
            temp_v1 = temp_v1 >= 0x9C;
            break;

        case 4:
            temp_v1 = (s16)(sp8[0] + sp8[1] + sp8[2]);
            temp_v1 = temp_v1 >= 0x51;
            break;

        case 5:
            temp_v1 = (s16)(sp8[0] + sp8[1] + sp8[2]);
            temp_v1 = temp_v1 >= 0x33;
            break;
    }
    return temp_v1;
}

void SetPanelPositionOffscreen(gItemPanel* arg0) {
    arg0->unk_0018 = arg0->unk_0014 + 0x280;
    arg0->unk_001A = arg0->unk_0016;
}

void SetPanelPositionOnscreen(gItemPanel* arg0) {
    arg0->unk_0018 = arg0->unk_0014;
    arg0->unk_001A = arg0->unk_0016;
}

void StartItemMoveAnimation(gItemPanel* a0) {
    gItemPanel* arg0 = a0;
    s16 temp_v0;
    s16 temp_v1;
    s16 tmp;

    TeamSelection_RulePrompt_BeginClose(1);
    if (TeamSelection_RulePrompt_TryFinish(1) >= 0) {
        tmp = a0->unk_0010 + a0->unk_0012 * 3;

        temp_v0 = a0->unk_0014 + (a0->unk_0010 * 0x84) + 0x74;
        temp_v1 = a0->unk_0016 + (a0->unk_0012 * 0x2C);

        arg0->unk_0030[tmp].raw |= 0x80000000;
        MoveScreen_Start(a0->moveScreen, a0->unk_0002, 0x30, 0xEC, temp_v0, temp_v1, &a0->unk_0030[tmp], 2);
        a0->unk_0001 = 6;
    }
    a0->unk_0018 = a0->unk_0014;
    a0->unk_001A = a0->unk_0016;
    a0->unk_0003 = 2;
}

void HandleItemMoveResult(gItemPanel* arg0) {
    s16 sp26 = arg0->unk_0010 + (arg0->unk_0012 * 3);
    s32 temp_v0 = GetSelectedMoveIndex(arg0->moveScreen);

    if (temp_v0 == 1) {
        RequestNextPokemon(arg0->pokemonPanel);
        arg0->unk_0004 = 0;
        arg0->unk_0001 = 3;
    } else if (temp_v0 == 2) {
        arg0->unk_0030[sp26].raw &= ~0x80000000;
        TeamSelection_RulePrompt_Open(1, NULL);
        arg0->unk_000A = 0;
        arg0->unk_0001 = 8;
    }
    arg0->unk_0018 = arg0->unk_0014;
    arg0->unk_001A = arg0->unk_0016;
}

void UpdatePanelSlideDown(gItemPanel* arg0) {
    arg0->unk_000A++;
    if (arg0->unk_000A <= 0) {
        arg0->unk_0018 = arg0->unk_0014 + 0x280;
        arg0->unk_0003 = 2;
    } else if (arg0->unk_000A == 0xA) {
        arg0->unk_000A = 0;
        arg0->unk_0018 = arg0->unk_0014;
        if (arg0->unk_0006 == arg0->unk_0008) {
            arg0->unk_0003 = 2;
            arg0->unk_0001 = 7;
        } else {
            // clang-format off
            *(s8*)&arg0->unk_0001 = 2; arg0->unk_0003 = 2;
            // clang-format on
        }
    } else {
        arg0->unk_0018 = (arg0->unk_0014 - (arg0->unk_000A << 6)) + 0x280;
        arg0->unk_0003 = 2;
    }
    arg0->unk_001A = arg0->unk_0016;
}

void UpdatePanelSlideUp(gItemPanel* arg0) {
    arg0->unk_000A++;
    if (arg0->unk_000A == 0xA) {
        arg0->unk_0001 = 0;
        arg0->unk_000A = 0;
        arg0->unk_0018 = arg0->unk_0014 + 0x280;
    } else {
        arg0->unk_0018 = arg0->unk_0014 - (arg0->unk_000A << 6);
    }
    arg0->unk_001A = arg0->unk_0016;
    arg0->unk_0003 = 2;
}

void ItemPanel_RemoveSelected(gItemPanel* arg0) {
    MarkSlotForRemoval(arg0);
    arg0->unk_0018 = arg0->unk_0014;
    arg0->unk_001A = arg0->unk_0016;
    arg0->unk_0003 = 2;
}

void ItemPanel_MoveCursorLeft(gItemPanel* arg0) {
    if (arg0->unk_0010 > 0) {
        arg0->unk_0010--;
        arg0->unk_000C = -1;
        arg0->unk_000E = -4;
        arg0->unk_0001 = 0xC;
        PlaySoundEffect(1);
    }
}

void ItemPanel_MoveCursorRight(gItemPanel* arg0) {
    if (arg0->unk_0010 < 2) {
        arg0->unk_0010++;
        arg0->unk_000C = 1;
        arg0->unk_000E = 4;
        arg0->unk_0001 = 0xC;
        PlaySoundEffect(1);
    }
}

void ItemPanel_MoveCursorUp(gItemPanel* arg0) {
    if (arg0->unk_0012 > 0) {
        arg0->unk_0012--;
        arg0->unk_000C = -1;
        arg0->unk_000E = -4;
        arg0->unk_0001 = 0xD;
        PlaySoundEffect(1);
    }
}

void ItemPanel_MoveCursorDown(gItemPanel* arg0) {
    if (arg0->unk_0012 <= 0) {
        arg0->unk_0012++;
        arg0->unk_000C = 1;
        arg0->unk_000E = 4;
        arg0->unk_0001 = 0xD;
        PlaySoundEffect(1);
    }
}

void ItemPanel_HandleInput(gItemPanel* arg0) {
    Controller* cont = &gControllers[arg0->unk_0002];

    if (arg0->unk_000A < 8) {
        arg0->unk_000A++;
    } else if (BTN_IS_PRESSED(cont, BTN_A)) {
        s32 temp_v0 = arg0->unk_0010 + (arg0->unk_0012 * 3);

        if (arg0->unk_0030[temp_v0].unk_004.unk_00.unk_00 != 0) {
            PlaySoundEffect(2);
            arg0->unk_0001 = 0xB;
        }
    } else if (BTN_IS_PRESSED(cont, BTN_B)) {
        PlaySoundEffect(3);
        arg0->unk_0001 = 0x10;
    } else if (BTN_IS_PRESSED(cont, BTN_DUP)) {
        ItemPanel_MoveCursorUp(arg0);
    } else if (BTN_IS_PRESSED(cont, BTN_DDOWN)) {
        ItemPanel_MoveCursorDown(arg0);
    } else if (BTN_IS_PRESSED(cont, BTN_DRIGHT)) {
        ItemPanel_MoveCursorRight(arg0);
    } else if (BTN_IS_PRESSED(cont, BTN_DLEFT)) {
        ItemPanel_MoveCursorLeft(arg0);
    }

    arg0->unk_0018 = arg0->unk_0014;
    arg0->unk_001A = arg0->unk_0016;
    arg0->unk_0003 = 2;
}

void ItemPanel_CheckModeTransition(gItemPanel* arg0) {
    TeamSelection_RulePrompt_BeginClose(1);
    if (TeamSelection_RulePrompt_TryFinish(1) >= 0) {
        if (CheckStatThresholdForMode(arg0) != 0) {
            arg0->unk_0001 = 0xF;
        } else if (arg0->unk_0000 == 0) {
            arg0->unk_0001 = 7;
        } else {
            arg0->unk_0001 = 0xE;
        }
    }
    arg0->unk_0003 = 2;
}

void ItemPanel_HandleMenuSelection(gItemPanel* arg0) {
    Controller* cont = &gControllers[arg0->unk_0002];
    s16 i;

    TeamSelection_RulePrompt_Open(0, cont);

    switch (TeamSelection_RulePrompt_TryFinish(0)) {
        case 0:
            i = arg0->unk_0006;
            if (i == 6) {
                i--;
            }
            arg0->unk_0010 = i % 3;
            arg0->unk_0012 = i / 3;
            arg0->unk_0008 = 6;
            arg0->unk_0001 = 2;
            break;

        case 1:
            TriggerSelectionAnim(arg0->pokemonPanel);
            arg0->unk_000A = 0;
            arg0->unk_0001 = 5;
            break;

        case 2:
            if (GbsSyncItemData(arg0) != 0) {
                arg0->unk_0001 = 9;
            } else {
                arg0->unk_0001 = 0xA;
            }
            break;

        case 3:
            TeamSelection_RulePrompt_Open(1, NULL);
            arg0->unk_0010 = 0;
            arg0->unk_0012 = 0;
            arg0->unk_000A = 0;
            arg0->unk_0001 = 8;
            break;

        case 4:
            for (i = 0; i < 6; i++) {
                arg0->unk_0030[i].raw = 0;
                arg0->unk_0030[i].unk_004.unk_00.unk_00 = 0;
            }

            SetMenuActive(arg0->pokemonPanel);

            arg0->unk_0006 = 0;
            arg0->unk_0010 = 0;
            arg0->unk_0012 = 0;
            arg0->unk_0008 = 6;
            arg0->unk_0001 = 2;
            break;
    }
    arg0->unk_0018 = arg0->unk_0014;
    arg0->unk_001A = arg0->unk_0016;
}

void ItemPanel_HandleAltMenuSelection(gItemPanel* arg0) {
    Controller* cont = &gControllers[arg0->unk_0002];
    s16 i;

    TeamSelection_RulePrompt_Open(0xA, cont);
    switch (TeamSelection_RulePrompt_TryFinish(0xA)) {
        case 0:
            i = arg0->unk_0006;
            if (i == 6) {
                i--;
            }
            arg0->unk_0010 = i % 3;
            arg0->unk_0012 = i / 3;
            arg0->unk_0008 = 6;
            arg0->unk_0001 = 2;
            break;

        case 1:
            TriggerSelectionAnim(arg0->pokemonPanel);
            RegistrationManager_Initialize(arg0->registrationManager, arg0->unk_001C, arg0->unk_001E, arg0->unk_0030);
            arg0->unk_0001 = 3;
            break;

        case 2:
            TeamSelection_RulePrompt_Open(1, NULL);
            arg0->unk_0010 = 0;
            arg0->unk_0012 = 0;
            arg0->unk_000A = 0;
            arg0->unk_0001 = 8;
            break;

        case 3:
            for (i = 0; i < 6; i++) {
                arg0->unk_0030[i].raw = 0;
                arg0->unk_0030[i].unk_004.unk_00.unk_00 = 0;
            }

            SetMenuActive(arg0->pokemonPanel);

            arg0->unk_0006 = 0;
            arg0->unk_0010 = 0;
            arg0->unk_0012 = 0;
            arg0->unk_0008 = 6;
            arg0->unk_0001 = 2;
            break;
    }

    arg0->unk_0018 = arg0->unk_0014;
    arg0->unk_001A = arg0->unk_0016;
}

void ItemPanel_HandleModeSpecificSelection(gItemPanel* arg0) {
    UNUSED s16 pad;
    s16 sp1C = 0xD;
    s32 temp_v0_2;
    Controller* cont = &gControllers[arg0->unk_0002];

    switch (gBattleContext.unk_0001) {
        case 3:
            break;

        case 4:
            sp1C = 0xE;
            break;

        case 5:
            sp1C = 0xF;
            break;
    }

    TeamSelection_RulePrompt_Open(sp1C, cont);

    temp_v0_2 = TeamSelection_RulePrompt_TryFinish(sp1C);
    if (temp_v0_2 != -1) {
        if (temp_v0_2 == 0) {
            arg0->unk_0010 = 2;
            arg0->unk_0012 = 1;
            arg0->unk_0008 = 6;
            arg0->unk_0001 = 2;
        } else {
            TeamSelection_RulePrompt_Open(1, NULL);
            arg0->unk_0010 = 0;
            arg0->unk_0012 = 0;
            arg0->unk_000A = 0;
            arg0->unk_0001 = 8;
        }
    }

    arg0->unk_0018 = arg0->unk_0014;
    arg0->unk_001A = arg0->unk_0016;
}

void ItemPanel_HandleActionSelection(gItemPanel* arg0) {
    Controller* cont = &gControllers[arg0->unk_0002];

    TeamSelection_RulePrompt_Open(2, cont);
    if (TeamSelection_RulePrompt_TryFinish(2) >= 0) {
        TriggerSelectionAnim(arg0->pokemonPanel);
        arg0->unk_000A = 0;
        arg0->unk_0001 = 5;
    }
}

void ItemPanel_HandleCancelSelection(gItemPanel* arg0) {
    Controller* cont = &gControllers[arg0->unk_0002];

    TeamSelection_RulePrompt_Open(3, cont);
    if (TeamSelection_RulePrompt_TryFinish(3) >= 0) {
        arg0->unk_0001 = 7;
    }
}

void ItemPanel_UpdateCursorAnim(gItemPanel* arg0) {
    if (arg0->unk_000E > 0) {
        arg0->unk_000C++;
        if (arg0->unk_000C >= arg0->unk_000E) {
            arg0->unk_0001 = 8;
        }
    } else {
        arg0->unk_000C--;
        if (arg0->unk_000E >= arg0->unk_000C) {
            arg0->unk_0001 = 8;
        }
    }
    arg0->unk_0018 = arg0->unk_0014;
    arg0->unk_001A = arg0->unk_0016;
    arg0->unk_0003 = 2;
}

s32 UpdateItemStateMachine(gItemPanel* arg0) {
    s32 sp1C = 0;

    switch (arg0->unk_0001) {
        case 0:
            SetPanelPositionOffscreen(arg0);
            break;

        case 1:
            SetPanelPositionOffscreen(arg0);
            break;

        case 3:
            SetPanelPositionOnscreen(arg0);
            break;

        case 2:
            ItemPanel_RemoveSelected(arg0);
            break;

        case 4:
            UpdatePanelSlideDown(arg0);
            sp1C = 1;
            break;

        case 5:
            UpdatePanelSlideUp(arg0);
            sp1C = 1;
            break;

        case 6:
            HandleItemMoveResult(arg0);
            break;

        case 7:
            ItemPanel_HandleMenuSelection(arg0);
            break;

        case 8:
            ItemPanel_HandleInput(arg0);
            break;

        case 9:
            ItemPanel_HandleActionSelection(arg0);
            break;

        case 10:
            ItemPanel_HandleCancelSelection(arg0);
            break;

        case 11:
            StartItemMoveAnimation(arg0);
            break;

        case 12:
            ItemPanel_UpdateCursorAnim(arg0);
            break;

        case 13:
            ItemPanel_UpdateCursorAnim(arg0);
            break;

        case 14:
            ItemPanel_HandleAltMenuSelection(arg0);
            break;

        case 15:
            ItemPanel_HandleModeSpecificSelection(arg0);
            break;

        case 16:
            ItemPanel_CheckModeTransition(arg0);
            break;
    }
    return sp1C;
}

s32 ItemPanel_Init(gItemPanel* arg0, unk_D_842168A0* arg1, unk_D_8423D3A8* arg2, unk_D_84229EB0* arg3, s16 arg4,
                  u16 arg5, char* arg6, s16 arg7, s16 arg8, s16 arg9) {
    s32 i;

    arg0->unk_0000 = arg4;
    arg0->unk_0001 = 1;
    arg0->unk_0002 = arg9;
    arg0->unk_0004 = 0;
    arg0->unk_0006 = 0;
    arg0->unk_0008 = 6;
    arg0->unk_000A = 0;
    arg0->unk_0010 = 0;
    arg0->unk_0012 = 0;
    arg0->unk_0014 = arg7;
    arg0->unk_0016 = arg8;
    arg0->unk_0018 = arg7 + 0x280;
    arg0->unk_001A = arg8;
    arg0->unk_001C = arg5;

    arg0->pokemonPanel = arg1;
    arg0->moveScreen = arg2;
    arg0->registrationManager = arg3;

    for (i = 0; i < 6; i++) {
        arg0->unk_0030[i].raw = 0;
        arg0->unk_0030[i].unk_004.unk_00.unk_00 = 0;
    }

    HAL_Strcpy(arg0->unk_001E, arg6);
    return 1;
}

s32 ItemPanel_StartSlideDown(gItemPanel* arg0, s16 arg1) {
    if (arg0->unk_0001 != 1) {
        return 0;
    }
    arg0->unk_0001 = 4;
    arg0->unk_000A = -arg1;
    return 1;
}

s32 ItemPanel_StartSlideUp(gItemPanel* arg0) {
    if (arg0->unk_0001 != 3) {
        return 0;
    }
    arg0->unk_0001 = 5;
    arg0->unk_000A = 0;
    return 1;
}

s32 ItemPanel_ClearAndReset(gItemPanel* arg0) {
    s16 i;

    if (arg0->unk_0001 != 3) {
        return 0;
    }

    for (i = 0; i < 6; i++) {
        arg0->unk_0030[i].raw = 0;
        arg0->unk_0030[i].unk_004.unk_00.unk_00 = 0;
    }

    SetMenuActive(arg0->pokemonPanel);
    arg0->unk_0006 = 0;
    arg0->unk_0008 = 6;
    arg0->unk_0010 = 0;
    arg0->unk_0012 = 0;
    arg0->unk_0001 = 2;
    return 1;
}

s32 ItemPanel_ConfirmSelection(gItemPanel* arg0) {
    s32 temp_v0;
    s32 temp_v1;

    temp_v1 = arg0->unk_0010 + (arg0->unk_0012 * 3);

    if (arg0->unk_0001 == 3) {
        if (arg0->unk_0006 == 0) {
            arg0->unk_0001 = 5;
            arg0->unk_000A = 0;
            return -1;
        }

        arg0->unk_0030[temp_v1].raw &= 0x7FFFFFFF;

        if (arg0->unk_0030[temp_v1].raw == 0) {
            temp_v0 = temp_v1 - 1;
            arg0->unk_0010 = temp_v0 % 3;
            arg0->unk_0012 = temp_v0 / 3;
            ClearSlotItem(arg0);
            arg0->unk_0001 = 2;
        } else {
            TeamSelection_RulePrompt_Open(1, NULL);
            arg0->unk_000A = 0;
            arg0->unk_0001 = 8;
        }
        return 1;
    }

    return 0;
}

s32 ItemPanel_AddItem(gItemPanel* arg0, unk_D_838067F0_0168_0000* arg1) {
    s32 var_v0 = arg0->unk_0010 + (arg0->unk_0012 * 3);

    if (arg0->unk_0001 != 3) {
        return 0;
    }

    if (arg0->unk_0030[var_v0].unk_004.unk_00.unk_00 == 0) {
        arg0->unk_0006 += 1;
    }

    arg0->unk_0030[var_v0] = *arg1;

    if (arg0->unk_0006 == arg0->unk_0008) {
        arg0->unk_0003 = 2;
        arg0->unk_0004 = 0;
        if (CheckStatThresholdForMode(arg0) != 0) {
            arg0->unk_0001 = 15;
        } else if (arg0->unk_0000 == 0) {
            arg0->unk_0001 = 7;
        } else {
            arg0->unk_0001 = 0xE;
        }
    } else {
        do {
            var_v0 = (var_v0 + 1) % 6;
        } while (arg0->unk_0030[var_v0].unk_004.unk_00.unk_00 != 0);
        arg0->unk_0010 = var_v0 % 3;
        arg0->unk_0012 = var_v0 / 3;
        arg0->unk_0001 = 2;
    }
    return 1;
}

s32 ItemPanel_RemoveCurrent(gItemPanel* arg0) {
    s32 idx = (arg0->unk_0010 + (arg0->unk_0012 * 3));

    if (arg0->unk_0001 != 3) {
        return 0;
    }

    if (arg0->unk_0006 == 0) {
        return 0;
    }

    if (arg0->unk_0004 == 0) {
        return 0;
    }

    if ((gBattleContext.unk_0001 != 0) && (gBattleContext.unk_0000 != 8)) {
        return 0;
    }

    arg0->unk_0003 = 2;
    arg0->unk_0004 = 0;
    arg0->unk_0008 = arg0->unk_0006;
    arg0->unk_0030[idx].raw = 0;

    if (arg0->unk_0000 == 0) {
        arg0->unk_0001 = 7;
    } else {
        arg0->unk_0001 = 0xE;
    }
    return 1;
}

s32 ItemPanel_IsItemDuplicate(gItemPanel* arg0, unk_D_838067F0_0168_0000* arg1) {
    s32 i;
    u8 temp_a2;
    unk_D_838067F0_0168_0000* ptr;

    ptr = &arg0->unk_0030[0];
    temp_a2 = arg1->unk_004.unk_00.unk_00;

    if (arg1->unk_004.unk_00.unk_00 == 0) {
        return 0;
    }

    for (i = 0; i < 6; i++, ptr++) {
        if ((ptr->unk_004.unk_00.unk_00 != 0) && !(ptr->raw & 0x80000000)) {
            if (gBattleContext.unk_0001 == 0) {
                if (ptr->raw == arg1->raw) {
                    return 0;
                }
            } else if (ptr->unk_004.unk_00.unk_00 == temp_a2) {
                return 0;
            }
        }
    }

    return 1;
}

s32 ItemPanel_HasItem(gItemPanel* arg0, unk_D_838067F0_0168_0000* arg1) {
    s32 i;
    unk_D_838067F0_0168_0000* ptr;

    if (arg1->unk_004.unk_00.unk_00 == 0) {
        return 0;
    }

    ptr = &arg0->unk_0030[0];
    for (i = 0; i < 6; i++, ptr++) {
        if ((ptr->unk_004.unk_00.unk_00 != 0) && !(ptr->raw & 0x80000000) && (ptr->raw == arg1->raw)) {
            return 1;
        }
    }

    return 0;
}

s32 ItemPanel_IsOffscreen(gItemPanel* arg0) {
    return arg0->unk_0001 == 0;
}

void ItemPanel_LoadItems(gItemPanel* arg0, PokemonData* arg1, s16 arg2) {
    s32 i;

    arg0->unk_0006 = arg2;
    arg0->unk_0008 = arg2;

    for (i = 0; i < arg2; i++) {
        PokeIcon_LoadModelTextureForMon(arg0->unk_0030[i].unk_058, 0, &arg1[i]);

        arg0->unk_0030[i].unk_004 = arg1[i];

        arg0->unk_0030[i].unk_000 = (arg1[i].unk_52 & 0x70) >> 4;
        arg0->unk_0030[i].unk_001 = arg1[i].unk_52 & 0xF;
        arg0->unk_0030[i].unk_002 = arg1[i].unk_53;
        arg0->unk_0030[i].unk_003 = arg1[i].unk_00.unk_00;
    }
}
