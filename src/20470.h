#ifndef _20470_H_
#define _20470_H_

#include "global.h"

extern Gfx D_8006F470[];
extern Gfx D_8006F498[];
extern Gfx D_8006F4C0[];
extern Gfx D_8006F4E0[];
extern Gfx D_8006F518[];
extern Gfx D_8006F558[];
extern Gfx D_8006F5A0[];
extern Gfx D_8006F608[];
extern Gfx D_8006F630[];
extern Gfx D_8006F710[];
extern Gfx D_8006F750[];
extern Gfx D_8006F768[];
extern Gfx D_8006F798[];

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
