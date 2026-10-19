#include "battle_engine.h"
#include "src/model_animation.h"
#include "src/model_animation_events.h"
#include "src/model_renderer.h"
#include "src/pokemon_stats.h"
#include "src/text_system.h"
#include "src/gb_save.h"
#include "src/audio_commands.h"
#include "src/3FB0.h"
#include "src/audio_fade.h"
#include "src/audio_stored_fade.h"
#include "src/audio_loop_point.h"
#include "src/cry.h"
#include "src/matrix.h"
#include "src/memory.h"

static unk_D_8438E7B0 gAnimDataPlayer0;
static unk_D_8438E7B0 gAnimDataPlayer1;
static unk_D_8438FF70 gAnimDataSetB0;
static unk_D_8438FF70 gAnimDataSetB1;
static unk_D_8438FF70 gAnimDataSetC0;
static unk_D_8438FF70 gAnimDataSetC1;
static unk_D_84384588 gAnimExtraDataPlayer0;
static unk_D_84384588 gAnimExtraDataPlayer1;
BattlePlayerEntity* sActivePokemon[2];
BattlePlayerEntity* gPrimaryPokemonEntity;
BattlePlayerEntity* gPokemonEntityUnused;
static BattleAnimDataEntry* gCurrentAnimChannel;
unk_D_84390028 gPokemonModelDimensions[2];
static unk_D_84390048 gAnimTempVector;
static unk_D_84390068 gBattleSceneStateTickSlots[7];
static s32 gAnimStateQueueIndex;
static s32 gAnimStateQueueCount;
f32 gPlayerScaleFactors[2];

unk_D_8438E7B0* gAnimDataByPlayer[] = { &gAnimDataPlayer0, &gAnimDataPlayer1 };
unk_D_8438FF70* gAnimDataSetB[] = {
    &gAnimDataSetB0,
    &gAnimDataSetB1,
};
unk_D_8438FF70* gAnimDataSetC[] = {
    &gAnimDataSetC0,
    &gAnimDataSetC1,
};
unk_D_84384588* gAnimExtraDataByPlayer[] = { &gAnimExtraDataPlayer0, &gAnimExtraDataPlayer1 };
u8 gSpecialMoveIDs[] = { 0x39, 0x67, 0x64, 0x6D, 0x28, 0x6E, 0x2A, 0x47 };
static u8 gSpecialConditionIDs[] = { 0x64, 0x6E };
static u8 gStatMaskIndices[] = {
    0x06, 0x0C, 0x30, 0x31, 0x32, 0x33, 0x8D, 0x96, 0x97,
};
static u8 gStatMaskEntry0[] = {
    0x06,
    0x2E,
};
static u8 gStatMaskEntry1[] = {
    0x06,
    0x42,
};
static u8 gStatMaskEntry2[] = {
    0x06,
    0x42,
};
static u8 gStatMaskEntry3[] = {
    0x06,
    0x42,
};
static u8 gStatMaskEntry4[] = {
    0x06,
    0x06,
};
static u8 gStatMaskEntry5[] = {
    0x06,
    0x06,
};
static u8 gStatMaskEntry6[] = {
    0x06,
    0x16,
};
static u8 gStatMaskEntry7[] = {
    0x01,
    0x7F,
};
static u8 gStatMaskEntry8[] = {
    0x06,
    0x7F,
};
static u8* gStatMaskTable[] = {
    gStatMaskEntry0, gStatMaskEntry1, gStatMaskEntry2, gStatMaskEntry3, gStatMaskEntry4, gStatMaskEntry5, gStatMaskEntry6, gStatMaskEntry7, gStatMaskEntry8,
};
u8 gPokemonSfxId_0 = 0x8E;
u8 gPokemonSfxId_1 = 0x16;
u8 gPokemonSfxId_2 = 0x53;
u8 gPokemonSfxId_3[] = { 0x55, 0x54 };

char** gMessageBank_0x1E;
char** gMessageBank_0x24;
char** gPokemonMessageBank;
char** gMessageBank_0x29;
char** gMarqueeMessageBank;

void BattleScene_ClearStateTickCallbacks(void) {
    s32 i;

    for (i = 0; i < 7; i++) {
        gBattleSceneStateTickSlots[i].rotation = gAnimStateIdle;
    }
}

void BattleScene_QueueRowEffectList3(BattlePlayerEntity* arg0, s32 arg1) {
    BattleAnim_QueueEffectList3(arg1, &arg0->unk_000, &arg0->unk_000, 0xFF, 0xFF);
}

void BattleAnim_PlayMoveEffectScriptA(BattlePlayerEntity* arg0, s32 arg1) {
    UNUSED s16 pad;
    s16 sp24;
    s32 sp20;

    sp20 = BattleScene_GetParticipantSideIndex(arg0) == 0;
    sp24 = Battle_GetCameraShotFieldB(arg0);
    BattleAnim_QueueMoveEffectScriptA(arg1, arg0, sActivePokemon[sp20], sp24, Battle_GetCameraShotFieldC(arg0));
}

void BattleAnim_PlayMoveEffectScriptB(BattlePlayerEntity* arg0, s32 arg1) {
    UNUSED s16 pad;
    s16 sp24;
    s32 sp20;

    sp20 = BattleScene_GetParticipantSideIndex(arg0) == 0;
    sp24 = Battle_GetCameraShotFieldB(arg0);
    BattleAnim_QueueMoveEffectScriptB(arg1, arg0, sActivePokemon[sp20], sp24, Battle_GetCameraShotFieldC(arg0));
}

void BattleAnim_PlayMoveEffectEnd(BattlePlayerEntity* arg0, s32 arg1) {
    UNUSED s16 pad;
    s16 sp24;
    s32 sp20;

    sp20 = BattleScene_GetParticipantSideIndex(arg0) == 0;
    sp24 = Battle_GetSideAnimTableFieldB(arg0);
    BattleAnim_QueueMoveEffectEnd(arg1, sActivePokemon[sp20], arg0, sp24, Battle_GetSideAnimTableFieldC(arg0));
}

void BattleScene_TickClearAnimRecordIfLoaded(BattlePlayerEntity* arg0) {
    if (BattleAnim_TryRegisterAssetTables(arg0) != 0) {
        arg0->animationStateIndex = 0;
        gBattleSceneStateTickSlots[gAnimStateQueueIndex].rotation = gAnimStateIdle;
    }
}

void BattleScene_TickStartRowAnimRecord(BattlePlayerEntity* arg0) {
    UNUSED s32 pad;
    s32 idx = arg0->moveAnimIndex;
    s32 sp24 = gMoveAnimData[idx].unk_20;

    gCurrentAnimChannel = &gAnimDataByPlayer[BattleScene_GetParticipantSideIndex(arg0)]->unk_000[sp24];
    if (BattleAnim_TryRegisterAssetTables(arg0) != 0) {
        BattleAnim_SetModelEventTrackAndState(arg0, sp24, 2);
        arg0->animationStateIndex = 0;
        gBattleSceneStateTickSlots[gAnimStateQueueIndex].rotation = gAnimStateIdle;
        ModelAnim_SetFrame(&arg0->unk_000, 0);
        ModelAnim_SetAnimation(&arg0->unk_000, gCurrentAnimChannel->posX);
    }
}

void BattleScene_TickQueueRowEffectList3AtAnimEnd(BattlePlayerEntity* arg0) {
    s32 idx = arg0->moveAnimIndex;
    s32 sp28 = gMoveAnimData[idx].unk_20;

    gCurrentAnimChannel = &gAnimDataByPlayer[BattleScene_GetParticipantSideIndex(arg0)]->unk_000[sp28];
    if (BattleScene_GetParticipantModelHeight(arg0) != 0.0f) {
        gBattleSceneStateTickSlots[gAnimStateQueueIndex].rotation = gAnimStateIdle;
    } else if ((arg0->animationStateIndex == (gCurrentAnimChannel->rotation + 1)) && (BattleAnim_IsAssetLoadBusy(arg0) == 0)) {
        BattleScene_QueueRowEffectList3(arg0, gMoveAnimData[idx].unk_24);
        gBattleSceneStateTickSlots[gAnimStateQueueIndex].rotation = gAnimStateIdle;
    }
}

void BattleScene_ResetStateFrameCounter(BattlePlayerEntity* arg0) {
    arg0->animationStateIndex = 0;
}

void BattleScene_ResetOpponentStateFrameCounter(BattlePlayerEntity* arg0) {
    sActivePokemon[BattleScene_GetParticipantSideIndex(arg0) == 0]->animationStateIndex = 0;
}

void BattleAnim_SetOverlayFlagForSpecialMoves(BattlePlayerEntity* arg0) {
    PokemonAudioInfo* ptr = &arg0->animationState.unk_38;

    if (ptr->currentMoveId == 0x46 || ptr->currentMoveId == 0x9D || ptr->currentMoveId == 0x58) {
        sActivePokemon[0]->unk_000.unk_000.posY |= 2;
        sActivePokemon[1]->unk_000.unk_000.posY |= 2;
    }
}

void BattleAnim_ClearOverlayFlag(BattlePlayerEntity* arg0) {
    sActivePokemon[0]->unk_000.unk_000.posY &= ~2;
    sActivePokemon[1]->unk_000.unk_000.posY &= ~2;
}

s32 BattleAnim_IsAssetLoadBusy(BattlePlayerEntity* arg0) {
    return arg0->pokemonAnimation->unk_1D & 0xD0;
}

s32 BattleAnim_PollAssetLoadBusyFlags(BattlePlayerEntity* arg0) {
    PokeIcon_PollBackgroundForObject(arg0->pokemonAnimation);
    return arg0->pokemonAnimation->unk_1D & 0xC0;
}

s32 BattleAnim_IsSessionBusy(BattlePlayerEntity* arg0) {
    return arg0->pokemonAnimation->posX & 0xD0;
}

s32 BattleAnim_TryRegisterAssetTables(BattlePlayerEntity* arg0) {
    if (BattleAnim_PollAssetLoadBusyFlags(arg0) == 0) {
        BattleAnim_RegisterAssetTablesForSession(arg0->pokemonAnimation);
        return 1;
    }
    return 0;
}

void BattleScene_LoadMoveResourceList(BattlePlayerEntity* arg0) {
    if (gBattleScene.posX->unk_48 == 0xE) {
        BattleAnim_LoadMoveResourceList(arg0->pokemonAnimation, BattleScene_GetActiveAnimRowId(arg0));
    } else {
        BattleAnim_LoadMoveResourceList(arg0->pokemonAnimation, BattleScene_GetActiveAnimRowId(arg0));
    }
}

void BattleScene_LoadRowResourceList(BattlePlayerEntity* arg0) {
    s32 idx = arg0->moveAnimIndex;

    BattleAnim_LoadModeResourceList(arg0->pokemonAnimation, gMoveAnimData[idx].unk_24);
}

void BattleScene_ReloadMoveResourceList(BattlePlayerEntity* arg0) {
    BattleAnim_LoadMoveResourceList(arg0->pokemonAnimation, BattleScene_GetActiveAnimRowId(arg0));
}

void BattleAnim_BeginSessionRequest(BattlePlayerEntity* arg0) {
    arg0->pokemonAnimation->posY = 0x98;
    arg0->pokemonAnimation->posX |= 0x80;
}

void BattleAnim_BeginSessionRequestForActiveMon(BattlePlayerEntity* arg0) {
    arg0->pokemonAnimation->rotation = &arg0->boundRoster->unk_01C[arg0->animationState.RentalSlotAnimData_PosePhase];
    arg0->pokemonAnimation->posX |= 0x80;
    arg0->pokemonAnimation->posY = arg0->animationState.unk_BC;
}

s32 BattleScene_FindU16InByteArray(u16 arg0, u8* arg1, s32 arg2) {
    s32 var_v1 = 0;

    while (arg2--) {
        if (arg0 == *arg1) {
            return var_v1;
        }
        arg1++;
        var_v1++;
    }

    return -1;
}

void Battle_FilterUnusableMoves(BattlePlayerEntity* arg0, u16 arg1, unk_D_84390010_94C* arg2, unk_D_84390010_94C* arg3) {
    s32 i;
    s32 j;
    s32 temp_v0_3;
    s32 temp_v1_2;
    u8 var_a0;
    gBaseStats* temp_s4; //TODO: this is definitely typed wrong
    PokemonAudioInfo* temp_s5;

    temp_s5 = &arg0->animationState.unk_38;

    for (i = 0; i < 4; i++) {
        if (temp_s5->unk_1F[i] != 0) {
            temp_s4 = &gSpeciesBaseStats[arg1];

            for (j = 0; j < ARRAY_COUNT(temp_s4->unk_0A); j++) {
                if ((temp_s4->unk_0A[j] != 0) && (temp_s4->unk_0A[j] == temp_s5->unk_1F[i])) {
                    arg0->animationState.statFlags[i] = 0;
                }
            }

            for (j = 0; j < 10; j++) {
                if ((arg2->posX[j] != 0) && (temp_s5->unk_26 >= arg2->posX[j]) &&
                    (arg2->unk_0A[j] == temp_s5->unk_1F[i])) {
                    arg0->animationState.statFlags[i] = 0;
                }
            }

            for (j = 0; j < 10; j++) {
                if ((arg3->posX[j] != 0) && (temp_s5->unk_26 >= arg3->posX[j]) &&
                    (arg3->unk_0A[j] == temp_s5->unk_1F[i])) {
                    arg0->animationState.statFlags[i] = 0;
                }
            }

            for (j = 0; j < 0x37; j++) {
                temp_v0_3 = BattleScene_FindU16InByteArray(arg1 + 1, gStatMaskIndices, 9);
                if (temp_v0_3 >= 0) {
                    temp_v1_2 = j / 8;
                    if (temp_v1_2 == gStatMaskTable[temp_v0_3][0]) {
                        var_a0 = temp_s4->unk_0F[temp_v1_2] | gStatMaskTable[temp_v0_3][1];
                    } else {
                        var_a0 = temp_s4->unk_0F[temp_v1_2];
                    }
                } else {
                    var_a0 = temp_s4->unk_0F[j / 8];
                }

                if (((var_a0 >> (j % 8)) & 1) && (Move_GetIdFromTableIndex(j) == temp_s5->unk_1F[i])) {
                    arg0->animationState.statFlags[i] = 0;
                }
            }
        } else {
            arg0->animationState.statFlags[i] = 0;
        }
    }
}

