#include "fragment62.h"
#include "src/17300.h"
#include "src/1C720.h"
#include "src/373A0.h"
#include "src/3D140.h"
#include "src/485C0.h"
#include "src/4BDC0.h"
#include "src/4F410.h"
#include "src/F420.h"

unk_BattlePlayerEntity* gOpponentPlayer;
unk_BattlePlayerEntity* gCurrentPlayer;
static f32 gBattleUnusedFloat_84390208;
static s32 pad_D_84390210[4];
static s32 gPlayer0ReadyFlag;
static s32 gPlayer1ReadyFlag;
static s32 gBattleUnusedInt_84390228;
s32 gTotalMoveCount;
s32 gCurrentMoveIndex;
s32 gInitialMoveIndex;

u8 gMoveIdSetA[] = {
    0x00, 0x03, 0x02, 0x06, 0x07,
};
u8 gMoveIdSetB[] = {
    0x00,
    0x02,
    0x06,
    0x07,
};
u8 gMoveIdSetC[] = {
    0x02,
    0x06,
    0x07,
};
u8 gMoveIdSetD[] = {
    0x04, 0x05, 0x08, 0x09, 0x0A, 0x0B,
};
u8 gMoveIdSetE[] = {
    0x05,
    0x09,
    0x0A,
    0x0B,
};
u16 gAnimFlagMask_5F92 = 0x5F92;
Vec3f gCameraFarSettings = { 0.0f, 100.0f, 0.0f };
Vec3f gCameraCloseSettings = { 0.0f, 10.0f, 0.0f };

void TriggerSpecialActionIfReady(unk_BattlePlayerEntity* arg0) {
    unk_BattlePlayerAnimState* ptr = &arg0->unk_654;

    if ((arg0->unk_000.unk_01A == 0x32) && (ptr->unk_34 & 0x4000)) {
        unk_BattleAnimDataEntry* tmp = &gAnimDataByPlayer[IsPrimaryEntity(arg0)]->unk_000[0x5A];

        GraphNode_TriggerAction(&arg0->unk_000, tmp->unk_00);
        arg0->unk_000.unk_000.unk_02 &= ~0x20;
    }
}

void Battle_ResetSubstate(void) {
    gBattleState.unk_00->unk_24 = 0;
}

s32 HandlePlayerActionFlag800(unk_BattlePlayerEntity* arg0) {
    unk_BattlePlayerAnimState* ptr = &arg0->unk_654;
    UNUSED s32 pad;
    s32 sp1C = 0;

    if (!(ptr->unk_34 & 0x800)) {
        return 0;
    }

    if (gBattleState.unk_00->unk_48 == 0x19) {
        return 0;
    }

    if ((ptr->unk_34 & 0x800) && (gBattleState.unk_00->unk_48 == 0x1C)) {
        return 0;
    }

    switch (gBattleState.unk_00->unk_24) {
        case 0:
            AnimChannel_SetTransformData(arg0);
            sp1C = 1;
            gBattleState.unk_00->unk_24++;
            break;

        case 1:
            sp1C = 1;
            if (arg0->unk_720->unk_00 & 0x10) {
                arg0->unk_720->unk_00 &= ~0x90;
                Pokemon_RestoreVisuals(arg0);
                TriggerSpecialActionIfReady(arg0);
                gBattleState.unk_00->unk_24++;
            }
            break;

        case 2:
            Battle_ResetSubstate();
            break;
    }
    return sp1C;
}

s32 HandlePlayerActionFlag800Alt(unk_BattlePlayerEntity* arg0) {
    UNUSED s32 pad[2];
    s32 sp1C = 0;

    if (!(arg0->unk_654.unk_34 & 0x800)) {
        return 0;
    }

    switch (gBattleState.unk_00->unk_24) {
        case 0:
            AnimChannel_SetFlags28(arg0);
            sp1C = 1;
            gBattleState.unk_00->unk_24++;
            break;

        case 1:
            sp1C = 1;
            if (arg0->unk_720->unk_00 & 0x10) {
                arg0->unk_720->unk_00 &= ~0x90;
                Pokemon_ResetAnimations(arg0);
                gBattleState.unk_00->unk_24++;
            }
            break;

        case 2:
            Battle_ResetSubstate();
            break;
    }
    return sp1C;
}

s32 HandlePlayerActionFlag1000(unk_BattlePlayerEntity* arg0) {
    UNUSED s32 pad[2];
    Vec3f sp34;
    s32 var_s0 = 0;

    if (!(arg0->unk_654.unk_34 & 0x1000)) {
        return 0;
    }

    switch (gBattleState.unk_00->unk_24) {
        case 0:
            AnimChannel_SetTransformData(arg0);
            var_s0 = 1;
            gBattleState.unk_00->unk_24++;
            break;

        case 1:
            var_s0 = 1;
            if (arg0->unk_720->unk_00 & 0x10) {
                arg0->unk_720->unk_00 &= ~0x90;
                Pokemon_RestoreVisuals(arg0);
                ClearEntityAnimFlags(arg0, 0x1800);
                var_s0 = 0;
                Battle_ResetSubstate();
                gBattleState.unk_00->unk_24++;
            }
            break;

        case 2:
            Battle_ResetSubstate();
            GetEntityCenterPosition(arg0, &sp34);
            Vector_Copy(&gBattleState.unk_00->unk_DC->unk_60.at, &sp34);
            break;
    }
    return var_s0;
}

s32 ProcessActionWhenState44Is2(unk_BattlePlayerEntity* arg0) {
    UNUSED s32 pad[2];
    s32 sp1C = 0;

    if (gBattleState.unk_00->unk_44 != 2) {
        return 0;
    }

    if (!(arg0->unk_654.unk_34 & 0x800)) {
        return 0;
    }

    if ((gBattleState.unk_00->unk_48 == 0x19) || (gBattleState.unk_00->unk_48 == 0x1C)) {
        return 0;
    }

    switch (gBattleState.unk_00->unk_24) {
        case 0:
            AnimChannel_SetTransformData(arg0);
            sp1C = 1;
            gBattleState.unk_00->unk_24 += 1;
            break;

        case 1:
            sp1C = 1;
            if (arg0->unk_720->unk_00 & 0x10) {
                arg0->unk_720->unk_00 &= ~0x90;
                Pokemon_RestoreVisuals(arg0);
                TriggerSpecialActionIfReady(arg0);
                gBattleState.unk_00->unk_24 += 1;
            }
            break;

        case 2:
            Battle_ResetSubstate();
            break;
    }
    return sp1C;
}

s32 ProcessDualPlayerActionState1(void) {
    UNUSED s32 pad[2];
    s32 sp1C = 0;
    unk_BattlePlayerAnimState* temp_a1 = &sActivePokemon[0]->unk_654;
    unk_BattlePlayerAnimState* temp_a2 = &sActivePokemon[1]->unk_654;

    if (gBattleState.unk_00->unk_44 != 1) {
        return 0;
    }

    if (!(temp_a1->unk_34 & 0x800) && !(temp_a2->unk_34 & 0x800)) {
        return 0;
    }

    switch (gBattleState.unk_00->unk_24) {
        case 0:
            if (temp_a1->unk_34 & 0x800) {
                AnimChannel_SetFlags28(sActivePokemon[0]);
            }
            sp1C = 1;
            gBattleState.unk_00->unk_24 = gBattleState.unk_00->unk_24 + 1;
            break;

        case 1:
            sp1C = 1;
            if (temp_a1->unk_34 & 0x800) {
                if (sActivePokemon[0]->unk_720->unk_00 & 0x10) {
                    sActivePokemon[0]->unk_720->unk_00 &= ~0x90;
                    Pokemon_ResetAnimations(sActivePokemon[0]);
                    gBattleState.unk_00->unk_24 += 1;
                }
            } else {
                gBattleState.unk_00->unk_24 = gBattleState.unk_00->unk_24 + 1;
            }
            break;

        case 2:
            if (temp_a2->unk_34 & 0x800) {
                AnimChannel_SetFlags28(sActivePokemon[1]);
            }
            sp1C = 1;
            gBattleState.unk_00->unk_24 = gBattleState.unk_00->unk_24 + 1;
            break;

        case 3:
            sp1C = 1;
            if (temp_a2->unk_34 & 0x800) {
                if (sActivePokemon[1]->unk_720->unk_00 & 0x10) {
                    sActivePokemon[1]->unk_720->unk_00 &= ~0x90;
                    Pokemon_ResetAnimations(sActivePokemon[1]);
                    gBattleState.unk_00->unk_24 += 1;
                }
            } else {
                gBattleState.unk_00->unk_24 = gBattleState.unk_00->unk_24 + 1;
            }
            break;

        case 4:
            Battle_ResetSubstate();
            break;
    }

    return sp1C;
}

void ClearAnimFlag20IfCondition(void) {
    PokemonAudioInfo* temp_v0 = &sActivePokemon[0]->unk_654.unk_38;
    PokemonAudioInfo* temp_v1 = &sActivePokemon[1]->unk_654.unk_38;

    if (temp_v0->unk_4F == 0) {
        temp_v0->unk_4C &= ~0x20;
    }

    if (temp_v1->unk_4F == 0) {
        temp_v1->unk_4C &= ~0x20;
    }
}

void func_8431FCC4(void) {
}

s32 UpdatePokemonHP(unk_BattlePlayerEntity* arg0) {
    PokemonAudioInfo* temp_s1 = &arg0->unk_654.unk_38;
    PokemonData* temp_s2 = &arg0->unk_724->unk_01C[arg0->unk_654.unk_08];
    f32 temp_fs0;
    UNUSED s16 pad;
    s16 sp30;

    if (gBattleUpdateHPFlag != 0) {
        return 1;
    }

    if (temp_s2->unk_02 == temp_s1->unk_0C) {
        return 1;
    }

    temp_fs0 = temp_s1->unk_28 / 90.0f;
    sp30 = IsPrimaryEntity(arg0);
    gPlayerScaleFactors[sp30] = Math_ApproachF32(gPlayerScaleFactors[IsPrimaryEntity(arg0)], temp_s1->unk_0C, temp_fs0, temp_fs0);
    temp_s2->unk_02 = gPlayerScaleFactors[IsPrimaryEntity(arg0)];
    if (temp_s2->unk_02 == temp_s1->unk_0C) {
        temp_fs0 = gPlayerScaleFactors[IsPrimaryEntity(arg0)] - temp_s2->unk_02;
        gPlayerScaleFactors[IsPrimaryEntity(arg0)] -= temp_fs0;
        if (arg0->unk_000.unk_01A == 0x98) {
            return 1;
        }
        return 1;
    }
    return 0;
}

void Battle_ClearSubstateFlag(void) {
    gBattleState.unk_00->unk_3C = 0;
}

void Battle_SetSubstateFlag(void) {
    gBattleState.unk_00->unk_3C = 1;
}

void Battle_SetPhase(UNUSED CameraStruct* arg0, s32 arg1) {
    gBattleState.unk_00->unk_38 = arg1;
    gBattleState.unk_00->unk_20 = 0;
}

void Battle_StoreCameraFOV(CameraStruct* arg0) {
    gBattleState.unk_00->unk_60 = arg0->unk_24.fovy;
}

void Battle_SetCameraFOV30(CameraStruct* arg0) {
    arg0->unk_24.fovy = 30.0f;
    gBattleState.unk_00->unk_60 = 30.0f;
}

s32 GetAnimDataField0D(unk_BattlePlayerEntity* arg0) {
    unk_BattleAnimDataEntry* ptr = &gAnimDataByPlayer[IsPrimaryEntity(arg0)]->unk_000[arg0->unk_654.unk_38.unk_5A - 1];

    return ptr->unk_0D;
}

s32 GetMappedAnimDataField0D(unk_BattlePlayerEntity* arg0) {
    UNUSED s32 pad;
    s32 sp18 = gAnimLookupTable[arg0->unk_654.unk_38.unk_5A - 1];
    unk_BattleAnimDataEntry* ptr = &gAnimDataByPlayer[IsPrimaryEntity(arg0)]->unk_000[sp18];

    return ptr->unk_0D;
}

s32 GetAnimDataField0E(unk_BattlePlayerEntity* arg0) {
    unk_BattleAnimDataEntry* ptr = &gAnimDataByPlayer[IsPrimaryEntity(arg0)]->unk_000[arg0->unk_654.unk_38.unk_5A - 1];

    return ptr->unk_0E;
}

s32 GetMappedAnimDataField0E(unk_BattlePlayerEntity* arg0) {
    UNUSED s32 pad;
    s32 sp18 = gAnimLookupTable[arg0->unk_654.unk_38.unk_5A - 1];
    unk_BattleAnimDataEntry* ptr = &gAnimDataByPlayer[IsPrimaryEntity(arg0)]->unk_000[sp18];

    return ptr->unk_0E;
}

s32 GetAnimDataField0FOrDefault(unk_BattlePlayerEntity* arg0) {
    unk_BattleAnimDataEntry* ptr = &gAnimDataByPlayer[IsPrimaryEntity(arg0)]->unk_000[arg0->unk_654.unk_38.unk_5A - 1];

    if (ptr->unk_0F == 0) {
        return 0xF;
    }
    return ptr->unk_0F;
}

void DetermineTurnOrder(void) {
    s32 sp2C;
    unk_BattlePlayerAnimState* temp_s0;
    unk_BattlePlayerAnimState* temp_s1;
    PokemonAudioInfo* ptr;

    temp_s0 = &sActivePokemon[0]->unk_654;
    temp_s1 = &sActivePokemon[1]->unk_654;
    Battle_SetTurnTimer(1, 1);

    sp2C = gBattleState.unk_00->unk_2C;
    gBattleState.unk_00->unk_2C = CompareMovePriority(sActivePokemon[0], sActivePokemon[1]);

    ptr = &sActivePokemon[gBattleState.unk_00->unk_2C]->unk_654.unk_38;
    if ((ptr->unk_5A & 0xF0) == 0xF0) {
        gBattleState.unk_00->unk_2C = !gBattleState.unk_00->unk_2C;
    }

    if (sActivePokemon[0]->unk_724->unk_000 & 2) {
        if (gBattleState.unk_00->unk_2C == 0) {
            BattleAI_RecordUsedMove(temp_s0->unk_08, temp_s1->unk_08, 0);
        } else {
            BattleAI_RecordUsedMove(temp_s0->unk_08, temp_s1->unk_08, 1);
        }
    } else if (sActivePokemon[1]->unk_724->unk_000 & 2) {
        if (gBattleState.unk_00->unk_2C == 1) {
            BattleAI_RecordUsedMove(temp_s1->unk_08, temp_s0->unk_08, 0);
        } else {
            BattleAI_RecordUsedMove(temp_s1->unk_08, temp_s0->unk_08, 1);
        }
    }

    gBattleState.unk_00->unk_2A = gBattleState.unk_00->unk_2C;
    gBattleState.unk_00->unk_38 = 0;
    temp_s0->unk_30 = 0;
    temp_s1->unk_30 = 0;
    gBattleState.unk_00->unk_44 = 2;
    BeginBattleMainLoop();
    gBattleState.unk_00->unk_2C = sp2C;
}

void DetermineTurnOrderPriority(void) {
    s32 sp2C;
    unk_BattlePlayerAnimState* sp28;
    unk_BattlePlayerAnimState* sp24;

    sp28 = &sActivePokemon[0]->unk_654;
    sp24 = &sActivePokemon[1]->unk_654;
    Battle_SetTurnTimer(1, 1);

    sp2C = gBattleState.unk_00->unk_2C;

    if ((sp28->unk_2D == 0xF) || (sp28->unk_2D == 0x10)) {
        if (sActivePokemon[0]->unk_724->unk_000 & 2) {
            BattleAI_RecordUsedMove(sp28->unk_08, sp24->unk_08, 2);
        }
        gBattleState.unk_00->unk_2C = 0;
        gBattleState.unk_00->unk_2A = 0;
        gBattleState.unk_00->unk_38 = 0;
        gBattleState.unk_00->unk_44 = 2;
        BeginBattleForEntity(sActivePokemon[0]);
        gBattleState.unk_00->unk_2C = sp2C;
    } else {
        if (sActivePokemon[0]->unk_724->unk_000 & 2) {
            BattleAI_RecordUsedMove(sp24->unk_08, sp28->unk_08, 2);
        }
        gBattleState.unk_00->unk_2C = 1;
        gBattleState.unk_00->unk_2A = 1;
        gBattleState.unk_00->unk_38 = 0;
        gBattleState.unk_00->unk_44 = 2;
        BeginBattleForEntity(sActivePokemon[1]);
        gBattleState.unk_00->unk_2C = sp2C;
    }
}

s32 HandlePokemonFaintOrSwitch(void) {
    unk_BattlePlayerAnimState* sp24 = &sActivePokemon[gBattleState.unk_00->unk_2C]->unk_654;
    unk_BattlePlayerAnimState* temp_a3 = &sActivePokemon[gBattleState.unk_00->unk_2C]->unk_654;
    unk_BattlePlayerAnimState* sp20 = &sActivePokemon[!gBattleState.unk_00->unk_2C]->unk_654;

    if ((sActivePokemon[gBattleState.unk_00->unk_2C]->unk_654.unk_2D == 0xF) || (sp24->unk_2D == 0x10)) {
        if (sActivePokemon[gBattleState.unk_00->unk_2C]->unk_724->unk_000 & 2) {
            BattleAI_RecordUsedMove(temp_a3->unk_08, sp20->unk_08, 2);
        }
        ClearEntityAnimFlags(sActivePokemon[gBattleState.unk_00->unk_2C], 0x1800);
        gBattleState.unk_00->unk_20 = 0;
        gBattleState.unk_00->unk_14 = 0;
        if (sp24->unk_2D == 0x10) {
            gBattleState.unk_00->unk_38 = 0x12;
        } else {
            GetEntityCenterPosition(sActivePokemon[gBattleState.unk_00->unk_2C], &gCameraPreset.unk_00);
            Battle_PlayCameraTransition(&gCameraPosB, gBattleState.unk_00->unk_DC, sActivePokemon[gBattleState.unk_00->unk_2C]);
            gBattleState.unk_00->unk_38 = 0xB;
        }
        return 1;
    }

    return 0;
}

void Battle_UpdateAfterTurn(void) {
    unk_BattlePlayerAnimState* sp1C = &sActivePokemon[0]->unk_654;
    unk_BattlePlayerAnimState* sp18 = &sActivePokemon[1]->unk_654;

    if ((Battle_TickCountdownTimer() == 0) && (gBattleResultPhase != 1)) {
        AudioFrameUpdate(1);
    }

    ClearAnimFlag20IfCondition();
    sp1C->unk_10 = 0;
    sp18->unk_10 = 0;

    if ((sp1C->unk_2D == 0x10) || (sp18->unk_2D == 0x10) || (gBattleState.unk_00->unk_2E == 2)) {
        Battle_SetTurnTimer(1, 0);
    } else {
        Battle_SetTurnTimer(1, 1);
    }

    gBattleState.unk_00->unk_44 = 1;
    gBattleState.unk_00->unk_20 += 1;
}

s32 Battle_SetPhaseAndReset(s32 arg0) {
    Battle_ClearSubstateFlag();
    Battle_FinishTurn();
    gBattleState.unk_00->unk_48 = 0;
    gBattleState.unk_00->unk_4C = 0;
    gBattleState.unk_00->unk_20 = 0;
    gBattleState.unk_00->unk_14 = 0;
    gBattleState.unk_00->unk_38 = arg0;
    return 1;
}

