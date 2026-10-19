#ifndef _48C60_H_
#define _48C60_H_

#include "global.h"

extern u8 gSpecialMoveSoundFlag[16];

s32 PlayMoveSoundEffect(s32, u32, u32, u32);
void Audio_FadeStoredSound(void);

#endif // _48C60_H_
