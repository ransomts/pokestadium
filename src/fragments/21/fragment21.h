#ifndef _FRAGMENT21_H_
#define _FRAGMENT21_H_

#include "global.h"
#include "src/fragments/3/fragment3.h"

void MiniGame_PlaySoundEffect(s16 arg0, s16 arg1);
void MiniGame_PlaySoundIfNotMuted(s16 arg0, s16 arg1);
void initSandshrew(MiniActor* sandshrew, s32 player);
void initSandshrews(void);
void miniSandshewReangle(MiniActor* sandshrew);
void miniSandshewReangleAll(void);
void miniSandshewChangeAnim(MiniActor* actor, s32 animID);
void sandshrewDecreaseVel(MiniActor* arg0, f32 arg1);
void sandshrewChangeState(MiniActor* sandshrew, s32 arg1);
void sandshrewHumanControls(MiniActor* sandshrew);
void sandshrewCompControls(MiniActor* arg0);
void MiniSandshrew_StateMachine(MiniActor* sandshrew);
void MiniGame_UpdateSandshrewPhysics(void);
void initSandshrewHole(MiniActor* a0, s32 arg1);
void initSandshrewHoles(void);
void SandshrewGame_UpdateHole(MiniActor* sandshrewHole, MiniActor* sandshrewPlayer);
void MiniGame_UpdateSandshrewHoles(void);
void initSandshrewWaterGeiser(MiniActor* arg0, s32 arg1);
void initSandshrewGeisers(void);
void SandshrewGame_UpdateGeiser(MiniActor* geiser);
void MiniGame_UpdateSandshrewGeisers(void);
void SandshrewGame_InitCamera(void);
void SandshrewGame_UpdateWinCamera(void);
void MiniGame_UpdateSandshrewHUD(void);
void sandshrewMinigameInitObjects(void);
s32 MiniSandshrewGame_DetermineWinner(void);
void SandshrewGame_ResetDigSpeeds(void);
s32 SandshrewGame_UpdateStartCountdown(void);
void MiniGame_UpdateSandshrewAI(void);
void MiniGame_UpdateSandshrewScore(void);
void SandshrewGame_DrawTutorialText(void);
void SandshrewGame_DrawTutorialScreen(void);
void fixSandshrewMinigameHUD(void);
void SandshrewGame_DrawTutorial(void);
void SandshrewGame_DrawPlayerHUBs(s32 arg0);
void MiniGame_WaitForFrame(s32 arg0);
void sandshrewMinigameInit(void);
void MiniGame_ShowTutorial(void);
void MiniGame_FadeOutAndWaitAudio(void);
void MiniGame_InitSandshrewObjects(void);
s32 sandshrewMinigameLoad(s32 arg0, UNUSED s32 arg1);

#endif // _FRAGMENT21_H_
