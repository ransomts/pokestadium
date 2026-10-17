#include "fragment15.h"
#include "src/F420.h"
#include "src/stage_loader.h"
#include "src/fragments/3/fragment3.h"

static s16 gCameraYaw;
static s16 gCameraPitch;
static f32 gCameraDistance;
static s16 D_8690B608;
static s16 D_8690B60A;
static f32 gHorizontalDist;
static f32 D_8690B610;
static Vec3f D_8690B618;

f32 ComputeDistance3D(Vec3f arg0, Vec3f arg1) {
    return sqrtf(SQ(arg1.x - arg0.x) + SQ(arg1.y - arg0.y) + SQ(arg1.z - arg0.z));
}

f32 ScaleCameraDistance(f32 arg0) {
    f32 temp_fv1 = (D_8690B2F8.unk_00 + gCameraZoomOffset) * arg0;

    if (temp_fv1 > 400.0f) {
        return 400.0f;
    }
    return temp_fv1;
}

f32 ComputeDistanceXZ(Vec3f arg0, Vec3f arg1) {
    return sqrtf(SQ(arg1.x - arg0.x) + SQ(arg1.z - arg0.z));
}

void func_8690232C(void) {
}

void Camera_Init(void) {
    gMiniCameraPtr = D_87906050->unk_00.unk_0C;
    gCameraYaw = 0;
    gCameraPitch = 0;
    gCameraDistance = ScaleCameraDistance(4.0f);

    if (D_8690B2F8.unk_08 != 0.0f) {
        gMiniCameraPtr->unk_60.at.y = D_8690B2F8.unk_08;
    } else {
        gMiniCameraPtr->unk_60.at.y = D_8690B2F8.unk_04 + D_8690B2F8.unk_0C;
    }

    Camera_SetViewParameters(&gMiniCameraPtr->unk_60.at, &gMiniCameraPtr->unk_60.eye, gCameraDistance, gCameraYaw, gCameraPitch);

    if (gMiniCameraPtr->unk_60.eye.y < 12.0f) {
        gMiniCameraPtr->unk_60.eye.y = 12.5f;
        Matrix_Decompose(&gMiniCameraPtr->unk_60.at, &gMiniCameraPtr->unk_60.eye, &gCameraDistance, &gCameraYaw, &gCameraPitch);
    }

    gMiniCameraPtr->unk_24.near = 20.0f;
    gMiniCameraPtr->unk_24.far = 10000.0f;
    gMiniCameraPtr->unk_24.fovy = 40.0f;
    gCameraParams->unk_008 = 40.0f;

    D_8690B610 = 0.0f;

    Vec3f_Set(&D_8690B618, gMiniCameraPtr->unk_60.at.x, gMiniCameraPtr->unk_60.at.y, gMiniCameraPtr->unk_60.at.z);
}

void Camera_UpdateZoomFromInput(void) {
    f32 temp_fv1;

    if (gPlayer2Controller->stickMag != 0.0f) {
        if (gPlayer2Controller->stickY >= 0.0f) {
            gCameraZoomOffset += gPlayer2Controller->stickMag / 400.0f;
        } else {
            gCameraZoomOffset -= gPlayer2Controller->stickMag / 400.0f;
        }

        temp_fv1 = 10.0f - D_8690B2F8.unk_00;
        if (gCameraZoomOffset < temp_fv1) {
            gCameraZoomOffset = temp_fv1;
        }

        if (gCameraZoomOffset > 60.0f) {
            gCameraZoomOffset = 60.0f;
        }
    }

    HAL_Printf(0x14, 0x14, "OFFSET %6.2f", gCameraZoomOffset);
}