void Battle_InitializeMoveUsabilityMask(BattlePlayerEntity* arg0) {
    arg0->animationState.statFlags[0] = 1;
    arg0->animationState.statFlags[1] = 1;
    arg0->animationState.statFlags[2] = 1;
    arg0->animationState.statFlags[3] = 1;

    Battle_FilterUnusableMoves(arg0, arg0->animationState.unk_38.unk_0B - 1, &arg0->unk_94C, &arg0->unk_9AC);

    if (gAnimExtraDataByPlayer[BattleScene_GetParticipantSideIndex(arg0)]->posX != 0) {
        Battle_FilterUnusableMoves(arg0, gAnimExtraDataByPlayer[BattleScene_GetParticipantSideIndex(arg0)]->posX - 1, &arg0->unk_96C, &arg0->unk_9CC);
    }

    if (gAnimExtraDataByPlayer[BattleScene_GetParticipantSideIndex(arg0)]->TrainerSlotSaveData_GamePort != 0) {
        Battle_FilterUnusableMoves(arg0, gAnimExtraDataByPlayer[BattleScene_GetParticipantSideIndex(arg0)]->TrainerSlotSaveData_GamePort - 1, &arg0->unk_98C, &arg0->unk_9EC);
    }
}

void Battle_DmaLoadAnimRecord(u8 arg0, u32 arg1) {
    u32 temp_a1 = (u32)_70D3A0_ROM_START + ((u32)&D_72780[arg0 - 1] & 0xFFFFFF);

    Dma_WriteChunks(arg1, temp_a1, temp_a1 + 0x20, 0);
}

void Battle_DmaLoadAnimRecordPair(s32 arg0, unk_D_84390010_94C* arg1, unk_D_84390010_94C* arg2) {
    UNUSED s32 pad[3];
    u32 temp_a1;

    temp_a1 = (u32)_70D3A0_ROM_START + ((u32)&D_72780[arg0] & 0xFFFFFF);
    Dma_WriteChunks(arg1, temp_a1, temp_a1 + 0x20, 0);
    temp_a1 = (u32)_70D3A0_ROM_START + ((u32)&D_73A60[arg0] & 0xFFFFFF);
    Dma_WriteChunks(arg2, temp_a1, temp_a1 + 0x20, 0);
}

void LoadPlayerAnimationData(BattlePlayerEntity* arg0, s32 arg1) {
    s16 sp6E;
    s32 sp68;
    s16 sp66;
    u32 var_a1;
    s32 pad[8];
    PokemonData* ptr;
    unk_D_8438FF70* ptr2;
    u32 tmp;

    sp68 = BattleScene_GetParticipantSideIndex(arg0);
    sp66 = arg0->unk_000.unk_01A - 1;

    ptr = &arg0->pokemonAnimation->RentalSlotAnimData_PosePhase[arg0->animationState.unk_2C]->unk_01C[arg0->animationState.unk_18];
    // Fake: dead early copy of the D_6E910 address pair so its two spill temps are created
    // before sp68 * 4 (IDO orders compiler-temp slots by first appearance in the source).
    var_a1 = (u32)_70D3A0_ROM_START + ((u32)(D_6E910 + (sp66 << 5)) & 0xFFFFFF);
    tmp = var_a1 + 0x20;

    var_a1 = (u32)_70D3A0_ROM_START + ((u32)gStageRomOffsets[sp66] & 0xFFFFFF);
    if ((arg0->unk_000.unk_01A == 0x19) && (ptr->unk_52 & 0x80)) {
        var_a1 = (u32)_70D3A0_ROM_START + ((u32)gStageRomOffsets[152] & 0xFFFFFF);
    }
    Dma_WriteChunks(gAnimDataByPlayer[sp68], var_a1, var_a1 + 0xBC0, 0);

    var_a1 = (u32)_70D3A0_ROM_START + ((u32)(D_6E910 + (sp66 << 5)) & 0xFFFFFF);
    Dma_WriteChunks(gAnimDataSetC[sp68], var_a1, var_a1 + 0x20, 0);

    if (sp68 == 1) {
        var_a1 = (u32)_70D3A0_ROM_START + ((u32)(D_6E910 + (sp66 << 5)) & 0xFFFFFF);
        Dma_WriteChunks(gAnimDataSetB[sp68], var_a1, var_a1 + 0x20, 0);

        ptr2 = gAnimDataSetB[sp68];
        if (ptr2->unk_10 != 0xFF) {
            sp6E = ptr2->unk_10;

            var_a1 = ((u32)_70D3A0_ROM_START) + (((u32)(D_6E910 + ((ptr2->unk_10 - (tmp = 2)) * 0x20))) & 0xFFFFFF);
            Dma_WriteChunks(ptr2, var_a1, var_a1 + 0x20, 0);

            gAnimDataSetB[sp68]->unk_10 = sp6E;
        }
    } else {
        var_a1 = (u32)_70D3A0_ROM_START + ((u32)(D_6E910 + (sp66 << 5)) & 0xFFFFFF);
        Dma_WriteChunks(gAnimDataSetB[sp68], var_a1, var_a1 + 0x20, 0);
    }

    var_a1 = (u32)_70D3A0_ROM_START + ((u32)(D_70B10 + (sp66 * 0x20)) & 0xFFFFFF);
    Dma_WriteChunks(&gAnimTempVector, var_a1, var_a1 + 0x20, 0);

    BattleAnim_Vec3fCopy(&arg0->unk_448.unk_24.posX, &gAnimTempVector.posX);
    BattleAnim_Vec3fCopy(&arg0->unk_448.unk_24.unk_0C, &gAnimTempVector.unk_0C);

    arg0->unk_448.unk_24.unk_18 = gAnimTempVector.unk_18;
    arg0->unk_448.unk_24.unk_19 = gAnimTempVector.unk_19;
    arg0->unk_448.unk_24.unk_1A = gAnimTempVector.unk_1A;
    arg0->unk_448.unk_24.unk_1B = gAnimTempVector.unk_1B;
    arg0->unk_448.unk_24.posX.x *= arg0->sideSign;
    arg0->unk_448.unk_24.unk_0C.x *= arg0->sideSign;

    var_a1 = (u32)_70D3A0_ROM_START + ((u32)(D_70110 + (sp66 << 4)) & 0xFFFFFF);
    Dma_WriteChunks(&gPokemonModelDimensions[sp68], var_a1, var_a1 + 0x10, 0);

    var_a1 = (u32)_70D3A0_ROM_START + ((u32)(D_71E10 + (sp66 * 0x10)) & 0xFFFFFF);
    Dma_WriteChunks(gAnimExtraDataByPlayer[sp68], var_a1, var_a1 + 0x10, 0);

    Battle_DmaLoadAnimRecordPair(sp66, &arg0->unk_94C, &arg0->unk_9AC);

    if (gAnimExtraDataByPlayer[sp68]->posX != 0) {
        Battle_DmaLoadAnimRecordPair(gAnimExtraDataByPlayer[sp68]->posX - 1, &arg0->unk_96C, &arg0->unk_9CC);
    }

    if (gAnimExtraDataByPlayer[sp68]->TrainerSlotSaveData_GamePort != 0) {
        Battle_DmaLoadAnimRecordPair(gAnimExtraDataByPlayer[sp68]->TrainerSlotSaveData_GamePort - 1, &arg0->unk_98C, &arg0->unk_9EC);
    }

    if (arg1 == 1) {
        Battle_InitializeMoveUsabilityMask(arg0);
    }
}

void BattleScene_TickRow10CleanupAndEnterState18(BattlePlayerEntity* arg0) {
    if (arg0->animationStateIndex == 0x14) {
        arg0->pokemonAnimation->posX |= 0x80;
    }

    if (arg0->pokemonAnimation->posX & 0x10) {
        arg0->pokemonAnimation->posX &= ~0x90;
        Battle_LoadOwnerModelForSwitchIn(arg0);
        BattleScene_TickOwnerCameraFraming(arg0);
        Audio_PlayCommand(2, 0, 0);
        gBattleSceneStateTickSlots[gAnimStateQueueIndex].rotation = gAnimStateIdle;
        BattleScene_EnterStateRow(arg0, 0x12);
    }
}

void BattleScene_EnterRow3StartMoveAnim(BattlePlayerEntity* arg0) {
    PokemonAudioInfo* sp24;
    BattlePlayerAnimState* sp20;
    s32 idx;
    s16 sp2A;
    u8 tmp;

    sp2A = arg0->unk_000.unk_01A - 1;
    sp24 = &arg0->animationState.unk_38;
    sp20 = &arg0->animationState;
    idx = BattleScene_GetParticipantSideIndex(arg0);

    gCurrentAnimChannel = &gAnimDataByPlayer[idx]->unk_000[sp24->currentMoveId - 1];

    if (!(sp20->unk_34 & 2)) {
        arg0->animationStateIndex = 0;

        if (BattleScene_IsPartnerPikachu(arg0) != 0) {
            tmp = BattleScene_GetParticipantSideIndex(arg0);
            PlayMoveSoundEffect(tmp, sp24->currentMoveId, 0xC8, 0);
        } else {
            tmp = BattleScene_GetParticipantSideIndex(arg0);
            PlayMoveSoundEffect(tmp, sp24->currentMoveId, sp2A + 1, 0);
        }

        if ((sp20->unk_34 & 0x4000) && ((sp2A == 0x32) || (sp2A == 0x31))) {
            Battle_ClearRuntimeFlags(arg0, 8);
            arg0->unk_000.unk_000.posY |= 0x20;
            Battle_SetRuntimeFlags(arg0, 0x10);
            Battle_ClearRuntimeFlags(arg0, 0x4000);
        }

        BattleAnim_SetOverlayFlagForSpecialMoves(arg0);
        ModelAnim_SetAnimation(&arg0->unk_000, gCurrentAnimChannel->posX);
        BattleAnim_SetModelEventTrackFromRow(arg0, sp24->currentMoveId - 1);

        if (gCurrentAnimChannel->unk_0B != 0) {
            ModelAnim_SetFrame(&arg0->unk_000, gCurrentAnimChannel->unk_0B);
            ModelAnim_SetEventFrame(&arg0->unk_000, gCurrentAnimChannel->unk_0B);
            arg0->animationStateIndex = gCurrentAnimChannel->unk_0B;
        } else {
            ModelAnim_SetFrame(&arg0->unk_000, 0);
        }
    }
}

void BattleScene_TickRow3PlayMoveEffectScript(BattlePlayerEntity* arg0) {
    UNUSED s32 pad;
    s16 sp32 = arg0->unk_000.unk_01A - 1;
    PokemonAudioInfo* sp24;

    BattleScene_GetParticipantSideIndex(arg0);
    sp24 = &arg0->animationState.unk_38;
    gCurrentAnimChannel = &gAnimDataByPlayer[BattleScene_GetParticipantSideIndex(arg0)]->unk_000[sp24->currentMoveId - 1];

    if ((sp24->currentMoveId == 0x19) && (sp32 == 0x64)) {
        gBattleSceneStateTickSlots[gAnimStateQueueIndex].rotation = gAnimStateIdle;
    } else if ((arg0->animationStateIndex == (gCurrentAnimChannel->rotation + 1)) && (BattleAnim_IsAssetLoadBusy(arg0) == 0)) {
        if (gBattleScene.posX->unk_48 == 0x14) {
            gBattleSceneStateTickSlots[gAnimStateQueueIndex].rotation = gAnimStateIdle;
        } else if (sp24->unk_44.posX == 0x5B) {
            gBattleSceneStateTickSlots[gAnimStateQueueIndex].rotation = gAnimStateIdle;
        } else {
            if (sp24->unk_44.posX == 0x6E) {
                if ((sp32 != 7) && (sp32 != 8) && (sp32 != 0x5A) && (sp32 != 6)) {
                    BattleScene_SetParticipantModelFlags(arg0, 0xC, 0);
                    BattleAnim_PlayMoveEffectScriptA(arg0, sp24->currentMoveId);
                }
            } else {
                if (sp24->unk_44.posX == 0x45) {
                    BattleScene_SetParticipantModelFlags(arg0, 8, 0);
                } else if (sp24->unk_44.posX == 0x39) {
                    BattleScene_SetParticipantModelFlags(arg0, 0xA, 0);
                } else if (sp24->unk_44.posX == 0x60) {
                    BattleScene_SetParticipantModelFlags(arg0, 0xD, 0);
                } else if (sp24->unk_44.posX == 0x7F) {
                    BattleScene_SetParticipantModelFlags(arg0, 0xE, 0);
                } else if (sp24->unk_44.posX == 0x6B) {
                    BattleScene_SetParticipantModelFlags(arg0, 9, 0);
                } else {
                    BattleScene_SetParticipantModelFlags(arg0, gCurrentAnimChannel->unk_05, 0);
                }

                if ((sp24->currentMoveId == 0x9A) && (gCurrentMoveIndex == gTotalMoveCount)) {
                    BattleAnim_PlayMoveEffectScriptB(arg0, sp24->currentMoveId);
                } else {
                    BattleAnim_PlayMoveEffectScriptA(arg0, sp24->currentMoveId);
                }
            }
            gBattleSceneStateTickSlots[gAnimStateQueueIndex].rotation = gAnimStateIdle;
        }
    }
}

