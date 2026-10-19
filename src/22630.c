#include "22630.h"
#include "include/string.h"
#include "src/22630.h"
#include "src/26820.h"
#include "src/2E110.h"
#include "src/gb_tower.h"
#include "src/hal_libc.h"
#include "src/util.h"

u16 GbData_ReadU16BE(u8* arg0) {
    return (arg0[0] << 8) | arg0[1];
}

u32 GbData_ReadU24BE(u8* arg0) {
    return (arg0[0] << 0x10) | (arg0[1] << 8) | arg0[2];
}

void GbData_WriteU16BE(u8* arg0, s32 arg1) {
    arg0[0] = (arg1 >> 8) & 0xFF;
    arg0[1] = arg1 & 0xFF;
}

void GbData_WriteU24BE(u8* arg0, s32 arg1) {
    arg0[0] = (arg1 >> 0x10) & 0xFF;
    arg0[1] = (arg1 >> 8) & 0xFF;
    arg0[2] = (arg1) & 0xFF;
}

char* Text_UntranscodeName(char* arg0, char* arg1) {
    extern s8 gGen1DecodeTable[];

    char* sp34 = arg0;
    char* sp18;
    char* temp_s1 = Text_GetPlayerLabel(1);

    while (*arg1 != 'P') {
        if (*arg1 == ']') {
            memcpy(arg0, temp_s1, strlen(temp_s1) + 1);
            arg0 += strlen(temp_s1);
        } else {
            *arg0++ = gGen1DecodeTable[*arg1];
        }
        arg1++;
    }

    *arg0++ = '\x0';

    return sp34;
}

void Text_UntranscodeNameWrapper(char* arg0, char* arg1) {
    Text_UntranscodeName(arg0, arg1);
}

char* Text_TranscodeName(char* arg0, char* arg1) {
    extern u8 gGen1EncodeTable[];

    char* sp1C = arg0;
    char* sp18 = arg1;

    if (HAL_Strcmp(sp18, Text_GetPlayerLabel(1)) == 0) {
        *arg0++ = ']';
    } else {
        while (*sp18 != 0) {
            *arg0++ = gGen1EncodeTable[*sp18++];
        }
    }

    *arg0++ = 'P';

    return sp1C;
}

char* Text_TranscodeNameWrapper(char* arg0, char* arg1) {
    return Text_TranscodeName(arg0, arg1);
}

char* Text_UntranscodeFixedName(char* arg0, char* arg1) {
    char sp1C[11];

    _bcopy(arg1, sp1C, 0xA);

    sp1C[10] = 'P';

    return Text_UntranscodeName(arg0, sp1C);
}

char* Text_CopyString(char* arg0, char* arg1) {
    HAL_Strcpy(arg0, arg1);
    return arg0;
}

char* Text_CopySpeciesName(char* arg0, s32 arg1) {
    Text_CopyString(arg0, (char*)*(u32*)D_8006FEE8[arg1]);
    return arg0;
}

char* GetItemName(s32 arg0, char* arg1) {
    extern char* gItemNames[];
    // "ひでんマシン%02d"
    static const char gHiddenMachineFormat[] = { 0xA4, 0xD2, 0xA4, 0xC7, 0xA4, 0xF3, 0xA5, 0xDE, 0xA5, 0xB7,
                                       0xA5, 0xF3, 0x25, 0x30, 0x32, 0x64, 0x00, 0x00, 0x00, 0x00 };
    // "わざマシン%02d"
    static const char gMoveMachineFormat[] = { 0xA4, 0xEF, 0xA4, 0xB6, 0xA5, 0xDE, 0xA5, 0xB7,
                                       0xA5, 0xF3, 0x25, 0x30, 0x32, 0x64, 0x00, 0x00 };

    if ((arg0 > 0) && (arg0 < 0x54)) {
        HAL_Strcpy(arg1, gItemNames[arg0 - 1]);
    } else if ((arg0 >= 0xC4) && (arg0 < 0xC9)) {
        sprintf(arg1, gHiddenMachineFormat, arg0 - 0xC3, arg0);
    } else if ((arg0 >= 0xC9) && (arg0 < 0xFF)) {
        sprintf(arg1, gMoveMachineFormat, arg0 - 0xC8, arg0);
    } else {
        HAL_Strcpy(arg1, gItemNames[6]);
    }

    return arg1;
}