void Camera_ResetPosition(void) {
    gCameraYaw = 0;
    gCameraPitch = 0;
    gCameraDistance = ScaleCameraDistance(4.0f);
    gMiniCameraPtr->unk_60.at.x = 0.0f;
    gMiniCameraPtr->unk_60.at.z = 0.0f;

    if (D_8690B2F8.unk_08 != 0) {
        gMiniCameraPtr->unk_60.at.y = D_8690B2F8.unk_08;
    } else {
        gMiniCameraPtr->unk_60.at.y = D_8690B2F8.unk_04 + D_8690B2F8.unk_0C;
    }

    Camera_SetViewParameters(&gMiniCameraPtr->unk_60.at, &gMiniCameraPtr->unk_60.eye, gCameraDistance, gCameraYaw, gCameraPitch);

    if (gMiniCameraPtr->unk_60.eye.y < 12.0f) {
        gMiniCameraPtr->unk_60.eye.y = 12.5f;
        Matrix_Decompose(&gMiniCameraPtr->unk_60.at, &gMiniCameraPtr->unk_60.eye, &gCameraDistance, &gCameraYaw, &gCameraPitch);
    }

    gMiniCameraPtr->unk_24.near = 20.0f;
    gMiniCameraPtr->unk_24.far = 10000.0f;
    gMiniCameraPtr->unk_24.fovy = 40.0f;
    gCameraParams->unk_008 = 40.0f;
    D_8690B610 = 0.0f;

    Vec3f_Set(&D_8690B618, gMiniCameraPtr->unk_60.at.x, gMiniCameraPtr->unk_60.at.y, gMiniCameraPtr->unk_60.at.z);
}

s32 Camera_ToggleFOV(void) {
    if (gControllerInput.buttonPressed & 0x10) {
        if (gCameraParams->unk_008 == 25.0f) {
            gCameraParams->unk_008 = 40.0f;
        } else {
            gCameraParams->unk_008 = 25.0f;
        }
    }

    gMiniCameraPtr->unk_24.fovy = func_800104AC(gMiniCameraPtr->unk_24.fovy, gCameraParams->unk_008, 1.5f, 1.5f);

    if (gMiniCameraPtr->unk_24.fovy == gCameraParams->unk_008) {
        return 0;
    }
    return 1;
}

void TransformVec3fByMtxF(Vec3f* arg0, MtxF* arg1) {
    f32 x = (arg1->mf[0][0] * arg0->x) + (arg1->mf[0][1] * arg0->y) + (arg1->mf[0][2] * arg0->z);
    f32 y = (arg1->mf[1][0] * arg0->x) + (arg1->mf[1][1] * arg0->y) + (arg1->mf[1][2] * arg0->z);
    f32 z = (arg1->mf[2][0] * arg0->x) + (arg1->mf[2][1] * arg0->y) + (arg1->mf[2][2] * arg0->z);

    arg0->x = x;
    arg0->y = y;
    arg0->z = z;
}

void Camera_RotateAroundTarget(s16 arg0) {
    MtxF sp70;
    Vec3s sp68;
    Vec3f sp5C;
    Vec3f sp50;
    UNUSED s32 pad[3];
    Vec3f sp38;
    UNUSED s32 pad2;

    Vec3f_Set(&sp38, 0, 0.0f, 0.0f);
    Matrix_Decompose(&sp38, &gMiniCameraPtr->unk_60.eye, &gHorizontalDist, &D_8690B608, &D_8690B60A);
    Vec3f_Set(&sp50, gMiniCameraPtr->unk_60.at.x, 0.0f, gMiniCameraPtr->unk_60.at.z);
    func_8000EB70(&sp68, 0, D_8690B60A + arg0, 0);
    Vec3f_Set(&sp5C, gCameraParams->unk_004 * 4.0f, 0.0f, 0.0f);
    Matrix_RotateTranslateScale(&sp70, &gMiniCameraPtr->unk_60.at, &sp68);
    TransformVec3fByMtxF(&sp5C, &sp70);

    sp50.x += sp5C.x;
    sp50.z += sp5C.z;

    gMiniCameraPtr->unk_60.at.x = sp50.x;
    gMiniCameraPtr->unk_60.at.z = sp50.z;

    Matrix_Decompose(&sp38, &gMiniCameraPtr->unk_60.at, &gHorizontalDist, &D_8690B608, &D_8690B60A);
    gHorizontalDist = ComputeDistanceXZ(sp38, gMiniCameraPtr->unk_60.at);
    if ((ScaleCameraDistance(1.9f) - 1.0f) <= gHorizontalDist) {
        Camera_SetViewParameters(&sp38, &sp50, ScaleCameraDistance(1.9f) - 1.0f, 0, D_8690B60A);
        gMiniCameraPtr->unk_60.at.x = sp50.x;
        gMiniCameraPtr->unk_60.at.z = sp50.z;
    }
    Matrix_Decompose(&gMiniCameraPtr->unk_60.at, &gMiniCameraPtr->unk_60.eye, &gCameraDistance, &gCameraYaw, &gCameraPitch);
}

