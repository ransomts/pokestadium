#include "fragment54.h"
#include "src/1CF30.h"
#include "src/20470.h"
#include "src/29BA0.h"
#include "src/2E110.h"
#include "src/3FB0.h"
#include "src/49790.h"
#include "src/DDC0.h"
#include "src/F420.h"
#include "src/memory.h"
#include "src/stage_loader.h"

static char** gFragment54MessageBank;
static BinArchive* gBattleHeaderArchive;
static void* gFragment54TextureAtlas;
static s16 gMenuCursorIndex;

static u8 gBackgroundFileIndexTable[] = {
    0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0F, 0x00, 0x00,
};

static s8 gMessageIdOffsetTable[] = {
    0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x02, 0x03,
};

void DrawPanelBorder(s16 arg0, s16 arg1) {
    gSPDisplayList(gDisplayListHead++, gPrefDL_Border);

    Gfx_DrawSpriteRGBA16(arg0, arg1, 0x30, 0x18, D_2006C00, 0x30, 0);
    Gfx_DrawSpriteRGBA16(arg0, arg1 + 0x18, 0x30, 0x18, D_2007500, 0x30, 0);

    gSPDisplayList(gDisplayListHead++, gPrefDL_End);
}

void RentalHub_DrawHeaderBar(s16 arg0, s16 arg1, s16 arg2, Color_RGBA8* arg3, Color_RGBA8* arg4) {
    gSPDisplayList(gDisplayListHead++, gDL_XluBorder);

    gDPSetEnvColor(gDisplayListHead++, arg3->r, arg3->g, arg3->b, 255);
    gDPSetPrimColor(gDisplayListHead++, 0, 0, arg4->r, arg4->g, arg4->b, 255);

    Gfx_DrawSpriteIA8(arg0, arg1, 0x10, 0x20, D_20003C0, 0x10, 0);
    Gfx_DrawSpriteIA8((arg0 + arg2) - 0x10, arg1, 0x10, 0x20, D_20005C0, 0x10, 0);
    Gfx_DrawTextureRect(arg0 + 0x10, arg1, arg2 - 0x20, 0x20, 0, 0, 0, 0x400, 0);

    gSPDisplayList(gDisplayListHead++, gPrefDL_End);
}

void DrawMenuHeader(void) {
    Color_RGBA8 sp2C;
    Color_RGBA8 sp28;

    GfxColor_SetRGB(&sp2C, 0x64, 0x64, 0xC8);
    GfxColor_SetRGB(&sp28, 0x28, 0x28, 0x8C);
    RentalHub_DrawHeaderBar(0x48, 0x28, 0x208, &sp2C, &sp28);
    DrawPanelBorder(0x30, 0x20);
    Text_ResetState();
    Text_SetFont(0x10, 0);
    Text_SetEnvColor(0, 0, 0, 0xFF);
    Text_Print(0x6A, 0x2C, GetMessageString(NULL, 0, gFragment54MessageBank, gMessageIdOffsetTable[gBattleContext.unk_0000]));
    Text_SetEnvColor(0xFF, 0xFF, 0x77, 0xFF);
    Text_Print(0x68, 0x2A, GetMessageString(NULL, 0, gFragment54MessageBank, gMessageIdOffsetTable[gBattleContext.unk_0000]));
    Text_SetupDL();
}

void RentalHub_DrawSelectionCursor(s16 arg0, s16 arg1, s16 arg2, s16 arg3) {
    static s16 D_82B01138 = 0;

    s16 sp56 = SINS(D_82B01138) * 2;
    UNUSED s32 pad[2];

    gSPDisplayList(gDisplayListHead++, gPrefDL_Border);
    gDPSetEnvColor(gDisplayListHead++, 240, 212, 104, 255);

    Gfx_DrawSpriteIA8(arg0 + sp56, arg1 + sp56, 0x10, 0x10, D_2000C80, 0x10, 0);
    Gfx_DrawSpriteIA8(arg0 + sp56, ((arg1 + arg3) - sp56) - 0x10, 0x10, 0x10, D_2000F80, 0x10, 0);
    Gfx_DrawSpriteIA8(((arg0 + arg2) - sp56) - 0x10, arg1 + sp56, 0x10, 0x10, D_2000D80, 0x10, 0);
    Gfx_DrawSpriteIA8(((arg0 + arg2) - sp56) - 0x10, ((arg1 + arg3) - sp56) - 0x10, 0x10, 0x10, D_2000E80, 0x10, 0);

    gSPDisplayList(gDisplayListHead++, gPrefDL_End);

    D_82B01138 += 0x2000;
}

