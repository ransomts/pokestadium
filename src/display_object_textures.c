#include "src/display_object_textures.h"
#include "src/geo_layout.h"
#include "src/dma.h"
#include "src/memmap.h"
#include "src/memory.h"
#include "src/util.h"
#include <PR/os_internal_reg.h>
#include <PR/leo.h>
#include "src/memory.h"

typedef struct ret_func_unk_D_800ABE10 {
    /* 0x00 */ char unk00[0x3];
    /* 0x03 */ u8 unk_03;
    /* 0x04 */ char unk04[0x4];
    /* 0x08 */ MiniHudMainGraph** RentalSlotAnimData_PosePhase;
    /* 0x0C */ char unk0C[0x8];
    /* 0x14 */ func_unk_D_800ABE10 unk_14;
} ret_func_unk_D_800ABE10;

// .bss
unk_D_800ABE10 gAssetManager;

void GeoLayout_ConvertTextures(MiniHudMainGraph* arg0, arg1_func_80010CA8 arg1) {
    s32 i;
    s32 j;
    GfxTextureInfo* var_s2 = arg0->unk_18;
    unk_D_86002F34_01C* var_s4 = arg0->unk_1C;

    for (i = 0; i < arg0->unk_24; i++, var_s2++) {
        if (var_s2->posX == 0) {
            if (var_s2->type == unk_D_86002F34_018_GFX_TYPE_2) {
                u16* var_s1 = (u16*)var_s2->texture;
                for (j = 0; j < var_s2->num_texels; j++, var_s1++) {
                    *var_s1 = Color_AdjustRGB5551(*var_s1, arg1);
                }
            }
            if (var_s2->type == unk_D_86002F34_018_GFX_TYPE_3) {
                u32* var_s1 = var_s2->texture;
                for (j = 0; j < var_s2->num_texels; j++, var_s1++) {
                    *var_s1 = Color_AdjustRGBA8(*var_s1, arg1);
                }
            }
        }
    }
    for (i = 0; i < arg0->unk_25; i++, var_s4++) {
        u16* var_s1 = var_s4->rotation;
        for (j = 0; j < var_s4->posX; j++, var_s1++) {
            *var_s1 = Color_AdjustRGB5551(*var_s1, arg1);
        }
    }
}

Fragment* Jpeg_AllocAndDecodeFragment(MemoryBlock* arg0, PRESJPEG* arg1, PRESJPEG* arg2) {
    Fragment* sp1C;
    s32 sp18;
    s32 temp_v0_2;

    sp18 = arg0->size;
    sp1C = MainPool_AllocAligned(arg0, arg2->unk_0C + 0x100, 0x10);

    if (sp1C != NULL) {
        temp_v0_2 = Jpeg_DecodeImage(sp1C, arg2->unk_0C + 0x100, (u8*)arg2 + arg2->RentalSlotAnimData_PosePhase);
        if (temp_v0_2 == 0) {
            MainPool_ResetStateToOffset(arg0, sp18);
            sp1C = NULL;
        } else {
            MainPool_ResetStateToOffset(arg0, sp18 + temp_v0_2);
        }
    }
    return sp1C;
}

Fragment* Yay0_AllocAndDecompressFragment(MainPoolState* arg0, PERSSZP* arg1, PERSSZP* arg2) {
    u8* sp1C = MainPool_AllocAligned(arg0, arg2->decompressed_size2, 0x10);

    if (sp1C != NULL) {
        Yay0_DecompressAndRelocate(arg2, sp1C);
    }
    return sp1C;
}

Fragment* Asset_AllocAndCopyFragment(MainPoolState* arg0, PERSSZP* arg1, s32 arg2, u32 arg3) {
    u32* sp1C;

    sp1C = MainPool_AllocAligned(arg0, arg3, 0x10);
    if (sp1C != NULL) {
        Util_Memcpy(sp1C, (u8*)arg1 + arg2, arg3 >> 2);
    }
    return sp1C;
}

Fragment* Fragment_LoadFromRomRange(MainPoolState* arg0, s32 start, s32 end, PERSSZP* arg3, s32 arg4) {
    UNUSED s32 pad;
    u32 size = ALIGN16(end - start);
    Fragment* var_v1 = NULL;

    if (arg4 >= size) {
        Dma_WriteChunks(arg3, start, end, 0);

        if (((u32*)arg3->magic)[0] == 'PERS' && (((u32*)arg3->magic)[1] == '-SZP')) {
            var_v1 = Yay0_AllocAndDecompressFragment(arg0, arg3, arg3);
        } else if (((u32*)arg3->magic)[0] == 'PRES' && (((u32*)arg3->magic)[1] == 'JPEG')) {
            var_v1 = Jpeg_AllocAndDecodeFragment(arg0, arg3, arg3);
        } else {
            var_v1 = Asset_AllocAndCopyFragment(arg0, arg3, 0, size);
        }
    }

    return var_v1;
}

