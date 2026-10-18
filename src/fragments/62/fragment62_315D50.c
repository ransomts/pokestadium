#include "fragment62.h"
#include "src/17300.h"
#include "src/19840.h"
#include "src/1C720.h"
#include "src/373A0.h"
#include "src/3D140.h"
#include "src/485C0.h"
#include "src/49790.h"
#include "src/4BDC0.h"
#include "src/4F410.h"
#include "src/F420.h"
#include "src/math_util.h"

typedef struct unk_D_84392040 {
    /* 0x00 */ char unk00[0xC];
    /* 0x0C */ f32 unk_0C;
    /* 0x10 */ f32 unk_10;
    /* 0x14 */ char unk14[0x4];
} unk_D_84392040; // size = 0x18

s32 D_843902A0;
#include "prevent_bss_reordering.h"
s32 gPanelDrawCount;
s32 D_843902A8;
static s32 gCurrentActionScriptId;
static s32 gPendingActionScriptFlag0;
static s32 D_843902B4;
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
unk_BattlePlayerEntity* gParticleEffectEntityA;
unk_BattlePlayerEntity* gParticleEffectData_42;
unk_BattlePlayerEntity* gParticleEffectEntityB;
s32 gGameStateFlag;
s32 D_843902F8;
static s8 gStateCallbackSlot;
func_D_84390300 gCameraCallbackFuncs[8];
func_D_84390320 gCameraUpdateFuncs[8];
s32 D_84390340;
static f32 gWaterScale;
Vec3f gCameraLookAtPos;
static Vec3s gCameraAngles;
static Vec3f gCameraPosOffset;
static Vec3s gCameraRotOffset;
static Vec3s gCameraTargetOffset;
s16 gSavedPrimColorR;
s16 gSavedPrimColorG;
s16 gSavedPrimColorB;
s16 D_84390380;
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
static unk_D_84392040 gWaterAnimParams;
f32 D_84392058[26];

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

ParticleRenderSettings gParticleRenderSettingsTable[] = {
    {
        0x01,
        0x01,
        0x0000,
        func_8140C880,
        RenderBillboardQuadPrimColor,
        &gWaterTexture[4],
    },
    {
        0x00,
        0x01,
        0x0000,
        func_8140C930,
        RenderBillboardQuad,
        &gWaterTexture[5],
    },
    {
        0x00,
        0x01,
        0x0000,
        func_8140C9EC,
        RenderBillboardQuad64,
        &gWaterTexture[20],
    },
    {
        0x00,
        0x01,
        0x0000,
        func_8140C9EC,
        func_8140D1FC,
        &gWaterTexture[20],
    },
    {
        0x00,
        0x01,
        0x0000,
        func_8140C930,
        RenderBillboardQuad,
        &gWaterTexture[5],
    },
    {
        0x00,
        0x01,
        0x0000,
        func_8140C930,
        RenderBillboardQuadGradient,
        &gWaterTexture[5],
    },
    {
        0x00,
        0x01,
        0x0000,
        func_8140C9EC,
        func_8140D1FC,
        &gWaterTexture[20],
    },
    {
        0x00,
        0x01,
        0x0000,
        LoadTexture_CI4_32x64_ByIndex,
        RenderBillboardQuad64,
        &gWaterTexture[9],
    },
    {
        0x00,
        0x01,
        0x0000,
        LoadTexture_CI4_32x32,
        RenderBillboardQuadPrimColor,
        &gWaterTexture[3],
    },
    {
        0x00,
        0x01,
        0x0000,
        func_8140C880,
        RenderBillboardQuad,
        &gWaterTexture[23],
    },
    {
        0x00,
        0x01,
        0x0001,
        func_8140C8B8,
        RenderBillboardQuad,
        &gWaterTexture[14],
    },
    {
        0x00,
        0x01,
        0x0000,
        LoadTexture_IA8_32x32_ByIndex,
        RenderBillboardQuad,
        &gWaterTexture[17],
    },
    {
        0x00,
        0x01,
        0x0000,
        func_8140C880,
        RenderBillboardQuad,
        &gWaterTexture[14],
    },
    {
        0x00,
        0x01,
        0x0001,
        LoadTexture_CI4_24x24_ByIndex,
        RenderBillboardQuad24,
        &gWaterTexture[8],
    },
    {
        0x00,
        0x01,
        0x0000,
        LoadTexture_CI4_24x24_ByIndex,
        RenderBillboardQuad24,
        &gWaterTexture[8],
    },
    {
        0x00,
        0x01,
        0x0000,
        LoadTexture_CI4_24x24_ByIndex,
        RenderRotatedQuad24,
        &gWaterTexture[8],
    },
    {
        0x00,
        0x01,
        0x0000,
        func_8140CA90,
        RenderBillboardQuadTriple,
        &gWaterTexture[18],
    },
    {
        0x00,
        0x01,
        0x0001,
        LoadTexture_IA8_32x32_ByIndex,
        RenderBillboardQuad,
        &gWaterTexture[17],
    },
    {
        0x00,
        0x01,
        0x0000,
        LoadTexture_IA8_32x32_ByIndex,
        RenderBillboardQuad,
        &gWaterTexture[17],
    },
    {
        0x00,
        0x01,
        0x0000,
        func_8140C930,
        RenderBillboardQuad,
        &gWaterTexture[5],
    },
    {
        0x00,
        0x01,
        0x0000,
        func_8140CA90,
        RenderBillboardQuadTriple,
        &gWaterTexture[18],
    },
    {
        0x00,
        0x01,
        0x0000,
        func_8140C880,
        RenderBillboardQuad,
        &gWaterTexture[23],
    },
    {
        0x00,
        0x01,
        0x0000,
        func_8140C880,
        RenderBillboardQuad,
        &gWaterTexture[13],
    },
    {
        0x00,
        0x01,
        0x0000,
        func_8140C8F4,
        RenderBillboardQuad,
        &gWaterTexture[13],
    },
    {
        0x00,
        0x01,
        0x0000,
        func_8140CAC8,
        RenderBillboardQuadTriple,
        &gWaterTexture[18],
    },
    {
        0x00,
        0x01,
        0x0000,
        func_8140C8B8,
        RenderBillboardQuad,
        &gWaterTexture[23],
    },
    {
        0x00,
        0x01,
        0x0000,
        func_8140CA64,
        RenderRotatedQuadTriple,
        &gWaterTexture[11],
    },
    {
        0x00,
        0x01,
        0x0001,
        LoadTexture_IA8_32x32_ByIndex,
        RenderBillboardQuad,
        &gWaterTexture[82],
    },
    {
        0x00,
        0x01,
        0x0000,
        LoadTexture_CI4_32x32,
        RenderBillboardQuadRoll,
        &gWaterTexture[16],
    },
    {
        0x00,
        0x01,
        0x0001,
        LoadTexture_IA8_32x32,
        RenderBillboardQuad,
        &gWaterTexture[84],
    },
    {
        0x00,
        0x01,
        0x0001,
        LoadTexture_CI4_32x32,
        RenderBillboardQuad,
        &gWaterTexture[169],
    },
    {
        0x00,
        0x01,
        0x0001,
        LoadTexture_CI4_32x32,
        RenderBillboardQuad,
        &gWaterTexture[172],
    },
    {
        0x00,
        0x01,
        0x0000,
        LoadTexture_CI4_32x32,
        RenderBillboardQuad,
        &gWaterTexture[166],
    },
    {
        0x00,
        0x01,
        0x0000,
        LoadTexture_CI4_32x32,
        RenderBillboardQuad,
        &gWaterTexture[167],
    },
    {
        0x00,
        0x01,
        0x0001,
        LoadTexture_CI4_32x32_ByIndex,
        RenderBillboardQuad,
        &gWaterTexture[83],
    },
    {
        0x00,
        0x01,
        0x0001,
        LoadTexture_CI4_32x32_ByIndex,
        RenderBillboardQuad,
        &gWaterTexture[83],
    },
    {
        0x00,
        0x01,
        0x0001,
        LoadTexture_CI4_64x64_ByIndex,
        RenderBillboardQuadTriple,
        &gWaterTexture[89],
    },
    {
        0x00,
        0x01,
        0x0001,
        LoadTexture_IA8_32x32,
        RenderBillboardQuadRoll,
        &gWaterTexture[95],
    },
    {
        0x01,
        0x01,
        0x0000,
        LoadTexture_IA8_32x32,
        RenderPanelBackground,
        &gWaterTexture[95],
    },
    {
        0x00,
        0x01,
        0x0000,
        LoadTexture_IA8_32x32_ByIndex,
        RenderBillboardQuad,
        &gWaterTexture[2],
    },
    {
        0x00,
        0x01,
        0x0001,
        LoadTexture_IA8_32x32_ByIndex,
        RenderBillboardQuad,
        &gWaterTexture[100],
    },
    {
        0x00,
        0x01,
        0x0001,
        LoadTexture_CI4_32x32_ByIndex,
        RenderBillboardQuadNoise,
        &gWaterTexture[83],
    },
    {
        0x00,
        0x01,
        0x0000,
        LoadTexture_CI4_32x32_ByIndex,
        RenderBillboardQuadNoise,
        &gWaterTexture[83],
    },
    {
        0x00,
        0x01,
        0x0001,
        LoadTexture_CI4_32x32_ByIndex,
        RenderBillboardQuad,
        &gWaterTexture[101],
    },
    {
        0x00,
        0x01,
        0x0000,
        LoadTexture_CI4_32x32_ByIndex,
        RenderBillboardQuad,
        &gWaterTexture[83],
    },
    {
        0x00,
        0x01,
        0x0000,
        func_8140CB38,
        RenderGroundQuad,
        &gWaterTexture[63],
    },
    {
        0x00,
        0x01,
        0x0000,
        func_8140CB64,
        RenderGroundQuad,
        &gWaterTexture[112],
    },
    {
        0x00,
        0x01,
        0x0000,
        LoadTexture_CI4_32x32_ByIndex,
        RenderBillboardQuadOffsetY,
        &gWaterTexture[83],
    },
    {
        0x00,
        0x01,
        0x0000,
        LoadTexture_IA8_32x64_ByIndex,
        RenderBillboardQuad64OffsetY,
        &gWaterTexture[117],
    },
    {
        0x00,
        0x01,
        0x0001,
        LoadTexture_IA8_32x32_ByIndex,
        RenderBillboardQuad,
        &gWaterTexture[122],
    },
    {
        0x00,
        0x01,
        0x0000,
        LoadTexture_IA8_32x32_ByIndex,
        RenderBillboardQuad,
        &gWaterTexture[82],
    },
    {
        0x00,
        0x01,
        0x0000,
        LoadTexture_IA8_32x32,
        RenderBillboardQuadRoll,
        &gWaterTexture[95],
    },
    {
        0x00,
        0x01,
        0x0001,
        LoadTexture_IA8_32x32_ByIndex,
        RenderBillboardQuadRoll,
        &gWaterTexture[82],
    },
    {
        0x00,
        0x01,
        0x0000,
        LoadTexture_IA8_32x32_ByIndex,
        RenderBillboardQuadRoll,
        &gWaterTexture[82],
    },
    {
        0x00,
        0x01,
        0x0000,
        LoadTexture_CI4_32x32_ByIndex,
        RenderBillboardQuad,
        &gWaterTexture[83],
    },
    {
        0x00,
        0x01,
        0x0000,
        func_8140C8B8,
        RenderBillboardQuad,
        &gWaterTexture[14],
    },
    {
        0x00,
        0x01,
        0x0000,
        LoadTexture_IA8_32x32_ByIndex,
        RenderBillboardQuadGradient,
        &gWaterTexture[17],
    },
};

