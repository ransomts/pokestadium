#include "fragment62.h"
#include "src/2E110.h"

typedef void (*func_D_8438AE50)(void);

static const char D_8438DC80[] = "は\nこんらんした";
static const char D_8438DC90[] = "SP %d\n";
static const char D_8438DC98[] = "index %d  step %d\n";
static const char D_8438DCAC[] = "index %d  step %d\n";
static const char D_8438DCC0[] = "index %d\n";
static const char D_8438DCCC[] = "paramStep %d index %d  step %d\n";
static const char D_8438DCEC[] = "\n%%%%%%%%%%%%%%%%%%%%%%%\n";
static const char D_8438DD08[] = "INDEX %d   WARIKOMI %d\n";
static const char D_8438DD20[] = "%%%%%%%%%%%%%%%%%%%%%%%\n\n";
static const char D_8438DD3C[] = "FAIL\n";
static const char D_8438DD44[] = "index %d\n";
static const char D_8438DD50[] = "index %d\n";
static const char D_8438DD5C[] = "FAIL\n";
static const char D_8438DD64[] = "FAIL2\n";
static const char D_8438DD6C[] = "FAIL3\n";
static const char D_8438DD74[] = "offp->count1 %d\n";
static const char D_8438DD88[] = "\n\n";
static const char D_8438DD8C[] = "******** spAttackMain ********\n";
static const char D_8438DDAC[] = "!!!! SPATTACK Num %d!!!!\n";
static const char D_8438DDC8[] = "******** spAttackMainEnd ********\n";

static char* D_8438AE50 = D_8438DC80;
static func_D_8438AE50 D_8438AE54[] = {
    Battle_TurnStart, Battle_ProcessCommand, Battle_UpdateProgress, Battle_HandleItemEffect, Battle_HandleItemEffect, Battle_HandleItemEffect, Battle_ResetState,
    Battle_UpdateProgress, NULL,          Battle_ApplyStatChange, Battle_ApplyStatChange, Battle_ApplyStatChange, Battle_ApplyStatChange, Battle_ApplyStatChange,
    Battle_ApplyStatChange, func_84375D78, NULL,          Battle_HandleStatDecrease, Battle_HandleStatDecrease, Battle_HandleStatDecrease, Battle_HandleStatDecrease,
    Battle_HandleStatDecrease, Battle_HandleStatDecrease, func_84375DA4, func_84375E6C, Battle_InitPhase, func_84374D08, Battle_HandleSpecialMove,
    func_84374E08, func_84374E08, func_84374EE4, Battle_TurnStart, Battle_ProcessCommand, Battle_HandleItemEffect, Battle_HandleItemEffect,
    Battle_HandleItemEffect, func_84374EE4, func_84374FD4, Battle_DisplayStatusMessage, NULL,          NULL,          func_843751F8,
    Battle_DisplayStatusMessage, func_84374E08, NULL,          func_843752C0, func_84375384, func_84375424, func_843755E8,
    Battle_ApplyStatChange, Battle_ApplyStatChange, Battle_ApplyStatChange, Battle_ApplyStatChange, Battle_ApplyStatChange, Battle_ApplyStatChange, func_8437600C,
    func_84376258, Battle_HandleStatDecrease, Battle_HandleStatDecrease, Battle_HandleStatDecrease, Battle_HandleStatDecrease, Battle_HandleStatDecrease, Battle_HandleStatDecrease,
    func_843765E8, func_843765E8, Battle_ProcessCommand, func_84375700, Battle_HandleStatDecrease, Battle_HandleStatDecrease, Battle_HandleStatDecrease,
    Battle_HandleStatDecrease, Battle_HandleStatDecrease, Battle_HandleStatDecrease, Battle_HandleStatDecrease, Battle_HandleStatDecrease, Battle_StartMiniGame, func_84374E08,
    NULL,          func_84375894, func_843759C4, func_843759DC, func_843759F4, NULL,          func_84375B1C,
    func_84375C24, func_84375C60, NULL,
};

u16 ScaleStatValue(u16* arg0, u16 arg1, u8 arg2) {
    *arg0 = (arg1 * gStatStageMultipliers[arg2 - 1].unk_00) / gStatStageMultipliers[arg2 - 1].unk_01;

    if (*arg0 == 0) {
        *arg0 = 1;
    }

    if (*arg0 > 999) {
        *arg0 = 999;
    }

    return *arg0;
}

void Battle_TurnStart(void) {
    s32 sp24;
    s32 var_v1;

    gBattleState.unk_00->unk_48 = 0x16;
    sp24 = gDefenderBattleEntity->unk_4D & 0x20;
    gDefenderBattleEntity->unk_4D &= ~0x20;

    if (sp24 == 0) {
        if (gDefenderBattleEntity->unk_15 & 7) {
            gIsBattleMode = 0;
            MessageBank_SetPointer_0x14_0x2A(0x19, GetPokemonName(D_84390010[!gBattleState.unk_00->unk_2C]));
            WriteMessageCharOrString(gBattleMessageBuffers->unk_088, -0x80);
            return;
        }

        if (gDefenderBattleEntity->unk_15 == 0) {
            HandleMoveEffectFlags();
            if ((gSpecialFlag == 0) &&
                ((Battle_HasAbilityEffect(D_84390010[!gBattleState.unk_00->unk_2C]) == 0) || (D_8438AC60[0] == 2))) {
                goto block_9;
            }
        }
        gCurrentDamage = 0;
        gSpecialFlag = 1;
        gIsBattleMode = 0;
        MessageBank_SetPointer_0x14_0x2A(0x19, GetPokemonName(D_84390010[!gBattleState.unk_00->unk_2C]));
        WriteMessageCharOrString(gBattleMessageBuffers->unk_088, -0x7F);
        return;
    }

block_9:
    if ((Battle_HasAbilityEffect(D_84390010[!gBattleState.unk_00->unk_2C]) != 0) && (D_8438AC60[0] != 2)) {
        gIsBattleMode = 0;
        MessageBank_SetPointer_0x14_0x2A(0x19, GetPokemonName(D_84390010[!gBattleState.unk_00->unk_2C]));
        WriteMessageCharOrString(gBattleMessageBuffers->unk_088, -0x7F);
        if ((sp24 != 0) && (D_8438AC60[0] == 1)) {
            gDefenderBattleEntity->unk_4D |= 0x20;
        }
    } else {
        do {
            if (D_8438AC60[0] == 2) {
                var_v1 = GetRandomU8() & 7;
            } else {
                var_v1 = GetRandomU8() & 3;
            }
        } while (var_v1 == 0);
        gSpecialFlag = 0;
        gDefenderBattleEntity->unk_15 = var_v1;
        MessageBank_SetPointer_0x14_0x2A(0x19, GetPokemonName(D_84390010[!gBattleState.unk_00->unk_2C]));
        WriteMessageCharOrString(gBattleMessageBuffers->unk_088, -0x7E);
    }
}

