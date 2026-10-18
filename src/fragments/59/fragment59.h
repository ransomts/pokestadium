#ifndef _FRAGMENT59_H_
#define _FRAGMENT59_H_

#include "global.h"
#include "src/6BC0.h"
#include "src/11BA0.h"

void AnimateRectangle(s16 arg0, s16 arg1, s16 arg2);
void Menu_AnimateRectangles(s16 arg0);
void MenuConfig_InitAnimation(void);
void Menu_DrawFrame(FramebufferImage* arg0, s16 arg1, s16 arg2);
void Menu_DrawBorderedRect(s16 arg0, s16 arg1, s16 arg2, s16 arg3, u8 arg4, u8 arg5, u8 arg6, u8 arg7);
void Menu_DrawAnimatedBorder(s16 arg0, s16 arg1, s16 arg2, s16 arg3, u8 arg4, u8 arg5, u8 arg6, u8 arg7);
s32 MenuBackground_Display(s32 arg0, SimpleGfxNode* arg1);
void Menu_DrawInfoBox(s16 arg0);
void Menu_UpdateRender(s32 arg0, s32 arg1, f32 arg2);
FramebufferImage* Menu_CreateBackgroundImage(u8* arg0, s16 arg1);
FramebufferImage* Menu_CreateOptionImage(u8* arg0, s16 arg1);
void Menu_InitializeResources(void);
s16 func_84101D80(void);
void Menu_MainLoop(void);
void Menu_GraphInit(void);
s32 Menu_StartBattleIfSelected(void);
s32 Menu_Run(s32 arg0, s32 arg1);

#endif // _FRAGMENT59_H_
