#include "fragment62.h"
#include "src/12D80.h"
#include "src/F420.h"

unk_D_843901B0 gCameraPreset;
f32 gCameraDistTarget;
f32 gCameraDistCurrent;

static s32 gBattleFrameCounter = 0;

f32 ClampScaledDistance(unk_BattlePlayerEntity* arg0, f32 arg1, f32 arg2) {
    f32 temp_fv1 = GetScaledWidth(arg0) * arg1;

    if (arg2 < temp_fv1) {
        return arg2;
    }
    return temp_fv1;
}

s32 Battle_WaitFrames(s32 arg0) {
    gBattleState.unk_00->unk_10++;
    if (gBattleState.unk_00->unk_10 >= arg0) {
        gBattleState.unk_00->unk_10 = 0;
        return 1;
    }
    return 0;
}

s32 Battle_WaitForAnimation(s32 arg0) {
    gBattleState.unk_00->unk_14++;
    if (gBattleState.unk_00->unk_14 >= arg0) {
        gBattleState.unk_00->unk_14 = 0;
        return 1;
    }
    return 0;
}

s32 Battle_WaitFramesNonBlocking(s32 arg0) {
    if (gBattleState.unk_00->unk_14 >= arg0) {
        return 1;
    }
    gBattleState.unk_00->unk_14++;
    return 0;
}

s32 Battle_IsAnimationFinished(s32 arg0) {
    if (gBattleState.unk_00->unk_14 >= arg0) {
        return 1;
    }
    return 0;
}

void SetCurrentPlayerIndex(s32 arg0) {
    gBattleState.unk_00->unk_2C = arg0;
}

void Battle_FinishTurn(void) {
    gBattleState.unk_00->unk_14 = 0;
}

void Battle_AdvanceTurnState(void) {
    gBattleState.unk_00->unk_10 = 0;
}

void SetCameraPositionAndView(CameraStruct* arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, s16 arg5, s16 arg6) {
    Vec3f_Set(&arg0->unk_60.at, arg1, arg2, arg3);
    Camera_SetViewParameters(&arg0->unk_60.at, &arg0->unk_60.eye, arg4, arg5, arg6);
}

void GetEntityGroundPosition(unk_BattlePlayerEntity* arg0, Vec3f* arg1) {
    UNUSED s32 pad;
    u8 sp18[] = {
        0x52, 0x73, 0x59, 0x91, 0x5F, 0x82, 0x58, 0x66, 0x0A,
    };

    if (Array_ContainsValue(arg0->unk_000.unk_01A, sp18, 9) != 0) {
        ResolveEntityPosition(arg0, arg1, 9);
    } else {
        ResolveEntityPosition(arg0, arg1, 0x64);
    }
}

void ResolveEntityPosition(unk_BattlePlayerEntity* arg0, Vec3f* arg1, s32 arg2) {
    if (Graph_GetRecordedPosition(&arg0->unk_000, arg2, arg1) == NULL) {
        GetEntityCenterPosition(arg0, arg1);
        arg1->x = GetEntityXOffset(arg0);
        arg1->z = 0.0f;
    }
}

void Battle_SetCamera(s32 arg0, s32 arg1) {
    gBattleState.unk_00->unk_1C = arg0;
    gBattleState.unk_00->unk_20 = arg1;
}

void Camera_SetClippingPlanes(CameraStruct* arg0, f32 arg1, f32 arg2) {
    arg0->unk_24.near = arg1;
    arg0->unk_24.far = arg2;
}

void Battle_SetTurnTimer(s32 arg0, u16 arg1) {
    gBattleState.unk_00->unk_30 = arg0;
    gBattleState.unk_00->unk_2E = arg1;
}

void Battle_UpdateTurnIndex(void) {
    if (gBattleState.unk_00->unk_18 == 2) {
        if (gBattleState.unk_00->unk_44 == 1) {
            Battle_SetCamera(1, 0x32);
        }

        if (gBattleState.unk_00->unk_44 == 2) {
            gBattleState.unk_00->unk_2C = gBattleState.unk_00->unk_2A;
            Battle_SetCamera(2, 0);
        }
    }
}

void Battle_ApplyOpponentAnimEffects(unk_BattlePlayerEntity* arg0) {
    PokemonData* ptr = &arg0->unk_724->unk_01C[arg0->unk_654.unk_08];

    gBattleState.unk_00->unk_68 = ((ptr->unk_02 - arg0->unk_654.unk_38.unk_0C) / 996.0f) * 1400.0f;

    if (gBattleState.unk_00->unk_68 == 0.0f) {
        gBattleState.unk_00->unk_68 = 0.0f;
    } else if (gBattleState.unk_00->unk_68 <= 20.0f) {
        gBattleState.unk_00->unk_68 = 20.0f;
    } else if (gBattleState.unk_00->unk_68 >= 50.0f) {
        gBattleState.unk_00->unk_68 = 50.0f;
    }

    gBattleState.unk_00->unk_7A = 0;

    if (gBattleUpdateHPFlag != 0) {
        gBattleState.unk_00->unk_68 = 25.0f;
    }
}

void Battle_ApplyCameraShake(CameraStruct* arg0) {
    UNUSED s32 pad;
    f32 sp30;
    f32 temp_fv0;
    s16 sp2A;
    s16 sp28;

    Math_CalcDistAndAngles(&arg0->unk_60.eye, &arg0->unk_60.at, &sp30, &sp28, &sp2A);
    gBattleState.unk_00->unk_7A += 0x38E0;
    Math_ExponentialApproach(&gBattleState.unk_00->unk_68, 0.0f, 0.18f);

    temp_fv0 = COSS(gBattleState.unk_00->unk_7A) * gBattleState.unk_00->unk_68;

    arg0->unk_60.eye.y += temp_fv0 / 3.0f;
    arg0->unk_60.at.y += temp_fv0 / 3.0f;
    arg0->unk_60.eye.x += temp_fv0 * SINS(sp2A + 0x4000);
    arg0->unk_60.at.x += temp_fv0 * SINS(sp2A + 0x4000);
}

void Anim_HandleSpecificMoveEvent(UNUSED unk_BattlePlayerEntity* arg0) {
    gBattleState.unk_00->unk_68 = 30.0f;
    gBattleState.unk_00->unk_7A = 0;
}

s32 Math_IsAngleWithinRange(s16 arg0, s16 arg1) {
    s16 temp_v1;
    s16 var_v1;

    temp_v1 = arg1 - arg0;
    var_v1 = arg1;
    if (temp_v1 > 0) {
        temp_v1 -= 0xE38;
        if (temp_v1 > 0) {
            var_v1 -= temp_v1;
        } else {
            var_v1 = arg1;
        }
    } else {
        temp_v1 += 0xE38;
        if (temp_v1 < 0) {
            var_v1 -= temp_v1;
        } else {
            var_v1 = arg1;
        }
    }

    if (var_v1 == arg1) {
        return 1;
    }
    return 0;
}

s32 Camera_SmoothPanToAngle(CameraStruct* arg0, s16 arg1, s16 arg2) {
    if (arg1 > 0) {
        gBattleState.unk_00->unk_58 -= arg1;
        if ((gBattleState.unk_00->unk_58 < arg2) && ((arg2 - arg1) < gBattleState.unk_00->unk_58)) {
            gBattleState.unk_00->unk_58 = arg2;
            return 1;
        }
    } else {
        gBattleState.unk_00->unk_58 -= arg1;
        if ((arg2 < gBattleState.unk_00->unk_58) && (gBattleState.unk_00->unk_58 < (arg2 - arg1))) {
            gBattleState.unk_00->unk_58 = arg2;
            return 1;
        }
    }

    Camera_SetViewParameters(&arg0->unk_60.at, &arg0->unk_60.eye, gBattleState.unk_00->unk_5C, gBattleState.unk_00->unk_56,
                  gBattleState.unk_00->unk_58);
    return 0;
}

s32 Camera_CheckPanFinished(UNUSED CameraStruct* arg0, s16 arg1, s16 arg2) {
    gBattleState.unk_00->unk_58 -= arg1;

    if (arg1 > 0) {
        if ((arg2 >= gBattleState.unk_00->unk_58) && (gBattleState.unk_00->unk_58 >= (arg2 - arg1))) {
            gBattleState.unk_00->unk_58 = arg2;
            return 1;
        }
    } else if ((gBattleState.unk_00->unk_58 >= arg2) && ((arg2 - arg1) >= gBattleState.unk_00->unk_58)) {
        gBattleState.unk_00->unk_58 = arg2;
        return 1;
    }
    return 0;
}

