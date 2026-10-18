#include "fragment29.h"
#include "src/1CF30.h"
#include "src/232C0.h"
#include "src/2D340.h"
#include "src/2E110.h"
#include "src/2E460.h"
#include "src/49790.h"
#include "src/memmap.h"
#include "src/memory.h"

s32 Dialog_HandleInput(unk_func_889000C4*, Controller*);
void Dialog_CreateOptionPanel(unk_func_889000C4_044*, char**, unk_func_889000C4*, MemoryPool*);
void DialogOption_SetState(unk_func_889000C4_044*, s32);
void DialogOption_Enable(unk_func_889000C4_044*);
void DialogOption_Reset(unk_func_889000C4_044*);

typedef struct unk_D_88901178 {
    /* 0x00 */ u16 unk_00;
    /* 0x00 */ s32 unk_04;
} unk_D_88901178; // size = 0x8

static Color_RGBA8 gDialogTextColors[] = { { 0xF0, 0xF0, 0xF0, 0xFF }, { 0xF0, 0xF0, 0xF0, 0x4D } };

static unk_D_88901178 gDialogMessageTable[] = {
    {
        0x0003,
        0x00000008,
    },
    {
        0x0004,
        0x00000008,
    },
    {
        0x0005,
        0x00000008,
    },
    {
        0x0000,
        0x00000008,
    },
    {
        0x0001,
        0x00000008,
    },
    {
        0x0002,
        0x00000010,
    },
};

static Color_RGBA8 gDialogBgColorPrimary = { 0x64, 0x96, 0xB4, 0xFF };
static Color_RGBA8 gDialogBgColorSecondary = { 0x3C, 0x64, 0x78, 0xFF };
static Color_RGBA8 D_889011B0 = { 0xFF, 0xFF, 0xFF, 0xFF };
static Color_RGBA8 D_889011B4 = { 0xFF, 0xB2, 0xB2, 0xFF };
static Color_RGBA8 D_889011B8 = { 0x64, 0x1E, 0x1E, 0xFF };
static Color_RGBA8 D_889011BC = { 0x29, 0x3C, 0x67, 0xFF };
static Color_RGBA8 D_889011C0 = { 0x74, 0x87, 0xB2, 0xFF };
static Color_RGBA8 D_889011C4 = { 0x58, 0x08, 0x00, 0xFF };
static Color_RGBA8 D_889011C8 = { 0xFF, 0xFF, 0xFF, 0xFF };
static Color_RGBA8 D_889011CC = { 0xFF, 0xF1, 0x78, 0xFF };
static char D_889011D0[] = "";
static char D_889011D4[] = "";

void Dialog_DrawTextLine(s32 arg0, s32 arg1, char* arg2, UNUSED s32 arg3, s32 arg4, UNUSED unk_func_88200FA0_030_030* arg5) {
    Color_RGBA8 sp24;
    UNUSED s32 pad;
    s32 var_v0 = (arg4 & 4) ? 1 : 0;

    sp24 = gDialogTextColors[var_v0];

    Text_ResetState();
    Text_SetEnvColor(sp24.r, sp24.g, sp24.b, sp24.a);
    Text_SetFont(8, 0);
    Text_Print(arg0 + 8, arg1 + 4, arg2);
    Text_SetupDL();
}

