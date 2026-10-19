#include "fragment62.h"
#include "src/17300.h"
#include "src/F420.h"

typedef struct CameraPreset {
    /* 0x00 */ u8 unk_00;
    /* 0x04 */ f32 unk_04;
    /* 0x08 */ s16 unk_08;
    /* 0x0A */ s16 unk_0A;
    /* 0x0C */ f32 unk_0C;
} CameraPreset; // size = 0x10

static CameraPreset gCameraPresets[] = {
    {
        0x00,
        2002.1199951171875f,
        1367,
        -20914,
        50.0f,
    },
    {
        0x01,
        1693.1199951171875f,
        183,
        -11871,
        50.0f,
    },
    {
        0x02,
        1934.97998046875f,
        1217,
        8182,
        50.0f,
    },
    {
        0x03,
        1733.780029296875f,
        397,
        6520,
        50.0f,
    },
    {
        0x04,
        1102.3900146484375f,
        1577,
        -3562,
        50.0f,
    },
    {
        0x05,
        1425.7900390625f,
        2285,
        -5775,
        50.0f,
    },
    {
        0x06,
        871.3599853515625f,
        1825,
        -8898,
        50.0f,
    },
    {
        0x07,
        1170.8199462890625f,
        4982,
        -6725,
        50.0f,
    },
    {
        0x11,
        1645.5699462890625f,
        7861,
        -122,
        50.0f,
    },
    {
        0x01,
        1741.530029296875f,
        6993,
        -6029,
        50.0f,
    },
    {
        0x06,
        1608.3199462890625f,
        6419,
        -16201,
        50.0f,
    },
    {
        0x00,
        1122.8599853515625f,
        2584,
        -14668,
        50.0f,
    },
    {
        0x00,
        1667.239990234375f,
        5360,
        4438,
        50.0f,
    },
    {
        0x00,
        1315.9599609375f,
        3001,
        -7883,
        50.0f,
    },
    {
        0x00,
        1575.4300537109375f,
        5834,
        10901,
        50.0f,
    },
    {
        0x00,
        719.8599853515625f,
        3047,
        -16384,
        50.0f,
    },
    {
        0x00,
        939.3900146484375f,
        2300,
        0,
        50.0f,
    },
    {
        0x01,
        560.239990234375f,
        773,
        -8863,
        50.0f,
    },
    {
        0x01,
        2002.1199951171875f,
        1367,
        -20914,
        30.0f,
    },
    {
        0x01,
        2002.1199951171875f,
        1367,
        -20914,
        30.0f,
    },
};

s32 Camera_IsCloseViewCondition(void) {
    if (((GetModelHeight(sActivePokemon[0]) + GetModelHeight(sActivePokemon[1])) <= 85.0f) &&
        (GetModelBaseY(sActivePokemon[0]) == 0.0f) && (GetModelBaseY(sActivePokemon[1]) == 0.0f) &&
        (sActivePokemon[0]->unk_000.unk_024.y == 0.0f) && (sActivePokemon[1]->unk_000.unk_024.y == 0.0f)) {
        return 1;
    }
    return 0;
}

s32 BattleScene_SkipIntroIfFainted(UNUSED unk_BattlePlayerEntity* arg0, CameraStruct* arg1) {
    unk_BattlePlayerAnimState* ptr = &sActivePokemon[gBattleState.unk_00->unk_2C]->unk_654;

    if ((ptr->unk_2D == 0x10) || ((ptr->unk_34 & 0x4000) != 0)) {
        Camera_UpdateStateMachine(arg1);
        return 1;
    }
    return 0;
}

