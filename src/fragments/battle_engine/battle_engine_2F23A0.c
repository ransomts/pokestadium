#include "battle_engine.h"
#include "src/17300.h"
#include "src/18140.h"
#include "src/1C720.h"
#include "src/2E110.h"
#include "src/F420.h"

s32 BattleScene_ByteArrayContains(u8 arg0, u8* arg1, s32 arg2) {
    while (arg2--) {
        if (arg0 == *arg1) {
            return 1;
        }
        arg1++;
    }

    return 0;
}

PokemonData* BattleScene_GetParticipantSessionMon(unk_BattlePlayerEntity* arg0) {
    PokemonData* ptr = &arg0->pokemonAnimation->unk_08[arg0->animationState.unk_2C]->unk_01C[arg0->animationState.unk_08];

    return ptr;
}

s32 BattleScene_IsPartnerPikachu(unk_BattlePlayerEntity* arg0) {
    PokemonData* temp_v0 = BattleScene_GetParticipantSessionMon(arg0);

    if ((arg0->unk_000.unk_01A == 0x19) && (temp_v0->unk_52 & 0x80)) {
        return 1;
    }
    return 0;
}

f32 BattleScene_GetParticipantModelHeight(unk_BattlePlayerEntity* arg0) {
    return gPokemonModelDimensions[BattleScene_GetParticipantSideIndex(arg0)].unk_08;
}

f32 BattleScene_GetParticipantModelRadius(unk_BattlePlayerEntity* arg0) {
    return gPokemonModelDimensions[BattleScene_GetParticipantSideIndex(arg0)].unk_00;
}

f32 BattleScene_GetParticipantModelWidth(unk_BattlePlayerEntity* arg0) {
    return gPokemonModelDimensions[BattleScene_GetParticipantSideIndex(arg0)].unk_04;
}

f32 BattleScene_GetParticipantEyeHeight(unk_BattlePlayerEntity* arg0) {
    return gPokemonModelDimensions[BattleScene_GetParticipantSideIndex(arg0)].unk_0C;
}

void BattleScene_PositionParticipantModel(unk_BattlePlayerEntity* arg0) {
    if (BattleScene_GetParticipantSideIndex(arg0) == 0) {
        if (arg0->unk_000.unk_01A == 0x82) {
            Vec3f_SetComponentsDuplicate(&arg0->unk_000.unk_024, -225.0f, BattleScene_GetParticipantModelHeight(arg0), 0.0f);
        } else if ((arg0->unk_000.unk_01A == 3) || (arg0->unk_000.unk_01A == 0x83)) {
            Vec3f_SetComponentsDuplicate(&arg0->unk_000.unk_024, -175.0f, BattleScene_GetParticipantModelHeight(arg0), 0.0f);
        } else if (arg0->unk_000.unk_01A == 0x5F) {
            Vec3f_SetComponentsDuplicate(&arg0->unk_000.unk_024, -225.0f, BattleScene_GetParticipantModelHeight(arg0), 7.5000005f);
        } else {
            Vec3f_SetComponentsDuplicate(&arg0->unk_000.unk_024, -150.0f, BattleScene_GetParticipantModelHeight(arg0), 0.0f);
        }
    } else if ((arg0->unk_000.unk_01A == 0x82) || (arg0->unk_000.unk_01A == 0x5F)) {
        Vec3f_SetComponentsDuplicate(&arg0->unk_000.unk_024, 225.0f, BattleScene_GetParticipantModelHeight(arg0), 0.0f);
    } else if ((arg0->unk_000.unk_01A == 3) || (arg0->unk_000.unk_01A == 0x83)) {
        Vec3f_SetComponentsDuplicate(&arg0->unk_000.unk_024, 175.0f, BattleScene_GetParticipantModelHeight(arg0), 0.0f);
    } else {
        Vec3f_SetComponentsDuplicate(&arg0->unk_000.unk_024, 150.0f, BattleScene_GetParticipantModelHeight(arg0), 0.0f);
    }
}

