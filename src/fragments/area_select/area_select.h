#ifndef _FRAGMENT37_H_
#define _FRAGMENT37_H_

#include "global.h"

s32 AreaSelect_CheckCartRemoved(s32 arg0);
void AreaSelect_DrawCrossfadeBackground(u8* arg0, u8* arg1, u8 arg2);
Vtx* AreaSelect_BuildExitFadeVertices(void);
void AreaSelect_DrawExitFade(void);
void AreaSelect_AdvanceMagnemiteTrail(void);
void AreaSelect_InitMagnemiteTrail(s32 arg0);
Vtx* AreaSelect_BuildMagnemiteQuadVerts(s16 arg0, s16 arg1, s16 arg2, Color_RGBA8 arg3);
void AreaSelect_DrawMagnemiteQuad(s16 arg0, s16 arg1, s16 arg2, u8* arg3, Color_RGBA8 arg4);
void AreaSelect_DrawMagnemiteTrail(u8* arg0);
void AreaSelect_DrawAndAdvanceMagnemites(void);
void AreaSelect_DrawNameBanner(s16 arg0, s16 arg1, s16 arg2, s16 arg3);
void AreaSelect_Update(void);
void AreaSelect_DrawNameBannerCrossfade(s16 arg0, s16 arg1, s16 arg2);
void AreaSelect_DrawMewtwoMarker(s16 arg0, s16 arg1);
void AreaSelect_DrawGlowCircle(s16 arg0, s16 arg1, s16 arg2);
void AreaSelect_DrawInfoPanel(s16 arg0, s16 arg1, s16 arg2, s16 arg3, u8 arg4, u8 arg5, u8 arg6, u8 arg7);
void AreaSelect_DrawAreaInfoBox(s32 arg0);
void AreaSelect_PollInput(void);
s32 AreaSelect_HandleInput(void);
s16 AreaSelect_UpdateCursorMove(void);
s32 AreaSelect_ShrinkMagnemites(void);
s32 AreaSelect_UpdateExitFade(void);
s32 AreaSelect_UpdateMewtwoExit(void);
s32 AreaSelect_UpdateCancelFade(void);
void AreaSelect_SetupOrthoProjection(void);
void AreaSelect_Draw(s16 arg0);
s32 AreaSelect_RevealMewtwo(void);
void AreaSelect_Intro(void);
void AreaSelect_Loop(void);
void AreaSelect_LoadBackgroundArt(void);
s32 AreaSelect_Main(UNUSED s32 arg0, UNUSED s32 arg1);

#endif // _FRAGMENT37_H_
