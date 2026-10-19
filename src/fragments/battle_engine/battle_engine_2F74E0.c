#include "battle_engine.h"
#include "src/373A0.h"
#include "src/3D140.h"
#include "src/49790.h"
#include "src/4BDC0.h"

static f32 gBattleTimer;
f32 gHPBarTimer;
f32 gPhaseTimer;
static f32 gBattlePhaseTimerMax;
static f32 gPhaseTimerInitial;
u8 gBattleResultPhase;
static s32 gRandomMoveSlot;
static s32 gRandomMoveSelectedFlag;
static s32 pad_D_84390140;
static u16 gBattleControllerId;
static Controller* gActiveController1;
static Controller* gActiveController2;
static Controller gDemoController;
s32 gBattleInitFlag;
unk_D_84390178 gBattleInitStruct;

static u8 D_84385750[] = {
    0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80,
};

void BattleScene_InitializePresentationTimers(void) {
    gBattlePhaseTimerMax = gSessionContext.unk_11EF * 0x1E;
    gPhaseTimerInitial = gSessionContext.unk_11EE * 0x708;
    gPhaseTimer = gSessionContext.unk_11EE * 0x708;
}

void BattleScene_QuantizePresentationTimer(void) {
    s32 tmp = (s32)(gPhaseTimer / 30.0f) * 0x1E;

    gPhaseTimer = tmp;
}

s32 BattleScene_TickPresentationTimer(void) {
    if (gPhaseTimer == 0.0f) {
        return 1;
    }

    gPhaseTimer -= 1.0f;
    return 0;
}

s32 BattleScene_IsPresentationCountdownComplete(void) {
    if (gSessionContext.unk_11ED == 0) {
        return 0;
    }

    if ((((s32)gPhaseTimer % 30) == 0) && (gPhaseTimer != 0.0f)) {
        Audio_PlayCommand(0x3E, 0, 0);
    }

    if (gPhaseTimer == 0.0f) {
        return 1;
    }
    return 0;
}

s32 Battle_ClassifyHpTier(s32 arg0, s32 arg1) {
    s32 temp_v0 = arg0 * 0x30;

    if (temp_v0 < (arg1 * 0xA)) {
        return 1;
    }

    if (temp_v0 < (arg1 * 0x1B)) {
        return 2;
    }

    return 3;
}

s32 BattleScene_DetermineWinner(void) {
    PokemonData* ptr;
    s32 i;
    s32 var_s3 = 0;
    s32 var_s4 = 0;
    s32 var_s5 = 0;
    s32 var_s6 = 0;

    for (i = 0; i < BattleScene_GetSelectedSideTeamSize(sActivePokemon[0]); i++) {
        ptr = &sActivePokemon[0]->unk_724->unk_01C[i];
        if (ptr->posY != 0) {
            var_s3++;
        }
    }

    for (i = 0; i < BattleScene_GetSelectedSideTeamSize(sActivePokemon[1]); i++) {
        ptr = &sActivePokemon[1]->unk_724->unk_01C[i];
        if (ptr->posY != 0) {
            var_s4++;
        }
    }

    if (var_s3 != var_s4) {
        if (var_s4 < var_s3) {
            return 1;
        }
        return 2;
    }

    for (i = 0; i < BattleScene_GetSelectedSideTeamSize(sActivePokemon[0]); i++) {
        ptr = &sActivePokemon[0]->unk_724->unk_01C[i];
        var_s5 += Battle_ClassifyHpTier(ptr->posY, ptr->unk_26);
    }

    for (i = 0; i < BattleScene_GetSelectedSideTeamSize(sActivePokemon[1]); i++) {
        ptr = &sActivePokemon[1]->unk_724->unk_01C[i];
        var_s6 += Battle_ClassifyHpTier(ptr->posY, ptr->unk_26);
    }

    if (var_s5 == var_s6) {
        return 3;
    }

    if (var_s6 < var_s5) {
        return 1;
    }

    if (var_s5 < var_s6) {
        return 2;
    }
}

s32 BattleScene_UpdateResultPresentation(void) {
    s32 sp1C = 0;
    s32 var_v0;

    if (gSessionContext.unk_11ED == 0) {
        return 0;
    }

    if (BattleScene_IsPresentationCountdownComplete() != 0) {
        switch (gBattleResultPhase) {
            case 1:
                BattleBox_Open(0xD);
                gBattleResultPhase = 2;
                Audio_PlayCommand(0x3F, 0, 0);
                Audio_StartResultMusicSequence();
                sp1C = 1;
                break;

            case 2:
                sp1C = 1;

                var_v0 = 0;
                if (gBattleTimer >= 120.0f) {
                    var_v0 = 1;
                }

                gBattleTimer += 1.0f;

                if (var_v0 != 0) {
                    gBattleScene.posX->unk_40 = BattleScene_DetermineWinner();
                    Audio_FadeOutAll(0x14);
                }
                break;
        }
    }
    return sp1C;
}

s32 BattleScene_IsActionSelectionTimerExpired(void) {
    if (gSessionContext.unk_11ED == 0) {
        return 0;
    }

    if (gHPBarTimer == 329.0f) {
        Audio_PlayCommand(0x3C, 0, 0);
    }

    if (gHPBarTimer == 91.0f) {
        Audio_PlayCommand(0x3D, 3, 0);
    }

    if (gHPBarTimer == 61.0f) {
        Audio_PlayCommand(0x3D, 2, 0);
    }

    if (gHPBarTimer == 31.0f) {
        Audio_PlayCommand(0x3D, 1, 0);
    }

    if (gHPBarTimer == 1.0f) {
        Audio_PlayCommand(0x3D, 0, 0);
    }

    if (gHPBarTimer == 0.0f) {
        return 1;
    }
    return 0;
}

void BattleScene_ResetActionSelectionTimer(void) {
    gHPBarTimer = gSessionContext.unk_11EF * 0x1E;
}

s32 BattleScene_TickActionSelectionTimers(void) {
    if (gHPBarTimer > 0.0f) {
        gHPBarTimer -= 1.0f;
    }

    if (gBattleTimer >= 150.0f) {
        return 1;
    }

    gBattleTimer += 1.0f;
    return 0;
}

void BattleScene_ResetActionSelectionTimers(void) {
    gBattleTimer = 0.0f;
    BattleScene_ResetActionSelectionTimer();
}

s32 BattleScene_ApplyForcedActionDelay(unk_BattlePlayerEntity* arg0) {
    unk_BattlePlayerAnimState* temp_v1 = &arg0->animationState;

    if (arg0->animationState.unk_10 == 3) {
        temp_v1->unk_1E += 0x38E;
        return 1;
    }
    return 0;
}

