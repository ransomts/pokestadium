#ifndef _C030_H_
#define _C030_H_

#include "global.h"

void WaitMs(long ms);
s32 IsStickerStationConnected(void);
u8 StickerStation_GetCommand(void);
void StickerStation_SetCommand(u8 arg0);

#endif // _C030_H_
