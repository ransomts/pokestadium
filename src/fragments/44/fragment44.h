#ifndef _FRAGMENT44_H_
#define _FRAGMENT44_H_

#include "global.h"
#include "src/30640.h"

s32 ItemSelect_HandleInput(unk_D_83407B38* arg0);
void ItemSelect_Init(s32 arg0, s32 arg1);
void DrawGridCellTexture(s32 arg0, s32 arg1);
void DrawGridPanelTexture(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void DrawResultPanelTexture(s32 arg0, s32 arg1, s32 arg2);
void DrawResultPanelHighlight(s32 arg0, s32 arg1, s32 arg2);
void DrawGridPageCounter(unk_D_83407B38* arg0, s32 arg1, s32 arg2);
void DrawGridCellBorder(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void DrawSlotStatusIcons(s32 arg0, s32 arg1, u16 arg2);
void CalcResultPanelSize(s32 arg0, s32* arg1, s32* arg2, f32* arg3);
void DrawResultPanelImage(u16* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, f32 arg5);
void ItemSelect_DrawGrid(s32 arg0, s32 arg1, unk_D_83407B38* arg2);
void ItemSelect_DrawHeader(unk_D_83407B38* arg0, s32 arg1, s32 arg2);
void DrawGridHelpPrompt(s32 arg0);
void DrawGridBackground(s32 arg0, s32 arg1, unk_D_83407B38* arg2);
void DrawHighlightBars(void);
void DrawAnimatedMonPanel(s32 arg0, s32 arg1, s32 arg2);
void DrawResultScreen(int arg0, int arg1, s32 arg2, f32 arg3);
char* GetGridHelpString(unk_D_83407B38* arg0);
void DrawGridHelpBox(unk_D_83407B38* arg0, s32 arg1, s32 arg2);
f32 UpdateFadeTimer(s32* arg0, u32* arg1, s32 arg2);
void DrawGridSelectionHighlight(unk_D_83407B38* arg0);
void ItemSelect_MainDraw(void);
void AdvanceResultAnim(unk_D_83407B38* arg0);
void BeginFadeOutAfterResult(unk_D_83407B38* arg0);
s32 ItemSelect_StateMachine(void);
void ItemSelect_ReadInputs(void);
void ItemSelect_Loop(void);
s32 ItemSelect_ApplySelection(unk_D_83407B38* arg0);
void func_83503C9C(s32 arg0, s32 arg1);

#endif // _FRAGMENT44_H_