s32 Battle_SetPhaseNoReset(s32 arg0) {
    Battle_ClearSubstateFlag();
    Battle_FinishTurn();
    gBattleState.unk_00->unk_4C = 0;
    gBattleState.unk_00->unk_20 = 0;
    gBattleState.unk_00->unk_14 = 0;
    gBattleState.unk_00->unk_38 = arg0;
    return 1;
}

s32 Battle_SetPhaseSimple(s32 arg0) {
    Battle_ClearSubstateFlag();
    Battle_FinishTurn();
    gBattleState.unk_00->unk_4C = 0;
    gBattleState.unk_00->unk_20 = 0;
    gBattleState.unk_00->unk_14 = 0;
    gBattleState.unk_00->unk_38 = arg0;
    return 1;
}

void Battle_TogglePlayerAndSetPhase5(CameraStruct* arg0) {
    gBattleState.unk_00->unk_2C = !gBattleState.unk_00->unk_2C;
    Battle_SetPhase(arg0, 5);
}

void Battle_TogglePlayerAndPrepare(u8 arg0) {
    unk_BattlePlayerAnimState* temp_a3;

    gBattleState.unk_00->unk_2C = !gBattleState.unk_00->unk_2C;
    temp_a3 = &sActivePokemon[gBattleState.unk_00->unk_2C]->unk_654;

    if ((temp_a3->unk_2D == 0xF) || (temp_a3->unk_2D == 0x10)) {
        BeginBattleForEntity(sActivePokemon[gBattleState.unk_00->unk_2C]);
    } else {
        BeginBattleMainLoop();
    }

    gBattleState.unk_00->unk_34 = 1;
    gBattleState.unk_00->unk_A0.z = 0.0f;
    Battle_SetPhase(gBattleState.unk_00->unk_DC, 0x24);
    gBattleState.unk_00->unk_78 = arg0;
}

void Battle_CheckAndAdvancePhase(void) {
    if (HandlePlayerActionFlag800(sActivePokemon[gBattleState.unk_00->unk_2C]) == 0) {
        gBattleState.unk_00->unk_38 = gBattleState.unk_00->unk_78;
    }
}

void Battle_HandleSubstateTransition(void) {
    PokemonAudioInfo* sp24;
    PokemonAudioInfo* sp20;
    unk_BattlePlayerAnimState* sp1C;

    if (gBattleState.unk_00->unk_34 == 0) {
        Anim_ClearEntityVisualFlags(sActivePokemon[gBattleState.unk_00->unk_2C]);
        ResetSoundDurations();
        Battle_ResetSubstate();

        sp24 = &sActivePokemon[gBattleState.unk_00->unk_2C]->unk_654.unk_38;
        sp20 = &sActivePokemon[!gBattleState.unk_00->unk_2C]->unk_654.unk_38;
        sp1C = &sActivePokemon[!gBattleState.unk_00->unk_2C]->unk_654;

        if ((((sp24->unk_5A & 0xF0) == 0xF0) || ((sp20->unk_5A & 0xF0) == 0xF0)) && (sp1C->unk_2D != 0xF) &&
            (sp1C->unk_2D != 0x10)) {
            gBattleState.unk_00->unk_20 = 0;
            gBattleState.unk_00->unk_14 = 0;
            gBattleState.unk_00->unk_38 = 4;

            if ((sp24->unk_5A & 0xF0) == 0xF0) {
                sp24->unk_5A = 0xA5;
            }

            if ((sp20->unk_5A & 0xF0) == 0xF0) {
                sp20->unk_5A = 0xA5;
            }
        } else {
            Battle_TogglePlayerAndPrepare(3);
            gBattleState.unk_00->unk_20 = 0;
            gBattleState.unk_00->unk_14 = 0;
        }
    } else {
        sp24 = &sActivePokemon[gBattleState.unk_00->unk_2C]->unk_654.unk_38;
        sp20 = &sActivePokemon[!gBattleState.unk_00->unk_2C]->unk_654.unk_38;

        Anim_ClearEntityVisualFlags(sActivePokemon[gBattleState.unk_00->unk_2C]);
        ResetSoundDurations();
        Battle_ResetSubstate();

        gBattleState.unk_00->unk_20 = 0;
        gBattleState.unk_00->unk_14 = 0;
        gBattleState.unk_00->unk_38 = 4;

        if ((sp24->unk_5A & 0xF0) == 0xF0) {
            sp24->unk_5A = 0xA5;
        }

        if ((sp20->unk_5A & 0xF0) == 0xF0) {
            sp20->unk_5A = 0xA5;
        }
    }
}

s32 Battle_OpponentSpecialCondition(void) {
    PokemonAudioInfo* temp_v0 = &gOpponentPlayer->unk_654.unk_38;

    if (((temp_v0->unk_4D & 0x80) || (temp_v0->unk_15 & 0x18)) && ((temp_v0->unk_5A & 0xF0) == 0xF0)) {
        Anim_ClearEntityVisualFlags(sActivePokemon[gBattleState.unk_00->unk_2C]);
        ResetSoundDurations();
        Battle_ResetSubstate();
        Battle_TogglePlayerAndPrepare(3);
        gBattleState.unk_00->unk_20 = 0;
        gBattleState.unk_00->unk_48 = 0;
        gBattleState.unk_00->unk_14 = 0;
        return 1;
    }
    return 0;
}

void Battle_HandlePhaseTransition(void) {
    if ((gBattleState.unk_00->unk_34 == 0) && ((gOpponentPlayer->unk_654.unk_38.unk_5A & 0xF0) != 0xF0)) {
        Anim_ClearEntityVisualFlags(sActivePokemon[gBattleState.unk_00->unk_2C]);
        ResetSoundDurations();
        Battle_ResetSubstate();
        Battle_TogglePlayerAndPrepare(3);
        gBattleState.unk_00->unk_20 = 0;
        gBattleState.unk_00->unk_14 = 0;
    } else if (Battle_OpponentSpecialCondition() == 0) {
        Anim_ClearEntityVisualFlags(sActivePokemon[gBattleState.unk_00->unk_2C]);
        ResetSoundDurations();
        Battle_ResetSubstate();
        gBattleState.unk_00->unk_20 = 0;
        gBattleState.unk_00->unk_14 = 0;
        gBattleState.unk_00->unk_38 = 4;
    }
}

void Battle_ProcessReadyState(CameraStruct* arg0) {
    if ((gPlayer0ReadyFlag == 1) && (gPlayer1ReadyFlag == 1)) {
        if (GetCurrentHP(sActivePokemon[gBattleState.unk_00->unk_2C]) == 0) {
            Battle_TogglePlayerAndSetPhase5(arg0);
        } else if (GetCurrentHP(sActivePokemon[!gBattleState.unk_00->unk_2C]) == 0) {
            Battle_SetPhase(arg0, 5);
        } else {
            Battle_HandlePhaseTransition();
        }
    }
}

void Battle_UpdateHPAndProceed(CameraStruct* arg0) {
    PokemonAudioInfo* sp1C = &sActivePokemon[gBattleState.unk_00->unk_2C]->unk_654.unk_38;

    gPlayer0ReadyFlag = UpdatePokemonHP(sActivePokemon[0]);
    gPlayer1ReadyFlag = UpdatePokemonHP(sActivePokemon[1]);
    Battle_ClearSubstateFlag();
    Battle_FinishTurn();

    if (GetCurrentHP(sActivePokemon[gBattleState.unk_00->unk_2C]) == 0) {
        Battle_TogglePlayerAndSetPhase5(arg0);
    } else if (GetCurrentHP(sActivePokemon[!gBattleState.unk_00->unk_2C]) == 0) {
        Battle_ProcessReadyState(arg0);
    } else if (gBattleState.unk_00->unk_4C == 0xA) {
        Battle_SetPhaseSimple(0xA);
    } else if (gBattleState.unk_00->unk_48 == 9) {
        Battle_SetPhaseAndReset(9);
    } else if ((sp1C->unk_15 & 0x18) || (sp1C->unk_4D & 0x80)) {
        Battle_SetPhaseAndReset(6);
    } else {
        Battle_ProcessReadyState(arg0);
    }
}

void Battle_MainLoopStep(CameraStruct* arg0) {
    if ((gPlayer0ReadyFlag == 1) && (gPlayer1ReadyFlag == 1)) {
        Dialog_Clear();
        Battle_UpdateHPAndProceed(arg0);
    }
}

s32 Battle_HandleSpecificPhases(void) {
    switch (gBattleState.unk_00->unk_48) {
        case 7:
        case 38:
        case 39:
            ExecuteAnimStateHandlers(gCurrentPlayer, 3);
            return Battle_SetPhaseNoReset(0x25);

        case 30:
            ExecuteAnimStateHandlers(gCurrentPlayer, 3);
            return Battle_SetPhaseNoReset(0x25);

        case 28:
            return Battle_SetPhaseNoReset(0x25);

        case 21:
            ExecuteAnimStateHandlers(gCurrentPlayer, 3);
            return Battle_SetPhaseNoReset(0x25);

        case 15:
            return Battle_SetPhaseNoReset(0x25);

        case 25:
            return Battle_SetPhaseNoReset(0x25);

        case 27:
            return Battle_SetPhaseNoReset(0x25);

        case 29:
            ExecuteAnimStateHandlers(gCurrentPlayer, 3);
            return Battle_SetPhaseNoReset(0x25);

        case 12:
            ExecuteAnimStateHandlers(gCurrentPlayer, 8);
            return Battle_SetPhaseNoReset(0x25);

        case 13:
            ExecuteAnimStateHandlers(gCurrentPlayer, 8);
            return Battle_SetPhaseNoReset(0x25);

        case 14:
            ExecuteAnimStateHandlers(gCurrentPlayer, 8);
            return Battle_SetPhaseNoReset(0x25);

        case 17:
            ExecuteAnimStateHandlers(gCurrentPlayer, 9);
            return Battle_SetPhaseNoReset(0x25);

        case 31:
            return Battle_SetPhaseNoReset(0x25);
    }
    return 0;
}

s32 Battle_HandlePhase10or14or8(void) {
    s32 tmp = gBattleState.unk_00->unk_48;

    if (tmp != 0x10) {
        if (gBattleState.unk_00->unk_48 == 0x14) {
            return Battle_SetPhaseAndReset(0x14);
        }
    } else {
        return Battle_SetPhaseAndReset(0x10);
    }

    if ((gSpecialFlag != 0) || (gBattleState.unk_00->unk_48 == 8)) {
        return Battle_SetPhaseAndReset(8);
    }
    return 0;
}

s32 Battle_CheckOpponentSpecialAction(void) {
    s32 idx = gBattleState.unk_00->unk_2C;
    PokemonAudioInfo* temp_v1_2 = &sActivePokemon[idx]->unk_654.unk_38;

    if (((temp_v1_2->unk_4D & 0x80) || (temp_v1_2->unk_15 & 0x18)) && ((temp_v1_2->unk_5A & 0xF0) == 0xF0)) {
        return Battle_SetPhaseAndReset(0x23);
    }
    return 0;
}

void Battle_SetCurrentAndOpponent(void) {
    s32 idx;

    gCurrentPlayer = sActivePokemon[gBattleState.unk_00->unk_2C];
    idx = gBattleState.unk_00->unk_2C == 0;
    gOpponentPlayer = sActivePokemon[idx];
}

void Battle_InitializeCameraAndAudio(CameraStruct* arg0) {
    AudioFrameUpdate(0);
    Camera_SetClippingPlanes(arg0, 20.0f, 12800.0f);
    Battle_ResetSubstate();
    gBattleState.unk_00->unk_34 = 0;
    Battle_ClearSubstateFlag();
    gBattleState.unk_00->unk_14 = 0;
    Battle_ApplyAnimEffect(sActivePokemon[0]);
    Battle_ApplyAnimEffect(sActivePokemon[1]);
    gBattleState.unk_00->unk_20++;
}

void Battle_HandleSpecialAnimation(CameraStruct* arg0) {
    unk_BattlePlayerAnimState* temp_t2 = &sActivePokemon[!gBattleState.unk_00->unk_2C]->unk_654;
    unk_BattlePlayerAnimState* temp_t1 = &sActivePokemon[gBattleState.unk_00->unk_2C]->unk_654;
    s16 sp2E = sActivePokemon[gBattleState.unk_00->unk_2C]->unk_000.unk_01A;
    unk_BattleAnimDataEntry* sp28 = &gAnimDataByPlayer[gBattleState.unk_00->unk_2C]->unk_A50;
    unk_BattlePlayerEntity* sp24 = sActivePokemon[gBattleState.unk_00->unk_2C];

    if (((temp_t2->unk_2D == 0x13) && (temp_t1->unk_2D == 0x13)) ||
        ((temp_t2->unk_2D == 0x10) && (temp_t1->unk_2D == 0x13)) ||
        ((temp_t1->unk_2D == 0x10) && (temp_t2->unk_2D == 0x13))) {
        Dialog_SetMode(0xE);
        Vec3f_Set(&arg0->unk_60.at, 0.0f, 75.0f, 0.0f);
        Vec3f_Set(&arg0->unk_60.eye, 0.0f, 80.0f, 400.0f);
        HandleStadiumModeAudio();
        gBattleState.unk_00->unk_20 = 8;
        return;
    }

    if (temp_t1->unk_34 & 0x4008) {
        sp24->unk_000.unk_01D = 0xFF;
        RunParticleEffectScript(4, sp24);
        sp24->unk_000.unk_024.y = gPokemonModelDimensions[gBattleState.unk_00->unk_2C].unk_08;
        sp24->unk_000.unk_000.unk_02 &= ~0x2;
        sp24->unk_000.unk_000.unk_02 |= 0x20;
        sp24->unk_000.unk_000.unk_01 |= 1;
        ClearEntityAnimFlags(sp24, 0x4608);
    }

    if (sActivePokemon[gBattleState.unk_00->unk_2C]->unk_4B4 == 0xA) {
        ApplyAnimEffectToOpponent(sActivePokemon[gBattleState.unk_00->unk_2C], 0, 0);
    }

    if (sActivePokemon[gBattleState.unk_00->unk_2C]->unk_4B4 == 0xD) {
        ApplyAnimEffectToOpponent(sActivePokemon[gBattleState.unk_00->unk_2C], 0, 0);
    }

    if (sActivePokemon[gBattleState.unk_00->unk_2C]->unk_4B4 == 0x10) {
        ApplyAnimEffectToOpponent(sActivePokemon[gBattleState.unk_00->unk_2C], 0, 0);
    }

    sActivePokemon[gBattleState.unk_00->unk_2C]->unk_000.unk_01E.x = 0;
    if ((sp2E == 0x32) || (sp2E == 0x33)) {
        sActivePokemon[gBattleState.unk_00->unk_2C]->unk_000.unk_000.unk_02 |= 0x20;
        sActivePokemon[gBattleState.unk_00->unk_2C]->unk_000.unk_000.unk_01 |= 1;
        GraphNode_TriggerAction(&sActivePokemon[gBattleState.unk_00->unk_2C]->unk_000, sp28->unk_00);
    }

    Battle_ApplyAnimEffect(sActivePokemon[gBattleState.unk_00->unk_2C]);
    Vec3f_Set(&sActivePokemon[gBattleState.unk_00->unk_2C]->unk_000.unk_030, 1.0f, 1.0f, 1.0f);
    sActivePokemon[gBattleState.unk_00->unk_2C]->unk_000.unk_024.y = GetModelBaseY(sActivePokemon[gBattleState.unk_00->unk_2C]);
    GetEntityCenterPosition(sActivePokemon[gBattleState.unk_00->unk_2C], &gCameraPreset.unk_00);
    Battle_PlayCameraTransition(&gBattleCameraPresetE, arg0, sActivePokemon[gBattleState.unk_00->unk_2C]);
    Battle_ApplyCameraSettings(arg0, sActivePokemon[gBattleState.unk_00->unk_2C], 1);
    HandleStadiumModeAudio();
    gBattleState.unk_00->unk_20 = 6;
}

s32 Battle_ResetMoveStateAndStartAnimation(unk_BattlePlayerEntity* arg0) {
    UNUSED s32 pad;
    unk_BattlePlayerAnimState* sp28 = &arg0->unk_654;

    gBattleState.unk_00->unk_54 = 0;
    ResetMoveStateAndStartAnimation(arg0);

    if (sp28->unk_34 & 0x200) {
        ClearEntityAnimFlags(arg0, 0x60C);
        return 1;
    }

    if (sp28->unk_34 & 0x4008) {
        arg0->unk_000.unk_01D = 0xFF;
        RunParticleEffectScript(4, arg0);
        arg0->unk_000.unk_024.y = gPokemonModelDimensions[IsPrimaryEntity(arg0)].unk_08;
        arg0->unk_000.unk_000.unk_02 &= ~0x2;
        arg0->unk_000.unk_000.unk_02 |= 0x20;
        arg0->unk_000.unk_000.unk_01 |= 1;
        ClearEntityAnimFlags(arg0, 0x4608);
    }

    ProcessStatusEffectEnd(arg0);
    sp28->unk_2E = 0xFF;
    GraphNode_SetColorRGBA(&arg0->unk_000, 0xFF, 0xFF, 0xFF, sp28->unk_2E);
    UpdateEntityStateByMode(arg0);
    arg0->unk_000.unk_01E.x = 0;
    return 0;
}

void Battle_HandleOpponentDefeat(CameraStruct* arg0) {
    if (HandlePlayerActionFlag800(sActivePokemon[!gBattleState.unk_00->unk_2C]) == 0) {
        ClearEntityAnimFlags(sActivePokemon[!gBattleState.unk_00->unk_2C], 0x1800);
        ResetSoundDurations();
        Battle_SetAnimChannelFlag(2);
        Battle_FinishTurn();
        RemovePlayer(GetPlayerDefeatMessageId(sActivePokemon[!gBattleState.unk_00->unk_2C]));

        if (Battle_ResetMoveStateAndStartAnimation(sActivePokemon[!gBattleState.unk_00->unk_2C]) != 0) {
            ExecuteAnimStateHandlers(sActivePokemon[!gBattleState.unk_00->unk_2C], 0x11);
            Battle_ResetCameraState();
            gBattleState.unk_00->unk_20 = 0xA;
        } else {
            ExecuteAnimStateHandlers(sActivePokemon[!gBattleState.unk_00->unk_2C], 0);
            Battle_ResetCameraState();
            gBattleState.unk_00->unk_20++;
        }

        Battle_QueueOpponentMove(sActivePokemon[!gBattleState.unk_00->unk_2C], arg0, 3);

        if (Pokemon_IsSpecialSpecies(sActivePokemon[!gBattleState.unk_00->unk_2C]) != 0) {
            Audio_PlaySequence(0xC8, 1);
        } else {
            Audio_PlaySequence(sActivePokemon[!gBattleState.unk_00->unk_2C]->unk_000.unk_01A, 1);
        }
    }
}