void BattleScene_SyncActiveHpToPartyState(void) {
    PokemonAudioInfo* temp_a2;
    PokemonAudioInfo* temp_a3;
    unk_BattlePlayerAnimState* ptr1;
    unk_BattlePlayerAnimState* ptr2;
    PokemonData* ptr3;
    PokemonData* ptr4;

    ptr1 = &sActivePokemon[0]->animationState;
    ptr2 = &sActivePokemon[1]->animationState;
    temp_a2 = &sActivePokemon[0]->animationState.unk_38;
    temp_a3 = &sActivePokemon[1]->animationState.unk_38;

    ptr3 = &sActivePokemon[0]->unk_724->unk_01C[ptr1->unk_08];
    ptr4 = &sActivePokemon[1]->unk_724->unk_01C[ptr2->unk_08];

    if (gBattleUpdateHPFlag != 0) {
        gPlayerScaleFactors[0] = temp_a2->unk_0C = temp_a2->unk_28;
        gPlayerScaleFactors[1] = temp_a3->unk_0C = temp_a3->unk_28;

        ptr3->posY = temp_a2->unk_28;
        ptr4->posY = temp_a3->unk_28;
    }
}

s32 BattleScene_SelectFallbackWhenNoUsableMoves(unk_BattlePlayerEntity* arg0) {
    s32 i;
    s32 var_v1;
    unk_BattlePlayerAnimState* temp_v1;
    PokemonAudioInfo* temp_v0;

    temp_v1 = &arg0->animationState;
    temp_v0 = &arg0->animationState.unk_38;
    var_v1 = 0;

    if (arg0->animationState.unk_38.unk_52 != 0) {
        for (i = 0; i < 4; i++) {
            if (((temp_v0->unk_52 >> 4) != i) && (temp_v0->unk_1F[i] != 0)) {
                var_v1 |= temp_v0->unk_32[i] & 0x3F;
            }
        }
    } else {
        for (i = 0; i < 4; i++) {
            if (temp_v0->unk_1F[i] != 0) {
                var_v1 |= temp_v0->unk_32[i] & 0x3F;
            }
        }
    }

    if (var_v1 == 0) {
        temp_v1->unk_1E = 0;
        temp_v1->unk_10 = 3;
        temp_v1->unk_14 = 4;
        return 1;
    }
    return 0;
}

s32 BattleScene_IsMoveUnavailable(unk_BattlePlayerEntity* arg0, s32 arg1) {
    PokemonAudioInfo* ptr = &arg0->animationState.unk_38;

    if (!(ptr->unk_32[arg1] & 0x3F)) {
        return 1;
    }

    if ((ptr->unk_52 & 0xF) && (arg1 == (ptr->unk_52 >> 4))) {
        return 1;
    }

    return 0;
}

void BattleScene_AutoSelectAvailableMove(unk_BattlePlayerEntity* arg0) {
    s32 i;
    unk_BattlePlayerAnimState* temp_v0 = &arg0->animationState;

    if (BattleScene_SelectFallbackWhenNoUsableMoves(arg0) == 0) {
        for (i = 0; i < 4; i++) {
            if (BattleScene_IsMoveUnavailable(arg0, i) == 0) {
                temp_v0->rotation = 1;
                temp_v0->unk_10 = 3;
                temp_v0->unk_14 = i;
                temp_v0->unk_0C = i;
                break;
            }
        }
    }
}

void BattleScene_AutoSelectReplacementMon(unk_BattlePlayerEntity* arg0) {
    s32 i;
    unk_BattlePlayerAnimState* sp1C = &arg0->animationState;

    for (i = 0; i < arg0->pokemonAnimation->unk_08[0]->unk_002; i++) {
        if ((arg0->pokemonAnimation->unk_08[0]->unk_01C[i].posY != 0) && (i != sp1C->unk_08)) {
            BattleAnim_PlaySoundEffect2();
            sp1C->unk_1C = 0;
            sp1C->unk_1E = 0;
            sp1C->unk_10 = 3;
            sp1C->unk_18 = i;
            return;
        }
    }

    BattleScene_AutoSelectAvailableMove(arg0);
}

void BattleScene_SelectActiveController(unk_BattlePlayerEntity* arg0) {
    unk_BattlePlayerAnimState* ptr = &arg0->animationState;

    ptr->unk_2C = ptr->unk_2B;
    ptr->controller = &gControllers[arg0->pokemonAnimation->unk_08[ptr->unk_2C]->unk_001];
}

void BattleScene_HandleActionSelectionCancel(s32 arg0) {
    unk_BattlePlayerAnimState* sp2C;
    unk_BattlePlayerAnimState* sp28;
    UNUSED s32 pad;
    Controller* cont;

    sp2C = &sActivePokemon[arg0]->animationState;
    sp28 = &sActivePokemon[arg0 == 0]->animationState;
    cont = sp2C->controller;

    if ((sp2C->unk_10 != 3) || !(cont->buttonPressed & 0x20)) {
        return;
    }

    if (sp2C->unk_2D == 0x10) {
        if (sp2C->rotation == 2) {
            BattleScene_SelectActiveController(sActivePokemon[arg0]);
        }
        BattleAnim_PlaySoundEffect3();
        sp2C->unk_10 = 2;
    }

    if (sp28->unk_2D != 0x10) {
        if (sp2C->rotation == 2) {
            BattleScene_SelectActiveController(sActivePokemon[arg0]);
        }
        BattleAnim_PlaySoundEffect3();
        sp2C->unk_10 = 0;
    }
}

void Battle_InitializeActiveRuntimeState(void) {
    BattleScene_InitializePresentationTimers();
    func_84370B7C(sActivePokemon[0]);
    func_84370B7C(sActivePokemon[1]);

    gPlayerScaleFactors[0] = sActivePokemon[0]->animationState.unk_38.unk_0C;
    gPlayerScaleFactors[1] = sActivePokemon[1]->animationState.unk_38.unk_0C;

    Battle_ResetTransientRuntimeState(0, 1);
    Battle_ResetTransientRuntimeState(1, 0);
}

s32 BattleScene_CpuHasNoUsableMoves(unk_BattlePlayerEntity* arg0) {
    PokemonAudioInfo* temp_v0 = &arg0->animationState.unk_38;
    s32 i;
    s32 var_v1 = 0;

    if (temp_v0->unk_52 != 0) {
        for (i = 0; i < 4; i++) {
            if (((temp_v0->unk_52 >> 4) != i) && (temp_v0->unk_1F[i] != 0)) {
                var_v1 |= temp_v0->unk_32[i] & 0x3F;
            }
        }
    } else {
        for (i = 0; i < 4; i++) {
            if (temp_v0->unk_1F[i] != 0) {
                var_v1 |= temp_v0->unk_32[i] & 0x3F;
            }
        }
    }

    if (var_v1 == 0) {
        return 1;
    }
    return 0;
}

