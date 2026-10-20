#ifndef _FRAGMENT50_H_
#define _FRAGMENT50_H_

#include "global.h"

extern char** D_8267E760;

void HallOfFame_CheckAllCaught(void);
s32 HallOfFame_StringsEqual(s8* arg0, s8* arg1);
s32 HallOfFame_IsCurrentSpeciesOwnedByPlayer(void);
Gfx* HallOfFame_DrawFrameBorder(Gfx* arg0);
s32 HallOfFame_SpeciesObtained(s32 arg0);
s32 HallOfFame_UpdateLeftPillarGlow(s32 arg0, PillarGlowParams* arg1);
s32 HallOfFame_UpdateRightPillarGlow(s32 arg0, PillarGlowParams* arg1);
void HallOfFame_NoopStub1(void);
void HallOfFame_NoopStub2(void);
void HallOfFame_InitCamera(void);
void HallOfFame_NoopStub3(void);
void HallOfFame_PollInput(void);
void HallOfFame_DrawSpeciesIcon(s32 arg0, s32 arg1, f32 arg2, s32 arg3);
void HallOfFame_DrawSpeciesGrid(void);
void HallOfFame_DrawOverlay(void);
void HallOfFame_DrawFrame(void);
void HallOfFame_InitCarouselModel(s16 arg0);
void HallOfFame_SpawnCarouselEntry(s16 arg0);
void HallOfFame_NoopStub6(void);
void HallOfFame_ClearCarouselSlot(s16 arg0);
void HallOfFame_RequestCarouselIconLoad(s16 arg0);
void HallOfFame_LoadCurrentCarouselIcon(s16 arg0);
void HallOfFame_ScrollCarousel(f32 arg0);
void HallOfFame_SetBackgroundPositionX(f32 arg0);
void HallOfFame_NoopStub7(void);
void HallOfFame_UpdateCarouselModelRotation(void);
void HallOfFame_ShowSpeciesInfo(void);
void HallOfFame_ShowSpeciesGrid(void);
void HallOfFame_HideSpeciesGrid(void);
void HallOfFame_HideOverlays(void);
void HallOfFame_ResetPillarGlow(s32 arg0);
s32 HallOfFame_HandleInput(s16* arg0);
s32 HallOfFame_HandleGalleryInput(void);
s32 HallOfFame_ScrollRight(void);
s32 HallOfFame_ScrollLeft(void);
s32 HallOfFame_PageRight(void);
s32 HallOfFame_PageLeft(void);
s32 HallOfFame_WaitFramebuffer(void);
void HallOfFame_RunGallery(void);
void HallOfFame_SpawnPokeIcon(s32 arg0, f32 arg1);
void HallOfFame_InitGallery(void);
s32 HallOfFame_Main(s32 arg0, s32 arg1);

#endif // _FRAGMENT50_H_
