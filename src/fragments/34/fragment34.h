#ifndef _FRAGMENT34_H_
#define _FRAGMENT34_H_

#include "global.h"

struct ParticleEffectInstance;
struct unk_D_8140E728_01C_004_1;
struct unk_D_84390010;
struct unk_D_8140E724;

typedef void (*func_unk_D_8140E724_008)(struct ParticleEffectInstance*);
typedef void (*func_unk_D_8140E724_00C)(struct ParticleEffectInstance*, CameraStruct*);
typedef void (*unk_D_8140E728_01C_004_1_04)(struct ParticleEffectInstance*, s32, struct unk_D_8140E728_01C_004_1*);
typedef void (*unk_D_8140E728_01C_004_1_08)(struct ParticleEffectInstance*, s32, struct unk_D_8140E728_01C_004_1*);

typedef struct unk_D_8140E728_01C_00C_1 {
    /* 0x00 */ s32 arg;
} unk_D_8140E728_01C_00C_1;

typedef union unk_D_8140E728_01C_00C {
    s32 arg;
    unk_D_8140E728_01C_00C_1* s;
} unk_D_8140E728_01C_00C;

typedef struct unk_D_8140E728_01C_004_1 {
    /* 0x00 */ u8 unk_00;
    /* 0x00 */ u8 unk_01;
    /* 0x00 */ s16 unk_02;
    /* 0x04 */ unk_D_8140E728_01C_004_1_04 unk_04;
    /* 0x08 */ unk_D_8140E728_01C_004_1_08 unk_08;
    /* 0x0C */ unk_D_8140E728_01C_00C unk_0C;
} unk_D_8140E728_01C_004_1; // size = 0x10

typedef union unk_D_8140E728_01C_004 {
    unk_D_8140E728_01C_004_1* a;
    func_unk_D_8140E724_00C func;
} unk_D_8140E728_01C_004;

typedef struct unk_D_8140E728_01C {
    /* 0x00 */ s32 unk_00; /* unk_04: 1 = a, 3 = func */
    /* 0x04 */ unk_D_8140E728_01C_004 unk_04;
} unk_D_8140E728_01C; // size = 0x08

typedef struct unk_D_8140E728 {
    /* 0x00 */ f32 unk_00;
    /* 0x04 */ Vec3f unk_04;
    /* 0x10 */ Vec3s unk_10;
    /* 0x18 */ func_unk_D_8140E724_008 unk_18;
    /* 0x1C */ unk_D_8140E728_01C* unk_1C;
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
} unk_D_8140E728; // size = 0x30

typedef struct ParticleEffectInstance {
    /* 0x00 */ struct ParticleEffectInstance* next;
    /* 0x04 */ struct ParticleEffectInstance* prev;
    /* 0x08 */ func_unk_D_8140E724_008 unk_08;
    /* 0x0C */ unk_D_8140E728_01C* unk_0C;
    /* 0x10 */ struct unk_D_84390010* unk_10;
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
    /* 0x9A */ Vec3s unk_9A;
    /* 0xA0 */ Vec3s unk_A0;
    /* 0xA6 */ s16 unk_A6;
    /* 0xA8 */ s16 unk_A8;
    /* 0xAA */ s16 unk_AA;
    /* 0xAC */ s16 unk_AC;
    /* 0xAE */ s16 unk_AE;
    /* 0xB0 */ s16 unk_B0;
    /* 0xB2 */ s16 unk_B2;
    /* 0xB4 */ char unkB4[0x2];
    /* 0xB6 */ s16 unk_B6;
    /* 0xB8 */ s16 unk_B8;
    /* 0xBA */ s16 unk_BA;
    /* 0xBC */ s16 unk_BC;
    /* 0xBE */ u8 prim_r;
    /* 0xBF */ u8 prim_g;
    /* 0xC0 */ u8 prim_b;
    /* 0xC1 */ u8 env_r;
    /* 0xC2 */ u8 env_g;
    /* 0xC3 */ u8 env_b;
    /* 0xC4 */ u8 prim_a;
    /* 0xC5 */ char unkC5[0x1];
    /* 0xC6 */ s8 unk_C6;
    /* 0xC7 */ s8 unk_C7;
    /* 0xC8 */ char unkC8[0x2];
    /* 0xCA */ u8 unk_CA;
    /* 0xCB */ u8 unk_CB;
    /* 0xCC */ u8 unk_CC;
    /* 0xCD */ u8 unk_CD;
    /* 0xCE */ u8 unk_CE;
    /* 0xCF */ u8 unk_CF;
    /* 0xD0 */ s8 unk_D0;
} ParticleEffectInstance; // size = 0xD4

typedef void (*func_unk_D_8140E724)(struct ParticleEffectInstance*);

typedef struct unk_D_8140E724 {
    /* 0x00 */ func_unk_D_8140E724 unk_00;
    /* 0x04 */ unk_D_8140E728_01C* unk_04;
    /* 0x08 */ struct unk_D_84390010* unk_08;
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
} unk_D_8140E724; // size = 0x1C

typedef struct arg1_func_87903D64_014 {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ ColorLerpEntry5* unk_04;
    /* 0x08 */ ColorLerpEntry5* unk_08;
    /* 0x0C */ ColorLerpEntry5* unk_0C;
    /* 0x10 */ ColorLerpEntry4* unk_10;
    /* 0x14 */ ColorLerpEntry4* unk_14;
    /* 0x18 */ ColorLerpEntry4* unk_18;
} arg1_func_87903D64_014; // size = 0x1C

// Possibly unk_D_86002F34_alt7, unk_D_86002F34_alt8,
// unk_D_86002F34_alt9 or unk_D_86002F34_alt2
typedef struct arg1_func_87903D64 {
    /* 0x00 */ char unk00[0x14];
    /* 0x14 */ arg1_func_87903D64_014* unk_14;
    /* 0x18 */ Gfx* unk_18;
} arg1_func_87903D64; // size >= 0x1C

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
    /* 0x00 */ arg1_func_81407874_014_000_014_000 unk_00;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
} arg1_func_81407874_014_000_014; // size >= 0x08

typedef struct arg1_func_81407874_014_000_01C {
    /* 0x00 */ u16 unk_00;
    /* 0x02 */ u16 unk_02;
} arg1_func_81407874_014_000_01C; // size >= 0x04

typedef struct arg1_func_81407874_014_000 {
    /* 0x00 */ struct arg1_func_81407874_014_000* unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ char unk08[0x8];
    /* 0x10 */ arg1_func_81407874_014_000_010* unk_10;
    /* 0x14 */ arg1_func_81407874_014_000_014* unk_14;
    /* 0x18 */ arg1_func_81407874_014_000_014* unk_18;
    /* 0x1C */ arg1_func_81407874_014_000_01C* unk_1C;
} arg1_func_81407874_014_000; // size >= 0x20