s32 BattleScene_IsEitherActivePokemonFainted(UNUSED unk_BattlePlayerEntity* arg0, UNUSED CameraStruct* arg1) {
    unk_BattlePlayerAnimState* ptr = &sActivePokemon[gBattleState.unk_00->unk_2C]->unk_654;
    s32 idx = gBattleState.unk_00->unk_2C == 0;
    unk_BattlePlayerAnimState* ptr2 = &sActivePokemon[idx]->unk_654;

    if ((ptr->unk_34 & 0x4000) || (ptr2->unk_34 & 0x4000)) {
        return 1;
    }
    return 0;
}

void Camera_SetCloseView(CameraStruct* arg0) {
    Battle_FinishTurn();
    arg0->unk_24.fovy = 50.0f;
    if (Camera_IsCloseViewCondition() != 0) {
        Camera_SetEyePosition(arg0, gCameraCloseSettings, 0, 0, 0.0f, 0.0f);
        Camera_SetEyeAndPanTargets(arg0, gCameraCloseSettings, 0x5B0, 0, 550.0f, 0.0f);
    } else {
        Camera_SetEyePosition(arg0, gCameraFarSettings, 0, 0, 0.0f, 0.0f);
        Camera_SetEyeAndPanTargets(arg0, gCameraFarSettings, 0x5B0, 0, 550.0f, 0.0f);
    }
    arg0->unk_60.eye.z *= 0.6;
    gBattleState.unk_00->unk_20++;
}

void Camera_SetFarView(CameraStruct* arg0) {
    Battle_FinishTurn();
    arg0->unk_24.fovy = 30.0f;
    if (Camera_IsCloseViewCondition() != 0) {
        Camera_SetEyePosition(arg0, gCameraCloseSettings, 0, 0, 0.0f, 0.0f);
        Camera_SetEyeAndPanTargets(arg0, gCameraCloseSettings, 0x1A4E, 0, 1000.0f, 0.0f);
    } else {
        Camera_SetEyePosition(arg0, gCameraFarSettings, 0, 0, 0.0f, 0.0f);
        Camera_SetEyeAndPanTargets(arg0, gCameraFarSettings, 0x1A4E, 0, 1000.0f, 0.0f);
    }
    gBattleState.unk_00->unk_20++;
}

void BattleScene_IntroCameraStep4Or6(CameraStruct* arg0, s32 arg1) {
    UNUSED s32 pad;
    f32 sp50;
    f32 sp4C;
    s16 sp4A;
    unk_BattlePlayerAnimState* sp44;
    UNUSED s32 pad2;
    u16 sp3E;
    unk_BattlePlayerEntity* temp_s0;

    sp44 = &sActivePokemon[arg1]->unk_654;
    Battle_ResetCameraState();
    SetCurrentPlayerIndex(arg1);
    temp_s0 = sActivePokemon[gBattleState.unk_00->unk_2C];

    if (BattleScene_SkipIntroIfFainted(temp_s0, arg0) == 0) {
        GetEntityCenterPosition(temp_s0, &gBattleState.unk_00->unk_D0);
        if (!(sp44->unk_34 & 2)) {
            ExecuteAnimStateHandlers(temp_s0, 1);
        }

        sp50 = GetScaledWidth(temp_s0) * 3.5f;
        sp3E = Math_RandomU16Scaled(3);
        sp50 *= ((GetScaledHeight(temp_s0) * 0.5f * sp3E) + 1.0f);

        if (sp50 > 325.0f) {
            sp50 = 325.0f;
        }

        sp3E = Math_RandomU16Scaled(4);
        sp4C = Battle_GetEntityHeight(temp_s0) * sp3E;
        sp4A = Math_RandomU16Scaled(0xB4);

        if (sp44->unk_34 & 0x200) {
            sp4C = 0.0f;
        }

        Camera_SetLookAtPosition(temp_s0, arg0, gBattleState.unk_00->unk_D0, 0, 0, 0, 0.0f);
        Camera_SetEyePositionOffset(arg0, gBattleState.unk_00->unk_D0, 0, 0x4000 - (sp4A * 0xB6), sp50, sp4C);
        Battle_UpdateCameraMatrix(arg0);
        ConfigureCameraForModel(temp_s0, arg0);

        if (temp_s0->unk_000.unk_01A == 0x5F) {
            arg0->unk_24.fovy = 50.0f;
        } else {
            arg0->unk_24.fovy = 30.0f;
        }
        gBattleState.unk_00->unk_20++;
    }
}

