#include "fragment62.h"
#include "src/1CF30.h"
#include "src/20470.h"
#include "src/225A0.h"
#include "src/29BA0.h"
#include "src/2E110.h"
#include "src/3D140.h"
#include "src/6A40.h"
#include "src/6BC0.h"
#include "src/F420.h"
#include "src/controller.h"
#include "src/memmap.h"
#include "src/memory.h"
#include "stdarg.h"

unk_D_843901A0* gBattleMessageBuffers;

static u8 D_84385990[] = { 0xE, 0x4A };
static u8 D_84385994[] = { 0x60, 0x69, 0x75, 0x78, 0x85 };
static u8 D_8438599C[] = { 0x61, 0x64, 0x66, 0x68, 0x8C };
static u8 D_843859A4[] = {
    1,    0xA,  0xB,  0x11, 0x13, 0x14, 0x15, 0x1E, 0x22, 0x23, 0x25, 0x27, 0x2B, 0x2C, 0x2D, 0x2E,
    0x2F, 0x40, 0x44, 0x46, 0x47, 0x51, 0x59, 0x5A, 0x5B, 0x5C, 0x67, 0x6A, 0x6B, 0x6E, 0x6F, 0x76,
    0x7A, 0x80, 0x84, 0x8B, 0x8D, 0x91, 0x94, 0x96, 0x97, 0x9A, 0x9C, 0x9F, 0xA3, 0xA4,
};

void ResetDialogBuffers(void) {
    gBattleMessageBuffers->unk_088[0] = 0;
    gBattleMessageBuffers->unk_088[1] = 0;
    gBattleMessageBuffers->unk_0C8[0] = 0;
    gBattleMessageBuffers->unk_0C8[1] = 0;
    gBattleMessageBuffers->unk_108[0] = 0;
    gBattleMessageBuffers->unk_108[1] = 0;
    gBattleMessageBuffers->unk_148[0] = 0;
    gBattleMessageBuffers->unk_148[1] = 0;
    gBattleMessageBuffers->unk_188[0] = 0;
    gBattleMessageBuffers->unk_188[1] = 0;
    gBattleMessageBuffers->unk_1C8[0] = 0;
    gBattleMessageBuffers->unk_1C8[1] = 0;
    gBattleMessageBuffers->unk_448[0][0] = 0;
    gBattleMessageBuffers->unk_448[0][1] = 0;
    gBattleMessageBuffers->unk_448[1][0] = 0;
    gBattleMessageBuffers->unk_448[1][1] = 0;
    gBattleMessageBuffers->unk_208[0] = 0;
    gBattleMessageBuffers->unk_208[1] = 0;
    gBattleMessageBuffers->unk_308[0] = 0;
    gBattleMessageBuffers->unk_308[1] = 0;
    gBattleMessageBuffers->unk_2C8[0] = 0;
    gBattleMessageBuffers->unk_2C8[1] = 0;
    gBattleMessageBuffers->unk_348[0] = 0;
    gBattleMessageBuffers->unk_348[1] = 0;
    gBattleMessageBuffers->unk_388[0] = 0;
    gBattleMessageBuffers->unk_388[1] = 0;
    gBattleMessageBuffers->unk_3C8[0] = 0;
    gBattleMessageBuffers->unk_3C8[1] = 0;
    gBattleMessageBuffers->unk_408[0] = 0;
    gBattleMessageBuffers->unk_408[1] = 0;
}

void ResetMessageIndices(void) {
    gBattleMessageBuffers->unk_004 = 0;
    gBattleMessageBuffers->unk_048[0] = 0;
    gBattleMessageBuffers->unk_048[1] = 0;
    gBattleMessageBuffers->unk_008[0] = 0;
    gBattleMessageBuffers->unk_008[1] = 0;
}

void SimpleStringFormat(s8* arg0, s8* arg1, ...) {
    va_list args;
    s8* src;
    s8* fmt;
    s32 len;

    len = 0;
    va_start(args, arg1);
    fmt = arg1;

    while (*fmt != 0) {
        if (*fmt != 0x25) {
            arg0[len++] = *fmt;
        } else {
            fmt++;
            if (*fmt == 0x73) {
                src = va_arg(args, s8*);
                while (*src != 0) {
                    arg0[len] = *src;
                    src++;
                    len++;
                }
            }
        }
        fmt++;
    }
    arg0[len] = 0;
}

