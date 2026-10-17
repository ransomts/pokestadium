#ifndef _490A0_H_
#define _490A0_H_

#include "global.h"

void Music_RequestHandle(s32 arg0);
s32 Music_GetState(s32 arg0);
s32 Audio_CalcLoadScore(void);
s32 Audio_GetFreeVoiceCount(void);
s32 Audio_GetReleasingVoiceCount(void);

#endif // _490A0_H_
