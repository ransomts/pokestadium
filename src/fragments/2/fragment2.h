#ifndef _FRAGMENT2_H_
#define _FRAGMENT2_H_

#include "global.h"

typedef struct unk_func_87801684 {
    /* 0x00 */ u32* unk_00;
    /* 0x04 */ s16 unk_04;
} unk_func_87801684; // size = 0x8

extern char** gItemNamesBank;
extern s16 gCurrentMenuIndex;
extern u32* gPositiveTextureBank[];
extern u32* gNegativeTextureBank[];
extern u32 gFragment2_1DisplayList[];

extern u16 gMenuRandomSeed;
extern s16 gMenuCursorX;
extern s16 gMenuCursorY;
extern s16 gMiniHudColorDefaults[4];
extern s16 gMenuState;
extern s16 gMenuSubState;
extern s16 gMenuOptionTimers[4];
extern s16 gMenuSelectedOption;
extern s16 gMenuOptionUsedFlags[9];
extern s16 gMenuOptionFlags[4];
extern u32* D_8780FA70;
extern u16 D_8780FC92;
extern u16 D_8780FC94;
extern u16 D_8780FC96;
extern u16 D_8780FC98;


void InitMessageBanks(void);
void UpdateScrollingMessage(void);
void IncrementRandomCounter(void);
u32 GetRandomMod(u32 arg0);
void DrawBorderRect(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void DrawProgressBar(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_878010C8(s16 arg0);
void FillRect(s16 arg0, s16 arg1, s16 arg2, s16 arg3);
void ParseStringAndMeasure(s32* arg0, s32* arg1, char* arg2, char* arg3, s32 arg4);
s32 GetTextWidth(UNUSED TextObject* arg0, char* arg1);
void DrawScaledTextureRect(s32 arg0, s16 arg1, s16 arg2, f32 arg3, f32 arg4);
void DrawUniformScaledTextureRect(s32 arg0, s16 arg1, s16 arg2, f32 arg3);
void func_87801684(s16 arg0, s16 arg1, unk_func_87801684* arg2);
void func_87801754(s16 arg0, s16 arg1, unk_func_87801684* arg2);
void func_87801824(s16 arg0, s16 arg1, unk_func_87801684* arg2);
void func_878018F4(s16 arg0, s16 arg1, unk_func_87801684* arg2);
void func_87801AC0(s16 arg0, s16 arg1, unk_func_87801684* arg2);
void func_87801C8C(s16 arg0, s16 arg1, unk_func_87801684* arg2);
void func_87801D5C(s16 arg0, s16 arg1, s16 arg2, unk_func_87801684* arg3);
void func_87801F48(s16 arg0, s16 arg1, s16 arg2);
void func_878021B4(s16 arg0, s16 arg1);

void Fragment2_1_CalcAnimOffset(s16 arg0, s16 arg1, f32* arg2, f32* arg3);
void Fragment2_1_Init(void);
void Fragment2_1_Update(void);
void Fragment2_1_SetStartFlag(s16 arg0);
s32 Fragment2_1_GetResult(void);

void ResultScreen_Init(void);
void ResetSelectionState(void);
void UpdateDeltaTime(void);
void SetResultFlag(s16 arg0);
void IncrementPlayerScore(s32 arg0);
void CheckScoreThreshold(void);
s32 IsSpecialWinCondition(void);
void FindLowestScorers(void);
s32 GetCurrentOptionCount(void);
void ResultScreen_DrawGradientPanel(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u8* arg4, u8* arg5);
void CreateScaledTranslationMatrix(Mtx* arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8, f32 arg9, f32 argA);
void RenderScoreCubes(s16 arg0);
void ResultScreen_RenderScaledTexture(s32 arg0, u32* arg1, u8 arg2, u8 arg3, s16 arg4, s16 arg5, s16 arg6, s16 arg7, f32 arg8, f32 arg9, f32 argA, f32 argB, f32 argC, f32 argD, f32 argE);
void ResultScreen_DrawTiledTexture(u32* arg0, u16 arg1, UNUSED u16 arg2, u16 arg3, u16 arg4, u8 arg5, u8 arg6);
void ResultScreen_RenderResultGraphics(u8 arg0, s8 arg1, s8 arg2, s8 arg3, s8 arg4);
void ResultScreen_DrawScoreCubes(s16 arg0);
s32 ResultScreen_UpdateAndRender(void);

#endif // _FRAGMENT2_H_
