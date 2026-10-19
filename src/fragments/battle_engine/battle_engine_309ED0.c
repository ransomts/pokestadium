#include "battle_engine.h"
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

void BattleScene_ApplyModelAnimationSlot5A(unk_BattlePlayerEntity* arg0) {
    unk_BattlePlayerAnimState* ptr = &arg0->animationState;

    if ((arg0->unk_000.unk_01A == 0x32) && (ptr->unk_34 & 0x4000)) {
        unk_BattleAnimDataEntry* tmp = &gAnimDataByPlayer[BattleScene_GetParticipantSideIndex(arg0)]->unk_000[0x5A];

        ModelAnim_SetAnimation(&arg0->unk_000, tmp->posX);
        arg0->unk_000.unk_000.posY &= ~0x20;
    }
}

void BattleScene_ResetAnimationStep(void) {
    gBattleScene.posX->unk_24 = 0;
}

s32 BattleScene_AdvanceOwnerAnimation(unk_BattlePlayerEntity* arg0) {
    unk_BattlePlayerAnimState* ptr = &arg0->animationState;
    UNUSED s32 pad;
    s32 sp1C = 0;

    if (!(ptr->unk_34 & 0x800)) {
        return 0;
    }

    if (gBattleScene.posX->unk_48 == 0x19) {
        return 0;
    }

    if ((ptr->unk_34 & 0x800) && (gBattleScene.posX->unk_48 == 0x1C)) {
        return 0;
    }

    switch (gBattleScene.posX->unk_24) {
        case 0:
            BattleAnim_BeginSessionRequestForActiveMon(arg0);
            sp1C = 1;
            gBattleScene.posX->unk_24++;
            break;

        case 1:
            sp1C = 1;
            if (arg0->pokemonAnimation->posX & 0x10) {
                arg0->pokemonAnimation->posX &= ~0x90;
                Battle_ReloadModelForActiveMove(arg0);
                BattleScene_ApplyModelAnimationSlot5A(arg0);
                gBattleScene.posX->unk_24++;
            }
            break;

        case 2:
            BattleScene_ResetAnimationStep();
            break;
    }
    return sp1C;
}

s32 BattleScene_AdvanceOwnerAnimation98(unk_BattlePlayerEntity* arg0) {
    UNUSED s32 pad[2];
    s32 sp1C = 0;

    if (!(arg0->animationState.unk_34 & 0x800)) {
        return 0;
    }

    switch (gBattleScene.posX->unk_24) {
        case 0:
            BattleAnim_BeginSessionRequest(arg0);
            sp1C = 1;
            gBattleScene.posX->unk_24++;
            break;

        case 1:
            sp1C = 1;
            if (arg0->pokemonAnimation->posX & 0x10) {
                arg0->pokemonAnimation->posX &= ~0x90;
                Battle_ReloadNeutralPlaceholderModel(arg0);
                gBattleScene.posX->unk_24++;
            }
            break;

        case 2:
            BattleScene_ResetAnimationStep();
            break;
    }
    return sp1C;
}

s32 BattleScene_AdvanceOwnerAnimationAndClearFlags(unk_BattlePlayerEntity* arg0) {
    UNUSED s32 pad[2];
    Vec3f sp34;
    s32 var_s0 = 0;

    if (!(arg0->animationState.unk_34 & 0x1000)) {
        return 0;
    }

    switch (gBattleScene.posX->unk_24) {
        case 0:
            BattleAnim_BeginSessionRequestForActiveMon(arg0);
            var_s0 = 1;
            gBattleScene.posX->unk_24++;
            break;

        case 1:
            var_s0 = 1;
            if (arg0->pokemonAnimation->posX & 0x10) {
                arg0->pokemonAnimation->posX &= ~0x90;
                Battle_ReloadModelForActiveMove(arg0);
                Battle_ClearRuntimeFlags(arg0, 0x1800);
                var_s0 = 0;
                BattleScene_ResetAnimationStep();
                gBattleScene.posX->unk_24++;
            }
            break;

        case 2:
            BattleScene_ResetAnimationStep();
            BattleAnim_GetOwnerDefaultAnchorPosition(arg0, &sp34);
            BattleAnim_Vec3fCopy(&gBattleScene.posX->unk_DC->unk_60.at, &sp34);
            break;
    }
    return var_s0;
}

s32 BattleScene_AdvanceDoublesOwnerAnimation(unk_BattlePlayerEntity* arg0) {
    UNUSED s32 pad[2];
    s32 sp1C = 0;

    if (gBattleScene.posX->unk_44 != 2) {
        return 0;
    }

    if (!(arg0->animationState.unk_34 & 0x800)) {
        return 0;
    }

    if ((gBattleScene.posX->unk_48 == 0x19) || (gBattleScene.posX->unk_48 == 0x1C)) {
        return 0;
    }

    switch (gBattleScene.posX->unk_24) {
        case 0:
            BattleAnim_BeginSessionRequestForActiveMon(arg0);
            sp1C = 1;
            gBattleScene.posX->unk_24 += 1;
            break;

        case 1:
            sp1C = 1;
            if (arg0->pokemonAnimation->posX & 0x10) {
                arg0->pokemonAnimation->posX &= ~0x90;
                Battle_ReloadModelForActiveMove(arg0);
                BattleScene_ApplyModelAnimationSlot5A(arg0);
                gBattleScene.posX->unk_24 += 1;
            }
            break;

        case 2:
            BattleScene_ResetAnimationStep();
            break;
    }
    return sp1C;
}

s32 BattleScene_AdvanceBothOwnerAnimations(void) {
    UNUSED s32 pad[2];
    s32 sp1C = 0;
    unk_BattlePlayerAnimState* temp_a1 = &sActivePokemon[0]->animationState;
    unk_BattlePlayerAnimState* temp_a2 = &sActivePokemon[1]->animationState;

    if (gBattleScene.posX->unk_44 != 1) {
        return 0;
    }

    if (!(temp_a1->unk_34 & 0x800) && !(temp_a2->unk_34 & 0x800)) {
        return 0;
    }

    switch (gBattleScene.posX->unk_24) {
        case 0:
            if (temp_a1->unk_34 & 0x800) {
                BattleAnim_BeginSessionRequest(sActivePokemon[0]);
            }
            sp1C = 1;
            gBattleScene.posX->unk_24 = gBattleScene.posX->unk_24 + 1;
            break;

        case 1:
            sp1C = 1;
            if (temp_a1->unk_34 & 0x800) {
                if (sActivePokemon[0]->pokemonAnimation->posX & 0x10) {
                    sActivePokemon[0]->pokemonAnimation->posX &= ~0x90;
                    Battle_ReloadNeutralPlaceholderModel(sActivePokemon[0]);
                    gBattleScene.posX->unk_24 += 1;
                }
            } else {
                gBattleScene.posX->unk_24 = gBattleScene.posX->unk_24 + 1;
            }
            break;

        case 2:
            if (temp_a2->unk_34 & 0x800) {
                BattleAnim_BeginSessionRequest(sActivePokemon[1]);
            }
            sp1C = 1;
            gBattleScene.posX->unk_24 = gBattleScene.posX->unk_24 + 1;
            break;

        case 3:
            sp1C = 1;
            if (temp_a2->unk_34 & 0x800) {
                if (sActivePokemon[1]->pokemonAnimation->posX & 0x10) {
                    sActivePokemon[1]->pokemonAnimation->posX &= ~0x90;
                    Battle_ReloadNeutralPlaceholderModel(sActivePokemon[1]);
                    gBattleScene.posX->unk_24 += 1;
                }
            } else {
                gBattleScene.posX->unk_24 = gBattleScene.posX->unk_24 + 1;
            }
            break;

        case 4:
            BattleScene_ResetAnimationStep();
            break;
    }

    return sp1C;
}

void BattleScene_ClearInactiveOwnerAnimationFlags(void) {
    PokemonAudioInfo* temp_v0 = &sActivePokemon[0]->animationState.unk_38;
    PokemonAudioInfo* temp_v1 = &sActivePokemon[1]->animationState.unk_38;

    if (temp_v0->unk_4F == 0) {
        temp_v0->unk_4C &= ~0x20;
    }

    if (temp_v1->unk_4F == 0) {
        temp_v1->unk_4C &= ~0x20;
    }
}

void func_8431FCC4(void) {
}

s32 BattleScene_AnimateDisplayedHpToRuntime(unk_BattlePlayerEntity* arg0) {
    PokemonAudioInfo* temp_s1 = &arg0->animationState.unk_38;
    PokemonData* temp_s2 = &arg0->unk_724->unk_01C[arg0->animationState.unk_08];
    f32 temp_fs0;
    UNUSED s16 pad;
    s16 sp30;

    if (gBattleUpdateHPFlag != 0) {
        return 1;
    }

    if (temp_s2->posY == temp_s1->unk_0C) {
        return 1;
    }

    temp_fs0 = temp_s1->unk_28 / 90.0f;
    sp30 = BattleScene_GetParticipantSideIndex(arg0);
    gPlayerScaleFactors[sp30] = Math_StepToF(gPlayerScaleFactors[BattleScene_GetParticipantSideIndex(arg0)], temp_s1->unk_0C, temp_fs0, temp_fs0);
    temp_s2->posY = gPlayerScaleFactors[BattleScene_GetParticipantSideIndex(arg0)];
    if (temp_s2->posY == temp_s1->unk_0C) {
        temp_fs0 = gPlayerScaleFactors[BattleScene_GetParticipantSideIndex(arg0)] - temp_s2->posY;
        gPlayerScaleFactors[BattleScene_GetParticipantSideIndex(arg0)] -= temp_fs0;
        if (arg0->unk_000.unk_01A == 0x98) {
            return 1;
        }
        return 1;
    }
    return 0;
}

void BattleScene_ClearPhaseFlag(void) {
    gBattleScene.posX->unk_3C = 0;
}

void BattleScene_SetPhaseFlag(void) {
    gBattleScene.posX->unk_3C = 1;
}

void BattleScene_SetPhase(UNUSED CameraStruct* arg0, s32 arg1) {
    gBattleScene.posX->unk_38 = arg1;
    gBattleScene.posX->unk_20 = 0;
}

void BattleScene_SaveCameraFov(CameraStruct* arg0) {
    gBattleScene.posX->unk_60 = arg0->unk_24.fovy;
}

void BattleScene_ResetCameraFov(CameraStruct* arg0) {
    arg0->unk_24.fovy = 30.0f;
    gBattleScene.posX->unk_60 = 30.0f;
}

s32 BattleScene_GetAnimationTimingField0D(unk_BattlePlayerEntity* arg0) {
    unk_BattleAnimDataEntry* ptr = &gAnimDataByPlayer[BattleScene_GetParticipantSideIndex(arg0)]->unk_000[arg0->animationState.unk_38.unk_5A - 1];

    return ptr->unk_0D;
}

s32 BattleScene_GetMappedAnimationTimingField0D(unk_BattlePlayerEntity* arg0) {
    UNUSED s32 pad;
    s32 sp18 = gAnimLookupTable[arg0->animationState.unk_38.unk_5A - 1];
    unk_BattleAnimDataEntry* ptr = &gAnimDataByPlayer[BattleScene_GetParticipantSideIndex(arg0)]->unk_000[sp18];

    return ptr->unk_0D;
}

s32 BattleScene_GetAnimationTimingField0E(unk_BattlePlayerEntity* arg0) {
    unk_BattleAnimDataEntry* ptr = &gAnimDataByPlayer[BattleScene_GetParticipantSideIndex(arg0)]->unk_000[arg0->animationState.unk_38.unk_5A - 1];

    return ptr->unk_0E;
}

s32 BattleScene_GetMappedAnimationTimingField0E(unk_BattlePlayerEntity* arg0) {
    UNUSED s32 pad;
    s32 sp18 = gAnimLookupTable[arg0->animationState.unk_38.unk_5A - 1];
    unk_BattleAnimDataEntry* ptr = &gAnimDataByPlayer[BattleScene_GetParticipantSideIndex(arg0)]->unk_000[sp18];

    return ptr->unk_0E;
}

s32 BattleScene_GetCameraShotDuration(unk_BattlePlayerEntity* arg0) {
    unk_BattleAnimDataEntry* ptr = &gAnimDataByPlayer[BattleScene_GetParticipantSideIndex(arg0)]->unk_000[arg0->animationState.unk_38.unk_5A - 1];

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

    temp_s0 = &sActivePokemon[0]->animationState;
    temp_s1 = &sActivePokemon[1]->animationState;
    BattleScene_SetCameraSubstate(1, 1);

    sp2C = gBattleScene.posX->unk_2C;
    gBattleScene.posX->unk_2C = Battle_DetermineMoveOrder(sActivePokemon[0], sActivePokemon[1]);

    ptr = &sActivePokemon[gBattleScene.posX->unk_2C]->animationState.unk_38;
    if ((ptr->unk_5A & 0xF0) == 0xF0) {
        gBattleScene.posX->unk_2C = !gBattleScene.posX->unk_2C;
    }

    if (sActivePokemon[0]->unk_724->unk_000 & 2) {
        if (gBattleScene.posX->unk_2C == 0) {
            BattleAI_RecordUsedMove(temp_s0->unk_08, temp_s1->unk_08, 0);
        } else {
            BattleAI_RecordUsedMove(temp_s0->unk_08, temp_s1->unk_08, 1);
        }
    } else if (sActivePokemon[1]->unk_724->unk_000 & 2) {
        if (gBattleScene.posX->unk_2C == 1) {
            BattleAI_RecordUsedMove(temp_s1->unk_08, temp_s0->unk_08, 0);
        } else {
            BattleAI_RecordUsedMove(temp_s1->unk_08, temp_s0->unk_08, 1);
        }
    }

    gBattleScene.posX->unk_2A = gBattleScene.posX->unk_2C;
    gBattleScene.posX->unk_38 = 0;
    temp_s0->unk_30 = 0;
    temp_s1->unk_30 = 0;
    gBattleScene.posX->unk_44 = 2;
    Battle_ResolveMonAction();
    gBattleScene.posX->unk_2C = sp2C;
}

void BattleScene_InitializeSwitchActions(void) {
    s32 sp2C;
    unk_BattlePlayerAnimState* sp28;
    unk_BattlePlayerAnimState* sp24;

    sp28 = &sActivePokemon[0]->animationState;
    sp24 = &sActivePokemon[1]->animationState;
    BattleScene_SetCameraSubstate(1, 1);

    sp2C = gBattleScene.posX->unk_2C;

    if ((sp28->unk_2D == 0xF) || (sp28->unk_2D == 0x10)) {
        if (sActivePokemon[0]->unk_724->unk_000 & 2) {
            BattleAI_RecordUsedMove(sp28->unk_08, sp24->unk_08, 2);
        }
        gBattleScene.posX->unk_2C = 0;
        gBattleScene.posX->unk_2A = 0;
        gBattleScene.posX->unk_38 = 0;
        gBattleScene.posX->unk_44 = 2;
        BeginBattleForEntity(sActivePokemon[0]);
        gBattleScene.posX->unk_2C = sp2C;
    } else {
        if (sActivePokemon[0]->unk_724->unk_000 & 2) {
            BattleAI_RecordUsedMove(sp24->unk_08, sp28->unk_08, 2);
        }
        gBattleScene.posX->unk_2C = 1;
        gBattleScene.posX->unk_2A = 1;
        gBattleScene.posX->unk_38 = 0;
        gBattleScene.posX->unk_44 = 2;
        BeginBattleForEntity(sActivePokemon[1]);
        gBattleScene.posX->unk_2C = sp2C;
    }
}

s32 BattleScene_PrepareReplacementTransition(void) {
    unk_BattlePlayerAnimState* sp24 = &sActivePokemon[gBattleScene.posX->unk_2C]->animationState;
    unk_BattlePlayerAnimState* temp_a3 = &sActivePokemon[gBattleScene.posX->unk_2C]->animationState;
    unk_BattlePlayerAnimState* sp20 = &sActivePokemon[!gBattleScene.posX->unk_2C]->animationState;

    if ((sActivePokemon[gBattleScene.posX->unk_2C]->animationState.unk_2D == 0xF) || (sp24->unk_2D == 0x10)) {
        if (sActivePokemon[gBattleScene.posX->unk_2C]->unk_724->unk_000 & 2) {
            BattleAI_RecordUsedMove(temp_a3->unk_08, sp20->unk_08, 2);
        }
        Battle_ClearRuntimeFlags(sActivePokemon[gBattleScene.posX->unk_2C], 0x1800);
        gBattleScene.posX->unk_20 = 0;
        gBattleScene.posX->unk_14 = 0;
        if (sp24->unk_2D == 0x10) {
            gBattleScene.posX->unk_38 = 0x12;
        } else {
            BattleAnim_GetOwnerDefaultAnchorPosition(sActivePokemon[gBattleScene.posX->unk_2C], &gCameraPreset.posX);
            BattleScene_LoadCameraPreset(&gCameraPosB, gBattleScene.posX->unk_DC, sActivePokemon[gBattleScene.posX->unk_2C]);
            gBattleScene.posX->unk_38 = 0xB;
        }
        return 1;
    }

    return 0;
}

void BattleScene_BeginBattlePhase(void) {
    unk_BattlePlayerAnimState* sp1C = &sActivePokemon[0]->animationState;
    unk_BattlePlayerAnimState* sp18 = &sActivePokemon[1]->animationState;

    if ((BattleScene_IsPresentationCountdownComplete() == 0) && (gBattleResultPhase != 1)) {
        AudioFrameUpdate(1);
    }

    BattleScene_ClearInactiveOwnerAnimationFlags();
    sp1C->unk_10 = 0;
    sp18->unk_10 = 0;

    if ((sp1C->unk_2D == 0x10) || (sp18->unk_2D == 0x10) || (gBattleScene.posX->unk_2E == 2)) {
        BattleScene_SetCameraSubstate(1, 0);
    } else {
        BattleScene_SetCameraSubstate(1, 1);
    }

    gBattleScene.posX->unk_44 = 1;
    gBattleScene.posX->unk_20 += 1;
}

s32 BattleScene_TransitionToPhaseFull(s32 arg0) {
    BattleScene_ClearPhaseFlag();
    BattleScene_ResetCameraFrameCounter();
    gBattleScene.posX->unk_48 = 0;
    gBattleScene.posX->unk_4C = 0;
    gBattleScene.posX->unk_20 = 0;
    gBattleScene.posX->unk_14 = 0;
    gBattleScene.posX->unk_38 = arg0;
    return 1;
}

s32 BattleScene_TransitionToPhase(s32 arg0) {
    BattleScene_ClearPhaseFlag();
    BattleScene_ResetCameraFrameCounter();
    gBattleScene.posX->unk_4C = 0;
    gBattleScene.posX->unk_20 = 0;
    gBattleScene.posX->unk_14 = 0;
    gBattleScene.posX->unk_38 = arg0;
    return 1;
}

s32 BattleScene_TransitionToPhaseDuplicate(s32 arg0) {
    BattleScene_ClearPhaseFlag();
    BattleScene_ResetCameraFrameCounter();
    gBattleScene.posX->unk_4C = 0;
    gBattleScene.posX->unk_20 = 0;
    gBattleScene.posX->unk_14 = 0;
    gBattleScene.posX->unk_38 = arg0;
    return 1;
}

void BattleScene_SwitchActiveSideAndSetPhase(CameraStruct* arg0) {
    gBattleScene.posX->unk_2C = !gBattleScene.posX->unk_2C;
    BattleScene_SetPhase(arg0, 5);
}

void Battle_ActSecondAttacker(u8 arg0) {
    unk_BattlePlayerAnimState* temp_a3;

    gBattleScene.posX->unk_2C = !gBattleScene.posX->unk_2C;
    temp_a3 = &sActivePokemon[gBattleScene.posX->unk_2C]->animationState;

    if ((temp_a3->unk_2D == 0xF) || (temp_a3->unk_2D == 0x10)) {
        BeginBattleForEntity(sActivePokemon[gBattleScene.posX->unk_2C]);
    } else {
        Battle_ResolveMonAction();
    }

    gBattleScene.posX->unk_34 = 1;
    gBattleScene.posX->unk_A0.z = 0.0f;
    BattleScene_SetPhase(gBattleScene.posX->unk_DC, 0x24);
    gBattleScene.posX->unk_78 = arg0;
}

