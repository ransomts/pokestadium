#include "fragment36.h"
#include "src/1CF30.h"
#include "src/26820.h"
#include "src/29BA0.h"
#include "src/20330.h"
#include "src/2E110.h"
#include "src/2C1C0.h"
#include "src/3FB0.h"
#include "src/490A0.h"
#include "src/49790.h"
#include "src/50A00.h"
#include "src/6A40.h"
#include "src/DDC0.h"
#include "src/controller.h"
#include "src/math_util.h"
#include "src/memory.h"
#include "src/stage_loader.h"

static char** gMessageBank14;
static s32 pad_D_82100EA4;
static unk_func_80027FA0 D_82100EA8;
static BinArchive* D_82100EB0;
static u8* D_82100EB4;
static void* D_82100EB8;
static void* gAudioBankBuffer;
static u16 gMenuOption;
static s16* gMenuStatePtr;
static s32 gBorderEnabled;

void func_82100020(void) {
}

void func_82100028(UNUSED s32 arg0, UNUSED s32 arg1) {
}

void func_82100034(void) {
    MenuInput_ReadDirection();
}

s32 GetMenuOptionCode(void) {
    static s32 D_82100DC0 = 0;

    s32 var_v1 = 4;

    if (D_82100DC0 != 0) {
        switch (gMenuOption) {
            case 0:
                break;

            case 1:
                var_v1 = 0x80;
            break;

            case 2:
                var_v1 = 0x81;
            break;

            case 3:
                var_v1 = 0x82;
            break;

            case 4:
                var_v1 = 0x20;
            break;

            case 5:
                var_v1 = 0x25;
            break;

            case 6:
                var_v1 = 0x11;
            break;
        }
    }

    return var_v1;
}

void DrawBorderOverlay(s16 arg0, s16 arg1) {
    static s32 D_82100DC4 = 0x40;

    s32 temp_v0 = D_82100DC4 - 0x30;
    s32 var_s0 = 0;

    if (temp_v0 >= 0) {
        if (temp_v0 < 0x10) {
            var_s0 = temp_v0 * 0x10;
        } else if (temp_v0 < 0x23) {
            var_s0 = 0xFF;
        } else if (temp_v0 < 0x32) {
            var_s0 = (-temp_v0 * 0x10) + 0x320;
        }
    }

    D_82100DC4++;
    if (D_82100DC4 > 0x6C) {
        D_82100DC4 = 0x30;
    }

    gSPDisplayList(gDisplayListHead++, gPrefDL_Border);
    gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, var_s0);

    gDPLoadTextureTile(gDisplayListHead++, D_2000000, G_IM_FMT_IA, G_IM_SIZ_8b, 100, 0, 0, 0, 100 - 1, 15 - 1, 0,
                       G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                       G_TX_NOLOD);

    Gfx_DrawTextureRect(arg0, arg1, 100, 15, 0, 0, 0x400, 0x400, 0);

    gSPDisplayList(gDisplayListHead++, gPrefDL_End);
}

void func_821002F8(void) {
    static s32 D_82100DC8 = 0;

    s32 sp24;
    s16 temp_s0;

    if (!(Cont_GetControllerBits() & 1)) {
        sp24 = MeasureTextWidth(4, 0, GetMessageString(NULL, 0, gMessageBank14, 0));
        temp_s0 = 0x50 - D_82100DC8;

        gDPSetScissor(gDisplayListHead++, G_SC_NON_INTERLACE, 16, 0, 304, 240);

        Text_ResetState();
        Text_SetFont(4, 0);
        Text_Print(temp_s0, 0xB3, GetMessageString(NULL, 0, gMessageBank14, 0));

        temp_s0 += sp24 + 30;
        if (temp_s0 < 0x140) {
            Text_Print(temp_s0, 0xB3, GetMessageString(NULL, 0, gMessageBank14, 0));
        }

        Text_SetupDL();

        gDPSetScissor(gDisplayListHead++, G_SC_NON_INTERLACE, 0, 0, 320, 240);

        D_82100DC8++;
        if (D_82100DC8 >= (sp24 + 0x50)) {
            D_82100DC8 = 0x32;
        }
    }
}

