#ifndef _FRAGMENT22_H_
#define _FRAGMENT22_H_

#include "global.h"
#include "src/fragments/26/fragment26.h"

typedef struct unk_func_8800071C {
    /* 0x00 */ unk_func_88001300_000 unk_00;
    /* 0x2C */ u8* unk_2C;
    /* 0x30 */ u8* unk_30;
    /* 0x34 */ Color_RGBA8 unk_34;
    /* 0x38 */ Color_RGBA8 unk_38;
} unk_func_8800071C; // size = 0x3C

typedef struct unk_func_88000830 {
    /* 0x00 */ unk_func_88001300_000 unk_00;
    /* 0x2C */ s32 unk_2C;
    /* 0x30 */ u8** unk_30;
    /* 0x34 */ s32 unk_34;
} unk_func_88000830; // size = 0x38

typedef struct unk_func_88000C18 {
    /* 0x00 */ unk_func_88001300_000 unk_00;
    /* 0x2C */ Color_RGBA8 unk_2C;
    /* 0x30 */ s32 unk_30;
} unk_func_88000C18; // size = 0x34

typedef struct unk_func_88000CC8 {
    /* 0x00 */ unk_func_88001300_000 unk_00;
    /* 0x2C */ u8* unk_2C;
    /* 0x30 */ u8* unk_30[2];
    /* 0x38 */ u8* unk_38[3];
    /* 0x44 */ s32 unk_44;
    /* 0x48 */ s32 unk_48;
    /* 0x4C */ s32 unk_4C;
    /* 0x50 */ unk_func_88001300_034* unk_50;
} unk_func_88000CC8; // size = 0x54

void Lab_InitTiledBackgroundWidget(unk_func_88001300_000* arg0, s32 arg1, s32 arg2);
s32 Lab_DrawTiledBackgroundWidget(unk_func_88001300_000* arg0, s32 arg1, s32 arg2);
void Lab_InitDualLayerIconWidget(unk_func_8800071C* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, u8* arg5, u8* arg6, Color_RGBA8 arg7, Color_RGBA8 arg8);
s32 Lab_DrawDualLayerIconWidget(unk_func_88001300_000* arg0, s32 arg1, s32 arg2);
void Lab_InitLoopAnimWidget(unk_func_88000830* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, u8** arg6);
s32 Lab_UpdateLoopAnimWidget(unk_func_88001300_000* arg0);
s32 Lab_DrawLoopAnimWidget(unk_func_88000830* arg0, s32 arg1, s32 arg2);
void Lab_InitFrameTimerWidget(unk_func_88000C18* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, Color_RGBA8 arg5);
void Lab_UpdateFrameTimerWidget(unk_func_88001300_000* arg0);
void Lab_SetFrameTimerState(unk_func_88001300* arg0, s32 arg1);
void Lab_InitAnimatedIconWidget(unk_func_88000CC8* arg0, s32 arg1, s32 arg2, unk_func_88500020* arg3, u8* arg4, u8* arg5, u8* arg6, u8* arg7, u8* arg8, unk_func_88001300_034* arg9);
void Lab_UpdateAnimatedIconWidget(unk_func_88001300_000* arg0);
s32 Lab_DrawAnimatedIconWidget(unk_func_88001300_000* arg0, s32 arg1, s32 arg2);
void Lab_ShowMenuItemDescription(unk_func_88001300* arg0);
void Lab_SetSelectedMenuItem(unk_func_88001300* arg0, s32 arg1);
s32 Lab_PollMenuInput(unk_func_88001300* arg0, Controller* controller);
s32 Lab_CountConnectedCarts(void);
s32 Lab_HandleMainMenuInput(unk_func_88001300* arg0);
void Lab_MainMenuThread(unk_func_88001300* arg0);
void Lab_DrawFrame(unk_func_88001300* arg0);
s32 Lab_RunFrameLoop(unk_func_88001300* arg0);
s32 Lab_Main(s32 arg0, UNUSED s32 arg1);

#endif // _FRAGMENT22_H_