void WriteMessageCharOrString(s8* arg0, s8 arg1) {
    u8 tmp = arg1;
    *arg0 = arg1;

    if (tmp >= 0x80) {
        if ((tmp - 0x80) >= 0xB) {
            GetMessageString(arg0 + 1, 0x40, gMessageBank_0x1E, tmp - 0x48);
        } else {
            GetMessageString(arg0 + 1, 0x40, gMessageBank_0x1E, tmp - 0x49);
        }
    } else {
        GetMessageString(arg0 + 1, 0x40, gMessageBank_0x1E, gMessageIdLookup[arg1]);
    }
}

void InitDialogHeader(char* arg0, s32 arg1) {
    UNUSED s32 pad[3];
    unk_BattlePlayerAnimState* sp28 = &D_84390010[arg1]->unk_654;
    UNUSED s32 pad2[2];

    ResetMessageIndices();
    gBattleMessageBuffers->unk_000 = D_84390010[arg1]->unk_720->unk_08[sp28->unk_2B]->unk_001;
    SimpleStringFormat(gBattleMessageBuffers->unk_048, arg0 + 1);
    *arg0 = 0;
}

void func_84317B38(void) {
}

void InitBattleDialogParameters(void) {
    unk_BattlePlayerEntity* ptr1 = D_84390010[0];
    unk_BattlePlayerEntity* ptr2 = D_84390010[1];

    if ((gBattleContext.unk_0000 != 0x10) && (gBattleState.unk_00->unk_30 == 0)) {
        func_8431595C(ptr1, 0x15, 0xF, ptr1->unk_720->unk_08[ptr1->unk_728.unk_16C]->unk_001);
        func_8431595C(ptr2, 0xE1, 0xF, ptr2->unk_720->unk_08[ptr2->unk_728.unk_16C]->unk_001);
    }
}

void DetermineMessageCategoryAndDisplay(void) {
    u32 sp1C;
    unk_D_800FCB18* sp18 = &D_84390010[gBattleState.unk_00->unk_2C]->unk_654.unk_38;

    sp18->unk_58 = sp18->unk_44.unk_00;

    if (Array_ContainsValue(sp18->unk_44.unk_00, D_84385990, 2) != 0) {
        sp1C = 0;
    } else if (Array_ContainsValue(sp18->unk_44.unk_00, D_84385994, 5) != 0) {
        sp1C = 1;
    } else if (Array_ContainsValue(sp18->unk_44.unk_00, D_8438599C, 5) != 0) {
        sp1C = 2;
    } else if (Array_ContainsValue(sp18->unk_44.unk_00, D_843859A4, 0x2E) != 0) {
        sp1C = 3;
    } else {
        sp1C = 4;
    }

    if ((sp18->unk_44.unk_00 == 0x76) || (sp18->unk_44.unk_00 == 0x77)) {
        MessageBank_SetPointer_0x14_0x2A(0x19, GetPokemonName(D_84390010[gBattleState.unk_00->unk_2C]));
        MessageBank_SetPointer_0x14_0x2A(0x1D, GetPokemonMessageString(D_84390010[gBattleState.unk_00->unk_2C]));

        switch (sp1C) {
            case 0:
                WriteMessageCharOrString(gBattleMessageBuffers->unk_388, 0x14);
                break;

            case 1:
                WriteMessageCharOrString(gBattleMessageBuffers->unk_388, 0x15);
                break;

            case 2:
                WriteMessageCharOrString(gBattleMessageBuffers->unk_388, 0x16);
                break;

            case 3:
                WriteMessageCharOrString(gBattleMessageBuffers->unk_388, 0x17);
                break;

            case 4:
                WriteMessageCharOrString(gBattleMessageBuffers->unk_388, 0x18);
                break;
        }
    } else {
        MessageBank_SetPointer_0x14_0x2A(0x19, GetPokemonName(D_84390010[gBattleState.unk_00->unk_2C]));
        MessageBank_SetPointer_0x14_0x2A(0x1D, GetPokemonMessageString(D_84390010[gBattleState.unk_00->unk_2C]));

        switch (sp1C) {
            case 0:
                WriteMessageCharOrString(gBattleMessageBuffers->unk_0C8, 0x14);
                break;

            case 1:
                WriteMessageCharOrString(gBattleMessageBuffers->unk_0C8, 0x15);
                break;

            case 2:
                WriteMessageCharOrString(gBattleMessageBuffers->unk_0C8, 0x16);
                break;

            case 3:
                WriteMessageCharOrString(gBattleMessageBuffers->unk_0C8, 0x17);
                break;

            case 4:
                WriteMessageCharOrString(gBattleMessageBuffers->unk_0C8, 0x18);
                break;
        }
    }
}