void Camera_SetPanTargets(s16 arg0, s16 arg1, f32 arg2) {
    gBattleState.unk_00->unk_56 = arg0;
    gBattleState.unk_00->unk_58 = arg1;
    gBattleState.unk_00->unk_5C = arg2;
}

void SetupBattleCamera(CameraStruct* arg0, s32 arg1) {
    static u8 gDefaultModelId = 0x5F;
    static u16 gDefaultModelParam = 0x38F;

    unk_BattlePlayerAnimState* sp6C;
    UNUSED s32 pad;
    unk_BattlePlayerEntity* temp_s0;
    Vec3f sp58;
    f32 sp54;
    UNUSED u16 pad2;
    UNUSED u8 pad3;
    u8 sp50;
    UNUSED u16 pad4;
    u16 sp4C;
    s32 idx = gBattleState.unk_00->unk_2C == 0;

    sp6C = &sActivePokemon[idx]->unk_654;
    sp50 = gDefaultModelId;
    sp4C = gDefaultModelParam;
    temp_s0 = sActivePokemon[arg1 == 0];
    arg0->unk_24.fovy = 60.0f;

    Battle_FinishTurn();
    GetEntityCenterPosition(temp_s0, &sp58);

    sp58.y /= 3.0f;
    if (temp_s0->unk_654.unk_34 & 0x4000) {
        sp58.y = 0.0f;
    }

    Camera_SetLookAtPosition(temp_s0, arg0, sp58, 0, 0, 0.0f, 0.0f);

    if ((sp6C->unk_2D != 0x10) && !(sp6C->unk_34 & 0x4000)) {
        ExecuteAnimStateHandlers(temp_s0, 1);
    }

    temp_s0 = sActivePokemon[arg1];
    if (temp_s0->unk_448.unk_24.unk_0C.x == 0.0f) {
        GetEntityCenterPosition(temp_s0, &sp58);
    } else {
        Vector_Copy(&sp58, &temp_s0->unk_448.unk_24.unk_0C);
        sp58.y += temp_s0->unk_000.unk_024.y - GetModelBaseY(temp_s0);
    }

    sp54 = ClampScaledDistance(temp_s0, 3.0f, 300.0f);
    if ((Array_ContainsValue(temp_s0->unk_000.unk_01A, &sp50, 1) != 0) && (arg1 == 1)) {
        Camera_SetEyePositionOffset(arg0, sp58, 0, GetPlayerSideYaw(temp_s0) - (temp_s0->unk_4B0 * 0x6AA4), sp54, 20.0f);
    } else if (Array_ContainsValue(temp_s0->unk_000.unk_01A, (u8*)&sp4C, 2) != 0) {
        Camera_SetEyePositionOffset(arg0, sp58, 0, GetPlayerSideYaw(temp_s0) - (temp_s0->unk_4B0 * 0x6AA4), sp54, 20.0f);
    } else {
        Camera_SetEyePositionOffset(arg0, sp58, 0, GetPlayerSideYaw(temp_s0) - (temp_s0->unk_4B0 * 0x754E), sp54, 0.0f);
    }
}

void BattleScene_ClampCameraEyeFloor(CameraStruct* arg0) {
    if (arg0->unk_60.eye.y <= 13.0f) {
        arg0->unk_60.eye.y = 13.0f;
    }
}

void ConfigureCameraForModel(unk_BattlePlayerEntity* arg0, CameraStruct* arg1) {
    unk_D_84390010_448* sp38 = &arg0->unk_448;
    UNUSED s32 pad[5];
    f32 sp3C = 0.0f;

    if (Array_ContainsValue(arg0->unk_000.unk_01A, &gPokemonSfxId_0, 1) != 0) {
        sp3C = Battle_GetEntityHeight(arg0) / 1.5f;
    } else if (Array_ContainsValue(arg0->unk_000.unk_01A, &gPokemonSfxId_1, 1) != 0) {
        sp3C = Battle_GetEntityHeight(arg0) * 0.5f;
    } else if ((Array_ContainsValue(arg0->unk_000.unk_01A, &gPokemonSfxId_2, 1) != 0) && (arg0->unk_654.unk_34 & 0x200)) {
        sp3C = 2.0f * Battle_GetEntityHeight(arg0);
    } else if ((Array_ContainsValue(arg0->unk_000.unk_01A, gPokemonSfxId_3, 2) != 0) && (arg0->unk_654.unk_34 & 0x200)) {
        sp3C = Battle_GetEntityHeight(arg0) * 1.5f;
    }

    Vec3f_Set(&arg0->unk_448.unk_18, arg0->unk_448.unk_24.unk_00.x, arg0->unk_448.unk_24.unk_00.y,
                  arg0->unk_448.unk_24.unk_00.z);
    arg0->unk_448.unk_18.y = (arg0->unk_000.unk_024.y - GetModelBaseY(arg0)) + arg0->unk_448.unk_18.y + sp3C;
    Vector_Copy(&gBattleState.unk_00->unk_B8, &arg1->unk_60.at);
    Vector_Copy(&gBattleState.unk_00->unk_C4, &arg1->unk_60.eye);
    Matrix_Decompose(&gBattleState.unk_00->unk_B8, &gBattleState.unk_00->unk_C4, &gBattleState.unk_00->unk_70, &sp38->unk_44,
                  &sp38->unk_46);
    Matrix_Decompose(&arg0->unk_448.unk_18, &arg1->unk_60.at, &sp38->unk_4C, &sp38->unk_44, &sp38->unk_46);
    gBattleState.unk_00->unk_6C = 0.0f;
    gBattleState.unk_00->unk_74 = 0.0f;
}

void Battle_ResetCameraState(void) {
    Vec3f_Set(&gBattleState.unk_00->unk_94, 0.0f, 0.0f, 0.0f);
    Vec3f_Set(&gBattleState.unk_00->unk_A0, 0.0f, 0.0f, 0.0f);
}

void Camera_SetLookAtPosition(unk_BattlePlayerEntity* arg0, CameraStruct* arg1, Vec3f arg2, s16 arg3, s16 arg4, f32 arg5, f32 arg6) {
    Camera_SetViewParameters(&arg2, &arg1->unk_60.at, arg5, arg3, arg4);
    arg1->unk_60.at.y += arg6;
    arg1->unk_60.at.y += GetModelDepth(arg0);
}

void Camera_SetEyePosition(CameraStruct* arg0, Vec3f arg1, s16 arg2, s16 arg3, f32 arg4, f32 arg5) {
    Camera_SetViewParameters(&arg1, &arg0->unk_60.at, arg4, arg2, arg3);
    arg0->unk_60.at.y += arg5;
}

void Camera_SetEyePositionOffset(CameraStruct* arg0, Vec3f arg1, s16 arg2, s16 arg3, f32 arg4, f32 arg5) {
    Camera_SetViewParameters(&arg1, &arg0->unk_60.eye, arg4, arg2, arg3);
    arg0->unk_60.eye.y += arg5;
}

void Camera_SetViewAndOffsetEye(CameraStruct* arg0, s16 arg1, s16 arg2, f32 arg3, f32 arg4) {
    Camera_SetViewParameters(&arg0->unk_60.at, &arg0->unk_60.eye, arg3, arg1, arg2);
    arg0->unk_60.eye.y += arg4;
}

void Camera_SetEyeAndPanTargets(CameraStruct* arg0, Vec3f arg1, s16 arg2, s16 arg3, f32 arg4, f32 arg5) {
    Camera_SetPanTargets(arg2, arg3, arg4);
    Camera_SetViewParameters(&arg1, &arg0->unk_60.eye, arg4, arg2, arg3);
    arg0->unk_60.eye.y += arg5;
}

void Camera_SetAtAndPanTargets(CameraStruct* arg0, s16 arg1, s16 arg2, f32 arg3, f32 arg4) {
    Camera_SetPanTargets(arg1, arg2, arg3);
    Camera_SetViewParameters(&arg0->unk_60.at, &arg0->unk_60.eye, arg3, arg1, arg2);
    arg0->unk_60.eye.y += arg4;
}

void BattleScene_CameraHelperNop(UNUSED CameraStruct* arg0) {
}

void SmoothFloatPair(f32* arg0, f32* arg1) {
    f32 tmp;

    if (*arg0 != *arg1) {
        if (*arg1 < *arg0) {
            tmp = *arg0 - *arg1;
            if (tmp <= 1e-05) {
                *arg1 = *arg0;
            }
        } else {
            tmp = *arg1 - *arg0;
            if (tmp <= 1e-05) {
                *arg0 = *arg1;
            }
        }
    }
}

