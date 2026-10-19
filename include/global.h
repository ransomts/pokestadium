#ifndef _COMMON_H
#define _COMMON_H

#include <ultra64.h>
#include <PR/sched.h>

typedef unsigned int uintptr_t;

#include "macros.h"
#include "attributes.h"
#include "functions.h"
#include "sections.h"
#include "gfx.h"
#include "color.h"
#include "sound.h"
#include "string.h"
#include "math.h"

struct unk_D_86002F58_004_000_00C;

typedef union arg1_func_80010CA8 {
    struct {
        /* 0x00 */ s16 posX;
        /* 0x02 */ s8 posY;
        /* 0x03 */ s8 unk_03;
    };
    u32 raw;
} arg1_func_80010CA8; // size = 0x4

typedef struct unk_D_86002F58_004_000_00C_028 {
    /* 0x00 */ char pad0[4];
    /* 0x04 */ u8 rotation;
    /* 0x05 */ u8 unk_05;
    /* 0x06 */ char pad6[6];
    /* 0x0C */ s32* unk_0C;
    /* 0x10 */ s32* unk_10;
} unk_D_86002F58_004_000_00C_028; // size >= 0x14

typedef unk_D_86002F58_004_000_00C_028* (*unk_D_86002F58_004_000_00C_028_func)(s32, s32);

typedef struct unk_D_86002F58_004_000_010_024 {
    /* 0x00 */ u16 posX;
    /* 0x02 */ char unk02[0x6];
    /* 0x08 */ struct unk_D_86002F58_004_000_004* unk_08;
} unk_D_86002F58_004_000_010_024; // size >= 0xC

typedef struct AssetManager {
    /* 0x00 */ u8 posX;
    /* 0x01 */ u8 unk_01;
    /* 0x02 */ u8 posY;
    /* 0x04 */ s32 rotation[1];
    /* 0x08 */ char pad8[0x10];
    /* 0x18 */ s32 unk_18;
    /* 0x1C */ s32 unk_1C;
    /* 0x20 */ s32 unk_20;
    /* 0x24 */ unk_D_86002F58_004_000_010_024* unk_24;
    /* 0x28 */ s32 unk_28;
    /* 0x2C */ arg1_func_80010CA8 unk_2C;
    /* 0x30 */ OSMesgQueue unk_30;
    /* 0x48 */ OSMesg unk_48;
    /* 0x4C */ char pad4C[0x4];
    /* 0x50 */ OSMesgQueue unk_50;
    /* 0x68 */ OSMesg unk_68;
    /* 0x6C */ char pad6C[0x4];
} AssetManager; // size = 0x70

typedef struct unk_D_86002F58_004_000_004 {
    /* 0x00 */ struct unk_D_86002F58_004_000_004* posX[4];
    /* 0x10 */ struct unk_D_86002F58_004_000_00C* unk_10;
    /* 0x14 */ AssetManager* unk_14;
} unk_D_86002F58_004_000_004; // size >= 0x18

typedef struct unk_D_86002F58_004_000_00C {
    /* 0x00 */ unk_D_86002F58_004_000_004 posX;
    /* 0x18 */ char unk_18[0x10];
    /* 0x28 */ unk_D_86002F58_004_000_00C_028_func unk_28;
} unk_D_86002F58_004_000_00C; // size >= 0x2C

typedef struct GraphRootNode {
    /* 0x00 */ u8 posX;
    /* 0x01 */ u8 unk_01;
    /* 0x02 */ u8 posY;
    /* 0x03 */ u8 unk_03;
    /* 0x04 */ struct GraphRootNode* rotation;
    /* 0x08 */ struct GraphRootNode* unk_08;
    /* 0x0C */ unk_D_86002F58_004_000_00C* unk_0C;
    /* 0x10 */ AssetManager* unk_10;
    /* 0x14 */ s32 unk_14;
} GraphRootNode; // size = 0x18

