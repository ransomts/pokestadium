#include "3D140.h"
#include "lib/ultralib/include/PR/leo.h"
#include "src/audio_commands.h"
#include "src/libnumus/player.h"
#include "src/3D140.h"
#include "src/gb_audio.h"
#include "src/libnaudio/n_libaudio_sc.h"
#include "src/libnaudio/n_libaudio_sn_sc.h"
#include "src/audio_stream.h"
#include "src/gb_audio_render.h"
#include "src/audio_loop_point.h"

typedef union {
    struct {
        s16 type;
    } gen;
    struct {
        s16 type;
        struct AudioInfo* info;
    } done;
} AudioMsg; // size = 0x8

typedef struct AudioInfo {
    /* 0x00 */ s16* data;
    /* 0x04 */ s16 frameSamples;
    /* 0x08 */ AudioMsg msg;
} AudioInfo; // size = 0x10

#define NUM_ACMD_LISTS 2
#define NUM_OUTPUT_BUFFERS 2
#define MAX_MESGS 3
#define NUM_DMA_BUFFERS 48
#define SAMPLES 184

typedef struct AMAudioMgr {
    /* 0x000 */ Acmd* ACMDList[NUM_ACMD_LISTS];
    /* 0x008 */ AudioInfo* audioInfo[NUM_OUTPUT_BUFFERS];
    /* 0x010 */ char unk10[0x228];
    ///* 0x010 */ OSThread thread;
    ///* 0x1C0 */ OSMesgQueue audioFrameMsgQ;
    ///* 0x1D8 */ OSMesg audioFrameMsgBuf[MAX_MESGS];
    ///* 0x1E0 */ OSMesgQueue audioReplyMsgQ;
    ///* 0x1F8 */ OSMesg audioReplyMsgBuf[MAX_MESGS];
    /* 0x238 */ ALGlobals g;
} AMAudioMgr; // size = 0x288

typedef struct AMDMABuffer {
    /* 0x00 */ ALLink node;
    /* 0x08 */ u32 startAddr;
    /* 0x0C */ u32 lastFrame;
    /* 0x10 */ char* ptr;
} AMDMABuffer; // size = 0x14

typedef struct AMDMAState {
    /* 0x00 */ u8 initialized;
    /* 0x04 */ AMDMABuffer* firstUsed;
    /* 0x08 */ AMDMABuffer* firstFree;
} AMDMAState; // size = 0xC

typedef struct HPHistoryEntry {
    /* 0x00 */ u16 posX[16];
    /* 0x20 */ s32 unk_20;
    /* 0x24 */ s32 unk_24;
    /* 0x28 */ u16 unk_28[16];
    /* 0x48 */ s32 unk_48;
    /* 0x4C */ s32 unk_4C;
    /* 0x50 */ u16 unk_50[16];
    /* 0x70 */ s32 unk_70;
    /* 0x74 */ s32 unk_74;
    /* 0x78 */ u32 unk_78;
    /* 0x7C */ u32 unk_7C;
    /* 0x80 */ s32 unk_80;
} HPHistoryEntry; // size = 0x84

typedef struct AudioCommandMapEntry {
    /* 0x00 */ u8 posX;
    /* 0x01 */ u8 TrainerSlotSaveData_GamePort;
} AudioCommandMapEntry;

// .data
extern u8 gMusicEnabled[];// = { 0, 0, 0, 0 };
extern f32 gMusicVolume;// = 0.8000000119f;
extern u8 gAudioProcessChannelsFlag[];// = { 0, 0, 0, 0 };
extern u8 gMusicFadeState[];// = { 0, 0, 0, 0 };
extern u16 gMusicFadeTargetTrack;
extern u32 gMusicFadeTimer;
extern u8 gAudioPausedFlag;
extern s32 gAudioUnitReady;
extern u32 audFrameCt;
extern u32 nextDMA;
extern u32 curAcmdList;
extern AudioInfo* lastInfo;
extern s32 min_only_one;
// global
extern s32 mus_active_fade_handle;
extern f32 mus_fade_start_volume;
extern u8 mus_fade_target_volume;
extern f32 mus_fade_step_rate;
extern f32 gMusicChannel2Volume;
extern f32 gMusicChannel2Step;
extern f32 gMusicChannel1Volume;
extern f32 gMusicChannel1Step;
extern u8 mus_sound_effect_blocked;

extern u16 gAudioCueTable_0x24F[];
extern u16 gAudioCueTable_0x269[];
extern u16 gAudioCueTable_0x281[];
extern u16 gAudioCueTable_0x27E[];
extern u16 gAudioCueTable_0x24D[];
extern u16 gAudioCueTable_0x24C[];
extern u16 gAudioCueTable_0x24B[];
extern u16 gAudioCueTable_0x27C[];
extern u16 gAudioCueTable_0x27A[];
extern u16 gAudioCueTable_0x252[];
extern u16 gAudioCueTable_0x284[];
extern u16 gAudioCueTable_0x259[];
extern u16 gAudioCueTable_0x25A[];
extern u16 gAudioCueTable_0x24E[];
extern u16 gAudioCueTable_0x251[];
extern u16 gAudioCueTable_GenericLow[];
extern u16 gAudioCueTable_GenericMid[];
extern u16 gAudioCueTable_GenericZero[];
extern u16 gAudioCueTable_ItemUse[6];
extern u16 gAudioCueTable_ItemConsume[7];
extern u16 gAudioCueTable_ItemEquip[6];
extern u16 gAudioCueTable_ItemUnequip[6];
extern u16 gAudioCueTable_ItemThrow[6];
extern u16 gAudioCueTable_ItemPickup[5];
extern u16 gAudioCueTable_ItemDrop[6];
extern u16 gAnnouncerCueCriticalHitLowDamage[4];
extern u16 gAnnouncerCueNotVeryEffectiveHeavy[5];
extern u16 gAnnouncerCueLightHitLowHp[3];
extern u16 gAnnouncerCueAttackMissed[4];
extern u16 gAnnouncerCueNoEffect[3];
extern u16 gAnnouncerCueMissNearKnockout[3];
extern u16 gAnnouncerCueNoEffectGhost[3];
extern u16 gAnnouncerCueLeechSeed[3];
extern u16 gAnnouncerCueBadlyPoisoned[3];
extern u16 gAnnouncerCuePoison[3];
extern u16 gAudioCueTable_ItemUseAlt[6];
extern u16 gAnnouncerCueMissRepeated[3];
extern u16 gAnnouncerCueSuperEffectiveEarly[3];
extern u16 gAnnouncerCueMultiHitLowHp[6];
extern u16 gAnnouncerCueOneHitKo[];
extern u16 gAnnouncerCueOneHitKoRepeat[];
extern u16 gAnnouncerCueHeavyDamage[];
extern u16 gAnnouncerCueHeavyDamageFirstTurn[];
extern u16 gAnnouncerCueKnockoutBlow[];
extern u16 gAnnouncerCueLightDamage[];
extern u16 gAnnouncerCueLightDamageFirstTurn[];
extern u16 gAnnouncerCueLightDamageFirstTurnAlt[];
extern u16 gAnnouncerCueRecall[];
extern u16 gAnnouncerCueRecallOutleveled[];
extern u16 gAnnouncerCueRecallLateBattle[];
extern u16 gAnnouncerCueRecallSurvivedBigHit[];
extern u16 gAnnouncerCueFainted[];
extern u16 gAnnouncerCueFaintedFirstTurn[];
extern u16 gAnnouncerCueSwitchIn[];
extern u16 gAnnouncerCueUnderdog[];
extern u16 gAnnouncerCueFrozen[];
extern u16 gAnnouncerCueAsleep[];
extern u16 gAnnouncerCueLowHp[];
extern u16 gAnnouncerCueUnderdogRepeat[];
extern u8 gAnnouncerCueSleep[8];
extern u8 gAnnouncerCueFreeze[10];
extern u8 gAnnouncerCueParalysis[6];
extern u8 gAnnouncerCueFreezeLastPokemon[6];
extern u16 gAnnouncerCueBothLastPokemon[];
extern u16 gAnnouncerCueCantMove[];
extern u16 gAnnouncerCueAttackContinues[3];
extern u16 gAnnouncerCueConfusionSelfHit[3];
extern u16 gAnnouncerCueConfusionSelfHitRepeat[3];
extern u16 gAnnouncerCueStatUp[];
extern u8 gAnnouncerCueStatDown[8];
extern u16 gAnnouncerCueStatDownRepeat[3];
extern u16 gAnnouncerCueSubstituteBroke[3];
extern u16 gAnnouncerCueMoveFailed[3];
extern u16 gAnnouncerCueMoveNoEffect[4];
extern u16 gAnnouncerCueFly[3];
extern u16 gAnnouncerCueDig[3];
extern u16 gAnnouncerCueBattleCommentary[];
extern u8 D_800780B3[]; // needs addressing
extern u8 gAnnouncerMoveDataMoves1To68[];
extern u8 gAnnouncerMoveDataMoves69To100[];
extern u8 gAnnouncerMoveDataMoves101To165[];
extern u8 gAnnouncerTypeEffectivenessTable[];
extern s32 gAudioActiveFlag;
extern u8 gTeamScores[4];
extern u8 gPlayerActiveFlag[2];
extern u8 gPlayerSideActiveIndex[4];
extern u8 gPlayerSideMap[4];
extern u8 gRecentMoveCount[];
extern u8 gAudioQueueNeedsUpdate;
extern u32 gAudioSeqQueue[4];
extern u32 gAudioSeqTimer;
extern s32 gAudioSeqIndex;
extern u8 gAudioSeqActiveFlag;
extern u8 gAudioSeqState;
extern u8 gAudioSeqPlayedFlag;
extern u32 gAudioSeqElapsed;
extern u32 gAudioQueueMode;
extern u8 gAudioCmd9DLatched;
extern u8 gAudioEstimateMinus3Latched;
extern u8 gAudioOneRemovalLatched;
extern u8 gAudioQueueSfxToggle;
extern u8 gAudioLowHPWarningFlag;
extern u8 gAudioClimaxMusicPlayed;
extern u8 gAudioRecentHeavyHitFlag;
extern u8 gAudioQueueSpecialFlag;
extern s16 gAudioSfxParam0;
extern s16 gAudioSfxParam1;
extern s16 gAudioSfxParam2;
extern u8 gAudioSystemEnabled;
extern u8 gAudioEffectId;
extern u32 gCurrentStadiumPhase;
extern s32 gStadiumPhaseSubstate;
extern u8 gAudioStadiumSfxEnabled;
extern u16 MenuSelectionSoundTable[17][9];
extern u16 D_80078446[1][9];
extern u16 D_800784EA[1][9];
extern u32 gCommandQueueCount;
extern AudioCommandMapEntry AudioCommandMap[];
extern u8 AudioEffectTriggerIds[];
extern u8 AudioEffectSecondaryIds[];

