#ifndef _FRAGMENT57_H_
#define _FRAGMENT57_H_

#include "global.h"
#include "src/6BC0.h"
#include "src/11BA0.h"
#include "src/26820.h"

typedef struct unk_D_82D0AB38 {
    /* 0x00 */ u8 unk_00;
    /* 0x01 */ u8 unk_01;
    /* 0x02 */ u8 unk_02;
    /* 0x03 */ u8 unk_03;
    /* 0x04 */ u8 unk_04;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ char unk_08[1];
    /* 0x09 */ char unk09[0xD];
} unk_D_82D0AB38; // size = 0x16

typedef struct unk_D_82D0ABD0 {
    /* 0x00 */ u8 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ s16 unk_08;
    /* 0x0A */ s16 unk_0A;
    /* 0x0C */ char unk0C[0x4];
} unk_D_82D0ABD0; // size = 0x10

typedef struct unk_D_82D09F1C {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ s8 unk_08;
    /* 0x09 */ s8 unk_09;
    /* 0x0A */ s8 unk_0A;
    /* 0x0B */ s8 unk_0B;
} unk_D_82D09F1C; // size = 0xC

s32 ValidatePIStatus(s32 arg0);
void PrefBackground_Draw(void);
void SetupFramebufferAndFill(FramebufferImage* arg0, s16 arg1, s16 arg2);
void DrawPanelBordered(s16 arg0, s16 arg1, s16 arg2, s16 arg3, u8 arg4, u8 arg5, u8 arg6, u8 arg7);
void DrawSmallPanel(s16 arg0, s16 arg1, s16 arg2, s16 arg3, u8 arg4, u8 arg5, u8 arg6, u8 arg7);
void DrawAnimatedPanel(s16 arg0, s16 arg1, s16 arg2, s16 arg3, u8 arg4, u8 arg5, u8 arg6, u8 arg7);
s32 DrawMenuTextureA(s32 arg0, SimpleGfxNode* arg1);
s32 DrawMenuTextureB(s32 arg0, SimpleGfxNode* arg1);
s32 DrawMenuTextureC(s32 arg0, SimpleGfxNode* arg1);
void PakUi_DrawPartyProgressBar(s32 arg0);
void RenderMenuBackground(s16 arg0);
void DrawMenuItemIcon(s32 arg0);
void DrawMenuItemInfoPanel(u8 arg0);
void SetupMenuPanel(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s8* arg4);
void InitMenuOption(s32 arg0);
void PakUi_BuildIconPanel(void);
void CreateTitlePanel(void);
void UpdateMenuDisplay(s32 arg0, s16 arg1);
void InitializeMenuScreen(void);
void CleanupMenuScreen(void);
s32 TransferPak_ShowRulesPrompt(void);
void DrawNineSlicePanel(s16 arg0, s16 arg1, s16 arg2, s16 arg3, u8 arg4, u8 arg5, u8 arg6, u8 arg7);
void PakUi_DrawMenuOptionText(s16 arg0, s16 arg1, s16 arg2, s16 arg3, char* arg4);
void DrawOptionDetailsPanel(s16 arg0, s16 arg1);
void DrawDetailedInfoPanel(s16 arg0, s16 arg1, unk_func_800281D4* arg2, s32 arg3);
void RenderDetailScreen(s16 arg0, s16 arg1, unk_func_800281D4* arg2, s16 arg3, s16 arg4);
s32 HandleOptionSelection(unk_func_800281D4* arg0);
s16 HandleMainMenu(unk_func_800281D4* arg0);
void DrawStatPanel(unk_D_82D0ABD0* arg0);
s32 UpdateStatPanelState(unk_D_82D0ABD0* arg0);
void StatPanel_Init(unk_D_82D0ABD0* arg0, s16 arg1, s16 arg2);
void StatPanel_SetInfo(unk_D_82D0ABD0* arg0, s16 arg1, s16 arg2);
s32 DrawMenuTextureGeneric(s32 arg0, UNUSED SimpleGfxNode* a1);
s32 GetSinusoidalAlpha(void);
void DrawAudioProgressBar(s32 arg0, s32 arg1);
void DrawAudioSmallPanel(s32 arg0, s32 arg1);
void AnimateMenuOptionNodes(s32 arg0, s32 arg1);
FramebufferImage* CreateSaveDataPanel(s32 arg0);
FramebufferImage* CreateOptionsPanel(void);
FramebufferImage* CreateControlsPanel(void);
FramebufferImage* Menu_CreateBackgroundFrame(void);
FramebufferImage* Menu_CreateOptionFrame(s8* arg0, u8 arg1, u8 arg2, u8 arg3);
void Menu_InitializeOptionNodes(void);
void Menu_Cleanup(void);
s32 TransferPak_MenuHandleInput(void);
s32 Menu_GetResultCode(void);
s16 TransferPak_MenuLoop(void);
void Menu_LoadItemData(void);
void Menu_LoadGraphics(void);
s32 Menu_Main(s32 arg0, s32 arg1);

#endif // _FRAGMENT57_H_
