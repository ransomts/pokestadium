#ifndef _20470_H_
#define _20470_H_

#include "global.h"

extern Gfx gMenuDL_BackgroundFill[];
extern Gfx gPrefDL_Fill[];
extern Gfx gDL_FillCycle[];
extern Gfx gTransferPakErrorBorderDL[];
extern Gfx gPrefDL_Border[];
extern Gfx gDL_XluBorder[];
extern Gfx gDL_PalettedIcon[];
extern Gfx gFontCharTableExtended[];
extern Gfx gPrefDL_End[];
extern Gfx gDL_TextResetState[];
extern Gfx gDL_TextSetup[];
extern Gfx gDL_TextBegin[];
extern Gfx gDL_TextEnd[];

void DrawTileTextureRect(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u8* arg4);
void DrawWindowBorder(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_8001FB40(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void DrawWindowBorderThin(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void FillRectWithColor(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u16 arg4);
void FillRectWithColorInset(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u16 arg4);
void DrawGradientRect(s32 arg0, s32 arg1, s32 arg2, s32 arg3, Color_RGB8* arg4, Color_RGB8* arg5);
void DrawPanel(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u16 arg4);
void DrawGradientPanel(s32 arg0, s32 arg1, s32 arg2, s32 arg3, Color_RGB8* arg4, Color_RGB8* arg5);
void DrawPanelAlt(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u16 arg4);
void DrawSimplePanel(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void DrawStatusIcon(s32 arg0, s32 arg1);
void AnimateIconOffset(s16 arg0, s16 arg1);
void DrawBadgeIcon(s32 arg0, s32 arg1, s32 arg2);
void DrawHealthBar(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void DrawExpBar(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_80021920(void);

#endif // _20470_H_
