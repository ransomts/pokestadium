#include "fragment62.h"
#include "src/11BA0.h"
#include "src/17300.h"
#include "src/2E110.h"
#include "src/373A0.h"
#include "src/F420.h"
#include "src/memory.h"
#include "src/util.h"

void Intro_SetupCamera(CameraStruct* arg0) {
    Battle_FinishTurn();
    func_8431AFD0(arg0, 20.0f, 12800.0f);
    SetMessageFromAltTable(D_84390010[0]->unk_720, 3);
    arg0->unk_24.fovy = 40.0f;
    D_84390010[0]->unk_000.unk_000.unk_01 &= ~1;
    D_84390010[1]->unk_000.unk_000.unk_01 &= ~1;
    Vec3f_Set(&arg0->unk_60.at, 0.0f, 75.0f, 0.0f);
    Vec3f_Set(&arg0->unk_60.eye, -1.79f, 0.075f, 155.2f);
    gBattleState.unk_00->unk_54 = 1;
    RenderBattleMenuSelection();
    gBattleState.unk_00->unk_20 += 1;
}

void Intro_CheckPlayerReady(UNUSED CameraStruct* arg0) {
    if ((func_8431ADF0(0xA) != 0) && (AnimChannel_CheckAndReset(D_84390010[0]) != 0)) {
        D_84390010[0]->unk_000.unk_000.unk_01 &= ~1;
        D_84390010[1]->unk_000.unk_000.unk_01 &= ~1;
        func_84308654(D_84390010[0], 1, 0);
        Audio_PlaySoundEffect(1, 0xFE, 0);
        InitActionScriptMode3(8, D_84390010[0], D_84390010[0], 0xFF, 0xFF);
        gBattleState.unk_00->unk_20 += 1;
    }
}

void Intro_PlayerEnter(UNUSED CameraStruct* arg0) {
    D_84390010[0]->unk_000.unk_000.unk_01 &= ~1;
    D_84390010[1]->unk_000.unk_000.unk_01 &= ~1;
    if (D_84390010[0]->unk_4EC.unk_024.y == 0.0f) {
        ProcessBattleMenuSelection();
        Audio_PlaySoundEffect(1, 1, 0);
        func_84308654(D_84390010[1], 1, 0);
        InitActionScriptMode3(0xA, D_84390010[1], D_84390010[1], 0xFF, 0xFF);
        gBattleState.unk_00->unk_20 += 1;
    }
}

void Intro_OpponentEnter(CameraStruct* arg0) {
    Vec3f sp3C;

    D_84390010[0]->unk_000.unk_000.unk_01 &= ~1;
    D_84390010[1]->unk_000.unk_000.unk_01 &= ~1;

    if (D_84390010[1]->unk_4EC.unk_024.y == 0.0f) {
        arg0->unk_24.fovy = 30.0f;
        func_84308654(D_84390010[0], 2, 0);
        InitActionScriptMode3(0xB, D_84390010[0], D_84390010[0], 0xFF, 0xFF);
        Vec3f_Set(&sp3C, -150.0f, 5.0f, 0.0f);
        func_8431BAB4(D_84390010[0], arg0, sp3C, 0, 0, 0.0f, 0.0f);
        func_8431BB80(arg0, sp3C, gBattleState.unk_00->unk_56 = 0x71C, 0x4000, gBattleState.unk_00->unk_84 = 300.0f, 0.0f);
        gBattleState.unk_00->unk_20 += 1;
    }
}

void Intro_CameraPanAndZoom(CameraStruct* arg0) {
    Vec3f sp2C;

    Vec3f_Set(&sp2C, -150.0f, 5.0f, 0.0f);
    D_84390010[0]->unk_000.unk_000.unk_01 &= ~1;
    D_84390010[1]->unk_000.unk_000.unk_01 &= ~1;
    Math_ExponentialApproach(&gBattleState.unk_00->unk_84, 40.0f, 0.1f);
    Math_StepTowards(&gBattleState.unk_00->unk_56, 0xB6, 0x1E);
    func_8431BB80(arg0, sp2C, gBattleState.unk_00->unk_56, 0x4000, gBattleState.unk_00->unk_84, 0.0f);

    if ((gBattleState.unk_00->unk_56 >= 0x2E) && (D_84390010[0]->unk_4EC.unk_024.y == 2.5f)) {
        Audio_PlaySoundEffect(2, 0, 0);
        D_84390010[0]->unk_4EC.unk_000.unk_02 |= 0x20;
        gBattleState.unk_00->unk_20 += 1;
    }
}

void Intro_WaitForAnimCompletion(UNUSED CameraStruct* arg0) {
    D_84390010[0]->unk_000.unk_000.unk_01 &= ~1;
    D_84390010[1]->unk_000.unk_000.unk_01 &= ~1;
    if (func_800174E4(&D_84390010[0]->unk_4EC) == 1) {
        gBattleState.unk_00->unk_20 += 1;
    }
}