u8 gMusicEnabled[4] = { 0, 0, 0, 0 };
f32 gMusicVolume = 0.8f;
u8 gAudioProcessChannelsFlag[4] = { 1, 0, 0, 0 };
u8 gMusicFadeState[4] = { 0, 0, 0, 0 };
u16 gMusicFadeTargetTrack = 0;
u32 gMusicFadeTimer = 0;
u8 gAudioPausedFlag = 0;
s32 gAudioUnitReady = 0;
u32 audFrameCt = 0;
u32 nextDMA = 0;
u32 curAcmdList = 0;
AudioInfo* lastInfo = NULL;
s32 min_only_one = 1;
s32 mus_active_fade_handle = 0;
f32 mus_fade_start_volume = 0.0f;
u8 mus_fade_target_volume = 0;  // tail holds D_80077DCD (linker-defined symbols)
f32 mus_fade_step_rate = 0.0f;
f32 gMusicChannel2Volume = 0.0f;
f32 gMusicChannel2Step = 0.0f;
f32 gMusicChannel1Volume = 0.0f;
f32 gMusicChannel1Step = 0.0f;
u8 mus_sound_effect_blocked = 0;
u32 gAudioDmaBufferCount[2] = { 0, 0 };
u16 gAudioCueTable_0x24F[8] = { 7, 0x24F, 0x250, 0x255, 0x271, 0x273, 0x289, 0x28F };
u16 gAudioCueTable_0x269[8] = { 6, 0x269, 0x26C, 0x26D, 0x26E, 0x287, 0x288, 0 };
u16 gAudioCueTable_0x281[4] = { 3, 0x281, 0x282, 0x283 };
u16 gAudioCueTable_0x27E[4] = { 3, 0x27E, 0x27F, 0x280 };
u16 gAudioCueTable_0x24D[4] = { 3, 0x24D, 0x278, 0x279 };
u16 gAudioCueTable_0x24C[4] = { 3, 0x24C, 0x274, 0x275 };
u16 gAudioCueTable_0x24B[4] = { 3, 0x24B, 0x276, 0x277 };
u16 gAudioCueTable_0x27C[4] = { 2, 0x27C, 0x27D, 0 };
u16 gAudioCueTable_0x27A[4] = { 2, 0x27A, 0x27B, 0 };
u16 gAudioCueTable_0x252[4] = { 3, 0x252, 0x270, 0x272 };
u16 gAudioCueTable_0x284[4] = { 3, 0x284, 0x285, 0x286 };
u16 gAudioCueTable_0x259[4] = { 3, 0x259, 0x28B, 0x28C };
u16 gAudioCueTable_0x25A[4] = { 3, 0x25A, 0x28A, 0x28C };
u16 gAudioCueTable_0x24E[4] = { 3, 0x24E, 0x258, 0x28E };
u16 gAudioCueTable_0x251[4] = { 2, 0x251, 0x28D, 0 };
u16 gAudioCueTable_GenericLow[8] = { 6, 0x24F, 0x250, 0x255, 0x271, 0x289, 0x28F, 0 };
u16 gAudioCueTable_GenericMid[4] = { 3, 0x253, 0x26F, 0x291 };
u16 gAudioCueTable_GenericZero[4] = { 2, 0x252, 0x270, 0 };
u16 gAudioCueTable_ItemUse[6] = { 5, 0x62, 0x67, 0x6E, 0x8D, 0x8E };
u16 gAudioCueTable_ItemConsume[7] = { 6, 0x6D, 0x72, 0x89, 0x8A, 0x8B, 0x8C };
u16 gAudioCueTable_ItemEquip[6] = { 5, 0x6F, 0x70, 0x9F, 0xA0, 0xA1 };
u16 gAudioCueTable_ItemUnequip[6] = { 5, 0x60, 0x65, 0x92, 0x93, 0x94 };
u16 gAudioCueTable_ItemThrow[6] = { 5, 0x61, 0x66, 0x95, 0x96, 0x97 };
u16 gAudioCueTable_ItemPickup[5] = { 4, 0x69, 0x98, 0x99, 0x9A };
u16 gAudioCueTable_ItemDrop[6] = { 5, 0x63, 0x64, 0x8F, 0x90, 0x91 };
u16 gAnnouncerCueCriticalHitLowDamage[4] = { 3, 0x6A, 0x9B, 0x9C };
u16 gAnnouncerCueNotVeryEffectiveHeavy[5] = { 4, 0x6B, 0x6C, 0x9D, 0x9E };
u16 gAnnouncerCueLightHitLowHp[3] = { 2, 0x8A, 0x8B };
u16 gAnnouncerCueAttackMissed[4] = { 3, 0x7C, 0x86, 0xAC };
u16 gAnnouncerCueNoEffect[3] = { 2, 0x7E, 0x7F };
u16 gAnnouncerCueMissNearKnockout[3] = { 2, 0xAE, 0xAF };
u16 gAnnouncerCueNoEffectGhost[3] = { 2, 0x82, 0x83 };
u16 gAnnouncerCueLeechSeed[3] = { 2, 0x72, 0x8A };
u16 gAnnouncerCueBadlyPoisoned[3] = { 2, 0x85, 0x84 };
u16 gAnnouncerCuePoison[3] = { 2, 0x88, 0x71 };
u16 gAudioCueTable_ItemUseAlt[6] = { 5, 0x62, 0x67, 0x6E, 0x8D, 0x8E };
u16 gAnnouncerCueMissRepeated[3] = { 2, 0x80, 0x81 };
u16 gAnnouncerCueSuperEffectiveEarly[3] = { 2, 0xB3, 0xB4 };
u16 gAnnouncerCueMultiHitLowHp[6] = { 5, 0x72, 0x89, 0x8A, 0x8B, 0x8C };
u16 gAnnouncerCueOneHitKo[4] = { 3, 0x1D, 0x1E, 0x1F };
u16 gAnnouncerCueOneHitKoRepeat[4] = { 3, 0x20, 0x21, 0x22 };
u16 gAnnouncerCueHeavyDamage[6] = { 4, 0x19, 0x1A, 0x1B, 0x1C, 0 };
u16 gAnnouncerCueHeavyDamageFirstTurn[4] = { 2, 0x1A, 0x1B, 0 };
u16 gAnnouncerCueKnockoutBlow[4] = { 3, 0x18, 0x1B, 0x1C };
u16 gAnnouncerCueLightDamage[6] = { 4, 0x14, 0x15, 0x16, 0x17, 0 };
u16 gAnnouncerCueLightDamageFirstTurn[4] = { 2, 0x10, 0x11, 0 };
u16 gAnnouncerCueLightDamageFirstTurnAlt[4] = { 2, 0x12, 0x13, 0 };
u16 gAnnouncerCueRecall[6] = { 4, 0xB7, 0xB8, 0xB9, 0xBA, 0 };
u16 gAnnouncerCueRecallOutleveled[4] = { 3, 0xBD, 0xBE, 0xBF };
u16 gAnnouncerCueRecallLateBattle[4] = { 2, 0xC0, 0xC1, 0 };
u16 gAnnouncerCueRecallSurvivedBigHit[4] = { 3, 0xBB, 0xC6, 0xC7 };
u16 gAnnouncerCueFainted[6] = { 4, 0x50, 0x51, 0x52, 0x53, 0 };
u16 gAnnouncerCueFaintedFirstTurn[4] = { 2, 0x56, 0x57, 0 };
u16 gAnnouncerCueSwitchIn[4] = { 2, 0x59, 0x5A, 0 };
u16 gAnnouncerCueUnderdog[4] = { 2, 0xB, 0xC, 0 };
u16 gAnnouncerCueFrozen[4] = { 2, 4, 3, 0 };
u16 gAnnouncerCueAsleep[4] = { 2, 5, 3, 0 };
u16 gAnnouncerCueLowHp[4] = { 2, 8, 0xD, 0 };
u16 gAnnouncerCueUnderdogRepeat[4] = { 2, 0xE, 0xF, 0 };
u8 gAnnouncerCueSleep[8] = { 0, 3, 1, 0x81, 1, 0x9D, 1, 0x9E };
u8 gAnnouncerCueFreeze[10] = { 0, 4, 1, 0x7C, 1, 0x82, 1, 0x9D, 1, 0x9E };
u8 gAnnouncerCueParalysis[6] = { 0, 2, 1, 0x7C, 1, 0x9E };
u8 gAnnouncerCueFreezeLastPokemon[6] = { 0, 2, 1, 0x80, 1, 0x98 };
u16 gAnnouncerCueBothLastPokemon[4] = { 2, 0x180, 0x17C, 0 };
u16 gAnnouncerCueCantMove[4] = { 3, 0x179, 0x19D, 0x19E };
u16 gAnnouncerCueAttackContinues[3] = { 2, 0x177, 0x178 };
u16 gAnnouncerCueConfusionSelfHit[3] = { 2, 0x183, 0x184 };
u16 gAnnouncerCueConfusionSelfHitRepeat[3] = { 2, 0x184, 0x185 };
u16 gAnnouncerCueStatUp[4] = { 3, 0x172, 0x173, 0x174 };
u8 gAnnouncerCueStatDown[8] = { 0, 3, 0, 0x71, 0, 0xA8, 0, 0xA9 };
u16 gAnnouncerCueStatDownRepeat[3] = { 2, 0x73, 0x74 };
u16 gAnnouncerCueSubstituteBroke[3] = { 2, 0x175, 0x176 };
u16 gAnnouncerCueMoveFailed[3] = { 2, 0x7D, 0xAA };
u16 gAnnouncerCueMoveNoEffect[4] = { 3, 0x7D, 0xAA, 0xAB };
u16 gAnnouncerCueFly[3] = { 2, 0x199, 0x19A };
u16 gAnnouncerCueDig[3] = { 2, 0x19B, 0x19C };
u16 gAnnouncerCueBattleCommentary[6] = { 5, 0x5B, 0x5C, 0x5D, 0x5E, 0x5F };
u8 gAnnouncerMoveDataMoves1To68[204] = { 0, 0x28, 0, 0, 0x32, 0, 0x1D, 0xF, 0, 0x1D, 0x12, 0, 0, 0x50, 0, 0x10, 0x28, 0, 4, 0x4B, 0x14, 5, 0x4B, 0x19, 6, 0x4B, 0x17, 0, 0x28, 0, 0, 0x37, 0, 0x26, 1, 0, 0x27, 0x50, 0, 0x32, 0, 0, 0, 0x32, 0, 0, 0x28, 0, 0, 0x23, 2, 0x1C, 0, 0, 0x2B, 0x46, 2, 0x2A, 0xF, 0, 0, 0x50, 0, 0, 0x23, 0x16, 0x25, 0x41, 0, 0x2C, 0x1E, 1, 0, 0x78, 0, 0x2D, 0x46, 1, 0x25, 0x3C, 1, 0x16, 0, 0, 0x25, 0x46, 0, 0, 0x41, 0, 0x1D, 0xF, 0, 0x26, 1, 0, 0, 0x23, 0, 0x24, 0x55, 0, 0x2A, 0xF, 0, 0x30, 0x5A, 0, 0x1B, 0x5A, 0, 0x30, 0x64, 0, 0x13, 0, 0, 2, 0xF, 3, 0x4D, 0x19, 7, 0x1D, 0xE, 7, 0x13, 0, 0, 0x1F, 0x3C, 0, 0x12, 0, 0, 0x1C, 0, 0, 0x20, 0, 0, 0x31, 0, 0, 0x29, 1, 0, 0x56, 0, 0, 0x45, 0x28, 3, 4, 0x28, 0x14, 4, 0x5F, 0x14, 0x2E, 0, 0x19, 0, 0x28, 0x15, 0, 0x78, 0x15, 0, 0x5F, 0x15, 5, 0x5F, 0x19, 0x23, 0x78, 0x19, 0x4C, 0x41, 0x18, 0x46, 0x41, 0x15, 0x44, 0x41, 0x19, 0x50, 0x96, 0, 0, 0x23, 2, 0, 0x50, 2, 0x30, 0x50, 1, 0x25, 0x32, 1, 0, 1, 1 };
u8 gAnnouncerMoveDataMoves69To100[96] = { 0x29, 1, 1, 0, 0x50, 0, 3, 0x14, 0x16, 3, 0x28, 0x16, 0x54, 0, 0x16, 0xD, 0, 0, 0, 0x37, 0x16, 0x27, 0x78, 0x16, 0x42, 0, 3, 0x43, 0, 0x16, 0x20, 0, 0x16, 0x1B, 0x46, 0x16, 0x14, 0, 7, 0x29, 1, 0x1A, 0x2A, 0xF, 0x14, 6, 0x28, 0x17, 6, 0x5F, 0x17, 0x43, 0, 0x17, 6, 0x78, 0x17, 0, 0x32, 5, 0, 0x64, 4, 0x26, 1, 4, 0x27, 0x64, 4, 0x42, 0, 3, 0x4C, 0x32, 0x18, 0x47, 0x5A, 0x18, 0x20, 0, 0x18, 0xA, 0, 0x18, 0x34, 0, 0x18, 0, 0x28, 0, 0x51, 0x14, 0, 0x1C, 0, 0x18 };
u8 gAnnouncerMoveDataMoves101To165[196] = { 0x29, 0, 8, 0x52, 0, 0, 0x3B, 0, 0, 0xF, 0, 0, 0x38, 0, 0, 0xB, 0, 0, 0xF, 0, 0, 0x16, 0, 0, 0x31, 0, 8, 0xB, 0, 0x15, 0xB, 0, 0, 0x33, 0, 0x18, 0x40, 0, 0x18, 0x19, 0, 0x19, 0x41, 0, 0x18, 0x2F, 0, 0, 0x1A, 0, 0, 0x53, 0, 0, 9, 0, 2, 7, 0x82, 0, 0, 0x64, 0, 0x24, 0x14, 8, 0x21, 0x14, 3, 0x21, 0x41, 3, 0x1F, 0x41, 4, 0x22, 0x78, 0x14, 0, 0x50, 0x15, 0x2A, 0x23, 0x15, 0x11, 0x3C, 0, 0x27, 0x64, 0, 0x1D, 0x14, 0, 0x46, 0xA, 0, 0x35, 0, 0x18, 0x16, 0, 0x18, 0x38, 0, 0, 0x2D, 0x55, 1, 0x43, 0, 0, 8, 0x64, 0x18, 0x42, 0, 3, 0x1D, 0xF, 0, 3, 0x14, 7, 0x20, 0, 0, 0x27, 0x8C, 2, 0x39, 0, 0, 0x46, 0x14, 0x15, 0, 0x46, 0, 0x20, 0, 0x16, 0x16, 0, 0, 0x29, 1, 0x18, 0x55, 0, 0, 0x33, 0, 3, 0, 0x5A, 0x15, 7, 0xAA, 0, 0x1D, 0x12, 0, 0x2C, 0x32, 4, 0x38, 0, 0x18, 0, 0x4B, 5, 0x1F, 0x50, 0, 0xA, 0, 0, 0x18, 0, 0, 0, 0x50, 0, 0x28, 1, 0, 0, 0x46, 0, 0x4F, 0, 0, 0x30, 0x32, 0, 0 };
u8 gAnnouncerTypeEffectivenessTable[228] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 1, 0, 0, 2, 2, 0, 3, 3, 0, 0, 0, 0, 0, 3, 2, 0, 2, 0, 3, 2, 2, 2, 0, 0, 0, 3, 0, 0, 0, 3, 0, 2, 0, 0, 3, 2, 2, 0, 0, 0, 1, 3, 0, 0, 0, 0, 2, 0, 2, 3, 0, 2, 0, 0, 2, 3, 2, 0, 2, 3, 0, 2, 0, 2, 2, 0, 3, 2, 0, 0, 3, 3, 0, 0, 3, 0, 3, 3, 0, 0, 0, 0, 3, 0, 2, 0, 2, 2, 2, 3, 1, 0, 0, 0, 0, 0, 3, 0, 0, 2, 2, 0, 0, 3, 2, 2, 0, 0, 3, 0, 3, 2, 0, 0, 3, 0, 1, 0, 2, 3, 0, 0, 0, 0, 0, 2, 3, 0, 3, 0, 0, 0, 0, 3, 2, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 0, 0, 2, 0, 0, 0, 0, 0, 2, 0, 0, 3, 0, 2, 0, 0, 2, 3, 0, 0, 2, 0, 0, 3, 0, 0, 0, 3, 2, 0, 2, 3, 0, 3, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0 };
s32 gAudioActiveFlag = 1;
u8 gTeamScores[4] = { 3, 3, 3, 3 };
u8 gPlayerActiveFlag[2] = { 3, 3 };
u8 gPlayerSideActiveIndex[4] = { 0, 1, 0, 0 };
u8 gPlayerSideMap[4] = { 1, 2, 1, 2 };
u8 gRecentMoveCount[4] = { 0, 0, 0, 0 };
u8 gAudioQueueNeedsUpdate = 0;
u32 gAudioSeqQueue[4] = { 0, 0, 0, 0 };
u32 gAudioSeqTimer = 0;
s32 gAudioSeqIndex = 0;
u8 gAudioSeqActiveFlag = 0;
u8 gAudioSeqState = 0;
u8 gAudioSeqPlayedFlag = 0;
u32 gAudioSeqElapsed = 0;
u32 gAudioQueueMode = 0;
u8 gAudioCmd9DLatched = 0;
u8 gAudioEstimateMinus3Latched = 0;
u8 gAudioOneRemovalLatched = 0;
u8 gAudioQueueSfxToggle = 0;
u8 gAudioLowHPWarningFlag = 0;
u8 gAudioClimaxMusicPlayed = 0;
u8 gAudioRecentHeavyHitFlag = 0;
u8 gAudioQueueSpecialFlag = 0;
s16 gAudioSfxParam0 = 0;
s16 gAudioSfxParam1 = 0;
s16 gAudioSfxParam2 = 0;
u8 gAudioSystemEnabled = 1;
u8 gAudioEffectId = 1;
u32 gCurrentStadiumPhase = 0;
s32 gStadiumPhaseSubstate = 0;
u8 gAudioStadiumSfxEnabled = 0;
u16 MenuSelectionSoundTable[17][9] = { { 0x35, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A }, { 0x35, 0x2B, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A }, { 0x35, 0x2C, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A }, { 0x35, 0x2D, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A }, { 0x37, 0x2F, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A }, { 0x36, 0x2E, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A }, { 0x38, 0x30, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A }, { 0x38, 0x31, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A }, { 0x38, 0x32, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A }, { 0x38, 0x33, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A }, { 0x38, 0x30, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A }, { 0x38, 0x30, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A }, { 0, 0x39, 0x4C, 0x4E, 0x3A, 0x4A, 0x4D, 0x4F, 0x3B }, { 0, 0x4B, 0x4C, 0x4E, 0x3C, 0x4A, 0x4D, 0x4F, 0x3D }, { 0, 0x4B, 0x4C, 0x4E, 0x3E, 0x4A, 0x4D, 0x4F, 0x3F }, { 0, 0x4B, 0x4C, 0x4E, 0x40, 0x4A, 0x4D, 0x4F, 0x41 }, { 0, 0x42, 0x43, 0x44, 0x45, 0x46, 0, 0, 0 } };  // tail holds D_80078446, D_800784EA (linker-defined symbols)
u32 gCommandQueueCount = 0;
AudioCommandMapEntry AudioCommandMap[6] = { { 3, 0x29 }, { 0x8C, 0x83 }, { 0x18, 0x1F }, { 0x9A, 4 }, { 0x9B, 0x2A }, { 0, 0 } };
u8 AudioEffectTriggerIds[20] = { 0xE, 0x36, 0x4A, 0x60, 0x61, 0x68, 0x6A, 0x6B, 0x6E, 0x6F, 0x70, 0x71, 0x73, 0x74, 0x85, 0x97, 0x9F, 0, 0, 0 };
u8 AudioEffectSecondaryIds[24] = { 0x1C, 0x27, 0x2B, 0x2D, 0x51, 0x67, 0x6C, 0x86, 0x94, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

// .rodata

// const f64 gAudioVolumeScale0 = 0.699999999999999956f;
// const f64 gAudioVolumeScale1 = 0.599999999999999978f;
// const f64 gAudioVolumeScale2 = 0.400000000000000022f;
// const f64 gAudioVolumeScale3 = 0.299999999999999989f;

// const f32 gAudioPitchScale0 = 1.100000024f;
// const f32 gAudioPitchScale1 = 1.100000024f;
// const f32 gAudioPitchScale2 = 1.200000048f;
// const f32 gAudioPitchScale3 = 1.100000024f;
// const f32 gAudioPitchStep = 0.009999999776f;

extern f64 gAudioVolumeScale0;
extern f64 gAudioVolumeScale1;
extern f64 gAudioVolumeScale2;
extern f64 gAudioVolumeScale3;

extern f32 gAudioPitchScale0;
extern f32 gAudioPitchScale1;
extern f32 gAudioPitchScale2;
extern f32 gAudioPitchScale3;
extern f32 gAudioPitchStep;

// .bss
extern s32 gAudioDMAFlags;
extern s8 gMusicFadeStepActive;
extern u8 gAudioUnitReadyCode;
extern s32 gAudioUnitReadyStatus;
extern AMAudioMgr __am;
extern AMDMAState dmaState;
extern s32 minFrameSize;
extern u32 frameSize;
extern s32 maxFrameSize;
extern s32 maxRSPCmds;
extern s32 gAudioOutputRate;
extern s32 gAudioMaxVoices;
extern OSMesgQueue audDMAMessageQ;
extern AMDMABuffer* dmaBuffs;
extern OSIoMesg* audDMAIOMesgBuf;
extern OSMesg* audDMAMessageBuf;
extern u32 dmaBufferLen;
extern OSPiHandle* gAudioPiHandle[4];
// s32 D_800FCB0C[3];
extern PokemonAudioInfo* gAudioInfoPtr[4];
extern u32 PlayerCurrentHP[2];
extern u8 MoveQueueFlag[2];
extern u8 RecentMoveIDs[2][8];
extern HPHistoryEntry gHPHistory[2];
extern s32 gAudioRecentMessages[20];
extern u8 gAudioGlobalFlag0;
extern u8 gAudioGlobalFlag1;
extern u8 gAudioQueueDelayCounter;
extern u32 gAudioHPChangePercent;
extern s32 gAudioPrevHPChangePercent;
extern u8 gAudioCurrentMoveId;
extern u8 gAudioCurrentCommandId;
extern u8 gAudioSpecialCounter;
extern u8 gAudioSpecialFlag0;
extern u8 gAudioFaintedSidePlusOne;
extern u8 gAudioSfxCrossoverFlag;
extern u8 gAudioQueueProcessingFlag;
extern u8 gAudioPendingFreezeReaction;
extern u8 gAudioPendingSleepReaction;
extern u8 gAudioPendingDefeatReaction;
extern u8 gAudioAttackContinuesActive;
extern u8 gAudioMoveDamageReactionDone;
extern u8 gAudioEffectState0[2];
extern u8 gAudioEffectStateDominanceCount[2];
extern u8 gAudioEffectStateSleepCount[2];
extern u8 gAudioEffectStateFreezeCount[2];
extern u8 gAudioEffectStateParalysisCount[2];
extern u8 gAudioEffectStateCantMoveCount[2];
extern u8 gAudioEffectStateSelfHitPlayed[2];
extern u8 gAudioEffectMapJRepeatCount[2];
extern u8 gAudioEffectMapKEscalationCount[2];
extern u8 gAudioEffectToggleSfxThrash[2];
extern u8 gAudioEffectFellAsleepPlayed[2];
extern u8 gAudioEffectMapPRepeatCount[2];
extern u8 gAudioEffectMapQRepeatCount[2];
extern u8 gAudioEffectMissCrashPlayed[2];
extern u8 gAudioEffectStateDefeatMsgPlayed[2];
extern u8 gAudioEffectStateHeavyDamageKo[2];
extern s8 gAudioEffectTriggeredMask[0x18];
extern u32 gAudioCommandQueue[10];
extern u8 gAudioShuffleBuffer[0x28];

// function prototypes
void Audio_QueueSoundWithFallbackList(u16, u16*, u8*);
u32 Battle_EstimateMoveDamage(u32, PokemonAudioInfo*, PokemonAudioInfo*);
s32 Battle_MapCategoryIdToCompactIndex(u8);
ALDMAproc __amDmaNew(AMDMAState** state);

/**
 * Sets or clears a bit in an array.
 */
void BitArray_SetBit(u8* array, u8 index, u8 flag) {
    u8 offset = index / 8;
    u8 bitPosition = index % 8;
    u8 mask = (1 << bitPosition);
    if (flag) {
        array[offset] |= mask;   // Set the bit
    } else {
        array[offset] &= ~mask;  // Clear the bit
    }
}

/**
 * Checks if a bit is set in an array.
 */
s32 BitArray_IsBitSet(u8* array, u8 index) {
    u8 offset = index / 8;
    u8 bitPosition = index % 8;
    u8 flag = (array[offset] & (u8)(1 << bitPosition));
    if (flag) {
        return 1;
    }
    return 0;
}

void Audio_SetVoiceEnabled(s32 arg0) {
    if (arg0 != 0) {
        gAudioActiveFlag = 1;
    } else {
        gAudioActiveFlag = 0;
    }
}

void Audio_SetChannelGroupCounts(u8 arg0, u8 arg1, u8 arg2, u8 arg3) {
    gTeamScores[0] = arg0;
    gTeamScores[1] = arg1;
    gTeamScores[2] = arg2;
    gTeamScores[3] = arg3;
}

void Audio_ResetChannelGroupState(u8 arg0) {
    s32 i;

    if (arg0 < 3) {
        for (i = 0; i < 16; i++) {
            gHPHistory[arg0].posX[i] = 0;
            gHPHistory[arg0].unk_28[i] = 0;
            gHPHistory[arg0].unk_50[i] = 0;
        }
        gHPHistory[arg0].unk_20 = 0;
        gHPHistory[arg0].unk_24 = 0;
        gHPHistory[arg0].unk_48 = 0;
        gHPHistory[arg0].unk_4C = 0;
        gHPHistory[arg0].unk_70 = 0;
        gHPHistory[arg0].unk_74 = 0;
        gHPHistory[arg0].unk_78 = 0;
        gHPHistory[arg0].unk_7C = 0;
        gHPHistory[arg0].unk_80 = 0;
        gAudioEffectStateSleepCount[arg0] = 0;
        gAudioEffectStateFreezeCount[arg0] = 0;
        gAudioEffectStateSelfHitPlayed[arg0] = 0;
        gAudioEffectMapJRepeatCount[arg0] = 0;
        gAudioEffectMapKEscalationCount[arg0] = 0;
        gAudioEffectToggleSfxThrash[arg0] = 0;
        gAudioEffectFellAsleepPlayed[arg0] = 0;
        gAudioEffectMapPRepeatCount[arg0] = 0;
        gAudioEffectMapQRepeatCount[arg0] = 0;
        gAudioEffectMissCrashPlayed[arg0] = 0;
        gAudioEffectStateDefeatMsgPlayed[arg0] = 0;
        gAudioEffectStateCantMoveCount[arg0] = 0;
        gAudioEffectStateParalysisCount[arg0] = 0;
    }
}

void Audio_ConfigureChannelGroups(u8 arg0, u8 arg1, u8 arg2, u8 arg3) {
    s32 i;
    s32 j;

    gPlayerSideMap[0] = arg0;
    gPlayerSideMap[1] = arg1;
    gPlayerSideMap[2] = arg2;
    gPlayerSideMap[3] = arg3;
    gPlayerSideActiveIndex[0] = 0xFF;
    gPlayerSideActiveIndex[1] = 0xFF;
    gPlayerActiveFlag[0] = 0;
    gPlayerActiveFlag[1] = 0;
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 4; j++) {
            if (i + 1 == gPlayerSideMap[j]) {
                gPlayerActiveFlag[i] += gTeamScores[j];
            }
        }
    }
    gAudioInfoPtr[0] = 0;
    gAudioInfoPtr[1] = 0;
    PlayerCurrentHP[0] = 0;
    PlayerCurrentHP[1] = 0;
    Audio_ResetChannelGroupState(0);
    Audio_ResetChannelGroupState(1);
}

