#ifndef _19840_H_
#define _19840_H_

#include "global.h"
#include "src/3FB0.h"
#include "src/F420.h"
#include "src/1C720.h"
#include "src/29BA0.h"

typedef struct unk_func_80019600 {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ OSMesgQueue* queue;
    /* 0x08 */ void* unk_08;
    /* 0x0C */ void* unk_0C;
    /* 0x10 */ MainPoolState* pool;
    /* 0x14 */ s32 size;
    /* 0x18 */ arg1_func_80010CA8 unk_18;
} unk_func_80019600; // size >= 0x1C

typedef struct sp18_func_800198E4 {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ u16 unk_02;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ s32 unk_10;
    /* 0x14 */ s32 unk_14;
    /* 0x18 */ arg1_func_80010CA8 unk_18;
} sp18_func_800198E4; // size = 0x1C

typedef struct unk_D_800ABE10_A04 {
    /* 0x00 */ BinArchive* unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ BinArchive* unk_10;
} unk_D_800ABE10_A04; // size >= 0x14

typedef struct unk_D_800ABE10 {
    /* 0x000 */ OSThread unk_000;
    /* 0x1B0 */ char unk1B0[0x800];
    /* 0x9B0 */ OSMesg unk_9B0;
    /* 0x9B4 */ char unk9B4[0x1C];
    /* 0x9D0 */ OSMesgQueue unk_9D0;
    /* 0x9E8 */ OSMesg unk_9E8;
    /* 0x9EC */ OSMesgQueue unk_9EC;
    /* 0xA04 */ unk_D_800ABE10_A04 unk_A04;
} unk_D_800ABE10; // size >= 0xA18

extern unk_D_800ABE10 gAssetManager;

void GeoLayout_ConvertTextures(unk_D_86002F34* arg0, arg1_func_80010CA8 arg1);
Fragment* Fragment_LoadPresJpeg(MemoryBlock* arg0, PRESJPEG* arg1, PRESJPEG* arg2);
Fragment* Fragment_LoadPersSzp(MainPoolState* arg0, PERSSZP* arg1, PERSSZP* arg2);
Fragment* Fragment_LoadRaw(MainPoolState* arg0, PERSSZP* arg1, s32 arg2, u32 arg3);
Fragment* Fragment_LoadFromRange(MainPoolState* arg0, s32 start, s32 end, PERSSZP* arg3, s32 arg4);
Fragment* Fragment_LoadCompressed(MainPoolState* arg0, unk_func_800041C0* arg1, PERSSZP* arg2, u32 arg3);
void Fragment_Relocate(MainPoolState* arg0, u32 arg1, Fragment* arg2);
Fragment* Fragment_LoadFromArchive(MainPoolState* arg0, BinArchive* arg1, BinArchiveFile* arg2, u32 arg3, s32 arg4);
Fragment* Fragment_LoadFromArchive2(MainPoolState* arg0, BinArchive* arg1, BinArchiveFile* arg2, u32 arg3, s32 arg4);
Fragment* Fragment_LoadFromFile(MainPoolState* arg0, BinArchive* arg1, s32 arg2, u32 arg3, s32 arg4);
s32 AssetGroup_CreateFromFragment(MemoryBlock* arg0, Fragment* arg1, arg1_func_80010CA8 arg2);
void GeoLayout_ProcessList(MemoryBlock* arg0, arg1_func_80019420* arg1);
void AssetLoader_LoadInitial(unk_func_80019600* arg0);
void AssetLoader_LoadAdditional(unk_func_80019600* arg0);
void AssetLoader_ThreadMain(UNUSED void* arg0);
void Sched_InitThreads(void);
AssetManager* AssetManager_Create(u32 arg0);
void AssetManager_LoadArchives(void);
s32 AssetManager_RequestLoad(AssetManager* arg0, u16 arg1, arg1_func_80010CA8 arg2);
s32 PokeIcon_RequestFrameLoadWithVariant(AssetManager* arg0, u16 arg1, arg1_func_80010CA8 arg2, s16 arg3);
s32 PokeIcon_RequestBackgroundLoad(AssetManager* arg0, s32 arg1, s32 arg2);
s32 AssetManager_HandleRequest(AssetManager* arg0, sp18_func_800198E4* arg1);
s32 AssetManager_TryProcessLoadQueue(AssetManager* arg0);
s32 PokeIcon_PollBackgroundLoad(AssetManager* arg0);
s32 AssetManager_WaitLoadQueue(AssetManager* arg0);
s32 PokeIcon_WaitBackgroundLoad(AssetManager* arg0);
unk_D_86002F30* GeoLayout_LoadById(s32 arg0);
unk_D_86002F30* Model_LoadForPokemon(PokemonData* arg0);
s32 Model_LoadWithScale(s32 arg0, s32 arg1);
arg1_func_80019420* BattleAnim_LoadResourceTable(s32 arg0);
Fragment* Fragment_LoadAndRelocateFromRomRange(MainPoolState* arg0, u32 arg1, s32 arg2, s32 arg3, PERSSZP* arg4, s32 arg5);


#endif // _19840_H_
