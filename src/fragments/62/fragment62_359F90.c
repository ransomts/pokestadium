#include "fragment62.h"
#include "src/22630.h"
#include "src/2E110.h"
#include "src/F420.h"

typedef struct unk_D_843C4DA0 {
    /* 0x00 */ u16 unk_00;
    /* 0x02 */ u8 unk_02;
    /* 0x03 */ u8 unk_03;
    /* 0x04 */ u8 unk_04;
    /* 0x05 */ u8 unk_05;
    /* 0x06 */ char unk06[0x3];
    /* 0x09 */ u8 unk_09;
    /* 0x0A */ char unk0A[0xA];
    /* 0x13 */ u8 unk_13;
    /* 0x14 */ char unk14[0x1];
    /* 0x15 */ u8 unk_15;
    /* 0x16 */ char unk16[0x1];
    /* 0x17 */ u8 unk_17;
    /* 0x18 */ char unk18[0xB];
    /* 0x22 */ u8 unk_22;
    /* 0x24 */ u16 unk_24;
    /* 0x26 */ u16 unk_26;
    /* 0x28 */ u16 unk_28;
    /* 0x2A */ u16 unk_2A;
    /* 0x2C */ u16 unk_2C;
    /* 0x2E */ char unk2E[0x1E];
} unk_D_843C4DA0; // size = 0x4C

static u16 gAccumulatedDamage;
static u8 gAccuracyCheckRandom;
static u8 gBattleMessageFlag;
u8 gSpecialFlag;
u8 gBattleEffectType;
static u8 gBattleUnusedFlag1;
static u8 gBattleUnusedFlag2;
static u8 gBattleUnusedFlag3;
u8 gBattleUnusedFlag4;
u8 gBattleUnusedFlag5;
static u8 gBattleUnusedFlag6;
static u8 gBattleUnusedFlag7;
static u8 gBattleUnusedFlag8;
static u8 gBattleUnusedFlag9;
static u8 gBattleUnusedFlag10;
static u8 gBattleUnusedFlag11;
static u8 gBattleUnusedFlag12;
static u8 gBattleUnusedFlag13;
static u8 gTypeEffectivenessMsgState;
static u8 gBattleUnusedFlag14;
static u8 gBattleUnusedFlag15;
static u8 gBattleUnusedFlag16;
static u8 gBattleUnusedFlag17;
static u8 gBattleUnusedFlag18;
static u8 gBattleUnusedFlag19;
static u8 gBattleUnusedFlag20;
static u8 gBattleUnusedFlag21;
static u8 gBattleUnusedFlag22;
static u8 gBattleUnusedFlag23;
static u8 gBattleUnusedFlag24;
static u8 gBattleUnusedFlag25;
static u8 gBattleUnusedFlag26;
static u8 gBattleUnusedFlag27;
static u8 gMoveEffectIndex;
u16 gCurrentDamage;
static u16 gMovePower;
static u16 gAttackerStat;
static u16 gDefenderStat;
static u16 gAttackerLevel;
static s32 pad_D_843C4DD0;
static s32 pad_D_843C4DD4;
static s32 pad_D_843C4DD8;
static s32 pad_D_843C4DDC;
static s32 pad_D_843C4DE0;
static s32 pad_D_843C4DE4;
static s32 pad_D_843C4DE8;
s32 gAnimTimer;
static s32 pad_D_843C4DF0[21];
u8 gIsBattleMode;
u8 gAnimStateFlag;
static s32 pad_D_843C4E48[252];
unk_D_800FCB18* gCurrentBattleEntity;
unk_D_800FCB18* gDefenderBattleEntity;
static unk_D_800FCB18 gBattleTempEntities[2];

u8 D_8438AC60[] = {
    0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x0E, 0x4A, 0x00, 0x00,
    0x60, 0x69, 0x75, 0x78, 0x85, 0x00, 0x00, 0x00, 0x61, 0x64, 0x66, 0x68, 0x8C, 0x00, 0x00, 0x00,
    0x01, 0x0A, 0x0B, 0x11, 0x13, 0x14, 0x15, 0x1E, 0x22, 0x23, 0x25, 0x27, 0x2B, 0x2C, 0x2D, 0x2E,
    0x2F, 0x40, 0x44, 0x46, 0x47, 0x51, 0x59, 0x5A, 0x5B, 0x5C, 0x67, 0x6A, 0x6B, 0x6E, 0x6F, 0x76,
    0x7A, 0x80, 0x84, 0x8B, 0x8D, 0x91, 0x94, 0x96, 0x97, 0x9A, 0x9C, 0x9F, 0xA3, 0xA4, 0x00, 0x00,
};
static u8 gMoveEffectImmunityList[] = { 1, 0x20, 0x43, 0x54, 0x56 };
StatStageMultiplier gStatStageMultipliers[] = {
    { 0x19, 0x64 }, { 0x1C, 0x64 }, { 0x21, 0x64 }, { 0x28, 0x64 }, { 0x32, 0x64 }, { 0x42, 0x64 }, { 0x01, 0x01 },
    { 0x0F, 0x0A }, { 0x02, 0x01 }, { 0x19, 0x0A }, { 0x03, 0x01 }, { 0x23, 0x0A }, { 0x04, 0x01 },
};
u8 gStatStageMultipliersAlt[] = {
    0x01, 0x03, 0x24, 0x64, 0x2B, 0x64, 0x01, 0x02, 0x42, 0x64, 0x4B, 0x64, 0x01,
    0x01, 0x85, 0x64, 0xA6, 0x64, 0x02, 0x01, 0xE9, 0x64, 0x85, 0x32, 0x03, 0x01,
};
u8 gTypeEffectivenessTable[] = {
    0x15, 0x14, 0x14, 0x14, 0x16, 0x14, 0x14, 0x19, 0x14, 0x16, 0x15, 0x14, 0x17, 0x15, 0x14, 0x15, 5,    0x14,
    4,    2,    0,    0x15, 0x15, 5,    0x14, 0x14, 5,    0x17, 0x17, 5,    0x19, 0x19, 5,    0x16, 0x16, 5,
    0x18, 0x18, 5,    0x14, 0x15, 5,    0x16, 0x14, 5,    0x15, 0x16, 5,    0x17, 0x16, 5,    0,    5,    5,
    0,    8,    0,    8,    8,    0x14, 0x14, 7,    0x14, 0x14, 5,    5,    0x15, 4,    0x14, 0x17, 4,    0,
    0x17, 2,    0x14, 0x16, 4,    0x14, 0x16, 7,    5,    0x16, 3,    5,    0x16, 5,    0x14, 0x16, 2,    5,
    0x19, 0x15, 5,    0x19, 0x16, 0x14, 0x19, 4,    0x14, 0x19, 2,    0x14, 1,    0,    0x14, 1,    3,    5,
    1,    2,    5,    1,    0x18, 5,    1,    7,    5,    1,    5,    0x14, 1,    0x19, 0x14, 1,    8,    0,
    3,    0x16, 0x14, 3,    3,    5,    3,    4,    5,    3,    7,    0x14, 3,    5,    5,    3,    8,    5,
    4,    0x14, 0x14, 4,    0x17, 0x14, 4,    0x16, 5,    4,    7,    5,    4,    5,    0x14, 4,    3,    0x14,
    2,    0x17, 5,    2,    1,    0x14, 2,    7,    0x14, 2,    0x16, 0x14, 2,    5,    5,    0x18, 1,    0x14,
    0x18, 3,    0x14, 7,    0x14, 5,    7,    0x16, 0x14, 7,    1,    5,    7,    2,    5,    7,    0x18, 0x14,
    7,    8,    5,    7,    3,    0x14, 5,    0x14, 0x14, 5,    1,    5,    5,    4,    5,    5,    2,    0x14,
    5,    7,    0x14, 5,    0x19, 0x14, 8,    0,    0,    8,    0x18, 0,    0x14, 0x1A, 5,    0x15, 0x1A, 5,
    0x17, 0x1A, 5,    0x16, 0x1A, 5,    0x19, 0x1A, 0x14, 0x1A, 0x1A, 0x14, 0xFF, 0,    0,
};
static u32 gBattleMoveEffectTable1[] = {
    0x18191C2E,
    0x2F313839,
    0x40414243,
    0x4F525455,
};
static u32 gBattleMoveEffectTable2[] = {
    0x1B000000,
};
static u32 gBattleMoveEffectTable3[] = {
    0x28290000,
};
static u32 gBattleMoveEffectTable4[] = {
    0x010A0B0C, 0x0D0E0F12, 0x13141516, 0x171A2032, 0x33343536, 0x373A3B3C, 0x3D3E3F00,
};
static u32 gBattleMoveEffectTable5[] = {
    0x03070810,
    0x1D1E2C30,
    0x4D510000,
};
static u32 gBattleMoveEffectTable6[] = {
    0x03070810,
    0x111D1E27,
    0x28292B2C,
    0x2D301B00,
};
static s32 gBattleRngSeed1 = 0x4D2;
static u32 gBattleRngSeed2 = 0x1A85;
static u32 gBattleRngSeed3 = 0x3039;
static u32 gBattleRngSeed4 = 0x10932;
static u8 gBattleTypeEffectivenessParams[] = { 2, 0x4B, 0x98, 0xA3 };

void func_8436F6D0(void) {
}

u8 GetRandomU8(void) {
    u8 var_v1;
    s32 ret;

    var_v1 = (osGetCount() & 0xFF0) >> 4;

    while (var_v1 > 0) {
        gBattleRngSeed1 = (gBattleRngSeed1 * 0x41C64E6D) + 0x303B;
        if (gBattleRngSeed2 & 1) {
            gBattleRngSeed2 ^= 0x11020;
        }
        gBattleRngSeed2 >>= 1;
        var_v1--;
    }

    ret = gBattleRngSeed1 ^ gBattleRngSeed2;
    return ret;
}

