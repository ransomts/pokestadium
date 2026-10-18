#include "fragment23.h"
#include "src/1CF30.h"
#include "src/20330.h"
#include "src/29BA0.h"
#include "src/2D340.h"
#include "src/2E110.h"
#include "src/2E460.h"
#include "src/49790.h"
#include "src/memmap.h"
#include "src/memory.h"
#include "src/stage_loader.h"

static char** gFragment23ItemNameBank;
static char** gFragment23CommonStringBank;

static u16 gFragment23DescriptionStringIds[4] = { 6, 7, 8, 9 };
static Color_RGBA8 gFragment23ButtonColor = { 0xA0, 0x96, 0x64, 0xFF };
static u16 gFragment23OptionStringIds[4] = { 2, 3, 4, 5 };
static Color_RGBA8 gFragment23PanelGradientStart = { 0x64, 0x96, 0xB4, 0xFF };
static Color_RGBA8 gFragment23PanelGradientEnd = { 0x3C, 0x64, 0x78, 0xFF };
static Color_RGBA8 gFragment23ButtonHighlightColor = { 0xA0, 0x96, 0x64, 0xFF };

void CreateInfoPanel(unk_func_88503298* arg0, s32 arg1, s32 arg2, MemoryPool* arg3) {
    s32 i;
    s32 temp_v0;
    s32 var_s1;
    unk_func_885012A4* temp_s0;

    var_s1 = 0;
    for (i = 0; i < 4; i++) {
        temp_v0 = MeasureTextWidth(0x10, 0, GetMessageString(NULL, 0, gFragment23CommonStringBank, gFragment23DescriptionStringIds[i]));
        if (var_s1 < temp_v0) {
            var_s1 = temp_v0;
        }
    }
    var_s1 += 0x10;

    ((func885007CC)Memmap_GetFragmentVaddr(func_885007CC))(arg0, sizeof(unk_func_88503298));
    arg0->unk_00.unk_10.unk_00 = ((0x280 - var_s1) / 2) - arg1;
    arg0->unk_00.unk_10.unk_02 = arg2;

    arg0->unk_2C = mem_pool_alloc(arg3, sizeof(unk_func_88001300_038));
    ((func88502274)Memmap_GetFragmentVaddr(Fragment_SetRect))(arg0->unk_2C, 0, 0, var_s1, 0x68);
    arg0->unk_2C->unk_00.unk_28 |= 0x200;
    arg0->unk_2C->unk_00.unk_28 |= 0x400;
    arg0->unk_2C->unk_00.unk_28 &= ~1;
    ((func8850068C)Memmap_GetFragmentVaddr(Fragment_SetChild))(arg0, arg0->unk_2C);

    temp_s0 = mem_pool_alloc(arg3, sizeof(unk_func_885012A4));
    ((func885012A4)Memmap_GetFragmentVaddr(UIFrame_Create))(temp_s0, 0, 0, var_s1, 0x68, gFragment23ButtonColor);
    ((func8850068C)Memmap_GetFragmentVaddr(Fragment_SetChild))(arg0->unk_2C, temp_s0);

    arg0->unk_30 = mem_pool_alloc(arg3, sizeof(unk_func_8850878C));
    ((func8850878C)Memmap_GetFragmentVaddr(TextObject_Create))(arg0->unk_30, 8, 8, 0, 0x10);
    arg0->unk_30->unk_3C = 0x20;
    ((func8850068C)Memmap_GetFragmentVaddr(Fragment_SetChild))(temp_s0, arg0->unk_30);
}

void InfoPanelSetText(unk_func_88503298* arg0, s8* arg1) {
    arg0->unk_30->unk_40 = arg1;
}

