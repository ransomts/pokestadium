#include "battle_engine.h"
#include "src/12D80.h"
#include "src/F420.h"

unk_D_843901B0 gCameraPreset;
f32 gCameraDistTarget;
f32 gCameraDistCurrent;

static s32 gBattleFrameCounter = 0;

f32 BattleScene_ScaleCameraDistance(BattlePlayerEntity* arg0, f32 arg1, f32 arg2) {
    f32 temp_fv1 = BattleScene_GetParticipantModelRadiusScaled(arg0) * arg1;

    if (arg2 < temp_fv1) {
        return arg2;
    }
    return temp_fv1;
}

s32 BattleScene_AdvanceCameraSubstepCounter(s32 arg0) {
    gBattleScene.posX->unk_10++;
    if (gBattleScene.posX->unk_10 >= arg0) {
        gBattleScene.posX->unk_10 = 0;
        return 1;
    }
    return 0;
}

s32 BattleScene_AdvanceCameraFrameCounter(s32 arg0) {
    gBattleScene.posX->unk_14++;
    if (gBattleScene.posX->unk_14 >= arg0) {
        gBattleScene.posX->unk_14 = 0;
        return 1;
    }
    return 0;
}

s32 BattleScene_AdvanceCameraFrameCounterUntil(s32 arg0) {
    if (gBattleScene.posX->unk_14 >= arg0) {
        return 1;
    }
    gBattleScene.posX->unk_14++;
    return 0;
}

s32 BattleScene_IsCameraFrameCounterAtLeast(s32 arg0) {
    if (gBattleScene.posX->unk_14 >= arg0) {
        return 1;
    }
    return 0;
}

void BattleScene_SetActivePokemonIndex(s32 arg0) {
    gBattleScene.posX->unk_2C = arg0;
}

void BattleScene_ResetCameraFrameCounter(void) {
    gBattleScene.posX->unk_14 = 0;
}

void BattleScene_ResetCameraSubstepCounter(void) {
    gBattleScene.posX->unk_10 = 0;
}

void BattleScene_SetCameraAtAndEyeFromAngles(CameraStruct* arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, s16 arg5, s16 arg6) {
    Vec3f_SetComponentsDuplicate(&arg0->unk_60.at, arg1, arg2, arg3);
    Camera_ComputeEyeFromAngles(&arg0->unk_60.at, &arg0->unk_60.eye, arg4, arg5, arg6);
}

void BattleScene_GetOwnerCameraAnchor(BattlePlayerEntity* arg0, Vec3f* arg1) {
    UNUSED s32 pad;
    u8 sp18[] = {
        0x52, 0x73, 0x59, 0x91, 0x5F, 0x82, 0x58, 0x66, 0x0A,
    };

    if (BattleScene_ByteArrayContains(arg0->unk_000.unk_01A, sp18, 9) != 0) {
        BattleScene_GetOwnerBoneOrDefaultAnchor(arg0, arg1, 9);
    } else {
        BattleScene_GetOwnerBoneOrDefaultAnchor(arg0, arg1, 0x64);
    }
}

void BattleScene_GetOwnerBoneOrDefaultAnchor(BattlePlayerEntity* arg0, Vec3f* arg1, s32 arg2) {
    if (GeoRender_FindAnchorPosition(&arg0->unk_000, arg2, arg1) == NULL) {
        BattleAnim_GetOwnerDefaultAnchorPosition(arg0, arg1);
        arg1->x = BattleScene_GetParticipantModelXOffset(arg0);
        arg1->z = 0.0f;
    }
}

void BattleScene_SetCameraModeAndStep(s32 arg0, s32 arg1) {
    gBattleScene.posX->unk_1C = arg0;
    gBattleScene.posX->unk_20 = arg1;
}

void BattleScene_SetCameraClipPlanes(CameraStruct* arg0, f32 arg1, f32 arg2) {
    arg0->unk_24.near = arg1;
    arg0->unk_24.far = arg2;
}

void BattleScene_SetCameraSubstate(s32 arg0, u16 arg1) {
    gBattleScene.posX->unk_30 = arg0;
    gBattleScene.posX->unk_2E = arg1;
}

void BattleScene_ApplyCameraPhaseDefaults(void) {
    if (gBattleScene.posX->unk_18 == 2) {
        if (gBattleScene.posX->unk_44 == 1) {
            BattleScene_SetCameraModeAndStep(1, 0x32);
        }

        if (gBattleScene.posX->unk_44 == 2) {
            gBattleScene.posX->unk_2C = gBattleScene.posX->unk_2A;
            BattleScene_SetCameraModeAndStep(2, 0);
        }
    }
}

void BattleScene_SetDamageShakeAmplitude(BattlePlayerEntity* arg0) {
    PokemonData* ptr = &arg0->boundRoster->unk_01C[arg0->animationState.unk_08];

    gBattleScene.posX->unk_68 = ((ptr->posY - arg0->animationState.unk_38.unk_0C) / 996.0f) * 1400.0f;

    if (gBattleScene.posX->unk_68 == 0.0f) {
        gBattleScene.posX->unk_68 = 0.0f;
    } else if (gBattleScene.posX->unk_68 <= 20.0f) {
        gBattleScene.posX->unk_68 = 20.0f;
    } else if (gBattleScene.posX->unk_68 >= 50.0f) {
        gBattleScene.posX->unk_68 = 50.0f;
    }

    gBattleScene.posX->cameraShakePhase = 0;

    if (gBattleUpdateHPFlag != 0) {
        gBattleScene.posX->unk_68 = 25.0f;
    }
}

void BattleScene_ApplyCameraShake(CameraStruct* arg0) {
    UNUSED s32 pad;
    f32 sp30;
    f32 temp_fv0;
    s16 sp2A;
    s16 sp28;

    BattleAnim_CalculateDistanceAngles(&arg0->unk_60.eye, &arg0->unk_60.at, &sp30, &sp28, &sp2A);
    gBattleScene.posX->cameraShakePhase += 0x38E0;
    BattleAnim_ApproachF(&gBattleScene.posX->unk_68, 0.0f, 0.18f);

    temp_fv0 = COSS(gBattleScene.posX->cameraShakePhase) * gBattleScene.posX->unk_68;

    arg0->unk_60.eye.y += temp_fv0 / 3.0f;
    arg0->unk_60.at.y += temp_fv0 / 3.0f;
    arg0->unk_60.eye.x += temp_fv0 * SINS(sp2A + 0x4000);
    arg0->unk_60.at.x += temp_fv0 * SINS(sp2A + 0x4000);
}

void BattleScene_StartCameraShake(UNUSED BattlePlayerEntity* arg0) {
    gBattleScene.posX->unk_68 = 30.0f;
    gBattleScene.posX->cameraShakePhase = 0;
}