ParticleEffectData gParticleEffectData[] = {
    {
        0x00000001,
        &gParticleRenderSettingsTable[0],
    },
    {
        0x00000001,
        &gParticleRenderSettingsTable[1],
    },
    {
        0x00000001,
        &gParticleRenderSettingsTable[2],
    },
    {
        0x00000001,
        &gParticleRenderSettingsTable[3],
    },
    {
        0x00000001,
        &gParticleRenderSettingsTable[4],
    },
    {
        0x00000001,
        &gParticleRenderSettingsTable[7],
    },
    {
        0x00000003,
        func_84331094,
    },
    {
        0x00000001,
        &gParticleRenderSettingsTable[8],
    },
    {
        0x00000001,
        &gParticleRenderSettingsTable[9],
    },
    {
        0x00000001,
        &gParticleRenderSettingsTable[10],
    },
    {
        0x00000001,
        &gParticleRenderSettingsTable[55],
    },
    {
        0x00000001,
        &gParticleRenderSettingsTable[11],
    },
    {
        0x00000001,
        &gParticleRenderSettingsTable[12],
    },
    {
        0x00000001,
        &gParticleRenderSettingsTable[13],
    },
    {
        0x00000001,
        &gParticleRenderSettingsTable[14],
    },
    {
        0x00000003,
        RenderTimerDigits,
    },
    {
        0x00000003,
        RenderTimerDigitsAlt,
    },
    {
        0x00000003,
        func_84331314,
    },
    {
        0x00000003,
        RenderTimerNumber,
    },
    {
        0x00000003,
        func_8433157C,
    },
    {
        0x00000003,
        func_843316A8,
    },
    {
        0x00000001,
        &gParticleRenderSettingsTable[16],
    },
    {
        0x00000001,
        &gParticleRenderSettingsTable[22],
    },
    {
        0x00000001,
        &gParticleRenderSettingsTable[23],
    },
    {
        0x00000001,
        &gParticleRenderSettingsTable[17],
    },
    {
        0x00000001,
        &gParticleRenderSettingsTable[18],
    },
    {
        0x00000001,
        &gParticleRenderSettingsTable[56],
    },
    {
        0x00000001,
        &gParticleRenderSettingsTable[5],
    },
    {
        0x00000003,
        func_843317D4,
    },
    {
        0x00000003,
        func_843318F8,
    },
    {
        0x00000003,
        func_84331A1C,
    },
    {
        0x00000001,
        &gParticleRenderSettingsTable[19],
    },
    {
        0x00000001,
        &gParticleRenderSettingsTable[20],
    },
    {
        0x00000001,
        &gParticleRenderSettingsTable[24],
    },
    {
        0x00000001,
        &gParticleRenderSettingsTable[21],
    },
    {
        0x00000001,
        &gParticleRenderSettingsTable[25],
    },
    {
        0x00000001,
        &gParticleRenderSettingsTable[26],
    },
    {
        0x00000003,
        func_84331D60,
    },
    {
        0x00000003,
        func_84331B58,
    },
    {
        0x00000003,
        func_84331C34,
    },
    {
        0x00000003,
        func_84330AF0,
    },
    {
        0x00000003,
        func_84330B40,
    },
    {
        0x00000001,
        &gParticleRenderSettingsTable[15],
    },
    {
        0x00000003,
        func_84330C70,
    },
    {
        0x00000003,
        func_84330D64,
    },
    {
        0x00000003,
        func_84330E58,
    },
    {
        0x00000003,
        func_84330F4C,
    },
    {
        0x00000003,
        func_84330388,
    },
    {
        0x00000003,
        RenderItemIcon,
    },
    {
        0x00000003,
        RenderStatusBar,
    },
    {
        0x00000003,
        func_84330688,
    },
    {
        0x00000003,
        RenderMultiBlockIcon,
    },
    {
        0x00000001,
        &gParticleRenderSettingsTable[27],
    },
    {
        0x00000001,
        &gParticleRenderSettingsTable[6],
    },
    {
        0x00000001,
        &gParticleRenderSettingsTable[45],
    },
    {
        0x00000001,
        &gParticleRenderSettingsTable[28],
    },
    {
        0x00000001,
        &gParticleRenderSettingsTable[29],
    },
    {
        0x00000001,
        &gParticleRenderSettingsTable[30],
    },
    {
        0x00000001,
        &gParticleRenderSettingsTable[31],
    },
    {
        0x00000001,
        &gParticleRenderSettingsTable[32],
    },
    {
        0x00000001,
        &gParticleRenderSettingsTable[33],
    },
    {
        0x00000001,
        &gParticleRenderSettingsTable[34],
    },
    {
        0x00000001,
        &gParticleRenderSettingsTable[35],
    },
    {
        0x00000001,
        &gParticleRenderSettingsTable[54],
    },
    {
        0x00000001,
        &gParticleRenderSettingsTable[36],
    },
    {
        0x00000003,
        func_84330B18,
    },
    {
        0x00000001,
        &gParticleRenderSettingsTable[37],
    },
    {
        0x00000001,
        &gParticleRenderSettingsTable[38],
    },
    {
        0x00000001,
        &gParticleRenderSettingsTable[51],
    },
    {
        0x00000001,
        &gParticleRenderSettingsTable[39],
    },
    {
        0x00000001,
        &gParticleRenderSettingsTable[40],
    },
    {
        0x00000001,
        &gParticleRenderSettingsTable[41],
    },
    {
        0x00000001,
        &gParticleRenderSettingsTable[42],
    },
    {
        0x00000001,
        &gParticleRenderSettingsTable[43],
    },
    {
        0x00000001,
        &gParticleRenderSettingsTable[44],
    },
    {
        0x00000001,
        &gParticleRenderSettingsTable[46],
    },
    {
        0x00000001,
        &gParticleRenderSettingsTable[47],
    },
    {
        0x00000001,
        &gParticleRenderSettingsTable[48],
    },
    {
        0x00000003,
        RenderPanelWithIcon,
    },
    {
        0x00000003,
        RenderOverlayWithIcon,
    },
    {
        0x00000001,
        &gParticleRenderSettingsTable[49],
    },
    {
        0x00000001,
        &gParticleRenderSettingsTable[50],
    },
    {
        0x00000003,
        func_84330934,
    },
    {
        0x00000001,
        &gParticleRenderSettingsTable[52],
    },
    {
        0x00000001,
        &gParticleRenderSettingsTable[53],
    },
    {
        0x00000000,
        NULL,
    },
};

