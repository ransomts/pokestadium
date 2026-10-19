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

typedef struct unk_BattlePlayerAnimState {
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
} unk_BattlePlayerAnimState; // size = 0xCC

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

typedef struct unk_BattlePlayerEntity {
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
    /* 0x654 */ unk_BattlePlayerAnimState unk_654;
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
} unk_BattlePlayerEntity; // size = 0xA0C

typedef struct unk_BattleAnimDataEntry {
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
} unk_BattleAnimDataEntry; // size = 0x10

typedef struct unk_D_8438E7B0 {
    /* 0x000 */ unk_BattleAnimDataEntry unk_000[165];
    /* 0xA50 */ unk_BattleAnimDataEntry unk_A50;
    /* 0xA60 */ char unkA60[0x10];
    /* 0xA70 */ unk_BattleAnimDataEntry unk_A70;
    /* 0xA80 */ unk_BattleAnimDataEntry unk_A80;
    /* 0xA90 */ char unkA90[0x60];
    /* 0xAF0 */ unk_BattleAnimDataEntry unk_AF0;
    /* 0xB00 */ unk_BattleAnimDataEntry unk_B00;
    /* 0xB10 */ unk_BattleAnimDataEntry unk_B10;
    /* 0xB20 */ unk_BattleAnimDataEntry unk_B20;
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

typedef void (*unk_D_84385384_func)(unk_BattlePlayerEntity*);

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
extern u8 gPokemonSfxId_0;
extern u8 gPokemonSfxId_1;
extern u8 gPokemonSfxId_2;
extern u8 gPokemonSfxId_3[];
extern s16 gAnimLookupTable[];
extern unk_D_843847BC gEntityInitParams[2];
extern unk_D_86B0C160 gCameraFovyPresetRandom[3];
extern unk_D_86B0C160 gCameraFovyPresetSpecial[2];
extern unk_D_86B0C160 gCameraPosB;
extern unk_D_86B0C160 gCameraPosD;
extern unk_D_86B0C160 gCameraPosC;
extern unk_D_86B0C160 gCameraPosA;
extern unk_D_86B0C160 gBattleCameraPresetTable[];
extern unk_D_86B0C160 gBattleCameraPresetE;
extern unk_D_86B0C160 gBattleCameraPresetTable2[];
extern Vec3f gCameraOffsetTable[];
extern unk_D_84385384_func gAnimStateIdle;
extern unk_D_84385384 gMoveAnimData[];
extern Vec3f gCameraFarSettings;
extern Vec3f gCameraCloseSettings;
extern u32 gMessageIdLookup[];
extern Vtx gPanelQuadVerts[];
extern Vtx gPanelBarVerts[];
extern Vtx gPanelBarSmallVerts[];
extern Vtx gPanelMiscVerts[];
extern Vtx gPanelBgVerts[];
extern Vtx gPanelBgLargeVerts[];
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
extern u8 gBattleEffectType;
extern u8 gBattleUnusedFlag4;
extern u8 gBattleUnusedFlag5;
extern s32 gAnimTimer;
//extern unk_D_843C4E44 gIsBattleMode;
extern u8 gIsBattleMode;
extern u8 gAnimStateFlag;
extern u16 gCurrentDamage;
extern unk_D_800FCB18* gCurrentBattleEntity;
extern unk_D_800FCB18* gDefenderBattleEntity;


extern unk_BattlePlayerEntity* sActivePokemon[2];
extern unk_BattlePlayerEntity* gPrimaryPokemonEntity;
extern unk_BattlePlayerEntity* gPokemonEntityUnused;
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
extern unk_D_843901A0* gBattleMessageBuffers;
extern unk_D_843901B0 gCameraPreset;
extern unk_BattlePlayerEntity* gOpponentPlayer;
extern unk_BattlePlayerEntity* gCurrentPlayer;
extern s32 gTotalMoveCount;
extern s32 gCurrentMoveIndex;
extern s32 gInitialMoveIndex;
extern unk_D_84390240 gBattleState;
extern s32 gBattleUpdateHPFlag;
extern s32 gPanelDrawCount;
extern s32 D_843902A8;
extern s16 gParticleTexture_Default;
extern s16 gParticleEffectPrimaryId;
extern unk_BattlePlayerEntity* gParticleEffectEntityA;
extern unk_BattlePlayerEntity* gParticleEffectData_42;
extern unk_BattlePlayerEntity* gParticleEffectEntityB;
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
s32 BattleScene_UpdateFrame(s32 arg0);
s32 BattleScene_UpdatePausedFrame(s32 arg0);
void Battle_UpdateCompletionGate(void);
s32 PokemonSelectScreen_Update(s32 arg0);
void Battle_CompleteRosterOrder(u8* arg0, s32 arg1);
void Battle_SelectComRoster(void);
void PokemonSelection_InitPlayer(unk_D_800AE540_1194* arg0, unk_D_86002F30* arg1);
void BattleScreen_Init(Stage* arg0);
void func_84301A24(void);
s32 BattleScreen_Run(s32 arg0, unk_D_800AE540* arg1);

void AnimStateQueue_ResetAll(void);
void Anim_TriggerActionScriptMode3(unk_BattlePlayerEntity* arg0, s32 arg1);
void AnimChannel_StartMoveAction(unk_BattlePlayerEntity* arg0, s32 arg1);
void AnimChannel_StartSpecialMoveAction(unk_BattlePlayerEntity* arg0, s32 arg1);
void AnimChannel_StartAnotherMoveAction(unk_BattlePlayerEntity* arg0, s32 arg1);
void AnimChannel_ResetIfNeeded(unk_BattlePlayerEntity* arg0);
void AnimChannel_SetupAndTrigger(unk_BattlePlayerEntity* arg0);
void AnimChannel_CheckModelBaseY(unk_BattlePlayerEntity* arg0);
void Anim_ResetPlayer(unk_BattlePlayerEntity* arg0);
void Anim_ResetAllPlayers(unk_BattlePlayerEntity* arg0);
void Anim_SetEntityVisualFlags(unk_BattlePlayerEntity* arg0);
void Anim_ClearEntityVisualFlags(unk_BattlePlayerEntity* arg0);
s32 AnimChannel_GetFlagsFB0(unk_BattlePlayerEntity* arg0);
s32 AnimChannel_FinishAndGetFlagsFC0(unk_BattlePlayerEntity* arg0);
s32 AnimChannel_GetFlagsFF0(unk_BattlePlayerEntity* arg0);
s32 AnimChannel_CheckAndReset(unk_BattlePlayerEntity* arg0);
void AnimChannel_HandleBattleState(unk_BattlePlayerEntity* arg0);
void AnimChannel_TriggerMoveEffect(unk_BattlePlayerEntity* arg0);
void AnimChannel_TriggerGenericEffect(unk_BattlePlayerEntity* arg0);
void AnimChannel_SetFlags28(unk_BattlePlayerEntity* arg0);
void AnimChannel_SetTransformData(unk_BattlePlayerEntity* arg0);
s32 FindIndexInArray(u16 arg0, u8* arg1, s32 arg2);
void ApplyStatMasksAndConditions(unk_BattlePlayerEntity* arg0, u16 arg1, unk_D_84390010_94C* arg2, unk_D_84390010_94C* arg3);
void ResetAllStatFlags(unk_BattlePlayerEntity* arg0);
void DMATransfer_MoveData(u8 arg0, u32 arg1);
void DMATransfer_MoveDataPair(s32 arg0, unk_D_84390010_94C* arg1, unk_D_84390010_94C* arg2);
void LoadPlayerAnimationData(unk_BattlePlayerEntity* arg0, s32 arg1);
void Pokemon_HandleFaint(unk_BattlePlayerEntity* arg0);
void Pokemon_StartMoveAnimation(unk_BattlePlayerEntity* arg0);
void Pokemon_HandleMoveCompletion(unk_BattlePlayerEntity* arg0);
void AnimChannel_CheckAndAdvance(unk_BattlePlayerEntity* arg0);
void AnimChannel_HandleSpecialMoves(unk_BattlePlayerEntity* arg0);
void AnimChannel_SetSubStateIfNeeded(unk_BattlePlayerEntity* arg0);
void Pokemon_GenericActionTrigger(unk_BattlePlayerEntity* arg0);
void Pokemon_PlayMoveEffect(unk_BattlePlayerEntity* arg0);
void Pokemon_TriggerAnimIfUnlocked(unk_BattlePlayerEntity* arg0);
void Pokemon_HandleMoveEnd(unk_BattlePlayerEntity* arg0);
void Pokemon_HandleSpecialMoveEnd(unk_BattlePlayerEntity* arg0);
void Pokemon_EnterBattleState(unk_BattlePlayerEntity* arg0);
void Pokemon_HandleSwitchIn(unk_BattlePlayerEntity* arg0);
void Pokemon_HandleSwitchOut(unk_BattlePlayerEntity* arg0);
void Pokemon_StartBattleIntro(unk_BattlePlayerEntity* arg0);
s32 Pokemon_CheckAnimStateC(unk_BattlePlayerEntity* arg0);
s32 Pokemon_CheckAnimState0(unk_BattlePlayerEntity* arg0);
void Pokemon_ResetAnimAndTrigger(unk_BattlePlayerEntity* arg0);
void Pokemon_HandleSpecialMoveAnimation(unk_BattlePlayerEntity* arg0);
void PlayBattleMusicIfReady(unk_BattlePlayerEntity* arg0);
void PlayBattleMusicAndSound(unk_BattlePlayerEntity* arg0);
void PlayBattleMusicAndSoundAlt(unk_BattlePlayerEntity* arg0);
void Pokemon_HandleMoveHit(unk_BattlePlayerEntity* arg0);
void Pokemon_HandleMoveHitSimple(unk_BattlePlayerEntity* arg0);
void Pokemon_HandleFaintEffect(unk_BattlePlayerEntity* arg0);
void Pokemon_ClearTransformFlag(unk_BattlePlayerEntity* arg0);
void Pokemon_TriggerAnimByLookup(unk_BattlePlayerEntity* arg0);
void Pokemon_HandleSpecialMoveEffect(unk_BattlePlayerEntity* arg0);
void Pokemon_SetSpecialAnimChannel(unk_BattlePlayerEntity* arg0);
void Pokemon_HandleSpecialCondition(unk_BattlePlayerEntity* arg0);
void Pokemon_TriggerAnimIfMatch(unk_BattlePlayerEntity* arg0);
void Pokemon_PlaySoundBasedOnFlags(unk_BattlePlayerEntity* arg0);
void Pokemon_HandleGroundedAnim(unk_BattlePlayerEntity* arg0);
void Pokemon_HandleAirborneAnim(unk_BattlePlayerEntity* arg0);
void CheckAnimStateCompletion(unk_BattlePlayerEntity* arg0);
void UpdateAnimChannelForEntity(unk_BattlePlayerEntity* arg0);
void ProcessAnimStateMatch(unk_BattlePlayerEntity* arg0);
s32 GetAnimStateResultCode(unk_BattlePlayerEntity* arg0);
void TriggerAnimStateSound(unk_BattlePlayerEntity* arg0);
void ApplyAnimStateEffect(unk_BattlePlayerEntity* arg0);
void Anim_NullHandler(unk_BattlePlayerEntity* arg0);
void ReplaceAnimQueueEntry(unk_BattlePlayerEntity* arg0, unk_D_84385384_func arg1);
void ResetAnimChannelToDefault(unk_BattlePlayerEntity* arg0);
void ExecuteAnimStateHandlers(unk_BattlePlayerEntity* arg0, s32 arg1);
void Anim_ProcessQueue(void);
void ClearAnimFlagIfState6A(unk_BattlePlayerEntity* arg0);
void PlayAnimSoundIfApplicable(unk_BattlePlayerEntity* arg0, s32 arg1);
s32 TryPlayAnimSoundAndSetState(unk_BattlePlayerEntity* arg0, s32 arg1, s32 arg2);
void PlayAnimSoundSimple(unk_BattlePlayerEntity* arg0, s32 arg1, s32 arg2);
s32 IsAnimStateLocked(unk_BattlePlayerEntity* arg0);
s32 CanAnimProceed(unk_BattlePlayerEntity* arg0, s32 arg1);
s32 CanAnimProceedWithChannel(unk_BattlePlayerEntity* arg0, s32 arg1);
s32 EvaluateAnimStateAgainstBattle(unk_BattlePlayerEntity* arg0, s32 arg1);
s32 EvaluateAnimStateWithAlternateChannel(unk_BattlePlayerEntity* arg0, s32 arg1);
s32 CanAnimChannelA80Proceed(unk_BattlePlayerEntity* arg0, s32 arg1);
void MaybeTriggerSpecialAnimEffect(unk_BattlePlayerEntity* arg0);
void SetEntityAnimFlags(unk_BattlePlayerEntity* arg0, u16 arg1);
s32 ClearEntityAnimFlags(unk_BattlePlayerEntity* arg0, u16 arg1);
void UpdateEntityModelForAnimFlags(unk_BattlePlayerEntity* arg0);
void ProcessEntityAnimFlagUpdates(void);
void PrepareEntityAnimState(unk_BattlePlayerEntity* arg0);
void AdjustModelBaseYForFlag8(unk_BattlePlayerEntity* arg0);
void HandleFlag4000AnimEffect(unk_BattlePlayerEntity* arg0);
void ApplyFlag4000EffectToEntity(unk_BattlePlayerEntity* arg0);
void UpdateEntityStateByMode(unk_BattlePlayerEntity* arg0);
void ProcessEntityPostMoveEffects(unk_BattlePlayerEntity* arg0);
void TriggerStatusEffectSound(unk_BattlePlayerEntity* arg0);
void AllocateEntityStruct(unk_D_800AE540_1194* arg0, s32 arg1);
void InitializeBattleEntities(unk_D_800AE540_1194* arg0);
void SetupEntityController(unk_BattlePlayerEntity* arg0);
void InitEntityGraphNode(unk_BattlePlayerEntity* arg0);
void InitEntitySubObjectGraph(unk_BattlePlayerEntity* arg0);
void InitEntityChildNodes(unk_BattlePlayerEntity* arg0, s32* arg1);
void InitEntityFragmentNode(unk_BattlePlayerEntity* arg0);
void InitializeBattleScene(unk_D_800AE540_1194* arg0);
void SetEntityOrientation(unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1, s32 arg2);
void InitMessageBanksAndAnimQueue(unk_D_800AE540_1194* arg0);
void ResetEntityAnimStates(unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1);
s32 BattleInitDispatch(s32 arg0, unk_D_800AE540_1194* arg1);
void AnimHandler_Idle(unk_BattlePlayerEntity* arg0);
void AnimHandler_AttackStart(unk_BattlePlayerEntity* arg0);
void AnimHandler_AttackHit(unk_BattlePlayerEntity* arg0);
void AnimHandler_AttackEnd(unk_BattlePlayerEntity* arg0);
void AnimHandler_DamageStart(unk_BattlePlayerEntity* arg0);
void AnimHandler_DamageHit(unk_BattlePlayerEntity* arg0);
void AnimHandler_DamageEnd(unk_BattlePlayerEntity* arg0);
void AnimHandler_FaintStart(unk_BattlePlayerEntity* arg0);
void AnimHandler_FaintEnd(unk_BattlePlayerEntity* arg0);
void AnimHandler_StatusEffect(unk_BattlePlayerEntity* arg0);
void AnimHandler_ItemUse(unk_BattlePlayerEntity* arg0);
void AnimHandler_SwitchIn(unk_BattlePlayerEntity* arg0);
void AnimHandler_SwitchOut(unk_BattlePlayerEntity* arg0, s32 arg1);
void AnimHandler_Victory(unk_BattlePlayerEntity* arg0, s32 arg1);
void AnimHandler_Defeat(unk_BattlePlayerEntity* arg0);


void TriggerPokemonAnimAndAction(unk_BattlePlayerEntity* arg0);
void ClearPokemonActiveFlag(unk_BattlePlayerEntity* arg0);
void SetPokemonActiveFlag(unk_BattlePlayerEntity* arg0);
void ClearAllPokemonActiveFlags(void);
void SetAllPokemonActiveFlags(void);
void BattleScene_SetOwnerPoseFlag(unk_D_84390010_728_0168* arg0);
void LoadPokemonModelParams(unk_BattlePlayerEntity* arg0);
void SetupPokemonForBattle(unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1);
void func_84307630(void);
void UpdatePokemonTransform(unk_BattlePlayerEntity* arg0);
void RefreshPokemonTransform(unk_BattlePlayerEntity* arg0);
void AssignPokemonModels(CameraStruct* arg0, unk_BattlePlayerEntity* arg1, CameraStruct* arg2, unk_BattlePlayerEntity* arg3);
void UpdatePokemonTurn(unk_BattlePlayerEntity* arg0, s32 arg1);
void ResetPokemonTurn(unk_BattlePlayerEntity* arg0, s32 arg1);
void ProcessPokemonTurnState(unk_BattlePlayerEntity* arg0);
void UpdatePokemonTurnIfBattleActive(unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1);
s32 HandleBattlePhase(s32 arg0, CameraStruct* arg1, CameraStruct* arg2);

s32 Array_ContainsValue(u8 arg0, u8* arg1, s32 arg2);
PokemonData* GetCurrentPokemonData(unk_BattlePlayerEntity* arg0);
s32 Pokemon_IsSpecialSpecies(unk_BattlePlayerEntity* arg0);
f32 GetModelBaseY(unk_BattlePlayerEntity* arg0);
f32 GetModelWidth(unk_BattlePlayerEntity* arg0);
f32 GetModelHeight(unk_BattlePlayerEntity* arg0);
f32 GetModelDepth(unk_BattlePlayerEntity* arg0);
void UpdateEntityBasePosition(unk_BattlePlayerEntity* arg0);
f32 GetEntityXOffset(unk_BattlePlayerEntity* arg0);
void SetEntityScale(unk_BattlePlayerEntity* arg0, f32 arg1);
s32 BattleScene_GetSelectedSideTeamSize(unk_BattlePlayerEntity* arg0);
s32 GetOpponentPokemonCount(unk_BattlePlayerEntity* arg0);
s32 IsPrimaryEntity(unk_BattlePlayerEntity* arg0);
u8 Anim_GetActionScriptId(unk_BattlePlayerEntity* arg0);
u8 Anim_GetActionScriptParam(unk_BattlePlayerEntity* arg0);
s16 GetOpponentAnimScriptId(unk_BattlePlayerEntity* arg0);
s32 GetOpponentAnimScriptParam(unk_BattlePlayerEntity* arg0);
f32 GetScaledHeight(unk_BattlePlayerEntity* arg0);
f32 GetModelHeightFactor(unk_BattlePlayerEntity* arg0);
s16 GetCurrentMoveId(unk_BattlePlayerEntity* arg0);
void GetEntityScaleDimensions(unk_BattlePlayerEntity* arg0, Vec3f* arg1);
void GetEntityRotation(unk_BattlePlayerEntity* arg0, Vec3s* arg1);
u16 GetCurrentHP(unk_BattlePlayerEntity* arg0);
s16 GetPlayerSideYaw(unk_BattlePlayerEntity* arg0);
s32 GetSpeciesOfPlayerIndex(s32 arg0);
s32 GetSpecies(unk_BattlePlayerEntity* arg0);
u8 IsEntityGenderMale(unk_BattlePlayerEntity* arg0);
void GetEntityPosition(unk_BattlePlayerEntity* arg0, Vec3f* arg1);
void GetEntityCenterPosition(unk_BattlePlayerEntity* arg0, Vec3f* arg1);
void GetEntityBasePosition(unk_BattlePlayerEntity* arg0, Vec3f* arg1);
void GetEntityOffsetPosition(unk_BattlePlayerEntity* arg0, Vec3f* arg1);
f32 Battle_GetEntityHeight(unk_BattlePlayerEntity* arg0);
f32 GetScaledWidth(unk_BattlePlayerEntity* arg0);
unk_D_86002F58_004_000_004* GraphNode_GetModelRoot(unk_BattlePlayerEntity* arg0, s32 arg1);
s32 GraphNode_GetModelPhase(unk_BattlePlayerEntity* arg0, UNUSED s32 arg1);
char* GetPokemonMessageString(unk_BattlePlayerEntity* arg0);
u8* GetPokemonName(unk_BattlePlayerEntity* arg0);
void ApplyAnimEffectToOpponent(unk_BattlePlayerEntity* arg0, s32 arg1, s32 arg2);
void Battle_ResetEntityAnim(unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1);
void Battle_ApplyAnimEffect(unk_BattlePlayerEntity* arg0);
void Battle_TriggerOpponentAnim(unk_BattlePlayerEntity* arg0);
void Entity_InitController(unk_BattlePlayerEntity* arg0, s32 arg1);
void Entity_InitPhysics(unk_BattlePlayerEntity* arg0, s32 arg1);
void Entity_BindController(unk_BattlePlayerEntity* arg0, Controller* arg1);
void Entity_SetupBattleState(unk_BattlePlayerEntity* arg0, s32 arg1);
s32 Battle_HasStatusEffect(unk_BattlePlayerEntity* arg0);
s32 Battle_HasAbilityEffect(unk_BattlePlayerEntity* arg0);
s32 GetTotalPokemonCount(unk_BattlePlayerEntity* arg0);
u8 GetPokemonType(unk_D_800AE540_0004* arg0);
s32 GetPlayerDefeatMessageId(unk_BattlePlayerEntity* arg0);
void Battle_InitModelAnimation(unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1, s32 arg2, s32 arg3);
void Battle_InitSubModelAnimation(unk_BattlePlayerEntity* arg0, unk_D_84390010_728* arg1, s16 arg2);
void Battle_InitEffectModels(unk_BattlePlayerEntity* arg0, s16 arg1);
void Battle_PlayAnimSound(unk_BattlePlayerEntity* arg0);
void Pokemon_ResetToDefaultState(unk_BattlePlayerEntity* arg0);
void Pokemon_ApplyFaintTransform(unk_BattlePlayerEntity* arg0);
void Pokemon_ClearFaintTransform(unk_BattlePlayerEntity* arg0);
void Pokemon_ResetAnimations(unk_BattlePlayerEntity* arg0);
void Pokemon_RestoreVisuals(unk_BattlePlayerEntity* arg0);


void Entity_SetLaunchVelocity(unk_BattlePlayerEntity* arg0, f32 arg1, s16 arg2);
void Entity_UpdateMovement(unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1, f32 arg2, f32 arg3, s32 arg4);
void Entity_UpdateMovementFast(UNUSED unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1, f32 arg2, f32 arg3, s32 arg4, s32 arg5);
void Entity_ResetSubObjectFlags(unk_BattlePlayerEntity* arg0);
void Entity_InitSubObjects(unk_BattlePlayerEntity* arg0);
void Entity_AnimateSubObjects(unk_BattlePlayerEntity* arg0);
void Entity_ActivateSubObjects(unk_BattlePlayerEntity* arg0);
s32 Entity_ScaleSubObjects(unk_BattlePlayerEntity* arg0);
void Entity_SetSubObjectCameraOffsets(unk_BattlePlayerEntity* arg0);
void Entity_UpdateCameraFromSubObject(unk_BattlePlayerEntity* arg0, s16 arg1);
void BattleScene_ResetParticipantModelFlags(unk_BattlePlayerEntity* arg0);
void Entity_LaunchProjectile(UNUSED unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1);
void Entity_HandleProjectileLanding(unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1);
void Entity_StateMachine_Dispatch(unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1);
void BattleAnim_StatusIdleCase2Sub0(UNUSED unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1);
void BattleAnim_StatusIdleCase2Sub1(unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1);
void BattleAnim_StatusIdleCase2(unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1);
void BattleAnim_StatusIdleCase3Sub0(UNUSED unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1);
void BattleAnim_StatusIdleCase3Sub1(unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1);
void BattleAnim_StatusIdleCase3(unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1);
void BattleAnim_StatusIdleCase14Sub0(UNUSED unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1);
void BattleAnim_StatusIdleCase14Sub1(unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1);
void func_8430A4E0(UNUSED unk_BattlePlayerEntity* arg0, UNUSED unk_BattlePlayerEntity* arg1);
void BattleAnim_StatusIdleCase14(unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1);
s32 BattleAnim_ApproachAngleAndCheckThreshold(unk_BattlePlayerEntity* arg0, s16 arg1, s16 arg2);
void BattleAnim_StatusIdleCase4Sub0(UNUSED unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1);
void BattleAnim_StatusIdleCase4Sub1(unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1);
void BattleAnim_StatusIdleCase4Sub2(unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1);
void BattleAnim_StatusIdleCase4(unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1);
void BattleAnim_StatusIdleCase5Sub0(UNUSED unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1);
void BattleAnim_StatusIdleCase5Sub1(unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1);
void BattleAnim_StatusIdleCase5Sub2(unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1);
void BattleAnim_StatusIdleCase5(unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1);
void BattleAnim_StatusIdleCase6Sub0(unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1);
void BattleAnim_StatusIdleCase6Sub1(unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1);
void BattleAnim_StatusIdleCase6Sub2(unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1);
void BattleAnim_StatusIdleCase6(unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1);
void BattleAnim_StatusIdleCase7Sub0(unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1);
void BattleAnim_StatusIdleCase7Sub1(UNUSED unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1);
void BattleAnim_StatusIdleCase7(unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1);
void BattleAnim_ResetOwnerFacingAndExitStatusIdle(unk_BattlePlayerEntity* arg0);
void BattleAnim_StatusIdleCase8Sub0(unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1);
void BattleAnim_StatusIdleCase8Sub1(UNUSED unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1);
void BattleAnim_StatusIdleCase8(unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1);
void BattleAnim_StatusIdleCase9Sub0(unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1);
void BattleAnim_StatusIdleCase9Sub1(unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1);
void BattleAnim_StatusIdleCase9(unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1);
void BattleAnim_StatusIdleCase12Sub0(UNUSED unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1);
void BattleAnim_StatusIdleCase12Sub1(unk_BattlePlayerEntity* arg0, UNUSED unk_BattlePlayerEntity* arg1);
void BattleAnim_StatusIdleCase12(unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1);
void BattleAnim_StatusIdleCase13Sub0(unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1);
void BattleAnim_StatusIdleCase13Sub1(unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1);
void BattleAnim_StatusIdleCase13Sub2(unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1);
void BattleAnim_StatusIdleCase13(unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1);
void BattleAnim_StatusIdleCase15Sub0(unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1);
void BattleAnim_StatusIdleCase15Sub1(unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1);
void BattleAnim_StatusIdleCase15(unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1);
void BattleAnim_StatusIdleCase16Sub0(UNUSED unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1);
void BattleAnim_StatusIdleCase16Sub1(unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1);
void BattleAnim_StatusIdleCase16(unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1);
void BattleAnim_StatusIdleCase10Sub0(UNUSED unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1);
void BattleAnim_StatusIdleCase10Sub1(unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1);
void BattleAnim_StatusIdleCase10(unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1);
void BattleAnim_StatusIdleCase0(UNUSED unk_BattlePlayerEntity* arg0, UNUSED unk_BattlePlayerEntity* arg1);
void Battle_ClearAnimFlags(s32 arg0);
void BattleAnim_SetOwnerSecondaryStatusFlags(unk_BattlePlayerEntity* arg0, u8 arg1, u8 arg2);
void BattleAnim_ClearOwnerSecondaryStatusFlags(unk_BattlePlayerEntity* arg0);
void BattleAnim_InitSecondarySwayOffset(unk_BattlePlayerEntity* arg0, f32 arg1, s16 arg2);
void BattleAnim_UpdateSecondarySwayPhysics(unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1, f32 arg2, f32 arg3, s32 arg4);
void BattleAnim_SecondaryStatusCaseBSub0(unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1);
void BattleAnim_SecondaryStatusCaseBSub1(unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1);
void BattleAnim_SecondaryStatusCaseB(unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1);
void BattleAnim_SecondaryStatusDefault(unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1);
void BattleAnim_UpdateOwnerSecondaryStatusAnimation(s32 arg0);


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
void BattleAnim_ApproachS16(s16* arg0, s16 arg1, s16 arg2);
void BattleAnim_ApproachU16(u16* arg0, u16 arg1, s16 arg2);
void Math_CubicBezierCoeffs(f32* arg0, f32 arg1);
void Battle_ComputeSplineWeightsVariantB(f32* arg0, f32 arg1);
void Battle_ComputeSplineWeightsVariantC(f32* arg0, f32 arg1);
void Math_EaseOutCubicCoeffs(f32* arg0, f32 arg1);
void Battle_ComputeSplineWeightsVariantE(f32* arg0, f32 arg1);


void Battle_InitTimers(void);
void Battle_AlignPhaseTimer(void);
s32 Battle_TickPhaseTimer(void);
s32 Battle_TickCountdownTimer(void);
s32 Battle_GetMoveScore(s32 arg0, s32 arg1);
s32 Battle_ComputeWinner(void);
s32 Battle_UpdateResultPhase(void);
s32 Battle_TickHPBarTimer(void);
void Battle_ResetHPBarTimer(void);
s32 Battle_TickBattleTimer(void);
void Battle_ResetAllTimers(void);
s32 Battle_UpdateAnimFrame(unk_BattlePlayerEntity* arg0);
void Battle_UpdateHPScale(void);
s32 Battle_CheckMoveAvailability(unk_BattlePlayerEntity* arg0);
s32 Battle_IsMoveInvalid(unk_BattlePlayerEntity* arg0, s32 arg1);
void Battle_SelectFirstAvailableMove(unk_BattlePlayerEntity* arg0);
void Battle_SelectNextValidMove(unk_BattlePlayerEntity* arg0);
void Battle_UpdateControllerRef(unk_BattlePlayerEntity* arg0);
void Battle_HandleConfirmInput(s32 arg0);
void Battle_InitLighting(void);
s32 Battle_HasAnyValidMoves(unk_BattlePlayerEntity* arg0);
s32 Battle_HandleSimultaneousInput(unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1);
void Battle_SetIdleAnim(unk_BattlePlayerEntity* arg0, UNUSED unk_BattlePlayerEntity* arg1);
void Battle_HandleMoveTimeout_Player1(unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1);
void Battle_HandleMoveTimeout_Player2(unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1);
s32 Battle_HandleMoveTimeout_Random(unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1);
s32 Battle_UpdateMoveSelection(unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1);
void Battle_HandleMenuNavigation(unk_BattlePlayerEntity* arg0);
void Battle_ClearMoveSelection(unk_BattlePlayerEntity* arg0);
s32 Battle_ValidateMoveSelection(unk_BattlePlayerEntity* arg0);
void Battle_InvalidMoveFeedback(unk_BattlePlayerEntity* arg0);
void Battle_UpdateActiveController(unk_BattlePlayerEntity* arg0, s32 arg1);
void Battle_HandleMoveSelectionInput(unk_BattlePlayerEntity* arg0, Controller* arg1);
void Battle_UpdateInputState(unk_BattlePlayerEntity* arg0);
void Battle_ApplyMoveAnimation(unk_BattlePlayerEntity* arg0);
s32 Battle_CheckInputTimeout(unk_BattlePlayerEntity* arg0);
s32 Battle_HandleMoveError(unk_BattlePlayerEntity* arg0);
void Battle_HandleQuickSelectInput(unk_BattlePlayerEntity* arg0);
void Battle_ProcessMoveInput(unk_BattlePlayerEntity* arg0);
s32 Battle_UpdateMoveInputState(unk_BattlePlayerEntity* arg0, UNUSED Controller* arg1);
void Battle_TriggerMoveAnim(unk_BattlePlayerEntity* arg0);
void Battle_HandleCancelInput(unk_BattlePlayerEntity* arg0);
s32 Battle_UpdateEntityState(unk_BattlePlayerEntity* arg0);
s32 Battle_UpdateDualEntityState(unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1);
void Entities_ShowAllModels(void);
void Entities_HideAllModels(void);
void DemoFeedScriptedInput(void);
void Battle_SyncMoveFlags(unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1);
void Battle_DemoUpdate(void);
void Battle_UpdateEntityInteraction(unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1);
void Battle_UpdateEntities(void);
void Battle_UpdateMain(void);
void Battle_UpdateFrame(void);


void func_8430FC10(void);
void DrawWindowBackground(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void DrawColoredRect(s32 arg0, s32 arg1, s32 arg2, s32 arg3, Color_RGB8* arg4, Color_RGB8* arg5);
void DrawColoredRectWrapper(s32 arg0, s32 arg1, s32 arg2, s32 arg3, Color_RGB8* arg4, Color_RGB8* arg5);
void func_84310360(void);
void DrawHPBar(s32 arg0, s32 arg1, f32 arg2, s32 arg3);
void func_843109EC(void);
void DrawLevelNumber(s32 arg0, s32 arg1, s32 arg2);
void DrawFractionNumber(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void BattleHud_DrawSpeciesNameLabel(s16 arg0, s16 arg1, s32 arg2, char* arg3, s32 arg4);
void DrawTextBoxAnimated(s16 arg0, s16 arg1, s32 arg2, u8* arg3, s32 arg4, s32 arg5);
void DrawPokemonMoveBox(unk_BattlePlayerEntity* arg0, unk_D_800AE540_0004* arg1, s16 arg2, s16 arg3, s32 arg4, u16 arg5, s32 arg6);
void DrawPokemonInfoWindow(unk_BattlePlayerEntity* arg0, PokemonData* arg1, unk_D_84385790* arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9, s32 argA);
s32 DrawTextureRect(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u8* arg4);
void func_84311420(void);
void BattleHud_DrawBoxBorder(s16 arg0, s16 arg1, s16 arg2, s16 arg3);
void DrawHPBarTimer(s16 arg0, s16 arg1);
void DrawPhaseTimer(s16 arg0, s16 arg1);
void DrawPokemonStatusIcons(unk_BattlePlayerEntity* arg0, s16 arg1, s16 arg2);
void DrawBattleInfoWindowLeft(unk_BattlePlayerEntity* arg0, s16 arg1, s16 arg2, u16 arg3, s32 arg4);
void DrawBattleInfoWindowRight(unk_BattlePlayerEntity* arg0, s16 arg1, s16 arg2, u16 arg3, s32 arg4);
void DrawBattleMenuThreeOptions(unk_BattlePlayerEntity* arg0, s16 arg1, s16 arg2, s32 arg3);
void DrawBattleMenuTwoOptions(unk_BattlePlayerEntity* arg0, s16 arg1, s16 arg2, s32 arg3);
void DrawBattleMenuOneOption(unk_BattlePlayerEntity* arg0, s16 arg1, s16 arg2, s32 arg3);
void Text_PrintRightAligned(s32 arg0, s32 arg1, char* arg2);
s32 DrawCounterLeftToRight(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 DrawCounterRightToLeft(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void DrawMovePPWindows(unk_BattlePlayerEntity* arg0, s16 arg1, s16 arg2, s32 arg3);
void BattleHud_DrawForfeitConfirmDialog(s16 arg0, s16 arg1, s16 arg2, s32 arg3);
void BattleHud_DrawPlainText(s16 arg0, s16 arg1, char* arg2);
void BattleHud_DrawDoublesRosterRow(unk_BattlePlayerEntity* arg0, unk_D_800AE540_0004* arg1, PokemonData* arg2, s32 arg3, s32 arg4, s32 arg5);
void BattleHud_DrawPartyRosterRow(unk_BattlePlayerEntity* arg0, unk_D_800AE540_0004* arg1, PokemonData* arg2, s32 arg3, s32 arg4, s32 arg5);
void BattleHud_DrawTeamStatusList(unk_BattlePlayerEntity* arg0, unk_D_800AE540_0004* arg1, s16 arg2, s16 arg3, s32 arg4);
void BattleHud_DrawDoublesTeamStatusList(unk_BattlePlayerEntity* arg0, s16 arg1, s16 arg2, s32 arg3);
void BattleHud_DrawCompactMonStatusBox(unk_BattlePlayerEntity* arg0, s16 arg1, s16 arg2, s32 arg3);
void BattleHud_DrawMessageBox(s32 arg0, s16 arg1, s16 arg2, char* arg3);
s32 Dialog_PrintLineIfSet(char* arg0, s16 arg1, s16 arg2);
void BattleHud_DrawExpandingCaptionBox(unk_D_843901A0_4C8* arg0, s16 arg1, s16 arg2, Vec3f arg3);
void Dialog_OpenColoredWindow(unk_D_843901A0_4C8* arg0, s16 arg1, s16 arg2);
s32 Dialog_ZoomColoredWindow(unk_D_843901A0_4C8* arg0, s16 arg1, s16 arg2);
void BattleHud_DrawExpandingCaptionBoxBlack(unk_D_843901A0_4C8* arg0, s16 arg1, s16 arg2, Vec3f arg3);
void Dialog_OpenDarkWindow(unk_D_843901A0_4C8* arg0, s16 arg1, s16 arg2);
s32 Dialog_ZoomDarkWindow(unk_D_843901A0_4C8* arg0, s16 arg1, s16 arg2);
void BattleHud_DrawTextBox(s32 arg0, s16 arg1, s16 arg2, char* arg3);
void BattleHud_DrawTwoOptionCursorMenu(unk_BattlePlayerEntity* arg0, s16 arg1, s16 arg2, s32 arg3);
void BattleScene_DrawStripWipeIfActive(void);
void Battle_DrawScrollingTextureRect(s16 arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5, s16 arg6, s16 arg7);
void Battle_DrawTiledStripSegment(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u8* arg4, s32 arg5);
void Battle_DrawSpectatorModeBackgroundPanel(void);
void Battle_DrawSpectatorModeIndicator(void);
void Battle_DrawSpectatorModeScrollingText(void);
void BattleHud_DrawOwnSideStatus(unk_BattlePlayerEntity* arg0, unk_BattlePlayerAnimState* arg1);
void BattleHud_DrawOpponentSideStatus(unk_BattlePlayerEntity* arg0, unk_BattlePlayerAnimState* arg1);


void ResetDialogBuffers(void);
void ResetMessageIndices(void);
void SimpleStringFormat(s8* arg0, s8* arg1, ...);
void WriteMessageCharOrString(s8* arg0, s8 arg1);
void InitDialogHeader(char* arg0, s32 arg1);
void func_84317B38(void);
void InitBattleDialogParameters(void);
void DetermineMessageCategoryAndDisplay(void);
void Battle_QueueMoveCategoryMessage(void);
void Battle_QueueMetronomeMoveMessage(void);
void Dialog_SetMode(s32 arg0);
void Dialog_Clear(void);
void ProcessMessageCommand(s8* arg0);
void RenderDialogBox(unk_D_843901A0_4C8* arg0, s16 arg1, s16 arg2);
s32 BattleBox_SelectMessage(unk_D_843901A0_4C8* arg0);
void Dialog_RunWindowSequence(s16 arg0, s16 arg1);
void Battle_SetEntityPosition(unk_BattlePlayerEntity* arg0);
void BattleScene_BuildParticipantMessage(unk_BattlePlayerEntity* arg0, s32 arg1);
void BattleScene_RevealParticipantMessageChars(unk_BattlePlayerEntity* arg0);
void BattleScene_TickHudTimers(void);
void Battle_InitMessageQueues(void);
void Battle_InitCamera(void);
void Battle_InitBattleEffects(void);


s32 Camera_IsCloseViewCondition(void);
s32 BattleScene_SkipIntroIfFainted(UNUSED unk_BattlePlayerEntity* arg0, CameraStruct* arg1);
s32 BattleScene_IsEitherActivePokemonFainted(UNUSED unk_BattlePlayerEntity* arg0, UNUSED CameraStruct* arg1);
void Camera_SetCloseView(CameraStruct* arg0);
void Camera_SetFarView(CameraStruct* arg0);
void BattleScene_IntroCameraStep4Or6(CameraStruct* arg0, s32 arg1);
void BattleScene_IntroCameraStep8Or10(CameraStruct* arg0, s32 arg1);
void BattleScene_IntroCameraStep12Or14(CameraStruct* arg0, s32 arg1);
void BattleScene_IntroCameraStep16(CameraStruct* arg0);
void BattleScene_IntroCameraStep18(CameraStruct* arg0);
void Camera_SetFromBattleContext(CameraStruct* arg0);
void BattleScene_IntroCameraStep22Or24(CameraStruct* arg0, s32 arg1);
void Camera_UpdateStateMachine(CameraStruct* arg0);
void BattleScene_IntroCameraRollStep(CameraStruct* arg0);
void BattleScene_IntroCameraRollStepNoFov(CameraStruct* arg0);
void BattleScene_IntroCameraAnimationHoldStep(CameraStruct* arg0);
void BattleScene_IntroCameraPresetHoldStep(CameraStruct* arg0);
void BattleScene_IntroCameraWideHoldStep(CameraStruct* arg0);
void BattleScene_IntroCameraHeightShotSwapStep(CameraStruct* arg0);
void BattleScene_IntroCameraHeightShotStep(CameraStruct* arg0);
void BattleScene_IntroCameraTimedHoldStep(CameraStruct* arg0);
void BattleScene_IntroCameraFinalHoldStep(CameraStruct* arg0);
void Camera_MainUpdate(CameraStruct* arg0);


f32 ClampScaledDistance(unk_BattlePlayerEntity* arg0, f32 arg1, f32 arg2);
s32 Battle_WaitFrames(s32 arg0);
s32 Battle_WaitForAnimation(s32 arg0);
s32 Battle_WaitFramesNonBlocking(s32 arg0);
s32 Battle_IsAnimationFinished(s32 arg0);
void SetCurrentPlayerIndex(s32 arg0);
void Battle_FinishTurn(void);
void Battle_AdvanceTurnState(void);
void SetCameraPositionAndView(CameraStruct* arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, s16 arg5, s16 arg6);
void GetEntityGroundPosition(unk_BattlePlayerEntity* arg0, Vec3f* arg1);
void ResolveEntityPosition(unk_BattlePlayerEntity* arg0, Vec3f* arg1, s32 arg2);
void Battle_SetCamera(s32 arg0, s32 arg1);
void Camera_SetClippingPlanes(CameraStruct* arg0, f32 arg1, f32 arg2);
void Battle_SetTurnTimer(s32 arg0, u16 arg1);
void Battle_UpdateTurnIndex(void);
void Battle_ApplyOpponentAnimEffects(unk_BattlePlayerEntity* arg0);
void Battle_ApplyCameraShake(CameraStruct* arg0);
void Anim_HandleSpecificMoveEvent(UNUSED unk_BattlePlayerEntity* arg0);
s32 Math_IsAngleWithinRange(s16 arg0, s16 arg1);
s32 Camera_SmoothPanToAngle(CameraStruct* arg0, s16 arg1, s16 arg2);
s32 Camera_CheckPanFinished(UNUSED CameraStruct* arg0, s16 arg1, s16 arg2);
void Camera_SetPanTargets(s16 arg0, s16 arg1, f32 arg2);
void SetupBattleCamera(CameraStruct* arg0, s32 arg1);
void BattleScene_ClampCameraEyeFloor(CameraStruct* arg0);
void ConfigureCameraForModel(unk_BattlePlayerEntity* arg0, CameraStruct* arg1);
void Battle_ResetCameraState(void);
void Camera_SetLookAtPosition(unk_BattlePlayerEntity* arg0, CameraStruct* arg1, Vec3f arg2, s16 arg3, s16 arg4, f32 arg5, f32 arg6);
void Camera_SetEyePosition(CameraStruct* arg0, Vec3f arg1, s16 arg2, s16 arg3, f32 arg4, f32 arg5);
void Camera_SetEyePositionOffset(CameraStruct* arg0, Vec3f arg1, s16 arg2, s16 arg3, f32 arg4, f32 arg5);
void Camera_SetViewAndOffsetEye(CameraStruct* arg0, s16 arg1, s16 arg2, f32 arg3, f32 arg4);
void Camera_SetEyeAndPanTargets(CameraStruct* arg0, Vec3f arg1, s16 arg2, s16 arg3, f32 arg4, f32 arg5);
void Camera_SetAtAndPanTargets(CameraStruct* arg0, s16 arg1, s16 arg2, f32 arg3, f32 arg4);
void BattleScene_CameraHelperNop(UNUSED CameraStruct* arg0);
void SmoothFloatPair(f32* arg0, f32* arg1);
void Camera_UpdateFocusOnEntity(CameraStruct* arg0, unk_BattlePlayerEntity* arg1, UNUSED f32 arg2);
void Camera_SmoothAdjustDistance(CameraStruct* arg0, unk_BattlePlayerEntity* arg1);
void Battle_AdvanceCameraTimeline(CameraStruct* arg0, unk_BattlePlayerEntity* arg1);
void Battle_AdvanceCameraTimelineFast(CameraStruct* arg0, unk_BattlePlayerEntity* arg1);
void Battle_AdvanceCameraTimelineSlow(CameraStruct* arg0, unk_BattlePlayerEntity* arg1);
void Camera_FocusEntityWithOffset(CameraStruct* arg0, unk_BattlePlayerEntity* arg1);
s32 Battle_ProcessOpponentAction(CameraStruct* arg0, unk_BattlePlayerEntity* arg1);
void Camera_SmoothFocusEntity(CameraStruct* arg0, unk_BattlePlayerEntity* arg1);
void Camera_SmoothFocusEntityY(CameraStruct* arg0, unk_BattlePlayerEntity* arg1);
void Camera_SmoothPanToEntity(CameraStruct* arg0, unk_BattlePlayerEntity* arg1);
void Camera_SetDistanceToEntity(CameraStruct* arg0, unk_BattlePlayerEntity* arg1, UNUSED s32 arg2);
void Camera_SmoothZoomOut(CameraStruct* arg0, unk_BattlePlayerEntity* arg1);
s32 Camera_SmoothZoomIn(CameraStruct* arg0, unk_BattlePlayerEntity* arg1);
s32 Battle_CheckPlayerAction(CameraStruct* arg0, unk_BattlePlayerEntity* arg1, s32 arg2, s32 arg3);
s32 Battle_ApplySpecialCamera(CameraStruct* arg0, unk_BattlePlayerEntity* arg1);
void Battle_UpdateCameraMatrix(UNUSED CameraStruct* arg0);
void Battle_ApplyCameraSettings(CameraStruct* arg0, unk_BattlePlayerEntity* arg1, s32 arg2);
void CameraPreset_SetAngles(s16 arg0, s16 arg1, s16 arg2, s16 arg3);
void CameraPreset_SetDistances(f32 arg0, f32 arg1);
void CameraPreset_SetSecondaryAngles(s16 arg0, s16 arg1, s16 arg2, s16 arg3);
void CameraPreset_SetSecondaryDistances(f32 arg0, f32 arg1);
void CameraPreset_SetTimelineParams(f32 arg0, f32 arg1);
void Battle_PlayCameraTransition(unk_D_86B0C160* arg0, CameraStruct* arg1, unk_BattlePlayerEntity* arg2);
void Battle_ApplyCameraPreset(unk_D_86B0C160* arg0, CameraStruct* arg1);
s32 Camera_SmoothFocusEntitySide(CameraStruct* arg0, unk_BattlePlayerEntity* arg1);
s32 Battle_CheckEntityHeightDiff(UNUSED CameraStruct* arg0);
void Camera_SetEntityView(CameraStruct* arg0, s32 arg1);
s32 Camera_SmoothFocusOpponent(CameraStruct* arg0, s32 arg1);
void Battle_ApplyPlayerAnimEffects(CameraStruct* arg0, unk_BattlePlayerEntity* arg1);
void Camera_SetEntityWideView(CameraStruct* arg0, unk_BattlePlayerEntity* arg1);
void Camera_TransitionToEntity(CameraStruct* arg0, unk_BattlePlayerEntity* arg1, s32 arg2);
void Camera_TransitionToEntitySide(CameraStruct* arg0, unk_BattlePlayerEntity* arg1, s32 arg2);
void Camera_TransitionToEntityBack(CameraStruct* arg0, unk_BattlePlayerEntity* arg1, s32 arg2);
void Camera_TransitionToEntityLow(CameraStruct* arg0, unk_BattlePlayerEntity* arg1, s32 arg2);
void Battle_SetCameraMoveDefault(CameraStruct* arg0, unk_BattlePlayerEntity* arg1, s32 arg2);
void Battle_SetCameraMoveStatic(CameraStruct* arg0, unk_BattlePlayerEntity* arg1, s32 arg2);
void Battle_SetCameraPreset(CameraStruct* arg0, unk_BattlePlayerEntity* arg1, s32 arg2, s32 arg3);
void Battle_SetCameraOpponentStandard(CameraStruct* arg0, unk_BattlePlayerEntity* arg1);
void Battle_SetCameraOpponentOffset(CameraStruct* arg0, unk_BattlePlayerEntity* arg1);
void Battle_SetCameraOpponentHigh(CameraStruct* arg0, unk_BattlePlayerEntity* arg1);
void Battle_SetCameraOpponentLow(CameraStruct* arg0, unk_BattlePlayerEntity* arg1);
void Battle_SetCameraOpponentClose(CameraStruct* arg0, unk_BattlePlayerEntity* arg1);
void Battle_SetCameraMoveDynamic(CameraStruct* arg0, unk_BattlePlayerEntity* arg1, s32 arg2);
void Battle_SetCameraMoveSimple(CameraStruct* arg0, unk_BattlePlayerEntity* arg1);
void Battle_ExecuteMove(unk_BattlePlayerEntity* arg0, CameraStruct* arg1, s32 arg2, s32 arg3);
void Battle_PlayMoveEffect(unk_BattlePlayerEntity* arg0, CameraStruct* arg1, s32 arg2);
void Battle_QueueOpponentMove(unk_BattlePlayerEntity* arg0, CameraStruct* arg1, s32 arg2);


void TriggerSpecialActionIfReady(unk_BattlePlayerEntity* arg0);
void Battle_ResetSubstate(void);
s32 HandlePlayerActionFlag800(unk_BattlePlayerEntity* arg0);
s32 HandlePlayerActionFlag800Alt(unk_BattlePlayerEntity* arg0);
s32 HandlePlayerActionFlag1000(unk_BattlePlayerEntity* arg0);
s32 ProcessActionWhenState44Is2(unk_BattlePlayerEntity* arg0);
s32 ProcessDualPlayerActionState1(void);
void ClearAnimFlag20IfCondition(void);
void func_8431FCC4(void);
s32 UpdatePokemonHP(unk_BattlePlayerEntity* arg0);
void Battle_ClearSubstateFlag(void);
void Battle_SetSubstateFlag(void);
void Battle_SetPhase(UNUSED CameraStruct* arg0, s32 arg1);
void Battle_StoreCameraFOV(CameraStruct* arg0);
void Battle_SetCameraFOV30(CameraStruct* arg0);
s32 GetAnimDataField0D(unk_BattlePlayerEntity* arg0);
s32 GetMappedAnimDataField0D(unk_BattlePlayerEntity* arg0);
s32 GetAnimDataField0E(unk_BattlePlayerEntity* arg0);
s32 GetMappedAnimDataField0E(unk_BattlePlayerEntity* arg0);
s32 GetAnimDataField0FOrDefault(unk_BattlePlayerEntity* arg0);
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
s32 Battle_ResetMoveStateAndStartAnimation(unk_BattlePlayerEntity* arg0);
void Battle_HandleOpponentDefeat(CameraStruct* arg0);
void Battle_HandleOpponentAnimation(CameraStruct* arg0);
void Battle_ProcessOpponentActionStep(CameraStruct* arg0);
void Battle_ProcessOpponentActionStep2(CameraStruct* arg0);
void Battle_DetermineNextPhaseAfterOpponent(CameraStruct* arg0);
void UnusedBattleStateHandler(UNUSED CameraStruct* arg0);
void Battle_AdjustCameraForAction(CameraStruct* arg0);
void BattleScene_CompleteSendOutCameraFade(UNUSED CameraStruct* arg0);
void BattleScene_CompleteSendOutExtendedFade(UNUSED CameraStruct* arg0);
void BattleScene_AdvanceSendOutFollowupCamera(CameraStruct* arg0);
void Battle_StateMachine(CameraStruct* arg0);
void Battle_HandleState2(UNUSED CameraStruct* arg0);
void Battle_StateMachineVariant(CameraStruct* arg0);
void Battle_ApplyStatusEffectAnimation(unk_BattlePlayerEntity* arg0);
void Battle_SetupInitialCamera(CameraStruct* arg0);
void Battle_TryAdvancePhase(CameraStruct* arg0);
void Battle_HandleSubstate0(CameraStruct* arg0);
void Player_SetActionTimer(unk_BattlePlayerEntity* arg0);
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
void Player_HandleSpecialAnimation(unk_BattlePlayerEntity* arg0);
s32 Player_IsSpecialCondition(unk_BattlePlayerEntity* arg0);
void Battle_CheckAndResetIfBothReady(CameraStruct* arg0, s32* arg1, s32* arg2);
void Battle_OpponentTurnPhase0(CameraStruct* arg0);
void Battle_OpponentTurnPhase1(CameraStruct* arg0);
void BattleScene_RunMoveEffectEndHpTransition(CameraStruct* arg0);
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
void BattleScene_Phase28(CameraStruct* arg0);
void BattleScene_Phase15(CameraStruct* arg0);
void BattleScene_Phase25(CameraStruct* arg0);
s32 StartMoveAnimationAndStatus(unk_BattlePlayerEntity* arg0);
void BattleScene_Phase29(CameraStruct* arg0);
void Battle_PlayerSwitchIn(CameraStruct* arg0);
void Battle_PlayerSwitchOut(CameraStruct* arg0);
void Battle_PlayerSwitchOutAlt(CameraStruct* arg0);
void Battle_PlayerSwitchInAlt(CameraStruct* arg0);
void Battle_OpponentActionInit(CameraStruct* arg0);
void Battle_PlayerDefeatAnim(CameraStruct* arg0);
void func_84326A70(void);
void BattleScene_Phase4(UNUSED CameraStruct* arg0);
void Battle_OpponentSwitchIn(CameraStruct* arg0);
void Battle_OpponentMoveAnimation(CameraStruct* arg0);
void Battle_OpponentDefeatAnim(CameraStruct* arg0);
void Battle_OpponentSwitchOut(CameraStruct* arg0);
void Battle_OpponentDefeatAnimAlt(CameraStruct* arg0);
void Battle_OpponentSwitchOutAlt(CameraStruct* arg0);
void Battle_OpponentDefeatAnimFinal(CameraStruct* arg0);
void StartMoveAnimationAndFinalizeStatus(unk_BattlePlayerEntity* arg0);
void Battle_PlayerDefeatSequence(CameraStruct* arg0);
void Battle_PlayerDefeatSequenceAlt(CameraStruct* arg0);
void Battle_StateMachineMain(CameraStruct* arg0);


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
void BattleCamera_RunState(CameraStruct* arg0, UNUSED unk_BattlePlayerEntity* arg1, UNUSED unk_BattlePlayerEntity* arg2);
void BattleState_Allocate(void);
void func_843297E8(UNUSED CameraStruct* arg0);
void func_843297F0(UNUSED CameraStruct* arg0);
void Camera_PreventDegenerateView(CameraStruct* arg0);
void Battle_StartSequence(CameraStruct* arg0);
void Battle_TransitionSequence(CameraStruct* arg0);
void Battle_RunSequence(CameraStruct* arg0);
u16 IsPointInTriangle(unk_BattlePlayerEntity* arg0, CameraStruct* arg1, unk_BattlePlayerEntity* a2, s16 arg3, f32 arg4);
u16 IsPointInTriangleAndWithinRange(unk_BattlePlayerEntity* arg0, CameraStruct* arg1, unk_BattlePlayerEntity* a2, s16 arg3, f32 arg4);
void UpdateEntityVisibilityFromCamera(CameraStruct* arg0);
void UpdateOppositeEntityVisibility(CameraStruct* arg0);
void func_8432A414(void);
void SetAllEntitiesActiveFlag(void);
void DeactivateOppositeEntity(void);
void DeactivateCurrentEntity(void);
void ClearEntityFlagIfInState(void);
void ProcessBattleState(CameraStruct* arg0);
void BattleScene_UpdateOwnerVisibilityDouble(CameraStruct* arg0);
void Battle_Update(CameraStruct* arg0);
s32 BattleScene_Dispatch(s32 arg0, CameraStruct* arg1);


void HandleMoveHitAnimation(unk_BattlePlayerEntity* arg0);
void TriggerCurrentAnimAction(unk_BattlePlayerEntity* arg0);
void StartMoveAnimation(unk_BattlePlayerEntity* arg0);
void ResetMoveStateAndStartAnimation(unk_BattlePlayerEntity* arg0);
void ResumeMoveAnimationIfNotTriggered(unk_BattlePlayerEntity* arg0);
void HandleItemOrStatusEffect(unk_BattlePlayerEntity* arg0);
void ProcessStatusEffectEnd(unk_BattlePlayerEntity* arg0);
void FinalizeStatusEffect(unk_BattlePlayerEntity* arg0);


void PlaySoundEffect_Select(void);
void PlaySoundEffect_Cancel(void);
void PlaySoundEffect_Confirm(void);
void PlaySoundEffect_Error(void);
void PlayBattleMusicOrDefault(unk_BattlePlayerEntity* arg0, s16 arg1);
void PlayHeightBasedSoundEffect(unk_BattlePlayerEntity* arg0);
void ProcessEntityAudioInfo(unk_BattlePlayerEntity* arg0);
void TriggerMoveEvent(unk_BattlePlayerEntity* arg0, unk_D_800FCB18* arg1, s32 arg2);
void SetPlayerSidesFromActivePokemons(void);
void SetTeamScoresFromActivePokemons(void);
void ProcessBattleMenuSelection(void);
void RenderBattleMenuSelection(void);
void PlayBattleSoundEffect(unk_BattlePlayerEntity* arg0, s32 arg1);
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
void InitActionScript(s32 arg0, unk_BattlePlayerEntity* arg1, unk_BattlePlayerEntity* arg2, s16 arg3, s16 arg4);
void InitActionScriptSimple(s32 arg0, unk_BattlePlayerEntity* arg1, unk_BattlePlayerEntity* arg2, s16 arg3, s16 arg4);
void InitDualTargetActionScript(s32 arg0, unk_BattlePlayerEntity* arg1, unk_BattlePlayerEntity* arg2, s16 arg3, s16 arg4);
void InitActionScriptMode1(s32 arg0, unk_BattlePlayerEntity* arg1, unk_BattlePlayerEntity* arg2, s16 arg3, s16 arg4);
void InitActionScriptMode3(s32 arg0, unk_BattlePlayerEntity* arg1, unk_BattlePlayerEntity* arg2, s16 arg3, s16 arg4);
void InitSingleEntityActionScript(s32 arg0, unk_BattlePlayerEntity* arg1);
void InitSingleEntityActionScriptVariant(s32 arg0, unk_BattlePlayerEntity* arg1);
void BattleAnim_QueueEffectList6Alt(s32 arg0, unk_BattlePlayerEntity* arg1);
void InitWaterEffect(s32 arg0);
void Battle_ApplyAnimChannelEffect(u8 arg0, unk_BattlePlayerEntity* arg1);
void RunParticleEffectScript(u8 arg0, unk_BattlePlayerEntity* arg1);
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
void Particle_CreateChildParticles(ParticleEffectInstance* arg0, func_unk_D_8140E724_008 arg1, ParticleEffectData* arg2, s16 arg3, s16 arg4, s16 arg5);
ParticleEffectInstance* ParticleNode_CreateAt(s16 arg0, s16 arg1, s32 arg2, f32 arg3);
void ParticleNode_ProcessChild(ParticleEffectInstance* arg0);
void ParticleNode_Destroy(ParticleEffectInstance* arg0);
void ParticleNode_UpdateBehavior(ParticleEffectInstance* arg0);
void ParticleNode_UpdateBehaviorAlt(ParticleEffectInstance* arg0);
void ParticleNode_UpdateScale(ParticleEffectInstance* arg0);
void ParticleNode_UpdateOrDestroy(ParticleEffectInstance* arg0);
void ParticleSystem_Update(void);
void ParticleInstance_Configure(ParticleEffectInstance* arg0, unk_BattlePlayerEntity* arg1, ParticleDef* arg2, s16 arg3);
void ParticleDef_SpawnInstances(ParticleDef* arg0, s32 arg1);
void ParticleDef_SpawnAll(ParticleDef* arg0);
void ParticleDef_SpawnBurst(ParticleDef* arg0);
void ParticleDef_SpawnSingle(ParticleDef* arg0);
void ParticleDef_SpawnByType(ParticleDef* arg0);
void ParticleDefs_Update(void);
void Particles_UpdateAll(void);
void ParticleSystem_ResetKeepSpecial(void);
void ParticleSystem_ResetKeepType4(void);
s32 GetParticleSpecialFlag(void);
void SetParticleSpecialFlagFromGlobal(void);
void ParticleCameraCallbacks_Clear(void);
s32 ParticleSystem_IsResettable(void);
void ParticleSystem_SetResetLock(void);
void ParticleSystem_ClearResetLock(void);
void ParticleSystem_ForceResetLock(void);
void Battle_SetAnimChannelFlag(s32 arg0);
void ParticleNode_TriggerByEntity(u8 arg0, unk_BattlePlayerEntity* arg1);
void ParticleSystem_ResetSpawnOffset(void);
void ParticleSystem_SetSpawnOffset(s32 arg0);
void ParticleSystem_AddSpawnOffset(s32 arg0);
void ParticleSystem_ResetSpawnOffset2(void);
ParticleDef* ParticleDef_Create(s32 arg0, s32 arg1, s8 arg2, func_unk_D_8140E724 arg3, ParticleEffectData* arg4, unk_BattlePlayerEntity* arg5, s16 arg6, s16 arg7, u8 arg8, u8 arg9, u8 argA, u8 argB);
ParticleDef* ParticleDef_CreateQuick(s32 arg0, func_unk_D_8140E724 arg1, ParticleEffectData* arg2, s16 arg3, s16 arg4, u8 arg5, u8 arg6, u8 arg7, u8 arg8);
ParticleDef* ParticleDef_CreateFull(s32 arg0, s32 arg1, s8 arg2, func_unk_D_8140E724 arg3, ParticleEffectData* arg4, s16 arg5, s16 arg6, u8 arg7, u8 arg8, u8 arg9, u8 argA);
ParticleDef* ParticleDef_CreateDefault(s32 arg0, s16 arg1, u8 arg2);
ParticleDef* ParticleDef_CreateBC20(s32 arg0, s16 arg1, s16 arg2, u8 arg3, u8 arg4);
ParticleDef* ParticleDef_CreateBC20CD(s32 arg0, s16 arg1, s16 arg2, u8 arg3);
ParticleDef* ParticleDef_CreateBC20CDAlt(s32 arg0, s16 arg1, s16 arg2, u8 arg3, u8 arg4);
ParticleDef* ParticleDef_CreateBC20CDFull(s32 arg0, s32 arg1, s8 arg2, s16 arg3, s16 arg4, u8 arg5, u8 arg6);
ParticleDef* ParticleDef_Create32E6C(s32 arg0, s16 arg1, s16 arg2, u8 arg3);
ParticleDef* ParticleDef_Create32E6CAlt(s32 arg0, s16 arg1, s16 arg2, u8 arg3, u8 arg4);
ParticleDef* ParticleDef_Create32E6CFull(s32 arg0, s32 arg1, s8 arg2, s16 arg3, s16 arg4, u8 arg5, u8 arg6);
ParticleDef* ParticleDef_Create32F30(s32 arg0, s16 arg1, u8 arg2);
ParticleDef* ParticleDef_Create32F30Alt(s32 arg0, s16 arg1, u8 arg2, u8 arg3);
ParticleDef* ParticleDef_Create32F30Full(s32 arg0, s32 arg1, s8 arg2, s16 arg3, u8 arg4, u8 arg5);
ParticleDef* ParticleDef_Create32FD0(s32 arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4);
ParticleDef* ParticleDef_Create330A0(s32 arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4);
ParticleDef* ParticleDef_Create31EAC(s32 arg0, u8 arg1, s16 arg2, s16 arg3, s16 arg4);
ParticleDef* ParticleDef_Create31FAC(s32 arg0, s16 arg1, u8 arg2, s16 arg3, s16 arg4, s16 arg5);
ParticleDef* ParticleDef_Create320A4(s32 arg0, s16 arg1, u8 arg2, s16 arg3, s16 arg4);
ParticleDef* ParticleDef_Create321BC(s32 arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4);
ParticleDef* ParticleDef_Create321BCAlt(s32 arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4);
ParticleDef* ParticleDef_Create323BC(s32 arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5);
ParticleDef* ParticleDef_Create323BCAlt(s32 arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5);
ParticleDef* ParticleDef_Create32604(s32 arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5);
ParticleDef* ParticleDef_Create327B8(s32 arg0, s16 arg1, u8 arg2);
ParticleDef* ParticleDef_CreateComplexColor(s32 arg0, s16 arg1, s16 arg2, u8 arg3);
ParticleDef* ParticleDef_CreateAlphaMode(s32 arg0, s16 arg1, s16 arg2, s16 arg3);
ParticleDef* ParticleDef_CreateAlphaModeFF(s32 arg0);
ParticleDef* ParticleDef_CreateAlphaModeZero(s32 arg0);
ParticleDef* ParticleDef_CreateNullType17(s32 arg0, u8 arg1);
ParticleDef* ParticleDef_CreateNullType19(s32 arg0, u8 arg1);
void BattleAnim_EffectStartNop(void);
void BattleAnim_EffectEndNop(void);
void SetGameStateFlag(s32 arg0);
void ClearGameStateFlag(void);
s32 GetGameStateFlag(void);
s32 IsEntityASpecies(s32 arg0);
s32 GetSpeciesPrimaryEffect(void);
s32 GetSpeciesSecondaryEffect(void);
void Model_GetNodePosition(unk_BattlePlayerEntity* arg0, s16 arg1, Vec3f* arg2);
void GetPrimaryEntityNodePosition(Vec3f* arg0);
void GetPrimaryEffectNodePosition(Vec3f* arg0);
void GetSecondaryEntityNodePosition(Vec3f* arg0);
void GetPrimaryEffectCenterOrNode(Vec3f* arg0);
void GetSecondaryEntityNode9Position(Vec3f* arg0);
void GetEntityDirectionVector(unk_BattlePlayerEntity* arg0, Vec3f* arg1);
f32 GetEntityCameraDistance(unk_BattlePlayerEntity* arg0);
f32 GetEntityScaleFactor(unk_BattlePlayerEntity* arg0);
void ComputeEntityScaleFactor(unk_BattlePlayerEntity* arg0);
f32 GetPrimaryEntityScale(void);
void ComputePrimaryEffectScale(void);
f32 GetSecondaryEntityScale(void);
void ComputeSecondaryEntityScale(void);
CameraStruct* GetBattleCamera(void);
ParticleEffectInstance* ParticleNode_CreateWhiteFlash(Vec3f arg0, u8 arg1);
void ParticleNode_SetPosition(ParticleEffectInstance* arg0, Vec3f arg1);
void ParticleNode_ClearActiveFlag(ParticleEffectInstance* arg0);
s16 ParticleNode_GetAngleToSecondary(ParticleEffectInstance* arg0);
void ParticleNode_SavePrimColor(ParticleEffectInstance* arg0);
void ParticleNode_RestorePrimColor(ParticleEffectInstance* arg0);


void Particle_WhiteFlashInit(ParticleEffectInstance* arg0);
void Particle_WhiteFlashUpdate(ParticleEffectInstance* arg0);
void Particle_WhiteFlashAltInit(ParticleEffectInstance* arg0);
void Particle_WhiteFlashAltUpdate(ParticleEffectInstance* arg0);
void Particle_SetWhiteFlashHandler(ParticleEffectInstance* arg0, u8 arg1);


s32 RenderPanelBackground(ParticleEffectInstance* arg0, CameraStruct* arg1);
void RenderIconMasked(ParticleEffectInstance* arg0, CameraStruct* arg1);
void RenderPanelWithIcon(ParticleEffectInstance* arg0, CameraStruct* arg1);
void RenderOverlayWithIcon(ParticleEffectInstance* arg0, CameraStruct* arg1);
void BattleAnim_DrawAsset1FAnimatedI4WithAsset20DisplayList(ParticleEffectInstance* arg0, CameraStruct* arg1);
s32 RenderItemIcon(ParticleEffectInstance* arg0, UNUSED CameraStruct* arg1);
void RenderStatusBar(ParticleEffectInstance* arg0, UNUSED CameraStruct* arg1);
void BattleAnim_DrawAssets27And28LayeredI4QuadVariantB(ParticleEffectInstance* arg0, UNUSED CameraStruct* arg1);
void RenderMultiBlockIcon(ParticleEffectInstance* arg0, UNUSED CameraStruct* arg1);
void BattleAnim_DrawAsset87AnimatedI4Quad(ParticleEffectInstance* arg0, UNUSED CameraStruct* arg1);
void BattleAnim_DrawI4AtlasYScaled(ParticleEffectInstance* arg0, u8* arg1);
void BattleAnim_DrawAsset19I4AtlasYScaled(ParticleEffectInstance* arg0, UNUSED CameraStruct* arg1);
void BattleAnim_DrawAsset5EI4AtlasYScaled(ParticleEffectInstance* arg0, UNUSED CameraStruct* arg1);
void BattleAnim_DrawAsset1AFrameI4Quad(ParticleEffectInstance* arg0, UNUSED CameraStruct* arg1);
void BattleAnim_DrawAsset1CRgba16Quad(ParticleEffectInstance* arg0, UNUSED CameraStruct* arg1);
void BattleAnim_DrawAsset1ERgba16Quad(ParticleEffectInstance* arg0, UNUSED CameraStruct* arg1);
void BattleAnim_DrawAssetC3Rgba16Quad(ParticleEffectInstance* arg0, UNUSED CameraStruct* arg1);
void BattleAnim_DrawAsset1DRotatedI4Quad(ParticleEffectInstance* arg0, UNUSED CameraStruct* arg1);
void BattleAnim_DrawParticleNoop(UNUSED ParticleEffectInstance* arg0, UNUSED CameraStruct* arg1);
void RenderTimerDigits(ParticleEffectInstance* arg0, UNUSED CameraStruct* arg1);
void RenderTimerDigitsAlt(ParticleEffectInstance* arg0, UNUSED CameraStruct* arg1);
void BattleAnim_DrawAsset13FrameI4YScaledQuadC(ParticleEffectInstance* arg0, UNUSED CameraStruct* arg1);
void RenderTimerNumber(ParticleEffectInstance* arg0, CameraStruct* arg1);
void BattleAnim_DrawAsset13FrameI4ModelQuadB(ParticleEffectInstance* arg0, CameraStruct* arg1);
void BattleAnim_DrawAsset13FrameI4ModelQuadC(ParticleEffectInstance* arg0, CameraStruct* arg1);
void BattleAnim_DrawAsset1BI4TriangleA(ParticleEffectInstance* arg0, UNUSED CameraStruct* arg1);
void BattleAnim_DrawAsset1BI4TriangleB(ParticleEffectInstance* arg0, UNUSED CameraStruct* arg1);
void BattleAnim_DrawAsset13FrameDiv2I4Quad(ParticleEffectInstance* arg0, UNUSED CameraStruct* arg1);
void BattleAnim_DrawAsset18FrameI4ModelQuad(ParticleEffectInstance* arg0, CameraStruct* arg1);
void BattleAnim_DrawAssetA9I4XYScaledQuad(ParticleEffectInstance* arg0, UNUSED CameraStruct* arg1);
void BattleAnim_DrawParticleFullScreenColorOverlay(ParticleEffectInstance* arg0, UNUSED CameraStruct* arg1);


void BattleAnim_SetupGlobalTintColorFadeDetach(ParticleEffectInstance* arg0);
void BattleAnim_CallbackGlobalTintColorFadeDetach(ParticleEffectInstance* arg0);
void Fragment_SetPrimColorFromPaletteAndRender(ParticleEffectInstance* arg0);
void BattleAnim_CallbackOwnerModelTintRampDetach(ParticleEffectInstance* arg0);
void Fragment_SetPrimColorFromPaletteAndRender_WithCE(ParticleEffectInstance* arg0);
void BattleAnim_CallbackOwnerModelTintPulseDetach(ParticleEffectInstance* arg0);
void func_8433209C(void);
void BattleAnim_CallbackOwnerModelTintHoldFadeDetach(ParticleEffectInstance* arg0);
void BattleAnim_SetupOwnerModelTintPaletteApproachInactive(ParticleEffectInstance* arg0);
void BattleAnim_CallbackOwnerModelTintPaletteApproachInactive(ParticleEffectInstance* arg0);
void BattleAnim_SetupOwnerModelTintPaletteApproach(ParticleEffectInstance* arg0);
void BattleAnim_CallbackOwnerModelTintPaletteApproach(ParticleEffectInstance* arg0);
void BattleAnim_SetupOwnerModelTintPaletteCycle(ParticleEffectInstance* arg0);
void BattleAnim_CallbackOwnerModelTintPaletteCycle(ParticleEffectInstance* arg0);
void BattleAnim_SetupOwnerModelTintPaletteApproachRampDown(ParticleEffectInstance* arg0);
void BattleAnim_CallbackOwnerModelTintPaletteApproachRampDown(ParticleEffectInstance* arg0);
void BattleAnim_SetupOwnerModelTintPaletteFade(ParticleEffectInstance* arg0);
void BattleAnim_CallbackOwnerModelTintPaletteFade(ParticleEffectInstance* arg0);
void Fragment_SetRandomPrimColorAndRender(ParticleEffectInstance* arg0);
void BattleAnim_CallbackOwnerModelTintRandomPaletteCycle(ParticleEffectInstance* arg0);
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
void BattleAnim_CallbackDescriptor25AlphaFadeInHold(ParticleEffectInstance* arg0);
void BattleAnim_SetupDescriptor25AlphaHoldDetach(ParticleEffectInstance* arg0);
void BattleAnim_CallbackDescriptor25AlphaHoldDetach(ParticleEffectInstance* arg0);
void BattleAnim_SetupDescriptor25PaletteFadeOut(ParticleEffectInstance* arg0);
void BattleAnim_CallbackDescriptor25PaletteFadeOut(ParticleEffectInstance* arg0);
void BattleAnim_SetupDescriptor25PaletteFadeIn(ParticleEffectInstance* arg0);
void BattleAnim_CallbackDescriptor25PaletteFadeIn(ParticleEffectInstance* arg0);


void Particle_FireBurstSmall(ParticleEffectInstance* arg0, s16 arg1);
void Particle_FireBurstSmall_Update(ParticleEffectInstance* arg0);
void Particle_FireBurstSmall_Handler(ParticleEffectInstance* arg0);
void Particle_FireBurstLarge(ParticleEffectInstance* arg0);
void Particle_FireBurstLarge_Update(ParticleEffectInstance* arg0);
void Particle_FireBurstLarge_Handler(ParticleEffectInstance* arg0);
void Particle_SmokePuff(ParticleEffectInstance* arg0);
void Particle_SmokePuff_Update(ParticleEffectInstance* arg0);
void Particle_SmokePuffHandler(ParticleEffectInstance* arg0);
void Particle_FireBurstTiny(ParticleEffectInstance* arg0, s16 arg1);
void Particle_FireBurstTiny_Update(ParticleEffectInstance* arg0);
void Particle_FireBurstTiny_Handler(ParticleEffectInstance* arg0);
void Particle_SootPuff_Init(ParticleEffectInstance* arg0);
void Particle_SootPuff_Handler(ParticleEffectInstance* arg0);
void Particle_SootPuff_Handler_Alt(ParticleEffectInstance* arg0);
void Particle_SootPuff_Handler_Sooty(ParticleEffectInstance* arg0);
void Particle_Firework(ParticleEffectInstance* arg0);
void ParticleEffect_FireUpdate(ParticleEffectInstance* arg0);
void Particle_Spark(ParticleEffectInstance* arg0);
void Particle_Spark_Handler(ParticleEffectInstance* arg0);
void Particle_Spark_Long_Init(ParticleEffectInstance* arg0);
void Particle_Spark_Long_Handler(ParticleEffectInstance* arg0);
void Particle_SmokeSoot_Init(ParticleEffectInstance* arg0);
void Particle_SmokeSoot_Handler(ParticleEffectInstance* arg0);
void Particle_Ember_Init(ParticleEffectInstance* arg0);
void Particle_Ember_Handler(ParticleEffectInstance* arg0);
void Particle_Dust_Init(ParticleEffectInstance* arg0);
void Particle_Dust_Handler(ParticleEffectInstance* arg0);
void Particle_Dust_Cloud_Init(ParticleEffectInstance* arg0);
void Particle_Dust_Cloud_Handler(ParticleEffectInstance* arg0);
void Particle_SetColorByIndex(ParticleEffectInstance* arg0, u8 arg1);
void func_84334B04(void);
void Particle_SetColorByVariant(ParticleEffectInstance* arg0);
void Particle_Explosion(ParticleEffectInstance* arg0);
void Particle_Explosion_Handler(ParticleEffectInstance* arg0);
void Particle_Firefly(ParticleEffectInstance* arg0);
void ParticleEffect_StateHandler_34F84(ParticleEffectInstance* arg0);
void Particle_Sparkle(ParticleEffectInstance* arg0);
void Particle_Sparkle_Handler(ParticleEffectInstance* arg0);
void Particle_Glitter_Init_Alt(ParticleEffectInstance* arg0);
void Particle_Glitter_Init_Alt_Handler(ParticleEffectInstance* arg0);
void Particle_Star(ParticleEffectInstance* arg0);
void Particle_Star_Handler(ParticleEffectInstance* arg0);
void Particle_Twinkle(ParticleEffectInstance* arg0);
void Particle_Twinkle_Handler(ParticleEffectInstance* arg0);
void Particle_Glitter(ParticleEffectInstance* arg0);
void Particle_Glitter_Handler(ParticleEffectInstance* arg0);
void Particle_Star_Tiny_Init(ParticleEffectInstance* arg0);
void Particle_Star_Tiny_Handler(ParticleEffectInstance* arg0);
void Particle_FireRing(ParticleEffectInstance* arg0);
void Particle_FireRingUpdate(ParticleEffectInstance* arg0);
void Particle_ExplosionVariant(ParticleEffectInstance* arg0, s16 arg1, s16 arg2);
void Particle_ExplosionUpdate(ParticleEffectInstance* arg0, s32 arg1);
void Particle_ExplosionVariant0(ParticleEffectInstance* arg0);
void Particle_ExplosionVariant1(ParticleEffectInstance* arg0);
void Particle_ExplosionInit(ParticleEffectInstance* arg0);
void Particle_RotationUpdate(ParticleEffectInstance* arg0);
void Particle_ExplosionStateUpdate(ParticleEffectInstance* arg0);
void Particle_SparkleInit(ParticleEffectInstance* arg0);
void Particle_SparkleRotationUpdate(ParticleEffectInstance* arg0);
void Particle_SparkleUpdate(ParticleEffectInstance* arg0);
void Particle_DustInit(ParticleEffectInstance* arg0);
void Particle_DustUpdate(ParticleEffectInstance* arg0);
void ParticleEffect_InitSetA(void);
void ParticleEffect_InitSetB(void);
void ParticleEffect_InitSetC(void);
void func_84336EE8(void);
void ParticleEffect_InitExplosionSet(void);
void ParticleEffect_InitSmokeSetB(void);
void ParticleEffect_InitExplosionSetB(void);
void ParticleEffect_InitSmokeSetC(void);
void ParticleEffect_InitFireSet(void);
void func_8433765C(void);
void func_84337664(void);
void ParticleEffect_InitSparkleSet(void);
void func_843378CC(void);
void ParticleEffect_InitCombinedSet(void);


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
void BattleAnim_CallbackUnusedIndexedFadeVariantA(ParticleEffectInstance* arg0);
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


void BattleAnim_SetupStartEffects18And73Descriptor11ScatterRiseFade(ParticleEffectInstance* arg0);
void ParticleEffect_CollisionHandler(ParticleEffectInstance* arg0);
void BattleAnim_ApplyStartEffect18MoveKeyedRadialOffset(ParticleEffectInstance* arg0);
void BattleAnim_SetupStartEffect18MoveKeyedRadialPulse(ParticleEffectInstance* arg0);
void BattleAnim_CallbackStartEffect18MoveKeyedRadialPulse(ParticleEffectInstance* arg0);
void BattleAnim_SetupSharedDescriptor0FDelayedRisingColumnFade(ParticleEffectInstance* arg0);
void BattleAnim_CallbackSharedDescriptor0FDelayedRisingColumnFade(ParticleEffectInstance* arg0);
void BattleAnim_SetupSharedDescriptor0FDelayedRisingColumnRandomScale(ParticleEffectInstance* arg0);
void BattleAnim_CallbackSharedDescriptor0FDelayedRisingColumnRandomScale(ParticleEffectInstance* arg0);
void BattleAnim_SetupSharedDirectionalSprayFade(ParticleEffectInstance* arg0);
void BattleAnim_CallbackSharedDirectionalSprayFade(ParticleEffectInstance* arg0);
void BattleAnim_SetupSharedDescriptor13DirectionalSprayScaledFade(ParticleEffectInstance* arg0);
void BattleAnim_CallbackSharedDescriptor13DirectionalSprayScaledFade(ParticleEffectInstance* arg0);
void BattleAnim_SetupStartEffect59EndEffect28DirectionalStreamFade(ParticleEffectInstance* arg0);
void BattleAnim_CallbackStartEffect59EndEffect28DirectionalStreamFade(ParticleEffectInstance* arg0);
void BattleAnim_SetupUnregisteredStraightDirectionalStreamFade(ParticleEffectInstance* arg0);
void BattleAnim_CallbackUnregisteredStraightDirectionalStreamFade(ParticleEffectInstance* arg0);
void BattleAnim_SetupEndEffect28Descriptor10UpwardBurstFade(ParticleEffectInstance* arg0);
void BattleAnim_CallbackEndEffect28Descriptor10UpwardBurstFade(ParticleEffectInstance* arg0);
void BattleAnim_SetupEndEffect28Descriptor10WideScatterBurstFade(ParticleEffectInstance* arg0);
void BattleAnim_CallbackEndEffect28Descriptor10WideScatterBurstFade(ParticleEffectInstance* arg0);
void BattleAnim_StartEffect18ScatterRadialAndColumnSequence(void);
void func_8433DECC(void);
void func_8433DFF4(void);
void func_8433E124(void);
void func_8433E33C(void);
void func_8433E46C(void);
void BattleAnim_EndEffect70Descriptor0F_13SprayColumnSequence(void);


void BattleAnim_InitStartEffect135Descriptor1CRisingScale(ParticleEffectInstance* arg0);
void BattleAnim_CallbackStartEffect135Descriptor1CRisingScaleFade(ParticleEffectInstance* arg0);
void BattleAnim_InitStartEffect135ExpandingFlash(ParticleEffectInstance* arg0);
void BattleAnim_CallbackStartEffect135ExpandingFlashFade(ParticleEffectInstance* arg0);
void BattleAnim_InitStartEffect139Descriptor42FallingScale(ParticleEffectInstance* arg0);
void BattleAnim_CallbackStartEffect139Descriptor42FallingScaleFade(ParticleEffectInstance* arg0);
void BattleAnim_InitStartEffect139Descriptor22SpinFade(ParticleEffectInstance* arg0);
void BattleAnim_CallbackStartEffect139Descriptor22SpinFadeSpark(ParticleEffectInstance* arg0);
void BattleAnim_InitStartEffect141Descriptor1CGridRise(ParticleEffectInstance* arg0);
void BattleAnim_CallbackStartEffect141Descriptor1CGridRiseFade(ParticleEffectInstance* arg0);
void BattleAnim_InitStartEffects133And134And143Descriptor44ModeOrbit(ParticleEffectInstance* arg0);
void BattleAnim_CallbackStartEffects133And134And143Descriptor44ModeOrbitSwirl(ParticleEffectInstance* arg0);
void BattleAnim_InitStartEffects133And134And143Descriptor38MetadataBurst(ParticleEffectInstance* arg0);
void BattleAnim_CallbackStartEffects133And134And143Descriptor38MetadataBurstEmitter(ParticleEffectInstance* arg0);
s16 BattleAnim_GetSessionModeEffectParam(void);
void BattleAnim_StartEffect139DualRepeatingSparks(void);
void BattleAnim_StartEffect140StartEffect139Alias(void);
void BattleAnim_StartEffect141GridRiseAndFallingBurst(void);
void BattleAnim_StartEffect142StartEffect141Alias(void);
void BattleAnim_StartEffect135ExpandingFlashAndRisingScaleFade(void);
void BattleAnim_StartEffect134ModeOrbitAndMetadataBurst(void);
void BattleAnim_StartEffect143ModeOrbitAndMetadataBurst(void);
void BattleAnim_StartEffect133ModeOrbitBurstAndEffect135Followup(void);
void BattleAnim_StartEffect122GlobalAndOwnerTintFade(void);


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
void ParticleEffect_StateHandlerA(ParticleEffectInstance* arg0);
void ParticleEffect_StateHandlerB(ParticleEffectInstance* arg0);
void ParticleEffect_StateHandlerC(ParticleEffectInstance* arg0);
void ParticleEffect_StateHandlerD(ParticleEffectInstance* arg0);
void ParticleEffect_StateHandlerE(ParticleEffectInstance* arg0);
void ParticleEffect_StateHandlerF(ParticleEffectInstance* arg0);
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
void ParticleEffect_PaletteFadeHandler(ParticleEffectInstance* arg0);
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
void ParticleEffect_StateHandler_4669C(ParticleEffectInstance* arg0);
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
void ParticleEffect_Noop_48C6C(UNUSED s32 arg0, UNUSED s32 arg1);
void ParticleEffect_Noop_48C78(UNUSED s32 arg0, UNUSED s32 arg1);
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
void Gfx_ParticlePaletteCallback(s32 arg0, arg1_func_84344CE8* arg1);
void func_84349FC8(Gfx* arg0, UNUSED arg1_func_8434E21C* arg1, UNUSED u16 arg2);
void Gfx_ParticlePaletteCallback2(s32 arg0, arg1_func_84344CE8* arg1);
s16 Particle_GetPaletteIndex(void);
s16 Particle_GetPaletteColorA(void);
s16 Particle_GetPaletteColorB(void);
void ParticleEffect_PaletteBurst(void);
void ParticleEffect_PaletteMultiBurst(void);
f32 ParticleEffect_SpeciesAdjustA(ParticleEffectInstance* arg0);
void Gfx_ParticleTextureTileCallback(Gfx* arg0, arg1_func_8434E21C* arg1, UNUSED u16 arg2);
void Gfx_ParticleTextureTileCallback2(s32 arg0, arg1_func_84344CE8* arg1);
void Gfx_ParticleRedPrimCallback(Gfx* arg0, UNUSED arg1_func_8434E21C* arg1, UNUSED u16 arg2);
void Gfx_ParticleRedPrimCallback2(s32 arg0, arg1_func_84344CE8* arg1);
void ParticleEffect_SimpleBurst(void);
void ParticleEffect_SimpleCallback(void);
void ParticleEffect_SimpleBurstScript(void);
void func_8434A930(void);
void ParticleEffect_MultiNodeAEntry(void);
void func_8434A9EC(void);
void ParticleEffect_MultiNodeC2(void);
void Gfx_PokemonPortraitCallback(Gfx* arg0, u8 arg1, UNUSED u16 arg2);
void Gfx_PokemonPortraitCallback2(s32 arg0, arg1_func_84344CE8* arg1);
void ParticleEffect_PortraitBurst(void);
void ParticleEffect_PortraitBurstInit(void);
void ParticleEffect_PortraitBurstNode(void);
void ParticleEffect_PortraitBurstCheck(void);
f32 ParticleEffect_SpeciesAdjustB(ParticleEffectInstance* arg0);
void ParticleEffect_SimpleBurst2(void);
void ParticleEffect_SimpleBurst3(void);
void ParticleEffect_SpeciesAdjustC(ParticleEffectInstance* arg0);
void ParticleEffect_PaletteInit(ParticleEffectInstance* arg0);
void ParticleEffect_PaletteStateHandler(ParticleEffectInstance* arg0);
void Gfx_PaletteParticleDL(Gfx* arg0, u8* arg1, UNUSED u16 arg2);
void Gfx_PaletteParticleDLCallback(s32 arg0, arg1_func_84344CE8* arg1);
void ParticleEffect_PaletteMultiBurst2(void);
void ParticleEffect_PaletteMultiBurst3(void);
void ParticleEffect_PaletteScriptBurst(void);
void ParticleEffect_PaletteBurst4(void);
void ParticleEffect_PaletteBurst5(void);
void ParticleEffect_FireworkBurst(void);
void ParticleEffect_WaterAnimInit(ParticleEffectInstance* arg0);
void ParticleEffect_WaterAnimStateHandler(ParticleEffectInstance* arg0);
void ParticleEffect_WaterAnimInit2(ParticleEffectInstance* arg0);
void ParticleEffect_WaterAnimStateHandler2(ParticleEffectInstance* arg0);
void Gfx_WaterAnimPrimEnvDL(Gfx* arg0, u8 arg1, UNUSED u16 arg2);
void Gfx_WaterAnimPrimEnvDLCallback(s32 arg0, arg1_func_84344CE8* arg1);
void ParticleEffect_WaterAnimBurst(void);
void ParticleEffect_WaterAnimBurst2(void);
void ParticleEffect_WaterAnimFirework(void);
void ParticleEffect_WaterAnimFirework2(void);
void Gfx_WaterAnimDL(Gfx* arg0, u8* arg1, UNUSED u16 arg2);
void Gfx_WaterAnimDLCallback(s32 arg0, arg1_func_84344CE8* arg1);
f32 ParticleEffect_SpeciesAdjustD(ParticleEffectInstance* arg0);
void ParticleEffect_BasicMultiBurst(void);
void ParticleEffect_FireballBurst(void);
void ParticleEffect_BasicMultiBurst2(void);
void ParticleEffect_AdvancedMultiBurst(void);
void ParticleEffect_SimpleBurst4(void);
void ParticleEffect_SimpleStateInit(ParticleEffectInstance* arg0);
void ParticleEffect_SimpleStateHandler(ParticleEffectInstance* arg0);
void ParticleEffect_RotationInit(ParticleEffectInstance* arg0);
void ParticleEffect_RotationStateHandler(ParticleEffectInstance* arg0);
void ParticleEffect_RotationEntry(void);
void ParticleEffect_FireworkInit(ParticleEffectInstance* arg0);
void ParticleEffect_FireworkStateHandler(ParticleEffectInstance* arg0);
void ParticleEffect_FireworkEntry(void);
void ParticleEffect_SimpleNodeInit(ParticleEffectInstance* arg0);
void ParticleEffect_SimpleNodeStateHandler(ParticleEffectInstance* arg0);
void Gfx_SimpleNodeDL(Gfx* arg0, arg1_func_8434E21C* arg1, UNUSED u16 arg2);
void Gfx_SimpleNodeDLCallback(s32 arg0, arg1_func_84344CE8* arg1);
void ParticleEffect_SimpleNodeEntry(void);
void ParticleEffect_SimpleNodeBurst(void);
void ParticleEffect_AlphaStateHandler(ParticleEffectInstance* arg0);
void ParticleEffect_AlphaBurst(void);
void ParticleEffect_AlphaBurst2(void);
void ParticleEffect_AlphaFirework(void);
void ParticleEffect_AlphaFirework2(void);
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
void ParticleEffect_AlphaFadeHandler(ParticleEffectInstance* arg0);
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
void BattleAnim_CallbackStartEffect132Descriptor39DelayedRiseFade(ParticleEffectInstance* arg0);
void ParticleEffect_CreateDual(void);
void Particle_SetDirectionOffsets(ParticleEffectInstance* arg0);
void Particle_HandleState(ParticleEffectInstance* arg0);
void Particle_SetupSpecialOffsets(ParticleEffectInstance* arg0);
void Particle_HandleState_Special(ParticleEffectInstance* arg0);
void Particle_SetupSpecialColorOffsets(ParticleEffectInstance* arg0);
void Particle_HandleState_SpecialColor(ParticleEffectInstance* arg0);
void Particle_CollisionInit_Standard(ParticleEffectInstance* arg0);
void Particle_HandleCollisionResponse(ParticleEffectInstance* arg0);
void Particle_CollisionInit_ExplosionAlt(ParticleEffectInstance* arg0);
void Particle_HandleCollisionResponse_ExplosionAlt(ParticleEffectInstance* arg0);
void Particle_DirectionalInit(ParticleEffectInstance* arg0);
void Particle_HandleState_Directional(ParticleEffectInstance* arg0);
void Particle_HandleState_Directional_Scale(ParticleEffectInstance* arg0);
void Particle_HandleState_Directional_ScaleAlt(ParticleEffectInstance* arg0);
void Particle_SootInit(ParticleEffectInstance* arg0);
void Particle_HandleState_Soot(ParticleEffectInstance* arg0);
void Particle_SparkInit(ParticleEffectInstance* arg0);
void Particle_HandleState_Spark(ParticleEffectInstance* arg0);
void Particle_SparkAltInit(ParticleEffectInstance* arg0);
void Particle_HandleState_SparkAlt(ParticleEffectInstance* arg0);
void Particle_ElectricInit(ParticleEffectInstance* arg0);
void Particle_HandleState_Electric(ParticleEffectInstance* arg0);
void Particle_GlowInit(ParticleEffectInstance* arg0);
void Particle_HandleState_Glow(ParticleEffectInstance* arg0);
void Particle_DebrisInit(ParticleEffectInstance* arg0);
void Particle_HandleState_Debris(ParticleEffectInstance* arg0);
void Particle_FireworkInit(ParticleEffectInstance* arg0);
void ParticleEffect_StateHandler_50DAC(ParticleEffectInstance* arg0);
void Particle_SmokeInit(ParticleEffectInstance* arg0);
void Particle_HandleState_Smoke(ParticleEffectInstance* arg0);
void Particle_FlashInit(ParticleEffectInstance* arg0);
void Particle_HandleState_Flash(ParticleEffectInstance* arg0);
void Particle_SmallDotInit(ParticleEffectInstance* arg0);
void Particle_HandleState_SmallDot(ParticleEffectInstance* arg0);
void Particle_RandomDotInit(ParticleEffectInstance* arg0);
void Particle_HandleState_RandomDot(ParticleEffectInstance* arg0);
void Particle_ColoredDotInit(ParticleEffectInstance* arg0);
void Particle_HandleState_ColoredDot(ParticleEffectInstance* arg0);
void Particle_MultiColorDotInit(ParticleEffectInstance* arg0);
void Particle_HandleState_MultiColorDot(ParticleEffectInstance* arg0);
void Particle_SpiralInit(ParticleEffectInstance* arg0);
void Particle_HandleState_Spiral(ParticleEffectInstance* arg0);
void ParticleNode_CreateExplosion(ParticleEffectInstance* arg0);
void Particle_HandleState_ExplosionNode(ParticleEffectInstance* arg0);
void Particle_ComplexInit(ParticleEffectInstance* arg0);
void Particle_HandleState_Complex(ParticleEffectInstance* arg0);
void ParticleEffect_FireworkStage1(ParticleEffectInstance* arg0);
void ParticleEffect_FireworkHandler(ParticleEffectInstance* arg0);
void ParticleEffect_FireworkHandler2(ParticleEffectInstance* arg0);
void BattleAnim_CallbackEndEffect43Descriptor40DelayedAnimFade_InitParticle(ParticleEffectInstance* arg0);
void ParticleEffect_SparkleHandler(ParticleEffectInstance* arg0);
void ParticleEffect_FireworkMainInit(ParticleEffectInstance* arg0);
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
void ParticleEffect_DirectionalHandler(ParticleEffectInstance* arg0);
void func_843553B4(void);
void ParticleEffect_BasicHandler(ParticleEffectInstance* arg0);
void ParticleEffect_FadeAndScale(ParticleEffectInstance* arg0);
void ParticleEffect_SpeedAndAlpha(ParticleEffectInstance* arg0);
void ParticleEffect_RotationAndColor(ParticleEffectInstance* arg0);
void ParticleEffect_ConditionalUpdate(ParticleEffectInstance* arg0);
void ParticleEffect_RandomRotation(ParticleEffectInstance* arg0);
void BattleAnim_CallbackStartEffects29And60And104And110DefaultDescriptorBurstEmitter(ParticleEffectInstance* arg0);
void ParticleEffect_PrimColorAndEnv(ParticleEffectInstance* arg0);
void ParticleEffect_ComplexSequence(ParticleEffectInstance* arg0);
void ParticleEffect_Sparkle(ParticleEffectInstance* arg0);
void ParticleEffect_SparkleHandlerState(ParticleEffectInstance* arg0);
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


void BattleAnim_RenderNop1(void);
void func_84358FF8(void);
void RenderPrimColorRect(u8, u8, u8, u8);
void Ui_DrawPanel(CameraStruct*);


void BattleAnim_NoopUpdateHook(void);
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
void BattleAnim_DrawStoredColorOverlay(void);
void BattleAnim_ReinitAuxiliaryEffects(void);
void func_843593A0(void);
void func_843593A8(void);
s32 BattleAnim_DefaultStartEffect_CompleteImmediately(void);
s32 BattleAnim_DefaultEndEffect_CompleteImmediately(void);
void BattleAnim_DefaultStartEffect_Draw(void);
void BattleAnim_DefaultEndEffect_Draw(void);
void Battle_GetTertiaryOwnerBonePositionUnused(Vec3f* arg0);
void BattleAnim_EffectSecondaryOwnerAnchorPosition(Vec3f* arg0);
void BattleAnim_EffectTertiaryOwnerBonePosition(Vec3f* arg0);
void BattleAnim_EffectSecondaryOwnerBonePosition(Vec3f* arg0);
f32 BattleAnim_EffectTertiaryOwnerModelScale(void);
f32 BattleAnim_EffectSecondaryOwnerModelScale(void);
void CalcVectorATtoDM(f32* arg0, f32* arg1, f32* arg2, f32* arg3, f32* arg4, f32* arg5);
void CalcVectorATtoDM2(f32* arg0, f32* arg1, f32* arg2, f32* arg3, f32* arg4, f32* arg5);
void InitEffectMatrix(void);
void SpawnParticleEmitters_Default(void);
s32 BattleAnim_Effect5RibbonMesh_Update(void);
void BattleAnim_Effect5RibbonMesh_Draw(void);
void SpawnParticleEmitters_Alt(void);
s32 BattleAnim_EndEffect1RibbonMesh_Update(void);
void BattleAnim_EndEffect1RibbonMesh_Draw(void);
void SpawnParticleEmitters_Dual(void);
s32 BattleAnim_EndEffect19RibbonMesh_Update(void);
void BattleAnim_EndEffect19RibbonMesh_Draw(void);
void SpawnParticleEmitters_Alt2(void);
s32 BattleAnim_Effect54RibbonMesh_Update(void);
void BattleAnim_Effect54RibbonMesh_Draw(void);
void WaterHeightMap_InitByCameraX(void);
s32 BattleAnim_StartEffect34TerrainGrid_Update(void);
void BattleAnim_StartEffect34TerrainGrid_Draw(void);
void BattleAnim_EndEffect16_NoOpInit(void);
s32 BattleAnim_EndEffect16_CompleteImmediately(void);
void BattleAnim_EndEffect16_NoOpDraw(void);
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
void RibbonMesh_Spawn(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, s32 arg5);
void ParticleEmitter_UpdateFade(unk_D_843925E0* arg0);
s32 ParticleEmitter_Update(unk_D_843925E0* arg0);
s32 ParticleEmitters_Tick(void);
Gfx* ParticleEmitter_BuildVertexBuffer(Gfx* arg0, unk_D_843925E0* arg1);
Gfx* ParticleEmitters_Render(Gfx* arg0);
void TerrainGrid_BuildCameraBounds(unk_D_843975E8* arg0, f32 arg1);
f32 TerrainGrid_SampleHeightAndSlope(f32 arg0, f32 arg1, f32* arg2);
s32 WaterHeightMap_Update(void);
void WaterHeightMap_Init(s32 arg0, s16 arg1, s16 arg2);
s32 TerrainGrid_Update(void);
Gfx* WaterSurface_Render(Gfx* arg0);


void Trail_Init(f32 arg0, f32 arg1, f32 arg2, f32 arg3, u8 arg4, u8 arg5, u8 arg6, u8 arg7, u8 arg8, u8 arg9);
f32 Trail_GetWidthScale(void);
s32 Trail_Update(void);
Gfx* Trail_Render(Gfx* arg0);
void Radial20_ResetPool(void);
void ParticleEmitter_AddSimple(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, s16 arg6, u8 arg7, u8 arg8, u8 arg9, u8 argA, f32 argB, f32 argC, f32 argD, s16 argE);
void ParticleEmitter_AddSimpleNoFade(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, s16 arg6, u8 arg7, u8 arg8, u8 arg9, u8 argA, f32 argB, f32 argC, f32 argD, s16 argE);
void ParticleEmitter_AddRandomized(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, s16 arg6, u8 arg7, u8 arg8, u8 arg9, u8 argA, u8 argB, u8 argC, u8 argD, f32 argE, f32 argF, f32 arg10, s16 arg11);
void Radial20_VariantD(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, s16 arg6, u8 arg7, u8 arg8, u8 arg9, u8 argA, u8 argB, u8 argC, u8 argD, f32 argE, f32 argF, f32 arg10, s16 arg11);
void Radial20_VariantE(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, s16 arg6, u8 arg7, u8 arg8, u8 arg9, u8 argA, f32 argB, f32 argC, f32 argD, s16 argE);
void Radial20_RotateVertexOffset(f32 arg0, UNUSED Vec3f* arg1, Vec3f* arg2, f32 arg3, UNUSED f32 arg4, UNUSED f32 arg5, UNUSED f32 arg6);
void Radial20_UpdateNode(unk_D_84398F50* arg0);
s32 Radial20_IsComplete(void);
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


void Trail40GridAlt_Init(s16 arg0);
void WaterSurface_CalcVertexNormal(s32 arg0, s32 arg1);
void WaterSurface_PackVertex(WaterSurfaceVertex* arg0, Vtx* arg1);
s32 Trail40GridAlt_IsComplete(void);
void Trail40GridAlt_Reset(void);
Gfx* Trail40GridAlt_Draw(Gfx* arg0);


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


void Battle_DebugLogClear(void);


void func_8436F6D0(void);
u8 GetRandomU8(void);
u8 GetRandomU8_Alt(void);
void ShowDamageMessage(s32 arg0, s32 arg1);
void ResetBattleAfterMove(s32 arg0, s32 arg1);
void func_8436FA80(unk_BattlePlayerEntity* arg0);
void ApplyDamageRandomFactor(void);
u16 CompareMovePriority(unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1);
s32 IsByteInArray(u8 arg0, u8* arg1, s32 arg2);
void Battle_SetActiveMoveFromSlotIndex(void);
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
void Battle_ApplyAnimStateEffects(unk_BattlePlayerEntity* arg0);
void ApplyParalysisSpeedCut(unk_BattlePlayerEntity* arg0);
void ApplyBurnAttackCut(unk_BattlePlayerEntity* arg0);
void func_84370B7C(unk_BattlePlayerEntity* arg0);
s32 Battle_IsPartyMemberAlive(unk_BattlePlayerEntity* arg0);
void func_84370E70(void);
void func_84370E78(void);
void func_84370E80(void);
void Battle_ApplyRageContinuation(void);
void func_84371010(void);
void func_84371080(void);
void func_8437114C(void);
void Battle_QueueMoveFailureAndApplyRecoil(void);
void func_843714D8(void);
s32 Battle_Effect_Metronome(void);
void Battle_ApplyPoisonOrBurnDamage(void);
void Battle_ApplyLeechSeedDamage(void);
s32 Battle_ApplyResidualEffects(void);
void func_843718DC(void);
s32 Battle_TryLoadFollowupMoveFromTarget(void);
void Battle_ApplyTypeEffectAndSTAB(void);
s32 Battle_Effect_Counter(void);
s32 Battle_CheckCriticalHit(void);
s32 ProcessBattleEntityStatus(void);
void ProcessBattleTurn(void);
void ResetBattleEntityStatus(unk_BattlePlayerEntity* arg0);
void CheckAllPartyFainted_HP(unk_BattlePlayerEntity* arg0);
void CheckAllPartyFainted_Status(unk_BattlePlayerEntity* arg0);
void CheckAllPartyFainted_PP(unk_BattlePlayerEntity* arg0);
void CheckAllPartyFainted_Level(unk_BattlePlayerEntity* arg0);
s32 CheckBattleEntityFaintStatus(unk_BattlePlayerEntity* arg0);
s32 ProcessFaintChecks(void);
void BeginBattleMainLoop(void);
void BeginBattleForEntity(unk_BattlePlayerEntity* arg0);


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
void Battle_Effect_Thrash(void);
void Battle_HandleSpecialMove(void);
void Battle_Effect_MultiHit(void);
void Battle_Effect_Flinch(void);
void Battle_Effect_OHKO(void);
void Battle_DisplayStatusMessage(void);
void Battle_Effect_Trap(void);
void Battle_Effect_Mist(void);
void Battle_Effect_FocusEnergy(void);
void Battle_Effect_Recoil(void);
void Battle_StartMiniGame(void);
void Battle_Effect_Confuse(void);
void Battle_Effect_Paralyze(void);
void Battle_Effect_Substitute(void);
void Battle_Effect_Recharge(void);
void Battle_Effect_Rage(void);
void Battle_Effect_Mimic(void);
void Battle_Effect_LeechSeed(void);
void Battle_Effect_Splash(void);
void Battle_Effect_Disable(void);
void Battle_Effect_PayDay(void);
void Battle_Effect_Conversion(void);
void Battle_Effect_Haze(void);
void Battle_Effect_Heal(void);
void Battle_Effect_Transform(void);
void Battle_Effect_ReflectLightScreen(void);
void SpAttack_Dispatch(void);
void SpAttack_Main(void);


void BattleAI_LoadConfiguration(s32 arg0, u32 arg1);
void func_843767DC(void);
s32 BattleAI_RandomBelowInclusive(s32 arg0);
void BattleAI_SeedRandomState(u8 arg0);
u8 BattleAI_EstimateCriticalHitChance(unk_D_800FCB18* arg0, unk_D_800FCB18* arg1, u8 arg2);
u16 BattleAI_ApplyMoveEffectDamageOverride(unk_D_800FCB18* arg0, unk_D_800FCB18* arg1);
void BattleAI_ClampDamageRatio(void);
void BattleAI_ApplyTypeEffectAndStab(unk_D_800FCB18* arg0, unk_D_800FCB18* arg1);
void BattleAI_PrepareDamageCalcState(unk_D_800FCB18* arg0, unk_D_800FCB18* arg1, u8 arg2);
void BattleAI_CalcDamage(unk_D_800FCB18* arg0, unk_D_800FCB18* arg1);
u16 BattleAI_PredictDamage(unk_D_800FCB18* arg0, unk_D_800FCB18* arg1, u8 arg2, u8 arg3);
void BattleAI_ResetTeamState(unk_D_843C60AC* arg0);
s32 BattleAI_ScaleSignedRatio(s32 arg0, s32 arg1);
void BattleAI_AppendTrainerTeamSpecies(unk_D_800AE540_0004* arg0);
s32 BattleAI_FindSpeciesIndex(s32 arg0);
s32 BattleAI_IsThresholdMet(u8 arg0, u8 arg1);
u16 BattleAI_ScaleStatHigh(unk_D_800FCB18* arg0);
u16 BattleAI_ScaleStatLow(unk_D_800FCB18* arg0);
f32 Battle_GetTypeEffectiveness(u8 arg0, unk_D_800FCB18* arg1);
s32 BattleAI_AllCandidatesResistType(u8 arg0, unk_D_843C60A4* arg1);
s32 BattleAI_IsTypeMatchupAllowed(u8 arg0, u8 arg1);
s32 BattleAI_HasCandidateStatusMask(unk_D_843C60A4* arg0, u8 arg1);
u8 BattleAI_ClassifyMoveAvailability(unk_D_843C60AC* arg0, unk_D_843C60AC* arg1, u8 arg2);
void func_843779C0(void);
u8 BattleAI_FindHeuristicMove(unk_D_843C60AC* arg0, unk_D_843C60AC* arg1, u8 arg2, u8* arg3);
u8 BattleAI_SelectBestHeuristicCandidate(unk_D_843C60AC* arg0, unk_D_843C60A4* arg1, u8* arg2, u8 arg3, u8* arg4);
s32 BattleAI_IsPriorityTableMove(u8 arg0, u8 arg1);
u8 BattleAI_ScoreCategorySetLowPP(unk_D_843C60AC* arg0, unk_D_843C60AC* arg1);
u8 BattleAI_ScoreCategorySetReady(unk_D_843C60AC* arg0, unk_D_843C60AC* arg1);
u8 BattleAI_HasExactlyOneUsableCandidate(unk_D_843C60A4* arg0);
void BattleAI_InitializeOrderCandidates(unk_D_800AE540_0004* arg0, unk_D_800AE540_0004* arg1, unk_D_800AE540_0004* arg2, unk_D_843C5568* arg3, s32 arg4);
void BattleAI_UpdateRememberedMoveCandidate(unk_D_843C60AC* arg0, u8 arg1);
u16 BattleAI_ScoreMove(unk_D_800FCB18* arg0, unk_D_800FCB18* arg1, u8 arg2);
void BattleAI_PickBestMove(unk_D_800FCB18* arg0, unk_D_800FCB18* arg1, u16* arg2, u8* arg3, u8 arg4, u8 arg5);
s32 BattleAI_ScoreAllCandidateMoves(unk_D_843C60AC* arg0, unk_D_843C60AC* arg1, u8* arg2, u8 arg3);
s32 BattleAI_ScoreAllCandidateMovesRatioToMaxHp(unk_D_843C60AC* arg0, unk_D_843C60AC* arg1, u8* arg2, u8 arg3);
s32 BattleAI_ScoreAllCandidateMovesRatioToCurrentHp(unk_D_843C60AC* arg0, unk_D_843C60AC* arg1, u8* arg2, u8 arg3);
void func_8437921C(void);
u8 BattleAI_CalcStagedMovePower(unk_D_800FCB18* arg0, unk_D_800FCB18* arg1, u8 arg2, u8 arg3);
void BattleAI_ApplyInverseWeightScale(u8 arg0, u8* arg1);
void BattleAI_BuildMoveCandidateScores(unk_D_843C60AC* arg0, unk_D_843C60AC* arg1, s32 arg2, u8 arg3, u8 arg4, unk_func_843794CC* arg5);
s32 BattleAI_HasScoredMoveAtValue(unk_func_843794CC* arg0, u8 arg1, u8 arg2);
s32 BattleAI_IsCandidateScoreBelowPeers(unk_func_843794CC* arg0, u8 arg1, u8 arg2, u8 arg3);
u8 BattleAI_HasOtherCandidateAtLeastScore(unk_func_843794CC* arg0, u8 arg1, u8 arg2, u8 arg3);
void func_8437B0CC(unk_D_843C60A4* arg0, unk_D_843C60A4* arg1, u8 arg2, unk_func_843794CC* arg3, u8 arg4);
s32 BattleAI_IsScoreBetter(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 BattleAI_SelectBestScoredMove(unk_D_843C60AC* arg0, UNUSED unk_D_843C60AC* arg1, u8 arg2, unk_func_843794CC* arg3);
s32 BattleAI_ChooseMoveForCandidate(void);
u16 BattleAI_ComputeDifficultyThreshold(u8 arg0, u8 arg1);
u8 BattleAI_GetPpWeight(u8 arg0);
void BattleAI_InitTeamContext(unk_D_800AE540_0004* arg0, unk_D_800AE540_0004* arg1, unk_D_843C60A4* arg2, u8 arg3);
s32 BattleAI_IsSpeciesUnselected(unk_D_843C60A4* arg0, u8* arg1, u8 arg2);
s32 BattleAI_IsSpeciesInList(unk_D_843C60A4* arg0, u8* arg1, u8 arg2, u8 arg3);
s32 BattleAI_MeetsHpBudgetConstraint(unk_D_843C60A4* arg0, u8* arg1, u8 arg2, s32 arg3);
s32 BattleAI_IsCandidateEligible(unk_D_843C60A4* arg0, u8* arg1, u8 arg2, u8 arg3);
s32 BattleAI_GroupSharesTypeWeakness(unk_D_843C60A4* arg0, u8* arg1, u8 arg2);
s32 BattleAI_ScoreAllTeamCandidates(unk_D_843C60A4* arg0, unk_D_843C60A4* arg1, u8* arg2, s32* arg3);
s32 BattleAI_InsertRankedCandidateGroup(unk_D_843C60A4* arg0, s32* arg1, s32 arg2, unk_func_8437F85C_arg3* arg3, u8* arg4, u8 arg5, u8 arg6);
void BattleAI_SelectRandomFallbackOrder(unk_D_843C60A4* arg0, u8* arg1, s32 arg2);
s32 BattleAI_SelectRandomUsableCandidate(unk_D_843C60A4* arg0);
s32 BattleAI_SelectRandomUsableMoveSlot(unk_D_800FCB18* arg0);
s32 func_8437FD74(unk_D_843C60A4* arg0, u8* arg1, s32* arg2, u8 arg3);
s32 BattleAI_SelectLeadFromScoredGroup(unk_D_843C60A4* arg0, unk_D_843C60A4* arg1, u8* arg2, u8* arg3, s32* arg4);
s32 BattleAI_TryBuildScoredOrder(unk_D_843C60A4* arg0, unk_D_843C60A4* arg1, u8* arg2, u8* arg3, s32 arg4);
void BattleAI_UpdateTeamAdvantageBias(void);
u8 BattleAI_SelectBestSwitchCandidateIndex(unk_D_843C60A4* arg0, unk_D_843C60A4* arg1);
u8 BattleAI_SelectBestAttackTargetIndex(unk_D_843C60AC* arg0, s32* arg1, s32* arg2, unk_D_843C60A4* arg3, u8 arg4, s32 arg5);
s32 BattleAI_ScoreSwitchUrgencyFromThreatMove(unk_D_843C60AC* arg0, unk_D_843C60AC* arg1, u8 arg2);
s32 BattleAI_ComputeAttackTargetScore(unk_func_8438220C* arg0);
s32 BattleAI_ScoreAttackOption(unk_D_843C60AC* arg0, unk_D_843C60AC* arg1, unk_D_843C60A4* arg2, u8* arg3, s32* arg4, s32* arg5, s32* arg6, s32* arg7, s32* arg8);
s32 BattleAI_ScoreAttackOptionDoubles(unk_D_843C60AC* arg0, unk_D_843C60AC* arg1, unk_D_843C60A4* arg2, u8* arg3, unk_func_8438220C* arg4);
u8 BattleAI_ScoreAttackVsSwitch(unk_D_843C60AC* arg0, unk_D_843C60AC* arg1, unk_D_843C60A4* arg2, unk_D_843C60A4* arg3, u8* arg4, unk_func_8438220C* arg5);
u16 BattleAI_ApplyStatStageModifier(u16* arg0, u16 arg1, u8 arg2);
void BattleAI_SimulateStatBoostGuess(unk_D_800FCB18* arg0, unk_D_800FCB18* arg1, u8 arg2, u8 arg3);
void BattleAI_BuildAllCandidateMoveScores(unk_func_8438220C* arg0);
void BattleAI_RefineAllCandidateMoveScores(unk_func_8438220C* arg0);
u8 BattleAI_DecideFinalAction(unk_func_8438220C* arg0);
s32 BattleAI_DecideAction(void);
s32 BattleAI_ResolveTiedActionChoice(s32 arg0);
s32 BattleAI_MatchesLastMoveCategory(u8 arg0, u8 arg1);
s32 BattleAI_IsDiscouragedRepeatCategory(u8 arg0, u8 arg1);
s32 BattleAI_IsBannedRandomMove(u8 arg0);
s32 BattleAI_IsRestrictedRandomMove(u8 arg0);
s32 BattleAI_IsMoveExcludedForSpecies(unk_D_800FCB18* arg0, s32 arg1, u8 arg2, u8 arg3);
s32 BattleAI_IsMoveIneffective(unk_D_800FCB18* arg0, unk_D_800FCB18* arg1, u8 arg2);
void BattleAI_SyncTeamStateFromRuntime(void);
s32 func_843831A0(unk_D_800AE540_0004* arg0, unk_D_800AE540_0004* arg1, unk_D_800AE540_0004* arg2, s32 arg3, u8* arg4, s32 arg5, s32 arg6);
void BattleAI_RecordUsedMove(UNUSED s32 arg0, UNUSED s32 arg1, s32 arg2);
s32 BattleAI_ChooseAction(UNUSED s32 arg0);
void BattleAI_InitTrainerRecords(void);
s32 Battle_GetEntityState(s32 arg0, s32 arg1);

#endif // _FRAGMENT62_H_
