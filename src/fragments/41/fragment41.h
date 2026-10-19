#ifndef _FRAGMENT41_H_
#define _FRAGMENT41_H_

#include "global.h"
#include "src/1AB70.h"
#include "src/29BA0.h"

typedef struct PickerPokemonEntry {
    /* 0x00 */ u8 unk_00;
    /* 0x01 */ char unk01[0xD];
    /* 0x0E */ u16 unk_0E;
    /* 0x10 */ char unk10[0x14];
    /* 0x24 */ u8 unk_24;
    /* 0x25 */ char unk25[0xB];
    /* 0x30 */ char unk_30[11];
    /* 0x3B */ char unk_3B[11];
    /* 0x46 */ char unk46[0xA];
    /* 0x50 */ s32 force_align;
} PickerPokemonEntry; // size = 0x54

typedef struct PickerPokemonGroup {
    /* 0x000 */ s16 unk_000;
    /* 0x004 */ struct PickerPokemonGroup* unk_004;
    /* 0x008 */ struct PickerPokemonGroup* unk_008;
    /* 0x00C */ PickerPokemonEntry unk_00C[20];
} PickerPokemonGroup; // size = 0x69C

typedef struct PickerState {
    /* 0x0000 */ s16 unk_0000;
    /* 0x0002 */ s16 unk_0002;
    /* 0x0004 */ s16 unk_0004;
    /* 0x0006 */ s16 unk_0006;
    /* 0x0008 */ s16 unk_0008;
    /* 0x000A */ s16 unk_000A;
    /* 0x000C */ s16 unk_000C;
    /* 0x000E */ s16 unk_000E;
    /* 0x0010 */ s16 unk_0010;
    /* 0x0012 */ s16 unk_0012;
    /* 0x0014 */ s16 unk_0014;
    /* 0x0016 */ s16 unk_0016;
    /* 0x0018 */ s16 unk_0018;
    /* 0x001A */ s16 unk_001A;
    /* 0x001C */ s16 unk_001C;
    /* 0x001E */ s16 unk_001E;
    /* 0x0020 */ s16 unk_0020;
    /* 0x0022 */ char unk0022[0x6];
    /* 0x0028 */ u16 unk_0028[0x640];
    /* 0x0CA8 */ PickerPokemonGroup pokemonGroups[13];
    /* 0x6294 */ char unk6294[0x4];
} PickerState; // size = 0x6298

typedef struct RentalItemInfo {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ s16 unk_08;
    /* 0x0C */ PickerPokemonEntry* unk_0C;
} RentalItemInfo; // size = 0x10

typedef struct unk_D_82F14450 {
    /* 0x00 */ u8 unk_00;
    /* 0x01 */ u8 unk_01;
    /* 0x02 */ u8 unk_02;
    /* 0x03 */ u8 unk_03;
    /* 0x04 */ u8 unk_04;
    /* 0x05 */ u8 unk_05;
    /* 0x06 */ u16 unk_06;
    /* 0x08 */ char unk_08[1];
    /* 0x09 */ char unk09[0xD];
} unk_D_82F14450; // size = 0x16

typedef struct unk_D_82F13B78 {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ char* unk_04;
} unk_D_82F13B78; // size = 0x8

typedef struct unk_D_82F20A10 {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ s16 unk_08;
    /* 0x0A */ s16 unk_0A;
    /* 0x0C */ s16 unk_0C;
    /* 0x0E */ s16 unk_0E;
    /* 0x10 */ s16 unk_10;
    /* 0x14 */ PokemonData* unk_14;
    /* 0x18 */ PickerState* unk_18;
    /* 0x1C */ s32 unk_1C;
    /* 0x20 */ AssetManager* unk_20;
    /* 0x24 */ unk_func_8001B1FC* unk_24;
} unk_D_82F20A10; // size >= 0x28

typedef struct PanelRect {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
} PanelRect; // size = 0x8

