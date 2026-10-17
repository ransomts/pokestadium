#ifndef _DDC0_H_
#define _DDC0_H_

#include "global.h"

void func_8000D1C0(void);
void func_8000D1C8(void);
void func_8000D1D0(void);
void func_8000D1D8(void);
void Music_ClearCurrentId(void);
void Music_ChangeTrack(s32 arg0);
void Music_SetTrack(s32 arg0);
void Music_StopTrack(s32 arg0);
s32 Audio_WaitForLoadAndFade(s32 arg0);
void Audio_FadeAllChannelsFast(void);
void Audio_Unpause(void);
void Audio_Pause(void);
void Audio_ThreadMain(void*);
void Audio_CreateThread(void);


#endif // _DDC0_H_
