#ifndef _1AB70_H_
#define _1AB70_H_

#include "global.h"
#include "6BC0.h"
#include "F420.h"
#include "29BA0.h"

typedef struct unk_func_8001B1FC {
    /* 0x00 */ u16 unk_00;
    /* 0x02 */ u16 unk_02;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ s16 unk_08;
    /* 0x0A */ s16 unk_0A;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ s16 unk_10;
    /* 0x12 */ s16 unk_12;
    /* 0x14 */ s32 unk_14;
    /* 0x18 */ f32 unk_18;
    /* 0x1C */ AssetManager* unk_1C;
    /* 0x20 */ GraphNode* unk_20;
    /* 0x24 */ Fragment2_1GraphNode* unk_24;
    /* 0x28 */ FramebufferImage* unk_28;
    /* 0x2C */ FramebufferImage* unk_2C;
} unk_func_8001B1FC; // size = 0x30

typedef union unk_func_8001A024_008_014 {
    struct {
        /* 0x00 */ s16 unk_00;
        /* 0x02 */ s16 unk_02;
    };
    u8* ptr;
    u32 raw;
} unk_func_8001A024_008_014; // size = 0x4

typedef struct unk_func_8001A024_008 {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ u16 unk_02;
    /* 0x04 */ s16 unk_04;
    /* 0x08 */ f32 unk_08;
    /* 0x0C */ FramebufferImage* unk_0C;
    /* 0x10 */ arg1_func_80010CA8 unk_10;
    /* 0x14 */ unk_func_8001A024_008_014 unk_14;
} unk_func_8001A024_008; // size = 0x18

typedef struct SpriteDisplay {
    /* 0x00 */ u8 unk_00;
    /* 0x01 */ u8 unk_01;
    /* 0x02 */ s8 unk_02;
    /* 0x03 */ s8 unk_03;
    /* 0x04 */ AssetManager* unk_04;
    /* 0x08 */ unk_func_8001A024_008* unk_08;
    /* 0x0C */ GraphNode* unk_0C;
    /* 0x10 */ Fragment2_1GraphNode* unk_10;
    /* 0x14 */ FramebufferImage* unk_14;
    /* 0x18 */ SpeciesDisplayParams* unk_18;
} SpriteDisplay; // size = 0x1C

typedef struct unk_D_84B25A28 {
    /* 0x00 */ u8 unk_00;
    /* 0x01 */ u8 unk_01;
    /* 0x02 */ u8 unk_02;
    /* 0x04 */ Fragment2_1GraphNode* unk_04;
    /* 0x08 */ unk_D_86002F34_00C* unk_08;
    /* 0x0C */ GraphNode* unk_0C;
    /* 0x10 */ GraphNode* unk_10;
    /* 0x14 */ GraphNode* unk_14;
    /* 0x18 */ GraphNode* unk_18;
    /* 0x1C */ GraphNode* unk_1C;
    /* 0x20 */ SpriteDisplay* unk_20;
    /* 0x24 */ FramebufferImage* unk_24;
    /* 0x28 */ FramebufferImage* unk_28;
    /* 0x2C */ char unk2C[0x4];
} unk_D_84B25A28; // size = 0x30

SpriteDisplay* SpriteDisplay_Alloc(AssetManager*, s16, s16, s16);
void SpriteDisplay_SetDepthBuffer(SpriteDisplay*, AssetManager*, FramebufferImage*);
void SpriteDisplay_SetScaleTable(SpriteDisplay*, SpeciesDisplayParams*);
void SpriteDisplay_Clear(SpriteDisplay*);
void SpriteDisplay_SetupSlot(SpriteDisplay*, s32, s32, u16);
void SpriteDisplay_ConfigSlotWithAnim(SpriteDisplay*, s32, PokemonData*, u16);
s32 SpriteDisplay_TryAdvance(SpriteDisplay*, s32);
s32 func_8001ABAC(SpriteDisplay*, s32);
s32 func_8001AD90(SpriteDisplay*, s32);
u8* SpriteDisplay_GetImagePtr(SpriteDisplay*, s32);
s32 func_8001B010(SpriteDisplay*);
void SpriteAssets_Load(void);
void func_8001B0DC(u16*, s32, PokemonData*);
unk_func_8001B1FC* func_8001B1FC(AssetManager*, s16, s16, s16, s16, s16, s16, u8*);
void func_8001B2D8(unk_func_8001B1FC* arg0, PokemonData* arg1, u16 arg2);
void func_8001B480(unk_func_8001B1FC*, s32, u16);
u8* func_8001B9D4(unk_func_8001B1FC*);

#endif // _1AB70_H_
