#ifndef _FRAGMENT47_H_
#define _FRAGMENT47_H_

#include "global.h"
#include "src/30640.h"
#include "src/geo_layout.h"
#include "src/fragments/43/fragment43.h"

typedef struct unk_D_8380565C {
    /* 0x000 */ u32 unk_000;
    /* 0x004 */ PokemonData unk_004[3];
    /* 0x100 */ char unk100[0x6E4];
    /* 0x7E4 */ PokemonData unk_7E4;
} unk_D_8380565C; // size >= 0x838

typedef struct unk_D_838067F0_0168_0000 {
    union {
        struct {
            /* 0x000 */ u8 unk_000;
            /* 0x001 */ u8 unk_001;
            /* 0x002 */ u8 unk_002;
            /* 0x003 */ u8 unk_003;
        };
        s32 raw;
    };
    /* 0x004 */ PokemonData unk_004;
    /* 0x058 */ u16 unk_058[0x640];
} unk_D_838067F0_0168_0000; // size = 0xCD8

typedef struct unk_D_838067F0_0168 {
    /* 0x0000 */ unk_D_838067F0_0168_0000 unk_0000[3];
    /* 0x2688 */ struct unk_D_838067F0_0168* unk_2688;
    /* 0x268C */ struct unk_D_838067F0_0168* unk_268C;
    /* 0x2690 */ s16 unk_2690;
    /* 0x2692 */ s16 unk_2692;
    /* 0x2694 */ char unk2694[0x4];
} unk_D_838067F0_0168; // size = 0x2698

typedef struct unk_D_838067F0_003C {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ u8 unk_02[1];
    /* 0x03 */ char unk03[0x13];
} unk_D_838067F0_003C; // size = 0x16

typedef struct unk_D_838067F0 {
    /* 0x0000 */ s32 unk_0000;
    /* 0x0004 */ s32 unk_0004;
    /* 0x0008 */ s32 unk_0008;
    /* 0x000C */ s32 unk_000C;
    /* 0x0010 */ s32 unk_0010;
    /* 0x0014 */ s32 unk_0014;
    /* 0x0018 */ s32 unk_0018;
    /* 0x001C */ s32 unk_001C;
    /* 0x0020 */ s32 unk_0020;
    /* 0x0024 */ s32 unk_0024;
    /* 0x0028 */ s32 unk_0028;
    /* 0x002C */ s32 unk_002C;
    /* 0x0030 */ s32 unk_0030;
    /* 0x0034 */ s32 unk_0034;
    /* 0x0038 */ s32 unk_0038;
    /* 0x003C */ unk_D_838067F0_003C unk_003C[13];
    /* 0x015C */ unk_D_8380565C* unk_015C;
    /* 0x0160 */ unk_D_838067F0_0168* unk_0160;
    /* 0x0164 */ char unk0164[0x4];
    /* 0x0168 */ unk_D_838067F0_0168 unk_0168[12];
} unk_D_838067F0; // size = 0x1D088

typedef struct unk_D_8380548C {
    /* 0x00 */ u8 unk_00;
    /* 0x01 */ u8 unk_01;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ s16 unk_08;
    /* 0x0A */ s16 unk_0A;
    /* 0x0C */ s16 unk_0C;
} unk_D_8380548C; // size = 0xE

void SnapSelect_Init(s32 arg0);
void SnapSelect_SetTimer(s32 arg0);
void SnapSelect_DrawHeader(s32 arg0, s32 arg1);
void SnapSelect_DrawPrompt(void);
void SnapSelect_Update(void);
void SnapSelect_Prepare(s32 arg0);
void SnapSelect_HandleResult(void);
s32 SnapSelect_Process(void);
void SnapSelect_ReadInputs(void);
void SnapSelect_MainLoop(void);
s32 SnapSelect_FinalizeResult(void);
s32 SnapSelect_Run(s32 arg0, s32 arg1);

s32 RenderPlayerInfoPanel(s32 arg0, GraphNode* arg1);
void UpdateIconPosition(s32 arg0, f32 arg1);
void AnimateIconMovement(s32 arg0, f32 arg1);
void LoadPlayerData(void);
void AssignPlayerIconTexture(void);
void SnapSelect_ConfigureGraphics(void);
void CreatePlayerIconNodes(void);
s32 SnapSelect_ApplySelection(s32 arg0);
void AnimateIconEntry(void);
void SelectPreviousPlayer(void);
void SelectAlternatePlayer(void);
void SelectPreviousSlot(void);
void SelectNextSlot(void);
void HandlePlayerSelectInput(void);
void AnimateIconExit(void);
void AnimateIconSelection(void);
void AnimateIconReset(void);
void HandleRentalSelection(void);
void PlayerSelectStateUpdate(void);
void UpdateSelectionOffset(void);
void DrawPlayerSlotBorder(s32 arg0, s16 arg1, s32 arg2);
void DrawPlayerSlotText(s32 arg0);
void DrawPlayerSelectUI(void);
void SnapSelect_UpdateInputState(s32 arg0);
s32 SnapSelect_GetUserChoice(void);

void SnapSelect_CopyStateToInfo(unk_D_83407B18_008* arg0);
s32 func_838024EC(void);
void SnapSelect_InitBackground(s32 arg0, s32 arg1, unk_D_8380565C* arg2);
s32 SnapSelect_LoadPokemonIndices(unk_D_838067F0* arg0, s32 arg1);
void SnapSelect_ApplyInputModifiers(unk_D_838067F0* arg0, PokemonData* arg1);
s32 SnapSelect_FillPokemonInfo(unk_D_838067F0* arg0, unk_D_838067F0_0168* arg1, s32 arg2, unk_D_8380565C* arg3);
s32 SnapSelect_LoadModeData(s32 arg0, unk_D_83407B18_008* arg1);
void SnapSelect_UpdateTimer(unk_D_838067F0* arg0);
unk_D_838067F0_0168* SnapSelect_AdvanceNode(unk_D_838067F0_0168* arg0, s32 arg1);
void SnapSelect_HandleConfirm(unk_D_838067F0* arg0);
void SnapSelect_HandleCancel(unk_D_838067F0* arg0);
void SnapSelect_NavigateNext(unk_D_838067F0* arg0);
void SnapSelect_NavigatePrev(unk_D_838067F0* arg0);
void func_83803038(unk_D_838067F0* arg0);
void func_838030A8(unk_D_838067F0* arg0);
void func_8380311C(unk_D_838067F0* arg0);
void func_838031F0(unk_D_838067F0* arg0);
void SnapSelect_ProcessInput(unk_D_838067F0* arg0);
void func_838033DC(unk_D_838067F0* arg0);
void func_83803438(unk_D_838067F0* arg0);
void func_83803488(void);
void func_8380355C(s16 arg0, s16 arg1, s16 arg2);
void func_8380369C(s16 arg0, s16 arg1, u8* arg2, s16 arg3);
void func_83803748(unk_D_838067F0* arg0);
void func_83803A80(s32 arg0, s32 arg1, unk_D_838067F0* arg2);
s32 func_83803E94(unk_D_838067F0* arg0);
s32 func_83803F04(unk_D_838067F0_0168* arg0);
void func_83803F34(s32 arg0, s32 arg1, unk_D_838067F0_0168* arg2);
void func_8380419C(s32 arg0, s32 arg1, unk_D_838067F0_0168* arg2);
void SnapSelect_UpdateCameraState(s32 arg0);

#endif // _FRAGMENT47_H_