void Battle_ProcessCommand(void) {
    char* sp1C = gBattleMessageBuffers->unk_088;

    if (!(gDefenderBattleEntity->unk_4D & 0x10) && (gDefenderBattleEntity->unk_15 == 0) && (gDefenderBattleEntity->unk_16[6] != 3) &&
        (gDefenderBattleEntity->unk_16[7] != 3)) {
        switch (gCurrentBattleEntity->unk_44.unk_01) {
            case 2:
                if (gBattleState.unk_00->unk_48 != 0x18) {
                    gBattleState.unk_00->unk_48 = 0;
                    sp1C = gBattleMessageBuffers->unk_208;
                } else {
                    sp1C = gBattleMessageBuffers->unk_308;
                }

                if (GetRandomU8() >= 0x34) {
                    return;
                }
                break;

            case 33:
                gBattleState.unk_00->unk_48 = 0;
                sp1C = gBattleMessageBuffers->unk_208;
                if (GetRandomU8() >= 0x67) {
                    return;
                }
                break;

            default:
                gBattleState.unk_00->unk_48 = 0x16;
                gAnimTimer = 0xA;
                HandleMoveEffectFlags();
                if (gSpecialFlag != 0) {
                    MessageBank_SetPointer_0x14_0x2A(0x19, GetPokemonName(D_84390010[!gBattleState.unk_00->unk_2C]));
                    WriteMessageCharOrString(sp1C, -0x7D);
                    return;
                }
                break;
        }

        gDefenderBattleEntity->unk_15 |= 8;
        if (gCurrentBattleEntity->unk_44.unk_00 == 0x5C) {
            gDefenderBattleEntity->unk_4E |= 1;
            gDefenderBattleEntity->unk_51 = 0;
            MessageBank_SetPointer_0x14_0x2A(0x19, GetPokemonName(D_84390010[!gBattleState.unk_00->unk_2C]));
            WriteMessageCharOrString(sp1C, -0x7C);
        } else {
            MessageBank_SetPointer_0x14_0x2A(0x19, GetPokemonName(D_84390010[!gBattleState.unk_00->unk_2C]));
            WriteMessageCharOrString(sp1C, -0x7B);
        }
    } else if (gCurrentBattleEntity->unk_44.unk_01 == 0x42) {
        if (gBattleState.unk_00->unk_48 != 0x18) {
            gSpecialFlag = 1;
            gBattleState.unk_00->unk_48 = 0x16;
            gIsBattleMode = 0;
        }
        MessageBank_SetPointer_0x14_0x2A(0x19, GetPokemonName(D_84390010[!gBattleState.unk_00->unk_2C]));
        WriteMessageCharOrString(sp1C, -0x7A);
    }
}

void Battle_UpdateProgress(void) {
    gCurrentDamage /= 2;
    if (gCurrentDamage == 0) {
        gCurrentDamage = 1;
    }

    if (gCurrentBattleEntity->unk_28 < gCurrentBattleEntity->unk_0C + gCurrentDamage) {
        gCurrentBattleEntity->unk_0C = gCurrentBattleEntity->unk_28;
    } else {
        gCurrentBattleEntity->unk_0C += gCurrentDamage;
    }

    if (gCurrentBattleEntity->unk_44.unk_01 == 8) {
        MessageBank_SetPointer_0x14_0x2A(0x19, GetPokemonName(D_84390010[!gBattleState.unk_00->unk_2C]));
        WriteMessageCharOrString(gBattleMessageBuffers->unk_208, -0x79);
    } else {
        MessageBank_SetPointer_0x14_0x2A(0x19, GetPokemonName(D_84390010[!gBattleState.unk_00->unk_2C]));
        WriteMessageCharOrString(gBattleMessageBuffers->unk_208, -0x78);
    }
}

void Battle_ResetState(void) {
    gBattleState.unk_00->unk_48 = 0x1E;
    gCurrentBattleEntity->unk_0C = 0;
    gCurrentBattleEntity->unk_15 = 0;
    gCurrentBattleEntity->unk_4D &= ~0x80;
}

void Battle_HandleItemEffect(void) {
    unk_D_800FCB18* temp_a2 = &D_84390010[!gBattleState.unk_00->unk_2C]->unk_654.unk_38;
    unk_BattlePlayerAnimState* temp_a0 = &D_84390010[!gBattleState.unk_00->unk_2C]->unk_654;

    if (gDefenderBattleEntity->unk_4D & 0x10) {
        return;
    }

    if (gDefenderBattleEntity->unk_15 != 0) {
        if ((gDefenderBattleEntity->unk_15 & 0x20) && (gCurrentBattleEntity->unk_44.unk_03 == 0x14)) {
            gDefenderBattleEntity->unk_15 = 0;
            if (temp_a0->unk_14 != 4) {
                temp_a2->unk_5A = temp_a2->unk_1F[temp_a0->unk_0C];
            } else {
                temp_a0->unk_14 = 0;
                temp_a0->unk_0C = 0;
                temp_a2->unk_5A = 0xA5;
            }
            MessageBank_SetPointer_0x14_0x2A(0x19, GetPokemonName(D_84390010[!gBattleState.unk_00->unk_2C]));
            WriteMessageCharOrString(gBattleMessageBuffers->unk_088, -0x77);
        }
        return;
    }

    if ((gDefenderBattleEntity->unk_16[6] != (*gCurrentBattleEntity).unk_44.unk_03) &&
        (gDefenderBattleEntity->unk_16[7] != (*gCurrentBattleEntity).unk_44.unk_03)) {
        if ((gCurrentBattleEntity->unk_44.unk_01 < 7) || ((D_8438AC60[0] != 2) && (gCurrentBattleEntity->unk_44.unk_00 == 0x3B))) {
            if (GetRandomU8() >= 0x1A) {
                return;
            }
        } else if (GetRandomU8() >= 0x4D) {
            return;
        }

        switch (gCurrentBattleEntity->unk_44.unk_01) {
            case 4:
            case 34:
                gDefenderBattleEntity->unk_15 = 0x10;
                ApplyBurnAttackCut(D_84390010[!gBattleState.unk_00->unk_2C]);
                MessageBank_SetPointer_0x14_0x2A(0x19, GetPokemonName(D_84390010[!gBattleState.unk_00->unk_2C]));
                WriteMessageCharOrString(gBattleMessageBuffers->unk_208, -0x76);
                break;

            case 5:
            case 35:
                if (Battle_HasStatusEffect(D_84390010[!gBattleState.unk_00->unk_2C]) == 0) {
                    gDefenderBattleEntity->unk_4D &= ~0x20;
                    gDefenderBattleEntity->unk_15 = 0x20;
                    MessageBank_SetPointer_0x14_0x2A(0x19, GetPokemonName(D_84390010[!gBattleState.unk_00->unk_2C]));
                    WriteMessageCharOrString(gBattleMessageBuffers->unk_208, -0x75);
                }
                break;

            case 6:
            case 36:
                gDefenderBattleEntity->unk_15 = 0x40;
                ApplyParalysisSpeedCut(D_84390010[!gBattleState.unk_00->unk_2C]);
                MessageBank_SetPointer_0x14_0x2A(0x19, GetPokemonName(D_84390010[!gBattleState.unk_00->unk_2C]));
                WriteMessageCharOrString(gBattleMessageBuffers->unk_208, -0x74);
                break;
        }
    }
}

