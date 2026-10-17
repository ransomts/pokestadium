#include "45720.h"

u8 gAudioPaused = 0;

s32 gAudioTransferPending;
GbAudioChannelState* gAudioChannel[2];
s16* gAudioSampleData[2];
u32 gAudioChunkSizeLarge;
u32 gAudioChunkSizeSmall;
u8 gAudioChannelState[2];
s32 gAudioChannelDmaStart[2];
u32 gAudioChannelVolume[2];
s32 gAudioChannelTargetVolume[2];
s32 gAudioChannelLoopCount[2];
s32 pad_D_800FCF18;
s16 gAudioChannelVolumeFadeStep[2];
u8 gAudioChannelStopFlag[2];
OSPiHandle* D_800FCF24;
unk_D_800FCF28* gAudioChannelBuffer[2];
u32 gAudioChannelReadPos[2];
u32 gAudioChannelWritePos[2];
OSMesgQueue gAudioDmaQueue;
OSMesg gAudioDmaMsg;

void Audio_Init(ALHeap* arg0, u32 arg1, u32 arg2) {
    s32 i;

    gAudioChunkSizeLarge = arg1 >> 1;
    gAudioChunkSizeSmall = arg2 >> 1;

    for (i = 0; i < 2; i++) {
        gAudioChannel[i] = alHeapDBAlloc(NULL, 0, arg0, 1, sizeof(GbAudioChannelState));
        gAudioChannelBuffer[i] = alHeapDBAlloc(NULL, 0, arg0, sizeof(*gAudioChannelBuffer[0]) / 2, 2);

        gAudioSampleData[i] = (u32)gAudioChannel[i] + 0x198;
        gAudioChannelReadPos[i] = 0;
        gAudioChannelWritePos[i] = 0x400;
        gAudioChannelState[i] = 2;

        bzero(gAudioChannelBuffer[i], 0x1140);
        bzero(gAudioSampleData[i], 0x1400);

        AudioChannel_Init(gAudioChannel[i], 0, 0);
        gAudioChannelStopFlag[i] = 0;
    }

    D_800FCF24 = osCartRomInit();
    osCreateMesgQueue(&gAudioDmaQueue, &gAudioDmaMsg, 1);
    gAudioTransferPending = 0;
    gAudioPaused = 0;
}

void Audio_StartChannel(u32 arg0, u32 arg1, u32 arg2, u32 arg3) {
    u32 temp_a0;

    if ((arg0 < 2) && (gAudioPaused == 0)) {
        if (arg2 >= 0x81) {
            arg2 = 0x80;
        }
        temp_a0 = osSetIntMask(1);

        if (arg3 == 0) {
            gAudioChannelState[arg0] = 0;
        } else {
            gAudioChannelState[arg0] = 3;
        }

        gAudioChannelDmaStart[arg0] = arg1;
        gAudioChannelLoopCount[arg0] = arg3;
        gAudioChannelTargetVolume[arg0] = arg2;

        osSetIntMask(temp_a0);
    }
}

void Audio_SetVolumeFade(u32 arg0, u32 arg1) {
    u32 temp_a0;

    if (arg0 < 2) {
        if (arg1 != 0) {
            gAudioChannelVolumeFadeStep[arg0] = (f32)gAudioChannelVolume[arg0] / arg1;
        }
        temp_a0 = osSetIntMask(1);
        if (arg1 != 0) {
            gAudioChannelState[arg0] = 5;
        } else {
            gAudioChannelState[arg0] = 1;
        }
        osSetIntMask(temp_a0);
    }
}

s32 Audio_IsChannelActive(u32 arg0) {
    if (gAudioChannelState[arg0] == 2) {
        return 0;
    }
    return 1;
}

void Audio_SetPaused(s32 arg0) {
    if (arg0 != 0) {
        gAudioPaused = 0;
    } else {
        gAudioPaused = 1;
    }
}

