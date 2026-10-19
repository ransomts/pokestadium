#ifndef _FRAGMENT38_H_
#define _FRAGMENT38_H_

#include "global.h"
#include "src/game_state.h"

typedef struct EventBattleState {
    /* 0x00 */ u8 posX;
    /* 0x01 */ u8 TrainerSlotSaveData_GamePort;
    /* 0x02 */ s16 posY;
    /* 0x04 */ s16 rotation;
    /* 0x06 */ s16 unk_06;
} EventBattleState; // size = 0x8

typedef struct RuleCard {
    /* 0x00 */ u8 posX;
    /* 0x01 */ u8 TrainerSlotSaveData_GamePort;
    /* 0x02 */ s16 posY;
    /* 0x04 */ s16 rotation;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ s16 RentalSlotAnimData_PosePhase;
    /* 0x0A */ s16 unk_0A;
    /* 0x0C */ u8* unk_0C;
    /* 0x10 */ char* unk_10;
    /* 0x14 */ s16 unk_14;
    /* 0x16 */ s16 unk_16;
    /* 0x18 */ s16 unk_18;
} RuleCard; // size = 0x1C

typedef struct AnimState {
    /* 0x00 */ u8 posX;
    /* 0x01 */ u8 TrainerSlotSaveData_GamePort;
    /* 0x02 */ s16 posY;
    /* 0x04 */ s16 rotation;
    /* 0x06 */ s16 unk_06;
} AnimState; // size = 0x8

typedef struct BattleSettings {
    /* 0x00 */ u8 posX;
    /* 0x00 */ u8 TrainerSlotSaveData_GamePort;
    /* 0x02 */ s16 posY;
    /* 0x04 */ s16 rotation;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ s16 RentalSlotAnimData_PosePhase;
    /* 0x0A */ s16 unk_0A;
    /* 0x0C */ s16 unk_0C;
} BattleSettings; // size = 0x10

typedef struct TrainerCard {
    /* 0x0000 */ u8 unk_0000;
    /* 0x0001 */ u8 unk_0001;
    /* 0x0002 */ u8 unk_0002;
    /* 0x0003 */ u8 unk_0003;
    /* 0x0004 */ s16 unk_0004;
    /* 0x0006 */ s16 slideProgress;
    /* 0x0008 */ s16 unk_0008;
    /* 0x000A */ s16 baseY;
    /* 0x000C */ s16 unk_000C;
    /* 0x000E */ s16 unk_000E;
    /* 0x0010 */ s16 unk_0010;
    /* 0x0012 */ u16 unk_0012;
    /* 0x0014 */ char unk_0014[4];
    /* 0x0018 */ char unk0018[0x8];
    /* 0x0020 */ PokemonData party[6];
    /* 0x0218 */ u8 iconTextures[6][0xC80];
} TrainerCard; // size = 0x4D18

typedef struct OptionLabel {
    /* 0x00 */ u8 posX;
    /* 0x02 */ s16 posY;
    /* 0x04 */ s16 rotation;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ char* RentalSlotAnimData_PosePhase;
} OptionLabel; // size = 0x0C

typedef struct unk_D_82305920 {
    /* 0x00 */ s16 posX;
    /* 0x02 */ s16 posY;
    /* 0x04 */ s16 rotation;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ s16 RentalSlotAnimData_PosePhase;
} unk_D_82305920; // size = 0xA

typedef struct unk_D_82305978 {
    /* 0x00 */ s16 posX;
    /* 0x02 */ s16 posY;
    /* 0x04 */ s16 rotation;
    /* 0x06 */ s16 unk_06;
} unk_D_82305978; // size = 0x8

u8 EventBattle_CheckTeamLegality(TrainerCard* arg0, s16 arg1);

#endif // _FRAGMENT38_H_
