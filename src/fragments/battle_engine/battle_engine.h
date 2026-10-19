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
    /* 0x04 */ u32 rotation;
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
    /* 0x38 */ PokemonAudioInfo unk_38;
    /* 0x9C */ unk_D_84390010_654_09C unk_9C;
    /* 0xAC */ unk_D_84390010_654_0AC unk_AC;
    /* 0xBC */ s16 unk_BC;
    /* 0xBE */ s16 unk_BE;
    /* 0xC0 */ char unkC0[1];
    /* 0xC1 */ u8 statFlags[4];
    /* 0xC8 */ Controller* controller;
} unk_BattlePlayerAnimState; // size = 0xCC

typedef struct unk_D_84390010_728_0168 {
    /* 0x00 */ GraphRootNode posX;
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
    /* 0x00 */ s32 posX;
    /* 0x04 */ s32 rotation;
    /* 0x08 */ s8 unk_08[4];
    /* 0x0C */ char unk0C[0x3C];
    /* 0x48 */ s8 unk_48[4];
    /* 0x4C */ char unk4C[0x3C];
} unk_D_84390010_8C4; // size = 0x88

typedef struct unk_D_84390010_94C {
    /* 0x00 */ u8 posX[10];
    /* 0x0A */ u8 unk_0A[4];
    /* 0x0E */ char unk0E[0x12];
} unk_D_84390010_94C; // size = 0x20

typedef struct unk_D_84390048 {
    /* 0x00 */ Vec3f posX;
    /* 0x0C */ Vec3f unk_0C;
    /* 0x18 */ u8 unk_18;
    /* 0x19 */ u8 unk_19;
    /* 0x1A */ u8 unk_1A;
    /* 0x1B */ u8 unk_1B;
    /* 0x1C */ char unk1C[4];
} unk_D_84390048; // size = 0x20

typedef struct unk_D_84390010_448 {
    /* 0x00 */ Vec3f posX;
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
    /* 0x498 */ f32 launchSpeed;
    /* 0x49C */ f32 unk_49C;
    /* 0x4A0 */ f32 oscillationAmplitude;
    /* 0x4A4 */ s16 unk_4A4;
    /* 0x4A6 */ s16 unk_4A6;
    /* 0x4A8 */ s16 tiltAngle;
    /* 0x4AC */ s32 frameCounter;
    /* 0x4B0 */ s32 sideSign;
    /* 0x4B4 */ s32 animationMode;
    /* 0x4B8 */ s32 animationSubstate;
    /* 0x4BC */ char unk4BC[0x4];
    /* 0x4C0 */ s32 moveAnimIndex;
    /* 0x4C4 */ s32 animationStateIndex;
    /* 0x4C8 */ s32 unk_4C8;
    /* 0x4CC */ Vec3f unk_4CC;
    /* 0x4D8 */ Vec3f secondarySwayOffset;
    /* 0x4E4 */ f32 swayMagnitude;
    /* 0x4E8 */ u8 secondaryStatusId;
    /* 0x4E9 */ u8 secondaryStatusState;
    /* 0x4EC */ Fragment2_1GraphNode effectGraphNode;
    /* 0x654 */ unk_BattlePlayerAnimState animationState;
    /* 0x720 */ unk_D_800AE540_1194* pokemonAnimation;
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
    /* 0x00 */ unk_D_84390240_000* posX;
    /* 0x04 */ char unk04[0x3C];
} unk_D_84390240; // size = 0x40

typedef void (*unk_D_84385384_func)(unk_BattlePlayerEntity*);

typedef struct unk_D_84385384 {
    /* 0x00 */ s16 posX;
    /* 0x04 */ unk_D_84385384_func rotation[7];
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
    /* 0x00 */ s32 posX;
    /* 0x04 */ char unk04[0x54];
} unk_D_843C4DEC; // size = 0x58

typedef struct unk_D_84390068 {
    /* 0x00 */ s32 posX;
    /* 0x04 */ unk_D_84385384_func rotation;
} unk_D_84390068; // size = 0x8

typedef struct unk_D_84384588 {
    /* 0x00 */ u8 posX;
    /* 0x01 */ u8 unk_01;
    /* 0x02 */ char unk02[0xE];
} unk_D_84384588; // size = 0x10

typedef struct BattleInitState {
    /* 0x00 */ s32 posX;
    /* 0x04 */ char unk04[0x14];
} BattleInitState; // size >= 0x18

typedef struct unk_D_8438FF70 {
    /* 0x00 */ Vec3f posX;
    /* 0x0C */ s16 unk_0C;
    /* 0x0E */ s16 unk_0E;
    /* 0x10 */ s16 unk_10;
    /* 0x12 */ u16 unk_12;
    /* 0x14 */ char unk14[0xC];
} unk_D_8438FF70; // size = 0x20

typedef struct unk_D_84390028 {
    /* 0x00 */ f32 posX;
    /* 0x04 */ f32 rotation;
    /* 0x08 */ f32 unk_08;
    /* 0x0C */ f32 unk_0C;
} unk_D_84390028; // size = 0x10

typedef struct unk_D_84384608 {
    /* 0x00 */ s32 posX;
    /* 0x04 */ u16 rotation;
} unk_D_84384608; // size = 0x8

typedef struct unk_D_843847BC {
    /* 0x00 */ s16 posX;
    /* 0x02 */ s16 posY;
    /* 0x04 */ s16 rotation;
    /* 0x08 */ f32 unk_08;
    /* 0x0C */ f32 unk_0C;
    /* 0x10 */ f32 unk_10;
    /* 0x14 */ s16 unk_14;
} unk_D_843847BC; // size = 0x18

typedef struct unk_D_843901B0 {
    /* 0x00 */Vec3f posX;
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
    /* 0x00 */ s32 posX;
    /* 0x04 */ s32 rotation;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ s32 unk_10;
    /* 0x14 */ Vec3f unk_14;
    /* 0x20 */ f32 unk_20;
    /* 0x24 */ f32 unk_24;
    /* 0x28 */ s16 unk_28;
    /* 0x2A */ s16 unk_2A;
} unk_D_843901A0_4C8; // size = 0x2C

typedef struct BattleMessageBuffers {
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
} BattleMessageBuffers; // size = 0x4F4

typedef struct unk_D_84385790 {
    /* 0x00 */ s32 posX;
    /* 0x04 */ Color_RGBA8 rotation;
} unk_D_84385790; // size = 0x8

typedef struct arg1_func_84344CE8 {
    /* 0x00 */ char unk00[0x14];
    /* 0x14 */ u8* unk_14;
    /* 0x18 */ Gfx* unk_18;
} arg1_func_84344CE8; // size >= 0x1C

typedef struct arg1_func_8434E21C {
    /* 0x00 */ u8* posX;
    /* 0x04 */ u8* rotation;
    /* 0x08 */ char unk08[0x2];
    /* 0x0A */ s16 unk_0A;
} arg1_func_8434E21C; // size >= 0xC

typedef struct unk_D_843925E0_430 {
    /* 0x00 */ f32 posX;
    /* 0x04 */ f32 rotation;
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
    /* 0x00 */ f32 posX;
    /* 0x04 */ f32 rotation;
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
    /* 0x00 */ f32 posX;
    /* 0x04 */ u8 rotation;
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
    /* 0x00 */ f32 posX;
    /* 0x04 */ f32 rotation;
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
    /* 0x00 */ f32 posX;
    /* 0x04 */ f32 rotation;
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
    /* 0x00 */ f32 posX;
    /* 0x08 */ u8 rotation;
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
    /* 0x00 */ u8 posX;
    /* 0x04 */ f32 rotation;
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
    /* 0x00 */ u8 posX;
    /* 0x04 */ f32 rotation;
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
    /* 0x00 */ u8 posX;
    /* 0x04 */ f32 rotation;
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
    /* 0x00 */ u8 posX;
    /* 0x04 */ f32 rotation;
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
    /* 0x00 */ s32 posX;
    /* 0x04 */ u8 rotation;
    /* 0x08 */ f32 unk_08;
    /* 0x0C */ f32 unk_0C;
    /* 0x10 */ Vec3f unk_10;
    /* 0x1C */ f32 unk_1C;
    /* 0x20 */ f32 unk_20;
    /* 0x24 */ f32 unk_24;
} WaterParticleVertex; // size = 0x28

typedef struct TextureTileInfo {
    /* 0x00 */ s16 posX;
    /* 0x02 */ s16 posY;
    /* 0x04 */ s16 rotation;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ s16 unk_08;
    /* 0x0A */ s16 unk_0A;
} TextureTileInfo; // size = 0xC

typedef struct CombineParams {
    /* 0x00 */ s32 posX;
    /* 0x04 */ s32 rotation;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ s32 unk_10;
    /* 0x14 */ s32 unk_14;
    /* 0x18 */ s32 unk_18;
    /* 0x1C */ s32 unk_1C;
} CombineParams; // size = 0x20

typedef struct ColorBlendInfo {
    /* 0x00 */ Color_RGBA8 posX;
    /* 0x04 */ u8 rotation;
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
    /* 0x081 */ ColorBlendInfo envColorBlend;
    /* 0x086 */ Color_RGBA8 lineColor;
    /* 0x08C */ f32 unk_08C;
    /* 0x090 */ f32 unk_090;
    /* 0x094 */ s16 unk_094;
    /* 0x096 */ char unk096[0x1A];
    /* 0x0B0 */ WaterParticleVertex unk_0B0[10];
} WaterParticleSystem; // size = 0x240

typedef struct Particle {
    /* 0x00 */ s16 posX;
    /* 0x02 */ s16 posY;
    /* 0x04 */ s16 rotation;
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
    /* 0x00 */ f32 posX;
    /* 0x04 */ f32 rotation;
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
    /* 0x00 */ u8 posX;
    /* 0x01 */ u8 unk_01;
} StatStageMultiplier; // size = 0x2

typedef struct TypeEffectivenessEntry {
    /* 0x00 */ u8 posX;
    /* 0x01 */ u8 unk_01;
    /* 0x02 */ u8 posY;
} TypeEffectivenessEntry; // size = 0x3

typedef struct unk_D_843C60AC {
    /* 0x00 */ u8 posX;
    /* 0x01 */ u8 unk_01;
    /* 0x02 */ u8 posY;
    /* 0x03 */ u8 unk_03;
    /* 0x04 */ u8 rotation;
    /* 0x05 */ u8 unk_05[1];
    /* 0x0C */ char unk06[0xC];
    /* 0x12 */ PokemonAudioInfo unk_12;
} unk_D_843C60AC; // size = 0x76

typedef struct unk_D_843C60A4 {
    /* 0x00 */ u8 posX;
    /* 0x01 */ u8 unk_01[2];
    /* 0x03 */ u8 unk_03;
    /* 0x04 */ u8 rotation[2];
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
    /* 0x00 */ u8 posX;
    /* 0x01 */ u8 unk_01;
    /* 0x02 */ u8 posY;
    /* 0x03 */ u8 unk_03;
    /* 0x04 */ u8 rotation;
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
    /* 0x00 */ u8 posX[1];
    /* 0x01 */ char unk01[9];
    /* 0x0A */ u8 unk_0A[1];
    /* 0x0B */ char unk0B[0x15];
} unk_D_843C5310; // size = 0x20

typedef struct unk_D_843C60C0 {
    /* 0x00 */ u8 posX;
    /* 0x01 */ u8 unk_01;
    /* 0x02 */ u8 posY;
    /* 0x04 */ s32 rotation[1];
    /* 0x08 */ char unk08[0xC];
} unk_D_843C60C0; // size = 0x14

typedef struct unk_D_843C60F0_00C {
    /* 0x00 */ s32 posX;
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
    /* 0x10 */ u8 unk_10;
    /* 0x11 */ char unk11[0x3];
} unk_D_843C60F0_00C; // size = 0x14

typedef struct unk_D_843C60F0 {
    /* 0x00 */ u8 posX;
    /* 0x01 */ u8 unk_01;
    /* 0x02 */ u8 posY;
    /* 0x03 */ char unk03[0x9];
    /* 0x0C */ unk_D_843C60C0 unk_0C[3];
} unk_D_843C60F0; // size >= 0x48

typedef struct unk_D_843C6148 {
    /* 0x00 */ u8 posX;
    /* 0x01 */ u8 unk_01;
    /* 0x02 */ u8 posY;
    /* 0x03 */ u8 unk_03;
    /* 0x04 */ u8 rotation;
    /* 0x05 */ u8 unk_05;
    /* 0x06 */ char unk06[0x2];
} unk_D_843C6148; // size <= 0x8

typedef struct unk_func_8438220C {
    /* 0x00 */ u8 posX;
    /* 0x01 */ char unk01[0x3];
    /* 0x04 */ unk_func_843794CC rotation[4];
    /* 0xB4 */ u8 unk_B4;
    /* 0xB8 */ s32 unk_B8;
} unk_func_8438220C; // size = 0xBC