void BattleScene_TickRow3PostEffectCamera(BattlePlayerEntity* arg0) {
    PokemonAudioInfo* sp24 = &arg0->animationState.unk_38;

    gCurrentAnimChannel = &gAnimDataByPlayer[BattleScene_GetParticipantSideIndex(arg0)]->unk_000[sp24->currentMoveId - 1];

    if (arg0->animationStateIndex == (gCurrentAnimChannel->rotation + 1)) {
        if (BattleAnim_IsAssetLoadBusy(arg0) == 0) {
            if (gBattleScene.posX->unk_48 == 0x18) {
                gInitialMoveIndex--;
                if (gInitialMoveIndex < 0) {
                    if (gBattleMoveFailed != 0) {
                        BattleAnim_PlaySpeciesReactionSound(arg0, sp24, 2);
                    }
                } else {
                    BattleAnim_PlaySpeciesReactionSound(arg0, sp24, 3);
                }
            } else if (gBattleMoveFailed != 0) {
                BattleAnim_PlaySpeciesReactionSound(arg0, sp24, 2);
            } else {
                if ((sp24->currentMoveId == 0x2D) || (sp24->currentMoveId == 0x2E) || (sp24->currentMoveId == 0x59)) {
                    BattleScene_StartCameraShake(arg0);
                }
                BattleAnim_PlaySpeciesReactionSound(arg0, sp24, 0);
                AnimChannel_SetSubStateIfNeeded(arg0);
            }
            gBattleSceneStateTickSlots[gAnimStateQueueIndex].rotation = gAnimStateIdle;
        }
    }
}

void BattleScene_TickRow3QueueEffectList6(BattlePlayerEntity* arg0) {
    PokemonAudioInfo* sp24 = &arg0->animationState.unk_38;
    UNUSED s16 pad;
    s16 sp18;

    sp18 = sp24->currentMoveId;
    BattleScene_GetParticipantSideIndex(arg0);
    gCurrentAnimChannel = &gAnimDataByPlayer[BattleScene_GetParticipantSideIndex(arg0)]->unk_000[sp24->currentMoveId - 1];

    if (arg0->animationStateIndex == (gCurrentAnimChannel->unk_09 + 1)) {
        if (BattleAnim_IsAssetLoadBusy(arg0) == 0) {
            if (((sp18 == 0x4A) || (sp18 == 0x60) || (sp18 == 0x61) || (sp18 == 0x6A) || (sp18 == 0x6E) ||
                 (sp18 == 0xE) || (sp18 == 0x68) || (sp18 == 0x6B) || (sp18 == 0x6F) || (sp18 == 0x70) ||
                 (sp18 == 0x85) || (sp18 == 0x97) || (sp18 == 0x9F)) &&
                (gAnimStateFlag == 1)) {
                BattleAnim_QueueEffectList6(3, arg0);
                Audio_PlayCommand(0x23, 0, 0);
            }
            gBattleSceneStateTickSlots[gAnimStateQueueIndex].rotation = gAnimStateIdle;
        }
    }
}

void AnimChannel_SetSubStateIfNeeded(BattlePlayerEntity* arg0) {
    PokemonAudioInfo* temp_v1 = &arg0->animationState.unk_38;

    gCurrentAnimChannel = &gAnimDataByPlayer[BattleScene_GetParticipantSideIndex(arg0)]->unk_000[temp_v1->currentMoveId - 1];

    if (temp_v1->currentMoveId == 0x6A) {
        Model_SetMaterialTextureMode(&arg0->unk_000, 1);
    }
}

void BattleScene_EnterRow21StartAnimRecord0(BattlePlayerEntity* arg0) {
    UNUSED s32 pad[2];
    BattlePlayerAnimState* temp_v1 = &arg0->animationState;
    s16 sp22;

    sp22 = arg0->unk_000.unk_01A - 1;
    gCurrentAnimChannel = gAnimDataByPlayer[BattleScene_GetParticipantSideIndex(arg0)]->unk_000;

    if (!(temp_v1->unk_34 & 2)) {
        arg0->animationStateIndex = 0;
        if ((temp_v1->unk_34 & 0x4000) && ((sp22 == 0x32) || (sp22 == 0x31))) {
            Battle_ClearRuntimeFlags(arg0, 8);
            arg0->unk_000.unk_000.posY |= 0x20;
            Battle_SetRuntimeFlags(arg0, 0x10);
            Battle_ClearRuntimeFlags(arg0, 0x4000);
        }
        ModelAnim_SetAnimation(&arg0->unk_000, gCurrentAnimChannel->posX);
        ModelAnim_SetFrame(&arg0->unk_000, 0);
        BattleAnim_SetModelEventTrackFromRow(arg0, 4);

        if (gCurrentAnimChannel->unk_0B != 0) {
            ModelAnim_SetFrame(&arg0->unk_000, gCurrentAnimChannel->unk_0B);
            ModelAnim_SetEventFrame(&arg0->unk_000, gCurrentAnimChannel->unk_0B);
            arg0->animationStateIndex = gCurrentAnimChannel->unk_0B;
        } else {
            ModelAnim_SetFrame(&arg0->unk_000, 0);
        }
    }
}

void BattleScene_TickRow21PlaySpeciesSound(BattlePlayerEntity* arg0) {
    gCurrentAnimChannel = &gAnimDataByPlayer[BattleScene_GetParticipantSideIndex(arg0)]->unk_000[0];
    if ((arg0->animationStateIndex == (gCurrentAnimChannel->rotation + 1)) && (BattleAnim_IsAssetLoadBusy(arg0) == 0)) {
        Effect_TriggerMoveVisual(1, arg0->unk_000.unk_01A, 0);
        gBattleSceneStateTickSlots[gAnimStateQueueIndex].rotation = gAnimStateIdle;
    }
}

void BattleScene_EnterRow19StartMoveAnimMidFrame(BattlePlayerEntity* arg0) {
    BattlePlayerAnimState* sp20;
    PokemonAudioInfo* ptr;

    sp20 = &arg0->animationState;
    ptr = &arg0->animationState.unk_38;
    gCurrentAnimChannel = &gAnimDataByPlayer[BattleScene_GetParticipantSideIndex(arg0)]->unk_000[ptr->currentMoveId - 1];

    if (sp20->unk_34 & 2) {
        return;
    }

    arg0->animationStateIndex = gCurrentAnimChannel->unk_06;
    if (!(sp20->unk_34 & 0x4000)) {
        BattleAnim_SetOverlayFlagForSpecialMoves(arg0);
        ModelAnim_SetAnimation(&arg0->unk_000, gCurrentAnimChannel->posX);
        ModelAnim_SetFrame(&arg0->unk_000, gCurrentAnimChannel->unk_06);
        if (gCurrentAnimChannel->TrainerSlotSaveData_GamePort != 0xFF) {
            ModelAnim_SetEventTrack(&arg0->unk_000, gCurrentAnimChannel->TrainerSlotSaveData_GamePort);
            ModelAnim_SetEventFrame(&arg0->unk_000, gCurrentAnimChannel->unk_06);
            sp20->unk_36 = 1;
        }
    }
}

void BattleScene_TickRow19PlayMoveEffectScript(BattlePlayerEntity* arg0) {
    PokemonAudioInfo* sp20;
    s32 var_v0;

    sp20 = &arg0->animationState.unk_38;
    gCurrentAnimChannel = &gAnimDataByPlayer[BattleScene_GetParticipantSideIndex(arg0)]->unk_000[sp20->currentMoveId - 1];
    if (sp20->currentMoveId == 0x9A) {
        var_v0 = gCurrentAnimChannel->rotation + 0x1E;
    } else {
        var_v0 = gCurrentAnimChannel->rotation + 1;
    }

    if ((var_v0 == arg0->animationStateIndex) && (BattleAnim_IsAssetLoadBusy(arg0) == 0)) {
        if (gBattleScene.posX->unk_48 == 0x14) {
            gBattleSceneStateTickSlots[gAnimStateQueueIndex].rotation = gAnimStateIdle;
            return;
        }

        if ((sp20->currentMoveId == 0x9A) && (gCurrentMoveIndex == gTotalMoveCount)) {
            BattleAnim_PlayMoveEffectScriptB(arg0, sp20->currentMoveId);
        } else {
            BattleAnim_PlayMoveEffectScriptA(arg0, sp20->currentMoveId);
        }

        if (sp20->unk_44.posX == 0x45) {
            BattleScene_SetParticipantModelFlags(arg0, 8, 0);
        } else if (sp20->unk_44.posX == 0x39) {
            BattleScene_SetParticipantModelFlags(arg0, 0xA, 0);
        } else {
            BattleScene_SetParticipantModelFlags(arg0, gCurrentAnimChannel->unk_05, 0);
        }
        gBattleSceneStateTickSlots[gAnimStateQueueIndex].rotation = gAnimStateIdle;
    }
}

void BattleScene_TickRow19PostEffectCamera(BattlePlayerEntity* arg0) {
    PokemonAudioInfo* sp18;
    s32 var_v0;

    sp18 = &arg0->animationState.unk_38;
    gCurrentAnimChannel = &gAnimDataByPlayer[BattleScene_GetParticipantSideIndex(arg0)]->unk_000[sp18->currentMoveId - 1];

    if (sp18->currentMoveId == 0x9A) {
        var_v0 = gCurrentAnimChannel->rotation + 0x1E;
    } else {
        var_v0 = gCurrentAnimChannel->rotation + 1;
    }

    if (var_v0 == arg0->animationStateIndex) {
        if (BattleAnim_IsAssetLoadBusy(arg0) == 0) {
            if (gBattleScene.posX->unk_48 == 0x18) {
                gInitialMoveIndex--;
                if (gInitialMoveIndex < 0) {
                    if (gBattleMoveFailed != 0) {
                        BattleAnim_PlaySpeciesReactionSound(arg0, sp18, 2);
                    } else {
                        BattleAnim_PlaySpeciesReactionSound(arg0, sp18, 0);
                    }
                } else {
                    BattleAnim_PlaySpeciesReactionSound(arg0, sp18, 3);
                }
            } else if (gBattleMoveFailed != 0) {
                BattleAnim_PlaySpeciesReactionSound(arg0, sp18, 2);
            } else {
                BattleAnim_PlaySpeciesReactionSound(arg0, sp18, 0);
            }
            gBattleSceneStateTickSlots[gAnimStateQueueIndex].rotation = gAnimStateIdle;
        }
    }
}

void BattleScene_EnterRow4StartHitReactionAnim(BattlePlayerEntity* arg0) {
    UNUSED s32 pad[3];
    s32 sp40;
    BattlePlayerAnimState* sp3C;
    UNUSED s32 pad2;
    s32 temp_v0;
    PokemonAudioInfo* sp28;
    BattlePlayerEntity* temp_a1;

    sp28 = &arg0->animationState.unk_38;
    sp40 = BattleScene_GetParticipantSideIndex(arg0) == 0;
    sp3C = &sActivePokemon[sp40]->animationState;
    temp_a1 = sActivePokemon[sp40];
    gCurrentAnimChannel = &gAnimDataByPlayer[sp40]->statusAnimChannel;

    if (sp3C->unk_34 & 1) {
        temp_v0 = BattleScene_ByteArrayContains(temp_a1->unk_000.unk_01A, gSpecialConditionIDs, 2);
        if (temp_v0 != 0) {
            gCurrentAnimChannel = &gAnimDataByPlayer[sp40]->unk_B20;
        }
    }

    sActivePokemon[sp40]->animationStateIndex = 0;

    if (!(sp3C->unk_34 & 0x200) && !(sp3C->unk_34 & 0x4000) && !(sp3C->unk_34 & 2)) {
        if (((gAnimTimer < 0xA) || (gBattleMoveFailed != 0)) && ((sp28->unk_15 & 0x20) == 0)) {
            gCurrentAnimChannel = &gAnimDataByPlayer[sp40]->idleAnimChannel;
            if (sp3C->unk_34 & 0x200) {
                gCurrentAnimChannel = &gAnimDataByPlayer[sp40]->faintedAnimChannel;
            }
        } else if (!(sp3C->unk_34 & 1)) {
            BattleAnim_SetModelEventTrackAndState(sActivePokemon[sp40], 0xA8, 1);
        }

        if ((gAnimTimer >= 0xB) && (BattleScene_IsPartnerPikachu(sActivePokemon[sp40]) != 0)) {
            Cry_Play(0xC8, 6);
        }

        if ((gAnimTimer == 0xA) && (BattleScene_IsPartnerPikachu(sActivePokemon[sp40]) != 0)) {
            Cry_Play(0xC8, 5);
        }

        if ((gBattleMoveFailed == 0) && (sp28->currentMoveId == 0x49)) {
            gCurrentAnimChannel = &gAnimDataByPlayer[sp40]->statusAnimChannel;
        }

        ModelAnim_SetFrame(&sActivePokemon[sp40]->unk_000, 0);
        ModelAnim_SetAnimation(&sActivePokemon[sp40]->unk_000, gCurrentAnimChannel->posX);

        if ((sp28->unk_44.posX == 0x17) || (sp28->unk_44.posX == 0x22) || (sp28->unk_44.posX == 0x45)) {
            BattleScene_SetParticipantModelFlags(sActivePokemon[sp40], 0xF, 0);
        }
    }
}

