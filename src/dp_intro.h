#ifndef _SRC_DP_INTRO_H_
#define _SRC_DP_INTRO_H_

#include "global.h"
#include "3FB0.h"

void RdpTask_Init(UnkStruct80001380* arg0);
void RdpTask_StartWithData(UnkStruct80001380* arg0, struct UnkArray4* arg1, s32 arg2);
void Vi_SetMode(s8 arg0, s8 arg1);
void IntroTask_SetPendingBuffer(struct UnkArray4* arg0);
void IntroTask_ProcessFrame(void);
void func_800017E4(void);
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
void func_80001C64(void);
s32 RspTaskYielded(void);
void func_80001CB8(void);
void func_80001CC8(void);

#endif /* _SRC_DP_INTRO_H_ */