f32 BattleScene_GetParticipantModelXOffset(unk_BattlePlayerEntity* arg0) {
    if (BattleScene_GetParticipantSideIndex(arg0) == 0) {
        if ((arg0->unk_000.unk_01A == 0x82) || (arg0->unk_000.unk_01A == 0x5F)) {
            return -200.0f;
        }

        if ((arg0->unk_000.unk_01A == 3) || (arg0->unk_000.unk_01A == 0x83)) {
            return -175.0f;
        }
        return -150.0f;
    }

    if ((arg0->unk_000.unk_01A == 0x82) || (arg0->unk_000.unk_01A == 0x5F)) {
        return 200.0f;
    }

    if ((arg0->unk_000.unk_01A == 3) || (arg0->unk_000.unk_01A == 0x83)) {
        return 175.0f;
    }

    return 150.0f;
}

void BattleScene_SetParticipantModelScale(unk_BattlePlayerEntity* arg0, f32 arg1) {
    arg0->unk_000.unk_030.x = arg1;
    arg0->unk_000.unk_030.y = arg1;
    arg0->unk_000.unk_030.z = arg1;
}

s32 BattleScene_GetSelectedSideTeamSize(unk_BattlePlayerEntity* arg0) {
    return arg0->pokemonAnimation->unk_08[arg0->animationState.unk_2B]->unk_002;
}

s32 BattleScene_GetOpposingSelectedSideTeamSize(unk_BattlePlayerEntity* arg0) {
    s32 idx = arg0->animationState.unk_2B == 0;

    return arg0->pokemonAnimation->unk_08[idx]->unk_002;
}

s32 BattleScene_GetParticipantSideIndex(unk_BattlePlayerEntity* arg0) {
    if (arg0 == gPrimaryPokemonEntity) {
        return 0;
    }
    return 1;
}

u8 Battle_GetCameraShotFieldB(unk_BattlePlayerEntity* arg0) {
    UNUSED s32 pad;
    UNUSED s16 pad2;
    s16 sp18 = arg0->animationState.unk_38.unk_5A - 1;
    unk_BattleAnimDataEntry* ptr = &gAnimDataByPlayer[BattleScene_GetParticipantSideIndex(arg0)]->unk_000[sp18];

    return ptr->unk_02;
}

u8 Battle_GetCameraShotFieldC(unk_BattlePlayerEntity* arg0) {
    UNUSED s32 pad;
    UNUSED s16 pad2;
    s16 sp18 = arg0->animationState.unk_38.unk_5A - 1;
    unk_BattleAnimDataEntry* ptr = &gAnimDataByPlayer[BattleScene_GetParticipantSideIndex(arg0)]->unk_000[sp18];

    return ptr->unk_03;
}

s16 Battle_GetSideAnimTableFieldB(unk_BattlePlayerEntity* arg0) {
    unk_BattleAnimDataEntry* ptr = &gAnimDataByPlayer[BattleScene_GetParticipantSideIndex(arg0)]->unk_A80;

    return ptr->unk_02;
}

s32 Battle_GetSideAnimTableFieldC(unk_BattlePlayerEntity* arg0) {
    unk_BattleAnimDataEntry* ptr = &gAnimDataByPlayer[BattleScene_GetParticipantSideIndex(arg0)]->unk_A80;

    return ptr->unk_03;
}

f32 Battle_GetScaledHeightY(unk_BattlePlayerEntity* arg0) {
    return ((BattleScene_GetParticipantModelWidth(arg0) * 2) / 50.0f) * arg0->unk_000.unk_030.y;
}

f32 Battle_GetScaleRatio(unk_BattlePlayerEntity* arg0) {
    return (BattleScene_GetParticipantModelWidth(arg0) * 2) / 50.0f;
}

s16 BattleScene_GetActiveAnimRowId(unk_BattlePlayerEntity* arg0) {
    return arg0->animationState.unk_38.unk_5A;
}

