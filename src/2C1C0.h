#ifndef _2C1C0_H_
#define _2C1C0_H_

#include "global.h"
#include "29BA0.h"

extern u8 gBattleTimerLimits[3];

void Battle_ResetSideState(unk_D_800AE540_1194* arg0);
void Battle_Init(s32 arg0, s32 arg1, s32 arg2);
void Battle_ClearSelectedMonIndices(void);
unk_D_800AE540_0004* RegisterPlayer(s32 arg0, s16 arg1, char* arg2, char* arg3);
void Battle_RegisterPlayerEntry(s32 arg0, unk_D_800AE540_0004* arg1);
void Battle_AddPartyMon(unk_D_800AE540_0004* arg0, unk_func_80026268_arg0* arg1);
unk_func_80026268_arg0* Pokemon_InitFromSpeciesLevel(unk_func_80026268_arg0* arg0, u8 arg1, s16 arg2);
void Battle_CreateTwoPlayerMatch(s16 arg0, s16 arg1, s16 arg2, s16 arg3);
void Battle_LoadTeamFromSaveSlot(s32 arg0, s32 arg1, s32 arg2);
void Battle_StartRentalBattle(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 Battle_IsMonIndexSelected(s32 arg0);
s32 Battle_PickRandomMon(s32 arg0);
s16 Battle_GetMaxPartyLevel(void);
void Battle_SetPartyLevel(s16 arg0);
void Battle_LoadPartyFromArchive(s16 arg0, s16 arg1, s16 arg2, s32 arg3);
void Battle_InitializeFromMode(void);
void Battle_StartVersusMode(s16 arg0);
void Battle_PackStateForSave(void);
s32 Battle_LoadStateFromSave(void);

#endif // _2C1C0_H_