void Audio_SelectModeMusic(u32 arg0, u32 arg1) {
    s32 pad[1];
    u8 sp1B = 0;
    u16 var_a0;

    ResetAudioState();
    gCurrentStadiumPhase = arg1;
    gStadiumPhaseSubstate = arg0;

    if (arg1 < 0x11) {
        gAudioSystemEnabled = 1;
        gAudioStadiumSfxEnabled = 1;

        if ((arg0 == 0) && (arg1 != 0x10) && (arg1 != 0xF)) {
            Audio_QueueSequenceId(0x34);
        } else if ((arg0 == 0xFF) && (arg1 != 0x10) && (arg1 != 0xF)) {
            Audio_QueueSequenceId(0x47);
            arg0 = 0;
            sp1B = 1;
        }

        if (arg1 < 0xC) {
            if (arg0 < 9) {
                var_a0 = MenuSelectionSoundTable[arg1][arg0];
                gAudioSystemEnabled = 1;
                gAudioEffectId = 1;
            } else {
                return;
            }
        } else if (arg1 == 0xC) {
            if ((arg0 < 0x21) && (arg0 != 0)) {
                var_a0 = D_800784EA[(arg0 - 1) / 8][(arg0 - 1) % 8];
                gAudioSystemEnabled = 1;
                gAudioEffectId = 0;
            } else {
                return;
            }
        } else if (arg1 == 0xD) {
            if (arg0 < 6) {
                var_a0 = D_80078446[arg1][arg0];
                gAudioSystemEnabled = 1;
                gAudioEffectId = 0;
            } else {
                return;
            }
        } else {
            if (arg1 == 0xE) {
                var_a0 = 0x49;
                gAudioSystemEnabled = 1;
                gAudioEffectId = 2;
            } else if (arg1 == 0xF) {
                var_a0 = 0;
                gAudioSystemEnabled = 0;
                gAudioEffectId = 0;
                arg0 = 1;
            } else {
                if (arg1 == 0x10) {
                    var_a0 = 0x48;
                    gAudioEffectId = 1;
                    arg0 = 1;
                } else {
                    var_a0 = 0;
                    gAudioEffectId = 1;
                }
                gAudioSystemEnabled = 1;
            }
        }

        if ((arg0 == 0) && (sp1B == 0)) {
            gAudioEffectId = 2;
        }

        if (var_a0 != 0) {
            Audio_QueueSequenceId(var_a0);
        }
    }
}

