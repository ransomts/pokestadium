#include "fragment62.h"
#include "src/17300.h"
#include "src/18140.h"
#include "src/1C720.h"

void HandleMoveHitAnimation(unk_BattlePlayerEntity* arg0) {
    UNUSED s32 pad[2];
    PokemonData* ptr;
    unk_BattlePlayerAnimState* sp2C;
    unk_D_800FCB18* sp28;
    unk_BattleAnimDataEntry* sp20;
    s32 idx = IsPrimaryEntity(arg0);

    sp28 = &arg0->unk_654.unk_38;
    sp2C = &arg0->unk_654;
    ptr = &arg0->unk_724->unk_01C[sp2C->unk_08];
    sp20 = &gAnimDataByPlayer[idx]->unk_A80;

    if ((ptr->unk_05 & 0x20) && (sp2C->unk_34 & 2)) {
        arg0->unk_000.unk_000.unk_02 &= ~0x20;
    }

    if ((sp28->unk_15 & 0x20) && (ptr->unk_05 & 0x20) && !(sp2C->unk_34 & 2) &&
        ((arg0->unk_000.unk_040.unk_08 >> 0x10) >= 3)) {
        GraphNode_TriggerAction(&arg0->unk_000, sp20->unk_00);
        Anim_SetChannelBase(&arg0->unk_000, 4);
        GraphNode_TriggerSound(&arg0->unk_000, sp20->unk_01);
        SetAnimStateIndex(&arg0->unk_000, 3);
        arg0->unk_000.unk_000.unk_02 &= ~0x20;
        SetEntityAnimFlags(arg0, 2);
        Battle_ApplyAnimChannelEffect(1, arg0);
        PlayBattleSoundEffect(arg0, 0x13);
    }
}

void TriggerCurrentAnimAction(unk_BattlePlayerEntity* arg0) {
    unk_BattleAnimDataEntry* ptr = &gAnimDataByPlayer[IsPrimaryEntity(arg0)]->unk_A50;

    GraphNode_TriggerAction(&arg0->unk_000, ptr->unk_00);
}

void StartMoveAnimation(unk_BattlePlayerEntity* arg0) {
    if (arg0->unk_654.unk_34 & 2) {
        RunParticleEffectScript(1, arg0);
        arg0->unk_000.unk_000.unk_02 |= 0x20;
        ClearEntityAnimFlags(arg0, 2);
        TriggerCurrentAnimAction(arg0);
    }
}

void ResetMoveStateAndStartAnimation(unk_BattlePlayerEntity* arg0) {
    PokemonData* ptr = &arg0->unk_724->unk_01C[arg0->unk_654.unk_08];

    if (arg0->unk_654.unk_34 & 2) {
        ptr->unk_05 = 0;
        RunParticleEffectScript(1, arg0);
        arg0->unk_000.unk_000.unk_02 |= 0x20;
        ClearEntityAnimFlags(arg0, 2);
        TriggerCurrentAnimAction(arg0);
    }
}

void ResumeMoveAnimationIfNotTriggered(unk_BattlePlayerEntity* arg0) {
    if ((arg0->unk_654.unk_34 & 2) && !(arg0->unk_654.unk_38.unk_15 & 0x20)) {
        RunParticleEffectScript(1, arg0);
        arg0->unk_000.unk_000.unk_02 |= 0x20;
        ClearEntityAnimFlags(arg0, 2);
        TriggerCurrentAnimAction(arg0);
    }
}

void HandleItemOrStatusEffect(unk_BattlePlayerEntity* arg0) {
    unk_BattlePlayerAnimState* sp24 = &arg0->unk_654;
    unk_D_800FCB18* sp28 = &sp24->unk_38;
    PokemonData* sp2C = &arg0->unk_724->unk_01C[arg0->unk_654.unk_08];

    if ((gBattleState.unk_00->unk_38 != 0xB) || (gBattleState.unk_00->unk_20 >= 6)) {
        if ((sp2C->unk_05 & 7) && (sp28->unk_15 & 7) && !(arg0->unk_654.unk_34 & 1)) {
            PlayAnimSoundSimple(arg0, 0xAF, 2);
            Battle_ApplyAnimChannelEffect(3, arg0);
            PlayBattleSoundEffect(arg0, 0x32);
            SetEntityAnimFlags(arg0, 1);
        }

        if (!(sp2C->unk_05 & 7) && (sp24->unk_34 & 1)) {
            if (gAnimDataByPlayer[IsPrimaryEntity(arg0)]->unk_B81 == 0xFF) {
                sp24->unk_36 = 0;
                PlayAnimSoundIfApplicable(arg0, 0xA5);
            } else {
                PlayAnimSoundSimple(arg0, 0xB8, 1);
            }
            RunParticleEffectScript(3, arg0);
            ClearEntityAnimFlags(arg0, 1);
        }
    }
}

void ProcessStatusEffectEnd(unk_BattlePlayerEntity* arg0) {
    PokemonData* ptr = &arg0->unk_724->unk_01C[arg0->unk_654.unk_08];

    if (arg0->unk_654.unk_34 & 1) {
        ptr->unk_05 = 0;
        if (gAnimDataByPlayer[IsPrimaryEntity(arg0)]->unk_B81 == 0xFF) {
            arg0->unk_654.unk_36 = 0;
            PlayAnimSoundIfApplicable(arg0, 0xA5);
        } else {
            PlayAnimSoundSimple(arg0, 0xB8, 1);
        }
        RunParticleEffectScript(3, arg0);
        ClearEntityAnimFlags(arg0, 1);
    }
}

void FinalizeStatusEffect(unk_BattlePlayerEntity* arg0) {
    if (arg0->unk_654.unk_34 & 1) {
        RunParticleEffectScript(3, arg0);
        ClearEntityAnimFlags(arg0, 1);
    }
}