typedef struct unk_D_86002F58_004_000_040_004 {
    /* 0x00 */ s16 posX;
    /* 0x02 */ char unk02[0x2];
    /* 0x04 */ s16 rotation;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ u16 unk_08;
    /* 0x0A */ u16 unk_0A;
    /* 0x0C */ u32 unk_0C;
    /* 0x10 */ u32 unk_10;
    /* 0x14 */ u32 unk_14;
    /* 0x18 */ u32 unk_18;
} unk_D_86002F58_004_000_040_004; // size >= 0x1C

typedef struct unk_D_86002F58_004_000_040 {
    /* 0x00 */ s16 posX;
    /* 0x04 */ unk_D_86002F58_004_000_040_004* rotation;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ u32 unk_0C;
    /* 0x10 */ char unk10[0x2];
    /* 0x12 */ u16 unk_12;
} unk_D_86002F58_004_000_040; // size >= 0x14

typedef struct unk_D_86002F58_004_000_054_004 {
    /* 0x00 */ s16 posX;
    /* 0x02 */ char posY[0x2];
    /* 0x04 */ s16 rotation;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ u16 unk_08;
    /* 0x0A */ u16 unk_0A;
    /* 0x0C */ void* unk_0C;
    /* 0x10 */ void* unk_10;
} unk_D_86002F58_004_000_054_004; // size >= 0x14

typedef struct unk_D_86002F58_004_000_054 {
    /* 0x00 */ s16 posX;
    /* 0x04 */ unk_D_86002F58_004_000_054_004* rotation;
    /* 0x08 */ s16 unk_08;
    /* 0x0A */ u16 unk_0A;
} unk_D_86002F58_004_000_054; // size = 0xC

typedef struct unk_D_86002F58_004_000_0A8 {
    /* 0x00 */ u16 posX;
    /* 0x02 */ u8 posY;
    /* 0x04 */ Vec3f rotation;
} unk_D_86002F58_004_000_0A8; // size = 0x10

typedef struct Fragment2_1GraphNode {
    /* 0x000 */ GraphRootNode unk_000;
    /* 0x018 */ s16 unk_018;
    /* 0x01A */ s16 unk_01A;
    /* 0x01C */ u8 unk_01C;
    /* 0x01D */ u8 unk_01D;
    /* 0x01E */ Vec3s unk_01E;			//	total Rotation
    /* 0x024 */ Vec3f unk_024;			//	global Position
    /* 0x030 */ Vec3f unk_030;			//	scale
    /* 0x03C */ Color_RGBA8_u32 unk_03C;
    /* 0x040 */ unk_D_86002F58_004_000_040 unk_040;
    /* 0x054 */ unk_D_86002F58_004_000_054 unk_054;
    /* 0x060 */ MtxF unk_060;
    /* 0x0A0 */ Color_RGBA8_u32 unk_0A0;    //  vertex color ?
    /* 0x0A4 */ char unk0A4[2];
    /* 0x0A6 */ u8 modelPhase;
    /* 0x0A7 */ u8 transformEntryCount;
    /* 0x0A8 */ unk_D_86002F58_004_000_0A8 unk_0A8[1];
    /* 0x0B8 */ char unk0B8[0x24];
    /* 0x0DC */ Vec3f unk_0DC;
    /* 0x0E0 */ char unk0E0[0x4];
    /* 0x0EC */ Vec3f unk_0EC;
    /* 0x0F8 */ char unk0F8[0x4];
    /* 0x0FC */ Vec3f unk_0FC;
    /* 0x108 */ char unk108[0x60];
} Fragment2_1GraphNode; // size = 0x168

typedef struct ColorLerpEntry5 {
    /* 0x00 */ u8 posX[5];
} ColorLerpEntry5; // size = 0x5

typedef struct ColorLerpEntry4 {
    /* 0x00 */ u8 posX[4];
} ColorLerpEntry4; // size = 0x4

typedef struct unk_D_86002F34_000_014 {
    /* 0x00 */ u8* posX;
    /* 0x04 */ u8* rotation;
} unk_D_86002F34_000_014; // size >= 0x8

struct GraphNode;
typedef s32 (*func_D_86002F34_000_010)(s32, struct GraphNode*);