void CommonStringMenuCreate(unk_func_88200FA0_030* arg0, s32 arg1, s32 arg2, unk_func_88001300_000* arg3, MemoryPool* arg4) {
    s32 i;
    s32 j;
    char* temp_s0;
    s32 temp_v0;
    s32 var_s2;
    unk_func_885012A4* temp_s0_2;
    unk_func_8850B254* sp6C;
    UNUSED s32 pad1[3];
    unk_func_88503298* temp_s0_3;
    unk_func_8850878C* temp_s1;

    if ((arg2 <= 0) || (arg2 >= 5)) {
        arg2 = 0;
    } else {
        arg2--;
    }

    var_s2 = MeasureTextWidth(0x10, 0, GetMessageString(NULL, 0, gFragment23CommonStringBank, 1));

    for (j = 0; j < 4; j++) {
        temp_v0 = MeasureTextWidth(0x10, 0, GetMessageString(NULL, 0, gFragment23CommonStringBank, gFragment23OptionStringIds[j]));
        if (var_s2 < temp_v0) {
            var_s2 = temp_v0;
        }
    }
    var_s2 += 0x10;

    ((func885007CC)Memmap_GetFragmentVaddr(func_885007CC))(arg0, sizeof(unk_func_88200FA0_030));
    arg0->unk_00.unk_20 = MenuProcessInput;
    arg0->unk_00.unk_10.unk_00 = (0x280 - var_s2) / 2;
    arg0->unk_00.unk_10.unk_02 = arg1;

    arg0->unk_2C = mem_pool_alloc(arg4, sizeof(unk_func_88001300_038));
    ((func88502274)Memmap_GetFragmentVaddr(Fragment_SetRect))(arg0->unk_2C, 0, 0, var_s2, 0xA4);
    arg0->unk_2C->unk_00.unk_28 |= 0x200;
    arg0->unk_2C->unk_00.unk_28 |= 0x400;
    arg0->unk_2C->unk_00.unk_28 &= ~1;
    ((func8850068C)Memmap_GetFragmentVaddr(Fragment_SetChild))(arg0, arg0->unk_2C);

    sp6C = mem_pool_alloc(arg4, sizeof(unk_func_8850B254));
    ((func8850B254)Memmap_GetFragmentVaddr(UIList_Create))(sp6C, 0, 0, var_s2, 0x18, gFragment23PanelGradientStart, gFragment23PanelGradientEnd);
    ((func8850068C)Memmap_GetFragmentVaddr(Fragment_SetChild))(arg0->unk_2C, sp6C);

    temp_s1 = mem_pool_alloc(arg4, sizeof(unk_func_8850878C));
    temp_s0 = GetMessageString(NULL, 0, gFragment23CommonStringBank, 1);
    ((func8850878C)Memmap_GetFragmentVaddr(TextObject_Create))(temp_s1, (var_s2 - MeasureTextWidth(0x10, 0, temp_s0)) / 2, 0,
                                                           temp_s0, 0x10);
    temp_s1->unk_3C = 0x1C;
    ((func8850068C)Memmap_GetFragmentVaddr(Fragment_SetChild))(sp6C, temp_s1);

    PtrList_Init(&arg0->unk_38, 4, arg4);

    for (i = 0; i < 4; i++) {
        PtrList_Insert(&arg0->unk_38, GetMessageString(NULL, 0, gFragment23CommonStringBank, gFragment23OptionStringIds[i]), i);
    }

    temp_s0_2 = mem_pool_alloc(arg4, sizeof(unk_func_885012A4));
    ((func885012A4)Memmap_GetFragmentVaddr(UIFrame_Create))(temp_s0_2, 0, 0x1C, var_s2, 0x88, gFragment23ButtonHighlightColor);
    ((func8850068C)Memmap_GetFragmentVaddr(Fragment_SetChild))(arg0->unk_2C, temp_s0_2);

    arg0->unk_30 = mem_pool_alloc(arg4, sizeof(unk_func_88200FA0_030_030));
    ((func885060BC)Memmap_GetFragmentVaddr(UIButton_Create))(arg0->unk_30, 0, 4, DrawMenuItemText, var_s2, 0x20, 4, 1, arg4);
    ((func88506384)Memmap_GetFragmentVaddr(List_SetItems))(arg0->unk_30, &arg0->unk_38, arg4);
    ((func88506BFC)Memmap_GetFragmentVaddr(Fragment_Refresh))(arg0->unk_30, arg2);
    ((func8850068C)Memmap_GetFragmentVaddr(Fragment_SetChild))(temp_s0_2, arg0->unk_30);

    arg0->unk_34 = mem_pool_alloc(arg4, sizeof(unk_func_88503298));
    CreateInfoPanel(arg0->unk_34, arg0->unk_00.unk_10.unk_00, 0xB4, arg4);
    ((func8850068C)Memmap_GetFragmentVaddr(Fragment_SetChild))(arg0, arg0->unk_34);
    UpdateDescriptionForSelection(arg0, arg2);

    temp_s0_3 = mem_pool_alloc(arg4, sizeof(unk_func_88503298));
    ((func88503298)Memmap_GetFragmentVaddr(Dialog_SetParent))(temp_s0_3, arg0->unk_2C, arg3);
    ((func8850068C)Memmap_GetFragmentVaddr(Fragment_SetChild))(arg0, temp_s0_3);
}

void UpdateDescriptionForSelection(unk_func_88200FA0_030* arg0, s32 arg1) {
    InfoPanelSetText(arg0->unk_34, GetMessageString(NULL, 0, gFragment23CommonStringBank, arg1 + 6));
}