s32 BattleScene_WaitForCpuChoice(unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1) {
    UNUSED s32 pad[2];
    unk_BattlePlayerAnimState* sp1C = &arg0->animationState;
    unk_BattlePlayerAnimState* temp_v0 = &arg1->animationState;

    if ((arg0->animationState.unk_2D == 0x10) && (arg1->animationState.unk_2D == 0x10)) {
        if (sp1C->unk_10 == 3) {
            BattleScene_ApplyForcedActionDelay(arg0);
            return 1;
        }

        sp1C->rotation = 2;
        sp1C->unk_10 = 2;

        if (gBattleTimer == 20.0f) {
            BattleAnim_PlaySoundEffect2();
            gRandomMoveSlot = BattleAI_ChooseAction(0);
            sp1C->unk_1C = 0;
            sp1C->unk_18 = gRandomMoveSlot - 4;
            sp1C->unk_1E = 0;
            sp1C->unk_10 = 3;
            sp1C->rotation = 2;
        }
        return 1;
    }

    if (sp1C->unk_2D == 0x10) {
        sp1C->rotation = 2;
        sp1C->unk_10 = 2;
        temp_v0->unk_10 = 3;
        temp_v0->rotation = 1;

        if (gBattleTimer == 20.0f) {
            BattleAnim_PlaySoundEffect2();
            gRandomMoveSlot = BattleAI_ChooseAction(0);
            sp1C->unk_1C = 0;
            sp1C->unk_18 = gRandomMoveSlot - 4;
            sp1C->unk_1E = 0;
            sp1C->unk_10 = 3;
            sp1C->rotation = 2;
        }
        return 1;
    }

    return 0;
}

void BattleScene_CompleteCpuForcedAction(unk_BattlePlayerEntity* arg0, UNUSED unk_BattlePlayerEntity* arg1) {
    unk_BattlePlayerAnimState* ptr = &arg0->animationState;

    BattleScene_ApplyForcedActionDelay(arg0);
    ptr->unk_2A = 1;
    ptr->rotation = 1;
    ptr->unk_0C = ptr->unk_14;
    ptr->unk_10 = 3;
}

void BattleScene_CompleteCpuMoveAction(unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1) {
    unk_BattlePlayerAnimState* sp20 = &arg1->animationState;
    unk_BattlePlayerAnimState* sp1C = &arg0->animationState;

    BattleScene_ApplyForcedActionDelay(arg0);
    sp1C->unk_2A = 1;

    if ((gBattleTimer == 30.0f) && (gRandomMoveSlot < 4)) {
        BattleAnim_PlaySoundEffect2();
    }

    if ((gRandomMoveSlot < 4) && (gBattleTimer >= 30.0f)) {
        sp1C->unk_10 = 1;
        sp1C->rotation = 1;
    }

    if (((gBattleTimer >= 90.0f) || ((sp20->unk_10 == 3) && (gBattleTimer >= 10.0f))) && (gRandomMoveSlot < 4)) {
        BattleAnim_PlaySoundEffect2();
        sp1C->rotation = 1;
        sp1C->unk_10 = 3;
        sp1C->unk_0C = sp1C->unk_14;
    }
}

void BattleScene_ApplyCpuChoice(unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1) {
    unk_BattlePlayerAnimState* sp18;
    unk_BattlePlayerAnimState* sp14;
    s32 var_v0;

    sp18 = &arg0->animationState;
    sp14 = &arg1->animationState;

    if ((gBattleTimer == 30.0f) && (gRandomMoveSlot < 4)) {
        BattleAnim_PlaySoundEffect2();
    }

    if (gRandomMoveSlot < 4) {
        if (gBattleTimer >= 30.0f) {
            sp18->unk_10 = 1;
            sp18->rotation = 1;
        }
    }

    if ((gBattleTimer >= 90.0f) || ((sp14->unk_10 == 3) && (gBattleTimer >= 10.0f))) {
        if (gRandomMoveSlot < 4) {
            BattleAnim_PlaySoundEffect2();
            sp18->rotation = 1;
            sp18->unk_10 = 3;
            if (BattleScene_CpuHasNoUsableMoves(arg0) != 0) {
                sp18->unk_14 = 4;
                sp18->unk_0C = 4;
            } else {
                var_v0 = gRandomMoveSlot;
                sp18->unk_14 = var_v0;
                sp18->unk_0C = var_v0;
            }
        }
    }
}

s32 BattleScene_ApplyCpuSwitchChoice(unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1) {
    unk_BattlePlayerAnimState* sp1C = &arg0->animationState;
    unk_BattlePlayerAnimState* sp18 = &arg1->animationState;

    if ((gBattleTimer == 30.0f) && (gRandomMoveSlot >= 4)) {
        BattleAnim_PlaySoundEffect2();
    }

    if (gBattleTimer >= 30.0f) {
        if (gRandomMoveSlot >= 4) {
            sp1C->unk_10 = 2;
            sp1C->rotation = 2;
        }
    }

    if ((gBattleTimer >= 90.0f) || ((sp18->unk_10 == 3) && (gBattleTimer >= 10.0f))) {
        if (gRandomMoveSlot >= 4) {
            BattleAnim_PlaySoundEffect2();
            sp1C->unk_1C = 0;
            sp1C->unk_18 = gRandomMoveSlot - 4;
            sp1C->unk_1E = 0;
            sp1C->unk_10 = 3;
            sp1C->rotation = 2;
        }
    }

    if (gRandomMoveSlot >= 4) {
        return 1;
    }
    return 0;
}

void BattleScene_TriggerCpuChoice(UNUSED PokemonAudioInfo* arg0, UNUSED PokemonAudioInfo* arg1, UNUSED unk_BattlePlayerAnimState* arg2,
                   UNUSED unk_BattlePlayerAnimState* arg3, UNUSED unk_BattlePlayerEntity* arg4) {
    if ((gBattleTimer == 1.0f) && (gRandomMoveSelectedFlag == 0)) {
        gRandomMoveSelectedFlag = 1;
        gRandomMoveSlot = BattleAI_ChooseAction(0);
    }
}

