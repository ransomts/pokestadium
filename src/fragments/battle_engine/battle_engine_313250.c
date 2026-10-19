#include "battle_engine.h"
#include "src/11BA0.h"
#include "src/17300.h"
#include "src/2E110.h"
#include "src/373A0.h"
#include "src/F420.h"
#include "src/memory.h"
#include "src/util.h"

void BattleScene_IntroSetupCamera(CameraStruct* arg0) {
    BattleScene_ResetCameraFrameCounter();
    BattleScene_SetCameraClipPlanes(arg0, 20.0f, 12800.0f);
    BattleAnim_LoadModeResourceList(sActivePokemon[0]->pokemonAnimation, 3);
    arg0->unk_24.fovy = 40.0f;
    sActivePokemon[0]->unk_000.unk_000.unk_01 &= ~1;
    sActivePokemon[1]->unk_000.unk_000.unk_01 &= ~1;
    Vec3f_SetComponentsDuplicate(&arg0->unk_60.at, 0.0f, 75.0f, 0.0f);
    Vec3f_SetComponentsDuplicate(&arg0->unk_60.eye, -1.79f, 0.075f, 155.2f);
    gBattleScene.posX->unk_54 = 1;
    BattleScene_StartBattleMusic();
    gBattleScene.posX->unk_20 += 1;
}

void BattleScene_IntroSendOutFirstMon(UNUSED CameraStruct* arg0) {
    if ((BattleScene_AdvanceCameraFrameCounterUntil(0xA) != 0) && (BattleAnim_TryRegisterAssetTables(sActivePokemon[0]) != 0)) {
        sActivePokemon[0]->unk_000.unk_000.unk_01 &= ~1;
        sActivePokemon[1]->unk_000.unk_000.unk_01 &= ~1;
        BattleScene_SetParticipantModelFlags(sActivePokemon[0], 1, 0);
        Audio_PlayCommand(1, 0xFE, 0);
        BattleAnim_QueueEffectList3(8, sActivePokemon[0], sActivePokemon[0], 0xFF, 0xFF);
        gBattleScene.posX->unk_20 += 1;
    }
}

void BattleScene_IntroSendOutSecondMon(UNUSED CameraStruct* arg0) {
    sActivePokemon[0]->unk_000.unk_000.unk_01 &= ~1;
    sActivePokemon[1]->unk_000.unk_000.unk_01 &= ~1;
    if (sActivePokemon[0]->effectGraphNode.unk_024.y == 0.0f) {
        BattleScene_SelectBattleMusic();
        Audio_PlayCommand(1, 1, 0);
        BattleScene_SetParticipantModelFlags(sActivePokemon[1], 1, 0);
        BattleAnim_QueueEffectList3(0xA, sActivePokemon[1], sActivePokemon[1], 0xFF, 0xFF);
        gBattleScene.posX->unk_20 += 1;
    }
}

void BattleScene_IntroNarrowFov(CameraStruct* arg0) {
    Vec3f sp3C;

    sActivePokemon[0]->unk_000.unk_000.unk_01 &= ~1;
    sActivePokemon[1]->unk_000.unk_000.unk_01 &= ~1;

    if (sActivePokemon[1]->effectGraphNode.unk_024.y == 0.0f) {
        arg0->unk_24.fovy = 30.0f;
        BattleScene_SetParticipantModelFlags(sActivePokemon[0], 2, 0);
        BattleAnim_QueueEffectList3(0xB, sActivePokemon[0], sActivePokemon[0], 0xFF, 0xFF);
        Vec3f_SetComponentsDuplicate(&sp3C, -150.0f, 5.0f, 0.0f);
        BattleScene_SetCameraAtFromAnchor(sActivePokemon[0], arg0, sp3C, 0, 0, 0.0f, 0.0f);
        BattleScene_SetCameraEyeFromPosition(arg0, sp3C, gBattleScene.posX->unk_56 = 0x71C, 0x4000, gBattleScene.posX->unk_84 = 300.0f, 0.0f);
        gBattleScene.posX->unk_20 += 1;
    }
}

