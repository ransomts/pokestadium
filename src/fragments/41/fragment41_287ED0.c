#include "fragment41.h"
#include "src/19840.h"
#include "src/1C720.h"
#include "src/1CF30.h"
#include "src/20330.h"
#include "src/20470.h"
#include "src/225A0.h"
#include "src/22630.h"
#include "src/232C0.h"
#include "src/2E110.h"
#include "src/3FB0.h"
#include "src/49790.h"
#include "src/4BDC0.h"
#include "src/6A40.h"
#include "src/controller.h"
#include "src/memory.h"
#include "src/stage_loader.h"

typedef struct unk_D_82F14438 {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ s16 unk_08;
    /* 0x0A */ s16 unk_0A;
    /* 0x0C */ u16 unk_0C;
    /* 0x10 */ s8* unk_10;
} unk_D_82F14438; // size = 0x14

typedef struct unk_D_82F144B0 {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ s16 unk_08;
} unk_D_82F144B0; // size = 0xA

static TextObject* gFragment41TextObject;
s32 gFragment41FrameCounter;
static s32 gFragment41State;
static s16 gMessageEntryIndex;
static unk_D_82F13B78* gCurrentMessageList;
static s32 pad_D_82F14434;
static unk_D_82F14438 gTextBoxState;
static unk_D_82F14438* gCurrentTextBox;
unk_D_82F14450 gPlayerInfo[4];
static s16 gActivePlayerIndex;
static s16 gSelectedOptionId;
static s32 pad_D_82F144AC;
static unk_D_82F144B0 gProgressBarRect;
static s32 gPoolStatePushed;
static s32 gPollControllerFlag;
static char** D_82F144C4;
static char** D_82F144C8;
static char** D_82F144CC;

char** D_82F13B70 = NULL;
char** D_82F13B74 = NULL;
static unk_D_82F13B78 D_82F13B78[2] = {
    { 0x0140, 0x0168, NULL },
    { 0x0000, 0x0000, NULL },
};
static u16 D_82F13B88 = 0;

char* GetMessageStringBank24(s32 arg0) {
    return GetMessageString(NULL, 0, D_82F144C4, arg0 - 1);
}

char* GetMessageStringBank25(s32 arg0) {
    return GetMessageString(NULL, 0, D_82F144C8, arg0 - 1);
}

char* GetMessageStringBank26Remapped(s32 arg0) {
    return GetMessageString(NULL, 0, D_82F144CC, RemapStadiumModeIndex(arg0));
}

void InitProgressBarRect(s16 arg0) {
    unk_D_82F144B0* ptr = &gProgressBarRect;

    switch (arg0) {
        case 0:
            ptr->unk_02 = 0;
            ptr->unk_04 = 0;
            ptr->unk_06 = 0x280;
            ptr->unk_08 = 0x1E0;
            break;

        case 1:
            ptr->unk_02 = 0;
            ptr->unk_04 = 0x154;
            ptr->unk_06 = 0x280;
            ptr->unk_08 = 0x8C;
            break;
    }
}

void ResetProgressBar(void) {
    gProgressBarRect.unk_00 = -1;
    InitProgressBarRect(0);
}

void UpdateProgressBar(void) {
    unk_D_82F144B0* ptr = &gProgressBarRect;

    if ((ptr->unk_00 != 0) && (MenuPanel_IsAnimating() != 0)) {
        if (ptr->unk_00 > 0) {
            ptr->unk_00--;
        }

        gSPDisplayList(gDisplayListHead++, gDL_FillCycle);
        gDPSetFillColor(gDisplayListHead++, 0x00010001);
        gDPFillRectangle(gDisplayListHead++, ptr->unk_02, ptr->unk_04, (ptr->unk_02 + ptr->unk_06) - 1,
                         (ptr->unk_04 + ptr->unk_08) - 1);
    }
}

void InitTextBox(void) {
    gCurrentTextBox = &gTextBoxState;
    gTextBoxState.unk_00 = 0;
    gTextBoxState.unk_02 = 0;
    gTextBoxState.unk_08 = 0;
    gTextBoxState.unk_0A = 2;
    gTextBoxState.unk_04 = 0;
    gTextBoxState.unk_06 = 0;
    gTextBoxState.unk_0C = 0;
    gTextBoxState.unk_10 = NULL;
}

void SetTextBox(s16 arg0, s16 arg1, s8* arg2, s32 arg3) {
    s8* ptr;

    gCurrentTextBox->unk_00 = 0;
    gCurrentTextBox->unk_02 = 0;

    ptr = arg2;
    if (ptr != NULL) {
        while (*ptr != '\x00') {
            gCurrentTextBox->unk_02++;
            ptr++;
        }
    }

    gCurrentTextBox->unk_08 = 0;
    gCurrentTextBox->unk_0A = 2;
    gCurrentTextBox->unk_04 = arg0;
    gCurrentTextBox->unk_06 = arg1;
    gCurrentTextBox->unk_0C = 0;

    if (arg3 != 0) {
        gCurrentTextBox->unk_0C |= 1;
    }

    gCurrentTextBox->unk_10 = arg2;
}