void DrawBackgroundTextureTiles(u8* arg0) {
    s32 i;
    s32 j;

    gDPPipeSync(gDisplayListHead++);
    gDPSetCycleType(gDisplayListHead++, G_CYC_1CYCLE);
    gDPSetRenderMode(gDisplayListHead++, G_RM_OPA_SURF, G_RM_OPA_SURF2);
    gDPSetTexturePersp(gDisplayListHead++, G_TP_NONE);
    gDPSetCombineMode(gDisplayListHead++, G_CC_DECALRGB, G_CC_DECALRGB);

    gDPPipeSync(gDisplayListHead++);

    for (i = 0; i < 0xF0; i += 0x10) {
        for (j = 0; j < 0x140; j += 0x10, arg0 += 0x200) {
            Gfx_DrawSpriteRGBA16(j, i, 0x10, 0x10, arg0, 0x10, 0);
        }
    }

    gSPDisplayList(gDisplayListHead++, gPrefDL_End);
}

void TitleScreen_RenderFrame(void) {
    Stage_BeginDisplayList();
    DrawBackgroundTextureTiles(D_82100EB4);
    if ((Cont_GetControllerBits() & 1) && (gBorderEnabled != 0)) {
        DrawBorderOverlay(0x6E, 0xAF);
    }
    func_821002F8();
    func_82100028(0x64, 0x50);
    Stage_Advance();
}

static u8 gFlagTable[] = {
    0x21, 0x22, 0x18, 0x21, 0x22, 0x14, 0x21, 0x22, 0x14, 0x21, 0x22, 0x24, 0x21, 0x22, 0x14, 0x21, 0x22, 0x24, 0x21,
    0x22, 0x21, 0x12, 0x21, 0x30, 0x03, 0x22, 0x21, 0x24, 0x21, 0x22, 0x14, 0x21, 0x22, 0x14, 0x21, 0x22, 0x21, 0x24,
    0x21, 0x24, 0x21, 0x24, 0x21, 0x30, 0x24, 0x21, 0x22, 0x22, 0x24, 0x21, 0x18, 0x21, 0x24, 0x21, 0x24, 0x22, 0x14,
    0x21, 0x14, 0x21, 0x22, 0x24, 0x21, 0x22, 0x18, 0x21, 0x24, 0x30, 0x21, 0x30, 0x24, 0x22, 0x24, 0x21, 0x24, 0x18,
    0x22, 0x24, 0x22, 0x24, 0x21, 0x18, 0x21, 0x22, 0x24, 0x22, 0x28, 0x24, 0x28, 0x21, 0x12, 0x21, 0x24, 0x18, 0x12,
    0x22, 0x18, 0x21, 0x24, 0x21, 0x18, 0x21, 0x18, 0x21, 0x24, 0x24, 0x24, 0x28, 0x21, 0x24, 0x22, 0x24, 0x18, 0x22,
    0x18, 0x21, 0x24, 0x21, 0x24, 0x22, 0x18, 0x24, 0x12, 0x18, 0x24, 0x28, 0x18, 0x18, 0x21, 0x18, 0x18, 0x18, 0x21,
    0x18, 0x18, 0x14, 0x22, 0x21, 0x24, 0x21, 0x24, 0x14, 0x18, 0x18, 0x18, 0x14, 0x21, 0x22, 0x18, 0x20, 0x28,
};

s32 CountFlagOccurrences(s32 arg0) {
    s32 var_v1 = 0;
    s32 i;

    for (i = 0; i < 151; i++) {
        if (gFlagTable[i] & arg0) {
            var_v1++;
        }
    }

    return var_v1;
}

s32 func_8210071C(s32 arg0, u32 arg1) {
    s32 i;

    for (i = 0; i < 150; i++) {
        if (gFlagTable[i] & arg1) {
            arg0--;
            if (arg0 == -1) {
                break;
            }
        }
    }

    return i + 1;
}

void func_82100760(u8* arg0) {
    s32 temp_s0;
    s32 sp38;
    UNUSED s32 pad[2];
    s32 sp2C;

    sp2C = CountFlagOccurrences(arg0[2]);

    temp_s0 = osGetCount() & 0xFF;
    while (temp_s0-- > 0) {
        MathUtil_Random_ZeroOne();
    }

    temp_s0 = MathUtil_Random_ZeroOne() * sp2C;
    do {
        sp38 = MathUtil_Random_ZeroOne() * sp2C;
    } while (temp_s0 == sp38);

    Battle_CreateTwoPlayerMatch(arg0[0], arg0[1], func_8210071C(temp_s0, arg0[2]), func_8210071C(sp38, arg0[2]));
}

static u8 gTwoPlayerBattlePresets[2][4] = {
    { 4, 0, 1, 3 },
    { 5, 0, 2, 9 },
};

static u8 D_82100E6C[4][4] = {
    { 3, 3, 4, 13 },
    { 6, 3, 8, 3 },
    { 7, 4, 16, 9 },
    { 0, 0, 32, 13 },
};