u8 GetRandomU8_Alt(void) {
    u8 var_v1;
    s32 ret;

    var_v1 = (osGetCount() & 0xFF0) >> 4;

    while (var_v1 > 0) {
        gBattleRngSeed3 = (gBattleRngSeed3 * 0x41C64E6D) + 0x303B;
        if (gBattleRngSeed4 & 1) {
            gBattleRngSeed4 ^= 0x11020;
        }
        gBattleRngSeed4 >>= 1;
        var_v1--;
    }
    ret = gBattleRngSeed3 ^ gBattleRngSeed4;
    return ret;
}

void ShowDamageMessage(s32 arg0, s32 arg1) {
    unk_D_800AE540_0004* temp_a3;
    unk_D_800FCB18* temp_a2_2;
    unk_BattlePlayerAnimState* temp_v1;
    s32 sp18;

    temp_v1 = &sActivePokemon[arg0]->unk_654;
    temp_a2_2 = &sActivePokemon[arg1]->unk_654.unk_38;
    temp_a3 = sActivePokemon[arg0]->unk_720->unk_08[temp_v1->unk_2C];

    if (temp_a2_2->unk_0C == 0) {
        MessageBank_SetPointer_0x14_0x2A(0x19, temp_a3->unk_01C[temp_v1->unk_18].unk_30);
        WriteMessageCharOrString(gBattleMessageBuffers->unk_088, 0x21);
        return;
    }

    temp_v1->unk_28 = temp_a2_2->unk_0C;
    sp18 = (temp_a2_2->unk_0C * 0x19) / (temp_a2_2->unk_28 >> 2);

    MessageBank_SetPointer_0x14_0x2A(0x19, temp_a3->unk_01C[temp_v1->unk_18].unk_30);

    if (sp18 >= 0x46) {
        WriteMessageCharOrString(gBattleMessageBuffers->unk_088, 0x21);
    } else if (sp18 >= 0x28) {
        WriteMessageCharOrString(gBattleMessageBuffers->unk_088, 0x22);
    } else if (sp18 >= 0xA) {
        WriteMessageCharOrString(gBattleMessageBuffers->unk_088, 0x23);
    } else {
        WriteMessageCharOrString(gBattleMessageBuffers->unk_088, 0x24);
    }
}

void ResetBattleAfterMove(s32 arg0, s32 arg1) {
    unk_D_800FCB18* sp1C = &sActivePokemon[arg0]->unk_654.unk_38;
    unk_D_800FCB18* sp18 = &sActivePokemon[arg1]->unk_654.unk_38;

    ShowDamageMessage(arg0, arg1);
    gMoveEffectIndex = 0;
    gTypeEffectivenessMsgState = 0;
    sp1C->unk_44.unk_00 = 0;
    sp1C->unk_58 = 0;
    sp18->unk_58 = 0;
    sp1C->unk_4A = 0;
    sp1C->unk_4B = 0;
    sp1C->unk_4C = 0;
    sp1C->unk_4D = 0;
    sp1C->unk_4E = 0;
    sp1C->unk_52 = 0;
    sp1C->unk_57 = 0;
    sp1C->unk_56 = 0;
    sp18->unk_4C &= ~0x20;
    gBattleMessageFlag = 1;
}

void func_8436FA80(unk_BattlePlayerEntity* arg0) {
    unk_BattlePlayerAnimState* sp1C = &sActivePokemon[0]->unk_654;
    unk_BattlePlayerAnimState* sp18 = &sActivePokemon[1]->unk_654;
    unk_D_800FCB18* temp_a1 = &sActivePokemon[0]->unk_654.unk_38;
    unk_D_800FCB18* temp_a2 = &sActivePokemon[1]->unk_654.unk_38;
    s32 var_v0;

    if (arg0 == sActivePokemon[0]) {
        var_v0 = ((sp1C->unk_28 - temp_a2->unk_0C) * 0x19) / (temp_a2->unk_28 >> 2);
    } else {
        var_v0 = ((sp18->unk_28 - temp_a1->unk_0C) * 0x19) / (temp_a1->unk_28 >> 2);
    }

    if (var_v0 == 0) {
        WriteMessageCharOrString(gBattleMessageBuffers->unk_1C8, 0x25);
    } else if (var_v0 < 0x1E) {
        WriteMessageCharOrString(gBattleMessageBuffers->unk_1C8, 0x26);
    } else if (var_v0 < 0x46) {
        WriteMessageCharOrString(gBattleMessageBuffers->unk_1C8, 0x27);
    } else {
        WriteMessageCharOrString(gBattleMessageBuffers->unk_1C8, 0x28);
    }

    if (sp1C->unk_2D == 0x10) {
        WriteMessageCharOrString(gBattleMessageBuffers->unk_1C8, 0);
    }
}

void ApplyDamageRandomFactor(void) {
    s32 temp_v0;

    if (gCurrentDamage >= 2) {
        temp_v0 = 0;
        while (temp_v0 < 0xD9) {
            temp_v0 = GetRandomU8();
        }
        gCurrentDamage = (gCurrentDamage * temp_v0) / 255;
    }
}

u16 CompareMovePriority(unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1) {
    unk_D_800FCB18* ptr1 = &arg0->unk_654.unk_38;
    unk_D_800FCB18* ptr2 = &arg1->unk_654.unk_38;

    if (ptr1->unk_5A == 0x62) {
        if (ptr2->unk_5A != 0x62) {
            return 0;
        }
    } else if (ptr2->unk_5A == 0x62) {
        return 1;
    }

    if (ptr1->unk_5A == 0x44) {
        if (ptr2->unk_5A != 0x44) {
            return 1;
        }
    } else if (ptr2->unk_5A == 0x44) {
        return 0;
    }

    if (ptr2->unk_2E < ptr1->unk_2E) {
        return 0;
    }

    if (ptr1->unk_2E < ptr2->unk_2E) {
        return 1;
    }

    if (GetRandomU8() < 0x80) {
        return 0;
    }
    return 1;
}

s32 IsByteInArray(u8 arg0, u8* arg1, s32 arg2) {
    while (arg2--) {
        if (arg0 == *arg1) {
            return 1;
        }
        arg1++;
    }

    return 0;
}

void Battle_SetActiveMoveFromSlotIndex(void) {
    gBattleTempEntities[0].unk_5A = gBattleTempEntities[0].unk_1F[gMoveEffectIndex];
}

s32 func_8436FDBC(void) {
    SpAttack_Main();

    if (gSpecialFlag == 1) {
        return 0;
    }
    return 1;
}

void ComputePokemonStat(s32 arg0, PokemonData* arg1) {
    u16 i;
    u16 spC;
    u16 spA;
    u16 tmp;
    u16 sp6;
    u16 temp_a0;

    switch (arg0) {
        case 1:
            spA = gSpeciesBaseStats[arg1->unk_24].unk_01;
            spC = arg1->unk_14;
            break;

        case 2:
            spA = gSpeciesBaseStats[arg1->unk_24].unk_02;
            spC = arg1->unk_16;
            break;

        case 3:
            spA = gSpeciesBaseStats[arg1->unk_24].unk_03;
            spC = arg1->unk_18;
            break;

        case 4:
            spA = gSpeciesBaseStats[arg1->unk_24].unk_04;
            spC = arg1->unk_1A;
            break;

        case 5:
            spA = gSpeciesBaseStats[arg1->unk_24].unk_05;
            spC = arg1->unk_1C;
            break;
    }

    for (i = 1; i < 255; i++) {
        if (SQ(i) >= spC) {
            break;
        }
    }

    tmp = gBattleTempEntities[0].unk_24;

    switch (arg0) {
        case 1:
            sp6 = ((tmp & 0x1000) >> 9) | ((tmp & 0x100) >> 6) | ((tmp & 0x10) >> 3) | (tmp & 1);
            break;

        case 2:
            sp6 = (tmp >> 0xC) & 0xF;
            break;

        case 3:
            sp6 = (tmp >> 8) & 0xF;
            break;

        case 4:
            sp6 = (tmp >> 4) & 0xF;
            break;

        case 5:
            sp6 = tmp & 0xF;
            break;
    }

    temp_a0 = ((((spA + sp6) * 2) + (i >> 2)) * arg1->unk_24) / 100;
    if (arg0 == 1) {
        temp_a0 += arg1->unk_24 + 0xA;
    } else {
        temp_a0 += 5;
    }

    if (temp_a0 >= 0x3E8) {
        temp_a0 = 0x3E7;
    }

    switch (arg0) {
        case 1:
            arg1->unk_26 = temp_a0;
            break;

        case 2:
            arg1->unk_28 = temp_a0;
            break;

        case 3:
            arg1->unk_2A = temp_a0;
            break;

        case 4:
            arg1->unk_2C = temp_a0;
            break;

        case 5:
            arg1->unk_2E = temp_a0;
            break;
    }
}

void ComputeAllPokemonStats(PokemonData* arg0) {
    ComputePokemonStat(0, arg0);
    ComputePokemonStat(1, arg0);
    ComputePokemonStat(2, arg0);
    ComputePokemonStat(3, arg0);
    ComputePokemonStat(4, arg0);
}