void Battle_HandleOpponentAnimation(CameraStruct* arg0) {
    UNUSED s32 pad[2];
    unk_BattlePlayerAnimState* sp24 = &sActivePokemon[!gBattleState.unk_00->unk_2C]->unk_654;
    unk_BattleAnimDataEntry* sp20 = &gAnimDataByPlayer[!gBattleState.unk_00->unk_2C]->unk_A70;

    if (AnimChannel_GetFlagsFB0(sActivePokemon[!gBattleState.unk_00->unk_2C]) == 0) {
        if (gBattleState.unk_00->unk_14 == 0x1D) {
            Battle_QueueOpponentMove(sActivePokemon[!gBattleState.unk_00->unk_2C], arg0, 4);
        }

        if (Battle_WaitFramesNonBlocking(0x1E) != 0) {
            Camera_SmoothZoomOut(arg0, sActivePokemon[!gBattleState.unk_00->unk_2C]);
        }

        if (((sp20->unk_04 >> 1) == (sActivePokemon[!gBattleState.unk_00->unk_2C]->unk_000.unk_040.unk_08 >> 0x10)) &&
            (sp24->unk_2D != 0x12)) {
            Dialog_SetMode(9);
        }

        if (sp20->unk_0A == ((sActivePokemon[!gBattleState.unk_00->unk_2C]->unk_000.unk_040.unk_08 >> 0x10) + 3)) {
            sActivePokemon[!gBattleState.unk_00->unk_2C]->unk_000.unk_000.unk_02 &= ~0x20;
            SetEntityAnimFlags(sActivePokemon[!gBattleState.unk_00->unk_2C], 0x100);
            Battle_FinishTurn();
            gBattleState.unk_00->unk_20 += 1;
        }
        Camera_SetDistanceToEntity(arg0, sActivePokemon[!gBattleState.unk_00->unk_2C], 0);
    }
}

void Battle_ProcessOpponentActionStep(CameraStruct* arg0) {
    Camera_SetDistanceToEntity(arg0, sActivePokemon[!gBattleState.unk_00->unk_2C], 1);
    if (Battle_WaitForAnimation(0x19) != 0) {
        ResetSoundDurations();
        gBattleState.unk_00->unk_20++;
    }
}

void Battle_ProcessOpponentActionStep2(CameraStruct* arg0) {
    unk_BattlePlayerAnimState* temp_s0 = &sActivePokemon[!gBattleState.unk_00->unk_2C]->unk_654;

    Camera_SetDistanceToEntity(arg0, sActivePokemon[!gBattleState.unk_00->unk_2C], 1);

    if (Battle_WaitForAnimation(5) != 0) {
        Battle_SetAnimChannelFlag(1);
        Audio_SetSfxDurationScale(3, 0);

        if (temp_s0->unk_2D != 0x12) {
            temp_s0->unk_2D = 0x10;
        }

        if (temp_s0->unk_2D == 0x12) {
            temp_s0->unk_2D = 0x13;
        }

        gBattleState.unk_00->unk_20++;
    }
}

void Battle_DetermineNextPhaseAfterOpponent(CameraStruct* arg0) {
    unk_BattlePlayerAnimState* sp24 = &sActivePokemon[!gBattleState.unk_00->unk_2C]->unk_654;
    unk_BattlePlayerAnimState* sp20 = &sActivePokemon[gBattleState.unk_00->unk_2C]->unk_654;

    if (Battle_WaitForAnimation(0xA) != 0) {
        Battle_FinishTurn();
        Battle_ClearSubstateFlag();
        gBattleState.unk_00->unk_20++;
        if (sp24->unk_2D == 0x10) {
            gBattleState.unk_00->unk_14 = 0;
            gBattleState.unk_00->unk_20 = 0;

            if ((sp20->unk_2D == 0x11) || (sp20->unk_2D == 0x12)) {
                gBattleState.unk_00->unk_38 = 5;
                gBattleState.unk_00->unk_2C = !gBattleState.unk_00->unk_2C;
            } else if ((sp24->unk_2D == 0x13) || (sp20->unk_2D == 0x13)) {
                Dialog_SetMode(0xE);
                Vec3f_Set(&arg0->unk_60.at, 0.0f, 75.0f, 0.0f);
                Vec3f_Set(&arg0->unk_60.eye, 0.0f, 80.0f, 400.0f);
                HandleStadiumModeAudio();
                gBattleState.unk_00->unk_2C = !gBattleState.unk_00->unk_2C;
                gBattleState.unk_00->unk_20 = 8;
            } else {
                gBattleState.unk_00->unk_38 = 4;
            }
        } else if ((sp20->unk_2D == 0x12) || (sp20->unk_2D == 0x11)) {
            gBattleState.unk_00->unk_14 = 0;
            gBattleState.unk_00->unk_20 = 0;
            gBattleState.unk_00->unk_38 = 5;
            gBattleState.unk_00->unk_2C = !gBattleState.unk_00->unk_2C;
        } else {
            Battle_HandleSpecialAnimation(arg0);
        }
        ResetSoundDurations();
    }
}

void UnusedBattleStateHandler(UNUSED CameraStruct* arg0) {
}

void Battle_AdjustCameraForAction(CameraStruct* arg0) {
    unk_BattlePlayerEntity* temp_s0;
    UNUSED s32 pad;
    f32 sp44;
    f32 sp40;
    s16 sp3E;
    UNUSED s16 pad2;
    u8 sp3B;
    s16 tmp1;

    temp_s0 = sActivePokemon[gBattleState.unk_00->unk_2C];
    sp3B = temp_s0->unk_000.unk_01A - 1;

    if (Battle_CheckPlayerAction(arg0, temp_s0, 1, 0) != 0) {
        Battle_FinishTurn();
        Dialog_SetMode(0xE);
        Camera_SetClippingPlanes(arg0, 10.0f, 12800.0f);
        arg0->unk_24.fovy = 60.0f;
        if ((sActivePokemon[gBattleState.unk_00->unk_2C]->unk_000.unk_01A == 0x5F) && (gBattleState.unk_00->unk_2C == 1)) {
            sp3B = 0x97;
        }

        sp44 = (gAnimDataSetC[gBattleState.unk_00->unk_2C]->unk_00.y + temp_s0->unk_000.unk_024.y) + gCameraOffsetTable[sp3B].z;
        sp40 = ((gAnimDataSetC[gBattleState.unk_00->unk_2C]->unk_00.z + gCameraOffsetTable[sp3B].y) * temp_s0->unk_4B0) +
               temp_s0->unk_000.unk_024.x;

        Vec3f_Set(&arg0->unk_60.at, sp40, sp44, temp_s0->unk_000.unk_024.z);

        sp40 = gAnimDataSetC[gBattleState.unk_00->unk_2C]->unk_00.x * gCameraOffsetTable[sp3B].x;
        sp3E = gAnimDataSetC[gBattleState.unk_00->unk_2C]->unk_0C;
        tmp1 = (temp_s0->unk_4B0 * gAnimDataSetC[gBattleState.unk_00->unk_2C]->unk_0E) + GetPlayerSideYaw(temp_s0);
        Camera_SetViewParameters(&arg0->unk_60.at, &arg0->unk_60.eye, sp40, sp3E, tmp1);
        gBattleState.unk_00->unk_20++;
    }
}

void BattleScene_CompleteSendOutCameraFade(UNUSED CameraStruct* arg0) {
    if (Battle_WaitForAnimation(0x50) != 0) {
        gBattleState.unk_00->unk_40 = gBattleState.unk_00->unk_2C + 1;
        Dialog_Clear();
        Stage_SetFadeColor(0x14);
    }
}

void BattleScene_CompleteSendOutExtendedFade(UNUSED CameraStruct* arg0) {
    if (Battle_WaitForAnimation(0x7D) != 0) {
        gBattleState.unk_00->unk_40 = gBattleState.unk_00->unk_2C + 1;
        Stage_SetFadeColor(0x14);
    }
}

void BattleScene_AdvanceSendOutFollowupCamera(CameraStruct* arg0) {
    UNUSED s32 pad[2];
    unk_BattlePlayerAnimState* sp24 = &sActivePokemon[!gBattleState.unk_00->unk_2C]->unk_654;
    unk_BattleAnimDataEntry* sp20 = &gAnimDataByPlayer[!gBattleState.unk_00->unk_2C]->unk_B10;

    if (AnimChannel_GetFlagsFB0(sActivePokemon[!gBattleState.unk_00->unk_2C]) == 0) {
        if (gBattleState.unk_00->unk_14 == 0x1D) {
            Battle_QueueOpponentMove(sActivePokemon[!gBattleState.unk_00->unk_2C], arg0, 4);
        }

        if (Battle_WaitFramesNonBlocking(0x1E) != 0) {
            Camera_SmoothZoomOut(arg0, sActivePokemon[!gBattleState.unk_00->unk_2C]);
        }

        if (((sp20->unk_04 >> 1) == (sActivePokemon[!gBattleState.unk_00->unk_2C]->unk_000.unk_040.unk_08 >> 0x10)) &&
            (sp24->unk_2D != 0x12)) {
            Dialog_SetMode(9);
        }

        if (sp20->unk_0A == ((sActivePokemon[!gBattleState.unk_00->unk_2C]->unk_000.unk_040.unk_08 >> 0x10) + 3)) {
            sActivePokemon[!gBattleState.unk_00->unk_2C]->unk_000.unk_000.unk_02 &= ~0x20;
            SetEntityAnimFlags(sActivePokemon[!gBattleState.unk_00->unk_2C], 0x100);
            Battle_FinishTurn();
            ConfigureCameraForModel(sActivePokemon[!gBattleState.unk_00->unk_2C], arg0);
            gBattleState.unk_00->unk_20 = 2;
        }

        Camera_SetDistanceToEntity(arg0, sActivePokemon[!gBattleState.unk_00->unk_2C], 0);
    }
}

void Battle_StateMachine(CameraStruct* arg0) {
    switch (gBattleState.unk_00->unk_20) {
        case 0:
            Battle_HandleOpponentDefeat(arg0);
            break;

        case 1:
            Battle_HandleOpponentAnimation(arg0);
            break;

        case 2:
            Battle_ProcessOpponentActionStep(arg0);
            break;

        case 3:
            Battle_ProcessOpponentActionStep2(arg0);
            break;

        case 4:
            Battle_DetermineNextPhaseAfterOpponent(arg0);
            break;

        case 5:
            UnusedBattleStateHandler(arg0);
            break;

        case 6:
            Battle_AdjustCameraForAction(arg0);
            break;

        case 7:
            BattleScene_CompleteSendOutCameraFade(arg0);
            break;

        case 8:
            BattleScene_CompleteSendOutExtendedFade(arg0);
            break;

        case 10:
            BattleScene_AdvanceSendOutFollowupCamera(arg0);
            break;
    }
}

void Battle_HandleState2(UNUSED CameraStruct* arg0) {
    unk_BattlePlayerAnimState* sp1C = &sActivePokemon[!gBattleState.unk_00->unk_2C]->unk_654;

    if (Battle_WaitForAnimation(2) != 0) {
        Battle_FinishTurn();
        Battle_ClearSubstateFlag();
        gBattleState.unk_00->unk_20 += 1;
        if (sp1C->unk_2D == 0x10) {
            gBattleState.unk_00->unk_14 = 0;
            gBattleState.unk_00->unk_20 = 0;
            gBattleState.unk_00->unk_38 = 4;
        } else {
            gBattleState.unk_00->unk_40 = gBattleState.unk_00->unk_2C + 1;
        }
        ResetSoundDurations();
    }
}

void Battle_StateMachineVariant(CameraStruct* arg0) {
    switch (gBattleState.unk_00->unk_20) {
        case 0:
            Battle_HandleOpponentDefeat(arg0);
            break;

        case 1:
            Battle_HandleOpponentAnimation(arg0);
            break;

        case 2:
            Battle_ProcessOpponentActionStep(arg0);
            break;

        case 3:
            Battle_ProcessOpponentActionStep2(arg0);
            break;

        case 4:
            Battle_HandleState2(arg0);
            break;

        case 5:
            UnusedBattleStateHandler(arg0);
            break;

        case 10:
            BattleScene_AdvanceSendOutFollowupCamera(arg0);
            break;
    }
}

void Battle_ApplyStatusEffectAnimation(unk_BattlePlayerEntity* arg0) {
    unk_BattlePlayerAnimState* ptr = &arg0->unk_654;

    if (ptr->unk_34 & 0x200) {
        arg0->unk_000.unk_024.y = gPokemonModelDimensions[IsPrimaryEntity(arg0)].unk_08;
        ClearEntityAnimFlags(arg0, 0x608);
    } else if (ptr->unk_34 & 0x4008) {
        arg0->unk_000.unk_01D = 0xFF;
        RunParticleEffectScript(4, arg0);
        arg0->unk_000.unk_024.y = gPokemonModelDimensions[IsPrimaryEntity(arg0)].unk_08;
        arg0->unk_000.unk_000.unk_02 &= ~0x2;
        arg0->unk_000.unk_000.unk_02 |= 0x20;
        arg0->unk_000.unk_000.unk_01 |= 1;
        ClearEntityAnimFlags(arg0, 0x4608);
    }
}

void Battle_SetupInitialCamera(CameraStruct* arg0) {
    s32 sp24;
    unk_BattlePlayerAnimState* sp20 = &sActivePokemon[0]->unk_654;
    unk_BattlePlayerAnimState* sp1C = &sActivePokemon[1]->unk_654;

    AnimStateQueue_ResetAll();
    Battle_ResetSubstate();

    sp24 = Math_RandomU16Scaled(5);
    if (sp24 >= 5) {
        sp24 = 0;
    }

    if ((sp20->unk_34 & 0x4000) || ((sp1C->unk_34 & 0x4000) != 0)) {
        sp24 = 2;
    } else if ((sp20->unk_34 & 0x200) || (sp1C->unk_34 & 0x200)) {
        sp24 = 4;
    } else if ((sp20->unk_2D == 0x10) || (sp1C->unk_2D == 0x10)) {
        sp24 = 2;
    }

    Vector_Copy(&gCameraPreset.unk_00, &gCameraFarSettings);
    Battle_ApplyCameraPreset(&gBattleCameraPresetTable2[sp24], arg0);
    Battle_ApplyCameraSettings(arg0, gCurrentPlayer, 0);
    gBattleState.unk_00->unk_20++;
}

void Battle_TryAdvancePhase(CameraStruct* arg0) {
    if (Battle_CheckPlayerAction(arg0, gCurrentPlayer, 0, 1) != 0) {
        Battle_SetPhase(arg0, 2);
    }
}

void Battle_HandleSubstate0(CameraStruct* arg0) {
    switch (gBattleState.unk_00->unk_20) {
        case 0:
            Battle_SetupInitialCamera(arg0);
            break;

        case 1:
            Battle_TryAdvancePhase(arg0);
            break;
    }
}

void Player_SetActionTimer(unk_BattlePlayerEntity* arg0) {
    arg0->unk_654.unk_30 = 0x800;
}

void Battle_StartTurn(UNUSED CameraStruct* arg0) {
    Battle_SetAnimChannelFlag(2);
    Player_SetActionTimer(gCurrentPlayer);
    AnimChannel_HandleBattleState(gCurrentPlayer);
}

void Battle_SelectMove(CameraStruct* arg0) {
    PokemonAudioInfo* sp1C = &sActivePokemon[gBattleState.unk_00->unk_2C]->unk_654.unk_38;
    unk_BattlePlayerAnimState* sp18 = &sActivePokemon[gBattleState.unk_00->unk_2C]->unk_654;
    s32 var_t0;

    if (gBattleState.unk_00->unk_48 == 0xE) {
        var_t0 = GetMappedAnimDataField0D(sActivePokemon[gBattleState.unk_00->unk_2C]);
    } else if ((gBattleState.unk_00->unk_48 == 0x1C) || (gBattleState.unk_00->unk_48 == 0x11) ||
               (gBattleState.unk_00->unk_48 == 0x1F)) {
        var_t0 = 0;
    } else {
        var_t0 = GetAnimDataField0D(sActivePokemon[gBattleState.unk_00->unk_2C]);
    }

    if ((sp1C->unk_5A == 0x3A) || (sp1C->unk_5A == 0x8F)) {
        if ((gBattleState.unk_00->unk_48 != 0x1C) && (gBattleState.unk_00->unk_48 != 0x11) &&
            (gBattleState.unk_00->unk_48 != 0x1F)) {
            var_t0 = 0x16;
        }
    }

    switch (var_t0) {
        case 20:
            Battle_ExecuteMove(gCurrentPlayer, arg0,
                          gBattleState.unk_00->unk_50 = gMoveIdSetA[Math_RandomIntBelow(ARRAY_COUNT(gMoveIdSetA))], 1);
            break;

        case 21:
            Battle_ExecuteMove(gCurrentPlayer, arg0,
                          gBattleState.unk_00->unk_50 = gMoveIdSetB[Math_RandomIntBelow(ARRAY_COUNT(gMoveIdSetB))], 1);
            break;

        case 22:
            Battle_ExecuteMove(gCurrentPlayer, arg0,
                          gBattleState.unk_00->unk_50 = gMoveIdSetC[Math_RandomIntBelow(ARRAY_COUNT(gMoveIdSetC))], 1);
            break;

        case 23:
            Battle_ExecuteMove(gCurrentPlayer, arg0,
                          gBattleState.unk_00->unk_50 = gMoveIdSetD[Math_RandomIntBelow(ARRAY_COUNT(gMoveIdSetD))], 1);
            break;

        case 24:
            Battle_ExecuteMove(gCurrentPlayer, arg0,
                          gBattleState.unk_00->unk_50 = gMoveIdSetE[Math_RandomIntBelow(ARRAY_COUNT(gMoveIdSetE))], 1);
            break;

        default:
            Battle_ExecuteMove(gCurrentPlayer, arg0, gBattleState.unk_00->unk_50 = var_t0, 1);
            if (sp18->unk_34 & 0x4000) {
                arg0->unk_60.at.y = 0.0f;
            }
            break;
    }
}

s32 Battle_HandleMoveSelection(CameraStruct* arg0) {
    UNUSED s32 pad;
    unk_BattlePlayerAnimState* sp20 = &sActivePokemon[gBattleState.unk_00->unk_2C]->unk_654;

    Battle_FinishTurn();
    Battle_SelectMove(arg0);

    if (Battle_HandleSpecificPhases() != 0) {
        return 0;
    }

    if (gBattleState.unk_00->unk_48 == 0x14) {
        ExecuteAnimStateHandlers(sActivePokemon[gBattleState.unk_00->unk_2C], 0x15);
    } else if (gBattleState.unk_00->unk_48 == 0x18) {
        ExecuteAnimStateHandlers(sActivePokemon[gBattleState.unk_00->unk_2C], 3);
    } else if (sp20->unk_34 & 0x4400) {
        ExecuteAnimStateHandlers(sActivePokemon[gBattleState.unk_00->unk_2C], 3);
        Battle_ExecuteMove(sActivePokemon[gBattleState.unk_00->unk_2C], arg0, gBattleState.unk_00->unk_50 = 2, 1);
    } else {
        ExecuteAnimStateHandlers(sActivePokemon[gBattleState.unk_00->unk_2C], 3);
    }

    Battle_ClearSubstateFlag();
    return 1;
}