void Camera_UpdateFocusOnEntity(CameraStruct* arg0, unk_BattlePlayerEntity* arg1, UNUSED f32 arg2) {
    unk_D_84390010_448* sp2C = &arg1->unk_448;
    f32 var_fv1;
    Vec3f sp64;
    Vec3f sp58;
    Vec3f sp4C;
    Vec3f sp40;
    f32 sp3C;
    f32 temp_fv1;
    s16 sp36;
    s16 sp34;

    Vector_Copy(&sp4C, &arg0->unk_60.at);
    Vector_Copy(&sp40, &arg0->unk_60.at);
    GetEntityGroundPosition(arg1, &sp64);
    Matrix_Decompose(&sp64, &arg1->unk_448.unk_18, &sp3C, &sp36, &sp34);

    switch (arg1->unk_000.unk_01A) {
        case 0x5F:
            arg0->unk_24.fovy = 50.0f;
            return;

        case 0x82:
            arg0->unk_24.fovy = 50.0f;
            if (sp3C < (GetModelWidth(arg1) * 0.5f)) {
                Vector_Copy(&sp64, &arg1->unk_448.unk_18);
            }
            break;

        case 0x1D:
        case 0x29:
        case 0x32:
        case 0x33:
        case 0x5B:
            if (sp3C < (GetModelWidth(arg1) * 5.0f)) {
                Vector_Copy(&sp64, &arg1->unk_448.unk_18);
            }
            break;

        case 0x12:
            if (sp3C < (GetModelWidth(arg1) * 1.5f)) {
                Vector_Copy(&sp64, &arg1->unk_448.unk_18);
            }
            break;

        case 0x27:
        case 0x58:
        case 0x59:
        case 0x96:
            if (sp3C < GetModelWidth(arg1)) {
                Vector_Copy(&sp64, &arg1->unk_448.unk_18);
            }
            break;

        case 0x4A:
        case 0x65:
        case 0x67:
            if (sp3C < (GetModelWidth(arg1) / 1.2f)) {
                Vector_Copy(&sp64, &arg1->unk_448.unk_18);
            }
            break;

        case 0x7:
        case 0x11:
        case 0x16:
        case 0x4C:
        case 0x5C:
        case 0x83:
            if (sp3C < (GetModelWidth(arg1) / 3.0f)) {
                Vector_Copy(&sp64, &arg1->unk_448.unk_18);
            }
            break;

        default:
            if (sp3C < (GetModelWidth(arg1) * 0.5f)) {
                Vector_Copy(&sp64, &arg1->unk_448.unk_18);
            }
            break;
    }

    sp64.y = arg1->unk_448.unk_18.y;
    Camera_SetViewParameters(&sp64, &sp58, sp2C->unk_4C, sp2C->unk_44, sp2C->unk_46);
    sp4C.y = sp58.y;
    Matrix_Decompose(&sp4C, &sp58, &sp3C, &sp36, &sp34);

    switch (arg1->unk_000.unk_01A) {
        case 0x58:
        case 0x59:
        case 0x87:
            var_fv1 = sp3C / (GetModelWidth(arg1) * 50.0f);
            break;

        case 0x16:
        case 0x4C:
        case 0x96:
            var_fv1 = sp3C / (GetModelWidth(arg1) * 1.5f);
            break;

        default:
            temp_fv1 = sp3C / GetModelWidth(arg1);
            if (temp_fv1 <= 0.1f) {
                var_fv1 = sp3C / (GetModelWidth(arg1) * 15.0f);
            } else if (temp_fv1 <= 0.2f) {
                var_fv1 = sp3C / (GetModelWidth(arg1) * 7.0f);
            } else if (temp_fv1 <= 0.3f) {
                var_fv1 = sp3C / (GetModelWidth(arg1) * 5.0f);
            } else if (temp_fv1 <= 0.4f) {
                var_fv1 = sp3C / (GetModelWidth(arg1) * 3.0f);
            } else if (temp_fv1 <= 0.5f) {
                var_fv1 = sp3C / (GetModelWidth(arg1) * 1.5f);
            } else {
                var_fv1 = sp3C / GetModelWidth(arg1);
            }
            break;
    }

    if (var_fv1 > 1.0f) {
        var_fv1 = 1.0f;
    }

    Camera_SetViewParameters(&sp4C, &arg0->unk_60.at, sp3C * var_fv1, 0, sp34);
    GetEntityGroundPosition(arg1, &sp64);
    Camera_SetViewParameters(&sp64, &sp58, sp2C->unk_4C, sp2C->unk_44, sp2C->unk_46);

    sp3C = sp40.y - sp58.y;
    if (sp3C < 0.0f) {
        sp3C *= -1.0f;
    }

    if (arg1->unk_4B4 == 0xD) {
        var_fv1 = 0;
    } else if ((arg1->unk_000.unk_01A == 0x58) || (arg1->unk_000.unk_01A == 0x59)) {
        temp_fv1 = sp3C / GetModelWidth(arg1);
        if (temp_fv1 <= 0.05f) {
            var_fv1 = sp3C / (GetModelWidth(arg1) * 90.0f);
        } else if (temp_fv1 <= 0.1f) {
            var_fv1 = sp3C / (GetModelWidth(arg1) * 70.0f);
        } else if (temp_fv1 <= 0.2f) {
            var_fv1 = sp3C / (GetModelWidth(arg1) * 65.0f);
        } else if (temp_fv1 <= 0.3f) {
            var_fv1 = sp3C / (GetModelWidth(arg1) * 63.0f);
        } else {
            var_fv1 = sp3C / (GetModelWidth(arg1) * 45.0f);
        }
    } else {
        temp_fv1 = sp3C / GetModelWidth(arg1);
        if (temp_fv1 <= 0.05f) {
            var_fv1 = sp3C / (GetModelWidth(arg1) * 50.0f);
        } else if (temp_fv1 <= 0.1f) {
            var_fv1 = sp3C / (GetModelWidth(arg1) * 30.0f);
        } else if (temp_fv1 <= 0.2f) {
            var_fv1 = sp3C / (GetModelWidth(arg1) * 25.0f);
        } else if (temp_fv1 <= 0.3f) {
            var_fv1 = sp3C / (GetModelWidth(arg1) * 23.0f);
        } else {
            var_fv1 = sp3C / (GetModelWidth(arg1) * 15.0f);
        }
    }

    if (var_fv1 > 1.0f) {
        var_fv1 = 1.0f;
    }

    Math_ExponentialApproach(&sp40.y, sp58.y, var_fv1);
    arg0->unk_60.at.y = sp40.y;
    SmoothFloatPair(&arg0->unk_60.at.x, &arg0->unk_60.eye.x);
    SmoothFloatPair(&arg0->unk_60.at.y, &arg0->unk_60.eye.y);
    SmoothFloatPair(&arg0->unk_60.at.z, &arg0->unk_60.eye.z);
}

void Camera_SmoothAdjustDistance(CameraStruct* arg0, unk_BattlePlayerEntity* arg1) {
    UNUSED s32 pad[5];
    f32 var_fv0_2;
    f32 sp44;
    s32 temp_lo;
    s16 sp3E;
    s16 sp3C;
    f32 sp38;
    s16 sp36;
    s16 sp34;
    u8 sp2C[] = { 0x2D, 0x35, 0x79, 0x2C, 0x6E };

    Matrix_Decompose(&gBattleState.unk_00->unk_B8, &gBattleState.unk_00->unk_C4, &sp38, &sp36, &sp34);
    Matrix_Decompose(&arg0->unk_60.at, &arg0->unk_60.eye, &sp44, &sp3E, &sp3C);

    temp_lo = sp34 / 182;
    if ((temp_lo == 0x5A) || (temp_lo == -0x5A)) {
        if (Array_ContainsValue(arg1->unk_000.unk_01A, sp2C, sizeof(sp2C)) != 0) {
            sp44 = sp38;
        } else {
            sp44 = Math_ApproachF32(sp44, sp38, 30.0f, 5.0f);
        }
    } else {
        var_fv0_2 = gBattleState.unk_00->unk_70 - sp44;
        if (var_fv0_2 < 0.0f) {
            var_fv0_2 *= -1.0f;
        }

        if (sp44 < sp38) {
            sp44 = Math_ApproachF32(sp44, gBattleState.unk_00->unk_70, var_fv0_2 * 0.4f, var_fv0_2 * 0.08f);
        }
    }
    Camera_SetViewParameters(&arg0->unk_60.at, &arg0->unk_60.eye, sp44, sp36, sp34);
}

void Battle_AdvanceCameraTimeline(CameraStruct* arg0, unk_BattlePlayerEntity* arg1) {
    Camera_UpdateFocusOnEntity(arg0, arg1, 50.0f);
    Camera_SmoothAdjustDistance(arg0, arg1);
}