void InitBattleParameters(void) {
    gCurrentDamage = 0;
    gMovePower = gCurrentBattleEntity->unk_44.unk_02;
    if (gMovePower) {
        if (gCurrentBattleEntity->unk_44.unk_03 < 0x14) {
            gDefenderStat = gDefenderBattleEntity->unk_2C;
            if (gDefenderBattleEntity->unk_4E & 4) {
                gDefenderStat *= 2;
            }

            if (gBattleEffectType != 0) {
                gDefenderStat = gDefenderBattleEntity->unk_3A;
                gAttackerStat = gCurrentBattleEntity->unk_38;
            } else {
                gAttackerStat = gCurrentBattleEntity->unk_2A;
            }
        } else {
            gDefenderStat = gDefenderBattleEntity->unk_30;
            if (gDefenderBattleEntity->unk_4E & 2) {
                gDefenderStat *= 2;
            }

            if (gBattleEffectType != 0) {
                gDefenderStat = gDefenderBattleEntity->unk_3E;
                gAttackerStat = gCurrentBattleEntity->unk_3E;
            } else {
                gAttackerStat = gCurrentBattleEntity->unk_30;
            }
        }

        if (gAttackerStat & 0xFF00) {
            if (gDefenderStat & 0xFF00) {
                gAttackerStat >>= 2;
                gDefenderStat >>= 2;
                if (gAttackerStat == 0) {
                    gAttackerStat = 1;
                }
            }
        }

        gAttackerLevel = gCurrentBattleEntity->unk_26;
        if (gBattleEffectType != 0) {
            gAttackerLevel *= 2;
        }
    }
}

s32 UpdateDamageAccumulator(void) {
    s32 temp_v0 = gCurrentBattleEntity->unk_44.unk_01;

    if (temp_v0 == 7) {
        gDefenderStat >>= 1;
        if (gDefenderStat == 0) {
            gDefenderStat = 1;
        }
    }

    if ((temp_v0 != 0x1D) && (temp_v0 != 0x1E)) {
        if (temp_v0 == 0x26) {
            return func_8436FDBC();
        }

        if (gMovePower == 0) {
            return 0;
        }
    }

    gCurrentDamage += (((((gAttackerLevel * 2) / 5) + 2) * gMovePower * gAttackerStat) / gDefenderStat) / 50;
    if (gCurrentDamage > 0x3E4) {
        gCurrentDamage = 0x3E4;
    }
    gCurrentDamage += 2;

    return 1;
}

void ProcessTurnEnd(void) {
    if (gDefenderBattleEntity->unk_4D & 0x10) {
        if (gBattleState.unk_00->unk_48 == 0x14) {
            MessageBank_SetPointer_0x14_0x2A(0x19, GetPokemonName(sActivePokemon[gBattleState.unk_00->unk_2C]));
            WriteMessageCharOrString(gBattleMessageBuffers->unk_208, 0x2B);
            if (gDefenderBattleEntity->unk_59 < gCurrentDamage) {
                gDefenderBattleEntity->unk_4D &= 0xFFEF;
                MessageBank_SetPointer_0x14_0x2A(0x19, GetPokemonName(sActivePokemon[gBattleState.unk_00->unk_2C]));
                WriteMessageCharOrString(gBattleMessageBuffers->unk_208, 0x2C);

                if ((D_8438AC60[0] == 1) && (gCurrentBattleEntity->unk_44.unk_01 == 0x1D)) {
                    SpAttack_Main();
                    gCurrentBattleEntity->unk_4F = 1;
                }

                if ((D_8438AC60[0] != 1) || (gCurrentBattleEntity->unk_44.unk_01 != 7)) {
                    gCurrentBattleEntity->unk_44.unk_01 = 0;
                }

                SetEntityAnimFlags(sActivePokemon[gBattleState.unk_00->unk_2C], 0x1000);
            } else {
                gDefenderBattleEntity->unk_59 -= gCurrentDamage;
            }
        } else {
            MessageBank_SetPointer_0x14_0x2A(0x19, GetPokemonName(sActivePokemon[!gBattleState.unk_00->unk_2C]));
            WriteMessageCharOrString(gBattleMessageBuffers->unk_208, 0x2B);
            if (gDefenderBattleEntity->unk_59 < gCurrentDamage) {
                gDefenderBattleEntity->unk_4D &= 0xFFEF;
                MessageBank_SetPointer_0x14_0x2A(0x19, GetPokemonName(sActivePokemon[!gBattleState.unk_00->unk_2C]));
                WriteMessageCharOrString(gBattleMessageBuffers->unk_208, 0x2C);

                if ((D_8438AC60[0] == 1) && (gCurrentBattleEntity->unk_44.unk_01 == 0x1D)) {
                    SpAttack_Main();
                    gCurrentBattleEntity->unk_4F = 1;
                }

                if ((D_8438AC60[0] != 1) || (gCurrentBattleEntity->unk_44.unk_01 != 7)) {
                    gCurrentBattleEntity->unk_44.unk_01 = 0;
                }

                SetEntityAnimFlags(sActivePokemon[!gBattleState.unk_00->unk_2C], 0x1000);
            } else {
                gDefenderBattleEntity->unk_59 -= gCurrentDamage;
            }
        }
    } else if (gBattleUpdateHPFlag == 0) {
        if (gCurrentDamage < gDefenderBattleEntity->unk_0C) {
            gDefenderBattleEntity->unk_0C -= gCurrentDamage;
        } else {
            gCurrentDamage = gDefenderBattleEntity->unk_0C;
            gDefenderBattleEntity->unk_0C = 0;
        }
    }
}

void DecrementMovePP(s32 arg0) {
    unk_D_800FCB18* temp_v0;
    unk_BattlePlayerAnimState* temp_a1;
    PokemonData* temp_a2;

    temp_v0 = &sActivePokemon[arg0]->unk_654.unk_38;
    temp_a1 = &sActivePokemon[arg0]->unk_654;
    temp_a2 = &sActivePokemon[arg0]->unk_724->unk_01C[temp_a1->unk_08];

    if ((temp_v0->unk_5A != 0xA5) && !(temp_v0->unk_4C & 7) && !(temp_v0->unk_4D & 0x40)) {
        temp_v0->unk_32[temp_a1->unk_0C]--;
        if (!(temp_v0->unk_4E & 8)) {
            temp_a2->unk_20[temp_a1->unk_0C] -= 1;
        }
    }
}

void ApplyAccuracyStageMultipliers(void) {
    StatStageMultiplier* var_v0;
    s32 var_a2;
    s32 idx;
    s32 idx2;

    if (D_8438AC60[0] == 1) {
        var_v0 = gStatStageMultipliersAlt;
    } else {
        var_v0 = gStatStageMultipliers;
    }

    idx = gCurrentBattleEntity->unk_5C[4];
    idx2 = gDefenderBattleEntity->unk_5C[5];
    idx2 = 0xE - idx2;

    var_a2 = (gCurrentBattleEntity->unk_44.unk_04 * var_v0[idx - 1].unk_00) / var_v0[idx - 1].unk_01;
    if (var_a2 == 0) {
        var_a2 = 1;
    }

    var_a2 = (var_a2 * var_v0[idx2 - 1].unk_00) / var_v0[idx2 - 1].unk_01;
    if (var_a2 == 0) {
        var_a2 = 1;
    }

    if (var_a2 >= 0x100) {
        var_a2 = 0xFF;
    }
    gCurrentBattleEntity->unk_44.unk_04 = var_a2;
}

void MarkAttackFailed(void) {
    gCurrentDamage = 0;
    gSpecialFlag = 1;
    gCurrentBattleEntity->unk_4C &= ~0x20;
}

void HandleMoveEffectFlags(void) {
    if (gCurrentBattleEntity->unk_44.unk_01 == 0x50) {
        if (!(gCurrentBattleEntity->unk_4D & 0x20) && (D_8438AC60[0] == 1)) {
            gCurrentBattleEntity->unk_4D |= 0x20;
        }
    }

    if ((gCurrentBattleEntity->unk_44.unk_01 == 8) && !(gDefenderBattleEntity->unk_15 & 7)) {
        MarkAttackFailed();
        return;
    }

    if (gDefenderBattleEntity->unk_4D & 0x10) {
        if (gCurrentBattleEntity->unk_44.unk_01 == 17) {
            return;
        }

        if (gCurrentBattleEntity->unk_44.unk_01 == 3 || gCurrentBattleEntity->unk_44.unk_01 == 8 ||
            ((D_8438AC60[0] == 1) && (IsByteInArray(gCurrentBattleEntity->unk_44.unk_01, gMoveEffectImmunityList, 5) != 0))) {
            MarkAttackFailed();
            return;
        }
    }

    if (gDefenderBattleEntity->unk_4C & 0x40) {
        if (gCurrentBattleEntity->unk_44.unk_01 != 0x11) {
            MarkAttackFailed();
        }
    } else {
        if ((((gCurrentBattleEntity->unk_44.unk_01 >= 0x12) && (gCurrentBattleEntity->unk_44.unk_01 < 0x1A)) ||
             ((gCurrentBattleEntity->unk_44.unk_01 >= 0x3A) && (gCurrentBattleEntity->unk_44.unk_01 < 0x42))) &&
            (gDefenderBattleEntity->unk_4D & 2)) {
            MarkAttackFailed();
            return;
        }

        if (!(gCurrentBattleEntity->unk_4D & 1)) {
            if ((D_8438AC60[0] != 1) || (gCurrentBattleEntity->unk_44.unk_01 != 0x11)) {
                ApplyAccuracyStageMultipliers();
            }

            gAccuracyCheckRandom = GetRandomU8_Alt();
            if (gAccuracyCheckRandom == 0xFF) {
                gAccuracyCheckRandom = GetRandomU8_Alt();
            }

            if (gAccuracyCheckRandom >= gCurrentBattleEntity->unk_44.unk_04) {
                MarkAttackFailed();
            }
        }
    }
}

