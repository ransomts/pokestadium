#include "battle_engine.h"
#include "src/model_animation.h"
#include "src/display_object_textures.h"
#include "src/model_renderer.h"
#include "src/audio_commands.h"
#include "src/3D140.h"
#include "src/audio_fade.h"
#include "src/audio_sfx.h"
#include "src/audio_loop_point.h"
#include "src/cry.h"
#include "src/matrix.h"
#include "src/math_util.h"

typedef struct WaterAnimParams {
    /* 0x00 */ char unk00[0xC];
    /* 0x0C */ f32 unk_0C;
    /* 0x10 */ f32 unk_10;
    /* 0x14 */ char unk14[0x4];
} WaterAnimParams; // size = 0x18

s32 gBattleEngineState;
#include "prevent_bss_reordering.h"
s32 gPanelDrawCount;
s32 gBattleEngineTimer;
static s32 gCurrentActionScriptId;
static s32 gPendingActionScriptFlag0;
static s32 gBattleEngineFlag;
static s32 gCurrentActionScriptSubIndex;
static s32 gWaterEffectCounter;
static s32 gPendingActionScriptFlag3;
static s32 gCurrentActionScriptMode;
static s32 gPendingActionScriptFlag1;
static s32 gCurrentActionScriptAltId;
static s32 gCurrentActionScriptSubId;
static s32 gPendingActionScriptFlag2;
static s32 gWaterEffectParam;
static s32 gWaterEffectTimerMax;
static s8 gCurrentEffectListSource;
s16 gParticleEffectParam;
s16 gParticleEffectPrimaryId;
static s16 gParticleEffectSecondaryId;
BattlePlayerEntity* gParticleEffectAttackerEntity;
BattlePlayerEntity* gParticleEffectUserEntity;
BattlePlayerEntity* gParticleEffectTargetEntity;
s32 gGameStateFlag;
s32 gBattleEngineStatus;
static s8 gStateCallbackSlot;
func_D_84390300 gCameraCallbackFuncs[8];
func_D_84390320 gCameraUpdateFuncs[8];
s32 gCameraStateFlag;
static f32 gWaterScale;
Vec3f gCameraLookAtPos;
static Vec3s gCameraAngles;
static Vec3f gCameraPosOffset;
static Vec3s gCameraRotOffset;
static Vec3s gCameraTargetOffset;
s16 gSavedPrimColorR;
s16 gSavedPrimColorG;
s16 gSavedPrimColorB;
s16 gSavedPrimColorA;
s16 gPrimColorR;
s16 gPrimColorG;
s16 gPrimColorB;
s16 gPrimColorA;
s16 gEnvColorR;
s16 gEnvColorG;
s16 gEnvColorB;
s16 gEnvColorA;
s16 gFogColorR;
s16 gFogColorG;
s16 gFogColorB;
s16 gFogColorA;
s16 gBlendColorR;
s16 gBlendColorG;
s16 gBlendColorB;
s16 gBlendColorA;
s32 pad_D_843903A8[2];
static s32 gGraphNodePoolInitFlag;
static s32 gParticleNodePoolInitFlag;
s32 pad_D_843903B8[6];
static Fragment2_1GraphNode D_843903D0[16];
static s32 gGraphNodeUsed[16];
static Fragment2_1GraphNode gParticleNodePool[4];
static s32 gParticleNodeUsed[4];
static WaterAnimParams gWaterAnimParams;
f32 gWaterWaveTable[26];

static s32 gPanelDrawCountArray[] = { 0, 0, 0, 0 };

u32 gMessageIdLookup[] = {
    0x00000005, 0x00000006, 0x00000007, 0x00000008, 0x00000009, 0x0000000A, 0x0000000B, 0x0000000C,
    0x0000000D, 0x0000000E, 0x0000000F, 0x00000010, 0x00000011, 0x00000012, 0x00000013, 0x00000014,
    0x00000015, 0x00000016, 0x00000017, 0x00000018, 0x00000019, 0x0000001A, 0x0000001B, 0x0000001C,
    0x0000001D, 0x0000001E, 0x0000001F, 0x00000020, 0x00000021, 0x00000026, 0x00000027, 0x00000028,
    0x00000029, 0x0000002A, 0x0000002B, 0x0000002C, 0x0000002D, 0x0000002E, 0x0000002F, 0x00000030,
    0x00000031, 0x00000032, 0x00000033, 0x00000034, 0x00000035, 0x00000036, 0x00000000, 0x00000000,
};