void BattleScene_TickPlayMoveEffectEnd(BattlePlayerEntity* arg0) {
    PokemonAudioInfo* sp20;
    s32 sp28;

    sp20 = &arg0->animationState.unk_38;
    sp28 = BattleScene_GetParticipantSideIndex(arg0);

    gCurrentAnimChannel = &gAnimDataByPlayer[BattleScene_GetParticipantSideIndex(arg0) == 0]->unk_000[sp20->currentMoveId - 1];

    if (sActivePokemon[sp28 == 0]->animationStateIndex == (gCurrentAnimChannel->unk_07 + 1)) {
        if (BattleAnim_IsAssetLoadBusy(arg0) == 0) {
            BattleAnim_CleanupEffects(1);
            if (sp20->unk_44.posX == 0x51) {
                if ((gAnimStateFlag != 0) && (gIsBattleMode != 0)) {
                    BattleAnim_PlayMoveEffectEnd(sActivePokemon[sp28 == 0], sp20->currentMoveId);
                    BattleScene_SetParticipantModelFlags(sActivePokemon[sp28 == 0], 0x10, 0);
                }
            } else {
                BattleAnim_PlayMoveEffectEnd(sActivePokemon[sp28 == 0], sp20->currentMoveId);
                if ((sp20->unk_44.posX == 0x14) || (sp20->unk_44.posX == 0x23) || (sp20->unk_44.posX == 0x84)) {
                    BattleScene_SetParticipantModelFlags(sActivePokemon[sp28 == 0], 0x10, 0);
                }
            }
            gBattleSceneStateTickSlots[gAnimStateQueueIndex].rotation = gAnimStateIdle;
        }
    }
}

void BattleScene_TickRow4PostEndCamera(BattlePlayerEntity* arg0) {
    PokemonAudioInfo* sp20;
    s32 sp28;

    sp28 = BattleScene_GetParticipantSideIndex(arg0) == 0;
    sp20 = &arg0->animationState.unk_38;

    gCurrentAnimChannel = &gAnimDataByPlayer[BattleScene_GetParticipantSideIndex(arg0) == 0]->unk_000[sp20->currentMoveId - 1];

    if ((gCurrentAnimChannel->unk_07 + 1) == sActivePokemon[sp28]->animationStateIndex) {
        if (BattleAnim_IsAssetLoadBusy(arg0) == 0) {
            if (gIsBattleMode == 1) {
                BattleAnim_PlaySpeciesReactionSound(sActivePokemon[sp28], sp20, 1);
            } else {
                BattleAnim_PlaySpeciesReactionSound(sActivePokemon[sp28], sp20, 5);
            }
            gBattleSceneStateTickSlots[gAnimStateQueueIndex].rotation = gAnimStateIdle;
        }
    }
}

void BattleScene_EnterRow15StartAnimA80Seq30(BattlePlayerEntity* arg0) {
    s32 sp1C = BattleScene_GetParticipantSideIndex(arg0);

    gCurrentAnimChannel = &gAnimDataByPlayer[sp1C]->statusAnimChannel;
    sActivePokemon[sp1C]->animationStateIndex = 0;
    ModelAnim_SetFrame(&arg0->unk_000, 0);
    ModelAnim_SetAnimation(&arg0->unk_000, gCurrentAnimChannel->posX);
    BattleAnim_SetModelEventTrackAndState(sActivePokemon[sp1C], 0xA8, 1);
    BattleAnim_PlayBattleSequenceById(arg0, 0x1E);
}

s32 BattleScene_IsOpponentRowCheckpointReached(BattlePlayerEntity* arg0) {
    PokemonAudioInfo* sp1C;

    sp1C = &sActivePokemon[BattleScene_GetParticipantSideIndex(arg0) == 0]->animationState.unk_38;
    gCurrentAnimChannel = &gAnimDataByPlayer[BattleScene_GetParticipantSideIndex(arg0)]->unk_000[sp1C->currentMoveId - 1];
    if (gCurrentAnimChannel->unk_0C != 0) {
        if (arg0->animationStateIndex == gCurrentAnimChannel->unk_0C) {
            return 1;
        }
        return 0;
    }
    return 0;
}

s32 BattleScene_IsRowZeroCheckpointReached(BattlePlayerEntity* arg0) {
    BattleScene_GetParticipantSideIndex(arg0);
    gCurrentAnimChannel = &gAnimDataByPlayer[BattleScene_GetParticipantSideIndex(arg0)]->unk_000[0];
    if (gCurrentAnimChannel->unk_0C != 0) {
        if (arg0->animationStateIndex == gCurrentAnimChannel->unk_0C) {
            return 1;
        }
        return 0;
    }
    return 0;
}

void Pokemon_ResetAnimAndTrigger(BattlePlayerEntity* arg0) {
    gCurrentAnimChannel = &gAnimDataByPlayer[BattleScene_GetParticipantSideIndex(arg0)]->statusAnimChannel;
    BattleAnim_SetModelEventTrackFromRow(arg0, 0xA8);
    arg0->animationStateIndex = 0;
    ModelAnim_SetFrame(&arg0->unk_000, 0);
    ModelAnim_SetAnimation(&arg0->unk_000, gCurrentAnimChannel->posX);
}

void BattleScene_EnterRowAnim166WithCry(BattlePlayerEntity* arg0) {
    s32 idx = arg0->moveAnimIndex;
    s32 temp_a0;
    s32 sp34;
    PokemonData* sp30;
    BattlePlayerAnimState* sp24;

    sp34 = gMoveAnimData[idx].unk_20;
    sp30 = &arg0->boundRoster->unk_01C[arg0->animationState.RentalSlotAnimData_PosePhase];
    sp24 = &arg0->animationState;
    gCurrentAnimChannel = &gAnimDataByPlayer[BattleScene_GetParticipantSideIndex(arg0)]->unk_000[sp34];
    temp_a0 = sp24->unk_34 & 2;

    if ((temp_a0 == 0) && !(sp24->unk_34 & 0x4000) && (temp_a0 == 0)) {
        if (sp30->unk_05 & 7) {
            if (BattleScene_ByteArrayContains(arg0->unk_000.unk_01A, gSpecialMoveIDs, 8) != 0) {
                gCurrentAnimChannel = &gAnimDataByPlayer[BattleScene_GetParticipantSideIndex(arg0)]->unkA90[0x60];
            } else {
                gCurrentAnimChannel = &gAnimDataByPlayer[BattleScene_GetParticipantSideIndex(arg0)]->idleAnimChannel;
            }
        } else if (sp24->unk_34 & 0x200) {
            gCurrentAnimChannel = &gAnimDataByPlayer[BattleScene_GetParticipantSideIndex(arg0)]->faintedAnimChannel;
        }

        ModelAnim_SetFrame(&arg0->unk_000, 0);
        ModelAnim_SetAnimation(&arg0->unk_000, gCurrentAnimChannel->posX);

        if (sp24->unk_34 & 0x200) {
            if (BattleScene_IsPartnerPikachu(arg0) != 0) {
                PlayMoveSoundEffect(BattleScene_GetParticipantSideIndex(arg0) & 0xFF, 0, 0xC8, 0x1A);
            } else {
                PlayMoveSoundEffect(BattleScene_GetParticipantSideIndex(arg0) & 0xFF, 0, arg0->unk_000.unk_01A, 0x1A);
            }
        } else if (BattleScene_IsPartnerPikachu(arg0) != 0) {
            PlayMoveSoundEffect(BattleScene_GetParticipantSideIndex(arg0) & 0xFF, 0, 0xC8, 0xA);
        } else {
            PlayMoveSoundEffect(BattleScene_GetParticipantSideIndex(arg0) & 0xFF, 0, arg0->unk_000.unk_01A, 0xA);
        }
    }
}

void BattleScene_TickRow1PlayOwnerCry(BattlePlayerEntity* arg0) {
    UNUSED s32 pad;
    BattlePlayerAnimState* sp18 = &arg0->animationState;
    PokemonData* ptr = &arg0->boundRoster->unk_01C[arg0->animationState.RentalSlotAnimData_PosePhase];

    if ((sp18->unk_34 & 0x4000) || (sp18->unk_34 & 2) || (ptr->unk_05 & 7)) {
        gBattleSceneStateTickSlots[gAnimStateQueueIndex].rotation = gAnimStateIdle;
    } else if (arg0->animationStateIndex == 1) {
        if (BattleAnim_IsAssetLoadBusy(arg0) == 0) {
            if (arg0->unk_000.unk_01A >= 0x98) {
                BattleAnim_PlayOwnerCry(arg0, sp18->unk_BC);
            } else {
                BattleAnim_PlayOwnerCry(arg0, arg0->unk_000.unk_01A);
            }
            gBattleSceneStateTickSlots[gAnimStateQueueIndex].rotation = gAnimStateIdle;
        }
    }
}

void BattleScene_TickRow16PlayCryAndSpeciesSound(BattlePlayerEntity* arg0) {
    UNUSED s32 pad;
    PokemonData* ptr = &arg0->boundRoster->unk_01C[arg0->animationState.RentalSlotAnimData_PosePhase];
    BattlePlayerAnimState* sp24 = &arg0->animationState;

    if ((arg0->animationState.unk_34 & 0x4000) || (sp24->unk_34 & 2) || (ptr->unk_05 & 7)) {
        gBattleSceneStateTickSlots[gAnimStateQueueIndex].rotation = gAnimStateIdle;
    } else if ((arg0->animationStateIndex == 1) && (BattleAnim_IsAssetLoadBusy(arg0) == 0)) {
        if (arg0->unk_000.unk_01A >= 0x98) {
            Cry_Play(sp24->unk_BC, 3);
        } else if (BattleScene_IsPartnerPikachu(arg0) != 0) {
            Cry_Play(0xC8, 3);
        } else {
            Cry_Play(arg0->unk_000.unk_01A, 3);
        }

        if (sp24->unk_34 & 0x200) {
            if (BattleScene_IsPartnerPikachu(arg0) != 0) {
                PlayMoveSoundEffect(BattleScene_GetParticipantSideIndex(arg0) & 0xFF, 0, 0xC8, 0x1B);
            } else {
                PlayMoveSoundEffect(BattleScene_GetParticipantSideIndex(arg0) & 0xFF, 0, arg0->unk_000.unk_01A, 0x1B);
            }
        } else if (BattleScene_IsPartnerPikachu(arg0) != 0) {
            PlayMoveSoundEffect(BattleScene_GetParticipantSideIndex(arg0) & 0xFF, 0, 0xC8, 0xB);
        } else {
            PlayMoveSoundEffect(BattleScene_GetParticipantSideIndex(arg0) & 0xFF, 0, arg0->unk_000.unk_01A, 0xB);
        }
        gBattleSceneStateTickSlots[gAnimStateQueueIndex].rotation = gAnimStateIdle;
    }
}

void BattleScene_TickRow18PlayCryAndSpeciesSound(BattlePlayerEntity* arg0) {
    UNUSED s32 pad;
    PokemonData* ptr = &arg0->boundRoster->unk_01C[arg0->animationState.RentalSlotAnimData_PosePhase];
    BattlePlayerAnimState* sp24;

    if ((arg0->animationState.unk_34 & 0x4000) || (ptr->unk_05 & 0x20) || (ptr->unk_05 & 7)) {
        gBattleSceneStateTickSlots[gAnimStateQueueIndex].rotation = gAnimStateIdle;
        return;
    }

    if ((arg0->animationStateIndex == 1) && (BattleAnim_IsAssetLoadBusy(arg0) == 0)) {
        sp24 = &arg0->animationState;
        if (arg0->unk_000.unk_01A >= 0x98) {
            Cry_Play(sp24->unk_BC, 4);
        } else if (BattleScene_IsPartnerPikachu(arg0) != 0) {
            Cry_Play(0xC8, 4);
        } else {
            Cry_Play(arg0->unk_000.unk_01A, 4);
        }

        if (sp24->unk_34 & 0x200) {
            if (BattleScene_IsPartnerPikachu(arg0) != 0) {
                PlayMoveSoundEffect(BattleScene_GetParticipantSideIndex(arg0) & 0xFF, 0, 0xC8, 0x1B);
            } else {
                PlayMoveSoundEffect(BattleScene_GetParticipantSideIndex(arg0) & 0xFF, 0, arg0->unk_000.unk_01A, 0x1B);
            }
        } else if (BattleScene_IsPartnerPikachu(arg0) != 0) {
            PlayMoveSoundEffect(BattleScene_GetParticipantSideIndex(arg0) & 0xFF, 0, 0xC8, 0xB);
        } else {
            PlayMoveSoundEffect(BattleScene_GetParticipantSideIndex(arg0) & 0xFF, 0, arg0->unk_000.unk_01A, 0xB);
        }

        gBattleSceneStateTickSlots[gAnimStateQueueIndex].rotation = gAnimStateIdle;
    }
}

void BattleScene_TickAssetLoadQueueRowEffectList3(BattlePlayerEntity* arg0) {
    UNUSED s32 pad[2];
    s32 sp24 = arg0->moveAnimIndex;
    BattlePlayerAnimState* temp_v1 = &arg0->animationState;

    if (BattleAnim_TryRegisterAssetTables(arg0) != 0) {
        arg0->pokemonAnimation->posY = arg0->animationState.unk_38.unk_0B;
        arg0->animationStateIndex = 0;
        BattleScene_QueueRowEffectList3(arg0, gMoveAnimData[sp24].unk_24);
        Audio_PlayCommand(3, 0, 0);
        arg0->pokemonAnimation->rotation = &arg0->pokemonAnimation->RentalSlotAnimData_PosePhase[temp_v1->unk_2B]->unk_01C[temp_v1->unk_18];
        gBattleSceneStateTickSlots[gAnimStateQueueIndex].rotation = gAnimStateIdle;
    }
}

