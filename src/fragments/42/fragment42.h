#ifndef _FRAGMENT42_H_
#define _FRAGMENT42_H_

#include "global.h"
#include "src/30640.h"

void DrawPanelFrame(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u8 arg4, u8 arg5, u8 arg6, u8 arg7);
unk_D_83407B38* GetActiveMenu(void);
void UpdateMenuItemStates(void);
s32 func_833005CC(void);
s32 ProcessMenuInput(void);
void ResetMenuState(void);
s32 HandlePokemonGridInput(unk_D_83407B38* arg0);
void func_83300D80(u16* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, f32 arg5, f32 arg6);
void DrawMenuScreen(void);
void DrawSubPanel(s32 arg0, s32 arg1, s32 arg2);
void DrawMessageBox(unk_D_83407B38* arg0, s32 arg1, s32 arg2);
void InitializeMenuState(s32 arg0, s32 arg1);
void func_83301998(s32 arg0, s32 arg1, s32 arg2, s32 arg3, Color_RGBA8* arg4, Color_RGBA8* arg5);
void DrawBackground(void);
void DrawPokemonGrid(unk_D_83407B38* arg0);
void DrawSelectionHighlight(unk_D_83407B38* arg0);
void func_8330267C(s32 arg0);
void RenderFrame(void);
void func_83302820(unk_D_83407B38* arg0);
void func_833028FC(void);
void func_833029F0(void);
void func_83302ACC(void);
s32 func_83302B5C(void);
void func_83302E3C(void);
void func_83302E6C(void);
s32 func_83302F48(void);
void func_83302FD8(s32 arg0, s32 arg1);

#endif // _FRAGMENT42_H_