void Battle_MainStep(CameraStruct* arg0) {
    unk_BattlePlayerAnimState* sp1C = &gCurrentPlayer->unk_654;

    Math_ExponentialApproach(&arg0->unk_24.fovy, 30.0f, 0.05f);

    switch (gBattleState.unk_00->unk_3C) {
        case 0:
            UpdateEntityStateByMode(sActivePokemon[0]);
            UpdateEntityStateByMode(sActivePokemon[1]);

            if ((HandlePokemonFaintOrSwitch() == 0) && (Battle_CheckOpponentSpecialAction() == 0)) {
                PrepareEntityAnimState(gCurrentPlayer);
                Battle_StartTurn(arg0);
                Battle_SetSubstateFlag();

                if ((gBattleState.unk_00->unk_34 == 1) && (gOpponentPlayer->unk_4C8 == 1)) {
                    Battle_ApplyStatusEffectAnimation(gOpponentPlayer);
                }

                GetEntityCenterPosition(gCurrentPlayer, &gCameraPreset.unk_00);

                if (sp1C->unk_34 & 0x4000) {
                    gCameraPreset.unk_00.y = 15.000001f;
                }

                if (gBattleState.unk_00->unk_34 == 1) {
                    Battle_SetCameraFOV30(arg0);

                    if ((gBattleState.unk_00->unk_48 == 0x1C) || (gBattleState.unk_00->unk_48 == 0x11) ||
                        (gBattleState.unk_00->unk_48 == 0x1F)) {
                        Battle_PlayMoveEffect(gCurrentPlayer, arg0, 3);
                    } else {
                        Battle_PlayMoveEffect(gCurrentPlayer, arg0, 4);
                    }

                    if (sp1C->unk_34 & 0x4000) {
                        arg0->unk_60.at.y = 15.000001f;
                    }
                    Battle_ApplyAnimEffect(gCurrentPlayer);
                } else if ((gBattleState.unk_00->unk_48 == 0x1C) || (gBattleState.unk_00->unk_48 == 0x11) ||
                           (gBattleState.unk_00->unk_48 == 0x1F)) {
                    Battle_PlayCameraTransition(&gCameraPosA, arg0, gCurrentPlayer);
                } else {
                    Battle_PlayCameraTransition(&gCameraPosB, arg0, gCurrentPlayer);
                }
            }
            break;

        case 1:
            if (AnimChannel_CheckAndReset(gCurrentPlayer) != 0) {
                gInitialMoveIndex = gCurrentMoveIndex = gTotalMoveCount;
                Dialog_SetMode(0);
                Battle_FinishTurn();
                gBattleState.unk_00->unk_3C += 1;
            }
            break;

        case 2:
            if (gBattleState.unk_00->unk_34 == 1) {
                if ((gBattleState.unk_00->unk_48 == 0x1C) || (gBattleState.unk_00->unk_48 == 0x11) ||
                    (gBattleState.unk_00->unk_48 == 0x1F)) {
                    if (Battle_WaitForAnimation(0xA) != 0) {
                        Battle_SetCameraFOV30(arg0);
                        if (Battle_HandleMoveSelection(arg0) != 0) {
                            gBattleState.unk_00->unk_20 = 1;
                        }
                    }
                } else if (Battle_WaitForAnimation(0x28) != 0) {
                    Battle_SetCameraFOV30(arg0);
                    if (Battle_HandleMoveSelection(arg0) != 0) {
                        gBattleState.unk_00->unk_20 = 1;
                    }
                }
            } else if (Battle_CheckPlayerAction(arg0, gCurrentPlayer, 1, 1) != 0) {
                Battle_SetCameraFOV30(arg0);
                if (Battle_HandleMoveSelection(arg0) != 0) {
                    gBattleState.unk_00->unk_20 = 1;
                }
            }
            break;
    }
}

void Battle_ReselectMoveIfNeeded(CameraStruct* arg0) {
    s32 temp_v0;
    s32 temp_t0;

    if (gCurrentMoveIndex != gTotalMoveCount) {
        temp_v0 = GetAnimDataField0E(sActivePokemon[gBattleState.unk_00->unk_2C]) & 0xFFFFFFFF;
        switch (temp_v0) {
            case 20:
                do {
                    temp_t0 = gMoveIdSetA[Math_RandomIntBelow(5.0f)];
                } while (temp_t0 == gBattleState.unk_00->unk_50);
                gBattleState.unk_00->unk_50 = temp_t0;
                Battle_ExecuteMove(gCurrentPlayer, arg0, gBattleState.unk_00->unk_50, 1);
                break;

            case 21:
                do {
                    temp_t0 = gMoveIdSetB[Math_RandomIntBelow(4.0f)];
                } while (temp_t0 == gBattleState.unk_00->unk_50);
                gBattleState.unk_00->unk_50 = temp_t0;
                Battle_ExecuteMove(gCurrentPlayer, arg0, gBattleState.unk_00->unk_50, 1);
                break;

            case 22:
                do {
                    temp_t0 = gMoveIdSetC[Math_RandomIntBelow(3.0f)];
                } while (temp_t0 == gBattleState.unk_00->unk_50);
                gBattleState.unk_00->unk_50 = temp_t0;
                Battle_ExecuteMove(gCurrentPlayer, arg0, gBattleState.unk_00->unk_50, 1);
                break;

            case 23:
                do {
                    temp_t0 = gMoveIdSetD[Math_RandomIntBelow(6.0f)];
                } while (temp_t0 == gBattleState.unk_00->unk_50);
                gBattleState.unk_00->unk_50 = temp_t0;
                if (1) {}
                if (1) {}
                if (1) {}
                if (1) {}
                Battle_ExecuteMove(gCurrentPlayer, arg0, gBattleState.unk_00->unk_50, 1);
                break;

            case 24:
                do {
                    temp_t0 = gMoveIdSetE[Math_RandomIntBelow(4.0f)];
                } while (temp_t0 == gBattleState.unk_00->unk_50);
                gBattleState.unk_00->unk_50 = temp_t0;
                Battle_ExecuteMove(gCurrentPlayer, arg0, gBattleState.unk_00->unk_50, 1);
                break;

            default:
                if (temp_v0 != gBattleState.unk_00->unk_50) {
                    Battle_ExecuteMove(gCurrentPlayer, arg0, temp_v0, 1);
                }
                break;
        }
    }
}

void Battle_ChooseMoveByContext(CameraStruct* arg0, s32 arg1) {
    PokemonAudioInfo* sp1C = &sActivePokemon[gBattleState.unk_00->unk_2C]->unk_654.unk_38;
    s32 sp18;

    if ((gBattleState.unk_00->unk_50 != 1) && (gBattleState.unk_00->unk_50 != 4) && (gBattleState.unk_00->unk_50 != 5) &&
        (gBattleState.unk_00->unk_50 != 8) && (gBattleState.unk_00->unk_50 != 9) && (gBattleState.unk_00->unk_50 != 0xA) &&
        (gBattleState.unk_00->unk_50 != 0xB)) {
        if (arg1 == 1) {
            sp18 = GetMappedAnimDataField0E(sActivePokemon[gBattleState.unk_00->unk_2C]);
        } else {
            sp18 = GetAnimDataField0E(sActivePokemon[gBattleState.unk_00->unk_2C]);
        }

        if ((sp1C->unk_5A == 0x3A) || (sp1C->unk_5A == 0x8F)) {
            sp18 = 0x19;
        }

        if (sp18 == 25) {
            return;
        }

        switch (sp18) {
            case 20:
                gBattleState.unk_00->unk_50 = gMoveIdSetA[Math_RandomIntBelow(ARRAY_COUNT(gMoveIdSetA))];
                if (sp18 != gBattleState.unk_00->unk_50) {
                    Battle_ExecuteMove(gCurrentPlayer, arg0, gBattleState.unk_00->unk_50, 1);
                }
                break;

            case 21:
                gBattleState.unk_00->unk_50 = gMoveIdSetB[Math_RandomIntBelow(ARRAY_COUNT(gMoveIdSetB))];
                if (sp18 != gBattleState.unk_00->unk_50) {
                    Battle_ExecuteMove(gCurrentPlayer, arg0, gBattleState.unk_00->unk_50, 1);
                }
                break;

            case 22:
                gBattleState.unk_00->unk_50 = gMoveIdSetC[Math_RandomIntBelow(ARRAY_COUNT(gMoveIdSetC))];
                if (sp18 != gBattleState.unk_00->unk_50) {
                    Battle_ExecuteMove(gCurrentPlayer, arg0, gBattleState.unk_00->unk_50, 1);
                }
                break;

            case 23:
                gBattleState.unk_00->unk_50 = gMoveIdSetD[Math_RandomIntBelow(ARRAY_COUNT(gMoveIdSetD))];
                if (sp18 != gBattleState.unk_00->unk_50) {
                    Battle_ExecuteMove(gCurrentPlayer, arg0, gBattleState.unk_00->unk_50, 1);
                }
                break;

            case 24:
                gBattleState.unk_00->unk_50 = gMoveIdSetE[Math_RandomIntBelow(ARRAY_COUNT(gMoveIdSetE))];
                if (sp18 != gBattleState.unk_00->unk_50) {
                    Battle_ExecuteMove(gCurrentPlayer, arg0, gBattleState.unk_00->unk_50, 1);
                }
                break;

            default:
                if (sp18 != gBattleState.unk_00->unk_50) {
                    if (1) {}
                    Battle_ExecuteMove(gCurrentPlayer, arg0, sp18, 1);
                }
                break;
        }
    }
}

s32 Battle_AdjustCameraForMove(CameraStruct* arg0, s32 arg1) {
    UNUSED s32 pad;
    s32 sp18 = 0;

    switch (gBattleState.unk_00->unk_50) {
        case 1:
            Math_ExponentialApproach(&arg0->unk_24.fovy, 60.0f, 0.03f);
            sp18 = 1;
            break;

        case 4:
        case 5:
        case 8:
        case 9:
        case 10:
        case 11:
            Battle_ApplySpecialCamera(arg0, gCurrentPlayer);
            sp18 = 1;
            break;

        default:
            if ((gCurrentPlayer->unk_4B4 != 6) && (gCurrentPlayer->unk_4B4 != 4) && (arg1 != 0)) {
                Battle_AdvanceCameraTimeline(arg0, gCurrentPlayer);
            }
            break;
    }
    return sp18;
}

void Battle_EndTurn(UNUSED CameraStruct* arg0) {
    AdjustModelBaseYForFlag8(gCurrentPlayer);
    ClearEntityAnimFlags(gCurrentPlayer, 0x10);
    if (Battle_HandlePhase10or14or8() == 0) {
        gBattleState.unk_00->unk_20 = 2;
    }
    Battle_SetAnimChannelFlag(1);
}

s32 Battle_IsMoveReady(UNUSED CameraStruct* arg0) {
    if (Battle_WaitForAnimation(GetAnimDataField0FOrDefault(gCurrentPlayer)) != 0) {
        return 1;
    }
    return 0;
}

void Battle_ProcessMovePhase0(CameraStruct* arg0) {
    switch (gBattleState.unk_00->unk_3C) {
        case 0:
            Battle_AdjustCameraForMove(arg0, 1);
            if (Battle_IsMoveReady(arg0) != 0) {
                Battle_FinishTurn();
                Battle_SetSubstateFlag();
                Battle_ChooseMoveByContext(arg0, 0);
            }
            break;

        case 1:
            Battle_AdjustCameraForMove(arg0, 1);
            if (EvaluateAnimStateAgainstBattle(gCurrentPlayer, 0x32) != 0) {
                Battle_FinishTurn();
                Battle_ClearSubstateFlag();
                Battle_EndTurn(arg0);
            }
            break;
    }
}

void Battle_ProcessMovePhase1(CameraStruct* arg0) {
    switch (gBattleState.unk_00->unk_3C) {
        case 0:
            Battle_AdvanceCameraTimeline(arg0, gCurrentPlayer);
            if (EvaluateAnimStateAgainstBattle(gCurrentPlayer, 0x32) != 0) {
                Battle_StoreCameraFOV(arg0);
                gCurrentMoveIndex--;
                Battle_ReselectMoveIfNeeded(arg0);
                if ((gCurrentMoveIndex < 0) || (gSpecialFlag != 0)) {
                    gCurrentMoveIndex = gTotalMoveCount;
                    gBattleState.unk_00->unk_3C++;
                } else {
                    ExecuteAnimStateHandlers(sActivePokemon[gBattleState.unk_00->unk_2C], 0x13);
                    ResetSoundDurations();
                    Battle_SetAnimChannelFlag(1);
                    gBattleState.unk_00->unk_3C = 0;
                }
            }
            break;

        case 1:
            Battle_AdvanceCameraTimeline(arg0, gCurrentPlayer);
            Battle_FinishTurn();
            Battle_ClearSubstateFlag();
            gBattleState.unk_00->unk_48 = 0;
            ResetSoundDurations();
            Battle_EndTurn(arg0);
            break;
    }
}

void Battle_ProcessMovePhase2(CameraStruct* arg0) {
    switch (gBattleState.unk_00->unk_3C) {
        case 0:
            if (Battle_WaitForAnimation(0xF) != 0) {
                Battle_ApplyAnimChannelEffect(7, gCurrentPlayer);
                Battle_FinishTurn();
                Battle_SetSubstateFlag();
                Battle_PlayMoveEffect(gCurrentPlayer, arg0, 3);
            }
            break;

        case 1:
            Battle_AdvanceCameraTimeline(arg0, gCurrentPlayer);
            if (EvaluateAnimStateAgainstBattle(gCurrentPlayer, 0x1E) != 0) {
                Battle_FinishTurn();
                Battle_ClearSubstateFlag();
                Battle_EndTurn(arg0);
            }
            break;
    }
}

void Battle_ProcessMovePhase3(CameraStruct* arg0) {
    UNUSED s32 pad;
    PokemonAudioInfo* sp18 = &gCurrentPlayer->unk_654.unk_38;

    IsPrimaryEntity(gCurrentPlayer);

    switch (gBattleState.unk_00->unk_3C) {
        case 0:
            Battle_FinishTurn();
            Battle_SetSubstateFlag();
            Vec3f_Set(&gCameraPreset.unk_00, gCurrentPlayer->unk_4B0 * -175.0f, 25.0f, 0.0f);
            Battle_PlayCameraTransition(&gCameraPosC, arg0, gCurrentPlayer);
            if ((gCurrentPlayer->unk_000.unk_01A != 0x33) && (gCurrentPlayer->unk_000.unk_01A != 0x32)) {
                AnimChannel_StartMoveAction(gCurrentPlayer, sp18->unk_5A);
            }
            break;

        case 1:
            if (Battle_CheckPlayerAction(arg0, gCurrentPlayer, 1, 0) != 0) {
                Battle_FinishTurn();
                Battle_ClearSubstateFlag();
                Battle_EndTurn(arg0);
            }
            break;
    }
}

void Battle_ProcessMovePhase4(CameraStruct* arg0) {
    switch (gBattleState.unk_00->unk_3C) {
        case 0:
            Battle_FinishTurn();
            Battle_SetSubstateFlag();
            GetEntityCenterPosition(gCurrentPlayer, &gCameraPreset.unk_00);
            Battle_PlayCameraTransition(&gCameraPosD, arg0, gCurrentPlayer);
            break;

        case 1:
            Battle_ApplySpecialCamera(arg0, gCurrentPlayer);
            if (EvaluateAnimStateAgainstBattle(gCurrentPlayer, 0x1E) != 0) {
                Battle_FinishTurn();
                Battle_ClearSubstateFlag();
                Battle_EndTurn(arg0);
            }
            break;
    }
}

void Battle_DispatchMoveHandler(CameraStruct* arg0) {
    unk_BattlePlayerAnimState* temp_a2 = &sActivePokemon[gBattleState.unk_00->unk_2C]->unk_654;
    u32 var_v1 = 0;

    if (gBattleState.unk_00->unk_48 == 0x18) {
        var_v1 = 0xA;
    } else if (gBattleState.unk_00->unk_48 == 0x14) {
        var_v1 = 0xB;
    } else if (temp_a2->unk_34 & 0x4000) {
        var_v1 = 0xC;
    } else if (temp_a2->unk_34 & 0x10) {
        var_v1 = 0xC;
    } else if (temp_a2->unk_34 & 0x400) {
        var_v1 = 0xD;
    }

    switch (var_v1) {
        case 0:
            Battle_ProcessMovePhase0(arg0);
            break;

        case 10:
            Battle_ProcessMovePhase1(arg0);
            break;

        case 11:
            Battle_ProcessMovePhase2(arg0);
            break;

        case 12:
            Battle_ProcessMovePhase3(arg0);
            break;

        case 13:
            Battle_ProcessMovePhase4(arg0);
            break;

        default:
            Battle_ProcessMovePhase0(arg0);
            break;
    }
}

void Player_HandleSpecialAnimation(unk_BattlePlayerEntity* arg0) {
    if (arg0->unk_654.unk_38.unk_5A == 0x45) {
        BattleAnim_ResetOwnerFacingAndExitStatusIdle(arg0);
    }
}

s32 Player_IsSpecialCondition(unk_BattlePlayerEntity* arg0) {
    if (arg0->unk_654.unk_38.unk_5A == 0x53) {
        return 1;
    }
    return 0;
}

void Battle_CheckAndResetIfBothReady(CameraStruct* arg0, s32* arg1, s32* arg2) {
    if ((*arg1 == 1) && (*arg2 == 1)) {
        Dialog_Clear();
        Battle_ApplyAnimEffect(gCurrentPlayer);
        gBattleState.unk_00->unk_1A = 0;
        Battle_FinishTurn();
        Battle_AdvanceTurnState();
        Battle_ClearSubstateFlag();
        Battle_ResetSubstate();
        Battle_UpdateHPAndProceed(arg0);
    }
}

void Battle_OpponentTurnPhase0(CameraStruct* arg0) {
    switch (gBattleState.unk_00->unk_3C) {
        case 0:
            if (HandlePlayerActionFlag800Alt(gOpponentPlayer) == 0) {
                Battle_QueueOpponentMove(gOpponentPlayer, arg0, 0);
                Battle_FinishTurn();
                Battle_SetSubstateFlag();
                ExecuteAnimStateHandlers(gCurrentPlayer, 0xE);
                HandleFlag4000AnimEffect(gOpponentPlayer);
                Battle_ApplyAnimStateEffects(gOpponentPlayer);
                Dialog_SetMode(1);
            }
            break;

        case 1:
            Battle_ProcessOpponentAction(arg0, gOpponentPlayer);
            if ((Pokemon_CheckAnimStateC(gOpponentPlayer) != 0) || (Battle_WaitForAnimation(0x5A) != 0)) {
                gPlayer0ReadyFlag = UpdatePokemonHP(gOpponentPlayer);
                gPlayer1ReadyFlag = UpdatePokemonHP(gCurrentPlayer);
                Battle_CheckAndResetIfBothReady(arg0, &gPlayer0ReadyFlag, &gPlayer1ReadyFlag);
            }
            break;
    }
}

void Battle_OpponentTurnPhase1(CameraStruct* arg0) {
    s32 sp1C;

    switch (gBattleState.unk_00->unk_3C) {
        case 0:
            if (HandlePlayerActionFlag800Alt(gOpponentPlayer) == 0) {
                Battle_ApplyAnimStateEffects(gOpponentPlayer);
                Battle_QueueOpponentMove(gOpponentPlayer, arg0, 0);
                Battle_FinishTurn();
                Battle_SetSubstateFlag();
                ExecuteAnimStateHandlers(gCurrentPlayer, 0xB);
                HandleFlag4000AnimEffect(gOpponentPlayer);
                Dialog_SetMode(1);
            }
            break;

        case 1:
            Battle_ProcessOpponentAction(arg0, gOpponentPlayer);
            gPlayer0ReadyFlag = UpdatePokemonHP(gOpponentPlayer);
            gPlayer1ReadyFlag = UpdatePokemonHP(gCurrentPlayer);
            sp1C = GetAnimStateResultCode(gCurrentPlayer);
            if ((sp1C == 2) && ((Pokemon_CheckAnimStateC(gOpponentPlayer) != 0) || (Battle_WaitForAnimation(0x64) != 0))) {
                Battle_CheckAndResetIfBothReady(arg0, &gPlayer0ReadyFlag, &gPlayer1ReadyFlag);
            } else if (sp1C == 1) {
                Battle_CheckAndResetIfBothReady(arg0, &gPlayer0ReadyFlag, &gPlayer1ReadyFlag);
            }
            break;
    }
}

