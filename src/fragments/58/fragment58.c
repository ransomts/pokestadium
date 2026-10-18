#include "fragment58.h"
#include "src/1CF30.h"
#include "src/20330.h"
#include "src/20470.h"
#include "src/232C0.h"
#include "src/29BA0.h"
#include "src/2C1C0.h"
#include "src/2E110.h"
#include "src/3FB0.h"
#include "src/49790.h"
#include "src/DDC0.h"
#include "src/F420.h"
#include "src/controller.h"
#include "src/memory.h"
#include "src/stage_loader.h"

typedef struct MenuSelection {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
} MenuSelection; // size = 0x4

typedef struct RuleOptionWindow {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ s16 unk_08;
} RuleOptionWindow; // size >= 0xA

typedef struct MenuEntry {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ u8* unk_08;
    /* 0x0C */ u8* unk_0C;
} MenuEntry; // size = 0x10

static char** gRuleMessageBank;
static char** gOptionMessageBank;
static BinArchive* D_84002D08;
static u8* gMenuBackgroundAtlas;
static s32 pad_D_84002D10;
static s16 D_84002D14;
static s16 D_84002D16;
static MenuSelection gMenuSelection;
static s32 pad_D_84002D1C;
static s16 gSelectedRuleOption;
static RuleOptionWindow gRuleOptionWindow;

static s16 gWindowAnimTimer = 2;
static s16 gSelectedRuleValue = 0;
static MenuEntry gMenuEntries[11] = {
    {
        1,
        0,
        48,
        6,
        0x03008FD0,
        NULL,
    },
    {
        3,
        0,
        48,
        36,
        0x03008FD0,
        0x03009720,
    },
    {
        5,
        0,
        48,
        66,
        0x03008FD0,
        0x03009E70,
    },
    {
        9,
        0,
        48,
        96,
        0x03008FD0,
        0x0300A5C0,
    },
    {
        2,
        15,
        280,
        6,
        0x03009720,
        NULL,
    },
    {
        4,
        15,
        280,
        36,
        0x03009E70,
        NULL,
    },
    {
        8,
        15,
        280,
        66,
        0x0300A5C0,
        NULL,
    },
    {
        0,
        15,
        280,
        96,
        0x03008880,
        NULL,
    },
    {
        6,
        15,
        336,
        6,
        0x03009720,
        0x03009E70,
    },
    {
        10,
        15,
        336,
        36,
        0x03009720,
        0x0300A5C0,
    },
    {
        12,
        15,
        336,
        66,
        0x03009E70,
        0x0300A5C0,
    },
};
static s16 gRuleBattleIds[] = { 0, 3, 4, 5, 6, 0 };

void DrawDialogBorderSmall(s16 arg0, s16 arg1) {
    gSPDisplayList(gDisplayListHead++, gPrefDL_Border);

    Gfx_DrawSpriteRGBA16(arg0, arg1, 0x30, 0x18, D_2006C00, 0x30, 0);
    Gfx_DrawSpriteRGBA16(arg0, arg1 + 0x18, 0x30, 0x18, D_2007500, 0x30, 0);

    gSPDisplayList(gDisplayListHead++, gPrefDL_End);
}

void DrawDialogBorderLarge(s16 arg0, s16 arg1) {
    gSPDisplayList(gDisplayListHead++, gPrefDL_Border);

    Gfx_DrawSpriteRGBA16(arg0, arg1, 0x64, 0x14, D_200B3E0, 0x64, 0);
    Gfx_DrawSpriteRGBA16(arg0, arg1 + 0x14, 0x64, 0x14, D_200C380, 0x64, 0);
    Gfx_DrawSpriteRGBA16(arg0, arg1 + 0x28, 0x64, 0x10, D_200D320, 0x64, 0);

    gSPDisplayList(gDisplayListHead++, gPrefDL_End);
}

