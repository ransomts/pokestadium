#ifndef _FRAGMENT42_H_
#define _FRAGMENT42_H_

#include "global.h"
#include "src/30640.h"

void DrawPanelFrame(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u8 arg4, u8 arg5, u8 arg6, u8 arg7);
unk_D_83407B38* GetActiveMenu(void);
void UpdateMenuItemStates(void);
s32 Menu_HandleConfirm(void);
s32 ProcessMenuInput(void);
void ResetMenuState(void);
s32 HandlePokemonGridInput(unk_D_83407B38* arg0);
void Menu_DrawAnimatedSprite(u16* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, f32 arg5, f32 arg6);
void DrawMenuScreen(void);
void DrawSubPanel(s32 arg0, s32 arg1, s32 arg2);
void DrawMessageBox(unk_D_83407B38* arg0, s32 arg1, s32 arg2);
void InitializeMenuState(s32 arg0, s32 arg1);
void Gfx_DrawFadeOverlay(s32 arg0, s32 arg1, s32 arg2, s32 arg3, Color_RGBA8* arg4, Color_RGBA8* arg5);
void DrawBackground(void);
void DrawPokemonGrid(unk_D_83407B38* arg0);
void DrawSelectionHighlight(unk_D_83407B38* arg0);
void Menu_DrawHeader(s32 arg0);
void RenderFrame(void);
void Menu_HandleSwapInput(unk_D_83407B38* arg0);
void Menu_HandleConfirmTimer(void);
void Menu_ProcessResult(void);
void Menu_FadeOutStep(void);
s32 Menu_MainLoopStep(void);
void Menu_PollInputs(void);
void Menu_RunLoop(void);
s32 Menu_GetResult(void);
void Menu_InitializeAndRun(s32 arg0, s32 arg1);

#endif // _FRAGMENT42_H_
