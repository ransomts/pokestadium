#ifndef _FRAGMENT62_H_
#define _FRAGMENT62_H_

#include "global.h"
#include "src/29BA0.h"
#include "src/3D140.h"
#include "src/6BC0.h"
#include "src/stage_loader.h"
#include "src/fragments/17/fragment17.h"
#include "src/fragments/34/fragment34.h"

typedef s32 (*func_D_84390300)(void);
typedef void (*func_D_84390320)(void);

typedef struct unk_D_84390010_654_09C {
    /* 0x00 */ char unk00[0x10];
} unk_D_84390010_654_09C; // size = 0x10

typedef struct unk_D_84390010_654_0AC {
    /* 0x00 */ char unk00[0x10];
} unk_D_84390010_654_0AC; // size = 0x10

typedef struct unk_D_84390010_168 {
    /* 0x000 */ Fragment2_1GraphNode unk_000;
    /* 0x168 */ char unk168[0x1];
    /* 0x169 */ u8 unk_169;
    /* 0x16A */ s16 unk_16A;
    /* 0x16C */ s16 unk_16C;
    /* 0x16E */ char unk16E[0x2];
} unk_D_84390010_168; // size = 0x170

typedef struct unk_D_84390010_654 {
    /* 0x00 */ char unk00[0x4];
    /* 0x04 */ u32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ u32 unk_10;
    /* 0x14 */ s32 unk_14;
    /* 0x18 */ u32 unk_18;
    /* 0x1C */ u8 unk_1C;
    /* 0x1E */ u16 unk_1E;
    /* 0x20 */ char unk20[0x8];
    /* 0x28 */ u16 unk_28;
    /* 0x2A */ u8 unk_2A;
    /* 0x2B */ u8 unk_2B;
    /* 0x2C */ u8 unk_2C;
    /* 0x2D */ u8 unk_2D;
    /* 0x2E */ u8 unk_2E;
    /* 0x2F */ u8 unk_2F;
    /* 0x30 */ u16 unk_30;
    /* 0x32 */ char unk32[0x2];
    /* 0x34 */ u16 unk_34;
    /* 0x36 */ u16 unk_36;
    /* 0x38 */ unk_D_800FCB18 unk_38;
    /* 0x9C */ unk_D_84390010_654_09C unk_9C;
    /* 0xAC */ unk_D_84390010_654_0AC unk_AC;
    /* 0xBC */ s16 unk_BC;
    /* 0xBE */ s16 unk_BE;
    /* 0xC0 */ char unkC0[1];
    /* 0xC1 */ u8 unk_C1[4];
    /* 0xC8 */ Controller* unk_C8;
} unk_D_84390010_654; // size = 0xCC

typedef struct unk_D_84390010_728_0168 {
    /* 0x00 */ GraphRootNode unk_00;
    /* 0x18 */ char unk18[0x4];
    /* 0x1C */ s16 unk_1C;
    /* 0x1E */ s16 unk_1E;
    /* 0x20 */ s16 unk_20;
    /* 0x22 */ char unk22[0xA];
    /* 0x2C */ f32 unk_2C;
    /* 0x30 */ char unk30[0x4];
    /* 0x34 */ f32 unk_34;
    /* 0x38 */ f32 unk_38;
    /* 0x3C */ char unk3C[0x6C];
    /* 0xA8 */ Vec3f unk_A8;
    /* 0xB4 */ Vec3f unk_B4;
} unk_D_84390010_728_0168; // size >= 0xC0

typedef struct unk_D_84390010_728 {
    /* 0x000 */ Fragment2_1GraphNode unk_000;
    /* 0x168 */ unk_D_84390010_728_0168* unk_168;
    /* 0x16C */ s32 unk_16C;
    /* 0x170 */ s32 unk_170;
    /* 0x174 */ char unk174[0x4];
    /* 0x178 */ s32 unk_178;
    /* 0x17C */ s32 unk_17C;
    /* 0x180 */ s32 unk_180;
    /* 0x184 */ s16 unk_184;
    /* 0x186 */ s16 unk_186;
    /* 0x188 */ f32 unk_188;
    /* 0x18C */ s32 unk_18C;
    /* 0x190 */ f32 unk_190;
    /* 0x194 */ f32 unk_194;
    /* 0x198 */ char unk198[0x4];
} unk_D_84390010_728; // size = 0x19C

typedef struct unk_D_84390010_8C4 {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s8 unk_08[4];
    /* 0x0C */ char unk0C[0x3C];
    /* 0x48 */ s8 unk_48[4];
    /* 0x4C */ char unk4C[0x3C];
} unk_D_84390010_8C4; // size = 0x88

typedef struct unk_D_84390010_94C {
    /* 0x00 */ u8 unk_00[10];
    /* 0x0A */ u8 unk_0A[4];
    /* 0x0E */ char unk0E[0x12];
} unk_D_84390010_94C; // size = 0x20

typedef struct unk_D_84390048 {
    /* 0x00 */ Vec3f unk_00;
    /* 0x0C */ Vec3f unk_0C;
    /* 0x18 */ u8 unk_18;
    /* 0x19 */ u8 unk_19;
    /* 0x1A */ u8 unk_1A;
    /* 0x1B */ u8 unk_1B;
    /* 0x1C */ char unk1C[4];
} unk_D_84390048; // size = 0x20

typedef struct unk_D_84390010_448 {
    /* 0x00 */ Vec3f unk_00;
    /* 0x0C */ Vec3f unk_0C;
    /* 0x18 */ Vec3f unk_18;
    /* 0x24 */ unk_D_84390048 unk_24;
    /* 0x44 */ s16 unk_44;
    /* 0x46 */ s16 unk_46;
    /* 0x48 */ char unk48[0x4];
    /* 0x4C */ f32 unk_4C;
} unk_D_84390010_448; // size >= 0x50

typedef struct unk_D_84390010 {
    /* 0x000 */ Fragment2_1GraphNode unk_000;
    /* 0x168 */ unk_D_84390010_168 unk_168[2];
    /* 0x448 */ unk_D_84390010_448 unk_448;
    /* 0x498 */ f32 unk_498;
    /* 0x49C */ f32 unk_49C;
    /* 0x4A0 */ f32 unk_4A0;
    /* 0x4A4 */ s16 unk_4A4;
    /* 0x4A6 */ s16 unk_4A6;
    /* 0x4A8 */ s16 unk_4A8;
    /* 0x4AC */ s32 unk_4AC;
    /* 0x4B0 */ s32 unk_4B0;
    /* 0x4B4 */ s32 unk_4B4;
    /* 0x4B8 */ s32 unk_4B8;
    /* 0x4BC */ char unk4BC[0x4];
    /* 0x4C0 */ s32 unk_4C0;
    /* 0x4C4 */ s32 unk_4C4;
    /* 0x4C8 */ s32 unk_4C8;
    /* 0x4CC */ Vec3f unk_4CC;
    /* 0x4D8 */ Vec3f unk_4D8;
    /* 0x4E4 */ f32 unk_4E4;
    /* 0x4E8 */ u8 unk_4E8;
    /* 0x4E9 */ u8 unk_4E9;
    /* 0x4EC */ Fragment2_1GraphNode unk_4EC;
    /* 0x654 */ unk_D_84390010_654 unk_654;
    /* 0x720 */ unk_D_800AE540_1194* unk_720;
    /* 0x724 */ unk_D_800AE540_0004* unk_724;
    /* 0x728 */ unk_D_84390010_728 unk_728;
    /* 0x8C4 */ unk_D_84390010_8C4 unk_8C4;
    /* 0x94C */ unk_D_84390010_94C unk_94C;
    /* 0x96C */ unk_D_84390010_94C unk_96C;
    /* 0x98C */ unk_D_84390010_94C unk_98C;
    /* 0x9AC */ unk_D_84390010_94C unk_9AC;
    /* 0x9CC */ unk_D_84390010_94C unk_9CC;
    /* 0x9EC */ unk_D_84390010_94C unk_9EC;
} unk_D_84390010; // size = 0xA0C

typedef struct unk_D_8438E7B0_A50 {
    /* 0x00 */ u8 unk_00;
    /* 0x01 */ u8 unk_01;
    /* 0x02 */ u8 unk_02;
    /* 0x03 */ u8 unk_03;
    /* 0x04 */ u8 unk_04;
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
} unk_D_8438E7B0_A50; // size = 0x10

typedef struct unk_D_8438E7B0 {
    /* 0x000 */ unk_D_8438E7B0_A50 unk_000[165];
    /* 0xA50 */ unk_D_8438E7B0_A50 unk_A50;
    /* 0xA60 */ char unkA60[0x10];
    /* 0xA70 */ unk_D_8438E7B0_A50 unk_A70;
    /* 0xA80 */ unk_D_8438E7B0_A50 unk_A80;
    /* 0xA90 */ char unkA90[0x60];
    /* 0xAF0 */ unk_D_8438E7B0_A50 unk_AF0;
    /* 0xB00 */ unk_D_8438E7B0_A50 unk_B00;
    /* 0xB10 */ unk_D_8438E7B0_A50 unk_B10;
    /* 0xB20 */ unk_D_8438E7B0_A50 unk_B20;
    /* 0xB30 */ char unkB30[0x51];
    /* 0xB81 */ u8 unk_B81;
    /* 0xB82 */ char unkB82[0x5E];
} unk_D_8438E7B0; // size = 0xBE0

typedef struct unk_D_84390240_000 {
    /* 0x00 */ char unk00[0x8];
    /* 0x08 */ s8 unk_08;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ s32 unk_10;
    /* 0x14 */ s32 unk_14;
    /* 0x18 */ u16 unk_18;
    /* 0x1A */ u8 unk_1A;
    /* 0x1C */ s32 unk_1C;
    /* 0x20 */ s32 unk_20;
    /* 0x24 */ s32 unk_24;
    /* 0x28 */ char unk28[0x2];
    /* 0x2A */ u16 unk_2A;
    /* 0x2C */ u16 unk_2C;
    /* 0x2E */ u16 unk_2E;
    /* 0x30 */ s32 unk_30;
    /* 0x34 */ s32 unk_34;
    /* 0x38 */ s32 unk_38;
    /* 0x3C */ s32 unk_3C;
    /* 0x40 */ s32 unk_40;
    /* 0x44 */ s32 unk_44;
    /* 0x48 */ s32 unk_48;
    /* 0x4C */ s32 unk_4C;
    /* 0x50 */ s32 unk_50;
    /* 0x54 */ u8 unk_54;
    /* 0x56 */ s16 unk_56;
    /* 0x58 */ s16 unk_58;
    /* 0x5A */ char unk5A[0x2];
    /* 0x5C */ f32 unk_5C;
    /* 0x60 */ f32 unk_60;
    /* 0x64 */ char unk64[0x4];
    /* 0x68 */ f32 unk_68;
    /* 0x6C */ f32 unk_6C;
    /* 0x70 */ f32 unk_70;
    /* 0x74 */ f32 unk_74;
    /* 0x78 */ u8 unk_78;
    /* 0x7A */ s16 unk_7A;
    /* 0x7C */ char unk7C[0x8];
    /* 0x84 */ f32 unk_84;
    /* 0x88 */ char unk88[0xC];
    /* 0x94 */ Vec3f unk_94;
    /* 0xA0 */ Vec3f unk_A0;
    /* 0xAC */ char unkAC[0xC];
    /* 0xB8 */ Vec3f unk_B8;
    /* 0xC4 */ Vec3f unk_C4;
    /* 0xD0 */ Vec3f unk_D0;
    /* 0xDC */ CameraStruct* unk_DC;
} unk_D_84390240_000; // size = 0xE0

typedef struct unk_D_84390240 {
    /* 0x00 */ unk_D_84390240_000* unk_00;
    /* 0x04 */ char unk04[0x3C];
} unk_D_84390240; // size = 0x40

typedef void (*unk_D_84385384_func)(unk_D_84390010*);

typedef struct unk_D_84385384 {
    /* 0x00 */ s16 unk_00;
    /* 0x04 */ unk_D_84385384_func unk_04[7];
    /* 0x20 */ s32 unk_20;
    /* 0x24 */ s32 unk_24;
    /* 0x28 */ s32 unk_28;
} unk_D_84385384; // size = 0x2C

typedef struct unk_D_843C4E44 {
    /* 0x000 */ u8 unk_000;
    /* 0x001 */ u8 unk_001;
    /* 0x3F2 */ char unk02[0x3F2];
} unk_D_843C4E44; // size >= 0x3F4

typedef struct unk_D_843C4DEC {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ char unk04[0x54];
} unk_D_843C4DEC; // size = 0x58

typedef struct unk_D_84390068 {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ unk_D_84385384_func unk_04;
} unk_D_84390068; // size = 0x8

typedef struct unk_D_84384588 {
    /* 0x00 */ u8 unk_00;
    /* 0x01 */ u8 unk_01;
    /* 0x02 */ char unk02[0xE];
} unk_D_84384588; // size = 0x10

typedef struct unk_D_84390178 {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ char unk04[0x14];
} unk_D_84390178; // size >= 0x18

typedef struct unk_D_8438FF70 {
    /* 0x00 */ Vec3f unk_00;
    /* 0x0C */ s16 unk_0C;
    /* 0x0E */ s16 unk_0E;
    /* 0x10 */ s16 unk_10;
    /* 0x12 */ u16 unk_12;
    /* 0x14 */ char unk14[0xC];
} unk_D_8438FF70; // size = 0x20

typedef struct unk_D_84390028 {
    /* 0x00 */ f32 unk_00;
    /* 0x04 */ f32 unk_04;
    /* 0x08 */ f32 unk_08;
    /* 0x0C */ f32 unk_0C;
} unk_D_84390028; // size = 0x10

typedef struct unk_D_84384608 {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ u16 unk_04;
} unk_D_84384608; // size = 0x8

typedef struct unk_D_843847BC {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s16 unk_04;
    /* 0x08 */ f32 unk_08;
    /* 0x0C */ f32 unk_0C;
    /* 0x10 */ f32 unk_10;
    /* 0x14 */ s16 unk_14;
} unk_D_843847BC; // size = 0x18

typedef struct unk_D_843901B0 {
    /* 0x00 */Vec3f unk_00;
    /* 0x0C */s16 unk_0C;
    /* 0x0E */s16 unk_0E;
    /* 0x10 */char unk10[0x2];
    /* 0x12 */s16 unk_12;
    /* 0x14 */s16 unk_14;
    /* 0x18 */f32 unk_18;
    /* 0x1C */f32 unk_1C;
    /* 0x20 */s16 unk_20;
    /* 0x22 */s16 unk_22;
    /* 0x24 */char unk24[0x2];
    /* 0x26 */s16 unk_26;
    /* 0x28 */s16 unk_28;
    /* 0x2C */f32 unk_2C;
    /* 0x30 */f32 unk_30;
    /* 0x34 */f32 unk_34;
    /* 0x38 */f32 unk_38;
    /* 0x3C */f32 unk_3C;
} unk_D_843901B0; // size >= 0x40

typedef struct unk_D_843901A0_4C8 {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ s32 unk_10;
    /* 0x14 */ Vec3f unk_14;
    /* 0x20 */ f32 unk_20;
    /* 0x24 */ f32 unk_24;
    /* 0x28 */ s16 unk_28;
    /* 0x2A */ s16 unk_2A;
} unk_D_843901A0_4C8; // size = 0x2C

typedef struct unk_D_843901A0 {
    /* 0x000 */ u8 unk_000;
    /* 0x004 */ s32 unk_004;
    /* 0x008 */ u8 unk_008[4];
    /* 0x00C */ char unk00C[0x3C];
    /* 0x048 */ u8 unk_048[64];
    /* 0x088 */ s8 unk_088[64];
    /* 0x0C8 */ s8 unk_0C8[64];
    /* 0x148 */ s8 unk_108[64];
    /* 0x148 */ s8 unk_148[64];
    /* 0x188 */ s8 unk_188[64];
    /* 0x1C8 */ s8 unk_1C8[64];
    /* 0x208 */ s8 unk_208[64];
    /* 0x248 */ s8 unk_248[64];
    /* 0x288 */ s8 unk_288[64];
    /* 0x2C8 */ s8 unk_2C8[64];
    /* 0x2C8 */ s8 unk_308[64];
    /* 0x348 */ s8 unk_348[64];
    /* 0x388 */ s8 unk_388[64];
    /* 0x3C8 */ s8 unk_3C8[64];
    /* 0x408 */ s8 unk_408[64];
    /* 0x448 */ s8 unk_448[2][64];
    /* 0x4C8 */ unk_D_843901A0_4C8 unk_4C8;
} unk_D_843901A0; // size = 0x4F4

typedef struct unk_D_84385790 {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ Color_RGBA8 unk_04;
} unk_D_84385790; // size = 0x8

typedef struct arg1_func_84344CE8 {
    /* 0x00 */ char unk00[0x14];
    /* 0x14 */ u8* unk_14;
    /* 0x18 */ Gfx* unk_18;
} arg1_func_84344CE8; // size >= 0x1C

typedef struct arg1_func_8434E21C {
    /* 0x00 */ u8* unk_00;
    /* 0x04 */ u8* unk_04;
    /* 0x08 */ char unk08[0x2];
    /* 0x0A */ s16 unk_0A;
} arg1_func_8434E21C; // size >= 0xC

typedef struct unk_D_843925E0_430 {
    /* 0x00 */ f32 unk_00;
    /* 0x04 */ f32 unk_04;
    /* 0x08 */ f32 unk_08;
    /* 0x0C */ s16 unk_0C;
    /* 0x0E */ s16 unk_0E;
    /* 0x10 */ Color_RGBA8 unk_10;
    /* 0x14 */ f32 unk_14;
    /* 0x18 */ f32 unk_18;
} unk_D_843925E0_430; // size = 0x1C

typedef struct unk_D_843925E0 {
    /* 0x000 */ s32 unk_000;
    /* 0x004 */ f32 unk_004;
    /* 0x008 */ f32 unk_008;
    /* 0x00C */ f32 unk_00C;
    /* 0x010 */ f32 unk_010;
    /* 0x014 */ f32 unk_014;
    /* 0x018 */ s16 unk_018;
    /* 0x01A */ s16 unk_01A;
    /* 0x01C */ s16 unk_01C;
    /* 0x01E */ s16 unk_01E;
    /* 0x020 */ f32 unk_020;
    /* 0x024 */ s32 unk_024;
    /* 0x028 */ s32 unk_028;
    /* 0x02C */ s32 unk_02C;
    /* 0x030 */ s32 unk_030;
    /* 0x034 */ s32 unk_034;
    /* 0x038 */ s32 unk_038;
    /* 0x03C */ s32 unk_03C;
    /* 0x040 */ s32 unk_040;
    /* 0x044 */ s32 unk_044;
    /* 0x048 */ char unk048[0x8];
    /* 0x050 */ Vtx unk_050[31 * 2];
    /* 0x430 */ unk_D_843925E0_430 unk_430[31 * 2];
} unk_D_843925E0; // size = 0xAF8

typedef struct unk_D_843975E8 {
    /* 0x00 */ f32 unk_00;
    /* 0x04 */ f32 unk_04;
    /* 0x08 */ f32 unk_08;
    /* 0x0C */ f32 unk_0C;
    /* 0x10 */ f32 unk_10;
    /* 0x14 */ f32 unk_14;
    /* 0x18 */ f32 unk_18;
    /* 0x1C */ f32 unk_1C;
    /* 0x20 */ f32 unk_20;
    /* 0x24 */ char unk24[0x4];
} unk_D_843975E8; // size = 0x28

typedef struct unk_D_84398F50_048 {
    /* 0x00 */ f32 unk_00;
    /* 0x04 */ u8 unk_04;
    /* 0x08 */ f32 unk_08;
    /* 0x0C */ f32 unk_0C;
    /* 0x10 */ Vec3f unk_10;
    /* 0x1C */ Vec3f unk_1C;
    /* 0x28 */ char unk28[0x20];
} unk_D_84398F50_048; // size = 0x48

typedef struct unk_D_84398F50 {
    /* 0x000 */ s16 unk_000;
    /* 0x002 */ s16 unk_002;
    /* 0x004 */ s16 unk_004;
    /* 0x006 */ s16 unk_006;
    /* 0x008 */ s16 unk_008;
    /* 0x00A */ Color_RGBA8 unk_00A;
    /* 0x00E */ Color_RGB8 unk_00E;
    /* 0x014 */ f32 unk_014;
    /* 0x018 */ f32 unk_018;
    /* 0x01C */ Vtx* unk_01C;
    /* 0x020 */ char unk020[0x18];
    /* 0x038 */ s32 unk_038[3];
    /* 0x044 */ char unk044[0x4];
    /* 0x048 */ unk_D_84398F50_048 unk_048[20];
} unk_D_84398F50; // size = 0x5E8

typedef struct WaterSurfaceVertex {
    /* 0x00 */ f32 unk_00;
    /* 0x04 */ f32 unk_04;
    /* 0x08 */ f32 unk_08;
    /* 0x0C */ f32 unk_0C;
    /* 0x10 */ f32 unk_10;
    /* 0x14 */ f32 unk_14;
    /* 0x18 */ s16 unk_18;
    /* 0x1A */ s16 unk_1A;
} WaterSurfaceVertex; // size = 0x1C

typedef struct WaterSurfaceData {
    /* 0x0000 */ s16 unk_0000;
    /* 0x0002 */ s16 unk_0002;
    /* 0x0004 */ s16 unk_0004;
    /* 0x0008 */ f32 unk_0008;
    /* 0x000C */ Vtx* unk_000C;
    /* 0x0010 */ Mtx* unk_0010;
    /* 0x0014 */ WaterSurfaceVertex unk_0014[16][16];
} WaterSurfaceData; // size >= 0x1C14

typedef struct unk_D_8439E680_0014 {
    /* 0x00 */ f32 unk_00;
    /* 0x04 */ f32 unk_04;
    /* 0x08 */ f32 unk_08;
    /* 0x0C */ f32 unk_0C;
    /* 0x10 */ f32 unk_10;
    /* 0x14 */ f32 unk_14;
    /* 0x18 */ s16 unk_18;
    /* 0x1A */ s16 unk_1A;
    /* 0x1C */ f32 unk_1C;
} unk_D_8439E680_0014; // size = 0x20

typedef struct WaterSurface {
    /* 0x0000 */ s16 unk_0000;
    /* 0x0002 */ s16 unk_0002;
    /* 0x0004 */ s16 unk_0004;
    /* 0x0008 */ f32 unk_0008;
    /* 0x000C */ Vtx* unk_000C;
    /* 0x0010 */ Mtx* unk_0010;
    /* 0x0014 */ unk_D_8439E680_0014 unk_0014[16][16];
} WaterSurface; // size >= 0x2014

typedef struct unk_D_843A22C0_038 {
    /* 0x00 */ f32 unk_00;
    /* 0x08 */ u8 unk_04;
    /* 0x08 */ f32 unk_08;
    /* 0x0C */ Vec3f unk_0C;
    /* 0x18 */ Vec3f unk_18;
    /* 0x24 */ Vec3f unk_24;
    /* 0x30 */ Vtx unk_30[2];
} unk_D_843A22C0_038; // size = 0x50

typedef struct unk_D_843A22C0 {
    /* 0x000 */ s16 unk_000;
    /* 0x002 */ s16 unk_002;
    /* 0x004 */ s16 unk_004;
    /* 0x006 */ s16 unk_006;
    /* 0x008 */ s16 unk_008;
    /* 0x00A */ Color_RGB8 unk_00A;
    /* 0x010 */ f32 unk_010;
    /* 0x014 */ f32 unk_014;
    /* 0x018 */ Vtx* unk_018;
    /* 0x01C */ char unk01C[0x1C];
    /* 0x038 */ unk_D_843A22C0_038 unk_038[10];
} unk_D_843A22C0; // size = 0x358

