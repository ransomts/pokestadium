#ifndef _4BA90_H_
#define _4BA90_H_

#include "global.h"

void Music_SetMasterVolumeLevel(s32 arg0, u32 arg1);
void Music_SetPanMode(s32 arg0);
void Music_HandleStateChange(u32 arg0);
void Music_StartVolumeFade(u32 arg0);
void Music_EndVolumeFade(void);

#endif // _4BA90_H_