void func_84317EDC(void) {
    u32 sp24;
    UNUSED s32 pad;
    unk_D_800FCB18* sp1C = &D_84390010[gBattleState.unk_00->unk_2C]->unk_654.unk_38;

    if (Array_ContainsValue(sp1C->unk_5A, D_84385990, 2) != 0) {
        sp24 = 0;
    } else if (Array_ContainsValue(sp1C->unk_5A, D_84385994, 5) != 0) {
        sp24 = 1;
    } else if (Array_ContainsValue(sp1C->unk_5A, D_8438599C, 5) != 0) {
        sp24 = 2;
    } else if (Array_ContainsValue(sp1C->unk_5A, D_843859A4, 0x2E) != 0) {
        sp24 = 3;
    } else {
        sp24 = 4;
    }

    MessageBank_SetPointer_0x14_0x2A(0x19, GetPokemonName(D_84390010[gBattleState.unk_00->unk_2C]));
    MessageBank_SetPointer_0x14_0x2A(0x1D, GetPokemonMessageString(D_84390010[gBattleState.unk_00->unk_2C]));

    switch (sp24) {
        case 0:
            WriteMessageCharOrString(gBattleMessageBuffers->unk_0C8, 0x14);
            break;

        case 1:
            WriteMessageCharOrString(gBattleMessageBuffers->unk_0C8, 0x15);
            break;

        case 2:
            WriteMessageCharOrString(gBattleMessageBuffers->unk_0C8, 0x16);
            break;

        case 3:
            WriteMessageCharOrString(gBattleMessageBuffers->unk_0C8, 0x17);
            break;

        case 4:
            WriteMessageCharOrString(gBattleMessageBuffers->unk_0C8, 0x18);
            break;
    }
}