void Pokemon_FromGbRecord(PokemonData* arg0, unk_D_800AE4E8_004_1_000_010_000* arg1) {
    arg0->posX.posX = Species_FromInternalIndex(arg1->posX);
    arg0->posX.unk_01 = arg1->posX;
    arg0->posY = GbData_ReadU16BE(arg1->unk_01);

    arg0->rotation = arg1->unk_03;
    arg0->unk_05 = arg1->rotation;
    arg0->unk_06 = arg1->unk_05;
    arg0->unk_07 = arg1->unk_06;
    arg0->unk_08 = arg1->unk_07;

    arg0->unk_0E = GbData_ReadU16BE(arg1->unk_0C);
    arg0->unk_10 = GbData_ReadU24BE(arg1->unk_0E);
    arg0->unk_14 = GbData_ReadU16BE(arg1->unk_11);
    arg0->unk_16 = GbData_ReadU16BE(arg1->unk_13);
    arg0->unk_18 = GbData_ReadU16BE(arg1->unk_15);
    arg0->unk_1A = GbData_ReadU16BE(arg1->unk_17);
    arg0->unk_1C = GbData_ReadU16BE(arg1->unk_19);
    arg0->unk_1E = GbData_ReadU16BE(arg1->unk_1B);

    memcpy(arg0->unk_09, arg1->unk_08, 4);
    memcpy(arg0->unk_20, arg1->unk_1D, 4);
}

void Pokemon_FromGbRecordExt(PokemonData* arg0, unk_D_800AC910_050_9AC_008* arg1) {
    Pokemon_FromGbRecord(arg0, &arg1->posX);
    arg0->unk_24 = arg1->unk_21;
    arg0->unk_26 = GbData_ReadU16BE(&arg1->unk_22);
    arg0->unk_28 = GbData_ReadU16BE(&arg1->unk_24);
    arg0->unk_2A = GbData_ReadU16BE(&arg1->unk_26);
    arg0->unk_2C = GbData_ReadU16BE(&arg1->unk_28);
    arg0->unk_2E = GbData_ReadU16BE(&arg1->unk_2A);
}

void Pokemon_ToGbRecord(PokemonData* arg0, unk_D_800AE4E8_004_1_000_010_000* arg1) {
    if (Species_ToInternalIndex(arg0->posX.posX) & 0xFF) {
        arg1->posX = Species_ToInternalIndex(arg0->posX.posX);
    } else {
        arg1->posX = arg0->posX.unk_01;
    }

    GbData_WriteU16BE(arg1->unk_01, (u16)arg0->posY);

    arg1->unk_03 = arg0->rotation;
    arg1->rotation = arg0->unk_05;
    arg1->unk_05 = arg0->unk_06;
    arg1->unk_06 = arg0->unk_07;
    arg1->unk_07 = arg0->unk_08;

    GbData_WriteU16BE(arg1->unk_0C, arg0->unk_0E);
    GbData_WriteU24BE(arg1->unk_0E, arg0->unk_10);
    GbData_WriteU16BE(arg1->unk_11, arg0->unk_14);
    GbData_WriteU16BE(arg1->unk_13, arg0->unk_16);
    GbData_WriteU16BE(arg1->unk_15, arg0->unk_18);
    GbData_WriteU16BE(arg1->unk_17, arg0->unk_1A);
    GbData_WriteU16BE(arg1->unk_19, arg0->unk_1C);
    GbData_WriteU16BE(arg1->unk_1B, arg0->unk_1E);

    memcpy(arg1->unk_08, arg0->unk_09, 4);
    memcpy(arg1->unk_1D, arg0->unk_20, 4);
}

void Pokemon_ToGbRecordExt(unk_func_88205880_00D0* arg0, unk_D_800AC910_050_9AC_008* arg1) {
    Pokemon_ToGbRecord(arg0->unk_000, arg1);
    arg1->unk_21 = arg0->unk_000[0].unk_24;
    GbData_WriteU16BE(&arg1->unk_22, arg0->unk_000[0].unk_26);
    GbData_WriteU16BE(&arg1->unk_24, arg0->unk_000[0].unk_28);
    GbData_WriteU16BE(&arg1->unk_26, arg0->unk_000[0].unk_2A);
    GbData_WriteU16BE(&arg1->unk_28, arg0->unk_000[0].unk_2C);
    GbData_WriteU16BE(&arg1->unk_2A, arg0->unk_000[0].unk_2E);
}

u16 StatExpSqrt(u16 arg0) {
    u16 i;

    for (i = 1; i < 255; i++) {
        if (SQ(i) >= arg0) {
            break;
        }
    }
    return i;
}

void func_800220C4(void) {
}