void BattleScene_IntroCameraStep8Or10(CameraStruct* arg0, s32 arg1) {
    UNUSED s32 pad[2];
    unk_D_86B0C160* sp24;
    s32 var_a0;
    unk_BattlePlayerEntity* temp_s0;

    Battle_ResetCameraState();
    SetCurrentPlayerIndex(arg1);
    temp_s0 = sActivePokemon[gBattleState.unk_00->unk_2C];

    if (BattleScene_SkipIntroIfFainted(temp_s0, arg0) == 0) {
        if (temp_s0->unk_654.unk_34 & 0x200) {
            sp24 = &gCameraFovyPresetSpecial[0];
        } else {
            var_a0 = Math_RandomU16Scaled(5);
            if (var_a0 >= 5) {
                var_a0 = 0;
            }
            sp24 = &gCameraFovyPresetRandom[var_a0];
        }
        arg0->unk_24.fovy = sp24->unk_30;
        GetEntityCenterPosition(temp_s0, &gCameraPreset.unk_00);
        Battle_PlayCameraTransition(sp24, arg0, temp_s0);
        Battle_ApplyCameraSettings(arg0, temp_s0, 1);
        Battle_UpdateCameraMatrix(arg0);
        gBattleState.unk_00->unk_20++;
    }
}

void BattleScene_IntroCameraStep12Or14(CameraStruct* arg0, s32 arg1) {
    arg0->unk_24.fovy = 30.0f;
    SetCurrentPlayerIndex(arg1);
    if (BattleScene_SkipIntroIfFainted(sActivePokemon[arg1], arg0) == 0) {
        SetupBattleCamera(arg0, arg1);
        gBattleState.unk_00->unk_20++;
    }
}

void BattleScene_IntroCameraStep16(CameraStruct* arg0) {
    SetCurrentPlayerIndex(gBattleState.unk_00->unk_54 - 1);
    if (BattleScene_IsEitherActivePokemonFainted(sActivePokemon[gBattleState.unk_00->unk_2C], arg0) != 0) {
        gBattleState.unk_00->unk_54 = 0;
        Camera_UpdateStateMachine(arg0);
    } else {
        Camera_SetEntityView(arg0, gBattleState.unk_00->unk_2C);
        gBattleState.unk_00->unk_20++;
    }
}

void BattleScene_IntroCameraStep18(CameraStruct* arg0) {
    SetCurrentPlayerIndex(gBattleState.unk_00->unk_2C);
    gBattleState.unk_00->unk_54 = 0;
    if (BattleScene_IsEitherActivePokemonFainted(sActivePokemon[gBattleState.unk_00->unk_2C], arg0) != 0) {
        Camera_UpdateStateMachine(arg0);
    } else {
        Camera_SetEntityView(arg0, gBattleState.unk_00->unk_2C);
        gBattleState.unk_00->unk_20++;
    }
}

void Camera_SetFromBattleContext(CameraStruct* arg0) {
    s16 var_v1;

    Battle_FinishTurn();
    if (gBattleContext.unk_0000 == 0x10) {
        var_v1 = gCameraPresets[gBattleContext.unk_0001].unk_00;
        if (gBattleContext.unk_0001 == 7) {
            var_v1 += gBattleContext.unk_0002;
        }
    } else {
        var_v1 = gCameraPresets[gBattleContext.unk_0000].unk_00;
        if (gBattleContext.unk_0000 == 7) {
            var_v1 += gBattleContext.unk_0002;
        }
    }
    arg0->unk_24.fovy = gCameraPresets[var_v1].unk_0C;
    Vec3f_Set(&arg0->unk_60.at, 0.0f, 10.0f, 0.0f);
    Camera_SetViewParameters(&arg0->unk_60.at, &arg0->unk_60.eye, gCameraPresets[var_v1].unk_04, gCameraPresets[var_v1].unk_08,
                  gCameraPresets[var_v1].unk_0A);
    gBattleState.unk_00->unk_20++;
}