void ClearMessageList(void) {
    gCurrentMessageList = NULL;
}

void LoadNextMessageEntry(unk_D_82F13B78* arg0, s32 arg1) {
    if (arg0 != gCurrentMessageList) {
        gMessageEntryIndex = 0;
    }

    gCurrentMessageList = arg0;

    if (NULL != arg0) {
        unk_D_82F13B78* ptr = &arg0[gMessageEntryIndex];

        SetTextBox(ptr->unk_00, ptr->unk_02, ptr->unk_04, arg1);
        gMessageEntryIndex++;
    }
}

s32 IsMessageEntryEmpty(unk_D_82F13B78* arg0) {
    unk_D_82F13B78* ptr = &arg0[gMessageEntryIndex];
    s32 var_v1 = 0;

    if (ptr->unk_04 == NULL) {
        var_v1 = 1;
    }
    return var_v1;
}

void UpdateTextBox(void) {
    u8 tmp;

    if ((gCurrentTextBox->unk_10 != 0) && (gCurrentTextBox->unk_00 >= 0)) {
        if (gPlayer1Controller->buttonPressed & 0x8000) {
            gCurrentTextBox->unk_08 = 0;
            gCurrentTextBox->unk_0A = 1;
        } else {
            gCurrentTextBox->unk_08 -= 1;
        }

        if (gCurrentTextBox->unk_08 <= 0) {
            PlaySoundEffect(0x01200001);
            gCurrentTextBox->unk_08 = gCurrentTextBox->unk_0A;

            gCurrentTextBox->unk_00++;

            tmp = gCurrentTextBox->unk_10[gCurrentTextBox->unk_00 - 1];
            if (tmp >= 0x80) {
                gCurrentTextBox->unk_00++;
            }

            if (gCurrentTextBox->unk_00 >= gCurrentTextBox->unk_02) {
                gCurrentTextBox->unk_00 = -1;
            }
        }
    }
}

s32 GetTextBoxState(void) {
    s32 var_v1 = 0;

    if (gCurrentTextBox->unk_10 != NULL) {
        if (gCurrentTextBox->unk_00 == -1) {
            var_v1 = 2;
        } else if (gCurrentTextBox->unk_00 >= 0) {
            var_v1 = 1;
        }
    }

    return var_v1;
}

void DrawTextBox(void) {
    s32 i;
    s32 temp_t0;
    s8 sp38[0x100];

    if (gCurrentTextBox->unk_10 != NULL) {
        Text_ResetState();
        Text_SetFont(0x10, 0);

        if (gCurrentTextBox->unk_0C & 1) {
            s32 a = D_82F13B88;
            u8 arg = a & 0xF;

            arg = (arg * 0xFF) / 15;
            if (a & 0x10) {
                arg = 0xFF - arg;
            }
            Text_SetEnvColor(0xFF, 0xFF, 0xFF, arg);
        } else {
            Text_SetEnvColor(0xFF, 0xFF, 0xFF, 0xFF);
        }

        Text_SetLineHeight(0x1E);
        temp_t0 = MeasureTextWidth(0, 0, gCurrentTextBox->unk_10) / 2;
        if (gCurrentTextBox->unk_00 == -1) {
            Text_Print(gCurrentTextBox->unk_04 - temp_t0, gCurrentTextBox->unk_06, gCurrentTextBox->unk_10);
        } else {
            s8* p_sp38 = sp38;
            s8* other = gCurrentTextBox->unk_10;

            for (i = 0; i < gCurrentTextBox->unk_00; i++) {
                *p_sp38++ = *other++;
            }

            *p_sp38 = '\x00';
            Text_Print(gCurrentTextBox->unk_04 - temp_t0, gCurrentTextBox->unk_06, &sp38);
        }
        Text_SetupDL();
        D_82F13B88++;
    }
}

void PollControllerInputs(void) {
    Cont_StartReadInputs();
    Cont_ReadInputs();
    MenuInput_Init();
}

