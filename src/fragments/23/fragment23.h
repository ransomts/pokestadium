#ifndef _FRAGMENT23_H_
#define _FRAGMENT23_H_

#include "global.h"
#include "src/fragments/26/fragment26.h"
#include "src/fragments/29/fragment29.h"
#include "src/2D340.h"
#include "src/22630.h"
#include "src/2E460.h"

struct unk_func_8821421C_038_04C_000;
struct unk_func_8820B12C_02C;
struct YesNoPanel;
struct unk_func_8821421C_038;
struct unk_func_8821421C_03C;
struct ItemBlockInfo;
struct QuantityEntry;
struct unk_func_8821421C_02C;

typedef struct ItemBlockHeader {
    /* 0x00 */ char unk00[0x4];
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ char* unk_08;
} ItemBlockHeader; // size >= 0xC

typedef struct unk_func_88200FA0_030 {
    /* 0x00 */ unk_func_88001300_000 unk_00;
    /* 0x2C */ unk_func_88001300_038* unk_2C;
    /* 0x30 */ unk_func_88200FA0_030_030* unk_30;
    /* 0x34 */ unk_func_88503298* unk_34;
    /* 0x38 */ unk_func_88200FA0_030_038 unk_38;
} unk_func_88200FA0_030; // size = 0x44

typedef struct unk_func_88200FA0 {
    /* 0x00 */ unk_func_88001300_000 unk_00;
    /* 0x2C */ unk_func_885088F4* unk_2C;
    /* 0x30 */ unk_func_88200FA0_030* unk_30;
} unk_func_88200FA0; // size = 0x34

typedef struct BoxPCScreen {
    /* 0x0000 */ unk_func_88001300_000 unk_0000;
    /* 0x002C */ unk_func_88203ED8* unk_002C;
    /* 0x0030 */ char unk0030[0x64];
    /* 0x0094 */ unk_func_88201DA0* unk_0094;
    /* 0x0098 */ unk_func_88205880_0098 unk_0098;
    /* 0x00D0 */ unk_func_88205880_00D0 unk_00D0[12];
    /* 0x5050 */ unk_func_88205880_00D0 unk_5050[12];
    /* 0x9FD0 */ unk_func_88205880_00D0* unk_9FD0[12];
    /* 0xA000 */ unk_func_88205880_00D0* unk_A000[12];
    /* 0xA030 */ unk_func_88205880_A030 unk_A030[2];
} BoxPCScreen; // size = 0xA048

typedef struct unk_func_882062E4 {
    /* 0x0000 */ char unk_00[0x54];
} unk_func_882062E4; // size = 0x54

typedef struct unk_func_88208C5C {
    /* 0x00 */ unk_func_88001300_000 unk_00;
    /* 0x2C */ unk_func_8850143C* unk_2C;
    /* 0x30 */ s32 unk_30;
    /* 0x34 */ s32 unk_34;
    /* 0x38 */ s32 unk_38;
} unk_func_88208C5C; // size = 0x3C

typedef struct unk_func_882079D8 {
    /* 0x00 */ unk_func_88001300_000 unk_00;
    /* 0x2C */ unk_func_88205880_00D0* unk_2C;
} unk_func_882079D8; // size = 0x30

typedef struct unk_func_8820BE14_030 {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ MemoryPool* unk_04;
    /* 0x08 */ unk_func_88001300_000_000* unk_08;
    /* 0x0C */ unk_func_88205880_00D0* unk_0C;
    /* 0x10 */ s32 unk_10;
    /* 0x14 */ unk_func_88001300_000* unk_14;
    /* 0x18 */ s32 unk_18;
} unk_func_8820BE14_030; // size >= 0x1C

typedef struct unk_func_8820B12C_02C_020 {
    /* 0x00 */ unk_func_88200FA0_030_030_1AE680 unk_00; // unk_func_882025E0_024
    /* 0x54 */ u16 unk_54;
    /* 0x56 */ u16 unk_56;
    /* 0x58 */ s32 unk_58;
    /* 0x5C */ s32 unk_5C;
    /* 0x60 */ s32 unk_60;
    /* 0x64 */ s32 unk_64;
    /* 0x68 */ s32 unk_68;
    /* 0x6C */ s32 unk_6C;
    /* 0x70 */ s32 unk_70;
    /* 0x74 */ unk_func_88001300_01C unk_74;
    /* 0x78 */ unk_func_88001300_018 unk_78;
    /* 0x7C */ unk_func_88001300_020 unk_7C;
    /* 0x80 */ unk_func_88001300_018 unk_80;
    /* 0x84 */ unk_func_8820BE14_02C_038_084* unk_84;
    /* 0x88 */ s32* unk_88;
    /* 0x8C */ u32 unk_8C;
} unk_func_8820B12C_02C_020; // size = 0x90

typedef s32 (*unk_func_8820B12C_02C_010)(struct unk_func_8820B12C_02C* arg0, Controller* arg1);
typedef void (*unk_func_8820B12C_02C_014)(struct unk_func_8820B12C_02C* arg0, s32 arg1);

typedef struct unk_func_8820B12C_02C {
    /* 0x00 */ char unk00[0x4];
    /* 0x04 */ struct unk_func_8820B12C_02C* unk_04;
    /* 0x08 */ struct unk_func_8820B12C_02C* unk_08;
    /* 0x0C */ char unk0C[0x4];
    /* 0x10 */ unk_func_8820B12C_02C_010 unk_10;
    /* 0x14 */ unk_func_8820B12C_02C_014 unk_14;
    /* 0x18 */ s32 unk_18;
    /* 0x1C */ s32 unk_1C;
    /* 0x20 */ unk_func_8820B12C_02C_020* unk_20[2];
    /* 0x28 */ s32 unk_28;
    /* 0x2C */ s32 unk_2C;
    /* 0x30 */ s32 unk_30;
    /* 0x34 */ s32 unk_34;
    /* 0x38 */ unk_func_88217740* unk_38;
    /* 0x3C */ TextObjectGraphics* unk_3C;
    /* 0x40 */ unk_func_8850CD44* unk_40;
    /* 0x44 */ FragmentEntry unk_44;
    /* 0x48 */ unk_func_8820BE14_030* unk_48;
    /* 0x4C */ unk_func_882173EC* unk_4C[2];
    /* 0x54 */ unk_func_882079D8* unk_54[2];
    /* 0x5C */ unk_func_8850878C* unk_5C[6];
    /* 0x74 */ s32 unk_74;
} unk_func_8820B12C_02C; // size = 0x78