void Pokemon_HandleMoveHitSimple(BattlePlayerEntity* arg0) {
    BattleScene_GetParticipantSideIndex(arg0);
    if ((arg0->animationStateIndex == 1) && (BattleAnim_IsAssetLoadBusy(arg0) == 0)) {
        s32 idx = arg0->moveAnimIndex;

        BattleScene_QueueRowEffectList3(arg0, gMoveAnimData[idx].unk_24);
        Audio_PlayCommand(3, 0, 0);
        gBattleSceneStateTickSlots[gAnimStateQueueIndex].rotation = gAnimStateIdle;
    }
}

void BattleScene_TickRow20CleanupAndEnterState18(BattlePlayerEntity* arg0) {
    if (arg0->animationStateIndex == 0x4F) {
        arg0->pokemonAnimation->posX |= 0x80;
    }

    if (arg0->pokemonAnimation->posX & 0x10) {
        arg0->pokemonAnimation->posX &= ~0x90;

        Battle_LoadOwnerModelForSwitchIn(arg0);
        BattleScene_TickOwnerCameraFraming(arg0);
        Audio_PlayCommand(2, 0, 0);

        gBattleSceneStateTickSlots[gAnimStateQueueIndex].rotation = gAnimStateIdle;

        BattleScene_EnterStateRow(arg0, 0x12);
    }
}

void Pokemon_ClearTransformFlag(BattlePlayerEntity* arg0) {
    if (arg0->pokemonAnimation->posX & 0x10) {
        arg0->pokemonAnimation->posX &= ~0x90;
        Battle_ResetOwnerModelToNeutralPlaceholder(arg0);
    }
}

void BattleScene_EnterRow8StartMappedMoveAnim(BattlePlayerEntity* arg0) {
    UNUSED s32 pad[2];
    s32 sp24 = gAnimLookupTable[arg0->animationState.unk_38.currentMoveId - 1];

    gCurrentAnimChannel = &gAnimDataByPlayer[BattleScene_GetParticipantSideIndex(arg0)]->unk_000[sp24];
    arg0->animationStateIndex = 0;
    ModelAnim_SetFrame(&arg0->unk_000, 0);
    ModelAnim_SetAnimation(&arg0->unk_000, gCurrentAnimChannel->posX);
    BattleAnim_SetModelEventTrackFromRow(arg0, sp24);
}

void BattleScene_TickRow8PlayMoveEffectScriptB(BattlePlayerEntity* arg0) {
    PokemonAudioInfo* temp_s1_2;
    s16 sp22;
    s16 temp_s1;

    sp22 = arg0->unk_000.unk_01A - 1;
    temp_s1_2 = &arg0->animationState.unk_38;
    temp_s1 = gAnimLookupTable[temp_s1_2->currentMoveId - 1];

    BattleScene_GetParticipantSideIndex(arg0);

    gCurrentAnimChannel = &gAnimDataByPlayer[BattleScene_GetParticipantSideIndex(arg0)]->unk_000[temp_s1];

    if ((arg0->animationStateIndex == (gCurrentAnimChannel->rotation + 1)) && (BattleAnim_IsAssetLoadBusy(arg0) == 0)) {
        BattleAnim_PlayMoveEffectScriptB(arg0, temp_s1_2->currentMoveId);

        if (temp_s1_2->currentMoveId == 0x13) {
            BattleScene_SetParticipantModelFlags(arg0, 3, 0);
        }

        if ((temp_s1_2->currentMoveId == 0x5B) && (sp22 != 0x31) && (sp22 != 0x32)) {
            BattleScene_SetParticipantModelFlags(arg0, 5, 0);
            BattleAnim_QueueEffectList(4, arg0);
        }

        gBattleSceneStateTickSlots[gAnimStateQueueIndex].rotation = gAnimStateIdle;

        BattleAnim_PlaySpeciesReactionSound(arg0, temp_s1_2, 4);
    }
}

void BattleScene_EnterRow9SetEventTrack(BattlePlayerEntity* arg0) {
    UNUSED s32 pad[3];
    PokemonData* ptr = &arg0->boundRoster->unk_01C[arg0->animationState.RentalSlotAnimData_PosePhase];
    s32 sp1C;

    arg0->animationStateIndex = 0;
    if (!(arg0->animationState.unk_34 & 2)) {
        if (ptr->unk_05 & 7) {
            if (BattleScene_ByteArrayContains(arg0->unk_000.unk_01A, gSpecialMoveIDs, 8) != 0) {
                sp1C = 0xAF;
            } else {
                sp1C = 0xA5;
            }
        } else {
            sp1C = 0xA5;
        }
        gCurrentAnimChannel = &gAnimDataByPlayer[BattleScene_GetParticipantSideIndex(arg0)]->unk_000[sp1C];
        BattleAnim_SetModelEventTrackFromRow(arg0, sp1C);
    }
}

void BattleScene_EnterRow9QueueEffectList6(BattlePlayerEntity* arg0) {
    PokemonAudioInfo* ptr = &sActivePokemon[BattleScene_GetParticipantSideIndex(arg0) == 0]->animationState.unk_38;

    if (ptr->unk_4C & 0x20) {
        if ((ptr->currentMoveId == 0x14) || (ptr->currentMoveId == 0x23) || (ptr->currentMoveId == 0x51)) {
            BattleAnim_QueueEffectList6(2, arg0);
            BattleScene_SetParticipantModelFlags(arg0, 0x10, 0);
        }
    }
}

void BattleScene_Row12Slot1CameraCleanup(BattlePlayerEntity* arg0) {
    PokemonAudioInfo* sp20;
    s32 sp28;

    sp28 = BattleScene_GetParticipantSideIndex(arg0) == 0;
    sp20 = &arg0->animationState.unk_38;
    gCurrentAnimChannel = &gAnimDataByPlayer[BattleScene_GetParticipantSideIndex(arg0) == 0]->unk_000[sp20->currentMoveId - 1];

    if ((gCurrentAnimChannel->unk_07 + 1) == sActivePokemon[sp28]->animationStateIndex) {
        if (BattleAnim_IsAssetLoadBusy(arg0) == 0) {
            BattleAnim_PlaySpeciesReactionSound(arg0, sp20, 5);
            gBattleSceneStateTickSlots[gAnimStateQueueIndex].rotation = gAnimStateIdle;
        }
    }
}

void BattleScene_Row13PlaySequences14And21(BattlePlayerEntity* arg0) {
    PokemonAudioInfo* sp20 = &arg0->animationState.unk_38;

    if (sp20->unk_15 & 8) {
        BattleAnim_PlayBattleSequenceById(arg0, 0x14);
    }

    if (sp20->unk_15 & 0x10) {
        BattleAnim_PlayBattleSequenceById(arg0, 0x21);
    }

    gBattleSceneStateTickSlots[gAnimStateQueueIndex].rotation = gAnimStateIdle;
}

void BattleScene_TickPlaySpeciesSequence33(BattlePlayerEntity* arg0) {
    UNUSED s32 pad;
    u16 sp22 = arg0->unk_000.unk_01A;

    gCurrentAnimChannel = &gAnimDataByPlayer[BattleScene_GetParticipantSideIndex(arg0)]->sendOutAnimChannel;
    if ((BattleScene_GetParticipantModelHeight(arg0) != 0.0f) && (sp22 != 0x16) && (sp22 != 0x52) && (sp22 != 0x8E)) {
        gBattleSceneStateTickSlots[gAnimStateQueueIndex].rotation = gAnimStateIdle;
    } else if ((arg0->animationStateIndex == (gCurrentAnimChannel->rotation + 1)) && (BattleAnim_IsAssetLoadBusy(arg0) == 0)) {
        BattleAnim_PlaySpeciesSequence33(arg0);
        gBattleSceneStateTickSlots[gAnimStateQueueIndex].rotation = gAnimStateIdle;
    }
}

void BattleScene_TickQueueList3Selector2OrC(BattlePlayerEntity* arg0) {
    s32 sp24;

    gCurrentAnimChannel = &gAnimDataByPlayer[BattleScene_GetParticipantSideIndex(arg0)]->sendOutAnimChannel;
    if (gCurrentAnimChannel->unk_09 == 1) {
        sp24 = gCurrentAnimChannel->unk_0A - 0x4C;
    } else {
        sp24 = gCurrentAnimChannel->unk_0A - 0x31;
    }

    if (BattleAnim_IsAssetLoadBusy(arg0) == 0) {
        if (BattleScene_GetParticipantModelHeight(arg0) != 0.0f) {
            if ((sp24 <= 0) || (sp24 == arg0->animationStateIndex)) {
                if (gCurrentAnimChannel->unk_09 == 1) {
                    BattleAnim_QueueEffectList3(2, arg0, arg0, 0xFF, 0xFF);
                } else {
                    BattleAnim_QueueEffectList3(0xC, arg0, arg0, 0xFF, 0xFF);
                }
                Audio_PlayCommand(3, 0, 0);
                gBattleSceneStateTickSlots[gAnimStateQueueIndex].rotation = gAnimStateIdle;
            }
        } else if ((sp24 <= 0) || (sp24 == arg0->animationStateIndex)) {
            if (gCurrentAnimChannel->unk_09 == 1) {
                BattleAnim_QueueEffectList3(2, arg0, arg0, 0xFF, 0xFF);
            } else {
                BattleAnim_QueueEffectList3(0xC, arg0, arg0, 0xFF, 0xFF);
            }
            Audio_PlayCommand(3, 0, 0);
            gBattleSceneStateTickSlots[gAnimStateQueueIndex].rotation = gAnimStateIdle;
        }
    }
}

void BattleScene_TickQueueList3Selector2OrCFromB10(BattlePlayerEntity* arg0) {
    s32 sp24;

    gCurrentAnimChannel = &gAnimDataByPlayer[BattleScene_GetParticipantSideIndex(arg0)]->followupSendOutAnimChannel;
    if (gCurrentAnimChannel->unk_09 == 1) {
        sp24 = gCurrentAnimChannel->unk_0A - 0x4C;
    } else {
        sp24 = gCurrentAnimChannel->unk_0A - 0x31;
    }

    if ((BattleAnim_IsAssetLoadBusy(arg0) == 0) && ((sp24 <= 0) || (sp24 == arg0->animationStateIndex))) {
        if (gCurrentAnimChannel->unk_09 == 1) {
            BattleAnim_QueueEffectList3(2, arg0, arg0, 0xFF, 0xFF);
        } else {
            BattleAnim_QueueEffectList3(0xC, arg0, arg0, 0xFF, 0xFF);
        }
        Audio_PlayCommand(3, 0, 0);
        gBattleSceneStateTickSlots[gAnimStateQueueIndex].rotation = gAnimStateIdle;
    }
}

void UpdateAnimChannelForEntity(BattlePlayerEntity* arg0) {
    UNUSED s32 pad;
    s32 sp48;
    UNUSED s32 pad2;
    s32 sp40;
    BattlePlayerAnimState* sp3C;
    UNUSED s32 pad3[2];
    BattlePlayerEntity* sp30;
    PokemonAudioInfo* sp28;

    sp48 = 0xA5;
    sp40 = BattleScene_GetParticipantSideIndex(arg0) == 0;
    sp3C = &sActivePokemon[sp40]->animationState;
    sp30 = sActivePokemon[sp40];
    sp28 = &arg0->animationState.unk_38;

    gCurrentAnimChannel = &gAnimDataByPlayer[sp40]->statusAnimChannel;

    if (sp3C->unk_34 & 1) {
        if (BattleScene_ByteArrayContains(sp30->unk_000.unk_01A, gSpecialConditionIDs, 2) != 0) {
            gCurrentAnimChannel = &gAnimDataByPlayer[sp40]->unk_B20;
        }
    }

    if ((sp3C->unk_34 & 1) && BattleScene_ByteArrayContains(sp30->unk_000.unk_01A, gSpecialMoveIDs, 8)) {
        sp48 = 0xAF;
    }

    sActivePokemon[sp40]->animationStateIndex = 0;

    if (!(sp3C->unk_34 & 0x4000) && !(sp3C->unk_34 & 2)) {
        if ((sp28->currentMoveId == 0x91) && (gAnimTimer < 0xA)) {
            gCurrentAnimChannel = &gAnimDataByPlayer[sp40]->unk_000[sp48];
        }

        if ((gIsBattleMode == 0) || (gBattleMoveFailed != 0)) {
            // FAKE? keeps &gCurrentAnimChannel out of a register while the load stays a CSE temp
            if (gAnimDataByPlayer[sp40]) {}
            gCurrentAnimChannel = &gAnimDataByPlayer[sp40]->unk_000[sp48];
            if (sp3C->unk_34 & 0x200) {
                gCurrentAnimChannel = &gAnimDataByPlayer[sp40]->unk_000[0xB0];
            }
        } else if (!(sp3C->unk_34 & 1)) {
            BattleAnim_SetModelEventTrackFromRow(sActivePokemon[sp40], 0xA8);
        }

        ModelAnim_SetFrame(&sActivePokemon[sp40]->unk_000, 0);
        ModelAnim_SetAnimation(&sActivePokemon[sp40]->unk_000, gCurrentAnimChannel->posX);

        if ((sp28->unk_44.posX == 0x17) || (sp28->unk_44.posX == 0x22) || (sp28->unk_44.posX == 0x45)) {
            BattleScene_SetParticipantModelFlags(sActivePokemon[sp40], 0xF, 0);
        }
    }
}