void Battle_ApplyStatIncrease(void) {
    s32 sp2C;
    s32 sp28;
    s32 sp24;
    s32 var_a3;
    u16* sp1C;
    u16* sp18;

    gBattleState.unk_00->unk_4C = 0xA;

    var_a3 = 1;
    sp24 = gCurrentBattleEntity->unk_44.unk_01 - 0xA;

    if (sp24 >= 8) {
        var_a3 = 2;
        sp24 -= 0x28;
    }

    if (gCurrentBattleEntity->unk_5C[sp24] != 0xD) {
        gCurrentBattleEntity->unk_5C[sp24] += var_a3;
        if (gCurrentBattleEntity->unk_5C[sp24] >= 0xE) {
            gCurrentBattleEntity->unk_5C[var_a3] = 0xD;
        }

        sp28 = 0;
        sp2C = 0;

        if (sp24 < 4) {
            switch (sp24) {
                case 0:
                    sp18 = &gCurrentBattleEntity->unk_38;
                    sp1C = &gCurrentBattleEntity->unk_2A;
                    sp2C = 1;
                    break;

                case 1:
                    sp18 = &gCurrentBattleEntity->unk_3A;
                    sp1C = &gCurrentBattleEntity->unk_2C;
                    break;

                case 2:
                    sp18 = &gCurrentBattleEntity->unk_3C;
                    sp1C = &gCurrentBattleEntity->unk_2E;
                    sp28 = 1;
                    break;

                case 3:
                    sp18 = &gCurrentBattleEntity->unk_3E;
                    sp1C = &gCurrentBattleEntity->unk_30;
                    break;
            }

            if (*sp1C != 0x3E7) {
                *sp1C = (*sp18 * gStatStageMultipliers[gCurrentBattleEntity->unk_5C[sp24] - 1].unk_00) /
                        gStatStageMultipliers[gCurrentBattleEntity->unk_5C[sp24] - 1].unk_01;
                if (*sp1C >= 0x3E8) {
                    *sp1C = 0x3E7;
                }
            } else {
                goto block_29;
            }
        }

        if (gCurrentBattleEntity->unk_44.unk_00 == 0x6B) {
            gCurrentBattleEntity->unk_56 = 1;
        }

        if (var_a3 == 2) {
            MessageBank_SetPointer_0x14_0x2A(0x19, GetPokemonName(D_84390010[!gBattleState.unk_00->unk_2C]));
            WriteMessageCharOrString(gBattleMessageBuffers->unk_2C8, sp24 + 0x8D);
        } else {
            MessageBank_SetPointer_0x14_0x2A(0x19, GetPokemonName(D_84390010[!gBattleState.unk_00->unk_2C]));
            WriteMessageCharOrString(gBattleMessageBuffers->unk_2C8, sp24 + 0x93);
        }

        if ((sp28 != 0) || (D_8438AC60[0] != 1)) {
            ApplyParalysisSpeedCut(D_84390010[!gBattleState.unk_00->unk_2C]);
        }

        if ((sp2C != 0) || (D_8438AC60[0] != 1)) {
            ApplyBurnAttackCut(D_84390010[!gBattleState.unk_00->unk_2C]);
        }
    } else {
    block_29:
        WriteMessageCharOrString(gBattleMessageBuffers->unk_2C8, -0x67);
    }
}

void Battle_ApplyStatChange(void) {
    s32 sp2C;
    s32 sp28;
    s32 sp24;
    s32 var_a3;
    u16* sp1C;
    u16* sp18;

    if (gCurrentBattleEntity->unk_44.unk_00 == 0x6E) {
        gBattleState.unk_00->unk_48 = 0x26;
    } else {
        gBattleState.unk_00->unk_48 = 7;
    }

    var_a3 = 1;
    sp24 = gCurrentBattleEntity->unk_44.unk_01 - 0xA;
    if (sp24 >= 8) {
        var_a3 = 2;
        sp24 -= 0x28;
    }

    if (gCurrentBattleEntity->unk_5C[sp24] != 0xD) {
        gCurrentBattleEntity->unk_5C[sp24] += var_a3;
        if (gCurrentBattleEntity->unk_5C[sp24] >= 0xE) {
            gCurrentBattleEntity->unk_5C[sp24] = 0xD;
        }

        sp28 = 0;
        sp2C = 0;

        if (sp24 < 4) {
            switch (sp24) {
                case 0:
                    sp18 = &gCurrentBattleEntity->unk_38;
                    sp1C = &gCurrentBattleEntity->unk_2A;
                    sp2C = 1;
                    break;

                case 1:
                    sp18 = &gCurrentBattleEntity->unk_3A;
                    sp1C = &gCurrentBattleEntity->unk_2C;
                    break;

                case 2:
                    sp18 = &gCurrentBattleEntity->unk_3C;
                    sp1C = &gCurrentBattleEntity->unk_2E;
                    sp28 = 1;
                    break;

                case 3:
                    sp18 = &gCurrentBattleEntity->unk_3E;
                    sp1C = &gCurrentBattleEntity->unk_30;
                    break;
            }

            if (*sp1C != 0x3E7) {
                *sp1C = (*sp18 * gStatStageMultipliers[gCurrentBattleEntity->unk_5C[sp24] - 1].unk_00) /
                        gStatStageMultipliers[gCurrentBattleEntity->unk_5C[sp24] - 1].unk_01;
                if (*sp1C >= 0x3E8) {
                    *sp1C = 0x3E7;
                }
            } else {
                goto block_32;
            }
        }

        if (gCurrentBattleEntity->unk_44.unk_00 == 0x6B) {
            gCurrentBattleEntity->unk_56 = 1;
        }

        if (var_a3 == 2) {
            MessageBank_SetPointer_0x14_0x2A(0x19, GetPokemonName(D_84390010[gBattleState.unk_00->unk_2C]));
            WriteMessageCharOrString(gBattleMessageBuffers->unk_088, sp24 + 0x8D);
        } else {
            MessageBank_SetPointer_0x14_0x2A(0x19, GetPokemonName(D_84390010[gBattleState.unk_00->unk_2C]));
            WriteMessageCharOrString(gBattleMessageBuffers->unk_088, sp24 + 0x93);
        }

        if ((sp28 != 0) || (D_8438AC60[0] != 1)) {
            ApplyParalysisSpeedCut(D_84390010[gBattleState.unk_00->unk_2C]);
        }

        if ((sp2C != 0) || (D_8438AC60[0] != 1)) {
            ApplyBurnAttackCut(D_84390010[gBattleState.unk_00->unk_2C]);
        }
    } else {
    block_32:
        gAnimStateFlag = 0;
        WriteMessageCharOrString(gBattleMessageBuffers->unk_088, -0x67);
    }
}