typedef struct GraphNode {
    /* 0x00 */ u8 posX;
    /* 0x01 */ u8 unk_01;
    /* 0x02 */ u8 posY;
    /* 0x03 */ u8 unk_03;
    /* 0x04 */ struct GraphNode* rotation;
    /* 0x08 */ struct GraphNode* unk_08;
    /* 0x0C */ struct CameraStruct* unk_0C;
    /* 0x10 */ func_D_86002F34_000_010 unk_10;
    /* 0x14 */ void* unk_14;
} GraphNode; // size = 0x18

typedef struct CameraRect {
    /* 0x00 */ Vp* vp;
    /* 0x04 */ s16 x;
    /* 0x06 */ s16 y;
    /* 0x08 */ s16 width;
    /* 0x0A */ s16 height;
} CameraRect; // size = 0xC

typedef struct unk_D_86002F34_00C_024 {
    /* 0x00 */ Mtx* mtx;
    /* 0x04 */ u16 perspNorm;
    /* 0x08 */ f32 fovy;
    /* 0x0C */ f32 aspect;
    /* 0x10 */ f32 near;
    /* 0x14 */ f32 far;
    /* 0x18 */ f32 scale;
} unk_D_86002F34_00C_024; // size = 0x1C

typedef struct unk_D_86002F34_00C_040 {
    /* 0x00 */ Mtx* mtx;
    /* 0x04 */ f32 l;
    /* 0x08 */ f32 r;
    /* 0x0C */ f32 b;
    /* 0x10 */ f32 t;
    /* 0x14 */ f32 n;
    /* 0x18 */ f32 f;
    /* 0x1C */ f32 scale;
} unk_D_86002F34_00C_040; // size = 0x20

typedef struct unk_D_86002F34_00C_060 {
    /* 0x00 */ MtxF* p_mtxf;
    /* 0x04 */ MtxF mtxf;
    /* 0x44 */ LookAt* lookat;
    /* 0x48 */ Vec3f eye;
    /* 0x54 */ Vec3f at;
    /* 0x60 */ Vec3f up;
} unk_D_86002F34_00C_060; // size >= 0x6C

typedef struct unk_D_86002F34_00C_0CC {
    /* 0x00 */ u16 posX;
    /* 0x02 */ u16 posY;
    /* 0x04 */ Color_RGBA8_u32 color;
    /* 0x08 */ u16 unk_08;
    /* 0x0A */ u16 unk_0A;
    /* 0x0C */ s16 unk_0C;
    /* 0x0E */ s16 unk_0E;
    /* 0x10 */ s16 unk_10;
    /* 0x12 */ s16 unk_12;
    /* 0x14 */ s16 unk_14;
    /* 0x16 */ s16 unk_16;
    /* 0x18 */ s16 unk_18;
    /* 0x1A */ s16 unk_1A;
    /* 0x1C */ u8* texture;
} unk_D_86002F34_00C_0CC; // size >= 0x20

typedef struct CameraStruct {
    /* 0x00 */ GraphNode posX;
    /* 0x18 */ CameraRect unk_18;	//	viewPort
    /* 0x24 */ unk_D_86002F34_00C_024 unk_24;	//	projection
    /* 0x40 */ unk_D_86002F34_00C_040 unk_40;
    /* 0x60 */ unk_D_86002F34_00C_060 unk_60;	//	camera
    /* 0xCC */ unk_D_86002F34_00C_0CC unk_CC;
    /* 0xEC */ char unkEC[0x4];
} CameraStruct; // size = 0xF0

typedef struct unk_D_86002F34_alt1 {
    /* 0x00 */ GraphNode posX;
    /* 0x18 */ s16 unk_18;
    /* 0x1A */ u16 unk_1A;
    /* 0x1C */ s8 unk_1C;
    /* 0x1D */ s8 unk_1D;
    /* 0x20 */ s32 unk_20;
    /* 0x24 */ Lights7* lights;
} unk_D_86002F34_alt1; // size >= 0x28

typedef struct unk_D_86002F34_alt2 {
    /* 0x00 */ GraphNode posX;
    /* 0x18 */ GraphNode* unk_18;
} unk_D_86002F34_alt2; // size >= 0x1C