void BattleScene_TickRow14PlayMoveEffectEnd(BattlePlayerEntity* arg0) {
    s32 sp2C;
    UNUSED s32 pad;
    PokemonAudioInfo* sp24;
    PokemonAudioInfo* sp1C;

    sp2C = BattleScene_GetParticipantSideIndex(arg0);
    sp24 = &sActivePokemon[sp2C == 0]->animationState.unk_38;
    sp1C = &arg0->animationState.unk_38;

    gCurrentAnimChannel = &gAnimDataByPlayer[sp2C == 0]->unk_000[sp1C->currentMoveId - 1];

    if ((sActivePokemon[sp2C == 0]->animationStateIndex == (gCurrentAnimChannel->unk_07 + 1)) && (BattleAnim_IsAssetLoadBusy(arg0) == 0)) {
        BattleAnim_CleanupEffects(1);
        if (((sp1C->currentMoveId == 0x30) || (sp1C->currentMoveId == 0x6D)) && (sp24->unk_4C & 0x80) && (gBattleMoveFailed == 0) &&
            (gIsBattleMode == 1)) {
            BattleAnim_PlayBattleSequenceById(sActivePokemon[sp2C == 0], 0x12);
        }

        BattleAnim_PlayMoveEffectEnd(sActivePokemon[sp2C == 0], sp1C->currentMoveId);
        if ((gBattleMoveFailed == 0) || (gIsBattleMode == 1)) {
            BattleAnim_PlaySpeciesReactionSound(sActivePokemon[sp2C == 0], &arg0->animationState.unk_38, 1);
        }

        gBattleSceneStateTickSlots[gAnimStateQueueIndex].rotation = gAnimStateIdle;
    }
}

s32 GetAnimStateResultCode(BattlePlayerEntity* arg0) {
    PokemonAudioInfo* ptr = &arg0->animationState.unk_38;
    s32 temp_v1;

    temp_v1 = BattleScene_GetParticipantSideIndex(arg0) == 0;
    gCurrentAnimChannel = &gAnimDataByPlayer[temp_v1]->unk_000[ptr->currentMoveId - 1];

    if (gAnimStateFlag != 1) {
        return 2;
    }

    if ((gCurrentAnimChannel->RentalSlotAnimData_PosePhase + 0x50) == sActivePokemon[temp_v1]->animationStateIndex) {
        return 1;
    }

    return 0;
}

void BattleScene_TickRow11QueueEffectList6(BattlePlayerEntity* arg0) {
    PokemonAudioInfo* ptr = &arg0->animationState.unk_38;
    s32 sp28;

    sp28 = BattleScene_GetParticipantSideIndex(arg0) == 0;
    gCurrentAnimChannel = &gAnimDataByPlayer[BattleScene_GetParticipantSideIndex(arg0) == 0]->unk_000[ptr->currentMoveId - 1];
    if (sActivePokemon[sp28]->animationStateIndex == (gCurrentAnimChannel->RentalSlotAnimData_PosePhase + 1)) {
        if (BattleAnim_IsAssetLoadBusy(arg0) == 0) {
            if (gAnimStateFlag == 1) {
                BattleAnim_QueueEffectList6(1, sActivePokemon[sp28]);
                BattleAnim_PlayBattleSequenceById(arg0, 0x20);
            }
            gBattleSceneStateTickSlots[gAnimStateQueueIndex].rotation = gAnimStateIdle;
        }
    }
}

void BattleScene_TickRow11PostEndCamera(BattlePlayerEntity* arg0) {
    PokemonAudioInfo* sp20;
    s32 sp28;

    sp28 = BattleScene_GetParticipantSideIndex(arg0) == 0;
    sp20 = &arg0->animationState.unk_38;
    gCurrentAnimChannel = &gAnimDataByPlayer[BattleScene_GetParticipantSideIndex(arg0) == 0]->unk_000[sp20->currentMoveId - 1];

    if ((gCurrentAnimChannel->unk_07 + 1) == sActivePokemon[sp28]->animationStateIndex) {
        if (BattleAnim_IsAssetLoadBusy(arg0) == 0) {
            if (gIsBattleMode == 1) {
                BattleAnim_PlaySpeciesReactionSound(sActivePokemon[sp28], sp20, 1);
            } else {
                BattleAnim_PlaySpeciesReactionSound(sActivePokemon[sp28], sp20, 5);
            }
            gBattleSceneStateTickSlots[gAnimStateQueueIndex].rotation = gAnimStateIdle;
        }
    }
}

void BattleScene_StateCallbackNop(BattlePlayerEntity* arg0) {
}

void BattleScene_RegisterStateTickCallback(BattlePlayerEntity* arg0, unk_D_84385384_func arg1) {
    unk_D_84390068* var_a2;
    s32 i;

    for (i = 0; i < 7; i++) {
        if (gAnimStateIdle == gBattleSceneStateTickSlots[i].rotation) {
            gBattleSceneStateTickSlots[i].rotation = arg1;
            gBattleSceneStateTickSlots[i].posX = arg0;
            break;
        }
    }
}

void BattleScene_SetOpponentEventTrackA6(BattlePlayerEntity* arg0) {
    BattleAnim_SetModelEventTrackFromRow(sActivePokemon[BattleScene_GetParticipantSideIndex(arg0)], 0xA6);
}

void BattleScene_EnterStateRow(BattlePlayerEntity* arg0, s32 arg1) {
    arg0->moveAnimIndex = arg1;

    gMoveAnimData[arg1].rotation[0](arg0);
    gMoveAnimData[arg1].rotation[1](arg0);
    gMoveAnimData[arg1].rotation[2](arg0);

    BattleScene_RegisterStateTickCallback(arg0, gMoveAnimData[arg1].rotation[3]);
    BattleScene_RegisterStateTickCallback(arg0, gMoveAnimData[arg1].rotation[4]);
    BattleScene_RegisterStateTickCallback(arg0, gMoveAnimData[arg1].rotation[5]);
    BattleScene_RegisterStateTickCallback(arg0, gMoveAnimData[arg1].rotation[6]);
}

void BattleScene_TickStateCallbacks(void) {
    sActivePokemon[0]->animationStateIndex++;
    sActivePokemon[1]->animationStateIndex++;

    for (gAnimStateQueueIndex = 0; gAnimStateQueueIndex < 7; gAnimStateQueueIndex++) {
        gBattleSceneStateTickSlots[gAnimStateQueueIndex].rotation(gBattleSceneStateTickSlots[gAnimStateQueueIndex].posX);
    }
}

void Battle_ResetCryEventIfStruggle(BattlePlayerEntity* arg0) {
    if (arg0->animationState.unk_38.currentMoveId == 0x6A) {
        arg0->unk_000.unk_01C = 0;
    }
}

void BattleAnim_SetModelEventTrackFromRow(BattlePlayerEntity* arg0, s32 arg1) {
    s32 temp_v0;
    s32 sp30;
    BattlePlayerAnimState* sp24 = &arg0->animationState;

    if (BattleAnim_IsSessionBusy(arg0) == 0) {
        sp30 = gAnimDataByPlayer[BattleScene_GetParticipantSideIndex(arg0)]->unk_000[arg1].TrainerSlotSaveData_GamePort;
        if ((sp30 != 0xFF) && (sp24->unk_36 != 2)) {
            if ((arg1 == 165) && (arg0->unk_000.unk_01A == 0x33)) {
                ModelAnim_SetEventFrame(&arg0->unk_000, 0);
                temp_v0 = BattleAnim_RandomRange(3);
                if (temp_v0 >= 3) {
                    temp_v0 = 2;
                }
                ModelAnim_SetEventTrack(&arg0->unk_000, sp30 + temp_v0);
            } else {
                ModelAnim_SetEventFrame(&arg0->unk_000, 0);
                ModelAnim_SetEventTrack(&arg0->unk_000, sp30);
                sp24->unk_36 = 1;
            }
        }
    }
}

s32 BattleAnim_TrySetModelEventTrackFromRow(BattlePlayerEntity* arg0, s32 arg1, s32 arg2) {
    UNUSED s32 pad;
    s32 sp20;

    if (BattleAnim_IsSessionBusy(arg0) != 0) {
        return 0;
    }

    sp20 = gAnimDataByPlayer[BattleScene_GetParticipantSideIndex(arg0)]->unk_000[arg1].TrainerSlotSaveData_GamePort;
    if (sp20 == 0xFF) {
        return 1;
    }

    ModelAnim_SetEventFrame(&arg0->unk_000, 0);
    ModelAnim_SetEventTrack(&arg0->unk_000, sp20);
    ModelAnim_SetEventFrame(&arg0->unk_000, arg0->unk_000.unk_054.rotation->unk_0A);

    arg0->animationState.unk_36 = arg2;
    return 0;
}

void BattleAnim_SetModelEventTrackAndState(BattlePlayerEntity* arg0, s32 arg1, s32 arg2) {
    u8 temp_a1;

    if (BattleAnim_IsSessionBusy(arg0) == 0) {
        temp_a1 = gAnimDataByPlayer[BattleScene_GetParticipantSideIndex(arg0)]->unk_000[arg1].TrainerSlotSaveData_GamePort;
        if (temp_a1 != 0xFF) {
            ModelAnim_SetEventTrack(&arg0->unk_000, temp_a1);
            ModelAnim_SetEventFrame(&arg0->unk_000, 0);
            arg0->animationState.unk_36 = arg2;
        }
    }
}

s32 BattleScene_IsParticipantIncapacitated(BattlePlayerEntity* arg0) {
    BattlePlayerAnimState* sp20 = &arg0->animationState;
    PokemonData* ptr = &arg0->boundRoster->unk_01C[arg0->animationState.RentalSlotAnimData_PosePhase];

    if ((sp20->unk_34 & 2) || (ptr->unk_05 & 7) || ((sp20->unk_34 & 0x200) && !(sp20->unk_34 & 0x400)) ||
        (sp20->unk_34 & 0x4000)) {
        return 1;
    }
    return 0;
}

s32 BattleScene_IsRowWaitComplete(BattlePlayerEntity* arg0, s32 arg1) {
    if (BattleScene_IsParticipantIncapacitated(arg0) != 0) {
        if (BattleScene_AdvanceCameraFrameCounter(arg1) != 0) {
            return 1;
        }
        return 0;
    }

    if (arg0->unk_000.unk_040.posX == -1) {
        return 1;
    }
    return ModelAnim_IsAnimationDone(&arg0->unk_000);
}

s32 BattleScene_IsRowWaitCompleteWithEventCount(BattlePlayerEntity* arg0, s32 arg1) {
    u8 temp_v0;

    gCurrentAnimChannel = gAnimDataByPlayer[BattleScene_GetParticipantSideIndex(arg0)]->unkA60;
    if (BattleScene_IsParticipantIncapacitated(arg0) != 0) {
        if (BattleScene_AdvanceCameraFrameCounter(arg1) != 0) {
            return 1;
        }
        return 0;
    }

    if ((gCurrentAnimChannel->unk_0A < 0xB) || (gCurrentAnimChannel->unk_0A == 0xFF)) {
        if (arg0->unk_000.unk_040.posX == -1) {
            return 1;
        }
        return ModelAnim_IsAnimationDone(&arg0->unk_000);
    }

    if (BattleScene_AdvanceCameraFrameCounter(gCurrentAnimChannel->unk_0A + 1) != 0) {
        return 1;
    }

    return 0;
}

s32 Battle_IsRowAnimationSettled(BattlePlayerEntity* arg0, s32 arg1) {
    PokemonAudioInfo* ptr = &arg0->animationState.unk_38;
    BattleAnimDataEntry* sp20;
    BattleAnimDataEntry* sp1C;

    if (arg0) {}

    sp20 = &gAnimDataByPlayer[BattleScene_GetParticipantSideIndex(arg0)]->unk_000[ptr->currentMoveId - 1];
    sp1C = &gAnimDataByPlayer[BattleScene_GetParticipantSideIndex(arg0)]->idleAnimChannel;

    if (BattleScene_IsParticipantIncapacitated(arg0) != 0) {
        if (BattleScene_AdvanceCameraFrameCounter(arg1) != 0) {
            return 1;
        }
        return 0;
    }

    if (arg0->unk_000.unk_040.posX == -1) {
        return 1;
    }

    if (gBattleScene.posX->unk_48 == 0x14) {
        sp20 = &gAnimDataByPlayer[BattleScene_GetParticipantSideIndex(arg0)]->unk_000[0];
    }

    if (sp20->posX == sp1C->posX) {
        if (sp20->unk_0A != 0xFF) {
            gBattleScene.posX->unk_14++;
            if (sp20->unk_0A == arg0->animationStateIndex) {
                return 1;
            }
            return 0;
        }

        if (BattleScene_AdvanceCameraFrameCounter(arg1) != 0) {
            return 1;
        }
        return 0;
    }

    gBattleScene.posX->unk_14++;

    if (sp20->unk_0A != 0xFF) {
        if (sp20->unk_0A == arg0->animationStateIndex) {
            return 1;
        }
        return 0;
    }

    return ModelAnim_IsAnimationDone(&arg0->unk_000);
}

