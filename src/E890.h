#ifndef _E890_H_
#define _E890_H_

#include "global.h"

typedef struct unk_D_800AA680 {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ u16 unk_04;
    /* 0x06 */ u16 unk_06;
    /* 0x08 */ void* unk_08;
    /* 0x0C */ s32 unk_0C;
} unk_D_800AA680; // size = 0x10

typedef struct unk_D_800AA690 {
    /* 0x00 */ u16 unk_00;
    /* 0x02 */ u16 unk_02;
    /* 0x04 */ u16 unk_04;
    /* 0x06 */ u16 unk_06;
} unk_D_800AA690; // size = 0x8

extern unk_D_800AA680 gBootIDData;

s32 Boot_ValidateAndCopy(void);
s32 BootID_StoreIfValid(unk_D_800AA680* arg0);
s32 func_8000DDB0(void);
s32 func_8000DDE4(void);
s32 Boot_DMAReadHeader(unk_D_800AA680* arg0);
s32 Boot_DMAReadData(void);
s32 Boot_ProcessMessage(void);
s32 Boot_ProcessMessageStage2(void);
s32 Boot_ProcessMessageWithID(unk_D_800AA680* arg0);
s32 Boot_ProcessMessageStage3(void);
s32 Boot_CheckUnitReady(void);
void func_8000E5B4(void);
s32 Boot_MainLoop(unk_D_800AA680* arg0);
s32 Boot_Init(void);
void func_8000E760(void);
void func_8000E7E4(void);

#endif // _E890_H_