typedef struct unk_func_8437F85C_arg3 {
    /* 0x00 */ u8 posX[3][3];
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
extern DioramaAnimData gCameraFovyPresetRandom[3];
extern DioramaAnimData gCameraFovyPresetSpecial[2];
extern DioramaAnimData gCameraPosB;
extern DioramaAnimData gCameraPosD;
extern DioramaAnimData gCameraPosC;
extern DioramaAnimData gCameraPosA;
extern DioramaAnimData gBattleCameraPresetTable[];
extern DioramaAnimData gBattleCameraPresetE;
extern DioramaAnimData gBattleCameraPresetTable2[];
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
extern ParticleEffectData gBattleAnimParticleDescriptors[86];
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

extern u8 gBattleMoveFailed;
extern u8 gBattleEffectType;
extern u8 gBattleUnusedFlag4;
extern u8 gBattleUnusedFlag5;
extern s32 gAnimTimer;
//extern unk_D_843C4E44 gIsBattleMode;
extern u8 gIsBattleMode;
extern u8 gAnimStateFlag;
extern u16 gBattleDamage;
extern PokemonAudioInfo* gBattleUser;
extern PokemonAudioInfo* gBattleTarget;


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
extern BattleInitState gBattleInitStruct;
extern Vec3f gCameraPosition;
extern BattleMessageBuffers* gBattleMessageQueues;
extern unk_D_843901B0 gCameraPreset;
extern unk_BattlePlayerEntity* gOpponentPlayer;
extern unk_BattlePlayerEntity* gCurrentPlayer;
extern s32 gTotalMoveCount;
extern s32 gCurrentMoveIndex;
extern s32 gInitialMoveIndex;
extern unk_D_84390240 gBattleScene;
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
extern u8* gBattleAnimAssetPointers[256];
extern s16 gMessageBuffer[0x10];
extern arg1_func_80019420* gMessageStringLists[40];



s32 Battle_StageGeoDispatchCallback(s32 arg0, GraphNode* arg1);
s32 Battle_StageLightAngleCallbackA(s32 arg0, PillarGlowParams* arg1);
s32 Battle_StageLightAngleCallbackB(s32 arg0, PillarGlowParams* arg1);
s32 Battle_StageMaterialTintCallback(s32 arg0, Fragment2_1GraphNode* arg1);
void Battle_SetStageTintColor(u8 arg0, u8 arg1, u8 arg2);
void Battle_SetStageScale(f32 arg0);
u16 Battle_TintTexel16(u16 arg0);
void Battle_DrawStageBackdrop(void);
void Battle_RenderActivePokemonThumbnail(GraphNode* arg0, FramebufferImage* arg1);
void Battle_DrawClippedTextureRect(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void Battle_DrawTexturedRectSegment(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u8* arg4, s32 arg5);
void Battle_FillActivePokemonThumbnail(GraphNode* arg0, FramebufferImage* arg1);
void Battle_ResetFaintBatches(void);
void Battle_UpdateFaintBatches(void);
void func_84300E78(void);
void func_84300E80(void);
s32 BattleScene_UpdateFrame(s32 arg0);
s32 BattleScene_UpdatePausedFrame(s32 arg0);
void Battle_UpdateCompletionGate(void);
s32 Battle_FrameCallback(s32 arg0);
void Battle_CompleteRosterOrder(u8* arg0, s32 arg1);
void Battle_SelectComRoster(void);
void BattleScene_InitializeParticipantPresentation(unk_D_800AE540_1194* arg0, ModelData* arg1);
void BattleScene_Init(Stage* arg0);
void func_84301A24(void);
s32 Battle_Main(s32 arg0, SessionContext* arg1);

void BattleScene_ClearStateTickCallbacks(void);
void BattleScene_QueueRowEffectList3(unk_BattlePlayerEntity* arg0, s32 arg1);
void BattleAnim_PlayMoveEffectScriptA(unk_BattlePlayerEntity* arg0, s32 arg1);
void BattleAnim_PlayMoveEffectScriptB(unk_BattlePlayerEntity* arg0, s32 arg1);
void BattleAnim_PlayMoveEffectEnd(unk_BattlePlayerEntity* arg0, s32 arg1);
void BattleScene_TickClearAnimRecordIfLoaded(unk_BattlePlayerEntity* arg0);
void BattleScene_TickStartRowAnimRecord(unk_BattlePlayerEntity* arg0);
void BattleScene_TickQueueRowEffectList3AtAnimEnd(unk_BattlePlayerEntity* arg0);
void BattleScene_ResetStateFrameCounter(unk_BattlePlayerEntity* arg0);
void BattleScene_ResetOpponentStateFrameCounter(unk_BattlePlayerEntity* arg0);
void BattleAnim_SetOverlayFlagForSpecialMoves(unk_BattlePlayerEntity* arg0);
void BattleAnim_ClearOverlayFlag(unk_BattlePlayerEntity* arg0);
s32 BattleAnim_IsAssetLoadBusy(unk_BattlePlayerEntity* arg0);
s32 BattleAnim_PollAssetLoadBusyFlags(unk_BattlePlayerEntity* arg0);
s32 BattleAnim_IsSessionBusy(unk_BattlePlayerEntity* arg0);
s32 BattleAnim_TryRegisterAssetTables(unk_BattlePlayerEntity* arg0);
void BattleScene_LoadMoveResourceList(unk_BattlePlayerEntity* arg0);
void BattleScene_LoadRowResourceList(unk_BattlePlayerEntity* arg0);
void BattleScene_ReloadMoveResourceList(unk_BattlePlayerEntity* arg0);
void BattleAnim_BeginSessionRequest(unk_BattlePlayerEntity* arg0);
void BattleAnim_BeginSessionRequestForActiveMon(unk_BattlePlayerEntity* arg0);
s32 BattleScene_FindU16InByteArray(u16 arg0, u8* arg1, s32 arg2);
void Battle_FilterUnusableMoves(unk_BattlePlayerEntity* arg0, u16 arg1, unk_D_84390010_94C* arg2, unk_D_84390010_94C* arg3);
void Battle_InitializeMoveUsabilityMask(unk_BattlePlayerEntity* arg0);
void Battle_DmaLoadAnimRecord(u8 arg0, u32 arg1);
void Battle_DmaLoadAnimRecordPair(s32 arg0, unk_D_84390010_94C* arg1, unk_D_84390010_94C* arg2);
void LoadPlayerAnimationData(unk_BattlePlayerEntity* arg0, s32 arg1);
void BattleScene_TickRow10CleanupAndEnterState18(unk_BattlePlayerEntity* arg0);
void BattleScene_EnterRow3StartMoveAnim(unk_BattlePlayerEntity* arg0);
void BattleScene_TickRow3PlayMoveEffectScript(unk_BattlePlayerEntity* arg0);
void BattleScene_TickRow3PostEffectCamera(unk_BattlePlayerEntity* arg0);
void BattleScene_TickRow3QueueEffectList6(unk_BattlePlayerEntity* arg0);
void AnimChannel_SetSubStateIfNeeded(unk_BattlePlayerEntity* arg0);
void BattleScene_EnterRow21StartAnimRecord0(unk_BattlePlayerEntity* arg0);
void BattleScene_TickRow21PlaySpeciesSound(unk_BattlePlayerEntity* arg0);
void BattleScene_EnterRow19StartMoveAnimMidFrame(unk_BattlePlayerEntity* arg0);
void BattleScene_TickRow19PlayMoveEffectScript(unk_BattlePlayerEntity* arg0);
void BattleScene_TickRow19PostEffectCamera(unk_BattlePlayerEntity* arg0);
void BattleScene_EnterRow4StartHitReactionAnim(unk_BattlePlayerEntity* arg0);
void BattleScene_TickPlayMoveEffectEnd(unk_BattlePlayerEntity* arg0);
void BattleScene_TickRow4PostEndCamera(unk_BattlePlayerEntity* arg0);
void BattleScene_EnterRow15StartAnimA80Seq30(unk_BattlePlayerEntity* arg0);
s32 BattleScene_IsOpponentRowCheckpointReached(unk_BattlePlayerEntity* arg0);
s32 BattleScene_IsRowZeroCheckpointReached(unk_BattlePlayerEntity* arg0);
void Pokemon_ResetAnimAndTrigger(unk_BattlePlayerEntity* arg0);
void BattleScene_EnterRowAnim166WithCry(unk_BattlePlayerEntity* arg0);
void BattleScene_TickRow1PlayOwnerCry(unk_BattlePlayerEntity* arg0);
void BattleScene_TickRow16PlayCryAndSpeciesSound(unk_BattlePlayerEntity* arg0);
void BattleScene_TickRow18PlayCryAndSpeciesSound(unk_BattlePlayerEntity* arg0);
void BattleScene_TickAssetLoadQueueRowEffectList3(unk_BattlePlayerEntity* arg0);
void Pokemon_HandleMoveHitSimple(unk_BattlePlayerEntity* arg0);
void BattleScene_TickRow20CleanupAndEnterState18(unk_BattlePlayerEntity* arg0);
void Pokemon_ClearTransformFlag(unk_BattlePlayerEntity* arg0);
void BattleScene_EnterRow8StartMappedMoveAnim(unk_BattlePlayerEntity* arg0);
void BattleScene_TickRow8PlayMoveEffectScriptB(unk_BattlePlayerEntity* arg0);
void BattleScene_EnterRow9SetEventTrack(unk_BattlePlayerEntity* arg0);
void BattleScene_EnterRow9QueueEffectList6(unk_BattlePlayerEntity* arg0);
void BattleScene_Row12Slot1CameraCleanup(unk_BattlePlayerEntity* arg0);
void BattleScene_Row13PlaySequences14And21(unk_BattlePlayerEntity* arg0);
void BattleScene_TickPlaySpeciesSequence33(unk_BattlePlayerEntity* arg0);
void BattleScene_TickQueueList3Selector2OrC(unk_BattlePlayerEntity* arg0);
void BattleScene_TickQueueList3Selector2OrCFromB10(unk_BattlePlayerEntity* arg0);
void UpdateAnimChannelForEntity(unk_BattlePlayerEntity* arg0);
void BattleScene_TickRow14PlayMoveEffectEnd(unk_BattlePlayerEntity* arg0);
s32 GetAnimStateResultCode(unk_BattlePlayerEntity* arg0);
void BattleScene_TickRow11QueueEffectList6(unk_BattlePlayerEntity* arg0);
void BattleScene_TickRow11PostEndCamera(unk_BattlePlayerEntity* arg0);
void BattleScene_StateCallbackNop(unk_BattlePlayerEntity* arg0);
void BattleScene_RegisterStateTickCallback(unk_BattlePlayerEntity* arg0, unk_D_84385384_func arg1);
void BattleScene_SetOpponentEventTrackA6(unk_BattlePlayerEntity* arg0);
void BattleScene_EnterStateRow(unk_BattlePlayerEntity* arg0, s32 arg1);
void BattleScene_TickStateCallbacks(void);
void Battle_ResetCryEventIfStruggle(unk_BattlePlayerEntity* arg0);
void BattleAnim_SetModelEventTrackFromRow(unk_BattlePlayerEntity* arg0, s32 arg1);
s32 BattleAnim_TrySetModelEventTrackFromRow(unk_BattlePlayerEntity* arg0, s32 arg1, s32 arg2);
void BattleAnim_SetModelEventTrackAndState(unk_BattlePlayerEntity* arg0, s32 arg1, s32 arg2);
s32 BattleScene_IsParticipantIncapacitated(unk_BattlePlayerEntity* arg0);
s32 BattleScene_IsRowWaitComplete(unk_BattlePlayerEntity* arg0, s32 arg1);
s32 BattleScene_IsRowWaitCompleteWithEventCount(unk_BattlePlayerEntity* arg0, s32 arg1);
s32 Battle_IsRowAnimationSettled(unk_BattlePlayerEntity* arg0, s32 arg1);
s32 BattleScene_IsMoveKeyedRowWaitComplete(unk_BattlePlayerEntity* arg0, s32 arg1);
s32 BattleScene_IsRowAnimWaitComplete(unk_BattlePlayerEntity* arg0, s32 arg1);
void MaybeTriggerSpecialAnimEffect(unk_BattlePlayerEntity* arg0);
void Battle_SetRuntimeFlags(unk_BattlePlayerEntity* arg0, u16 arg1);
s32 Battle_ClearRuntimeFlags(unk_BattlePlayerEntity* arg0, u16 arg1);
void BattleScene_ResetParticipantAnimationFlags(unk_BattlePlayerEntity* arg0);
void BattleScene_ResetBothParticipantsAnimationState(void);
void Battle_ClearOpponentHopFlagAndSyncMove(unk_BattlePlayerEntity* arg0);
void BattleScene_CleanupParticipantHideFlag(unk_BattlePlayerEntity* arg0);
void BattleScene_CleanupOpponentSpecialAnimFlag(unk_BattlePlayerEntity* arg0);
void BattleScene_CleanupOpponentAnimationFlags(unk_BattlePlayerEntity* arg0);
void BattleScene_CleanupParticipantEffectMode(unk_BattlePlayerEntity* arg0);
void BattleAnim_TickParticipantStatusAnimation(unk_BattlePlayerEntity* arg0);
void BattleAnim_TriggerStatusAfflictionCry(unk_BattlePlayerEntity* arg0);
void BattleScene_AllocateParticipantRecord(unk_D_800AE540_1194* arg0, s32 arg1);
void BattleScene_AllocateParticipants(unk_D_800AE540_1194* arg0);
void BattleScene_InitializeParticipantController(unk_BattlePlayerEntity* arg0);
void BattleScene_InitializeParticipantModel(unk_BattlePlayerEntity* arg0);
void BattleScene_InitializeParticipantOwnerModel(unk_BattlePlayerEntity* arg0);
void BattleScene_InitializeParticipantSecondaryModels(unk_BattlePlayerEntity* arg0, s32* arg1);
void BattleScene_InitializeParticipantAuxiliaryModel(unk_BattlePlayerEntity* arg0);
void BattleScene_InitializePresentation(unk_D_800AE540_1194* arg0);
void BattleScene_ResetParticipantAuxTransform(unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1, s32 arg2);
void BattleScene_InitializeRuntime(unk_D_800AE540_1194* arg0);
void BattleScene_UpdateParticipantsAndQueueEffects(unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1);
s32 BattleScene_DispatchLifecycle(s32 arg0, unk_D_800AE540_1194* arg1);
void AnimHandler_Idle(unk_BattlePlayerEntity* arg0);
void BattleScene_StateRow56EnterNop(unk_BattlePlayerEntity* arg0);
void BattleScene_StateRow5Slot3Nop(unk_BattlePlayerEntity* arg0);
void BattleScene_StateRow5Slot4Nop(unk_BattlePlayerEntity* arg0);
void BattleScene_StateRow5Slot5Nop(unk_BattlePlayerEntity* arg0);
void BattleScene_StateRow5Slot6Nop(unk_BattlePlayerEntity* arg0);
void BattleScene_StateRow7Slot5Nop(unk_BattlePlayerEntity* arg0);
void BattleScene_StateRow6Slot6Nop(unk_BattlePlayerEntity* arg0);
void BattleScene_StateRow6Slot5Nop(unk_BattlePlayerEntity* arg0);
void BattleScene_StateRow6Slot4Nop(unk_BattlePlayerEntity* arg0);
void BattleScene_StateRow6Slot3Nop(unk_BattlePlayerEntity* arg0);
void AnimHandler_SwitchIn(unk_BattlePlayerEntity* arg0);
void AnimHandler_SwitchOut(unk_BattlePlayerEntity* arg0, s32 arg1);
void AnimHandler_Victory(unk_BattlePlayerEntity* arg0, s32 arg1);
void BattleScene_StateRow7Slot4Nop(unk_BattlePlayerEntity* arg0);


void BattleScene_TriggerOwnerModelAnimation(unk_BattlePlayerEntity* arg0);
void BattleScene_ClearParticipantOwnerActiveFlag(unk_BattlePlayerEntity* arg0);
void BattleScene_SetParticipantOwnerActiveFlag(unk_BattlePlayerEntity* arg0);
void BattleScene_ClearBothOwnerActiveFlags(void);
void BattleScene_SetBothOwnerActiveFlags(void);
void BattleScene_SetOwnerPoseFlag(unk_D_84390010_728_0168* arg0);
void BattleScene_LoadOwnerCameraFramingConstants(unk_BattlePlayerEntity* arg0);
void BattleScene_SetupOwnerCameraFraming(unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1);
void func_84307630(void);
void BattleScene_ApplyOwnerCameraFraming(unk_BattlePlayerEntity* arg0);
void BattleScene_TickOwnerCameraFraming(unk_BattlePlayerEntity* arg0);
void BattleScene_InitializeOwnerCameraFraming(CameraStruct* arg0, unk_BattlePlayerEntity* arg1, CameraStruct* arg2, unk_BattlePlayerEntity* arg3);
void BattleScene_TickOwnerSlideIn(unk_BattlePlayerEntity* arg0, s32 arg1);
void BattleScene_TickOwnerSlideOut(unk_BattlePlayerEntity* arg0, s32 arg1);
void BattleScene_TickOwnerSlideAnimation(unk_BattlePlayerEntity* arg0);
void BattleScene_TickBothOwnerSlideAnimations(unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1);
s32 BattleScene_DispatchOwnerCameraLifecycle(s32 arg0, CameraStruct* arg1, CameraStruct* arg2);

s32 BattleScene_ByteArrayContains(u8 arg0, u8* arg1, s32 arg2);
PokemonData* BattleScene_GetParticipantSessionMon(unk_BattlePlayerEntity* arg0);
s32 BattleScene_IsPartnerPikachu(unk_BattlePlayerEntity* arg0);
f32 BattleScene_GetParticipantModelHeight(unk_BattlePlayerEntity* arg0);
f32 BattleScene_GetParticipantModelRadius(unk_BattlePlayerEntity* arg0);
f32 BattleScene_GetParticipantModelWidth(unk_BattlePlayerEntity* arg0);
f32 BattleScene_GetParticipantEyeHeight(unk_BattlePlayerEntity* arg0);
void BattleScene_PositionParticipantModel(unk_BattlePlayerEntity* arg0);
f32 BattleScene_GetParticipantModelXOffset(unk_BattlePlayerEntity* arg0);
void BattleScene_SetParticipantModelScale(unk_BattlePlayerEntity* arg0, f32 arg1);
s32 BattleScene_GetSelectedSideTeamSize(unk_BattlePlayerEntity* arg0);
s32 BattleScene_GetOpposingSelectedSideTeamSize(unk_BattlePlayerEntity* arg0);
s32 BattleScene_GetParticipantSideIndex(unk_BattlePlayerEntity* arg0);
u8 Battle_GetCameraShotFieldB(unk_BattlePlayerEntity* arg0);
u8 Battle_GetCameraShotFieldC(unk_BattlePlayerEntity* arg0);
s16 Battle_GetSideAnimTableFieldB(unk_BattlePlayerEntity* arg0);
s32 Battle_GetSideAnimTableFieldC(unk_BattlePlayerEntity* arg0);
f32 Battle_GetScaledHeightY(unk_BattlePlayerEntity* arg0);
f32 Battle_GetScaleRatio(unk_BattlePlayerEntity* arg0);
s16 BattleScene_GetActiveAnimRowId(unk_BattlePlayerEntity* arg0);
void BattleScene_GetParticipantModelBoundsScaled(unk_BattlePlayerEntity* arg0, Vec3f* arg1);
void BattleScene_GetParticipantModelRotation(unk_BattlePlayerEntity* arg0, Vec3s* arg1);
u16 Battle_GetActiveMonHp(unk_BattlePlayerEntity* arg0);
s16 BattleScene_GetParticipantFacingAngle(unk_BattlePlayerEntity* arg0);
s32 BattleAnim_GetSpeciesBySideIndex(s32 arg0);
s32 BattleAnim_GetOwnerSpecies(unk_BattlePlayerEntity* arg0);
u8 BattleScene_IsParticipantModelVisible(unk_BattlePlayerEntity* arg0);
void BattleScene_GetParticipantModelPosition(unk_BattlePlayerEntity* arg0, Vec3f* arg1);
void BattleAnim_GetOwnerDefaultAnchorPosition(unk_BattlePlayerEntity* arg0, Vec3f* arg1);
void BattleScene_ComputeParticipantModelOffset(unk_BattlePlayerEntity* arg0, Vec3f* arg1);
void BattleScene_GetParticipantAuxiliaryModelPosition(unk_BattlePlayerEntity* arg0, Vec3f* arg1);
f32 BattleAnim_GetOwnerModelHeight(unk_BattlePlayerEntity* arg0);
f32 BattleScene_GetParticipantModelRadiusScaled(unk_BattlePlayerEntity* arg0);
unk_D_86002F58_004_000_004* Battle_GetMoveEffectListEntry(unk_BattlePlayerEntity* arg0, s32 arg1);
s32 Battle_GetTrainerId(unk_BattlePlayerEntity* arg0, UNUSED s32 arg1);
char* Battle_GetActiveMoveName(unk_BattlePlayerEntity* arg0);
u8* Battle_GetActiveMonNickname(unk_BattlePlayerEntity* arg0);
void BattleScene_SetParticipantModelFlags(unk_BattlePlayerEntity* arg0, s32 arg1, s32 arg2);
void Battle_AdvanceSecondaryModelAnimIfFinished(unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1);
void Battle_ResetModelToIdleAnim(unk_BattlePlayerEntity* arg0);
void Battle_SetModelToStatusAnim(unk_BattlePlayerEntity* arg0);
void BattleScene_BindParticipantRosterForSide(unk_BattlePlayerEntity* arg0, s32 arg1);
void BattleScene_SetParticipantSelectedSide(unk_BattlePlayerEntity* arg0, s32 arg1);
void BattleScene_SetParticipantController(unk_BattlePlayerEntity* arg0, Controller* arg1);
void BattleScene_RebindParticipantToSide(unk_BattlePlayerEntity* arg0, s32 arg1);
s32 Battle_HasUsableSleepStatusTarget(unk_BattlePlayerEntity* arg0);
s32 Battle_HasUsableMajorStatusTarget(unk_BattlePlayerEntity* arg0);
s32 BattleScene_GetCombinedTeamSize(unk_BattlePlayerEntity* arg0);
u8 BattleScene_GetRosterTeamSize(unk_D_800AE540_0004* arg0);
s32 BattleScene_GetParticipantDisplayPlayerNumber(unk_BattlePlayerEntity* arg0);
void BattleScene_ReinitParticipantBodyModel(unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1, s32 arg2, s32 arg3);
void BattleScene_ReinitParticipantOwnerModel(unk_BattlePlayerEntity* arg0, unk_D_84390010_728* arg1, s16 arg2);
void BattleScene_ReinitParticipantSecondaryModels(unk_BattlePlayerEntity* arg0, s16 arg1);
void Battle_ResetEventTrack(unk_BattlePlayerEntity* arg0);
void Battle_LoadOwnerModelForSpecies(unk_BattlePlayerEntity* arg0);
void Battle_LoadOwnerModelForSwitchIn(unk_BattlePlayerEntity* arg0);
void Battle_ResetOwnerModelToNeutralPlaceholder(unk_BattlePlayerEntity* arg0);
void Battle_ReloadNeutralPlaceholderModel(unk_BattlePlayerEntity* arg0);
void Battle_ReloadModelForActiveMove(unk_BattlePlayerEntity* arg0);


void BattleAnim_InitSwayOffset(unk_BattlePlayerEntity* arg0, f32 arg1, s16 arg2);
void BattleAnim_UpdateSwayPhysicsToOwner(unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1, f32 arg2, f32 arg3, s32 arg4);
void BattleAnim_UpdateSwayPhysicsToTarget(UNUSED unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1, f32 arg2, f32 arg3, s32 arg4, s32 arg5);
void BattleScene_HideParticipantSecondaryModels(unk_BattlePlayerEntity* arg0);
void BattleScene_ShowSecondaryModelsAtMainTransform(unk_BattlePlayerEntity* arg0);
void BattleScene_UpdateSecondaryModelOrbit(unk_BattlePlayerEntity* arg0);
void BattleScene_ShowSecondaryModelsAtMainPose(unk_BattlePlayerEntity* arg0);
s32 BattleScene_ShrinkSecondaryModelsToScale(unk_BattlePlayerEntity* arg0);
void BattleScene_ShowSecondaryModelsStaggeredFrame(unk_BattlePlayerEntity* arg0);
void BattleScene_UpdateSecondaryModelTrailPosition(unk_BattlePlayerEntity* arg0, s16 arg1);
void BattleScene_ResetParticipantModelFlags(unk_BattlePlayerEntity* arg0);
void BattleAnim_StatusIdleCase1Sub0(UNUSED unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1);
void BattleAnim_StatusIdleCase1Sub1(unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1);
void BattleAnim_StatusIdleCase1(unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1);
void BattleAnim_StatusIdleCase2Sub0(UNUSED unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1);
void BattleAnim_StatusIdleCase2Sub1(unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1);
void BattleAnim_StatusIdleCase2(unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1);
void BattleAnim_StatusIdleCase3Sub0(UNUSED unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1);
void BattleAnim_StatusIdleCase3Sub1(unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1);
void BattleAnim_StatusIdleCase3(unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1);
void BattleAnim_StatusIdleCase14Sub0(UNUSED unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1);
void BattleAnim_StatusIdleCase14Sub1(unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1);
void BattleAnim_StatusIdleCase14Sub2(UNUSED unk_BattlePlayerEntity* arg0, UNUSED unk_BattlePlayerEntity* arg1);
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
void BattleAnim_UpdateOwnerStatusIdleAnimation(s32 arg0);
void BattleAnim_SetOwnerSecondaryStatusFlags(unk_BattlePlayerEntity* arg0, u8 arg1, u8 arg2);
void BattleAnim_ClearOwnerSecondaryStatusFlags(unk_BattlePlayerEntity* arg0);
void BattleAnim_InitSecondarySwayOffset(unk_BattlePlayerEntity* arg0, f32 arg1, s16 arg2);
void BattleAnim_UpdateSecondarySwayPhysics(unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1, f32 arg2, f32 arg3, s32 arg4);
void BattleAnim_SecondaryStatusCaseBSub0(unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1);
void BattleAnim_SecondaryStatusCaseBSub1(unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1);
void BattleAnim_SecondaryStatusCaseB(unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1);
void BattleAnim_SecondaryStatusDefault(unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1);
void BattleAnim_UpdateOwnerSecondaryStatusAnimation(s32 arg0);


void BattleAnim_CalculateDistanceAngles(Vec3f* arg0, Vec3f* arg1, f32* arg2, s16* arg3, s16* arg4);
Vec3f* BattleAnim_Vec3fSetZero(Vec3f* arg0);
Vec3f* BattleAnim_Vec3fOffsetByPolarXZ(Vec3f* arg0, Vec3f* arg1, f32 arg2, s16 arg3);
void BattleAnim_Vec3fSetPolarXZ(Vec3f* arg0, f32 arg1, s16 arg2);
Vec3f* BattleAnim_Vec3fCopy(Vec3f* arg0, Vec3f* arg1);
Vec3s* BattleAnim_Vec3sCopy(Vec3s* arg0, Vec3s* arg1);
Vec3f* BattleAnim_Vec3fScaleComponents(Vec3f* arg0, f32 arg1, f32 arg2, f32 arg3);
s16 BattleAnim_Atan2sFromPoints(f32 arg0, f32 arg1, f32 arg2, f32 arg3);
f32 BattleAnim_Vec3fDistance(Vec3f arg0, Vec3f arg1);
f32 BattleAnim_Distance2D(f32 arg0, f32 arg1, f32 arg2, f32 arg3);
s32 BattleAnim_RandomIntWithWarmup(f32 arg0);
u16 BattleAnim_RandomRange(s32 arg0);
s32 BattleAnim_StepToS16(s16* arg0, s16 arg1, s16 arg2);
s32 BattleAnim_StepToS16VariableRate(s16* arg0, s16 arg1, f32 arg2);
void BattleAnim_ApproachF(f32* arg0, f32 arg1, f32 arg2);
void BattleAnim_ApproachS16(s16* arg0, s16 arg1, s16 arg2);
void BattleAnim_ApproachU16(u16* arg0, u16 arg1, s16 arg2);
void Battle_ComputeSplineWeightsVariantA(f32* arg0, f32 arg1);
void Battle_ComputeSplineWeightsVariantB(f32* arg0, f32 arg1);
void Battle_ComputeSplineWeightsVariantC(f32* arg0, f32 arg1);
void Battle_ComputeSplineWeightsVariantD(f32* arg0, f32 arg1);
void Battle_ComputeSplineWeightsVariantE(f32* arg0, f32 arg1);


void BattleScene_InitializePresentationTimers(void);
void BattleScene_QuantizePresentationTimer(void);
s32 BattleScene_TickPresentationTimer(void);
s32 BattleScene_IsPresentationCountdownComplete(void);
s32 Battle_ClassifyHpTier(s32 arg0, s32 arg1);
s32 BattleScene_DetermineWinner(void);
s32 BattleScene_UpdateResultPresentation(void);
s32 BattleScene_IsActionSelectionTimerExpired(void);
void BattleScene_ResetActionSelectionTimer(void);
s32 BattleScene_TickActionSelectionTimers(void);
void BattleScene_ResetActionSelectionTimers(void);
s32 BattleScene_ApplyForcedActionDelay(unk_BattlePlayerEntity* arg0);
void BattleScene_SyncActiveHpToPartyState(void);
s32 BattleScene_SelectFallbackWhenNoUsableMoves(unk_BattlePlayerEntity* arg0);
s32 BattleScene_IsMoveUnavailable(unk_BattlePlayerEntity* arg0, s32 arg1);
void BattleScene_AutoSelectAvailableMove(unk_BattlePlayerEntity* arg0);
void BattleScene_AutoSelectReplacementMon(unk_BattlePlayerEntity* arg0);
void BattleScene_SelectActiveController(unk_BattlePlayerEntity* arg0);
void BattleScene_HandleActionSelectionCancel(s32 arg0);
void Battle_InitializeActiveRuntimeState(void);
s32 BattleScene_CpuHasNoUsableMoves(unk_BattlePlayerEntity* arg0);
s32 BattleScene_WaitForCpuChoice(unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1);
void BattleScene_CompleteCpuForcedAction(unk_BattlePlayerEntity* arg0, UNUSED unk_BattlePlayerEntity* arg1);
void BattleScene_CompleteCpuMoveAction(unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1);
void BattleScene_ApplyCpuChoice(unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1);
s32 BattleScene_ApplyCpuSwitchChoice(unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1);
s32 BattleScene_CollectCpuAction(unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1);
void BattleScene_ForfeitPrompt(unk_BattlePlayerEntity* arg0);
void BattleScene_CommitPlayerSwitchAction(unk_BattlePlayerEntity* arg0);
s32 BattleScene_ValidateSelectedPartyMember(unk_BattlePlayerEntity* arg0);
void BattleScene_QueuePartySelectionConfirmMessage(unk_BattlePlayerEntity* arg0);
void BattleScene_AssignActiveCoopController(unk_BattlePlayerEntity* arg0, s32 arg1);
void BattleScene_HandlePartySlotCursorInput(unk_BattlePlayerEntity* arg0, Controller* arg1);
void BattleScene_HandlePlayerPartySelection(unk_BattlePlayerEntity* arg0);
void BattleScene_CommitSelectedMoveAction(unk_BattlePlayerEntity* arg0);
s32 BattleScene_HandleNoUsableMoveSelection(unk_BattlePlayerEntity* arg0);
s32 BattleScene_ValidateSelectedMove(unk_BattlePlayerEntity* arg0);
void BattleScene_SelectMoveFromButtons(unk_BattlePlayerEntity* arg0);
void BattleScene_HandlePlayerMoveSelection(unk_BattlePlayerEntity* arg0);
s32 BattleScene_HandlePlayerMoveSelectionLocked(unk_BattlePlayerEntity* arg0, UNUSED Controller* arg1);
void BattleScene_ConfirmForcedMoveRepeat(unk_BattlePlayerEntity* arg0);
void BattleScene_PollActionMenuRequestButtons(unk_BattlePlayerEntity* arg0);
s32 BattleScene_HandlePlayerActionInput(unk_BattlePlayerEntity* arg0);
s32 BattleScene_HandlePlayerForcedActionState(unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1);
void BattleScene_ShowParticipantOwnerAndSecondaryModels(void);
void BattleScene_HideParticipantOwnerAndSecondaryModels(void);
void BattleScene_AdvanceAttractInputScript(void);
void BattleScene_CheckForcedActionCondition(unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1);
void BattleScene_TickAttractModeInput(void);
void BattleScene_CollectPlayerAction(unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1);
void BattleScene_CollectActions(void);
void BattleScene_UpdateActionCollection(void);
void BattleScene_UpdateActionSelectPhase(void);


void BattleHud_InitEmpty(void);
void BattleHud_DrawTranslucentShadowRect(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void BattleHud_DrawGradientRect(s32 arg0, s32 arg1, s32 arg2, s32 arg3, Color_RGB8* arg4, Color_RGB8* arg5);
void Battle_DrawGradientRectWrapper(s32 arg0, s32 arg1, s32 arg2, s32 arg3, Color_RGB8* arg4, Color_RGB8* arg5);
void func_84310360(void);
void BattleHud_DrawHpBar(s32 arg0, s32 arg1, f32 arg2, s32 arg3);
void BattleHud_InitEmpty5(void);
void BattleHud_DrawLevelNumber(s32 arg0, s32 arg1, s32 arg2);
void BattleHud_DrawHpFractionText(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void BattleHud_DrawSpeciesNameLabel(s16 arg0, s16 arg1, s32 arg2, char* arg3, s32 arg4);
void BattleHud_DrawSpeciesNameLabelBlink(s16 arg0, s16 arg1, s32 arg2, u8* arg3, s32 arg4, s32 arg5);
void BattleHud_DrawSpeciesNameLabelAuto(unk_BattlePlayerEntity* arg0, unk_D_800AE540_0004* arg1, s16 arg2, s16 arg3, s32 arg4, u16 arg5, s32 arg6);
void BattleHud_DrawMonInfoPanel(unk_BattlePlayerEntity* arg0, PokemonData* arg1, unk_D_84385790* arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9, s32 argA);
s32 BattleHud_DrawBorderTile(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u8* arg4);
void func_84311420(void);
void BattleHud_DrawBoxBorder(s16 arg0, s16 arg1, s16 arg2, s16 arg3);
void BattleHud_DrawParticipantTimer(s16 arg0, s16 arg1);
void BattleHud_DrawBattleTimer(s16 arg0, s16 arg1);
void BattleHud_DrawPartyBallRow(unk_BattlePlayerEntity* arg0, s16 arg1, s16 arg2);
void BattleHud_DrawMonStatusBoxPlayer(unk_BattlePlayerEntity* arg0, s16 arg1, s16 arg2, u16 arg3, s32 arg4);
void BattleHud_DrawMonStatusBoxOpponent(unk_BattlePlayerEntity* arg0, s16 arg1, s16 arg2, u16 arg3, s32 arg4);
void BattleHud_DrawThreeOptionLabelBar(unk_BattlePlayerEntity* arg0, s16 arg1, s16 arg2, s32 arg3);
void BattleHud_DrawTwoOptionLabelBar(unk_BattlePlayerEntity* arg0, s16 arg1, s16 arg2, s32 arg3);
void BattleHud_DrawOneOptionLabelBar(unk_BattlePlayerEntity* arg0, s16 arg1, s16 arg2, s32 arg3);
void Battle_DrawRightAlignedText(s32 arg0, s32 arg1, char* arg2);
s32 BattleHud_DrawMovePpTextLTR(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 BattleHud_DrawMovePpTextRTL(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void BattleHud_DrawMoveSelectMenu(unk_BattlePlayerEntity* arg0, s16 arg1, s16 arg2, s32 arg3);
void BattleHud_DrawForfeitConfirmDialog(s16 arg0, s16 arg1, s16 arg2, s32 arg3);
void BattleHud_DrawPlainText(s16 arg0, s16 arg1, char* arg2);
void BattleHud_DrawDoublesRosterRow(unk_BattlePlayerEntity* arg0, unk_D_800AE540_0004* arg1, PokemonData* arg2, s32 arg3, s32 arg4, s32 arg5);
void BattleHud_DrawPartyRosterRow(unk_BattlePlayerEntity* arg0, unk_D_800AE540_0004* arg1, PokemonData* arg2, s32 arg3, s32 arg4, s32 arg5);
void BattleHud_DrawTeamStatusList(unk_BattlePlayerEntity* arg0, unk_D_800AE540_0004* arg1, s16 arg2, s16 arg3, s32 arg4);
void BattleHud_DrawDoublesTeamStatusList(unk_BattlePlayerEntity* arg0, s16 arg1, s16 arg2, s32 arg3);
void BattleHud_DrawCompactMonStatusBox(unk_BattlePlayerEntity* arg0, s16 arg1, s16 arg2, s32 arg3);
void BattleHud_DrawMessageBox(s32 arg0, s16 arg1, s16 arg2, char* arg3);
s32 Battle_DrawTextIfNonEmpty(char* arg0, s16 arg1, s16 arg2);
void BattleHud_DrawExpandingCaptionBox(unk_D_843901A0_4C8* arg0, s16 arg1, s16 arg2, Vec3f arg3);
void BattleHud_InitCaptionBoxPopup(unk_D_843901A0_4C8* arg0, s16 arg1, s16 arg2);
s32 BattleHud_UpdateCaptionBoxPopup(unk_D_843901A0_4C8* arg0, s16 arg1, s16 arg2);
void BattleHud_DrawExpandingCaptionBoxBlack(unk_D_843901A0_4C8* arg0, s16 arg1, s16 arg2, Vec3f arg3);
void BattleHud_InitCaptionBoxPopupBlack(unk_D_843901A0_4C8* arg0, s16 arg1, s16 arg2);
s32 BattleHud_UpdateCaptionBoxPopupBlack(unk_D_843901A0_4C8* arg0, s16 arg1, s16 arg2);
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


void Battle_ClearAllMessageQueues(void);
void Battle_ClearMessageCursor(void);
void SimpleStringFormat(s8* arg0, s8* arg1, ...);
void Battle_QueueMessage(s8* arg0, s8 arg1);
void Battle_QueueStatusText(char* arg0, s32 arg1);
void func_84317B38(void);
void Battle_DrawCompactStatusBoxesIfVisible(void);
void Battle_QueueMoveCategoryUsedMessage(void);
void Battle_QueueMoveCategoryMessage(void);
void Battle_QueueMetronomeMoveMessage(void);
void BattleBox_Open(s32 arg0);
void BattleBox_Close(void);
void BattleBox_PlayTextBlip(s8* arg0);
void BattleBox_DrawMessage(unk_D_843901A0_4C8* arg0, s16 arg1, s16 arg2);
s32 BattleBox_SelectMessage(unk_D_843901A0_4C8* arg0);
void BattleBox_Update(s16 arg0, s16 arg1);
void BattleScene_ClearParticipantMessageBuffer(unk_BattlePlayerEntity* arg0);
void BattleScene_BuildParticipantMessage(unk_BattlePlayerEntity* arg0, s32 arg1);
void BattleScene_RevealParticipantMessageChars(unk_BattlePlayerEntity* arg0);
void BattleScene_TickHudTimers(void);
void Battle_InitMessageQueues(void);
void BattleScene_ResetMessageQueue(void);
void Battle_RenderHud(void);


s32 BattleScene_AreBothParticipantModelsCompact(void);
s32 BattleScene_SkipIntroIfFainted(UNUSED unk_BattlePlayerEntity* arg0, CameraStruct* arg1);
s32 BattleScene_IsEitherActivePokemonFainted(UNUSED unk_BattlePlayerEntity* arg0, UNUSED CameraStruct* arg1);
void BattleScene_IntroCameraStep0(CameraStruct* arg0);
void BattleScene_IntroCameraStep2(CameraStruct* arg0);
void BattleScene_IntroCameraStep4Or6(CameraStruct* arg0, s32 arg1);
void BattleScene_IntroCameraStep8Or10(CameraStruct* arg0, s32 arg1);
void BattleScene_IntroCameraStep12Or14(CameraStruct* arg0, s32 arg1);
void BattleScene_IntroCameraStep16(CameraStruct* arg0);
void BattleScene_IntroCameraStep18(CameraStruct* arg0);
void BattleScene_IntroCameraStep20(CameraStruct* arg0);
void BattleScene_IntroCameraStep22Or24(CameraStruct* arg0, s32 arg1);
void BattleScene_SelectNextIntroCameraShot(CameraStruct* arg0);
void BattleScene_IntroCameraRollStep(CameraStruct* arg0);
void BattleScene_IntroCameraRollStepNoFov(CameraStruct* arg0);
void BattleScene_IntroCameraAnimationHoldStep(CameraStruct* arg0);
void BattleScene_IntroCameraPresetHoldStep(CameraStruct* arg0);
void BattleScene_IntroCameraWideHoldStep(CameraStruct* arg0);
void BattleScene_IntroCameraHeightShotSwapStep(CameraStruct* arg0);
void BattleScene_IntroCameraHeightShotStep(CameraStruct* arg0);
void BattleScene_IntroCameraTimedHoldStep(CameraStruct* arg0);
void BattleScene_IntroCameraFinalHoldStep(CameraStruct* arg0);
void BattleScene_UpdateIntroCameraSequence(CameraStruct* arg0);


f32 BattleScene_ScaleCameraDistance(unk_BattlePlayerEntity* arg0, f32 arg1, f32 arg2);
s32 BattleScene_AdvanceCameraSubstepCounter(s32 arg0);
s32 BattleScene_AdvanceCameraFrameCounter(s32 arg0);
s32 BattleScene_AdvanceCameraFrameCounterUntil(s32 arg0);
s32 BattleScene_IsCameraFrameCounterAtLeast(s32 arg0);
void BattleScene_SetActivePokemonIndex(s32 arg0);
void BattleScene_ResetCameraFrameCounter(void);
void BattleScene_ResetCameraSubstepCounter(void);
void BattleScene_SetCameraAtAndEyeFromAngles(CameraStruct* arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, s16 arg5, s16 arg6);
void BattleScene_GetOwnerCameraAnchor(unk_BattlePlayerEntity* arg0, Vec3f* arg1);
void BattleScene_GetOwnerBoneOrDefaultAnchor(unk_BattlePlayerEntity* arg0, Vec3f* arg1, s32 arg2);
void BattleScene_SetCameraModeAndStep(s32 arg0, s32 arg1);
void BattleScene_SetCameraClipPlanes(CameraStruct* arg0, f32 arg1, f32 arg2);
void BattleScene_SetCameraSubstate(s32 arg0, u16 arg1);
void BattleScene_ApplyCameraPhaseDefaults(void);
void BattleScene_SetDamageShakeAmplitude(unk_BattlePlayerEntity* arg0);
void BattleScene_ApplyCameraShake(CameraStruct* arg0);
void BattleScene_StartCameraShake(UNUSED unk_BattlePlayerEntity* arg0);
s32 BattleScene_IsCameraAngleSettled(s16 arg0, s16 arg1);
s32 BattleScene_ApproachCameraRoll(CameraStruct* arg0, s16 arg1, s16 arg2);
s32 BattleScene_ApproachCameraRollNoEyeUpdate(UNUSED CameraStruct* arg0, s16 arg1, s16 arg2);
void BattleScene_SetCameraAnglesAndDistance(s16 arg0, s16 arg1, f32 arg2);
void BattleScene_SetCameraSendOutShot(CameraStruct* arg0, s32 arg1);
void BattleScene_ClampCameraEyeFloor(CameraStruct* arg0);
void BattleScene_UpdateCameraModelOffset(unk_BattlePlayerEntity* arg0, CameraStruct* arg1);
void BattleScene_ClearCameraOffsetVectors(void);
void BattleScene_SetCameraAtFromAnchor(unk_BattlePlayerEntity* arg0, CameraStruct* arg1, Vec3f arg2, s16 arg3, s16 arg4, f32 arg5, f32 arg6);
void BattleScene_SetCameraAtFromPosition(CameraStruct* arg0, Vec3f arg1, s16 arg2, s16 arg3, f32 arg4, f32 arg5);
void BattleScene_SetCameraEyeFromPosition(CameraStruct* arg0, Vec3f arg1, s16 arg2, s16 arg3, f32 arg4, f32 arg5);
void BattleScene_SetCameraEyeFromAt(CameraStruct* arg0, s16 arg1, s16 arg2, f32 arg3, f32 arg4);
void BattleScene_SetCameraEyeAndStoreAngles(CameraStruct* arg0, Vec3f arg1, s16 arg2, s16 arg3, f32 arg4, f32 arg5);
void BattleScene_SetCameraEyeAndStoreAnglesFromAt(CameraStruct* arg0, s16 arg1, s16 arg2, f32 arg3, f32 arg4);
void BattleScene_CameraHelperNop(UNUSED CameraStruct* arg0);
void BattleScene_SnapFloatPair(f32* arg0, f32* arg1);
void BattleScene_ApplyOwnerFramingAdjustments(CameraStruct* arg0, unk_BattlePlayerEntity* arg1, UNUSED f32 arg2);
void BattleScene_RecomputeCameraDistance(CameraStruct* arg0, unk_BattlePlayerEntity* arg1);
void BattleScene_ReframeAndRecomputeDistance(CameraStruct* arg0, unk_BattlePlayerEntity* arg1);
void BattleScene_ReframeAndRecomputeDistanceForSwitch(CameraStruct* arg0, unk_BattlePlayerEntity* arg1);
void BattleScene_ApplyOwnerFramingOnly(CameraStruct* arg0, unk_BattlePlayerEntity* arg1);
void BattleScene_UpdateCameraTargetFromOwner(CameraStruct* arg0, unk_BattlePlayerEntity* arg1);
s32 BattleScene_FrameCamera(CameraStruct* arg0, unk_BattlePlayerEntity* arg1);
void BattleScene_ApproachCameraTargetFromOwner(CameraStruct* arg0, unk_BattlePlayerEntity* arg1);
void BattleScene_UpdateCameraVerticalFraming(CameraStruct* arg0, unk_BattlePlayerEntity* arg1);
void BattleScene_RecenterCameraOnOwner(CameraStruct* arg0, unk_BattlePlayerEntity* arg1);
void BattleScene_ApproachCameraTarget(CameraStruct* arg0, unk_BattlePlayerEntity* arg1, UNUSED s32 arg2);
void BattleScene_ApproachCameraZoom(CameraStruct* arg0, unk_BattlePlayerEntity* arg1);
s32 BattleScene_ApproachCloseCameraShot(CameraStruct* arg0, unk_BattlePlayerEntity* arg1);
s32 BattleScene_AnimateCameraPreset(CameraStruct* arg0, unk_BattlePlayerEntity* arg1, s32 arg2, s32 arg3);
s32 BattleScene_AnimateCameraPresetToOwner(CameraStruct* arg0, unk_BattlePlayerEntity* arg1);
void BattleScene_CameraPresetNop(UNUSED CameraStruct* arg0);
void BattleScene_ApplyCameraPreset(CameraStruct* arg0, unk_BattlePlayerEntity* arg1, s32 arg2);
void BattleScene_SetCameraPresetAtAngles(s16 arg0, s16 arg1, s16 arg2, s16 arg3);
void BattleScene_SetCameraPresetAtDistances(f32 arg0, f32 arg1);
void BattleScene_SetCameraPresetEyeAngles(s16 arg0, s16 arg1, s16 arg2, s16 arg3);
void BattleScene_SetCameraPresetEyeDistances(f32 arg0, f32 arg1);
void BattleScene_SetCameraPresetSmoothing(f32 arg0, f32 arg1);
void BattleScene_LoadCameraPreset(DioramaAnimData* arg0, CameraStruct* arg1, unk_BattlePlayerEntity* arg2);
void BattleScene_LoadCameraPresetUnscaled(DioramaAnimData* arg0, CameraStruct* arg1);
s32 BattleScene_AnimateCameraIntro(CameraStruct* arg0, unk_BattlePlayerEntity* arg1);
s32 BattleScene_AreActivePokemonHeightsSeparated(UNUSED CameraStruct* arg0);
void BattleScene_SetCameraActivePokemonHeightShot(CameraStruct* arg0, s32 arg1);
s32 BattleScene_ApproachCameraActivePokemonHeightShot(CameraStruct* arg0, s32 arg1);
void BattleScene_SetCameraOwnerShot(CameraStruct* arg0, unk_BattlePlayerEntity* arg1);
void BattleScene_SetCameraOwnerWideShot(CameraStruct* arg0, unk_BattlePlayerEntity* arg1);
void BattleScene_SetCameraPresetClose(CameraStruct* arg0, unk_BattlePlayerEntity* arg1, s32 arg2);
void BattleScene_SetCameraPresetAngledClose(CameraStruct* arg0, unk_BattlePlayerEntity* arg1, s32 arg2);
void BattleScene_SetCameraPresetOffsetClose(CameraStruct* arg0, unk_BattlePlayerEntity* arg1, s32 arg2);
void BattleScene_SetCameraPresetLowClose(CameraStruct* arg0, unk_BattlePlayerEntity* arg1, s32 arg2);
void BattleScene_SetCameraPresetWide(CameraStruct* arg0, unk_BattlePlayerEntity* arg1, s32 arg2);
void BattleScene_SetCameraPresetWideStatic(CameraStruct* arg0, unk_BattlePlayerEntity* arg1, s32 arg2);
void BattleScene_SetCameraPresetFromTable(CameraStruct* arg0, unk_BattlePlayerEntity* arg1, s32 arg2, s32 arg3);
void BattleScene_CameraShotTargetStandard(CameraStruct* arg0, unk_BattlePlayerEntity* arg1);
void BattleScene_CameraShotTargetAngled(CameraStruct* arg0, unk_BattlePlayerEntity* arg1);
void BattleScene_CameraShotTargetHigh(CameraStruct* arg0, unk_BattlePlayerEntity* arg1);
void BattleScene_CameraShotTargetLow(CameraStruct* arg0, unk_BattlePlayerEntity* arg1);
void BattleScene_CameraShotTargetClose(CameraStruct* arg0, unk_BattlePlayerEntity* arg1);
void BattleScene_SetCameraFollowPresetNear(CameraStruct* arg0, unk_BattlePlayerEntity* arg1, s32 arg2);
void BattleScene_SetCameraOwnerStandardShot(CameraStruct* arg0, unk_BattlePlayerEntity* arg1);
void BattleScene_SelectCameraPreset(unk_BattlePlayerEntity* arg0, CameraStruct* arg1, s32 arg2, s32 arg3);
void BattleScene_SelectCameraFollowPreset(unk_BattlePlayerEntity* arg0, CameraStruct* arg1, s32 arg2);
void BattleScene_SelectCameraShot(unk_BattlePlayerEntity* arg0, CameraStruct* arg1, s32 arg2);


void BattleScene_ApplyModelAnimationSlot5A(unk_BattlePlayerEntity* arg0);
void BattleScene_ResetAnimationStep(void);
s32 BattleScene_AdvanceOwnerAnimation(unk_BattlePlayerEntity* arg0);
s32 BattleScene_AdvanceOwnerAnimation98(unk_BattlePlayerEntity* arg0);
s32 BattleScene_AdvanceOwnerAnimationAndClearFlags(unk_BattlePlayerEntity* arg0);
s32 BattleScene_AdvanceDoublesOwnerAnimation(unk_BattlePlayerEntity* arg0);
s32 BattleScene_AdvanceBothOwnerAnimations(void);
void BattleScene_ClearInactiveOwnerAnimationFlags(void);
void func_8431FCC4(void);
s32 BattleScene_AnimateDisplayedHpToRuntime(unk_BattlePlayerEntity* arg0);
void BattleScene_ClearPhaseFlag(void);
void BattleScene_SetPhaseFlag(void);
void BattleScene_SetPhase(UNUSED CameraStruct* arg0, s32 arg1);
void BattleScene_SaveCameraFov(CameraStruct* arg0);
void BattleScene_ResetCameraFov(CameraStruct* arg0);
s32 BattleScene_GetAnimationTimingField0D(unk_BattlePlayerEntity* arg0);
s32 BattleScene_GetMappedAnimationTimingField0D(unk_BattlePlayerEntity* arg0);
s32 BattleScene_GetAnimationTimingField0E(unk_BattlePlayerEntity* arg0);
s32 BattleScene_GetMappedAnimationTimingField0E(unk_BattlePlayerEntity* arg0);
s32 BattleScene_GetCameraShotDuration(unk_BattlePlayerEntity* arg0);
void DetermineTurnOrder(void);
void BattleScene_InitializeSwitchActions(void);
s32 BattleScene_PrepareReplacementTransition(void);
void BattleScene_BeginBattlePhase(void);
s32 BattleScene_TransitionToPhaseFull(s32 arg0);
s32 BattleScene_TransitionToPhase(s32 arg0);
s32 BattleScene_TransitionToPhaseDuplicate(s32 arg0);
void BattleScene_SwitchActiveSideAndSetPhase(CameraStruct* arg0);
void Battle_ActSecondAttacker(u8 arg0);
void BattleScene_PhaseResumeSaved(void);
void BattleScene_CleanupActionAndAdvance(void);
s32 BattleScene_HandleFaintStatusCompletion(void);
void BattleScene_CompleteActionPhase(void);
void BattleScene_ResolveDisplayedHpCompletion(CameraStruct* arg0);
void BattleScene_UpdateDisplayedHpAndTransition(CameraStruct* arg0);
void BattleScene_WaitForDisplayedHpAnimations(CameraStruct* arg0);
s32 BattleScene_ActionPresentationTransitionCheck(void);
s32 BattleScene_ActionPresentationCleanupCheck(void);
s32 BattleScene_PrepareResidualStatusPresentation(void);
void BattleScene_UpdateActiveOwnerPointers(void);
void BattleScene_InitializeBattlePresentation(CameraStruct* arg0);
void BattleScene_SendOutPresentationFinalize(CameraStruct* arg0);
s32 BattleScene_ResetOwnerStatusPresentation(unk_BattlePlayerEntity* arg0);
void BattleScene_AdvanceSendOutPreparation(CameraStruct* arg0);
void BattleScene_AdvanceSendOutCamera(CameraStruct* arg0);
void BattleScene_AdvanceSendOutCameraClose(CameraStruct* arg0);
void BattleScene_FinishSendOutCameraClose(CameraStruct* arg0);
void BattleScene_CompleteSendOutPresentation(CameraStruct* arg0);
void UnusedBattleStateHandler(UNUSED CameraStruct* arg0);
void BattleScene_SetupSendOutOwnerShot(CameraStruct* arg0);
void BattleScene_CompleteSendOutCameraFade(UNUSED CameraStruct* arg0);
void BattleScene_CompleteSendOutExtendedFade(UNUSED CameraStruct* arg0);
void BattleScene_AdvanceSendOutFollowupCamera(CameraStruct* arg0);
void BattleScene_PhaseSendOut(CameraStruct* arg0);
void BattleScene_CompleteSendOutFollowup(UNUSED CameraStruct* arg0);
void BattleScene_PhaseSendOutAfterFaint(CameraStruct* arg0);
void BattleScene_ResetOwnerPresentationFlags(unk_BattlePlayerEntity* arg0);
void BattleScene_InitializeIntroCamera(CameraStruct* arg0);
void BattleScene_AdvanceIntroCamera(CameraStruct* arg0);
void BattleScene_PhaseIntro(CameraStruct* arg0);
void BattleScene_SetMonMoveResourceFlag(unk_BattlePlayerEntity* arg0);
void BattleScene_PrepareMoveResourcePresentation(UNUSED CameraStruct* arg0);
void BattleScene_SelectActionCameraPreset(CameraStruct* arg0);
s32 BattleScene_AdvanceActionPresentationSetup(CameraStruct* arg0);
void BattleScene_ActionSetupCameraStep(CameraStruct* arg0);
void BattleScene_RefreshActionCameraPreset(CameraStruct* arg0);
void BattleScene_SelectActionCameraPresetFromTiming(CameraStruct* arg0, s32 arg1);
s32 BattleScene_ApplyActionCameraMode(CameraStruct* arg0, s32 arg1);
void BattleScene_CleanupActionPresentation(UNUSED CameraStruct* arg0);
s32 BattleScene_WaitForActionCameraDuration(UNUSED CameraStruct* arg0);
void BattleScene_ActionSetupAnimationDefault(CameraStruct* arg0);
void BattleScene_ActionSetupAnimationVariantA(CameraStruct* arg0);
void BattleScene_ActionSetupAnimationVariantB(CameraStruct* arg0);
void BattleScene_ActionSetupAnimationVariantC(CameraStruct* arg0);
void BattleScene_ActionSetupAnimationVariantD(CameraStruct* arg0);
void BattleScene_ActionSetupAnimationStep(CameraStruct* arg0);
void BattleScene_StopSpecialOwnerAnimation(unk_BattlePlayerEntity* arg0);
s32 BattleScene_IsSpecialOwnerAnimation(unk_BattlePlayerEntity* arg0);
void BattleScene_CompleteHpUpdateTransition(CameraStruct* arg0, s32* arg1, s32* arg2);
void BattleScene_RunBasicHpTransition(CameraStruct* arg0);
void BattleScene_RunConditionalHpTransition(CameraStruct* arg0);
void BattleScene_RunMoveEffectEndHpTransition(CameraStruct* arg0);
void BattleScene_RunActionEffectHpTransition(CameraStruct* arg0);
void func_84324404(void);
void func_8432440C(void);
void BattleScene_RunRepeatedHitHpTransition(CameraStruct* arg0);
void BattleScene_ActionSetupFinalizeStep(CameraStruct* arg0);
void BattleScene_Phase2(CameraStruct* arg0);
void BattleScene_Phase3(CameraStruct* arg0);
s32 BattleScene_PhaseSelectMoveAnim(void);
void BattleScene_Phase7(CameraStruct* arg0);
void BattleScene_Phase38(CameraStruct* arg0);
void BattleScene_Phase27(CameraStruct* arg0);
void BattleScene_Phase30(CameraStruct* arg0);
void BattleScene_Phase28(CameraStruct* arg0);
void BattleScene_Phase15(CameraStruct* arg0);
void BattleScene_Phase25(CameraStruct* arg0);
s32 BattleScene_EndStatusAnimationsAndCommit(unk_BattlePlayerEntity* arg0);
void BattleScene_Phase29(CameraStruct* arg0);
void BattleScene_Phase12(CameraStruct* arg0);
void BattleScene_Phase13(CameraStruct* arg0);
void BattleScene_Phase14(CameraStruct* arg0);
void BattleScene_Phase17(CameraStruct* arg0);
void BattleScene_PhaseFaint(CameraStruct* arg0);
void BattleScene_Phase31(CameraStruct* arg0);
void func_84326A70(void);
void BattleScene_Phase4(UNUSED CameraStruct* arg0);
void BattleScene_Phase16(CameraStruct* arg0);
void BattleScene_PhaseMoveFailedMessage(CameraStruct* arg0);
void BattleScene_PhaseAttackHit(CameraStruct* arg0);
void BattleScene_PhaseDrainDamage(CameraStruct* arg0);
void BattleScene_Phase10(CameraStruct* arg0);
void BattleScene_PhaseAttackHitRecoil(CameraStruct* arg0);
void BattleScene_PhaseCheckFaintedEndTurn(CameraStruct* arg0);
void BattleScene_ClearMonStatusAnimations(unk_BattlePlayerEntity* arg0);
void BattleScene_PhaseWithdrawFainted(CameraStruct* arg0);
void BattleScene_PhaseWithdrawSwitch(CameraStruct* arg0);
void BattleScene_UpdatePhase(CameraStruct* arg0);


void BattleScene_IntroSetupCamera(CameraStruct* arg0);
void BattleScene_IntroSendOutFirstMon(UNUSED CameraStruct* arg0);
void BattleScene_IntroSendOutSecondMon(UNUSED CameraStruct* arg0);
void BattleScene_IntroNarrowFov(CameraStruct* arg0);
void BattleScene_IntroPanCamera(CameraStruct* arg0);
void BattleScene_IntroWaitFirstMonAnim(UNUSED CameraStruct* arg0);
void BattleScene_IntroRevealFirstMon(CameraStruct* arg0);
void BattleScene_IntroFirstMonSettle(CameraStruct* arg0);
void BattleScene_IntroRevealSecondMon(CameraStruct* arg0);
void BattleScene_IntroSecondMonSettle(CameraStruct* arg0);
void BattleScene_IntroStepNop(UNUSED CameraStruct* arg0);
void BattleScene_IntroInitNop(void);
void BattleScene_UpdateIntroSequence(CameraStruct* arg0);


void BattleScene_FinalPresentationFrameActiveOwner(CameraStruct* arg0);
void BattleScene_FinalPresentationFrameOwner0(CameraStruct* arg0);
void BattleScene_RunFinalPresentation(CameraStruct* arg0, UNUSED unk_BattlePlayerEntity* arg1, UNUSED unk_BattlePlayerEntity* arg2);
void BattleScene_AllocateMemory(void);
void func_843297E8(UNUSED CameraStruct* arg0);
void func_843297F0(UNUSED CameraStruct* arg0);
void BattleScene_AvoidDegenerateCameraLookAt(CameraStruct* arg0);
void BattleScene_TickCameraSubstateDefault(CameraStruct* arg0);
void BattleScene_TickCameraSubstateStripWipe(CameraStruct* arg0);
void BattleScene_TickCameraSubstate(CameraStruct* arg0);
u16 BattleScene_IsOwnerInViewWedge(unk_BattlePlayerEntity* arg0, CameraStruct* arg1, unk_BattlePlayerEntity* a2, s16 arg3, f32 arg4);
u16 BattleScene_IsOwnerInViewWedgeAlt(unk_BattlePlayerEntity* arg0, CameraStruct* arg1, unk_BattlePlayerEntity* a2, s16 arg3, f32 arg4);
void BattleScene_UpdateBothOwnersVisibilityCulling(CameraStruct* arg0);
void BattleScene_UpdateOpponentVisibilityCulling(CameraStruct* arg0);
void func_8432A414(void);
void BattleScene_ShowBothOwners(void);
void BattleScene_HideOpponentOwner(void);
void BattleScene_HideActiveOwner(void);
void BattleScene_HideFaintedOwners(void);
void BattleScene_UpdateOwnerVisibilitySingle(CameraStruct* arg0);
void BattleScene_UpdateOwnerVisibilityDouble(CameraStruct* arg0);
void BattleScene_Update(CameraStruct* arg0);
s32 BattleScene_Dispatch(s32 arg0, CameraStruct* arg1);


void BattleAnim_StartFreezeStatusAnimation(unk_BattlePlayerEntity* arg0);
void BattleAnim_RestoreBaseModelAnimation(unk_BattlePlayerEntity* arg0);
void BattleAnim_ClearFreezeStatusAnimation(unk_BattlePlayerEntity* arg0);
void BattleAnim_ResetFreezeStatusAndRestoreAnimation(unk_BattlePlayerEntity* arg0);
void BattleAnim_ClearFreezeStatusAnimationIfThawed(unk_BattlePlayerEntity* arg0);
void BattleAnim_UpdateSleepStatusAnimation(unk_BattlePlayerEntity* arg0);
void BattleAnim_EndSleepStatusAnimation(unk_BattlePlayerEntity* arg0);
void BattleAnim_ClearSleepStatusAnimation(unk_BattlePlayerEntity* arg0);


void BattleAnim_PlaySoundEffect1(void);
void BattleAnim_PlaySoundEffect2(void);
void BattleAnim_PlaySoundEffect3(void);
void BattleAnim_PlaySoundEffect8(void);
void BattleAnim_PlayOwnerCry(unk_BattlePlayerEntity* arg0, s16 arg1);
void BattleAnim_PlaySpeciesSequence33(unk_BattlePlayerEntity* arg0);
void Battle_TriggerTrainerPresentationCue(unk_BattlePlayerEntity* arg0);
void BattleAnim_PlaySpeciesReactionSound(unk_BattlePlayerEntity* arg0, PokemonAudioInfo* arg1, s32 arg2);
void BattleScene_ConfigureAudioChannelGroupsByTeam(void);
void BattleScene_ConfigureAudioChannelGroupCounts(void);
void BattleScene_SelectBattleMusic(void);
void BattleScene_StartBattleMusic(void);
void BattleAnim_PlayBattleSequenceById(unk_BattlePlayerEntity* arg0, s32 arg1);
void BattleAnim_RunEffectInitStart(s16 arg0);
void BattleAnim_RunEffectInitEnd(s16 arg0);
void BattleAnim_RegisterEffectSlot(func_D_84390300 arg0, func_D_84390320 arg1);
void BattleAnim_RunEffectList(s32 arg0, s32 arg1, s32 arg2);
void BattleAnim_ProcessQueuedEffects(void);
void BattleAnim_UpdateFrame(UNUSED CameraStruct* arg0);
void BattleAnim_SetQueuedEffectList(u8 arg0);
u8 BattleAnim_GetCurrentEffectList(void);
void BattleAnim_SetQueuedResourceListId(u8 arg0);
u8 BattleAnim_GetQueuedResourceListId(void);
s16 BattleAnim_GetQueuedMoveId(void);
void BattleAnim_QueueMoveEffect(s32 arg0, unk_BattlePlayerEntity* arg1, unk_BattlePlayerEntity* arg2, s16 arg3, s16 arg4);
void BattleAnim_QueueMoveEffectScriptA(s32 arg0, unk_BattlePlayerEntity* arg1, unk_BattlePlayerEntity* arg2, s16 arg3, s16 arg4);
void BattleAnim_QueueMoveEffectEnd(s32 arg0, unk_BattlePlayerEntity* arg1, unk_BattlePlayerEntity* arg2, s16 arg3, s16 arg4);
void BattleAnim_QueueMoveEffectScriptB(s32 arg0, unk_BattlePlayerEntity* arg1, unk_BattlePlayerEntity* arg2, s16 arg3, s16 arg4);
void BattleAnim_QueueEffectList3(s32 arg0, unk_BattlePlayerEntity* arg1, unk_BattlePlayerEntity* arg2, s16 arg3, s16 arg4);
void BattleAnim_QueueEffectList6(s32 arg0, unk_BattlePlayerEntity* arg1);
void BattleAnim_QueueEffectList5(s32 arg0, unk_BattlePlayerEntity* arg1);
void BattleAnim_QueueEffectList6Alt(s32 arg0, unk_BattlePlayerEntity* arg1);
void BattleAnim_QueueEffectList9(s32 arg0);
void BattleAnim_QueueEffectList(u8 arg0, unk_BattlePlayerEntity* arg1);
void BattleAnim_StopOwnerCategoryParticles(u8 arg0, unk_BattlePlayerEntity* arg1);
void BattleAnim_RegisterAssetTable(arg1_func_80019420* arg0);
void BattleAnim_ResetAssetTable(void);
void BattleAnim_BuildResourceListForMove(s16 arg0);
void BattleAnim_LoadMoveResourceList(unk_D_800AE540_1194* arg0, s16 arg1);
void BattleAnim_LoadModeResourceList(unk_D_800AE540_1194* arg0, s16 arg1);
void BattleAnim_RegisterAllAssetTables(void);
void BattleAnim_RegisterAssetTablesForSession(unk_D_800AE540_1194* arg0);
void BattleAnim_ResetDisplayContexts(void);
ParticleEffectInstance* BattleAnim_GetOwnerContextParticle(Fragment2_1GraphNode* arg0);
Fragment2_1GraphNode* BattleAnim_AllocOwnerDisplayContext(ParticleEffectInstance* arg0);
void BattleAnim_FreeOwnerDisplayContext(Fragment2_1GraphNode* arg0);
Fragment2_1GraphNode* BattleAnim_AllocParticleDisplayContext(ParticleEffectInstance* arg0);
void BattleAnim_FreeParticleDisplayContext(Fragment2_1GraphNode* arg0);
void BattleAnim_InitModelWithAnim(Fragment2_1GraphNode* arg0, s16 arg1, s16 arg2);
void BattleAnim_SetModelAnimFrame(Fragment2_1GraphNode* arg0, s16 arg1);
void BattleAnim_InitModel(Fragment2_1GraphNode* arg0, s16 arg1);
void BattleAnim_BindModelAnim(Fragment2_1GraphNode* arg0, s16 arg1);
void BattleAnim_BindModelAnimReversed(Fragment2_1GraphNode* arg0, s16 arg1);
s32 BattleAnim_IsModelAnimComplete(Fragment2_1GraphNode* arg0);
void BattleAnim_UpdateEffectCallbacks(UNUSED CameraStruct* arg0);
void BattleAnim_DrawEffectCallbacks(UNUSED CameraStruct* arg0);
void BattleAnim_UpdateCamera(CameraStruct* arg0);
s32 BattleAnim_DispatchPresentation(s32 arg0, CameraStruct* arg1);
void BattleAnim_Initialize(void);
void BattleAnim_Reset(void);
void BattleAnim_GetPointAlongCameraRay(Vec3f* arg0, f32 arg1);
void BattleAnim_GetCameraEyeAngles(s16* arg0, s16* arg1);
void BattleAnim_GetCameraEyeYaw(s16* arg0);
void BattleAnim_GetCameraLookAngles(s16* arg0, s16* arg1);
void BattleAnim_GetCameraLookYaw(s16* arg0);
void BattleAnim_GetCameraStoredAngles76(s16* arg0, s16* arg1);
void BattleAnim_GetCameraStoredYaw78(s16* arg0);
void BattleAnim_GetCameraStoredAngles70(s16* arg0, s16* arg1);
void BattleAnim_GetCameraStoredYaw72(s16* arg0);


void BattleAnim_InitParticleSystem(void);
gBattleAnimEffectSlots* BattleAnim_AllocEffectSlot(void);
void BattleAnim_FreeEffectSlot(gBattleAnimEffectSlots* arg0);
void BattleAnim_InitializeParticleChain(ParticleEffectInstance* arg0, Vec3f arg1, Vec3s arg2, s32 arg3, s32 arg4);
void BattleAnim_CloneParticleState(ParticleEffectInstance* arg0, ParticleEffectInstance* arg1, func_unk_D_8140E724_008 arg2, ParticleEffectData* arg3, s32 arg4);
void BattleAnim_EmitParticleBurst(ParticleEffectInstance* arg0, func_unk_D_8140E724_008 arg1, ParticleEffectData* arg2, s16 arg3);
void BattleAnim_EmitParticleBurstWithMetadata(ParticleEffectInstance* arg0, func_unk_D_8140E724_008 arg1, ParticleEffectData* arg2, s16 arg3, s16 arg4, s16 arg5);
ParticleEffectInstance* BattleAnim_CreateProceduralParticle(s16 arg0, s16 arg1, s32 arg2, f32 arg3);
void BattleAnim_ReleaseParticleModel(ParticleEffectInstance* arg0);
void BattleAnim_DestroyParticle(ParticleEffectInstance* arg0);
void BattleAnim_InitializeParticleAnchor(ParticleEffectInstance* arg0);
void BattleAnim_UpdateParticleAnchor(ParticleEffectInstance* arg0);
void BattleAnim_UpdateParticleCameraScale(ParticleEffectInstance* arg0);
void BattleAnim_UpdateOrDestroyParticle(ParticleEffectInstance* arg0);
void BattleAnim_UpdateParticlePool(void);
void BattleAnim_InitializeParticleFromEffect(ParticleEffectInstance* arg0, unk_BattlePlayerEntity* arg1, gBattleAnimEffectSlots* arg2, s16 arg3);
void BattleAnim_SpawnEffectParticles(gBattleAnimEffectSlots* arg0, s32 arg1);
void BattleAnim_SpawnStandardParticles(gBattleAnimEffectSlots* arg0);
void BattleAnim_SpawnBatchedParticles(gBattleAnimEffectSlots* arg0);
void BattleAnim_SpawnSingleParticle(gBattleAnimEffectSlots* arg0);
void BattleAnim_DispatchParticleEmission(gBattleAnimEffectSlots* arg0);
void BattleAnim_TickEffectSlots(void);
void BattleAnim_UpdateEffects(void);
void BattleAnim_CleanupEffectsRetainingCategories47(void);
void BattleAnim_CleanupEffectsRetainingCategory4(void);
s32 BattleAnim_GetMoveFailedFlag(void);
void BattleAnim_UpdateMoveFailedFlag(void);
void BattleAnim_ClearEffectCallbacks(void);
s32 BattleAnim_IsEffectSpawningEnabled(void);
void BattleAnim_DisableEffectSpawning(void);
void BattleAnim_EnableEffectSpawning(void);
void BattleAnim_DisableEffectSpawningAlias(void);
void BattleAnim_CleanupEffects(s32 arg0);
void BattleAnim_StopParticlesForOwnerCategory(u8 arg0, unk_BattlePlayerEntity* arg1);
void BattleAnim_ResetSpawnDelay(void);
void BattleAnim_SetSpawnDelay(s32 arg0);
void BattleAnim_AddSpawnDelay(s32 arg0);
void BattleAnim_ResetSpawnDelayAlias(void);
gBattleAnimEffectSlots* BattleAnim_CreateEffectSlot(s32 arg0, s32 arg1, s8 arg2, func_unk_D_8140E724 arg3, ParticleEffectData* arg4, unk_BattlePlayerEntity* arg5, s16 arg6, s16 arg7, u8 arg8, u8 arg9, u8 argA, u8 argB);
gBattleAnimEffectSlots* BattleAnim_CreateEffectSlotForCurrentOwner(s32 arg0, func_unk_D_8140E724 arg1, ParticleEffectData* arg2, s16 arg3, s16 arg4, u8 arg5, u8 arg6, u8 arg7, u8 arg8);
gBattleAnimEffectSlots* BattleAnim_CreateRepeatingEffectSlotForCurrentOwner(s32 arg0, s32 arg1, s8 arg2, func_unk_D_8140E724 arg3, ParticleEffectData* arg4, s16 arg5, s16 arg6, u8 arg7, u8 arg8, u8 arg9, u8 argA);
gBattleAnimEffectSlots* BattleAnim_SpawnGlobalTintColorFadeDetach(s32 arg0, s16 arg1, u8 arg2);
gBattleAnimEffectSlots* BattleAnim_SpawnDescriptor25AlphaFadeInHoldOut(s32 arg0, s16 arg1, s16 arg2, u8 arg3, u8 arg4);
gBattleAnimEffectSlots* BattleAnim_SpawnDescriptor25AlphaHoldFadeOutFullAlpha(s32 arg0, s16 arg1, s16 arg2, u8 arg3);
gBattleAnimEffectSlots* BattleAnim_SpawnDescriptor25AlphaHoldFadeOut(s32 arg0, s16 arg1, s16 arg2, u8 arg3, u8 arg4);
gBattleAnimEffectSlots* BattleAnim_SpawnDescriptor25AlphaHoldFadeOutRepeating(s32 arg0, s32 arg1, s8 arg2, s16 arg3, s16 arg4, u8 arg5, u8 arg6);
gBattleAnimEffectSlots* BattleAnim_SpawnDescriptor25AlphaFadeInHoldFullAlpha(s32 arg0, s16 arg1, s16 arg2, u8 arg3);
gBattleAnimEffectSlots* BattleAnim_SpawnDescriptor25AlphaFadeInHold(s32 arg0, s16 arg1, s16 arg2, u8 arg3, u8 arg4);
gBattleAnimEffectSlots* BattleAnim_SpawnDescriptor25AlphaFadeInHoldRepeating(s32 arg0, s32 arg1, s8 arg2, s16 arg3, s16 arg4, u8 arg5, u8 arg6);
gBattleAnimEffectSlots* BattleAnim_SpawnDescriptor25AlphaHoldDetachFullAlpha(s32 arg0, s16 arg1, u8 arg2);
gBattleAnimEffectSlots* BattleAnim_SpawnDescriptor25AlphaHoldDetach(s32 arg0, s16 arg1, u8 arg2, u8 arg3);
gBattleAnimEffectSlots* BattleAnim_SpawnDescriptor25AlphaHoldDetachRepeating(s32 arg0, s32 arg1, s8 arg2, s16 arg3, u8 arg4, u8 arg5);
gBattleAnimEffectSlots* BattleAnim_SpawnDescriptor25PaletteFadeOut(s32 arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4);
gBattleAnimEffectSlots* BattleAnim_SpawnDescriptor25PaletteFadeIn(s32 arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4);
gBattleAnimEffectSlots* BattleAnim_SpawnOwnerModelTintRampDetach(s32 arg0, u8 arg1, s16 arg2, s16 arg3, s16 arg4);
gBattleAnimEffectSlots* BattleAnim_SpawnOwnerModelTintPulseDetach(s32 arg0, s16 arg1, u8 arg2, s16 arg3, s16 arg4, s16 arg5);
gBattleAnimEffectSlots* BattleAnim_SpawnOwnerModelTintHoldFadeDetach(s32 arg0, s16 arg1, u8 arg2, s16 arg3, s16 arg4);
gBattleAnimEffectSlots* BattleAnim_SpawnOwnerModelTintPaletteApproachInactive(s32 arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4);
gBattleAnimEffectSlots* BattleAnim_SpawnOwnerModelTintPaletteApproachInactiveAlt(s32 arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4);
gBattleAnimEffectSlots* BattleAnim_SpawnOwnerModelTintPaletteCycle(s32 arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5);
gBattleAnimEffectSlots* BattleAnim_SpawnOwnerModelTintPaletteCycleVariant(s32 arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5);
gBattleAnimEffectSlots* BattleAnim_SpawnOwnerModelTintPaletteFade(s32 arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5);
gBattleAnimEffectSlots* BattleAnim_SpawnOwnerModelTintRandomPaletteCycle(s32 arg0, s16 arg1, u8 arg2);
gBattleAnimEffectSlots* BattleAnim_SpawnOwnerModelTintPaletteRotateFadeDetach(s32 arg0, s16 arg1, s16 arg2, u8 arg3);
gBattleAnimEffectSlots* BattleAnim_SpawnOwnerModelAlphaFade(s32 arg0, s16 arg1, s16 arg2, s16 arg3);
gBattleAnimEffectSlots* BattleAnim_SpawnOwnerModelAlphaFadeFullPreset(s32 arg0);
gBattleAnimEffectSlots* BattleAnim_SpawnOwnerModelAlphaFadeZeroStartPreset(s32 arg0);
gBattleAnimEffectSlots* BattleAnim_SpawnCategory17MarkerSlot(s32 arg0, u8 arg1);
gBattleAnimEffectSlots* BattleAnim_SpawnCategory19MarkerSlot(s32 arg0, u8 arg1);
void BattleAnim_EffectStartNop(void);
void BattleAnim_EffectEndNop(void);
void BattleAnim_SetEffectStateFlag(s32 arg0);
void BattleAnim_ClearEffectStateFlag(void);
s32 BattleAnim_GetEffectStateFlag(void);
s32 BattleAnim_IsCurrentOwnerSpecies(s32 arg0);
s32 BattleAnim_GetSecondaryOwnerSpecies(void);
s32 BattleAnim_GetTertiaryOwnerSpecies(void);
void BattleAnim_GetOwnerBonePosition(unk_BattlePlayerEntity* arg0, s16 arg1, Vec3f* arg2);
void BattleAnim_GetCurrentOwnerBonePosition(Vec3f* arg0);
void BattleAnim_GetSecondaryOwnerBonePosition(Vec3f* arg0);
void BattleAnim_GetTertiaryOwnerBonePosition(Vec3f* arg0);
void BattleAnim_GetSecondaryOwnerAnchorPosition(Vec3f* arg0);
void BattleAnim_GetTertiaryOwnerBone9Position(Vec3f* arg0);
void BattleAnim_GetOwnerModelBoundsScaled(unk_BattlePlayerEntity* arg0, Vec3f* arg1);
f32 BattleAnim_GetSpeciesBaseScale(unk_BattlePlayerEntity* arg0);
f32 BattleAnim_GetOwnerModelScale(unk_BattlePlayerEntity* arg0);
void BattleAnim_GetOwnerSpeciesBaseScaleAlias(unk_BattlePlayerEntity* arg0);
f32 BattleAnim_GetSecondaryOwnerModelScale(void);
void BattleAnim_GetSecondaryOwnerSpeciesBaseScale(void);
f32 BattleAnim_GetTertiaryOwnerModelScale(void);
void BattleAnim_GetTertiaryOwnerSpeciesBaseScale(void);
CameraStruct* BattleAnim_GetCameraContext(void);
ParticleEffectInstance* BattleAnim_SpawnSecondaryOwnerParticle(Vec3f arg0, u8 arg1);
void BattleAnim_SetParticlePosition(ParticleEffectInstance* arg0, Vec3f arg1);
void BattleAnim_MarkParticleInactive(ParticleEffectInstance* arg0);
s16 BattleAnim_GetParticleAngleYToTertiaryOwner(ParticleEffectInstance* arg0);
void BattleAnim_SetGlobalTintFromParticle(ParticleEffectInstance* arg0);
void BattleAnim_LoadGlobalTintToParticle(ParticleEffectInstance* arg0);


void BattleAnim_InitSecondaryOwnerParticleBlueFadeGrow(ParticleEffectInstance* arg0);
void BattleAnim_UpdateSecondaryOwnerParticleBlueFadeGrow(ParticleEffectInstance* arg0);
void BattleAnim_InitSecondaryOwnerParticleBlueGrow(ParticleEffectInstance* arg0);
void BattleAnim_UpdateSecondaryOwnerParticleBlueGrow(ParticleEffectInstance* arg0);
void BattleAnim_ConfigureSecondaryOwnerParticleVariant(ParticleEffectInstance* arg0, u8 arg1);


s32 BattleAnim_DrawAsset95Ia8Billboard(ParticleEffectInstance* arg0, CameraStruct* arg1);
void BattleAnim_DrawAsset76Ia8FrameWithAsset77I4Overlay(ParticleEffectInstance* arg0, CameraStruct* arg1);
void BattleAnim_DrawAsset76Ia8FrameWithAsset77I4OverlayPipelineA(ParticleEffectInstance* arg0, CameraStruct* arg1);
void BattleAnim_DrawAsset76Ia8FrameWithAsset77I4OverlayPipelineB(ParticleEffectInstance* arg0, CameraStruct* arg1);
void BattleAnim_DrawAsset1FAnimatedI4WithAsset20DisplayList(ParticleEffectInstance* arg0, CameraStruct* arg1);
s32 BattleAnim_DrawAssetBcRgba16WithAssetBdDisplayList(ParticleEffectInstance* arg0, UNUSED CameraStruct* arg1);
void BattleAnim_DrawAssets27And28LayeredI4QuadVariantA(ParticleEffectInstance* arg0, UNUSED CameraStruct* arg1);
void BattleAnim_DrawAssets27And28LayeredI4QuadVariantB(ParticleEffectInstance* arg0, UNUSED CameraStruct* arg1);
void BattleAnim_DrawAsset29DualI4LayeredQuad(ParticleEffectInstance* arg0, UNUSED CameraStruct* arg1);
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
void BattleAnim_DrawAsset13FrameI4YScaledQuadA(ParticleEffectInstance* arg0, UNUSED CameraStruct* arg1);
void BattleAnim_DrawAsset13FrameI4YScaledQuadB(ParticleEffectInstance* arg0, UNUSED CameraStruct* arg1);
void BattleAnim_DrawAsset13FrameI4YScaledQuadC(ParticleEffectInstance* arg0, UNUSED CameraStruct* arg1);
void BattleAnim_DrawAsset13FrameI4ModelQuadA(ParticleEffectInstance* arg0, CameraStruct* arg1);
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
void BattleAnim_SetupOwnerModelTintRampDetach(ParticleEffectInstance* arg0);
void BattleAnim_CallbackOwnerModelTintRampDetach(ParticleEffectInstance* arg0);
void BattleAnim_SetupOwnerModelTintPulseDetach(ParticleEffectInstance* arg0);
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
void BattleAnim_SetupOwnerModelTintRandomPaletteCycle(ParticleEffectInstance* arg0);
void BattleAnim_CallbackOwnerModelTintRandomPaletteCycle(ParticleEffectInstance* arg0);
void BattleAnim_SetupOwnerModelTintPaletteRotateFadeDetach(ParticleEffectInstance* arg0);
void BattleAnim_CallbackOwnerModelTintPaletteRotateFadeDetach(ParticleEffectInstance* arg0);
void BattleAnim_SetupOwnerModelAlphaFade(ParticleEffectInstance* arg0);
void BattleAnim_CallbackOwnerModelAlphaFade(ParticleEffectInstance* arg0);
void BattleAnim_SetupParticleRecolorTransparent(ParticleEffectInstance* arg0);
void BattleAnim_CallbackStartEffect125OwnerColorAlphaFade(ParticleEffectInstance* arg0);
void BattleAnim_SetupDescriptor25AlphaFadeInHoldOut(ParticleEffectInstance* arg0);
void BattleAnim_CallbackDescriptor25AlphaFadeInHoldOut(ParticleEffectInstance* arg0);
void BattleAnim_SetupDescriptor25AlphaHoldFadeOut(ParticleEffectInstance* arg0);
void BattleAnim_CallbackDescriptor25AlphaHoldFadeOut(ParticleEffectInstance* arg0);
void BattleAnim_SetupDescriptor25AlphaFadeInHold(ParticleEffectInstance* arg0);
void BattleAnim_CallbackDescriptor25AlphaFadeInHold(ParticleEffectInstance* arg0);
void BattleAnim_SetupDescriptor25AlphaHoldDetach(ParticleEffectInstance* arg0);
void BattleAnim_CallbackDescriptor25AlphaHoldDetach(ParticleEffectInstance* arg0);
void BattleAnim_SetupDescriptor25PaletteFadeOut(ParticleEffectInstance* arg0);
void BattleAnim_CallbackDescriptor25PaletteFadeOut(ParticleEffectInstance* arg0);
void BattleAnim_SetupDescriptor25PaletteFadeIn(ParticleEffectInstance* arg0);
void BattleAnim_CallbackDescriptor25PaletteFadeIn(ParticleEffectInstance* arg0);


void BattleAnim_CallbackStartEffects23And35And84Descriptor4FColorCycleScaleFade_InitParticle(ParticleEffectInstance* arg0, s16 arg1);
void BattleAnim_CallbackStartEffects23And35And84Descriptor4FColorCycleScaleFade_AdvancePhase(ParticleEffectInstance* arg0);
void BattleAnim_CallbackStartEffects23And35And84Descriptor4FColorCycleScaleFade(ParticleEffectInstance* arg0);
void BattleAnim_SetupUnusedDescriptor4FColorCycleScaleFadeVariant(ParticleEffectInstance* arg0);
void BattleAnim_MotionUnusedDescriptor4FColorCycleScaleFadeVariant(ParticleEffectInstance* arg0);
void BattleAnim_CallbackUnusedDescriptor4FColorCycleScaleFadeVariant(ParticleEffectInstance* arg0);
void BattleAnim_CallbackStartEffects23And35And84Descriptor3DAlphaScaleFade_InitParticle(ParticleEffectInstance* arg0);
void BattleAnim_CallbackStartEffects23And35And84Descriptor3DAlphaScaleFade_AdvancePhase(ParticleEffectInstance* arg0);
void BattleAnim_CallbackStartEffects23And35And84Descriptor3DAlphaScaleFade(ParticleEffectInstance* arg0);
void BattleAnim_CallbackStartEffects23And35And84Descriptor4FRotatingFallColorCycle_InitParticle(ParticleEffectInstance* arg0, s16 arg1);
void BattleAnim_CallbackStartEffects23And35And84Descriptor4FRotatingFallColorCycle_AdvancePhase(ParticleEffectInstance* arg0);
void BattleAnim_CallbackStartEffects23And35And84Descriptor4FRotatingFallColorCycle(ParticleEffectInstance* arg0);
void BattleAnim_CallbackSharedGrowFadeSetup(ParticleEffectInstance* arg0);
void BattleAnim_CallbackSharedDescriptor04GrowFade(ParticleEffectInstance* arg0);
void BattleAnim_CallbackEndEffect68Descriptor1BExpandingFadeDrift(ParticleEffectInstance* arg0);
void BattleAnim_CallbackUnusedGrowFadeVariant(ParticleEffectInstance* arg0);
void BattleAnim_CallbackStartEffect104DelayedSpiralFade_InitParticle(ParticleEffectInstance* arg0);
void BattleAnim_CallbackStartEffect104DelayedSpiralFade(ParticleEffectInstance* arg0);
void BattleAnim_CallbackEndEffect29Descriptor02RotatingScaleGrow_InitParticle(ParticleEffectInstance* arg0);
void BattleAnim_CallbackEndEffect29Descriptor02RotatingScaleGrow(ParticleEffectInstance* arg0);
void BattleAnim_SetupUnusedVariant2(ParticleEffectInstance* arg0);
void BattleAnim_CallbackUnusedVariant2(ParticleEffectInstance* arg0);
void BattleAnim_CallbackStartEffect22Descriptor4ABurstChild_InitParticle(ParticleEffectInstance* arg0);
void BattleAnim_CallbackStartEffect22Descriptor4ABurstChild(ParticleEffectInstance* arg0);
void BattleAnim_CallbackStartEffect22Descriptor46BurstEmitter_InitParticle(ParticleEffectInstance* arg0);
void BattleAnim_CallbackStartEffect22Descriptor46BurstEmitter(ParticleEffectInstance* arg0);
void BattleAnim_CallbackStartEffect22Descriptor34RotatingPaletteScaleFade_InitParticle(ParticleEffectInstance* arg0);
void BattleAnim_CallbackStartEffect22Descriptor34RotatingPaletteScaleFade(ParticleEffectInstance* arg0);
void BattleAnim_CallbackStartEffect22Descriptor3DRotatingAlphaPaletteFade_InitParticle(ParticleEffectInstance* arg0);
void BattleAnim_CallbackStartEffect22Descriptor3DRotatingAlphaPaletteFade(ParticleEffectInstance* arg0);
void BattleAnim_SetParticleColorFromVariantIndex(ParticleEffectInstance* arg0, u8 arg1);
void func_84334B04(void);
void BattleAnim_ApproachParticleColorFromVariantIndex(ParticleEffectInstance* arg0);
void BattleAnim_CallbackEndEffect40Descriptor46DelayedScaleAlphaFade_InitParticle(ParticleEffectInstance* arg0);
void BattleAnim_CallbackEndEffect40Descriptor46DelayedScaleAlphaFade(ParticleEffectInstance* arg0);
void BattleAnim_CallbackEndEffects81And82Descriptor46AnimatedFade_InitParticle(ParticleEffectInstance* arg0);
void BattleAnim_CallbackEndEffects81And82Descriptor46AnimatedFade(ParticleEffectInstance* arg0);
void BattleAnim_CallbackEndEffect40Descriptor48SpreadScaleAlphaFade_InitParticle(ParticleEffectInstance* arg0);
void BattleAnim_CallbackEndEffect40Descriptor48SpreadScaleAlphaFade(ParticleEffectInstance* arg0);
void BattleAnim_CallbackEndEffect40Descriptor3DSpreadRisingColorFade_InitParticle(ParticleEffectInstance* arg0);
void BattleAnim_CallbackEndEffect40Descriptor3DSpreadRisingColorFade(ParticleEffectInstance* arg0);
void BattleAnim_CallbackEndEffect56Descriptor46RisingScaleAlphaFade_InitParticle(ParticleEffectInstance* arg0);
void BattleAnim_CallbackEndEffect56Descriptor46RisingScaleAlphaFade(ParticleEffectInstance* arg0);
void BattleAnim_CallbackEndEffect56Descriptor47SpreadScaleAlphaRise_InitParticle(ParticleEffectInstance* arg0);
void BattleAnim_CallbackEndEffect56Descriptor47SpreadScaleAlphaRise(ParticleEffectInstance* arg0);
void BattleAnim_CallbackEndEffects54And56Descriptor3DRisingColorScaleFade_InitParticle(ParticleEffectInstance* arg0);
void BattleAnim_CallbackEndEffects54And56Descriptor3DRisingColorScaleFade(ParticleEffectInstance* arg0);
void BattleAnim_CallbackEndEffects40And54Descriptor46SpreadScaleFade_InitParticle(ParticleEffectInstance* arg0);
void BattleAnim_CallbackEndEffects40And54Descriptor46SpreadScaleFade(ParticleEffectInstance* arg0);
void BattleAnim_CallbackEndEffect54Descriptor46DelayedColorAlphaFade_InitParticle(ParticleEffectInstance* arg0);
void BattleAnim_CallbackEndEffect54Descriptor46DelayedColorAlphaFade(ParticleEffectInstance* arg0);
void BattleAnim_CallbackSharedRotatingColorFadeSetup(ParticleEffectInstance* arg0, s16 arg1, s16 arg2);
void BattleAnim_CallbackSharedRotatingColorFadeMotion(ParticleEffectInstance* arg0, s32 arg1);
void BattleAnim_CallbackEndEffects15And22Descriptor4ERotatingColorFadeVariant0(ParticleEffectInstance* arg0);
void BattleAnim_CallbackEndEffects15And22Descriptor4ERotatingColorFadeVariant1(ParticleEffectInstance* arg0);
void BattleAnim_CallbackEndEffects15And22And59Descriptor3DRotatingAlphaScaleFade_InitParticle(ParticleEffectInstance* arg0);
void BattleAnim_CallbackEndEffects15And22And59Descriptor3DRotatingAlphaScaleFade_AdvancePhase(ParticleEffectInstance* arg0);
void BattleAnim_CallbackEndEffects15And22And59Descriptor3DRotatingAlphaScaleFade(ParticleEffectInstance* arg0);
void BattleAnim_CallbackEndEffect59Descriptor4FRotatingColorScaleFade_InitParticle(ParticleEffectInstance* arg0);
void BattleAnim_CallbackEndEffect59Descriptor4FRotatingColorScaleFade_AdvancePhase(ParticleEffectInstance* arg0);
void BattleAnim_CallbackEndEffect59Descriptor4FRotatingColorScaleFade(ParticleEffectInstance* arg0);
void BattleAnim_CallbackEndEffect59Descriptor4FColorScaleFade_InitParticle(ParticleEffectInstance* arg0);
void BattleAnim_CallbackEndEffect59Descriptor4FColorScaleFade(ParticleEffectInstance* arg0);
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


void BattleAnim_CallbackEndEffect16Descriptor45DelayedRotatingMotion_InitParticle(ParticleEffectInstance* arg0);
void BattleAnim_CallbackEndEffect16Descriptor45DelayedRotatingMotion(ParticleEffectInstance* arg0);
void BattleAnim_CallbackStartEffect48Descriptor45RisingSparkFade_InitParticle(ParticleEffectInstance* arg0, s16 arg1);
void BattleAnim_CallbackStartEffect48Descriptor45RisingSparkFade(ParticleEffectInstance* arg0);
void BattleAnim_CallbackStartEffects77And120Descriptor45DeceleratingSparkFade_InitParticle(ParticleEffectInstance* arg0);
void BattleAnim_CallbackStartEffects77And120Descriptor45DeceleratingSparkFade_AdvancePhase(ParticleEffectInstance* arg0);
void BattleAnim_CallbackStartEffects77And120Descriptor45DeceleratingSparkFade(ParticleEffectInstance* arg0);
void BattleAnim_CallbackStartEffects77And120Descriptor45AimedSparkFade_InitParticle(ParticleEffectInstance* arg0);
void BattleAnim_CallbackStartEffects77And120Descriptor45AimedSparkFade(ParticleEffectInstance* arg0);
void BattleAnim_SetupUnusedRotatingSparkVariant(ParticleEffectInstance* arg0);
void BattleAnim_MotionUnusedRotatingSparkVariant(ParticleEffectInstance* arg0);
void BattleAnim_CallbackUnusedRotatingSparkVariant(ParticleEffectInstance* arg0);
void BattleAnim_SetupUnusedAimedSparkVariant(ParticleEffectInstance* arg0);
void BattleAnim_CallbackUnusedAimedSparkVariant(ParticleEffectInstance* arg0);
void BattleAnim_CallbackStartEffects6And58AnimatedScaleAlphaFade_InitParticle(ParticleEffectInstance* arg0);
void BattleAnim_CallbackStartEffects6And58AnimatedScaleAlphaFade(ParticleEffectInstance* arg0);
void BattleAnim_CallbackStartEffect58Descriptor0ABurstChild_InitParticle(ParticleEffectInstance* arg0);
void BattleAnim_CallbackStartEffect58Descriptor0ABurstChild(ParticleEffectInstance* arg0);
void BattleAnim_CallbackStartEffect58Descriptor08MetadataBurstChild_InitParticle(ParticleEffectInstance* arg0);
void BattleAnim_CallbackStartEffect58Descriptor08MetadataBurstChild(ParticleEffectInstance* arg0);
void BattleAnim_CallbackStartEffect58Descriptor08MetadataBurstEmitter_InitParticle(ParticleEffectInstance* arg0);
void BattleAnim_CallbackStartEffect58Descriptor08MetadataBurstEmitter(ParticleEffectInstance* arg0);
void BattleAnim_CallbackStartEffect6Descriptor0ABurstChild_InitParticle(ParticleEffectInstance* arg0);
void BattleAnim_CallbackStartEffect6Descriptor0ABurstChild(ParticleEffectInstance* arg0);
void BattleAnim_CallbackStartEffect6Descriptor08MetadataBurstChild_InitParticle(ParticleEffectInstance* arg0);
void BattleAnim_CallbackStartEffect6Descriptor08MetadataBurstChild(ParticleEffectInstance* arg0);
void BattleAnim_CallbackStartEffect6DefaultDescriptorBurstEmitter_InitParticle(ParticleEffectInstance* arg0);
void BattleAnim_CallbackStartEffect6DefaultDescriptorBurstEmitter(ParticleEffectInstance* arg0);
void BattleAnim_CallbackStartEffect47Descriptor4AAnimatedScaleFade_InitParticle(ParticleEffectInstance* arg0);
void BattleAnim_CallbackStartEffect47Descriptor4AAnimatedScaleFade_AdvancePhase(ParticleEffectInstance* arg0);
void BattleAnim_CallbackStartEffect47Descriptor4AAnimatedScaleFade(ParticleEffectInstance* arg0);
void BattleAnim_CallbackStartEffects2And15Descriptor08IndexedScaleDelayFade_InitParticle(ParticleEffectInstance* arg0);
void BattleAnim_CallbackStartEffects2And15Descriptor08IndexedScaleDelayFade(ParticleEffectInstance* arg0);
void BattleAnim_CallbackSharedDescriptor53ScaleGrowAnimFade_InitParticle(ParticleEffectInstance* arg0);
void BattleAnim_CallbackSharedDescriptor53ScaleGrowAnimFade(ParticleEffectInstance* arg0);
void BattleAnim_CallbackSharedDescriptor53ScalePulseCycle_InitParticle(ParticleEffectInstance* arg0);
void BattleAnim_CallbackSharedDescriptor53ScalePulseCycle(ParticleEffectInstance* arg0);
void BattleAnim_CallbackSharedExpandingScaleAlphaFade_InitParticle(ParticleEffectInstance* arg0);
void BattleAnim_CallbackSharedExpandingScaleAlphaFade(ParticleEffectInstance* arg0);
void BattleAnim_CallbackEndEffect68Descriptor54FlickerExpandingFade_InitParticle(ParticleEffectInstance* arg0);
void BattleAnim_CallbackEndEffect68Descriptor54FlickerExpandingFade(ParticleEffectInstance* arg0);
void BattleAnim_CallbackEndEffect69Descriptor54ExpandingHoldFade_InitParticle(ParticleEffectInstance* arg0);
void BattleAnim_CallbackEndEffect69Descriptor54ExpandingHoldFade(ParticleEffectInstance* arg0);
void BattleAnim_CallbackSharedDescriptor19AnimatedFadeMotion_InitParticle(ParticleEffectInstance* arg0);
void BattleAnim_CallbackSharedDescriptor19AnimatedFadeMotion(ParticleEffectInstance* arg0);
void BattleAnim_CallbackEndEffect23Descriptor19AnimatedFade_InitParticle(ParticleEffectInstance* arg0);
void BattleAnim_CallbackEndEffect23Descriptor19AnimatedFade(ParticleEffectInstance* arg0);
void BattleAnim_CallbackEndEffect2Descriptor19AnimatedAlphaFade_InitParticle(ParticleEffectInstance* arg0);
void BattleAnim_CallbackEndEffect2Descriptor19AnimatedAlphaFade(ParticleEffectInstance* arg0);
void BattleAnim_CallbackSharedDescriptor19RecolorAnimatedFade_InitParticle(ParticleEffectInstance* arg0);
void BattleAnim_CallbackSharedDescriptor19RecolorAnimatedFade(ParticleEffectInstance* arg0);
void BattleAnim_CallbackEndEffect86Descriptor19ModePositionedAnimFade_InitParticle(ParticleEffectInstance* arg0);
void BattleAnim_CallbackEndEffect86Descriptor19ModePositionedAnimFade(ParticleEffectInstance* arg0);
void BattleAnim_CallbackSharedDescriptor19DelayedAnimatedGrowFade_InitParticle(ParticleEffectInstance* arg0);
void BattleAnim_CallbackSharedDescriptor19DelayedAnimatedGrowFade(ParticleEffectInstance* arg0);
void BattleAnim_SetupUnusedIndexedFadeVariantA(ParticleEffectInstance* arg0);
void BattleAnim_CallbackUnusedIndexedFadeVariantA(ParticleEffectInstance* arg0);
void BattleAnim_SetupUnusedIndexedFadeVariantB(ParticleEffectInstance* arg0);
void BattleAnim_CallbackUnusedIndexedFadeVariantB(ParticleEffectInstance* arg0);
void BattleAnim_CallbackEndEffects34And53Descriptor45RotatingBounceFade_InitParticle(ParticleEffectInstance* arg0);
void BattleAnim_CallbackEndEffects34And53Descriptor45RotatingBounceFade(ParticleEffectInstance* arg0);
void BattleAnim_CallbackEndEffect27Descriptor4BGrowColorShiftFade_InitParticle(ParticleEffectInstance* arg0);
void BattleAnim_CallbackEndEffect27Descriptor4BGrowColorShiftFade(ParticleEffectInstance* arg0);
void BattleAnim_CallbackEndEffect2Descriptor4BModeColorShiftFade_InitParticle(ParticleEffectInstance* arg0);
void BattleAnim_CallbackEndEffect2Descriptor4BModeColorShiftFade(ParticleEffectInstance* arg0);
void BattleAnim_CallbackEndEffects2And27Descriptor0AFallingSparkFade_InitParticle(ParticleEffectInstance* arg0);
void BattleAnim_CallbackEndEffects2And27Descriptor0AFallingSparkFade(ParticleEffectInstance* arg0);
void BattleAnim_StartEffect15Descriptor08IndexedScaleDelayFade(void);
void BattleAnim_StartEffect2Descriptor08IndexedScaleDelayFade(void);
void SpawnTimedFireballEffect(void);
void InitParticleEffectGroup_Basic(void);
void BattleAnim_StartEffect6AnimatedScaleAndBurstEmitter(void);
void InitComplexParticleSequence(void);
void InitExplosionEffectSet(void);
void InitAdvancedParticleCombo(void);
void InitParticleEffectSet_WithTexture53(void);
void BattleAnim_StartEffect4TintDescriptor53ScalePulse(void);
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
void BattleAnim_EndEffect25Descriptor13DelegateSequence(void);
void InitParticleEffectSet_ThreeInstances(void);


void BattleAnim_SetupStartEffects18And73Descriptor11ScatterRiseFade(ParticleEffectInstance* arg0);
void BattleAnim_CallbackStartEffects18And73Descriptor11ScatterRiseFade(ParticleEffectInstance* arg0);
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
void BattleAnim_CreateSprayColumnEffect(void);
void BattleAnim_CreateSprayColumnEffectTrigger(void);
void BattleAnim_CreateStreamSprayColumnEffect(void);
void BattleAnim_CreateBurstStreamEffect(void);
void BattleAnim_CreateCollisionRandomEffect(void);
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


void BattleAnim_UnusedResetAppearanceAndAdvance(ParticleEffectInstance* arg0);
void BattleAnim_CallbackUnusedGenericFadeApproach(ParticleEffectInstance* arg0);
void BattleAnim_SetupOrphanDescriptor2BSpinFade(ParticleEffectInstance* arg0);
void BattleAnim_CallbackOrphanDescriptor2BSpinFade(ParticleEffectInstance* arg0);
void BattleAnim_SetupOrphanDescriptor2EScatterFade(ParticleEffectInstance* arg0);
void BattleAnim_CallbackOrphanDescriptor2EScatterFade(ParticleEffectInstance* arg0);
void BattleAnim_SetupEndEffect26Descriptor2CGravityScatterFall(ParticleEffectInstance* arg0);
void BattleAnim_CallbackEndEffect26Descriptor2CGravityScatterFall(ParticleEffectInstance* arg0);
void BattleAnim_SetupEndEffects85And87GravityFallDelay(ParticleEffectInstance* arg0);
void BattleAnim_CallbackEndEffects85And87GravityFallDelay(ParticleEffectInstance* arg0);
void func_84340AC4(void);
void BattleAnim_OrphanDescriptor2BAnd2EEmitterSequence(void);
void RegisterParticleEffect_ComplexMovement(void);
void RegisterParticleEffect_Burst(void);


void ParticleEffect_RegisterExplosion(void);
void ParticleEffect_RegisterSmoke(void);
void BattleAnim_StartEffect1Descriptor2FPhaseFadeOut(void);
void BattleAnim_StartEffect12DelayedModelAnim(void);
void BattleAnim_ApplySpeciesMotionOffset(ParticleEffectInstance*);
void BattleAnim_StartEffect14ModelAnimAndMoveKeyedTintParticles(void);
void ParticleEffect_RegisterCallbacks(void);
void ParticleEffect_RegisterParticleNodes(void);
void ParticleEffect_RegisterEffectE0(void);
void ParticleEffect_RegisterEffectE0Alt(void);
void ParticleEffect_RegisterEffectE0Alt2(void);
void BattleAnim_StartEffect8ModelBurstAndVerticalFade(void);
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
void BattleAnim_StartEffect10Model60AndModelAnimWait(void);
void BattleAnim_ApplySpeciesXZOffsetVariantA(ParticleEffectInstance*);
void ParticleEffect_RegisterHandler_47448(void);


void BattleAnim_SetupReflectiveCamera(void);
void BattleAnim_SelectParticleModelFrames(ParticleEffectInstance* arg0, s32 arg1);
void BattleAnim_CallbackInitModelAnimWait(ParticleEffectInstance* arg0);
void BattleAnim_CallbackInitModelAnim(ParticleEffectInstance* arg0);
void BattleAnim_CallbackStartEffects83And103ModelAlphaFadeIn(ParticleEffectInstance* arg0);
void BattleAnim_CallbackInitModelAnimWaitCleanup(ParticleEffectInstance* arg0);
void ParticleEffect_StateHandlerE(ParticleEffectInstance* arg0);
void BattleAnim_CallbackInitModelAnimMode2Update(ParticleEffectInstance* arg0);
Gfx* BattleAnim_BuildAnimatedTileDisplayList(Gfx* arg0, u8* arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5, s16 arg6, s16 arg7, s16 arg8, s16 arg9, s16 argA, s16 argB);
Gfx* BattleAnim_BuildAnimatedTileDisplayListFromStruct(Gfx* arg0, arg1_func_8434E21C* arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5, s16 arg6, s16 arg7, s16 arg8, s16 arg9, s16 argA, s16 argB);
void Gfx_SetParticlePrimEnvColors(Gfx* arg0);
void ParticleEffect_AllocateGfxIfNeeded(s32 arg0, arg1_func_84344CE8* arg1);
void Gfx_DrawParticleTextureWithParams(Gfx* arg0, arg1_func_8434E21C* arg1, UNUSED u16 arg2);
void ParticleEffect_AllocateGfxAndDraw(s32 arg0, arg1_func_84344CE8* arg1);
void BattleAnim_SetupMove86EndDescriptor24(ParticleEffectInstance* arg0);
void BattleAnim_CallbackMove86EndDescriptor24(ParticleEffectInstance* arg0);
void BattleAnim_ApplyMove86SpeciesOffset(ParticleEffectInstance* arg0);
void BattleAnim_SetupMove86StartDescriptor24(ParticleEffectInstance* arg0);
void BattleAnim_CallbackMove86StartDescriptor24(ParticleEffectInstance* arg0);
void ParticleEffect_RegisterExplosion(void);
void ParticleEffect_RegisterSmoke(void);
void BattleAnim_ApplyEffect1SpeciesMotion(ParticleEffectInstance* arg0);
void BattleAnim_SetupEffect1Descriptor2F(ParticleEffectInstance* arg0);
void BattleAnim_CallbackStartEffect1Descriptor2FPhaseFadeOut(ParticleEffectInstance* arg0);
void BattleAnim_StartEffect1Descriptor2FPhaseFadeOut(void);
void BattleAnim_ApplyModelSpeciesOffset(ParticleEffectInstance* arg0);
void BattleAnim_InitModelAnimationSlot(ParticleEffectInstance* arg0, s16 arg1);
void BattleAnim_CallbackStartEffects12And129DelayedModelAnimWait(ParticleEffectInstance* arg0);
void BattleAnim_StartEffect12DelayedModelAnim(void);
void BattleAnim_ApplySpeciesMotionOffset(ParticleEffectInstance* arg0);
void BattleAnim_StartEffect14ModelAnimAndMoveKeyedTintParticles(void);
void BattleAnim_BuildReflectiveTextureDisplayList(Gfx* arg0, s32 arg1, u16 arg2);
void BattleAnim_AllocateReflectiveTextureDisplayList(s32 arg0, arg1_func_84344CE8* arg1);
void BattleAnim_ApplyEffect125ModelScaleOffset(ParticleEffectInstance* arg0);
void BattleAnim_InitEffect125Model(ParticleEffectInstance* arg0, UNUSED s16 arg1);
void BattleAnim_CallbackStartEffect125ModelBurstEmitter(ParticleEffectInstance* arg0);
void BattleAnim_BuildEffect125DisplayList(Gfx* arg0, u16 arg1);
void BattleAnim_AllocateEffect125DisplayList(s32 arg0, arg1_func_84344CE8* arg1);
void ParticleEffect_RegisterCallbacks(void);
void BattleAnim_InitEffect65Overlay(ParticleEffectInstance* arg0);
void BattleAnim_CallbackStartEffect65Descriptors31And32FadeIn(ParticleEffectInstance* arg0);
void ParticleEffect_RegisterParticleNodes(void);
void BattleAnim_InitEffect28Overlay(ParticleEffectInstance* arg0);
void BattleAnim_CallbackStartEffects28And53And76Descriptor33FadeIn(ParticleEffectInstance* arg0);
void ParticleEffect_RegisterEffectE0(void);
void ParticleEffect_RegisterEffectE0Alt(void);
void ParticleEffect_RegisterEffectE0Alt2(void);
void BattleAnim_InitEffect8Descriptor4A(ParticleEffectInstance* arg0);
void BattleAnim_CallbackStartEffect8Descriptor4ABurstChild(ParticleEffectInstance* arg0);
void BattleAnim_InitEffect8ModelBurst(ParticleEffectInstance* arg0);
void BattleAnim_CallbackStartEffect8ModelBurstEmitter(ParticleEffectInstance* arg0);
void BattleAnim_ApplyEffect31SpeciesOffset(ParticleEffectInstance* arg0);
void BattleAnim_InitEffect31Model(ParticleEffectInstance* arg0);
void BattleAnim_CallbackMove73EndEffect31SpawnDescriptor42(ParticleEffectInstance* arg0);
void BattleAnim_StartEffect8ModelBurstAndVerticalFade(void);
void ParticleEffect_RegisterMultiple(void);
void ParticleEffect_RegisterSpecific(void);
void ParticleEffect_DrawSimple(Gfx* arg0, u8* arg1);
void ParticleEffect_CreateSimpleDL(s32 arg0, arg1_func_84344CE8* arg1);
void BattleAnim_CallbackStartEffect34SpecialModelFadeIn_InitParticle(ParticleEffectInstance* arg0);
void BattleAnim_CallbackStartEffect34SpecialModelFadeIn(ParticleEffectInstance* arg0);
void BattleAnim_CallbackEndEffect23Descriptor4AAnimatedFade_InitParticle(ParticleEffectInstance* arg0);
void BattleAnim_CallbackEndEffect23Descriptor4AAnimatedFade(ParticleEffectInstance* arg0);
void ParticleEffect_RegisterSparkle(void);
void ParticleEffect_RegisterAll(void);
void ParticleEffect_DrawNode(Gfx* arg0, s32 arg1, u16 arg2);
void ParticleEffect_CreateNodeDL(s32 arg0, arg1_func_84344CE8* arg1);
void ParticleEffect_DrawNodeVariant(Gfx* arg0, arg1_func_8434E21C* arg1, UNUSED u16 arg2);
void ParticleEffect_CreateNodeVariantDL(s32 arg0, arg1_func_84344CE8* arg1);
void ParticleEffect_DrawSimple2(Gfx* arg0, u8* arg1, UNUSED u16 arg2);
void ParticleEffect_CreateSimple2DL(s32 arg0, arg1_func_84344CE8* arg1);
void func_84345490(void);
void BattleAnim_ApplyMove146SpeciesOffset(ParticleEffectInstance* arg0);
void BattleAnim_InitMove146Model(ParticleEffectInstance* arg0);
void BattleAnim_CallbackMove146EndEffect6ModelAnimWait(ParticleEffectInstance* arg0);
void ParticleEffect_RegisterPaletteVariants(void);
void BattleAnim_InitEffect49Model(ParticleEffectInstance* arg0);
void BattleAnim_CallbackEndEffect49Model33Anim34WaitCleanup(ParticleEffectInstance* arg0);
void BattleAnim_CallbackEndEffect21ModelAnimWait(ParticleEffectInstance* arg0);
void BattleAnim_BuildEffect49DisplayList(Gfx* arg0, UNUSED s32 arg1, UNUSED u16 arg2);
void BattleAnim_AllocateEffect49DisplayList(s32 arg0, arg1_func_84344CE8* arg1);
void ParticleEffect_RegisterColorAnim(void);
void ParticleEffect_RegisterModeSpecific(void);
void BattleAnim_InitEffect40Model(ParticleEffectInstance* arg0);
void BattleAnim_CallbackStartEffect40ModelFadeCycle(ParticleEffectInstance* arg0);
void ParticleEffect_RegisterLargeExplosion(void);
void BattleAnim_InitEffect86Model(ParticleEffectInstance* arg0);
void BattleAnim_CallbackStartEffect86ModelFadeCycle(ParticleEffectInstance* arg0);
void ParticleEffect_RegisterLargeExplosionAndEffects(void);
void BattleAnim_BuildEffect63DisplayList(Gfx* arg0, s32 arg1, u16 arg2);
void BattleAnim_AllocateEffect63DisplayList(s32 arg0, arg1_func_84344CE8* arg1);
void BattleAnim_BuildEffect75DisplayList(Gfx* arg0, UNUSED s32 arg1, UNUSED u16 arg2);
void BattleAnim_AllocateEffect75DisplayList(s32 arg0, arg1_func_84344CE8* arg1);
void BattleAnim_InitEffects63And75Model(ParticleEffectInstance* arg0);
void BattleAnim_CallbackStartEffects63And75ModelAnimWait(ParticleEffectInstance* arg0);
void BattleAnim_InitEffects10And50Model(ParticleEffectInstance* arg0);
void BattleAnim_CallbackEndEffects10And50ModelAnimColorFade(ParticleEffectInstance* arg0);
void BattleAnim_ApplyEffects63And75SpeciesScaleOffset(ParticleEffectInstance* arg0);
void BattleAnim_InitEffects63And75Model38(ParticleEffectInstance* arg0);
void BattleAnim_CallbackStartEffects63And75Model38FadeIn(ParticleEffectInstance* arg0);
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
void BattleAnim_CallbackStartEffect10Model60AlphaFadeIn_InitParticle(ParticleEffectInstance* arg0);
void BattleAnim_CallbackStartEffect10Model60AlphaFadeIn(ParticleEffectInstance* arg0);
void Gfx_DrawParticleCyanEnv(Gfx* arg0, arg1_func_8434E21C* arg1, UNUSED u16 arg2);
void Particle_CreateDisplayList_CyanEnv(s32 arg0, arg1_func_84344CE8* arg1);
void Gfx_DrawParticleBluePrim(Gfx* arg0, arg1_func_8434E21C* arg1, UNUSED u16 arg2);
void Particle_CreateDisplayList_BluePrim(s32 arg0, arg1_func_84344CE8* arg1);
void BattleAnim_StartEffect10Model60AndModelAnimWait(void);
void ParticleEffect_RegisterHandler_47448(void);
void BattleAnim_ApplySpeciesXZOffsetVariantA(ParticleEffectInstance* arg0);
void BattleAnim_CallbackStartEffects50And82ModelDelay(ParticleEffectInstance* arg0);
void BattleAnim_CallbackStartEffects50And82ScalePulse_InitParticle(ParticleEffectInstance* arg0);
void BattleAnim_CallbackStartEffects50And82ScalePulse(ParticleEffectInstance* arg0);
void BattleAnim_CallbackStartEffects50And82Descriptor48AnimatedScaleFade_InitParticle(ParticleEffectInstance* arg0);
void BattleAnim_CallbackStartEffects50And82Descriptor48AnimatedScaleFade(ParticleEffectInstance* arg0);
void BattleAnim_CallbackStartEffects50And82Descriptor4AAnimatedVerticalFade_InitParticle(ParticleEffectInstance* arg0);
void BattleAnim_CallbackStartEffects50And82Descriptor4AAnimatedVerticalFade(ParticleEffectInstance* arg0);
void Gfx_DrawParticleCustomColors(Gfx* arg0, arg1_func_8434E21C* arg1, UNUSED u16 arg2);
void Particle_CreateDisplayList_CustomColors(s32 arg0, arg1_func_84344CE8* arg1);
void BattleAnim_CallbackStartEffects50And82CenterModelScalePaletteFade(ParticleEffectInstance* arg0);
void BattleAnim_CallbackStartEffects50And82OffsetModelsScalePaletteFade(ParticleEffectInstance* arg0);
void BattleAnim_CallbackEndEffects81And82ModelScalePaletteFade(ParticleEffectInstance* arg0);
void BattleAnim_CallbackEndEffects81And82Descriptor4AAnimatedColorFade_InitParticle(ParticleEffectInstance* arg0);
void BattleAnim_CallbackEndEffects81And82Descriptor4AAnimatedColorFade(ParticleEffectInstance* arg0);
void BattleAnim_CallbackEndEffects81And82Descriptor4FAnimatedPaletteFade_InitParticle(ParticleEffectInstance* arg0);
void BattleAnim_CallbackEndEffects81And82Descriptor4FAnimatedPaletteFade(ParticleEffectInstance* arg0);
void ParticleEffect_RegisterAll_48630(void);
void ParticleEffect_RegisterAll_489FC(void);
void ParticleEffect_Noop_48C6C(UNUSED s32 arg0, UNUSED s32 arg1);
void ParticleEffect_Noop_48C78(UNUSED s32 arg0, UNUSED s32 arg1);
void BattleAnim_CallbackStartEffects71And74And111SpecialModelColorCycle_InitParticle(ParticleEffectInstance* arg0);
void BattleAnim_CallbackStartEffects71And74And111SpecialModelColorCycle(ParticleEffectInstance* arg0);
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
f32 BattleAnim_GetSpeciesScaleAdjust(ParticleEffectInstance* arg0);
void BattleAnim_CallbackStartEffect69ModelPhaseWait(ParticleEffectInstance* arg0);
void ParticleEffect_RegisterHandlers_49504(void);
void BattleAnim_ApplySpeciesXZOffsetVariantB(ParticleEffectInstance* arg0);
void ParticleEffect_RegisterHandler_49628(void);
void ParticleEffect_RegisterHandlers_4967C(void);
void BattleAnim_ApplySpeciesYOffsetVariantA(ParticleEffectInstance* arg0);
void ParticleEffect_RegisterHandler_49830(void);
void ParticleEffect_RegisterHandler_498D8(void);
void BattleAnim_ApplySpeciesYOffsetVariantB(ParticleEffectInstance* arg0);
void ParticleEffect_RegisterDefaultTexture(void);
void BattleAnim_CallbackStartEffect17ModelAnimFinish_InitParticle(ParticleEffectInstance* arg0);
void BattleAnim_CallbackStartEffect17ModelAnimFinish(ParticleEffectInstance* arg0);
void BattleAnim_CallbackEndEffect7ModelScaleAlphaFade_InitParticle(ParticleEffectInstance* arg0);
void BattleAnim_CallbackEndEffect7ModelScaleAlphaFade(ParticleEffectInstance* arg0);
void Gfx_DrawParticlePaletteBased(Gfx* arg0, u8* arg1, UNUSED u16 arg2);
void Gfx_ParticlePaletteCallback(s32 arg0, arg1_func_84344CE8* arg1);
void func_84349FC8(Gfx* arg0, UNUSED arg1_func_8434E21C* arg1, UNUSED u16 arg2);
void Gfx_ParticlePaletteCallback2(s32 arg0, arg1_func_84344CE8* arg1);
s16 BattleAnim_GetMoveKeyedModelVariantIndex(void);
s16 BattleAnim_GetMoveKeyedTintRampParam(void);
s16 BattleAnim_GetMoveKeyedTrailVariantParam(void);
void BattleAnim_StartEffect17ModelAnimFinish(void);
void ParticleEffect_PaletteMultiBurst(void);
f32 BattleAnim_GetSpeciesScaleAndApplyYOffset(ParticleEffectInstance* arg0);
void Gfx_ParticleTextureTileCallback(Gfx* arg0, arg1_func_8434E21C* arg1, UNUSED u16 arg2);
void Gfx_ParticleTextureTileCallback2(s32 arg0, arg1_func_84344CE8* arg1);
void Gfx_ParticleRedPrimCallback(Gfx* arg0, UNUSED arg1_func_8434E21C* arg1, UNUSED u16 arg2);
void Gfx_ParticleRedPrimCallback2(s32 arg0, arg1_func_84344CE8* arg1);
void ParticleEffect_SimpleBurst(void);
void BattleAnim_StartEffect39Descriptor26ModelAnimWaitSequence(void);
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
f32 BattleAnim_GetSpeciesScaleAndOffset(ParticleEffectInstance* arg0);
void ParticleEffect_SimpleBurst2(void);
void ParticleEffect_SimpleBurst3(void);
void BattleAnim_ApplySpeciesYOffsetVariantC(ParticleEffectInstance* arg0);
void BattleAnim_CallbackStartEffects95To97EndEffects62And63ModelFadeIn_InitParticle(ParticleEffectInstance* arg0);
void BattleAnim_CallbackStartEffects95To97EndEffects62And63ModelFadeIn(ParticleEffectInstance* arg0);
void Gfx_PaletteParticleDL(Gfx* arg0, u8* arg1, UNUSED u16 arg2);
void Gfx_PaletteParticleDLCallback(s32 arg0, arg1_func_84344CE8* arg1);
void ParticleEffect_PaletteMultiBurst2(void);
void ParticleEffect_PaletteMultiBurst3(void);
void ParticleEffect_PaletteScriptBurst(void);
void ParticleEffect_PaletteBurst4(void);
void ParticleEffect_PaletteBurst5(void);
void ParticleEffect_FireworkBurst(void);
void BattleAnim_CallbackStartEffects21And93ModelAlphaAnchorFollow_InitParticle(ParticleEffectInstance* arg0);
void BattleAnim_CallbackStartEffects21And93ModelAlphaAnchorFollow(ParticleEffectInstance* arg0);
void BattleAnim_CallbackEndEffect60Model42AnimC2RotationYFollow_InitParticle(ParticleEffectInstance* arg0);
void BattleAnim_CallbackEndEffect60Model42AnimC2RotationYFollow(ParticleEffectInstance* arg0);
void Gfx_WaterAnimPrimEnvDL(Gfx* arg0, u8 arg1, UNUSED u16 arg2);
void Gfx_WaterAnimPrimEnvDLCallback(s32 arg0, arg1_func_84344CE8* arg1);
void ParticleEffect_WaterAnimBurst(void);
void ParticleEffect_WaterAnimBurst2(void);
void ParticleEffect_WaterAnimFirework(void);
void ParticleEffect_WaterAnimFirework2(void);
void Gfx_WaterAnimDL(Gfx* arg0, u8* arg1, UNUSED u16 arg2);
void Gfx_WaterAnimDLCallback(s32 arg0, arg1_func_84344CE8* arg1);
f32 BattleAnim_GetSpeciesScaleAdjustSmall(ParticleEffectInstance* arg0);
void ParticleEffect_BasicMultiBurst(void);
void ParticleEffect_FireballBurst(void);
void ParticleEffect_BasicMultiBurst2(void);
void ParticleEffect_AdvancedMultiBurst(void);
void ParticleEffect_SimpleBurst4(void);
void BattleAnim_CallbackStartEffect101EndEffect65Descriptor4ABurstChild_InitParticle(ParticleEffectInstance* arg0);
void BattleAnim_CallbackStartEffect101EndEffect65Descriptor4ABurstChild(ParticleEffectInstance* arg0);
void BattleAnim_CallbackStartEffect101ModelBurstEmitter_InitParticle(ParticleEffectInstance* arg0);
void BattleAnim_CallbackStartEffect101ModelBurstEmitter(ParticleEffectInstance* arg0);
void ParticleEffect_RotationEntry(void);
void BattleAnim_CallbackMove140EndEffect65EmitDescriptor4A_InitParticle(ParticleEffectInstance* arg0);
void BattleAnim_CallbackMove140EndEffect65EmitDescriptor4A(ParticleEffectInstance* arg0);
void ParticleEffect_FireworkEntry(void);
void BattleAnim_CallbackStartEffect49EndEffect66ModelFadeIn_InitParticle(ParticleEffectInstance* arg0);
void BattleAnim_CallbackStartEffect49EndEffect66ModelFadeIn(ParticleEffectInstance* arg0);
void Gfx_SimpleNodeDL(Gfx* arg0, arg1_func_8434E21C* arg1, UNUSED u16 arg2);
void Gfx_SimpleNodeDLCallback(s32 arg0, arg1_func_84344CE8* arg1);
void ParticleEffect_SimpleNodeEntry(void);
void ParticleEffect_SimpleNodeBurst(void);
void BattleAnim_CallbackEndEffects73And74DefaultDescriptorFade(ParticleEffectInstance* arg0);
void ParticleEffect_AlphaBurst(void);
void ParticleEffect_AlphaBurst2(void);
void ParticleEffect_AlphaFirework(void);
void ParticleEffect_AlphaFirework2(void);
f32 BattleAnim_GetSpeciesScaleAdjustTiny(ParticleEffectInstance* arg0);
void BattleAnim_StartEffect3ModelTintAndVerticalFade(void);
void BattleAnim_EndEffect85TintAndDescriptorMode2Sequence(void);
void ParticleEffect_InitFire(void);
void ParticleEffect_InitSmoke(void);
void ParticleEffect_PlaySoundAndReset(void);
void ParticleEffect_DrawQuad(Gfx* arg0, arg1_func_8434E21C* arg1, UNUSED u16 arg2);
void ParticleEffect_AllocateDisplayList(s32 arg0, arg1_func_84344CE8* arg1);
void BattleAnim_EndEffect72Descriptor20ModelAnimWaitSequence(void);
void ParticleEffect_TriggerSpecial(void);
void BattleAnim_CallbackEndEffect76DefaultDescriptorModelFade(ParticleEffectInstance* arg0);
void ParticleEffect_TriggerAnother(void);
void ParticleEffect_TriggerDefault1(void);
void ParticleEffect_TriggerDefault2(void);
void ParticleEffect_TriggerDefault3(void);
void ParticleEffect_TriggerDefault4(void);
void BattleAnim_CallbackStartEffects118And119ModelPalettePulse(ParticleEffectInstance* arg0);
void ParticleEffect_CreateWithCallback(void);
void ParticleEffect_CreateCallback(void);
void BattleAnim_CallbackEndEffect79DefaultDescriptorPaletteFade(ParticleEffectInstance* arg0);
void ParticleEffect_CreateColorVariant(void);
void ParticleEffect_SetMode(void);
void BattleAnim_CallbackStartEffects127And128Descriptor39ScaleFade_InitParticle(ParticleEffectInstance* arg0);
void BattleAnim_CallbackStartEffects127And128Descriptor39ScaleFade(ParticleEffectInstance* arg0);
void ParticleEffect_CreateVariant45(void);
void ParticleEffect_CreateVariant47(void);
void ParticleEffect_CreateTypeX(void);
void ParticleEffect_CreateSmoke(void);
void ParticleEffect_CreateSmokeHighPriority(void);
void BattleAnim_CallbackStartEffect132Descriptor39DelayedRiseFade_InitParticle(ParticleEffectInstance* arg0);
void BattleAnim_CallbackStartEffect132Descriptor39DelayedRiseFade(ParticleEffectInstance* arg0);
void ParticleEffect_CreateDual(void);
void BattleAnim_CallbackSharedDescriptor29ScaleAnimFade_InitParticle(ParticleEffectInstance* arg0);
void BattleAnim_CallbackSharedDescriptor29ScaleAnimFade(ParticleEffectInstance* arg0);
void BattleAnim_CallbackEndEffect3Descriptor29DirectionalScaleFade_InitParticle(ParticleEffectInstance* arg0);
void BattleAnim_CallbackEndEffect3Descriptor29DirectionalScaleFade(ParticleEffectInstance* arg0);
void BattleAnim_CallbackSharedDescriptor29DirectionalScatterFade_InitParticle(ParticleEffectInstance* arg0);
void BattleAnim_CallbackSharedDescriptor29DirectionalScatterFade(ParticleEffectInstance* arg0);
void BattleAnim_CallbackSharedOwnerKeyedGrowColorFade_InitParticle(ParticleEffectInstance* arg0);
void BattleAnim_CallbackSharedOwnerKeyedGrowColorFade(ParticleEffectInstance* arg0);
void BattleAnim_CallbackSharedOwnerKeyedGrowColorAlphaFade_InitParticle(ParticleEffectInstance* arg0);
void BattleAnim_CallbackSharedOwnerKeyedGrowColorAlphaFade(ParticleEffectInstance* arg0);
void BattleAnim_CallbackSharedOwnerKeyedAnimGrowFade_InitParticle(ParticleEffectInstance* arg0);
void BattleAnim_CallbackSharedOwnerKeyedAnimGrowFade(ParticleEffectInstance* arg0);
void BattleAnim_CallbackEndEffect88Descriptor2AOwnerKeyedAnimGrowFade_InitParticle(ParticleEffectInstance* arg0);
void BattleAnim_CallbackEndEffect88Descriptor2AOwnerKeyedAnimGrowFade(ParticleEffectInstance* arg0);
void BattleAnim_CallbackEndEffects39And41And45And46And83Descriptor3DMetadataBurstChild_InitParticle(ParticleEffectInstance* arg0);
void BattleAnim_CallbackEndEffects39And41And45And46And83Descriptor3DMetadataBurstChild(ParticleEffectInstance* arg0);
void BattleAnim_CallbackSharedTieredSmallRiseImpulseFade_InitParticle(ParticleEffectInstance* arg0);
void BattleAnim_CallbackSharedTieredSmallRiseImpulseFade(ParticleEffectInstance* arg0);
void BattleAnim_CallbackSharedTieredLargeRiseImpulseFade_InitParticle(ParticleEffectInstance* arg0);
void BattleAnim_CallbackSharedTieredLargeRiseImpulseFade(ParticleEffectInstance* arg0);
void BattleAnim_CallbackStartEffect31Descriptor49TieredRiseImpulseFade_InitParticle(ParticleEffectInstance* arg0);
void BattleAnim_CallbackStartEffect31Descriptor49TieredRiseImpulseFade(ParticleEffectInstance* arg0);
void BattleAnim_SetupUnusedRiseImpulseVariant(ParticleEffectInstance* arg0);
void BattleAnim_CallbackUnusedRiseImpulseVariant(ParticleEffectInstance* arg0);
void BattleAnim_CallbackEndEffect55Descriptor49RiseGravityFade_InitParticle(ParticleEffectInstance* arg0);
void BattleAnim_CallbackEndEffect55Descriptor49RiseGravityFade(ParticleEffectInstance* arg0);
void BattleAnim_CallbackSharedDescriptors3EAnd3FAnimatedRiseFade_InitParticle(ParticleEffectInstance* arg0);
void BattleAnim_CallbackSharedDescriptors3EAnd3FAnimatedRiseFade(ParticleEffectInstance* arg0);
void BattleAnim_CallbackEndEffect67Descriptor3DAnimatedGravityFade_InitParticle(ParticleEffectInstance* arg0);
void BattleAnim_CallbackEndEffect67Descriptor3DAnimatedGravityFade(ParticleEffectInstance* arg0);
void BattleAnim_CallbackOrphanDescriptor34ColorFadeDetach_InitParticle(ParticleEffectInstance* arg0);
void BattleAnim_CallbackOrphanDescriptor34ColorFadeDetach(ParticleEffectInstance* arg0);
void BattleAnim_CallbackSharedDescriptor36ScaleAlphaFade_InitParticle(ParticleEffectInstance* arg0);
void BattleAnim_CallbackSharedDescriptor36ScaleAlphaFade(ParticleEffectInstance* arg0);
void BattleAnim_SetupUnusedGlitterVariant(ParticleEffectInstance* arg0);
void BattleAnim_CallbackUnusedGlitterVariant(ParticleEffectInstance* arg0);
void BattleAnim_CallbackEndEffects37And38Descriptor38BurstChild_InitParticle(ParticleEffectInstance* arg0);
void BattleAnim_CallbackEndEffects37And38Descriptor38BurstChild(ParticleEffectInstance* arg0);
void BattleAnim_CallbackSharedDescriptor3DAnimatedColorMotion_InitParticle(ParticleEffectInstance* arg0);
void BattleAnim_CallbackSharedDescriptor3DAnimatedColorMotion(ParticleEffectInstance* arg0);
void BattleAnim_CallbackEndEffect52Descriptor42BurstChild_InitParticle(ParticleEffectInstance* arg0);
void BattleAnim_CallbackEndEffect52Descriptor42BurstChild(ParticleEffectInstance* arg0);
void BattleAnim_SetupEndEffect52DefaultBurstChild(ParticleEffectInstance* arg0);
void BattleAnim_CallbackEndEffect52DefaultBurstEmitter(ParticleEffectInstance* arg0);
void BattleAnim_SetupSharedScalePulseFallSetup(ParticleEffectInstance* arg0);
void BattleAnim_CallbackSharedDescriptors42And44ScaleFall(ParticleEffectInstance* arg0);
void BattleAnim_CallbackEndEffect23Descriptor44ScalePulse_InitParticle(ParticleEffectInstance* arg0);
void BattleAnim_CallbackEndEffect23Descriptor44ScalePulse(ParticleEffectInstance* arg0);
void BattleAnim_CallbackEndEffect67Descriptor42ScalePulseFallFade(ParticleEffectInstance* arg0);
void BattleAnim_CallbackEndEffect43Descriptor40DelayedAnimFade_InitParticle(ParticleEffectInstance* arg0);
void BattleAnim_CallbackEndEffect43Descriptor40DelayedAnimFade(ParticleEffectInstance* arg0);
void BattleAnim_CallbackSharedDescriptor34DelayedFrameMotion_InitParticle(ParticleEffectInstance* arg0);
void BattleAnim_CallbackSharedDescriptor34DelayedFrameMotion(ParticleEffectInstance* arg0);
void BattleAnim_CallbackEndEffects39And41And45And46And83Descriptor34BurstEmitter_InitParticle(ParticleEffectInstance* arg0);
void BattleAnim_CallbackEndEffects39And41And45And46And83Descriptor34BurstEmitter(ParticleEffectInstance* arg0);
void BattleAnim_CallbackEndEffects37And38Descriptor34BurstEmitter_InitParticle(ParticleEffectInstance* arg0);
s32 BattleAnim_CallbackEndEffects37And38Descriptor34BurstEmitter(ParticleEffectInstance* arg0);
void BattleAnim_CallbackStartEffect56Descriptor40AnimScaleFade_InitParticle(ParticleEffectInstance* arg0);
void BattleAnim_CallbackStartEffect56Descriptor40AnimScaleFade(ParticleEffectInstance* arg0);
void BattleAnim_CallbackStartEffect56Descriptor46AnimColorImpulseFade_InitParticle(ParticleEffectInstance* arg0);
void BattleAnim_CallbackStartEffect56Descriptor46AnimColorImpulseFade(ParticleEffectInstance* arg0);
void BattleAnim_CallbackStartEffect73Descriptor15AnimatedColorImpulseFade_InitParticle(ParticleEffectInstance* arg0);
void BattleAnim_CallbackStartEffect73Descriptor15AnimatedColorImpulseFade(ParticleEffectInstance* arg0);
void BattleAnim_RecolorParticleByQueuedMoveId(ParticleEffectInstance* arg0);
void BattleAnim_CallbackStartEffects28And53And65And76Descriptor47AnimatedScaleMotion_InitParticle(ParticleEffectInstance* arg0);
void BattleAnim_CallbackStartEffects28And53And65And76Descriptor47AnimatedScaleMotion(ParticleEffectInstance* arg0);
void BattleAnim_CallbackStartEffect81Descriptor4BGrowColorShiftFade_InitParticle(ParticleEffectInstance* arg0);
void BattleAnim_CallbackStartEffect81Descriptor4BGrowColorShiftFade(ParticleEffectInstance* arg0);
void BattleAnim_CallbackStartEffect81Descriptor3DRisingAnimFade_InitParticle(ParticleEffectInstance* arg0);
void BattleAnim_CallbackStartEffect81Descriptor3DRisingAnimFade(ParticleEffectInstance* arg0);
void BattleAnim_InitSharedVerticalFadeParticle_ApplySpeciesOffset(ParticleEffectInstance* arg0);
void BattleAnim_InitSharedVerticalFadeParticle(ParticleEffectInstance* arg0);
void BattleAnim_CallbackSharedAnimatedVerticalFade(ParticleEffectInstance* arg0);
void BattleAnim_ApplySpeciesKeyedSpawnOffset(ParticleEffectInstance* arg0);
void BattleAnim_CallbackEndEffect16MultiDescriptorAnimatedFallFade(ParticleEffectInstance* arg0);
void BattleAnim_CallbackStartEffect69EndEffect78Descriptor4AFallFade(ParticleEffectInstance* arg0);
void BattleAnim_CallbackStartEffect69EndEffect78Descriptor30YThresholdFall(ParticleEffectInstance* arg0);
void BattleAnim_CallbackStartEffect101Descriptor3DMetadataBurstChild_InitParticle(ParticleEffectInstance* arg0);
void BattleAnim_CallbackStartEffect101Descriptor3DMetadataBurstChild(ParticleEffectInstance* arg0);
void BattleAnim_CallbackDescriptor50BurstChild_InitParticle(ParticleEffectInstance* arg0);
void BattleAnim_CallbackDescriptor50BurstChild(ParticleEffectInstance* arg0);
void BattleAnim_CallbackDescriptor50BurstEmitter_InitParticle(ParticleEffectInstance* arg0);
void BattleAnim_CallbackDescriptor50BurstEmitter(ParticleEffectInstance* arg0);
void func_843553B4(void);
void BattleAnim_CallbackUnusedFallingTrailVariant(ParticleEffectInstance* arg0);
void BattleAnim_CallbackSharedDescriptor3CExpandingFadeIn_InitParticle(ParticleEffectInstance* arg0);
void BattleAnim_CallbackSharedDescriptor3CExpandingFadeIn(ParticleEffectInstance* arg0);
void BattleAnim_CallbackStartEffects29And60And104And110Descriptor44BurstChild_InitParticle(ParticleEffectInstance* arg0);
void BattleAnim_CallbackStartEffects29And60And104And110Descriptor44BurstChild(ParticleEffectInstance* arg0);
void BattleAnim_CallbackStartEffects29And60And104And110DefaultDescriptorBurstEmitter_InitParticle(ParticleEffectInstance* arg0);
void BattleAnim_CallbackStartEffects29And60And104And110DefaultDescriptorBurstEmitter(ParticleEffectInstance* arg0);
void BattleAnim_CallbackDescriptor26BurstChild_InitParticle(ParticleEffectInstance* arg0);
void BattleAnim_CallbackDescriptor26BurstChild(ParticleEffectInstance* arg0);
void BattleAnim_CallbackDescriptor26BurstEmitter_InitParticle(ParticleEffectInstance* arg0);
void BattleAnim_CallbackDescriptor26BurstEmitter(ParticleEffectInstance* arg0);
void BattleAnim_SetupUnusedGrowingSparkVariant(ParticleEffectInstance* arg0);
void BattleAnim_CallbackUnusedGrowingSparkVariant(ParticleEffectInstance* arg0);
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
void BattleAnim_OrphanDescriptor34Emitter(void);
void ParticleEffect_AdditionalSetupA(void);
void ParticleEffect_AdditionalSetupB(void);
void ParticleEffect_CombinedSetupA(void);
void ParticleEffect_CombinedSetupB(void);
void BattleAnim_EndEffects41And83Descriptor34BurstSequence(void);
void BattleAnim_StartEffect7GlobalTintFade(void);
void ParticleEffect_MultiHandleSetup(void);
void BattleAnim_StartEffect137Descriptor3FRisingFade(void);
void ParticleEffect_TextureNodeSetup(void);
void ParticleEffect_HandleStateSetup(void);
void ParticleEffect_HandleCollisionSetup(void);
void BattleAnim_StartEffect13SecondaryOwnerSpeciesBranch(void);
void ParticleEffect_DynamicCollisionSetup(void);
void ParticleEffect_ConditionalStateSetup(void);
void ParticleEffect_CollisionResponseSwitch(void);
void ParticleEffect_CollisionAndBurstSetup(void);
void ParticleEffect_StateCollisionSetupA(void);
void ParticleEffect_StateCollisionSetupB(void);
void ParticleEffect_AdditionalNodeSetup(void);
void ParticleEffect_SpecialCollisionSetup(void);
void BattleAnim_StartEffect11GlobalTintFade(void);
void ParticleEffect_MultiTextureSetup(void);
void ParticleEffect_SmallNodeSetupB(void);
void BattleAnim_EndEffect26DelayedDescriptor29ScatterSequence(void);
void ParticleEffect_ModeSpecificSetup(void);
void ParticleEffect_ComplexNodeSetup(void);
void ParticleEffect_SimpleNodeSetup(void);
void ParticleEffect_AdvancedModeSetup(void);
void BattleAnim_StartEffect16TintDescriptor34Sequence(void);
void ParticleEffect_FullSetupB(void);
void ParticleEffect_FinalSetupA(void);
void ParticleEffect_FinalSetupB(void);
void ParticleEffect_FinalSetupC(void);
void ParticleEffect_AdditionalNodeA(void);
void BattleAnim_EndEffect58Descriptor4AAnd51Sequence(void);
void BattleAnim_EndEffectUnusedVerticalFadeAndDelayedFrameSequence(void);
void BattleAnim_StartEffects87And88Descriptor3DVerticalFadeSequence(void);
void ParticleEffect_MultiNodeD(void);
void BattleAnim_SpawnDefaultDescriptorBurstEmitterSequence(s32 arg0);
void ParticleEffect_GroupSetupA(void);
void BattleAnim_StartEffect105TintDefaultBurstAndDescriptor3CSequence(void);
void ParticleEffect_SimpleGroupSetup(void);
void ParticleEffect_ComplexGroupSetup(void);
void ParticleEffect_FinalGroupSetup(void);


void BattleAnim_RenderNop1(void);
void func_84358FF8(void);
void BattleAnim_DrawFullScreenColorOverlay(u8, u8, u8, u8);
void BattleAnim_RenderEffectsFrame(CameraStruct*);


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
void BattleAnim_CalcVectorAtToDm(f32* arg0, f32* arg1, f32* arg2, f32* arg3, f32* arg4, f32* arg5);
void BattleAnim_CalcVectorAtToDm2(f32* arg0, f32* arg1, f32* arg2, f32* arg3, f32* arg4, f32* arg5);
void BattleAnim_ResetSharedEffectMatrix(void);
void BattleAnim_Effect5RibbonMesh_Init(void);
s32 BattleAnim_Effect5RibbonMesh_Update(void);
void BattleAnim_Effect5RibbonMesh_Draw(void);
void BattleAnim_EndEffect1RibbonMesh_Init(void);
s32 BattleAnim_EndEffect1RibbonMesh_Update(void);
void BattleAnim_EndEffect1RibbonMesh_Draw(void);
void BattleAnim_EndEffect19RibbonMesh_Init(void);
s32 BattleAnim_EndEffect19RibbonMesh_Update(void);
void BattleAnim_EndEffect19RibbonMesh_Draw(void);
void BattleAnim_Effect54RibbonMesh_Init(void);
s32 BattleAnim_Effect54RibbonMesh_Update(void);
void BattleAnim_Effect54RibbonMesh_Draw(void);
void BattleAnim_StartEffect34TerrainGrid_Init(void);
s32 BattleAnim_StartEffect34TerrainGrid_Update(void);
void BattleAnim_StartEffect34TerrainGrid_Draw(void);
void BattleAnim_EndEffect16_NoOpInit(void);
s32 BattleAnim_EndEffect16_CompleteImmediately(void);
void BattleAnim_EndEffect16_NoOpDraw(void);
void BattleAnim_StartEffect19Radial20_EmitVariantD(void);
void BattleAnim_StartEffect19Radial20_Init(void);
s32 BattleAnim_StartEffect19Radial20_Update(void);
void BattleAnim_StartEffect19Radial20_Draw(void);
void BattleAnim_EndEffect9Radial20_Init(void);
s32 BattleAnim_EndEffect9Radial20_Update(void);
void BattleAnim_EndEffect9Radial20_Draw(void);
void BattleAnim_StartEffect7TexturedRibbonSheet_Emit(void);
void BattleAnim_StartEffect7TexturedRibbonSheet_Init(void);
s32 BattleAnim_StartEffect7TexturedRibbonSheet_Update(void);
void BattleAnim_StartEffect7TexturedRibbonSheet_Draw(void);
void BattleAnim_StartEffect33Radial20_EmitVariantC(void);
void BattleAnim_StartEffect33Radial20_Init(void);
s32 BattleAnim_StartEffect33Radial20_Update(void);
void BattleAnim_StartEffect33Radial20_Draw(void);
void BattleAnim_EndEffect32Radial20_Init(void);
s32 BattleAnim_EndEffect32Radial20_Update(void);
void BattleAnim_EndEffect32Radial20_Draw(void);
void BattleAnim_EndEffect33Radial20_Init(void);
s32 BattleAnim_EndEffect33Radial20_Update(void);
void BattleAnim_EndEffect33Radial20_Draw(void);
void BattleAnim_StartEffect98Radial20_EmitVariantD(void);
void BattleAnim_StartEffect98Radial20_Init(void);
s32 BattleAnim_StartEffect98Radial20_Update(void);
void BattleAnim_StartEffect98Radial20_Draw(void);
void BattleAnim_StartEffect11Trail50Alt_Init(void);
s32 BattleAnim_StartEffect11Trail50Alt_Update(void);
void BattleAnim_StartEffect11Trail50Alt_Draw(void);
void BattleAnim_StartEffect57Trail50_Init(void);
s32 BattleAnim_StartEffect57Trail50_Update(void);
void BattleAnim_StartEffect57Trail50_Draw(void);
void BattleAnim_StartEffect42Trail40_Init(void);
s32 BattleAnim_StartEffect42Trail40_Update(void);
void BattleAnim_StartEffect42Trail40_Draw(void);
void BattleAnim_StartEffect43Trail40Variant_Init(void);
s32 BattleAnim_StartEffect43Trail40Variant_Update(void);
void BattleAnim_StartEffect43Trail40Variant_Draw(void);
void BattleAnim_StartEffect44Trail40GridAlt_Init(void);
s32 BattleAnim_StartEffect44Trail40GridAlt_Update(void);
void BattleAnim_StartEffect44Trail40GridAlt_Draw(void);
void BattleAnim_StartEffect45FourStreamTrail_Init(void);
s32 BattleAnim_StartEffect45FourStreamTrail_Update(void);
void BattleAnim_StartEffect45FourStreamTrail_Draw(void);
void BattleAnim_StartEffect62OwnerLinkedFourStream_Init(void);
s32 BattleAnim_StartEffect62OwnerLinkedFourStream_Update(void);
void BattleAnim_StartEffect62OwnerLinkedFourStream_Draw(void);
void BattleAnim_StartEffect67OwnerAnchoredFourStream_Init(void);
s32 BattleAnim_StartEffect67OwnerAnchoredFourStream_Update(void);
void BattleAnim_StartEffect67OwnerAnchoredFourStream_Draw(void);
void BattleAnim_StartEffect78Radial20_EmitVariantA(void);
void BattleAnim_StartEffect78Radial20_Init(void);
s32 BattleAnim_StartEffect78Radial20_Update(void);
void BattleAnim_StartEffect78Radial20_Draw(void);
void BattleAnim_StartEffect26DoubleTextureTrail_Seed(void);
void BattleAnim_StartEffect26DoubleTextureTrail_Init(void);
s32 BattleAnim_StartEffect26DoubleTextureTrail_Update(void);
void BattleAnim_StartEffect26DoubleTextureTrail_Draw(void);
void BattleAnim_StartEffect47SixSlotTrail_Seed(void);
void BattleAnim_StartEffect47SixSlotTrail_Init(void);
s32 BattleAnim_StartEffect47SixSlotTrail_Update(void);
void BattleAnim_StartEffect47SixSlotTrail_Draw(void);
void BattleAnim_StartEffect4DoubleTextureTrail_Seed(void);
void BattleAnim_StartEffect4DoubleTextureTrail_Init(void);
s32 BattleAnim_StartEffect4DoubleTextureTrail_Update(void);
void BattleAnim_StartEffect4DoubleTextureTrail_Draw(void);
void BattleAnim_StartEffect77DoubleTextureTrail_Seed(void);
void BattleAnim_StartEffect77DoubleTextureTrail_Init(void);
s32 BattleAnim_StartEffect77DoubleTextureTrail_Update(void);
void BattleAnim_StartEffect77DoubleTextureTrail_Draw(void);
void BattleAnim_StartEffect70DoubleTextureTrail_Seed(void);
void BattleAnim_StartEffect70DoubleTextureTrail_Init(void);
s32 BattleAnim_StartEffect70DoubleTextureTrail_Update(void);
void BattleAnim_StartEffect70DoubleTextureTrail_Draw(void);
void BattleAnim_StartEffect39DoubleTextureTrail_Seed(void);
void BattleAnim_StartEffect39SixSlotTrail_Seed(void);
void BattleAnim_StartEffect39CombinedTrail_Init(void);
s32 BattleAnim_StartEffect39CombinedTrail_Update(void);
void BattleAnim_StartEffect39CombinedTrail_Draw(void);


void RibbonMesh_Init(void);
void RibbonMesh_Configure(unk_D_843925E0* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9);
void RibbonMesh_Spawn(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, s32 arg5);
void RibbonMesh_UpdateEnvAlpha(unk_D_843925E0* arg0);
s32 RibbonMesh_Update(unk_D_843925E0* arg0);
s32 RibbonMesh_UpdatePool(void);
Gfx* RibbonMesh_Draw(Gfx* arg0, unk_D_843925E0* arg1);
Gfx* RibbonMesh_DrawPool(Gfx* arg0);
void TerrainGrid_BuildCameraBounds(unk_D_843975E8* arg0, f32 arg1);
f32 TerrainGrid_SampleHeightAndSlope(f32 arg0, f32 arg1, f32* arg2);
s32 TerrainGrid_UpdateWaves(void);
void TerrainGrid_Init(s32 arg0, s16 arg1, s16 arg2);
s32 TerrainGrid_Update(void);
Gfx* TerrainGrid_Draw(Gfx* arg0);


void Radial20_Init(f32 arg0, f32 arg1, f32 arg2, f32 arg3, u8 arg4, u8 arg5, u8 arg6, u8 arg7, u8 arg8, u8 arg9);
f32 Strip400_GetTailFadeRatio(void);
s32 Radial20_Update(void);
Gfx* Strip400_Draw(Gfx* arg0);
void Radial20_ResetPool(void);
void Radial20_VariantA(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, s16 arg6, u8 arg7, u8 arg8, u8 arg9, u8 argA, f32 argB, f32 argC, f32 argD, s16 argE);
void Radial20_VariantB(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, s16 arg6, u8 arg7, u8 arg8, u8 arg9, u8 argA, f32 argB, f32 argC, f32 argD, s16 argE);
void Radial20_VariantC(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, s16 arg6, u8 arg7, u8 arg8, u8 arg9, u8 argA, u8 argB, u8 argC, u8 argD, f32 argE, f32 argF, f32 arg10, s16 arg11);
void Radial20_VariantD(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, s16 arg6, u8 arg7, u8 arg8, u8 arg9, u8 argA, u8 argB, u8 argC, u8 argD, f32 argE, f32 argF, f32 arg10, s16 arg11);
void Radial20_VariantE(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, s16 arg6, u8 arg7, u8 arg8, u8 arg9, u8 argA, f32 argB, f32 argC, f32 argD, s16 argE);
void Radial20_RotateVertexOffset(f32 arg0, UNUSED Vec3f* arg1, Vec3f* arg2, f32 arg3, UNUSED f32 arg4, UNUSED f32 arg5, UNUSED f32 arg6);
void Radial20_UpdateNode(unk_D_84398F50* arg0);
s32 Radial20_IsComplete(void);
Gfx* func_84362084(Gfx* arg0);


void Trail40_Init(s16 arg0);
void Trail40_Start(s32 arg0, s32 arg1);
void Trail40Node_FillVertex(WaterSurfaceVertex* arg0, Vtx* arg1);
s32 Trail40_IsComplete(void);
void Trail40_Reset(void);
Gfx* Trail40_Draw(Gfx* arg0);


void Trail40Variant_ApplyRippleAtPoint(s16 arg0, s16 arg1);
void Trail40Variant_InitPool(s16 arg0);
void Trail40Variant_UpdateNodes(s32 arg0, s32 arg1);
void Trail40Variant_WriteVertex(unk_D_8439E680_0014* arg0, Vtx* arg1);
s32 Trail40Variant_AdvanceTimer(void);
void Trail40Variant_SetupCameraTransform(void);
Gfx* Trail40Variant_BuildGfx(Gfx* arg0);


void Trail40GridAlt_Init(s16 arg0);
void Trail40GridAlt_Start(s32 arg0, s32 arg1);
void Trail40GridAlt_FillVertex(WaterSurfaceVertex* arg0, Vtx* arg1);
s32 Trail40GridAlt_IsComplete(void);
void Trail40GridAlt_Reset(void);
Gfx* Trail40GridAlt_Draw(Gfx* arg0);


void TexturedRibbonSheet_Init(void);
void TexturedRibbonSheet_Start(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, u8 arg6, u8 arg7, u8 arg8, u8 arg9, f32 argA, s16 argB);
void TexturedRibbonSheet_Update(f32 arg0, Vec3f* arg1, f32 arg2);
void TexturedRibbonSheet_UpdateRecord(unk_D_843A22C0* arg0);
s32 TexturedRibbonSheet_IsComplete(void);
Gfx* TexturedRibbonSheet_Draw(Gfx* arg0);


Gfx* Gfx_DrawThickLine(Gfx* arg0, Vec3f* arg1, Vec3f* arg2, Vec3f* arg3, f32 arg4, u8 arg5, u8 arg6, u8 arg7, u8 arg8);


void FourStreamTrail_Init(void);
void FourStreamTrail_Start(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, u8 arg6, u8 arg7, u8 arg8, u8 arg9, f32 argA, f32 argB, f32 argC, s16 argD);
void FourStreamTrail_Update(f32 arg0, Vec3f* arg1, f32 arg2, f32 arg3);
void FourStreamTrail_UpdateNodeChain(WaterParticleEmitter* arg0);
s32 FourStreamTrail_IsComplete(void);
Gfx* FourStreamTrail_Draw(Gfx* arg0);


void OwnerLinkedFourStream_Init(void);
void OwnerLinkedFourStream_Start(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, u8 arg6, u8 arg7, u8 arg8, u8 arg9, f32 argA, f32 argB, f32 argC, s16 argD);
void OwnerLinkedFourStream_Update(f32 arg0, Vec3f* arg1, f32 arg2);
void OwnerLinkedFourStream_UpdateNodeChain(ParticleEmitter* arg0);
s32 OwnerLinkedFourStream_IsComplete(void);
Gfx* OwnerLinkedFourStream_Draw(Gfx* arg0);


void OwnerAnchoredFourStream_Init(void);
void OwnerAnchoredFourStream_Start(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, u8 arg6, u8 arg7, u8 arg8, u8 arg9, f32 argA, f32 argB, f32 argC, s16 argD);
void OwnerAnchoredFourStream_Update(f32 arg0, Vec3f* arg1, f32 arg2);
void OwnerAnchoredFourStream_UpdateNodeChain(unk_D_843ACA10* arg0);
s32 OwnerAnchoredFourStream_IsComplete(void);
Gfx* OwnerAnchoredFourStream_Draw(Gfx* arg0);


void Trail50Effect_Init(void);
void Trail50Effect_Start(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, u8 arg6, u8 arg7, u8 arg8, u8 arg9, f32 argA, f32 argB, f32 argC, s16 argD);
void Trail50Effect_Update(f32 arg0, Vec3f* arg1, f32 arg2);
void Trail50Effect_AdvanceNodes(unk_D_843ADA80* arg0);
s32 Trail50Effect_IsComplete(void);
Gfx* Trail50Effect_Draw(Gfx* arg0);


void Trail50EffectAlt_Init(void);
void Trail50EffectAlt_Start(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, u8 arg6, u8 arg7, u8 arg8, u8 arg9, f32 argA, f32 argB, f32 argC, s16 argD);
void Trail50EffectAlt_Update(f32 arg0, Vec3f* arg1, f32 arg2);
void Trail50EffectAlt_AdvanceNodes(unk_D_843ADA80* arg0);
s32 Trail50EffectAlt_IsComplete(void);
Gfx* Trail50EffectAlt_Draw(Gfx* arg0);


void DoubleTextureTrail_InitPool(void);
void DoubleTextureTrail_Spawn(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8, f32 arg9, f32 argA, s16 argB, s32 argC, s32 argD, s16 argE, s16 argF, s16 arg10, s16 arg11, s16 arg12, s16 arg13, s16 arg14, s16 arg15, CombineParams* arg16, CombineParams* arg17, u8 arg18, u8 arg19, u8 arg1A, u8 arg1B, u8 arg1C, u8 arg1D, u8 arg1E, u8 arg1F, u8 arg20, u8 arg21, u8 arg22, u8 arg23, u8 arg24);
void DoubleTextureTrail_RotateVertexOffset(f32 arg0, Vec3f* arg1, f32 arg2);
void DoubleTextureTrail_Update(WaterParticleSystem* arg0);
s32 DoubleTextureTrail_UpdateAll(void);
Gfx* WaterParticle_DrawPass(Gfx* arg0, WaterParticleSystem* arg1, s16 arg2, s16 arg3);
Gfx* DoubleTextureTrail_LoadTextures(Gfx* arg0, WaterParticleSystem* arg1);
Gfx* DoubleTextureTrail_DrawAll(Gfx* arg0);


void BattleAnim_SixSlotTrail_ResetPool(void);
void BattleAnim_SixSlotTrail_Spawn(s16 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, u8 arg7, u8 arg8, u8 arg9, u8 argA, u8 argB, u8 argC, u8 argD, u8 argE, u8 argF, f32 arg10, f32 arg11, f32 arg12, s16 arg13, s32 arg14, s32 arg15, s16 arg16, s16 arg17, s16 arg18, s16 arg19, s16 arg1A, s16 arg1B, s16 arg1C, s16 arg1D, CombineParams* arg1E, CombineParams* arg1F);
void BattleAnim_SixSlotTrail_ComputeCameraRelativeOffset(s32 arg0, Vec3f* arg1, Vec3f* arg2, Vec3f* arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7);
void BattleAnim_SixSlotTrail_ComputeRotatedOffset(f32 arg0, Vec3f* arg1, Vec3f* arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6);
void BattleAnim_SixSlotTrail_UpdateSlot(unk_D_843C3508* arg0);
s32 BattleAnim_SixSlotTrail_UpdateAll(void);
Gfx* BattleAnim_SixSlotTrail_DrawSegments(Gfx* arg0, unk_D_843C3508* arg1);
Gfx* BattleAnim_SixSlotTrail_LoadTextures(Gfx* arg0, unk_D_843C3508* arg1);
Gfx* BattleAnim_SixSlotTrail_DrawAll(Gfx* arg0);
void AuxiliaryEffect_Init(void);
s16 AuxiliaryEffect_Alloc(void);
void AuxiliaryEffect_Spawn(s16 arg0, f32 arg1, f32 arg2, f32 arg3, s16 arg4, f32 arg5);
void AuxiliaryEffect_Update(s16 arg0);
Gfx* AuxiliaryEffect_DrawOne(Gfx* arg0, Particle* arg1, MtxF* arg2);
Gfx* AuxiliaryEffect_Draw(s16 arg0, Gfx* arg1);
void func_8436EED4(void);
void func_8436EEDC(void);
s32 func_8436EEE4(s32 arg0);


void BattleScene_SetStripWipeState(s32 arg0, s32 arg1);
s32 BattleScene_GetStripWipeState(void);
void BattleScene_UpdateStripWipe(void);
Gfx* BattleScene_BuildStripWipeDisplayList(Gfx* arg0, s32 arg1);
void BattleScene_DrawStripWipe(void);


void Battle_DebugLogClear(void);


void func_8436F6D0(void);
u8 Battle_Random(void);
u8 Battle_RandomAccuracy(void);
void ShowDamageMessage(s32 arg0, s32 arg1);
void Battle_ResetTransientRuntimeState(s32 arg0, s32 arg1);
void func_8436FA80(unk_BattlePlayerEntity* arg0);
void Battle_ApplyDamageRandomFactor(void);
u16 Battle_DetermineMoveOrder(unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1);
s32 IsByteInArray(u8 arg0, u8* arg1, s32 arg2);
void Battle_SetActiveMoveFromSlotIndex(void);
s32 func_8436FDBC(void);
void ComputePokemonStat(s32 arg0, PokemonData* arg1);
void ComputeAllPokemonStats(PokemonData* arg0);
void InitBattleParameters(void);
s32 Battle_CalcDamage(void);
void Battle_ApplyDamage(void);
void Battle_DecrementPP(s32 arg0);
void ApplyAccuracyStageMultipliers(void);
void MarkAttackFailed(void);
void HandleMoveEffectFlags(void);
void Battle_ApplyAnimStateEffects(unk_BattlePlayerEntity* arg0);
void ApplyParalysisSpeedCut(unk_BattlePlayerEntity* arg0);
void ApplyBurnAttackCut(unk_BattlePlayerEntity* arg0);
void Battle_InitPokemonRuntimeState(unk_BattlePlayerEntity* arg0);
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
s32 Battle_CheckMonCanAct(void);
void ProcessBattleTurn(void);
void Battle_HandleFaint(unk_BattlePlayerEntity* arg0);
void CheckAllPartyFainted_HP(unk_BattlePlayerEntity* arg0);
void CheckAllPartyFainted_Status(unk_BattlePlayerEntity* arg0);
void CheckAllPartyFainted_PP(unk_BattlePlayerEntity* arg0);
void CheckAllPartyFainted_Level(unk_BattlePlayerEntity* arg0);
s32 Battle_CheckSideDefeatAfterResidualStatus(unk_BattlePlayerEntity* arg0);
s32 Battle_CheckFaintAfterMove(void);
void Battle_ResolveMonAction(void);
void BeginBattleForEntity(unk_BattlePlayerEntity* arg0);


u16 Battle_ApplyStatStageMultiplier(u16* arg0, u16 arg1, u8 arg2);
void Battle_Effect_Sleep(void);
void Battle_Effect_Poison(void);
void Battle_Effect_DrainHP(void);
void Battle_Effect_Explosion(void);
void Battle_Effect_SecondaryStatusChance(void);
void Battle_ApplyRageStatBoost(void);
void Battle_Effect_RaiseOwnStat(void);
void Battle_Effect_LowerStat(void);
void Battle_Effect_Bide(void);
void Battle_Effect_Thrash(void);
void Battle_Effect_ForceSwitchOrFlee(void);
void Battle_Effect_MultiHit(void);
void Battle_Effect_Flinch(void);
void Battle_Effect_OHKO(void);
void Battle_Effect_TwoTurnMove(void);
void Battle_Effect_Trap(void);
void Battle_Effect_Mist(void);
void Battle_Effect_FocusEnergy(void);
void Battle_Effect_Recoil(void);
void Battle_Effect_ConfuseChance(void);
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
void Battle_RunMoveEffect(void);
void Battle_ExecuteMoveEffect(void);


void BattleAI_LoadConfiguration(s32 arg0, u32 arg1);
void func_843767DC(void);
s32 BattleAI_RandomBelowInclusive(s32 arg0);
void BattleAI_SeedRandomState(u8 arg0);
u8 BattleAI_EstimateCriticalHitChance(PokemonAudioInfo* arg0, PokemonAudioInfo* arg1, u8 arg2);
u16 BattleAI_ApplyMoveEffectDamageOverride(PokemonAudioInfo* arg0, PokemonAudioInfo* arg1);
void BattleAI_ClampDamageRatio(void);
void BattleAI_ApplyTypeEffectAndStab(PokemonAudioInfo* arg0, PokemonAudioInfo* arg1);
void BattleAI_PrepareDamageCalcState(PokemonAudioInfo* arg0, PokemonAudioInfo* arg1, u8 arg2);
void BattleAI_CalcDamage(PokemonAudioInfo* arg0, PokemonAudioInfo* arg1);
u16 BattleAI_PredictDamage(PokemonAudioInfo* arg0, PokemonAudioInfo* arg1, u8 arg2, u8 arg3);
void BattleAI_ResetTeamState(unk_D_843C60AC* arg0);
s32 BattleAI_ScaleSignedRatio(s32 arg0, s32 arg1);
void BattleAI_AppendTrainerTeamSpecies(unk_D_800AE540_0004* arg0);
s32 BattleAI_FindSpeciesIndex(s32 arg0);
s32 BattleAI_IsThresholdMet(u8 arg0, u8 arg1);
u16 BattleAI_ScaleStatHigh(PokemonAudioInfo* arg0);
u16 BattleAI_ScaleStatLow(PokemonAudioInfo* arg0);
f32 Battle_GetTypeEffectiveness(u8 arg0, PokemonAudioInfo* arg1);
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
u16 BattleAI_ScoreMove(PokemonAudioInfo* arg0, PokemonAudioInfo* arg1, u8 arg2);
void BattleAI_PickBestMove(PokemonAudioInfo* arg0, PokemonAudioInfo* arg1, u16* arg2, u8* arg3, u8 arg4, u8 arg5);
s32 BattleAI_ScoreAllCandidateMoves(unk_D_843C60AC* arg0, unk_D_843C60AC* arg1, u8* arg2, u8 arg3);
s32 BattleAI_ScoreAllCandidateMovesRatioToMaxHp(unk_D_843C60AC* arg0, unk_D_843C60AC* arg1, u8* arg2, u8 arg3);
s32 BattleAI_ScoreAllCandidateMovesRatioToCurrentHp(unk_D_843C60AC* arg0, unk_D_843C60AC* arg1, u8* arg2, u8 arg3);
void func_8437921C(void);
u8 BattleAI_CalcStagedMovePower(PokemonAudioInfo* arg0, PokemonAudioInfo* arg1, u8 arg2, u8 arg3);
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
s32 BattleAI_SelectRandomUsableMoveSlot(PokemonAudioInfo* arg0);
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
void BattleAI_SimulateStatBoostGuess(PokemonAudioInfo* arg0, PokemonAudioInfo* arg1, u8 arg2, u8 arg3);
void BattleAI_BuildAllCandidateMoveScores(unk_func_8438220C* arg0);
void BattleAI_RefineAllCandidateMoveScores(unk_func_8438220C* arg0);
u8 BattleAI_DecideFinalAction(unk_func_8438220C* arg0);
s32 BattleAI_DecideAction(void);
s32 BattleAI_ResolveTiedActionChoice(s32 arg0);
s32 BattleAI_MatchesLastMoveCategory(u8 arg0, u8 arg1);
s32 BattleAI_IsDiscouragedRepeatCategory(u8 arg0, u8 arg1);
s32 BattleAI_IsBannedRandomMove(u8 arg0);
s32 BattleAI_IsRestrictedRandomMove(u8 arg0);
s32 BattleAI_IsMoveExcludedForSpecies(PokemonAudioInfo* arg0, s32 arg1, u8 arg2, u8 arg3);
s32 BattleAI_IsMoveIneffective(PokemonAudioInfo* arg0, PokemonAudioInfo* arg1, u8 arg2);
void BattleAI_SyncTeamStateFromRuntime(void);
s32 func_843831A0(unk_D_800AE540_0004* arg0, unk_D_800AE540_0004* arg1, unk_D_800AE540_0004* arg2, s32 arg3, u8* arg4, s32 arg5, s32 arg6);
void BattleAI_RecordUsedMove(UNUSED s32 arg0, UNUSED s32 arg1, s32 arg2);
s32 BattleAI_ChooseAction(UNUSED s32 arg0);
void BattleAI_InitTrainerRecords(void);
s32 BattleAI_ResolveRandomMove(s32 arg0, s32 arg1);

#endif // _FRAGMENT62_H_
