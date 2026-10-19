#ifndef _17300_H_
#define _17300_H_

#include "global.h"

typedef struct unk_D_800ABCC0_008 {
    /* 0x00 */ u8 posX;
    /* 0x01 */ u8 TrainerSlotSaveData_GamePort;
    /* 0x02 */ u8 posY;
    /* 0x03 */ u8 unk_03;
    /* 0x04 */ u16 rotation;
    /* 0x06 */ u16 unk_06;
    /* 0x08 */ u16 RentalSlotAnimData_PosePhase;
} unk_D_800ABCC0_008; // size = 0xA

typedef struct unk_D_800ABCC0 {
    /* 0x00 */ u8 posX;
    /* 0x01 */ u8 TrainerSlotSaveData_GamePort;
    /* 0x02 */ s16 posY;
    /* 0x04 */ unk_D_86002F58_004_000_040_004* rotation;
    /* 0x08 */ unk_D_800ABCC0_008* RentalSlotAnimData_PosePhase;
    /* 0x0C */ s16* unk_0C;
    /* 0x10 */ s16* unk_10;
    /* 0x14 */ s16* unk_14;
} unk_D_800ABCC0; // size = 0x18

f32 ModelAnim_EvaluateTranslationChannel(unk_D_800ABCC0* arg0, s32 arg1);
s16 ModelAnim_EvaluateRotationChannel(unk_D_800ABCC0* arg0, s32 arg1);
f32 ModelAnim_EvaluateScaleChannel(unk_D_800ABCC0* arg0, s32 arg1);
f32 ModelAnim_InterpolateKeyframe(Vec3s* arg0, s16 arg1, s16 arg2);
f32 ModelAnim_EvaluateTranslationCurve(unk_D_800ABCC0* arg0, s32 arg1);
s16 ModelAnim_EvaluateRotationCurve(unk_D_800ABCC0* arg0, s32 arg1);
f32 ModelAnim_EvaluateScaleCurve(unk_D_800ABCC0* arg0, s32 arg1);
void ModelAnim_ResetCurveContext(void);
void ModelAnim_BeginCurveContext(unk_D_86002F58_004_000_040* arg0, u16 arg1, s32 arg2);
void ModelAnim_EndCurveContext(void);
void ModelAnim_EvaluateJointTransform(Vec3f* arg0, Vec3s* arg1, Vec3f* arg2, s32 arg3);
void ModelAnim_ClearTransformChannel(Fragment2_1GraphNode* arg0);
s32 ModelAnim_BindTransformCurve(Fragment2_1GraphNode* arg0, s16 arg1, void* arg2, s32 arg3);
s32 ModelAnim_SetSpeed(Fragment2_1GraphNode* arg0, s32 arg1);
void ModelAnim_SetFrame(Fragment2_1GraphNode* arg0, s16 arg1);
s32 ModelAnim_HasCrossedFrame(Fragment2_1GraphNode* arg0, s16 arg1);
s32 ModelAnim_IsAnimationDone(Fragment2_1GraphNode* arg0);
s32 ModelAnim_IsFinished(Fragment2_1GraphNode* arg0);


#endif // _17300_H_