Fragment* Fragment_LoadFromLbaRange(MainPoolState* arg0, StorageRange* arg1, PERSSZP* arg2, u32 arg3) {
    s32 sp3C;
    Fragment* sp38;
    PERSSZP* temp_s1;

    LeoLBAToByte(arg1->posX, arg1->posY, &sp3C);
    sp3C = ALIGN16(sp3C);

    if (arg3 >= sp3C) {
        temp_s1 = arg1->rotation + (u8*)arg2;

        Storage_QueueDiskTransfer(0, arg2, arg1->posX, arg1->posY, &gAssetManager.unk_9EC, 0);
        osRecvMesg(&gAssetManager.unk_9EC, NULL, 1);

        if (((u32*)temp_s1->magic)[0] == 'PERS' && (((u32*)temp_s1->magic)[1] == '-SZP')) {
            sp38 = Yay0_AllocAndDecompressFragment(arg0, arg2, temp_s1);
        } else if (((u32*)temp_s1->magic)[0] == 'PRES' && (((u32*)temp_s1->magic)[1] == 'JPEG')) {
            sp38 = Jpeg_AllocAndDecodeFragment(arg0, arg2, temp_s1);
        } else {
            sp38 = Asset_AllocAndCopyFragment(arg0, arg2, arg1->rotation, arg1->RentalSlotAnimData_PosePhase);
        }
    }

    return sp38;
}

void Fragment_RelocateAndCommit(MainPoolState* arg0, u32 arg1, Fragment* arg2) {
    Memmap_RelocateFragment(arg1, arg2);
    MainPool_ResetStateToOffset(arg0, ((u32)arg2 + arg2->sizeInRam) - (u32)arg0->listHeadR);
}

Fragment* BinArchive_LoadFileFromRomRange(MainPoolState* arg0, BinArchive* arg1, BinArchiveFile* arg2, u32 arg3, s32 arg4) {
    s32 temp_a1 = arg1->rotation + arg2->offset;

    return Fragment_LoadFromRomRange(arg0, temp_a1, arg2->size + temp_a1, arg3, arg4);
}

Fragment* BinArchive_LoadFileFromLbaRange(MainPoolState* arg0, BinArchive* arg1, BinArchiveFile* arg2, u32 arg3, s32 arg4) {
    StorageRange sp1C;

    Storage_SetByteRange(&sp1C, arg1->rotation, arg2->offset, arg2->size);
    return Fragment_LoadFromLbaRange(arg0, &sp1C, arg3, arg4);
}

Fragment* BinArchive_LoadFileToPool(MainPoolState* arg0, BinArchive* arg1, s32 arg2, u32 arg3, s32 arg4) {
    s32 pad[4];
    Fragment* var_s0 = NULL;
    BinArchiveFile* sp2C = (u8*)arg1 + sizeof(BinArchive) + (arg2 * sizeof(BinArchiveFile));

    if (arg2 < arg1->num_files) {
        if (arg1->posX & 1) {
            var_s0 = (u8*)arg1 + sp2C->offset;
        } else if (!(arg1->posX & 4) && (sp2C->RentalSlotAnimData_PosePhase != NULL)) {
            var_s0 = sp2C->RentalSlotAnimData_PosePhase;
        } else {
            if (arg1->posX & 0x80) {
                var_s0 = BinArchive_LoadFileFromLbaRange(arg0, arg1, sp2C, arg3, arg4);
            } else {
                var_s0 = BinArchive_LoadFileFromRomRange(arg0, arg1, sp2C, arg3, arg4);
            }

            if (var_s0 != NULL) {
                if ((((u32*)var_s0->magic)[0] == 'FRAG') && (((u32*)var_s0->magic)[1] == 'MENT')) {
                    Fragment_RelocateAndCommit(arg0, arg1->posY, var_s0);
                }
                sp2C->RentalSlotAnimData_PosePhase = var_s0;
            }
        }
    }

    return var_s0;
}

