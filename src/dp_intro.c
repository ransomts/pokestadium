#include "global.h"
#include <PR/os_internal_reg.h>
#include "dp_intro.h"
#include "5580.h"
#include "6BC0.h"
#include "crash_screen.h"
#include "profiler.h"
#include "memory.h"

extern u64 F3DEX2_data_bin[]; // F3DEX2_data.bin

// .data
s32 gForceBlackScreen = 0;
char gViModeIndexTable[] = {
    0x0E, 0x10, 0x17, 0x19, 0x00, 0x02, 0x09, 0x0B,
    0x1C, 0x1E, 0x25, 0x27, 0x2A, 0x2C, 0x33, 0x35,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
};

// .rodata
const f32 gViYScaleTable[4] = {
    0.8333333135f,
    0.0f,
    0.0f,
    0.0f,
};

// .bss
UnkStruct80083CA0_2 gIntroTaskState;
u64 gRdpBootUcode[0x100 / sizeof(u64)];
u64 gRdpDramStack[0x408 / sizeof(u64)];
u64 gRdpYieldData[0xC08 / sizeof(u64)];
u64 gRdpOutputBuffer[0x20000 / sizeof(u64)];

// function prototypes
void Gfx_SetFrameFillColor(u16 color);
void IntroBuffer_SetParams(struct UnkArray4* arg0, u8 arg1, u8 arg2, u8 arg3, u8 arg4, s32 arg5, s32 arg6, s32 arg7);

void RdpTask_Init(UnkStruct80001380* arg0) {
    arg0->task.t.type = M_GFXTASK;
    arg0->task.t.flags = 0;
    arg0->task.t.ucode_boot = gRdpBootUcode;
    arg0->task.t.ucode_boot_size = 0x100;
    arg0->task.t.ucode = _binary_assets_us_F3DEX2_bin_start;
    arg0->task.t.ucode_data = F3DEX2_data_bin;
    arg0->task.t.ucode_size = 0x1000;
    arg0->task.t.ucode_data_size = 0x800;
    arg0->task.t.dram_stack = (void*)ALIGN16((uintptr_t)gRdpDramStack);
    arg0->task.t.dram_stack_size = 0x400;
    arg0->task.t.yield_data_ptr = (void*)ALIGN16((uintptr_t)gRdpYieldData);
    arg0->task.t.yield_data_size = 0xC00;
    arg0->task.t.output_buff = (gRdpOutputBuffer);
    arg0->task.t.output_buff_size = (gRdpOutputBuffer + (0x20000 / sizeof(u64)));
    osCreateMesgQueue(&arg0->queue, &arg0->mesg, 1);
}

void RdpTask_StartWithData(UnkStruct80001380* arg0, struct UnkArray4* arg1, s32 arg2) {
    arg0->task.t.data_ptr = (void*)(uintptr_t)arg1->unk_04;
    arg0->task.t.data_size = arg1->unk_08;
    RspTaskStart(arg0, arg2);
}

void Vi_SetMode(s8 arg0, s8 arg1) {
    s32 var_v0;

    if (osTvType == 2) {
        var_v0 = (arg0 * 2) + arg1 + 8;
    } else {
        var_v0 = (arg0 * 2) + arg1 + 4;
    }

    osViSetMode(&osViModeTable[(s32)gViModeIndexTable[var_v0]]);
    osViSetSpecialFeatures(0x40U);
    osViSetSpecialFeatures(2U);
    osViSetSpecialFeatures(0x10U);
    if (osTvType == 0) {
        osViSetYScale(gViYScaleTable[0]);
    }
}

void IntroTask_SetPendingBuffer(struct UnkArray4* arg0) {
    if (arg0 == NULL) {
        gIntroTaskState.unk_A8C.unk_04 = 0;
        gIntroTaskState.unk_A8C.unk_08 = 0;
        gIntroTaskState.unk_A8C.unk_0C = NULL;
        gIntroTaskState.unk_A8C.unk_01 = gIntroTaskState.unk_A9C.unk_01;
        gIntroTaskState.unk_A8C.unk_02 = gIntroTaskState.unk_A9C.unk_02;
        gIntroTaskState.unk_A8C.unk_00 = gIntroTaskState.unk_A9C.unk_00;
    } else {
        gIntroTaskState.unk_A8C.unk_01 = arg0->unk_01;
        gIntroTaskState.unk_A8C.unk_02 = arg0->unk_02;
        gIntroTaskState.unk_A8C.unk_00 = arg0->unk_00;
        gIntroTaskState.unk_A8C.unk_04 = arg0->unk_04;
        gIntroTaskState.unk_A8C.unk_08 = arg0->unk_08;
        gIntroTaskState.unk_A8C.unk_0C = arg0->unk_0C;
        gIntroTaskState.unk_A8C.unk_03 = arg0->unk_03;
    }
}

