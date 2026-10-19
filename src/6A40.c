#include "global.h"
#include "6A40.h"

typedef struct UnkStruct800A7428 {
    u32* unk0;
    u32* unk4;
    u32 unk8;
    s32 unkC;
    s16 unk10;
} UnkStruct800A7428; // size = 0x12

Gfx* gDisplayListHead;
UnkStruct800A7428 gDLBuffers;
ClipRect gClipRect;

void Gfx_SwapDisplayListBuffer(void);

void Gfx_InitDisplayListBuffers(u32 arg0, s32 arg1) {
    gDLBuffers.unk10 = 0;
    gDLBuffers.unkC = arg0;
    gDLBuffers.unk0 = main_pool_alloc_with_func(arg0, arg1, 'DYN0', NULL);
    gDLBuffers.unk4 = main_pool_alloc_with_func(arg0, arg1, 'DYN1', NULL);
    Gfx_SwapDisplayListBuffer();
}

void Gfx_FreeDisplayListBuffers(void) {
    main_pool_try_free(gDLBuffers.unk4);
    main_pool_try_free(gDLBuffers.unk0);
}

void Gfx_SwapDisplayListBuffer(void) {
    s32* temp_v0 = (s32*)&gDLBuffers;

    gDLBuffers.unk10 ^= 1;
    temp_v0 += gDLBuffers.unk10;

    gDLBuffers.unk8 = *temp_v0 + gDLBuffers.unkC;
    gDisplayListHead = *temp_v0;
}

void Gfx_GetDisplayListRange(Gfx** arg0, Gfx** arg1) {
    s32* ptr = (s32*)&gDLBuffers;
    *arg1 = (Gfx*)((uintptr_t)gDisplayListHead - ptr[gDLBuffers.unk10]);
    *arg0 = (Gfx*)(ptr[gDLBuffers.unk10]);
}

void* Gfx_AllocDisplayList(s32 arg0) {
    u32 temp_v0;
    u32 ret;

    arg0 = ALIGN8(arg0);
    temp_v0 = (gDLBuffers.unk8 - arg0);
    ret = NULL;
    if (temp_v0 >= (uintptr_t)gDisplayListHead) {
        gDLBuffers.unk8 = temp_v0;
        ret = temp_v0;
    }
    return ret;
}

s32 Gfx_GetDisplayListRemaining(void) {
    return gDLBuffers.unk8 - (uintptr_t)gDisplayListHead;
}