void Camera_UpdateSpeedFactor(void) {
    if (((gControllerInput.buttonDown & 8) | (gControllerInput.buttonDown & 4) | (gControllerInput.buttonDown & 2) |
         (gControllerInput.buttonDown & 1)) != 0) {
        gCameraParams->unk_004 = func_800104AC(gCameraParams->unk_004, 1.0f, 0.2f, 0.2f);
    } else {
        gCameraParams->unk_004 = func_800104AC(gCameraParams->unk_004, 0.0f, 0.2f, 0.2f);
    }

    if ((gControllerInput.buttonDown & 8) && (gMiniCameraPtr->unk_60.at.y < 300.0f)) {
        gMiniCameraPtr->unk_60.at.y += 4.0f * gCameraParams->unk_004;
        Matrix_Decompose(&gMiniCameraPtr->unk_60.at, &gMiniCameraPtr->unk_60.eye, &gCameraDistance, &gCameraYaw, &gCameraPitch);
        if (gCameraYaw < -0x38E3) {
            gMiniCameraPtr->unk_60.at.y -= 4.0f * gCameraParams->unk_004;
        }
        Matrix_Decompose(&gMiniCameraPtr->unk_60.at, &gMiniCameraPtr->unk_60.eye, &gCameraDistance, &gCameraYaw, &gCameraPitch);
    } else if ((gControllerInput.buttonDown & 4) && (gMiniCameraPtr->unk_60.at.y > 5.0f)) {
        gMiniCameraPtr->unk_60.at.y -= 4.0f * gCameraParams->unk_004;
        Matrix_Decompose(&gMiniCameraPtr->unk_60.at, &gMiniCameraPtr->unk_60.eye, &gCameraDistance, &gCameraYaw, &gCameraPitch);
        if (gCameraYaw >= 0x38E4) {
            gMiniCameraPtr->unk_60.at.y += 4.0f * gCameraParams->unk_004;
        }
        Matrix_Decompose(&gMiniCameraPtr->unk_60.at, &gMiniCameraPtr->unk_60.eye, &gCameraDistance, &gCameraYaw, &gCameraPitch);
    }

    if (gMiniCameraPtr->unk_60.at.y > 200.0f) {
        gMiniCameraPtr->unk_60.at.y = 200.0f;
        Matrix_Decompose(&gMiniCameraPtr->unk_60.at, &gMiniCameraPtr->unk_60.eye, &gCameraDistance, &gCameraYaw, &gCameraPitch);
    }

    if (gMiniCameraPtr->unk_60.at.y < 5.0f) {
        gMiniCameraPtr->unk_60.at.y = 5.0f;
        Matrix_Decompose(&gMiniCameraPtr->unk_60.at, &gMiniCameraPtr->unk_60.eye, &gCameraDistance, &gCameraYaw, &gCameraPitch);
    }

    if (gControllerInput.buttonDown & 1) {
        Camera_RotateAroundTarget(0);
    } else if (gControllerInput.buttonDown & 2) {
        Camera_RotateAroundTarget(-0x8000);
    }
}

