#include "fragment56.h"
#include "src/1CF30.h"
#include "src/20470.h"
#include "src/26820.h"
#include "src/29BA0.h"
#include "src/2E110.h"
#include "src/3D140.h"
#include "src/3FB0.h"
#include "src/49790.h"
#include "src/4BA90.h"
#include "src/6A40.h"
#include "src/memory.h"
#include "src/stage_loader.h"

static char** gPrefMessageBank;
static s16 gPrefSelectedOption;
static u16 gPrefToggleFlags;

void func_82C00020(void) {
    gDPPipeSync(gDisplayListHead++);

    gDPSetCycleType(gDisplayListHead++, G_CYC_1CYCLE);
    gDPSetTexturePersp(gDisplayListHead++, G_TP_NONE);
    gDPSetCombineLERP(gDisplayListHead++, ENVIRONMENT, PRIMITIVE, TEXEL0, PRIMITIVE, TEXEL0, 0, ENVIRONMENT, 0,
                      ENVIRONMENT, PRIMITIVE, TEXEL0, PRIMITIVE, TEXEL0, 0, ENVIRONMENT, 0);
    gDPSetRenderMode(gDisplayListHead++, G_RM_OPA_SURF, G_RM_OPA_SURF2);
    gDPSetEnvColor(gDisplayListHead++, 50, 150, 80, 255);
    gDPSetPrimColor(gDisplayListHead++, 0, 0, 20, 100, 50, 255);
    gSPClearGeometryMode(gDisplayListHead++, G_ZBUFFER | G_LIGHTING);

    gDPLoadTextureBlock_4b(gDisplayListHead++, gPrefBackgroundTexture, G_IM_FMT_I, 128, 64, 0, G_TX_NOMIRROR | G_TX_WRAP,
                           G_TX_NOMIRROR | G_TX_WRAP, 7, 6, G_TX_NOLOD, G_TX_NOLOD);

    Gfx_DrawTextureRect(0, 0, 0x280, 0x1E0, 0, 0, 0x400, 0x400, 0);

    gSPDisplayList(gDisplayListHead++, gPrefDL_End);
}