typedef struct arg1_func_81407874_014_004_008 {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s16 unk_04;
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
    /* 0x00 */ arg1_func_81407874_014_000* unk_00;
    /* 0x04 */ arg1_func_81407874_014_004_004* unk_04;
    /* 0x08 */ arg1_func_81407874_014_004_008* unk_08;
    /* 0x0C */ arg1_func_81407874_014_000_014* unk_0C;
} arg1_func_81407874_014_004; // size >= 0x4

typedef struct arg1_func_81407874_014 {
    /* 0x00 */ arg1_func_81407874_014_000* unk_00;
    /* 0x04 */ arg1_func_81407874_014_004* unk_04;
} arg1_func_81407874_014; // size >= 0x8

typedef struct arg1_func_81407874 {
    /* 0x00 */ char unk00[0x14];
    /* 0x00 */ arg1_func_81407874_014* unk_14;
} arg1_func_81407874; // size >= 0x18

typedef struct unk_D_8140E634_010 {
    /* 0x00 */ MtxF unk_00;
    /* 0x40 */ Vec3f unk_40;
    /* 0x4C */ Vec3f unk_4C;
    /* 0x58 */ Vec3f unk_58;
    /* 0x64 */ Vec3f unk_64;
    /* 0x70 */ s16 unk_70;
    /* 0x72 */ s16 unk_72;
    /* 0x74 */ char unk74[0x2];
    /* 0x76 */ s16 unk_76;
    /* 0x78 */ s16 unk_78;
} unk_D_8140E634_010; // size = 0x7C

typedef struct unk_D_8140E634 {
    /* 0x00 */ Vec3f unk_00;
    /* 0x0C */ CameraStruct* unk_0C;
    /* 0x10 */ unk_D_8140E634_010 unk_10;
} unk_D_8140E634; // size = 0x8C

typedef struct unk_D_8140E620 {
    /* 0x0000 */ MtxF unk_0000[364];
    /* 0x5B00 */ char unk5B00[0x80];
    /* 0x5B80 */ Mtx unk_5B80;
    /* 0x5BC0 */ char unk5BC0[0x20];
} unk_D_8140E620; // size = 0x5BE0

extern Gfx D_8140DAE0[];
extern Gfx D_8140DB30[];
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
extern Gfx D_8140DD78[];
extern Gfx D_8140DDD8[];
extern Gfx D_8140DDF8[];
extern Vtx D_8140DE78[];
extern Vtx D_8140DEF8[];
extern Vtx D_8140DF78[];
extern Vtx D_8140DFA8[];
extern Vtx D_8140DFD8[];
extern Vtx gMatrix_UITransform[];
extern Vtx D_8140E058[];
extern Vtx D_8140E098[];
extern Vtx D_8140E0D8[];
extern Vtx D_8140E108[];
extern Vtx D_8140E148[];
extern Vtx D_8140E178[];
extern Vtx D_8140E1B8[];
extern Vtx D_8140E1F8[];
extern Vtx D_8140E238[];
extern Vtx D_8140E2B8[];
extern Vtx D_8140E378[];
extern Vtx D_8140E3B8[];
extern Gfx gDL_PanelBackground[];
extern Gfx D_8140E430[];
extern Gfx D_8140E448[];
extern unk_D_8140E728_01C gParticleDefaultCallback;

extern u8 gPrimColorPalette[];

extern unk_D_8140E620* gMatrixBuffer;
extern s32 gMatrixBufferIdx;
extern s32 gMatrixBufferIdx;
extern unk_D_8140E634 gParticleScaleFactor;
extern unk_D_8140E634_010* D_8140E6B4;
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
extern u32 D_8140E6EC;
extern u32 D_8140E6F0;
extern s32 D_8140E6F4;
extern s32 D_8140E6F8;
extern s32 D_8140E6FC;
extern s32 D_8140E700;
extern s32 D_8140E704;
extern s32 D_8140E708;
extern s32 D_8140E70C;
extern s32 gRandomSeedCounter;
extern ParticleEffectInstance* gParticleInstances;
extern unk_D_8140E724* D_8140E724;
extern unk_D_8140E728* gParticleEmitters;
extern s32 gParticleAllocIndex;
extern s32 D_8140E730;
extern s32 gParticleEmitterNextIdx;

