#ifndef _232C0_H_
#define _232C0_H_

#include "global.h"
#include "memory.h"
#include "29BA0.h"
#include "2D340.h"
#include "22630.h"

typedef enum {
    POKEMON_ROM_NONE = 0,
    POKEMON_ROM_RED = 1,
    POKEMON_ROM_GREEN = 2,
    POKEMON_ROM_BLUE = 3,
    POKEMON_ROM_YELLOW = 7,
} PokemonRomType;

typedef struct func_800253F4_arg1 {
    /* 0x000 */ u8 unk_000;
    /* 0x001 */ u8 unk_001;
    /* 0x002 */ u16 unk_002;
    /* 0x004 */ char unk_004[11];
    /* 0x00F */ unk_D_800AC910_050_9AC unk_00F;
} func_800253F4_arg1; // size >= 0x1A3

typedef struct unk_func_800228F0 {
    /* 0x00 */ u8 unk_00;
    /* 0x01 */ u8 unk_01;
    /* 0x02 */ u16 unk_02;
    /* 0x04 */ char unk_04[16];
    /* 0x14 */ char unk_14[16];
} unk_func_800228F0; // size >= 0x28

u16 CalculateLevelFromExperience(s32 arg0, u32 arg1);
void ApplyPPUps(PokemonData* arg0);
void SetMonNickname(PokemonData* arg0);
s32 LoadPokemonNameData(unk_func_800228F0*, u16);
void SavePokemonNameData(PokemonData* arg0, s16 arg1, u8 arg2);
s32 IsPokemonNameMatch(u16* arg0, Gen1StringDecodeBuffer* arg1);
u8 GetPokemonType1(s32 arg0);
u8 GetPokemonBaseStat(s32 arg0);
s32 GetPokemonFormId(s32 arg0);
u8 GetPokemonMoveData(s32 arg0);
u8 GetPokemonEvolutionData(s32 arg0);
s32 GetPokemonEggGroup(s32 arg0);
s32 GetPokemonGrowthRate(s32 arg0);
void GbsBlock_InitStandard(unk_func_80022C28_ret* arg0);
void GbsBlock_InitExtended(unk_func_80022C28_ret* arg0);
unk_func_80022C28_ret* CreateGbsBlock(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
unk_func_80022C28_ret* GbsBlock_CreateWithString(s32 arg0, s32 arg1, s32 arg2, s32 arg3, char* arg4, u16 arg5);
s32 InvalidateAndFreeGbsBlock(unk_func_80022C28_ret* arg0);
s32 CommitAndFreeGbsBlock(unk_func_80022C28_ret* arg0);
s32 GbsBlock_SetLimit(unk_func_80022C28_ret*, s32);
s32 GbsBlock_ReadPokemon(u8* arg0, s32 arg1, unk_func_80022C28_ret* arg2);
s32 GbsBlock_WriteEntries(u8* arg0, s32 arg1, unk_func_80022C28_ret* arg2);
void LoadNameSlots(void);
char* GetNameSlot(s32 arg0);
s32 IsPokemonSave(u8* arg0);
s32 ValidateChecksum(u8* arg0, u8* arg1);
void ComputeChecksum(u8* arg0, u8* arg1);
s32 VerifySaveData(u8* arg0, s32 arg1);
s8 DetectPokemonRom(s32 arg0);
s32 VerifySaveChecksum(s32 arg0);
s32 LoadAndVerifySave(s32 arg0);
s32 SaveAndVerifyFooter(s32 arg0);
s32 ReadSaveBoxData(s32 arg0, s32 arg1);
s32 WriteAndVerifyBoxData(s32 arg0, s32 arg1);
void PlayerSave_PoolFreeCallback(UNUSED MainPoolBlock* arg0, u32 arg1);
void VerifySaveFlag(s32 arg0);
s32 PlayerSave_InitAndLoad(s32 arg0);
s32 SaveSlot_Load(s32 arg0);
s32 PlayerSave_LoadBoxes(s32 arg0);
s32 SnapSelect_SetCameraMode(s32 arg0);
s32 PlayerSave_UpdateState(s32 arg0);
void PlayerSave_Refresh(s32 arg0);
void PlayerSave_RequestRefresh(s32 arg0);
s32 InitializePlayers(void);
void SetSaveDirtyFlag(s32 arg0);
s32 PlayerSave_WriteBoxes(s32 arg0);
s32 PlayerSave_WriteHeader(s32 arg0);
s32 PlayerSave_FullSave(s32 arg0);
void PlayerSave_VerifyPresence(s32 arg0);
void PlayerSave_PowerOff(s32 arg0);
unk_D_800AC910_050_B40_000* GetPokemonRecordPtr(s32 arg0, s32 arg1);
void LoadPartyPokemon(PokemonData* arg0, s32 arg1, s32 arg2);
void SavePartyPokemon(unk_func_88205880_00D0* arg0, s32 arg1, s32 arg2);
void LoadBoxPokemon(PokemonData* arg0, s32 arg1, s32 arg2, s32 arg3);
void SaveBoxPokemon(unk_func_88205880_00D0* arg0, s32 arg1, s32 arg2, s32 arg3);
s32 GetPokemonRecordId(s32 arg0, s32 arg1);
void SetPokemonRecordId(s32 arg0, s32 arg1, s32 arg2);
s32 GetSaveBlockMaxEntries(s32 arg0);
s32 GetSaveBlockEntrySize(s32 arg0);
s32 GetSaveBlockCurrentCount(s32 arg0, s32 arg1, s32 arg2);
void SetSaveBlockCount(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void IncrementSaveBlockCount(s32 arg0, s32 arg1, s32 arg2);
s32 ReadSaveBlockEntry(s32 arg0, s32 arg1, s32 arg2, s32 arg3, PokemonData* arg4);
s32 WriteSaveBlockEntry(s32 arg0, s32 arg1, s32 arg2, s32 arg3, unk_func_88205880_00D0* arg4);
s32 GetActivePlayerMask(void);
s32 MenuItem_GetPokemonSpecies(s32 arg0);
s32 GetPlayerBitmask(s32 arg0);
s32 MenuItem_GetHeldItemId(s32 arg0);
s32 MenuItem_GetPokemonLevel(s32 arg0);
s32 SaveSlot_LoadPokemonData(s32 arg0);
void Controller_ReadInput(s32 arg0, Gen1StringDecodeBuffer* arg1);
s32 SaveSlot_GetPokemonId(s32 arg0);
void SaveSlot_SetPokemonId(s32 arg0, u16 arg1);
s32 SaveSlot_GetPokemonBall(s32 arg0);
char* SaveSlot_GetTrainerName(s32 arg0, char* arg1);
char* SaveSlot_EncodeTrainerName(s32 arg0, char* arg1);
char* SaveSlot_GetNickname(s32 arg0, char* arg1);
char* SaveSlot_EncodeNickname(s32 arg0, char* arg1);
s32 SaveSlot_GetPokemonExperience(s32 arg0);
s32 MenuItem_GetPokemonGender(s32 arg0);
s32 MenuItem_IsPokemonShiny(s32 arg0);
s32 MenuItem_IsPokemonEgg(s32 arg0);
s32 SaveSlot_CopyPokemonStats(s32 arg0, func_800253F4_arg1* arg1);
void MarkPokemonOwned(char* arg0, s32 arg1, u8* arg2);
void SaveSlot_UpdateOwnedPokemonBitmask(s32 arg0);
s32 SaveSlot_CheckPokemonOwned(s32 arg0, s32 arg1);
void SaveSlot_SetPokemonOwned(s32 arg0, s32 arg1, s32 arg2);
s32 SaveSlot_CountOwnedPokemon1(s32 arg0);
s32 SaveSlot_CountOwnedPokemon2(s32 arg0);
s32 SaveSlot_CountOwnedPokemon3(s32 arg0);

#endif // _232C0_H_
