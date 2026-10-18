#ifndef _3D140_H_
#define _3D140_H_

#include "global.h"

typedef struct unk_D_800FCB18_044 {
    /* 0x00 */ u8 unk_00;
    /* 0x01 */ u8 unk_01;
    /* 0x02 */ u8 unk_02;
    /* 0x03 */ u8 unk_03;
    /* 0x04 */ u8 unk_04;
    /* 0x05 */ u8 unk_05;
} unk_D_800FCB18_044; // size = 0x6

typedef struct unk_D_800FCB18 {
    /* 0x00 */ u8 unk_00;
    /* 0x01 */ u8 unk_01;
    /* 0x02 */ char unk02[0x2];
    /* 0x04 */ u8 unk_04;
    /* 0x05 */ u8 unk_05;
    /* 0x06 */ char unk06[0x5];
    /* 0x0B */ u8 unk_0B;
    /* 0x0C */ u16 unk_0C;
    /* 0x0E */ u16 unk_0E;
    /* 0x10 */ u16 unk_10;
    /* 0x12 */ u16 unk_12;
    /* 0x14 */ u8 unk_14;
    /* 0x15 */ u8 unk_15;
    /* 0x16 */ u8 unk_16[9];
    /* 0x1F */ u8 unk_1F[4];
    /* 0x23 */ char unk23[0x1];
    /* 0x24 */ u16 unk_24;
    /* 0x26 */ u8 unk_26;
    /* 0x28 */ u16 unk_28;
    /* 0x2A */ u16 unk_2A;
    /* 0x2C */ u16 unk_2C;
    /* 0x2E */ u16 unk_2E;
    /* 0x30 */ u16 unk_30;
    /* 0x32 */ u8 unk_32[4];
    /* 0x36 */ u16 unk_36;
    /* 0x38 */ u16 unk_38;
    /* 0x3A */ u16 unk_3A;
    /* 0x3C */ u16 unk_3C;
    /* 0x3E */ u16 unk_3E;
    /* 0x40 */ char unk40[0x4];
    /* 0x44 */ unk_D_800FCB18_044 unk_44;
    /* 0x4A */ u8 unk_4A;
    /* 0x4B */ u8 unk_4B;
    /* 0x4C */ u8 unk_4C;
    /* 0x4D */ u8 unk_4D;
    /* 0x4E */ u8 unk_4E;
    /* 0x4F */ u8 unk_4F;
    /* 0x50 */ u8 unk_50;
    /* 0x51 */ u8 unk_51;
    /* 0x52 */ u8 unk_52;
    /* 0x53 */ u8 unk_53;
    /* 0x54 */ u16 unk_54;
    /* 0x56 */ u8 unk_56;
    /* 0x57 */ u8 unk_57;
    /* 0x58 */ u8 unk_58;
    /* 0x59 */ u8 unk_59;
    /* 0x5A */ u8 unk_5A;
    /* 0x5B */ u8 unk_5B;
    /* 0x5C */ u8 unk_5C[6];
    /* 0x62 */ char unk62[0x2];
} unk_D_800FCB18; // size = 0x64

typedef struct amConfig {
    /* 0x00 */ u32 outputRate;
    /* 0x04 */ u32 framesPerField;
    /* 0x08 */ u32 maxACMDSize;
} amConfig; // size = 0xC

extern s32 mus_active_fade_handle;
extern f32 mus_fade_start_volume;
extern u8 mus_fade_target_volume;
extern f32 mus_fade_step_rate;
extern f32 gMusicChannel2Volume;
extern f32 gMusicChannel2Step;
extern f32 gMusicChannel1Volume;
extern f32 gMusicChannel1Step;
extern u8 mus_sound_effect_blocked;

extern unk_D_800FCB18* gAudioInfoPtr[4];

void amCreateAudioMgr(ALSynConfig*, amConfig*, u32, s32, s32);
OSTask* AudioTask_Build(OSTask*);
void __clearAudioDMA(void);
void Audio_StartMusicFade(s32);
void Audio_MusicFadeUpdate(void);
s32 Audio_IsMusicEnabled(void);
s32 Audio_SetPauseState(s32);
void SetAudioActiveFlag(s32);
void SetTeamScores(u8, u8, u8, u8);
void SetPlayerSidesAndReset(u8, u8, u8, u8);
void ProcessMenuSelection(u32 arg0, u32 arg1);
void AudioFrameUpdate(s32 arg0);
void ProcessAudioInfo(s32, unk_D_800FCB18*);
void RemovePlayer(u32);
void PlayerDefeated(u32);
void ProcessCommandQueue(u32 arg0);
void ProcessAudioCommandQueue(s32);
void HandleMoveEvent(unk_D_800FCB18* arg0, s32 arg1, s32 arg2, s32 arg3);
void QueuePlayerDefeatMessage(s32);
void HandleStadiumModeAudio(void);
void QueueEndTurnSound(void);
void Audio_UpdateEffects(void);
void ResetAudioState(void);
void AudioQueueRemoveLast(void);
void AudioQueueAdd(u32 arg0);
void SwapU8(u8* arg0, u8* arg1);
u16 IsMessageInRecentList(u16 arg0);
void AddMessageToRecent(u16 arg0);
void ShiftRecentMessages(u16 arg0);
u32 ShuffleIndices(u16* arg0);
void AudioPlayCueTable(u16* arg0);

#endif // _3D140_H_
