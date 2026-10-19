#include "src/model_animation_events.h"
#include "src/util.h"

static AnimStackEntry gAnimStack[2];
static s32 gAnimStackDepth;

s32 ModelAnim_ResolveEventIndex(s32 arg0, unk_func_80017540_arg1* arg1, s32 arg2) {
    unk_func_80017540_arg1* temp_v0 = &arg1[arg2];
    s32 ret;

    if (arg0 < temp_v0->posX) {
        ret = arg0 + temp_v0->posY;
    } else {
        ret = (temp_v0->posY + temp_v0->posX) - 1;
    }
    return ret;
}

s16 ModelAnim_AdvanceEventFrame(unk_D_86002F58_004_000_054* arg0, u16 arg1) {
    s16 var_v1;
    unk_D_86002F58_004_000_054_004* temp_v0;

    var_v1 = arg0->RentalSlotAnimData_PosePhase;
    temp_v0 = arg0->rotation;

    if (arg0->unk_0A != arg1) {
        var_v1 += 1;
        if (var_v1 >= temp_v0->unk_0A) {
            if (temp_v0->posX & 2) {
                var_v1 = temp_v0->unk_0A - 1;
            } else {
                var_v1 = temp_v0->unk_06;
            }
        }
    }
    return var_v1;
}

void ModelAnim_ResetEventContext(void) {
    gAnimStackDepth = -1;
}

void ModelAnim_BeginEventContext(unk_D_86002F58_004_000_054* arg0, u16 arg1, s32 arg2) {
    unk_D_86002F58_004_000_054_004* sp24;
    AnimStackEntry* temp_s0;

    sp24 = arg0->rotation;
    gAnimStackDepth++;
    if (gAnimStackDepth < 2) {
        temp_s0 = &gAnimStack[gAnimStackDepth];
        if (arg0->rotation != NULL) {
            if (arg2 != 0) {
                arg0->RentalSlotAnimData_PosePhase = ModelAnim_AdvanceEventFrame(arg0, arg1);
            }
            arg0->unk_0A = arg1;
            temp_s0->posX = 1;
            temp_s0->posY = arg0->RentalSlotAnimData_PosePhase;
            temp_s0->rotation = sp24;
            temp_s0->RentalSlotAnimData_PosePhase = Util_ConvertAddrToVirtAddr(sp24->unk_0C);
            temp_s0->unk_0C = Util_ConvertAddrToVirtAddr(sp24->unk_10);
            if (temp_s0->posY < 0) {
                temp_s0->posY = 0;
            }
        } else {
            temp_s0->posX = 0;
        }
    }
}

void ModelAnim_EndEventContext(void) {
    if (gAnimStackDepth >= 0) {
        gAnimStackDepth--;
    }
}

void ModelAnim_GetEventAtFrame(TextureInfo** arg0, TextureInfo* arg1, s32 arg2) {
    AnimStackEntry* sp1C;

    if ((gAnimStackDepth >= 0) && (gAnimStackDepth < 2)) {
        sp1C = &gAnimStack[gAnimStackDepth];
        if ((sp1C->posX == 1) && (arg2 >= 0) && (arg2 < sp1C->rotation->RentalSlotAnimData_PosePhase)) {
            *arg0 = &arg1[((u8*)sp1C->unk_0C)[ModelAnim_ResolveEventIndex(sp1C->posY, sp1C->RentalSlotAnimData_PosePhase, arg2)]];
        }
    }
}

void ModelAnim_ClearEventTrack(Fragment2_1GraphNode* arg0) {
    arg0->unk_054.posX = -1;
    arg0->unk_054.rotation = 0;
}

s16 ModelAnim_BindEventTrack(Fragment2_1GraphNode* arg0, s16 arg1, s32 arg2) {
    unk_D_86002F58_004_000_054_004* temp_v0 = Util_ConvertAddrToVirtAddr(arg2);
    unk_D_86002F58_004_000_054* ptr = &arg0->unk_054;

    if ((temp_v0 != ptr->rotation) || (arg1 != ptr->posX)) {
        ptr->posX = arg1;
        ptr->rotation = temp_v0;
        ptr->RentalSlotAnimData_PosePhase = temp_v0->rotation - 1;
    }

    return ptr->RentalSlotAnimData_PosePhase;
}

void ModelAnim_SetEventFrame(Fragment2_1GraphNode* arg0, s16 arg1) {
    arg0->unk_054.RentalSlotAnimData_PosePhase = arg1 - 1;
}

s32 ModelAnim_IsEventFrame(Fragment2_1GraphNode* arg0, s16 arg1) {
    return (arg0->unk_054.RentalSlotAnimData_PosePhase + 1) == arg1;
}

s32 ModelAnim_IsEventTrackNearEnd(Fragment2_1GraphNode* arg0) {
    return (arg0->unk_054.RentalSlotAnimData_PosePhase + 2) == arg0->unk_054.rotation->unk_0A;
}

s32 ModelAnim_IsEventTrackDone(Fragment2_1GraphNode* arg0) {
    return (arg0->unk_054.RentalSlotAnimData_PosePhase + 1) == arg0->unk_054.rotation->unk_0A;
}
