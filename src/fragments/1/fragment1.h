#ifndef _FRAGMENT1_H_
#define _FRAGMENT1_H_

#include "global.h"
#include "src/E1C0.h"

void GbEmu_Init(GbEmuState*);
void GbEmu_RunFrame(GbEmuState*);
void GbEmu_AudioUpdateThread(GbEmuThreadInfo*);
void GbAudio_Update();
void UpdateAudioParameters(GbPakDeviceState*); 
s32 osGbSetNextBuffer(void*, s32);

#endif /* _FRAGMENT1_H_ */