s32 func_82100844(void) {
    u8 temp_a1 = (*gMenuStatePtr >> 8);
    u8 temp_a2 = *gMenuStatePtr;
    s16 mod = temp_a2 % 2;
    s16 low_index = temp_a2 / 2;

    if (mod == 0) {
        func_82100760(gTwoPlayerBattlePresets[low_index]);
    } else {
        gBattleContext.unk_0000 = 0x19;
        gBattleContext.unk_0003 = gTwoPlayerBattlePresets[low_index][3];
    }

    temp_a1 = ((temp_a1 + 1) % 4);
    temp_a2 = (temp_a2 + 1) % 12;
    *gMenuStatePtr = (temp_a1 << 8) | temp_a2;
    return 2;
}

s32 func_82100958(void) {
    static u32 D_82100E7C = 0;

    s32 sp1C = 0;

    if (D_82100E7C >= 0x259) {
        if (Audio_CalcLoadScore() == 0) {
            sp1C = 1;
        }
    } else {
        D_82100E7C += 1;
    }
    return sp1C;
}

s32 func_821009AC(void) {
    return 0;
}

s32 func_821009B4(void) {
    s32 var_s0 = 0;
    s32 var_s2 = 30;

    MenuInput_SetController(gPlayer1Controller);

    while (var_s0 == 0) {
        if (gBorderEnabled == 0) {
            var_s2--;
            if (var_s2 <= 0) {
                gBorderEnabled = 1;
            }
        }

        Game_UpdateInputs();

        if ((gPlayer1Controller->buttonPressed & 0x9000) && (gBorderEnabled != 0)) {
            PlaySoundEffect(0xF);
            var_s0 = GetMenuOptionCode();
        } else if (func_82100958() != 0) {
            var_s0 = func_82100844();
        } else {
            var_s0 = func_821009AC();
            if (var_s0 == 0) {
                func_82100034();
            }
        }

        TitleScreen_RenderFrame();
    }

    return var_s0;
}

void func_82100AB8(void) {
    if (Stage_GetFadeState() == 1) {
        Stage_FadeIn(0xA);
        while (Stage_GetFadeState() != 0) {
            Game_UpdateInputs();
            TitleScreen_RenderFrame();
        }
    }
}

void func_82100B1C(s32 arg0) {
    if (arg0 == 3) {
        Stage_SetFillColor(1);
    } else {
        Stage_SetFillColor(0xFFFF);
    }

    Stage_FadeOut(8);

    while (Stage_GetFadeState() != 1) {
        Game_UpdateInputs();
        TitleScreen_RenderFrame();
    }
}

void func_82100B98(void) {
    ASSET_LOAD(D_1000000, common_menu1_ui, 0);
    // bin contains a JP logo and press start, but this bin is loaded for the "Press Start" gfx
    ASSET_LOAD(D_2000000, title_ui, 0);

    D_82100EB8 = main_pool_alloc(0x4510, 0);
    gAudioBankBuffer = main_pool_alloc(0x100000, 0);

    D_82100EB0 = ASSET_LOAD2(backgrounds, 1, 1);

    if (D_82100EA8.unk_00 == 0x1F8) {
        D_82100EB4 = BinArchive_GetFile(D_82100EB0, 0x11);
    } else {
        D_82100EB4 = BinArchive_GetFile(D_82100EB0, 0);
    }

    gBorderEnabled = 0;
}

s32 func_82100C98(UNUSED s32 arg0, s16* arg1) {
    s32 sp24;

    gMenuStatePtr = arg1;

    if (Stage_GetCurrent() == NULL) {
        main_pool_push_state('TITL');

        Gfx_InitBuffers(0x10000, 0);
        Stage_Set(Stage_Create(0, 1, 3, 1, 2, 1));
    } else {
        Menu_SetupDisplayList();
    }

    GbsEnsureBankLoaded(2);
    GBAudio_ResetState(&D_82100EA8, 0);
    Text_Init(6, 0);
    func_82100B98();
    MessageBank_Init();
    gMessageBank14 = GetMessageBank(0x14);
    Audio_LoadBankAndSong(gAudioBankBuffer);
    func_82100AB8();
    sp24 = func_821009B4();
    func_82100B1C(sp24);
    Stage_Destroy();
    Audio_WaitForLoadAndFade(0);
    Audio_ClearBankDMAFlag();
    Gfx_FreeBuffers();

    main_pool_pop_state('TITL');
    return sp24;
}
