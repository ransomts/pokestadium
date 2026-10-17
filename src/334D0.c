#include "334D0.h"
#include "src/12D80.h"
#include "src/30640.h"
#include "src/32D10.h"
#include "src/33FE0.h"
#include "src/6A40.h"
#include "src/F420.h"

typedef struct StadiumModelSlot {
    /* 0x000 */ StadiumModel model;
    /* 0x204 */ char pad204[0x5CC];
} StadiumModelSlot; // size = 0x7D0

typedef struct unk_func_80032F94_a0 {
    /* 0x00 */ u8 pad00[0x18];
    /* 0x18 */ s32 unk_18;
    /* 0x1C */ s32 unk_1C;
} unk_func_80032F94_a0;  // size = 0x20

typedef struct unk_D_800B2EA8 {
    u8 unk_00[0xA8];
} unk_D_800B2EA8; // size = 0xA8

typedef struct {
    MtxF mtx[16];   // 16 (0x10) × 0x40 = 0x400
} MtxBuffer; // size = 0x400

extern s32 gIdentityMtx[16];
extern Gfx gModelSetupDL[3];
extern Gfx gModelRenderDL[];

s32 gIdentityMtx[16] = { 65536, 0, 1, 0, 0, 65536, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0 };
Gfx gModelSetupDL[3] = { { { 0xE3000A01, 0x100000 } }, { { 0xE7000000, 0 } }, { { 0xDF000000, 0 } } };
Gfx gModelRenderDL[5] = { { { 0xD9FDFFFF, 0 } }, { { 0xE7000000, 0 } }, { { 0xFC309680, 0x5F1AFFFF } }, { { 0xE3001001, 0 } }, { { 0xDF000000, 0 } } };
extern u32 gNormalModelSegment[];
extern u32 gSpecialModelSegment[];

// extern Gfx gModelRenderDL[] = {
//     gsSPSetGeometryMode(0x00FDFFFF),
//     gsDPPipeSync(),
//     gsDPSetCombineLERP(
//         TEXEL0, 0, SHADE, 0,      // Color cycle 1
//         TEXEL0, 0, SHADE, 0,      // Color cycle 2
//         0, 0, 0, SHADE,           // Alpha cycle 1
//         0, 0, 0, SHADE            // Alpha cycle 2
//     ),
//     gsDPSetAlphaCompare(G_AC_NONE),
//     gsSPEndDisplayList(),
// };

s16 gModelPhase[4];
static MtxBuffer gModelMtxBuffers[2];
static StadiumModelSlot gStadiumModelSlots[2][3];
static unk_D_800B2EA8 gModelTextureData[1];

void func_800328D0(s32 arg0) {

}

s32 func_800328D8(UNUSED s32 arg0) {
    return 1;
}

void Model_CopyCurrentToBuffer(u8 arg0) {
    Matrix_Copy(gModelMtxBuffers[arg0].mtx, Matrix_GetRelative(0));
    Matrix_Copy(gModelMtxBuffers[arg0].mtx[1].mf, Matrix_GetRelative(-1));
}

void Model_ConcatCameraMatrix(u8 index) {
    MtxF* temp_a1;
    MtxF sp1C;

    temp_a1 = &gModelMtxBuffers[index];
    func_80031EF4(&sp1C, &gCurrentCameraNode->unk_60.mtxf);
    guMtxCatF(sp1C.mf, temp_a1->mf, temp_a1->mf);
}

void Model_ApplyScaleAndTranslation(u8 index) {
    MtxF* temp_a0;
    
    s32 pad[2];
    f32 spC0;
    f32 spBC;
    f32 spB8;
    
    MtxF sp78;
    MtxF sp38;
    Vec3f sp2C;
    
    temp_a0 = &gModelMtxBuffers[index].mtx;
    
    func_80032034(temp_a0, &sp2C);
    guScaleF(sp38.mf, sp2C.x, sp2C.y, sp2C.z);
    guMtxXFMF(temp_a0->mf, 0.0f, 0.0f, 0.0f, &spC0, &spBC, &spB8);
    guTranslateF(sp78.mf, spC0, spBC, spB8);
    guMtxCatF(sp38.mf, sp78.mf, temp_a0->mf);
}