typedef struct WaterParticleParticle {
    /* 0x00 */ u8 unk_00;
    /* 0x04 */ f32 unk_04;
    /* 0x08 */ f32 unk_08;
    /* 0x0C */ Vec3f unk_0C;
    /* 0x18 */ Vec3f unk_18;
    /* 0x24 */ f32 unk_24;
    /* 0x28 */ f32 unk_28;
    /* 0x2C */ Vec3f unk_2C;
    /* 0x38 */ Vec3f unk_38;
} WaterParticleParticle; // size = 0x44

typedef struct WaterParticleEmitter {
    /* 0x000 */ s16 unk_000;
    /* 0x002 */ s16 unk_002;
    /* 0x004 */ s16 unk_004;
    /* 0x006 */ s16 unk_006;
    /* 0x008 */ Color_RGB8 unk_008;
    /* 0x00C */ f32 unk_00C;
    /* 0x010 */ f32 unk_010;
    /* 0x014 */ f32 unk_014;
    /* 0x018 */ Vtx* unk_018;
    /* 0x01C */ Vec3f unk_01C;
    /* 0x028 */ char unk028[0xC];
    /* 0x034 */ WaterParticleParticle unk_034[15];
} WaterParticleEmitter; // size = 0x430

typedef struct ParticleState {
    /* 0x00 */ u8 unk_00;
    /* 0x04 */ f32 unk_04;
    /* 0x08 */ f32 unk_08;
    /* 0x0C */ Vec3f unk_0C;
    /* 0x18 */ Vec3f unk_18;
    /* 0x24 */ f32 unk_24;
    /* 0x28 */ f32 unk_28;
    /* 0x2C */ Vec3f unk_2C;
    /* 0x38 */ Vec3f unk_38;
} ParticleState; // size = 0x44

typedef struct ParticleEmitter {
    /* 0x000 */ s16 unk_000;
    /* 0x002 */ s16 unk_002;
    /* 0x004 */ s16 unk_004;
    /* 0x006 */ s16 unk_006;
    /* 0x008 */ Color_RGB8 unk_008;
    /* 0x00C */ f32 unk_00C;
    /* 0x010 */ f32 unk_010;
    /* 0x014 */ f32 unk_014;
    /* 0x018 */ Vtx* unk_018;
    /* 0x01C */ Vec3f unk_01C;
    /* 0x028 */ char unk028[0xC];
    /* 0x034 */ ParticleEffectInstance* unk_034;
    /* 0x038 */ ParticleState unk_038[15];
} ParticleEmitter; // size = 0x434

typedef struct unk_D_843ACA10_01C {
    /* 0x00 */ u8 unk_00;
    /* 0x04 */ f32 unk_04;
    /* 0x08 */ f32 unk_08;
    /* 0x0C */ Vec3f unk_0C;
    /* 0x18 */ Vec3f unk_18;
    /* 0x24 */ f32 unk_24;
    /* 0x28 */ f32 unk_28;
    /* 0x2C */ Vec3f unk_2C;
    /* 0x38 */ Vec3f unk_38;
} unk_D_843ACA10_01C; // size = 0x44

typedef struct unk_D_843ACA10 {
    /* 0x000 */ s16 unk_000;
    /* 0x002 */ s16 unk_002;
    /* 0x004 */ s16 unk_004;
    /* 0x006 */ s16 unk_006;
    /* 0x008 */ Color_RGB8 unk_008;
    /* 0x010 */ f32 unk_00C;
    /* 0x010 */ f32 unk_010;
    /* 0x014 */ Vtx* unk_014;
    /* 0x018 */ ParticleEffectInstance* unk_018;
    /* 0x01C */ unk_D_843ACA10_01C unk_01C[15];
    /* 0x418 */ f32 unk_418;
} unk_D_843ACA10; // size = 0x41C

typedef struct unk_D_843ADA80_040 {
    /* 0x00 */ u8 unk_00;
    /* 0x04 */ f32 unk_04;
    /* 0x08 */ f32 unk_08;
    /* 0x0C */ Vec3f unk_0C;
    /* 0x18 */ Vec3f unk_18;
    /* 0x24 */ Vec3f unk_24;
    /* 0x30 */ f32 unk_30;
    /* 0x34 */ f32 unk_34;
    /* 0x38 */ Vec3f unk_38;
    /* 0x44 */ Vec3f unk_44;
} unk_D_843ADA80_040; // size = 0x50

typedef struct unk_D_843ADA80 {
    /* 0x000 */ s16 unk_000;
    /* 0x002 */ s16 unk_002;
    /* 0x004 */ s16 unk_004;
    /* 0x006 */ s16 unk_006;
    /* 0x008 */ s16 unk_008;
    /* 0x00A */ Color_RGB8 unk_00A;
    /* 0x010 */ f32 unk_010;
    /* 0x014 */ f32 unk_014;
    /* 0x018 */ f32 unk_018;
    /* 0x01C */ char unk01C[0x4];
    /* 0x020 */ Vtx* unk_020;
    /* 0x024 */ Vec3f unk_024;
    /* 0x030 */ char unk030[0x10];
    /* 0x040 */ unk_D_843ADA80_040 unk_040[10];
} unk_D_843ADA80; // size = 0x360

typedef struct WaterParticleVertex {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ u8 unk_04;
    /* 0x08 */ f32 unk_08;
    /* 0x0C */ f32 unk_0C;
    /* 0x10 */ Vec3f unk_10;
    /* 0x1C */ f32 unk_1C;
    /* 0x20 */ f32 unk_20;
    /* 0x24 */ f32 unk_24;
} WaterParticleVertex; // size = 0x28

typedef struct TextureTileInfo {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ s16 unk_08;
    /* 0x0A */ s16 unk_0A;
} TextureTileInfo; // size = 0xC

typedef struct CombineParams {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ s32 unk_10;
    /* 0x14 */ s32 unk_14;
    /* 0x18 */ s32 unk_18;
    /* 0x1C */ s32 unk_1C;
} CombineParams; // size = 0x20

typedef struct ColorBlendInfo {
    /* 0x00 */ Color_RGBA8 unk_00;
    /* 0x04 */ u8 unk_04;
} ColorBlendInfo; // size = 0x8

typedef struct WaterParticleSystem {
    /* 0x000 */ s16 unk_000;
    /* 0x002 */ s16 unk_002;
    /* 0x004 */ s16 unk_004;
    /* 0x008 */ f32 unk_008;
    /* 0x00C */ f32 unk_00C;
    /* 0x010 */ f32 unk_010;
    /* 0x014 */ f32 unk_014;
    /* 0x018 */ Vtx* unk_018;
    /* 0x01C */ s32 unk_01C;
    /* 0x020 */ s32 unk_020;
    /* 0x024 */ CombineParams unk_024;
    /* 0x044 */ CombineParams unk_044;
    /* 0x064 */ TextureTileInfo unk_064;
    /* 0x070 */ TextureTileInfo unk_070;
    /* 0x07C */ ColorBlendInfo unk_07C;
    /* 0x081 */ ColorBlendInfo unk_081;
    /* 0x086 */ Color_RGBA8 unk_086;
    /* 0x08C */ f32 unk_08C;
    /* 0x090 */ f32 unk_090;
    /* 0x094 */ s16 unk_094;
    /* 0x096 */ char unk096[0x1A];
    /* 0x0B0 */ WaterParticleVertex unk_0B0[10];
} WaterParticleSystem; // size = 0x240

typedef struct Particle {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ f32 unk_08;
    /* 0x0C */ Vec3f unk_0C;
} Particle; // size = 0x18

typedef struct unk_D_843C49C0 {
    /* 0x000 */ s16 unk_000;
    /* 0x002 */ char pad002[2];
    /* 0x004 */ Particle unk_004[20];
} unk_D_843C49C0; // size = 0x1E4

typedef struct unk_D_843C3508_0A4 {
    /* 0x00 */ f32 unk_00;
    /* 0x04 */ f32 unk_04;
    /* 0x08 */ f32 unk_08;
    /* 0x0C */ Vec3f unk_0C;
    /* 0x18 */ Vec3f unk_18;
} unk_D_843C3508_0A4; // size = 0x24

typedef struct unk_D_843C3508 {
    /* 0x000 */ s16 unk_000;
    /* 0x002 */ s16 unk_002;
    /* 0x004 */ s16 unk_004;
    /* 0x006 */ s16 unk_006;
    /* 0x008 */ ColorBlendInfo unk_008;
    /* 0x00D */ ColorBlendInfo unk_00D;
    /* 0x014 */ f32 unk_014;
    /* 0x018 */ f32 unk_018;
    /* 0x01C */ s16 unk_01C;
    /* 0x020 */ s32 unk_020;
    /* 0x024 */ s32 unk_024;
    /* 0x028 */ CombineParams unk_028;
    /* 0x048 */ CombineParams unk_048;
    /* 0x068 */ TextureTileInfo unk_068;
    /* 0x074 */ TextureTileInfo unk_074;
    /* 0x080 */ f32 unk_080;
    /* 0x084 */ f32 unk_084;
    /* 0x088 */ Vtx* unk_088;
    /* 0x08C */ char unk08C[0x18];
    /* 0x0A4 */ unk_D_843C3508_0A4 unk_0A4[20];
} unk_D_843C3508; // size = 0x374

typedef struct StatStageMultiplier {
    /* 0x00 */ u8 unk_00;
    /* 0x01 */ u8 unk_01;
} StatStageMultiplier; // size = 0x2

typedef struct TypeEffectivenessEntry {
    /* 0x00 */ u8 unk_00;
    /* 0x01 */ u8 unk_01;
    /* 0x02 */ u8 unk_02;
} TypeEffectivenessEntry; // size = 0x3

typedef struct unk_D_843C60AC {
    /* 0x00 */ u8 unk_00;
    /* 0x01 */ u8 unk_01;
    /* 0x02 */ u8 unk_02;
    /* 0x03 */ u8 unk_03;
    /* 0x04 */ u8 unk_04;
    /* 0x05 */ u8 unk_05[1];
    /* 0x0C */ char unk06[0xC];
    /* 0x12 */ unk_D_800FCB18 unk_12;
} unk_D_843C60AC; // size = 0x76

typedef struct unk_D_843C60A4 {
    /* 0x00 */ u8 unk_00;
    /* 0x01 */ u8 unk_01[2];
    /* 0x03 */ u8 unk_03;
    /* 0x04 */ u8 unk_04[2];
    /* 0x06 */ u8 unk_06;
    /* 0x07 */ u8 unk_07[1];
    /* 0x08 */ u8 unk_08;
    /* 0x09 */ u8 unk_09;
    /* 0x0A */ u8 unk_0A[1];
    /* 0x0B */ char unk0B[0x5];
    /* 0x10 */ u8 unk_10;
    /* 0x11 */ u8 unk_11;
    /* 0x12 */ u8 unk_12;
    /* 0x13 */ u8 unk_13;
    /* 0x14 */ unk_D_843C60AC unk_14[1];
} unk_D_843C60A4; // size >= 0x8A

typedef struct unk_D_843C5568 {
    /* 0x000 */ u8 unk_000;
    /* 0x001 */ u8 unk_001;
    /* 0x002 */ u8 unk_002;
    /* 0x003 */ u8 unk_003;
    /* 0x004 */ u8 unk_004;
    /* 0x005 */ u8 unk_005;
    /* 0x006 */ u8 unk_006;
    /* 0x007 */ u8 unk_007;
    /* 0x008 */ u8 unk_008;
    /* 0x009 */ char unk009[0x3];
    /* 0x00C */ u8 unk_00C[1];
    /* 0x00D */ char unk00D[0x5];
    /* 0x012 */ u8 unk_012;
    /* 0x013 */ char unk013[0x3];
    /* 0x016 */ unk_D_843C60AC unk_016[1];
    /* 0x08C */ char unk08C[0x510];
} unk_D_843C5568; // size = 0x59C

typedef struct unk_func_843794CC {
    /* 0x00 */ u8 unk_00;
    /* 0x01 */ u8 unk_01;
    /* 0x02 */ u8 unk_02;
    /* 0x03 */ u8 unk_03;
    /* 0x04 */ u8 unk_04;
    /* 0x05 */ u8 unk_05;
    /* 0x06 */ u8 unk_06;
    /* 0x07 */ u8 unk_07;
    /* 0x08 */ u8 unk_08;
    /* 0x0A */ s16 unk_0A;
    /* 0x0C */ s16 unk_0C;
    /* 0x0E */ s16 unk_0E;
    /* 0x10 */ s16 unk_10;
    /* 0x12 */ s16 unk_12;
    /* 0x14 */ s16 unk_14;
    /* 0x16 */ s16 unk_16;
    /* 0x18 */ s16 unk_18;
    /* 0x1A */ s16 unk_1A;
    /* 0x1C */ s16 unk_1C;
    /* 0x1E */ s16 unk_1E;
    /* 0x20 */ s16 unk_20;
    /* 0x24 */ s32 unk_24;
    /* 0x28 */ s32 unk_28;
} unk_func_843794CC; // size = 0x2C

typedef struct unk_D_843C5310 {
    /* 0x00 */ u8 unk_00[1];
    /* 0x01 */ char unk01[9];
    /* 0x0A */ u8 unk_0A[1];
    /* 0x0B */ char unk0B[0x15];
} unk_D_843C5310; // size = 0x20

typedef struct unk_D_843C60C0 {
    /* 0x00 */ u8 unk_00;
    /* 0x01 */ u8 unk_01;
    /* 0x02 */ u8 unk_02;
    /* 0x04 */ s32 unk_04[1];
    /* 0x08 */ char unk08[0xC];
} unk_D_843C60C0; // size = 0x14

typedef struct unk_D_843C60F0_00C {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ u8 unk_04;
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
    /* 0x10 */ u8 unk_10;
    /* 0x11 */ char unk11[0x3];
} unk_D_843C60F0_00C; // size = 0x14

typedef struct unk_D_843C60F0 {
    /* 0x00 */ u8 unk_00;
    /* 0x01 */ u8 unk_01;
    /* 0x02 */ u8 unk_02;
    /* 0x03 */ char unk03[0x9];
    /* 0x0C */ unk_D_843C60C0 unk_0C[3];
} unk_D_843C60F0; // size >= 0x48

typedef struct unk_D_843C6148 {
    /* 0x00 */ u8 unk_00;
    /* 0x01 */ u8 unk_01;
    /* 0x02 */ u8 unk_02;
    /* 0x03 */ u8 unk_03;
    /* 0x04 */ u8 unk_04;
    /* 0x05 */ u8 unk_05;
    /* 0x06 */ char unk06[0x2];
} unk_D_843C6148; // size <= 0x8

typedef struct unk_func_8438220C {
    /* 0x00 */ u8 unk_00;
    /* 0x01 */ char unk01[0x3];
    /* 0x04 */ unk_func_843794CC unk_04[4];
    /* 0xB4 */ u8 unk_B4;
    /* 0xB8 */ s32 unk_B8;
} unk_func_8438220C; // size = 0xBC

typedef struct unk_func_8437F85C_arg3 {
    /* 0x00 */ u8 unk_00[3][3];
} unk_func_8437F85C_arg3; // size = 0x3

extern unk_D_8438E7B0* gAnimDataByPlayer[];
extern unk_D_8438FF70* gAnimDataSetB[];
extern unk_D_8438FF70* gAnimDataSetC[];
extern unk_D_84384588* gAnimExtraDataByPlayer[];
extern u8 gSpecialMoveIDs[];
extern u8 D_843845F0;
extern u8 D_843845F4;
extern u8 D_843845F8;
extern u8 D_843845FC[];
extern s16 gAnimLookupTable[];
extern unk_D_843847BC D_843847BC[2];
extern unk_D_86B0C160 gCameraFovyPresetRandom[3];
extern unk_D_86B0C160 gCameraFovyPresetSpecial[2];
extern unk_D_86B0C160 gCameraPosB;
extern unk_D_86B0C160 gCameraPosD;
extern unk_D_86B0C160 gCameraPosC;
extern unk_D_86B0C160 gCameraPosA;
extern unk_D_86B0C160 D_843849C0[];
extern unk_D_86B0C160 D_84384AF8;
extern unk_D_86B0C160 D_84384B2C[];
extern Vec3f gCameraOffsetTable[];
extern unk_D_84385384_func gAnimStateIdle;
extern unk_D_84385384 gMoveAnimData[];
extern Vec3f gCameraFarSettings;
extern Vec3f gCameraCloseSettings;
extern u32 gMessageIdLookup[];
extern Vtx D_84385C80[];
extern Vtx D_84385CC0[];
extern Vtx D_84385D00[];
extern Vtx D_84385D40[];
extern Vtx D_84385DC0[];
extern Vtx D_84385E00[];
extern ParticleEffectData gParticleEffectData[86];
extern func_D_84390320 gStateCallbackTable[];
extern func_D_84390320 gParticleCallbackTable[];
extern func_D_84390320 gStateEnterCallbackTable[];
extern func_D_84390320 gParticleEnterCallbackTable[];
extern func_D_84390320 gStateExitCallbackTable[];
extern func_D_84390320 gParticleExitCallbackTable[];
extern Gfx gWaterParticleQuadDL[];
extern u32 gBeamTexture[];
extern Gfx gParticleQuadDL[];
extern u8 D_8438AC60[];
extern StatStageMultiplier gStatStageMultipliers[];
extern u8 gStatStageMultipliersAlt[];
extern u8 gTypeEffectivenessTable[];
extern u8* gPokemonPortraitImage0;
extern u8* gPokemonPortraitImage1;

extern u8 gSpecialFlag;
extern u8 D_843C4DA5;
extern u8 D_843C4DA9;
extern u8 D_843C4DAA;
extern s32 gAnimTimer;
//extern unk_D_843C4E44 gIsBattleMode;
extern u8 gIsBattleMode;
extern u8 gAnimStateFlag;
extern u16 gCurrentDamage;
extern unk_D_800FCB18* gCurrentBattleEntity;
extern unk_D_800FCB18* gDefenderBattleEntity;


extern unk_D_84390010* D_84390010[2];
extern unk_D_84390010* gPrimaryPokemonEntity;
extern unk_D_84390010* gPokemonEntityUnused;
extern unk_D_84390028 gPokemonModelDimensions[2];
extern f32 gPlayerScaleFactors[];
extern char** gMessageBank_0x1E;
extern char** gMessageBank_0x24;
extern char** gPokemonMessageBank;
extern char** gMessageBank_0x29;
extern char** gMarqueeMessageBank;
extern f32 gHPBarTimer;
extern f32 gPhaseTimer;
extern u8 gBattleResultPhase;
extern s32 gBattleInitFlag;
extern unk_D_84390178 gBattleInitStruct;
extern Vec3f gCameraPosition;
extern unk_D_843901A0* D_843901A0;
extern unk_D_843901B0 gCameraPreset;
extern unk_D_84390010* gOpponentPlayer;
extern unk_D_84390010* gCurrentPlayer;
extern s32 gTotalMoveCount;
extern s32 gCurrentMoveIndex;
extern s32 gInitialMoveIndex;
extern unk_D_84390240 gBattleState;
extern s32 D_84390288;
extern s32 gPanelDrawCount;
extern s32 D_843902A8;
extern s16 gParticleTexture_Default;
extern s16 gParticleEffectPrimaryId;
extern unk_D_84390010* gParticleEffectEntityA;
extern unk_D_84390010* gParticleEffectData_42;
extern unk_D_84390010* gParticleEffectEntityB;
extern s32 gGameStateFlag;
extern s32 D_843902F8;
extern func_D_84390300 gCameraCallbackFuncs[8];
extern func_D_84390320 gCameraUpdateFuncs[8];
extern s32 D_84390340;
extern Vec3f gCameraLookAtPos;
extern s16 gSavedPrimColorR;
extern s16 gSavedPrimColorG;
extern s16 gSavedPrimColorB;
extern s16 D_84390380;
extern s16 gPrimColorR;
extern s16 gPrimColorG;
extern s16 gPrimColorB;
extern s16 gPrimColorA;
extern s16 gEnvColorR;
extern s16 gEnvColorG;
extern s16 gEnvColorB;
extern s16 gEnvColorA;
extern s16 gFogColorR;
extern s16 gFogColorG;
extern s16 gFogColorB;
extern s16 gFogColorA;
extern s16 gBlendColorR;
extern s16 gBlendColorG;
extern s16 gBlendColorB;
extern s16 gBlendColorA;
extern f32 D_84392058[26];
extern u8* gWaterTexture[256];
extern s16 gMessageBuffer[0x10];
extern arg1_func_80019420* gMessageStringLists[40];