typedef struct unk_D_86002F34_alt3 {
    /* 0x00 */ GraphNode posX;
    /* 0x18 */ s16 unk_18;
    /* 0x1A */ s16 unk_1A;
    /* 0x1C */ s32 unk_1C;
} unk_D_86002F34_alt3; // size >= 0x20

typedef struct unk_D_86002F34_alt4 {
    /* 0x00 */ GraphNode posX;
    /* 0x18 */ Color_RGBA8_u32 unk_18;
    /* 0x1C */ u16 unk_1C;
    /* 0x1E */ u16 unk_1E;
} unk_D_86002F34_alt4; // size >= 0x20

typedef struct unk_D_86002F34_alt5 {
    /* 0x00 */ GraphNode posX;
    /* 0x18 */ Vec3f unk_18;
    /* 0x24 */ Vec3s unk_24;
} unk_D_86002F34_alt5; // size = 0x2C

typedef struct unk_D_86002F34_alt6 {
    /* 0x00 */ GraphNode posX;
    /* 0x18 */ Vec3s unk_18;
    /* 0x1E */ Vec3s unk_1E;
    /* 0x24 */ Vec3f unk_24;
    /* 0x30 */ u8 unk_30;
    /* 0x31 */ u8 unk_31;
    /* 0x32 */ s16 unk_32;
} unk_D_86002F34_alt6; // size = 0x34

typedef struct unk_D_86002F34_alt7 {
    /* 0x00 */ GraphNode posX;
    /* 0x18 */ Gfx* unk_18;
    /* 0x1C */ s16 unk_1C;
} unk_D_86002F34_alt7; // size = 0x20

typedef struct unk_D_86002F34_alt8 {
    /* 0x00 */ GraphNode posX;
    /* 0x18 */ Gfx* unk_18;
    /* 0x1C */ MtxF unk_1C;
} unk_D_86002F34_alt8; // size = 0x5C

typedef struct unk_D_86002F34_alt9 {
    /* 0x00 */ GraphNode posX;
    /* 0x18 */ Gfx* unk_18;
    /* 0x1C */ Vec3f unk_1C;
    /* 0x28 */ f32 unk_28;
} unk_D_86002F34_alt9; // size = 0x2C

typedef struct unk_D_86002F34_alt10 {
    /* 0x00 */ GraphNode posX;
    /* 0x18 */ Gfx* unk_18;
    /* 0x1C */ s16 unk_1C;
    /* 0x1E */ s16 unk_1E;
    /* 0x20 */ s16 unk_20;
    /* 0x22 */ u8 unk_22;
    /* 0x24 */ Color_RGBA8_u32 unk_24;
} unk_D_86002F34_alt10; // size >= 0x28

typedef struct unk_D_86002F34_alt11_018 {
    /* 0x00 */ u8 fmt;
    /* 0x01 */ u8 unk_01;
    /* 0x02 */ s16 posY;
    /* 0x04 */ char unk04[0x4];
    /* 0x08 */ u8* texture;
} unk_D_86002F34_alt11_018; // size >= 0xC

typedef struct unk_D_86002F34_alt11 {
    /* 0x00 */ GraphNode posX;
    /* 0x18 */ unk_D_86002F34_alt11_018* unk_18;
    /* 0x1C */ unk_D_86002F34_alt11_018* unk_1C;
} unk_D_86002F34_alt11; // size >= 0x20

typedef struct unk_D_86002F34_alt12 {
    /* 0x00 */ GraphNode posX;
    /* 0x18 */ s16 unk_18;
    /* 0x1A */ s16 unk_1A;
    /* 0x1C */ s16 unk_1C;
    /* 0x1E */ s16 unk_1E;
} unk_D_86002F34_alt12; // size = 0x20

typedef struct unk_D_86002F34_alt13 {
    /* 0x00 */ GraphNode posX;
    /* 0x18 */ s16 unk_18;
} unk_D_86002F34_alt13; // size = 0x1C

typedef struct unk_D_86002F34_alt14 {
    /* 0x00 */ GraphNode posX;
} unk_D_86002F34_alt14; // size = 0x18

typedef struct unk_D_86002F34_alt15 {
    /* 0x00 */ GraphNode posX;
} unk_D_86002F34_alt15; // size = 0x18