void Battle_AdvanceCameraTimelineFast(CameraStruct* arg0, unk_BattlePlayerEntity* arg1) {
    Camera_UpdateFocusOnEntity(arg0, arg1, 90.0f);
    Camera_SmoothAdjustDistance(arg0, arg1);
}

void Battle_AdvanceCameraTimelineSlow(CameraStruct* arg0, unk_BattlePlayerEntity* arg1) {
    Camera_UpdateFocusOnEntity(arg0, arg1, 50.0f);
}

void Camera_FocusEntityWithOffset(CameraStruct* arg0, unk_BattlePlayerEntity* arg1) {
    unk_D_84390010_448* ptr = &arg1->unk_448;
    UNUSED s32 pad;
    Vec3f sp54;
    Vec3f sp48;
    Vec3f sp3C;
    f32 sp38;
    f32 var_fa0;
    s16 sp32;
    s16 sp30;

    Vector_Copy(&sp3C, &arg0->unk_60.at);
    GetEntityGroundPosition(arg1, &sp54);
    Matrix_Decompose(&sp54, &arg1->unk_448.unk_18, &sp38, &sp32, &sp30);

    if (sp38 < (GetModelWidth(arg1) * 1.1f)) {
        Vector_Copy(&sp54, &arg1->unk_448.unk_18);
    }

    Camera_SetViewParameters(&sp54, &sp48, ptr->unk_4C, ptr->unk_44, ptr->unk_46);
    Matrix_Decompose(&sp3C, &sp48, &sp38, &sp32, &sp30);

    var_fa0 = (sp38 / (GetModelWidth(arg1) * 80.0f)) * 3.0f;
    if (var_fa0 >= 1.0f) {
        var_fa0 = 1.0f;
    }

    Camera_SetViewParameters(&sp3C, &arg0->unk_60.at, sp38 * var_fa0, sp32, sp30);
}

s32 Battle_ProcessOpponentAction(CameraStruct* arg0, unk_BattlePlayerEntity* arg1) {
    Vec3f sp84;
    UNUSED s32 pad[3];
    Vec3f sp6C;
    Vec3f sp60;
    UNUSED s32 pad2[3];
    s16 sp52;
    s16 sp50;
    s16 sp4E;
    s16 sp4C;
    UNUSED s32 pad3[2];
    unk_D_800FCB18* temp_v1;

    temp_v1 = &sActivePokemon[IsPrimaryEntity(arg1) == 0]->unk_654.unk_38;

    if (arg1->unk_654.unk_34 & 0x4000) {
        return 1;
    }

    if (temp_v1->unk_5A == 0x53) {
        Battle_QueueOpponentMove(arg1, arg0, 4);
        return 1;
    }

    Vector_Copy(&sp6C, &arg0->unk_60.at);
    Vector_Copy(&sp60, &arg0->unk_60.eye);

    if ((arg1->unk_000.unk_01A != 0x5F) && (arg1->unk_4B4 != 0xD)) {
        Camera_FocusEntityWithOffset(arg0, arg1);
    }

    GetEntityCenterPosition(arg1, &sp84);
    gCameraDistTarget = ClampScaledDistance(arg1, 3.5f, 300.0f);
    Camera_SetEyePositionOffset(arg0, sp84, 0, GetPlayerSideYaw(arg1), gCameraDistTarget, 0.0f);

    if (arg0->unk_60.eye.y <= 13.0f) {
        arg0->unk_60.eye.y = 13.0f;
    }

    Math_CalcDistAndAngles(&sp84, &arg0->unk_60.eye, &gCameraDistCurrent, &sp4C, &sp50);
    Math_CalcDistAndAngles(&sp84, &sp60, &gCameraDistTarget, &sp4E, &sp52);
    Math_ExponentialApproach(&gCameraDistTarget, gCameraDistCurrent, 0.2f);
    Math_ExponentialApproach(&gBattleState.unk_00->unk_94.z, 0.2f, 0.03f);
    Math_StepTowardsProportional(&sp52, sp50, gBattleState.unk_00->unk_94.z);
    Math_StepTowardsProportional(&sp4E, sp4C, gBattleState.unk_00->unk_94.z);
    Camera_SetEyePositionOffset(arg0, sp84, sp4E, sp52, gCameraDistTarget, 0.0f);

    if ((sp4C == sp4E) && (sp50 == sp52)) {
        return 1;
    }
    return 0;
}

void Camera_SmoothFocusEntity(CameraStruct* arg0, unk_BattlePlayerEntity* arg1) {
    unk_D_84390010_448* ptr = &arg1->unk_448;
    Vec3f sp58;
    Vec3f sp4C;
    UNUSED s32 pad[3];
    Vec3f sp34;
    f32 sp30;
    UNUSED s32 pad2[1];
    s16 sp2A;
    s16 sp28;

    Vector_Copy(&sp34, &arg0->unk_60.at);
    GetEntityGroundPosition(arg1, &sp58);
    Camera_SetViewParameters(&sp58, &sp4C, ptr->unk_4C, ptr->unk_44, ptr->unk_46);
    Matrix_Decompose(&sp34, &sp4C, &sp30, &sp2A, &sp28);
    gBattleState.unk_00->unk_94.z = Math_ApproachF32(gBattleState.unk_00->unk_94.z, 0.8f, 0.05f, 0.05f);
    Camera_SetViewParameters(&sp34, &arg0->unk_60.at, gBattleState.unk_00->unk_94.z * sp30, sp2A, sp28);
}

void Camera_SmoothFocusEntityY(CameraStruct* arg0, unk_BattlePlayerEntity* arg1) {
    unk_D_84390010_448* ptr = &arg1->unk_448;
    Vec3f sp60;
    Vec3f sp54;
    UNUSED s32 pad[3];
    Vec3f sp3C;
    UNUSED s32 pad2[3];

    Vector_Copy(&sp3C, &arg0->unk_60.at);
    GetEntityGroundPosition(arg1, &sp60);
    Camera_SetViewParameters(&sp60, &sp54, ptr->unk_4C, ptr->unk_44, ptr->unk_46);
    Math_ExponentialApproach(&arg0->unk_60.at.y, sp54.y, 0.1f);
    if (arg0->unk_60.at.y < -10.0f) {
        arg0->unk_60.at.y = -10.0f;
    }
    Math_ExponentialApproach(&arg0->unk_60.eye.y, Battle_GetEntityHeight(arg1) * 4.0f, 0.04f);
}

void Camera_SmoothPanToEntity(CameraStruct* arg0, unk_BattlePlayerEntity* arg1) {
    Vec3f sp74;
    Vec3f sp68;
    Vec3f sp5C;
    f32 sp58;
    s16 sp56;
    s16 sp54;
    s16 sp52;
    s16 sp50;
    s16 sp4E;
    s16 sp4C;

    Vector_Copy(&sp68, &arg0->unk_60.at);
    Vector_Copy(&sp5C, &arg0->unk_60.eye);
    GetEntityCenterPosition(arg1, &sp74);
    gCameraDistTarget = ClampScaledDistance(arg1, 3.5f, 300.0f);
    Camera_SetLookAtPosition(arg1, arg0, sp74, 0, GetPlayerSideYaw(arg1), 0.0f, 0.0f);
    Camera_SetEyePositionOffset(arg0, sp74, 0, GetPlayerSideYaw(arg1), gCameraDistTarget, 0.0f);
    Math_CalcDistAndAngles(&arg0->unk_60.at, &arg0->unk_60.eye, &gCameraDistCurrent, &sp4C, &sp50);
    Math_CalcDistAndAngles(&sp68, &sp5C, &gCameraDistTarget, &sp4E, &sp52);
    Math_ExponentialApproach(&gCameraDistTarget, gCameraDistCurrent, 0.05f);
    Math_StepTowards(&sp52, sp50, 0x108);
    Math_StepTowards(&sp4E, sp4C, 0xB6);
    Math_CalcDistAndAngles(&sp68, &arg0->unk_60.at, &sp58, &sp56, &sp54);
    Camera_SetViewParameters(&sp68, &arg0->unk_60.at, sp58 / 8, sp56, sp54);
    Camera_SetViewAndOffsetEye(arg0, sp4E, sp52, gCameraDistTarget, 0.0f);
}

