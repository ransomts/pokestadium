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
extern unk_D_83403C60 gGalleryEntries[36];
extern unk_D_83403C60 gGalleryCamEntries[21];
extern unk_D_83403C60* gCurrentCamEntry;
extern unk_D_83403C60* gCurrentCamEntryPage;
extern unk_D_83407AC8 D_83407AC8;
extern s32 gGallerySpecialUnlocked;
extern s32 gGallerySpecialViewed;
extern s32 gGalleryAudioStateFlag;
extern unk_D_83407B00 gGallerySelection;
extern unk_D_83407B00 D_83407B00;
extern unk_D_83407B00 gGallerySubSelection;
extern unk_D_83407B00 gGalleryTertiarySelection;
extern unk_D_83407B18 gGalleryFinalSelection;
extern unk_D_83407B00 gGalleryMainSelection;
extern unk_D_83407B38 gGalleryCamList;

extern s32 D_83402E20;
extern s32 D_83402E24;
extern s32 D_83402E28;

void Gallery_Init(void);
s32 Gallery_IsUnlocked(unk_D_83406EB0* arg0);
s32 Gallery_IsViewed(unk_D_83406EB0* arg0);
s32 Gallery_CompareEntries(unk_D_83403C60* arg0, unk_D_83403C60* arg1, s32 arg2);
s32 Gallery_CheckForChanges(void);
s32 Gallery_SaveChanges(s32 arg0, s32 arg1);
void Gallery_Terminate(void);
void Gallery_Reset(void);
void Gallery_ClearEntry(unk_D_83403C60* arg0);
void Gallery_SwapEntries(unk_D_83403C60* arg0, unk_D_83403C60* arg1);
s32 Gallery_IsEntryEqual(unk_D_83403C60* arg0, unk_D_83403C60* arg1);
void Gallery_SetCurrentEntry(unk_D_83403C60* arg0);
unk_D_83403C60* Gallery_GetCurrentEntry(s32 arg0);
void GallerySelection_Init(unk_D_83407B00* arg0);
s32 Text_CountLines(s8* arg0);
s32 CountDisplayableMonIndices(unk_D_83403C60* arg0, s32 arg1, s32 arg2);
s32 FindNthDisplayableMonIndex(unk_D_83403C60* arg0, s32 arg1, s32 arg2, s32 arg3);
s32 FindFirstUndisplayedMonIndex(unk_D_83403C60* arg0, s32 arg1);
void Gallery_DrawGradientPanel(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void Gallery_DrawBorderedRect(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u8 arg4, u8 arg5, u8 arg6, u8 arg7);
void DrawPanelWithTextures(s32 arg0, s32 arg1, s32 arg2, Color_RGBA8* arg3, Color_RGBA8* arg4);
void DrawVerticalTextureStrip(u16* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);
void func_834016C8(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void DrawRectBorder(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void Gallery_DrawShadow(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void Gallery_DrawTextureList(u16* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6);
void Gallery_DrawAnimatedCorners(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void Gallery_DrawCursor(s32 arg0, s32 arg1, s32 arg2);
void CamList_Init(unk_D_83407B38* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, AssetManager* arg5,
    BinArchive* arg6, unk_D_83403C60* arg7, s32 arg8, s32 arg9);
void CamList_Update(unk_D_83407B38* arg0);
void Gallery_ClearActiveCamera(void);
s32 Gallery_CountDisplayableInPage(unk_D_83407B38* arg0, s32 arg1);
void Selection_Reset(unk_D_83407B00* arg0);
void Gallery_SyncSelectionToCam(unk_D_83407B38* arg0, unk_D_83407B00* arg1);
void Gallery_SyncCamToSelection(unk_D_83407B38* arg0, unk_D_83407B00* arg1);
void Gallery_GetPageAndIndex(unk_D_83407B38* arg0, s32* arg1, s32* arg2, s32 arg3);
s32 Gallery_GetGlobalIndex(unk_D_83407B38* arg0, s32 arg1, s32 arg2);
void Gallery_UpdateCameraAssets(unk_D_83407B38* arg0, AssetManager* arg1, BinArchive* arg2);

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