void Battle_ApplyAnimStateEffects(unk_BattlePlayerEntity* arg0) {
    PokemonData* ptr = &arg0->unk_724->unk_01C[arg0->unk_654.unk_08];

    ptr->unk_05 = arg0->unk_654.unk_38.unk_15;
}

void ApplyParalysisSpeedCut(unk_BattlePlayerEntity* arg0) {
    unk_D_800FCB18* temp_v0 = &arg0->unk_654.unk_38;

    if (arg0->unk_654.unk_38.unk_15 & 0x40) {
        temp_v0->unk_2E >>= 2;
        if (temp_v0->unk_2E == 0) {
            temp_v0->unk_2E = 1;
        }
    }
}

void ApplyBurnAttackCut(unk_BattlePlayerEntity* arg0) {
    unk_D_800FCB18* temp_v0 = &arg0->unk_654.unk_38;

    if (arg0->unk_654.unk_38.unk_15 & 0x10) {
        temp_v0->unk_2A >>= 1;
        if (temp_v0->unk_2A == 0) {
            temp_v0->unk_2A = 1;
        }
    }
}

void func_84370B7C(unk_BattlePlayerEntity* arg0) {
    unk_BattlePlayerAnimState* sp28;
    unk_D_800FCB18* sp24;
    PokemonData* sp34;
    s32 i;
    s32 j;

    sp28 = &arg0->unk_654;
    sp24 = &arg0->unk_654.unk_38;
    sp34 = &arg0->unk_720->unk_08[sp28->unk_2C]->unk_01C[sp28->unk_18];

    sp24->unk_14 = sp28->unk_08;
    sp24->unk_0B = sp34->unk_00.unk_00;
    sp24->unk_0C = sp34->unk_02;
    sp24->unk_15 = sp34->unk_05;
    sp24->unk_16[6] = sp34->unk_06;
    sp24->unk_16[7] = sp34->unk_07;
    sp24->unk_16[8] = sp34->unk_08;

    sp24->unk_1F[0] = sp34->unk_09[0];
    sp24->unk_1F[1] = sp34->unk_09[1];
    sp24->unk_1F[2] = sp34->unk_09[2];
    sp24->unk_1F[3] = sp34->unk_09[3];
    sp24->unk_24 = sp34->unk_1E;

    sp24->unk_32[0] = sp34->unk_20[0];
    sp24->unk_32[1] = sp34->unk_20[1];
    sp24->unk_32[2] = sp34->unk_20[2];
    sp24->unk_32[3] = sp34->unk_20[3];

    if ((sp34->unk_09[0] == 0) || (sp34->unk_09[0] >= 0xA6)) {
        sp24->unk_32[0] = 0;
    }

    if ((sp34->unk_09[1] == 0) || (sp34->unk_09[1] >= 0xA6)) {
        sp24->unk_32[1] = 0;
    }

    if ((sp34->unk_09[2] == 0) || (sp34->unk_09[2] >= 0xA6)) {
        sp24->unk_32[2] = 0;
    }

    if ((sp34->unk_09[3] == 0) || (sp34->unk_09[3] >= 0xA6)) {
        sp24->unk_32[3] = 0;
    }

    for (i = 0; i < 4; i++) {
        if (sp34->unk_09[i] == 0) {
            for (j = i; j < 4; j++) {
                sp24->unk_32[j] = 0;
                sp24->unk_1F[j] = sp34->unk_09[j] = 0;
            }
            break;
        }
    }

    sp24->unk_26 = sp34->unk_24;
    sp24->unk_28 = sp34->unk_26;
    sp24->unk_2A = sp34->unk_28;
    sp24->unk_2C = sp34->unk_2A;
    sp24->unk_2E = sp34->unk_2C;
    sp24->unk_30 = sp34->unk_2E;

    ApplyParalysisSpeedCut(arg0);
    ApplyBurnAttackCut(arg0);

    sp24->unk_36 = D_80070F84[sp24->unk_0B].baseHP;
    sp24->unk_38 = sp34->unk_28;
    sp24->unk_3A = sp34->unk_2A;
    sp24->unk_3C = sp34->unk_2C;
    sp24->unk_3E = sp34->unk_2E;

    // clang-format off
    for (i = 0; i < 8; i++) { sp24->unk_5C[i] = 7; }
    // clang-format on
}

s32 Battle_IsPartyMemberAlive(unk_BattlePlayerEntity* arg0) {
    if (arg0->unk_724->unk_01C[arg0->unk_654.unk_18 - 1].unk_02 != 0) {
        return 1;
    }
    return 0;
}

void func_84370E70(void) {
}

void func_84370E78(void) {
}

void func_84370E80(void) {
    gCurrentBattleEntity->unk_44.unk_00 = gMoveBattleData[gCurrentBattleEntity->unk_5A - 1].unk_00;
    gCurrentBattleEntity->unk_44.unk_01 = gMoveBattleData[gCurrentBattleEntity->unk_5A - 1].unk_01;
    gCurrentBattleEntity->unk_44.unk_02 = gMoveBattleData[gCurrentBattleEntity->unk_5A - 1].unk_02;
    gCurrentBattleEntity->unk_44.unk_03 = gMoveBattleData[gCurrentBattleEntity->unk_5A - 1].unk_03;
    gCurrentBattleEntity->unk_44.unk_04 = gMoveBattleData[gCurrentBattleEntity->unk_5A - 1].unk_04;
    gCurrentBattleEntity->unk_44.unk_05 = gMoveBattleData[gCurrentBattleEntity->unk_5A - 1].unk_05;
}

void Battle_ApplyRageContinuation(void) {
    unk_D_800FCB18* sp24;

    if ((gDefenderBattleEntity->unk_4D & 0x40) && ((gDefenderBattleEntity->unk_5C[0]) != 0xD)) {
        sp24 = gCurrentBattleEntity;

        gCurrentBattleEntity = gDefenderBattleEntity;
        gCurrentBattleEntity->unk_44.unk_00 = 0;
        gCurrentBattleEntity->unk_44.unk_01 = 10;

        MessageBank_SetPointer_0x14_0x2A(0x19, GetPokemonName(sActivePokemon[!gBattleState.unk_00->unk_2C]));
        WriteMessageCharOrString(gBattleMessageBuffers->unk_348, 0x1F);
        Battle_ApplyStatIncrease();

        gCurrentBattleEntity->unk_44.unk_00 = 0x63;
        gCurrentBattleEntity->unk_44.unk_01 = 0;

        gCurrentBattleEntity = sp24;
    }
}

void func_84371010(void) {
    gAnimTimer = gTypeEffectivenessMsgState & 0x7F;
    if (gAnimTimer >= 0xB) {
        WriteMessageCharOrString(gBattleMessageBuffers->unk_088, 0x29);
    } else if (gAnimTimer < 0xA) {
        WriteMessageCharOrString(gBattleMessageBuffers->unk_088, 0x2A);
    }
}

void func_84371080(void) {
    unk_D_800FCB18* sp1C = &sActivePokemon[!gBattleState.unk_00->unk_2C]->unk_654.unk_38;

    switch (gBattleEffectType) {
        case 1:
            WriteMessageCharOrString(gBattleMessageBuffers->unk_148, 0x1D);
            gBattleState.unk_00->unk_1A = 2;
            break;
        case 2:
            WriteMessageCharOrString(gBattleMessageBuffers->unk_148, 0x1E);
            gBattleState.unk_00->unk_1A = 2;
            break;
    }
    sp1C->unk_5B = gBattleEffectType;
    gBattleEffectType = 0;
}

void func_8437114C(void) {
    s32 var_s0;
    s32 temp_v0;

    switch (gCurrentBattleEntity->unk_44.unk_01) {
        case 38:
            break;

        case 40:
            gCurrentDamage = gDefenderBattleEntity->unk_0C / 2;
            if (gCurrentDamage == 0) {
                gCurrentDamage = 1;
            }
            break;

        case 41:
            switch (gCurrentBattleEntity->unk_44.unk_00) {
                case 0x45:
                case 0x65:
                    var_s0 = gCurrentBattleEntity->unk_26;
                    break;

                case 0x31:
                    var_s0 = 0x14;
                    break;

                case 0x52:
                    var_s0 = 0x28;
                    break;

                default:
                    var_s0 = gCurrentBattleEntity->unk_26;
                    var_s0 = (var_s0 >> 1) + var_s0;
                    do {
                        do {
                            temp_v0 = GetRandomU8();
                        } while (temp_v0 == 0);
                    } while (temp_v0 >= var_s0);
                    var_s0 = temp_v0;
            }
            gCurrentDamage = var_s0;
            break;

        default:
            if (gCurrentBattleEntity->unk_44.unk_02 != 0) {
                if (gCurrentBattleEntity->unk_4C & 4) {
                    gAccumulatedDamage += gCurrentDamage;
                } else {
                    gAccumulatedDamage = gCurrentDamage;
                }
                break;
            }
            return;
    }

    if (gCurrentDamage != 0) {
        ProcessTurnEnd();
    }
}

