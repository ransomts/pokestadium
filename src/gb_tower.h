#ifndef _SRC_GB_TOWER_H_
#define _SRC_GB_TOWER_H_

#include "global.h"

s32 GbPak_VerifyBlock(s32 arg0, void* arg1);
s32 GbPak_TestMemory(s32 arg0, u8* arg1);
s32 GbPak_InitAndTest(s32 arg0, u8* arg1, u8* arg2);
s32 GbPak_SetPowerState(s32 arg0, u8 arg1);
void func_8000A924(void);
s32 GbPak_IsSupportedPokemonCart(OSGbpakId* header);
s32 GbPak_InitAll(void);
s32 GbPak_IsCartRemoved(s32 arg0);
s32 GbPak_IsCartInserted(s32 arg0);
s32 GbPak_ReinitSlot(s32 arg0);
s32 GbPak_VerifyBlockNoDetect(s32 arg0, void* arg1);
s32 GbPak_MbcRead(s32 arg0, void* arg1, u16 arg2, u16 arg3);
s32 GbPak_MbcWrite(s32 arg0, void* arg1, u16 arg2, u16 arg3);
s32 GbPak_Read(s32 arg0, u8* arg1, u16 arg2, u16 arg3);
s32 GbPak_Write(s32 arg0, u8* arg1, u16 arg2, u16 arg3);
int func_8000B0CC(s32 arg0, s32 arg1);
s32 GbPak_WriteDataAligned(s32 arg0, u8* arg1, s32 arg2, s32 arg3);
u8 func_8000B318(u8 arg0);
void Cont_FinishRead(void);

#endif /* _SRC_GB_TOWER_H_ */