typedef struct unk_D_82F20A40 {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ PanelRect unk_06;
    /* 0x0E */ PanelRect unk_0E[3];
    /* 0x26 */ PanelRect unk_26;
    /* 0x2E */ PanelRect unk_2E;
    /* 0x36 */ PanelRect unk_36;
    /* 0x40 */ PanelRect* unk_40;
    /* 0x44 */ PanelRect* unk_44;
} unk_D_82F20A40; // size = 0x48

typedef struct unk_D_82F20A88 {
    /* 0x000 */ s16 unk_000;
    /* 0x002 */ s16 unk_002;
    /* 0x004 */ s16 unk_004;
    /* 0x006 */ s16 unk_006;
    /* 0x008 */ s16 unk_008;
    /* 0x00A */ s16 unk_00A;
    /* 0x00C */ s16 unk_00C;
    /* 0x00E */ s16 unk_00E;
    /* 0x010 */ s16 unk_010;
    /* 0x012 */ s16 unk_012;
    /* 0x014 */ s16 unk_014;
    /* 0x018 */ f32 unk_018;
    /* 0x01C */ f32 unk_01C;
    /* 0x020 */ f32 unk_020;
    /* 0x024 */ u8* unk_024;
    /* 0x028 */ Fragment2_1GraphNode unk_028;
} unk_D_82F20A88; // size = 0x190

typedef struct RentalMenuState {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ u16 unk_04;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ s16 unk_08;
    /* 0x0A */ s16 unk_0A;
    /* 0x0C */ s16 unk_0C;
    /* 0x0E */ s16 unk_0E;
    /* 0x10 */ s16 unk_10;
    /* 0x12 */ s16 unk_12;
    /* 0x14 */ PanelRect unk_14[2];
    /* 0x24 */ PanelRect unk_24;
    /* 0x2C */ PanelRect unk_2C;
    /* 0x34 */ PanelRect unk_34;
} RentalMenuState; // size = 0x3C

typedef struct unk_D_82F21160 {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ s16 unk_08;
    /* 0x0A */ s16 unk_0A;
    /* 0x0C */ s16 unk_0C;
    /* 0x0E */ s16 unk_0E;
    /* 0x10 */ s16 unk_10;
    /* 0x12 */ s16 unk_12;
    /* 0x14 */ f32 unk_14;
    /* 0x18 */ f32 unk_18;
    /* 0x1C */ f32 unk_1C;
} unk_D_82F21160; // size = 0x20

typedef struct unk_D_82F21140 {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ s16 unk_08;
    /* 0x0A */ s16 unk_0A;
    /* 0x0C */ u16 unk_0C;
    /* 0x0E */ s16 unk_0E;
    /* 0x10 */ f32 unk_10;
    /* 0x14 */ u16 unk_14;
    /* 0x16 */ u16 unk_16;
    /* 0x18 */ s16 unk_18;
} unk_D_82F21140; // size = 0x1C

typedef struct unk_D_82F211A0_010 {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s16 unk_04;
} unk_D_82F211A0_010; // size = 0x6

typedef struct unk_D_82F211A0 {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x00 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ s16 unk_08;
    /* 0x0A */ s16 unk_0A;
    /* 0x0C */ s16 unk_0C;
    /* 0x0E */ s16 unk_0E;
    /* 0x10 */ unk_D_82F211A0_010 unk_10[10];
} unk_D_82F211A0; // size = 0x4C

typedef struct unk_D_82F21238 {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ s16 unk_08;
    /* 0x0A */ s16 unk_0A;
    /* 0x0C */ s16 unk_0C;
    /* 0x0E */ s16 unk_0E;
    /* 0x10 */ s16 unk_10;
    /* 0x12 */ s16 unk_12;
    /* 0x14 */ s16 unk_14;
    /* 0x16 */ s16 unk_16;
    /* 0x18 */ s16 unk_18;
    /* 0x1A */ s16 unk_1A;
    /* 0x1C */ s16 unk_1C;
    /* 0x1E */ s16 unk_1E;
    /* 0x20 */ s32 unk_20;
    /* 0x24 */ PokemonData* unk_24;
    /* 0x28 */ AssetManager* unk_28;
    /* 0x2C */ unk_func_8001B1FC* unk_2C;
    /* 0x30 */ PanelRect unk_30;
} unk_D_82F21238; // size = 0x38

