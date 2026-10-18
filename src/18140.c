#include "18140.h"
#include "src/util.h"

static AnimStackEntry gAnimStack[2];
static s32 gAnimStackDepth;

s32 MapIndexInRange(s32 arg0, unk_func_80017540_arg1* arg1, s32 arg2) {
    unk_func_80017540_arg1* temp_v0 = &arg1[arg2];
    s32 ret;

    if (arg0 < temp_v0->unk_00) {
        ret = arg0 + temp_v0->unk_02;
    } else {
        ret = (temp_v0->unk_02 + temp_v0->unk_00) - 1;
    }
    return ret;
}

s16 GetNextAnimFrame(unk_D_86002F58_004_000_054* arg0, u16 arg1) {
    s16 var_v1;
    unk_D_86002F58_004_000_054_004* temp_v0;

    var_v1 = arg0->unk_08;
    temp_v0 = arg0->unk_04;

    if (arg0->unk_0A != arg1) {
        var_v1 += 1;
        if (var_v1 >= temp_v0->unk_0A) {
            if (temp_v0->unk_00 & 2) {
                var_v1 = temp_v0->unk_0A - 1;
            } else {
                var_v1 = temp_v0->unk_06;
            }
        }
    }
    return var_v1;
}

void ResetAnimStack(void) {
    gAnimStackDepth = -1;
}

void PushAnimStackEntry(unk_D_86002F58_004_000_054* arg0, u16 arg1, s32 arg2) {
    unk_D_86002F58_004_000_054_004* sp24;
    AnimStackEntry* temp_s0;

    sp24 = arg0->unk_04;
    gAnimStackDepth++;
    if (gAnimStackDepth < 2) {
        temp_s0 = &gAnimStack[gAnimStackDepth];
        if (arg0->unk_04 != NULL) {
            if (arg2 != 0) {
                arg0->unk_08 = GetNextAnimFrame(arg0, arg1);
            }
            arg0->unk_0A = arg1;
            temp_s0->unk_00 = 1;
            temp_s0->unk_02 = arg0->unk_08;
            temp_s0->unk_04 = sp24;
            temp_s0->unk_08 = Util_ConvertAddrToVirtAddr(sp24->unk_0C);
            temp_s0->unk_0C = Util_ConvertAddrToVirtAddr(sp24->unk_10);
            if (temp_s0->unk_02 < 0) {
                temp_s0->unk_02 = 0;
            }
        } else {
            temp_s0->unk_00 = 0;
        }
    }
}

void PopAnimStackEntry(void) {
    if (gAnimStackDepth >= 0) {
        gAnimStackDepth--;
    }
}

void GetAnimStackCurrentFramePtr(unk_D_86002F34_alt11_018** arg0, unk_D_86002F34_alt11_018* arg1, s32 arg2) {
    AnimStackEntry* sp1C;

    if ((gAnimStackDepth >= 0) && (gAnimStackDepth < 2)) {
        sp1C = &gAnimStack[gAnimStackDepth];
        if ((sp1C->unk_00 == 1) && (arg2 >= 0) && (arg2 < sp1C->unk_04->unk_08)) {
            *arg0 = &arg1[((u8*)sp1C->unk_0C)[MapIndexInRange(sp1C->unk_02, sp1C->unk_08, arg2)]];
        }
    }
}

void InitAnimState(Fragment2_1GraphNode* arg0) {
    arg0->unk_054.unk_00 = -1;
    arg0->unk_054.unk_04 = 0;
}

s16 SetAnimStateTable(Fragment2_1GraphNode* arg0, s16 arg1, s32 arg2) {
    unk_D_86002F58_004_000_054_004* temp_v0 = Util_ConvertAddrToVirtAddr(arg2);
    unk_D_86002F58_004_000_054* ptr = &arg0->unk_054;

    if ((temp_v0 != ptr->unk_04) || (arg1 != ptr->unk_00)) {
        ptr->unk_00 = arg1;
        ptr->unk_04 = temp_v0;
        ptr->unk_08 = temp_v0->unk_04 - 1;
    }

    return ptr->unk_08;
}

void SetAnimStateIndex(Fragment2_1GraphNode* arg0, s16 arg1) {
    arg0->unk_054.unk_08 = arg1 - 1;
}

s32 IsAnimStateAtIndex(Fragment2_1GraphNode* arg0, s16 arg1) {
    return (arg0->unk_054.unk_08 + 1) == arg1;
}

s32 IsAnimStateSecondLast(Fragment2_1GraphNode* arg0) {
    return (arg0->unk_054.unk_08 + 2) == arg0->unk_054.unk_04->unk_0A;
}

s32 IsAnimStateLast(Fragment2_1GraphNode* arg0) {
    return (arg0->unk_054.unk_08 + 1) == arg0->unk_054.unk_04->unk_0A;
}
