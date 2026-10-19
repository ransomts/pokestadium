#include "src/gsm_decoder.h"

typedef struct AnimHeader {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    s16 unk6;
    s16 unk8;
    s16 unkA;
    s16 unkC;
    s16 unkE;
} AnimHeader; // size 0x10

typedef struct AnimPackedData {
    u8 unk0;
    u8 unk1;
    u8 unk2;
    u8 unk3;
    u8 unk4;
    u8 unk5;
    u8 unk6;
} AnimPackedData; // size 0x7

typedef struct AnimBlock19 {
    s16 xRotA;
    s16 xRotB;
    s16 flag0;
    s16 yRotA;
    s16 yRotB;
    s16 flag1;
    s16 zRotA;
    s16 zRotB;
    s16 flag2;
    s16 unkA;
    s16 unkB;
    s16 unkC;
    s16 unkD;
} AnimBlock19; // size 0x1A

typedef struct AnimProcessor {
    char pad0[0x168];
    AnimHeader unk168[2];
    s16 unk188;       // 0x188
} AnimProcessor;

void Decoding_of_the_coded_Log_Area_Ratios(AnimProcessor* arg0, AnimHeader* arg1, s32 arg2, s32 arg3) {
    AnimHeader* temp_v0_2;

    temp_v0_2 = &arg0->unk168[arg0->unk188];
    temp_v0_2->unk0 = (s16) (((s32) ((((arg1->unk0 - 0x20) << 0xA) * 0x3333) + 0x4000) >> 0xF) * 2);
    temp_v0_2->unk2 = (s16) (((s32) ((((arg1->unk2 - 0x20) << 0xA) * 0x3333) + 0x4000) >> 0xF) * 2);
    temp_v0_2->unk4 = (s16) (((s32) ((((arg1->unk4 - 0x10) << 0xA) * 0x3333) - 0x0332F000) >> 0xF) * 2);
    temp_v0_2->unk6 = (s16) (((s32) ((((arg1->unk6 - 0x10) << 0xA) * 0x3333) + 0x04003C00) >> 0xF) * 2);
    temp_v0_2->unk8 = (s16) (((s32) ((((arg1->unk8 - 8) << 0xA) * 0x4B17) - 0x0036E4E4) >> 0xF) * 2);
    temp_v0_2->unkA = (s16) (((s32) ((((arg1->unkA - 8) << 0xA) * 0x4444) + 0x03BBF800) >> 0xF) * 2);
    temp_v0_2->unkC = (s16) (((s32) ((((arg1->unkC - 4) << 0xA) * 0x7ADE) + 0x0147936C) >> 0xF) * 2);
    temp_v0_2->unkE = (s16) (((s32) ((((arg1->unkE - 4) << 0xA) * 0x740C) + 0x040D6B40) >> 0xF) * 2);

    Gsm_Short_Term_Synthesis_Filter((s32)arg0, arg2, arg3);
    arg0->unk188 ^= 1;
}

void Gsm_Decoder(AnimProcessor* arg0, AnimHeader* arg1, s16* arg2, s16* arg3, s16* arg4, s16* arg5, AnimBlock19* arg6, s32 arg7) {
    s32 i;
    s16 sp44[40];
    
    for (i = 0; i < 4; i++) {
        Gsm_RPE_Decoding(*arg5, *arg4, arg6, sp44);
        Gsm_Long_term_synthesis_filtering(arg0, *arg2, *arg3, sp44);
        arg5++;
        arg3++;
        arg2++;
        arg4++;
        arg6++;
    }


    Decoding_of_the_coded_Log_Area_Ratios(arg0, arg1, arg0, arg7);
}

s32 Gsm_Decode(AnimProcessor* arg0, AnimPackedData* arg1, s32 arg2) {
    AnimHeader header;
    s16 spC8[4];
    s16 spC0[4];
    s16 spB8[4];
    s16 spB0[4];
    AnimBlock19 sp48[4];
    s32 i;

    header.unk0 = ((arg1[0].unk0 & 0xF) << 2) | ((arg1[0].unk1 >> 6) & 3);
    header.unk2 = arg1[0].unk1 & 0x3F;
    header.unk4 = (arg1[0].unk2 >> 3) & 0x1F;
    header.unk6 = ((arg1[0].unk2 & 7) << 2) | ((arg1[0].unk3 >> 6) & 3);
    header.unk8 = (arg1[0].unk3 >> 2) & 0xF;
    header.unkA = ((arg1[0].unk3 & 3) << 2) | ((arg1[0].unk4 >> 6) & 3);
    header.unkC = (arg1[0].unk4 >> 3) & 7;
    header.unkE = arg1[0].unk4 & 7;
    for (i = 0; i < 4; i++)  {
        spC8[i] = (arg1[i].unk5 >> 1) & 0x7F;
        spB8[i] = ((arg1[i].unk5 & 1) << 1) | ((arg1[i].unk6 >> 7) & 1);
        spC0[i] = (arg1[i].unk6 >> 5) & 3;
        spB0[i] = ((arg1[i].unk6 & 0x1F) << 1) | ((arg1[i + 1].unk0 >> 7) & 1);

        sp48[i].xRotA = (arg1[i + 1].unk0 >> 4) & 7;
        sp48[i].xRotB = (arg1[i + 1].unk0 >> 1) & 7;
        sp48[i].flag0 = ((arg1[i + 1].unk0 & 1) << 2) | ((arg1[i + 1].unk1 >> 6) & 3);
        sp48[i].yRotA = (arg1[i + 1].unk1 >> 3) & 7;
        sp48[i].yRotB = arg1[i + 1].unk1 & 7;
        sp48[i].flag1 = (arg1[i + 1].unk2 >> 5) & 7;
        sp48[i].zRotA = (arg1[i + 1].unk2 >> 2) & 7;
        sp48[i].zRotB = ((arg1[i + 1].unk2 & 3) << 1) | ((arg1[i + 1].unk3 >> 7) & 1);
        sp48[i].flag2 = (arg1[i + 1].unk3 >> 4) & 7;
        sp48[i].unkA = (arg1[i + 1].unk3 >> 1) & 7;
        sp48[i].unkB = ((arg1[i + 1].unk3 & 1) << 2) | ((arg1[i + 1].unk4 >> 6) & 3);
        sp48[i].unkC = (arg1[i + 1].unk4 >> 3) & 7;
        sp48[i].unkD = arg1[i + 1].unk4 & 7;
    }
    Gsm_Decoder(arg0, &header, spC8, spB8, spC0, spB0, sp48, arg2);
    return 0;
}