void Battle_HandleStatDecrease(void) {
    s32 sp2C;
    s32 sp28;
    s32 sp24;
    s32 sp20;
    u16* sp1C;
    u16* sp18;

    if (gCurrentBattleEntity->unk_44.unk_01 < 0x44) {
        gBattleState.unk_00->unk_48 = 0x1A;
    } else {
        gBattleState.unk_00->unk_1A = 3;
    }

    if (gDefenderBattleEntity->unk_4D & 0x10) {
        goto end;
    }

    sp24 = gCurrentBattleEntity->unk_44.unk_01;
    sp20 = 1;

    if (sp24 >= 0x44) {
        if (GetRandomU8() < 0x55) {
            sp24 -= 0x44;
            goto block_14;
        }
    } else {
        HandleMoveEffectFlags();

        if (gSpecialFlag != 0) {
            goto end;
        }

        if (gDefenderBattleEntity->unk_4C & 0x40) {
            goto end;
        }

        sp24 -= 0x12;
        if (sp24 >= 9) {
            sp20 = 2;
            sp24 -= 0x28;
        }

    block_14:
        if (gDefenderBattleEntity->unk_5C[sp24] != 1) {
            gDefenderBattleEntity->unk_5C[sp24] -= sp20;
            if (gDefenderBattleEntity->unk_5C[sp24] <= 0) {
                gDefenderBattleEntity->unk_5C[sp24] = 1;
            }

            sp28 = 0;
            sp2C = 0;

            if (sp24 < 4) {
                switch (sp24) {
                    case 0:
                        sp2C = 1;
                        sp18 = &gDefenderBattleEntity->unk_38;
                        sp1C = &gDefenderBattleEntity->unk_2A;
                        break;

                    case 1:
                        sp18 = &gDefenderBattleEntity->unk_3A;
                        sp1C = &gDefenderBattleEntity->unk_2C;
                        break;

                    case 2:
                        sp28 = 1;
                        sp18 = &gDefenderBattleEntity->unk_3C;
                        sp1C = &gDefenderBattleEntity->unk_2E;
                        break;

                    case 3:
                        sp18 = &gDefenderBattleEntity->unk_3E;
                        sp1C = &gDefenderBattleEntity->unk_30;
                        break;
                }

                if (*sp1C != 1) {
                    *sp1C = (*sp18 * gStatStageMultipliers[gDefenderBattleEntity->unk_5C[sp24] - 1].unk_00) /
                            gStatStageMultipliers[gDefenderBattleEntity->unk_5C[sp24] - 1].unk_01;
                    if (*sp1C == 0) {
                        *sp1C = 1;
                    }
                } else {
                    goto block_39;
                }
            }

            if (sp20 == 2) {
                MessageBank_SetPointer_0x14_0x2A(0x19, GetPokemonName(D_84390010[!gBattleState.unk_00->unk_2C]));
                WriteMessageCharOrString(gBattleMessageBuffers->unk_208, sp24 + 0x9A);
            } else {
                MessageBank_SetPointer_0x14_0x2A(0x19, GetPokemonName(D_84390010[!gBattleState.unk_00->unk_2C]));
                WriteMessageCharOrString(gBattleMessageBuffers->unk_208, sp24 + 0xA0);
            }

            if ((sp28 != 0) || (D_8438AC60[0] != 1)) {
                ApplyParalysisSpeedCut(D_84390010[!gBattleState.unk_00->unk_2C]);
            }

            if ((sp2C != 0) || (D_8438AC60[0] != 1)) {
                ApplyBurnAttackCut(D_84390010[!gBattleState.unk_00->unk_2C]);
            }
            return;
        }
    }

block_39:
    if (gCurrentBattleEntity->unk_44.unk_01 < 0x44) {
        gIsBattleMode = 0;
        gAnimStateFlag = 0;
        WriteMessageCharOrString(gBattleMessageBuffers->unk_088, -0x5A);
        return;
    }

end:
    if (gCurrentBattleEntity->unk_44.unk_01 < 0x44) {
        gIsBattleMode = 0;
        gAnimStateFlag = 0;
        if (gBattleUnusedFlag4 == 0) {
            WriteMessageCharOrString(gBattleMessageBuffers->unk_088, -0x59);
        }
    } else {
        gAnimStateFlag = 0;
    }
}

void Battle_InitPhase(void) {
    gBattleState.unk_00->unk_48 = 0x1B;
    gCurrentBattleEntity->unk_44.unk_01 = 0;
    gCurrentBattleEntity->unk_4C |= 1;
    gCurrentBattleEntity->unk_54 = 0;
    gCurrentBattleEntity->unk_4F = (GetRandomU8() & 1) + 2;
}

void func_84374D08(void) {
    gCurrentBattleEntity->unk_44.unk_01 = 0;
    gCurrentBattleEntity->unk_4C |= 2;
    gCurrentBattleEntity->unk_4F = (GetRandomU8() & 1) + 2;
}

