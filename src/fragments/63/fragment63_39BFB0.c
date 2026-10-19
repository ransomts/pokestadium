#include "fragment63.h"
#include "src/12D80.h"
#include "src/19840.h"
#include "src/1C720.h"
#include "src/20470.h"
#include "src/4CBC0.h"
#include "src/6BC0.h"
#include "src/F420.h"
#include "src/math_util.h"
#include "src/memmap.h"
#include "src/memory.h"

static s8 gHealthBarSpriteLookup[] = {
    0xFF, 0x00, 0x01, 0x02, 0x06, 0x07, 0x08, 0xFF, 0xFF, 0x03, 0x04, 0x05, 0x09, 0x0A, 0x0B, 0xFF,
};
static Vtx gHealthBarQuadVtx[] = {
    VTX(-32, 48, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF),       VTX(-32, 16, 0, 0, 1024, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(32, 16, 0, 2048, 1024, 0xFF, 0xFF, 0xFF, 0xFF),  VTX(32, 48, 0, 2048, 0, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(-32, 16, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF),       VTX(-32, -16, 0, 0, 1024, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(32, -16, 0, 2048, 1024, 0xFF, 0xFF, 0xFF, 0xFF), VTX(32, 16, 0, 2048, 0, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(-32, -16, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF),      VTX(-32, -48, 0, 0, 1024, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(32, -48, 0, 2048, 1024, 0xFF, 0xFF, 0xFF, 0xFF), VTX(32, -16, 0, 2048, 0, 0xFF, 0xFF, 0xFF, 0xFF),
};
static Gfx D_84B14CE0[] = {
    gsSPSetGeometryMode(G_CULL_BACK),
    gsDPSetCombineLERP(0, 0, 0, TEXEL0, 0, 0, 0, SHADE, 0, 0, 0, COMBINED, COMBINED, 0, PRIM_LOD_FRAC, 0),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsSPVertex(gHealthBarQuadVtx, 12, 0),
    gsDPLoadTextureBlock(0x0F000000, G_IM_FMT_RGBA, G_IM_SIZ_16b, 64, 32, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                         G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsDPLoadTextureBlock(0x0F001000, G_IM_FMT_RGBA, G_IM_SIZ_16b, 64, 32, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                         G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP2Triangles(4, 5, 6, 0, 4, 6, 7, 0),
    gsDPLoadTextureBlock(0x0F002000, G_IM_FMT_RGBA, G_IM_SIZ_16b, 64, 32, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                         G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP2Triangles(8, 9, 10, 0, 8, 10, 11, 0),
    gsSPEndDisplayList(),
};
static u32 gHealthBarNodeData[] = {
    0x17000000, 0x00000000, 0x00000000,    0x00000000, gHealthBarQuadVtx, 0x05000000, 0x22050000,
    0x00000000, 0x08000000, DrawPokemonFrontSprite, D_84B14CE0, 0x06000000, 0x01000000, 0x00000000,
};
static Vtx gHealthBarVtx[] = {
    VTX(-32, 48, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF),       VTX(-32, 16, 0, 0, 1024, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(32, 16, 0, 2048, 1024, 0xFF, 0xFF, 0xFF, 0xFF),  VTX(32, 48, 0, 2048, 0, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(-32, 16, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF),       VTX(-32, -16, 0, 0, 1024, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(32, -16, 0, 2048, 1024, 0xFF, 0xFF, 0xFF, 0xFF), VTX(32, 16, 0, 2048, 0, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(-32, -16, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF),      VTX(-32, -48, 0, 0, 1024, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(32, -48, 0, 2048, 1024, 0xFF, 0xFF, 0xFF, 0xFF), VTX(32, -16, 0, 2048, 0, 0xFF, 0xFF, 0xFF, 0xFF),
};
static Vtx gHealthBarSegmentVtx0[] = {
    VTX(-30, 45, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF),      VTX(-30, 30, 0, 0, 1024, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(0, 30, 0, 2048, 1024, 0xFF, 0xFF, 0xFF, 0xFF),  VTX(0, 45, 0, 2048, 0, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(0, 45, 0, 2048, 0, 0xFF, 0xFF, 0xFF, 0xFF),     VTX(0, 30, 0, 2048, 1024, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(30, 30, 0, 4096, 1024, 0xFF, 0xFF, 0xFF, 0xFF), VTX(30, 45, 0, 4096, 0, 0xFF, 0xFF, 0xFF, 0xFF),
};
static Vtx gHealthBarSegmentVtx1[] = {
    VTX(-30, 30, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF),      VTX(-30, 15, 0, 0, 1024, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(0, 15, 0, 2048, 1024, 0xFF, 0xFF, 0xFF, 0xFF),  VTX(0, 30, 0, 2048, 0, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(0, 30, 0, 2048, 0, 0xFF, 0xFF, 0xFF, 0xFF),     VTX(0, 15, 0, 2048, 1024, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(30, 15, 0, 4096, 1024, 0xFF, 0xFF, 0xFF, 0xFF), VTX(30, 30, 0, 4096, 0, 0xFF, 0xFF, 0xFF, 0xFF),
};
static Vtx gHealthBarSegmentVtx2[] = {
    VTX(-30, 15, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF),     VTX(-30, 0, 0, 0, 1024, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(0, 0, 0, 2048, 1024, 0xFF, 0xFF, 0xFF, 0xFF),  VTX(0, 15, 0, 2048, 0, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(0, 15, 0, 2048, 0, 0xFF, 0xFF, 0xFF, 0xFF),    VTX(0, 0, 0, 2048, 1024, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(30, 0, 0, 4096, 1024, 0xFF, 0xFF, 0xFF, 0xFF), VTX(30, 15, 0, 4096, 0, 0xFF, 0xFF, 0xFF, 0xFF),
};
static Vtx gHealthBarSegmentVtx3[] = {
    VTX(-30, 0, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF),        VTX(-30, -15, 0, 0, 1024, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(0, -15, 0, 2048, 1024, 0xFF, 0xFF, 0xFF, 0xFF),  VTX(0, 0, 0, 2048, 0, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(0, 0, 0, 2048, 0, 0xFF, 0xFF, 0xFF, 0xFF),       VTX(0, -15, 0, 2048, 1024, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(30, -15, 0, 4096, 1024, 0xFF, 0xFF, 0xFF, 0xFF), VTX(30, 0, 0, 4096, 0, 0xFF, 0xFF, 0xFF, 0xFF),
};
static Vtx gHealthBarSegmentVtx4[] = {
    VTX(-30, -15, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF),      VTX(-30, -30, 0, 0, 1024, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(0, -30, 0, 2048, 1024, 0xFF, 0xFF, 0xFF, 0xFF),  VTX(0, -15, 0, 2048, 0, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(0, -15, 0, 2048, 0, 0xFF, 0xFF, 0xFF, 0xFF),     VTX(0, -30, 0, 2048, 1024, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(30, -30, 0, 4096, 1024, 0xFF, 0xFF, 0xFF, 0xFF), VTX(30, -15, 0, 4096, 0, 0xFF, 0xFF, 0xFF, 0xFF),
};
static Vtx gHealthBarSegmentVtx5[] = {
    VTX(-30, -30, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF),      VTX(-30, -45, 0, 0, 1024, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(0, -45, 0, 2048, 1024, 0xFF, 0xFF, 0xFF, 0xFF),  VTX(0, -30, 0, 2048, 0, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(0, -30, 0, 2048, 0, 0xFF, 0xFF, 0xFF, 0xFF),     VTX(0, -45, 0, 2048, 1024, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(30, -45, 0, 4096, 1024, 0xFF, 0xFF, 0xFF, 0xFF), VTX(30, -30, 0, 4096, 0, 0xFF, 0xFF, 0xFF, 0xFF),
};
static Vtx gHealthBarBackVtx[] = {
    VTX(-30, 30, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(-30, -30, 0, 0, 2048, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(30, -30, 0, 2048, 2048, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(30, 30, 0, 2048, 0, 0xFF, 0xFF, 0xFF, 0xFF),
};
static Gfx gHealthBarDL_Segments[] = {
    gsSPSetGeometryMode(G_CULL_BACK),
    gsDPSetCombineLERP(0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, COMBINED, 0, PRIM_LOD_FRAC, 0),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsSPVertex(gHealthBarVtx, 12, 0),
    gsDPLoadTextureBlock(0x0E000000, G_IM_FMT_RGBA, G_IM_SIZ_16b, 64, 32, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                         G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsDPLoadTextureBlock(0x0E001000, G_IM_FMT_RGBA, G_IM_SIZ_16b, 64, 32, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                         G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP2Triangles(4, 5, 6, 0, 4, 6, 7, 0),
    gsDPLoadTextureBlock(0x0E002000, G_IM_FMT_RGBA, G_IM_SIZ_16b, 64, 32, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                         G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP2Triangles(8, 9, 10, 0, 8, 10, 11, 0),
    gsSPVertex(gHealthBarSegmentVtx0, 8, 0),
    gsDPLoadTextureTile(0x0F000000, G_IM_FMT_RGBA, G_IM_SIZ_16b, 128, 0, 0, 0, 63, 31, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsDPLoadTextureTile(0x0F000000, G_IM_FMT_RGBA, G_IM_SIZ_16b, 128, 0, 64, 0, 127, 31, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP2Triangles(4, 5, 6, 0, 4, 6, 7, 0),
    gsSPVertex(gHealthBarSegmentVtx1, 8, 0),
    gsDPLoadTextureTile(0x0F002000, G_IM_FMT_RGBA, G_IM_SIZ_16b, 128, 0, 0, 0, 63, 31, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsDPLoadTextureTile(0x0F002000, G_IM_FMT_RGBA, G_IM_SIZ_16b, 128, 0, 64, 0, 127, 31, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP2Triangles(4, 5, 6, 0, 4, 6, 7, 0),
    gsSPVertex(gHealthBarSegmentVtx2, 8, 0),
    gsDPLoadTextureTile(0x0F004000, G_IM_FMT_RGBA, G_IM_SIZ_16b, 128, 0, 0, 0, 63, 31, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsDPLoadTextureTile(0x0F004000, G_IM_FMT_RGBA, G_IM_SIZ_16b, 128, 0, 64, 0, 127, 31, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP2Triangles(4, 5, 6, 0, 4, 6, 7, 0),
    gsSPVertex(gHealthBarSegmentVtx3, 8, 0),
    gsDPLoadTextureTile(0x0F006000, G_IM_FMT_RGBA, G_IM_SIZ_16b, 128, 0, 0, 0, 63, 31, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsDPLoadTextureTile(0x0F006000, G_IM_FMT_RGBA, G_IM_SIZ_16b, 128, 0, 64, 0, 127, 31, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP2Triangles(4, 5, 6, 0, 4, 6, 7, 0),
    gsSPVertex(gHealthBarSegmentVtx4, 8, 0),
    gsDPLoadTextureTile(0x0F008000, G_IM_FMT_RGBA, G_IM_SIZ_16b, 128, 0, 0, 0, 63, 31, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsDPLoadTextureTile(0x0F008000, G_IM_FMT_RGBA, G_IM_SIZ_16b, 128, 0, 64, 0, 127, 31, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP2Triangles(4, 5, 6, 0, 4, 6, 7, 0),
    gsSPVertex(gHealthBarSegmentVtx5, 8, 0),
    gsDPLoadTextureTile(0x0F00A000, G_IM_FMT_RGBA, G_IM_SIZ_16b, 128, 0, 0, 0, 63, 31, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsDPLoadTextureTile(0x0F00A000, G_IM_FMT_RGBA, G_IM_SIZ_16b, 128, 0, 64, 0, 127, 31, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP2Triangles(4, 5, 6, 0, 4, 6, 7, 0),
    gsSPEndDisplayList(),
};
static Gfx gHealthBarBackDL[] = {
    gsSPSetGeometryMode(G_CULL_BACK),
    gsDPSetCombineLERP(TEXEL0, 0, ENVIRONMENT, 0, TEXEL0, 0, ENVIRONMENT, 0, 0, 0, 0, COMBINED, COMBINED, 0,
                       PRIM_LOD_FRAC, 0),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsSPVertex(gHealthBarBackVtx, 4, 0),
    gsDPSetEnvColor(255, 50, 20, 160),
    gsDPLoadTextureBlock_4b(D_3017F00, G_IM_FMT_I, 64, 64, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                            G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSPEndDisplayList(),
};
static u32 gHealthBarNodeData_Status[] = {
    0x17000000, 0x00000000,    0x00000000, 0x00000000, gHealthBarVtx, 0x05000000, 0x22050000, 0x00000000,
    0x08000000, DrawPokemonStatusIcon, gHealthBarDL_Segments, 0x22050000, gHealthBarBackDL, 0x25000000, 0x06000000, 0x01000000,
};
static Vtx gItemIconVtx[] = {
    VTX(-32, 48, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF),       VTX(-32, 16, 0, 0, 1024, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(32, 16, 0, 2048, 1024, 0xFF, 0xFF, 0xFF, 0xFF),  VTX(32, 48, 0, 2048, 0, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(-32, 16, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF),       VTX(-32, -16, 0, 0, 1024, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(32, -16, 0, 2048, 1024, 0xFF, 0xFF, 0xFF, 0xFF), VTX(32, 16, 0, 2048, 0, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(-32, -16, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF),      VTX(-32, -48, 0, 0, 1024, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(32, -48, 0, 2048, 1024, 0xFF, 0xFF, 0xFF, 0xFF), VTX(32, -16, 0, 2048, 0, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(-20, 30, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF),       VTX(-20, -10, 0, 0, 1280, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(20, -10, 0, 1280, 1280, 0xFF, 0xFF, 0xFF, 0xFF), VTX(20, 30, 0, 1280, 0, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(-24, -20, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF),      VTX(-24, -44, 0, 0, 1024, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(24, -44, 0, 2048, 1024, 0xFF, 0xFF, 0xFF, 0xFF), VTX(24, -20, 0, 2048, 0, 0xFF, 0xFF, 0xFF, 0xFF),
};
static Vtx gItemIconBackVtx[] = {
    VTX(-20, 30, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(-20, -10, 0, 0, 2048, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(20, -10, 0, 2048, 2048, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(20, 30, 0, 2048, 0, 0xFF, 0xFF, 0xFF, 0xFF),
};
static Gfx gItemIconDL[] = {
    gsSPSetGeometryMode(G_CULL_BACK),
    gsDPSetCombineLERP(0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, COMBINED, 0, PRIM_LOD_FRAC, 0),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsSPVertex(gItemIconVtx, 20, 0),
    gsDPLoadTextureBlock(0x0E000000, G_IM_FMT_RGBA, G_IM_SIZ_16b, 64, 32, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                         G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsDPLoadTextureBlock(0x0E001000, G_IM_FMT_RGBA, G_IM_SIZ_16b, 64, 32, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                         G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP2Triangles(4, 5, 6, 0, 4, 6, 7, 0),
    gsDPLoadTextureBlock(0x0E002000, G_IM_FMT_RGBA, G_IM_SIZ_16b, 64, 32, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                         G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP2Triangles(8, 9, 10, 0, 8, 10, 11, 0),
    gsDPLoadTextureBlock(0x0F000000, G_IM_FMT_RGBA, G_IM_SIZ_16b, 40, 40, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                         G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP2Triangles(12, 13, 14, 0, 12, 14, 15, 0),
    gsDPLoadTextureBlock(D_3016F00, G_IM_FMT_RGBA, G_IM_SIZ_16b, 64, 32, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                         G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP2Triangles(16, 17, 18, 0, 16, 18, 19, 0),
    gsSPEndDisplayList(),
};
static Gfx gItemIconBackDL[] = {
    gsSPSetGeometryMode(G_CULL_BACK),
    gsDPSetCombineLERP(TEXEL0, 0, ENVIRONMENT, 0, TEXEL0, 0, ENVIRONMENT, 0, 0, 0, 0, COMBINED, COMBINED, 0,
                       PRIM_LOD_FRAC, 0),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsSPVertex(gItemIconBackVtx, 4, 0),
    gsDPSetEnvColor(255, 50, 20, 160),
    gsDPLoadTextureBlock_4b(D_3017F00, G_IM_FMT_I, 64, 64, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                            G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSPEndDisplayList(),
};
static u32 gItemIconNodeData[] = {
    0x17000000, 0x00000000,    0x00000000, 0x00000000, gItemIconVtx, 0x05000000, 0x22050000, 0x00000000,
    0x08000000, DrawPokemonItemIcon, gItemIconDL, 0x22050000, gItemIconBackDL, 0x25000000, 0x06000000, 0x01000000,
};
static Vtx gHPBarSegmentVtx[] = {
    VTX(-32, 24, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF),      VTX(-32, 0, 0, 0, 768, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(32, 0, 0, 2048, 768, 0xFF, 0xFF, 0xFF, 0xFF),   VTX(32, 24, 0, 2048, 0, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(-32, 0, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF),       VTX(-32, -24, 0, 0, 768, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(32, -24, 0, 2048, 768, 0xFF, 0xFF, 0xFF, 0xFF), VTX(32, 0, 0, 2048, 0, 0xFF, 0xFF, 0xFF, 0xFF),
};
static Vtx gHPBarSegmentVtx0[] = {
    VTX(-30, 22, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF),     VTX(-30, 7, 0, 0, 1024, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(0, 7, 0, 2048, 1024, 0xFF, 0xFF, 0xFF, 0xFF),  VTX(0, 22, 0, 2048, 0, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(0, 22, 0, 2048, 0, 0xFF, 0xFF, 0xFF, 0xFF),    VTX(0, 7, 0, 2048, 1024, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(30, 7, 0, 4096, 1024, 0xFF, 0xFF, 0xFF, 0xFF), VTX(30, 22, 0, 4096, 0, 0xFF, 0xFF, 0xFF, 0xFF),
};
static Vtx gHPBarSegmentVtx1[] = {
    VTX(-30, 7, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF),       VTX(-30, -7, 0, 0, 1024, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(0, -7, 0, 2048, 1024, 0xFF, 0xFF, 0xFF, 0xFF),  VTX(0, 7, 0, 2048, 0, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(0, 7, 0, 2048, 0, 0xFF, 0xFF, 0xFF, 0xFF),      VTX(0, -7, 0, 2048, 1024, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(30, -7, 0, 4096, 1024, 0xFF, 0xFF, 0xFF, 0xFF), VTX(30, 7, 0, 4096, 0, 0xFF, 0xFF, 0xFF, 0xFF),
};
static Vtx gHPBarSegmentVtx2[] = {
    VTX(-30, -7, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF),       VTX(-30, -22, 0, 0, 1024, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(0, -22, 0, 2048, 1024, 0xFF, 0xFF, 0xFF, 0xFF),  VTX(0, -7, 0, 2048, 0, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(0, -7, 0, 2048, 0, 0xFF, 0xFF, 0xFF, 0xFF),      VTX(0, -22, 0, 2048, 1024, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(30, -22, 0, 4096, 1024, 0xFF, 0xFF, 0xFF, 0xFF), VTX(30, -7, 0, 4096, 0, 0xFF, 0xFF, 0xFF, 0xFF),
};
static Vtx gHPBarBackVtx[] = {
    VTX(-22, 22, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(-22, -22, 0, 0, 2048, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(22, -22, 0, 2048, 2048, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(22, 22, 0, 2048, 0, 0xFF, 0xFF, 0xFF, 0xFF),
};
static Gfx gHPBarSegmentDL[] = {
    gsSPSetGeometryMode(G_CULL_BACK),
    gsDPSetCombineLERP(0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, COMBINED, 0, PRIM_LOD_FRAC, 0),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsSPVertex(gHPBarSegmentVtx, 8, 0),
    gsDPLoadTextureBlock(0x0E000000, G_IM_FMT_RGBA, G_IM_SIZ_16b, 64, 24, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                         G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsDPLoadTextureBlock(0x0E000C00, G_IM_FMT_RGBA, G_IM_SIZ_16b, 64, 24, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                         G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP2Triangles(4, 5, 6, 0, 4, 6, 7, 0),
    gsSPVertex(gHPBarSegmentVtx0, 8, 0),
    gsDPLoadTextureTile(0x0F000000, G_IM_FMT_RGBA, G_IM_SIZ_16b, 128, 0, 0, 0, 63, 31, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsDPLoadTextureTile(0x0F000000, G_IM_FMT_RGBA, G_IM_SIZ_16b, 128, 0, 64, 0, 127, 31, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP2Triangles(4, 5, 6, 0, 4, 6, 7, 0),
    gsSPVertex(gHPBarSegmentVtx1, 8, 0),
    gsDPLoadTextureTile(0x0F002000, G_IM_FMT_RGBA, G_IM_SIZ_16b, 128, 0, 0, 0, 63, 31, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsDPLoadTextureTile(0x0F002000, G_IM_FMT_RGBA, G_IM_SIZ_16b, 128, 0, 64, 0, 127, 31, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP2Triangles(4, 5, 6, 0, 4, 6, 7, 0),
    gsSPVertex(gHPBarSegmentVtx2, 8, 0),
    gsDPLoadTextureTile(0x0F004000, G_IM_FMT_RGBA, G_IM_SIZ_16b, 128, 0, 0, 0, 63, 31, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsDPLoadTextureTile(0x0F004000, G_IM_FMT_RGBA, G_IM_SIZ_16b, 128, 0, 64, 0, 127, 31, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP2Triangles(4, 5, 6, 0, 4, 6, 7, 0),
    gsSPEndDisplayList(),
};
static Gfx gHPBarBackDL[] = {
    gsSPSetGeometryMode(G_CULL_BACK),
    gsDPSetCombineLERP(TEXEL0, 0, ENVIRONMENT, 0, TEXEL0, 0, ENVIRONMENT, 0, 0, 0, 0, COMBINED, COMBINED, 0,
                       PRIM_LOD_FRAC, 0),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsSPVertex(gHPBarBackVtx, 4, 0),
    gsDPSetEnvColor(255, 50, 20, 160),
    gsDPLoadTextureBlock_4b(D_3017F00, G_IM_FMT_I, 64, 64, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                            G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSPEndDisplayList(),
};
static u32 gHPBarNodeData[] = {
    0x17000000, 0x00000000, 0x00000000, 0x00000000, gHPBarSegmentVtx, 0x05000000, 0x1B000000,    0x00000000,
    0x00000000, 0x00180000, 0x05000000, 0x22050000, 0x00000000, 0x08000000, DrawHPBarSegment, gHPBarSegmentDL,
    0x22050000, gHPBarBackDL, 0x25000000, 0x06000000, 0x06000000, 0x01000000,
};
static u32 gHPBarNodeData_Alt[] = {
    0x17000000, 0x00000000, 0x00000000, 0x00000000, gHPBarSegmentVtx, 0x05000000, 0x1B000000,    0x00000000,
    0x00000000, 0xFFE80000, 0x05000000, 0x22050000, 0x00000000, 0x08000000, DrawHPBarSegment, gHPBarSegmentDL,
    0x22050000, gHPBarBackDL, 0x25000000, 0x06000000, 0x06000000, 0x01000000,
};
static Vtx gHPBarSegmentVtxAlt[] = {
    VTX(-32, 24, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF),       VTX(-32, 0, 0, 0, 768, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(32, 0, 0, 2048, 768, 0xFF, 0xFF, 0xFF, 0xFF),    VTX(32, 24, 0, 2048, 0, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(-32, 0, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF),        VTX(-32, -24, 0, 0, 768, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(32, -24, 0, 2048, 768, 0xFF, 0xFF, 0xFF, 0xFF),  VTX(32, 0, 0, 2048, 0, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(-14, 20, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF),       VTX(-14, -8, 0, 0, 1280, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(14, -8, 0, 1280, 1280, 0xFF, 0xFF, 0xFF, 0xFF),  VTX(14, 20, 0, 1280, 0, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(-12, -8, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF),       VTX(-12, -20, 0, 0, 1024, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(12, -20, 0, 2048, 1024, 0xFF, 0xFF, 0xFF, 0xFF), VTX(12, -8, 0, 2048, 0, 0xFF, 0xFF, 0xFF, 0xFF),
};
static Vtx gHPBarBackVtxAlt[] = {
    VTX(-14, 20, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(-14, -8, 0, 0, 2048, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(14, -8, 0, 2048, 2048, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(14, 20, 0, 2048, 0, 0xFF, 0xFF, 0xFF, 0xFF),
};
static Gfx gHPBarSegmentDLAlt[] = {
    gsSPSetGeometryMode(G_CULL_BACK),
    gsDPSetCombineLERP(0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, COMBINED, 0, PRIM_LOD_FRAC, 0),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsSPVertex(gHPBarSegmentVtxAlt, 16, 0),
    gsDPLoadTextureBlock(0x0E000000, G_IM_FMT_RGBA, G_IM_SIZ_16b, 64, 24, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                         G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsDPLoadTextureBlock(0x0E000C00, G_IM_FMT_RGBA, G_IM_SIZ_16b, 64, 24, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                         G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP2Triangles(4, 5, 6, 0, 4, 6, 7, 0),
    gsDPLoadTextureBlock(0x0F000000, G_IM_FMT_RGBA, G_IM_SIZ_16b, 40, 40, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                         G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP2Triangles(8, 9, 10, 0, 8, 10, 11, 0),
    gsDPLoadTextureBlock(D_3016F00, G_IM_FMT_RGBA, G_IM_SIZ_16b, 64, 32, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                         G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP2Triangles(12, 13, 14, 0, 12, 14, 15, 0),
    gsSPEndDisplayList(),
};
static Gfx gHPBarBackDLAlt[] = {
    gsSPSetGeometryMode(G_CULL_BACK),
    gsDPSetCombineLERP(TEXEL0, 0, ENVIRONMENT, 0, TEXEL0, 0, ENVIRONMENT, 0, 0, 0, 0, COMBINED, COMBINED, 0,
                       PRIM_LOD_FRAC, 0),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsSPVertex(gHPBarBackVtxAlt, 4, 0),
    gsDPSetEnvColor(255, 50, 20, 160),
    gsDPLoadTextureBlock_4b(D_3017F00, G_IM_FMT_I, 64, 64, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                            G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSPEndDisplayList(),
};
static u32 gHPBarNodeDataAlt[] = {
    0x17000000, 0x00000000, 0x00000000, 0x00000000, gHPBarSegmentVtxAlt, 0x05000000, 0x1B000000,    0x00000000,
    0x00000000, 0x00180000, 0x05000000, 0x22050000, 0x00000000, 0x08000000, DrawHPBarSegmentAlt, gHPBarSegmentDLAlt,
    0x22050000, gHPBarBackDLAlt, 0x25000000, 0x06000000, 0x06000000, 0x01000000,
};
static u32 gHPBarNodeDataAlt2[] = {
    0x17000000, 0x00000000, 0x00000000, 0x00000000, gHPBarSegmentVtxAlt, 0x05000000, 0x1B000000,    0x00000000,
    0x00000000, 0xFFE80000, 0x05000000, 0x22050000, 0x00000000, 0x08000000, DrawHPBarSegmentAlt, gHPBarSegmentDLAlt,
    0x22050000, gHPBarBackDLAlt, 0x25000000, 0x06000000, 0x06000000, 0x01000000, 0x00000000,    0x00000000,
};

s32 DrawPokemonFrontSprite(s32 arg0, SimpleGfxNode* arg1) {
    unk_D_84B25A58* temp_v1;
    u8* var_a3;

    if (arg0 == 5) {
        temp_v1 = (unk_D_84B25A58*)gDefaultGraphRoot->unk_000.unk_14;
        if (temp_v1->unk_04->modelPhase == gDefaultGraphRoot->modelPhase) {
            var_a3 = temp_v1->unk_24->img_p;
        } else {
            var_a3 = temp_v1->unk_28->img_p;
        }

        gDPPipeSync(gDisplayListHead++);
        gSPSegment(gDisplayListHead++, 0x0F, (u32)var_a3 & 0x1FFFFFFF);
        gSPDisplayList(gDisplayListHead++, arg1->unk_00.unk_14);

        Gfx_ResetRenderState();
    }
    return 0;
}

s32 DrawPokemonStatusIcon(s32 arg0, SimpleGfxNode* arg1) {
    unk_D_84B25A58* temp_t1;
    s32 temp_t2;
    u8* var_a3;

    if (arg0 == 5) {
        temp_t1 = (unk_D_84B25A58*)gDefaultGraphRoot->unk_000.unk_14;
        temp_t2 = gDefaultGraphRoot->modelPhase - temp_t1->unk_04->modelPhase;
        if (temp_t2 < 4) {
            var_a3 = D_3006000;
        } else {
            var_a3 = D_3009000;
        }

        gDPPipeSync(gDisplayListHead++);
        gSPSegment(gDisplayListHead++, 0x0F, (u32)SpriteDisplay_GetImagePtr(temp_t1->unk_1C, temp_t2 - 1) & 0x1FFFFFFF);
        gSPSegment(gDisplayListHead++, 0x0E, (u32)Memmap_GetSegmentVaddr(var_a3) & 0x1FFFFFFF);
        gSPDisplayList(gDisplayListHead++, arg1->unk_00.unk_14);

        Gfx_ResetRenderState();

        if (temp_t1->unk_2C[temp_t2 - 1] != 0) {
            arg1->unk_00.unk_08->unk_01 |= 1;
        } else {
            arg1->unk_00.unk_08->unk_01 &= ~1;
        }
    }
    return 0;
}

s32 DrawPokemonItemIcon(s32 arg0, SimpleGfxNode* arg1) {
    unk_D_84B25A58* temp_a3;
    s32 temp_t0;
    u8* var_a0;

    if (arg0 == 5) {
        temp_a3 = (unk_D_84B25A58*)gDefaultGraphRoot->unk_000.unk_14;
        temp_t0 = (gDefaultGraphRoot->modelPhase - temp_a3->unk_04->modelPhase) % 8;
        if (temp_t0 < 4) {
            var_a0 = D_3006000;
        } else {
            var_a0 = D_3009000;
        }

        gDPPipeSync(gDisplayListHead++);
        gSPSegment(gDisplayListHead++, 0x0F, (u32)temp_a3->unk_20[temp_t0 - 1] & 0x1FFFFFFF);
        gSPSegment(gDisplayListHead++, 0x0E, (u32)Memmap_GetSegmentVaddr(var_a0) & 0x1FFFFFFF);
        gSPDisplayList(gDisplayListHead++, arg1->unk_00.unk_14);

        Gfx_ResetRenderState();
    }
    return 0;
}

s32 DrawHPBarSegment(s32 arg0, SimpleGfxNode* arg1) {
    u8* var_a3;
    unk_D_84B25A58* temp_t1;
    s32 temp_a1;

    if (arg0 == 5) {
        temp_t1 = (unk_D_84B25A58*)gDefaultGraphRoot->unk_000.unk_14;
        temp_a1 = gDefaultGraphRoot->modelPhase - temp_t1->unk_04->modelPhase;

        if (temp_a1 >= 0x10) {
            temp_a1 = (temp_a1 - 0x10) % 12;
        } else {
            temp_a1 = gHealthBarSpriteLookup[temp_a1];
        }

        if (temp_a1 < 6) {
            var_a3 = D_300C000;
        } else {
            var_a3 = D_300D800;
        }

        gDPPipeSync(gDisplayListHead++);
        gSPSegment(gDisplayListHead++, 0x0F, (u32)SpriteDisplay_GetImagePtr(temp_t1->unk_1C, temp_a1) & 0x1FFFFFFF);
        gSPSegment(gDisplayListHead++, 0x0E, (u32)Memmap_GetSegmentVaddr(var_a3) & 0x1FFFFFFF);
        gSPDisplayList(gDisplayListHead++, arg1->unk_00.unk_14);

        Gfx_ResetRenderState();

        if (temp_t1->unk_2C[temp_a1] != 0) {
            arg1->unk_00.unk_08->unk_01 |= 1;
        } else {
            arg1->unk_00.unk_08->unk_01 &= ~1;
        }
    }
    return 0;
}

s32 DrawHPBarSegmentAlt(s32 arg0, SimpleGfxNode* arg1) {
    s32 temp_a3;
    unk_D_84B25A58* temp_t1;
    u8* var_a0;

    if (arg0 == 5) {
        temp_t1 = (unk_D_84B25A58*)gDefaultGraphRoot->unk_000.unk_14;
        temp_a3 = gDefaultGraphRoot->modelPhase - temp_t1->unk_04->modelPhase;

        if (temp_a3 >= 0x10) {
            temp_a3 = (temp_a3 - 0x10) % 12;
        } else {
            temp_a3 = gHealthBarSpriteLookup[temp_a3];
        }

        if (temp_a3 < 6) {
            var_a0 = D_300C000;
        } else {
            var_a0 = D_300D800;
        }

        gDPPipeSync(gDisplayListHead++);
        gSPSegment(gDisplayListHead++, 0x0F, (u32)temp_t1->unk_20[temp_a3] & 0x1FFFFFFF);
        gSPSegment(gDisplayListHead++, 0x0E, (u32)Memmap_GetSegmentVaddr(var_a0) & 0x1FFFFFFF);
        gSPDisplayList(gDisplayListHead++, arg1->unk_00.unk_14);

        Gfx_ResetRenderState();
    }
    return 0;
}

void DrawPlayerHealthBars(unk_D_84B25A58* arg0, s32 arg1) {
    s32 i;
    s32 j;
    UNUSED s32 pad;
    unk_D_800AE540_0004* temp_s5;
    s32 temp_lo;
    s32 var_s0;

    for (i = 0; i < 2; i++) {
        temp_s5 = gBattleContext.unk_1194[i].unk_08[0];

        for (j = 0; j < temp_s5->unk_002; j++) {
            temp_lo = temp_s5->unk_01C[j].unk_26 * arg1;
            var_s0 = temp_s5->unk_01C[j].unk_02 * 0x64;
            if (var_s0 < temp_lo) {
                var_s0 = temp_lo;
            }
            Gfx_SetupFrameBuffer(&gDisplayListHead, arg0->unk_1C->unk_08[i * 3 + j].unk_0C);
            DrawHealthBar(4, 0xB4, 0x78, var_s0, temp_s5->unk_01C[j].unk_26 * 0x64);
        }
    }
}

void DrawDoubleBattleHealthBars(unk_D_84B25A58* arg0, s32 arg1) {
    s32 i;
    s32 j;
    s32 x;
    s32 temp_lo;
    s32 var_s0;
    unk_D_800AE540_0004* temp_s5;

    for (i = 0; i < 2; i++) {
        for (j = 0; j < 2; j++) {
            temp_s5 = gBattleContext.unk_1194[i].unk_08[j];

            if (temp_s5 != NULL) {
                for (x = 0; x < temp_s5->unk_002; x++) {
                    temp_lo = temp_s5->unk_01C[x].unk_26 * arg1;
                    var_s0 = temp_s5->unk_01C[x].unk_02 * 0x64;
                    if (var_s0 < temp_lo) {
                        var_s0 = temp_lo;
                    }
                    Gfx_SetupFrameBuffer(&gDisplayListHead, arg0->unk_1C->unk_08[(i * 6) + (j * 3) + x].unk_0C);
                    DrawHealthBar(4, 0x54, 0x78, var_s0, temp_s5->unk_01C[x].unk_26 * 0x64);
                }
            }
        }
    }
}

void SetHPBarCriticalFlag(unk_D_84B25A58* arg0, s32 arg1) {
    UNUSED s32 pad;
    unk_D_800AE540_0004* temp_s5;
    s32 temp_v0;
    s32 i;
    s32 j;

    for (i = 0; i < 2; i++) {
        temp_s5 = gBattleContext.unk_1194[i].unk_08[0];

        for (j = 0; j < temp_s5->unk_002; j++) {
            if (arg1 == temp_s5->unk_01C[j].unk_25) {
                temp_v0 = (i * 3) + j;
                arg0->unk_2C[temp_v0] = 1;
                PlayUISfx(0x0110000B, temp_v0 + 1, 0);
            }
        }
    }
}

void SetDoubleBattleHPBarCriticalFlag(unk_D_84B25A58* arg0, s32 arg1) {
    s32 i;
    s32 j;
    s32 x;
    unk_D_800AE540_0004* temp_s5;
    s32 temp_v0;

    for (i = 0; i < 2; i++) {
        for (j = 0; j < 2; j++) {
            temp_s5 = gBattleContext.unk_1194[i].unk_08[j];

            if (temp_s5 != NULL) {
                for (x = 0; x < temp_s5->unk_002; x++) {
                    if (arg1 == temp_s5->unk_01C[x].unk_25) {
                        temp_v0 = (i * 6) + (j * 3) + x;
                        arg0->unk_2C[temp_v0] = 1;
                        PlayUISfx(0x0110000B, temp_v0 + 1, 1);
                    }
                }
            }
        }
    }
}

void InitHealthBarGraphNodes(unk_D_84B25A58* arg0) {
    s32 i;

    for (i = 1; i < 7; i++) {
        GraphNode_InitChild(&arg0->unk_04[i], 0, 0, arg0->unk_08);
        arg0->unk_04[i].unk_000.unk_14 = arg0;
    }

    for (i = 1; i < 4; i++) {
        arg0->unk_04[i].unk_01E.y = 0x5800;
        Vec3f_Set(&arg0->unk_04[i].unk_024, (i * 64.0f) - 96.0f, 48.0f, -289.0f);
    }

    for (i = 0; i < 3; i++) {
        arg0->unk_04[4 + i].unk_01E.y = -0x5800;
        Vec3f_Set(&arg0->unk_04[4 + i].unk_024, (i * 64.0f) - 96.0f, -48.0f, -289.0f);
    }
}

void InitDoubleBattleHealthBarGraphNodes(unk_D_84B25A58* arg0) {
    s32 i;

    for (i = 1; i < 7; i++) {
        GraphNode_InitChild(&arg0->unk_04[8 + i], 0, 0, arg0->unk_10);
        arg0->unk_04[8 + i].unk_000.unk_14 = arg0;
        arg0->unk_04[8 + i].unk_01E.y = -0x8000;
    }

    for (i = 1; i < 4; i++) {
        Vec3f_Set(&arg0->unk_04[8 + i].unk_024, (i * 64.0f) - 96.0f, 48.0f, -289.0f);
    }

    for (i = 0; i < 3; i++) {
        Vec3f_Set(&arg0->unk_04[12 + i].unk_024, (i * 64.0f) - 96.0f, -48.0f, -289.0f);
    }
}

void InitDoubleBattleHealthBarGraphNodes_Alt(unk_D_84B25A58* arg0) {
    s32 i;

    for (i = 1; i < 4; i++) {
        GraphNode_InitChild(&arg0->unk_04[15 + i], 0, 0, arg0->unk_08);
        GraphNode_InitChild(&arg0->unk_04[18 + i], 0, 0, arg0->unk_0C);
        arg0->unk_04[15 + i].unk_000.unk_14 = arg0;
        arg0->unk_04[18 + i].unk_000.unk_14 = arg0;

        arg0->unk_04[15 + i].unk_01E.y = 0x5800;
        arg0->unk_04[18 + i].unk_01E.y = 0x5800;

        Vec3f_Set(&arg0->unk_04[15 + i].unk_024, (i * 64.0f) - 96.0f, 48.0f, -289.0f);
        Vec3f_Set(&arg0->unk_04[18 + i].unk_024, (i * 64.0f) - 96.0f, 48.0f, -289.0f);
    }

    for (i = 0; i < 3; i++) {
        GraphNode_InitChild(&arg0->unk_04[22 + i], 0, 0, arg0->unk_08);
        GraphNode_InitChild(&arg0->unk_04[25 + i], 0, 0, arg0->unk_0C);
        arg0->unk_04[22 + i].unk_000.unk_14 = arg0;
        arg0->unk_04[25 + i].unk_000.unk_14 = arg0;

        arg0->unk_04[22 + i].unk_01E.y = -0x5800;
        arg0->unk_04[25 + i].unk_01E.y = -0x5800;

        Vec3f_Set(&arg0->unk_04[22 + i].unk_024, (i * 64.0f) - 96.0f, -48.0f, -289.0f);
        Vec3f_Set(&arg0->unk_04[25 + i].unk_024, (i * 64.0f) - 96.0f, -48.0f, -289.0f);
    }
}

void InitDoubleBattleHealthBarGraphNodes_Alt2(unk_D_84B25A58* arg0) {
    s32 i;

    for (i = 1; i < 4; i++) {
        GraphNode_InitChild(&arg0->unk_04[27 + i], 0, 0, arg0->unk_10);
        GraphNode_InitChild(&arg0->unk_04[30 + i], 0, 0, arg0->unk_14);

        arg0->unk_04[27 + i].unk_000.unk_14 = arg0;
        arg0->unk_04[30 + i].unk_000.unk_14 = arg0;

        arg0->unk_04[27 + i].unk_01E.y = -0x8000;
        arg0->unk_04[30 + i].unk_01E.y = -0x8000;

        Vec3f_Set(&arg0->unk_04[27 + i].unk_024, (i * 64.0f) - 96.0f, 48.0f, -289.0f);
        Vec3f_Set(&arg0->unk_04[30 + i].unk_024, (i * 64.0f) - 96.0f, 48.0f, -289.0f);
    }

    for (i = 0; i < 3; i++) {
        GraphNode_InitChild(&arg0->unk_04[34 + i], 0, 0, arg0->unk_10);
        GraphNode_InitChild(&arg0->unk_04[37 + i], 0, 0, arg0->unk_14);
        arg0->unk_04[34 + i].unk_000.unk_14 = arg0;
        arg0->unk_04[37 + i].unk_000.unk_14 = arg0;

        arg0->unk_04[34 + i].unk_01E.y = -0x8000;
        arg0->unk_04[37 + i].unk_01E.y = -0x8000;

        Vec3f_Set(&arg0->unk_04[34 + i].unk_024, (i * 64.0f) - 96.0f, -48.0f, -289.0f);
        Vec3f_Set(&arg0->unk_04[37 + i].unk_024, (i * 64.0f) - 96.0f, -48.0f, -289.0f);
    }
}

void AnimateHealthBarSlideIn(unk_D_84B25A58* arg0, s16 arg1) {
    s16 i;

    if (arg1 == 0) {
        PlayUISfx(0x01100009, 0, 0);
    }

    if (arg1 < 0xB) {
        for (i = 0; i < 4; i++) {
            arg0->unk_04[i].unk_01E.y -= 0x800;
        }

        for (i = 4; i < 8; i++) {
            arg0->unk_04[i].unk_01E.y += 0x800;
        }

        DrawPlayerHealthBars(arg0, 0x64);
    }
}

void AnimateDoubleHealthBarSlideIn(unk_D_84B25A58* arg0, s16 arg1) {
    s16 i;

    if (arg1 == 0) {
        PlayUISfx(0x01100009, 0, 0);
    }

    if (arg1 < 0xB) {
        arg0->unk_04[0].unk_01E.y -= 0x800;
        arg0->unk_04[7].unk_01E.y += 0x800;

        for (i = 16; i < 22; i++) {
            arg0->unk_04[i].unk_01E.y -= 0x800;
        }

        for (i = 22; i < 28; i++) {
            arg0->unk_04[i].unk_01E.y += 0x800;
        }

        DrawDoubleBattleHealthBars(arg0, 0x64);
    }
}

void AnimateHealthBarDrain(unk_D_84B25A58* arg0, s16 arg1) {
    if (arg1 == 0) {
        PlayUISfx(0x0110000A, 0, 0);
    }

    if (arg1 < 0x1A) {
        DrawPlayerHealthBars(arg0, 0x64 - (arg1 * 4));
    } else if (arg1 < 0x3E) {
        if (((arg1 - 0x1A) % 6) == 0) {
            SetHPBarCriticalFlag(arg0, ((arg1 - 0x1A) / 6) + 1);
        }
    }
}

void AnimateDoubleHealthBarDrain(unk_D_84B25A58* arg0, s16 arg1) {
    if (arg1 == 0) {
        PlayUISfx(0x0110000A, 0, 0);
    }

    if (arg1 < 0x1A) {
        DrawDoubleBattleHealthBars(arg0, 0x64 - (arg1 * 4));
    } else if (arg1 < 0x3E) {
        if (((arg1 - 0x1A) % 3) == 0) {
            SetDoubleBattleHPBarCriticalFlag(arg0, ((arg1 - 0x1A) / 3) + 1);
        }
    }
}

void AnimateHealthBarDrainFast(unk_D_84B25A58* arg0, s16 arg1) {
    if (arg1 == 0) {
        PlayUISfx(0x0110000A, 0, 0);
    }

    if (arg1 < 0x15) {
        DrawPlayerHealthBars(arg0, 0x64 - (arg1 * 5));
    } else if (arg1 < 0x33) {
        if (((arg1 - 0x15) % 5) == 0) {
            SetHPBarCriticalFlag(arg0, ((arg1 - 0x15) / 5) + 1);
        }
    }
}

void AnimateDoubleHealthBarDrainFast(unk_D_84B25A58* arg0, s16 arg1) {
    if (arg1 == 0) {
        PlayUISfx(0x0110000A, 0, 0);
    }

    if (arg1 < 0x15) {
        DrawDoubleBattleHealthBars(arg0, 0x64 - (arg1 * 5));
    } else if (arg1 < 0x39) {
        if (((arg1 - 0x15) % 3) == 0) {
            SetDoubleBattleHPBarCriticalFlag(arg0, ((arg1 - 0x15) / 3) + 1);
        }
    }
}

void AnimateHealthBarEntry(unk_D_84B25A58* arg0, s16 arg1) {
    s32 i;
    PokemonData* temp_s5 = gBattleContext.unk_1194[0].unk_08[0]->unk_01C;
    PokemonData* temp_s6 = gBattleContext.unk_1194[1].unk_08[0]->unk_01C;

    if (arg1 == 0) {
        InitDoubleBattleHealthBarGraphNodes(arg0);
    }

    if (arg1 < 0x10) {
        for (i = 0; i < gBattleContext.unk_1194[0].unk_08[0]->unk_002; i++) {
            if (temp_s5[i].unk_25 != 0) {
                arg0->unk_04[1 + i].unk_01E.y += 0x800;
                arg0->unk_04[9 + i].unk_01E.y += 0x800;
            }
        }

        for (i = 0; i < gBattleContext.unk_1194[1].unk_08[0]->unk_002; i++) {
            if (temp_s6[i].unk_25 != 0) {
                arg0->unk_04[4 + i].unk_01E.y -= 0x800;
                arg0->unk_04[12 + i].unk_01E.y -= 0x800;
            }
        }
    }

    if (arg1 == 0x10) {
        for (i = 1; i < 7; i++) {
            GraphNode_ClearCallback(&arg0->unk_04[i]);
            GraphNode_Reset(&arg0->unk_04[8 + i]);
            arg0->unk_04[i].unk_01E.y = 0;
        }

        for (i = 0; i < 3; i++) {
            if ((i >= gBattleContext.unk_1194[0].unk_08[0]->unk_002) || (temp_s5[i].unk_25 == 0)) {
                GraphNode_InitChild(&arg0->unk_04[1 + i], 0, 0, arg0->unk_08);
            } else {
                GraphNode_InitChild(&arg0->unk_04[1 + i], 0, 0, arg0->unk_10);
            }
        }

        for (i = 0; i < 3; i++) {
            if ((i >= gBattleContext.unk_1194[1].unk_08[0]->unk_002) || (temp_s6[i].unk_25 == 0)) {
                GraphNode_InitChild(&arg0->unk_04[4 + i], 0, 0, arg0->unk_08);
            } else {
                GraphNode_InitChild(&arg0->unk_04[4 + i], 0, 0, arg0->unk_10);
            }
        }
    }
}

void AnimateDoubleHealthBarEntry(unk_D_84B25A58* arg0, s16 arg1) {
    s32 i;
    PokemonData* temp_s0 = &gBattleContext.unk_1194[0].unk_08[0]->unk_01C[0];
    PokemonData* var_a3 = NULL;
    PokemonData* temp_t1 = &gBattleContext.unk_1194[1].unk_08[0]->unk_01C[0];
    PokemonData* var_t0 = NULL;

    if (gBattleContext.unk_1194[0].unk_01 == 2) {
        var_a3 = &gBattleContext.unk_1194[0].unk_08[1]->unk_01C[0];
    }

    if (gBattleContext.unk_1194[1].unk_01 == 2) {
        var_t0 = &gBattleContext.unk_1194[1].unk_08[1]->unk_01C[0];
    }

    if (arg1 == 0) {
        InitDoubleBattleHealthBarGraphNodes_Alt2(arg0);
    }

    if (arg1 < 0x10) {
        for (i = 0; i < gBattleContext.unk_1194[0].unk_08[0]->unk_002; i++) {
            if (temp_s0[i].unk_25 != 0) {
                arg0->unk_04[16 + i].unk_01E.y += 0x800;
                arg0->unk_04[28 + i].unk_01E.y += 0x800;
            }
        }

        for (i = 0; i < gBattleContext.unk_1194[1].unk_08[0]->unk_002; i++) {
            if (temp_t1[i].unk_25 != 0) {
                arg0->unk_04[22 + i].unk_01E.y -= 0x800;
                arg0->unk_04[34 + i].unk_01E.y -= 0x800;
            }
        }

        if (var_a3 != NULL) {
            for (i = 0; i < gBattleContext.unk_1194[0].unk_08[1]->unk_002; i++) {
                if (var_a3[i].unk_25 != 0) {
                    arg0->unk_04[19 + i].unk_01E.y += 0x800;
                    arg0->unk_04[31 + i].unk_01E.y += 0x800;
                }
            }
        }

        if (var_t0 != NULL) {
            for (i = 0; i < gBattleContext.unk_1194[1].unk_08[1]->unk_002; i++) {
                if (var_t0[i].unk_25 != 0) {
                    arg0->unk_04[25 + i].unk_01E.y -= 0x800;
                    arg0->unk_04[37 + i].unk_01E.y -= 0x800;
                }
            }
        }
    }

    if (arg1 == 0x10) {
        for (i = 0; i < 3; i++) {
            if (arg0->unk_04[16 + i].unk_01E.y == 0) {
                GraphNode_InitChild(&arg0->unk_04[1 + i], 0, 0, arg0->unk_08);
            } else {
                GraphNode_InitChild(&arg0->unk_04[1 + i], 0, 0, arg0->unk_10);
            }
            arg0->unk_04[1 + i].unk_000.unk_14 = arg0;
            Vec3f_Set(&arg0->unk_04[1 + i].unk_024, (i * 64.0f) - 32.0f, 48.0f, -289.0f);
        }

        for (i = 0; i < 3; i++) {
            if (arg0->unk_04[19 + i].unk_01E.y == 0) {
                GraphNode_InitChild(&arg0->unk_04[9 + i], 0, 0, arg0->unk_0C);
            } else {
                GraphNode_InitChild(&arg0->unk_04[9 + i], 0, 0, arg0->unk_14);
            }
            arg0->unk_04[9 + i].unk_000.unk_14 = arg0;
            Vec3f_Set(&arg0->unk_04[9 + i].unk_024, (i * 64.0f) - 32.0f, 48.0f, -289.0f);
        }

        for (i = 0; i < 3; i++) {
            if (arg0->unk_04[22 + i].unk_01E.y == 0) {
                GraphNode_InitChild(&arg0->unk_04[4 + i], 0, 0, arg0->unk_08);
            } else {
                GraphNode_InitChild(&arg0->unk_04[4 + i], 0, 0, arg0->unk_10);
            }
            arg0->unk_04[4 + i].unk_000.unk_14 = arg0;
            Vec3f_Set(&arg0->unk_04[4 + i].unk_024, (i * 64.0f) - 96.0f, -48.0f, -289.0f);
        }

        for (i = 0; i < 3; i++) {
            if (arg0->unk_04[25 + i].unk_01E.y == 0) {
                GraphNode_InitChild(&arg0->unk_04[12 + i], 0, 0, arg0->unk_0C);
            } else {
                GraphNode_InitChild(&arg0->unk_04[12 + i], 0, 0, arg0->unk_14);
            }
            arg0->unk_04[12 + i].unk_000.unk_14 = arg0;
            Vec3f_Set(&arg0->unk_04[12 + i].unk_024, (i * 64.0f) - 96.0f, -48.0f, -289.0f);
        }

        for (i = 16; i < 40; i++) {
            GraphNode_Reset(&arg0->unk_04[i]);
        }
    }
}

void UpdateHealthBarAnimation(unk_D_84B25A58* arg0) {
    if (osTvType == OS_TV_PAL) {
        if (arg0->unk_02 == 1) {
            if (arg0->unk_01 >= 0) {
                AnimateDoubleHealthBarSlideIn(arg0, arg0->unk_01);
            }

            if (arg0->unk_01 >= 0xC) {
                AnimateDoubleHealthBarDrainFast(arg0, arg0->unk_01 - 0xC);
            }

            if (arg0->unk_01 >= 0x3E) {
                AnimateDoubleHealthBarEntry(arg0, arg0->unk_01 - 0x3E);
            }
        } else {
            if (arg0->unk_01 >= 0) {
                AnimateHealthBarSlideIn(arg0, arg0->unk_01);
            }

            if (arg0->unk_01 >= 0xC) {
                AnimateHealthBarDrainFast(arg0, arg0->unk_01 - 0xC);
            }

            if (arg0->unk_01 >= 0x3E) {
                AnimateHealthBarEntry(arg0, arg0->unk_01 - 0x3E);
            }
        }

        arg0->unk_01++;
        if (arg0->unk_01 == 0x50) {
            arg0->unk_00 = 0;
        }
    } else {
        if (arg0->unk_02 == 1) {
            if (arg0->unk_01 >= 0) {
                AnimateDoubleHealthBarSlideIn(arg0, arg0->unk_01);
            }

            if (arg0->unk_01 >= 0xC) {
                AnimateDoubleHealthBarDrain(arg0, arg0->unk_01 - 0xC);
            }

            if (arg0->unk_01 >= 0x4A) {
                AnimateDoubleHealthBarEntry(arg0, arg0->unk_01 - 0x4A);
            }
        } else {
            if (arg0->unk_01 >= 0) {
                AnimateHealthBarSlideIn(arg0, arg0->unk_01);
            }

            if (arg0->unk_01 >= 0xC) {
                AnimateHealthBarDrain(arg0, arg0->unk_01 - 0xC);
            }

            if (arg0->unk_01 >= 0x4A) {
                AnimateHealthBarEntry(arg0, arg0->unk_01 - 0x4A);
            }
        }

        arg0->unk_01++;
        if (arg0->unk_01 == 0x60) {
            arg0->unk_00 = 0;
        }
    }
}

void AdvanceSpriteAnimation(unk_D_84B25A58* arg0) {
    SpriteDisplay_TryAdvance(arg0->unk_1C, 0);

    arg0->unk_01++;
    if ((arg0->unk_01 >= 0x1E) && (SpriteDisplay_IsAnimating(arg0->unk_1C) != 0)) {
        arg0->unk_01 = 0;
        arg0->unk_00 = 2;
    }
}

void UI_UpdateState(unk_D_84B25A58* arg0) {
    switch (arg0->unk_00) {
        case 1:
            AdvanceSpriteAnimation(arg0);
            break;

        case 3:
            UpdateHealthBarAnimation(arg0);
            break;
    }
}

void SetupSingleBattleSpriteSlots(unk_D_84B25A58* arg0) {
    s32 i;
    s32 count;
    AssetManager* temp_s0;

    temp_s0 = AssetManager_Create(5);
    SpriteDisplay_SetDepthBuffer(arg0->unk_1C, temp_s0, FramebufferImage_Allocate(0, 2, 0x80, 0xC0, 1));

    for (count = 0, i = 0; i < gBattleContext.unk_1194[0].unk_08[0]->unk_002; count++, i++) {
        SpriteDisplay_SetupSlot(arg0->unk_1C, count, gBattleContext.unk_1194[0].unk_08[0]->unk_01C[i].unk_00.unk_00, 0);
    }

    for (count = 3, i = 0; i < gBattleContext.unk_1194[1].unk_08[0]->unk_002; count++, i++) {
        SpriteDisplay_SetupSlot(arg0->unk_1C, count, gBattleContext.unk_1194[1].unk_08[0]->unk_01C[i].unk_00.unk_00, 0);
    }
}

void SetupDoubleBattleSpriteSlots(unk_D_84B25A58* arg0) {
    s32 i;
    s32 count;
    AssetManager* temp_s0;

    temp_s0 = AssetManager_Create(5);
    SpriteDisplay_SetDepthBuffer(arg0->unk_1C, temp_s0, FramebufferImage_Allocate(0, 2, 0x80, 0x60, 1));

    for (count = 0, i = 0; i < gBattleContext.unk_1194[0].unk_08[0]->unk_002; count++, i++) {
        SpriteDisplay_SetupSlot(arg0->unk_1C, count, gBattleContext.unk_1194[0].unk_08[0]->unk_01C[i].unk_00.unk_00, 0);
    }

    for (count = 6, i = 0; i < gBattleContext.unk_1194[1].unk_08[0]->unk_002; count++, i++) {
        SpriteDisplay_SetupSlot(arg0->unk_1C, count, gBattleContext.unk_1194[1].unk_08[0]->unk_01C[i].unk_00.unk_00, 0);
    }

    if (gBattleContext.unk_1194[0].unk_08[1] != NULL) {
        for (count = 3, i = 0; i < gBattleContext.unk_1194[0].unk_08[1]->unk_002; count++, i++) {
            SpriteDisplay_SetupSlot(arg0->unk_1C, count, gBattleContext.unk_1194[0].unk_08[1]->unk_01C[i].unk_00.unk_00, 0);
        }
    }

    if (gBattleContext.unk_1194[1].unk_08[1] != NULL) {
        for (count = 9, i = 0; i < gBattleContext.unk_1194[1].unk_08[1]->unk_002; count++, i++) {
            SpriteDisplay_SetupSlot(arg0->unk_1C, count, gBattleContext.unk_1194[1].unk_08[1]->unk_01C[i].unk_00.unk_00, 0);
        }
    }
}

void UI_Setup(unk_D_84B25A58* arg0, BinArchive* arg1) {
    u8* sp24 = BinArchive_GetFile(arg1, gBattleContext.unk_1194[0].unk_08[0]->unk_214->unk_003);
    u8* sp20 = BinArchive_GetFile(arg1, gBattleContext.unk_1194[1].unk_08[0]->unk_214->unk_003);

    AssetManager_LoadArchives();

    FRAGMENT_LOAD(fragment31);

    if (arg0->unk_02 == 1) {
        SetupDoubleBattleSpriteSlots(arg0);
    } else {
        SetupSingleBattleSpriteSlots(arg0);
    }

    Battle_DrawTrainerInfo(arg0->unk_24, 0, sp24, D_3000000);
    Battle_DrawTrainerInfo(arg0->unk_28, 1, sp20, D_3003000);
    arg0->unk_00 = 1;
}

s32 UI_WaitUntilReady(unk_D_84B25A58* arg0, Fragment2_1GraphNode* arg1) {
    if (arg0->unk_00 == 2) {
        arg0->unk_00 = 3;
        arg0->unk_04 = arg1;
        arg0->unk_01 = 0;
        arg1->unk_000.unk_14 = arg0;

        arg0->unk_04[7].unk_000.unk_14 = arg0;
        arg0->unk_04[0].unk_01E.y = 0x5800;
        arg0->unk_04[7].unk_01E.y = -0x5800;

        Vec3f_Set(&arg0->unk_04[0].unk_024, -96.0f, 48.0f, -289.0f);
        Vec3f_Set(&arg0->unk_04[7].unk_024, 96.0f, -48.0f, -289.0f);
        GraphNode_InitChild(&arg0->unk_04[0], 0, 0, arg0->unk_18);
        GraphNode_InitChild(&arg0->unk_04[7], 0, 0, arg0->unk_18);

        if (arg0->unk_02 == 1) {
            InitDoubleBattleHealthBarGraphNodes_Alt(arg0);
        } else {
            InitHealthBarGraphNodes(arg0);
        }
    }
    return arg0->unk_00 == 3;
}

void UpdateSingleBattleSpriteImages(unk_D_84B25A58* arg0) {
    s32 i;
    s32 count;

    for (i = 0, count = 0; i < gBattleContext.unk_1194[0].unk_08[0]->unk_002; count++, i++) {
        PokeIcon_LoadModelTextureForMon(arg0->unk_20[count], gBattleContext.unk_1194[0].unk_08[0]->unk_01C[i].unk_00.unk_00, NULL);
    }

    for (i = 0, count = 3; i < gBattleContext.unk_1194[1].unk_08[0]->unk_002; count++, i++) {
        PokeIcon_LoadModelTextureForMon(arg0->unk_20[count], gBattleContext.unk_1194[1].unk_08[0]->unk_01C[i].unk_00.unk_00, NULL);
    }
}

void UpdateDoubleBattleSpriteImages(unk_D_84B25A58* arg0) {
    s32 i;
    s32 count;

    for (i = 0, count = 0; i < gBattleContext.unk_1194[0].unk_08[0]->unk_002; count++, i++) {
        PokeIcon_LoadModelTextureForMon(&arg0->unk_20[count], gBattleContext.unk_1194[0].unk_08[0]->unk_01C[i].unk_00.unk_00, NULL);
    }

    for (i = 0, count = 6; i < gBattleContext.unk_1194[1].unk_08[0]->unk_002; count++, i++) {
        PokeIcon_LoadModelTextureForMon(&arg0->unk_20[count], gBattleContext.unk_1194[1].unk_08[0]->unk_01C[i].unk_00.unk_00, NULL);
    }

    if (gBattleContext.unk_1194[0].unk_08[1] != NULL) {
        for (i = 0, count = 3; i < gBattleContext.unk_1194[0].unk_08[1]->unk_002; count++, i++) {
            PokeIcon_LoadModelTextureForMon(&arg0->unk_20[count], gBattleContext.unk_1194[0].unk_08[1]->unk_01C[i].unk_00.unk_00, NULL);
        }
    }

    if (gBattleContext.unk_1194[1].unk_08[1] != NULL) {
        for (i = 0, count = 9; i < gBattleContext.unk_1194[1].unk_08[1]->unk_002; count++, i++) {
            PokeIcon_LoadModelTextureForMon(&arg0->unk_20[count], gBattleContext.unk_1194[1].unk_08[1]->unk_01C[i].unk_00.unk_00, NULL);
        }
    }
}

void UI_InitElement(unk_D_84B25A58* arg0) {
    MemoryBlock* sp2C;
    s32 i;

    arg0->unk_00 = 0;
    arg0->unk_01 = 0;
    arg0->unk_02 = 0;
    arg0->unk_24 = FramebufferImage_Allocate(0, 2, 0x40, 0x60, 0);
    arg0->unk_28 = FramebufferImage_Allocate(0, 2, 0x40, 0x60, 0);

    if ((gBattleContext.unk_0001 == 8) && (gBattleContext.unk_1194[0].unk_08[0]->unk_002 >= 4)) {
        arg0->unk_02 = 1;
    }

    if (gBattleContext.unk_0001 == 0) {
        if ((gBattleContext.unk_1194[0].unk_01 == 2) || (gBattleContext.unk_1194[1].unk_01 == 2)) {
            arg0->unk_02 = 1;
        } else {
            if (gBattleContext.unk_1194[0].unk_08[0]->unk_002 >= 4) {
                arg0->unk_02 = 1;
            }

            if (gBattleContext.unk_1194[1].unk_08[0]->unk_002 >= 4) {
                arg0->unk_02 = 1;
            }
        }
    }

    for (i = 0; i < 12; i++) {
        arg0->unk_2C[i] = 0;
    }

    if (arg0->unk_02 == 1) {
        arg0->unk_1C = SpriteDisplay_Alloc(NULL, 0xC, 0x80, 0x60);
        arg0->unk_20 = ALIGN64((u32)main_pool_alloc(0x9640, 0));
    } else {
        arg0->unk_1C = SpriteDisplay_Alloc(NULL, 6, 0x80, 0xC0);
        arg0->unk_20 = ALIGN64((u32)main_pool_alloc(0x4B40, 0));
    }

    SpriteDisplay_SetScaleTable(arg0->unk_1C, gSpeciesDisplayParamsBack);

    sp2C = state_pool_try_init(main_pool_get_available(), 0);
    if (arg0->unk_02 == 1) {
        arg0->unk_08 = process_geo_layout(sp2C, gHPBarNodeData);
        arg0->unk_0C = process_geo_layout(sp2C, gHPBarNodeData_Alt);
        arg0->unk_10 = process_geo_layout(sp2C, gHPBarNodeDataAlt);
        arg0->unk_14 = process_geo_layout(sp2C, gHPBarNodeDataAlt2);
    } else {
        arg0->unk_08 = process_geo_layout(sp2C, gHealthBarNodeData_Status);
        arg0->unk_10 = process_geo_layout(sp2C, gItemIconNodeData);
    }

    arg0->unk_18 = process_geo_layout(sp2C, gHealthBarNodeData);
    mem_pool_resize_block(sp2C);

    if (arg0->unk_02 == 1) {
        UpdateDoubleBattleSpriteImages(arg0);
    } else {
        UpdateSingleBattleSpriteImages(arg0);
    }
}