void BattleScene_GetParticipantModelBoundsScaled(unk_BattlePlayerEntity* arg0, Vec3f* arg1) {
    arg1->x = ((BattleScene_GetParticipantModelRadius(arg0) * 2) / 50.0f) * arg0->unk_000.unk_030.x;
    arg1->y = ((BattleScene_GetParticipantModelWidth(arg0) * 2) / 50.0f) * arg0->unk_000.unk_030.y;
    arg1->z = ((BattleScene_GetParticipantModelRadius(arg0) * 2) / 50.0f) * arg0->unk_000.unk_030.x;
}

void BattleScene_GetParticipantModelRotation(unk_BattlePlayerEntity* arg0, Vec3s* arg1) {
    arg1->x = arg0->unk_000.unk_01E.x;
    arg1->y = arg0->unk_000.unk_01E.y;
    arg1->z = arg0->unk_000.unk_01E.z;
}

u16 Battle_GetActiveMonHp(unk_BattlePlayerEntity* arg0) {
    PokemonData* ptr = &arg0->unk_724->unk_01C[arg0->animationState.unk_08];

    return ptr->unk_02;
}

s16 BattleScene_GetParticipantFacingAngle(unk_BattlePlayerEntity* arg0) {
    return arg0->sideSign << 0xE;
}

s32 BattleAnim_GetSpeciesBySideIndex(s32 arg0) {
    return sActivePokemon[arg0]->unk_000.unk_01A;
}

s32 BattleAnim_GetOwnerSpecies(unk_BattlePlayerEntity* arg0) {
    return arg0->unk_000.unk_01A;
}

u8 BattleScene_IsParticipantModelVisible(unk_BattlePlayerEntity* arg0) {
    s32 ret = arg0->unk_000.unk_000.unk_01 & 1;
    return ret;
}

void BattleScene_GetParticipantModelPosition(unk_BattlePlayerEntity* arg0, Vec3f* arg1) {
    arg1->x = arg0->unk_000.unk_024.x;
    arg1->y = arg0->unk_000.unk_024.y;
    arg1->z = arg0->unk_000.unk_024.z;
}

void BattleAnim_GetOwnerDefaultAnchorPosition(unk_BattlePlayerEntity* arg0, Vec3f* arg1) {
    f32 var_fs0 = 0.0f;

    if (BattleScene_ByteArrayContains(arg0->unk_000.unk_01A, &gPokemonSfxId_0, 1) != 0) {
        var_fs0 = BattleAnim_GetOwnerModelHeight(arg0) / 1.5f;
    } else if (BattleScene_ByteArrayContains(arg0->unk_000.unk_01A, &gPokemonSfxId_1, 1) != 0) {
        var_fs0 = BattleAnim_GetOwnerModelHeight(arg0) * 0.5f;
    } else if ((BattleScene_ByteArrayContains(arg0->unk_000.unk_01A, &gPokemonSfxId_2, 1) != 0) && (arg0->animationState.unk_34 & 0x200)) {
        var_fs0 = 2.0f * BattleAnim_GetOwnerModelHeight(arg0);
    } else if ((BattleScene_ByteArrayContains(arg0->unk_000.unk_01A, gPokemonSfxId_3, 2) != 0) && (arg0->animationState.unk_34 & 0x200)) {
        var_fs0 = BattleAnim_GetOwnerModelHeight(arg0) * 1.5f;
    }

    if (BattleScene_GetParticipantModelHeight(arg0) != 0.0f) {
        arg1->x = arg0->unk_000.unk_024.x;
        arg1->y = arg0->unk_000.unk_024.y + var_fs0;
        arg1->z = arg0->unk_000.unk_024.z;
    } else {
        arg1->x = arg0->unk_000.unk_024.x;
        arg1->y = BattleAnim_GetOwnerModelHeight(arg0) + arg0->unk_000.unk_024.y + var_fs0;
        arg1->z = arg0->unk_000.unk_024.z;
    }

    if (arg1->y < 0.0f) {
        arg1->y = BattleAnim_GetOwnerModelHeight(arg0);
    }
}