s32 Fragment_ProcessGeoLayout(MemoryBlock* arg0, Fragment* arg1, arg1_func_80010CA8 arg2) {
    s32 i;
    MiniHudMainGraph* temp_v0_2;
    ret_func_unk_D_800ABE10* temp_v0;
    ret_func_unk_D_800ABE10* (*func)(s32, s32) = arg1;

    temp_v0 = func(0, 0);
    temp_v0->unk_14 = arg1;

    for (i = 0; i < temp_v0->unk_03; i++) {
        temp_v0_2 = process_geo_layout(arg0, temp_v0->RentalSlotAnimData_PosePhase[i]);

        if (temp_v0_2->posX.posX == 0xE) {
            temp_v0_2->unk_28 = arg1;
            if (arg2.raw != 0) {
                GeoLayout_ConvertTextures(temp_v0_2, arg2);
            }
        }
        temp_v0->RentalSlotAnimData_PosePhase[i] = temp_v0_2;
    }

    return temp_v0;
}

void Fragment_ProcessGeoLayoutList(MemoryBlock* arg0, arg1_func_80019420* arg1) {
    while (arg1->posX) {
        if (arg1->posX == 3) {
            arg1->rotation = process_geo_layout(arg0, arg1->rotation);
        }

        arg1++;
    }
}

void PokeIcon_LoadModelArchive(unk_func_80019600* arg0) {
    UNUSED s32 pad;
    MemoryBlock* sp28;
    Fragment* sp24;

    sp28 = MainPool_InitState(arg0->pool, arg0->size);
    sp24 = BinArchive_LoadFileToPool(sp28, gAssetManager.modelArchives.posX, arg0->posY, gAssetManager.modelArchives.RentalSlotAnimData_PosePhase, 0x28000);

    if (sp24 != NULL) {
        arg0->RentalSlotAnimData_PosePhase = Fragment_ProcessGeoLayout(sp28, sp24, arg0->unk_18);
    } else {
        arg0->RentalSlotAnimData_PosePhase = 0;
    }

    arg0->size = sp28->size + 0x10;
}

void PokeIcon_LoadMultipleModels(unk_func_80019600* arg0) {
    Fragment* temp_v0;
    MainPoolState* temp_s3;
    s32 var_s2;
    s32* temp_s6;
    s16* var_s0;

    temp_s6 = arg0->RentalSlotAnimData_PosePhase;
    var_s2 = 0;
    temp_s3 = MainPool_InitState(arg0->pool, arg0->size);
    var_s0 = arg0->unk_0C;

    while (*var_s0 != -1) {
        temp_v0 = BinArchive_LoadFileToPool(temp_s3, gAssetManager.modelArchives.rotation, *var_s0, gAssetManager.modelArchives.RentalSlotAnimData_PosePhase, 0x28000);
        if (temp_v0 == NULL) {
            break;
        }

        temp_s6[var_s2] = temp_v0 + 1;
        Fragment_ProcessGeoLayoutList(temp_s3, temp_v0 + 1);
        var_s0++;
        var_s2++;
    }

    temp_s6[var_s2] = 0;
    arg0->size = temp_s3->listHeadL + 1;
}

void PokeIcon_ThreadMain(UNUSED void* arg0) {
    unk_func_80019600* sp34;

    __osSetFpcCsr(0x01000C01);

    while (true) {
        osRecvMesg(&gAssetManager.requestQueue, &sp34, 1);

        switch (sp34->posX) {
            case 1:
                PokeIcon_LoadModelArchive(sp34);
                break;

            case 2:
                PokeIcon_LoadMultipleModels(sp34);
                break;
        }

        if (sp34->queue != NULL) {
            osSendMesg(sp34->queue, sp34, 1);
        }
    }
}

void PokeIcon_StartThread(void) {
    osCreateMesgQueue(&gAssetManager.requestQueue, &gAssetManager.requestMessage, 8);
    osCreateMesgQueue(&gAssetManager.unk_9EC, &gAssetManager.unk_9E8, 1);
    osCreateThread(&gAssetManager.unk_000, 7, PokeIcon_ThreadMain, NULL, &gAssetManager.requestMessage, 0xA);
    osStartThread(&gAssetManager.unk_000);
}

AssetManager* PokeIcon_AllocFramebuffers(u32 arg0) {
    s16 i = 1;
    AssetManager* temp_v0 = main_pool_alloc(sizeof(AssetManager), 1);

    temp_v0->posX = arg0;
    temp_v0->TrainerSlotSaveData_GamePort = 0;
    temp_v0->posY = 0;
    temp_v0->unk_24 = 0;
    temp_v0->rotation[0] = NULL;
    temp_v0->rotation[1] = NULL;
    temp_v0->unk_18 = NULL;
    temp_v0->unk_2C.raw = 0;

    if (arg0 & 1) {
        temp_v0->rotation[0] = main_pool_alloc(0x3C000, 1);
        if (arg0 & 4) {
            temp_v0->rotation[1] = main_pool_alloc(0x3C000, 1);
        } else if (arg0 & 8) {
            for (i = 1; i < 5; i++) {
                temp_v0->rotation[i] = main_pool_alloc(0x3C000, 1);
            }
        }
    }

    if (arg0 & 2) {
        temp_v0->unk_18 = main_pool_alloc(0x18000, 1);
    }

    osCreateMesgQueue(&temp_v0->unk_30, &temp_v0->unk_48, 2);
    osCreateMesgQueue(&temp_v0->unk_50, &temp_v0->unk_68, 2);
    return temp_v0;
}

