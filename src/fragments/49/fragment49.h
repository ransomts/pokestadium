#ifndef _FRAGMENT49_H_
#define _FRAGMENT49_H_

#include "global.h"

void Menu_Init(void);
void Menu_DrawFramebuffer(s32 arg0, s32 arg1);
void Menu_DrawBackground(s32 arg0, u8* arg1);
void Menu_RenderFrame(void);
s32 Menu_IsConfirmPressed(void);
s32 Menu_Update(void);
void Menu_ProcessInput(void);
void func_83A009C0(void);
void func_83A009C8(void);
s32 Menu_Entry(s32 arg0, s32 arg1);

#endif // _FRAGMENT49_H_