void AudioFrameUpdate(s32 arg0) {
    s8 var_t0;
    s8 var_t2;
    s8 var_t4;
    s8 var_t5;
    s32 var_v0;
    s32 var_a0;
    s32 i;

    if (arg0 != 0) {
        var_v0 = osSetIntMask(1);
        gAudioSeqActiveFlag = 1;
        gAudioSeqElapsed = 0;
        gAudioSeqState = 0;
        gAudioSeqPlayedFlag = 0;
        osSetIntMask(var_v0);
        gAudioEstimateMinus3Latched = 0;
        gAudioOneRemovalLatched = 0;
        gAudioQueueSfxToggle = 0;
        gAudioSpecialCounter = 0;
        gAudioSpecialFlag0 = 0;
        gAudioQueueProcessingFlag = 0;
        gAudioAttackContinuesActive = 0;
        gAudioRecentHeavyHitFlag = 0;
        gAudioQueueSpecialFlag = 0;
        gAudioHPChangePercent = 0;
        Audio_PlayCommand(0x5A, gAudioEffectId, 0);

        if ((gAudioInfoPtr[0] == NULL) || (gAudioInfoPtr[1] == NULL)) {
            return;
        }

        if (gAudioInfoPtr[0] != NULL) {
            PlayerCurrentHP[0] = gAudioInfoPtr[0]->unk_0C;
        }

        if (gAudioInfoPtr[1] != NULL) {
            PlayerCurrentHP[1] = gAudioInfoPtr[1]->unk_0C;
        }

        gHPHistory[0].unk_24++;
        gHPHistory[0].posX[gHPHistory[0].unk_24 & 0xF] = gAudioInfoPtr[0]->unk_0C;
        gHPHistory[1].unk_24++;
        gHPHistory[1].posX[gHPHistory[1].unk_24 & 0xF] = gAudioInfoPtr[1]->unk_0C;

        if (gAudioQueueMode == 0) {
            return;
        }

        if (gAudioInfoPtr[0]->unk_26 < gAudioInfoPtr[1]->unk_26) {
            var_t2 = 0;
            var_t4 = 1;
        } else {
            var_t2 = 1;
            var_t4 = 0;
        }

        if (gAudioInfoPtr[0]->unk_0C < gAudioInfoPtr[1]->unk_0C) {
            var_t0 = 0;
            var_t5 = 1;
        } else {
            var_t0 = 1;
            var_t5 = 0;
        }

        if (gAudioQueueMode < 2) {
            if ((gAudioInfoPtr[0]->unk_0C == 0) || (gAudioInfoPtr[1]->unk_0C == 0)) {
                var_v0 = osSetIntMask(1);
                gAudioSeqState = 1;
                osSetIntMask(var_v0);

                if (gAudioInfoPtr[0]->unk_0C == 0) {
                    gAudioFaintedSidePlusOne = 1;
                } else {
                    gAudioFaintedSidePlusOne = 2;
                }

                if ((gAudioInfoPtr[0]->unk_0C == 0) && (gAudioInfoPtr[1]->unk_0C == 0)) {
                    Audio_QueueSoundAvoidingRecent(gAudioCueTable_GenericZero);
                } else {
                    Audio_QueueSoundAvoidingRecent(gAudioCueTable_0x252);
                }
                return;
            }

            if (((((u32)gAudioInfoPtr[0]->unk_0C * 100) / gAudioInfoPtr[0]->unk_28) < 0x1E) &&
                ((((u32)gAudioInfoPtr[1]->unk_0C * 100) / gAudioInfoPtr[1]->unk_28) < 0x1E)) {
                Audio_QueueSoundAvoidingRecent(gAudioCueTable_GenericMid);
                return;
            }

            if (((((gAudioInfoPtr[var_t4]->unk_26 - gAudioInfoPtr[var_t2]->unk_26) * 0x64U) /
                  gAudioInfoPtr[var_t2]->unk_26) >= 0x15) &&
                ((((u32)gAudioInfoPtr[var_t2]->unk_0C * 100) / gAudioInfoPtr[var_t2]->unk_28) < 0x28) &&
                ((((u32)gAudioInfoPtr[var_t4]->unk_0C * 100) / gAudioInfoPtr[var_t4]->unk_28) >= 0x51)) {
                if ((osGetTime() % 3) == 0) {
                    var_a0 = 0x256;
                    goto block_53;
                }
            }

            if (((((u32)gAudioInfoPtr[0]->unk_0C * 100) / gAudioInfoPtr[0]->unk_28) >= 0x5B) &&
                ((((u32)gAudioInfoPtr[1]->unk_0C * 100) / gAudioInfoPtr[1]->unk_28) >= 0x5B)) {
                Audio_QueueSoundAvoidingRecent(gAudioCueTable_0x24E);
            } else if (gAudioEffectId == 0) {
                Audio_QueueSoundAvoidingRecent(gAudioCueTable_GenericLow);
            } else {
                Audio_QueueSoundAvoidingRecent(gAudioCueTable_0x24F);
            }
            return;
        }

        if ((gAudioInfoPtr[0]->unk_0C == 0) || (gAudioInfoPtr[1]->unk_0C == 0)) {
            var_v0 = osSetIntMask(1);
            gAudioSeqState = 1;
            osSetIntMask(var_v0);

            if (gAudioInfoPtr[0]->unk_0C == 0) {
                gAudioFaintedSidePlusOne = 1;
            } else {
                gAudioFaintedSidePlusOne = 2;
            }

            if (gPlayerActiveFlag[0] >= gPlayerActiveFlag[1]) {
                var_v0 = gPlayerActiveFlag[0] - gPlayerActiveFlag[1];
            } else {
                var_v0 = gPlayerActiveFlag[1] - gPlayerActiveFlag[0];
            }

            if (var_v0 >= 2) {
                Audio_QueueSoundAvoidingRecent(gAudioCueTable_0x251);
                return;
            }

            if ((gPlayerActiveFlag[0] == 1) && (gPlayerActiveFlag[1] == 1)) {
                if (gAudioClimaxMusicPlayed != 0) {
                    gAudioClimaxMusicPlayed = 0;
                    var_a0 = 0x290;
                } else if ((osGetTime() % 2) != 0) {
                    var_a0 = 0x254;
                } else {
                    var_a0 = 0x26B;
                }
            block_53:
                Audio_QueueSequenceId(var_a0);
            } else if (gPlayerActiveFlag[gAudioFaintedSidePlusOne - 1] == 1) {
                Audio_QueueSequenceId(0x26A);
            } else {
                Audio_QueueSoundAvoidingRecent(gAudioCueTable_0x269);
            }
            return;
        }

        if (gAudioFaintedSidePlusOne != 0) {
            if (((gPlayerActiveFlag[0] == 1) || (gPlayerActiveFlag[1] == 1)) && (gPlayerActiveFlag[0] < 4) &&
                (gPlayerActiveFlag[1] < 4)) {
                if (gPlayerActiveFlag[0] == 1) {
                    switch (gPlayerActiveFlag[1]) {
                        case 1:
                            Audio_QueueSequenceId(0x260);
                            Audio_QueueSequenceId(0x266);
                            break;

                        case 2:
                            Audio_QueueSequenceId(0x261);
                            if (gAudioFaintedSidePlusOne == 1) {
                                Audio_QueueSequenceId(0x265);
                            } else {
                                Audio_QueueSequenceId(0x267);
                            }
                            break;

                        case 3:
                            Audio_QueueSequenceId(0x262);
                            Audio_QueueSequenceId(0x264);
                            break;

                        default:
                            Audio_QueueSequenceId(0x271);
                            break;
                    }

                    gAudioFaintedSidePlusOne = 0;
                    return;
                }

                switch (gPlayerActiveFlag[0]) {
                    case 2:
                        Audio_QueueSequenceId(0x25E);
                        if (gAudioFaintedSidePlusOne == 2) {
                            Audio_QueueSequenceId(0x265);
                        } else {
                            Audio_QueueSequenceId(0x267);
                        }
                        break;

                    case 3:
                        Audio_QueueSequenceId(0x25C);
                        Audio_QueueSequenceId(0x264);
                        break;

                    default:
                        Audio_QueueSequenceId(0x271);
                        break;
                }

                gAudioFaintedSidePlusOne = 0;
                return;
            }

            if (gAudioSfxCrossoverFlag != 0) {
                if ((osGetTime() % 2) != 0) {
                    gAudioFaintedSidePlusOne = 0;
                    Audio_QueueSoundAvoidingRecent(gAudioCueTable_0x281);
                    return;
                }
            }

            if (gAudioInfoPtr[0]->unk_16[6] != gAudioInfoPtr[1]->unk_16[6]) {
                if (gAudioInfoPtr[0]->unk_16[6] != gAudioInfoPtr[1]->unk_16[7]) {
                    if ((gAudioInfoPtr[0]->unk_16[7] != gAudioInfoPtr[1]->unk_16[6]) &&
                        (gAudioInfoPtr[0]->unk_16[7] != gAudioInfoPtr[1]->unk_16[7])) {
                        gAudioFaintedSidePlusOne = 0;
                        Audio_QueueSoundAvoidingRecent(gAudioCueTable_0x27E);
                        return;
                    }
                }
            }

            gAudioFaintedSidePlusOne = 0;
            switch (gPlayerActiveFlag[0]) {
                case 2:
                    switch (gPlayerActiveFlag[1]) {
                        case 2:
                            Audio_QueueSequenceId(0x25D);
                            Audio_QueueSequenceId(0x268);
                            break;

                        case 3:
                            Audio_QueueSequenceId(0x25F);
                            Audio_QueueSequenceId(0x263);
                            break;

                        default:
                            Audio_QueueSequenceId(0x271);
                            break;
                    }
                    break;

                case 3:
                    if (gPlayerActiveFlag[1] == 2) {
                        Audio_QueueSequenceId(0x25B);
                        Audio_QueueSequenceId(0x263);
                    } else {
                        Audio_QueueSequenceId(0x271);
                    }
                    break;

                default:
                    if (gAudioEffectId == 0) {
                        Audio_QueueSoundAvoidingRecent(gAudioCueTable_GenericLow);
                    } else {
                        Audio_QueueSoundAvoidingRecent(gAudioCueTable_0x24F);
                    }
                    break;
            }

            return;
        }

        if (gAudioPendingFreezeReaction != 0) {
            Audio_QueueSoundAvoidingRecent(gAudioCueTable_0x27C);
            gAudioPendingFreezeReaction = 0;
            return;
        }

        if (gAudioPendingSleepReaction != 0) {
            Audio_QueueSoundAvoidingRecent(gAudioCueTable_0x27A);
            gAudioPendingSleepReaction = 0;
            return;
        }

        if (gAudioPendingDefeatReaction != 0) {
            Audio_QueueSoundAvoidingRecent(gAudioCueTable_0x284);
            gAudioPendingDefeatReaction = 0;
            return;
        }

        if ((gAudioInfoPtr[0]->unk_28 * 0.5f) <
            (gHPHistory[0].posX[(gHPHistory[0].unk_24 - 1) & 0xF] -
             gHPHistory[0].posX[gHPHistory[0].unk_24 & 0xF])) {
            if ((gAudioInfoPtr[1]->unk_28 * 0.5f) <
                (gHPHistory[1].posX[(gHPHistory[1].unk_24 - 1) & 0xF] -
                 gHPHistory[1].posX[gHPHistory[1].unk_24 & 0xF])) {
                if (((((u32)gAudioInfoPtr[0]->unk_0C * 100) / gAudioInfoPtr[0]->unk_28) < 0x14U) &&
                    ((((u32)gAudioInfoPtr[1]->unk_0C * 100) / gAudioInfoPtr[1]->unk_28) < 0x14U)) {
                    Audio_QueueSoundAvoidingRecent(gAudioCueTable_0x25A);
                } else {
                    Audio_QueueSoundAvoidingRecent(gAudioCueTable_0x259);
                }
                return;
            }
        }

        if (gAudioInfoPtr[0]->unk_0C >= gAudioInfoPtr[1]->unk_0C) {
            var_v0 = gAudioInfoPtr[0]->unk_0C - gAudioInfoPtr[1]->unk_0C;
        } else {
            var_v0 = gAudioInfoPtr[1]->unk_0C - gAudioInfoPtr[0]->unk_0C;
        }

        if (((gAudioInfoPtr[var_t0]->unk_28 * 0.7) < var_v0) &&
            ((((u32)gAudioInfoPtr[var_t5]->unk_0C * 100) / gAudioInfoPtr[var_t5]->unk_28) >= 0x47) &&
            (gAudioInfoPtr[0]->unk_0C != gAudioInfoPtr[0]->unk_28) && (gAudioInfoPtr[1]->unk_0C != gAudioInfoPtr[1]->unk_28)) {
            if ((gAudioInfoPtr[var_t5]->unk_28 * 0.6) < gAudioInfoPtr[var_t5]->unk_0C) {
                if (gAudioInfoPtr[var_t0]->unk_0C < (gAudioInfoPtr[var_t0]->unk_28 * 0.4)) {
                    Audio_QueueSoundAvoidingRecent(gAudioCueTable_0x24D);
                    return;
                }
            }
        }

        if (gAudioInfoPtr[0]->unk_0C >= gAudioInfoPtr[1]->unk_0C) {
            var_v0 = gAudioInfoPtr[0]->unk_0C - gAudioInfoPtr[1]->unk_0C;
        } else {
            var_v0 = gAudioInfoPtr[1]->unk_0C - gAudioInfoPtr[0]->unk_0C;
        }

        if (var_v0 < 0xA) {
            if ((gAudioInfoPtr[0]->unk_28 * 0.5) < gAudioInfoPtr[0]->unk_0C) {
                if (((gAudioInfoPtr[1]->unk_28 * 0.5) < gAudioInfoPtr[1]->unk_0C) &&
                    (gAudioInfoPtr[0]->unk_0C < gAudioInfoPtr[0]->unk_28) &&
                    (gAudioInfoPtr[1]->unk_0C < gAudioInfoPtr[1]->unk_28)) {
                    Audio_QueueSoundAvoidingRecent(gAudioCueTable_0x24B);
                    return;
                }
            }
        }

        if (gAudioInfoPtr[0]->unk_0C >= gAudioInfoPtr[1]->unk_0C) {
            var_v0 = gAudioInfoPtr[0]->unk_0C - gAudioInfoPtr[1]->unk_0C;
        } else {
            var_v0 = gAudioInfoPtr[1]->unk_0C - gAudioInfoPtr[0]->unk_0C;
        }

        if (var_v0 < 0xA) {
            if (gAudioInfoPtr[0]->unk_0C < (gAudioInfoPtr[0]->unk_28 * 0.3)) {
                if (gAudioInfoPtr[1]->unk_0C < (gAudioInfoPtr[1]->unk_28 * 0.3)) {
                    Audio_QueueSoundAvoidingRecent(gAudioCueTable_0x24C);
                    return;
                }
            }
        }

        if (gAudioEffectId == 0) {
            Audio_QueueSoundAvoidingRecent(gAudioCueTable_GenericLow);
        } else {
            Audio_QueueSoundAvoidingRecent(gAudioCueTable_0x24F);
        }

        return;
    }

    var_v0 = osSetIntMask(1);
    gAudioSeqActiveFlag = 0;
    osSetIntMask(var_v0);
    Audio_FadeCommand(0x5A, 0);
    Audio_FadeCommand(0x5B, 0);

    if (gAudioInfoPtr[0] != NULL) {
        PlayerCurrentHP[0] = gAudioInfoPtr[0]->unk_0C;
    }

    if (gAudioInfoPtr[1] != NULL) {
        PlayerCurrentHP[1] = gAudioInfoPtr[1]->unk_0C;
    }

    gAudioQueueMode++;

    for (i = 0; i < 2; i++) {
        gHPHistory[i].unk_78++;
        if (gHPHistory[i].unk_7C != 0) {
            gHPHistory[i].unk_7C++;
        }
    }

    gAudioPendingSleepReaction = 0;
    gAudioPendingFreezeReaction = 0;
    gAudioPendingDefeatReaction = 0;
    gAudioClimaxMusicPlayed = 0;

    if ((gAudioInfoPtr[0] != NULL) && (gAudioInfoPtr[1] != NULL) && (gAudioStadiumSfxEnabled != 0) &&
        (gAudioInfoPtr[0]->unk_0C != 0) && (gAudioInfoPtr[1]->unk_0C != 0) && (AudioStream_IsPlaying(1) == 0)) {
        if ((osGetTime() % 2) == 0) {
            Audio_QueueSoundAvoidingRecent(gAnnouncerCueBattleCommentary);
        }
    }
}

