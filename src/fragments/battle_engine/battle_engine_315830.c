#include "battle_engine.h"
#include "src/17300.h"
#include "src/18140.h"
#include "src/1C720.h"

void BattleAnim_StartFreezeStatusAnimation(BattlePlayerEntity* arg0) {
    UNUSED s32 pad[2];
    PokemonData* ptr;
    BattlePlayerAnimState* sp2C;
    PokemonAudioInfo* sp28;
    BattleAnimDataEntry* sp20;
    s32 idx = BattleScene_GetParticipantSideIndex(arg0);

    sp28 = &arg0->animationState.unk_38;
    sp2C = &arg0->animationState;
    ptr = &arg0->boundRoster->unk_01C[sp2C->unk_08];
    sp20 = &gAnimDataByPlayer[idx]->statusAnimChannel;

    if ((ptr->unk_05 & 0x20) && (sp2C->unk_34 & 2)) {
        arg0->unk_000.unk_000.posY &= ~0x20;
    }

    if ((sp28->unk_15 & 0x20) && (ptr->unk_05 & 0x20) && !(sp2C->unk_34 & 2) &&
        ((arg0->unk_000.unk_040.unk_08 >> 0x10) >= 3)) {
        ModelAnim_SetAnimation(&arg0->unk_000, sp20->posX);
        ModelAnim_SetFrame(&arg0->unk_000, 4);
        ModelAnim_SetEventTrack(&arg0->unk_000, sp20->unk_01);
        ModelAnim_SetEventFrame(&arg0->unk_000, 3);
        arg0->unk_000.unk_000.posY &= ~0x20;
        Battle_SetRuntimeFlags(arg0, 2);
        BattleAnim_QueueEffectList(1, arg0);
        BattleAnim_PlayBattleSequenceById(arg0, 0x13);
    }
}

void BattleAnim_RestoreBaseModelAnimation(BattlePlayerEntity* arg0) {
    BattleAnimDataEntry* ptr = &gAnimDataByPlayer[BattleScene_GetParticipantSideIndex(arg0)]->idleAnimChannel;

    ModelAnim_SetAnimation(&arg0->unk_000, ptr->posX);
}

void BattleAnim_ClearFreezeStatusAnimation(BattlePlayerEntity* arg0) {
    if (arg0->animationState.unk_34 & 2) {
        BattleAnim_StopOwnerCategoryParticles(1, arg0);
        arg0->unk_000.unk_000.posY |= 0x20;
        Battle_ClearRuntimeFlags(arg0, 2);
        BattleAnim_RestoreBaseModelAnimation(arg0);
    }
}

void BattleAnim_ResetFreezeStatusAndRestoreAnimation(BattlePlayerEntity* arg0) {
    PokemonData* ptr = &arg0->boundRoster->unk_01C[arg0->animationState.unk_08];

    if (arg0->animationState.unk_34 & 2) {
        ptr->unk_05 = 0;
        BattleAnim_StopOwnerCategoryParticles(1, arg0);
        arg0->unk_000.unk_000.posY |= 0x20;
        Battle_ClearRuntimeFlags(arg0, 2);
        BattleAnim_RestoreBaseModelAnimation(arg0);
    }
}

void BattleAnim_ClearFreezeStatusAnimationIfThawed(BattlePlayerEntity* arg0) {
    if ((arg0->animationState.unk_34 & 2) && !(arg0->animationState.unk_38.unk_15 & 0x20)) {
        BattleAnim_StopOwnerCategoryParticles(1, arg0);
        arg0->unk_000.unk_000.posY |= 0x20;
        Battle_ClearRuntimeFlags(arg0, 2);
        BattleAnim_RestoreBaseModelAnimation(arg0);
    }
}

void BattleAnim_UpdateSleepStatusAnimation(BattlePlayerEntity* arg0) {
    BattlePlayerAnimState* sp24 = &arg0->animationState;
    PokemonAudioInfo* sp28 = &sp24->unk_38;
    PokemonData* sp2C = &arg0->boundRoster->unk_01C[arg0->animationState.unk_08];

    if ((gBattleScene.posX->unk_38 != 0xB) || (gBattleScene.posX->unk_20 >= 6)) {
        if ((sp2C->unk_05 & 7) && (sp28->unk_15 & 7) && !(arg0->animationState.unk_34 & 1)) {
            BattleAnim_SetModelEventTrackAndState(arg0, 0xAF, 2);
            BattleAnim_QueueEffectList(3, arg0);
            BattleAnim_PlayBattleSequenceById(arg0, 0x32);
            Battle_SetRuntimeFlags(arg0, 1);
        }

        if (!(sp2C->unk_05 & 7) && (sp24->unk_34 & 1)) {
            if (gAnimDataByPlayer[BattleScene_GetParticipantSideIndex(arg0)]->unk_B81 == 0xFF) {
                sp24->unk_36 = 0;
                BattleAnim_SetModelEventTrackFromRow(arg0, 0xA5);
            } else {
                BattleAnim_SetModelEventTrackAndState(arg0, 0xB8, 1);
            }
            BattleAnim_StopOwnerCategoryParticles(3, arg0);
            Battle_ClearRuntimeFlags(arg0, 1);
        }
    }
}

void BattleAnim_EndSleepStatusAnimation(BattlePlayerEntity* arg0) {
    PokemonData* ptr = &arg0->boundRoster->unk_01C[arg0->animationState.unk_08];

    if (arg0->animationState.unk_34 & 1) {
        ptr->unk_05 = 0;
        if (gAnimDataByPlayer[BattleScene_GetParticipantSideIndex(arg0)]->unk_B81 == 0xFF) {
            arg0->animationState.unk_36 = 0;
            BattleAnim_SetModelEventTrackFromRow(arg0, 0xA5);
        } else {
            BattleAnim_SetModelEventTrackAndState(arg0, 0xB8, 1);
        }
        BattleAnim_StopOwnerCategoryParticles(3, arg0);
        Battle_ClearRuntimeFlags(arg0, 1);
    }
}

void BattleAnim_ClearSleepStatusAnimation(BattlePlayerEntity* arg0) {
    if (arg0->animationState.unk_34 & 1) {
        BattleAnim_StopOwnerCategoryParticles(3, arg0);
        Battle_ClearRuntimeFlags(arg0, 1);
    }
}