void Camera_ClampSegmentToRadius(Vec3f* arg0, Vec3f* arg1, Vec3f arg2, f32 arg3, s32 arg4) {
    Vec3f sp94;
    Vec3f sp88;
    Vec3f sp7C;
    Vec3f sp70;
    f32 sp6C;
    f32 sp68;
    f32 tmp;
    f32 sp3C;
    f32 sp38;
    f32 sp34;
    f32 sp54;

    sp70 = D_86908C20;

    if (arg0->x == arg1->x) {
        sp7C.x = arg0->x;
        if (arg0->z < 0.0) {
            sp7C.z = -arg3;
        } else {
            sp7C.z = arg3;
        }
    } else {
        sp6C = (arg1->z - arg0->z) / (arg1->x - arg0->x);
        sp68 = arg1->z - (arg1->x * sp6C);

        sp54 = (((SQ(arg2.x) + SQ(sp68)) - ((2 * arg2.z) * sp68)) + SQ(arg2.z)) - SQ(arg3);

        sp38 = SQ(sp6C) + 1.0f;
        sp3C = (((2 * sp6C) * sp68) - (2 * arg2.x)) - ((2 * arg2.z) * sp6C);

        if (SQ(sp3C) < ((4 * sp38) * sp54)) {
            Vec3f_Set(arg1, arg0->x, arg0->y, arg0->z);
            return;
        }

        sp34 = SQ(sp3C) - ((4 * sp38) * sp54);

        sp94.x = (-sp3C - sqrtf(sp34)) / (2 * sp38);
        sp94.y = 0.0f;
        sp94.z = (sp6C * sp94.x) + sp68;

        sp88.x = (sqrtf(sp34) + -sp3C) / (2 * sp38);
        sp88.y = 0.0f;
        sp88.z = (sp6C * sp88.x) + sp68;

        if (ComputeDistanceXZ(*arg0, sp94) > ComputeDistanceXZ(*arg0, sp88)) {
            sp7C.x = sp88.x;
            sp7C.z = sp88.z;
        } else {
            sp7C.x = sp94.x;
            sp7C.z = sp94.z;
        }
    }

    sp6C = arg0->y - arg1->y;
    if (sp6C == 0.0f) {
        sp7C.y = arg1->y;
    } else {
        if (arg1->x == arg0->x) {
            tmp = (sp7C.z - arg0->z) / (arg1->z - arg0->z);
        } else {
            tmp = (sp7C.x - arg0->x) / (arg1->x - arg0->x);
        }

        if (arg4 == 1) {
            sp7C.y = ((arg1->y - arg0->y) * tmp) + arg0->y;
        } else {
            sp7C.y = ((arg0->y - arg1->y) * tmp) + arg1->y;
        }
    }

    Vec3f_Set(arg0, arg1->x, arg1->y, arg1->z);
    Vec3f_Set(arg1, sp7C.x, sp7C.y, sp7C.z);
    Matrix_Decompose(&gMiniCameraPtr->unk_60.at, arg1, &gCameraDistance, &gCameraYaw, &gCameraPitch);
}

void func_8690325C(Vec3f* arg0, Vec3f* arg1, Vec3f arg2, f32 arg3) {
    Vec3f sp84;
    Vec3f sp78;
    Vec3f tmp;
    Vec3f sp60;
    f32 sp5C;
    f32 sp58;
    f32 sp40;
    f32 sp3C;
    f32 sp38;
    f32 sp2C;
    f32 sp44;

    sp60 = D_86908C2C;
    sp2C = arg1->x;
    tmp.z = arg3;
    if (gMiniCameraPtr->unk_60.at.x == sp2C) {
        tmp.x = gMiniCameraPtr->unk_60.at.x;
    } else {
        sp5C = (arg1->z - gMiniCameraPtr->unk_60.at.z) / (arg1->x - gMiniCameraPtr->unk_60.at.x);
        sp58 = arg1->z - (arg1->x * sp5C);

        sp44 = (((SQ(arg2.x) + SQ(sp58)) - ((2 * arg2.z) * sp58)) + SQ(arg2.z)) - SQ(arg3);

        sp3C = SQ(sp5C) + 1.0f;
        sp38 = ((2 * sp5C * sp58) - (2 * arg2.x)) - ((2 * arg2.z) * sp5C);

        sp2C = SQ(sp38) - ((4 * sp3C) * sp44);

        sp84.x = (-sp38 - sqrtf(sp2C)) / (2 * sp3C);
        sp84.y = 0.0f;
        sp84.z = (sp5C * sp84.x) + sp58;

        sp78.x = (sqrtf(sp2C) + -sp38) / (2 * sp3C);
        sp78.y = 0.0f;
        sp78.z = (sp5C * sp78.x) + sp58;

        if (ComputeDistanceXZ(*arg1, sp84) > ComputeDistanceXZ(*arg1, sp78)) {
            tmp.x = sp78.x;
            tmp.z = sp78.z;
        } else {
            tmp.x = sp84.x;
            tmp.z = sp84.z;
        }
    }

    tmp.y = arg0->y;

    Vec3f_Set(arg1, tmp.x, tmp.y, tmp.z);
    Matrix_Decompose(&gMiniCameraPtr->unk_60.at, arg1, &gCameraDistance, &gCameraYaw, &gCameraPitch);
}

