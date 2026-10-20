#include "src/fragments/particle_math/particle_math.h"

static u8 gParticleColorPalette[][3] = {
    { 0, 0, 0 },          { 0, 0x14, 0x1E },    { 0, 0x23, 0x2D },    { 0x40, 0x40, 0x40 }, { 0x46, 0x55, 0x55 },
    { 0x6E, 0x6E, 0x6E }, { 0x80, 0x80, 0x80 }, { 0xB4, 0xC8, 0xC8 }, { 0xC8, 0xFF, 0xFF }, { 0xE6, 0xF0, 0xF0 },
    { 0xFF, 0xFF, 0xFF }, { 0xFF, 0, 0 },       { 0xF0, 0x28, 0x28 }, { 0xFF, 0x80, 0x80 }, { 0xAA, 0x32, 0 },
    { 0x96, 0, 0 },       { 0x64, 0, 0 },       { 0x46, 0x14, 0 },    { 0x32, 0xA, 0xA },   { 0xFF, 0x80, 0 },
    { 0xFF, 0xA0, 0 },    { 0xF0, 0xDC, 0xD8 }, { 0xFF, 0xC8, 0xC8 }, { 0xFF, 0x78, 0xC8 }, { 0xFF, 0, 0x64 },
    { 0xFF, 0xFF, 0 },    { 0xFF, 0xFF, 0x64 }, { 0xFF, 0xFF, 0x9B }, { 0xFF, 0xFF, 0xC8 }, { 0xFF, 0xC8, 0 },
    { 0xD7, 0xFF, 0x73 }, { 0xC8, 0xC8, 0 },    { 0x96, 0x96, 0x32 }, { 0x64, 0x64, 0 },    { 0x80, 0x80, 0x50 },
    { 0, 0xFF, 0 },       { 0x28, 0xFF, 0x28 }, { 0x64, 0xFF, 0x64 }, { 0x80, 0xFF, 0x80 }, { 0x9B, 0xFF, 0xC8 },
    { 0x50, 0x64, 0x3C }, { 0xC8, 0xFF, 0 },    { 0xC8, 0xC8, 0 },    { 0x96, 0xB4, 0 },    { 0, 0x96, 0 },
    { 0, 0x64, 0 },       { 0, 0, 0xFF },       { 0x32, 0x32, 0xFF }, { 0, 0x32, 0xFF },    { 0, 0x64, 0xFF },
    { 0, 0x78, 0xFF },    { 0x20, 0x7C, 0xFF }, { 0x80, 0x80, 0xFF }, { 0x64, 0xC8, 0xFF }, { 0, 0xFF, 0xFF },
    { 0x64, 0xFF, 0xFF }, { 0xB4, 0xFF, 0xFF }, { 0xC8, 0xFF, 0xFF }, { 0x46, 0x64, 0x78 }, { 0xFF, 0, 0xFF },
    { 0xFF, 0x32, 0xFF }, { 0xD7, 0, 0xFF },    { 0x96, 0, 0xC8 },    { 0x64, 0, 0xFF },    { 0xFF, 0x32, 0xFF },
    { 0x78, 0x1E, 0x78 },
};

u8 gParticleColorScheme1[] = {
    0x0C, 0x19, 0x23, 0x36, 0x2F, 0x3B,
};

static u8 gParticleColorScheme2[] = {
    0x17, 0x19, 0x25, 0x23, 0x35, 0x14,
};

static u8 gParticleRandomColorIndices[] = {
    0x0A, 0x19, 0x36, 0x24, 0x16,
};