s32 BattleScene_CollectCpuAction(unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1) {
    PokemonAudioInfo* sp34 = &arg0->animationState.unk_38;
    PokemonAudioInfo* sp30 = &arg1->animationState.unk_38;
    unk_BattlePlayerAnimState* sp2C = &arg0->animationState;
    unk_BattlePlayerAnimState* sp28 = &arg1->animationState;

    if (BattleScene_WaitForCpuChoice(arg0, arg1) != 0) {
        return 0;
    }

    if (!(sp34->unk_4D & 0x60)) {
        sp34->unk_4C &= ~8;
        sp30->unk_4C &= ~8;

        if (!(sp34->unk_4C & 0x12)) {
            if (BattleScene_ApplyForcedActionDelay(arg0) != 0) {
                return 0;
            }

            if (gBattleTimer == 0.0f) {
                gRandomMoveSelectedFlag = 0;
                return 0;
            }

            BattleScene_TriggerCpuChoice(sp34, sp30, sp2C, sp28, arg1);

            if (BattleScene_ApplyCpuSwitchChoice(arg0, arg1) != 0) {
                return 0;
            }

            if (!(sp34->unk_15 & 0x27)) {
                if (!(sp34->unk_4C & 0x21)) {
                    if (sp30->unk_4C & 0x20) {
                        BattleScene_CompleteCpuMoveAction(arg0, arg1);
                        sp34->unk_5A = 0xFF;
                    } else if (BattleScene_ApplyForcedActionDelay(arg0) != 0) {
                        return 0;
                    } else {
                        if (gBattleTimer == 0.0f) {
                            gRandomMoveSelectedFlag = 0;
                            return 0;
                        }
                        BattleScene_TriggerCpuChoice(sp34, sp30, sp2C, sp28, arg1);
                        BattleScene_ApplyCpuChoice(arg0, arg1);
                    }
                } else {
                    BattleScene_CompleteCpuMoveAction(arg0, arg1);
                }
            } else {
                BattleScene_CompleteCpuMoveAction(arg0, arg1);
            }
        } else {
            BattleScene_CompleteCpuForcedAction(arg0, arg1);
        }
    } else {
        BattleScene_CompleteCpuForcedAction(arg0, arg1);
    }

    return 0;
}

void BattleScene_ForfeitPrompt(unk_BattlePlayerEntity* arg0) {
    unk_BattlePlayerAnimState* sp18 = &arg0->animationState;
    unk_BattlePlayerAnimState* temp_a0 = &sActivePokemon[BattleScene_GetParticipantSideIndex(arg0) == 0]->animationState;

    if (arg0->pokemonAnimation->unk_01 == 1) {
        gActiveController1 = &gControllers[arg0->pokemonAnimation->unk_08[0]->unk_001];
        gActiveController2 = &gControllers[arg0->pokemonAnimation->unk_08[0]->unk_001];
    } else {
        gActiveController1 = &gControllers[arg0->pokemonAnimation->unk_08[0]->unk_001];
        gActiveController2 = &gControllers[arg0->pokemonAnimation->unk_08[1]->unk_001];
    }

    if (temp_a0->unk_10 == 4) {
        sp18->unk_10 = 0;
        sp18->rotation = 0;
        return;
    }

    if (sp18->unk_10 != 4) {
        sp18->unk_2F = 0;
    }

    sp18->unk_10 = 4;

    if ((gBattleScene.posX->unk_40 == 0) &&
        (BTN_IS_PRESSED(gActiveController1, BTN_DLEFT) || BTN_IS_PRESSED(gActiveController2, BTN_DLEFT))) {
        sp18->unk_2F = 0;
        Audio_PlaySoundEffectById(1);
    }

    if ((gBattleScene.posX->unk_40 == 0) &&
        (BTN_IS_PRESSED(gActiveController1, BTN_DRIGHT) || BTN_IS_PRESSED(gActiveController2, BTN_DRIGHT))) {
        sp18->unk_2F = 1;
        Audio_PlaySoundEffectById(1);
    }

    if ((sp18->unk_2F == 1) && (BTN_IS_PRESSED(gActiveController1, BTN_A) || BTN_IS_PRESSED(gActiveController2, BTN_A)) &&
        (gBattleScene.posX->unk_40 == 0)) {
        Audio_PlaySoundEffectById(2);
        gBattleScene.posX->unk_40 = (BattleScene_GetParticipantSideIndex(arg0) == 0) + 1;
        Audio_FadeOutAll(0x14);
    } else if ((sp18->unk_2F == 0) && (BTN_IS_PRESSED(gActiveController1, BTN_A) || BTN_IS_PRESSED(gActiveController2, BTN_A))) {
        sp18->unk_10 = 0;
        sp18->rotation = 0;
        Audio_PlaySoundEffectById(3);
    }
}

void BattleScene_CommitPlayerSwitchAction(unk_BattlePlayerEntity* arg0) {
    unk_BattlePlayerAnimState* temp_v0 = &arg0->animationState;
    PokemonAudioInfo* temp_v1 = &sActivePokemon[BattleScene_GetParticipantSideIndex(arg0) == 0]->animationState.unk_38;

    if (temp_v1->unk_4C & 0x20) {
        arg0->animationState.unk_38.unk_5A = 0xFF;
    }

    if (temp_v0->unk_2D != 0x10) {
        temp_v0->unk_2D = 0xF;
    }

    temp_v0->unk_1C = 0;
    BattleScene_ClearParticipantMessageBuffer(arg0);
}

s32 BattleScene_ValidateSelectedPartyMember(unk_BattlePlayerEntity* arg0) {
    if (arg0->pokemonAnimation->unk_08[arg0->animationState.unk_2C]->unk_01C[arg0->animationState.unk_18].posY != 0) {
        return 1;
    }

    BattleScene_ClearParticipantMessageBuffer(arg0);
    BattleScene_BuildParticipantMessage(arg0, 3);
    BattleAnim_PlaySoundEffect8();
    return 0;
}

void BattleScene_QueuePartySelectionConfirmMessage(unk_BattlePlayerEntity* arg0) {
    BattleScene_ClearParticipantMessageBuffer(arg0);
    BattleScene_BuildParticipantMessage(arg0, 4);
}

void BattleScene_AssignActiveCoopController(unk_BattlePlayerEntity* arg0, s32 arg1) {
    if (arg1 == 1) {
        gActiveController1 = &gControllers[arg0->pokemonAnimation->unk_08[0]->unk_001];
        gActiveController2 = &gControllers[arg0->pokemonAnimation->unk_08[0]->unk_001];
    } else {
        gActiveController1 = &gControllers[arg0->pokemonAnimation->unk_08[0]->unk_001];
        gActiveController2 = &gControllers[arg0->pokemonAnimation->unk_08[1]->unk_001];
    }

    if (arg1 == 1) {
        if (BTN_IS_PRESSED(gActiveController1, BTN_A | BTN_B | BTN_CUP | BTN_CDOWN | BTN_CLEFT | BTN_CRIGHT)) {
            arg0->animationState.unk_2C = 0;
            BattleScene_SetParticipantController(arg0, gActiveController1);
        } else if (BTN_IS_PRESSED(gActiveController2, BTN_A | BTN_B | BTN_CUP | BTN_CDOWN | BTN_CLEFT | BTN_CRIGHT)) {
            BattleScene_SetParticipantController(arg0, gActiveController2);
            arg0->animationState.unk_2C = 0;
        }
    } else if (BTN_IS_PRESSED(gActiveController1, BTN_A | BTN_B | BTN_CUP | BTN_CDOWN | BTN_CLEFT | BTN_CRIGHT)) {
        BattleScene_SetParticipantController(arg0, gActiveController1);
        arg0->animationState.unk_2C = 0;
    } else if (BTN_IS_PRESSED(gActiveController2, BTN_A | BTN_B | BTN_CUP | BTN_CDOWN | BTN_CLEFT | BTN_CRIGHT)) {
        BattleScene_SetParticipantController(arg0, gActiveController2);
        arg0->animationState.unk_2C = 1;
    }
}