typedef struct unk_func_8820B12C_000 {
    /* 0x00 */ char unk00[0x4];
    /* 0x04 */ struct unk_func_8820B12C_000* unk_04;
    /* 0x08 */ struct unk_func_8820B12C_000* unk_08;
    /* 0x0C */ char unk0C[0x4];
    /* 0x10 */ unk_func_8820B12C_02C_010 unk_10;
    /* 0x14 */ unk_func_8820B12C_02C_014 unk_14;
    /* 0x18 */ char unk18[0x4];
    /* 0x1C */ s32 unk_1C;
    /* 0x20 */ s32 unk_20;
    /* 0x24 */ struct TextObjectRenderer* unk_24;
} unk_func_8820B12C_000; // size = 0x28

typedef struct unk_func_8820B12C {
    /* 0x00 */ unk_func_8820B12C_000 unk_00;
    /* 0x28 */ unk_func_88001300_03C* unk_28;
    /* 0x28 */ unk_func_8820B12C_02C* unk_2C;
} unk_func_8820B12C; // size = 0x30

typedef struct unk_func_8820BE14_02C_070 {
    /* 0x0000 */ unk_func_88001300_000 unk_0000;
    /* 0x002C */ unk_func_88205880_00D0* unk_002C;
    /* 0x0030 */ s16 unk_0030;
    /* 0x0032 */ char unk0032[0x7];
    /* 0x0039 */ u8 unk_0039[2][0xC80];
} unk_func_8820BE14_02C_070; // size = 0x193C

typedef struct unk_func_8820BE14_02C_078_034 {
    /* 0x00 */ unk_func_88001300_000 unk_00;
    /* 0x2C */ unk_func_88001300_038* unk_2C;
    /* 0x30 */ unk_func_88200FA0_030_030* unk_30;
} unk_func_8820BE14_02C_078_034; // size = 0x34

typedef struct unk_func_8820BE14_02C_078 {
    /* 0x00 */ unk_func_88001300_000 unk_00;
    /* 0x2C */ unk_func_88001300_038* unk_2C;
    /* 0x30 */ unk_func_88200FA0_030_030* unk_30;
    /* 0x34 */ unk_func_8820BE14_02C_078_034* unk_34;
    /* 0x38 */ unk_func_8820BE14_06C unk_38;
    /* 0x48 */ s32 unk_48;
    /* 0x4C */ s32 unk_4C;
    /* 0x50 */ s32 unk_50;
    /* 0x54 */ s32 unk_54;
    /* 0x58 */ s32 unk_58;
    /* 0x5C */ s32 unk_5C;
} unk_func_8820BE14_02C_078; // size = 0x60

typedef struct TextObjectRenderer {
    /* 0x00 */ unk_func_88001300_000 unk_00;
    /* 0x2C */ unk_func_88001300_038* unk_2C;
    /* 0x30 */ unk_func_88208C5C* unk_30[2];
    /* 0x38 */ unk_func_8820BE14_02C_038* unk_38[2];
    /* 0x40 */ unk_func_88217740* unk_40;
    /* 0x44 */ unk_func_882149A0* unk_44[8];
    /* 0x64 */ unk_func_88500994* unk_64;
    /* 0x68 */ unk_func_88500994* unk_68;
    /* 0x6C */ unk_func_88500994* unk_6C;
    /* 0x70 */ unk_func_8820BE14_02C_070* unk_70;
    /* 0x74 */ unk_func_8820B12C* unk_74;
    /* 0x78 */ unk_func_8820BE14_02C_078* unk_78[2];
    /* 0x80 */ TextObjectGraphics* unk_80;
    /* 0x84 */ unk_func_889000C4* unk_84;
    /* 0x88 */ unk_func_8850878C* unk_88;
    /* 0x8C */ unk_func_8820BE14_06C* unk_8C;
    /* 0x90 */ char unk90[0x10];
} TextObjectRenderer; // size = 0xA0

typedef struct TextObjectContext {
    /* 0x00 */ unk_func_88001300_000 unk_00;
    /* 0x2C */ TextObjectRenderer* unk_2C;
    /* 0x30 */ unk_func_8820BE14_030 unk_30;
    /* 0x4C */ char** unk_4C;
    /* 0x50 */ char** unk_50;
    /* 0x54 */ char** unk_54;
    /* 0x58 */ char** unk_58;
    /* 0x5C */ char** unk_5C;
    /* 0x60 */ char** unk_60;
    /* 0x64 */ char** unk_64;
    /* 0x68 */ TextObjectGraphics* unk_68;
    /* 0x6C */ unk_func_8820BE14_06C unk_6C;
    /* 0x7C */ unk_func_8820BE14_06C unk_7C;
    /* 0x8C */ unk_func_8820BE14_06C unk_8C;
} TextObjectContext; // size = 0x9C

typedef struct unk_func_882170A8 {
    /* 0x00 */ unk_func_88001300_000 unk_00;
    /* 0x2C */ unk_func_8820BE14_02C_038* unk_2C;
    /* 0x30 */ s32 unk_30;
} unk_func_882170A8; // size = 0x34

typedef struct unk_D_88217C6C {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ u8* unk_08;
    /* 0x0C */ s16 unk_0C;
    /* 0x10 */ Color_RGBA8* unk_10;
    /* 0x14 */ s32 unk_14;
} unk_D_88217C6C; // size = 0x18

typedef struct unk_func_8821421C_02C_06C_02C_068 {
    /* 0x00 */ unk_func_88001300_000 unk_00;
    /* 0x2C */ s32 unk_2C;
} unk_func_8821421C_02C_06C_02C_068; // size = 0x30

typedef struct unk_func_8820E99C_030 {
    /* 0x00 */ unk_func_88001300_000 unk_00;
    /* 0x2C */ unk_func_88001300_038* unk_2C;
    /* 0x30 */ unk_func_8820E99C_030_030 unk_30;
    /* 0x44 */ unk_func_8820E99C_030_044* unk_44;
} unk_func_8820E99C_030; // size = 0x48

typedef struct QuantityEntry {
    /* 0x00 */ unk_func_88001300_000 unk_00;
    /* 0x2C */ unk_func_88001300_038* unk_2C;
    /* 0x30 */ unk_func_8820E99C_030* unk_30;
    /* 0x34 */ s32 unk_34;
} QuantityEntry; // size = 0x38