void Camera_InterpolatePositionToY(Vec3f* arg0, Vec3f* arg1, f32 arg2, f32 arg3, s32 arg4) {
    f32 temp_fa0;

    arg2 += arg3;

    if (arg4 == 1) {
        temp_fa0 = (arg2 - arg0->y) / (arg1->y - arg0->y);
        if (arg1->x == arg0->x) {
            arg1->x = arg0->x;
        } else {
            arg1->x = ((arg1->x - arg0->x) * temp_fa0) + arg0->x;
        }

        if (arg1->z == arg0->z) {
            arg1->z = arg0->z;
        } else {
            arg1->z = ((arg1->z - arg0->z) * temp_fa0) + arg0->z;
        }
    }

    arg1->y = arg2;
    Matrix_Decompose(&gMiniCameraPtr->unk_60.at, arg1, &gCameraDistance, &gCameraYaw, &gCameraPitch);
}

void Camera_EnforceConstraints(Vec3f* arg0, Vec3f* arg1) {
    UNUSED s32 pad[2];
    Vec3f sp3C = D_86908C38;
    f32 sp38;

    if (arg1->y < 12.0f) {
        Camera_InterpolatePositionToY(arg0, arg1, 12.0f, 0.05f, 0);
    }

    if (arg1->y > 350.0f) {
        Camera_InterpolatePositionToY(arg0, arg1, 350.0f, 0.0f, 0);
    }

    sp38 = ScaleCameraDistance(1.9f);
    if (ComputeDistanceXZ(sp3C, *arg1) < sp38) {
        Camera_ClampSegmentToRadius(arg0, arg1, sp3C, ScaleCameraDistance(1.9f) + 0.05f, 1);
    }

    if (ComputeDistanceXZ(sp3C, *arg1) > 400.0f) {
        Camera_ClampSegmentToRadius(arg0, arg1, sp3C, 399.0f, 1);
    }

    if (ComputeDistanceXZ(gMiniCameraPtr->unk_60.at, *arg1) < 30.0f) {
        Camera_ClampSegmentToRadius(arg0, arg1, gMiniCameraPtr->unk_60.at, 30.1f, 1);
    }
}