void DrawMenuItemText(s32 arg0, s32 arg1, char* arg2, s32 arg3) {
    static Color_RGBA8 gFragment23TextColor = { 0xF0, 0xF0, 0xF0, 0xFF };

    Text_ResetState();
    Text_SetEnvColor(gFragment23TextColor.r, gFragment23TextColor.g, gFragment23TextColor.b, gFragment23TextColor.a);
    Text_SetFont(0x10, 0);
    Text_Print(arg0 + 8, arg1 + 4, arg2);
    Text_SetupDL();
}

s32 MenuProcessInput(unk_func_88200FA0_030* arg0, Controller* arg1) {
    s32 sp1C;

    if (arg0->unk_2C->unk_30 & 2) {
        sp1C = arg0->unk_30->unk_00.unk_20(arg0->unk_30, arg1);
        if ((sp1C & 1) && (sp1C & 8)) {
            UpdateDescriptionForSelection(arg0, arg0->unk_30->unk_38);
        }
    } else if (!(arg0->unk_2C->unk_00.unk_28 & 1)) {
        sp1C = 2;
    } else {
        sp1C = 1;
    }
    return sp1C;
}

void MenuActivate(unk_func_88200FA0_030* arg0) {
    arg0->unk_2C->unk_00.unk_28 |= 1;
    arg0->unk_34->unk_2C->unk_00.unk_28 |= 1;
}

void MenuCloseAndWait(unk_func_88200FA0_030* arg0) {
    arg0->unk_2C->unk_2C = 0xB;
    arg0->unk_34->unk_2C->unk_2C = 0xB;
    while (arg0->unk_2C->unk_00.unk_28 & 1) {
        ControllerMsgQueue_SendAndRead(NULL);
    }
}

s32 MenuRunSelectionLoop(unk_func_88200FA0_030* arg0, Controller* arg1) {
    s32 var_s0;
    s32 var_s1 = 0;

    MenuActivate(arg0);

    while (var_s1 == 0) {
        ControllerMsgQueue_SendAndRead(NULL);
        var_s0 = MenuProcessInput(arg0, arg1);
        if (!(var_s0 & 1)) {
            if (arg1->buttonPressed & 0x4000) {
                var_s0 = 0x80000003;
                var_s1 = 1;
            } else if (arg1->buttonPressed & 0x8000) {
                PlaySoundEffect(0x1C);
                var_s0 = 1;
                var_s1 = arg0->unk_30->unk_38 + 2;
            }
        }
        ((func8850BC94)Memmap_GetFragmentVaddr(Fragment_HandleResult))(var_s0);
    }
    MenuCloseAndWait(arg0);
    return var_s1;
}

void ItemInfoScreenCreate(unk_func_88200FA0* arg0, s32 arg1, s32 arg2, s32 arg3, MemoryPool* arg4) {
    static Color_RGBA8 gFragment23BackgroundColorTop = { 0x1E, 0x50, 0x50, 0xFF };
    static Color_RGBA8 gFragment23BackgroundColorBottom = { 0x00, 0x0A, 0x0A, 0xFF };

    unk_func_88001300_000* sp4C;
    unk_func_88500EE4* sp48;
    unk_func_88509A2C* sp44;
    unk_func_88509E34* sp40;

    ((func885007CC)Memmap_GetFragmentVaddr(func_885007CC))(arg0, 0x34);
    arg0->unk_00.unk_10.unk_00 = arg1;
    arg0->unk_00.unk_10.unk_02 = arg2;

    sp4C = mem_pool_alloc(arg4, sizeof(unk_func_88001300_000));
    ((func885031E8)Memmap_GetFragmentVaddr(UIElementBase_Create))(sp4C, 0, 0, 0x280, 0x1E0);
    ((func8850068C)Memmap_GetFragmentVaddr(Fragment_SetChild))(arg0, sp4C);

    sp48 = mem_pool_alloc(arg4, sizeof(unk_func_88500EE4));
    ((func88500EE4)Memmap_GetFragmentVaddr(UIColoredTextureRect_Create))(sp48, 0, 0, 0x280, 0x1E0, gPcBackdropTile, gFragment23BackgroundColorTop,
                                                           gFragment23BackgroundColorBottom);
    ((func8850068C)Memmap_GetFragmentVaddr(Fragment_SetChild))(sp4C, sp48);

    arg0->unk_2C = mem_pool_alloc(arg4, sizeof(unk_func_885088F4));
    ((func885088F4)Memmap_GetFragmentVaddr(ProgressBarFragment_Create))(arg0->unk_2C, 0x41, 0x15C, 0xDC);
    if (Stage_GetFadeState() == 0) {
        arg0->unk_2C->unk_2C = 5;
    }
    ((func8850068C)Memmap_GetFragmentVaddr(Fragment_SetChild))(sp4C, arg0->unk_2C);

    sp44 = mem_pool_alloc(arg4, sizeof(unk_func_88509A2C));
    ((func88509A2C)Memmap_GetFragmentVaddr(TrainerMoveInfoFragment_Create))(sp44, 0x38, 0x22, GetCurrentPokemonBank(),
                                                           GetMessageString(NULL, 0, gFragment23ItemNameBank, 0));
    ((func8850068C)Memmap_GetFragmentVaddr(Fragment_SetChild))(arg0->unk_2C, sp44);

    sp40 = mem_pool_alloc(arg4, sizeof(unk_func_88509E34));
    ((func88509E34)Memmap_GetFragmentVaddr(LabelFragment_Create))(sp40, 0, 0, GetMessageString(NULL, 0, gFragment23CommonStringBank, 0));
    ((func8850068C)Memmap_GetFragmentVaddr(Fragment_SetChild))(arg0->unk_2C, sp40);

    arg0->unk_30 = mem_pool_alloc(arg4, sizeof(unk_func_88200FA0_030));
    CommonStringMenuCreate(arg0->unk_30, 0x78, arg3, sp4C, arg4);
    ((func8850068C)Memmap_GetFragmentVaddr(Fragment_SetChild))(arg0, arg0->unk_30);

    arg0->unk_00.unk_24(&arg0->unk_00, 1);
}

