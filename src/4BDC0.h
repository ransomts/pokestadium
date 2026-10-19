#ifndef _4BDC0_H_
#define _4BDC0_H_

#include "global.h"

void Stage_SetFadeColor(s32);
s32 ResultScreen_SetAnimation(s32);
s32 Audio_StartTrackForCategory(s32, s32);
s32 Audio_UpdateSpecialSequence(s32, u32);
u32 Audio_GetSpecialSequenceState(void);

#endif // _4BDC0_H_
