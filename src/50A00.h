#ifndef _50A00_H_
#define _50A00_H_

#include "global.h"

extern u8* gSfxBankSpecial;

s32 Audio_LoadBankAndSong(u8*);
void Audio_ClearBankDMAFlag(void);

#endif // _50A00_H_