s32 ScreenMessageLoopRun(unk_func_88200FA0* arg0) {
    s32 sp34 = 0;

    while (sp34 == 0) {
        Stage_BeginDisplayList();
        ((func885008C4)Memmap_GetFragmentVaddr(TextObject_Render))(arg0);
        ((func88500828)Memmap_GetFragmentVaddr(TextObject_PostRender))(arg0, 0, 0);
        Stage_Advance();
        ControllerMsgQueue_Recv(&sp34);
    }
    return sp34;
}

void Fragment23ThreadMain(unk_func_88200FA0* arg0) {
    s32 sp24;
    s32 i;

    while (Stage_GetFadeState() != 0) {
        ControllerMsgQueue_SendAndRead(NULL);
    }

    MenuInput_SetController(gPlayer1Controller);

    sp24 = MenuRunSelectionLoop(arg0->unk_30, gPlayer1Controller);
    if (sp24 == 1) {
        arg0->unk_2C->unk_2C = 9;
        Stage_FadeOut(8);

        i = 10;
        while (i-- > 0) {
            ControllerMsgQueue_SendAndRead(NULL);
        }
    }
    ControllerMsgQueue_SendAndRead(sp24);

    osStopThread(NULL);
}

s32 Fragment23_GetNextState(s32 arg0, UNUSED s32 arg1) {
    MemoryPool* sp34;
    void* sp30;
    u8* sp2C;
    TextObjectThreadData* sp28;
    UNUSED s32 pad;
    s32 sp20;

    main_pool_push_state('SLTM');

    sp2C = main_pool_alloc(0x1000, 0);
    sp34 = mem_pool_try_init(0x8000, 0);

    MessageBank_Init();
    gFragment23ItemNameBank = GetMessageBank(0x2A);
    gFragment23CommonStringBank = GetMessageBank(1);

    sp30 = mem_pool_alloc(sp34, sizeof(unk_func_88200FA0));
    ItemInfoScreenCreate(sp30, 0, 0, arg0, sp34);

    sp28 = ALIGN16((u32)mem_pool_alloc(sp34, sizeof(TextObjectThreadData)));
    osCreateThread(&sp28->thread, 0x32, Fragment23ThreadMain, sp30, sp2C + 0x1000, osGetThreadPri(NULL) - 1);

    ControllerMsgQueue_Init();
    MenuInput_SetController(gPlayer1Controller);

    osStartThread(&sp28->thread);

    Stage_FadeIn(8);
    sp20 = ScreenMessageLoopRun(sp30);

    osDestroyThread(&sp28->thread);

    main_pool_pop_state('SLTM');

    if (sp20 == 1) {
        FRAGMENT_LOAD_AND_CALL2(fragment22, 1, 0);
        return 0;
    }

    if (sp20 == 5) {
        FRAGMENT_LOAD_AND_CALL2(fragment24, 1, 0);
        return 0;
    }

    return sp20 - 1;
}