void Camera_EnforceConstraintsMode(Vec3f* arg0, Vec3f* arg1, s32 arg2) {
    UNUSED s32 pad[2];
    Vec3f sp3C = D_86908C44;
    f32 sp38;

    if (arg2 == 0) {
        if (arg1->y < 12.0f) {
            Camera_InterpolatePositionToY(arg0, arg1, 12.0f, 0.05f, 1);
        }

        if (arg1->y > 350.0f) {
            Camera_InterpolatePositionToY(arg0, arg1, 350.0f, 0.0f, 1);
        }
    } else {
        if (arg1->y < 12.0f) {
            Camera_InterpolatePositionToY(arg0, arg1, 12.0f, 0.05f, 0);
        }

        if (arg1->y > 350.0f) {
            Camera_InterpolatePositionToY(arg0, arg1, 350.0f, 0.0f, 0);
        }
    }

    if (arg2 == 0) {
        sp38 = ScaleCameraDistance(1.9f);
        if (ComputeDistanceXZ(sp3C, *arg1) < sp38) {
            Camera_ClampSegmentToRadius(arg0, arg1, sp3C, ScaleCameraDistance(1.9f) + 0.05f, 0);
        }

        if (ComputeDistanceXZ(sp3C, *arg1) > 400.0f) {
            Camera_ClampSegmentToRadius(arg0, arg1, sp3C, 399.0f, 0);
        }

        if (ComputeDistanceXZ(gMiniCameraPtr->unk_60.at, *arg1) < 30.0f) {
            Camera_ClampSegmentToRadius(arg0, arg1, gMiniCameraPtr->unk_60.at, 30.1f, 0);
        }
    } else {
        sp38 = ScaleCameraDistance(1.9f);
        if (ComputeDistanceXZ(sp3C, *arg1) < sp38) {
            func_8690325C(arg0, arg1, sp3C, ScaleCameraDistance(1.9f) + 0.05f);
        }

        if (ComputeDistanceXZ(sp3C, *arg1) > 400.0f) {
            func_8690325C(arg0, arg1, sp3C, 399.0f);
        }

        if (ComputeDistanceXZ(gMiniCameraPtr->unk_60.at, *arg1) < 30.0f) {
            func_8690325C(arg0, arg1, gMiniCameraPtr->unk_60.at, 30.1f);
        }
    }
}

void Camera_Update(void) {
    Vec3f sp44;
    Vec3f sp38;
    UNUSED s32 pad;
    f32 mag;

    if (gControllerInput.stickMag != 0.0f) {
        Vec3f_Set(&sp44, gMiniCameraPtr->unk_60.eye.x, gMiniCameraPtr->unk_60.eye.y, gMiniCameraPtr->unk_60.eye.z);
        if (gControllerInput.stickY >= 0.0f) {
            mag = -(gControllerInput.stickMag / 6.0f);
            Camera_SetViewParameters(&gMiniCameraPtr->unk_60.eye, &sp38, mag, gCameraYaw, gCameraPitch);
        } else {
            mag = gControllerInput.stickMag / 6.0f;
            Camera_SetViewParameters(&gMiniCameraPtr->unk_60.eye, &sp38, mag, gCameraYaw, gCameraPitch);
        }
        gCameraDistance = ComputeDistance3D(gMiniCameraPtr->unk_60.at, sp38);
        Camera_EnforceConstraints(&sp44, &sp38);
        Vec3f_Set(&gMiniCameraPtr->unk_60.eye, sp38.x, sp38.y, sp38.z);
    }

    if (gControllerInput.buttonDown & 0x200) {
        gCameraPitch -= 0x100;
    }

    if (gControllerInput.buttonDown & 0x100) {
        gCameraPitch += 0x100;
    }

    if (gControllerInput.buttonDown & 0x300) {
        Vec3f_Set(&sp44, gMiniCameraPtr->unk_60.eye.x, gMiniCameraPtr->unk_60.eye.y, gMiniCameraPtr->unk_60.eye.z);
        Camera_SetViewParameters(&gMiniCameraPtr->unk_60.at, &sp38, gCameraDistance, gCameraYaw, gCameraPitch);
        Camera_EnforceConstraintsMode(&sp44, &sp38, 1);
        Vec3f_Set(&gMiniCameraPtr->unk_60.eye, sp38.x, sp38.y, sp38.z);
    }

    if (gControllerInput.buttonDown & 0x800) {
        gCameraYaw += 0x100;
    }

    if (gControllerInput.buttonDown & 0x400) {
        gCameraYaw -= 0x100;
    }

    if (gControllerInput.buttonDown & 0xC00) {
        Vec3f_Set(&sp44, gMiniCameraPtr->unk_60.eye.x, gMiniCameraPtr->unk_60.eye.y, gMiniCameraPtr->unk_60.eye.z);
        Camera_SetViewParameters(&gMiniCameraPtr->unk_60.at, &sp38, gCameraDistance, gCameraYaw, gCameraPitch);
        Camera_EnforceConstraintsMode(&sp44, &sp38, 0);
        Vec3f_Set(&gMiniCameraPtr->unk_60.eye, sp38.x, sp38.y, sp38.z);
    }
}