void BattleScene_ComputeParticipantModelOffset(unk_BattlePlayerEntity* arg0, Vec3f* arg1) {
    if (BattleScene_GetParticipantSideIndex(arg0) == 0) {
        if (arg0->unk_000.unk_01A == 0x82) {
            Vec3f_SetComponentsDuplicate(arg1, -225.0f, BattleScene_GetParticipantModelHeight(arg0), 0.0f);
        } else if ((arg0->unk_000.unk_01A == 3) || (arg0->unk_000.unk_01A == 0x83)) {
            Vec3f_SetComponentsDuplicate(arg1, -175.0f, BattleScene_GetParticipantModelHeight(arg0), 0.0f);
        } else if (arg0->unk_000.unk_01A == 0x5F) {
            Vec3f_SetComponentsDuplicate(arg1, -225.0f, BattleScene_GetParticipantModelHeight(arg0), 7.5000005f);
        } else {
            Vec3f_SetComponentsDuplicate(arg1, -150.0f, BattleScene_GetParticipantModelHeight(arg0), 0.0f);
        }
    } else if ((arg0->unk_000.unk_01A == 0x82) || (arg0->unk_000.unk_01A == 0x5F)) {
        Vec3f_SetComponentsDuplicate(arg1, 225.0f, BattleScene_GetParticipantModelHeight(arg0), 0.0f);
    } else if ((arg0->unk_000.unk_01A == 3) || (arg0->unk_000.unk_01A == 0x83)) {
        Vec3f_SetComponentsDuplicate(arg1, 175.0f, BattleScene_GetParticipantModelHeight(arg0), 0.0f);
    } else {
        Vec3f_SetComponentsDuplicate(arg1, 150.0f, BattleScene_GetParticipantModelHeight(arg0), 0.0f);
    }
}

void BattleScene_GetParticipantAuxiliaryModelPosition(unk_BattlePlayerEntity* arg0, Vec3f* arg1) {
    arg1->x = arg0->effectGraphNode.unk_024.x;
    arg1->y = arg0->effectGraphNode.unk_024.y + 2.5f;
    arg1->z = arg0->effectGraphNode.unk_024.z;
}

f32 BattleAnim_GetOwnerModelHeight(unk_BattlePlayerEntity* arg0) {
    if (arg0->animationMode == 0x10) {
        return BattleScene_GetParticipantModelWidth(arg0);
    }
    return BattleScene_GetParticipantModelWidth(arg0) * arg0->unk_000.unk_030.y;
}

f32 BattleScene_GetParticipantModelRadiusScaled(unk_BattlePlayerEntity* arg0) {
    return BattleScene_GetParticipantModelRadius(arg0) * arg0->unk_000.unk_030.y;
}

unk_D_86002F58_004_000_004* Battle_GetMoveEffectListEntry(unk_BattlePlayerEntity* arg0, s32 arg1) {
    return arg0->pokemonAnimation->unk_14->unk_00[2]->unk_00[arg1];
}

s32 Battle_GetTrainerId(unk_BattlePlayerEntity* arg0, UNUSED s32 arg1) {
    return arg0->pokemonAnimation->unk_02;
}

char* Battle_GetActiveMoveName(unk_BattlePlayerEntity* arg0) {
    return Text_GetString(NULL, 0, gPokemonMessageBank, arg0->animationState.unk_38.unk_5A - 1);
}

u8* Battle_GetActiveMonNickname(unk_BattlePlayerEntity* arg0) {
    return arg0->unk_724->unk_01C[arg0->animationState.unk_08].unk_30;
}

void BattleScene_SetParticipantModelFlags(unk_BattlePlayerEntity* arg0, s32 arg1, s32 arg2) {
    arg0->animationMode = arg1;
    arg0->animationSubstate = arg2;
}

