#ifndef _2C1C0_H_
#define _2C1C0_H_

#include "global.h"
#include "29BA0.h"

extern u8 D_80075680[3];

void Battle_ResetSideState(unk_D_800AE540_1194* arg0);
void Battle_Init(s32 arg0, s32 arg1, s32 arg2);
void func_8002B6BC(void);
unk_D_800AE540_0004* RegisterPlayer(s32 arg0, s16 arg1, char* arg2, char* arg3);
void Battle_RegisterPlayerEntry(s32 arg0, unk_D_800AE540_0004* arg1);
void Battle_AddPartyMon(unk_D_800AE540_0004* arg0, unk_func_80026268_arg0* arg1);
unk_func_80026268_arg0* func_8002B924(unk_func_80026268_arg0* arg0, u8 arg1, s16 arg2);
void func_8002BA34(s16 arg0, s16 arg1, s16 arg2, s16 arg3);
void func_8002BB7C(s32 arg0, s32 arg1, s32 arg2);
void func_8002BC64(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_8002BD14(s32 arg0);
s32 Battle_PickRandomMon(s32 arg0);
s16 Battle_GetMaxPartyLevel(void);
void Battle_SetPartyLevel(s16 arg0);
void func_8002BFC4(s16 arg0, s16 arg1, s16 arg2, s32 arg3);
void func_8002C128(void);
void func_8002C394(s16 arg0);
void func_8002C538(void);
s32 func_8002C5E8(void);

#endif // _2C1C0_H_
