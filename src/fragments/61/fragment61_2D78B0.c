#include "fragment61.h"
#include "src/19840.h"
#include "src/1AB70.h"
#include "src/1CF30.h"
#include "src/20330.h"
#include "src/20470.h"
#include "src/225A0.h"
#include "src/22630.h"
#include "src/232C0.h"
#include "src/26820.h"
#include "src/29BA0.h"
#include "src/2C1C0.h"
#include "src/2E110.h"
#include "src/3FB0.h"
#include "src/49790.h"
#include "src/DDC0.h"
#include "src/F420.h"
#include "src/fragments/61/fragment61.h"
#include "src/hal_libc.h"
#include "src/memory.h"
#include "src/stage_loader.h"

BinArchive* gBattleSelectionBackgroundArchive;
void* gPartyScreenBackground;
unk_D_842168A0_0013C* gBattleSelectionControllerInfo;
char** D_84211B3C;
char** D_84211B40;
char** gMessageBank_26;
char** D_84211B48;
char** gMessageBank_06;
unk_D_84211B50 gPartyInfo;
unk_D_842168A0 gControllerInfo;
unk_D_84229EB0 gPokemonData;
unk_D_8423D3A8 gMoveScreenInfo;
unk_D_8423D3D8 gBattleSelectionSlots[4];
s16 gMenuSelectionIndex;

s16 gFrameTimer = 2;
s16 gSubsystemEnableMask = 0x20;
s16 gPartyScreenIconAnimTimer = 0;
u8 gStadiumModeTextureIndices[] = {
    0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0F,
};

s32 CheckPIIdleAndReturnArg(s32 arg0) {
    u32 temp_a0 = osSetIntMask(1);

    if (!(IO_READ(PI_STATUS_REG) & (PI_STATUS_DMA_BUSY | PI_STATUS_IO_BUSY)) &&
        (((D_B0000800 & 0xFFFF) & 0xFFFF) != 1)) {
        arg0 = -0x80;
    }
    osSetIntMask(temp_a0);
    return arg0;
}

char* GetMessageBank24String(s32 arg0) {
    return GetMessageString(NULL, 0, D_84211B3C, arg0 - 1);
}

char* GetMessageBank25String(s32 arg0) {
    return GetMessageString(NULL, 0, D_84211B40, arg0 - 1);
}

char* GetStadiumModeString(s32 arg0) {
    return GetMessageString(NULL, 0, gMessageBank_26, RemapStadiumModeIndex(arg0));
}

char* GetMessageBank1AString(s32 arg0) {
    return GetMessageString(NULL, 0, D_84211B48, arg0);
}

char* GetMessageBank06String(s32 arg0) {
    return GetMessageString(NULL, 0, gMessageBank_06, arg0);
}

char* GetMessageBank1AStringCustomBuf(char* arg0, s32 arg1, s32 arg2) {
    return GetMessageString(arg0, arg1, D_84211B48, arg2);
}

