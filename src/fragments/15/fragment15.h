#ifndef _FRAGMENT15_H_
#define _FRAGMENT15_H_

#include "global.h"
#include "src/controller.h"
#include "src/1C720.h"

typedef struct unk_D_8690B2F8 {
    /* 0x00 */ f32 unk_00;
    /* 0x04 */ f32 unk_04;
    /* 0x08 */ f32 unk_08;
    /* 0x0C */ f32 unk_0C;
} unk_D_8690B2F8; // size >= 0x10

typedef struct unk_D_8690A710 {
    /* 0x000 */ char unk000[0x4];
    /* 0x004 */ f32 unk_004;
    /* 0x008 */ f32 unk_008;
    /* 0x00C */ s32 unk_00C;
    /* 0x010 */ char unk010[0x4];
    /* 0x014 */ u8 unk_014;
    /* 0x015 */ char unk015[0x16F];
} unk_D_8690A710; // size = 0x184

typedef struct unk_D_8690B350 {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s16 unk_08;
    /* 0x0A */ s16 unk_0A;
    /* 0x0C */ s16 unk_0C;
    /* 0x0E */ s16 unk_0E;
} unk_D_8690B350; // size = 0x10

typedef struct unk_D_8690B360 {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ s16 unk_08;
    /* 0x0A */ s16 unk_0A;
    /* 0x0C */ f32 unk_0C;
    /* 0x10 */ f32 unk_10;
    /* 0x14 */ f32 unk_14;
} unk_D_8690B360; // size = 0x18

typedef struct unk_D_8690B308 {
    /* 0x00 */ s16 unk_00[8];
    /* 0x18 */ f32 unk_10;
    /* 0x1C */ f32 unk_14;
    /* 0x20 */ f32 unk_18;
    /* 0x24 */ f32 unk_1C;
    /* 0x28 */ f32 unk_20;
    /* 0x2C */ f32 unk_24;
    /* 0x30 */ f32 unk_28;
    /* 0x34 */ f32 unk_2C;
    /* 0x38 */ s16 unk_30;
    /* 0x3A */ s16 unk_32;
    /* 0x3C */ s16 unk_34;
    /* 0x3E */ s16 unk_36;
} unk_D_8690B308; // size >= 0x38

typedef struct unk_D_8690B3C0 {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
} unk_D_8690B3C0; // size >= 0x10

extern u8 D_5001950[];
extern u8 D_5003AE8[];

extern Vec3f gCameraClampCenter;
extern Vec3f gCameraClampCenterMode;
extern Vec3f gCameraConstraintCenter;
extern Vec3f gCameraConstraintCenterMode;
extern char* D_86908C58[];
extern Color_RGB8 D_86908C98;
extern Color_RGB8 D_86908C9C;

extern const char D_8690A520[];
extern const char D_8690A52C[];
extern const char D_8690A538[];
extern const char D_8690A544[];
extern const char D_8690A550[];
extern const char D_8690A55C[];
extern const char D_8690A568[];
extern const char D_8690A574[];
extern const char D_8690A584[];
extern const char D_8690A594[];
extern const char D_8690A5A0[];
extern const char D_8690A5AC[];
extern const char D_8690A5B8[];
extern const char D_8690A5C8[];
extern const char D_8690A5D8[];
extern const char D_8690A5E8[];

extern char** D_8690A678;
extern f32 gCameraZoomOffset;
extern unk_D_8690A710* gCameraParams;
extern unk_D_8690B2F8 gCameraConfig;
extern unk_D_8690B308 D_8690B308;
extern s32 D_8690B344;
extern s32 D_8690B348;
extern unk_D_8690B350 D_8690B350;
extern unk_D_8690B360 D_8690B360;

extern s32 D_8690B384;
extern s32 D_8690B388;
extern s32 D_8690B380;
extern s32 D_8690B38C;
extern Controller gControllerInput;
extern unk_D_8690B3C0 D_8690B3C0;
extern s8 D_8690B3D0[255];

s32 CameraNode_SetAnglesFromCurrent(s32 arg0, GraphNode* arg1);
s32 CameraNode_SetAnglesNegated(s32 arg0, GraphNode* arg1);
s32 GraphNode_ApplyGlobalColor(s32 arg0, GraphNode* arg1);
void SetGlobalRGBA(u8 arg0, u8 arg1, u8 arg2);
void LoadStageDataDMA(void);
unk_D_86002F58_004_000_010_024* CreatePlayerStatNode(PokemonData* arg0);
void Stage_Init(void);
void WaitForRSPAndCleanup(void);
void LoadStageFragmentByIndex(s32 arg0);
void Graphics_Init(void);
void ComputeOffsetFromAngle(f32* arg0, f32* arg1, s16* arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, s16 arg7);
void StageState_Reset(void);
void CopyControllerState(Controller* arg0, Controller* arg1);
void SimulateControllerInputFromScript(void);
void ApplyPolarOffset(f32* arg0, f32* arg1, s16 arg2, s16 arg3);
void UpdateControllerAndMenuInput(void);
void UpdateStageAnimationTimers(void);
void UpdateStageSoundTimer(void);
void ResetAnimStateIfSecondLast(void);
void HandleSnapshotButton(void);
void LoadFragmentIfFlag(u16 arg0);
s32 ProcessCameraNavigationInput(void);
void UpdateTutorialText(void);
s32 StageMainUpdate(void);
s32 func_8690172C(void);
s32 func_869017D0(void);
s32 func_869018A0(void);
s32 func_8690193C(void);
s32 func_869019BC(void);
void func_86901A44(void);
void func_86901B28(void);
void func_86901ECC(void);
void func_86901FB4(void);
void func_86902004(s32 arg0);
s32 func_86902098(s32 arg0, UNUSED s32 arg1);

f32 ComputeDistance3D(Vec3f arg0, Vec3f arg1);
f32 ScaleCameraDistance(f32 arg0);
f32 ComputeDistanceXZ(Vec3f arg0, Vec3f arg1);
void func_8690232C(void);
void Camera_Init(void);
void Camera_UpdateZoomFromInput(void);
void Camera_ResetPosition(void);
s32 Camera_ToggleFOV(void);
void TransformVec3fByMtxF(Vec3f* arg0, MtxF* arg1);
void Camera_RotateAroundTarget(s16 arg0);
void Camera_UpdateSpeedFactor(void);
void Camera_ClampSegmentToRadius(Vec3f* arg0, Vec3f* arg1, Vec3f arg2, f32 arg3, s32 arg4);
void Camera_ClampSegmentToRadiusMode(Vec3f* arg0, Vec3f* arg1, Vec3f arg2, f32 arg3);
void Camera_InterpolatePositionToY(Vec3f* arg0, Vec3f* arg1, f32 arg2, f32 arg3, s32 arg4);
void Camera_EnforceConstraints(Vec3f* arg0, Vec3f* arg1);
void Camera_EnforceConstraintsMode(Vec3f* arg0, Vec3f* arg1, s32 arg2);
void Camera_Update(void);

void RenderMessageBox(char*);
void RenderMainMenu(s32);
void RenderGradientPanel(void);
void RenderHPBar(void);
void func_86908418(void);
void func_86908668(void);
void func_869089AC(void);


#endif // _FRAGMENT15_H_
