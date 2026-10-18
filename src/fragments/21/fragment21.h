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
void func_86F00F68(MiniActor* sandshrewHole, MiniActor* sandshrewPlayer);
void MiniGame_UpdateSandshrewHoles(void);
void initSandshrewWaterGeiser(MiniActor* arg0, s32 arg1);
void initSandshrewGeisers(void);
void func_86F011E8(MiniActor* geiser);
void MiniGame_UpdateSandshrewGeisers(void);
void func_86F0132C(void);
void func_86F013B8(void);
void MiniGame_UpdateSandshrewHUD(void);
void sandshrewMinigameInitObjects(void);
s32 MiniSandshrewGame_DetermineWinner(void);
void func_86F0164C(void);
s32 func_86F016D8(void);
void MiniGame_UpdateSandshrewAI(void);
void MiniGame_UpdateSandshrewScore(void);
void func_86F01904(void);
void func_86F01C40(void);
void fixSandshrewMinigameHUD(void);
void func_86F01EB4(void);
void func_86F01EF4(s32 arg0);
void MiniGame_WaitForFrame(s32 arg0);
void sandshrewMinigameInit(void);
void MiniGame_ShowTutorial(void);
void MiniGame_FadeOutAndWaitAudio(void);
void MiniGame_InitSandshrewObjects(void);
s32 sandshrewMinigameLoad(s32 arg0, UNUSED s32 arg1);

#endif // _FRAGMENT21_H_
