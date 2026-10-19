#ifndef _FRAGMENT34_H_
#define _FRAGMENT34_H_

#include "global.h"

struct ParticleEffectInstance;
struct ParticleRenderSettings;
struct BattlePlayerEntity;
struct gBattleAnimEffectSlots;

typedef void (*func_unk_D_8140E724_008)(struct ParticleEffectInstance*);
typedef void (*func_unk_D_8140E724_00C)(struct ParticleEffectInstance*, CameraStruct*);
typedef void (*unk_D_8140E728_01C_004_1_04)(struct ParticleEffectInstance*, s32, struct ParticleRenderSettings*);
typedef void (*unk_D_8140E728_01C_004_1_08)(struct ParticleEffectInstance*, s32, struct ParticleRenderSettings*);

typedef struct unk_D_8140E728_01C_00C_1 {
    /* 0x00 */ s32 arg;
} unk_D_8140E728_01C_00C_1;

typedef union unk_D_8140E728_01C_00C {
    s32 arg;
    unk_D_8140E728_01C_00C_1* s;
} unk_D_8140E728_01C_00C;

typedef struct ParticleRenderSettings {
    /* 0x00 */ u8 posX;
    /* 0x00 */ u8 unk_01;
    /* 0x00 */ s16 posY;
    /* 0x04 */ unk_D_8140E728_01C_004_1_04 rotation;
    /* 0x08 */ unk_D_8140E728_01C_004_1_08 unk_08;
    /* 0x0C */ unk_D_8140E728_01C_00C unk_0C;
} ParticleRenderSettings; // size = 0x10

typedef union unk_D_8140E728_01C_004 {
    ParticleRenderSettings* a;
    func_unk_D_8140E724_00C func;
} unk_D_8140E728_01C_004;

typedef struct ParticleEffectData {
    /* 0x00 */ s32 posX; /* rotation: 1 = a, 3 = func */
    /* 0x04 */ unk_D_8140E728_01C_004 rotation;
} ParticleEffectData; // size = 0x08

typedef struct ParticleSpawner {
    /* 0x00 */ f32 posX;
    /* 0x04 */ Vec3f rotation;
    /* 0x10 */ Vec3s unk_10;
    /* 0x18 */ func_unk_D_8140E724_008 unk_18;
    /* 0x1C */ ParticleEffectData* unk_1C;
    /* 0x20 */ s32 unk_20;
    /* 0x24 */ u16 unk_24;
    /* 0x26 */ s16 unk_26;
    /* 0x28 */ s16 unk_28;
    /* 0x2A */ s8 unk_2A;
    /* 0x2B */ s8 unk_2B;
    /* 0x2C */ u8 unk_2C;
    /* 0x2D */ u8 unk_2D;
    /* 0x2E */ u8 unk_2E;
    /* 0x2F */ u8 unk_2F;
} ParticleSpawner; // size = 0x30

typedef struct ParticleEffectInstance {
    /* 0x00 */ struct ParticleEffectInstance* next;
    /* 0x04 */ struct ParticleEffectInstance* prev;
    /* 0x08 */ func_unk_D_8140E724_008 unk_08;
    /* 0x0C */ ParticleEffectData* unk_0C;
    /* 0x10 */ struct BattlePlayerEntity* unk_10;
    /* 0x14 */ Fragment2_1GraphNode* unk_14;
    /* 0x18 */ u32 unk_18;
    /* 0x1C */ f32 unk_1C;
    /* 0x20 */ f32 unk_20;
    /* 0x24 */ f32 unk_24;
    /* 0x28 */ f32 unk_28;
    /* 0x2C */ Vec3f unk_2C;
    /* 0x38 */ Vec3f unk_38;
    /* 0x44 */ char unk44[0xC];
    /* 0x50 */ Vec3f unk_50;
    /* 0x5C */ Vec3f unk_5C;
    /* 0x68 */ Vec3f unk_68;
    /* 0x74 */ f32 unk_74;
    /* 0x78 */ f32 unk_78;
    /* 0x7C */ Vec3f unk_7C;
    /* 0x88 */ char unk88[0xC];
    /* 0x94 */ Vec3s unk_94;
    /* 0x9A */ Vec3s rotationDelta;
    /* 0xA0 */ Vec3s unk_A0;
    /* 0xA6 */ s16 initialAlpha;
    /* 0xA8 */ s16 unk_A8;
    /* 0xAA */ s16 alphaStep;
    /* 0xAC */ s16 unk_AC;
    /* 0xAE */ s16 alpha;
    /* 0xB0 */ s16 unk_B0;
    /* 0xB2 */ s16 updateState;
    /* 0xB4 */ char unkB4[0x2];
    /* 0xB6 */ s16 rampStepTimer;
    /* 0xB8 */ s16 unk_B8;
    /* 0xBA */ s16 durationTimer;
    /* 0xBC */ s16 unk_BC;
    /* 0xBE */ u8 prim_r;
    /* 0xBF */ u8 prim_g;
    /* 0xC0 */ u8 prim_b;
    /* 0xC1 */ u8 env_r;
    /* 0xC2 */ u8 env_g;
    /* 0xC3 */ u8 env_b;
    /* 0xC4 */ u8 prim_a;
    /* 0xC5 */ char unkC5[0x1];
    /* 0xC6 */ s8 rampRepeatCount;
    /* 0xC7 */ s8 rampValue;
    /* 0xC8 */ char unkC8[0x2];
    /* 0xCA */ u8 effectType;
    /* 0xCB */ u8 unk_CB;
    /* 0xCC */ u8 unk_CC;
    /* 0xCD */ u8 targetAlpha;
    /* 0xCE */ u8 unk_CE;
    /* 0xCF */ u8 paletteIndex;
    /* 0xD0 */ s8 unk_D0;
} ParticleEffectInstance; // size = 0xD4

typedef void (*func_unk_D_8140E724)(struct ParticleEffectInstance*);

typedef struct gBattleAnimEffectSlots {
    /* 0x00 */ func_unk_D_8140E724 posX;
    /* 0x04 */ ParticleEffectData* rotation;
    /* 0x08 */ struct BattlePlayerEntity* unk_08;
    /* 0x0C */ s16 unk_0C;
    /* 0x0E */ s16 unk_0E;
    /* 0x10 */ s16 unk_10;
    /* 0x12 */ s16 unk_12;
    /* 0x14 */ s8 unk_14;
    /* 0x15 */ s8 unk_15;
    /* 0x16 */ u8 unk_16;
    /* 0x17 */ u8 unk_17;
    /* 0x18 */ u8 unk_18;
    /* 0x19 */ u8 unk_19;
    /* 0x1A */ u8 unk_1A;
    /* 0x1B */ u8 unk_1B;
} gBattleAnimEffectSlots; // size = 0x1C

typedef struct ColorLerpData {
    /* 0x00 */ s32 posX;
    /* 0x04 */ ColorLerpEntry5* rotation;
    /* 0x08 */ ColorLerpEntry5* unk_08;
    /* 0x0C */ ColorLerpEntry5* unk_0C;
    /* 0x10 */ ColorLerpEntry4* unk_10;
    /* 0x14 */ ColorLerpEntry4* unk_14;
    /* 0x18 */ ColorLerpEntry4* unk_18;
} ColorLerpData; // size = 0x1C

// Possibly unk_D_86002F34_alt7, unk_D_86002F34_alt8,
// unk_D_86002F34_alt9 or unk_D_86002F34_alt2
typedef struct ColorLerpHook {
    /* 0x00 */ char unk00[0x14];
    /* 0x14 */ ColorLerpData* unk_14;
    /* 0x18 */ Gfx* unk_18;
} ColorLerpHook; // size >= 0x1C

typedef struct arg1_func_81407874_014_000_014_000_000 {
    /* 0x00 */ Color_RGBA8 color;
    /* 0x04 */ u8 l;
} arg1_func_81407874_014_000_014_000_000; // size = 0x5

typedef struct arg1_func_81407874_014_000_018_000_000 {
    /* 0x00 */ Color_RGBA8 color;
} arg1_func_81407874_014_000_018_000_000; // size = 0x4

typedef union arg1_func_81407874_014_000_014_000 {
    arg1_func_81407874_014_000_014_000_000* ptr5;
    arg1_func_81407874_014_000_018_000_000* ptr4;
    Color_RGBA8_u32 color;
    u8** texture;
} arg1_func_81407874_014_000_014_000; // size = 0x4

typedef struct arg1_func_81407874_014_000_014 {
    /* 0x00 */ arg1_func_81407874_014_000_014_000 posX;
    /* 0x04 */ s16 rotation;
    /* 0x06 */ s16 unk_06;
} arg1_func_81407874_014_000_014; // size >= 0x08

typedef struct arg1_func_81407874_014_000_01C {
    /* 0x00 */ u16 posX;
    /* 0x02 */ u16 posY;
} arg1_func_81407874_014_000_01C; // size >= 0x04

