#ifndef _FRAGMENT43_H_
#define _FRAGMENT43_H_

#include "global.h"
#include "30640.h"

typedef struct MenuPanelInfo {
    /* 0x00 */ s16 unk_00;
    /* 0x00 */ s16 unk_02;
    /* 0x00 */ s16 unk_04;
    /* 0x00 */ s16 unk_06;
    /* 0x00 */ s8 unk_08;
    /* 0x00 */ s8 unk_09;
    /* 0x00 */ s16 unk_0A;
    /* 0x00 */ s16* unk_0C;
} MenuPanelInfo; // size = 0x10

typedef struct unk_D_83407B18_008 {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ s16 unk_08;
    /* 0x0A */ char unk_0A[0x2];
} unk_D_83407B18_008; // size >= 0xC

typedef struct unk_D_83407B18 {
    /* 0x00 */ unk_D_83407B00 unk_00;
    /* 0x08 */ unk_D_83407B18_008 unk_08;
    /* 0x14 */ char unk14[0x4];
} unk_D_83407B18; // size = 0x18

extern unk_D_83402EE0 D_83402EE0[24];
extern s32 D_83403C00[24];
extern unk_D_83403C60 D_83403C60[36];
extern unk_D_83403C60 D_834063C0[21];
extern unk_D_83403C60* D_83407ABC;
extern unk_D_83403C60* D_83407AC0;
extern unk_D_83407AC8 D_83407AC8;
extern s32 D_83407AE4;
extern s32 D_83407AE8;
extern s32 D_83407AEC;
extern unk_D_83407B00 D_83407AF8;
extern unk_D_83407B00 D_83407B00;
extern unk_D_83407B00 D_83407B08;
extern unk_D_83407B00 D_83407B10;
extern unk_D_83407B18 D_83407B18;
extern unk_D_83407B00 D_83407B30;
extern unk_D_83407B38 D_83407B38;

extern s32 D_83402E20;
extern s32 D_83402E24;
extern s32 D_83402E28;

void Gallery_Init(void);
s32 func_834002C4(unk_D_83406EB0* arg0);
s32 func_834002E4(unk_D_83406EB0* arg0);
s32 func_83400304(unk_D_83403C60* arg0, unk_D_83403C60* arg1, s32 arg2);
s32 func_83400334(void);
s32 Gallery_SaveChanges(s32 arg0, s32 arg1);
void Gallery_Terminate(void);
void Gallery_Reset(void);
void func_83400570(unk_D_83403C60* arg0);
void func_83400590(unk_D_83403C60* arg0, unk_D_83403C60* arg1);
s32 func_83400660(unk_D_83403C60* arg0, unk_D_83403C60* arg1);
void func_83400694(unk_D_83403C60* arg0);
unk_D_83403C60* func_834006A0(s32 arg0);
void GallerySelection_Init(unk_D_83407B00* arg0);
s32 func_834006CC(s8* arg0);
s32 CountDisplayableMonIndices(unk_D_83403C60* arg0, s32 arg1, s32 arg2);
s32 FindNthDisplayableMonIndex(unk_D_83403C60* arg0, s32 arg1, s32 arg2, s32 arg3);
s32 FindFirstUndisplayedMonIndex(unk_D_83403C60* arg0, s32 arg1);
void func_834008DC(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_83400928(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u8 arg4, u8 arg5, u8 arg6, u8 arg7);
void DrawPanelWithTextures(s32 arg0, s32 arg1, s32 arg2, Color_RGBA8* arg3, Color_RGBA8* arg4);
void DrawVerticalTextureStrip(u16* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);
void func_834016C8(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void DrawRectBorder(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void func_83401818(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_834018C0(u16* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6);
void func_83401B48(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_83401D0C(s32 arg0, s32 arg1, s32 arg2);
void CamList_Init(unk_D_83407B38* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, unk_D_86002F58_004_000_010* arg5,
    BinArchive* arg6, unk_D_83403C60* arg7, s32 arg8, s32 arg9);
void CamList_Update(unk_D_83407B38* arg0);
void func_834020D8(void);
s32 func_83402124(unk_D_83407B38* arg0, s32 arg1);
void Selection_Reset(unk_D_83407B00* arg0);
void func_834021D8(unk_D_83407B38* arg0, unk_D_83407B00* arg1);
void func_834021EC(unk_D_83407B38* arg0, unk_D_83407B00* arg1);
void func_83402210(unk_D_83407B38* arg0, s32* arg1, s32* arg2, s32 arg3);
s32 func_83402280(unk_D_83407B38* arg0, s32 arg1, s32 arg2);
void func_83402298(unk_D_83407B38* arg0, unk_D_86002F58_004_000_010* arg1, BinArchive* arg2);

void Text_LoadMessageBanks(void);
char* Text_GetMessageString_Bank2C(s32 arg0);
char* Text_GetMessageString_Bank2C_Buffered(char* arg0, s32 arg1, s32 arg2);
char* Text_GetMessageString_Bank1A(s32 arg0);
char* Text_GetMessageString_Bank1A_Buffered(char* arg0, s32 arg1, u32 arg2);

void MenuPanel_DrawYesNo(MenuPanelInfo* arg0, s16 arg1);
void func_834024C4(MenuPanelInfo* arg0);
void func_834026A4(MenuPanelInfo* arg0);
void func_83402834(MenuPanelInfo* arg0);
void SnapSelect_SetupDisplay(void);
void SnapSelect_UpdateUIState(UNUSED s32 arg0);
void func_83402A38(void);
void func_83402BF4(void);
void func_83402C34(void);
s32 func_83402C6C(void);
s32 func_83402CE4(s16 arg0, Controller* arg1);
s32 func_83402D74(s16 arg0);
s16 SnapSelect_GetResultCode(s16 arg0);

#endif // _FRAGMENT43_H_
