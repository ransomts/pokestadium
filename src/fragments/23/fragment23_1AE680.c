#include "fragment23.h"
#include "src/12D80.h"
#include "src/1AB70.h"
#include "src/1CF30.h"
#include "src/20330.h"
#include "src/26820.h"
#include "src/29BA0.h"
#include "src/2D340.h"
#include "src/2E110.h"
#include "src/3FB0.h"
#include "src/49790.h"
#include "src/hal_libc.h"
#include "src/fragments/25/fragment25.h"
#include "src/fragments/26/fragment26.h"
#include "src/memmap.h"
#include "src/memory.h"
#include "src/stage_loader.h"
#include "src/232C0.h"

typedef void (*ThreadEntries)(TextObjectContext*);

typedef struct unk_D_88217D10 {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ u8 unk_08[4];
} unk_D_88217D10; // size = 0xC

typedef struct MoveIconInfoEntry {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ u8* unk_10;
} MoveIconInfoEntry; // size = 0x14

typedef struct UIComponentInfoEntry {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ u8* unk_08;
    /* 0x0C */ s16 unk_0C;
    /* 0x0E */ s16 unk_0E;
    /* 0x10 */ Color_RGBA8* unk_10;
    /* 0x14 */ s32 unk_14;
    /* 0x18 */ u16 unk_18;
} UIComponentInfoEntry; // size = 0x1C

typedef struct unk_func_8820634C_arg2_unk0 {
    /* 0x00 */ char pad00[0x8];
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
} unk_func_8820634C_arg2_unk0;

typedef struct unk_func_8820634C_arg2 {
    /* 0x00 */ unk_func_8820634C_arg2_unk0* unk_00;
    /* 0x00 */ char pad04[0x4];
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
} unk_func_8820634C_arg2; // size = 0x54

void TextObject_WaitForClose(TextObjectContext*);
void TextObject_FadeInOutAndClose(TextObjectContext*);
void MenuDualList_UpdateSublists(unk_func_8820B12C_02C*);
s32 UIState_Update(TextObjectRenderer*);
void MenuDualList_SetState(unk_func_8820B12C_02C*, s32);
void MenuDualList_SetMode(unk_func_8820B12C_02C*, s32);
s32 MenuDualList_ProcessInput(unk_func_8820B12C_02C*, Controller*);
s32 UI_HandleInput(TextObjectRenderer*, Controller*);
void UI_SetState(TextObjectRenderer*, s32);
void UIComponent_SetCallback(unk_func_8820B12C*, TextObjectRenderer*);
s32 MainScreen_HandleInput(unk_func_8820B12C*, Controller*);
void LevelLabelFragment_SetData(unk_func_882079D8* arg0, unk_func_88205880_00D0* arg1);
s32 LevelLabelFragment_DrawIfData(unk_func_882079D8*, s32, s32);
s32 MenuList_ProcessInput(unk_func_8820BE14_02C_078*, Controller*);
s32 MoveTargetSelector_Draw(unk_func_88208C5C*, s32, s32);
void func_88209A88(unk_func_8820BE14_02C_070* arg0, unk_func_88205880_00D0* arg1);
s32 RenderMoveInfoPanel(unk_func_8820BE14_02C_070*, s32, s32);

static char** gMessageBank_2A;
static char** gMessageBank_2;
static char** gMessageBank_24;
static char** gMessageBank_25;

static unk_D_88217D10 gMonInitTable[2][9] = {
    {
        { 1, 0x87, 0x21, 0x2D, 0, 0 },
        { 4, 0x87, 0xA, 0x2D, 0, 0 },
        { 7, 0x87, 0x21, 0x27, 0, 0 },
        { 0x6A, 0x1F40, 0x18, 0x60, 0, 0 },
        { 0x6B, 0x1F40, 4, 0x61, 0, 0 },
        { 0x85, 0x3D09, 0x21, 0x1C, 0, 0 },
        { 0x8A, 0x1F40, 0x37, 0x6E, 0, 0 },
        { 0x8C, 0x1F40, 0xA, 0x6A, 0, 0 },
        { 0x36, 0xD2F, 0xA, 0x85, 0, 0 },
    },
    {
        { 1, 0x87, 0x21, 0x2D, 0, 0 },
        { 4, 0x87, 0xA, 0x2D, 0, 0 },
        { 7, 0x87, 0x21, 0x27, 0, 0 },
        { 0x6A, 0x1F40, 0x18, 0x60, 0, 0 },
        { 0x6B, 0x1F40, 4, 0x61, 0, 0 },
        { 0x85, 0x3D09, 0x21, 0x27, 0, 0 },
        { 0x8A, 0x1F40, 0x37, 0x6E, 0, 0 },
        { 0x8C, 0x1F40, 0xA, 0x6A, 0, 0 },
        { 0x36, 0xD2F, 0xA, 0x85, 0, 0 },
    },
};

void InitMonData(PokemonData* arg0) {
    s32 i;
    s32 var_a2;
    unk_D_88217D10* var_v0;
    unk_D_88217D10* temp_a1;
    s32 var_a2_copy;
    s32 j;

    bzero(arg0, sizeof(PokemonData));

    arg0->unk_00.unk_00 = func_8002816C() & 0xFF;
    var_a2 = MenuItem_GetHeldItemId(func_80029080());
    i = 0;
    if (var_a2 == 7) {
        var_a2 = 1;
    } else {
        var_a2 = 0;
    }

    var_v0 = temp_a1 = gMonInitTable[var_a2];
    var_a2_copy = var_a2; // fake copy; keeps var_a2 out of v1
    for (; i < 9; i++, var_v0++) {
        if (var_v0->unk_00 == arg0->unk_00.unk_00) {
            break;
        }
    }

    if (i == 9) {
        i = 0;
        var_v0 = gMonInitTable[var_a2_copy];
    }

    arg0->unk_10 = var_v0->unk_04;
    for (j = 0; j < 4; j++) {
        arg0->unk_09[j] = temp_a1[i].unk_08[j];
    }

    arg0->unk_0E = 0x7D0;
    arg0->unk_14 = 0;
    arg0->unk_16 = 0;
    arg0->unk_18 = 0;
    arg0->unk_1A = 0;
    arg0->unk_1C = 0;

    arg0->unk_1E = guRandom() & 0xFFFF;

    arg0->unk_06 = gSpeciesBaseStats[arg0->unk_00.unk_00 - 1].unk_06;
    arg0->unk_07 = gSpeciesBaseStats[arg0->unk_00.unk_00 - 1].unk_07;

    ApplyPPUps(arg0);

    arg0->unk_04 = arg0->unk_24;

    HAL_Strcpy(arg0->unk_30, GetMessageString(NULL, 0, gMessageBank_24, arg0->unk_00.unk_00 - 1));
    HAL_Strcpy(arg0->unk_3B, GetMessageString(NULL, 0, gMessageBank_2, 0x17));

    SetMonNickname(arg0);

    if (func_8002816C() & 0x100) {
        arg0->unk_08 = 0xA8;
    } else {
        arg0->unk_08 = 0xA7;
    }

    arg0->unk_52 = 0;
    arg0->unk_53 = 0;
    arg0->unk_25 = 0;
}

s32 LoadPokemonFromSave(unk_func_882062E4* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 sp1C = 0;
    unk_func_80022C28_ret* sp18;

    sp18 = CreateGbsBlock(arg2, arg3, arg4, 0);
    if (sp18 != NULL) {
        sp1C = GbsBlock_ReadPokemon(arg0, arg1, sp18);
        CommitAndFreeGbsBlock(sp18);
    }
    return sp1C;
}

static Color_RGBA8 gTextColor_WhiteOpaque = { 0xF0, 0xF0, 0xF0, 0xFF };
static Color_RGBA8 gTextColor_WhiteSemiTransparent = { 0xF0, 0xF0, 0xF0, 0x4D };
static Color_RGBA8 gTextColor_YellowOpaque = { 0xF0, 0xF0, 0x00, 0xFF };

const char gFormat_Decimal[] = "%d";
const char gString_SpaceZeroZero[] = " 00";

void MenuEntry_DrawBox(s32 arg0, s32 arg1, unk_func_8820634C_arg2* arg2, s32 arg3, s32 arg4, unk_func_88200FA0_030_030* arg5) {
    static Color_RGBA8 gBoxColor_DarkGrayBlue = { 0x6C, 0x6C, 0x7E, 0xFF };
    Color_RGBA8 sp64;
    s32 pad60[1];
    char* sp5C;
    char sp58[4];
    s32 color;

    sp5C = GetMessageString(0, 0, gMessageBank_2, 0x41);
    gDPPipeSync(gDisplayListHead++);
    gDPSetCycleType(gDisplayListHead++, G_CYC_FILL);
    gDPSetRenderMode(gDisplayListHead++, 0, 0);

    color = GPACK_RGBA5551(gBoxColor_DarkGrayBlue.r, gBoxColor_DarkGrayBlue.g, gBoxColor_DarkGrayBlue.b, 1);
    gDPPipeSync(gDisplayListHead++);
    gDPSetFillColor(gDisplayListHead++, (color << 16) | color);
    gDPFillRectangle(gDisplayListHead++, arg0, arg1, (arg5->unk_3C + arg0) - 1, (arg1 + arg5->unk_3E) - 1);
    Text_ResetState();
    if (arg4 & 0x100) {
        sp64 = *(Color_RGBA8 *)&gTextColor_YellowOpaque;
    } else if (arg4 & 4) {
        sp64 = *(Color_RGBA8 *)&gTextColor_WhiteSemiTransparent;
    } else {
        sp64 = *(Color_RGBA8 *)&gTextColor_WhiteOpaque;
    }
    Text_SetEnvColor(sp64.r, sp64.g, sp64.b, sp64.a);
    Text_SetFont(8, 0);

    Text_Print(arg0 + 8, arg1 + 2, sp5C);
    sprintf(sp58, gFormat_Decimal, (int)arg3 + 1);
    Text_Print(((arg0 + MeasureTextWidth(0, 0, sp5C) + MeasureTextWidth(0, 0, gString_SpaceZeroZero)) - MeasureTextWidth(0, 0, sp58)) + 8, arg1 + 2, sp58);
    Text_SetupDL();
    Cursor_Draw((arg5->unk_3C + arg0) - 0x35, arg1 + 8, arg2->unk_0C, arg2->unk_08, 2);
}


static u8 gLevelOptionMessageIds[] = {
    0x18,
    0x19,
    0x1A,
};
static Color_RGBA8 gTextColor_WhiteOpaque_Alt = { 0xF0, 0xF0, 0xF0, 0xFF };
static Color_RGBA8 gTextColor_WhiteSemiTransparent_Alt = { 0xF0, 0xF0, 0xF0, 0x4D };
static Color_RGBA8 gTextColor_YellowOpaque_Alt = { 0xF0, 0xF0, 0x00, 0xFF };

void MenuOption_DrawBox(s32 arg0, s32 arg1, unk_func_8820634C_arg2* arg2, s32 arg3, s32 arg4, unk_func_88200FA0_030_030* arg5) {
    static Color_RGBA8 D_88217E08 = { 0x6C, 0x6C, 0x7E, 0xFF };
    unk_func_8820634C_arg2_unk0* temp_v0_7;
    Color_RGBA8 sp48;
    u32 color;

    gDPPipeSync(gDisplayListHead++);
    gDPSetCycleType(gDisplayListHead++, G_CYC_FILL);
    gDPSetRenderMode(gDisplayListHead++, 0, 0);

    color = GPACK_RGBA5551(D_88217E08.r, D_88217E08.g, D_88217E08.b, 1);
    gDPPipeSync(gDisplayListHead++);
    gDPSetFillColor(gDisplayListHead++, (color << 16) | color);
    gDPFillRectangle(gDisplayListHead++, arg0, arg1, (arg5->unk_3C + arg0) - 1, (arg1 + arg5->unk_3E) - 1);
    Text_ResetState();
    if (arg4 & 0x100) {
        sp48 = *(Color_RGBA8 *)&gTextColor_YellowOpaque_Alt;
    } else if (arg4 & 4) {
        sp48 = *(Color_RGBA8 *)&gTextColor_WhiteSemiTransparent_Alt;
    } else {
        sp48 = *(Color_RGBA8 *)&gTextColor_WhiteOpaque_Alt;
    }
    Text_SetEnvColor(sp48.r, sp48.g, sp48.b, sp48.a);
    Text_SetFont(8, 0);
    Text_Print(arg0 + 8, arg1 + 4, GetMessageString(0, 0, gMessageBank_2, gLevelOptionMessageIds[arg3]));
    Text_SetupDL();
    if (arg2->unk_08 == 1) {
        temp_v0_7 = arg2->unk_00;
        Cursor_Draw((arg5->unk_3C + arg0) - 0x35, arg1 + 0xA, temp_v0_7->unk_0C, temp_v0_7->unk_08, 2);
    }
}

s32 MenuEntry_ProcessInput(unk_func_8820BE14_02C_078_034* arg0, Controller* arg1) {
    s32 var_v1;

    if (arg0->unk_2C->unk_30 & 2) {
        var_v1 = arg0->unk_30->unk_00.unk_20(arg0->unk_30, arg1);
    } else {
        var_v1 = 1;
    }
    return var_v1;
}

s32 Menu_NavigateAndSelect(unk_func_88001300_034* arg0, Controller* arg1) {
    s32 var_s0;
    s32 var_s1 = 0;

    arg0->unk_00.unk_24(&arg0->unk_00, 1);

    ((func88502C98)Memmap_GetFragmentVaddr(UIAnimatedElement_WaitForInput))(arg0->unk_2C);

    while (var_s1 == 0) {
        ControllerMsgQueue_SendAndRead(var_s1);

        var_s0 = arg0->unk_00.unk_20(arg0, arg1);

        if (!(var_s0 & 1)) {
            if (arg1->buttonPressed & 0x4000) {
                var_s0 = 0x80000003;
                var_s1 = 1;
            } else if (arg1->buttonPressed & 0x8000) {
                var_s0 = 0x80000005;
                var_s1 = 2;
            }
        }

        ((func8850BC94)Memmap_GetFragmentVaddr(Fragment_HandleResult))(var_s0);
    }

    arg0->unk_2C->unk_2C = 0xB;
    return var_s1 - 1;
}

s32 GetMenuEntryWidth(void) {
    s32 tmp;
    s32 sp18;

    sp18 = MeasureTextWidth(8, 0, GetMessageString(NULL, 0, gMessageBank_2, 0x41));
    tmp = MeasureTextWidth(8, 0, " 00");

    return sp18 + tmp + 0x3D;
}

void MenuEntry_Init(unk_func_8820BE14_02C_078_034* arg0, s32 arg1, s32 arg2, MemoryPool* arg3) {
    s32 sp4C = GetMenuEntryWidth() + 0x10;
    UNUSED s32 pad[2];

    ((func885007CC)Memmap_GetFragmentVaddr(func_885007CC))(&arg0->unk_00, sizeof(unk_func_8820BE14_02C_078_034));

    arg0->unk_00.unk_20 = MenuEntry_ProcessInput;
    arg0->unk_00.unk_10.unk_00 = arg1;
    arg0->unk_00.unk_10.unk_02 = arg2;

    arg0->unk_2C = mem_pool_alloc(arg3, sizeof(unk_func_88001300_038));
    ((func88502274)Memmap_GetFragmentVaddr(Fragment_SetRect))(arg0->unk_2C, 0, 0, sp4C, 0x120);

    arg0->unk_2C->unk_00.unk_28 |= 0x200;
    arg0->unk_2C->unk_00.unk_28 |= 0x400;
    arg0->unk_2C->unk_00.unk_28 &= ~1;

    ((func8850068C)Memmap_GetFragmentVaddr(Fragment_SetChild))(arg0, arg0->unk_2C);

    arg0->unk_30 = mem_pool_alloc(arg3, sizeof(unk_func_88200FA0_030_030));
    ((func885060BC)Memmap_GetFragmentVaddr(UIButton_Create))(arg0->unk_30, 0, 0, MenuEntry_DrawBox, sp4C, 0x18, 0xC, 1, arg3);
    ((func88506238)Memmap_GetFragmentVaddr(ScrollableList_SetItemHeight))(arg0->unk_30, 0xC, arg3);
    ((func8850068C)Memmap_GetFragmentVaddr(Fragment_SetChild))(arg0->unk_2C, arg0->unk_30);
}