static u8 gColorPairTable[][2] = {
    { 0x19, 0xC },  { 0xA, 0x3B },  { 0, 0xC },     { 8, 0x31 },    { 0x2A, 0x23 }, { 0x19, 0x1F }, { 0x36, 0x32 },
    { 0x19, 0xB },  { 0x3B, 0x3C }, { 0xC, 0xC },   { 0xA, 0x1C },  { 0xA, 0x14 },  { 0xA, 0x35 },  { 0xA, 0x24 },
    { 0xA, 0xC },   { 0x19, 0x14 }, { 0x19, 0xC },  { 0x15, 0xA },  { 0xE, 0x11 },  { 8, 0x37 },    { 0x36, 0x30 },
    { 0xA, 0x3F },  { 0xB, 0 },     { 0xA, 0x19 },  { 0xA, 0x36 },  { 0x37, 0x31 }, { 0x19, 0xB },  { 0, 0x3B },
    { 0, 1 },       { 0xA, 0xA },   { 4, 2 },       { 0x29, 0x2C }, { 0xA, 0 },     { 0xC, 0x10 },  { 0x1B, 0x3B },
    { 0xA, 0x27 },  { 0x14, 0xB },  { 0xA, 0x1C },  { 0xA, 0x35 },  { 0xA, 8 },     { 0xA, 0x31 },  { 0x1C, 0x1A },
    { 0x1A, 0xB },  { 0x14, 0xF },  { 0x1A, 0x14 }, { 0x14, 0 },    { 0xB, 0 },     { 0x36, 0x2D }, { 0x23, 0x2C },
    { 0x1A, 0x20 }, { 0x21, 0x21 }, { 0xA, 0xA },   { 0x19, 0x2C }, { 0x3B, 0x3C }, { 0x2B, 0xA },  { 0x3E, 0xA },
    { 0x19, 0x23 }, { 0xA, 0x23 },  { 0xB, 0 },     { 0xA, 0x1A },  { 0xA, 0x35 },  { 0xA, 0x35 },  { 0xA, 0x17 },
    { 0xA, 0x3F },  { 0xA, 0x31 },  { 0xA, 0x17 },  { 0xA, 0x13 },  { 0x3C, 0x3E }, { 0x15, 0x15 }, { 0x3E, 0x3E },
    { 0x23, 0x23 }, { 0x13, 0xC },  { 0x19, 0x13 }, { 0x16, 0xC },  { 0x1C, 0x19 }, { 0x39, 0x2F }, { 0xA, 0x39 },
    { 0x38, 0x35 }, { 0x38, 0x39 }, { 0x1C, 0x1A }, { 9, 0x35 },
};

void ParticleGfx_LoadTextureCallbackRgba16_32x32(UNUSED ParticleEffectInstance* arg0, u8* texture) {
    ParticleGfx_LoadTextureRgba16(texture, 32, 32);
}

void ParticleGfx_LoadTextureCallbackIa8Frame_32x32(ParticleEffectInstance* arg0, u8* texture) {
    ParticleGfx_LoadTextureIa8(&texture[arg0->rampValue * 32 * 32], 32, 32);
}

void ParticleGfx_LoadTextureCallbackIa8_32x32(UNUSED ParticleEffectInstance* arg0, u8* texture) {
    ParticleGfx_LoadTextureIa8(texture, 32, 32);
}

void ParticleGfx_LoadTextureCallbackIa8Frame_32x64(ParticleEffectInstance* arg0, u8* texture) {
    ParticleGfx_LoadTextureIa8(&texture[arg0->rampValue * 32 * 64], 32, 64);
}

void ParticleGfx_LoadTextureCallbackI4_32x32(UNUSED ParticleEffectInstance* arg0, u8* texture) {
    ParticleGfx_LoadTextureI4Alias(texture, 32, 32);
}

void ParticleGfx_LoadTextureCallbackI4ParticleFrame_32x32(ParticleEffectInstance* arg0, u8* texture) {
    ParticleGfx_LoadTextureI4Alias(&texture[arg0->rampValue * (32 * 32 / 2)], 32, 32);
}

void ParticleGfx_LoadTextureCallbackI4FrameMod4_32x32(UNUSED ParticleEffectInstance* arg0, u8* texture) {
    ParticleGfx_LoadTextureI4Alias(&texture[gTimerMask2 * (32 * 32 / 2)], 32, 32);
}

void ParticleGfx_LoadTextureCallbackI4FrameDiv2Mod4_32x32(UNUSED ParticleEffectInstance* arg0, u8* texture) {
    ParticleGfx_LoadTextureI4Alias(&texture[(gTimerShift1 & 3) * (32 * 32 / 2)], 32, 32);
}

void ParticleGfx_LoadTextureCallbackI4FrameDiv4Mod4_32x32(UNUSED ParticleEffectInstance* arg0, u8* texture) {
    ParticleGfx_LoadTextureI4Alias(&texture[(gTimerShift2 & 3) * (32 * 32 / 2)], 32, 32);
}