void Battle_HandleSpecialMove(void) {
    if (gCurrentBattleEntity->unk_44.unk_00 == 0x64) {
        gBattleState.unk_00->unk_48 = 0x27;
        WriteMessageCharOrString(gBattleMessageBuffers->unk_088, -0x53);
        return;
    }
    gBattleState.unk_00->unk_48 = 8;
    MessageBank_SetPointer_0x14_0x2A(0x19, GetPokemonName(D_84390010[!gBattleState.unk_00->unk_2C]));
    WriteMessageCharOrString(gBattleMessageBuffers->unk_088, -0x52);
}

void func_84374E08(void) {
    s32 var_v1;

    if (!(gCurrentBattleEntity->unk_4C & 4)) {
        gCurrentBattleEntity->unk_4C |= 4;

        switch (gCurrentBattleEntity->unk_44.unk_01) {
            case 0x4D:
                gCurrentBattleEntity->unk_44.unk_01 = 2;

            case 0x2C:
                gCurrentBattleEntity->unk_54 = 2;
                gCurrentBattleEntity->unk_4F = gCurrentBattleEntity->unk_54;
                break;

            default:
                var_v1 = GetRandomU8() & 3;
                if (var_v1 >= 2) {
                    var_v1 = GetRandomU8() & 3;
                }
                gCurrentBattleEntity->unk_4F = gCurrentBattleEntity->unk_54 = var_v1 + 2;
                break;
        }

        gTotalMoveCount = gCurrentBattleEntity->unk_54 - 1;
        gBattleState.unk_00->unk_48 = 0x18;
    }
}

void func_84374EE4(void) {
    if (!(gDefenderBattleEntity->unk_4D & 0x10)) {
        if (D_8438AC60[0] == 1) {
            if (gCurrentBattleEntity->unk_44.unk_01 == 0x1F) {
                if (GetRandomU8() >= 0x1A) {
                    return;
                }
            } else if (GetRandomU8() >= 0x4D) {
                return;
            }
        } else {
            gDefenderBattleEntity->unk_4D &= ~0x20;
            if (gCurrentBattleEntity->unk_44.unk_01 == 0x1F) {
                if (GetRandomU8() >= 0x1A) {
                    return;
                }
            } else if (GetRandomU8() >= 0x4D) {
                return;
            }
        }
        gDefenderBattleEntity->unk_4C |= 8;
    }
}

void func_84374FD4(void) {
    gCurrentDamage = 0;
    gBattleEffectType = 0xFF;
    if (gCurrentBattleEntity->unk_2E < gDefenderBattleEntity->unk_2E) {
        gSpecialFlag = 1;
        return;
    }
    gCurrentDamage = 0xFFFF;
    gBattleEffectType = 2;
}

void Battle_DisplayStatusMessage(void) {
    gBattleState.unk_00->unk_48 = 0xE;
    gCurrentBattleEntity->unk_4C |= 0x10;

    if ((gCurrentBattleEntity->unk_44.unk_01 == 0x2B) || (gCurrentBattleEntity->unk_44.unk_00 == 0x5B)) {
        gCurrentBattleEntity->unk_4C |= 0x40;
        if (gCurrentBattleEntity->unk_44.unk_00 == 0x5B) {
            gBattleState.unk_00->unk_48 = 0xD;
        }

        if (gCurrentBattleEntity->unk_44.unk_01 == 0x2B) {
            gBattleState.unk_00->unk_48 = 0xC;
        }
    }

    MessageBank_SetPointer_0x14_0x2A(0x19, GetPokemonName(D_84390010[gBattleState.unk_00->unk_2C]));

    switch (gCurrentBattleEntity->unk_44.unk_00) {
        case 0xD:
            WriteMessageCharOrString(gBattleMessageBuffers->unk_0C8, -0x51);
            break;

        case 0x4C:
            WriteMessageCharOrString(gBattleMessageBuffers->unk_0C8, -0x50);
            break;

        case 0x82:
            WriteMessageCharOrString(gBattleMessageBuffers->unk_0C8, -0x4F);
            break;

        case 0x8F:
            WriteMessageCharOrString(gBattleMessageBuffers->unk_0C8, -0x4E);
            break;

        case 0x13:
            WriteMessageCharOrString(gBattleMessageBuffers->unk_148, -0x4D);
            break;

        case 0x5B:
            WriteMessageCharOrString(gBattleMessageBuffers->unk_148, -0x4C);
            break;
    }
}

void func_843751F8(void) {
    s32 var_v1;

    if (!(gCurrentBattleEntity->unk_4C & 0x20) && ((D_8438AC60[0] != 1) || (gCurrentBattleEntity->unk_44.unk_03 != 0) ||
                                         ((gDefenderBattleEntity->unk_16[6] != 8) && (gDefenderBattleEntity->unk_16[7] != 8)))) {
        gDefenderBattleEntity->unk_4D &= 0xFFDF;
        gCurrentBattleEntity->unk_4C |= 0x20;
        var_v1 = GetRandomU8() & 3;
        if (var_v1 >= 2) {
            var_v1 = GetRandomU8() & 3;
        }
        gCurrentBattleEntity->unk_4F = var_v1 + 1;
    }
}

void func_843752C0(void) {
    if (gCurrentBattleEntity->unk_4D & 2) {
        gBattleState.unk_00->unk_48 = 7;
        WriteMessageCharOrString(gBattleMessageBuffers->unk_088, -0x4B);
        return;
    }
    gBattleState.unk_00->unk_48 = 7;
    gCurrentBattleEntity->unk_4D |= 2;
    MessageBank_SetPointer_0x14_0x2A(0x19, GetPokemonName(D_84390010[gBattleState.unk_00->unk_2C]));
    WriteMessageCharOrString(gBattleMessageBuffers->unk_088, -0x4A);
}

void func_84375384(void) {
    gBattleState.unk_00->unk_48 = 7;
    if (gCurrentBattleEntity->unk_4D & 4) {
        WriteMessageCharOrString(gBattleMessageBuffers->unk_088, -0x49);
        return;
    }
    gCurrentBattleEntity->unk_4D |= 4;
    MessageBank_SetPointer_0x14_0x2A(0x19, GetPokemonName(D_84390010[gBattleState.unk_00->unk_2C]));
    WriteMessageCharOrString(gBattleMessageBuffers->unk_088, -0x48);
}