/*
 * Read n bits (LSB first) from the 0x400-word ring buffer at arg0->bitstreamRingBuffer.
 * bits = current word shifted down, left = bits remaining in it, pos = bit
 * position of the current word (low 5 bits are stale once a refill happened).
 */
#define READ_BITS(dst, n)                                         \
    if (left > (n)) {                                             \
        dst = bits & ((1 << (n)) - 1);                            \
        bits >>= (n);                                             \
        left -= (n);                                              \
    } else {                                                      \
        dst = bits & ((1 << left) - 1);                           \
        pos += 32;                                                \
        bits = ((u32*)arg0->bitstreamRingBuffer)[(pos >> 5) & 0x3FF];        \
        if (left != (n)) {                                        \
            dst |= (bits & ((1 << ((n) - left)) - 1)) << left;    \
        }                                                         \
        bits >>= (n) - left;                                      \
        left += 32 - (n);                                         \
    }

// Speech/voice frame decoder: called once per 160-sample (0x140-byte) output
// frame by AudioStream_RefillAndDecode (src/45720.c). Bitstream layout:
//  - if no run is active: 1 bit; 1 => silence run of (4 bits + 1) frames
//    (unk_18C), 0 => voiced run of (7 bits + 1) frames (unk_18A).
//  - silence frame: zero the output buffer.
//  - voiced frame: 8 header fields (6,6,5,5,4,4,3,3 bits) then 4 subframes of
//    (7,2,2,6 bits + 13 x 3 bits), same layout Gsm_Decode unpacks from
//    bytes, then synthesised by Gsm_Decoder.
// The stored position is (word-aligned pos) + (32 - left).
s32 Gsm_Decode_Stream(GbAudioChannelState* arg0, void* arg1) {
    AnimHeader header;
    s16 spE0[4];
    s16 spD8[4];
    s16 spD0[4];
    s16 spC8[4];
    AnimBlock19 sp60[4];
    s32 i;
    s32 left;
    u32 bits;
    s32 pos;
    UNUSED s32 pad[2]; // matches the frame; probably two locals removed from the original

    pos = arg0->bitReadPosition;
    bits = ((u32*)arg0->bitstreamRingBuffer)[(pos >> 5) & 0x3FF] >> (pos & 0x1F);
    left = 32 - (pos & 0x1F);

    if ((arg0->unk_0000.voicedFramesRemaining == 0) && (arg0->unk_0000.unk_18C == 0)) {
        READ_BITS(i, 1);
        if (i) {
            READ_BITS(arg0->unk_0000.unk_18C, 4);
            arg0->unk_0000.unk_18C++;
        } else {
            READ_BITS(arg0->unk_0000.voicedFramesRemaining, 7);
            arg0->unk_0000.voicedFramesRemaining++;
        }
    }

    if (arg0->unk_0000.unk_18C != 0) {
        bzero(arg1, 0x140);
        arg0->unk_0000.unk_18C--;
    } else {
        READ_BITS(header.unk0, 6);
        READ_BITS(header.unk2, 6);
        READ_BITS(header.unk4, 5);
        READ_BITS(header.unk6, 5);
        READ_BITS(header.unk8, 4);
        READ_BITS(header.unkA, 4);
        READ_BITS(header.unkC, 3);
        READ_BITS(header.unkE, 3);
        for (i = 0; i < 4; i++) {
            READ_BITS(spE0[i], 7);
            READ_BITS(spD0[i], 2);
            READ_BITS(spD8[i], 2);
            READ_BITS(spC8[i], 6);
            READ_BITS(sp60[i].xRotA, 3);
            READ_BITS(sp60[i].xRotB, 3);
            READ_BITS(sp60[i].flag0, 3);
            READ_BITS(sp60[i].yRotA, 3);
            READ_BITS(sp60[i].yRotB, 3);
            READ_BITS(sp60[i].flag1, 3);
            READ_BITS(sp60[i].zRotA, 3);
            READ_BITS(sp60[i].zRotB, 3);
            READ_BITS(sp60[i].flag2, 3);
            READ_BITS(sp60[i].unkA, 3);
            READ_BITS(sp60[i].unkB, 3);
            READ_BITS(sp60[i].unkC, 3);
            READ_BITS(sp60[i].unkD, 3);
        }
        arg0->unk_0000.voicedFramesRemaining--;
        Gsm_Decoder((AnimProcessor*)arg0, &header, spE0, spD0, spD8, spC8, sp60, (s32)arg1);
    }

    arg0->bitReadPosition = (pos & ~0x1F) - left + 32;
    return 0;
}