void PokeIcon_OpenModelArchives(void) {
    gAssetManager.modelArchives.posX = BinArchive_Open(0x920000, NULL, 1, 1);
    gAssetManager.modelArchives.rotation = BinArchive_Open(0x8CC000, NULL, 1, 1);
    gAssetManager.modelArchives.RentalSlotAnimData_PosePhase = main_pool_alloc(0x28000, 1);
}

s32 PokeIcon_RequestFrameLoad(AssetManager* arg0, u16 arg1, arg1_func_80010CA8 arg2) {
    s32 sp1C;
    sp18_func_800198E4* sp18;
    s32 var_v1;

    sp1C = 0;
    if ((arg0->posX & 1) && !(arg0->TrainerSlotSaveData_GamePort & 1)) {
        sp18 = Util_Malloc(sizeof(sp18_func_800198E4));
        if (sp18 != NULL) {
            var_v1 = arg0->posY;
            if (arg0->posX & 4) {
                var_v1 ^= 1;
            }

            sp18->posX = 1;
            sp18->posY = arg1 - 1;
            sp18->rotation = &arg0->unk_30;
            sp18->RentalSlotAnimData_PosePhase = 0;
            sp18->unk_0C = 0;
            sp18->unk_10 = arg0->rotation[var_v1];
            sp18->unk_14 = 0x3C000;
            sp18->unk_18 = arg2;

            if ((arg0->unk_24 != NULL) && (arg0->unk_24->posX == arg1) && (arg0->unk_2C.raw == sp18->unk_18.raw)) {
                osSendMesg(sp18->rotation, sp18, 1);
            } else {
                osSendMesg(&gAssetManager.requestQueue, sp18, 1);
            }

            arg0->TrainerSlotSaveData_GamePort |= 1;
            sp1C = 1;
        }
    }

    return sp1C;
}

s32 PokeIcon_RequestFrameLoadToSlot(AssetManager* arg0, u16 arg1, arg1_func_80010CA8 arg2, s16 arg3) {
    if ((arg0->posX & 8) && !(arg0->TrainerSlotSaveData_GamePort & 1)) {
        arg0->posY = arg3;
        PokeIcon_RequestFrameLoad(arg0, arg1, arg2);
    }
    return 0;
}

s32 PokeIcon_RequestBackgroundLoad(AssetManager* arg0, s32 arg1, s32 arg2) {
    s32 sp1C = 0;
    sp18_func_800198E4* temp_v0;

    if ((arg0->posX & 2) && !(arg0->TrainerSlotSaveData_GamePort & 2)) {
        temp_v0 = Util_Malloc(sizeof(sp18_func_800198E4));
        if (temp_v0 != NULL) {
            temp_v0->posX = 2;
            temp_v0->posY = 0;
            temp_v0->rotation = &arg0->unk_50;
            temp_v0->RentalSlotAnimData_PosePhase = arg2;
            temp_v0->unk_0C = arg1;
            temp_v0->unk_10 = arg0->unk_18;
            temp_v0->unk_14 = 0x18000;

            osSendMesg(&gAssetManager.requestQueue, temp_v0, 1);

            sp1C = 1;
            arg0->TrainerSlotSaveData_GamePort |= 2;
        }
    }

    return sp1C;
}

s32 PokeIcon_ApplyLoadResult(AssetManager* arg0, sp18_func_800198E4* arg1) {
    s32 sp1C = 0;

    switch (arg1->posX) {
        case 1:
            arg0->TrainerSlotSaveData_GamePort &= ~1;
            if (arg1->RentalSlotAnimData_PosePhase != 0) {
                if (arg0->posX & 4) {
                    arg0->posY ^= 1;
                }
                arg0->unk_24 = arg1->RentalSlotAnimData_PosePhase;
                arg0->unk_1C = arg1->unk_14;
                arg0->unk_2C = arg1->unk_18;
            }
            sp1C = 1;
            break;

        case 2:
            arg0->TrainerSlotSaveData_GamePort &= ~2;
            arg0->unk_28 = arg1->RentalSlotAnimData_PosePhase;
            arg0->unk_20 = arg1->unk_14;
            sp1C = 1;
            break;
    }

    Util_Free(arg1);
    return sp1C;
}

