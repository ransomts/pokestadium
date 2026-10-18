#ifndef _FRAGMENT39_H_
#define _FRAGMENT39_H_

#include "global.h"
#include "6BC0.h"

typedef struct unk_D_82508B00 {
    /* 0x00 */ u16 unk_00;
    /* 0x02 */ u16 unk_02;
    /* 0x04 */ u16 unk_04;
    /* 0x06 */ u16 unk_06;
    /* 0x08 */ u16 unk_08;
    /* 0x0A */ s16 unk_0A;
} unk_D_82508B00; // size = 0xC

typedef struct unk_D_8250A288 {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ s16 unk_08;
} unk_D_8250A288; // size >= 0xA

typedef struct UIElementNode {
    /* 0x00 */ char unk00[0x1];
    /* 0x01 */ u8 unk_01;
    /* 0x02 */ char unk02[0x12];
    /* 0x14 */ s32 unk_14;
    /* 0x18 */ char unk18[0x6];
    /* 0x1E */ s16 unk_1E;
    /* 0x20 */ s16 unk_20;
    /* 0x22 */ s16 unk_22;
    /* 0x24 */ Vec3f unk_24;
    /* 0x30 */ Vec3f unk_30;
} UIElementNode; // size >= 0x3C

typedef struct unk_D_8250A228 {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ u16 unk_06;
    /* 0x08 */ s16 unk_08;
    /* 0x08 */ s16 unk_0A;
    /* 0x0C */ s16 unk_0C;
    /* 0x0E */ s16 unk_0E[4];
    /* 0x16 */ char unk16[0x16];
    /* 0x2C */ struct unk_D_8250A228* unk_2C;
    /* 0x30 */ struct unk_D_8250A228* unk_30;
    /* 0x34 */ struct unk_D_8250A228* unk_34;
    /* 0x38 */ FramebufferImage* unk_38;
    /* 0x3C */ UIElementNode unk_3C;
} unk_D_8250A228; // size >= 0x78

typedef struct UIElement {
    /* 0x000 */ s16 unk_000;
    /* 0x002 */ u16 unk_002;
    /* 0x004 */ s16 unk_004;
    /* 0x004 */ u16 unk_006;
    /* 0x008 */ s16 unk_008;
    /* 0x00A */ s16 unk_00A;
    /* 0x00C */ s16 unk_00C;
    /* 0x00E */ s16 unk_00E[4];
    /* 0x018 */ f32 unk_018;
    /* 0x01C */ f32 unk_01C;
    /* 0x020 */ Vec3f unk_020;
    /* 0x02C */ unk_D_8250A228* unk_02C;
    /* 0x030 */ unk_D_8250A228* unk_030;
    /* 0x034 */ s32 unk_034;
    /* 0x034 */ s32 unk_038;
    /* 0x03C */ UIElementNode unk_03C;
    /* 0x078 */ char unk078[0x12C];
} UIElement; // size = 0x1A4

typedef struct unk_D_8250A308 {
    /* 0x000 */ Fragment2_1GraphNode unk_000;
    /* 0x168 */ s16 unk_168;
    /* 0x16A */ s16 unk_16A;
    /* 0x16C */ s16 unk_16C;
    /* 0x16E */ s16 unk_16E;
    /* 0x170 */ s16 unk_170;
} unk_D_8250A308; // size = 0x174

typedef struct unk_D_8250A480 {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ s16 unk_08;
    /* 0x0A */ s16 unk_0A;
    /* 0x0A */ s16 unk_0C;
    /* 0x10 */ f32 unk_10;
    /* 0x14 */ char** unk_14;
} unk_D_8250A480; // size = 0x18

typedef struct unk_D_8250A498 {
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
    /* 0x14 */ char** unk_14;
} unk_D_8250A498; // size = 0x18

extern TextObject* gTextObjectHandle;