extern s32 gFragment41FrameCounter;
extern unk_D_82F14450 gPlayerInfo[4];

extern char** D_82F13B70;
extern char** D_82F13B74;

char* GetMessageStringBank24(s32 arg0);
char* GetMessageStringBank25(s32 arg0);
char* GetMessageStringBank26Remapped(s32 arg0);
void InitProgressBarRect(s16 arg0);
void ResetProgressBar(void);
void UpdateProgressBar(void);
void InitTextBox(void);
void SetTextBox(s16 arg0, s16 arg1, s8* arg2, s32 arg3);
void ClearMessageList(void);
void LoadNextMessageEntry(unk_D_82F13B78* arg0, s32 arg1);
s32 IsMessageEntryEmpty(unk_D_82F13B78* arg0);
void UpdateTextBox(void);
s32 GetTextBoxState(void);
void DrawTextBox(void);
void PollControllerInputs(void);
void UpdateControllerInfo(void);
void SwapPlayerSelections(void);
void func_82F00960(void);
void InitFragment41(void);
void RenderFragment41Frame(void);
void Trade_SetState(s32 arg0);
void Trade_ChangeTopic(s16 arg0);
void Trade_UpdateMainMenu(void);
void Trade_UpdateWaitForBoxConfirm(void);
void Trade_UpdateWaitForCableCondition(void);
void Trade_UpdateWaitForPickSelection(void);
void Trade_UpdateWaitForDepositSave(void);
void Trade_UpdateWaitForWithdrawSave(void);
s32 Trade_Update(void);
void Trade_Loop(void);
s32 Trade_Main(s32 arg0, s32 arg1);

s16 LoadPokemonFromGbsBlock(PickerState* arg0, s16 arg1);
u16* GetSpriteDataPtr(u8* arg0, s16 arg1, s16 arg2);
void InitPokemonPicker(s32 arg0, s16 arg1);
s32 GetPickerState(void);
void PickerCountdownTick(PickerState* arg0);
void HandlePickerInput(PickerState* arg0);
void Picker_SlideTransition(PickerState* arg0);
void Picker_HandleBattleStart(PickerState* arg0);
void Picker_ExitAnimation(PickerState* arg0);
void Picker_DrawFrame(s16 arg0, s16 arg1, s16 arg2, s16 arg3);
void Picker_DrawHeader(s16 arg0, s16 arg1, s16 arg2);
void Picker_DrawRect(s16 arg0, s16 arg1, s16 arg2, s16 arg3, Color_RGB8* arg4, s16 arg5);
void Picker_DrawSlot(s16 arg0, s16 arg1, s16 arg2);
void DrawNumberSprite(s16 arg0, s16 arg1, s16 arg2);
void Picker_DrawCursor(s16 arg0, s16 arg1, s16 arg2, s16 arg3);
void Picker_DrawListBackground(s16 arg0, s16 arg1, s16 arg2);
void Picker_DrawPanelBorder(s16 arg0, s16 arg1, s16 arg2, s16 arg3, u8 arg4, u8 arg5, u8 arg6, u8 arg7);
void Picker_DrawLargePanelBorder(s16, s16, s16, s16, u8, u8, u8, u8);
void Picker_DrawListSlot(s16 arg0, s16 arg1, u8* arg2, s16 arg3);
void DrawPokemonListUI(PickerState* arg0, s16 arg1, s16 arg2, s32 arg3);
void DrawStatusPanel(s16 arg0, s16 arg1, s16 arg2);
void UpdateAndRenderPicker(PickerState* arg0);
void Picker_Reset(void);
void Picker_Update(void);
void Picker_Render(void);
u16* Picker_GetSelectedSprite(s32);
void Picker_SwapSelectedSprites(void);
s32 Picker_GetSelectionInfo(s32 arg0, RentalItemInfo* arg1);