void IntroTask_ProcessFrame(void) {
    s32 i;
    s32 sp20 = 0;

    if (gIntroTaskState.unk_A9C.unk_04 != 0) {
        RspTaskYield(&gIntroTaskState.unk_A20);
    }

    if ((gIntroTaskState.unk_A8C.unk_04 != 0) && (gIntroTaskState.unk_AAC.unk_0C != gIntroTaskState.unk_A8C.unk_0C) &&
        (gIntroTaskState.unk_AAC.unk_03 != gIntroTaskState.unk_A8C.unk_03)) {
        RdpTask_StartWithData(&gIntroTaskState.unk_A20, &gIntroTaskState.unk_A8C, 1);
        sp20 = 1;
    }

    for (i = 1; i < gIntroTaskState.unk_AAC.unk_00; i++) {
        MessageQueue_Recv(&gIntroTaskState);
    }

    while (gIntroTaskState.unk_1C0.validCount > 0) {
        MessageQueue_TryRecv(&gIntroTaskState);
    }

    if (gIntroTaskState.unk_A9C.unk_0C != NULL) {
        osViSwapBuffer(gIntroTaskState.unk_A9C.unk_0C->img_p);
        osViRepeatLine(0);
        if ((gIntroTaskState.unk_A9C.unk_01 != gIntroTaskState.unk_AAC.unk_01) ||
            (gIntroTaskState.unk_A9C.unk_02 != gIntroTaskState.unk_AAC.unk_02)) {
            Vi_SetMode((s8)gIntroTaskState.unk_A9C.unk_01, (s8)gIntroTaskState.unk_A9C.unk_02);
        }
        if (gForceBlackScreen != 0) {
            osViBlack(1U);
        } else {
            osViBlack(0U);
        }
        crash_screen_set_draw_info((u16*)gIntroTaskState.unk_A9C.unk_0C->img_p, gIntroTaskState.unk_A9C.unk_0C->width, 0x10);
    } else {
        osViRepeatLine(1);
        osViSwapBuffer(gIntroTaskState.unk_9E0->img_p);
        if ((gIntroTaskState.unk_A9C.unk_01 != gIntroTaskState.unk_AAC.unk_01) ||
            (gIntroTaskState.unk_A9C.unk_02 != gIntroTaskState.unk_AAC.unk_02)) {
            Vi_SetMode((s8)gIntroTaskState.unk_A9C.unk_01, (s8)gIntroTaskState.unk_A9C.unk_02);
        }
    }

    if ((sp20 == 0) && (gIntroTaskState.unk_A8C.unk_04 != 0)) {
        RdpTask_StartWithData(&gIntroTaskState.unk_A20, &gIntroTaskState.unk_A8C, 0);
    }

    gIntroTaskState.unk_AAC = gIntroTaskState.unk_A9C;
    gIntroTaskState.unk_A9C = gIntroTaskState.unk_A8C;
    profiler_log_thread5_time(THREAD5_END);
    MessageQueue_Recv(&gIntroTaskState);
}

void func_800017E4(void) {
    MessageQueue_Recv(&gIntroTaskState);
    while (gIntroTaskState.unk_1C0.validCount > 0) {
        MessageQueue_TryRecv(&gIntroTaskState);
    }
    MessageQueue_Recv(&gIntroTaskState);
}