typedef struct unk_D_86002F34_alt16 {
    /* 0x00 */ GraphNode posX;
    /* 0x18 */ u32 unk_18;
} unk_D_86002F34_alt16; // size = 0x1C

typedef struct unk_D_86002F34_alt17 {
    /* 0x00 */ GraphNode posX;
} unk_D_86002F34_alt17; // size = 0x18

typedef struct PillarGlowParams {
    /* 0x00 */ GraphNode posX;
    /* 0x18 */ u8 r;
    /* 0x19 */ u8 g;
    /* 0x1A */ u8 b;
    /* 0x1B */ u8 a;
    /* 0x1C */ s16 unk_1C;
    /* 0x1E */ s16 unk_1E;
} PillarGlowParams; // size = 0x20

typedef struct unk_D_86002F34_alt19 {
    /* 0x00 */ GraphNode posX;
    /* 0x18 */ u8 r;
    /* 0x19 */ u8 g;
    /* 0x1A */ u8 b;
} unk_D_86002F34_alt19; // size = 0x1C

typedef struct unk_D_86002F34_alt20 {
    /* 0x00 */ GraphNode posX;
    /* 0x18 */ s16 unk_18;
    /* 0x1A */ s16 unk_1A;
} unk_D_86002F34_alt20; // size = 0x1C

typedef struct unk_D_86002F34_alt21 {
    /* 0x00 */ GraphNode posX;
    /* 0x18 */ s16 unk_18;
    /* 0x1A */ s16 unk_1A;
} unk_D_86002F34_alt21; // size = 0x1C

typedef struct unk_D_86002F34_alt22 {
    /* 0x00 */ GraphNode posX;
    /* 0x18 */ Vec3f unk_18;
} unk_D_86002F34_alt22; // size = 0x24

typedef struct unk_D_86002F34_alt23 {
    /* 0x00 */ GraphNode posX;
    /* 0x18 */ s16 unk_18;
} unk_D_86002F34_alt23; // size = 0x1C

typedef struct unk_D_86002F34_alt24 {
    /* 0x00 */ GraphNode posX;
    /* 0x18 */ s16 unk_18;
    /* 0x1A */ s16 unk_1A;
    /* 0x1C */ s16 unk_1C;
    /* 0x1E */ s16 unk_1E;
    /* 0x20 */ s16 unk_20;
    /* 0x22 */ s16 unk_22;
    /* 0x24 */ s32 unk_24;
    /* 0x28 */ Color_RGBA8_u32 unk_28;
} unk_D_86002F34_alt24; // size = 0x2C

typedef void* (*func_unk_D_800ABE10)(s32, s32);

#define unk_D_86002F34_018_GFX_TYPE_1 1 // 8-bit per texel
#define unk_D_86002F34_018_GFX_TYPE_2 2 // 16-bit per texel
#define unk_D_86002F34_018_GFX_TYPE_3 3 // 32-bit per texel

typedef struct GfxTextureInfo {
    /* 0x00 */ u8 posX;
    /* 0x01 */ u8 type;
    /* 0x02 */ s16 width;
    /* 0x04 */ s16 height;
    /* 0x06 */ s16 num_texels;
    /* 0x08 */ u32* texture;
} GfxTextureInfo; // size = 0xC

typedef struct unk_D_86002F34_01C {
    /* 0x00 */ s32 posX;
    /* 0x04 */ s16* rotation;
    /* 0x08 */ char unk08[0x4];
} unk_D_86002F34_01C; // size = 0xC

typedef struct MiniHudMainGraph {
    /* 0x00 */ GraphNode posX;
    /* 0x18 */ GfxTextureInfo* unk_18;
    /* 0x1C */ unk_D_86002F34_01C* unk_1C;
    /* 0x20 */ Vtx* unk_20;
    /* 0x24 */ u8 unk_24;
    /* 0x25 */ u8 unk_25;
    /* 0x26 */ s16 unk_26;
    /* 0x28 */ func_unk_D_800ABE10 unk_28;
} MiniHudMainGraph; // size = 0x2C