void Audio_ProcessChannels(void) {
    u32 j;
    u32 var_s7;
    u32 temp_a2;
    u32 i;
    s16 temp;
    s32 temp_v0_9;
    UNUSED s32 pad;

    for (i = 0; i < 2; i++) {
        if (gAudioChannelState[i] == 2) {
            continue;
        }

        if (gAudioChannelReadPos[i] < gAudioChannelWritePos[i]) {
            if ((gAudioChannelWritePos[i] - gAudioChannelReadPos[i]) < gAudioChunkSizeSmall) {
                var_s7 = gAudioChunkSizeSmall;
            } else {
                var_s7 = gAudioChunkSizeLarge;
            }
        } else if ((0x8A0 - gAudioChunkSizeSmall) < (gAudioChannelReadPos[i] - gAudioChannelWritePos[i])) {
            var_s7 = gAudioChunkSizeSmall;
        } else {
            var_s7 = gAudioChunkSizeLarge;
        }

        AudioChannel_Update(gAudioChannel[i]);
        if ((u8) gAudioChannel[i]->unk_25D1 == 2) {
            osWritebackDCache(gAudioChannelBuffer[i], 0x1140);
            AudioChannel_StartPlayback(gAudioChannel[i]);
            gAudioTransferPending = 1;
            gAudioChannelStopFlag[i] = 0;
        } else {
            if ((gAudioChannelState[i] != 0) && (gAudioChannelState[i] != 3) && ((u8) gAudioChannel[i]->unk_25D1 == 4)) {
                if (gAudioChannelStopFlag[i] == 0) {
                    AudioChannel_Stop(gAudioChannel[i]);
                    gAudioChannelStopFlag[i] = 1;
                }
                gAudioTransferPending = 0;
                gAudioChannelState[i] = 2;
                bzero(gAudioSampleData[i], 0x1400);
                bzero(gAudioChannelBuffer[i], 0x1140);
            }
        }

        AudioChannel_Consume(gAudioChannel[i], var_s7);

        temp_a2 = gAudioChannel[i]->unk_25C8 - var_s7;
        for (j = 0; j < var_s7; j++) {
            temp = (gAudioSampleData[i][(temp_a2 + j) % 2560] * gAudioChannelVolume[i]) >> 7;
            gAudioChannelBuffer[i]->unk_000[(gAudioChannelWritePos[i] + (j << 1) + 1) % 2208] = temp;
            gAudioChannelBuffer[i]->unk_000[(gAudioChannelWritePos[i] + (j << 1)) % 2208] = temp;
        }

        gAudioChannelWritePos[i] += var_s7 * 2;
        gAudioChannelWritePos[i] %= 2208;
        osWritebackDCache(gAudioChannelBuffer[i], 0x1140);

        switch (gAudioChannelState[i]) {
            case 2:
            case 4:
                break;

            case 0:
                AudioChannel_Init(gAudioChannel[i], gAudioChannelDmaStart[i], Audio_DmaTransfer);
                gAudioChannelState[i] = 4;
                if (gAudioTransferPending != 0) {
                    gAudioTransferPending = 0;
                }
                gAudioChannelVolume[i] = gAudioChannelTargetVolume[i];
                break;

            case 1:
                AudioChannel_Stop(gAudioChannel[i]);
                bzero(gAudioSampleData[i], 0x1400);
                gAudioChannelStopFlag[i] = 1;
                break;

            case 3:
                gAudioChannelLoopCount[i]--;
                if (gAudioChannelLoopCount[i] == 0) {
                    gAudioChannelState[i] = 0;
                }
                break;

            case 5:
                temp_v0_9 = gAudioChannelVolume[i] - gAudioChannelVolumeFadeStep[i];
                if (temp_v0_9 <= 0) {
                    gAudioChannelVolume[i] = 0;
                    gAudioChannelState[i] = 1;
                } else {
                    gAudioChannelVolume[i] = temp_v0_9;
                }
                break;
        }
    }
}

void Audio_DmaTransfer(u32 arg0, u32 arg1, u32 arg2, OSMesgQueue* arg3) {
    OSIoMesg sp48;
    u32 var_s1;
    u32 var_s2;
    u32 var_s3;

    var_s2 = arg0;
    var_s3 = arg1;

    while (arg2) {
        if (arg2 >= 0x1001) {
            var_s1 = 0x1000;
        } else {
            var_s1 = arg2;
        }

        sp48.hdr.pri = 0;
        sp48.hdr.retQueue = &gAudioDmaQueue;
        sp48.dramAddr = var_s3;
        sp48.devAddr = var_s2;
        sp48.size = var_s1;

        osInvalDCache(arg1, arg2);
        osEPiStartDma(D_800FCF24, &sp48, 0);
        osRecvMesg(&gAudioDmaQueue, NULL, 1);

        arg2 -= var_s1;
        var_s2 += var_s1;
        var_s3 += var_s1;
    }

    osSendMesg(arg3, NULL, 1);
}

