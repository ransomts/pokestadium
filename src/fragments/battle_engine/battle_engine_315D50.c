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
static s8 gCurrentActionScriptType;
s16 gParticleTexture_Default;
s16 gParticleEffectPrimaryId;
static s16 gParticleEffectSecondaryId;
BattlePlayerEntity* gParticleEffectEntityA;
BattlePlayerEntity* gParticleEffectData_42;
BattlePlayerEntity* gParticleEffectEntityB;
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
    ParticleEffect_WaterAnimBurst, ParticleEffect_InitSetA, ParticleEffect_InitSmokeSetA, ParticleEffect_PaletteScriptBurst, BattleAnim_EffectStartNop, InitParticleEffectSet_Alt2, BattleAnim_EffectStartNop,
    ParticleEffect_RegisterEffectE0, ParticleEffect_GroupSetupA, ParticleEffect_FinalGroupSetup, ParticleEffect_ComplexNodeSetup, BattleAnim_EffectStartNop, BattleAnim_EffectStartNop, ParticleEffect_RegisterSparkle,
    ParticleEffect_InitSmokeSetB, ParticleEffect_BasicMultiBurst2, ParticleEffect_SimpleBurstScript, ParticleEffect_RegisterExplosion, InitParticleEffectSet_WithFade, ParticleEffect_RegisterLargeExplosion, ParticleEffect_TextureSetup,
    BattleAnim_EffectStartNop, BattleAnim_EffectStartNop, BattleAnim_EffectStartNop, ParticleEffect_SetMode, BattleAnim_EffectStartNop, InitParticleEffectSet_WithTexture53, SpawnTimedFireballEffect,
    ParticleEffect_SimpleNodeEntry, ParticleEffect_RegisterAll_48630, BattleAnim_EffectStartNop, ParticleEffect_RegisterHandler_49628, ParticleEffect_RegisterEffectE0Alt2, BattleAnim_EffectStartNop, ParticleEffect_RegisterHandler_49830,
    ParticleEffect_AdditionalNodeSetup, ParticleEffect_SmallNodeSetupB, InitExplosionEffectSet, BattleAnim_CreateStreamSprayColumnEffect, ParticleEffect_GroupSetupA, ParticleEffect_HandleStateSetup, BattleAnim_EffectStartNop,
    ParticleEffect_RegisterHandlers_Default, ParticleEffect_RegisterHandler_416B0, ParticleEffect_RegisterParticleNodes, ParticleEffect_RegisterMultipleHandlers, BattleAnim_EffectStartNop, ParticleEffect_RegisterHandler_49384, ParticleEffect_RegisterHandlers_49504,
    InitParticleEffectSet_WithDifferentTiming, ParticleEffect_RegisterHandler_49058, ParticleEffect_RegisterHandler_47448, BattleAnim_CreateCollisionRandomEffect, ParticleEffect_RegisterHandler_49108, ParticleEffect_RegisterHandlers_Alternate, ParticleEffect_RegisterEffectE0Alt,
    InitSmallGlowEffectSet, InitParticleEffectSet_Single, ParticleEffect_RegisterHandler_498D8, ParticleEffect_RegisterDefaultTexture, ParticleEffect_AdvancedModeSetup, ParticleEffect_RegisterAll_48630, ParticleEffect_SimpleBurst,
    ParticleEffect_InitSmokeSetC, ParticleEffect_FinalSetupA, ParticleEffect_RegisterLargeExplosionAndEffects, BattleAnim_EffectStart_Custom, ParticleEffect_MultiNodeC2, ParticleEffect_MultiNodeD, ParticleEffect_PortraitBurst,
    ParticleEffect_PortraitBurstNode, ParticleEffect_PortraitBurstCheck, ParticleEffect_WaterAnimFirework, ParticleEffect_SimpleBurst2, ParticleEffect_PaletteMultiBurst2, ParticleEffect_PaletteBurst4, ParticleEffect_PaletteBurst5,
    BattleAnim_EffectStartNop, ParticleEffect_BasicMultiBurst, ParticleEffect_SimpleBurst4, ParticleEffect_RotationEntry, BattleAnim_DisableEffectSpawningAlias, ParticleEffect_InitSmoke, ParticleEffect_InitFire,
    ParticleEffect_TriggerSpecial, ParticleEffect_AlphaBurst, ParticleEffect_AlphaBurst2, ParticleEffect_AdditionalSetupA, ParticleEffect_SimpleGroupSetup, ParticleEffect_ComplexGroupSetup, ParticleEffect_RegisterHandler_490A8,
    ParticleEffect_PortraitBurstInit, ParticleEffect_TriggerDefault1, ParticleEffect_FinalSetupB, ParticleEffect_FinalSetupC, ParticleEffect_AdditionalNodeA, ParticleEffect_StateCollisionSetupA, ParticleEffect_CreateWithCallback,
    ParticleEffect_CreateCallback, InitSmallGlowEffectSet, ParticleEffect_TriggerDefault3, BattleAnim_StartEffect122GlobalAndOwnerTintFade, ParticleEffect_ConditionalStateSetup, ParticleEffect_CollisionResponseSwitch, ParticleEffect_RegisterCallbacks,
    BattleAnim_EffectStart_Special, ParticleEffect_CreateVariant45, ParticleEffect_CreateVariant47, ParticleEffect_CreateTypeX, ParticleEffect_CreateSmoke, ParticleEffect_CreateSmokeHighPriority, ParticleEffect_CreateDual,
    BattleAnim_StartEffect133ModeOrbitBurstAndEffect135Followup, BattleAnim_StartEffect134ModeOrbitAndMetadataBurst, BattleAnim_StartEffect135ExpandingFlashAndRisingScaleFade, BattleAnim_EffectStartNop, BattleAnim_StartEffect137Descriptor3FRisingFade, ParticleEffect_TextureNodeSetup, BattleAnim_StartEffect139DualRepeatingSparks,
    BattleAnim_StartEffect140StartEffect139Alias, BattleAnim_StartEffect141GridRiseAndFallingBurst, BattleAnim_StartEffect142StartEffect141Alias, BattleAnim_StartEffect143ModeOrbitAndMetadataBurst, BattleAnim_EffectStartNop,
};
static func_D_84390320 gParticleStateFunctionTable[] = {
    BattleAnim_EffectEndNop, BattleAnim_EffectEndNop, InitComplexParticleSequence, ParticleEffect_SpecialCollisionSetup, ParticleEffect_MultiTextureSetup, ParticleEffect_DynamicCollisionSetup, ParticleEffect_RegisterPaletteVariants,
    ParticleEffect_PaletteMultiBurst, BattleAnim_CreateSprayColumnEffect, BattleAnim_EffectEndNop, ParticleEffect_RegisterAnimationCallbacks, BattleAnim_EffectEndNop, BattleAnim_EffectEndNop, ParticleEffect_RegisterSpecific,
    ParticleEffect_InitializeGroup, ParticleEffect_InitExplosionSetB, ParticleEffect_AdvancedMultiBurst, ParticleEffect_RegisterSmoke, ParticleEffect_ModeSpecificSetup, BattleAnim_EffectEndNop, InitParticleComboVariant,
    ParticleEffect_RegisterModeSpecific, ParticleEffect_InitExplosionSet, ParticleEffect_RegisterAll, BattleAnim_EffectEndNop, ParticleEffect_PlaySoundAndReset, RegisterParticleEffect_ComplexMovement, InitAdvancedParticleCombo,
    BattleAnim_CreateBurstStreamEffect, ParticleEffect_InitFireSet, ParticleEffect_HandleCollisionSetup, ParticleEffect_RegisterMultiple, BattleAnim_EffectEndNop, BattleAnim_EffectEndNop, InitParticleEffectGroup_Basic,
    ParticleEffect_ConfigB, ParticleEffect_ConfigA, ParticleEffect_SpecialSetupA, ParticleEffect_SpecialSetupB, ParticleEffect_AdditionalSetupB, ParticleEffect_InitSparkleSet, ParticleEffect_Trigger56A74,
    ParticleEffect_ModeSetup, ParticleEffect_CollisionSetup, ParticleEffect_ConfigVariantA, ParticleEffect_CombinedSetupA, ParticleEffect_CombinedSetupB, ParticleEffect_SpecialSetupC, BattleAnim_EffectEndNop,
    ParticleEffect_RegisterColorAnim, ParticleEffect_RegisterHandler_WithParticleData, ParticleEffect_WaterAnimBurst2, ParticleEffect_MultiHandleSetup, InitParticleEffectSet_WithCustomCallback, ParticleEffect_InitSetC, ParticleEffect_SimpleNodeSetup,
    ParticleEffect_InitSetB, ParticleEffect_FullSetupB, BattleAnim_EffectEnd_Custom, ParticleEffect_InitCombinedSet, ParticleEffect_WaterAnimFirework2, ParticleEffect_SimpleBurst3, ParticleEffect_PaletteMultiBurst3,
    ParticleEffect_FireworkBurst, ParticleEffect_FireballBurst, ParticleEffect_FireworkEntry, ParticleEffect_SimpleNodeBurst, InitParticleEffectSet_WithMultiple, InitParticleEffectSet_WithTimedFireball, InitParticleEffectSet_Variant2,
    InitParticleEffectSet_WithComplex, InitParticleEffectSet_Variant3, BattleAnim_CreateSprayColumnEffectTrigger, ParticleEffect_AlphaFirework2, ParticleEffect_AlphaFirework, ParticleEffect_MultiNodeAEntry, ParticleEffect_TriggerAnother,
    ParticleEffect_TriggerDefault2, ParticleEffect_RegisterHandlers_4967C, ParticleEffect_CreateColorVariant, ParticleEffect_ConfigVariantB, ParticleEffect_RegisterAll_489FC, ParticleEffect_RegisterAll_489FC, ParticleEffect_ConfigureAndTrigger_4917C,
    ParticleEffect_TriggerDefault4, ParticleEffect_StateCollisionSetupB, InitParticleEffectSet_ThreeInstances, RegisterParticleEffect_Burst, ParticleEffect_CollisionAndBurstSetup, BattleAnim_EffectEndNop,
};
static u8 gBattleScript_NullParam[] = {
    0x3F, 0x00, 0x00, 0x00, 0x3F, 0x00, 0x00, 0x00, 0x3F, 0x00, 0x00, 0x00,
    0x3F, 0x00, 0x00, 0x00, 0x01, 0x3F, 0x00, 0x00, 0x3F, 0x00, 0x00, 0x00,

};
static u8 gBattleScript_NullParam8[] = {
    0x03,
    0x3F,
    0x00,
    0x00,

};
static u8 gBattleScriptTable_48[] = {
    0x04,
    0x3F,
    0x00,
    0x00,

};
static u8 gBattleScript_Param05[] = {
    0x05,
    0x3F,
    0x00,
    0x00,

};
static u8 gBattleScript_Param06[] = {
    0x06,
    0x3F,
    0x00,
    0x00,

};
static u8 gBattleScript_Param09[] = {
    0x09,
    0x3F,
    0x00,
    0x00,

};
static u8 gBattleScript_Param0A[] = {
    0x0A,
    0x3F,
    0x00,
    0x00,

};
static u8 gBattleScript_NullParam7[] = {
    0x0B,
    0x3F,
    0x00,
    0x00,

};
static u8 gBattleScriptTable_60[] = {
    0x0C, 0x3F, 0x00, 0x00, 0x0D, 0x3F, 0x00, 0x00,

};
static u8 gBattleScript_NullParam5[] = {
    0x0E,
    0x3F,
    0x00,
    0x00,

};
static u8 gBattleScript_NullParam11[] = {
    0x0F,
    0x3F,
    0x00,
    0x00,

};
static u8 gBattleScript_Param10[] = {
    0x10,
    0x3F,
    0x00,
    0x00,

};
static u8 gBattleScript_NullParam6[] = {
    0x11,
    0x3F,
    0x00,
    0x00,

};
static u8 gBattleScript_NullParam10[] = {
    0x11,
    0x3D,
    0x3F,
    0x00,

};
static u8 gBattleScriptCmd_46[] = {
    0x12,
    0x3F,
    0x00,
    0x00,

};
static u8 gBattleScript_Param13[] = {
    0x13,
    0x3F,
    0x00,
    0x00,

};
static u8 gBattleScriptTable_84[] = {
    0x14, 0x3F, 0x00, 0x00, 0x15, 0x3F, 0x00, 0x00,

};
static u8 gBattleScript_Param16[] = {
    0x16, 0x3F, 0x00, 0x00, 0x17, 0x3F, 0x00, 0x00,

};
static u8 gBattleScript_NullParam2[] = {
    0x18,
    0x3F,
    0x00,
    0x00,

};
static u8 gBattleScript_Param19[] = {
    0x19,
    0x32,
    0x3F,
    0x00,

};
static u8 gBattleScript_Param1A[] = {
    0x1A,
    0x3F,
    0x00,
    0x00,

};
static u8 gBattleScript_NullParam9[] = {
    0x1B,
    0x27,
    0x3F,
    0x00,

};
static u8 gBattleScriptTable_A4[] = {
    0x1C,
    0x3F,
    0x00,
    0x00,

};
static u8 gBattleScript_Param27[] = {
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
static u8 gBattleScriptTable_B4[] = {
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
static u8 gBattleScript_NullParam12[] = {
    0x25,
    0x3F,
    0x00,
    0x00,

};
static u8 gBattleScript_NullParam4[] = {
    0x26,
    0x11,
    0x3F,
    0x00,

};
static u8 gBattleScriptTable_D0[] = {
    0x27,
    0x32,
    0x3F,
    0x00,

};
static u8 gBattleScriptCmd_28[] = {
    0x28,
    0x3F,
    0x00,
    0x00,

};
static u8 gBattleScriptCmd_29[] = {
    0x29,
    0x03,
    0x3F,
    0x00,

};
static u8 gBattleScriptCmd_2A[] = {
    0x2A,
    0x3F,
    0x00,
    0x00,

};
static u8 gBattleScriptCmd_2B[] = {
    0x2B,
    0x11,
    0x3F,
    0x00,

};
static u8 gBattleScriptCmd_17[] = {
    0x17,
    0x3F,
    0x00,
    0x00,

};
static u8 gBattleScriptCmd_09[] = {
    0x09,
    0x3F,
    0x00,
    0x00,

};
static u8 gBattleScriptCmd_0B_0E[] = {
    0x0B, 0x3F, 0x00, 0x00, 0x0E, 0x3F, 0x00, 0x00,

};
static u8 gBattleScriptCmd_14[] = {
    0x14,
    0x3F,
    0x00,
    0x00,

};
static u8 gBattleScriptCmd_15[] = {
    0x15,
    0x3F,
    0x00,
    0x00,

};
static u8 gBattleScriptCmd_1E[] = {
    0x1E,
    0x3F,
    0x00,
    0x00,

};
static u8 gBattleScriptCmd_10[] = {
    0x10,
    0x3F,
    0x00,
    0x00,

};
static u8 gBattleScriptTable_904[] = {
    0x14,
    0x3F,
    0x00,
    0x00,

};
static u8 gBattleScriptCmd_0C[] = {
    0x0C,
    0x3F,
    0x00,
    0x00,

};
static u8 gBattleScriptCmd_07[] = {
    0x07,
    0x3F,
    0x00,
    0x00,

};
static u8 gBattleScriptCmd_36[] = {
    0x36,
    0x3F,
    0x00,
    0x00,

};
static u8 gBattleScriptCmd_18[] = {
    0x18,
    0x0D,
    0x3F,
    0x00,

};
static u8 gBattleScriptTable_918[] = {
    0x03, 0x3F, 0x00, 0x00, 0x14, 0x3F, 0x00, 0x00,

};
static u8 gBattleScriptCmd_2C[] = {
    0x2C,
    0x3F,
    0x00,
    0x00,

};
static u8 gBattleScriptCmd_2C_Alt[] = {
    0x2C,
    0x3F,
    0x00,
    0x00,

};
static u8 gBattleScriptCmd_3C[] = {
    0x3C,
    0x3F,
    0x00,
    0x00,

};
static u8 gBattleScriptCmd_2D[] = {
    0x2D,
    0x3F,
    0x00,
    0x00,

};
static u8 gBattleScriptCmd_08[] = {
    0x08,
    0x3F,
    0x00,
    0x00,

};
static u8 gBattleScriptCmd_2E[] = {
    0x2E,
    0x3F,
    0x00,
    0x00,

};
static u8 gBattleScriptCmd_2F[] = {
    0x2F,
    0x3F,
    0x00,
    0x00,

};
static u8 gBattleScriptCmd_30[] = {
    0x30,
    0x3F,
    0x00,
    0x00,

};
static u8 gBattleScriptCmd_31[] = {
    0x31,
    0x3F,
    0x00,
    0x00,

};
static u8 gBattleScriptCmd_32[] = {
    0x32,
    0x3F,
    0x00,
    0x00,

};
static u8 gBattleScriptCmd_33[] = {
    0x33,
    0x3F,
    0x00,
    0x00,

};
static u8 gBattleScriptCmd_34[] = {
    0x34,
    0x3F,
    0x00,
    0x00,

};
static u8 gBattleScriptCmd_35[] = {
    0x35,
    0x3F,
    0x00,
    0x00,

};
static u8 gBattleScriptCmd_37[] = {
    0x37,
    0x3F,
    0x00,
    0x00,

};
static u8 gBattleScriptCmd_38[] = {
    0x38,
    0x3F,
    0x00,
    0x00,

};
static u8 gBattleScriptCmd_39[] = {
    0x39,
    0x3F,
    0x00,
    0x00,

};
static u8 gBattleScriptCmd_3A[] = {
    0x3A,
    0x0B,
    0x3F,
    0x00,

};
static u8 gBattleScriptCmd_3B[] = {
    0x3B,
    0x2C,
    0x3F,
    0x00,

};
static u8 gBattleScriptCmd_00[] = {
    0x00, 0x00, 0x00, 0x00, 0x66, 0x00, 0x00, 0x00,

};
static u8 gBattleScriptCmd_90[] = {
    0x90,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScriptCmd_01[] = {
    0x01,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScriptCmd_02[] = {
    0x02,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScriptCmd_03[] = {
    0x03,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScriptCmd_66_04_05[] = {
    0x66, 0x04, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00,

};
static u8 gBattleScriptCmd_06[] = {
    0x06,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScriptCmd_3A_Alt[] = {
    0x3A,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScriptJump_07[] = {
    0x66,
    0x07,
    0x00,
    0x00,

};
static u8 gBattleScriptCmd_08_09[] = {
    0x08, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00,

};
static u8 gBattleScriptCmd_0A[] = {
    0x0A,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScriptCmd_66_0B_0C[] = {
    0x66, 0x0B, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x00,

};
static u8 gBattleScriptCmd_0D[] = {
    0x0D,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScriptCmd_7B[] = {
    0x7B,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScriptCmd_7C[] = {
    0x7C,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScriptCmd_0E[] = {
    0x0E,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScriptCmd_0F[] = {
    0x0F,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScriptTable_9BC[] = {
    0x10,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScriptCmd_11[] = {
    0x11,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScriptCmd_12[] = {
    0x12,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScriptCmd_13_14[] = {
    0x13, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00,

};
static u8 gBattleScriptCmd_15_Alt[] = {
    0x15,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScriptCmd_16[] = {
    0x16,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScriptCmd_4D[] = {
    0x17,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScriptCmd_18_Alt[] = {
    0x18,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScriptCmd_4E[] = {
    0x19, 0x00, 0x00, 0x00, 0x1B, 0x00, 0x00, 0x00,

};
static u8 gBattleScriptCmd_1C[] = {
    0x1C,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScriptCmd_4C[] = {
    0x4C,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScriptTable_9F0[] = {
    0x1D, 0x00, 0x00, 0x00, 0x1E, 0x00, 0x00, 0x00,

};
static u8 gBattleScriptCmd_1F[] = {
    0x1F,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScriptCmd_20[] = {
    0x20,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScriptCmd_21[] = {
    0x21,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScriptCmd_22[] = {
    0x22,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScriptCmd_23[] = {
    0x23,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScriptJump_24[] = {
    0x66,
    0x24,
    0x00,
    0x00,

};
static u8 gBattleScriptCmd_25[] = {
    0x25,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScriptCmd_26[] = {
    0x26,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScriptJump_27[] = {
    0x66,
    0x27,
    0x00,
    0x00,

};
static u8 gBattleScriptCmd_28_Alt[] = {
    0x28,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScriptCmd_29_Alt[] = {
    0x29,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScriptJump_2A[] = {
    0x66,
    0x2A,
    0x00,
    0x00,

};
static u8 gBattleScriptCmd_2B_Alt[] = {
    0x2B,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScriptCmd_2C_Alt2[] = {
    0x2C,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScriptJump_2D[] = {
    0x66, 0x2D, 0x00, 0x00, 0x2E, 0x00, 0x00, 0x00,

};
static u8 gBattleScriptJump_2F[] = {
    0x66,
    0x2F,
    0x00,
    0x00,

};
static u8 gBattleScriptTable_A3C[] = {
    0x30,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScriptTable_A40[] = {
    0x31,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScriptTable_A44[] = {
    0x32,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScriptCmd_52[] = {
    0x52,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScriptCmd_59[] = {
    0x59,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScriptTable_A50[] = {
    0x34, 0x00, 0x00, 0x00, 0x35, 0x00, 0x00, 0x00, 0x36, 0x00, 0x00, 0x00,

};
static u8 gBattleScriptTable_A5C[] = {
    0x37,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScriptCmd_35_05[] = {
    0x35,
    0x05,
    0x00,
    0x00,

};
static u8 gBattleScriptCmd_6A[] = {
    0x6A,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScriptCmd_6B[] = {
    0x6B,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScriptCmd_1B[] = {
    0x1B,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScriptCmd_56[] = {
    0x56,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScriptTable_A74[] = {
    0x1E,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScriptCmd_5D[] = {
    0x5D,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScriptTable_A7C[] = {
    0x1C,
    0x36,
    0x00,
    0x00,

};
static u8 gBattleScriptTable_A80[] = {
    0x0E,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScriptCmd_40[] = {
    0x40,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScriptTable_A88[] = {
    0x0C,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScriptCmd_42[] = {
    0x42,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScriptCmd_5F[] = {
    0x5F,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScriptJump_4E[] = {
    0x66,
    0x4E,
    0x00,
    0x00,

};
static u8 gBattleScriptTable_A98[] = {
    0x3B,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScriptCmd_38_Alt[] = {
    0x38,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScriptJump_39[] = {
    0x66,
    0x39,
    0x00,
    0x00,

};
static u8 gBattleScriptCmd_3D[] = {
    0x3D,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScriptCmd_3E[] = {
    0x3E,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScriptCmd_7D[] = {
    0x7D,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScriptCmd_7E[] = {
    0x7E,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScriptCmd_7F[] = {
    0x7F,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScriptCmd_80[] = {
    0x80,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScriptCmd_81[] = {
    0x81,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScriptCmd_82[] = {
    0x82,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScriptCmd_83[] = {
    0x83,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScriptCmd_84[] = {
    0x84,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScriptCmd_8B[] = {
    0x8B,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScriptCmd_8C[] = {
    0x8C,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScriptCmd_8D[] = {
    0x8D,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScriptCmd_8E[] = {
    0x8E,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScriptCmd_85[] = {
    0x85,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScriptCmd_86[] = {
    0x86,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScriptCmd_8F[] = {
    0x8F,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScriptCmd_87[] = {
    0x87,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScriptCmd_88[] = {
    0x88,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScriptCmd_89[] = {
    0x89,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScriptCmd_8A[] = {
    0x8A,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScriptCmd_3F[] = {
    0x3F,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScriptCmd_41[] = {
    0x41,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScriptCmd_43[] = {
    0x43,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScriptCmd_71[] = {
    0x71,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScriptCmd_79[] = {
    0x79,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScriptCmd_44[] = {
    0x44,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScriptCmd_45[] = {
    0x45,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScriptJump_46[] = {
    0x66,
    0x46,
    0x00,
    0x00,

};
static u8 gBattleScriptCmd_47[] = {
    0x47,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScriptCmd_6F[] = {
    0x6F,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScriptCmd_48[] = {
    0x48,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScriptCmd_49[] = {
    0x49,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScriptCmd_4A[] = {
    0x4A,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScriptCmd_4B[] = {
    0x4B,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScriptJump_78[] = {
    0x66,
    0x78,
    0x00,
    0x00,

};
static u8 gBattleScriptCmd_4F[] = {
    0x4F,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScriptCmd_50[] = {
    0x50,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScriptCmd_51[] = {
    0x51,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScriptCmd_53[] = {
    0x53,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScriptCmd_54[] = {
    0x54,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScriptCmd_55[] = {
    0x55,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScriptCmd_72[] = {
    0x72,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScriptCmd_73[] = {
    0x73,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScriptCmd_74[] = {
    0x74,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScriptCmd_57[] = {
    0x57,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScriptCmd_58[] = {
    0x58,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScriptTable_B60[] = {
    0x59,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScriptCmd_5A[] = {
    0x5A,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScriptCmd_5B[] = {
    0x5B,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScriptCmd_5C[] = {
    0x5C,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScriptCmd_5E[] = {
    0x5E,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScriptCmd_60[] = {
    0x60,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScriptCmd_61[] = {
    0x61,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScriptCmd_62[] = {
    0x62,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScriptCmd_63[] = {
    0x63,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScriptCmd_64[] = {
    0x64,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScriptCmd_65[] = {
    0x65,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScriptJump_1A[] = {
    0x66,
    0x1A,
    0x00,
    0x00,

};
static u8 gBattleScriptCmd_67[] = {
    0x67,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScriptCmd_68[] = {
    0x68,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScriptCmd_69[] = {
    0x69,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScriptCmd_6C[] = {
    0x6C,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScriptCmd_6D[] = {
    0x6D,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScriptCmd_6E[] = {
    0x6E,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScriptCmd_70[] = {
    0x70,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScriptCmd_75[] = {
    0x75,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScriptCmd_76[] = {
    0x76,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScriptCmd_77[] = {
    0x77,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScriptCmd_7A[] = {
    0x7A,
    0x00,
    0x00,
    0x00,

};
static u8 gBattleScript_NullParam3[] = {
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
static u8 Fragment62_Byte04[] = {
    0x04,
    0x00,
    0x00,
    0x00,

};
static u8 Fragment62_Byte05[] = {
    0x05,
    0x00,
    0x00,
    0x00,

};
static u8 Fragment62_Entry58_06[] = {
    0x58, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00,

};
static u8 Fragment62_Byte07[] = {
    0x07,
    0x00,
    0x00,
    0x00,

};
static u8 Fragment62_Byte08[] = {
    0x08,
    0x00,
    0x00,
    0x00,

};
static u8 Fragment62_Byte48[] = {
    0x48,
    0x00,
    0x00,
    0x00,

};
static u8 Fragment62_Byte09[] = {
    0x09,
    0x00,
    0x00,
    0x00,

};
static u8 Fragment62_Bytes0A_0B_0C_0D[] = {
    0x0A, 0x00, 0x00, 0x00, 0x0B, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x00, 0x0D, 0x00, 0x00, 0x00,

};
static u8 Fragment62_Byte0E[] = {
    0x0E,
    0x00,
    0x00,
    0x00,

};
static u8 Fragment62_Byte23[] = {
    0x23,
    0x00,
    0x00,
    0x00,

};
static u8 Fragment62_Byte24[] = {
    0x24,
    0x00,
    0x00,
    0x00,

};
static u8 Fragment62_Byte25[] = {
    0x25,
    0x00,
    0x00,
    0x00,

};
static u8 Fragment62_Bytes54_25[] = {
    0x54,
    0x25,
    0x00,
    0x00,

};
static u8 Fragment62_Bytes4D_0E[] = {
    0x4D,
    0x0E,
    0x00,
    0x00,

};
static u8 Fragment62_Byte26[] = {
    0x26,
    0x00,
    0x00,
    0x00,

};
static u8 Fragment62_Byte0F[] = {
    0x0F,
    0x00,
    0x00,
    0x00,

};
static u8 Fragment62_Byte10[] = {
    0x10,
    0x00,
    0x00,
    0x00,

};
static u8 Fragment62_Byte11[] = {
    0x11,
    0x00,
    0x00,
    0x00,

};
static u8 Fragment62_Bytes12_13_14[] = {
    0x12, 0x00, 0x00, 0x00, 0x13, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00,

};
static u8 Fragment62_Byte15[] = {
    0x15,
    0x00,
    0x00,
    0x00,

};
static u8 Fragment62_Byte16[] = {
    0x16,
    0x00,
    0x00,
    0x00,

};
static u8 Fragment62_Byte17[] = {
    0x17,
    0x00,
    0x00,
    0x00,

};
static u8 Fragment62_Byte18[] = {
    0x18,
    0x00,
    0x00,
    0x00,

};
static u8 Fragment62_Byte19[] = {
    0x19,
    0x00,
    0x00,
    0x00,

};
static u8 Fragment62_Bytes0D_0E[] = {
    0x0D,
    0x0E,
    0x00,
    0x00,

};
static u8 Fragment62_Byte03[] = {
    0x03,
    0x00,
    0x00,
    0x00,

};
static u8 Fragment62_Byte07b[] = {
    0x07,
    0x00,
    0x00,
    0x00,

};
static u8 Fragment62_Byte22[] = {
    0x22,
    0x00,
    0x00,
    0x00,

};
static u8 Fragment62_Byte35[] = {
    0x35,
    0x00,
    0x00,
    0x00,

};
static u8 Fragment62_Bytes45_0E_04[] = {
    0x45, 0x00, 0x00, 0x00, 0x0E, 0x04, 0x00, 0x00,

};
static u8 Fragment62_Byte1A[] = {
    0x1A,
    0x00,
    0x00,
    0x00,

};
static u8 Fragment62_Byte09b[] = {
    0x09,
    0x00,
    0x00,
    0x00,

};
static u8 Fragment62_Bytes06_0E[] = {
    0x06,
    0x0E,
    0x00,
    0x00,

};
static u8 Fragment62_Bytes1B_1C[] = {
    0x1B, 0x00, 0x00, 0x00, 0x1C, 0x00, 0x00, 0x00,

};
static u8 Fragment62_Byte1D[] = {
    0x1D,
    0x00,
    0x00,
    0x00,

};
static u8 Fragment62_Byte1E[] = {
    0x1E,
    0x00,
    0x00,
    0x00,

};
static u8 Fragment62_Byte55[] = {
    0x55,
    0x00,
    0x00,
    0x00,

};
static u8 Fragment62_Byte1F[] = {
    0x1F,
    0x00,
    0x00,
    0x00,

};
static u8 Fragment62_Byte20[] = {
    0x20,
    0x00,
    0x00,
    0x00,

};
static u8 Fragment62_Byte21[] = {
    0x21,
    0x00,
    0x00,
    0x00,

};
static u8 Fragment62_Bytes4F_27[] = {
    0x4F,
    0x27,
    0x00,
    0x00,

};
static u8 Fragment62_Byte28[] = {
    0x28,
    0x00,
    0x00,
    0x00,

};
static u8 Fragment62_Byte29[] = {
    0x29,
    0x00,
    0x00,
    0x00,

};
static u8 Fragment62_Byte2A[] = {
    0x2A,
    0x00,
    0x00,
    0x00,

};
static u8 Fragment62_Byte2B[] = {
    0x2B,
    0x00,
    0x00,
    0x00,

};
static u8 Fragment62_Byte2C[] = {
    0x2C,
    0x00,
    0x00,
    0x00,

};
static u8 Fragment62_Byte2D[] = {
    0x2D,
    0x00,
    0x00,
    0x00,

};
static u8 Fragment62_Bytes4F_2D[] = {
    0x4F,
    0x2D,
    0x00,
    0x00,

};
static u8 Fragment62_Byte2E[] = {
    0x2E,
    0x00,
    0x00,
    0x00,

};
static u8 Fragment62_Byte2F[] = {
    0x2F,
    0x00,
    0x00,
    0x00,

};
static u8 Fragment62_Byte31[] = {
    0x31,
    0x00,
    0x00,
    0x00,

};
static u8 Fragment62_Byte32[] = {
    0x32,
    0x00,
    0x00,
    0x00,

};
static u8 Fragment62_Bytes3F_23_33[] = {
    0x3F, 0x23, 0x00, 0x00, 0x33, 0x00, 0x00, 0x00,

};
static u8 Fragment62_Byte34[] = {
    0x34,
    0x00,
    0x00,
    0x00,

};
static u8 Fragment62_Byte36[] = {
    0x36,
    0x00,
    0x00,
    0x00,

};
static u8 Fragment62_Byte37[] = {
    0x37,
    0x00,
    0x00,
    0x00,

};
static u8 Fragment62_Byte39[] = {
    0x39,
    0x00,
    0x00,
    0x00,

};
static u8 Fragment62_Byte49[] = {
    0x49,
    0x00,
    0x00,
    0x00,

};
static u8 Fragment62_Byte4A[] = {
    0x4A,
    0x00,
    0x00,
    0x00,

};
static u8 Fragment62_Byte3A[] = {
    0x3A,
    0x00,
    0x00,
    0x00,

};
static u8 Fragment62_Byte4B[] = {
    0x4B,
    0x00,
    0x00,
    0x00,

};
static u8 Fragment62_Byte3B[] = {
    0x3B,
    0x00,
    0x00,
    0x00,

};
static u8 Fragment62_Byte3C[] = {
    0x3C,
    0x00,
    0x00,
    0x00,

};
static u8 Fragment62_Byte3D[] = {
    0x3D,
    0x00,
    0x00,
    0x00,

};
static u8 Fragment62_Byte3E[] = {
    0x3E,
    0x00,
    0x00,
    0x00,

};
static u8 Fragment62_Byte40[] = {
    0x40,
    0x00,
    0x00,
    0x00,

};
static u8 Fragment62_Bytes2D_1E[] = {
    0x2D,
    0x1E,
    0x00,
    0x00,

};
static u8 Fragment62_Byte41[] = {
    0x41,
    0x00,
    0x00,
    0x00,

};
static u8 Fragment62_Byte42[] = {
    0x42,
    0x00,
    0x00,
    0x00,

};
static u8 Fragment62_Byte43[] = {
    0x43,
    0x00,
    0x00,
    0x00,

};
static u8 Fragment62_Byte44[] = {
    0x44,
    0x00,
    0x00,
    0x00,

};
static u8 Fragment62_Byte46[] = {
    0x46,
    0x00,
    0x00,
    0x00,

};
static u8 Fragment62_Byte47[] = {
    0x47,
    0x00,
    0x00,
    0x00,

};
static u8 Fragment62_Bytes50_4C[] = {
    0x50,
    0x4C,
    0x00,
    0x00,

};
static u8 Fragment62_Bytes38_4D[] = {
    0x38, 0x00, 0x00, 0x00, 0x4D, 0x00, 0x00, 0x00,

};
static u8 Fragment62_Bytes4E_4F[] = {
    0x4E, 0x00, 0x00, 0x00, 0x4F, 0x00, 0x00, 0x00,

};
static u8 Fragment62_Byte51[] = {
    0x51,
    0x00,
    0x00,
    0x00,

};
static u8 Fragment62_Byte52[] = {
    0x52,
    0x00,
    0x00,
    0x00,

};
static u8 Fragment62_Byte02[] = {
    0x02,
    0x00,
    0x00,
    0x00,

};
static u8 Fragment62_Byte56[] = {
    0x56,
    0x00,
    0x00,
    0x00,

};
static u8 Fragment62_Byte53[] = {
    0x53,
    0x00,
    0x00,
    0x00,

};
static u8 Fragment62_Bytes57_23[] = {
    0x57,
    0x23,
    0x00,
    0x00,
};
static u8* Fragment62_SubTablePtr2D[][2] = {
    {
        gBattleScriptCmd_00,
        gBattleScript_NullParam,
    },
    {
        gBattleScriptCmd_85,
        gBattleScriptCmd_2C,
    },
    {
        gBattleScriptCmd_86,
        gBattleScriptCmd_2C,
    },
    {
        gBattleScriptCmd_87,
        gBattleScriptCmd_2C_Alt,
    },
    {
        gBattleScriptCmd_88,
        gBattleScriptCmd_2C_Alt,
    },
    {
        gBattleScriptCmd_89,
        gBattleScriptCmd_2D,
    },
    {
        gBattleScriptCmd_8A,
        gBattleScript_NullParam,
    },
    {
        gBattleScriptCmd_00,
        gBattleScript_NullParam,
    },
    {
        gBattleScriptCmd_8B,
        gBattleScriptCmd_2C_Alt,
    },
    {
        gBattleScriptCmd_15_Alt,
        gBattleScript_Param10,
    },
    {
        gBattleScriptCmd_8C,
        gBattleScriptCmd_3C,
    },
    {
        gBattleScriptCmd_8D,
        gBattleScriptCmd_3C,
    },
    {
        gBattleScriptCmd_8F,
        gBattleScriptCmd_2C,
    },
    {
        gBattleScriptCmd_8E,
        gBattleScriptCmd_3C,
    },
    {
        gBattleScriptCmd_7A,
        gBattleScript_NullParam,
    },
};
static u8* Fragment62_DataPtrArray[] = {
    gBattleScriptCmd_00, gBattleScriptCmd_7D, gBattleScriptCmd_7E, gBattleScriptCmd_01, gBattleScriptCmd_45, gBattleScriptCmd_7F,
    gBattleScriptCmd_80, gBattleScriptCmd_81, gBattleScriptCmd_82, gBattleScriptCmd_83, gBattleScriptCmd_84, gBattleScriptCmd_90,
};
static u8* Fragment62_GroupPtrArray[] = {
    gBattleScript_NullParam3, gBattleScript_MsgStart, Fragment62_Byte09, gBattleScript_MsgEnd, Fragment62_Byte31,
};
static u8* Fragment62_SpecialPairPtr[] = { gBattleScriptCmd_00, gBattleScriptCmd_2C_Alt2 };
static u8* Fragment62_ComplexPtrTable[][5] = {
    {
        gBattleScriptCmd_00,
        gBattleScriptCmd_00,
        gBattleScript_NullParam3,
        gBattleScript_NullParam,
        gBattleScript_NullParam,
    },
    {
        gBattleScriptCmd_00,
        gBattleScriptCmd_00,
        Fragment62_Byte2C,
        gBattleScript_NullParam,
        gBattleScript_NullParam2,
    },
    {
        gBattleScriptCmd_00,
        gBattleScriptCmd_00,
        Fragment62_Byte2C,
        gBattleScript_NullParam,
        gBattleScript_NullParam2,
    },
    {
        gBattleScriptCmd_00,
        gBattleScriptCmd_00,
        Fragment62_Byte0E,
        gBattleScript_NullParam,
        gBattleScript_NullParam2,
    },
    {
        gBattleScriptCmd_00,
        gBattleScriptCmd_00,
        Fragment62_Byte23,
        gBattleScript_NullParam,
        gBattleScript_NullParam2,
    },
    {
        gBattleScriptCmd_0F,
        gBattleScriptCmd_00,
        Fragment62_Bytes50_4C,
        gBattleScript_NullParam8,
        gBattleScript_NullParam2,
    },
    {
        gBattleScriptCmd_00,
        gBattleScriptCmd_00,
        Fragment62_Bytes0D_0E,
        gBattleScript_NullParam,
        gBattleScriptCmd_17,
    },
    {
        gBattleScriptCmd_38_Alt,
        gBattleScriptCmd_00,
        Fragment62_Byte36,
        gBattleScript_NullParam6,
        gBattleScript_NullParam2,
    },
    {
        gBattleScriptCmd_29_Alt,
        gBattleScriptCmd_00,
        Fragment62_Byte2A,
        gBattleScript_AnimAttack,
        gBattleScript_NullParam2,
    },
    {
        gBattleScriptCmd_49,
        gBattleScriptCmd_00,
        Fragment62_Byte2B,
        gBattleScript_NullParam11,
        gBattleScript_NullParam2,
    },
    {
        gBattleScriptCmd_0D,
        gBattleScriptCmd_00,
        Fragment62_Byte05,
        gBattleScript_NullParam7,
        gBattleScript_NullParam,
    },
    {
        gBattleScriptCmd_47,
        gBattleScriptCmd_00,
        Fragment62_Byte29,
        gBattleScriptCmd_08,
        gBattleScript_NullParam2,
    },
    {
        gBattleScriptCmd_6F,
        gBattleScriptCmd_00,
        Fragment62_Byte53,
        gBattleScriptCmd_08,
        gBattleScript_NullParam2,
    },
    {
        gBattleScriptCmd_0A,
        gBattleScriptCmd_48,
        Fragment62_Byte03,
        gBattleScriptCmd_09,
        gBattleScriptCmd_0B_0E,
    },
    {
        gBattleScriptCmd_44,
        gBattleScriptCmd_00,
        gBattleScript_NullParam3,
        gBattleScriptCmd_2E,
        gBattleScript_NullParam,
    },
    {
        gBattleScriptCmd_3D,
        gBattleScriptCmd_00,
        Fragment62_Byte1E,
        gBattleScript_NullParam7,
        gBattleScript_NullParam,
    },
    {
        gBattleScriptCmd_0A,
        gBattleScriptCmd_00,
        Fragment62_Byte2F,
        gBattleScript_Param09,
        gBattleScript_NullParam2,
    },
    {
        gBattleScriptCmd_00,
        gBattleScriptCmd_00,
        Fragment62_Bytes57_23,
        gBattleScript_Param0A,
        gBattleScript_NullParam2,
    },
    {
        gBattleScriptCmd_0A,
        gBattleScriptCmd_00,
        gBattleScript_NullParam3,
        gBattleScript_Param09,
        gBattleScript_NullParam,
    },
    {
        gBattleScriptCmd_00,
        gBattleScriptCmd_28_Alt,
        Fragment62_Bytes4F_2D,
        D_843868AC,
        gBattleScript_NullParam2,
    },
    {
        gBattleScriptCmd_13_14,
        gBattleScriptCmd_00,
        Fragment62_Byte09,
        gBattleScript_NullParam,
        gBattleScript_NullParam,
    },
    {
        gBattleScriptCmd_00,
        gBattleScriptCmd_00,
        Fragment62_Byte2D,
        gBattleScript_NullParam,
        gBattleScript_NullParam2,
    },
    {
        gBattleScriptCmd_75,
        gBattleScriptCmd_00,
        Fragment62_Byte55,
        gBattleScript_NullParam7,
        gBattleScript_Param0A,
    },
    {
        gBattleScriptCmd_00,
        gBattleScriptCmd_00,
        Fragment62_Bytes4F_27,
        gBattleScript_NullParam,
        gBattleScript_NullParam2,
    },
    {
        gBattleScriptCmd_00,
        gBattleScriptCmd_00,
        Fragment62_Byte23,
        gBattleScript_NullParam,
        gBattleScript_NullParam2,
    },
    {
        gBattleScriptCmd_02,
        gBattleScriptCmd_00,
        Fragment62_Bytes50_4C,
        gBattleScript_NullParam8,
        gBattleScript_NullParam2,
    },
    {
        gBattleScriptCmd_00,
        gBattleScriptCmd_00,
        Fragment62_Byte2C,
        gBattleScript_NullParam,
        gBattleScript_NullParam2,
    },
    {
        gBattleScriptCmd_00,
        gBattleScriptCmd_00,
        Fragment62_Byte2C,
        gBattleScript_NullParam,
        gBattleScript_NullParam2,
    },
    {
        gBattleScriptCmd_1F,
        gBattleScriptCmd_00,
        Fragment62_Byte37,
        gBattleScript_Param16,
        gBattleScript_NullParam2,
    },
    {
        gBattleScriptCmd_00,
        gBattleScriptCmd_00,
        Fragment62_Byte0E,
        gBattleScript_NullParam,
        gBattleScript_NullParam2,
    },
    {
        gBattleScriptCmd_77,
        gBattleScriptCmd_00,
        Fragment62_Byte25,
        gBattleScript_Param06,
        gBattleScript_NullParam2,
    },
    {
        gBattleScriptCmd_76,
        gBattleScriptCmd_00,
        Fragment62_Byte2F,
        gBattleScript_Param06,
        gBattleScript_NullParam2,
    },
    {
        gBattleScriptCmd_79,
        gBattleScriptCmd_00,
        Fragment62_Bytes54_25,
        gBattleScript_Param06,
        gBattleScript_NullParam2,
    },
    {
        gBattleScriptCmd_00,
        gBattleScriptCmd_00,
        Fragment62_Byte2C,
        gBattleScript_NullParam,
        gBattleScript_NullParam2,
    },
    {
        gBattleScriptCmd_74,
        gBattleScriptCmd_00,
        Fragment62_Bytes4F_2D,
        gBattleScript_NullParam,
        gBattleScript_NullParam2,
    },
    {
        gBattleScriptCmd_13_14,
        gBattleScriptCmd_00,
        Fragment62_Byte09,
        gBattleScript_NullParam,
        gBattleScript_NullParam,
    },
    {
        gBattleScriptCmd_73,
        gBattleScriptCmd_00,
        Fragment62_Byte2C,
        gBattleScriptCmd_32,
        gBattleScript_NullParam2,
    },
    {
        gBattleScriptCmd_72,
        gBattleScriptCmd_00,
        Fragment62_Byte2D,
        gBattleScript_NullParam,
        gBattleScript_NullParam2,
    },
    {
        gBattleScriptCmd_73,
        gBattleScriptCmd_00,
        Fragment62_Byte2D,
        gBattleScriptCmd_32,
        gBattleScript_NullParam2,
    },
    {
        gBattleScriptCmd_00,
        gBattleScriptCmd_00,
        gBattleScript_NullParam3,
        gBattleScript_NullParam,
        gBattleScript_NullParam,
    },
    {
        gBattleScriptCmd_43,
        gBattleScriptCmd_00,
        Fragment62_Byte26,
        gBattleScript_Param06,
        gBattleScript_NullParam2,
    },
    {
        gBattleScriptCmd_43,
        gBattleScriptCmd_00,
        Fragment62_Byte26,
        gBattleScript_Param06,
        gBattleScript_NullParam2,
    },
    {
        gBattleScriptCmd_43,
        gBattleScriptCmd_00,
        Fragment62_Byte25,
        gBattleScript_Param06,
        gBattleScript_NullParam2,
    },
    {
        gBattleScriptCmd_53,
        gBattleScriptCmd_00,
        gBattleScript_NullParam3,
        gBattleScriptCmd_30,
        gBattleScript_NullParam,
    },
    {
        gBattleScriptCmd_4A,
        gBattleScriptCmd_00,
        Fragment62_Byte29,
        gBattleScriptCmd_08,
        gBattleScript_NullParam2,
    },
    {
        gBattleScriptCmd_00,
        gBattleScriptCmd_00,
        gBattleScript_NullParam3,
        gBattleScript_NullParam,
        gBattleScript_NullParam,
    },
    {
        gBattleScriptCmd_00,
        gBattleScriptCmd_00,
        gBattleScript_NullParam3,
        gBattleScript_NullParam,
        gBattleScript_NullParam,
    },
    {
        gBattleScriptCmd_2B_Alt,
        gBattleScriptCmd_00,
        gBattleScript_NullParam3,
        gBattleScript_AnimHit,
        gBattleScript_NullParam,
    },
    {
        gBattleScriptCmd_2C_Alt2,
        gBattleScriptCmd_00,
        gBattleScript_NullParam3,
        gBattleScript_AnimMiss,
        gBattleScript_NullParam,
    },
    {
        gBattleScriptJump_2D,
        gBattleScriptCmd_00,
        Fragment62_Byte23,
        gBattleScript_AnimFaint,
        gBattleScript_NullParam2,
    },
    {
        gBattleScriptCmd_62,
        gBattleScriptCmd_00,
        Fragment62_Byte21,
        gBattleScript_NullParam,
        gBattleScript_NullParam,
    },
    {
        gBattleScriptCmd_11,
        gBattleScriptCmd_00,
        Fragment62_Byte07b,
        gBattleScript_NullParam5,
        gBattleScript_NullParam,
    },
    {
        gBattleScriptCmd_16,
        gBattleScriptCmd_00,
        Fragment62_Bytes38_4D,
        gBattleScript_NullParam6,
        gBattleScript_NullParam2,
    },
    {
        gBattleScriptCmd_4D,
        gBattleScriptCmd_00,
        Fragment62_Byte16,
        gBattleScript_NullParam6,
        gBattleScript_NullParam2,
    },
    {
        gBattleScriptCmd_35_05,
        gBattleScriptCmd_00,
        gBattleScript_NullParam3,
        gBattleScriptCmd_14,
        gBattleScript_NullParam,
    },
    {
        gBattleScriptCmd_06,
        gBattleScriptCmd_00,
        Fragment62_Byte02,
        gBattleScript_NullParam8,
        gBattleScript_NullParam5,
    },
    {
        gBattleScriptCmd_3A_Alt,
        gBattleScriptCmd_00,
        Fragment62_Bytes1B_1C,
        gBattleScript_NullParam8,
        gBattleScript_NullParam5,
    },
    {
        gBattleScriptJump_24,
        gBattleScriptCmd_00,
        Fragment62_Byte10,
        gBattleScript_Param1A,
        gBattleScript_NullParam8,
    },
    {
        gBattleScriptJump_2F,
        gBattleScriptCmd_00,
        Fragment62_Byte43,
        gBattleScriptCmd_29,
        gBattleScript_NullParam,
    },
    {
        gBattleScriptCmd_22,
        gBattleScriptCmd_00,
        Fragment62_Byte17,
        gBattleScript_Param19,
        gBattleScript_NullParam8,
    },
    {
        gBattleScriptCmd_66_04_05,
        gBattleScriptCmd_00,
        Fragment62_Byte44,
        gBattleScript_NullParam,
        gBattleScriptCmd_29,
    },
    {
        gBattleScriptJump_78,
        gBattleScriptCmd_00,
        Fragment62_Byte35,
        gBattleScript_NullParam,
        gBattleScriptCmd_29,
    },
    {
        gBattleScriptJump_1A,
        gBattleScriptCmd_00,
        Fragment62_Bytes45_0E_04,
        gBattleScript_NullParam,
        gBattleScriptCmd_29,
    },
    {
        gBattleScriptJump_27,
        gBattleScriptCmd_00,
        Fragment62_Byte46,
        gBattleScript_Param27,
        gBattleScriptCmd_29,
    },
    {
        gBattleScriptCmd_76,
        gBattleScriptCmd_00,
        Fragment62_Byte25,
        gBattleScript_Param06,
        gBattleScript_NullParam2,
    },
    {
        gBattleScriptCmd_71,
        gBattleScriptCmd_00,
        Fragment62_Bytes4D_0E,
        gBattleScript_Param06,
        gBattleScript_NullParam2,
    },
    {
        gBattleScriptCmd_6C,
        gBattleScriptCmd_00,
        Fragment62_Byte2E,
        gBattleScript_NullParam,
        gBattleScript_NullParam2,
    },
    {
        gBattleScriptCmd_00,
        gBattleScriptCmd_00,
        Fragment62_Byte24,
        gBattleScript_NullParam,
        gBattleScript_NullParam2,
    },
    {
        gBattleScriptCmd_00,
        gBattleScriptCmd_00,
        Fragment62_Byte2C,
        gBattleScript_NullParam,
        gBattleScript_NullParam2,
    },
    {
        gBattleScriptCmd_4E,
        gBattleScriptCmd_00,
        Fragment62_Bytes4F_2D,
        gBattleScript_NullParam,
        gBattleScript_NullParam2,
    },
    {
        gBattleScriptCmd_4B,
        gBattleScriptCmd_00,
        Fragment62_Byte32,
        gBattleScriptCmd_46,
        gBattleScript_NullParam,
    },
    {
        gBattleScriptCmd_18_Alt,
        gBattleScriptCmd_00,
        Fragment62_Byte15,
        gBattleScript_Param13,
        gBattleScript_NullParam4,
    },
    {
        gBattleScriptCmd_18_Alt,
        gBattleScriptCmd_00,
        Fragment62_Byte15,
        gBattleScript_Param13,
        gBattleScript_NullParam4,
    },
    {
        gBattleScriptCmd_08_09,
        gBattleScriptCmd_00,
        Fragment62_Byte1F,
        gBattleScript_Param05,
        gBattleScript_NullParam,
    },
    {
        gBattleScriptCmd_6D,
        gBattleScriptCmd_00,
        gBattleScript_NullParam3,
        gBattleScript_NullParam,
        gBattleScript_NullParam,
    },
    {
        gBattleScriptCmd_66_0B_0C,
        gBattleScriptCmd_00,
        Fragment62_Byte04,
        gBattleScript_Param0A,
        gBattleScript_NullParam2,
    },
    {
        gBattleScriptJump_46,
        gBattleScriptCmd_69,
        Fragment62_Byte47,
        gBattleScriptCmd_15,
        gBattleScriptCmd_29,
    },
    {
        gBattleScriptCmd_41,
        gBattleScriptCmd_00,
        Fragment62_Bytes12_13_14,
        gBattleScript_NullParam12,
        gBattleScript_NullParam2,
    },
    {
        gBattleScriptCmd_41,
        gBattleScriptCmd_00,
        Fragment62_Bytes12_13_14,
        gBattleScript_NullParam12,
        gBattleScript_NullParam2,
    },
    {
        gBattleScriptCmd_41,
        gBattleScriptCmd_00,
        Fragment62_Bytes12_13_14,
        gBattleScript_NullParam12,
        gBattleScript_NullParam2,
    },
    {
        gBattleScriptJump_39,
        gBattleScriptCmd_00,
        Fragment62_Byte1A,
        gBattleScript_Param0A,
        gBattleScript_NullParam2,
    },
    {
        gBattleScriptCmd_21,
        gBattleScriptCmd_00,
        Fragment62_Byte20,
        gBattleScript_NullParam,
        gBattleScript_NullParam,
    },
    {
        gBattleScriptCmd_23,
        gBattleScriptCmd_00,
        Fragment62_Byte0F,
        gBattleScript_NullParam6,
        gBattleScript_NullParam2,
    },
    {
        gBattleScriptCmd_54,
        gBattleScriptCmd_00,
        Fragment62_Byte1D,
        gBattleScript_NullParam10,
        gBattleScript_NullParam2,
    },
    {
        gBattleScriptTable_A98,
        gBattleScriptCmd_00,
        Fragment62_Byte08,
        gBattleScript_NullParam11,
        gBattleScript_NullParam,
    },
    {
        gBattleScriptCmd_12,
        gBattleScriptCmd_00,
        Fragment62_Byte08,
        gBattleScript_NullParam11,
        gBattleScript_NullParam,
    },
    {
        gBattleScriptCmd_26,
        gBattleScriptCmd_00,
        Fragment62_Byte11,
        gBattleScriptTable_A4,
        gBattleScript_NullParam,
    },
    {
        gBattleScriptCmd_12,
        gBattleScriptCmd_00,
        Fragment62_Byte48,
        gBattleScript_NullParam11,
        gBattleScript_NullParam,
    },
    {
        gBattleScriptCmd_3F,
        gBattleScriptCmd_00,
        Fragment62_Bytes0A_0B_0C_0D,
        gBattleScript_NullParam,
        gBattleScriptCmd_46,
    },
    {
        gBattleScriptCmd_25,
        gBattleScriptCmd_00,
        Fragment62_Byte4B,
        gBattleScript_NullParam9,
        gBattleScript_NullParam2,
    },
    {
        gBattleScriptCmd_25,
        gBattleScriptCmd_00,
        Fragment62_Byte3A,
        gBattleScript_NullParam9,
        gBattleScript_NullParam2,
    },
    {
        gBattleScriptTable_A50,
        gBattleScriptCmd_00,
        Fragment62_Bytes4E_4F,
        gBattleScriptCmd_28,
        gBattleScript_NullParam2,
    },
    {
        gBattleScriptCmd_11,
        gBattleScriptCmd_00,
        Fragment62_Byte07,
        gBattleScript_NullParam5,
        gBattleScript_NullParam,
    },
    {
        gBattleScriptCmd_6B,
        gBattleScriptCmd_00,
        Fragment62_Byte49,
        gBattleScript_NullParam4,
        gBattleScript_NullParam2,
    },
    {
        gBattleScriptCmd_6A,
        gBattleScriptCmd_00,
        Fragment62_Byte4A,
        gBattleScript_NullParam4,
        gBattleScript_NullParam2,
    },
    {
        gBattleScriptJump_2A,
        gBattleScriptCmd_00,
        gBattleScript_NullParam3,
        gBattleScriptTable_B4,
        gBattleScript_NullParam,
    },
    {
        gBattleScriptCmd_60,
        gBattleScriptCmd_00,
        gBattleScript_NullParam3,
        gBattleScriptCmd_37,
        gBattleScript_NullParam,
    },
    {
        gBattleScriptCmd_1B,
        gBattleScriptCmd_00,
        gBattleScript_NullParam3,
        gBattleScript_NullParam,
        gBattleScript_NullParam,
    },
    {
        gBattleScriptCmd_5A,
        gBattleScriptCmd_00,
        Fragment62_Byte2C,
        gBattleScriptCmd_32,
        gBattleScript_NullParam2,
    },
    {
        gBattleScriptCmd_55,
        gBattleScriptCmd_00,
        Fragment62_Byte2C,
        gBattleScript_NullParam4,
        gBattleScript_NullParam2,
    },
    {
        gBattleScriptCmd_56,
        gBattleScriptCmd_00,
        gBattleScript_NullParam3,
        gBattleScriptCmd_1E,
        gBattleScript_NullParam,
    },
    {
        gBattleScriptCmd_61,
        gBattleScriptCmd_00,
        Fragment62_Bytes3F_23_33,
        gBattleScriptCmd_38,
        gBattleScript_NullParam2,
    },
    {
        gBattleScriptTable_9F0,
        gBattleScriptCmd_00,
        gBattleScript_NullParam3,
        gBattleScript_NullParam,
        gBattleScript_NullParam,
    },
    {
        gBattleScriptJump_2A,
        gBattleScriptCmd_00,
        gBattleScript_NullParam3,
        gBattleScriptTable_B4,
        gBattleScript_NullParam,
    },
    {
        gBattleScriptCmd_1B,
        gBattleScriptCmd_00,
        gBattleScript_NullParam3,
        gBattleScript_NullParam,
        gBattleScript_NullParam,
    },
    {
        gBattleScriptCmd_6E,
        gBattleScriptCmd_00,
        gBattleScript_NullParam3,
        gBattleScript_NullParam,
        gBattleScript_NullParam,
    },
    {
        gBattleScriptTable_A74,
        gBattleScriptCmd_00,
        gBattleScript_NullParam3,
        gBattleScript_NullParam,
        gBattleScript_NullParam,
    },
    {
        gBattleScriptCmd_00,
        gBattleScriptCmd_00,
        gBattleScript_NullParam3,
        gBattleScript_NullParam,
        gBattleScript_NullParam,
    },
    {
        gBattleScriptCmd_1C,
        gBattleScriptCmd_00,
        gBattleScript_NullParam3,
        gBattleScriptTable_84,
        gBattleScript_NullParam2,
    },
    {
        gBattleScriptCmd_5D,
        gBattleScriptCmd_00,
        Fragment62_Byte3C,
        gBattleScriptCmd_10,
        gBattleScript_NullParam2,
    },
    {
        gBattleScriptCmd_5B,
        gBattleScriptCmd_00,
        gBattleScript_NullParam3,
        gBattleScriptCmd_33,
        gBattleScript_NullParam,
    },
    {
        gBattleScriptCmd_57,
        gBattleScriptCmd_00,
        gBattleScript_NullParam3,
        gBattleScriptCmd_31,
        gBattleScript_NullParam2,
    },
    {
        gBattleScriptCmd_0E,
        gBattleScriptCmd_00,
        gBattleScript_NullParam3,
        gBattleScriptTable_60,
        gBattleScript_NullParam,
    },
    {
        gBattleScriptCmd_0E,
        gBattleScriptCmd_00,
        gBattleScript_NullParam3,
        gBattleScriptTable_60,
        gBattleScript_NullParam,
    },
    {
        gBattleScriptTable_A7C,
        gBattleScriptCmd_00,
        gBattleScript_NullParam3,
        gBattleScriptTable_904,
        gBattleScript_NullParam,
    },
    {
        gBattleScriptTable_A80,
        gBattleScriptCmd_00,
        gBattleScript_NullParam3,
        gBattleScriptCmd_0C,
        gBattleScript_NullParam,
    },
    {
        gBattleScriptCmd_03,
        gBattleScriptCmd_00,
        gBattleScript_NullParam3,
        gBattleScript_NullParam4,
        gBattleScript_NullParam,
    },
    {
        gBattleScriptCmd_55,
        gBattleScriptCmd_00,
        Fragment62_Byte2C,
        gBattleScript_NullParam4,
        gBattleScript_NullParam2,
    },
    {
        gBattleScriptCmd_20,
        gBattleScriptCmd_00,
        Fragment62_Byte18,
        gBattleScript_NullParam,
        gBattleScript_NullParam,
    },
    {
        gBattleScriptCmd_00,
        gBattleScriptCmd_00,
        Fragment62_Byte18,
        gBattleScript_NullParam,
        gBattleScript_NullParam,
    },
    {
        gBattleScriptTable_A44,
        gBattleScriptCmd_00,
        Fragment62_Byte51,
        gBattleScriptTable_D0,
        gBattleScript_NullParam6,
    },
    {
        gBattleScriptCmd_40,
        gBattleScriptCmd_00,
        Fragment62_Byte28,
        gBattleScriptCmd_07,
        gBattleScript_NullParam6,
    },
    {
        gBattleScriptCmd_5C,
        gBattleScriptCmd_00,
        Fragment62_Byte07,
        gBattleScriptCmd_34,
        gBattleScript_NullParam5,
    },
    {
        gBattleScriptCmd_4C,
        gBattleScriptCmd_00,
        Fragment62_Bytes12_13_14,
        gBattleScriptTable_84,
        gBattleScript_NullParam2,
    },
    {
        gBattleScriptCmd_11,
        gBattleScriptCmd_00,
        Fragment62_Byte07,
        gBattleScript_NullParam5,
        gBattleScript_NullParam,
    },
    {
        gBattleScriptCmd_4F,
        gBattleScriptCmd_00,
        Fragment62_Byte0E,
        gBattleScriptCmd_2F,
        gBattleScript_NullParam2,
    },
    {
        gBattleScriptCmd_4D,
        gBattleScriptCmd_00,
        Fragment62_Byte3B,
        gBattleScript_NullParam6,
        gBattleScript_NullParam2,
    },
    {
        gBattleScriptCmd_63,
        gBattleScriptCmd_00,
        Fragment62_Byte40,
        gBattleScriptCmd_39,
        gBattleScript_NullParam8,
    },
    {
        gBattleScriptCmd_47,
        gBattleScriptCmd_00,
        Fragment62_Byte29,
        gBattleScriptCmd_08,
        gBattleScript_NullParam2,
    },
    {
        gBattleScriptJump_07,
        gBattleScriptCmd_00,
        Fragment62_Byte34,
        gBattleScriptTable_48,
        gBattleScript_NullParam2,
    },
    {
        gBattleScriptCmd_70,
        gBattleScriptCmd_00,
        Fragment62_Bytes50_4C,
        gBattleScriptCmd_32,
        gBattleScript_NullParam2,
    },
    {
        gBattleScriptCmd_3E,
        gBattleScriptCmd_00,
        Fragment62_Byte25,
        gBattleScript_Param06,
        gBattleScript_NullParam2,
    },
    {
        gBattleScriptCmd_13_14,
        gBattleScriptCmd_00,
        Fragment62_Byte09b,
        gBattleScript_NullParam,
        gBattleScript_NullParam,
    },
    {
        gBattleScriptTable_A88,
        gBattleScriptCmd_00,
        gBattleScript_NullParam3,
        gBattleScript_NullParam,
        gBattleScript_NullParam,
    },
    {
        gBattleScriptTable_A5C,
        gBattleScriptCmd_2C_Alt2,
        gBattleScript_NullParam3,
        gBattleScriptCmd_2A,
        gBattleScript_AnimMiss,
    },
    {
        gBattleScriptCmd_42,
        gBattleScriptCmd_00,
        gBattleScript_NullParam3,
        gBattleScriptCmd_07,
        gBattleScript_NullParam,
    },
    {
        gBattleScriptCmd_5A,
        gBattleScriptCmd_00,
        Fragment62_Byte2C,
        gBattleScriptCmd_32,
        gBattleScript_NullParam2,
    },
    {
        gBattleScriptCmd_53,
        gBattleScriptCmd_00,
        gBattleScript_NullParam3,
        gBattleScriptCmd_30,
        gBattleScript_NullParam,
    },
    {
        gBattleScriptCmd_5F,
        gBattleScriptCmd_00,
        Fragment62_Byte3E,
        gBattleScriptCmd_36,
        gBattleScript_NullParam,
    },
    {
        gBattleScriptCmd_1C,
        gBattleScriptCmd_00,
        Fragment62_Bytes12_13_14,
        gBattleScriptTable_84,
        gBattleScript_NullParam2,
    },
    {
        gBattleScriptCmd_65,
        gBattleScriptCmd_00,
        Fragment62_Byte41,
        gBattleScriptCmd_3B,
        gBattleScript_NullParam2,
    },
    {
        gBattleScriptCmd_18_Alt,
        gBattleScriptCmd_00,
        Fragment62_Byte15,
        gBattleScript_Param13,
        gBattleScript_NullParam4,
    },
    {
        gBattleScriptCmd_5E,
        gBattleScriptCmd_00,
        Fragment62_Byte3D,
        gBattleScriptCmd_35,
        gBattleScript_NullParam,
    },
    {
        gBattleScriptCmd_67,
        gBattleScriptCmd_68,
        Fragment62_Byte19,
        gBattleScriptCmd_2B,
        gBattleScriptCmd_29,
    },
    {
        gBattleScriptTable_B60,
        gBattleScriptCmd_00,
        gBattleScript_NullParam3,
        gBattleScript_NullParam,
        gBattleScript_NullParam,
    },
    {
        gBattleScriptTable_A3C,
        gBattleScriptCmd_00,
        Fragment62_Byte22,
        gBattleScript_NullParam8,
        gBattleScript_NullParam2,
    },
    {
        gBattleScriptCmd_00,
        gBattleScriptCmd_00,
        Fragment62_Bytes06_0E,
        gBattleScript_NullParam,
        gBattleScriptCmd_18,
    },
    {
        gBattleScriptCmd_41,
        gBattleScriptCmd_00,
        Fragment62_Bytes12_13_14,
        gBattleScript_NullParam12,
        gBattleScript_NullParam2,
    },
    {
        gBattleScriptTable_9BC,
        gBattleScriptCmd_00,
        Fragment62_Byte39,
        gBattleScript_NullParam,
        gBattleScript_NullParam2,
    },
    {
        gBattleScriptTable_A40,
        gBattleScriptCmd_00,
        Fragment62_Byte42,
        gBattleScript_NullParam4,
        gBattleScript_NullParam2,
    },
    {
        gBattleScriptCmd_00,
        gBattleScriptCmd_00,
        gBattleScript_NullParam3,
        gBattleScript_NullParam,
        gBattleScript_NullParam,
    },
    {
        gBattleScriptCmd_51,
        gBattleScriptCmd_00,
        gBattleScript_NullParam3,
        gBattleScript_NullParam5,
        gBattleScript_NullParam2,
    },
    {
        gBattleScriptCmd_64,
        gBattleScriptCmd_00,
        Fragment62_Bytes2D_1E,
        gBattleScriptCmd_3A,
        gBattleScript_NullParam2,
    },
    {
        gBattleScriptCmd_52,
        gBattleScriptCmd_00,
        Fragment62_Byte52,
        gBattleScriptTable_D0,
        gBattleScript_NullParam6,
    },
    {
        gBattleScriptCmd_7C,
        gBattleScriptCmd_7B,
        Fragment62_Entry58_06,
        gBattleScript_NullParam7,
        gBattleScript_NullParam,
    },
    {
        gBattleScriptCmd_50,
        gBattleScriptCmd_00,
        Fragment62_Byte2C,
        gBattleScriptCmd_2F,
        gBattleScript_NullParam2,
    },
    {
        gBattleScriptCmd_00,
        gBattleScriptCmd_00,
        gBattleScript_NullParam3,
        gBattleScript_NullParam,
        gBattleScript_NullParam,
    },
    {
        gBattleScriptCmd_3F,
        gBattleScriptCmd_00,
        Fragment62_Bytes0A_0B_0C_0D,
        gBattleScript_NullParam,
        gBattleScriptCmd_46,
    },
    {
        gBattleScriptCmd_4A,
        gBattleScriptCmd_00,
        Fragment62_Byte29,
        gBattleScriptCmd_08,
        gBattleScript_NullParam2,
    },
    {
        gBattleScriptCmd_58,
        gBattleScriptCmd_00,
        gBattleScript_NullParam3,
        gBattleScriptCmd_31,
        gBattleScript_NullParam2,
    },
    {
        gBattleScriptTable_9F0,
        gBattleScriptCmd_00,
        gBattleScript_NullParam3,
        gBattleScript_NullParam,
        gBattleScript_NullParam,
    },
    {
        gBattleScriptJump_4E,
        gBattleScriptCmd_00,
        Fragment62_Byte56,
        gBattleScriptTable_918,
        gBattleScript_NullParam2,
    },
    {
        gBattleScriptCmd_4A,
        gBattleScriptCmd_00,
        Fragment62_Byte29,
        gBattleScriptCmd_08,
        gBattleScript_NullParam2,
    },
    {
        gBattleScriptCmd_0D,
        gBattleScriptCmd_00,
        Fragment62_Byte05,
        gBattleScript_NullParam7,
        gBattleScript_NullParam,
    },
    {
        gBattleScriptCmd_59,
        gBattleScriptCmd_00,
        gBattleScript_NullParam3,
        gBattleScript_NullParam,
        gBattleScript_NullParam,
    },
    {
        gBattleScriptCmd_72,
        gBattleScriptCmd_00,
        Fragment62_Byte2C,
        gBattleScript_NullParam,
        gBattleScript_NullParam2,
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
    ProcessAudioInfo(BattleScene_GetParticipantDisplayPlayerNumber(arg0), &arg0->animationState.unk_38);
}

void BattleAnim_PlaySpeciesReactionSound(BattlePlayerEntity* arg0, PokemonAudioInfo* arg1, s32 arg2) {
    Effect_TriggerMoveVisual(arg1->unk_5A, arg0->unk_000.unk_01A, arg2);
    HandleMoveEvent(arg1, arg1->unk_5A, arg0->unk_000.unk_01A, arg2);
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

    sp20[ptr1->pokemonAnimation->unk_08[0]->unk_001] = 1;
    if (ptr1->pokemonAnimation->unk_01 == 2) {
        sp20[ptr1->pokemonAnimation->unk_08[1]->unk_001] = 1;
    }
    sp20[ptr2->pokemonAnimation->unk_08[0]->unk_001] = 2;
    if (ptr2->pokemonAnimation->unk_01 == 2) {
        sp20[ptr2->pokemonAnimation->unk_08[1]->unk_001] = 2;
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

    sp24[ptr1->pokemonAnimation->unk_08[0]->unk_001] = BattleScene_GetRosterTeamSize(ptr1->pokemonAnimation->unk_08[0]);
    if (ptr1->pokemonAnimation->unk_01 == 2) {
        sp24[ptr1->pokemonAnimation->unk_08[1]->unk_001] = BattleScene_GetRosterTeamSize(ptr1->pokemonAnimation->unk_08[1]);
    }

    sp24[ptr2->pokemonAnimation->unk_08[0]->unk_001] = BattleScene_GetRosterTeamSize(ptr2->pokemonAnimation->unk_08[0]);
    if (ptr2->pokemonAnimation->unk_01 == 2) {
        sp24[ptr2->pokemonAnimation->unk_08[1]->unk_001] = BattleScene_GetRosterTeamSize(ptr2->pokemonAnimation->unk_08[1]);
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
    gParticleTexture_Default = gParticleEffectPrimaryId;
    gStateFunctionTable[arg0]();
    if (gParticleEffectSecondaryId != 0xFF) {
        gParticleTexture_Default = gParticleEffectSecondaryId;
        gStateFunctionTable[arg0]();
    }
}

void BattleAnim_RunEffectInitEnd(s16 arg0) {
    gParticleTexture_Default = gParticleEffectPrimaryId;
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

    gCurrentActionScriptType = arg1;

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
            BattleAnim_RegisterEffectSlot(gStateEnterCallbackTable[*sp2C], gStateExitCallbackTable[*sp2C]);
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
            BattleAnim_RegisterEffectSlot(gParticleEnterCallbackTable[*sp2C], gParticleExitCallbackTable[*sp2C]);
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
    return gCurrentActionScriptType;
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
    gParticleEffectEntityA = arg1;
    gParticleEffectData_42 = arg1;
    gParticleEffectEntityB = arg2;
}

void BattleAnim_QueueMoveEffectScriptA(s32 arg0, BattlePlayerEntity* arg1, BattlePlayerEntity* arg2, s16 arg3, s16 arg4) {
    BattleAnim_QueueMoveEffect(arg0, arg1, arg2, arg3, arg4);
}

void BattleAnim_QueueMoveEffectEnd(s32 arg0, BattlePlayerEntity* arg1, BattlePlayerEntity* arg2, s16 arg3, s16 arg4) {
    BattleAnim_QueueMoveEffect(arg0, arg1, arg2, arg3, arg4);
    BattleAnim_SetQueuedEffectList(2);
    gParticleEffectEntityA = arg2;
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
    gParticleEffectEntityA = arg1;
    gParticleEffectData_42 = arg1;
    gParticleEffectEntityB = arg1;
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
    gParticleEffectEntityA = arg1;
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
        gMessageBuffer[var_v0] = *temp_a1;
        temp_a1++;
        var_v0++;
    }

    temp_a1 = Fragment62_ComplexPtrTable[arg0][4];
    while (*temp_a1 != 0x3F) {
        gMessageBuffer[var_v0] = *temp_a1;
        temp_a1++;
        var_v0++;
    }

    gMessageBuffer[var_v0] = -1;
}

void BattleAnim_LoadMoveResourceList(BattlePokemon* arg0, s16 arg1) {
    if (arg1 != 0xFF) {
        BattleAnim_BuildResourceListForMove(arg1);
        arg0->unk_1D |= 0x80;
        arg0->unk_20 = gMessageBuffer;
        arg0->unk_24 = gMessageStringLists;
    }
}

void BattleAnim_LoadModeResourceList(BattlePokemon* arg0, s16 arg1) {
    s32 var_v0 = 0;
    u8* var_v1 = Fragment62_SubTablePtr2D[arg1][1];

    while (*var_v1 != 0x3F) {
        gMessageBuffer[var_v0] = *var_v1;
        var_v1++;
        var_v0++;
    }

    gMessageBuffer[var_v0] = -1;
    arg0->unk_20 = gMessageBuffer;
    arg0->unk_1D |= 0x80;
    arg0->unk_24 = gMessageStringLists;
}

void BattleAnim_RegisterAllAssetTables(void) {
    s32 i = 0;
    arg1_func_80019420* var_v0;
    arg1_func_80019420** var_s1 = gMessageStringLists;

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

    if (arg0->unk_040.unk_08 == 0) {
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
    BattleAnim_GetCameraLookAngles(&gParticleCameraInfo->unk_70, &gParticleCameraInfo->lookYaw);
    BattleAnim_GetCameraEyeAngles(&gParticleCameraInfo->eyePitch, &gParticleCameraInfo->unk_78);
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

    gParticleEffectEntityA = NULL;
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

void BattleAnim_GetCameraStoredAngles76(s16* arg0, s16* arg1) {
    *arg0 = gParticleCameraInfo->eyePitch;
    *arg1 = gParticleCameraInfo->unk_78;
}

void BattleAnim_GetCameraStoredYaw78(s16* arg0) {
    *arg0 = gParticleCameraInfo->unk_78;
}

void BattleAnim_GetCameraStoredAngles70(s16* arg0, s16* arg1) {
    *arg0 = gParticleCameraInfo->unk_70;
    *arg1 = gParticleCameraInfo->lookYaw;
}

void BattleAnim_GetCameraStoredYaw72(s16* arg0) {
    *arg0 = gParticleCameraInfo->lookYaw;
}
