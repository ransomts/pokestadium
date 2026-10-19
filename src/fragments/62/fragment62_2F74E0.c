#include "fragment62.h"
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

void Battle_InitTimers(void) {
    gBattlePhaseTimerMax = gBattleContext.unk_11EF * 0x1E;
    gPhaseTimerInitial = gBattleContext.unk_11EE * 0x708;
    gPhaseTimer = gBattleContext.unk_11EE * 0x708;
}

void Battle_AlignPhaseTimer(void) {
    s32 tmp = (s32)(gPhaseTimer / 30.0f) * 0x1E;

    gPhaseTimer = tmp;
}

s32 Battle_TickPhaseTimer(void) {
    if (gPhaseTimer == 0.0f) {
        return 1;
    }

    gPhaseTimer -= 1.0f;
    return 0;
}

s32 Battle_TickCountdownTimer(void) {
    if (gBattleContext.unk_11ED == 0) {
        return 0;
    }

    if ((((s32)gPhaseTimer % 30) == 0) && (gPhaseTimer != 0.0f)) {
        Audio_PlaySoundEffect(0x3E, 0, 0);
    }

    if (gPhaseTimer == 0.0f) {
        return 1;
    }
    return 0;
}

s32 Battle_GetMoveScore(s32 arg0, s32 arg1) {
    s32 temp_v0 = arg0 * 0x30;

    if (temp_v0 < (arg1 * 0xA)) {
        return 1;
    }

    if (temp_v0 < (arg1 * 0x1B)) {
        return 2;
    }

    return 3;
}