void BattleScene_PhaseResumeSaved(void) {
    if (BattleScene_AdvanceOwnerAnimation(sActivePokemon[gBattleScene.posX->unk_2C]) == 0) {
        gBattleScene.posX->unk_38 = gBattleScene.posX->unk_78;
    }
}

void BattleScene_CleanupActionAndAdvance(void) {
    PokemonAudioInfo* sp24;
    PokemonAudioInfo* sp20;
    unk_BattlePlayerAnimState* sp1C;

    if (gBattleScene.posX->unk_34 == 0) {
        BattleAnim_ClearOverlayFlag(sActivePokemon[gBattleScene.posX->unk_2C]);
        Audio_FadeAndClearStoredSounds();
        BattleScene_ResetAnimationStep();

        sp24 = &sActivePokemon[gBattleScene.posX->unk_2C]->animationState.unk_38;
        sp20 = &sActivePokemon[!gBattleScene.posX->unk_2C]->animationState.unk_38;
        sp1C = &sActivePokemon[!gBattleScene.posX->unk_2C]->animationState;

        if ((((sp24->unk_5A & 0xF0) == 0xF0) || ((sp20->unk_5A & 0xF0) == 0xF0)) && (sp1C->unk_2D != 0xF) &&
            (sp1C->unk_2D != 0x10)) {
            gBattleScene.posX->unk_20 = 0;
            gBattleScene.posX->unk_14 = 0;
            gBattleScene.posX->unk_38 = 4;

            if ((sp24->unk_5A & 0xF0) == 0xF0) {
                sp24->unk_5A = 0xA5;
            }

            if ((sp20->unk_5A & 0xF0) == 0xF0) {
                sp20->unk_5A = 0xA5;
            }
        } else {
            Battle_ActSecondAttacker(3);
            gBattleScene.posX->unk_20 = 0;
            gBattleScene.posX->unk_14 = 0;
        }
    } else {
        sp24 = &sActivePokemon[gBattleScene.posX->unk_2C]->animationState.unk_38;
        sp20 = &sActivePokemon[!gBattleScene.posX->unk_2C]->animationState.unk_38;

        BattleAnim_ClearOverlayFlag(sActivePokemon[gBattleScene.posX->unk_2C]);
        Audio_FadeAndClearStoredSounds();
        BattleScene_ResetAnimationStep();

        gBattleScene.posX->unk_20 = 0;
        gBattleScene.posX->unk_14 = 0;
        gBattleScene.posX->unk_38 = 4;

        if ((sp24->unk_5A & 0xF0) == 0xF0) {
            sp24->unk_5A = 0xA5;
        }

        if ((sp20->unk_5A & 0xF0) == 0xF0) {
            sp20->unk_5A = 0xA5;
        }
    }
}

s32 BattleScene_HandleFaintStatusCompletion(void) {
    PokemonAudioInfo* temp_v0 = &gOpponentPlayer->animationState.unk_38;

    if (((temp_v0->unk_4D & 0x80) || (temp_v0->unk_15 & 0x18)) && ((temp_v0->unk_5A & 0xF0) == 0xF0)) {
        BattleAnim_ClearOverlayFlag(sActivePokemon[gBattleScene.posX->unk_2C]);
        Audio_FadeAndClearStoredSounds();
        BattleScene_ResetAnimationStep();
        Battle_ActSecondAttacker(3);
        gBattleScene.posX->unk_20 = 0;
        gBattleScene.posX->unk_48 = 0;
        gBattleScene.posX->unk_14 = 0;
        return 1;
    }
    return 0;
}

void BattleScene_CompleteActionPhase(void) {
    if ((gBattleScene.posX->unk_34 == 0) && ((gOpponentPlayer->animationState.unk_38.unk_5A & 0xF0) != 0xF0)) {
        BattleAnim_ClearOverlayFlag(sActivePokemon[gBattleScene.posX->unk_2C]);
        Audio_FadeAndClearStoredSounds();
        BattleScene_ResetAnimationStep();
        Battle_ActSecondAttacker(3);
        gBattleScene.posX->unk_20 = 0;
        gBattleScene.posX->unk_14 = 0;
    } else if (BattleScene_HandleFaintStatusCompletion() == 0) {
        BattleAnim_ClearOverlayFlag(sActivePokemon[gBattleScene.posX->unk_2C]);
        Audio_FadeAndClearStoredSounds();
        BattleScene_ResetAnimationStep();
        gBattleScene.posX->unk_20 = 0;
        gBattleScene.posX->unk_14 = 0;
        gBattleScene.posX->unk_38 = 4;
    }
}

void BattleScene_ResolveDisplayedHpCompletion(CameraStruct* arg0) {
    if ((gPlayer0ReadyFlag == 1) && (gPlayer1ReadyFlag == 1)) {
        if (Battle_GetActiveMonHp(sActivePokemon[gBattleScene.posX->unk_2C]) == 0) {
            BattleScene_SwitchActiveSideAndSetPhase(arg0);
        } else if (Battle_GetActiveMonHp(sActivePokemon[!gBattleScene.posX->unk_2C]) == 0) {
            BattleScene_SetPhase(arg0, 5);
        } else {
            BattleScene_CompleteActionPhase();
        }
    }
}

void BattleScene_UpdateDisplayedHpAndTransition(CameraStruct* arg0) {
    PokemonAudioInfo* sp1C = &sActivePokemon[gBattleScene.posX->unk_2C]->animationState.unk_38;

    gPlayer0ReadyFlag = BattleScene_AnimateDisplayedHpToRuntime(sActivePokemon[0]);
    gPlayer1ReadyFlag = BattleScene_AnimateDisplayedHpToRuntime(sActivePokemon[1]);
    BattleScene_ClearPhaseFlag();
    BattleScene_ResetCameraFrameCounter();

    if (Battle_GetActiveMonHp(sActivePokemon[gBattleScene.posX->unk_2C]) == 0) {
        BattleScene_SwitchActiveSideAndSetPhase(arg0);
    } else if (Battle_GetActiveMonHp(sActivePokemon[!gBattleScene.posX->unk_2C]) == 0) {
        BattleScene_ResolveDisplayedHpCompletion(arg0);
    } else if (gBattleScene.posX->unk_4C == 0xA) {
        BattleScene_TransitionToPhaseDuplicate(0xA);
    } else if (gBattleScene.posX->unk_48 == 9) {
        BattleScene_TransitionToPhaseFull(9);
    } else if ((sp1C->unk_15 & 0x18) || (sp1C->unk_4D & 0x80)) {
        BattleScene_TransitionToPhaseFull(6);
    } else {
        BattleScene_ResolveDisplayedHpCompletion(arg0);
    }
}

void BattleScene_WaitForDisplayedHpAnimations(CameraStruct* arg0) {
    if ((gPlayer0ReadyFlag == 1) && (gPlayer1ReadyFlag == 1)) {
        BattleBox_Close();
        BattleScene_UpdateDisplayedHpAndTransition(arg0);
    }
}

s32 BattleScene_ActionPresentationTransitionCheck(void) {
    switch (gBattleScene.posX->unk_48) {
        case 7:
        case 38:
        case 39:
            BattleScene_EnterStateRow(gCurrentPlayer, 3);
            return BattleScene_TransitionToPhase(0x25);

        case 30:
            BattleScene_EnterStateRow(gCurrentPlayer, 3);
            return BattleScene_TransitionToPhase(0x25);

        case 28:
            return BattleScene_TransitionToPhase(0x25);

        case 21:
            BattleScene_EnterStateRow(gCurrentPlayer, 3);
            return BattleScene_TransitionToPhase(0x25);

        case 15:
            return BattleScene_TransitionToPhase(0x25);

        case 25:
            return BattleScene_TransitionToPhase(0x25);

        case 27:
            return BattleScene_TransitionToPhase(0x25);

        case 29:
            BattleScene_EnterStateRow(gCurrentPlayer, 3);
            return BattleScene_TransitionToPhase(0x25);

        case 12:
            BattleScene_EnterStateRow(gCurrentPlayer, 8);
            return BattleScene_TransitionToPhase(0x25);

        case 13:
            BattleScene_EnterStateRow(gCurrentPlayer, 8);
            return BattleScene_TransitionToPhase(0x25);

        case 14:
            BattleScene_EnterStateRow(gCurrentPlayer, 8);
            return BattleScene_TransitionToPhase(0x25);

        case 17:
            BattleScene_EnterStateRow(gCurrentPlayer, 9);
            return BattleScene_TransitionToPhase(0x25);

        case 31:
            return BattleScene_TransitionToPhase(0x25);
    }
    return 0;
}

s32 BattleScene_ActionPresentationCleanupCheck(void) {
    s32 tmp = gBattleScene.posX->unk_48;

    if (tmp != 0x10) {
        if (gBattleScene.posX->unk_48 == 0x14) {
            return BattleScene_TransitionToPhaseFull(0x14);
        }
    } else {
        return BattleScene_TransitionToPhaseFull(0x10);
    }

    if ((gBattleMoveFailed != 0) || (gBattleScene.posX->unk_48 == 8)) {
        return BattleScene_TransitionToPhaseFull(8);
    }
    return 0;
}

s32 BattleScene_PrepareResidualStatusPresentation(void) {
    s32 idx = gBattleScene.posX->unk_2C;
    PokemonAudioInfo* temp_v1_2 = &sActivePokemon[idx]->animationState.unk_38;

    if (((temp_v1_2->unk_4D & 0x80) || (temp_v1_2->unk_15 & 0x18)) && ((temp_v1_2->unk_5A & 0xF0) == 0xF0)) {
        return BattleScene_TransitionToPhaseFull(0x23);
    }
    return 0;
}

void BattleScene_UpdateActiveOwnerPointers(void) {
    s32 idx;

    gCurrentPlayer = sActivePokemon[gBattleScene.posX->unk_2C];
    idx = gBattleScene.posX->unk_2C == 0;
    gOpponentPlayer = sActivePokemon[idx];
}

void BattleScene_InitializeBattlePresentation(CameraStruct* arg0) {
    AudioFrameUpdate(0);
    BattleScene_SetCameraClipPlanes(arg0, 20.0f, 12800.0f);
    BattleScene_ResetAnimationStep();
    gBattleScene.posX->unk_34 = 0;
    BattleScene_ClearPhaseFlag();
    gBattleScene.posX->unk_14 = 0;
    Battle_ResetModelToIdleAnim(sActivePokemon[0]);
    Battle_ResetModelToIdleAnim(sActivePokemon[1]);
    gBattleScene.posX->unk_20++;
}

void BattleScene_SendOutPresentationFinalize(CameraStruct* arg0) {
    unk_BattlePlayerAnimState* temp_t2 = &sActivePokemon[!gBattleScene.posX->unk_2C]->animationState;
    unk_BattlePlayerAnimState* temp_t1 = &sActivePokemon[gBattleScene.posX->unk_2C]->animationState;
    s16 sp2E = sActivePokemon[gBattleScene.posX->unk_2C]->unk_000.unk_01A;
    unk_BattleAnimDataEntry* sp28 = &gAnimDataByPlayer[gBattleScene.posX->unk_2C]->unk_A50;
    unk_BattlePlayerEntity* sp24 = sActivePokemon[gBattleScene.posX->unk_2C];

    if (((temp_t2->unk_2D == 0x13) && (temp_t1->unk_2D == 0x13)) ||
        ((temp_t2->unk_2D == 0x10) && (temp_t1->unk_2D == 0x13)) ||
        ((temp_t1->unk_2D == 0x10) && (temp_t2->unk_2D == 0x13))) {
        BattleBox_Open(0xE);
        Vec3f_SetComponentsDuplicate(&arg0->unk_60.at, 0.0f, 75.0f, 0.0f);
        Vec3f_SetComponentsDuplicate(&arg0->unk_60.eye, 0.0f, 80.0f, 400.0f);
        Audio_StartBattleMusicSequence();
        gBattleScene.posX->unk_20 = 8;
        return;
    }

    if (temp_t1->unk_34 & 0x4008) {
        sp24->unk_000.unk_01D = 0xFF;
        BattleAnim_StopOwnerCategoryParticles(4, sp24);
        sp24->unk_000.unk_024.y = gPokemonModelDimensions[gBattleScene.posX->unk_2C].unk_08;
        sp24->unk_000.unk_000.posY &= ~0x2;
        sp24->unk_000.unk_000.posY |= 0x20;
        sp24->unk_000.unk_000.unk_01 |= 1;
        Battle_ClearRuntimeFlags(sp24, 0x4608);
    }

    if (sActivePokemon[gBattleScene.posX->unk_2C]->animationMode == 0xA) {
        BattleScene_SetParticipantModelFlags(sActivePokemon[gBattleScene.posX->unk_2C], 0, 0);
    }

    if (sActivePokemon[gBattleScene.posX->unk_2C]->animationMode == 0xD) {
        BattleScene_SetParticipantModelFlags(sActivePokemon[gBattleScene.posX->unk_2C], 0, 0);
    }

    if (sActivePokemon[gBattleScene.posX->unk_2C]->animationMode == 0x10) {
        BattleScene_SetParticipantModelFlags(sActivePokemon[gBattleScene.posX->unk_2C], 0, 0);
    }

    sActivePokemon[gBattleScene.posX->unk_2C]->unk_000.unk_01E.x = 0;
    if ((sp2E == 0x32) || (sp2E == 0x33)) {
        sActivePokemon[gBattleScene.posX->unk_2C]->unk_000.unk_000.posY |= 0x20;
        sActivePokemon[gBattleScene.posX->unk_2C]->unk_000.unk_000.unk_01 |= 1;
        ModelAnim_SetAnimation(&sActivePokemon[gBattleScene.posX->unk_2C]->unk_000, sp28->posX);
    }

    Battle_ResetModelToIdleAnim(sActivePokemon[gBattleScene.posX->unk_2C]);
    Vec3f_SetComponentsDuplicate(&sActivePokemon[gBattleScene.posX->unk_2C]->unk_000.unk_030, 1.0f, 1.0f, 1.0f);
    sActivePokemon[gBattleScene.posX->unk_2C]->unk_000.unk_024.y = BattleScene_GetParticipantModelHeight(sActivePokemon[gBattleScene.posX->unk_2C]);
    BattleAnim_GetOwnerDefaultAnchorPosition(sActivePokemon[gBattleScene.posX->unk_2C], &gCameraPreset.posX);
    BattleScene_LoadCameraPreset(&gBattleCameraPresetE, arg0, sActivePokemon[gBattleScene.posX->unk_2C]);
    BattleScene_ApplyCameraPreset(arg0, sActivePokemon[gBattleScene.posX->unk_2C], 1);
    Audio_StartBattleMusicSequence();
    gBattleScene.posX->unk_20 = 6;
}

s32 BattleScene_ResetOwnerStatusPresentation(unk_BattlePlayerEntity* arg0) {
    UNUSED s32 pad;
    unk_BattlePlayerAnimState* sp28 = &arg0->animationState;

    gBattleScene.posX->unk_54 = 0;
    BattleAnim_ResetFreezeStatusAndRestoreAnimation(arg0);

    if (sp28->unk_34 & 0x200) {
        Battle_ClearRuntimeFlags(arg0, 0x60C);
        return 1;
    }

    if (sp28->unk_34 & 0x4008) {
        arg0->unk_000.unk_01D = 0xFF;
        BattleAnim_StopOwnerCategoryParticles(4, arg0);
        arg0->unk_000.unk_024.y = gPokemonModelDimensions[BattleScene_GetParticipantSideIndex(arg0)].unk_08;
        arg0->unk_000.unk_000.posY &= ~0x2;
        arg0->unk_000.unk_000.posY |= 0x20;
        arg0->unk_000.unk_000.unk_01 |= 1;
        Battle_ClearRuntimeFlags(arg0, 0x4608);
    }

    BattleAnim_EndSleepStatusAnimation(arg0);
    sp28->unk_2E = 0xFF;
    Model_SetMaterialColor(&arg0->unk_000, 0xFF, 0xFF, 0xFF, sp28->unk_2E);
    BattleScene_CleanupParticipantEffectMode(arg0);
    arg0->unk_000.unk_01E.x = 0;
    return 0;
}

void BattleScene_AdvanceSendOutPreparation(CameraStruct* arg0) {
    if (BattleScene_AdvanceOwnerAnimation(sActivePokemon[!gBattleScene.posX->unk_2C]) == 0) {
        Battle_ClearRuntimeFlags(sActivePokemon[!gBattleScene.posX->unk_2C], 0x1800);
        Audio_FadeAndClearStoredSounds();
        BattleAnim_CleanupEffects(2);
        BattleScene_ResetCameraFrameCounter();
        RemovePlayer(BattleScene_GetParticipantDisplayPlayerNumber(sActivePokemon[!gBattleScene.posX->unk_2C]));

        if (BattleScene_ResetOwnerStatusPresentation(sActivePokemon[!gBattleScene.posX->unk_2C]) != 0) {
            BattleScene_EnterStateRow(sActivePokemon[!gBattleScene.posX->unk_2C], 0x11);
            BattleScene_ClearCameraOffsetVectors();
            gBattleScene.posX->unk_20 = 0xA;
        } else {
            BattleScene_EnterStateRow(sActivePokemon[!gBattleScene.posX->unk_2C], 0);
            BattleScene_ClearCameraOffsetVectors();
            gBattleScene.posX->unk_20++;
        }

        BattleScene_SelectCameraShot(sActivePokemon[!gBattleScene.posX->unk_2C], arg0, 3);

        if (BattleScene_IsPartnerPikachu(sActivePokemon[!gBattleScene.posX->unk_2C]) != 0) {
            Cry_Play(0xC8, 1);
        } else {
            Cry_Play(sActivePokemon[!gBattleScene.posX->unk_2C]->unk_000.unk_01A, 1);
        }
    }
}

void BattleScene_AdvanceSendOutCamera(CameraStruct* arg0) {
    UNUSED s32 pad[2];
    unk_BattlePlayerAnimState* sp24 = &sActivePokemon[!gBattleScene.posX->unk_2C]->animationState;
    unk_BattleAnimDataEntry* sp20 = &gAnimDataByPlayer[!gBattleScene.posX->unk_2C]->unk_A70;

    if (BattleAnim_IsAssetLoadBusy(sActivePokemon[!gBattleScene.posX->unk_2C]) == 0) {
        if (gBattleScene.posX->unk_14 == 0x1D) {
            BattleScene_SelectCameraShot(sActivePokemon[!gBattleScene.posX->unk_2C], arg0, 4);
        }

        if (BattleScene_AdvanceCameraFrameCounterUntil(0x1E) != 0) {
            BattleScene_ApproachCameraZoom(arg0, sActivePokemon[!gBattleScene.posX->unk_2C]);
        }

        if (((sp20->rotation >> 1) == (sActivePokemon[!gBattleScene.posX->unk_2C]->unk_000.unk_040.unk_08 >> 0x10)) &&
            (sp24->unk_2D != 0x12)) {
            BattleBox_Open(9);
        }

        if (sp20->unk_0A == ((sActivePokemon[!gBattleScene.posX->unk_2C]->unk_000.unk_040.unk_08 >> 0x10) + 3)) {
            sActivePokemon[!gBattleScene.posX->unk_2C]->unk_000.unk_000.posY &= ~0x20;
            Battle_SetRuntimeFlags(sActivePokemon[!gBattleScene.posX->unk_2C], 0x100);
            BattleScene_ResetCameraFrameCounter();
            gBattleScene.posX->unk_20 += 1;
        }
        BattleScene_ApproachCameraTarget(arg0, sActivePokemon[!gBattleScene.posX->unk_2C], 0);
    }
}

void BattleScene_AdvanceSendOutCameraClose(CameraStruct* arg0) {
    BattleScene_ApproachCameraTarget(arg0, sActivePokemon[!gBattleScene.posX->unk_2C], 1);
    if (BattleScene_AdvanceCameraFrameCounter(0x19) != 0) {
        Audio_FadeAndClearStoredSounds();
        gBattleScene.posX->unk_20++;
    }
}

void BattleScene_FinishSendOutCameraClose(CameraStruct* arg0) {
    unk_BattlePlayerAnimState* temp_s0 = &sActivePokemon[!gBattleScene.posX->unk_2C]->animationState;

    BattleScene_ApproachCameraTarget(arg0, sActivePokemon[!gBattleScene.posX->unk_2C], 1);

    if (BattleScene_AdvanceCameraFrameCounter(5) != 0) {
        BattleAnim_CleanupEffects(1);
        Audio_FadeCommand(3, 0);

        if (temp_s0->unk_2D != 0x12) {
            temp_s0->unk_2D = 0x10;
        }

        if (temp_s0->unk_2D == 0x12) {
            temp_s0->unk_2D = 0x13;
        }

        gBattleScene.posX->unk_20++;
    }
}

