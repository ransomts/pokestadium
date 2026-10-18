#include "fragment17.h"
#include "src/F420.h"

typedef struct CameraModeFlag {
    u8 unk_00[1];
} CameraModeFlag; // size = ??

static CameraModeFlag gCameraModeFlag = { 0x8E };

s16 GetCameraBaseY(void) {
    return gCameraTarget->unk_004.unk_01E.y + 0x8000;
}

s32 ByteArrayContains(u8 arg0, u8* arg1, s32 arg2) {
    while (arg2--) {
        if (arg0 == *arg1) {
            return 1;
        }
        arg1++;
    }
    return 0;
}

void ComputeCameraTargetPos(unk_D_86B0FA78* arg0, Vec3f* arg1) {
    f32 sp24 = 0.0f;
    CameraModeFlag sp20 = gCameraModeFlag;

    if (ByteArrayContains(gCameraTarget->unk_174, sp20.unk_00, 1) != 0) {
        sp24 = gMonsterStageData.unk_04 / 1.5f;
    }

    if (gMonsterStageData.unk_08 != 0) {
        arg1->x = arg0->unk_004.unk_024.x;
        arg1->y = arg0->unk_004.unk_024.y + sp24;
        arg1->z = arg0->unk_004.unk_024.z;
    } else {
        arg1->x = arg0->unk_004.unk_024.x;
        arg1->y = arg0->unk_004.unk_024.y + gMonsterStageData.unk_04;
        arg1->z = arg0->unk_004.unk_024.z;
    }

    if (arg1->y < 0) {
        arg1->y = gMonsterStageData.unk_04;
    }
}

void Camera_UpdateView(void) {
    Camera_SetViewParameters(&gCameraState->unk_04, &gCameraState->unk_00->unk_60.at, gCameraState->unk_1C, gCameraState->unk_10,
                  GetCameraBaseY() + gCameraState->unk_12);
    Camera_SetViewParameters(&gCameraState->unk_04, &gCameraState->unk_00->unk_60.eye, gCameraState->unk_20, gCameraState->unk_16,
                  GetCameraBaseY() + gCameraState->unk_18);

    gCameraState->unk_00->unk_60.at.y += gMonsterStageData.unk_0C;
    if (gCameraState->unk_00->unk_60.eye.y <= 10.0f) {
        gCameraState->unk_00->unk_60.eye.y = 10.0f;
    }
}

f32 ClampFloatByScale(f32 arg0, f32 arg1) {
    f32 temp_fv1 = gMonsterStageData.unk_00 * arg0;

    if (arg1 < temp_fv1) {
        return arg1;
    }
    return temp_fv1;
}

void Camera_SetBaseParams(s16 arg0, s16 arg1, s16 arg2, s16 arg3) {
    gCameraState->unk_10 = arg0;
    gCameraState->unk_12 = arg1;
    gCameraState->unk_24 = arg2;
    gCameraState->unk_26 = arg3;
}

void func_86B08A3C(f32 arg0, f32 arg1) {
    gCameraState->unk_1C = arg0;
    gCameraState->unk_30 = arg1;
}

void Camera_SetEyeParams(s16 arg0, s16 arg1, s16 arg2, s16 arg3) {
    gCameraState->unk_16 = arg0;
    gCameraState->unk_18 = arg1;
    gCameraState->unk_2A = arg2;
    gCameraState->unk_2C = arg3;
}

void func_86B08AB4(f32 arg0, f32 arg1) {
    gCameraState->unk_20 = arg0;
    gCameraState->unk_34 = arg1;
}

void Camera_SetApproachParams(f32 arg0, f32 arg1) {
    gCameraState->unk_38 = arg0;
    gCameraState->unk_3C = arg1;
}

void Camera_InitFromConfig(unk_D_86B0C160* arg0, CameraStruct* arg1) {
    f32 sp34;
    f32 sp30;
    f32 sp2C;
    f32 sp28;

    gCameraState->unk_44 = 0.0f;
    if (arg0->unk_30 != 200.0f) {
        arg1->unk_24.fovy = gCameraState->unk_40 = arg0->unk_30;
    } else {
        gCameraState->unk_40 = arg0->unk_30;
    }

    sp34 = ClampFloatByScale(arg0->unk_0C, 500.0f);
    sp30 = ClampFloatByScale(arg0->unk_20, 500.0f);
    sp2C = ClampFloatByScale(arg0->unk_10, 500.0f);
    sp28 = ClampFloatByScale(arg0->unk_24, 500.0f);

    Camera_SetBaseParams(arg0->unk_00, GetCameraBaseY() + arg0->unk_02, arg0->unk_14, GetCameraBaseY() + arg0->unk_16);
    func_86B08A3C(sp34, sp30);

    Camera_SetEyeParams(arg0->unk_06, GetCameraBaseY() + arg0->unk_08, arg0->unk_1A, GetCameraBaseY() + arg0->unk_1C);
    func_86B08AB4(sp2C, sp28);
    Camera_SetApproachParams(arg0->unk_28, arg0->unk_2C);
}

s32 func_86B08C44(CameraStruct* arg0) {
    Vec3f sp5C;
    Vec3f sp50;
    Vec3f sp44;
    Vec3f sp38;
    f32 sp34;
    f32 sp30;
    s16 sp2E;
    s16 sp2C;

    if (gCameraState->unk_40 != 200.0f) {
        arg0->unk_24.fovy = gCameraState->unk_40;
    } else {
        Math_ApproachFloat(&arg0->unk_24.fovy, 30.0f, 0.06f);
    }

    Math_ApproachFloat(&gCameraState->unk_44, gCameraState->unk_38, gCameraState->unk_3C);
    Camera_SetViewParameters(&gCameraState->unk_04, &sp50, gCameraState->unk_34, gCameraState->unk_2A,
                  GetCameraBaseY() + gCameraState->unk_2C);

    if (sp50.y <= 10.0f) {
        sp50.y = 10.0f;
    }

    func_86B01404(&sp44, &arg0->unk_60.eye);
    Matrix_Decompose(&sp44, &sp50, &sp34, &sp2E, &sp2C);
    Camera_SetViewParameters(&sp44, &arg0->unk_60.eye, gCameraState->unk_44 * sp34, sp2E, sp2C);
    Camera_SetViewParameters(&gCameraState->unk_04, &sp38, gCameraState->unk_30, gCameraState->unk_24,
                  GetCameraBaseY() + gCameraState->unk_26);

    sp38.y += gMonsterStageData.unk_0C;

    func_86B01404(&sp5C, &arg0->unk_60.at);
    Matrix_Decompose(&sp5C, &sp38, &sp30, &sp2E, &sp2C);
    Camera_SetViewParameters(&sp5C, &arg0->unk_60.at, gCameraState->unk_44 * sp30, sp2E, sp2C);

    if ((sp34 <= 1.0f) && (sp30 <= 1.0f)) {
        return 1;
    }
    return 0;
}
