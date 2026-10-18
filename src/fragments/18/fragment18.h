#ifndef _FRAGMENT18_H_
#define _FRAGMENT18_H_

#include "global.h"
#include "src/fragments/3/fragment3.h"

s32 Ekans_GetLaunchForceLevel(MiniActor* arg0);
void miniDiglettGoldCheck(s16 arg0, s32* arg1, s32* arg2);
void MiniGame_PlaySoundEvent(s16 arg0, s16 arg1);
void MiniGame_QueueSoundEvent(s16 arg0, s16 arg1);
void Ekans_ResetPosition(MiniActor* arg0);
void initEkans(MiniActor* ekans, s16 player);
void initAllEkans(void);
f32 Ekans_GetMaxStickMagnitude(MiniActor* arg0);
s16 Ekans_ClampYRotation(MiniActor* arg0, s16 arg1);
void miniEkansHumanControls(MiniActor* ekans);
void MiniEkans_CompSetState1All(void);
s32 MiniEkans_CompShouldSwitchTarget(MiniActor* arg0);
s16 MiniEkans_CompPickRandomActiveDiglett(void);
s16 MiniEkans_CompPickGoldOrActiveDiglett(MiniActor* arg0);
s16 MiniEkans_CompPickUniqueActiveDiglett(MiniActor* arg0);
s32 MiniEkans_CompPickTarget(MiniActor* arg0);
void MiniEkans_CompAimAtDiglett(MiniActor* compEkans);
void miniEkansCompGetForce(MiniActor* compEkans);
s16 MiniEkans_CompHoldDelay(void);
s16 MiniEkans_CompRepeatDelay(void);
void miniEkansCompControls(MiniActor* compEkans);
void MiniEkans_ApplyLaunchPhysics(MiniActor* ekans);
void func_86C01748(void);
void ekansFixDirToDiglett(MiniActor* arg0, s32 arg1, s32 arg2, f32 arg3, f32 arg4, f32 arg5);
void checkCollitionWithDigletts(MiniActor* ekans, s32 nPlayer);
void MiniEkans_ResolveHoopConflicts(void);
void MiniEkansHandleDiglettCollision(MiniActor* ekans, s32 nPlayer);
void miniGetCloser2Diglett(MiniActor* ekans, s32 nPlayer);
void MiniEkansApplyStickMovement(MiniActor* ekans);
void miniEkansAnycontrols(MiniActor* ekans);
void miniEkansPlayerStateMachine(MiniActor* ekans, s32 nPlayer);
void func_86C0250C(void);
void miniEkansPlayersUpdate(void);
void initDiglett(MiniActor* diglett, s32 nDiglett);
void initDiglettHole(MiniActor* hole, s32 arg1);
void ActiveDigletts_Reset(void);
void func_86C027A4(void);
void func_86C027AC(void);
void func_86C027B4(void);
void ActiveDigletts_SetInactive(void);
void initDigletts(void);
s16 miniEkansChooseRandDiglett(s16 arg0);
void MiniDiglettMaybeSetGold(MiniActor* diglett);
void miniEkansRecolorDiglet(MiniActor* diglett, s32 nActiveDiglett);
void miniDiglettStateMachine(void);
void MiniDiglettsUpdateAll(void);
void ekansMinigameInitObjects(void);
s32 MiniEkansAllIdleCheck(void);
void MiniEkansAwardWinner(void);
s32 MiniEkansHandleResultSound(void);
s32 MiniEkansCountdownTick(void);
void miniEkansMinigameStateMachine(void);
void func_86C034F8(void);
void miniEkansInitCam(void);
void MiniEkansDebugAndCameraUpdate(void);
void MiniEkansDrawTutoTextPanel(void);
void MiniEkansTutoScreenUpdate(void);
void miniEkansDrawCountdown(void);
void miniEkansDrawHub(void);
void MiniEkansTutoScreenMain(void);
void MiniEkansTutoScreenOrResult(s32 arg0);
void MiniEkansDrawShadows(void);
void MiniEkansMainDisplayList(s32 arg0);
void initEkansMinigameAssets(void);
void miniEkansTutoScreenControls(void);
void ekansMinigameUpdate(void);
void MiniEkansInitSceneGraph(void);
s32 ekansMinigameLoad(s32 arg0, UNUSED s32 arg1);

#endif // _FRAGMENT18_H_