void BattleScene_HandlePartySlotCursorInput(unk_BattlePlayerEntity* arg0, Controller* arg1) {
    unk_BattlePlayerAnimState* sp1C;
    unk_D_800AE540_0004* temp_a1;

    sp1C = &arg0->animationState;

    BattleScene_AssignActiveCoopController(arg0, arg0->pokemonAnimation->unk_01);
    temp_a1 = arg0->pokemonAnimation->unk_08[sp1C->unk_2C];
    arg1 = sp1C->controller;

    if (temp_a1->unk_002 < 4) {
        if (BTN_IS_PRESSED(arg1, BTN_CUP)) {
            sp1C->unk_18 = 0;
        } else if (BTN_IS_PRESSED(arg1, BTN_CRIGHT)) {
            sp1C->unk_18 = 1;
        } else if (BTN_IS_PRESSED(arg1, BTN_CDOWN)) {
            sp1C->unk_18 = 2;
        } else {
            return;
        }
    } else {
        if (BTN_IS_PRESSED(arg1, BTN_CUP)) {
            sp1C->unk_18 = 0;
        }

        if (BTN_IS_PRESSED(arg1, BTN_CLEFT)) {
            sp1C->unk_18 = 1;
        }

        if (BTN_IS_PRESSED(arg1, BTN_B)) {
            sp1C->unk_18 = 2;
        }

        if (BTN_IS_PRESSED(arg1, BTN_CRIGHT)) {
            sp1C->unk_18 = 3;
        }

        if (BTN_IS_PRESSED(arg1, BTN_CDOWN)) {
            sp1C->unk_18 = 4;
        }

        if (BTN_IS_PRESSED(arg1, BTN_A)) {
            sp1C->unk_18 = 5;
        }
    }

    if (BTN_IS_PRESSED(arg1, BTN_A | BTN_B | BTN_CUP | BTN_CDOWN | BTN_CLEFT | BTN_CRIGHT)) {
        if ((sp1C->unk_08 == sp1C->unk_18) && (sp1C->unk_2C == sp1C->unk_2B)) {
            if (BattleScene_ValidateSelectedPartyMember(arg0) != 0) {
                BattleAnim_PlaySoundEffect8();
                BattleScene_QueuePartySelectionConfirmMessage(arg0);
            }
        } else if (((temp_a1->unk_002 - 1) >= sp1C->unk_18) && (BattleScene_ValidateSelectedPartyMember(arg0) != 0)) {
            BattleAnim_PlaySoundEffect2();
            sp1C->unk_1C = 0;
            sp1C->unk_1E = 0;
            sp1C->unk_10 = 3;
        }
    }
}

void BattleScene_HandlePlayerPartySelection(unk_BattlePlayerEntity* arg0) {
    UNUSED s32 pad;
    s32 idx;
    unk_BattlePlayerAnimState* sp18 = &arg0->animationState;

    if (arg0->pokemonAnimation->unk_01 == 1) {
        gActiveController1 = &gControllers[arg0->pokemonAnimation->unk_08[0]->unk_001];
        gActiveController2 = &gControllers[arg0->pokemonAnimation->unk_08[0]->unk_001];
    } else {

        gActiveController1 = &gControllers[arg0->pokemonAnimation->unk_08[sp18->unk_2C]->unk_001];
        idx = sp18->unk_2C == 0;
        gActiveController2 = &gControllers[arg0->pokemonAnimation->unk_08[idx]->unk_001];
    }

    if (arg0->unk_8C4.posX != 0) {
        if (sp18->controller->buttonPressed & 0xE03F) {
            BattleScene_ClearParticipantMessageBuffer(arg0);
        }
    } else if (sp18->unk_10 == 0) {
        sp18->unk_10 = 2;
    } else if (((gActiveController1->buttonPressed & 0x20) || (gActiveController2->buttonPressed & 0x20)) && (sp18->unk_2D != 0x10) &&
               !(gActiveController1->buttonDown & 0x10) && !(gActiveController2->buttonDown & 0x10)) {
        BattleScene_SelectActiveController(arg0);
        BattleAnim_PlaySoundEffect3();
        sp18->unk_10 = 0;
    } else {
        sp18->unk_1C = 0;
        if ((gActiveController1->buttonDown & 0x10) || (gActiveController2->buttonDown & 0x10)) {
            if ((gActiveController1->buttonPressed & 0x10) || (gActiveController2->buttonPressed & 0x10)) {
                BattleAnim_PlaySoundEffect1();
            }
            sp18->unk_1C = 1;
        }
        BattleScene_HandlePartySlotCursorInput(arg0, sp18->controller);
    }
}

void BattleScene_CommitSelectedMoveAction(unk_BattlePlayerEntity* arg0) {
    unk_BattlePlayerAnimState* temp_v0 = &arg0->animationState;
    PokemonAudioInfo* temp_v1 = &arg0->animationState.unk_38;

    if (arg0->animationState.unk_14 != 4) {
        temp_v0->unk_0C = temp_v0->unk_14;
        if (temp_v0->unk_2A == 0) {
            temp_v1->unk_5A = temp_v1->unk_1F[temp_v0->unk_0C];
        }
    } else {
        if (temp_v1->unk_4C & 0x20) {
            temp_v0->unk_0C = temp_v0->unk_14;
        } else {
            temp_v0->unk_14 = 0;
            temp_v0->unk_0C = 0;
            temp_v1->unk_5A = 0xA5;
        }
    }

    temp_v0->unk_1C = 0;
    BattleScene_ClearParticipantMessageBuffer(arg0);
}