s32 BattleScene_IsCameraAngleSettled(s16 arg0, s16 arg1) {
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

s32 BattleScene_ApproachCameraRoll(CameraStruct* arg0, s16 arg1, s16 arg2) {
    if (arg1 > 0) {
        gBattleScene.posX->unk_58 -= arg1;
        if ((gBattleScene.posX->unk_58 < arg2) && ((arg2 - arg1) < gBattleScene.posX->unk_58)) {
            gBattleScene.posX->unk_58 = arg2;
            return 1;
        }
    } else {
        gBattleScene.posX->unk_58 -= arg1;
        if ((arg2 < gBattleScene.posX->unk_58) && (gBattleScene.posX->unk_58 < (arg2 - arg1))) {
            gBattleScene.posX->unk_58 = arg2;
            return 1;
        }
    }

    Camera_ComputeEyeFromAngles(&arg0->unk_60.at, &arg0->unk_60.eye, gBattleScene.posX->unk_5C, gBattleScene.posX->unk_56,
                  gBattleScene.posX->unk_58);
    return 0;
}

s32 BattleScene_ApproachCameraRollNoEyeUpdate(UNUSED CameraStruct* arg0, s16 arg1, s16 arg2) {
    gBattleScene.posX->unk_58 -= arg1;

    if (arg1 > 0) {
        if ((arg2 >= gBattleScene.posX->unk_58) && (gBattleScene.posX->unk_58 >= (arg2 - arg1))) {
            gBattleScene.posX->unk_58 = arg2;
            return 1;
        }
    } else if ((gBattleScene.posX->unk_58 >= arg2) && ((arg2 - arg1) >= gBattleScene.posX->unk_58)) {
        gBattleScene.posX->unk_58 = arg2;
        return 1;
    }
    return 0;
}

void BattleScene_SetCameraAnglesAndDistance(s16 arg0, s16 arg1, f32 arg2) {
    gBattleScene.posX->unk_56 = arg0;
    gBattleScene.posX->unk_58 = arg1;
    gBattleScene.posX->unk_5C = arg2;
}

void BattleScene_SetCameraSendOutShot(CameraStruct* arg0, s32 arg1) {
    static u8 gDefaultModelId = 0x5F;
    static u16 gDefaultModelParam = 0x38F;

    BattlePlayerAnimState* sp6C;
    UNUSED s32 pad;
    BattlePlayerEntity* temp_s0;
    Vec3f sp58;
    f32 sp54;
    UNUSED u16 pad2;
    UNUSED u8 pad3;
    u8 sp50;
    UNUSED u16 pad4;
    u16 sp4C;
    s32 idx = gBattleScene.posX->unk_2C == 0;

    sp6C = &sActivePokemon[idx]->animationState;
    sp50 = gDefaultModelId;
    sp4C = gDefaultModelParam;
    temp_s0 = sActivePokemon[arg1 == 0];
    arg0->unk_24.fovy = 60.0f;

    BattleScene_ResetCameraFrameCounter();
    BattleAnim_GetOwnerDefaultAnchorPosition(temp_s0, &sp58);

    sp58.y /= 3.0f;
    if (temp_s0->animationState.unk_34 & 0x4000) {
        sp58.y = 0.0f;
    }

    BattleScene_SetCameraAtFromAnchor(temp_s0, arg0, sp58, 0, 0, 0.0f, 0.0f);

    if ((sp6C->unk_2D != 0x10) && !(sp6C->unk_34 & 0x4000)) {
        BattleScene_EnterStateRow(temp_s0, 1);
    }

    temp_s0 = sActivePokemon[arg1];
    if (temp_s0->unk_448.unk_24.unk_0C.x == 0.0f) {
        BattleAnim_GetOwnerDefaultAnchorPosition(temp_s0, &sp58);
    } else {
        BattleAnim_Vec3fCopy(&sp58, &temp_s0->unk_448.unk_24.unk_0C);
        sp58.y += temp_s0->unk_000.unk_024.y - BattleScene_GetParticipantModelHeight(temp_s0);
    }

    sp54 = BattleScene_ScaleCameraDistance(temp_s0, 3.0f, 300.0f);
    if ((BattleScene_ByteArrayContains(temp_s0->unk_000.unk_01A, &sp50, 1) != 0) && (arg1 == 1)) {
        BattleScene_SetCameraEyeFromPosition(arg0, sp58, 0, BattleScene_GetParticipantFacingAngle(temp_s0) - (temp_s0->sideSign * 0x6AA4), sp54, 20.0f);
    } else if (BattleScene_ByteArrayContains(temp_s0->unk_000.unk_01A, (u8*)&sp4C, 2) != 0) {
        BattleScene_SetCameraEyeFromPosition(arg0, sp58, 0, BattleScene_GetParticipantFacingAngle(temp_s0) - (temp_s0->sideSign * 0x6AA4), sp54, 20.0f);
    } else {
        BattleScene_SetCameraEyeFromPosition(arg0, sp58, 0, BattleScene_GetParticipantFacingAngle(temp_s0) - (temp_s0->sideSign * 0x754E), sp54, 0.0f);
    }
}

void BattleScene_ClampCameraEyeFloor(CameraStruct* arg0) {
    if (arg0->unk_60.eye.y <= 13.0f) {
        arg0->unk_60.eye.y = 13.0f;
    }
}

void BattleScene_UpdateCameraModelOffset(BattlePlayerEntity* arg0, CameraStruct* arg1) {
    unk_D_84390010_448* sp38 = &arg0->unk_448;
    UNUSED s32 pad[5];
    f32 sp3C = 0.0f;

    if (BattleScene_ByteArrayContains(arg0->unk_000.unk_01A, &gPokemonSfxId_0, 1) != 0) {
        sp3C = BattleAnim_GetOwnerModelHeight(arg0) / 1.5f;
    } else if (BattleScene_ByteArrayContains(arg0->unk_000.unk_01A, &gPokemonSfxId_1, 1) != 0) {
        sp3C = BattleAnim_GetOwnerModelHeight(arg0) * 0.5f;
    } else if ((BattleScene_ByteArrayContains(arg0->unk_000.unk_01A, &gPokemonSfxId_2, 1) != 0) && (arg0->animationState.unk_34 & 0x200)) {
        sp3C = 2.0f * BattleAnim_GetOwnerModelHeight(arg0);
    } else if ((BattleScene_ByteArrayContains(arg0->unk_000.unk_01A, gPokemonSfxId_3, 2) != 0) && (arg0->animationState.unk_34 & 0x200)) {
        sp3C = BattleAnim_GetOwnerModelHeight(arg0) * 1.5f;
    }

    Vec3f_SetComponentsDuplicate(&arg0->unk_448.unk_18, arg0->unk_448.unk_24.posX.x, arg0->unk_448.unk_24.posX.y,
                  arg0->unk_448.unk_24.posX.z);
    arg0->unk_448.unk_18.y = (arg0->unk_000.unk_024.y - BattleScene_GetParticipantModelHeight(arg0)) + arg0->unk_448.unk_18.y + sp3C;
    BattleAnim_Vec3fCopy(&gBattleScene.posX->unk_B8, &arg1->unk_60.at);
    BattleAnim_Vec3fCopy(&gBattleScene.posX->cameraEye, &arg1->unk_60.eye);
    Vec3f_CalculateDistanceAngles(&gBattleScene.posX->unk_B8, &gBattleScene.posX->cameraEye, &gBattleScene.posX->unk_70, &sp38->unk_44,
                  &sp38->unk_46);
    Vec3f_CalculateDistanceAngles(&arg0->unk_448.unk_18, &arg1->unk_60.at, &sp38->unk_4C, &sp38->unk_44, &sp38->unk_46);
    gBattleScene.posX->unk_6C = 0.0f;
    gBattleScene.posX->unk_74 = 0.0f;
}

void BattleScene_ClearCameraOffsetVectors(void) {
    Vec3f_SetComponentsDuplicate(&gBattleScene.posX->unk_94, 0.0f, 0.0f, 0.0f);
    Vec3f_SetComponentsDuplicate(&gBattleScene.posX->unk_A0, 0.0f, 0.0f, 0.0f);
}

void BattleScene_SetCameraAtFromAnchor(BattlePlayerEntity* arg0, CameraStruct* arg1, Vec3f arg2, s16 arg3, s16 arg4, f32 arg5, f32 arg6) {
    Camera_ComputeEyeFromAngles(&arg2, &arg1->unk_60.at, arg5, arg3, arg4);
    arg1->unk_60.at.y += arg6;
    arg1->unk_60.at.y += BattleScene_GetParticipantEyeHeight(arg0);
}

void BattleScene_SetCameraAtFromPosition(CameraStruct* arg0, Vec3f arg1, s16 arg2, s16 arg3, f32 arg4, f32 arg5) {
    Camera_ComputeEyeFromAngles(&arg1, &arg0->unk_60.at, arg4, arg2, arg3);
    arg0->unk_60.at.y += arg5;
}

void BattleScene_SetCameraEyeFromPosition(CameraStruct* arg0, Vec3f arg1, s16 arg2, s16 arg3, f32 arg4, f32 arg5) {
    Camera_ComputeEyeFromAngles(&arg1, &arg0->unk_60.eye, arg4, arg2, arg3);
    arg0->unk_60.eye.y += arg5;
}

void BattleScene_SetCameraEyeFromAt(CameraStruct* arg0, s16 arg1, s16 arg2, f32 arg3, f32 arg4) {
    Camera_ComputeEyeFromAngles(&arg0->unk_60.at, &arg0->unk_60.eye, arg3, arg1, arg2);
    arg0->unk_60.eye.y += arg4;
}

void BattleScene_SetCameraEyeAndStoreAngles(CameraStruct* arg0, Vec3f arg1, s16 arg2, s16 arg3, f32 arg4, f32 arg5) {
    BattleScene_SetCameraAnglesAndDistance(arg2, arg3, arg4);
    Camera_ComputeEyeFromAngles(&arg1, &arg0->unk_60.eye, arg4, arg2, arg3);
    arg0->unk_60.eye.y += arg5;
}

void BattleScene_SetCameraEyeAndStoreAnglesFromAt(CameraStruct* arg0, s16 arg1, s16 arg2, f32 arg3, f32 arg4) {
    BattleScene_SetCameraAnglesAndDistance(arg1, arg2, arg3);
    Camera_ComputeEyeFromAngles(&arg0->unk_60.at, &arg0->unk_60.eye, arg3, arg1, arg2);
    arg0->unk_60.eye.y += arg4;
}

void BattleScene_CameraHelperNop(UNUSED CameraStruct* arg0) {
}

void BattleScene_SnapFloatPair(f32* arg0, f32* arg1) {
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

void BattleScene_ApplyOwnerFramingAdjustments(CameraStruct* arg0, BattlePlayerEntity* arg1, UNUSED f32 arg2) {
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

    BattleAnim_Vec3fCopy(&sp4C, &arg0->unk_60.at);
    BattleAnim_Vec3fCopy(&sp40, &arg0->unk_60.at);
    BattleScene_GetOwnerCameraAnchor(arg1, &sp64);
    Vec3f_CalculateDistanceAngles(&sp64, &arg1->unk_448.unk_18, &sp3C, &sp36, &sp34);

    switch (arg1->unk_000.unk_01A) {
        case 0x5F:
            arg0->unk_24.fovy = 50.0f;
            return;

        case 0x82:
            arg0->unk_24.fovy = 50.0f;
            if (sp3C < (BattleScene_GetParticipantModelRadius(arg1) * 0.5f)) {
                BattleAnim_Vec3fCopy(&sp64, &arg1->unk_448.unk_18);
            }
            break;

        case 0x1D:
        case 0x29:
        case 0x32:
        case 0x33:
        case 0x5B:
            if (sp3C < (BattleScene_GetParticipantModelRadius(arg1) * 5.0f)) {
                BattleAnim_Vec3fCopy(&sp64, &arg1->unk_448.unk_18);
            }
            break;

        case 0x12:
            if (sp3C < (BattleScene_GetParticipantModelRadius(arg1) * 1.5f)) {
                BattleAnim_Vec3fCopy(&sp64, &arg1->unk_448.unk_18);
            }
            break;

        case 0x27:
        case 0x58:
        case 0x59:
        case 0x96:
            if (sp3C < BattleScene_GetParticipantModelRadius(arg1)) {
                BattleAnim_Vec3fCopy(&sp64, &arg1->unk_448.unk_18);
            }
            break;

        case 0x4A:
        case 0x65:
        case 0x67:
            if (sp3C < (BattleScene_GetParticipantModelRadius(arg1) / 1.2f)) {
                BattleAnim_Vec3fCopy(&sp64, &arg1->unk_448.unk_18);
            }
            break;

        case 0x7:
        case 0x11:
        case 0x16:
        case 0x4C:
        case 0x5C:
        case 0x83:
            if (sp3C < (BattleScene_GetParticipantModelRadius(arg1) / 3.0f)) {
                BattleAnim_Vec3fCopy(&sp64, &arg1->unk_448.unk_18);
            }
            break;

        default:
            if (sp3C < (BattleScene_GetParticipantModelRadius(arg1) * 0.5f)) {
                BattleAnim_Vec3fCopy(&sp64, &arg1->unk_448.unk_18);
            }
            break;
    }

    sp64.y = arg1->unk_448.unk_18.y;
    Camera_ComputeEyeFromAngles(&sp64, &sp58, sp2C->unk_4C, sp2C->unk_44, sp2C->unk_46);
    sp4C.y = sp58.y;
    Vec3f_CalculateDistanceAngles(&sp4C, &sp58, &sp3C, &sp36, &sp34);

    switch (arg1->unk_000.unk_01A) {
        case 0x58:
        case 0x59:
        case 0x87:
            var_fv1 = sp3C / (BattleScene_GetParticipantModelRadius(arg1) * 50.0f);
            break;

        case 0x16:
        case 0x4C:
        case 0x96:
            var_fv1 = sp3C / (BattleScene_GetParticipantModelRadius(arg1) * 1.5f);
            break;

        default:
            temp_fv1 = sp3C / BattleScene_GetParticipantModelRadius(arg1);
            if (temp_fv1 <= 0.1f) {
                var_fv1 = sp3C / (BattleScene_GetParticipantModelRadius(arg1) * 15.0f);
            } else if (temp_fv1 <= 0.2f) {
                var_fv1 = sp3C / (BattleScene_GetParticipantModelRadius(arg1) * 7.0f);
            } else if (temp_fv1 <= 0.3f) {
                var_fv1 = sp3C / (BattleScene_GetParticipantModelRadius(arg1) * 5.0f);
            } else if (temp_fv1 <= 0.4f) {
                var_fv1 = sp3C / (BattleScene_GetParticipantModelRadius(arg1) * 3.0f);
            } else if (temp_fv1 <= 0.5f) {
                var_fv1 = sp3C / (BattleScene_GetParticipantModelRadius(arg1) * 1.5f);
            } else {
                var_fv1 = sp3C / BattleScene_GetParticipantModelRadius(arg1);
            }
            break;
    }

    if (var_fv1 > 1.0f) {
        var_fv1 = 1.0f;
    }

    Camera_ComputeEyeFromAngles(&sp4C, &arg0->unk_60.at, sp3C * var_fv1, 0, sp34);
    BattleScene_GetOwnerCameraAnchor(arg1, &sp64);
    Camera_ComputeEyeFromAngles(&sp64, &sp58, sp2C->unk_4C, sp2C->unk_44, sp2C->unk_46);

    sp3C = sp40.y - sp58.y;
    if (sp3C < 0.0f) {
        sp3C *= -1.0f;
    }

    if (arg1->animationMode == 0xD) {
        var_fv1 = 0;
    } else if ((arg1->unk_000.unk_01A == 0x58) || (arg1->unk_000.unk_01A == 0x59)) {
        temp_fv1 = sp3C / BattleScene_GetParticipantModelRadius(arg1);
        if (temp_fv1 <= 0.05f) {
            var_fv1 = sp3C / (BattleScene_GetParticipantModelRadius(arg1) * 90.0f);
        } else if (temp_fv1 <= 0.1f) {
            var_fv1 = sp3C / (BattleScene_GetParticipantModelRadius(arg1) * 70.0f);
        } else if (temp_fv1 <= 0.2f) {
            var_fv1 = sp3C / (BattleScene_GetParticipantModelRadius(arg1) * 65.0f);
        } else if (temp_fv1 <= 0.3f) {
            var_fv1 = sp3C / (BattleScene_GetParticipantModelRadius(arg1) * 63.0f);
        } else {
            var_fv1 = sp3C / (BattleScene_GetParticipantModelRadius(arg1) * 45.0f);
        }
    } else {
        temp_fv1 = sp3C / BattleScene_GetParticipantModelRadius(arg1);
        if (temp_fv1 <= 0.05f) {
            var_fv1 = sp3C / (BattleScene_GetParticipantModelRadius(arg1) * 50.0f);
        } else if (temp_fv1 <= 0.1f) {
            var_fv1 = sp3C / (BattleScene_GetParticipantModelRadius(arg1) * 30.0f);
        } else if (temp_fv1 <= 0.2f) {
            var_fv1 = sp3C / (BattleScene_GetParticipantModelRadius(arg1) * 25.0f);
        } else if (temp_fv1 <= 0.3f) {
            var_fv1 = sp3C / (BattleScene_GetParticipantModelRadius(arg1) * 23.0f);
        } else {
            var_fv1 = sp3C / (BattleScene_GetParticipantModelRadius(arg1) * 15.0f);
        }
    }

    if (var_fv1 > 1.0f) {
        var_fv1 = 1.0f;
    }

    BattleAnim_ApproachF(&sp40.y, sp58.y, var_fv1);
    arg0->unk_60.at.y = sp40.y;
    BattleScene_SnapFloatPair(&arg0->unk_60.at.x, &arg0->unk_60.eye.x);
    BattleScene_SnapFloatPair(&arg0->unk_60.at.y, &arg0->unk_60.eye.y);
    BattleScene_SnapFloatPair(&arg0->unk_60.at.z, &arg0->unk_60.eye.z);
}

void BattleScene_RecomputeCameraDistance(CameraStruct* arg0, BattlePlayerEntity* arg1) {
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

    Vec3f_CalculateDistanceAngles(&gBattleScene.posX->unk_B8, &gBattleScene.posX->cameraEye, &sp38, &sp36, &sp34);
    Vec3f_CalculateDistanceAngles(&arg0->unk_60.at, &arg0->unk_60.eye, &sp44, &sp3E, &sp3C);

    temp_lo = sp34 / 182;
    if ((temp_lo == 0x5A) || (temp_lo == -0x5A)) {
        if (BattleScene_ByteArrayContains(arg1->unk_000.unk_01A, sp2C, sizeof(sp2C)) != 0) {
            sp44 = sp38;
        } else {
            sp44 = Math_StepToF(sp44, sp38, 30.0f, 5.0f);
        }
    } else {
        var_fv0_2 = gBattleScene.posX->unk_70 - sp44;
        if (var_fv0_2 < 0.0f) {
            var_fv0_2 *= -1.0f;
        }

        if (sp44 < sp38) {
            sp44 = Math_StepToF(sp44, gBattleScene.posX->unk_70, var_fv0_2 * 0.4f, var_fv0_2 * 0.08f);
        }
    }
    Camera_ComputeEyeFromAngles(&arg0->unk_60.at, &arg0->unk_60.eye, sp44, sp36, sp34);
}

void BattleScene_ReframeAndRecomputeDistance(CameraStruct* arg0, BattlePlayerEntity* arg1) {
    BattleScene_ApplyOwnerFramingAdjustments(arg0, arg1, 50.0f);
    BattleScene_RecomputeCameraDistance(arg0, arg1);
}

void BattleScene_ReframeAndRecomputeDistanceForSwitch(CameraStruct* arg0, BattlePlayerEntity* arg1) {
    BattleScene_ApplyOwnerFramingAdjustments(arg0, arg1, 90.0f);
    BattleScene_RecomputeCameraDistance(arg0, arg1);
}

void BattleScene_ApplyOwnerFramingOnly(CameraStruct* arg0, BattlePlayerEntity* arg1) {
    BattleScene_ApplyOwnerFramingAdjustments(arg0, arg1, 50.0f);
}

void BattleScene_UpdateCameraTargetFromOwner(CameraStruct* arg0, BattlePlayerEntity* arg1) {
    unk_D_84390010_448* ptr = &arg1->unk_448;
    UNUSED s32 pad;
    Vec3f sp54;
    Vec3f sp48;
    Vec3f sp3C;
    f32 sp38;
    f32 var_fa0;
    s16 sp32;
    s16 sp30;

    BattleAnim_Vec3fCopy(&sp3C, &arg0->unk_60.at);
    BattleScene_GetOwnerCameraAnchor(arg1, &sp54);
    Vec3f_CalculateDistanceAngles(&sp54, &arg1->unk_448.unk_18, &sp38, &sp32, &sp30);

    if (sp38 < (BattleScene_GetParticipantModelRadius(arg1) * 1.1f)) {
        BattleAnim_Vec3fCopy(&sp54, &arg1->unk_448.unk_18);
    }

    Camera_ComputeEyeFromAngles(&sp54, &sp48, ptr->unk_4C, ptr->unk_44, ptr->unk_46);
    Vec3f_CalculateDistanceAngles(&sp3C, &sp48, &sp38, &sp32, &sp30);

    var_fa0 = (sp38 / (BattleScene_GetParticipantModelRadius(arg1) * 80.0f)) * 3.0f;
    if (var_fa0 >= 1.0f) {
        var_fa0 = 1.0f;
    }

    Camera_ComputeEyeFromAngles(&sp3C, &arg0->unk_60.at, sp38 * var_fa0, sp32, sp30);
}

s32 BattleScene_FrameCamera(CameraStruct* arg0, BattlePlayerEntity* arg1) {
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
    PokemonAudioInfo* temp_v1;

    temp_v1 = &sActivePokemon[BattleScene_GetParticipantSideIndex(arg1) == 0]->animationState.unk_38;

    if (arg1->animationState.unk_34 & 0x4000) {
        return 1;
    }

    if (temp_v1->unk_5A == 0x53) {
        BattleScene_SelectCameraShot(arg1, arg0, 4);
        return 1;
    }

    BattleAnim_Vec3fCopy(&sp6C, &arg0->unk_60.at);
    BattleAnim_Vec3fCopy(&sp60, &arg0->unk_60.eye);

    if ((arg1->unk_000.unk_01A != 0x5F) && (arg1->animationMode != 0xD)) {
        BattleScene_UpdateCameraTargetFromOwner(arg0, arg1);
    }

    BattleAnim_GetOwnerDefaultAnchorPosition(arg1, &sp84);
    gCameraDistTarget = BattleScene_ScaleCameraDistance(arg1, 3.5f, 300.0f);
    BattleScene_SetCameraEyeFromPosition(arg0, sp84, 0, BattleScene_GetParticipantFacingAngle(arg1), gCameraDistTarget, 0.0f);

    if (arg0->unk_60.eye.y <= 13.0f) {
        arg0->unk_60.eye.y = 13.0f;
    }

    BattleAnim_CalculateDistanceAngles(&sp84, &arg0->unk_60.eye, &gCameraDistCurrent, &sp4C, &sp50);
    BattleAnim_CalculateDistanceAngles(&sp84, &sp60, &gCameraDistTarget, &sp4E, &sp52);
    BattleAnim_ApproachF(&gCameraDistTarget, gCameraDistCurrent, 0.2f);
    BattleAnim_ApproachF(&gBattleScene.posX->unk_94.z, 0.2f, 0.03f);
    BattleAnim_StepToS16VariableRate(&sp52, sp50, gBattleScene.posX->unk_94.z);
    BattleAnim_StepToS16VariableRate(&sp4E, sp4C, gBattleScene.posX->unk_94.z);
    BattleScene_SetCameraEyeFromPosition(arg0, sp84, sp4E, sp52, gCameraDistTarget, 0.0f);

    if ((sp4C == sp4E) && (sp50 == sp52)) {
        return 1;
    }
    return 0;
}

void BattleScene_ApproachCameraTargetFromOwner(CameraStruct* arg0, BattlePlayerEntity* arg1) {
    unk_D_84390010_448* ptr = &arg1->unk_448;
    Vec3f sp58;
    Vec3f sp4C;
    UNUSED s32 pad[3];
    Vec3f sp34;
    f32 sp30;
    UNUSED s32 pad2[1];
    s16 sp2A;
    s16 sp28;

    BattleAnim_Vec3fCopy(&sp34, &arg0->unk_60.at);
    BattleScene_GetOwnerCameraAnchor(arg1, &sp58);
    Camera_ComputeEyeFromAngles(&sp58, &sp4C, ptr->unk_4C, ptr->unk_44, ptr->unk_46);
    Vec3f_CalculateDistanceAngles(&sp34, &sp4C, &sp30, &sp2A, &sp28);
    gBattleScene.posX->unk_94.z = Math_StepToF(gBattleScene.posX->unk_94.z, 0.8f, 0.05f, 0.05f);
    Camera_ComputeEyeFromAngles(&sp34, &arg0->unk_60.at, gBattleScene.posX->unk_94.z * sp30, sp2A, sp28);
}

void BattleScene_UpdateCameraVerticalFraming(CameraStruct* arg0, BattlePlayerEntity* arg1) {
    unk_D_84390010_448* ptr = &arg1->unk_448;
    Vec3f sp60;
    Vec3f sp54;
    UNUSED s32 pad[3];
    Vec3f sp3C;
    UNUSED s32 pad2[3];

    BattleAnim_Vec3fCopy(&sp3C, &arg0->unk_60.at);
    BattleScene_GetOwnerCameraAnchor(arg1, &sp60);
    Camera_ComputeEyeFromAngles(&sp60, &sp54, ptr->unk_4C, ptr->unk_44, ptr->unk_46);
    BattleAnim_ApproachF(&arg0->unk_60.at.y, sp54.y, 0.1f);
    if (arg0->unk_60.at.y < -10.0f) {
        arg0->unk_60.at.y = -10.0f;
    }
    BattleAnim_ApproachF(&arg0->unk_60.eye.y, BattleAnim_GetOwnerModelHeight(arg1) * 4.0f, 0.04f);
}

void BattleScene_RecenterCameraOnOwner(CameraStruct* arg0, BattlePlayerEntity* arg1) {
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

    BattleAnim_Vec3fCopy(&sp68, &arg0->unk_60.at);
    BattleAnim_Vec3fCopy(&sp5C, &arg0->unk_60.eye);
    BattleAnim_GetOwnerDefaultAnchorPosition(arg1, &sp74);
    gCameraDistTarget = BattleScene_ScaleCameraDistance(arg1, 3.5f, 300.0f);
    BattleScene_SetCameraAtFromAnchor(arg1, arg0, sp74, 0, BattleScene_GetParticipantFacingAngle(arg1), 0.0f, 0.0f);
    BattleScene_SetCameraEyeFromPosition(arg0, sp74, 0, BattleScene_GetParticipantFacingAngle(arg1), gCameraDistTarget, 0.0f);
    BattleAnim_CalculateDistanceAngles(&arg0->unk_60.at, &arg0->unk_60.eye, &gCameraDistCurrent, &sp4C, &sp50);
    BattleAnim_CalculateDistanceAngles(&sp68, &sp5C, &gCameraDistTarget, &sp4E, &sp52);
    BattleAnim_ApproachF(&gCameraDistTarget, gCameraDistCurrent, 0.05f);
    BattleAnim_StepToS16(&sp52, sp50, 0x108);
    BattleAnim_StepToS16(&sp4E, sp4C, 0xB6);
    BattleAnim_CalculateDistanceAngles(&sp68, &arg0->unk_60.at, &sp58, &sp56, &sp54);
    Camera_ComputeEyeFromAngles(&sp68, &arg0->unk_60.at, sp58 / 8, sp56, sp54);
    BattleScene_SetCameraEyeFromAt(arg0, sp4E, sp52, gCameraDistTarget, 0.0f);
}

void BattleScene_ApproachCameraTarget(CameraStruct* arg0, BattlePlayerEntity* arg1, UNUSED s32 arg2) {
    unk_D_84390010_448* ptr = &arg1->unk_448;
    Vec3f sp50;
    Vec3f sp44;
    Vec3f sp38;
    f32 sp34;
    s16 sp32;
    s16 sp30;
    UNUSED s32 pad;

    BattleScene_GetOwnerCameraAnchor(arg1, &sp50);
    BattleAnim_Vec3fCopy(&sp38, &arg0->unk_60.at);
    Camera_ComputeEyeFromAngles(&sp50, &sp44, ptr->unk_4C, ptr->unk_44, ptr->unk_46);
    BattleAnim_CalculateDistanceAngles(&sp38, &sp44, &sp34, &sp32, &sp30);
    Camera_ComputeEyeFromAngles(&sp38, &arg0->unk_60.at, sp34 * 0.1f, sp32, sp30);
}

void BattleScene_ApproachCameraZoom(CameraStruct* arg0, BattlePlayerEntity* arg1) {
    s16 sp26;
    s16 sp24;

    gCameraDistTarget = BattleScene_ScaleCameraDistance(arg1, 8.0f, 500.0f);
    BattleAnim_CalculateDistanceAngles(&arg0->unk_60.at, &arg0->unk_60.eye, &gCameraDistCurrent, &sp26, &sp24);
    BattleAnim_ApproachF(&gCameraDistCurrent, gCameraDistTarget, 0.03f);
    BattleAnim_StepToS16(&sp26, 0xE38, 0x5B);
    BattleScene_SetCameraEyeFromAt(arg0, sp26, sp24, gCameraDistCurrent, 0.0f);
}

s32 BattleScene_ApproachCloseCameraShot(CameraStruct* arg0, BattlePlayerEntity* arg1) {
    Vec3f sp3C;
    Vec3f sp30;
    f32 sp2C;
    s16 sp2A;
    s16 sp28;

    BattleAnim_Vec3fCopy(&sp3C, &arg0->unk_60.at);
    BattleAnim_Vec3fCopy(&sp30, &arg0->unk_60.eye);
    BattleScene_CameraShotTargetClose(arg0, arg1);
    Vec3f_CalculateDistanceAngles(&sp30, &arg0->unk_60.eye, &sp2C, &sp28, &sp2A);
    Camera_ComputeEyeFromAngles(&sp30, &arg0->unk_60.eye, sp2C / 2, sp28, sp2A);
    BattleAnim_Vec3fCopy(&arg0->unk_60.at, &sp3C);

    if (sp2C <= 0.5f) {
        return 1;
    }
    return 0;
}

s32 BattleScene_AnimateCameraPreset(CameraStruct* arg0, BattlePlayerEntity* arg1, s32 arg2, s32 arg3) {
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
        BattleAnim_ApproachF(&arg0->unk_24.fovy, 30.0f, 0.06f);
    } else {
        arg0->unk_24.fovy = 30.0f;
    }

    BattleAnim_ApproachF(&gBattleScene.posX->unk_94.z, gCameraPreset.unk_34, gCameraPreset.unk_38);
    Camera_ComputeEyeFromAngles(&gCameraPreset.posX, &sp54, gCameraPreset.unk_30, gCameraPreset.unk_26, gCameraPreset.unk_28);
    BattleAnim_Vec3fCopy(&sp48, &arg0->unk_60.eye);
    BattleAnim_CalculateDistanceAngles(&sp48, &sp54, &sp38, &sp32, &sp30);
    Camera_ComputeEyeFromAngles(&sp48, &arg0->unk_60.eye, gBattleScene.posX->unk_94.z * sp38, sp32, sp30);
    Camera_ComputeEyeFromAngles(&gCameraPreset.posX, &sp3C, gCameraPreset.unk_2C, gCameraPreset.unk_20, gCameraPreset.unk_22);

    if (arg2 == 1) {
        sp3C.y += BattleScene_GetParticipantEyeHeight(arg1);
    }

    BattleAnim_Vec3fCopy(&sp60, &arg0->unk_60.at);
    BattleAnim_CalculateDistanceAngles(&sp60, &sp3C, &sp34, &sp32, &sp30);
    Camera_ComputeEyeFromAngles(&sp60, &arg0->unk_60.at, gBattleScene.posX->unk_94.z * sp34, sp32, sp30);

    if ((sp38 <= 1.75f) && (sp34 <= 1.75f)) {
        return 1;
    }
    return 0;
}

s32 BattleScene_AnimateCameraPresetToOwner(CameraStruct* arg0, BattlePlayerEntity* arg1) {
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

    BattleAnim_ApproachF(&gBattleScene.posX->unk_94.z, gCameraPreset.unk_34, gCameraPreset.unk_38);
    BattleScene_GetOwnerCameraAnchor(arg1, &sp6C);
    Vec3f_CalculateDistanceAngles(&gCameraPreset.posX, &sp6C, &sp44, &sp36, &sp34);

    var_fa1 = sp44 / (BattleScene_GetParticipantModelRadius(arg1) * 40.0f);
    if (var_fa1 >= 0.6f) {
        var_fa1 = 1.0f;
    }

    sp44 *= var_fa1;
    sp44 += gCameraPreset.unk_30;

    Camera_ComputeEyeFromAngles(&gCameraPreset.posX, &sp60, sp44, gCameraPreset.unk_26, gCameraPreset.unk_28);
    BattleAnim_Vec3fCopy(&sp54, &arg0->unk_60.eye);
    BattleAnim_CalculateDistanceAngles(&sp54, &sp60, &sp40, &sp36, &sp34);
    Camera_ComputeEyeFromAngles(&sp54, &arg0->unk_60.eye, gBattleScene.posX->unk_94.z * sp40, sp36, sp34);
    BattleScene_GetOwnerCameraAnchor(arg1, &sp6C);
    Vec3f_CalculateDistanceAngles(&gCameraPreset.posX, &sp6C, &sp44, &sp36, &sp34);

    var_fa1 = sp44 / (BattleScene_GetParticipantModelRadius(arg1) * 40.0f);
    if (var_fa1 >= 0.6f) {
        var_fa1 = 1;
    }
    sp44 *= var_fa1;
    sp44 += gCameraPreset.unk_2C;

    Camera_ComputeEyeFromAngles(&gCameraPreset.posX, &sp48, sp44, gCameraPreset.unk_20, gCameraPreset.unk_22);
    sp48.y += BattleScene_GetParticipantEyeHeight(arg1);
    BattleAnim_Vec3fCopy(&sp6C, &arg0->unk_60.at);
    BattleAnim_CalculateDistanceAngles(&sp6C, &sp48, &sp3C, &sp36, &sp34);
    Camera_ComputeEyeFromAngles(&sp6C, &arg0->unk_60.at, gBattleScene.posX->unk_94.z * sp3C, sp36, sp34);

    if ((sp40 <= 1.0f) && (sp3C <= 1.0f)) {
        return 1;
    }
    return 0;
}

void BattleScene_CameraPresetNop(UNUSED CameraStruct* arg0) {
    if (arg0) {}
}

void BattleScene_ApplyCameraPreset(CameraStruct* arg0, BattlePlayerEntity* arg1, s32 arg2) {
    BattleScene_SetCameraAtFromPosition(arg0, gCameraPreset.posX, gCameraPreset.unk_0C, gCameraPreset.unk_0E, gCameraPreset.unk_18, 0.0f);
    if (arg2 == 1) {
        arg0->unk_60.at.y += BattleScene_GetParticipantEyeHeight(arg1);
        BattleScene_SetCameraEyeFromPosition(arg0, arg0->unk_60.at, gCameraPreset.unk_12, gCameraPreset.unk_14, gCameraPreset.unk_1C, 0.0f);
    } else {
        BattleScene_SetCameraEyeFromPosition(arg0, gCameraPreset.posX, gCameraPreset.unk_12, gCameraPreset.unk_14, gCameraPreset.unk_1C, 0.0f);
    }
}

void BattleScene_SetCameraPresetAtAngles(s16 arg0, s16 arg1, s16 arg2, s16 arg3) {
    gCameraPreset.unk_0C = arg0;
    gCameraPreset.unk_0E = arg1;
    gCameraPreset.unk_20 = arg2;
    gCameraPreset.unk_22 = arg3;
}

void BattleScene_SetCameraPresetAtDistances(f32 arg0, f32 arg1) {
    gCameraPreset.unk_18 = arg0;
    gCameraPreset.unk_2C = arg1;
}

void BattleScene_SetCameraPresetEyeAngles(s16 arg0, s16 arg1, s16 arg2, s16 arg3) {
    gCameraPreset.unk_12 = arg0;
    gCameraPreset.unk_14 = arg1;
    gCameraPreset.unk_26 = arg2;
    gCameraPreset.unk_28 = arg3;
}

void BattleScene_SetCameraPresetEyeDistances(f32 arg0, f32 arg1) {
    gCameraPreset.unk_1C = arg0;
    gCameraPreset.unk_30 = arg1;
}

void BattleScene_SetCameraPresetSmoothing(f32 arg0, f32 arg1) {
    gCameraPreset.unk_34 = arg0;
    gCameraPreset.unk_38 = arg1;
}

void BattleScene_LoadCameraPreset(DioramaAnimData* arg0, CameraStruct* arg1, BattlePlayerEntity* arg2) {
    f32 sp34;
    f32 sp30;
    f32 sp2C;
    f32 sp28;
    f32 temp_fv1;
    UNUSED s16 pad;
    s16 sp20;

    BattleScene_ClearCameraOffsetVectors();
    if (arg0->unk_30 != 200.0f) {
        temp_fv1 = arg0->unk_30;
        gCameraPreset.unk_3C = temp_fv1;
        arg1->unk_24.fovy = temp_fv1;
    } else {
        gCameraPreset.unk_3C = arg0->unk_30;
    }

    sp34 = BattleScene_ScaleCameraDistance(arg2, arg0->unk_0C, 500.0f);
    sp30 = BattleScene_ScaleCameraDistance(arg2, arg0->unk_20, 500.0f);
    sp2C = BattleScene_ScaleCameraDistance(arg2, arg0->unk_10, 500.0f);
    sp28 = BattleScene_ScaleCameraDistance(arg2, arg0->unk_24, 500.0f);
    sp20 = BattleScene_GetParticipantFacingAngle(arg2);

    BattleScene_SetCameraPresetAtAngles(arg0->posX, sp20 - (arg0->posY * arg2->sideSign), arg0->unk_14,
                  BattleScene_GetParticipantFacingAngle(arg2) - (arg0->unk_16 * arg2->sideSign));
    BattleScene_SetCameraPresetAtDistances(sp34, sp30);
    sp20 = BattleScene_GetParticipantFacingAngle(arg2);
    BattleScene_SetCameraPresetEyeAngles(arg0->unk_06, sp20 - (arg0->unk_08 * arg2->sideSign), arg0->unk_1A,
                  BattleScene_GetParticipantFacingAngle(arg2) - (arg0->unk_1C * arg2->sideSign));
    BattleScene_SetCameraPresetEyeDistances(sp2C, sp28);
    BattleScene_SetCameraPresetSmoothing(arg0->unk_28, arg0->unk_2C);
}

void BattleScene_LoadCameraPresetUnscaled(DioramaAnimData* arg0, CameraStruct* arg1) {
    f32 sp2C;
    f32 sp28;
    f32 sp24;
    f32 sp20;
    f32 tmp;

    BattleScene_ClearCameraOffsetVectors();

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

    BattleScene_SetCameraPresetAtAngles(arg0->posX, arg0->posY, arg0->unk_14, arg0->unk_16);
    BattleScene_SetCameraPresetAtDistances(sp2C, sp28);
    BattleScene_SetCameraPresetEyeAngles(arg0->unk_06, arg0->unk_08, arg0->unk_1A, arg0->unk_1C);
    BattleScene_SetCameraPresetEyeDistances(sp24, sp20);
    BattleScene_SetCameraPresetSmoothing(arg0->unk_28, arg0->unk_2C);
}

s32 BattleScene_AnimateCameraIntro(CameraStruct* arg0, BattlePlayerEntity* arg1) {
    Vec3f sp64;
    Vec3f sp58;
    Vec3f sp4C;
    Vec3f sp40;
    Vec3f sp34;
    f32 sp30;
    UNUSED s32 pad;
    s16 sp2A;
    s16 sp28;

    BattleAnim_ApproachF(&arg0->unk_24.fovy, 30.0f, 0.06f);
    Vec3f_SetComponentsDuplicate(&sp64, arg1->sideSign * -150.0f, 5.0f, 0.0f);
    BattleAnim_ApproachF(&gBattleScene.posX->unk_94.z, 0.2f, 0.06f);
    Camera_ComputeEyeFromAngles(&sp64, &sp4C, 100.0f, 0, BattleScene_GetParticipantFacingAngle(arg1));
    BattleAnim_Vec3fCopy(&sp40, &arg0->unk_60.eye);
    BattleAnim_CalculateDistanceAngles(&sp40, &sp4C, &sp30, &sp2A, &sp28);
    Camera_ComputeEyeFromAngles(&sp40, &arg0->unk_60.eye, gBattleScene.posX->unk_94.z * sp30, sp2A, sp28);
    Camera_ComputeEyeFromAngles(&sp64, &sp34, 0.0f, 0, BattleScene_GetParticipantFacingAngle(arg1));
    BattleAnim_Vec3fCopy(&sp58, &arg0->unk_60.at);
    BattleAnim_CalculateDistanceAngles(&sp58, &sp34, &sp30, &sp2A, &sp28);

    if (sp30 >= 1.0f) {
        Camera_ComputeEyeFromAngles(&sp58, &arg0->unk_60.at, gBattleScene.posX->unk_94.z * sp30, sp2A, sp28);
        return 0;
    }
    return 1;
}

s32 BattleScene_AreActivePokemonHeightsSeparated(UNUSED CameraStruct* arg0) {
    Vec3f sp2C;
    Vec3f sp20;
    f32 var_fv0;

    BattleAnim_GetOwnerDefaultAnchorPosition(sActivePokemon[0], &sp2C);
    BattleAnim_GetOwnerDefaultAnchorPosition(sActivePokemon[1], &sp20);

    var_fv0 = sp2C.y - sp20.y;
    if (sp2C.y < sp20.y) {
        var_fv0 *= -1.0f;
    }

    if (var_fv0 > 35.0f) {
        return 1;
    }
    return 0;
}

void BattleScene_SetCameraActivePokemonHeightShot(CameraStruct* arg0, s32 arg1) {
    UNUSED s32 pad;
    Vec3f sp60;
    Vec3f sp54;
    Vec3f sp48;
    BattlePlayerEntity* sp40;

    BattleScene_ClearCameraOffsetVectors();
    arg0->unk_24.fovy = 30.0f;

    sp40 = sActivePokemon[arg1];
    BattleAnim_GetOwnerDefaultAnchorPosition(sp40, &sp60);
    BattleScene_SetCameraEyeFromPosition(arg0, sp60, 0, sp40->sideSign << 0xE, 100.0f, 0.0f);
    BattleAnim_GetOwnerDefaultAnchorPosition(sActivePokemon[arg1], &sp54);

    BattleAnim_GetOwnerDefaultAnchorPosition(sActivePokemon[arg1 == 0], &sp48);
    sp40 = sActivePokemon[arg1 == 0];
    BattleAnim_GetOwnerDefaultAnchorPosition(sp40, &sp60);

    if (sp48.y < sp54.y) {
        sp60.y = sp54.y * 1.8f;
        BattleScene_SetCameraAtFromAnchor(sp40, arg0, sp60, 0, 0, 0, 0);
    } else {
        sp60.y = 0.0f;
        BattleScene_SetCameraAtFromAnchor(sp40, arg0, sp60, 0, 0, 0, 0);
    }
}

s32 BattleScene_ApproachCameraActivePokemonHeightShot(CameraStruct* arg0, s32 arg1) {
    UNUSED s32 pad;
    Vec3f sp58;
    Vec3f sp4C;
    Vec3f sp40;
    Vec3f sp34;
    f32 sp30;
    s16 sp2E;
    s16 sp2C;

    BattleAnim_ApproachF(&gBattleScene.posX->unk_94.z, 0.1f, 0.05f);
    BattleAnim_GetOwnerDefaultAnchorPosition(sActivePokemon[arg1], &sp40);
    BattleAnim_GetOwnerDefaultAnchorPosition(sActivePokemon[!arg1], &sp34);

    if (sp34.y < sp40.y) {
        BattleAnim_GetOwnerDefaultAnchorPosition(sActivePokemon[!arg1], &sp4C);
    } else {
        BattleAnim_GetOwnerDefaultAnchorPosition(sActivePokemon[!arg1], &sp4C);
        sp4C.y *= 1.3f;
    }

    BattleAnim_Vec3fCopy(&sp58, &arg0->unk_60.at);
    BattleAnim_CalculateDistanceAngles(&sp58, &sp4C, &sp30, &sp2E, &sp2C);
    Camera_ComputeEyeFromAngles(&sp58, &arg0->unk_60.at, gBattleScene.posX->unk_94.z * sp30, sp2E, sp2C);

    if (sp30 <= 1.0f) {
        return 1;
    }
    return 0;
}

void BattleScene_SetCameraOwnerShot(CameraStruct* arg0, BattlePlayerEntity* arg1) {
    BattleAnim_GetOwnerDefaultAnchorPosition(arg1, &gBattleScene.posX->unk_D0);

    gBattleScene.posX->unk_D0.x = BattleScene_GetParticipantModelXOffset(arg1);
    gBattleScene.posX->unk_D0.z = 0.0f;

    if (arg1->animationState.unk_38.unk_44.posX == 0x6E) {
        gCameraDistTarget = BattleScene_ScaleCameraDistance(arg1, 4.5f, 300.0f);
        if (gCameraDistTarget <= 100.0f) {
            gCameraDistTarget = 100.0f;
        }

        if (gBattleScene.posX->unk_D0.y < 20.0f) {
            gBattleScene.posX->unk_D0.y = 20.0f;
        }
    } else {
        gCameraDistTarget = BattleScene_ScaleCameraDistance(arg1, 3.5f, 300.0f);
    }

    BattleScene_SetCameraAtFromAnchor(arg1, arg0, gBattleScene.posX->unk_D0, 0, BattleScene_GetParticipantFacingAngle(arg1), 0.0f, 0.0f);
    BattleScene_SetCameraEyeFromPosition(arg0, gBattleScene.posX->unk_D0, 0, BattleScene_GetParticipantFacingAngle(arg1), gCameraDistTarget, 0.0f);
}

void BattleScene_SetCameraOwnerWideShot(CameraStruct* arg0, BattlePlayerEntity* arg1) {
    f32 sp3C;

    BattleAnim_GetOwnerDefaultAnchorPosition(arg1, &gBattleScene.posX->unk_D0);
    sp3C = BattleScene_ScaleCameraDistance(arg1, 8.0f, 300.0f);
    BattleScene_SetCameraAtFromAnchor(arg1, arg0, gBattleScene.posX->unk_D0, 0, BattleScene_GetParticipantFacingAngle(arg1), 0.0f, 0.0f);
    BattleScene_SetCameraEyeFromAt(arg0, 0, arg1->sideSign << 0xE, sp3C, 0.0f);
}

void BattleScene_SetCameraPresetClose(CameraStruct* arg0, BattlePlayerEntity* arg1, s32 arg2) {
    BattleAnim_GetOwnerDefaultAnchorPosition(arg1, &gBattleScene.posX->unk_D0);
    gCameraDistTarget = BattleScene_ScaleCameraDistance(arg1, 0.5f, 100.0f);
    gCameraDistCurrent = BattleScene_ScaleCameraDistance(arg1, 5.0f, 300.0f);
    BattleScene_SetCameraAtFromAnchor(arg1, arg0, gBattleScene.posX->unk_D0, 0, BattleScene_GetParticipantFacingAngle(arg1), gCameraDistTarget, 0.0f);
    BattleScene_SetCameraEyeFromPosition(arg0, gBattleScene.posX->unk_D0, 0, BattleScene_GetParticipantFacingAngle(arg1) - (arg1->sideSign * 0x31C7), gCameraDistCurrent, 0.0f);

    if (arg2 == 1) {
        BattleScene_UpdateCameraModelOffset(arg1, arg0);
    } else {
        BattleScene_ReframeAndRecomputeDistance(arg0, arg1);
        BattleScene_ReframeAndRecomputeDistance(arg0, arg1);
    }

    BattleScene_ReframeAndRecomputeDistance(arg0, arg1);
}

void BattleScene_SetCameraPresetAngledClose(CameraStruct* arg0, BattlePlayerEntity* arg1, s32 arg2) {
    BattleAnim_GetOwnerDefaultAnchorPosition(arg1, &gBattleScene.posX->unk_D0);
    gCameraDistTarget = BattleScene_ScaleCameraDistance(arg1, 0.5f, 100.0f);
    gCameraDistCurrent = BattleScene_ScaleCameraDistance(arg1, 5.0f, 300.0f);
    BattleScene_SetCameraAtFromAnchor(arg1, arg0, gBattleScene.posX->unk_D0, 0, BattleScene_GetParticipantFacingAngle(arg1), gCameraDistTarget, 0.0f);
    BattleScene_SetCameraEyeFromPosition(arg0, gBattleScene.posX->unk_D0, 0x71C, BattleScene_GetParticipantFacingAngle(arg1) - (arg1->sideSign * 0x1555), gCameraDistCurrent,
                  0.0f);
    if (arg2 == 1) {
        BattleScene_UpdateCameraModelOffset(arg1, arg0);
    } else {
        BattleScene_ReframeAndRecomputeDistance(arg0, arg1);
        BattleScene_ReframeAndRecomputeDistance(arg0, arg1);
    }
    BattleScene_ReframeAndRecomputeDistance(arg0, arg1);
}

void BattleScene_SetCameraPresetOffsetClose(CameraStruct* arg0, BattlePlayerEntity* arg1, s32 arg2) {
    BattleAnim_GetOwnerDefaultAnchorPosition(arg1, &gBattleScene.posX->unk_D0);
    gCameraDistTarget = BattleScene_ScaleCameraDistance(arg1, 0.5f, 100.0f);
    gCameraDistCurrent = BattleScene_ScaleCameraDistance(arg1, 5.0f, 300.0f);
    BattleScene_SetCameraAtFromAnchor(arg1, arg0, gBattleScene.posX->unk_D0, 0, BattleScene_GetParticipantFacingAngle(arg1), gCameraDistTarget, 0.0f);
    BattleScene_SetCameraEyeFromPosition(arg0, gBattleScene.posX->unk_D0, 0xE38, BattleScene_GetParticipantFacingAngle(arg1), gCameraDistCurrent, 0.0f);
    if (arg2 == 1) {
        BattleScene_UpdateCameraModelOffset(arg1, arg0);
    } else {
        BattleScene_ReframeAndRecomputeDistance(arg0, arg1);
        BattleScene_ReframeAndRecomputeDistance(arg0, arg1);
    }
    BattleScene_ReframeAndRecomputeDistance(arg0, arg1);
}

void BattleScene_SetCameraPresetLowClose(CameraStruct* arg0, BattlePlayerEntity* arg1, s32 arg2) {
    UNUSED s32 pad[4];
    s16 sp3E;

    BattleAnim_GetOwnerDefaultAnchorPosition(arg1, &gBattleScene.posX->unk_D0);
    gCameraDistTarget = BattleScene_ScaleCameraDistance(arg1, 0.5f, 100.0f);
    gCameraDistCurrent = BattleScene_ScaleCameraDistance(arg1, 5.0f, 300.0f);
    BattleScene_SetCameraAtFromAnchor(arg1, arg0, gBattleScene.posX->unk_D0, 0, BattleScene_GetParticipantFacingAngle(arg1), gCameraDistTarget, 0.0f);
    sp3E = BattleScene_GetParticipantFacingAngle(arg1);
    BattleScene_SetCameraEyeFromPosition(arg0, gBattleScene.posX->unk_D0, 0, sp3E - (arg1->sideSign * 0x1555), gCameraDistCurrent,
                  -BattleAnim_GetOwnerModelHeight(arg1) * 0.8);
    if (arg2 == 1) {
        BattleScene_UpdateCameraModelOffset(arg1, arg0);
    } else {
        BattleScene_ReframeAndRecomputeDistance(arg0, arg1);
        BattleScene_ReframeAndRecomputeDistance(arg0, arg1);
    }
    BattleScene_ReframeAndRecomputeDistance(arg0, arg1);
}

void BattleScene_SetCameraPresetWide(CameraStruct* arg0, BattlePlayerEntity* arg1, s32 arg2) {
    BattleAnim_GetOwnerDefaultAnchorPosition(arg1, &gBattleScene.posX->unk_D0);
    gCameraDistTarget = BattleScene_ScaleCameraDistance(arg1, 3.5f, 300.0f);
    BattleScene_SetCameraAtFromAnchor(arg1, arg0, gBattleScene.posX->unk_D0, 0, BattleScene_GetParticipantFacingAngle(arg1), 0.0f, 0.0f);
    BattleScene_SetCameraEyeFromPosition(arg0, gBattleScene.posX->unk_D0, 0, BattleScene_GetParticipantFacingAngle(arg1), gCameraDistTarget, 0.0f);
    if (arg2 == 1) {
        BattleScene_UpdateCameraModelOffset(arg1, arg0);
    } else {
        BattleScene_ReframeAndRecomputeDistance(arg0, arg1);
        BattleScene_ReframeAndRecomputeDistance(arg0, arg1);
    }
    BattleScene_ReframeAndRecomputeDistance(arg0, arg1);
}

void BattleScene_SetCameraPresetWideStatic(CameraStruct* arg0, BattlePlayerEntity* arg1, s32 arg2) {
    BattleAnim_GetOwnerDefaultAnchorPosition(arg1, &gBattleScene.posX->unk_D0);
    gCameraDistTarget = BattleScene_ScaleCameraDistance(arg1, 3.5f, 300.0f);
    BattleScene_SetCameraAtFromAnchor(arg1, arg0, gBattleScene.posX->unk_D0, 0, BattleScene_GetParticipantFacingAngle(arg1), 0.0f, 0.0f);
    BattleScene_SetCameraEyeFromPosition(arg0, gBattleScene.posX->unk_D0, 0, BattleScene_GetParticipantFacingAngle(arg1), gCameraDistTarget, 0.0f);
    if (arg2 == 1) {
        BattleScene_UpdateCameraModelOffset(arg1, arg0);
    }
}

void BattleScene_SetCameraPresetFromTable(CameraStruct* arg0, BattlePlayerEntity* arg1, s32 arg2, s32 arg3) {
    BattleAnim_GetOwnerDefaultAnchorPosition(arg1, &gCameraPreset.posX);
    BattleScene_LoadCameraPreset(&gBattleCameraPresetTable[arg2], arg0, arg1);
    BattleScene_ApplyCameraPreset(arg0, arg1, 1);
    BattleScene_CameraPresetNop(arg0);
    if (arg3 == 1) {
        BattleScene_UpdateCameraModelOffset(arg1, arg0);
    }
}

void BattleScene_CameraShotTargetStandard(CameraStruct* arg0, BattlePlayerEntity* arg1) {
    BattleScene_ClearCameraOffsetVectors();
    BattleAnim_GetOwnerDefaultAnchorPosition(arg1, &gBattleScene.posX->unk_D0);
    gCameraDistTarget = BattleScene_ScaleCameraDistance(arg1, 5.0f, 400.0f);
    BattleScene_SetCameraAtFromAnchor(arg1, arg0, gBattleScene.posX->unk_D0, 0, arg1->sideSign << 0xE, 0.0f, 0.0f);
    BattleScene_SetCameraEyeFromPosition(arg0, gBattleScene.posX->unk_D0, 0, arg1->sideSign * 0xE38, gCameraDistTarget, 0.0f);
    BattleScene_UpdateCameraModelOffset(arg1, arg0);
}

void BattleScene_CameraShotTargetAngled(CameraStruct* arg0, BattlePlayerEntity* arg1) {
    BattleScene_ClearCameraOffsetVectors();
    BattleAnim_GetOwnerDefaultAnchorPosition(arg1, &gBattleScene.posX->unk_D0);
    gCameraDistTarget = BattleScene_ScaleCameraDistance(arg1, 5.0f, 400.0f);
    BattleScene_SetCameraAtFromAnchor(arg1, arg0, gBattleScene.posX->unk_D0, 0, arg1->sideSign << 0xE, 0.0f, 0.0f);
    BattleScene_SetCameraEyeFromPosition(arg0, gBattleScene.posX->unk_D0, 0x1555, arg1->sideSign * 0xE38, gCameraDistTarget, 0.0f);
    BattleScene_UpdateCameraModelOffset(arg1, arg0);
}

void BattleScene_CameraShotTargetHigh(CameraStruct* arg0, BattlePlayerEntity* arg1) {
    BattleAnim_GetOwnerDefaultAnchorPosition(arg1, &gBattleScene.posX->unk_D0);
    gCameraDistTarget = BattleScene_ScaleCameraDistance(arg1, 5.0f, 400.0f);
    BattleScene_SetCameraAtFromAnchor(arg1, arg0, gBattleScene.posX->unk_D0, 0, arg1->sideSign << 0xE, 0.0f, 0.0f);
    BattleScene_SetCameraEyeFromPosition(arg0, gBattleScene.posX->unk_D0, 0, arg1->sideSign * 0xE38, gCameraDistTarget, 2.0f * BattleAnim_GetOwnerModelHeight(arg1));
    BattleScene_UpdateCameraModelOffset(arg1, arg0);
}

void BattleScene_CameraShotTargetLow(CameraStruct* arg0, BattlePlayerEntity* arg1) {
    BattleAnim_GetOwnerDefaultAnchorPosition(arg1, &gBattleScene.posX->unk_D0);
    gCameraDistTarget = BattleScene_ScaleCameraDistance(arg1, 5.0f, 400.0f);
    BattleScene_SetCameraAtFromAnchor(arg1, arg0, gBattleScene.posX->unk_D0, 0, arg1->sideSign << 0xE, 0.0f, 0.0f);
    BattleScene_SetCameraEyeFromPosition(arg0, gBattleScene.posX->unk_D0, 0, arg1->sideSign * 0xE38, gCameraDistTarget, -BattleAnim_GetOwnerModelHeight(arg1) * 0.8f);
    if (arg0->unk_60.eye.y <= 15.0f) {
        arg0->unk_60.eye.y = 15.0f;
    }
    BattleScene_UpdateCameraModelOffset(arg1, arg0);
}

void BattleScene_CameraShotTargetClose(CameraStruct* arg0, BattlePlayerEntity* arg1) {
    BattleAnim_GetOwnerDefaultAnchorPosition(arg1, &gBattleScene.posX->unk_D0);
    gCameraDistTarget = BattleScene_ScaleCameraDistance(arg1, 3.5f, 300.0f);
    BattleScene_SetCameraAtFromAnchor(arg1, arg0, gBattleScene.posX->unk_D0, 0, BattleScene_GetParticipantFacingAngle(arg1), 0.0f, 0.0f);
    BattleScene_SetCameraEyeFromPosition(arg0, gBattleScene.posX->unk_D0, 0, BattleScene_GetParticipantFacingAngle(arg1), gCameraDistTarget, 0.0f);
    BattleScene_UpdateCameraModelOffset(arg1, arg0);
}

void BattleScene_SetCameraFollowPresetNear(CameraStruct* arg0, BattlePlayerEntity* arg1, s32 arg2) {
    BattleAnim_GetOwnerDefaultAnchorPosition(arg1, &gBattleScene.posX->unk_D0);
    gCameraDistTarget = BattleScene_ScaleCameraDistance(arg1, 3.5f, 300.0f);
    gCameraDistCurrent = BattleScene_ScaleCameraDistance(arg1, 0.5f, 100.0f);
    BattleScene_SetCameraAtFromAnchor(arg1, arg0, gBattleScene.posX->unk_D0, 0, BattleScene_GetParticipantFacingAngle(arg1), gCameraDistCurrent, 0.0f);
    BattleScene_SetCameraEyeFromPosition(arg0, gBattleScene.posX->unk_D0, 0, BattleScene_GetParticipantFacingAngle(arg1) - (arg1->sideSign * 0x1555), gCameraDistTarget, 0.0f);
    if (arg2 == 1) {
        BattleScene_UpdateCameraModelOffset(arg1, arg0);
    }
}

void BattleScene_SetCameraOwnerStandardShot(CameraStruct* arg0, BattlePlayerEntity* arg1) {
    BattleAnim_GetOwnerDefaultAnchorPosition(arg1, &gBattleScene.posX->unk_D0);
    gCameraDistTarget = BattleScene_ScaleCameraDistance(arg1, 3.5f, 300.0f);
    BattleScene_SetCameraAtFromAnchor(arg1, arg0, gBattleScene.posX->unk_D0, 0, BattleScene_GetParticipantFacingAngle(arg1), 0.0f, 0.0f);
    BattleScene_SetCameraEyeFromPosition(arg0, gBattleScene.posX->unk_D0, 0, BattleScene_GetParticipantFacingAngle(arg1), gCameraDistTarget, 0.0f);
    BattleScene_UpdateCameraModelOffset(arg1, arg0);
}

void BattleScene_SelectCameraPreset(BattlePlayerEntity* arg0, CameraStruct* arg1, s32 arg2, s32 arg3) {
    BattleScene_ClearCameraOffsetVectors();
    switch (arg2) {
        case 0:
            BattleScene_SetCameraPresetWide(arg1, arg0, arg3);
            break;

        case 1:
            BattleScene_SetCameraPresetWideStatic(arg1, arg0, arg3);
            break;

        case 2:
            BattleScene_SetCameraPresetClose(arg1, arg0, arg3);
            break;

        case 3:
            BattleScene_SetCameraPresetOffsetClose(arg1, arg0, arg3);
            break;

        case 4:
            BattleScene_SetCameraPresetFromTable(arg1, arg0, 0, arg3);
            break;

        case 5:
            BattleScene_SetCameraPresetFromTable(arg1, arg0, 1, arg3);
            break;

        case 6:
            BattleScene_SetCameraPresetAngledClose(arg1, arg0, arg3);
            break;

        case 7:
            BattleScene_SetCameraPresetLowClose(arg1, arg0, arg3);
            break;

        case 8:
            BattleScene_SetCameraPresetFromTable(arg1, arg0, 2, arg3);
            break;

        case 9:
            BattleScene_SetCameraPresetFromTable(arg1, arg0, 3, arg3);
            break;

        case 10:
            BattleScene_SetCameraPresetFromTable(arg1, arg0, 4, arg3);
            break;

        case 11:
            BattleScene_SetCameraPresetFromTable(arg1, arg0, 5, arg3);
            break;

        default:
            BattleScene_SetCameraPresetClose(arg1, arg0, arg3);
            break;
    }
}

void BattleScene_SelectCameraFollowPreset(BattlePlayerEntity* arg0, CameraStruct* arg1, s32 arg2) {
    BattleScene_ClearCameraOffsetVectors();
    switch (arg2) {
        case 0:
            BattleScene_SetCameraPresetClose(arg1, arg0, 1);
            break;
        case 1:
            BattleScene_SetCameraPresetAngledClose(arg1, arg0, 1);
            break;
        case 2:
            BattleScene_SetCameraPresetLowClose(arg1, arg0, 1);
            break;
        case 3:
            BattleScene_SetCameraPresetWide(arg1, arg0, 1);
            break;
        case 4:
            BattleScene_SetCameraFollowPresetNear(arg1, arg0, 1);
            break;
        default:
            BattleScene_SetCameraPresetClose(arg1, arg0, 1);
            break;
    }
}

void BattleScene_SelectCameraShot(BattlePlayerEntity* arg0, CameraStruct* arg1, s32 arg2) {
    BattleScene_ClearCameraOffsetVectors();
    switch (arg2) {
        case 0:
            BattleScene_CameraShotTargetStandard(arg1, arg0);
            break;

        case 1:
            BattleScene_CameraShotTargetHigh(arg1, arg0);
            break;

        case 2:
            BattleScene_CameraShotTargetLow(arg1, arg0);
            break;

        case 3:
            BattleScene_CameraShotTargetClose(arg1, arg0);
            break;

        case 4:
            BattleScene_CameraShotTargetAngled(arg1, arg0);
            break;

        case 5:
            BattleScene_CameraShotTargetHigh(arg1, arg0);
            break;

        case 6:
            BattleScene_CameraShotTargetLow(arg1, arg0);
            break;

        case 7:
            BattleScene_CameraShotTargetClose(arg1, arg0);
            break;

        default:
            BattleScene_CameraShotTargetClose(arg1, arg0);
            break;
    }
}
