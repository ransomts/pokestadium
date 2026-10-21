#include "global.h"
#include <PR/os_internal_reg.h>
#include "dp_intro.h"
#include "src/scheduler.h"
#include "src/gfx_rect.h"
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
UnkStruct80083CA0_2 gDisplayWorkerState;
u64 gRdpBootUcode[0x100 / sizeof(u64)];
u64 gRdpDramStack[0x408 / sizeof(u64)];
u64 gRdpYieldData[0xC08 / sizeof(u64)];
u64 gRdpOutputBuffer[0x20000 / sizeof(u64)];

// function prototypes
void Display_ClearFramebufferLine(u16 color);
void Display_SetBufferConfig(struct UnkArray4* arg0, u8 arg1, u8 arg2, u8 arg3, u8 arg4, s32 arg5, s32 arg6, s32 arg7);

void DisplayTask_Initialize(UnkStruct80001380* arg0) {
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

void DisplayTask_Submit(UnkStruct80001380* arg0, struct UnkArray4* arg1, s32 arg2) {
    arg0->task.t.data_ptr = (void*)(uintptr_t)arg1->rotation;
    arg0->task.t.data_size = arg1->RentalSlotAnimData_PosePhase;
    Sched_SubmitTask(arg0, arg2);
}

void Video_SetMode(s8 arg0, s8 arg1) {
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

void DisplayWorker_SetBufferConfig(struct UnkArray4* arg0) {
    if (arg0 == NULL) {
        gDisplayWorkerState.pendingTask.rotation = 0;
        gDisplayWorkerState.pendingTask.RentalSlotAnimData_PosePhase = 0;
        gDisplayWorkerState.pendingTask.unk_0C = NULL;
        gDisplayWorkerState.pendingTask.TrainerSlotSaveData_GamePort = gDisplayWorkerState.currentTask.TrainerSlotSaveData_GamePort;
        gDisplayWorkerState.pendingTask.posY = gDisplayWorkerState.currentTask.posY;
        gDisplayWorkerState.pendingTask.posX = gDisplayWorkerState.currentTask.posX;
    } else {
        gDisplayWorkerState.pendingTask.TrainerSlotSaveData_GamePort = arg0->TrainerSlotSaveData_GamePort;
        gDisplayWorkerState.pendingTask.posY = arg0->posY;
        gDisplayWorkerState.pendingTask.posX = arg0->posX;
        gDisplayWorkerState.pendingTask.rotation = arg0->rotation;
        gDisplayWorkerState.pendingTask.RentalSlotAnimData_PosePhase = arg0->RentalSlotAnimData_PosePhase;
        gDisplayWorkerState.pendingTask.unk_0C = arg0->unk_0C;
        gDisplayWorkerState.pendingTask.unk_03 = arg0->unk_03;
    }
}

void DisplayWorker_ProcessFrame(void) {
    s32 i;
    s32 sp20 = 0;

    if (gDisplayWorkerState.currentTask.rotation != 0) {
        Sched_WaitForTaskMessage(&gDisplayWorkerState.unk_A20);
    }

    if ((gDisplayWorkerState.pendingTask.rotation != 0) && (gDisplayWorkerState.previousTask.unk_0C != gDisplayWorkerState.pendingTask.unk_0C) &&
        (gDisplayWorkerState.previousTask.unk_03 != gDisplayWorkerState.pendingTask.unk_03)) {
        DisplayTask_Submit(&gDisplayWorkerState.unk_A20, &gDisplayWorkerState.pendingTask, 1);
        sp20 = 1;
    }

    for (i = 1; i < gDisplayWorkerState.previousTask.posX; i++) {
        Sched_WaitClientQueue(&gDisplayWorkerState);
    }

    while (gDisplayWorkerState.messageQueue.validCount > 0) {
        Sched_TryReceiveClientQueue(&gDisplayWorkerState);
    }

    if (gDisplayWorkerState.currentTask.unk_0C != NULL) {
        osViSwapBuffer(gDisplayWorkerState.currentTask.unk_0C->img_p);
        osViRepeatLine(0);
        if ((gDisplayWorkerState.currentTask.TrainerSlotSaveData_GamePort != gDisplayWorkerState.previousTask.TrainerSlotSaveData_GamePort) ||
            (gDisplayWorkerState.currentTask.posY != gDisplayWorkerState.previousTask.posY)) {
            Video_SetMode((s8)gDisplayWorkerState.currentTask.TrainerSlotSaveData_GamePort, (s8)gDisplayWorkerState.currentTask.posY);
        }
        if (gForceBlackScreen != 0) {
            osViBlack(1U);
        } else {
            osViBlack(0U);
        }
        crash_screen_set_draw_info((u16*)gDisplayWorkerState.currentTask.unk_0C->img_p, gDisplayWorkerState.currentTask.unk_0C->width, 0x10);
    } else {
        osViRepeatLine(1);
        osViSwapBuffer(gDisplayWorkerState.framebufferImage->img_p);
        if ((gDisplayWorkerState.currentTask.TrainerSlotSaveData_GamePort != gDisplayWorkerState.previousTask.TrainerSlotSaveData_GamePort) ||
            (gDisplayWorkerState.currentTask.posY != gDisplayWorkerState.previousTask.posY)) {
            Video_SetMode((s8)gDisplayWorkerState.currentTask.TrainerSlotSaveData_GamePort, (s8)gDisplayWorkerState.currentTask.posY);
        }
    }

    if ((sp20 == 0) && (gDisplayWorkerState.pendingTask.rotation != 0)) {
        DisplayTask_Submit(&gDisplayWorkerState.unk_A20, &gDisplayWorkerState.pendingTask, 0);
    }

    gDisplayWorkerState.previousTask = gDisplayWorkerState.currentTask;
    gDisplayWorkerState.currentTask = gDisplayWorkerState.pendingTask;
    profiler_log_thread5_time(THREAD5_END);
    Sched_WaitClientQueue(&gDisplayWorkerState);
}

void DisplayWorker_DrainEvents(void) {
    Sched_WaitClientQueue(&gDisplayWorkerState);
    while (gDisplayWorkerState.messageQueue.validCount > 0) {
        Sched_TryReceiveClientQueue(&gDisplayWorkerState);
    }
    Sched_WaitClientQueue(&gDisplayWorkerState);
}

void DisplayWorker_ThreadMain(UNUSED void* arg) {
    __osSetFpcCsr(0x01000C01);
    Display_SetBufferConfig(&gDisplayWorkerState.previousTask, 0, 1, 2, 0xFF, 0, 0, 0);
    Display_SetBufferConfig(&gDisplayWorkerState.currentTask, 0, 1, 2, 0xFF, 0, 0, 0);
    Sched_InitClientQueue(&gDisplayWorkerState.thread, 0, 4);
    Sched_AddClient(&gDisplayWorkerState);
    DisplayTask_Initialize(&gDisplayWorkerState.unk_A20);
    while (1) {
        void* sp4C;
        if (gRspTaskManager.preNmiState > 0) {
            DisplayWorker_DrainEvents();
            continue;
        }
        profiler_log_thread5_time(THREAD5_START);
        gDisplayWorkerState.waitingForMessage = 1;
        osRecvMesg(&gDisplayWorkerState.unk_9EC, &sp4C, 1);
        gDisplayWorkerState.waitingForMessage = 0;
        profiler_log_thread5_time(UNK_EVENT_1);
        profiler_log_thread5_time(UNK_EVENT_2);
        DisplayWorker_SetBufferConfig(sp4C);
        DisplayWorker_ProcessFrame();
        osSendMesg(&gDisplayWorkerState.doneQueue, (void*)'DONE', 0);
    }
}

void DisplayWorker_Initialize(void) {
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

    osCreateThread(&gDisplayWorkerState.thread, 5, DisplayWorker_ThreadMain, NULL, &gDisplayWorkerState.framebufferImage, 0x28);
    osStartThread(&gDisplayWorkerState.thread);
    osCreateMesgQueue(&gDisplayWorkerState.unk_9EC, &gDisplayWorkerState.unk_9E4, 1);
    osCreateMesgQueue(&gDisplayWorkerState.doneQueue, &gDisplayWorkerState.doneMessage, 1);
    gDisplayWorkerState.unk_A88 = 0;
    gDisplayWorkerState.waitingForMessage = 0;
    gDisplayWorkerState.framebufferImage = GfxImage_Allocate(0, IMAGE_SIZE_BITS_16b, 0x280, 1, MEMORY_POOL_RIGHT);
    Display_ClearFramebufferLine(1);
    Dma_WriteChunks(&gRdpBootUcode, 0xB0000B70, 0xB0000C70, 0);
}

/**
 * Write a specific color to a line on the framebuffer for a 640x480 resolution.
 */
void Display_ClearFramebufferLine(u16 color) {
    s32 width = 640;
    u16* buf = (u16*)gDisplayWorkerState.framebufferImage->img_p;

    while (width-- > 0) {
        *(buf)++ = color;
    }

    osWritebackDCache(gDisplayWorkerState.framebufferImage->img_p, 0x500);
}

u16 Display_GetFramebufferClearColor(void) {
    u16* ptr = (u16*)gDisplayWorkerState.framebufferImage->img_p;
    return *ptr;
}

s32 Display_IsCurrentFramebuffer(void) {
    s32 result = 0;

    if (osViGetCurrentFramebuffer() == gDisplayWorkerState.framebufferImage->img_p) {
        result = 1;
    }

    return result;
}

void Display_WaitForCompletion(void) {
    osRecvMesg(&gDisplayWorkerState.doneQueue, NULL, 1);
}

void Display_QueueFramebufferRequest(void* arg0) {
    osSendMesg(&gDisplayWorkerState.unk_9EC, arg0, 0);
}

void Display_WaitForFrames(s32 arg0) {
    while (arg0-- > 0) {
        Display_QueueFramebufferRequest(0);
        Display_WaitForCompletion();
    }
}

void Display_SetBufferConfig(struct UnkArray4* arg0, u8 arg1, u8 arg2, u8 arg3, u8 arg4, s32 arg5, s32 arg6, s32 arg7) {
    arg0->TrainerSlotSaveData_GamePort = arg1;
    arg0->posY = arg2;
    arg0->posX = arg3;
    arg0->unk_03 = arg4;
    arg0->rotation = arg5;
    arg0->RentalSlotAnimData_PosePhase = arg6;
    arg0->unk_0C = (struct FramebufferImage*)(uintptr_t)arg7;
}

s32 Display_GetWorkerStatus(void) {
    return (s32)gDisplayWorkerState.previousTask.unk_0C;
}

void Display_ApplyPendingVideoMode(void) {
    Video_SetMode((s8)gDisplayWorkerState.previousTask.TrainerSlotSaveData_GamePort, (s8)gDisplayWorkerState.previousTask.posY);
}

s32 Display_IsFrameReady(void) {
    s32 result = 1;

    if (gDisplayWorkerState.currentTask.rotation != 0) {
        result = gDisplayWorkerState.unk_A20.queue.validCount > 0;
    }
    return result;
}

void Display_EnableBlackout(void) {
    gForceBlackScreen = 1;
}

void Display_DisableBlackout(void) {
    gForceBlackScreen = 0;
}