void func_84000200(s16 arg0, s16 arg1, s16 arg2, Color_RGBA8* arg3, Color_RGBA8* arg4) {
    gSPDisplayList(gDisplayListHead++, gDL_XluBorder);
    gDPSetEnvColor(gDisplayListHead++, arg3->r, arg3->g, arg3->b, 255);
    gDPSetPrimColor(gDisplayListHead++, 0, 0, arg4->r, arg4->g, arg4->b, 255);

    Gfx_DrawSpriteIA8(arg0, arg1, 0x10, 0x20, D_20003C0, 0x10, 0);
    Gfx_DrawSpriteIA8((arg0 + arg2) - 0x10, arg1, 0x10, 0x20, D_20005C0, 0x10, 0);
    Gfx_DrawTextureRect(arg0 + 0x10, arg1, arg2 - 0x20, 0x20, 0, 0, 0, 0x400, 0);

    gSPDisplayList(gDisplayListHead++, gPrefDL_End);
}

void DrawTitlePanel(void) {
    Color_RGBA8 sp2C;
    Color_RGBA8 sp28;

    GfxColor_SetRGB(&sp2C, 0x64, 0x64, 0xC8);
    GfxColor_SetRGB(&sp28, 0x28, 0x28, 0x8C);
    func_84000200(0x48, 0x28, 0x208, &sp2C, &sp28);
    DrawDialogBorderSmall(0x30, 0x20);
    Text_ResetState();
    Text_SetFont(0x10, 0);
    Text_SetEnvColor(0, 0, 0, 0xFF);
    Text_Print(0x6A, 0x2C, GetMessageString(NULL, 0, gRuleMessageBank, 0));
    Text_SetEnvColor(0xFF, 0xFF, 0x77, 0xFF);
    Text_Print(0x68, 0x2A, GetMessageString(NULL, 0, gRuleMessageBank, 0));
    Text_SetupDL();
}

void DrawSelectionBorder(s16 arg0, s16 arg1, s16 arg2, s16 arg3) {
    static s16 D_84002CA4 = 0;

    s16 sp56 = SINS(D_84002CA4) * 2;
    UNUSED s32 pad[2];

    gSPDisplayList(gDisplayListHead++, gPrefDL_Border);
    gDPSetEnvColor(gDisplayListHead++, 240, 212, 104, 255);

    Gfx_DrawSpriteIA8(arg0 + sp56, arg1 + sp56, 0x10, 0x10, D_2000C80, 0x10, 0);
    Gfx_DrawSpriteIA8(arg0 + sp56, ((arg1 + arg3) - sp56) - 0x10, 0x10, 0x10, D_2000F80, 0x10, 0);
    Gfx_DrawSpriteIA8(((arg0 + arg2) - sp56) - 0x10, arg1 + sp56, 0x10, 0x10, D_2000D80, 0x10, 0);
    Gfx_DrawSpriteIA8(((arg0 + arg2) - sp56) - 0x10, ((arg1 + arg3) - sp56) - 0x10, 0x10, 0x10, D_2000E80, 0x10, 0);

    gSPDisplayList(gDisplayListHead++, gPrefDL_End);

    D_84002CA4 += 0x2000;
}

void DrawWindow(s16 arg0, s16 arg1, s16 arg2, s16 arg3) {
    gSPDisplayList(gDisplayListHead++, gPrefDL_Border);

    Gfx_DrawSpriteIA8(arg0 - 3, arg1 - 3, 8, 8, D_2000340, 8, 0);
    Gfx_DrawSpriteIA8((arg0 + arg2) - 5, arg1 - 3, 8, 8, D_2000380, 8, 0);
    Gfx_DrawTextureRect(arg0 + 4, arg1 - 3, arg2 - 8, 8, 0, 0, 0, 0x400, 0);
    Gfx_DrawSpriteIA8(arg0 - 3, (arg1 + arg3) - 5, 8, 8, D_20002C0, 8, 0);
    Gfx_DrawTextureRect(arg0 - 3, arg1 + 4, 8, arg3 - 8, 0, 0, 0x400, 0, 0);
    Gfx_DrawSpriteIA8((arg0 + arg2) - 5, (arg1 + arg3) - 5, 8, 8, D_2000300, 8, 0);
    Gfx_DrawTextureRect(arg0 + 4, (arg1 + arg3) - 5, arg2 - 8, 8, 0, 0, 0, 0x400, 0);
    Gfx_DrawTextureRect((arg0 + arg2) - 5, arg1 + 4, 8, arg3 - 8, 0, 0, 0x400, 0, 0);

    gSPDisplayList(gDisplayListHead++, gMenuDL_BackgroundFill);

    Gfx_FillRect(arg0 + 4, arg1 + 4, arg2 - 8, arg3 - 8, 0x3C, 0x3C, 0xA0);

    gSPDisplayList(gDisplayListHead++, gPrefDL_End);
}