void BattleScene_RunMoveEffectEndHpTransition(CameraStruct* arg0) {
    PokemonAudioInfo* sp34 = &gCurrentPlayer->unk_654.unk_38;
    UNUSED s32 pad;
    UNUSED s16 pad2;
    s16 sp2C;

    switch (gBattleState.unk_00->unk_3C) {
        case 0:
            if (HandlePlayerActionFlag800Alt(gOpponentPlayer) == 0) {
                Battle_ApplyAnimStateEffects(gOpponentPlayer);
                Battle_QueueOpponentMove(gOpponentPlayer, arg0, 0);
                Battle_FinishTurn();
                Battle_SetSubstateFlag();
                HandleFlag4000AnimEffect(gOpponentPlayer);
                Dialog_SetMode(1);
                sp2C = GetOpponentAnimScriptId(gOpponentPlayer);
                InitDualTargetActionScript(sp34->unk_5A, gCurrentPlayer, gOpponentPlayer, sp2C, GetOpponentAnimScriptParam(gOpponentPlayer));
                ApplyAnimEffectToOpponent(gOpponentPlayer, 0x10, 0);
            }
            break;

        case 1:
            Battle_ProcessOpponentAction(arg0, gOpponentPlayer);
            gPlayer0ReadyFlag = UpdatePokemonHP(gOpponentPlayer);
            gPlayer1ReadyFlag = UpdatePokemonHP(gCurrentPlayer);
            if ((Pokemon_CheckAnimStateC(gOpponentPlayer) != 0) || (Battle_WaitForAnimation(0x5A) != 0)) {
                Battle_CheckAndResetIfBothReady(arg0, &gPlayer0ReadyFlag, &gPlayer1ReadyFlag);
            }
            break;
    }
}

void Battle_OpponentTurnPhase2(CameraStruct* arg0) {
    PokemonAudioInfo* sp24 = &gOpponentPlayer->unk_654.unk_38;
    UNUSED s32 pad;
    s32 sp1C;
    s32 temp_v0;
    s32 var_a0;

    switch (gBattleState.unk_00->unk_3C) {
        case 0:
            if (HandlePlayerActionFlag800Alt(gOpponentPlayer) == 0) {
                Player_HandleSpecialAnimation(gCurrentPlayer);
                Dialog_SetMode(1);
                Battle_FinishTurn();
                Battle_SetSubstateFlag();
                Battle_ApplyOpponentAnimEffects(gOpponentPlayer);
                if (gBattleState.unk_00->unk_1A == 3) {
                    ExecuteAnimStateHandlers(gCurrentPlayer, 0xB);
                } else {
                    ExecuteAnimStateHandlers(gCurrentPlayer, 4);
                }
                Battle_QueueOpponentMove(gOpponentPlayer, arg0, 0);
                Battle_ApplyAnimStateEffects(gOpponentPlayer);
                HandleFlag4000AnimEffect(gOpponentPlayer);
                ResumeMoveAnimationIfNotTriggered(gOpponentPlayer);
            }
            break;

        case 1:
            if (Battle_WaitForAnimation(5) != 0) {
                Battle_ApplyStatusEffectAnimation(gCurrentPlayer);
                gBattleState.unk_00->unk_3C++;
            }
            break;

        case 2:
            Battle_ResetSubstate();
            gPlayer0ReadyFlag = UpdatePokemonHP(gOpponentPlayer);
            gPlayer1ReadyFlag = UpdatePokemonHP(gCurrentPlayer);
            if (sp24->unk_0C != 0) {
                if (Pokemon_CheckAnimStateC(gOpponentPlayer) != 0) {
                    gBattleState.unk_00->unk_3C = 4;
                } else if (CanAnimChannelA80Proceed(gOpponentPlayer, 2) != 0) {
                    gBattleState.unk_00->unk_3C = 5;
                } else if (Battle_ProcessOpponentAction(arg0, gOpponentPlayer) != 0) {
                    gBattleState.unk_00->unk_3C = 3;
                }
            } else if (Battle_ProcessOpponentAction(arg0, gOpponentPlayer) != 0) {
                gBattleState.unk_00->unk_3C = 4;
            }
            break;

        case 3:
            gPlayer0ReadyFlag = UpdatePokemonHP(gOpponentPlayer);
            gPlayer1ReadyFlag = UpdatePokemonHP(gCurrentPlayer);
            Battle_ProcessOpponentAction(arg0, gOpponentPlayer);
            if (Pokemon_CheckAnimStateC(gOpponentPlayer) != 0) {
                gBattleState.unk_00->unk_3C++;
            } else if (CanAnimChannelA80Proceed(gOpponentPlayer, 0xF) != 0) {
                gBattleState.unk_00->unk_3C++;
            }
            break;

        case 4:
            gPlayer0ReadyFlag = UpdatePokemonHP(gOpponentPlayer);
            gPlayer1ReadyFlag = UpdatePokemonHP(gCurrentPlayer);
            temp_v0 = Battle_ProcessOpponentAction(arg0, gOpponentPlayer);
            if ((gPlayer0ReadyFlag == 1) && (gPlayer1ReadyFlag == 1) && (temp_v0 != 0) && (Battle_WaitForAnimation(0xF) != 0)) {
                gBattleState.unk_00->unk_3C = 6;
            }
            break;

        case 5:
            gPlayer0ReadyFlag = UpdatePokemonHP(gOpponentPlayer);
            gPlayer1ReadyFlag = UpdatePokemonHP(gCurrentPlayer);
            sp1C = Battle_ProcessOpponentAction(arg0, gOpponentPlayer);
            if ((Player_IsSpecialCondition(gCurrentPlayer) != 0) && ((gAnimTimer < 0xA) || (gSpecialFlag != 0)) &&
                !(sp24->unk_15 & 0x20)) {
                var_a0 = 0x5A;
            } else {
                var_a0 = 0xF;
            }

            if ((gPlayer0ReadyFlag == 1) && (gPlayer1ReadyFlag == 1) && (sp1C != 0) && (Battle_WaitForAnimation(var_a0) != 0)) {
                gBattleState.unk_00->unk_3C++;
            }
            break;

        case 6:
            if (HandlePlayerActionFlag1000(gOpponentPlayer) == 0) {
                gPlayer0ReadyFlag = UpdatePokemonHP(gOpponentPlayer);
                gPlayer1ReadyFlag = UpdatePokemonHP(gCurrentPlayer);
                Battle_ProcessOpponentAction(arg0, gOpponentPlayer);
                Battle_CheckAndResetIfBothReady(arg0, &gPlayer0ReadyFlag, &gPlayer1ReadyFlag);
            }
            break;
    }
}

void func_84324404(void) {
}

void func_8432440C(void) {
}

void Battle_OpponentAnimationStep(CameraStruct* arg0) {
    PokemonAudioInfo* sp24 = &gCurrentPlayer->unk_654.unk_38;
    unk_BattleAnimDataEntry* temp_v1 = &gAnimDataByPlayer[IsPrimaryEntity(gOpponentPlayer)]->unk_000[sp24->unk_5A - 1];
    volatile s32 sp1C;
    s32 temp_v0_2;

    if (gOpponentPlayer->unk_000.unk_01A == 0x98) {
        sp1C = 0xF;
    } else if (temp_v1->unk_0A == 0xFF) {
        sp1C = gCurrentPlayer->unk_000.unk_040.unk_04->unk_0A - temp_v1->unk_06;
    } else {
        sp1C = temp_v1->unk_0A - temp_v1->unk_06;
    }

    switch (gBattleState.unk_00->unk_3C) {
        case 0:
            if (HandlePlayerActionFlag800Alt(gOpponentPlayer) == 0) {
                Battle_ResetSubstate();
                Battle_ApplyOpponentAnimEffects(gOpponentPlayer);
                ExecuteAnimStateHandlers(gCurrentPlayer, 4);
                gCurrentMoveIndex--;
                Battle_QueueOpponentMove(gOpponentPlayer, arg0, gCurrentMoveIndex + 1);
                if (gCurrentMoveIndex < 0) {
                    Battle_QueueOpponentMove(gOpponentPlayer, arg0, gCurrentMoveIndex + 1);
                    Battle_ProcessOpponentAction(arg0, gOpponentPlayer);
                    Battle_ApplyAnimStateEffects(gOpponentPlayer);
                    Battle_FinishTurn();
                    gBattleState.unk_00->unk_3C = 2;
                    HandleFlag4000AnimEffect(gOpponentPlayer);
                    Dialog_SetMode(1);
                } else {
                    gBattleState.unk_00->unk_3C++;
                }
            }
            break;

        case 1:
            Battle_AdvanceCameraTimeline(arg0, gOpponentPlayer);
            if (Battle_WaitForAnimation(sp1C) != 0) {
                ResetSoundDurations();
                Battle_SetAnimChannelFlag(1);
                gBattleState.unk_00->unk_3C = 0;
            }
            break;

        case 2:
            gPlayer0ReadyFlag = UpdatePokemonHP(gOpponentPlayer);
            gPlayer1ReadyFlag = UpdatePokemonHP(gCurrentPlayer);

            if (sp24->unk_0C != 0) {
                if (Pokemon_CheckAnimStateC(gOpponentPlayer) != 0) {
                    gBattleState.unk_00->unk_3C = 5;
                }

                if (CanAnimChannelA80Proceed(gOpponentPlayer, 0xF) != 0) {
                    gBattleState.unk_00->unk_3C = 5;
                }

                if (Battle_ProcessOpponentAction(arg0, gOpponentPlayer) != 0) {
                    gBattleState.unk_00->unk_3C = 4;
                }
            } else if (Battle_ProcessOpponentAction(arg0, gOpponentPlayer) != 0) {
                Battle_FinishTurn();
                gBattleState.unk_00->unk_3C = 5;
            }
            break;

        case 3:
            gPlayer0ReadyFlag = UpdatePokemonHP(gOpponentPlayer);
            gPlayer1ReadyFlag = UpdatePokemonHP(gCurrentPlayer);

            if (Pokemon_CheckAnimStateC(gOpponentPlayer) != 0) {
                gBattleState.unk_00->unk_3C = 5;
            }

            if (Battle_ProcessOpponentAction(arg0, gOpponentPlayer) != 0) {
                gBattleState.unk_00->unk_3C = 9;
            }
            break;

        case 4:
            gPlayer0ReadyFlag = UpdatePokemonHP(gOpponentPlayer);
            gPlayer1ReadyFlag = UpdatePokemonHP(gCurrentPlayer);

            if (Pokemon_CheckAnimStateC(gOpponentPlayer) != 0) {
                gBattleState.unk_00->unk_3C = 5;
            }

            Battle_ProcessOpponentAction(arg0, gOpponentPlayer);

            if (CanAnimChannelA80Proceed(gOpponentPlayer, 0xF) != 0) {
                gBattleState.unk_00->unk_3C++;
            }
            break;

        case 5:
            gPlayer0ReadyFlag = UpdatePokemonHP(gOpponentPlayer);
            gPlayer1ReadyFlag = UpdatePokemonHP(gCurrentPlayer);
            temp_v0_2 = Battle_ProcessOpponentAction(arg0, gOpponentPlayer);
            if ((gPlayer0ReadyFlag == 1) && (gPlayer1ReadyFlag == 1) && (temp_v0_2 != 0) && (Battle_WaitForAnimation(0xF) != 0)) {
                gBattleState.unk_00->unk_3C++;
            }
            break;

        case 6:
            if (HandlePlayerActionFlag1000(gOpponentPlayer) == 0) {
                gPlayer0ReadyFlag = UpdatePokemonHP(gOpponentPlayer);
                gPlayer1ReadyFlag = UpdatePokemonHP(gCurrentPlayer);
                Battle_ProcessOpponentAction(arg0, gOpponentPlayer);
                Battle_CheckAndResetIfBothReady(arg0, &gPlayer0ReadyFlag, &gPlayer1ReadyFlag);
            }
            break;
    }
}

void Battle_HandleBattleStateTransitions(CameraStruct* arg0) {
    Battle_SetCameraFOV30(arg0);
    Battle_ApplyAnimStateEffects(sActivePokemon[!gBattleState.unk_00->unk_2C]);
    if (gBattleState.unk_00->unk_48 == 0x16) {
        Battle_OpponentTurnPhase0(arg0);
    } else if (gBattleState.unk_00->unk_48 == 0x20) {
        BattleScene_RunMoveEffectEndHpTransition(arg0);
    } else if (gBattleState.unk_00->unk_48 == 0x1A) {
        Battle_OpponentTurnPhase1(arg0);
    } else if (gBattleState.unk_00->unk_1A == 1) {
        Battle_OpponentAnimationStep(arg0);
    } else {
        Battle_OpponentTurnPhase2(arg0);
    }
}

void Battle_StateMachineStepA(CameraStruct* arg0) {
    switch (gBattleState.unk_00->unk_20) {
        case 0:
            Battle_MainStep(arg0);
            break;

        case 1:
            Battle_DispatchMoveHandler(arg0);
            break;

        case 2:
            Battle_HandleBattleStateTransitions(arg0);
            break;
    }
}

void Battle_StateMachineStepB(CameraStruct* arg0) {
    switch (gBattleState.unk_00->unk_20) {
        case 0:
            Battle_MainStep(arg0);
            break;

        case 1:
            Battle_DispatchMoveHandler(arg0);
            break;

        case 2:
            Battle_HandleBattleStateTransitions(arg0);
            break;
    }
}

s32 Battle_FinalPhaseHandler(void) {
    Battle_AdjustCameraForMove(gBattleState.unk_00->unk_DC, 0);

    if (Battle_WaitForAnimation(GetAnimDataField0FOrDefault(gCurrentPlayer)) == 0) {
        return 0;
    }

    if ((gBattleState.unk_00->unk_48 != 0x1E) && (gBattleState.unk_00->unk_48 != 0x27)) {
        Dialog_SetMode(3);
    }

    if (gBattleState.unk_00->unk_48 == 0x1B) {
        QueuePlayerDefeatMessage(GetPlayerDefeatMessageId(gCurrentPlayer));
    }

    switch (gBattleState.unk_00->unk_48) {
        case 7:
            return Battle_SetPhaseAndReset(7);

        case 21:
            return Battle_SetPhaseAndReset(7);

        case 39:
            return Battle_SetPhaseAndReset(7);

        case 27:
            return Battle_SetPhaseAndReset(0x1B);

        case 30:
            return Battle_SetPhaseAndReset(0x1E);

        case 28:
            return Battle_SetPhaseAndReset(0x1C);

        case 15:
            return Battle_SetPhaseAndReset(0xF);

        case 25:
            return Battle_SetPhaseAndReset(0x19);

        case 29:
            return Battle_SetPhaseAndReset(0x1D);

        case 38:
            return Battle_SetPhaseAndReset(0x26);

        case 12:
            return Battle_SetPhaseAndReset(0xC);

        case 13:
            return Battle_SetPhaseAndReset(0xD);

        case 14:
            return Battle_SetPhaseAndReset(0xE);

        case 17:
            return Battle_SetPhaseAndReset(0x11);

        case 31:
            return Battle_SetPhaseAndReset(0x1F);
    }

    return 0;
}

void Battle_PlayerMoveAnimation(CameraStruct* arg0) {
    PokemonAudioInfo* sp1C = &gCurrentPlayer->unk_654.unk_38;
    unk_BattleAnimDataEntry* sp18 = &gAnimDataByPlayer[IsPrimaryEntity(gCurrentPlayer)]->unk_000[sp1C->unk_5A - 1];

    switch (gBattleState.unk_00->unk_20) {
        case 0:
            Battle_StoreCameraFOV(arg0);
            Battle_ChooseMoveByContext(arg0, 0);
            Battle_FinishTurn();
            Battle_AdvanceTurnState();
            if (sp18->unk_04 < 0x15) {
                Battle_ApplyAnimStateEffects(gCurrentPlayer);
            }
            gBattleState.unk_00->unk_20++;
            break;

        case 1:
            Battle_AdjustCameraForMove(arg0, 1);
            if (gCurrentPlayer->unk_4C4 == (sp18->unk_04 + 1)) {
                Battle_ApplyAnimStateEffects(gCurrentPlayer);
            }

            if (gCurrentPlayer->unk_4C4 >= (sp18->unk_04 + 0xA)) {
                gPlayer0ReadyFlag = UpdatePokemonHP(sActivePokemon[gBattleState.unk_00->unk_2C]);
                gPlayer1ReadyFlag = UpdatePokemonHP(sActivePokemon[!gBattleState.unk_00->unk_2C]);
            }

            if ((gCurrentPlayer->unk_4C4 == (sp18->unk_04 + 0x12)) && (sp1C->unk_5A == 0x64)) {
                Dialog_SetMode(0xF);
            }

            if (EvaluateAnimStateAgainstBattle(gCurrentPlayer, 0x3C) != 0) {
                Battle_FinishTurn();
                gBattleState.unk_00->unk_20++;
            }
            break;

        case 2:
            if (gCurrentPlayer->unk_4C4 == (sp18->unk_04 + 1)) {
                Battle_ApplyAnimStateEffects(gCurrentPlayer);
            }
            Battle_AdjustCameraForMove(arg0, 1);
            gPlayer0ReadyFlag = UpdatePokemonHP(sActivePokemon[gBattleState.unk_00->unk_2C]);
            gPlayer1ReadyFlag = UpdatePokemonHP(sActivePokemon[!gBattleState.unk_00->unk_2C]);
            if ((gPlayer0ReadyFlag == 1) && (gPlayer1ReadyFlag == 1) && (Battle_WaitForAnimation(0xF) != 0)) {
                if ((gOpponentPlayer->unk_654.unk_38.unk_5A & 0xF0) == 0xF0) {
                    gBattleState.unk_00->unk_34 = 3;
                }
                Battle_FinishTurn();
                Battle_ResetSubstate();
                Battle_MainLoopStep(arg0);
            }
            break;
    }
}

void Battle_PlayerMoveAnimationAlt(CameraStruct* arg0) {
    switch (gBattleState.unk_00->unk_20) {
        case 0:
            Battle_StoreCameraFOV(arg0);
            Battle_ApplyPlayerAnimEffects(arg0, gCurrentPlayer);
            ConfigureCameraForModel(gCurrentPlayer, arg0);
            Battle_ApplyAnimStateEffects(gCurrentPlayer);
            Battle_FinishTurn();
            Battle_AdvanceTurnState();
            gBattleState.unk_00->unk_20++;
            break;

        case 1:
            if (EvaluateAnimStateAgainstBattle(gCurrentPlayer, 0x3C) != 0) {
                gBattleState.unk_00->unk_20 += 1;
            }
            break;

        case 2:
            gPlayer0ReadyFlag = UpdatePokemonHP(sActivePokemon[gBattleState.unk_00->unk_2C]);
            gPlayer1ReadyFlag = UpdatePokemonHP(sActivePokemon[!gBattleState.unk_00->unk_2C]);
            if ((gOpponentPlayer->unk_654.unk_38.unk_5A & 0xF0) == 0xF0) {
                gBattleState.unk_00->unk_34 = 3;
            }
            Battle_FinishTurn();
            Battle_ResetSubstate();
            Battle_MainLoopStep(arg0);
            break;
    }
}