void func_84375424(void) {
    s32 var_v1;

    gCurrentBattleEntity->unk_12 = gCurrentBattleEntity->unk_0C;

    if (gCurrentBattleEntity->unk_44.unk_00 == 0xA5) {
        var_v1 = gCurrentDamage >> 1;
    } else {
        var_v1 = gCurrentDamage >> 2;
    }

    if (var_v1 == 0) {
        var_v1 += 1;
    }

    if (gCurrentBattleEntity->unk_12 < var_v1) {
        gCurrentBattleEntity->unk_12 = 0;
    } else {
        gCurrentBattleEntity->unk_12 -= var_v1;
    }

    gDefenderBattleEntity->unk_12 = gDefenderBattleEntity->unk_0C;
    MessageBank_SetPointer_0x14_0x2A(0x19, GetPokemonName(D_84390010[gBattleState.unk_00->unk_2C]));
    WriteMessageCharOrString(gBattleMessageBuffers->unk_408, -0x47);
    gBattleState.unk_00->unk_48 = 9;
}

void Battle_StartMiniGame(void) {
    if (!(gDefenderBattleEntity->unk_4D & 0x10) && (GetRandomU8() < 0x1A) && !(gDefenderBattleEntity->unk_4C & 0x80)) {
        gBattleState.unk_00->unk_1A = 3;
        gAnimStateFlag = 0;
        gDefenderBattleEntity->unk_4C |= 0x80;
        gDefenderBattleEntity->unk_50 = (GetRandomU8() & 3) + 2;
        MessageBank_SetPointer_0x14_0x2A(0x19, GetPokemonName(D_84390010[!gBattleState.unk_00->unk_2C]));
        WriteMessageCharOrString(gBattleMessageBuffers->unk_208, -0x46);
    }
}

void func_843755E8(void) {
    gBattleState.unk_00->unk_48 = 0x16;
    gIsBattleMode = 0;

    if (!(gDefenderBattleEntity->unk_4D & 0x10)) {
        HandleMoveEffectFlags();
        if ((gSpecialFlag == 0) && !(gDefenderBattleEntity->unk_4C & 0x80)) {
            gIsBattleMode = 1;
            gDefenderBattleEntity->unk_4C |= 0x80;
            gDefenderBattleEntity->unk_50 = (GetRandomU8() & 3) + 2;
            MessageBank_SetPointer_0x14_0x2A(0x19, GetPokemonName(D_84390010[!gBattleState.unk_00->unk_2C]));
            WriteMessageCharOrString(gBattleMessageBuffers->unk_088, -0x45);
            return;
        }
    }

    if (gBattleUnusedFlag4 == 0) {
        WriteMessageCharOrString(gBattleMessageBuffers->unk_088, -0x44);
    }
}

void func_84375700(void) {
    gBattleState.unk_00->unk_48 = 0x16;
    if (gDefenderBattleEntity->unk_15 == 0) {
        if ((gCurrentBattleEntity->unk_44.unk_03 != 0x17) || ((gDefenderBattleEntity->unk_16[6] != 4) && (gDefenderBattleEntity->unk_16[7] != 4))) {
            HandleMoveEffectFlags();
            if (gSpecialFlag == 0) {
                gDefenderBattleEntity->unk_15 |= 0x40;
                ApplyParalysisSpeedCut(D_84390010[!gBattleState.unk_00->unk_2C]);
                MessageBank_SetPointer_0x14_0x2A(0x19, GetPokemonName(D_84390010[!gBattleState.unk_00->unk_2C]));
                WriteMessageCharOrString(gBattleMessageBuffers->unk_088, -0x43);
                return;
            }
        } else {
            gBattleState.unk_00->unk_48 = 8;
            gIsBattleMode = 0;
            WriteMessageCharOrString(gBattleMessageBuffers->unk_088, -0x42);
            return;
        }
    }

    gBattleState.unk_00->unk_48 = 8;
    gIsBattleMode = 0;
    MessageBank_SetPointer_0x14_0x2A(0x19, GetPokemonName(D_84390010[!gBattleState.unk_00->unk_2C]));
    WriteMessageCharOrString(gBattleMessageBuffers->unk_088, -0x41);
}

void func_84375894(void) {
    s32 temp_v1;

    gBattleState.unk_00->unk_48 = 0x1C;
    if (gCurrentBattleEntity->unk_4D & 0x10) {
        MessageBank_SetPointer_0x14_0x2A(0x19, GetPokemonName(D_84390010[gBattleState.unk_00->unk_2C]));
        WriteMessageCharOrString(gBattleMessageBuffers->unk_088, -0x2A);
        return;
    }

    temp_v1 = gCurrentBattleEntity->unk_28 >> 2;
    if (temp_v1 >= gCurrentBattleEntity->unk_0C) {
        WriteMessageCharOrString(gBattleMessageBuffers->unk_088, -0x29);
        return;
    }

    gBattleState.unk_00->unk_48 = 0x19;
    gCurrentBattleEntity->unk_59 = temp_v1;
    gCurrentBattleEntity->unk_0C -= temp_v1;
    gCurrentBattleEntity->unk_4D |= 0x10;
    MessageBank_SetPointer_0x14_0x2A(0x19, GetPokemonName(D_84390010[gBattleState.unk_00->unk_2C]));
    WriteMessageCharOrString(gBattleMessageBuffers->unk_088, -0x28);
}

void func_843759C4(void) {
    gCurrentBattleEntity->unk_4D |= 0x20;
}

void func_843759DC(void) {
    gCurrentBattleEntity->unk_4D |= 0x40;
}

void func_843759F4(void) {
    unk_BattlePlayerAnimState* sp24 = &D_84390010[gBattleState.unk_00->unk_2C]->unk_654;
    s32 var_t0;
    u8 temp_v0;

    gBattleState.unk_00->unk_48 = 7;
    HandleMoveEffectFlags();

    if ((gSpecialFlag == 0) && !(gDefenderBattleEntity->unk_4C & 0x40)) {
        gBattleUnusedFlag5 = 1;
        do {
            var_t0 = Math_RandomU16Scaled(4);
            if (var_t0 >= 4) {
                var_t0 = 3;
            }
            temp_v0 = gDefenderBattleEntity->unk_1F[var_t0];
        } while (temp_v0 == 0);

        gCurrentBattleEntity->unk_1F[sp24->unk_0C] = temp_v0;
        MessageBank_SetPointer_0x14_0x2A(0x1E, GetMessageString(NULL, 0, gPokemonMessageBank, gDefenderBattleEntity->unk_1F[var_t0] - 1));
        WriteMessageCharOrString(gBattleMessageBuffers->unk_088, -0x40);
        return;
    }

    WriteMessageCharOrString(gBattleMessageBuffers->unk_088, -0x3F);
}