void Dialog_Create(unk_func_889000C4* arg0, s32 arg1, unk_func_88001300_038* arg2, unk_func_88001300_000* arg3,
                   char** arg4, MemoryPool* arg5) {
    UNUSED s32 pad[3];
    s32 i;
    s32 sp7C;
    s32 temp_v0;
    s32 var_s1;
    unk_func_8850B254* temp_s0;
    unk_func_8850878C* temp_s0_2;
    unk_func_8850878C* temp_s0_3;
    unk_func_8850878C* temp_s0_4;
    char* sp60;
    unk_func_885012A4* temp_s0_5;
    unk_func_88503298* temp_s0_6;

    var_s1 = 0;
    for (i = 0; i < 6; i++) {
        temp_v0 = MeasureTextWidth(gDialogMessageTable[i].unk_04, 0, GetMessageString(NULL, 0, arg4, gDialogMessageTable[i].unk_00));
        if (var_s1 < temp_v0) {
            var_s1 = temp_v0;
        }
    }
    var_s1 += 0x10;

    PtrList_Init(&arg0->unk_34, 3, arg5);
    PtrList_Insert(&arg0->unk_34, GetMessageString(NULL, 0, arg4, 3), 0);
    PtrList_Insert(&arg0->unk_34, GetMessageString(NULL, 0, arg4, 4), 1);
    if (arg1 == 0) {
        PtrList_Insert(&arg0->unk_34, GetMessageString(NULL, 0, arg4, 5), 2);
    }
    sp7C = (arg0->unk_34.unk_08 * 0x1C) + 0x38;
    ((func885007CC)Memmap_GetFragmentVaddr(func_885007CC))(&arg0->unk_00, sizeof(unk_func_889000C4));
    arg0->unk_00.unk_20 = Dialog_HandleInput;
    if (arg2 != NULL) {
        arg0->unk_00.unk_10.unk_00 = (arg2->unk_00.unk_14.unk_00 - var_s1) / 2;
        arg0->unk_00.unk_10.unk_02 = (arg2->unk_00.unk_14.unk_02 - sp7C) / 2;
    }
    arg0->unk_00.unk_14.unk_00 = var_s1;
    arg0->unk_00.unk_14.unk_02 = sp7C;

    arg0->unk_2C = mem_pool_alloc(arg5, sizeof(unk_func_889000C4_02C));
    ((func88502274)Memmap_GetFragmentVaddr(Fragment_SetRect))(&arg0->unk_2C->unk_00, 0, 0, var_s1, sp7C);
    arg0->unk_2C->unk_00.unk_28 |= 0x200;
    arg0->unk_2C->unk_00.unk_28 |= 0x400;
    arg0->unk_2C->unk_00.unk_28 &= ~1;
    ((func8850068C)Memmap_GetFragmentVaddr(Fragment_SetChild))(&arg0->unk_00.unk_00, &arg0->unk_2C->unk_00.unk_00);

    temp_s0 = mem_pool_alloc(arg5, sizeof(unk_func_8850B254));
    ((func8850B254)Memmap_GetFragmentVaddr(UIList_Create))(temp_s0, 0, 0, var_s1, 0x2C, gDialogBgColorPrimary, gDialogBgColorSecondary);
    ((func8850068C)Memmap_GetFragmentVaddr(Fragment_SetChild))(&arg0->unk_2C->unk_00.unk_00, &temp_s0->unk_00.unk_00);

    arg0->unk_40 = mem_pool_alloc(arg5, sizeof(unk_func_88500994));
    ((func88500994)Memmap_GetFragmentVaddr(func_88500994))(arg0->unk_40, 0, 0);
    ((func8850068C)Memmap_GetFragmentVaddr(Fragment_SetChild))(&temp_s0->unk_00.unk_00, &arg0->unk_40->unk_00.unk_00);

    temp_s0_2 = mem_pool_alloc(arg5, sizeof(unk_func_8850878C));
    ((func8850878C)Memmap_GetFragmentVaddr(TextObject_Create))(temp_s0_2, 8, 0, GetMessageString(NULL, 0, arg4, 0), 8);
    temp_s0_2->unk_3C = 0x18;
    ((func88500A3C)Memmap_GetFragmentVaddr(Fragment_AddToParent))(arg0->unk_40, &temp_s0_2->unk_00);

    temp_s0_3 = mem_pool_alloc(arg5, sizeof(unk_func_8850878C));
    ((func8850878C)Memmap_GetFragmentVaddr(TextObject_Create))(temp_s0_3, 8, 0, GetMessageString(NULL, 0, arg4, 1), 8);
    temp_s0_3->unk_3C = 0x18;
    ((func88500A3C)Memmap_GetFragmentVaddr(Fragment_AddToParent))(arg0->unk_40, &temp_s0_3->unk_00);

    temp_s0_4 = mem_pool_alloc(arg5, sizeof(unk_func_8850878C));
    sp60 = GetMessageString(NULL, 0, arg4, 2);
    ((func8850878C)Memmap_GetFragmentVaddr(TextObject_Create))(temp_s0_4, (var_s1 - MeasureTextWidth(0x10, 0, sp60)) / 2, 0xA,
                                                           sp60, 0x10);
    temp_s0_4->unk_30 = (0, D_889011B0);
    temp_s0_4->unk_44 = temp_s0_4->unk_44;
    temp_s0_4->unk_34 = (0, D_889011B4);
    temp_s0_4->unk_44 = 1;
    ((func88500A3C)Memmap_GetFragmentVaddr(Fragment_AddToParent))(arg0->unk_40, &temp_s0_4->unk_00);

    temp_s0_5 = mem_pool_alloc(arg5, sizeof(unk_func_885012A4));
    ((func885012A4)Memmap_GetFragmentVaddr(UIFrame_Create))(temp_s0_5, 0, 0x30, var_s1, sp7C - 0x30, D_889011B8);
    ((func8850068C)Memmap_GetFragmentVaddr(Fragment_SetChild))(&arg0->unk_2C->unk_00.unk_00, &temp_s0_5->unk_00.unk_00);

    arg0->unk_30 = mem_pool_alloc(arg5, sizeof(unk_func_88200FA0_030_030));
    ((func885060BC)Memmap_GetFragmentVaddr(UIButton_Create))(arg0->unk_30, 0, 4, Dialog_DrawTextLine, var_s1, 0x1C,
                                                           arg0->unk_34.unk_08, 1, arg5);
    ((func88506384)Memmap_GetFragmentVaddr(List_SetItems))(arg0->unk_30, &arg0->unk_34, arg5);
    ((func8850068C)Memmap_GetFragmentVaddr(Fragment_SetChild))(&temp_s0_5->unk_00.unk_00, &arg0->unk_30->unk_00.unk_00);

    if (arg3 != NULL) {
        temp_s0_6 = mem_pool_alloc(arg5, sizeof(unk_func_88503298));
        ((func88503298)Memmap_GetFragmentVaddr(Dialog_SetParent))(temp_s0_6, arg0->unk_2C, arg3);
        ((func8850068C)Memmap_GetFragmentVaddr(Fragment_SetChild))(&arg0->unk_00.unk_00, &temp_s0_6->unk_00.unk_00);
    }

    arg0->unk_44 = mem_pool_alloc(arg5, sizeof(unk_func_889000C4_044));
    Dialog_CreateOptionPanel(arg0->unk_44, arg4, arg0, arg5);
    ((func8850068C)Memmap_GetFragmentVaddr(Fragment_SetChild))(&arg0->unk_00.unk_00, &arg0->unk_44->unk_00.unk_00);
}