void Battle_PlayerMoveSequence(CameraStruct* arg0) {
    switch (gBattleState.unk_00->unk_20) {
        case 0:
            Battle_StoreCameraFOV(arg0);
            Battle_ApplyAnimStateEffects(gCurrentPlayer);
            Battle_ChooseMoveByContext(arg0, 0);
            Battle_FinishTurn();
            gBattleState.unk_00->unk_20++;
            break;

        case 1:
            Battle_AdjustCameraForMove(arg0, 1);
            if (Battle_WaitForAnimation(0x28) != 0) {
                gBattleState.unk_00->unk_20 += 1;
            }
            break;

        case 2:
            Battle_AdjustCameraForMove(arg0, 1);
            gPlayer0ReadyFlag = UpdatePokemonHP(sActivePokemon[gBattleState.unk_00->unk_2C]);
            gPlayer1ReadyFlag = UpdatePokemonHP(sActivePokemon[!gBattleState.unk_00->unk_2C]);
            if ((gOpponentPlayer->unk_654.unk_38.unk_5A & 0xF0) == 0xF0) {
                gBattleState.unk_00->unk_34 = 3;
            }
            Battle_FinishTurn();
            Battle_ResetSubstate();
            Battle_MainLoopStep(arg0);
            break;
    }
}

void Battle_PlayerOpponentInteraction(CameraStruct* arg0) {
    PokemonAudioInfo* sp1C = &gOpponentPlayer->unk_654.unk_38;

    switch (gBattleState.unk_00->unk_20) {
        case 0:
            ClearEntityAnimFlags(gCurrentPlayer, 0x1800);
            Battle_StoreCameraFOV(arg0);
            Battle_FinishTurn();
            Battle_ChooseMoveByContext(arg0, 0);
            Battle_ApplyAnimStateEffects(gCurrentPlayer);
            Battle_FinishTurn();
            gBattleState.unk_00->unk_20++;
            break;

        case 1:
            Battle_AdjustCameraForMove(arg0, 1);
            if (EvaluateAnimStateAgainstBattle(gCurrentPlayer, 0x3C) != 0) {
                Battle_FinishTurn();
                gBattleState.unk_00->unk_20++;
            }
            break;

        case 2:
            if (HandlePlayerActionFlag800Alt(gOpponentPlayer) == 0) {
                Battle_SetAnimChannelFlag(1);
                ResetSoundDurations();
                Battle_QueueOpponentMove(gOpponentPlayer, arg0, Math_RandomU16Scaled(2));
                ExecuteAnimStateHandlers(gCurrentPlayer, 4);
                Battle_FinishTurn();
                gBattleState.unk_00->unk_20++;
            }
            break;

        case 3:
            if (HandlePlayerActionFlag1000(gOpponentPlayer) == 0) {
                Battle_AdvanceCameraTimeline(arg0, gOpponentPlayer);
                if (gBattleState.unk_00->unk_14 == 0) {
                    Dialog_SetMode(1);
                }
                gPlayer0ReadyFlag = UpdatePokemonHP(sActivePokemon[gBattleState.unk_00->unk_2C]);
                gPlayer1ReadyFlag = UpdatePokemonHP(sActivePokemon[!gBattleState.unk_00->unk_2C]);
                if (Battle_WaitForAnimation(0x32) != 0) {
                    gBattleState.unk_00->unk_20 += 1;
                }
                if (Pokemon_CheckAnimStateC(gOpponentPlayer) != 0) {
                    Battle_FinishTurn();
                    gBattleState.unk_00->unk_20++;
                }
            }
            break;

        case 4:
            Battle_AdvanceCameraTimeline(arg0, gOpponentPlayer);
            gPlayer0ReadyFlag = UpdatePokemonHP(sActivePokemon[gBattleState.unk_00->unk_2C]);
            gPlayer1ReadyFlag = UpdatePokemonHP(sActivePokemon[!gBattleState.unk_00->unk_2C]);
            if ((gPlayer1ReadyFlag == 1) && (gPlayer0ReadyFlag == 1)) {
                if (sp1C->unk_0C != 0) {
                    Battle_SetAnimChannelFlag(1);
                    ResetSoundDurations();
                    Battle_PlayMoveEffect(gCurrentPlayer, arg0, 3);
                    gBattleState.unk_00->unk_20++;
                } else {
                    if ((gOpponentPlayer->unk_654.unk_38.unk_5A & 0xF0) == 0xF0) {
                        gBattleState.unk_00->unk_34 = 3;
                    }
                    Battle_FinishTurn();
                    Battle_ResetSubstate();
                    Battle_SetPhase(arg0, 5);
                }
            }
            break;

        case 5:
            Battle_PlayMoveEffect(gCurrentPlayer, arg0, 3);
            gPlayer0ReadyFlag = UpdatePokemonHP(sActivePokemon[gBattleState.unk_00->unk_2C]);
            gPlayer1ReadyFlag = UpdatePokemonHP(sActivePokemon[!gBattleState.unk_00->unk_2C]);
            if ((gOpponentPlayer->unk_654.unk_38.unk_5A & 0xF0) == 0xF0) {
                gBattleState.unk_00->unk_34 = 3;
            }
            Battle_FinishTurn();
            Battle_ResetSubstate();
            Battle_ProcessReadyState(arg0);
            break;
    }
}

void BattleScene_Phase28(CameraStruct* arg0) {
    switch (gBattleState.unk_00->unk_20) {
        case 0:
            Battle_StoreCameraFOV(arg0);
            Battle_ApplyAnimStateEffects(gCurrentPlayer);
            Battle_PlayMoveEffect(gCurrentPlayer, arg0, 3);
            Battle_FinishTurn();
            gBattleState.unk_00->unk_20 += 1;
            break;

        case 1:
            if (Battle_WaitForAnimation(0x28) != 0) {
                gBattleState.unk_00->unk_20 += 1;
            }
            break;

        case 2:
            gPlayer0ReadyFlag = UpdatePokemonHP(sActivePokemon[gBattleState.unk_00->unk_2C]);
            gPlayer1ReadyFlag = UpdatePokemonHP(sActivePokemon[!gBattleState.unk_00->unk_2C]);
            if ((gOpponentPlayer->unk_654.unk_38.unk_5A & 0xF0) == 0xF0) {
                gBattleState.unk_00->unk_34 = 3;
            }
            Battle_FinishTurn();
            Battle_ResetSubstate();
            Battle_MainLoopStep(arg0);
            break;
    }
}

void BattleScene_Phase15(CameraStruct* arg0) {
    UNUSED s32 pad[3];
    PokemonAudioInfo* sp30 = &gCurrentPlayer->unk_654.unk_38;
    PokemonAudioInfo* sp2C = &gOpponentPlayer->unk_654.unk_38;
    unk_BattlePlayerAnimState* sp28 = &gCurrentPlayer->unk_654;
    unk_BattlePlayerAnimState* sp24 = &gOpponentPlayer->unk_654;

    switch (gBattleState.unk_00->unk_20) {
        case 0:
            Battle_ChooseMoveByContext(arg0, 0);
            Camera_SmoothPanToEntity(arg0, gCurrentPlayer);
            if (sp30->unk_4D & 0x10) {
                if (sp2C->unk_4E & 8) {
                    sp28->unk_BC = gCurrentPlayer->unk_720->unk_02 = sp24->unk_BE;
                } else if (gOpponentPlayer->unk_720->unk_02 == 0x98) {
                    sp28->unk_BC = gCurrentPlayer->unk_720->unk_02 = sp2C->unk_0B;
                } else {
                    sp28->unk_BC = gCurrentPlayer->unk_720->unk_02 = gOpponentPlayer->unk_720->unk_02;
                }
            } else if (sp2C->unk_4E & 8) {
                gCurrentPlayer->unk_720->unk_02 = sp24->unk_BE;
            } else if (gOpponentPlayer->unk_720->unk_02 == 0x98) {
                gCurrentPlayer->unk_720->unk_02 = sp2C->unk_0B;
            } else {
                gCurrentPlayer->unk_720->unk_02 = gOpponentPlayer->unk_720->unk_02;
            }
            gCurrentPlayer->unk_720->unk_04 = &gCurrentPlayer->unk_724->unk_01C[gCurrentPlayer->unk_654.unk_08];
            gCurrentPlayer->unk_720->unk_00 |= 0x80;
            gBattleState.unk_00->unk_20 += 1;
            break;

        case 1:
            Camera_SmoothPanToEntity(arg0, gCurrentPlayer);
            if (gCurrentPlayer->unk_720->unk_00 & 0x10) {
                gCurrentPlayer->unk_720->unk_00 &= ~0x90;
                Pokemon_ResetToDefaultState(gCurrentPlayer);
                RefreshPokemonTransform(gCurrentPlayer);
                AnimChannel_StartMoveAction(gCurrentPlayer, sp30->unk_5A);
                TriggerMoveEvent(gCurrentPlayer, sp30, 0);
                gBattleState.unk_00->unk_20 += 1;
            }
            break;

        case 2:
            Camera_SmoothPanToEntity(arg0, gCurrentPlayer);
            TriggerMoveEvent(gCurrentPlayer, sp30, 0);
            ExecuteAnimStateHandlers(gCurrentPlayer, 0x12);
            gBattleState.unk_00->unk_20 += 1;
            break;

        case 3:
            Camera_SmoothPanToEntity(arg0, gCurrentPlayer);
            gCurrentPlayer->unk_728.unk_168->unk_00.unk_01 |= 1;
            gCurrentPlayer->unk_728.unk_000.unk_000.unk_01 |= 1;
            TriggerPokemonAnimAndAction(gCurrentPlayer);
            if (CanAnimProceed(gCurrentPlayer, 0x32) != 0) {
                Battle_ResetSubstate();
                Battle_UpdateHPAndProceed(arg0);
            }
            break;
    }
}

void BattleScene_Phase25(CameraStruct* arg0) {
    PokemonAudioInfo* sp1C = &sActivePokemon[gBattleState.unk_00->unk_2C]->unk_654.unk_38;
    unk_BattlePlayerAnimState* sp18 = &sActivePokemon[gBattleState.unk_00->unk_2C]->unk_654;

    switch (gBattleState.unk_00->unk_20) {
        case 0:
            Battle_StoreCameraFOV(arg0);
            AnimChannel_StartMoveAction(gCurrentPlayer, sp1C->unk_5A);
            Battle_ChooseMoveByContext(arg0, 0);
            if (!(sp18->unk_34 & 0x800)) {
                AnimChannel_SetFlags28(gCurrentPlayer);
            }
            gBattleState.unk_00->unk_20 += 1;
            break;

        case 1:
            Battle_AdjustCameraForMove(arg0, 0);
            if (!(sp18->unk_34 & 0x800)) {
                Pokemon_ClearTransformFlag(gCurrentPlayer);
            }
            if (AnimChannel_GetFlagsFF0(gCurrentPlayer) == 0) {
                TriggerMoveEvent(gCurrentPlayer, sp1C, 0);
                Battle_PlayMoveEffect(gCurrentPlayer, arg0, 3);
                Battle_FinishTurn();
                gBattleState.unk_00->unk_20 += 1;
            }
            break;

        case 2:
            Battle_PlayMoveEffect(gCurrentPlayer, arg0, 3);
            gPlayer0ReadyFlag = UpdatePokemonHP(sActivePokemon[gBattleState.unk_00->unk_2C]);
            gPlayer1ReadyFlag = UpdatePokemonHP(sActivePokemon[!gBattleState.unk_00->unk_2C]);
            if (Battle_WaitForAnimation(0x2E) != 0) {
                gBattleState.unk_00->unk_20 += 1;
            }
            break;

        case 3:
            if (!(sp18->unk_34 & 0x800)) {
                SetEntityAnimFlags(gCurrentPlayer, 0x800);
            }
            gPlayer0ReadyFlag = UpdatePokemonHP(sActivePokemon[gBattleState.unk_00->unk_2C]);
            gPlayer1ReadyFlag = UpdatePokemonHP(sActivePokemon[!gBattleState.unk_00->unk_2C]);
            if ((gOpponentPlayer->unk_654.unk_38.unk_5A & 0xF0) == 0xF0) {
                gBattleState.unk_00->unk_34 = 3;
            }
            Battle_ResetSubstate();
            Battle_MainLoopStep(arg0);
            break;
    }
}

s32 StartMoveAnimationAndStatus(unk_BattlePlayerEntity* arg0) {
    StartMoveAnimation(arg0);
    ProcessStatusEffectEnd(arg0);
    Battle_ApplyAnimStateEffects(arg0);
}

void BattleScene_Phase29(CameraStruct* arg0) {
    switch (gBattleState.unk_00->unk_20) {
        case 0:
            Battle_StoreCameraFOV(arg0);
            Battle_ApplyAnimStateEffects(gCurrentPlayer);
            Battle_ChooseMoveByContext(arg0, 0);
            Battle_FinishTurn();
            Battle_AdvanceTurnState();
            gBattleState.unk_00->unk_20 += 1;
            break;

        case 1:
            Battle_AdjustCameraForMove(arg0, 1);
            if (EvaluateAnimStateAgainstBattle(gCurrentPlayer, 0x3C) != 0) {
                StartMoveAnimationAndStatus(gOpponentPlayer);
                gBattleState.unk_00->unk_20 += 1;
            }
            break;

        case 2:
            Battle_AdjustCameraForMove(arg0, 1);
            gPlayer0ReadyFlag = UpdatePokemonHP(sActivePokemon[gBattleState.unk_00->unk_2C]);
            gPlayer1ReadyFlag = UpdatePokemonHP(sActivePokemon[!gBattleState.unk_00->unk_2C]);
            if ((gOpponentPlayer->unk_654.unk_38.unk_5A & 0xF0) == 0xF0) {
                gBattleState.unk_00->unk_34 = 3;
            }
            Vec3f_Set(&gCurrentPlayer->unk_000.unk_030, 1.0f, 1.0f, 1.0f);
            Vec3f_Set(&gOpponentPlayer->unk_000.unk_030, 1.0f, 1.0f, 1.0f);
            Battle_FinishTurn();
            Battle_ResetSubstate();
            Battle_MainLoopStep(arg0);
            break;
    }
}

void Battle_PlayerSwitchIn(CameraStruct* arg0) {
    unk_BattleAnimDataEntry* sp4C = &gAnimDataByPlayer[gBattleState.unk_00->unk_2C]->unk_B00;
    UNUSED s32 pad;
    Vec3f sp3C;

    switch (gBattleState.unk_00->unk_20) {
        case 0:
            Battle_FinishTurn();
            Battle_ClearSubstateFlag();
            Battle_PlayMoveEffect(gCurrentPlayer, arg0, 3);
            Camera_SmoothFocusEntity(arg0, gCurrentPlayer);
            SetEntityAnimFlags(gCurrentPlayer, 0x200);
            gBattleState.unk_00->unk_20 += 1;
            break;

        case 1:
            if (gCurrentPlayer->unk_000.unk_024.y >= 100.0f) {
                GetEntityCenterPosition(gCurrentPlayer, &sp3C);
                sp3C.y += Battle_GetEntityHeight(gCurrentPlayer);
                gBattleUnusedFloat_84390208 = ClampScaledDistance(gCurrentPlayer, 3.0f, 500.0f);
                Camera_SetEyePositionOffset(arg0, sp3C, 0x11C6, GetPlayerSideYaw(gCurrentPlayer) - (gCurrentPlayer->unk_4B0 * 0x754E),
                              gBattleUnusedFloat_84390208, Battle_GetEntityHeight(gCurrentPlayer));
                Vec3f_Set(&sp3C, 0.0f, 200.0f, 0.0f);
                Vector_Copy(&arg0->unk_60.at, &sp3C);
                Battle_SetAnimChannelFlag(2);
                GraphNode_TriggerAction(&gCurrentPlayer->unk_000, sp4C->unk_00);
                arg0->unk_24.fovy = 60.0f;
                gBattleState.unk_00->unk_20 += 1;
            } else {
                Camera_SmoothFocusEntity(arg0, gCurrentPlayer);
            }
            break;

        case 2:
            Math_ExponentialApproach(&arg0->unk_24.fovy, 60.0f, 0.2f);
            if (gCurrentPlayer->unk_000.unk_024.y >= 200.0f) {
                gBattleState.unk_00->unk_20 += 1;
            }
            break;

        case 3:
            gPlayer0ReadyFlag = UpdatePokemonHP(sActivePokemon[gBattleState.unk_00->unk_2C]);
            gPlayer1ReadyFlag = UpdatePokemonHP(sActivePokemon[!gBattleState.unk_00->unk_2C]);
            if ((gPlayer0ReadyFlag == 1) && (gPlayer1ReadyFlag == 1) && (Battle_WaitFramesNonBlocking(0x1E) != 0)) {
                SetEntityAnimFlags(sActivePokemon[gBattleState.unk_00->unk_2C], 4);
                ClearGameStateFlag();
                Battle_FinishTurn();
                Battle_ResetSubstate();
                Battle_UpdateHPAndProceed(arg0);
            }
            break;
    }
}

void Battle_PlayerSwitchOut(CameraStruct* arg0) {
    UNUSED s32 pad;
    f32 sp28;
    UNUSED s16 pad2;
    u16 sp24 = gAnimFlagMask_5F92;

    switch (gBattleState.unk_00->unk_20) {
        case 0:
            Battle_StoreCameraFOV(arg0);
            Battle_FinishTurn();
            Battle_ClearSubstateFlag();
            Battle_PlayMoveEffect(gCurrentPlayer, arg0, 3);
            gBattleState.unk_00->unk_20 += 1;
            break;

        case 1:
            if (gCurrentPlayer->unk_4B8 == 2) {
                Camera_SmoothFocusEntityY(arg0, gCurrentPlayer);
                gCurrentPlayer->unk_000.unk_000.unk_02 &= 0xFFBF;
            }

            if ((gCurrentPlayer->unk_000.unk_01A == 0x32) || (gCurrentPlayer->unk_000.unk_01A == 0x33)) {
                if (CanAnimProceed(gCurrentPlayer, 0x1E) != 0) {
                    Dialog_Clear();
                    SetEntityAnimFlags(gCurrentPlayer, 0x4000);
                    gCurrentPlayer->unk_000.unk_000.unk_02 &= 0xFFDF;
                    gBattleState.unk_00->unk_20 += 1;
                }
            } else if (AnimChannel_GetFlagsFB0(gCurrentPlayer) == 0) {
                if (Array_ContainsValue(gCurrentPlayer->unk_000.unk_01A, (u8*)&sp24, 2) != 0) {
                    sp28 = 10.0f;
                } else {
                    sp28 = 3.5f;
                }

                if (gCurrentPlayer->unk_000.unk_024.y <= (-Battle_GetEntityHeight(gCurrentPlayer) * sp28)) {
                    SetEntityAnimFlags(gCurrentPlayer, 0x4000);
                    gCurrentPlayer->unk_000.unk_000.unk_02 &= 0xFFDF;
                    gBattleState.unk_00->unk_20 += 1;
                }
            }
            break;

        case 2:
            if ((gCurrentPlayer->unk_000.unk_01A != 0x32) && (gCurrentPlayer->unk_000.unk_01A != 0x33)) {
                gCurrentPlayer->unk_000.unk_000.unk_02 |= 0x40;
            }
            Camera_SmoothFocusEntityY(arg0, gCurrentPlayer);
            gPlayer0ReadyFlag = UpdatePokemonHP(sActivePokemon[gBattleState.unk_00->unk_2C]);
            gPlayer1ReadyFlag = UpdatePokemonHP(sActivePokemon[!gBattleState.unk_00->unk_2C]);
            Battle_ResetSubstate();
            Battle_MainLoopStep(arg0);
            break;
    }
}