void BattleScene_CompleteSendOutPresentation(CameraStruct* arg0) {
    unk_BattlePlayerAnimState* sp24 = &sActivePokemon[!gBattleScene.posX->unk_2C]->animationState;
    unk_BattlePlayerAnimState* sp20 = &sActivePokemon[gBattleScene.posX->unk_2C]->animationState;

    if (BattleScene_AdvanceCameraFrameCounter(0xA) != 0) {
        BattleScene_ResetCameraFrameCounter();
        BattleScene_ClearPhaseFlag();
        gBattleScene.posX->unk_20++;
        if (sp24->unk_2D == 0x10) {
            gBattleScene.posX->unk_14 = 0;
            gBattleScene.posX->unk_20 = 0;

            if ((sp20->unk_2D == 0x11) || (sp20->unk_2D == 0x12)) {
                gBattleScene.posX->unk_38 = 5;
                gBattleScene.posX->unk_2C = !gBattleScene.posX->unk_2C;
            } else if ((sp24->unk_2D == 0x13) || (sp20->unk_2D == 0x13)) {
                BattleBox_Open(0xE);
                Vec3f_SetComponentsDuplicate(&arg0->unk_60.at, 0.0f, 75.0f, 0.0f);
                Vec3f_SetComponentsDuplicate(&arg0->unk_60.eye, 0.0f, 80.0f, 400.0f);
                Audio_StartBattleMusicSequence();
                gBattleScene.posX->unk_2C = !gBattleScene.posX->unk_2C;
                gBattleScene.posX->unk_20 = 8;
            } else {
                gBattleScene.posX->unk_38 = 4;
            }
        } else if ((sp20->unk_2D == 0x12) || (sp20->unk_2D == 0x11)) {
            gBattleScene.posX->unk_14 = 0;
            gBattleScene.posX->unk_20 = 0;
            gBattleScene.posX->unk_38 = 5;
            gBattleScene.posX->unk_2C = !gBattleScene.posX->unk_2C;
        } else {
            BattleScene_SendOutPresentationFinalize(arg0);
        }
        Audio_FadeAndClearStoredSounds();
    }
}

void UnusedBattleStateHandler(UNUSED CameraStruct* arg0) {
}

void BattleScene_SetupSendOutOwnerShot(CameraStruct* arg0) {
    unk_BattlePlayerEntity* temp_s0;
    UNUSED s32 pad;
    f32 sp44;
    f32 sp40;
    s16 sp3E;
    UNUSED s16 pad2;
    u8 sp3B;
    s16 tmp1;

    temp_s0 = sActivePokemon[gBattleScene.posX->unk_2C];
    sp3B = temp_s0->unk_000.unk_01A - 1;

    if (BattleScene_AnimateCameraPreset(arg0, temp_s0, 1, 0) != 0) {
        BattleScene_ResetCameraFrameCounter();
        BattleBox_Open(0xE);
        BattleScene_SetCameraClipPlanes(arg0, 10.0f, 12800.0f);
        arg0->unk_24.fovy = 60.0f;
        if ((sActivePokemon[gBattleScene.posX->unk_2C]->unk_000.unk_01A == 0x5F) && (gBattleScene.posX->unk_2C == 1)) {
            sp3B = 0x97;
        }

        sp44 = (gAnimDataSetC[gBattleScene.posX->unk_2C]->posX.y + temp_s0->unk_000.unk_024.y) + gCameraOffsetTable[sp3B].z;
        sp40 = ((gAnimDataSetC[gBattleScene.posX->unk_2C]->posX.z + gCameraOffsetTable[sp3B].y) * temp_s0->sideSign) +
               temp_s0->unk_000.unk_024.x;

        Vec3f_SetComponentsDuplicate(&arg0->unk_60.at, sp40, sp44, temp_s0->unk_000.unk_024.z);

        sp40 = gAnimDataSetC[gBattleScene.posX->unk_2C]->posX.x * gCameraOffsetTable[sp3B].x;
        sp3E = gAnimDataSetC[gBattleScene.posX->unk_2C]->unk_0C;
        tmp1 = (temp_s0->sideSign * gAnimDataSetC[gBattleScene.posX->unk_2C]->unk_0E) + BattleScene_GetParticipantFacingAngle(temp_s0);
        Camera_ComputeEyeFromAngles(&arg0->unk_60.at, &arg0->unk_60.eye, sp40, sp3E, tmp1);
        gBattleScene.posX->unk_20++;
    }
}

void BattleScene_CompleteSendOutCameraFade(UNUSED CameraStruct* arg0) {
    if (BattleScene_AdvanceCameraFrameCounter(0x50) != 0) {
        gBattleScene.posX->unk_40 = gBattleScene.posX->unk_2C + 1;
        BattleBox_Close();
        Audio_FadeOutAll(0x14);
    }
}

void BattleScene_CompleteSendOutExtendedFade(UNUSED CameraStruct* arg0) {
    if (BattleScene_AdvanceCameraFrameCounter(0x7D) != 0) {
        gBattleScene.posX->unk_40 = gBattleScene.posX->unk_2C + 1;
        Audio_FadeOutAll(0x14);
    }
}

void BattleScene_AdvanceSendOutFollowupCamera(CameraStruct* arg0) {
    UNUSED s32 pad[2];
    unk_BattlePlayerAnimState* sp24 = &sActivePokemon[!gBattleScene.posX->unk_2C]->animationState;
    unk_BattleAnimDataEntry* sp20 = &gAnimDataByPlayer[!gBattleScene.posX->unk_2C]->unk_B10;

    if (BattleAnim_IsAssetLoadBusy(sActivePokemon[!gBattleScene.posX->unk_2C]) == 0) {
        if (gBattleScene.posX->unk_14 == 0x1D) {
            BattleScene_SelectCameraShot(sActivePokemon[!gBattleScene.posX->unk_2C], arg0, 4);
        }

        if (BattleScene_AdvanceCameraFrameCounterUntil(0x1E) != 0) {
            BattleScene_ApproachCameraZoom(arg0, sActivePokemon[!gBattleScene.posX->unk_2C]);
        }

        if (((sp20->rotation >> 1) == (sActivePokemon[!gBattleScene.posX->unk_2C]->unk_000.unk_040.unk_08 >> 0x10)) &&
            (sp24->unk_2D != 0x12)) {
            BattleBox_Open(9);
        }

        if (sp20->unk_0A == ((sActivePokemon[!gBattleScene.posX->unk_2C]->unk_000.unk_040.unk_08 >> 0x10) + 3)) {
            sActivePokemon[!gBattleScene.posX->unk_2C]->unk_000.unk_000.posY &= ~0x20;
            Battle_SetRuntimeFlags(sActivePokemon[!gBattleScene.posX->unk_2C], 0x100);
            BattleScene_ResetCameraFrameCounter();
            BattleScene_UpdateCameraModelOffset(sActivePokemon[!gBattleScene.posX->unk_2C], arg0);
            gBattleScene.posX->unk_20 = 2;
        }

        BattleScene_ApproachCameraTarget(arg0, sActivePokemon[!gBattleScene.posX->unk_2C], 0);
    }
}