void BattleScene_IntroCameraStep22Or24(CameraStruct* arg0, s32 arg1) {
    UNUSED s32 pad[5];
    s32 var_v1;
    unk_BattlePlayerEntity* temp_s0;
    f32 tmp1;
    s16 tmp4;
    s16 tmp3;
    f32 tmp2;

    Camera_SetClippingPlanes(arg0, 10.0f, 12800.0f);
    arg0->unk_24.fovy = 60.0f;
    SetCurrentPlayerIndex(arg1);
    temp_s0 = sActivePokemon[arg1];

    if (BattleScene_SkipIntroIfFainted(temp_s0, arg0) == 0) {
        if ((temp_s0->unk_000.unk_01A == 0x98) || (temp_s0->unk_654.unk_34 & 2)) {
            Camera_UpdateStateMachine(arg0);
            return;
        }

        if ((temp_s0->unk_000.unk_01A == 0x5F) && (arg1 == 1)) {
            var_v1 = 0x97;
        } else {
            var_v1 = (temp_s0->unk_000.unk_01A - 1) & 0xFF;
        }

        tmp2 = (gAnimDataSetC[arg1]->unk_00.y + temp_s0->unk_000.unk_024.y) + gCameraOffsetTable[var_v1].z;
        tmp1 = ((gAnimDataSetC[arg1]->unk_00.z + gCameraOffsetTable[var_v1].y) * temp_s0->unk_4B0) + temp_s0->unk_000.unk_024.x;

        Vec3f_Set(&arg0->unk_60.at, tmp1, tmp2, temp_s0->unk_000.unk_024.z);

        tmp1 = gAnimDataSetC[gBattleState.unk_00->unk_2C]->unk_00.x * gCameraOffsetTable[var_v1].x;
        tmp4 = gAnimDataSetC[gBattleState.unk_00->unk_2C]->unk_0C;
        tmp3 = (temp_s0->unk_4B0 * gAnimDataSetC[gBattleState.unk_00->unk_2C]->unk_0E) + GetPlayerSideYaw(temp_s0);

        Camera_SetViewParameters(&arg0->unk_60.at, &arg0->unk_60.eye, tmp1, tmp4, tmp3);
        gBattleState.unk_00->unk_20++;
    }
}