typedef struct arg1_func_81407874_014_000 {
    /* 0x00 */ struct arg1_func_81407874_014_000* posX;
    /* 0x04 */ s32 rotation;
    /* 0x08 */ char unk08[0x8];
    /* 0x10 */ arg1_func_81407874_014_000_010* unk_10;
    /* 0x14 */ arg1_func_81407874_014_000_014* unk_14;
    /* 0x18 */ arg1_func_81407874_014_000_014* unk_18;
    /* 0x1C */ arg1_func_81407874_014_000_01C* unk_1C;
} arg1_func_81407874_014_000; // size >= 0x20

typedef struct arg1_func_81407874_014_004_008 {
    /* 0x00 */ s16 posX;
    /* 0x02 */ s16 posY;
    /* 0x04 */ s16 rotation;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ s16 unk_08;
} arg1_func_81407874_014_004_008; // size >= 0xA

typedef struct arg1_func_81407874_014_004_004 {
    /* 0x00 */ s16 fmt;
    /* 0x02 */ s16 size;
    /* 0x04 */ s16 width;
    /* 0x06 */ s16 height;
    /* 0x08 */ s16 cms;
    /* 0x0A */ s16 cmt;
    /* 0x0C */ s16 masks;
    /* 0x0E */ s16 maskt;
    /* 0x10 */ s16 shfits;
    /* 0x12 */ s16 shiftt;
} arg1_func_81407874_014_004_004; // size >= 0x14

typedef struct arg1_func_81407874_014_004 {
    /* 0x00 */ arg1_func_81407874_014_000* posX;
    /* 0x04 */ arg1_func_81407874_014_004_004* rotation;
    /* 0x08 */ arg1_func_81407874_014_004_008* unk_08;
    /* 0x0C */ arg1_func_81407874_014_000_014* unk_0C;
} arg1_func_81407874_014_004; // size >= 0x4

typedef struct arg1_func_81407874_014 {
    /* 0x00 */ arg1_func_81407874_014_000* posX;
    /* 0x04 */ arg1_func_81407874_014_004* rotation;
} arg1_func_81407874_014; // size >= 0x8

typedef struct arg1_func_81407874 {
    /* 0x00 */ char unk00[0x14];
    /* 0x00 */ arg1_func_81407874_014* unk_14;
} arg1_func_81407874; // size >= 0x18

typedef struct ParticleCameraInfo {
    /* 0x00 */ MtxF posX;
    /* 0x40 */ Vec3f unk_40;
    /* 0x4C */ Vec3f unk_4C;
    /* 0x58 */ Vec3f unk_58;
    /* 0x64 */ Vec3f unk_64;
    /* 0x70 */ s16 unk_70;
    /* 0x72 */ s16 unk_72;
    /* 0x74 */ char unk74[0x2];
    /* 0x76 */ s16 unk_76;
    /* 0x78 */ s16 unk_78;
} ParticleCameraInfo; // size = 0x7C

typedef struct unk_D_8140E634 {
    /* 0x00 */ Vec3f posX;
    /* 0x0C */ CameraStruct* unk_0C;
    /* 0x10 */ ParticleCameraInfo unk_10;
} unk_D_8140E634; // size = 0x8C

typedef struct gMatrixBufferStruct {
    /* 0x0000 */ MtxF unk_0000[364];
    /* 0x5B00 */ char unk5B00[0x80];
    /* 0x5B80 */ Mtx unk_5B80;
    /* 0x5BC0 */ char unk5BC0[0x20];
} gMatrixBufferStruct; // size = 0x5BE0

extern Gfx gDL_End3D[];
extern Gfx gDL_Begin3D[];
extern Gfx gDL_ItemIcon[];
extern Gfx gDL_BaseUI2[];
extern Gfx D_8140DC58[];
extern Gfx gDL_OverlayUI2[];
extern Gfx D_8140DC98[];
extern Gfx D_8140DCB8[];
extern Gfx gDL_BaseUI[];
extern Gfx D_8140DCF8[];
extern Gfx D_8140DD18[];
extern Gfx D_8140DD38[];
extern Gfx gDL_OverlayUI[];
extern Gfx gDL_BeginUIOverlay[];
extern Gfx gDL_EndColorFill[];
extern Gfx gDL_BeginColorFill[];
extern Vtx gVtx_UI_SmallQuad[];
extern Vtx gVtx_UI_LargeQuad[];
extern Vtx gVtx_UI_TriangleSmall[];
extern Vtx gVtx_UI_TriangleLarge[];
extern Vtx gVtx_UI_MediumQuad[];
extern Vtx gMatrix_UITransform[];
extern Vtx gVtx_UI_RectHorizontal[];
extern Vtx gVtx_UI_RectVertical[];
extern Vtx gVtx_UI_TriangleDown[];
extern Vtx gVtx_UI_ColorQuad[];
extern Vtx gVtx_UI_PanelQuad[];
extern Vtx gVtx_UI_RectTall[];
extern Vtx gVtx_UI_RectWide[];
extern Vtx gVtx_UI_Square[];
extern Vtx gVtx_UI_ComplexQuad[];
extern Vtx gVtx_UI_GridQuad[];
extern Vtx gGroundQuadVtx[];
extern Vtx gFullscreenQuadVtx[];
extern Gfx gDL_PanelBackground[];
extern Gfx gDL_PanelQuad[];
extern Gfx gDL_UITransformQuad[];
extern ParticleEffectData gParticleDefaultCallback;

extern u8 gPrimColorPalette[];

extern gMatrixBufferStruct* gMatrixBuffer;
extern s32 gMatrixBufferIdx;
extern s32 gMatrixBufferIdx;
extern unk_D_8140E634 gParticleRenderContext;
extern ParticleCameraInfo* gParticleCameraInfo;
extern u32 gTimerCounter;
extern s32 gTimerMask6;
extern s32 gTimerMask5;
extern s32 gTimerMask4;
extern s32 gTimerMask3;
extern s32 gTimerMask2;
extern u32 gTimerMod3;
extern s32 gTimerMask1;
extern u32 gTimerShift6;
extern u32 gTimerShift5;
extern u32 gTimerShift4;
extern u32 gTimerShift3;
extern u32 gTimerShift2;
extern u32 gTimerDiv3;
extern u32 gTimerShift1;
extern s32 gTimerBit6;
extern s32 gTimerBit5;
extern s32 gTimerBit4;
extern s32 gTimerBit3;
extern s32 gTimerBit2;
extern s32 gTimerDiv3Parity;
extern s32 gTimerBit1;
extern s32 gRandomSeedCounter;
extern ParticleEffectInstance* gParticlePool;
extern gBattleAnimEffectSlots* gParticleDefs;
extern ParticleSpawner* gMiniFxEmitters;
extern s32 gParticlePoolIndex;
extern s32 gParticleDefNextIdx;
extern s32 gParticleEmitterNextIdx;