void ParticleGfx_LoadTextureCallbackI4FrameDiv2Mod8_32x32(UNUSED ParticleEffectInstance* arg0, u8* texture) {
    ParticleGfx_LoadTextureI4Alias(&texture[(gTimerShift1 & 7) * (32 * 32 / 2)], 32, 32);
}

void ParticleGfx_LoadTextureCallbackI4TileFrameDiv2Mod8_24x24(UNUSED ParticleEffectInstance* arg0, u8* texture) {
    ParticleGfx_LoadTextureTileI4Alias(&texture[(gTimerShift1 & 7) * (24 * 24 / 2)], 24, 24);
}

void ParticleGfx_LoadTextureCallbackI4TileParticleFrame_24x24(ParticleEffectInstance* arg0, u8* texture) {
    ParticleGfx_LoadTextureTileI4Alias(&texture[arg0->rampValue * (24 * 24 / 2)], 24, 24);
}

void ParticleGfx_LoadTextureCallbackI4FrameMod10_32x64(UNUSED ParticleEffectInstance* arg0, u8* texture) {
    ParticleGfx_LoadTextureI4Alias(&texture[(gTimerCounter % 10) * (32 * 64 / 2)], 32, 64);
}

void ParticleGfx_LoadTextureCallbackI4ParticleFrame_32x64(ParticleEffectInstance* arg0, u8* texture) {
    ParticleGfx_LoadTextureI4Alias(&texture[arg0->rampValue * (32 * 64 / 2)], 32, 64);
}

void ParticleGfx_LoadTextureCallbackI4_64x64(UNUSED ParticleEffectInstance* arg0, u8* texture) {
    ParticleGfx_LoadTextureI4Alias(texture, 64, 64);
}

void ParticleGfx_LoadTextureCallbackI4FrameMod8_64x64(UNUSED ParticleEffectInstance* arg0, u8* texture) {
    ParticleGfx_LoadTextureI4Alias(&texture[gTimerMask3 * (64 * 64 / 2)], 64, 64);
}

void ParticleGfx_LoadTextureCallbackI4FrameDiv2Mod8_64x64(UNUSED ParticleEffectInstance* arg0, u8* texture) {
    ParticleGfx_LoadTextureI4Alias(&texture[(gTimerShift1 & 7) * (64 * 64 / 2)], 64, 64);
}

void ParticleGfx_LoadTextureCallbackI4ParticleFrame_64x64(ParticleEffectInstance* arg0, u8* texture) {
    ParticleGfx_LoadTextureI4Alias(&texture[arg0->rampValue * (64 * 64 / 2)], 64, 64);
}

void ParticleGfx_LoadTextureCallbackI4WrapST_64x64(UNUSED ParticleEffectInstance* arg0, u8* texture) {
    ParticleGfx_LoadTextureI4WrapST(texture, 64, 64);
}

void ParticleGfx_LoadTextureCallbackIa8WrapST_64x64(UNUSED ParticleEffectInstance* arg0, u8* texture) {
    ParticleGfx_LoadTextureIa8WrapST(texture, 64, 64);
}

void ParticleGfx_DrawBillboardPrim(ParticleEffectInstance* arg0, CameraStruct* arg1) {
    ParticleGfx_SetPrimColorTextureCombine(arg0->prim_r, arg0->prim_g, arg0->prim_b, arg0->prim_a);
    ParticleGfx_DrawModelQuad(arg1, arg0->unk_2C, arg0->unk_1C, gMatrix_UITransform);
}

void ParticleGfx_DrawBillboardPrimEnv(ParticleEffectInstance* arg0, CameraStruct* arg1) {
    ParticleGfx_SetPrimEnvColorCombine(arg0->prim_r, arg0->prim_g, arg0->prim_b, arg0->env_r, arg0->env_g, arg0->env_b, arg0->prim_a);
    ParticleGfx_DrawModelQuad(arg1, arg0->unk_2C, arg0->unk_1C, gVtx_UI_MediumQuad);
}

s32 ParticleGfx_DrawBillboardDoubleSided(ParticleEffectInstance* arg0, UNUSED CameraStruct* arg1) {
    gSPClearGeometryMode(gDisplayListHead++, G_CULL_BACK);

    ParticleGfx_SetPrimEnvColorCombine(arg0->prim_r, arg0->prim_g, arg0->prim_b, arg0->env_r, arg0->env_g, arg0->env_b, arg0->prim_a);
    ParticleGfx_DrawTransformedQuad(arg0->unk_2C, arg0->unk_94, arg0->unk_1C, gVtx_UI_MediumQuad);

    gSPSetGeometryMode(gDisplayListHead++, G_CULL_BACK);
}

