#ifndef _FRAGMENT13_H_
#define _FRAGMENT13_H_

#include "global.h"

void MiniGame_PollController(void);
void MiniGame_InitCamera(void);
void MiniGame_HandleCameraInput(void);
void MiniGame_DrawOverlay(s32 arg0);
void MiniGame_RenderFrame(s32 arg0);
void MiniGame_RunOpening(void);
void MiniGame_RunPlaying(void);
void MiniGame_RunEnding(void);
void MiniGame_InitGraph(void);
s32 MiniGame_Main(UNUSED s32 arg0, UNUSED s32 arg1);

#endif // _FRAGMENT13_H_