void ModelSlot_Reset(s32 arg0) {
    s32 i;
    StadiumModelSlot* slot = &gStadiumModelSlots[arg0];

    for (i = 0; i < 3; i++) {
        slot[i].model.unk_00 = 0;
    }
}

Gfx* Model_SetRenderColors(Gfx* gfx) {
    u8 temp_v0 = gDefaultGraphRoot->unk_01D;

    switch (gDefaultGraphRoot->unk_01A) {
        case 0x92:
            gSPDisplayList(gfx++, gModelRenderDL);
            gDPSetPrimColor(gfx++, 0, temp_v0, 255, 255, 255, 200);
            gDPSetEnvColor(gfx++, 255, 32, 0, 0);
            break;
        case 0x7E:
            gSPDisplayList(gfx++, gModelRenderDL);
            gDPSetPrimColor(gfx++, 0, temp_v0, 255, 255, 5, 255);
            gDPSetEnvColor(gfx++, 255, 32, 0, 0);
            break;
        default:
            gSPDisplayList(gfx++, gModelRenderDL);
            gDPSetPrimColor(gfx++, 0, temp_v0, 255, 255, 255, 255);
            gDPSetEnvColor(gfx++, 180 - (gAnimationFrame % 8) * 10, 32, 0, 0);
            break;
    }

    return gfx;
}

void Model_DrawCurrent(void) {
    u8 index;
    s32 mode;

    mode = func_800325B4();
    index = (u8)mode;
    if (mode < 2) {
        Model_CopyCurrentToBuffer(index);
        Model_ApplyScaleAndTranslation(index);
        Model_ConcatCameraMatrix(index);

        if (gDefaultGraphRoot->unk_01A == 0x92) {
            func_80033B2C(&gStadiumModelSlots[index][D_800AF7B0[index & 1]].model, gModelTextureData, gModelMtxBuffers[index].mtx, &gSpecialModelSegment);
            return;
        }
        func_80033B2C(&gStadiumModelSlots[index][D_800AF7B0[index & 1]].model, gModelTextureData, gModelMtxBuffers[index].mtx, &gNormalModelSegment);
    }
}

void Model_DrawIfReady(void) {
    u8 index;
    s32 mode;

    mode = func_800325B4();
    index = (u8)mode;
    if ((mode < 2) && (func_800325AC() == 0) && (gModelPhase[index] >= 2)) {
        Model_CopyCurrentToBuffer(index);
        Model_ApplyScaleAndTranslation(index);
        Model_ConcatCameraMatrix(index);
        func_800361C4(&gStadiumModelSlots[index][D_800AF7B0[index & 1]].model, &gModelMtxBuffers[index].mtx);
    }
}

