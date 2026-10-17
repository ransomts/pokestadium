#ifndef _6A40_H_
#define _6A40_H_

#include "global.h"

void Gfx_InitBuffers(u32 arg0, s32 arg1);
void Gfx_FreeBuffers(void);
void Gfx_SwapDisplayList(void);
void Gfx_GetCurrentDL(Gfx** arg0, Gfx** arg1);
void* GfxAlloc(s32 arg0);
s32 func_80005F9C(void);

#endif // _6A40_H_