void func_843180AC(void) {
    s32 sp2C;
    s32 tmp;
    unk_D_800FCB18* sp24;

    sp24 = &D_84390010[gBattleState.unk_00->unk_2C]->unk_654.unk_38;

    if (Array_ContainsValue(sp24->unk_5A, D_84385990, 2) != 0) {
        sp2C = 0;
    } else if (Array_ContainsValue(sp24->unk_5A, D_84385994, 5) != 0) {
        sp2C = 1;
    } else if (Array_ContainsValue(sp24->unk_5A, D_8438599C, 5) != 0) {
        sp2C = 2;
    } else if (Array_ContainsValue(sp24->unk_5A, D_843859A4, 0x2E) != 0) {
        sp2C = 3;
    } else {
        sp2C = 4;
    }

    if (sp24->unk_5A == 0x76) {
        do {
            tmp = GetRandomU8();
        } while ((tmp == 0) || (tmp >= 0xA5) || tmp == 0x76);

        sp24->unk_5A = tmp;

        MessageBank_SetPointer_0x14_0x2A(0x19, GetPokemonName(D_84390010[gBattleState.unk_00->unk_2C]));
        MessageBank_SetPointer_0x14_0x2A(0x1D, GetPokemonMessageString(D_84390010[gBattleState.unk_00->unk_2C]));

        switch (sp2C) {
            case 0:
                WriteMessageCharOrString(gBattleMessageBuffers->unk_0C8, 0x14);
                break;

            case 1:
                WriteMessageCharOrString(gBattleMessageBuffers->unk_0C8, 0x15);
                break;

            case 2:
                WriteMessageCharOrString(gBattleMessageBuffers->unk_0C8, 0x16);
                break;

            case 3:
                WriteMessageCharOrString(gBattleMessageBuffers->unk_0C8, 0x17);
                break;

            case 4:
                WriteMessageCharOrString(gBattleMessageBuffers->unk_0C8, 0x18);
                break;
        }

        sp24->unk_5A = 0x76;

        MessageBank_SetPointer_0x14_0x2A(0x19, GetPokemonName(D_84390010[gBattleState.unk_00->unk_2C]));
        MessageBank_SetPointer_0x14_0x2A(0x1D, GetPokemonMessageString(D_84390010[gBattleState.unk_00->unk_2C]));

        switch (sp2C) {
            case 0:
                WriteMessageCharOrString(gBattleMessageBuffers->unk_388, 0x14);
                break;

            case 1:
                WriteMessageCharOrString(gBattleMessageBuffers->unk_388, 0x15);
                break;

            case 2:
                WriteMessageCharOrString(gBattleMessageBuffers->unk_388, 0x16);
                break;

            case 3:
                WriteMessageCharOrString(gBattleMessageBuffers->unk_388, 0x17);
                break;

            case 4:
                WriteMessageCharOrString(gBattleMessageBuffers->unk_388, 0x18);
                break;
        }
    } else {
        MessageBank_SetPointer_0x14_0x2A(0x19, GetPokemonName(D_84390010[gBattleState.unk_00->unk_2C]));
        MessageBank_SetPointer_0x14_0x2A(0x1D, GetPokemonMessageString(D_84390010[gBattleState.unk_00->unk_2C]));

        switch (sp2C) {
            case 0:
                WriteMessageCharOrString(gBattleMessageBuffers->unk_0C8, 0x14);
                break;

            case 1:
                WriteMessageCharOrString(gBattleMessageBuffers->unk_0C8, 0x15);
                break;

            case 2:
                WriteMessageCharOrString(gBattleMessageBuffers->unk_0C8, 0x16);
                break;

            case 3:
                WriteMessageCharOrString(gBattleMessageBuffers->unk_0C8, 0x17);
                break;

            case 4:
                WriteMessageCharOrString(gBattleMessageBuffers->unk_0C8, 0x18);
                break;
        }
    }
}

void Dialog_SetMode(s32 arg0) {
    unk_D_843901A0_4C8* ptr = &gBattleMessageBuffers->unk_4C8;

    ptr->unk_00 = 0;
    ptr->unk_04 = arg0;
}

void Dialog_Clear(void) {
    unk_D_843901A0_4C8* ptr = &gBattleMessageBuffers->unk_4C8;

    ptr->unk_00 = 0xFF;
}

void ProcessMessageCommand(s8* arg0) {
    s32 temp_v0;

    if (arg0[1] == '\x00') {
        return;
    }

    temp_v0 = arg0[0] & 0x7F;

    if ((arg0[0] & 0x80) == '\x00') {
        ProcessCommandQueue(arg0[0]);
    } else if (temp_v0 == 'Q') {
        ProcessCommandQueue(0xBC);
    } else if (temp_v0 == 'R') {
        ProcessCommandQueue(0xB5);
    } else if (temp_v0 == 'S') {
        ProcessCommandQueue(0xB6);
    } else if (temp_v0 == 'T') {
        ProcessCommandQueue(0xB7);
    } else if (temp_v0 == 'U') {
        ProcessCommandQueue(0xB8);
    } else if (temp_v0 == 'V') {
        ProcessCommandQueue(0xB9);
    } else if (temp_v0 == 'W') {
        ProcessCommandQueue(0xBA);
    } else if (temp_v0 == 'X') {
        ProcessCommandQueue(0xBB);
    } else {
        ProcessCommandQueue(temp_v0 + 0x64);
    }
}

