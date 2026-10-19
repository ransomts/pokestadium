#ifndef _FRAGMENT48_H_
#define _FRAGMENT48_H_

#include "global.h"

void Gallery_Debugger_PostLoad(void);
void func_83900028(void);
void func_83900030(void);
void GalleryDebugger_LoadDeckEntries(void);
void GalleryDebugger_SaveDeckEntries(void);
void GalleryDebugger_DrawMenu(void);
void GalleryDebugger_DrawFrame(void);
s32 GalleryDebugger_HandleMenuInput(void);
s32 GalleryDebugger_UpdateFadeState(void);
void GalleryDebugger_PollInput(void);
void GalleryDebugger_MenuLoop(void);
s32 GalleryDebugger_Main(s32 arg0, s32 arg1);

#endif // _FRAGMENT48_H_
