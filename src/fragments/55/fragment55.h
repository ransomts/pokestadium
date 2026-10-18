#ifndef _FRAGMENT55_H_
#define _FRAGMENT55_H_

#include "global.h"
#include "src/29BA0.h"

typedef struct unk_D_83003CE0 {
    /* 0x00 */ char* unk_00[29];
    /* 0x74 */ char* unk_74;
    /* 0x78 */ char* unk_78;
    /* 0x7C */ char* unk_7C;
    /* 0x80 */ char* unk_80;
    /* 0x84 */ char* unk_84;
    /* 0x88 */ char* unk_88;
    /* 0x8C */ char* unk_8C;
    /* 0x90 */ char* unk_90;
    /* 0x94 */ char* unk_94;
    /* 0x98 */ char* unk_98;
    /* 0x9C */ char unk9C[0x64];
} unk_D_83003CE0; // size = 0x100

typedef struct unk_D_83079E70_014_000 {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
} unk_D_83079E70_014_000; // size = 0x4

typedef struct unk_D_83079E70_000 {
    /* 0x00 */ unk_D_83079E70_014_000 unk_00[6];
    /* 0x18 */ struct unk_D_83079E70_000* unk_18;
    /* 0x1C */ struct unk_D_83079E70_000* unk_1C;
} unk_D_83079E70_000; // size = 0x20

typedef struct unk_D_83079E70 {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ s16 unk_08;
    /* 0x0A */ s16 unk_0A;
    /* 0x0C */ s16 unk_0C;
    /* 0x10 */ unk_D_83079E70_000* unk_10;
    /* 0x14 */ unk_D_83079E70_000 unk_14[6];
} unk_D_83079E70; // size = 0xD4

extern unk_D_83003CE0 gMenuStaticStrings;
extern unk_D_83003CE0 gMenuOptionStrings;

extern char** D_830039C0;

char* GetBattleModeMessage(s32 arg0);
void BattleMode_LoadAssets(void);
void MenuInput_Update(void);
s16* GetMenuOptionList(unk_D_800AE540* arg0);
char* GetBattleModeTitle(s8 arg0);
char* GetBattleModeSubtitle(s8 arg0);
s32 MenuOptionStringsMissing(s16* arg0);
void FadeIn_Update(void);
void MenuInput_HandleSelection(void);
void Menu_CheckDialogComplete(void);
void FadeOut_Update(void);
s32 FadeOut_IsComplete(void);
void DrawBattleModeBackground(void);
void DrawLoadingBar(void);
void func_83000F10(s16 arg0, s16 arg1, s16 arg2, s16 arg3);
void DrawColoredPanel(s16 arg0, s16 arg1, s16 arg2, s16 arg3, u8 arg4, u8 arg5, u8 arg6);
void DrawMenuIcon(s16 arg0, s16 arg1);
void DrawMenuOptions(s16 arg0, s16 arg1);
void DrawSelectionMenu(void);
void BattleModeMenu_Render(void);
void Menu_InitStaticStrings(void);
void Menu_InitOptionStrings(void);
void BattleModeMenu_Init(void);
s32 BattleModeMenu_UpdateState(void);
void BattleModeMenu_MainLoop(void);
s32 BattleModeMenu_Entry(UNUSED s32 arg0, UNUSED s32 arg1);

s32 GetStringLineCount(s8* arg0);
void Dialog_UpdateOpening(void);
void Dialog_WaitForInput(void);
void Dialog_UpdateClosing(void);
void Dialog_CloseImmediately(void);
void Dialog_UpdateStateMachine(void);
void Dialog_Render(void);
void Dialog_Start(s16 arg0);
s32 Dialog_IsActive(void);
s32 Dialog_GetAnimProgress(void);

s32 PokemonFlagCheck(s16 arg0, s16 arg1);
s16 GetPokemonCountByFilter(s16 arg0);
s32 FillPokemonSelectionList(unk_D_83079E70_000* arg0, s16 arg1, s16 arg2);
unk_D_83079E70_000* GetSelectionNodeByOffset(unk_D_83079E70_000* arg0, s32 arg1);
s32 MoveSelectionUp(unk_D_83079E70* arg0);
s32 MoveSelectionDown(unk_D_83079E70* arg0);
void UpdateSelectionOpenTimer(unk_D_83079E70* arg0);
void HandleSelectionInput(unk_D_83079E70* arg0);
void UpdateSelectionCloseTimer(unk_D_83079E70* arg0);
void UpdateSelectionConfirmTimer(unk_D_83079E70* arg0);
void func_83002C74(s16 arg0, s16 arg1, unk_D_83079E70* arg2);
void func_83002F9C(s16 arg0, s16 arg1);
void DrawPokemonSelectionEntries(s16 arg0, s16 arg1, unk_D_83079E70_000* arg2);
void func_830032D8(s32 arg0);
void func_830033F0(void);
void RenderSelectionMenu(void);
void func_830038DC(void);
s32 func_83003988(void);
s32 func_830039AC(void);


#endif // _FRAGMENT55_H_