void UpdateControllerInfo(void) {
    UNUSED s32 pad;
    unk_D_82F14450* ptr;
    Gen1StringDecodeBuffer sp40;
    u8 temp_s2 = Cont_GetControllerBits();
    s32 i;

    main_pool_push_state('info');

    for (i = 0, ptr = &gPlayerInfo[0]; i < 4; i++, ptr++) {
        Controller_ReadInput(i, &sp40);
        SaveSlot_Load(i);
        DecodeGen1StringToBuffer(ptr->unk_08, sp40.unk_02);
        ptr->unk_06 = sp40.unk_00;
        ptr->unk_01 = MenuItem_GetHeldItemId(i);
        ptr->unk_00 = MenuItem_GetPokemonSpecies(i);
        ptr->unk_03 = MenuItem_GetPokemonGender(i);
        ptr->unk_04 = MenuItem_IsPokemonShiny(i);
        ptr->unk_05 = (temp_s2 & (1 << i)) != 0;
        ptr->unk_02 = MenuItem_GetPokemonLevel(i);
    }

    main_pool_pop_state('info');
}

void SwapPlayerSelections(void) {
    s32 i;
    PickerPokemonEntry sp50;
    unk_func_82F00838_sp30 sp30[2];

    for (i = 0; i < 2; i++) {
        Picker_GetSelectionInfo(i, &sp30[i]);
    }

    sp50 = sp30[0].unk_0C[sp30[0].unk_06];
    sp30[0].unk_0C[sp30[0].unk_06] = sp30[1].unk_0C[sp30[1].unk_06];
    sp30[1].unk_0C[sp30[1].unk_06] = sp50;

    Picker_SwapSelectedSprites();
}

void func_82F00960(void) {
}

void InitFragment41(void) {
    Graph_InitRoots();
    MessageBank_Init();
    D_82F13B70 = GetMessageBank(0x21);
    D_82F13B74 = GetMessageBank(6);
    D_82F144C4 = GetMessageBank(0x24);
    D_82F144C8 = GetMessageBank(0x25);
    D_82F144CC = GetMessageBank(0x26);
    D_82F13B78[0].unk_04 = GetMessageString(NULL, 0, D_82F13B70, 0);
    gFragment41State = 0;
    ClearMessageList();
    gFragment41FrameCounter = 0;
    gActivePlayerIndex = 0;
    gPoolStatePushed = 0;
    ResetProgressBar();
    InitTextBox();
    MenuPanel_Init();
    UpdateControllerInfo();
    InitMenuGraphics();
    Picker_Reset();
    func_82F0C190();
}

void RenderFragment41Frame(void) {
    Stage_BeginDisplayList();
    UpdateProgressBar();
    if (MenuPanel_IsAnimating() != 0) {
        MenuPanel_Render();
    }
    DrawTextBox();
    func_82F09E30();
    Picker_Render();
    func_82F0C320();
    func_82F00960();
    Stage_Advance();
}

void func_82F00AC8(s32 arg0) {
    gFragment41State = arg0;

    switch (gFragment41State) {
        case 1:
            ClearMessageList();
            LoadNextMessageEntry(D_82F13B78, 0);
            break;

        case 2:
            func_82F07958();
            SetTextBox(0, 0, 0, 0);
            break;

        case 4:
            if (gActivePlayerIndex == 1) {
                if (gPoolStatePushed != 0) {
                    main_pool_pop_state('pmex');
                }
                main_pool_push_state('pmex');
                gPoolStatePushed = 1;
            }
            SnapSelect_SetCameraMode(func_82F07A54(gActivePlayerIndex));
            InitPokemonPicker(gActivePlayerIndex, func_82F07A54(gActivePlayerIndex));
            break;

        case 5:
            RentalMenu_Init(0);
            break;

        case 6:
            RentalMenu_Init(1);
            break;

        case 7:
            InitProgressBarRect(0);
            Stage_FadeOut(0xF);
            Stage_SetFadeColor(0xF);
            break;
    }
}

void func_82F00C14(s16 arg0) {
    gSelectedOptionId = arg0;
    func_82F00AC8(3);
    MenuPanel_SetMainState(gSelectedOptionId);
}

void func_82F00C50(void) {
    if (BTN_IS_PRESSED(gPlayer1Controller, BTN_A)) {
        if (IsMessageEntryEmpty(D_82F13B78) == 0) {
            LoadNextMessageEntry(D_82F13B78, 0);
        } else {
            func_82F00AC8(2);
        }
        PlaySoundEffect(2);
        PlaySoundEffect(4);
    } else if (BTN_IS_PRESSED(gPlayer1Controller, BTN_B)) {
        func_82F00AC8(7);
        PlaySoundEffect(3);
    }
}

void func_82F00CE0(void) {
    InitProgressBarRect(1);
    if (func_82F07A74() == 0) {
        if (func_82F07A54(1) == -1) {
            func_82F00AC8(7);
        } else {
            func_82F00C14(1);
        }
    }
}