Gfx* Model_DrawSegment(Gfx* gfx) {
    ModelSegment* segment;
    s32 pad[1];
    MtxF modelMtx;     // sp1E8
    MtxF tempCatMtx;   // sp1A8
    MtxF sp168;
    MtxF scaleMtx;     // sp128
    MtxF translateMtx; // spE8
    Mtx tempMtx;       // spA8
    Mtx* mtxL;
    u32 pad2[16];
    Vec3f scale;
    Vec3f translate;

    if (gDefaultGraphRoot->unk_01A == 0x92) {
        segment = (ModelSegment *)&gSpecialModelSegment;
    } else {
        segment = (ModelSegment *)&gNormalModelSegment;
    }
    func_80031EF4(&modelMtx, &gCurrentCameraNode->unk_60.mtxf);
    guMtxF2L(&modelMtx.mf[0], &tempMtx);
    Matrix_Copy(&tempCatMtx, Matrix_GetRelative(0));
    func_80032034(&tempCatMtx, &scale);
    guScaleF(&scaleMtx.mf[0], scale.x, scale.y, scale.z);
    guMtxXFMF(&tempCatMtx.mf[0], 0.0f, 0.0f, 0.0f, &translate.z, &translate.y, &translate.x);
    guTranslateF(&translateMtx.mf[0], translate.z, translate.y, translate.x);
    mtxL = GfxAlloc(0x40);
    guMtxCatF(&scaleMtx.mf[0], &translateMtx.mf[0], &tempCatMtx.mf[0]);
    guMtxF2L(&tempCatMtx.mf[0], mtxL);
    guMtxCatL(&tempMtx, mtxL, mtxL);
    {    Gfx *_gfx = (Gfx *)(gfx++);    _gfx->words.w0 = 0xDA380002;    _gfx->words.w1 = mtxL;    }
    gfx = Model_SetRenderColors(gfx);
    {    Gfx *_gfx = (Gfx *)(gfx++);    _gfx->words.w0 = 0xDB060038;    _gfx->words.w1 = (s32) segment->vertexSegment;    }
    {    Gfx *_gfx = (Gfx *)(gfx++);    _gfx->words.w0 = 0xDE000000;    _gfx->words.w1 = (s32) segment->displayList;    }
    {    Gfx *_gfx = (Gfx *)(gfx++);    _gfx->words.w0 = 0xD8380002;    _gfx->words.w1 = 0x40;    }
    {    Gfx *_gfx = (Gfx *)(gfx++);    _gfx->words.w0 = 0xDE000000;    _gfx->words.w1 = &gModelSetupDL;    }
    return gfx;
}

Gfx* Model_RenderStateMachine(Gfx* gfx) {
    u8 mode;
    Vtx* vtx;
    s16* var_v1;

    mode = func_800325B4();
    if ((mode == 0xFF) || (mode == 0xFE)) {
        return Model_DrawSegment(gfx);
    }
    if (mode >= 4) {
        return gfx;
    }
    if (mode >= 2) {
        mode &= 1;
        if (gModelPhase[mode] >= 2) {
            GfxAlloc(0xA0);
            gfx = Model_SetRenderColors(gfx);
            var_v1 = &D_800AF7B0[mode & 1];
            {
                ModelSegment* segment = (ModelSegment*)(&gStadiumModelSlots[mode][*var_v1].model.unkSegment);
                {    Gfx *_gfx = (Gfx *)(gfx++);    _gfx->words.w0 = 0xDB060038;    _gfx->words.w1 = (s32) segment->vertexSegment;    }
                {    Gfx *_gfx = (Gfx *)(gfx++);    _gfx->words.w0 = 0xDE000000;    _gfx->words.w1 = (s32) segment->displayList;    }
                {    Gfx *_gfx = (Gfx *)(gfx++);    _gfx->words.w0 = 0xDE000000;    _gfx->words.w1 = &gModelSetupDL;    }
            }
            *var_v1 += 1;
        }
        return gfx;
    }
    switch (gModelPhase[mode]) {
        default:
            var_v1 = &D_800AF7B0[mode & 1];
            break;
        case 1:
            Model_DrawCurrent();
            var_v1 = &D_800AF7B0[mode & 1];
            break;
        case 2:
        case 3:
            vtx = GfxAlloc(0xA0);
            {    Gfx *_gfx = (Gfx *)(gfx++);    _gfx->words.w0 = 0xDA380002;    _gfx->words.w1 = &gIdentityMtx;    }
            gfx = Model_SetRenderColors(gfx);
            var_v1 = &D_800AF7B0[mode & 1];
            gfx = func_800366A4(gfx, &gStadiumModelSlots[mode][*var_v1].model, vtx);
            {    Gfx *_gfx = (Gfx *)(gfx++);    _gfx->words.w0 = 0xD8380002;    _gfx->words.w1 = 0x40;    }
            {    Gfx *_gfx = (Gfx *)(gfx++);    _gfx->words.w0 = 0xDE000000;    _gfx->words.w1 = &gModelSetupDL;    }
            break;
    }
    *var_v1 += 1;
    return gfx;
}