static func_D_84390320 gStateFunctionTable[] = {
    func_8432F998, ParticleEffect_RegisterDefault, SpawnLargeBurstIfNotActive, ParticleEffect_InitSmallExplosion, InitParticleEffectSet_Alt, func_8432F998, SpawnSmallGlowAndCustomEffect,
    ParticleEffect_SmallSetup, ParticleEffect_RegisterCombined, func_8432F998, ParticleEffect_RegisterHandlers_473BC, ParticleEffect_SmallNodeSetup, ParticleEffect_InitBurstEffect, ParticleEffect_DynamicStateSetup,
    ParticleEffect_Init, SpawnLargeBurstEffect, ParticleEffect_FullSetupA, ParticleEffect_PaletteBurst, func_8433DC80, func_8432F998, func_843378CC,
    ParticleEffect_WaterAnimBurst, ParticleEffect_InitSetA, func_84336EE8, ParticleEffect_PaletteScriptBurst, func_8432F998, InitParticleEffectSet_Alt2, func_8432F998,
    ParticleEffect_RegisterEffectE0, ParticleEffect_GroupSetupA, ParticleEffect_FinalGroupSetup, ParticleEffect_ComplexNodeSetup, func_8432F998, func_8432F998, ParticleEffect_RegisterSparkle,
    ParticleEffect_InitSmokeSetB, ParticleEffect_BasicMultiBurst2, ParticleEffect_SimpleBurstScript, ParticleEffect_RegisterExplosion, InitParticleEffectSet_WithFade, ParticleEffect_RegisterLargeExplosion, ParticleEffect_TextureSetup,
    func_8432F998, func_8432F998, func_8432F998, ParticleEffect_SetMode, func_8432F998, InitParticleEffectSet_WithTexture53, SpawnTimedFireballEffect,
    ParticleEffect_SimpleNodeEntry, ParticleEffect_RegisterAll_48630, func_8432F998, ParticleEffect_RegisterHandler_49628, ParticleEffect_RegisterEffectE0Alt2, func_8432F998, ParticleEffect_RegisterHandler_49830,
    ParticleEffect_AdditionalNodeSetup, ParticleEffect_SmallNodeSetupB, InitExplosionEffectSet, func_8433E124, ParticleEffect_GroupSetupA, ParticleEffect_HandleStateSetup, func_8432F998,
    ParticleEffect_RegisterHandlers_Default, ParticleEffect_RegisterHandler_416B0, ParticleEffect_RegisterParticleNodes, ParticleEffect_RegisterMultipleHandlers, func_8432F998, ParticleEffect_RegisterHandler_49384, ParticleEffect_RegisterHandlers_49504,
    InitParticleEffectSet_WithDifferentTiming, ParticleEffect_RegisterHandler_49058, ParticleEffect_RegisterHandler_47448, func_8433E46C, ParticleEffect_RegisterHandler_49108, ParticleEffect_RegisterHandlers_Alternate, ParticleEffect_RegisterEffectE0Alt,
    InitSmallGlowEffectSet, InitParticleEffectSet_Single, ParticleEffect_RegisterHandler_498D8, ParticleEffect_RegisterDefaultTexture, ParticleEffect_AdvancedModeSetup, ParticleEffect_RegisterAll_48630, ParticleEffect_SimpleBurst,
    ParticleEffect_InitSmokeSetC, ParticleEffect_FinalSetupA, ParticleEffect_RegisterLargeExplosionAndEffects, func_8434A9EC, ParticleEffect_MultiNodeC2, ParticleEffect_MultiNodeD, ParticleEffect_PortraitBurst,
    ParticleEffect_PortraitBurstNode, ParticleEffect_PortraitBurstCheck, ParticleEffect_WaterAnimFirework, ParticleEffect_SimpleBurst2, ParticleEffect_PaletteMultiBurst2, ParticleEffect_PaletteBurst4, ParticleEffect_PaletteBurst5,
    func_8432F998, ParticleEffect_BasicMultiBurst, ParticleEffect_SimpleBurst4, ParticleEffect_RotationEntry, ParticleSystem_ForceResetLock, ParticleEffect_InitSmoke, ParticleEffect_InitFire,
    ParticleEffect_TriggerSpecial, ParticleEffect_AlphaBurst, ParticleEffect_AlphaBurst2, ParticleEffect_AdditionalSetupA, ParticleEffect_SimpleGroupSetup, ParticleEffect_ComplexGroupSetup, ParticleEffect_RegisterHandler_490A8,
    ParticleEffect_PortraitBurstInit, ParticleEffect_TriggerDefault1, ParticleEffect_FinalSetupB, ParticleEffect_FinalSetupC, ParticleEffect_AdditionalNodeA, ParticleEffect_StateCollisionSetupA, ParticleEffect_CreateWithCallback,
    ParticleEffect_CreateCallback, InitSmallGlowEffectSet, ParticleEffect_TriggerDefault3, func_8433FD30, ParticleEffect_ConditionalStateSetup, ParticleEffect_CollisionResponseSwitch, ParticleEffect_RegisterCallbacks,
    func_8433765C, ParticleEffect_CreateVariant45, ParticleEffect_CreateVariant47, ParticleEffect_CreateTypeX, ParticleEffect_CreateSmoke, ParticleEffect_CreateSmokeHighPriority, ParticleEffect_CreateDual,
    func_8433FAF8, func_8433F758, func_8433F5D4, func_8432F998, ParticleEffect_ExtraNodeSetup, ParticleEffect_TextureNodeSetup, func_8433F414,
    func_8433F4CC, func_8433F4EC, func_8433F5B4, func_8433F974, func_8432F998,
};
static func_D_84390320 gParticleStateFunctionTable[] = {
    func_8432F9A0, func_8432F9A0, InitComplexParticleSequence, ParticleEffect_SpecialCollisionSetup, ParticleEffect_MultiTextureSetup, ParticleEffect_DynamicCollisionSetup, ParticleEffect_RegisterPaletteVariants,
    ParticleEffect_PaletteMultiBurst, func_8433DECC, func_8432F9A0, ParticleEffect_RegisterAnimationCallbacks, func_8432F9A0, func_8432F9A0, ParticleEffect_RegisterSpecific,
    ParticleEffect_InitializeGroup, ParticleEffect_InitExplosionSetB, ParticleEffect_AdvancedMultiBurst, ParticleEffect_RegisterSmoke, ParticleEffect_ModeSpecificSetup, func_8432F9A0, InitParticleComboVariant,
    ParticleEffect_RegisterModeSpecific, ParticleEffect_InitExplosionSet, ParticleEffect_RegisterAll, func_8432F9A0, ParticleEffect_PlaySoundAndReset, RegisterParticleEffect_ComplexMovement, InitAdvancedParticleCombo,
    func_8433E33C, ParticleEffect_InitFireSet, ParticleEffect_HandleCollisionSetup, ParticleEffect_RegisterMultiple, func_8432F9A0, func_8432F9A0, InitParticleEffectGroup_Basic,
    ParticleEffect_ConfigB, ParticleEffect_ConfigA, ParticleEffect_SpecialSetupA, ParticleEffect_SpecialSetupB, ParticleEffect_AdditionalSetupB, ParticleEffect_InitSparkleSet, ParticleEffect_Trigger56A74,
    ParticleEffect_ModeSetup, ParticleEffect_CollisionSetup, ParticleEffect_ConfigVariantA, ParticleEffect_CombinedSetupA, ParticleEffect_CombinedSetupB, ParticleEffect_SpecialSetupC, func_8432F9A0,
    ParticleEffect_RegisterColorAnim, ParticleEffect_RegisterHandler_WithParticleData, ParticleEffect_WaterAnimBurst2, ParticleEffect_MultiHandleSetup, InitParticleEffectSet_WithCustomCallback, ParticleEffect_InitSetC, ParticleEffect_SimpleNodeSetup,
    ParticleEffect_InitSetB, ParticleEffect_FullSetupB, func_8434A930, ParticleEffect_InitCombinedSet, ParticleEffect_WaterAnimFirework2, ParticleEffect_SimpleBurst3, ParticleEffect_PaletteMultiBurst3,
    ParticleEffect_FireworkBurst, ParticleEffect_FireballBurst, ParticleEffect_FireworkEntry, ParticleEffect_SimpleNodeBurst, InitParticleEffectSet_WithMultiple, InitParticleEffectSet_WithTimedFireball, InitParticleEffectSet_Variant2,
    InitParticleEffectSet_WithComplex, InitParticleEffectSet_Variant3, func_8433DFF4, ParticleEffect_AlphaFirework2, ParticleEffect_AlphaFirework, ParticleEffect_MultiNodeAEntry, ParticleEffect_TriggerAnother,
    ParticleEffect_TriggerDefault2, ParticleEffect_RegisterHandlers_4967C, ParticleEffect_CreateColorVariant, ParticleEffect_ConfigVariantB, ParticleEffect_RegisterAll_489FC, ParticleEffect_RegisterAll_489FC, ParticleEffect_ConfigureAndTrigger_4917C,
    ParticleEffect_TriggerDefault4, ParticleEffect_StateCollisionSetupB, InitParticleEffectSet_ThreeInstances, RegisterParticleEffect_Burst, ParticleEffect_CollisionAndBurstSetup, func_8432F9A0,
};
static u8 D_8438682C[] = {
    0x3F, 0x00, 0x00, 0x00, 0x3F, 0x00, 0x00, 0x00, 0x3F, 0x00, 0x00, 0x00,
    0x3F, 0x00, 0x00, 0x00, 0x01, 0x3F, 0x00, 0x00, 0x3F, 0x00, 0x00, 0x00,

};
static u8 D_84386844[] = {
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
static u8 D_8438684C[] = {
    0x05,
    0x3F,
    0x00,
    0x00,

};
static u8 D_84386850[] = {
    0x06,
    0x3F,
    0x00,
    0x00,

};
static u8 D_84386854[] = {
    0x09,
    0x3F,
    0x00,
    0x00,

};
static u8 D_84386858[] = {
    0x0A,
    0x3F,
    0x00,
    0x00,

};
static u8 D_8438685C[] = {
    0x0B,
    0x3F,
    0x00,
    0x00,

};
static u8 gBattleScriptTable_60[] = {
    0x0C, 0x3F, 0x00, 0x00, 0x0D, 0x3F, 0x00, 0x00,

};
static u8 D_84386868[] = {
    0x0E,
    0x3F,
    0x00,
    0x00,

};
static u8 D_8438686C[] = {
    0x0F,
    0x3F,
    0x00,
    0x00,

};
static u8 D_84386870[] = {
    0x10,
    0x3F,
    0x00,
    0x00,

};
static u8 D_84386874[] = {
    0x11,
    0x3F,
    0x00,
    0x00,

};
static u8 D_84386878[] = {
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
static u8 D_84386880[] = {
    0x13,
    0x3F,
    0x00,
    0x00,

};
static u8 gBattleScriptTable_84[] = {
    0x14, 0x3F, 0x00, 0x00, 0x15, 0x3F, 0x00, 0x00,

};
static u8 D_8438688C[] = {
    0x16, 0x3F, 0x00, 0x00, 0x17, 0x3F, 0x00, 0x00,

};
static u8 D_84386894[] = {
    0x18,
    0x3F,
    0x00,
    0x00,

};
static u8 D_84386898[] = {
    0x19,
    0x32,
    0x3F,
    0x00,

};
static u8 D_8438689C[] = {
    0x1A,
    0x3F,
    0x00,
    0x00,

};
static u8 D_843868A0[] = {
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
static u8 D_843868A8[] = {
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
static u8 D_843868B0[] = {
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
static u8 D_843868B8[] = {
    0x21,
    0x3F,
    0x00,
    0x00,

};
static u8 D_843868BC[] = {
    0x22,
    0x3F,
    0x00,
    0x00,

};
static u8 D_843868C0[] = {
    0x23, 0x3F, 0x00, 0x00, 0x24, 0x3F, 0x00, 0x00,

};
static u8 D_843868C8[] = {
    0x25,
    0x3F,
    0x00,
    0x00,

};
static u8 D_843868CC[] = {
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
static u8 D_843868EC[] = {
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
static u8 D_84386924[] = {
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
static u8 D_84386980[] = {
    0x66, 0x04, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00,

};
static u8 gBattleScriptCmd_06[] = {
    0x06,
    0x00,
    0x00,
    0x00,

};
static u8 D_8438698C[] = {
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
static u8 D_84386994[] = {
    0x08, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00,

};
static u8 gBattleScriptCmd_0A[] = {
    0x0A,
    0x00,
    0x00,
    0x00,

};
static u8 D_843869A0[] = {
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
static u8 D_843869C8[] = {
    0x13, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00,

};
static u8 D_843869D0[] = {
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
static u8 D_843869DC[] = {
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
static u8 D_84386A1C[] = {
    0x28,
    0x00,
    0x00,
    0x00,

};
static u8 D_84386A20[] = {
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
static u8 D_84386A28[] = {
    0x2B,
    0x00,
    0x00,
    0x00,

};
static u8 D_84386A2C[] = {
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
static u8 D_84386A60[] = {
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
static u8 D_84386A9C[] = {
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
static u8 D_84386BBC[] = {
    0x00, 0x00, 0x00, 0x00, 0x59, 0x00, 0x00, 0x00,

};
static u8 D_84386BC4[] = {
    0x01,
    0x00,
    0x00,
    0x00,

};
static u8 D_84386BC8[] = {
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
        D_8438682C,
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
        D_84386924,
    },
    {
        gBattleScriptCmd_88,
        D_84386924,
    },
    {
        gBattleScriptCmd_89,
        gBattleScriptCmd_2D,
    },
    {
        gBattleScriptCmd_8A,
        D_8438682C,
    },
    {
        gBattleScriptCmd_00,
        D_8438682C,
    },
    {
        gBattleScriptCmd_8B,
        D_84386924,
    },
    {
        D_843869D0,
        D_84386870,
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
        D_8438682C,
    },
};
static u8* Fragment62_DataPtrArray[] = {
    gBattleScriptCmd_00, gBattleScriptCmd_7D, gBattleScriptCmd_7E, gBattleScriptCmd_01, gBattleScriptCmd_45, gBattleScriptCmd_7F,
    gBattleScriptCmd_80, gBattleScriptCmd_81, gBattleScriptCmd_82, gBattleScriptCmd_83, gBattleScriptCmd_84, gBattleScriptCmd_90,
};
static u8* Fragment62_GroupPtrArray[] = {
    D_84386BBC, D_84386BC4, Fragment62_Byte09, D_84386BC8, Fragment62_Byte31,
};
static u8* Fragment62_SpecialPairPtr[] = { gBattleScriptCmd_00, D_84386A2C };
static u8* Fragment62_ComplexPtrTable[][5] = {
    {
        gBattleScriptCmd_00,
        gBattleScriptCmd_00,
        D_84386BBC,
        D_8438682C,
        D_8438682C,
    },
    {
        gBattleScriptCmd_00,
        gBattleScriptCmd_00,
        Fragment62_Byte2C,
        D_8438682C,
        D_84386894,
    },
    {
        gBattleScriptCmd_00,
        gBattleScriptCmd_00,
        Fragment62_Byte2C,
        D_8438682C,
        D_84386894,
    },
    {
        gBattleScriptCmd_00,
        gBattleScriptCmd_00,
        Fragment62_Byte0E,
        D_8438682C,
        D_84386894,
    },
    {
        gBattleScriptCmd_00,
        gBattleScriptCmd_00,
        Fragment62_Byte23,
        D_8438682C,
        D_84386894,
    },
    {
        gBattleScriptCmd_0F,
        gBattleScriptCmd_00,
        Fragment62_Bytes50_4C,
        D_84386844,
        D_84386894,
    },
    {
        gBattleScriptCmd_00,
        gBattleScriptCmd_00,
        Fragment62_Bytes0D_0E,
        D_8438682C,
        gBattleScriptCmd_17,
    },
    {
        D_84386A9C,
        gBattleScriptCmd_00,
        Fragment62_Byte36,
        D_84386874,
        D_84386894,
    },
    {
        D_84386A20,
        gBattleScriptCmd_00,
        Fragment62_Byte2A,
        D_843868B0,
        D_84386894,
    },
    {
        gBattleScriptCmd_49,
        gBattleScriptCmd_00,
        Fragment62_Byte2B,
        D_8438686C,
        D_84386894,
    },
    {
        gBattleScriptCmd_0D,
        gBattleScriptCmd_00,
        Fragment62_Byte05,
        D_8438685C,
        D_8438682C,
    },
    {
        gBattleScriptCmd_47,
        gBattleScriptCmd_00,
        Fragment62_Byte29,
        gBattleScriptCmd_08,
        D_84386894,
    },
    {
        gBattleScriptCmd_6F,
        gBattleScriptCmd_00,
        Fragment62_Byte53,
        gBattleScriptCmd_08,
        D_84386894,
    },
    {
        gBattleScriptCmd_0A,
        gBattleScriptCmd_48,
        Fragment62_Byte03,
        gBattleScriptCmd_09,
        D_843868EC,
    },
    {
        gBattleScriptCmd_44,
        gBattleScriptCmd_00,
        D_84386BBC,
        gBattleScriptCmd_2E,
        D_8438682C,
    },
    {
        gBattleScriptCmd_3D,
        gBattleScriptCmd_00,
        Fragment62_Byte1E,
        D_8438685C,
        D_8438682C,
    },
    {
        gBattleScriptCmd_0A,
        gBattleScriptCmd_00,
        Fragment62_Byte2F,
        D_84386854,
        D_84386894,
    },
    {
        gBattleScriptCmd_00,
        gBattleScriptCmd_00,
        Fragment62_Bytes57_23,
        D_84386858,
        D_84386894,
    },
    {
        gBattleScriptCmd_0A,
        gBattleScriptCmd_00,
        D_84386BBC,
        D_84386854,
        D_8438682C,
    },
    {
        gBattleScriptCmd_00,
        D_84386A1C,
        Fragment62_Bytes4F_2D,
        D_843868AC,
        D_84386894,
    },
    {
        D_843869C8,
        gBattleScriptCmd_00,
        Fragment62_Byte09,
        D_8438682C,
        D_8438682C,
    },
    {
        gBattleScriptCmd_00,
        gBattleScriptCmd_00,
        Fragment62_Byte2D,
        D_8438682C,
        D_84386894,
    },
    {
        gBattleScriptCmd_75,
        gBattleScriptCmd_00,
        Fragment62_Byte55,
        D_8438685C,
        D_84386858,
    },
    {
        gBattleScriptCmd_00,
        gBattleScriptCmd_00,
        Fragment62_Bytes4F_27,
        D_8438682C,
        D_84386894,
    },
    {
        gBattleScriptCmd_00,
        gBattleScriptCmd_00,
        Fragment62_Byte23,
        D_8438682C,
        D_84386894,
    },
    {
        gBattleScriptCmd_02,
        gBattleScriptCmd_00,
        Fragment62_Bytes50_4C,
        D_84386844,
        D_84386894,
    },
    {
        gBattleScriptCmd_00,
        gBattleScriptCmd_00,
        Fragment62_Byte2C,
        D_8438682C,
        D_84386894,
    },
    {
        gBattleScriptCmd_00,
        gBattleScriptCmd_00,
        Fragment62_Byte2C,
        D_8438682C,
        D_84386894,
    },
    {
        gBattleScriptCmd_1F,
        gBattleScriptCmd_00,
        Fragment62_Byte37,
        D_8438688C,
        D_84386894,
    },
    {
        gBattleScriptCmd_00,
        gBattleScriptCmd_00,
        Fragment62_Byte0E,
        D_8438682C,
        D_84386894,
    },
    {
        gBattleScriptCmd_77,
        gBattleScriptCmd_00,
        Fragment62_Byte25,
        D_84386850,
        D_84386894,
    },
    {
        gBattleScriptCmd_76,
        gBattleScriptCmd_00,
        Fragment62_Byte2F,
        D_84386850,
        D_84386894,
    },
    {
        gBattleScriptCmd_79,
        gBattleScriptCmd_00,
        Fragment62_Bytes54_25,
        D_84386850,
        D_84386894,
    },
    {
        gBattleScriptCmd_00,
        gBattleScriptCmd_00,
        Fragment62_Byte2C,
        D_8438682C,
        D_84386894,
    },
    {
        gBattleScriptCmd_74,
        gBattleScriptCmd_00,
        Fragment62_Bytes4F_2D,
        D_8438682C,
        D_84386894,
    },
    {
        D_843869C8,
        gBattleScriptCmd_00,
        Fragment62_Byte09,
        D_8438682C,
        D_8438682C,
    },
    {
        gBattleScriptCmd_73,
        gBattleScriptCmd_00,
        Fragment62_Byte2C,
        gBattleScriptCmd_32,
        D_84386894,
    },
    {
        gBattleScriptCmd_72,
        gBattleScriptCmd_00,
        Fragment62_Byte2D,
        D_8438682C,
        D_84386894,
    },
    {
        gBattleScriptCmd_73,
        gBattleScriptCmd_00,
        Fragment62_Byte2D,
        gBattleScriptCmd_32,
        D_84386894,
    },
    {
        gBattleScriptCmd_00,
        gBattleScriptCmd_00,
        D_84386BBC,
        D_8438682C,
        D_8438682C,
    },
    {
        gBattleScriptCmd_43,
        gBattleScriptCmd_00,
        Fragment62_Byte26,
        D_84386850,
        D_84386894,
    },
    {
        gBattleScriptCmd_43,
        gBattleScriptCmd_00,
        Fragment62_Byte26,
        D_84386850,
        D_84386894,
    },
    {
        gBattleScriptCmd_43,
        gBattleScriptCmd_00,
        Fragment62_Byte25,
        D_84386850,
        D_84386894,
    },
    {
        gBattleScriptCmd_53,
        gBattleScriptCmd_00,
        D_84386BBC,
        gBattleScriptCmd_30,
        D_8438682C,
    },
    {
        gBattleScriptCmd_4A,
        gBattleScriptCmd_00,
        Fragment62_Byte29,
        gBattleScriptCmd_08,
        D_84386894,
    },
    {
        gBattleScriptCmd_00,
        gBattleScriptCmd_00,
        D_84386BBC,
        D_8438682C,
        D_8438682C,
    },
    {
        gBattleScriptCmd_00,
        gBattleScriptCmd_00,
        D_84386BBC,
        D_8438682C,
        D_8438682C,
    },
    {
        D_84386A28,
        gBattleScriptCmd_00,
        D_84386BBC,
        D_843868B8,
        D_8438682C,
    },
    {
        D_84386A2C,
        gBattleScriptCmd_00,
        D_84386BBC,
        D_843868BC,
        D_8438682C,
    },
    {
        gBattleScriptJump_2D,
        gBattleScriptCmd_00,
        Fragment62_Byte23,
        D_843868C0,
        D_84386894,
    },
    {
        gBattleScriptCmd_62,
        gBattleScriptCmd_00,
        Fragment62_Byte21,
        D_8438682C,
        D_8438682C,
    },
    {
        gBattleScriptCmd_11,
        gBattleScriptCmd_00,
        Fragment62_Byte07b,
        D_84386868,
        D_8438682C,
    },
    {
        gBattleScriptCmd_16,
        gBattleScriptCmd_00,
        Fragment62_Bytes38_4D,
        D_84386874,
        D_84386894,
    },
    {
        gBattleScriptCmd_4D,
        gBattleScriptCmd_00,
        Fragment62_Byte16,
        D_84386874,
        D_84386894,
    },
    {
        D_84386A60,
        gBattleScriptCmd_00,
        D_84386BBC,
        gBattleScriptCmd_14,
        D_8438682C,
    },
    {
        gBattleScriptCmd_06,
        gBattleScriptCmd_00,
        Fragment62_Byte02,
        D_84386844,
        D_84386868,
    },
    {
        D_8438698C,
        gBattleScriptCmd_00,
        Fragment62_Bytes1B_1C,
        D_84386844,
        D_84386868,
    },
    {
        gBattleScriptJump_24,
        gBattleScriptCmd_00,
        Fragment62_Byte10,
        D_8438689C,
        D_84386844,
    },
    {
        gBattleScriptJump_2F,
        gBattleScriptCmd_00,
        Fragment62_Byte43,
        gBattleScriptCmd_29,
        D_8438682C,
    },
    {
        gBattleScriptCmd_22,
        gBattleScriptCmd_00,
        Fragment62_Byte17,
        D_84386898,
        D_84386844,
    },
    {
        D_84386980,
        gBattleScriptCmd_00,
        Fragment62_Byte44,
        D_8438682C,
        gBattleScriptCmd_29,
    },
    {
        gBattleScriptJump_78,
        gBattleScriptCmd_00,
        Fragment62_Byte35,
        D_8438682C,
        gBattleScriptCmd_29,
    },
    {
        gBattleScriptJump_1A,
        gBattleScriptCmd_00,
        Fragment62_Bytes45_0E_04,
        D_8438682C,
        gBattleScriptCmd_29,
    },
    {
        gBattleScriptJump_27,
        gBattleScriptCmd_00,
        Fragment62_Byte46,
        D_843868A8,
        gBattleScriptCmd_29,
    },
    {
        gBattleScriptCmd_76,
        gBattleScriptCmd_00,
        Fragment62_Byte25,
        D_84386850,
        D_84386894,
    },
    {
        gBattleScriptCmd_71,
        gBattleScriptCmd_00,
        Fragment62_Bytes4D_0E,
        D_84386850,
        D_84386894,
    },
    {
        gBattleScriptCmd_6C,
        gBattleScriptCmd_00,
        Fragment62_Byte2E,
        D_8438682C,
        D_84386894,
    },
    {
        gBattleScriptCmd_00,
        gBattleScriptCmd_00,
        Fragment62_Byte24,
        D_8438682C,
        D_84386894,
    },
    {
        gBattleScriptCmd_00,
        gBattleScriptCmd_00,
        Fragment62_Byte2C,
        D_8438682C,
        D_84386894,
    },
    {
        gBattleScriptCmd_4E,
        gBattleScriptCmd_00,
        Fragment62_Bytes4F_2D,
        D_8438682C,
        D_84386894,
    },
    {
        gBattleScriptCmd_4B,
        gBattleScriptCmd_00,
        Fragment62_Byte32,
        gBattleScriptCmd_46,
        D_8438682C,
    },
    {
        D_843869DC,
        gBattleScriptCmd_00,
        Fragment62_Byte15,
        D_84386880,
        D_843868CC,
    },
    {
        D_843869DC,
        gBattleScriptCmd_00,
        Fragment62_Byte15,
        D_84386880,
        D_843868CC,
    },
    {
        D_84386994,
        gBattleScriptCmd_00,
        Fragment62_Byte1F,
        D_8438684C,
        D_8438682C,
    },
    {
        gBattleScriptCmd_6D,
        gBattleScriptCmd_00,
        D_84386BBC,
        D_8438682C,
        D_8438682C,
    },
    {
        D_843869A0,
        gBattleScriptCmd_00,
        Fragment62_Byte04,
        D_84386858,
        D_84386894,
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
        D_843868C8,
        D_84386894,
    },
    {
        gBattleScriptCmd_41,
        gBattleScriptCmd_00,
        Fragment62_Bytes12_13_14,
        D_843868C8,
        D_84386894,
    },
    {
        gBattleScriptCmd_41,
        gBattleScriptCmd_00,
        Fragment62_Bytes12_13_14,
        D_843868C8,
        D_84386894,
    },
    {
        gBattleScriptJump_39,
        gBattleScriptCmd_00,
        Fragment62_Byte1A,
        D_84386858,
        D_84386894,
    },
    {
        gBattleScriptCmd_21,
        gBattleScriptCmd_00,
        Fragment62_Byte20,
        D_8438682C,
        D_8438682C,
    },
    {
        gBattleScriptCmd_23,
        gBattleScriptCmd_00,
        Fragment62_Byte0F,
        D_84386874,
        D_84386894,
    },
    {
        gBattleScriptCmd_54,
        gBattleScriptCmd_00,
        Fragment62_Byte1D,
        D_84386878,
        D_84386894,
    },
    {
        gBattleScriptTable_A98,
        gBattleScriptCmd_00,
        Fragment62_Byte08,
        D_8438686C,
        D_8438682C,
    },
    {
        gBattleScriptCmd_12,
        gBattleScriptCmd_00,
        Fragment62_Byte08,
        D_8438686C,
        D_8438682C,
    },
    {
        gBattleScriptCmd_26,
        gBattleScriptCmd_00,
        Fragment62_Byte11,
        gBattleScriptTable_A4,
        D_8438682C,
    },
    {
        gBattleScriptCmd_12,
        gBattleScriptCmd_00,
        Fragment62_Byte48,
        D_8438686C,
        D_8438682C,
    },
    {
        gBattleScriptCmd_3F,
        gBattleScriptCmd_00,
        Fragment62_Bytes0A_0B_0C_0D,
        D_8438682C,
        gBattleScriptCmd_46,
    },
    {
        gBattleScriptCmd_25,
        gBattleScriptCmd_00,
        Fragment62_Byte4B,
        D_843868A0,
        D_84386894,
    },
    {
        gBattleScriptCmd_25,
        gBattleScriptCmd_00,
        Fragment62_Byte3A,
        D_843868A0,
        D_84386894,
    },
    {
        gBattleScriptTable_A50,
        gBattleScriptCmd_00,
        Fragment62_Bytes4E_4F,
        gBattleScriptCmd_28,
        D_84386894,
    },
    {
        gBattleScriptCmd_11,
        gBattleScriptCmd_00,
        Fragment62_Byte07,
        D_84386868,
        D_8438682C,
    },
    {
        gBattleScriptCmd_6B,
        gBattleScriptCmd_00,
        Fragment62_Byte49,
        D_843868CC,
        D_84386894,
    },
    {
        gBattleScriptCmd_6A,
        gBattleScriptCmd_00,
        Fragment62_Byte4A,
        D_843868CC,
        D_84386894,
    },
    {
        gBattleScriptJump_2A,
        gBattleScriptCmd_00,
        D_84386BBC,
        gBattleScriptTable_B4,
        D_8438682C,
    },
    {
        gBattleScriptCmd_60,
        gBattleScriptCmd_00,
        D_84386BBC,
        gBattleScriptCmd_37,
        D_8438682C,
    },
    {
        gBattleScriptCmd_1B,
        gBattleScriptCmd_00,
        D_84386BBC,
        D_8438682C,
        D_8438682C,
    },
    {
        gBattleScriptCmd_5A,
        gBattleScriptCmd_00,
        Fragment62_Byte2C,
        gBattleScriptCmd_32,
        D_84386894,
    },
    {
        gBattleScriptCmd_55,
        gBattleScriptCmd_00,
        Fragment62_Byte2C,
        D_843868CC,
        D_84386894,
    },
    {
        gBattleScriptCmd_56,
        gBattleScriptCmd_00,
        D_84386BBC,
        gBattleScriptCmd_1E,
        D_8438682C,
    },
    {
        gBattleScriptCmd_61,
        gBattleScriptCmd_00,
        Fragment62_Bytes3F_23_33,
        gBattleScriptCmd_38,
        D_84386894,
    },
    {
        gBattleScriptTable_9F0,
        gBattleScriptCmd_00,
        D_84386BBC,
        D_8438682C,
        D_8438682C,
    },
    {
        gBattleScriptJump_2A,
        gBattleScriptCmd_00,
        D_84386BBC,
        gBattleScriptTable_B4,
        D_8438682C,
    },
    {
        gBattleScriptCmd_1B,
        gBattleScriptCmd_00,
        D_84386BBC,
        D_8438682C,
        D_8438682C,
    },
    {
        gBattleScriptCmd_6E,
        gBattleScriptCmd_00,
        D_84386BBC,
        D_8438682C,
        D_8438682C,
    },
    {
        gBattleScriptTable_A74,
        gBattleScriptCmd_00,
        D_84386BBC,
        D_8438682C,
        D_8438682C,
    },
    {
        gBattleScriptCmd_00,
        gBattleScriptCmd_00,
        D_84386BBC,
        D_8438682C,
        D_8438682C,
    },
    {
        gBattleScriptCmd_1C,
        gBattleScriptCmd_00,
        D_84386BBC,
        gBattleScriptTable_84,
        D_84386894,
    },
    {
        gBattleScriptCmd_5D,
        gBattleScriptCmd_00,
        Fragment62_Byte3C,
        gBattleScriptCmd_10,
        D_84386894,
    },
    {
        gBattleScriptCmd_5B,
        gBattleScriptCmd_00,
        D_84386BBC,
        gBattleScriptCmd_33,
        D_8438682C,
    },
    {
        gBattleScriptCmd_57,
        gBattleScriptCmd_00,
        D_84386BBC,
        gBattleScriptCmd_31,
        D_84386894,
    },
    {
        gBattleScriptCmd_0E,
        gBattleScriptCmd_00,
        D_84386BBC,
        gBattleScriptTable_60,
        D_8438682C,
    },
    {
        gBattleScriptCmd_0E,
        gBattleScriptCmd_00,
        D_84386BBC,
        gBattleScriptTable_60,
        D_8438682C,
    },
    {
        gBattleScriptTable_A7C,
        gBattleScriptCmd_00,
        D_84386BBC,
        gBattleScriptTable_904,
        D_8438682C,
    },
    {
        gBattleScriptTable_A80,
        gBattleScriptCmd_00,
        D_84386BBC,
        gBattleScriptCmd_0C,
        D_8438682C,
    },
    {
        gBattleScriptCmd_03,
        gBattleScriptCmd_00,
        D_84386BBC,
        D_843868CC,
        D_8438682C,
    },
    {
        gBattleScriptCmd_55,
        gBattleScriptCmd_00,
        Fragment62_Byte2C,
        D_843868CC,
        D_84386894,
    },
    {
        gBattleScriptCmd_20,
        gBattleScriptCmd_00,
        Fragment62_Byte18,
        D_8438682C,
        D_8438682C,
    },
    {
        gBattleScriptCmd_00,
        gBattleScriptCmd_00,
        Fragment62_Byte18,
        D_8438682C,
        D_8438682C,
    },
    {
        gBattleScriptTable_A44,
        gBattleScriptCmd_00,
        Fragment62_Byte51,
        gBattleScriptTable_D0,
        D_84386874,
    },
    {
        gBattleScriptCmd_40,
        gBattleScriptCmd_00,
        Fragment62_Byte28,
        gBattleScriptCmd_07,
        D_84386874,
    },
    {
        gBattleScriptCmd_5C,
        gBattleScriptCmd_00,
        Fragment62_Byte07,
        gBattleScriptCmd_34,
        D_84386868,
    },
    {
        gBattleScriptCmd_4C,
        gBattleScriptCmd_00,
        Fragment62_Bytes12_13_14,
        gBattleScriptTable_84,
        D_84386894,
    },
    {
        gBattleScriptCmd_11,
        gBattleScriptCmd_00,
        Fragment62_Byte07,
        D_84386868,
        D_8438682C,
    },
    {
        gBattleScriptCmd_4F,
        gBattleScriptCmd_00,
        Fragment62_Byte0E,
        gBattleScriptCmd_2F,
        D_84386894,
    },
    {
        gBattleScriptCmd_4D,
        gBattleScriptCmd_00,
        Fragment62_Byte3B,
        D_84386874,
        D_84386894,
    },
    {
        gBattleScriptCmd_63,
        gBattleScriptCmd_00,
        Fragment62_Byte40,
        gBattleScriptCmd_39,
        D_84386844,
    },
    {
        gBattleScriptCmd_47,
        gBattleScriptCmd_00,
        Fragment62_Byte29,
        gBattleScriptCmd_08,
        D_84386894,
    },
    {
        gBattleScriptJump_07,
        gBattleScriptCmd_00,
        Fragment62_Byte34,
        gBattleScriptTable_48,
        D_84386894,
    },
    {
        gBattleScriptCmd_70,
        gBattleScriptCmd_00,
        Fragment62_Bytes50_4C,
        gBattleScriptCmd_32,
        D_84386894,
    },
    {
        gBattleScriptCmd_3E,
        gBattleScriptCmd_00,
        Fragment62_Byte25,
        D_84386850,
        D_84386894,
    },
    {
        D_843869C8,
        gBattleScriptCmd_00,
        Fragment62_Byte09b,
        D_8438682C,
        D_8438682C,
    },
    {
        gBattleScriptTable_A88,
        gBattleScriptCmd_00,
        D_84386BBC,
        D_8438682C,
        D_8438682C,
    },
    {
        gBattleScriptTable_A5C,
        D_84386A2C,
        D_84386BBC,
        gBattleScriptCmd_2A,
        D_843868BC,
    },
    {
        gBattleScriptCmd_42,
        gBattleScriptCmd_00,
        D_84386BBC,
        gBattleScriptCmd_07,
        D_8438682C,
    },
    {
        gBattleScriptCmd_5A,
        gBattleScriptCmd_00,
        Fragment62_Byte2C,
        gBattleScriptCmd_32,
        D_84386894,
    },
    {
        gBattleScriptCmd_53,
        gBattleScriptCmd_00,
        D_84386BBC,
        gBattleScriptCmd_30,
        D_8438682C,
    },
    {
        gBattleScriptCmd_5F,
        gBattleScriptCmd_00,
        Fragment62_Byte3E,
        gBattleScriptCmd_36,
        D_8438682C,
    },
    {
        gBattleScriptCmd_1C,
        gBattleScriptCmd_00,
        Fragment62_Bytes12_13_14,
        gBattleScriptTable_84,
        D_84386894,
    },
    {
        gBattleScriptCmd_65,
        gBattleScriptCmd_00,
        Fragment62_Byte41,
        gBattleScriptCmd_3B,
        D_84386894,
    },
    {
        D_843869DC,
        gBattleScriptCmd_00,
        Fragment62_Byte15,
        D_84386880,
        D_843868CC,
    },
    {
        gBattleScriptCmd_5E,
        gBattleScriptCmd_00,
        Fragment62_Byte3D,
        gBattleScriptCmd_35,
        D_8438682C,
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
        D_84386BBC,
        D_8438682C,
        D_8438682C,
    },
    {
        gBattleScriptTable_A3C,
        gBattleScriptCmd_00,
        Fragment62_Byte22,
        D_84386844,
        D_84386894,
    },
    {
        gBattleScriptCmd_00,
        gBattleScriptCmd_00,
        Fragment62_Bytes06_0E,
        D_8438682C,
        gBattleScriptCmd_18,
    },
    {
        gBattleScriptCmd_41,
        gBattleScriptCmd_00,
        Fragment62_Bytes12_13_14,
        D_843868C8,
        D_84386894,
    },
    {
        gBattleScriptTable_9BC,
        gBattleScriptCmd_00,
        Fragment62_Byte39,
        D_8438682C,
        D_84386894,
    },
    {
        gBattleScriptTable_A40,
        gBattleScriptCmd_00,
        Fragment62_Byte42,
        D_843868CC,
        D_84386894,
    },
    {
        gBattleScriptCmd_00,
        gBattleScriptCmd_00,
        D_84386BBC,
        D_8438682C,
        D_8438682C,
    },
    {
        gBattleScriptCmd_51,
        gBattleScriptCmd_00,
        D_84386BBC,
        D_84386868,
        D_84386894,
    },
    {
        gBattleScriptCmd_64,
        gBattleScriptCmd_00,
        Fragment62_Bytes2D_1E,
        gBattleScriptCmd_3A,
        D_84386894,
    },
    {
        gBattleScriptCmd_52,
        gBattleScriptCmd_00,
        Fragment62_Byte52,
        gBattleScriptTable_D0,
        D_84386874,
    },
    {
        gBattleScriptCmd_7C,
        gBattleScriptCmd_7B,
        Fragment62_Entry58_06,
        D_8438685C,
        D_8438682C,
    },
    {
        gBattleScriptCmd_50,
        gBattleScriptCmd_00,
        Fragment62_Byte2C,
        gBattleScriptCmd_2F,
        D_84386894,
    },
    {
        gBattleScriptCmd_00,
        gBattleScriptCmd_00,
        D_84386BBC,
        D_8438682C,
        D_8438682C,
    },
    {
        gBattleScriptCmd_3F,
        gBattleScriptCmd_00,
        Fragment62_Bytes0A_0B_0C_0D,
        D_8438682C,
        gBattleScriptCmd_46,
    },
    {
        gBattleScriptCmd_4A,
        gBattleScriptCmd_00,
        Fragment62_Byte29,
        gBattleScriptCmd_08,
        D_84386894,
    },
    {
        gBattleScriptCmd_58,
        gBattleScriptCmd_00,
        D_84386BBC,
        gBattleScriptCmd_31,
        D_84386894,
    },
    {
        gBattleScriptTable_9F0,
        gBattleScriptCmd_00,
        D_84386BBC,
        D_8438682C,
        D_8438682C,
    },
    {
        gBattleScriptJump_4E,
        gBattleScriptCmd_00,
        Fragment62_Byte56,
        gBattleScriptTable_918,
        D_84386894,
    },
    {
        gBattleScriptCmd_4A,
        gBattleScriptCmd_00,
        Fragment62_Byte29,
        gBattleScriptCmd_08,
        D_84386894,
    },
    {
        gBattleScriptCmd_0D,
        gBattleScriptCmd_00,
        Fragment62_Byte05,
        D_8438685C,
        D_8438682C,
    },
    {
        gBattleScriptCmd_59,
        gBattleScriptCmd_00,
        D_84386BBC,
        D_8438682C,
        D_8438682C,
    },
    {
        gBattleScriptCmd_72,
        gBattleScriptCmd_00,
        Fragment62_Byte2C,
        D_8438682C,
        D_84386894,
    },
};

void PlaySoundEffect_Select(void) {
    PlaySoundEffect(1);
}

void PlaySoundEffect_Cancel(void) {
    PlaySoundEffect(2);
}

void PlaySoundEffect_Confirm(void) {
    PlaySoundEffect(3);
}

void PlaySoundEffect_Error(void) {
    PlaySoundEffect(8);
}

void PlayBattleMusicOrDefault(unk_BattlePlayerEntity* arg0, s16 arg1) {
    if (Pokemon_IsSpecialSpecies(arg0) != 0) {
        Audio_PlaySequence(0xC8, 2);
    } else {
        Audio_PlaySequence(arg1, 2);
    }
}

void PlayHeightBasedSoundEffect(unk_BattlePlayerEntity* arg0) {
    s16 sp1E = arg0->unk_000.unk_01A;

    GetModelHeight(arg0);
    Audio_PlaySoundEffect(0x33, sp1E, 0);
}

void ProcessEntityAudioInfo(unk_BattlePlayerEntity* arg0) {
    ProcessAudioInfo(GetPlayerDefeatMessageId(arg0), &arg0->unk_654.unk_38);
}

void TriggerMoveEvent(unk_BattlePlayerEntity* arg0, unk_D_800FCB18* arg1, s32 arg2) {
    Effect_TriggerMoveVisual(arg1->unk_5A, arg0->unk_000.unk_01A, arg2);
    HandleMoveEvent(arg1, arg1->unk_5A, arg0->unk_000.unk_01A, arg2);
}

void SetPlayerSidesFromActivePokemons(void) {
    unk_BattlePlayerEntity* ptr1 = D_84390010[0];
    unk_BattlePlayerEntity* ptr2 = D_84390010[1];
    u8 i;
    u8 sp20[4];

    sp20[0] = 0xA;
    sp20[1] = 0xA;
    sp20[2] = 0xA;
    sp20[3] = 0xA;

    sp20[ptr1->unk_720->unk_08[0]->unk_001] = 1;
    if (ptr1->unk_720->unk_01 == 2) {
        sp20[ptr1->unk_720->unk_08[1]->unk_001] = 1;
    }
    sp20[ptr2->unk_720->unk_08[0]->unk_001] = 2;
    if (ptr2->unk_720->unk_01 == 2) {
        sp20[ptr2->unk_720->unk_08[1]->unk_001] = 2;
    }

    for (i = 0; i < 4; i++) {
        if (sp20[i] == 0xA) {
            sp20[i] = 0;
        }
    }

    SetPlayerSidesAndReset(sp20[0], sp20[1], sp20[2], sp20[3]);
}

void SetTeamScoresFromActivePokemons(void) {
    unk_BattlePlayerEntity* ptr1 = D_84390010[0];
    unk_BattlePlayerEntity* ptr2 = D_84390010[1];
    u8 sp24[4];

    sp24[0] = 0;
    sp24[1] = 0;
    sp24[2] = 0;
    sp24[3] = 0;

    sp24[ptr1->unk_720->unk_08[0]->unk_001] = GetPokemonType(ptr1->unk_720->unk_08[0]);
    if (ptr1->unk_720->unk_01 == 2) {
        sp24[ptr1->unk_720->unk_08[1]->unk_001] = GetPokemonType(ptr1->unk_720->unk_08[1]);
    }

    sp24[ptr2->unk_720->unk_08[0]->unk_001] = GetPokemonType(ptr2->unk_720->unk_08[0]);
    if (ptr2->unk_720->unk_01 == 2) {
        sp24[ptr2->unk_720->unk_08[1]->unk_001] = GetPokemonType(ptr2->unk_720->unk_08[1]);
    }
    SetTeamScores(sp24[0], sp24[1], sp24[2], sp24[3]);
}

void ProcessBattleMenuSelection(void) {
    switch (gBattleContext.unk_0000) {
        case 0:
            switch (gBattleContext.unk_0001) {
                case 0:
                    ProcessMenuSelection(0, 0xE);
                    break;

                case 1:
                    ProcessMenuSelection(0, 0xA);
                    break;

                case 2:
                    ProcessMenuSelection(0, 0xB);
                    break;

                case 3:
                    ProcessMenuSelection(0, 6);
                    break;

                case 4:
                    ProcessMenuSelection(0, 5);
                    break;

                case 5:
                    ProcessMenuSelection(0, 4);
                    break;

                case 6:
                    ProcessMenuSelection(0, 0);
                    break;

                case 7:
                    ProcessMenuSelection(0, 0xC);
                    break;

                case 8:
                    ProcessMenuSelection(0, 0xC);
                    break;
            }
            break;

        case 1:
            ProcessMenuSelection(gBattleContext.unk_0003, 0xA);
            break;

        case 2:
            ProcessMenuSelection(gBattleContext.unk_0003, 0xB);
            break;

        case 3:
            switch (gBattleContext.unk_0002) {
                case 0:
                    ProcessMenuSelection(gBattleContext.unk_0003, 6);
                    break;

                case 1:
                    ProcessMenuSelection(gBattleContext.unk_0003, 7);
                    break;

                case 2:
                    ProcessMenuSelection(gBattleContext.unk_0003, 8);
                    break;

                case 3:
                    ProcessMenuSelection(gBattleContext.unk_0003, 9);
                    break;
            }
            break;

        case 4:
            ProcessMenuSelection(gBattleContext.unk_0003, 5);
            break;

        case 5:
            ProcessMenuSelection(gBattleContext.unk_0003, 4);
            break;

        case 6:
            switch (gBattleContext.unk_0002) {
                case 0:
                    ProcessMenuSelection(gBattleContext.unk_0003, 0);
                    break;

                case 1:
                    ProcessMenuSelection(gBattleContext.unk_0003, 1);
                    break;

                case 2:
                    ProcessMenuSelection(gBattleContext.unk_0003, 2);
                    break;

                case 3:
                    ProcessMenuSelection(gBattleContext.unk_0003, 3);
                    break;
            }
            break;

        case 7:
            if (gBattleContext.unk_0002 == 9) {
                ProcessMenuSelection(5, 0xD);
            } else if (gBattleContext.unk_0002 == 8) {
                ProcessMenuSelection(gBattleContext.unk_0003, 0xD);
            } else {
                ProcessMenuSelection((gBattleContext.unk_0002 * 4) + gBattleContext.unk_0003, 0xC);
            }
            break;

        case 8:
            ProcessMenuSelection(gBattleContext.unk_0003, 0xF);
            break;

        case 10:
            switch (gBattleContext.unk_0001) {
                case 0:
                    ProcessMenuSelection(0xFF, 0xE);
                    break;

                case 1:
                    ProcessMenuSelection(0xFF, 0xA);
                    break;

                case 2:
                    ProcessMenuSelection(0xFF, 0xB);
                    break;

                case 3:
                    ProcessMenuSelection(0xFF, 6);
                    break;

                case 4:
                    ProcessMenuSelection(0xFF, 5);
                    break;

                case 5:
                    ProcessMenuSelection(0xFF, 4);
                    break;

                case 6:
                    ProcessMenuSelection(0xFF, 0);
                    break;

                case 7:
                    ProcessMenuSelection(0xFF, 0xC);
                    break;

                case 8:
                    ProcessMenuSelection(0xFF, 0xC);
                    break;
            }
            break;

        case 9:
            ProcessMenuSelection(0, 0x10);
            break;
    }
}

void RenderBattleMenuSelection(void) {
    switch (gBattleContext.unk_0000) {
        case 16:
            ResultScreen_SetAnimation(1);
            break;

        case 0:
            switch (gBattleContext.unk_0001) {
                case 0:
                    func_8004BA88(0, 0xE);
                    break;

                case 1:
                    func_8004BA88(0, 0xA);
                    break;

                case 2:
                    func_8004BA88(0, 0xB);
                    break;

                case 3:
                    func_8004BA88(0, 6);
                    break;

                case 4:
                    func_8004BA88(0, 5);
                    break;

                case 5:
                    func_8004BA88(0, 4);
                    break;

                case 6:
                    func_8004BA88(0, 0);
                    break;

                case 7:
                    func_8004BA88(0, 0xC);
                    break;

                case 8:
                    func_8004BA88(0, 0xC);
                    break;
            }
            break;

        case 1:
            func_8004BA88(gBattleContext.unk_0003, 0xA);
            break;

        case 2:
            func_8004BA88(gBattleContext.unk_0003, 0xB);
            break;

        case 3:
            switch (gBattleContext.unk_0002) {
                case 0:
                    func_8004BA88(gBattleContext.unk_0003, 6);
                    break;

                case 1:
                    func_8004BA88(gBattleContext.unk_0003, 7);
                    break;

                case 2:
                    func_8004BA88(gBattleContext.unk_0003, 8);
                    break;

                case 3:
                    func_8004BA88(gBattleContext.unk_0003, 9);
                    break;
            }
            break;

        case 4:
            func_8004BA88(gBattleContext.unk_0003, 5);
            break;

        case 5:
            func_8004BA88(gBattleContext.unk_0003, 4);
            break;

        case 6:
            switch (gBattleContext.unk_0002) {
                case 0:
                    func_8004BA88(gBattleContext.unk_0003, 0);
                    break;

                case 1:
                    func_8004BA88(gBattleContext.unk_0003, 1);
                    break;

                case 2:
                    func_8004BA88(gBattleContext.unk_0003, 2);
                    break;

                case 3:
                    func_8004BA88(gBattleContext.unk_0003, 3);
                    break;
            }
            break;

        case 7:
            if (gBattleContext.unk_0002 == 9) {
                func_8004BA88(5, 0xD);
            } else if (gBattleContext.unk_0002 == 8) {
                func_8004BA88(gBattleContext.unk_0003, 0xD);
            } else {
                func_8004BA88((gBattleContext.unk_0002 * 4) + gBattleContext.unk_0003, 0xC);
            }
            break;

        case 8:
            func_8004BA88(gBattleContext.unk_0003, 0xF);
            break;

        case 10:
            switch (gBattleContext.unk_0001) {
                case 0:
                    func_8004BA88(0xFF, 0xE);
                    break;

                case 1:
                    func_8004BA88(0xFF, 0xA);
                    break;

                case 2:
                    func_8004BA88(0xFF, 0xB);
                    break;

                case 3:
                    func_8004BA88(0xFF, 6);
                    break;

                case 4:
                    func_8004BA88(0xFF, 5);
                    break;

                case 5:
                    func_8004BA88(0xFF, 4);
                    break;

                case 6:
                    func_8004BA88(0xFF, 0);
                    break;

                case 7:
                    func_8004BA88(0xFF, 0xC);
                    break;

                case 8:
                    func_8004BA88(0xFF, 0xC);
                    break;
            }
            break;

        case 9:
            func_8004BA88(0, 0x10);
            break;
    }
}

void PlayBattleSoundEffect(unk_BattlePlayerEntity* arg0, s32 arg1) {
    s16 sp1E = arg0->unk_000.unk_01A;

    if ((Pokemon_IsSpecialSpecies(arg0) != 0) && (arg1 == 0x32)) {
        Audio_PlaySoundEffect(0x32, 0xC8, 0);
    } else if (arg1 == 0x14) {
        Audio_PlaySoundEffect(0x14, 0, 0);
    } else if (arg1 == 0x12) {
        Audio_PlaySoundEffect(0x12, 0, 0);
    } else if (arg1 == 0x32) {
        Audio_PlaySoundEffect(0x32, sp1E, 0);
    } else if (arg1 == 0x21) {
        Audio_PlaySoundEffect(0x21, 0, 0);
    } else if (arg1 == 0x13) {
        Audio_PlaySoundEffect(0x13, 0, 0);
    } else if (arg1 == 0x1E) {
        Audio_PlaySoundEffect(0x1E, 0, 0);
    } else if (arg1 == 0x1F) {
        Audio_PlaySoundEffect(0x1F, 0, 0);
    } else if (arg1 == 0x20) {
        Audio_PlaySoundEffect(0x20, 0, 0);
    }
}

void ExecuteStateFunction(s16 arg0) {
    gParticleTexture_Default = gParticleEffectPrimaryId;
    gStateFunctionTable[arg0]();
    if (gParticleEffectSecondaryId != 0xFF) {
        gParticleTexture_Default = gParticleEffectSecondaryId;
        gStateFunctionTable[arg0]();
    }
}

void ExecuteParticleEffect(s16 arg0) {
    gParticleTexture_Default = gParticleEffectPrimaryId;
    gParticleStateFunctionTable[arg0]();
}

void RegisterStateCallbacks(func_D_84390300 arg0, func_D_84390320 arg1) {
    if (gStateCallbackSlot >= 8) {
        gStateCallbackSlot = 0;
    }

    if (gCameraCallbackFuncs[gStateCallbackSlot]) {}

    gCameraCallbackFuncs[gStateCallbackSlot] = arg0;
    gCameraUpdateFuncs[gStateCallbackSlot] = arg1;
    gStateCallbackSlot++;
}

void RunActionScript(s32 arg0, s32 arg1, s32 arg2) {
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
            ExecuteStateFunction(*sp2C);
            gStateCallbackTable[*sp2C]();
            RegisterStateCallbacks(gStateEnterCallbackTable[*sp2C], gStateExitCallbackTable[*sp2C]);
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
            ExecuteParticleEffect(*sp2C);
            gParticleCallbackTable[*sp2C]();
            RegisterStateCallbacks(gParticleEnterCallbackTable[*sp2C], gParticleExitCallbackTable[*sp2C]);
            sp2C++;
        }
    }
}

void ProcessPendingActionScripts(void) {
    if (gPendingActionScriptFlag0 != 0) {
        ParticleSystem_ResetSpawnOffset2();
        RunActionScript(gCurrentActionScriptId, gCurrentActionScriptSubIndex, gPendingActionScriptFlag0);
        gPendingActionScriptFlag0 = 0;
    }

    if (gPendingActionScriptFlag1 != 0) {
        RunActionScript(gCurrentActionScriptAltId, gCurrentActionScriptSubId, gPendingActionScriptFlag1);
        gPendingActionScriptFlag1 = 0;
    }

    if (gPendingActionScriptFlag2 != 0) {
        RunActionScript(gWaterEffectParam, gWaterEffectTimerMax, gPendingActionScriptFlag2);
        gPendingActionScriptFlag2 = 0;
    }

    if (gPendingActionScriptFlag3 != 0) {
        RunActionScript(gCurrentActionScriptMode, 4, gPendingActionScriptFlag3);
        gPendingActionScriptFlag3 = 0;
    }
}

void MainUpdateLoop(UNUSED CameraStruct* arg0) {
    Timer_UpdateCounters();
    ProcessPendingActionScripts();
    Particles_UpdateAll();
    func_843592E0();
}

void SetActionScriptSubIndex(u8 arg0) {
    gCurrentActionScriptSubIndex = arg0;
}

u8 GetActionScriptSubIndex(void) {
    return gCurrentActionScriptType;
}

void SetActionScriptMode(u8 arg0) {
    gCurrentActionScriptMode = arg0;
}

u8 GetActionScriptMode(void) {
    return gCurrentActionScriptMode;
}

s16 GetActionScriptId(void) {
    return gCurrentActionScriptId;
}

void InitActionScript(s32 arg0, unk_BattlePlayerEntity* arg1, unk_BattlePlayerEntity* arg2, s16 arg3, s16 arg4) {
    SetActionScriptSubIndex(0);
    gPendingActionScriptFlag0 = 1;
    gCurrentActionScriptId = arg0;
    gPanelDrawCount = 0;
    gParticleEffectPrimaryId = arg3;
    gParticleEffectSecondaryId = arg4;
    gParticleEffectEntityA = arg1;
    gParticleEffectData_42 = arg1;
    gParticleEffectEntityB = arg2;
}

void InitActionScriptSimple(s32 arg0, unk_BattlePlayerEntity* arg1, unk_BattlePlayerEntity* arg2, s16 arg3, s16 arg4) {
    InitActionScript(arg0, arg1, arg2, arg3, arg4);
}

void InitDualTargetActionScript(s32 arg0, unk_BattlePlayerEntity* arg1, unk_BattlePlayerEntity* arg2, s16 arg3, s16 arg4) {
    InitActionScript(arg0, arg1, arg2, arg3, arg4);
    SetActionScriptSubIndex(2);
    gParticleEffectEntityA = arg2;
    gPendingActionScriptFlag0 = 2;
}

void InitActionScriptMode1(s32 arg0, unk_BattlePlayerEntity* arg1, unk_BattlePlayerEntity* arg2, s16 arg3, s16 arg4) {
    InitActionScript(arg0, arg1, arg2, arg3, arg4);
    SetActionScriptSubIndex(1);
}

void InitActionScriptMode3(s32 arg0, unk_BattlePlayerEntity* arg1, unk_BattlePlayerEntity* arg2, s16 arg3, s16 arg4) {
    InitActionScript(arg0, arg1, arg2, arg3, arg4);
    SetActionScriptSubIndex(3);
}

void InitSingleEntityActionScript(s32 arg0, unk_BattlePlayerEntity* arg1) {
    gPendingActionScriptFlag1 = 2;
    gCurrentActionScriptAltId = arg0;
    gCurrentActionScriptSubId = 6;
    gParticleEffectPrimaryId = 0xFF;
    gParticleEffectSecondaryId = 0xFF;
    gParticleEffectEntityA = arg1;
    gParticleEffectData_42 = arg1;
    gParticleEffectEntityB = arg1;
}

void InitSingleEntityActionScriptVariant(s32 arg0, unk_BattlePlayerEntity* arg1) {
    InitSingleEntityActionScript(arg0, arg1);
    gPendingActionScriptFlag1 = 1;
    gCurrentActionScriptSubId = 5;
}

void func_8432C748(s32 arg0, unk_BattlePlayerEntity* arg1) {
    InitSingleEntityActionScript(arg0, arg1);
}

void InitWaterEffect(s32 arg0) {
    gPendingActionScriptFlag2 = 1;
    gWaterEffectTimerMax = 9;
    gWaterEffectParam = arg0;
    gParticleEffectPrimaryId = 0xFF;
    gParticleEffectSecondaryId = 0xFF;
}

void Battle_ApplyAnimChannelEffect(u8 arg0, unk_BattlePlayerEntity* arg1) {
    gPendingActionScriptFlag3 = 1;
    SetActionScriptMode(arg0);
    gParticleEffectEntityA = arg1;
    gParticleEffectPrimaryId = 0xFF;
    gParticleEffectSecondaryId = 0xFF;
    if (arg0 == 3) {
        gParticleEffectPrimaryId = 7;
    }
}

void RunParticleEffectScript(u8 arg0, unk_BattlePlayerEntity* arg1) {
    ParticleNode_TriggerByEntity(arg0, arg1);
}

void LoadWaterTexturesFromList(arg1_func_80019420* arg0) {
    if (arg0 != NULL) {
        do {
            if (arg0->unk_02 != 0) {
                gWaterTexture[arg0->unk_02] = arg0->unk_04;
                arg0++;
            }
        } while (arg0->unk_00 != 0);
    }
}

void InitWaterTextures(void) {
    s32 i;

    // clang-format off
    for (i = 0; i < 256; i++) { gWaterTexture[i] = NULL; }
    // clang-format on

    LoadWaterTexturesFromList(func_80019EA0(0));
}

void BuildMessageString(s16 arg0) {
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

void SetMessageFromId(unk_D_800AE540_1194* arg0, s16 arg1) {
    if (arg1 != 0xFF) {
        BuildMessageString(arg1);
        arg0->unk_1D |= 0x80;
        arg0->unk_20 = gMessageBuffer;
        arg0->unk_24 = gMessageStringLists;
    }
}

void SetMessageFromAltTable(unk_D_800AE540_1194* arg0, s16 arg1) {
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

void ProcessWaterTextureLists(void) {
    s32 i = 0;
    arg1_func_80019420* var_v0;
    arg1_func_80019420** var_s1 = gMessageStringLists;

    while (*var_s1 != NULL) {
        var_v0 = *var_s1;
        if (i) {}
        LoadWaterTexturesFromList(var_v0);
        var_s1++;
        i++;
    }
}

void ResetWaterEffect(unk_D_800AE540_1194* arg0) {
    arg0->unk_1D &= ~0x10;
    ProcessWaterTextureLists();
}

void InitGraphNodePools(void) {
    s32 i;

    for (i = 0; i < 16; i++) {
        Graph_AddToRootList0(&D_843903D0[i]);
        gGraphNodeUsed[i] = 0;
    }

    for (i = 0; i < 4; i++) {
        Graph_AddToRootList1(&gParticleNodePool[i]);
        gParticleNodeUsed[i] = 0;
    }
}

ParticleEffectInstance* GetGraphNodeData(Fragment2_1GraphNode* arg0) {
    return arg0->unk_000.unk_14;
}

Fragment2_1GraphNode* AllocateGraphNode(ParticleEffectInstance* arg0) {
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

void FreeGraphNode(Fragment2_1GraphNode* arg0) {
    s32 i;

    for (i = 0; i < 16; i++) {
        if (arg0 == &D_843903D0[i]) {
            break;
        }
    }

    if (i != 16) {
        gGraphNodeUsed[i] = 0;
        GraphNode_ClearCallback(arg0);
    }
}

Fragment2_1GraphNode* AllocateParticleNode(ParticleEffectInstance* arg0) {
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
        Particle_SetFlag(arg0, 0x400);
        sp1C->unk_000.unk_14 = arg0;
    } else {
        sp1C = NULL;
    }
    return sp1C;
}

void FreeParticleNode(Fragment2_1GraphNode* arg0) {
    s32 i;

    for (i = 0; i < 4; i++) {
        if (arg0 == &gParticleNodePool[i]) {
            break;
        }
    }

    if (i != 4) {
        gParticleNodeUsed[i] = 0;
        GraphNode_ClearCallback(arg0);
    }
}

void InitWaterAnimNode(Fragment2_1GraphNode* arg0, s16 arg1, s16 arg2) {
    GraphNode_InitChild(arg0, 0, 0, gWaterTexture[arg1]);
    Anim_SetChannel(arg0, 0, gWaterTexture[arg2], 0x10000);
}

void SetAnimChannelBase(Fragment2_1GraphNode* arg0, s16 arg1) {
    Anim_SetChannelBase(arg0, arg1);
}

void InitGraphNodeTexture(Fragment2_1GraphNode* arg0, s16 arg1) {
    GraphNode_InitChild(arg0, 0, 0, gWaterTexture[arg1]);
}

void SetAnimChannel(Fragment2_1GraphNode* arg0, s16 arg1) {
    Anim_SetChannel(arg0, 0, gWaterTexture[arg1], 0x10000);
}

void InitReverseAnimNode(Fragment2_1GraphNode* arg0, s16 arg1) {
    Anim_SetChannel(arg0, 0, gWaterTexture[arg1], -0x10000);
    Anim_SetChannelBase(arg0, arg0->unk_040.unk_04->unk_0A - 1);
}

s32 IsAnimChannelFinished(Fragment2_1GraphNode* arg0) {
    s32 ret = 0;

    if (arg0->unk_040.unk_08 == 0) {
        ret = 1;
    }
    return ret;
}

void ClearCameraCallbacks(UNUSED CameraStruct* arg0) {
    s32 i;

    for (i = 0; i < 8; i++) {
        if ((gCameraCallbackFuncs[i] != NULL) && (gCameraCallbackFuncs[i]() != 0)) {
            gCameraCallbackFuncs[i] = NULL;
            gCameraUpdateFuncs[i] = 0;
        }
    }
}

void RunCameraCallbacks(UNUSED CameraStruct* arg0) {
    s32 i;

    for (i = 0; i < 8; i++) {
        if (gCameraUpdateFuncs[i] != NULL) {
            gCameraUpdateFuncs[i]();
        }
    }
}

void UpdateCameraGlobals(CameraStruct* arg0) {
    gParticleScaleFactor.unk_0C = arg0;
    gParticleCameraInfo = &gParticleScaleFactor.unk_10;

    Matrix_Copy(&gParticleCameraInfo->unk_00, &arg0->unk_60.mtxf);
    Vec3f_Copy(&gParticleCameraInfo->unk_40, &arg0->unk_60.eye);
    Vec3f_Copy(&gParticleCameraInfo->unk_4C, &arg0->unk_60.at);
    GetCameraPitchYawFromAtToEye(&gParticleCameraInfo->unk_70, &gParticleCameraInfo->unk_72);
    GetCameraPitchYawFromEyeToAt(&gParticleCameraInfo->unk_76, &gParticleCameraInfo->unk_78);
    Vec3f_GetDirection(&gParticleCameraInfo->unk_58, gParticleCameraInfo->unk_40, gParticleCameraInfo->unk_4C);
    Vec3f_GetDirection(&gParticleCameraInfo->unk_64, gParticleCameraInfo->unk_4C, gParticleCameraInfo->unk_40);
}

s32 HandleCameraMode(s32 arg0, CameraStruct* arg1) {
    switch (arg0) {
        case 1:
        case 3:
        case 4:
            break;

        case 0:
            InitGameState();
            break;

        case 2:
            UpdateCameraGlobals(arg1);
            MainUpdateLoop(arg1);
            ClearCameraCallbacks(arg1);
            break;

        case 5:
            Ui_DrawPanel(arg1);
            break;
    }

    return 0;
}

void InitGameState(void) {
    ParticlePools_Allocate();
    ResetGameGlobals();
}

void ResetGameGlobals(void) {
    s32 i;

    gParticleEffectEntityA = NULL;
    gWaterEffectCounter = 0;
    gParticleScaleFactor.unk_00.x = 1.0f;
    gParticleScaleFactor.unk_00.y = 1.0f;
    gParticleScaleFactor.unk_00.z = 1.0f;
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

    Vec3f_Set(&gCameraPosOffset, 0.0f, 0.0f, 0.0f);
    Vec3s_Set(&gCameraRotOffset, 0, 0, 0);
    Vec3s_Set(&gCameraTargetOffset, 0, 0, 0);
    Vec3f_Set(&gCameraLookAtPos, 0.0f, 0.0f, 0.0f);
    Vec3s_Set(&gCameraAngles, 0, 0, 0);
    InitWaterTextures();
    InitGraphNodePools();
    gGraphNodePoolInitFlag = 0;
    gParticleNodePoolInitFlag = 0;
    ParticleSystem_ClearResetLock();
}

void GetCameraOffsetPosition(Vec3f* arg0, f32 arg1) {
    arg0->x = gParticleCameraInfo->unk_40.x + (arg1 * gParticleCameraInfo->unk_58.x);
    arg0->y = gParticleCameraInfo->unk_40.y + (arg1 * gParticleCameraInfo->unk_58.y);
    arg0->z = gParticleCameraInfo->unk_40.z + (arg1 * gParticleCameraInfo->unk_58.z);
}

void GetCameraPitchYawFromEyeToAt(s16* arg0, s16* arg1) {
    CameraStruct* temp_v0 = GetBattleCamera();
    f32 sp20 = temp_v0->unk_60.eye.x - temp_v0->unk_60.at.x;
    f32 sp1C = temp_v0->unk_60.eye.y - temp_v0->unk_60.at.y;
    f32 sp18 = temp_v0->unk_60.eye.z - temp_v0->unk_60.at.z;

    *arg0 = MathUtil_Atan2s(sqrtf(SQ(sp20) + SQ(sp18)), sp1C);
    *arg1 = MathUtil_Atan2s(sp18, sp20);
}

void GetCameraYawFromEyeToAt(s16* arg0) {
    CameraStruct* temp_v0 = GetBattleCamera();
    f32 x = temp_v0->unk_60.eye.x - temp_v0->unk_60.at.x;
    f32 z = temp_v0->unk_60.eye.z - temp_v0->unk_60.at.z;

    *arg0 = MathUtil_Atan2s(z, x);
}

void GetCameraPitchYawFromAtToEye(s16* arg0, s16* arg1) {
    CameraStruct* temp_v0 = GetBattleCamera();
    f32 sp20 = temp_v0->unk_60.at.x - temp_v0->unk_60.eye.x;
    f32 sp1C = temp_v0->unk_60.at.y - temp_v0->unk_60.eye.y;
    f32 sp18 = temp_v0->unk_60.at.z - temp_v0->unk_60.eye.z;

    *arg0 = MathUtil_Atan2s(sqrtf(SQ(sp20) + SQ(sp18)), sp1C);
    *arg1 = MathUtil_Atan2s(sp18, sp20);
}

void GetCameraYawFromAtToEye(s16* arg0) {
    CameraStruct* temp_v0 = GetBattleCamera();
    f32 x = temp_v0->unk_60.at.x - temp_v0->unk_60.eye.x;
    f32 z = temp_v0->unk_60.at.z - temp_v0->unk_60.eye.z;

    *arg0 = MathUtil_Atan2s(z, x);
}

void GetCameraStoredPitchYaw(s16* arg0, s16* arg1) {
    *arg0 = gParticleCameraInfo->unk_76;
    *arg1 = gParticleCameraInfo->unk_78;
}

void GetCameraStoredYaw(s16* arg0) {
    *arg0 = gParticleCameraInfo->unk_78;
}

void GetCameraStoredRollPitch(s16* arg0, s16* arg1) {
    *arg0 = gParticleCameraInfo->unk_70;
    *arg1 = gParticleCameraInfo->unk_72;
}

void GetCameraStoredPitch(s16* arg0) {
    *arg0 = gParticleCameraInfo->unk_72;
}