void Picker_SetSelectedSprite(s16, PokemonData*);
void BattleResultScreen_Start(PickerState* arg0, u8* arg1, s16 arg2, s16 arg3);
void BattleResultScreen_UpdateTimer(unk_D_82F20A10* arg0);
void BattleResultScreen_HandleInput(unk_D_82F20A10* arg0);
void BattleResultScreen_Close(unk_D_82F20A10* arg0);
void Gfx_FillRectRGBA5551(s16 arg0, s16 arg1, s16 arg2, s16 arg3, u8 arg4, u8 arg5, u8 arg6);
void Gfx_DrawBorderedRect(s16 arg0, s16 arg1, s16 arg2, s16 arg3, u8 arg4, u8 arg5, u8 arg6);
void Gfx_DrawVerticalFade(s16 arg0, s16 arg1, s32 arg2);
void Gfx_DrawNumberSprite(s16 arg0, s16 arg1, s16 arg2);
s32 IsInvalidMoveId(s32 arg0);
void BattleResultScreen_Draw(unk_D_82F20A10* arg0);
void Trade_ResetInfoBox(void);
void Trade_UpdateInfoBox(void);
void Trade_DrawInfoBoxIfActive(void);
s32 Trade_GetInfoBoxState(void);

s32 RenderPlayerSlot(s32 arg0, GraphNode* arg1);
s16 GetSlotTypeFromPlayerInfo(unk_D_82F14450* arg0);
void InitPlayerSlots(s16 arg0);
void SetSlotState(unk_D_82F20A88* arg0, s16 arg1);
void Trade_UpdateBoxSlotFlyIn(unk_D_82F20A88* arg0);
void Trade_UpdateBoxSlotBob(unk_D_82F20A88* arg0);
void Trade_UpdateBoxSlotBobIdle(unk_D_82F20A88* arg0);
void Trade_UpdateBoxSlotFlyOut(unk_D_82F20A88* arg0);
void Trade_UpdateBoxSlotFadeOut(unk_D_82F20A88* arg0);
void Trade_UpdateBoxSlotShrink(unk_D_82F20A88* arg0);
void UpdateAllSlots(void);
void Trade_ResetBoxMachineFlow(void);
s32 Trade_GetSelectedBox(s16 arg0);
s32 Trade_GetBoxMachineFlowState(void);
void Trade_UpdateBoxMachineFlowOpen(unk_D_82F20A40* arg0, s32 arg1);
void HandleMenuInput(unk_D_82F20A40* arg0);
void Trade_UpdateBoxMachineFlowFrameMove(unk_D_82F20A40* arg0);
void Trade_UpdateBoxMachineFlowConfirmWait(unk_D_82F20A40* arg0);
void Trade_UpdateBoxMachineFlowFrameReturn(unk_D_82F20A40* arg0);
void Trade_UpdateBoxMachineSlots(unk_D_82F20A40* arg0, s16 arg1, s16 arg2);
void Trade_UpdateBoxMachineFlowPanelsFull(unk_D_82F20A40* arg0);
void Trade_UpdateBoxMachineFlowConfirmOpen(unk_D_82F20A40* arg0);
void Trade_UpdateBoxMachineFlowConfirmInput(unk_D_82F20A40* arg0);
void Trade_UpdateBoxMachineRect(PanelRect* arg0, s16 arg1, s16 arg2);
void Trade_UpdateBoxMachineFlowConfirmDone(unk_D_82F20A40* arg0);
void Trade_UpdateBoxMachineFlowClose(unk_D_82F20A40* arg0);
void Trade_DrawBoxMachineTopBar(unk_D_82F20A40* arg0);
void Trade_DrawBoxMachineSlots(unk_D_82F20A40* arg0);
void Trade_DrawBoxMachineTitle(unk_D_82F20A40* arg0);
void Trade_DrawBoxMachineConfirm(unk_D_82F20A40* arg0);
void Trade_DrawBoxMachineBanner(unk_D_82F20A40* arg0);
void Trade_DrawBoxMachineTransferArrows(s16 arg0, s16 arg1);
void Trade_DrawBoxMachineCursor(s16 arg0);
void InitMenuGraphics(void);
void UpdateMenuStateMachine(void);
void Trade_DrawBoxMachine(void);