void ProcessAudioInfo(s32 arg0, PokemonAudioInfo* arg1) {
    u8 pad;
    u8 value;
    u8 side;
    u8 changed = 0;
    u32 i;
    u8 pad2;

    gAudioSfxCrossoverFlag = 0;
    gAudioSfxParam0 = 0;
    gAudioSfxParam1 = 0;
    gAudioSfxParam2 = 0;

    if (arg1 == NULL) {
        return;
    }
    if ((arg0 == 0) || ((u32)arg0 >= 5)) {
        return;
    }

    arg0--;
    side = gPlayerSideMap[arg0];
    if ((side <= 0) || (side >= 3)) {
        return;
    }
    side--;
    side &= 0xFF;

    if (gPlayerSideActiveIndex[side] != arg0) {
        changed = 1;
        gPlayerSideActiveIndex[side] = arg0;
    }

    gAudioInfoPtr[side] = arg1;

    Audio_ResetChannelGroupState(side);

    gAudioEffectMapKEscalationCount[side ^ 1] = 0;

    PlayerCurrentHP[side] = gAudioInfoPtr[side]->unk_0C;
    gHPHistory[side].unk_24++;
    gHPHistory[side].posX[gHPHistory[side].unk_24 & 0xF] = gAudioInfoPtr[side]->unk_0C;

    value = gAudioInfoPtr[side]->unk_0B;
    if ((value <= 0) || (value >= 0x98)) {
        return;
    }

    for (i = 0; i < gRecentMoveCount[side]; i++) {
        if (RecentMoveIDs[side][i] == value) {
            goto found_value;
        }
    }

    RecentMoveIDs[side][gRecentMoveCount[side]] = value;
    gRecentMoveCount[side]++;
    if (gRecentMoveCount[side] >= 8) {
        gRecentMoveCount[side] = 7;
    }

    MoveQueueFlag[side] = 0;
    if (gAudioQueueMode != 0) {
        Audio_QueueSequenceId(value + 0xCB);
        if (changed) {
            Audio_QueueSoundAvoidingRecent(gAnnouncerCueSwitchIn);
        }

        if (gAudioInfoPtr[side ^ 1] == NULL) {
            return;
        }

        if (((f32)gAudioInfoPtr[side ^ 1]->unk_26 - (f32)(gAudioInfoPtr[side])->unk_26) > ((f32)(gAudioInfoPtr[side])->unk_26 * 2.0f)) {
            gAudioSfxCrossoverFlag = 1;
            gAudioEffectStateDominanceCount[side] = 0;
            return;
        }

        if (((f32)(gAudioInfoPtr[side])->unk_26 * 0.3f) < ((f32)gAudioInfoPtr[side ^ 1]->unk_26 - (f32)(gAudioInfoPtr[side])->unk_26)) {
            gAudioSfxCrossoverFlag = 1;
            gAudioEffectStateDominanceCount[side] = 0;
            return;
        }

        if (((f32)gAudioInfoPtr[side ^ 1]->unk_26 * 0.3f) < ((f32)(gAudioInfoPtr[side])->unk_26 - (f32)gAudioInfoPtr[side ^ 1]->unk_26)) {
            gAudioSfxCrossoverFlag = 1;
            if ((gAudioEffectStateHeavyDamageKo[side] != 0) && (gAudioEffectStateDominanceCount[side] != 0)) {
                if (changed == 0) {
                    Audio_QueueSoundAvoidingRecent(gAnnouncerCueUnderdogRepeat);
                }
            } else if (changed == 0) {
                Audio_QueueSoundWithFallbackList(9, gAnnouncerCueUnderdog, &gAudioEffectStateDominanceCount[side]);
            } else {
                gAudioEffectStateDominanceCount[side]++;
            }

            gAudioEffectState0[side] = 0;
            gAudioEffectStateHeavyDamageKo[side] = 0;
            return;
        }

        if ((gPlayerActiveFlag[side] == 2) && (gPlayerActiveFlag[side ^ 1] == 3)) {
            if ((((u32)gAudioInfoPtr[side ^ 1]->unk_0C * 100) / gAudioInfoPtr[side ^ 1]->unk_28) < 0x32) {
                if (gAudioLowHPWarningFlag == 0) {
                    if (changed == 0) {
                        Audio_QueueSequenceId(0xA);
                    }
                    gAudioLowHPWarningFlag = 1;
                }
            }
        }
    }
    gAudioEffectState0[side] = 0;
    gAudioEffectStateDominanceCount[side] = 0;
    return;

found_value:
    if (MoveQueueFlag[side] == 0) {
        if (gAudioQueueSfxToggle == 0) {
            if (gPlayerActiveFlag[side] < 2) {
                if ((osGetTime() % 2) == 0) {
                    Audio_QueueSequenceId(2);
                } else {
                    Audio_QueueSequenceId(1);
                }
            } else {
                Audio_QueueSequenceId(0x50);
                if (changed != 0) {
                    Audio_QueueSoundAvoidingRecent(gAnnouncerCueSwitchIn);
                }
            }
            gAudioQueueSfxToggle = 1;
        } else {
            Audio_QueueSequenceId(0x58);
            gAudioQueueSfxToggle = 0;
            if (changed != 0) {
                Audio_QueueSoundAvoidingRecent(gAnnouncerCueSwitchIn);
            }
        }
    } else if (changed != 0) {
        Audio_QueueSoundAvoidingRecent(gAnnouncerCueSwitchIn);
    }

    MoveQueueFlag[side] = 0;

    if (gAudioInfoPtr[side ^ 1] == NULL) {
        return;
    }

    if (changed != 0) {
        return;
    }

    if ((gAudioInfoPtr[side])->unk_15 & 0x20) {
        Audio_QueueSoundAvoidingRecent(gAnnouncerCueFrozen);
        return;
    }

    if ((gAudioInfoPtr[side])->unk_15 & 7) {
        Audio_QueueSoundAvoidingRecent(gAnnouncerCueAsleep);
        return;
    }

    if ((gAudioInfoPtr[side])->unk_15 & 8) {
        Audio_QueueSequenceId(6);
        return;
    }

    if ((gAudioInfoPtr[side])->unk_15 & 0x10) {
        Audio_QueueSequenceId(7);
        return;
    }

    if ((((f32)(gAudioInfoPtr[side])->unk_0C / (f32)(gAudioInfoPtr[side])->unk_28) < 0.2f) && ((gAudioInfoPtr[side])->unk_0C < gAudioInfoPtr[side ^ 1]->unk_0C)) {
        Audio_QueueSoundAvoidingRecent(gAnnouncerCueLowHp);
    }
}

void RemovePlayer(u32 arg0) {
    u8 sp1F;

    if (arg0 == 0 || arg0 >= 5) {
        return;
    }
    arg0--;
    sp1F = gPlayerSideMap[arg0];
    if (sp1F <= 0 || sp1F >= 3) {
        return;
    }
    sp1F--;
    gTeamScores[arg0]--;
    gPlayerActiveFlag[sp1F]--;
    MoveQueueFlag[sp1F] = 0;
    if (gAudioInfoPtr[0] == 0 || gAudioInfoPtr[1] == 0) {
        return;
    }
    Audio_PlayCommand(0x16, gAudioEffectId, 0);
    if (gAudioOneRemovalLatched != 0) {
        Audio_QueueSequenceId(0xC3);
        gAudioOneRemovalLatched = 0;
        gAudioClimaxMusicPlayed = 1;
        return;
    }
    gAudioOneRemovalLatched = 1;
    if (gAudioEstimateMinus3Latched != 0) {
        Audio_QueueSequenceId(0xB9);
        gAudioEstimateMinus3Latched = 0;
        return;
    }
    if (gAudioQueueMode < 2) {
        if (osGetTime() % 2 == 0) {
            Audio_QueueSequenceId(0xBC);
        } else {                
            Audio_QueueSequenceId(0xC5);
        }
    } else if (gAudioCmd9DLatched != 0) {
        Audio_QueueSequenceId(0xC4);
        gAudioCmd9DLatched = 0;
    } else if ((gAudioHPChangePercent >= 0x64U) && (gAudioQueueProcessingFlag == 0) && (gAudioQueueSpecialFlag == 0)) {
        if (((f32)gAudioInfoPtr[sp1F]->unk_26 * (3.0 / 10.0)) < ((f32)gAudioInfoPtr[sp1F ^ 1]->unk_26 - gAudioInfoPtr[sp1F]->unk_26)) {
            Audio_QueueSoundAvoidingRecent(gAnnouncerCueRecallOutleveled);
        } else {
            Audio_QueueSoundAvoidingRecent(gAnnouncerCueRecallSurvivedBigHit);
        }
        gAudioEffectStateHeavyDamageKo[sp1F] = 1;
    } else if ((gHPHistory[sp1F].unk_78 >= 8U) && (gAudioQueueProcessingFlag == 0)) {
        if (((u32) gAudioHPChangePercent < 5U) && (gAudioRecentHeavyHitFlag == 0)) {
            Audio_QueueSequenceId(0xC2);
        } else {
            Audio_QueueSoundAvoidingRecent(gAnnouncerCueRecallLateBattle);
        }
    } else {
        Audio_QueueSoundAvoidingRecent(gAnnouncerCueRecall);
    }
}

void PlayerDefeated(u32 arg0) {
    u8 temp_v0;
    
    if (arg0 == 0 || arg0 >= 5) {
        return;
    }
    
    arg0--;
    temp_v0 = gPlayerSideMap[arg0];

    if (temp_v0 <= 0 || temp_v0 >= 3) {
        return;
    }
    
    temp_v0--;

    if (gAudioInfoPtr[0] == 0 || gAudioInfoPtr[1] == 0) {
        return;
    }

    if (gAudioInfoPtr[temp_v0]->unk_0C <= 0) {
       return; 
    }
    
    MoveQueueFlag[temp_v0] = 1;
    gAudioPendingDefeatReaction = 1;
    
    if (gAudioQueueSfxToggle != 0) {
        Audio_QueueSequenceId(0x58);
        gAudioQueueSfxToggle = 0;
        return;
    }
    
    gAudioQueueSfxToggle = 1;
    
    if (gAudioQueueMode < 2) {
        if (osGetTime() % 2 == 0) {
            Audio_QueueSequenceId(0x54);
        } else {
            Audio_QueueSequenceId(0x55);
        }
    } else if (gHPHistory[temp_v0].unk_78 < 2) {
        Audio_QueueSoundAvoidingRecent(gAnnouncerCueFaintedFirstTurn);
    } else {
        Audio_QueueSoundAvoidingRecent(gAnnouncerCueFainted);
    }
}

void Audio_QueuePendingSoundId(u32 arg0) {
    gAudioCommandQueue[gCommandQueueCount] = arg0;
    gCommandQueueCount++;
    if (gCommandQueueCount >= 0xA) {
        gCommandQueueCount--;
    }
}