void func_82F00D3C(void) {
    InitProgressBarRect(0);

    switch (gSelectedOptionId) {
        case 1:
            if (MenuPanel_CheckState(1) != 0) {
                func_82F00AC8(4);
            }
            break;

        case 19:
            if (MenuPanel_CheckState(2) != 0) {
                func_82F00AC8(4);
            }
            break;

        case 4:
        case 8:
        case 11:
            if (MenuPanel_CheckState(3) != 0) {
                func_82F00AC8(2);
            }
            break;

        case 20:
            if (MenuPanel_CheckState(6) != 0) {
                func_82F00AC8(5);
            }
            break;

        case 21:
            if (MenuPanel_CheckState(8) != 0) {
                SwapPlayerSelections();
                func_82F00C14(0xC);
            }
            break;

        case 12:
            if (MenuPanel_CheckState(0xC) != 0) {
                if (gProgressBarRect.unk_00 == -1) {
                    gProgressBarRect.unk_00 = 5;
                }
            } else {
                gProgressBarRect.unk_00 = -1;
            }

            if (MenuPanel_CheckState(0xA) != 0) {
                func_82F00AC8(6);
            }
            break;
    }
}

void func_82F00E88(void) {
    unk_func_82F00838_sp30 sp20;

    if (GetPickerState() == 0) {
        Picker_GetSelectionInfo(gActivePlayerIndex, &sp20);

        if (sp20.unk_00 != 0) {
            if (gActivePlayerIndex == 0) {
                func_82F00C14(0x13);
            } else {
                func_82F00C14(0x14);
            }
            gActivePlayerIndex ^= 1;
        } else {
            if (gActivePlayerIndex == 0) {
                SetTextBox(0, 0, NULL, 0);
                func_82F00C14(4);
                return;
            }
            func_82F00C14(8);
            gActivePlayerIndex = 0;
        }
    }
}

void func_82F00F3C(void) {
    InitProgressBarRect(1);

    if (func_82F0C16C() == 2) {
        if (gProgressBarRect.unk_00 == -1) {
            gProgressBarRect.unk_00 = 3;
        }
    } else {
        gProgressBarRect.unk_00 = -1;
    }

    if (func_82F0C16C() == 0) {
        if (func_82F0C178() != 0) {
            func_82F00C14(0x15);
        } else {
            func_82F00C14(0xB);
        }
    }
}

void func_82F00FD8(void) {
    InitProgressBarRect(1);

    if (func_82F0C16C() == 2) {
        if (gProgressBarRect.unk_00 == -1) {
            gProgressBarRect.unk_00 = 3;
        }
    } else {
        gProgressBarRect.unk_00 = -1;
    }

    if (func_82F0C16C() == 7) {
        gPollControllerFlag = 0;
    } else {
        gPollControllerFlag = 1;
    }

    if (func_82F0C16C() == 0) {
        if (func_82F0C184() != 0) {
            func_82F00AC8(2);
        } else {
            func_82F00AC8(7);
        }
    }
}

s32 func_82F0109C(void) {
    s32 sp1C = 1;

    switch (gFragment41State) {
        case 0:
            if (Stage_GetFadeState() == 0) {
                func_82F00AC8(1);
            }
            break;

        case 1:
            func_82F00C50();
            break;

        case 2:
            func_82F00CE0();
            break;

        case 3:
            func_82F00D3C();
            break;

        case 4:
            func_82F00E88();
            break;

        case 5:
            func_82F00F3C();
            break;

        case 6:
            func_82F00FD8();
            break;

        case 7:
            if (Stage_GetFadeState() == 1) {
                sp1C = 0;
            }
            break;
    }
    return sp1C;
}

void func_82F01180(void) {
    Stage_FadeIn(0x10);
    ResultScreen_SetAnimation(0x10);
    MenuInput_SetController(gPlayer1Controller);

    gPollControllerFlag = 1;

    do {
        if (gPollControllerFlag != 0) {
            PollControllerInputs();
        }
        UpdateTextBox();
        UpdateMenuStateMachine();
        Picker_Update();
        func_82F0C254();
        MenuPanel_Update();
        RenderFragment41Frame();
        gFragment41FrameCounter++;
    } while (func_82F0109C() != 0);
}

s32 func_82F01234(s32 arg0, s32 arg1) {
    Stage* sp24;

    main_pool_push_state('PMEX');

    Gfx_InitBuffers(0x14000, 0);
    sp24 = Stage_Create(1, 0, 2, 0, 2, 1);
    gFragment41TextObject = Text_Init(0x1E, 0);

    ASSET_LOAD(D_1000000, common_menu1_ui, 0);
    ASSET_LOAD(D_3000000, trade_select_ui, 0);

    FRAGMENT_LOAD(fragment31);

    AssetManager_LoadArchives();
    SpriteAssets_Load();
    InitFragment41();
    Stage_Set(sp24);
    func_82F01180();
    Stage_AdvanceN(2);
    Stage_Destroy();
    FontManager_Free();
    Gfx_FreeBuffers();

    main_pool_pop_state('PMEX');

    return 0;
}