s32 DrawStatusIconForPlayer(s32 arg0, GraphNode* arg1);
s32 DrawComputerSelection(s32 arg0, GraphNode* arg1);
s32 DrawComputerRootUI(s32 arg0, GraphNode* arg1);
s32 DrawItemSelectionUI(s32 arg0, GraphNode* arg1);
void UI_Cursor_Init(void);
void UI_Cursor_Update(Fragment2_1GraphNode* a0);
s32 UI_DrawIcon(s32 arg0, GraphNode* arg1);
void ControllerInput_Clear(void);
void ControllerInput_Update(void);
void ToggleInputUpdate(void);
s32 GetSelectedItemId(void);
s32 GetItemIndexById(s32 arg0);
s32 GetCategoryIndex(s16 arg0, s32 arg1);
void InitItemSelectionTimer(void);
void ResetUIElement(UIElement* arg0);
void UI_AnimatedBackground_Draw(UIElement* arg0);
void UI_GradientPanel_Draw(UIElement* arg0);
unk_D_8250A228* UI_Element_Allocate(void);
unk_D_8250A228* UI_Element_Create(s16 arg0, s16 arg1, GraphNode* arg2);
void LinkUIElementsForward(unk_D_8250A228* arg0, unk_D_8250A228* arg1);
void SetUIElementNext(unk_D_8250A228* arg0, unk_D_8250A228* arg1);
void SetUIElementState(unk_D_8250A228* arg0, s16 arg1);
void SetUIElementSelection(unk_D_8250A228* arg0, s16 arg1, s32 arg2);
s32 UI_Element_IsState(unk_D_8250A228* arg0, s16 arg1);
void FadeOutUIElement(UIElement* arg0);
s32 CountUIElementColors(unk_D_8250A228* arg0, s16 arg1);
s32 UpdateUIElementAnimation(UIElement* arg0);
void UpdateAllUIElements(void);
void SelectionState_Clear(void);
void SelectionState_InitDefaults(void);
void SelectionCursor_Update(s16 arg0, s16 arg1);
void SelectionUI_Init(s16 arg0, s16 arg1);
void UI_DrawStatusIcon(void);
void UI_DrawPendingElements(void);
void UI_DrawGradientPanelWithText(void);
void SelectionUI_Render(void);
void SelectionUI_Reset(void);
void UI_HandleMainSelectionInput(void);
void SelectionUI_ConfirmChoice(void);
void ComputerUI_HandleInput(void);
void GradientPanel_Animate(void);
void ComputerUIRoot_HandleInput(void);
s32 ItemGrid_Navigate(s16* arg0, s16 arg1);
s32 SelectionScreen_ProcessRandomSelection(s16* arg0, s16 arg1);
void SelectionScreen_HandleOptionUse(void);
void SelectionScreen_CheckMiniHudAndFade(void);
void RunSelectionScreen(s16 arg0, s16 arg1);
void SelectionScreen_InitResources(void);
s32 SelectionScreen_Entry(s32 arg0, s32 arg1);

void MessageBox_SetBank(char** arg0);
s32 MessageBox_GetState(void);
void MessageBox_SetState(s16 arg0);
void func_82504930(unk_D_8250A480* arg0);
void func_82504A08(unk_D_8250A480* arg0);
void func_82504A68(unk_D_8250A480* arg0);
void SelectionScreen_HandleInput(void);
void Gfx_DrawBorderedBox(s16 arg0, s16 arg1, s16 arg2, s16 arg3, u8 arg4, u8 arg5, u8 arg6, u8 arg7);
void Text_PrintWavy(s16 arg0, s16 arg1, s8* arg2, f32 arg3, s16 arg4);
void MessageBox_Render(void);
void OptionMenu_Init(char** arg0);
void func_825057A0(void);
void OptionMenu_SetSelection(s16 arg0);
void OptionMenu_SetState(s16 arg0, s16 arg1);
void func_82505998(unk_D_8250A498* arg0);
void func_82505A70(unk_D_8250A498* arg0);
void func_82505AB8(unk_D_8250A498* arg0);
void OptionMenu_Update(void);
void OptionMenu_Render(void);

void UpdateMenuRandomSeed(void);
void SetCurrentMenuIndex(s16);
void func_82505FE0(s16);
s16 GetRandomUnusedMenuSlot(void);

#endif // _FRAGMENT39_H_