void ProcessAudioCommandQueue(s32 arg0) {
    u32 mask;
    u32 sp40;
    s32 sp3C;
    u8 temp_s0;
    u8 sp3A;
    u8 sp39;
    u8 sp38;
    u8 sp37;
    u8 sp36;
    u8 pad1;
    u8 sp34;
    u8 pad2;
    u8 sp32;

    sp3A = 0;
    sp39 = 0;
    sp38 = 0;
    sp37 = 0;
    sp36 = 0;
    sp34 = 0;
    sp32 = 0;
    mask = osSetIntMask(1);
    sp3C = gAudioQueueDelayCounter;
    gAudioQueueDelayCounter = 0;
    osSetIntMask(mask);
    gAudioCmd9DLatched = 0;
    gAudioQueueProcessingFlag = 0;
    if (arg0 == 0 || arg0 >= 5U) {
        return;
    }
    arg0--;
    temp_s0 = gPlayerSideMap[arg0];
    if (temp_s0 <= 0 || temp_s0 >= 3) {
        return;
    }
    temp_s0--;
    if (gAudioInfoPtr[0] == 0 || gAudioInfoPtr[1] == 0) {
        return;
    }
    for (sp40 = 0; sp40 < gCommandQueueCount; sp40++) {
        switch (gAudioCommandQueue[sp40]) {
        case 0x1D:
            sp3A = 1;
            gAudioQueueNeedsUpdate = 1;
            break;
        case 0x1E:
            sp37 = 1;
            gAudioQueueNeedsUpdate = 1;
            break;
        case 0x29:
            sp39 = 1;
            gAudioQueueNeedsUpdate = 1;
            break;
        case 0x2A:
            sp38 = 1;
            gAudioQueueNeedsUpdate = 1;
            break;
        case 0x66:
            sp36 = 1;
            break;
        case 0x6F:
            sp34 = 1;
            break;
        case 0x6B:
        case 0x6C:
            gHPHistory[temp_s0].unk_24++;
            gHPHistory[temp_s0].posX[gHPHistory[temp_s0].unk_24 & 0xF] = gAudioInfoPtr[temp_s0]->unk_0C;
            mask = osSetIntMask(1);
            gAudioQueueDelayCounter = sp3C;
            osSetIntMask(mask);
            break;
        case 0x6E:
        case 0x70:
        case 0x9E:
        case 0xAB:
            mask = osSetIntMask(1);
            gAudioQueueDelayCounter = sp3C;
            osSetIntMask(mask);
            break;
        case 0x0:
        case 0x1:
        case 0x2:
            gAudioQueueProcessingFlag = 1;
            gAudioQueueSpecialFlag = 1;
            break;
        case 0x9D:
            gAudioCmd9DLatched = 1;
            gAudioQueueProcessingFlag = 1;
            break;
        case 0x6D:
            Audio_QueueSequenceId(0x165);
            gCommandQueueCount = 0;
            gAudioEffectStateFreezeCount[temp_s0] = 0;
            Audio_PlayCommand(0x16, gAudioEffectId, 0);
            return;
        case 0x6:
            if (gHPHistory[temp_s0].unk_7C == 1) {
                Audio_QueueSequenceId(0x19F);
            } else if (gHPHistory[temp_s0].unk_7C >= 4) {
                Audio_QueueSequenceId(0x164);
            } else {
                Audio_QueueSequenceId(0x163);
            }
            gCommandQueueCount = 0;
            gHPHistory[temp_s0].unk_7C = 0;
            gAudioEffectStateSleepCount[temp_s0] = 0;
            gAudioPendingSleepReaction = 0;
            Audio_PlayCommand(0x16, gAudioEffectId, 0);
            return;
        case 0xB:
            Audio_QueueSequenceId(0x17B);
            gCommandQueueCount = 0;
            return;
        case 0xC:
            Audio_QueueSequenceId(0x186);
            gAudioEffectStateSelfHitPlayed[temp_s0] = 0;
            gCommandQueueCount = 0;
            return;
        case 0x11:
            Audio_QueueSequenceId(0x192);
            gAudioEffectStateDefeatMsgPlayed[temp_s0] = 0;
            gCommandQueueCount = 0;
            return;
        case 0x5:
            if ((gPlayerActiveFlag[0] == 1) && (gPlayerActiveFlag[1] == 1)) {
                Audio_QueueSoundWithFallbackList(0x17D, &gAnnouncerCueBothLastPokemon, &gAudioEffectStateSleepCount[temp_s0]);
            } else {
                Audio_QueueSoundWithFallbackList(0x17D, gAnnouncerCueSleep, &gAudioEffectStateSleepCount[temp_s0]);
            }
            gCommandQueueCount = 0;
            return;
        case 0x7:
            if ((gPlayerActiveFlag[0] == 1) && (gPlayerActiveFlag[1] == 1)) {
                Audio_QueueSoundWithFallbackList(0x17E, gAnnouncerCueFreezeLastPokemon, &gAudioEffectStateFreezeCount[temp_s0]);
            } else {
                Audio_QueueSoundWithFallbackList(0x17E, gAnnouncerCueFreeze, &gAudioEffectStateFreezeCount[temp_s0]);
            }
            gCommandQueueCount = 0;
            return;
        case 0x10:
            if ((gPlayerActiveFlag[0] == 1) && (gPlayerActiveFlag[1] == 1)) {
                Audio_QueueSoundWithFallbackList(0x17F, &gAnnouncerCueBothLastPokemon, &gAudioEffectStateParalysisCount[temp_s0]);
            } else {
                Audio_QueueSoundWithFallbackList(0x17F, gAnnouncerCueParalysis, &gAudioEffectStateParalysisCount[temp_s0]);
            }
            gCommandQueueCount = 0;
            return;
        case 0x8:
            if ((gPlayerActiveFlag[0] == 1) && (gPlayerActiveFlag[1] == 1)) {
                Audio_QueueSoundWithFallbackList(0x17C, &gAnnouncerCueBothLastPokemon, &gAudioEffectStateCantMoveCount[temp_s0]);
            } else {
                Audio_QueueSoundWithFallbackList(0x17C, &gAnnouncerCueCantMove, &gAudioEffectStateCantMoveCount[temp_s0]);
            }
            gCommandQueueCount = 0;
            return;
        case 0x9:
        case 0xA:
            if ((gPlayerActiveFlag[0] == 1) && (gPlayerActiveFlag[1] == 1)) {
                Audio_QueueSequenceId(0x180);
            } else {
                Audio_QueueSequenceId(0x17C);
            }
            gCommandQueueCount = 0;
            return;
        case 0x13:
            Audio_QueueSoundAvoidingRecent(gAnnouncerCueAttackContinues);
            gAudioAttackContinuesActive = 1;
            gCommandQueueCount = 0;
            return;
        case 0xF:
            Audio_QueueSequenceId(0x17A);
            gCommandQueueCount = 0;
            return;
        case 0xE:
            gAudioCmd9DLatched = 1;
            if (gAudioEffectStateSelfHitPlayed[temp_s0] != 0) {
                Audio_QueueSoundAvoidingRecent(gAnnouncerCueConfusionSelfHitRepeat);
            } else {
                Audio_QueueSoundAvoidingRecent(gAnnouncerCueConfusionSelfHit);
                gAudioEffectStateSelfHitPlayed[temp_s0] = 1;
            }
            gCommandQueueCount = 0;
            Audio_PlayCommand(0x16, gAudioEffectId, 0);
            return;
        case 0x12:
            if (gAudioEffectToggleSfxThrash[temp_s0] == 0) {
                Audio_QueueSequenceId(0x18C);
            } else {
                Audio_QueueSequenceId(0x18E);
            }
            gAudioEffectToggleSfxThrash[temp_s0] ^= 1;
            gCommandQueueCount = 0;
            Audio_PlayCommand(0x16, gAudioEffectId, 0);
            return;
        case 0x71:
        case 0x77:
            Audio_QueueSoundWithFallbackList(0x16A, &gAnnouncerCueStatUp, &gAudioEffectMapJRepeatCount[temp_s0]);
            gCommandQueueCount = 0;
            return;
        case 0x72:
        case 0x78:
            Audio_QueueSoundWithFallbackList(0x16B, &gAnnouncerCueStatUp, &gAudioEffectMapJRepeatCount[temp_s0]);
            gCommandQueueCount = 0;
            return;
        case 0x73:
        case 0x79:
            Audio_QueueSoundWithFallbackList(0x16C, &gAnnouncerCueStatUp, &gAudioEffectMapJRepeatCount[temp_s0]);
            gCommandQueueCount = 0;
            return;
        case 0x74:
        case 0x7A:
            Audio_QueueSoundWithFallbackList(0x16D, &gAnnouncerCueStatUp, &gAudioEffectMapJRepeatCount[temp_s0]);
            gCommandQueueCount = 0;
            return;
        case 0x75:
        case 0x7B:
            Audio_QueueSoundWithFallbackList(0x16E, &gAnnouncerCueStatUp, &gAudioEffectMapJRepeatCount[temp_s0]);
            gCommandQueueCount = 0;
            return;
        case 0x76:
        case 0x7C:
            Audio_QueueSoundWithFallbackList(0x16F, &gAnnouncerCueStatUp, &gAudioEffectMapJRepeatCount[temp_s0]);
            gCommandQueueCount = 0;
            return;
        case 0xB5:
            Audio_QueueSoundWithFallbackList(0x170, &gAnnouncerCueStatUp, &gAudioEffectMapJRepeatCount[temp_s0]);
            gCommandQueueCount = 0;
            return;
        case 0xB7:
            Audio_QueueSoundWithFallbackList(0x171, &gAnnouncerCueStatUp, &gAudioEffectMapJRepeatCount[temp_s0]);
            gCommandQueueCount = 0;
            return;
        case 0x9A:
            Audio_QueueSoundWithFallbackList(0x169, &gAnnouncerCueStatUp, &gAudioEffectMapJRepeatCount[temp_s0]);
            gCommandQueueCount = 0;
            return;
        case 0x9C:
            Audio_QueueSoundWithFallbackList(0x194, &gAnnouncerCueStatUp, &gAudioEffectMapJRepeatCount[temp_s0]);
            gCommandQueueCount = 0;
            return;
        case 0xAE:
            Audio_QueueSequenceId(0x1A0);
            gCommandQueueCount = 0;
            return;
        case 0x7E:
        case 0x84:
            if (gAudioEffectMapKEscalationCount[temp_s0] < 3) {
                Audio_QueueSoundWithFallbackList(0xA2, gAnnouncerCueStatDown, &gAudioEffectMapKEscalationCount[temp_s0]);
            } else {
                Audio_QueueSoundAvoidingRecent(gAnnouncerCueStatDownRepeat);
            }
            gCommandQueueCount = 0;
            return;
        case 0x7F:
        case 0x85:
            if (gAudioEffectMapKEscalationCount[temp_s0] < 3) {
                Audio_QueueSoundWithFallbackList(0xA3, gAnnouncerCueStatDown, &gAudioEffectMapKEscalationCount[temp_s0]);
            } else {
                Audio_QueueSoundAvoidingRecent(gAnnouncerCueStatDownRepeat);
            }
            gCommandQueueCount = 0;
            return;
        case 0x80:
        case 0x86:
            if (gAudioEffectMapKEscalationCount[temp_s0] < 3) {
                Audio_QueueSoundWithFallbackList(0xA7, gAnnouncerCueStatDown, &gAudioEffectMapKEscalationCount[temp_s0]);
            } else {
                Audio_QueueSoundAvoidingRecent(gAnnouncerCueStatDownRepeat);
            }
            gCommandQueueCount = 0;
            return;
        case 0x81:
        case 0x87:
            if (gAudioEffectMapKEscalationCount[temp_s0] < 3) {
                Audio_QueueSoundWithFallbackList(0xA4, gAnnouncerCueStatDown, &gAudioEffectMapKEscalationCount[temp_s0]);
            } else {
                Audio_QueueSoundAvoidingRecent(gAnnouncerCueStatDownRepeat);
            }
            gCommandQueueCount = 0;
            return;
        case 0x82:
        case 0x88:
            if (gAudioEffectMapKEscalationCount[temp_s0] < 3) {
                Audio_QueueSoundWithFallbackList(0xA5, gAnnouncerCueStatDown, &gAudioEffectMapKEscalationCount[temp_s0]);
            } else {
                Audio_QueueSoundAvoidingRecent(gAnnouncerCueStatDownRepeat);
            }
            gCommandQueueCount = 0;
            return;
        case 0x83:
        case 0x89:
            if (gAudioEffectMapKEscalationCount[temp_s0] < 3) {
                Audio_QueueSoundWithFallbackList(0xA6, gAnnouncerCueStatDown, &gAudioEffectMapKEscalationCount[temp_s0]);
            } else {
                Audio_QueueSoundAvoidingRecent(gAnnouncerCueStatDownRepeat);
            }
            gCommandQueueCount = 0;
            return;
        case 0x19:
        case 0x1B:
            if ((D_800780B3[gAudioCurrentMoveId * 3] == 0) && ((gAudioInfoPtr[temp_s0]->unk_16[6] == 8) || (gAudioInfoPtr[temp_s0]->unk_16[7] == 8))) {
                Audio_QueueSoundAvoidingRecent(gAnnouncerCueNoEffectGhost);
            } else {
                Audio_QueueSoundAvoidingRecent(gAnnouncerCueNoEffect);
            }
            gCommandQueueCount = 0;
            return;
        case 0x1A:
        case 0x1C:
            if (gAudioEffectMissCrashPlayed[temp_s0 ^ 1] != 0) {
                Audio_QueueSoundAvoidingRecent(gAnnouncerCueMissRepeated);
            } else {
                if ((gAudioEstimateMinus3Latched != 0) || ((gPlayerActiveFlag[temp_s0 ^ 1] == 1) && (gAudioInfoPtr[temp_s0 ^ 1]->unk_0C < 0x13))) {
                    Audio_QueueSoundAvoidingRecent(gAnnouncerCueMissNearKnockout);
                    Audio_PlayCommand(0x16, gAudioEffectId, 0);
                } else {
                    Audio_QueueSoundAvoidingRecent(gAnnouncerCueAttackMissed);
                }
                gAudioEffectMissCrashPlayed[temp_s0 ^ 1] = 1;
            }
            gCommandQueueCount = 0;
            return;
        case 0xA7:
            Audio_QueueSoundAvoidingRecent(gAnnouncerCueAttackMissed);
            gCommandQueueCount = 0;
            return;
        case 0x20:
        case 0x7D:
        case 0x8C:
        case 0x99:
        case 0x9B:
        case 0xA5:
        case 0xAD:
        case 0xB2:
        case 0xB4:
        case 0xB6:
        case 0xB8:
        case 0xB9:
        case 0xBA:
        case 0xBC:
            Audio_QueueSoundAvoidingRecent(gAnnouncerCueMoveFailed);
            gCommandQueueCount = 0;
            return;
        case 0x64:
        case 0x65:
        case 0x67:
        case 0x6A:
        case 0x8A:
        case 0x8B:
        case 0x8D:
        case 0x91:
        case 0x92:
        case 0xA0:
        case 0xA2:
        case 0xA3:
        case 0xAA:
            Audio_QueueSoundAvoidingRecent(gAnnouncerCueMoveNoEffect);
            gCommandQueueCount = 0;
            return;
        case 0x1F:
            Audio_QueueSequenceId(0x18D);
            gCommandQueueCount = 0;
            return;
        case 0x93:
        case 0x94:
        case 0x95:
        case 0x96:
            Audio_QueueSequenceId(0x18F);
            gCommandQueueCount = 0;
            return;
        case 0x97:
            Audio_QueueSoundWithFallbackList(0x18A, gAnnouncerCueFly, &gAudioEffectMapPRepeatCount[temp_s0]);
            gCommandQueueCount = 0;
            Audio_PlayCommand(0x16, gAudioEffectId, 0);
            return;
        case 0x98:
            Audio_QueueSoundWithFallbackList(0x18B, gAnnouncerCueDig, &gAudioEffectMapQRepeatCount[temp_s0]);
            gCommandQueueCount = 0;
            Audio_PlayCommand(0x16, gAudioEffectId, 0);
            return;
        case 0x2B:
            Audio_QueueSequenceId(0x76);
            gCommandQueueCount = 0;
            return;
        case 0x2C:
            Audio_QueueSoundAvoidingRecent(gAnnouncerCueSubstituteBroke);
            gCommandQueueCount = 0;
            return;
        case 0xBB:
            Audio_QueueSequenceId(0x189);
            gCommandQueueCount = 0;
            Audio_PlayCommand(0x16, gAudioEffectId, 0);
            gAudioCmd9DLatched = 1;
            return;
        case 0x68:
            Audio_QueueSoundAvoidingRecent(gAnnouncerCueBadlyPoisoned);
            gCommandQueueCount = 0;
            return;
        case 0x69:
            Audio_QueueSoundAvoidingRecent(gAnnouncerCuePoison);
            gCommandQueueCount = 0;
            return;
        case 0xA1:
            Audio_QueueSequenceId(0x7A);
            gCommandQueueCount = 0;
            return;
        case 0xA6:
            Audio_QueueSoundAvoidingRecent(gAnnouncerCueLeechSeed);
            gCommandQueueCount = 0;
            return;
        case 0xAF:
        case 0xB0:
            Audio_QueueSequenceId(0x167);
            gHPHistory[temp_s0].unk_24++;
            gHPHistory[temp_s0].posX[gHPHistory[temp_s0].unk_24 & 0xF] = gAudioInfoPtr[temp_s0]->unk_0C;
            gCommandQueueCount = 0;
            return;
        case 0xB1:
            Audio_QueueSequenceId(0x166);
            gHPHistory[temp_s0].unk_24++;
            gHPHistory[temp_s0].posX[gHPHistory[temp_s0].unk_24 & 0xF] = gAudioInfoPtr[temp_s0]->unk_0C;
            gCommandQueueCount = 0;
            return;
        case 0xB3:
            Audio_QueueSequenceId(0x188);
            gCommandQueueCount = 0;
            Audio_PlayCommand(0x16, gAudioEffectId, 0);
            return;
        case 0xA8:
            Audio_QueueSequenceId(0x197);
            gCommandQueueCount = 0;
            return;
        case 0xA9:
            Audio_QueueSequenceId(0x193);
            gCommandQueueCount = 0;
            return;
        case 0xA4:
            Audio_QueueSequenceId(0x195);
            gCommandQueueCount = 0;
            return;
        case 0xAC:
            Audio_QueueSequenceId(0x196);
            gCommandQueueCount = 0;
            return;
        case 0x9F:
            Audio_QueueSequenceId(0x87);
            gCommandQueueCount = 0;
            return;
        case 0x4:
            sp32 = 1;
            break;
        default:
            break;
        }
    }
    gCommandQueueCount = 0;

    if (sp34 != 0) {
        mask = osSetIntMask(1);
        gAudioQueueDelayCounter = 0;
        osSetIntMask(mask);
        Audio_QueueSequenceId(0x79);
        gAudioPendingFreezeReaction = 1;
        Audio_PlayCommand(0x16, gAudioEffectId, 0);
    } else if (sp36 != 0) {
        mask = osSetIntMask(1);
        gAudioQueueDelayCounter = 0;
        osSetIntMask(mask);
        if (gAudioEffectFellAsleepPlayed[temp_s0] != 0) {
            Audio_QueueSequenceId(0xAD);
        } else {
            Audio_QueueSequenceId(0x78);
        }
        gHPHistory[temp_s0].unk_7C = 1;
        gAudioEffectFellAsleepPlayed[temp_s0] = 1;
        gAudioPendingSleepReaction = 1;
        Audio_PlayCommand(0x16, gAudioEffectId, 0);
    } else if (sp37 != 0) {
        mask = osSetIntMask(1);
        gAudioQueueDelayCounter = 0;
        osSetIntMask(mask);
        gAudioRecentHeavyHitFlag = 1;
        Audio_QueueSequenceId(0x77);
        Audio_PlayCommand(0x16, gAudioEffectId, 0);
    } else if (sp3A != 0) {
        mask = osSetIntMask(1);
        gAudioQueueDelayCounter = 0;
        osSetIntMask(mask);
        gAudioRecentHeavyHitFlag = 1;
        if (sp39 != 0) {
            if (gAudioHPChangePercent < 0xA) {
                if ((gAudioInfoPtr[temp_s0]->unk_0C > 0) && (gAudioInfoPtr[temp_s0 ^ 1]->unk_0C >= 0xB)) {
                    Audio_QueueSoundAvoidingRecent(gAnnouncerCueCriticalHitLowDamage);
                } else {
                    Audio_QueueSoundAvoidingRecent(gAnnouncerCueLightHitLowHp);
                }
            } else if (gAudioQueueMode < 2) {
                Audio_QueueSequenceId(0x68);
                Audio_PlayCommand(0x16, gAudioEffectId, 0);
            } else {
                if ((gHPHistory[temp_s0 ^ 1].unk_78 < 2U) && (gPlayerActiveFlag[temp_s0 ^ 1] >= 2)) {
                    Audio_QueueSoundAvoidingRecent(gAnnouncerCueSuperEffectiveEarly);
                } else {
                    Audio_QueueSoundAvoidingRecent(gAudioCueTable_ItemDrop);
                }
                Audio_PlayCommand(0x16, gAudioEffectId, 0);
            }
        } else if (gAudioHPChangePercent < 0xA) {
            if ((gAudioInfoPtr[temp_s0]->unk_0C > 0) && (gAudioInfoPtr[temp_s0 ^ 1]->unk_0C >= 0xB)) {
                Audio_QueueSoundAvoidingRecent(gAnnouncerCueCriticalHitLowDamage);
            } else {
                Audio_QueueSoundAvoidingRecent(gAnnouncerCueLightHitLowHp);
            }
        } else {
            Audio_QueueSoundAvoidingRecent(gAudioCueTable_ItemUnequip);
            Audio_PlayCommand(0x16, gAudioEffectId, 0);
        }
    } else if (sp39 != 0) {
        mask = osSetIntMask(1);
        gAudioQueueDelayCounter = 0;
        osSetIntMask(mask);
        gAudioRecentHeavyHitFlag = 1;
        if ((gHPHistory[temp_s0 ^ 1].unk_78 < 2U) && (gPlayerActiveFlag[temp_s0 ^ 1] >= 2)) {
            Audio_QueueSoundAvoidingRecent(gAnnouncerCueSuperEffectiveEarly);
        } else {
            Audio_QueueSoundAvoidingRecent(gAudioCueTable_ItemThrow);
        }
        Audio_PlayCommand(0x16, gAudioEffectId, 0);
    } else if (sp38 != 0) {
        mask = osSetIntMask(1);
        gAudioQueueDelayCounter = 0;
        osSetIntMask(mask);
        if (gAudioHPChangePercent >= 0x29) {
            Audio_QueueSoundAvoidingRecent(gAnnouncerCueNotVeryEffectiveHeavy);
            Audio_PlayCommand(0x16, gAudioEffectId, 0);
        } else if ((gAudioInfoPtr[0]->unk_0C > 0) && (gAudioInfoPtr[1]->unk_0C > 0)) {
            Audio_QueueSoundAvoidingRecent(gAudioCueTable_ItemPickup);
        } else {
            Audio_QueueSoundAvoidingRecent(gAnnouncerCueLightHitLowHp);
            Audio_PlayCommand(0x16, gAudioEffectId, 0);
        }
    } else if ((sp32 != 0) && (gAudioHPChangePercent != 0)) {
        if (gAudioHPChangePercent >= 0x29) {
            Audio_QueueSoundAvoidingRecent(gAudioCueTable_ItemUse);
            Audio_PlayCommand(0x16, gAudioEffectId, 0);
        } else if (gAudioHPChangePercent >= 6) {
            if ((gAudioInfoPtr[0]->unk_0C > 0) && (gAudioInfoPtr[1]->unk_0C > 0)) {
                Audio_QueueSoundAvoidingRecent(gAudioCueTable_ItemConsume);
            } else {
                Audio_QueueSoundAvoidingRecent(gAnnouncerCueMultiHitLowHp);
            }
        } else if ((gAudioInfoPtr[0]->unk_0C > 0) && (gAudioInfoPtr[1]->unk_0C > 0)) {
            Audio_QueueSoundAvoidingRecent(gAudioCueTable_ItemEquip);
        } else {
            Audio_QueueSoundAvoidingRecent(gAnnouncerCueLightHitLowHp);
        }
    }
}