void func_84375B1C(void) {
    HandleMoveEffectFlags();

    if ((gSpecialFlag == 0) && (gDefenderBattleEntity->unk_16[6] != 0x16) && (gDefenderBattleEntity->unk_16[7] != 0x16)) {
        if (!(gDefenderBattleEntity->unk_4D & 0x80)) {
            gDefenderBattleEntity->unk_4D |= 0x80;
            MessageBank_SetPointer_0x14_0x2A(0x19, GetPokemonName(D_84390010[!gBattleState.unk_00->unk_2C]));
            WriteMessageCharOrString(gBattleMessageBuffers->unk_088, -0x3E);
            return;
        }
    }

    gBattleState.unk_00->unk_48 = 8;
    MessageBank_SetPointer_0x14_0x2A(0x19, GetPokemonName(D_84390010[!gBattleState.unk_00->unk_2C]));
    WriteMessageCharOrString(gBattleMessageBuffers->unk_088, -0x3D);
}

void func_84375C24(void) {
    gBattleState.unk_00->unk_48 = 7;
    WriteMessageCharOrString(gBattleMessageBuffers->unk_088, -0x3C);
}

void func_84375C60(void) {
    s32 sp24;
    s32 temp_v1;

    HandleMoveEffectFlags();

    if (gSpecialFlag == 0) {
        gBattleState.unk_00->unk_48 = 0x20;
        if (gDefenderBattleEntity->unk_52 == 0) {
            do {
                sp24 = GetRandomU8() & 3;
            } while (gDefenderBattleEntity->unk_1F[sp24] == 0);
            temp_v1 = (GetRandomU8() & 7) + 1;
            gDefenderBattleEntity->unk_52 = (sp24 * 0x10) + temp_v1;
            gDefenderBattleEntity->unk_57 = gDefenderBattleEntity->unk_1F[sp24];
            MessageBank_SetPointer_0x14_0x2A(0x1E, GetMessageString(NULL, 0, gPokemonMessageBank, gDefenderBattleEntity->unk_57 - 1));
            WriteMessageCharOrString(gBattleMessageBuffers->unk_088, -0x3B);
            return;
        }
    }

    gBattleState.unk_00->unk_48 = 8;
    WriteMessageCharOrString(gBattleMessageBuffers->unk_088, -0x3A);
}

void func_84375D78(void) {
    WriteMessageCharOrString(gBattleMessageBuffers->unk_088, -0x39);
}

void func_84375DA4(void) {
    gBattleState.unk_00->unk_48 = 7;
    if (!(gDefenderBattleEntity->unk_4C & 0x40)) {
        gCurrentBattleEntity->unk_16[6] = gDefenderBattleEntity->unk_16[6];
        gCurrentBattleEntity->unk_16[7] = gDefenderBattleEntity->unk_16[7];
        MessageBank_SetPointer_0x14_0x2A(0x19, GetPokemonName(D_84390010[!gBattleState.unk_00->unk_2C]));
        WriteMessageCharOrString(gBattleMessageBuffers->unk_088, -0x38);
    } else {
        WriteMessageCharOrString(gBattleMessageBuffers->unk_088, -0x37);
    }
}

void func_84375E6C(void) {
    s32 i;
    unk_D_800FCB18* temp_t0 = &D_84390010[0]->unk_654.unk_38;
    unk_D_800FCB18* temp_a3 = &D_84390010[1]->unk_654.unk_38;

    gBattleState.unk_00->unk_48 = 0x1D;

    for (i = 0; i < 8; i++) {
        temp_t0->unk_5C[i] = 7;
        temp_a3->unk_5C[i] = 7;
    }

    temp_t0->unk_2A = temp_t0->unk_38;
    temp_t0->unk_2C = temp_t0->unk_3A;
    temp_t0->unk_2E = temp_t0->unk_3C;
    temp_t0->unk_30 = temp_t0->unk_3E;
    temp_a3->unk_2A = temp_a3->unk_38;
    temp_a3->unk_2C = temp_a3->unk_3A;
    temp_a3->unk_2E = temp_a3->unk_3C;
    temp_a3->unk_30 = temp_a3->unk_3E;

    if ((gDefenderBattleEntity->unk_15 & 0x27) && !(gDefenderBattleEntity->unk_4C & 0x10)) {
        gDefenderBattleEntity->unk_5A = 0xFE;
    }

    gDefenderBattleEntity->unk_15 = 0;
    // clang-format off
    if (D_8438AC60[0] == 1) { gCurrentBattleEntity->unk_15 = 0; }
    // clang-format on

    temp_t0->unk_52 = temp_a3->unk_52 = 0;
    temp_t0->unk_57 = temp_a3->unk_57 = 0;
    temp_t0->unk_4C &= ~0x80;
    temp_t0->unk_4D &= 0x78;
    temp_t0->unk_4E &= 8;
    temp_a3->unk_4C &= ~0x80;
    temp_a3->unk_4D &= 0x78;
    temp_a3->unk_4E &= 8;
    gCurrentBattleEntity->unk_56 = 0;
    gDefenderBattleEntity->unk_56 = 0;

    WriteMessageCharOrString(gBattleMessageBuffers->unk_088, -0x36);
}

void func_8437600C(void) {
    u8 temp_v0;
    unk_BattlePlayerAnimState* temp_a1;
    unk_D_800FCB18* temp_a2;

    temp_a1 = &D_84390010[gBattleState.unk_00->unk_2C]->unk_654;
    temp_a2 = &D_84390010[gBattleState.unk_00->unk_2C]->unk_654.unk_38;

    gBattleState.unk_00->unk_48 = 0x15;
    if (gCurrentBattleEntity->unk_0C != gCurrentBattleEntity->unk_28) {
        if (gCurrentBattleEntity->unk_44.unk_00 == 0x9C) {
            temp_v0 = gCurrentBattleEntity->unk_15;

            gCurrentBattleEntity->unk_15 = 2;
            temp_a2->unk_16[temp_a1->unk_08 + temp_a1->unk_2B * 3] = 2;

            if (temp_v0 != 0) {
                if (D_8438AC60[0] == 1) {
                    gCurrentBattleEntity->unk_4E &= ~1;
                    ScaleStatValue(&gCurrentBattleEntity->unk_2A, gCurrentBattleEntity->unk_38, gCurrentBattleEntity->unk_5C[0]);
                    ScaleStatValue(&gCurrentBattleEntity->unk_2E, gCurrentBattleEntity->unk_3C, gCurrentBattleEntity->unk_5C[2]);
                }
                MessageBank_SetPointer_0x14_0x2A(0x19, GetPokemonName(D_84390010[gBattleState.unk_00->unk_2C]));
                WriteMessageCharOrString(gBattleMessageBuffers->unk_088, -0x35);
            } else {
                MessageBank_SetPointer_0x14_0x2A(0x19, GetPokemonName(D_84390010[gBattleState.unk_00->unk_2C]));
                WriteMessageCharOrString(gBattleMessageBuffers->unk_088, -0x34);
            }
            gCurrentBattleEntity->unk_0C += gCurrentBattleEntity->unk_28;
        } else {
            gCurrentBattleEntity->unk_0C += gCurrentBattleEntity->unk_28 / 2;
        }

        if (gCurrentBattleEntity->unk_28 < gCurrentBattleEntity->unk_0C) {
            gCurrentBattleEntity->unk_0C = gCurrentBattleEntity->unk_28;
        }

        MessageBank_SetPointer_0x14_0x2A(0x19, GetPokemonName(D_84390010[gBattleState.unk_00->unk_2C]));
        WriteMessageCharOrString(gBattleMessageBuffers->unk_148, -0x33);
        return;
    }

    gBattleState.unk_00->unk_48 = 0x1C;
    gSpecialFlag = 1;
    WriteMessageCharOrString(gBattleMessageBuffers->unk_088, -0x32);
}