void Battle_QueueMoveFailureAndApplyRecoil(void) {
    unk_D_800FCB18* sp1C;

    if (gTypeEffectivenessMsgState & 0x7F) {
        if (gBattleEffectType == 0xFF) {
            MessageBank_SetPointer_0x14_0x2A(0x19, GetPokemonName(sActivePokemon[!gBattleState.unk_00->unk_2C]));
            WriteMessageCharOrString(gBattleMessageBuffers->unk_088, 0x19);
        } else {
            MessageBank_SetPointer_0x14_0x2A(0x19, GetPokemonName(sActivePokemon[gBattleState.unk_00->unk_2C]));
            WriteMessageCharOrString(gBattleMessageBuffers->unk_088, 0x1A);
        }
    } else {
        MessageBank_SetPointer_0x14_0x2A(0x19, GetPokemonName(sActivePokemon[!gBattleState.unk_00->unk_2C]));
        WriteMessageCharOrString(gBattleMessageBuffers->unk_088, 0x1B);
    }

    gBattleEffectType = 0;

    if (gCurrentBattleEntity->unk_44.unk_01 == 0x2D) {
        gBattleState.unk_00->unk_48 = 0x10;
        gCurrentDamage >>= 3;
        if (gCurrentDamage == 0) {
            gCurrentDamage++;
        }

        MessageBank_SetPointer_0x14_0x2A(0x19, GetPokemonName(sActivePokemon[gBattleState.unk_00->unk_2C]));
        WriteMessageCharOrString(gBattleMessageBuffers->unk_088, 0x1C);

        sp1C = gCurrentBattleEntity;
        gCurrentBattleEntity = gDefenderBattleEntity;
        gDefenderBattleEntity = sp1C;
        gBattleState.unk_00->unk_2C = !gBattleState.unk_00->unk_2C;
        ProcessTurnEnd();
        gBattleState.unk_00->unk_2C = !gBattleState.unk_00->unk_2C;
        gDefenderBattleEntity = gCurrentBattleEntity;
        gCurrentBattleEntity = sp1C;
    }
}

void func_843714D8(void) {
    unk_D_800FCB18* ptr;
    PokemonData* temp_a0;
    unk_BattlePlayerAnimState* temp_a1;

    ptr = &sActivePokemon[gBattleState.unk_00->unk_2C]->unk_654.unk_38;
    temp_a0 =
        &sActivePokemon[gBattleState.unk_00->unk_2C]->unk_724->unk_01C[sActivePokemon[gBattleState.unk_00->unk_2C]->unk_654.unk_08];
    temp_a1 = &sActivePokemon[gBattleState.unk_00->unk_2C]->unk_654;

    gCurrentBattleEntity->unk_32[temp_a1->unk_0C]++;
    if (!(ptr->unk_4E & 8)) {
        temp_a0->unk_20[temp_a1->unk_0C]++;
    }
}

s32 Battle_Effect_Metronome(void) {
    s32 temp_v0;

    func_843714D8();
    do {
        do {
            temp_v0 = GetRandomU8();
        } while (temp_v0 == 0 || temp_v0 >= 0xA5);
    } while (temp_v0 == 0x76);
    gCurrentBattleEntity->unk_5A = temp_v0;
    func_84370E80();
    return 1;
}

void Battle_ApplyPoisonOrBurnDamage(void) {
    u16 var_a0;

    if (gCurrentBattleEntity->unk_12 != 0xFFFF) {
        gCurrentBattleEntity->unk_0E = gCurrentBattleEntity->unk_12;
    } else {
        gCurrentBattleEntity->unk_0E = gCurrentBattleEntity->unk_0C;
    }

    var_a0 = (gCurrentBattleEntity->unk_28 >> 4) & 0xFFFF;
    if (var_a0 == 0) {
        var_a0++;
    }

    if (gCurrentBattleEntity->unk_4E & 1) {
        gCurrentBattleEntity->unk_51++;
        var_a0 *= gCurrentBattleEntity->unk_51;
    }

    if (gCurrentBattleEntity->unk_0E < var_a0) {
        gCurrentBattleEntity->unk_0E = 0;
    } else {
        gCurrentBattleEntity->unk_0E -= var_a0;
    }

    gCurrentBattleEntity->unk_10 = gCurrentBattleEntity->unk_0E;
}

void Battle_ApplyLeechSeedDamage(void) {
    u16 var_a0;

    if (!(gCurrentBattleEntity->unk_15 & 0x18)) {
        if (gCurrentBattleEntity->unk_12 != 0xFFFF) {
            gCurrentBattleEntity->unk_10 = gCurrentBattleEntity->unk_12;
        } else {
            gCurrentBattleEntity->unk_10 = gCurrentBattleEntity->unk_0C;
        }
    }

    var_a0 = (gCurrentBattleEntity->unk_28 >> 4) & 0xFFFF;
    if (var_a0 == 0) {
        var_a0++;
    }

    if (gCurrentBattleEntity->unk_4E & 1) {
        gCurrentBattleEntity->unk_51++;
        var_a0 *= gCurrentBattleEntity->unk_51;
    }

    if (gCurrentBattleEntity->unk_10 < var_a0) {
        var_a0 = gCurrentBattleEntity->unk_10;
        gCurrentBattleEntity->unk_10 = 0;
    } else {
        gCurrentBattleEntity->unk_10 -= var_a0;
    }

    gDefenderBattleEntity->unk_10 = gDefenderBattleEntity->unk_0C;
    gDefenderBattleEntity->unk_10 += var_a0;

    if (gDefenderBattleEntity->unk_28 < gDefenderBattleEntity->unk_10) {
        gDefenderBattleEntity->unk_10 = gDefenderBattleEntity->unk_28;
    }
}

s32 Battle_ApplyResidualEffects(void) {
    if (gDefenderBattleEntity->unk_0C == 0) {
        return 0;
    }

    if (gCurrentBattleEntity->unk_15 & 0x18) {
        if (gCurrentBattleEntity->unk_15 & 8) {
            MessageBank_SetPointer_0x14_0x2A(0x19, GetPokemonName(sActivePokemon[gBattleState.unk_00->unk_2C]));
            WriteMessageCharOrString(gBattleMessageBuffers->unk_248, 0);
        } else {
            MessageBank_SetPointer_0x14_0x2A(0x19, GetPokemonName(sActivePokemon[gBattleState.unk_00->unk_2C]));
            WriteMessageCharOrString(gBattleMessageBuffers->unk_248, 1);
        }
        Battle_ApplyPoisonOrBurnDamage();
        gDefenderBattleEntity->unk_0E = gDefenderBattleEntity->unk_0C;
    }

    if (gCurrentBattleEntity->unk_4D & 0x80) {
        Battle_ApplyLeechSeedDamage();
        MessageBank_SetPointer_0x14_0x2A(0x19, GetPokemonName(sActivePokemon[gBattleState.unk_00->unk_2C]));
        WriteMessageCharOrString(gBattleMessageBuffers->unk_288, 2);
    }

    if (gCurrentBattleEntity->unk_0C != 0) {
        return 0;
    }
    return 1;
}

void func_843718DC(void) {
}

s32 Battle_TryLoadFollowupMoveFromTarget(void) {
    if ((gDefenderBattleEntity->unk_58 == 0x77) || (gDefenderBattleEntity->unk_58 == 0)) {
        gBattleMessageBuffers->unk_388[0] = 0;
        gBattleMessageBuffers->unk_388[1] = 0;
        gBattleState.unk_00->unk_48 = 0x1C;
        WriteMessageCharOrString(gBattleMessageBuffers->unk_088, 0x20);
        return 0;
    }

    gCurrentBattleEntity->unk_5A = gDefenderBattleEntity->unk_58;
    func_843714D8();
    func_84370E80();
    return 1;
}

void Battle_ApplyTypeEffectAndSTAB(void) {
    u8 var_v0;
    u8 var_v1;
    u8 temp_a0;
    u8 temp_a1;
    u8 temp_a3;
    u8 temp_t1;
    TypeEffectivenessEntry* var_a3;

    var_v0 = 3;

    temp_a1 = gCurrentBattleEntity->unk_16[6];
    temp_a3 = gCurrentBattleEntity->unk_16[7];

    var_v1 = gDefenderBattleEntity->unk_16[6];
    temp_a0 = gDefenderBattleEntity->unk_16[7];

    temp_t1 = gCurrentBattleEntity->unk_44.unk_03;

    if ((D_8438AC60[0] != 1) || (gCurrentBattleEntity->unk_44.unk_00 != 0xA5)) {
        if ((temp_t1 == temp_a1) || (temp_t1 == temp_a3)) {
            gCurrentDamage += gCurrentDamage >> 1;
            gTypeEffectivenessMsgState |= 0x80;
        }

        var_a3 = &gTypeEffectivenessTable[0];
        while (var_a3->unk_00 != 0xFF) {
            if ((var_a3->unk_00 == temp_t1) && ((var_a3->unk_01 == var_v1) || (var_a3->unk_01 == temp_a0))) {
                if (var_a3->unk_02 != 0) {
                    if (var_a3->unk_02 >= 0xB) {
                        var_v0++;
                    } else {
                        var_v0--;
                    }
                }

                gCurrentDamage = (gCurrentDamage * var_a3->unk_02) / 10;

                if (gCurrentDamage == 0) {
                    gSpecialFlag = 1;
                }
            }
            var_a3++;
        }

        switch (var_v0) {
            case 1:
            case 2:
                gTypeEffectivenessMsgState = (gTypeEffectivenessMsgState & 0x80) + 5;
                break;

            case 3:
                break;

            case 4:
            case 5:
                gTypeEffectivenessMsgState = (gTypeEffectivenessMsgState & 0x80) + 0x14;
                break;
        }
    }
}

s32 Battle_Effect_Counter(void) {
    if (gCurrentBattleEntity->unk_5A != 0x44) {
        return 1;
    }

    gSpecialFlag = 1;

    if (gDefenderBattleEntity->unk_5A == 0x44) {
        return 0;
    }

    if (gDefenderBattleEntity->unk_44.unk_02 == 0) {
        return 0;
    }

    if ((gDefenderBattleEntity->unk_44.unk_03 == 0) || (gDefenderBattleEntity->unk_44.unk_03 == 1)) {
        if (gCurrentDamage == 0) {
            return 0;
        }

        if (gCurrentDamage >= 0x8000) {
            gCurrentDamage = 0xFFFF;
        } else {
            gCurrentDamage *= 2;
        }

        gSpecialFlag = 0;
        gBattleEffectType = 0;
        HandleMoveEffectFlags();
        return 0;
    }
    return 0;
}