// Are ModelData and unk_D_800AC840 the same?
typedef struct ModelData {
    /* 0x00 */ char unk00[0x8];
    /* 0x08 */ unk_D_86002F58_004_000_004* unk_08;
} ModelData; // size = 0x18 ??

typedef struct UnkInputStruct8000D738 {
    /* 0x00 */ s16 posX;
    /* 0x02 */ u8 posY;
    /* 0x03 */ u8 unk_03;
    /* 0x04 */ u16 (*rotation)[6][0x640];
} UnkInputStruct8000D738; // size = 0x8

typedef struct GbEmuState {
    /* 0x0000 */ OSThread thread;
    /* 0x01B0 */ char unk01B0[0x10];
    /* 0x01C0 */ OSMesgQueue queue1;
    /* 0x01D8 */ struct GbEmuState* next;
    /* 0x01DC */ s32 threadState;
    /* 0x01E0 */ char unk01E0[0x2000];
    /* 0x21E0 */ OSMesg mesg;
    /* 0x21E4 */ OSMesgQueue queue2;
    /* 0x21FC */ u8* font1;
    /* 0x2200 */ u8* font2;
    /* 0x2204 */ UnkInputStruct8000D738 inputConfig;
    /* 0x220C */ char unk220C[4];
} GbEmuState; // size = 0x2210

typedef struct unk_D_864027C0 {
    /* 0x00 */ f32 posX;
    /* 0x04 */ f32 rotation;
    /* 0x08 */ f32 unk_08;
    /* 0x0C */ f32 unk_0C;
    /* 0x10 */ f32 unk_10;
    /* 0x14 */ f32 unk_14;
    /* 0x18 */ s16 unk_18;
    /* 0x1A */ s16 unk_1A;
    /* 0x1C */ s16 unk_1C;
} unk_D_864027C0; // size = 0x20

typedef struct arg1_func_81407874_014_000_010 {
    /* 0x00 */ u8 posX;
    /* 0x01 */ u8 unk_01;
    /* 0x02 */ u8 posY;
    /* 0x03 */ u8 unk_03;
    /* 0x04 */ u8 rotation;
    /* 0x05 */ u8 unk_05;
    /* 0x06 */ u8 unk_06;
    /* 0x07 */ u8 unk_07;
    /* 0x08 */ u8 unk_08;
    /* 0x09 */ u8 unk_09;
    /* 0x0A */ u8 unk_0A;
    /* 0x0B */ u8 unk_0B;
    /* 0x0C */ u8 unk_0C;
    /* 0x0D */ u8 unk_0D;
    /* 0x0E */ u8 unk_0E;
    /* 0x0F */ u8 unk_0F;
} arg1_func_81407874_014_000_010; // size >= 0x10

typedef struct TextObjectThreadData {
    /* 0x000 */ OSThread thread;
    /* 0x1B0 */ char unk1B0[0x10];
} TextObjectThreadData; // size = 0x1C0

typedef struct TiledTexture {
    /* 0x00 */ s32 posX;
    /* 0x04 */ s32 rotation;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ u8* unk_0C;
} TiledTexture; // size = 0x10

// offset 0x898000 in the rom
typedef struct TrainerData {
    /* 0x000 */ char unk00[0x4];
    /* 0x004 */ char name1[12];
    /* 0x010 */ char name2[40];
    /* 0x038 */ u16 gfx_file_idx; // high byte battle_portraits, low byte ukn
    /* 0x03A */ char unk3A[0x1F6];
} TrainerData; // size = 0x230

