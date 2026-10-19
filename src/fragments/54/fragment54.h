#ifndef _FRAGMENT54_H_
#define _FRAGMENT54_H_

#include "global.h"
#include "src/26820.h"

void DrawPanelBorder(s16 arg0, s16 arg1);
void RentalHub_DrawHeaderBar(s16 arg0, s16 arg1, s16 arg2, Color_RGBA8* arg3, Color_RGBA8* arg4);
void DrawMenuHeader(void);
void RentalHub_DrawSelectionCursor(s16 arg0, s16 arg1, s16 arg2, s16 arg3);
void DrawFrameRect(s16 arg0, s16 arg1, s16 arg2, s16 arg3);
void DrawMenuEntryBox(s16 arg0, s16 arg1, s16 arg2, char* arg3);
void DrawMenuEntries(s16 arg0);
s32 GetMenuInput(void);
void RenderMenuFrame(s16 arg0);
void FadeInAndRunMenu(void);
void FadeOutAndCleanup(void);
s16 RunMenuSelectionLoop(void);
void LoadMenuBackground(unk_func_80027FA0* arg0);
s32 MenuFragment_Init(void);
s32 RentalHub_LoadRentalPicker(void);
s32 RentalHub_LoadRentalRules(void);
s32 Fragment54_Main(UNUSED s32 arg0, UNUSED s32 arg1);

#endif // _FRAGMENT54_H_