void ParticleGfx_DrawBillboardDefaultQuad(ParticleEffectInstance* arg0, CameraStruct* arg1) {
    ParticleGfx_DrawModelQuad(arg1, arg0->unk_2C, arg0->unk_1C, gMatrix_UITransform);
}

void ParticleGfx_DrawBillboardPrimEnvQuad(ParticleEffectInstance* arg0, CameraStruct* arg1) {
    ParticleGfx_SetPrimEnvColorCombine(arg0->prim_r, arg0->prim_g, arg0->prim_b, arg0->env_r, arg0->env_g, arg0->env_b, arg0->prim_a);
    ParticleGfx_DrawModelQuad(arg1, arg0->unk_2C, arg0->unk_1C, gMatrix_UITransform);
}

void ParticleGfx_DrawBillboardTextureAlphaRotatedQuad(ParticleEffectInstance* arg0, CameraStruct* arg1) {
    ParticleGfx_SetTextureAlphaCombine(arg0->prim_a);
    ParticleGfx_DrawModelQuadRotated(arg1, arg0->unk_2C, arg0->unk_1C, gVtx_UI_ColorQuad, arg0->unk_94.z);
}

void ParticleGfx_DrawBillboardOffsetQuad(ParticleEffectInstance* arg0, CameraStruct* arg1) {
    ParticleGfx_DrawModelQuad(arg1, arg0->unk_2C, arg0->unk_1C, gVtx_UI_RectHorizontal);
}

void ParticleGfx_DrawBillboardPrimEnvNoiseQuad(ParticleEffectInstance* arg0, CameraStruct* arg1) {
    ParticleGfx_SetPrimEnvNoiseCombine(arg0->prim_r, arg0->prim_g, arg0->prim_b, arg0->env_r, arg0->env_g, arg0->env_b, arg0->prim_a);
    ParticleGfx_DrawModelQuad(arg1, arg0->unk_2C, arg0->unk_1C, gMatrix_UITransform);
}

void ParticleGfx_DrawBillboardPrimEnvRotatedQuad(ParticleEffectInstance* arg0, CameraStruct* arg1) {
    ParticleGfx_SetPrimEnvColorCombine(arg0->prim_r, arg0->prim_g, arg0->prim_b, arg0->env_r, arg0->env_g, arg0->env_b, arg0->prim_a);
    ParticleGfx_DrawModelQuadRotated(arg1, arg0->unk_2C, arg0->unk_1C, gMatrix_UITransform, arg0->unk_94.z);
}

void ParticleGfx_DrawBillboardPrimEnvRotatedTriangle(ParticleEffectInstance* arg0, CameraStruct* arg1) {
    ParticleGfx_SetPrimEnvColorCombine(arg0->prim_r, arg0->prim_g, arg0->prim_b, arg0->env_r, arg0->env_g, arg0->env_b, arg0->prim_a);
    ParticleGfx_DrawModelTriangleRotated(arg1, arg0->unk_2C, arg0->unk_1C, gVtx_UI_TriangleDown, arg0->unk_94.z);
}

void ParticleGfx_DrawBillboardPrimEnvQuadVariantA(ParticleEffectInstance* arg0, CameraStruct* arg1) {
    ParticleGfx_SetPrimEnvColorCombine(arg0->prim_r, arg0->prim_g, arg0->prim_b, arg0->env_r, arg0->env_g, arg0->env_b, arg0->prim_a);
    ParticleGfx_DrawModelQuad(arg1, arg0->unk_2C, arg0->unk_1C, gVtx_UI_RectTall);
}

void ParticleGfx_DrawBillboardPrimEnvQuadVariantB(ParticleEffectInstance* arg0, CameraStruct* arg1) {
    ParticleGfx_SetPrimEnvColorCombine(arg0->prim_r, arg0->prim_g, arg0->prim_b, arg0->env_r, arg0->env_g, arg0->env_b, arg0->prim_a);
    ParticleGfx_DrawModelQuad(arg1, arg0->unk_2C, arg0->unk_1C, gVtx_UI_Square);
}