void Camera_SetDistanceToEntity(CameraStruct* arg0, unk_BattlePlayerEntity* arg1, UNUSED s32 arg2) {
    unk_D_84390010_448* ptr = &arg1->unk_448;
    Vec3f sp50;
    Vec3f sp44;
    Vec3f sp38;
    f32 sp34;
    s16 sp32;
    s16 sp30;
    UNUSED s32 pad;

    GetEntityGroundPosition(arg1, &sp50);
    Vector_Copy(&sp38, &arg0->unk_60.at);
    Camera_SetViewParameters(&sp50, &sp44, ptr->unk_4C, ptr->unk_44, ptr->unk_46);
    Math_CalcDistAndAngles(&sp38, &sp44, &sp34, &sp32, &sp30);
    Camera_SetViewParameters(&sp38, &arg0->unk_60.at, sp34 * 0.1f, sp32, sp30);
}

void Camera_SmoothZoomOut(CameraStruct* arg0, unk_BattlePlayerEntity* arg1) {
    s16 sp26;
    s16 sp24;

    gCameraDistTarget = ClampScaledDistance(arg1, 8.0f, 500.0f);
    Math_CalcDistAndAngles(&arg0->unk_60.at, &arg0->unk_60.eye, &gCameraDistCurrent, &sp26, &sp24);
    Math_ExponentialApproach(&gCameraDistCurrent, gCameraDistTarget, 0.03f);
    Math_StepTowards(&sp26, 0xE38, 0x5B);
    Camera_SetViewAndOffsetEye(arg0, sp26, sp24, gCameraDistCurrent, 0.0f);
}

s32 Camera_SmoothZoomIn(CameraStruct* arg0, unk_BattlePlayerEntity* arg1) {
    Vec3f sp3C;
    Vec3f sp30;
    f32 sp2C;
    s16 sp2A;
    s16 sp28;

    Vector_Copy(&sp3C, &arg0->unk_60.at);
    Vector_Copy(&sp30, &arg0->unk_60.eye);
    Battle_SetCameraOpponentClose(arg0, arg1);
    Matrix_Decompose(&sp30, &arg0->unk_60.eye, &sp2C, &sp28, &sp2A);
    Camera_SetViewParameters(&sp30, &arg0->unk_60.eye, sp2C / 2, sp28, sp2A);
    Vector_Copy(&arg0->unk_60.at, &sp3C);

    if (sp2C <= 0.5f) {
        return 1;
    }
    return 0;
}

s32 Battle_CheckPlayerAction(CameraStruct* arg0, unk_BattlePlayerEntity* arg1, s32 arg2, s32 arg3) {
    UNUSED s32 pad;
    Vec3f sp60;
    Vec3f sp54;
    Vec3f sp48;
    Vec3f sp3C;
    f32 sp38;
    f32 sp34;
    s16 sp32;
    s16 sp30;

    if (gCameraPreset.unk_3C != 200.0f) {
        arg0->unk_24.fovy = gCameraPreset.unk_3C;
    } else if (arg3 == 1) {
        Math_ExponentialApproach(&arg0->unk_24.fovy, 30.0f, 0.06f);
    } else {
        arg0->unk_24.fovy = 30.0f;
    }

    Math_ExponentialApproach(&gBattleState.unk_00->unk_94.z, gCameraPreset.unk_34, gCameraPreset.unk_38);
    Camera_SetViewParameters(&gCameraPreset.unk_00, &sp54, gCameraPreset.unk_30, gCameraPreset.unk_26, gCameraPreset.unk_28);
    Vector_Copy(&sp48, &arg0->unk_60.eye);
    Math_CalcDistAndAngles(&sp48, &sp54, &sp38, &sp32, &sp30);
    Camera_SetViewParameters(&sp48, &arg0->unk_60.eye, gBattleState.unk_00->unk_94.z * sp38, sp32, sp30);
    Camera_SetViewParameters(&gCameraPreset.unk_00, &sp3C, gCameraPreset.unk_2C, gCameraPreset.unk_20, gCameraPreset.unk_22);

    if (arg2 == 1) {
        sp3C.y += GetModelDepth(arg1);
    }

    Vector_Copy(&sp60, &arg0->unk_60.at);
    Math_CalcDistAndAngles(&sp60, &sp3C, &sp34, &sp32, &sp30);
    Camera_SetViewParameters(&sp60, &arg0->unk_60.at, gBattleState.unk_00->unk_94.z * sp34, sp32, sp30);

    if ((sp38 <= 1.75f) && (sp34 <= 1.75f)) {
        return 1;
    }
    return 0;
}

s32 Battle_ApplySpecialCamera(CameraStruct* arg0, unk_BattlePlayerEntity* arg1) {
    Vec3f sp6C;
    Vec3f sp60;
    Vec3f sp54;
    Vec3f sp48;
    f32 sp44;
    f32 sp40;
    f32 sp3C;
    f32 var_fa1;
    s16 sp36;
    s16 sp34;

    if (gCameraPreset.unk_3C != 200.0f) {
        arg0->unk_24.fovy = gCameraPreset.unk_3C;
    } else {
        arg0->unk_24.fovy = 30.0f;
    }

    Math_ExponentialApproach(&gBattleState.unk_00->unk_94.z, gCameraPreset.unk_34, gCameraPreset.unk_38);
    GetEntityGroundPosition(arg1, &sp6C);
    Matrix_Decompose(&gCameraPreset.unk_00, &sp6C, &sp44, &sp36, &sp34);

    var_fa1 = sp44 / (GetModelWidth(arg1) * 40.0f);
    if (var_fa1 >= 0.6f) {
        var_fa1 = 1.0f;
    }

    sp44 *= var_fa1;
    sp44 += gCameraPreset.unk_30;

    Camera_SetViewParameters(&gCameraPreset.unk_00, &sp60, sp44, gCameraPreset.unk_26, gCameraPreset.unk_28);
    Vector_Copy(&sp54, &arg0->unk_60.eye);
    Math_CalcDistAndAngles(&sp54, &sp60, &sp40, &sp36, &sp34);
    Camera_SetViewParameters(&sp54, &arg0->unk_60.eye, gBattleState.unk_00->unk_94.z * sp40, sp36, sp34);
    GetEntityGroundPosition(arg1, &sp6C);
    Matrix_Decompose(&gCameraPreset.unk_00, &sp6C, &sp44, &sp36, &sp34);

    var_fa1 = sp44 / (GetModelWidth(arg1) * 40.0f);
    if (var_fa1 >= 0.6f) {
        var_fa1 = 1;
    }
    sp44 *= var_fa1;
    sp44 += gCameraPreset.unk_2C;

    Camera_SetViewParameters(&gCameraPreset.unk_00, &sp48, sp44, gCameraPreset.unk_20, gCameraPreset.unk_22);
    sp48.y += GetModelDepth(arg1);
    Vector_Copy(&sp6C, &arg0->unk_60.at);
    Math_CalcDistAndAngles(&sp6C, &sp48, &sp3C, &sp36, &sp34);
    Camera_SetViewParameters(&sp6C, &arg0->unk_60.at, gBattleState.unk_00->unk_94.z * sp3C, sp36, sp34);

    if ((sp40 <= 1.0f) && (sp3C <= 1.0f)) {
        return 1;
    }
    return 0;
}

void Battle_UpdateCameraMatrix(UNUSED CameraStruct* arg0) {
    if (arg0) {}
}

void Battle_ApplyCameraSettings(CameraStruct* arg0, unk_BattlePlayerEntity* arg1, s32 arg2) {
    Camera_SetEyePosition(arg0, gCameraPreset.unk_00, gCameraPreset.unk_0C, gCameraPreset.unk_0E, gCameraPreset.unk_18, 0.0f);
    if (arg2 == 1) {
        arg0->unk_60.at.y += GetModelDepth(arg1);
        Camera_SetEyePositionOffset(arg0, arg0->unk_60.at, gCameraPreset.unk_12, gCameraPreset.unk_14, gCameraPreset.unk_1C, 0.0f);
    } else {
        Camera_SetEyePositionOffset(arg0, gCameraPreset.unk_00, gCameraPreset.unk_12, gCameraPreset.unk_14, gCameraPreset.unk_1C, 0.0f);
    }
}

void CameraPreset_SetAngles(s16 arg0, s16 arg1, s16 arg2, s16 arg3) {
    gCameraPreset.unk_0C = arg0;
    gCameraPreset.unk_0E = arg1;
    gCameraPreset.unk_20 = arg2;
    gCameraPreset.unk_22 = arg3;
}

void CameraPreset_SetDistances(f32 arg0, f32 arg1) {
    gCameraPreset.unk_18 = arg0;
    gCameraPreset.unk_2C = arg1;
}

void CameraPreset_SetSecondaryAngles(s16 arg0, s16 arg1, s16 arg2, s16 arg3) {
    gCameraPreset.unk_12 = arg0;
    gCameraPreset.unk_14 = arg1;
    gCameraPreset.unk_26 = arg2;
    gCameraPreset.unk_28 = arg3;
}