s32 BattleScene_IsMoveKeyedRowWaitComplete(BattlePlayerEntity* arg0, s32 arg1) {
    BattleAnimDataEntry* temp_a2;
    PokemonData* sp28;
    UNUSED s32 pad;
    s32 sp20;
    BattleAnimDataEntry* sp1C;

    sp28 = &arg0->boundRoster->unk_01C[arg0->animationState.RentalSlotAnimData_PosePhase];
    sp20 = gAnimLookupTable[arg0->animationState.unk_38.currentMoveId - 1];
    sp1C = &gAnimDataByPlayer[BattleScene_GetParticipantSideIndex(arg0)]->unk_000[sp20];
    temp_a2 = &gAnimDataByPlayer[BattleScene_GetParticipantSideIndex(arg0)]->idleAnimChannel;

    if ((arg0->animationState.unk_34 & 2) || (sp28->unk_05 & 7) ||
        ((arg0->animationState.unk_34 & 0x200) && !(arg0->animationState.unk_34 & 0x400)) || (arg0->animationState.unk_34 & 0x4000)) {
        if (BattleScene_AdvanceCameraFrameCounter(arg1) != 0) {
            return 1;
        }
        return 0;
    }

    if (arg0->unk_000.unk_040.posX == -1) {
        return 1;
    }

    if (sp1C->posX == temp_a2->posX) {
        if (sp1C->unk_0A != 0xFF) {
            gBattleScene.posX->unk_14++;
            if (sp1C->unk_0A == arg0->animationStateIndex) {
                return 1;
            }
            return 0;
        }
        if (BattleScene_AdvanceCameraFrameCounter(arg1) != 0) {
            return 1;
        }
        return 0;
    }

    gBattleScene.posX->unk_14++;

    if (sp1C->unk_0A != 0xFF) {
        if (sp1C->unk_0A == arg0->animationStateIndex) {
            return 1;
        }
        return 0;
    }
    return ModelAnim_IsAnimationDone(&arg0->unk_000);
}

s32 BattleScene_IsRowAnimWaitComplete(BattlePlayerEntity* arg0, s32 arg1) {
    gCurrentAnimChannel = &gAnimDataByPlayer[BattleScene_GetParticipantSideIndex(arg0)]->statusAnimChannel;

    if ((arg0->animationState.unk_34 & 2) || ((arg0->animationState.unk_34 & 0x200) && !(arg0->animationState.unk_34 & 0x400))) {
        if (BattleScene_AdvanceCameraFrameCounter(arg1) != 0) {
            return 1;
        }
        return 0;
    }

    if (arg0->unk_000.unk_040.posX == -1) {
        return 1;
    }

    if (arg0->unk_000.unk_040.posX != gCurrentAnimChannel->posX) {
        return 1;
    }

    return ModelAnim_IsAnimationDone(&arg0->unk_000);
}

void MaybeTriggerSpecialAnimEffect(BattlePlayerEntity* arg0) {
    gCurrentAnimChannel = &gAnimDataByPlayer[BattleScene_GetParticipantSideIndex(arg0)]->idleAnimChannel;
    if (BattleAnim_IsSessionBusy(arg0) == 0) {
        if ((arg0->unk_000.unk_040.posX != -1) && (arg0->unk_000.unk_000.TrainerSlotSaveData_GamePort & 1) &&
            (arg0->unk_000.unk_000.posY & 0x20) && (gBattleScene.posX->unk_1C == 1) &&
            (gCurrentAnimChannel->posX == arg0->unk_000.unk_040.posX) &&
            (gCurrentAnimChannel->rotation == (arg0->unk_000.unk_040.RentalSlotAnimData_PosePhase >> 0x10)) && (gCurrentAnimChannel->unk_05 != 0) &&
            (BattleAnim_RandomRange(2) == 1)) {
            BattleAnim_QueueEffectList3(gCurrentAnimChannel->unk_05, &arg0->unk_000, &arg0->unk_000, gCurrentAnimChannel->posY, gCurrentAnimChannel->posY);
        }
    }
}

void Battle_SetRuntimeFlags(BattlePlayerEntity* arg0, u16 arg1) {
    arg0->animationState.unk_34 |= arg1;
}

s32 Battle_ClearRuntimeFlags(BattlePlayerEntity* arg0, u16 arg1) {
    arg0->animationState.unk_34 &= ~arg1;
}

void BattleScene_ResetParticipantAnimationFlags(BattlePlayerEntity* arg0) {
    BattlePlayerAnimState* sp24 = &arg0->animationState;

    if (arg0->unk_4C8 != 0) {
        if (sp24->unk_34 & 0x200) {
            arg0->unk_000.unk_024.y = gPokemonModelDimensions[BattleScene_GetParticipantSideIndex(arg0)].RentalSlotAnimData_PosePhase;
            Battle_ClearRuntimeFlags(arg0, 0x608);
        }

        if (sp24->unk_34 & 0x4008) {
            arg0->unk_000.unk_01D = 0xFF;
            BattleAnim_StopOwnerCategoryParticles(4, arg0);
            arg0->unk_000.unk_024.y = gPokemonModelDimensions[BattleScene_GetParticipantSideIndex(arg0)].RentalSlotAnimData_PosePhase;
            arg0->unk_000.unk_000.posY &= ~2;
            arg0->unk_000.unk_000.posY |= 0x20;
            arg0->unk_000.unk_000.TrainerSlotSaveData_GamePort |= 1;
            Battle_ClearRuntimeFlags(arg0, 0x4608);
        }
    }
}

void BattleScene_ResetBothParticipantsAnimationState(void) {
    BattlePlayerAnimState* sp34;
    BattlePlayerAnimState* sp30;
    UNUSED s32 pad[2];
    BattlePlayerEntity* sp24;
    BattlePlayerEntity* sp20;

    sp34 = &sActivePokemon[0]->animationState;
    sp30 = &sActivePokemon[1]->animationState;
    sp24 = sActivePokemon[0];
    sp20 = sActivePokemon[1];

    if (sp34->unk_34 & 4) {
        sActivePokemon[0]->unk_000.unk_024.y = 200.0f;
        Battle_SetRuntimeFlags(sActivePokemon[0], 0x200);
        Battle_ClearRuntimeFlags(sActivePokemon[0], 4);
    }

    if (sp30->unk_34 & 4) {
        sActivePokemon[1]->unk_000.unk_024.y = 200.0f;
        Battle_SetRuntimeFlags(sActivePokemon[1], 0x200);
        Battle_ClearRuntimeFlags(sActivePokemon[1], 4);
    }

    if ((sp34->unk_34 & 0x4000) && (sp24->unk_000.unk_01A == 0x33)) {
        gCurrentAnimChannel = &gAnimDataByPlayer[0]->unk_000[0x5A];
        ModelAnim_SetFrame(&sActivePokemon[0]->unk_000, 0);
        ModelAnim_SetAnimation(&sActivePokemon[0]->unk_000, gCurrentAnimChannel->posX);
    }

    if ((sp30->unk_34 & 0x4000) && (sp20->unk_000.unk_01A == 0x33)) {
        gCurrentAnimChannel = &gAnimDataByPlayer[1]->unk_000[0x5A];
        ModelAnim_SetFrame(&sActivePokemon[1]->unk_000, 0);
        ModelAnim_SetAnimation(&sActivePokemon[1]->unk_000, gCurrentAnimChannel->posX);
    }

    BattleScene_ResetParticipantAnimationFlags(sActivePokemon[0]);
    BattleScene_ResetParticipantAnimationFlags(sActivePokemon[1]);
}

void Battle_ClearOpponentHopFlagAndSyncMove(BattlePlayerEntity* arg0) {
    UNUSED s32 pad;
    BattlePlayerAnimState* sp20;

    sp20 = &sActivePokemon[BattleScene_GetParticipantSideIndex(arg0) == 0]->animationState;
    BattleScene_GetParticipantSideIndex(arg0);
    BattleScene_GetParticipantSideIndex(arg0);
    Battle_ResetCryEventIfStruggle(sActivePokemon[BattleScene_GetParticipantSideIndex(arg0) == 0]);

    if (sp20->unk_34 & 4) {
        sActivePokemon[BattleScene_GetParticipantSideIndex(arg0) == 0]->unk_000.unk_024.y = 200.0f;
        Battle_SetRuntimeFlags(sActivePokemon[BattleScene_GetParticipantSideIndex(arg0) == 0], 0x200);
        Battle_ClearRuntimeFlags(sActivePokemon[BattleScene_GetParticipantSideIndex(arg0) == 0], 4);
    }

    if (arg0->animationState.unk_34 & 0x200) {
        Battle_SetRuntimeFlags(arg0, 0x400);
    }
}

void BattleScene_CleanupParticipantHideFlag(BattlePlayerEntity* arg0) {
    if (arg0->animationState.unk_34 & 8) {
        arg0->unk_000.unk_024.y = BattleScene_GetParticipantModelHeight(arg0);
        Battle_ClearRuntimeFlags(arg0, 0x608);
    }
}

void BattleScene_CleanupOpponentSpecialAnimFlag(BattlePlayerEntity* arg0) {
    UNUSED s32 pad[2];
    BattlePlayerEntity* sp1C = sActivePokemon[BattleScene_GetParticipantSideIndex(arg0) == 0];

    if (sp1C->animationState.unk_34 & 0x4000) {
        sp1C->unk_000.unk_000.posY |= 0x20;
        sp1C->unk_000.unk_000.TrainerSlotSaveData_GamePort |= 1;
        BattleAnim_StopOwnerCategoryParticles(4, sp1C);
        Battle_ClearRuntimeFlags(sp1C, 0x4000);
    }
}

void BattleScene_CleanupOpponentAnimationFlags(BattlePlayerEntity* arg0) {
    BattlePlayerEntity* temp_s0 = sActivePokemon[BattleScene_GetParticipantSideIndex(arg0) == 0];
    BattlePlayerAnimState* ptr = &temp_s0->animationState;

    if (ptr->unk_34 & 0x4000) {
        temp_s0->unk_000.unk_000.posY |= 0x20;
        temp_s0->unk_000.unk_000.TrainerSlotSaveData_GamePort |= 1;
        BattleAnim_StopOwnerCategoryParticles(4, temp_s0);
        Battle_ClearRuntimeFlags(temp_s0, 0x4000);
    }

    if (ptr->unk_34 & 8) {
        temp_s0->unk_000.unk_024.y = BattleScene_GetParticipantModelHeight(arg0);
        Battle_ClearRuntimeFlags(temp_s0, 0x608);
    }
}

void BattleScene_CleanupParticipantEffectMode(BattlePlayerEntity* arg0) {
    switch (arg0->animationMode) {
        case 14:
            BattleScene_SetParticipantModelFlags(arg0, 0, 0);
            BattleScene_PositionParticipantModel(arg0);
            break;

        case 13:
        case 15:
        case 16:
            BattleScene_SetParticipantModelFlags(arg0, 0, 0);
            if (arg0->animationState.unk_38.unk_56 == 0) {
                Vec3f_SetComponentsDuplicate(&arg0->unk_000.unk_030, 1.0f, 1.0f, 1.0f);
            } else {
                Vec3f_SetComponentsDuplicate(&arg0->unk_000.unk_030, 0.8f, 0.8f, 0.8f);
            }
            break;

        case 12:
            BattleScene_SetParticipantModelFlags(arg0, 0, 0);
            if (arg0->animationState.unk_38.unk_56 == 0) {
                Vec3f_SetComponentsDuplicate(&arg0->unk_000.unk_030, 1.0f, 1.0f, 1.0f);
            } else {
                Vec3f_SetComponentsDuplicate(&arg0->unk_000.unk_030, 0.8f, 0.8f, 0.8f);
            }
            break;

        case 10:
            BattleScene_SetParticipantModelFlags(arg0, 0, 0);
            arg0->unk_000.unk_024.y = BattleScene_GetParticipantModelHeight(arg0);
            arg0->unk_000.unk_01E.x = 0;
            break;

        case 9:
            BattleScene_SetParticipantModelFlags(arg0, 0, 0);
            Vec3f_SetComponentsDuplicate(&arg0->unk_000.unk_030, 0.8f, 0.8f, 0.8f);
            BattleScene_HideParticipantSecondaryModels(arg0);
            break;

        case 7:
            BattleScene_SetParticipantModelFlags(arg0, 0, 0);
            BattleScene_HideParticipantSecondaryModels(arg0);
            break;

        case 6:
            BattleScene_SetParticipantModelFlags(arg0, 0, 0);
            BattleScene_HideParticipantSecondaryModels(arg0);
            BattleScene_PositionParticipantModel(arg0);
            Vec3s_SetComponents(&arg0->unk_000.unk_01E, 0, arg0->sideSign << 0xE, 0);
            break;

        case 4:
            BattleScene_SetParticipantModelFlags(arg0, 0, 0);
            arg0->unk_000.unk_01E.y = arg0->sideSign << 0xE;
            BattleScene_HideParticipantSecondaryModels(arg0);
            break;
    }
}

void BattleAnim_TickParticipantStatusAnimation(BattlePlayerEntity* arg0) {
    BattlePlayerAnimState* temp_s1 = &arg0->animationState;

    BattleAnim_StartFreezeStatusAnimation(arg0);
    BattleAnim_UpdateSleepStatusAnimation(arg0);

    if (temp_s1->unk_34 & 0x100) {
        arg0->unk_000.unk_000.posY &= 0xFFDF;
    }

    if ((temp_s1->unk_2D == 0x10) || (temp_s1->unk_2D == 0x13)) {
        Battle_ClearRuntimeFlags(arg0, 0x100);
    }

    temp_s1->unk_2E = Math_StepToS32(temp_s1->unk_2E, 0, 0x1E, 0x1E);
    if (temp_s1->unk_2E != 0) {
        Model_SetMaterialColor(&arg0->unk_000, 0xFF, 0xFF, 0xFF, temp_s1->unk_2E);
    }

    switch (temp_s1->unk_36) {
        case 2:
            break;

        case 0:
            if (BattleAnim_RandomRange(0x32) == 2) {
                BattleAnim_SetModelEventTrackFromRow(arg0, 0xA5);
            }
            break;

        case 1:
            if (ModelAnim_IsEventTrackNearEnd(&arg0->unk_000) == 1) {
                ModelAnim_SetEventTrack(&arg0->unk_000, -1);
                ModelAnim_SetEventFrame(&arg0->unk_000, 0);
                temp_s1->unk_36 = 0;
            }
            break;
    }

    if (temp_s1->unk_34 & 0x4000) {
        if ((arg0->unk_000.unk_01A != 0x32) && (arg0->unk_000.unk_01A != 0x33)) {
            arg0->unk_000.unk_01D = 0;
        }
    }
}