void ParticleGfx_DrawBillboardPrimEnvQuadVariantC(ParticleEffectInstance* arg0, CameraStruct* arg1) {
    ParticleGfx_SetPrimEnvColorCombine(arg0->prim_r, arg0->prim_g, arg0->prim_b, arg0->env_r, arg0->env_g, arg0->env_b, arg0->prim_a);
    ParticleGfx_DrawModelQuad(arg1, arg0->unk_2C, arg0->unk_1C, gVtx_UI_RectWide);
}

void ParticleGfx_DrawBillboardPrimEnvComposite(ParticleEffectInstance* arg0, CameraStruct* arg1) {
    ParticleGfx_SetPrimEnvColorCombine(arg0->prim_r, arg0->prim_g, arg0->prim_b, arg0->env_r, arg0->env_g, arg0->env_b, arg0->prim_a);
    ParticleGfx_DrawModelQuad(arg1, arg0->unk_2C, arg0->unk_1C, gVtx_UI_GridQuad);
}

s32 ParticleGfx_DrawBillboardPrimEnvTriangleDoubleSided(ParticleEffectInstance* arg0, UNUSED CameraStruct* arg1) {
    gSPClearGeometryMode(gDisplayListHead++, G_CULL_BACK);

    ParticleGfx_SetPrimEnvColorCombine(arg0->prim_r, arg0->prim_g, arg0->prim_b, arg0->env_r, arg0->env_g, arg0->env_b, arg0->prim_a);
    ParticleGfx_DrawTransformedQuad(arg0->unk_2C, arg0->unk_94, arg0->unk_1C, gVtx_UI_GridQuad);

    gSPSetGeometryMode(gDisplayListHead++, G_CULL_BACK);
}

void ParticleGfx_DrawBillboardPrimEnvTransformedQuad(ParticleEffectInstance* arg0, CameraStruct* arg1) {
    ParticleGfx_SetPrimEnvColorCombine(arg0->prim_r, arg0->prim_g, arg0->prim_b, arg0->env_r, arg0->env_g, arg0->env_b, arg0->prim_a);
    ParticleGfx_DrawTransformedQuad(arg0->unk_2C, arg0->unk_94, arg0->unk_1C, gGroundQuadVtx);
}

void ParticleGfx_CopyPaletteRgb(u8* arg0, u16 arg1) {
    arg0[0] = gParticleColorPalette[arg1][0];
    arg0[1] = gParticleColorPalette[arg1][1];
    arg0[2] = gParticleColorPalette[arg1][2];
}

void ParticleGfx_CopyPalettePairRgb(u8* arg0, u8* arg1, u16 arg2) {
    u8 sp1C = gColorPairTable[arg2][0];
    u8 sp1E = gColorPairTable[arg2][1];

    ParticleGfx_CopyPaletteRgb(arg0, sp1C);
    ParticleGfx_CopyPaletteRgb(arg1, sp1E);
}

void ParticleGfx_RecolorPrim(ParticleEffectInstance* arg0, u16 arg1) {
    arg0->prim_r = gParticleColorPalette[arg1][0];
    arg0->prim_g = gParticleColorPalette[arg1][1];
    arg0->prim_b = gParticleColorPalette[arg1][2];
}

void ParticleGfx_RecolorEnv(ParticleEffectInstance* arg0, u16 arg1) {
    arg0->env_r = gParticleColorPalette[arg1][0];
    arg0->env_g = gParticleColorPalette[arg1][1];
    arg0->env_b = gParticleColorPalette[arg1][2];
}

void ParticleGfx_RecolorPrimEnvFromPalettePair(ParticleEffectInstance* arg0, u16 arg1) {
    u8 sp1C = gColorPairTable[arg1][0];
    u8 sp1E = gColorPairTable[arg1][1];

    ParticleGfx_RecolorPrim(arg0, sp1C);
    ParticleGfx_RecolorEnv(arg0, sp1E);
}

void ParticleGfx_RecolorPrimFromPaletteSetA(ParticleEffectInstance* arg0, s16 arg1) {
    ParticleGfx_RecolorPrim(arg0, gParticleColorScheme1[arg1]);
}

void ParticleGfx_RecolorEnvFromPaletteSetA(ParticleEffectInstance* arg0, s16 arg1) {
    ParticleGfx_RecolorEnv(arg0, gParticleColorScheme1[arg1]);
}