s32 BattleScene_HandleNoUsableMoveSelection(unk_BattlePlayerEntity* arg0) {
    s32 i;
    s32 temp_a1;
    s32 var_v1;
    unk_BattlePlayerAnimState* temp_v0;
    PokemonAudioInfo* temp_a0;
    Controller* cont;

    temp_v0 = &arg0->animationState;
    temp_a0 = &arg0->animationState.unk_38;
    cont = arg0->animationState.controller;
    var_v1 = 0;

    if (temp_a0->unk_52 != 0) {
        temp_a1 = temp_a0->unk_52 >> 4;
        for (i = 0; i < 4; i++) {
            if ((temp_a1 != i) && (temp_a0->unk_1F[i] != 0)) {
                var_v1 |= temp_a0->unk_32[i] & 0x3F;
            }
        }
    } else {
        for (i = 0; i < 4; i++) {
            if (temp_a0->unk_1F[i] != 0) {
                var_v1 |= temp_a0->unk_32[i] & 0x3F;
            }
        }
    }

    if (var_v1 == 0) {
        if (arg0->unk_8C4.posX == 0) {
            if (temp_v0->unk_10 == 0) {
                temp_v0->unk_10 = 1;
            }
            BattleScene_ClearParticipantMessageBuffer(arg0);
            BattleScene_BuildParticipantMessage(arg0, 0);
        } else if (cont->buttonPressed & 0x20) {
            BattleScene_ClearParticipantMessageBuffer(arg0);
            temp_v0->unk_10 = 0;
            BattleAnim_PlaySoundEffect3();
        } else if (cont->buttonPressed & 0x8000) {
            BattleScene_ClearParticipantMessageBuffer(arg0);
            temp_v0->unk_1E = 0;
            temp_v0->unk_10 = 3;
            temp_v0->unk_14 = 4;
        }
        return 1;
    }
    return 0;
}

s32 BattleScene_ValidateSelectedMove(unk_BattlePlayerEntity* arg0) {
    UNUSED s32 pad[2];
    unk_BattlePlayerAnimState* sp24 = &arg0->animationState;
    PokemonAudioInfo* ptr = &arg0->animationState.unk_38;

    if (!(ptr->unk_32[sp24->unk_14] & 0x3F)) {
        BattleAnim_PlaySoundEffect8();
        BattleScene_ClearParticipantMessageBuffer(arg0);
        BattleScene_BuildParticipantMessage(arg0, 1);
        return 1;
    }

    if ((ptr->unk_52 & 0xF) && (sp24->unk_14 == (ptr->unk_52 >> 4))) {
        BattleAnim_PlaySoundEffect8();
        BattleScene_ClearParticipantMessageBuffer(arg0);
        BattleScene_BuildParticipantMessage(arg0, 2);
        return 1;
    }

    BattleAnim_PlaySoundEffect2();
    sp24->unk_1E = 0;
    sp24->unk_10 = 3;
    sp24->unk_1C = 0;
    return 0;
}

void BattleScene_SelectMoveFromButtons(unk_BattlePlayerEntity* arg0) {
    Controller* cont = arg0->animationState.controller;

    if ((cont->buttonPressed & 8) != 0) {
        if ((arg0->animationState.unk_38.unk_1F[0] != 0) && (arg0->animationState.unk_38.unk_1F[0] < 0xA6)) {
            arg0->animationState.unk_14 = 0;
            BattleScene_ValidateSelectedMove(arg0);
            return;
        }
    }

    if ((cont->buttonPressed & 1) != 0) {
        if ((arg0->animationState.unk_38.unk_1F[1] != 0) && (arg0->animationState.unk_38.unk_1F[1] < 0xA6)) {
            arg0->animationState.unk_14 = 1;
            BattleScene_ValidateSelectedMove(arg0);
            return;
        }
    }

    if ((cont->buttonPressed & 4) != 0) {
        if ((arg0->animationState.unk_38.unk_1F[2] != 0) && (arg0->animationState.unk_38.unk_1F[2] < 0xA6)) {
            arg0->animationState.unk_14 = 2;
            BattleScene_ValidateSelectedMove(arg0);
            return;
        }
    }

    if ((cont->buttonPressed & 2) != 0) {
        if ((arg0->animationState.unk_38.unk_1F[3] != 0) && (arg0->animationState.unk_38.unk_1F[3] < 0xA6)) {
            arg0->animationState.unk_14 = 3;
            BattleScene_ValidateSelectedMove(arg0);
            return;
        }
    }

    if ((cont->buttonPressed & 8) || (cont->buttonPressed & 1) || (cont->buttonPressed & 4) ||
        (cont->buttonPressed & 2)) {
        BattleAnim_PlaySoundEffect8();
    }
}

void BattleScene_HandlePlayerMoveSelection(unk_BattlePlayerEntity* arg0) {
    UNUSED s32 pad[2];
    Controller* sp1C = arg0->animationState.controller;
    unk_BattlePlayerAnimState* temp_v0 = &arg0->animationState;

    if ((temp_v0->rotation == 1) && (BattleScene_HandleNoUsableMoveSelection(arg0) == 0)) {
        if (arg0->unk_8C4.posX != 0) {
            if (BTN_IS_PRESSED(sp1C,
                               BTN_A | BTN_B | BTN_Z | BTN_L | BTN_R | BTN_CUP | BTN_CDOWN | BTN_CLEFT | BTN_CRIGHT)) {
                BattleScene_ClearParticipantMessageBuffer(arg0);
            }
        } else {
            if (temp_v0->unk_10 == 0) {
                temp_v0->unk_10 = 1;
            } else if (BTN_IS_PRESSED(sp1C, BTN_L) && !BTN_IS_DOWN(sp1C, BTN_R)) {
                temp_v0->unk_10 = 0;
                BattleAnim_PlaySoundEffect3();
            } else {
                temp_v0->unk_1C = 0;
                if (BTN_IS_DOWN(sp1C, BTN_R)) {
                    temp_v0->unk_1C = 1;
                }

                if (BTN_IS_PRESSED(sp1C, BTN_R)) {
                    BattleAnim_PlaySoundEffect1();
                }

                BattleScene_SelectMoveFromButtons(arg0);
            }
        }
    }
}

s32 BattleScene_HandlePlayerMoveSelectionLocked(unk_BattlePlayerEntity* arg0, UNUSED Controller* arg1) {
    arg0->animationState.unk_2A = 1;
    BattleScene_HandlePlayerMoveSelection(arg0);
    arg0->animationState.unk_2A = 1;
    return 0;
}

void BattleScene_ConfirmForcedMoveRepeat(unk_BattlePlayerEntity* arg0) {
    unk_BattlePlayerAnimState* ptr = &arg0->animationState;

    BattleScene_ApplyForcedActionDelay(arg0);
    ptr->unk_2A = 1;
    ptr->unk_10 = 3;
    ptr->unk_0C = ptr->unk_14;
}