void Camera_UpdateStateMachine(CameraStruct* arg0) {
    UNUSED s32 pad[2];
    s32 sp20[] = {
        // D_84385B20
        0x00000000, 0x00000008, 0x00000004, 0x00000014, 0x0000000A,
        0x00000006, 0x00000002, 0x00000016, 0x00000018, 0x000000FF,
    };

    Camera_SetClippingPlanes(arg0, 20.0f, 12800.0f);
    arg0->unk_24.fovy = 30.0f;
    if ((gBattleState.unk_00->unk_54 != 0) && (Battle_CheckEntityHeightDiff(arg0) != 0)) {
        gBattleState.unk_00->unk_20 = 0x10;
    } else {
        gBattleState.unk_00->unk_54 = 0;
        if (sp20[gBattleState.unk_00->unk_0C] == 0xFF) {
            gBattleState.unk_00->unk_0C = 0;
        }
        gBattleState.unk_00->unk_20 = sp20[gBattleState.unk_00->unk_0C];
        gBattleState.unk_00->unk_0C++;
    }

    Battle_ApplyAnimEffect(*sActivePokemon);
    Battle_ApplyAnimEffect(sActivePokemon[1]);
    Battle_FinishTurn();

    switch (gBattleState.unk_00->unk_20) {
        case 0:
            Camera_SetCloseView(arg0);
            break;

        case 2:
            Camera_SetFarView(arg0);
            break;

        case 4:
            BattleScene_IntroCameraStep4Or6(arg0, 0);
            break;

        case 6:
            BattleScene_IntroCameraStep4Or6(arg0, 1);
            break;

        case 8:
            BattleScene_IntroCameraStep8Or10(arg0, 0);
            break;

        case 10:
            BattleScene_IntroCameraStep8Or10(arg0, 1);
            break;

        case 12:
            BattleScene_IntroCameraStep12Or14(arg0, 0);
            break;

        case 14:
            BattleScene_IntroCameraStep12Or14(arg0, 1);
            break;

        case 16:
            BattleScene_IntroCameraStep16(arg0);
            break;

        case 18:
            BattleScene_IntroCameraStep18(arg0);
            break;

        case 20:
            Camera_SetFromBattleContext(arg0);
            break;

        case 22:
            BattleScene_IntroCameraStep22Or24(arg0, 0);
            break;

        case 24:
            BattleScene_IntroCameraStep22Or24(arg0, 1);
            break;
    }
}

void BattleScene_IntroCameraRollStep(CameraStruct* arg0) {
    arg0->unk_24.fovy = 50.0f;
    if (Camera_SmoothPanToAngle(arg0, 0xB6, 0x78DC) != 0) {
        Camera_UpdateStateMachine(arg0);
    } else {
        arg0->unk_60.eye.z *= 0.6;
    }
}

void BattleScene_IntroCameraRollStepNoFov(CameraStruct* arg0) {
    if (Camera_SmoothPanToAngle(arg0, 0xB6, 0x78DC) != 0) {
        Camera_UpdateStateMachine(arg0);
    }
}

void BattleScene_IntroCameraAnimationHoldStep(CameraStruct* arg0) {
    UNUSED s32 pad;
    unk_BattlePlayerAnimState* sp18 = &sActivePokemon[gBattleState.unk_00->unk_2C]->unk_654;

    if ((sp18->unk_2D == 0x10) || ((sp18->unk_34 & 0x4000) != 0)) {
        Camera_UpdateStateMachine(arg0);
        return;
    }

    if (!(sp18->unk_34 & 0x200)) {
        Battle_AdvanceCameraTimelineSlow(arg0, sActivePokemon[gBattleState.unk_00->unk_2C]);
    }

    if ((sp18->unk_34 & 1) || (sp18->unk_34 & 2) || (sActivePokemon[gBattleState.unk_00->unk_2C]->unk_000.unk_01A == 0x98)) {
        if (Battle_WaitForAnimation(0x5A) != 0) {
            Camera_UpdateStateMachine(arg0);
        }
    } else if (GraphNode_IsAnimationFinished(&sActivePokemon[gBattleState.unk_00->unk_2C]->unk_000) != 0) {
        Camera_UpdateStateMachine(arg0);
    }
}

void BattleScene_IntroCameraPresetHoldStep(CameraStruct* arg0) {
    unk_BattlePlayerEntity* sp1C = sActivePokemon[gBattleState.unk_00->unk_2C];

    if ((sp1C->unk_654.unk_2D == 0x10) || (sp1C->unk_654.unk_34 & 0x4000)) {
        Camera_UpdateStateMachine(arg0);
    } else if ((Battle_WaitForAnimation(0x5A) != 0) || (Battle_CheckPlayerAction(arg0, sp1C, 1, 0) != 0)) {
        Camera_UpdateStateMachine(arg0);
    }
}

