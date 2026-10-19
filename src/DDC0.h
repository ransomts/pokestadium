#ifndef _DDC0_H_
#define _DDC0_H_

#include "global.h"

void Audio_Stub1(void);
void Audio_Stub2(void);
void Audio_Stub3(void);
void Audio_Stub4(void);
void Audio_ResetCurrentMusic(void);
void Audio_PlayMusicIfChanged(s32 arg0);
void Audio_PlayMusicIfChangedImmediate(s32 arg0);
void Audio_StopMusic(s32 arg0);
s32 Audio_WaitForIdle(s32 arg0);
void Audio_FadeOutForShutdown(void);
void Audio_Disable(void);
void Audio_Enable(void);
void Audio_ThreadMain(void*);
void Audio_StartThread(void);


#endif // _DDC0_H_