void CameraPreset_SetSecondaryDistances(f32 arg0, f32 arg1) {
    gCameraPreset.unk_1C = arg0;
    gCameraPreset.unk_30 = arg1;
}

void CameraPreset_SetTimelineParams(f32 arg0, f32 arg1) {
    gCameraPreset.unk_34 = arg0;
    gCameraPreset.unk_38 = arg1;
}

void Battle_PlayCameraTransition(unk_D_86B0C160* arg0, CameraStruct* arg1, unk_BattlePlayerEntity* arg2) {
    f32 sp34;
    f32 sp30;
    f32 sp2C;
    f32 sp28;
    f32 temp_fv1;
    UNUSED s16 pad;
    s16 sp20;

    Battle_ResetCameraState();
    if (arg0->unk_30 != 200.0f) {
        temp_fv1 = arg0->unk_30;
        gCameraPreset.unk_3C = temp_fv1;
        arg1->unk_24.fovy = temp_fv1;
    } else {
        gCameraPreset.unk_3C = arg0->unk_30;
    }

    sp34 = ClampScaledDistance(arg2, arg0->unk_0C, 500.0f);
    sp30 = ClampScaledDistance(arg2, arg0->unk_20, 500.0f);
    sp2C = ClampScaledDistance(arg2, arg0->unk_10, 500.0f);
    sp28 = ClampScaledDistance(arg2, arg0->unk_24, 500.0f);
    sp20 = GetPlayerSideYaw(arg2);

    CameraPreset_SetAngles(arg0->unk_00, sp20 - (arg0->unk_02 * arg2->unk_4B0), arg0->unk_14,
                  GetPlayerSideYaw(arg2) - (arg0->unk_16 * arg2->unk_4B0));
    CameraPreset_SetDistances(sp34, sp30);
    sp20 = GetPlayerSideYaw(arg2);
    CameraPreset_SetSecondaryAngles(arg0->unk_06, sp20 - (arg0->unk_08 * arg2->unk_4B0), arg0->unk_1A,
                  GetPlayerSideYaw(arg2) - (arg0->unk_1C * arg2->unk_4B0));
    CameraPreset_SetSecondaryDistances(sp2C, sp28);
    CameraPreset_SetTimelineParams(arg0->unk_28, arg0->unk_2C);
}

void Battle_ApplyCameraPreset(unk_D_86B0C160* arg0, CameraStruct* arg1) {
    f32 sp2C;
    f32 sp28;
    f32 sp24;
    f32 sp20;
    f32 tmp;

    Battle_ResetCameraState();

    if (arg0->unk_30 != 200.0f) {
        tmp = arg0->unk_30;
        gCameraPreset.unk_3C = tmp;
        arg1->unk_24.fovy = tmp;
    } else {
        gCameraPreset.unk_3C = arg0->unk_30;
    }

    sp2C = arg0->unk_0C;
    sp28 = arg0->unk_20;
    sp24 = arg0->unk_10;
    sp20 = arg0->unk_24;

    CameraPreset_SetAngles(arg0->unk_00, arg0->unk_02, arg0->unk_14, arg0->unk_16);
    CameraPreset_SetDistances(sp2C, sp28);
    CameraPreset_SetSecondaryAngles(arg0->unk_06, arg0->unk_08, arg0->unk_1A, arg0->unk_1C);
    CameraPreset_SetSecondaryDistances(sp24, sp20);
    CameraPreset_SetTimelineParams(arg0->unk_28, arg0->unk_2C);
}

s32 Camera_SmoothFocusEntitySide(CameraStruct* arg0, unk_BattlePlayerEntity* arg1) {
    Vec3f sp64;
    Vec3f sp58;
    Vec3f sp4C;
    Vec3f sp40;
    Vec3f sp34;
    f32 sp30;
    UNUSED s32 pad;
    s16 sp2A;
    s16 sp28;

    Math_ExponentialApproach(&arg0->unk_24.fovy, 30.0f, 0.06f);
    Vec3f_Set(&sp64, arg1->unk_4B0 * -150.0f, 5.0f, 0.0f);
    Math_ExponentialApproach(&gBattleState.unk_00->unk_94.z, 0.2f, 0.06f);
    Camera_SetViewParameters(&sp64, &sp4C, 100.0f, 0, GetPlayerSideYaw(arg1));
    Vector_Copy(&sp40, &arg0->unk_60.eye);
    Math_CalcDistAndAngles(&sp40, &sp4C, &sp30, &sp2A, &sp28);
    Camera_SetViewParameters(&sp40, &arg0->unk_60.eye, gBattleState.unk_00->unk_94.z * sp30, sp2A, sp28);
    Camera_SetViewParameters(&sp64, &sp34, 0.0f, 0, GetPlayerSideYaw(arg1));
    Vector_Copy(&sp58, &arg0->unk_60.at);
    Math_CalcDistAndAngles(&sp58, &sp34, &sp30, &sp2A, &sp28);

    if (sp30 >= 1.0f) {
        Camera_SetViewParameters(&sp58, &arg0->unk_60.at, gBattleState.unk_00->unk_94.z * sp30, sp2A, sp28);
        return 0;
    }
    return 1;
}

s32 Battle_CheckEntityHeightDiff(UNUSED CameraStruct* arg0) {
    Vec3f sp2C;
    Vec3f sp20;
    f32 var_fv0;

    GetEntityCenterPosition(sActivePokemon[0], &sp2C);
    GetEntityCenterPosition(sActivePokemon[1], &sp20);

    var_fv0 = sp2C.y - sp20.y;
    if (sp2C.y < sp20.y) {
        var_fv0 *= -1.0f;
    }

    if (var_fv0 > 35.0f) {
        return 1;
    }
    return 0;
}

void Camera_SetEntityView(CameraStruct* arg0, s32 arg1) {
    UNUSED s32 pad;
    Vec3f sp60;
    Vec3f sp54;
    Vec3f sp48;
    unk_BattlePlayerEntity* sp40;

    Battle_ResetCameraState();
    arg0->unk_24.fovy = 30.0f;

    sp40 = sActivePokemon[arg1];
    GetEntityCenterPosition(sp40, &sp60);
    Camera_SetEyePositionOffset(arg0, sp60, 0, sp40->unk_4B0 << 0xE, 100.0f, 0.0f);
    GetEntityCenterPosition(sActivePokemon[arg1], &sp54);

    GetEntityCenterPosition(sActivePokemon[arg1 == 0], &sp48);
    sp40 = sActivePokemon[arg1 == 0];
    GetEntityCenterPosition(sp40, &sp60);

    if (sp48.y < sp54.y) {
        sp60.y = sp54.y * 1.8f;
        Camera_SetLookAtPosition(sp40, arg0, sp60, 0, 0, 0, 0);
    } else {
        sp60.y = 0.0f;
        Camera_SetLookAtPosition(sp40, arg0, sp60, 0, 0, 0, 0);
    }
}

s32 Camera_SmoothFocusOpponent(CameraStruct* arg0, s32 arg1) {
    UNUSED s32 pad;
    Vec3f sp58;
    Vec3f sp4C;
    Vec3f sp40;
    Vec3f sp34;
    f32 sp30;
    s16 sp2E;
    s16 sp2C;

    Math_ExponentialApproach(&gBattleState.unk_00->unk_94.z, 0.1f, 0.05f);
    GetEntityCenterPosition(sActivePokemon[arg1], &sp40);
    GetEntityCenterPosition(sActivePokemon[!arg1], &sp34);

    if (sp34.y < sp40.y) {
        GetEntityCenterPosition(sActivePokemon[!arg1], &sp4C);
    } else {
        GetEntityCenterPosition(sActivePokemon[!arg1], &sp4C);
        sp4C.y *= 1.3f;
    }

    Vector_Copy(&sp58, &arg0->unk_60.at);
    Math_CalcDistAndAngles(&sp58, &sp4C, &sp30, &sp2E, &sp2C);
    Camera_SetViewParameters(&sp58, &arg0->unk_60.at, gBattleState.unk_00->unk_94.z * sp30, sp2E, sp2C);

    if (sp30 <= 1.0f) {
        return 1;
    }
    return 0;
}

