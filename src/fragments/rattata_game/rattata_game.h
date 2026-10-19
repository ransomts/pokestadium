#ifndef _FRAGMENT8_H_
#define _FRAGMENT8_H_

#include "global.h"

typedef struct RaceObstacle {
    /* 0x000 */ s16 unk_000;
    /* 0x002 */ s16 unk_002;
    /* 0x004 */ Fragment2_1GraphNode unk_004;
    /* 0x16C */ s32 unk_16C;
    /* 0x170 */ s16 unk_170;
    /* 0x172 */ s8 unk_172[6];
    /* 0x178 */ s16 unk_178;
    /* 0x17A */ u16 unk_17A;
} RaceObstacle; // size = 0x17C

typedef struct RacePlayerState {
    /* 0x000 */ s16 unk_000;
    /* 0x002 */ s16 unk_002;
    /* 0x004 */ char pad4[4];
    /* 0x008 */ Fragment2_1GraphNode unk_008;
    /* 0x170 */ u16 unk_170;
    /* 0x172 */ char pad172[2];
    /* 0x174 */ f32 unk_174;
    /* 0x178 */ f32 unk_178;
    /* 0x17C */ f32 unk_17C;
    /* 0x180 */ f32 unk_180;
    /* 0x184 */ f32 unk_184;
    /* 0x188 */ f32 unk_188;
    /* 0x18C */ f32 unk_18C;
    /* 0x190 */ f32 unk_190;
    /* 0x194 */ f32 unk_194;
    /* 0x198 */ f32 finishTime;
    /* 0x19C */ s16 animState;
    /* 0x19E */ s16 finishState;
    /* 0x1A0 */ s16 rankPending;
    /* 0x1A2 */ s16 unk_1A2;
    /* 0x1A4 */ f32 hurdlePos;
    /* 0x1A8 */ f32 unk_1A8;
    /* 0x1AC */ s16 hurdleHitCount;
    /* 0x1AE */ s16 unk_1AE;
    /* 0x1B0 */ s16 unk_1B0;
    /* 0x1B2 */ s16 finishRank;
    /* 0x1B4 */ s16 unk_1B4;
    /* 0x1B6 */ char pad1B6[0x12];
    /* 0x1C8 */ u16 unk_1C8;
    /* 0x1CA */ char pad1CA[6];
} RacePlayerState; // size = 0x1D0

extern u32 gRacePlayerScreenY[4];

void RattataGame_InitAIDifficulty(RacePlayerState* arg0);
void RattataGame_DrawRankBanners(void);
void Race_Stub(void);
void RattataGame_UpdateAIInput(void);
void RattataGame_PollInput(void);
void RattataGame_InitCamera(void);
void RattataGame_UpdateCamera(void);
void RattataGame_Stub(void);
void RattataGame_DrawTutorialScreen(s32 arg0);
void RattataGame_DrawFrame(s32 arg0);
s32 RattataGame_WaitForStart(void);
void RattataGame_UpdateStartCountdown(void);
void RattataGame_SyncRacerZPosition(RacePlayerState* arg0);
void RattataGame_ResetRacerState(RacePlayerState* arg0);
s32 RattataGame_CheckHurdleCollision(RacePlayerState* arg0, RaceObstacle* arg1);
void RattataGame_UpdateRunAnimSpeed(RacePlayerState* arg0);
void RattataGame_SetRacerAnimState(RacePlayerState* arg0, s32 arg1);
void RattataGame_UpdateHurdleMarkers(RacePlayerState* arg0);
s16 RattataGame_UpdateRacers(void);
void RattataGame_AdvanceFinishLineApproach(void);
void RattataGame_MainLoop(void);
void RattataGame_UpdatePostRaceIdleAnim(void);
void RattataGame_PlayResultAnimation(void);
void RattataGame_WaitForAudioToFinish(void);
void RattataGame_FadeOutAndTransition(void);
void RattataGame_PlayOutroSequence(s32 arg0);
void RattataGame_WaitForContinue(void);
void RattataGame_LoadAssets(void);
void RattataGame_InitPlayerSlots(void);
void RattataGame_Main(s32 arg0, UNUSED s32 arg1);

#endif // _FRAGMENT8_H_