typedef struct YesNoPanel {
    /* 0x00 */ unk_func_88001300_000 unk_00;
    /* 0x2C */ unk_func_88001300_038* unk_2C;
    /* 0x30 */ unk_func_88001300_03C* unk_30;
    /* 0x34 */ unk_func_8850878C* unk_34;
} YesNoPanel; // size = 0x38

typedef struct unk_func_8821421C_038_02C {
    /* 0x00 */ unk_func_88001300_000 unk_00;
    /* 0x2C */ unk_func_8850143C* unk_2C;
    /* 0x30 */ unk_func_8821421C_038_050* unk_30;
} unk_func_8821421C_038_02C; // size = 0x34

typedef struct spE8_func_882121E0 {
    /* 0x00 */ char* unk_00[3];
} spE8_func_882121E0; // size >= 0xC

typedef struct unk_func_8821421C_02C_030 {
    /* 0x00 */ unk_func_88001300_000 unk_00;
    /* 0x2C */ unk_func_8850143C* unk_2C;
    /* 0x30 */ s32 unk_30;
    /* 0x34 */ s32 unk_34;
    /* 0x38 */ spE8_func_882121E0* unk_38;
} unk_func_8821421C_02C_030; // size = 0x3C

typedef struct unk_func_8821421C_02C_06C_02C_060_02C_000 {
    /* 0x00 */ u8 unk_00;
    /* 0x01 */ u8 unk_01;
} unk_func_8821421C_02C_06C_02C_060_02C_000; // size = 0x2

typedef struct unk_func_8821421C_02C_06C_02C_060_02C {
    /* 0x00 */ unk_func_8821421C_02C_06C_02C_060_02C_000 unk_00;
    /* 0x02 */ unk_func_8821421C_02C_06C_02C_060_02C_000 unk_02;
} unk_func_8821421C_02C_06C_02C_060_02C; // size >= 0x4

typedef struct unk_func_8821421C_02C_06C_02C_060 {
    /* 0x00 */ unk_func_88001300_000 unk_00;
    /* 0x2C */ unk_func_8821421C_02C_06C_02C_060_02C unk_2C;
} unk_func_8821421C_02C_06C_02C_060; // size = 0x30

typedef struct unk_func_8821421C_02C_06C_02C {
    /* 0x00 */ char unk00[0x10];
    /* 0x10 */ unk_func_882025E0_010 unk_10;
    /* 0x14 */ unk_func_882025E0_014 unk_14;
    /* 0x18 */ s32 unk_18;
    /* 0x1C */ s32 unk_1C;
    /* 0x20 */ unk_func_8820BE14_02C_038* unk_20[2];
    /* 0x28 */ struct QuantityEntry* unk_28;
    /* 0x2C */ unk_func_8820BE14_02C_038* unk_2C[2];
    /* 0x34 */ struct QuantityEntry* unk_34;
    /* 0x38 */ s32 unk_38;
    /* 0x3C */ s32 unk_3C;
    /* 0x40 */ s32 unk_40;
    /* 0x44 */ s32 unk_44;
    /* 0x48 */ unk_func_88217740* unk_48;
    /* 0x4C */ TextObjectGraphics* unk_4C;
    /* 0x50 */ unk_func_8850CD44* unk_50;
    /* 0x54 */ char unk54[0x4];
    /* 0x58 */ unk_func_882173EC* unk_58[2];
    /* 0x60 */ unk_func_8821421C_02C_06C_02C_060* unk_60[2];
    /* 0x68 */ unk_func_8821421C_02C_06C_02C_068* unk_68[2];
    /* 0x70 */ unk_func_8821421C_02C_06C_02C_060* unk_70[2];
    /* 0x78 */ unk_func_882025E0_03C unk_78[5];
} unk_func_8821421C_02C_06C_02C; // size = 0xB4

typedef struct unk_func_8821421C_02C_06C_000 {
    /* 0x00 */ char unk00[0x4];
    /* 0x04 */ struct unk_func_88203ED8_064* unk_04;
    /* 0x08 */ struct unk_func_88203ED8_064* unk_08;
    /* 0x0C */ char unk0C[0x4];
    /* 0x10 */ unk_func_8820B12C_02C_010 unk_10;
    /* 0x14 */ unk_func_8820B12C_02C_014 unk_14;
    /* 0x18 */ char unk18[0x4];
    /* 0x1C */ s32 unk_1C;
    /* 0x20 */ s32 unk_20;
    /* 0x24 */ struct unk_func_8821421C_02C* unk_24;
} unk_func_8821421C_02C_06C_000; // size = 0x28

typedef struct unk_func_8821421C_02C_06C {
    /* 0x00 */ unk_func_8821421C_02C_06C_000 unk_00;
    /* 0x28 */ unk_func_88001300_03C* unk_28;
    /* 0x2C */ unk_func_8821421C_02C_06C_02C* unk_2C;
} unk_func_8821421C_02C_06C; // size = 0x30

typedef struct unk_func_8821421C_02C_070 {
    /* 0x00 */ unk_func_88001300_000 unk_00;
    /* 0x2C */ unk_func_88001300_038* unk_2C;
    /* 0x30 */ unk_func_88200FA0_030_030* unk_30;
    /* 0x34 */ unk_func_88205880_A030 unk_34;
    /* 0x40 */ s32 unk_40;
    /* 0x44 */ s32 unk_44;
    /* 0x48 */ s32 unk_48;
} unk_func_8821421C_02C_070; // size = 0x4C