s32 Battle_CheckCriticalHit(void) {
    UNUSED s32 pad;
    s32 sp18;

    gBattleEffectType = 0;
    if (D_8438AC60[0] == 1) {
        sp18 = (D_80070F84[gCurrentBattleEntity->unk_0B].baseDefense + 0x4C) >> 2;
    } else {
        sp18 = D_80070F84[gCurrentBattleEntity->unk_0B].baseDefense >> 1;
    }

    if (gCurrentBattleEntity->unk_44.unk_02 == 0) {
        return 0;
    }

    if (D_8438AC60[0] == 1) {
        if (gCurrentBattleEntity->unk_4D & 4) {
            sp18 = (sp18 * 4) + 0xA0;
        } else {
            sp18 *= 2;
        }

        if (IsByteInArray(gCurrentBattleEntity->unk_44.unk_00, gBattleTypeEffectivenessParams, 4) != 0) {
            sp18 *= 4;
        } else {
            sp18 >>= 1;
        }
    } else {
        if (gCurrentBattleEntity->unk_4D & 4) {
            sp18 >>= 1;
        } else {
            sp18 *= 2;
            if (sp18 >= 0x100) {
                sp18 = 0xFF;
            }
        }

        if (IsByteInArray(gCurrentBattleEntity->unk_44.unk_00, gBattleTypeEffectivenessParams, 4) != 0) {
            sp18 *= 4;
            if (sp18 >= 0x100) {
                sp18 = 0xFF;
            }
        } else {
            sp18 >>= 1;
        }
    }

    if (sp18 >= 0x100) {
        sp18 = 0xFF;
    }

    if (sp18 <= 0) {
        sp18 = 1;
    }

    gAccuracyCheckRandom = GetRandomU8();
    if (gAccuracyCheckRandom >= sp18) {
        return 0;
    }
    gBattleEffectType = 1;
    return 1;
}

s32 ProcessBattleEntityStatus(void) {
    unk_D_800FCB18* sp2C;
    unk_BattlePlayerAnimState* temp_v0;
    u16 sp26;
    u8 sp25;
    unk_D_800FCB18* temp_v1;

    temp_v0 = &sActivePokemon[gBattleState.unk_00->unk_2C]->unk_654;
    temp_v1 = &sActivePokemon[gBattleState.unk_00->unk_2C]->unk_654.unk_38;

    if (gCurrentBattleEntity->unk_15 & 7) {
        gCurrentBattleEntity->unk_15 = (gCurrentBattleEntity->unk_15 & 7) - 1;
        if (temp_v1->unk_16[temp_v0->unk_08 + temp_v0->unk_2B * 3] != 0) {
            temp_v1->unk_16[temp_v0->unk_08 + temp_v0->unk_2B * 3]--;
        }

        if (gCurrentBattleEntity->unk_15 != 0) {
            MessageBank_SetPointer_0x14_0x2A(0x19, GetPokemonName(sActivePokemon[gBattleState.unk_00->unk_2C]));
            WriteMessageCharOrString(gBattleMessageBuffers->unk_088, 5);
            gBattleState.unk_00->unk_48 = 0x11;
        } else {
            MessageBank_SetPointer_0x14_0x2A(0x19, GetPokemonName(sActivePokemon[gBattleState.unk_00->unk_2C]));
            WriteMessageCharOrString(gBattleMessageBuffers->unk_088, 6);
            gBattleState.unk_00->unk_48 = 0x11;
        }

        gCurrentBattleEntity->unk_58 = 0;
        return 0;
    }

    if (gCurrentBattleEntity->unk_15 & 0x20) {
        MessageBank_SetPointer_0x14_0x2A(0x19, GetPokemonName(sActivePokemon[gBattleState.unk_00->unk_2C]));
        WriteMessageCharOrString(gBattleMessageBuffers->unk_088, 7);
        gCurrentBattleEntity->unk_58 = 0;
        gBattleState.unk_00->unk_48 = 0x11;
        return 0;
    }

    if (gDefenderBattleEntity->unk_4C & 0x20) {
        MessageBank_SetPointer_0x14_0x2A(0x19, GetPokemonName(sActivePokemon[gBattleState.unk_00->unk_2C]));
        WriteMessageCharOrString(gBattleMessageBuffers->unk_088, 8);
        gBattleState.unk_00->unk_48 = 0x11;
        return 0;
    }

    if (gCurrentBattleEntity->unk_4C & 8) {
        MessageBank_SetPointer_0x14_0x2A(0x19, GetPokemonName(sActivePokemon[gBattleState.unk_00->unk_2C]));
        WriteMessageCharOrString(gBattleMessageBuffers->unk_088, 9);
        gCurrentBattleEntity->unk_4D &= 0xFFDF;
        gCurrentBattleEntity->unk_4C &= 0xFFF7;
        gBattleState.unk_00->unk_48 = 0x1C;
        return 0;
    }

    if (gCurrentBattleEntity->unk_4D & 0x20) {
        gCurrentBattleEntity->unk_4D &= ~0x20;
        if (D_8438AC60[0] == 1) {
            gCurrentDamage = 0;
        }
        gBattleState.unk_00->unk_48 = 0x11;
        MessageBank_SetPointer_0x14_0x2A(0x19, GetPokemonName(sActivePokemon[gBattleState.unk_00->unk_2C]));
        WriteMessageCharOrString(gBattleMessageBuffers->unk_088, 0xA);
        return 0;
    }

    if (gCurrentBattleEntity->unk_52 != 0) {
        gCurrentBattleEntity->unk_52--;
        if (!(gCurrentBattleEntity->unk_52 & 0xF)) {
            gCurrentBattleEntity->unk_52 = 0;
            gCurrentBattleEntity->unk_57 = 0;
            MessageBank_SetPointer_0x14_0x2A(0x19, GetPokemonName(sActivePokemon[gBattleState.unk_00->unk_2C]));
            WriteMessageCharOrString(gBattleMessageBuffers->unk_388, 0xB);
        }
    }

    if (gCurrentBattleEntity->unk_4C & 0x80) {
        gCurrentBattleEntity->unk_50--;
        if (gCurrentBattleEntity->unk_50 == 0) {
            gCurrentBattleEntity->unk_4C &= 0xFF7F;
            MessageBank_SetPointer_0x14_0x2A(0x19, GetPokemonName(sActivePokemon[gBattleState.unk_00->unk_2C]));
            WriteMessageCharOrString(gBattleMessageBuffers->unk_188, 0xC);
        } else {
            Battle_QueueMoveCategoryMessage();
            MessageBank_SetPointer_0x14_0x2A(0x19, GetPokemonName(sActivePokemon[gBattleState.unk_00->unk_2C]));
            WriteMessageCharOrString(gBattleMessageBuffers->unk_188, 0xD);
            gAccuracyCheckRandom = GetRandomU8();
            if (gAccuracyCheckRandom >= 0x80) {
                Battle_QueueMetronomeMoveMessage();
                gBattleState.unk_00->unk_48 = 0x14;
                gCurrentBattleEntity->unk_4C &= 0x80;
                WriteMessageCharOrString(gBattleMessageBuffers->unk_148, 0xE);

                sp26 = gDefenderBattleEntity->unk_2C;
                gDefenderBattleEntity->unk_2C = gCurrentBattleEntity->unk_2C;
                sp25 = gCurrentBattleEntity->unk_44.unk_01;
                gCurrentBattleEntity->unk_44.unk_01 = 0;
                gBattleEffectType = 0;
                gCurrentBattleEntity->unk_44.unk_02 = 0x28;
                gCurrentBattleEntity->unk_44.unk_03 = 0;
                InitBattleParameters();
                UpdateDamageAccumulator();
                gCurrentBattleEntity->unk_44.unk_01 = sp25;
                gDefenderBattleEntity->unk_2C = sp26;

                sp2C = gCurrentBattleEntity;
                gCurrentBattleEntity = gDefenderBattleEntity;
                gDefenderBattleEntity = sp2C;
                ProcessTurnEnd();
                gDefenderBattleEntity = gCurrentBattleEntity;
                gCurrentBattleEntity = sp2C;
                goto label1;
            }
        }
    }

    if ((gCurrentBattleEntity->unk_57 != 0) && (gCurrentBattleEntity->unk_57 == gCurrentBattleEntity->unk_5A)) {
        gCurrentBattleEntity->unk_4C &= 0xFFEF;
        MessageBank_SetPointer_0x14_0x2A(0x1D, (u32)gMoveStrings[gCurrentBattleEntity->unk_5A - 1].unk_04);
        WriteMessageCharOrString(gBattleMessageBuffers->unk_088, 0xF);
        gBattleState.unk_00->unk_48 = 0x11;
        return 0;
    }

    if (gCurrentBattleEntity->unk_15 & 0x40) {
        gAccuracyCheckRandom = GetRandomU8();
        if (gAccuracyCheckRandom < 0x3F) {
            MessageBank_SetPointer_0x14_0x2A(0x19, GetPokemonName(sActivePokemon[gBattleState.unk_00->unk_2C]));
            WriteMessageCharOrString(gBattleMessageBuffers->unk_088, 0x10);
            gBattleState.unk_00->unk_48 = 0x1F;
            gCurrentDamage = 0;
        label1:
            gCurrentBattleEntity->unk_4C &= 0xFF8C;
            return 0;
        }
    }

    if (gCurrentBattleEntity->unk_4C & 1) {
        gCurrentBattleEntity->unk_44.unk_00 = 0;
        gCurrentBattleEntity->unk_54 += gCurrentDamage;
        gCurrentBattleEntity->unk_4F -= 1;
        if (gCurrentBattleEntity->unk_4F != 0) {
            gBattleState.unk_00->unk_48 = 0x1B;
            return 0;
        }
        gCurrentBattleEntity->unk_4C &= 0xFFFE;
        MessageBank_SetPointer_0x14_0x2A(0x19, GetPokemonName(sActivePokemon[gBattleState.unk_00->unk_2C]));
        WriteMessageCharOrString(gBattleMessageBuffers->unk_0C8, 0x11);
        gCurrentBattleEntity->unk_44.unk_02 = 1;

        gCurrentDamage = gCurrentBattleEntity->unk_54 * 2;
        if (!gCurrentDamage) {
            gSpecialFlag = 1;
        }

        if ((D_8438AC60[0] == 1) && (gDefenderBattleEntity->unk_4C & 0x40)) {
            gSpecialFlag = 1;
        }

        gCurrentBattleEntity->unk_54 = 0;
        gCurrentBattleEntity->unk_44.unk_00 = 0x75;
        return 5;
    }

    if (gCurrentBattleEntity->unk_4C & 2) {
        gCurrentBattleEntity->unk_44.unk_00 = 0x25;
        MessageBank_SetPointer_0x14_0x2A(0x19, GetPokemonName(sActivePokemon[gBattleState.unk_00->unk_2C]));
        WriteMessageCharOrString(gBattleMessageBuffers->unk_0C8, 0x12);
        gCurrentBattleEntity->unk_4F -= 1;
        if (gCurrentBattleEntity->unk_4F != 0) {
            return 4;
        }

        WriteMessageCharOrString(gBattleMessageBuffers->unk_188, -0x45);
        gCurrentBattleEntity->unk_4C &= 0xFFFD;
        gCurrentBattleEntity->unk_4C |= 0x80;
        gCurrentBattleEntity->unk_50 = (GetRandomU8() & 3) + 2;
        return 4;
    }

    if (gCurrentBattleEntity->unk_4C & 0x20) {
        MessageBank_SetPointer_0x14_0x2A(0x19, GetPokemonName(sActivePokemon[gBattleState.unk_00->unk_2C]));
        WriteMessageCharOrString(gBattleMessageBuffers->unk_0C8, 0x13);
        gCurrentBattleEntity->unk_4F -= 1;
        return 6;
    }

    if (gCurrentBattleEntity->unk_4D & 0x40) {
        gCurrentBattleEntity->unk_44.unk_01 = 0;
        return 3;
    }
    return 2;
}