s32 MenuEntry_CalcMaxWidth(void) {
    static u8 gLevelOptionMessageIds_Local[3] = { 0x18, 0x19, 0x1A };

    s32 i;
    s32 var_v1;
    s32 var_s1 = 0;

    for (i = 0; i < 3; i++) {
        var_v1 = MeasureTextWidth(8, 0, GetMessageString(NULL, 0, gMessageBank_2, gLevelOptionMessageIds_Local[i]));

        if (i == 0) {
            var_v1 += 0x3D;
        }

        if (var_s1 < var_v1) {
            var_s1 = var_v1;
        }
    }

    return var_s1;
}

void MenuList_Init(unk_func_8820BE14_02C_078* arg0, s32 arg1, s32 arg2, s32 arg3, unk_func_8820BE14_06C_000* arg4,
                   s32 arg5, MemoryPool* arg6) {
    UNUSED s32 pad;
    s32 sp48 = MenuEntry_CalcMaxWidth() + 0x10;
    UNUSED s32 pad2;

    ((func885007CC)Memmap_GetFragmentVaddr(func_885007CC))(&arg0->unk_00, sizeof(unk_func_8820BE14_02C_078));

    arg0->unk_00.unk_20 = MenuList_ProcessInput;
    arg0->unk_00.unk_10.unk_00 = ((arg3 - sp48) / 2) + arg1;
    arg0->unk_00.unk_10.unk_02 = arg2;

    arg0->unk_4C = arg5;
    arg0->unk_2C = mem_pool_alloc(arg6, sizeof(unk_func_88001300_038));

    ((func88502274)Memmap_GetFragmentVaddr(Fragment_SetRect))(arg0->unk_2C, 0, 0, sp48, 0x54);
    arg0->unk_2C->unk_00.unk_28 |= 0x200;
    arg0->unk_2C->unk_00.unk_28 |= 0x400;
    arg0->unk_2C->unk_00.unk_28 &= ~1;

    ((func8850068C)Memmap_GetFragmentVaddr(Fragment_SetChild))(&arg0->unk_00, arg0->unk_2C);

    SubList_Init(&arg0->unk_38, arg4, 0x10, 3, 3);

    arg0->unk_30 = mem_pool_alloc(arg6, sizeof(unk_func_88200FA0_030_030));
    ((func885060BC)Memmap_GetFragmentVaddr(UIButton_Create))(arg0->unk_30, 0, 0, MenuOption_DrawBox, sp48, 0x1C, 3, 1, arg6);
    ((func88506404)Memmap_GetFragmentVaddr(List_InitFromData3))(arg0->unk_30, &arg0->unk_38, arg6);
    ((func8850068C)Memmap_GetFragmentVaddr(Fragment_SetChild))(arg0->unk_2C, arg0->unk_30);

    arg0->unk_34 = mem_pool_alloc(arg6, sizeof(unk_func_8820BE14_02C_078_034));
    MenuEntry_Init(arg0->unk_34, 0x9C, 0x1C, arg6);

    ((func8850068C)Memmap_GetFragmentVaddr(Fragment_SetChild))(arg0, arg0->unk_34);

    arg0->unk_48 = 0;
}

u32 Menu_GetStateFlags(unk_func_8820BE14_02C_078* arg0) {
    return ((arg0->unk_30->unk_38 == 0) ? 0 : arg0->unk_34->unk_30->unk_38) | (arg0->unk_30->unk_38 << 0x10);
}

void Menu_SetStateFlags(unk_func_8820BE14_02C_078* arg0, u32 arg1) {
    arg0->unk_50 = arg1 >> 0x10;
    arg0->unk_54 = arg1 & 0xFFFF;

    ((func8850628C)Memmap_GetFragmentVaddr(Fragment_ClearFlags))(arg0->unk_30);
    ((func88506BFC)Memmap_GetFragmentVaddr(Fragment_Refresh))(arg0->unk_30, arg0->unk_50);

    if (arg0->unk_50 == 0) {
        arg0->unk_30->unk_34[arg0->unk_30->unk_38] |= 0x100;
    }
}

void Menu_SetSecondaryFlags(unk_func_8820BE14_02C_078* arg0, u32 arg1) {
    arg0->unk_58 = arg1 >> 0x10;
    arg0->unk_5C = arg1 & 0xFFFF;

    if (arg0->unk_58 == 0) {
        arg0->unk_30->unk_34[arg0->unk_58] |= 4;
    }
}

s32 MenuList_ProcessInput(unk_func_8820BE14_02C_078* arg0, Controller* arg1) {
    s32 var_v1;
    s32 sp20;

    if (arg0->unk_2C->unk_30 & 2) {
        var_v1 = arg0->unk_30->unk_00.unk_20(arg0->unk_30, arg1);

        if (!(var_v1 & 1)) {
            if (arg1->buttonPressed & 0x4000) {
                var_v1 = 0x80000002;
            } else if (arg1->buttonPressed & 0x8000) {
                if (arg0->unk_30->unk_38 == 0) {
                    var_v1 = 0x80000004;
                } else {
                    sp20 = 0;

                    ((func885063B8)Memmap_GetFragmentVaddr(Fragment_SetData))(arg0->unk_34->unk_30,
                                                                           &arg0->unk_38.unk_00[arg0->unk_30->unk_38]);

                    if (arg0->unk_4C != 0) {
                        arg0->unk_34->unk_00.unk_10.unk_00 = -arg0->unk_34->unk_2C->unk_00.unk_14.unk_00;
                    } else {
                        arg0->unk_34->unk_00.unk_10.unk_00 = arg0->unk_2C->unk_00.unk_14.unk_00;
                    }

                    arg0->unk_34->unk_00.unk_10.unk_02 = 8;
                    if (arg0->unk_50 == arg0->unk_30->unk_38) {
                        arg0->unk_34->unk_30->unk_34[arg0->unk_54] |= 0x100;
                        sp20 = arg0->unk_54;
                    }

                    if (arg0->unk_58 == arg0->unk_30->unk_38) {
                        arg0->unk_34->unk_30->unk_34[arg0->unk_5C] |= 4;
                        if ((sp20 == 0) && (arg0->unk_5C == 0)) {
                            sp20 = 1;
                        }
                    }

                    ((func88506BFC)Memmap_GetFragmentVaddr(Fragment_Refresh))(arg0->unk_34->unk_30, sp20);

                    PlaySoundEffect(2);

                    arg0->unk_00.unk_24(&arg0->unk_00, 0x100);

                    if (Menu_NavigateAndSelect(arg0->unk_34, arg1) == 1) {
                        var_v1 = 4;
                    } else {
                        var_v1 = 1;
                    }
                    arg0->unk_00.unk_24(&arg0->unk_00, 1);
                }
            }
        }
    } else {
        var_v1 = 1;
    }
    return var_v1;
}

s32 MenuList_NavigateAndSelect(unk_func_8820BE14_02C_078* arg0, Controller* arg1) {
    s32 var_s0;
    s32 var_s1 = 0;

    arg0->unk_00.unk_24(&arg0->unk_00, 1);

    ((func88502C98)Memmap_GetFragmentVaddr(UIAnimatedElement_WaitForInput))(arg0->unk_2C);

    while (var_s1 == 0) {
        ControllerMsgQueue_SendAndRead(var_s1);

        var_s0 = arg0->unk_00.unk_20(arg0, arg1);
        if (!(var_s0 & 1)) {
            if (var_s0 & 2) {
                var_s0 |= 1;
                var_s1 = 1;
            } else if (var_s0 & 4) {
                var_s0 |= 1;
                var_s1 = 2;
            }
        }

        ((func8850BC94)Memmap_GetFragmentVaddr(Fragment_HandleResult))(var_s0);
    }

    arg0->unk_2C->unk_2C = 0xB;
    return var_s1 - 1;
}

void DrawLevelLabel(unk_func_88205880_00D0* arg0, s32 arg1, s32 arg2, s32 arg3) {
    static Color_RGBA8 gLevelLabelTextColor_White = { 0xF0, 0xF0, 0xF0, 0xFF };
    static Color_RGBA8 gLevelLabelTextColor_Blue = { 0x5A, 0x5A, 0xA6, 0xFF };

    s32 temp_v1;

    Text_ResetState();
    Text_SetEnvColor(gLevelLabelTextColor_White.r, gLevelLabelTextColor_White.g, gLevelLabelTextColor_White.b, gLevelLabelTextColor_White.a);
    Text_SetFont(8, 0);
    Text_Print(arg1 + 0x14, arg2 + 4, arg0->unk_000[0].unk_30);
    Text_SetFont(4, 0);

    temp_v1 = MeasureTextWidth(0, 0, "L100");

    if ((arg0->unk_000[0].unk_00.unk_00 <= 0) || (arg0->unk_000[0].unk_00.unk_00 >= 0x98)) {
        Text_Print(((arg1 + arg3) - temp_v1) - 0x14, arg2 + 8, "L?");
    } else {
        Text_Print(((arg1 + arg3) - temp_v1) - 0x14, arg2 + 8, "L%d", arg0->unk_000[0].unk_24);
    }
    Text_SetupDL();
}

void LevelLabel_DrawBackground(s32 arg0, s32 arg1, unk_func_88205880_00D0* arg2, s32 arg3, s32 arg4, unk_func_88200FA0_030_030* arg5) {
    static Color_RGBA8 gLevelLabelBgColor_DarkBlue = { 0x40, 0x40, 0x74, 0xFF };
    static Color_RGBA8 gLevelLabelBgColors[] = {
        { 0x78, 0x78, 0xF1, 0xFF },
        { 0x5E, 0x5E, 0xBE, 0xFF },
        { 0xFF, 0xCB, 0xDE, 0xFF },
        { 0xFF, 0xBF, 0xD6, 0xFF },
    };
    Color_RGBA8 spD4;
    s32 sp94;
    

    if (arg2 != 0) {
        if (arg4 & 2) {
            spD4 = Color_ScaleRGB(gLevelLabelBgColor_DarkBlue, 1.4f);
        } else {
            spD4 = *(Color_RGBA8 *)&gLevelLabelBgColor_DarkBlue;
        }
        gDPPipeSync(gDisplayListHead++);
        gDPSetCycleType(gDisplayListHead++, G_CYC_FILL);
        gDPSetRenderMode(gDisplayListHead++, 0, 0);
        {
            
            s32 color = GPACK_RGBA5551(spD4.r, spD4.g, spD4.b, 1);
            gDPPipeSync(gDisplayListHead++);
            gDPSetFillColor(gDisplayListHead++, (color << 16) | color);
            gDPFillRectangle(gDisplayListHead++, arg0, arg1 + 1, arg0 + 0xCB, arg1 + 0x1A);
        }
        {
            s32 color = GPACK_RGBA5551(gLevelLabelBgColors[1].r, gLevelLabelBgColors[1].g, gLevelLabelBgColors[1].b, 1);
            gDPPipeSync(gDisplayListHead++);
            gDPSetFillColor(gDisplayListHead++, (color << 16) | color);
            gDPFillRectangle(gDisplayListHead++, arg0, arg1, arg0 + 0xCB, arg1);
        }
        {
            s32 color = GPACK_RGBA5551(gLevelLabelBgColors[1].r, gLevelLabelBgColors[1].g, gLevelLabelBgColors[1].b, 1);
            gDPPipeSync(gDisplayListHead++);
            gDPSetFillColor(gDisplayListHead++, (color << 16) | color);
            gDPFillRectangle(gDisplayListHead++, arg0, arg1 + 0x1B, arg0 + 0xCB, arg1 + 0x1B);
        }
        if (!(arg4 & 0x100)) {
            DrawLevelLabel(arg2, arg0, arg1, arg5->unk_3C);
        }
    } else {
        if (arg4 & 1) {
            spD4 = *(Color_RGBA8 *)&gLevelLabelBgColor_DarkBlue;
            gDPPipeSync(gDisplayListHead++);
            gDPSetCycleType(gDisplayListHead++, G_CYC_FILL);
            gDPSetRenderMode(gDisplayListHead++, 0, 0);
            {
                s32 color = GPACK_RGBA5551(spD4.r, spD4.g, spD4.b, 1);
                gDPPipeSync(gDisplayListHead++);
                gDPSetFillColor(gDisplayListHead++, (color << 16) | color);
                gDPFillRectangle(gDisplayListHead++, arg0, arg1 + 1, arg0 + 0xCB, arg1 + 0x1A);
            }
            {
                s32 color = GPACK_RGBA5551(gLevelLabelBgColors[1].r, gLevelLabelBgColors[1].g, gLevelLabelBgColors[1].b, 1);
                gDPPipeSync(gDisplayListHead++);
                gDPSetFillColor(gDisplayListHead++, (color << 16) | color);
                gDPFillRectangle(gDisplayListHead++, arg0, arg1, arg0 + 0xCB, arg1);
            }
            {
                s32 color = GPACK_RGBA5551(gLevelLabelBgColors[1].r, gLevelLabelBgColors[1].g, gLevelLabelBgColors[1].b, 1);
                gDPPipeSync(gDisplayListHead++);
                gDPSetFillColor(gDisplayListHead++, (color << 16) | color);
                gDPFillRectangle(gDisplayListHead++, arg0, arg1 + 0x1B, arg0 + 0xCB, arg1 + 0x1B);
            }
            return;
        }
        spD4 = Color_ScaleRGB(gLevelLabelBgColor_DarkBlue, 0.8f);
        gDPPipeSync(gDisplayListHead++);
        gDPSetCycleType(gDisplayListHead++, G_CYC_FILL);
        gDPSetRenderMode(gDisplayListHead++, 0, 0);
        {
            s32 color = GPACK_RGBA5551(spD4.r, spD4.g, spD4.b, 1);
            gDPPipeSync(gDisplayListHead++);
            gDPSetFillColor(gDisplayListHead++, (color << 16) | color);
            gDPFillRectangle(gDisplayListHead++, arg0, arg1, arg0 + 0xCB, arg1 + 0x1B);
        }
    }
}


void LevelLabelFragment_Init(unk_func_882079D8* arg0, s32 arg1, s32 arg2, s32 arg3, unk_func_88205880_00D0* arg4) {
    ((func885007CC)Memmap_GetFragmentVaddr(func_885007CC))(&arg0->unk_00, sizeof(unk_func_882079D8));

    arg0->unk_00.unk_18 = LevelLabelFragment_DrawIfData;
    arg0->unk_00.unk_10.unk_00 = arg1;
    arg0->unk_00.unk_10.unk_02 = arg2;
    arg0->unk_00.unk_14.unk_00 = arg3;
    arg0->unk_00.unk_14.unk_02 = 0;

    LevelLabelFragment_SetData(arg0, arg4);
}