typedef struct unk_func_8821421C_02C {
    /* 0x00 */ unk_func_88001300_000 unk_00;
    /* 0x2C */ unk_func_88001300_038* unk_2C;
    /* 0x30 */ unk_func_8821421C_02C_030* unk_30[2];
    /* 0x38 */ unk_func_8820BE14_02C_038* unk_38[2];
    /* 0x40 */ unk_func_88217740* unk_40;
    /* 0x44 */ unk_func_882149A0* unk_44[6];
    /* 0x5C */ unk_func_88500994* unk_5C;
    /* 0x60 */ unk_func_88500994* unk_60;
    /* 0x64 */ unk_func_88500994* unk_64;
    /* 0x68 */ unk_func_8850878C* unk_68;
    /* 0x6C */ unk_func_8821421C_02C_06C* unk_6C;
    /* 0x70 */ unk_func_8821421C_02C_070* unk_70[2];
    /* 0x78 */ struct unk_func_8821421C_03C* unk_78;
    /* 0x78 */ struct unk_func_8821421C_03C* unk_7C;
    /* 0x80 */ s32 unk_80;
    /* 0x84 */ struct unk_func_8821421C_038* unk_84;
    /* 0x88 */ struct YesNoPanel* unk_88;
    /* 0x8C */ TextObjectGraphics* unk_8C;
    /* 0x90 */ struct ItemBlockInfo* unk_90;
    /* 0x94 */ unk_func_882025E0_03C unk_94[1];
    /* 0xA0 */ unk_func_889000C4* unk_A0;
} unk_func_8821421C_02C; // size = 0xA4

typedef void (*unk_func_8821421C_038_04C_000_014)(struct unk_func_8821421C_038_04C_000*, Controller*);

typedef struct unk_func_8821421C_038_04C_000 {
    /* 0x00 */ char unk00[0x4];
    /* 0x04 */ struct unk_func_88203ED8_064* unk_04;
    /* 0x08 */ struct unk_func_88203ED8_064* unk_08;
    /* 0x0C */ char unk0C[0x4];
    /* 0x10 */ unk_func_8820B12C_02C_010 unk_10;
    /* 0x14 */ unk_func_8821421C_038_04C_000_014 unk_14;
    /* 0x18 */ char unk18[0x4];
    /* 0x1C */ s32 unk_1C;
    /* 0x20 */ s32 unk_20;
    /* 0x24 */ struct unk_func_8821421C_038* unk_24;
} unk_func_8821421C_038_04C_000; // size = 0x28

typedef struct unk_func_8821421C_038_04C {
    /* 0x00 */ unk_func_8821421C_038_04C_000 unk_00;
    /* 0x28 */ unk_func_88001300_03C* unk_28;
} unk_func_8821421C_038_04C; // size = 0x2C

typedef struct unk_func_8821421C_03C {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ unk_func_8820BE14_06C unk_04;
} unk_func_8821421C_03C; // size = 0x14

typedef struct ItemBlockInfo {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ char unk_08[4]; // unk size
    /* 0x0C */ char unk0C[0x8];
} ItemBlockInfo; // size = 0x14

typedef struct unk_func_8821421C_038 {
    /* 0x00 */ unk_func_88001300_000 unk_00;
    /* 0x2C */ unk_func_8821421C_038_02C* unk_2C;
    /* 0x30 */ unk_func_8820BE14_02C_038* unk_30;
    /* 0x34 */ unk_func_8821421C_038_034* unk_34;
    /* 0x38 */ unk_func_88500994* unk_38;
    /* 0x3C */ unk_func_88500994* unk_3C;
    /* 0x40 */ unk_func_8850878C* unk_40;
    /* 0x44 */ unk_func_88001300_038* unk_44;
    /* 0x48 */ YesNoPanel* unk_48;
    /* 0x4C */ unk_func_8821421C_038_04C* unk_4C;
    /* 0x50 */ unk_func_8821421C_038_050* unk_50[1];
    /* 0x54 */ char unk54[0xC];
    /* 0x60 */ s32 unk_60;
    /* 0x64 */ unk_func_8820BE14_06C unk_64;
    /* 0x74 */ char unk74[0x4];
} unk_func_8821421C_038; // size = 0x78

typedef struct ItemPCScreen {
    /* 0x00 */ unk_func_88001300_000 unk_00;
    /* 0x2C */ unk_func_8821421C_02C* unk_2C;
    /* 0x34 */ TextObjectGraphics* unk_30;
    /* 0x34 */ YesNoPanel* unk_34;
    /* 0x38 */ unk_func_8821421C_038* unk_38;
    /* 0x3C */ unk_func_8821421C_03C unk_3C[3];
    /* 0x78 */ s32 unk_78;
    /* 0x7C */ ItemBlockInfo unk_7C[4];
} ItemPCScreen; // size = 0xCC

extern Color_RGBA8 gPanelAccentTexture1[2];
extern Color_RGBA8 gPanelAccentTexture2[2];
extern Color_RGBA8 gPanelAccentTexture3[2];
extern Color_RGBA8 gPanelAccentTexture4[2];
extern Color_RGBA8 gPanelColorA[2];
extern Color_RGBA8 gPanelColorB[2];
extern Color_RGBA8 D_882181E0[2];
extern Color_RGBA8 gPanelOverlayTexture[2];
extern Color_RGBA8 gPanelTextureAlt1[2];
extern Color_RGBA8 gPanelTextureAlt4[2];
extern Color_RGBA8 gPanelTextureAlt3[2];
extern Color_RGBA8 gPanelTextureAlt2[2];
extern Color_RGBA8 gTexture_MainMenuOption1[2];
extern Color_RGBA8 gTexture_MainMenuOption2[2];
extern Color_RGBA8 D_88218220[2];
extern Color_RGBA8 gPanelTextureDefault[2];
extern Color_RGBA8 D_88218230[2];
extern Color_RGBA8 D_88218238[2];

extern u32 gPanelIconTexture[];
extern u32 gPanelBackgroundTexture1[];
extern u32 gTexture_PanelA[];
extern u32 gPanelBackgroundTexture3[];
extern u32 gPanelBackgroundTexture2[];
extern u32 gPanelBackgroundTexture4[];
extern u32 gTexture_PanelB[];
extern u32 D_8821D378[];
extern u32 gSwapArrowsTexture[];
extern u32 D_882220D8[];
extern u32 D_882225C0[];
extern u32 D_88222AA8[];
extern u32 D_88222F90[];
extern u32* gTexture_MoveTargetSmall[];
extern u32 gTexture_MoveTargetLarge[];
extern u32 gPcBackdropTile[];

TextObject* Fragment23_Init(void);
void Fragment23_Terminate(void);
s32 Fragment23_Execute(UNUSED s32 arg0, UNUSED s32 arg1);
s32 Fragment23_HandleState(s32 arg0, s32 arg1);