void ParticleMath_BitwiseOr(s32* arg0, s32 arg1);
void ParticleMath_BitwiseAndNot(s32* arg0, s32 arg1);
void ParticleMath_BitwiseXor(s32* arg0, s32 arg1);
s32 ParticleMath_HasBits(s32* arg0, s32 arg1);
s32 ParticleMath_LacksBits(s32* arg0, s32 arg1);
s32 ParticleMath_ApproachFloatUp(f32* arg0, f32 arg1, f32 arg2);
s32 ParticleMath_ApproachFloatDown(f32* arg0, f32 arg1, f32 arg2);
s32 ParticleMath_ApproachS32Up(s32* arg0, s32 arg1, s32 arg2);
s32 ParticleMath_ApproachS32Down(s32* arg0, s32 arg1, s32 arg2);
s32 ParticleMath_ApproachS16Up(s16* arg0, s16 arg1, s16 arg2);
s32 ParticleMath_ApproachU16Up(u16* arg0, u16 arg1, u16 arg2);
s32 ParticleMath_ApproachS16Down(s16* arg0, s16 arg1, s16 arg2);
s32 ParticleMath_ApproachU16Down(u16* arg0, s32 arg1, s32 arg2);
s32 ParticleMath_ApproachFloatUpByPointer(f32* arg0, f32 arg1, f32* arg2);
s32 ParticleMath_ApproachFloatDownByPointer(f32* arg0, f32 arg1, f32* arg2);
s32 ParticleMath_ApproachS32UpByPointer(s32* arg0, s32 arg1, s32* arg2);
s32 ParticleMath_ApproachS32DownByPointer(s32* arg0, s32 arg1, s32* arg2);
s32 ParticleMath_ApproachS16UpByPointer(s16* arg0, s16 arg1, s16* arg2);
s32 ParticleMath_ApproachS16DownByPointer(s16* arg0, s16 arg1, s16* arg2);
s32 ParticleMath_ApproachS8(s8* arg0, s8 arg1, s8 arg2);
s32 ParticleMath_ApproachU8(u8* arg0, u8 arg1, u8 arg2);
s32 ParticleMath_ApproachS16(s16* arg0, s16 arg1, s16 arg2);
s32 ParticleMath_ApproachAngle(s16* arg0, s16 arg1, s16 arg2);
s32 ParticleMath_ApproachS32(s32* arg0, s32 arg1, s32 arg2);
s32 ParticleMath_ApproachFloat(f32* arg0, f32 arg1, f32 arg2);
void ParticleMath_BounceFloat(f32* arg0, f32 arg1, f32 arg2, f32* arg3);
void ParticleMath_BounceS16(s16* arg0, s16 arg1, s16 arg2, s16* arg3);
void ParticleMath_CopyVec3f(Vec3f* arg0, Vec3f* arg1);
void ParticleMath_CopyVec3s(Vec3s* arg0, Vec3s* arg1);
void ParticleMath_AddVec3f(Vec3f* arg0, Vec3f* arg1);
void ParticleMath_AddVec3s(Vec3s* arg0, Vec3s* arg1);
f32 ParticleMath_DotVec3f(Vec3f arg0, Vec3f arg1);
s32 ParticleMath_IsWithinRadius2D(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4);
void ParticleMath_AdvanceRandomOffset(void);
u32 ParticleMath_RandomRange(s32 arg0);
s32 ParticleMath_RandomRangeOffset(s32 arg0, s32 arg1);
s32 ParticleMath_RandomSigned(s32 arg0);
s32 ParticleMath_RandomSignedOffset(s32 arg0, s32 arg1);
s32 ParticleMath_RandomSignedOffsetBySign(s32 arg0, s32 arg1);
void ParticleMath_NoopStub(UNUSED s32 arg0);
s16 ParticleMath_Atan2YZ(Vec3f arg0);
s16 ParticleMath_Atan2ZX(Vec3f arg0);
s16 ParticleMath_Atan2XY(Vec3f arg0);
void ParticleMath_Vec3ToAngles(Vec3s* arg0, Vec3f arg1);
f32 ParticleMath_Rotate2DX(f32 arg0, f32 arg1, s16 arg2);
f32 ParticleMath_Rotate2DY(f32 arg0, f32 arg1, s16 arg2);
Vec3f* ParticleMath_RotateVec3fY(Vec3f* arg0, Vec3f arg1, Vec3s arg4);
Vec3f* ParticleMath_MakeXZVectorFromAngle(Vec3f* arg0, f32 arg1, s16 arg2);
Vec3f* ParticleMath_RotateVec3fXY(Vec3f* arg0, Vec3f arg1, Vec3s arg4);
f32 ParticleMath_Distance3D(Vec3f arg0, Vec3f arg1);
f32 ParticleMath_DistanceXZ(Vec3f arg0, Vec3f arg1);
Vec3f* ParticleMath_NormalizedDirection(Vec3f* arg0, Vec3f arg1, Vec3f arg2);
s32 ParticleMath_DistanceScaled(Vec3f arg0, Vec3f arg1, f32 arg2);
s32 ParticleMath_ScaleDirectionToLength(Vec3f* arg0, Vec3f arg1, Vec3f arg2, f32 arg3);
Vec3f* ParticleMath_RandomDirection(Vec3f* arg0, f32 arg1);
Vec3f* ParticleMath_ScaleVec3f(Vec3f* arg0, f32 arg1);
s16 ParticleMath_AngleXBetweenPoints(Vec3f arg0, Vec3f arg1);
s16 ParticleMath_AngleYBetweenPoints(Vec3f arg0, Vec3f arg1);
s16 ParticleMath_AngleZBetweenPoints(Vec3f arg0, Vec3f arg1);
s16 ParticleMath_ApproachAngleCoarse(s16 arg0, s16 arg1);
void ParticleGfx_NoopStub1(void);
void ParticleGfx_PushMatrix(MtxF* arg0);
void ParticleGfx_Build2DTransformMatrix(MtxF* arg0, s16 arg1, s16 arg2, s16 arg3, f32 arg4);
void ParticleGfx_Build2DTransformMatrixYScaled(MtxF* arg0, s16 arg1, s16 arg2, s16 arg3, f32 arg4);
void ParticleGfx_Push2DTransform(s16 arg0, s16 arg1, s16 arg2, f32 arg3);
void ParticleGfx_Push2DTransformYScaled(s16 arg0, s16 arg1, s16 arg2, f32 arg3);
void ParticleGfx_BuildTransformMatrix(MtxF* arg0, Vec3f arg1, Vec3s arg2, f32 arg3);
void ParticleGfx_BuildTransformMatrixYScaled(MtxF* arg0, Vec3f arg1, Vec3s arg2, f32 arg3);
void ParticleGfx_BuildTransformMatrixXYScaled(MtxF* arg0, Vec3f arg1, Vec3s arg2, f32 arg3, f32 arg4);
void ParticleGfx_BuildBillboardMatrix(MtxF* arg0, MtxF* arg1, Vec3f arg2, f32 arg3);
void ParticleGfx_BuildBillboardMatrixYScaled(MtxF* arg0, MtxF* arg1, Vec3f arg2, f32 arg3);
void ParticleGfx_BuildBillboardRotatedMatrix(MtxF* arg0, MtxF* arg1, Vec3f arg2, f32 arg3, s16 arg4);
void ParticleGfx_BuildBillboardRotatedMatrixYScaled(MtxF* arg0, MtxF* arg1, Vec3f arg2, f32 arg3, s16 arg4);
void ParticleGfx_BuildDirectionMatrix(MtxF* arg0, Vec3f arg1, Vec3f arg2, s16 arg3, f32 arg4);
void ParticleGfx_PushTransformMatrix(Vec3f arg0, Vec3s arg1, f32 arg2);
void ParticleGfx_PushTransformMatrixYScaled(Vec3f arg0, Vec3s arg1, f32 arg2);
void ParticleGfx_PushTransformMatrixXYScaled(Vec3f arg0, Vec3s arg1, f32 arg2, f32 arg3);
void ParticleGfx_PushBillboardMatrix(CameraStruct* arg0, Vec3f arg1, f32 arg4);
void ParticleGfx_PushBillboardRotatedMatrix(CameraStruct* arg0, Vec3f arg1, f32 arg4, s16 arg5);
void ParticleGfx_PushBillboardMatrixYScaled(CameraStruct* arg0, Vec3f arg1, f32 arg4);
void ParticleGfx_PushBillboardRotatedMatrixYScaled(CameraStruct* arg0, Vec3f arg1, f32 arg4, s16 arg5);
void ParticleGfx_PushTransformMatrixWithHalfTurnXY(Vec3f arg0, Vec3s arg3, f32 arg5);
void ParticleGfx_PushDirectionMatrix(Vec3f arg0, Vec3f arg3, f32 arg6);