void Intro_DisplayPokemonInfo(CameraStruct* arg0) {
    unk_D_84390010_654* sp2C = &D_84390010[0]->unk_654;
    unk_D_800AE540_0004* sp28 = D_84390010[0]->unk_720->unk_08[sp2C->unk_2C];

    D_84390010[0]->unk_728.unk_168->unk_00.unk_01 |= 1;
    D_84390010[0]->unk_728.unk_000.unk_000.unk_01 |= 1;
    TriggerPokemonAnimAndAction(D_84390010[0]);
    D_84390010[0]->unk_000.unk_000.unk_01 &= ~1;
    D_84390010[1]->unk_000.unk_000.unk_01 &= ~1;
    InitActionScriptMode3(3, D_84390010[0], D_84390010[0], 0xFF, 0xFF);
    D_84390010[0]->unk_000.unk_000.unk_01 |= 1;
    D_84390010[0]->unk_4EC.unk_000.unk_01 &= ~1;
    Battle_PlayMoveEffect(D_84390010[0], arg0, 3);
    ExecuteAnimStateHandlers(D_84390010[0], 0x10);
    gBattleState.unk_00->unk_2C = 0;
    MessageBank_SetPointer_0x14_0x2A(0x19, (u32)sp28->unk_01C[sp2C->unk_18].unk_30);
    WriteMessageCharOrString(D_843901A0->unk_088, 0x21);
    Dialog_SetMode(0xC);
    ProcessEntityAudioInfo(D_84390010[0]);
    gBattleState.unk_00->unk_10 = 0;
    gBattleState.unk_00->unk_20 += 1;
}

void Intro_PostInfoDelay(CameraStruct* arg0) {
    if (gBattleState.unk_00->unk_10++ == 1) {
        Battle_PlayMoveEffect(D_84390010[0], arg0, 3);
    }

    D_84390010[0]->unk_728.unk_168->unk_00.unk_01 &= ~1;
    D_84390010[0]->unk_728.unk_000.unk_000.unk_01 &= ~1;
    D_84390010[1]->unk_000.unk_000.unk_01 &= ~1;
    func_8431C750(arg0, D_84390010[0]);

    if (CanAnimProceedWithChannel(D_84390010[0], 0x3C) != 0) {
        gBattleState.unk_00->unk_20 += 1;
    }
}

void Opponent_DisplayPokemonInfo(CameraStruct* arg0) {
    unk_D_84390010_654* sp2C = &D_84390010[1]->unk_654;
    unk_D_800AE540_0004* sp28 = D_84390010[1]->unk_720->unk_08[sp2C->unk_2C];

    D_84390010[1]->unk_728.unk_168->unk_00.unk_01 |= 1;
    D_84390010[1]->unk_728.unk_000.unk_000.unk_01 |= 1;
    TriggerPokemonAnimAndAction(D_84390010[1]);
    Audio_PlaySoundEffect(2, 0, 0);
    InitActionScriptMode3(3, D_84390010[1], D_84390010[1], 0xFF, 0xFF);
    Battle_FinishTurn();
    D_84390010[1]->unk_000.unk_000.unk_01 |= 1;
    Battle_PlayMoveEffect(D_84390010[1], arg0, 3);
    ExecuteAnimStateHandlers(D_84390010[1], 0x10);
    gBattleState.unk_00->unk_10 = 0;
    gBattleState.unk_00->unk_2C = 1;
    MessageBank_SetPointer_0x14_0x2A(0x19, (u32)sp28->unk_01C[sp2C->unk_18].unk_30);
    WriteMessageCharOrString(D_843901A0->unk_088, 0x21);
    if (gBattleContext.unk_0000 != 8) {
        Dialog_SetMode(0xC);
    }
    ProcessEntityAudioInfo(D_84390010[1]);
    gBattleState.unk_00->unk_20 += 1;
}

void Opponent_PostInfoDelay(CameraStruct* arg0) {
    if (gBattleState.unk_00->unk_10++ == 1) {
        Battle_PlayMoveEffect(D_84390010[1], arg0, 3);
    }
    D_84390010[1]->unk_728.unk_168->unk_00.unk_01 &= ~1;
    D_84390010[1]->unk_728.unk_000.unk_000.unk_01 &= ~1;
    D_84390010[0]->unk_000.unk_000.unk_01 &= ~1;
    func_8431C750(arg0, D_84390010[1]);
    if (CanAnimProceedWithChannel(D_84390010[1], 0x3C) != 0) {
        Battle_UpdateAfterTurn();
        gBattleState.unk_00->unk_20 += 1;
    }
}

void Intro_End(UNUSED CameraStruct* arg0) {
}

void UnusedFunction(void) {
}

void Intro_StateMachine(CameraStruct* arg0) {
    switch (gBattleState.unk_00->unk_20) {
        case 0:
            Intro_SetupCamera(arg0);

        case 1:
            Intro_CheckPlayerReady(arg0);
            break;

        case 2:
            Intro_PlayerEnter(arg0);
            break;

        case 3:
            Intro_OpponentEnter(arg0);
            break;

        case 4:
            Intro_CameraPanAndZoom(arg0);
            break;

        case 5:
            Intro_WaitForAnimCompletion(arg0);
            break;

        case 6:
            Intro_DisplayPokemonInfo(arg0);
            break;

        case 7:
            Intro_PostInfoDelay(arg0);
            break;

        case 8:
            Opponent_DisplayPokemonInfo(arg0);
            break;

        case 9:
            Opponent_PostInfoDelay(arg0);
            break;

        case 10:
            Intro_End(arg0);
            break;
    }
}