void RenderDialogBox(unk_D_843901A0_4C8* arg0, s16 arg1, s16 arg2) {
    UNUSED s32 pad;
    s32 temp_s1;

    if (1) {}

    switch (arg0->unk_04) {
        case 0:
            if (Dialog_PrintLineIfSet(&gBattleMessageBuffers->unk_388[1], arg1 + 4, arg2 + (arg0->unk_10 * 0xC) + 3) != 0) {
                arg0->unk_10 += 1;
            }

            if (Dialog_PrintLineIfSet(&gBattleMessageBuffers->unk_0C8[1], arg1 + 4, arg2 + (arg0->unk_10 * 0xC) + 3) != 0) {
                arg0->unk_10 += 1;
            }

            if (Dialog_PrintLineIfSet(&gBattleMessageBuffers->unk_188[1], arg1 + 4, arg2 + (arg0->unk_10 * 0xC) + 3) != 0) {
                arg0->unk_10 += 1;
            }
            break;

        case 3:
            if (Dialog_PrintLineIfSet(&gBattleMessageBuffers->unk_088[1], arg1 + 4, arg2 + (arg0->unk_10 * 0xC) + 3) != 0) {
                arg0->unk_10 += 1;
            }

            if (Dialog_PrintLineIfSet(&gBattleMessageBuffers->unk_148[1], arg1 + 4, arg2 + (arg0->unk_10 * 0xC) + 3) != 0) {
                arg0->unk_10 += 1;
            }

            if (Dialog_PrintLineIfSet(&gBattleMessageBuffers->unk_208[1], arg1 + 4, arg2 + (arg0->unk_10 * 0xC) + 3) != 0) {
                arg0->unk_10 += 1;
            }
            break;

        case 1:
            if (Dialog_PrintLineIfSet(&gBattleMessageBuffers->unk_3C8[1], arg1 + 4, arg2 + (arg0->unk_10 * 0xC) + 3) != 0) {
                arg0->unk_10 += 1;
            }

            if (Dialog_PrintLineIfSet(&gBattleMessageBuffers->unk_088[1], arg1 + 4, arg2 + (arg0->unk_10 * 0xC) + 3) != 0) {
                arg0->unk_10 += 1;
            }

            if (Dialog_PrintLineIfSet(&gBattleMessageBuffers->unk_148[1], arg1 + 4, arg2 + (arg0->unk_10 * 0xC) + 3) != 0) {
                arg0->unk_10 += 1;
            }

            if ((arg0->unk_10 < 3) &&
                (Dialog_PrintLineIfSet(&gBattleMessageBuffers->unk_208[1], arg1 + 4, arg2 + (arg0->unk_10 * 0xC) + 3) != 0)) {
                arg0->unk_10 += 1;
            }
            break;

        case 2:
            if (Dialog_PrintLineIfSet(&gBattleMessageBuffers->unk_088[1], arg1 + 4, arg2 + (arg0->unk_10 * 0xC) + 3) != 0) {
                arg0->unk_10 += 1;
            }

            if (Dialog_PrintLineIfSet(&gBattleMessageBuffers->unk_148[1], arg1 + 4, arg2 + (arg0->unk_10 * 0xC) + 3) != 0) {
                arg0->unk_10 += 1;
            }

            if (Dialog_PrintLineIfSet(&gBattleMessageBuffers->unk_208[1], arg1 + 4, arg2 + (arg0->unk_10 * 0xC) + 3) != 0) {
                arg0->unk_10 += 1;
            }
            break;

        case 4:
            Dialog_PrintLineIfSet(&gBattleMessageBuffers->unk_248[1], arg1 + 4, arg2 + 3);
            break;

        case 5:
            Dialog_PrintLineIfSet(&gBattleMessageBuffers->unk_288[1], arg1 + 4, arg2 + 3);
            break;

        case 6:
            Dialog_PrintLineIfSet(&gBattleMessageBuffers->unk_408[1], arg1 + 4, arg2 + 3);
            break;

        case 7:
            Dialog_PrintLineIfSet(&gBattleMessageBuffers->unk_348[1], arg1 + 4, arg2 + 3);
            Dialog_PrintLineIfSet(&gBattleMessageBuffers->unk_2C8[1], arg1 + 4, arg2 + 0x10);
            break;

        case 8:
            Dialog_PrintLineIfSet(&gBattleMessageBuffers->unk_448[arg0->unk_0C][1], arg1 + 4, arg2 + 3);
            break;

        case 9:
        case 10:
            Dialog_PrintLineIfSet(&gBattleMessageBuffers->unk_1C8[1], arg1 + 4, arg2 + 3);
            break;

        case 11:
            Dialog_PrintLineIfSet(&gBattleMessageBuffers->unk_088[1], arg1 + 4, arg2 + 3);
            break;

        case 12:
            Dialog_PrintLineIfSet(&gBattleMessageBuffers->unk_088[1], arg1 + 4, arg2 + 3);
            break;

        case 13:
            temp_s1 = MeasureTextWidth(1, 0, GetMessageString(NULL, 0, gMessageBank_0x1E, 0xA4)) / 2;
            Dialog_PrintLineIfSet(GetMessageString(NULL, 0, gMessageBank_0x1E, 0xA4), 0xA1 - temp_s1, 0x71);
            break;

        case 14:
            func_84317004();
            break;

        case 15:
            Dialog_PrintLineIfSet(&gBattleMessageBuffers->unk_088[1], arg1 + 4, arg2 + (arg0->unk_10 * 0xC) + 3);
            break;
    }

    arg0->unk_10 = 0;
}