s32 LoadRentalItemData(RentalItemInfo* arg0);
s32 InitRentalItems(RentalMenuState* arg0);
void RentalMenu_Init(s32 arg0);
void RentalMenu_UpdatePanels(RentalMenuState* arg0);
void RentalMenu_HandleSelection(RentalMenuState* arg0);
void RentalMenu_ConfirmWait(RentalMenuState* arg0);
void RentalMenu_ShowItemDetailsA(RentalMenuState* arg0);
void RentalMenu_ShowItemDetailsB(RentalMenuState* arg0);
void RentalMenu_ShowOptions(RentalMenuState* arg0);
void RentalMenu_ProcessItemSelection(RentalMenuState* arg0);
void RentalMenu_Finalize(RentalMenuState* arg0);
void Trade_DrawSaveSeqBoxThumbnail(s16 arg0, s16 arg1, s16 arg2);
void RentalMenu_RenderItemList(RentalMenuState* arg0);
void RentalMenu_DrawPanels(RentalMenuState* arg0);
void Trade_DrawSaveSeqBannerPanel(RentalMenuState* arg0);
void Trade_DrawSaveSeqSubBanner(RentalMenuState* arg0);
void Trade_DrawSaveSeqMessageBackdrop(s16 arg0, s16 arg1, s16 arg2, s16 arg3);
void RentalMenu_DrawMessage(RentalMenuState* arg0);
s32 Trade_GetSaveSeqState(void);
s32 Trade_GetSaveDirection(void);
s32 Trade_GetSaveSlotIndex(void);
void Trade_ResetSaveSeq(void);
void Trade_UpdateSaveSeq(void);
void Trade_DrawSaveSeq(void);

