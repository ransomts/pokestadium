#ifndef _45720_H_
#define _45720_H_

#include "global.h"
#include "src/46680.h"

typedef struct unk_D_800FCF28 {
    /* 0x000 */ s16 unk_000[0x8A0];
} unk_D_800FCF28; // size = 0x1140

extern unk_D_800FCF28* D_800FCF28[2];
extern u32 D_800FCF30[2];

void Audio_Init(ALHeap*, u32, u32);
void Audio_StartChannel(u32, u32, u32, u32);
void Audio_SetVolumeFade(u32, u32);
s32 Audio_IsChannelActive(u32);
void Audio_SetPaused(s32);
void Audio_ProcessChannels(void);
void Audio_DmaTransfer(u32 arg0, u32 arg1, u32 arg2, OSMesgQueue* arg3);
void AudioChannel_Init(unk_D_800FCED8*, s32, s32);
void AudioChannel_Update(unk_D_800FCED8*);
u32 AudioChannel_Consume(unk_D_800FCED8*, u32);
void AudioChannel_StartPlayback(unk_D_800FCED8*);
void AudioChannel_Stop(unk_D_800FCED8*);

#endif // _45720_H_