void BattleScene_IntroPanCamera(CameraStruct* arg0) {
    Vec3f sp2C;

    Vec3f_SetComponentsDuplicate(&sp2C, -150.0f, 5.0f, 0.0f);
    sActivePokemon[0]->unk_000.unk_000.unk_01 &= ~1;
    sActivePokemon[1]->unk_000.unk_000.unk_01 &= ~1;
    BattleAnim_ApproachF(&gBattleScene.posX->unk_84, 40.0f, 0.1f);
    BattleAnim_StepToS16(&gBattleScene.posX->unk_56, 0xB6, 0x1E);
    BattleScene_SetCameraEyeFromPosition(arg0, sp2C, gBattleScene.posX->unk_56, 0x4000, gBattleScene.posX->unk_84, 0.0f);

    if ((gBattleScene.posX->unk_56 >= 0x2E) && (sActivePokemon[0]->effectGraphNode.unk_024.y == 2.5f)) {
        Audio_PlayCommand(2, 0, 0);
        sActivePokemon[0]->effectGraphNode.unk_000.posY |= 0x20;
        gBattleScene.posX->unk_20 += 1;
    }
}

void BattleScene_IntroWaitFirstMonAnim(UNUSED CameraStruct* arg0) {
    sActivePokemon[0]->unk_000.unk_000.unk_01 &= ~1;
    sActivePokemon[1]->unk_000.unk_000.unk_01 &= ~1;
    if (ModelAnim_IsAnimationDone(&sActivePokemon[0]->effectGraphNode) == 1) {
        gBattleScene.posX->unk_20 += 1;
    }
}

void BattleScene_IntroRevealFirstMon(CameraStruct* arg0) {
    BattlePlayerAnimState* sp2C = &sActivePokemon[0]->animationState;
    BattleAI_TeamContext* sp28 = sActivePokemon[0]->pokemonAnimation->unk_08[sp2C->unk_2C];

    sActivePokemon[0]->unk_728.unk_168->posX.unk_01 |= 1;
    sActivePokemon[0]->unk_728.unk_000.unk_000.unk_01 |= 1;
    BattleScene_TriggerOwnerModelAnimation(sActivePokemon[0]);
    sActivePokemon[0]->unk_000.unk_000.unk_01 &= ~1;
    sActivePokemon[1]->unk_000.unk_000.unk_01 &= ~1;
    BattleAnim_QueueEffectList3(3, sActivePokemon[0], sActivePokemon[0], 0xFF, 0xFF);
    sActivePokemon[0]->unk_000.unk_000.unk_01 |= 1;
    sActivePokemon[0]->effectGraphNode.unk_000.unk_01 &= ~1;
    BattleScene_SelectCameraFollowPreset(sActivePokemon[0], arg0, 3);
    BattleScene_EnterStateRow(sActivePokemon[0], 0x10);
    gBattleScene.posX->unk_2C = 0;
    Text_SetStringToken(0x19, (u32)sp28->unk_01C[sp2C->unk_18].unk_30);
    Battle_QueueMessage(gBattleMessageQueues->unk_088, 0x21);
    BattleBox_Open(0xC);
    Battle_TriggerTrainerPresentationCue(sActivePokemon[0]);
    gBattleScene.posX->unk_10 = 0;
    gBattleScene.posX->unk_20 += 1;
}

void BattleScene_IntroFirstMonSettle(CameraStruct* arg0) {
    if (gBattleScene.posX->unk_10++ == 1) {
        BattleScene_SelectCameraFollowPreset(sActivePokemon[0], arg0, 3);
    }

    sActivePokemon[0]->unk_728.unk_168->posX.unk_01 &= ~1;
    sActivePokemon[0]->unk_728.unk_000.unk_000.unk_01 &= ~1;
    sActivePokemon[1]->unk_000.unk_000.unk_01 &= ~1;
    BattleScene_ReframeAndRecomputeDistanceForSwitch(arg0, sActivePokemon[0]);

    if (BattleScene_IsRowWaitCompleteWithEventCount(sActivePokemon[0], 0x3C) != 0) {
        gBattleScene.posX->unk_20 += 1;
    }
}

