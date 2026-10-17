#ifndef _32D10_H_
#define _32D10_H_

#include "global.h"

extern u8 D_800AF770[8];
extern s16 gHpWheelDigitOffsetOnes[4];
extern s16 gHpWheelDigitOffsetTens[4];
extern s16 gHpWheelDigitOffsetHundreds[4];
extern s16 gHpWheelDigitOffsetOnesSmooth[4];
extern s16 gHpWheelDigitOffsetTensSmooth[4];
extern s16 gHpWheelDigitOffsetHundredsSmooth[4];
extern s16 D_800AF7AE;
extern s16 gModelUpdateFlag[2];

void HpWheel_SetDigits(u8 arg0, s16 arg1);
void HpWheel_SetDigitsSmooth(u8 arg0, s16 arg1);
void AnimationFrame_StallCheck(void);
s32 ModelPhase_IsIdle(void);
u8 GraphRoot_GetCurrentModelSlot(void);
s16 func_800325E0(void);
void GraphNode_EnableTransform(unk_D_86002F58_004_000* arg0);
void ModelPhase_Advance(u32 arg0, u32 arg1);
void ModelPhase_UpdateStatus(u32 arg0, u32 arg1);
void Gfx_SetCombineRaw(Gfx*, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);

#endif // _32D10_H_