void LevelLabelFragment_SetData(unk_func_882079D8* arg0, unk_func_88205880_00D0* arg1) {
    arg0->unk_2C = arg1;
}

s32 LevelLabelFragment_DrawIfData(unk_func_882079D8* arg0, s32 arg1, s32 arg2) {
    if (arg0->unk_2C != NULL) {
        DrawLevelLabel(arg0->unk_2C, arg1, arg2, arg0->unk_00.unk_14.unk_00);
    }
}

void MenuDualList_Init(unk_func_8820B12C_02C* arg0, unk_func_8820B12C_02C_020* arg1, unk_func_8820B12C_02C_020* arg2,
                   unk_func_88217740* arg3, TextObjectGraphics* arg4, s32 arg5, MemoryPool* arg6) {
    static Color_RGBA8 gMenuItemColor_White = { 0xF0, 0xF0, 0xF0, 0xFF };

    s32 i;

    ((func88500668)Memmap_GetFragmentVaddr(ListNode_Init))(arg0, sizeof(unk_func_8820B12C_02C));

    arg0->unk_14 = MenuDualList_SetState;
    arg0->unk_10 = MenuDualList_ProcessInput;
    arg0->unk_18 = 0;
    arg0->unk_1C = 0;
    arg0->unk_20[0] = arg1;
    arg0->unk_20[1] = arg2;
    arg0->unk_34 = 1;
    arg0->unk_38 = arg3;
    arg0->unk_3C = arg4;
    arg0->unk_74 = arg5;

    MenuDualList_SetMode(arg0, 0);

    for (i = 0; i < 6; i++) {
        arg0->unk_5C[i] = mem_pool_alloc(arg6, sizeof(unk_func_8850878C));

        ((func8850878C)Memmap_GetFragmentVaddr(TextObject_Create))(arg0->unk_5C[i], 0, 0,
                                                               GetMessageString(NULL, 0, gMessageBank_2, i + 0xB), 0x10);

        arg0->unk_5C[i]->unk_30 = gMenuItemColor_White;
        arg0->unk_5C[i]->unk_44 = arg0->unk_5C[i]->unk_44;
    }
}

void MenuDualList_SetSelection(unk_func_8820B12C_02C* arg0, s32 arg1) {
    arg0->unk_48->unk_18 = arg1;
    arg0->unk_44(2, arg0->unk_48);
}

void MenuDualList_SetState(unk_func_8820B12C_02C* arg0, s32 arg1) {
    arg0->unk_18 = arg1;
    MenuDualList_UpdateSublists(arg0);
}

void MenuDualList_UpdateSublists(unk_func_8820B12C_02C* arg0) {
    s32 temp_s3;
    s32 temp_s4;
    s32 temp_v0;
    s32 i;
    s32 var_v0;
    unk_func_8820B12C_02C* var_s1;
    unk_func_8820B12C_02C_020* temp_a0;

    temp_v0 = arg0->unk_18;
    temp_s3 = temp_v0 & 0xFF;
    temp_s4 = temp_v0 & 0xFF00;

    for (i = 0; i < 2; i++) {
        var_v0 = 0;
        if (i == arg0->unk_1C) {
            var_v0 = 1;
        }
        arg0->unk_20[i]->unk_00.unk_00.unk_24(&arg0->unk_20[i]->unk_00, (var_v0 & temp_s3) | temp_s4);
    }
}

void MenuDualList_SetActiveSublist(unk_func_8820B12C_02C* arg0, s32 arg1) {
    arg0->unk_1C = arg1;
    MenuDualList_UpdateSublists(arg0);
}

void MenuDualList_SetMode(unk_func_8820B12C_02C* arg0, s32 arg1) {
    arg0->unk_28 = arg1;
    arg0->unk_2C = 0;
}

void MenuDualList_SwapSublists(unk_func_8820B12C_02C* arg0) {
    unk_func_8820B12C_02C_020* temp_t6 = arg0->unk_20[0];

    arg0->unk_20[0] = arg0->unk_20[1];
    arg0->unk_20[1] = temp_t6;
    arg0->unk_34 = !arg0->unk_34;
}

void MenuDualList_GetCurrentAndSecondary(unk_func_8820B12C_02C* arg0, unk_func_88205880_00D0** arg1, unk_func_88205880_00D0** arg2) {
    switch (arg0->unk_28) {
        case 0:
        case 3:
            *arg1 = arg0->unk_20[0]->unk_00.unk_2C->unk_00[arg0->unk_20[0]->unk_00.unk_38];
            *arg2 = NULL;
            break;

        case 1:
            *arg1 = arg0->unk_20[0]->unk_00.unk_2C->unk_00[arg0->unk_30];
            *arg2 = arg0->unk_20[0]->unk_00.unk_2C->unk_00[arg0->unk_20[0]->unk_00.unk_38];
            break;

        case 2:
            *arg1 = arg0->unk_20[0]->unk_00.unk_2C->unk_00[arg0->unk_20[0]->unk_00.unk_38];
            *arg2 = arg0->unk_20[1]->unk_00.unk_2C->unk_00[arg0->unk_20[1]->unk_00.unk_38];
            break;
    }
}

void MenuDualList_CalcItemPositions(unk_func_8820B12C_02C* arg0, unk_func_88001300_000_010* arg1, unk_func_88001300_000_010* arg2) {
    s16 var_v1;

    switch (arg0->unk_28) {
        case 0:
            arg1->unk_00 = arg0->unk_20[0]->unk_00.unk_00.unk_10.unk_00;
            arg1->unk_02 =
                arg0->unk_20[0]->unk_00.unk_00.unk_10.unk_02 + (arg0->unk_20[0]->unk_5C - arg0->unk_20[0]->unk_58);

            arg2->unk_00 = arg0->unk_20[1]->unk_00.unk_00.unk_10.unk_00;
            arg2->unk_02 =
                arg0->unk_20[1]->unk_00.unk_00.unk_10.unk_02 + (arg0->unk_20[1]->unk_5C - arg0->unk_20[1]->unk_58);
            break;

        case 1:
            var_v1 = (arg0->unk_20[0]->unk_00.unk_3E * arg0->unk_30) - arg0->unk_20[0]->unk_58;
            if (var_v1 < -arg0->unk_20[0]->unk_00.unk_3E) {
                var_v1 = -arg0->unk_20[0]->unk_00.unk_3E;
            } else if (arg0->unk_20[0]->unk_00.unk_00.unk_14.unk_02 < var_v1) {
                var_v1 = arg0->unk_20[0]->unk_00.unk_00.unk_14.unk_02;
            }

            arg1->unk_00 = arg0->unk_20[0]->unk_00.unk_00.unk_10.unk_00;
            arg1->unk_02 = arg0->unk_20[0]->unk_00.unk_00.unk_10.unk_02 + var_v1;

            arg2->unk_00 = arg0->unk_20[0]->unk_00.unk_00.unk_10.unk_00;
            arg2->unk_02 =
                arg0->unk_20[0]->unk_00.unk_00.unk_10.unk_02 + (arg0->unk_20[0]->unk_5C - arg0->unk_20[0]->unk_58);
            break;

        case 2:
            arg1->unk_00 = arg0->unk_20[0]->unk_00.unk_00.unk_10.unk_00;
            arg1->unk_02 =
                arg0->unk_20[0]->unk_00.unk_00.unk_10.unk_02 + (arg0->unk_20[0]->unk_5C - arg0->unk_20[0]->unk_58);

            arg2->unk_00 = arg0->unk_20[1]->unk_00.unk_00.unk_10.unk_00;
            arg2->unk_02 =
                arg0->unk_20[1]->unk_00.unk_00.unk_10.unk_02 + (arg0->unk_20[1]->unk_5C - arg0->unk_20[1]->unk_58);
            break;
    }
}

void MenuDualList_HandleStateTransition(unk_func_8820B12C_02C* arg0, s32 arg1) {
    switch (arg1) {
        case 0:
            ((func8850628C)Memmap_GetFragmentVaddr(Fragment_ClearFlags))(arg0->unk_20[0]);
            ScrollableList_SetDirection(&arg0->unk_20[0]->unk_00, 1);
            ScrollableList_SetDirection(&arg0->unk_20[1]->unk_00, 1);
            MenuDualList_SetActiveSublist(arg0, 0);
            func_88217BB8(arg0->unk_38);
            break;

        case 1:
            arg0->unk_20[0]->unk_00.unk_34[arg0->unk_20[0]->unk_00.unk_38] |= 2;
            ScrollableList_SetActive(arg0->unk_20[1], 0);
            ScrollableList_SetDirection(&arg0->unk_20[1]->unk_00, 0);
            MenuDualList_SetActiveSublist(arg0, 1);
            func_88217BAC(arg0->unk_38);
            break;

        case 2:
            arg0->unk_20[arg0->unk_1C]->unk_00.unk_34[arg0->unk_20[arg0->unk_1C]->unk_00.unk_38] |= 2;
            ScrollableList_SetDirection(&arg0->unk_20[arg0->unk_1C]->unk_00, 0);
            arg0->unk_30 = arg0->unk_20[arg0->unk_1C]->unk_00.unk_38;
            func_88217BAC(arg0->unk_38);
            break;

        case 3:
            arg0->unk_20[0]->unk_00.unk_34[arg0->unk_20[0]->unk_00.unk_38] |= 2;
            ScrollableList_SetDirection(&arg0->unk_20[1]->unk_00, 0);
            MenuDualList_SetActiveSublist(arg0, 1);
            func_88217BAC(arg0->unk_38);
            break;
    }

    arg0->unk_2C = arg1;
}

void MenuDualList_ResetAndInitSecond(unk_func_8820B12C_02C* arg0) {
    MenuDualList_HandleStateTransition(arg0, 0);
    ((func8850628C)Memmap_GetFragmentVaddr(Fragment_ClearFlags))(&arg0->unk_20[1]->unk_00);
}

s32 MenuDualList_IsStateZero(unk_func_8820B12C_02C* arg0) {
    s32 var_v1 = 0;

    if (arg0->unk_2C == 0) {
        var_v1 = 1;
    }
    return var_v1;
}

void MenuDualList_CopyEntry(unk_func_8820B12C_02C_020* arg0, unk_func_8820B12C_02C_020* arg1) {
    unk_func_88205880_00D0* ptr2 = arg0->unk_00.unk_2C->unk_00[arg0->unk_00.unk_38];

    ((func88507CC4)Memmap_GetFragmentVaddr(PtrList_InsertAtSelection))(arg1, ptr2);
    ((func88507CEC)Memmap_GetFragmentVaddr(PtrList_RemoveCurrentAndAdjust))(arg0);

    *arg1->unk_88 = 1;
    *arg0->unk_88 = *arg1->unk_88;
}

void MenuDualList_SwapEntries(unk_func_8820B12C_02C_020* arg0, s32 arg1, s32 arg2) {
    unk_func_88205880_00D0* temp_v0 = arg0->unk_00.unk_2C->unk_00[arg1];

    arg0->unk_00.unk_2C->unk_00[arg1] = arg0->unk_00.unk_2C->unk_00[arg2];
    arg0->unk_00.unk_2C->unk_00[arg2] = temp_v0;

    *arg0->unk_88 = 1;
}

void MenuDualList_SwapEntriesBetweenLists(unk_func_8820B12C_02C_020* arg0, unk_func_8820B12C_02C_020* arg1) {
    unk_func_88205880_00D0* temp_v0 = arg1->unk_00.unk_2C->unk_00[arg1->unk_00.unk_38];
    unk_func_88205880_00D0** temp_v1;

    arg1->unk_00.unk_2C->unk_00[arg1->unk_00.unk_38] = arg0->unk_00.unk_2C->unk_00[arg0->unk_00.unk_38];
    arg0->unk_00.unk_2C->unk_00[arg0->unk_00.unk_38] = temp_v0;

    *arg1->unk_88 = 1;
    *arg0->unk_88 = *arg1->unk_88;
}

void MenuDualList_FinalizeEntry(unk_func_8820B12C_02C_020* arg0) {
    ((func88507CEC)Memmap_GetFragmentVaddr(PtrList_RemoveCurrentAndAdjust))(arg0);
    *arg0->unk_88 = 1;
}

void MenuDualList_Update(unk_func_8820B12C_02C* arg0, Controller* arg1) {
    unk_func_88205880_00D0* sp34;
    unk_func_88205880_00D0* sp30;
    unk_func_88001300_000_010 sp2C;
    unk_func_88001300_000_010 sp28;

    MenuDualList_GetCurrentAndSecondary(arg0, &sp30, &sp34);
    LevelLabelFragment_SetData(arg0->unk_54[0], sp30);
    MenuDualList_CalcItemPositions(arg0, &sp2C, &sp28);
    func_882175F4(arg0->unk_4C[0], sp2C, sp28);

    arg0->unk_14(arg0, 0);

    ((func8850CF00)Memmap_GetFragmentVaddr(ItemArray_WaitForSelection))(arg0->unk_40, arg1);

    arg0->unk_14(arg0, 1);

    MenuDualList_CopyEntry(arg0->unk_20[0], arg0->unk_20[1]);
    MenuDualList_ResetAndInitSecond(arg0);
}

void MenuDualList_UpdateWithSwapFlag(unk_func_8820B12C_02C* arg0, Controller* arg1, s32 arg2) {
    unk_func_88205880_00D0* sp34;
    unk_func_88205880_00D0* sp30;
    unk_func_88001300_000_010 sp2C;
    unk_func_88001300_000_010 sp28;

    MenuDualList_GetCurrentAndSecondary(arg0, &sp30, &sp34);
    LevelLabelFragment_SetData(arg0->unk_54[0], sp30);
    LevelLabelFragment_SetData(arg0->unk_54[1], sp34);
    MenuDualList_CalcItemPositions(arg0, &sp2C, &sp28);
    func_882175F4(arg0->unk_4C[0], sp2C, sp28);
    func_882175F4(arg0->unk_4C[1], sp28, sp2C);

    arg0->unk_14(arg0, 0);

    ((func8850CF00)Memmap_GetFragmentVaddr(ItemArray_WaitForSelection))(arg0->unk_40, arg1);

    arg0->unk_14(arg0, 1);

    if (arg2 != 0) {
        MenuDualList_SwapEntries(arg0->unk_20[0], arg0->unk_30, arg0->unk_20[0]->unk_00.unk_38);
    } else {
        MenuDualList_SwapEntriesBetweenLists(arg0->unk_20[0], arg0->unk_20[1]);
    }

    MenuDualList_ResetAndInitSecond(arg0);
}

void MenuDualList_ConfirmSelection(unk_func_8820B12C_02C* arg0) {
    unk_func_88205880_00D0* sp2C;
    unk_func_88205880_00D0* sp28;
    s32 sp24;

    MenuDualList_GetCurrentAndSecondary(arg0, &sp28, &sp2C);

    arg0->unk_48->unk_0C = sp28;
    arg0->unk_48->unk_10 = arg0->unk_20[0]->unk_8C >> 0x10;

    arg0->unk_44(1, arg0->unk_48);

    PlaySoundEffect(2);

    arg0->unk_20[0]->unk_00.unk_00.unk_24(&arg0->unk_20[0]->unk_00.unk_00, 0x100);

    sp24 = arg0->unk_44(4, arg0->unk_48);

    arg0->unk_20[0]->unk_00.unk_00.unk_24(&arg0->unk_20[0]->unk_00.unk_00, 1);

    if (arg0->unk_48->unk_18 != 0) {
        if (sp24 == 0) {
            MenuDualList_FinalizeEntry(arg0->unk_20[0]);
        }
    } else if (sp24 == 1) {
        *arg0->unk_20[0]->unk_88 = 1;
    }

    MenuDualList_ResetAndInitSecond(arg0);
}

