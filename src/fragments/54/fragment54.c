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

static char** D_82B01140;
static BinArchive* D_82B01144;
static void* D_82B01148;
static s16 D_82B0114C;

static u8 D_82B01120[] = {
    0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0F, 0x00, 0x00,
};

static s8 D_82B0112C[] = {
    0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x02, 0x03,
};

void func_82B00020(s16 arg0, s16 arg1) {
    gSPDisplayList(gDisplayListHead++, gPrefDL_Border);

    Gfx_DrawSpriteRGBA16(arg0, arg1, 0x30, 0x18, D_2006C00, 0x30, 0);
    Gfx_DrawSpriteRGBA16(arg0, arg1 + 0x18, 0x30, 0x18, D_2007500, 0x30, 0);

    gSPDisplayList(gDisplayListHead++, gPrefDL_End);
}

void func_82B000F4(s16 arg0, s16 arg1, s16 arg2, Color_RGBA8* arg3, Color_RGBA8* arg4) {
    gSPDisplayList(gDisplayListHead++, D_8006F558);

    gDPSetEnvColor(gDisplayListHead++, arg3->r, arg3->g, arg3->b, 255);
    gDPSetPrimColor(gDisplayListHead++, 0, 0, arg4->r, arg4->g, arg4->b, 255);

    Gfx_DrawSpriteIA8(arg0, arg1, 0x10, 0x20, D_20003C0, 0x10, 0);
    Gfx_DrawSpriteIA8((arg0 + arg2) - 0x10, arg1, 0x10, 0x20, D_20005C0, 0x10, 0);
    Gfx_DrawTextureRect(arg0 + 0x10, arg1, arg2 - 0x20, 0x20, 0, 0, 0, 0x400, 0);

    gSPDisplayList(gDisplayListHead++, gPrefDL_End);
}

void func_82B0029C(void) {
    Color_RGBA8 sp2C;
    Color_RGBA8 sp28;

    func_8000E820(&sp2C, 0x64, 0x64, 0xC8);
    func_8000E820(&sp28, 0x28, 0x28, 0x8C);
    func_82B000F4(0x48, 0x28, 0x208, &sp2C, &sp28);
    func_82B00020(0x30, 0x20);
    Text_ResetState();
    Text_SetFont(0x10, 0);
    Text_SetEnvColor(0, 0, 0, 0xFF);
    Text_Print(0x6A, 0x2C, GetMessageString(NULL, 0, D_82B01140, D_82B0112C[gBattleContext.unk_0000]));
    Text_SetEnvColor(0xFF, 0xFF, 0x77, 0xFF);
    Text_Print(0x68, 0x2A, GetMessageString(NULL, 0, D_82B01140, D_82B0112C[gBattleContext.unk_0000]));
    Text_SetupDL();
}