void SetBits(s32* arg0, s32 arg1);
void ClearBits(s32* arg0, s32 arg1);
void ToggleBits(s32* arg0, s32 arg1);
s32 IsBitSet(s32* arg0, s32 arg1);
s32 IsBitClear(s32* arg0, s32 arg1);
s32 ApproachFloatUp(f32* arg0, f32 arg1, f32 arg2);
s32 ApproachFloatDown(f32* arg0, f32 arg1, f32 arg2);
s32 ApproachIntUp(s32* arg0, s32 arg1, s32 arg2);
s32 ApproachIntDown(s32* arg0, s32 arg1, s32 arg2);
s32 ApproachS16Up(s16* arg0, s16 arg1, s16 arg2);
s32 ApproachU16Up(u16* arg0, u16 arg1, u16 arg2);
s32 ApproachS16Down(s16* arg0, s16 arg1, s16 arg2);
s32 ApproachU16Down(u16* arg0, s32 arg1, s32 arg2);
s32 ApproachFloatUpPtr(f32* arg0, f32 arg1, f32* arg2);
s32 ApproachFloatDownPtr(f32* arg0, f32 arg1, f32* arg2);
s32 ApproachS32UpPtr(s32* arg0, s32 arg1, s32* arg2);
s32 ApproachS32DownPtr(s32* arg0, s32 arg1, s32* arg2);
s32 ApproachS16UpPtr(s16* arg0, s16 arg1, s16* arg2);
s32 ApproachS16DownPtr(s16* arg0, s16 arg1, s16* arg2);
s32 ApproachS8(s8* arg0, s8 arg1, s8 arg2);
s32 ApproachU8(u8* arg0, u8 arg1, u8 arg2);
s32 ApproachS16Signed(s16* arg0, s16 arg1, s16 arg2);
s32 ApproachU16Wrap(s16* arg0, s16 arg1, s16 arg2);
s32 ApproachS32(s32* arg0, s32 arg1, s32 arg2);
s32 ApproachF32(f32* arg0, f32 arg1, f32 arg2);
void BounceFloat(f32* arg0, f32 arg1, f32 arg2, f32* arg3);
void func_814008B0(s16* arg0, s16 arg1, s16 arg2, s16* arg3);
void Vec3f_Copy(Vec3f* arg0, Vec3f* arg1);
void func_8140094C(Vec3s* arg0, Vec3s* arg1);
void func_81400968(Vec3f* arg0, Vec3f* arg1);
void func_8140099C(Vec3s* arg0, Vec3s* arg1);
f32 Vec3f_Dot(Vec3f arg0, Vec3f arg1);
s32 IsWithinRadius2D(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4);
void func_81400A60(void);
u32 RandomMod(s32 arg0);
s32 func_81400ADC(s32 arg0, s32 arg1);
s32 RandomRangeSigned(s32 arg0);
s32 func_81400B28(s32 arg0, s32 arg1);
s32 func_81400B4C(s32 arg0, s32 arg1);
void func_81400B84(UNUSED s32 arg0);
s16 func_81400B8C(Vec3f arg0);
s16 func_81400BBC(Vec3f arg0);
s16 func_81400BEC(Vec3f arg0);
void Vec3f_ToAngles(Vec3s* arg0, Vec3f arg1);
f32 func_81400C80(f32 arg0, f32 arg1, s16 arg2);
f32 func_81400CC0(f32 arg0, f32 arg1, s16 arg2);
Vec3f* func_81400D00(Vec3f* arg0, Vec3f arg1, Vec3s arg4);
Vec3f* func_81400D6C(Vec3f* arg0, f32 arg1, s16 arg2);
Vec3f* func_81400DC0(Vec3f* arg0, Vec3f arg1, Vec3s arg4);
f32 func_81400E8C(Vec3f arg0, Vec3f arg1);
f32 func_81400EF0(Vec3f arg0, Vec3f arg1);
Vec3f* func_81400F44(Vec3f* arg0, Vec3f arg1, Vec3f arg2);
s32 func_81400FA4(Vec3f arg0, Vec3f arg1, f32 arg2);
s32 Particle_ComputeLifespan(Vec3f* arg0, Vec3f arg1, Vec3f arg2, f32 arg3);
Vec3f* func_814010D8(Vec3f* arg0, f32 arg1);
Vec3f* func_81401168(Vec3f* arg0, f32 arg1);
s16 func_8140119C(Vec3f arg0, Vec3f arg1);
s16 func_814011E0(Vec3f arg0, Vec3f arg1);
s16 func_81401224(Vec3f arg0, Vec3f arg1);
s16 func_81401268(s16 arg0, s16 arg1);
void func_8140138C(void);
void func_81401394(MtxF* arg0);
void func_81401430(MtxF* arg0, s16 arg1, s16 arg2, s16 arg3, f32 arg4);
void func_814014E8(MtxF* arg0, s16 arg1, s16 arg2, s16 arg3, f32 arg4);
void func_814015A0(s16 arg0, s16 arg1, s16 arg2, f32 arg3);
void func_814015F8(s16 arg0, s16 arg1, s16 arg2, f32 arg3);
void func_81401650(MtxF* arg0, Vec3f arg1, Vec3s arg2, f32 arg3);
void func_814017E0(MtxF* arg0, Vec3f arg1, Vec3s arg2, f32 arg3);
void func_81401940(MtxF* arg0, Vec3f arg1, Vec3s arg2, f32 arg3, f32 arg4);
void func_81401ABC(MtxF* arg0, MtxF* arg1, Vec3f arg2, f32 arg3);
void func_81401B6C(MtxF* arg0, MtxF* arg1, Vec3f arg2, f32 arg3);
void func_81401C04(MtxF* arg0, MtxF* arg1, Vec3f arg2, f32 arg3, s16 arg4);
void func_81401D50(MtxF* arg0, MtxF* arg1, Vec3f arg2, f32 arg3, s16 arg4);
void func_81401E84(MtxF* arg0, Vec3f arg1, Vec3f arg2, s16 arg3, f32 arg4);
void func_81401FC0(Vec3f arg0, Vec3s arg1, f32 arg2);
void func_8140203C(Vec3f arg0, Vec3s arg1, f32 arg2);
void func_814020B8(Vec3f arg0, Vec3s arg1, f32 arg2, f32 arg3);
void func_8140213C(CameraStruct* arg0, Vec3f arg1, f32 arg4);
void func_814021A4(CameraStruct* arg0, Vec3f arg1, f32 arg4, s16 arg5);
void func_81402214(CameraStruct* arg0, Vec3f arg1, f32 arg4);
void func_8140227C(CameraStruct* arg0, Vec3f arg1, f32 arg4, s16 arg5);
void func_814022EC(Vec3f arg0, Vec3s arg3, f32 arg5);
void func_8140238C(Vec3f arg0, Vec3f arg3, f32 arg6);