void HandleMoveEvent(PokemonAudioInfo* arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 i;
    s32 sp40;
    u32 temp_lo;
    u32 temp_v0;
    s32 sp34;
    u32 tmp;
    OSIntMask sp2C;

    if (arg0 == NULL) {
        return;
    }

    if (arg0 == gAudioInfoPtr[0]) {
        sp40 = 0;
    } else if (arg0 == gAudioInfoPtr[1]) {
        sp40 = 1;
    } else {
        return;
    }

    if ((gAudioInfoPtr[0] == NULL) || (gAudioInfoPtr[1] == NULL)) {
        return;
    }

    gAudioCurrentMoveId = arg1;

    switch (arg3) {
        case 1:
            gAudioMoveDamageReactionDone = 0;
            Audio_RemoveLastQueuedSequenceId();
            sp40 ^= 1;

            if (gAudioInfoPtr[sp40]->unk_0C != 0) {
                for (i = 0; i < 5; i++) {
                    // FAKE
                    if (arg2) {}
                    if (arg1 == AudioCommandMap[i].posX) {
                        if (gAudioInfoPtr[sp40]->unk_0C < gHPHistory[sp40].posX[gHPHistory[sp40].unk_24 & 0xF]) {
                            tmp = (gHPHistory[sp40].posX[gHPHistory[sp40].unk_24 & 0xF] - gAudioInfoPtr[sp40]->unk_0C);
                            gAudioHPChangePercent = (tmp * 0x64) / gAudioInfoPtr[sp40]->unk_28;
                        } else {
                            gAudioHPChangePercent = 0;
                        }
                        gAudioCurrentCommandId = arg2;
                        return;
                    }

                    if (arg1 == AudioCommandMap[i].TrainerSlotSaveData_GamePort) {
                        if (gAudioInfoPtr[sp40]->unk_0C < gHPHistory[sp40].posX[gHPHistory[sp40].unk_24 & 0xF]) {
                            tmp = gHPHistory[sp40].posX[gHPHistory[sp40].unk_24 & 0xF] - gAudioInfoPtr[sp40]->unk_0C;
                            gAudioHPChangePercent = (tmp * 0x64) / gAudioInfoPtr[sp40]->unk_28;
                        } else {
                            gAudioHPChangePercent = 0;
                        }
                        gAudioCurrentCommandId = arg2;
                        return;
                    }
                }
            }

            temp_v0 = osSetIntMask(sp2C);

            gAudioQueueDelayCounter = 0x1E;
            if (gAudioInfoPtr[sp40]->unk_0C < gHPHistory[sp40].posX[gHPHistory[sp40].unk_24 & 0xF]) {
                tmp = gHPHistory[sp40].posX[gHPHistory[sp40].unk_24 & 0xF] - gAudioInfoPtr[sp40]->unk_0C;
                gAudioHPChangePercent = (tmp * 0x64) / gAudioInfoPtr[sp40]->unk_28;
            } else {
                gAudioHPChangePercent = 0;
            }
            gAudioCurrentCommandId = arg2;

            osSetIntMask(temp_v0);

            if (gAudioHPChangePercent >= 0x29) {
                Audio_PlayCommand(0x16, gAudioEffectId, 0);
            }
            break;

        case 0:
        case 2:
            Audio_RemoveLastQueuedSequenceId();
            gAudioEffectStateParalysisCount[sp40] = 0;
            gAudioEffectStateCantMoveCount[sp40] = 0;

            if (arg1 != 0x13) {
                gAudioEffectMapPRepeatCount[sp40] = 0;
            }

            if (arg1 != 0x5B) {
                gAudioEffectMapQRepeatCount[sp40] = 0;
            }

            if (arg3 != 2) {
                gAudioEffectMissCrashPlayed[sp40] = 0;
            }

            gAudioSpecialCounter += 1;

            for (i = 0; i < 17; i++) {
                if (arg1 == AudioEffectTriggerIds[i]) {
                    goto loop1_end;
                }
            }

            gAudioEffectMapJRepeatCount[sp40] = 0;
        loop1_end:

            for (i = 0; i < 9; i++) {
                if (arg1 == AudioEffectSecondaryIds[i]) {
                    goto loop2_end;
                }
            }

            gAudioEffectMapKEscalationCount[sp40] = 0;
        loop2_end:

            gAudioQueueDelayCounter = 0;
            if (gAudioMoveDamageReactionDone == 0) {
                tmp = Battle_EstimateMoveDamage(arg1, gAudioInfoPtr[sp40], gAudioInfoPtr[sp40 ^ 1]);

                if (tmp == -1) {
                    if (BitArray_IsBitSet(gAudioEffectTriggeredMask, arg1 - 1) == 0) {
                        sp34 = arg1 + 0x1A2;
                        BitArray_SetBit(gAudioEffectTriggeredMask, arg1 - 1, 1);
                        Audio_QueueSequenceId(sp34);
                    } else {
                        Audio_QueueSoundAvoidingRecent(gAnnouncerCueOneHitKo);
                    }
                } else if (tmp == -2) {
                    if (BitArray_IsBitSet(gAudioEffectTriggeredMask, arg1 - 1) == 0) {
                        sp34 = arg1 + 0x1A2;
                        BitArray_SetBit(gAudioEffectTriggeredMask, arg1 - 1, 1);
                        Audio_QueueSequenceId(sp34);
                    } else {
                        Audio_QueueSoundAvoidingRecent(gAnnouncerCueOneHitKoRepeat);
                    }
                } else if (tmp == -3) {
                    gAudioEstimateMinus3Latched = 1;
                    if (BitArray_IsBitSet(gAudioEffectTriggeredMask, arg1 - 1) == 0) {
                        sp34 = arg1 + 0x1A2;
                        BitArray_SetBit(gAudioEffectTriggeredMask, arg1 - 1, 1);
                        Audio_QueueSequenceId(sp34);
                    } else {
                        Audio_QueueSequenceId(0x187);
                    }
                } else if (tmp == -4) {
                    if (BitArray_IsBitSet(gAudioEffectTriggeredMask, arg1 - 1) == 0) {
                        sp34 = arg1 + 0x1A2;
                        BitArray_SetBit(gAudioEffectTriggeredMask, arg1 - 1, 1);
                        Audio_QueueSequenceId(sp34);
                    } else {
                        Audio_QueueSoundAvoidingRecent(gAnnouncerCueLightDamage);
                    }
                } else if (tmp != -5) {
                    if ((gHPHistory[sp40 ^ 1].posX[gHPHistory[sp40 ^ 1].unk_24 & 0xF] < tmp) && (gAudioAttackContinuesActive == 0)) {
                        if (BitArray_IsBitSet(gAudioEffectTriggeredMask, arg1 - 1) == 0) {
                            sp34 = arg1 + 0x1A2;
                            BitArray_SetBit(gAudioEffectTriggeredMask, arg1 - 1, 1);
                            Audio_QueueSequenceId(sp34);
                        } else {
                            Audio_QueueSoundAvoidingRecent(gAnnouncerCueKnockoutBlow);
                            gAudioAttackContinuesActive = 0;
                        }
                    } else {
                        gAudioAttackContinuesActive = 0;
                        temp_lo = (tmp * 0x64) / gAudioInfoPtr[sp40 ^ 1]->unk_28;
                        if (temp_lo >= 0x51) {
                            if (gAudioSpecialFlag0 == 0) {
                                gAudioSpecialFlag0 = 1;
                                Audio_QueueSoundAvoidingRecent(gAnnouncerCueOneHitKo);
                            } else {
                                Audio_QueueSoundAvoidingRecent(gAnnouncerCueOneHitKoRepeat);
                            }
                        } else if (temp_lo >= 0x33) {
                            if (gAudioQueueMode == 1) {
                                Audio_QueueSoundAvoidingRecent(gAnnouncerCueHeavyDamageFirstTurn);
                            } else {
                                Audio_QueueSoundAvoidingRecent(gAnnouncerCueHeavyDamage);
                            }
                        } else if (AudioStream_IsPlaying(1) == 0) {
                            if (gAudioQueueMode == 1) {
                                if (gAudioSpecialCounter == 2) {
                                    Audio_QueueSoundAvoidingRecent(gAnnouncerCueLightDamageFirstTurnAlt);
                                } else {
                                    Audio_QueueSoundAvoidingRecent(gAnnouncerCueLightDamageFirstTurn);
                                }
                            } else {
                                Audio_QueueSoundAvoidingRecent(gAnnouncerCueLightDamage);
                            }
                        }
                    }
                }
            }
            break;

        case 3:
            if (gAudioMoveDamageReactionDone == 0) {
                gAudioMoveDamageReactionDone = 1;
                gAudioQueueDelayCounter = 0;
                tmp = Battle_EstimateMoveDamage(arg1, gAudioInfoPtr[sp40], gAudioInfoPtr[sp40 ^ 1]);
                if ((tmp >> 0x10) == 0) {
                    tmp = tmp << 1;

                    if (gHPHistory[sp40 ^ 1].posX[gHPHistory[sp40 ^ 1].unk_24 & 0xF] < tmp) {
                        if (BitArray_IsBitSet(gAudioEffectTriggeredMask, arg1 - 1) == 0) {
                            sp34 = arg1 + 0x1A2;
                            BitArray_SetBit(gAudioEffectTriggeredMask, arg1 - 1, 1);
                            Audio_QueueSequenceId(sp34);
                        } else {
                            Audio_QueueSoundAvoidingRecent(gAnnouncerCueKnockoutBlow);
                        }
                    } else {
                        temp_lo = (tmp * 0x64u) / gAudioInfoPtr[sp40 ^ 1]->unk_28;
                        if (temp_lo >= 0x51) {
                            if (gAudioSpecialFlag0 == 0) {
                                gAudioSpecialFlag0 = 1;
                                Audio_QueueSoundAvoidingRecent(gAnnouncerCueOneHitKo);
                            } else {
                                Audio_QueueSoundAvoidingRecent(gAnnouncerCueOneHitKoRepeat);
                            }
                        } else if (temp_lo >= 0x33) {
                            if (gAudioQueueMode == 1) {
                                Audio_QueueSoundAvoidingRecent(gAnnouncerCueHeavyDamageFirstTurn);
                            } else {
                                Audio_QueueSoundAvoidingRecent(gAnnouncerCueHeavyDamage);
                            }
                        } else if (AudioStream_IsPlaying(1) == 0) {
                            if (gAudioQueueMode == 1) {
                                if (gAudioSpecialCounter == 2) {
                                    Audio_QueueSoundAvoidingRecent(gAnnouncerCueLightDamageFirstTurnAlt);
                                } else {
                                    Audio_QueueSoundAvoidingRecent(gAnnouncerCueLightDamageFirstTurn);
                                }
                            } else {
                                Audio_QueueSoundAvoidingRecent(gAnnouncerCueLightDamage);
                            }
                        }
                    }
                }
            }
            break;

        case 4:
            gAudioSpecialCounter += 1;
            gAudioMoveDamageReactionDone = 0;
            gAudioQueueDelayCounter = 0;
            break;

        case 5:
            gAudioMoveDamageReactionDone = 0;
            gAudioQueueDelayCounter = 0;
            break;

        default:
            gAudioMoveDamageReactionDone = 0;
            gAudioQueueDelayCounter = 0;
            break;
    }
}

void QueuePlayerDefeatMessage(s32 arg0) {
    u8 temp_v0;

    if (arg0 == 0 || arg0 >= 5U) {
        return;
    }
    arg0--;
    temp_v0 = gPlayerSideMap[arg0];
    if (temp_v0 <= 0 || temp_v0 >= 3) {
        return;
    }
    temp_v0--;
    if (gAudioEffectStateDefeatMsgPlayed[temp_v0] == 0) {
        Audio_QueueSequenceId(0x190);
        gAudioEffectStateDefeatMsgPlayed[temp_v0] = 1;
    } else {
        Audio_QueueSequenceId(0x191);   
    }
}

void Audio_StartBattleMusicSequence(void) {
    if (gStadiumModeActive == 0) {
        Audio_StartMusicTrack(0x3D);
        Audio_PlayCommand(0x16, gAudioEffectId, 0);
        if (gCurrentStadiumPhase == 0xC) {
            if (!(gStadiumPhaseSubstate & 3) && (*gPlayerActiveFlag != 0)) {
                Audio_QueueSequenceId(0xCA);
                return;
            }
            Audio_QueueSequenceId(0xC8);
            return;
        }
        if (gCurrentStadiumPhase == 0xD) {
            if ((gStadiumPhaseSubstate == 4) && (*gPlayerActiveFlag != 0)) {
                Audio_QueueSequenceId(0xCA);
                return;
            }
            if ((gStadiumPhaseSubstate == 5) && (*gPlayerActiveFlag != 0)) {
                Audio_QueueSequenceId(0xCB);
                return;
            }
            Audio_QueueSequenceId(0xC8);
            return;
        }
        if ((gStadiumPhaseSubstate == 8) && (*gPlayerActiveFlag != 0)) {
            Audio_QueueSequenceId(0xC9);
            return;
        }
        Audio_QueueSequenceId(0xC8);
    }
}

void Audio_StartResultMusicSequence(void) {
    Audio_PlayCommand(0x16, gAudioEffectId, 0);
    Audio_QueueSequenceId(0x1A2);
}