Vtx gPanelQuadVerts[] = {
    VTX(-64, -63, 0, 0, 2016, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(62, -63, 0, 2016, 2016, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(62, 0, 0, 2016, 0, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(-64, 0, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF),
};

Vtx gPanelBarVerts[] = {
    VTX(-16, 96, 0, 0, 3040, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(15, 96, 0, 992, 3040, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(15, 0, 0, 992, 0, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(-16, 0, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF),
};

Vtx gPanelBarSmallVerts[] = {
    VTX(-8, 96, 0, 0, 3040, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(7, 96, 0, 992, 3040, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(7, 0, 0, 992, 0, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(-8, 0, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF),
};

Vtx gPanelMiscVerts[] = {
    VTX(-4, 96, 0, 0, 3040, 0xFF, 0xFF, 0xFF, 0xFF),     VTX(3, 96, 0, 992, 3040, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(3, 0, 0, 992, 0, 0xFF, 0xFF, 0xFF, 0xFF),        VTX(-4, 0, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(-160, -120, 0, 0, 2048, 0x00, 0x00, 0x78, 0xFF), VTX(160, -120, 0, 2048, 2048, 0x00, 0x00, 0x78, 0xFF),
    VTX(160, 120, 0, 2048, 0, 0x00, 0x00, 0x78, 0xFF),   VTX(-160, 120, 0, 0, 0, 0x00, 0x00, 0x78, 0xFF),
};

Vtx gPanelBgVerts[] = {
    VTX(-160, -120, 0, 0, 4096, 0x00, 0x00, 0x78, 0xFF),
    VTX(160, -120, 0, 4096, 4096, 0x00, 0x00, 0x78, 0xFF),
    VTX(160, 120, 0, 4096, 0, 0x00, 0x00, 0x78, 0xFF),
    VTX(-160, 120, 0, 0, 0, 0x00, 0x00, 0x78, 0xFF),
};

Vtx gPanelBgLargeVerts[] = {
    VTX(-160, -120, 0, 0, 8192, 0x00, 0x00, 0x78, 0xFF),
    VTX(160, -120, 0, 8192, 8192, 0x00, 0x00, 0x78, 0xFF),
    VTX(160, 120, 0, 8192, 0, 0x00, 0x00, 0x78, 0xFF),
    VTX(-160, 120, 0, 0, 0, 0x00, 0x00, 0x78, 0xFF),
};

ParticleRenderSettings gParticleDescriptorChildren[] = {
    {
        0x01,
        0x01,
        0x0000,
        ParticleGfx_LoadTextureCallbackI4FrameMod4_32x32,
        ParticleGfx_DrawBillboardPrim,
        &gBattleAnimAssetPointers[4],
    },
    {
        0x00,
        0x01,
        0x0000,
        ParticleGfx_LoadTextureCallbackI4FrameDiv2Mod8_32x32,
        ParticleGfx_DrawBillboardPrimEnvQuad,
        &gBattleAnimAssetPointers[5],
    },
    {
        0x00,
        0x01,
        0x0000,
        ParticleGfx_LoadTextureCallbackI4FrameMod10_32x64,
        ParticleGfx_DrawBillboardPrimEnvQuadVariantA,
        &gBattleAnimAssetPointers[20],
    },
    {
        0x00,
        0x01,
        0x0000,
        ParticleGfx_LoadTextureCallbackI4FrameMod10_32x64,
        ParticleGfx_DrawBillboardPrimEnvQuadVariantC,
        &gBattleAnimAssetPointers[20],
    },
    {
        0x00,
        0x01,
        0x0000,
        ParticleGfx_LoadTextureCallbackI4FrameDiv2Mod8_32x32,
        ParticleGfx_DrawBillboardPrimEnvQuad,
        &gBattleAnimAssetPointers[5],
    },
    {
        0x00,
        0x01,
        0x0000,
        ParticleGfx_LoadTextureCallbackI4FrameDiv2Mod8_32x32,
        ParticleGfx_DrawBillboardTextureAlphaRotatedQuad,
        &gBattleAnimAssetPointers[5],
    },
    {
        0x00,
        0x01,
        0x0000,
        ParticleGfx_LoadTextureCallbackI4FrameMod10_32x64,
        ParticleGfx_DrawBillboardPrimEnvQuadVariantC,
        &gBattleAnimAssetPointers[20],
    },
    {
        0x00,
        0x01,
        0x0000,
        ParticleGfx_LoadTextureCallbackI4ParticleFrame_32x64,
        ParticleGfx_DrawBillboardPrimEnvQuadVariantA,
        &gBattleAnimAssetPointers[9],
    },
    {
        0x00,
        0x01,
        0x0000,
        ParticleGfx_LoadTextureCallbackI4_32x32,
        ParticleGfx_DrawBillboardPrim,
        &gBattleAnimAssetPointers[3],
    },
    {
        0x00,
        0x01,
        0x0000,
        ParticleGfx_LoadTextureCallbackI4FrameMod4_32x32,
        ParticleGfx_DrawBillboardPrimEnvQuad,
        &gBattleAnimAssetPointers[23],
    },
    {
        0x00,
        0x01,
        0x0001,
        ParticleGfx_LoadTextureCallbackI4FrameDiv2Mod4_32x32,
        ParticleGfx_DrawBillboardPrimEnvQuad,
        &gBattleAnimAssetPointers[14],
    },
    {
        0x00,
        0x01,
        0x0000,
        ParticleGfx_LoadTextureCallbackIa8Frame_32x32,
        ParticleGfx_DrawBillboardPrimEnvQuad,
        &gBattleAnimAssetPointers[17],
    },
    {
        0x00,
        0x01,
        0x0000,
        ParticleGfx_LoadTextureCallbackI4FrameMod4_32x32,
        ParticleGfx_DrawBillboardPrimEnvQuad,
        &gBattleAnimAssetPointers[14],
    },
    {
        0x00,
        0x01,
        0x0001,
        ParticleGfx_LoadTextureCallbackI4TileParticleFrame_24x24,
        ParticleGfx_DrawBillboardPrimEnv,
        &gBattleAnimAssetPointers[8],
    },
    {
        0x00,
        0x01,
        0x0000,
        ParticleGfx_LoadTextureCallbackI4TileParticleFrame_24x24,
        ParticleGfx_DrawBillboardPrimEnv,
        &gBattleAnimAssetPointers[8],
    },
    {
        0x00,
        0x01,
        0x0000,
        ParticleGfx_LoadTextureCallbackI4TileParticleFrame_24x24,
        ParticleGfx_DrawBillboardDoubleSided,
        &gBattleAnimAssetPointers[8],
    },
    {
        0x00,
        0x01,
        0x0000,
        ParticleGfx_LoadTextureCallbackI4FrameMod8_64x64,
        ParticleGfx_DrawBillboardPrimEnvComposite,
        &gBattleAnimAssetPointers[18],
    },
    {
        0x00,
        0x01,
        0x0001,
        ParticleGfx_LoadTextureCallbackIa8Frame_32x32,
        ParticleGfx_DrawBillboardPrimEnvQuad,
        &gBattleAnimAssetPointers[17],
    },
    {
        0x00,
        0x01,
        0x0000,
        ParticleGfx_LoadTextureCallbackIa8Frame_32x32,
        ParticleGfx_DrawBillboardPrimEnvQuad,
        &gBattleAnimAssetPointers[17],
    },
    {
        0x00,
        0x01,
        0x0000,
        ParticleGfx_LoadTextureCallbackI4FrameDiv2Mod8_32x32,
        ParticleGfx_DrawBillboardPrimEnvQuad,
        &gBattleAnimAssetPointers[5],
    },
    {
        0x00,
        0x01,
        0x0000,
        ParticleGfx_LoadTextureCallbackI4FrameMod8_64x64,
        ParticleGfx_DrawBillboardPrimEnvComposite,
        &gBattleAnimAssetPointers[18],
    },
    {
        0x00,
        0x01,
        0x0000,
        ParticleGfx_LoadTextureCallbackI4FrameMod4_32x32,
        ParticleGfx_DrawBillboardPrimEnvQuad,
        &gBattleAnimAssetPointers[23],
    },
    {
        0x00,
        0x01,
        0x0000,
        ParticleGfx_LoadTextureCallbackI4FrameMod4_32x32,
        ParticleGfx_DrawBillboardPrimEnvQuad,
        &gBattleAnimAssetPointers[13],
    },
    {
        0x00,
        0x01,
        0x0000,
        ParticleGfx_LoadTextureCallbackI4FrameDiv4Mod4_32x32,
        ParticleGfx_DrawBillboardPrimEnvQuad,
        &gBattleAnimAssetPointers[13],
    },
    {
        0x00,
        0x01,
        0x0000,
        ParticleGfx_LoadTextureCallbackI4FrameDiv2Mod8_64x64,
        ParticleGfx_DrawBillboardPrimEnvComposite,
        &gBattleAnimAssetPointers[18],
    },
    {
        0x00,
        0x01,
        0x0000,
        ParticleGfx_LoadTextureCallbackI4FrameDiv2Mod4_32x32,
        ParticleGfx_DrawBillboardPrimEnvQuad,
        &gBattleAnimAssetPointers[23],
    },
    {
        0x00,
        0x01,
        0x0000,
        ParticleGfx_LoadTextureCallbackI4_64x64,
        ParticleGfx_DrawBillboardPrimEnvTriangleDoubleSided,
        &gBattleAnimAssetPointers[11],
    },
    {
        0x00,
        0x01,
        0x0001,
        ParticleGfx_LoadTextureCallbackIa8Frame_32x32,
        ParticleGfx_DrawBillboardPrimEnvQuad,
        &gBattleAnimAssetPointers[82],
    },
    {
        0x00,
        0x01,
        0x0000,
        ParticleGfx_LoadTextureCallbackI4_32x32,
        ParticleGfx_DrawBillboardPrimEnvRotatedQuad,
        &gBattleAnimAssetPointers[16],
    },
    {
        0x00,
        0x01,
        0x0001,
        ParticleGfx_LoadTextureCallbackIa8_32x32,
        ParticleGfx_DrawBillboardPrimEnvQuad,
        &gBattleAnimAssetPointers[84],
    },
    {
        0x00,
        0x01,
        0x0001,
        ParticleGfx_LoadTextureCallbackI4_32x32,
        ParticleGfx_DrawBillboardPrimEnvQuad,
        &gBattleAnimAssetPointers[169],
    },
    {
        0x00,
        0x01,
        0x0001,
        ParticleGfx_LoadTextureCallbackI4_32x32,
        ParticleGfx_DrawBillboardPrimEnvQuad,
        &gBattleAnimAssetPointers[172],
    },
    {
        0x00,
        0x01,
        0x0000,
        ParticleGfx_LoadTextureCallbackI4_32x32,
        ParticleGfx_DrawBillboardPrimEnvQuad,
        &gBattleAnimAssetPointers[166],
    },
    {
        0x00,
        0x01,
        0x0000,
        ParticleGfx_LoadTextureCallbackI4_32x32,
        ParticleGfx_DrawBillboardPrimEnvQuad,
        &gBattleAnimAssetPointers[167],
    },
    {
        0x00,
        0x01,
        0x0001,
        ParticleGfx_LoadTextureCallbackI4ParticleFrame_32x32,
        ParticleGfx_DrawBillboardPrimEnvQuad,
        &gBattleAnimAssetPointers[83],
    },
    {
        0x00,
        0x01,
        0x0001,
        ParticleGfx_LoadTextureCallbackI4ParticleFrame_32x32,
        ParticleGfx_DrawBillboardPrimEnvQuad,
        &gBattleAnimAssetPointers[83],
    },
    {
        0x00,
        0x01,
        0x0001,
        ParticleGfx_LoadTextureCallbackI4ParticleFrame_64x64,
        ParticleGfx_DrawBillboardPrimEnvComposite,
        &gBattleAnimAssetPointers[89],
    },
    {
        0x00,
        0x01,
        0x0001,
        ParticleGfx_LoadTextureCallbackIa8_32x32,
        ParticleGfx_DrawBillboardPrimEnvRotatedQuad,
        &gBattleAnimAssetPointers[95],
    },
    {
        0x01,
        0x01,
        0x0000,
        ParticleGfx_LoadTextureCallbackIa8_32x32,
        BattleAnim_DrawAsset95Ia8Billboard,
        &gBattleAnimAssetPointers[95],
    },
    {
        0x00,
        0x01,
        0x0000,
        ParticleGfx_LoadTextureCallbackIa8Frame_32x32,
        ParticleGfx_DrawBillboardPrimEnvQuad,
        &gBattleAnimAssetPointers[2],
    },
    {
        0x00,
        0x01,
        0x0001,
        ParticleGfx_LoadTextureCallbackIa8Frame_32x32,
        ParticleGfx_DrawBillboardPrimEnvQuad,
        &gBattleAnimAssetPointers[100],
    },
    {
        0x00,
        0x01,
        0x0001,
        ParticleGfx_LoadTextureCallbackI4ParticleFrame_32x32,
        ParticleGfx_DrawBillboardPrimEnvNoiseQuad,
        &gBattleAnimAssetPointers[83],
    },
    {
        0x00,
        0x01,
        0x0000,
        ParticleGfx_LoadTextureCallbackI4ParticleFrame_32x32,
        ParticleGfx_DrawBillboardPrimEnvNoiseQuad,
        &gBattleAnimAssetPointers[83],
    },
    {
        0x00,
        0x01,
        0x0001,
        ParticleGfx_LoadTextureCallbackI4ParticleFrame_32x32,
        ParticleGfx_DrawBillboardPrimEnvQuad,
        &gBattleAnimAssetPointers[101],
    },
    {
        0x00,
        0x01,
        0x0000,
        ParticleGfx_LoadTextureCallbackI4ParticleFrame_32x32,
        ParticleGfx_DrawBillboardPrimEnvQuad,
        &gBattleAnimAssetPointers[83],
    },
    {
        0x00,
        0x01,
        0x0000,
        ParticleGfx_LoadTextureCallbackI4WrapST_64x64,
        ParticleGfx_DrawBillboardPrimEnvTransformedQuad,
        &gBattleAnimAssetPointers[63],
    },
    {
        0x00,
        0x01,
        0x0000,
        ParticleGfx_LoadTextureCallbackIa8WrapST_64x64,
        ParticleGfx_DrawBillboardPrimEnvTransformedQuad,
        &gBattleAnimAssetPointers[112],
    },
    {
        0x00,
        0x01,
        0x0000,
        ParticleGfx_LoadTextureCallbackI4ParticleFrame_32x32,
        ParticleGfx_DrawBillboardOffsetQuad,
        &gBattleAnimAssetPointers[83],
    },
    {
        0x00,
        0x01,
        0x0000,
        ParticleGfx_LoadTextureCallbackIa8Frame_32x64,
        ParticleGfx_DrawBillboardPrimEnvQuadVariantB,
        &gBattleAnimAssetPointers[117],
    },
    {
        0x00,
        0x01,
        0x0001,
        ParticleGfx_LoadTextureCallbackIa8Frame_32x32,
        ParticleGfx_DrawBillboardPrimEnvQuad,
        &gBattleAnimAssetPointers[122],
    },
    {
        0x00,
        0x01,
        0x0000,
        ParticleGfx_LoadTextureCallbackIa8Frame_32x32,
        ParticleGfx_DrawBillboardPrimEnvQuad,
        &gBattleAnimAssetPointers[82],
    },
    {
        0x00,
        0x01,
        0x0000,
        ParticleGfx_LoadTextureCallbackIa8_32x32,
        ParticleGfx_DrawBillboardPrimEnvRotatedQuad,
        &gBattleAnimAssetPointers[95],
    },
    {
        0x00,
        0x01,
        0x0001,
        ParticleGfx_LoadTextureCallbackIa8Frame_32x32,
        ParticleGfx_DrawBillboardPrimEnvRotatedQuad,
        &gBattleAnimAssetPointers[82],
    },
    {
        0x00,
        0x01,
        0x0000,
        ParticleGfx_LoadTextureCallbackIa8Frame_32x32,
        ParticleGfx_DrawBillboardPrimEnvRotatedQuad,
        &gBattleAnimAssetPointers[82],
    },
    {
        0x00,
        0x01,
        0x0000,
        ParticleGfx_LoadTextureCallbackI4ParticleFrame_32x32,
        ParticleGfx_DrawBillboardPrimEnvQuad,
        &gBattleAnimAssetPointers[83],
    },
    {
        0x00,
        0x01,
        0x0000,
        ParticleGfx_LoadTextureCallbackI4FrameDiv2Mod4_32x32,
        ParticleGfx_DrawBillboardPrimEnvQuad,
        &gBattleAnimAssetPointers[14],
    },
    {
        0x00,
        0x01,
        0x0000,
        ParticleGfx_LoadTextureCallbackIa8Frame_32x32,
        ParticleGfx_DrawBillboardTextureAlphaRotatedQuad,
        &gBattleAnimAssetPointers[17],
    },
};

ParticleEffectData gBattleAnimParticleDescriptors[] = {
    {
        0x00000001,
        &gParticleDescriptorChildren[0],
    },
    {
        0x00000001,
        &gParticleDescriptorChildren[1],
    },
    {
        0x00000001,
        &gParticleDescriptorChildren[2],
    },
    {
        0x00000001,
        &gParticleDescriptorChildren[3],
    },
    {
        0x00000001,
        &gParticleDescriptorChildren[4],
    },
    {
        0x00000001,
        &gParticleDescriptorChildren[7],
    },
    {
        0x00000003,
        BattleAnim_DrawParticleNoop,
    },
    {
        0x00000001,
        &gParticleDescriptorChildren[8],
    },
    {
        0x00000001,
        &gParticleDescriptorChildren[9],
    },
    {
        0x00000001,
        &gParticleDescriptorChildren[10],
    },
    {
        0x00000001,
        &gParticleDescriptorChildren[55],
    },
    {
        0x00000001,
        &gParticleDescriptorChildren[11],
    },
    {
        0x00000001,
        &gParticleDescriptorChildren[12],
    },
    {
        0x00000001,
        &gParticleDescriptorChildren[13],
    },
    {
        0x00000001,
        &gParticleDescriptorChildren[14],
    },
    {
        0x00000003,
        BattleAnim_DrawAsset13FrameI4YScaledQuadA,
    },
    {
        0x00000003,
        BattleAnim_DrawAsset13FrameI4YScaledQuadB,
    },
    {
        0x00000003,
        BattleAnim_DrawAsset13FrameI4YScaledQuadC,
    },
    {
        0x00000003,
        BattleAnim_DrawAsset13FrameI4ModelQuadA,
    },
    {
        0x00000003,
        BattleAnim_DrawAsset13FrameI4ModelQuadB,
    },
    {
        0x00000003,
        BattleAnim_DrawAsset13FrameI4ModelQuadC,
    },
    {
        0x00000001,
        &gParticleDescriptorChildren[16],
    },
    {
        0x00000001,
        &gParticleDescriptorChildren[22],
    },
    {
        0x00000001,
        &gParticleDescriptorChildren[23],
    },
    {
        0x00000001,
        &gParticleDescriptorChildren[17],
    },
    {
        0x00000001,
        &gParticleDescriptorChildren[18],
    },
    {
        0x00000001,
        &gParticleDescriptorChildren[56],
    },
    {
        0x00000001,
        &gParticleDescriptorChildren[5],
    },
    {
        0x00000003,
        BattleAnim_DrawAsset1BI4TriangleA,
    },
    {
        0x00000003,
        BattleAnim_DrawAsset1BI4TriangleB,
    },
    {
        0x00000003,
        BattleAnim_DrawAsset13FrameDiv2I4Quad,
    },
    {
        0x00000001,
        &gParticleDescriptorChildren[19],
    },
    {
        0x00000001,
        &gParticleDescriptorChildren[20],
    },
    {
        0x00000001,
        &gParticleDescriptorChildren[24],
    },
    {
        0x00000001,
        &gParticleDescriptorChildren[21],
    },
    {
        0x00000001,
        &gParticleDescriptorChildren[25],
    },
    {
        0x00000001,
        &gParticleDescriptorChildren[26],
    },
    {
        0x00000003,
        BattleAnim_DrawParticleFullScreenColorOverlay,
    },
    {
        0x00000003,
        BattleAnim_DrawAsset18FrameI4ModelQuad,
    },
    {
        0x00000003,
        BattleAnim_DrawAssetA9I4XYScaledQuad,
    },
    {
        0x00000003,
        BattleAnim_DrawAsset19I4AtlasYScaled,
    },
    {
        0x00000003,
        BattleAnim_DrawAsset1AFrameI4Quad,
    },
    {
        0x00000001,
        &gParticleDescriptorChildren[15],
    },
    {
        0x00000003,
        BattleAnim_DrawAsset1CRgba16Quad,
    },
    {
        0x00000003,
        BattleAnim_DrawAsset1ERgba16Quad,
    },
    {
        0x00000003,
        BattleAnim_DrawAssetC3Rgba16Quad,
    },
    {
        0x00000003,
        BattleAnim_DrawAsset1DRotatedI4Quad,
    },
    {
        0x00000003,
        BattleAnim_DrawAsset1FAnimatedI4WithAsset20DisplayList,
    },
    {
        0x00000003,
        BattleAnim_DrawAssetBcRgba16WithAssetBdDisplayList,
    },
    {
        0x00000003,
        BattleAnim_DrawAssets27And28LayeredI4QuadVariantA,
    },
    {
        0x00000003,
        BattleAnim_DrawAssets27And28LayeredI4QuadVariantB,
    },
    {
        0x00000003,
        BattleAnim_DrawAsset29DualI4LayeredQuad,
    },
    {
        0x00000001,
        &gParticleDescriptorChildren[27],
    },
    {
        0x00000001,
        &gParticleDescriptorChildren[6],
    },
    {
        0x00000001,
        &gParticleDescriptorChildren[45],
    },
    {
        0x00000001,
        &gParticleDescriptorChildren[28],
    },
    {
        0x00000001,
        &gParticleDescriptorChildren[29],
    },
    {
        0x00000001,
        &gParticleDescriptorChildren[30],
    },
    {
        0x00000001,
        &gParticleDescriptorChildren[31],
    },
    {
        0x00000001,
        &gParticleDescriptorChildren[32],
    },
    {
        0x00000001,
        &gParticleDescriptorChildren[33],
    },
    {
        0x00000001,
        &gParticleDescriptorChildren[34],
    },
    {
        0x00000001,
        &gParticleDescriptorChildren[35],
    },
    {
        0x00000001,
        &gParticleDescriptorChildren[54],
    },
    {
        0x00000001,
        &gParticleDescriptorChildren[36],
    },
    {
        0x00000003,
        BattleAnim_DrawAsset5EI4AtlasYScaled,
    },
    {
        0x00000001,
        &gParticleDescriptorChildren[37],
    },
    {
        0x00000001,
        &gParticleDescriptorChildren[38],
    },
    {
        0x00000001,
        &gParticleDescriptorChildren[51],
    },
    {
        0x00000001,
        &gParticleDescriptorChildren[39],
    },
    {
        0x00000001,
        &gParticleDescriptorChildren[40],
    },
    {
        0x00000001,
        &gParticleDescriptorChildren[41],
    },
    {
        0x00000001,
        &gParticleDescriptorChildren[42],
    },
    {
        0x00000001,
        &gParticleDescriptorChildren[43],
    },
    {
        0x00000001,
        &gParticleDescriptorChildren[44],
    },
    {
        0x00000001,
        &gParticleDescriptorChildren[46],
    },
    {
        0x00000001,
        &gParticleDescriptorChildren[47],
    },
    {
        0x00000001,
        &gParticleDescriptorChildren[48],
    },
    {
        0x00000003,
        BattleAnim_DrawAsset76Ia8FrameWithAsset77I4OverlayPipelineA,
    },
    {
        0x00000003,
        BattleAnim_DrawAsset76Ia8FrameWithAsset77I4OverlayPipelineB,
    },
    {
        0x00000001,
        &gParticleDescriptorChildren[49],
    },
    {
        0x00000001,
        &gParticleDescriptorChildren[50],
    },
    {
        0x00000003,
        BattleAnim_DrawAsset87AnimatedI4Quad,
    },
    {
        0x00000001,
        &gParticleDescriptorChildren[52],
    },
    {
        0x00000001,
        &gParticleDescriptorChildren[53],
    },
    {
        0x00000000,
        NULL,
    },
};

static func_D_84390320 gStateFunctionTable[] = {
    BattleAnim_EffectStartNop, BattleAnim_StartEffect1Descriptor2FPhaseFadeOut, BattleAnim_StartEffect2Descriptor08IndexedScaleDelayFade, BattleAnim_StartEffect3ModelTintAndVerticalFade, BattleAnim_StartEffect4TintDescriptor53ScalePulse, BattleAnim_EffectStartNop, BattleAnim_StartEffect6AnimatedScaleAndBurstEmitter,
    BattleAnim_StartEffect7GlobalTintFade, BattleAnim_StartEffect8ModelBurstAndVerticalFade, BattleAnim_EffectStartNop, BattleAnim_StartEffect10Model60AndModelAnimWait, BattleAnim_StartEffect11GlobalTintFade, BattleAnim_StartEffect12DelayedModelAnim, BattleAnim_StartEffect13SecondaryOwnerSpeciesBranch,
    BattleAnim_StartEffect14ModelAnimAndMoveKeyedTintParticles, BattleAnim_StartEffect15Descriptor08IndexedScaleDelayFade, BattleAnim_StartEffect16TintDescriptor34Sequence, BattleAnim_StartEffect17ModelAnimFinish, BattleAnim_StartEffect18ScatterRadialAndColumnSequence, BattleAnim_EffectStartNop, BattleAnim_EffectStart_Generic,
    ParticleEffect_WaterAnimBurst, BattleAnim_StartEffect22RotatingPaletteNoTint, BattleAnim_StartEffect23SmokeWithMarker, ParticleEffect_PaletteScriptBurst, BattleAnim_EffectStartNop, BattleAnim_StartEffect26TintDescriptor53ScalePulse, BattleAnim_EffectStartNop,
    ParticleEffect_RegisterEffectE0, ParticleEffect_GroupSetupTintAndDefaultBurst, ParticleEffect_FinalGroupSetup, ParticleEffect_ComplexNodeSetup, BattleAnim_EffectStartNop, BattleAnim_EffectStartNop, ParticleEffect_RegisterSparkle,
    BattleAnim_StartEffect35SmokeTexture1, ParticleEffect_BasicMultiBurstDelayedSprayOnly, ParticleEffect_SimpleBurstScript, ParticleEffect_RegisterExplosion, BattleAnim_StartEffect39TintRampAndModelAnimWait, ParticleEffect_RegisterLargeExplosion, ParticleEffect_TextureSetup,
    BattleAnim_EffectStartNop, BattleAnim_EffectStartNop, BattleAnim_EffectStartNop, ParticleEffect_SetMode, BattleAnim_EffectStartNop, BattleAnim_StartEffect47TintDescriptor53ScalePulseAndDescriptor4AFade, SpawnTimedFireballEffect,
    ParticleEffect_SimpleNodeEntry, BattleAnim_StartEffects50And82TintRampAndModelScaleFade, BattleAnim_EffectStartNop, BattleAnim_StartEffect52ModelAnim, BattleAnim_StartEffect53Descriptor33FadeAndDescriptor47ScaleMotion, BattleAnim_EffectStartNop, BattleAnim_StartEffect55ModelAnimWaitMarkerSlotAndScaleFall,
    ParticleEffect_AdditionalNodeSetup, BattleAnim_StartEffect57GlobalTintFade, BattleAnim_StartEffect58ScaleFadesAndBurstEmitter, BattleAnim_CreateStreamSprayColumnEffect, ParticleEffect_GroupSetupTintAndDefaultBurst, ParticleEffect_HandleStateSetup, BattleAnim_EffectStartNop,
    ParticleEffect_RegisterHandlers_Default, BattleAnim_StartEffect64ModelAnimWait, ParticleEffect_RegisterParticleNodes, ParticleEffect_RegisterMultipleHandlers, BattleAnim_EffectStartNop, BattleAnim_StartEffect68ModelAnimWaitAndDescriptor42ScaleFall, BattleAnim_StartEffect69ModelPhaseWaitAndFallingParticles,
    BattleAnim_StartEffect70TintDescriptor53ScalePulse, BattleAnim_StartEffect71SpecialModelColorCycle, BattleAnim_StartEffect72ModelAnimWait, BattleAnim_CreateCollisionRandomEffect, BattleAnim_StartEffect74SpecialModelColorCycle, ParticleEffect_RegisterHandlers_Alternate, BattleAnim_StartEffect76Descriptor33FadeAndDescriptor47ScaleMotion,
    BattleAnim_StartEffects77And120SparkFades, BattleAnim_StartEffect78TintDescriptor53ScaleGrow, BattleAnim_StartEffect79ModelAnimWaitAndDescriptor25AlphaFade, ParticleEffect_RegisterDefaultTexture, ParticleEffect_AdvancedModeSetup, BattleAnim_StartEffects50And82TintRampAndModelScaleFade, ParticleEffect_SimpleBurst,
    BattleAnim_StartEffect84SmokeLongDuration, ParticleEffect_FinalSetupSpiralAndVerticalFade, ParticleEffect_RegisterLargeExplosionAndEffects, BattleAnim_StartEffect87TintRampAnimVerticalFade, ParticleEffect_MultiNodeEffect88Palette7, ParticleEffect_MultiNodeD, ParticleEffect_PortraitBurst,
    ParticleEffect_PortraitBurstNode, ParticleEffect_PortraitBurstCheck, ParticleEffect_WaterAnimFirework, ParticleEffect_SimpleBurstAnimWaitDelayedTintFade, ParticleEffect_PaletteMultiBurstCleanupWithTintFade, ParticleEffect_PaletteBurstVariant4Model8D, ParticleEffect_PaletteBurstVariant2Model8EDelayedFadeOut,
    BattleAnim_EffectStartNop, ParticleEffect_BasicMultiBurst, ParticleEffect_SimpleBurstAnimWaitDelayedAlphaFadeOut, ParticleEffect_RotationEntry, BattleAnim_DisableEffectSpawningAlias, ParticleEffect_InitSmoke, ParticleEffect_InitFire,
    ParticleEffect_TriggerSpecial, ParticleEffect_AlphaBurst, ParticleEffect_AlphaBurstPalette17, ParticleEffect_AdditionalSetupDualRiseFade, ParticleEffect_SimpleGroupSetup, ParticleEffect_ComplexGroupSetup, BattleAnim_StartEffect111GlobalTintAndSpecialModelColorCycle,
    ParticleEffect_PortraitBurstInit, ParticleEffect_TriggerDefaultPalette1B, ParticleEffect_FinalSetupRiseAndVerticalFade, ParticleEffect_FinalSetupPortraitBurst, ParticleEffect_AdditionalRiseFade, ParticleEffect_StateCollisionSetupDesc29ScaleAnimFade, ParticleEffect_CreateWithCallback,
    ParticleEffect_CreateCallback, BattleAnim_StartEffects77And120SparkFades, ParticleEffect_TriggerDefaultPalette1BWithTintFade, BattleAnim_StartEffect122GlobalAndOwnerTintFade, ParticleEffect_ConditionalStateSetup, ParticleEffect_CollisionResponseSwitch, ParticleEffect_RegisterCallbacks,
    BattleAnim_EffectStart_Special, BattleAnim_StartEffect127Descriptor39ScaleFade, BattleAnim_StartEffect128Descriptor39ScaleFade, ParticleEffect_CreateTypeX, ParticleEffect_CreateSmoke, ParticleEffect_CreateSmokeHighPriority, ParticleEffect_CreateDual,
    BattleAnim_StartEffect133ModeOrbitBurstAndEffect135Followup, BattleAnim_StartEffect134ModeOrbitAndMetadataBurst, BattleAnim_StartEffect135ExpandingFlashAndRisingScaleFade, BattleAnim_EffectStartNop, BattleAnim_StartEffect137Descriptor3FRisingFade, ParticleEffect_TextureNodeSetup, BattleAnim_StartEffect139DualRepeatingSparks,
    BattleAnim_StartEffect140StartEffect139Alias, BattleAnim_StartEffect141GridRiseAndFallingBurst, BattleAnim_StartEffect142StartEffect141Alias, BattleAnim_StartEffect143ModeOrbitAndMetadataBurst, BattleAnim_EffectStartNop,
};
static func_D_84390320 gParticleStateFunctionTable[] = {
    BattleAnim_EffectEndNop, BattleAnim_EffectEndNop, BattleAnim_EndEffect2AlphaFadesAndFallingSparks, ParticleEffect_SpecialCollisionSetup, ParticleEffect_MultiTextureSetup, ParticleEffect_DynamicCollisionSetup, ParticleEffect_RegisterPaletteVariants,
    ParticleEffect_PaletteMultiBurst, BattleAnim_CreateSprayColumnEffect, BattleAnim_EffectEndNop, ParticleEffect_RegisterAnimationCallbacks, BattleAnim_EffectEndNop, BattleAnim_EffectEndNop, ParticleEffect_RegisterSpecific,
    ParticleEffect_InitializeGroup, BattleAnim_EndEffect15ExplosionTintPalette35, ParticleEffect_AdvancedMultiBurst, ParticleEffect_RegisterSmoke, ParticleEffect_ModeSpecificSetup, BattleAnim_EffectEndNop, BattleAnim_EndEffect20ParticleComboBasic,
    ParticleEffect_RegisterModeSpecific, ParticleEffect_InitExplosionSet, ParticleEffect_RegisterAll, BattleAnim_EffectEndNop, ParticleEffect_PlaySoundAndReset, BattleAnim_EndEffect26GravityScatterFallSequence, BattleAnim_EndEffect27AdvancedParticleCombo,
    BattleAnim_CreateBurstStreamEffect, ParticleEffect_InitFireSet, ParticleEffect_HandleCollisionSetup, ParticleEffect_RegisterMultiple, BattleAnim_EffectEndNop, BattleAnim_EffectEndNop, BattleAnim_EndEffect34DelayedRotatingBounceFades,
    ParticleEffect_ConfigTexture7Palette1, ParticleEffect_ConfigTexture9Palette2, ParticleEffect_SpecialSetupBurstPalette3, ParticleEffect_SpecialSetupBurstPalette4, ParticleEffect_AdditionalSetupBurstAndRiseFade, ParticleEffect_InitSparkleSet, BattleAnim_EndEffect41Descriptor34Burst,
    ParticleEffect_ModeSetup, ParticleEffect_CollisionSetup, BattleAnim_EndEffect44ConfigMotion6, ParticleEffect_CombinedSetupBurst3DRandom, ParticleEffect_CombinedSetupBurstHorizontalRandom, ParticleEffect_SpecialSetupDelayedScatterPalette1, BattleAnim_EffectEndNop,
    ParticleEffect_RegisterColorAnim, ParticleEffect_RegisterHandler_WithParticleData, ParticleEffect_WaterAnimBurstTintFadeOnly, ParticleEffect_MultiHandleSetup, BattleAnim_EndEffect53GrowRecolorAndBounceFades, BattleAnim_EndEffect54TintRampDelayedColorFade, ParticleEffect_SimpleNodeSetup,
    BattleAnim_EndEffect56TintRampRisingSpread, ParticleEffect_FullSetupTintFadeOutAndRestore, BattleAnim_EndEffect58ModelAnimVerticalFade, ParticleEffect_InitCombinedSet, ParticleEffect_WaterAnimFireworkModel42RotationFollow, ParticleEffect_SimpleBurstTintPulseAnimWaitPaletteC, ParticleEffect_PaletteMultiBurstNoCleanupNoTintFade,
    ParticleEffect_FireworkBurst, ParticleEffect_FireballBurst, ParticleEffect_FireworkEntry, ParticleEffect_SimpleNodeBurst, BattleAnim_EndEffect67GravityAndScalePulseFades, BattleAnim_EndEffect68PaletteRotateAndFlickerFades, BattleAnim_EndEffect69PaletteRotateWithExpandingHoldFade,
    BattleAnim_EndEffect70ScaleFadesAndSprayColumns, BattleAnim_EndEffect71PaletteApproachWithExpandingScaleFades, BattleAnim_CreateSprayColumnEffectTrigger, ParticleEffect_AlphaFireworkPalette17, ParticleEffect_AlphaFirework, ParticleEffect_MultiNodeAEntry, ParticleEffect_TriggerAnother,
    ParticleEffect_TriggerDefaultPalette1C, BattleAnim_EndEffect78ModelAnimDelayedMotionAndFallingParticles, BattleAnim_EndEffect79ModelPaletteFade, BattleAnim_EndEffect80ConfigMotion16, BattleAnim_EndEffects81And82TintRampAndModelScaleFade, BattleAnim_EndEffects81And82TintRampAndModelScaleFade, BattleAnim_EndEffect83TintRampAndDescriptor34Burst,
    ParticleEffect_TriggerDefaultPalette1CWithTintRamps, ParticleEffect_StateCollisionSetupDesc2BGravityFall, BattleAnim_EndEffect86ModePositionedAnimFades, BattleAnim_EndEffect87GravityFallDelay, ParticleEffect_CollisionAndBurstSetup, BattleAnim_EffectEndNop,
};
static u8 gBattleScript_LoadGfxEmpty[] = {
    0x3F, 0x00, 0x00, 0x00, 0x3F, 0x00, 0x00, 0x00, 0x3F, 0x00, 0x00, 0x00,
    0x3F, 0x00, 0x00, 0x00, 0x01, 0x3F, 0x00, 0x00, 0x3F, 0x00, 0x00, 0x00,

};
static u8 gBattleScript_LoadGfx03[] = {
    0x03,
    0x3F,
    0x00,
    0x00,

};
static u8 gBattleScript_LoadGfx04[] = {
    0x04,
    0x3F,
    0x00,
    0x00,

};
static u8 gBattleScript_LoadGfx05[] = {
    0x05,
    0x3F,
    0x00,
    0x00,

};
static u8 gBattleScript_LoadGfx06[] = {
    0x06,
    0x3F,
    0x00,
    0x00,

};
static u8 gBattleScript_LoadGfx09[] = {
    0x09,
    0x3F,
    0x00,
    0x00,

};
static u8 gBattleScript_LoadGfx0A[] = {
    0x0A,
    0x3F,
    0x00,
    0x00,

};
static u8 gBattleScript_LoadGfx0B[] = {
    0x0B,
    0x3F,
    0x00,
    0x00,

};
static u8 gBattleScript_LoadGfx0C[] = {
    0x0C, 0x3F, 0x00, 0x00, 0x0D, 0x3F, 0x00, 0x00,

};
static u8 gBattleScript_LoadGfx0E[] = {
    0x0E,
    0x3F,
    0x00,
    0x00,

};
static u8 gBattleScript_LoadGfx0F[] = {
    0x0F,
    0x3F,
    0x00,
    0x00,

};
static u8 gBattleScript_LoadGfx10[] = {
    0x10,
    0x3F,
    0x00,
    0x00,

};
static u8 gBattleScript_LoadGfx11[] = {
    0x11,
    0x3F,
    0x00,
    0x00,

};
static u8 gBattleScript_LoadGfx11_3D[] = {
    0x11,
    0x3D,
    0x3F,
    0x00,

};
static u8 gBattleScript_LoadGfx12[] = {
    0x12,
    0x3F,
    0x00,
    0x00,

};
static u8 gBattleScript_LoadGfx13[] = {
    0x13,
    0x3F,
    0x00,
    0x00,

};
static u8 gBattleScript_LoadGfx14[] = {
    0x14, 0x3F, 0x00, 0x00, 0x15, 0x3F, 0x00, 0x00,

};
static u8 gBattleScript_LoadGfx16[] = {
    0x16, 0x3F, 0x00, 0x00, 0x17, 0x3F, 0x00, 0x00,

};
static u8 gBattleScript_LoadGfx18[] = {
    0x18,
    0x3F,
    0x00,
    0x00,

};
static u8 gBattleScript_LoadGfx19_32[] = {
    0x19,
    0x32,
    0x3F,
    0x00,

};
static u8 gBattleScript_LoadGfx1A[] = {
    0x1A,
    0x3F,
    0x00,
    0x00,

};
static u8 gBattleScript_LoadGfx1B_27[] = {
    0x1B,
    0x27,
    0x3F,
    0x00,

};
static u8 gBattleScript_LoadGfx1C[] = {
    0x1C,
    0x3F,
    0x00,
    0x00,

};
static u8 gBattleScript_LoadGfx27[] = {
    0x27,
    0x3F,
    0x00,
    0x00,

};
static u8 D_843868AC[] = {
    0x1E,
    0x3F,
    0x00,
    0x00,

};
static u8 gBattleScript_AnimAttack[] = {
    0x1F,
    0x3F,
    0x00,
    0x00,

};
static u8 gBattleScript_LoadGfx20[] = {
    0x20,
    0x3F,
    0x00,
    0x00,

};
static u8 gBattleScript_AnimHit[] = {
    0x21,
    0x3F,
    0x00,
    0x00,

};
static u8 gBattleScript_AnimMiss[] = {
    0x22,
    0x3F,
    0x00,
    0x00,

};
static u8 gBattleScript_AnimFaint[] = {
    0x23, 0x3F, 0x00, 0x00, 0x24, 0x3F, 0x00, 0x00,

};
static u8 gBattleScript_LoadGfx25[] = {
    0x25,
    0x3F,
    0x00,
    0x00,

};
static u8 gBattleScript_LoadGfx26_11[] = {
    0x26,
    0x11,
    0x3F,
    0x00,

};
static u8 gBattleScript_LoadGfx27_32[] = {
    0x27,
    0x32,
    0x3F,
    0x00,

};
static u8 gBattleScript_LoadGfx28[] = {
    0x28,
    0x3F,
    0x00,
    0x00,

};
static u8 gBattleScript_LoadGfx29_03[] = {
    0x29,
    0x03,
    0x3F,
    0x00,

};
static u8 gBattleScript_LoadGfx2A[] = {
    0x2A,
    0x3F,
    0x00,
    0x00,

};
static u8 gBattleScript_LoadGfx2B_11[] = {
    0x2B,
    0x11,
    0x3F,
    0x00,

};
static u8 gBattleScript_LoadGfx17[] = {
    0x17,
    0x3F,
    0x00,
    0x00,

};
static u8 gBattleScript_LoadGfx09_Alt[] = {
    0x09,
    0x3F,
    0x00,
    0x00,

};
static u8 gBattleScript_LoadGfx0B_Alt[] = {
    0x0B, 0x3F, 0x00, 0x00, 0x0E, 0x3F, 0x00, 0x00,

};
static u8 gBattleScript_LoadGfx14_Alt[] = {
    0x14,
    0x3F,
    0x00,
    0x00,

};
static u8 gBattleScript_LoadGfx15[] = {
    0x15,
    0x3F,
    0x00,
    0x00,

};
static u8 gBattleScript_LoadGfx1E[] = {
    0x1E,
    0x3F,
    0x00,
    0x00,

};
static u8 gBattleScript_LoadGfx10_Alt[] = {
    0x10,
    0x3F,
    0x00,
    0x00,

};
static u8 gBattleScript_LoadGfx14_Alt2[] = {
    0x14,
    0x3F,
    0x00,
    0x00,

};
static u8 gBattleScript_LoadGfx0C_Alt[] = {
    0x0C,
    0x3F,
    0x00,
    0x00,

};
static u8 gBattleScript_LoadGfx07[] = {
    0x07,
    0x3F,
    0x00,
    0x00,

};
static u8 gBattleScript_LoadGfx36[] = {
    0x36,
    0x3F,
    0x00,
    0x00,

};
static u8 gBattleScript_LoadGfx18_0D[] = {
    0x18,
    0x0D,
    0x3F,
    0x00,

};
static u8 gBattleScript_LoadGfx03_Alt[] = {
    0x03, 0x3F, 0x00, 0x00, 0x14, 0x3F, 0x00, 0x00,

};
static u8 gBattleScript_LoadGfx2C[] = {
    0x2C,
    0x3F,
    0x00,
    0x00,

};
static u8 gBattleScript_LoadGfx2C_Alt[] = {
    0x2C,
    0x3F,
    0x00,
    0x00,

};
static u8 gBattleScript_LoadGfx3C[] = {
    0x3C,
    0x3F,
    0x00,
    0x00,

};
static u8 gBattleScript_LoadGfx2D[] = {
    0x2D,
    0x3F,
    0x00,
    0x00,

};
static u8 gBattleScript_LoadGfx08[] = {
    0x08,
    0x3F,
    0x00,
    0x00,

};
static u8 gBattleScript_LoadGfx2E[] = {
    0x2E,
    0x3F,
    0x00,
    0x00,

};
static u8 gBattleScript_LoadGfx2F[] = {
    0x2F,
    0x3F,
    0x00,
    0x00,

};
static u8 gBattleScript_LoadGfx30[] = {
    0x30,
    0x3F,
    0x00,
    0x00,

};
static u8 gBattleScript_LoadGfx31[] = {
    0x31,
    0x3F,
    0x00,
    0x00,

};
static u8 gBattleScript_LoadGfx32[] = {
    0x32,
    0x3F,
    0x00,
    0x00,

};
static u8 gBattleScript_LoadGfx33[] = {
    0x33,
    0x3F,
    0x00,
    0x00,

};
static u8 gBattleScript_LoadGfx34[] = {
    0x34,
    0x3F,
    0x00,
    0x00,

};
static u8 gBattleScript_LoadGfx35[] = {
    0x35,
    0x3F,
    0x00,
    0x00,

};
static u8 gBattleScript_LoadGfx37[] = {
    0x37,
    0x3F,
    0x00,
    0x00,

};
static u8 gBattleScript_LoadGfx38[] = {
    0x38,
    0x3F,
    0x00,
    0x00,

};
static u8 gBattleScript_LoadGfx39[] = {
    0x39,
    0x3F,
    0x00,
    0x00,

};
static u8 gBattleScript_LoadGfx3A_0B[] = {
    0x3A,
    0x0B,
    0x3F,
    0x00,

};
static u8 gBattleScript_LoadGfx3B_2C[] = {
    0x3B,
    0x2C,
    0x3F,
    0x00,

};
static u8 gBattleScript_StartEmpty[] = {
    0x00, 0x00, 0x00, 0x00, 0x66, 0x00, 0x00, 0x00,

};
static u8 gBattleScript_Start90Nop[] = {
    0x90,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_Start01Descriptor2FPhaseFadeOut[] = {
    0x01,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_Start02Descriptor08IndexedScaleDelayFade[] = {
    0x02,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_Start03ModelTintAndVerticalFade[] = {
    0x03,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_NoSpawnThen04TintDescriptor53ScalePulse[] = {
    0x66, 0x04, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00,

};
static u8 gBattleScript_Start06AnimatedScaleAndBurstEmitter[] = {
    0x06,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_Start3AInitExplosionEffectSet[] = {
    0x3A,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_NoSpawnThen07TexturedRibbonSheet[] = {
    0x66,
    0x07,
    0x00,
    0x00,

};
static u8 gBattleScript_Start08ModelBurstAndVerticalFade[] = {
    0x08, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00,

};
static u8 gBattleScript_Start0AModel60AndModelAnimWait[] = {
    0x0A,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_NoSpawnThen0BGlobalTintFade[] = {
    0x66, 0x0B, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x00,

};
static u8 gBattleScript_Start0DSecondaryOwnerSpeciesBranch[] = {
    0x0D,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_Start7BConditionalStateSetup[] = {
    0x7B,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_Start7CCollisionResponseSwitch[] = {
    0x7C,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_Start0EModelAnimAndMoveKeyedTintParticles[] = {
    0x0E,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_Start0FDescriptor08IndexedScaleDelayFade[] = {
    0x0F,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_Start10TintDescriptor34Sequence[] = {
    0x10,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_Start11ModelAnimFinish[] = {
    0x11,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_Start12ScatterRadialAndColumnSequence[] = {
    0x12,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_Start13Radial20[] = {
    0x13, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00,

};
static u8 gBattleScript_Start15WaterAnimBurst[] = {
    0x15,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_Start16Effect22RotatingPaletteNoTint[] = {
    0x16,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_Start17Effect23SmokeWithMarker[] = {
    0x17,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_Start18PaletteScriptBurst[] = {
    0x18,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_Start19Nop[] = {
    0x19, 0x00, 0x00, 0x00, 0x1B, 0x00, 0x00, 0x00,

};
static u8 gBattleScript_Start1CRegisterEffectE0[] = {
    0x1C,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_Start4CRegisterEffectE0Alt[] = {
    0x4C,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_Start1DGroupSetupA[] = {
    0x1D, 0x00, 0x00, 0x00, 0x1E, 0x00, 0x00, 0x00,

};
static u8 gBattleScript_Start1FComplexNodeSetup[] = {
    0x1F,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_Start20Nop[] = {
    0x20,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_Start21Radial20[] = {
    0x21,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_Start22RegisterSparkle[] = {
    0x22,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_Start23Effect35SmokeTexture1[] = {
    0x23,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_NoSpawnThen24TerrainGrid[] = {
    0x66,
    0x24,
    0x00,
    0x00,

};
static u8 gBattleScript_Start25SimpleBurstScript[] = {
    0x25,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_Start26RegisterExplosion[] = {
    0x26,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_NoSpawnThen27InitSetWithFade[] = {
    0x66,
    0x27,
    0x00,
    0x00,

};
static u8 gBattleScript_Start28RegisterLargeExplosion[] = {
    0x28,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_Start29TextureSetup[] = {
    0x29,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_NoSpawnThen2ATrail40[] = {
    0x66,
    0x2A,
    0x00,
    0x00,

};
static u8 gBattleScript_Start2BTrail40Variant[] = {
    0x2B,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_Start2CTrail40GridAlt[] = {
    0x2C,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_NoSpawnThen2DSetMode[] = {
    0x66, 0x2D, 0x00, 0x00, 0x2E, 0x00, 0x00, 0x00,

};
static u8 gBattleScript_NoSpawnThen2FInitSetWithTexture53[] = {
    0x66,
    0x2F,
    0x00,
    0x00,

};
static u8 gBattleScript_Start30TimedFireball[] = {
    0x30,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_Start31SimpleNodeEntry[] = {
    0x31,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_Start32TintRampAndModelScaleFade[] = {
    0x32,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_Start52TintRampAndModelScaleFade[] = {
    0x52,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_Start59MultiNodeD[] = {
    0x59,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_Start34ModelAnim[] = {
    0x34, 0x00, 0x00, 0x00, 0x35, 0x00, 0x00, 0x00, 0x36, 0x00, 0x00, 0x00,

};
static u8 gBattleScript_Start37ModelAnimWaitMarkerSlotAndScaleFall[] = {
    0x37,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_Start35RegisterEffectE0Alt2_05RibbonMesh[] = {
    0x35,
    0x05,
    0x00,
    0x00,

};
static u8 gBattleScript_Start6AAlphaBurst[] = {
    0x6A,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_Start6BAlphaBurstPalette17[] = {
    0x6B,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_Start1BNop[] = {
    0x1B,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_Start56RegisterLargeExplosionAndEffects[] = {
    0x56,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_Start1EFinalGroupSetup[] = {
    0x1E,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_Start5DWaterAnimFirework[] = {
    0x5D,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_Start1CRegisterEffectE0_36RibbonMesh[] = {
    0x1C,
    0x36,
    0x00,
    0x00,

};
static u8 gBattleScript_Start0EModelAnimAndMoveKeyedTintParticles_Alt[] = {
    0x0E,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_Start40ModelAnimWait[] = {
    0x40,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_Start0CDelayedModelAnim[] = {
    0x0C,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_Start42RegisterMultipleHandlers[] = {
    0x42,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_Start5FPaletteMultiBurstCleanupWithTintFade[] = {
    0x5F,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_NoSpawnThen4EInitSetSingle[] = {
    0x66,
    0x4E,
    0x00,
    0x00,

};
static u8 gBattleScript_Start3BCreateStreamSprayColumnEffect[] = {
    0x3B,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_Start38AdditionalNodeSetup[] = {
    0x38,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_NoSpawnThen39SmallNodeSetupB[] = {
    0x66,
    0x39,
    0x00,
    0x00,

};
static u8 gBattleScript_Start3DHandleStateSetup[] = {
    0x3D,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_Start3EOwnerLinkedFourStream[] = {
    0x3E,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_Start7DRegisterCallbacks[] = {
    0x7D,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_Start7ESpecial[] = {
    0x7E,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_Start7FCreateVariant45[] = {
    0x7F,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_Start80CreateVariant47[] = {
    0x80,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_Start81CreateTypeX[] = {
    0x81,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_Start82CreateSmoke[] = {
    0x82,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_Start83CreateSmokeHighPriority[] = {
    0x83,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_Start84CreateDual[] = {
    0x84,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_Start8BDualRepeatingSparks[] = {
    0x8B,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_Start8CDualRepeatingSparksAlias[] = {
    0x8C,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_Start8DGridRiseAndFallingBurst[] = {
    0x8D,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_Start8EGridRiseAndFallingBurstAlias[] = {
    0x8E,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_Start85ModeOrbitBurstAndFollowup[] = {
    0x85,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_Start86ModeOrbitAndMetadataBurst[] = {
    0x86,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_Start8FModeOrbitAndMetadataBurst[] = {
    0x8F,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_Start87ExpandingFlashAndRisingScaleFade[] = {
    0x87,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_Start88Nop[] = {
    0x88,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_Start89Descriptor3FRisingFade[] = {
    0x89,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_Start8ATextureNodeSetup[] = {
    0x8A,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_Start3FRegisterHandlersDefault[] = {
    0x3F,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_Start41RegisterParticleNodes[] = {
    0x41,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_Start43OwnerAnchoredFourStream[] = {
    0x43,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_Start71TriggerDefaultPalette1B[] = {
    0x71,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_Start79TriggerDefaultPalette1BWithTintFade[] = {
    0x79,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_Start44ModelAnimWaitAndDescriptor42ScaleFall[] = {
    0x44,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_Start45ModelPhaseWaitAndFallingParticles[] = {
    0x45,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_NoSpawnThen46InitSetWithDifferentTiming[] = {
    0x66,
    0x46,
    0x00,
    0x00,

};
static u8 gBattleScript_Start47SpecialModelColorCycle[] = {
    0x47,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_Start6FGlobalTintAndSpecialModelColorCycle[] = {
    0x6F,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_Start48ModelAnimWait[] = {
    0x48,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_Start49CreateCollisionRandomEffect[] = {
    0x49,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_Start4ASpecialModelColorCycle[] = {
    0x4A,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_Start4BRegisterHandlersAlternate[] = {
    0x4B,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_NoSpawnThen78InitSmallGlowEffectSet[] = {
    0x66,
    0x78,
    0x00,
    0x00,

};
static u8 gBattleScript_Start4FModelAnimWaitAndDescriptor25AlphaFade[] = {
    0x4F,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_Start50RegisterDefaultTexture[] = {
    0x50,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_Start51AdvancedModeSetup[] = {
    0x51,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_Start53SimpleBurst[] = {
    0x53,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_Start54Effect84SmokeLongDuration[] = {
    0x54,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_Start55FinalSetupA[] = {
    0x55,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_Start72FinalSetupB[] = {
    0x72,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_Start73FinalSetupC[] = {
    0x73,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_Start74AdditionalRiseFade[] = {
    0x74,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_Start57Effect87TintRampAnimVerticalFade[] = {
    0x57,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_Start58MultiNodeEffect88Palette7[] = {
    0x58,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_Start59MultiNodeD_Alt[] = {
    0x59,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_Start5APortraitBurst[] = {
    0x5A,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_Start5BPortraitBurstNode[] = {
    0x5B,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_Start5CPortraitBurstCheck[] = {
    0x5C,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_Start5ESimpleBurstAnimWaitDelayedTintFade[] = {
    0x5E,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_Start60PaletteBurstVariant4Model8D[] = {
    0x60,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_Start61PaletteBurstVariant2Model8EDelayedFadeOut[] = {
    0x61,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_Start62Radial20[] = {
    0x62,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_Start63BasicMultiBurst[] = {
    0x63,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_Start64SimpleBurstAnimWaitDelayedAlphaFadeOut[] = {
    0x64,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_Start65RotationEntry[] = {
    0x65,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_NoSpawnThen1AEffect26DoubleTextureTrail[] = {
    0x66,
    0x1A,
    0x00,
    0x00,

};
static u8 gBattleScript_Start67InitSmoke[] = {
    0x67,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_Start68InitFire[] = {
    0x68,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_Start69TriggerSpecial[] = {
    0x69,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_Start6CAdditionalSetupA[] = {
    0x6C,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_Start6DSimpleGroupSetup[] = {
    0x6D,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_Start6EComplexGroupSetup[] = {
    0x6E,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_Start70PortraitBurstInit[] = {
    0x70,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_Start75StateCollisionSetupA[] = {
    0x75,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_Start76CreateWithCallback[] = {
    0x76,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_Start77CreateCallback[] = {
    0x77,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_Start7AGlobalAndOwnerTintFade[] = {
    0x7A,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_EndEmpty[] = {
    0x00, 0x00, 0x00, 0x00, 0x59, 0x00, 0x00, 0x00,

};
static u8 gBattleScript_MsgStart[] = {
    0x01,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_MsgEnd[] = {
    0x30, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00,

};
static u8 gBattleScript_End04_MultiTextureSetup[] = {
    0x04,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_End05_DynamicCollisionSetup[] = {
    0x05,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_End58_CollisionAndBurstSetup[] = {
    0x58, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00,

};
static u8 gBattleScript_End07_PaletteMultiBurst[] = {
    0x07,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_End08_SprayColumnEffect[] = {
    0x08,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_End48_SprayColumnEffectTrigger[] = {
    0x48,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_End09_Radial20[] = {
    0x09,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_End0A_RegisterAnimationCallbacks[] = {
    0x0A, 0x00, 0x00, 0x00, 0x0B, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x00, 0x0D, 0x00, 0x00, 0x00,

};
static u8 gBattleScript_End0E_InitializeGroup[] = {
    0x0E,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_End23_ConfigTexture7Palette1[] = {
    0x23,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_End24_ConfigTexture9Palette2[] = {
    0x24,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_End25_SpecialSetupBurstPalette3[] = {
    0x25,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_End54_25_TriggerDefault4AndSpecialSetupBurstPalette3[] = {
    0x54,
    0x25,
    0x00,
    0x00,

};
static u8 gBattleScript_End4D_0E_TriggerDefault2AndInitializeGroup[] = {
    0x4D,
    0x0E,
    0x00,
    0x00,

};
static u8 gBattleScript_End26_SpecialSetupBurstPalette4[] = {
    0x26,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_End0F_ExplosionTintPalette35[] = {
    0x0F,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_End10_AdvancedMultiBurst[] = {
    0x10,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_End11_RegisterSmoke[] = {
    0x11,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_End12_ModeSpecificSetup[] = {
    0x12, 0x00, 0x00, 0x00, 0x13, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00,

};
static u8 gBattleScript_End15_RegisterModeSpecific[] = {
    0x15,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_End16_ExplosionSet[] = {
    0x16,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_End17_RegisterAll[] = {
    0x17,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_End18_NoOp[] = {
    0x18,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_End19_PlaySoundAndReset[] = {
    0x19,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_End0D_0E_RegisterSpecificAndInitializeGroup[] = {
    0x0D,
    0x0E,
    0x00,
    0x00,

};
static u8 gBattleScript_End03_SpecialCollisionSetup[] = {
    0x03,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_End07_PaletteMultiBurst_Alt[] = {
    0x07,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_End22_InitParticleGroupBasic[] = {
    0x22,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_End35_SetWithCustomCallback[] = {
    0x35,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_End45_SetVariant2[] = {
    0x45, 0x00, 0x00, 0x00, 0x0E, 0x04, 0x00, 0x00,

};
static u8 gBattleScript_End1A_ComplexMovement[] = {
    0x1A,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_End09_Radial20_Alt[] = {
    0x09,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_End06_0E_RegisterPaletteVariantsAndInitializeGroup[] = {
    0x06,
    0x0E,
    0x00,
    0x00,

};
static u8 gBattleScript_End1B_AdvancedParticleCombo[] = {
    0x1B, 0x00, 0x00, 0x00, 0x1C, 0x00, 0x00, 0x00,

};
static u8 gBattleScript_End1D_FireSet[] = {
    0x1D,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_End1E_HandleCollisionSetup[] = {
    0x1E,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_End55_StateCollisionSetupDesc2BGravityFall[] = {
    0x55,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_End1F_RegisterMultiple[] = {
    0x1F,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_End20_Radial20[] = {
    0x20,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_End21_Radial20[] = {
    0x21,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_End4F_27_ColorVariantAndAdditionalSetupBurstAndRiseFade[] = {
    0x4F,
    0x27,
    0x00,
    0x00,

};
static u8 gBattleScript_End28_SparkleSet[] = {
    0x28,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_End29_Descriptor34Burst[] = {
    0x29,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_End2A_ModeSetup[] = {
    0x2A,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_End2B_CollisionSetup[] = {
    0x2B,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_End2C_ConfigMotion6[] = {
    0x2C,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_End2D_CombinedSetupBurst3DRandom[] = {
    0x2D,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_End4F_2D_ColorVariantAndCombinedSetupBurst3DRandom[] = {
    0x4F,
    0x2D,
    0x00,
    0x00,

};
static u8 gBattleScript_End2E_CombinedSetupBurstHorizontalRandom[] = {
    0x2E,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_End2F_SpecialSetupDelayedScatterPalette1[] = {
    0x2F,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_End31_RegisterColorAnim[] = {
    0x31,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_End32_RegisterHandlerWithParticleData[] = {
    0x32,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_End3F_23_FireworkBurstAndConfigTexture7Palette1[] = {
    0x3F, 0x23, 0x00, 0x00, 0x33, 0x00, 0x00, 0x00,

};
static u8 gBattleScript_End34_MultiHandleSetup[] = {
    0x34,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_End36_TintRampDelayedColorFade[] = {
    0x36,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_End37_SimpleNodeSetup[] = {
    0x37,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_End39_FullSetupTintFadeOutAndRestore[] = {
    0x39,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_End49_AlphaFireworkPalette17[] = {
    0x49,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_End4A_AlphaFirework[] = {
    0x4A,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_End3A_ModelAnimVerticalFade[] = {
    0x3A,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_End4B_MultiNodeAEntry[] = {
    0x4B,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_End3B_InitCombinedSet[] = {
    0x3B,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_End3C_WaterAnimFireworkModel42RotationFollow[] = {
    0x3C,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_End3D_SimpleBurstTintPulseAnimWaitPaletteC[] = {
    0x3D,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_End3E_PaletteMultiBurstNoCleanupNoTintFade[] = {
    0x3E,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_End40_FireballBurst[] = {
    0x40,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_End2D_1E_CombinedSetupBurst3DRandomAndHandleCollisionSetup[] = {
    0x2D,
    0x1E,
    0x00,
    0x00,

};
static u8 gBattleScript_End41_FireworkEntry[] = {
    0x41,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_End42_SimpleNodeBurst[] = {
    0x42,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_End43_SetWithMultiple[] = {
    0x43,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_End44_SetWithTimedFireball[] = {
    0x44,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_End46_SetWithComplex[] = {
    0x46,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_End47_SetVariant3[] = {
    0x47,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_End50_4C_ConfigMotion16AndTriggerAnother[] = {
    0x50,
    0x4C,
    0x00,
    0x00,

};
static u8 gBattleScript_End38_TintRampRisingSpread[] = {
    0x38, 0x00, 0x00, 0x00, 0x4D, 0x00, 0x00, 0x00,

};
static u8 gBattleScript_End4E_ModelAnimDelayedMotionAndFallingParticles[] = {
    0x4E, 0x00, 0x00, 0x00, 0x4F, 0x00, 0x00, 0x00,

};
static u8 gBattleScript_End51_TintRampAndModelScaleFade[] = {
    0x51,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_End52_TintRampAndModelScaleFade[] = {
    0x52,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_End02_ComplexParticleSequence[] = {
    0x02,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_End56_ThreeInstanceSet[] = {
    0x56,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_End53_TintRampAndDescriptor34Burst[] = {
    0x53,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_End57_23_BurstAndConfigTexture7Palette1[] = {
    0x57,
    0x23,
    0x00,
    0x00,
};
static u8* Fragment62_SubTablePtr2D[][2] = {
    {
        gBattleScript_StartEmpty,
        gBattleScript_LoadGfxEmpty,
    },
    {
        gBattleScript_Start85ModeOrbitBurstAndFollowup,
        gBattleScript_LoadGfx2C,
    },
    {
        gBattleScript_Start86ModeOrbitAndMetadataBurst,
        gBattleScript_LoadGfx2C,
    },
    {
        gBattleScript_Start87ExpandingFlashAndRisingScaleFade,
        gBattleScript_LoadGfx2C_Alt,
    },
    {
        gBattleScript_Start88Nop,
        gBattleScript_LoadGfx2C_Alt,
    },
    {
        gBattleScript_Start89Descriptor3FRisingFade,
        gBattleScript_LoadGfx2D,
    },
    {
        gBattleScript_Start8ATextureNodeSetup,
        gBattleScript_LoadGfxEmpty,
    },
    {
        gBattleScript_StartEmpty,
        gBattleScript_LoadGfxEmpty,
    },
    {
        gBattleScript_Start8BDualRepeatingSparks,
        gBattleScript_LoadGfx2C_Alt,
    },
    {
        gBattleScript_Start15WaterAnimBurst,
        gBattleScript_LoadGfx10,
    },
    {
        gBattleScript_Start8CDualRepeatingSparksAlias,
        gBattleScript_LoadGfx3C,
    },
    {
        gBattleScript_Start8DGridRiseAndFallingBurst,
        gBattleScript_LoadGfx3C,
    },
    {
        gBattleScript_Start8FModeOrbitAndMetadataBurst,
        gBattleScript_LoadGfx2C,
    },
    {
        gBattleScript_Start8EGridRiseAndFallingBurstAlias,
        gBattleScript_LoadGfx3C,
    },
    {
        gBattleScript_Start7AGlobalAndOwnerTintFade,
        gBattleScript_LoadGfxEmpty,
    },
};
static u8* Fragment62_DataPtrArray[] = {
    gBattleScript_StartEmpty, gBattleScript_Start7DRegisterCallbacks, gBattleScript_Start7ESpecial, gBattleScript_Start01Descriptor2FPhaseFadeOut, gBattleScript_Start45ModelPhaseWaitAndFallingParticles, gBattleScript_Start7FCreateVariant45,
    gBattleScript_Start80CreateVariant47, gBattleScript_Start81CreateTypeX, gBattleScript_Start82CreateSmoke, gBattleScript_Start83CreateSmokeHighPriority, gBattleScript_Start84CreateDual, gBattleScript_Start90Nop,
};
static u8* Fragment62_GroupPtrArray[] = {
    gBattleScript_EndEmpty, gBattleScript_MsgStart, gBattleScript_End09_Radial20, gBattleScript_MsgEnd, gBattleScript_End31_RegisterColorAnim,
};
static u8* Fragment62_SpecialPairPtr[] = { gBattleScript_StartEmpty, gBattleScript_Start2CTrail40GridAlt };
static u8* Fragment62_ComplexPtrTable[][5] = {
    {
        gBattleScript_StartEmpty,
        gBattleScript_StartEmpty,
        gBattleScript_EndEmpty,
        gBattleScript_LoadGfxEmpty,
        gBattleScript_LoadGfxEmpty,
    },
    {
        gBattleScript_StartEmpty,
        gBattleScript_StartEmpty,
        gBattleScript_End2C_ConfigMotion6,
        gBattleScript_LoadGfxEmpty,
        gBattleScript_LoadGfx18,
    },
    {
        gBattleScript_StartEmpty,
        gBattleScript_StartEmpty,
        gBattleScript_End2C_ConfigMotion6,
        gBattleScript_LoadGfxEmpty,
        gBattleScript_LoadGfx18,
    },
    {
        gBattleScript_StartEmpty,
        gBattleScript_StartEmpty,
        gBattleScript_End0E_InitializeGroup,
        gBattleScript_LoadGfxEmpty,
        gBattleScript_LoadGfx18,
    },
    {
        gBattleScript_StartEmpty,
        gBattleScript_StartEmpty,
        gBattleScript_End23_ConfigTexture7Palette1,
        gBattleScript_LoadGfxEmpty,
        gBattleScript_LoadGfx18,
    },
    {
        gBattleScript_Start0FDescriptor08IndexedScaleDelayFade,
        gBattleScript_StartEmpty,
        gBattleScript_End50_4C_ConfigMotion16AndTriggerAnother,
        gBattleScript_LoadGfx03,
        gBattleScript_LoadGfx18,
    },
    {
        gBattleScript_StartEmpty,
        gBattleScript_StartEmpty,
        gBattleScript_End0D_0E_RegisterSpecificAndInitializeGroup,
        gBattleScript_LoadGfxEmpty,
        gBattleScript_LoadGfx17,
    },
    {
        gBattleScript_Start38AdditionalNodeSetup,
        gBattleScript_StartEmpty,
        gBattleScript_End36_TintRampDelayedColorFade,
        gBattleScript_LoadGfx11,
        gBattleScript_LoadGfx18,
    },
    {
        gBattleScript_Start29TextureSetup,
        gBattleScript_StartEmpty,
        gBattleScript_End2A_ModeSetup,
        gBattleScript_AnimAttack,
        gBattleScript_LoadGfx18,
    },
    {
        gBattleScript_Start49CreateCollisionRandomEffect,
        gBattleScript_StartEmpty,
        gBattleScript_End2B_CollisionSetup,
        gBattleScript_LoadGfx0F,
        gBattleScript_LoadGfx18,
    },
    {
        gBattleScript_Start0DSecondaryOwnerSpeciesBranch,
        gBattleScript_StartEmpty,
        gBattleScript_End05_DynamicCollisionSetup,
        gBattleScript_LoadGfx0B,
        gBattleScript_LoadGfxEmpty,
    },
    {
        gBattleScript_Start47SpecialModelColorCycle,
        gBattleScript_StartEmpty,
        gBattleScript_End29_Descriptor34Burst,
        gBattleScript_LoadGfx08,
        gBattleScript_LoadGfx18,
    },
    {
        gBattleScript_Start6FGlobalTintAndSpecialModelColorCycle,
        gBattleScript_StartEmpty,
        gBattleScript_End53_TintRampAndDescriptor34Burst,
        gBattleScript_LoadGfx08,
        gBattleScript_LoadGfx18,
    },
    {
        gBattleScript_Start0AModel60AndModelAnimWait,
        gBattleScript_Start48ModelAnimWait,
        gBattleScript_End03_SpecialCollisionSetup,
        gBattleScript_LoadGfx09_Alt,
        gBattleScript_LoadGfx0B_Alt,
    },
    {
        gBattleScript_Start44ModelAnimWaitAndDescriptor42ScaleFall,
        gBattleScript_StartEmpty,
        gBattleScript_EndEmpty,
        gBattleScript_LoadGfx2E,
        gBattleScript_LoadGfxEmpty,
    },
    {
        gBattleScript_Start3DHandleStateSetup,
        gBattleScript_StartEmpty,
        gBattleScript_End1E_HandleCollisionSetup,
        gBattleScript_LoadGfx0B,
        gBattleScript_LoadGfxEmpty,
    },
    {
        gBattleScript_Start0AModel60AndModelAnimWait,
        gBattleScript_StartEmpty,
        gBattleScript_End2F_SpecialSetupDelayedScatterPalette1,
        gBattleScript_LoadGfx09,
        gBattleScript_LoadGfx18,
    },
    {
        gBattleScript_StartEmpty,
        gBattleScript_StartEmpty,
        gBattleScript_End57_23_BurstAndConfigTexture7Palette1,
        gBattleScript_LoadGfx0A,
        gBattleScript_LoadGfx18,
    },
    {
        gBattleScript_Start0AModel60AndModelAnimWait,
        gBattleScript_StartEmpty,
        gBattleScript_EndEmpty,
        gBattleScript_LoadGfx09,
        gBattleScript_LoadGfxEmpty,
    },
    {
        gBattleScript_StartEmpty,
        gBattleScript_Start28RegisterLargeExplosion,
        gBattleScript_End4F_2D_ColorVariantAndCombinedSetupBurst3DRandom,
        D_843868AC,
        gBattleScript_LoadGfx18,
    },
    {
        gBattleScript_Start13Radial20,
        gBattleScript_StartEmpty,
        gBattleScript_End09_Radial20,
        gBattleScript_LoadGfxEmpty,
        gBattleScript_LoadGfxEmpty,
    },
    {
        gBattleScript_StartEmpty,
        gBattleScript_StartEmpty,
        gBattleScript_End2D_CombinedSetupBurst3DRandom,
        gBattleScript_LoadGfxEmpty,
        gBattleScript_LoadGfx18,
    },
    {
        gBattleScript_Start75StateCollisionSetupA,
        gBattleScript_StartEmpty,
        gBattleScript_End55_StateCollisionSetupDesc2BGravityFall,
        gBattleScript_LoadGfx0B,
        gBattleScript_LoadGfx0A,
    },
    {
        gBattleScript_StartEmpty,
        gBattleScript_StartEmpty,
        gBattleScript_End4F_27_ColorVariantAndAdditionalSetupBurstAndRiseFade,
        gBattleScript_LoadGfxEmpty,
        gBattleScript_LoadGfx18,
    },
    {
        gBattleScript_StartEmpty,
        gBattleScript_StartEmpty,
        gBattleScript_End23_ConfigTexture7Palette1,
        gBattleScript_LoadGfxEmpty,
        gBattleScript_LoadGfx18,
    },
    {
        gBattleScript_Start02Descriptor08IndexedScaleDelayFade,
        gBattleScript_StartEmpty,
        gBattleScript_End50_4C_ConfigMotion16AndTriggerAnother,
        gBattleScript_LoadGfx03,
        gBattleScript_LoadGfx18,
    },
    {
        gBattleScript_StartEmpty,
        gBattleScript_StartEmpty,
        gBattleScript_End2C_ConfigMotion6,
        gBattleScript_LoadGfxEmpty,
        gBattleScript_LoadGfx18,
    },
    {
        gBattleScript_StartEmpty,
        gBattleScript_StartEmpty,
        gBattleScript_End2C_ConfigMotion6,
        gBattleScript_LoadGfxEmpty,
        gBattleScript_LoadGfx18,
    },
    {
        gBattleScript_Start1FComplexNodeSetup,
        gBattleScript_StartEmpty,
        gBattleScript_End37_SimpleNodeSetup,
        gBattleScript_LoadGfx16,
        gBattleScript_LoadGfx18,
    },
    {
        gBattleScript_StartEmpty,
        gBattleScript_StartEmpty,
        gBattleScript_End0E_InitializeGroup,
        gBattleScript_LoadGfxEmpty,
        gBattleScript_LoadGfx18,
    },
    {
        gBattleScript_Start77CreateCallback,
        gBattleScript_StartEmpty,
        gBattleScript_End25_SpecialSetupBurstPalette3,
        gBattleScript_LoadGfx06,
        gBattleScript_LoadGfx18,
    },
    {
        gBattleScript_Start76CreateWithCallback,
        gBattleScript_StartEmpty,
        gBattleScript_End2F_SpecialSetupDelayedScatterPalette1,
        gBattleScript_LoadGfx06,
        gBattleScript_LoadGfx18,
    },
    {
        gBattleScript_Start79TriggerDefaultPalette1BWithTintFade,
        gBattleScript_StartEmpty,
        gBattleScript_End54_25_TriggerDefault4AndSpecialSetupBurstPalette3,
        gBattleScript_LoadGfx06,
        gBattleScript_LoadGfx18,
    },
    {
        gBattleScript_StartEmpty,
        gBattleScript_StartEmpty,
        gBattleScript_End2C_ConfigMotion6,
        gBattleScript_LoadGfxEmpty,
        gBattleScript_LoadGfx18,
    },
    {
        gBattleScript_Start74AdditionalRiseFade,
        gBattleScript_StartEmpty,
        gBattleScript_End4F_2D_ColorVariantAndCombinedSetupBurst3DRandom,
        gBattleScript_LoadGfxEmpty,
        gBattleScript_LoadGfx18,
    },
    {
        gBattleScript_Start13Radial20,
        gBattleScript_StartEmpty,
        gBattleScript_End09_Radial20,
        gBattleScript_LoadGfxEmpty,
        gBattleScript_LoadGfxEmpty,
    },
    {
        gBattleScript_Start73FinalSetupC,
        gBattleScript_StartEmpty,
        gBattleScript_End2C_ConfigMotion6,
        gBattleScript_LoadGfx32,
        gBattleScript_LoadGfx18,
    },
    {
        gBattleScript_Start72FinalSetupB,
        gBattleScript_StartEmpty,
        gBattleScript_End2D_CombinedSetupBurst3DRandom,
        gBattleScript_LoadGfxEmpty,
        gBattleScript_LoadGfx18,
    },
    {
        gBattleScript_Start73FinalSetupC,
        gBattleScript_StartEmpty,
        gBattleScript_End2D_CombinedSetupBurst3DRandom,
        gBattleScript_LoadGfx32,
        gBattleScript_LoadGfx18,
    },
    {
        gBattleScript_StartEmpty,
        gBattleScript_StartEmpty,
        gBattleScript_EndEmpty,
        gBattleScript_LoadGfxEmpty,
        gBattleScript_LoadGfxEmpty,
    },
    {
        gBattleScript_Start43OwnerAnchoredFourStream,
        gBattleScript_StartEmpty,
        gBattleScript_End26_SpecialSetupBurstPalette4,
        gBattleScript_LoadGfx06,
        gBattleScript_LoadGfx18,
    },
    {
        gBattleScript_Start43OwnerAnchoredFourStream,
        gBattleScript_StartEmpty,
        gBattleScript_End26_SpecialSetupBurstPalette4,
        gBattleScript_LoadGfx06,
        gBattleScript_LoadGfx18,
    },
    {
        gBattleScript_Start43OwnerAnchoredFourStream,
        gBattleScript_StartEmpty,
        gBattleScript_End25_SpecialSetupBurstPalette3,
        gBattleScript_LoadGfx06,
        gBattleScript_LoadGfx18,
    },
    {
        gBattleScript_Start53SimpleBurst,
        gBattleScript_StartEmpty,
        gBattleScript_EndEmpty,
        gBattleScript_LoadGfx30,
        gBattleScript_LoadGfxEmpty,
    },
    {
        gBattleScript_Start4ASpecialModelColorCycle,
        gBattleScript_StartEmpty,
        gBattleScript_End29_Descriptor34Burst,
        gBattleScript_LoadGfx08,
        gBattleScript_LoadGfx18,
    },
    {
        gBattleScript_StartEmpty,
        gBattleScript_StartEmpty,
        gBattleScript_EndEmpty,
        gBattleScript_LoadGfxEmpty,
        gBattleScript_LoadGfxEmpty,
    },
    {
        gBattleScript_StartEmpty,
        gBattleScript_StartEmpty,
        gBattleScript_EndEmpty,
        gBattleScript_LoadGfxEmpty,
        gBattleScript_LoadGfxEmpty,
    },
    {
        gBattleScript_Start2BTrail40Variant,
        gBattleScript_StartEmpty,
        gBattleScript_EndEmpty,
        gBattleScript_AnimHit,
        gBattleScript_LoadGfxEmpty,
    },
    {
        gBattleScript_Start2CTrail40GridAlt,
        gBattleScript_StartEmpty,
        gBattleScript_EndEmpty,
        gBattleScript_AnimMiss,
        gBattleScript_LoadGfxEmpty,
    },
    {
        gBattleScript_NoSpawnThen2DSetMode,
        gBattleScript_StartEmpty,
        gBattleScript_End23_ConfigTexture7Palette1,
        gBattleScript_AnimFaint,
        gBattleScript_LoadGfx18,
    },
    {
        gBattleScript_Start62Radial20,
        gBattleScript_StartEmpty,
        gBattleScript_End21_Radial20,
        gBattleScript_LoadGfxEmpty,
        gBattleScript_LoadGfxEmpty,
    },
    {
        gBattleScript_Start11ModelAnimFinish,
        gBattleScript_StartEmpty,
        gBattleScript_End07_PaletteMultiBurst_Alt,
        gBattleScript_LoadGfx0E,
        gBattleScript_LoadGfxEmpty,
    },
    {
        gBattleScript_Start16Effect22RotatingPaletteNoTint,
        gBattleScript_StartEmpty,
        gBattleScript_End38_TintRampRisingSpread,
        gBattleScript_LoadGfx11,
        gBattleScript_LoadGfx18,
    },
    {
        gBattleScript_Start17Effect23SmokeWithMarker,
        gBattleScript_StartEmpty,
        gBattleScript_End16_ExplosionSet,
        gBattleScript_LoadGfx11,
        gBattleScript_LoadGfx18,
    },
    {
        gBattleScript_Start35RegisterEffectE0Alt2_05RibbonMesh,
        gBattleScript_StartEmpty,
        gBattleScript_EndEmpty,
        gBattleScript_LoadGfx14_Alt,
        gBattleScript_LoadGfxEmpty,
    },
    {
        gBattleScript_Start06AnimatedScaleAndBurstEmitter,
        gBattleScript_StartEmpty,
        gBattleScript_End02_ComplexParticleSequence,
        gBattleScript_LoadGfx03,
        gBattleScript_LoadGfx0E,
    },
    {
        gBattleScript_Start3AInitExplosionEffectSet,
        gBattleScript_StartEmpty,
        gBattleScript_End1B_AdvancedParticleCombo,
        gBattleScript_LoadGfx03,
        gBattleScript_LoadGfx0E,
    },
    {
        gBattleScript_NoSpawnThen24TerrainGrid,
        gBattleScript_StartEmpty,
        gBattleScript_End10_AdvancedMultiBurst,
        gBattleScript_LoadGfx1A,
        gBattleScript_LoadGfx03,
    },
    {
        gBattleScript_NoSpawnThen2FInitSetWithTexture53,
        gBattleScript_StartEmpty,
        gBattleScript_End43_SetWithMultiple,
        gBattleScript_LoadGfx29_03,
        gBattleScript_LoadGfxEmpty,
    },
    {
        gBattleScript_Start22RegisterSparkle,
        gBattleScript_StartEmpty,
        gBattleScript_End17_RegisterAll,
        gBattleScript_LoadGfx19_32,
        gBattleScript_LoadGfx03,
    },
    {
        gBattleScript_NoSpawnThen04TintDescriptor53ScalePulse,
        gBattleScript_StartEmpty,
        gBattleScript_End44_SetWithTimedFireball,
        gBattleScript_LoadGfxEmpty,
        gBattleScript_LoadGfx29_03,
    },
    {
        gBattleScript_NoSpawnThen78InitSmallGlowEffectSet,
        gBattleScript_StartEmpty,
        gBattleScript_End35_SetWithCustomCallback,
        gBattleScript_LoadGfxEmpty,
        gBattleScript_LoadGfx29_03,
    },
    {
        gBattleScript_NoSpawnThen1AEffect26DoubleTextureTrail,
        gBattleScript_StartEmpty,
        gBattleScript_End45_SetVariant2,
        gBattleScript_LoadGfxEmpty,
        gBattleScript_LoadGfx29_03,
    },
    {
        gBattleScript_NoSpawnThen27InitSetWithFade,
        gBattleScript_StartEmpty,
        gBattleScript_End46_SetWithComplex,
        gBattleScript_LoadGfx27,
        gBattleScript_LoadGfx29_03,
    },
    {
        gBattleScript_Start76CreateWithCallback,
        gBattleScript_StartEmpty,
        gBattleScript_End25_SpecialSetupBurstPalette3,
        gBattleScript_LoadGfx06,
        gBattleScript_LoadGfx18,
    },
    {
        gBattleScript_Start71TriggerDefaultPalette1B,
        gBattleScript_StartEmpty,
        gBattleScript_End4D_0E_TriggerDefault2AndInitializeGroup,
        gBattleScript_LoadGfx06,
        gBattleScript_LoadGfx18,
    },
    {
        gBattleScript_Start6CAdditionalSetupA,
        gBattleScript_StartEmpty,
        gBattleScript_End2E_CombinedSetupBurstHorizontalRandom,
        gBattleScript_LoadGfxEmpty,
        gBattleScript_LoadGfx18,
    },
    {
        gBattleScript_StartEmpty,
        gBattleScript_StartEmpty,
        gBattleScript_End24_ConfigTexture9Palette2,
        gBattleScript_LoadGfxEmpty,
        gBattleScript_LoadGfx18,
    },
    {
        gBattleScript_StartEmpty,
        gBattleScript_StartEmpty,
        gBattleScript_End2C_ConfigMotion6,
        gBattleScript_LoadGfxEmpty,
        gBattleScript_LoadGfx18,
    },
    {
        gBattleScript_Start19Nop,
        gBattleScript_StartEmpty,
        gBattleScript_End4F_2D_ColorVariantAndCombinedSetupBurst3DRandom,
        gBattleScript_LoadGfxEmpty,
        gBattleScript_LoadGfx18,
    },
    {
        gBattleScript_Start4BRegisterHandlersAlternate,
        gBattleScript_StartEmpty,
        gBattleScript_End32_RegisterHandlerWithParticleData,
        gBattleScript_LoadGfx12,
        gBattleScript_LoadGfxEmpty,
    },
    {
        gBattleScript_Start18PaletteScriptBurst,
        gBattleScript_StartEmpty,
        gBattleScript_End15_RegisterModeSpecific,
        gBattleScript_LoadGfx13,
        gBattleScript_LoadGfx26_11,
    },
    {
        gBattleScript_Start18PaletteScriptBurst,
        gBattleScript_StartEmpty,
        gBattleScript_End15_RegisterModeSpecific,
        gBattleScript_LoadGfx13,
        gBattleScript_LoadGfx26_11,
    },
    {
        gBattleScript_Start08ModelBurstAndVerticalFade,
        gBattleScript_StartEmpty,
        gBattleScript_End1F_RegisterMultiple,
        gBattleScript_LoadGfx05,
        gBattleScript_LoadGfxEmpty,
    },
    {
        gBattleScript_Start6DSimpleGroupSetup,
        gBattleScript_StartEmpty,
        gBattleScript_EndEmpty,
        gBattleScript_LoadGfxEmpty,
        gBattleScript_LoadGfxEmpty,
    },
    {
        gBattleScript_NoSpawnThen0BGlobalTintFade,
        gBattleScript_StartEmpty,
        gBattleScript_End04_MultiTextureSetup,
        gBattleScript_LoadGfx0A,
        gBattleScript_LoadGfx18,
    },
    {
        gBattleScript_NoSpawnThen46InitSetWithDifferentTiming,
        gBattleScript_Start69TriggerSpecial,
        gBattleScript_End47_SetVariant3,
        gBattleScript_LoadGfx15,
        gBattleScript_LoadGfx29_03,
    },
    {
        gBattleScript_Start41RegisterParticleNodes,
        gBattleScript_StartEmpty,
        gBattleScript_End12_ModeSpecificSetup,
        gBattleScript_LoadGfx25,
        gBattleScript_LoadGfx18,
    },
    {
        gBattleScript_Start41RegisterParticleNodes,
        gBattleScript_StartEmpty,
        gBattleScript_End12_ModeSpecificSetup,
        gBattleScript_LoadGfx25,
        gBattleScript_LoadGfx18,
    },
    {
        gBattleScript_Start41RegisterParticleNodes,
        gBattleScript_StartEmpty,
        gBattleScript_End12_ModeSpecificSetup,
        gBattleScript_LoadGfx25,
        gBattleScript_LoadGfx18,
    },
    {
        gBattleScript_NoSpawnThen39SmallNodeSetupB,
        gBattleScript_StartEmpty,
        gBattleScript_End1A_ComplexMovement,
        gBattleScript_LoadGfx0A,
        gBattleScript_LoadGfx18,
    },
    {
        gBattleScript_Start21Radial20,
        gBattleScript_StartEmpty,
        gBattleScript_End20_Radial20,
        gBattleScript_LoadGfxEmpty,
        gBattleScript_LoadGfxEmpty,
    },
    {
        gBattleScript_Start23Effect35SmokeTexture1,
        gBattleScript_StartEmpty,
        gBattleScript_End0F_ExplosionTintPalette35,
        gBattleScript_LoadGfx11,
        gBattleScript_LoadGfx18,
    },
    {
        gBattleScript_Start54Effect84SmokeLongDuration,
        gBattleScript_StartEmpty,
        gBattleScript_End1D_FireSet,
        gBattleScript_LoadGfx11_3D,
        gBattleScript_LoadGfx18,
    },
    {
        gBattleScript_Start3BCreateStreamSprayColumnEffect,
        gBattleScript_StartEmpty,
        gBattleScript_End08_SprayColumnEffect,
        gBattleScript_LoadGfx0F,
        gBattleScript_LoadGfxEmpty,
    },
    {
        gBattleScript_Start12ScatterRadialAndColumnSequence,
        gBattleScript_StartEmpty,
        gBattleScript_End08_SprayColumnEffect,
        gBattleScript_LoadGfx0F,
        gBattleScript_LoadGfxEmpty,
    },
    {
        gBattleScript_Start26RegisterExplosion,
        gBattleScript_StartEmpty,
        gBattleScript_End11_RegisterSmoke,
        gBattleScript_LoadGfx1C,
        gBattleScript_LoadGfxEmpty,
    },
    {
        gBattleScript_Start12ScatterRadialAndColumnSequence,
        gBattleScript_StartEmpty,
        gBattleScript_End48_SprayColumnEffectTrigger,
        gBattleScript_LoadGfx0F,
        gBattleScript_LoadGfxEmpty,
    },
    {
        gBattleScript_Start3FRegisterHandlersDefault,
        gBattleScript_StartEmpty,
        gBattleScript_End0A_RegisterAnimationCallbacks,
        gBattleScript_LoadGfxEmpty,
        gBattleScript_LoadGfx12,
    },
    {
        gBattleScript_Start25SimpleBurstScript,
        gBattleScript_StartEmpty,
        gBattleScript_End4B_MultiNodeAEntry,
        gBattleScript_LoadGfx1B_27,
        gBattleScript_LoadGfx18,
    },
    {
        gBattleScript_Start25SimpleBurstScript,
        gBattleScript_StartEmpty,
        gBattleScript_End3A_ModelAnimVerticalFade,
        gBattleScript_LoadGfx1B_27,
        gBattleScript_LoadGfx18,
    },
    {
        gBattleScript_Start34ModelAnim,
        gBattleScript_StartEmpty,
        gBattleScript_End4E_ModelAnimDelayedMotionAndFallingParticles,
        gBattleScript_LoadGfx28,
        gBattleScript_LoadGfx18,
    },
    {
        gBattleScript_Start11ModelAnimFinish,
        gBattleScript_StartEmpty,
        gBattleScript_End07_PaletteMultiBurst,
        gBattleScript_LoadGfx0E,
        gBattleScript_LoadGfxEmpty,
    },
    {
        gBattleScript_Start6BAlphaBurstPalette17,
        gBattleScript_StartEmpty,
        gBattleScript_End49_AlphaFireworkPalette17,
        gBattleScript_LoadGfx26_11,
        gBattleScript_LoadGfx18,
    },
    {
        gBattleScript_Start6AAlphaBurst,
        gBattleScript_StartEmpty,
        gBattleScript_End4A_AlphaFirework,
        gBattleScript_LoadGfx26_11,
        gBattleScript_LoadGfx18,
    },
    {
        gBattleScript_NoSpawnThen2ATrail40,
        gBattleScript_StartEmpty,
        gBattleScript_EndEmpty,
        gBattleScript_LoadGfx20,
        gBattleScript_LoadGfxEmpty,
    },
    {
        gBattleScript_Start60PaletteBurstVariant4Model8D,
        gBattleScript_StartEmpty,
        gBattleScript_EndEmpty,
        gBattleScript_LoadGfx37,
        gBattleScript_LoadGfxEmpty,
    },
    {
        gBattleScript_Start1BNop,
        gBattleScript_StartEmpty,
        gBattleScript_EndEmpty,
        gBattleScript_LoadGfxEmpty,
        gBattleScript_LoadGfxEmpty,
    },
    {
        gBattleScript_Start5APortraitBurst,
        gBattleScript_StartEmpty,
        gBattleScript_End2C_ConfigMotion6,
        gBattleScript_LoadGfx32,
        gBattleScript_LoadGfx18,
    },
    {
        gBattleScript_Start55FinalSetupA,
        gBattleScript_StartEmpty,
        gBattleScript_End2C_ConfigMotion6,
        gBattleScript_LoadGfx26_11,
        gBattleScript_LoadGfx18,
    },
    {
        gBattleScript_Start56RegisterLargeExplosionAndEffects,
        gBattleScript_StartEmpty,
        gBattleScript_EndEmpty,
        gBattleScript_LoadGfx1E,
        gBattleScript_LoadGfxEmpty,
    },
    {
        gBattleScript_Start61PaletteBurstVariant2Model8EDelayedFadeOut,
        gBattleScript_StartEmpty,
        gBattleScript_End3F_23_FireworkBurstAndConfigTexture7Palette1,
        gBattleScript_LoadGfx38,
        gBattleScript_LoadGfx18,
    },
    {
        gBattleScript_Start1DGroupSetupA,
        gBattleScript_StartEmpty,
        gBattleScript_EndEmpty,
        gBattleScript_LoadGfxEmpty,
        gBattleScript_LoadGfxEmpty,
    },
    {
        gBattleScript_NoSpawnThen2ATrail40,
        gBattleScript_StartEmpty,
        gBattleScript_EndEmpty,
        gBattleScript_LoadGfx20,
        gBattleScript_LoadGfxEmpty,
    },
    {
        gBattleScript_Start1BNop,
        gBattleScript_StartEmpty,
        gBattleScript_EndEmpty,
        gBattleScript_LoadGfxEmpty,
        gBattleScript_LoadGfxEmpty,
    },
    {
        gBattleScript_Start6EComplexGroupSetup,
        gBattleScript_StartEmpty,
        gBattleScript_EndEmpty,
        gBattleScript_LoadGfxEmpty,
        gBattleScript_LoadGfxEmpty,
    },
    {
        gBattleScript_Start1EFinalGroupSetup,
        gBattleScript_StartEmpty,
        gBattleScript_EndEmpty,
        gBattleScript_LoadGfxEmpty,
        gBattleScript_LoadGfxEmpty,
    },
    {
        gBattleScript_StartEmpty,
        gBattleScript_StartEmpty,
        gBattleScript_EndEmpty,
        gBattleScript_LoadGfxEmpty,
        gBattleScript_LoadGfxEmpty,
    },
    {
        gBattleScript_Start1CRegisterEffectE0,
        gBattleScript_StartEmpty,
        gBattleScript_EndEmpty,
        gBattleScript_LoadGfx14,
        gBattleScript_LoadGfx18,
    },
    {
        gBattleScript_Start5DWaterAnimFirework,
        gBattleScript_StartEmpty,
        gBattleScript_End3C_WaterAnimFireworkModel42RotationFollow,
        gBattleScript_LoadGfx10_Alt,
        gBattleScript_LoadGfx18,
    },
    {
        gBattleScript_Start5BPortraitBurstNode,
        gBattleScript_StartEmpty,
        gBattleScript_EndEmpty,
        gBattleScript_LoadGfx33,
        gBattleScript_LoadGfxEmpty,
    },
    {
        gBattleScript_Start57Effect87TintRampAnimVerticalFade,
        gBattleScript_StartEmpty,
        gBattleScript_EndEmpty,
        gBattleScript_LoadGfx31,
        gBattleScript_LoadGfx18,
    },
    {
        gBattleScript_Start0EModelAnimAndMoveKeyedTintParticles,
        gBattleScript_StartEmpty,
        gBattleScript_EndEmpty,
        gBattleScript_LoadGfx0C,
        gBattleScript_LoadGfxEmpty,
    },
    {
        gBattleScript_Start0EModelAnimAndMoveKeyedTintParticles,
        gBattleScript_StartEmpty,
        gBattleScript_EndEmpty,
        gBattleScript_LoadGfx0C,
        gBattleScript_LoadGfxEmpty,
    },
    {
        gBattleScript_Start1CRegisterEffectE0_36RibbonMesh,
        gBattleScript_StartEmpty,
        gBattleScript_EndEmpty,
        gBattleScript_LoadGfx14_Alt2,
        gBattleScript_LoadGfxEmpty,
    },
    {
        gBattleScript_Start0EModelAnimAndMoveKeyedTintParticles_Alt,
        gBattleScript_StartEmpty,
        gBattleScript_EndEmpty,
        gBattleScript_LoadGfx0C_Alt,
        gBattleScript_LoadGfxEmpty,
    },
    {
        gBattleScript_Start03ModelTintAndVerticalFade,
        gBattleScript_StartEmpty,
        gBattleScript_EndEmpty,
        gBattleScript_LoadGfx26_11,
        gBattleScript_LoadGfxEmpty,
    },
    {
        gBattleScript_Start55FinalSetupA,
        gBattleScript_StartEmpty,
        gBattleScript_End2C_ConfigMotion6,
        gBattleScript_LoadGfx26_11,
        gBattleScript_LoadGfx18,
    },
    {
        gBattleScript_Start20Nop,
        gBattleScript_StartEmpty,
        gBattleScript_End18_NoOp,
        gBattleScript_LoadGfxEmpty,
        gBattleScript_LoadGfxEmpty,
    },
    {
        gBattleScript_StartEmpty,
        gBattleScript_StartEmpty,
        gBattleScript_End18_NoOp,
        gBattleScript_LoadGfxEmpty,
        gBattleScript_LoadGfxEmpty,
    },
    {
        gBattleScript_Start32TintRampAndModelScaleFade,
        gBattleScript_StartEmpty,
        gBattleScript_End51_TintRampAndModelScaleFade,
        gBattleScript_LoadGfx27_32,
        gBattleScript_LoadGfx11,
    },
    {
        gBattleScript_Start40ModelAnimWait,
        gBattleScript_StartEmpty,
        gBattleScript_End28_SparkleSet,
        gBattleScript_LoadGfx07,
        gBattleScript_LoadGfx11,
    },
    {
        gBattleScript_Start5CPortraitBurstCheck,
        gBattleScript_StartEmpty,
        gBattleScript_End07_PaletteMultiBurst,
        gBattleScript_LoadGfx34,
        gBattleScript_LoadGfx0E,
    },
    {
        gBattleScript_Start4CRegisterEffectE0Alt,
        gBattleScript_StartEmpty,
        gBattleScript_End12_ModeSpecificSetup,
        gBattleScript_LoadGfx14,
        gBattleScript_LoadGfx18,
    },
    {
        gBattleScript_Start11ModelAnimFinish,
        gBattleScript_StartEmpty,
        gBattleScript_End07_PaletteMultiBurst,
        gBattleScript_LoadGfx0E,
        gBattleScript_LoadGfxEmpty,
    },
    {
        gBattleScript_Start4FModelAnimWaitAndDescriptor25AlphaFade,
        gBattleScript_StartEmpty,
        gBattleScript_End0E_InitializeGroup,
        gBattleScript_LoadGfx2F,
        gBattleScript_LoadGfx18,
    },
    {
        gBattleScript_Start17Effect23SmokeWithMarker,
        gBattleScript_StartEmpty,
        gBattleScript_End3B_InitCombinedSet,
        gBattleScript_LoadGfx11,
        gBattleScript_LoadGfx18,
    },
    {
        gBattleScript_Start63BasicMultiBurst,
        gBattleScript_StartEmpty,
        gBattleScript_End40_FireballBurst,
        gBattleScript_LoadGfx39,
        gBattleScript_LoadGfx03,
    },
    {
        gBattleScript_Start47SpecialModelColorCycle,
        gBattleScript_StartEmpty,
        gBattleScript_End29_Descriptor34Burst,
        gBattleScript_LoadGfx08,
        gBattleScript_LoadGfx18,
    },
    {
        gBattleScript_NoSpawnThen07TexturedRibbonSheet,
        gBattleScript_StartEmpty,
        gBattleScript_End34_MultiHandleSetup,
        gBattleScript_LoadGfx04,
        gBattleScript_LoadGfx18,
    },
    {
        gBattleScript_Start70PortraitBurstInit,
        gBattleScript_StartEmpty,
        gBattleScript_End50_4C_ConfigMotion16AndTriggerAnother,
        gBattleScript_LoadGfx32,
        gBattleScript_LoadGfx18,
    },
    {
        gBattleScript_Start3EOwnerLinkedFourStream,
        gBattleScript_StartEmpty,
        gBattleScript_End25_SpecialSetupBurstPalette3,
        gBattleScript_LoadGfx06,
        gBattleScript_LoadGfx18,
    },
    {
        gBattleScript_Start13Radial20,
        gBattleScript_StartEmpty,
        gBattleScript_End09_Radial20_Alt,
        gBattleScript_LoadGfxEmpty,
        gBattleScript_LoadGfxEmpty,
    },
    {
        gBattleScript_Start0CDelayedModelAnim,
        gBattleScript_StartEmpty,
        gBattleScript_EndEmpty,
        gBattleScript_LoadGfxEmpty,
        gBattleScript_LoadGfxEmpty,
    },
    {
        gBattleScript_Start37ModelAnimWaitMarkerSlotAndScaleFall,
        gBattleScript_Start2CTrail40GridAlt,
        gBattleScript_EndEmpty,
        gBattleScript_LoadGfx2A,
        gBattleScript_AnimMiss,
    },
    {
        gBattleScript_Start42RegisterMultipleHandlers,
        gBattleScript_StartEmpty,
        gBattleScript_EndEmpty,
        gBattleScript_LoadGfx07,
        gBattleScript_LoadGfxEmpty,
    },
    {
        gBattleScript_Start5APortraitBurst,
        gBattleScript_StartEmpty,
        gBattleScript_End2C_ConfigMotion6,
        gBattleScript_LoadGfx32,
        gBattleScript_LoadGfx18,
    },
    {
        gBattleScript_Start53SimpleBurst,
        gBattleScript_StartEmpty,
        gBattleScript_EndEmpty,
        gBattleScript_LoadGfx30,
        gBattleScript_LoadGfxEmpty,
    },
    {
        gBattleScript_Start5FPaletteMultiBurstCleanupWithTintFade,
        gBattleScript_StartEmpty,
        gBattleScript_End3E_PaletteMultiBurstNoCleanupNoTintFade,
        gBattleScript_LoadGfx36,
        gBattleScript_LoadGfxEmpty,
    },
    {
        gBattleScript_Start1CRegisterEffectE0,
        gBattleScript_StartEmpty,
        gBattleScript_End12_ModeSpecificSetup,
        gBattleScript_LoadGfx14,
        gBattleScript_LoadGfx18,
    },
    {
        gBattleScript_Start65RotationEntry,
        gBattleScript_StartEmpty,
        gBattleScript_End41_FireworkEntry,
        gBattleScript_LoadGfx3B_2C,
        gBattleScript_LoadGfx18,
    },
    {
        gBattleScript_Start18PaletteScriptBurst,
        gBattleScript_StartEmpty,
        gBattleScript_End15_RegisterModeSpecific,
        gBattleScript_LoadGfx13,
        gBattleScript_LoadGfx26_11,
    },
    {
        gBattleScript_Start5ESimpleBurstAnimWaitDelayedTintFade,
        gBattleScript_StartEmpty,
        gBattleScript_End3D_SimpleBurstTintPulseAnimWaitPaletteC,
        gBattleScript_LoadGfx35,
        gBattleScript_LoadGfxEmpty,
    },
    {
        gBattleScript_Start67InitSmoke,
        gBattleScript_Start68InitFire,
        gBattleScript_End19_PlaySoundAndReset,
        gBattleScript_LoadGfx2B_11,
        gBattleScript_LoadGfx29_03,
    },
    {
        gBattleScript_Start59MultiNodeD_Alt,
        gBattleScript_StartEmpty,
        gBattleScript_EndEmpty,
        gBattleScript_LoadGfxEmpty,
        gBattleScript_LoadGfxEmpty,
    },
    {
        gBattleScript_Start30TimedFireball,
        gBattleScript_StartEmpty,
        gBattleScript_End22_InitParticleGroupBasic,
        gBattleScript_LoadGfx03,
        gBattleScript_LoadGfx18,
    },
    {
        gBattleScript_StartEmpty,
        gBattleScript_StartEmpty,
        gBattleScript_End06_0E_RegisterPaletteVariantsAndInitializeGroup,
        gBattleScript_LoadGfxEmpty,
        gBattleScript_LoadGfx18_0D,
    },
    {
        gBattleScript_Start41RegisterParticleNodes,
        gBattleScript_StartEmpty,
        gBattleScript_End12_ModeSpecificSetup,
        gBattleScript_LoadGfx25,
        gBattleScript_LoadGfx18,
    },
    {
        gBattleScript_Start10TintDescriptor34Sequence,
        gBattleScript_StartEmpty,
        gBattleScript_End39_FullSetupTintFadeOutAndRestore,
        gBattleScript_LoadGfxEmpty,
        gBattleScript_LoadGfx18,
    },
    {
        gBattleScript_Start31SimpleNodeEntry,
        gBattleScript_StartEmpty,
        gBattleScript_End42_SimpleNodeBurst,
        gBattleScript_LoadGfx26_11,
        gBattleScript_LoadGfx18,
    },
    {
        gBattleScript_StartEmpty,
        gBattleScript_StartEmpty,
        gBattleScript_EndEmpty,
        gBattleScript_LoadGfxEmpty,
        gBattleScript_LoadGfxEmpty,
    },
    {
        gBattleScript_Start51AdvancedModeSetup,
        gBattleScript_StartEmpty,
        gBattleScript_EndEmpty,
        gBattleScript_LoadGfx0E,
        gBattleScript_LoadGfx18,
    },
    {
        gBattleScript_Start64SimpleBurstAnimWaitDelayedAlphaFadeOut,
        gBattleScript_StartEmpty,
        gBattleScript_End2D_1E_CombinedSetupBurst3DRandomAndHandleCollisionSetup,
        gBattleScript_LoadGfx3A_0B,
        gBattleScript_LoadGfx18,
    },
    {
        gBattleScript_Start52TintRampAndModelScaleFade,
        gBattleScript_StartEmpty,
        gBattleScript_End52_TintRampAndModelScaleFade,
        gBattleScript_LoadGfx27_32,
        gBattleScript_LoadGfx11,
    },
    {
        gBattleScript_Start7CCollisionResponseSwitch,
        gBattleScript_Start7BConditionalStateSetup,
        gBattleScript_End58_CollisionAndBurstSetup,
        gBattleScript_LoadGfx0B,
        gBattleScript_LoadGfxEmpty,
    },
    {
        gBattleScript_Start50RegisterDefaultTexture,
        gBattleScript_StartEmpty,
        gBattleScript_End2C_ConfigMotion6,
        gBattleScript_LoadGfx2F,
        gBattleScript_LoadGfx18,
    },
    {
        gBattleScript_StartEmpty,
        gBattleScript_StartEmpty,
        gBattleScript_EndEmpty,
        gBattleScript_LoadGfxEmpty,
        gBattleScript_LoadGfxEmpty,
    },
    {
        gBattleScript_Start3FRegisterHandlersDefault,
        gBattleScript_StartEmpty,
        gBattleScript_End0A_RegisterAnimationCallbacks,
        gBattleScript_LoadGfxEmpty,
        gBattleScript_LoadGfx12,
    },
    {
        gBattleScript_Start4ASpecialModelColorCycle,
        gBattleScript_StartEmpty,
        gBattleScript_End29_Descriptor34Burst,
        gBattleScript_LoadGfx08,
        gBattleScript_LoadGfx18,
    },
    {
        gBattleScript_Start58MultiNodeEffect88Palette7,
        gBattleScript_StartEmpty,
        gBattleScript_EndEmpty,
        gBattleScript_LoadGfx31,
        gBattleScript_LoadGfx18,
    },
    {
        gBattleScript_Start1DGroupSetupA,
        gBattleScript_StartEmpty,
        gBattleScript_EndEmpty,
        gBattleScript_LoadGfxEmpty,
        gBattleScript_LoadGfxEmpty,
    },
    {
        gBattleScript_NoSpawnThen4EInitSetSingle,
        gBattleScript_StartEmpty,
        gBattleScript_End56_ThreeInstanceSet,
        gBattleScript_LoadGfx03_Alt,
        gBattleScript_LoadGfx18,
    },
    {
        gBattleScript_Start4ASpecialModelColorCycle,
        gBattleScript_StartEmpty,
        gBattleScript_End29_Descriptor34Burst,
        gBattleScript_LoadGfx08,
        gBattleScript_LoadGfx18,
    },
    {
        gBattleScript_Start0DSecondaryOwnerSpeciesBranch,
        gBattleScript_StartEmpty,
        gBattleScript_End05_DynamicCollisionSetup,
        gBattleScript_LoadGfx0B,
        gBattleScript_LoadGfxEmpty,
    },
    {
        gBattleScript_Start59MultiNodeD,
        gBattleScript_StartEmpty,
        gBattleScript_EndEmpty,
        gBattleScript_LoadGfxEmpty,
        gBattleScript_LoadGfxEmpty,
    },
    {
        gBattleScript_Start72FinalSetupB,
        gBattleScript_StartEmpty,
        gBattleScript_End2C_ConfigMotion6,
        gBattleScript_LoadGfxEmpty,
        gBattleScript_LoadGfx18,
    },
};

void BattleAnim_PlaySoundEffect1(void) {
    Audio_PlaySoundEffectById(1);
}

void BattleAnim_PlaySoundEffect2(void) {
    Audio_PlaySoundEffectById(2);
}

void BattleAnim_PlaySoundEffect3(void) {
    Audio_PlaySoundEffectById(3);
}

void BattleAnim_PlaySoundEffect8(void) {
    Audio_PlaySoundEffectById(8);
}

void BattleAnim_PlayOwnerCry(BattlePlayerEntity* arg0, s16 arg1) {
    if (BattleScene_IsPartnerPikachu(arg0) != 0) {
        Cry_Play(0xC8, 2);
    } else {
        Cry_Play(arg1, 2);
    }
}

void BattleAnim_PlaySpeciesSequence33(BattlePlayerEntity* arg0) {
    s16 sp1E = arg0->unk_000.unk_01A;

    BattleScene_GetParticipantModelWidth(arg0);
    Audio_PlayCommand(0x33, sp1E, 0);
}

void Battle_TriggerTrainerPresentationCue(BattlePlayerEntity* arg0) {
    Audio_ProcessBattleInfo(BattleScene_GetParticipantDisplayPlayerNumber(arg0), &arg0->animationState.unk_38);
}

void BattleAnim_PlaySpeciesReactionSound(BattlePlayerEntity* arg0, PokemonAudioInfo* arg1, s32 arg2) {
    Effect_TriggerMoveVisual(arg1->currentMoveId, arg0->unk_000.unk_01A, arg2);
    Audio_HandleMoveEvent(arg1, arg1->currentMoveId, arg0->unk_000.unk_01A, arg2);
}

void BattleScene_ConfigureAudioChannelGroupsByTeam(void) {
    BattlePlayerEntity* ptr1 = sActivePokemon[0];
    BattlePlayerEntity* ptr2 = sActivePokemon[1];
    u8 i;
    u8 sp20[4];

    sp20[0] = 0xA;
    sp20[1] = 0xA;
    sp20[2] = 0xA;
    sp20[3] = 0xA;

    sp20[ptr1->pokemonAnimation->RentalSlotAnimData_PosePhase[0]->unk_001] = 1;
    if (ptr1->pokemonAnimation->TrainerSlotSaveData_GamePort == 2) {
        sp20[ptr1->pokemonAnimation->RentalSlotAnimData_PosePhase[1]->unk_001] = 1;
    }
    sp20[ptr2->pokemonAnimation->RentalSlotAnimData_PosePhase[0]->unk_001] = 2;
    if (ptr2->pokemonAnimation->TrainerSlotSaveData_GamePort == 2) {
        sp20[ptr2->pokemonAnimation->RentalSlotAnimData_PosePhase[1]->unk_001] = 2;
    }

    for (i = 0; i < 4; i++) {
        if (sp20[i] == 0xA) {
            sp20[i] = 0;
        }
    }

    Audio_ConfigureChannelGroups(sp20[0], sp20[1], sp20[2], sp20[3]);
}

void BattleScene_ConfigureAudioChannelGroupCounts(void) {
    BattlePlayerEntity* ptr1 = sActivePokemon[0];
    BattlePlayerEntity* ptr2 = sActivePokemon[1];
    u8 sp24[4];

    sp24[0] = 0;
    sp24[1] = 0;
    sp24[2] = 0;
    sp24[3] = 0;

    sp24[ptr1->pokemonAnimation->RentalSlotAnimData_PosePhase[0]->unk_001] = BattleScene_GetRosterTeamSize(ptr1->pokemonAnimation->RentalSlotAnimData_PosePhase[0]);
    if (ptr1->pokemonAnimation->TrainerSlotSaveData_GamePort == 2) {
        sp24[ptr1->pokemonAnimation->RentalSlotAnimData_PosePhase[1]->unk_001] = BattleScene_GetRosterTeamSize(ptr1->pokemonAnimation->RentalSlotAnimData_PosePhase[1]);
    }

    sp24[ptr2->pokemonAnimation->RentalSlotAnimData_PosePhase[0]->unk_001] = BattleScene_GetRosterTeamSize(ptr2->pokemonAnimation->RentalSlotAnimData_PosePhase[0]);
    if (ptr2->pokemonAnimation->TrainerSlotSaveData_GamePort == 2) {
        sp24[ptr2->pokemonAnimation->RentalSlotAnimData_PosePhase[1]->unk_001] = BattleScene_GetRosterTeamSize(ptr2->pokemonAnimation->RentalSlotAnimData_PosePhase[1]);
    }
    Audio_SetChannelGroupCounts(sp24[0], sp24[1], sp24[2], sp24[3]);
}

void BattleScene_SelectBattleMusic(void) {
    switch (gSessionContext.unk_0000) {
        case 0:
            switch (gSessionContext.unk_0001) {
                case 0:
                    Audio_SelectModeMusic(0, 0xE);
                    break;

                case 1:
                    Audio_SelectModeMusic(0, 0xA);
                    break;

                case 2:
                    Audio_SelectModeMusic(0, 0xB);
                    break;

                case 3:
                    Audio_SelectModeMusic(0, 6);
                    break;

                case 4:
                    Audio_SelectModeMusic(0, 5);
                    break;

                case 5:
                    Audio_SelectModeMusic(0, 4);
                    break;

                case 6:
                    Audio_SelectModeMusic(0, 0);
                    break;

                case 7:
                    Audio_SelectModeMusic(0, 0xC);
                    break;

                case 8:
                    Audio_SelectModeMusic(0, 0xC);
                    break;
            }
            break;

        case 1:
            Audio_SelectModeMusic(gSessionContext.unk_0003, 0xA);
            break;

        case 2:
            Audio_SelectModeMusic(gSessionContext.unk_0003, 0xB);
            break;

        case 3:
            switch (gSessionContext.unk_0002) {
                case 0:
                    Audio_SelectModeMusic(gSessionContext.unk_0003, 6);
                    break;

                case 1:
                    Audio_SelectModeMusic(gSessionContext.unk_0003, 7);
                    break;

                case 2:
                    Audio_SelectModeMusic(gSessionContext.unk_0003, 8);
                    break;

                case 3:
                    Audio_SelectModeMusic(gSessionContext.unk_0003, 9);
                    break;
            }
            break;

        case 4:
            Audio_SelectModeMusic(gSessionContext.unk_0003, 5);
            break;

        case 5:
            Audio_SelectModeMusic(gSessionContext.unk_0003, 4);
            break;

        case 6:
            switch (gSessionContext.unk_0002) {
                case 0:
                    Audio_SelectModeMusic(gSessionContext.unk_0003, 0);
                    break;

                case 1:
                    Audio_SelectModeMusic(gSessionContext.unk_0003, 1);
                    break;

                case 2:
                    Audio_SelectModeMusic(gSessionContext.unk_0003, 2);
                    break;

                case 3:
                    Audio_SelectModeMusic(gSessionContext.unk_0003, 3);
                    break;
            }
            break;

        case 7:
            if (gSessionContext.unk_0002 == 9) {
                Audio_SelectModeMusic(5, 0xD);
            } else if (gSessionContext.unk_0002 == 8) {
                Audio_SelectModeMusic(gSessionContext.unk_0003, 0xD);
            } else {
                Audio_SelectModeMusic((gSessionContext.unk_0002 * 4) + gSessionContext.unk_0003, 0xC);
            }
            break;

        case 8:
            Audio_SelectModeMusic(gSessionContext.unk_0003, 0xF);
            break;

        case 10:
            switch (gSessionContext.unk_0001) {
                case 0:
                    Audio_SelectModeMusic(0xFF, 0xE);
                    break;

                case 1:
                    Audio_SelectModeMusic(0xFF, 0xA);
                    break;

                case 2:
                    Audio_SelectModeMusic(0xFF, 0xB);
                    break;

                case 3:
                    Audio_SelectModeMusic(0xFF, 6);
                    break;

                case 4:
                    Audio_SelectModeMusic(0xFF, 5);
                    break;

                case 5:
                    Audio_SelectModeMusic(0xFF, 4);
                    break;

                case 6:
                    Audio_SelectModeMusic(0xFF, 0);
                    break;

                case 7:
                    Audio_SelectModeMusic(0xFF, 0xC);
                    break;

                case 8:
                    Audio_SelectModeMusic(0xFF, 0xC);
                    break;
            }
            break;

        case 9:
            Audio_SelectModeMusic(0, 0x10);
            break;
    }
}

void BattleScene_StartBattleMusic(void) {
    switch (gSessionContext.unk_0000) {
        case 16:
            Audio_StartMusicTrack(1);
            break;

        case 0:
            switch (gSessionContext.unk_0001) {
                case 0:
                    Audio_StartTrackForCategory(0, 0xE);
                    break;

                case 1:
                    Audio_StartTrackForCategory(0, 0xA);
                    break;

                case 2:
                    Audio_StartTrackForCategory(0, 0xB);
                    break;

                case 3:
                    Audio_StartTrackForCategory(0, 6);
                    break;

                case 4:
                    Audio_StartTrackForCategory(0, 5);
                    break;

                case 5:
                    Audio_StartTrackForCategory(0, 4);
                    break;

                case 6:
                    Audio_StartTrackForCategory(0, 0);
                    break;

                case 7:
                    Audio_StartTrackForCategory(0, 0xC);
                    break;

                case 8:
                    Audio_StartTrackForCategory(0, 0xC);
                    break;
            }
            break;

        case 1:
            Audio_StartTrackForCategory(gSessionContext.unk_0003, 0xA);
            break;

        case 2:
            Audio_StartTrackForCategory(gSessionContext.unk_0003, 0xB);
            break;

        case 3:
            switch (gSessionContext.unk_0002) {
                case 0:
                    Audio_StartTrackForCategory(gSessionContext.unk_0003, 6);
                    break;

                case 1:
                    Audio_StartTrackForCategory(gSessionContext.unk_0003, 7);
                    break;

                case 2:
                    Audio_StartTrackForCategory(gSessionContext.unk_0003, 8);
                    break;

                case 3:
                    Audio_StartTrackForCategory(gSessionContext.unk_0003, 9);
                    break;
            }
            break;

        case 4:
            Audio_StartTrackForCategory(gSessionContext.unk_0003, 5);
            break;

        case 5:
            Audio_StartTrackForCategory(gSessionContext.unk_0003, 4);
            break;

        case 6:
            switch (gSessionContext.unk_0002) {
                case 0:
                    Audio_StartTrackForCategory(gSessionContext.unk_0003, 0);
                    break;

                case 1:
                    Audio_StartTrackForCategory(gSessionContext.unk_0003, 1);
                    break;

                case 2:
                    Audio_StartTrackForCategory(gSessionContext.unk_0003, 2);
                    break;

                case 3:
                    Audio_StartTrackForCategory(gSessionContext.unk_0003, 3);
                    break;
            }
            break;

        case 7:
            if (gSessionContext.unk_0002 == 9) {
                Audio_StartTrackForCategory(5, 0xD);
            } else if (gSessionContext.unk_0002 == 8) {
                Audio_StartTrackForCategory(gSessionContext.unk_0003, 0xD);
            } else {
                Audio_StartTrackForCategory((gSessionContext.unk_0002 * 4) + gSessionContext.unk_0003, 0xC);
            }
            break;

        case 8:
            Audio_StartTrackForCategory(gSessionContext.unk_0003, 0xF);
            break;

        case 10:
            switch (gSessionContext.unk_0001) {
                case 0:
                    Audio_StartTrackForCategory(0xFF, 0xE);
                    break;

                case 1:
                    Audio_StartTrackForCategory(0xFF, 0xA);
                    break;

                case 2:
                    Audio_StartTrackForCategory(0xFF, 0xB);
                    break;

                case 3:
                    Audio_StartTrackForCategory(0xFF, 6);
                    break;

                case 4:
                    Audio_StartTrackForCategory(0xFF, 5);
                    break;

                case 5:
                    Audio_StartTrackForCategory(0xFF, 4);
                    break;

                case 6:
                    Audio_StartTrackForCategory(0xFF, 0);
                    break;

                case 7:
                    Audio_StartTrackForCategory(0xFF, 0xC);
                    break;

                case 8:
                    Audio_StartTrackForCategory(0xFF, 0xC);
                    break;
            }
            break;

        case 9:
            Audio_StartTrackForCategory(0, 0x10);
            break;
    }
}

void BattleAnim_PlayBattleSequenceById(BattlePlayerEntity* arg0, s32 arg1) {
    s16 sp1E = arg0->unk_000.unk_01A;

    if ((BattleScene_IsPartnerPikachu(arg0) != 0) && (arg1 == 0x32)) {
        Audio_PlayCommand(0x32, 0xC8, 0);
    } else if (arg1 == 0x14) {
        Audio_PlayCommand(0x14, 0, 0);
    } else if (arg1 == 0x12) {
        Audio_PlayCommand(0x12, 0, 0);
    } else if (arg1 == 0x32) {
        Audio_PlayCommand(0x32, sp1E, 0);
    } else if (arg1 == 0x21) {
        Audio_PlayCommand(0x21, 0, 0);
    } else if (arg1 == 0x13) {
        Audio_PlayCommand(0x13, 0, 0);
    } else if (arg1 == 0x1E) {
        Audio_PlayCommand(0x1E, 0, 0);
    } else if (arg1 == 0x1F) {
        Audio_PlayCommand(0x1F, 0, 0);
    } else if (arg1 == 0x20) {
        Audio_PlayCommand(0x20, 0, 0);
    }
}

void BattleAnim_RunEffectInitStart(s16 arg0) {
    gParticleEffectParam = gParticleEffectPrimaryId;
    gStateFunctionTable[arg0]();
    if (gParticleEffectSecondaryId != 0xFF) {
        gParticleEffectParam = gParticleEffectSecondaryId;
        gStateFunctionTable[arg0]();
    }
}

void BattleAnim_RunEffectInitEnd(s16 arg0) {
    gParticleEffectParam = gParticleEffectPrimaryId;
    gParticleStateFunctionTable[arg0]();
}

void BattleAnim_RegisterEffectSlot(func_D_84390300 arg0, func_D_84390320 arg1) {
    if (gStateCallbackSlot >= 8) {
        gStateCallbackSlot = 0;
    }

    if (gCameraCallbackFuncs[gStateCallbackSlot]) {}

    gCameraCallbackFuncs[gStateCallbackSlot] = arg0;
    gCameraUpdateFuncs[gStateCallbackSlot] = arg1;
    gStateCallbackSlot++;
}

void BattleAnim_RunEffectList(s32 arg0, s32 arg1, s32 arg2) {
    u8* sp2C;

    gCurrentEffectListSource = arg1;

    if (arg2 == 1) {
        switch (arg1) {
            case 0:
                sp2C = Fragment62_ComplexPtrTable[arg0][0];
                break;

            case 1:
                sp2C = Fragment62_ComplexPtrTable[arg0][1];
                break;

            case 3:
                sp2C = Fragment62_SubTablePtr2D[arg0][0];
                break;

            case 4:
                sp2C = Fragment62_DataPtrArray[arg0];
                break;

            case 9:
                sp2C = Fragment62_SpecialPairPtr[arg0];
                break;
        }

        while (*sp2C != 0) {
            BattleAnim_RunEffectInitStart(*sp2C);
            gStateCallbackTable[*sp2C]();
            BattleAnim_RegisterEffectSlot(gStateUpdateCallbackTable[*sp2C], gStateDrawCallbackTable[*sp2C]);
            sp2C++;
        }
    } else {
        switch (arg1) {
            case 2:
                sp2C = Fragment62_ComplexPtrTable[arg0][2];
                break;

            case 6:
                sp2C = Fragment62_GroupPtrArray[arg0];
                break;
        }

        while (*sp2C != 0) {
            BattleAnim_RunEffectInitEnd(*sp2C);
            gParticleCallbackTable[*sp2C]();
            BattleAnim_RegisterEffectSlot(gParticleUpdateCallbackTable[*sp2C], gParticleDrawCallbackTable[*sp2C]);
            sp2C++;
        }
    }
}

void BattleAnim_ProcessQueuedEffects(void) {
    if (gPendingActionScriptFlag0 != 0) {
        BattleAnim_ResetSpawnDelayAlias();
        BattleAnim_RunEffectList(gCurrentActionScriptId, gCurrentActionScriptSubIndex, gPendingActionScriptFlag0);
        gPendingActionScriptFlag0 = 0;
    }

    if (gPendingActionScriptFlag1 != 0) {
        BattleAnim_RunEffectList(gCurrentActionScriptAltId, gCurrentActionScriptSubId, gPendingActionScriptFlag1);
        gPendingActionScriptFlag1 = 0;
    }

    if (gPendingActionScriptFlag2 != 0) {
        BattleAnim_RunEffectList(gWaterEffectParam, gWaterEffectTimerMax, gPendingActionScriptFlag2);
        gPendingActionScriptFlag2 = 0;
    }

    if (gPendingActionScriptFlag3 != 0) {
        BattleAnim_RunEffectList(gCurrentActionScriptMode, 4, gPendingActionScriptFlag3);
        gPendingActionScriptFlag3 = 0;
    }
}

void BattleAnim_UpdateFrame(UNUSED CameraStruct* arg0) {
    Particle_UpdateFrameCounters();
    BattleAnim_ProcessQueuedEffects();
    BattleAnim_UpdateEffects();
    BattleAnim_NoopUpdateHook();
}

void BattleAnim_SetQueuedEffectList(u8 arg0) {
    gCurrentActionScriptSubIndex = arg0;
}

u8 BattleAnim_GetCurrentEffectList(void) {
    return gCurrentEffectListSource;
}

void BattleAnim_SetQueuedResourceListId(u8 arg0) {
    gCurrentActionScriptMode = arg0;
}

u8 BattleAnim_GetQueuedResourceListId(void) {
    return gCurrentActionScriptMode;
}

s16 BattleAnim_GetQueuedMoveId(void) {
    return gCurrentActionScriptId;
}

void BattleAnim_QueueMoveEffect(s32 arg0, BattlePlayerEntity* arg1, BattlePlayerEntity* arg2, s16 arg3, s16 arg4) {
    BattleAnim_SetQueuedEffectList(0);
    gPendingActionScriptFlag0 = 1;
    gCurrentActionScriptId = arg0;
    gPanelDrawCount = 0;
    gParticleEffectPrimaryId = arg3;
    gParticleEffectSecondaryId = arg4;
    gParticleEffectAttackerEntity = arg1;
    gParticleEffectUserEntity = arg1;
    gParticleEffectTargetEntity = arg2;
}

void BattleAnim_QueueMoveEffectScriptA(s32 arg0, BattlePlayerEntity* arg1, BattlePlayerEntity* arg2, s16 arg3, s16 arg4) {
    BattleAnim_QueueMoveEffect(arg0, arg1, arg2, arg3, arg4);
}

void BattleAnim_QueueMoveEffectEnd(s32 arg0, BattlePlayerEntity* arg1, BattlePlayerEntity* arg2, s16 arg3, s16 arg4) {
    BattleAnim_QueueMoveEffect(arg0, arg1, arg2, arg3, arg4);
    BattleAnim_SetQueuedEffectList(2);
    gParticleEffectAttackerEntity = arg2;
    gPendingActionScriptFlag0 = 2;
}

void BattleAnim_QueueMoveEffectScriptB(s32 arg0, BattlePlayerEntity* arg1, BattlePlayerEntity* arg2, s16 arg3, s16 arg4) {
    BattleAnim_QueueMoveEffect(arg0, arg1, arg2, arg3, arg4);
    BattleAnim_SetQueuedEffectList(1);
}

void BattleAnim_QueueEffectList3(s32 arg0, BattlePlayerEntity* arg1, BattlePlayerEntity* arg2, s16 arg3, s16 arg4) {
    BattleAnim_QueueMoveEffect(arg0, arg1, arg2, arg3, arg4);
    BattleAnim_SetQueuedEffectList(3);
}

void BattleAnim_QueueEffectList6(s32 arg0, BattlePlayerEntity* arg1) {
    gPendingActionScriptFlag1 = 2;
    gCurrentActionScriptAltId = arg0;
    gCurrentActionScriptSubId = 6;
    gParticleEffectPrimaryId = 0xFF;
    gParticleEffectSecondaryId = 0xFF;
    gParticleEffectAttackerEntity = arg1;
    gParticleEffectUserEntity = arg1;
    gParticleEffectTargetEntity = arg1;
}

void BattleAnim_QueueEffectList5(s32 arg0, BattlePlayerEntity* arg1) {
    BattleAnim_QueueEffectList6(arg0, arg1);
    gPendingActionScriptFlag1 = 1;
    gCurrentActionScriptSubId = 5;
}

void BattleAnim_QueueEffectList6Alt(s32 arg0, BattlePlayerEntity* arg1) {
    BattleAnim_QueueEffectList6(arg0, arg1);
}

void BattleAnim_QueueEffectList9(s32 arg0) {
    gPendingActionScriptFlag2 = 1;
    gWaterEffectTimerMax = 9;
    gWaterEffectParam = arg0;
    gParticleEffectPrimaryId = 0xFF;
    gParticleEffectSecondaryId = 0xFF;
}

void BattleAnim_QueueEffectList(u8 arg0, BattlePlayerEntity* arg1) {
    gPendingActionScriptFlag3 = 1;
    BattleAnim_SetQueuedResourceListId(arg0);
    gParticleEffectAttackerEntity = arg1;
    gParticleEffectPrimaryId = 0xFF;
    gParticleEffectSecondaryId = 0xFF;
    if (arg0 == 3) {
        gParticleEffectPrimaryId = 7;
    }
}

void BattleAnim_StopOwnerCategoryParticles(u8 arg0, BattlePlayerEntity* arg1) {
    BattleAnim_StopParticlesForOwnerCategory(arg0, arg1);
}

void BattleAnim_RegisterAssetTable(arg1_func_80019420* arg0) {
    if (arg0 != NULL) {
        do {
            if (arg0->posY != 0) {
                gBattleAnimAssetPointers[arg0->posY] = arg0->rotation;
                arg0++;
            }
        } while (arg0->posX != 0);
    }
}

void BattleAnim_ResetAssetTable(void) {
    s32 i;

    // clang-format off
    for (i = 0; i < 256; i++) { gBattleAnimAssetPointers[i] = NULL; }
    // clang-format on

    BattleAnim_RegisterAssetTable(BattleAnim_LoadResourceTable(0));
}

void BattleAnim_BuildResourceListForMove(s16 arg0) {
    s32 var_v0 = 0;
    u8* temp_a1 = Fragment62_ComplexPtrTable[arg0][3];

    while (*temp_a1 != 0x3F) {
        gBattleAnimResourceListBuffer[var_v0] = *temp_a1;
        temp_a1++;
        var_v0++;
    }

    temp_a1 = Fragment62_ComplexPtrTable[arg0][4];
    while (*temp_a1 != 0x3F) {
        gBattleAnimResourceListBuffer[var_v0] = *temp_a1;
        temp_a1++;
        var_v0++;
    }

    gBattleAnimResourceListBuffer[var_v0] = -1;
}

void BattleAnim_LoadMoveResourceList(BattlePokemon* arg0, s16 arg1) {
    if (arg1 != 0xFF) {
        BattleAnim_BuildResourceListForMove(arg1);
        arg0->unk_1D |= 0x80;
        arg0->unk_20 = gBattleAnimResourceListBuffer;
        arg0->unk_24 = gBattleAnimAssetTables;
    }
}

void BattleAnim_LoadModeResourceList(BattlePokemon* arg0, s16 arg1) {
    s32 var_v0 = 0;
    u8* var_v1 = Fragment62_SubTablePtr2D[arg1][1];

    while (*var_v1 != 0x3F) {
        gBattleAnimResourceListBuffer[var_v0] = *var_v1;
        var_v1++;
        var_v0++;
    }

    gBattleAnimResourceListBuffer[var_v0] = -1;
    arg0->unk_20 = gBattleAnimResourceListBuffer;
    arg0->unk_1D |= 0x80;
    arg0->unk_24 = gBattleAnimAssetTables;
}

void BattleAnim_RegisterAllAssetTables(void) {
    s32 i = 0;
    arg1_func_80019420* var_v0;
    arg1_func_80019420** var_s1 = gBattleAnimAssetTables;

    while (*var_s1 != NULL) {
        var_v0 = *var_s1;
        if (i) {}
        BattleAnim_RegisterAssetTable(var_v0);
        var_s1++;
        i++;
    }
}

void BattleAnim_RegisterAssetTablesForSession(BattlePokemon* arg0) {
    arg0->unk_1D &= ~0x10;
    BattleAnim_RegisterAllAssetTables();
}

void BattleAnim_ResetDisplayContexts(void) {
    s32 i;

    for (i = 0; i < 16; i++) {
        ModelRenderer_AttachDisplayObject(&D_843903D0[i]);
        gGraphNodeUsed[i] = 0;
    }

    for (i = 0; i < 4; i++) {
        ModelRenderer_AttachSecondaryDisplayObject(&gParticleNodePool[i]);
        gParticleNodeUsed[i] = 0;
    }
}

ParticleEffectInstance* BattleAnim_GetOwnerContextParticle(Fragment2_1GraphNode* arg0) {
    return arg0->unk_000.unk_14;
}

Fragment2_1GraphNode* BattleAnim_AllocOwnerDisplayContext(ParticleEffectInstance* arg0) {
    s32 i;
    s32 var_v0 = -1;
    Fragment2_1GraphNode* temp_a0;

    for (i = 0; i < 16; i++) {
        if (gGraphNodeUsed[i] == 0) {
            var_v0 = i;
            break;
        }
    }

    if (var_v0 >= 0) {
        temp_a0 = &D_843903D0[var_v0];
        gGraphNodeUsed[var_v0] = 1;
        temp_a0->unk_000.unk_14 = arg0;
    } else {
        temp_a0 = NULL;
    }
    return temp_a0;
}

void BattleAnim_FreeOwnerDisplayContext(Fragment2_1GraphNode* arg0) {
    s32 i;

    for (i = 0; i < 16; i++) {
        if (arg0 == &D_843903D0[i]) {
            break;
        }
    }

    if (i != 16) {
        gGraphNodeUsed[i] = 0;
        ModelRenderer_ClearDisplayObject(arg0);
    }
}

Fragment2_1GraphNode* BattleAnim_AllocParticleDisplayContext(ParticleEffectInstance* arg0) {
    s32 i;
    s32 var_a2 = -1;
    Fragment2_1GraphNode* sp1C;

    for (i = 0; i < 4; i++) {
        if (gParticleNodeUsed[i] == 0) {
            var_a2 = i;
            break;
        }
    }

    if (var_a2 >= 0) {
        sp1C = &gParticleNodePool[var_a2];
        gParticleNodeUsed[var_a2] = 1;
        Particle_SetFlags(arg0, 0x400);
        sp1C->unk_000.unk_14 = arg0;
    } else {
        sp1C = NULL;
    }
    return sp1C;
}

void BattleAnim_FreeParticleDisplayContext(Fragment2_1GraphNode* arg0) {
    s32 i;

    for (i = 0; i < 4; i++) {
        if (arg0 == &gParticleNodePool[i]) {
            break;
        }
    }

    if (i != 4) {
        gParticleNodeUsed[i] = 0;
        ModelRenderer_ClearDisplayObject(arg0);
    }
}

void BattleAnim_InitModelWithAnim(Fragment2_1GraphNode* arg0, s16 arg1, s16 arg2) {
    Model_InitDisplayObject(arg0, 0, 0, gBattleAnimAssetPointers[arg1]);
    ModelAnim_BindTransformCurve(arg0, 0, gBattleAnimAssetPointers[arg2], 0x10000);
}

void BattleAnim_SetModelAnimFrame(Fragment2_1GraphNode* arg0, s16 arg1) {
    ModelAnim_SetFrame(arg0, arg1);
}

void BattleAnim_InitModel(Fragment2_1GraphNode* arg0, s16 arg1) {
    Model_InitDisplayObject(arg0, 0, 0, gBattleAnimAssetPointers[arg1]);
}

void BattleAnim_BindModelAnim(Fragment2_1GraphNode* arg0, s16 arg1) {
    ModelAnim_BindTransformCurve(arg0, 0, gBattleAnimAssetPointers[arg1], 0x10000);
}

void BattleAnim_BindModelAnimReversed(Fragment2_1GraphNode* arg0, s16 arg1) {
    ModelAnim_BindTransformCurve(arg0, 0, gBattleAnimAssetPointers[arg1], -0x10000);
    ModelAnim_SetFrame(arg0, arg0->unk_040.rotation->unk_0A - 1);
}

s32 BattleAnim_IsModelAnimComplete(Fragment2_1GraphNode* arg0) {
    s32 ret = 0;

    if (arg0->unk_040.RentalSlotAnimData_PosePhase == 0) {
        ret = 1;
    }
    return ret;
}

void BattleAnim_UpdateEffectCallbacks(UNUSED CameraStruct* arg0) {
    s32 i;

    for (i = 0; i < 8; i++) {
        if ((gCameraCallbackFuncs[i] != NULL) && (gCameraCallbackFuncs[i]() != 0)) {
            gCameraCallbackFuncs[i] = NULL;
            gCameraUpdateFuncs[i] = 0;
        }
    }
}

void BattleAnim_DrawEffectCallbacks(UNUSED CameraStruct* arg0) {
    s32 i;

    for (i = 0; i < 8; i++) {
        if (gCameraUpdateFuncs[i] != NULL) {
            gCameraUpdateFuncs[i]();
        }
    }
}

void BattleAnim_UpdateCamera(CameraStruct* arg0) {
    gParticleRenderContext.unk_0C = arg0;
    gParticleCameraInfo = &gParticleRenderContext.unk_10;

    MtxF_Copy(&gParticleCameraInfo->posX, &arg0->unk_60.mtxf);
    ParticleMath_CopyVec3f(&gParticleCameraInfo->unk_40, &arg0->unk_60.eye);
    ParticleMath_CopyVec3f(&gParticleCameraInfo->unk_4C, &arg0->unk_60.at);
    BattleAnim_GetCameraLookAngles(&gParticleCameraInfo->unk_70, &gParticleCameraInfo->lookRotationY);
    BattleAnim_GetCameraEyeAngles(&gParticleCameraInfo->eyeRotationX, &gParticleCameraInfo->unk_78);
    ParticleMath_NormalizedDirection(&gParticleCameraInfo->unk_58, gParticleCameraInfo->unk_40, gParticleCameraInfo->unk_4C);
    ParticleMath_NormalizedDirection(&gParticleCameraInfo->unk_64, gParticleCameraInfo->unk_4C, gParticleCameraInfo->unk_40);
}

s32 BattleAnim_DispatchPresentation(s32 arg0, CameraStruct* arg1) {
    switch (arg0) {
        case 1:
        case 3:
        case 4:
            break;

        case 0:
            BattleAnim_Initialize();
            break;

        case 2:
            BattleAnim_UpdateCamera(arg1);
            BattleAnim_UpdateFrame(arg1);
            BattleAnim_UpdateEffectCallbacks(arg1);
            break;

        case 5:
            BattleAnim_RenderEffectsFrame(arg1);
            break;
    }

    return 0;
}

void BattleAnim_Initialize(void) {
    BattleAnim_InitParticleSystem();
    BattleAnim_Reset();
}

void BattleAnim_Reset(void) {
    s32 i;

    gParticleEffectAttackerEntity = NULL;
    gWaterEffectCounter = 0;
    gParticleRenderContext.posX.x = 1.0f;
    gParticleRenderContext.posX.y = 1.0f;
    gParticleRenderContext.posX.z = 1.0f;
    gGameStateFlag = 0;
    gWaterAnimParams.unk_0C = 1.0f;
    gWaterAnimParams.unk_10 = 1.0f;
    gStateCallbackSlot = 0;

    for (i = 0; i < 8; i++) {
        gCameraCallbackFuncs[i] = NULL;
        gCameraUpdateFuncs[i] = NULL;
    }

    gSavedPrimColorR = 0xFF;
    gSavedPrimColorG = 0xFF;
    gSavedPrimColorB = 0xFF;
    gPrimColorA = 0xFF;
    gPrimColorR = 0xFF;
    gPrimColorG = 0xFF;
    gPrimColorB = 0xFF;
    gEnvColorR = 0xFF;
    gEnvColorG = 0xFF;
    gEnvColorB = 0x64;
    gFogColorR = 0;
    gFogColorG = 0;
    gFogColorB = 0;
    gWaterScale = 1.0f;

    Vec3f_SetComponentsDuplicate(&gCameraPosOffset, 0.0f, 0.0f, 0.0f);
    Vec3s_SetComponents(&gCameraRotOffset, 0, 0, 0);
    Vec3s_SetComponents(&gCameraTargetOffset, 0, 0, 0);
    Vec3f_SetComponentsDuplicate(&gCameraLookAtPos, 0.0f, 0.0f, 0.0f);
    Vec3s_SetComponents(&gCameraAngles, 0, 0, 0);
    BattleAnim_ResetAssetTable();
    BattleAnim_ResetDisplayContexts();
    gGraphNodePoolInitFlag = 0;
    gParticleNodePoolInitFlag = 0;
    BattleAnim_EnableEffectSpawning();
}

void BattleAnim_GetPointAlongCameraRay(Vec3f* arg0, f32 arg1) {
    arg0->x = gParticleCameraInfo->unk_40.x + (arg1 * gParticleCameraInfo->unk_58.x);
    arg0->y = gParticleCameraInfo->unk_40.y + (arg1 * gParticleCameraInfo->unk_58.y);
    arg0->z = gParticleCameraInfo->unk_40.z + (arg1 * gParticleCameraInfo->unk_58.z);
}

void BattleAnim_GetCameraEyeAngles(s16* arg0, s16* arg1) {
    CameraStruct* temp_v0 = BattleAnim_GetCameraContext();
    f32 sp20 = temp_v0->unk_60.eye.x - temp_v0->unk_60.at.x;
    f32 sp1C = temp_v0->unk_60.eye.y - temp_v0->unk_60.at.y;
    f32 sp18 = temp_v0->unk_60.eye.z - temp_v0->unk_60.at.z;

    *arg0 = MathUtil_Atan2s(sqrtf(SQ(sp20) + SQ(sp18)), sp1C);
    *arg1 = MathUtil_Atan2s(sp18, sp20);
}

void BattleAnim_GetCameraEyeYaw(s16* arg0) {
    CameraStruct* temp_v0 = BattleAnim_GetCameraContext();
    f32 x = temp_v0->unk_60.eye.x - temp_v0->unk_60.at.x;
    f32 z = temp_v0->unk_60.eye.z - temp_v0->unk_60.at.z;

    *arg0 = MathUtil_Atan2s(z, x);
}

void BattleAnim_GetCameraLookAngles(s16* arg0, s16* arg1) {
    CameraStruct* temp_v0 = BattleAnim_GetCameraContext();
    f32 sp20 = temp_v0->unk_60.at.x - temp_v0->unk_60.eye.x;
    f32 sp1C = temp_v0->unk_60.at.y - temp_v0->unk_60.eye.y;
    f32 sp18 = temp_v0->unk_60.at.z - temp_v0->unk_60.eye.z;

    *arg0 = MathUtil_Atan2s(sqrtf(SQ(sp20) + SQ(sp18)), sp1C);
    *arg1 = MathUtil_Atan2s(sp18, sp20);
}

void BattleAnim_GetCameraLookYaw(s16* arg0) {
    CameraStruct* temp_v0 = BattleAnim_GetCameraContext();
    f32 x = temp_v0->unk_60.at.x - temp_v0->unk_60.eye.x;
    f32 z = temp_v0->unk_60.at.z - temp_v0->unk_60.eye.z;

    *arg0 = MathUtil_Atan2s(z, x);
}

void BattleAnim_GetCameraStoredEyeAngles(s16* arg0, s16* arg1) {
    *arg0 = gParticleCameraInfo->eyeRotationX;
    *arg1 = gParticleCameraInfo->unk_78;
}

void BattleAnim_GetCameraStoredEyeRotationY(s16* arg0) {
    *arg0 = gParticleCameraInfo->unk_78;
}

void BattleAnim_GetCameraStoredLookAngles(s16* arg0, s16* arg1) {
    *arg0 = gParticleCameraInfo->unk_70;
    *arg1 = gParticleCameraInfo->lookRotationY;
}

void BattleAnim_GetCameraStoredLookRotationY(s16* arg0) {
    *arg0 = gParticleCameraInfo->lookRotationY;
}