void Battle_AdvanceSecondaryModelAnimIfFinished(unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1) {
    s32 idx;
    unk_BattleAnimDataEntry* sp30;
    unk_BattleAnimDataEntry* sp2C;
    unk_BattleAnimDataEntry* sp28;
    unk_BattlePlayerAnimState* sp20 = &arg0->animationState;

    idx = BattleScene_GetParticipantSideIndex(arg0);
    sp30 = &gAnimDataByPlayer[idx]->unk_A50;
    idx = BattleScene_GetParticipantSideIndex(arg0);
    sp2C = &gAnimDataByPlayer[idx]->unk_B00;
    idx = BattleScene_GetParticipantSideIndex(arg0);
    sp28 = &gAnimDataByPlayer[idx]->unk_AF0;

    if (!(sp20->unk_34 & 0x4002)) {
        if ((BattleAnim_IsSessionBusy(arg0) == 0) && (arg1->unk_000.unk_040.unk_00 != -1) &&
            (ModelAnim_IsFinished(&arg1->unk_000) == 1)) {
            if (sp20->unk_34 & 0x200) {
                ModelAnim_SetAnimation(&arg1->unk_000, sp2C->unk_00);
            } else if ((sp20->unk_34 & 1) && (BattleScene_ByteArrayContains(arg1->unk_000.unk_01A, gSpecialMoveIDs, 8) != 0)) {
                ModelAnim_SetAnimation(&arg1->unk_000, sp28->unk_00);
            } else {
                if (arg1->unk_000.unk_01A == 0x84) {
                    idx = BattleAnim_RandomRange(5);
                    ModelAnim_SetAnimation(&arg1->unk_000, idx + 0xE);
                } else {
                    ModelAnim_SetAnimation(&arg1->unk_000, sp30->unk_00);
                }

                if (!(sp20->unk_34 & 1)) {
                    BattleAnim_SetModelEventTrackAndState(arg0, 0xA5, 1);
                }
            }

            ModelAnim_SetFrame(&arg1->unk_000, 0);
        }
    }
}

void Battle_ResetModelToIdleAnim(unk_BattlePlayerEntity* arg0) {
    s32 idx;
    unk_BattlePlayerAnimState* sp24;
    unk_BattleAnimDataEntry* sp34;
    unk_BattleAnimDataEntry* sp30;
    unk_BattleAnimDataEntry* sp2C;

    sp24 = &arg0->animationState;
    idx = BattleScene_GetParticipantSideIndex(arg0);
    sp34 = &gAnimDataByPlayer[idx]->unk_A50;
    idx = BattleScene_GetParticipantSideIndex(arg0);
    sp30 = &gAnimDataByPlayer[idx]->unk_B00;
    idx = BattleScene_GetParticipantSideIndex(arg0);
    sp2C = &gAnimDataByPlayer[idx]->unk_AF0;

    if (!(sp24->unk_34 & 0x4002) && (BattleAnim_IsSessionBusy(arg0) == 0) && (arg0->unk_000.unk_040.unk_00 != -1)) {
        ModelAnim_SetFrame(&arg0->unk_000, 0);
        if (sp24->unk_34 & 0x200) {
            ModelAnim_SetAnimation(&arg0->unk_000, sp30->unk_00);
        } else if ((sp24->unk_34 & 1) && (BattleScene_ByteArrayContains(arg0->unk_000.unk_01A, gSpecialMoveIDs, 8) != 0)) {
            ModelAnim_SetAnimation(&arg0->unk_000, sp2C->unk_00);
        } else {
            if (arg0->unk_000.unk_01A == 0x84) {
                ModelAnim_SetAnimation(&arg0->unk_000, BattleAnim_RandomRange(5) + 0xE);
            } else {
                ModelAnim_SetAnimation(&arg0->unk_000, sp34->unk_00);
            }

            if (!(sp24->unk_34 & 1)) {
                BattleAnim_SetModelEventTrackAndState(arg0, 0xA5, 1);
            }
        }
    }
}

void Battle_SetModelToStatusAnim(unk_BattlePlayerEntity* arg0) {
    unk_BattleAnimDataEntry* sp1C = &gAnimDataByPlayer[BattleScene_GetParticipantSideIndex(arg0)]->unk_A80;

    if (arg0->unk_000.unk_040.unk_00 != -1) {
        ModelAnim_SetFrame(&arg0->unk_000, 0);
        ModelAnim_SetAnimation(&arg0->unk_000, sp1C->unk_00);
    }
}