void ParticleGfx_PipeSync(void);
void ParticleGfx_SetTextureState(void);
s32 ParticleGfx_TextureSizeLog2(s32 size);
void ParticleGfx_NoopStub2(void);
void func_814024C8(void);
void func_814024D0(void);
void func_814024D8(void);
void func_814024E0(void);
void func_814024E8(void);
void func_814024F0(void);
void func_814024F8(void);
void ParticleGfx_LoadTextureBlock32(u8* texture, s32 fmt, s32 width, s32 height, s32 cms, s32 cmt, s32 masks, s32 maskt, s32 shifts, s32 shiftt);
void ParticleGfx_LoadTextureTile32(u8* texture, s32 fmt, s32 width, s32 height, s32 cms, s32 cmt, s32 masks, s32 maskt, s32 shifts, s32 shiftt);
void ParticleGfx_LoadTextureBlock16(u8* texture, s32 fmt, s32 width, s32 height, s32 cms, s32 cmt, s32 masks, s32 maskt, s32 shifts, s32 shiftt);
void ParticleGfx_LoadTextureTile16(u8* texture, s32 fmt, s32 width, s32 height, s32 cms, s32 cmt, s32 masks, s32 maskt, s32 shifts, s32 shiftt);
void ParticleGfx_LoadTextureBlock8(u8* texture, s32 fmt, s32 width, s32 height, s32 cms, s32 cmt, s32 masks, s32 maskt, s32 shifts, s32 shiftt);
void ParticleGfx_LoadTextureTile8(u8* texture, s32 fmt, s32 width, s32 height, s32 cms, s32 cmt, s32 masks, s32 maskt, s32 shifts, s32 shiftt);
void ParticleGfx_LoadTextureBlock4(u8* texture, s32 fmt, s32 width, s32 height, s32 cms, s32 cmt, s32 masks, s32 maskt, s32 shifts, s32 shiftt);
void ParticleGfx_LoadTextureTile4(u8* texture, s32 fmt, s32 width, s32 height, s32 cms, s32 cmt, s32 masks, s32 maskt, s32 shifts, s32 shiftt);
void ParticleGfx_LoadTextureMultiBlock4(u8* texture, s32 tmem, s32 rtile, s32 fmt, s32 width, s32 height, s32 cms, s32 cmt, s32 masks, s32 maskt, s32 shifts, s32 shiftt);
void ParticleGfx_LoadTextureRgba32(u8* texture, s32 width, s32 height);
void ParticleGfx_LoadTextureTileRgba32(u8* texture, s32 width, s32 height);
void ParticleGfx_LoadTextureRgba16(u8* texture, s32 width, s32 height);
void ParticleGfx_LoadTextureRgba16Dual(u8* texture1, u8* texture2, s32 width, s32 height);
void ParticleGfx_LoadTextureRgba16WrapS(u8* texture, s32 width, s32 height);
void ParticleGfx_LoadTextureRgba16WrapT(u8* texture, s32 width, s32 height);
void ParticleGfx_LoadTextureRgba16WrapST(u8* texture, s32 width, s32 height);
void ParticleGfx_LoadTextureRgba16WrapSWithMask(u8* texture, s32 width, s32 height, s32 masks);
void ParticleGfx_LoadTextureTileRgba16(u8* texture, s32 width, s32 height);
void ParticleGfx_LoadTextureIa16(u8* texture, s32 width, s32 height);
void ParticleGfx_LoadTextureTileIa16(u8* texture, s32 width, s32 height);
void ParticleGfx_LoadTextureIa8(u8* texture, s32 width, s32 height);
void ParticleGfx_LoadTextureTileIa8(u8* texture, s32 width, s32 height);
void ParticleGfx_LoadTextureIa8WrapST(u8* texture, s32 width, s32 height);
void ParticleGfx_LoadTextureI8(u8* texture, s32 width, s32 height);
void ParticleGfx_LoadTextureI8WrapST(u8* texture, s32 width, s32 height);
void ParticleGfx_LoadTextureTileI8(u8* texture, s32 width, s32 height);
void ParticleGfx_LoadTextureI8Alias(u8* texture, s32 width, s32 height);
void ParticleGfx_LoadTextureTileI8Alias(u8* texture, s32 width, s32 height);
void ParticleGfx_LoadTextureTileIa4(u8* texture, s32 width, s32 height);
void ParticleGfx_LoadTextureTileI4(u8* texture, s32 width, s32 height);
void ParticleGfx_LoadTextureIa4(u8* texture, s32 width, s32 height);
void ParticleGfx_LoadTextureI4(u8* texture, s32 width, s32 height);
void ParticleGfx_LoadTextureI4WrapST(u8* texture, s32 width, s32 height);
void ParticleGfx_LoadTextureI4Alias(u8* texture, s32 width, s32 height);
void ParticleGfx_LoadTextureTileI4Alias(u8* texture, s32 width, s32 height);
void ParticleGfx_LoadTextureI4WrapS(u8* texture, s32 width, s32 height);
void ParticleGfx_LoadTextureI4WrapSTNoMirror(u8* texture, s32 width, s32 height);
void ParticleGfx_LoadTextureI4MultiBlockWrapST(u8* texture, s32 width, s32 height);
void ParticleGfx_LoadTextureI4MultiBlockWrapSTWithShift(u8* texture, s32 width, s32 height, s32 shifts, s32 shiftt);
void ParticleGfx_LoadTextureCi8(u8* texture, s32 width, s32 height);
void ParticleGfx_LoadTextureCi8WrapSWithMask(u8* texture, s32 width, s32 height, s32 masks);
void ParticleGfx_LoadTextureTileCi8(u8* texture, s32 width, s32 height);
void ParticleGfx_LoadTextureDualRgba16I8(u8* texture1, u8* texture2, s32 width, s32 height);
void ParticleGfx_DrawQuadVertices(Vtx* arg0);
void ParticleGfx_NoopStub10(void);
void ParticleGfx_DrawTransformedQuad(Vec3f arg0, Vec3s arg1, f32 arg2, Vtx* arg3);
void ParticleGfx_DrawTransformedQuadYScaled(Vec3f arg0, Vec3s arg1, f32 arg3, Vtx* arg4);
void ParticleGfx_DrawTransformedQuadXYScaled(Vec3f arg0, Vec3s arg1, f32 arg2, f32 arg3, Vtx* arg4);
void ParticleGfx_DrawTransformedTriangle(Vec3f arg0, Vec3s arg1, f32 arg2, Vtx* arg3);
void ParticleGfx_DrawModelQuad(CameraStruct* arg0, Vec3f arg1, f32 arg2, Vtx* arg3);
void ParticleGfx_DrawModelQuadRotated(CameraStruct* arg0, Vec3f arg1, f32 arg2, Vtx* arg3, s16 arg4);
void ParticleGfx_DrawModelQuadYScaled(CameraStruct* arg0, Vec3f arg1, f32 arg2, Vtx* arg3);
void ParticleGfx_DrawModelQuadRotatedYScaled(CameraStruct* arg0, Vec3f arg1, f32 arg2, Vtx* arg3, s16 arg4);
void ParticleGfx_DrawModelTriangle(CameraStruct* arg0, Vec3f arg1, f32 arg2, Vtx* arg3);
void ParticleGfx_DrawModelTriangleRotated(CameraStruct* arg0, Vec3f arg1, f32 arg2, Vtx* arg3, s16 arg4);
void ParticleGfx_DrawI8TextureAtlas(u8* texture, Vtx* vtx, s32 arg2, s32 arg3, s32 width, s32 height);
void ParticleGfx_DrawIa16TextureAtlas(u8* texture, Vtx* vtx, s32 arg2, s32 arg3, s32 width, s32 height);
void ParticleGfx_DrawIa8TextureAtlas(u8* texture, Vtx* vtx, s32 arg2, s32 arg3, s32 width, s32 height);
void ParticleGfx_DrawI4TextureAtlas(u8* texture, Vtx* vtx, s32 arg2, s32 arg3, s32 width, s32 height);
void ParticleGfx_DrawI4TextureAtlasTiled(u8* texture, Vtx* vtx, s32 arg2, s32 arg3, s32 width, s32 height);
void ParticleGfx_SetPrimColor(u8 r, u8 g, u8 b, u8 a);
void ParticleGfx_SetEnvColor(u8 r, u8 g, u8 b, u8 a);
void ParticleGfx_SetFogColor(u8 r, u8 g, u8 b, u8 a);
void ParticleGfx_SetBlendColor(u8 r, u8 g, u8 b, u8 a);
void ParticleGfx_SetPrimColorTextureCombine(u8 r, u8 g, u8 b, u8 a);
void ParticleGfx_SetTextureAlphaCombine(u8 a);
void ParticleGfx_SetPrimEnvColorCombine(u8 prim_r, u8 prim_g, u8 prim_b, u8 env_r, u8 env_g, u8 env_b, u8 prim_a);
void ParticleGfx_SetPrimEnvNoiseCombine(u8 prim_r, u8 prim_g, u8 prim_b, u8 env_r, u8 env_g, u8 env_b, u8 prim_a);
void ParticleGfx_SetPrimEnvColorShadeCombine(u8 prim_r, u8 prim_g, u8 prim_b, u8 prim_a, u8 env_r, u8 env_g, u8 env_b, u8 env_a);
void ParticleGfx_SetPrimEnvLodCombine(u8 l, u8 prim_r, u8 prim_g, u8 prim_b, u8 prim_a, u8 env_r, u8 env_g, u8 env_b);
void ParticleGfx_SetPrimEnvLodTextureCombine(u8 l, u8 prim_r, u8 prim_g, u8 prim_b, u8 prim_a, u8 env_r, u8 env_g, u8 env_b);
u32 ParticleGfx_GetFrameDivisor(s32 arg0);
void ParticleGfx_SetAnimatedTileSize(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void ParticleGfx_SetAnimatedAuxTileSize(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void ParticleGfx_SetAnimatedTileSizeOnList(Gfx* gfx, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void ParticleGfx_SetAnimatedAuxTileSizeOnList(Gfx* gfx, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void ParticleGfx_SetPartiallyAnimatedTileSize(Gfx* gfx, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void ParticleGfx_SetPartiallyAnimatedAuxTileSize(Gfx* gfx, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void ParticleGfx_SetFrameIndexedTileSize(Gfx* gfx, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7);
void ParticleGfx_SetFrameIndexedAuxTileSize(Gfx* gfx, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7);
void ParticleGfx_LoadTextureI4ToList(Gfx* gfx, u8* texture, s32 width, s32 height);
Gfx* ParticleGfx_LoadDescriptorTexture(Gfx* arg0, u8* texture, arg1_func_81407874_014_004* arg2, s32 tmem, s32 rtile);
Gfx* ParticleGfx_LoadDescriptorTextureAndTile(Gfx* arg0, arg1_func_81407874_014_004* arg1, s32 tmem, s32 rtile);
Gfx* ParticleGfx_LoadPrimaryDescriptorTexture(Gfx* arg0, arg1_func_81407874_014* arg1);
Gfx* ParticleGfx_LoadSecondaryDescriptorTexture(Gfx* arg0, arg1_func_81407874_014* arg1);
void ParticleGfx_SetCombineModeFromDescriptor(Gfx* arg0, arg1_func_81407874_014_000_010* arg1);
Gfx* Gfx_ApplyTextureState(Gfx* arg0, arg1_func_81407874_014* arg1);
void ParticleGfx_GraphNodeBuildDescriptorMaterialList(s32 arg0, ColorLerpHook* arg1);


void Particle_ResetDefaults(ParticleEffectInstance* arg0);
ParticleEffectInstance* Particle_Alloc(void);
void Particle_Free(ParticleEffectInstance* arg0);
ParticleEffectInstance* Particle_New(void);
ParticleEffectInstance* Particle_AllocChain(u8 arg0);
void Particle_EmitBurstAtTransform(f32 arg0, Vec3f arg1, Vec3s arg2, func_unk_D_8140E724_008 arg3, ParticleEffectData* arg4, s16 arg5);
void Particle_EmitBurstAtTransformWithMetadata(f32 arg0, Vec3f arg1, Vec3s arg2, func_unk_D_8140E724_008 arg3, ParticleEffectData* arg4, s16 arg5, s16 arg6);
void Particle_EmitBurstFromObject(Fragment2_1GraphNode* arg0, func_unk_D_8140E724_008 arg1, ParticleEffectData* arg2, s16 arg3, s16 arg4);
void Particle_EmitBurstFromObjectWithMetadata(Fragment2_1GraphNode* arg0, func_unk_D_8140E724_008 arg1, ParticleEffectData* arg2, s16 arg3, s16 arg4, s16 arg5);
s32 Particle_CountActive(void);
s32 Particle_CountActiveAlias(void);
void Particle_InitLifecycle(ParticleEffectInstance* arg0);
void Particle_MarkInactive(ParticleEffectInstance* arg0);
void Particle_DisableAndDetach(ParticleEffectInstance* arg0);
s32 Particle_IsInactive(ParticleEffectInstance* arg0);
s32 Particle_IsRunning(ParticleEffectInstance* arg0);
void Particle_AdvanceLifecycle(ParticleEffectInstance* arg0);
s32 Particle_TickDelayTimer(ParticleEffectInstance* arg0, s16 arg1);
s32 Particle_TickDelayAndAdvanceLifecycle(ParticleEffectInstance* arg0, s16 arg1);
void Particle_SetFlags(ParticleEffectInstance* arg0, s32 arg1);
void Particle_ClearFlags(ParticleEffectInstance* arg0, s32 arg1);
void Particle_ToggleFlags(ParticleEffectInstance* arg0, s32 arg1);
s32 Particle_HasFlags(ParticleEffectInstance* arg0, s32 arg1);
s32 Particle_LacksFlags(ParticleEffectInstance* arg0, s32 arg1);
void Particle_EnableRendering(ParticleEffectInstance* arg0);
void Particle_DisableRendering(ParticleEffectInstance* arg0);
s32 Particle_IsRenderingEnabled(ParticleEffectInstance* arg0);
void Particle_EnableFlag40(ParticleEffectInstance* arg0);
void Particle_DisableFlag40(ParticleEffectInstance* arg0);
void Particle_HasFlag40(ParticleEffectInstance* arg0);
void Particle_SetTextureFrame(ParticleEffectInstance* arg0, s16 arg1);
s32 Particle_AnimateFramesForward(ParticleEffectInstance* arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5);
s32 Particle_AnimateFramesForwardAndAdvanceLifecycle(ParticleEffectInstance* arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5);
s32 Particle_AnimateFramesReverse(ParticleEffectInstance* arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5);
s32 Particle_AnimateFramesReverseAndAdvanceLifecycle(ParticleEffectInstance* arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5);
s32 Particle_AnimateFramesPingPong(ParticleEffectInstance* arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5);
s32 Particle_AnimateFramesPingPongAndAdvanceLifecycle(ParticleEffectInstance* arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5);
s32 Particle_AnimateFramesReverseFirstPingPong(ParticleEffectInstance* arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5);
s32 Particle_AnimateFramesReverseFirstPingPongAndAdvanceLifecycle(ParticleEffectInstance* arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5);
void Particle_BeginPhase(ParticleEffectInstance* arg0);
void Particle_ResetPhase(ParticleEffectInstance* arg0);
void Particle_AdvancePhase(ParticleEffectInstance* arg0);
s32 Particle_TickPhaseTimer(ParticleEffectInstance* arg0, s16 arg1);
void Particle_UpdateWorldTransform(ParticleEffectInstance* arg0);
void Particle_SetVelocityScaledXYZ(ParticleEffectInstance* arg0, f32 arg1, f32 arg2, f32 arg3);
void Particle_SetVelocityScaledVec(ParticleEffectInstance* arg0, Vec3f arg1);
void Particle_SetVelocityDirectXYZ(ParticleEffectInstance* arg0, f32 arg1, f32 arg2, f32 arg3);
void Particle_SetVelocityXScaled(ParticleEffectInstance* arg0, f32 arg1);
void Particle_SetVelocityYScaled(ParticleEffectInstance* arg0, f32 arg1);
void Particle_SetVelocityZScaled(ParticleEffectInstance* arg0, f32 arg1);
void Particle_SetPositionFromRotationTemplate1(ParticleEffectInstance* arg0, f32 arg1);
void Particle_SetPositionFromRotationTemplate2(ParticleEffectInstance* arg0, f32 arg1);
void Particle_AddVelocityScaledVec(ParticleEffectInstance* arg0, Vec3f arg1);
void Particle_AddVelocityDirectVec(ParticleEffectInstance* arg0, Vec3f arg1);
void Particle_AddVelocityScaledXYZ(ParticleEffectInstance* arg0, f32 arg1, f32 arg2, f32 arg3);
void Particle_AddVelocityXScaled(ParticleEffectInstance* arg0, f32 arg1);
void Particle_AddVelocityYScaled(ParticleEffectInstance* arg0, f32 arg1);
void Particle_AddVelocityZScaled(ParticleEffectInstance* arg0, f32 arg1);
void Particle_AddVelocityForward(ParticleEffectInstance* arg0, f32 arg1);
void Particle_AddVelocityBackward(ParticleEffectInstance* arg0, f32 arg1);
void Particle_AddVelocityRight(ParticleEffectInstance* arg0, f32 arg1);
void Particle_AddVelocityLeft(ParticleEffectInstance* arg0, f32 arg1);
void Particle_AddVelocityFromDirVector(ParticleEffectInstance* arg0, f32 arg1);
void Particle_AddPositionFromRotationTemplate1(ParticleEffectInstance* arg0, f32 arg1);
void Particle_AddPositionFromRotationTemplate2(ParticleEffectInstance* arg0, f32 arg1);
void Particle_AddPositionRotatedVectorByYaw(ParticleEffectInstance* arg0, Vec3f arg1);
void Particle_SetRandomVelocityX(ParticleEffectInstance* arg0, s32 arg1);
void Particle_SetRandomVelocityY(ParticleEffectInstance* arg0, s32 arg1);
void Particle_SetRandomVelocityZ(ParticleEffectInstance* arg0, s32 arg1);
void Particle_SetRandomVelocityXOffset(ParticleEffectInstance* arg0, s32 arg1, s32 arg2);
void Particle_SetRandomVelocityYOffset(ParticleEffectInstance* arg0, s32 arg1, s32 arg2);
void Particle_SetRandomVelocityZOffset(ParticleEffectInstance* arg0, s32 arg1, s32 arg2);
void Particle_SetRandomVelocityXSymmetric(ParticleEffectInstance* arg0, s32 arg1, s32 arg2);
void Particle_SetRandomVelocityYSymmetric(ParticleEffectInstance* arg0, s32 arg1, s32 arg2);
void Particle_SetRandomVelocityZSymmetric(ParticleEffectInstance* arg0, s32 arg1, s32 arg2);
void Particle_SetRandomVelocityXYZ(ParticleEffectInstance* arg0, s32 arg1, s32 arg2, s32 arg3);
void Particle_SetRandomModVelocityXYZ(ParticleEffectInstance* arg0, s32 arg1, s32 arg2, s32 arg3);
void Particle_SetRandomRotatedVelocityXY(ParticleEffectInstance* arg0, s32 arg1, s32 arg2);
void Particle_AddRandomVelocityXYZ(ParticleEffectInstance* arg0, s32 arg1, s32 arg2, s32 arg3);
void Particle_SetOrigin(ParticleEffectInstance* arg0, f32 arg1, f32 arg2, f32 arg3);
void Particle_SetVelocity(ParticleEffectInstance* arg0, f32 arg1, f32 arg2, f32 arg3);
void Particle_SetVelocityX(ParticleEffectInstance* arg0, f32 arg1);
void Particle_SetVelocityY(ParticleEffectInstance* arg0, f32 arg1);
void Particle_SetVelocityZ(ParticleEffectInstance* arg0, f32 arg1);
void Particle_SetVelocityRandomDirection(ParticleEffectInstance* arg0, f32 arg1);
void Particle_AddVelocity(ParticleEffectInstance* arg0, f32 arg1, f32 arg2, f32 arg3);
void Particle_AddScaledVelocityX(ParticleEffectInstance* arg0, f32 arg1);
void Particle_AddScaledVelocityY(ParticleEffectInstance* arg0, f32 arg1);
void Particle_AddScaledVelocityZ(ParticleEffectInstance* arg0, f32 arg1);
void Particle_SubtractScaledVelocityXYZ(ParticleEffectInstance* arg0, f32 arg1, f32 arg2, f32 arg3);
void Particle_SubtractScaledVelocityX(ParticleEffectInstance* arg0, f32 arg1);
void Particle_SubtractScaledVelocityY(ParticleEffectInstance* arg0, f32 arg1);
void Particle_SubtractScaledVelocityZ(ParticleEffectInstance* arg0, f32 arg1);
s32 Particle_ApproachVelocityX(ParticleEffectInstance* arg0, f32 arg1);
s32 Particle_ApproachVelocityY(ParticleEffectInstance* arg0, f32 arg1);
s32 Particle_ApproachVelocityZ(ParticleEffectInstance* arg0, f32 arg1);
void Particle_CopyVelocityFromTarget(ParticleEffectInstance* arg0);
void Particle_CopyVelocityXZFromTarget(ParticleEffectInstance* arg0);
void Particle_CopyVelocityXYFromTarget(ParticleEffectInstance* arg0);
void Particle_AddVelocityFromTarget(ParticleEffectInstance* arg0);
void Particle_AddVelocityXZFromTarget(ParticleEffectInstance* arg0);
void Particle_AddVelocityXYFromTarget(ParticleEffectInstance* arg0);
void Particle_AddVelocityXFromTarget(ParticleEffectInstance* arg0);
void Particle_AddVelocityYFromTarget(ParticleEffectInstance* arg0);
void Particle_AddVelocityZFromTarget(ParticleEffectInstance* arg0);
void Particle_ApplyB278AndCopyXZ(ParticleEffectInstance* arg0);
void Particle_AddVelocityXZFromRotationYViaImpulse(ParticleEffectInstance* arg0);
void Particle_AddVelocityXYFromRotationZViaImpulse(ParticleEffectInstance* arg0);
void Particle_AddVelocityFromRotationTemplate1(ParticleEffectInstance* arg0);
void Particle_AddVelocityFromRotationTemplate2(ParticleEffectInstance* arg0);
void Particle_AddVelocityFromRotationTemplate3(ParticleEffectInstance* arg0);
void Particle_AddVelocityFromRotationTemplate4(ParticleEffectInstance* arg0);
void Particle_AddVelocityFromRotationTemplate5(ParticleEffectInstance* arg0);
void Particle_AddVelocityFromRotationTemplate6(ParticleEffectInstance* arg0);
void Particle_AddVelocityFromRotationTemplate7A(ParticleEffectInstance* arg0);
void Particle_AddVelocityFromRotationTemplate7B(ParticleEffectInstance* arg0);
void Particle_AddVelocityXZFromRotationY(ParticleEffectInstance* arg0);
void Particle_AddVelocityXZFromRotationYPlusHalfTurn(ParticleEffectInstance* arg0);
void Particle_AddVelocityXZFromRotationYPlusHalfTurnFromArgument(ParticleEffectInstance* arg0, f32 arg1);
void Particle_AddVelocityYFromFieldOffset74(ParticleEffectInstance* arg0);
s32 Particle_FallAndCheckGround(ParticleEffectInstance* arg0);
s32 Particle_FallAccelerateAndCheckGround(ParticleEffectInstance* arg0);
void Particle_SetVelocityTarget(ParticleEffectInstance* arg0, f32 arg1, f32 arg2, f32 arg3);
void Particle_Field5C_SetXScaled_0A07C(ParticleEffectInstance* arg0, f32 arg1);
void Particle_Field5C_SetYScaled_0A094(ParticleEffectInstance* arg0, f32 arg1);
void Particle_Field5C_SetZScaled_0A0AC(ParticleEffectInstance* arg0, f32 arg1);
s32 Particle_Field5C_ApproachY_0A0C4(ParticleEffectInstance* arg0, f32 arg1, f32 arg2);
f32 ParticleMath_ScaleApproachStep(f32 arg0);
void Particle_ApproachPosition(ParticleEffectInstance* arg0, Vec3f arg1);
void Particle_SetRotationFromVec3s(ParticleEffectInstance* arg0, Vec3s arg1);
void Particle_SetRotation(ParticleEffectInstance* arg0, s16 arg1, s16 arg2, s16 arg3);
void Particle_SetRotationX(ParticleEffectInstance* arg0, s16 arg1);
void Particle_SetRotationY(ParticleEffectInstance* arg0, s16 arg1);
void Particle_SetRotationZ(ParticleEffectInstance* arg0, s16 arg1);
void Particle_AddRotationAllAxes(ParticleEffectInstance* arg0);
void Particle_AddRotationX(ParticleEffectInstance* arg0);
void Particle_AddRotationY(ParticleEffectInstance* arg0);
void Particle_AddRotationZ(ParticleEffectInstance* arg0);
void Particle_SetRotationSpeed(ParticleEffectInstance* arg0, s16 arg1, s16 arg2, s16 arg3);
void Particle_SetRotationDeltaFromVec3s(ParticleEffectInstance* arg0, Vec3s arg1);
void Particle_SetRotationDeltaXY(ParticleEffectInstance* arg0, s16 arg1, s16 arg2);
void Particle_SetRotationDeltaX(ParticleEffectInstance* arg0, s16 arg1);
void Particle_SetRotationDeltaY(ParticleEffectInstance* arg0, s16 arg1);
void Particle_SetRotationDeltaZ(ParticleEffectInstance* arg0, s16 arg1);
void Particle_SetTargetRotationX(ParticleEffectInstance* arg0, s16 arg1);
void Particle_SetTargetRotationY(ParticleEffectInstance* arg0, s16 arg1);
void Particle_SetRotationTargetXY(ParticleEffectInstance* arg0, s16 arg1, s16 arg2);
void Particle_SetRotationTargetFromCurrent(ParticleEffectInstance* arg0);
void Particle_AddRotationDelta(ParticleEffectInstance* arg0);
void Particle_AddRotationDeltaX(ParticleEffectInstance* arg0);
void Particle_AddRotationDeltaY(ParticleEffectInstance* arg0);
void Particle_AddRotationDeltaZ(ParticleEffectInstance* arg0);
void Particle_AddRotationDeltaVec(ParticleEffectInstance* arg0, Vec3s arg1);
void Particle_AddRotationDeltaXYZ(ParticleEffectInstance* arg0, s16 arg1, s16 arg2, s16 arg3);
void Particle_Field94_AddX_0A578(ParticleEffectInstance* arg0, s16 arg1);
void Particle_RotateY(ParticleEffectInstance* arg0, s16 arg1);
void Particle_Field94_AddZ_0A5B0(ParticleEffectInstance* arg0, s16 arg1);
void Particle_AddRotationTargetXY(ParticleEffectInstance* arg0, s16 arg1, s16 arg2);
void Particle_SubtractRotationDeltaVec(ParticleEffectInstance* arg0, Vec3s arg1);
void Particle_SubtractRotationDeltaX(ParticleEffectInstance* arg0, s16 arg1);
void Particle_SubtractRotationDeltaY(ParticleEffectInstance* arg0, s16 arg1);
void Particle_SubtractRotationDeltaZ(ParticleEffectInstance* arg0, s16 arg1);
void Particle_ApproachRotationTargetX(ParticleEffectInstance* arg0);
void Particle_ApproachRotationTargetY(ParticleEffectInstance* arg0);
void Particle_ApproachRotationTargetZ(ParticleEffectInstance* arg0);
void Particle_ApproachRotationTargetXY(ParticleEffectInstance* arg0);
void Particle_ApproachRotationTargetXYZ(ParticleEffectInstance* arg0);
void Particle_ApproachRotationXTo(ParticleEffectInstance* arg0, s16 arg1, s16 arg2);
void Particle_ApproachRotationYTo(ParticleEffectInstance* arg0, s16 arg1, s16 arg2);
s32 Particle_DecreaseRotationXTowards(ParticleEffectInstance* arg0, s32 arg1, s32 arg2);
s32 Particle_DecreaseRotationYTowards(ParticleEffectInstance* arg0, s32 arg1, s32 arg2);
s32 Particle_DecreaseRotationZTowards(ParticleEffectInstance* arg0, s32 arg1, s32 arg2);
void Particle_AddRotationRandomSignedXY(ParticleEffectInstance* arg0, s32 arg1, s32 arg2);
void Particle_AddRotationRandomSignedXYWithXHalfTurn(ParticleEffectInstance* arg0, s32 arg1, s32 arg2);
void Particle_AddRotationRandomSignedY(ParticleEffectInstance* arg0, s32 arg1);
void Particle_AddRotationRandomSignedYWithHalfTurn(ParticleEffectInstance* arg0, s32 arg1);
void Particle_AddRotationRandomSignedXWithFixedYQuarterTurn(ParticleEffectInstance* arg0);
void Particle_ComputeVectorFromRotationY(ParticleEffectInstance* arg0, f32 arg1, Vec3f* arg2);
void Particle_ComputeVectorFromRotationXY(ParticleEffectInstance* arg0, f32 arg1, Vec3f* arg2);
void Particle_ComputeVectorFromRotationXZ(ParticleEffectInstance* arg0, f32 arg1, Vec3f* arg2);
void Particle_ComputeVectorFromRotationXYZAlt(ParticleEffectInstance* arg0, f32 arg1, Vec3f* arg2);
void Particle_ComputeVectorFromRotationYZVariant(ParticleEffectInstance* arg0, f32 arg1, Vec3f* arg2);
void Particle_SetSpeed(ParticleEffectInstance* arg0, f32 arg1);
void Particle_SetAcceleration(ParticleEffectInstance* arg0, f32 arg1);
s32 Particle_ApproachSpeedScaled(ParticleEffectInstance* arg0, f32 arg1, f32 arg2);
s32 Particle_ApproachSpeed(ParticleEffectInstance* arg0, f32 arg1);
s32 Particle_ApproachAcceleration(ParticleEffectInstance* arg0, f32 arg1, f32 arg2);
void Particle_Field7C_SetVecScaled_0AE84(ParticleEffectInstance* arg0, Vec3f arg1);
void Particle_SetVelocityImpulse(ParticleEffectInstance* arg0, f32 arg1, f32 arg2, f32 arg3);
void Particle_Field7C_SetXScaled_0AF0C(ParticleEffectInstance* arg0, f32 arg1);
void Particle_Field7C_SetYScaled_0AF24(ParticleEffectInstance* arg0, f32 arg1);
void Particle_Field7C_SetZScaled_0AF3C(ParticleEffectInstance* arg0, f32 arg1);
s32 Particle_Field7C_IncrementXUntilAtLeast_0AF54(ParticleEffectInstance* arg0, f32 arg1, f32 arg2);
s32 Particle_Field7C_IncrementYUntilAtLeast_0AFA8(ParticleEffectInstance* arg0, f32 arg1, f32 arg2);
s32 Particle_Field7C_IncrementZUntilAtLeast_0AFFC(ParticleEffectInstance* arg0, f32 arg1, f32 arg2);
s32 Particle_Field7C_DecrementXUntilAtMost_0B050(ParticleEffectInstance* arg0, f32 arg1, f32 arg2);
s32 Particle_Field7C_DecrementYUntilAtMost_0B0A4(ParticleEffectInstance* arg0, f32 arg1, f32 arg2);
s32 Particle_Field7C_DecrementZUntilAtMost_0B0F8(ParticleEffectInstance* arg0, f32 arg1, f32 arg2);
void Particle_Field7C_ScaleVec_0B14C(ParticleEffectInstance* arg0, f32 arg1);
s32 Particle_Field7C_ApproachY_0B180(ParticleEffectInstance* arg0, f32 arg1, f32 arg2);
void Particle_Field7C_SetYFromField74AngleX_0B1C4(ParticleEffectInstance* arg0);
void Particle_Field7C_SetXFromField74AngleY_0B1EC(ParticleEffectInstance* arg0);
void Particle_Field7C_SetZFromField74AngleY_0B214(ParticleEffectInstance* arg0);
void Particle_Field7C_SetXYFromField74AngleZ_0B23C(ParticleEffectInstance* arg0);
void Particle_Field7C_SetXZFromField74AngleY_0B278(ParticleEffectInstance* arg0);
void Particle_Field7C_SetVecFromField74AnglesXY_0B2B4(ParticleEffectInstance* arg0);
void Particle_Field7C_SetVecFromField74AnglesXZ_0B330(ParticleEffectInstance* arg0);
void Particle_Field7C_SetVecFromField74AnglesXYAlt_0B3AC(ParticleEffectInstance* arg0);
void Particle_Field7C_SetVecFromField74AnglesYZ_0B42C(ParticleEffectInstance* arg0);
void Particle_Field7C_SetVecFromField74AnglesXYZ_0B4A0(ParticleEffectInstance* arg0);
void Particle_Field7C_SetVecFromField74AnglesXYZAlt_0B568(ParticleEffectInstance* arg0);
void Particle_Field7C_SetVecFromField74AnglesYZAlt_0B638(ParticleEffectInstance* arg0);
void Particle_Field7C_SetVecFromField74AnglesYZVariant_0B700(ParticleEffectInstance* arg0);
void Particle_UpdateRotatingVelocityXZ(ParticleEffectInstance* arg0, f32 arg1, s16 arg2);
s32 Particle_Field50_AdvanceField7CWithTimer_0B854(ParticleEffectInstance* arg0, f32 arg1, f32 arg2, f32 arg3, s16 arg4, s16 arg5);
void Particle_SetScaleFactor1(ParticleEffectInstance* arg0, f32 arg1);
void Particle_SetScale(ParticleEffectInstance* arg0, f32 arg1);
void Particle_SetScaleSpeed(ParticleEffectInstance* arg0, f32 arg1);
void Particle_SetScaleTarget(ParticleEffectInstance* arg0, f32 arg1);
s32 Particle_ApproachScaleFactor1(ParticleEffectInstance* arg0, f32 arg1, f32 arg2);
s32 Particle_ApproachScaleFactor1WithCallback(ParticleEffectInstance* arg0, f32 arg1, f32 arg2);
s32 Particle_ApproachScaleFactor2(ParticleEffectInstance* arg0);
s32 Particle_ApproachScaleFactor2WithCallback(ParticleEffectInstance* arg0);
s32 Particle_Field20_Approach_0BA84(ParticleEffectInstance* arg0, f32 arg1, f32 arg2);
void Particle_SetPrimColor(ParticleEffectInstance* arg0, u8 arg1, u8 arg2, u8 arg3);
s32 Particle_PrimR_Approach_0BAE4(ParticleEffectInstance* arg0, u8 arg1, u8 arg2);
s32 Particle_PrimG_Approach_0BB14(ParticleEffectInstance* arg0, u8 arg1, u8 arg2);
s32 Particle_PrimB_Approach_0BB44(ParticleEffectInstance* arg0, u8 arg1, u8 arg2);
void Particle_SetEnvColor(ParticleEffectInstance* arg0, u8 arg1, u8 arg2, u8 arg3);
s32 Particle_EnvR_Approach_0BB90(ParticleEffectInstance* arg0, u8 arg1, u8 arg2);
s32 Particle_EnvB_Approach_0BBC0(ParticleEffectInstance* arg0, u8 arg1, u8 arg2);
s32 Particle_EnvG_Approach_0BBF0(ParticleEffectInstance* arg0, u8 arg1, u8 arg2);
void Particle_SetPrimAlpha(ParticleEffectInstance* arg0, u8 arg1);
s32 Particle_PrimAlpha_Approach_0BC2C(ParticleEffectInstance* arg0, u8 arg1, u8 arg2);
s32 Particle_PrimAlpha_ApproachAndStepState_0BC5C(ParticleEffectInstance* arg0, u8 arg1, u8 arg2);
void Particle_SetTimerA6(ParticleEffectInstance* arg0, s16 arg1);
s16 Particle_GetTimerA6(ParticleEffectInstance* arg0);
s32 Particle_DecrementTimerA6Clamp(ParticleEffectInstance* arg0, s16 arg1, s16 arg2);
s32 Particle_DecrementTimerA6By(ParticleEffectInstance* arg0, s16 arg1);
s32 Particle_DecrementTimerA6ByWithCallback(ParticleEffectInstance* arg0, s16 arg1);
s32 Particle_DecrementTimerA6To(ParticleEffectInstance* arg0, s16 arg1);
s32 Particle_DecrementTimerA6ToZero(ParticleEffectInstance* arg0);
s32 Particle_DecrementTimerA6ToZeroWithCallback(ParticleEffectInstance* arg0);
void Particle_SetTimerA8(ParticleEffectInstance* arg0, s16 arg1);
s16 Particle_GetTimerA8(ParticleEffectInstance* arg0);
s32 Particle_DecrementTimerA8Clamp(ParticleEffectInstance* arg0, s16 arg1);
s32 Particle_DecrementTimerA8ToZero(ParticleEffectInstance* arg0);
s32 Particle_DecrementTimerA8ToZeroWithCallback(ParticleEffectInstance* arg0);
void Particle_FieldCA_SetU8_0BECC(ParticleEffectInstance* arg0, u8 arg1);
void Particle_FieldAC_SetS16_0BED8(ParticleEffectInstance* arg0, s16 arg1);
void Particle_FieldCF_SetU8_0BEEC(ParticleEffectInstance* arg0, u8 arg1);
void Particle_FieldCF_SetU8Alt_0BEF8(ParticleEffectInstance* arg0, u8 arg1);
void Particle_FieldCC_SetU8_0BF04(ParticleEffectInstance* arg0, u8 arg1);
void Particle_FieldAA_SetS16_0BF10(ParticleEffectInstance* arg0, s16 arg1);
void Particle_FieldCE_SetS16_0BF24(ParticleEffectInstance* arg0, s16 arg1);
void Particle_FieldCD_SetS16_0BF38(ParticleEffectInstance* arg0, s16 arg1);
void Particle_FieldAE_SetS16_0BF4C(ParticleEffectInstance* arg0, s16 arg1);
s32 Particle_FieldAE_Approach_0BF60(ParticleEffectInstance* arg0, s16 arg1, s16 arg2);
s32 Particle_FieldAE_ApproachAndStepState_0BF98(ParticleEffectInstance* arg0, s16 arg1, s16 arg2);
void Particle_FieldB0_SetS16_0BFEC(ParticleEffectInstance* arg0, s16 arg1);
s32 Particle_FieldB0_Approach_0C000(ParticleEffectInstance* arg0, s16 arg1, s16 arg2);
s16 Particle_FieldAC_GetS16_0C038(ParticleEffectInstance* arg0);
s32 Particle_FieldCE_GetS32_0C040(ParticleEffectInstance* arg0);
u8 Particle_FieldCD_GetU8_0C048(ParticleEffectInstance* arg0);
s16 Particle_FieldAE_GetS16_0C050(ParticleEffectInstance* arg0);
s16 Particle_FieldCF_GetS16_0C058(ParticleEffectInstance* arg0);
s16 Particle_FieldAA_GetS16_0C068(ParticleEffectInstance* arg0);
void Particle_SetFieldOffsetACIfNotSentinel(ParticleEffectInstance* arg0, s16 arg1);
void Particle_SetFieldOffsetCFIfNotSentinel(ParticleEffectInstance* arg0, u8 arg1);
void Particle_SetFieldOffsetA6IfNotSentinel(ParticleEffectInstance* arg0, s16 arg1);
void Particle_SetFieldOffsetA8IfNotSentinel(ParticleEffectInstance* arg0, s16 arg1);
void Particle_SetFieldOffsetCEIfNotSentinel(ParticleEffectInstance* arg0, u8 arg1);
void Particle_SetFieldOffsetCDIfNotSentinel(ParticleEffectInstance* arg0, u8 arg1);
void Particle_SetFieldOffsetAAIfNotSentinel(ParticleEffectInstance* arg0, s16 arg1);
void Particle_SetPrimAlphaIfNotSentinel(ParticleEffectInstance* arg0, u8 arg1);
void Particle_SetFieldOffsetAEIfNotSentinel(ParticleEffectInstance* arg0, s16 arg1);
void Particle_SetFieldOffsetB0IfNotSentinel(ParticleEffectInstance* arg0, s16 arg1);
void Particle_RenderWorldChains(CameraStruct* arg0);
void Particle_RenderOrthoParticles(CameraStruct* arg0);
void Particle_SetRenderMode(s16 arg0);
void Particle_InvokeRenderSetup(ParticleEffectInstance* arg0, ParticleRenderSettings* arg1);
void Particle_PrepareRender(ParticleEffectInstance* arg0);
void Particle_DispatchDraw(ParticleEffectInstance* arg0, CameraStruct* arg1);
void Particle_NoopDraw(UNUSED ParticleEffectInstance* arg0, UNUSED CameraStruct* arg1);


void Particle_UpdateFrameCounters(void);
void Particle_UpdateFrameCountersAlias(void);


void ParticleGfx_LoadTextureCallbackRgba16_32x32(UNUSED ParticleEffectInstance* arg0, u8* texture);
void ParticleGfx_LoadTextureCallbackIa8Frame_32x32(ParticleEffectInstance* arg0, u8* texture);
void ParticleGfx_LoadTextureCallbackIa8_32x32(UNUSED ParticleEffectInstance* arg0, u8* texture);
void ParticleGfx_LoadTextureCallbackIa8Frame_32x64(ParticleEffectInstance* arg0, u8* texture);
void ParticleGfx_LoadTextureCallbackI4_32x32(UNUSED ParticleEffectInstance* arg0, u8* texture);
void ParticleGfx_LoadTextureCallbackI4ParticleFrame_32x32(ParticleEffectInstance* arg0, u8* texture);
void ParticleGfx_LoadTextureCallbackI4FrameMod4_32x32(UNUSED ParticleEffectInstance* arg0, u8* texture);
void ParticleGfx_LoadTextureCallbackI4FrameDiv2Mod4_32x32(UNUSED ParticleEffectInstance* arg0, u8* texture);
void ParticleGfx_LoadTextureCallbackI4FrameDiv4Mod4_32x32(UNUSED ParticleEffectInstance* arg0, u8* texture);
void ParticleGfx_LoadTextureCallbackI4FrameDiv2Mod8_32x32(UNUSED ParticleEffectInstance* arg0, u8* texture);
void ParticleGfx_LoadTextureCallbackI4TileFrameDiv2Mod8_24x24(UNUSED ParticleEffectInstance* arg0, u8* texture);
void ParticleGfx_LoadTextureCallbackI4TileParticleFrame_24x24(ParticleEffectInstance* arg0, u8* texture);
void ParticleGfx_LoadTextureCallbackI4FrameMod10_32x64(UNUSED ParticleEffectInstance* arg0, u8* texture);
void ParticleGfx_LoadTextureCallbackI4ParticleFrame_32x64(ParticleEffectInstance* arg0, u8* texture);
void ParticleGfx_LoadTextureCallbackI4_64x64(UNUSED ParticleEffectInstance* arg0, u8* texture);
void ParticleGfx_LoadTextureCallbackI4FrameMod8_64x64(UNUSED ParticleEffectInstance* arg0, u8* texture);
void ParticleGfx_LoadTextureCallbackI4FrameDiv2Mod8_64x64(UNUSED ParticleEffectInstance* arg0, u8* texture);
void ParticleGfx_LoadTextureCallbackI4ParticleFrame_64x64(ParticleEffectInstance* arg0, u8* texture);
void ParticleGfx_LoadTextureCallbackI4WrapST_64x64(UNUSED ParticleEffectInstance* arg0, u8* texture);
void ParticleGfx_LoadTextureCallbackIa8WrapST_64x64(UNUSED ParticleEffectInstance* arg0, u8* texture);
void ParticleGfx_DrawBillboardPrim(ParticleEffectInstance* arg0, CameraStruct* arg1);
void ParticleGfx_DrawBillboardPrimEnv(ParticleEffectInstance* arg0, CameraStruct* arg1);
s32 ParticleGfx_DrawBillboardDoubleSided(ParticleEffectInstance* arg0, UNUSED CameraStruct* arg1);
void ParticleGfx_DrawBillboardDefaultQuad(ParticleEffectInstance* arg0, CameraStruct* arg1);
void ParticleGfx_DrawBillboardPrimEnvQuad(ParticleEffectInstance* arg0, CameraStruct* arg1);
void ParticleGfx_DrawBillboardTextureAlphaRotatedQuad(ParticleEffectInstance* arg0, CameraStruct* arg1);
void ParticleGfx_DrawBillboardOffsetQuad(ParticleEffectInstance* arg0, CameraStruct* arg1);
void ParticleGfx_DrawBillboardPrimEnvNoiseQuad(ParticleEffectInstance* arg0, CameraStruct* arg1);
void ParticleGfx_DrawBillboardPrimEnvRotatedQuad(ParticleEffectInstance* arg0, CameraStruct* arg1);
void ParticleGfx_DrawBillboardPrimEnvRotatedTriangle(ParticleEffectInstance* arg0, CameraStruct* arg1);
void ParticleGfx_DrawBillboardPrimEnvQuadVariantA(ParticleEffectInstance* arg0, CameraStruct* arg1);
void ParticleGfx_DrawBillboardPrimEnvQuadVariantB(ParticleEffectInstance* arg0, CameraStruct* arg1);
void ParticleGfx_DrawBillboardPrimEnvQuadVariantC(ParticleEffectInstance* arg0, CameraStruct* arg1);
void ParticleGfx_DrawBillboardPrimEnvComposite(ParticleEffectInstance* arg0, CameraStruct* arg1);
s32 ParticleGfx_DrawBillboardPrimEnvTriangleDoubleSided(ParticleEffectInstance* arg0, UNUSED CameraStruct* arg1);
void ParticleGfx_DrawBillboardPrimEnvTransformedQuad(ParticleEffectInstance* arg0, CameraStruct* arg1);
void ParticleGfx_CopyPaletteRgb(u8* arg0, u16 arg1);
void ParticleGfx_CopyPalettePairRgb(u8* arg0, u8* arg1, u16 arg2);
void ParticleGfx_RecolorPrim(ParticleEffectInstance* arg0, u16 arg1);
void ParticleGfx_RecolorEnv(ParticleEffectInstance* arg0, u16 arg1);
void ParticleGfx_RecolorPrimEnvFromPalettePair(ParticleEffectInstance* arg0, u16 arg1);
void ParticleGfx_RecolorPrimFromPaletteSetA(ParticleEffectInstance* arg0, s16 arg1);
void ParticleGfx_RecolorEnvFromPaletteSetA(ParticleEffectInstance* arg0, s16 arg1);
void ParticleGfx_RecolorPrimFromPaletteSetB(ParticleEffectInstance* arg0, s16 arg1);
void ParticleGfx_RecolorEnvFromPaletteSetB(ParticleEffectInstance* arg0, s16 arg1);
void ParticleGfx_RecolorPrimEnvFromPaletteSetA(ParticleEffectInstance* arg0, s16 arg1);
void ParticleGfx_RecolorPrimEnvFromPaletteSetB(ParticleEffectInstance* arg0, s16 arg1);
void ParticleGfx_RecolorPrimRandomPalette(ParticleEffectInstance* arg0);
void ParticleGfx_RecolorEnvRandomPalette(ParticleEffectInstance* arg0);
s32 ParticleGfx_ApproachPrimPalette(ParticleEffectInstance* arg0, u16 arg1, u8 arg2);
s32 ParticleGfx_ApproachEnvPalette(ParticleEffectInstance* arg0, u16 arg1, u8 arg2);
s32 ParticleGfx_ApproachPrimEnvPalettePair(ParticleEffectInstance* arg0, u16 arg1, u8 arg2);

#endif // _FRAGMENT34_H_