void BattleScene_IntroCameraWideHoldStep(CameraStruct* arg0) {
    unk_BattlePlayerAnimState* ptr = &sActivePokemon[gBattleState.unk_00->unk_2C]->unk_654;

    if ((ptr->unk_2D == 0x10) || (ptr->unk_34 & 0x4000)) {
        Camera_UpdateStateMachine(arg0);
    } else {
        arg0->unk_24.fovy = 60.0f;
        if (Battle_WaitForAnimation(0x3C) != 0) {
            Camera_UpdateStateMachine(arg0);
        }
    }
}

void BattleScene_IntroCameraHeightShotSwapStep(CameraStruct* arg0) {
    if (Camera_SmoothFocusOpponent(arg0, gBattleState.unk_00->unk_2C) != 0) {
        s32 idx = gBattleState.unk_00->unk_2C == 0;

        gBattleState.unk_00->unk_2C = idx;
        gBattleState.unk_00->unk_20 = 0x12;
        BattleScene_IntroCameraStep18(arg0);
    }
}

void BattleScene_IntroCameraHeightShotStep(CameraStruct* arg0) {
    if (Camera_SmoothFocusOpponent(arg0, gBattleState.unk_00->unk_2C) != 0) {
        Camera_UpdateStateMachine(arg0);
    }
}

void BattleScene_IntroCameraTimedHoldStep(CameraStruct* arg0) {
    if (Battle_WaitForAnimation(0x78) != 0) {
        Camera_UpdateStateMachine(arg0);
    }
}

void BattleScene_IntroCameraFinalHoldStep(CameraStruct* arg0) {
    Camera_SetClippingPlanes(arg0, 10.0f, 12800.0f);
    arg0->unk_24.fovy = 60.0f;
    if (Battle_WaitForAnimation(0x3C) != 0) {
        Camera_UpdateStateMachine(arg0);
    }
}

void Camera_MainUpdate(CameraStruct* arg0) {
    if ((gBattleContext.unk_0000 == 0x10) && (gBattleState.unk_00->unk_1C == 1)) {
        Battle_UpdateFrame();
    } else if (gBattleState.unk_00->unk_1C == 1) {
        if ((gBattleState.unk_00->unk_30 == 0) && (sActivePokemon[0]->unk_728.unk_168->unk_1C == 0x17) &&
            (sActivePokemon[1]->unk_728.unk_168->unk_1C == 0x103)) {
            Battle_UpdateFrame();
        } else if ((gBattleState.unk_00->unk_30 == 0) && (sActivePokemon[0]->unk_728.unk_168->unk_1C < 0xE) &&
                   (sActivePokemon[1]->unk_728.unk_168->unk_1C >= 0x10D)) {
            Battle_ResetAllTimers();
        }
    }

    switch (gBattleState.unk_00->unk_20) {
        case 1:
            BattleScene_IntroCameraRollStep(arg0);
            break;

        case 3:
            BattleScene_IntroCameraRollStepNoFov(arg0);
            break;

        case 5:
            BattleScene_IntroCameraAnimationHoldStep(arg0);
            break;

        case 7:
            BattleScene_IntroCameraAnimationHoldStep(arg0);
            break;

        case 9:
            BattleScene_IntroCameraPresetHoldStep(arg0);
            break;

        case 11:
            BattleScene_IntroCameraPresetHoldStep(arg0);
            break;

        case 13:
            BattleScene_IntroCameraWideHoldStep(arg0);
            break;

        case 15:
            BattleScene_IntroCameraWideHoldStep(arg0);
            break;

        case 17:
            BattleScene_IntroCameraHeightShotSwapStep(arg0);
            break;

        case 19:
            BattleScene_IntroCameraHeightShotStep(arg0);
            break;

        case 21:
            BattleScene_IntroCameraTimedHoldStep(arg0);
            break;

        case 23:
            BattleScene_IntroCameraFinalHoldStep(arg0);
            break;

        case 25:
            BattleScene_IntroCameraFinalHoldStep(arg0);
            break;

        case 50:
            Camera_UpdateStateMachine(arg0);
            break;
    }
}