s32 PokeIcon_PollFrameLoad(AssetManager* arg0) {
    sp18_func_800198E4* sp1C;
    s32 sp18 = 0;

    if (osRecvMesg(&arg0->unk_30, &sp1C, 0) != -1) {
        sp18 = PokeIcon_ApplyLoadResult(arg0, sp1C);
    }

    return sp18;
}

s32 PokeIcon_PollBackgroundLoad(AssetManager* arg0) {
    OSMesg sp1C;
    s32 sp18 = 0;

    if (osRecvMesg(&arg0->unk_50, &sp1C, 0) != -1) {
        sp18 = PokeIcon_ApplyLoadResult(arg0, sp1C);
    }

    return sp18;
}

s32 PokeIcon_WaitFrameLoad(AssetManager* arg0) {
    OSMesg sp1C;

    osRecvMesg(&arg0->unk_30, &sp1C, 1);
    return PokeIcon_ApplyLoadResult(arg0, sp1C);
}

s32 PokeIcon_WaitBackgroundLoad(AssetManager* arg0) {
    OSMesg sp1C;

    osRecvMesg(&arg0->unk_50, &sp1C, 1);
    return PokeIcon_ApplyLoadResult(arg0, sp1C);
}

ModelData* Model_LoadByArchiveIndex(s32 arg0) {
    Fragment* sp2C;
    arg1_func_80010CA8 sp28;
    ModelData* sp24 = NULL;
    MemoryBlock* sp20;

    sp2C = BinArchive_GetFile(gAssetManager.modelArchives.posX, arg0 - 1);
    if (sp2C != NULL) {
        sp20 = MainPool_AllocState(main_pool_get_available(), 0);
        sp28.raw = 0;
        sp24 = Fragment_ProcessGeoLayout(sp20, sp2C, sp28);
        MainPool_FinalizeAllocation(sp20);
    }

    return sp24;
}

ModelData* Model_LoadForPokemon(PokemonData* arg0) {
    Fragment* sp2C;
    arg1_func_80010CA8 sp28;
    ModelData* sp24 = NULL;
    MemoryBlock* sp20;

    sp2C = BinArchive_GetFile(gAssetManager.modelArchives.posX, arg0->posX.posX - 1);
    if (sp2C != NULL) {
        sp20 = MainPool_AllocState(main_pool_get_available(), 0);
        Model_ComputeMonSizeFromNickname(&sp28, arg0);
        sp24 = Fragment_ProcessGeoLayout(sp20, sp2C, sp28);
        MainPool_FinalizeAllocation(sp20);
    }
    return sp24;
}

s32 Model_LoadWithScale(s32 arg0, s32 arg1) {
    Fragment* sp2C;
    arg1_func_80010CA8 sp28;
    s32 sp24 = 0;
    MemoryBlock* sp20;

    sp2C = BinArchive_GetFile(gAssetManager.modelArchives.posX, arg0 - 1);
    if (sp2C != NULL) {
        sp20 = MainPool_AllocState(main_pool_get_available(), 0);
        sp28.raw = 0;
        sp28.posX = arg1 * 64;
        sp24 = Fragment_ProcessGeoLayout(sp20, sp2C, sp28);
        MainPool_FinalizeAllocation(sp20);
    }
    return sp24;
}

arg1_func_80019420* BattleAnim_LoadResourceTable(s32 arg0) {
    Fragment* sp24;
    arg1_func_80019420* sp20;
    MemoryBlock* sp1C;

    sp20 = NULL;
    sp24 = BinArchive_GetFile(gAssetManager.modelArchives.rotation, arg0);
    if (sp24 != NULL) {
        sp1C = MainPool_AllocState(main_pool_get_available(), 0);
        sp20 = sp24->data;
        Fragment_ProcessGeoLayoutList(sp1C, sp20);
        MainPool_FinalizeAllocation(sp1C);
    }
    return sp20;
}

Fragment* Fragment_LoadAndRelocateFromRomRange(MainPoolState* arg0, u32 arg1, s32 arg2, s32 arg3, PERSSZP* arg4, s32 arg5) {
    Fragment* sp24 = Fragment_LoadFromRomRange(arg0, arg2, arg3, arg4, arg5);

    if (sp24 != NULL) {
        Fragment_RelocateAndCommit(arg0, arg1, sp24);
    }
    return sp24;
}