void DrawBorderedBox(s16 arg0, s16 arg1, s16 arg2, s16 arg3) {
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

void DrawColoredBox(s16 arg0, s16 arg1, s16 arg2, s16 arg3, u8 arg4, u8 arg5, u8 arg6, u8 arg7) {
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

void DrawAnimatedGoldBorder(s16 arg0, s16 arg1, s16 arg2, s16 arg3) {
    static s16 D_84210D58 = 0;

    s16 sp56 = SINS(D_84210D58) * 2;
    UNUSED s32 pad[2];

    gSPDisplayList(gDisplayListHead++, gPrefDL_Border);
    gDPSetEnvColor(gDisplayListHead++, 240, 212, 104, 255);

    Gfx_DrawSpriteIA8(arg0 + sp56, arg1 + sp56, 0x10, 0x10, D_2000C80, 0x10, 0);
    Gfx_DrawSpriteIA8(arg0 + sp56, ((arg1 + arg3) - sp56) - 0x10, 0x10, 0x10, D_2000F80, 0x10, 0);
    Gfx_DrawSpriteIA8(((arg0 + arg2) - sp56) - 0x10, arg1 + sp56, 0x10, 0x10, D_2000D80, 0x10, 0);
    Gfx_DrawSpriteIA8(((arg0 + arg2) - sp56) - 0x10, ((arg1 + arg3) - sp56) - 0x10, 0x10, 0x10, D_2000E80, 0x10, 0);

    gSPDisplayList(gDisplayListHead++, gPrefDL_End);

    D_84210D58 += 0x2000;
}

void DrawTiledBorder(s16 arg0, s16 arg1, s16 arg2, s16 arg3, u8 arg4, u8 arg5, u8 arg6, u8 arg7) {
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

void DrawSmallTiledBorder(s16 arg0, s16 arg1, s16 arg2, s16 arg3, u8 arg4, u8 arg5, u8 arg6, u8 arg7) {
    s16 temp_a2;
    s16 temp_s0_32;
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
    temp_a2 = arg2 - (var_s3 * 2);
    temp_s0_32 = arg3 - (var_s2 * 2);

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

void DrawTopPanel(s16 arg0, s16 arg1) {
    gSPDisplayList(gDisplayListHead++, gPrefDL_Border);

    Gfx_DrawSpriteRGBA16(arg0, arg1, 0x30, 0x18, D_2006C00, 0x30, 0);
    Gfx_DrawSpriteRGBA16(arg0, arg1 + 0x18, 0x30, 0x18, D_2007500, 0x30, 0);

    gSPDisplayList(gDisplayListHead++, gPrefDL_End);
}

void DrawAlternateTopPanel(s16 arg0, s16 arg1) {
    gSPDisplayList(gDisplayListHead++, gPrefDL_Border);

    Gfx_DrawSpriteRGBA16(arg0, arg1, 0x30, 0x18, &D_2028AE0, 0x30, 0);
    Gfx_DrawSpriteRGBA16(arg0, arg1 + 0x18, 0x30, 0x18, &D_20293E0, 0x30, 0);

    gSPDisplayList(gDisplayListHead++, gPrefDL_End);
}

void DrawIconPanel(s16 arg0, s16 arg1, s16 arg2) {
    static u8* D_84210D5C[] = { D_200DFA0, D_200F3E0, D_2010820, D_2011C60, D_20130A0 };

    gSPDisplayList(gDisplayListHead++, gPrefDL_Border);

    Gfx_DrawSpriteRGBA16(arg0, arg1, 0x48, 0x12, D_84210D5C[arg2], 0x48, 0);
    Gfx_DrawSpriteRGBA16(arg0, arg1 + 0x12, 0x48, 0x12, D_84210D5C[arg2] + 0xA20, 0x48, 0);

    gSPDisplayList(gDisplayListHead++, gPrefDL_End);
}

void func_84201BC4(s16 arg0, s16 arg1, s16 arg2, Color_RGBA8* arg3, Color_RGBA8* arg4) {
    gSPDisplayList(gDisplayListHead++, gDL_XluBorder);
    gDPSetEnvColor(gDisplayListHead++, arg3->r, arg3->g, arg3->b, 255);
    gDPSetPrimColor(gDisplayListHead++, 0, 0, arg4->r, arg4->g, arg4->b, 255);

    Gfx_DrawSpriteIA8(arg0, arg1, 0x10, 0x20, D_20003C0, 0x10, 0);
    Gfx_DrawSpriteIA8((arg0 + arg2) - 0x10, arg1, 0x10, 0x20, D_20005C0, 0x10, 0);
    Gfx_DrawTextureRect(arg0 + 0x10, arg1, arg2 - 0x20, 0x20, 0, 0, 0, 0x400, 0);

    gSPDisplayList(gDisplayListHead++, gPrefDL_End);
}

void SetupBattleSelectionUI(void) {
    static s32 D_84210D70[] = {
        0x3B, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3D, 0x3E,
    };

    Color_RGBA8 sp2C;
    Color_RGBA8 sp28;

    GfxColor_SetRGB(&sp2C, 0x64, 0x64, 0xC8);
    GfxColor_SetRGB(&sp28, 0x28, 0x28, 0x8C);
    func_84201BC4(0x48, 0x28, 0x208, &sp2C, &sp28);
    DrawTopPanel(0x30, 0x20);
    Text_ResetState();
    Text_SetFont(0x10, 0);
    Text_SetEnvColor(0, 0, 0, 0xFF);
    Text_Print(0x6A, 0x2C, GetMessageBank1AString(D_84210D70[gBattleContext.unk_0000]));
    Text_SetEnvColor(0xFF, 0xFF, 0x77, 0xFF);
    Text_Print(0x68, 0x2A, GetMessageBank1AString(D_84210D70[gBattleContext.unk_0000]));
    Text_SetupDL();
}

void PrintMenuOption(s16 arg0, s16 arg1, s16 arg2, s32 arg3) {
    if (arg2 == gMenuSelectionIndex) {
        Text_SetEnvColor(0xFF, 0xFF, 0, 0xFF);
    } else {
        Text_SetEnvColor(0xFF, 0xFF, 0xFF, 0xFF);
    }
    Text_Print(arg0 + 0x36, arg1 + (arg2 * 0x1E) + 0x2C, arg3);
}

void DrawOptionsScreen(s16 arg0, s16 arg1, s16 arg2) {
    UNUSED s32 pad[2];
    char* sp30;
    s16 temp_a3;
    s16 temp_v0;

    Stage_BeginDisplayList();
    Gfx_DrawTextureAtlas(gPartyScreenBackground);
    SetupBattleSelectionUI();
    if (arg2 > 0) {
        temp_a3 = (((arg2 * 0x9A) - 0x9A) / 8) + 0x10;
        DrawSimplePanel(0x6D, (s16)(((0xAA - temp_a3) / 2) + 0x81), 0x1A6, temp_a3);
        temp_v0 = (((arg2 * 0x5C) - 0x5C) / 8) + 0x10;
        if (1) {}
        DrawSmallTiledBorder(0x38, ((0x6C - temp_v0) / 2) + 0x14C, 0x210, (((arg2 * 0x5C) - 0x5C) / 8) + 0x10, 0x1E, 0x1E,
                      0x82, 0x96);
        if (arg2 == 9) {
            DrawColoredBox(0x74, 0x88, 0x198, 0x20, 0x8C, 0x28, 0x8C, 0xFF);
            DrawColoredBox(0x74, 0xA8, 0x198, 0x7C, 0x64, 0x1E, 0x64, 0xFF);
            AnimateIconOffset(0x79, (gMenuSelectionIndex * 0x1E) + 0xAD);
            Text_ResetState();
            Text_SetFont(0x10, 0);
            Text_Print(0x7D, 0x8B, "%s %s", GetMessageBank1AString(gBattleContext.unk_0001 + 0x3F), GetMessageBank1AString(0x48));
            PrintMenuOption(0x6D, 0x81, 0, GetMessageBank1AString(0x49));
            PrintMenuOption(0x6D, 0x81, 1, GetMessageBank1AString(0x4A));
            PrintMenuOption(0x6D, 0x81, 2, GetMessageBank1AString(0x4B));
            PrintMenuOption(0x6D, 0x81, 3, GetMessageBank1AString(0x4C));
            Text_SetFont(8, 0);
            Text_SetEnvColor(0xFF, 0xFF, 0xFF, 0xFF);
            Text_SetLineHeight(0x18);
            Text_Print(0x58, 0x154, GetMessageString(NULL, 0, D_84211B48, 0x4D));
            Text_SetupDL();
        }
    }
    func_8420D4F8(0);
    Stage_Advance();
}

void WaitForMenuConfirm(void) {
    PlaySoundEffect(8);
    func_8420DA28(0x10, gPlayer1Controller);

    while (func_8420DB48(0x10) == -1) {
        func_8420D9B0();
        DrawOptionsScreen(0x8C, 0xBC, 9);
        Game_UpdateInputs();
    }
}

s32 UpdateMenuSelectionInput(void) {
    s32 sp1C = 'exec';

    if (BTN_IS_PRESSED(gPlayer1Controller, BTN_A)) {
        if ((gMenuSelectionIndex == 0) && (func_80028E68() == 0xA)) {
            WaitForMenuConfirm();
        } else {
            if (gMenuSelectionIndex < 3) {
                PlaySoundEffect(0x1C);
            } else {
                PlaySoundEffect(3);
            }
            sp1C = 'btnA';
        }
    } else if (BTN_IS_PRESSED(gPlayer1Controller, BTN_B)) {
        PlaySoundEffect(3);
        gMenuSelectionIndex = 3;
        sp1C = 'btnB';
    } else if (BTN_IS_PRESSED(gPlayer1Controller, BTN_DUP)) {
        PlaySoundEffect(1);
        gMenuSelectionIndex--;
        if (gMenuSelectionIndex < 0) {
            gMenuSelectionIndex = 3;
        }
    } else if (BTN_IS_PRESSED(gPlayer1Controller, BTN_DDOWN)) {
        PlaySoundEffect(1);
        gMenuSelectionIndex++;
        if (gMenuSelectionIndex >= 4) {
            gMenuSelectionIndex = 0;
        }
    }
    return sp1C;
}

s16 RunMenuSelection(void) {
    s16 i;
    s32 temp_s0;

    gMenuSelectionIndex = 0;
    PlaySoundEffect(4);

    for (i = 0; i < 9; i++) {
        Game_UpdateInputs();
        DrawOptionsScreen(0x8C, 0xBC, i);
    }

    do {
        Game_UpdateInputs();
        temp_s0 = UpdateMenuSelectionInput();
        DrawOptionsScreen(0x8C, 0xBC, 9);
    } while (temp_s0 == 'exec');

    for (i = 8; i >= 0; i--) {
        Game_UpdateInputs();
        DrawOptionsScreen(0x8C, 0xBC, i);
    }

    DrawOptionsScreen(0x8C, 0xBC, 0);
    return CheckPIIdleAndReturnArg(gMenuSelectionIndex);
}

void DrawPartyTopPanel(s16 arg0, s16 arg1) {
    Color_RGBA8 sp34;
    Color_RGBA8 sp30;
    s32 var_t0 = 0;

    if ((gBattleContext.unk_0000 == 0) && (arg1 >= 0)) {
        if (gPartyScreenIconAnimTimer == 0) {
            var_t0 = 1;
        } else {
            if ((gPartyScreenIconAnimTimer % 12) >= 5) {
                var_t0 = 1;
            }
            gPartyScreenIconAnimTimer--;
        }
    }

    if (arg0 == 0) {
        GfxColor_SetRGB(&sp34, 0x64, 0x64, 0xC8);
        GfxColor_SetRGB(&sp30, 0x28, 0x28, 0x8C);
        func_84201BC4(0x48, 0x28, 0x208, &sp34, &sp30);
        DrawTopPanel(0x30, 0x20);
        if (var_t0 != 0) {
            DrawIconPanel(0x1AE, 0x26, arg1);
        }
    } else {
        GfxColor_SetRGB(&sp34, 0xB4, 0x5A, 0xA0);
        GfxColor_SetRGB(&sp30, 0x78, 0x28, 0x64);
        func_84201BC4(0x48, 0x28, 0x208, &sp34, &sp30);
        DrawAlternateTopPanel(0x30, 0x20);
    }

    Text_ResetState();
    Text_SetFont(0x10, 0);
    Text_SetEnvColor(0, 0, 0, 0xFF);

    Text_Print(0x6A, 0x2C, GetMessageString(NULL, 0, D_84211B48, arg0 + 0x37));
    Text_SetEnvColor(0xFF, 0xFF, 0x77, 0xFF);
    Text_Print(0x68, 0x2A, GetMessageString(NULL, 0, D_84211B48, arg0 + 0x37));

    if ((arg0 == 0) && (var_t0 != 0)) {
        Text_SetFont(4, 0);
        Text_Print(0x1F9, 0x2F, GetMessageString(NULL, 0, D_84211B48, 0x4E));
    }
    Text_SetupDL();
}

void DrawPartyScreenSubsystems(UNUSED s16 arg0, s16 arg1, s16 arg2) {
    s32 temp_s0 = gFrameTimer > 0;

    Stage_BeginDisplayList();

    if (temp_s0 != 0) {
        gFrameTimer--;
        Gfx_DrawTextureAtlas(gPartyScreenBackground);
        DrawPartyTopPanel(arg1, arg2);
    }

    if (gSubsystemEnableMask & 8) {
        func_84204760(temp_s0);
    }

    if (gSubsystemEnableMask & 1) {
        DrawItemInfoPanel(&gPartyInfo, temp_s0);
    }

    if (gSubsystemEnableMask & 2) {
        func_84209340(&gControllerInfo, temp_s0);
    }

    if (gSubsystemEnableMask & 4) {
        UpdateAndRenderPokemonListScreen(&gPokemonData, temp_s0);
    }

    if (gSubsystemEnableMask & 0x10) {
        DrawPokemonMoveInfo(&gMoveScreenInfo, temp_s0);
    }

    if (gSubsystemEnableMask & 0x20) {
        func_8420D4F8(temp_s0);
    }

    Stage_Advance();
}

s16 RunPartyMenuSelection(s16 arg0, s16 arg1, s16 arg2, s32 arg3) {
    s32 temp_s1 = -1;
    s16 i;

    gPartyScreenIconAnimTimer = 0x27;

    for (i = 0; i < 4; i++) {
        gFrameTimer = 2;
        DrawPartyScreenSubsystems(-1, arg1, arg2);
    }

    Menu_Start(arg0, arg3);

    while (temp_s1 == -1) {
        Game_UpdateInputs();
        func_8420570C();
        func_8420D9B0();
        temp_s1 = Menu_GetSelectedIndex();
        gFrameTimer = 2;
        DrawPartyScreenSubsystems(-1, arg1, arg2);
    }

    DrawPartyScreenSubsystems(-1, arg1, arg2);
    return temp_s1;
}

void UpdatePartyScreenSubsystems(UNUSED s16 arg0, UNUSED s32 arg1) {
    s32 var_a1 = 0;

    if (gSubsystemEnableMask & 1) {
        var_a1 = UpdateItemStateMachine(&gPartyInfo);
    }

    if (gSubsystemEnableMask & 2) {
        var_a1 |= func_8420B0C8(&gControllerInfo);
    }

    if (gSubsystemEnableMask & 4) {
        var_a1 |= func_842106FC(&gPokemonData);
    }

    if (gSubsystemEnableMask & 0x10) {
        var_a1 |= MoveScreen_Update(&gMoveScreenInfo);
    }

    if (gSubsystemEnableMask & 0x20) {
        var_a1 |= func_8420D9B0();
    }

    if (var_a1 != 0) {
        gFrameTimer = 2;
    }
}

void PartyScreenTransition(s16 arg0, s32 arg1, s16 arg2) {
    PlaySoundEffect(4);
    if (arg0 == 4) {
        func_84210A18(&gPokemonData);
    } else {
        func_842079B4(&gPartyInfo, 0);
        func_8420B1D0(&gControllerInfo, 0);
    }
    Game_UpdateInputs();
    UpdatePartyScreenSubsystems(arg0, 0);
    DrawPartyScreenSubsystems(arg0, arg1, arg2);
}

void PartyScreenInputLoop(s16 arg0, s16 arg1, s16 arg2) {
    s32 var_s0 = 1;

    MenuInput_SetController(&gControllers[gControllerInfo.unk_00003]);

    while (var_s0 != 0) {
        Game_UpdateInputs();
        UpdatePartyScreenSubsystems(arg0, MenuInput_ReadDirection() & 0xFFFF);
        DrawPartyScreenSubsystems(arg0, arg1, arg2);

        if (arg0 == 4) {
            var_s0 = func_84210B54(&gPokemonData) == 0;
        } else {
            var_s0 = !func_842081A8(&gPartyInfo);
            var_s0 |= !func_8420B37C(&gControllerInfo);
        }
    }
}

void InitBattleSelectionSlots(void) {
    s16 i;
    unk_D_800AE540_0004* var_v0 = gBattleContext.unk_0004;

    for (i = 0; i < 4; i++) {
        gBattleSelectionSlots[i].unk_00 = 0;
        gBattleSelectionSlots[i].unk_01 = i;
        gBattleSelectionSlots[i].unk_02 = i;
    }

    for (i = 0; i < 4; i++, var_v0++) {
        if (var_v0->unk_000 & 1) {
            if (!(var_v0->unk_000 & 2)) {
                gBattleSelectionSlots[var_v0->unk_001].unk_00 = 1;
                gBattleSelectionSlots[var_v0->unk_001].unk_04 = var_v0;
            } else if (gBattleContext.unk_0000 == 0) {
                gBattleSelectionSlots[var_v0->unk_001].unk_00 = 1;
                gBattleSelectionSlots[var_v0->unk_001].unk_04 = var_v0;
                gBattleSelectionSlots[var_v0->unk_001].unk_01 = 4;
                gBattleSelectionSlots[var_v0->unk_001].unk_02 = 0;
            }
        }
    }
}

void SetupBattleSelectionSlot(unk_D_8423D3D8* arg0, s16 arg1) {
    char sp50[16];
    UNUSED s32 pad;
    u16 var_v1;
    Gen1StringDecodeBuffer sp38;

    if (arg1 == 4) {
        gSubsystemEnableMask |= func_8421089C(&gPokemonData, &gPartyInfo, &gControllerInfo, &gMoveScreenInfo, 0, 0x2C, 0x54, arg0->unk_02);
        return;
    }

    if (arg1 < 4) {
        Controller_ReadInput(arg1, &sp38);
        DecodeGen1String(sp50, sp38.unk_02);
        var_v1 = sp38.unk_00;
    } else {
        HAL_Strcpy(sp50, GetNameSlot(1));
        var_v1 = 0;
    }

    gSubsystemEnableMask |= func_842078C0(&gPartyInfo, &gControllerInfo, &gMoveScreenInfo, NULL, 0, var_v1, sp50, 0x40, 0x54, arg0->unk_02);
    gSubsystemEnableMask |= func_8420AF1C(&gControllerInfo, &gPartyInfo, &gMoveScreenInfo, 0, 0x68, 0xE4, arg0->unk_02, arg1, gBattleSelectionControllerInfo);
}

s32 CommitBattleSelectionSlot(unk_D_8423D3D8* arg0, s16 arg1) {
    s32 temp_s3;
    s32 var_s0 = 0;
    unk_D_84229EB0_00024* sp34;
    s32 i;

    arg0->unk_04->unk_002 = 0;
    if (arg1 == 4) {
        temp_s3 = func_84210B60(&gPokemonData, &sp34);
        if (sp34 != NULL) {
            arg0->unk_04->unk_018 = sp34->unk_4D10;
            if (gBattleContext.unk_0000 != 0) {
                HAL_Strcpy(arg0->unk_04->unk_008, sp34->unk_4D12);
            }
            HAL_Strcpy(arg0->unk_04->unk_214->unk_014, sp34->unk_4D12);

            for (i = 0; i < temp_s3; i++) {
                Battle_AddPartyMon(arg0->unk_04, &sp34->unk_0000[i].unk_004);
            }
            var_s0 = 1;
        }
    } else {
        arg0->unk_04->unk_018 = gPartyInfo.unk_001C;
        if (gBattleContext.unk_0000 != 0) {
            HAL_Strcpy(arg0->unk_04->unk_008, gPartyInfo.unk_001E);
        }
        HAL_Strcpy(arg0->unk_04->unk_214->unk_014, gPartyInfo.unk_001E);

        if (gPartyInfo.unk_0006 > 0) {
            for (i = 0; i < gPartyInfo.unk_0006; i++) {
                Battle_AddPartyMon(arg0->unk_04, &gPartyInfo.unk_0030[i].unk_004);
            }
            var_s0 = 1;
        }
    }
    return var_s0;
}

void FadeOutPartyScreen(s32 arg0) {
    s32 i;

    Stage_SetFillColor(1);
    Music_StopTrack(0x10);
    Stage_FadeOut(8);

    for (i = 0; i < 8; i++) {
        Game_UpdateInputs();
        Stage_BeginDisplayList();
        Gfx_DrawTextureAtlas(gPartyScreenBackground);
        if (arg0 != 0) {
            DrawPartyTopPanel(0, -1);
        }
        Stage_Advance();
    }

    Stage_AdvanceN(2);
}

void FadeInPartyScreen(void) {
    s32 i;

    if (Stage_GetFadeState() == 1) {
        Stage_FadeIn(8);
        for (i = 0; i < 10; i++) {
            Game_UpdateInputs();
            Stage_BeginDisplayList();
            Gfx_DrawTextureAtlas(gPartyScreenBackground);
            DrawPartyTopPanel(0, -1);
            Stage_Advance();
        }
    }
}

void ShowSelectedMonInfo(s16 arg0, s16 arg1) {
    unk_D_800AE540_0004* temp_v1 = gBattleSelectionSlots[arg0].unk_04;

    if (temp_v1->unk_002 != 0) {
        if (arg1 == 4) {
            func_84210C80(&gPokemonData, temp_v1->unk_214->unk_028[0].unk_53);
        } else {
            func_842081B4(&gPartyInfo, &temp_v1->unk_214->unk_028, temp_v1->unk_214->unk_002);
        }
    }
}

s32 RunBattleSelectionMode(void) {
    s16 var_s1 = 0;
    s16 var_s2;

    if ((gBattleContext.unk_0000 == 7) && (gBattleContext.unk_0002 == 9)) {
        FadeOutPartyScreen(0);
        Battle_ClearSelectedMonIndices();
        return 1;
    }

    switch (gBattleContext.unk_0000) {
        case 0:
            Music_ChangeTrack(0x2D);
            break;

        case 7:
            Music_ChangeTrack(0x2B);
            break;

        case 8:
            Music_ChangeTrack(0x30);
            break;

        default:
            Music_ChangeTrack(0x15);
            break;
    }

    InitBattleSelectionSlots();
    FadeInPartyScreen();

    gSubsystemEnableMask |= func_84205C18(0);
    gSubsystemEnableMask |= MoveScreen_Create(&gMoveScreenInfo);

    while (var_s1 >= 0 && var_s1 < 4) {
        if (gBattleSelectionSlots[var_s1].unk_00 != 0) {
            var_s2 = RunPartyMenuSelection(gBattleSelectionSlots[var_s1].unk_02, 0, gBattleSelectionSlots[var_s1].unk_01, 1);
            gBattleSelectionSlots[var_s1].unk_04->unk_002 = 0;

            if (var_s2 < 0) {
                var_s1 -= 1;
                while (var_s1 >= 0) {
                    if (gBattleSelectionSlots[var_s1].unk_00 != 0) {
                        var_s2 = (gBattleSelectionSlots[var_s1].unk_04->unk_01C[0].unk_52 & 0x70) >> 4;
                        break;
                    }
                    var_s1--;
                }
            }

            if (var_s1 >= 0) {
                s32 idx = var_s1;

                main_pool_push_state('pkgb');

                if (var_s2 < 4) {
                    SnapSelect_SetCameraMode(var_s2);
                    func_80024208(var_s2);
                    gBattleContext.unk_11F0 = func_80025328(var_s2);
                } else {
                    gBattleContext.unk_11F0 = 0;
                }

                SetupBattleSelectionSlot(&gBattleSelectionSlots[(unsigned long)idx], var_s2);
                ShowSelectedMonInfo(var_s1, var_s2);
                PartyScreenTransition(var_s2, 0, gBattleSelectionSlots[var_s1].unk_01);
                PartyScreenInputLoop(var_s2, 0, gBattleSelectionSlots[var_s1].unk_01);

                if (CommitBattleSelectionSlot(&gBattleSelectionSlots[(unsigned long)idx], var_s2) != 0) {
                    var_s1++;
                }

                main_pool_pop_state('pkgb');
            }
        } else {
            var_s1++;
        }
    }

    if (var_s1 == -1) {
        return 0;
    }

    FadeOutPartyScreen(1);
    Battle_ClearSelectedMonIndices();
    return 1;
}

s32 RunBattleSelectionModeAlt(void) {
    s16 var_s1 = 0;
    s16 var_s2;

    switch (gBattleContext.unk_0000) {
        case 0:
            Music_ChangeTrack(0x2D);
            break;

        case 7:
            Music_ChangeTrack(0x2B);
            break;

        case 8:
            Music_ChangeTrack(0x30);
            break;

        default:
            Music_ChangeTrack(0x15);
            break;
    }

    InitBattleSelectionSlots();
    FadeInPartyScreen();

    gSubsystemEnableMask |= func_84205C18(0);
    gSubsystemEnableMask |= MoveScreen_Create(&gMoveScreenInfo);

    while ((var_s1 >= 0) && (var_s1 < 4)) {
        if (gBattleSelectionSlots[var_s1].unk_00 != 0) {
            if (gBattleSelectionSlots[var_s1].unk_04->unk_002 == 0) {
                var_s2 = RunPartyMenuSelection(gBattleSelectionSlots[var_s1].unk_02, 0, gBattleSelectionSlots[var_s1].unk_01, 1);
            } else {
                var_s2 = ((gBattleSelectionSlots[var_s1].unk_04->unk_01C[0].unk_52 & 0x70) >> 4);
            }

            if (var_s2 < 0) {
                var_s1--;

                while (var_s1 >= 0) {
                    if (gBattleSelectionSlots[var_s1].unk_00 != 0) {
                        var_s2 = (gBattleSelectionSlots[var_s1].unk_04->unk_01C[0].unk_52 & 0x70) >> 4;
                        break;
                    }
                    var_s1--;
                }
            }

            if (var_s1 >= 0) {
                s32 idx = var_s1;

                main_pool_push_state('pkgb');

                if (var_s2 < 4) {
                    SnapSelect_SetCameraMode(var_s2);
                    func_80024208(var_s2);
                    gBattleContext.unk_11F0 = func_80025328(var_s2);
                } else {
                    gBattleContext.unk_11F0 = 0;
                }
                SetupBattleSelectionSlot(&gBattleSelectionSlots[(unsigned long)idx], var_s2);
                ShowSelectedMonInfo(var_s1, var_s2);
                PartyScreenTransition(var_s2, 0, gBattleSelectionSlots[var_s1].unk_01);
                PartyScreenInputLoop(var_s2, 0, gBattleSelectionSlots[var_s1].unk_01);
                if (CommitBattleSelectionSlot(&gBattleSelectionSlots[(unsigned long)idx], var_s2) != 0) {
                    var_s1++;
                }

                main_pool_pop_state('pkgb');
            }
        } else {
            var_s1++;
        }
    }

    if (var_s1 == -1) {
        return 0;
    }

    FadeOutPartyScreen(1);
    Battle_ClearSelectedMonIndices();
    return 1;
}

void RunRegistrationMode(void) {
    unk_D_84229EB0* ptr;
    char sp74[16];
    s16 temp_v0;
    u16 var_s1;
    Gen1StringDecodeBuffer sp60;

    while (true) {
        temp_v0 = RunPartyMenuSelection(0, 1, 0, 1);
        if (temp_v0 < 0) {
            return;
        }

        main_pool_push_state('regi');

        if (temp_v0 < 4) {
            SnapSelect_SetCameraMode(temp_v0);
            func_80024208(temp_v0);
            Controller_ReadInput(temp_v0, &sp60);
            DecodeGen1String(sp74, sp60.unk_02);
            var_s1 = sp60.unk_00;
        } else {
            HAL_Strcpy(sp74, GetNameSlot(1));
            var_s1 = 0;
        }

        ptr = &gPokemonData;
        gSubsystemEnableMask |= func_8421089C(ptr, &gPartyInfo, &gControllerInfo, &gMoveScreenInfo, 3, 0x2C, 0xBC, 0);
        gSubsystemEnableMask |= func_842078C0(&gPartyInfo, &gControllerInfo, &gMoveScreenInfo, ptr, 1, var_s1, sp74, 0x40, 0x54, 0);
        gSubsystemEnableMask |= func_8420AF1C(&gControllerInfo, &gPartyInfo, &gMoveScreenInfo, 1, 0x68, 0xE4, 0, temp_v0, gBattleSelectionControllerInfo);

        PartyScreenTransition(temp_v0, 1, 0);
        PartyScreenInputLoop(temp_v0, 1, 0);

        main_pool_pop_state('regi');

        if (gPartyInfo.unk_0006 != 0) {
            break;
        }
    }
}

void RunRentalSelectionMode(void) {
    gSubsystemEnableMask |= func_8421089C(&gPokemonData, &gPartyInfo, &gControllerInfo, &gMoveScreenInfo, 1, 0x2C, 0x54, 0);

    func_84210A18(&gPokemonData);
    Game_UpdateInputs();
    UpdatePartyScreenSubsystems(4, 0);
    DrawPartyScreenSubsystems(4, 2, 0);
    MenuInput_SetController(&gControllers[gControllerInfo.unk_00003]);

    do {
        Game_UpdateInputs();
        UpdatePartyScreenSubsystems(4, MenuInput_ReadDirection() & 0xFFFF);
        DrawPartyScreenSubsystems(4, 2, 0);
    } while (func_84210B54(&gPokemonData) == 0);
}

void RunTradeSelectionMode(void) {
    gSubsystemEnableMask |= func_8421089C(&gPokemonData, &gPartyInfo, &gControllerInfo, &gMoveScreenInfo, 2, 0x2C, 0x54, 0);

    func_84210A18(&gPokemonData);
    Game_UpdateInputs();
    UpdatePartyScreenSubsystems(4, 0);
    DrawPartyScreenSubsystems(4, 3, 0);
    MenuInput_SetController(&gControllers[gControllerInfo.unk_00003]);

    do {
        Game_UpdateInputs();
        UpdatePartyScreenSubsystems(4, MenuInput_ReadDirection() & 0xFFFF);
        DrawPartyScreenSubsystems(4, 3, 0);
    } while (func_84210B54(&gPokemonData) == 0);
}

s32 RunMainPartyMenu(void) {
    s16 temp_v0;

    gSubsystemEnableMask |= func_84205C18(1);
    gSubsystemEnableMask |= MoveScreen_Create(&gMoveScreenInfo);

    do {
        temp_v0 = RunMenuSelection();
        switch (temp_v0) {
            case 0:
                RunRegistrationMode();
                break;

            case 1:
                RunRentalSelectionMode();
                break;

            case 2:
                RunTradeSelectionMode();
                break;
        }
    } while (temp_v0 != 3);

    return 1;
}

void LoadBattleSelectionControllerAssets(void) {
    BinArchive* temp_a0;
    s16 var_a1;

    temp_a0 = Asset_Load2(0x898000, NULL, 1, 0);

    switch (gBattleContext.unk_0001) {
        case 0:
            var_a1 = 0x1A;
            break;

        case 1:
            var_a1 = 0x1A;
            break;

        case 2:
            var_a1 = 0x1B;
            break;

        case 3:
            var_a1 = 0x1C;
            break;

        case 4:
            var_a1 = 0x17;
            break;

        case 5:
            var_a1 = 0x18;
            break;

        case 6:
            var_a1 = 0x19;
            break;

        case 7:
            var_a1 = 0x1E;
            break;

        case 8:
            var_a1 = 0x19;
            break;

        default:
            var_a1 = 0;
            break;
    }

    if (var_a1 == 0) {
        gBattleSelectionControllerInfo = NULL;
    } else {
        if (gBattleContext.unk_11F2 != 0) {
            var_a1 += 0x1F;
        }
        gBattleSelectionControllerInfo = BinArchive_GetFile(temp_a0, var_a1);
    }
}

void LoadBattleSelectionBackground(void) {
    unk_func_80027FA0 sp20;

    gBattleSelectionBackgroundArchive = ASSET_LOAD2(backgrounds, 1, 1);
    if (gBattleContext.unk_0000 == 7) {
        if (gBattleContext.unk_0002 >= 8) {
            gPartyScreenBackground = BinArchive_GetFile(gBattleSelectionBackgroundArchive, 0xE);
        } else {
            GbsEnsureBankLoaded(2);
            GBAudio_ResetState(&sp20, gBattleContext.unk_11F2);
            if (sp20.unk_04 < 8) {
                gPartyScreenBackground = BinArchive_GetFile(gBattleSelectionBackgroundArchive, 0xD);
            } else {
                gPartyScreenBackground = BinArchive_GetFile(gBattleSelectionBackgroundArchive, 0x10);
            }
        }
    } else {
        gPartyScreenBackground = BinArchive_GetFile(gBattleSelectionBackgroundArchive, gStadiumModeTextureIndices[gBattleContext.unk_0000]);
    }
}

s32 RunPartyScreenMain(s32 arg0, UNUSED s32 arg1) {
    s32 var_v1;

    main_pool_push_state('PICK');

    Text_Init(0x1C, 0);
    ASSET_LOAD(D_1000000, common_menu1_ui, 0);
    ASSET_LOAD(D_2000000, common_menu2_ui, 0);
    FRAGMENT_LOAD(fragment31);
    AssetManager_LoadArchives();
    MessageBank_Init();

    D_84211B3C = GetMessageBank(0x24);
    D_84211B40 = GetMessageBank(0x25);
    gMessageBank_26 = GetMessageBank(0x26);
    D_84211B48 = GetMessageBank(0x1A);
    gMessageBank_06 = GetMessageBank(6);

    GbsEnsureBankLoaded(gBattleContext.unk_0001 / 4);
    func_80028C48(gBattleContext.unk_0001);
    func_80028EB8();
    LoadBattleSelectionBackground();
    SpriteAssets_Load();
    LoadBattleSelectionControllerAssets();
    func_80007754();

    if (arg0 == 1) {
        var_v1 = RunMainPartyMenu();
    } else if (gBattleContext.unk_11F6 & 0x20) {
        var_v1 = RunBattleSelectionModeAlt();
        gBattleContext.unk_11F6 = gBattleContext.unk_11F6 & 0xFFDF;
    } else {
        gBattleContext.unk_11F5 &= 0xFFFD;
        var_v1 = RunBattleSelectionMode();
    }

    Stage_Terminate();

    main_pool_pop_state('PICK');

    return var_v1;
}
