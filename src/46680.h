#ifndef _46680_H_
#define _46680_H_

#include "global.h"

typedef struct unk_D_800FCED8_0000 {
    /* 0x000 */ char unk000[0x166];
    /* 0x166 */ s16 unk_166;
    /* 0x168 */ char unk168[0x22];
    /* 0x18A */ s16 unk_18A;
    /* 0x18C */ s16 unk_18C;
    /* 0x18E */ s16 unk18E;
} unk_D_800FCED8_0000; // size = 0x190

typedef struct unk_D_800FCED8_0198 {
    /* 0x000 */ char unk_0000[0x1400];
} unk_D_800FCED8_0198; // size = 0x1400

typedef struct unk_D_800FCED8_01598 {
    /* 0x00 */ char unk00[0x4];
    /* 0x04 */ u32 unk_04;
} unk_D_800FCED8_01598; // size = 0x8

typedef void (*unk_D_800FCED8_190)(s32, unk_D_800FCED8_01598*, s32, OSMesgQueue*);

typedef struct GbAudioChannelState {
    /* 0x0000 */ unk_D_800FCED8_0000 unk_0000;
    /* 0x0190 */ unk_D_800FCED8_190 dmaCallback;
    /* 0x0194 */ s32 sourceBaseAddress;
    /* 0x0198 */ unk_D_800FCED8_0198 pcmRingBuffer;
    /* 0x1598 */ unk_D_800FCED8_01598 bitstreamRingBuffer[1];
    /* 0x15A0 */ u32 inputWordCount;
    /* 0x15A4 */ char unk_15A4[0xFF4];
    /* 0x2598 */ u16 framesRemaining;
    /* 0x259A */ u16 unk_259A;
    /* 0x259C */ u32 inputWordsRemaining;
    /* 0x25A0 */ OSMesgQueue dmaQueue;
    /* 0x25B8 */ OSMesg dmaMessage;
    /* 0x25BC */ u32 bitReadPosition;
    /* 0x25C0 */ u32 bitstreamReadOffset;
    /* 0x25C4 */ u32 bitstreamWriteOffset;
    /* 0x25C8 */ s32 playbackSamplePosition;
    /* 0x25CC */ u32 decodedSamplePosition;
    /* 0x25D0 */ s8 dmaPending;
    /* 0x25D1 */ s8 streamState;
    /* 0x25D2 */ s8 decodeFrameLimit;
    /* 0x25D3 */ char unk25D3[0x5];
} GbAudioChannelState; // size = 0x25D8

s32 GbAudio_DecodeSpeechFrame(GbAudioChannelState*, void*);

#endif // _46680_H_