void BattleScene_IntroRevealSecondMon(CameraStruct* arg0) {
    BattlePlayerAnimState* sp2C = &sActivePokemon[1]->animationState;
    BattleAI_TeamContext* sp28 = sActivePokemon[1]->pokemonAnimation->unk_08[sp2C->unk_2C];

    sActivePokemon[1]->unk_728.unk_168->posX.unk_01 |= 1;
    sActivePokemon[1]->unk_728.unk_000.unk_000.unk_01 |= 1;
    BattleScene_TriggerOwnerModelAnimation(sActivePokemon[1]);
    Audio_PlayCommand(2, 0, 0);
    BattleAnim_QueueEffectList3(3, sActivePokemon[1], sActivePokemon[1], 0xFF, 0xFF);
    BattleScene_ResetCameraFrameCounter();
    sActivePokemon[1]->unk_000.unk_000.unk_01 |= 1;
    BattleScene_SelectCameraFollowPreset(sActivePokemon[1], arg0, 3);
    BattleScene_EnterStateRow(sActivePokemon[1], 0x10);
    gBattleScene.posX->unk_10 = 0;
    gBattleScene.posX->unk_2C = 1;
    Text_SetStringToken(0x19, (u32)sp28->unk_01C[sp2C->unk_18].unk_30);
    Battle_QueueMessage(gBattleMessageQueues->unk_088, 0x21);
    if (gSessionContext.unk_0000 != 8) {
        BattleBox_Open(0xC);
    }
    Battle_TriggerTrainerPresentationCue(sActivePokemon[1]);
    gBattleScene.posX->unk_20 += 1;
}

void BattleScene_IntroSecondMonSettle(CameraStruct* arg0) {
    if (gBattleScene.posX->unk_10++ == 1) {
        BattleScene_SelectCameraFollowPreset(sActivePokemon[1], arg0, 3);
    }
    sActivePokemon[1]->unk_728.unk_168->posX.unk_01 &= ~1;
    sActivePokemon[1]->unk_728.unk_000.unk_000.unk_01 &= ~1;
    sActivePokemon[0]->unk_000.unk_000.unk_01 &= ~1;
    BattleScene_ReframeAndRecomputeDistanceForSwitch(arg0, sActivePokemon[1]);
    if (BattleScene_IsRowWaitCompleteWithEventCount(sActivePokemon[1], 0x3C) != 0) {
        BattleScene_BeginBattlePhase();
        gBattleScene.posX->unk_20 += 1;
    }
}

void BattleScene_IntroStepNop(UNUSED CameraStruct* arg0) {
}

void BattleScene_IntroInitNop(void) {
}

void BattleScene_UpdateIntroSequence(CameraStruct* arg0) {
    switch (gBattleScene.posX->unk_20) {
        case 0:
            BattleScene_IntroSetupCamera(arg0);

        case 1:
            BattleScene_IntroSendOutFirstMon(arg0);
            break;

        case 2:
            BattleScene_IntroSendOutSecondMon(arg0);
            break;

        case 3:
            BattleScene_IntroNarrowFov(arg0);
            break;

        case 4:
            BattleScene_IntroPanCamera(arg0);
            break;

        case 5:
            BattleScene_IntroWaitFirstMonAnim(arg0);
            break;

        case 6:
            BattleScene_IntroRevealFirstMon(arg0);
            break;

        case 7:
            BattleScene_IntroFirstMonSettle(arg0);
            break;

        case 8:
            BattleScene_IntroRevealSecondMon(arg0);
            break;

        case 9:
            BattleScene_IntroSecondMonSettle(arg0);
            break;

        case 10:
            BattleScene_IntroStepNop(arg0);
            break;
    }
}