void CreateInfoPanel(unk_func_88503298* arg0, s32 arg1, s32 arg2, MemoryPool* arg3);
void InfoPanelSetText(unk_func_88503298* arg0, s8* arg1);
void CommonStringMenuCreate(unk_func_88200FA0_030* arg0, s32 arg1, s32 arg2, unk_func_88001300_000* arg3, MemoryPool* arg4);
void UpdateDescriptionForSelection(unk_func_88200FA0_030* arg0, s32 arg1);
void DrawMenuItemText(s32 arg0, s32 arg1, char* arg2, s32 arg3);
s32 MenuProcessInput(unk_func_88200FA0_030* arg0, Controller* arg1);
void MenuActivate(unk_func_88200FA0_030* arg0);
void MenuCloseAndWait(unk_func_88200FA0_030* arg0);
s32 MenuRunSelectionLoop(unk_func_88200FA0_030* arg0, Controller* arg1);
void ItemInfoScreenCreate(unk_func_88200FA0* arg0, s32 arg1, s32 arg2, s32 arg3, MemoryPool* arg4);
s32 ScreenMessageLoopRun(unk_func_88200FA0* arg0);
void Fragment23ThreadMain(unk_func_88200FA0* arg0);
s32 Fragment23_GetNextState(s32 arg0, UNUSED s32 arg1);

void Box_MarkSpeciesOwned(unk_func_88205880_00D0* arg0);
void Box_SaveToGbs(s32 arg0, s32 arg1, s32 arg2, unk_func_88205880_00D0* arg3);
s32 Box_LoadFromGbs(s32 arg0, s32 arg1, s32 arg2, unk_func_88205880_00D0* arg3, s32 arg4);
void Boxes_LoadFromGbs(unk_func_88205880_00D0* arg0, s32 arg1, s32 arg2, s32 arg3);
s32 BoxList_HasNoEmptyBoxes(unk_func_88205880_A030* arg0);
s32 BoxList_IsEmpty(unk_func_88205880_A030* arg0);
void func_88202054(unk_func_88201DA0* arg0, u32 arg1, u32 arg2);
void func_8820213C(unk_func_88201DA0* arg0, unk_func_88205880_00D0* arg1, u32 arg2);
void func_88202228(unk_func_88203ED8* arg0, s32 arg1);
s32 func_88202254(unk_func_88201DA0* arg0, Controller* arg1);
void func_88202394(unk_func_88201DA0* arg0, Controller* arg1);
void DrawBoxMonCount(unk_func_88205880_00D0* arg0, s32 arg1, s32 arg2);
void func_8820253C(unk_func_8820253C* arg0, s32 arg1, s32 arg2, unk_func_88205880_00D0* arg3);
void func_882025AC(unk_func_8820253C* arg0, unk_func_88205880_00D0* arg1);
s32 func_882025B4(unk_func_8820253C* arg0, s32 arg1, s32 arg2);
void BoxMove_Init(unk_func_882025E0_1A9780* arg0, unk_func_88200FA0_030_030* arg1, unk_func_88200FA0_030_030* arg2, unk_func_88203ED8* arg3, MemoryPool* arg4);
void func_88202738(unk_func_882025E0_1A9780* arg0, s32 arg1);
void func_88202758(unk_func_882025E0_1A9780* arg0);
void func_882027F0(unk_func_882025E0_1A9780* arg0, s32 arg1);
void func_88202810(unk_func_882025E0_1A9780* arg0, unk_func_88205880_00D0** arg1, unk_func_88205880_00D0** arg2);
void func_882028EC(unk_func_882025E0_1A9780* arg0, unk_func_88001300_000_010* arg1, unk_func_88001300_000_010* arg2);
void BoxList_DisableEmptyBoxes(unk_func_88200FA0_030_030* arg0);
void BoxList_DisableNonEmptyBoxes(unk_func_88200FA0_030_030* arg0);
void func_88202CBC(unk_func_882025E0_1A9780* arg0);
void BoxMove_SetPhase(unk_func_882025E0_1A9780* arg0, s32 arg1);
void BoxMove_SetMoveMode(unk_func_882025E0_1A9780* arg0, s32 arg1);
void func_88202E98(unk_func_882025E0_1A9780* arg0);
void BoxMove_SwapSides(unk_func_882025E0_1A9780* arg0);
s32 func_88202ED8(unk_func_882025E0_1A9780* arg0);
void BoxMove_SwapWithinList(unk_func_882025E0_1A9780* arg0);
void BoxMove_SwapBetweenLists(unk_func_882025E0_1A9780* arg0);
s32 BoxMove_HandleInput(unk_func_882025E0_1A9780* arg0, Controller* arg1);
void BoxListHeader_Init(unk_func_8820399C* arg0, s32 arg1, unk_func_8850143C* arg2);
s32 BoxListHeader_Draw(unk_func_8820399C* arg0, s32 arg1, s32 arg2);
s32 func_88204BA8(unk_func_88203ED8* arg0);
void func_88204BFC(unk_func_88203ED8* arg0, s32 arg1);
s32 func_88204C28(unk_func_88203ED8* arg0, Controller* arg1);
void func_88204C74(unk_func_88203ED8* arg0);
void func_88204CBC(unk_func_88203ED8* arg0);
void func_88204DC0(unk_func_88203ED8_064* arg0, unk_func_88203ED8* arg1);
u32 Box_DiffersFromGbs(unk_func_88205880_00D0* arg0, s32 arg1, s32 arg2, s32 arg3);
s32 MarkModifiedBoxes(unk_func_88203ED8* arg0);
void SaveModifiedBoxes(unk_func_88203ED8* arg0, s32 arg1);
s32 PromptToSaveBoxChanges(unk_func_88203ED8* arg0, Controller* arg1);
s32 BoxPCMenuCursor_HandleInput(unk_func_88203ED8_064* arg0, Controller* arg1);
void BoxPCUI_Run(unk_func_88203ED8* arg0, Controller* arg1);
s32 func_88205DD0(BoxPCScreen* arg0, Controller* arg1);
void BoxPC_RunDisplayLoop(BoxPCScreen* arg0);
void BoxPCThreadMain(BoxPCScreen* arg0);