static const char gFmtInt[] = "%d";
static const char D_8438DC04[] = " SpAttackTbl6\n";

void ProcessBattleTurn(void) {
    UNUSED s32 pad;
    char sp2C[8];

    if (gCurrentBattleEntity->unk_5A != 0xFF) {
        gSpecialFlag = 0;
        gBattleUnusedFlag15 = 0;
        gBattleUnusedFlag4 = 0;
        gTypeEffectivenessMsgState = 0xA;

        switch (ProcessBattleEntityStatus()) {
            case 2:
                func_84370E80();
                if (gCurrentBattleEntity->unk_4C & 0x10) {
                    gCurrentBattleEntity->unk_4C &= ~0x50;
                    SetEntityAnimFlags(sActivePokemon[gBattleState.unk_00->unk_2C], 8);
                } else {
                block_5:
                    switch (gCurrentBattleEntity->unk_44.unk_01) {
                        case 0x27:
                        case 0x2B:
                            if (D_8438AC60[0] == 1) {
                                gCurrentDamage = 0;
                            }
                            SpAttack_Main();
                            gCurrentBattleEntity->unk_58 = gCurrentBattleEntity->unk_5A;
                            return;
                    }
                }

            case 3:
                DetermineMessageCategoryAndDisplay();
                DecrementMovePP(gBattleState.unk_00->unk_2C);

                if (IsByteInArray(gCurrentBattleEntity->unk_44.unk_01, gBattleMoveEffectTable1, 0x10) != 0) {
                    if (D_8438AC60[0] == 1) {
                        gCurrentDamage = 0;
                    }
                    SpAttack_Main();
                    return;
                }

                if (IsByteInArray(gCurrentBattleEntity->unk_44.unk_01, gBattleMoveEffectTable2, 1) != 0) {
                    SpAttack_Main();
                }

            case 4:
                if (IsByteInArray(gCurrentBattleEntity->unk_44.unk_01, gBattleMoveEffectTable3, 2) == 0) {
                    Battle_CheckCriticalHit();
                    if (Battle_Effect_Counter() == 0) {
                        goto case_5;
                    }

                    InitBattleParameters();
                    if (UpdateDamageAccumulator() == 0) {
                        goto case_6;
                    }

                    Battle_ApplyTypeEffectAndSTAB();
                    ApplyDamageRandomFactor();
                }

                if (D_8438AC60[0] == 1) {
                    gCurrentBattleEntity->unk_44.unk_04 = gMoveBattleData[gCurrentBattleEntity->unk_5A - 1].unk_04;
                }
                HandleMoveEffectFlags();

            case 5:
            case_5:
                if (gSpecialFlag != 0) {
                    switch (gCurrentBattleEntity->unk_44.unk_01) {
                        case 7:
                            break;
                    }
                // The unk_4F retry jumps here rather than straight to case_6.
                loop_4F:
                    goto case_6;
                }

            case 6:
            case_6:
                switch (gCurrentBattleEntity->unk_44.unk_01) {
                    case 9:
                        if (Battle_TryLoadFollowupMoveFromTarget() == 0) {
                            goto end;
                        }
                        gBattleUnusedFlag15 = 0;
                        goto block_5;

                    case 0x53:
                        Battle_Effect_Metronome();
                        goto block_5;
                }

                if (IsByteInArray(gCurrentBattleEntity->unk_44.unk_01, gBattleMoveEffectTable4, 0x1B) != 0) {
                    SpAttack_Main();
                    return;
                }

                if (gSpecialFlag != 0) {
                    Battle_QueueMoveFailureAndApplyRecoil();

                    if (gCurrentBattleEntity->unk_44.unk_01 != 7) {
                        goto end;
                    }
                } else {
                    func_8437114C();
                    func_84371080();
                    func_84371010();
                    gBattleUnusedFlag4 = 1;
                }

                if (IsByteInArray(gCurrentBattleEntity->unk_44.unk_01, gBattleMoveEffectTable5, 0xA) != 0) {
                    SpAttack_Main();
                }

                if (gDefenderBattleEntity->unk_0C == 0) {
                    if (D_8438AC60[0] == 1) {
                        switch (gCurrentBattleEntity->unk_44.unk_01) {
                            case 0x50:
                                gCurrentDamage = 0;
                                return;
                        }
                    }
                    return;
                }

                Battle_ApplyRageContinuation();

                if (gCurrentBattleEntity->unk_4C & 4) {
                    gCurrentBattleEntity->unk_4F -= 1;
                    if (gCurrentBattleEntity->unk_4F != 0) {
                        goto loop_4F;
                    }
                    gCurrentBattleEntity->unk_4C &= ~4;
                    sprintf(sp2C, gFmtInt, gCurrentBattleEntity->unk_54);
                    MessageBank_SetPointer_1_9(2, gCurrentBattleEntity->unk_54);
                    WriteMessageCharOrString(gBattleMessageBuffers->unk_3C8, 4);
                    gBattleState.unk_00->unk_1A = 1;
                    gCurrentBattleEntity->unk_54 = 0;
                    gCurrentDamage = gAccumulatedDamage;
                }

                if (gCurrentBattleEntity->unk_44.unk_01 == 0) {
                    goto end;
                }

                if (IsByteInArray(gCurrentBattleEntity->unk_44.unk_01, gBattleMoveEffectTable6, 0xF) != 0) {
                    goto end;
                }

                SpAttack_Main();
                goto end;
        }
    }
end:
    gBattleUnusedFlag17 = 0;
}

void ResetBattleEntityStatus(unk_BattlePlayerEntity* arg0) {
    s32 sp1C = IsPrimaryEntity(arg0);
    unk_BattlePlayerAnimState* temp_a10;
    unk_D_800FCB18* temp_a11;
    unk_D_800FCB18* temp_a01;

    temp_a10 = &sActivePokemon[sp1C]->unk_654;
    temp_a11 = &sActivePokemon[sp1C]->unk_654.unk_38;
    temp_a01 = &sActivePokemon[!sp1C]->unk_654.unk_38;

    temp_a01->unk_54 = 0;
    temp_a01->unk_58 = 0;
    temp_a01->unk_4C &= ~4;

    temp_a11->unk_4A = 0;
    temp_a11->unk_4B = 0;
    temp_a11->unk_4C = 0;
    temp_a11->unk_4D &= 0x80;
    temp_a11->unk_4E = 0;
    temp_a11->unk_52 = 0;
    temp_a11->unk_57 = 0;
    temp_a11->unk_56 = 0;
    temp_a11->unk_58 = 0;

    if (temp_a10->unk_2D != 0xF) {
        temp_a10->unk_2D = 0x11;
    }

    func_8436FA80(arg0);
    MessageBank_SetPointer_0x14_0x2A(0x19, GetPokemonName(sActivePokemon[sp1C]));
    WriteMessageCharOrString(gBattleMessageBuffers->unk_448[sp1C], 3);
}