void Battle_ApplyPlayerAnimEffects(CameraStruct* arg0, unk_BattlePlayerEntity* arg1) {
    GetEntityCenterPosition(arg1, &gBattleState.unk_00->unk_D0);

    gBattleState.unk_00->unk_D0.x = GetEntityXOffset(arg1);
    gBattleState.unk_00->unk_D0.z = 0.0f;

    if (arg1->unk_654.unk_38.unk_44.unk_00 == 0x6E) {
        gCameraDistTarget = ClampScaledDistance(arg1, 4.5f, 300.0f);
        if (gCameraDistTarget <= 100.0f) {
            gCameraDistTarget = 100.0f;
        }

        if (gBattleState.unk_00->unk_D0.y < 20.0f) {
            gBattleState.unk_00->unk_D0.y = 20.0f;
        }
    } else {
        gCameraDistTarget = ClampScaledDistance(arg1, 3.5f, 300.0f);
    }

    Camera_SetLookAtPosition(arg1, arg0, gBattleState.unk_00->unk_D0, 0, GetPlayerSideYaw(arg1), 0.0f, 0.0f);
    Camera_SetEyePositionOffset(arg0, gBattleState.unk_00->unk_D0, 0, GetPlayerSideYaw(arg1), gCameraDistTarget, 0.0f);
}

void Camera_SetEntityWideView(CameraStruct* arg0, unk_BattlePlayerEntity* arg1) {
    f32 sp3C;

    GetEntityCenterPosition(arg1, &gBattleState.unk_00->unk_D0);
    sp3C = ClampScaledDistance(arg1, 8.0f, 300.0f);
    Camera_SetLookAtPosition(arg1, arg0, gBattleState.unk_00->unk_D0, 0, GetPlayerSideYaw(arg1), 0.0f, 0.0f);
    Camera_SetViewAndOffsetEye(arg0, 0, arg1->unk_4B0 << 0xE, sp3C, 0.0f);
}

void Camera_TransitionToEntity(CameraStruct* arg0, unk_BattlePlayerEntity* arg1, s32 arg2) {
    GetEntityCenterPosition(arg1, &gBattleState.unk_00->unk_D0);
    gCameraDistTarget = ClampScaledDistance(arg1, 0.5f, 100.0f);
    gCameraDistCurrent = ClampScaledDistance(arg1, 5.0f, 300.0f);
    Camera_SetLookAtPosition(arg1, arg0, gBattleState.unk_00->unk_D0, 0, GetPlayerSideYaw(arg1), gCameraDistTarget, 0.0f);
    Camera_SetEyePositionOffset(arg0, gBattleState.unk_00->unk_D0, 0, GetPlayerSideYaw(arg1) - (arg1->unk_4B0 * 0x31C7), gCameraDistCurrent, 0.0f);

    if (arg2 == 1) {
        ConfigureCameraForModel(arg1, arg0);
    } else {
        Battle_AdvanceCameraTimeline(arg0, arg1);
        Battle_AdvanceCameraTimeline(arg0, arg1);
    }

    Battle_AdvanceCameraTimeline(arg0, arg1);
}

void Camera_TransitionToEntitySide(CameraStruct* arg0, unk_BattlePlayerEntity* arg1, s32 arg2) {
    GetEntityCenterPosition(arg1, &gBattleState.unk_00->unk_D0);
    gCameraDistTarget = ClampScaledDistance(arg1, 0.5f, 100.0f);
    gCameraDistCurrent = ClampScaledDistance(arg1, 5.0f, 300.0f);
    Camera_SetLookAtPosition(arg1, arg0, gBattleState.unk_00->unk_D0, 0, GetPlayerSideYaw(arg1), gCameraDistTarget, 0.0f);
    Camera_SetEyePositionOffset(arg0, gBattleState.unk_00->unk_D0, 0x71C, GetPlayerSideYaw(arg1) - (arg1->unk_4B0 * 0x1555), gCameraDistCurrent,
                  0.0f);
    if (arg2 == 1) {
        ConfigureCameraForModel(arg1, arg0);
    } else {
        Battle_AdvanceCameraTimeline(arg0, arg1);
        Battle_AdvanceCameraTimeline(arg0, arg1);
    }
    Battle_AdvanceCameraTimeline(arg0, arg1);
}

void Camera_TransitionToEntityBack(CameraStruct* arg0, unk_BattlePlayerEntity* arg1, s32 arg2) {
    GetEntityCenterPosition(arg1, &gBattleState.unk_00->unk_D0);
    gCameraDistTarget = ClampScaledDistance(arg1, 0.5f, 100.0f);
    gCameraDistCurrent = ClampScaledDistance(arg1, 5.0f, 300.0f);
    Camera_SetLookAtPosition(arg1, arg0, gBattleState.unk_00->unk_D0, 0, GetPlayerSideYaw(arg1), gCameraDistTarget, 0.0f);
    Camera_SetEyePositionOffset(arg0, gBattleState.unk_00->unk_D0, 0xE38, GetPlayerSideYaw(arg1), gCameraDistCurrent, 0.0f);
    if (arg2 == 1) {
        ConfigureCameraForModel(arg1, arg0);
    } else {
        Battle_AdvanceCameraTimeline(arg0, arg1);
        Battle_AdvanceCameraTimeline(arg0, arg1);
    }
    Battle_AdvanceCameraTimeline(arg0, arg1);
}

void Camera_TransitionToEntityLow(CameraStruct* arg0, unk_BattlePlayerEntity* arg1, s32 arg2) {
    UNUSED s32 pad[4];
    s16 sp3E;

    GetEntityCenterPosition(arg1, &gBattleState.unk_00->unk_D0);
    gCameraDistTarget = ClampScaledDistance(arg1, 0.5f, 100.0f);
    gCameraDistCurrent = ClampScaledDistance(arg1, 5.0f, 300.0f);
    Camera_SetLookAtPosition(arg1, arg0, gBattleState.unk_00->unk_D0, 0, GetPlayerSideYaw(arg1), gCameraDistTarget, 0.0f);
    sp3E = GetPlayerSideYaw(arg1);
    Camera_SetEyePositionOffset(arg0, gBattleState.unk_00->unk_D0, 0, sp3E - (arg1->unk_4B0 * 0x1555), gCameraDistCurrent,
                  -Battle_GetEntityHeight(arg1) * 0.8);
    if (arg2 == 1) {
        ConfigureCameraForModel(arg1, arg0);
    } else {
        Battle_AdvanceCameraTimeline(arg0, arg1);
        Battle_AdvanceCameraTimeline(arg0, arg1);
    }
    Battle_AdvanceCameraTimeline(arg0, arg1);
}

void Battle_SetCameraMoveDefault(CameraStruct* arg0, unk_BattlePlayerEntity* arg1, s32 arg2) {
    GetEntityCenterPosition(arg1, &gBattleState.unk_00->unk_D0);
    gCameraDistTarget = ClampScaledDistance(arg1, 3.5f, 300.0f);
    Camera_SetLookAtPosition(arg1, arg0, gBattleState.unk_00->unk_D0, 0, GetPlayerSideYaw(arg1), 0.0f, 0.0f);
    Camera_SetEyePositionOffset(arg0, gBattleState.unk_00->unk_D0, 0, GetPlayerSideYaw(arg1), gCameraDistTarget, 0.0f);
    if (arg2 == 1) {
        ConfigureCameraForModel(arg1, arg0);
    } else {
        Battle_AdvanceCameraTimeline(arg0, arg1);
        Battle_AdvanceCameraTimeline(arg0, arg1);
    }
    Battle_AdvanceCameraTimeline(arg0, arg1);
}

void Battle_SetCameraMoveStatic(CameraStruct* arg0, unk_BattlePlayerEntity* arg1, s32 arg2) {
    GetEntityCenterPosition(arg1, &gBattleState.unk_00->unk_D0);
    gCameraDistTarget = ClampScaledDistance(arg1, 3.5f, 300.0f);
    Camera_SetLookAtPosition(arg1, arg0, gBattleState.unk_00->unk_D0, 0, GetPlayerSideYaw(arg1), 0.0f, 0.0f);
    Camera_SetEyePositionOffset(arg0, gBattleState.unk_00->unk_D0, 0, GetPlayerSideYaw(arg1), gCameraDistTarget, 0.0f);
    if (arg2 == 1) {
        ConfigureCameraForModel(arg1, arg0);
    }
}

void Battle_SetCameraPreset(CameraStruct* arg0, unk_BattlePlayerEntity* arg1, s32 arg2, s32 arg3) {
    GetEntityCenterPosition(arg1, &gCameraPreset.unk_00);
    Battle_PlayCameraTransition(&gBattleCameraPresetTable[arg2], arg0, arg1);
    Battle_ApplyCameraSettings(arg0, arg1, 1);
    Battle_UpdateCameraMatrix(arg0);
    if (arg3 == 1) {
        ConfigureCameraForModel(arg1, arg0);
    }
}

