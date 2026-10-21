#ifndef _FRAGMENT1_H_
#define _FRAGMENT1_H_

#include "global.h"
#include "src/gb_tower_audio.h"

extern u8 D_102BA0_END[];

void GbEmu_Init(GbEmuState*);
void GbEmu_RunFrame(GbEmuState*);
void GbEmu_AudioVideoTick(GbEmuThreadInfo*);
void GbAudio_Update();
void GbEmu_InitContext(GbPakDeviceState*);
s32 osGbSetNextBuffer(void*, s32);
void GbAudio_SetAlternateStreamId(s32);
u8 GbMem_ReadIoRegister(u16);
s32 GbCpu_Execute(GbPakDeviceState*, s32);
void GbCpu_InitOpcodeTables(GbPakDeviceState*, void*);
void GbAudio_RenderStream(s32, s16*);

#endif /* _FRAGMENT1_H_ */
