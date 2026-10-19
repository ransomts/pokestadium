#ifndef _1AB70_H_
#define _1AB70_H_

#include "global.h"
#include "src/gfx_rect.h"
#include "src/matrix.h"
#include "src/game_state.h"

typedef struct ModelPreview {
    /* 0x00 */ u16 posX;
    /* 0x02 */ u16 posY;
    /* 0x04 */ s16 rotation;
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
} ModelPreview; // size = 0x30

typedef union unk_func_8001A024_008_014 {
    struct {
        /* 0x00 */ s16 posX;
        /* 0x02 */ s16 posY;
    };
    u8* ptr;
    u32 raw;
} unk_func_8001A024_008_014; // size = 0x4

typedef struct SpriteSlot {
    /* 0x00 */ s16 posX;
    /* 0x02 */ u16 posY;
    /* 0x04 */ s16 rotation;
    /* 0x08 */ f32 unk_08;
    /* 0x0C */ FramebufferImage* unk_0C;
    /* 0x10 */ arg1_func_80010CA8 unk_10;
    /* 0x14 */ unk_func_8001A024_008_014 unk_14;
} SpriteSlot; // size = 0x18

typedef struct SpriteDisplay {
    /* 0x00 */ u8 posX;
    /* 0x01 */ u8 unk_01;
    /* 0x02 */ s8 posY;
    /* 0x03 */ s8 unk_03;
    /* 0x04 */ AssetManager* rotation;
    /* 0x08 */ SpriteSlot* unk_08;
    /* 0x0C */ GraphNode* unk_0C;
    /* 0x10 */ Fragment2_1GraphNode* unk_10;
    /* 0x14 */ FramebufferImage* unk_14;
    /* 0x18 */ SpeciesDisplayParams* unk_18;
} SpriteDisplay; // size = 0x1C

typedef struct BattleUiState {
    /* 0x00 */ u8 posX;
    /* 0x01 */ u8 unk_01;
    /* 0x02 */ u8 posY;
    /* 0x04 */ Fragment2_1GraphNode* rotation;
    /* 0x08 */ CameraStruct* unk_08;
    /* 0x0C */ GraphNode* unk_0C;
    /* 0x10 */ GraphNode* unk_10;
    /* 0x14 */ GraphNode* unk_14;
    /* 0x18 */ GraphNode* unk_18;
    /* 0x1C */ GraphNode* unk_1C;
    /* 0x20 */ SpriteDisplay* unk_20;
    /* 0x24 */ FramebufferImage* unk_24;
    /* 0x28 */ FramebufferImage* unk_28;
    /* 0x2C */ char unk2C[0x4];
} BattleUiState; // size = 0x30

SpriteDisplay* PokeIcon_CreateRenderList(AssetManager*, s16, s16, s16);
void PokeIcon_AttachDepthBuffer(SpriteDisplay*, AssetManager*, FramebufferImage*);
void PokeIcon_SetNameTable(SpriteDisplay*, SpeciesDisplayParams*);
void PokeIcon_ResetRenderList(SpriteDisplay*);
void SpriteDisplay_SetupSlot(SpriteDisplay*, s32, s32, u16);
void SpriteDisplay_ConfigSlotWithAnim(SpriteDisplay*, s32, PokemonData*, u16);
s32 PokeIcon_ProcessNextSlot(SpriteDisplay*, s32);
s32 PokeIcon_ProcessAllSlots(SpriteDisplay*, s32);
s32 PokeIcon_RenderNextSlotBlocking(SpriteDisplay*, s32);
u8* PokeIcon_GetImage(SpriteDisplay*, s32);
s32 PokeIcon_AreSlotsIdle(SpriteDisplay*);
void PokeIcon_OpenModelArchive(void);
void PokeIcon_LoadModelTextureForMon(u16*, s32, PokemonData*);
ModelPreview* PokeIcon_CreateModelPreview(AssetManager*, s16, s16, s16, s16, s16, s16, u8*);
void PokeIcon_SetPreviewMon(ModelPreview* arg0, PokemonData* arg1, u16 arg2);
void PokeIcon_SetPreviewSpecies(ModelPreview*, s32, u16);
u8* PokeIcon_RenderPreview(ModelPreview*);

#endif // _1AB70_H_