void Battle_SetCameraOpponentStandard(CameraStruct* arg0, unk_BattlePlayerEntity* arg1) {
    Battle_ResetCameraState();
    GetEntityCenterPosition(arg1, &gBattleState.unk_00->unk_D0);
    gCameraDistTarget = ClampScaledDistance(arg1, 5.0f, 400.0f);
    Camera_SetLookAtPosition(arg1, arg0, gBattleState.unk_00->unk_D0, 0, arg1->unk_4B0 << 0xE, 0.0f, 0.0f);
    Camera_SetEyePositionOffset(arg0, gBattleState.unk_00->unk_D0, 0, arg1->unk_4B0 * 0xE38, gCameraDistTarget, 0.0f);
    ConfigureCameraForModel(arg1, arg0);
}

void Battle_SetCameraOpponentOffset(CameraStruct* arg0, unk_BattlePlayerEntity* arg1) {
    Battle_ResetCameraState();
    GetEntityCenterPosition(arg1, &gBattleState.unk_00->unk_D0);
    gCameraDistTarget = ClampScaledDistance(arg1, 5.0f, 400.0f);
    Camera_SetLookAtPosition(arg1, arg0, gBattleState.unk_00->unk_D0, 0, arg1->unk_4B0 << 0xE, 0.0f, 0.0f);
    Camera_SetEyePositionOffset(arg0, gBattleState.unk_00->unk_D0, 0x1555, arg1->unk_4B0 * 0xE38, gCameraDistTarget, 0.0f);
    ConfigureCameraForModel(arg1, arg0);
}

void Battle_SetCameraOpponentHigh(CameraStruct* arg0, unk_BattlePlayerEntity* arg1) {
    GetEntityCenterPosition(arg1, &gBattleState.unk_00->unk_D0);
    gCameraDistTarget = ClampScaledDistance(arg1, 5.0f, 400.0f);
    Camera_SetLookAtPosition(arg1, arg0, gBattleState.unk_00->unk_D0, 0, arg1->unk_4B0 << 0xE, 0.0f, 0.0f);
    Camera_SetEyePositionOffset(arg0, gBattleState.unk_00->unk_D0, 0, arg1->unk_4B0 * 0xE38, gCameraDistTarget, 2.0f * Battle_GetEntityHeight(arg1));
    ConfigureCameraForModel(arg1, arg0);
}

void Battle_SetCameraOpponentLow(CameraStruct* arg0, unk_BattlePlayerEntity* arg1) {
    GetEntityCenterPosition(arg1, &gBattleState.unk_00->unk_D0);
    gCameraDistTarget = ClampScaledDistance(arg1, 5.0f, 400.0f);
    Camera_SetLookAtPosition(arg1, arg0, gBattleState.unk_00->unk_D0, 0, arg1->unk_4B0 << 0xE, 0.0f, 0.0f);
    Camera_SetEyePositionOffset(arg0, gBattleState.unk_00->unk_D0, 0, arg1->unk_4B0 * 0xE38, gCameraDistTarget, -Battle_GetEntityHeight(arg1) * 0.8f);
    if (arg0->unk_60.eye.y <= 15.0f) {
        arg0->unk_60.eye.y = 15.0f;
    }
    ConfigureCameraForModel(arg1, arg0);
}

void Battle_SetCameraOpponentClose(CameraStruct* arg0, unk_BattlePlayerEntity* arg1) {
    GetEntityCenterPosition(arg1, &gBattleState.unk_00->unk_D0);
    gCameraDistTarget = ClampScaledDistance(arg1, 3.5f, 300.0f);
    Camera_SetLookAtPosition(arg1, arg0, gBattleState.unk_00->unk_D0, 0, GetPlayerSideYaw(arg1), 0.0f, 0.0f);
    Camera_SetEyePositionOffset(arg0, gBattleState.unk_00->unk_D0, 0, GetPlayerSideYaw(arg1), gCameraDistTarget, 0.0f);
    ConfigureCameraForModel(arg1, arg0);
}

void Battle_SetCameraMoveDynamic(CameraStruct* arg0, unk_BattlePlayerEntity* arg1, s32 arg2) {
    GetEntityCenterPosition(arg1, &gBattleState.unk_00->unk_D0);
    gCameraDistTarget = ClampScaledDistance(arg1, 3.5f, 300.0f);
    gCameraDistCurrent = ClampScaledDistance(arg1, 0.5f, 100.0f);
    Camera_SetLookAtPosition(arg1, arg0, gBattleState.unk_00->unk_D0, 0, GetPlayerSideYaw(arg1), gCameraDistCurrent, 0.0f);
    Camera_SetEyePositionOffset(arg0, gBattleState.unk_00->unk_D0, 0, GetPlayerSideYaw(arg1) - (arg1->unk_4B0 * 0x1555), gCameraDistTarget, 0.0f);
    if (arg2 == 1) {
        ConfigureCameraForModel(arg1, arg0);
    }
}

void Battle_SetCameraMoveSimple(CameraStruct* arg0, unk_BattlePlayerEntity* arg1) {
    GetEntityCenterPosition(arg1, &gBattleState.unk_00->unk_D0);
    gCameraDistTarget = ClampScaledDistance(arg1, 3.5f, 300.0f);
    Camera_SetLookAtPosition(arg1, arg0, gBattleState.unk_00->unk_D0, 0, GetPlayerSideYaw(arg1), 0.0f, 0.0f);
    Camera_SetEyePositionOffset(arg0, gBattleState.unk_00->unk_D0, 0, GetPlayerSideYaw(arg1), gCameraDistTarget, 0.0f);
    ConfigureCameraForModel(arg1, arg0);
}

void Battle_ExecuteMove(unk_BattlePlayerEntity* arg0, CameraStruct* arg1, s32 arg2, s32 arg3) {
    Battle_ResetCameraState();
    switch (arg2) {
        case 0:
            Battle_SetCameraMoveDefault(arg1, arg0, arg3);
            break;

        case 1:
            Battle_SetCameraMoveStatic(arg1, arg0, arg3);
            break;

        case 2:
            Camera_TransitionToEntity(arg1, arg0, arg3);
            break;

        case 3:
            Camera_TransitionToEntityBack(arg1, arg0, arg3);
            break;

        case 4:
            Battle_SetCameraPreset(arg1, arg0, 0, arg3);
            break;

        case 5:
            Battle_SetCameraPreset(arg1, arg0, 1, arg3);
            break;

        case 6:
            Camera_TransitionToEntitySide(arg1, arg0, arg3);
            break;

        case 7:
            Camera_TransitionToEntityLow(arg1, arg0, arg3);
            break;

        case 8:
            Battle_SetCameraPreset(arg1, arg0, 2, arg3);
            break;

        case 9:
            Battle_SetCameraPreset(arg1, arg0, 3, arg3);
            break;

        case 10:
            Battle_SetCameraPreset(arg1, arg0, 4, arg3);
            break;

        case 11:
            Battle_SetCameraPreset(arg1, arg0, 5, arg3);
            break;

        default:
            Camera_TransitionToEntity(arg1, arg0, arg3);
            break;
    }
}

void Battle_PlayMoveEffect(unk_BattlePlayerEntity* arg0, CameraStruct* arg1, s32 arg2) {
    Battle_ResetCameraState();
    switch (arg2) {
        case 0:
            Camera_TransitionToEntity(arg1, arg0, 1);
            break;
        case 1:
            Camera_TransitionToEntitySide(arg1, arg0, 1);
            break;
        case 2:
            Camera_TransitionToEntityLow(arg1, arg0, 1);
            break;
        case 3:
            Battle_SetCameraMoveDefault(arg1, arg0, 1);
            break;
        case 4:
            Battle_SetCameraMoveDynamic(arg1, arg0, 1);
            break;
        default:
            Camera_TransitionToEntity(arg1, arg0, 1);
            break;
    }
}

void Battle_QueueOpponentMove(unk_BattlePlayerEntity* arg0, CameraStruct* arg1, s32 arg2) {
    Battle_ResetCameraState();
    switch (arg2) {
        case 0:
            Battle_SetCameraOpponentStandard(arg1, arg0);
            break;

        case 1:
            Battle_SetCameraOpponentHigh(arg1, arg0);
            break;

        case 2:
            Battle_SetCameraOpponentLow(arg1, arg0);
            break;

        case 3:
            Battle_SetCameraOpponentClose(arg1, arg0);
            break;

        case 4:
            Battle_SetCameraOpponentOffset(arg1, arg0);
            break;

        case 5:
            Battle_SetCameraOpponentHigh(arg1, arg0);
            break;

        case 6:
            Battle_SetCameraOpponentLow(arg1, arg0);
            break;

        case 7:
            Battle_SetCameraOpponentClose(arg1, arg0);
            break;

        default:
            Battle_SetCameraOpponentClose(arg1, arg0);
            break;
    }
}
