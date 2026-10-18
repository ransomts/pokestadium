#ifndef _FRAGMENT58_H_
#define _FRAGMENT58_H_

#include "global.h"

void DrawDialogBorderSmall(s16 arg0, s16 arg1);
void DrawDialogBorderLarge(s16 arg0, s16 arg1);
void func_84000200(s16 arg0, s16 arg1, s16 arg2, Color_RGBA8* arg3, Color_RGBA8* arg4);
void DrawTitlePanel(void);
void DrawSelectionBorder(s16 arg0, s16 arg1, s16 arg2, s16 arg3);
void DrawWindow(s16 arg0, s16 arg1, s16 arg2, s16 arg3);
void DrawCustomWindow(s16 arg0, s16 arg1, s16 arg2, s16 arg3, u8 arg4, u8 arg5, u8 arg6, u8 arg7);
s32 IsMenuEntryEnabled(s16 arg0);
void PrintMenuItemChar(s16 arg0, s16 arg1, s16 arg2);
void DrawItemSelectionScreen(void);
void HandleItemSelectInput(void);
void HandleOpponentSelectInput(void);
void ResetMenuSelections(void);
s32 IsAnyMenuOptionSelected(void);
void PrintMenuText(s16 arg0, s16 arg1, s16 arg2, char* arg3);
void func_84001AD8(void);
void DrawRuleDetailsScreen(void);
void HandleRuleOptionInput(void);
void ResetRuleOption(void);
void PrintRuleOptionText(s16 arg0, char* arg1);
void DrawRuleOptionPanel(void);
void InitRuleOptionState(void);
void RuleOption_Next(void);
void RuleOption_Prev(void);
void HandleRuleOptionSelection(void);
void Menu_UpdateInput(void);
void func_840023B8(void);
void Menu_FadeIn(void);
void Menu_FadeOut(void);
void Menu_AnimateWindowIn(void);
void Menu_AnimateWindowOut(void);
void Menu_SetupBattle(void);
s32 func_84002914(void);
s32 RuleMenu_Main(s32 arg0, s32 arg1);

#endif // _FRAGMENT58_H_