void Audio_UpdateBattleAudioFrame(void) {
    u8* seq;

    if ((gAudioSeqTimer < gAudioSeqIndex) && (gAudioActiveFlag != 0) && (AudioStream_IsPlaying(1) == 0)) {
        if (gAudioSeqQueue[gAudioSeqTimer & 3] != 0) {
            seq = gAudioSeqData->seqArray[gAudioSeqQueue[gAudioSeqTimer & 3] - 1].offset;
            AudioStream_Start(1, seq, 0x7E, 0);
        }
        gAudioSeqTimer++;
    }

    if (gAudioSeqActiveFlag != 0) {
        if ((gAudioSeqElapsed >= 0x3E9) && (gAudioSeqState == 0) && (gAudioQueueMode != 0)) {
            Audio_QueueSequenceId(0x248);
            gAudioSeqState = 1;
        } else if ((gAudioSeqElapsed >= 0x7D1) && (gAudioSeqState == 0) && (gAudioQueueMode == 0)) {
            Audio_QueueSequenceId(0x248);
            gAudioSeqState = 1;
            gAudioSeqElapsed = 0x3E8;
        } else if ((gAudioSeqElapsed >= 0x641) && (gAudioSeqState == 1)) {
            Audio_QueueSequenceId(0x249);
            if (gAudioSeqPlayedFlag == 0) {
                Audio_PlayCommand(0x5B, gAudioEffectId, 0);
                gAudioSeqPlayedFlag = 1;
            }
            gAudioSeqState = 2;
        } else if ((gAudioSeqElapsed >= 0x899) && (gAudioSeqState == 2)) {
            Audio_QueueSequenceId(0x24A);
            gAudioSeqElapsed = 0x3E8;
            gAudioSeqState = 1;
        }

        gAudioSeqElapsed++;
    }

    if (gAudioQueueDelayCounter != 0) {
        if (gAudioQueueDelayCounter == 1) {
            if (gAudioHPChangePercent != 0) {
                if (gAudioHPChangePercent >= 0x29) {
                    if (((gAudioCurrentCommandId == 0x10) || (gAudioCurrentCommandId == 0x11) || (gAudioCurrentCommandId == 0x12) || (gAudioCurrentCommandId == 0x15) ||
                         (gAudioCurrentCommandId == 0x16) || (gAudioCurrentCommandId == 0x53) || (gAudioCurrentCommandId == 0x54) ||
                         (gAudioCurrentCommandId == 0x55)) &&
                        ((gAudioCurrentMoveId == 0x34) || (gAudioCurrentMoveId == 0x35) || (gAudioCurrentMoveId == 0x7E))) {
                        Audio_QueueSoundAvoidingRecent(gAudioCueTable_ItemUseAlt);
                    } else {
                        Audio_QueueSoundAvoidingRecent(gAudioCueTable_ItemUse);
                    }
                } else if (gAudioHPChangePercent >= 6) {
                    if ((gAudioInfoPtr[0]->unk_0C > 0) && (gAudioInfoPtr[1]->unk_0C > 0)) {
                        Audio_QueueSoundAvoidingRecent(gAudioCueTable_ItemConsume);
                    } else {
                        Audio_QueueSoundAvoidingRecent(gAnnouncerCueMultiHitLowHp);
                    }
                } else if ((gAudioInfoPtr[0]->unk_0C > 0) && (gAudioInfoPtr[1]->unk_0C > 0)) {
                    Audio_QueueSoundAvoidingRecent(gAudioCueTable_ItemEquip);
                } else {
                    Audio_QueueSoundAvoidingRecent(gAnnouncerCueLightHitLowHp);
                }
            }
            gAudioPrevHPChangePercent = gAudioHPChangePercent;
        }
        gAudioQueueDelayCounter--;
    }
}

void ResetAudioState(void) {
    s32 i;
    s32 j;

    gAudioQueueMode = 0;
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 8; j++) {
            RecentMoveIDs[i][j] = 0;
        }
    }
    gRecentMoveCount[0] = 0;
    gRecentMoveCount[1] = 0;
    gAudioGlobalFlag0 = gAudioGlobalFlag1 = 0;
    gAudioQueueDelayCounter = 0;
    gAudioHPChangePercent = 0;
    gAudioCurrentMoveId = 0;
    gAudioLowHPWarningFlag = 0;
    gAudioSpecialFlag0 = 0;
    gAudioFaintedSidePlusOne = 0;
    gAudioQueueProcessingFlag = 0;
    gAudioPendingFreezeReaction = 0;
    gAudioPendingSleepReaction = 0;
    gAudioPendingDefeatReaction = 0;
    gAudioMoveDamageReactionDone = 0;
    gAudioAttackContinuesActive = 0;
    gAudioClimaxMusicPlayed = 0;
    gAudioRecentHeavyHitFlag = 0;
    gAudioQueueSpecialFlag = 0;
    gAudioSfxParam0 = 0;
    gAudioSfxParam1 = 0;
    gAudioSfxParam2 = 0;
    for (i = 0; i < 0x15; i++) {
        gAudioEffectTriggeredMask[i] = 0;
    }
    for (i = 0; i < 20; i++) {
        gAudioRecentMessages[i] = 0;
    }
    for (i = 0; i < 2; i++) {
        gAudioEffectState0[i] = 0;
        gAudioEffectStateDominanceCount[i] = 0;
        gAudioEffectStateSleepCount[i] = 0;
        gAudioEffectStateFreezeCount[i] = 0;
        gAudioEffectStateParalysisCount[i] = 0;
        gAudioEffectStateCantMoveCount[i] = 0;
        gAudioEffectStateDefeatMsgPlayed[i] = 0;
        gAudioEffectStateHeavyDamageKo[i] = 0;
    }
}

void Audio_QueueSequenceId(u32 arg0) {
    OSIntMask mask;

    if ((gAudioActiveFlag != 0) && (gAudioSystemEnabled != 0) && (arg0 != 0)) {
        mask = osSetIntMask(OS_IM_NONE);
        gAudioSeqQueue[gAudioSeqIndex & 3] = arg0;
        gAudioSeqIndex++;
        osSetIntMask(mask);
    }
}

void Audio_RemoveLastQueuedSequenceId(void) {
    OSIntMask mask;

    if ((gAudioActiveFlag != 0) && (gAudioSystemEnabled != 0)) {
        mask = osSetIntMask(OS_IM_NONE);
        gAudioSeqQueue[(gAudioSeqIndex - 1) & 3] = 0;
        osSetIntMask(mask);
    }
}

void Audio_SwapSoundCandidates(u8* arg0, u8* arg1) {
    u8 temp_v0 = *arg0;
    u8 temp_v1 = *arg1;

    if (temp_v1 != temp_v0) {
        *arg0 = temp_v1;
        *arg1 = temp_v0;
    }
}

u16 Audio_FilterRecentSoundId(u16 arg0) {
    s32 i;

    for (i = 0; i < 20; i++) {
        if (arg0 == gAudioRecentMessages[i]) {
            return 0;
        }
    }

    return arg0;
}

void Audio_RecordRecentSoundId(u16 arg0) {
    u16 i;

    for (i = 0; i < 19; i++) {
        gAudioRecentMessages[i] = gAudioRecentMessages[i + 1];
    }

    gAudioRecentMessages[19] = arg0;
}

void Audio_RemoveRecentSoundAt(u16 arg0) {
    u32 i;

    for (i = arg0; i > 0; i--) {
        gAudioRecentMessages[i] = gAudioRecentMessages[i - 1];
    }

    gAudioRecentMessages[0] = 0;
}

u32 Audio_SelectSoundAvoidingRecent(u16* arg0) {
    u16 temp_v0 = *arg0;
    u32 i;
    u32 j;
    u16 sp5A;

    for (i = 0; i < temp_v0; i++) {
        gAudioShuffleBuffer[i] = i + 1;
    }

    for (i = 0; i < temp_v0 << 1; i++) {
        Audio_SwapSoundCandidates(gAudioShuffleBuffer, gAudioShuffleBuffer + (osGetTime() % (s32)temp_v0));
    }

    for (i = 0; i < temp_v0; i++) {
        sp5A = Audio_FilterRecentSoundId(arg0[gAudioShuffleBuffer[i]]);
        if (sp5A != 0) {
            Audio_RecordRecentSoundId(sp5A);
            return sp5A;
        }
    }

    for (i = 0; i < 20; i++) {
        for (j = 1; j <= temp_v0; j++) {
            if (gAudioRecentMessages[i] == arg0[j]) {
                Audio_RemoveRecentSoundAt(i);
                Audio_RecordRecentSoundId(arg0[j]);
                return arg0[j];
            }
        }
    }

    return 0;
}

void Audio_QueueSoundAvoidingRecent(u16* arg0) {
    u32 temp_v0 = Audio_SelectSoundAvoidingRecent(arg0);

    if (temp_v0 != 0) {
        Audio_QueueSequenceId(temp_v0);
    }
}

void Audio_QueueSoundWithFallbackList(u16 arg0, u16* arg1, u8* arg2) {
    u8 temp_v0;

    if (*arg2 == 0) {
        Audio_QueueSequenceId(arg0);
    } else {
        Audio_QueueSoundAvoidingRecent(arg1);
    }
    temp_v0 = *arg2;
    if (temp_v0 < 0xFF) {
        *arg2 = temp_v0 + 1;
    }
}

void func_800420F0_empty() {
    
}

u32 Battle_EstimateMoveDamage(u32 arg0, PokemonAudioInfo* arg1, PokemonAudioInfo* arg2) {
    u32 power;
    f32 atk;
    f32 def;
    f32 base;
    f32 dmg;
    f32 prevA;
    f32 hpA;
    f32 mulA;
    f32 prevB;
    f32 hpB;
    f32 mulB;
    u8 mode;
    f32 status;
    u8 conv1;
    u8 conv2;
    u8 conv0;
    u8 type;
    f32 eff2;
    f32 stab;
    u8* entry;
    u32 ret;
    s32 side;

    if ((arg0 == 0) || (arg0 >= 0xA6)) {
        arg0 = 1;
    }

    if (arg1 == gAudioInfoPtr[0]) {
        side = 0;
    } else if (arg1 == gAudioInfoPtr[1]) {
        side = 1;
    } else {
        return 0;
    }

    entry = &gAnnouncerMoveDataMoves1To68[(arg0 - 1) * 3];
    conv0 = Battle_MapCategoryIdToCompactIndex(entry[2]);
    type = entry[0];
    power = entry[1];

    switch (type) {
        case 0x26:
            return -1;

        case 0x28:
            return arg2->unk_28 / 2;

        case 0x29:
            switch (arg0) {
                case 0x31:
                    return 0x14;
                case 0x45:
                    return arg1->unk_26;
                case 0x52:
                    return 0x28;
                case 0x65:
                    return arg1->unk_26;
                case 0x95:
                    return (u32)arg1->unk_26 * 1.5f;
                default:
                    return 0;
            }

        case 0x7:
            return -3;

        case 0x9:
        case 0xA:
        case 0xB:
        case 0xD:
        case 0xF:
        case 0x18:
        case 0x19:
        case 0x1A:
        case 0x2E:
        case 0x2F:
        case 0x32:
        case 0x33:
        case 0x34:
        case 0x35:
        case 0x38:
        case 0x39:
        case 0x40:
        case 0x41:
        case 0x4F:
        case 0x52:
        case 0x53:
        case 0x55:
            return -5;

        case 0x12:
        case 0x13:
        case 0x14:
        case 0x16:
        case 0x20:
        case 0x31:
        case 0x3B:
        case 0x42:
        case 0x43:
        case 0x54:
        case 0x56:
            return -4;

        case 0x1C:
            if (gAnnouncerMoveDataMoves101To165 == &gAnnouncerMoveDataMoves1To68[arg0 * 3]) {
                return -5;
            }
            return -4;
    }

    if (gAnnouncerMoveDataMoves69To100 == &gAnnouncerMoveDataMoves1To68[arg0 * 3]) {
        return -2;
    }

    if (arg1->unk_2A != 0) {
        atk = (u32)arg1->unk_2A;
    } else {
        atk = 1.0f;
    }

    if (arg2->unk_2C != 0) {
        def = (u32)arg2->unk_2C;
    } else {
        def = 1.0f;
    }

    base = (f32)(((arg1->unk_26 * 2) / 5) + 2) * power * atk / def / 50.0f;

    conv1 = Battle_MapCategoryIdToCompactIndex(arg2->unk_16[6]);
    conv2 = Battle_MapCategoryIdToCompactIndex(arg2->unk_16[7]);

    mode = gAnnouncerTypeEffectivenessTable[conv0 * 15 + conv1];
    switch (mode) {
        case 1:
            mulB = 0.0f;
            break;
        case 2:
            mulB = 0.5f;
            break;
        case 3:
            mulB = 2.0f;
            break;
        default:
            mulB = 1.0f;
    }

    mode = gAnnouncerTypeEffectivenessTable[conv0 * 15 + conv2];
    switch (mode) {
        case 1:
            eff2 = 0.0f;
            break;
        case 2:
            eff2 = 0.5f;
            break;
        case 3:
            eff2 = 2.0f;
            break;
        default:
            eff2 = 1.0f;
    }

    if ((arg1->unk_16[6] == entry[2]) || (arg1->unk_16[7] == entry[2])) {
        stab = 1.5f;
    } else {
        stab = 1.0f;
    }

    dmg = base * mulB * eff2 * stab;

    prevA = (u32)gHPHistory[side ^ 1].posX[gHPHistory[side ^ 1].unk_24 & 0xF];
    if (prevA == 0) {
        prevA = 1;
    }
    hpA = (u32)arg2->unk_28;
    if (gPlayerActiveFlag[side ^ 1] == 1) {
        mulA = 1.1f;
    } else {
        mulA = 1.0f;
    }

    prevB = (u32)gHPHistory[side].posX[gHPHistory[side].unk_24 & 0xF];
    if (prevB == 0) {
        prevB = 1;
    }
    hpB = (u32)arg1->unk_28;
    if (gPlayerActiveFlag[side] == 1) {
        mulB = 1.1f;
    } else {
        mulB = 1.0f;
    }

    if (arg2->unk_15 & 0x20) {
        status = 1.2f;
    } else if (arg2->unk_15 & 7) {
        status = 1.1f;
    } else {
        status = 1.0f;
    }

    ret = (((hpA / prevA) * 0.01f) + 1) * dmg * (1 + ((hpB / prevB) * 0.01f)) * mulA * mulB * status;

    if (ret >= 0x8000) {
        ret = 0x7FFF;
    }
    return ret;
}

s32 Battle_MapCategoryIdToCompactIndex(u8 arg0) {
    switch (arg0) {
    case 0:
        return 0;
    case 20:
        return 1;
    case 21:
        return 2;
    case 23:
        return 3;
    case 22:
        return 4;
    case 25:
        return 5;
    case 1:
        return 6;
    case 3:
        return 7;
    case 4:
        return 8;
    case 2:
        return 9;
    case 24:
        return 0xA;
    case 7:
        return 0xB;
    case 5:
        return 0xC;
    case 8:
        return 0xD;
    case 26:
        return 0xE;
    default:
        return 0;
    }
}

void Audio_QueueSequenceIdWrapper(u32 arg0) {
    Audio_QueueSequenceId(arg0);
}