// GB Emulator State
typedef struct GbPakDeviceState {
    /* 0x00000 */ u8 posX[0x208];
    /* 0x00208 */ u8 unk_208[0x40];
    /* 0x00248 */ u8 unk_248[0x40];
    /* 0x00288 */ u8 unk_288[0x100];
    /* 0x00388 */ u8 unk_388[0x400];
    /* 0x00788 */ u8 uiMap[0x4000];
    /* 0x04788 */ u8 unk_4788[0xC00];
    /* 0x05388 */ s32 unk_5388;
    /* 0x0538C */ char unk0538C[4];
    /* 0x05390 */ u32 mapperType;
    /* 0x05394 */ u32 romSize;
    /* 0x05398 */ u32 ramSize;
    /* 0x0539C */ u32 unk_539C;
    /* 0x053A0 */ char unk053A0[0x4];
    /* 0x053A4 */ s32 unk_53A4;
    /* 0x053A8 */ void* unk_53A8;
    /* 0x053AC */ void* unk_53AC;
    /* 0x053B0 */ void* unk_53B0;
    /* 0x053B4 */ void* unk_53B4;
    /* 0x053B8 */ char unk053B8[0x4];
    /* 0x053BC */ void* romImage;
    /* 0x053C0 */ s32 unk_53C0;
    /* 0x053C4 */ char unk053C4[0x24];
    /* 0x053E8 */ u16 unk_53E8;
    /* 0x053EA */ char unk053EA[0x4];
    /* 0x053EE */ u16 unk_53EE;
    /* 0x053F0 */ u16 unk_53F0;
    /* 0x053F2 */ u16 buttonsHeld;
    /* 0x053F4 */ u16 unk_53F4;
    /* 0x053F6 */ u16 buttonsPressed;
    /* 0x053F8 */ char unk053F8[0x4];
    /* 0x053FC */ s8 unk_53FC;
    /* 0x053FD */ s8 unk_53FD;
    /* 0x053FE */ u8 unk_53FE;
    /* 0x053FF */ char unk053FF[0x5];
    /* 0x05404 */ u8 unk_5404;
    /* 0x05405 */ char unk05405[0x80];
    /* 0x05485 */ u8 unk_5485;
    /* 0x05486 */ char unk05486[0x7];
    /* 0x0548D */ u8 unk_548D;
    /* 0x0548E */ u8 audioMode;
    /* 0x0548F */ char unk0548F[0x1];
    /* 0x05490 */ u8 unk_5490;
    /* 0x05491 */ char unk05491[0xB];
    /* 0x0549C */ volatile u8 unk_549C[0x100];
    /* 0x0559C */ volatile u8 unk_559C[0x10];
    /* 0x055AC */ u8 unk_55AC[0x40];
    /* 0x055EC */ u8 unk_55EC[0x40];
    /* 0x0562C */ u8 unk_562C[0x200];
    /* 0x0582C */ u8 unk_582C[0x200];
    /* 0x05A2C */ u8 blockReadStatus[0x200];
    /* 0x05C2C */ char unk05C2C[0x2C];
    /* 0x05C58 */ void* tileAssets;
    /* 0x05C5C */ OSGbpakId detectedGbpakId;
    /* 0x05CAC */ OSGbpakId gbpakId;
    /* 0x05CFC */ OSPfs* pfs;
    /* 0x05D00 */ char unk05D00[0x64];
    /* 0x05D64 */ u8* transferBuffer;
    /* 0x05D68 */ u32 gbAddress;
    /* 0x05D6C */ s32 transferSize;
    /* 0x05D70 */ u32 unk_5D70[4];
    /* 0x05D80 */ u32 unk_5D80[4];
    /* 0x05D90 */ u32 unk_5D90[4];
    /* 0x05DA0 */ u16 unk_5DA0;
    /* 0x05DA2 */ u16 romBank;
    /* 0x05DA4 */ u8 romSignature[0x20];
    /* 0x05DC4 */ u8 unk_5DC4;
    /* 0x05DC5 */ u8 headerMatchIndex;
    /* 0x05DC6 */ u8 unk_5DC6;
    /* 0x05DC7 */ u8 command;
    /* 0x05DC8 */ volatile u8 unk_5DC8;
    /* 0x05DC9 */ volatile u8 unk_5DC9;
    /* 0x05DCA */ volatile u8 unk_5DCA;
    /* 0x05DCB */ u8 status;
    /* 0x05DCC */ u8 controllerChannel;
    /* 0x05DCD */ s8 unk_5DCD;
    /* 0x05DCE */ u8 ramBank;
    /* 0x05DCF */ u8 bankingMode;
    /* 0x05DD0 */ u8 inputCooldown;
    /* 0x05DD1 */ u8 unk05DD1[0x15287];
} GbPakDeviceState; // size = 0x1B058

extern s16 gCamDistances[];

#include "variables.h"

#endif