void Gfx_PipeSync(void);
void Gfx_SetCycle1_NoTexture(void);
s32 GetLog2(s32 size);
void func_814024C0(void);
void func_814024C8(void);
void func_814024D0(void);
void func_814024D8(void);
void func_814024E0(void);
void func_814024E8(void);
void func_814024F0(void);
void func_814024F8(void);
void Gfx_LoadTextureBlockRGBA32(u8* texture, s32 fmt, s32 width, s32 height, s32 cms, s32 cmt, s32 masks, s32 maskt, s32 shifts, s32 shiftt);
void Gfx_LoadTextureTileRGBA32(u8* texture, s32 fmt, s32 width, s32 height, s32 cms, s32 cmt, s32 masks, s32 maskt, s32 shifts, s32 shiftt);
void Gfx_LoadTextureBlockRGBA16(u8* texture, s32 fmt, s32 width, s32 height, s32 cms, s32 cmt, s32 masks, s32 maskt, s32 shifts, s32 shiftt);
void Gfx_LoadTextureTileRGBA16(u8* texture, s32 fmt, s32 width, s32 height, s32 cms, s32 cmt, s32 masks, s32 maskt, s32 shifts, s32 shiftt);
void Gfx_LoadTextureBlockIA8(u8* texture, s32 fmt, s32 width, s32 height, s32 cms, s32 cmt, s32 masks, s32 maskt, s32 shifts, s32 shiftt);
void Gfx_LoadTextureTileIA8(u8* texture, s32 fmt, s32 width, s32 height, s32 cms, s32 cmt, s32 masks, s32 maskt, s32 shifts, s32 shiftt);
void Gfx_LoadTextureBlock4b(u8* texture, s32 fmt, s32 width, s32 height, s32 cms, s32 cmt, s32 masks, s32 maskt, s32 shifts, s32 shiftt);
void Gfx_LoadTextureTile4b(u8* texture, s32 fmt, s32 width, s32 height, s32 cms, s32 cmt, s32 masks, s32 maskt, s32 shifts, s32 shiftt);
void Gfx_LoadMultiBlock4b(u8* texture, s32 tmem, s32 rtile, s32 fmt, s32 width, s32 height, s32 cms, s32 cmt, s32 masks, s32 maskt, s32 shifts, s32 shiftt);
void Gfx_LoadTextureBlockRGBA32_Clamp(u8* texture, s32 width, s32 height);
void Gfx_LoadTextureTileRGBA32_Clamp(u8* texture, s32 width, s32 height);
void Gfx_LoadTextureBlockRGBA16_Clamp(u8* texture, s32 width, s32 height);
void Gfx_LoadMultiTextureRGBA16(u8* texture1, u8* texture2, s32 width, s32 height);
void Gfx_LoadTextureBlockRGBA16_MirrorWrapS(u8* texture, s32 width, s32 height);
void Gfx_LoadTextureBlockRGBA16_MirrorWrapT(u8* texture, s32 width, s32 height);
void Gfx_LoadTextureBlockRGBA16_MirrorWrapST(u8* texture, s32 width, s32 height);
void Gfx_LoadTextureBlockRGBA16_MaskS(u8* texture, s32 width, s32 height, s32 masks);
void func_81403EA8(u8* texture, s32 width, s32 height);
void func_81403EF4(u8* texture, s32 width, s32 height);
void func_81403F40(u8* texture, s32 width, s32 height);
void Gfx_LoadTextureBlockIA8_Clamp(u8* texture, s32 width, s32 height);
void func_81403FD8(u8* texture, s32 width, s32 height);
void func_81404024(u8* texture, s32 width, s32 height);
void Gfx_LoadTextureBlockI_Clamp(u8* texture, s32 width, s32 height);
void Gfx_LoadTextureBlockI_MirrorWrap(u8* texture, s32 width, s32 height);
void func_81404150(u8* texture, s32 width, s32 height);
void func_8140419C(u8* texture, s32 width, s32 height);
void func_814041BC(u8* texture, s32 width, s32 height);
void func_814041DC(u8* texture, s32 width, s32 height);
void func_81404228(u8* texture, s32 width, s32 height);
void func_81404274(u8* texture, s32 width, s32 height);
void func_814042C0(u8* texture, s32 width, s32 height);
void func_8140430C(u8* texture, s32 width, s32 height);
void func_8140437C(u8* texture, s32 width, s32 height);
void func_8140439C(u8* texture, s32 width, s32 height);
void func_814043BC(u8* texture, s32 width, s32 height);
void func_8140441C(u8* texture, s32 width, s32 height);
void func_81404484(u8* texture, s32 width, s32 height);
void func_814044FC(u8* texture, s32 width, s32 height, s32 shifts, s32 shiftt);
void Gfx_LoadTextureBlockCI_Clamp(u8* texture, s32 width, s32 height);
void func_814045CC(u8* texture, s32 width, s32 height, s32 masks);
void func_81404624(u8* texture, s32 width, s32 height);
void Gfx_SetupMultiTextureCI_RGBA16(u8* texture1, u8* texture2, s32 width, s32 height);
void func_81404A6C(Vtx* arg0);
void func_81404AB4(void);
void func_81404ABC(Vec3f arg0, Vec3s arg1, f32 arg2, Vtx* arg3);
void func_81404B78(Vec3f arg0, Vec3s arg1, f32 arg3, Vtx* arg4);
void func_81404C34(Vec3f arg0, Vec3s arg1, f32 arg2, f32 arg3, Vtx* arg4);
void func_81404CF8(Vec3f arg0, Vec3s arg1, f32 arg2, Vtx* arg3);
void func_81404DB4(CameraStruct* arg0, Vec3f arg1, f32 arg2, Vtx* arg3);
void func_81404E4C(CameraStruct* arg0, Vec3f arg1, f32 arg2, Vtx* arg3, s16 arg4);
void func_81404EEC(CameraStruct* arg0, Vec3f arg1, f32 arg2, Vtx* arg3);
void func_81404F84(CameraStruct* arg0, Vec3f arg1, f32 arg2, Vtx* arg3, s16 arg4);
void func_81405024(CameraStruct* arg0, Vec3f arg1, f32 arg2, Vtx* arg3);
void func_814050BC(CameraStruct* arg0, Vec3f arg1, f32 arg2, Vtx* arg3, s16 arg4);
void func_8140515C(u8* texture, Vtx* vtx, s32 arg2, s32 arg3, s32 width, s32 height);
void func_81405308(u8* texture, Vtx* vtx, s32 arg2, s32 arg3, s32 width, s32 height);
void func_814054B4(u8* texture, Vtx* vtx, s32 arg2, s32 arg3, s32 width, s32 height);
void func_81405660(u8* texture, Vtx* vtx, s32 arg2, s32 arg3, s32 width, s32 height);
void func_81405814(u8* texture, Vtx* vtx, s32 arg2, s32 arg3, s32 width, s32 height);
void Gfx_SetPrimColor(u8 r, u8 g, u8 b, u8 a);
void Gfx_SetEnvColor(u8 r, u8 g, u8 b, u8 a);
void Gfx_SetFogColor(u8 r, u8 g, u8 b, u8 a);
void func_81405B00(u8 r, u8 g, u8 b, u8 a);
void Gfx_SetPrimColorCombinePrimitive(u8 r, u8 g, u8 b, u8 a);
void func_81405C04(u8 a);
void func_81405C70(u8 prim_r, u8 prim_g, u8 prim_b, u8 env_r, u8 env_g, u8 env_b, u8 prim_a);
void func_81405D38(u8 prim_r, u8 prim_g, u8 prim_b, u8 env_r, u8 env_g, u8 env_b, u8 prim_a);
void func_81405E04(u8 prim_r, u8 prim_g, u8 prim_b, u8 prim_a, u8 env_r, u8 env_g, u8 env_b, u8 env_a);
void func_81405ED8(u8 l, u8 prim_r, u8 prim_g, u8 prim_b, u8 prim_a, u8 env_r, u8 env_g, u8 env_b);
void func_81405FAC(u8 l, u8 prim_r, u8 prim_g, u8 prim_b, u8 prim_a, u8 env_r, u8 env_g, u8 env_b);
u32 GetTileSizeByIndex(s32 arg0);
void func_814060D4(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_81406168(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_81406204(Gfx* gfx, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void func_81406288(Gfx* gfx, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void func_81406314(Gfx* gfx, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void func_81406388(Gfx* gfx, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void func_81406404(Gfx* gfx, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7);
void func_814064B0(Gfx* gfx, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7);
void func_8140679C(Gfx* gfx, u8* texture, s32 width, s32 height);
Gfx* func_814067F0(Gfx* arg0, u8* texture, arg1_func_81407874_014_004* arg2, s32 tmem, s32 rtile);
Gfx* func_814072B0(Gfx* arg0, arg1_func_81407874_014_004* arg1, s32 tmem, s32 rtile);
Gfx* func_81407410(Gfx* arg0, arg1_func_81407874_014* arg1);
Gfx* func_8140743C(Gfx* arg0, arg1_func_81407874_014* arg1);
void func_81407484(Gfx* arg0, arg1_func_81407874_014_000_010* arg1);
Gfx* func_81407590(Gfx* arg0, arg1_func_81407874_014* arg1);
void func_81407874(s32 arg0, arg1_func_87903D64* arg1);


void Particle_ResetDefaults(ParticleEffectInstance* arg0);
ParticleEffectInstance* Particle_Allocate(void);
void Particle_Free(ParticleEffectInstance* arg0);
ParticleEffectInstance* Particle_AllocateInstance(void);
ParticleEffectInstance* Particle_AllocateChain(u8 arg0);
void Particle_CreateMultiple(f32 arg0, Vec3f arg1, Vec3s arg2, func_unk_D_8140E724_008 arg3, unk_D_8140E728_01C* arg4, s16 arg5);
void Particle_CreateMultipleWithExtra(f32 arg0, Vec3f arg1, Vec3s arg2, func_unk_D_8140E724_008 arg3, unk_D_8140E728_01C* arg4, s16 arg5, s16 arg6);
void Particle_CreateFromEntityMultiple(Fragment2_1GraphNode* arg0, func_unk_D_8140E724_008 arg1, unk_D_8140E728_01C* arg2, s16 arg3, s16 arg4);
void Particle_CreateFromEntityMultipleWithExtra(Fragment2_1GraphNode* arg0, func_unk_D_8140E724_008 arg1, unk_D_8140E728_01C* arg2, s16 arg3, s16 arg4, s16 arg5);
s32 Particle_CountActive(void);
s32 Particle_GetActiveCount(void);
void Particle_Init(ParticleEffectInstance* arg0);
void Particle_ClearActiveFlag(ParticleEffectInstance* arg0);
void Particle_ResetState(ParticleEffectInstance* arg0);
s32 Particle_IsInactive(ParticleEffectInstance* arg0);
s32 Particle_IsActive(ParticleEffectInstance* arg0);
void Particle_IncrementState(ParticleEffectInstance* arg0);
s32 Particle_StartTimer80(ParticleEffectInstance* arg0, s16 arg1);
s32 Particle_ProcessTimer80(ParticleEffectInstance* arg0, s16 arg1);
void Particle_SetFlag(ParticleEffectInstance* arg0, s32 arg1);
void Particle_ClearFlag(ParticleEffectInstance* arg0, s32 arg1);
void Particle_ToggleFlag(ParticleEffectInstance* arg0, s32 arg1);
s32 Particle_HasFlag(ParticleEffectInstance* arg0, s32 arg1);
s32 Particle_CanSetFlag(ParticleEffectInstance* arg0, s32 arg1);
void Particle_EnableFlag4(ParticleEffectInstance* arg0);
void Particle_DisableFlag4(ParticleEffectInstance* arg0);
s32 Particle_HasFlag4(ParticleEffectInstance* arg0);
void Particle_EnableFlag40(ParticleEffectInstance* arg0);
void Particle_DisableFlag40(ParticleEffectInstance* arg0);
void Particle_HasFlag40(ParticleEffectInstance* arg0);
void Particle_SetParamC7(ParticleEffectInstance* arg0, s16 arg1);
s32 Particle_AnimLoopForward(ParticleEffectInstance* arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5);
s32 Particle_AnimLoopForwardComplete(ParticleEffectInstance* arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5);
s32 Particle_AnimLoopBackward(ParticleEffectInstance* arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5);
s32 Particle_AnimLoopBackwardComplete(ParticleEffectInstance* arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5);
s32 Particle_AnimPingPong(ParticleEffectInstance* arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5);
s32 Particle_AnimPingPongComplete(ParticleEffectInstance* arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5);
s32 Particle_AnimReversePingPong(ParticleEffectInstance* arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5);
s32 Particle_AnimReversePingPongComplete(ParticleEffectInstance* arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5);
void Particle_EnableFlag2(ParticleEffectInstance* arg0);
void Particle_DisableFlag2(ParticleEffectInstance* arg0);
void Particle_IncrementFlag2Counter(ParticleEffectInstance* arg0);
s32 Particle_StartTimer2(ParticleEffectInstance* arg0, s16 arg1);
void Particle_UpdateTransform(ParticleEffectInstance* arg0);
void Particle_SetVelocityScaledXYZ(ParticleEffectInstance* arg0, f32 arg1, f32 arg2, f32 arg3);
void Particle_SetVelocityScaledVec(ParticleEffectInstance* arg0, Vec3f arg1);
void Particle_SetVelocityDirectXYZ(ParticleEffectInstance* arg0, f32 arg1, f32 arg2, f32 arg3);
void Particle_SetVelocityXScaled(ParticleEffectInstance* arg0, f32 arg1);
void Particle_SetVelocityYScaled(ParticleEffectInstance* arg0, f32 arg1);
void Particle_SetVelocityZScaled(ParticleEffectInstance* arg0, f32 arg1);
void Particle_SetVelocityFromComplexDir(ParticleEffectInstance* arg0, f32 arg1);
void Particle_SetVelocityFromAnotherDir(ParticleEffectInstance* arg0, f32 arg1);
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
void Particle_AddComplexDirection(ParticleEffectInstance* arg0, f32 arg1);
void Particle_AddAnotherDirection(ParticleEffectInstance* arg0, f32 arg1);
void Particle_AddRotatedOffset(ParticleEffectInstance* arg0, Vec3f arg1);
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
void Particle_SetPosition(ParticleEffectInstance* arg0, f32 arg1, f32 arg2, f32 arg3);
void Particle_SetVelocityScaled(ParticleEffectInstance* arg0, f32 arg1, f32 arg2, f32 arg3);
void Particle_SetVelocityX(ParticleEffectInstance* arg0, f32 arg1);
void Particle_SetVelocityY(ParticleEffectInstance* arg0, f32 arg1);
void Particle_SetVelocityZ(ParticleEffectInstance* arg0, f32 arg1);
void Particle_ScaleVelocity(ParticleEffectInstance* arg0, f32 arg1);
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
void Particle_ApplyB278AndCopyXZAlt(ParticleEffectInstance* arg0);
void Particle_ApplyB23CAndCopyXY(ParticleEffectInstance* arg0);
void Particle_ApplyB2B4AndAddAll(ParticleEffectInstance* arg0);
void Particle_ApplyB330AndAddAll(ParticleEffectInstance* arg0);
void Particle_ApplyB3ACAndAddAll(ParticleEffectInstance* arg0);
void Particle_ApplyB42CAndAddAll(ParticleEffectInstance* arg0);
void Particle_ApplyB568AndAddAll(ParticleEffectInstance* arg0);
void Particle_ApplyB4A0AndAddAll(ParticleEffectInstance* arg0);
void Particle_ApplyB638AndAddAll(ParticleEffectInstance* arg0);
void Particle_ApplyB638AndAddAllAlt(ParticleEffectInstance* arg0);
void Particle_SetTargetVelocityForward(ParticleEffectInstance* arg0);
void Particle_SetTargetVelocityBackward(ParticleEffectInstance* arg0);
void Particle_SetTargetVelocityCustom(ParticleEffectInstance* arg0, f32 arg1);
void Particle_SetTargetVelocityY(ParticleEffectInstance* arg0);
s32 Particle_FallAndCheckGround(ParticleEffectInstance* arg0);
s32 Particle_FallAccelerateAndCheckGround(ParticleEffectInstance* arg0);
void Particle_SetAccelerationScaled(ParticleEffectInstance* arg0, f32 arg1, f32 arg2, f32 arg3);
void Particle_SetAccelerationXScaled(ParticleEffectInstance* arg0, f32 arg1);
void Particle_SetAccelerationYScaled(ParticleEffectInstance* arg0, f32 arg1);
void Particle_SetAccelerationZScaled(ParticleEffectInstance* arg0, f32 arg1);
s32 Particle_ApproachAccelerationY(ParticleEffectInstance* arg0, f32 arg1, f32 arg2);
f32 Particle_ScaleFactor40Percent(f32 arg0);
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
void Particle_SetRotationDelta(ParticleEffectInstance* arg0, s16 arg1, s16 arg2, s16 arg3);
void Particle_SetRotationDeltaFromVec3s(ParticleEffectInstance* arg0, Vec3s arg1);
void Particle_SetRotationDeltaXY(ParticleEffectInstance* arg0, s16 arg1, s16 arg2);
void Particle_SetRotationDeltaX(ParticleEffectInstance* arg0, s16 arg1);
void Particle_SetRotationDeltaY(ParticleEffectInstance* arg0, s16 arg1);
void Particle_SetRotationDeltaZ(ParticleEffectInstance* arg0, s16 arg1);
void Particle_SetTargetRotationX(ParticleEffectInstance* arg0, s16 arg1);
void Particle_SetTargetRotationY(ParticleEffectInstance* arg0, s16 arg1);
void Particle_SetTargetRotationXY(ParticleEffectInstance* arg0, s16 arg1, s16 arg2);
void Particle_CopyRotationToTarget(ParticleEffectInstance* arg0);
void Particle_AddRotationDelta(ParticleEffectInstance* arg0);
void Particle_AddRotationDeltaX(ParticleEffectInstance* arg0);
void Particle_AddRotationDeltaY(ParticleEffectInstance* arg0);
void Particle_AddRotationDeltaZ(ParticleEffectInstance* arg0);
void Particle_AddRotationDeltaVec(ParticleEffectInstance* arg0, Vec3s arg1);
void Particle_AddRotationDeltaXYZ(ParticleEffectInstance* arg0, s16 arg1, s16 arg2, s16 arg3);
void func_8140A578(ParticleEffectInstance* arg0, s16 arg1);
void func_8140A594(ParticleEffectInstance* arg0, s16 arg1);
void func_8140A5B0(ParticleEffectInstance* arg0, s16 arg1);
void Particle_AddTargetRotationXY(ParticleEffectInstance* arg0, s16 arg1, s16 arg2);
void Particle_SubtractRotationDeltaVec(ParticleEffectInstance* arg0, Vec3s arg1);
void Particle_SubtractRotationDeltaX(ParticleEffectInstance* arg0, s16 arg1);
void Particle_SubtractRotationDeltaY(ParticleEffectInstance* arg0, s16 arg1);
void Particle_SubtractRotationDeltaZ(ParticleEffectInstance* arg0, s16 arg1);
void Particle_ApproachRotationXWrap(ParticleEffectInstance* arg0);
void Particle_ApproachRotationYWrap(ParticleEffectInstance* arg0);
void Particle_ApproachRotationZWrap(ParticleEffectInstance* arg0);
void Particle_ApproachRotationAllWrap(ParticleEffectInstance* arg0);
void Particle_ApproachRotationAllWrapFull(ParticleEffectInstance* arg0);
void Particle_ApproachRotationXWrapToTarget(ParticleEffectInstance* arg0, s16 arg1, s16 arg2);
void Particle_ApproachRotationYWrapToTarget(ParticleEffectInstance* arg0, s16 arg1, s16 arg2);
s32 Particle_DecreaseRotationXTowards(ParticleEffectInstance* arg0, s32 arg1, s32 arg2);
s32 Particle_DecreaseRotationYTowards(ParticleEffectInstance* arg0, s32 arg1, s32 arg2);
s32 Particle_DecreaseRotationZTowards(ParticleEffectInstance* arg0, s32 arg1, s32 arg2);
void Particle_RandomizeRotationXY(ParticleEffectInstance* arg0, s32 arg1, s32 arg2);
void Particle_RandomizeRotationXWithMaskY(ParticleEffectInstance* arg0, s32 arg1, s32 arg2);
void Particle_RandomizeRotationY(ParticleEffectInstance* arg0, s32 arg1);
void Particle_RandomizeRotationYWithMask(ParticleEffectInstance* arg0, s32 arg1);
void Particle_RandomizeRotationXYFixedY(ParticleEffectInstance* arg0);
void Particle_CalcDirectionVector(ParticleEffectInstance* arg0, f32 arg1, Vec3f* arg2);
void Particle_CalcDirectionVectorXYZ(ParticleEffectInstance* arg0, f32 arg1, Vec3f* arg2);
void Particle_CalcDirectionVectorXZ(ParticleEffectInstance* arg0, f32 arg1, Vec3f* arg2);
void Particle_CalcComplexDirection(ParticleEffectInstance* arg0, f32 arg1, Vec3f* arg2);
void Particle_CalcAnotherDirection(ParticleEffectInstance* arg0, f32 arg1, Vec3f* arg2);
void Particle_SetSpeed(ParticleEffectInstance* arg0, f32 arg1);
void Particle_SetAcceleration(ParticleEffectInstance* arg0, f32 arg1);
s32 Particle_ApproachSpeedScaled(ParticleEffectInstance* arg0, f32 arg1, f32 arg2);
s32 Particle_ApproachSpeed(ParticleEffectInstance* arg0, f32 arg1);
s32 Particle_ApproachAcceleration(ParticleEffectInstance* arg0, f32 arg1, f32 arg2);
void Particle_SetAccelerationVector(ParticleEffectInstance* arg0, Vec3f arg1);
void Particle_SetAccelerationXYZ(ParticleEffectInstance* arg0, f32 arg1, f32 arg2, f32 arg3);
void Particle_SetAccelerationX(ParticleEffectInstance* arg0, f32 arg1);
void Particle_SetAccelerationY(ParticleEffectInstance* arg0, f32 arg1);
void Particle_SetAccelerationZ(ParticleEffectInstance* arg0, f32 arg1);
s32 Particle_IncrementAccelerationXClamp(ParticleEffectInstance* arg0, f32 arg1, f32 arg2);
s32 Particle_IncrementAccelerationYClamp(ParticleEffectInstance* arg0, f32 arg1, f32 arg2);
s32 Particle_IncrementAccelerationZClamp(ParticleEffectInstance* arg0, f32 arg1, f32 arg2);
s32 Particle_DecrementAccelerationXClamp(ParticleEffectInstance* arg0, f32 arg1, f32 arg2);
s32 Particle_DecrementAccelerationYClamp(ParticleEffectInstance* arg0, f32 arg1, f32 arg2);
s32 Particle_DecrementAccelerationZClamp(ParticleEffectInstance* arg0, f32 arg1, f32 arg2);
void Particle_ScaleAccelerationVector(ParticleEffectInstance* arg0, f32 arg1);
s32 func_8140B180(ParticleEffectInstance* arg0, f32 arg1, f32 arg2);
void Particle_SetVelocityYFromRotationX(ParticleEffectInstance* arg0);
void Particle_SetVelocityXFromRotationY(ParticleEffectInstance* arg0);
void Particle_SetVelocityZFromRotationY(ParticleEffectInstance* arg0);
void Particle_SetVelocityXYFromRotationZ(ParticleEffectInstance* arg0);
void Particle_SetVelocityXZFromRotationY(ParticleEffectInstance* arg0);
void Particle_SetVelocityFromRotationXY(ParticleEffectInstance* arg0);
void Particle_SetVelocityFromRotationXZ(ParticleEffectInstance* arg0);
void Particle_SetVelocityFromRotationYX(ParticleEffectInstance* arg0);
void Particle_SetVelocityFromRotationYZ(ParticleEffectInstance* arg0);
void Particle_SetVelocityComplexA(ParticleEffectInstance* arg0);
void Particle_SetVelocityComplexB(ParticleEffectInstance* arg0);
void Particle_SetVelocityComplexC(ParticleEffectInstance* arg0);
void Particle_SetVelocityComplexD(ParticleEffectInstance* arg0);
void Particle_UpdatePositionAndAccelFromYaw(ParticleEffectInstance* arg0, f32 arg1, s16 arg2);
s32 Particle_StartVerticalMotionTimer(ParticleEffectInstance* arg0, f32 arg1, f32 arg2, f32 arg3, s16 arg4, s16 arg5);
void Particle_SetScaleFactor1(ParticleEffectInstance* arg0, f32 arg1);
void Particle_SetScaleRaw1(ParticleEffectInstance* arg0, f32 arg1);
void Particle_SetScaleFactor2(ParticleEffectInstance* arg0, f32 arg1);
void Particle_SetScaleFactor3(ParticleEffectInstance* arg0, f32 arg1);
s32 Particle_ApproachScaleFactor1(ParticleEffectInstance* arg0, f32 arg1, f32 arg2);
s32 Particle_ApproachScaleFactor1WithCallback(ParticleEffectInstance* arg0, f32 arg1, f32 arg2);
s32 Particle_ApproachScaleFactor2(ParticleEffectInstance* arg0);
s32 Particle_ApproachScaleFactor2WithCallback(ParticleEffectInstance* arg0);
s32 Particle_ApproachScaleFactor3(ParticleEffectInstance* arg0, f32 arg1, f32 arg2);
void Particle_SetPrimColor(ParticleEffectInstance* arg0, u8 arg1, u8 arg2, u8 arg3);
s32 Particle_ApproachPrimR(ParticleEffectInstance* arg0, u8 arg1, u8 arg2);
s32 Particle_ApproachPrimG(ParticleEffectInstance* arg0, u8 arg1, u8 arg2);
s32 Particle_ApproachPrimB(ParticleEffectInstance* arg0, u8 arg1, u8 arg2);
void Particle_SetEnvColor(ParticleEffectInstance* arg0, u8 arg1, u8 arg2, u8 arg3);
s32 Particle_ApproachEnvR(ParticleEffectInstance* arg0, u8 arg1, u8 arg2);
s32 Particle_ApproachEnvB(ParticleEffectInstance* arg0, u8 arg1, u8 arg2);
s32 Particle_ApproachEnvG(ParticleEffectInstance* arg0, u8 arg1, u8 arg2);
void Particle_SetPrimAlpha(ParticleEffectInstance* arg0, u8 arg1);
s32 Particle_ApproachPrimAlpha(ParticleEffectInstance* arg0, u8 arg1, u8 arg2);
s32 Particle_ApproachPrimAlphaWithCallback(ParticleEffectInstance* arg0, u8 arg1, u8 arg2);
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
void Particle_SetByteCA(ParticleEffectInstance* arg0, u8 arg1);
void Particle_SetShortAC(ParticleEffectInstance* arg0, s16 arg1);
void Particle_SetByteCF(ParticleEffectInstance* arg0, u8 arg1);
void func_8140BEF8(ParticleEffectInstance* arg0, u8 arg1);
void Particle_SetByteCC(ParticleEffectInstance* arg0, u8 arg1);
void Particle_SetShortAA(ParticleEffectInstance* arg0, s16 arg1);
void Particle_SetShortCE(ParticleEffectInstance* arg0, s16 arg1);
void Particle_SetByteCD(ParticleEffectInstance* arg0, s16 arg1);
void Particle_SetShortAE(ParticleEffectInstance* arg0, s16 arg1);
s32 Particle_ApproachShortAE(ParticleEffectInstance* arg0, s16 arg1, s16 arg2);
s32 Particle_ApproachShortAEWithCallback(ParticleEffectInstance* arg0, s16 arg1, s16 arg2);
void Particle_SetShortB0(ParticleEffectInstance* arg0, s16 arg1);
s32 Particle_ApproachShortB0(ParticleEffectInstance* arg0, s16 arg1, s16 arg2);
s16 Particle_GetShortAC(ParticleEffectInstance* arg0);
s32 Particle_GetShortCE(ParticleEffectInstance* arg0);
u8 Particle_GetByteCD(ParticleEffectInstance* arg0);
s16 Particle_GetShortAE(ParticleEffectInstance* arg0);
s16 Particle_GetShortCF(ParticleEffectInstance* arg0);
s16 Particle_GetShortAA(ParticleEffectInstance* arg0);
void Particle_SetShortACIfValid(ParticleEffectInstance* arg0, s16 arg1);
void Particle_SetByteCFIfValid(ParticleEffectInstance* arg0, u8 arg1);
void Particle_SetTimerA6IfValid(ParticleEffectInstance* arg0, s16 arg1);
void Particle_SetTimerA8IfValid(ParticleEffectInstance* arg0, s16 arg1);
void Particle_SetByteCEIfValid(ParticleEffectInstance* arg0, u8 arg1);
void Particle_SetByteCDIfValid(ParticleEffectInstance* arg0, u8 arg1);
void Particle_SetShortAAIfValid(ParticleEffectInstance* arg0, s16 arg1);
void Particle_SetPrimAlphaIfValid(ParticleEffectInstance* arg0, u8 arg1);
void Particle_SetShortAEIfValid(ParticleEffectInstance* arg0, s16 arg1);
void Particle_SetShortB0IfValid(ParticleEffectInstance* arg0, s16 arg1);
void Particle_UpdateForCamera(CameraStruct* arg0);
void Particle_ProcessAllForCamera(CameraStruct* arg0);
void Particle_RenderUIOverlay(s16 arg0);
void Particle_ExecuteCallbackBasedOnType(ParticleEffectInstance* arg0, unk_D_8140E728_01C_004_1* arg1);
void Particle_HandleDisplayList(ParticleEffectInstance* arg0);
void Particle_RenderWithCamera(ParticleEffectInstance* arg0, CameraStruct* arg1);
void Particle_NoOp(UNUSED ParticleEffectInstance* arg0, UNUSED CameraStruct* arg1);


void Timer_UpdateCounters(void);
void Timer_Tick(void);


void LoadTexture_RGBA16_32x32(UNUSED ParticleEffectInstance* arg0, u8* texture);
void LoadTexture_IA8_32x32_ByIndex(ParticleEffectInstance* arg0, u8* texture);
void LoadTexture_IA8_32x32(UNUSED ParticleEffectInstance* arg0, u8* texture);
void LoadTexture_IA8_32x64_ByIndex(ParticleEffectInstance* arg0, u8* texture);
void LoadTexture_CI4_32x32(UNUSED ParticleEffectInstance* arg0, u8* texture);
void func_8140C84C(ParticleEffectInstance* arg0, u8* texture);
void func_8140C880(UNUSED ParticleEffectInstance* arg0, u8* texture);
void func_8140C8B8(UNUSED ParticleEffectInstance* arg0, u8* texture);
void func_8140C8F4(UNUSED ParticleEffectInstance* arg0, u8* texture);
void func_8140C930(UNUSED ParticleEffectInstance* arg0, u8* texture);
void func_8140C96C(UNUSED ParticleEffectInstance* arg0, u8* texture);
void func_8140C9B0(ParticleEffectInstance* arg0, u8* texture);
void func_8140C9EC(UNUSED ParticleEffectInstance* arg0, u8* texture);
void func_8140CA30(ParticleEffectInstance* arg0, u8* texture);
void func_8140CA64(UNUSED ParticleEffectInstance* arg0, u8* texture);
void func_8140CA90(UNUSED ParticleEffectInstance* arg0, u8* texture);
void func_8140CAC8(UNUSED ParticleEffectInstance* arg0, u8* texture);
void func_8140CB04(ParticleEffectInstance* arg0, u8* texture);
void func_8140CB38(UNUSED ParticleEffectInstance* arg0, u8* texture);
void func_8140CB64(UNUSED ParticleEffectInstance* arg0, u8* texture);
void func_8140CB90(ParticleEffectInstance* arg0, CameraStruct* arg1);
void func_8140CC04(ParticleEffectInstance* arg0, CameraStruct* arg1);
s32 func_8140CC90(ParticleEffectInstance* arg0, UNUSED CameraStruct* arg1);
void func_8140CD80(ParticleEffectInstance* arg0, CameraStruct* arg1);
void func_8140CDDC(ParticleEffectInstance* arg0, CameraStruct* arg1);
void func_8140CE68(ParticleEffectInstance* arg0, CameraStruct* arg1);
void func_8140CED4(ParticleEffectInstance* arg0, CameraStruct* arg1);
void func_8140CF30(ParticleEffectInstance* arg0, CameraStruct* arg1);
void func_8140CFBC(ParticleEffectInstance* arg0, CameraStruct* arg1);
void func_8140D050(ParticleEffectInstance* arg0, CameraStruct* arg1);
void func_8140D0E4(ParticleEffectInstance* arg0, CameraStruct* arg1);
void func_8140D170(ParticleEffectInstance* arg0, CameraStruct* arg1);
void func_8140D1FC(ParticleEffectInstance* arg0, CameraStruct* arg1);
void func_8140D288(ParticleEffectInstance* arg0, CameraStruct* arg1);
s32 func_8140D314(ParticleEffectInstance* arg0, UNUSED CameraStruct* arg1);
void func_8140D404(ParticleEffectInstance* arg0, CameraStruct* arg1);
void GetPaletteColor(u8* arg0, u16 arg1);
void GetPaletteColorPair(u8* arg0, u8* arg1, u16 arg2);
void SetPrimColorFromPalette(ParticleEffectInstance* arg0, u16 arg1);
void SetEnvColorFromPalette(ParticleEffectInstance* arg0, u16 arg1);
void SetPrimEnvColorFromPair(ParticleEffectInstance* arg0, u16 arg1);
void func_8140D5F0(ParticleEffectInstance* arg0, s16 arg1);
void func_8140D624(ParticleEffectInstance* arg0, s16 arg1);
void func_8140D658(ParticleEffectInstance* arg0, s16 arg1);
void func_8140D68C(ParticleEffectInstance* arg0, s16 arg1);
void func_8140D6C0(ParticleEffectInstance* arg0, s16 arg1);
void func_8140D708(ParticleEffectInstance* arg0, s16 arg1);
void func_8140D750(ParticleEffectInstance* arg0);
void func_8140D78C(ParticleEffectInstance* arg0);
s32 IsPrimColorSupported(ParticleEffectInstance* arg0, u16 arg1, u8 arg2);
s32 IsEnvColorSupported(ParticleEffectInstance* arg0, u16 arg1, u8 arg2);
s32 AreBothColorsSupported(ParticleEffectInstance* arg0, u16 arg1, u8 arg2);

#endif // _FRAGMENT34_H_