void IntroTask_ThreadMain(UNUSED void* arg) {
    __osSetFpcCsr(0x01000C01);
    IntroBuffer_SetParams(&gIntroTaskState.unk_AAC, 0, 1, 2, 0xFF, 0, 0, 0);
    IntroBuffer_SetParams(&gIntroTaskState.unk_A9C, 0, 1, 2, 0xFF, 0, 0, 0);
    MessageQueue_Create(&gIntroTaskState.thread, 0, 4);
    ThreadList_Add(&gIntroTaskState);
    RdpTask_Init(&gIntroTaskState.unk_A20);
    while (1) {
        void* sp4C;
        if (gRspTaskManager.unk_A38 > 0) {
            func_800017E4();
            continue;
        }
        profiler_log_thread5_time(THREAD5_START);
        gIntroTaskState.unk_A8A = 1;
        osRecvMesg(&gIntroTaskState.unk_9EC, &sp4C, 1);
        gIntroTaskState.unk_A8A = 0;
        profiler_log_thread5_time(UNK_EVENT_1);
        profiler_log_thread5_time(UNK_EVENT_2);
        IntroTask_SetPendingBuffer(sp4C);
        IntroTask_ProcessFrame();
        osSendMesg(&gIntroTaskState.unk_A04, (void*)'DONE', 0);
    }
}

void IntroTask_Init(void) {
    switch (osTvType) {
        case 1:
        case 2:
            break;

        default:
            osViBlack(1U);
            while (1) {
                ;
            }
            break;
    }

    osCreateThread(&gIntroTaskState.thread, 5, IntroTask_ThreadMain, NULL, &gIntroTaskState.unk_9E0, 0x28);
    osStartThread(&gIntroTaskState.thread);
    osCreateMesgQueue(&gIntroTaskState.unk_9EC, &gIntroTaskState.unk_9E4, 1);
    osCreateMesgQueue(&gIntroTaskState.unk_A04, &gIntroTaskState.unk_9E8, 1);
    gIntroTaskState.unk_A88 = 0;
    gIntroTaskState.unk_A8A = 0;
    gIntroTaskState.unk_9E0 = FramebufferImage_Allocate(0, IMAGE_SIZE_BITS_16b, 0x280, 1, MEMORY_POOL_RIGHT);
    Gfx_SetFrameFillColor(1);
    DmaCopyAsyncRange(&gRdpBootUcode, 0xB0000B70, 0xB0000C70, 0);
}

/**
 * Write a specific color to a line on the framebuffer for a 640x480 resolution.
 */
void Gfx_SetFrameFillColor(u16 color) {
    s32 width = 640;
    u16* buf = (u16*)gIntroTaskState.unk_9E0->img_p;

    while (width-- > 0) {
        *(buf)++ = color;
    }

    osWritebackDCache(gIntroTaskState.unk_9E0->img_p, 0x500);
}

u16 Gfx_GetFrameFillColor(void) {
    u16* ptr = (u16*)gIntroTaskState.unk_9E0->img_p;
    return *ptr;
}

s32 IsSoftResetPending(void) {
    s32 result = 0;

    if (osViGetCurrentFramebuffer() == gIntroTaskState.unk_9E0->img_p) {
        result = 1;
    }

    return result;
}

void Sched_WaitFrame(void) {
    osRecvMesg(&gIntroTaskState.unk_A04, NULL, 1);
}

void Sched_SendFrame(void* arg0) {
    osSendMesg(&gIntroTaskState.unk_9EC, arg0, 0);
}

void Sched_RunFrames(s32 arg0) {
    while (arg0-- > 0) {
        Sched_SendFrame(0);
        Sched_WaitFrame();
    }
}

void IntroBuffer_SetParams(struct UnkArray4* arg0, u8 arg1, u8 arg2, u8 arg3, u8 arg4, s32 arg5, s32 arg6, s32 arg7) {
    arg0->unk_01 = arg1;
    arg0->unk_02 = arg2;
    arg0->unk_00 = arg3;
    arg0->unk_03 = arg4;
    arg0->unk_04 = arg5;
    arg0->unk_08 = arg6;
    arg0->unk_0C = (struct FramebufferImage*)(uintptr_t)arg7;
}

s32 GetFramebufferInfo(void) {
    return (s32)gIntroTaskState.unk_AAC.unk_0C;
}

void func_80001C64(void) {
    Vi_SetMode((s8)gIntroTaskState.unk_AAC.unk_01, (s8)gIntroTaskState.unk_AAC.unk_02);
}

s32 RspTaskYielded(void) {
    s32 result = 1;

    if (gIntroTaskState.unk_A9C.unk_04 != 0) {
        result = gIntroTaskState.unk_A20.queue.validCount > 0;
    }
    return result;
}

void func_80001CB8(void) {
    gForceBlackScreen = 1;
}

void func_80001CC8(void) {
    gForceBlackScreen = 0;
}