u16 GetPokemonDV(s32 statId, u16 dvBits) { //GetPokemonDV
    u16 dvValue;

    switch (statId) {
        case STAT_HP: // HP DV (derived from the LSBs of other DVs)
            dvValue = ((dvBits & 0x1000) >> 9)  // Special DV bit 0 → HP DV bit 0
                    | ((dvBits & 0x0100) >> 6)  // Speed DV bit 0 → HP DV bit 1
                    | ((dvBits & 0x0010) >> 3)  // Defense DV bit 0 → HP DV bit 2
                    | (dvBits & 0x0001);        // Attack DV bit 0 → HP DV bit 3
            break;

        case STAT_SPECIAL: // Special DV
            dvValue = (dvBits >> 12) & 0xF;
            break;

        case STAT_SPEED: // Speed DV
            dvValue = (dvBits >> 8) & 0xF;
            break;

        case STAT_DEFENSE: // Defense DV
            dvValue = (dvBits >> 4) & 0xF;
            break;

        case STAT_ATTACK: // Attack DV
            dvValue = dvBits & 0xF;
            break;
    }

    return dvValue;
}

u32 CalculateStatValue(s32 statId, s32 speciesId, u16 statModifier, u16 level, u16 dvBits) {
    u16 statValue;
    u16 baseStat;
    u16 dvValue;

    switch (statId) {
        case STAT_HP:
            baseStat = D_80070F84[speciesId].baseHP;
            break;
        case STAT_SPECIAL:
            baseStat = D_80070F84[speciesId].baseSpecial;
            break;
        case STAT_SPEED:
            baseStat = D_80070F84[speciesId].baseSpeed;
            break;
        case STAT_DEFENSE:
            baseStat = D_80070F84[speciesId].baseDefense;
            break;
        case STAT_ATTACK:
            baseStat = D_80070F84[speciesId].baseAttack;
            break;
    }

    // Get the Pokémon's DV for the stat (or HP DV)
    dvValue = GetPokemonDV(statId, dvBits);

    // Compute the preliminary stat value
    statValue = (((StatExpSqrt(statModifier) / 4) + ((baseStat + dvValue) * 2)) * level) / 100;

    // Add final adjustments
    if (statId == STAT_HP) {
        statValue += level + 10;
    } else {
        statValue += 5;
    }

    // Cap at 999
    if (statValue > 999) {
        statValue = 999;
    }

    return statValue;
}

void Pokemon_RecalcStats(PokemonData* arg0) {
    arg0->unk_24 = Pokemon_LevelFromExp(arg0->posX.posX, arg0->unk_10);
    arg0->unk_26 = CalculateStatValue(1, arg0->posX.posX, arg0->unk_14, arg0->unk_24, arg0->unk_1E);
    arg0->unk_28 = CalculateStatValue(2, arg0->posX.posX, arg0->unk_16, arg0->unk_24, arg0->unk_1E);
    arg0->unk_2A = CalculateStatValue(3, arg0->posX.posX, arg0->unk_18, arg0->unk_24, arg0->unk_1E);
    arg0->unk_2C = CalculateStatValue(4, arg0->posX.posX, arg0->unk_1A, arg0->unk_24, arg0->unk_1E);
    arg0->unk_2E = CalculateStatValue(5, arg0->posX.posX, arg0->unk_1C, arg0->unk_24, arg0->unk_1E);
}

u16 Pokemon_StatExpForTarget(s32 arg0, s32 arg1, u16 arg2, u16 arg3, u16 arg4) {
    s32 i;
    s32 tmp;

    for (i = 1; i < 0xFFFF; i += 2) {
        tmp = CalculateStatValue(arg0, arg1, i + 2, arg3, arg4);
        if (arg2 < tmp) {
            break;
        }
    }

    return i;
}

u32 Pokemon_ExpForLevel(s32 arg0, u16 arg1) {
    u32 sp4;

    switch (D_80070F84[arg0].unk_13) {
        case 0:
            sp4 = arg1 * arg1 * arg1;
            break;

        case 1:
            sp4 = (((arg1 * arg1 * arg1 * 3) / 4) + (arg1 * 0xA * arg1)) - 0x1E;
            break;

        case 2:
            sp4 = (((arg1 * arg1 * arg1 * 3) / 4) + (arg1 * 0x14 * arg1)) - 0x1E;
            break;

        case 3:
            sp4 = ((((arg1 * arg1 * arg1 * 6) / 5) - (arg1 * 0xF * arg1)) + (arg1 * 0x64)) - 0x8C;
            break;

        case 4:
            sp4 = (arg1 * arg1 * arg1 * 4) / 5;
            break;

        case 5:
            sp4 = (arg1 * arg1 * arg1 * 5) / 4;
            break;
    }

    return sp4;
}