void Gfx_DrawScisTextureRect(s16 arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5, s16 arg6, s16 arg7, s32 arg8);
void MenuBar_ResetState(void);
void MenuBar_SetState(s32 arg0, s16 arg1);
void MenuBar_UpdateFade(unk_D_82F211A0* arg0);
void MenuBar_UpdatePulse(unk_D_82F211A0* arg0);
void MenuBar_AddParticle(unk_D_82F211A0* arg0);
void MenuBar_UpdateParticles(unk_D_82F211A0* arg0);
void MenuBar_UpdateSlide(unk_D_82F211A0* arg0);
void MenuBar_ProcessAll(void);
void MenuBar_Render(void);
void ScreenTransition_Reset(void);
void ScreenTransition_Init(unk_D_82F21238* arg0, s32 arg1);
void ScreenTransition_Start(s16 arg0);
void ScreenTransition_UpdateAnim(unk_D_82F21238* arg0);
void ScreenTransition_Expand(unk_D_82F21238* arg0);
s32 IsSpecialPokemonId(s32 arg0);
void ScreenTransition_HandleInput(unk_D_82F21238* arg0);
void ScreenTransition_Shrink(unk_D_82F21238* arg0);
s32 MessageString_Equals(s16 arg0, s8* arg1);
void PokemonData_UpdateNameIfSpecial(s16 arg0, PokemonData* arg1);
void ScreenTransition_ApplyPokemonUpdate(unk_D_82F21238* arg0);
void ScreenTransition_ShrinkReverse(unk_D_82F21238* arg0);
void ScreenTransition_Collapse(unk_D_82F21238* arg0);
void ScreenTransition_Process(void);
void DrawTransitionOverlay(s16 arg0, s16 arg1, s16 arg2);
void DrawMenuPanelBorder(s16 arg0, s16 arg1, s16 arg2, s16 arg3);
void DrawTransitionImage(unk_D_82F21238* arg0);
void func_82F0ECA4(void);
void DrawTransitionText(PanelRect* arg0, PokemonData* arg1);
void ScreenTransition_Render(void);
void MenuPanel_ResetState(void);
void MenuPanel_SetState(s32 arg0, s16 arg1);
void MenuPanel_UpdateFade(unk_D_82F21160* arg0);
void MenuPanel_UpdatePulse(unk_D_82F21160* arg0);
void MenuPanel_UpdateExpand(unk_D_82F21160* arg0);
void MenuPanel_UpdateBounce(unk_D_82F21160* arg0);
void MenuPanel_SlideOut(unk_D_82F21160* arg0);
void MenuPanel_SlideIn(unk_D_82F21160* arg0);
void MenuPanel_BounceLoop(unk_D_82F21160* arg0);
void MenuPanel_ShrinkOut(unk_D_82F21160* arg0);
void MenuPanel_ProcessAll(void);
void DrawMenuPanel(s16 arg0, s16 arg1, f32 arg2, s16 arg3);
void MenuPanel_RenderAll(void);
s32 MenuPanel_IsAnimating(void);
void MenuPanel_SetMainState(s16 arg0);
void MenuPanel_UpdateState(unk_D_82F21140* arg0);
void MenuPanel_AnimateIntro(unk_D_82F21140* arg0);
void MenuPanel_AnimateSlide(unk_D_82F21140* arg0);
void MenuPanel_AnimateWait(unk_D_82F21140* arg0);
void MenuPanel_AnimateExit(unk_D_82F21140* arg0);
void MenuPanel_AnimateWait2(unk_D_82F21140* arg0);
void MenuPanel_AnimateSlideOut(unk_D_82F21140* arg0);
void MenuPanel_HandleBarConfirm(unk_D_82F21140* arg0);
void MenuPanel_WaitForBarConfirm(unk_D_82F21140* arg0);
void MenuPanel_AnimateFadeOutLeft(unk_D_82F21140* arg0);
void MenuPanel_WaitForScreenTransitionLeft(unk_D_82F21140* arg0);
void MenuPanel_AnimateFadeOutRight(unk_D_82F21140* arg0);
void MenuPanel_WaitForScreenTransitionRight(unk_D_82F21140* arg0);
void MenuPanel_AnimateExitDown(unk_D_82F21140* arg0);
void MenuPanel_AnimateOutro(unk_D_82F21140* arg0);
void MenuPanel_DrawMainBG(s16 arg0, s16 arg1, f32 arg2);
void MenuPanel_DrawLargeButton(s16 arg0, s16 arg1, f32 arg2, s16 arg3, s16 arg4, s16 arg5);
void MenuPanel_DrawMediumButton(s16 arg0, s16 arg1, f32 arg2, s16 arg3, s16 arg4, s16 arg5);
void MenuPanel_DrawSmallButton(s16 arg0, s16 arg1, f32 arg2, s16 arg3, s16 arg4, s16 arg5);
void MenuPanel_DrawTallBar(s16 arg0, s16 arg1, f32 arg2, s16 arg3, s16 arg4, s16 arg5);
void MenuPanel_DrawTallBarHighlight(s16 arg0, s16 arg1, f32 arg2, s16 arg3, s16 arg4, s16 arg5, s16 arg6);
void MenuPanel_DrawSquareBG(s16 arg0, s16 arg1, f32 arg2, s16 arg3, s16 arg4, s16 arg5);
void MenuPanel_DrawAnimatedBG(void);
void MenuPanel_DrawSquareBGWithAlpha(s16 arg0, s16 arg1, f32 arg2, s16 arg3, s16 arg4, s16 arg5);
void MenuPanel_Init(void);
void MenuPanel_Update(void);
void MenuPanel_Render(void);
s32 MenuPanel_CheckState(s16 arg0);
void MenuPanel_SetStateVar(s16 arg0);
s16 MenuPanel_GetState(void);

#endif // _FRAGMENT41_H_