void BattleScene_PollActionMenuRequestButtons(unk_BattlePlayerEntity* arg0) {
    unk_BattlePlayerAnimState* temp_v1 = &arg0->animationState;
    unk_BattlePlayerAnimState* temp_t0 = &sActivePokemon[BattleScene_GetParticipantSideIndex(arg0) == 0]->animationState;

    if (temp_v1->unk_10 == 0) {
        if (arg0->pokemonAnimation->unk_01 == 1) {
            gActiveController1 = &gControllers[arg0->pokemonAnimation->unk_08[0]->unk_001];
            gActiveController2 = &gControllers[arg0->pokemonAnimation->unk_08[0]->unk_001];
        } else {
            gActiveController1 = &gControllers[arg0->pokemonAnimation->unk_08[0]->unk_001];
            gActiveController2 = &gControllers[arg0->pokemonAnimation->unk_08[1]->unk_001];
        }

        if (temp_v1->controller->buttonPressed & 0x8000) {
            temp_v1->rotation = 1;
        } else if ((gActiveController1->buttonPressed | gActiveController2->buttonPressed) & 0x4000) {
            temp_v1->rotation = 2;
        } else if ((gActiveController1->buttonPressed | gActiveController2->buttonPressed) & 0x1000) {
            temp_v1->rotation = 3;
        } else {
            temp_v1->rotation = 0;
        }

        if ((temp_v1->controller->buttonPressed & 0x8000) ||
            (((gActiveController1->buttonPressed | gActiveController2->buttonPressed) & 0x4000) != 0) ||
            (((gActiveController1->buttonPressed | gActiveController2->buttonPressed) & 0x1000) && (temp_t0->unk_10 != 4))) {
            BattleAnim_PlaySoundEffect2();
        }
    }
}

s32 BattleScene_HandlePlayerActionInput(unk_BattlePlayerEntity* arg0) {
    BattleScene_GetParticipantSideIndex(arg0);

    if (BattleScene_ApplyForcedActionDelay(arg0) != 0) {
        return 1;
    }

    if (BattleScene_IsActionSelectionTimerExpired() != 0) {
        if (arg0->animationState.rotation == 2) {
            BattleScene_AutoSelectReplacementMon(arg0);
        } else {
            BattleScene_AutoSelectAvailableMove(arg0);
        }
        return 1;
    }

    BattleScene_PollActionMenuRequestButtons(arg0);

    switch (arg0->animationState.rotation) {
        case 2:
            BattleScene_HandlePlayerPartySelection(arg0);
            return 1;

        case 3:
            BattleScene_ForfeitPrompt(arg0);
            return 1;

        case 1:
            break;
    }
    return 0;
}

s32 BattleScene_HandlePlayerForcedActionState(unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1) {
    unk_BattlePlayerAnimState* sp1C = &arg0->animationState;
    unk_BattlePlayerAnimState* temp_v0 = &arg1->animationState;

    if ((sp1C->unk_2D == 0x10) && (temp_v0->unk_2D == 0x10)) {
        if (sp1C->unk_10 == 3) {
            BattleScene_ApplyForcedActionDelay(arg0);
            return 1;
        }

        if (BattleScene_IsActionSelectionTimerExpired() != 0) {
            BattleScene_AutoSelectReplacementMon(arg0);
            return 1;
        }

        sp1C->rotation = 2;
        sp1C->unk_10 = 2;
        BattleScene_HandlePlayerPartySelection(arg0);
        return 1;
    }

    if (sp1C->unk_2D == 0x10) {
        if (BattleScene_IsActionSelectionTimerExpired() != 0) {
            BattleScene_AutoSelectReplacementMon(arg0);
            return 1;
        }
        sp1C->rotation = 2;
        temp_v0->rotation = 1;
        sp1C->unk_10 = 2;
        temp_v0->unk_10 = 3;
        BattleScene_HandlePlayerPartySelection(arg0);
        return 1;
    }
    return 0;
}

void BattleScene_ShowParticipantOwnerAndSecondaryModels(void) {
    sActivePokemon[0]->unk_728.unk_168->posX.unk_01 |= 1;
    sActivePokemon[0]->unk_728.unk_000.unk_000.unk_01 |= 1;
    sActivePokemon[1]->unk_728.unk_168->posX.unk_01 |= 1;
    sActivePokemon[1]->unk_728.unk_000.unk_000.unk_01 |= 1;
}

void BattleScene_HideParticipantOwnerAndSecondaryModels(void) {
    sActivePokemon[0]->unk_728.unk_168->posX.unk_01 &= ~1;
    sActivePokemon[0]->unk_728.unk_000.unk_000.unk_01 &= ~1;
    sActivePokemon[1]->unk_728.unk_168->posX.unk_01 &= ~1;
    sActivePokemon[1]->unk_728.unk_000.unk_000.unk_01 &= ~1;
}

void BattleScene_AdvanceAttractInputScript(void) {
    static u16 D_84385758[][3] = {
        { 0x17C, 0, 0 },        { 0xA, BTN_L, 0 },  { 0xA, BTN_R, 0 }, { 0xC8, BTN_START, 0 },
        { 0xC8, BTN_START, 0 }, { 0xDC, BTN_A, 0 }, { 0, 0, 0 },
    };
    Controller* controller = &gDemoController;

    controller->buttonPressed = 0;

    if (gBattleInitStruct.posX == 0) {
        gBattleInitStruct.posX = D_84385758[gBattleInitFlag][0];
        if (gBattleInitStruct.posX != 0) {
            controller->buttonPressed = D_84385758[gBattleInitFlag][1];
            controller->buttonDown = D_84385758[gBattleInitFlag][2];
            gBattleInitFlag++;
        }
    }

    if (gBattleInitStruct.posX > 0) {
        gBattleInitStruct.posX--;
    }
}

void BattleScene_CheckForcedActionCondition(unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1) {
    PokemonAudioInfo* temp_v0 = &arg0->animationState.unk_38;
    PokemonAudioInfo* temp_v1 = &arg1->animationState.unk_38;

    if (!(arg0->animationState.unk_38.unk_4D & 0x60)) {
        temp_v0->unk_4C &= ~8;
        temp_v1->unk_4C &= ~8;
        if (temp_v0->unk_4C & 0x12) {
            arg0->animationState.unk_2A = 1;
        }
    } else {
        arg0->animationState.unk_2A = 1;
    }
}