s32 MenuDualList_ProcessInput(unk_func_8820B12C_02C* arg0, Controller* arg1) {
    s32 var_v1;
    s32 var_v0;
    func8850A10C temp_v1;

    var_v1 = arg0->unk_20[arg0->unk_1C]->unk_00.unk_00.unk_20(arg0->unk_20[arg0->unk_1C], arg1);

    if (var_v1 & 1) {
        return var_v1;
    }

    if (var_v1 == 0) {
        if (arg1->buttonPressed & 0x4000) {
            var_v1 = 0x80000002;
        } else if (arg1->buttonPressed & 0x8000) {
            var_v1 = 0x80000004;
        }
    }

    switch (arg0->unk_2C) {
        case 0:
            switch (arg0->unk_28) {
                case 0:
                    if (!(var_v1 & 2) && (var_v1 & 4)) {
                        if (arg0->unk_20[0]->unk_00.unk_2C->unk_08 == 0) {
                            PlaySoundEffect(8);
                            ((func8850A10C)Memmap_GetFragmentVaddr(TextBox_Configure))(arg0->unk_3C, arg0->unk_5C[0], 0, 0);
                            ((func8850A3CC)Memmap_GetFragmentVaddr(Menu_WaitForConfirm))(arg0->unk_3C, arg1);
                            var_v1 = 1;
                        } else if (arg0->unk_20[1]->unk_00.unk_2C->unk_08 >= arg0->unk_20[1]->unk_00.unk_2C->unk_04) {
                            PlaySoundEffect(8);
                            ((func8850A10C)Memmap_GetFragmentVaddr(TextBox_Configure))(arg0->unk_3C, arg0->unk_5C[5], 0, 0);
                            ((func8850A3CC)Memmap_GetFragmentVaddr(Menu_WaitForConfirm))(arg0->unk_3C, arg1);
                            var_v1 = 1;
                        } else {
                            MenuDualList_HandleStateTransition(arg0, 1);
                            var_v1 |= 1;
                        }
                    }
                    break;

                case 1:
                    if (!(var_v1 & 2) && (var_v1 & 4)) {
                        if (arg0->unk_20[0]->unk_00.unk_2C->unk_08 == 0) {
                            PlaySoundEffect(8);
                            ((func8850A10C)Memmap_GetFragmentVaddr(TextBox_Configure))(arg0->unk_3C, arg0->unk_5C[1], 0, 0);
                            ((func8850A3CC)Memmap_GetFragmentVaddr(Menu_WaitForConfirm))(arg0->unk_3C, arg1);
                            var_v1 = 1;
                        } else {
                            MenuDualList_HandleStateTransition(arg0, 2);
                            var_v1 |= 1;
                        }
                    }
                    break;

                case 2:
                    if (!(var_v1 & 2) && (var_v1 & 4)) {
                        if ((arg0->unk_20[0]->unk_00.unk_2C->unk_08 == 0) ||
                            (arg0->unk_20[1]->unk_00.unk_2C->unk_08 == 0)) {
                            PlaySoundEffect(8);
                            ((func8850A10C)Memmap_GetFragmentVaddr(TextBox_Configure))(arg0->unk_3C, arg0->unk_5C[2], 0, 0);
                            ((func8850A3CC)Memmap_GetFragmentVaddr(Menu_WaitForConfirm))(arg0->unk_3C, arg1);
                            var_v1 = 1;
                        } else {
                            MenuDualList_HandleStateTransition(arg0, 3);
                            var_v1 |= 1;
                        }
                    }
                    break;

                case 3:
                    if (!(var_v1 & 2) && (var_v1 & 4)) {
                        if (arg0->unk_20[0]->unk_00.unk_2C->unk_08 == 0) {
                            PlaySoundEffect(8);
                            temp_v1 = ((func8850A10C)Memmap_GetFragmentVaddr(TextBox_Configure));
                            if (arg0->unk_48->unk_18 != 0) {
                                var_v0 = 4;
                            } else {
                                var_v0 = 3;
                            }
                            temp_v1(arg0->unk_3C, arg0->unk_5C[var_v0], 0, 0);
                            ((func8850A3CC)Memmap_GetFragmentVaddr(Menu_WaitForConfirm))(arg0->unk_3C, arg1);
                            var_v1 = 1;
                        } else {
                            MenuDualList_ConfirmSelection(arg0);
                            var_v1 = 5;
                        }
                    }
                    break;
            }
            break;

        case 1:
            if (var_v1 & 2) {
                MenuDualList_HandleStateTransition(arg0, 0);
                ScrollableList_SetActive(arg0->unk_20[1], 1);
                var_v1 |= 1;
            } else if (var_v1 & 4) {
                PlaySoundEffect(0x18);
                arg0->unk_20[0]->unk_00.unk_34[arg0->unk_20[0]->unk_00.unk_38] |= 0x100;
                MenuDualList_Update(arg0, arg1);
                ScrollableList_SetActive(arg0->unk_20[1], 2);
                if (arg0->unk_74 != 0) {
                    var_v1 = 0x02000000;
                } else {
                    var_v1 = 0x80000081;
                }
            }
            break;

        case 2:
            if (var_v1 & 2) {
                MenuDualList_HandleStateTransition(arg0, 0);
                var_v1 |= 1;
            } else if (var_v1 & 4) {
                if (arg0->unk_30 == arg0->unk_20[arg0->unk_1C]->unk_00.unk_38) {
                    var_v1 = 0x80000101;
                } else {
                    PlaySoundEffect(0x18);
                    arg0->unk_20[arg0->unk_1C]->unk_00.unk_34[arg0->unk_20[arg0->unk_1C]->unk_00.unk_38] |= 2;
                    arg0->unk_20[arg0->unk_1C]->unk_00.unk_34[arg0->unk_30] |= 0x100;
                    arg0->unk_20[arg0->unk_1C]->unk_00.unk_34[arg0->unk_20[arg0->unk_1C]->unk_00.unk_38] |= 0x100;
                    MenuDualList_UpdateWithSwapFlag(arg0, arg1, 1);
                    var_v1 = 0x80000081;
                }
            }
            break;

        case 3:
            if (var_v1 & 2) {
                MenuDualList_HandleStateTransition(arg0, 0);
                var_v1 |= 1;
            } else if (var_v1 & 4) {
                PlaySoundEffect(0x18);
                arg0->unk_20[1]->unk_00.unk_34[arg0->unk_20[1]->unk_00.unk_38] |= 2;
                arg0->unk_20[0]->unk_00.unk_34[arg0->unk_20[0]->unk_00.unk_38] |= 0x100;
                arg0->unk_20[1]->unk_00.unk_34[arg0->unk_20[1]->unk_00.unk_38] |= 0x100;
                MenuDualList_UpdateWithSwapFlag(arg0, arg1, 0);
                var_v1 = 0x80000081;
            }
            break;
    }

    return var_v1;
}

unk_func_88205880_00D0* MenuDualList_GetSelectedItem(unk_func_8820B12C_02C* arg0) {
    s32 temp_v1;
    unk_func_88205880_A030* temp_a1;

    if (arg0->unk_2C == 1) {
        return NULL;
    }

    temp_v1 = arg0->unk_20[arg0->unk_1C]->unk_00.unk_38;
    temp_a1 = arg0->unk_20[arg0->unk_1C]->unk_00.unk_2C;

    if (temp_v1 >= temp_a1->unk_08) {
        return NULL;
    }

    return temp_a1->unk_00[temp_v1];
}

void MoveTargetSelector_Init(unk_func_88208C5C* arg0, unk_func_8850143C* arg1) {
    ((func885007CC)Memmap_GetFragmentVaddr(func_885007CC))(arg0, sizeof(unk_func_88208C5C));

    arg0->unk_00.unk_18 = MoveTargetSelector_Draw;
    arg0->unk_00.unk_14.unk_00 = arg1->unk_00.unk_14.unk_00;
    arg0->unk_00.unk_14.unk_02 = arg1->unk_00.unk_14.unk_02;
    arg0->unk_2C = arg1;
    arg0->unk_30 = GetMoveTargetType(MenuItem_GetHeldItemId(func_80029080()));
    arg0->unk_34 = -1;
    arg0->unk_38 = -1;
}

s32 MoveTargetSelector_Draw(unk_func_88208C5C* arg0, s32 arg1, s32 arg2) {
    static u8 gMoveTargetMessageIds[] = {
        0x27,
        0x42,
        0x43,
        0x40,
    };
    static Color_RGBA8 gMoveTargetTextColor_WhiteOpaque = { 0xF0, 0xF0, 0xF0, 0xFF };
    static Color_RGBA8 gMoveTargetTextColor_WhiteOpaque2 = { 0xF0, 0xF0, 0xF0, 0xFF };

    char* spBC = GetMessageString(NULL, 0, gMessageBank_2, gMoveTargetMessageIds[arg0->unk_34]);
    s8 sp9C[0x20];
    s32 temp_v0;
    s32 var_s0;

    if (arg0->unk_38 == -1) {
        return 1;
    }

    if ((arg0->unk_34 == 1) || (arg0->unk_34 == 2)) {
        sprintf(sp9C, "%s %d", spBC, arg0->unk_38 + 1);
        spBC = sp9C;
    }

    temp_v0 = MeasureTextWidth(8, 0, spBC);

    gDPPipeSync(gDisplayListHead++);

    gDPSetCycleType(gDisplayListHead++, G_CYC_COPY);
    gDPSetRenderMode(gDisplayListHead++, G_RM_NOOP, G_RM_NOOP2);
    gDPSetAlphaCompare(gDisplayListHead++, G_AC_THRESHOLD);
    gDPSetTexturePersp(gDisplayListHead++, G_TP_NONE);

    if ((arg0->unk_34 == 0) || (arg0->unk_34 == 1)) {
        var_s0 = (((arg0->unk_00.unk_14.unk_00 - temp_v0) - 0x20) / 2) + arg1 + 0x20;

        gDPLoadTextureBlock(gDisplayListHead++, gTexture_MoveTargetSmall[arg0->unk_30], G_IM_FMT_RGBA, G_IM_SIZ_16b, 24, 26, 0,
                            G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                            G_TX_NOLOD);
        gSPTextureRectangle(gDisplayListHead++, (var_s0 - 0x20) << 2, (arg2 + 2) << 2, (var_s0 - 9) << 2,
                            (arg2 + 0x1B) << 2, G_TX_RENDERTILE, 0, 0, 0x1000, 0x0400);
    } else {
        var_s0 = (((arg0->unk_00.unk_14.unk_00 - temp_v0) - 0x30) / 2) + arg1 + 0x30;

        gDPLoadTextureBlock(gDisplayListHead++, gTexture_MoveTargetLarge, G_IM_FMT_RGBA, G_IM_SIZ_16b, 48, 26, 0,
                            G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                            G_TX_NOLOD);
        gSPTextureRectangle(gDisplayListHead++, (var_s0 - 0x30) << 2, (arg2 + 2) << 2, (var_s0 - 9) << 2,
                            (arg2 + 0x1B) << 2, G_TX_RENDERTILE, 0, 0, 0x1000, 0x0400);
    }

    gDPPipeSync(gDisplayListHead++);

    gDPSetAlphaCompare(gDisplayListHead++, G_AC_NONE);

    Text_ResetState();
    Text_SetEnvColor(gMoveTargetTextColor_WhiteOpaque.r, gMoveTargetTextColor_WhiteOpaque.g, gMoveTargetTextColor_WhiteOpaque.b, gMoveTargetTextColor_WhiteOpaque.a);
    Text_SetFont(8, 0);
    Text_Print(var_s0, arg2 + 5, spBC);
    Text_SetupDL();

    return 0;
}

u32 MoveTargetSelector_GetSelection(unk_func_88208C5C* arg0) {
    return (arg0->unk_34 << 0x10) | arg0->unk_38;
}

void Scroll_SetOffset(unk_func_88208C5C* arg0, u32 arg1) {
    arg0->unk_34 = arg1 >> 0x10;
    arg0->unk_38 = arg1 & 0xFFFF;
}

void MoveIconList_Init(unk_func_8820BE14_02C_070* arg0, s32 arg1, s32 arg2) {
    ((func885007CC)Memmap_GetFragmentVaddr(func_885007CC))(arg0, sizeof(unk_func_8820BE14_02C_070));

    arg0->unk_0000.unk_18 = RenderMoveInfoPanel;
    arg0->unk_0000.unk_10.unk_00 = arg1;
    arg0->unk_0000.unk_10.unk_02 = arg2;

    func_88209A88(arg0, NULL);

    arg0->unk_0030 = 0;
}

void DrawMoveName(s32 arg0, s32 arg1, ret_func_8002ED08* arg2, s32 arg3) {
    Color_RGBA8 sp24;
    char* sp20;

    Text_SetFont(8, 0);
    if (arg2 == NULL) {
        sp24 = ((func884000C4)Memmap_GetFragmentVaddr(GetMoveCategoryColorGradient))(0)->unk_04;
        sp20 = "???????";
    } else {
        sp24 = ((func884000C4)Memmap_GetFragmentVaddr(GetMoveCategoryColorGradient))(arg2->unk_00[1])->unk_04;
        sp20 = GetMessageString(NULL, 0, gMessageBank_25, arg2->unk_00[0] - 1);
    }

    Text_SetEnvColor(sp24.r, sp24.g, sp24.b, sp24.a);

    if (arg3 != 0) {
        arg0 = (arg0 - MeasureTextWidth(0, 0, sp20)) + 0x8C;
    }

    Text_Print(arg0, arg1, sp20);
}