s32 CameraNode_UpdateCallback(s32 arg0, GraphNode* arg1);
s32 CameraNode_GetPanTiltPositive(s32 arg0, unk_D_86002F34_alt18* arg1);
s32 CameraNode_GetPanTiltNegative(s32 arg0, unk_D_86002F34_alt18* arg1);
s32 FragmentNode_SetScaleAndColor(s32 arg0, Fragment2_1GraphNode* arg1);
void ColorRectNode_SetColor(u8 arg0, u8 arg1, u8 arg2);
void FragmentNode_SetGlobalScale(f32 arg0);
u16 Color_ModulateWithGlobal(u16 arg0);
void RenderBackgroundScreen(void);
void FramebufferNode_Init(GraphNode* arg0, FramebufferImage* arg1);
void Gfx_DrawClippedTextureRect(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void Gfx_LoadTextureDrawClippedRect(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u8* arg4, s32 arg5);
void RenderPokemonPortraits(GraphNode* arg0, FramebufferImage* arg1);
void PokemonSelection_ClearFlags(void);
void PokemonSelection_AssignIndices(void);
void func_84300E78(void);
void func_84300E80(void);
s32 func_84300E88(s32 arg0);
s32 func_84300FBC(s32 arg0);
void func_84301094(void);
s32 PokemonSelectScreen_Update(s32 arg0);
void func_8430123C(u8* arg0, s32 arg1);
void func_8430128C(void);
void PokemonSelection_InitPlayer(unk_D_800AE540_1194* arg0, unk_D_86002F30* arg1);
void BattleScreen_Init(Stage* arg0);
void func_84301A24(void);
s32 BattleScreen_Run(s32 arg0, unk_D_800AE540* arg1);

void AnimStateQueue_ResetAll(void);
void func_84301B48(unk_D_84390010* arg0, s32 arg1);
void AnimChannel_StartMoveAction(unk_D_84390010* arg0, s32 arg1);
void AnimChannel_StartSpecialMoveAction(unk_D_84390010* arg0, s32 arg1);
void AnimChannel_StartAnotherMoveAction(unk_D_84390010* arg0, s32 arg1);
void AnimChannel_ResetIfNeeded(unk_D_84390010* arg0);
void AnimChannel_SetupAndTrigger(unk_D_84390010* arg0);
void AnimChannel_CheckModelBaseY(unk_D_84390010* arg0);
void Anim_ResetPlayer(unk_D_84390010* arg0);
void Anim_ResetAllPlayers(unk_D_84390010* arg0);
void func_84301F2C(unk_D_84390010* arg0);
void func_84301F80(unk_D_84390010* arg0);
s32 AnimChannel_GetFlagsFB0(unk_D_84390010* arg0);
s32 AnimChannel_FinishAndGetFlagsFC0(unk_D_84390010* arg0);
s32 AnimChannel_GetFlagsFF0(unk_D_84390010* arg0);
s32 AnimChannel_CheckAndReset(unk_D_84390010* arg0);
void AnimChannel_HandleBattleState(unk_D_84390010* arg0);
void AnimChannel_TriggerMoveEffect(unk_D_84390010* arg0);
void AnimChannel_TriggerGenericEffect(unk_D_84390010* arg0);
void AnimChannel_SetFlags28(unk_D_84390010* arg0);
void AnimChannel_SetTransformData(unk_D_84390010* arg0);
s32 FindIndexInArray(u16 arg0, u8* arg1, s32 arg2);
void ApplyStatMasksAndConditions(unk_D_84390010* arg0, u16 arg1, unk_D_84390010_94C* arg2, unk_D_84390010_94C* arg3);
void ResetAllStatFlags(unk_D_84390010* arg0);
void DMATransfer_MoveData(u8 arg0, u32 arg1);
void DMATransfer_MoveDataPair(s32 arg0, unk_D_84390010_94C* arg1, unk_D_84390010_94C* arg2);
void LoadPlayerAnimationData(unk_D_84390010* arg0, s32 arg1);
void Pokemon_HandleFaint(unk_D_84390010* arg0);
void Pokemon_StartMoveAnimation(unk_D_84390010* arg0);
void Pokemon_HandleMoveCompletion(unk_D_84390010* arg0);
void AnimChannel_CheckAndAdvance(unk_D_84390010* arg0);
void AnimChannel_HandleSpecialMoves(unk_D_84390010* arg0);
void AnimChannel_SetSubStateIfNeeded(unk_D_84390010* arg0);
void Pokemon_GenericActionTrigger(unk_D_84390010* arg0);
void Pokemon_PlayMoveEffect(unk_D_84390010* arg0);
void Pokemon_TriggerAnimIfUnlocked(unk_D_84390010* arg0);
void Pokemon_HandleMoveEnd(unk_D_84390010* arg0);
void Pokemon_HandleSpecialMoveEnd(unk_D_84390010* arg0);
void Pokemon_EnterBattleState(unk_D_84390010* arg0);
void Pokemon_HandleSwitchIn(unk_D_84390010* arg0);
void Pokemon_HandleSwitchOut(unk_D_84390010* arg0);
void Pokemon_StartBattleIntro(unk_D_84390010* arg0);
s32 Pokemon_CheckAnimStateC(unk_D_84390010* arg0);
s32 Pokemon_CheckAnimState0(unk_D_84390010* arg0);
void Pokemon_ResetAnimAndTrigger(unk_D_84390010* arg0);
void Pokemon_HandleSpecialMoveAnimation(unk_D_84390010* arg0);
void PlayBattleMusicIfReady(unk_D_84390010* arg0);
void PlayBattleMusicAndSound(unk_D_84390010* arg0);
void PlayBattleMusicAndSoundAlt(unk_D_84390010* arg0);
void Pokemon_HandleMoveHit(unk_D_84390010* arg0);
void Pokemon_HandleMoveHitSimple(unk_D_84390010* arg0);
void Pokemon_HandleFaintEffect(unk_D_84390010* arg0);
void Pokemon_ClearTransformFlag(unk_D_84390010* arg0);
void Pokemon_TriggerAnimByLookup(unk_D_84390010* arg0);
void Pokemon_HandleSpecialMoveEffect(unk_D_84390010* arg0);
void Pokemon_SetSpecialAnimChannel(unk_D_84390010* arg0);
void Pokemon_HandleSpecialCondition(unk_D_84390010* arg0);
void Pokemon_TriggerAnimIfMatch(unk_D_84390010* arg0);
void Pokemon_PlaySoundBasedOnFlags(unk_D_84390010* arg0);
void Pokemon_HandleGroundedAnim(unk_D_84390010* arg0);
void Pokemon_HandleAirborneAnim(unk_D_84390010* arg0);
void CheckAnimStateCompletion(unk_D_84390010* arg0);
void UpdateAnimChannelForEntity(unk_D_84390010* arg0);
void ProcessAnimStateMatch(unk_D_84390010* arg0);
s32 GetAnimStateResultCode(unk_D_84390010* arg0);
void TriggerAnimStateSound(unk_D_84390010* arg0);
void ApplyAnimStateEffect(unk_D_84390010* arg0);
void Anim_NullHandler(unk_D_84390010* arg0);
void ReplaceAnimQueueEntry(unk_D_84390010* arg0, unk_D_84385384_func arg1);
void ResetAnimChannelToDefault(unk_D_84390010* arg0);
void ExecuteAnimStateHandlers(unk_D_84390010* arg0, s32 arg1);
void Anim_ProcessQueue(void);
void ClearAnimFlagIfState6A(unk_D_84390010* arg0);
void PlayAnimSoundIfApplicable(unk_D_84390010* arg0, s32 arg1);
s32 TryPlayAnimSoundAndSetState(unk_D_84390010* arg0, s32 arg1, s32 arg2);
void PlayAnimSoundSimple(unk_D_84390010* arg0, s32 arg1, s32 arg2);
s32 IsAnimStateLocked(unk_D_84390010* arg0);
s32 CanAnimProceed(unk_D_84390010* arg0, s32 arg1);
s32 CanAnimProceedWithChannel(unk_D_84390010* arg0, s32 arg1);
s32 EvaluateAnimStateAgainstBattle(unk_D_84390010* arg0, s32 arg1);
s32 EvaluateAnimStateWithAlternateChannel(unk_D_84390010* arg0, s32 arg1);
s32 CanAnimChannelA80Proceed(unk_D_84390010* arg0, s32 arg1);
void MaybeTriggerSpecialAnimEffect(unk_D_84390010* arg0);
void SetEntityAnimFlags(unk_D_84390010* arg0, u16 arg1);
s32 ClearEntityAnimFlags(unk_D_84390010* arg0, u16 arg1);
void UpdateEntityModelForAnimFlags(unk_D_84390010* arg0);
void ProcessEntityAnimFlagUpdates(void);
void PrepareEntityAnimState(unk_D_84390010* arg0);
void AdjustModelBaseYForFlag8(unk_D_84390010* arg0);
void HandleFlag4000AnimEffect(unk_D_84390010* arg0);
void ApplyFlag4000EffectToEntity(unk_D_84390010* arg0);
void UpdateEntityStateByMode(unk_D_84390010* arg0);
void ProcessEntityPostMoveEffects(unk_D_84390010* arg0);
void TriggerStatusEffectSound(unk_D_84390010* arg0);
void AllocateEntityStruct(unk_D_800AE540_1194* arg0, s32 arg1);
void InitializeBattleEntities(unk_D_800AE540_1194* arg0);
void SetupEntityController(unk_D_84390010* arg0);
void InitEntityGraphNode(unk_D_84390010* arg0);
void InitEntitySubObjectGraph(unk_D_84390010* arg0);
void InitEntityChildNodes(unk_D_84390010* arg0, s32* arg1);
void InitEntityFragmentNode(unk_D_84390010* arg0);
void InitializeBattleScene(unk_D_800AE540_1194* arg0);
void SetEntityOrientation(unk_D_84390010* arg0, unk_D_84390010* arg1, s32 arg2);
void InitMessageBanksAndAnimQueue(unk_D_800AE540_1194* arg0);
void ResetEntityAnimStates(unk_D_84390010* arg0, unk_D_84390010* arg1);
s32 BattleInitDispatch(s32 arg0, unk_D_800AE540_1194* arg1);
void func_84307414(unk_D_84390010* arg0);
void func_8430741C(unk_D_84390010* arg0);
void func_84307424(unk_D_84390010* arg0);
void func_8430742C(unk_D_84390010* arg0);
void func_84307434(unk_D_84390010* arg0);
void func_8430743C(unk_D_84390010* arg0);
void func_84307444(unk_D_84390010* arg0);
void func_8430744C(unk_D_84390010* arg0);
void func_84307454(unk_D_84390010* arg0);
void func_8430745C(unk_D_84390010* arg0);
void func_84307464(unk_D_84390010* arg0);
void func_8430746C(unk_D_84390010* arg0);
void func_84307474(unk_D_84390010* arg0, s32 arg1);
void func_84307480(unk_D_84390010* arg0, s32 arg1);
void func_8430748C(unk_D_84390010* arg0);


void TriggerPokemonAnimAndAction(unk_D_84390010* arg0);
void ClearPokemonActiveFlag(unk_D_84390010* arg0);
void SetPokemonActiveFlag(unk_D_84390010* arg0);
void ClearAllPokemonActiveFlags(void);
void SetAllPokemonActiveFlags(void);
void func_8430753C(unk_D_84390010_728_0168* arg0);
void LoadPokemonModelParams(unk_D_84390010* arg0);
void SetupPokemonForBattle(unk_D_84390010* arg0, unk_D_84390010* arg1);
void func_84307630(void);
void UpdatePokemonTransform(unk_D_84390010* arg0);
void RefreshPokemonTransform(unk_D_84390010* arg0);
void AssignPokemonModels(CameraStruct* arg0, unk_D_84390010* arg1, CameraStruct* arg2, unk_D_84390010* arg3);
void UpdatePokemonTurn(unk_D_84390010* arg0, s32 arg1);
void ResetPokemonTurn(unk_D_84390010* arg0, s32 arg1);
void ProcessPokemonTurnState(unk_D_84390010* arg0);
void UpdatePokemonTurnIfBattleActive(unk_D_84390010* arg0, unk_D_84390010* arg1);
s32 HandleBattlePhase(s32 arg0, CameraStruct* arg1, CameraStruct* arg2);

s32 func_84307AE0(u8 arg0, u8* arg1, s32 arg2);
PokemonData* GetCurrentPokemonData(unk_D_84390010* arg0);
s32 func_84307B60(unk_D_84390010* arg0);
f32 GetModelBaseY(unk_D_84390010* arg0);
f32 GetModelWidth(unk_D_84390010* arg0);
f32 GetModelHeight(unk_D_84390010* arg0);
f32 GetModelDepth(unk_D_84390010* arg0);
void UpdateEntityBasePosition(unk_D_84390010* arg0);
f32 GetEntityXOffset(unk_D_84390010* arg0);
void SetEntityScale(unk_D_84390010* arg0, f32 arg1);
s32 func_84307EC4(unk_D_84390010* arg0);
s32 func_84307EE0(unk_D_84390010* arg0);
s32 IsPrimaryEntity(unk_D_84390010* arg0);
u8 func_84307F24(unk_D_84390010* arg0);
u8 func_84307F68(unk_D_84390010* arg0);
s16 func_84307FAC(unk_D_84390010* arg0);
s32 func_84307FE0(unk_D_84390010* arg0);
f32 func_84308014(unk_D_84390010* arg0);
f32 func_84308058(unk_D_84390010* arg0);
s16 GetCurrentMoveId(unk_D_84390010* arg0);
void func_84308094(unk_D_84390010* arg0, Vec3f* arg1);
void func_84308148(unk_D_84390010* arg0, Vec3s* arg1);
u16 GetCurrentHP(unk_D_84390010* arg0);
s16 GetPlayerSideYaw(unk_D_84390010* arg0);
s32 GetSpeciesOfPlayerIndex(s32 arg0);
s32 GetSpecies(unk_D_84390010* arg0);
u8 func_843081C4(unk_D_84390010* arg0);
void GetEntityPosition(unk_D_84390010* arg0, Vec3f* arg1);
void GetEntityCenterPosition(unk_D_84390010* arg0, Vec3f* arg1);
void func_843083A0(unk_D_84390010* arg0, Vec3f* arg1);
void func_84308520(unk_D_84390010* arg0, Vec3f* arg1);
f32 func_84308548(unk_D_84390010* arg0);
f32 func_84308598(unk_D_84390010* arg0);
unk_D_86002F58_004_000_004* func_843085C4(unk_D_84390010* arg0, s32 arg1);
s32 func_843085E0(unk_D_84390010* arg0, UNUSED s32 arg1);
char* GetPokemonMessageString(unk_D_84390010* arg0);
u8* GetPokemonName(unk_D_84390010* arg0);
void func_84308654(unk_D_84390010* arg0, s32 arg1, s32 arg2);
void func_84308660(unk_D_84390010* arg0, unk_D_84390010* arg1);
void func_843087F8(unk_D_84390010* arg0);
void func_8430897C(unk_D_84390010* arg0);
void func_843089DC(unk_D_84390010* arg0, s32 arg1);
void func_843089F4(unk_D_84390010* arg0, s32 arg1);
void func_843089FC(unk_D_84390010* arg0, Controller* arg1);
void func_84308A04(unk_D_84390010* arg0, s32 arg1);
s32 func_84308A4C(unk_D_84390010* arg0);
s32 func_84308BD0(unk_D_84390010* arg0);
s32 func_84308D54(unk_D_84390010* arg0);
u8 func_84308D90(unk_D_800AE540_0004* arg0);
s32 func_84308D98(unk_D_84390010* arg0);
void func_84308DB8(unk_D_84390010* arg0, unk_D_84390010* arg1, s32 arg2, s32 arg3);
void func_84308ED4(unk_D_84390010* arg0, unk_D_84390010_728* arg1, s16 arg2);
void func_84308F94(unk_D_84390010* arg0, s16 arg1);
void func_84309110(unk_D_84390010* arg0);
void func_84309168(unk_D_84390010* arg0);
void func_8430920C(unk_D_84390010* arg0);
void func_843092B4(unk_D_84390010* arg0);
void func_84309328(unk_D_84390010* arg0);
void func_84309368(unk_D_84390010* arg0);


void Entity_SetLaunchVelocity(unk_D_84390010* arg0, f32 arg1, s16 arg2);
void Entity_UpdateMovement(unk_D_84390010* arg0, unk_D_84390010* arg1, f32 arg2, f32 arg3, s32 arg4);
void Entity_UpdateMovementFast(UNUSED unk_D_84390010* arg0, unk_D_84390010* arg1, f32 arg2, f32 arg3, s32 arg4, s32 arg5);
void Entity_ResetSubObjectFlags(unk_D_84390010* arg0);
void Entity_InitSubObjects(unk_D_84390010* arg0);
void Entity_AnimateSubObjects(unk_D_84390010* arg0);
void Entity_ActivateSubObjects(unk_D_84390010* arg0);
s32 Entity_ScaleSubObjects(unk_D_84390010* arg0);
void Entity_SetSubObjectCameraOffsets(unk_D_84390010* arg0);
void Entity_UpdateCameraFromSubObject(unk_D_84390010* arg0, s16 arg1);
void func_84309F0C(unk_D_84390010* arg0);
void Entity_LaunchProjectile(UNUSED unk_D_84390010* arg0, unk_D_84390010* arg1);
void Entity_HandleProjectileLanding(unk_D_84390010* arg0, unk_D_84390010* arg1);
void Entity_StateMachine_Dispatch(unk_D_84390010* arg0, unk_D_84390010* arg1);
void func_8430A0E4(UNUSED unk_D_84390010* arg0, unk_D_84390010* arg1);
void func_8430A17C(unk_D_84390010* arg0, unk_D_84390010* arg1);
void func_8430A22C(unk_D_84390010* arg0, unk_D_84390010* arg1);
void func_8430A280(UNUSED unk_D_84390010* arg0, unk_D_84390010* arg1);
void func_8430A308(unk_D_84390010* arg0, unk_D_84390010* arg1);
void func_8430A390(unk_D_84390010* arg0, unk_D_84390010* arg1);
void func_8430A3E4(UNUSED unk_D_84390010* arg0, unk_D_84390010* arg1);
void func_8430A464(unk_D_84390010* arg0, unk_D_84390010* arg1);
void func_8430A4E0(UNUSED unk_D_84390010* arg0, UNUSED unk_D_84390010* arg1);
void func_8430A4EC(unk_D_84390010* arg0, unk_D_84390010* arg1);
s32 func_8430A558(unk_D_84390010* arg0, s16 arg1, s16 arg2);
void func_8430A5D4(UNUSED unk_D_84390010* arg0, unk_D_84390010* arg1);
void func_8430A618(unk_D_84390010* arg0, unk_D_84390010* arg1);
void func_8430A6AC(unk_D_84390010* arg0, unk_D_84390010* arg1);
void func_8430A7BC(unk_D_84390010* arg0, unk_D_84390010* arg1);
void func_8430A828(UNUSED unk_D_84390010* arg0, unk_D_84390010* arg1);
void func_8430A848(unk_D_84390010* arg0, unk_D_84390010* arg1);
void func_8430A8DC(unk_D_84390010* arg0, unk_D_84390010* arg1);
void func_8430AA18(unk_D_84390010* arg0, unk_D_84390010* arg1);
void func_8430AA84(unk_D_84390010* arg0, unk_D_84390010* arg1);
void func_8430AB00(unk_D_84390010* arg0, unk_D_84390010* arg1);
void func_8430ABF0(unk_D_84390010* arg0, unk_D_84390010* arg1);
void func_8430AD10(unk_D_84390010* arg0, unk_D_84390010* arg1);
void func_8430AD7C(unk_D_84390010* arg0, unk_D_84390010* arg1);
void func_8430ADE8(UNUSED unk_D_84390010* arg0, unk_D_84390010* arg1);
void func_8430AE3C(unk_D_84390010* arg0, unk_D_84390010* arg1);
void func_8430AE90(unk_D_84390010* arg0);
void func_8430AF08(unk_D_84390010* arg0, unk_D_84390010* arg1);
void func_8430AF80(UNUSED unk_D_84390010* arg0, unk_D_84390010* arg1);
void func_8430B104(unk_D_84390010* arg0, unk_D_84390010* arg1);
void func_8430B158(unk_D_84390010* arg0, unk_D_84390010* arg1);
void func_8430B1B8(unk_D_84390010* arg0, unk_D_84390010* arg1);
void func_8430B244(unk_D_84390010* arg0, unk_D_84390010* arg1);
void func_8430B298(UNUSED unk_D_84390010* arg0, unk_D_84390010* arg1);
void func_8430B2AC(unk_D_84390010* arg0, UNUSED unk_D_84390010* arg1);
void func_8430B374(unk_D_84390010* arg0, unk_D_84390010* arg1);
void func_8430B3C8(unk_D_84390010* arg0, unk_D_84390010* arg1);
void func_8430B40C(unk_D_84390010* arg0, unk_D_84390010* arg1);
void func_8430B550(unk_D_84390010* arg0, unk_D_84390010* arg1);
void func_8430B68C(unk_D_84390010* arg0, unk_D_84390010* arg1);
void func_8430B6F8(unk_D_84390010* arg0, unk_D_84390010* arg1);
void func_8430B734(unk_D_84390010* arg0, unk_D_84390010* arg1);
void func_8430B8FC(unk_D_84390010* arg0, unk_D_84390010* arg1);
void func_8430B950(UNUSED unk_D_84390010* arg0, unk_D_84390010* arg1);
void func_8430B968(unk_D_84390010* arg0, unk_D_84390010* arg1);
void func_8430BAB8(unk_D_84390010* arg0, unk_D_84390010* arg1);
void func_8430BB0C(UNUSED unk_D_84390010* arg0, unk_D_84390010* arg1);
void func_8430BB24(unk_D_84390010* arg0, unk_D_84390010* arg1);
void func_8430BBE4(unk_D_84390010* arg0, unk_D_84390010* arg1);
void func_8430BC38(UNUSED unk_D_84390010* arg0, UNUSED unk_D_84390010* arg1);
void func_8430BC44(s32 arg0);
void func_8430BD9C(unk_D_84390010* arg0, u8 arg1, u8 arg2);
void func_8430BDB0(unk_D_84390010* arg0);
void func_8430BDBC(unk_D_84390010* arg0, f32 arg1, s16 arg2);
void func_8430BE08(unk_D_84390010* arg0, unk_D_84390010* arg1, f32 arg2, f32 arg3, s32 arg4);
void func_8430BEC0(unk_D_84390010* arg0, unk_D_84390010* arg1);
void func_8430BF3C(unk_D_84390010* arg0, unk_D_84390010* arg1);
void func_8430BFB0(unk_D_84390010* arg0, unk_D_84390010* arg1);
void func_8430C004(unk_D_84390010* arg0, unk_D_84390010* arg1);
void func_8430C010(s32 arg0);


void Math_CalcDistAndAngles(Vec3f* arg0, Vec3f* arg1, f32* arg2, s16* arg3, s16* arg4);
Vec3f* Vector_Zero(Vec3f* arg0);
Vec3f* Vector_CalcPolarOffset(Vec3f* arg0, Vec3f* arg1, f32 arg2, s16 arg3);
void Vector_SetXZFromPolar(Vec3f* arg0, f32 arg1, s16 arg2);
Vec3f* Vector_Copy(Vec3f* arg0, Vec3f* arg1);
Vec3s* VectorS_Copy(Vec3s* arg0, Vec3s* arg1);
Vec3f* Vector_ScaleXYZ(Vec3f* arg0, f32 arg1, f32 arg2, f32 arg3);
s16 Math_CalcAngleBetweenPoints(f32 arg0, f32 arg1, f32 arg2, f32 arg3);
f32 Vector_Distance(Vec3f arg0, Vec3f arg1);
f32 Math_2DDistance(f32 arg0, f32 arg1, f32 arg2, f32 arg3);
s32 Math_RandomIntBelow(f32 arg0);
u16 Math_RandomU16Scaled(s32 arg0);
s32 Math_StepTowards(s16* arg0, s16 arg1, s16 arg2);
s32 Math_StepTowardsProportional(s16* arg0, s16 arg1, f32 arg2);
void Math_ExponentialApproach(f32* arg0, f32 arg1, f32 arg2);
void func_8430C780(s16* arg0, s16 arg1, s16 arg2);
void func_8430C7B4(u16* arg0, u16 arg1, s16 arg2);
void Math_CubicBezierCoeffs(f32* arg0, f32 arg1);
void func_8430C8A0(f32* arg0, f32 arg1);
void func_8430C97C(f32* arg0, f32 arg1);
void Math_EaseOutCubicCoeffs(f32* arg0, f32 arg1);
void func_8430CB3C(f32* arg0, f32 arg1);


void func_8430CC20(void);
void func_8430CC84(void);
s32 Battle_TickPhaseTimer(void);
s32 Battle_TickCountdownTimer(void);
s32 func_8430CDAC(s32 arg0, s32 arg1);
s32 Battle_ComputeWinner(void);
s32 func_8430D02C(void);
s32 func_8430D124(void);
void func_8430D268(void);
s32 func_8430D294(void);
void func_8430D30C(void);
s32 func_8430D334(unk_D_84390010* arg0);
void func_8430D364(void);
s32 func_8430D434(unk_D_84390010* arg0);
s32 func_8430D574(unk_D_84390010* arg0, s32 arg1);
void func_8430D5BC(unk_D_84390010* arg0);
void func_8430D638(unk_D_84390010* arg0);
void func_8430D6D0(unk_D_84390010* arg0);
void func_8430D710(s32 arg0);
void func_8430D814(void);
s32 func_8430D8C4(unk_D_84390010* arg0);
s32 func_8430D9EC(unk_D_84390010* arg0, unk_D_84390010* arg1);
void func_8430DB58(unk_D_84390010* arg0, UNUSED unk_D_84390010* arg1);
void func_8430DBA0(unk_D_84390010* arg0, unk_D_84390010* arg1);
void func_8430DCD4(unk_D_84390010* arg0, unk_D_84390010* arg1);
s32 func_8430DE20(unk_D_84390010* arg0, unk_D_84390010* arg1);
s32 func_8430DFCC(unk_D_84390010* arg0, unk_D_84390010* arg1);
void func_8430E1CC(unk_D_84390010* arg0);
void func_8430E490(unk_D_84390010* arg0);
s32 func_8430E504(unk_D_84390010* arg0);
void func_8430E580(unk_D_84390010* arg0);
void func_8430E5AC(unk_D_84390010* arg0, s32 arg1);
void func_8430E72C(unk_D_84390010* arg0, Controller* arg1);
void func_8430E8E8(unk_D_84390010* arg0);
void func_8430EB1C(unk_D_84390010* arg0);
s32 func_8430EBA8(unk_D_84390010* arg0);
s32 func_8430ED88(unk_D_84390010* arg0);
void func_8430EE50(unk_D_84390010* arg0);
void func_8430EF4C(unk_D_84390010* arg0);
s32 func_8430F044(unk_D_84390010* arg0, UNUSED Controller* arg1);
void func_8430F080(unk_D_84390010* arg0);
void func_8430F0C0(unk_D_84390010* arg0);
s32 func_8430F27C(unk_D_84390010* arg0);
s32 func_8430F350(unk_D_84390010* arg0, unk_D_84390010* arg1);
void Entities_ShowAllModels(void);
void Entities_HideAllModels(void);
void DemoFeedScriptedInput(void);
void func_8430F598(unk_D_84390010* arg0, unk_D_84390010* arg1);
void func_8430F5F4(void);
void func_8430F794(unk_D_84390010* arg0, unk_D_84390010* arg1);
void func_8430F8B8(void);
void func_8430FB20(void);
void func_8430FB68(void);


void func_8430FC10(void);
void DrawWindowBackground(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void DrawColoredRect(s32 arg0, s32 arg1, s32 arg2, s32 arg3, Color_RGB8* arg4, Color_RGB8* arg5);
void func_84310334(s32 arg0, s32 arg1, s32 arg2, s32 arg3, Color_RGB8* arg4, Color_RGB8* arg5);
void func_84310360(void);
void DrawHPBar(s32 arg0, s32 arg1, f32 arg2, s32 arg3);
void func_843109EC(void);
void DrawLevelNumber(s32 arg0, s32 arg1, s32 arg2);
void DrawFractionNumber(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_84310CE4(s16 arg0, s16 arg1, s32 arg2, char* arg3, s32 arg4);
void func_84310DC4(s16 arg0, s16 arg1, s32 arg2, u8* arg3, s32 arg4, s32 arg5);
void func_84310FA4(unk_D_84390010* arg0, unk_D_800AE540_0004* arg1, s16 arg2, s16 arg3, s32 arg4, u16 arg5, s32 arg6);
void DrawPokemonInfoWindow(unk_D_84390010* arg0, PokemonData* arg1, unk_D_84385790* arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9, s32 argA);
s32 func_843112C4(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u8* arg4);
void func_84311420(void);
void func_84311428(s16 arg0, s16 arg1, s16 arg2, s16 arg3);
void func_843116D8(s16 arg0, s16 arg1);
void func_843118A8(s16 arg0, s16 arg1);
void func_84311A38(unk_D_84390010* arg0, s16 arg1, s16 arg2);
void func_84311F30(unk_D_84390010* arg0, s16 arg1, s16 arg2, u16 arg3, s32 arg4);
void func_843128A0(unk_D_84390010* arg0, s16 arg1, s16 arg2, u16 arg3, s32 arg4);
void func_84313148(unk_D_84390010* arg0, s16 arg1, s16 arg2, s32 arg3);
void func_843133B4(unk_D_84390010* arg0, s16 arg1, s16 arg2, s32 arg3);
void func_843135B8(unk_D_84390010* arg0, s16 arg1, s16 arg2, s32 arg3);
void Text_PrintRightAligned(s32 arg0, s32 arg1, char* arg2);
s32 DrawCounterLeftToRight(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 DrawCounterRightToLeft(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_84313A74(unk_D_84390010* arg0, s16 arg1, s16 arg2, s32 arg3);
void func_8431493C(s16 arg0, s16 arg1, s16 arg2, s32 arg3);
void func_84314B20(s16 arg0, s16 arg1, char* arg2);
void func_84314B6C(unk_D_84390010* arg0, unk_D_800AE540_0004* arg1, PokemonData* arg2, s32 arg3, s32 arg4, s32 arg5);
void func_84314F60(unk_D_84390010* arg0, unk_D_800AE540_0004* arg1, PokemonData* arg2, s32 arg3, s32 arg4, s32 arg5);
void func_8431524C(unk_D_84390010* arg0, unk_D_800AE540_0004* arg1, s16 arg2, s16 arg3, s32 arg4);
void func_84315550(unk_D_84390010* arg0, s16 arg1, s16 arg2, s32 arg3);
void func_8431595C(unk_D_84390010* arg0, s16 arg1, s16 arg2, s32 arg3);
void func_84315ADC(s32 arg0, s16 arg1, s16 arg2, char* arg3);
s32 Dialog_PrintLineIfSet(char* arg0, s16 arg1, s16 arg2);
void func_84315C28(unk_D_843901A0_4C8* arg0, s16 arg1, s16 arg2, Vec3f arg3);
void Dialog_OpenColoredWindow(unk_D_843901A0_4C8* arg0, s16 arg1, s16 arg2);
s32 Dialog_ZoomColoredWindow(unk_D_843901A0_4C8* arg0, s16 arg1, s16 arg2);
void func_84315FAC(unk_D_843901A0_4C8* arg0, s16 arg1, s16 arg2, Vec3f arg3);
void Dialog_OpenDarkWindow(unk_D_843901A0_4C8* arg0, s16 arg1, s16 arg2);
s32 Dialog_ZoomDarkWindow(unk_D_843901A0_4C8* arg0, s16 arg1, s16 arg2);
void func_843162E4(s32 arg0, s16 arg1, s16 arg2, char* arg3);
void func_843163C8(unk_D_84390010* arg0, s16 arg1, s16 arg2, s32 arg3);
void func_84316610(void);
void func_84316640(s16 arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5, s16 arg6, s16 arg7);
void func_843167D4(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u8* arg4, s32 arg5);
void func_8431694C(void);
void func_84317004(void);
void func_8431712C(void);
void func_843172A0(unk_D_84390010* arg0, unk_D_84390010_654* arg1);
void func_84317558(unk_D_84390010* arg0, unk_D_84390010_654* arg1);


void ResetDialogBuffers(void);
void ResetMessageIndices(void);
void SimpleStringFormat(s8* arg0, s8* arg1, ...);
void WriteMessageCharOrString(s8* arg0, s8 arg1);
void InitDialogHeader(char* arg0, s32 arg1);
void func_84317B38(void);
void InitBattleDialogParameters(void);
void DetermineMessageCategoryAndDisplay(void);
void func_84317EDC(void);
void func_843180AC(void);
void Dialog_SetMode(s32 arg0);
void Dialog_Clear(void);
void ProcessMessageCommand(s8* arg0);
void RenderDialogBox(unk_D_843901A0_4C8* arg0, s16 arg1, s16 arg2);
s32 func_84318CE4(unk_D_843901A0_4C8* arg0);
void Dialog_RunWindowSequence(s16 arg0, s16 arg1);
void func_843193F4(unk_D_84390010* arg0);
void func_84319408(unk_D_84390010* arg0, s32 arg1);
void func_843194A0(unk_D_84390010* arg0);
void func_84319564(void);
void func_8431962C(void);
void func_84319668(void);
void func_843196A4(void);


s32 Camera_IsCloseViewCondition(void);
s32 func_84319878(UNUSED unk_D_84390010* arg0, CameraStruct* arg1);
s32 func_843198EC(UNUSED unk_D_84390010* arg0, UNUSED CameraStruct* arg1);
void Camera_SetCloseView(CameraStruct* arg0);
void Camera_SetFarView(CameraStruct* arg0);
void func_84319C58(CameraStruct* arg0, s32 arg1);
void func_84319F10(CameraStruct* arg0, s32 arg1);
void func_8431A024(CameraStruct* arg0, s32 arg1);
void func_8431A098(CameraStruct* arg0);
void func_8431A130(CameraStruct* arg0);
void Camera_SetFromBattleContext(CameraStruct* arg0);
void func_8431A2C8(CameraStruct* arg0, s32 arg1);
void Camera_UpdateStateMachine(CameraStruct* arg0);
void func_8431A718(CameraStruct* arg0);
void func_8431A780(CameraStruct* arg0);
void func_8431A7B8(CameraStruct* arg0);
void func_8431A8B0(CameraStruct* arg0);
void func_8431A94C(CameraStruct* arg0);
void func_8431A9E0(CameraStruct* arg0);
void func_8431AA3C(CameraStruct* arg0);
void func_8431AA78(CameraStruct* arg0);
void func_8431AAAC(CameraStruct* arg0);
void Camera_MainUpdate(CameraStruct* arg0);


f32 ClampScaledDistance(unk_D_84390010* arg0, f32 arg1, f32 arg2);
s32 func_8431AD68(s32 arg0);
s32 Battle_WaitForAnimation(s32 arg0);
s32 func_8431ADF0(s32 arg0);
s32 func_8431AE20(s32 arg0);
void SetCurrentPlayerIndex(s32 arg0);
void Battle_FinishTurn(void);
void func_8431AE6C(void);
void SetCameraPositionAndView(CameraStruct* arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, s16 arg5, s16 arg6);
void GetEntityGroundPosition(unk_D_84390010* arg0, Vec3f* arg1);
void ResolveEntityPosition(unk_D_84390010* arg0, Vec3f* arg1, s32 arg2);
void func_8431AFB4(s32 arg0, s32 arg1);
void func_8431AFD0(CameraStruct* arg0, f32 arg1, f32 arg2);
void func_8431AFE4(s32 arg0, u16 arg1);
void func_8431B004(void);
void func_8431B078(unk_D_84390010* arg0);
void func_8431B174(CameraStruct* arg0);
void func_8431B290(UNUSED unk_D_84390010* arg0);
s32 func_8431B2B8(s16 arg0, s16 arg1);
s32 func_8431B34C(CameraStruct* arg0, s16 arg1, s16 arg2);
s32 func_8431B42C(UNUSED CameraStruct* arg0, s16 arg1, s16 arg2);
void func_8431B4C0(s16 arg0, s16 arg1, f32 arg2);
void SetupBattleCamera(CameraStruct* arg0, s32 arg1);
void func_8431B830(CameraStruct* arg0);
void ConfigureCameraForModel(unk_D_84390010* arg0, CameraStruct* arg1);
void func_8431BA5C(void);
void func_8431BAB4(unk_D_84390010* arg0, CameraStruct* arg1, Vec3f arg2, s16 arg3, s16 arg4, f32 arg5, f32 arg6);
void func_8431BB24(CameraStruct* arg0, Vec3f arg1, s16 arg2, s16 arg3, f32 arg4, f32 arg5);
void func_8431BB80(CameraStruct* arg0, Vec3f arg1, s16 arg2, s16 arg3, f32 arg4, f32 arg5);
void func_8431BBDC(CameraStruct* arg0, s16 arg1, s16 arg2, f32 arg3, f32 arg4);
void func_8431BC38(CameraStruct* arg0, Vec3f arg1, s16 arg2, s16 arg3, f32 arg4, f32 arg5);
void func_8431BCA4(CameraStruct* arg0, s16 arg1, s16 arg2, f32 arg3, f32 arg4);
void func_8431BD10(UNUSED CameraStruct* arg0);
void SmoothFloatPair(f32* arg0, f32* arg1);
void func_8431BD94(CameraStruct* arg0, unk_D_84390010* arg1, UNUSED f32 arg2);
void func_8431C594(CameraStruct* arg0, unk_D_84390010* arg1);
void Battle_AdvanceCameraTimeline(CameraStruct* arg0, unk_D_84390010* arg1);
void func_8431C750(CameraStruct* arg0, unk_D_84390010* arg1);
void func_8431C784(CameraStruct* arg0, unk_D_84390010* arg1);
void func_8431C7A4(CameraStruct* arg0, unk_D_84390010* arg1);
s32 Battle_ProcessOpponentAction(CameraStruct* arg0, unk_D_84390010* arg1);
void func_8431CB54(CameraStruct* arg0, unk_D_84390010* arg1);
void func_8431CC38(CameraStruct* arg0, unk_D_84390010* arg1);
void func_8431CCFC(CameraStruct* arg0, unk_D_84390010* arg1);
void func_8431CEF0(CameraStruct* arg0, unk_D_84390010* arg1, UNUSED s32 arg2);
void func_8431CFA4(CameraStruct* arg0, unk_D_84390010* arg1);
s32 func_8431D048(CameraStruct* arg0, unk_D_84390010* arg1);
s32 Battle_CheckPlayerAction(CameraStruct* arg0, unk_D_84390010* arg1, s32 arg2, s32 arg3);
s32 Battle_ApplySpecialCamera(CameraStruct* arg0, unk_D_84390010* arg1);
void func_8431D5C8(UNUSED CameraStruct* arg0);
void Battle_ApplyCameraSettings(CameraStruct* arg0, unk_D_84390010* arg1, s32 arg2);
void func_8431D704(s16 arg0, s16 arg1, s16 arg2, s16 arg3);
void func_8431D750(f32 arg0, f32 arg1);
void func_8431D764(s16 arg0, s16 arg1, s16 arg2, s16 arg3);
void func_8431D7B0(f32 arg0, f32 arg1);
void func_8431D7C4(f32 arg0, f32 arg1);
void Battle_PlayCameraTransition(unk_D_86B0C160* arg0, CameraStruct* arg1, unk_D_84390010* arg2);
void Battle_ApplyCameraPreset(unk_D_86B0C160* arg0, CameraStruct* arg1);
s32 func_8431DA38(CameraStruct* arg0, unk_D_84390010* arg1);
s32 func_8431DBEC(UNUSED CameraStruct* arg0);
void func_8431DC78(CameraStruct* arg0, s32 arg1);
s32 func_8431DE30(CameraStruct* arg0, s32 arg1);
void func_8431DF98(CameraStruct* arg0, unk_D_84390010* arg1);
void func_8431E118(CameraStruct* arg0, unk_D_84390010* arg1);
void func_8431E1DC(CameraStruct* arg0, unk_D_84390010* arg1, s32 arg2);
void func_8431E368(CameraStruct* arg0, unk_D_84390010* arg1, s32 arg2);
void func_8431E4DC(CameraStruct* arg0, unk_D_84390010* arg1, s32 arg2);
void func_8431E63C(CameraStruct* arg0, unk_D_84390010* arg1, s32 arg2);
void func_8431E7D0(CameraStruct* arg0, unk_D_84390010* arg1, s32 arg2);
void func_8431E90C(CameraStruct* arg0, unk_D_84390010* arg1, s32 arg2);
void func_8431EA1C(CameraStruct* arg0, unk_D_84390010* arg1, s32 arg2, s32 arg3);
void func_8431EAB8(CameraStruct* arg0, unk_D_84390010* arg1);
void func_8431EBD0(CameraStruct* arg0, unk_D_84390010* arg1);
void func_8431ECEC(CameraStruct* arg0, unk_D_84390010* arg1);
void func_8431EE08(CameraStruct* arg0, unk_D_84390010* arg1);
void func_8431EF54(CameraStruct* arg0, unk_D_84390010* arg1);
void func_8431F050(CameraStruct* arg0, unk_D_84390010* arg1, s32 arg2);
void func_8431F194(CameraStruct* arg0, unk_D_84390010* arg1);
void Battle_ExecuteMove(unk_D_84390010* arg0, CameraStruct* arg1, s32 arg2, s32 arg3);
void Battle_PlayMoveEffect(unk_D_84390010* arg0, CameraStruct* arg1, s32 arg2);
void Battle_QueueOpponentMove(unk_D_84390010* arg0, CameraStruct* arg1, s32 arg2);


void TriggerSpecialActionIfReady(unk_D_84390010* arg0);
void Battle_ResetSubstate(void);
s32 HandlePlayerActionFlag800(unk_D_84390010* arg0);
s32 HandlePlayerActionFlag800Alt(unk_D_84390010* arg0);
s32 HandlePlayerActionFlag1000(unk_D_84390010* arg0);
s32 ProcessActionWhenState44Is2(unk_D_84390010* arg0);
s32 ProcessDualPlayerActionState1(void);
void ClearAnimFlag20IfCondition(void);
void func_8431FCC4(void);
s32 UpdatePokemonHP(unk_D_84390010* arg0);
void Battle_ClearSubstateFlag(void);
void Battle_SetSubstateFlag(void);
void Battle_SetPhase(UNUSED CameraStruct* arg0, s32 arg1);
void Battle_StoreCameraFOV(CameraStruct* arg0);
void Battle_SetCameraFOV30(CameraStruct* arg0);
s32 GetAnimDataField0D(unk_D_84390010* arg0);
s32 GetMappedAnimDataField0D(unk_D_84390010* arg0);
s32 GetAnimDataField0E(unk_D_84390010* arg0);
s32 GetMappedAnimDataField0E(unk_D_84390010* arg0);
s32 GetAnimDataField0FOrDefault(unk_D_84390010* arg0);
void DetermineTurnOrder(void);
void DetermineTurnOrderPriority(void);
s32 HandlePokemonFaintOrSwitch(void);
void Battle_UpdateAfterTurn(void);
s32 Battle_SetPhaseAndReset(s32 arg0);
s32 Battle_SetPhaseNoReset(s32 arg0);
s32 Battle_SetPhaseSimple(s32 arg0);
void Battle_TogglePlayerAndSetPhase5(CameraStruct* arg0);
void Battle_TogglePlayerAndPrepare(u8 arg0);
void Battle_CheckAndAdvancePhase(void);
void Battle_HandleSubstateTransition(void);
s32 Battle_OpponentSpecialCondition(void);
void Battle_HandlePhaseTransition(void);
void Battle_ProcessReadyState(CameraStruct* arg0);
void Battle_UpdateHPAndProceed(CameraStruct* arg0);
void Battle_MainLoopStep(CameraStruct* arg0);
s32 Battle_HandleSpecificPhases(void);
s32 Battle_HandlePhase10or14or8(void);
s32 Battle_CheckOpponentSpecialAction(void);
void Battle_SetCurrentAndOpponent(void);
void Battle_InitializeCameraAndAudio(CameraStruct* arg0);
void Battle_HandleSpecialAnimation(CameraStruct* arg0);
s32 Battle_ResetMoveStateAndStartAnimation(unk_D_84390010* arg0);
void Battle_HandleOpponentDefeat(CameraStruct* arg0);
void Battle_HandleOpponentAnimation(CameraStruct* arg0);
void Battle_ProcessOpponentActionStep(CameraStruct* arg0);
void Battle_ProcessOpponentActionStep2(CameraStruct* arg0);
void Battle_DetermineNextPhaseAfterOpponent(CameraStruct* arg0);
void UnusedBattleStateHandler(UNUSED CameraStruct* arg0);
void Battle_AdjustCameraForAction(CameraStruct* arg0);
void func_84321F2C(UNUSED CameraStruct* arg0);
void func_84321F74(UNUSED CameraStruct* arg0);
void func_84321FB8(CameraStruct* arg0);
void Battle_StateMachine(CameraStruct* arg0);
void Battle_HandleState2(UNUSED CameraStruct* arg0);
void Battle_StateMachineVariant(CameraStruct* arg0);
void Battle_ApplyStatusEffectAnimation(unk_D_84390010* arg0);
void Battle_SetupInitialCamera(CameraStruct* arg0);
void Battle_TryAdvancePhase(CameraStruct* arg0);
void Battle_HandleSubstate0(CameraStruct* arg0);
void Player_SetActionTimer(unk_D_84390010* arg0);
void Battle_StartTurn(UNUSED CameraStruct* arg0);
void Battle_SelectMove(CameraStruct* arg0);
s32 Battle_HandleMoveSelection(CameraStruct* arg0);
void Battle_MainStep(CameraStruct* arg0);
void Battle_ReselectMoveIfNeeded(CameraStruct* arg0);
void Battle_ChooseMoveByContext(CameraStruct* arg0, s32 arg1);
s32 Battle_AdjustCameraForMove(CameraStruct* arg0, s32 arg1);
void Battle_EndTurn(UNUSED CameraStruct* arg0);
s32 Battle_IsMoveReady(UNUSED CameraStruct* arg0);
void Battle_ProcessMovePhase0(CameraStruct* arg0);
void Battle_ProcessMovePhase1(CameraStruct* arg0);
void Battle_ProcessMovePhase2(CameraStruct* arg0);
void Battle_ProcessMovePhase3(CameraStruct* arg0);
void Battle_ProcessMovePhase4(CameraStruct* arg0);
void Battle_DispatchMoveHandler(CameraStruct* arg0);
void Player_HandleSpecialAnimation(unk_D_84390010* arg0);
s32 Player_IsSpecialCondition(unk_D_84390010* arg0);
void Battle_CheckAndResetIfBothReady(CameraStruct* arg0, s32* arg1, s32* arg2);
void Battle_OpponentTurnPhase0(CameraStruct* arg0);
void Battle_OpponentTurnPhase1(CameraStruct* arg0);
void func_84323E44(CameraStruct* arg0);
void Battle_OpponentTurnPhase2(CameraStruct* arg0);
void func_84324404(void);
void func_8432440C(void);
void Battle_OpponentAnimationStep(CameraStruct* arg0);
void Battle_HandleBattleStateTransitions(CameraStruct* arg0);
void Battle_StateMachineStepA(CameraStruct* arg0);
void Battle_StateMachineStepB(CameraStruct* arg0);
s32 Battle_FinalPhaseHandler(void);
void Battle_PlayerMoveAnimation(CameraStruct* arg0);
void Battle_PlayerMoveAnimationAlt(CameraStruct* arg0);
void Battle_PlayerMoveSequence(CameraStruct* arg0);
void Battle_PlayerOpponentInteraction(CameraStruct* arg0);
void func_843255DC(CameraStruct* arg0);
void func_84325724(CameraStruct* arg0);
void func_84325A10(CameraStruct* arg0);
s32 func_84325CAC(unk_D_84390010* arg0);
void func_84325CDC(CameraStruct* arg0);
void func_84325E94(CameraStruct* arg0);
void func_843261CC(CameraStruct* arg0);
void func_84326460(CameraStruct* arg0);
void func_84326570(CameraStruct* arg0);
void func_843266D4(CameraStruct* arg0);
void func_8432691C(CameraStruct* arg0);
void func_84326A70(void);
void func_84326A78(UNUSED CameraStruct* arg0);
void func_84326AC4(CameraStruct* arg0);
void func_84326CB4(CameraStruct* arg0);
void func_84326E84(CameraStruct* arg0);
void func_8432734C(CameraStruct* arg0);
void func_843275F8(CameraStruct* arg0);
void func_84327720(CameraStruct* arg0);
void func_84327B90(CameraStruct* arg0);
void func_84327D98(unk_D_84390010* arg0);
void func_84327DC0(CameraStruct* arg0);
void func_84328250(CameraStruct* arg0);
void func_84328734(CameraStruct* arg0);


void Intro_SetupCamera(CameraStruct* arg0);
void Intro_CheckPlayerReady(UNUSED CameraStruct* arg0);
void Intro_PlayerEnter(UNUSED CameraStruct* arg0);
void Intro_OpponentEnter(CameraStruct* arg0);
void Intro_CameraPanAndZoom(CameraStruct* arg0);
void Intro_WaitForAnimCompletion(UNUSED CameraStruct* arg0);
void Intro_DisplayPokemonInfo(CameraStruct* arg0);
void Intro_PostInfoDelay(CameraStruct* arg0);
void Opponent_DisplayPokemonInfo(CameraStruct* arg0);
void Opponent_PostInfoDelay(CameraStruct* arg0);
void Intro_End(UNUSED CameraStruct* arg0);
void UnusedFunction(void);
void Intro_StateMachine(CameraStruct* arg0);


void InitializeCameraForCurrentEntity(CameraStruct* arg0);
void InitializeCameraForPlayerEntity(CameraStruct* arg0);
void BattleCamera_RunState(CameraStruct* arg0, UNUSED unk_D_84390010* arg1, UNUSED unk_D_84390010* arg2);
void BattleState_Allocate(void);
void func_843297E8(UNUSED CameraStruct* arg0);
void func_843297F0(UNUSED CameraStruct* arg0);
void Camera_PreventDegenerateView(CameraStruct* arg0);
void Battle_StartSequence(CameraStruct* arg0);
void Battle_TransitionSequence(CameraStruct* arg0);
void Battle_RunSequence(CameraStruct* arg0);
u16 IsPointInTriangle(unk_D_84390010* arg0, CameraStruct* arg1, unk_D_84390010* a2, s16 arg3, f32 arg4);
u16 IsPointInTriangleAndWithinRange(unk_D_84390010* arg0, CameraStruct* arg1, unk_D_84390010* a2, s16 arg3, f32 arg4);
void UpdateEntityVisibilityFromCamera(CameraStruct* arg0);
void UpdateOppositeEntityVisibility(CameraStruct* arg0);
void func_8432A414(void);
void SetAllEntitiesActiveFlag(void);
void DeactivateOppositeEntity(void);
void DeactivateCurrentEntity(void);
void ClearEntityFlagIfInState(void);
void ProcessBattleState(CameraStruct* arg0);
void func_8432ABBC(CameraStruct* arg0);
void Battle_Update(CameraStruct* arg0);
s32 func_8432AEE4(s32 arg0, CameraStruct* arg1);


void HandleMoveHitAnimation(unk_D_84390010* arg0);
void TriggerCurrentAnimAction(unk_D_84390010* arg0);
void StartMoveAnimation(unk_D_84390010* arg0);
void ResetMoveStateAndStartAnimation(unk_D_84390010* arg0);
void ResumeMoveAnimationIfNotTriggered(unk_D_84390010* arg0);
void HandleItemOrStatusEffect(unk_D_84390010* arg0);
void ProcessStatusEffectEnd(unk_D_84390010* arg0);
void FinalizeStatusEffect(unk_D_84390010* arg0);


void PlaySoundEffect_Select(void);
void PlaySoundEffect_Cancel(void);
void PlaySoundEffect_Confirm(void);
void PlaySoundEffect_Error(void);
void PlayBattleMusicOrDefault(unk_D_84390010* arg0, s16 arg1);
void PlayHeightBasedSoundEffect(unk_D_84390010* arg0);
void ProcessEntityAudioInfo(unk_D_84390010* arg0);
void TriggerMoveEvent(unk_D_84390010* arg0, unk_D_800FCB18* arg1, s32 arg2);
void SetPlayerSidesFromActivePokemons(void);
void SetTeamScoresFromActivePokemons(void);
void ProcessBattleMenuSelection(void);
void RenderBattleMenuSelection(void);
void PlayBattleSoundEffect(unk_D_84390010* arg0, s32 arg1);
void ExecuteStateFunction(s16 arg0);
void ExecuteParticleEffect(s16 arg0);
void RegisterStateCallbacks(func_D_84390300 arg0, func_D_84390320 arg1);
void RunActionScript(s32 arg0, s32 arg1, s32 arg2);
void ProcessPendingActionScripts(void);
void MainUpdateLoop(UNUSED CameraStruct* arg0);
void SetActionScriptSubIndex(u8 arg0);
u8 GetActionScriptSubIndex(void);
void SetActionScriptMode(u8 arg0);
u8 GetActionScriptMode(void);
s16 GetActionScriptId(void);
void InitActionScript(s32 arg0, unk_D_84390010* arg1, unk_D_84390010* arg2, s16 arg3, s16 arg4);
void InitActionScriptSimple(s32 arg0, unk_D_84390010* arg1, unk_D_84390010* arg2, s16 arg3, s16 arg4);
void InitDualTargetActionScript(s32 arg0, unk_D_84390010* arg1, unk_D_84390010* arg2, s16 arg3, s16 arg4);
void InitActionScriptMode1(s32 arg0, unk_D_84390010* arg1, unk_D_84390010* arg2, s16 arg3, s16 arg4);
void InitActionScriptMode3(s32 arg0, unk_D_84390010* arg1, unk_D_84390010* arg2, s16 arg3, s16 arg4);
void InitSingleEntityActionScript(s32 arg0, unk_D_84390010* arg1);
void InitSingleEntityActionScriptVariant(s32 arg0, unk_D_84390010* arg1);
void func_8432C748(s32 arg0, unk_D_84390010* arg1);
void func_8432C768(s32 arg0);
void func_8432C7A0(u8 arg0, unk_D_84390010* arg1);
void func_8432C80C(u8 arg0, unk_D_84390010* arg1);
void LoadWaterTexturesFromList(arg1_func_80019420* arg0);
void InitWaterTextures(void);
void BuildMessageString(s16 arg0);
void SetMessageFromId(unk_D_800AE540_1194* arg0, s16 arg1);
void SetMessageFromAltTable(unk_D_800AE540_1194* arg0, s16 arg1);
void ProcessWaterTextureLists(void);
void ResetWaterEffect(unk_D_800AE540_1194* arg0);
void InitGraphNodePools(void);
ParticleEffectInstance* GetGraphNodeData(Fragment2_1GraphNode* arg0);
Fragment2_1GraphNode* AllocateGraphNode(ParticleEffectInstance* arg0);
void FreeGraphNode(Fragment2_1GraphNode* arg0);
Fragment2_1GraphNode* AllocateParticleNode(ParticleEffectInstance* arg0);
void FreeParticleNode(Fragment2_1GraphNode* arg0);
void InitWaterAnimNode(Fragment2_1GraphNode* arg0, s16 arg1, s16 arg2);
void SetAnimChannelBase(Fragment2_1GraphNode* arg0, s16 arg1);
void InitGraphNodeTexture(Fragment2_1GraphNode* arg0, s16 arg1);
void SetAnimChannel(Fragment2_1GraphNode* arg0, s16 arg1);
void InitReverseAnimNode(Fragment2_1GraphNode* arg0, s16 arg1);
s32 IsAnimChannelFinished(Fragment2_1GraphNode* arg0);
void ClearCameraCallbacks(UNUSED CameraStruct* arg0);
void RunCameraCallbacks(UNUSED CameraStruct* arg0);
void UpdateCameraGlobals(CameraStruct* arg0);
s32 HandleCameraMode(s32 arg0, CameraStruct* arg1);
void InitGameState(void);
void ResetGameGlobals(void);
void GetCameraOffsetPosition(Vec3f* arg0, f32 arg1);
void GetCameraPitchYawFromEyeToAt(s16* arg0, s16* arg1);
void GetCameraYawFromEyeToAt(s16* arg0);
void GetCameraPitchYawFromAtToEye(s16* arg0, s16* arg1);
void GetCameraYawFromAtToEye(s16* arg0);
void GetCameraStoredPitchYaw(s16* arg0, s16* arg1);
void GetCameraStoredYaw(s16* arg0);
void GetCameraStoredRollPitch(s16* arg0, s16* arg1);
void GetCameraStoredPitch(s16* arg0);


void ParticlePools_Allocate(void);
ParticleDef* ParticleDef_Allocate(void);
void ParticleDef_Reset(ParticleDef* arg0);
void ParticleNode_Init(ParticleEffectInstance* arg0, Vec3f arg1, Vec3s arg2, s32 arg3, s32 arg4);
void ParticleNode_CopyFrom(ParticleEffectInstance* arg0, ParticleEffectInstance* arg1, func_unk_D_8140E724_008 arg2, ParticleEffectData* arg3, s32 arg4);
void ParticleNode_CreateMultiple(ParticleEffectInstance* arg0, func_unk_D_8140E724_008 arg1, ParticleEffectData* arg2, s16 arg3);
void func_8432D8E8(ParticleEffectInstance* arg0, func_unk_D_8140E724_008 arg1, ParticleEffectData* arg2, s16 arg3, s16 arg4, s16 arg5);
ParticleEffectInstance* ParticleNode_CreateAt(s16 arg0, s16 arg1, s32 arg2, f32 arg3);
void ParticleNode_ProcessChild(ParticleEffectInstance* arg0);
void ParticleNode_Destroy(ParticleEffectInstance* arg0);
void ParticleNode_UpdateBehavior(ParticleEffectInstance* arg0);
void func_8432DE0C(ParticleEffectInstance* arg0);
void func_8432E0A4(ParticleEffectInstance* arg0);
void func_8432E144(ParticleEffectInstance* arg0);
void ParticleSystem_Update(void);
void ParticleInstance_Configure(ParticleEffectInstance* arg0, unk_D_84390010* arg1, ParticleDef* arg2, s16 arg3);
void ParticleDef_SpawnInstances(ParticleDef* arg0, s32 arg1);
void func_8432E434(ParticleDef* arg0);
void func_8432E454(ParticleDef* arg0);
void func_8432E474(ParticleDef* arg0);
void func_8432E4B0(ParticleDef* arg0);
void ParticleDefs_Update(void);
void Particles_UpdateAll(void);
void func_8432E6B4(void);
void func_8432E784(void);
s32 func_8432E8B0(void);
void func_8432E8BC(void);
void func_8432E8EC(void);
s32 func_8432E97C(void);
void func_8432E99C(void);
void func_8432E9AC(void);
void func_8432E9B8(void);
void func_8432E9D8(s32 arg0);
void func_8432EA60(u8 arg0, unk_D_84390010* arg1);
void func_8432EB14(void);
void func_8432EB20(s32 arg0);
void func_8432EB2C(s32 arg0);
void func_8432EB44(void);
ParticleDef* ParticleDef_Create(s32 arg0, s32 arg1, s8 arg2, func_unk_D_8140E724 arg3, ParticleEffectData* arg4, unk_D_84390010* arg5, s16 arg6, s16 arg7, u8 arg8, u8 arg9, u8 argA, u8 argB);
ParticleDef* func_8432EC28(s32 arg0, func_unk_D_8140E724 arg1, ParticleEffectData* arg2, s16 arg3, s16 arg4, u8 arg5, u8 arg6, u8 arg7, u8 arg8);
ParticleDef* func_8432ECA0(s32 arg0, s32 arg1, s8 arg2, func_unk_D_8140E724 arg3, ParticleEffectData* arg4, s16 arg5, s16 arg6, u8 arg7, u8 arg8, u8 arg9, u8 argA);
ParticleDef* func_8432ED0C(s32 arg0, s16 arg1, u8 arg2);
ParticleDef* func_8432ED74(s32 arg0, s16 arg1, s16 arg2, u8 arg3, u8 arg4);
ParticleDef* func_8432EDE8(s32 arg0, s16 arg1, s16 arg2, u8 arg3);
ParticleDef* func_8432EE5C(s32 arg0, s16 arg1, s16 arg2, u8 arg3, u8 arg4);
ParticleDef* func_8432EED0(s32 arg0, s32 arg1, s8 arg2, s16 arg3, s16 arg4, u8 arg5, u8 arg6);
ParticleDef* func_8432EF40(s32 arg0, s16 arg1, s16 arg2, u8 arg3);
ParticleDef* func_8432EFB4(s32 arg0, s16 arg1, s16 arg2, u8 arg3, u8 arg4);
ParticleDef* func_8432F028(s32 arg0, s32 arg1, s8 arg2, s16 arg3, s16 arg4, u8 arg5, u8 arg6);
ParticleDef* func_8432F098(s32 arg0, s16 arg1, u8 arg2);
ParticleDef* func_8432F104(s32 arg0, s16 arg1, u8 arg2, u8 arg3);
ParticleDef* func_8432F174(s32 arg0, s32 arg1, s8 arg2, s16 arg3, u8 arg4, u8 arg5);
ParticleDef* func_8432F1E0(s32 arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4);
ParticleDef* func_8432F254(s32 arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4);
ParticleDef* func_8432F2C8(s32 arg0, u8 arg1, s16 arg2, s16 arg3, s16 arg4);
ParticleDef* func_8432F344(s32 arg0, s16 arg1, u8 arg2, s16 arg3, s16 arg4, s16 arg5);
ParticleDef* func_8432F3C4(s32 arg0, s16 arg1, u8 arg2, s16 arg3, s16 arg4);
ParticleDef* func_8432F440(s32 arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4);
ParticleDef* func_8432F4BC(s32 arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4);
ParticleDef* func_8432F538(s32 arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5);
ParticleDef* func_8432F5B8(s32 arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5);
ParticleDef* func_8432F638(s32 arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5);
ParticleDef* func_8432F6B8(s32 arg0, s16 arg1, u8 arg2);
ParticleDef* func_8432F728(s32 arg0, s16 arg1, s16 arg2, u8 arg3);
ParticleDef* func_8432F7A0(s32 arg0, s16 arg1, s16 arg2, s16 arg3);
ParticleDef* func_8432F818(s32 arg0);
ParticleDef* func_8432F884(s32 arg0);
ParticleDef* func_8432F8E8(s32 arg0, u8 arg1);
ParticleDef* func_8432F93C(s32 arg0, u8 arg1);
void func_8432F998(void);
void func_8432F9A0(void);
void func_8432F9A8(s32 arg0);
void func_8432F9B4(void);
s32 func_8432F9C0(void);
s32 func_8432F9CC(s32 arg0);
s32 func_8432FA0C(void);
s32 func_8432FA30(void);
void Model_GetNodePosition(unk_D_84390010* arg0, s16 arg1, Vec3f* arg2);
void func_8432FB38(Vec3f* arg0);
void func_8432FB64(Vec3f* arg0);
void func_8432FB90(Vec3f* arg0);
void func_8432FBBC(Vec3f* arg0);
void func_8432FC14(Vec3f* arg0);
void func_8432FC40(unk_D_84390010* arg0, Vec3f* arg1);
f32 func_8432FC60(unk_D_84390010* arg0);
f32 func_8432FC94(unk_D_84390010* arg0);
void func_8432FCB4(unk_D_84390010* arg0);
f32 GetPrimaryEntityScale(void);
void func_8432FCF8(void);
f32 func_8432FD1C(void);
void func_8432FD40(void);
CameraStruct* GetBattleCamera(void);
ParticleEffectInstance* func_8432FD70(Vec3f arg0, u8 arg1);
void func_8432FDF0(ParticleEffectInstance* arg0, Vec3f arg1);
void func_8432FE24(ParticleEffectInstance* arg0);
s16 func_8432FE44(ParticleEffectInstance* arg0);
void func_8432FEC4(ParticleEffectInstance* arg0);
void func_8432FEEC(ParticleEffectInstance* arg0);


void Particle_WhiteFlashInit(ParticleEffectInstance* arg0);
void Particle_WhiteFlashUpdate(ParticleEffectInstance* arg0);
void Particle_WhiteFlashAltInit(ParticleEffectInstance* arg0);
void Particle_WhiteFlashAltUpdate(ParticleEffectInstance* arg0);
void Particle_SetWhiteFlashHandler(ParticleEffectInstance* arg0, u8 arg1);


s32 RenderPanelBackground(ParticleEffectInstance* arg0, CameraStruct* arg1);
void RenderIconMasked(ParticleEffectInstance* arg0, CameraStruct* arg1);
void RenderPanelWithIcon(ParticleEffectInstance* arg0, CameraStruct* arg1);
void RenderOverlayWithIcon(ParticleEffectInstance* arg0, CameraStruct* arg1);
void func_84330388(ParticleEffectInstance* arg0, CameraStruct* arg1);
s32 RenderItemIcon(ParticleEffectInstance* arg0, UNUSED CameraStruct* arg1);
void RenderStatusBar(ParticleEffectInstance* arg0, UNUSED CameraStruct* arg1);
void func_84330688(ParticleEffectInstance* arg0, UNUSED CameraStruct* arg1);
void RenderMultiBlockIcon(ParticleEffectInstance* arg0, UNUSED CameraStruct* arg1);
void func_84330934(ParticleEffectInstance* arg0, UNUSED CameraStruct* arg1);
void func_84330A18(ParticleEffectInstance* arg0, u8* arg1);
void func_84330AF0(ParticleEffectInstance* arg0, UNUSED CameraStruct* arg1);
void func_84330B18(ParticleEffectInstance* arg0, UNUSED CameraStruct* arg1);
void func_84330B40(ParticleEffectInstance* arg0, UNUSED CameraStruct* arg1);
void func_84330C70(ParticleEffectInstance* arg0, UNUSED CameraStruct* arg1);
void func_84330D64(ParticleEffectInstance* arg0, UNUSED CameraStruct* arg1);
void func_84330E58(ParticleEffectInstance* arg0, UNUSED CameraStruct* arg1);
void func_84330F4C(ParticleEffectInstance* arg0, UNUSED CameraStruct* arg1);
void func_84331094(UNUSED ParticleEffectInstance* arg0, UNUSED CameraStruct* arg1);
void RenderTimerDigits(ParticleEffectInstance* arg0, UNUSED CameraStruct* arg1);
void RenderTimerDigitsAlt(ParticleEffectInstance* arg0, UNUSED CameraStruct* arg1);
void func_84331314(ParticleEffectInstance* arg0, UNUSED CameraStruct* arg1);
void RenderTimerNumber(ParticleEffectInstance* arg0, CameraStruct* arg1);
void func_8433157C(ParticleEffectInstance* arg0, CameraStruct* arg1);
void func_843316A8(ParticleEffectInstance* arg0, CameraStruct* arg1);
void func_843317D4(ParticleEffectInstance* arg0, UNUSED CameraStruct* arg1);
void func_843318F8(ParticleEffectInstance* arg0, UNUSED CameraStruct* arg1);
void func_84331A1C(ParticleEffectInstance* arg0, UNUSED CameraStruct* arg1);
void func_84331B58(ParticleEffectInstance* arg0, CameraStruct* arg1);
void func_84331C34(ParticleEffectInstance* arg0, UNUSED CameraStruct* arg1);
void func_84331D60(ParticleEffectInstance* arg0, UNUSED CameraStruct* arg1);


void func_84331DA0(ParticleEffectInstance* arg0);
void func_84331DC8(ParticleEffectInstance* arg0);
void Fragment_SetPrimColorFromPaletteAndRender(ParticleEffectInstance* arg0);
void func_84331EAC(ParticleEffectInstance* arg0);
void Fragment_SetPrimColorFromPaletteAndRender_WithCE(ParticleEffectInstance* arg0);
void func_84331FAC(ParticleEffectInstance* arg0);
void func_8433209C(void);
void func_843320A4(ParticleEffectInstance* arg0);
void func_84332174(ParticleEffectInstance* arg0);
void func_843321BC(ParticleEffectInstance* arg0);
void func_8433227C(ParticleEffectInstance* arg0);
void func_843322C4(ParticleEffectInstance* arg0);
void func_8433237C(ParticleEffectInstance* arg0);
void func_843323BC(ParticleEffectInstance* arg0);
void func_843324A4(ParticleEffectInstance* arg0);
void func_843324EC(ParticleEffectInstance* arg0);
void func_843325C4(ParticleEffectInstance* arg0);
void func_84332604(ParticleEffectInstance* arg0);
void Fragment_SetRandomPrimColorAndRender(ParticleEffectInstance* arg0);
void func_843327B8(ParticleEffectInstance* arg0);
void Fragment_SetFixedPrimColorsAndRender(ParticleEffectInstance* arg0);
void Fragment_ComplexColorMode(ParticleEffectInstance* arg0);
void Fragment_SetAlphaFromUnkA6AndRender(ParticleEffectInstance* arg0);
void Fragment_ProcessAlphaMode(ParticleEffectInstance* arg0);
void Fragment_SetPrimColorFromPaletteAndRender_ZeroBC20(ParticleEffectInstance* arg0);
void Fragment_ProcessBC20Mode(ParticleEffectInstance* arg0);
void Fragment_SetPrimColorFromPaletteAndRender_ZeroBC20_Alt(ParticleEffectInstance* arg0);
void Fragment_ProcessBC20Variant(ParticleEffectInstance* arg0);
void Fragment_SetPrimColorFromPaletteAndRender_WithCD_BC20(ParticleEffectInstance* arg0);
void Fragment_ProcessBC20WithCDMode(ParticleEffectInstance* arg0);
void Fragment_SetPrimColorFromPaletteAndRender_ZeroBC20_Third(ParticleEffectInstance* arg0);
void func_84332E6C(ParticleEffectInstance* arg0);
void func_84332EE8(ParticleEffectInstance* arg0);
void func_84332F30(ParticleEffectInstance* arg0);
void func_84332F90(ParticleEffectInstance* arg0);
void func_84332FD0(ParticleEffectInstance* arg0);
void func_84333060(ParticleEffectInstance* arg0);
void func_843330A0(ParticleEffectInstance* arg0);


void Particle_FireBurstSmall(ParticleEffectInstance* arg0, s16 arg1);
void func_84333210(ParticleEffectInstance* arg0);
void func_843332B4(ParticleEffectInstance* arg0);
void Particle_FireBurstLarge(ParticleEffectInstance* arg0);
void func_84333570(ParticleEffectInstance* arg0);
void func_84333600(ParticleEffectInstance* arg0);
void Particle_SmokePuff(ParticleEffectInstance* arg0);
void func_84333884(ParticleEffectInstance* arg0);
void Particle_SmokePuffHandler(ParticleEffectInstance* arg0);
void func_84333A20(ParticleEffectInstance* arg0, s16 arg1);
void func_84333B04(ParticleEffectInstance* arg0);
void func_84333BA8(ParticleEffectInstance* arg0);
void func_84333DC4(ParticleEffectInstance* arg0);
void func_84333E28(ParticleEffectInstance* arg0);
void func_84333EE8(ParticleEffectInstance* arg0);
void func_84333FBC(ParticleEffectInstance* arg0);
void Particle_Firework(ParticleEffectInstance* arg0);
void func_84334154(ParticleEffectInstance* arg0);
void Particle_Spark(ParticleEffectInstance* arg0);
void func_84334350(ParticleEffectInstance* arg0);
void func_843343F8(ParticleEffectInstance* arg0);
void func_843344A0(ParticleEffectInstance* arg0);
void func_84334558(ParticleEffectInstance* arg0);
void func_843345A0(ParticleEffectInstance* arg0);
void func_84334654(ParticleEffectInstance* arg0);
void func_843346BC(ParticleEffectInstance* arg0);
void func_843347A4(ParticleEffectInstance* arg0);
void func_84334808(ParticleEffectInstance* arg0);
void func_843348DC(ParticleEffectInstance* arg0);
void func_84334994(ParticleEffectInstance* arg0);
void Particle_SetColorByIndex(ParticleEffectInstance* arg0, u8 arg1);
void func_84334B04(void);
void func_84334B0C(ParticleEffectInstance* arg0);
void Particle_Explosion(ParticleEffectInstance* arg0);
void func_84334D7C(ParticleEffectInstance* arg0);
void Particle_Firefly(ParticleEffectInstance* arg0);
void func_84334F84(ParticleEffectInstance* arg0);
void Particle_Sparkle(ParticleEffectInstance* arg0);
void func_843351C8(ParticleEffectInstance* arg0);
void func_843352AC(ParticleEffectInstance* arg0);
void func_843353C4(ParticleEffectInstance* arg0);
void Particle_Star(ParticleEffectInstance* arg0);
void func_84335668(ParticleEffectInstance* arg0);
void Particle_Twinkle(ParticleEffectInstance* arg0);
void func_84335848(ParticleEffectInstance* arg0);
void Particle_Glitter(ParticleEffectInstance* arg0);
void func_84335A84(ParticleEffectInstance* arg0);
void func_84335BA0(ParticleEffectInstance* arg0);
void func_84335D10(ParticleEffectInstance* arg0);
void Particle_FireRing(ParticleEffectInstance* arg0);
void func_84335EF8(ParticleEffectInstance* arg0);
void Particle_ExplosionVariant(ParticleEffectInstance* arg0, s16 arg1, s16 arg2);
void func_8433617C(ParticleEffectInstance* arg0, s32 arg1);
void func_84336320(ParticleEffectInstance* arg0);
void func_84336340(ParticleEffectInstance* arg0);
void func_84336360(ParticleEffectInstance* arg0);
void func_84336480(ParticleEffectInstance* arg0);
void func_84336520(ParticleEffectInstance* arg0);
void func_8433661C(ParticleEffectInstance* arg0);
void func_8433679C(ParticleEffectInstance* arg0);
void func_84336830(ParticleEffectInstance* arg0);
void func_843369AC(ParticleEffectInstance* arg0);
void func_84336A58(ParticleEffectInstance* arg0);
void func_84336B8C(void);
void func_84336C80(void);
void func_84336DD8(void);
void func_84336EE8(void);
void func_84337000(void);
void func_843371C0(void);
void func_843372D8(void);
void func_843374A4(void);
void func_843375B0(void);
void func_8433765C(void);
void func_84337664(void);
void func_8433766C(void);
void func_843378CC(void);
void func_843378D4(void);


void ParticleEffect_Type0_Stage1(ParticleEffectInstance* arg0);
void ParticleEffect_Type0_Main(ParticleEffectInstance* arg0);
void ParticleEffect_Type1_Stage1(ParticleEffectInstance* arg0, s16 arg1);
void ParticleEffect_Type1_Main(ParticleEffectInstance* arg0);
void ParticleEffect_Type2_Stage1(ParticleEffectInstance* arg0);
void ParticleEffect_Type2_RotationAdjust(ParticleEffectInstance* arg0);
void ParticleEffect_Type2_Main(ParticleEffectInstance* arg0);
void ParticleEffect_Type3_Stage1(ParticleEffectInstance* arg0);
void ParticleEffect_Type3_Main(ParticleEffectInstance* arg0);
void ParticleEffect_Type4_Stage1(ParticleEffectInstance* arg0);
void ParticleEffect_Type4_PostStage(ParticleEffectInstance* arg0);
void ParticleEffect_Type4_Main(ParticleEffectInstance* arg0);
void ParticleEffect_Type5_Stage1(ParticleEffectInstance* arg0);
void ParticleEffect_Type5_Main(ParticleEffectInstance* arg0);
void ParticleEffect_SmallGlow_Stage1(ParticleEffectInstance* arg0);
void ParticleEffect_SmallGlow(ParticleEffectInstance* arg0);
void ParticleEffect_SlowGlow_Stage1(ParticleEffectInstance* arg0);
void ParticleEffect_ComplexExplosion_Stage2(ParticleEffectInstance* arg0);
void ParticleEffect_DirectionalBurst_Stage1(ParticleEffectInstance* arg0);
void ParticleEffect_DirectionalBurst(ParticleEffectInstance* arg0);
void ParticleEffect_FastFlash(ParticleEffectInstance* arg0);
void ParticleEffect_ComplexExplosion(ParticleEffectInstance* arg0);
void ParticleEffect_SlowGlow(ParticleEffectInstance* arg0);
void ParticleEffect_FadeOut(ParticleEffectInstance* arg0);
void ParticleEffect_GravityVariant(ParticleEffectInstance* arg0);
void ParticleEffect_GravityWithColor(ParticleEffectInstance* arg0);
void ParticleEffect_HighSpeedFlash(ParticleEffectInstance* arg0);
void ParticleEffect_HighSpeedFlash_Main(ParticleEffectInstance* arg0);
void ParticleEffect_FadeOut_Stage1(ParticleEffectInstance* arg0);
void ParticleEffect_GravityVariant_Stage2(ParticleEffectInstance* arg0);
void ParticleEffect_GravityVariant_Main(ParticleEffectInstance* arg0);
void ParticleEffect_LargeBurst_Stage1(ParticleEffectInstance* arg0);
void ParticleEffect_LargeBurst(ParticleEffectInstance* arg0);
void ParticleEffect_MediumBurst(ParticleEffectInstance* arg0);
void ParticleEffect_MediumBurst_Main(ParticleEffectInstance* arg0);
void ParticleEffect_RotatingBurst(ParticleEffectInstance* arg0);
void ParticleEffect_RotatingBurst_Main(ParticleEffectInstance* arg0);
void ParticleEffect_LargeFireball(ParticleEffectInstance* arg0);
void ParticleEffect_LargeFireball_Main(ParticleEffectInstance* arg0);
void ParticleEffect_TimedFireball_Stage1(ParticleEffectInstance* arg0);
void ParticleEffect_TimedFireball(ParticleEffectInstance* arg0);
void ParticleEffect_Fireball_Stage1(ParticleEffectInstance* arg0);
void ParticleEffect_Fireball_Main(ParticleEffectInstance* arg0);
void ParticleEffect_Fireball_Stage2(ParticleEffectInstance* arg0);
void ParticleEffect_Fireball_Stage3(ParticleEffectInstance* arg0);
void ParticleEffect_Fireball_Stage4(ParticleEffectInstance* arg0);
void ParticleEffect_Fireball_Stage5(ParticleEffectInstance* arg0);
void ParticleEffect_Fireball_Stage6(ParticleEffectInstance* arg0);
void ParticleEffect_Fireball_Stage7(ParticleEffectInstance* arg0);
void ParticleEffect_RandomColor_Stage1(ParticleEffectInstance* arg0);
void ParticleEffect_RandomColor_Main(ParticleEffectInstance* arg0);
void ParticleEffect_ThreeWayBurst_Stage1(ParticleEffectInstance* arg0);
void ParticleEffect_ThreeWayBurst_Main(ParticleEffectInstance* arg0);
void ParticleEffect_SmallBurst_Stage1(ParticleEffectInstance* arg0);
void ParticleEffect_SmallBurst_Main(ParticleEffectInstance* arg0);
void ParticleEffect_MediumBurst_Stage1(ParticleEffectInstance* arg0);
void func_8433A858(ParticleEffectInstance* arg0);
void ParticleEffect_BrightBurst_Stage1(ParticleEffectInstance* arg0);
void ParticleEffect_BrightBurst_Main(ParticleEffectInstance* arg0);
void ParticleEffect_InitRotationAndSpeed(ParticleEffectInstance* arg0);
void ParticleEffect_UpdateStateMachine(ParticleEffectInstance* arg0);
void ParticleEffect_SetGlowParameters(ParticleEffectInstance* arg0);
void ParticleEffect_HandleMultiStage(ParticleEffectInstance* arg0);
void ParticleEffect_SetRotationBasedOnState(ParticleEffectInstance* arg0);
void ParticleEffect_StageBasedUpdate(ParticleEffectInstance* arg0);
void ParticleEffect_RandomizedPosition(ParticleEffectInstance* arg0);
void ParticleEffect_ConditionalTerminate(ParticleEffectInstance* arg0);
void SpawnLargeBurstEffect(void);
void SpawnLargeBurstIfNotActive(void);
void SpawnTimedFireballEffect(void);
void InitParticleEffectGroup_Basic(void);
void SpawnSmallGlowAndCustomEffect(void);
void InitComplexParticleSequence(void);
void InitExplosionEffectSet(void);
void InitAdvancedParticleCombo(void);
void InitParticleEffectSet_WithTexture53(void);
void InitParticleEffectSet_Alt(void);
void InitSmallGlowEffectSet(void);
void InitParticleEffectSet_Alt2(void);
void InitParticleEffectSet_WithFade(void);
void InitParticleEffectSet_WithDifferentTiming(void);
void InitParticleEffectSet_Single(void);
void InitParticleComboVariant(void);
void InitParticleEffectSet_WithMultiple(void);
void InitParticleEffectSet_WithTimedFireball(void);
void InitParticleEffectSet_WithCustomCallback(void);
void InitParticleEffectSet_Variant2(void);
void InitParticleEffectSet_WithComplex(void);
void InitParticleEffectSet_Variant3(void);
void InitParticleEffectSet_Variant4(void);
void InitParticleEffectSet_ThreeInstances(void);


void func_8433CC10(ParticleEffectInstance* arg0);
void func_8433CCFC(ParticleEffectInstance* arg0);
void func_8433CDAC(ParticleEffectInstance* arg0);
void func_8433CEA4(ParticleEffectInstance* arg0);
void func_8433CEFC(ParticleEffectInstance* arg0);
void func_8433CFA8(ParticleEffectInstance* arg0);
void func_8433D070(ParticleEffectInstance* arg0);
void func_8433D154(ParticleEffectInstance* arg0);
void func_8433D224(ParticleEffectInstance* arg0);
void func_8433D308(ParticleEffectInstance* arg0);
void func_8433D3B0(ParticleEffectInstance* arg0);
void func_8433D460(ParticleEffectInstance* arg0);
void func_8433D560(ParticleEffectInstance* arg0);
void func_8433D604(ParticleEffectInstance* arg0);
void func_8433D6EC(ParticleEffectInstance* arg0);
void func_8433D790(ParticleEffectInstance* arg0);
void func_8433D868(ParticleEffectInstance* arg0);
void func_8433D90C(ParticleEffectInstance* arg0);
void func_8433DA54(ParticleEffectInstance* arg0);
void func_8433DAF8(ParticleEffectInstance* arg0);
void func_8433DBDC(ParticleEffectInstance* arg0);
void func_8433DC80(void);
void func_8433DECC(void);
void func_8433DFF4(void);
void func_8433E124(void);
void func_8433E33C(void);
void func_8433E46C(void);
void func_8433E524(void);


void func_8433E650(ParticleEffectInstance* arg0);
void func_8433E758(ParticleEffectInstance* arg0);
void func_8433E840(ParticleEffectInstance* arg0);
void func_8433E8A8(ParticleEffectInstance* arg0);
void func_8433E950(ParticleEffectInstance* arg0);
void func_8433EA04(ParticleEffectInstance* arg0);
void func_8433EB0C(ParticleEffectInstance* arg0);
void func_8433EB9C(ParticleEffectInstance* arg0);
void func_8433EC40(ParticleEffectInstance* arg0);
void func_8433ED3C(ParticleEffectInstance* arg0);
void func_8433EE10(ParticleEffectInstance* arg0);
void func_8433F06C(ParticleEffectInstance* arg0);
void func_8433F208(ParticleEffectInstance* arg0);
void func_8433F270(ParticleEffectInstance* arg0);
s16 func_8433F3B4(void);
void func_8433F414(void);
void func_8433F4CC(void);
void func_8433F4EC(void);
void func_8433F5B4(void);
void func_8433F5D4(void);
void func_8433F758(void);
void func_8433F974(void);
void func_8433FAF8(void);
void func_8433FD30(void);


void Particle_SetWhiteColor(ParticleEffectInstance* arg0);
void Particle_StateHandler(ParticleEffectInstance* arg0);
void Particle_InitializeBasic(ParticleEffectInstance* arg0);
void Particle_UpdateStateAndScale(ParticleEffectInstance* arg0);
void Particle_SetPaletteColors24(ParticleEffectInstance* arg0);
void Particle_HandleCollisionAndFade(ParticleEffectInstance* arg0);
void Particle_InitializeTwirl(ParticleEffectInstance* arg0);
void Particle_UpdateComplexMovement(ParticleEffectInstance* arg0);
void Particle_InitializeBurst(ParticleEffectInstance* arg0);
void Particle_UpdateBurstState(ParticleEffectInstance* arg0);
void func_84340AC4(void);
void RegisterParticleEffects_62_32A640(void);
void RegisterParticleEffect_ComplexMovement(void);
void RegisterParticleEffect_Burst(void);


void ParticleEffect_RegisterExplosion(void);
void ParticleEffect_RegisterSmoke(void);
void ParticleEffect_RegisterDefault(void);
void ParticleEffect_InitBurstEffect(void);
void ParticleEffect_SetScaleAndSpeedByMoveId(ParticleEffectInstance*);
void ParticleEffect_Init(void);
void ParticleEffect_RegisterCallbacks(void);
void ParticleEffect_RegisterParticleNodes(void);
void ParticleEffect_RegisterEffectE0(void);
void ParticleEffect_RegisterEffectE0Alt(void);
void ParticleEffect_RegisterEffectE0Alt2(void);
void ParticleEffect_RegisterCombined(void);
void ParticleEffect_RegisterMultiple(void);
void ParticleEffect_RegisterSpecific(void);
void ParticleEffect_RegisterSparkle(void);
void ParticleEffect_RegisterAll(void);
void ParticleEffect_RegisterPaletteVariants(void);
void ParticleEffect_RegisterColorAnim(void);
void ParticleEffect_RegisterModeSpecific(void);
void ParticleEffect_RegisterLargeExplosion(void);
void ParticleEffect_RegisterLargeExplosionAndEffects(void);
void ParticleEffect_RegisterHandlers_Default(void);
void ParticleEffect_RegisterAnimationCallbacks(void);
void ParticleEffect_RegisterHandlers_Alternate(void);
void ParticleEffect_RegisterHandler_WithParticleData(void);
void ParticleEffect_RegisterHandler_416B0(void);
void ParticleEffect_RegisterMultipleHandlers(void);
void ParticleEffect_RegisterHandlers_473BC(void);
void ParticleEffect_AdjustParametersByAnimId(ParticleEffectInstance*);
void ParticleEffect_RegisterHandler_47448(void);


void Camera_SetLookAtReflect(void);
void ParticleEffect_ConfigureState(ParticleEffectInstance* arg0, s32 arg1);
void func_843416B0(ParticleEffectInstance* arg0);
void func_8434171C(ParticleEffectInstance* arg0);
void func_8434174C(ParticleEffectInstance* arg0);
void func_843417AC(ParticleEffectInstance* arg0);
void func_84341830(ParticleEffectInstance* arg0);
void func_84341860(ParticleEffectInstance* arg0);
Gfx* Gfx_LoadParticleTextureTile(Gfx* arg0, u8* arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5, s16 arg6, s16 arg7, s16 arg8, s16 arg9, s16 argA, s16 argB);
Gfx* Gfx_LoadParticleTextureTileFromStruct(Gfx* arg0, arg1_func_8434E21C* arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5, s16 arg6, s16 arg7, s16 arg8, s16 arg9, s16 argA, s16 argB);
void Gfx_SetParticlePrimEnvColors(Gfx* arg0);
void ParticleEffect_AllocateGfxIfNeeded(s32 arg0, arg1_func_84344CE8* arg1);
void Gfx_DrawParticleTextureWithParams(Gfx* arg0, arg1_func_8434E21C* arg1, UNUSED u16 arg2);
void ParticleEffect_AllocateGfxAndDraw(s32 arg0, arg1_func_84344CE8* arg1);
void ParticleEffect_ConfigDefaultParameters(ParticleEffectInstance* arg0);
void ParticleEffect_StateMachineHandler(ParticleEffectInstance* arg0);
void ParticleEffect_SetGravityByMoveId(ParticleEffectInstance* arg0);
void ParticleEffect_ConfigByMoveId(ParticleEffectInstance* arg0);
void ParticleEffect_HandleStateTransitions(ParticleEffectInstance* arg0);
void ParticleEffect_RegisterExplosion(void);
void ParticleEffect_RegisterSmoke(void);
void ParticleEffect_SetParamsByMoveId(ParticleEffectInstance* arg0);
void ParticleEffect_StartWithParams(ParticleEffectInstance* arg0);
void ParticleEffect_StateHandler(ParticleEffectInstance* arg0);
void ParticleEffect_RegisterDefault(void);
void ParticleEffect_SetVerticalOffsetByMoveId(ParticleEffectInstance* arg0);
void ParticleEffect_CreateBurstWithRotation(ParticleEffectInstance* arg0, s16 arg1);
void ParticleEffect_HandleBurstState(ParticleEffectInstance* arg0);
void ParticleEffect_InitBurstEffect(void);
void ParticleEffect_SetScaleAndSpeedByMoveId(ParticleEffectInstance* arg0);
void ParticleEffect_Init(void);
void ParticleEffect_Render(Gfx* arg0, s32 arg1, u16 arg2);
void ParticleEffect_CreateDisplayList(s32 arg0, arg1_func_84344CE8* arg1);
void ParticleEffect_ConfigureScale(ParticleEffectInstance* arg0);
void ParticleEffect_Start(ParticleEffectInstance* arg0, UNUSED s16 arg1);
void ParticleEffect_UpdateState(ParticleEffectInstance* arg0);
void ParticleEffect_DrawOverlay(Gfx* arg0, u16 arg1);
void ParticleEffect_CreateOverlayDL(s32 arg0, arg1_func_84344CE8* arg1);
void ParticleEffect_RegisterCallbacks(void);
void ParticleEffect_SetPaletteColors(ParticleEffectInstance* arg0);
void func_843441F8(ParticleEffectInstance* arg0);
void ParticleEffect_RegisterParticleNodes(void);
void ParticleEffect_SetPrimEnvFromPair(ParticleEffectInstance* arg0);
void ParticleEffect_StateHandler2(ParticleEffectInstance* arg0);
void ParticleEffect_RegisterEffectE0(void);
void ParticleEffect_RegisterEffectE0Alt(void);
void ParticleEffect_RegisterEffectE0Alt2(void);
void ParticleEffect_InitializeSmall(ParticleEffectInstance* arg0);
void ParticleEffect_SmallStateHandler(ParticleEffectInstance* arg0);
void ParticleEffect_FireworksInit(ParticleEffectInstance* arg0);
void ParticleEffect_FireworksState(ParticleEffectInstance* arg0);
void ParticleEffect_AdjustHeight(ParticleEffectInstance* arg0);
void ParticleEffect_RotatingInit(ParticleEffectInstance* arg0);
void ParticleEffect_RotatingState(ParticleEffectInstance* arg0);
void ParticleEffect_RegisterCombined(void);
void ParticleEffect_RegisterMultiple(void);
void ParticleEffect_RegisterSpecific(void);
void ParticleEffect_DrawSimple(Gfx* arg0, u8* arg1);
void ParticleEffect_CreateSimpleDL(s32 arg0, arg1_func_84344CE8* arg1);
void ParticleEffect_ExplosionInit(ParticleEffectInstance* arg0);
void ParticleEffect_ExplosionState(ParticleEffectInstance* arg0);
void ParticleEffect_SparkleInit(ParticleEffectInstance* arg0);
void ParticleEffect_SparkleState(ParticleEffectInstance* arg0);
void ParticleEffect_RegisterSparkle(void);
void ParticleEffect_RegisterAll(void);
void ParticleEffect_DrawNode(Gfx* arg0, s32 arg1, u16 arg2);
void ParticleEffect_CreateNodeDL(s32 arg0, arg1_func_84344CE8* arg1);
void ParticleEffect_DrawNodeVariant(Gfx* arg0, arg1_func_8434E21C* arg1, UNUSED u16 arg2);
void ParticleEffect_CreateNodeVariantDL(s32 arg0, arg1_func_84344CE8* arg1);
void ParticleEffect_DrawSimple2(Gfx* arg0, u8* arg1, UNUSED u16 arg2);
void ParticleEffect_CreateSimple2DL(s32 arg0, arg1_func_84344CE8* arg1);
void func_84345490(void);
void ParticleEffect_GetVerticalOffset(ParticleEffectInstance* arg0);
void ParticleEffect_ConfigureFromPalette(ParticleEffectInstance* arg0);
void ParticleEffect_PaletteState(ParticleEffectInstance* arg0);
void ParticleEffect_RegisterPaletteVariants(void);
void ParticleEffect_SetupColorAndAnim(ParticleEffectInstance* arg0);
void ParticleEffect_ColorAnimState(ParticleEffectInstance* arg0);
void ParticleEffect_ColorAnimStateAlt(ParticleEffectInstance* arg0);
void ParticleEffect_DrawColorNode(Gfx* arg0, UNUSED s32 arg1, UNUSED u16 arg2);
void ParticleEffect_CreateColorNodeDL(s32 arg0, arg1_func_84344CE8* arg1);
void ParticleEffect_RegisterColorAnim(void);
void ParticleEffect_RegisterModeSpecific(void);
void ParticleEffect_LargeExplosionInit(ParticleEffectInstance* arg0);
void ParticleEffect_LargeExplosionState(ParticleEffectInstance* arg0);
void ParticleEffect_RegisterLargeExplosion(void);
void ParticleEffect_LargeExplosionInitDup(ParticleEffectInstance* arg0);
void ParticleEffect_LargeExplosionStateDup(ParticleEffectInstance* arg0);
void ParticleEffect_RegisterLargeExplosionAndEffects(void);
void ParticleEffect_DrawSpecial(Gfx* arg0, s32 arg1, u16 arg2);
void ParticleEffect_CreateSpecialDL(s32 arg0, arg1_func_84344CE8* arg1);
void ParticleEffect_DrawSimpleColor(Gfx* arg0, UNUSED s32 arg1, UNUSED u16 arg2);
void ParticleEffect_CreateSimpleColorDL(s32 arg0, arg1_func_84344CE8* arg1);
void ParticleEffect_SetAnimByPalette(ParticleEffectInstance* arg0);
void ParticleEffect_AnimState(ParticleEffectInstance* arg0);
void ParticleEffect_SetOffsetsByPalette(ParticleEffectInstance* arg0);
void ParticleEffect_OffsetState(ParticleEffectInstance* arg0);
void Particle_ConfigureScaleSpeed(ParticleEffectInstance* arg0);
void ParticleEffect_InitWithResource(ParticleEffectInstance* arg0);
void func_8434669C(ParticleEffectInstance* arg0);
void Gfx_DrawParticleAlpha(Gfx* arg0, s32 arg1, u16 arg2);
void Particle_CreateDisplayList_TypeA(s32 arg0, arg1_func_84344CE8* arg1);
void Gfx_DrawParticleTexture4b(Gfx* arg0, u8* arg1, UNUSED u16 arg2);
void Particle_CreateDisplayList_Texture4b(s32 arg0, arg1_func_84344CE8* arg1);
void Gfx_DrawParticleGreenPrim(Gfx* arg0, u8* arg1, UNUSED u16 arg2);
void Particle_CreateDisplayList_GreenPrim(s32 arg0, arg1_func_84344CE8* arg1);
void ParticleEffect_RegisterHandlers_Default(void);
void ParticleEffect_RegisterAnimationCallbacks(void);
void ParticleEffect_RegisterHandlers_Alternate(void);
void ParticleEffect_RegisterHandler_WithParticleData(void);
void ParticleEffect_RegisterHandler_416B0(void);
void ParticleEffect_RegisterMultipleHandlers(void);
void ParticleEffect_InitLargeScale(ParticleEffectInstance* arg0);
void ParticleEffect_StateHandler_47108(ParticleEffectInstance* arg0);
void Gfx_DrawParticleCyanEnv(Gfx* arg0, arg1_func_8434E21C* arg1, UNUSED u16 arg2);
void Particle_CreateDisplayList_CyanEnv(s32 arg0, arg1_func_84344CE8* arg1);
void Gfx_DrawParticleBluePrim(Gfx* arg0, arg1_func_8434E21C* arg1, UNUSED u16 arg2);
void Particle_CreateDisplayList_BluePrim(s32 arg0, arg1_func_84344CE8* arg1);
void ParticleEffect_RegisterHandlers_473BC(void);
void ParticleEffect_RegisterHandler_47448(void);
void ParticleEffect_AdjustParametersByAnimId(ParticleEffectInstance* arg0);
void ParticleEffect_StateHandler_47670(ParticleEffectInstance* arg0);
void ParticleEffect_InitStandard(ParticleEffectInstance* arg0);
void ParticleEffect_StateHandler_4775C(ParticleEffectInstance* arg0);
void ParticleEffect_InitRandomized(ParticleEffectInstance* arg0);
void ParticleEffect_StateHandler_47904(ParticleEffectInstance* arg0);
void ParticleEffect_InitVariantA(ParticleEffectInstance* arg0);
void ParticleEffect_StateHandler_47AF0(ParticleEffectInstance* arg0);
void Gfx_DrawParticleCustomColors(Gfx* arg0, arg1_func_8434E21C* arg1, UNUSED u16 arg2);
void Particle_CreateDisplayList_CustomColors(s32 arg0, arg1_func_84344CE8* arg1);
void ParticleEffect_StateHandler_47D74(ParticleEffectInstance* arg0);
void ParticleEffect_StateHandler_47E9C(ParticleEffectInstance* arg0);
void ParticleEffect_StateHandler_48058(ParticleEffectInstance* arg0);
void ParticleEffect_InitComplex_48194(ParticleEffectInstance* arg0);
void ParticleEffect_StateHandler_482D4(ParticleEffectInstance* arg0);
void ParticleEffect_InitComplex_483D4(ParticleEffectInstance* arg0);
void ParticleEffect_StateHandler_48514(ParticleEffectInstance* arg0);
void ParticleEffect_RegisterAll_48630(void);
void ParticleEffect_RegisterAll_489FC(void);
void func_84348C6C(UNUSED s32 arg0, UNUSED s32 arg1);
void func_84348C78(UNUSED s32 arg0, UNUSED s32 arg1);
void ParticleEffect_InitSparkle(ParticleEffectInstance* arg0);
void ParticleEffect_StateHandler_48D4C(ParticleEffectInstance* arg0);
void Gfx_DrawParticleFromTempColors(Gfx* arg0, s32 arg1, u16 arg2);
void Particle_CreateDisplayList_TempColors(s32 arg0, arg1_func_84344CE8* arg1);
void ParticleEffect_RegisterHandler_49058(void);
void ParticleEffect_RegisterHandler_490A8(void);
void ParticleEffect_RegisterHandler_49108(void);
void ParticleEffect_Trigger56A74(void);
void ParticleEffect_ConfigureAndTrigger_4917C(void);
void Gfx_DrawParticleVariant_D4(Gfx* arg0, u8* arg1, UNUSED u16 arg2);
void Particle_CreateDisplayList_Variant_D4(s32 arg0, arg1_func_84344CE8* arg1);
void Gfx_DrawParticleVariant_AC(Gfx* arg0, u8* arg1, UNUSED u16 arg2);
void Particle_CreateDisplayList_Variant_AC(s32 arg0, arg1_func_84344CE8* arg1);
void ParticleEffect_RegisterHandler_49384(void);
f32 ParticleEffect_GetScaleFactorByAnimId(ParticleEffectInstance* arg0);
void ParticleEffect_StateHandler_494AC(ParticleEffectInstance* arg0);
void ParticleEffect_RegisterHandlers_49504(void);
void ParticleEffect_ApplySpecialEffect_495F0(ParticleEffectInstance* arg0);
void ParticleEffect_RegisterHandler_49628(void);
void ParticleEffect_RegisterHandlers_4967C(void);
void ParticleEffect_AdjustVerticalOffset_497A8(ParticleEffectInstance* arg0);
void ParticleEffect_RegisterHandler_49830(void);
void ParticleEffect_RegisterHandler_498D8(void);
void ParticleEffect_AdjustSizeByAnimId(ParticleEffectInstance* arg0);
void ParticleEffect_RegisterDefaultTexture(void);
void ParticleEffect_InitWithResource_A70(ParticleEffectInstance* arg0);
void ParticleEffect_StateHandler_49AE8(ParticleEffectInstance* arg0);
void ParticleEffect_InitWithOffsets_B50(ParticleEffectInstance* arg0);
void ParticleEffect_StateHandler_49C74(ParticleEffectInstance* arg0);
void Gfx_DrawParticlePaletteBased(Gfx* arg0, u8* arg1, UNUSED u16 arg2);
void func_84349F80(s32 arg0, arg1_func_84344CE8* arg1);
void func_84349FC8(Gfx* arg0, UNUSED arg1_func_8434E21C* arg1, UNUSED u16 arg2);
void func_8434A18C(s32 arg0, arg1_func_84344CE8* arg1);
s16 func_8434A1D4(void);
s16 func_8434A244(void);
s16 func_8434A2B4(void);
void func_8434A324(void);
void func_8434A384(void);
f32 func_8434A574(ParticleEffectInstance* arg0);
void func_8434A654(Gfx* arg0, arg1_func_8434E21C* arg1, UNUSED u16 arg2);
void func_8434A6D8(s32 arg0, arg1_func_84344CE8* arg1);
void func_8434A720(Gfx* arg0, UNUSED arg1_func_8434E21C* arg1, UNUSED u16 arg2);
void func_8434A794(s32 arg0, arg1_func_84344CE8* arg1);
void func_8434A7DC(void);
void func_8434A844(void);
void func_8434A898(void);
void func_8434A930(void);
void func_8434A9CC(void);
void func_8434A9EC(void);
void func_8434AA6C(void);
void func_8434AAEC(Gfx* arg0, u8 arg1, UNUSED u16 arg2);
void func_8434AC44(s32 arg0, arg1_func_84344CE8* arg1);
void func_8434AC8C(void);
void func_8434ACEC(void);
void func_8434AD1C(void);
void func_8434AD70(void);
f32 func_8434AE68(ParticleEffectInstance* arg0);
void func_8434B000(void);
void func_8434B064(void);
void func_8434B0D8(ParticleEffectInstance* arg0);
void func_8434B14C(ParticleEffectInstance* arg0);
void func_8434B21C(ParticleEffectInstance* arg0);
void func_8434B2B8(Gfx* arg0, u8* arg1, UNUSED u16 arg2);
void func_8434BA28(s32 arg0, arg1_func_84344CE8* arg1);
void func_8434BA70(void);
void func_8434BCD4(void);
void func_8434BF2C(void);
void func_8434C070(void);
void func_8434C0C4(void);
void func_8434C144(void);
void func_8434C214(ParticleEffectInstance* arg0);
void func_8434C29C(ParticleEffectInstance* arg0);
void func_8434C320(ParticleEffectInstance* arg0);
void func_8434C3A8(ParticleEffectInstance* arg0);
void func_8434C3F0(Gfx* arg0, u8 arg1, UNUSED u16 arg2);
void func_8434C548(s32 arg0, arg1_func_84344CE8* arg1);
void func_8434C590(void);
void func_8434C5F0(void);
void func_8434C618(void);
void func_8434C720(void);
void func_8434C814(Gfx* arg0, u8* arg1, UNUSED u16 arg2);
void func_8434CA48(s32 arg0, arg1_func_84344CE8* arg1);
f32 func_8434CA90(ParticleEffectInstance* arg0);
void func_8434CAD8(void);
void func_8434CC68(void);
void func_8434CE14(void);
void func_8434CF64(void);
void func_8434D0F8(void);
void func_8434D168(ParticleEffectInstance* arg0);
void func_8434D1B0(ParticleEffectInstance* arg0);
void func_8434D260(ParticleEffectInstance* arg0);
void func_8434D2E0(ParticleEffectInstance* arg0);
void func_8434D448(void);
void func_8434D4A0(ParticleEffectInstance* arg0);
void func_8434D530(ParticleEffectInstance* arg0);
void func_8434D5EC(void);
void func_8434D6C0(ParticleEffectInstance* arg0);
void func_8434D72C(ParticleEffectInstance* arg0);
void func_8434D77C(Gfx* arg0, arg1_func_8434E21C* arg1, UNUSED u16 arg2);
void func_8434D890(s32 arg0, arg1_func_84344CE8* arg1);
void func_8434D8D8(void);
void func_8434D938(void);
void func_8434D9F8(ParticleEffectInstance* arg0);
void func_8434DA94(void);
void func_8434DB40(void);
void func_8434DBEC(void);
void func_8434DD08(void);
f32 GetParticleScaleForEffect(ParticleEffectInstance* arg0);
void ParticleEffect_InitSmallExplosion(void);
void ParticleEffect_InitLargeExplosion(void);
void ParticleEffect_InitFire(void);
void ParticleEffect_InitSmoke(void);
void ParticleEffect_PlaySoundAndReset(void);
void ParticleEffect_DrawQuad(Gfx* arg0, arg1_func_8434E21C* arg1, UNUSED u16 arg2);
void ParticleEffect_AllocateDisplayList(s32 arg0, arg1_func_84344CE8* arg1);
void ParticleEffect_TriggerEffect(void);
void ParticleEffect_TriggerSpecial(void);
void func_8434E7CC(ParticleEffectInstance* arg0);
void ParticleEffect_TriggerAnother(void);
void ParticleEffect_TriggerDefault1(void);
void ParticleEffect_TriggerDefault2(void);
void ParticleEffect_TriggerDefault3(void);
void ParticleEffect_TriggerDefault4(void);
void ParticleEffect_ColorStateHandler(ParticleEffectInstance* arg0);
void ParticleEffect_CreateWithCallback(void);
void ParticleEffect_CreateCallback(void);
void ParticleEffect_ColorStateHandler2(ParticleEffectInstance* arg0);
void ParticleEffect_CreateColorVariant(void);
void ParticleEffect_SetMode(void);
void ParticleEffect_ConfigureParameters(ParticleEffectInstance* arg0);
void ParticleEffect_MainStateHandler(ParticleEffectInstance* arg0);
void ParticleEffect_CreateVariant45(void);
void ParticleEffect_CreateVariant47(void);
void ParticleEffect_CreateTypeX(void);
void ParticleEffect_CreateSmoke(void);
void ParticleEffect_CreateSmokeHighPriority(void);
void ParticleEffect_ConfigureParameters_Slow(ParticleEffectInstance* arg0);
void func_8434F248(ParticleEffectInstance* arg0);
void ParticleEffect_CreateDual(void);
void Particle_SetDirectionOffsets(ParticleEffectInstance* arg0);
void Particle_HandleState(ParticleEffectInstance* arg0);
void Particle_SetupSpecialOffsets(ParticleEffectInstance* arg0);
void Particle_HandleState_Special(ParticleEffectInstance* arg0);
void func_8434F888(ParticleEffectInstance* arg0);
void Particle_HandleState_SpecialColor(ParticleEffectInstance* arg0);
void func_8434FB3C(ParticleEffectInstance* arg0);
void Particle_HandleCollisionResponse(ParticleEffectInstance* arg0);
void func_8434FCC4(ParticleEffectInstance* arg0);
void Particle_HandleCollisionResponse_ExplosionAlt(ParticleEffectInstance* arg0);
void func_8434FE58(ParticleEffectInstance* arg0);
void Particle_HandleState_Directional(ParticleEffectInstance* arg0);
void Particle_HandleState_Directional_Scale(ParticleEffectInstance* arg0);
void Particle_HandleState_Directional_ScaleAlt(ParticleEffectInstance* arg0);
void func_843501CC(ParticleEffectInstance* arg0);
void func_84350260(ParticleEffectInstance* arg0);
void func_84350330(ParticleEffectInstance* arg0);
void func_8435043C(ParticleEffectInstance* arg0);
void func_84350520(ParticleEffectInstance* arg0);
void func_84350634(ParticleEffectInstance* arg0);
void func_84350728(ParticleEffectInstance* arg0);
void func_84350828(ParticleEffectInstance* arg0);
void func_843508F0(ParticleEffectInstance* arg0);
void func_84350A04(ParticleEffectInstance* arg0);
void func_84350AFC(ParticleEffectInstance* arg0);
void func_84350BE4(ParticleEffectInstance* arg0);
void func_84350CD8(ParticleEffectInstance* arg0);
void func_84350DAC(ParticleEffectInstance* arg0);
void func_84350EC8(ParticleEffectInstance* arg0);
void func_84350FC0(ParticleEffectInstance* arg0);
void func_84351090(ParticleEffectInstance* arg0);
void func_84351144(ParticleEffectInstance* arg0);
void func_84351264(ParticleEffectInstance* arg0);
void func_843512AC(ParticleEffectInstance* arg0);
void func_84351330(ParticleEffectInstance* arg0);
void func_843513F4(ParticleEffectInstance* arg0);
void func_843514B4(ParticleEffectInstance* arg0);
void func_843515C8(ParticleEffectInstance* arg0);
void func_843516A0(ParticleEffectInstance* arg0);
void func_84351984(ParticleEffectInstance* arg0);
void func_84351ADC(ParticleEffectInstance* arg0);
void func_84351BCC(ParticleEffectInstance* arg0);
void ParticleNode_CreateExplosion(ParticleEffectInstance* arg0);
void func_84351D20(ParticleEffectInstance* arg0);
void func_84351D70(ParticleEffectInstance* arg0);
void func_8435226C(ParticleEffectInstance* arg0);
void ParticleEffect_FireworkStage1(ParticleEffectInstance* arg0);
void ParticleEffect_FireworkHandler(ParticleEffectInstance* arg0);
void ParticleEffect_FireworkHandler2(ParticleEffectInstance* arg0);
void func_84352620(ParticleEffectInstance* arg0);
void ParticleEffect_SparkleHandler(ParticleEffectInstance* arg0);
void func_84352754(ParticleEffectInstance* arg0);
void ParticleEffect_FireworkMain(ParticleEffectInstance* arg0);
void ParticleEffect_FireworkColors(ParticleEffectInstance* arg0);
void ParticleEffect_FireworkMain2(ParticleEffectInstance* arg0);
void ParticleEffect_ModeSpecificColors(ParticleEffectInstance* arg0);
s32 ParticleEffect_ModeSpecificHandler(ParticleEffectInstance* arg0);
void ParticleEffect_SmallBurst(ParticleEffectInstance* arg0);
void ParticleEffect_SmallBurstHandler(ParticleEffectInstance* arg0);
void ParticleEffect_RandomDirection(ParticleEffectInstance* arg0);
void ParticleEffect_RandomDirectionHandler(ParticleEffectInstance* arg0);
void ParticleEffect_RandomDirectionDuplicate(ParticleEffectInstance* arg0);
void ParticleEffect_RandomDirectionHandler2(ParticleEffectInstance* arg0);
void ParticleEffect_SetColorFromMode(ParticleEffectInstance* arg0);
void ParticleEffect_ColorfulBurst(ParticleEffectInstance* arg0);
void ParticleEffect_ColorfulBurstHandler(ParticleEffectInstance* arg0);
void ParticleEffect_SimpleColor(ParticleEffectInstance* arg0);
void ParticleEffect_SimpleColorHandler(ParticleEffectInstance* arg0);
void ParticleEffect_RandomSpeed(ParticleEffectInstance* arg0);
void ParticleEffect_RandomSpeedHandler(ParticleEffectInstance* arg0);
void ParticleEffect_ApplyModeSpecifics(ParticleEffectInstance* arg0);
void ParticleEffect_BasicSetup(ParticleEffectInstance* arg0);
void ParticleEffect_BasicSetupHandler(ParticleEffectInstance* arg0);
void ParticleEffect_AdjustLifetime(ParticleEffectInstance* arg0);
void ParticleEffect_AdvancedSetup(ParticleEffectInstance* arg0);
void ParticleEffect_GravityAdjust(ParticleEffectInstance* arg0);
void ParticleEffect_ConditionalStop(ParticleEffectInstance* arg0);
void ParticleEffect_RandomRotationSetup(ParticleEffectInstance* arg0);
void ParticleEffect_RandomRotationHandler(ParticleEffectInstance* arg0);
void ParticleEffect_SmallScatter(ParticleEffectInstance* arg0);
void ParticleEffect_SmallScatterHandler(ParticleEffectInstance* arg0);
void ParticleEffect_DirectionalInit(ParticleEffectInstance* arg0);
void func_84355330(ParticleEffectInstance* arg0);
void func_843553B4(void);
void func_843553BC(ParticleEffectInstance* arg0);
void ParticleEffect_FadeAndScale(ParticleEffectInstance* arg0);
void ParticleEffect_SpeedAndAlpha(ParticleEffectInstance* arg0);
void ParticleEffect_RotationAndColor(ParticleEffectInstance* arg0);
void ParticleEffect_ConditionalUpdate(ParticleEffectInstance* arg0);
void ParticleEffect_RandomRotation(ParticleEffectInstance* arg0);
void func_8435581C(ParticleEffectInstance* arg0);
void ParticleEffect_PrimColorAndEnv(ParticleEffectInstance* arg0);
void ParticleEffect_ComplexSequence(ParticleEffectInstance* arg0);
void ParticleEffect_Sparkle(ParticleEffectInstance* arg0);
void func_84355B8C(ParticleEffectInstance* arg0);
void ParticleEffect_ExplosionScale(ParticleEffectInstance* arg0);
void ParticleEffect_ExplosionVariant(ParticleEffectInstance* arg0);
void ParticleEffect_InitializeGroup(void);
void ParticleEffect_ConfigB(void);
void ParticleEffect_ConfigA(void);
void ParticleEffect_ConfigVariantA(void);
void ParticleEffect_ConfigVariantB(void);
void ParticleEffect_SpecialSetupA(void);
void ParticleEffect_SpecialSetupB(void);
void ParticleEffect_SpecialSetupC(void);
void ParticleEffect_TextureSetup(void);
void ParticleEffect_ModeSetup(void);
void ParticleEffect_CollisionSetup(void);
void ParticleEffect_TextureAssign(void);
void ParticleEffect_AdditionalSetupA(void);
void ParticleEffect_AdditionalSetupB(void);
void ParticleEffect_CombinedSetupA(void);
void ParticleEffect_CombinedSetupB(void);
void ParticleEffect_SimpleSetup(void);
void ParticleEffect_SmallSetup(void);
void ParticleEffect_MultiHandleSetup(void);
void ParticleEffect_ExtraNodeSetup(void);
void ParticleEffect_TextureNodeSetup(void);
void ParticleEffect_HandleStateSetup(void);
void ParticleEffect_HandleCollisionSetup(void);
void ParticleEffect_DynamicStateSetup(void);
void ParticleEffect_DynamicCollisionSetup(void);
void ParticleEffect_ConditionalStateSetup(void);
void ParticleEffect_CollisionResponseSwitch(void);
void ParticleEffect_CollisionAndBurstSetup(void);
void ParticleEffect_StateCollisionSetupA(void);
void ParticleEffect_StateCollisionSetupB(void);
void ParticleEffect_AdditionalNodeSetup(void);
void ParticleEffect_SpecialCollisionSetup(void);
void ParticleEffect_SmallNodeSetup(void);
void ParticleEffect_MultiTextureSetup(void);
void ParticleEffect_SmallNodeSetupB(void);
void ParticleEffect_MultiNodeSetup(void);
void ParticleEffect_ModeSpecificSetup(void);
void ParticleEffect_ComplexNodeSetup(void);
void ParticleEffect_SimpleNodeSetup(void);
void ParticleEffect_AdvancedModeSetup(void);
void ParticleEffect_FullSetupA(void);
void ParticleEffect_FullSetupB(void);
void ParticleEffect_FinalSetupA(void);
void ParticleEffect_FinalSetupB(void);
void ParticleEffect_FinalSetupC(void);
void ParticleEffect_AdditionalNodeA(void);
void ParticleEffect_MultiNodeA(void);
void ParticleEffect_MultiNodeB(void);
void ParticleEffect_MultiNodeC(void);
void ParticleEffect_MultiNodeD(void);
void ParticleEffect_CreateMultipleNodes(s32 arg0);
void ParticleEffect_GroupSetupA(void);
void ParticleEffect_GroupSetupB(void);
void ParticleEffect_SimpleGroupSetup(void);
void ParticleEffect_ComplexGroupSetup(void);
void ParticleEffect_FinalGroupSetup(void);


void func_84358FF0(void);
void func_84358FF8(void);
void RenderPrimColorRect(u8, u8, u8, u8);
void Ui_DrawPanel(CameraStruct*);


void func_843592E0(void);
void func_843592E8(void);
void func_843592F0(void);
void func_843592F8(void);
void func_84359300(void);
void func_84359308(void);
void func_84359310(void);
void func_84359318(void);
void func_84359320(void);
void func_84359328(void);
void func_84359330(UNUSED s32 arg0);
void func_84359338(UNUSED s32 arg0);
void func_84359340(void);
void func_84359348(void);
void func_84359380(void);
void func_843593A0(void);
void func_843593A8(void);
s32 func_843593B0(void);
s32 func_843593B8(void);
void func_843593C0(void);
void func_843593C8(void);
void func_843593D0(Vec3f* arg0);
void func_843593F0(Vec3f* arg0);
void func_84359410(Vec3f* arg0);
void func_84359430(Vec3f* arg0);
f32 func_84359450(void);
f32 func_84359470(void);
void CalcVectorATtoDM(f32* arg0, f32* arg1, f32* arg2, f32* arg3, f32* arg4, f32* arg5);
void CalcVectorATtoDM2(f32* arg0, f32* arg1, f32* arg2, f32* arg3, f32* arg4, f32* arg5);
void InitEffectMatrix(void);
void SpawnParticleEmitters_Default(void);
s32 func_843596DC(void);
void func_843596FC(void);
void SpawnParticleEmitters_Alt(void);
s32 func_843597AC(void);
void func_843597CC(void);
void SpawnParticleEmitters_Dual(void);
s32 func_8435989C(void);
void func_843598BC(void);
void SpawnParticleEmitters_Alt2(void);
s32 func_8435998C(void);
void func_843599AC(void);
void WaterHeightMap_InitByCameraX(void);
s32 func_84359A6C(void);
void func_84359A8C(void);
void func_84359AE0(void);
s32 func_84359AE8(void);
void func_84359AF0(void);
void SpawnRandomizedParticleEffect(void);
void StartParticleEffectA(void);
s32 UpdateParticleEffectA(void);
void RenderParticleEffectA(void);
void InitTrailEffect(void);
s32 UpdateTrailEffect(void);
void RenderTrailEffect(void);
void SpawnWaterParticleEffect(void);
void StartWaterParticleEffectB(void);
s32 UpdateWaterParticleEffectB(void);
void RenderWaterParticleEffectB(void);
void SpawnRandomizedParticleEffectC(void);
void StartParticleEffectC(void);
s32 UpdateParticleEffectC(void);
void RenderParticleEffectC(void);
void InitTrailEffectVariant(void);
s32 UpdateTrailEffectVariant(void);
void RenderTrailEffectVariant(void);
void InitTrailEffectVariant2(void);
s32 UpdateTrailEffectVariant2(void);
void RenderTrailEffectVariant2(void);
void SpawnRandomizedParticleEffectD(void);
void StartParticleEffectE(void);
s32 UpdateParticleEffectE(void);
void RenderParticleEffectE(void);
void StartEffectF(void);
s32 UpdateEffectF(void);
void RenderWaterParticleEffectF(void);
void StartWaterParticlePoolG(void);
s32 UpdateWaterParticlePoolG(void);
void RenderWaterParticlePoolG(void);
void InitWaterSurface(void);
s32 UpdateWaterSurface(void);
void RenderWaterSurface(void);
void InitWaterSurfaceVariant(void);
s32 UpdateWaterSurfaceVariant(void);
void RenderWaterSurfaceVariant(void);
void InitWaterEffectVariant(void);
s32 UpdateWaterEffectVariant(void);
void RenderWaterEffectVariant(void);
void ResetAllParticleSystems(void);
s32 UpdateWaterParticleSystemPhaseA(void);
void RenderWaterParticleSystemPhaseA(void);
void ResetParticleEmittersPhaseB(void);
s32 UpdateParticleEmittersPhaseB(void);
void RenderParticleEmittersPhaseB(void);
void StartParticleSystemI(void);
s32 UpdateParticleSystemI(void);
void RenderParticleSystemI(void);
void CreateSimpleParticleEmitter(void);
void StartParticleEffectD(void);
s32 UpdateParticleEffectD(void);
void RenderParticleEffectD(void);
void ConfigureWaterParticleSystemCombine(void);
void InitWaterParticleSystemsCombined(void);
s32 UpdateWaterParticleSystemsCombined(void);
void RenderCombinedWaterEffect(void);
void SpawnWaterEffectVariant1(void);
void StartWaterEffectH(void);
s32 UpdateWaterEffectH(void);
void RenderWaterEffectH(void);
void ConfigureWaterEffectVariant2(void);
void InitWaterEffectVariant2(void);
s32 UpdateWaterEffectVariant2(void);
void RenderWaterEffectVariant2(void);
void ConfigureWaterEffectVariant3(void);
void InitWaterEffectVariant3(void);
s32 UpdateWaterEffectVariant3(void);
void RenderWaterEffectVariant3(void);
void ConfigureWaterEffectVariant4(void);
void InitWaterEffectVariant4(void);
s32 UpdateWaterEffectVariant4(void);
void RenderWaterEffectVariant4(void);
void ConfigureWaterEffectVariant5(void);
void SpawnWaterEffectVariant5(void);
void InitWaterEffectVariant5(void);
s32 UpdateWaterEffectD(void);
void RenderCombinedWaterEffectD(void);


void ParticleEmitters_Reset(void);
void ParticleEmitter_SetColors(unk_D_843925E0* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9);
void func_8435CAE8(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, s32 arg5);
void ParticleEmitter_UpdateFade(unk_D_843925E0* arg0);
s32 ParticleEmitter_Update(unk_D_843925E0* arg0);
s32 ParticleEmitters_Tick(void);
Gfx* ParticleEmitter_BuildVertexBuffer(Gfx* arg0, unk_D_843925E0* arg1);
Gfx* ParticleEmitters_Render(Gfx* arg0);
void func_8435DED0(unk_D_843975E8* arg0, f32 arg1);
f32 func_8435E158(f32 arg0, f32 arg1, f32* arg2);
s32 WaterHeightMap_Update(void);
void WaterHeightMap_Init(s32 arg0, s16 arg1, s16 arg2);
s32 func_8435EDF8(void);
Gfx* WaterSurface_Render(Gfx* arg0);


void Trail_Init(f32 arg0, f32 arg1, f32 arg2, f32 arg3, u8 arg4, u8 arg5, u8 arg6, u8 arg7, u8 arg8, u8 arg9);
f32 Trail_GetWidthScale(void);
s32 Trail_Update(void);
Gfx* Trail_Render(Gfx* arg0);
void func_843605C0(void);
void ParticleEmitter_AddSimple(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, s16 arg6, u8 arg7, u8 arg8, u8 arg9, u8 argA, f32 argB, f32 argC, f32 argD, s16 argE);
void ParticleEmitter_AddSimpleNoFade(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, s16 arg6, u8 arg7, u8 arg8, u8 arg9, u8 argA, f32 argB, f32 argC, f32 argD, s16 argE);
void ParticleEmitter_AddRandomized(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, s16 arg6, u8 arg7, u8 arg8, u8 arg9, u8 argA, u8 argB, u8 argC, u8 argD, f32 argE, f32 argF, f32 arg10, s16 arg11);
void func_84360EFC(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, s16 arg6, u8 arg7, u8 arg8, u8 arg9, u8 argA, u8 argB, u8 argC, u8 argD, f32 argE, f32 argF, f32 arg10, s16 arg11);
void func_843612F8(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, s16 arg6, u8 arg7, u8 arg8, u8 arg9, u8 argA, f32 argB, f32 argC, f32 argD, s16 argE);
void func_843616B0(f32 arg0, UNUSED Vec3f* arg1, Vec3f* arg2, f32 arg3, UNUSED f32 arg4, UNUSED f32 arg5, UNUSED f32 arg6);
void func_84361744(unk_D_84398F50* arg0);
s32 func_84361FB0(void);
Gfx* func_84362084(Gfx* arg0);


void WaterSurface_Init(s16 arg0);
void WaterSurface_CalcNormal(s32 arg0, s32 arg1);
void WaterSurface_FillVertex(WaterSurfaceVertex* arg0, Vtx* arg1);
s32 WaterSurface_Update(void);
void WaterSurface_SetupMatrix(void);
Gfx* WaterSurface_Draw(Gfx* arg0);


void WaterSurface_UpdateAngles(s16 arg0, s16 arg1);
void WaterSurface_Initialize(s16 arg0);
void WaterSurface_CalculateNormal(s32 arg0, s32 arg1);
void WaterSurface_VertexFromData(unk_D_8439E680_0014* arg0, Vtx* arg1);
s32 WaterSurface_Tick(void);
void WaterSurface_CalcViewMatrix(void);
Gfx* WaterSurface_DrawLit(Gfx* arg0);


void func_84365A10(s16 arg0);
void WaterSurface_CalcVertexNormal(s32 arg0, s32 arg1);
void WaterSurface_PackVertex(WaterSurfaceVertex* arg0, Vtx* arg1);
s32 func_843661D0(void);
void func_8436643C(void);
Gfx* func_84366560(Gfx* arg0);


void WaterParticle_Reset(void);
void WaterParticle_Spawn(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, u8 arg6, u8 arg7, u8 arg8, u8 arg9, f32 argA, s16 argB);
void WaterParticle_TransformVertex(f32 arg0, Vec3f* arg1, f32 arg2);
void WaterParticle_UpdateSegment(unk_D_843A22C0* arg0);
s32 WaterParticle_TickAll(void);
Gfx* WaterParticle_RenderAll(Gfx* arg0);


Gfx* Gfx_DrawThickLine(Gfx* arg0, Vec3f* arg1, Vec3f* arg2, Vec3f* arg3, f32 arg4, u8 arg5, u8 arg6, u8 arg7, u8 arg8);


void WaterParticleSystem_ResetAll(void);
void WaterParticleSystem_Spawn(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, u8 arg6, u8 arg7, u8 arg8, u8 arg9, f32 argA, f32 argB, f32 argC, s16 argD);
void WaterParticle_CalcOffset(f32 arg0, Vec3f* arg1, f32 arg2, f32 arg3);
void WaterParticleSystem_UpdateEmitter(WaterParticleEmitter* arg0);
s32 WaterParticleSystem_UpdateAll(void);
Gfx* WaterParticleSystem_Render(Gfx* arg0);


void ResetParticleEmitters(void);
void CreateParticleEmitter(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, u8 arg6, u8 arg7, u8 arg8, u8 arg9, f32 argA, f32 argB, f32 argC, s16 argD);
void ComputeParticleOffset(f32 arg0, Vec3f* arg1, f32 arg2);
void UpdateParticleEmitter(ParticleEmitter* arg0);
s32 TickParticleEmitters(void);
Gfx* RenderParticleEmitters(Gfx* arg0);


void ParticleSystem_ResetAll(void);
void ParticleSystem_Spawn(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, u8 arg6, u8 arg7, u8 arg8, u8 arg9, f32 argA, f32 argB, f32 argC, s16 argD);
void CalcRotatedOffsetX(f32 arg0, Vec3f* arg1, f32 arg2);
void ParticleSystem_UpdateEmitter(unk_D_843ACA10* arg0);
s32 ParticleSystem_TickAll(void);
Gfx* ParticleSystem_RenderAll(Gfx* arg0);


void WaterParticlePool_Init(void);
void WaterParticlePool_Spawn(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, u8 arg6, u8 arg7, u8 arg8, u8 arg9, f32 argA, f32 argB, f32 argC, s16 argD);
void WaterParticle_CalcOffsetRoll(f32 arg0, Vec3f* arg1, f32 arg2);
void WaterParticleSystem_Update(unk_D_843ADA80* arg0);
s32 WaterParticlePool_Tick(void);
Gfx* WaterParticlePool_Render(Gfx* arg0);


void WaterParticlePool_InitAlt(void);
void WaterParticlePool_SpawnAlt(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, u8 arg6, u8 arg7, u8 arg8, u8 arg9, f32 argA, f32 argB, f32 argC, s16 argD);
void WaterParticle_CalcVertexOffset(f32 arg0, Vec3f* arg1, f32 arg2);
void WaterParticle_Update(unk_D_843ADA80* arg0);
s32 WaterParticle_UpdateAll(void);
Gfx* WaterParticle_Render(Gfx* arg0);


void WaterParticleSystems_ResetAll(void);
void WaterParticleSystems_Spawn(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8, f32 arg9, f32 argA, s16 argB, s32 argC, s32 argD, s16 argE, s16 argF, s16 arg10, s16 arg11, s16 arg12, s16 arg13, s16 arg14, s16 arg15, CombineParams* arg16, CombineParams* arg17, u8 arg18, u8 arg19, u8 arg1A, u8 arg1B, u8 arg1C, u8 arg1D, u8 arg1E, u8 arg1F, u8 arg20, u8 arg21, u8 arg22, u8 arg23, u8 arg24);
void WaterParticle_ComputeOffset(f32 arg0, Vec3f* arg1, f32 arg2);
void WaterParticle_UpdateSystem(WaterParticleSystem* arg0);
s32 WaterParticleSystems_Tick(void);
Gfx* WaterParticle_DrawPass(Gfx* arg0, WaterParticleSystem* arg1, s16 arg2, s16 arg3);
Gfx* WaterParticle_LoadTextureTiles(Gfx* arg0, WaterParticleSystem* arg1);
Gfx* WaterParticleSystems_Render(Gfx* arg0);


void WaterEffect_Init(void);
void WaterEffect_Spawn(s16 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, u8 arg7, u8 arg8, u8 arg9, u8 argA, u8 argB, u8 argC, u8 argD, u8 argE, u8 argF, f32 arg10, f32 arg11, f32 arg12, s16 arg13, s32 arg14, s32 arg15, s16 arg16, s16 arg17, s16 arg18, s16 arg19, s16 arg1A, s16 arg1B, s16 arg1C, s16 arg1D, CombineParams* arg1E, CombineParams* arg1F);
void WaterEffect_CalcDirection(s32 arg0, Vec3f* arg1, Vec3f* arg2, Vec3f* arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7);
void WaterEffect_ApplyRotation(f32 arg0, Vec3f* arg1, Vec3f* arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6);
void WaterEffect_UpdateParticles(unk_D_843C3508* arg0);
s32 WaterEffect_Process(void);
Gfx* WaterEffect_RenderGeometry(Gfx* arg0, unk_D_843C3508* arg1);
Gfx* WaterEffect_LoadTextures(Gfx* arg0, unk_D_843C3508* arg1);
Gfx* WaterEffect_RenderAll(Gfx* arg0);
void GlowEmitters_Reset(void);
s16 GlowEmitter_Allocate(void);
void ParticleEmitter_AddParticle(s16 arg0, f32 arg1, f32 arg2, f32 arg3, s16 arg4, f32 arg5);
void GlowEmitter_Update(s16 arg0);
Gfx* GlowParticle_Draw(Gfx* arg0, Particle* arg1, MtxF* arg2);
Gfx* ParticleEmitter_RenderAll(s16 arg0, Gfx* arg1);
void func_8436EED4(void);
void func_8436EEDC(void);
s32 func_8436EEE4(s32 arg0);


void ScreenTransition_SetState(s32 arg0, s32 arg1);
s32 ScreenTransition_GetState(void);
void ScreenTransition_Update(void);
Gfx* ScreenTransition_Draw(Gfx* arg0, s32 arg1);
void ScreenTransition_Apply(void);


void func_8436F6C0(void);


void func_8436F6D0(void);
u8 GetRandomU8(void);
u8 GetRandomU8_Alt(void);
void ShowDamageMessage(s32 arg0, s32 arg1);
void ResetBattleAfterMove(s32 arg0, s32 arg1);
void func_8436FA80(unk_D_84390010* arg0);
void ApplyDamageRandomFactor(void);
u16 CompareMovePriority(unk_D_84390010* arg0, unk_D_84390010* arg1);
s32 IsByteInArray(u8 arg0, u8* arg1, s32 arg2);
void func_8436FD9C(void);
s32 func_8436FDBC(void);
void ComputePokemonStat(s32 arg0, PokemonData* arg1);
void ComputeAllPokemonStats(PokemonData* arg0);
void InitBattleParameters(void);
s32 UpdateDamageAccumulator(void);
void ProcessTurnEnd(void);
void DecrementMovePP(s32 arg0);
void ApplyAccuracyStageMultipliers(void);
void MarkAttackFailed(void);
void HandleMoveEffectFlags(void);
void func_84370ADC(unk_D_84390010* arg0);
void ApplyParalysisSpeedCut(unk_D_84390010* arg0);
void ApplyBurnAttackCut(unk_D_84390010* arg0);
void func_84370B7C(unk_D_84390010* arg0);
s32 func_84370E30(unk_D_84390010* arg0);
void func_84370E70(void);
void func_84370E78(void);
void func_84370E80(void);
void func_84370F40(void);
void func_84371010(void);
void func_84371080(void);
void func_8437114C(void);
void func_843712CC(void);
void func_843714D8(void);
s32 func_84371564(void);
void func_843715C0(void);
void func_8437166C(void);
s32 func_8437176C(void);
void func_843718DC(void);
s32 func_843718E4(void);
void func_84371974(void);
s32 func_84371B3C(void);
s32 func_84371C18(void);
s32 func_84371DCC(void);
void func_84372670(void);
void func_84372B48(unk_D_84390010* arg0);
void func_84372C40(unk_D_84390010* arg0);
void func_84372D88(unk_D_84390010* arg0);
void func_84372ED0(unk_D_84390010* arg0);
void func_84373018(unk_D_84390010* arg0);
s32 func_84373160(unk_D_84390010* arg0);
s32 func_843732B8(void);
void func_8437345C(void);
void func_84373570(unk_D_84390010* arg0);


u16 ScaleStatValue(u16* arg0, u16 arg1, u8 arg2);
void Battle_TurnStart(void);
void Battle_ProcessCommand(void);
void Battle_UpdateProgress(void);
void Battle_ResetState(void);
void Battle_HandleItemEffect(void);
void Battle_ApplyStatIncrease(void);
void Battle_ApplyStatChange(void);
void Battle_HandleStatDecrease(void);
void Battle_InitPhase(void);
void func_84374D08(void);
void Battle_HandleSpecialMove(void);
void func_84374E08(void);
void func_84374EE4(void);
void func_84374FD4(void);
void Battle_DisplayStatusMessage(void);
void func_843751F8(void);
void func_843752C0(void);
void func_84375384(void);
void func_84375424(void);
void Battle_StartMiniGame(void);
void func_843755E8(void);
void func_84375700(void);
void func_84375894(void);
void func_843759C4(void);
void func_843759DC(void);
void func_843759F4(void);
void func_84375B1C(void);
void func_84375C24(void);
void func_84375C60(void);
void func_84375D78(void);
void func_84375DA4(void);
void func_84375E6C(void);
void func_8437600C(void);
void func_84376258(void);
void func_843765E8(void);
void SpAttack_Dispatch(void);
void SpAttack_Main(void);


void func_84376790(s32 arg0, u32 arg1);
void func_843767DC(void);
s32 func_843767E4(s32 arg0);
void func_843768D8(u8 arg0);
u8 func_84376920(unk_D_800FCB18* arg0, unk_D_800FCB18* arg1, u8 arg2);
u16 func_84376A34(unk_D_800FCB18* arg0, unk_D_800FCB18* arg1);
void func_84376B38(void);
void func_84376B9C(unk_D_800FCB18* arg0, unk_D_800FCB18* arg1);
void func_84376C90(unk_D_800FCB18* arg0, unk_D_800FCB18* arg1, u8 arg2);
void func_84376E40(unk_D_800FCB18* arg0, unk_D_800FCB18* arg1);
u16 func_84376F68(unk_D_800FCB18* arg0, unk_D_800FCB18* arg1, u8 arg2, u8 arg3);
void func_84377030(unk_D_843C60AC* arg0);
s32 func_84377068(s32 arg0, s32 arg1);
void func_8437717C(unk_D_800AE540_0004* arg0);
s32 func_84377280(s32 arg0);
s32 func_843772E4(u8 arg0, u8 arg1);
u16 func_8437731C(unk_D_800FCB18* arg0);
u16 func_84377354(unk_D_800FCB18* arg0);
f32 func_8437738C(u8 arg0, unk_D_800FCB18* arg1);
s32 func_84377430(u8 arg0, unk_D_843C60A4* arg1);
s32 func_84377550(u8 arg0, u8 arg1);
s32 func_84377644(unk_D_843C60A4* arg0, u8 arg1);
u8 func_843776FC(unk_D_843C60AC* arg0, unk_D_843C60AC* arg1, u8 arg2);
void func_843779C0(void);
u8 func_843779C8(unk_D_843C60AC* arg0, unk_D_843C60AC* arg1, u8 arg2, u8* arg3);
u8 func_84377FA4(unk_D_843C60AC* arg0, unk_D_843C60A4* arg1, u8* arg2, u8 arg3, u8* arg4);
s32 func_843780FC(u8 arg0, u8 arg1);
u8 func_84378140(unk_D_843C60AC* arg0, unk_D_843C60AC* arg1);
u8 func_8437828C(unk_D_843C60AC* arg0, unk_D_843C60AC* arg1);
u8 func_843783CC(unk_D_843C60A4* arg0);
void func_84378474(unk_D_800AE540_0004* arg0, unk_D_800AE540_0004* arg1, unk_D_800AE540_0004* arg2, unk_D_843C5568* arg3, s32 arg4);
void func_84378578(unk_D_843C60AC* arg0, u8 arg1);
u16 func_8437865C(unk_D_800FCB18* arg0, unk_D_800FCB18* arg1, u8 arg2);
void func_843787F4(unk_D_800FCB18* arg0, unk_D_800FCB18* arg1, u16* arg2, u8* arg3, u8 arg4, u8 arg5);
s32 func_84378B0C(unk_D_843C60AC* arg0, unk_D_843C60AC* arg1, u8* arg2, u8 arg3);
s32 func_843791AC(unk_D_843C60AC* arg0, unk_D_843C60AC* arg1, u8* arg2, u8 arg3);
s32 func_843791E4(unk_D_843C60AC* arg0, unk_D_843C60AC* arg1, u8* arg2, u8 arg3);
void func_8437921C(void);
u8 func_84379224(unk_D_800FCB18* arg0, unk_D_800FCB18* arg1, u8 arg2, u8 arg3);
void func_843793E0(u8 arg0, u8* arg1);
void func_843794CC(unk_D_843C60AC* arg0, unk_D_843C60AC* arg1, s32 arg2, u8 arg3, u8 arg4, unk_func_843794CC* arg5);
s32 func_8437AC20(unk_func_843794CC* arg0, u8 arg1, u8 arg2);
s32 func_8437ACB0(unk_func_843794CC* arg0, u8 arg1, u8 arg2, u8 arg3);
u8 func_8437AEA4(unk_func_843794CC* arg0, u8 arg1, u8 arg2, u8 arg3);
void func_8437B0CC(unk_D_843C60A4* arg0, unk_D_843C60A4* arg1, u8 arg2, unk_func_843794CC* arg3, u8 arg4);
s32 func_8437E3B4(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_8437E448(unk_D_843C60AC* arg0, UNUSED unk_D_843C60AC* arg1, u8 arg2, unk_func_843794CC* arg3);
s32 func_8437E7A4(void);
u16 func_8437E860(u8 arg0, u8 arg1);
u8 func_8437E920(u8 arg0);
void func_8437E974(unk_D_800AE540_0004* arg0, unk_D_800AE540_0004* arg1, unk_D_843C60A4* arg2, u8 arg3);
s32 func_8437ECFC(unk_D_843C60A4* arg0, u8* arg1, u8 arg2);
s32 func_8437ED54(unk_D_843C60A4* arg0, u8* arg1, u8 arg2, u8 arg3);
s32 func_8437EDB8(unk_D_843C60A4* arg0, u8* arg1, u8 arg2, s32 arg3);
s32 func_8437EFBC(unk_D_843C60A4* arg0, u8* arg1, u8 arg2, u8 arg3);
s32 func_8437F068(unk_D_843C60A4* arg0, u8* arg1, u8 arg2);
s32 func_8437F2EC(unk_D_843C60A4* arg0, unk_D_843C60A4* arg1, u8* arg2, s32* arg3);
s32 func_8437F85C(unk_D_843C60A4* arg0, s32* arg1, s32 arg2, unk_func_8437F85C_arg3* arg3, u8* arg4, u8 arg5, u8 arg6);
void func_8437FB14(unk_D_843C60A4* arg0, u8* arg1, s32 arg2);
s32 func_8437FC10(unk_D_843C60A4* arg0);
s32 func_8437FCCC(unk_D_800FCB18* arg0);
s32 func_8437FD74(unk_D_843C60A4* arg0, u8* arg1, s32* arg2, u8 arg3);
s32 func_84380164(unk_D_843C60A4* arg0, unk_D_843C60A4* arg1, u8* arg2, u8* arg3, s32* arg4);
s32 func_843804F4(unk_D_843C60A4* arg0, unk_D_843C60A4* arg1, u8* arg2, u8* arg3, s32 arg4);
void func_84380598(void);
u8 func_84380870(unk_D_843C60A4* arg0, unk_D_843C60A4* arg1);
u8 func_84380B40(unk_D_843C60AC* arg0, s32* arg1, s32* arg2, unk_D_843C60A4* arg3, u8 arg4, s32 arg5);
s32 func_84380EB4(unk_D_843C60AC* arg0, unk_D_843C60AC* arg1, u8 arg2);
s32 func_84380F7C(unk_func_8438220C* arg0);
s32 func_843811D0(unk_D_843C60AC* arg0, unk_D_843C60AC* arg1, unk_D_843C60A4* arg2, u8* arg3, s32* arg4, s32* arg5, s32* arg6, s32* arg7, s32* arg8);
s32 func_843813D4(unk_D_843C60AC* arg0, unk_D_843C60AC* arg1, unk_D_843C60A4* arg2, u8* arg3, unk_func_8438220C* arg4);
u8 func_84381584(unk_D_843C60AC* arg0, unk_D_843C60AC* arg1, unk_D_843C60A4* arg2, unk_D_843C60A4* arg3, u8* arg4, unk_func_8438220C* arg5);
u16 func_84381BD4(u16* arg0, u16 arg1, u8 arg2);
void func_84381C78(unk_D_800FCB18* arg0, unk_D_800FCB18* arg1, u8 arg2, u8 arg3);
void func_84381DD4(unk_func_8438220C* arg0);
void func_84381F50(unk_func_8438220C* arg0);
u8 func_843820B8(unk_func_8438220C* arg0);
s32 func_8438220C(void);
s32 func_8438223C(s32 arg0);
s32 func_8438249C(u8 arg0, u8 arg1);
s32 func_8438255C(u8 arg0, u8 arg1);
s32 func_843825D8(u8 arg0);
s32 func_84382614(u8 arg0);
s32 func_84382668(unk_D_800FCB18* arg0, s32 arg1, u8 arg2, u8 arg3);
s32 func_84382840(unk_D_800FCB18* arg0, unk_D_800FCB18* arg1, u8 arg2);
void func_84382ACC(void);
s32 func_843831A0(unk_D_800AE540_0004* arg0, unk_D_800AE540_0004* arg1, unk_D_800AE540_0004* arg2, s32 arg3, u8* arg4, s32 arg5, s32 arg6);
void func_8438363C(UNUSED s32 arg0, UNUSED s32 arg1, s32 arg2);
s32 func_84383B5C(UNUSED s32 arg0);
void func_84384124(void);
s32 func_843841C4(s32 arg0, s32 arg1);

#endif // _FRAGMENT62_H_