s32 func_84318CE4(unk_D_843901A0_4C8* arg0) {
    unk_D_843901A0* temp_v0;
    s32 tmp;

    arg0->unk_10 = 0;

    switch (arg0->unk_04) {
        case 0:
            if ((gBattleMessageBuffers->unk_0C8[1] == 0) && (gBattleMessageBuffers->unk_388[1] == 0) && (gBattleMessageBuffers->unk_188[1] == 0)) {
                arg0->unk_00 = 0xFF;
                return 1;
            }

            arg0->unk_0C = gBattleState.unk_00->unk_2C;
            if (gBattleMessageBuffers->unk_0C8[1] != 0) {
                ProcessMessageCommand(gBattleMessageBuffers->unk_0C8);
            }

            if (gBattleMessageBuffers->unk_388[1] != 0) {
                ProcessMessageCommand(gBattleMessageBuffers->unk_388);
            }

            if (gBattleMessageBuffers->unk_188[1] != 0) {
                ProcessMessageCommand(gBattleMessageBuffers->unk_188);
            }
            arg0->unk_00 += 1;
            break;

        case 1:
        case 3:
            arg0->unk_0C = gBattleState.unk_00->unk_2C;
            ProcessMessageCommand(gBattleMessageBuffers->unk_088);
            ProcessMessageCommand(gBattleMessageBuffers->unk_148);
            ProcessMessageCommand(gBattleMessageBuffers->unk_208);
            ProcessMessageCommand(gBattleMessageBuffers->unk_3C8);
            ProcessMessageCommand(gBattleMessageBuffers->unk_308);
            if ((gBattleMessageBuffers->unk_088[1] == 0) && (gBattleMessageBuffers->unk_148[1] == 0) && (gBattleMessageBuffers->unk_208[1] == 0) &&
                (gBattleMessageBuffers->unk_3C8[1] == 0) && (gBattleMessageBuffers->unk_308[1] == 0)) {
                arg0->unk_00 = 0xFF;
                return 1;
            }
            arg0->unk_00 += 1;
            break;

        case 2:
            arg0->unk_0C = gBattleState.unk_00->unk_2C;
            ProcessMessageCommand(gBattleMessageBuffers->unk_088);
            ProcessMessageCommand(gBattleMessageBuffers->unk_148);
            ProcessMessageCommand(gBattleMessageBuffers->unk_208);
            if ((gBattleMessageBuffers->unk_088[1] == 0) && (gBattleMessageBuffers->unk_148[1] == 0) && (gBattleMessageBuffers->unk_208[1] == 0)) {
                arg0->unk_00 = 0xFF;
                return 1;
            }
            arg0->unk_00 += 1;
            break;

        case 15:
            arg0->unk_0C = gBattleState.unk_00->unk_2C;
            ProcessMessageCommand(gBattleMessageBuffers->unk_088);
            if (gBattleMessageBuffers->unk_088[1] == 0) {
                arg0->unk_00 = 0xFF;
                return 1;
            }
            arg0->unk_00 += 1;
            break;

        case 8:
            if (gBattleMessageBuffers->unk_448[arg0->unk_0C][1] == 0) {
                arg0->unk_00 = 0xFF;
                return 1;
            }
            tmp = gBattleState.unk_00->unk_2C == 0;
            arg0->unk_00 += 1;
            arg0->unk_0C = tmp;
            break;

        case 9:
            tmp = gBattleState.unk_00->unk_2C == 0;
            arg0->unk_00 += 1;
            arg0->unk_0C = tmp;
            break;

        case 4:
        case 5:
        case 6:
            ProcessMessageCommand(gBattleMessageBuffers->unk_248);
            ProcessMessageCommand(gBattleMessageBuffers->unk_288);
            ProcessMessageCommand(gBattleMessageBuffers->unk_408);
            arg0->unk_00 += 1;
            break;

        case 14:
            gCameraPosition.z = 0.0f;
            gCameraPosition.x = 321.0f;
            gCameraPosition.y = 160.0f;
            arg0->unk_0C = gBattleState.unk_00->unk_2C;
            arg0->unk_00 += 1;
            break;

        default:
            arg0->unk_0C = gBattleState.unk_00->unk_2C;
            arg0->unk_00 += 1;
            break;
    }
    return 0;
}