void BattleScene_BindParticipantRosterForSide(unk_BattlePlayerEntity* arg0, s32 arg1) {
    arg0->unk_724 = arg0->pokemonAnimation->unk_08[arg1];
}

void BattleScene_SetParticipantSelectedSide(unk_BattlePlayerEntity* arg0, s32 arg1) {
    arg0->animationState.unk_2B = arg1;
}

void BattleScene_SetParticipantController(unk_BattlePlayerEntity* arg0, Controller* arg1) {
    arg0->animationState.controller = arg1;
}

void BattleScene_RebindParticipantToSide(unk_BattlePlayerEntity* arg0, s32 arg1) {
    unk_BattlePlayerAnimState* temp_v0 = &arg0->animationState;

    BattleScene_BindParticipantRosterForSide(arg0, arg1);
    BattleScene_SetParticipantSelectedSide(arg0, arg1);
    temp_v0->unk_08 = temp_v0->unk_18;
    arg0->unk_728.unk_16C = temp_v0->unk_2B;
}

s32 Battle_HasUsableSleepStatusTarget(unk_BattlePlayerEntity* arg0) {
    s32 i;
    unk_BattlePlayerAnimState* temp_s0;
    PokemonData* ptr;

    temp_s0 = &arg0->animationState;

    for (i = 0; i < BattleScene_GetSelectedSideTeamSize(arg0); i++) {
        ptr = &arg0->unk_724->unk_01C[i];
        if ((ptr->unk_05 & 0x20) && (arg0->animationState.unk_38.unk_16[temp_s0->unk_08 + temp_s0->unk_2B * 3] == 0)) {
            return 1;
        }
    }

    if (arg0->pokemonAnimation->unk_01 == 2) {
        for (i = 0; i < BattleScene_GetOpposingSelectedSideTeamSize(arg0); i++) {
            ptr = &arg0->pokemonAnimation->unk_08[temp_s0->unk_2B == 0]->unk_01C[i];
            if ((ptr->unk_05 & 0x20) &&
                (arg0->animationState.unk_38.unk_16[temp_s0->unk_08 + (temp_s0->unk_2B == 0) * 3] == 0)) {
                return 1;
            }
        }
    }

    return 0;
}

s32 Battle_HasUsableMajorStatusTarget(unk_BattlePlayerEntity* arg0) {
    s32 i;
    unk_BattlePlayerAnimState* temp_s0;
    PokemonData* ptr;

    temp_s0 = &arg0->animationState;

    for (i = 0; i < BattleScene_GetSelectedSideTeamSize(arg0); i++) {
        ptr = &arg0->unk_724->unk_01C[i];
        if ((ptr->unk_05 & 7) && (arg0->animationState.unk_38.unk_16[temp_s0->unk_08 + temp_s0->unk_2B * 3] == 0)) {
            return 1;
        }
    }

    if (arg0->pokemonAnimation->unk_01 == 2) {
        for (i = 0; i < BattleScene_GetOpposingSelectedSideTeamSize(arg0); i++) {
            ptr = &arg0->pokemonAnimation->unk_08[temp_s0->unk_2B == 0]->unk_01C[i];
            if ((ptr->unk_05 & 7) && (arg0->animationState.unk_38.unk_16[temp_s0->unk_08 + (temp_s0->unk_2B == 0) * 3] == 0)) {
                return 1;
            }
        }
    }
    return 0;
}

s32 BattleScene_GetCombinedTeamSize(unk_BattlePlayerEntity* arg0) {
    if (arg0->pokemonAnimation->unk_01 != 2) {
        return arg0->pokemonAnimation->unk_08[0]->unk_002;
    }
    return arg0->pokemonAnimation->unk_08[1]->unk_002 + arg0->pokemonAnimation->unk_08[0]->unk_002;
}

u8 BattleScene_GetRosterTeamSize(unk_D_800AE540_0004* arg0) {
    return arg0->unk_002;
}

s32 BattleScene_GetParticipantDisplayPlayerNumber(unk_BattlePlayerEntity* arg0) {
    return arg0->pokemonAnimation->unk_08[arg0->unk_728.unk_16C]->unk_001 + 1;
}