void func_84376258(void) {
    s32 i;
    unk_BattlePlayerAnimState* sp20;
    unk_BattlePlayerAnimState* sp1C;
    unk_D_800FCB18* ptr;

    sp20 = &D_84390010[gBattleState.unk_00->unk_2C]->unk_654;
    sp1C = &D_84390010[!gBattleState.unk_00->unk_2C]->unk_654;

    if ((D_8438AC60[0] == 1) && ((((gDefenderBattleEntity->unk_4E & 8) == 0) && (gDefenderBattleEntity->unk_0B == 0x84)) ||
                                 (((gDefenderBattleEntity->unk_4E & 8) != 0) && (sp1C->unk_BE == 0x84)))) {
        gBattleState.unk_00->unk_48 = 0x1C;
        MessageBank_SetPointer_0x14_0x2A(0x1B, GetPokemonName(D_84390010[!gBattleState.unk_00->unk_2C]));
        WriteMessageCharOrString(gBattleMessageBuffers->unk_088, -0x2F);
        return;
    }

    ptr = gCurrentBattleEntity;
    if (!(ptr->unk_4C & 0x40) &&
        ((D_8438AC60[0] != 1) || (gDefenderBattleEntity->unk_1F[0] != 0x90) || (gDefenderBattleEntity->unk_1F[1] != 0))) {
        gBattleState.unk_00->unk_48 = 0xF;
        MessageBank_SetPointer_0x14_0x2A(0x1B, GetPokemonName(D_84390010[!gBattleState.unk_00->unk_2C]));
        WriteMessageCharOrString(gBattleMessageBuffers->unk_148, -0x31);
        gCurrentBattleEntity->unk_4E |= 8;

        if (gDefenderBattleEntity->unk_4E & 8) {
            sp20->unk_BE = sp1C->unk_BE;
        } else {
            sp20->unk_BE = gDefenderBattleEntity->unk_0B;
        }

        gCurrentBattleEntity->unk_16[6] = gDefenderBattleEntity->unk_16[6];
        gCurrentBattleEntity->unk_16[7] = gDefenderBattleEntity->unk_16[7];
        gCurrentBattleEntity->unk_1F[0] = gDefenderBattleEntity->unk_1F[0];
        gCurrentBattleEntity->unk_1F[1] = gDefenderBattleEntity->unk_1F[1];
        gCurrentBattleEntity->unk_1F[2] = gDefenderBattleEntity->unk_1F[2];
        gCurrentBattleEntity->unk_1F[3] = gDefenderBattleEntity->unk_1F[3];
        gCurrentBattleEntity->unk_24 = gDefenderBattleEntity->unk_24;
        gCurrentBattleEntity->unk_2A = gDefenderBattleEntity->unk_2A;
        gCurrentBattleEntity->unk_2C = gDefenderBattleEntity->unk_2C;
        gCurrentBattleEntity->unk_2E = gDefenderBattleEntity->unk_2E;
        gCurrentBattleEntity->unk_30 = gDefenderBattleEntity->unk_30;

        for (i = 0; i < 4; i++) {
            if (gDefenderBattleEntity->unk_1F[i] == 0) {
                break;
            }
            gCurrentBattleEntity->unk_32[i] = 5;
        }

        gCurrentBattleEntity->unk_38 = gDefenderBattleEntity->unk_38;
        gCurrentBattleEntity->unk_3A = gDefenderBattleEntity->unk_3A;
        gCurrentBattleEntity->unk_3C = gDefenderBattleEntity->unk_3C;
        gCurrentBattleEntity->unk_3E = gDefenderBattleEntity->unk_3E;

        for (i = 0; i < 8; i++) {
            gCurrentBattleEntity->unk_5C[i] = gDefenderBattleEntity->unk_5C[i];
        }
        return;
    }

    gBattleState.unk_00->unk_48 = 0x1C;
    WriteMessageCharOrString(gBattleMessageBuffers->unk_088, -0x30);
}

void func_843765E8(void) {
    gBattleState.unk_00->unk_48 = 7;
    if (gCurrentBattleEntity->unk_44.unk_01 == 0x40) {
        if (!(gCurrentBattleEntity->unk_4E & 2)) {
            gCurrentBattleEntity->unk_4E |= 2;
            MessageBank_SetPointer_0x14_0x2A(0x19, GetPokemonName(D_84390010[gBattleState.unk_00->unk_2C]));
            WriteMessageCharOrString(gBattleMessageBuffers->unk_088, -0x2E);
        } else {
            WriteMessageCharOrString(gBattleMessageBuffers->unk_088, -0x2D);
        }
    } else if (!(gCurrentBattleEntity->unk_4E & 4)) {
        gCurrentBattleEntity->unk_4E |= 4;
        MessageBank_SetPointer_0x14_0x2A(0x19, GetPokemonName(D_84390010[gBattleState.unk_00->unk_2C]));
        WriteMessageCharOrString(gBattleMessageBuffers->unk_088, -0x2C);
    } else {
        WriteMessageCharOrString(gBattleMessageBuffers->unk_088, -0x2B);
    }
}

void SpAttack_Dispatch(void) {
    unk_D_800FCB18* ptr = &D_84390010[gBattleState.unk_00->unk_2C]->unk_654.unk_38;
    s32 idx = ptr->unk_44.unk_01;

    if (D_8438AE54[idx - 1] != NULL) {
        D_8438AE54[idx - 1]();
    }
}

void SpAttack_Main(void) {
    SpAttack_Dispatch();
}
