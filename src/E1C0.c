#include "E1C0.h"
#include <PR/os_internal_reg.h>
#include "dp_intro.h"
#include "sections.h"
#include "memory.h"
#include "dp_intro.h"
#include "3FB0.h"
#include "5580.h"
#include "util.h"
#include "src/fragments/1/fragment1.h"

GbEmuState* gGbEmuState;
GbEmuThreadInfo* gGbEmuThreadInfo;
static char gGbEmuThreadId;

extern u8 D_81200000[];

void GbAudio_ThreadMain(UNUSED void* arg0) {
    void (*func)(void*) = Util_ConvertAddrToVirtAddr(&func_81206F38);

    __osSetFpcCsr(0x01000C01);
    MessageQueue_Create(gGbEmuThreadInfo, 0, 1);
    ThreadList_Add(gGbEmuThreadInfo);

    while (1) {
        MessageQueue_Recv(gGbEmuThreadInfo);
        if (gRspTaskManager.unk_A38 >= 0x15) {
            continue;
        }
        func(gGbEmuThreadInfo);
    }
}

void GbEmu_ThreadMain(UNUSED void* arg0) {
    void (*func1)(void* func) = Util_ConvertAddrToVirtAddr(&func_81206D9C);
    void (*func2)(void* func) = Util_ConvertAddrToVirtAddr(&func_81206E64);

    __osSetFpcCsr(0x01000C01);
    MessageQueue_Create(gGbEmuState, 0, 1);
    ThreadList_Add(gGbEmuState);
    func1(gGbEmuState);
    osStartThread(&gGbEmuThreadInfo->thread);

    while (1) {
        MessageQueue_Recv(gGbEmuState);
        if (gRspTaskManager.unk_A38 >= 0x15) {
            continue;
        }
        func2(gGbEmuState);
    }
}

void GbEmu_Create(UnkInputStruct8000D738* arg0) {
    s32 temp_v0;

    main_pool_push_state('GBEM');
    gGbEmuState = main_pool_alloc(0x2210, 0);
    gGbEmuThreadInfo = main_pool_alloc(0x21E0, 0);

    FRAGMENT_LOAD(fragment1);
    temp_v0 = ASSET_LOAD2(fonts, 1, 1);

    gGbEmuState->font1 = BinArchive_GetFile(temp_v0, 0);
    gGbEmuState->font2 = BinArchive_GetFile(temp_v0, 1);
    gGbEmuState->inputConfig = *arg0;
    osCreateMesgQueue(&gGbEmuState->queue2, &gGbEmuState->mesg, 1);
    osCreateThread(&gGbEmuThreadInfo->thread, 10, GbAudio_ThreadMain, NULL, (u32)gGbEmuThreadInfo + 0x21E0, 0x11);
    osCreateThread(&gGbEmuState->thread, 8, GbEmu_ThreadMain, NULL, (u32)gGbEmuState + 0x21E0, 0xF);
    gGbEmuThreadId = func_8000B318(0);
    osStartThread(&gGbEmuState->thread);
}

OSMesg* GbEmu_RecvMessage(void) {
    OSMesg mesg;

    osRecvMesg(&gGbEmuState->queue2, &mesg, OS_MESG_BLOCK);
    return mesg;
}

void GbEmu_Shutdown(UnkInputStruct8000D738* arg0) {
    *arg0 = gGbEmuState->inputConfig;
    func_8000B318(gGbEmuThreadId);
    osViBlack(1U);
    func_80001C64();
    ThreadList_Remove(gGbEmuState);
    ThreadList_Remove(gGbEmuThreadInfo);
    osDestroyThread(&gGbEmuState->thread);
    osDestroyThread(&gGbEmuThreadInfo->thread);
    main_pool_pop_state('GBEM');
}
