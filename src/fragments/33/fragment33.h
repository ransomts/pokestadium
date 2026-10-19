#ifndef _FRAGMENT33_H_
#define _FRAGMENT33_H_

#include "global.h"

typedef struct unk_D_81304008 {
    /* 0x000 */ s16 unk_000;
    /* 0x002 */ s16 unk_002;
    /* 0x004 */ s16 unk_004;
    /* 0x006 */ char unk006[0x2];
    /* 0x008 */ s16 unk_008;
    /* 0x00A */ s16 unk_00A;
    /* 0x00C */ s16 unk_00C;
    /* 0x00E */ s16 unk_00E;
    /* 0x010 */ s16 unk_010;
    /* 0x014 */ f32 unk_014;
    /* 0x018 */ f32 unk_018;
    /* 0x01C */ u8* unk_01C;
    /* 0x020 */ f32 unk_020;
    /* 0x020 */ f32 unk_024;
    /* 0x020 */ Fragment2_1GraphNode unk_028;
} unk_D_81304008; // size = 0x190

typedef struct unk_D_81303FA8 {
    /* 0x00 */ u8 unk_00;
    /* 0x01 */ u8 unk_01;
    /* 0x02 */ u8 unk_02;
    /* 0x03 */ u8 unk_03;
    /* 0x04 */ u8 unk_04;
    /* 0x05 */ char unk05[0x1];
    /* 0x06 */ u16 unk_06;
    /* 0x08 */ char unk_08[1];
    /* 0x09 */ char unk09[0xD];
} unk_D_81303FA8; // size = 0x16

s32 GraphNode_RenderMenu(s32 arg0, GraphNode* arg1);
s32 GetPlayerNameLength(void);
void StartEntrySelection(void);
s32 GetEntryStatus(s32 arg0);
s32 GetEntryMenuOption(s32 arg0);
void DrawEntryPanel(s32 arg0, s32 arg1, s32 arg2);
void TransferPak_DrawSpinningPakIcon(u8* arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, f32 arg5);
void UpdatePulseAlpha(void);
void DrawTextureRectFlipped(u8* arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, f32 arg5, s16 arg6);
void DrawBorderedPanel(s16 arg0, s16 arg1, s16 arg2, s16 arg3, u8 arg4, u8 arg5, u8 arg6, u8 arg7);
void RenderMenuScreen(void);
void HandleEntryNavigation(void);
void HandleEntryConfirmCancel(void);
void Menu_InitInput(void);
void TransferPak_DrawFrame(s32 arg0);
void Menu_UpdateEntryData(void);
void Menu_SelectDefaultEntry(void);
void Menu_UpdateEntryAnimations(void);
s32 Menu_RunScreen(s32 arg0);
void Menu_InitEntryNodes(void);
void Menu_InitGeo(void);
s32 Menu_EntrySelection_Init(s32 arg0, s32 arg1);
void Gfx_DrawBackgroundGrid(u8* arg0);
void Gfx_DrawMenuBackground(void);

#endif // _FRAGMENT33_H_