void func_82B003B8(s16 arg0, s16 arg1, s16 arg2, s16 arg3) {
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

void func_82B005AC(s16 arg0, s16 arg1, s16 arg2, s16 arg3) {
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

void func_82B00814(s16 arg0, s16 arg1, s16 arg2, char* arg3) {
    UNUSED s32 pad;

    if (arg2 >= 0xA) {
        arg1 += ((0x30 - arg2) / 2);
        func_82B005AC(arg0, arg1, 0x98, arg2);

        gSPDisplayList(gDisplayListHead++, D_8006F470);

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

void func_82B00994(s16 arg0) {
    UNUSED s32 pad;

    func_82B00814(0x50, 0x180, arg0 * 6, GetMessageString(NULL, 0, D_82B01140, 4));
    func_82B00814(0xF4, 0x180, arg0 * 6, GetMessageString(NULL, 0, D_82B01140, 5));
    func_82B00814(0x198, 0x180, arg0 * 6, GetMessageString(NULL, 0, D_82B01140, 6));
}

s32 func_82B00A50(void) {
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
        D_82B0114C -= 1;
        if (D_82B0114C < 0) {
            D_82B0114C = 2;
        }
    } else if (BTN_IS_PRESSED(gPlayer1Controller, BTN_DRIGHT)) {
        PlaySoundEffect(1);
        var_v1 = 'exec';
        D_82B0114C++;
        if (D_82B0114C >= 3) {
            D_82B0114C = 0;
        }
    }
    return var_v1;
}

void func_82B00B3C(s16 arg0) {
    Stage_BeginDisplayList();
    Gfx_DrawTextureAtlas(D_82B01148);
    func_82B0029C();
    func_82B00994(arg0);
    if (arg0 == 8) {
        func_82B003B8((D_82B0114C * 0xA4) + 0x50, 0x180, 0x98, 0x30);
    }
    Stage_Advance();
}

void func_82B00BC8(void) {
    if (func_80007604 != NULL) {
        func_80006C6C(8);
        while (func_80007604() != 0) {
            Game_UpdateInputs();
            func_82B00B3C(0);
        }
    }
}

void func_82B00C24(void) {
    if ((gBattleContext.unk_0000 == 7) || (gBattleContext.unk_0000 == 8)) {
        func_8000D278(0x10);
    }

    func_80007990(0xFFFF);
    func_80006CB4(8);

    while (func_80007604() != 1) {
        Game_UpdateInputs();
        func_82B00B3C(0);
    }

    Stage_AdvanceN(2);
}

s16 func_82B00CB4(void) {
    s16 i;
    s16 var_v1;
    u32 temp_s1 = 'exec';

    D_82B0114C = 0;
    func_82B00BC8();
    PlaySoundEffect(4);

    for (i = 1; i < 8; i++) {
        Game_UpdateInputs();
        func_82B00B3C(i);
    }

    while (temp_s1 == 'exec') {
        Game_UpdateInputs();
        temp_s1 = func_82B00A50();
        func_82B00B3C(i);
    }

    for (i = 7; i >= 0; i--) {
        Game_UpdateInputs();
        func_82B00B3C(i);
    }

    func_82B00B3C(i);

    if (temp_s1 == 'btnA') {
        var_v1 = D_82B0114C + 1;
    } else {
        if (gBattleContext.unk_0000 != 0) {
            func_82B00C24();
        }
        var_v1 = 0;
    }
    return var_v1;
}

void func_82B00DD0(unk_func_80027FA0* arg0) {
    D_82B01144 = Asset_Load2(backgrounds_ROM_START, battle_headers_ROM_START, 1, 1);

    if (gBattleContext.unk_0000 == 7) {
        if (arg0->unk_04 < 8) {
            D_82B01148 = BinArchive_GetFile(D_82B01144, 0xD);
        } else {
            D_82B01148 = BinArchive_GetFile(D_82B01144, 0x10);
        }
    } else {
        D_82B01148 = BinArchive_GetFile(D_82B01144, D_82B01120[gBattleContext.unk_0000]);
    }
}

s32 func_82B00E84(void) {
    s16 sp26;
    unk_func_80027FA0 sp1C;
    s16 temp_v0;

    main_pool_push_state('menu');

    GbsEnsureBankLoaded(2);
    func_80027FA0(&sp1C, gBattleContext.unk_11F2);
    Text_Init(0x10, 0);

    ASSET_LOAD(D_1000000, common_menu1_ui, 0);
    ASSET_LOAD(D_2000000, common_menu2_ui, 0);

    func_82B00DD0(&sp1C);
    MessageBank_Init();

    D_82B01140 = GetMessageBank(0x18);
    D_82B0114C = 0;

    if (gBattleContext.unk_0000 == 7) {
        if (sp1C.unk_04 < 8) {
            func_8000D1F0(0x2A);
        } else {
            func_8000D1F0(0x27);
        }
    }

    func_80007754();
    sp26 = func_82B00CB4();
    func_8000771C();

    main_pool_pop_state('menu');

    return sp26;
}

s32 func_82B00FAC(void) {
    FRAGMENT_LOAD_AND_CALL(fragment61, 1, 0);
    return 4;
}

s32 func_82B00FFC(void) {
    FRAGMENT_LOAD_AND_CALL(fragment55, 0, 0);
    return 4;
}

s32 func_82B0104C(UNUSED s32 arg0, UNUSED s32 arg1) {
    s16 sp2E;
    s32 var_v1;
    s32 var_v1_2;

    sp2E = 4;
    main_pool_push_state('SUBT');

    while (sp2E >= 2) {
        switch (sp2E) {
            case 2:
                sp2E = func_82B00FFC();
                break;

            case 3:
                sp2E = func_82B00FAC();
                break;

            case 4:
                sp2E = func_82B00E84();
                break;
        }
    }

    main_pool_pop_state('SUBT');
    return sp2E;
}