void InitMonData(PokemonData* arg0);
s32 LoadPokemonFromSave(unk_func_882062E4* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
s32 MenuEntry_ProcessInput(unk_func_8820BE14_02C_078_034* arg0, Controller* arg1);
s32 Menu_NavigateAndSelect(unk_func_88001300_034* arg0, Controller* arg1);
s32 GetMenuEntryWidth(void);
void MenuEntry_Init(unk_func_8820BE14_02C_078_034* arg0, s32 arg1, s32 arg2, MemoryPool* arg3);
s32 MenuEntry_CalcMaxWidth(void);
u32 Menu_GetStateFlags(unk_func_8820BE14_02C_078* arg0);
void Menu_SetStateFlags(unk_func_8820BE14_02C_078* arg0, u32 arg1);
void Menu_SetSecondaryFlags(unk_func_8820BE14_02C_078* arg0, u32 arg1);
s32 MenuList_ProcessInput(unk_func_8820BE14_02C_078* arg0, Controller* arg1);
s32 MenuList_NavigateAndSelect(unk_func_8820BE14_02C_078* arg0, Controller* arg1);
void DrawLevelLabel(unk_func_88205880_00D0* arg0, s32 arg1, s32 arg2, s32 arg3);
void LevelLabelFragment_Init(unk_func_882079D8* arg0, s32 arg1, s32 arg2, s32 arg3, unk_func_88205880_00D0* arg4);
void LevelLabelFragment_SetData(unk_func_882079D8* arg0, unk_func_88205880_00D0* arg1);
s32 LevelLabelFragment_DrawIfData(unk_func_882079D8* arg0, s32 arg1, s32 arg2);
void MenuDualList_SetSelection(unk_func_8820B12C_02C* arg0, s32 arg1);
void MenuDualList_SetState(unk_func_8820B12C_02C* arg0, s32 arg1);
void MenuDualList_UpdateSublists(unk_func_8820B12C_02C* arg0);
void MenuDualList_SetActiveSublist(unk_func_8820B12C_02C* arg0, s32 arg1);
void MenuDualList_SetMode(unk_func_8820B12C_02C* arg0, s32 arg1);
void MenuDualList_SwapSublists(unk_func_8820B12C_02C* arg0);
void MenuDualList_GetCurrentAndSecondary(unk_func_8820B12C_02C* arg0, unk_func_88205880_00D0** arg1, unk_func_88205880_00D0** arg2);
void MenuDualList_CalcItemPositions(unk_func_8820B12C_02C* arg0, unk_func_88001300_000_010* arg1, unk_func_88001300_000_010* arg2);
void MenuDualList_HandleStateTransition(unk_func_8820B12C_02C* arg0, s32 arg1);
void MenuDualList_ResetAndInitSecond(unk_func_8820B12C_02C* arg0);
s32 MenuDualList_IsStateZero(unk_func_8820B12C_02C* arg0);
void MenuDualList_CopyEntry(unk_func_8820B12C_02C_020* arg0, unk_func_8820B12C_02C_020* arg1);
void MenuDualList_SwapEntries(unk_func_8820B12C_02C_020* arg0, s32 arg1, s32 arg2);
void MenuDualList_SwapEntriesBetweenLists(unk_func_8820B12C_02C_020* arg0, unk_func_8820B12C_02C_020* arg1);
void MenuDualList_FinalizeEntry(unk_func_8820B12C_02C_020* arg0);
void MenuDualList_Update(unk_func_8820B12C_02C* arg0, Controller* arg1);
void MenuDualList_UpdateWithSwapFlag(unk_func_8820B12C_02C* arg0, Controller* arg1, s32 arg2);
void MenuDualList_ConfirmSelection(unk_func_8820B12C_02C* arg0);
s32 MenuDualList_ProcessInput(unk_func_8820B12C_02C* arg0, Controller* arg1);
unk_func_88205880_00D0* MenuDualList_GetSelectedItem(unk_func_8820B12C_02C* arg0);
void MoveTargetSelector_Init(unk_func_88208C5C* arg0, unk_func_8850143C* arg1);
s32 MoveTargetSelector_Draw(unk_func_88208C5C* arg0, s32 arg1, s32 arg2);
u32 MoveTargetSelector_GetSelection(unk_func_88208C5C* arg0);
void Scroll_SetOffset(unk_func_88208C5C* arg0, u32 arg1);
void MoveIconList_Init(unk_func_8820BE14_02C_070* arg0, s32 arg1, s32 arg2);
void DrawMoveName(s32 arg0, s32 arg1, ret_func_8002ED08* arg2, s32 arg3);
s32 RenderMoveInfoPanel(unk_func_8820BE14_02C_070* arg0, s32 arg1, s32 arg2);
void MonPreview_SetMon(unk_func_8820BE14_02C_070* arg0, unk_func_88205880_00D0* arg1);
s32 FindFirstIncompleteSlot(unk_func_8820BE14_06C* arg0);
s32 UIState_Update(TextObjectRenderer* arg0);
s32 UI_HandleInput(TextObjectRenderer* arg0, Controller* arg1);
s32 UI_WaitForConfirm(TextObjectRenderer* arg0, Controller* arg1);
void UI_SetState(TextObjectRenderer* arg0, s32 arg1);
void Panel_ToggleAllFills(unk_func_8820B12C_02C* arg0);
void UIComponent_SetCallback(unk_func_8820B12C* arg0, TextObjectRenderer* arg1);
s32 CheckPokemonDataChanged(unk_func_8820BE14_06C_000* arg0, s32 arg1, s32 arg2, s32 arg3);
s32 GetChangedBankMask(TextObjectRenderer* arg0);
s32 IsFirstBankEmpty(TextObjectRenderer* arg0);
void WritePokemonGbsBlock(s32 arg0, s32 arg1, s32 arg2, unk_func_88200FA0_030_038* arg3);
void MonList_MarkSpeciesOwned(unk_func_88200FA0_030_038* arg0, s32 arg1);
void SaveChangesAndUpdateUI(TextObjectRenderer* arg0, s32 arg1);
s32 ShowChangeDialog(TextObjectRenderer* arg0, Controller* arg1);
s32 MainScreen_HandleInput(unk_func_8820B12C* arg0, Controller* arg1);
void TextObject_MainLoop(TextObjectContext* arg0);
void TextObject_WaitForClose(TextObjectContext* arg0);
void TextObject_FadeInOutAndClose(TextObjectContext* arg0);
void TextObject_Show(TextObject* arg0, s32 arg1);

void TryReadPokemonBlock(s32 arg0, s32 arg1, s32 arg2, unk_func_8820BE14_06C* arg3);
void TryReadPokemonBlockEx(s32 arg0, s32 arg1, s32 arg2, unk_func_8820BE14_06C* arg3, s32 arg4, char* arg5, s32 arg6);
void UpdateBlockInfo_12(ItemBlockInfo* arg0);
s32 FindBlockIndexByIdAndName(ItemBlockInfo* arg0, s32 arg1, char* arg2);
void ItemListHeader_Init(unk_func_8821421C_02C_030* arg0, unk_func_8850143C* arg1, spE8_func_882121E0* arg2);
s32 ItemListHeader_Draw(unk_func_8821421C_02C_030* arg0, s32 arg1, s32 arg2);
s32 MoveTargetSelector_GetSelectedIndex(unk_func_8821421C_02C_030* arg0);
void MoveTargetSelector_SetSelectedIndex(unk_func_8821421C_02C_030* arg0, s32 arg1);
void NumericInput_Init(YesNoPanel* arg0, s32 arg1, s32 arg2, MemoryPool* arg3);
s32 NumericInput_HandleInput(YesNoPanel* arg0, Controller* arg1);
void NumericInput_SetValue(YesNoPanel* arg0, s32 arg1);
void NumericInput_SetPrompt(YesNoPanel* arg0, char* arg1);
s32 NumericInput_Process(YesNoPanel* arg0, Controller* arg1);
s32 MeasureMaxTextWidth(spE8_func_882121E0* arg0, s32 arg1);
void ListItem_Draw(s32 arg0, s32 arg1, s8* arg2, s32 arg3, s32 arg4, unk_func_88200FA0_030_030* arg5);
s32 func_8820DB98(unk_func_8821421C_02C_070* arg0, Controller* arg1);
void ScrollableList_SetSelection(unk_func_8821421C_02C_070* arg0, s32 arg1);
s32 ScrollableList_GetCurrentIndex(unk_func_8821421C_02C_070* arg0);
void ScrollableList_SetItemCount(unk_func_8821421C_02C_070* arg0, s32 arg1);
void ScrollableList_Reset(unk_func_8821421C_02C_070* arg0);
void ScrollableList_Finish(unk_func_8821421C_02C_070* arg0);
s32 ScrollableList_ProcessInput(unk_func_8821421C_02C_070* arg0, Controller* arg1);
void ScrollableList_SetHighlightedIndex(unk_func_8821421C_02C_070* arg0, s32 arg1);
s32 StageName_DrawEntry(u8* arg0, s32 arg1, s32 arg2, s32 arg3);
void StageInfo_Draw(s32 arg0, s32 arg1, u8* arg2, s32 arg3, s32 arg4, unk_func_8820BE14_02C_038* arg5);
void TextBox_Init(unk_func_8821421C_02C_06C_02C_060* arg0, s32 arg1, s32 arg2, s32 arg3);
void TextBox_SetData(unk_func_8821421C_02C_06C_02C_060* arg0, unk_func_8821421C_02C_06C_02C_060_02C_000 arg1);
s32 TextBox_Draw(unk_func_8821421C_02C_06C_02C_060* arg0, s32 arg1, s32 arg2);
void NumberInput_InitParams(unk_func_8820E99C_030* arg0, s32 arg1);
void NumberInput_Create(unk_func_8820E99C_030* arg0, s32 arg1, s32 arg2, MemoryPool* arg3);
void NumberInput_SetSelection(unk_func_8820E99C_030* arg0, s32 arg1);
s32 NumberInput_CalcOffset(unk_func_8820E99C_030* arg0);
s32 NumberInput_DrawDigits(unk_func_8820E99C_030* arg0, s32 arg1, s32 arg2);
s32 NumberInput_HandleController(unk_func_8820E99C_030* arg0, Controller* arg1);
void NumberInput_Setup(QuantityEntry* arg0, s32 arg1, s32 arg2);
void NumericEntry_Create(QuantityEntry* arg0, s32 arg1, s32 arg2, MemoryPool* arg3);
void NumericEntry_SetSelection(QuantityEntry* arg0, s32 arg1);
s32 NumericEntry_HandleInput(QuantityEntry* arg0, Controller* arg1);
void NumericEntry_Reset(QuantityEntry* arg0);
void NumericEntry_Finish(QuantityEntry* arg0);
void LabelComponent_Init(unk_func_8821421C_038_02C* arg0, unk_func_8850143C* arg1);
s32 LabelComponent_Draw(unk_func_8821421C_038_02C* arg0, s32 arg1, s32 arg2);
void LabelComponent_SetLabel(unk_func_8821421C_038_02C* arg0, unk_func_8821421C_038_050* arg1);
void ItemInfo_Draw(s32 arg0, s32 arg1, ItemBlockHeader* arg2, s32 arg3, s32 arg4, unk_func_8821421C_038_034* arg5);
void func_8820FFF8(unk_func_8821421C_038* arg0, ItemBlockInfo* arg1);
s32 MainMenuFragment_Update(unk_func_8821421C_038* arg0);
s32 MainMenuFragment_HandleInput(unk_func_8821421C_038* arg0, Controller* arg1);
void MainMenuFragment_SetSelection(unk_func_8821421C_038* arg0, s32 arg1);
void MainMenuFragment_LoadData(unk_func_8821421C_038* arg0, s32 arg1);
s32 func_88210234(unk_func_8821421C_038* arg0, Controller* arg1);
void Fragment_SetInputCallback(unk_func_8821421C_038_04C* arg0, unk_func_8821421C_038* arg1);
s32 Fragment_InputHandler(unk_func_8821421C_038_04C* arg0, Controller* arg1);
void Fragment_SetState(unk_func_8821421C_02C_06C_02C* arg0, s32 arg1);
void Fragment_UpdateOptionVisibility(unk_func_8821421C_02C_06C_02C* arg0);
void Fragment_SetSelection(unk_func_8821421C_02C_06C_02C* arg0, s32 arg1);
void Fragment_ToggleSide(unk_func_8821421C_02C_06C_02C* arg0);
void Fragment_UpdatePosition(unk_func_8821421C_02C_06C_02C* arg0, s32 arg1);
void Fragment_SetMode(unk_func_8821421C_02C_06C_02C* arg0, s32 arg1);
void Fragment_InitMode(unk_func_8821421C_02C_06C_02C* arg0, s32 arg1);
void Fragment_ResetList(unk_func_8821421C_02C_06C_02C* arg0);
s32 Fragment_IsInitialState(unk_func_8821421C_02C_06C_02C* arg0);
void func_88210DA8(void);
s32 ComputeScoreAdjustment(s32 arg0, unk_func_8820BE14_06C* arg1);
s32 GetStageScoreDelta(s32 arg0, unk_func_8820BE14_06C* arg1);
void List_InsertItem(unk_func_8820BE14_02C_038* arg0, u8* arg1);
void List_RemoveItem(unk_func_8820BE14_02C_038* arg0, s32 arg1);
void List_RemoveLastItem(unk_func_8820BE14_02C_038* arg0);
void List_AdjustCounts(unk_func_8820BE14_02C_038* arg0, s32 arg1, s32 arg2);
void List_DecreaseItemCount(unk_func_8820BE14_02C_038* arg0, s32 arg1);
void List_TransferItem(unk_func_8820BE14_02C_038* arg0, unk_func_8820BE14_02C_038* arg1, QuantityEntry* arg2);
s32 SplitValueBetweenEntries(unk_func_8821421C_02C_06C_02C_060_02C_000* arg0, unk_func_8821421C_02C_06C_02C_060_02C_000* arg1);
void List_SwapEntries(unk_func_8820BE14_02C_038* arg0, s32 arg1, s32 arg2);
void List_SwapBetweenLists(unk_func_8820BE14_02C_038* arg0, unk_func_8820BE14_02C_038* arg1);
void Fragment_UpdateAndRender(unk_func_8821421C_02C_06C_02C* arg0, Controller* arg1);
void Fragment_SecondaryUpdate(unk_func_8821421C_02C_06C_02C* arg0, Controller* arg1);
void Fragment_TertiaryUpdate(unk_func_8821421C_02C_06C_02C* arg0, Controller* arg1);
s32 Fragment_ProcessInput(unk_func_8821421C_02C_06C_02C* arg0, Controller* arg1);
u8* Fragment_GetCurrentDataPointer(unk_func_8821421C_02C_06C_02C* arg0);
s32 func_8821347C(unk_func_8821421C_02C* arg0);
s32 func_882135D4(unk_func_8821421C_02C* arg0, Controller* arg1);
s32 Menu_WaitForSelection(unk_func_8821421C_02C* arg0, Controller* arg1);
void Menu_SetState(unk_func_8821421C_02C* arg0, s32 arg1);
void ItemPCUI_ToggleModeButtons(unk_func_8821421C_02C* arg0);
void Menu_SetParent(unk_func_8821421C_02C_06C* arg0, unk_func_8821421C_02C* arg1);
s32 GbsBlock_CompareAndUpdate(unk_func_8821421C_03C* arg0, s32 arg1, s32 arg2, s32 arg3);
s32 Menu_GetDirtyFlags(unk_func_8821421C_02C* arg0);
void Menu_CommitChanges(unk_func_8821421C_02C* arg0, s32 arg1);
s32 Menu_HandleDialog(unk_func_8821421C_02C* arg0, Controller* arg1);
s32 ItemPCMenuCursor_HandleInput(unk_func_8821421C_02C_06C* arg0, Controller* arg1);
void Menu_Create(ItemPCScreen* arg0, s32 arg1, s32 arg2, MemoryPool* arg3, s32 arg4, char** arg5);
void ItemPC_RunDisplayLoop(ItemPCScreen* arg0);
void Menu_ThreadEntry(ItemPCScreen* arg0);
void TextObject_Confirm(TextObject* arg0);

void Panel_Init(unk_func_882149A0* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, Color_RGBA8 arg7, Color_RGBA8 arg8, Color_RGBA8 arg9);
s32 Panel_Draw(unk_func_882149A0* arg0, s32 arg1, s32 arg2);
void Panel_ToggleFill(unk_func_882149A0* arg0);
void ScrollableList_Init(unk_func_8820BE14_02C_038* arg0, s32 arg1, s32 arg2, s32 arg3, void (*arg4)(), s32 arg5, s32 arg6, MemoryPool* arg7);
void ScrollableList_SetDirection(unk_func_88200FA0_030_030* arg0, s32 arg1);
void ScrollableList_SetItemRenderer(unk_func_8820BE14_02C_038* arg0, unk_func_88507D4C* arg1);
s32 ScrollableList_Update(unk_func_8820BE14_02C_038* arg0);
s32 ScrollableList_DrawItems(unk_func_8820BE14_02C_038* arg0, s32 arg1, s32 arg2, s32 arg3);
s32 StatBar_Draw(unk_func_88507D4C* arg0, s32 arg1, s32 arg2);
s32 ScrollableList_HandleInput(unk_func_8820BE14_02C_038* arg0, Controller* arg1);
void ScrollableList_SetActive(unk_func_8820BE14_02C_038* arg0, s32 arg1);
void ScrollableList_SetDataPtr(unk_func_8820BE14_02C_038* arg0, unk_func_8820BE14_06C_000* arg1, s32 arg2);
void ScrollableList_SetData(unk_func_8820BE14_02C_038*, s32*, s32);
void ItemSlot_Init(unk_func_882170A8* arg0, s32 arg1, s32 arg2, unk_func_8820BE14_02C_038* arg3, s32 arg4);
void Cursor_Draw(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
s32 func_8821738C(unk_func_882170A8* arg0, s32 arg1, s32 arg2);
void Button_Init(unk_func_882173EC* arg0, s32 arg1, s32 arg2);
s32 SlideAnim_Update(unk_func_882173EC* arg0);
void SlideAnim_Begin(unk_func_882173EC* arg0, unk_func_88001300_000_010 arg1, unk_func_88001300_000_010 arg2);
void Button_Create(unk_func_8821421C_02C_06C_02C_068* arg0, s32 arg1, s32 arg2);
s32 func_882176C4(unk_func_8821421C_02C_06C_02C_068* arg0);
void func_88217718(unk_func_8821421C_02C_06C_02C_068* arg0, unk_func_88001300_000_010 arg1);
void SwapArrows_Init(unk_func_88217740* arg0, s32 arg1, s32 arg2);
s32 SwapArrows_Draw(unk_func_88217740* arg0, s32 arg1, s32 arg2);
void func_88217BA0(unk_func_88217740* arg0, s32 arg1);
void SwapArrows_Show(unk_func_88217740* arg0);
void SwapArrows_Hide(unk_func_88217740* arg0);
void SwapArrows_ToggleDirection(unk_func_88217740* arg0);


#endif // _FRAGMENT23_H_
