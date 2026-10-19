#include "fragment62.h"
#include "src/17300.h"
#include "src/18140.h"
#include "src/1C720.h"
#include "src/232C0.h"
#include "src/2E110.h"
#include "src/2E460.h"
#include "src/373A0.h"
#include "src/3FB0.h"
#include "src/485C0.h"
#include "src/48C60.h"
#include "src/4BDC0.h"
#include "src/4F410.h"
#include "src/F420.h"
#include "src/memory.h"

static unk_D_8438E7B0 gAnimDataPlayer0;
static unk_D_8438E7B0 gAnimDataPlayer1;
static unk_D_8438FF70 gAnimDataSetB0;
static unk_D_8438FF70 gAnimDataSetB1;
static unk_D_8438FF70 gAnimDataSetC0;
static unk_D_8438FF70 gAnimDataSetC1;
static unk_D_84384588 gAnimExtraDataPlayer0;
static unk_D_84384588 gAnimExtraDataPlayer1;
unk_BattlePlayerEntity* sActivePokemon[2];
unk_BattlePlayerEntity* gPrimaryPokemonEntity;
unk_BattlePlayerEntity* gPokemonEntityUnused;
static unk_BattleAnimDataEntry* gCurrentAnimChannel;
unk_D_84390028 gPokemonModelDimensions[2];
static unk_D_84390048 gAnimTempVector;
static unk_D_84390068 gAnimStateQueue[7];
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

void AnimStateQueue_ResetAll(void) {
    s32 i;

    for (i = 0; i < 7; i++) {
        gAnimStateQueue[i].unk_04 = gAnimStateIdle;
    }
}

void Anim_TriggerActionScriptMode3(unk_BattlePlayerEntity* arg0, s32 arg1) {
    InitActionScriptMode3(arg1, &arg0->unk_000, &arg0->unk_000, 0xFF, 0xFF);
}

void AnimChannel_StartMoveAction(unk_BattlePlayerEntity* arg0, s32 arg1) {
    UNUSED s16 pad;
    s16 sp24;
    s32 sp20;

    sp20 = IsPrimaryEntity(arg0) == 0;
    sp24 = Anim_GetActionScriptId(arg0);
    InitActionScriptSimple(arg1, arg0, sActivePokemon[sp20], sp24, Anim_GetActionScriptParam(arg0));
}

void AnimChannel_StartSpecialMoveAction(unk_BattlePlayerEntity* arg0, s32 arg1) {
    UNUSED s16 pad;
    s16 sp24;
    s32 sp20;

    sp20 = IsPrimaryEntity(arg0) == 0;
    sp24 = Anim_GetActionScriptId(arg0);
    InitActionScriptMode1(arg1, arg0, sActivePokemon[sp20], sp24, Anim_GetActionScriptParam(arg0));
}

void AnimChannel_StartAnotherMoveAction(unk_BattlePlayerEntity* arg0, s32 arg1) {
    UNUSED s16 pad;
    s16 sp24;
    s32 sp20;

    sp20 = IsPrimaryEntity(arg0) == 0;
    sp24 = GetOpponentAnimScriptId(arg0);
    InitDualTargetActionScript(arg1, sActivePokemon[sp20], arg0, sp24, GetOpponentAnimScriptParam(arg0));
}

void AnimChannel_ResetIfNeeded(unk_BattlePlayerEntity* arg0) {
    if (AnimChannel_CheckAndReset(arg0) != 0) {
        arg0->unk_4C4 = 0;
        gAnimStateQueue[gAnimStateQueueIndex].unk_04 = gAnimStateIdle;
    }
}

void AnimChannel_SetupAndTrigger(unk_BattlePlayerEntity* arg0) {
    UNUSED s32 pad;
    s32 idx = arg0->unk_4C0;
    s32 sp24 = gMoveAnimData[idx].unk_20;

    gCurrentAnimChannel = &gAnimDataByPlayer[IsPrimaryEntity(arg0)]->unk_000[sp24];
    if (AnimChannel_CheckAndReset(arg0) != 0) {
        PlayAnimSoundSimple(arg0, sp24, 2);
        arg0->unk_4C4 = 0;
        gAnimStateQueue[gAnimStateQueueIndex].unk_04 = gAnimStateIdle;
        Anim_SetChannelBase(&arg0->unk_000, 0);
        GraphNode_TriggerAction(&arg0->unk_000, gCurrentAnimChannel->unk_00);
    }
}

void AnimChannel_CheckModelBaseY(unk_BattlePlayerEntity* arg0) {
    s32 idx = arg0->unk_4C0;
    s32 sp28 = gMoveAnimData[idx].unk_20;

    gCurrentAnimChannel = &gAnimDataByPlayer[IsPrimaryEntity(arg0)]->unk_000[sp28];
    if (GetModelBaseY(arg0) != 0.0f) {
        gAnimStateQueue[gAnimStateQueueIndex].unk_04 = gAnimStateIdle;
    } else if ((arg0->unk_4C4 == (gCurrentAnimChannel->unk_04 + 1)) && (AnimChannel_GetFlagsFB0(arg0) == 0)) {
        Anim_TriggerActionScriptMode3(arg0, gMoveAnimData[idx].unk_24);
        gAnimStateQueue[gAnimStateQueueIndex].unk_04 = gAnimStateIdle;
    }
}

void Anim_ResetPlayer(unk_BattlePlayerEntity* arg0) {
    arg0->unk_4C4 = 0;
}

void Anim_ResetAllPlayers(unk_BattlePlayerEntity* arg0) {
    sActivePokemon[IsPrimaryEntity(arg0) == 0]->unk_4C4 = 0;
}

void Anim_SetEntityVisualFlags(unk_BattlePlayerEntity* arg0) {
    unk_D_800FCB18* ptr = &arg0->unk_654.unk_38;

    if (ptr->unk_5A == 0x46 || ptr->unk_5A == 0x9D || ptr->unk_5A == 0x58) {
        sActivePokemon[0]->unk_000.unk_000.unk_02 |= 2;
        sActivePokemon[1]->unk_000.unk_000.unk_02 |= 2;
    }
}

void Anim_ClearEntityVisualFlags(unk_BattlePlayerEntity* arg0) {
    sActivePokemon[0]->unk_000.unk_000.unk_02 &= ~2;
    sActivePokemon[1]->unk_000.unk_000.unk_02 &= ~2;
}

s32 AnimChannel_GetFlagsFB0(unk_BattlePlayerEntity* arg0) {
    return arg0->unk_720->unk_1D & 0xD0;
}

s32 AnimChannel_FinishAndGetFlagsFC0(unk_BattlePlayerEntity* arg0) {
    FinishPokemonAnimation(arg0->unk_720);
    return arg0->unk_720->unk_1D & 0xC0;
}

s32 AnimChannel_GetFlagsFF0(unk_BattlePlayerEntity* arg0) {
    return arg0->unk_720->unk_00 & 0xD0;
}

s32 AnimChannel_CheckAndReset(unk_BattlePlayerEntity* arg0) {
    if (AnimChannel_FinishAndGetFlagsFC0(arg0) == 0) {
        ResetWaterEffect(arg0->unk_720);
        return 1;
    }
    return 0;
}

void AnimChannel_HandleBattleState(unk_BattlePlayerEntity* arg0) {
    if (gBattleState.unk_00->unk_48 == 0xE) {
        SetMessageFromId(arg0->unk_720, GetCurrentMoveId(arg0));
    } else {
        SetMessageFromId(arg0->unk_720, GetCurrentMoveId(arg0));
    }
}

void AnimChannel_TriggerMoveEffect(unk_BattlePlayerEntity* arg0) {
    s32 idx = arg0->unk_4C0;

    SetMessageFromAltTable(arg0->unk_720, gMoveAnimData[idx].unk_24);
}

void AnimChannel_TriggerGenericEffect(unk_BattlePlayerEntity* arg0) {
    SetMessageFromId(arg0->unk_720, GetCurrentMoveId(arg0));
}

void AnimChannel_SetFlags28(unk_BattlePlayerEntity* arg0) {
    arg0->unk_720->unk_02 = 0x98;
    arg0->unk_720->unk_00 |= 0x80;
}

void AnimChannel_SetTransformData(unk_BattlePlayerEntity* arg0) {
    arg0->unk_720->unk_04 = &arg0->unk_724->unk_01C[arg0->unk_654.unk_08];
    arg0->unk_720->unk_00 |= 0x80;
    arg0->unk_720->unk_02 = arg0->unk_654.unk_BC;
}