void Battle_PlayerSwitchOutAlt(CameraStruct* arg0) {
    switch (gBattleState.unk_00->unk_20) {
        case 0:
            Battle_ChooseMoveByContext(arg0, 1);
            Battle_StoreCameraFOV(arg0);
            Battle_FinishTurn();
            Battle_AdvanceTurnState();
            Battle_ApplyAnimStateEffects(gCurrentPlayer);
            gBattleState.unk_00->unk_20 += 1;
            break;

        case 1:
            Battle_AdjustCameraForMove(arg0, 1);
            gPlayer0ReadyFlag = UpdatePokemonHP(sActivePokemon[gBattleState.unk_00->unk_2C]);
            gPlayer1ReadyFlag = UpdatePokemonHP(sActivePokemon[!gBattleState.unk_00->unk_2C]);
            if (EvaluateAnimStateWithAlternateChannel(gCurrentPlayer, 0x1E) != 0) {
                Battle_ResetSubstate();
                Battle_MainLoopStep(arg0);
            }
            break;
    }
}

void Battle_PlayerSwitchInAlt(CameraStruct* arg0) {
    unk_BattlePlayerAnimState* sp1C = &sActivePokemon[gBattleState.unk_00->unk_2C]->unk_654;

    switch (gBattleState.unk_00->unk_20) {
        case 0:
            Battle_FinishTurn();
            Battle_StoreCameraFOV(arg0);
            Battle_ApplyAnimStateEffects(gCurrentPlayer);
            if (!(sp1C->unk_34 & 2)) {
                Battle_ChooseMoveByContext(arg0, 0);
            }
            gBattleState.unk_00->unk_20 += 1;
            break;

        case 1:
            gPlayer0ReadyFlag = UpdatePokemonHP(sActivePokemon[gBattleState.unk_00->unk_2C]);
            gPlayer1ReadyFlag = UpdatePokemonHP(sActivePokemon[!gBattleState.unk_00->unk_2C]);
            if (Battle_WaitForAnimation(0x3C) != 0) {
                gBattleState.unk_00->unk_20 += 1;
            }
            break;

        case 2:
            gPlayer0ReadyFlag = UpdatePokemonHP(sActivePokemon[gBattleState.unk_00->unk_2C]);
            gPlayer1ReadyFlag = UpdatePokemonHP(sActivePokemon[!gBattleState.unk_00->unk_2C]);
            Battle_ResetSubstate();
            Battle_MainLoopStep(arg0);
            break;
    }
}

void Battle_OpponentActionInit(CameraStruct* arg0) {
    Battle_SetCameraFOV30(arg0);

    switch (gBattleState.unk_00->unk_20) {
        case 0:
            if (HandlePlayerActionFlag800Alt(gCurrentPlayer) == 0) {
                Dialog_SetMode(2);
                Battle_ApplyStatusEffectAnimation(gCurrentPlayer);
                gBattleState.unk_00->unk_20 += 1;
            }
            break;

        case 1:
            Battle_ResetSubstate();
            AnimStateQueue_ResetAll();
            ExecuteAnimStateHandlers(gCurrentPlayer, 0xF);
            Battle_QueueOpponentMove(gCurrentPlayer, arg0, 3);
            Battle_ApplyOpponentAnimEffects(gCurrentPlayer);
            Battle_ApplyAnimChannelEffect(8, gCurrentPlayer);
            gBattleState.unk_00->unk_20 += 1;
            break;

        case 2:
            gPlayer0ReadyFlag = UpdatePokemonHP(sActivePokemon[gBattleState.unk_00->unk_2C]);
            gPlayer1ReadyFlag = UpdatePokemonHP(sActivePokemon[!gBattleState.unk_00->unk_2C]);
            Battle_ProcessOpponentAction(arg0, gCurrentPlayer);
            if (Pokemon_CheckAnimState0(gCurrentPlayer) != 0) {
                gBattleState.unk_00->unk_20 += 1;
            } else if (CanAnimProceed(gCurrentPlayer, 0x32) != 0) {
                gBattleState.unk_00->unk_20 += 1;
            }
            break;

        case 3:
            Battle_ProcessOpponentAction(arg0, gCurrentPlayer);
            if (HandlePlayerActionFlag1000(gCurrentPlayer) == 0) {
                gBattleState.unk_00->unk_20 += 1;
            }
            break;

        case 4:
            gPlayer0ReadyFlag = UpdatePokemonHP(sActivePokemon[gBattleState.unk_00->unk_2C]);
            gPlayer1ReadyFlag = UpdatePokemonHP(sActivePokemon[!gBattleState.unk_00->unk_2C]);
            Battle_ProcessOpponentAction(arg0, gCurrentPlayer);
            Battle_ResetSubstate();
            Battle_UpdateHPAndProceed(arg0);
            break;
    }
}

void Battle_PlayerDefeatAnim(CameraStruct* arg0) {
    switch (gBattleState.unk_00->unk_20) {
        case 0:
            Battle_StoreCameraFOV(arg0);
            Battle_ApplyAnimStateEffects(gCurrentPlayer);
            gCurrentPlayer->unk_4C8 = 1;
            Battle_FinishTurn();
            gBattleState.unk_00->unk_20 += 1;
            break;

        case 1:
            gPlayer0ReadyFlag = UpdatePokemonHP(sActivePokemon[gBattleState.unk_00->unk_2C]);
            gPlayer1ReadyFlag = UpdatePokemonHP(sActivePokemon[!gBattleState.unk_00->unk_2C]);
            if (Battle_WaitForAnimation(0x3C) != 0) {
                gBattleState.unk_00->unk_20 += 1;
            }
            break;

        case 2:
            gPlayer0ReadyFlag = UpdatePokemonHP(sActivePokemon[gBattleState.unk_00->unk_2C]);
            gPlayer1ReadyFlag = UpdatePokemonHP(sActivePokemon[!gBattleState.unk_00->unk_2C]);
            Battle_ResetSubstate();
            Battle_MainLoopStep(arg0);
            break;
    }
}

void func_84326A70(void) {
}

void BattleScene_Phase4(UNUSED CameraStruct* arg0) {
    switch (gBattleState.unk_00->unk_20) {
        case 0:
            Battle_UpdateAfterTurn();

        case 1:
            break;
    }
}

void Battle_OpponentSwitchIn(CameraStruct* arg0) {
    UNUSED s32 pad;
    s32 idx = gBattleState.unk_00->unk_2C;
    unk_BattleAnimDataEntry* sp1C = &gAnimDataByPlayer[idx]->unk_A80;

    Battle_SetCameraFOV30(arg0);

    switch (gBattleState.unk_00->unk_20) {
        case 0:
            Battle_ResetSubstate();
            Dialog_SetMode(2);
            gBattleState.unk_00->unk_20 += 1;
            break;

        case 1:
            if (HandlePlayerActionFlag800Alt(gCurrentPlayer) == 0) {
                Battle_ApplyAnimEffect(gCurrentPlayer);
                Battle_SetAnimChannelFlag(1);
                ExecuteAnimStateHandlers(gCurrentPlayer, 0xF);
                Battle_QueueOpponentMove(gCurrentPlayer, arg0, 3);
                Battle_ApplyOpponentAnimEffects(gCurrentPlayer);
                Battle_ResetSubstate();
                GraphNode_TriggerAction(&gCurrentPlayer->unk_000, sp1C->unk_00);
                gBattleState.unk_00->unk_20 += 1;
            }
            break;

        case 2:
            if (Battle_WaitForAnimation(0x28) != 0) {
                gBattleState.unk_00->unk_20 += 1;
            }
            break;

        case 3:
            if (HandlePlayerActionFlag1000(gCurrentPlayer) == 0) {
                Dialog_Clear();
                gBattleState.unk_00->unk_20 += 1;
            }
            break;

        case 4:
            gPlayer0ReadyFlag = UpdatePokemonHP(sActivePokemon[gBattleState.unk_00->unk_2C]);
            gPlayer1ReadyFlag = UpdatePokemonHP(sActivePokemon[!gBattleState.unk_00->unk_2C]);
            if ((gPlayer0ReadyFlag != 0) && (gPlayer1ReadyFlag != 0)) {
                Battle_ResetSubstate();
                Battle_UpdateHPAndProceed(arg0);
            }
            break;
    }
}

void Battle_OpponentMoveAnimation(CameraStruct* arg0) {
    unk_BattlePlayerAnimState* sp1C = &gOpponentPlayer->unk_654;

    switch (gBattleState.unk_00->unk_20) {
        case 0:
            if (HandlePlayerActionFlag800Alt(gOpponentPlayer) == 0) {
                Dialog_SetMode(2);
                Player_HandleSpecialAnimation(gCurrentPlayer);
                Battle_SetCameraFOV30(arg0);
                Battle_SetAnimChannelFlag(1);

                if (sp1C->unk_34 & 0x200) {
                    Battle_QueueOpponentMove(gOpponentPlayer, arg0, gBattleUnusedInt_84390228 = 2);
                } else {
                    if (gOpponentPlayer->unk_000.unk_01A == 0xF) {
                        Battle_QueueOpponentMove(gOpponentPlayer, arg0, 0);
                    }
                    Battle_QueueOpponentMove(gOpponentPlayer, arg0, gBattleUnusedInt_84390228 = Math_RandomU16Scaled(2));
                }

                ExecuteAnimStateHandlers(gCurrentPlayer, 0xC);
                Battle_FinishTurn();
                SetParticleSpecialFlagFromGlobal();
                gBattleState.unk_00->unk_20 += 1;
                ApplyFlag4000EffectToEntity(gOpponentPlayer);
            }
            break;

        case 1:
            if ((gOpponentPlayer->unk_000.unk_01A == 0xF) && !(sp1C->unk_34 & 0x200)) {
                Battle_ProcessOpponentAction(arg0, gOpponentPlayer);
            }

            if (Battle_WaitForAnimation(0x32) != 0) {
                Dialog_Clear();
                Battle_ApplyStatusEffectAnimation(gCurrentPlayer);
                UpdateEntityStateByMode(gCurrentPlayer);
                Battle_ClearSubstateFlag();
                Battle_FinishTurn();
                Battle_ResetSubstate();
                Battle_UpdateHPAndProceed(arg0);
            }
            break;
    }
}

void Battle_OpponentDefeatAnim(CameraStruct* arg0) {
    PokemonAudioInfo* sp24 = &sActivePokemon[gBattleState.unk_00->unk_2C]->unk_654.unk_38;
    PokemonAudioInfo* sp20 = &sActivePokemon[!gBattleState.unk_00->unk_2C]->unk_654.unk_38;

    switch (gBattleState.unk_00->unk_20) {
        case 0:
            ClearAnimFlagIfState6A(gCurrentPlayer);
            Battle_SetCameraMoveSimple(arg0, sActivePokemon[gBattleState.unk_00->unk_2C]);
            Battle_ResetSubstate();
            UpdateEntityStateByMode(gCurrentPlayer);
            Battle_SetAnimChannelFlag(2);
            gBattleState.unk_00->unk_20 += 1;
            break;

        case 1:
            if (HandlePlayerActionFlag800(sActivePokemon[gBattleState.unk_00->unk_2C]) == 0) {
                Battle_ApplyAnimEffect(gCurrentPlayer);
                ResetSoundDurations();
                Battle_SetAnimChannelFlag(1);
                Battle_SetCameraMoveSimple(arg0, sActivePokemon[gBattleState.unk_00->unk_2C]);
                ExecuteAnimStateHandlers(sActivePokemon[gBattleState.unk_00->unk_2C], 0xD);

                if (sp24->unk_15 & 0x18) {
                    Dialog_SetMode(4);
                    sp24->unk_0C = sp24->unk_0E;
                    sp20->unk_0C = sp20->unk_0E;
                    if (sp24->unk_15 & 0x10) {
                        Battle_ApplyAnimChannelEffect(6, gCurrentPlayer);
                    } else {
                        Battle_ApplyAnimChannelEffect(5, gCurrentPlayer);
                    }
                    gBattleState.unk_00->unk_20 += 1;
                } else {
                    Dialog_SetMode(5);
                    Audio_PlaySoundEffect(0x22, 0, 0);
                    sp24->unk_0C = sp24->unk_10;
                    sp20->unk_0C = sp20->unk_10;
                    Battle_ApplyAnimChannelEffect(0xA, gCurrentPlayer);
                    Battle_FinishTurn();
                    gBattleState.unk_00->unk_20 = 3;
                }
            }
            break;

        case 2:
            Battle_SetCameraMoveSimple(arg0, sActivePokemon[gBattleState.unk_00->unk_2C]);
            gPlayer0ReadyFlag = UpdatePokemonHP(sActivePokemon[gBattleState.unk_00->unk_2C]);
            gPlayer1ReadyFlag = UpdatePokemonHP(sActivePokemon[!gBattleState.unk_00->unk_2C]);

            if ((gPlayer0ReadyFlag == 1) && (gPlayer1ReadyFlag == 1) && (Battle_WaitFramesNonBlocking(0x32) != 0)) {
                Battle_FinishTurn();
                if (GetCurrentHP(sActivePokemon[gBattleState.unk_00->unk_2C]) == 0) {
                    Battle_ClearSubstateFlag();
                    Battle_SetPhase(arg0, 5);
                    gBattleState.unk_00->unk_2C = !gBattleState.unk_00->unk_2C;
                } else if (sp24->unk_4D & 0x80) {
                    Battle_FinishTurn();
                    Audio_PlaySoundEffect(0x22, 0, 0);
                    sp24->unk_0C = sp24->unk_10;
                    sp20->unk_0C = sp20->unk_10;
                    Battle_ApplyAnimChannelEffect(0xA, gCurrentPlayer);
                    gBattleState.unk_00->unk_20 += 1;
                } else {
                    gBattleState.unk_00->unk_20 = 4;
                }
            }
            break;

        case 3:
            Battle_SetCameraMoveSimple(arg0, sActivePokemon[gBattleState.unk_00->unk_2C]);
            gPlayer0ReadyFlag = UpdatePokemonHP(sActivePokemon[gBattleState.unk_00->unk_2C]);
            gPlayer1ReadyFlag = UpdatePokemonHP(sActivePokemon[!gBattleState.unk_00->unk_2C]);

            if ((Battle_WaitFramesNonBlocking(0x32) != 0) && (gPlayer0ReadyFlag == 1) && (gPlayer1ReadyFlag == 1)) {
                gBattleState.unk_00->unk_20 += 1;
                Battle_FinishTurn();
            }
            break;

        case 4:
            if (HandlePlayerActionFlag1000(gOpponentPlayer) == 0) {
                gBattleState.unk_00->unk_20 += 1;
            }
            break;

        case 5:
            Battle_ResetSubstate();
            Battle_SetCameraMoveSimple(arg0, sActivePokemon[gBattleState.unk_00->unk_2C]);
            gPlayer0ReadyFlag = UpdatePokemonHP(sActivePokemon[gBattleState.unk_00->unk_2C]);
            gPlayer1ReadyFlag = UpdatePokemonHP(sActivePokemon[!gBattleState.unk_00->unk_2C]);
            Battle_ProcessReadyState(arg0);
            break;
    }
}

void Battle_OpponentSwitchOut(CameraStruct* arg0) {
    PokemonAudioInfo* sp1C = &sActivePokemon[gBattleState.unk_00->unk_2C]->unk_654.unk_38;
    PokemonAudioInfo* sp18 = &sActivePokemon[!gBattleState.unk_00->unk_2C]->unk_654.unk_38;

    switch (gBattleState.unk_00->unk_20) {
        case 0:
            UpdateEntityStateByMode(gCurrentPlayer);
            Battle_SetAnimChannelFlag(2);
            Camera_SetEntityWideView(arg0, sActivePokemon[gBattleState.unk_00->unk_2C]);
            gBattleState.unk_00->unk_20 += 1;
            break;

        case 1:
            if (HandlePlayerActionFlag800(sActivePokemon[gBattleState.unk_00->unk_2C]) == 0) {
                Battle_ApplyAnimEffect(gCurrentPlayer);
                ResetSoundDurations();
                Battle_SetAnimChannelFlag(1);
                Battle_ApplyAnimChannelEffect(9, gCurrentPlayer);
                Battle_FinishTurn();
                Camera_SetEntityWideView(arg0, sActivePokemon[gBattleState.unk_00->unk_2C]);
                sp1C->unk_0C = sp1C->unk_12;
                sp18->unk_0C = sp18->unk_12;
                Dialog_SetMode(6);
                gBattleState.unk_00->unk_20 += 1;
            }
            break;

        case 2:
            if (Camera_SmoothZoomIn(arg0, sActivePokemon[gBattleState.unk_00->unk_2C]) != 0) {
                Battle_QueueOpponentMove(gCurrentPlayer, arg0, 3);
                Pokemon_ResetAnimAndTrigger(gCurrentPlayer);
                PlayBattleSoundEffect(gCurrentPlayer, 0x1F);
                Battle_ApplyOpponentAnimEffects(gCurrentPlayer);
                gBattleState.unk_00->unk_20 += 1;
            }
            break;

        case 3:
            if (HandlePlayerActionFlag1000(gOpponentPlayer) == 0) {
                Battle_ProcessOpponentAction(arg0, gCurrentPlayer);
                gBattleState.unk_00->unk_20 += 1;
            }
            break;

        case 4:
            Battle_ResetSubstate();
            gPlayer0ReadyFlag = UpdatePokemonHP(sActivePokemon[gBattleState.unk_00->unk_2C]);
            gPlayer1ReadyFlag = UpdatePokemonHP(sActivePokemon[!gBattleState.unk_00->unk_2C]);
            Battle_ProcessOpponentAction(arg0, gCurrentPlayer);
            if ((gPlayer0ReadyFlag == 1) && (gPlayer1ReadyFlag == 1) && (Battle_WaitFramesNonBlocking(0x3C) != 0)) {
                Battle_UpdateHPAndProceed(arg0);
            }
            break;
    }
}

void Battle_OpponentDefeatAnimAlt(CameraStruct* arg0) {
    switch (gBattleState.unk_00->unk_20) {
        case 0:
            UpdateEntityStateByMode(gCurrentPlayer);
            if (HandlePlayerActionFlag800(sActivePokemon[gBattleState.unk_00->unk_2C]) == 0) {
                Battle_ApplyAnimEffect(gCurrentPlayer);
                ResetSoundDurations();
                Battle_SetAnimChannelFlag(1);
                Battle_FinishTurn();
                InitSingleEntityActionScript(3, gOpponentPlayer);
                Audio_PlaySoundEffect(0x23, 0, 0);
                Battle_SetCameraMoveSimple(arg0, gOpponentPlayer);
                Dialog_SetMode(7);
                gBattleState.unk_00->unk_20 += 1;
            }
            break;

        case 1:
            if (Battle_WaitForAnimation(0x37) != 0) {
                gBattleState.unk_00->unk_20 += 1;
            }

        case 2:
            if (Battle_WaitForAnimation(0x3C) != 0) {
                Battle_UpdateHPAndProceed(arg0);
            }
            break;
    }
}

