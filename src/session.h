#ifndef _2C1C0_H_
#define _2C1C0_H_

#include "global.h"
#include "src/game_state.h"

extern u8 gBattleTimerLimits[3];

void Team_ClearTrainerSlot(BattlePokemon* arg0);
void Session_SetMode(s32 arg0, s32 arg1, s32 arg2);
void Team_ResetOpponentHistory(void);
BattleAI_TeamContext* Trainer_Create(s32 arg0, s16 arg1, char* arg2, char* arg3);
void Team_AddTrainer(s32 arg0, BattleAI_TeamContext* arg1);
void Trainer_AddPokemon(BattleAI_TeamContext* arg0, PokemonData* arg1);
PokemonData* Pokemon_CreateDefault(PokemonData* arg0, u8 arg1, s16 arg2);
void Session_SetupDemoBattle(s16 arg0, s16 arg1, s16 arg2, s16 arg3);
void Team_AddDeckTrainer(s32 arg0, s32 arg1, s32 arg2);
void Team_BuildDeckOpponents(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 Team_IsOpponentIndexUsed(s32 arg0);
s32 Team_PickRandomOpponentIndex(s32 arg0);
s16 Team_GetHighestPartyLevel(void);
void Team_ScaleOpponentToLevel(s16 arg0);
void Team_LoadPresetTrainer(s16 arg0, s16 arg1, s16 arg2, s32 arg3);
void Team_LoadOpponentPreset(void);
void Team_BuildQuickBattleTeams(s16 arg0);
void Session_SaveContinueData(void);
s32 Session_LoadContinueData(void);

#endif // _2C1C0_H_
