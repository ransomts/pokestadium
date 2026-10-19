#ifndef _SRC_DP_INTRO_H_
#define _SRC_DP_INTRO_H_

#include "global.h"
#include "3FB0.h"

void RdpTask_Init(UnkStruct80001380* arg0);
void RdpTask_StartWithData(UnkStruct80001380* arg0, struct UnkArray4* arg1, s32 arg2);
void Vi_SetMode(s8 arg0, s8 arg1);
void IntroTask_SetPendingBuffer(struct UnkArray4* arg0);
void IntroTask_ProcessFrame(void);
void DisplayWorker_DrainEvents(void);
void IntroTask_ThreadMain(UNUSED void* arg);
void IntroTask_Init(void);
void Gfx_SetFrameFillColor(u16 color);
u16 Gfx_GetFrameFillColor(void);
s32 IsSoftResetPending(void);
void Sched_WaitFrame(void);
void Sched_SendFrame(void* arg0);
void Sched_RunFrames(s32 arg0);
void IntroBuffer_SetParams(struct UnkArray4* arg0, u8 arg1, u8 arg2, u8 arg3, u8 arg4, s32 arg5, s32 arg6, s32 arg7);
s32 GetFramebufferInfo(void);
void Display_ApplyPendingVideoMode(void);
s32 RspTaskYielded(void);
void Display_EnableBlackout(void);
void Display_DisableBlackout(void);

#endif /* _SRC_DP_INTRO_H_ */