void Dialog_SetEnabled(unk_func_889000C4* arg0, s32 arg1) {
    if (arg1 != 0) {
        ((func88500A6C)Memmap_GetFragmentVaddr(UIContainer_SetChildCount))(arg0->unk_40, 1);
        arg0->unk_30->unk_34[0] |= 4;
        ((func88506BFC)Memmap_GetFragmentVaddr(Fragment_Refresh))(arg0->unk_30, 2);
    } else {
        ((func88500A6C)Memmap_GetFragmentVaddr(UIContainer_SetChildCount))(arg0->unk_40, 0);
        arg0->unk_30->unk_34[0] = 0;
        ((func88506BFC)Memmap_GetFragmentVaddr(Fragment_Refresh))(arg0->unk_30, 0);
    }
    arg0->unk_00.unk_24(&arg0->unk_00, 1);
    ((func88502C98)Memmap_GetFragmentVaddr(UIAnimatedElement_WaitForInput))(arg0->unk_2C);
}

void Dialog_SetCloseState(unk_func_889000C4* arg0) {
    arg0->unk_2C->unk_2C = 0xB;
}

s32 Dialog_HandleInput(unk_func_889000C4* arg0, Controller* arg1) {
    s32 var_v1;

    if (arg0->unk_2C->unk_30 & 2) {
        var_v1 = arg0->unk_30->unk_00.unk_20(&arg0->unk_30->unk_00, arg1);
    } else {
        var_v1 = 1;
    }
    return var_v1;
}

s32 Dialog_WaitForSelection(unk_func_889000C4* arg0, Controller* arg1, s32 arg2) {
    s32 temp_v0;
    u32 var_s0 = 0;

    while (var_s0 == 0) {
        ControllerMsgQueue_SendAndRead(var_s0);
        temp_v0 = arg0->unk_00.unk_20(&arg0->unk_00, arg1);
        if (!(temp_v0 & 1)) {
            if (arg1->buttonPressed & 0x4000) {
                if (arg0->unk_30->unk_2C->unk_08 == 3) {
                    var_s0 = 3;
                    PlaySoundEffect(var_s0);
                }
            } else if (arg1->buttonPressed & 0x8000) {
                if (arg2 != 0) {
                    switch (arg0->unk_30->unk_38) {
                        case 0:
                            PlaySoundEffect(0x1D);
                            break;

                        case 1:
                            PlaySoundEffect(0x21);
                            break;

                        case 2:
                            PlaySoundEffect(3);
                            break;
                    }
                }
                var_s0 = arg0->unk_30->unk_38 + 1;
            }
        }
        ((func8850BC94)Memmap_GetFragmentVaddr(Fragment_HandleResult))(temp_v0);
    }
    return var_s0 - 1;
}