void Dialog_RunWindowSequence(s16 arg0, s16 arg1) {
    unk_D_843901A0_4C8* temp_s0 = &gBattleMessageBuffers->unk_4C8;

    if (gBattleContext.unk_0000 == 0x10) {
        return;
    }

    switch (temp_s0->unk_00) {
        case 0:
            temp_s0->unk_08 = 0;
            if (temp_s0->unk_04 == 0xD) {
                Dialog_OpenDarkWindow(temp_s0, 0xA0, 0x78);
                temp_s0->unk_00++;
            } else if (temp_s0->unk_04 == 0xE) {
                func_84318CE4(temp_s0);
            } else if (func_84318CE4(temp_s0) == 0) {
                Dialog_OpenColoredWindow(temp_s0, arg0, arg1);
            }
            break;

        case 1:
            if (temp_s0->unk_04 == 0xD) {
                if (Dialog_ZoomDarkWindow(temp_s0, 0xA0, 0x78) != 0) {
                    RenderDialogBox(temp_s0, temp_s0->unk_14.x, temp_s0->unk_14.y);
                    temp_s0->unk_00++;
                }
            } else {
                if (temp_s0->unk_04 == 0xE) {
                    ProcessAudioCommandQueue(GetPlayerDefeatMessageId(D_84390010[temp_s0->unk_0C]));
                    RenderDialogBox(temp_s0, temp_s0->unk_14.x, temp_s0->unk_14.y);
                    temp_s0->unk_00++;
                } else if (Dialog_ZoomColoredWindow(temp_s0, arg0, arg1) != 0) {
                    ProcessAudioCommandQueue(GetPlayerDefeatMessageId(D_84390010[temp_s0->unk_0C]));
                    RenderDialogBox(temp_s0, temp_s0->unk_14.x, temp_s0->unk_14.y);
                    temp_s0->unk_00++;
                }
            }
            break;

        case 2:
            if (temp_s0->unk_04 == 0xD) {
                Dialog_ZoomDarkWindow(temp_s0, 0xA0, 0x78);
                RenderDialogBox(temp_s0, temp_s0->unk_14.x, temp_s0->unk_14.y);

                temp_s0->unk_08++;
                if (temp_s0->unk_08 == 0x46) {
                    temp_s0->unk_00++;
                }
            } else {
                if (temp_s0->unk_04 == 0xE) {
                    RenderDialogBox(temp_s0, temp_s0->unk_14.x, temp_s0->unk_14.y);
                } else {
                    Dialog_ZoomColoredWindow(temp_s0, arg0, arg1);
                    RenderDialogBox(temp_s0, temp_s0->unk_14.x, temp_s0->unk_14.y);

                    temp_s0->unk_08++;
                    if (temp_s0->unk_08 == 0x2D) {
                        temp_s0->unk_00++;
                    }
                }
            }
            break;
    }
}

void Battle_SetEntityPosition(unk_BattlePlayerEntity* arg0) {
    arg0->unk_8C4.unk_00 = 0;
    arg0->unk_8C4.unk_04 = 0;
    arg0->unk_8C4.unk_48[0] = 0;
    arg0->unk_8C4.unk_08[0] = 0;
}