void BattleScene_ReinitParticipantBodyModel(unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1, s32 arg2, s32 arg3) {
    UNUSED s32 pad;
    unk_D_86002F58_004_000_004* sp20 = Battle_GetMoveEffectListEntry(arg0, 0);

    BattleScene_GetParticipantSideIndex(arg0);
    ModelRenderer_ClearDisplayObject(&arg1->unk_000);

    if (arg0 == sActivePokemon[0]) {
        arg1->unk_000.modelPhase = 0;
    } else {
        arg1->unk_000.modelPhase = 1;
    }

    Model_InitDisplayObject(&arg1->unk_000, 0, arg2, sp20);
    LoadPlayerAnimationData(arg0, arg3);
    ModelAnim_SetFrame(&arg1->unk_000, 0);
    ModelAnim_SetAnimation(&arg1->unk_000, 0);

    if ((arg1->unk_000.unk_01A == 0x32) || (arg1->unk_000.unk_01A == 0x33)) {
        arg1->unk_000.unk_000.unk_02 &= 0xFFBF;
    } else {
        arg1->unk_000.unk_000.unk_02 |= 0x40;
    }

    if (!(arg0->animationState.unk_34 & 0x200)) {
        if (arg0 == sActivePokemon[0]) {
            BattleScene_PositionParticipantModel(arg0);
            arg1->unk_000.unk_01E.y = 0x4000;
        } else {
            BattleScene_PositionParticipantModel(arg0);
            arg1->unk_000.unk_01E.y = -0x4000;
        }
    }
}

void BattleScene_ReinitParticipantOwnerModel(unk_BattlePlayerEntity* arg0, unk_D_84390010_728* arg1, s16 arg2) {
    unk_D_86002F58_004_000_004* sp24;

    sp24 = Battle_GetMoveEffectListEntry(arg0, 0);
    ModelRenderer_ClearDisplayObject(&arg1->unk_000);

    if (arg0 == sActivePokemon[0]) {
        arg1->unk_000.modelPhase = 0xFF;
    } else {
        arg1->unk_000.modelPhase = 0xFF;
    }

    if (arg0 == sActivePokemon[0]) {
        Model_InitDisplayObject(&arg1->unk_000, 1, arg2, sp24);
    } else {
        Model_InitDisplayObject(&arg1->unk_000, 2, arg2, sp24);
    }

    ModelAnim_SetFrame(&arg1->unk_000, 0);
    ModelAnim_SetAnimation(&arg1->unk_000, 0);
    arg1->unk_000.unk_000.unk_02 &= ~0x40;
}

void BattleScene_ReinitParticipantSecondaryModels(unk_BattlePlayerEntity* arg0, s16 arg1) {
    s32 i;
    unk_D_86002F58_004_000_004* sp58;
    unk_D_84390010_168* var_s0;

    sp58 = Battle_GetMoveEffectListEntry(arg0, 0);

    for (i = 0; i < 2; i++) {
        var_s0 = &arg0->unk_168[i];

        ModelRenderer_ClearDisplayObject(&var_s0->unk_000);
        if (arg0 == sActivePokemon[0]) {
            var_s0->unk_000.modelPhase = 0xFF;
        } else {
            var_s0->unk_000.modelPhase = 0xFF;
        }

        Model_InitDisplayObject(&var_s0->unk_000, 0, arg1, sp58);
        ModelAnim_SetFrame(&var_s0->unk_000, 0);
        ModelAnim_SetAnimation(&var_s0->unk_000, 0);

        var_s0->unk_000.unk_000.unk_02 &= ~0x40;

        if (arg0 == sActivePokemon[0]) {
            Vec3f_SetComponentsDuplicate(&var_s0->unk_000.unk_024, -150.0f, 0.0f, 0.0f);
            var_s0->unk_000.unk_01E.y = 0x4000;
        } else {
            Vec3f_SetComponentsDuplicate(&var_s0->unk_000.unk_024, 150.0f, 0.0f, 0.0f);
            var_s0->unk_000.unk_01E.y = -0x4000;
        }

        var_s0->unk_000.unk_000.unk_01 &= ~1;
    }
}

