#ifndef _17300_H_
#define _17300_H_

#include "global.h"

typedef struct unk_D_800ABCC0_008 {
    /* 0x00 */ u8 unk_00;
    /* 0x01 */ u8 unk_01;
    /* 0x02 */ u8 unk_02;
    /* 0x03 */ u8 unk_03;
    /* 0x04 */ u16 unk_04;
    /* 0x06 */ u16 unk_06;
    /* 0x08 */ u16 unk_08;
} unk_D_800ABCC0_008; // size = 0xA

typedef struct unk_D_800ABCC0 {
    /* 0x00 */ u8 unk_00;
    /* 0x01 */ u8 unk_01;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ unk_D_86002F58_004_000_040_004* unk_04;
    /* 0x08 */ unk_D_800ABCC0_008* unk_08;
    /* 0x0C */ s16* unk_0C;
    /* 0x10 */ s16* unk_10;
    /* 0x14 */ s16* unk_14;
} unk_D_800ABCC0; // size = 0x18

f32 Anim_GetScalar(unk_D_800ABCC0* arg0, s32 arg1);
s16 Anim_GetRotation(unk_D_800ABCC0* arg0, s32 arg1);
f32 Anim_GetPosition(unk_D_800ABCC0* arg0, s32 arg1);
f32 Anim_InterpolateCubic(Vec3s* arg0, s16 arg1, s16 arg2);
f32 Anim_GetScaleInterpolated(unk_D_800ABCC0* arg0, s32 arg1);
s16 Anim_GetRotationInterpolated(unk_D_800ABCC0* arg0, s32 arg1);
f32 Anim_GetPositionInterpolated(unk_D_800ABCC0* arg0, s32 arg1);
void Anim_ResetChannelIndex(void);
void Anim_StartChannel(unk_D_86002F58_004_000_040* arg0, u16 arg1, s32 arg2);
void Anim_EndChannel(void);
void Anim_GetTransformTriple(Vec3f* arg0, Vec3s* arg1, Vec3f* arg2, s32 arg3);
void Anim_ClearChannelState(Fragment2_1GraphNode* arg0);
s32 Anim_SetChannel(Fragment2_1GraphNode* arg0, s16 arg1, void* arg2, s32 arg3);
s32 Anim_SetChannelOffset(Fragment2_1GraphNode* arg0, s32 arg1);
void Anim_SetChannelBase(Fragment2_1GraphNode* arg0, s16 arg1);
s32 Anim_IsFrameInRange(Fragment2_1GraphNode* arg0, s16 arg1);
s32 func_800174E4(Fragment2_1GraphNode* arg0);
s32 Anim_HasReachedEnd(Fragment2_1GraphNode* arg0);


#endif // _17300_H_
