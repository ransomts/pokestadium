#include <PR/os_internal_reg.h>
#include "global.h"
#include "dp_intro.h"
#include "profiler.h"
#include "4BDC0.h"
#include "5580.h"
#include "E1C0.h"
#include "373A0.h"
#include "src/50860.h"
#include "src/490A0.h"
#include "src/4BA90.h"
#include "src/4BDC0.h"

typedef struct unk_D_800A8480 {
  /* 0x0000 */ OSThread thread;
  /* 0x01B0 */ char unk01B0[0x2030];
} unk_D_800A8480; // size = 0x21E0

static s32 gAudioThreadEnabled;
static UnkStruct80001380 gAudioMessageQueues[2];
static s32 gAudioTaskBufferIndex;
static s32 gCurrentMusicId;
static unk_D_800A8480 gAudioThreadData;

void func_8000D1C0(void) {
}

void func_8000D1C8(void) {
}

void func_8000D1D0(void) {
}

void func_8000D1D8(void) {
}

void Music_ClearCurrentId(void) {
    gCurrentMusicId = -1;
}

void Music_ChangeTrack(s32 arg0) {
    if (arg0 != gCurrentMusicId) {
        if (gCurrentMusicId >= 0) {
            func_8004B9C4(0);
        }
        func_8004B1CC(arg0);
        gCurrentMusicId = arg0;
    }
}

void Music_SetTrack(s32 arg0) {
    if (arg0 != gCurrentMusicId) {
        func_8004B1CC(arg0);
        gCurrentMusicId = arg0;
    }
}

void Music_StopTrack(s32 arg0) {
    if (gCurrentMusicId >= 0) {
        func_8004B9C4(arg0);
        gCurrentMusicId = -1;
    }
}

s32 Audio_WaitForLoadAndFade(s32 arg0) {
    s32 retvar = 0;

    if (arg0 != 0) {
        Audio_ResetAndSetFade(2);
    }
    while (Audio_CalcLoadScore() != 0) {
        if (retvar < 1000000) {
            retvar++;
        } else if (retvar == 1000000) {
            Audio_FadeAllChannelsDefault();
            retvar++;
        }
    }
    return retvar;
}

void Audio_FadeAllChannelsFast(void) {
    Audio_FadeAllChannels(0x10);
}

void Audio_Unpause(void) {
    gAudioThreadEnabled = 0;
    Audio_SetPauseState(0);
}

void Audio_Pause(void) {
    Audio_SetPauseState(1);
    gAudioThreadEnabled = 1;
}

void Audio_ThreadMain(void* unused) {
    __osSetFpcCsr(0x01000C01);
    MessageQueue_Create(&gAudioThreadData.thread, 1, 1);
    ThreadList_Add(&gAudioThreadData.thread);
    gAudioThreadEnabled = 1;
    gCurrentMusicId = -1;
    gAudioTaskBufferIndex = 0;
    osCreateMesgQueue(&gAudioMessageQueues[0].queue, &gAudioMessageQueues[0].mesg, 1);
    osCreateMesgQueue(&gAudioMessageQueues[1].queue, &gAudioMessageQueues[1].mesg, 1);
    osSendMesg(&gAudioMessageQueues[0].queue, (void*)'DONE', 0);
    osSendMesg(&gAudioMessageQueues[1].queue, (void*)'DONE', 0);
    Audio_Initialize();
    Music_SetPanMode(0);
    Music_SetMasterVolumeLevel(3, 4);

    // thread loop
    while (1) {
        MessageQueue_Recv(&gAudioThreadData.thread);
        profiler_log_thread4_time();
        if ((gAudioThreadEnabled != 0) && (gRspTaskManager.unk_A38 < 0x15)) {
            Audio_BuildTask(&gAudioMessageQueues[gAudioTaskBufferIndex].task);
            RspTaskStart(&gAudioMessageQueues[gAudioTaskBufferIndex], 0);
        }
        gAudioTaskBufferIndex ^= 1;
        profiler_log_thread4_time();
    }
}

void Audio_CreateThread(void) {
    osCreateThread(&gAudioThreadData.thread, 4, Audio_ThreadMain, NULL, &gGbEmuState, 0x50);
    osStartThread(&gAudioThreadData.thread);
}