s32 FindIndexInArray(u16 arg0, u8* arg1, s32 arg2) {
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

void ApplyStatMasksAndConditions(unk_BattlePlayerEntity* arg0, u16 arg1, unk_D_84390010_94C* arg2, unk_D_84390010_94C* arg3) {
    s32 i;
    s32 j;
    s32 temp_v0_3;
    s32 temp_v1_2;
    u8 var_a0;
    SpeciesStats* temp_s4; //TODO: this is definitely typed wrong
    unk_D_800FCB18* temp_s5;

    temp_s5 = &arg0->unk_654.unk_38;

    for (i = 0; i < 4; i++) {
        if (temp_s5->unk_1F[i] != 0) {
            temp_s4 = &gSpeciesBaseStats[arg1];

            for (j = 0; j < ARRAY_COUNT(temp_s4->unk_0A); j++) {
                if ((temp_s4->unk_0A[j] != 0) && (temp_s4->unk_0A[j] == temp_s5->unk_1F[i])) {
                    arg0->unk_654.unk_C1[i] = 0;
                }
            }

            for (j = 0; j < 10; j++) {
                if ((arg2->unk_00[j] != 0) && (temp_s5->unk_26 >= arg2->unk_00[j]) &&
                    (arg2->unk_0A[j] == temp_s5->unk_1F[i])) {
                    arg0->unk_654.unk_C1[i] = 0;
                }
            }

            for (j = 0; j < 10; j++) {
                if ((arg3->unk_00[j] != 0) && (temp_s5->unk_26 >= arg3->unk_00[j]) &&
                    (arg3->unk_0A[j] == temp_s5->unk_1F[i])) {
                    arg0->unk_654.unk_C1[i] = 0;
                }
            }

            for (j = 0; j < 0x37; j++) {
                temp_v0_3 = FindIndexInArray(arg1 + 1, gStatMaskIndices, 9);
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

                if (((var_a0 >> (j % 8)) & 1) && (GetPokemonType1(j) == temp_s5->unk_1F[i])) {
                    arg0->unk_654.unk_C1[i] = 0;
                }
            }
        } else {
            arg0->unk_654.unk_C1[i] = 0;
        }
    }
}

void ResetAllStatFlags(unk_BattlePlayerEntity* arg0) {
    arg0->unk_654.unk_C1[0] = 1;
    arg0->unk_654.unk_C1[1] = 1;
    arg0->unk_654.unk_C1[2] = 1;
    arg0->unk_654.unk_C1[3] = 1;

    ApplyStatMasksAndConditions(arg0, arg0->unk_654.unk_38.unk_0B - 1, &arg0->unk_94C, &arg0->unk_9AC);

    if (gAnimExtraDataByPlayer[IsPrimaryEntity(arg0)]->unk_00 != 0) {
        ApplyStatMasksAndConditions(arg0, gAnimExtraDataByPlayer[IsPrimaryEntity(arg0)]->unk_00 - 1, &arg0->unk_96C, &arg0->unk_9CC);
    }

    if (gAnimExtraDataByPlayer[IsPrimaryEntity(arg0)]->unk_01 != 0) {
        ApplyStatMasksAndConditions(arg0, gAnimExtraDataByPlayer[IsPrimaryEntity(arg0)]->unk_01 - 1, &arg0->unk_98C, &arg0->unk_9EC);
    }
}

void DMATransfer_MoveData(u8 arg0, u32 arg1) {
    u32 temp_a1 = (u32)_70D3A0_ROM_START + ((u32)&D_72780[arg0 - 1] & 0xFFFFFF);

    DmaCopyAsyncRange(arg1, temp_a1, temp_a1 + 0x20, 0);
}

void DMATransfer_MoveDataPair(s32 arg0, unk_D_84390010_94C* arg1, unk_D_84390010_94C* arg2) {
    UNUSED s32 pad[3];
    u32 temp_a1;

    temp_a1 = (u32)_70D3A0_ROM_START + ((u32)&D_72780[arg0] & 0xFFFFFF);
    DmaCopyAsyncRange(arg1, temp_a1, temp_a1 + 0x20, 0);
    temp_a1 = (u32)_70D3A0_ROM_START + ((u32)&D_73A60[arg0] & 0xFFFFFF);
    DmaCopyAsyncRange(arg2, temp_a1, temp_a1 + 0x20, 0);
}

void LoadPlayerAnimationData(unk_BattlePlayerEntity* arg0, s32 arg1) {
    s16 sp6E;
    s32 sp68;
    s16 sp66;
    u32 var_a1;
    s32 pad[8];
    PokemonData* ptr;
    unk_D_8438FF70* ptr2;
    u32 tmp;

    sp68 = IsPrimaryEntity(arg0);
    sp66 = arg0->unk_000.unk_01A - 1;

    ptr = &arg0->unk_720->unk_08[arg0->unk_654.unk_2C]->unk_01C[arg0->unk_654.unk_18];
    // Fake: dead early copy of the D_6E910 address pair so its two spill temps are created
    // before sp68 * 4 (IDO orders compiler-temp slots by first appearance in the source).
    var_a1 = (u32)_70D3A0_ROM_START + ((u32)(D_6E910 + (sp66 << 5)) & 0xFFFFFF);
    tmp = var_a1 + 0x20;

    var_a1 = (u32)_70D3A0_ROM_START + ((u32)gStageRomOffsets[sp66] & 0xFFFFFF);
    if ((arg0->unk_000.unk_01A == 0x19) && (ptr->unk_52 & 0x80)) {
        var_a1 = (u32)_70D3A0_ROM_START + ((u32)gStageRomOffsets[152] & 0xFFFFFF);
    }
    DmaCopyAsyncRange(gAnimDataByPlayer[sp68], var_a1, var_a1 + 0xBC0, 0);

    var_a1 = (u32)_70D3A0_ROM_START + ((u32)(D_6E910 + (sp66 << 5)) & 0xFFFFFF);
    DmaCopyAsyncRange(gAnimDataSetC[sp68], var_a1, var_a1 + 0x20, 0);

    if (sp68 == 1) {
        var_a1 = (u32)_70D3A0_ROM_START + ((u32)(D_6E910 + (sp66 << 5)) & 0xFFFFFF);
        DmaCopyAsyncRange(gAnimDataSetB[sp68], var_a1, var_a1 + 0x20, 0);

        ptr2 = gAnimDataSetB[sp68];
        if (ptr2->unk_10 != 0xFF) {
            sp6E = ptr2->unk_10;

            var_a1 = ((u32)_70D3A0_ROM_START) + (((u32)(D_6E910 + ((ptr2->unk_10 - (tmp = 2)) * 0x20))) & 0xFFFFFF);
            DmaCopyAsyncRange(ptr2, var_a1, var_a1 + 0x20, 0);

            gAnimDataSetB[sp68]->unk_10 = sp6E;
        }
    } else {
        var_a1 = (u32)_70D3A0_ROM_START + ((u32)(D_6E910 + (sp66 << 5)) & 0xFFFFFF);
        DmaCopyAsyncRange(gAnimDataSetB[sp68], var_a1, var_a1 + 0x20, 0);
    }

    var_a1 = (u32)_70D3A0_ROM_START + ((u32)(D_70B10 + (sp66 * 0x20)) & 0xFFFFFF);
    DmaCopyAsyncRange(&gAnimTempVector, var_a1, var_a1 + 0x20, 0);

    Vector_Copy(&arg0->unk_448.unk_24.unk_00, &gAnimTempVector.unk_00);
    Vector_Copy(&arg0->unk_448.unk_24.unk_0C, &gAnimTempVector.unk_0C);

    arg0->unk_448.unk_24.unk_18 = gAnimTempVector.unk_18;
    arg0->unk_448.unk_24.unk_19 = gAnimTempVector.unk_19;
    arg0->unk_448.unk_24.unk_1A = gAnimTempVector.unk_1A;
    arg0->unk_448.unk_24.unk_1B = gAnimTempVector.unk_1B;
    arg0->unk_448.unk_24.unk_00.x *= arg0->unk_4B0;
    arg0->unk_448.unk_24.unk_0C.x *= arg0->unk_4B0;

    var_a1 = (u32)_70D3A0_ROM_START + ((u32)(D_70110 + (sp66 << 4)) & 0xFFFFFF);
    DmaCopyAsyncRange(&gPokemonModelDimensions[sp68], var_a1, var_a1 + 0x10, 0);

    var_a1 = (u32)_70D3A0_ROM_START + ((u32)(D_71E10 + (sp66 * 0x10)) & 0xFFFFFF);
    DmaCopyAsyncRange(gAnimExtraDataByPlayer[sp68], var_a1, var_a1 + 0x10, 0);

    DMATransfer_MoveDataPair(sp66, &arg0->unk_94C, &arg0->unk_9AC);

    if (gAnimExtraDataByPlayer[sp68]->unk_00 != 0) {
        DMATransfer_MoveDataPair(gAnimExtraDataByPlayer[sp68]->unk_00 - 1, &arg0->unk_96C, &arg0->unk_9CC);
    }

    if (gAnimExtraDataByPlayer[sp68]->unk_01 != 0) {
        DMATransfer_MoveDataPair(gAnimExtraDataByPlayer[sp68]->unk_01 - 1, &arg0->unk_98C, &arg0->unk_9EC);
    }

    if (arg1 == 1) {
        ResetAllStatFlags(arg0);
    }
}

void Pokemon_HandleFaint(unk_BattlePlayerEntity* arg0) {
    if (arg0->unk_4C4 == 0x14) {
        arg0->unk_720->unk_00 |= 0x80;
    }

    if (arg0->unk_720->unk_00 & 0x10) {
        arg0->unk_720->unk_00 &= ~0x90;
        Pokemon_ApplyFaintTransform(arg0);
        RefreshPokemonTransform(arg0);
        Audio_PlaySoundEffect(2, 0, 0);
        gAnimStateQueue[gAnimStateQueueIndex].unk_04 = gAnimStateIdle;
        ExecuteAnimStateHandlers(arg0, 0x12);
    }
}

void Pokemon_StartMoveAnimation(unk_BattlePlayerEntity* arg0) {
    unk_D_800FCB18* sp24;
    unk_BattlePlayerAnimState* sp20;
    s32 idx;
    s16 sp2A;
    u8 tmp;

    sp2A = arg0->unk_000.unk_01A - 1;
    sp24 = &arg0->unk_654.unk_38;
    sp20 = &arg0->unk_654;
    idx = IsPrimaryEntity(arg0);

    gCurrentAnimChannel = &gAnimDataByPlayer[idx]->unk_000[sp24->unk_5A - 1];

    if (!(sp20->unk_34 & 2)) {
        arg0->unk_4C4 = 0;

        if (Pokemon_IsSpecialSpecies(arg0) != 0) {
            tmp = IsPrimaryEntity(arg0);
            PlayMoveSoundEffect(tmp, sp24->unk_5A, 0xC8, 0);
        } else {
            tmp = IsPrimaryEntity(arg0);
            PlayMoveSoundEffect(tmp, sp24->unk_5A, sp2A + 1, 0);
        }

        if ((sp20->unk_34 & 0x4000) && ((sp2A == 0x32) || (sp2A == 0x31))) {
            ClearEntityAnimFlags(arg0, 8);
            arg0->unk_000.unk_000.unk_02 |= 0x20;
            SetEntityAnimFlags(arg0, 0x10);
            ClearEntityAnimFlags(arg0, 0x4000);
        }

        Anim_SetEntityVisualFlags(arg0);
        GraphNode_TriggerAction(&arg0->unk_000, gCurrentAnimChannel->unk_00);
        PlayAnimSoundIfApplicable(arg0, sp24->unk_5A - 1);

        if (gCurrentAnimChannel->unk_0B != 0) {
            Anim_SetChannelBase(&arg0->unk_000, gCurrentAnimChannel->unk_0B);
            SetAnimStateIndex(&arg0->unk_000, gCurrentAnimChannel->unk_0B);
            arg0->unk_4C4 = gCurrentAnimChannel->unk_0B;
        } else {
            Anim_SetChannelBase(&arg0->unk_000, 0);
        }
    }
}

void Pokemon_HandleMoveCompletion(unk_BattlePlayerEntity* arg0) {
    UNUSED s32 pad;
    s16 sp32 = arg0->unk_000.unk_01A - 1;
    unk_D_800FCB18* sp24;

    IsPrimaryEntity(arg0);
    sp24 = &arg0->unk_654.unk_38;
    gCurrentAnimChannel = &gAnimDataByPlayer[IsPrimaryEntity(arg0)]->unk_000[sp24->unk_5A - 1];

    if ((sp24->unk_5A == 0x19) && (sp32 == 0x64)) {
        gAnimStateQueue[gAnimStateQueueIndex].unk_04 = gAnimStateIdle;
    } else if ((arg0->unk_4C4 == (gCurrentAnimChannel->unk_04 + 1)) && (AnimChannel_GetFlagsFB0(arg0) == 0)) {
        if (gBattleState.unk_00->unk_48 == 0x14) {
            gAnimStateQueue[gAnimStateQueueIndex].unk_04 = gAnimStateIdle;
        } else if (sp24->unk_44.unk_00 == 0x5B) {
            gAnimStateQueue[gAnimStateQueueIndex].unk_04 = gAnimStateIdle;
        } else {
            if (sp24->unk_44.unk_00 == 0x6E) {
                if ((sp32 != 7) && (sp32 != 8) && (sp32 != 0x5A) && (sp32 != 6)) {
                    ApplyAnimEffectToOpponent(arg0, 0xC, 0);
                    AnimChannel_StartMoveAction(arg0, sp24->unk_5A);
                }
            } else {
                if (sp24->unk_44.unk_00 == 0x45) {
                    ApplyAnimEffectToOpponent(arg0, 8, 0);
                } else if (sp24->unk_44.unk_00 == 0x39) {
                    ApplyAnimEffectToOpponent(arg0, 0xA, 0);
                } else if (sp24->unk_44.unk_00 == 0x60) {
                    ApplyAnimEffectToOpponent(arg0, 0xD, 0);
                } else if (sp24->unk_44.unk_00 == 0x7F) {
                    ApplyAnimEffectToOpponent(arg0, 0xE, 0);
                } else if (sp24->unk_44.unk_00 == 0x6B) {
                    ApplyAnimEffectToOpponent(arg0, 9, 0);
                } else {
                    ApplyAnimEffectToOpponent(arg0, gCurrentAnimChannel->unk_05, 0);
                }

                if ((sp24->unk_5A == 0x9A) && (gCurrentMoveIndex == gTotalMoveCount)) {
                    AnimChannel_StartSpecialMoveAction(arg0, sp24->unk_5A);
                } else {
                    AnimChannel_StartMoveAction(arg0, sp24->unk_5A);
                }
            }
            gAnimStateQueue[gAnimStateQueueIndex].unk_04 = gAnimStateIdle;
        }
    }
}

void AnimChannel_CheckAndAdvance(unk_BattlePlayerEntity* arg0) {
    unk_D_800FCB18* sp24 = &arg0->unk_654.unk_38;

    gCurrentAnimChannel = &gAnimDataByPlayer[IsPrimaryEntity(arg0)]->unk_000[sp24->unk_5A - 1];

    if (arg0->unk_4C4 == (gCurrentAnimChannel->unk_04 + 1)) {
        if (AnimChannel_GetFlagsFB0(arg0) == 0) {
            if (gBattleState.unk_00->unk_48 == 0x18) {
                gInitialMoveIndex--;
                if (gInitialMoveIndex < 0) {
                    if (gSpecialFlag != 0) {
                        TriggerMoveEvent(arg0, sp24, 2);
                    }
                } else {
                    TriggerMoveEvent(arg0, sp24, 3);
                }
            } else if (gSpecialFlag != 0) {
                TriggerMoveEvent(arg0, sp24, 2);
            } else {
                if ((sp24->unk_5A == 0x2D) || (sp24->unk_5A == 0x2E) || (sp24->unk_5A == 0x59)) {
                    Anim_HandleSpecificMoveEvent(arg0);
                }
                TriggerMoveEvent(arg0, sp24, 0);
                AnimChannel_SetSubStateIfNeeded(arg0);
            }
            gAnimStateQueue[gAnimStateQueueIndex].unk_04 = gAnimStateIdle;
        }
    }
}

void AnimChannel_HandleSpecialMoves(unk_BattlePlayerEntity* arg0) {
    unk_D_800FCB18* sp24 = &arg0->unk_654.unk_38;
    UNUSED s16 pad;
    s16 sp18;

    sp18 = sp24->unk_5A;
    IsPrimaryEntity(arg0);
    gCurrentAnimChannel = &gAnimDataByPlayer[IsPrimaryEntity(arg0)]->unk_000[sp24->unk_5A - 1];

    if (arg0->unk_4C4 == (gCurrentAnimChannel->unk_09 + 1)) {
        if (AnimChannel_GetFlagsFB0(arg0) == 0) {
            if (((sp18 == 0x4A) || (sp18 == 0x60) || (sp18 == 0x61) || (sp18 == 0x6A) || (sp18 == 0x6E) ||
                 (sp18 == 0xE) || (sp18 == 0x68) || (sp18 == 0x6B) || (sp18 == 0x6F) || (sp18 == 0x70) ||
                 (sp18 == 0x85) || (sp18 == 0x97) || (sp18 == 0x9F)) &&
                (gAnimStateFlag == 1)) {
                InitSingleEntityActionScript(3, arg0);
                Audio_PlaySoundEffect(0x23, 0, 0);
            }
            gAnimStateQueue[gAnimStateQueueIndex].unk_04 = gAnimStateIdle;
        }
    }
}

void AnimChannel_SetSubStateIfNeeded(unk_BattlePlayerEntity* arg0) {
    unk_D_800FCB18* temp_v1 = &arg0->unk_654.unk_38;

    gCurrentAnimChannel = &gAnimDataByPlayer[IsPrimaryEntity(arg0)]->unk_000[temp_v1->unk_5A - 1];

    if (temp_v1->unk_5A == 0x6A) {
        GraphNode_SetSubState(&arg0->unk_000, 1);
    }
}

void Pokemon_GenericActionTrigger(unk_BattlePlayerEntity* arg0) {
    UNUSED s32 pad[2];
    unk_BattlePlayerAnimState* temp_v1 = &arg0->unk_654;
    s16 sp22;

    sp22 = arg0->unk_000.unk_01A - 1;
    gCurrentAnimChannel = gAnimDataByPlayer[IsPrimaryEntity(arg0)]->unk_000;

    if (!(temp_v1->unk_34 & 2)) {
        arg0->unk_4C4 = 0;
        if ((temp_v1->unk_34 & 0x4000) && ((sp22 == 0x32) || (sp22 == 0x31))) {
            ClearEntityAnimFlags(arg0, 8);
            arg0->unk_000.unk_000.unk_02 |= 0x20;
            SetEntityAnimFlags(arg0, 0x10);
            ClearEntityAnimFlags(arg0, 0x4000);
        }
        GraphNode_TriggerAction(&arg0->unk_000, gCurrentAnimChannel->unk_00);
        Anim_SetChannelBase(&arg0->unk_000, 0);
        PlayAnimSoundIfApplicable(arg0, 4);

        if (gCurrentAnimChannel->unk_0B != 0) {
            Anim_SetChannelBase(&arg0->unk_000, gCurrentAnimChannel->unk_0B);
            SetAnimStateIndex(&arg0->unk_000, gCurrentAnimChannel->unk_0B);
            arg0->unk_4C4 = gCurrentAnimChannel->unk_0B;
        } else {
            Anim_SetChannelBase(&arg0->unk_000, 0);
        }
    }
}

void Pokemon_PlayMoveEffect(unk_BattlePlayerEntity* arg0) {
    gCurrentAnimChannel = &gAnimDataByPlayer[IsPrimaryEntity(arg0)]->unk_000[0];
    if ((arg0->unk_4C4 == (gCurrentAnimChannel->unk_04 + 1)) && (AnimChannel_GetFlagsFB0(arg0) == 0)) {
        Effect_TriggerMoveVisual(1, arg0->unk_000.unk_01A, 0);
        gAnimStateQueue[gAnimStateQueueIndex].unk_04 = gAnimStateIdle;
    }
}

void Pokemon_TriggerAnimIfUnlocked(unk_BattlePlayerEntity* arg0) {
    unk_BattlePlayerAnimState* sp20;
    unk_D_800FCB18* ptr;

    sp20 = &arg0->unk_654;
    ptr = &arg0->unk_654.unk_38;
    gCurrentAnimChannel = &gAnimDataByPlayer[IsPrimaryEntity(arg0)]->unk_000[ptr->unk_5A - 1];

    if (sp20->unk_34 & 2) {
        return;
    }

    arg0->unk_4C4 = gCurrentAnimChannel->unk_06;
    if (!(sp20->unk_34 & 0x4000)) {
        Anim_SetEntityVisualFlags(arg0);
        GraphNode_TriggerAction(&arg0->unk_000, gCurrentAnimChannel->unk_00);
        Anim_SetChannelBase(&arg0->unk_000, gCurrentAnimChannel->unk_06);
        if (gCurrentAnimChannel->unk_01 != 0xFF) {
            GraphNode_TriggerSound(&arg0->unk_000, gCurrentAnimChannel->unk_01);
            SetAnimStateIndex(&arg0->unk_000, gCurrentAnimChannel->unk_06);
            sp20->unk_36 = 1;
        }
    }
}

void Pokemon_HandleMoveEnd(unk_BattlePlayerEntity* arg0) {
    unk_D_800FCB18* sp20;
    s32 var_v0;

    sp20 = &arg0->unk_654.unk_38;
    gCurrentAnimChannel = &gAnimDataByPlayer[IsPrimaryEntity(arg0)]->unk_000[sp20->unk_5A - 1];
    if (sp20->unk_5A == 0x9A) {
        var_v0 = gCurrentAnimChannel->unk_04 + 0x1E;
    } else {
        var_v0 = gCurrentAnimChannel->unk_04 + 1;
    }

    if ((var_v0 == arg0->unk_4C4) && (AnimChannel_GetFlagsFB0(arg0) == 0)) {
        if (gBattleState.unk_00->unk_48 == 0x14) {
            gAnimStateQueue[gAnimStateQueueIndex].unk_04 = gAnimStateIdle;
            return;
        }

        if ((sp20->unk_5A == 0x9A) && (gCurrentMoveIndex == gTotalMoveCount)) {
            AnimChannel_StartSpecialMoveAction(arg0, sp20->unk_5A);
        } else {
            AnimChannel_StartMoveAction(arg0, sp20->unk_5A);
        }

        if (sp20->unk_44.unk_00 == 0x45) {
            ApplyAnimEffectToOpponent(arg0, 8, 0);
        } else if (sp20->unk_44.unk_00 == 0x39) {
            ApplyAnimEffectToOpponent(arg0, 0xA, 0);
        } else {
            ApplyAnimEffectToOpponent(arg0, gCurrentAnimChannel->unk_05, 0);
        }
        gAnimStateQueue[gAnimStateQueueIndex].unk_04 = gAnimStateIdle;
    }
}

void Pokemon_HandleSpecialMoveEnd(unk_BattlePlayerEntity* arg0) {
    unk_D_800FCB18* sp18;
    s32 var_v0;

    sp18 = &arg0->unk_654.unk_38;
    gCurrentAnimChannel = &gAnimDataByPlayer[IsPrimaryEntity(arg0)]->unk_000[sp18->unk_5A - 1];

    if (sp18->unk_5A == 0x9A) {
        var_v0 = gCurrentAnimChannel->unk_04 + 0x1E;
    } else {
        var_v0 = gCurrentAnimChannel->unk_04 + 1;
    }

    if (var_v0 == arg0->unk_4C4) {
        if (AnimChannel_GetFlagsFB0(arg0) == 0) {
            if (gBattleState.unk_00->unk_48 == 0x18) {
                gInitialMoveIndex--;
                if (gInitialMoveIndex < 0) {
                    if (gSpecialFlag != 0) {
                        TriggerMoveEvent(arg0, sp18, 2);
                    } else {
                        TriggerMoveEvent(arg0, sp18, 0);
                    }
                } else {
                    TriggerMoveEvent(arg0, sp18, 3);
                }
            } else if (gSpecialFlag != 0) {
                TriggerMoveEvent(arg0, sp18, 2);
            } else {
                TriggerMoveEvent(arg0, sp18, 0);
            }
            gAnimStateQueue[gAnimStateQueueIndex].unk_04 = gAnimStateIdle;
        }
    }
}

void Pokemon_EnterBattleState(unk_BattlePlayerEntity* arg0) {
    UNUSED s32 pad[3];
    s32 sp40;
    unk_BattlePlayerAnimState* sp3C;
    UNUSED s32 pad2;
    s32 temp_v0;
    unk_D_800FCB18* sp28;
    unk_BattlePlayerEntity* temp_a1;

    sp28 = &arg0->unk_654.unk_38;
    sp40 = IsPrimaryEntity(arg0) == 0;
    sp3C = &sActivePokemon[sp40]->unk_654;
    temp_a1 = sActivePokemon[sp40];
    gCurrentAnimChannel = &gAnimDataByPlayer[sp40]->unk_A80;

    if (sp3C->unk_34 & 1) {
        temp_v0 = Array_ContainsValue(temp_a1->unk_000.unk_01A, gSpecialConditionIDs, 2);
        if (temp_v0 != 0) {
            gCurrentAnimChannel = &gAnimDataByPlayer[sp40]->unk_B20;
        }
    }

    sActivePokemon[sp40]->unk_4C4 = 0;

    if (!(sp3C->unk_34 & 0x200) && !(sp3C->unk_34 & 0x4000) && !(sp3C->unk_34 & 2)) {
        if (((gAnimTimer < 0xA) || (gSpecialFlag != 0)) && ((sp28->unk_15 & 0x20) == 0)) {
            gCurrentAnimChannel = &gAnimDataByPlayer[sp40]->unk_A50;
            if (sp3C->unk_34 & 0x200) {
                gCurrentAnimChannel = &gAnimDataByPlayer[sp40]->unk_B00;
            }
        } else if (!(sp3C->unk_34 & 1)) {
            PlayAnimSoundSimple(sActivePokemon[sp40], 0xA8, 1);
        }

        if ((gAnimTimer >= 0xB) && (Pokemon_IsSpecialSpecies(sActivePokemon[sp40]) != 0)) {
            Audio_PlaySequence(0xC8, 6);
        }

        if ((gAnimTimer == 0xA) && (Pokemon_IsSpecialSpecies(sActivePokemon[sp40]) != 0)) {
            Audio_PlaySequence(0xC8, 5);
        }

        if ((gSpecialFlag == 0) && (sp28->unk_5A == 0x49)) {
            gCurrentAnimChannel = &gAnimDataByPlayer[sp40]->unk_A80;
        }

        Anim_SetChannelBase(&sActivePokemon[sp40]->unk_000, 0);
        GraphNode_TriggerAction(&sActivePokemon[sp40]->unk_000, gCurrentAnimChannel->unk_00);

        if ((sp28->unk_44.unk_00 == 0x17) || (sp28->unk_44.unk_00 == 0x22) || (sp28->unk_44.unk_00 == 0x45)) {
            ApplyAnimEffectToOpponent(sActivePokemon[sp40], 0xF, 0);
        }
    }
}

void Pokemon_HandleSwitchIn(unk_BattlePlayerEntity* arg0) {
    unk_D_800FCB18* sp20;
    s32 sp28;

    sp20 = &arg0->unk_654.unk_38;
    sp28 = IsPrimaryEntity(arg0);

    gCurrentAnimChannel = &gAnimDataByPlayer[IsPrimaryEntity(arg0) == 0]->unk_000[sp20->unk_5A - 1];

    if (sActivePokemon[sp28 == 0]->unk_4C4 == (gCurrentAnimChannel->unk_07 + 1)) {
        if (AnimChannel_GetFlagsFB0(arg0) == 0) {
            Battle_SetAnimChannelFlag(1);
            if (sp20->unk_44.unk_00 == 0x51) {
                if ((gAnimStateFlag != 0) && (gIsBattleMode != 0)) {
                    AnimChannel_StartAnotherMoveAction(sActivePokemon[sp28 == 0], sp20->unk_5A);
                    ApplyAnimEffectToOpponent(sActivePokemon[sp28 == 0], 0x10, 0);
                }
            } else {
                AnimChannel_StartAnotherMoveAction(sActivePokemon[sp28 == 0], sp20->unk_5A);
                if ((sp20->unk_44.unk_00 == 0x14) || (sp20->unk_44.unk_00 == 0x23) || (sp20->unk_44.unk_00 == 0x84)) {
                    ApplyAnimEffectToOpponent(sActivePokemon[sp28 == 0], 0x10, 0);
                }
            }
            gAnimStateQueue[gAnimStateQueueIndex].unk_04 = gAnimStateIdle;
        }
    }
}

void Pokemon_HandleSwitchOut(unk_BattlePlayerEntity* arg0) {
    unk_D_800FCB18* sp20;
    s32 sp28;

    sp28 = IsPrimaryEntity(arg0) == 0;
    sp20 = &arg0->unk_654.unk_38;

    gCurrentAnimChannel = &gAnimDataByPlayer[IsPrimaryEntity(arg0) == 0]->unk_000[sp20->unk_5A - 1];

    if ((gCurrentAnimChannel->unk_07 + 1) == sActivePokemon[sp28]->unk_4C4) {
        if (AnimChannel_GetFlagsFB0(arg0) == 0) {
            if (gIsBattleMode == 1) {
                TriggerMoveEvent(sActivePokemon[sp28], sp20, 1);
            } else {
                TriggerMoveEvent(sActivePokemon[sp28], sp20, 5);
            }
            gAnimStateQueue[gAnimStateQueueIndex].unk_04 = gAnimStateIdle;
        }
    }
}

void Pokemon_StartBattleIntro(unk_BattlePlayerEntity* arg0) {
    s32 sp1C = IsPrimaryEntity(arg0);

    gCurrentAnimChannel = &gAnimDataByPlayer[sp1C]->unk_A80;
    sActivePokemon[sp1C]->unk_4C4 = 0;
    Anim_SetChannelBase(&arg0->unk_000, 0);
    GraphNode_TriggerAction(&arg0->unk_000, gCurrentAnimChannel->unk_00);
    PlayAnimSoundSimple(sActivePokemon[sp1C], 0xA8, 1);
    PlayBattleSoundEffect(arg0, 0x1E);
}

s32 Pokemon_CheckAnimStateC(unk_BattlePlayerEntity* arg0) {
    unk_D_800FCB18* sp1C;

    sp1C = &sActivePokemon[IsPrimaryEntity(arg0) == 0]->unk_654.unk_38;
    gCurrentAnimChannel = &gAnimDataByPlayer[IsPrimaryEntity(arg0)]->unk_000[sp1C->unk_5A - 1];
    if (gCurrentAnimChannel->unk_0C != 0) {
        if (arg0->unk_4C4 == gCurrentAnimChannel->unk_0C) {
            return 1;
        }
        return 0;
    }
    return 0;
}

s32 Pokemon_CheckAnimState0(unk_BattlePlayerEntity* arg0) {
    IsPrimaryEntity(arg0);
    gCurrentAnimChannel = &gAnimDataByPlayer[IsPrimaryEntity(arg0)]->unk_000[0];
    if (gCurrentAnimChannel->unk_0C != 0) {
        if (arg0->unk_4C4 == gCurrentAnimChannel->unk_0C) {
            return 1;
        }
        return 0;
    }
    return 0;
}

void Pokemon_ResetAnimAndTrigger(unk_BattlePlayerEntity* arg0) {
    gCurrentAnimChannel = &gAnimDataByPlayer[IsPrimaryEntity(arg0)]->unk_A80;
    PlayAnimSoundIfApplicable(arg0, 0xA8);
    arg0->unk_4C4 = 0;
    Anim_SetChannelBase(&arg0->unk_000, 0);
    GraphNode_TriggerAction(&arg0->unk_000, gCurrentAnimChannel->unk_00);
}

void Pokemon_HandleSpecialMoveAnimation(unk_BattlePlayerEntity* arg0) {
    s32 idx = arg0->unk_4C0;
    s32 temp_a0;
    s32 sp34;
    PokemonData* sp30;
    unk_BattlePlayerAnimState* sp24;

    sp34 = gMoveAnimData[idx].unk_20;
    sp30 = &arg0->unk_724->unk_01C[arg0->unk_654.unk_08];
    sp24 = &arg0->unk_654;
    gCurrentAnimChannel = &gAnimDataByPlayer[IsPrimaryEntity(arg0)]->unk_000[sp34];
    temp_a0 = sp24->unk_34 & 2;

    if ((temp_a0 == 0) && !(sp24->unk_34 & 0x4000) && (temp_a0 == 0)) {
        if (sp30->unk_05 & 7) {
            if (Array_ContainsValue(arg0->unk_000.unk_01A, gSpecialMoveIDs, 8) != 0) {
                gCurrentAnimChannel = &gAnimDataByPlayer[IsPrimaryEntity(arg0)]->unkA90[0x60];
            } else {
                gCurrentAnimChannel = &gAnimDataByPlayer[IsPrimaryEntity(arg0)]->unk_A50;
            }
        } else if (sp24->unk_34 & 0x200) {
            gCurrentAnimChannel = &gAnimDataByPlayer[IsPrimaryEntity(arg0)]->unk_B00;
        }

        Anim_SetChannelBase(&arg0->unk_000, 0);
        GraphNode_TriggerAction(&arg0->unk_000, gCurrentAnimChannel->unk_00);

        if (sp24->unk_34 & 0x200) {
            if (Pokemon_IsSpecialSpecies(arg0) != 0) {
                PlayMoveSoundEffect(IsPrimaryEntity(arg0) & 0xFF, 0, 0xC8, 0x1A);
            } else {
                PlayMoveSoundEffect(IsPrimaryEntity(arg0) & 0xFF, 0, arg0->unk_000.unk_01A, 0x1A);
            }
        } else if (Pokemon_IsSpecialSpecies(arg0) != 0) {
            PlayMoveSoundEffect(IsPrimaryEntity(arg0) & 0xFF, 0, 0xC8, 0xA);
        } else {
            PlayMoveSoundEffect(IsPrimaryEntity(arg0) & 0xFF, 0, arg0->unk_000.unk_01A, 0xA);
        }
    }
}

void PlayBattleMusicIfReady(unk_BattlePlayerEntity* arg0) {
    UNUSED s32 pad;
    unk_BattlePlayerAnimState* sp18 = &arg0->unk_654;
    PokemonData* ptr = &arg0->unk_724->unk_01C[arg0->unk_654.unk_08];

    if ((sp18->unk_34 & 0x4000) || (sp18->unk_34 & 2) || (ptr->unk_05 & 7)) {
        gAnimStateQueue[gAnimStateQueueIndex].unk_04 = gAnimStateIdle;
    } else if (arg0->unk_4C4 == 1) {
        if (AnimChannel_GetFlagsFB0(arg0) == 0) {
            if (arg0->unk_000.unk_01A >= 0x98) {
                PlayBattleMusicOrDefault(arg0, sp18->unk_BC);
            } else {
                PlayBattleMusicOrDefault(arg0, arg0->unk_000.unk_01A);
            }
            gAnimStateQueue[gAnimStateQueueIndex].unk_04 = gAnimStateIdle;
        }
    }
}

void PlayBattleMusicAndSound(unk_BattlePlayerEntity* arg0) {
    UNUSED s32 pad;
    PokemonData* ptr = &arg0->unk_724->unk_01C[arg0->unk_654.unk_08];
    unk_BattlePlayerAnimState* sp24 = &arg0->unk_654;

    if ((arg0->unk_654.unk_34 & 0x4000) || (sp24->unk_34 & 2) || (ptr->unk_05 & 7)) {
        gAnimStateQueue[gAnimStateQueueIndex].unk_04 = gAnimStateIdle;
    } else if ((arg0->unk_4C4 == 1) && (AnimChannel_GetFlagsFB0(arg0) == 0)) {
        if (arg0->unk_000.unk_01A >= 0x98) {
            Audio_PlaySequence(sp24->unk_BC, 3);
        } else if (Pokemon_IsSpecialSpecies(arg0) != 0) {
            Audio_PlaySequence(0xC8, 3);
        } else {
            Audio_PlaySequence(arg0->unk_000.unk_01A, 3);
        }

        if (sp24->unk_34 & 0x200) {
            if (Pokemon_IsSpecialSpecies(arg0) != 0) {
                PlayMoveSoundEffect(IsPrimaryEntity(arg0) & 0xFF, 0, 0xC8, 0x1B);
            } else {
                PlayMoveSoundEffect(IsPrimaryEntity(arg0) & 0xFF, 0, arg0->unk_000.unk_01A, 0x1B);
            }
        } else if (Pokemon_IsSpecialSpecies(arg0) != 0) {
            PlayMoveSoundEffect(IsPrimaryEntity(arg0) & 0xFF, 0, 0xC8, 0xB);
        } else {
            PlayMoveSoundEffect(IsPrimaryEntity(arg0) & 0xFF, 0, arg0->unk_000.unk_01A, 0xB);
        }
        gAnimStateQueue[gAnimStateQueueIndex].unk_04 = gAnimStateIdle;
    }
}

void PlayBattleMusicAndSoundAlt(unk_BattlePlayerEntity* arg0) {
    UNUSED s32 pad;
    PokemonData* ptr = &arg0->unk_724->unk_01C[arg0->unk_654.unk_08];
    unk_BattlePlayerAnimState* sp24;

    if ((arg0->unk_654.unk_34 & 0x4000) || (ptr->unk_05 & 0x20) || (ptr->unk_05 & 7)) {
        gAnimStateQueue[gAnimStateQueueIndex].unk_04 = gAnimStateIdle;
        return;
    }

    if ((arg0->unk_4C4 == 1) && (AnimChannel_GetFlagsFB0(arg0) == 0)) {
        sp24 = &arg0->unk_654;
        if (arg0->unk_000.unk_01A >= 0x98) {
            Audio_PlaySequence(sp24->unk_BC, 4);
        } else if (Pokemon_IsSpecialSpecies(arg0) != 0) {
            Audio_PlaySequence(0xC8, 4);
        } else {
            Audio_PlaySequence(arg0->unk_000.unk_01A, 4);
        }

        if (sp24->unk_34 & 0x200) {
            if (Pokemon_IsSpecialSpecies(arg0) != 0) {
                PlayMoveSoundEffect(IsPrimaryEntity(arg0) & 0xFF, 0, 0xC8, 0x1B);
            } else {
                PlayMoveSoundEffect(IsPrimaryEntity(arg0) & 0xFF, 0, arg0->unk_000.unk_01A, 0x1B);
            }
        } else if (Pokemon_IsSpecialSpecies(arg0) != 0) {
            PlayMoveSoundEffect(IsPrimaryEntity(arg0) & 0xFF, 0, 0xC8, 0xB);
        } else {
            PlayMoveSoundEffect(IsPrimaryEntity(arg0) & 0xFF, 0, arg0->unk_000.unk_01A, 0xB);
        }

        gAnimStateQueue[gAnimStateQueueIndex].unk_04 = gAnimStateIdle;
    }
}

void Pokemon_HandleMoveHit(unk_BattlePlayerEntity* arg0) {
    UNUSED s32 pad[2];
    s32 sp24 = arg0->unk_4C0;
    unk_BattlePlayerAnimState* temp_v1 = &arg0->unk_654;

    if (AnimChannel_CheckAndReset(arg0) != 0) {
        arg0->unk_720->unk_02 = arg0->unk_654.unk_38.unk_0B;
        arg0->unk_4C4 = 0;
        Anim_TriggerActionScriptMode3(arg0, gMoveAnimData[sp24].unk_24);
        Audio_PlaySoundEffect(3, 0, 0);
        arg0->unk_720->unk_04 = &arg0->unk_720->unk_08[temp_v1->unk_2B]->unk_01C[temp_v1->unk_18];
        gAnimStateQueue[gAnimStateQueueIndex].unk_04 = gAnimStateIdle;
    }
}

void Pokemon_HandleMoveHitSimple(unk_BattlePlayerEntity* arg0) {
    IsPrimaryEntity(arg0);
    if ((arg0->unk_4C4 == 1) && (AnimChannel_GetFlagsFB0(arg0) == 0)) {
        s32 idx = arg0->unk_4C0;

        Anim_TriggerActionScriptMode3(arg0, gMoveAnimData[idx].unk_24);
        Audio_PlaySoundEffect(3, 0, 0);
        gAnimStateQueue[gAnimStateQueueIndex].unk_04 = gAnimStateIdle;
    }
}

void Pokemon_HandleFaintEffect(unk_BattlePlayerEntity* arg0) {
    if (arg0->unk_4C4 == 0x4F) {
        arg0->unk_720->unk_00 |= 0x80;
    }

    if (arg0->unk_720->unk_00 & 0x10) {
        arg0->unk_720->unk_00 &= ~0x90;

        Pokemon_ApplyFaintTransform(arg0);
        RefreshPokemonTransform(arg0);
        Audio_PlaySoundEffect(2, 0, 0);

        gAnimStateQueue[gAnimStateQueueIndex].unk_04 = gAnimStateIdle;

        ExecuteAnimStateHandlers(arg0, 0x12);
    }
}

void Pokemon_ClearTransformFlag(unk_BattlePlayerEntity* arg0) {
    if (arg0->unk_720->unk_00 & 0x10) {
        arg0->unk_720->unk_00 &= ~0x90;
        Pokemon_ClearFaintTransform(arg0);
    }
}

void Pokemon_TriggerAnimByLookup(unk_BattlePlayerEntity* arg0) {
    UNUSED s32 pad[2];
    s32 sp24 = gAnimLookupTable[arg0->unk_654.unk_38.unk_5A - 1];

    gCurrentAnimChannel = &gAnimDataByPlayer[IsPrimaryEntity(arg0)]->unk_000[sp24];
    arg0->unk_4C4 = 0;
    Anim_SetChannelBase(&arg0->unk_000, 0);
    GraphNode_TriggerAction(&arg0->unk_000, gCurrentAnimChannel->unk_00);
    PlayAnimSoundIfApplicable(arg0, sp24);
}

void Pokemon_HandleSpecialMoveEffect(unk_BattlePlayerEntity* arg0) {
    unk_D_800FCB18* temp_s1_2;
    s16 sp22;
    s16 temp_s1;

    sp22 = arg0->unk_000.unk_01A - 1;
    temp_s1_2 = &arg0->unk_654.unk_38;
    temp_s1 = gAnimLookupTable[temp_s1_2->unk_5A - 1];

    IsPrimaryEntity(arg0);

    gCurrentAnimChannel = &gAnimDataByPlayer[IsPrimaryEntity(arg0)]->unk_000[temp_s1];

    if ((arg0->unk_4C4 == (gCurrentAnimChannel->unk_04 + 1)) && (AnimChannel_GetFlagsFB0(arg0) == 0)) {
        AnimChannel_StartSpecialMoveAction(arg0, temp_s1_2->unk_5A);

        if (temp_s1_2->unk_5A == 0x13) {
            ApplyAnimEffectToOpponent(arg0, 3, 0);
        }

        if ((temp_s1_2->unk_5A == 0x5B) && (sp22 != 0x31) && (sp22 != 0x32)) {
            ApplyAnimEffectToOpponent(arg0, 5, 0);
            Battle_ApplyAnimChannelEffect(4, arg0);
        }

        gAnimStateQueue[gAnimStateQueueIndex].unk_04 = gAnimStateIdle;

        TriggerMoveEvent(arg0, temp_s1_2, 4);
    }
}

void Pokemon_SetSpecialAnimChannel(unk_BattlePlayerEntity* arg0) {
    UNUSED s32 pad[3];
    PokemonData* ptr = &arg0->unk_724->unk_01C[arg0->unk_654.unk_08];
    s32 sp1C;

    arg0->unk_4C4 = 0;
    if (!(arg0->unk_654.unk_34 & 2)) {
        if (ptr->unk_05 & 7) {
            if (Array_ContainsValue(arg0->unk_000.unk_01A, gSpecialMoveIDs, 8) != 0) {
                sp1C = 0xAF;
            } else {
                sp1C = 0xA5;
            }
        } else {
            sp1C = 0xA5;
        }
        gCurrentAnimChannel = &gAnimDataByPlayer[IsPrimaryEntity(arg0)]->unk_000[sp1C];
        PlayAnimSoundIfApplicable(arg0, sp1C);
    }
}

void Pokemon_HandleSpecialCondition(unk_BattlePlayerEntity* arg0) {
    unk_D_800FCB18* ptr = &sActivePokemon[IsPrimaryEntity(arg0) == 0]->unk_654.unk_38;

    if (ptr->unk_4C & 0x20) {
        if ((ptr->unk_5A == 0x14) || (ptr->unk_5A == 0x23) || (ptr->unk_5A == 0x51)) {
            InitSingleEntityActionScript(2, arg0);
            ApplyAnimEffectToOpponent(arg0, 0x10, 0);
        }
    }
}

void Pokemon_TriggerAnimIfMatch(unk_BattlePlayerEntity* arg0) {
    unk_D_800FCB18* sp20;
    s32 sp28;

    sp28 = IsPrimaryEntity(arg0) == 0;
    sp20 = &arg0->unk_654.unk_38;
    gCurrentAnimChannel = &gAnimDataByPlayer[IsPrimaryEntity(arg0) == 0]->unk_000[sp20->unk_5A - 1];

    if ((gCurrentAnimChannel->unk_07 + 1) == sActivePokemon[sp28]->unk_4C4) {
        if (AnimChannel_GetFlagsFB0(arg0) == 0) {
            TriggerMoveEvent(arg0, sp20, 5);
            gAnimStateQueue[gAnimStateQueueIndex].unk_04 = gAnimStateIdle;
        }
    }
}

void Pokemon_PlaySoundBasedOnFlags(unk_BattlePlayerEntity* arg0) {
    unk_D_800FCB18* sp20 = &arg0->unk_654.unk_38;

    if (sp20->unk_15 & 8) {
        PlayBattleSoundEffect(arg0, 0x14);
    }

    if (sp20->unk_15 & 0x10) {
        PlayBattleSoundEffect(arg0, 0x21);
    }

    gAnimStateQueue[gAnimStateQueueIndex].unk_04 = gAnimStateIdle;
}

void Pokemon_HandleGroundedAnim(unk_BattlePlayerEntity* arg0) {
    UNUSED s32 pad;
    u16 sp22 = arg0->unk_000.unk_01A;

    gCurrentAnimChannel = &gAnimDataByPlayer[IsPrimaryEntity(arg0)]->unk_A70;
    if ((GetModelBaseY(arg0) != 0.0f) && (sp22 != 0x16) && (sp22 != 0x52) && (sp22 != 0x8E)) {
        gAnimStateQueue[gAnimStateQueueIndex].unk_04 = gAnimStateIdle;
    } else if ((arg0->unk_4C4 == (gCurrentAnimChannel->unk_04 + 1)) && (AnimChannel_GetFlagsFB0(arg0) == 0)) {
        PlayHeightBasedSoundEffect(arg0);
        gAnimStateQueue[gAnimStateQueueIndex].unk_04 = gAnimStateIdle;
    }
}

void Pokemon_HandleAirborneAnim(unk_BattlePlayerEntity* arg0) {
    s32 sp24;

    gCurrentAnimChannel = &gAnimDataByPlayer[IsPrimaryEntity(arg0)]->unk_A70;
    if (gCurrentAnimChannel->unk_09 == 1) {
        sp24 = gCurrentAnimChannel->unk_0A - 0x4C;
    } else {
        sp24 = gCurrentAnimChannel->unk_0A - 0x31;
    }

    if (AnimChannel_GetFlagsFB0(arg0) == 0) {
        if (GetModelBaseY(arg0) != 0.0f) {
            if ((sp24 <= 0) || (sp24 == arg0->unk_4C4)) {
                if (gCurrentAnimChannel->unk_09 == 1) {
                    InitActionScriptMode3(2, arg0, arg0, 0xFF, 0xFF);
                } else {
                    InitActionScriptMode3(0xC, arg0, arg0, 0xFF, 0xFF);
                }
                Audio_PlaySoundEffect(3, 0, 0);
                gAnimStateQueue[gAnimStateQueueIndex].unk_04 = gAnimStateIdle;
            }
        } else if ((sp24 <= 0) || (sp24 == arg0->unk_4C4)) {
            if (gCurrentAnimChannel->unk_09 == 1) {
                InitActionScriptMode3(2, arg0, arg0, 0xFF, 0xFF);
            } else {
                InitActionScriptMode3(0xC, arg0, arg0, 0xFF, 0xFF);
            }
            Audio_PlaySoundEffect(3, 0, 0);
            gAnimStateQueue[gAnimStateQueueIndex].unk_04 = gAnimStateIdle;
        }
    }
}

void CheckAnimStateCompletion(unk_BattlePlayerEntity* arg0) {
    s32 sp24;

    gCurrentAnimChannel = &gAnimDataByPlayer[IsPrimaryEntity(arg0)]->unk_B10;
    if (gCurrentAnimChannel->unk_09 == 1) {
        sp24 = gCurrentAnimChannel->unk_0A - 0x4C;
    } else {
        sp24 = gCurrentAnimChannel->unk_0A - 0x31;
    }

    if ((AnimChannel_GetFlagsFB0(arg0) == 0) && ((sp24 <= 0) || (sp24 == arg0->unk_4C4))) {
        if (gCurrentAnimChannel->unk_09 == 1) {
            InitActionScriptMode3(2, arg0, arg0, 0xFF, 0xFF);
        } else {
            InitActionScriptMode3(0xC, arg0, arg0, 0xFF, 0xFF);
        }
        Audio_PlaySoundEffect(3, 0, 0);
        gAnimStateQueue[gAnimStateQueueIndex].unk_04 = gAnimStateIdle;
    }
}

void UpdateAnimChannelForEntity(unk_BattlePlayerEntity* arg0) {
    UNUSED s32 pad;
    s32 sp48;
    UNUSED s32 pad2;
    s32 sp40;
    unk_BattlePlayerAnimState* sp3C;
    UNUSED s32 pad3[2];
    unk_BattlePlayerEntity* sp30;
    unk_D_800FCB18* sp28;

    sp48 = 0xA5;
    sp40 = IsPrimaryEntity(arg0) == 0;
    sp3C = &sActivePokemon[sp40]->unk_654;
    sp30 = sActivePokemon[sp40];
    sp28 = &arg0->unk_654.unk_38;

    gCurrentAnimChannel = &gAnimDataByPlayer[sp40]->unk_A80;

    if (sp3C->unk_34 & 1) {
        if (Array_ContainsValue(sp30->unk_000.unk_01A, gSpecialConditionIDs, 2) != 0) {
            gCurrentAnimChannel = &gAnimDataByPlayer[sp40]->unk_B20;
        }
    }

    if ((sp3C->unk_34 & 1) && Array_ContainsValue(sp30->unk_000.unk_01A, gSpecialMoveIDs, 8)) {
        sp48 = 0xAF;
    }

    sActivePokemon[sp40]->unk_4C4 = 0;

    if (!(sp3C->unk_34 & 0x4000) && !(sp3C->unk_34 & 2)) {
        if ((sp28->unk_5A == 0x91) && (gAnimTimer < 0xA)) {
            gCurrentAnimChannel = &gAnimDataByPlayer[sp40]->unk_000[sp48];
        }

        if ((gIsBattleMode == 0) || (gSpecialFlag != 0)) {
            // FAKE? keeps &gCurrentAnimChannel out of a register while the load stays a CSE temp
            if (gAnimDataByPlayer[sp40]) {}
            gCurrentAnimChannel = &gAnimDataByPlayer[sp40]->unk_000[sp48];
            if (sp3C->unk_34 & 0x200) {
                gCurrentAnimChannel = &gAnimDataByPlayer[sp40]->unk_000[0xB0];
            }
        } else if (!(sp3C->unk_34 & 1)) {
            PlayAnimSoundIfApplicable(sActivePokemon[sp40], 0xA8);
        }

        Anim_SetChannelBase(&sActivePokemon[sp40]->unk_000, 0);
        GraphNode_TriggerAction(&sActivePokemon[sp40]->unk_000, gCurrentAnimChannel->unk_00);

        if ((sp28->unk_44.unk_00 == 0x17) || (sp28->unk_44.unk_00 == 0x22) || (sp28->unk_44.unk_00 == 0x45)) {
            ApplyAnimEffectToOpponent(sActivePokemon[sp40], 0xF, 0);
        }
    }
}

void ProcessAnimStateMatch(unk_BattlePlayerEntity* arg0) {
    s32 sp2C;
    UNUSED s32 pad;
    unk_D_800FCB18* sp24;
    unk_D_800FCB18* sp1C;

    sp2C = IsPrimaryEntity(arg0);
    sp24 = &sActivePokemon[sp2C == 0]->unk_654.unk_38;
    sp1C = &arg0->unk_654.unk_38;

    gCurrentAnimChannel = &gAnimDataByPlayer[sp2C == 0]->unk_000[sp1C->unk_5A - 1];

    if ((sActivePokemon[sp2C == 0]->unk_4C4 == (gCurrentAnimChannel->unk_07 + 1)) && (AnimChannel_GetFlagsFB0(arg0) == 0)) {
        Battle_SetAnimChannelFlag(1);
        if (((sp1C->unk_5A == 0x30) || (sp1C->unk_5A == 0x6D)) && (sp24->unk_4C & 0x80) && (gSpecialFlag == 0) &&
            (gIsBattleMode == 1)) {
            PlayBattleSoundEffect(sActivePokemon[sp2C == 0], 0x12);
        }

        AnimChannel_StartAnotherMoveAction(sActivePokemon[sp2C == 0], sp1C->unk_5A);
        if ((gSpecialFlag == 0) || (gIsBattleMode == 1)) {
            TriggerMoveEvent(sActivePokemon[sp2C == 0], &arg0->unk_654.unk_38, 1);
        }

        gAnimStateQueue[gAnimStateQueueIndex].unk_04 = gAnimStateIdle;
    }
}

s32 GetAnimStateResultCode(unk_BattlePlayerEntity* arg0) {
    unk_D_800FCB18* ptr = &arg0->unk_654.unk_38;
    s32 temp_v1;

    temp_v1 = IsPrimaryEntity(arg0) == 0;
    gCurrentAnimChannel = &gAnimDataByPlayer[temp_v1]->unk_000[ptr->unk_5A - 1];

    if (gAnimStateFlag != 1) {
        return 2;
    }

    if ((gCurrentAnimChannel->unk_08 + 0x50) == sActivePokemon[temp_v1]->unk_4C4) {
        return 1;
    }

    return 0;
}

void TriggerAnimStateSound(unk_BattlePlayerEntity* arg0) {
    unk_D_800FCB18* ptr = &arg0->unk_654.unk_38;
    s32 sp28;

    sp28 = IsPrimaryEntity(arg0) == 0;
    gCurrentAnimChannel = &gAnimDataByPlayer[IsPrimaryEntity(arg0) == 0]->unk_000[ptr->unk_5A - 1];
    if (sActivePokemon[sp28]->unk_4C4 == (gCurrentAnimChannel->unk_08 + 1)) {
        if (AnimChannel_GetFlagsFB0(arg0) == 0) {
            if (gAnimStateFlag == 1) {
                InitSingleEntityActionScript(1, sActivePokemon[sp28]);
                PlayBattleSoundEffect(arg0, 0x20);
            }
            gAnimStateQueue[gAnimStateQueueIndex].unk_04 = gAnimStateIdle;
        }
    }
}

void ApplyAnimStateEffect(unk_BattlePlayerEntity* arg0) {
    unk_D_800FCB18* sp20;
    s32 sp28;

    sp28 = IsPrimaryEntity(arg0) == 0;
    sp20 = &arg0->unk_654.unk_38;
    gCurrentAnimChannel = &gAnimDataByPlayer[IsPrimaryEntity(arg0) == 0]->unk_000[sp20->unk_5A - 1];

    if ((gCurrentAnimChannel->unk_07 + 1) == sActivePokemon[sp28]->unk_4C4) {
        if (AnimChannel_GetFlagsFB0(arg0) == 0) {
            if (gIsBattleMode == 1) {
                TriggerMoveEvent(sActivePokemon[sp28], sp20, 1);
            } else {
                TriggerMoveEvent(sActivePokemon[sp28], sp20, 5);
            }
            gAnimStateQueue[gAnimStateQueueIndex].unk_04 = gAnimStateIdle;
        }
    }
}

void Anim_NullHandler(unk_BattlePlayerEntity* arg0) {
}

void ReplaceAnimQueueEntry(unk_BattlePlayerEntity* arg0, unk_D_84385384_func arg1) {
    unk_D_84390068* var_a2;
    s32 i;

    for (i = 0; i < 7; i++) {
        if (gAnimStateIdle == gAnimStateQueue[i].unk_04) {
            gAnimStateQueue[i].unk_04 = arg1;
            gAnimStateQueue[i].unk_00 = arg0;
            break;
        }
    }
}

void ResetAnimChannelToDefault(unk_BattlePlayerEntity* arg0) {
    PlayAnimSoundIfApplicable(sActivePokemon[IsPrimaryEntity(arg0)], 0xA6);
}

void ExecuteAnimStateHandlers(unk_BattlePlayerEntity* arg0, s32 arg1) {
    arg0->unk_4C0 = arg1;

    gMoveAnimData[arg1].unk_04[0](arg0);
    gMoveAnimData[arg1].unk_04[1](arg0);
    gMoveAnimData[arg1].unk_04[2](arg0);

    ReplaceAnimQueueEntry(arg0, gMoveAnimData[arg1].unk_04[3]);
    ReplaceAnimQueueEntry(arg0, gMoveAnimData[arg1].unk_04[4]);
    ReplaceAnimQueueEntry(arg0, gMoveAnimData[arg1].unk_04[5]);
    ReplaceAnimQueueEntry(arg0, gMoveAnimData[arg1].unk_04[6]);
}

void Anim_ProcessQueue(void) {
    sActivePokemon[0]->unk_4C4++;
    sActivePokemon[1]->unk_4C4++;

    for (gAnimStateQueueIndex = 0; gAnimStateQueueIndex < 7; gAnimStateQueueIndex++) {
        gAnimStateQueue[gAnimStateQueueIndex].unk_04(gAnimStateQueue[gAnimStateQueueIndex].unk_00);
    }
}

void ClearAnimFlagIfState6A(unk_BattlePlayerEntity* arg0) {
    if (arg0->unk_654.unk_38.unk_5A == 0x6A) {
        arg0->unk_000.unk_01C = 0;
    }
}

void PlayAnimSoundIfApplicable(unk_BattlePlayerEntity* arg0, s32 arg1) {
    s32 temp_v0;
    s32 sp30;
    unk_BattlePlayerAnimState* sp24 = &arg0->unk_654;

    if (AnimChannel_GetFlagsFF0(arg0) == 0) {
        sp30 = gAnimDataByPlayer[IsPrimaryEntity(arg0)]->unk_000[arg1].unk_01;
        if ((sp30 != 0xFF) && (sp24->unk_36 != 2)) {
            if ((arg1 == 165) && (arg0->unk_000.unk_01A == 0x33)) {
                SetAnimStateIndex(&arg0->unk_000, 0);
                temp_v0 = Math_RandomU16Scaled(3);
                if (temp_v0 >= 3) {
                    temp_v0 = 2;
                }
                GraphNode_TriggerSound(&arg0->unk_000, sp30 + temp_v0);
            } else {
                SetAnimStateIndex(&arg0->unk_000, 0);
                GraphNode_TriggerSound(&arg0->unk_000, sp30);
                sp24->unk_36 = 1;
            }
        }
    }
}

s32 TryPlayAnimSoundAndSetState(unk_BattlePlayerEntity* arg0, s32 arg1, s32 arg2) {
    UNUSED s32 pad;
    s32 sp20;

    if (AnimChannel_GetFlagsFF0(arg0) != 0) {
        return 0;
    }

    sp20 = gAnimDataByPlayer[IsPrimaryEntity(arg0)]->unk_000[arg1].unk_01;
    if (sp20 == 0xFF) {
        return 1;
    }

    SetAnimStateIndex(&arg0->unk_000, 0);
    GraphNode_TriggerSound(&arg0->unk_000, sp20);
    SetAnimStateIndex(&arg0->unk_000, arg0->unk_000.unk_054.unk_04->unk_0A);

    arg0->unk_654.unk_36 = arg2;
    return 0;
}

void PlayAnimSoundSimple(unk_BattlePlayerEntity* arg0, s32 arg1, s32 arg2) {
    u8 temp_a1;

    if (AnimChannel_GetFlagsFF0(arg0) == 0) {
        temp_a1 = gAnimDataByPlayer[IsPrimaryEntity(arg0)]->unk_000[arg1].unk_01;
        if (temp_a1 != 0xFF) {
            GraphNode_TriggerSound(&arg0->unk_000, temp_a1);
            SetAnimStateIndex(&arg0->unk_000, 0);
            arg0->unk_654.unk_36 = arg2;
        }
    }
}

s32 IsAnimStateLocked(unk_BattlePlayerEntity* arg0) {
    unk_BattlePlayerAnimState* sp20 = &arg0->unk_654;
    PokemonData* ptr = &arg0->unk_724->unk_01C[arg0->unk_654.unk_08];

    if ((sp20->unk_34 & 2) || (ptr->unk_05 & 7) || ((sp20->unk_34 & 0x200) && !(sp20->unk_34 & 0x400)) ||
        (sp20->unk_34 & 0x4000)) {
        return 1;
    }
    return 0;
}

s32 CanAnimProceed(unk_BattlePlayerEntity* arg0, s32 arg1) {
    if (IsAnimStateLocked(arg0) != 0) {
        if (Battle_WaitForAnimation(arg1) != 0) {
            return 1;
        }
        return 0;
    }

    if (arg0->unk_000.unk_040.unk_00 == -1) {
        return 1;
    }
    return GraphNode_IsAnimationFinished(&arg0->unk_000);
}

s32 CanAnimProceedWithChannel(unk_BattlePlayerEntity* arg0, s32 arg1) {
    u8 temp_v0;

    gCurrentAnimChannel = gAnimDataByPlayer[IsPrimaryEntity(arg0)]->unkA60;
    if (IsAnimStateLocked(arg0) != 0) {
        if (Battle_WaitForAnimation(arg1) != 0) {
            return 1;
        }
        return 0;
    }

    if ((gCurrentAnimChannel->unk_0A < 0xB) || (gCurrentAnimChannel->unk_0A == 0xFF)) {
        if (arg0->unk_000.unk_040.unk_00 == -1) {
            return 1;
        }
        return GraphNode_IsAnimationFinished(&arg0->unk_000);
    }

    if (Battle_WaitForAnimation(gCurrentAnimChannel->unk_0A + 1) != 0) {
        return 1;
    }

    return 0;
}

s32 EvaluateAnimStateAgainstBattle(unk_BattlePlayerEntity* arg0, s32 arg1) {
    unk_D_800FCB18* ptr = &arg0->unk_654.unk_38;
    unk_BattleAnimDataEntry* sp20;
    unk_BattleAnimDataEntry* sp1C;

    if (arg0) {}

    sp20 = &gAnimDataByPlayer[IsPrimaryEntity(arg0)]->unk_000[ptr->unk_5A - 1];
    sp1C = &gAnimDataByPlayer[IsPrimaryEntity(arg0)]->unk_A50;

    if (IsAnimStateLocked(arg0) != 0) {
        if (Battle_WaitForAnimation(arg1) != 0) {
            return 1;
        }
        return 0;
    }

    if (arg0->unk_000.unk_040.unk_00 == -1) {
        return 1;
    }

    if (gBattleState.unk_00->unk_48 == 0x14) {
        sp20 = &gAnimDataByPlayer[IsPrimaryEntity(arg0)]->unk_000[0];
    }

    if (sp20->unk_00 == sp1C->unk_00) {
        if (sp20->unk_0A != 0xFF) {
            gBattleState.unk_00->unk_14++;
            if (sp20->unk_0A == arg0->unk_4C4) {
                return 1;
            }
            return 0;
        }

        if (Battle_WaitForAnimation(arg1) != 0) {
            return 1;
        }
        return 0;
    }

    gBattleState.unk_00->unk_14++;

    if (sp20->unk_0A != 0xFF) {
        if (sp20->unk_0A == arg0->unk_4C4) {
            return 1;
        }
        return 0;
    }

    return GraphNode_IsAnimationFinished(&arg0->unk_000);
}

s32 EvaluateAnimStateWithAlternateChannel(unk_BattlePlayerEntity* arg0, s32 arg1) {
    unk_BattleAnimDataEntry* temp_a2;
    PokemonData* sp28;
    UNUSED s32 pad;
    s32 sp20;
    unk_BattleAnimDataEntry* sp1C;

    sp28 = &arg0->unk_724->unk_01C[arg0->unk_654.unk_08];
    sp20 = gAnimLookupTable[arg0->unk_654.unk_38.unk_5A - 1];
    sp1C = &gAnimDataByPlayer[IsPrimaryEntity(arg0)]->unk_000[sp20];
    temp_a2 = &gAnimDataByPlayer[IsPrimaryEntity(arg0)]->unk_A50;

    if ((arg0->unk_654.unk_34 & 2) || (sp28->unk_05 & 7) ||
        ((arg0->unk_654.unk_34 & 0x200) && !(arg0->unk_654.unk_34 & 0x400)) || (arg0->unk_654.unk_34 & 0x4000)) {
        if (Battle_WaitForAnimation(arg1) != 0) {
            return 1;
        }
        return 0;
    }

    if (arg0->unk_000.unk_040.unk_00 == -1) {
        return 1;
    }

    if (sp1C->unk_00 == temp_a2->unk_00) {
        if (sp1C->unk_0A != 0xFF) {
            gBattleState.unk_00->unk_14++;
            if (sp1C->unk_0A == arg0->unk_4C4) {
                return 1;
            }
            return 0;
        }
        if (Battle_WaitForAnimation(arg1) != 0) {
            return 1;
        }
        return 0;
    }

    gBattleState.unk_00->unk_14++;

    if (sp1C->unk_0A != 0xFF) {
        if (sp1C->unk_0A == arg0->unk_4C4) {
            return 1;
        }
        return 0;
    }
    return GraphNode_IsAnimationFinished(&arg0->unk_000);
}

s32 CanAnimChannelA80Proceed(unk_BattlePlayerEntity* arg0, s32 arg1) {
    gCurrentAnimChannel = &gAnimDataByPlayer[IsPrimaryEntity(arg0)]->unk_A80;

    if ((arg0->unk_654.unk_34 & 2) || ((arg0->unk_654.unk_34 & 0x200) && !(arg0->unk_654.unk_34 & 0x400))) {
        if (Battle_WaitForAnimation(arg1) != 0) {
            return 1;
        }
        return 0;
    }

    if (arg0->unk_000.unk_040.unk_00 == -1) {
        return 1;
    }

    if (arg0->unk_000.unk_040.unk_00 != gCurrentAnimChannel->unk_00) {
        return 1;
    }

    return GraphNode_IsAnimationFinished(&arg0->unk_000);
}

void MaybeTriggerSpecialAnimEffect(unk_BattlePlayerEntity* arg0) {
    gCurrentAnimChannel = &gAnimDataByPlayer[IsPrimaryEntity(arg0)]->unk_A50;
    if (AnimChannel_GetFlagsFF0(arg0) == 0) {
        if ((arg0->unk_000.unk_040.unk_00 != -1) && (arg0->unk_000.unk_000.unk_01 & 1) &&
            (arg0->unk_000.unk_000.unk_02 & 0x20) && (gBattleState.unk_00->unk_1C == 1) &&
            (gCurrentAnimChannel->unk_00 == arg0->unk_000.unk_040.unk_00) &&
            (gCurrentAnimChannel->unk_04 == (arg0->unk_000.unk_040.unk_08 >> 0x10)) && (gCurrentAnimChannel->unk_05 != 0) &&
            (Math_RandomU16Scaled(2) == 1)) {
            InitActionScriptMode3(gCurrentAnimChannel->unk_05, &arg0->unk_000, &arg0->unk_000, gCurrentAnimChannel->unk_02, gCurrentAnimChannel->unk_02);
        }
    }
}

void SetEntityAnimFlags(unk_BattlePlayerEntity* arg0, u16 arg1) {
    arg0->unk_654.unk_34 |= arg1;
}

s32 ClearEntityAnimFlags(unk_BattlePlayerEntity* arg0, u16 arg1) {
    arg0->unk_654.unk_34 &= ~arg1;
}

void UpdateEntityModelForAnimFlags(unk_BattlePlayerEntity* arg0) {
    unk_BattlePlayerAnimState* sp24 = &arg0->unk_654;

    if (arg0->unk_4C8 != 0) {
        if (sp24->unk_34 & 0x200) {
            arg0->unk_000.unk_024.y = gPokemonModelDimensions[IsPrimaryEntity(arg0)].unk_08;
            ClearEntityAnimFlags(arg0, 0x608);
        }

        if (sp24->unk_34 & 0x4008) {
            arg0->unk_000.unk_01D = 0xFF;
            RunParticleEffectScript(4, arg0);
            arg0->unk_000.unk_024.y = gPokemonModelDimensions[IsPrimaryEntity(arg0)].unk_08;
            arg0->unk_000.unk_000.unk_02 &= ~2;
            arg0->unk_000.unk_000.unk_02 |= 0x20;
            arg0->unk_000.unk_000.unk_01 |= 1;
            ClearEntityAnimFlags(arg0, 0x4608);
        }
    }
}

void ProcessEntityAnimFlagUpdates(void) {
    unk_BattlePlayerAnimState* sp34;
    unk_BattlePlayerAnimState* sp30;
    UNUSED s32 pad[2];
    unk_BattlePlayerEntity* sp24;
    unk_BattlePlayerEntity* sp20;

    sp34 = &sActivePokemon[0]->unk_654;
    sp30 = &sActivePokemon[1]->unk_654;
    sp24 = sActivePokemon[0];
    sp20 = sActivePokemon[1];

    if (sp34->unk_34 & 4) {
        sActivePokemon[0]->unk_000.unk_024.y = 200.0f;
        SetEntityAnimFlags(sActivePokemon[0], 0x200);
        ClearEntityAnimFlags(sActivePokemon[0], 4);
    }

    if (sp30->unk_34 & 4) {
        sActivePokemon[1]->unk_000.unk_024.y = 200.0f;
        SetEntityAnimFlags(sActivePokemon[1], 0x200);
        ClearEntityAnimFlags(sActivePokemon[1], 4);
    }

    if ((sp34->unk_34 & 0x4000) && (sp24->unk_000.unk_01A == 0x33)) {
        gCurrentAnimChannel = &gAnimDataByPlayer[0]->unk_000[0x5A];
        Anim_SetChannelBase(&sActivePokemon[0]->unk_000, 0);
        GraphNode_TriggerAction(&sActivePokemon[0]->unk_000, gCurrentAnimChannel->unk_00);
    }

    if ((sp30->unk_34 & 0x4000) && (sp20->unk_000.unk_01A == 0x33)) {
        gCurrentAnimChannel = &gAnimDataByPlayer[1]->unk_000[0x5A];
        Anim_SetChannelBase(&sActivePokemon[1]->unk_000, 0);
        GraphNode_TriggerAction(&sActivePokemon[1]->unk_000, gCurrentAnimChannel->unk_00);
    }

    UpdateEntityModelForAnimFlags(sActivePokemon[0]);
    UpdateEntityModelForAnimFlags(sActivePokemon[1]);
}

void PrepareEntityAnimState(unk_BattlePlayerEntity* arg0) {
    UNUSED s32 pad;
    unk_BattlePlayerAnimState* sp20;

    sp20 = &sActivePokemon[IsPrimaryEntity(arg0) == 0]->unk_654;
    IsPrimaryEntity(arg0);
    IsPrimaryEntity(arg0);
    ClearAnimFlagIfState6A(sActivePokemon[IsPrimaryEntity(arg0) == 0]);

    if (sp20->unk_34 & 4) {
        sActivePokemon[IsPrimaryEntity(arg0) == 0]->unk_000.unk_024.y = 200.0f;
        SetEntityAnimFlags(sActivePokemon[IsPrimaryEntity(arg0) == 0], 0x200);
        ClearEntityAnimFlags(sActivePokemon[IsPrimaryEntity(arg0) == 0], 4);
    }

    if (arg0->unk_654.unk_34 & 0x200) {
        SetEntityAnimFlags(arg0, 0x400);
    }
}

void AdjustModelBaseYForFlag8(unk_BattlePlayerEntity* arg0) {
    if (arg0->unk_654.unk_34 & 8) {
        arg0->unk_000.unk_024.y = GetModelBaseY(arg0);
        ClearEntityAnimFlags(arg0, 0x608);
    }
}

void HandleFlag4000AnimEffect(unk_BattlePlayerEntity* arg0) {
    UNUSED s32 pad[2];
    unk_BattlePlayerEntity* sp1C = sActivePokemon[IsPrimaryEntity(arg0) == 0];

    if (sp1C->unk_654.unk_34 & 0x4000) {
        sp1C->unk_000.unk_000.unk_02 |= 0x20;
        sp1C->unk_000.unk_000.unk_01 |= 1;
        RunParticleEffectScript(4, sp1C);
        ClearEntityAnimFlags(sp1C, 0x4000);
    }
}

void ApplyFlag4000EffectToEntity(unk_BattlePlayerEntity* arg0) {
    unk_BattlePlayerEntity* temp_s0 = sActivePokemon[IsPrimaryEntity(arg0) == 0];
    unk_BattlePlayerAnimState* ptr = &temp_s0->unk_654;

    if (ptr->unk_34 & 0x4000) {
        temp_s0->unk_000.unk_000.unk_02 |= 0x20;
        temp_s0->unk_000.unk_000.unk_01 |= 1;
        RunParticleEffectScript(4, temp_s0);
        ClearEntityAnimFlags(temp_s0, 0x4000);
    }

    if (ptr->unk_34 & 8) {
        temp_s0->unk_000.unk_024.y = GetModelBaseY(arg0);
        ClearEntityAnimFlags(temp_s0, 0x608);
    }
}

void UpdateEntityStateByMode(unk_BattlePlayerEntity* arg0) {
    switch (arg0->unk_4B4) {
        case 14:
            ApplyAnimEffectToOpponent(arg0, 0, 0);
            UpdateEntityBasePosition(arg0);
            break;

        case 13:
        case 15:
        case 16:
            ApplyAnimEffectToOpponent(arg0, 0, 0);
            if (arg0->unk_654.unk_38.unk_56 == 0) {
                Vec3f_Set(&arg0->unk_000.unk_030, 1.0f, 1.0f, 1.0f);
            } else {
                Vec3f_Set(&arg0->unk_000.unk_030, 0.8f, 0.8f, 0.8f);
            }
            break;

        case 12:
            ApplyAnimEffectToOpponent(arg0, 0, 0);
            if (arg0->unk_654.unk_38.unk_56 == 0) {
                Vec3f_Set(&arg0->unk_000.unk_030, 1.0f, 1.0f, 1.0f);
            } else {
                Vec3f_Set(&arg0->unk_000.unk_030, 0.8f, 0.8f, 0.8f);
            }
            break;

        case 10:
            ApplyAnimEffectToOpponent(arg0, 0, 0);
            arg0->unk_000.unk_024.y = GetModelBaseY(arg0);
            arg0->unk_000.unk_01E.x = 0;
            break;

        case 9:
            ApplyAnimEffectToOpponent(arg0, 0, 0);
            Vec3f_Set(&arg0->unk_000.unk_030, 0.8f, 0.8f, 0.8f);
            Entity_ResetSubObjectFlags(arg0);
            break;

        case 7:
            ApplyAnimEffectToOpponent(arg0, 0, 0);
            Entity_ResetSubObjectFlags(arg0);
            break;

        case 6:
            ApplyAnimEffectToOpponent(arg0, 0, 0);
            Entity_ResetSubObjectFlags(arg0);
            UpdateEntityBasePosition(arg0);
            Vec3s_Set(&arg0->unk_000.unk_01E, 0, arg0->unk_4B0 << 0xE, 0);
            break;

        case 4:
            ApplyAnimEffectToOpponent(arg0, 0, 0);
            arg0->unk_000.unk_01E.y = arg0->unk_4B0 << 0xE;
            Entity_ResetSubObjectFlags(arg0);
            break;
    }
}

void ProcessEntityPostMoveEffects(unk_BattlePlayerEntity* arg0) {
    unk_BattlePlayerAnimState* temp_s1 = &arg0->unk_654;

    HandleMoveHitAnimation(arg0);
    HandleItemOrStatusEffect(arg0);

    if (temp_s1->unk_34 & 0x100) {
        arg0->unk_000.unk_000.unk_02 &= 0xFFDF;
    }

    if ((temp_s1->unk_2D == 0x10) || (temp_s1->unk_2D == 0x13)) {
        ClearEntityAnimFlags(arg0, 0x100);
    }

    temp_s1->unk_2E = Math_ApproachS32(temp_s1->unk_2E, 0, 0x1E, 0x1E);
    if (temp_s1->unk_2E != 0) {
        GraphNode_SetColorRGBA(&arg0->unk_000, 0xFF, 0xFF, 0xFF, temp_s1->unk_2E);
    }

    switch (temp_s1->unk_36) {
        case 2:
            break;

        case 0:
            if (Math_RandomU16Scaled(0x32) == 2) {
                PlayAnimSoundIfApplicable(arg0, 0xA5);
            }
            break;

        case 1:
            if (IsAnimStateSecondLast(&arg0->unk_000) == 1) {
                GraphNode_TriggerSound(&arg0->unk_000, -1);
                SetAnimStateIndex(&arg0->unk_000, 0);
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

void TriggerStatusEffectSound(unk_BattlePlayerEntity* arg0) {
    PokemonData* ptr = &arg0->unk_724->unk_01C[arg0->unk_654.unk_08];

    if ((ptr->unk_05 & 7) && !(arg0->unk_654.unk_34 & 1)) {
        PlayAnimSoundSimple(arg0, 0xAF, 2);
        Battle_ApplyAnimChannelEffect(3, arg0);
        PlayBattleSoundEffect(arg0, 0x32);
    }
}

void AllocateEntityStruct(unk_D_800AE540_1194* arg0, s32 arg1) {
    unk_BattlePlayerEntity* ptr = main_pool_alloc(sizeof(unk_BattlePlayerEntity), 0);

    sActivePokemon[arg1] = ptr;

    bzero(ptr, sizeof(unk_BattlePlayerEntity));
    bzero(&sActivePokemon[arg1]->unk_654, sizeof(unk_BattlePlayerAnimState));
    bzero(&sActivePokemon[arg1]->unk_654.unk_38, sizeof(unk_D_800FCB18));
    bzero(&sActivePokemon[arg1]->unk_728, sizeof(unk_D_84390010_728));
    bzero(&sActivePokemon[arg1]->unk_654.unk_38.unk_44, sizeof(unk_D_800FCB18_044));
    bzero(&sActivePokemon[arg1]->unk_654.unk_9C, sizeof(unk_D_84390010_654_09C));
    bzero(&sActivePokemon[arg1]->unk_654.unk_AC, sizeof(unk_D_84390010_654_0AC));
    bzero(&sActivePokemon[arg1]->unk_8C4, sizeof(unk_D_84390010_8C4));
    sActivePokemon[arg1]->unk_720 = arg0;
}

void InitializeBattleEntities(unk_D_800AE540_1194* arg0) {
    AllocateEntityStruct(&arg0[0], 0);
    AllocateEntityStruct(&arg0[1], 1);
    Battle_InitMessageQueues();
    gPrimaryPokemonEntity = sActivePokemon[0];
    gPokemonEntityUnused = sActivePokemon[1];
}

void SetupEntityController(unk_BattlePlayerEntity* arg0) {
    Controller* sp24 = &gControllers[arg0->unk_720->unk_08[0]->unk_001];

    Entity_InitController(arg0, 0);
    Entity_InitPhysics(arg0, 0);
    Entity_BindController(arg0, sp24);
    arg0->unk_728.unk_16C = 0;
}

void InitEntityGraphNode(unk_BattlePlayerEntity* arg0) {
    UNUSED s32 pad[2];
    unk_D_86002F58_004_000_004* sp24;
    s16 sp22;

    IsPrimaryEntity(arg0);
    sp24 = GraphNode_GetModelRoot(arg0, 0);
    sp22 = GraphNode_GetModelPhase(arg0, 0);
    Graph_AddToRootList0(&arg0->unk_000);

    if (arg0 == sActivePokemon[0]) {
        arg0->unk_000.modelPhase = 0;
    } else {
        arg0->unk_000.modelPhase = 1;
    }

    GraphNode_InitChild(&arg0->unk_000, 0, sp22, sp24);
    LoadPlayerAnimationData(arg0, 1);
    GraphNode_TriggerAction(&arg0->unk_000, 0);
    Anim_SetChannelBase(&arg0->unk_000, 0);

    arg0->unk_720->unk_04 = arg0->unk_724->unk_01C;
    if ((arg0->unk_000.unk_01A == 0x32) || (arg0->unk_000.unk_01A == 0x33)) {
        arg0->unk_000.unk_000.unk_02 &= ~0x40;
    } else {
        arg0->unk_000.unk_000.unk_02 |= 0x40;
    }

    if (arg0 == sActivePokemon[0]) {
        UpdateEntityBasePosition(arg0);
        arg0->unk_000.unk_01E.y = 0x4000;
    } else {
        UpdateEntityBasePosition(arg0);
        arg0->unk_000.unk_01E.y = -0x4000;
    }
}

void InitEntitySubObjectGraph(unk_BattlePlayerEntity* arg0) {
    unk_D_84390010_728* ptr = &arg0->unk_728;
    unk_D_86002F58_004_000_004* sp28;
    s16 sp26;

    sp28 = GraphNode_GetModelRoot(arg0, 0);
    sp26 = GraphNode_GetModelPhase(arg0, 0);
    Graph_AddToRootList0(&ptr->unk_000);

    if (arg0 == sActivePokemon[0]) {
        ptr->unk_000.modelPhase = -1;
        GraphNode_InitChild(&ptr->unk_000, 1, sp26, sp28);
    } else {
        ptr->unk_000.modelPhase = -1;
        GraphNode_InitChild(&ptr->unk_000, 2, sp26, sp28);
    }

    GraphNode_TriggerAction(&ptr->unk_000, 0);
    Anim_SetChannelBase(&ptr->unk_000, 0);
    ptr->unk_000.unk_000.unk_02 &= ~0x40;
    Vec3f_Set(&ptr->unk_000.unk_024, 0.0f, 0.0f, 0.0f);
}

void InitEntityChildNodes(unk_BattlePlayerEntity* arg0, s32* arg1) {
    unk_D_86002F58_004_000_004* sp44;
    s16 sp42;
    s32 i;
    unk_D_84390010_168* ptr;

    sp44 = GraphNode_GetModelRoot(arg0, 0);
    sp42 = GraphNode_GetModelPhase(arg0, 0);

    for (i = 0; i < 2; i++) {
        ptr = &arg0->unk_168[i];

        Graph_AddToRootList0(ptr);

        if (arg0 == sActivePokemon[0]) {
            ptr->unk_000.modelPhase = 0xFF;
        } else {
            ptr->unk_000.modelPhase = 0xFF;
        }

        GraphNode_InitChild(ptr, 0, sp42, sp44);
        Anim_SetChannelBase(ptr, 0);
        GraphNode_TriggerAction(ptr, 0);

        ptr->unk_000.unk_000.unk_02 &= ~0x40;

        if (arg0 == sActivePokemon[0]) {
            UpdateEntityBasePosition(arg0);
        } else {
            UpdateEntityBasePosition(arg0);
        }
        ptr->unk_000.unk_000.unk_01 &= ~1;
    }
}

void InitEntityFragmentNode(unk_BattlePlayerEntity* arg0) {
    Fragment2_1GraphNode* ptr = &arg0->unk_4EC;
    unk_D_86002F58_004_000_004* sp20 = arg0->unk_720->unk_18;

    Graph_AddToRootList0(ptr);
    ptr->modelPhase = 0xFF;
    GraphNode_InitChild(ptr, 0, 0x9A, sp20);
    GraphNode_TriggerAction(ptr, 0);

    ptr->unk_000.unk_02 &= ~0x20;
    ptr->unk_000.unk_01 &= ~1;

    if (arg0 == sActivePokemon[0]) {
        Vec3f_Set(&ptr->unk_024, -50.0f, 2.0f, 0.0f);
    } else {
        Vec3f_Set(&ptr->unk_024, 50.0f, 2.0f, 0.0f);
    }
}

void InitializeBattleScene(unk_D_800AE540_1194* arg0) {
    gBattleInitFlag = 0;
    gBattleInitStruct.unk_00 = 0;

    SetupEntityController(sActivePokemon[0]);
    SetupEntityController(sActivePokemon[1]);
    InitEntityGraphNode(sActivePokemon[0]);
    InitEntityGraphNode(sActivePokemon[1]);
    InitEntitySubObjectGraph(sActivePokemon[0]);
    InitEntitySubObjectGraph(sActivePokemon[1]);
    InitEntityChildNodes(sActivePokemon[0], &sActivePokemon[0]->unk_168);
    InitEntityChildNodes(sActivePokemon[1], &sActivePokemon[1]->unk_168);
    InitEntityFragmentNode(sActivePokemon[0]);
    InitEntityFragmentNode(sActivePokemon[1]);

    switch (gBattleContext.unk_0000) {
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
            Battle_SetCamera(4, 0);
            break;

        case 16:
            Battle_SetCamera(1, 0x32);
            ResultScreen_SetAnimation(1);
            break;

        default:
            Battle_SetCamera(4, 0);
            break;
    }

    ApplyAnimEffectToOpponent(sActivePokemon[0], 0, 0);
    ApplyAnimEffectToOpponent(sActivePokemon[1], 0, 0);
    Battle_InitCamera();
    Battle_SetEntityPosition(sActivePokemon[0]);
    Battle_SetEntityPosition(sActivePokemon[1]);
    SetTeamScoresFromActivePokemons();
    SetPlayerSidesFromActivePokemons();
}

void SetEntityOrientation(unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1, s32 arg2) {
    Vec3f_Set(&arg1->unk_448, 0.0f, 0.0f, 0.0f);
    Vec3f_Set(&arg1->unk_448.unk_0C, 0.0f, 0.0f, 0.0f);
    arg1->unk_4B0 = arg2;
}

void InitMessageBanksAndAnimQueue(unk_D_800AE540_1194* arg0) {
    s32 i;

    MessageBank_Init();

    gMessageBank_0x1E = GetMessageBank(0x1E);
    gMessageBank_0x24 = GetMessageBank(0x24);
    gPokemonMessageBank = GetMessageBank(0x25);
    gMessageBank_0x29 = GetMessageBank(0x29);
    gMarqueeMessageBank = GetMessageBank(0x14);

    for (i = 0; i < 7; i++) {
        gAnimStateQueue[i].unk_04 = gAnimStateIdle;
    }

    SetEntityOrientation(sActivePokemon[0], sActivePokemon[0], 1);
    SetEntityOrientation(sActivePokemon[1], sActivePokemon[1], -1);
    InitializeBattleScene(arg0);
    Battle_InitLighting();
    ResetAllStatFlags(sActivePokemon[0]);
    ResetAllStatFlags(sActivePokemon[1]);
    Dialog_Clear();
}

void ResetEntityAnimStates(unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1) {
    Battle_ResetEntityAnim(sActivePokemon[0], sActivePokemon[0]);
    Battle_ResetEntityAnim(sActivePokemon[1], sActivePokemon[1]);
    Battle_ClearAnimFlags(0);
    Battle_ClearAnimFlags(1);
    MaybeTriggerSpecialAnimEffect(sActivePokemon[0]);
    MaybeTriggerSpecialAnimEffect(sActivePokemon[1]);
}

s32 BattleInitDispatch(s32 arg0, unk_D_800AE540_1194* arg1) {
    switch (arg0) {
        case 0:
            InitializeBattleEntities(arg1);
            break;

        case 1:
        case 2:
            ResetEntityAnimStates(sActivePokemon[0], sActivePokemon[1]);
            break;

        case 3:
            InitMessageBanksAndAnimQueue(arg1);
            break;

        case 5:
            Battle_InitBattleEffects();
            break;
    }

    return 0;
}

void AnimHandler_Idle(unk_BattlePlayerEntity* arg0) {
}

void AnimHandler_AttackStart(unk_BattlePlayerEntity* arg0) {
}

void AnimHandler_AttackHit(unk_BattlePlayerEntity* arg0) {
}

void AnimHandler_AttackEnd(unk_BattlePlayerEntity* arg0) {
}

void AnimHandler_DamageStart(unk_BattlePlayerEntity* arg0) {
}

void AnimHandler_DamageHit(unk_BattlePlayerEntity* arg0) {
}

void AnimHandler_DamageEnd(unk_BattlePlayerEntity* arg0) {
}

void AnimHandler_FaintStart(unk_BattlePlayerEntity* arg0) {
}

void AnimHandler_FaintEnd(unk_BattlePlayerEntity* arg0) {
}

void AnimHandler_StatusEffect(unk_BattlePlayerEntity* arg0) {
}

void AnimHandler_ItemUse(unk_BattlePlayerEntity* arg0) {
}

void AnimHandler_SwitchIn(unk_BattlePlayerEntity* arg0) {
}

void AnimHandler_SwitchOut(unk_BattlePlayerEntity* arg0, s32 arg1) {
}

void AnimHandler_Victory(unk_BattlePlayerEntity* arg0, s32 arg1) {
}

void AnimHandler_Defeat(unk_BattlePlayerEntity* arg0) {
}