void BattleScene_TickAttractModeInput(void) {
    unk_BattlePlayerAnimState* sp24 = &sActivePokemon[0]->animationState;
    unk_BattlePlayerAnimState* sp20 = &sActivePokemon[1]->animationState;
    PokemonAudioInfo* sp1C = &sActivePokemon[0]->animationState.unk_38;
    PokemonAudioInfo* sp18 = &sActivePokemon[1]->animationState.unk_38;
    Controller* cont = &gDemoController;

    BattleScene_AdvanceAttractInputScript();
    BattleScene_CheckForcedActionCondition(sActivePokemon[0], sActivePokemon[1]);
    BattleScene_CheckForcedActionCondition(sActivePokemon[1], sActivePokemon[0]);

    if (cont->buttonPressed & 0x20) {
        BattleScene_ShowParticipantOwnerAndSecondaryModels();
        BattleScene_TriggerOwnerModelAnimation(sActivePokemon[0]);
        BattleScene_TriggerOwnerModelAnimation(sActivePokemon[1]);
    }

    if (cont->buttonPressed & 0x10) {
        BattleScene_HideParticipantOwnerAndSecondaryModels();
    }

    if (cont->buttonPressed & 0x1000) {
        sp24->rotation = 0;
        sp20->rotation = 0;

        if (sp24->unk_2A == 0) {
            sp1C->unk_5A = BattleAI_ResolveRandomMove(0, 0);
        }

        if (sp20->unk_2A == 0) {
            sp18->unk_5A = BattleAI_ResolveRandomMove(1, 0);
        }

        sp24->unk_10 = 3;
        sp20->unk_10 = 3;

        if ((sp24->unk_10 == 3) && (sp20->unk_10 == 3)) {
            DetermineTurnOrder();
        }
    }

    BattleScene_SyncActiveHpToPartyState();

    if (cont->buttonPressed & 0x2000) {
        gBattleInitFlag = 0;
        gBattleInitStruct.posX = 0;
    }

    if (cont->buttonPressed & 0x8000) {
        gBattleScene.posX->unk_40 = 3;
    }
}

void BattleScene_CollectPlayerAction(unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1) {
    UNUSED s32 pad;
    PokemonAudioInfo* sp20 = &arg0->animationState.unk_38;
    PokemonAudioInfo* sp1C = &arg1->animationState.unk_38;

    if (BattleScene_HandlePlayerForcedActionState(arg0, arg1) == 0) {
        if (!(sp20->unk_4D & 0x60)) {
            sp20->unk_4C &= ~8;
            sp1C->unk_4C &= ~8;
            if (!(sp20->unk_4C & 0x12)) {
                if (BattleScene_HandlePlayerActionInput(arg0) == 0) {
                    if (!(sp20->unk_15 & 0x27)) {
                        if (!(sp20->unk_4C & 0x21)) {
                            if (sp1C->unk_4C & 0x20) {
                                BattleScene_HandlePlayerMoveSelectionLocked(arg0, arg0->animationState.controller);
                                sp20->unk_5A = 0xFF;
                            } else {
                                BattleScene_HandlePlayerMoveSelection(arg0);
                            }
                        } else {
                            BattleScene_HandlePlayerMoveSelectionLocked(arg0, arg0->animationState.controller);
                        }
                    } else {
                        BattleScene_HandlePlayerMoveSelectionLocked(arg0, arg0->animationState.controller);
                    }
                }
            } else {
                BattleScene_ConfirmForcedMoveRepeat(arg0);
            }
        } else {
            BattleScene_ConfirmForcedMoveRepeat(arg0);
        }
    }
}

void BattleScene_CollectActions(void) {
    unk_BattlePlayerAnimState* sp24 = &sActivePokemon[0]->animationState;
    unk_BattlePlayerAnimState* sp20 = &sActivePokemon[1]->animationState;
    PokemonAudioInfo* sp1C = &sActivePokemon[0]->animationState.unk_38;
    PokemonAudioInfo* sp18 = &sActivePokemon[1]->animationState.unk_38;

    if (sActivePokemon[0]->unk_724->unk_000 & 2) {
        gBattleControllerId = gBattleDamage;
        BattleScene_CollectCpuAction(sActivePokemon[0], sActivePokemon[1]);
        gBattleDamage = gBattleControllerId;
    } else {
        BattleScene_CollectPlayerAction(sActivePokemon[0], sActivePokemon[1]);
    }

    if (sActivePokemon[1]->unk_724->unk_000 & 2) {
        gBattleControllerId = gBattleDamage;
        BattleScene_CollectCpuAction(sActivePokemon[1], sActivePokemon[0]);
        gBattleDamage = gBattleControllerId;
    } else {
        BattleScene_CollectPlayerAction(sActivePokemon[1], sActivePokemon[0]);
    }

    if ((sp24->unk_10 == 3) && (sp20->unk_10 == 3)) {
        if (BattleScene_IsPresentationCountdownComplete() != 0) {
            gBattleResultPhase = 1;
        }

        if (sp24->rotation == 2) {
            BattleScene_CommitPlayerSwitchAction(sActivePokemon[0]);
        } else {
            BattleScene_CommitSelectedMoveAction(sActivePokemon[0]);
        }

        if (sp20->rotation == 2) {
            BattleScene_CommitPlayerSwitchAction(sActivePokemon[1]);
        } else {
            BattleScene_CommitSelectedMoveAction(sActivePokemon[1]);
        }

        if ((sp24->rotation == 2) || (sp20->rotation == 2)) {
            BattleScene_InitializeSwitchActions();
        } else {
            DetermineTurnOrder();
        }
    } else {
        if (!(sActivePokemon[0]->unk_724->unk_000 & 2) && !(sp1C->unk_4D & 0x60) && !(sp1C->unk_4C & 0x12)) {
            BattleScene_HandleActionSelectionCancel(0);
        }

        if (!(sActivePokemon[1]->unk_724->unk_000 & 2) && !(sp18->unk_4D & 0x60) && !(sp18->unk_4C & 0x12)) {
            BattleScene_HandleActionSelectionCancel(1);
        }
    }
}

void BattleScene_UpdateActionCollection(void) {
    gBattleUpdateHPFlag = 0;
    if (gSessionContext.unk_0000 == 0x10) {
        BattleScene_TickAttractModeInput();
    } else {
        BattleScene_CollectActions();
    }
}

void BattleScene_UpdateActionSelectPhase(void) {
    unk_BattlePlayerAnimState* sp1C = &sActivePokemon[0]->animationState;
    unk_BattlePlayerAnimState* sp18 = &sActivePokemon[1]->animationState;

    if (BattleScene_UpdateResultPresentation() == 0) {
        sActivePokemon[0]->unk_4C8 = 0;
        sActivePokemon[1]->unk_4C8 = 0;

        if (sp1C->unk_2A != 1) {
            sp1C->unk_2A = 0;
        }

        if (sp18->unk_2A != 1) {
            sp18->unk_2A = 0;
        }

        BattleScene_UpdateActionCollection();
        BattleScene_TickPresentationTimer();
        BattleScene_TickActionSelectionTimers();
    }
}