void Battle_ResetEventTrack(unk_BattlePlayerEntity* arg0) {
    if (arg0->animationState.unk_34 & 1) {
        BattleAnim_TrySetModelEventTrackFromRow(arg0, 0xAF, 2);
    } else {
        arg0->animationState.unk_36 = 0;
        ModelAnim_SetEventFrame(&arg0->unk_000, 0);
        ModelAnim_SetEventTrack(&arg0->unk_000, -1);
    }
}

void Battle_LoadOwnerModelForSpecies(unk_BattlePlayerEntity* arg0) {
    unk_BattlePlayerAnimState* ptr = &arg0->animationState;
    UNUSED s32 pad[3];
    s16 sp26;

    Battle_GetMoveEffectListEntry(arg0, 0);
    sp26 = Battle_GetTrainerId(arg0, 0);
    BattleScene_ReinitParticipantBodyModel(arg0, arg0, sp26, 0);
    BattleScene_ReinitParticipantOwnerModel(arg0, &arg0->unk_728, sp26);
    BattleScene_ReinitParticipantSecondaryModels(arg0, sp26);
    Battle_ResetEventTrack(arg0);
    ptr->unk_34 &= 0x1800;
    Vec3f_SetComponentsDuplicate(&arg0->unk_000.unk_030, 1.0f, 1.0f, 1.0f);
}

void Battle_LoadOwnerModelForSwitchIn(unk_BattlePlayerEntity* arg0) {
    unk_BattlePlayerAnimState* ptr = &arg0->animationState;
    UNUSED s32 pad[3];
    s16 sp26;

    Battle_GetMoveEffectListEntry(arg0, 0);
    sp26 = Battle_GetTrainerId(arg0, 0);
    BattleScene_ReinitParticipantBodyModel(arg0, arg0, sp26, 1);
    BattleScene_ReinitParticipantOwnerModel(arg0, &arg0->unk_728, sp26);
    BattleScene_ReinitParticipantSecondaryModels(arg0, sp26);
    Battle_ResetEventTrack(arg0);
    ptr->unk_2D = 0;
    ptr->unk_34 &= 0x1800;
    Vec3f_SetComponentsDuplicate(&arg0->unk_000.unk_030, 1.0f, 1.0f, 1.0f);
}

void Battle_ResetOwnerModelToNeutralPlaceholder(unk_BattlePlayerEntity* arg0) {
    Model_SetMaterialColor(&arg0->unk_000, 0xFF, 0xFF, 0xFF, arg0->animationState.unk_2E = 0xFF);
    arg0->animationState.unk_BC = arg0->unk_000.unk_01A;
    BattleScene_ReinitParticipantBodyModel(arg0, arg0, 0x98, 0);
    BattleScene_ReinitParticipantSecondaryModels(arg0, 0x98);
    Battle_ResetEventTrack(arg0);
}

void Battle_ReloadNeutralPlaceholderModel(unk_BattlePlayerEntity* arg0) {
    BattleScene_ReinitParticipantBodyModel(arg0, arg0, 0x98, 0);
    BattleScene_ReinitParticipantSecondaryModels(arg0, 0x98);
    Battle_ResetEventTrack(arg0);
}

void Battle_ReloadModelForActiveMove(unk_BattlePlayerEntity* arg0) {
    UNUSED s32 pad[3];
    unk_BattlePlayerAnimState* ptr = &arg0->animationState;
    s16 sp2E = Battle_GetTrainerId(arg0, 0);

    ptr->unk_2E = 0xFF;
    Model_SetMaterialColor(&arg0->unk_000, 0xFF, 0xFF, 0xFF, ptr->unk_2E);
    BattleScene_ReinitParticipantBodyModel(arg0, arg0, sp2E, 0);
    BattleScene_ReinitParticipantSecondaryModels(arg0, sp2E);
    Battle_ResetEventTrack(arg0);
}
