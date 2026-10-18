#ifndef _FRAGMENT56_H_
#define _FRAGMENT56_H_

#include "global.h"

void Pref_DrawBackground(void);
void Pref_DrawBorderedPanel(s16 arg0, s16 arg1, s16 arg2, s16 arg3, u8 arg4, u8 arg5, u8 arg6, u8 arg7);
void Pref_DrawToggleBar(s16 arg0, s16 arg1);
void Pref_DrawMainPanel(s16 arg0, s32 arg1);
void Pref_DrawAudioSettingsPanel(s32 arg0, s32 arg1, s32 arg2);
void Pref_DrawResetPanel(s32 arg0);
void Pref_RenderScreen(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 Pref_ConfirmReset(s32 arg0);
void Pref_RunResetDemo(void);
void Pref_ClearSaveData(void);
void Pref_ApplyAudioSettingsFromFlags(u16 arg0);
s16 Pref_HandleOptionSelect(void);
void Pref_MainLoop(void);
s32 Pref_Entry(UNUSED s32 arg0, UNUSED s32 arg1);

#endif // _FRAGMENT56_H_