s32 Battle_ComputeWinner(void) {
    PokemonData* ptr;
    s32 i;
    s32 var_s3 = 0;
    s32 var_s4 = 0;
    s32 var_s5 = 0;
    s32 var_s6 = 0;

    for (i = 0; i < BattleScene_GetSelectedSideTeamSize(sActivePokemon[0]); i++) {
        ptr = &sActivePokemon[0]->unk_724->unk_01C[i];
        if (ptr->unk_02 != 0) {
            var_s3++;
        }
    }

    for (i = 0; i < BattleScene_GetSelectedSideTeamSize(sActivePokemon[1]); i++) {
        ptr = &sActivePokemon[1]->unk_724->unk_01C[i];
        if (ptr->unk_02 != 0) {
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
        var_s5 += Battle_GetMoveScore(ptr->unk_02, ptr->unk_26);
    }

    for (i = 0; i < BattleScene_GetSelectedSideTeamSize(sActivePokemon[1]); i++) {
        ptr = &sActivePokemon[1]->unk_724->unk_01C[i];
        var_s6 += Battle_GetMoveScore(ptr->unk_02, ptr->unk_26);
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

s32 Battle_UpdateResultPhase(void) {
    s32 sp1C = 0;
    s32 var_v0;

    if (gBattleContext.unk_11ED == 0) {
        return 0;
    }

    if (Battle_TickCountdownTimer() != 0) {
        switch (gBattleResultPhase) {
            case 1:
                Dialog_SetMode(0xD);
                gBattleResultPhase = 2;
                Audio_PlaySoundEffect(0x3F, 0, 0);
                QueueEndTurnSound();
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
                    gBattleState.unk_00->unk_40 = Battle_ComputeWinner();
                    Stage_SetFadeColor(0x14);
                }
                break;
        }
    }
    return sp1C;
}

s32 Battle_TickHPBarTimer(void) {
    if (gBattleContext.unk_11ED == 0) {
        return 0;
    }

    if (gHPBarTimer == 329.0f) {
        Audio_PlaySoundEffect(0x3C, 0, 0);
    }

    if (gHPBarTimer == 91.0f) {
        Audio_PlaySoundEffect(0x3D, 3, 0);
    }

    if (gHPBarTimer == 61.0f) {
        Audio_PlaySoundEffect(0x3D, 2, 0);
    }

    if (gHPBarTimer == 31.0f) {
        Audio_PlaySoundEffect(0x3D, 1, 0);
    }

    if (gHPBarTimer == 1.0f) {
        Audio_PlaySoundEffect(0x3D, 0, 0);
    }

    if (gHPBarTimer == 0.0f) {
        return 1;
    }
    return 0;
}

void Battle_ResetHPBarTimer(void) {
    gHPBarTimer = gBattleContext.unk_11EF * 0x1E;
}

s32 Battle_TickBattleTimer(void) {
    if (gHPBarTimer > 0.0f) {
        gHPBarTimer -= 1.0f;
    }

    if (gBattleTimer >= 150.0f) {
        return 1;
    }

    gBattleTimer += 1.0f;
    return 0;
}

void Battle_ResetAllTimers(void) {
    gBattleTimer = 0.0f;
    Battle_ResetHPBarTimer();
}

s32 Battle_UpdateAnimFrame(unk_BattlePlayerEntity* arg0) {
    unk_BattlePlayerAnimState* temp_v1 = &arg0->unk_654;

    if (arg0->unk_654.unk_10 == 3) {
        temp_v1->unk_1E += 0x38E;
        return 1;
    }
    return 0;
}

void Battle_UpdateHPScale(void) {
    unk_D_800FCB18* temp_a2;
    unk_D_800FCB18* temp_a3;
    unk_BattlePlayerAnimState* ptr1;
    unk_BattlePlayerAnimState* ptr2;
    PokemonData* ptr3;
    PokemonData* ptr4;

    ptr1 = &sActivePokemon[0]->unk_654;
    ptr2 = &sActivePokemon[1]->unk_654;
    temp_a2 = &sActivePokemon[0]->unk_654.unk_38;
    temp_a3 = &sActivePokemon[1]->unk_654.unk_38;

    ptr3 = &sActivePokemon[0]->unk_724->unk_01C[ptr1->unk_08];
    ptr4 = &sActivePokemon[1]->unk_724->unk_01C[ptr2->unk_08];

    if (gBattleUpdateHPFlag != 0) {
        gPlayerScaleFactors[0] = temp_a2->unk_0C = temp_a2->unk_28;
        gPlayerScaleFactors[1] = temp_a3->unk_0C = temp_a3->unk_28;

        ptr3->unk_02 = temp_a2->unk_28;
        ptr4->unk_02 = temp_a3->unk_28;
    }
}

s32 Battle_CheckMoveAvailability(unk_BattlePlayerEntity* arg0) {
    s32 i;
    s32 var_v1;
    unk_BattlePlayerAnimState* temp_v1;
    unk_D_800FCB18* temp_v0;

    temp_v1 = &arg0->unk_654;
    temp_v0 = &arg0->unk_654.unk_38;
    var_v1 = 0;

    if (arg0->unk_654.unk_38.unk_52 != 0) {
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

s32 Battle_IsMoveInvalid(unk_BattlePlayerEntity* arg0, s32 arg1) {
    unk_D_800FCB18* ptr = &arg0->unk_654.unk_38;

    if (!(ptr->unk_32[arg1] & 0x3F)) {
        return 1;
    }

    if ((ptr->unk_52 & 0xF) && (arg1 == (ptr->unk_52 >> 4))) {
        return 1;
    }

    return 0;
}

void Battle_SelectFirstAvailableMove(unk_BattlePlayerEntity* arg0) {
    s32 i;
    unk_BattlePlayerAnimState* temp_v0 = &arg0->unk_654;

    if (Battle_CheckMoveAvailability(arg0) == 0) {
        for (i = 0; i < 4; i++) {
            if (Battle_IsMoveInvalid(arg0, i) == 0) {
                temp_v0->unk_04 = 1;
                temp_v0->unk_10 = 3;
                temp_v0->unk_14 = i;
                temp_v0->unk_0C = i;
                break;
            }
        }
    }
}

void Battle_SelectNextValidMove(unk_BattlePlayerEntity* arg0) {
    s32 i;
    unk_BattlePlayerAnimState* sp1C = &arg0->unk_654;

    for (i = 0; i < arg0->unk_720->unk_08[0]->unk_002; i++) {
        if ((arg0->unk_720->unk_08[0]->unk_01C[i].unk_02 != 0) && (i != sp1C->unk_08)) {
            PlaySoundEffect_Cancel();
            sp1C->unk_1C = 0;
            sp1C->unk_1E = 0;
            sp1C->unk_10 = 3;
            sp1C->unk_18 = i;
            return;
        }
    }

    Battle_SelectFirstAvailableMove(arg0);
}

void Battle_UpdateControllerRef(unk_BattlePlayerEntity* arg0) {
    unk_BattlePlayerAnimState* ptr = &arg0->unk_654;

    ptr->unk_2C = ptr->unk_2B;
    ptr->unk_C8 = &gControllers[arg0->unk_720->unk_08[ptr->unk_2C]->unk_001];
}

void Battle_HandleConfirmInput(s32 arg0) {
    unk_BattlePlayerAnimState* sp2C;
    unk_BattlePlayerAnimState* sp28;
    UNUSED s32 pad;
    Controller* cont;

    sp2C = &sActivePokemon[arg0]->unk_654;
    sp28 = &sActivePokemon[arg0 == 0]->unk_654;
    cont = sp2C->unk_C8;

    if ((sp2C->unk_10 != 3) || !(cont->buttonPressed & 0x20)) {
        return;
    }

    if (sp2C->unk_2D == 0x10) {
        if (sp2C->unk_04 == 2) {
            Battle_UpdateControllerRef(sActivePokemon[arg0]);
        }
        PlaySoundEffect_Confirm();
        sp2C->unk_10 = 2;
    }

    if (sp28->unk_2D != 0x10) {
        if (sp2C->unk_04 == 2) {
            Battle_UpdateControllerRef(sActivePokemon[arg0]);
        }
        PlaySoundEffect_Confirm();
        sp2C->unk_10 = 0;
    }
}

void Battle_InitLighting(void) {
    Battle_InitTimers();
    func_84370B7C(sActivePokemon[0]);
    func_84370B7C(sActivePokemon[1]);

    gPlayerScaleFactors[0] = sActivePokemon[0]->unk_654.unk_38.unk_0C;
    gPlayerScaleFactors[1] = sActivePokemon[1]->unk_654.unk_38.unk_0C;

    ResetBattleAfterMove(0, 1);
    ResetBattleAfterMove(1, 0);
}

s32 Battle_HasAnyValidMoves(unk_BattlePlayerEntity* arg0) {
    unk_D_800FCB18* temp_v0 = &arg0->unk_654.unk_38;
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

s32 Battle_HandleSimultaneousInput(unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1) {
    UNUSED s32 pad[2];
    unk_BattlePlayerAnimState* sp1C = &arg0->unk_654;
    unk_BattlePlayerAnimState* temp_v0 = &arg1->unk_654;

    if ((arg0->unk_654.unk_2D == 0x10) && (arg1->unk_654.unk_2D == 0x10)) {
        if (sp1C->unk_10 == 3) {
            Battle_UpdateAnimFrame(arg0);
            return 1;
        }

        sp1C->unk_04 = 2;
        sp1C->unk_10 = 2;

        if (gBattleTimer == 20.0f) {
            PlaySoundEffect_Cancel();
            gRandomMoveSlot = BattleAI_ChooseAction(0);
            sp1C->unk_1C = 0;
            sp1C->unk_18 = gRandomMoveSlot - 4;
            sp1C->unk_1E = 0;
            sp1C->unk_10 = 3;
            sp1C->unk_04 = 2;
        }
        return 1;
    }

    if (sp1C->unk_2D == 0x10) {
        sp1C->unk_04 = 2;
        sp1C->unk_10 = 2;
        temp_v0->unk_10 = 3;
        temp_v0->unk_04 = 1;

        if (gBattleTimer == 20.0f) {
            PlaySoundEffect_Cancel();
            gRandomMoveSlot = BattleAI_ChooseAction(0);
            sp1C->unk_1C = 0;
            sp1C->unk_18 = gRandomMoveSlot - 4;
            sp1C->unk_1E = 0;
            sp1C->unk_10 = 3;
            sp1C->unk_04 = 2;
        }
        return 1;
    }

    return 0;
}

void Battle_SetIdleAnim(unk_BattlePlayerEntity* arg0, UNUSED unk_BattlePlayerEntity* arg1) {
    unk_BattlePlayerAnimState* ptr = &arg0->unk_654;

    Battle_UpdateAnimFrame(arg0);
    ptr->unk_2A = 1;
    ptr->unk_04 = 1;
    ptr->unk_0C = ptr->unk_14;
    ptr->unk_10 = 3;
}

void Battle_HandleMoveTimeout_Player1(unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1) {
    unk_BattlePlayerAnimState* sp20 = &arg1->unk_654;
    unk_BattlePlayerAnimState* sp1C = &arg0->unk_654;

    Battle_UpdateAnimFrame(arg0);
    sp1C->unk_2A = 1;

    if ((gBattleTimer == 30.0f) && (gRandomMoveSlot < 4)) {
        PlaySoundEffect_Cancel();
    }

    if ((gRandomMoveSlot < 4) && (gBattleTimer >= 30.0f)) {
        sp1C->unk_10 = 1;
        sp1C->unk_04 = 1;
    }

    if (((gBattleTimer >= 90.0f) || ((sp20->unk_10 == 3) && (gBattleTimer >= 10.0f))) && (gRandomMoveSlot < 4)) {
        PlaySoundEffect_Cancel();
        sp1C->unk_04 = 1;
        sp1C->unk_10 = 3;
        sp1C->unk_0C = sp1C->unk_14;
    }
}

void Battle_HandleMoveTimeout_Player2(unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1) {
    unk_BattlePlayerAnimState* sp18;
    unk_BattlePlayerAnimState* sp14;
    s32 var_v0;

    sp18 = &arg0->unk_654;
    sp14 = &arg1->unk_654;

    if ((gBattleTimer == 30.0f) && (gRandomMoveSlot < 4)) {
        PlaySoundEffect_Cancel();
    }

    if (gRandomMoveSlot < 4) {
        if (gBattleTimer >= 30.0f) {
            sp18->unk_10 = 1;
            sp18->unk_04 = 1;
        }
    }

    if ((gBattleTimer >= 90.0f) || ((sp14->unk_10 == 3) && (gBattleTimer >= 10.0f))) {
        if (gRandomMoveSlot < 4) {
            PlaySoundEffect_Cancel();
            sp18->unk_04 = 1;
            sp18->unk_10 = 3;
            if (Battle_HasAnyValidMoves(arg0) != 0) {
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

s32 Battle_HandleMoveTimeout_Random(unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1) {
    unk_BattlePlayerAnimState* sp1C = &arg0->unk_654;
    unk_BattlePlayerAnimState* sp18 = &arg1->unk_654;

    if ((gBattleTimer == 30.0f) && (gRandomMoveSlot >= 4)) {
        PlaySoundEffect_Cancel();
    }

    if (gBattleTimer >= 30.0f) {
        if (gRandomMoveSlot >= 4) {
            sp1C->unk_10 = 2;
            sp1C->unk_04 = 2;
        }
    }

    if ((gBattleTimer >= 90.0f) || ((sp18->unk_10 == 3) && (gBattleTimer >= 10.0f))) {
        if (gRandomMoveSlot >= 4) {
            PlaySoundEffect_Cancel();
            sp1C->unk_1C = 0;
            sp1C->unk_18 = gRandomMoveSlot - 4;
            sp1C->unk_1E = 0;
            sp1C->unk_10 = 3;
            sp1C->unk_04 = 2;
        }
    }

    if (gRandomMoveSlot >= 4) {
        return 1;
    }
    return 0;
}

void Battle_RandomizeMoveSlot(UNUSED unk_D_800FCB18* arg0, UNUSED unk_D_800FCB18* arg1, UNUSED unk_BattlePlayerAnimState* arg2,
                   UNUSED unk_BattlePlayerAnimState* arg3, UNUSED unk_BattlePlayerEntity* arg4) {
    if ((gBattleTimer == 1.0f) && (gRandomMoveSelectedFlag == 0)) {
        gRandomMoveSelectedFlag = 1;
        gRandomMoveSlot = BattleAI_ChooseAction(0);
    }
}

s32 Battle_UpdateMoveSelection(unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1) {
    unk_D_800FCB18* sp34 = &arg0->unk_654.unk_38;
    unk_D_800FCB18* sp30 = &arg1->unk_654.unk_38;
    unk_BattlePlayerAnimState* sp2C = &arg0->unk_654;
    unk_BattlePlayerAnimState* sp28 = &arg1->unk_654;

    if (Battle_HandleSimultaneousInput(arg0, arg1) != 0) {
        return 0;
    }

    if (!(sp34->unk_4D & 0x60)) {
        sp34->unk_4C &= ~8;
        sp30->unk_4C &= ~8;

        if (!(sp34->unk_4C & 0x12)) {
            if (Battle_UpdateAnimFrame(arg0) != 0) {
                return 0;
            }

            if (gBattleTimer == 0.0f) {
                gRandomMoveSelectedFlag = 0;
                return 0;
            }

            Battle_RandomizeMoveSlot(sp34, sp30, sp2C, sp28, arg1);

            if (Battle_HandleMoveTimeout_Random(arg0, arg1) != 0) {
                return 0;
            }

            if (!(sp34->unk_15 & 0x27)) {
                if (!(sp34->unk_4C & 0x21)) {
                    if (sp30->unk_4C & 0x20) {
                        Battle_HandleMoveTimeout_Player1(arg0, arg1);
                        sp34->unk_5A = 0xFF;
                    } else if (Battle_UpdateAnimFrame(arg0) != 0) {
                        return 0;
                    } else {
                        if (gBattleTimer == 0.0f) {
                            gRandomMoveSelectedFlag = 0;
                            return 0;
                        }
                        Battle_RandomizeMoveSlot(sp34, sp30, sp2C, sp28, arg1);
                        Battle_HandleMoveTimeout_Player2(arg0, arg1);
                    }
                } else {
                    Battle_HandleMoveTimeout_Player1(arg0, arg1);
                }
            } else {
                Battle_HandleMoveTimeout_Player1(arg0, arg1);
            }
        } else {
            Battle_SetIdleAnim(arg0, arg1);
        }
    } else {
        Battle_SetIdleAnim(arg0, arg1);
    }

    return 0;
}

void Battle_HandleMenuNavigation(unk_BattlePlayerEntity* arg0) {
    unk_BattlePlayerAnimState* sp18 = &arg0->unk_654;
    unk_BattlePlayerAnimState* temp_a0 = &sActivePokemon[IsPrimaryEntity(arg0) == 0]->unk_654;

    if (arg0->unk_720->unk_01 == 1) {
        gActiveController1 = &gControllers[arg0->unk_720->unk_08[0]->unk_001];
        gActiveController2 = &gControllers[arg0->unk_720->unk_08[0]->unk_001];
    } else {
        gActiveController1 = &gControllers[arg0->unk_720->unk_08[0]->unk_001];
        gActiveController2 = &gControllers[arg0->unk_720->unk_08[1]->unk_001];
    }

    if (temp_a0->unk_10 == 4) {
        sp18->unk_10 = 0;
        sp18->unk_04 = 0;
        return;
    }

    if (sp18->unk_10 != 4) {
        sp18->unk_2F = 0;
    }

    sp18->unk_10 = 4;

    if ((gBattleState.unk_00->unk_40 == 0) &&
        (BTN_IS_PRESSED(gActiveController1, BTN_DLEFT) || BTN_IS_PRESSED(gActiveController2, BTN_DLEFT))) {
        sp18->unk_2F = 0;
        PlaySoundEffect(1);
    }

    if ((gBattleState.unk_00->unk_40 == 0) &&
        (BTN_IS_PRESSED(gActiveController1, BTN_DRIGHT) || BTN_IS_PRESSED(gActiveController2, BTN_DRIGHT))) {
        sp18->unk_2F = 1;
        PlaySoundEffect(1);
    }

    if ((sp18->unk_2F == 1) && (BTN_IS_PRESSED(gActiveController1, BTN_A) || BTN_IS_PRESSED(gActiveController2, BTN_A)) &&
        (gBattleState.unk_00->unk_40 == 0)) {
        PlaySoundEffect(2);
        gBattleState.unk_00->unk_40 = (IsPrimaryEntity(arg0) == 0) + 1;
        Stage_SetFadeColor(0x14);
    } else if ((sp18->unk_2F == 0) && (BTN_IS_PRESSED(gActiveController1, BTN_A) || BTN_IS_PRESSED(gActiveController2, BTN_A))) {
        sp18->unk_10 = 0;
        sp18->unk_04 = 0;
        PlaySoundEffect(3);
    }
}

void Battle_ClearMoveSelection(unk_BattlePlayerEntity* arg0) {
    unk_BattlePlayerAnimState* temp_v0 = &arg0->unk_654;
    unk_D_800FCB18* temp_v1 = &sActivePokemon[IsPrimaryEntity(arg0) == 0]->unk_654.unk_38;

    if (temp_v1->unk_4C & 0x20) {
        arg0->unk_654.unk_38.unk_5A = 0xFF;
    }

    if (temp_v0->unk_2D != 0x10) {
        temp_v0->unk_2D = 0xF;
    }

    temp_v0->unk_1C = 0;
    Battle_SetEntityPosition(arg0);
}

s32 Battle_ValidateMoveSelection(unk_BattlePlayerEntity* arg0) {
    if (arg0->unk_720->unk_08[arg0->unk_654.unk_2C]->unk_01C[arg0->unk_654.unk_18].unk_02 != 0) {
        return 1;
    }

    Battle_SetEntityPosition(arg0);
    BattleScene_BuildParticipantMessage(arg0, 3);
    PlaySoundEffect_Error();
    return 0;
}

void Battle_InvalidMoveFeedback(unk_BattlePlayerEntity* arg0) {
    Battle_SetEntityPosition(arg0);
    BattleScene_BuildParticipantMessage(arg0, 4);
}

void Battle_UpdateActiveController(unk_BattlePlayerEntity* arg0, s32 arg1) {
    if (arg1 == 1) {
        gActiveController1 = &gControllers[arg0->unk_720->unk_08[0]->unk_001];
        gActiveController2 = &gControllers[arg0->unk_720->unk_08[0]->unk_001];
    } else {
        gActiveController1 = &gControllers[arg0->unk_720->unk_08[0]->unk_001];
        gActiveController2 = &gControllers[arg0->unk_720->unk_08[1]->unk_001];
    }

    if (arg1 == 1) {
        if (BTN_IS_PRESSED(gActiveController1, BTN_A | BTN_B | BTN_CUP | BTN_CDOWN | BTN_CLEFT | BTN_CRIGHT)) {
            arg0->unk_654.unk_2C = 0;
            Entity_BindController(arg0, gActiveController1);
        } else if (BTN_IS_PRESSED(gActiveController2, BTN_A | BTN_B | BTN_CUP | BTN_CDOWN | BTN_CLEFT | BTN_CRIGHT)) {
            Entity_BindController(arg0, gActiveController2);
            arg0->unk_654.unk_2C = 0;
        }
    } else if (BTN_IS_PRESSED(gActiveController1, BTN_A | BTN_B | BTN_CUP | BTN_CDOWN | BTN_CLEFT | BTN_CRIGHT)) {
        Entity_BindController(arg0, gActiveController1);
        arg0->unk_654.unk_2C = 0;
    } else if (BTN_IS_PRESSED(gActiveController2, BTN_A | BTN_B | BTN_CUP | BTN_CDOWN | BTN_CLEFT | BTN_CRIGHT)) {
        Entity_BindController(arg0, gActiveController2);
        arg0->unk_654.unk_2C = 1;
    }
}

void Battle_HandleMoveSelectionInput(unk_BattlePlayerEntity* arg0, Controller* arg1) {
    unk_BattlePlayerAnimState* sp1C;
    unk_D_800AE540_0004* temp_a1;

    sp1C = &arg0->unk_654;

    Battle_UpdateActiveController(arg0, arg0->unk_720->unk_01);
    temp_a1 = arg0->unk_720->unk_08[sp1C->unk_2C];
    arg1 = sp1C->unk_C8;

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
            if (Battle_ValidateMoveSelection(arg0) != 0) {
                PlaySoundEffect_Error();
                Battle_InvalidMoveFeedback(arg0);
            }
        } else if (((temp_a1->unk_002 - 1) >= sp1C->unk_18) && (Battle_ValidateMoveSelection(arg0) != 0)) {
            PlaySoundEffect_Cancel();
            sp1C->unk_1C = 0;
            sp1C->unk_1E = 0;
            sp1C->unk_10 = 3;
        }
    }
}

void Battle_UpdateInputState(unk_BattlePlayerEntity* arg0) {
    UNUSED s32 pad;
    s32 idx;
    unk_BattlePlayerAnimState* sp18 = &arg0->unk_654;

    if (arg0->unk_720->unk_01 == 1) {
        gActiveController1 = &gControllers[arg0->unk_720->unk_08[0]->unk_001];
        gActiveController2 = &gControllers[arg0->unk_720->unk_08[0]->unk_001];
    } else {

        gActiveController1 = &gControllers[arg0->unk_720->unk_08[sp18->unk_2C]->unk_001];
        idx = sp18->unk_2C == 0;
        gActiveController2 = &gControllers[arg0->unk_720->unk_08[idx]->unk_001];
    }

    if (arg0->unk_8C4.unk_00 != 0) {
        if (sp18->unk_C8->buttonPressed & 0xE03F) {
            Battle_SetEntityPosition(arg0);
        }
    } else if (sp18->unk_10 == 0) {
        sp18->unk_10 = 2;
    } else if (((gActiveController1->buttonPressed & 0x20) || (gActiveController2->buttonPressed & 0x20)) && (sp18->unk_2D != 0x10) &&
               !(gActiveController1->buttonDown & 0x10) && !(gActiveController2->buttonDown & 0x10)) {
        Battle_UpdateControllerRef(arg0);
        PlaySoundEffect_Confirm();
        sp18->unk_10 = 0;
    } else {
        sp18->unk_1C = 0;
        if ((gActiveController1->buttonDown & 0x10) || (gActiveController2->buttonDown & 0x10)) {
            if ((gActiveController1->buttonPressed & 0x10) || (gActiveController2->buttonPressed & 0x10)) {
                PlaySoundEffect_Select();
            }
            sp18->unk_1C = 1;
        }
        Battle_HandleMoveSelectionInput(arg0, sp18->unk_C8);
    }
}

void Battle_ApplyMoveAnimation(unk_BattlePlayerEntity* arg0) {
    unk_BattlePlayerAnimState* temp_v0 = &arg0->unk_654;
    unk_D_800FCB18* temp_v1 = &arg0->unk_654.unk_38;

    if (arg0->unk_654.unk_14 != 4) {
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
    Battle_SetEntityPosition(arg0);
}

s32 Battle_CheckInputTimeout(unk_BattlePlayerEntity* arg0) {
    s32 i;
    s32 temp_a1;
    s32 var_v1;
    unk_BattlePlayerAnimState* temp_v0;
    unk_D_800FCB18* temp_a0;
    Controller* cont;

    temp_v0 = &arg0->unk_654;
    temp_a0 = &arg0->unk_654.unk_38;
    cont = arg0->unk_654.unk_C8;
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
        if (arg0->unk_8C4.unk_00 == 0) {
            if (temp_v0->unk_10 == 0) {
                temp_v0->unk_10 = 1;
            }
            Battle_SetEntityPosition(arg0);
            BattleScene_BuildParticipantMessage(arg0, 0);
        } else if (cont->buttonPressed & 0x20) {
            Battle_SetEntityPosition(arg0);
            temp_v0->unk_10 = 0;
            PlaySoundEffect_Confirm();
        } else if (cont->buttonPressed & 0x8000) {
            Battle_SetEntityPosition(arg0);
            temp_v0->unk_1E = 0;
            temp_v0->unk_10 = 3;
            temp_v0->unk_14 = 4;
        }
        return 1;
    }
    return 0;
}

s32 Battle_HandleMoveError(unk_BattlePlayerEntity* arg0) {
    UNUSED s32 pad[2];
    unk_BattlePlayerAnimState* sp24 = &arg0->unk_654;
    unk_D_800FCB18* ptr = &arg0->unk_654.unk_38;

    if (!(ptr->unk_32[sp24->unk_14] & 0x3F)) {
        PlaySoundEffect_Error();
        Battle_SetEntityPosition(arg0);
        BattleScene_BuildParticipantMessage(arg0, 1);
        return 1;
    }

    if ((ptr->unk_52 & 0xF) && (sp24->unk_14 == (ptr->unk_52 >> 4))) {
        PlaySoundEffect_Error();
        Battle_SetEntityPosition(arg0);
        BattleScene_BuildParticipantMessage(arg0, 2);
        return 1;
    }

    PlaySoundEffect_Cancel();
    sp24->unk_1E = 0;
    sp24->unk_10 = 3;
    sp24->unk_1C = 0;
    return 0;
}

void Battle_HandleQuickSelectInput(unk_BattlePlayerEntity* arg0) {
    Controller* cont = arg0->unk_654.unk_C8;

    if ((cont->buttonPressed & 8) != 0) {
        if ((arg0->unk_654.unk_38.unk_1F[0] != 0) && (arg0->unk_654.unk_38.unk_1F[0] < 0xA6)) {
            arg0->unk_654.unk_14 = 0;
            Battle_HandleMoveError(arg0);
            return;
        }
    }

    if ((cont->buttonPressed & 1) != 0) {
        if ((arg0->unk_654.unk_38.unk_1F[1] != 0) && (arg0->unk_654.unk_38.unk_1F[1] < 0xA6)) {
            arg0->unk_654.unk_14 = 1;
            Battle_HandleMoveError(arg0);
            return;
        }
    }

    if ((cont->buttonPressed & 4) != 0) {
        if ((arg0->unk_654.unk_38.unk_1F[2] != 0) && (arg0->unk_654.unk_38.unk_1F[2] < 0xA6)) {
            arg0->unk_654.unk_14 = 2;
            Battle_HandleMoveError(arg0);
            return;
        }
    }

    if ((cont->buttonPressed & 2) != 0) {
        if ((arg0->unk_654.unk_38.unk_1F[3] != 0) && (arg0->unk_654.unk_38.unk_1F[3] < 0xA6)) {
            arg0->unk_654.unk_14 = 3;
            Battle_HandleMoveError(arg0);
            return;
        }
    }

    if ((cont->buttonPressed & 8) || (cont->buttonPressed & 1) || (cont->buttonPressed & 4) ||
        (cont->buttonPressed & 2)) {
        PlaySoundEffect_Error();
    }
}

void Battle_ProcessMoveInput(unk_BattlePlayerEntity* arg0) {
    UNUSED s32 pad[2];
    Controller* sp1C = arg0->unk_654.unk_C8;
    unk_BattlePlayerAnimState* temp_v0 = &arg0->unk_654;

    if ((temp_v0->unk_04 == 1) && (Battle_CheckInputTimeout(arg0) == 0)) {
        if (arg0->unk_8C4.unk_00 != 0) {
            if (BTN_IS_PRESSED(sp1C,
                               BTN_A | BTN_B | BTN_Z | BTN_L | BTN_R | BTN_CUP | BTN_CDOWN | BTN_CLEFT | BTN_CRIGHT)) {
                Battle_SetEntityPosition(arg0);
            }
        } else {
            if (temp_v0->unk_10 == 0) {
                temp_v0->unk_10 = 1;
            } else if (BTN_IS_PRESSED(sp1C, BTN_L) && !BTN_IS_DOWN(sp1C, BTN_R)) {
                temp_v0->unk_10 = 0;
                PlaySoundEffect_Confirm();
            } else {
                temp_v0->unk_1C = 0;
                if (BTN_IS_DOWN(sp1C, BTN_R)) {
                    temp_v0->unk_1C = 1;
                }

                if (BTN_IS_PRESSED(sp1C, BTN_R)) {
                    PlaySoundEffect_Select();
                }

                Battle_HandleQuickSelectInput(arg0);
            }
        }
    }
}

s32 Battle_UpdateMoveInputState(unk_BattlePlayerEntity* arg0, UNUSED Controller* arg1) {
    arg0->unk_654.unk_2A = 1;
    Battle_ProcessMoveInput(arg0);
    arg0->unk_654.unk_2A = 1;
    return 0;
}

void Battle_TriggerMoveAnim(unk_BattlePlayerEntity* arg0) {
    unk_BattlePlayerAnimState* ptr = &arg0->unk_654;

    Battle_UpdateAnimFrame(arg0);
    ptr->unk_2A = 1;
    ptr->unk_10 = 3;
    ptr->unk_0C = ptr->unk_14;
}

void Battle_HandleCancelInput(unk_BattlePlayerEntity* arg0) {
    unk_BattlePlayerAnimState* temp_v1 = &arg0->unk_654;
    unk_BattlePlayerAnimState* temp_t0 = &sActivePokemon[IsPrimaryEntity(arg0) == 0]->unk_654;

    if (temp_v1->unk_10 == 0) {
        if (arg0->unk_720->unk_01 == 1) {
            gActiveController1 = &gControllers[arg0->unk_720->unk_08[0]->unk_001];
            gActiveController2 = &gControllers[arg0->unk_720->unk_08[0]->unk_001];
        } else {
            gActiveController1 = &gControllers[arg0->unk_720->unk_08[0]->unk_001];
            gActiveController2 = &gControllers[arg0->unk_720->unk_08[1]->unk_001];
        }

        if (temp_v1->unk_C8->buttonPressed & 0x8000) {
            temp_v1->unk_04 = 1;
        } else if ((gActiveController1->buttonPressed | gActiveController2->buttonPressed) & 0x4000) {
            temp_v1->unk_04 = 2;
        } else if ((gActiveController1->buttonPressed | gActiveController2->buttonPressed) & 0x1000) {
            temp_v1->unk_04 = 3;
        } else {
            temp_v1->unk_04 = 0;
        }

        if ((temp_v1->unk_C8->buttonPressed & 0x8000) ||
            (((gActiveController1->buttonPressed | gActiveController2->buttonPressed) & 0x4000) != 0) ||
            (((gActiveController1->buttonPressed | gActiveController2->buttonPressed) & 0x1000) && (temp_t0->unk_10 != 4))) {
            PlaySoundEffect_Cancel();
        }
    }
}

s32 Battle_UpdateEntityState(unk_BattlePlayerEntity* arg0) {
    IsPrimaryEntity(arg0);

    if (Battle_UpdateAnimFrame(arg0) != 0) {
        return 1;
    }

    if (Battle_TickHPBarTimer() != 0) {
        if (arg0->unk_654.unk_04 == 2) {
            Battle_SelectNextValidMove(arg0);
        } else {
            Battle_SelectFirstAvailableMove(arg0);
        }
        return 1;
    }

    Battle_HandleCancelInput(arg0);

    switch (arg0->unk_654.unk_04) {
        case 2:
            Battle_UpdateInputState(arg0);
            return 1;

        case 3:
            Battle_HandleMenuNavigation(arg0);
            return 1;

        case 1:
            break;
    }
    return 0;
}

s32 Battle_UpdateDualEntityState(unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1) {
    unk_BattlePlayerAnimState* sp1C = &arg0->unk_654;
    unk_BattlePlayerAnimState* temp_v0 = &arg1->unk_654;

    if ((sp1C->unk_2D == 0x10) && (temp_v0->unk_2D == 0x10)) {
        if (sp1C->unk_10 == 3) {
            Battle_UpdateAnimFrame(arg0);
            return 1;
        }

        if (Battle_TickHPBarTimer() != 0) {
            Battle_SelectNextValidMove(arg0);
            return 1;
        }

        sp1C->unk_04 = 2;
        sp1C->unk_10 = 2;
        Battle_UpdateInputState(arg0);
        return 1;
    }

    if (sp1C->unk_2D == 0x10) {
        if (Battle_TickHPBarTimer() != 0) {
            Battle_SelectNextValidMove(arg0);
            return 1;
        }
        sp1C->unk_04 = 2;
        temp_v0->unk_04 = 1;
        sp1C->unk_10 = 2;
        temp_v0->unk_10 = 3;
        Battle_UpdateInputState(arg0);
        return 1;
    }
    return 0;
}

void Entities_ShowAllModels(void) {
    sActivePokemon[0]->unk_728.unk_168->unk_00.unk_01 |= 1;
    sActivePokemon[0]->unk_728.unk_000.unk_000.unk_01 |= 1;
    sActivePokemon[1]->unk_728.unk_168->unk_00.unk_01 |= 1;
    sActivePokemon[1]->unk_728.unk_000.unk_000.unk_01 |= 1;
}

void Entities_HideAllModels(void) {
    sActivePokemon[0]->unk_728.unk_168->unk_00.unk_01 &= ~1;
    sActivePokemon[0]->unk_728.unk_000.unk_000.unk_01 &= ~1;
    sActivePokemon[1]->unk_728.unk_168->unk_00.unk_01 &= ~1;
    sActivePokemon[1]->unk_728.unk_000.unk_000.unk_01 &= ~1;
}

void DemoFeedScriptedInput(void) {
    static u16 D_84385758[][3] = {
        { 0x17C, 0, 0 },        { 0xA, BTN_L, 0 },  { 0xA, BTN_R, 0 }, { 0xC8, BTN_START, 0 },
        { 0xC8, BTN_START, 0 }, { 0xDC, BTN_A, 0 }, { 0, 0, 0 },
    };
    Controller* controller = &gDemoController;

    controller->buttonPressed = 0;

    if (gBattleInitStruct.unk_00 == 0) {
        gBattleInitStruct.unk_00 = D_84385758[gBattleInitFlag][0];
        if (gBattleInitStruct.unk_00 != 0) {
            controller->buttonPressed = D_84385758[gBattleInitFlag][1];
            controller->buttonDown = D_84385758[gBattleInitFlag][2];
            gBattleInitFlag++;
        }
    }

    if (gBattleInitStruct.unk_00 > 0) {
        gBattleInitStruct.unk_00--;
    }
}

void Battle_SyncMoveFlags(unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1) {
    unk_D_800FCB18* temp_v0 = &arg0->unk_654.unk_38;
    unk_D_800FCB18* temp_v1 = &arg1->unk_654.unk_38;

    if (!(arg0->unk_654.unk_38.unk_4D & 0x60)) {
        temp_v0->unk_4C &= ~8;
        temp_v1->unk_4C &= ~8;
        if (temp_v0->unk_4C & 0x12) {
            arg0->unk_654.unk_2A = 1;
        }
    } else {
        arg0->unk_654.unk_2A = 1;
    }
}

void Battle_DemoUpdate(void) {
    unk_BattlePlayerAnimState* sp24 = &sActivePokemon[0]->unk_654;
    unk_BattlePlayerAnimState* sp20 = &sActivePokemon[1]->unk_654;
    unk_D_800FCB18* sp1C = &sActivePokemon[0]->unk_654.unk_38;
    unk_D_800FCB18* sp18 = &sActivePokemon[1]->unk_654.unk_38;
    Controller* cont = &gDemoController;

    DemoFeedScriptedInput();
    Battle_SyncMoveFlags(sActivePokemon[0], sActivePokemon[1]);
    Battle_SyncMoveFlags(sActivePokemon[1], sActivePokemon[0]);

    if (cont->buttonPressed & 0x20) {
        Entities_ShowAllModels();
        TriggerPokemonAnimAndAction(sActivePokemon[0]);
        TriggerPokemonAnimAndAction(sActivePokemon[1]);
    }

    if (cont->buttonPressed & 0x10) {
        Entities_HideAllModels();
    }

    if (cont->buttonPressed & 0x1000) {
        sp24->unk_04 = 0;
        sp20->unk_04 = 0;

        if (sp24->unk_2A == 0) {
            sp1C->unk_5A = Battle_GetEntityState(0, 0);
        }

        if (sp20->unk_2A == 0) {
            sp18->unk_5A = Battle_GetEntityState(1, 0);
        }

        sp24->unk_10 = 3;
        sp20->unk_10 = 3;

        if ((sp24->unk_10 == 3) && (sp20->unk_10 == 3)) {
            DetermineTurnOrder();
        }
    }

    Battle_UpdateHPScale();

    if (cont->buttonPressed & 0x2000) {
        gBattleInitFlag = 0;
        gBattleInitStruct.unk_00 = 0;
    }

    if (cont->buttonPressed & 0x8000) {
        gBattleState.unk_00->unk_40 = 3;
    }
}

void Battle_UpdateEntityInteraction(unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1) {
    UNUSED s32 pad;
    unk_D_800FCB18* sp20 = &arg0->unk_654.unk_38;
    unk_D_800FCB18* sp1C = &arg1->unk_654.unk_38;

    if (Battle_UpdateDualEntityState(arg0, arg1) == 0) {
        if (!(sp20->unk_4D & 0x60)) {
            sp20->unk_4C &= ~8;
            sp1C->unk_4C &= ~8;
            if (!(sp20->unk_4C & 0x12)) {
                if (Battle_UpdateEntityState(arg0) == 0) {
                    if (!(sp20->unk_15 & 0x27)) {
                        if (!(sp20->unk_4C & 0x21)) {
                            if (sp1C->unk_4C & 0x20) {
                                Battle_UpdateMoveInputState(arg0, arg0->unk_654.unk_C8);
                                sp20->unk_5A = 0xFF;
                            } else {
                                Battle_ProcessMoveInput(arg0);
                            }
                        } else {
                            Battle_UpdateMoveInputState(arg0, arg0->unk_654.unk_C8);
                        }
                    } else {
                        Battle_UpdateMoveInputState(arg0, arg0->unk_654.unk_C8);
                    }
                }
            } else {
                Battle_TriggerMoveAnim(arg0);
            }
        } else {
            Battle_TriggerMoveAnim(arg0);
        }
    }
}

void Battle_UpdateEntities(void) {
    unk_BattlePlayerAnimState* sp24 = &sActivePokemon[0]->unk_654;
    unk_BattlePlayerAnimState* sp20 = &sActivePokemon[1]->unk_654;
    unk_D_800FCB18* sp1C = &sActivePokemon[0]->unk_654.unk_38;
    unk_D_800FCB18* sp18 = &sActivePokemon[1]->unk_654.unk_38;

    if (sActivePokemon[0]->unk_724->unk_000 & 2) {
        gBattleControllerId = gCurrentDamage;
        Battle_UpdateMoveSelection(sActivePokemon[0], sActivePokemon[1]);
        gCurrentDamage = gBattleControllerId;
    } else {
        Battle_UpdateEntityInteraction(sActivePokemon[0], sActivePokemon[1]);
    }

    if (sActivePokemon[1]->unk_724->unk_000 & 2) {
        gBattleControllerId = gCurrentDamage;
        Battle_UpdateMoveSelection(sActivePokemon[1], sActivePokemon[0]);
        gCurrentDamage = gBattleControllerId;
    } else {
        Battle_UpdateEntityInteraction(sActivePokemon[1], sActivePokemon[0]);
    }

    if ((sp24->unk_10 == 3) && (sp20->unk_10 == 3)) {
        if (Battle_TickCountdownTimer() != 0) {
            gBattleResultPhase = 1;
        }

        if (sp24->unk_04 == 2) {
            Battle_ClearMoveSelection(sActivePokemon[0]);
        } else {
            Battle_ApplyMoveAnimation(sActivePokemon[0]);
        }

        if (sp20->unk_04 == 2) {
            Battle_ClearMoveSelection(sActivePokemon[1]);
        } else {
            Battle_ApplyMoveAnimation(sActivePokemon[1]);
        }

        if ((sp24->unk_04 == 2) || (sp20->unk_04 == 2)) {
            DetermineTurnOrderPriority();
        } else {
            DetermineTurnOrder();
        }
    } else {
        if (!(sActivePokemon[0]->unk_724->unk_000 & 2) && !(sp1C->unk_4D & 0x60) && !(sp1C->unk_4C & 0x12)) {
            Battle_HandleConfirmInput(0);
        }

        if (!(sActivePokemon[1]->unk_724->unk_000 & 2) && !(sp18->unk_4D & 0x60) && !(sp18->unk_4C & 0x12)) {
            Battle_HandleConfirmInput(1);
        }
    }
}

void Battle_UpdateMain(void) {
    gBattleUpdateHPFlag = 0;
    if (gBattleContext.unk_0000 == 0x10) {
        Battle_DemoUpdate();
    } else {
        Battle_UpdateEntities();
    }
}

void Battle_UpdateFrame(void) {
    unk_BattlePlayerAnimState* sp1C = &sActivePokemon[0]->unk_654;
    unk_BattlePlayerAnimState* sp18 = &sActivePokemon[1]->unk_654;

    if (Battle_UpdateResultPhase() == 0) {
        sActivePokemon[0]->unk_4C8 = 0;
        sActivePokemon[1]->unk_4C8 = 0;

        if (sp1C->unk_2A != 1) {
            sp1C->unk_2A = 0;
        }

        if (sp18->unk_2A != 1) {
            sp18->unk_2A = 0;
        }

        Battle_UpdateMain();
        Battle_TickPhaseTimer();
        Battle_TickBattleTimer();
    }
}