void DrawFrameRect(s16 arg0, s16 arg1, s16 arg2, s16 arg3) {
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

void DrawMenuEntryBox(s16 arg0, s16 arg1, s16 arg2, char* arg3) {
    UNUSED s32 pad;

    if (arg2 >= 0xA) {
        arg1 += ((0x30 - arg2) / 2);
        DrawFrameRect(arg0, arg1, 0x98, arg2);

        gSPDisplayList(gDisplayListHead++, gMenuDL_BackgroundFill);

        Gfx_FillRect(arg0 + 4, arg1 + 4, 0x90, arg2 - 8, 0x1E, 0x1E, 0x82);

        gSPDisplayList(gDisplayListHead++, gPrefDL_End);

        if ((arg2 - 8) == 0x28) {
            Text_ResetState();
            Text_SetFont(0x10, 0);
            Text_Print((arg0 - (MeasureTextWidth(0x10, 0, arg3) / 2)) + 0x4C, arg1 + 0xB, arg3);
            Text_SetupDL();
        }
    }
}

void DrawMenuEntries(s16 arg0) {
    UNUSED s32 pad;

    DrawMenuEntryBox(0x50, 0x180, arg0 * 6, GetMessageString(NULL, 0, gFragment54MessageBank, 4));
    DrawMenuEntryBox(0xF4, 0x180, arg0 * 6, GetMessageString(NULL, 0, gFragment54MessageBank, 5));
    DrawMenuEntryBox(0x198, 0x180, arg0 * 6, GetMessageString(NULL, 0, gFragment54MessageBank, 6));
}

s32 GetMenuInput(void) {
    u32 var_v1 = 'exec';

    if (BTN_IS_PRESSED(gPlayer1Controller, BTN_A)) {
        PlaySoundEffect(0x1C);
        var_v1 = 'btnA';
    } else if (BTN_IS_PRESSED(gPlayer1Controller, BTN_B)) {
        PlaySoundEffect(3);
        var_v1 = 'btnB';
    } else if (BTN_IS_PRESSED(gPlayer1Controller, BTN_DLEFT)) {
        PlaySoundEffect(1);
        var_v1 = 'exec';
        gMenuCursorIndex -= 1;
        if (gMenuCursorIndex < 0) {
            gMenuCursorIndex = 2;
        }
    } else if (BTN_IS_PRESSED(gPlayer1Controller, BTN_DRIGHT)) {
        PlaySoundEffect(1);
        var_v1 = 'exec';
        gMenuCursorIndex++;
        if (gMenuCursorIndex >= 3) {
            gMenuCursorIndex = 0;
        }
    }
    return var_v1;
}

void RenderMenuFrame(s16 arg0) {
    Stage_BeginDisplayList();
    Gfx_DrawTextureAtlas(gFragment54TextureAtlas);
    DrawMenuHeader();
    DrawMenuEntries(arg0);
    if (arg0 == 8) {
        RentalHub_DrawSelectionCursor((gMenuCursorIndex * 0xA4) + 0x50, 0x180, 0x98, 0x30);
    }
    Stage_Advance();
}

void FadeInAndRunMenu(void) {
    if (Stage_GetFadeState != NULL) {
        Stage_FadeIn(8);
        while (Stage_GetFadeState() != 0) {
            Game_UpdateInputs();
            RenderMenuFrame(0);
        }
    }
}

void FadeOutAndCleanup(void) {
    if ((gBattleContext.unk_0000 == 7) || (gBattleContext.unk_0000 == 8)) {
        Music_StopTrack(0x10);
    }

    Stage_SetFillColor(0xFFFF);
    Stage_FadeOut(8);

    while (Stage_GetFadeState() != 1) {
        Game_UpdateInputs();
        RenderMenuFrame(0);
    }

    Stage_AdvanceN(2);
}

s16 RunMenuSelectionLoop(void) {
    s16 i;
    s16 var_v1;
    u32 temp_s1 = 'exec';

    gMenuCursorIndex = 0;
    FadeInAndRunMenu();
    PlaySoundEffect(4);

    for (i = 1; i < 8; i++) {
        Game_UpdateInputs();
        RenderMenuFrame(i);
    }

    while (temp_s1 == 'exec') {
        Game_UpdateInputs();
        temp_s1 = GetMenuInput();
        RenderMenuFrame(i);
    }

    for (i = 7; i >= 0; i--) {
        Game_UpdateInputs();
        RenderMenuFrame(i);
    }

    RenderMenuFrame(i);

    if (temp_s1 == 'btnA') {
        var_v1 = gMenuCursorIndex + 1;
    } else {
        if (gBattleContext.unk_0000 != 0) {
            FadeOutAndCleanup();
        }
        var_v1 = 0;
    }
    return var_v1;
}

void LoadMenuBackground(unk_func_80027FA0* arg0) {
    gBattleHeaderArchive = Asset_Load2(backgrounds_ROM_START, battle_headers_ROM_START, 1, 1);

    if (gBattleContext.unk_0000 == 7) {
        if (arg0->unk_04 < 8) {
            gFragment54TextureAtlas = BinArchive_GetFile(gBattleHeaderArchive, 0xD);
        } else {
            gFragment54TextureAtlas = BinArchive_GetFile(gBattleHeaderArchive, 0x10);
        }
    } else {
        gFragment54TextureAtlas = BinArchive_GetFile(gBattleHeaderArchive, gBackgroundFileIndexTable[gBattleContext.unk_0000]);
    }
}

s32 MenuFragment_Init(void) {
    s16 sp26;
    unk_func_80027FA0 sp1C;
    s16 temp_v0;

    main_pool_push_state('menu');

    GbsEnsureBankLoaded(2);
    GBAudio_ResetState(&sp1C, gBattleContext.unk_11F2);
    Text_Init(0x10, 0);

    ASSET_LOAD(D_1000000, common_menu1_ui, 0);
    ASSET_LOAD(D_2000000, common_menu2_ui, 0);

    LoadMenuBackground(&sp1C);
    MessageBank_Init();

    gFragment54MessageBank = GetMessageBank(0x18);
    gMenuCursorIndex = 0;

    if (gBattleContext.unk_0000 == 7) {
        if (sp1C.unk_04 < 8) {
            Music_ChangeTrack(0x2A);
        } else {
            Music_ChangeTrack(0x27);
        }
    }

    Menu_SetupDisplayList();
    sp26 = RunMenuSelectionLoop();
    Stage_Terminate();

    main_pool_pop_state('menu');

    return sp26;
}

s32 RentalHub_LoadRentalPicker(void) {
    FRAGMENT_LOAD_AND_CALL(fragment61, 1, 0);
    return 4;
}

s32 RentalHub_LoadRentalRules(void) {
    FRAGMENT_LOAD_AND_CALL(fragment55, 0, 0);
    return 4;
}

s32 Fragment54_Main(UNUSED s32 arg0, UNUSED s32 arg1) {
    s16 sp2E;
    s32 var_v1;
    s32 var_v1_2;

    sp2E = 4;
    main_pool_push_state('SUBT');

    while (sp2E >= 2) {
        switch (sp2E) {
            case 2:
                sp2E = RentalHub_LoadRentalRules();
                break;

            case 3:
                sp2E = RentalHub_LoadRentalPicker();
                break;

            case 4:
                sp2E = MenuFragment_Init();
                break;
        }
    }

    main_pool_pop_state('SUBT');
    return sp2E;
}