void AudioChannel_Init(GbAudioChannelState* arg0, s32 arg1, s32 arg2) {
    bzero(&arg0->unk_0000, sizeof(unk_D_800FCED8_0000));

    arg0->unk_0000.unk_166 = 0x28;
    arg0->unk_0190 = arg2;
    arg0->unk_0194 = arg1;

    osCreateMesgQueue(&arg0->unk_25A0, &arg0->unk_25B8, 1);

    if ((arg1 == 0) || (arg2 == 0)) {
        arg0->unk_25D1 = 0;
    } else {
        arg0->unk_25D1 = 1;
    }

    arg0->unk_25D0 = 0;
    arg0->unk_2598 = arg0->unk_259C = arg0->unk_259A = 0;
    arg0->unk_25BC = 0;
    arg0->unk_25C4 = 0;
    arg0->unk_25C0 = 0;
    arg0->unk_25CC = 0;
    arg0->unk_25C8 = 0;
    arg0->unk_25D2 = 2;
}

void AudioChannel_Update(GbAudioChannelState* arg0) {
    s32 var_a2;
    s32 var_s2;
    u32 var_v1;

    var_s2 = arg0->unk_25D2;

    if ((arg0->unk_25D0 != 0) && (osRecvMesg(&arg0->unk_25A0, NULL, 0) >= 0)) {
        if (arg0->unk_25C4 == 0) {
            arg0->unk_2598 = (arg0->unk_1598[0].unk_04 >> 0x10) & 0xFFFF;
            arg0->unk_259A = arg0->unk_1598[0].unk_04 & 0xFFFF;
            arg0->unk_259C = arg0->unk_15A0 & 0xFFFFFF;
            arg0->unk_25BC = 0x60;
        }

        arg0->unk_25C4 += 0x400;
        if (arg0->unk_259C >= 0x100) {
            arg0->unk_259C -= 0x100;
        } else {
            arg0->unk_259C = 0;
        }
        arg0->unk_25D0 = 0;
    }

    if ((arg0->unk_25D0 == 0) && ((arg0->unk_25D1 == 1) || (arg0->unk_25D1 == 2) || (arg0->unk_25D1 == 3))) {
        if ((arg0->unk_25C4 - arg0->unk_25C0) < 0xC01) {
            if (arg0->unk_25C4 == 0) {
                var_a2 = 0x400;
            } else if (arg0->unk_259C >= 0x101) {
                var_a2 = 0x400;
            } else {
                var_a2 = arg0->unk_259C * 4;
            }

            if (var_a2 > 0) {
                arg0->unk_25D0 = 1;
                arg0->unk_0190(arg0->unk_0194 + arg0->unk_25C4, &arg0->unk_1598[(arg0->unk_25C4 & 0xFFF) >> 3], var_a2,
                               &arg0->unk_25A0);
            }
        }
    }

    var_v1 = arg0->unk_25CC - arg0->unk_25C8;
    while ((var_v1 < 0x960) && ((arg0->unk_25D1 == 1) || (arg0->unk_2598 > 0)) &&
           ((arg0->unk_25C4 - arg0->unk_25C0) >= 0x25) && (var_s2 > 0)) {
        GbAudio_DecodeSpeechFrame(arg0, arg0->unk_0198.unk_0000 + (((arg0->unk_25CC % 2560) >> 2) * 8));
        arg0->unk_25C0 = (arg0->unk_25BC >> 3) & ~3;
        arg0->unk_25CC += 0xA0;
        arg0->unk_2598--;
        var_v1 = arg0->unk_25CC - arg0->unk_25C8;
        var_s2--;
    }

    if ((arg0->unk_25D1 == 1) && (var_v1 >= 0x8C0)) {
        arg0->unk_25D1 = 2;
    }
}

u32 AudioChannel_Consume(GbAudioChannelState* arg0, u32 arg1) {
    u32 temp_v0;
    u32 var_a2;

    if (arg0->unk_25D1 == 3) {
        temp_v0 = arg0->unk_25CC - arg0->unk_25C8;
        if (arg1 < temp_v0) {
            var_a2 = arg1;
        } else {
            var_a2 = temp_v0;
            if (arg0->unk_2598 <= 0) {
                arg0->unk_25D1 = 4;
            }
        }
        arg0->unk_25C8 += var_a2;
        return var_a2;
    }

    return 0;
}

void AudioChannel_StartPlayback(GbAudioChannelState* arg0) {
    if (arg0->unk_25D1 == 2) {
        arg0->unk_25D1 = 3;
    }
}

void AudioChannel_Stop(GbAudioChannelState* arg0) {
    arg0->unk_25D1 = 4;
}