void BattleAnim_TriggerStatusAfflictionCry(BattlePlayerEntity* arg0) {
    PokemonData* ptr = &arg0->boundRoster->unk_01C[arg0->animationState.RentalSlotAnimData_PosePhase];

    if ((ptr->unk_05 & 7) && !(arg0->animationState.unk_34 & 1)) {
        BattleAnim_SetModelEventTrackAndState(arg0, 0xAF, 2);
        BattleAnim_QueueEffectList(3, arg0);
        BattleAnim_PlayBattleSequenceById(arg0, 0x32);
    }
}

void BattleScene_AllocateParticipantRecord(BattlePokemon* arg0, s32 arg1) {
    BattlePlayerEntity* ptr = main_pool_alloc(sizeof(BattlePlayerEntity), 0);

    sActivePokemon[arg1] = ptr;

    bzero(ptr, sizeof(BattlePlayerEntity));
    bzero(&sActivePokemon[arg1]->animationState, sizeof(BattlePlayerAnimState));
    bzero(&sActivePokemon[arg1]->animationState.unk_38, sizeof(PokemonAudioInfo));
    bzero(&sActivePokemon[arg1]->ownerModel, sizeof(unk_D_84390010_728));
    bzero(&sActivePokemon[arg1]->animationState.unk_38.unk_44, sizeof(unk_D_800FCB18_044));
    bzero(&sActivePokemon[arg1]->animationState.unk_9C, sizeof(unk_D_84390010_654_09C));
    bzero(&sActivePokemon[arg1]->animationState.unk_AC, sizeof(unk_D_84390010_654_0AC));
    bzero(&sActivePokemon[arg1]->messageBuffer, sizeof(unk_D_84390010_8C4));
    sActivePokemon[arg1]->pokemonAnimation = arg0;
}

void BattleScene_AllocateParticipants(BattlePokemon* arg0) {
    BattleScene_AllocateParticipantRecord(&arg0[0], 0);
    BattleScene_AllocateParticipantRecord(&arg0[1], 1);
    Battle_InitMessageQueues();
    gPrimaryPokemonEntity = sActivePokemon[0];
    gPokemonEntityUnused = sActivePokemon[1];
}

void BattleScene_InitializeParticipantController(BattlePlayerEntity* arg0) {
    Controller* sp24 = &gControllers[arg0->pokemonAnimation->RentalSlotAnimData_PosePhase[0]->unk_001];

    BattleScene_BindParticipantRosterForSide(arg0, 0);
    BattleScene_SetParticipantSelectedSide(arg0, 0);
    BattleScene_SetParticipantController(arg0, sp24);
    arg0->ownerModel.unk_16C = 0;
}

void BattleScene_InitializeParticipantModel(BattlePlayerEntity* arg0) {
    UNUSED s32 pad[2];
    ModelRootNode* sp24;
    s16 sp22;

    BattleScene_GetParticipantSideIndex(arg0);
    sp24 = Battle_GetMoveEffectListEntry(arg0, 0);
    sp22 = Battle_GetTrainerId(arg0, 0);
    ModelRenderer_AttachDisplayObject(&arg0->unk_000);

    if (arg0 == sActivePokemon[0]) {
        arg0->unk_000.modelPhase = 0;
    } else {
        arg0->unk_000.modelPhase = 1;
    }

    Model_InitDisplayObject(&arg0->unk_000, 0, sp22, sp24);
    LoadPlayerAnimationData(arg0, 1);
    ModelAnim_SetAnimation(&arg0->unk_000, 0);
    ModelAnim_SetFrame(&arg0->unk_000, 0);

    arg0->pokemonAnimation->rotation = arg0->boundRoster->unk_01C;
    if ((arg0->unk_000.unk_01A == 0x32) || (arg0->unk_000.unk_01A == 0x33)) {
        arg0->unk_000.unk_000.posY &= ~0x40;
    } else {
        arg0->unk_000.unk_000.posY |= 0x40;
    }

    if (arg0 == sActivePokemon[0]) {
        BattleScene_PositionParticipantModel(arg0);
        arg0->unk_000.unk_01E.y = 0x4000;
    } else {
        BattleScene_PositionParticipantModel(arg0);
        arg0->unk_000.unk_01E.y = -0x4000;
    }
}

void BattleScene_InitializeParticipantOwnerModel(BattlePlayerEntity* arg0) {
    unk_D_84390010_728* ptr = &arg0->ownerModel;
    ModelRootNode* sp28;
    s16 sp26;

    sp28 = Battle_GetMoveEffectListEntry(arg0, 0);
    sp26 = Battle_GetTrainerId(arg0, 0);
    ModelRenderer_AttachDisplayObject(&ptr->unk_000);

    if (arg0 == sActivePokemon[0]) {
        ptr->unk_000.modelPhase = -1;
        Model_InitDisplayObject(&ptr->unk_000, 1, sp26, sp28);
    } else {
        ptr->unk_000.modelPhase = -1;
        Model_InitDisplayObject(&ptr->unk_000, 2, sp26, sp28);
    }

    ModelAnim_SetAnimation(&ptr->unk_000, 0);
    ModelAnim_SetFrame(&ptr->unk_000, 0);
    ptr->unk_000.unk_000.posY &= ~0x40;
    Vec3f_SetComponentsDuplicate(&ptr->unk_000.unk_024, 0.0f, 0.0f, 0.0f);
}

void BattleScene_InitializeParticipantSecondaryModels(BattlePlayerEntity* arg0, s32* arg1) {
    ModelRootNode* sp44;
    s16 sp42;
    s32 i;
    unk_D_84390010_168* ptr;

    sp44 = Battle_GetMoveEffectListEntry(arg0, 0);
    sp42 = Battle_GetTrainerId(arg0, 0);

    for (i = 0; i < 2; i++) {
        ptr = &arg0->unk_168[i];

        ModelRenderer_AttachDisplayObject(ptr);

        if (arg0 == sActivePokemon[0]) {
            ptr->unk_000.modelPhase = 0xFF;
        } else {
            ptr->unk_000.modelPhase = 0xFF;
        }

        Model_InitDisplayObject(ptr, 0, sp42, sp44);
        ModelAnim_SetFrame(ptr, 0);
        ModelAnim_SetAnimation(ptr, 0);

        ptr->unk_000.unk_000.posY &= ~0x40;

        if (arg0 == sActivePokemon[0]) {
            BattleScene_PositionParticipantModel(arg0);
        } else {
            BattleScene_PositionParticipantModel(arg0);
        }
        ptr->unk_000.unk_000.TrainerSlotSaveData_GamePort &= ~1;
    }
}

void BattleScene_InitializeParticipantAuxiliaryModel(BattlePlayerEntity* arg0) {
    Fragment2_1GraphNode* ptr = &arg0->effectGraphNode;
    ModelRootNode* sp20 = arg0->pokemonAnimation->unk_18;

    ModelRenderer_AttachDisplayObject(ptr);
    ptr->modelPhase = 0xFF;
    Model_InitDisplayObject(ptr, 0, 0x9A, sp20);
    ModelAnim_SetAnimation(ptr, 0);

    ptr->unk_000.posY &= ~0x20;
    ptr->unk_000.TrainerSlotSaveData_GamePort &= ~1;

    if (arg0 == sActivePokemon[0]) {
        Vec3f_SetComponentsDuplicate(&ptr->unk_024, -50.0f, 2.0f, 0.0f);
    } else {
        Vec3f_SetComponentsDuplicate(&ptr->unk_024, 50.0f, 2.0f, 0.0f);
    }
}

void BattleScene_InitializePresentation(BattlePokemon* arg0) {
    gBattleInitFlag = 0;
    gBattleInitStruct.posX = 0;

    BattleScene_InitializeParticipantController(sActivePokemon[0]);
    BattleScene_InitializeParticipantController(sActivePokemon[1]);
    BattleScene_InitializeParticipantModel(sActivePokemon[0]);
    BattleScene_InitializeParticipantModel(sActivePokemon[1]);
    BattleScene_InitializeParticipantOwnerModel(sActivePokemon[0]);
    BattleScene_InitializeParticipantOwnerModel(sActivePokemon[1]);
    BattleScene_InitializeParticipantSecondaryModels(sActivePokemon[0], &sActivePokemon[0]->unk_168);
    BattleScene_InitializeParticipantSecondaryModels(sActivePokemon[1], &sActivePokemon[1]->unk_168);
    BattleScene_InitializeParticipantAuxiliaryModel(sActivePokemon[0]);
    BattleScene_InitializeParticipantAuxiliaryModel(sActivePokemon[1]);

    switch (gSessionContext.unk_0000) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
            BattleScene_SetCameraModeAndStep(4, 0);
            break;

        case 16:
            BattleScene_SetCameraModeAndStep(1, 0x32);
            Audio_StartMusicTrack(1);
            break;

        default:
            BattleScene_SetCameraModeAndStep(4, 0);
            break;
    }

    BattleScene_SetParticipantModelFlags(sActivePokemon[0], 0, 0);
    BattleScene_SetParticipantModelFlags(sActivePokemon[1], 0, 0);
    BattleScene_ResetMessageQueue();
    BattleScene_ClearParticipantMessageBuffer(sActivePokemon[0]);
    BattleScene_ClearParticipantMessageBuffer(sActivePokemon[1]);
    BattleScene_ConfigureAudioChannelGroupCounts();
    BattleScene_ConfigureAudioChannelGroupsByTeam();
}

void BattleScene_ResetParticipantAuxTransform(BattlePlayerEntity* arg0, BattlePlayerEntity* arg1, s32 arg2) {
    Vec3f_SetComponentsDuplicate(&arg1->unk_448, 0.0f, 0.0f, 0.0f);
    Vec3f_SetComponentsDuplicate(&arg1->unk_448.unk_0C, 0.0f, 0.0f, 0.0f);
    arg1->sideSign = arg2;
}

void BattleScene_InitializeRuntime(BattlePokemon* arg0) {
    s32 i;

    Text_InitStringTables();

    gMessageBank_0x1E = Text_GetStringTable(0x1E);
    gMessageBank_0x24 = Text_GetStringTable(0x24);
    gPokemonMessageBank = Text_GetStringTable(0x25);
    gMessageBank_0x29 = Text_GetStringTable(0x29);
    gMarqueeMessageBank = Text_GetStringTable(0x14);

    for (i = 0; i < 7; i++) {
        gBattleSceneStateTickSlots[i].rotation = gAnimStateIdle;
    }

    BattleScene_ResetParticipantAuxTransform(sActivePokemon[0], sActivePokemon[0], 1);
    BattleScene_ResetParticipantAuxTransform(sActivePokemon[1], sActivePokemon[1], -1);
    BattleScene_InitializePresentation(arg0);
    Battle_InitializeActiveRuntimeState();
    Battle_InitializeMoveUsabilityMask(sActivePokemon[0]);
    Battle_InitializeMoveUsabilityMask(sActivePokemon[1]);
    BattleBox_Close();
}

void BattleScene_UpdateParticipantsAndQueueEffects(BattlePlayerEntity* arg0, BattlePlayerEntity* arg1) {
    Battle_AdvanceSecondaryModelAnimIfFinished(sActivePokemon[0], sActivePokemon[0]);
    Battle_AdvanceSecondaryModelAnimIfFinished(sActivePokemon[1], sActivePokemon[1]);
    BattleAnim_UpdateOwnerStatusIdleAnimation(0);
    BattleAnim_UpdateOwnerStatusIdleAnimation(1);
    MaybeTriggerSpecialAnimEffect(sActivePokemon[0]);
    MaybeTriggerSpecialAnimEffect(sActivePokemon[1]);
}

s32 BattleScene_DispatchLifecycle(s32 arg0, BattlePokemon* arg1) {
    switch (arg0) {
        case 0:
            BattleScene_AllocateParticipants(arg1);
            break;

        case 1:
        case 2:
            BattleScene_UpdateParticipantsAndQueueEffects(sActivePokemon[0], sActivePokemon[1]);
            break;

        case 3:
            BattleScene_InitializeRuntime(arg1);
            break;

        case 5:
            Battle_RenderHud();
            break;
    }

    return 0;
}

void AnimHandler_Idle(BattlePlayerEntity* arg0) {
}

void BattleScene_StateRow56EnterNop(BattlePlayerEntity* arg0) {
}

void BattleScene_StateRow5Slot3Nop(BattlePlayerEntity* arg0) {
}

void BattleScene_StateRow5Slot4Nop(BattlePlayerEntity* arg0) {
}

void BattleScene_StateRow5Slot5Nop(BattlePlayerEntity* arg0) {
}

void BattleScene_StateRow5Slot6Nop(BattlePlayerEntity* arg0) {
}

void BattleScene_StateRow7Slot5Nop(BattlePlayerEntity* arg0) {
}

void BattleScene_StateRow6Slot6Nop(BattlePlayerEntity* arg0) {
}

void BattleScene_StateRow6Slot5Nop(BattlePlayerEntity* arg0) {
}

void BattleScene_StateRow6Slot4Nop(BattlePlayerEntity* arg0) {
}

void BattleScene_StateRow6Slot3Nop(BattlePlayerEntity* arg0) {
}

void AnimHandler_SwitchIn(BattlePlayerEntity* arg0) {
}

void AnimHandler_SwitchOut(BattlePlayerEntity* arg0, s32 arg1) {
}

void AnimHandler_Victory(BattlePlayerEntity* arg0, s32 arg1) {
}

void BattleScene_StateRow7Slot4Nop(BattlePlayerEntity* arg0) {
}