void func_82C0025C(s16 arg0, s16 arg1, s16 arg2, s16 arg3, u8 arg4, u8 arg5, u8 arg6, u8 arg7) {
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

void func_82C00574(s16 arg0, s16 arg1) {
    gDPSetEnvColor(gDisplayListHead++, 60, 60, 160, 255);

    Gfx_DrawSpriteI4(arg0, arg1, 0x10, 0x1C, D_30242C0, 0x10, 0);
    Gfx_DrawSpriteI4(arg0 + 0x68, arg1, 0x10, 0x1C, D_30243A0, 0x10, 0);
    Gfx_DrawTextureRect(arg0 + 0x10, arg1, 0x58, 0x1C, 0, 0, 0, 0x400, 0);
}

void func_82C00658(s16 arg0, s32 arg1) {
    UNUSED s32 pad;
    s32 var_a2;
    s16 sp30 = (arg0 * 0x16) + 0xA;
    s16 sp2C = ((0xBA - sp30) / 2) + 0xE5;

    if (arg0 > 0) {
        DrawSimplePanel(0x89, sp2C, 0x16E, sp30);

        if (arg0 == 8) {
            char* sp40;

            func_82C0025C(0x90, sp2C + 7, 0x160, 0x20, 0x3C, 0x3C, 0xA0, 0xFF);
            func_82C0025C(0x90, sp2C + 0x27, 0x160, 0x8C, 0x1E, 0x1E, 0x64, 0xFF);

            if (arg1 != 0) {
                AnimateIconOffset(0x95, sp2C + (gPrefSelectedOption * 0x20) + 0x31);
            }

            gSPDisplayList(gDisplayListHead++, gPrefDL_Border);

            func_82C00574(0x168, sp2C + 0x30);
            func_82C00574(0x168, sp2C + 0x50);

            gSPDisplayList(gDisplayListHead++, gPrefDL_End);

            Text_ResetState();
            Text_SetFont(0x10, 0);
            sp40 = GetMessageString(NULL, 0, gPrefMessageBank, 4);
            Text_Print(0x140 - (MeasureTextWidth(0x10, 0, sp40) / 2), sp2C + 0xA, sp40);

            if (gPrefSelectedOption == 0) {
                var_a2 = 0;
            } else {
                var_a2 = 0xFF;
            }

            Text_SetEnvColor(0xFF, 0xFF, var_a2, 0xFF);
            Text_Print(0xBB, sp2C + 0x31, GetMessageString(NULL, 0, gPrefMessageBank, 5));
            sp40 = GetMessageString(NULL, 0, gPrefMessageBank, (gPrefToggleFlags & 1) != 0);
            Text_Print(0x1A4 - (MeasureTextWidth(0x10, 0, sp40) / 2), sp2C + 0x31, sp40);

            if (gPrefSelectedOption == 1) {
                var_a2 = 0;
            } else {
                var_a2 = 0xFF;
            }

            Text_SetEnvColor(0xFF, 0xFF, var_a2, 0xFF);
            Text_Print(0xBB, sp2C + 0x51, GetMessageString(NULL, 0, gPrefMessageBank, 6));
            sp40 = GetMessageString(NULL, 0, gPrefMessageBank, ((gPrefToggleFlags & 2) != 0) + 2);
            Text_Print(0x1A4 - (MeasureTextWidth(0x10, 0, sp40) / 2), sp2C + 0x51, sp40);

            if (gPrefSelectedOption == 2) {
                var_a2 = 0;
            } else {
                var_a2 = 0xFF;
            }

            Text_SetEnvColor(0xFF, 0xFF, var_a2, 0xFF);
            Text_Print(0xBB, sp2C + 0x71, GetMessageString(NULL, 0, gPrefMessageBank, 7));

            if (gPrefSelectedOption == 3) {
                var_a2 = 0;
            } else {
                var_a2 = 0xFF;
            }

            Text_SetEnvColor(0xFF, 0xFF, var_a2, 0xFF);
            Text_Print(0xBB, sp2C + 0x91, GetMessageString(NULL, 0, gPrefMessageBank, 8));
            Text_SetupDL();
        }
    }
}

void func_82C00AA4(s32 arg0, s32 arg1, s32 arg2) {
    UNUSED s32 pad;
    s16 sp28 = (arg2 * 0x11) + 2;
    s16 sp24 = ((0x8A - sp28) / 2) + 0x54;

    if (arg2 > 0) {
        DrawPanel(0x51, sp24, 0x1DE, sp28, 0x6109);

        if (arg2 == 8) {
            AnimateIconOffset(0x119, sp24 + (arg1 * 0x1C) + 0x48);
            Text_ResetState();
            Text_SetFont(0x10, 0);
            Text_SetEnvColor(0xFF, 0xFF, 0x64, 0xFF);

            if (arg0 == 0) {
                Text_SetLineHeight(0x1C);
                Text_Print(0x63, sp24 + 0xC, GetMessageString(NULL, 0, gPrefMessageBank, 9));
            } else {
                Text_SetLineHeight(0x1C);
                Text_Print(0x63, sp24 + 0xC, GetMessageString(NULL, 0, gPrefMessageBank, 0xA));
            }

            Text_SetEnvColor(0xFF, 0xFF, (arg1 == 0) ? 0 : 0xFF, 0xFF);
            Text_Print(0x141, sp24 + 0x48, GetMessageString(NULL, 0, gPrefMessageBank, 0xB));
            Text_SetEnvColor(0xFF, 0xFF, (arg1 == 1) ? 0 : 0xFF, 0xFF);
            Text_Print(0x141, sp24 + 0x64, GetMessageString(NULL, 0, gPrefMessageBank, 0xC));
            Text_SetupDL();
        }
    }
}

void func_82C00CB4(s32 arg0) {
    UNUSED s32 pad;
    s16 sp28 = arg0 * 9;
    s16 sp24 = ((0x38 - sp28) / 2) + 0x82;

    if (arg0 >= 2) {
        DrawPanel(0x87, sp24, 0x172, sp28, 0x6109);
        if (arg0 == 8) {
            Text_ResetState();
            Text_SetFont(0x10, 0);
            Text_SetEnvColor(0xFF, 0xFF, 0x64, 0xFF);
            Text_Print(0x9B, sp24 + 0x18, GetMessageString(NULL, 0, gPrefMessageBank, 0xD));
            Text_SetupDL();
        }
    }
}

void func_82C00D98(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    Stage_BeginDisplayList();
    func_82C00020();
    func_82C00658(arg0, arg1 == 0);

    if (arg2 < 2) {
        func_82C00AA4(arg2, arg3, arg1);
    } else {
        func_82C00CB4(arg1);
    }

    Stage_Advance();
}

s32 func_82C00E10(s32 arg0) {
    s16 i;
    s32 temp_s2;
    s32 var_s2 = 1;
    s16 var_s1 = 1;

    if (arg0 == 0) {
        for (i = 1; i < 8; i++) {
            Game_UpdateInputs();
            func_82C00D98(8, i, arg0, 1);
        }
    }

    while (var_s2 != 0) {
        Game_UpdateInputs();
        if (BTN_IS_PRESSED(gPlayer1Controller, BTN_DUP | BTN_DDOWN)) {
            PlaySoundEffect(1);
            var_s1 ^= 1;
        } else if (BTN_IS_PRESSED(gPlayer1Controller, BTN_A)) {
            var_s2 = 0;
        } else if (BTN_IS_PRESSED(gPlayer1Controller, BTN_B)) {
            var_s1 = 1;
            var_s2 = 0;
        }
        func_82C00D98(8, 8, arg0, var_s1);
    }

    temp_s2 = var_s1 == 0;
    if (temp_s2 != 0) {
        if (arg0 == 0) {
            PlaySoundEffect(2);
        } else {
            PlaySoundEffect(0x1F);
        }
    } else {
        PlaySoundEffect(3);
    }

    if ((arg0 == 1) || (var_s1 == 1)) {
        for (i = 7; i > 0; i--) {
            Game_UpdateInputs();
            func_82C00D98(8, i, arg0, var_s1);
        }
    }
    return temp_s2;
}

void func_82C00F88(void) {
    s16 i;

    for (i = 1; i < 8; i++) {
        Game_UpdateInputs();
        func_82C00D98(8, i, 2, 0);
    }

    do {
        Game_UpdateInputs();
        func_82C00D98(8, 8, 2, 0);
    } while (!BTN_IS_PRESSED(gPlayer1Controller, BTN_A));

    PlaySoundEffect(2);

    for (i = 7; i > 0; i--) {
        Game_UpdateInputs();
        func_82C00D98(8, i, 2, 0);
    }
}

void func_82C01054(void) {
    s32 i;
    s32 j;

    for (i = 0; i < 9; i++) {
        func_80028C48(i);

        for (j = 0; j < 12; j++) {
            GbsClearAndCommitBlock(0x10, j);
        }
    }

    for (j = 0; j < 12; j++) {
        GbsClearAndCommitBlock(0x11, j);
    }

    for (j = 0; j < 4; j++) {
        GbsClearAndCommitBlock(0x12, j);
    }

    GbsClearAndCommitBlock(0x13, 0);
    GbsClearAndCommitBlock(0x14, 0);
    GbsClearAndCommitBlock(0x15, 0);
    GbsClearAndCommitBlock(0x16, 0);
    GbsClearAndCommitBlock(0x17, 0);
    func_800286D8();
    gBattleContext.unk_11F2 = 0;
    func_8004AF24(0);
    SetAudioActiveFlag(1);
    gPrefToggleFlags = 0;
}

void func_82C0115C(u16 arg0) {
    u16 sp26;
    u16 sp24;

    func_80028070(&sp26);
    sp24 = arg0 ^ sp26;

    if (sp24 != 0) {
        if (sp24 & 1) {
            if (arg0 & 1) {
                func_8004AF24(1);
            } else {
                func_8004AF24(0);
            }
        }

        if (sp24 & 2) {
            if (arg0 & 2) {
                SetAudioActiveFlag(0);
            } else {
                SetAudioActiveFlag(1);
            }
        }

        func_80028084(&arg0);
        GbsCommitBankBlock(0x14, 0);
    }
}

s16 func_82C0120C(void) {
    s16 sp1E = 0;

    switch (gPrefSelectedOption) {
        case 0:
            PlaySoundEffect(2);
            gPrefToggleFlags ^= 1;
            break;

        case 1:
            PlaySoundEffect(2);
            gPrefToggleFlags ^= 2;
            break;

        case 2:
            PlaySoundEffect(2);
            if ((func_82C00E10(0) != 0) && (func_82C00E10(1) != 0)) {
                func_82C01054();
                func_82C00F88();
            }
            break;

        case 3:
            PlaySoundEffect(0x1D);
            func_82C0115C(gPrefToggleFlags);
            sp1E = 1;
            break;
    }

    return sp1E;
}

void Pref_MainLoop(void) {
    s16 i;
    s16 var_s1 = 0;

    func_80006C6C(8);
    while (func_80007604() != 0) {
        Game_UpdateInputs();
        func_82C00D98(0, 0, 0, 0);
    }

    for (i = 1; i < 8; i++) {
        Game_UpdateInputs();
        func_82C00D98(i, 0, 0, 0);
    }

    while (var_s1 == 0) {
        Game_UpdateInputs();
        if (BTN_IS_PRESSED(gPlayer1Controller, BTN_DUP)) {
            gPrefSelectedOption = (gPrefSelectedOption + 3) % 4;
            PlaySoundEffect(1);
        } else if (BTN_IS_PRESSED(gPlayer1Controller, BTN_DDOWN)) {
            gPrefSelectedOption = (gPrefSelectedOption + 1) % 4;
            PlaySoundEffect(1);
        } else if (BTN_IS_PRESSED(gPlayer1Controller, BTN_A)) {
            var_s1 = func_82C0120C();
        } else if (BTN_IS_PRESSED(gPlayer1Controller, BTN_B)) {
            var_s1 = 2;
            PlaySoundEffect(3);
        }
        func_82C00D98(8, 0, 0, 0);
    }

    for (i = 7; i > 0; i--) {
        Game_UpdateInputs();
        func_82C00D98(i, 0, 0, 0);
    }

    func_80007990(0xFFFF);
    func_80006CB4(8);

    while (func_80007604() != 1) {
        Game_UpdateInputs();
        func_82C00D98(0, 0, 0, 0);
    }
}

s32 Pref_Entry(UNUSED s32 arg0, UNUSED s32 arg1) {
    Stage* sp24;

    main_pool_push_state('PREF');

    Gfx_InitBuffers(0x10000, 0);
    sp24 = Stage_Create(1, 0, 2, 0, 2, 1);
    Text_Init(0x1C, 0);

    ASSET_LOAD(D_1000000, common_menu1_ui, 0);
    ASSET_LOAD(D_3000000, menu_select_ui, 0);
    ASSET_LOAD(D_2000000, common_menu2_ui, 0);

    MessageBank_Init();
    gPrefMessageBank = GetMessageBank(0x15);
    func_80028BE4();
    func_80028070(&gPrefToggleFlags);
    gPrefSelectedOption = 0;
    Stage_Set(sp24);
    Pref_MainLoop();
    Stage_Destroy();
    func_800286D8();
    Gfx_FreeBuffers();

    main_pool_pop_state('PREF');

    return 4;
}