void Battle_OpponentSwitchOutAlt(CameraStruct* arg0) {
    PokemonAudioInfo* sp24 = &sActivePokemon[gBattleState.unk_00->unk_2C]->unk_654.unk_38;
    PokemonAudioInfo* sp20 = &sActivePokemon[!gBattleState.unk_00->unk_2C]->unk_654.unk_38;

    switch (gBattleState.unk_00->unk_20) {
        case 0:
            UpdateEntityStateByMode(gCurrentPlayer);
            Battle_SetAnimChannelFlag(2);
            gBattleState.unk_00->unk_20 += 1;
            break;

        case 1:
            if (HandlePlayerActionFlag800(sActivePokemon[gBattleState.unk_00->unk_2C]) == 0) {
                Battle_ApplyAnimEffect(gCurrentPlayer);
                ResetSoundDurations();
                Battle_SetAnimChannelFlag(1);
                Battle_SetCameraMoveSimple(arg0, sActivePokemon[gBattleState.unk_00->unk_2C]);
                ExecuteAnimStateHandlers(sActivePokemon[gBattleState.unk_00->unk_2C], 0xD);

                if (sp24->unk_15 & 0x18) {
                    Dialog_SetMode(4);
                    sp24->unk_0C = sp24->unk_0E;
                    sp20->unk_0C = sp20->unk_0E;
                    if (sp24->unk_15 & 0x10) {
                        Battle_ApplyAnimChannelEffect(6, gCurrentPlayer);
                    } else {
                        Battle_ApplyAnimChannelEffect(5, gCurrentPlayer);
                    }
                    gBattleState.unk_00->unk_20 += 1;
                } else {
                    Dialog_SetMode(5);
                    sp24->unk_0C = sp24->unk_10;
                    sp20->unk_0C = sp20->unk_10;
                    Battle_ApplyAnimChannelEffect(0xA, gCurrentPlayer);
                    gBattleState.unk_00->unk_20 = 3;
                }
            }
            break;

        case 2:
            Battle_SetCameraMoveSimple(arg0, sActivePokemon[gBattleState.unk_00->unk_2C]);
            gPlayer0ReadyFlag = UpdatePokemonHP(sActivePokemon[gBattleState.unk_00->unk_2C]);
            gPlayer1ReadyFlag = UpdatePokemonHP(sActivePokemon[!gBattleState.unk_00->unk_2C]);
            if ((gPlayer0ReadyFlag == 1) && (gPlayer1ReadyFlag == 1) && (Battle_WaitFramesNonBlocking(0x32) != 0)) {
                Battle_FinishTurn();
                if (GetCurrentHP(sActivePokemon[gBattleState.unk_00->unk_2C]) == 0) {
                    Battle_ClearSubstateFlag();
                    Battle_SetPhase(arg0, 5);
                    gBattleState.unk_00->unk_2C = !gBattleState.unk_00->unk_2C;
                } else if (sp24->unk_4D & 0x80) {
                    Audio_PlaySoundEffect(0x22, 0, 0);
                    sp24->unk_0C = sp24->unk_10;
                    sp20->unk_0C = sp20->unk_10;
                    Battle_ApplyAnimChannelEffect(0xA, gCurrentPlayer);
                    gBattleState.unk_00->unk_20 += 1;
                } else {
                    gBattleState.unk_00->unk_20 = 4;
                }
            }
            break;

        case 3:
            Battle_SetCameraMoveSimple(arg0, sActivePokemon[gBattleState.unk_00->unk_2C]);
            gPlayer0ReadyFlag = UpdatePokemonHP(sActivePokemon[gBattleState.unk_00->unk_2C]);
            gPlayer1ReadyFlag = UpdatePokemonHP(sActivePokemon[!gBattleState.unk_00->unk_2C]);
            if ((Battle_WaitFramesNonBlocking(0x32) != 0) && (gPlayer0ReadyFlag == 1) && (gPlayer1ReadyFlag == 1)) {
                gBattleState.unk_00->unk_20 += 1;
                Battle_FinishTurn();
            }
            break;

        case 4:
            if (HandlePlayerActionFlag1000(gOpponentPlayer) == 0) {
                gBattleState.unk_00->unk_20 += 1;
            }
            break;

        case 5:
            Battle_ResetSubstate();
            Battle_SetCameraMoveSimple(arg0, sActivePokemon[gBattleState.unk_00->unk_2C]);
            gPlayer0ReadyFlag = UpdatePokemonHP(sActivePokemon[gBattleState.unk_00->unk_2C]);
            gPlayer1ReadyFlag = UpdatePokemonHP(sActivePokemon[!gBattleState.unk_00->unk_2C]);
            Battle_ProcessReadyState(arg0);
            break;
    }
}

void Battle_OpponentDefeatAnimFinal(CameraStruct* arg0) {
    PokemonAudioInfo* sp1C = &sActivePokemon[gBattleState.unk_00->unk_2C]->unk_654.unk_38;
    PokemonAudioInfo* sp18 = &sActivePokemon[!gBattleState.unk_00->unk_2C]->unk_654.unk_38;

    switch (gBattleState.unk_00->unk_20) {
        case 0:
            UpdateEntityStateByMode(gCurrentPlayer);
            Battle_SetAnimChannelFlag(2);
            gBattleState.unk_00->unk_20 += 1;
            break;

        case 1:
            Battle_ApplyAnimEffect(gCurrentPlayer);
            ResetSoundDurations();
            Battle_SetAnimChannelFlag(1);
            Battle_SetCameraOpponentClose(arg0, sActivePokemon[gBattleState.unk_00->unk_2C]);
            ExecuteAnimStateHandlers(sActivePokemon[gBattleState.unk_00->unk_2C], 0xD);
            sp1C->unk_0C = sp1C->unk_0E;
            sp18->unk_0C = sp18->unk_0E;
            gBattleState.unk_00->unk_20 += 1;
            break;

        case 2:
            Battle_SetCameraOpponentClose(arg0, sActivePokemon[gBattleState.unk_00->unk_2C]);
            gPlayer0ReadyFlag = UpdatePokemonHP(sActivePokemon[gBattleState.unk_00->unk_2C]);
            gPlayer1ReadyFlag = 1;

            if ((gPlayer0ReadyFlag == 1) && (gPlayer1ReadyFlag == 1) && (Battle_WaitFramesNonBlocking(0x32) != 0)) {
                Battle_FinishTurn();
                if (GetCurrentHP(sActivePokemon[gBattleState.unk_00->unk_2C]) == 0) {
                    Battle_ClearSubstateFlag();
                    Battle_SetPhase(arg0, 0x22);
                    gBattleState.unk_00->unk_2C = !gBattleState.unk_00->unk_2C;
                } else {
                    Battle_HandleSubstateTransition();
                }
            }
            break;
    }
}

void StartMoveAnimationAndFinalizeStatus(unk_BattlePlayerEntity* arg0) {
    StartMoveAnimation(arg0);
    FinalizeStatusEffect(arg0);
}

void Battle_PlayerDefeatSequence(CameraStruct* arg0) {
    unk_BattlePlayerAnimState* sp34 = &sActivePokemon[gBattleState.unk_00->unk_2C]->unk_654;
    unk_BattlePlayerEntity* temp_s0 = sActivePokemon[gBattleState.unk_00->unk_2C];
    PokemonAudioInfo* sp2C = &sActivePokemon[gBattleState.unk_00->unk_2C]->unk_654.unk_38;

    if (gBattleState.unk_00->unk_2C) {}

    switch (gBattleState.unk_00->unk_20) {
        case 0:
            if (gBattleState.unk_00->unk_34 == 1) {
                Battle_SetCameraFOV30(arg0);
                Battle_PlayMoveEffect(temp_s0, arg0, 4);
                PlayerDefeated(GetPlayerDefeatMessageId(temp_s0));
                gBattleState.unk_00->unk_20 += 1;
            } else if (Battle_CheckPlayerAction(arg0, temp_s0, 1, 1) != 0) {
                Dialog_SetMode(0xA);
                PlayerDefeated(GetPlayerDefeatMessageId(temp_s0));
                gBattleState.unk_00->unk_20 += 1;
            }
            break;

        case 1:
            Camera_SmoothZoomOut(arg0, temp_s0);
            ExecuteAnimStateHandlers(temp_s0, 2);
            StartMoveAnimationAndFinalizeStatus(temp_s0);
            gBattleState.unk_00->unk_20 += 1;
            break;

        case 2:
            Camera_SmoothZoomOut(arg0, temp_s0);
            if (Battle_WaitForAnimation(0x69) != 0) {
                Vec3f_Set(&arg0->unk_60.at, temp_s0->unk_4B0 * -150.0f, 0.0, 0.0f);
                if (gBattleState.unk_00 && gBattleState.unk_00) {}
                Vec3f_Set(&arg0->unk_60.eye, temp_s0->unk_4B0 * -50.0f, 5.0f, 0.0f);
                ApplyAnimEffectToOpponent(temp_s0, 2, 0);
                InitActionScriptMode3(0xD, temp_s0, temp_s0, 0xFF, 0xFF);
                gBattleState.unk_00->unk_20 += 1;
            }
            break;

        case 3:
            if (temp_s0->unk_4EC.unk_024.y == 2.5f) {
                temp_s0->unk_4EC.unk_000.unk_02 |= 0x20;
            }

            if (GraphNode_IsAnimationFinished(&temp_s0->unk_4EC) == 1) {
                gBattleState.unk_00->unk_20 += 1;
            }
            break;

        case 4:
            temp_s0->unk_4EC.unk_000.unk_01 &= ~1;
            temp_s0->unk_720->unk_04 = &temp_s0->unk_720->unk_08[sp34->unk_2C]->unk_01C[sp34->unk_18];
            temp_s0->unk_720->unk_00 |= 0x80;
            gBattleState.unk_00->unk_20 += 1;
            break;

        case 5:
            if (temp_s0->unk_720->unk_00 & 0x10) {
                temp_s0->unk_720->unk_00 &= ~0x90;
                Pokemon_ApplyFaintTransform(temp_s0);
                RefreshPokemonTransform(temp_s0);
                gPlayerScaleFactors[gBattleState.unk_00->unk_2C] = temp_s0->unk_654.unk_38.unk_0C;
                InitActionScriptMode3(3, temp_s0, temp_s0, 0xFF, 0xFF);
                Audio_PlaySoundEffect(2, 0, 0);
                Entity_SetupBattleState(temp_s0, sp34->unk_2C);
                arg0->unk_24.fovy = 40.0f;
                Dialog_SetMode(0xC);
                ProcessEntityAudioInfo(temp_s0);
                gCurrentDamage = 0;
                gBattleState.unk_00->unk_20 += 1;
            }
            break;

        case 6:
            ExecuteAnimStateHandlers(temp_s0, 0x12);
            Battle_PlayMoveEffect(temp_s0, arg0, 3);
            Battle_FinishTurn();
            gBattleState.unk_00->unk_20 += 1;
            break;

        case 7:
            Battle_AdvanceCameraTimelineFast(arg0, temp_s0);
            if (CanAnimProceedWithChannel(temp_s0, 0x3C) != 0) {
                ResetSoundDurations();
                Battle_SetAnimChannelFlag(2);
                Battle_FinishTurn();
                Vec3f_Set(&temp_s0->unk_000.unk_030, 1.0f, 1.0f, 1.0f);
                if (sp2C->unk_5A == 0xFE) {
                    sp2C->unk_5A = 0xA5;
                }
                Battle_HandleSubstateTransition();
                sp34->unk_34 &= ~0x1800;
                Dialog_Clear();
                gBattleState.unk_00->unk_54 = !gBattleState.unk_00->unk_2C + 1;
            }
            break;
    }
}

void Battle_PlayerDefeatSequenceAlt(CameraStruct* arg0) {
    unk_BattlePlayerAnimState* sp3C = &sActivePokemon[gBattleState.unk_00->unk_2C]->unk_654;
    unk_BattlePlayerAnimState* sp38 = &sActivePokemon[!gBattleState.unk_00->unk_2C]->unk_654;
    UNUSED s32 pad;
    unk_BattlePlayerEntity* temp_s0 = sActivePokemon[gBattleState.unk_00->unk_2C];
    PokemonAudioInfo* sp2C = &sActivePokemon[gBattleState.unk_00->unk_2C]->unk_654.unk_38;

    switch (gBattleState.unk_00->unk_20) {
        case 0:
            if (gBattleState.unk_00->unk_34 == 1) {
                Battle_SetCameraFOV30(arg0);
                Battle_FinishTurn();
                Dialog_SetMode(0xB);
                SetMessageFromAltTable(temp_s0->unk_720, 3);
                Vec3f_Set(&arg0->unk_60.at, temp_s0->unk_4B0 * -150.0f, 0.0, 0.0f);
                Vec3f_Set(&arg0->unk_60.eye, temp_s0->unk_4B0 * -50.0f, 5.0f, 0.0f);
                Vec3f_Set(&temp_s0->unk_000.unk_024, temp_s0->unk_4B0 * -150.0f, 25.0f, 0.0f);
                gBattleState.unk_00->unk_20 += 1;
            } else {
                Math_ExponentialApproach(&arg0->unk_24.fovy, 30.0f, 0.05f);
                if (Camera_SmoothFocusEntitySide(arg0, temp_s0) != 0) {
                    Battle_SetCameraFOV30(arg0);
                    Battle_FinishTurn();
                    Dialog_SetMode(0xB);
                    SetMessageFromAltTable(temp_s0->unk_720, 3);
                    gBattleState.unk_00->unk_20 += 1;
                }
            }
            break;

        case 1:
            if (AnimChannel_CheckAndReset(temp_s0) != 0) {
                temp_s0->unk_720->unk_02 = sp2C->unk_0B;
                ApplyAnimEffectToOpponent(temp_s0, 2, 0);
                InitActionScriptMode3(0xD, temp_s0, temp_s0, 0xFF, 0xFF);
                gBattleState.unk_00->unk_20 += 1;
            }
            break;

        case 2:
            if (temp_s0->unk_4EC.unk_024.y == 2.5f) {
                temp_s0->unk_4EC.unk_000.unk_02 |= 0x20;
            }

            if (GraphNode_IsAnimationFinished(&temp_s0->unk_4EC) == 1) {
                gBattleState.unk_00->unk_20 += 1;
            }
            break;

        case 3:
            temp_s0->unk_4EC.unk_000.unk_01 &= ~1;
            temp_s0->unk_720->unk_00 |= 0x80;
            temp_s0->unk_720->unk_04 = &temp_s0->unk_720->unk_08[sp3C->unk_2C]->unk_01C[sp3C->unk_18];
            gBattleState.unk_00->unk_20 += 1;
            break;

        case 4:
            if (temp_s0->unk_720->unk_00 & 0x10) {
                temp_s0->unk_720->unk_00 &= ~0x90;
                Pokemon_ApplyFaintTransform(temp_s0);
                RefreshPokemonTransform(temp_s0);
                gPlayerScaleFactors[IsPrimaryEntity(temp_s0)] = temp_s0->unk_654.unk_38.unk_0C;
                Audio_PlaySoundEffect(2, 0, 0);
                Entity_SetupBattleState(temp_s0, sp3C->unk_2C);
                Battle_FinishTurn();
                InitActionScriptMode3(3, temp_s0, temp_s0, 0xFF, 0xFF);
                arg0->unk_24.fovy = 40.0f;
                ProcessEntityAudioInfo(temp_s0);
                gCurrentDamage = 0;
                gBattleState.unk_00->unk_20 += 1;
            }
            break;

        case 5:
            ExecuteAnimStateHandlers(temp_s0, 0x12);
            Battle_PlayMoveEffect(temp_s0, arg0, 3);
            gBattleState.unk_00->unk_20 += 1;
            break;

        case 6:
            Battle_AdvanceCameraTimelineFast(arg0, temp_s0);
            if (CanAnimProceedWithChannel(temp_s0, 0x3C) != 0) {
                if ((sp2C->unk_5A & 0xF0) == 0xF0) {
                    sp2C->unk_5A = 0xA5;
                }
                ResetSoundDurations();
                Battle_SetAnimChannelFlag(2);
                Battle_FinishTurn();
                Vec3f_Set(&temp_s0->unk_000.unk_030, 1.0f, 1.0f, 1.0f);
                if (sp38->unk_2D != 0x10) {
                    gBattleState.unk_00->unk_34 = 3;
                }
                gBattleState.unk_00->unk_2E = 2;
                Battle_HandleSubstateTransition();
                sp3C->unk_34 &= 0xE7FF;
                gBattleState.unk_00->unk_54 = !gBattleState.unk_00->unk_2C + 1;
            }
            break;
    }
}

void Battle_StateMachineMain(CameraStruct* arg0) {
    Battle_SetCurrentAndOpponent();

    switch (gBattleState.unk_00->unk_38) {
        case 0:
            Battle_InitializeCameraAndAudio(arg0);
            Battle_SetPhase(arg0, 1);

        case 1:
            Battle_HandleSubstate0(arg0);
            break;
        case 2:
            Battle_StateMachineStepA(arg0);
            break;
        case 3:
            Battle_StateMachineStepB(arg0);
            break;
        case 4:
            BattleScene_Phase4(arg0);
            break;
        case 7:
            Battle_PlayerMoveAnimation(arg0);
            break;
        case 38:
            Battle_PlayerMoveAnimationAlt(arg0);
            break;
        case 27:
            Battle_PlayerMoveSequence(arg0);
            break;
        case 30:
            Battle_PlayerOpponentInteraction(arg0);
            break;
        case 29:
            BattleScene_Phase29(arg0);
            break;
        case 28:
            BattleScene_Phase28(arg0);
            break;
        case 25:
            BattleScene_Phase25(arg0);
            break;
        case 12:
            Battle_PlayerSwitchIn(arg0);
            break;
        case 13:
            Battle_PlayerSwitchOut(arg0);
            break;
        case 14:
            Battle_PlayerSwitchOutAlt(arg0);
            break;
        case 15:
            BattleScene_Phase15(arg0);
            break;
        case 17:
            Battle_PlayerSwitchInAlt(arg0);
            break;
        case 31:
            Battle_PlayerDefeatAnim(arg0);
            break;
        case 20:
            Battle_OpponentActionInit(arg0);
            break;
        case 8:
            Battle_OpponentMoveAnimation(arg0);
            break;
        case 10:
            Battle_OpponentDefeatAnimAlt(arg0);
            break;
        case 6:
            Battle_OpponentDefeatAnim(arg0);
            break;
        case 33:
            Battle_OpponentDefeatAnimFinal(arg0);
            break;
        case 35:
            Battle_OpponentSwitchOutAlt(arg0);
            break;
        case 9:
            Battle_OpponentSwitchOut(arg0);
            break;
        case 16:
            Battle_OpponentSwitchIn(arg0);
            break;
        case 11:
            Battle_PlayerDefeatSequence(arg0);
            break;
        case 18:
            Battle_PlayerDefeatSequenceAlt(arg0);
            break;
        case 5:
            Battle_StateMachine(arg0);
            break;
        case 34:
            Battle_StateMachineVariant(arg0);
            break;
        case 36:
            Battle_CheckAndAdvancePhase();
            break;
        case 37:
            Battle_FinalPhaseHandler();
            break;
    }
}