void func_84319408(unk_BattlePlayerEntity* arg0, s32 arg1) {
    gBattleMessageBuffers->unk_000 = arg0->unk_720->unk_08[arg0->unk_654.unk_2C]->unk_001;
    arg0->unk_8C4.unk_00 = 1;
    MessageBank_SetPointer_0x14_0x2A(0x19, arg0->unk_724->unk_01C[arg0->unk_654.unk_08].unk_30);
    GetMessageString(arg0->unk_8C4.unk_48, 0x40, gMessageBank_0x1E, arg1);
}

void func_843194A0(unk_BattlePlayerEntity* arg0) {
    unk_D_800AE540_0004* temp_t0 = arg0->unk_720->unk_08[arg0->unk_654.unk_2C];

    if (arg0->unk_8C4.unk_48[arg0->unk_8C4.unk_04] != '\x00') {
        arg0->unk_8C4.unk_08[arg0->unk_8C4.unk_04] = arg0->unk_8C4.unk_48[arg0->unk_8C4.unk_04];
        arg0->unk_8C4.unk_04++;
    }

    if (arg0->unk_8C4.unk_48[arg0->unk_8C4.unk_04] != '\x00') {
        arg0->unk_8C4.unk_08[arg0->unk_8C4.unk_04] = arg0->unk_8C4.unk_48[arg0->unk_8C4.unk_04];
        arg0->unk_8C4.unk_04++;
    }

    arg0->unk_8C4.unk_08[arg0->unk_8C4.unk_04] = '\x00';

    if (arg0->unk_8C4.unk_48[0] != 0) {
        if (arg0 == gPrimaryPokemonEntity) {
            func_843162E4(temp_t0->unk_001, 0x5F, 0xE, &arg0->unk_8C4.unk_08);
        } else {
            func_843162E4(temp_t0->unk_001, 0x17, 0xBB, &arg0->unk_8C4.unk_08);
        }
    }
}

void func_84319564(void) {
    unk_BattlePlayerAnimState* sp1C = &D_84390010[0]->unk_654;
    unk_BattlePlayerAnimState* sp18 = &D_84390010[1]->unk_654;

    if ((gBattleContext.unk_11ED != 0) && (D_84390010[1]->unk_728.unk_168->unk_1C == 0x103) &&
        (D_84390010[0]->unk_728.unk_168->unk_1C == 0x17)) {
        DrawPhaseTimer(0x101, 0x64);
        if (gBattleResultPhase == 0) {
            if (sp1C->unk_10 != 3) {
                DrawHPBarTimer(0x46, 0x4D);
            }

            if (sp18->unk_10 != 3) {
                DrawHPBarTimer(0xE8, 0x96);
            }
        }
    }
}

void func_8431962C(void) {
    gBattleMessageBuffers = main_pool_alloc(sizeof(unk_D_843901A0), 0);
    bzero(gBattleMessageBuffers, sizeof(unk_D_843901A0));
}

void Battle_InitCamera(void) {
    gBattleMessageBuffers->unk_004 = 0;
    gBattleMessageBuffers->unk_008[gBattleMessageBuffers->unk_004] = 0;
    ResetMessageIndices();
}

void Battle_InitBattleEffects(void) {
    unk_BattlePlayerAnimState* sp1C = &D_84390010[0]->unk_654;
    unk_BattlePlayerAnimState* sp18 = &D_84390010[1]->unk_654;

    if (1) {}

    Dialog_RunWindowSequence(0xA0, 0xC8);

    if (gBattleContext.unk_0000 == 0x10) {
        func_8431712C();
        func_8431694C();
    }

    switch (gBattleState.unk_00->unk_1C) {
        case 1:
            func_843172A0(D_84390010[0], sp1C);
            func_84317558(D_84390010[1], sp18);
            func_843194A0(D_84390010[0]);
            func_843194A0(D_84390010[1]);
            func_84319564();
            func_84316610();
            break;

        case 2:
            InitBattleDialogParameters();
            func_84316610();
            break;
    }
}
