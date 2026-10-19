#ifndef _FRAGMENT60_H_
#define _FRAGMENT60_H_

#include "global.h"
#include "src/11BA0.h"

void CupSelect_PollController(void);
void DrawBorderCorners(s16 arg0, s16 arg1, s16 arg2, s16 arg3, u8 arg4, u8 arg5, u8 arg6, u8 arg7);
s32 Background_DrawLayer(s32 arg0, SimpleGfxNode* arg1);
s32 Overlay_DrawLayer(s32 arg0, SimpleGfxNode* arg1);
void Stage_DrawFrame(s32 arg0, s32 arg1);
void Stage_InitGraphNodes(void);
s32 Menu_HandleInput(void);
s32 Menu_RunSelection(void);
void Stage_LoadResourcesAndInit(void);
s32 Fragment60_Main(UNUSED s32 arg0, UNUSED s32 arg1);

#endif // _FRAGMENT60_H_