void ParticleGfx_RecolorPrimFromPaletteSetB(ParticleEffectInstance* arg0, s16 arg1) {
    ParticleGfx_RecolorPrim(arg0, gParticleColorScheme2[arg1]);
}

void ParticleGfx_RecolorEnvFromPaletteSetB(ParticleEffectInstance* arg0, s16 arg1) {
    ParticleGfx_RecolorEnv(arg0, gParticleColorScheme2[arg1]);
}

void ParticleGfx_RecolorPrimEnvFromPaletteSetA(ParticleEffectInstance* arg0, s16 arg1) {
    u8 sp1F = gParticleColorScheme1[arg1];

    ParticleGfx_RecolorPrim(arg0, sp1F);
    ParticleGfx_RecolorEnv(arg0, sp1F);
}

void ParticleGfx_RecolorPrimEnvFromPaletteSetB(ParticleEffectInstance* arg0, s16 arg1) {
    u8 sp1F = gParticleColorScheme2[arg1];

    ParticleGfx_RecolorPrim(arg0, sp1F);
    ParticleGfx_RecolorEnv(arg0, sp1F);
}

void ParticleGfx_RecolorPrimRandomPalette(ParticleEffectInstance* arg0) {
    ParticleGfx_RecolorPrim(arg0, gParticleRandomColorIndices[(ParticleMath_RandomRange(5) & 0xFF)]);
}

void ParticleGfx_RecolorEnvRandomPalette(ParticleEffectInstance* arg0) {
    ParticleGfx_RecolorEnv(arg0, gParticleRandomColorIndices[ParticleMath_RandomRange(5) & 0xFF]);
}

s32 ParticleGfx_ApproachPrimPalette(ParticleEffectInstance* arg0, u16 arg1, u8 arg2) {
    s32 sp2C = 0;
    s32 sp28;
    s32 sp24;
    s32 sp20;
    u8 sp1C[3];

    ParticleGfx_CopyPaletteRgb(sp1C, arg1);

    sp28 = Particle_ApproachPrimR(arg0, sp1C[0], arg2);
    sp24 = Particle_ApproachPrimG(arg0, sp1C[1], arg2);
    sp20 = Particle_ApproachPrimB(arg0, sp1C[2], arg2);

    if ((sp28 * sp24 * sp20) != 0) {
        sp2C = 1;
    }
    return sp2C;
}

s32 ParticleGfx_ApproachEnvPalette(ParticleEffectInstance* arg0, u16 arg1, u8 arg2) {
    s32 sp2C = 0;
    s32 sp28;
    s32 sp24;
    s32 sp20;
    u8 sp1C[3];

    ParticleGfx_CopyPaletteRgb(&sp1C, arg1);

    sp28 = Particle_ApproachEnvR(arg0, sp1C[0], arg2);
    sp24 = Particle_ApproachEnvG(arg0, sp1C[1], arg2);
    sp20 = Particle_ApproachEnvB(arg0, sp1C[2], arg2);

    if ((sp28 * sp24 * sp20) != 0) {
        sp2C = 1;
    }
    return sp2C;
}

s32 ParticleGfx_ApproachPrimEnvPalettePair(ParticleEffectInstance* arg0, u16 arg1, u8 arg2) {
    s32 sp44 = 0;
    s32 sp40;
    s32 sp3C;
    s32 sp38;
    s32 sp34;
    s32 sp30;
    s32 sp2C;
    u8 sp28[3];
    u8 sp24[3];

    ParticleGfx_CopyPalettePairRgb(sp28, sp24, arg1);

    sp40 = Particle_ApproachPrimR(arg0, sp28[0], arg2);
    sp3C = Particle_ApproachPrimG(arg0, sp28[1], arg2);
    sp38 = Particle_ApproachPrimB(arg0, sp28[2], arg2);
    sp34 = Particle_ApproachEnvR(arg0, sp24[0], arg2);
    sp30 = Particle_ApproachEnvG(arg0, sp24[1], arg2);
    sp2C = Particle_ApproachEnvB(arg0, sp24[2], arg2);

    if ((sp40 * sp3C * sp38 * sp34 * sp30 * sp2C) != 0) {
        sp44 = 1;
    }
    return sp44;
}