void Dialog_Run(unk_func_889000C4* arg0, s32 arg1) {
    s32 var_s0;
    s32 temp_v0;
    s32 var_s7 = 0;

    func_8002447C(arg1);

    while (func_800243D8(arg1) == 0) {
        if (var_s7 == 0) {
            DialogOption_Enable(arg0->unk_44);
            var_s7 = 1;
        }
        DialogOption_SetState(arg0->unk_44, 2);

        var_s0 = 2;
        temp_v0 = 0;
        while (temp_v0 != 2) {
            temp_v0 = func_80023E34(arg1);
            switch (temp_v0) {
                case 1:
                    var_s0 = 1;
                    break;

                case 2:
                    var_s0 = 0;
                    break;

                case 3:
                    var_s0 = 3;
                    break;
            }

            DialogOption_SetState(arg0->unk_44, var_s0);
            ControllerMsgQueue_Flush();
            ControllerMsgQueue_Flush();
        }
    }

    if (var_s7 != 0) {
        DialogOption_Reset(arg0->unk_44);
    }
    func_800244F4(arg1);
}

void Dialog_CreateOptionPanel(unk_func_889000C4_044* arg0, char** arg1, unk_func_889000C4* arg2, MemoryPool* arg3) {
    UNUSED s32 pad[2];
    s32 sp54;
    unk_func_885012A4* sp50;
    unk_func_8850878C* sp4C;
    unk_func_8850878C* sp48;
    unk_func_8850878C* sp44;
    unk_func_8850878C* sp40;

    ((func885007CC)Memmap_GetFragmentVaddr(func_885007CC))(&arg0->unk_00, sizeof(unk_func_889000C4_044));
    arg0->unk_00.unk_10.unk_00 = (arg2->unk_00.unk_14.unk_00 - 0x1A0) / 2;
    arg0->unk_00.unk_10.unk_02 = (arg2->unk_00.unk_14.unk_02 - 0x108) / 2;

    arg0->unk_2C = mem_pool_alloc(arg3, sizeof(unk_func_889000C4_044_02C));
    ((func88502274)Memmap_GetFragmentVaddr(Fragment_SetRect))(arg0->unk_2C, 0, 0, 0x1A0, 0x108);
    arg0->unk_2C->unk_00.unk_28 |= 0x200;
    arg0->unk_2C->unk_00.unk_28 |= 0x400;
    arg0->unk_2C->unk_00.unk_28 &= ~1;
    ((func8850068C)Memmap_GetFragmentVaddr(Fragment_SetChild))(&arg0->unk_00.unk_00, &arg0->unk_2C->unk_00.unk_00);

    sp50 = mem_pool_alloc(arg3, sizeof(unk_func_885012A4));
    ((func885012A4)Memmap_GetFragmentVaddr(UIFrame_Create))(sp50, 0, 0, 0x1A0, 0x108, D_889011C4);
    ((func8850068C)Memmap_GetFragmentVaddr(Fragment_SetChild))(&arg0->unk_2C->unk_00.unk_00, &sp50->unk_00.unk_00);

    arg0->unk_30 = mem_pool_alloc(arg3, sizeof(unk_func_88500994));
    ((func88500994)Memmap_GetFragmentVaddr(func_88500994))(arg0->unk_30, 0, 0);
    ((func8850068C)Memmap_GetFragmentVaddr(Fragment_SetChild))(&sp50->unk_00.unk_00, &arg0->unk_30->unk_00.unk_00);

    sp4C = mem_pool_alloc(arg3, sizeof(unk_func_8850878C));
    sp54 = MeasureTextWidth(0x10, 0, GetMessageString(NULL, 0, arg1, 6));
    ((func8850878C)Memmap_GetFragmentVaddr(TextObject_Create))(sp4C, (0x1A0 - sp54) / 2, 0x30,
                                                           GetMessageString(NULL, 0, arg1, 6), 0x10);
    sp4C->unk_30 = (0, D_889011C8);
    sp4C->unk_44 = sp4C->unk_44;
    sp4C->unk_34 = (0, D_889011CC);
    sp4C->unk_44 = 1;
    ((func88500A3C)Memmap_GetFragmentVaddr(Fragment_AddToParent))(arg0->unk_30, &sp4C->unk_00);

    sp48 = mem_pool_alloc(arg3, sizeof(unk_func_8850878C));
    ((func8850878C)Memmap_GetFragmentVaddr(TextObject_Create))(sp48, 0, 0x30, D_889011D0, 0x10);
    sp48->unk_30 = (0, D_889011C8);
    sp48->unk_44 = sp48->unk_44;
    sp48->unk_34 = (0, D_889011CC);
    sp48->unk_44 = 1;
    ((func88500A3C)Memmap_GetFragmentVaddr(Fragment_AddToParent))(arg0->unk_30, &sp48->unk_00);

    sp44 = mem_pool_alloc(arg3, sizeof(unk_func_8850878C));
    sp54 = MeasureTextWidth(0x10, 0, GetMessageString(NULL, 0, arg1, 7));
    ((func8850878C)Memmap_GetFragmentVaddr(TextObject_Create))(sp44, (0x1A0 - sp54) / 2, 0x30,
                                                           GetMessageString(NULL, 0, arg1, 7), 0x10);
    sp44->unk_30 = (0, D_889011C8);
    sp44->unk_44 = sp44->unk_44;
    sp44->unk_34 = (0, D_889011CC);
    sp44->unk_44 = 1;
    ((func88500A3C)Memmap_GetFragmentVaddr(Fragment_AddToParent))(arg0->unk_30, &sp44->unk_00);

    sp40 = mem_pool_alloc(arg3, sizeof(unk_func_8850878C));
    sp54 = MeasureTextWidth(0x10, 0, GetMessageString(NULL, 0, arg1, 8));
    ((func8850878C)Memmap_GetFragmentVaddr(TextObject_Create))(sp40, (0x1A0 - sp54) / 2, 0xC,
                                                           GetMessageString(NULL, 0, arg1, 8), 0x10);
    sp40->unk_3C = 0x1C;
    sp40->unk_30 = (0, D_889011C8);
    sp40->unk_44 = sp40->unk_44;
    sp40->unk_34 = (0, D_889011CC);
    sp40->unk_44 = 1;
    ((func88500A3C)Memmap_GetFragmentVaddr(Fragment_AddToParent))(arg0->unk_30, &sp40->unk_00);
    sp54 = MeasureTextWidth(0x10, 0, GetMessageString(NULL, 0, arg1, 9));

    arg0->unk_34 = mem_pool_alloc(arg3, sizeof(unk_func_8850878C));
    ((func8850878C)Memmap_GetFragmentVaddr(TextObject_Create))(arg0->unk_34, (0x1A0 - sp54) / 2, 0x78,
                                                           GetMessageString(NULL, 0, arg1, 9), 0x10);
    arg0->unk_34->unk_3C = 0x24;
    ((func8850068C)Memmap_GetFragmentVaddr(Fragment_SetChild))(&arg0->unk_2C->unk_00.unk_00, &arg0->unk_34->unk_00.unk_00);

    arg0->unk_38 = mem_pool_alloc(arg3, sizeof(unk_func_8850878C));
    ((func8850878C)Memmap_GetFragmentVaddr(TextObject_Create))(arg0->unk_38, 0xC, 0x78, D_889011D4, 0x10);
    arg0->unk_38->unk_3C = 0x24;
    ((func8850068C)Memmap_GetFragmentVaddr(Fragment_SetChild))(&arg0->unk_2C->unk_00.unk_00, &arg0->unk_38->unk_00.unk_00);
}

void DialogOption_Enable(unk_func_889000C4_044* arg0) {
    arg0->unk_2C->unk_00.unk_28 |= 1;
}

void DialogOption_Reset(unk_func_889000C4_044* arg0) {
    arg0->unk_2C->unk_2C = 0xB;
}

void DialogOption_SetState(unk_func_889000C4_044* arg0, s32 arg1) {
    ((func88500A6C)Memmap_GetFragmentVaddr(UIContainer_SetChildCount))(arg0->unk_30, arg1);

    if (arg1 == 0) {
        arg0->unk_34->unk_00.unk_28 &= ~1;
        arg0->unk_38->unk_00.unk_28 &= ~1;
    } else {
        arg0->unk_34->unk_00.unk_28 |= 1;
        arg0->unk_38->unk_00.unk_28 |= 1;
    }
}