void BattleScene_PhaseSendOut(CameraStruct* arg0) {
    switch (gBattleScene.posX->unk_20) {
        case 0:
            BattleScene_AdvanceSendOutPreparation(arg0);
            break;

        case 1:
            BattleScene_AdvanceSendOutCamera(arg0);
            break;

        case 2:
            BattleScene_AdvanceSendOutCameraClose(arg0);
            break;

        case 3:
            BattleScene_FinishSendOutCameraClose(arg0);
            break;

        case 4:
            BattleScene_CompleteSendOutPresentation(arg0);
            break;

        case 5:
            UnusedBattleStateHandler(arg0);
            break;

        case 6:
            BattleScene_SetupSendOutOwnerShot(arg0);
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

void BattleScene_CompleteSendOutFollowup(UNUSED CameraStruct* arg0) {
    unk_BattlePlayerAnimState* sp1C = &sActivePokemon[!gBattleScene.posX->unk_2C]->animationState;

    if (BattleScene_AdvanceCameraFrameCounter(2) != 0) {
        BattleScene_ResetCameraFrameCounter();
        BattleScene_ClearPhaseFlag();
        gBattleScene.posX->unk_20 += 1;
        if (sp1C->unk_2D == 0x10) {
            gBattleScene.posX->unk_14 = 0;
            gBattleScene.posX->unk_20 = 0;
            gBattleScene.posX->unk_38 = 4;
        } else {
            gBattleScene.posX->unk_40 = gBattleScene.posX->unk_2C + 1;
        }
        Audio_FadeAndClearStoredSounds();
    }
}

void BattleScene_PhaseSendOutAfterFaint(CameraStruct* arg0) {
    switch (gBattleScene.posX->unk_20) {
        case 0:
            BattleScene_AdvanceSendOutPreparation(arg0);
            break;

        case 1:
            BattleScene_AdvanceSendOutCamera(arg0);
            break;

        case 2:
            BattleScene_AdvanceSendOutCameraClose(arg0);
            break;

        case 3:
            BattleScene_FinishSendOutCameraClose(arg0);
            break;

        case 4:
            BattleScene_CompleteSendOutFollowup(arg0);
            break;

        case 5:
            UnusedBattleStateHandler(arg0);
            break;

        case 10:
            BattleScene_AdvanceSendOutFollowupCamera(arg0);
            break;
    }
}

void BattleScene_ResetOwnerPresentationFlags(unk_BattlePlayerEntity* arg0) {
    unk_BattlePlayerAnimState* ptr = &arg0->animationState;

    if (ptr->unk_34 & 0x200) {
        arg0->unk_000.unk_024.y = gPokemonModelDimensions[BattleScene_GetParticipantSideIndex(arg0)].unk_08;
        Battle_ClearRuntimeFlags(arg0, 0x608);
    } else if (ptr->unk_34 & 0x4008) {
        arg0->unk_000.unk_01D = 0xFF;
        BattleAnim_StopOwnerCategoryParticles(4, arg0);
        arg0->unk_000.unk_024.y = gPokemonModelDimensions[BattleScene_GetParticipantSideIndex(arg0)].unk_08;
        arg0->unk_000.unk_000.posY &= ~0x2;
        arg0->unk_000.unk_000.posY |= 0x20;
        arg0->unk_000.unk_000.unk_01 |= 1;
        Battle_ClearRuntimeFlags(arg0, 0x4608);
    }
}

void BattleScene_InitializeIntroCamera(CameraStruct* arg0) {
    s32 sp24;
    unk_BattlePlayerAnimState* sp20 = &sActivePokemon[0]->animationState;
    unk_BattlePlayerAnimState* sp1C = &sActivePokemon[1]->animationState;

    BattleScene_ClearStateTickCallbacks();
    BattleScene_ResetAnimationStep();

    sp24 = BattleAnim_RandomRange(5);
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

    BattleAnim_Vec3fCopy(&gCameraPreset.posX, &gCameraFarSettings);
    BattleScene_LoadCameraPresetUnscaled(&gBattleCameraPresetTable2[sp24], arg0);
    BattleScene_ApplyCameraPreset(arg0, gCurrentPlayer, 0);
    gBattleScene.posX->unk_20++;
}

void BattleScene_AdvanceIntroCamera(CameraStruct* arg0) {
    if (BattleScene_AnimateCameraPreset(arg0, gCurrentPlayer, 0, 1) != 0) {
        BattleScene_SetPhase(arg0, 2);
    }
}

void BattleScene_PhaseIntro(CameraStruct* arg0) {
    switch (gBattleScene.posX->unk_20) {
        case 0:
            BattleScene_InitializeIntroCamera(arg0);
            break;

        case 1:
            BattleScene_AdvanceIntroCamera(arg0);
            break;
    }
}

void BattleScene_SetMonMoveResourceFlag(unk_BattlePlayerEntity* arg0) {
    arg0->animationState.unk_30 = 0x800;
}

void BattleScene_PrepareMoveResourcePresentation(UNUSED CameraStruct* arg0) {
    BattleAnim_CleanupEffects(2);
    BattleScene_SetMonMoveResourceFlag(gCurrentPlayer);
    BattleScene_LoadMoveResourceList(gCurrentPlayer);
}

void BattleScene_SelectActionCameraPreset(CameraStruct* arg0) {
    PokemonAudioInfo* sp1C = &sActivePokemon[gBattleScene.posX->unk_2C]->animationState.unk_38;
    unk_BattlePlayerAnimState* sp18 = &sActivePokemon[gBattleScene.posX->unk_2C]->animationState;
    s32 var_t0;

    if (gBattleScene.posX->unk_48 == 0xE) {
        var_t0 = BattleScene_GetMappedAnimationTimingField0D(sActivePokemon[gBattleScene.posX->unk_2C]);
    } else if ((gBattleScene.posX->unk_48 == 0x1C) || (gBattleScene.posX->unk_48 == 0x11) ||
               (gBattleScene.posX->unk_48 == 0x1F)) {
        var_t0 = 0;
    } else {
        var_t0 = BattleScene_GetAnimationTimingField0D(sActivePokemon[gBattleScene.posX->unk_2C]);
    }

    if ((sp1C->unk_5A == 0x3A) || (sp1C->unk_5A == 0x8F)) {
        if ((gBattleScene.posX->unk_48 != 0x1C) && (gBattleScene.posX->unk_48 != 0x11) &&
            (gBattleScene.posX->unk_48 != 0x1F)) {
            var_t0 = 0x16;
        }
    }

    switch (var_t0) {
        case 20:
            BattleScene_SelectCameraPreset(gCurrentPlayer, arg0,
                          gBattleScene.posX->unk_50 = gMoveIdSetA[BattleAnim_RandomIntWithWarmup(ARRAY_COUNT(gMoveIdSetA))], 1);
            break;

        case 21:
            BattleScene_SelectCameraPreset(gCurrentPlayer, arg0,
                          gBattleScene.posX->unk_50 = gMoveIdSetB[BattleAnim_RandomIntWithWarmup(ARRAY_COUNT(gMoveIdSetB))], 1);
            break;

        case 22:
            BattleScene_SelectCameraPreset(gCurrentPlayer, arg0,
                          gBattleScene.posX->unk_50 = gMoveIdSetC[BattleAnim_RandomIntWithWarmup(ARRAY_COUNT(gMoveIdSetC))], 1);
            break;

        case 23:
            BattleScene_SelectCameraPreset(gCurrentPlayer, arg0,
                          gBattleScene.posX->unk_50 = gMoveIdSetD[BattleAnim_RandomIntWithWarmup(ARRAY_COUNT(gMoveIdSetD))], 1);
            break;

        case 24:
            BattleScene_SelectCameraPreset(gCurrentPlayer, arg0,
                          gBattleScene.posX->unk_50 = gMoveIdSetE[BattleAnim_RandomIntWithWarmup(ARRAY_COUNT(gMoveIdSetE))], 1);
            break;

        default:
            BattleScene_SelectCameraPreset(gCurrentPlayer, arg0, gBattleScene.posX->unk_50 = var_t0, 1);
            if (sp18->unk_34 & 0x4000) {
                arg0->unk_60.at.y = 0.0f;
            }
            break;
    }
}

s32 BattleScene_AdvanceActionPresentationSetup(CameraStruct* arg0) {
    UNUSED s32 pad;
    unk_BattlePlayerAnimState* sp20 = &sActivePokemon[gBattleScene.posX->unk_2C]->animationState;

    BattleScene_ResetCameraFrameCounter();
    BattleScene_SelectActionCameraPreset(arg0);

    if (BattleScene_ActionPresentationTransitionCheck() != 0) {
        return 0;
    }

    if (gBattleScene.posX->unk_48 == 0x14) {
        BattleScene_EnterStateRow(sActivePokemon[gBattleScene.posX->unk_2C], 0x15);
    } else if (gBattleScene.posX->unk_48 == 0x18) {
        BattleScene_EnterStateRow(sActivePokemon[gBattleScene.posX->unk_2C], 3);
    } else if (sp20->unk_34 & 0x4400) {
        BattleScene_EnterStateRow(sActivePokemon[gBattleScene.posX->unk_2C], 3);
        BattleScene_SelectCameraPreset(sActivePokemon[gBattleScene.posX->unk_2C], arg0, gBattleScene.posX->unk_50 = 2, 1);
    } else {
        BattleScene_EnterStateRow(sActivePokemon[gBattleScene.posX->unk_2C], 3);
    }

    BattleScene_ClearPhaseFlag();
    return 1;
}

void BattleScene_ActionSetupCameraStep(CameraStruct* arg0) {
    unk_BattlePlayerAnimState* sp1C = &gCurrentPlayer->animationState;

    BattleAnim_ApproachF(&arg0->unk_24.fovy, 30.0f, 0.05f);

    switch (gBattleScene.posX->unk_3C) {
        case 0:
            BattleScene_CleanupParticipantEffectMode(sActivePokemon[0]);
            BattleScene_CleanupParticipantEffectMode(sActivePokemon[1]);

            if ((BattleScene_PrepareReplacementTransition() == 0) && (BattleScene_PrepareResidualStatusPresentation() == 0)) {
                Battle_ClearOpponentHopFlagAndSyncMove(gCurrentPlayer);
                BattleScene_PrepareMoveResourcePresentation(arg0);
                BattleScene_SetPhaseFlag();

                if ((gBattleScene.posX->unk_34 == 1) && (gOpponentPlayer->unk_4C8 == 1)) {
                    BattleScene_ResetOwnerPresentationFlags(gOpponentPlayer);
                }

                BattleAnim_GetOwnerDefaultAnchorPosition(gCurrentPlayer, &gCameraPreset.posX);

                if (sp1C->unk_34 & 0x4000) {
                    gCameraPreset.posX.y = 15.000001f;
                }

                if (gBattleScene.posX->unk_34 == 1) {
                    BattleScene_ResetCameraFov(arg0);

                    if ((gBattleScene.posX->unk_48 == 0x1C) || (gBattleScene.posX->unk_48 == 0x11) ||
                        (gBattleScene.posX->unk_48 == 0x1F)) {
                        BattleScene_SelectCameraFollowPreset(gCurrentPlayer, arg0, 3);
                    } else {
                        BattleScene_SelectCameraFollowPreset(gCurrentPlayer, arg0, 4);
                    }

                    if (sp1C->unk_34 & 0x4000) {
                        arg0->unk_60.at.y = 15.000001f;
                    }
                    Battle_ResetModelToIdleAnim(gCurrentPlayer);
                } else if ((gBattleScene.posX->unk_48 == 0x1C) || (gBattleScene.posX->unk_48 == 0x11) ||
                           (gBattleScene.posX->unk_48 == 0x1F)) {
                    BattleScene_LoadCameraPreset(&gCameraPosA, arg0, gCurrentPlayer);
                } else {
                    BattleScene_LoadCameraPreset(&gCameraPosB, arg0, gCurrentPlayer);
                }
            }
            break;

        case 1:
            if (BattleAnim_TryRegisterAssetTables(gCurrentPlayer) != 0) {
                gInitialMoveIndex = gCurrentMoveIndex = gTotalMoveCount;
                BattleBox_Open(0);
                BattleScene_ResetCameraFrameCounter();
                gBattleScene.posX->unk_3C += 1;
            }
            break;

        case 2:
            if (gBattleScene.posX->unk_34 == 1) {
                if ((gBattleScene.posX->unk_48 == 0x1C) || (gBattleScene.posX->unk_48 == 0x11) ||
                    (gBattleScene.posX->unk_48 == 0x1F)) {
                    if (BattleScene_AdvanceCameraFrameCounter(0xA) != 0) {
                        BattleScene_ResetCameraFov(arg0);
                        if (BattleScene_AdvanceActionPresentationSetup(arg0) != 0) {
                            gBattleScene.posX->unk_20 = 1;
                        }
                    }
                } else if (BattleScene_AdvanceCameraFrameCounter(0x28) != 0) {
                    BattleScene_ResetCameraFov(arg0);
                    if (BattleScene_AdvanceActionPresentationSetup(arg0) != 0) {
                        gBattleScene.posX->unk_20 = 1;
                    }
                }
            } else if (BattleScene_AnimateCameraPreset(arg0, gCurrentPlayer, 1, 1) != 0) {
                BattleScene_ResetCameraFov(arg0);
                if (BattleScene_AdvanceActionPresentationSetup(arg0) != 0) {
                    gBattleScene.posX->unk_20 = 1;
                }
            }
            break;
    }
}

void BattleScene_RefreshActionCameraPreset(CameraStruct* arg0) {
    s32 temp_v0;
    s32 temp_t0;

    if (gCurrentMoveIndex != gTotalMoveCount) {
        temp_v0 = BattleScene_GetAnimationTimingField0E(sActivePokemon[gBattleScene.posX->unk_2C]) & 0xFFFFFFFF;
        switch (temp_v0) {
            case 20:
                do {
                    temp_t0 = gMoveIdSetA[BattleAnim_RandomIntWithWarmup(5.0f)];
                } while (temp_t0 == gBattleScene.posX->unk_50);
                gBattleScene.posX->unk_50 = temp_t0;
                BattleScene_SelectCameraPreset(gCurrentPlayer, arg0, gBattleScene.posX->unk_50, 1);
                break;

            case 21:
                do {
                    temp_t0 = gMoveIdSetB[BattleAnim_RandomIntWithWarmup(4.0f)];
                } while (temp_t0 == gBattleScene.posX->unk_50);
                gBattleScene.posX->unk_50 = temp_t0;
                BattleScene_SelectCameraPreset(gCurrentPlayer, arg0, gBattleScene.posX->unk_50, 1);
                break;

            case 22:
                do {
                    temp_t0 = gMoveIdSetC[BattleAnim_RandomIntWithWarmup(3.0f)];
                } while (temp_t0 == gBattleScene.posX->unk_50);
                gBattleScene.posX->unk_50 = temp_t0;
                BattleScene_SelectCameraPreset(gCurrentPlayer, arg0, gBattleScene.posX->unk_50, 1);
                break;

            case 23:
                do {
                    temp_t0 = gMoveIdSetD[BattleAnim_RandomIntWithWarmup(6.0f)];
                } while (temp_t0 == gBattleScene.posX->unk_50);
                gBattleScene.posX->unk_50 = temp_t0;
                if (1) {}
                if (1) {}
                if (1) {}
                if (1) {}
                BattleScene_SelectCameraPreset(gCurrentPlayer, arg0, gBattleScene.posX->unk_50, 1);
                break;

            case 24:
                do {
                    temp_t0 = gMoveIdSetE[BattleAnim_RandomIntWithWarmup(4.0f)];
                } while (temp_t0 == gBattleScene.posX->unk_50);
                gBattleScene.posX->unk_50 = temp_t0;
                BattleScene_SelectCameraPreset(gCurrentPlayer, arg0, gBattleScene.posX->unk_50, 1);
                break;

            default:
                if (temp_v0 != gBattleScene.posX->unk_50) {
                    BattleScene_SelectCameraPreset(gCurrentPlayer, arg0, temp_v0, 1);
                }
                break;
        }
    }
}

void BattleScene_SelectActionCameraPresetFromTiming(CameraStruct* arg0, s32 arg1) {
    PokemonAudioInfo* sp1C = &sActivePokemon[gBattleScene.posX->unk_2C]->animationState.unk_38;
    s32 sp18;

    if ((gBattleScene.posX->unk_50 != 1) && (gBattleScene.posX->unk_50 != 4) && (gBattleScene.posX->unk_50 != 5) &&
        (gBattleScene.posX->unk_50 != 8) && (gBattleScene.posX->unk_50 != 9) && (gBattleScene.posX->unk_50 != 0xA) &&
        (gBattleScene.posX->unk_50 != 0xB)) {
        if (arg1 == 1) {
            sp18 = BattleScene_GetMappedAnimationTimingField0E(sActivePokemon[gBattleScene.posX->unk_2C]);
        } else {
            sp18 = BattleScene_GetAnimationTimingField0E(sActivePokemon[gBattleScene.posX->unk_2C]);
        }

        if ((sp1C->unk_5A == 0x3A) || (sp1C->unk_5A == 0x8F)) {
            sp18 = 0x19;
        }

        if (sp18 == 25) {
            return;
        }

        switch (sp18) {
            case 20:
                gBattleScene.posX->unk_50 = gMoveIdSetA[BattleAnim_RandomIntWithWarmup(ARRAY_COUNT(gMoveIdSetA))];
                if (sp18 != gBattleScene.posX->unk_50) {
                    BattleScene_SelectCameraPreset(gCurrentPlayer, arg0, gBattleScene.posX->unk_50, 1);
                }
                break;

            case 21:
                gBattleScene.posX->unk_50 = gMoveIdSetB[BattleAnim_RandomIntWithWarmup(ARRAY_COUNT(gMoveIdSetB))];
                if (sp18 != gBattleScene.posX->unk_50) {
                    BattleScene_SelectCameraPreset(gCurrentPlayer, arg0, gBattleScene.posX->unk_50, 1);
                }
                break;

            case 22:
                gBattleScene.posX->unk_50 = gMoveIdSetC[BattleAnim_RandomIntWithWarmup(ARRAY_COUNT(gMoveIdSetC))];
                if (sp18 != gBattleScene.posX->unk_50) {
                    BattleScene_SelectCameraPreset(gCurrentPlayer, arg0, gBattleScene.posX->unk_50, 1);
                }
                break;

            case 23:
                gBattleScene.posX->unk_50 = gMoveIdSetD[BattleAnim_RandomIntWithWarmup(ARRAY_COUNT(gMoveIdSetD))];
                if (sp18 != gBattleScene.posX->unk_50) {
                    BattleScene_SelectCameraPreset(gCurrentPlayer, arg0, gBattleScene.posX->unk_50, 1);
                }
                break;

            case 24:
                gBattleScene.posX->unk_50 = gMoveIdSetE[BattleAnim_RandomIntWithWarmup(ARRAY_COUNT(gMoveIdSetE))];
                if (sp18 != gBattleScene.posX->unk_50) {
                    BattleScene_SelectCameraPreset(gCurrentPlayer, arg0, gBattleScene.posX->unk_50, 1);
                }
                break;

            default:
                if (sp18 != gBattleScene.posX->unk_50) {
                    if (1) {}
                    BattleScene_SelectCameraPreset(gCurrentPlayer, arg0, sp18, 1);
                }
                break;
        }
    }
}

s32 BattleScene_ApplyActionCameraMode(CameraStruct* arg0, s32 arg1) {
    UNUSED s32 pad;
    s32 sp18 = 0;

    switch (gBattleScene.posX->unk_50) {
        case 1:
            BattleAnim_ApproachF(&arg0->unk_24.fovy, 60.0f, 0.03f);
            sp18 = 1;
            break;

        case 4:
        case 5:
        case 8:
        case 9:
        case 10:
        case 11:
            BattleScene_AnimateCameraPresetToOwner(arg0, gCurrentPlayer);
            sp18 = 1;
            break;

        default:
            if ((gCurrentPlayer->animationMode != 6) && (gCurrentPlayer->animationMode != 4) && (arg1 != 0)) {
                BattleScene_ReframeAndRecomputeDistance(arg0, gCurrentPlayer);
            }
            break;
    }
    return sp18;
}

void BattleScene_CleanupActionPresentation(UNUSED CameraStruct* arg0) {
    BattleScene_CleanupParticipantHideFlag(gCurrentPlayer);
    Battle_ClearRuntimeFlags(gCurrentPlayer, 0x10);
    if (BattleScene_ActionPresentationCleanupCheck() == 0) {
        gBattleScene.posX->unk_20 = 2;
    }
    BattleAnim_CleanupEffects(1);
}

s32 BattleScene_WaitForActionCameraDuration(UNUSED CameraStruct* arg0) {
    if (BattleScene_AdvanceCameraFrameCounter(BattleScene_GetCameraShotDuration(gCurrentPlayer)) != 0) {
        return 1;
    }
    return 0;
}

void BattleScene_ActionSetupAnimationDefault(CameraStruct* arg0) {
    switch (gBattleScene.posX->unk_3C) {
        case 0:
            BattleScene_ApplyActionCameraMode(arg0, 1);
            if (BattleScene_WaitForActionCameraDuration(arg0) != 0) {
                BattleScene_ResetCameraFrameCounter();
                BattleScene_SetPhaseFlag();
                BattleScene_SelectActionCameraPresetFromTiming(arg0, 0);
            }
            break;

        case 1:
            BattleScene_ApplyActionCameraMode(arg0, 1);
            if (Battle_IsRowAnimationSettled(gCurrentPlayer, 0x32) != 0) {
                BattleScene_ResetCameraFrameCounter();
                BattleScene_ClearPhaseFlag();
                BattleScene_CleanupActionPresentation(arg0);
            }
            break;
    }
}

void BattleScene_ActionSetupAnimationVariantA(CameraStruct* arg0) {
    switch (gBattleScene.posX->unk_3C) {
        case 0:
            BattleScene_ReframeAndRecomputeDistance(arg0, gCurrentPlayer);
            if (Battle_IsRowAnimationSettled(gCurrentPlayer, 0x32) != 0) {
                BattleScene_SaveCameraFov(arg0);
                gCurrentMoveIndex--;
                BattleScene_RefreshActionCameraPreset(arg0);
                if ((gCurrentMoveIndex < 0) || (gBattleMoveFailed != 0)) {
                    gCurrentMoveIndex = gTotalMoveCount;
                    gBattleScene.posX->unk_3C++;
                } else {
                    BattleScene_EnterStateRow(sActivePokemon[gBattleScene.posX->unk_2C], 0x13);
                    Audio_FadeAndClearStoredSounds();
                    BattleAnim_CleanupEffects(1);
                    gBattleScene.posX->unk_3C = 0;
                }
            }
            break;

        case 1:
            BattleScene_ReframeAndRecomputeDistance(arg0, gCurrentPlayer);
            BattleScene_ResetCameraFrameCounter();
            BattleScene_ClearPhaseFlag();
            gBattleScene.posX->unk_48 = 0;
            Audio_FadeAndClearStoredSounds();
            BattleScene_CleanupActionPresentation(arg0);
            break;
    }
}

void BattleScene_ActionSetupAnimationVariantB(CameraStruct* arg0) {
    switch (gBattleScene.posX->unk_3C) {
        case 0:
            if (BattleScene_AdvanceCameraFrameCounter(0xF) != 0) {
                BattleAnim_QueueEffectList(7, gCurrentPlayer);
                BattleScene_ResetCameraFrameCounter();
                BattleScene_SetPhaseFlag();
                BattleScene_SelectCameraFollowPreset(gCurrentPlayer, arg0, 3);
            }
            break;

        case 1:
            BattleScene_ReframeAndRecomputeDistance(arg0, gCurrentPlayer);
            if (Battle_IsRowAnimationSettled(gCurrentPlayer, 0x1E) != 0) {
                BattleScene_ResetCameraFrameCounter();
                BattleScene_ClearPhaseFlag();
                BattleScene_CleanupActionPresentation(arg0);
            }
            break;
    }
}

void BattleScene_ActionSetupAnimationVariantC(CameraStruct* arg0) {
    UNUSED s32 pad;
    PokemonAudioInfo* sp18 = &gCurrentPlayer->animationState.unk_38;

    BattleScene_GetParticipantSideIndex(gCurrentPlayer);

    switch (gBattleScene.posX->unk_3C) {
        case 0:
            BattleScene_ResetCameraFrameCounter();
            BattleScene_SetPhaseFlag();
            Vec3f_SetComponentsDuplicate(&gCameraPreset.posX, gCurrentPlayer->sideSign * -175.0f, 25.0f, 0.0f);
            BattleScene_LoadCameraPreset(&gCameraPosC, arg0, gCurrentPlayer);
            if ((gCurrentPlayer->unk_000.unk_01A != 0x33) && (gCurrentPlayer->unk_000.unk_01A != 0x32)) {
                BattleAnim_PlayMoveEffectScriptA(gCurrentPlayer, sp18->unk_5A);
            }
            break;

        case 1:
            if (BattleScene_AnimateCameraPreset(arg0, gCurrentPlayer, 1, 0) != 0) {
                BattleScene_ResetCameraFrameCounter();
                BattleScene_ClearPhaseFlag();
                BattleScene_CleanupActionPresentation(arg0);
            }
            break;
    }
}

void BattleScene_ActionSetupAnimationVariantD(CameraStruct* arg0) {
    switch (gBattleScene.posX->unk_3C) {
        case 0:
            BattleScene_ResetCameraFrameCounter();
            BattleScene_SetPhaseFlag();
            BattleAnim_GetOwnerDefaultAnchorPosition(gCurrentPlayer, &gCameraPreset.posX);
            BattleScene_LoadCameraPreset(&gCameraPosD, arg0, gCurrentPlayer);
            break;

        case 1:
            BattleScene_AnimateCameraPresetToOwner(arg0, gCurrentPlayer);
            if (Battle_IsRowAnimationSettled(gCurrentPlayer, 0x1E) != 0) {
                BattleScene_ResetCameraFrameCounter();
                BattleScene_ClearPhaseFlag();
                BattleScene_CleanupActionPresentation(arg0);
            }
            break;
    }
}

void BattleScene_ActionSetupAnimationStep(CameraStruct* arg0) {
    unk_BattlePlayerAnimState* temp_a2 = &sActivePokemon[gBattleScene.posX->unk_2C]->animationState;
    u32 var_v1 = 0;

    if (gBattleScene.posX->unk_48 == 0x18) {
        var_v1 = 0xA;
    } else if (gBattleScene.posX->unk_48 == 0x14) {
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
            BattleScene_ActionSetupAnimationDefault(arg0);
            break;

        case 10:
            BattleScene_ActionSetupAnimationVariantA(arg0);
            break;

        case 11:
            BattleScene_ActionSetupAnimationVariantB(arg0);
            break;

        case 12:
            BattleScene_ActionSetupAnimationVariantC(arg0);
            break;

        case 13:
            BattleScene_ActionSetupAnimationVariantD(arg0);
            break;

        default:
            BattleScene_ActionSetupAnimationDefault(arg0);
            break;
    }
}

void BattleScene_StopSpecialOwnerAnimation(unk_BattlePlayerEntity* arg0) {
    if (arg0->animationState.unk_38.unk_5A == 0x45) {
        BattleAnim_ResetOwnerFacingAndExitStatusIdle(arg0);
    }
}

s32 BattleScene_IsSpecialOwnerAnimation(unk_BattlePlayerEntity* arg0) {
    if (arg0->animationState.unk_38.unk_5A == 0x53) {
        return 1;
    }
    return 0;
}

void BattleScene_CompleteHpUpdateTransition(CameraStruct* arg0, s32* arg1, s32* arg2) {
    if ((*arg1 == 1) && (*arg2 == 1)) {
        BattleBox_Close();
        Battle_ResetModelToIdleAnim(gCurrentPlayer);
        gBattleScene.posX->unk_1A = 0;
        BattleScene_ResetCameraFrameCounter();
        BattleScene_ResetCameraSubstepCounter();
        BattleScene_ClearPhaseFlag();
        BattleScene_ResetAnimationStep();
        BattleScene_UpdateDisplayedHpAndTransition(arg0);
    }
}

void BattleScene_RunBasicHpTransition(CameraStruct* arg0) {
    switch (gBattleScene.posX->unk_3C) {
        case 0:
            if (BattleScene_AdvanceOwnerAnimation98(gOpponentPlayer) == 0) {
                BattleScene_SelectCameraShot(gOpponentPlayer, arg0, 0);
                BattleScene_ResetCameraFrameCounter();
                BattleScene_SetPhaseFlag();
                BattleScene_EnterStateRow(gCurrentPlayer, 0xE);
                BattleScene_CleanupOpponentSpecialAnimFlag(gOpponentPlayer);
                Battle_ApplyAnimStateEffects(gOpponentPlayer);
                BattleBox_Open(1);
            }
            break;

        case 1:
            BattleScene_FrameCamera(arg0, gOpponentPlayer);
            if ((BattleScene_IsOpponentRowCheckpointReached(gOpponentPlayer) != 0) || (BattleScene_AdvanceCameraFrameCounter(0x5A) != 0)) {
                gPlayer0ReadyFlag = BattleScene_AnimateDisplayedHpToRuntime(gOpponentPlayer);
                gPlayer1ReadyFlag = BattleScene_AnimateDisplayedHpToRuntime(gCurrentPlayer);
                BattleScene_CompleteHpUpdateTransition(arg0, &gPlayer0ReadyFlag, &gPlayer1ReadyFlag);
            }
            break;
    }
}

void BattleScene_RunConditionalHpTransition(CameraStruct* arg0) {
    s32 sp1C;

    switch (gBattleScene.posX->unk_3C) {
        case 0:
            if (BattleScene_AdvanceOwnerAnimation98(gOpponentPlayer) == 0) {
                Battle_ApplyAnimStateEffects(gOpponentPlayer);
                BattleScene_SelectCameraShot(gOpponentPlayer, arg0, 0);
                BattleScene_ResetCameraFrameCounter();
                BattleScene_SetPhaseFlag();
                BattleScene_EnterStateRow(gCurrentPlayer, 0xB);
                BattleScene_CleanupOpponentSpecialAnimFlag(gOpponentPlayer);
                BattleBox_Open(1);
            }
            break;

        case 1:
            BattleScene_FrameCamera(arg0, gOpponentPlayer);
            gPlayer0ReadyFlag = BattleScene_AnimateDisplayedHpToRuntime(gOpponentPlayer);
            gPlayer1ReadyFlag = BattleScene_AnimateDisplayedHpToRuntime(gCurrentPlayer);
            sp1C = GetAnimStateResultCode(gCurrentPlayer);
            if ((sp1C == 2) && ((BattleScene_IsOpponentRowCheckpointReached(gOpponentPlayer) != 0) || (BattleScene_AdvanceCameraFrameCounter(0x64) != 0))) {
                BattleScene_CompleteHpUpdateTransition(arg0, &gPlayer0ReadyFlag, &gPlayer1ReadyFlag);
            } else if (sp1C == 1) {
                BattleScene_CompleteHpUpdateTransition(arg0, &gPlayer0ReadyFlag, &gPlayer1ReadyFlag);
            }
            break;
    }
}

void BattleScene_RunMoveEffectEndHpTransition(CameraStruct* arg0) {
    PokemonAudioInfo* sp34 = &gCurrentPlayer->animationState.unk_38;
    UNUSED s32 pad;
    UNUSED s16 pad2;
    s16 sp2C;

    switch (gBattleScene.posX->unk_3C) {
        case 0:
            if (BattleScene_AdvanceOwnerAnimation98(gOpponentPlayer) == 0) {
                Battle_ApplyAnimStateEffects(gOpponentPlayer);
                BattleScene_SelectCameraShot(gOpponentPlayer, arg0, 0);
                BattleScene_ResetCameraFrameCounter();
                BattleScene_SetPhaseFlag();
                BattleScene_CleanupOpponentSpecialAnimFlag(gOpponentPlayer);
                BattleBox_Open(1);
                sp2C = Battle_GetSideAnimTableFieldB(gOpponentPlayer);
                BattleAnim_QueueMoveEffectEnd(sp34->unk_5A, gCurrentPlayer, gOpponentPlayer, sp2C, Battle_GetSideAnimTableFieldC(gOpponentPlayer));
                BattleScene_SetParticipantModelFlags(gOpponentPlayer, 0x10, 0);
            }
            break;

        case 1:
            BattleScene_FrameCamera(arg0, gOpponentPlayer);
            gPlayer0ReadyFlag = BattleScene_AnimateDisplayedHpToRuntime(gOpponentPlayer);
            gPlayer1ReadyFlag = BattleScene_AnimateDisplayedHpToRuntime(gCurrentPlayer);
            if ((BattleScene_IsOpponentRowCheckpointReached(gOpponentPlayer) != 0) || (BattleScene_AdvanceCameraFrameCounter(0x5A) != 0)) {
                BattleScene_CompleteHpUpdateTransition(arg0, &gPlayer0ReadyFlag, &gPlayer1ReadyFlag);
            }
            break;
    }
}

void BattleScene_RunActionEffectHpTransition(CameraStruct* arg0) {
    PokemonAudioInfo* sp24 = &gOpponentPlayer->animationState.unk_38;
    UNUSED s32 pad;
    s32 sp1C;
    s32 temp_v0;
    s32 var_a0;

    switch (gBattleScene.posX->unk_3C) {
        case 0:
            if (BattleScene_AdvanceOwnerAnimation98(gOpponentPlayer) == 0) {
                BattleScene_StopSpecialOwnerAnimation(gCurrentPlayer);
                BattleBox_Open(1);
                BattleScene_ResetCameraFrameCounter();
                BattleScene_SetPhaseFlag();
                BattleScene_SetDamageShakeAmplitude(gOpponentPlayer);
                if (gBattleScene.posX->unk_1A == 3) {
                    BattleScene_EnterStateRow(gCurrentPlayer, 0xB);
                } else {
                    BattleScene_EnterStateRow(gCurrentPlayer, 4);
                }
                BattleScene_SelectCameraShot(gOpponentPlayer, arg0, 0);
                Battle_ApplyAnimStateEffects(gOpponentPlayer);
                BattleScene_CleanupOpponentSpecialAnimFlag(gOpponentPlayer);
                BattleAnim_ClearFreezeStatusAnimationIfThawed(gOpponentPlayer);
            }
            break;

        case 1:
            if (BattleScene_AdvanceCameraFrameCounter(5) != 0) {
                BattleScene_ResetOwnerPresentationFlags(gCurrentPlayer);
                gBattleScene.posX->unk_3C++;
            }
            break;

        case 2:
            BattleScene_ResetAnimationStep();
            gPlayer0ReadyFlag = BattleScene_AnimateDisplayedHpToRuntime(gOpponentPlayer);
            gPlayer1ReadyFlag = BattleScene_AnimateDisplayedHpToRuntime(gCurrentPlayer);
            if (sp24->unk_0C != 0) {
                if (BattleScene_IsOpponentRowCheckpointReached(gOpponentPlayer) != 0) {
                    gBattleScene.posX->unk_3C = 4;
                } else if (BattleScene_IsRowAnimWaitComplete(gOpponentPlayer, 2) != 0) {
                    gBattleScene.posX->unk_3C = 5;
                } else if (BattleScene_FrameCamera(arg0, gOpponentPlayer) != 0) {
                    gBattleScene.posX->unk_3C = 3;
                }
            } else if (BattleScene_FrameCamera(arg0, gOpponentPlayer) != 0) {
                gBattleScene.posX->unk_3C = 4;
            }
            break;

        case 3:
            gPlayer0ReadyFlag = BattleScene_AnimateDisplayedHpToRuntime(gOpponentPlayer);
            gPlayer1ReadyFlag = BattleScene_AnimateDisplayedHpToRuntime(gCurrentPlayer);
            BattleScene_FrameCamera(arg0, gOpponentPlayer);
            if (BattleScene_IsOpponentRowCheckpointReached(gOpponentPlayer) != 0) {
                gBattleScene.posX->unk_3C++;
            } else if (BattleScene_IsRowAnimWaitComplete(gOpponentPlayer, 0xF) != 0) {
                gBattleScene.posX->unk_3C++;
            }
            break;

        case 4:
            gPlayer0ReadyFlag = BattleScene_AnimateDisplayedHpToRuntime(gOpponentPlayer);
            gPlayer1ReadyFlag = BattleScene_AnimateDisplayedHpToRuntime(gCurrentPlayer);
            temp_v0 = BattleScene_FrameCamera(arg0, gOpponentPlayer);
            if ((gPlayer0ReadyFlag == 1) && (gPlayer1ReadyFlag == 1) && (temp_v0 != 0) && (BattleScene_AdvanceCameraFrameCounter(0xF) != 0)) {
                gBattleScene.posX->unk_3C = 6;
            }
            break;

        case 5:
            gPlayer0ReadyFlag = BattleScene_AnimateDisplayedHpToRuntime(gOpponentPlayer);
            gPlayer1ReadyFlag = BattleScene_AnimateDisplayedHpToRuntime(gCurrentPlayer);
            sp1C = BattleScene_FrameCamera(arg0, gOpponentPlayer);
            if ((BattleScene_IsSpecialOwnerAnimation(gCurrentPlayer) != 0) && ((gAnimTimer < 0xA) || (gBattleMoveFailed != 0)) &&
                !(sp24->unk_15 & 0x20)) {
                var_a0 = 0x5A;
            } else {
                var_a0 = 0xF;
            }

            if ((gPlayer0ReadyFlag == 1) && (gPlayer1ReadyFlag == 1) && (sp1C != 0) && (BattleScene_AdvanceCameraFrameCounter(var_a0) != 0)) {
                gBattleScene.posX->unk_3C++;
            }
            break;

        case 6:
            if (BattleScene_AdvanceOwnerAnimationAndClearFlags(gOpponentPlayer) == 0) {
                gPlayer0ReadyFlag = BattleScene_AnimateDisplayedHpToRuntime(gOpponentPlayer);
                gPlayer1ReadyFlag = BattleScene_AnimateDisplayedHpToRuntime(gCurrentPlayer);
                BattleScene_FrameCamera(arg0, gOpponentPlayer);
                BattleScene_CompleteHpUpdateTransition(arg0, &gPlayer0ReadyFlag, &gPlayer1ReadyFlag);
            }
            break;
    }
}

void func_84324404(void) {
}

void func_8432440C(void) {
}

void BattleScene_RunRepeatedHitHpTransition(CameraStruct* arg0) {
    PokemonAudioInfo* sp24 = &gCurrentPlayer->animationState.unk_38;
    unk_BattleAnimDataEntry* temp_v1 = &gAnimDataByPlayer[BattleScene_GetParticipantSideIndex(gOpponentPlayer)]->unk_000[sp24->unk_5A - 1];
    volatile s32 sp1C;
    s32 temp_v0_2;

    if (gOpponentPlayer->unk_000.unk_01A == 0x98) {
        sp1C = 0xF;
    } else if (temp_v1->unk_0A == 0xFF) {
        sp1C = gCurrentPlayer->unk_000.unk_040.rotation->unk_0A - temp_v1->unk_06;
    } else {
        sp1C = temp_v1->unk_0A - temp_v1->unk_06;
    }

    switch (gBattleScene.posX->unk_3C) {
        case 0:
            if (BattleScene_AdvanceOwnerAnimation98(gOpponentPlayer) == 0) {
                BattleScene_ResetAnimationStep();
                BattleScene_SetDamageShakeAmplitude(gOpponentPlayer);
                BattleScene_EnterStateRow(gCurrentPlayer, 4);
                gCurrentMoveIndex--;
                BattleScene_SelectCameraShot(gOpponentPlayer, arg0, gCurrentMoveIndex + 1);
                if (gCurrentMoveIndex < 0) {
                    BattleScene_SelectCameraShot(gOpponentPlayer, arg0, gCurrentMoveIndex + 1);
                    BattleScene_FrameCamera(arg0, gOpponentPlayer);
                    Battle_ApplyAnimStateEffects(gOpponentPlayer);
                    BattleScene_ResetCameraFrameCounter();
                    gBattleScene.posX->unk_3C = 2;
                    BattleScene_CleanupOpponentSpecialAnimFlag(gOpponentPlayer);
                    BattleBox_Open(1);
                } else {
                    gBattleScene.posX->unk_3C++;
                }
            }
            break;

        case 1:
            BattleScene_ReframeAndRecomputeDistance(arg0, gOpponentPlayer);
            if (BattleScene_AdvanceCameraFrameCounter(sp1C) != 0) {
                Audio_FadeAndClearStoredSounds();
                BattleAnim_CleanupEffects(1);
                gBattleScene.posX->unk_3C = 0;
            }
            break;

        case 2:
            gPlayer0ReadyFlag = BattleScene_AnimateDisplayedHpToRuntime(gOpponentPlayer);
            gPlayer1ReadyFlag = BattleScene_AnimateDisplayedHpToRuntime(gCurrentPlayer);

            if (sp24->unk_0C != 0) {
                if (BattleScene_IsOpponentRowCheckpointReached(gOpponentPlayer) != 0) {
                    gBattleScene.posX->unk_3C = 5;
                }

                if (BattleScene_IsRowAnimWaitComplete(gOpponentPlayer, 0xF) != 0) {
                    gBattleScene.posX->unk_3C = 5;
                }

                if (BattleScene_FrameCamera(arg0, gOpponentPlayer) != 0) {
                    gBattleScene.posX->unk_3C = 4;
                }
            } else if (BattleScene_FrameCamera(arg0, gOpponentPlayer) != 0) {
                BattleScene_ResetCameraFrameCounter();
                gBattleScene.posX->unk_3C = 5;
            }
            break;

        case 3:
            gPlayer0ReadyFlag = BattleScene_AnimateDisplayedHpToRuntime(gOpponentPlayer);
            gPlayer1ReadyFlag = BattleScene_AnimateDisplayedHpToRuntime(gCurrentPlayer);

            if (BattleScene_IsOpponentRowCheckpointReached(gOpponentPlayer) != 0) {
                gBattleScene.posX->unk_3C = 5;
            }

            if (BattleScene_FrameCamera(arg0, gOpponentPlayer) != 0) {
                gBattleScene.posX->unk_3C = 9;
            }
            break;

        case 4:
            gPlayer0ReadyFlag = BattleScene_AnimateDisplayedHpToRuntime(gOpponentPlayer);
            gPlayer1ReadyFlag = BattleScene_AnimateDisplayedHpToRuntime(gCurrentPlayer);

            if (BattleScene_IsOpponentRowCheckpointReached(gOpponentPlayer) != 0) {
                gBattleScene.posX->unk_3C = 5;
            }

            BattleScene_FrameCamera(arg0, gOpponentPlayer);

            if (BattleScene_IsRowAnimWaitComplete(gOpponentPlayer, 0xF) != 0) {
                gBattleScene.posX->unk_3C++;
            }
            break;

        case 5:
            gPlayer0ReadyFlag = BattleScene_AnimateDisplayedHpToRuntime(gOpponentPlayer);
            gPlayer1ReadyFlag = BattleScene_AnimateDisplayedHpToRuntime(gCurrentPlayer);
            temp_v0_2 = BattleScene_FrameCamera(arg0, gOpponentPlayer);
            if ((gPlayer0ReadyFlag == 1) && (gPlayer1ReadyFlag == 1) && (temp_v0_2 != 0) && (BattleScene_AdvanceCameraFrameCounter(0xF) != 0)) {
                gBattleScene.posX->unk_3C++;
            }
            break;

        case 6:
            if (BattleScene_AdvanceOwnerAnimationAndClearFlags(gOpponentPlayer) == 0) {
                gPlayer0ReadyFlag = BattleScene_AnimateDisplayedHpToRuntime(gOpponentPlayer);
                gPlayer1ReadyFlag = BattleScene_AnimateDisplayedHpToRuntime(gCurrentPlayer);
                BattleScene_FrameCamera(arg0, gOpponentPlayer);
                BattleScene_CompleteHpUpdateTransition(arg0, &gPlayer0ReadyFlag, &gPlayer1ReadyFlag);
            }
            break;
    }
}

void BattleScene_ActionSetupFinalizeStep(CameraStruct* arg0) {
    BattleScene_ResetCameraFov(arg0);
    Battle_ApplyAnimStateEffects(sActivePokemon[!gBattleScene.posX->unk_2C]);
    if (gBattleScene.posX->unk_48 == 0x16) {
        BattleScene_RunBasicHpTransition(arg0);
    } else if (gBattleScene.posX->unk_48 == 0x20) {
        BattleScene_RunMoveEffectEndHpTransition(arg0);
    } else if (gBattleScene.posX->unk_48 == 0x1A) {
        BattleScene_RunConditionalHpTransition(arg0);
    } else if (gBattleScene.posX->unk_1A == 1) {
        BattleScene_RunRepeatedHitHpTransition(arg0);
    } else {
        BattleScene_RunActionEffectHpTransition(arg0);
    }
}

void BattleScene_Phase2(CameraStruct* arg0) {
    switch (gBattleScene.posX->unk_20) {
        case 0:
            BattleScene_ActionSetupCameraStep(arg0);
            break;

        case 1:
            BattleScene_ActionSetupAnimationStep(arg0);
            break;

        case 2:
            BattleScene_ActionSetupFinalizeStep(arg0);
            break;
    }
}

void BattleScene_Phase3(CameraStruct* arg0) {
    switch (gBattleScene.posX->unk_20) {
        case 0:
            BattleScene_ActionSetupCameraStep(arg0);
            break;

        case 1:
            BattleScene_ActionSetupAnimationStep(arg0);
            break;

        case 2:
            BattleScene_ActionSetupFinalizeStep(arg0);
            break;
    }
}

s32 BattleScene_PhaseSelectMoveAnim(void) {
    BattleScene_ApplyActionCameraMode(gBattleScene.posX->unk_DC, 0);

    if (BattleScene_AdvanceCameraFrameCounter(BattleScene_GetCameraShotDuration(gCurrentPlayer)) == 0) {
        return 0;
    }

    if ((gBattleScene.posX->unk_48 != 0x1E) && (gBattleScene.posX->unk_48 != 0x27)) {
        BattleBox_Open(3);
    }

    if (gBattleScene.posX->unk_48 == 0x1B) {
        QueuePlayerDefeatMessage(BattleScene_GetParticipantDisplayPlayerNumber(gCurrentPlayer));
    }

    switch (gBattleScene.posX->unk_48) {
        case 7:
            return BattleScene_TransitionToPhaseFull(7);

        case 21:
            return BattleScene_TransitionToPhaseFull(7);

        case 39:
            return BattleScene_TransitionToPhaseFull(7);

        case 27:
            return BattleScene_TransitionToPhaseFull(0x1B);

        case 30:
            return BattleScene_TransitionToPhaseFull(0x1E);

        case 28:
            return BattleScene_TransitionToPhaseFull(0x1C);

        case 15:
            return BattleScene_TransitionToPhaseFull(0xF);

        case 25:
            return BattleScene_TransitionToPhaseFull(0x19);

        case 29:
            return BattleScene_TransitionToPhaseFull(0x1D);

        case 38:
            return BattleScene_TransitionToPhaseFull(0x26);

        case 12:
            return BattleScene_TransitionToPhaseFull(0xC);

        case 13:
            return BattleScene_TransitionToPhaseFull(0xD);

        case 14:
            return BattleScene_TransitionToPhaseFull(0xE);

        case 17:
            return BattleScene_TransitionToPhaseFull(0x11);

        case 31:
            return BattleScene_TransitionToPhaseFull(0x1F);
    }

    return 0;
}

void BattleScene_Phase7(CameraStruct* arg0) {
    PokemonAudioInfo* sp1C = &gCurrentPlayer->animationState.unk_38;
    unk_BattleAnimDataEntry* sp18 = &gAnimDataByPlayer[BattleScene_GetParticipantSideIndex(gCurrentPlayer)]->unk_000[sp1C->unk_5A - 1];

    switch (gBattleScene.posX->unk_20) {
        case 0:
            BattleScene_SaveCameraFov(arg0);
            BattleScene_SelectActionCameraPresetFromTiming(arg0, 0);
            BattleScene_ResetCameraFrameCounter();
            BattleScene_ResetCameraSubstepCounter();
            if (sp18->rotation < 0x15) {
                Battle_ApplyAnimStateEffects(gCurrentPlayer);
            }
            gBattleScene.posX->unk_20++;
            break;

        case 1:
            BattleScene_ApplyActionCameraMode(arg0, 1);
            if (gCurrentPlayer->animationStateIndex == (sp18->rotation + 1)) {
                Battle_ApplyAnimStateEffects(gCurrentPlayer);
            }

            if (gCurrentPlayer->animationStateIndex >= (sp18->rotation + 0xA)) {
                gPlayer0ReadyFlag = BattleScene_AnimateDisplayedHpToRuntime(sActivePokemon[gBattleScene.posX->unk_2C]);
                gPlayer1ReadyFlag = BattleScene_AnimateDisplayedHpToRuntime(sActivePokemon[!gBattleScene.posX->unk_2C]);
            }

            if ((gCurrentPlayer->animationStateIndex == (sp18->rotation + 0x12)) && (sp1C->unk_5A == 0x64)) {
                BattleBox_Open(0xF);
            }

            if (Battle_IsRowAnimationSettled(gCurrentPlayer, 0x3C) != 0) {
                BattleScene_ResetCameraFrameCounter();
                gBattleScene.posX->unk_20++;
            }
            break;

        case 2:
            if (gCurrentPlayer->animationStateIndex == (sp18->rotation + 1)) {
                Battle_ApplyAnimStateEffects(gCurrentPlayer);
            }
            BattleScene_ApplyActionCameraMode(arg0, 1);
            gPlayer0ReadyFlag = BattleScene_AnimateDisplayedHpToRuntime(sActivePokemon[gBattleScene.posX->unk_2C]);
            gPlayer1ReadyFlag = BattleScene_AnimateDisplayedHpToRuntime(sActivePokemon[!gBattleScene.posX->unk_2C]);
            if ((gPlayer0ReadyFlag == 1) && (gPlayer1ReadyFlag == 1) && (BattleScene_AdvanceCameraFrameCounter(0xF) != 0)) {
                if ((gOpponentPlayer->animationState.unk_38.unk_5A & 0xF0) == 0xF0) {
                    gBattleScene.posX->unk_34 = 3;
                }
                BattleScene_ResetCameraFrameCounter();
                BattleScene_ResetAnimationStep();
                BattleScene_WaitForDisplayedHpAnimations(arg0);
            }
            break;
    }
}

void BattleScene_Phase38(CameraStruct* arg0) {
    switch (gBattleScene.posX->unk_20) {
        case 0:
            BattleScene_SaveCameraFov(arg0);
            BattleScene_SetCameraOwnerShot(arg0, gCurrentPlayer);
            BattleScene_UpdateCameraModelOffset(gCurrentPlayer, arg0);
            Battle_ApplyAnimStateEffects(gCurrentPlayer);
            BattleScene_ResetCameraFrameCounter();
            BattleScene_ResetCameraSubstepCounter();
            gBattleScene.posX->unk_20++;
            break;

        case 1:
            if (Battle_IsRowAnimationSettled(gCurrentPlayer, 0x3C) != 0) {
                gBattleScene.posX->unk_20 += 1;
            }
            break;

        case 2:
            gPlayer0ReadyFlag = BattleScene_AnimateDisplayedHpToRuntime(sActivePokemon[gBattleScene.posX->unk_2C]);
            gPlayer1ReadyFlag = BattleScene_AnimateDisplayedHpToRuntime(sActivePokemon[!gBattleScene.posX->unk_2C]);
            if ((gOpponentPlayer->animationState.unk_38.unk_5A & 0xF0) == 0xF0) {
                gBattleScene.posX->unk_34 = 3;
            }
            BattleScene_ResetCameraFrameCounter();
            BattleScene_ResetAnimationStep();
            BattleScene_WaitForDisplayedHpAnimations(arg0);
            break;
    }
}

void BattleScene_Phase27(CameraStruct* arg0) {
    switch (gBattleScene.posX->unk_20) {
        case 0:
            BattleScene_SaveCameraFov(arg0);
            Battle_ApplyAnimStateEffects(gCurrentPlayer);
            BattleScene_SelectActionCameraPresetFromTiming(arg0, 0);
            BattleScene_ResetCameraFrameCounter();
            gBattleScene.posX->unk_20++;
            break;

        case 1:
            BattleScene_ApplyActionCameraMode(arg0, 1);
            if (BattleScene_AdvanceCameraFrameCounter(0x28) != 0) {
                gBattleScene.posX->unk_20 += 1;
            }
            break;

        case 2:
            BattleScene_ApplyActionCameraMode(arg0, 1);
            gPlayer0ReadyFlag = BattleScene_AnimateDisplayedHpToRuntime(sActivePokemon[gBattleScene.posX->unk_2C]);
            gPlayer1ReadyFlag = BattleScene_AnimateDisplayedHpToRuntime(sActivePokemon[!gBattleScene.posX->unk_2C]);
            if ((gOpponentPlayer->animationState.unk_38.unk_5A & 0xF0) == 0xF0) {
                gBattleScene.posX->unk_34 = 3;
            }
            BattleScene_ResetCameraFrameCounter();
            BattleScene_ResetAnimationStep();
            BattleScene_WaitForDisplayedHpAnimations(arg0);
            break;
    }
}

void BattleScene_Phase30(CameraStruct* arg0) {
    PokemonAudioInfo* sp1C = &gOpponentPlayer->animationState.unk_38;

    switch (gBattleScene.posX->unk_20) {
        case 0:
            Battle_ClearRuntimeFlags(gCurrentPlayer, 0x1800);
            BattleScene_SaveCameraFov(arg0);
            BattleScene_ResetCameraFrameCounter();
            BattleScene_SelectActionCameraPresetFromTiming(arg0, 0);
            Battle_ApplyAnimStateEffects(gCurrentPlayer);
            BattleScene_ResetCameraFrameCounter();
            gBattleScene.posX->unk_20++;
            break;

        case 1:
            BattleScene_ApplyActionCameraMode(arg0, 1);
            if (Battle_IsRowAnimationSettled(gCurrentPlayer, 0x3C) != 0) {
                BattleScene_ResetCameraFrameCounter();
                gBattleScene.posX->unk_20++;
            }
            break;

        case 2:
            if (BattleScene_AdvanceOwnerAnimation98(gOpponentPlayer) == 0) {
                BattleAnim_CleanupEffects(1);
                Audio_FadeAndClearStoredSounds();
                BattleScene_SelectCameraShot(gOpponentPlayer, arg0, BattleAnim_RandomRange(2));
                BattleScene_EnterStateRow(gCurrentPlayer, 4);
                BattleScene_ResetCameraFrameCounter();
                gBattleScene.posX->unk_20++;
            }
            break;

        case 3:
            if (BattleScene_AdvanceOwnerAnimationAndClearFlags(gOpponentPlayer) == 0) {
                BattleScene_ReframeAndRecomputeDistance(arg0, gOpponentPlayer);
                if (gBattleScene.posX->unk_14 == 0) {
                    BattleBox_Open(1);
                }
                gPlayer0ReadyFlag = BattleScene_AnimateDisplayedHpToRuntime(sActivePokemon[gBattleScene.posX->unk_2C]);
                gPlayer1ReadyFlag = BattleScene_AnimateDisplayedHpToRuntime(sActivePokemon[!gBattleScene.posX->unk_2C]);
                if (BattleScene_AdvanceCameraFrameCounter(0x32) != 0) {
                    gBattleScene.posX->unk_20 += 1;
                }
                if (BattleScene_IsOpponentRowCheckpointReached(gOpponentPlayer) != 0) {
                    BattleScene_ResetCameraFrameCounter();
                    gBattleScene.posX->unk_20++;
                }
            }
            break;

        case 4:
            BattleScene_ReframeAndRecomputeDistance(arg0, gOpponentPlayer);
            gPlayer0ReadyFlag = BattleScene_AnimateDisplayedHpToRuntime(sActivePokemon[gBattleScene.posX->unk_2C]);
            gPlayer1ReadyFlag = BattleScene_AnimateDisplayedHpToRuntime(sActivePokemon[!gBattleScene.posX->unk_2C]);
            if ((gPlayer1ReadyFlag == 1) && (gPlayer0ReadyFlag == 1)) {
                if (sp1C->unk_0C != 0) {
                    BattleAnim_CleanupEffects(1);
                    Audio_FadeAndClearStoredSounds();
                    BattleScene_SelectCameraFollowPreset(gCurrentPlayer, arg0, 3);
                    gBattleScene.posX->unk_20++;
                } else {
                    if ((gOpponentPlayer->animationState.unk_38.unk_5A & 0xF0) == 0xF0) {
                        gBattleScene.posX->unk_34 = 3;
                    }
                    BattleScene_ResetCameraFrameCounter();
                    BattleScene_ResetAnimationStep();
                    BattleScene_SetPhase(arg0, 5);
                }
            }
            break;

        case 5:
            BattleScene_SelectCameraFollowPreset(gCurrentPlayer, arg0, 3);
            gPlayer0ReadyFlag = BattleScene_AnimateDisplayedHpToRuntime(sActivePokemon[gBattleScene.posX->unk_2C]);
            gPlayer1ReadyFlag = BattleScene_AnimateDisplayedHpToRuntime(sActivePokemon[!gBattleScene.posX->unk_2C]);
            if ((gOpponentPlayer->animationState.unk_38.unk_5A & 0xF0) == 0xF0) {
                gBattleScene.posX->unk_34 = 3;
            }
            BattleScene_ResetCameraFrameCounter();
            BattleScene_ResetAnimationStep();
            BattleScene_ResolveDisplayedHpCompletion(arg0);
            break;
    }
}

void BattleScene_Phase28(CameraStruct* arg0) {
    switch (gBattleScene.posX->unk_20) {
        case 0:
            BattleScene_SaveCameraFov(arg0);
            Battle_ApplyAnimStateEffects(gCurrentPlayer);
            BattleScene_SelectCameraFollowPreset(gCurrentPlayer, arg0, 3);
            BattleScene_ResetCameraFrameCounter();
            gBattleScene.posX->unk_20 += 1;
            break;

        case 1:
            if (BattleScene_AdvanceCameraFrameCounter(0x28) != 0) {
                gBattleScene.posX->unk_20 += 1;
            }
            break;

        case 2:
            gPlayer0ReadyFlag = BattleScene_AnimateDisplayedHpToRuntime(sActivePokemon[gBattleScene.posX->unk_2C]);
            gPlayer1ReadyFlag = BattleScene_AnimateDisplayedHpToRuntime(sActivePokemon[!gBattleScene.posX->unk_2C]);
            if ((gOpponentPlayer->animationState.unk_38.unk_5A & 0xF0) == 0xF0) {
                gBattleScene.posX->unk_34 = 3;
            }
            BattleScene_ResetCameraFrameCounter();
            BattleScene_ResetAnimationStep();
            BattleScene_WaitForDisplayedHpAnimations(arg0);
            break;
    }
}

void BattleScene_Phase15(CameraStruct* arg0) {
    UNUSED s32 pad[3];
    PokemonAudioInfo* sp30 = &gCurrentPlayer->animationState.unk_38;
    PokemonAudioInfo* sp2C = &gOpponentPlayer->animationState.unk_38;
    unk_BattlePlayerAnimState* sp28 = &gCurrentPlayer->animationState;
    unk_BattlePlayerAnimState* sp24 = &gOpponentPlayer->animationState;

    switch (gBattleScene.posX->unk_20) {
        case 0:
            BattleScene_SelectActionCameraPresetFromTiming(arg0, 0);
            BattleScene_RecenterCameraOnOwner(arg0, gCurrentPlayer);
            if (sp30->unk_4D & 0x10) {
                if (sp2C->unk_4E & 8) {
                    sp28->unk_BC = gCurrentPlayer->pokemonAnimation->posY = sp24->unk_BE;
                } else if (gOpponentPlayer->pokemonAnimation->posY == 0x98) {
                    sp28->unk_BC = gCurrentPlayer->pokemonAnimation->posY = sp2C->unk_0B;
                } else {
                    sp28->unk_BC = gCurrentPlayer->pokemonAnimation->posY = gOpponentPlayer->pokemonAnimation->posY;
                }
            } else if (sp2C->unk_4E & 8) {
                gCurrentPlayer->pokemonAnimation->posY = sp24->unk_BE;
            } else if (gOpponentPlayer->pokemonAnimation->posY == 0x98) {
                gCurrentPlayer->pokemonAnimation->posY = sp2C->unk_0B;
            } else {
                gCurrentPlayer->pokemonAnimation->posY = gOpponentPlayer->pokemonAnimation->posY;
            }
            gCurrentPlayer->pokemonAnimation->rotation = &gCurrentPlayer->unk_724->unk_01C[gCurrentPlayer->animationState.unk_08];
            gCurrentPlayer->pokemonAnimation->posX |= 0x80;
            gBattleScene.posX->unk_20 += 1;
            break;

        case 1:
            BattleScene_RecenterCameraOnOwner(arg0, gCurrentPlayer);
            if (gCurrentPlayer->pokemonAnimation->posX & 0x10) {
                gCurrentPlayer->pokemonAnimation->posX &= ~0x90;
                Battle_LoadOwnerModelForSpecies(gCurrentPlayer);
                BattleScene_TickOwnerCameraFraming(gCurrentPlayer);
                BattleAnim_PlayMoveEffectScriptA(gCurrentPlayer, sp30->unk_5A);
                BattleAnim_PlaySpeciesReactionSound(gCurrentPlayer, sp30, 0);
                gBattleScene.posX->unk_20 += 1;
            }
            break;

        case 2:
            BattleScene_RecenterCameraOnOwner(arg0, gCurrentPlayer);
            BattleAnim_PlaySpeciesReactionSound(gCurrentPlayer, sp30, 0);
            BattleScene_EnterStateRow(gCurrentPlayer, 0x12);
            gBattleScene.posX->unk_20 += 1;
            break;

        case 3:
            BattleScene_RecenterCameraOnOwner(arg0, gCurrentPlayer);
            gCurrentPlayer->unk_728.unk_168->posX.unk_01 |= 1;
            gCurrentPlayer->unk_728.unk_000.unk_000.unk_01 |= 1;
            BattleScene_TriggerOwnerModelAnimation(gCurrentPlayer);
            if (BattleScene_IsRowWaitComplete(gCurrentPlayer, 0x32) != 0) {
                BattleScene_ResetAnimationStep();
                BattleScene_UpdateDisplayedHpAndTransition(arg0);
            }
            break;
    }
}

void BattleScene_Phase25(CameraStruct* arg0) {
    PokemonAudioInfo* sp1C = &sActivePokemon[gBattleScene.posX->unk_2C]->animationState.unk_38;
    unk_BattlePlayerAnimState* sp18 = &sActivePokemon[gBattleScene.posX->unk_2C]->animationState;

    switch (gBattleScene.posX->unk_20) {
        case 0:
            BattleScene_SaveCameraFov(arg0);
            BattleAnim_PlayMoveEffectScriptA(gCurrentPlayer, sp1C->unk_5A);
            BattleScene_SelectActionCameraPresetFromTiming(arg0, 0);
            if (!(sp18->unk_34 & 0x800)) {
                BattleAnim_BeginSessionRequest(gCurrentPlayer);
            }
            gBattleScene.posX->unk_20 += 1;
            break;

        case 1:
            BattleScene_ApplyActionCameraMode(arg0, 0);
            if (!(sp18->unk_34 & 0x800)) {
                Pokemon_ClearTransformFlag(gCurrentPlayer);
            }
            if (BattleAnim_IsSessionBusy(gCurrentPlayer) == 0) {
                BattleAnim_PlaySpeciesReactionSound(gCurrentPlayer, sp1C, 0);
                BattleScene_SelectCameraFollowPreset(gCurrentPlayer, arg0, 3);
                BattleScene_ResetCameraFrameCounter();
                gBattleScene.posX->unk_20 += 1;
            }
            break;

        case 2:
            BattleScene_SelectCameraFollowPreset(gCurrentPlayer, arg0, 3);
            gPlayer0ReadyFlag = BattleScene_AnimateDisplayedHpToRuntime(sActivePokemon[gBattleScene.posX->unk_2C]);
            gPlayer1ReadyFlag = BattleScene_AnimateDisplayedHpToRuntime(sActivePokemon[!gBattleScene.posX->unk_2C]);
            if (BattleScene_AdvanceCameraFrameCounter(0x2E) != 0) {
                gBattleScene.posX->unk_20 += 1;
            }
            break;

        case 3:
            if (!(sp18->unk_34 & 0x800)) {
                Battle_SetRuntimeFlags(gCurrentPlayer, 0x800);
            }
            gPlayer0ReadyFlag = BattleScene_AnimateDisplayedHpToRuntime(sActivePokemon[gBattleScene.posX->unk_2C]);
            gPlayer1ReadyFlag = BattleScene_AnimateDisplayedHpToRuntime(sActivePokemon[!gBattleScene.posX->unk_2C]);
            if ((gOpponentPlayer->animationState.unk_38.unk_5A & 0xF0) == 0xF0) {
                gBattleScene.posX->unk_34 = 3;
            }
            BattleScene_ResetAnimationStep();
            BattleScene_WaitForDisplayedHpAnimations(arg0);
            break;
    }
}

s32 BattleScene_EndStatusAnimationsAndCommit(unk_BattlePlayerEntity* arg0) {
    BattleAnim_ClearFreezeStatusAnimation(arg0);
    BattleAnim_EndSleepStatusAnimation(arg0);
    Battle_ApplyAnimStateEffects(arg0);
}

void BattleScene_Phase29(CameraStruct* arg0) {
    switch (gBattleScene.posX->unk_20) {
        case 0:
            BattleScene_SaveCameraFov(arg0);
            Battle_ApplyAnimStateEffects(gCurrentPlayer);
            BattleScene_SelectActionCameraPresetFromTiming(arg0, 0);
            BattleScene_ResetCameraFrameCounter();
            BattleScene_ResetCameraSubstepCounter();
            gBattleScene.posX->unk_20 += 1;
            break;

        case 1:
            BattleScene_ApplyActionCameraMode(arg0, 1);
            if (Battle_IsRowAnimationSettled(gCurrentPlayer, 0x3C) != 0) {
                BattleScene_EndStatusAnimationsAndCommit(gOpponentPlayer);
                gBattleScene.posX->unk_20 += 1;
            }
            break;

        case 2:
            BattleScene_ApplyActionCameraMode(arg0, 1);
            gPlayer0ReadyFlag = BattleScene_AnimateDisplayedHpToRuntime(sActivePokemon[gBattleScene.posX->unk_2C]);
            gPlayer1ReadyFlag = BattleScene_AnimateDisplayedHpToRuntime(sActivePokemon[!gBattleScene.posX->unk_2C]);
            if ((gOpponentPlayer->animationState.unk_38.unk_5A & 0xF0) == 0xF0) {
                gBattleScene.posX->unk_34 = 3;
            }
            Vec3f_SetComponentsDuplicate(&gCurrentPlayer->unk_000.unk_030, 1.0f, 1.0f, 1.0f);
            Vec3f_SetComponentsDuplicate(&gOpponentPlayer->unk_000.unk_030, 1.0f, 1.0f, 1.0f);
            BattleScene_ResetCameraFrameCounter();
            BattleScene_ResetAnimationStep();
            BattleScene_WaitForDisplayedHpAnimations(arg0);
            break;
    }
}

void BattleScene_Phase12(CameraStruct* arg0) {
    unk_BattleAnimDataEntry* sp4C = &gAnimDataByPlayer[gBattleScene.posX->unk_2C]->unk_B00;
    UNUSED s32 pad;
    Vec3f sp3C;

    switch (gBattleScene.posX->unk_20) {
        case 0:
            BattleScene_ResetCameraFrameCounter();
            BattleScene_ClearPhaseFlag();
            BattleScene_SelectCameraFollowPreset(gCurrentPlayer, arg0, 3);
            BattleScene_ApproachCameraTargetFromOwner(arg0, gCurrentPlayer);
            Battle_SetRuntimeFlags(gCurrentPlayer, 0x200);
            gBattleScene.posX->unk_20 += 1;
            break;

        case 1:
            if (gCurrentPlayer->unk_000.unk_024.y >= 100.0f) {
                BattleAnim_GetOwnerDefaultAnchorPosition(gCurrentPlayer, &sp3C);
                sp3C.y += BattleAnim_GetOwnerModelHeight(gCurrentPlayer);
                gBattleUnusedFloat_84390208 = BattleScene_ScaleCameraDistance(gCurrentPlayer, 3.0f, 500.0f);
                BattleScene_SetCameraEyeFromPosition(arg0, sp3C, 0x11C6, BattleScene_GetParticipantFacingAngle(gCurrentPlayer) - (gCurrentPlayer->sideSign * 0x754E),
                              gBattleUnusedFloat_84390208, BattleAnim_GetOwnerModelHeight(gCurrentPlayer));
                Vec3f_SetComponentsDuplicate(&sp3C, 0.0f, 200.0f, 0.0f);
                BattleAnim_Vec3fCopy(&arg0->unk_60.at, &sp3C);
                BattleAnim_CleanupEffects(2);
                ModelAnim_SetAnimation(&gCurrentPlayer->unk_000, sp4C->posX);
                arg0->unk_24.fovy = 60.0f;
                gBattleScene.posX->unk_20 += 1;
            } else {
                BattleScene_ApproachCameraTargetFromOwner(arg0, gCurrentPlayer);
            }
            break;

        case 2:
            BattleAnim_ApproachF(&arg0->unk_24.fovy, 60.0f, 0.2f);
            if (gCurrentPlayer->unk_000.unk_024.y >= 200.0f) {
                gBattleScene.posX->unk_20 += 1;
            }
            break;

        case 3:
            gPlayer0ReadyFlag = BattleScene_AnimateDisplayedHpToRuntime(sActivePokemon[gBattleScene.posX->unk_2C]);
            gPlayer1ReadyFlag = BattleScene_AnimateDisplayedHpToRuntime(sActivePokemon[!gBattleScene.posX->unk_2C]);
            if ((gPlayer0ReadyFlag == 1) && (gPlayer1ReadyFlag == 1) && (BattleScene_AdvanceCameraFrameCounterUntil(0x1E) != 0)) {
                Battle_SetRuntimeFlags(sActivePokemon[gBattleScene.posX->unk_2C], 4);
                BattleAnim_ClearEffectStateFlag();
                BattleScene_ResetCameraFrameCounter();
                BattleScene_ResetAnimationStep();
                BattleScene_UpdateDisplayedHpAndTransition(arg0);
            }
            break;
    }
}

void BattleScene_Phase13(CameraStruct* arg0) {
    UNUSED s32 pad;
    f32 sp28;
    UNUSED s16 pad2;
    u16 sp24 = gAnimFlagMask_5F92;

    switch (gBattleScene.posX->unk_20) {
        case 0:
            BattleScene_SaveCameraFov(arg0);
            BattleScene_ResetCameraFrameCounter();
            BattleScene_ClearPhaseFlag();
            BattleScene_SelectCameraFollowPreset(gCurrentPlayer, arg0, 3);
            gBattleScene.posX->unk_20 += 1;
            break;

        case 1:
            if (gCurrentPlayer->animationSubstate == 2) {
                BattleScene_UpdateCameraVerticalFraming(arg0, gCurrentPlayer);
                gCurrentPlayer->unk_000.unk_000.posY &= 0xFFBF;
            }

            if ((gCurrentPlayer->unk_000.unk_01A == 0x32) || (gCurrentPlayer->unk_000.unk_01A == 0x33)) {
                if (BattleScene_IsRowWaitComplete(gCurrentPlayer, 0x1E) != 0) {
                    BattleBox_Close();
                    Battle_SetRuntimeFlags(gCurrentPlayer, 0x4000);
                    gCurrentPlayer->unk_000.unk_000.posY &= 0xFFDF;
                    gBattleScene.posX->unk_20 += 1;
                }
            } else if (BattleAnim_IsAssetLoadBusy(gCurrentPlayer) == 0) {
                if (BattleScene_ByteArrayContains(gCurrentPlayer->unk_000.unk_01A, (u8*)&sp24, 2) != 0) {
                    sp28 = 10.0f;
                } else {
                    sp28 = 3.5f;
                }

                if (gCurrentPlayer->unk_000.unk_024.y <= (-BattleAnim_GetOwnerModelHeight(gCurrentPlayer) * sp28)) {
                    Battle_SetRuntimeFlags(gCurrentPlayer, 0x4000);
                    gCurrentPlayer->unk_000.unk_000.posY &= 0xFFDF;
                    gBattleScene.posX->unk_20 += 1;
                }
            }
            break;

        case 2:
            if ((gCurrentPlayer->unk_000.unk_01A != 0x32) && (gCurrentPlayer->unk_000.unk_01A != 0x33)) {
                gCurrentPlayer->unk_000.unk_000.posY |= 0x40;
            }
            BattleScene_UpdateCameraVerticalFraming(arg0, gCurrentPlayer);
            gPlayer0ReadyFlag = BattleScene_AnimateDisplayedHpToRuntime(sActivePokemon[gBattleScene.posX->unk_2C]);
            gPlayer1ReadyFlag = BattleScene_AnimateDisplayedHpToRuntime(sActivePokemon[!gBattleScene.posX->unk_2C]);
            BattleScene_ResetAnimationStep();
            BattleScene_WaitForDisplayedHpAnimations(arg0);
            break;
    }
}

void BattleScene_Phase14(CameraStruct* arg0) {
    switch (gBattleScene.posX->unk_20) {
        case 0:
            BattleScene_SelectActionCameraPresetFromTiming(arg0, 1);
            BattleScene_SaveCameraFov(arg0);
            BattleScene_ResetCameraFrameCounter();
            BattleScene_ResetCameraSubstepCounter();
            Battle_ApplyAnimStateEffects(gCurrentPlayer);
            gBattleScene.posX->unk_20 += 1;
            break;

        case 1:
            BattleScene_ApplyActionCameraMode(arg0, 1);
            gPlayer0ReadyFlag = BattleScene_AnimateDisplayedHpToRuntime(sActivePokemon[gBattleScene.posX->unk_2C]);
            gPlayer1ReadyFlag = BattleScene_AnimateDisplayedHpToRuntime(sActivePokemon[!gBattleScene.posX->unk_2C]);
            if (BattleScene_IsMoveKeyedRowWaitComplete(gCurrentPlayer, 0x1E) != 0) {
                BattleScene_ResetAnimationStep();
                BattleScene_WaitForDisplayedHpAnimations(arg0);
            }
            break;
    }
}

void BattleScene_Phase17(CameraStruct* arg0) {
    unk_BattlePlayerAnimState* sp1C = &sActivePokemon[gBattleScene.posX->unk_2C]->animationState;

    switch (gBattleScene.posX->unk_20) {
        case 0:
            BattleScene_ResetCameraFrameCounter();
            BattleScene_SaveCameraFov(arg0);
            Battle_ApplyAnimStateEffects(gCurrentPlayer);
            if (!(sp1C->unk_34 & 2)) {
                BattleScene_SelectActionCameraPresetFromTiming(arg0, 0);
            }
            gBattleScene.posX->unk_20 += 1;
            break;

        case 1:
            gPlayer0ReadyFlag = BattleScene_AnimateDisplayedHpToRuntime(sActivePokemon[gBattleScene.posX->unk_2C]);
            gPlayer1ReadyFlag = BattleScene_AnimateDisplayedHpToRuntime(sActivePokemon[!gBattleScene.posX->unk_2C]);
            if (BattleScene_AdvanceCameraFrameCounter(0x3C) != 0) {
                gBattleScene.posX->unk_20 += 1;
            }
            break;

        case 2:
            gPlayer0ReadyFlag = BattleScene_AnimateDisplayedHpToRuntime(sActivePokemon[gBattleScene.posX->unk_2C]);
            gPlayer1ReadyFlag = BattleScene_AnimateDisplayedHpToRuntime(sActivePokemon[!gBattleScene.posX->unk_2C]);
            BattleScene_ResetAnimationStep();
            BattleScene_WaitForDisplayedHpAnimations(arg0);
            break;
    }
}

void BattleScene_PhaseFaint(CameraStruct* arg0) {
    BattleScene_ResetCameraFov(arg0);

    switch (gBattleScene.posX->unk_20) {
        case 0:
            if (BattleScene_AdvanceOwnerAnimation98(gCurrentPlayer) == 0) {
                BattleBox_Open(2);
                BattleScene_ResetOwnerPresentationFlags(gCurrentPlayer);
                gBattleScene.posX->unk_20 += 1;
            }
            break;

        case 1:
            BattleScene_ResetAnimationStep();
            BattleScene_ClearStateTickCallbacks();
            BattleScene_EnterStateRow(gCurrentPlayer, 0xF);
            BattleScene_SelectCameraShot(gCurrentPlayer, arg0, 3);
            BattleScene_SetDamageShakeAmplitude(gCurrentPlayer);
            BattleAnim_QueueEffectList(8, gCurrentPlayer);
            gBattleScene.posX->unk_20 += 1;
            break;

        case 2:
            gPlayer0ReadyFlag = BattleScene_AnimateDisplayedHpToRuntime(sActivePokemon[gBattleScene.posX->unk_2C]);
            gPlayer1ReadyFlag = BattleScene_AnimateDisplayedHpToRuntime(sActivePokemon[!gBattleScene.posX->unk_2C]);
            BattleScene_FrameCamera(arg0, gCurrentPlayer);
            if (BattleScene_IsRowZeroCheckpointReached(gCurrentPlayer) != 0) {
                gBattleScene.posX->unk_20 += 1;
            } else if (BattleScene_IsRowWaitComplete(gCurrentPlayer, 0x32) != 0) {
                gBattleScene.posX->unk_20 += 1;
            }
            break;

        case 3:
            BattleScene_FrameCamera(arg0, gCurrentPlayer);
            if (BattleScene_AdvanceOwnerAnimationAndClearFlags(gCurrentPlayer) == 0) {
                gBattleScene.posX->unk_20 += 1;
            }
            break;

        case 4:
            gPlayer0ReadyFlag = BattleScene_AnimateDisplayedHpToRuntime(sActivePokemon[gBattleScene.posX->unk_2C]);
            gPlayer1ReadyFlag = BattleScene_AnimateDisplayedHpToRuntime(sActivePokemon[!gBattleScene.posX->unk_2C]);
            BattleScene_FrameCamera(arg0, gCurrentPlayer);
            BattleScene_ResetAnimationStep();
            BattleScene_UpdateDisplayedHpAndTransition(arg0);
            break;
    }
}

void BattleScene_Phase31(CameraStruct* arg0) {
    switch (gBattleScene.posX->unk_20) {
        case 0:
            BattleScene_SaveCameraFov(arg0);
            Battle_ApplyAnimStateEffects(gCurrentPlayer);
            gCurrentPlayer->unk_4C8 = 1;
            BattleScene_ResetCameraFrameCounter();
            gBattleScene.posX->unk_20 += 1;
            break;

        case 1:
            gPlayer0ReadyFlag = BattleScene_AnimateDisplayedHpToRuntime(sActivePokemon[gBattleScene.posX->unk_2C]);
            gPlayer1ReadyFlag = BattleScene_AnimateDisplayedHpToRuntime(sActivePokemon[!gBattleScene.posX->unk_2C]);
            if (BattleScene_AdvanceCameraFrameCounter(0x3C) != 0) {
                gBattleScene.posX->unk_20 += 1;
            }
            break;

        case 2:
            gPlayer0ReadyFlag = BattleScene_AnimateDisplayedHpToRuntime(sActivePokemon[gBattleScene.posX->unk_2C]);
            gPlayer1ReadyFlag = BattleScene_AnimateDisplayedHpToRuntime(sActivePokemon[!gBattleScene.posX->unk_2C]);
            BattleScene_ResetAnimationStep();
            BattleScene_WaitForDisplayedHpAnimations(arg0);
            break;
    }
}

void func_84326A70(void) {
}

void BattleScene_Phase4(UNUSED CameraStruct* arg0) {
    switch (gBattleScene.posX->unk_20) {
        case 0:
            BattleScene_BeginBattlePhase();

        case 1:
            break;
    }
}

void BattleScene_Phase16(CameraStruct* arg0) {
    UNUSED s32 pad;
    s32 idx = gBattleScene.posX->unk_2C;
    unk_BattleAnimDataEntry* sp1C = &gAnimDataByPlayer[idx]->unk_A80;

    BattleScene_ResetCameraFov(arg0);

    switch (gBattleScene.posX->unk_20) {
        case 0:
            BattleScene_ResetAnimationStep();
            BattleBox_Open(2);
            gBattleScene.posX->unk_20 += 1;
            break;

        case 1:
            if (BattleScene_AdvanceOwnerAnimation98(gCurrentPlayer) == 0) {
                Battle_ResetModelToIdleAnim(gCurrentPlayer);
                BattleAnim_CleanupEffects(1);
                BattleScene_EnterStateRow(gCurrentPlayer, 0xF);
                BattleScene_SelectCameraShot(gCurrentPlayer, arg0, 3);
                BattleScene_SetDamageShakeAmplitude(gCurrentPlayer);
                BattleScene_ResetAnimationStep();
                ModelAnim_SetAnimation(&gCurrentPlayer->unk_000, sp1C->posX);
                gBattleScene.posX->unk_20 += 1;
            }
            break;

        case 2:
            if (BattleScene_AdvanceCameraFrameCounter(0x28) != 0) {
                gBattleScene.posX->unk_20 += 1;
            }
            break;

        case 3:
            if (BattleScene_AdvanceOwnerAnimationAndClearFlags(gCurrentPlayer) == 0) {
                BattleBox_Close();
                gBattleScene.posX->unk_20 += 1;
            }
            break;

        case 4:
            gPlayer0ReadyFlag = BattleScene_AnimateDisplayedHpToRuntime(sActivePokemon[gBattleScene.posX->unk_2C]);
            gPlayer1ReadyFlag = BattleScene_AnimateDisplayedHpToRuntime(sActivePokemon[!gBattleScene.posX->unk_2C]);
            if ((gPlayer0ReadyFlag != 0) && (gPlayer1ReadyFlag != 0)) {
                BattleScene_ResetAnimationStep();
                BattleScene_UpdateDisplayedHpAndTransition(arg0);
            }
            break;
    }
}

void BattleScene_PhaseMoveFailedMessage(CameraStruct* arg0) {
    unk_BattlePlayerAnimState* sp1C = &gOpponentPlayer->animationState;

    switch (gBattleScene.posX->unk_20) {
        case 0:
            if (BattleScene_AdvanceOwnerAnimation98(gOpponentPlayer) == 0) {
                BattleBox_Open(2);
                BattleScene_StopSpecialOwnerAnimation(gCurrentPlayer);
                BattleScene_ResetCameraFov(arg0);
                BattleAnim_CleanupEffects(1);

                if (sp1C->unk_34 & 0x200) {
                    BattleScene_SelectCameraShot(gOpponentPlayer, arg0, gBattleUnusedInt_84390228 = 2);
                } else {
                    if (gOpponentPlayer->unk_000.unk_01A == 0xF) {
                        BattleScene_SelectCameraShot(gOpponentPlayer, arg0, 0);
                    }
                    BattleScene_SelectCameraShot(gOpponentPlayer, arg0, gBattleUnusedInt_84390228 = BattleAnim_RandomRange(2));
                }

                BattleScene_EnterStateRow(gCurrentPlayer, 0xC);
                BattleScene_ResetCameraFrameCounter();
                BattleAnim_UpdateMoveFailedFlag();
                gBattleScene.posX->unk_20 += 1;
                BattleScene_CleanupOpponentAnimationFlags(gOpponentPlayer);
            }
            break;

        case 1:
            if ((gOpponentPlayer->unk_000.unk_01A == 0xF) && !(sp1C->unk_34 & 0x200)) {
                BattleScene_FrameCamera(arg0, gOpponentPlayer);
            }

            if (BattleScene_AdvanceCameraFrameCounter(0x32) != 0) {
                BattleBox_Close();
                BattleScene_ResetOwnerPresentationFlags(gCurrentPlayer);
                BattleScene_CleanupParticipantEffectMode(gCurrentPlayer);
                BattleScene_ClearPhaseFlag();
                BattleScene_ResetCameraFrameCounter();
                BattleScene_ResetAnimationStep();
                BattleScene_UpdateDisplayedHpAndTransition(arg0);
            }
            break;
    }
}

void BattleScene_PhaseAttackHit(CameraStruct* arg0) {
    PokemonAudioInfo* sp24 = &sActivePokemon[gBattleScene.posX->unk_2C]->animationState.unk_38;
    PokemonAudioInfo* sp20 = &sActivePokemon[!gBattleScene.posX->unk_2C]->animationState.unk_38;

    switch (gBattleScene.posX->unk_20) {
        case 0:
            Battle_ResetCryEventIfStruggle(gCurrentPlayer);
            BattleScene_SetCameraOwnerStandardShot(arg0, sActivePokemon[gBattleScene.posX->unk_2C]);
            BattleScene_ResetAnimationStep();
            BattleScene_CleanupParticipantEffectMode(gCurrentPlayer);
            BattleAnim_CleanupEffects(2);
            gBattleScene.posX->unk_20 += 1;
            break;

        case 1:
            if (BattleScene_AdvanceOwnerAnimation(sActivePokemon[gBattleScene.posX->unk_2C]) == 0) {
                Battle_ResetModelToIdleAnim(gCurrentPlayer);
                Audio_FadeAndClearStoredSounds();
                BattleAnim_CleanupEffects(1);
                BattleScene_SetCameraOwnerStandardShot(arg0, sActivePokemon[gBattleScene.posX->unk_2C]);
                BattleScene_EnterStateRow(sActivePokemon[gBattleScene.posX->unk_2C], 0xD);

                if (sp24->unk_15 & 0x18) {
                    BattleBox_Open(4);
                    sp24->unk_0C = sp24->unk_0E;
                    sp20->unk_0C = sp20->unk_0E;
                    if (sp24->unk_15 & 0x10) {
                        BattleAnim_QueueEffectList(6, gCurrentPlayer);
                    } else {
                        BattleAnim_QueueEffectList(5, gCurrentPlayer);
                    }
                    gBattleScene.posX->unk_20 += 1;
                } else {
                    BattleBox_Open(5);
                    Audio_PlayCommand(0x22, 0, 0);
                    sp24->unk_0C = sp24->unk_10;
                    sp20->unk_0C = sp20->unk_10;
                    BattleAnim_QueueEffectList(0xA, gCurrentPlayer);
                    BattleScene_ResetCameraFrameCounter();
                    gBattleScene.posX->unk_20 = 3;
                }
            }
            break;

        case 2:
            BattleScene_SetCameraOwnerStandardShot(arg0, sActivePokemon[gBattleScene.posX->unk_2C]);
            gPlayer0ReadyFlag = BattleScene_AnimateDisplayedHpToRuntime(sActivePokemon[gBattleScene.posX->unk_2C]);
            gPlayer1ReadyFlag = BattleScene_AnimateDisplayedHpToRuntime(sActivePokemon[!gBattleScene.posX->unk_2C]);

            if ((gPlayer0ReadyFlag == 1) && (gPlayer1ReadyFlag == 1) && (BattleScene_AdvanceCameraFrameCounterUntil(0x32) != 0)) {
                BattleScene_ResetCameraFrameCounter();
                if (Battle_GetActiveMonHp(sActivePokemon[gBattleScene.posX->unk_2C]) == 0) {
                    BattleScene_ClearPhaseFlag();
                    BattleScene_SetPhase(arg0, 5);
                    gBattleScene.posX->unk_2C = !gBattleScene.posX->unk_2C;
                } else if (sp24->unk_4D & 0x80) {
                    BattleScene_ResetCameraFrameCounter();
                    Audio_PlayCommand(0x22, 0, 0);
                    sp24->unk_0C = sp24->unk_10;
                    sp20->unk_0C = sp20->unk_10;
                    BattleAnim_QueueEffectList(0xA, gCurrentPlayer);
                    gBattleScene.posX->unk_20 += 1;
                } else {
                    gBattleScene.posX->unk_20 = 4;
                }
            }
            break;

        case 3:
            BattleScene_SetCameraOwnerStandardShot(arg0, sActivePokemon[gBattleScene.posX->unk_2C]);
            gPlayer0ReadyFlag = BattleScene_AnimateDisplayedHpToRuntime(sActivePokemon[gBattleScene.posX->unk_2C]);
            gPlayer1ReadyFlag = BattleScene_AnimateDisplayedHpToRuntime(sActivePokemon[!gBattleScene.posX->unk_2C]);

            if ((BattleScene_AdvanceCameraFrameCounterUntil(0x32) != 0) && (gPlayer0ReadyFlag == 1) && (gPlayer1ReadyFlag == 1)) {
                gBattleScene.posX->unk_20 += 1;
                BattleScene_ResetCameraFrameCounter();
            }
            break;

        case 4:
            if (BattleScene_AdvanceOwnerAnimationAndClearFlags(gOpponentPlayer) == 0) {
                gBattleScene.posX->unk_20 += 1;
            }
            break;

        case 5:
            BattleScene_ResetAnimationStep();
            BattleScene_SetCameraOwnerStandardShot(arg0, sActivePokemon[gBattleScene.posX->unk_2C]);
            gPlayer0ReadyFlag = BattleScene_AnimateDisplayedHpToRuntime(sActivePokemon[gBattleScene.posX->unk_2C]);
            gPlayer1ReadyFlag = BattleScene_AnimateDisplayedHpToRuntime(sActivePokemon[!gBattleScene.posX->unk_2C]);
            BattleScene_ResolveDisplayedHpCompletion(arg0);
            break;
    }
}

void BattleScene_PhaseDrainDamage(CameraStruct* arg0) {
    PokemonAudioInfo* sp1C = &sActivePokemon[gBattleScene.posX->unk_2C]->animationState.unk_38;
    PokemonAudioInfo* sp18 = &sActivePokemon[!gBattleScene.posX->unk_2C]->animationState.unk_38;

    switch (gBattleScene.posX->unk_20) {
        case 0:
            BattleScene_CleanupParticipantEffectMode(gCurrentPlayer);
            BattleAnim_CleanupEffects(2);
            BattleScene_SetCameraOwnerWideShot(arg0, sActivePokemon[gBattleScene.posX->unk_2C]);
            gBattleScene.posX->unk_20 += 1;
            break;

        case 1:
            if (BattleScene_AdvanceOwnerAnimation(sActivePokemon[gBattleScene.posX->unk_2C]) == 0) {
                Battle_ResetModelToIdleAnim(gCurrentPlayer);
                Audio_FadeAndClearStoredSounds();
                BattleAnim_CleanupEffects(1);
                BattleAnim_QueueEffectList(9, gCurrentPlayer);
                BattleScene_ResetCameraFrameCounter();
                BattleScene_SetCameraOwnerWideShot(arg0, sActivePokemon[gBattleScene.posX->unk_2C]);
                sp1C->unk_0C = sp1C->unk_12;
                sp18->unk_0C = sp18->unk_12;
                BattleBox_Open(6);
                gBattleScene.posX->unk_20 += 1;
            }
            break;

        case 2:
            if (BattleScene_ApproachCloseCameraShot(arg0, sActivePokemon[gBattleScene.posX->unk_2C]) != 0) {
                BattleScene_SelectCameraShot(gCurrentPlayer, arg0, 3);
                Pokemon_ResetAnimAndTrigger(gCurrentPlayer);
                BattleAnim_PlayBattleSequenceById(gCurrentPlayer, 0x1F);
                BattleScene_SetDamageShakeAmplitude(gCurrentPlayer);
                gBattleScene.posX->unk_20 += 1;
            }
            break;

        case 3:
            if (BattleScene_AdvanceOwnerAnimationAndClearFlags(gOpponentPlayer) == 0) {
                BattleScene_FrameCamera(arg0, gCurrentPlayer);
                gBattleScene.posX->unk_20 += 1;
            }
            break;

        case 4:
            BattleScene_ResetAnimationStep();
            gPlayer0ReadyFlag = BattleScene_AnimateDisplayedHpToRuntime(sActivePokemon[gBattleScene.posX->unk_2C]);
            gPlayer1ReadyFlag = BattleScene_AnimateDisplayedHpToRuntime(sActivePokemon[!gBattleScene.posX->unk_2C]);
            BattleScene_FrameCamera(arg0, gCurrentPlayer);
            if ((gPlayer0ReadyFlag == 1) && (gPlayer1ReadyFlag == 1) && (BattleScene_AdvanceCameraFrameCounterUntil(0x3C) != 0)) {
                BattleScene_UpdateDisplayedHpAndTransition(arg0);
            }
            break;
    }
}

void BattleScene_Phase10(CameraStruct* arg0) {
    switch (gBattleScene.posX->unk_20) {
        case 0:
            BattleScene_CleanupParticipantEffectMode(gCurrentPlayer);
            if (BattleScene_AdvanceOwnerAnimation(sActivePokemon[gBattleScene.posX->unk_2C]) == 0) {
                Battle_ResetModelToIdleAnim(gCurrentPlayer);
                Audio_FadeAndClearStoredSounds();
                BattleAnim_CleanupEffects(1);
                BattleScene_ResetCameraFrameCounter();
                BattleAnim_QueueEffectList6(3, gOpponentPlayer);
                Audio_PlayCommand(0x23, 0, 0);
                BattleScene_SetCameraOwnerStandardShot(arg0, gOpponentPlayer);
                BattleBox_Open(7);
                gBattleScene.posX->unk_20 += 1;
            }
            break;

        case 1:
            if (BattleScene_AdvanceCameraFrameCounter(0x37) != 0) {
                gBattleScene.posX->unk_20 += 1;
            }

        case 2:
            if (BattleScene_AdvanceCameraFrameCounter(0x3C) != 0) {
                BattleScene_UpdateDisplayedHpAndTransition(arg0);
            }
            break;
    }
}

void BattleScene_PhaseAttackHitRecoil(CameraStruct* arg0) {
    PokemonAudioInfo* sp24 = &sActivePokemon[gBattleScene.posX->unk_2C]->animationState.unk_38;
    PokemonAudioInfo* sp20 = &sActivePokemon[!gBattleScene.posX->unk_2C]->animationState.unk_38;

    switch (gBattleScene.posX->unk_20) {
        case 0:
            BattleScene_CleanupParticipantEffectMode(gCurrentPlayer);
            BattleAnim_CleanupEffects(2);
            gBattleScene.posX->unk_20 += 1;
            break;

        case 1:
            if (BattleScene_AdvanceOwnerAnimation(sActivePokemon[gBattleScene.posX->unk_2C]) == 0) {
                Battle_ResetModelToIdleAnim(gCurrentPlayer);
                Audio_FadeAndClearStoredSounds();
                BattleAnim_CleanupEffects(1);
                BattleScene_SetCameraOwnerStandardShot(arg0, sActivePokemon[gBattleScene.posX->unk_2C]);
                BattleScene_EnterStateRow(sActivePokemon[gBattleScene.posX->unk_2C], 0xD);

                if (sp24->unk_15 & 0x18) {
                    BattleBox_Open(4);
                    sp24->unk_0C = sp24->unk_0E;
                    sp20->unk_0C = sp20->unk_0E;
                    if (sp24->unk_15 & 0x10) {
                        BattleAnim_QueueEffectList(6, gCurrentPlayer);
                    } else {
                        BattleAnim_QueueEffectList(5, gCurrentPlayer);
                    }
                    gBattleScene.posX->unk_20 += 1;
                } else {
                    BattleBox_Open(5);
                    sp24->unk_0C = sp24->unk_10;
                    sp20->unk_0C = sp20->unk_10;
                    BattleAnim_QueueEffectList(0xA, gCurrentPlayer);
                    gBattleScene.posX->unk_20 = 3;
                }
            }
            break;

        case 2:
            BattleScene_SetCameraOwnerStandardShot(arg0, sActivePokemon[gBattleScene.posX->unk_2C]);
            gPlayer0ReadyFlag = BattleScene_AnimateDisplayedHpToRuntime(sActivePokemon[gBattleScene.posX->unk_2C]);
            gPlayer1ReadyFlag = BattleScene_AnimateDisplayedHpToRuntime(sActivePokemon[!gBattleScene.posX->unk_2C]);
            if ((gPlayer0ReadyFlag == 1) && (gPlayer1ReadyFlag == 1) && (BattleScene_AdvanceCameraFrameCounterUntil(0x32) != 0)) {
                BattleScene_ResetCameraFrameCounter();
                if (Battle_GetActiveMonHp(sActivePokemon[gBattleScene.posX->unk_2C]) == 0) {
                    BattleScene_ClearPhaseFlag();
                    BattleScene_SetPhase(arg0, 5);
                    gBattleScene.posX->unk_2C = !gBattleScene.posX->unk_2C;
                } else if (sp24->unk_4D & 0x80) {
                    Audio_PlayCommand(0x22, 0, 0);
                    sp24->unk_0C = sp24->unk_10;
                    sp20->unk_0C = sp20->unk_10;
                    BattleAnim_QueueEffectList(0xA, gCurrentPlayer);
                    gBattleScene.posX->unk_20 += 1;
                } else {
                    gBattleScene.posX->unk_20 = 4;
                }
            }
            break;

        case 3:
            BattleScene_SetCameraOwnerStandardShot(arg0, sActivePokemon[gBattleScene.posX->unk_2C]);
            gPlayer0ReadyFlag = BattleScene_AnimateDisplayedHpToRuntime(sActivePokemon[gBattleScene.posX->unk_2C]);
            gPlayer1ReadyFlag = BattleScene_AnimateDisplayedHpToRuntime(sActivePokemon[!gBattleScene.posX->unk_2C]);
            if ((BattleScene_AdvanceCameraFrameCounterUntil(0x32) != 0) && (gPlayer0ReadyFlag == 1) && (gPlayer1ReadyFlag == 1)) {
                gBattleScene.posX->unk_20 += 1;
                BattleScene_ResetCameraFrameCounter();
            }
            break;

        case 4:
            if (BattleScene_AdvanceOwnerAnimationAndClearFlags(gOpponentPlayer) == 0) {
                gBattleScene.posX->unk_20 += 1;
            }
            break;

        case 5:
            BattleScene_ResetAnimationStep();
            BattleScene_SetCameraOwnerStandardShot(arg0, sActivePokemon[gBattleScene.posX->unk_2C]);
            gPlayer0ReadyFlag = BattleScene_AnimateDisplayedHpToRuntime(sActivePokemon[gBattleScene.posX->unk_2C]);
            gPlayer1ReadyFlag = BattleScene_AnimateDisplayedHpToRuntime(sActivePokemon[!gBattleScene.posX->unk_2C]);
            BattleScene_ResolveDisplayedHpCompletion(arg0);
            break;
    }
}

void BattleScene_PhaseCheckFaintedEndTurn(CameraStruct* arg0) {
    PokemonAudioInfo* sp1C = &sActivePokemon[gBattleScene.posX->unk_2C]->animationState.unk_38;
    PokemonAudioInfo* sp18 = &sActivePokemon[!gBattleScene.posX->unk_2C]->animationState.unk_38;

    switch (gBattleScene.posX->unk_20) {
        case 0:
            BattleScene_CleanupParticipantEffectMode(gCurrentPlayer);
            BattleAnim_CleanupEffects(2);
            gBattleScene.posX->unk_20 += 1;
            break;

        case 1:
            Battle_ResetModelToIdleAnim(gCurrentPlayer);
            Audio_FadeAndClearStoredSounds();
            BattleAnim_CleanupEffects(1);
            BattleScene_CameraShotTargetClose(arg0, sActivePokemon[gBattleScene.posX->unk_2C]);
            BattleScene_EnterStateRow(sActivePokemon[gBattleScene.posX->unk_2C], 0xD);
            sp1C->unk_0C = sp1C->unk_0E;
            sp18->unk_0C = sp18->unk_0E;
            gBattleScene.posX->unk_20 += 1;
            break;

        case 2:
            BattleScene_CameraShotTargetClose(arg0, sActivePokemon[gBattleScene.posX->unk_2C]);
            gPlayer0ReadyFlag = BattleScene_AnimateDisplayedHpToRuntime(sActivePokemon[gBattleScene.posX->unk_2C]);
            gPlayer1ReadyFlag = 1;

            if ((gPlayer0ReadyFlag == 1) && (gPlayer1ReadyFlag == 1) && (BattleScene_AdvanceCameraFrameCounterUntil(0x32) != 0)) {
                BattleScene_ResetCameraFrameCounter();
                if (Battle_GetActiveMonHp(sActivePokemon[gBattleScene.posX->unk_2C]) == 0) {
                    BattleScene_ClearPhaseFlag();
                    BattleScene_SetPhase(arg0, 0x22);
                    gBattleScene.posX->unk_2C = !gBattleScene.posX->unk_2C;
                } else {
                    BattleScene_CleanupActionAndAdvance();
                }
            }
            break;
    }
}

void BattleScene_ClearMonStatusAnimations(unk_BattlePlayerEntity* arg0) {
    BattleAnim_ClearFreezeStatusAnimation(arg0);
    BattleAnim_ClearSleepStatusAnimation(arg0);
}

void BattleScene_PhaseWithdrawFainted(CameraStruct* arg0) {
    unk_BattlePlayerAnimState* sp34 = &sActivePokemon[gBattleScene.posX->unk_2C]->animationState;
    unk_BattlePlayerEntity* temp_s0 = sActivePokemon[gBattleScene.posX->unk_2C];
    PokemonAudioInfo* sp2C = &sActivePokemon[gBattleScene.posX->unk_2C]->animationState.unk_38;

    if (gBattleScene.posX->unk_2C) {}

    switch (gBattleScene.posX->unk_20) {
        case 0:
            if (gBattleScene.posX->unk_34 == 1) {
                BattleScene_ResetCameraFov(arg0);
                BattleScene_SelectCameraFollowPreset(temp_s0, arg0, 4);
                PlayerDefeated(BattleScene_GetParticipantDisplayPlayerNumber(temp_s0));
                gBattleScene.posX->unk_20 += 1;
            } else if (BattleScene_AnimateCameraPreset(arg0, temp_s0, 1, 1) != 0) {
                BattleBox_Open(0xA);
                PlayerDefeated(BattleScene_GetParticipantDisplayPlayerNumber(temp_s0));
                gBattleScene.posX->unk_20 += 1;
            }
            break;

        case 1:
            BattleScene_ApproachCameraZoom(arg0, temp_s0);
            BattleScene_EnterStateRow(temp_s0, 2);
            BattleScene_ClearMonStatusAnimations(temp_s0);
            gBattleScene.posX->unk_20 += 1;
            break;

        case 2:
            BattleScene_ApproachCameraZoom(arg0, temp_s0);
            if (BattleScene_AdvanceCameraFrameCounter(0x69) != 0) {
                Vec3f_SetComponentsDuplicate(&arg0->unk_60.at, temp_s0->sideSign * -150.0f, 0.0, 0.0f);
                if (gBattleScene.posX && gBattleScene.posX) {}
                Vec3f_SetComponentsDuplicate(&arg0->unk_60.eye, temp_s0->sideSign * -50.0f, 5.0f, 0.0f);
                BattleScene_SetParticipantModelFlags(temp_s0, 2, 0);
                BattleAnim_QueueEffectList3(0xD, temp_s0, temp_s0, 0xFF, 0xFF);
                gBattleScene.posX->unk_20 += 1;
            }
            break;

        case 3:
            if (temp_s0->effectGraphNode.unk_024.y == 2.5f) {
                temp_s0->effectGraphNode.unk_000.posY |= 0x20;
            }

            if (ModelAnim_IsAnimationDone(&temp_s0->effectGraphNode) == 1) {
                gBattleScene.posX->unk_20 += 1;
            }
            break;

        case 4:
            temp_s0->effectGraphNode.unk_000.unk_01 &= ~1;
            temp_s0->pokemonAnimation->rotation = &temp_s0->pokemonAnimation->unk_08[sp34->unk_2C]->unk_01C[sp34->unk_18];
            temp_s0->pokemonAnimation->posX |= 0x80;
            gBattleScene.posX->unk_20 += 1;
            break;

        case 5:
            if (temp_s0->pokemonAnimation->posX & 0x10) {
                temp_s0->pokemonAnimation->posX &= ~0x90;
                Battle_LoadOwnerModelForSwitchIn(temp_s0);
                BattleScene_TickOwnerCameraFraming(temp_s0);
                gPlayerScaleFactors[gBattleScene.posX->unk_2C] = temp_s0->animationState.unk_38.unk_0C;
                BattleAnim_QueueEffectList3(3, temp_s0, temp_s0, 0xFF, 0xFF);
                Audio_PlayCommand(2, 0, 0);
                BattleScene_RebindParticipantToSide(temp_s0, sp34->unk_2C);
                arg0->unk_24.fovy = 40.0f;
                BattleBox_Open(0xC);
                Battle_TriggerTrainerPresentationCue(temp_s0);
                gBattleDamage = 0;
                gBattleScene.posX->unk_20 += 1;
            }
            break;

        case 6:
            BattleScene_EnterStateRow(temp_s0, 0x12);
            BattleScene_SelectCameraFollowPreset(temp_s0, arg0, 3);
            BattleScene_ResetCameraFrameCounter();
            gBattleScene.posX->unk_20 += 1;
            break;

        case 7:
            BattleScene_ReframeAndRecomputeDistanceForSwitch(arg0, temp_s0);
            if (BattleScene_IsRowWaitCompleteWithEventCount(temp_s0, 0x3C) != 0) {
                Audio_FadeAndClearStoredSounds();
                BattleAnim_CleanupEffects(2);
                BattleScene_ResetCameraFrameCounter();
                Vec3f_SetComponentsDuplicate(&temp_s0->unk_000.unk_030, 1.0f, 1.0f, 1.0f);
                if (sp2C->unk_5A == 0xFE) {
                    sp2C->unk_5A = 0xA5;
                }
                BattleScene_CleanupActionAndAdvance();
                sp34->unk_34 &= ~0x1800;
                BattleBox_Close();
                gBattleScene.posX->unk_54 = !gBattleScene.posX->unk_2C + 1;
            }
            break;
    }
}

void BattleScene_PhaseWithdrawSwitch(CameraStruct* arg0) {
    unk_BattlePlayerAnimState* sp3C = &sActivePokemon[gBattleScene.posX->unk_2C]->animationState;
    unk_BattlePlayerAnimState* sp38 = &sActivePokemon[!gBattleScene.posX->unk_2C]->animationState;
    UNUSED s32 pad;
    unk_BattlePlayerEntity* temp_s0 = sActivePokemon[gBattleScene.posX->unk_2C];
    PokemonAudioInfo* sp2C = &sActivePokemon[gBattleScene.posX->unk_2C]->animationState.unk_38;

    switch (gBattleScene.posX->unk_20) {
        case 0:
            if (gBattleScene.posX->unk_34 == 1) {
                BattleScene_ResetCameraFov(arg0);
                BattleScene_ResetCameraFrameCounter();
                BattleBox_Open(0xB);
                BattleAnim_LoadModeResourceList(temp_s0->pokemonAnimation, 3);
                Vec3f_SetComponentsDuplicate(&arg0->unk_60.at, temp_s0->sideSign * -150.0f, 0.0, 0.0f);
                Vec3f_SetComponentsDuplicate(&arg0->unk_60.eye, temp_s0->sideSign * -50.0f, 5.0f, 0.0f);
                Vec3f_SetComponentsDuplicate(&temp_s0->unk_000.unk_024, temp_s0->sideSign * -150.0f, 25.0f, 0.0f);
                gBattleScene.posX->unk_20 += 1;
            } else {
                BattleAnim_ApproachF(&arg0->unk_24.fovy, 30.0f, 0.05f);
                if (BattleScene_AnimateCameraIntro(arg0, temp_s0) != 0) {
                    BattleScene_ResetCameraFov(arg0);
                    BattleScene_ResetCameraFrameCounter();
                    BattleBox_Open(0xB);
                    BattleAnim_LoadModeResourceList(temp_s0->pokemonAnimation, 3);
                    gBattleScene.posX->unk_20 += 1;
                }
            }
            break;

        case 1:
            if (BattleAnim_TryRegisterAssetTables(temp_s0) != 0) {
                temp_s0->pokemonAnimation->posY = sp2C->unk_0B;
                BattleScene_SetParticipantModelFlags(temp_s0, 2, 0);
                BattleAnim_QueueEffectList3(0xD, temp_s0, temp_s0, 0xFF, 0xFF);
                gBattleScene.posX->unk_20 += 1;
            }
            break;

        case 2:
            if (temp_s0->effectGraphNode.unk_024.y == 2.5f) {
                temp_s0->effectGraphNode.unk_000.posY |= 0x20;
            }

            if (ModelAnim_IsAnimationDone(&temp_s0->effectGraphNode) == 1) {
                gBattleScene.posX->unk_20 += 1;
            }
            break;

        case 3:
            temp_s0->effectGraphNode.unk_000.unk_01 &= ~1;
            temp_s0->pokemonAnimation->posX |= 0x80;
            temp_s0->pokemonAnimation->rotation = &temp_s0->pokemonAnimation->unk_08[sp3C->unk_2C]->unk_01C[sp3C->unk_18];
            gBattleScene.posX->unk_20 += 1;
            break;

        case 4:
            if (temp_s0->pokemonAnimation->posX & 0x10) {
                temp_s0->pokemonAnimation->posX &= ~0x90;
                Battle_LoadOwnerModelForSwitchIn(temp_s0);
                BattleScene_TickOwnerCameraFraming(temp_s0);
                gPlayerScaleFactors[BattleScene_GetParticipantSideIndex(temp_s0)] = temp_s0->animationState.unk_38.unk_0C;
                Audio_PlayCommand(2, 0, 0);
                BattleScene_RebindParticipantToSide(temp_s0, sp3C->unk_2C);
                BattleScene_ResetCameraFrameCounter();
                BattleAnim_QueueEffectList3(3, temp_s0, temp_s0, 0xFF, 0xFF);
                arg0->unk_24.fovy = 40.0f;
                Battle_TriggerTrainerPresentationCue(temp_s0);
                gBattleDamage = 0;
                gBattleScene.posX->unk_20 += 1;
            }
            break;

        case 5:
            BattleScene_EnterStateRow(temp_s0, 0x12);
            BattleScene_SelectCameraFollowPreset(temp_s0, arg0, 3);
            gBattleScene.posX->unk_20 += 1;
            break;

        case 6:
            BattleScene_ReframeAndRecomputeDistanceForSwitch(arg0, temp_s0);
            if (BattleScene_IsRowWaitCompleteWithEventCount(temp_s0, 0x3C) != 0) {
                if ((sp2C->unk_5A & 0xF0) == 0xF0) {
                    sp2C->unk_5A = 0xA5;
                }
                Audio_FadeAndClearStoredSounds();
                BattleAnim_CleanupEffects(2);
                BattleScene_ResetCameraFrameCounter();
                Vec3f_SetComponentsDuplicate(&temp_s0->unk_000.unk_030, 1.0f, 1.0f, 1.0f);
                if (sp38->unk_2D != 0x10) {
                    gBattleScene.posX->unk_34 = 3;
                }
                gBattleScene.posX->unk_2E = 2;
                BattleScene_CleanupActionAndAdvance();
                sp3C->unk_34 &= 0xE7FF;
                gBattleScene.posX->unk_54 = !gBattleScene.posX->unk_2C + 1;
            }
            break;
    }
}

void BattleScene_UpdatePhase(CameraStruct* arg0) {
    BattleScene_UpdateActiveOwnerPointers();

    switch (gBattleScene.posX->unk_38) {
        case 0:
            BattleScene_InitializeBattlePresentation(arg0);
            BattleScene_SetPhase(arg0, 1);

        case 1:
            BattleScene_PhaseIntro(arg0);
            break;
        case 2:
            BattleScene_Phase2(arg0);
            break;
        case 3:
            BattleScene_Phase3(arg0);
            break;
        case 4:
            BattleScene_Phase4(arg0);
            break;
        case 7:
            BattleScene_Phase7(arg0);
            break;
        case 38:
            BattleScene_Phase38(arg0);
            break;
        case 27:
            BattleScene_Phase27(arg0);
            break;
        case 30:
            BattleScene_Phase30(arg0);
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
            BattleScene_Phase12(arg0);
            break;
        case 13:
            BattleScene_Phase13(arg0);
            break;
        case 14:
            BattleScene_Phase14(arg0);
            break;
        case 15:
            BattleScene_Phase15(arg0);
            break;
        case 17:
            BattleScene_Phase17(arg0);
            break;
        case 31:
            BattleScene_Phase31(arg0);
            break;
        case 20:
            BattleScene_PhaseFaint(arg0);
            break;
        case 8:
            BattleScene_PhaseMoveFailedMessage(arg0);
            break;
        case 10:
            BattleScene_Phase10(arg0);
            break;
        case 6:
            BattleScene_PhaseAttackHit(arg0);
            break;
        case 33:
            BattleScene_PhaseCheckFaintedEndTurn(arg0);
            break;
        case 35:
            BattleScene_PhaseAttackHitRecoil(arg0);
            break;
        case 9:
            BattleScene_PhaseDrainDamage(arg0);
            break;
        case 16:
            BattleScene_Phase16(arg0);
            break;
        case 11:
            BattleScene_PhaseWithdrawFainted(arg0);
            break;
        case 18:
            BattleScene_PhaseWithdrawSwitch(arg0);
            break;
        case 5:
            BattleScene_PhaseSendOut(arg0);
            break;
        case 34:
            BattleScene_PhaseSendOutAfterFaint(arg0);
            break;
        case 36:
            BattleScene_PhaseResumeSaved();
            break;
        case 37:
            BattleScene_PhaseSelectMoveAnim();
            break;
    }
}