void DrawCustomWindow(s16 arg0, s16 arg1, s16 arg2, s16 arg3, u8 arg4, u8 arg5, u8 arg6, u8 arg7) {
    s16 temp_a2;
    s16 temp_s0_32;
    s16 var_s2;
    s16 var_s3;

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

s32 IsMenuEntryEnabled(s16 arg0) {
    MenuEntry* ptr = &gMenuEntries[arg0];
    s16 t = ptr->unk_00;
    s32 var_v1 = 0;

    if (arg0 < 4) {
        if (D_84002D16 >= 2) {
            var_v1 = arg0 == gMenuSelection.unk_00;
        } else {
            var_v1 = ptr->unk_00 == (ptr->unk_00 & D_84002D14);
        }
    } else if (arg0 < 11) {
        if (D_84002D16 >= 3) {
            var_v1 = arg0 == (gMenuSelection.unk_02 + 4);
        } else {
            s16 tmp = (~gMenuEntries[gMenuSelection.unk_00].unk_00 & D_84002D14);

            var_v1 = ptr->unk_00 == (ptr->unk_00 & tmp);
        }
    }
    return var_v1;
}

void PrintMenuItemChar(s16 arg0, s16 arg1, s16 arg2) {
    if (IsMenuEntryEnabled(arg2) != 0) {
        Text_SetEnvColor(0xFF, 0xFF, 0xFF, 0xFF);
    } else {
        Text_SetEnvColor(0x64, 0x64, 0x64, 0x82);
    }
    Text_PutChar(arg0, arg1, 0x26);
}

void DrawItemSelectionScreen(void) {
    s32 i;
    s16 temp_s2;
    s16 temp_s3;
    s32 var_t1;
    MenuEntry* ptr;
    s16 tmp1;
    s16 tmp2;

    DrawCustomWindow(0x64, 0x72, 0x1B0, 0x80, 0, 0, 0, 0xFF);
    DrawDialogBorderLarge(0x10A, 0x96);

    gSPDisplayList(gDisplayListHead++, gPrefDL_Border);

    for (i = 0; i < 11; i++) {
        temp_s2 = gMenuEntries[i].unk_04 + 0x64;
        temp_s3 = gMenuEntries[i].unk_06 + 0x72;

        if (IsMenuEntryEnabled(i) != 0) {
            var_t1 = 0xFF;
        } else {
            var_t1 = 0x82;
        }

        gDPSetEnvColor(gDisplayListHead++, var_t1, var_t1, var_t1, var_t1);

        Gfx_DrawSpriteRGBA16(temp_s2, temp_s3, 0x24, 0x1A, gMenuEntries[i].unk_08, 0x24, 0);
        if (gMenuEntries[i].unk_0C != NULL) {
            Gfx_DrawSpriteRGBA16(temp_s2 + 0x30, temp_s3, 0x24, 0x1A, gMenuEntries[i].unk_0C, 0x24, 0);
        }
    }

    gSPDisplayList(gDisplayListHead++, gPrefDL_End);

    Text_ResetState();
    Text_SetFont(0x10, 0);

    for (i = 0; i < 11; i++) {
        if (gMenuEntries[i].unk_0C != NULL) {
            PrintMenuItemChar(gMenuEntries[i].unk_04 + 0x87, gMenuEntries[i].unk_06 + 0x73, i);
        }
    }

    Text_SetFont(0x10, 0);

    if ((D_84002D16 == 1) || (D_84002D16 == 2)) {
        Text_SetEnvColor(0xFF, 0xFF, 0xFF, 0xFF);
    } else {
        Text_SetEnvColor(0x78, 0x78, 0xC8, 0xFF);
    }

    Text_Print(0x64, 0x5A, GetMessageString(NULL, 0, gRuleMessageBank, 1));
    Text_SetupDL();

    if (D_84002D16 == 1) {
        ptr = &gMenuEntries[gMenuSelection.unk_00];
        tmp1 = ptr->unk_04 + 0x64;
        tmp2 = ptr->unk_06 + 0x72;
        DrawSelectionBorder(tmp1 - 4, tmp2 - 2, ((ptr->unk_0C == NULL) ? 0x24 : 0x54) + 8, 0x1E);
    } else if (D_84002D16 == 2) {
        ptr = &gMenuEntries[gMenuSelection.unk_02];
        tmp1 = ptr[4].unk_04 + 0x64;
        tmp2 = ptr[4].unk_06 + 0x72;
        DrawSelectionBorder(tmp1 - 4, tmp2 - 2, ((ptr[4].unk_0C == NULL) ? 0x24 : 0x54) + 8, 0x1E);
    }
}

void HandleItemSelectInput(void) {
    s32 sp24 = gMenuSelection.unk_00;

    if (BTN_IS_PRESSED(gPlayer1Controller, BTN_A)) {
        PlaySoundEffect(2);
        gMenuSelection.unk_02 = 0;
        while (IsMenuEntryEnabled(gMenuSelection.unk_02 + 4) == 0) {
            gMenuSelection.unk_02++;
        }
        D_84002D16 = 2;
    } else if (BTN_IS_PRESSED(gPlayer1Controller, BTN_B)) {
        PlaySoundEffect(3);
        D_84002D16 = 8;
    } else {
        do {
            if (BTN_IS_PRESSED(gPlayer1Controller, BTN_DUP)) {
                gMenuSelection.unk_00 = (gMenuSelection.unk_00 + 3) % 4;
            } else if (BTN_IS_PRESSED(gPlayer1Controller, BTN_DDOWN)) {
                gMenuSelection.unk_00 = (gMenuSelection.unk_00 + 1) % 4;
            }
        } while (IsMenuEntryEnabled(gMenuSelection.unk_00) == 0);

        if (sp24 != gMenuSelection.unk_00) {
            PlaySoundEffect(1);
        }
    }
}

void HandleOpponentSelectInput(void) {
    s32 sp34 = gMenuSelection.unk_02;
    s32 i;
    s32 var_a0;
    s32 var_s1;
    s32 var_s4;

    if (BTN_IS_PRESSED(gPlayer1Controller, BTN_A)) {
        PlaySoundEffect(2);
        if (gMenuSelection.unk_02 == 3) {
            D_84002D16 = 5;
        } else {
            gSelectedRuleOption = 0;
            D_84002D16 = 3;
        }
        return;
    }

    var_s4 = 0;
    if (BTN_IS_PRESSED(gPlayer1Controller, BTN_B)) {
        PlaySoundEffect(3);
        gMenuSelection.unk_02 = -1;
        D_84002D16 = 1;
        return;
    }

    var_a0 = gMenuSelection.unk_02 / 4;
    var_s1 = gMenuSelection.unk_02 % 4;

    if (BTN_IS_PRESSED(gPlayer1Controller, BTN_DLEFT) && (var_a0 == 1)) {
        var_a0 = 0;
        var_s4 = 1;
    } else if (BTN_IS_PRESSED(gPlayer1Controller, BTN_DRIGHT) && (var_a0 == 0)) {
        var_a0 = 1;
        var_s4 = 1;
    } else if (BTN_IS_PRESSED(gPlayer1Controller, BTN_DUP)) {
        var_s1 = (var_s1 + 3) % 4;
        var_s4 = -1;
    } else if (BTN_IS_PRESSED(gPlayer1Controller, BTN_DDOWN)) {
        var_s1 = (var_s1 + 1) % 4;
        var_s4 = 1;
    }

    if (var_s4 != 0) {
        for (i = 0; i < 4; i++) {
            if (IsMenuEntryEnabled(var_a0 * 4 + var_s1 + 4) != 0) {
                break;
            }
            var_s1 = (var_s1 + var_s4 + 4) % 4;
        }

        if (i != 4) {
            gMenuSelection.unk_02 = var_a0 * 4 + var_s1;
        }
    }

    if (sp34 != gMenuSelection.unk_02) {
        PlaySoundEffect(1);
    }
}

void ResetMenuSelections(void) {
    gMenuSelection.unk_00 = -1;
    gMenuSelection.unk_02 = -1;
}

s32 IsAnyMenuOptionSelected(void) {
    s32 var_v1 = 0;

    if ((gMenuSelection.unk_00 != -1) && (gMenuEntries[gMenuSelection.unk_00].unk_0C != 0)) {
        var_v1 = 1;
    }

    if ((gMenuSelection.unk_02 != -1) && (gMenuEntries[gMenuSelection.unk_02 + 4].unk_0C != 0)) {
        var_v1 = 1;
    }
    return var_v1;
}

void PrintMenuText(s16 arg0, s16 arg1, s16 arg2, char* arg3) {
    if ((arg2 != 0) && (IsAnyMenuOptionSelected() != 0)) {
        Text_SetEnvColor(0x3C, 0x3C, 0x3C, 0xFF);
    } else if (arg2 == gSelectedRuleOption) {
        Text_SetEnvColor(0xFF, 0xFF, 0, 0xFF);
    } else {
        Text_SetEnvColor(0xFF, 0xFF, 0xFF, 0xFF);
    }
    Text_Print(arg0, arg1 + (arg2 * 0x18), arg3);
}

void func_84001AD8(void) {
}

void DrawRuleDetailsScreen(void) {
    UNUSED s32 pad;
    char sp2C[128];

    DrawCustomWindow(0x64, 0x10C, 0x1B0, 0x84, 0, 0, 0, 0xFF);
    Text_ResetState();
    Text_SetFont(8, 0);
    PrintMenuText(0x94, 0x114, 0, GetMessageString(NULL, 0, gRuleMessageBank, 2));
    PrintMenuText(0x94, 0x114, 1, GetMessageString(NULL, 0, gRuleMessageBank, 3));
    PrintMenuText(0x94, 0x114, 2, GetMessageString(NULL, 0, gRuleMessageBank, 6));
    PrintMenuText(0x94, 0x114, 3, GetMessageString(NULL, 0, gRuleMessageBank, 7));
    PrintMenuText(0x94, 0x114, 4, GetMessageString(NULL, 0, gRuleMessageBank, 8));
    Text_SetFont(4, 0);

    sprintf(sp2C, "%s1~100", GetMessageString(NULL, 0, gOptionMessageBank, 0x15));
    PrintMenuText(0x1AE, 0x118, 0, sp2C);
    sprintf(sp2C, "%s50~55", GetMessageString(NULL, 0, gOptionMessageBank, 0x15));
    PrintMenuText(0x1AE, 0x118, 1, sp2C);
    sprintf(sp2C, "%s25~30", GetMessageString(NULL, 0, gOptionMessageBank, 0x15));
    PrintMenuText(0x1AE, 0x118, 2, sp2C);
    sprintf(sp2C, "%s15~20", GetMessageString(NULL, 0, gOptionMessageBank, 0x15));
    PrintMenuText(0x1AE, 0x118, 3, sp2C);
    sprintf(sp2C, "%s1~100", GetMessageString(NULL, 0, gOptionMessageBank, 0x15));
    PrintMenuText(0x1AE, 0x118, 4, sp2C);

    Text_SetFont(0x10, 0);

    if (D_84002D16 == 3) {
        Text_SetEnvColor(0xFF, 0xFF, 0xFF, 0xFF);
    } else {
        Text_SetEnvColor(0x78, 0x78, 0xC8, 0xFF);
    }

    Text_Print(0x64, 0xF4, GetMessageString(NULL, 0, gRuleMessageBank, 9));
    Text_SetupDL();

    if (D_84002D16 == 3) {
        AnimateIconOffset(0x6C, (gSelectedRuleOption * 0x18) + 0x114);
    }
}

void HandleRuleOptionInput(void) {
    if (BTN_IS_PRESSED(gPlayer1Controller, BTN_A)) {
        PlaySoundEffect(0x26);
        D_84002D16 = 7;
    } else if (BTN_IS_PRESSED(gPlayer1Controller, BTN_B)) {
        PlaySoundEffect(3);
        gSelectedRuleOption = -1;
        D_84002D16 = 2;
    } else if (IsAnyMenuOptionSelected() == 0) {
        if (BTN_IS_PRESSED(gPlayer1Controller, BTN_DUP)) {
            PlaySoundEffect(1);
            gSelectedRuleOption = (gSelectedRuleOption + 4) % 5;
        } else if (BTN_IS_PRESSED(gPlayer1Controller, BTN_DDOWN)) {
            PlaySoundEffect(1);
            gSelectedRuleOption = (gSelectedRuleOption + 1) % 5;
        }
    }
}

void ResetRuleOption(void) {
    gSelectedRuleOption = -1;
}

void PrintRuleOptionText(s16 arg0, char* arg1) {
    if (arg0 == gRuleOptionWindow.unk_08) {
        Text_SetEnvColor(0xFF, 0xFF, 0, 0xFF);
    } else {
        Text_SetEnvColor(0xFF, 0xFF, 0xFF, 0xFF);
    }
    Text_Print(gRuleOptionWindow.unk_00 + 0x34, gRuleOptionWindow.unk_02 + (arg0 * 0x1C) + 0x2B, arg1);
}

void DrawRuleOptionPanel(void) {
    if (gRuleOptionWindow.unk_04 > 0) {
        s16 tmp = gRuleOptionWindow.unk_04 * 0x11;

        DrawPanel(gRuleOptionWindow.unk_00, gRuleOptionWindow.unk_02 + (s16)((0x88 - tmp) / 2), 0x98, tmp, 0x2121);
        if (gRuleOptionWindow.unk_04 == 8) {
            gSPDisplayList(gDisplayListHead++, gPrefDL_Border);

            Gfx_DrawSpriteRGBA16(gRuleOptionWindow.unk_00 + 0xC, gRuleOptionWindow.unk_02 + 0xA, 0x24, 0x1A, D_3008880, 0x24, 0);

            gSPDisplayList(gDisplayListHead++, gPrefDL_End);

            AnimateIconOffset(gRuleOptionWindow.unk_00 + 0xC, gRuleOptionWindow.unk_02 + (gRuleOptionWindow.unk_08 * 0x1C) + 0x2B);
            Text_ResetState();
            Text_SetFont(0x10, 0);
            Text_Print(gRuleOptionWindow.unk_00 + 0x30, gRuleOptionWindow.unk_02 + 0xB, GetMessageString(NULL, 0, gRuleMessageBank, 0xA));
            PrintRuleOptionText(0, GetMessageString(NULL, 0, gRuleMessageBank, 0xB));
            PrintRuleOptionText(1, GetMessageString(NULL, 0, gRuleMessageBank, 0xC));
            PrintRuleOptionText(2, GetMessageString(NULL, 0, gRuleMessageBank, 0xD));
            Text_SetupDL();
        }
    }
}

void InitRuleOptionState(void) {
    gRuleOptionWindow.unk_00 = 0x190;
    gRuleOptionWindow.unk_02 = 0x64;
    gRuleOptionWindow.unk_04 = 0;
    gRuleOptionWindow.unk_08 = 1;
}

void RuleOption_Next(void) {
    gWindowAnimTimer = 2;
    gRuleOptionWindow.unk_04++;
    if (gRuleOptionWindow.unk_04 == 8) {
        D_84002D16 = 4;
    }
}

void RuleOption_Prev(void) {
    gWindowAnimTimer = 2;
    gRuleOptionWindow.unk_04--;
    if (gRuleOptionWindow.unk_04 == 0) {
        D_84002D16 = gRuleOptionWindow.unk_06;
    }
}

void HandleRuleOptionSelection(void) {
    if (BTN_IS_PRESSED(gPlayer1Controller, BTN_A)) {
        gSelectedRuleValue = gRuleOptionWindow.unk_08;
        gRuleOptionWindow.unk_06 = 3;
        gSelectedRuleOption = 0;
        D_84002D16 = 6;
        PlaySoundEffect(2);
    } else if (BTN_IS_PRESSED(gPlayer1Controller, BTN_B)) {
        gRuleOptionWindow.unk_06 = 2;
        D_84002D16 = 6;
        PlaySoundEffect(3);
    } else if (BTN_IS_PRESSED(gPlayer1Controller, BTN_DUP)) {
        PlaySoundEffect(1);
        gRuleOptionWindow.unk_08 = (gRuleOptionWindow.unk_08 + 2) % 3;
    } else if (BTN_IS_PRESSED(gPlayer1Controller, BTN_DDOWN)) {
        PlaySoundEffect(1);
        gRuleOptionWindow.unk_08 = (gRuleOptionWindow.unk_08 + 1) % 3;
    }
}

void Menu_UpdateInput(void) {
    Cont_StartReadInputs();
    Cont_ReadInputs();
    MenuInput_Init();
}

void func_840023B8(void) {
    Stage_BeginDisplayList();
    if (gWindowAnimTimer > 0) {
        DrawWindow(0x4C, 0x54, 0x1E8, 0x150);
        gWindowAnimTimer -= 1;
    }
    DrawItemSelectionScreen();
    DrawRuleDetailsScreen();
    DrawRuleOptionPanel();
    Stage_Advance();
}

void Menu_FadeIn(void) {
    s32 i;

    if (Stage_GetFadeState() == 1) {
        Stage_FadeIn(8);

        for (i = 0; i < 10; i++) {
            Game_UpdateInputs();
            Stage_BeginDisplayList();
            Gfx_DrawTextureAtlas(gMenuBackgroundAtlas);
            Stage_Advance();
        }
    }
}

void Menu_FadeOut(void) {
    Music_StopTrack(0x10);
    Stage_SetFillColor(0xFFFF);
    Stage_FadeOut(8);

    while (Stage_GetFadeState() != 1) {
        Game_UpdateInputs();
        Stage_BeginDisplayList();
        Gfx_DrawTextureAtlas(gMenuBackgroundAtlas);
        Stage_Advance();
    }

    Stage_AdvanceN(2);
}

void Menu_AnimateWindowIn(void) {
    s32 i;
    s16 tmp;

    PlaySoundEffect(4);

    for (i = 0x10; i < 0x170; i += 0x20) {
        Menu_UpdateInput();
        Stage_BeginDisplayList();
        Gfx_DrawTextureAtlas(gMenuBackgroundAtlas);
        DrawTitlePanel();
        tmp = i;
        tmp = (0x150 - tmp) / 2;
        DrawWindow(0x4C, tmp + 0x54, 0x1E8, i);
        Stage_Advance();
    }
}

void Menu_AnimateWindowOut(void) {
    s32 i;

    for (i = 9; i >= 0; i--) {
        Menu_UpdateInput();
        Stage_BeginDisplayList();
        Gfx_DrawTextureAtlas(gMenuBackgroundAtlas);
        DrawTitlePanel();
        DrawWindow(0x4C, (s16)((0x16C - (s16)(0xE + i * 0x23)) / 2) + 0x54, 0x1E8, 0xE + i * 0x23);
        Stage_Advance();
    }

    for (i = 0; i < 2; i++) {
        Stage_BeginDisplayList();
        Gfx_DrawTextureAtlas(gMenuBackgroundAtlas);
        Stage_Advance();
    }
}

void Menu_SetupBattle(void) {
    char sp44[12];
    unk_D_800AE540_0004* temp_v0;
    s32 i;

    Battle_Init(0, gRuleBattleIds[gSelectedRuleOption], 0);

    for (i = 0; i < 4; i++) {
        if (gMenuEntries[gMenuSelection.unk_00].unk_00 & (1 << i)) {
            sprintf(sp44, "%dP", i + 1);
            Battle_RegisterPlayerEntry(0, RegisterPlayer(i, 0, sp44, GetNameSlot(1)));
        }
    }

    if (gMenuSelection.unk_02 == 3) {
        gBattleContext.unk_11EC = gSelectedRuleValue;
        temp_v0 = RegisterPlayer(-1, 0, "COM", GetNameSlot(3));
        Battle_RegisterPlayerEntry(1, temp_v0);
        if (gMenuSelection.unk_00 == 3) {
            temp_v0->unk_001 = 2;
        } else {
            temp_v0->unk_001 = 3;
        }
    } else {
        for (i = 0; i < 4; i++) {
            if (gMenuEntries[gMenuSelection.unk_02 + 4].unk_00 & (1 << i)) {
                sprintf(sp44, "%dP", i + 1);
                Battle_RegisterPlayerEntry(1, RegisterPlayer(i, 0, sp44, GetNameSlot(1)));
            }
        }
    }

    if (gBattleContext.unk_1194[0].unk_01 == 2) {
        gBattleContext.unk_1194[0].unk_08[0]->unk_214->unk_003 = 0x35;
        gBattleContext.unk_1194[0].unk_08[1]->unk_214->unk_003 = 0x35;
    }

    if (gBattleContext.unk_1194[1].unk_01 == 2) {
        gBattleContext.unk_1194[1].unk_08[0]->unk_214->unk_003 = 0x35;
        gBattleContext.unk_1194[1].unk_08[1]->unk_214->unk_003 = 0x35;
    }
}

s32 func_84002914(void) {
    D_84002D16 = 0;
    Music_ChangeTrack(0x2D);
    ResetMenuSelections();
    ResetRuleOption();
    InitRuleOptionState();
    Menu_FadeIn();
    Menu_AnimateWindowIn();
    D_84002D16 = 1;
    gMenuSelection.unk_00 = 0;

    while ((D_84002D16 != 7) && (D_84002D16 != 8)) {
        Menu_UpdateInput();
        switch (D_84002D16) {
            case 1:
                HandleItemSelectInput();
                break;
            case 2:
                HandleOpponentSelectInput();
                break;
            case 3:
                HandleRuleOptionInput();
                break;
            case 4:
                HandleRuleOptionSelection();
                break;
            case 5:
                RuleOption_Next();
                break;
            case 6:
                RuleOption_Prev();
                break;
        }
        func_840023B8();
    }

    if (D_84002D16 == 8) {
        Menu_AnimateWindowOut();
        Menu_FadeOut();
        return 0;
    }

    Menu_SetupBattle();
    Menu_AnimateWindowOut();
    return 1;
}

s32 RuleMenu_Main(s32 arg0, s32 arg1) {
    s32 sp1C;

    main_pool_push_state('RULE');

    Text_Init(0x1C, 0);
    ASSET_LOAD(D_1000000, common_menu1_ui, 0);
    ASSET_LOAD(D_2000000, common_menu2_ui, 0);
    ASSET_LOAD(D_3000000, order_select_ui, 0);
    MessageBank_Init();
    gRuleMessageBank = GetMessageBank(0xF);
    gOptionMessageBank = GetMessageBank(6);
    D_84002D08 = ASSET_LOAD2(backgrounds, 1, 1);
    gMenuBackgroundAtlas = BinArchive_GetFile(D_84002D08, 6);
    D_84002D14 = Cont_GetControllerBits();
    Menu_SetupDisplayList();
    sp1C = func_84002914();
    Stage_Terminate();

    main_pool_pop_state('RULE');
    return sp1C;
}
