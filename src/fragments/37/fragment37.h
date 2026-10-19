#ifndef _FRAGMENT37_H_
#define _FRAGMENT37_H_

#include "global.h"

s32 GetControllerInputMask(s32 arg0);
void DrawFullScreenTextureBlend(u8* arg0, u8* arg1, u8 arg2);
Vtx* CreateTileVertices(void);
void DrawTileOverlay(void);
void UpdateParticleTrailPositions(void);
void InitParticleTrail(s32 arg0);
Vtx* CreateColoredQuad(s16 arg0, s16 arg1, s16 arg2, Color_RGBA8 arg3);
void DrawTexturedQuad(s16 arg0, s16 arg1, s16 arg2, u8* arg3, Color_RGBA8 arg4);
void DrawParticleSprites(u8* arg0);
void DrawParticleTrail(void);
void DrawScrollingBackground(s16 arg0, s16 arg1, s16 arg2, s16 arg3);
void AreaSelect_Update(void);
void UpdateBackgroundFade(s16 arg0, s16 arg1, s16 arg2);
void DrawAnimatedIcon(s16 arg0, s16 arg1);
void AreaSelect_DrawGlowCircle(s16 arg0, s16 arg1, s16 arg2);
void DrawBeveledPanel(s16 arg0, s16 arg1, s16 arg2, s16 arg3, u8 arg4, u8 arg5, u8 arg6, u8 arg7);
void DrawAreaLabel(s32 arg0);
void AreaSelect_InitInput(void);
s32 AreaSelect_HandleInput(void);
s16 AreaSelect_AnimateTransition(void);
s32 AreaSelect_AnimateParticleOut(void);
s32 AreaSelect_FadeInOverlay(void);
s32 AreaSelect_FadeOutSequence(void);
s32 AreaSelect_HandleFadeEnd(void);
void AreaSelect_SetupProjection(void);
void AreaSelect_Render(s16 arg0);
s32 AreaSelect_TransitionToGame(void);
void AreaSelect_StartAnimation(void);
void AreaSelect_MainLoop(void);
void AreaSelect_LoadAssets(void);
s32 AreaSelect_Main(UNUSED s32 arg0, UNUSED s32 arg1);

#endif // _FRAGMENT37_H_