s32 RenderMoveInfoPanel(unk_func_8820BE14_02C_070* arg0, s32 arg1, s32 arg2) {
    static Color_RGBA8 gDefaultTextColor = { 0xF0, 0xF0, 0xF0, 0xFF };
    static MoveIconInfoEntry gMoveIconInfo[] = {
        {
            0x000000DB,
            0x00000004,
            0x00000001,
            0x00000167,
            0x040037A8,
        },
        {
            0x00000193,
            0x0000001C,
            0x00000000,
            0x0000017F,
            0x04003AD0,
        },
        {
            0x0000017B,
            0x00000034,
            0x00000000,
            0x00000167,
            0x04003DF8,
        },
        { 0x000000C3, 0x0000001C, 0x00000001, 0x0000014F, 0x04004120 },
    };

    s32 i;
    s32 spB0;
    unk_func_88205880_00D0* ptr = arg0->unk_002C;

    if (ptr == NULL) {
        return 0;
    }

    spB0 = Mon_CountMoves(ptr);

    i = (u32)arg0->unk_0039[arg0->unk_0030] & ~7;

    gDPPipeSync(gDisplayListHead++);

    gDPSetCycleType(gDisplayListHead++, G_CYC_COPY);
    gDPSetRenderMode(gDisplayListHead++, G_RM_NOOP, G_RM_NOOP2);
    gDPSetAlphaCompare(gDisplayListHead++, G_AC_THRESHOLD);
    gDPSetTexturePersp(gDisplayListHead++, G_TP_NONE);

    gDPLoadTextureBlock(gDisplayListHead++, i, G_IM_FMT_RGBA, G_IM_SIZ_16b, 40, 40, 0, G_TX_NOMIRROR | G_TX_WRAP,
                        G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    gSPTextureRectangle(gDisplayListHead++, (arg1 + 0x84) << 2, (arg2 + 0xA) << 2, (arg1 + 0xAB) << 2,
                        (arg2 + 0x31) << 2, G_TX_RENDERTILE, 0, 0, 0x1000, 0x0400);

    for (i = 0; i < 4; i++) {
        gDPLoadTextureBlock(gDisplayListHead++, gMoveIconInfo[i].unk_10, G_IM_FMT_RGBA, G_IM_SIZ_16b, 20, 20, 0,
                            G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                            G_TX_NOLOD);
        gSPTextureRectangle(gDisplayListHead++, (arg1 + gMoveIconInfo[i].unk_0C) << 2, (arg2 + gMoveIconInfo[i].unk_04) << 2,
                            ((arg1 + gMoveIconInfo[i].unk_0C) + 0x13) << 2, (arg2 + gMoveIconInfo[i].unk_04 + 0x13) << 2,
                            G_TX_RENDERTILE, 0, 0, 0x1000, 0x0400);
    }

    gDPPipeSync(gDisplayListHead++);

    gDPSetAlphaCompare(gDisplayListHead++, G_AC_NONE);

    Text_ResetState();

    if ((arg0->unk_002C->unk_000[0].unk_00.unk_00 <= 0) || (arg0->unk_002C->unk_000[0].unk_00.unk_00 >= 0x98)) {
        Text_SetEnvColor(gDefaultTextColor.r, gDefaultTextColor.g, gDefaultTextColor.b, gDefaultTextColor.a);
        Text_SetFont(8, 0);
        Text_Print(arg1 + 8, arg2 + 8, "?????");
    } else {
        Text_SetEnvColor(gDefaultTextColor.r, gDefaultTextColor.g, gDefaultTextColor.b, gDefaultTextColor.a);
        Text_SetFont(8, 0);

        Text_Print(arg1 + 8, arg2 + 0x24, GetMessageString(NULL, 0, gMessageBank_2, 0x12));
        Text_SetEnvColor(0xFF, 0xC8, 0xC8, 0xFF);
        Text_SetFont(4, 0);

        Text_Print(arg1 + 6, arg2 + 0x56, GetMessageString(NULL, 0, gMessageBank_2, 0x13));
        Text_Print(arg1 + 0x91, arg2 + 0x56, GetMessageString(NULL, 0, gMessageBank_2, 0x14));
        Text_Print(arg1 + 0x11C, arg2 + 0x56, GetMessageString(NULL, 0, gMessageBank_2, 0x15));
        Text_Print(arg1 + 0x1A7, arg2 + 0x56, GetMessageString(NULL, 0, gMessageBank_2, 0x16));

        Text_SetEnvColor(gDefaultTextColor.r, gDefaultTextColor.g, gDefaultTextColor.b, gDefaultTextColor.a);
        Text_SetFont(8, 0);
        Text_Print(arg1 + 8, arg2 + 8,
                      GetMessageString(NULL, 0, gMessageBank_24, arg0->unk_002C->unk_000[0].unk_00.unk_00 - 1));

        Text_Print(arg1 + 0x44, arg2 + 0x24, "%3d", arg0->unk_002C->unk_000[0].unk_26);
        Text_Print(arg1 + 0x46, arg2 + 0x54, "%3d", arg0->unk_002C->unk_000[0].unk_28);
        Text_Print(arg1 + 0xD1, arg2 + 0x54, "%3d", arg0->unk_002C->unk_000[0].unk_2A);
        Text_Print(arg1 + 0x15C, arg2 + 0x54, "%3d", arg0->unk_002C->unk_000[0].unk_2C);
        Text_Print(arg1 + 0x1E7, arg2 + 0x54, "%3d", arg0->unk_002C->unk_000[0].unk_2E);
    }

    for (i = 0; i < spB0; i++) {
        DrawMoveName(gMoveIconInfo[i].unk_00 + arg1, gMoveIconInfo[i].unk_04 + arg2,
                      GetMoveEntry(arg0->unk_002C->unk_000[0].unk_09[i]), gMoveIconInfo[i].unk_08);
    }

    Text_SetupDL();

    return 0;
}

void func_88209A88(unk_func_8820BE14_02C_070* arg0, unk_func_88205880_00D0* arg1) {
    arg0->unk_002C = arg1;
    if (arg1 != NULL) {
        arg0->unk_0030 = (arg0->unk_0030 + 1) & 1;
        func_8001B0DC((u32)arg0->unk_0039[arg0->unk_0030] & ~7, 0, arg0->unk_002C);
    }
}

s32 FindFirstIncompleteSlot(unk_func_8820BE14_06C* arg0) {
    s32 i;
    s32 j;
    unk_func_8820BE14_06C_000* ptr;

    for (i = 0; i < 3; i++) {
        ptr = arg0[i].unk_00;
        for (j = 0; j < arg0[i].unk_08; j++) {
            if (ptr[j].unk_04.unk_08 < ptr[j].unk_04.unk_04) {
                return (i << 0x10) | j;
            }
        }
    }
    return 0;
}

static Color_RGBA8 gUIComponentColorPrimary = { 0x6C, 0x6C, 0x7E, 0xFF };
static Color_RGBA8 gUIComponentColorSecondary = { 0x50, 0x50, 0x86, 0xFF };
static Color_RGBA8 gUIComponentColorAccent = { 0x79, 0x79, 0xCB, 0xFF };
static Color_RGBA8 gUIComponentColorDark = { 0x40, 0x40, 0x6C, 0xFF };
static Color_RGBA8 gUIComponentColorHighlight = { 0x6A, 0x6A, 0xB2, 0xFF };
static UIComponentInfoEntry gUIComponentInfo[] = {
    {
        219,
        40,
        54,
        42,
        gPanelIconTexture,
        0x30,
        0x0000,
        gPanelOverlayTexture,
        1,
        1,
    },
    {
        279,
        40,
        54,
        42,
        gPanelIconTexture,
        0x30,
        0x0000,
        gPanelOverlayTexture,
        0,
        3,
    },
    {
        219,
        88,
        54,
        42,
        gPanelBackgroundTexture1,
        0x30,
        0x0000,
        gPanelAccentTexture2,
        0,
        3,
    },
    {
        279,
        88,
        54,
        42,
        gTexture_PanelA,
        0x30,
        0x0000,
        gPanelColorA,
        1,
        1,
    },
    {
        219,
        136,
        54,
        42,
        gPanelBackgroundTexture3,
        0x30,
        0x0000,
        gPanelAccentTexture4,
        0,
        1,
    },
    {
        279,
        136,
        54,
        42,
        gPanelBackgroundTexture2,
        0x30,
        0x0000,
        gPanelAccentTexture3,
        1,
        1,
    },
    {
        219,
        184,
        54,
        42,
        gPanelBackgroundTexture4,
        0x30,
        0x0000,
        gPanelAccentTexture1,
        0,
        3,
    },
    {
        279,
        184,
        54,
        42,
        D_8821D378,
        0x30,
        0x0000,
        D_882181E0,
        1,
        1,
    },
};
static Color_RGBA8 gDialogTitleColor = { 0xFF, 0xFF, 0x00, 0xFF };
static Color_RGBA8 gDialogBodyColor = { 0x2D, 0x1A, 0x41, 0xFF };
static Color_RGBA8 gDialogShadowColor = { 0x6F, 0x5F, 0x7F, 0xFF };
static Color_RGBA8* gDialogColorPalette[] = {
    gPanelTextureDefault, gPanelTextureDefault, gPanelTextureAlt1, gTexture_MainMenuOption1, gPanelTextureAlt3, gPanelTextureAlt2, gPanelTextureAlt4, D_88218220,
};
static Color_RGBA8* gDialogAccentPalette[] = { gPanelTextureAlt4, gPanelTextureAlt4 };
static Color_RGBA8 gDialogDefaultColor = { 0xF0, 0xF0, 0xF0, 0xFF };

void TextObjectRenderer_Init(TextObjectRenderer* arg0, s32 arg1, s32 arg2, unk_func_8820BE14_06C_000* arg3,
                   unk_func_8820BE14_06C_000* arg4, unk_func_88001300_000* arg5, FragmentEntry arg6,
                   unk_func_8820BE14_030* arg7, TextObjectGraphics* arg8, char** arg9, MemoryPool* argA) {
    s32 i;
    UNUSED s32 pad1;
    UNUSED s32 pad2;
    unk_func_885012A4* spF8[5];
    unk_func_88001300_000* spF0[2];
    unk_func_8850143C* spE8[2];
    s32 j;
    s32 temp_s0_5;
    char* temp_s1_2;
    char* temp_v0_10;
    unk_func_88001300_02C* temp_s0;
    unk_func_8850878C* spB4[8];
    unk_func_88001300_03C_01C* temp_s0_2;
    unk_func_8850143C* temp_s0_3;
    unk_func_8850878C* temp_s0_4;
    unk_func_88503298* temp_s0_6;
    char* spA0;
    s32 sp9C;
    unk_func_88507D4C* sp94[2];
    char* temp_s0_7;
    unk_func_88507D4C* sp88[2];
    unk_func_882170A8* temp_v0_14;
    unk_func_882170A8* temp_v0_16;
    UNUSED s32 pad[2];
    u32 temp_s1;
    unk_func_8820BE14_06C* temp_s0_8;
    s32 var_v0;

    if (arg1) {} // fake: makes arg1 take s0 ahead of arg2
    arg0->unk_8C = arg4;
    arg0->unk_80 = arg8;

    ((func885007CC)Memmap_GetFragmentVaddr(func_885007CC))(arg0, sizeof(TextObjectRenderer));

    arg0->unk_00.unk_1C = UIState_Update;
    arg0->unk_00.unk_20 = UI_HandleInput;
    arg0->unk_00.unk_24 = UI_SetState;
    arg0->unk_00.unk_10.unk_02 = arg2;
    arg0->unk_00.unk_10.unk_00 = arg1;

    arg0->unk_74 = mem_pool_alloc(argA, sizeof(unk_func_8820B12C));
    UIComponent_SetCallback(arg0->unk_74, arg0);

    arg0->unk_2C = mem_pool_alloc(argA, sizeof(unk_func_88001300_038));
    ((func88502274)Memmap_GetFragmentVaddr(Fragment_SetRect))(arg0->unk_2C, 0, 0, 0x228, 0x160);
    arg0->unk_2C->unk_00.unk_28 |= 0x400;
    ((func8850068C)Memmap_GetFragmentVaddr(Fragment_SetChild))(arg0, arg0->unk_2C);

    temp_s0 = mem_pool_alloc(argA, sizeof(unk_func_88001300_02C));
    ((func88503118)Memmap_GetFragmentVaddr(UITimer_Create))(temp_s0, 0, 0, 0x228, 0x160);
    temp_s0->unk_2C = 0;
    ((func8850068C)Memmap_GetFragmentVaddr(Fragment_SetChild))(arg0->unk_2C, temp_s0);

    spF8[0] = mem_pool_alloc(argA, sizeof(unk_func_885012A4));
    ((func885012A4)Memmap_GetFragmentVaddr(UIFrame_Create))(spF8[0], 0, 0, 0x228, 8, gUIComponentColorPrimary);
    ((func8850068C)Memmap_GetFragmentVaddr(Fragment_SetChild))(arg0->unk_2C, spF8[0]);

    spF8[1] = mem_pool_alloc(argA, sizeof(unk_func_885012A4));
    ((func885012A4)Memmap_GetFragmentVaddr(UIFrame_Create))(spF8[1], 0, 0xEE, 0x228, 6, gUIComponentColorPrimary);
    ((func8850068C)Memmap_GetFragmentVaddr(Fragment_SetChild))(arg0->unk_2C, spF8[1]);

    spF8[2] = mem_pool_alloc(argA, sizeof(unk_func_885012A4));
    ((func885012A4)Memmap_GetFragmentVaddr(UIFrame_Create))(spF8[2], 0, 8, 8, 0xE6, gUIComponentColorPrimary);
    ((func8850068C)Memmap_GetFragmentVaddr(Fragment_SetChild))(arg0->unk_2C, spF8[2]);

    spF8[3] = mem_pool_alloc(argA, sizeof(unk_func_885012A4));
    ((func885012A4)Memmap_GetFragmentVaddr(UIFrame_Create))(spF8[3], 0x220, 8, 8, 0xE6, gUIComponentColorPrimary);
    ((func8850068C)Memmap_GetFragmentVaddr(Fragment_SetChild))(arg0->unk_2C, spF8[3]);

    spF8[4] = mem_pool_alloc(argA, sizeof(unk_func_885012A4));
    ((func885012A4)Memmap_GetFragmentVaddr(UIFrame_Create))(spF8[4], 0xD4, 8, 0x80, 0xE6, gUIComponentColorPrimary);
    ((func8850068C)Memmap_GetFragmentVaddr(Fragment_SetChild))(arg0->unk_2C, spF8[4]);

    spF0[0] = mem_pool_alloc(argA, sizeof(unk_func_88001300_000));
    ((func8850AB48)Memmap_GetFragmentVaddr(DialogBox_Init))(spF0[0], 8, 8, 0xCC, 0xE6);
    ((func8850068C)Memmap_GetFragmentVaddr(Fragment_SetChild))(arg0->unk_2C, spF0[0]);

    spF0[1] = mem_pool_alloc(argA, sizeof(unk_func_88001300_000));
    ((func8850AB48)Memmap_GetFragmentVaddr(DialogBox_Init))(spF0[1], 0x154, 8, 0xCC, 0xE6);
    ((func8850068C)Memmap_GetFragmentVaddr(Fragment_SetChild))(arg0->unk_2C, spF0[1]);

    spE8[0] = mem_pool_alloc(argA, sizeof(unk_func_8850143C));
    ((func8850143C)Memmap_GetFragmentVaddr(UIGradientRect_Create))(spE8[0], 8, 8, 0xCC, 0x1E, gUIComponentColorSecondary, gUIComponentColorAccent);
    ((func8850068C)Memmap_GetFragmentVaddr(Fragment_SetChild))(arg0->unk_2C, spE8[0]);

    spE8[1] = mem_pool_alloc(argA, sizeof(unk_func_8850143C));
    ((func8850143C)Memmap_GetFragmentVaddr(UIGradientRect_Create))(spE8[1], 0x154, 8, 0xCC, 0x1E, gUIComponentColorSecondary, gUIComponentColorAccent);
    ((func8850068C)Memmap_GetFragmentVaddr(Fragment_SetChild))(arg0->unk_2C, spE8[1]);

    arg0->unk_30[0] = mem_pool_alloc(argA, sizeof(unk_func_88208C5C));
    MoveTargetSelector_Init(arg0->unk_30[0], spE8[0]);
    ((func8850068C)Memmap_GetFragmentVaddr(Fragment_SetChild))(spE8[0], arg0->unk_30[0]);

    arg0->unk_30[1] = mem_pool_alloc(argA, sizeof(unk_func_88208C5C));
    MoveTargetSelector_Init(arg0->unk_30[1], spE8[1]);
    ((func8850068C)Memmap_GetFragmentVaddr(Fragment_SetChild))(spE8[1], arg0->unk_30[1]);

    arg0->unk_40 = mem_pool_alloc(argA, sizeof(unk_func_88217740));
    func_88217740(arg0->unk_40, 0xF4, 0xA);
    ((func8850068C)Memmap_GetFragmentVaddr(Fragment_SetChild))(arg0->unk_2C, arg0->unk_40);

    if (arg3 != NULL) {
        arg0->unk_40->unk_00.unk_28 &= ~1;
    }

    var_v0 = (arg3 != NULL) ? 1 : 0;

    for (j = 0; j < 8U; j++) {
        UIComponentInfoEntry* ptr = &gUIComponentInfo[j];
        if (!(ptr->unk_18 & (1 << var_v0))) {
            continue;
        }

        arg0->unk_44[j] = mem_pool_alloc(argA, sizeof(unk_func_882149A0));
        Panel_Init(arg0->unk_44[j], ptr->unk_00, ptr->unk_02, ptr->unk_04, ptr->unk_06, ptr->unk_08, ptr->unk_0C,
                      ptr->unk_10[0], ptr->unk_10[1], gUIComponentColorPrimary);

        if (ptr->unk_14 != 0) {
            Panel_ToggleFill(arg0->unk_44[j]);
        }

        ((func8850068C)Memmap_GetFragmentVaddr(Fragment_SetChild))(arg0->unk_2C, arg0->unk_44[j]);
    }

    arg0->unk_74->unk_28 = mem_pool_alloc(argA, sizeof(unk_func_88001300_03C));
    ((func8850C284)Memmap_GetFragmentVaddr(func_8850C284))(arg0->unk_74->unk_28, 4, 2, argA);
    ((func8850BF80)Memmap_GetFragmentVaddr(Screen_SetFragment))(arg0->unk_74, arg0->unk_74->unk_28);

    for (j = 0; j != 8; j++) {
        if (gUIComponentInfo[j].unk_18 & (1 << var_v0)) {
            arg0->unk_74->unk_28->unk_18[(j / 2) * arg0->unk_74->unk_28->unk_2C + (j % 2)] = arg0->unk_44[j];
        }
    }

    ((func8850CB48)Memmap_GetFragmentVaddr(GridMenu_SetSelection))(arg0->unk_74->unk_28, 2);

    temp_s0_2 = mem_pool_alloc(argA, sizeof(unk_func_88001300_03C_01C));
    ((func88503340)Memmap_GetFragmentVaddr(UIFlashingElement_Create))(temp_s0_2, 0, 0, 0x10, 0x10, gDialogTitleColor);
    ((func8850068C)Memmap_GetFragmentVaddr(Fragment_SetChild))(arg0->unk_2C, temp_s0_2);
    arg0->unk_74->unk_28->unk_1C = temp_s0_2;

    temp_s0_3 = mem_pool_alloc(argA, sizeof(unk_func_8850143C));
    ((func8850143C)Memmap_GetFragmentVaddr(UIGradientRect_Create))(temp_s0_3, 0, 0xF4, 0x228, 0x6C, gDialogBodyColor, gDialogShadowColor);
    ((func8850068C)Memmap_GetFragmentVaddr(Fragment_SetChild))(arg0->unk_2C, temp_s0_3);

    arg0->unk_64 = mem_pool_alloc(argA, sizeof(unk_func_88500994));
    ((func88500994)Memmap_GetFragmentVaddr(func_88500994))(arg0->unk_64, 0, 0);
    ((func8850068C)Memmap_GetFragmentVaddr(Fragment_SetChild))(temp_s0_3, arg0->unk_64);

    arg0->unk_68 = mem_pool_alloc(argA, sizeof(unk_func_88500994));
    ((func88500994)Memmap_GetFragmentVaddr(func_88500994))(arg0->unk_68, 0, 0);
    ((func88500A3C)Memmap_GetFragmentVaddr(Fragment_AddToParent))(arg0->unk_64, arg0->unk_68);

    for (i = 0; i != 8; i++) {
        temp_s1_2 = GetMessageString(NULL, 0, gMessageBank_2, i + 1);
        spB4[i] = mem_pool_alloc(argA, sizeof(unk_func_8850878C));
        ((func8850878C)Memmap_GetFragmentVaddr(TextObject_Create))(spB4[i], (0x228 - MeasureTextWidth(0x10, 0, temp_s1_2)) / 2,
                                                               0x2A, temp_s1_2, 0x10);
        spB4[i]->unk_30 = gDialogColorPalette[i][0];
        spB4[i]->unk_44 = spB4[i]->unk_44;
        spB4[i]->unk_34 = gDialogColorPalette[i][1];
        spB4[i]->unk_44 = 1;
        ((func88500A3C)Memmap_GetFragmentVaddr(Fragment_AddToParent))(arg0->unk_68, spB4[i]);
    }

    if (arg3 != NULL) {
        temp_v0_10 = GetMessageString(NULL, 0, gMessageBank_2, 9);
        spB4[2]->unk_00.unk_10.unk_00 = (0x228 - MeasureTextWidth(0x10, 0, temp_v0_10)) / 2;
        spB4[2]->unk_00.unk_10.unk_02 = 0x2A;
        spB4[2]->unk_40 = temp_v0_10;
    }

    arg0->unk_6C = mem_pool_alloc(argA, sizeof(unk_func_88500994));
    ((func88500994)Memmap_GetFragmentVaddr(func_88500994))(arg0->unk_6C, 0, 0);
    ((func88500A3C)Memmap_GetFragmentVaddr(Fragment_AddToParent))(arg0->unk_64, arg0->unk_6C);

    for (j = 0; j != 2; j++) {
        temp_s0_4 = mem_pool_alloc(argA, sizeof(unk_func_8850878C));
        spA0 = GetMessageString(NULL, 0, gMessageBank_2, 0xA);

        if (j == 0) {
            sp9C = 0x210 - MeasureTextWidth(0x10, 0, spA0);
        } else {
            sp9C = 0x18;
        }

        ((func8850878C)Memmap_GetFragmentVaddr(TextObject_Create))(temp_s0_4, sp9C, 0x1A, spA0, 0x10);

        temp_s0_4->unk_30 = gDialogAccentPalette[j][0];
        temp_s0_4->unk_44 = temp_s0_4->unk_44;
        temp_s0_4->unk_34 = gDialogAccentPalette[j][1];
        temp_s0_4->unk_44 = 1;
        temp_s0_4->unk_3C = 0x20;

        ((func88500A3C)Memmap_GetFragmentVaddr(Fragment_AddToParent))(arg0->unk_6C, temp_s0_4);
    }

    arg0->unk_70 = mem_pool_alloc(argA, sizeof(unk_func_8820BE14_02C_070));
    MoveIconList_Init(arg0->unk_70, 0, 0);
    ((func88500A3C)Memmap_GetFragmentVaddr(Fragment_AddToParent))(arg0->unk_64, arg0->unk_70);

    arg0->unk_38[0] = mem_pool_alloc(argA, sizeof(unk_func_8820B12C_02C_020));
    ScrollableList_Init(arg0->unk_38[0], 8, 0x36, 6, LevelLabel_DrawBackground, 0xCC, 0x1C, argA);
    ((func88506238)Memmap_GetFragmentVaddr(ScrollableList_SetItemHeight))(arg0->unk_38[0], 0x14, argA);

    sp94[0] = mem_pool_alloc(argA, sizeof(unk_func_88507D4C));
    ((func88507D4C)Memmap_GetFragmentVaddr(ItemSlot_Create))(sp94[0], 8, 0x26, 0xCC, 0, arg0->unk_38[0]);
    ((func8850068C)Memmap_GetFragmentVaddr(Fragment_SetChild))(arg0->unk_2C, sp94[0]);

    sp94[1] = mem_pool_alloc(argA, sizeof(unk_func_88507D4C));
    ((func88507D4C)Memmap_GetFragmentVaddr(ItemSlot_Create))(sp94[1], 8, arg0->unk_38[0]->unk_00.unk_00.unk_14.unk_02 + 0x36,
                                                           0xCC, 1, arg0->unk_38[0]);
    ((func8850068C)Memmap_GetFragmentVaddr(Fragment_SetChild))(arg0->unk_2C, sp94[1]);
    ScrollableList_SetItemRenderer(arg0->unk_38[0], sp94[1]);

    temp_v0_14 = mem_pool_alloc(argA, sizeof(unk_func_882170A8));
    ItemSlot_Init(temp_v0_14, 0x98, 2, arg0->unk_38[0], 2);
    ((func8850068C)Memmap_GetFragmentVaddr(Fragment_SetChild))(sp94[1], temp_v0_14);
    ((func8850068C)Memmap_GetFragmentVaddr(Fragment_SetChild))(arg0->unk_2C, arg0->unk_38[0]);

    arg0->unk_38[1] = mem_pool_alloc(argA, sizeof(unk_func_8820B12C_02C_020));
    ScrollableList_Init(arg0->unk_38[1], 0x154, 0x36, 6, LevelLabel_DrawBackground, 0xCC, 0x1C, argA);
    ((func88506238)Memmap_GetFragmentVaddr(ScrollableList_SetItemHeight))(arg0->unk_38[1], 0x14, argA);

    sp88[0] = mem_pool_alloc(argA, sizeof(unk_func_88507D4C));
    ((func88507D4C)Memmap_GetFragmentVaddr(ItemSlot_Create))(sp88[0], 0x154, 0x26, 0xCC, 0, arg0->unk_38[1]);
    ((func8850068C)Memmap_GetFragmentVaddr(Fragment_SetChild))(arg0->unk_2C, sp88[0]);

    sp88[1] = mem_pool_alloc(argA, sizeof(unk_func_88507D4C));
    ((func88507D4C)Memmap_GetFragmentVaddr(ItemSlot_Create))(
        sp88[1], 0x154, arg0->unk_38[1]->unk_00.unk_00.unk_14.unk_02 + 0x36, 0xCC, 1, arg0->unk_38[1]);
    ((func8850068C)Memmap_GetFragmentVaddr(Fragment_SetChild))(arg0->unk_2C, sp88[1]);
    ScrollableList_SetItemRenderer(arg0->unk_38[1], sp88[1]);

    temp_v0_16 = mem_pool_alloc(argA, sizeof(unk_func_882170A8));
    ItemSlot_Init(temp_v0_16, 0x98, 2, arg0->unk_38[1], 2);
    ((func8850068C)Memmap_GetFragmentVaddr(Fragment_SetChild))(sp88[1], temp_v0_16);
    ((func8850068C)Memmap_GetFragmentVaddr(Fragment_SetChild))(arg0->unk_2C, arg0->unk_38[1]);

    if (arg3 != NULL) {
        temp_s0_5 = FindFirstIncompleteSlot(arg0->unk_8C);
        Scroll_SetOffset(arg0->unk_30[0], 0x30000);
        Scroll_SetOffset(arg0->unk_30[1], temp_s0_5);
        ScrollableList_SetDataPtr(arg0->unk_38[0], arg3, 0x30000);
        ScrollableList_SetDataPtr(arg0->unk_38[1],
                      (unk_func_8820BE14_06C_000*)((u8*)arg0->unk_8C[temp_s0_5 >> 0x10].unk_00 +
                                                   (arg0->unk_8C[temp_s0_5 >> 0x10].unk_0C * (temp_s0_5 & 0xFFFF))),
                      temp_s0_5);
    } else {
        temp_s1 = 0x10000;
        Scroll_SetOffset(arg0->unk_30[0], 0);
        Scroll_SetOffset(arg0->unk_30[1], temp_s1);
        temp_s0_8 = arg0->unk_8C;
        ScrollableList_SetDataPtr(arg0->unk_38[0], temp_s0_8[0].unk_00, 0);
        temp_s0_8 = arg0->unk_8C;
        ScrollableList_SetDataPtr(arg0->unk_38[1], temp_s0_8[1].unk_00, temp_s1);
    }

    arg0->unk_74->unk_2C = mem_pool_alloc(argA, sizeof(unk_func_8820B12C_02C));
    MenuDualList_Init(arg0->unk_74->unk_2C, arg0->unk_38[0], arg0->unk_38[1], arg0->unk_40, arg0->unk_80, arg3 != NULL, argA);
    ((func8850BF80)Memmap_GetFragmentVaddr(Screen_SetFragment))(arg0->unk_74, arg0->unk_74->unk_2C);

    arg0->unk_74->unk_2C->unk_40 = mem_pool_alloc(argA, sizeof(unk_func_8850CD44));
    ((func8850CD44)Memmap_GetFragmentVaddr(Panel_Setup))(arg0->unk_74->unk_2C->unk_40, 2, argA);

    for (j = 0; j < 2; j++) {
        arg0->unk_74->unk_2C->unk_4C[j] = mem_pool_alloc(argA, sizeof(unk_func_882173EC));
        Button_Init(arg0->unk_74->unk_2C->unk_4C[j], 0, 0);
        ((func8850068C)Memmap_GetFragmentVaddr(Fragment_SetChild))(arg0->unk_2C, arg0->unk_74->unk_2C->unk_4C[j]);

        arg0->unk_74->unk_2C->unk_54[j] = mem_pool_alloc(argA, sizeof(unk_func_882079D8));
        LevelLabelFragment_Init(arg0->unk_74->unk_2C->unk_54[j], 0, 0, 0xCC, NULL);
        ((func8850068C)Memmap_GetFragmentVaddr(Fragment_SetChild))(arg0->unk_74->unk_2C->unk_4C[j],
                                                               arg0->unk_74->unk_2C->unk_54[j]);

        arg0->unk_74->unk_2C->unk_40->unk_1C[j] = arg0->unk_74->unk_2C->unk_4C[j];
    }

    arg0->unk_74->unk_2C->unk_44 = arg6;
    arg0->unk_74->unk_2C->unk_48 = arg7;

    arg0->unk_78[0] = mem_pool_alloc(argA, sizeof(unk_func_8820BE14_02C_078));
    MenuList_Init(arg0->unk_78[0], 8, 0x2A, 0xCC, arg0->unk_8C, 0, argA);
    ((func8850068C)Memmap_GetFragmentVaddr(Fragment_SetChild))(arg0->unk_2C, arg0->unk_78[0]);

    arg0->unk_78[1] = mem_pool_alloc(argA, sizeof(unk_func_8820BE14_02C_078));
    MenuList_Init(arg0->unk_78[1], 0x154, 0x2A, 0xCC, arg0->unk_8C, 1, argA);
    ((func8850068C)Memmap_GetFragmentVaddr(Fragment_SetChild))(arg0->unk_2C, arg0->unk_78[1]);

    temp_s0_6 = mem_pool_alloc(argA, sizeof(unk_func_88503298));
    ((func88503298)Memmap_GetFragmentVaddr(Dialog_SetParent))(temp_s0_6, arg0->unk_2C, arg5);
    ((func8850068C)Memmap_GetFragmentVaddr(Fragment_SetChild))(arg0, temp_s0_6);

    arg0->unk_84 = mem_pool_alloc(argA, sizeof(unk_func_889000C4));
    ((func889000C4)Memmap_GetFragmentVaddr(Dialog_Create))(arg0->unk_84, arg3 != NULL, arg0->unk_2C, 0, arg9, argA);
    ((func8850068C)Memmap_GetFragmentVaddr(Fragment_SetChild))(arg0, arg0->unk_84);

    temp_s0_7 = mem_pool_alloc(argA, sizeof(char) * 0x80);

    arg0->unk_88 = mem_pool_alloc(argA, sizeof(unk_func_8850878C));
    ((func8850878C)Memmap_GetFragmentVaddr(TextObject_Create))(arg0->unk_88, 0, 0, temp_s0_7, 0x10);
    arg0->unk_88->unk_30 = gDialogDefaultColor;
    arg0->unk_88->unk_44 = arg0->unk_88->unk_44;
}

s32 UIState_Update(TextObjectRenderer* arg0) {
    switch (arg0->unk_74->unk_00.unk_1C) {
        case 0:
            if ((arg0->unk_74->unk_28->unk_20 == 0x100) && (arg0->unk_74->unk_28->unk_24 < 2)) {
                ((func88500A6C)Memmap_GetFragmentVaddr(UIContainer_SetChildCount))(arg0->unk_64, 1);
                ((func88500A6C)Memmap_GetFragmentVaddr(UIContainer_SetChildCount))(arg0->unk_6C,
                                                                       (arg0->unk_74->unk_28->unk_24 == 0) ? 0 : 1);
            } else {
                ((func88500A6C)Memmap_GetFragmentVaddr(UIContainer_SetChildCount))(arg0->unk_64, 0);
                ((func88500A6C)Memmap_GetFragmentVaddr(UIContainer_SetChildCount))(arg0->unk_68, arg0->unk_74->unk_28->unk_24);
            }
            break;

        case 1:
            if (MoveTargetSelector_GetSelection(arg0->unk_30[0]) == 0x30000) {
                ((func88500A6C)Memmap_GetFragmentVaddr(UIContainer_SetChildCount))(arg0->unk_64, 0);
                ((func88500A6C)Memmap_GetFragmentVaddr(UIContainer_SetChildCount))(arg0->unk_68, arg0->unk_74->unk_28->unk_24);
            } else {
                func_88209A88(arg0->unk_70, MenuDualList_GetSelectedItem(arg0->unk_74->unk_2C));
                ((func88500A6C)Memmap_GetFragmentVaddr(UIContainer_SetChildCount))(arg0->unk_64, 2);
            }
            break;
    }

    return 0;
}

s32 UI_HandleInput(TextObjectRenderer* arg0, Controller* arg1) {
    s32 var_v1;

    if (arg0->unk_2C->unk_30 & 2) {
        var_v1 = arg0->unk_74->unk_00.unk_10(&arg0->unk_74->unk_00, arg1);
    } else {
        var_v1 = 1;
    }
    return var_v1;
}

s32 UI_WaitForConfirm(TextObjectRenderer* arg0, Controller* arg1) {
    s32 temp_v0;
    s32 var_s2 = 0;

    arg0->unk_00.unk_24(&arg0->unk_00, 1);

    ((func88502C98)Memmap_GetFragmentVaddr(UIAnimatedElement_WaitForInput))(arg0->unk_2C);

    while (var_s2 == 0) {
        ControllerMsgQueue_SendAndRead(0);

        temp_v0 = arg0->unk_00.unk_20(arg0, gPlayer1Controller);

        if (!(temp_v0 & 1) && (temp_v0 & 2)) {
            var_s2 = 1;
        }

        ((func8850BC94)Memmap_GetFragmentVaddr(Fragment_HandleResult))(temp_v0);
    }

    arg0->unk_2C->unk_2C = 0xB;
    return var_s2;
}

void UI_SetState(TextObjectRenderer* arg0, s32 arg1) {
    arg0->unk_00.unk_2A = arg1;
    ((func8850BF60)Memmap_GetFragmentVaddr(SelectableList_SetSelected))(arg0->unk_74, arg1);
}

void Panel_ToggleAllFills(unk_func_8820B12C_02C* arg0) {
    Panel_ToggleFill(arg0->unk_4C[0]);
    Panel_ToggleFill(arg0->unk_54[0]);
    Panel_ToggleFill(arg0->unk_54[1]);
    Panel_ToggleFill(arg0->unk_4C[1]);
    Panel_ToggleFill(arg0->unk_5C[1]);
}

void UIComponent_SetCallback(unk_func_8820B12C* arg0, TextObjectRenderer* arg1) {
    ((func8850BDF0)Memmap_GetFragmentVaddr(SelectableList_Init))(&arg0->unk_00);

    arg0->unk_00.unk_10 = MainScreen_HandleInput;
    arg0->unk_00.unk_24 = arg1;
}

s32 CheckPokemonDataChanged(unk_func_8820BE14_06C_000* arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 i;
    s32 sp90;
    unk_func_80022C28_ret* temp_v0;
    unk_func_88205880_00D0** var_s1;
    PokemonData sp34;

    sp90 = 0;
    if (arg0->unk_00 == 0) {
        return 0;
    }

    temp_v0 = CreateGbsBlock(arg1, arg2, arg3, 0);
    if (temp_v0 == NULL) {
        return 0;
    }

    arg0->unk_00 = 0;

    if (GetMonBankField(arg1, arg2, arg3) != arg0->unk_04.unk_08) {
        arg0->unk_00 = 1;
        sp90 = 1;
    } else {
        var_s1 = arg0->unk_04.unk_00;

        for (i = 0; i < arg0->unk_04.unk_08; i++, var_s1++) {
            bzero(&sp34, sizeof(PokemonData));
            GbsBlock_ReadPokemon(&sp34, 1, temp_v0);
            if (bcmp(&sp34, *var_s1, sizeof(PokemonData)) != 0) {
                arg0->unk_00 = 1;
                sp90 = 1;
                break;
            }
        }
    }

    CommitAndFreeGbsBlock(temp_v0);

    return sp90;
}

s32 GetChangedBankMask(TextObjectRenderer* arg0) {
    s32 i;
    s32 temp_s2;
    s32 var_s4;
    unk_func_8820BE14_06C_000* var_s1;

    temp_s2 = func_80029080();
    var_s4 = 0;

    var_s1 = arg0->unk_8C[0].unk_00;
    for (i = 0; i < 1; i++) {
        if (CheckPokemonDataChanged(&var_s1[i], 0x20, temp_s2, i) != 0) {
            var_s4 |= 1;
            break;
        }
    }

    var_s1 = arg0->unk_8C[1].unk_00;
    for (i = 0; i < 12; i++) {
        if (CheckPokemonDataChanged(&var_s1[i], 0x21, temp_s2, i) != 0) {
            var_s4 |= 2;
            break;
        }
    }

    var_s1 = arg0->unk_8C[2].unk_00;
    for (i = 0; i < 12; i++) {
        if (CheckPokemonDataChanged(&var_s1[i], 0x11, temp_s2, i) != 0) {
            var_s4 |= 4;
            break;
        }
    }

    return var_s4;
}

s32 IsFirstBankEmpty(TextObjectRenderer* arg0) {
    return arg0->unk_8C->unk_00->unk_04.unk_08 == 0;
}

void WritePokemonGbsBlock(s32 arg0, s32 arg1, s32 arg2, unk_func_88200FA0_030_038* arg3) {
    s32 i;
    unk_func_88205880_00D0** sp28;
    unk_func_80022C28_ret* temp_s3;

    sp28 = arg3->unk_00;
    temp_s3 = CreateGbsBlock(arg0, arg1, arg2, 1);

    for (i = 0; i < arg3->unk_08; i++) {
        func_80022F24(sp28[i], 1, temp_s3);
    }

    if ((arg0 == 0x10) || (arg0 == 0x11) || (arg0 == 0x12)) {
        InvalidateAndFreeGbsBlock(temp_s3);
    } else {
        CommitAndFreeGbsBlock(temp_s3);
    }
}

void func_8820B480(unk_func_88200FA0_030_038* arg0, s32 arg1) {
    s32 i;
    unk_func_88205880_00D0** tmp = arg0->unk_00;

    for (i = 0; i < arg0->unk_08; i++) {
        if ((tmp[i]->unk_000[0].unk_00.unk_00 > 0) && (tmp[i]->unk_000[0].unk_00.unk_00 < 0x98)) {
            func_800256F4(arg1, tmp[i]->unk_000[0].unk_00.unk_00, 3);
        }
    }
}

void SaveChangesAndUpdateUI(TextObjectRenderer* arg0, s32 arg1) {
    s32 i;
    s32 temp_s5;
    unk_func_8820BE14_06C_000* temp_s4;

    temp_s5 = func_80029080();
    ((func88500A6C)Memmap_GetFragmentVaddr(UIContainer_SetChildCount))(arg0->unk_84->unk_40, 2);
    ControllerMsgQueue_SendAndRead(NULL);

    temp_s4 = arg0->unk_8C[0].unk_00;
    for (i = 0; i < 1; i++) {
        if (temp_s4[i].unk_00 != 0) {
            WritePokemonGbsBlock(0x20, temp_s5, i, &temp_s4[i].unk_04);
            func_8820B480(&temp_s4[i].unk_04, temp_s5);
        }
    }

    temp_s4 = arg0->unk_8C[1].unk_00;
    for (i = 0; i < 12; i++) {
        if (temp_s4[i].unk_00 != 0) {
            WritePokemonGbsBlock(0x21, temp_s5, i, &temp_s4[i].unk_04);
            func_8820B480(&temp_s4[i].unk_04, temp_s5);
        }
    }

    temp_s4 = arg0->unk_8C[2].unk_00;
    for (i = 0; i < 12; i++) {
        if (temp_s4[i].unk_00 != 0) {
            WritePokemonGbsBlock(0x11, temp_s5, i, &temp_s4[i].unk_04);
        }
    }

    if (MoveTargetSelector_GetSelection(arg0->unk_30[0]) == 0x30000) {
        func_8002817C(0, 0);
        GbsProcessBankWrites(2);
        GbsSyncBank(2);
    }

    if (arg1 & 4) {
        GbsSyncBank(3);
    }

    if (arg1 & 3) {
        func_80025540(temp_s5);
        ((func88900970)Memmap_GetFragmentVaddr(Dialog_Run))(arg0->unk_84, temp_s5);
    }

    if (arg1 & 4) {
        GbsProcessBankWrites(3);
        GbsSyncBank(3);
    }
}

s32 ShowChangeDialog(TextObjectRenderer* arg0, Controller* arg1) {
    s32 sp34;
    s32 sp30;
    UNUSED s32 pad[2];
    func889006D4 sp24;
    s32 temp_v0_2;

    sp34 = 1;
    sp30 = GetChangedBankMask(arg0);

    if (sp30 != 0) {
        arg0->unk_74->unk_28->unk_14(arg0->unk_74->unk_28, 0);

        sp24 = ((func889006D4)Memmap_GetFragmentVaddr(Dialog_SetEnabled));

        sp24(arg0->unk_84, IsFirstBankEmpty(arg0));

        temp_v0_2 = ((func88900808)Memmap_GetFragmentVaddr(Dialog_WaitForSelection))(arg0->unk_84, arg1, 1);
        if (temp_v0_2 == 0) {
            SaveChangesAndUpdateUI(arg0, sp30);
            ((func889007AC)Memmap_GetFragmentVaddr(Dialog_SetCloseState))(arg0->unk_84);
        } else if (temp_v0_2 == 1) {
            ((func889007AC)Memmap_GetFragmentVaddr(Dialog_SetCloseState))(arg0->unk_84);
        } else if (temp_v0_2 == 2) {
            ((func889007AC)Memmap_GetFragmentVaddr(Dialog_SetCloseState))(arg0->unk_84);
            sp34 = 0;
        }

        arg0->unk_74->unk_28->unk_14(arg0->unk_74->unk_28, 1);
    }
    return sp34;
}

s32 MainScreen_HandleInput(unk_func_8820B12C* arg0, Controller* arg1) {
    static u8 D_88217FBC[] = { 0x18, 0x19, 0x1A };

    s32 i;
    s32 var_s1;
    s32 temp_v0_8;
    unk_func_8820B12C_000* var_a0;
    s32 sp64;
    u32 sp60;
    s32 sp5C;
    s32 sp58;
    s32 sp54;
    s32 sp50;
    char sp30[0x20];

    var_s1 = 0;
    if (arg0->unk_00.unk_20 > 0) {
        var_a0 = arg0->unk_00.unk_04;
        for (i = 0; i < arg0->unk_00.unk_1C; i++) {
            var_a0 = var_a0->unk_08;
        }
        var_s1 = var_a0->unk_10(var_a0, arg1);
    }

    if (var_s1 & 1) {
        return var_s1;
    }

    if (var_s1 == 0) {
        if (arg1->buttonPressed & 0x4000) {
            var_s1 = 0x80000002;
        } else if (arg1->buttonPressed & 0x8000) {
            var_s1 = 0x80000004;
        } else if (arg1->buttonPressed & 0x30) {
            var_s1 = 0x01000000;
        }
    }

    if (var_s1 & 2) {
        switch (arg0->unk_00.unk_1C) {
            case 0:
                PlaySoundEffect(3);
                var_s1 = 2;
                if (ShowChangeDialog(arg0->unk_00.unk_24, arg1) == 0) {
                    var_s1 = 3;
                }
                break;

            case 1:
                ((func8850C064)Memmap_GetFragmentVaddr(Fragment_SetActive))(arg0, 0);
                var_s1 |= 1;
                break;
        }
    } else if (var_s1 & 4) {
        switch (arg0->unk_00.unk_1C) {
            case 1:
                break;

            case 0:
                switch (arg0->unk_28->unk_24) {
                    case 0:
                    case 1:
                        if (arg0->unk_28->unk_24 == 0) {
                            sp64 = 0;
                        } else {
                            sp64 = 1;
                        }
                        PlaySoundEffect(2);
                        Menu_SetStateFlags(arg0->unk_00.unk_24->unk_78[sp64],
                                      MoveTargetSelector_GetSelection(arg0->unk_00.unk_24->unk_30[sp64]));
                        Menu_SetSecondaryFlags(arg0->unk_00.unk_24->unk_78[sp64],
                                      MoveTargetSelector_GetSelection(arg0->unk_00.unk_24->unk_30[1 - sp64]));

                        arg0->unk_28->unk_14(arg0->unk_28, 0x100);

                        if (MenuList_NavigateAndSelect(arg0->unk_00.unk_24->unk_78[sp64], arg1) == 1) {
                            sp60 = Menu_GetStateFlags(arg0->unk_00.unk_24->unk_78[sp64]);
                            Scroll_SetOffset(arg0->unk_00.unk_24->unk_30[sp64], sp60);
                            ScrollableList_SetDataPtr(arg0->unk_00.unk_24->unk_38[sp64],
                                          (u8*)arg0->unk_00.unk_24->unk_8C[sp60 >> 0x10].unk_00 +
                                              (arg0->unk_00.unk_24->unk_8C[sp60 >> 0x10].unk_0C * (sp60 & 0xFFFF)),
                                          sp60);
                        }
                        arg0->unk_28->unk_14(arg0->unk_28, 1);
                        var_s1 = 1;
                        break;

                    case 2:
                        MenuDualList_SetMode(arg0->unk_2C, 0);
                        ((func8850C064)Memmap_GetFragmentVaddr(Fragment_SetActive))(arg0, 1);
                        var_s1 |= 1;
                        break;

                    case 5:
                        MenuDualList_SetMode(arg0->unk_2C, 1);
                        ((func8850C064)Memmap_GetFragmentVaddr(Fragment_SetActive))(arg0, 1);
                        var_s1 |= 1;
                        break;

                    case 4:
                        MenuDualList_SetMode(arg0->unk_2C, 2);
                        ((func8850C064)Memmap_GetFragmentVaddr(Fragment_SetActive))(arg0, 1);
                        var_s1 |= 1;
                        break;

                    case 6:
                        PlaySoundEffect(3);
                        var_s1 = 2;
                        if (ShowChangeDialog(arg0->unk_00.unk_24, arg1) == 0) {
                            var_s1 = 3;
                        }
                        break;

                    case 3:
                        MenuDualList_SetMode(arg0->unk_2C, 3);
                        MenuDualList_SetSelection(arg0->unk_2C, 0);
                        ((func8850C064)Memmap_GetFragmentVaddr(Fragment_SetActive))(arg0, 1);
                        var_s1 |= 1;
                        break;
                    case 7:
                        MenuDualList_SetMode(arg0->unk_2C, 3);
                        MenuDualList_SetSelection(arg0->unk_2C, 1);
                        ((func8850C064)Memmap_GetFragmentVaddr(Fragment_SetActive))(arg0, 1);
                        var_s1 |= 1;
                        break;
                }
                break;
        }
    } else if ((arg0->unk_00.unk_24->unk_40->unk_00.unk_28 & 1) && (var_s1 & 0x01000000)) {
        var_s1 = 1;
        sp5C = (arg1->buttonPressed & 0x20) != 0;
        sp58 = arg0->unk_2C->unk_34;
        switch (arg0->unk_00.unk_1C) {
            case 0:
                sp58 = sp5C;
                break;

            case 1:
                if (MenuDualList_IsStateZero(arg0->unk_2C) != 0) {
                    sp58 = sp5C;
                }
                break;
        }

        if (sp58 != arg0->unk_2C->unk_34) {
            MenuDualList_SwapSublists(arg0->unk_2C);
            Panel_ToggleAllFills(arg0->unk_00.unk_24);
            func_88217BC0(arg0->unk_00.unk_24->unk_40);
            ((func8850BFB0)Memmap_GetFragmentVaddr(SelectableList_UpdateVisuals))(arg0);
            var_s1 = 0x80000005;
        }
    } else if (var_s1 & 0x02000000) {
        ((func8850C064)Memmap_GetFragmentVaddr(Fragment_SetActive))(arg0, 0);

        temp_v0_8 = MoveTargetSelector_GetSelection(arg0->unk_00.unk_24->unk_30[1]);
        sp50 = temp_v0_8 & 0xFFFF;
        sp54 = temp_v0_8 >> 0x10;

        HAL_Strcpy(sp30, GetMessageString(NULL, 0, gMessageBank_2, D_88217FBC[sp54]));

        if ((sp54 == 1) || (sp54 == 2)) {
            sprintf(&sp30[strlen(sp30)], " %d", sp50 + 1);
        }

        MessageBank_SetPointer_0x14_0x2A(0x25, &sp30);
        GetMessageString(arg0->unk_00.unk_24->unk_88->unk_40, 0x80, gMessageBank_2, 0x11);

        ((func8850A10C)Memmap_GetFragmentVaddr(TextBox_Configure))(arg0->unk_00.unk_24->unk_80, arg0->unk_00.unk_24->unk_88,
                                                               2, 0);
        ((func8850A3EC)Memmap_GetFragmentVaddr(Menu_WaitForCancel))(arg0->unk_00.unk_24->unk_80, arg1);

        PlaySoundEffect(0x29);

        var_s1 |= 2;
        if (ShowChangeDialog(arg0->unk_00.unk_24, arg1) == 0) {
            var_s1 |= 1;
        }
    }

    return var_s1;
}

// Inner loops: dead `j = 0;` before LoadPokemonFromSave plus for (j = 0; ...) gives the target's delay-slot
// move; indexing ptr[i] with ptr2 = &ptr[i].unk_04 (count stored through ptr2) puts ptr2 in s0.
void Fragment_Init(TextObjectContext* arg0, s32 arg1, s32 arg2, s32 arg3, MemoryPool* arg4, s32 arg5, char** arg6,
                   char** arg7, char** arg8, char** arg9, char** argA, char** argB) {
    static Color_RGBA8 gUIBorderColor = { 0x1E, 0x50, 0x50, 0xFF };
    static Color_RGBA8 gUIBackgroundColor = { 0x00, 0x0A, 0x0A, 0xFF };

    unk_func_88001300_000* spC4;
    s32 i;
    s32 j;
    unk_func_8820BE14_06C_000* ptr;
    s32 spB4;
    unk_func_8820BE14_06C_000* var_s4;
    UNUSED s32 pad2;
    unk_func_88200FA0_030_038* ptr2;
    s32 count;
    unk_func_8820BE14_06C_000* spA0;
    FragmentEntry temp_v0_7;
    unk_func_88500EE4* temp_s0;
    unk_func_88001300_000* temp_s0_4;
    unk_func_88509A2C* temp_s1;
    unk_func_88509E34* temp_s1_2;
    unk_func_885088F4* temp_s2;
    PokemonData* temp_v0_5;
    unk_func_882062E4* var_s1;
    UNUSED s32 pad[5];

    spA0 = NULL;

    ((func885007CC)Memmap_GetFragmentVaddr(func_885007CC))(arg0, 0x9C);

    arg0->unk_00.unk_10.unk_00 = arg1;
    arg0->unk_00.unk_10.unk_02 = arg2;

    spB4 = func_80029080();

    var_s1 = mem_pool_alloc(arg4, sizeof(unk_func_882062E4) * (6 + (12 * 20) * 2));
    bzero(var_s1, sizeof(unk_func_882062E4) * (6 + (12 * 20) * 2));

    List_Init(&arg0->unk_6C, 0x10, 1, arg4);
    List_Init(&arg0->unk_7C, 0x10, 12, arg4);
    List_Init(&arg0->unk_8C, 0x10, 12, arg4);

    arg0->unk_6C.unk_08 = 1;
    ptr = arg0->unk_6C.unk_00;
    for (i = 0; i < 1; i++) {
        PtrList_Init(&ptr[i].unk_04, 6, arg4);
    }

    arg0->unk_7C.unk_08 = 12;
    ptr = arg0->unk_7C.unk_00;
    for (i = 0; i < 12; i++) {
        PtrList_Init(&ptr[i].unk_04, 20, arg4);
    }

    arg0->unk_8C.unk_08 = 12;
    ptr = arg0->unk_8C.unk_00;
    for (i = 0; i < 12; i++) {
        PtrList_Init(&ptr[i].unk_04, 20, arg4);
    }

    if (func_8002513C(spB4) == 0) {
        func_80024208(spB4);
    }

    ptr = var_s4 = arg0->unk_6C.unk_00;
    for (i = 0; i < 1; i++, var_s4++) {
        j = 0;
        count = LoadPokemonFromSave(var_s1, 6, 0x20, spB4, i);
        ptr2 = &ptr[i].unk_04;
        ptr2->unk_08 = count;

        for (j = 0; j < count; j++) {
            ptr2->unk_00[j] = var_s1++;
        }

        var_s4->unk_00 = 0;
    }

    ptr = var_s4 = arg0->unk_7C.unk_00;
    for (i = 0; i < 12; i++, var_s4++) {
        j = 0;
        count = LoadPokemonFromSave(var_s1, 20, 0x21, spB4, i);
        ptr2 = &ptr[i].unk_04;
        ptr2->unk_08 = count;

        for (j = 0; j < count; j++) {
            ptr2->unk_00[j] = var_s1++;
        }

        var_s4->unk_00 = 0;
    }

    ptr = var_s4 = arg0->unk_8C.unk_00;
    for (i = 0; i < 12; i++, var_s4++) {
        j = 0;
        count = LoadPokemonFromSave(var_s1, 20, 0x11, 0, i);
        ptr2 = &ptr[i].unk_04;
        ptr2->unk_08 = count;

        for (j = 0; j < count; j++) {
            ptr2->unk_00[j] = var_s1++;
        }

        var_s4->unk_00 = 0;
    }

    if (arg3 == 1) {
        temp_v0_5 = mem_pool_alloc(arg4, sizeof(PokemonData));
        InitMonData(temp_v0_5);

        spA0 = mem_pool_alloc(arg4, sizeof(unk_func_8820BE14_06C_000));
        PtrList_Init(&spA0->unk_04, 1, arg4);

        spA0->unk_04.unk_08 = 1;
        *spA0->unk_04.unk_00 = temp_v0_5;
        spA0->unk_00 = 0;
    }

    spC4 = mem_pool_alloc(arg4, sizeof(unk_func_88001300_000));
    ((func885031E8)Memmap_GetFragmentVaddr(UIElementBase_Create))(spC4, 0, 0, 0x280, 0x1E0);
    ((func8850068C)Memmap_GetFragmentVaddr(Fragment_SetChild))(arg0, spC4);

    temp_s0 = mem_pool_alloc(arg4, sizeof(unk_func_88500EE4));
    ((func88500EE4)Memmap_GetFragmentVaddr(UIColoredTextureRect_Create))(temp_s0, 0, 0, 0x280, 0x1E0, D_88223E48, gUIBorderColor,
                                                           gUIBackgroundColor);
    ((func8850068C)Memmap_GetFragmentVaddr(Fragment_SetChild))(spC4, temp_s0);

    temp_s2 = mem_pool_alloc(arg4, sizeof(unk_func_885088F4));
    ((func885088F4)Memmap_GetFragmentVaddr(ProgressBarFragment_Create))(temp_s2, 0x41, 0x15C, 0xDC);
    temp_s2->unk_2C = 5;
    ((func8850068C)Memmap_GetFragmentVaddr(Fragment_SetChild))(spC4, temp_s2);

    temp_s1 = mem_pool_alloc(arg4, sizeof(unk_func_88509A2C));
    ((func88509A2C)Memmap_GetFragmentVaddr(TrainerMoveInfoFragment_Create))(temp_s1, 0x38, 0x22, func_80029080(),
                                                           GetMessageString(NULL, 0, gMessageBank_2A, 0));
    ((func8850068C)Memmap_GetFragmentVaddr(Fragment_SetChild))(temp_s2, temp_s1);

    temp_s1_2 = mem_pool_alloc(arg4, sizeof(unk_func_88509E34));
    ((func88509E34)Memmap_GetFragmentVaddr(LabelFragment_Create))(temp_s1_2, 0, 0, GetMessageString(NULL, 0, gMessageBank_2, 0));
    ((func8850068C)Memmap_GetFragmentVaddr(Fragment_SetChild))(temp_s2, temp_s1_2);

    temp_s0_4 = mem_pool_alloc(arg4, sizeof(unk_func_88001300_000));
    ((func885031E8)Memmap_GetFragmentVaddr(UIElementBase_Create))(temp_s0_4, 0, 0, 0x280, 0x1E0);
    ((func8850068C)Memmap_GetFragmentVaddr(Fragment_SetChild))(arg0, temp_s0_4);

    temp_v0_7 = FRAGMENT_LOAD(fragment27);

    arg0->unk_30.unk_04 = arg4;
    arg0->unk_30.unk_00 = 0x38, arg0->unk_30.unk_02 = 0x52;
    arg0->unk_30.unk_14 = temp_s0_4;
    arg0->unk_30.unk_18 = 0;

    arg0->unk_4C = arg7;
    arg0->unk_50 = gMessageBank_24;
    arg0->unk_54 = gMessageBank_25;
    arg0->unk_58 = arg8;
    arg0->unk_5C = arg9;
    arg0->unk_60 = argA;
    arg0->unk_64 = argB;

    temp_v0_7(0, &arg0->unk_30);

    arg0->unk_68 = mem_pool_alloc(arg4, sizeof(TextObjectGraphics));
    ((func88509F48)Memmap_GetFragmentVaddr(TextObjectGraphics_Init))(arg0->unk_68, 0x2C, 0x4C, 0x228, 0x160, arg4, arg5);

    arg0->unk_2C = mem_pool_alloc(arg4, sizeof(TextObjectRenderer));
    TextObjectRenderer_Init(arg0->unk_2C, 0x2C, 0x4C, spA0, &arg0->unk_6C, spC4, temp_v0_7, &arg0->unk_30, arg0->unk_68, arg6,
                  arg4);

    ((func8850068C)Memmap_GetFragmentVaddr(Fragment_SetChild))(temp_s0_4, arg0->unk_2C);
    ((func8850068C)Memmap_GetFragmentVaddr(Fragment_SetChild))(&arg0->unk_00, arg0->unk_30.unk_08);
    ((func8850068C)Memmap_GetFragmentVaddr(Fragment_SetChild))(temp_s0_4, arg0->unk_68);
}

void TextObject_MainLoop(TextObjectContext* arg0) {
    volatile s32 sp34 = 0;

    while (sp34 == 0) {
        Gfx_FinishFrame();
        Stage_BeginDisplayList();

        ((func885008C4)Memmap_GetFragmentVaddr(TextObject_Render))(&arg0->unk_00);
        ((func88500828)Memmap_GetFragmentVaddr(TextObject_PostRender))(&arg0->unk_00, 0, 0);

        Stage_Advance();
        ControllerMsgQueue_Recv(&sp34);
    }
}

void TextObject_WaitForClose(TextObjectContext* arg0) {
    s32 sp24 = UI_WaitForConfirm(arg0->unk_2C, gPlayer1Controller);

    while (arg0->unk_2C->unk_2C->unk_00.unk_28 & 1) {
        ControllerMsgQueue_SendAndRead(0);
    }

    ControllerMsgQueue_SendAndRead(sp24);
    osStopThread(NULL);
}

void TextObject_FadeInOutAndClose(TextObjectContext* arg0) {
    s32 sp24;
    s32 var_s0;

    Stage_FadeIn(8);

    var_s0 = 8;
    while (var_s0-- > 0) {
        ControllerMsgQueue_SendAndRead(NULL);
    }

    sp24 = UI_WaitForConfirm(arg0->unk_2C, gPlayer1Controller);

    while (arg0->unk_2C->unk_2C->unk_00.unk_28 & 1) {
        ControllerMsgQueue_SendAndRead(NULL);
    }

    Stage_FadeOut(8);

    var_s0 = 10;
    while (var_s0-- > 0) {
        ControllerMsgQueue_SendAndRead(NULL);
    }

    ControllerMsgQueue_SendAndRead(sp24);

    osStopThread(NULL);
}

void TextObject_Show(TextObject* arg0, s32 arg1) {
    static ThreadEntries gTextObjectThreadFuncs[] = { TextObject_WaitForClose, TextObject_FadeInOutAndClose };

    MemoryPool* sp5C;
    void* sp58;
    u8* sp54;
    TextObjectThreadData* sp50;
    char** sp4C;
    char** sp48;
    char** sp44;
    char** sp40;
    char** sp3C;
    char** sp38;

    main_pool_push_state('OTPC');

    FRAGMENT_LOAD(fragment25);

    SpriteAssets_Load();

    sp54 = main_pool_alloc(0x10000, 0);
    sp5C = mem_pool_try_init(0x18000, 0);

    if (arg1 == 1) {
        GbsEnsureBankLoaded(2);
    }
    MessageBank_Init();

    gMessageBank_2A = GetMessageBank(0x2A);
    gMessageBank_2 = GetMessageBank(2);
    gMessageBank_24 = GetMessageBank(0x24);
    gMessageBank_25 = GetMessageBank(0x25);

    sp4C = GetMessageBank(7);
    sp48 = GetMessageBank(6);
    sp44 = GetMessageBank(0x26);
    sp40 = GetMessageBank(0x28);
    sp3C = GetMessageBank(0x29);
    sp38 = GetMessageBank(0xB);

    sp58 = mem_pool_alloc(sp5C, sizeof(TextObjectContext));
    Fragment_Init(sp58, 0, 0, arg1, sp5C, arg0, sp4C, sp48, sp44, sp40, sp3C, sp38);

    sp50 = ALIGN16((u32)mem_pool_alloc(sp5C, sizeof(TextObjectThreadData)));

    osCreateThread(&sp50->thread, 0x32, gTextObjectThreadFuncs[arg1], sp58, sp54 + 0x10000, osGetThreadPri(NULL) - 1);

    ControllerMsgQueue_Init();
    MenuInput_SetController(gPlayer1Controller);

    osStartThread(&sp50->thread);

    TextObject_MainLoop(sp58);

    osDestroyThread(&sp50->thread);

    main_pool_pop_state('OTPC');
}