void CheckAllPartyFainted_HP(unk_BattlePlayerEntity* arg0) {
    unk_BattlePlayerAnimState* ptr1 = &arg0->unk_654;
    PokemonData* temp_v0;
    s32 i;
    s32 var_s2 = 0;

    for (i = 0; i < BattleScene_GetSelectedSideTeamSize(arg0); i++) {
        if (i == ptr1->unk_08) {
            var_s2 += arg0->unk_654.unk_38.unk_0E;
        } else {
            temp_v0 = &arg0->unk_724->unk_01C[i];
            var_s2 += temp_v0->unk_02;
        }
    }

    if (arg0->unk_720->unk_01 == 2) {
        for (i = 0; i < GetOpponentPokemonCount(arg0); i++) {
            temp_v0 = &arg0->unk_720->unk_08[!ptr1->unk_2B]->unk_01C[i];
            var_s2 += temp_v0->unk_02;
        }
    }

    if (var_s2 == 0) {
        func_8436FA80(arg0);
        ptr1->unk_2D = 0x12;
    } else {
        ResetBattleEntityStatus(arg0);
    }
}

void CheckAllPartyFainted_Status(unk_BattlePlayerEntity* arg0) {
    unk_BattlePlayerAnimState* ptr1 = &arg0->unk_654;
    PokemonData* temp_v0;
    s32 i;
    s32 var_s2 = 0;

    for (i = 0; i < BattleScene_GetSelectedSideTeamSize(arg0); i++) {
        if (i == ptr1->unk_08) {
            var_s2 += arg0->unk_654.unk_38.unk_10;
        } else {
            temp_v0 = &arg0->unk_724->unk_01C[i];
            var_s2 += temp_v0->unk_02;
        }
    }

    if (arg0->unk_720->unk_01 == 2) {
        for (i = 0; i < GetOpponentPokemonCount(arg0); i++) {
            temp_v0 = &arg0->unk_720->unk_08[!ptr1->unk_2B]->unk_01C[i];
            var_s2 += temp_v0->unk_02;
        }
    }

    if (var_s2 == 0) {
        func_8436FA80(arg0);
        ptr1->unk_2D = 0x12;
    } else {
        ResetBattleEntityStatus(arg0);
    }
}

void CheckAllPartyFainted_PP(unk_BattlePlayerEntity* arg0) {
    unk_BattlePlayerAnimState* ptr1 = &arg0->unk_654;
    PokemonData* temp_v0;
    s32 i;
    s32 var_s2 = 0;

    for (i = 0; i < BattleScene_GetSelectedSideTeamSize(arg0); i++) {
        if (i == ptr1->unk_08) {
            var_s2 += arg0->unk_654.unk_38.unk_12;
        } else {
            temp_v0 = &arg0->unk_724->unk_01C[i];
            var_s2 += temp_v0->unk_02;
        }
    }

    if (arg0->unk_720->unk_01 == 2) {
        for (i = 0; i < GetOpponentPokemonCount(arg0); i++) {
            temp_v0 = &arg0->unk_720->unk_08[!ptr1->unk_2B]->unk_01C[i];
            var_s2 += temp_v0->unk_02;
        }
    }

    if (var_s2 == 0) {
        func_8436FA80(arg0);
        ptr1->unk_2D = 0x12;
    } else {
        ResetBattleEntityStatus(arg0);
    }
}

void CheckAllPartyFainted_Level(unk_BattlePlayerEntity* arg0) {
    unk_BattlePlayerAnimState* ptr1 = &arg0->unk_654;
    PokemonData* temp_v0;
    s32 i;
    s32 var_s2 = 0;

    for (i = 0; i < BattleScene_GetSelectedSideTeamSize(arg0); i++) {
        if (i == ptr1->unk_08) {
            var_s2 += arg0->unk_654.unk_38.unk_0C;
        } else {
            temp_v0 = &arg0->unk_724->unk_01C[i];
            var_s2 += temp_v0->unk_02;
        }
    }

    if (arg0->unk_720->unk_01 == 2) {
        for (i = 0; i < GetOpponentPokemonCount(arg0); i++) {
            temp_v0 = &arg0->unk_720->unk_08[!ptr1->unk_2B]->unk_01C[i];
            var_s2 += temp_v0->unk_02;
        }
    }

    if (var_s2 == 0) {
        func_8436FA80(arg0);
        ptr1->unk_2D = 0x12;
    } else {
        ResetBattleEntityStatus(arg0);
    }
}

s32 CheckBattleEntityFaintStatus(unk_BattlePlayerEntity* arg0) {
    unk_BattlePlayerAnimState* ptr1 = &arg0->unk_654;
    PokemonData* temp_v0;
    s32 i;
    s32 var_s2;

    if (arg0->unk_654.unk_38.unk_15 & 0x18) {
        var_s2 = 0;
        if (arg0->unk_654.unk_38.unk_0E == 0) {
            for (i = 0; i < BattleScene_GetSelectedSideTeamSize(arg0); i++) {
                temp_v0 = &arg0->unk_724->unk_01C[i];
                var_s2 += temp_v0->unk_02;
            }

            if (arg0->unk_720->unk_01 == 2) {
                for (i = 0; i < GetOpponentPokemonCount(arg0); i++) {
                    temp_v0 = &arg0->unk_720->unk_08[!ptr1->unk_2B]->unk_01C[i];
                    var_s2 += temp_v0->unk_02;
                }
            }

            if (var_s2 == 0) {
                ptr1->unk_2D = 0x12;
                return 1;
            }
            ResetBattleEntityStatus(arg0);
        }
        return 1;
    }
    return 0;
}

s32 ProcessFaintChecks(void) {
    if (gDefenderBattleEntity->unk_0C == 0) {
        CheckAllPartyFainted_Level(sActivePokemon[!gBattleState.unk_00->unk_2C]);
    }

    if (gCurrentBattleEntity->unk_0C == 0) {
        CheckAllPartyFainted_Level(sActivePokemon[gBattleState.unk_00->unk_2C]);
    }

    if ((gCurrentBattleEntity->unk_0C != 0) && (gDefenderBattleEntity->unk_0C != 0) && (gCurrentBattleEntity->unk_12 == 0)) {
        CheckAllPartyFainted_PP(sActivePokemon[gBattleState.unk_00->unk_2C]);
        return 0;
    } else if ((gCurrentBattleEntity->unk_0C != 0) && (gDefenderBattleEntity->unk_0C != 0) && (gCurrentBattleEntity->unk_15 & 0x18) &&
               (gCurrentBattleEntity->unk_0E == 0)) {
        CheckAllPartyFainted_HP(sActivePokemon[gBattleState.unk_00->unk_2C]);
        return 0;
    } else if ((gCurrentBattleEntity->unk_0C != 0) && (gDefenderBattleEntity->unk_0C != 0) && (gCurrentBattleEntity->unk_4D & 0x80) &&
               (gCurrentBattleEntity->unk_10 == 0)) {
        CheckAllPartyFainted_Status(sActivePokemon[gBattleState.unk_00->unk_2C]);
        return 0;
    }
}

void BeginBattleMainLoop(void) {
    unk_D_800FCB18* sp1C = &sActivePokemon[gBattleState.unk_00->unk_2C]->unk_654.unk_38;
    unk_D_800FCB18* sp18 = &sActivePokemon[!gBattleState.unk_00->unk_2C]->unk_654.unk_38;
    unk_BattlePlayerAnimState* ptr1 = &sActivePokemon[0]->unk_654;
    unk_BattlePlayerAnimState* ptr2 = &sActivePokemon[1]->unk_654;

    ptr1->unk_2A = 0;
    ptr2->unk_2A = 0;

    gIsBattleMode = 1;
    gAnimStateFlag = 1;

    gBattleState.unk_00->unk_1A = 0;

    gBattleState.unk_00->unk_4C = 0;
    gBattleState.unk_00->unk_48 = 0;

    sp1C->unk_12 = 0xFFFF;
    sp18->unk_12 = 0xFFFF;

    gAccumulatedDamage = 0;

    ResetDialogBuffers();
    Battle_ApplyAnimStateEffects(sActivePokemon[0]);
    Battle_ApplyAnimStateEffects(sActivePokemon[1]);

    gCurrentBattleEntity = sp1C;
    gDefenderBattleEntity = sp18;
    ProcessBattleTurn();
    Battle_ApplyResidualEffects();

    if (gBattleUpdateHPFlag == 0) {
        ProcessFaintChecks();
    }
}

void BeginBattleForEntity(unk_BattlePlayerEntity* arg0) {
    unk_BattlePlayerAnimState* sp24;
    unk_BattlePlayerAnimState* sp20;
    unk_D_800FCB18* ptr1;
    unk_D_800FCB18* ptr2;

    ptr1 = &arg0->unk_654.unk_38;

    sp24 = &sActivePokemon[0]->unk_654;
    sp20 = &sActivePokemon[1]->unk_654;

    ptr2 = &sActivePokemon[IsPrimaryEntity(arg0) == 0]->unk_654.unk_38;

    sp24->unk_2A = 0;
    sp20->unk_2A = 0;
    ptr1->unk_12 = 0xFFFF;
    ptr2->unk_12 = 0xFFFF;

    gIsBattleMode = 1;
    gAnimStateFlag = 1;

    gBattleState.unk_00->unk_48 = 0;
    gBattleState.unk_00->unk_4C = 0;

    gCurrentBattleEntity = ptr1;
    gDefenderBattleEntity = ptr2;

    func_8436FA80(arg0);
    Vec3f_Set(&arg0->unk_448.unk_00, 0.0f, 0.0f, 0.0f);
    Vec3f_Set(&arg0->unk_448.unk_0C, 0.0f, 0.0f, 0.0f);
    func_84370B7C(arg0);

    if (arg0 == sActivePokemon[0]) {
        ResetBattleAfterMove(0, 1);
    } else {
        ResetBattleAfterMove(1, 0);
    }
}
