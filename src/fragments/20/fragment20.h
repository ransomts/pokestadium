#ifndef _FRAGMENT20_H_
#define _FRAGMENT20_H_

#include "global.h"
#include "src/fragments/3/fragment3.h"

void MiniAudioEventHandler(s16 arg0, s16 arg1);
void PlayAudioIfEnabled(s16 arg0, s16 arg1);
void miniInitMetapodPlayer(MiniActor* metapod, s32 arg1);
void miniInitMetapodPlayers(void);
void MetapodTakeDamage(MiniActor* metapod);
void miniMetapodHumanControls(MiniActor* metapod);
void MiniActor_ResetCompState(MiniActor* metapod);
s32 SelectCompMetapodStrategy(MiniActor* arg0, s32 arg1);
void CompMetapodSetHardenParams(MiniActor* metapod, s32 arg1);
void CompMetapodSetRandomParams(MiniActor* arg0, s32 arg1);
void CompMetapodSetImmediateParams(MiniActor* metapod, s32 arg1);
void CompMetapodCheckRockCollision(MiniActor* metapod, s32 player);
void miniMetapodCompControls(MiniActor* compMetapod, s32 nPlayer);
void miniUpdateMetapods(void);
s32 metapodRockCollisionCheck_void(void);
s32 HandleMetapodRockCollision(s32 arg0);
void miniRockChecks(MiniActor* arg0, s32 nPlayer);
void miniMatapodChecks(MiniActor* metapod, s32 nPlayer);
void miniMatapodMinigameChecks(void);
void MiniActor_SyncAnimTransform(void);
void MiniActor_SyncAllAnimTransforms(void);
void miniInitRock(MiniActor* rock, s32 arg1);
void miniInitRocks(void);
void InitMetapodRockWave(void);
void StartMetapodRockThrow(MiniActor* rock);
void DeactivateMetapodRock(MiniActor* rock);
void miniRockStateMachine(MiniActor* rock);
void miniRockUpdatePosition(MiniActor* rock);
void miniUpdateRockTransform(MiniActor* rock);
void miniUpdateRocks(void);
void MiniActor_UpdateTransform(MiniActor* arg0);
void miniUpdateRocksPositions(void);
void MetapodGame_InitCamera(void);
void miniMetapodCameraControls(void);
void initMetapodMinigameAssets(void);
void MetapodGame_UpdateRockWaveScheduler(void);
s32 MetapodGame_CheckWinCondition(void);
s32 MetapodGame_PlayWinnerAnimations(void);
void func_86E01EB0(void);
s32 MetapodGame_UpdateStartCountdown(void);
s32 MetapodGame_AllRocksCleared(void);
void miniMetapodMinigameStateMachine(void);
void MetapodGame_UpdateParticleFx(void);
void miniDrawMetapodHealth(void);
void miniDrawMetapodHeads(void);
void MetapodGame_DrawTutorialText(void);
void MetapodGame_DrawTutorialScreen(void);
void MetapodGame_DrawTutorial(void);
void miniMetapodDrawPlayerHUBs(s32 arg0);
void MetapodGame_DrawFrame(s32 arg0);
void metapodMinigameInit(void);
void func_86E0296C(void);
void miniMetapodTutoScreenControls(void);
void MetapodGame_LockPlayerInputOnPress(void);
void MetapodGame_MainLoop(void);
void MetapodGame_ShowResultText(void);
void MetapodGame_LoadAssets(void);
s32 metapodMinigameLoad(s32 arg0, s32 arg1);

#endif // _FRAGMENT20_H_
