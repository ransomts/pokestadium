#include "12D80.h"
#include "src/12D80.h"
#include "src/1CF30.h"
#include "src/1CF30.h"
#include "src/17300.h"
#include "src/18140.h"
#include "src/6A40.h"
#include "src/6BC0.h"
#include "src/32D10.h"
#include "src/F420.h"
#include "src/memmap.h"
#include "src/util.h"

typedef void (*func_D_8006F0A4)(GraphNode* arg0);

typedef struct unk_D_800AA8C8 {
    /* 0x0000 */ MtxF unk_0000[64];
    /* 0x1000 */ MtxF* unk_1000[32];
    /* 0x1080 */ s8 unk_1080[32];
    /* 0x10A0 */ s32 unk_10A0;
} unk_D_800AA8C8; // size >= 0x10A4

s32 gRenderFrameCounter = 0;
u16 gAnimationFrame = 0;
CameraStruct* gCurrentCameraNode = NULL;
unk_D_86002F34_alt1* gCurrentTextureNode = NULL;
unk_D_86002F34_alt1* gCurrentLightNode = NULL;
CameraStruct* gActiveCameraNode = NULL;
unk_D_86002F34_alt1* gActiveNode = NULL;
Fragment2_1GraphNode* gDefaultGraphRoot = NULL;
unk_D_86002F34_alt11* gActiveLayerNode = NULL;
static func_D_8006F0A4 D_8006F0A4[] = {
    Geo_ProcessNodeChildren, Geo_NodeReference, Geo_NodeCamera, Geo_NodeType3Pass, Geo_NodeModelRoot, Geo_NodeOrtho, Geo_NodePerspective,
    Geo_NodeBackground, Geo_NodeClearDepth, Geo_NodeType9Empty, Geo_NodeFog, Graph_AddLight, Geo_NodeType12Empty, Geo_NodeAmbientLight,
    Geo_NodeShadowContext, Geo_NodeShadow, Geo_NodeCullDistance, Geo_NodeSwitchCase, Geo_NodeTranslateRotate, Geo_NodeTranslate, Geo_NodeAnimatedPart,
    Geo_NodeDisplayListPart, Geo_NodeModelPart, Geo_NodeDisplayListMatrix, Geo_NodeScale, Geo_NodeDisplayList, Geo_NodeShadowTexture, Geo_NodeAnchor,
    Geo_NodeGroup, NULL,          NULL,
};

static s32 gIsRenderInitialized = 0;

static u32 D_8006F124[4][9] = {
    {
        0x3024000,
        0x3024000,
        0x3024000,
        0x3024000,
        0x3027008,
        0x104240,
        0x104240,
        0x104240,
        0x104240,
    },
    {
        0x3124370,
        0x112230,
        0x112E10,
        0x112230,
        0x113238,
        0x104A50,
        0x104E50,
        0x104A50,
        0x104A70,
    },
    {
        0x3024000,
        0x112048,
        0x112048,
        0x112048,
        0x113048,
        0x1041C8,
        0x1041C8,
        0x1041C8,
        0x1041C8,
    },
    {
        0x3124370,
        0x112078,
        0x112D58,
        0x112478,
        0x113078,
        0x1049D8,
        0x104DD8,
        0x1045D8,
        0x1049F8,
    },
};

static u8 D_8006F1B4[15][16] = {
    { 0x1F, 0x1F, 0x1F, 3, 7, 7, 7, 3, 0, 0x1F, 4, 0x1F, 0, 7, 6, 7 },
    { 1, 0x1F, 3, 0x1F, 7, 7, 7, 1, 0, 0x1F, 4, 0x1F, 0, 7, 6, 7 },
    { 1, 3, 8, 3, 7, 7, 3, 7, 0, 0x1F, 4, 0x1F, 0, 7, 6, 7 },
    { 1, 0x1F, 3, 0x1F, 7, 7, 7, 3, 0, 0x1F, 4, 0x1F, 0, 7, 6, 7 },
    { 1, 0x1F, 3, 0x1F, 1, 7, 3, 7, 0, 0x1F, 4, 0x1F, 0, 7, 6, 7 },
    { 0x1F, 0x1F, 0x1F, 3, 7, 7, 7, 3, 0x1F, 0x1F, 0x1F, 0, 0, 7, 6, 7 },
    { 1, 0x1F, 3, 0x1F, 7, 7, 7, 1, 0x1F, 0x1F, 0x1F, 0, 0, 7, 6, 7 },
    { 1, 3, 8, 3, 7, 7, 3, 7, 0x1F, 0x1F, 0x1F, 0, 0, 7, 6, 7 },
    { 1, 0x1F, 3, 0x1F, 7, 7, 7, 3, 0x1F, 0x1F, 0x1F, 0, 0, 7, 6, 7 },
    { 1, 0x1F, 3, 0x1F, 1, 7, 3, 7, 0x1F, 0x1F, 0x1F, 0, 0, 7, 6, 7 },
    { 0x1F, 0x1F, 0x1F, 4, 7, 7, 7, 4, 0x1F, 0x1F, 0x1F, 0, 0, 7, 6, 7 },
    { 1, 0x1F, 4, 0x1F, 7, 7, 7, 1, 0x1F, 0x1F, 0x1F, 0, 0, 7, 6, 7 },
    { 1, 4, 8, 4, 7, 7, 3, 7, 0x1F, 0x1F, 0x1F, 0, 0, 7, 6, 7 },
    { 1, 0x1F, 4, 0x1F, 7, 7, 7, 4, 0x1F, 0x1F, 0x1F, 0, 0, 7, 6, 7 },
    { 1, 0x1F, 4, 0x1F, 1, 7, 4, 7, 0x1F, 0x1F, 0x1F, 0, 0, 7, 6, 7 },
};

static s16 D_8006F2A4[] = { 16, 8, 4, 2, 0, 0 };

static s32 gGraphNodeReturnVal;
static MtxF* gNodeMatrixCache[8];
static u8 pad_D_800AA6E8[0x1E0];
static unk_D_800AA8C8 gMatrixStack;
static unk_D_800AB970 gScaleStack;
static s32 gRenderModeIndex;
static s32 gRenderFlags;
static s32 gPipeSynced;
static unk_D_800ABB10 gRenderState;
static unk_D_800ABB28 gLayerStates[10];
static unk_D_800ABB28* gCurrentRenderState;
static s32 gRenderStateCount;

void GeoRender_InitMatrixStack(void) {
    gMatrixStack.unk_10A0 = 0;
    gMatrixStack.unk_1080[0] = 0;
    MtxF_Identity(&gMatrixStack.unk_0000[0]);
    gMatrixStack.unk_1000[0] = Gfx_AllocDisplayList(sizeof(Mtx) * 1);
    MtxF_ToFixed(gMatrixStack.unk_1000[0], gMatrixStack.unk_0000);
}

void GeoRender_CommitMatrix(void) {
    gMatrixStack.unk_1080[gMatrixStack.unk_10A0] = 0;
    gMatrixStack.unk_1000[gMatrixStack.unk_10A0] = Gfx_AllocDisplayList(sizeof(MtxF) * 1);
    MtxF_ToFixed(gMatrixStack.unk_1000[gMatrixStack.unk_10A0], &gMatrixStack.unk_0000[gMatrixStack.unk_10A0]);
}

void GeoRender_SetMatrix(MtxF* arg0) {
    MtxF_Copy(&gMatrixStack.unk_0000[gMatrixStack.unk_10A0], arg0);
    gMatrixStack.unk_1080[gMatrixStack.unk_10A0] = 0;
    gMatrixStack.unk_1000[gMatrixStack.unk_10A0] = Gfx_AllocDisplayList(sizeof(MtxF) * 1);
    MtxF_ToFixed(gMatrixStack.unk_1000[gMatrixStack.unk_10A0], &gMatrixStack.unk_0000[gMatrixStack.unk_10A0]);
}

void GeoRender_PushMultipliedMatrix(MtxF* arg0) {
    MtxF* temp_a0;

    gMatrixStack.unk_10A0++;
    temp_a0 = &gMatrixStack.unk_0000[gMatrixStack.unk_10A0];

    MtxF_Multiply(&temp_a0[0], arg0, &temp_a0[-1]);
    gMatrixStack.unk_1080[gMatrixStack.unk_10A0] = 0;
    gMatrixStack.unk_1000[gMatrixStack.unk_10A0] = Gfx_AllocDisplayList(sizeof(MtxF) * 1);
    MtxF_ToFixed(gMatrixStack.unk_1000[gMatrixStack.unk_10A0], &gMatrixStack.unk_0000[gMatrixStack.unk_10A0]);
}

void GeoRender_PushScaledMatrix(Vec3f* arg0) {
    MtxF* temp_a0;

    gMatrixStack.unk_10A0++;
    temp_a0 = &gMatrixStack.unk_0000[gMatrixStack.unk_10A0];

    MtxF_ScaleRows(&temp_a0[0], &temp_a0[-1], arg0);

    gMatrixStack.unk_1080[gMatrixStack.unk_10A0] = 0;
    gMatrixStack.unk_1000[gMatrixStack.unk_10A0] = Gfx_AllocDisplayList(sizeof(MtxF) * 1);

    MtxF_ToFixed(gMatrixStack.unk_1000[gMatrixStack.unk_10A0], &gMatrixStack.unk_0000[gMatrixStack.unk_10A0]);
}

MtxF* GeoRender_GetRelativeMatrix(s32 arg0) {
    MtxF* var_v1 = NULL;

    if (arg0 <= 0) {
        var_v1 = &(&gMatrixStack.unk_0000[gMatrixStack.unk_10A0])[arg0];
    }

    return var_v1;
}

MtxF* GeoRender_GetMatrix(s32 arg0) {
    MtxF* var_v1 = NULL;

    if ((arg0 >= 0) && (arg0 < 0x20)) {
        var_v1 = &gMatrixStack.unk_0000[arg0];
    }

    return var_v1;
}

void GeoRender_ResetTransformStack(void) {
    gScaleStack.unk_180 = 0;
    gScaleStack.unk_000[0] = gRootNodeScale;
}

void GeoRender_PushScale(Vec3f* arg0) {
    gScaleStack.unk_000[gScaleStack.unk_180 + 1].x = gScaleStack.unk_000[gScaleStack.unk_180].x * arg0->x;
    gScaleStack.unk_000[gScaleStack.unk_180 + 1].y = gScaleStack.unk_000[gScaleStack.unk_180].y * arg0->y;
    gScaleStack.unk_000[gScaleStack.unk_180 + 1].z = gScaleStack.unk_000[gScaleStack.unk_180].z * arg0->z;

    gScaleStack.unk_180++;
}

Vtx* GeoOverlay_BuildFadeQuad(unk_D_86002F34_00C_0CC* arg0, unk_D_86002F34_00C_040* arg1) {
    u8 sp47;
    Vtx* temp_v0 = Gfx_AllocDisplayList(sizeof(Vtx) * 4);

    if (temp_v0 != NULL) {
        switch (arg0->posX) {
            case 1:
                sp47 = 0xFF;
                break;

            case 2:
                sp47 = 0xFF - ((arg0->unk_0A * 0xFF) / arg0->unk_08);
                break;

            case 3:
                sp47 = (arg0->unk_0A * 0xFF) / arg0->unk_08;
                break;
        }

        Gfx_SetVertexAttributes(&temp_v0[0], arg1->l, arg1->t, -1, 0, 0, arg0->color.r, arg0->color.g, arg0->color.b, sp47);
        Gfx_SetVertexAttributes(&temp_v0[1], arg1->l, arg1->b, -1, 0, 0, arg0->color.r, arg0->color.g, arg0->color.b, sp47);
        Gfx_SetVertexAttributes(&temp_v0[2], arg1->r, arg1->b, -1, 0, 0, arg0->color.r, arg0->color.g, arg0->color.b, sp47);
        Gfx_SetVertexAttributes(&temp_v0[3], arg1->r, arg1->t, -1, 0, 0, arg0->color.r, arg0->color.g, arg0->color.b, sp47);
    }

    return temp_v0;
}

void GeoOverlay_DrawFadeQuad(unk_D_86002F34_00C_0CC* arg0, unk_D_86002F34_00C_040* arg1) {
    Vtx* temp_v0 = GeoOverlay_BuildFadeQuad(arg0, arg1);

    if (temp_v0 != NULL) {
        gDPSetCombineMode(gDisplayListHead++, G_CC_SHADE, G_CC_SHADE);
        gDPSetRenderMode(gDisplayListHead++, G_RM_AA_XLU_SURF, G_RM_AA_XLU_SURF2);

        gSPVertex(gDisplayListHead++, (u32)temp_v0 & 0x1FFFFFFF, 4, 0);
        gSP2Triangles(gDisplayListHead++, 0, 1, 2, 0, 0, 2, 3, 0);
    }

    if (arg0->posX != 1) {
        arg0->unk_0A++;
        if (arg0->unk_0A == arg0->unk_08) {
            if (arg0->posX == 2) {
                arg0->posX = 0;
            } else {
                arg0->posX = 1;
            }
        }
    }
}

void Graph_MakeRotatedVertex(Vtx* arg0, unk_D_86002F34_00C_0CC* arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5, s16 arg6,
                   s16 arg7) {
    f32 temp_fa0;
    f32 temp_fv1;
    u16 idx = arg1->unk_18;
    f32 a4;
    f32 a5;
    s16 tmp1;
    s16 tmp2;

    a4 = arg4;
    temp_fv1 = COSS(idx);
    temp_fa0 = SINS(idx);
    a5 = arg5;

    // The rotated coordinates must be computed in their own statements: the table loads keep uopt
    // from sinking them into the call, and as1 schedules by source line. The dead temp_fv1/temp_fa0
    // loads above are needed for the float register choice.
    tmp1 = (s16)((a4 * COSS(idx)) - (SINS(idx) * a5)) + arg2;
    tmp2 = (s16)((a4 * SINS(idx)) + (COSS(idx) * a5)) + arg3;

    Gfx_SetVertexAttributes(arg0, tmp1, tmp2, -1, arg6 * 32, arg7 * 32, arg1->color.r, arg1->color.g, arg1->color.b,
                  0xFF);
}

Vtx* GeoOverlay_BuildRotatingQuad(unk_D_86002F34_00C_0CC* arg0) {
    Vtx* temp_v0 = Gfx_AllocDisplayList(sizeof(Vtx) * 8);
    Vtx* temp_s0;
    s16 temp_s2;
    s16 temp_s4;
    s16 temp_s5;

    if (temp_v0 != NULL) {
        temp_s0 = temp_v0;

        temp_s4 = arg0->unk_10 + (((arg0->unk_14 - arg0->unk_10) * arg0->unk_0A) / arg0->unk_08);
        temp_s5 = arg0->unk_12 + (((arg0->unk_16 - arg0->unk_12) * arg0->unk_0A) / arg0->unk_08);
        temp_s2 = arg0->unk_0C + (((arg0->unk_0E - arg0->unk_0C) * arg0->unk_0A) / arg0->unk_08);

        if (arg0->posX == 2) {
            Graph_MakeRotatedVertex(temp_s0++, arg0, temp_s4, temp_s5, -temp_s2, -temp_s2, -0x1F, 0x3F);
            Graph_MakeRotatedVertex(temp_s0++, arg0, temp_s4, temp_s5, temp_s2, -temp_s2, 0x1F, 0x3F);
            Graph_MakeRotatedVertex(temp_s0++, arg0, temp_s4, temp_s5, temp_s2, temp_s2, 0x1F, 0);
            Graph_MakeRotatedVertex(temp_s0++, arg0, temp_s4, temp_s5, -temp_s2, temp_s2, -0x1F, 0);
        } else {
            Graph_MakeRotatedVertex(temp_s0++, arg0, temp_s4, temp_s5, -temp_s2, -temp_s2, 0, 0x3F);
            Graph_MakeRotatedVertex(temp_s0++, arg0, temp_s4, temp_s5, temp_s2, -temp_s2, 0x3F, 0x3F);
            Graph_MakeRotatedVertex(temp_s0++, arg0, temp_s4, temp_s5, temp_s2, temp_s2, 0x3F, 0);
            Graph_MakeRotatedVertex(temp_s0++, arg0, temp_s4, temp_s5, -temp_s2, temp_s2, 0, 0);
        }

        Graph_MakeRotatedVertex(temp_s0++, arg0, temp_s4, temp_s5, -0x7D0, -0x7D0, 0, 0);
        Graph_MakeRotatedVertex(temp_s0++, arg0, temp_s4, temp_s5, 0x7D0, -0x7D0, 0, 0);
        Graph_MakeRotatedVertex(temp_s0++, arg0, temp_s4, temp_s5, 0x7D0, 0x7D0, 0, 0);
        Graph_MakeRotatedVertex(temp_s0++, arg0, temp_s4, temp_s5, -0x7D0, 0x7D0, 0, 0);
    }

    arg0->unk_18 += arg0->unk_1A;
    return temp_v0;
}

void GeoOverlay_DrawRotatingQuad(unk_D_86002F34_00C_0CC* arg0, UNUSED unk_D_86002F34_00C_040* arg1) {
    Vtx* temp_v0 = GeoOverlay_BuildRotatingQuad(arg0);

    if (temp_v0 != 0) {
        gDPSetCombineMode(gDisplayListHead++, G_CC_SHADE, G_CC_SHADE);
        gDPSetRenderMode(gDisplayListHead++, G_RM_AA_OPA_SURF, G_RM_AA_OPA_SURF2);

        gSPVertex(gDisplayListHead++, (u32)temp_v0 & 0x1FFFFFFF, 8, 0);
        gSP2Triangles(gDisplayListHead++, 0, 4, 1, 0, 1, 4, 5, 0);
        gSP2Triangles(gDisplayListHead++, 1, 5, 2, 0, 2, 5, 6, 0);
        gSP2Triangles(gDisplayListHead++, 2, 6, 7, 0, 2, 7, 3, 0);
        gSP2Triangles(gDisplayListHead++, 3, 4, 0, 0, 3, 7, 4, 0);

        gDPPipeSync(gDisplayListHead++);

        gDPSetCombineMode(gDisplayListHead++, G_CC_MODULATEIDECALA, G_CC_MODULATEIDECALA);
        gDPSetRenderMode(gDisplayListHead++, G_RM_AA_XLU_SURF, G_RM_AA_XLU_SURF2);
        gDPSetTextureFilter(gDisplayListHead++, G_TF_BILERP);

        if (arg0->posY == 0) {
            gDPLoadTextureBlock(gDisplayListHead++, arg0->texture, G_IM_FMT_IA, G_IM_SIZ_8b, 64, 64, 0,
                                G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, 6, 6, G_TX_NOLOD, G_TX_NOLOD);
        } else {
            gDPLoadTextureBlock(gDisplayListHead++, arg0->texture, G_IM_FMT_IA, G_IM_SIZ_8b, 32, 64, 0,
                                G_TX_MIRROR | G_TX_WRAP, G_TX_MIRROR | G_TX_WRAP, 5, 6, G_TX_NOLOD, G_TX_NOLOD);
        }

        gSPTexture(gDisplayListHead++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);

        gSPVertex(gDisplayListHead++, (u32)temp_v0 & 0x1FFFFFFF, 4, 0);
        gSP2Triangles(gDisplayListHead++, 0, 1, 2, 0, 0, 2, 3, 0);

        gSPTexture(gDisplayListHead++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF);
        gDPSetTextureFilter(gDisplayListHead++, G_TF_BILERP);
    }

    arg0->unk_0A++;
    if (arg0->unk_0A == arg0->unk_08) {
        if (arg0->posX == 4) {
            arg0->posX = 0;
        } else {
            arg0->posX = 1;
        }
    }
}

void GeoOverlay_Draw(unk_D_86002F34_00C_0CC* arg0, unk_D_86002F34_00C_040* arg1) {
    if (arg0->posX != 0) {
        gDPPipeSync(gDisplayListHead++);

        gDPSetCycleType(gDisplayListHead++, G_CYC_1CYCLE);
        gSPClearGeometryMode(gDisplayListHead++, G_ZBUFFER | G_LIGHTING);
        gSPPerspNormalize(gDisplayListHead++, 0xFFFF);
        gSPMatrix(gDisplayListHead++, (u32)arg1->mtx & 0x1FFFFFFF, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
        gSPMatrix(gDisplayListHead++, (u32)&gCamProjectionMatrix & 0x1FFFFFFF, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

        if ((arg0->posX == 1) || (arg0->posX == 2) || (arg0->posX == 3)) {
            GeoOverlay_DrawFadeQuad(arg0, arg1);
        } else {
            GeoOverlay_DrawRotatingQuad(arg0, arg1);
        }

        gDPPipeSync(gDisplayListHead++);
        gDPSetCycleType(gDisplayListHead++, G_CYC_2CYCLE);
    }
}

void Geo_ProcessNodeChildren(GraphNode* arg0) {
    GraphNode* temp_s2 = arg0->unk_0C;
    GraphNode* var_s0 = temp_s2;

    if (temp_s2 != NULL) {
        do {
            if (var_s0->unk_01 & 1) {
                gGraphNodeReturnVal = 0;
                if (var_s0->unk_10 != NULL) {
                    gGraphNodeReturnVal = var_s0->unk_10(2, var_s0);
                }
                D_8006F0A4[var_s0->posX](var_s0);
            }
            var_s0 = var_s0->unk_08;
        } while (var_s0 != temp_s2);
    }
}

void Geo_NodeReference(GraphNode* arg0) {
    UNUSED s32 pad;
    GraphNode* temp_a1 = ((MiniHudMainGraph*)arg0)->unk_18;

    if ((temp_a1 != NULL) && (temp_a1->unk_01 & 1)) {
        gGraphNodeReturnVal = 0;
        if (temp_a1->unk_10 != NULL) {
            gGraphNodeReturnVal = temp_a1->unk_10(2, temp_a1);
        }
        D_8006F0A4[temp_a1->posX](temp_a1);
    }

    Geo_ProcessNodeChildren(arg0);
}

void Geo_NodeCamera(GraphNode* arg0) {
    UNUSED MtxF pad_mtx;
    CameraStruct* arg = (CameraStruct*)arg0;
    unk_D_86002F34_00C_040* temp_s2 = &arg->unk_40;
    unk_D_86002F34_00C_060* temp_s1 = &arg->unk_60;
    unk_D_86002F34_00C_024* sp48 = &arg->unk_24;
    CameraRect* temp_s0 = &arg->unk_18;

    temp_s0->vp = Gfx_AllocDisplayList(sizeof(Vp) * 1);
    temp_s2->mtx = Gfx_AllocDisplayList(sizeof(Mtx) * 1);
    sp48->mtx = Gfx_AllocDisplayList(sizeof(MtxF) * 1);
    temp_s1->p_mtxf = Gfx_AllocDisplayList(sizeof(MtxF) * 1);
    temp_s1->lookat = Gfx_AllocDisplayList(sizeof(LookAt) * 1);

    temp_s0->vp->vp.vtrans[0] = (temp_s0->x * 4) + (temp_s0->width * 2);
    temp_s0->vp->vp.vtrans[1] = (temp_s0->y * 4) + (temp_s0->height * 2);
    temp_s0->vp->vp.vtrans[2] = 0x1FF;

    temp_s0->vp->vp.vscale[0] = temp_s0->width * 2;
    temp_s0->vp->vp.vscale[1] = temp_s0->height * 2;
    temp_s0->vp->vp.vscale[2] = 0x1FF;

    gSPViewport(gDisplayListHead++, (u32)temp_s0->vp & 0x1FFFFFFF);
    gDPSetScissorFrac(gDisplayListHead++, G_SC_NON_INTERLACE, temp_s0->x * 4.0f, temp_s0->y * 4.0f,
                      (temp_s0->x + temp_s0->width) * 4.0f, (temp_s0->y + temp_s0->height) * 4.0f);

    guOrtho(temp_s2->mtx, temp_s2->l, temp_s2->r, temp_s2->b, temp_s2->t, temp_s2->n, temp_s2->f, temp_s2->scale);
    guPerspective(sp48->mtx, &sp48->perspNorm, sp48->fovy, sp48->aspect, sp48->near, sp48->far, sp48->scale);
    guLookAtReflectF(&temp_s1->mtxf, temp_s1->lookat, temp_s1->eye.x, temp_s1->eye.y, temp_s1->eye.z, temp_s1->at.x,
                     temp_s1->at.y, temp_s1->at.z, temp_s1->up.x, temp_s1->up.y, temp_s1->up.z);
    MtxF_ToFixed(temp_s1->p_mtxf, &temp_s1->mtxf);

    gCurrentCameraNode = arg;
    if ((arg->unk_CC.posX != 1) && (arg->posX.unk_0C != NULL)) {
        Geo_ProcessNodeChildren(&arg->posX);
    }
    GeoOverlay_Draw(&arg->unk_CC, temp_s2);
    Gfx_ApplyScissorRect(&gDisplayListHead);
    gCurrentCameraNode = NULL;
}

void Geo_NodeType3Pass(GraphNode* arg0) {
    gCurrentTextureNode = arg0;
    Geo_ProcessNodeChildren(arg0);
    gCurrentTextureNode = NULL;
}

void Geo_NodeModelRoot(GraphNode* arg0) {
    unk_D_86002F34_alt1* arg = (unk_D_86002F34_alt1*)arg0;

    if (arg->posX.unk_0C != NULL) {
        arg->unk_1D = 0;
        arg->unk_20 = -1;
        arg->lights = Gfx_AllocDisplayList(sizeof(Lights7));
        arg->unk_1C = 0;
        arg->lights->a.l.col[0] = 0;
        arg->lights->a.l.col[1] = 0;
        arg->lights->a.l.col[2] = 0;

        gSPClearGeometryMode(gDisplayListHead++, G_ZBUFFER | G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING |
                                                     G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD | G_SHADING_SMOOTH);
        gSPSetGeometryMode(gDisplayListHead++, G_SHADE | G_CULL_BACK | G_SHADING_SMOOTH);
        gSPTexture(gDisplayListHead++, 0, 0, 0, G_TX_RENDERTILE, G_OFF);
        gDPSetCycleType(gDisplayListHead++, G_CYC_2CYCLE);

        ModelAnim_ResetCurveContext();
        ModelAnim_ResetEventContext();
        GeoRender_InitMatrixStack();
        GeoRender_ResetTransformStack();

        gSPMatrix(gDisplayListHead++, (u32)gMatrixStack.unk_1000[gMatrixStack.unk_10A0] & 0x1FFFFFFF,
                  G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

        gCurrentLightNode = arg;
        Geo_ProcessNodeChildren(arg0);
        gCurrentLightNode = NULL;
    }

    arg->unk_1A = gAnimationFrame;
}

void Geo_NodeModelPartRoot(GraphNode* arg0) {
    CameraStruct* arg = (CameraStruct*)arg0;

    if ((gActiveCameraNode == NULL) && (arg->posX.unk_0C != NULL)) {
        gActiveCameraNode = arg;
        GeoRender_InitMaterialState(arg->posX.posY & 3, gRenderFrameCounter);
        Geo_ProcessNodeChildren(arg0);
        GeoRender_FlushMaterialSlots();
        gActiveCameraNode = NULL;
    }
}

void Geo_NodeOrtho(GraphNode* arg0) {
    if ((gActiveCameraNode == NULL) && (arg0->unk_0C != NULL)) {
        gSPPerspNormalize(gDisplayListHead++, 0xFFFF);
        gSPMatrix(gDisplayListHead++, (u32)gCurrentCameraNode->unk_40.mtx & 0x1FFFFFFF,
                  G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);

        Geo_NodeModelPartRoot(arg0);
    }
}

void Geo_NodePerspective(GraphNode* arg0) {
    if ((gActiveCameraNode == NULL) && (arg0->unk_0C != NULL)) {
        gSPLookAt(gDisplayListHead++, (u32)&gCurrentCameraNode->unk_60.lookat->l & 0x1FFFFFFF);

        gSPPerspNormalize(gDisplayListHead++, gCurrentCameraNode->unk_24.perspNorm);

        gSPMatrix(gDisplayListHead++, (u32)gCurrentCameraNode->unk_24.mtx & 0x1FFFFFFF,
                  G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
        gSPMatrix(gDisplayListHead++, (u32)gCurrentCameraNode->unk_60.p_mtxf & 0x1FFFFFFF,
                  G_MTX_NOPUSH | G_MTX_MUL | G_MTX_PROJECTION);

        Geo_NodeModelPartRoot(arg0);
    }
}

void Geo_NodeBackground(GraphNode* arg0) {
    unk_D_86002F34_alt2* arg = (unk_D_86002F34_alt2*)arg0;
    CameraRect* ptr = &gCurrentCameraNode->unk_18;

    GfxImage_FillRectangle(&gDisplayListHead, ptr->x, ptr->y, ptr->width, ptr->height, arg->unk_18);

    gDPPipeSync(gDisplayListHead++);
    gDPSetCycleType(gDisplayListHead++, G_CYC_2CYCLE);
}

void Geo_NodeClearDepth(UNUSED GraphNode* arg0) {
    CameraRect* ptr = &gCurrentCameraNode->unk_18;

    GfxImage_ClearDepthRectangle(&gDisplayListHead, ptr->x, ptr->y, ptr->width, ptr->height);

    gDPPipeSync(gDisplayListHead++);
    gDPSetCycleType(gDisplayListHead++, G_CYC_2CYCLE);
}

void Geo_NodeType9Empty(UNUSED GraphNode* arg0) {
}

void Geo_NodeFog(GraphNode* arg0) {
    unk_D_86002F34_alt3* arg = (unk_D_86002F34_alt3*)arg0;

    gCurrentLightNode->unk_1D = 1;
    gCurrentLightNode->unk_20 = arg->unk_1C;

    gSPFogPosition(gDisplayListHead++, arg->unk_18, arg->unk_1A);
    gSPSetGeometryMode(gDisplayListHead++, G_FOG);
    gDPSetColor(gDisplayListHead++, G_SETFOGCOLOR, arg->unk_1C);
}

void Graph_AddLight(GraphNode* arg0) {
    unk_D_86002F34_alt4* arg = (unk_D_86002F34_alt4*)arg0;
    Light* light;
    Ambient* temp_a4;

    if (gCurrentLightNode->unk_1C >= 7) {
        return;
    }

    light = &gCurrentLightNode->lights->l[gCurrentLightNode->unk_1C];
    temp_a4 = &gCurrentLightNode->lights->a;

    *(u32*)light->l.col = arg->unk_18.rgba;
    *(u32*)light->l.colc = arg->unk_18.rgba;

    light->l.dir[0] = (120.0f * COSS(arg->unk_1C)) * SINS(arg->unk_1E);
    light->l.dir[1] = (120.0f) * SINS(arg->unk_1C);
    light->l.dir[2] = (120.0f * COSS(arg->unk_1C)) * COSS(arg->unk_1E);

    temp_a4->l.col[0] += ((arg->unk_18.r * arg->unk_18.a) / 100);
    if (temp_a4->l.col[0] > 0xFF) {
        temp_a4->l.col[0] = 0xFF;
    }

    temp_a4->l.col[1] += ((arg->unk_18.g * arg->unk_18.a) / 100);
    if (temp_a4->l.col[1] > 0xFF) {
        temp_a4->l.col[1] = 0xFF;
    }

    temp_a4->l.col[2] += ((arg->unk_18.b * arg->unk_18.a) / 100);
    if (temp_a4->l.col[2] > 0xFF) {
        temp_a4->l.col[2] = 0xFF;
    }

    gCurrentLightNode->unk_1C++;
}

void Geo_NodeType12Empty(UNUSED GraphNode* arg0) {
}

void Geo_NodeAmbientLight(GraphNode* arg0) {
    unk_D_86002F34_alt4* arg = (unk_D_86002F34_alt4*)arg0;
    s32 i;
    Lights7* lights;

    lights = gCurrentLightNode->lights;
    if ((arg->unk_18.r == 0xFF) && (arg->unk_18.g == 0xFF) && (arg->unk_18.b == 0xFF)) {
        lights->a.l.colc[0] = lights->a.l.col[0];
        lights->a.l.colc[1] = lights->a.l.col[1];
        lights->a.l.colc[2] = lights->a.l.col[2];
    } else {
        lights->a.l.colc[0] = lights->a.l.col[0] = arg->unk_18.r;
        lights->a.l.colc[1] = lights->a.l.col[1] = arg->unk_18.g;
        lights->a.l.colc[2] = lights->a.l.col[2] = arg->unk_18.b;
    }

    gSPSetGeometryMode(gDisplayListHead++, G_LIGHTING);
    gMoveWd(gDisplayListHead++, 2, 0, gCurrentLightNode->unk_1C * 0x18);

    for (i = 0; i < gCurrentLightNode->unk_1C; i++) {
        gSPLight(gDisplayListHead++, &gCurrentLightNode->lights->l[i], i + 1);
    }

    gSPLight(gDisplayListHead++, gCurrentLightNode->lights, i + 1);
}

void Geo_NodeShadowContext(GraphNode* arg0) {
    unk_D_86002F34_alt11* arg = (unk_D_86002F34_alt11*)arg0;
    MtxF* temp_v0 = &gMatrixStack.unk_0000[gMatrixStack.unk_10A0];
    Vec3f sp2C;
    Vec3s sp24;

    if (gDefaultGraphRoot->unk_000.posY & 2) {
        Vec3f_SetComponentsDuplicate(&sp2C, temp_v0->xw, 0.0f, temp_v0->zw);
        Vec3s_SetComponents(&sp24, 0, gDefaultGraphRoot->unk_01E.y, 0);
        MtxF_SetRotationTranslationF(&gMatrixStack.unk_0000[gMatrixStack.unk_10A0 + 1], &sp2C, &sp24);

        gMatrixStack.unk_10A0++;

        GeoRender_CommitMatrix();
        GeoRender_SubmitMaterial(0, gMatrixStack.unk_1000[gMatrixStack.unk_10A0]);
        GeoRender_SubmitDisplayList(D_1002590, 1);

        gMatrixStack.unk_10A0--;
    }

    gActiveLayerNode = arg;
    Geo_ProcessNodeChildren(arg0);
    gActiveLayerNode = NULL;
}

void Geo_NodeCullDistance(GraphNode* arg0) {
    unk_D_86002F34_alt3* arg = (unk_D_86002F34_alt3*)arg0;
    MtxF* mtx2 = &gCurrentCameraNode->unk_60.mtxf;
    f32 a = gMatrixStack.unk_0000[gMatrixStack.unk_10A0].mf[3][0];
    f32 b = gMatrixStack.unk_0000[gMatrixStack.unk_10A0].mf[3][1];
    f32 c = gMatrixStack.unk_0000[gMatrixStack.unk_10A0].mf[3][2];
    s16 temp_ft5 = ((a * mtx2->mf[0][2]) + (b * mtx2->mf[1][2]) + (c * mtx2->mf[2][2])) + mtx2->mf[3][2];

    if ((temp_ft5 >= arg->unk_18) && (temp_ft5 < arg->unk_1A)) {
        Geo_ProcessNodeChildren(arg0);
    }
}

void Geo_NodeSwitchCase(GraphNode* arg0) {
    unk_D_86002F34_alt3* arg = (unk_D_86002F34_alt3*)arg0;
    s32 i;
    GraphNode* var_a1 = arg->posX.unk_0C;

    if (var_a1 != NULL) {
        for (i = 0; i < arg->unk_1A; i++) {
            var_a1 = var_a1->unk_08;
        }
    }

    if (var_a1->unk_01 & 1) {
        D_8006F0A4[var_a1->posX](var_a1);
    }
}

void Geo_NodeTranslateRotate(GraphNode* arg0) {
    MtxF sp20;
    unk_D_86002F34_alt5* arg = (unk_D_86002F34_alt5*)arg0;

    MtxF_SetRotationTranslationF(&sp20, &arg->unk_18, &arg->unk_24);
    GeoRender_PushMultipliedMatrix(&sp20);
    Geo_ProcessNodeChildren(arg0);

    gMatrixStack.unk_10A0--;
}

void Geo_NodeTranslate(GraphNode* arg0) {
    unk_D_86002F34_alt5* arg = (unk_D_86002F34_alt5*)arg0;

    GeoRender_PushScaledMatrix(&arg->unk_18);
    Geo_ProcessNodeChildren(arg0);

    gMatrixStack.unk_10A0--;
}

void Geo_NodeAnimatedPart(GraphNode* arg0) {
    Vec3s sp90;
    Vec3f sp84;
    Vec3f sp78;
    MtxF sp38;
    unk_D_86002F34_alt6* arg = (unk_D_86002F34_alt6*)arg0;
    s32 sp30;

    sp30 = 0;
    sp90 = arg->unk_1E;
    sp78 = arg->unk_24;

    Vec3f_FromVec3s(&sp84, &arg->unk_18);
    ModelAnim_EvaluateJointTransform(&sp84, &sp90, &sp78, arg->unk_32 * 3);

    if (arg->unk_31 & 2) {
        MtxF_BuildTransform(&sp38, &sp84, &sp90, &sp78, &gCurrentCameraNode->unk_60.mtxf, &gMatrixStack.unk_0000[gMatrixStack.unk_10A0]);
        gMatrixStack.unk_10A0++;
        GeoRender_SetMatrix(&sp38);
    } else if (arg->unk_31 & 1) {
        MtxF_SetRotationScaleTranslation(&sp38, &sp84, &sp90, &sp78);
        GeoRender_PushMultipliedMatrix(&sp38);
    } else {
        MtxF_SetRotationAndScaledTranslation(&sp38, &sp84, &sp90, &gScaleStack.unk_000[gScaleStack.unk_180]);

        gMatrixStack.unk_10A0++;

        GeoRender_PushScale(&sp78);
        if (gMatrixStack.unk_1080[gMatrixStack.unk_10A0 - 1] == 1) {
            MtxF_Multiply(&gMatrixStack.unk_0000[gMatrixStack.unk_10A0 + 32], &sp38,
                          &gMatrixStack.unk_0000[gMatrixStack.unk_10A0 + 31]);
        } else {
            MtxF_Multiply(&gMatrixStack.unk_0000[gMatrixStack.unk_10A0 + 32], &sp38,
                          &gMatrixStack.unk_0000[gMatrixStack.unk_10A0 - 1]);
        }
        MtxF_ScaleRows(&gMatrixStack.unk_0000[gMatrixStack.unk_10A0], &gMatrixStack.unk_0000[gMatrixStack.unk_10A0 + 32],
                      &gScaleStack.unk_000[gScaleStack.unk_180]);
        GeoRender_CommitMatrix();
        gMatrixStack.unk_1080[gMatrixStack.unk_10A0] = 1;
        sp30 = 1;
    }

    gNodeMatrixCache[arg->unk_30] = gMatrixStack.unk_1000[gMatrixStack.unk_10A0];
    Geo_ProcessNodeChildren(arg0);
    gNodeMatrixCache[arg->unk_30] = NULL;
    gMatrixStack.unk_10A0--;

    if (sp30 != 0) {
        gScaleStack.unk_180--;
    }
}

void Geo_NodeDisplayListPart(GraphNode* arg0) {
    unk_D_86002F34_alt7* arg = (unk_D_86002F34_alt7*)arg0;

    if (arg->unk_18 != NULL) {
        GeoRender_SubmitMaterial(arg->posX.unk_03, gNodeMatrixCache[arg->unk_1C]);
        GeoRender_SubmitDisplayList(arg->unk_18, (arg->posX.posY & 4) != 0);
    }

    Geo_ProcessNodeChildren(arg0);
}

void Geo_NodeModelPart(GraphNode* arg0) {
    MtxF sp38;
    Color_RGBA8_u32 sp34;
    Fragment2_1GraphNode* arg = (Fragment2_1GraphNode*)arg0;

    if (gCurrentLightNode->unk_18 == arg->unk_018) {
        arg->transformEntryCount = 0;
        ModelAnim_BeginCurveContext(&arg->unk_040, gAnimationFrame, (arg->unk_000.posY & 0x20) != 0);
        ModelAnim_BeginEventContext(&arg->unk_054, gAnimationFrame, (arg->unk_000.posY & 0x20) != 0);

        if (arg->unk_000.posY & 0x10) {
            MtxF_Multiply(&sp38, &arg->unk_060, &gMatrixStack.unk_0000[gMatrixStack.unk_10A0]);
        } else if (arg->unk_000.posY & 8) {
            MtxF_ApplyScaleTransform(&sp38, &gCurrentCameraNode->unk_60.mtxf, &gMatrixStack.unk_0000[gMatrixStack.unk_10A0], &arg->unk_024,
                          1.0f);
        } else if (arg->unk_000.posY & 0x80) {
            MtxF_SetRotationAndTransformTranslation(&sp38, &arg->unk_024, &arg->unk_01E);
            MtxF_Multiply(&sp38, &sp38, &gMatrixStack.unk_0000[gMatrixStack.unk_10A0]);
        } else {
            MtxF_SetRotationTranslationF(&sp38, &arg->unk_024, &arg->unk_01E);
            MtxF_Multiply(&sp38, &sp38, &gMatrixStack.unk_0000[gMatrixStack.unk_10A0]);
        }

        MtxF_ScaleRows(&gMatrixStack.unk_0000[gMatrixStack.unk_10A0 + 1], &sp38, &arg->unk_030);

        if (!(arg->unk_000.posY & 4)) {
            gMatrixStack.unk_10A0++;

            GeoRender_CommitMatrix();
            gDefaultGraphRoot = arg0;

            GeoRender_SetMaterialParams(arg->unk_0A0, arg->unk_01D, arg->unk_01C);

            if ((gCurrentTextureNode->unk_18 < 0) && (arg->unk_01A > 0)) {
                ModelAnim_UpdateDisplayObjectAnimation(arg->modelPhase, arg->unk_01A);
                Geo_ProcessNodeChildren(arg0);
                ModelAnim_FinalizeDisplayObjectAnimation(arg->modelPhase, arg->unk_01A);
            } else {
                Geo_ProcessNodeChildren(arg0);
            }

            sp34.rgba = 0xFFFFFF00;
            GeoRender_SetMaterialParams(sp34, 0xFF, 0);
            gDefaultGraphRoot = NULL;
        }

        ModelAnim_EndCurveContext();
        ModelAnim_EndEventContext();
        gMatrixStack.unk_10A0 -= 1;
    }
}

void Geo_NodeDisplayListMatrix(GraphNode* arg0) {
    unk_D_86002F34_alt8* arg = (unk_D_86002F34_alt8*)arg0;

    GeoRender_PushMultipliedMatrix(&arg->unk_1C);

    if ((arg->unk_18 != NULL) || (arg->posX.unk_10 != NULL)) {
        GeoRender_SubmitMaterial(arg->posX.unk_03, gMatrixStack.unk_1000[gMatrixStack.unk_10A0]);
        if (arg->posX.unk_10 != NULL) {
            arg->posX.unk_10(5, arg0);
        }
        GeoRender_SubmitDisplayList(arg->unk_18, (arg->posX.posY & 4) != 0);
    }
    Geo_ProcessNodeChildren(arg0);
    gMatrixStack.unk_10A0--;
}

void Geo_NodeScale(GraphNode* arg0) {
    MtxF sp30;
    unk_D_86002F34_alt9* arg = (unk_D_86002F34_alt9*)arg0;

    MtxF_ApplyScaleTransform(&sp30, &gCurrentCameraNode->unk_60.mtxf, &gMatrixStack.unk_0000[gMatrixStack.unk_10A0], &arg->unk_1C,
                  arg->unk_28);
    gMatrixStack.unk_10A0++;
    GeoRender_SetMatrix(&sp30);

    if ((arg->unk_18 != NULL) || (arg->posX.unk_10 != NULL)) {
        GeoRender_SubmitMaterial(arg->posX.unk_03, gMatrixStack.unk_1000[gMatrixStack.unk_10A0]);
        if (arg->posX.unk_10 != NULL) {
            arg->posX.unk_10(5, arg0);
        }
        GeoRender_SubmitDisplayList(arg->unk_18, (arg->posX.posY & 4) != 0);
    }

    Geo_ProcessNodeChildren(arg0);
    gMatrixStack.unk_10A0--;
}

void Geo_NodeDisplayList(GraphNode* arg0) {
    unk_D_86002F34_alt9* arg = (unk_D_86002F34_alt9*)arg0;

    if ((arg->unk_18 != NULL) || (arg->posX.unk_10 != NULL)) {
        GeoRender_SubmitMaterial(arg->posX.unk_03, gMatrixStack.unk_1000[gMatrixStack.unk_10A0]);
        if (arg->posX.unk_10 != NULL) {
            arg->posX.unk_10(5, arg0);
        }
        GeoRender_SubmitDisplayList(arg->unk_18, (arg->posX.posY & 4) != 0);
    }
    Geo_ProcessNodeChildren(arg0);
}

void Geo_NodeShadowTexture(GraphNode* arg0) {
    Color_RGBA8_u32 sp44;
    unk_D_86002F34_alt10* arg = (unk_D_86002F34_alt10*)arg0;
    unk_D_86002F34_alt11_018* sp3C;
    unk_D_86002F34_alt11_018* sp38;
    s32 sp34;

    sp3C = NULL;
    sp38 = NULL;
    sp34 = arg->unk_18;

    if (arg->unk_22 == 1) {
        sp44.rgba = 0xFFFFFFFF;
    } else {
        sp44.rgba = arg->unk_24.rgba;
    }

    if (arg->unk_1C >= 0) {
        sp3C = &gActiveLayerNode->unk_18[arg->unk_1C];
    }

    if (arg->unk_1E >= 0) {
        sp38 = &gActiveLayerNode->unk_1C[arg->unk_1E];
    }

    if (gDefaultGraphRoot != NULL) {
        sp44.r = (sp44.r * gDefaultGraphRoot->unk_03C.r) / 255;
        sp44.g = (sp44.g * gDefaultGraphRoot->unk_03C.g) / 255;
        sp44.b = (sp44.b * gDefaultGraphRoot->unk_03C.b) / 255;
    }

    ModelAnim_GetEventAtFrame(&sp3C, gActiveLayerNode->unk_18, arg->unk_20);
    GeoRender_SetMaterialTexture(arg->unk_22, sp44, sp3C, sp38, sp34);
    Geo_ProcessNodeChildren(arg0);
}

void GeoRender_RecordAnchorPosition(s32 arg0) {
    MtxF* temp_a1;
    unk_D_86002F58_004_000_0A8* ptr;

    if (gDefaultGraphRoot != NULL) {
        if (gDefaultGraphRoot->transformEntryCount < 0xC) {
            ptr = &gDefaultGraphRoot->unk_0A8[gDefaultGraphRoot->transformEntryCount++];
            temp_a1 = &gMatrixStack.unk_0000[gMatrixStack.unk_10A0];

            ptr->posX = arg0;
            ptr->rotation.x = temp_a1->mf[3][0];
            ptr->rotation.y = temp_a1->mf[3][1];
            ptr->rotation.z = temp_a1->mf[3][2];
        }
    }
}

void Geo_NodeAnchor(GraphNode* arg0) {
    unk_D_86002F34_alt3* arg = (unk_D_86002F34_alt3*)arg0;

    GeoRender_RecordAnchorPosition(arg->unk_18);
    Geo_ProcessNodeChildren(arg0);
}

void Geo_NodeGroup(GraphNode* arg0) {
    Geo_ProcessNodeChildren(arg0);
}

void Geo_NodeShadow(GraphNode* arg0) {
    Vec3f sp9C;
    Vec3f sp90;
    Vec3f sp84;
    f32 sp80;
    MtxF sp40;
    MtxF* sp3C;
    unk_D_86002F34_alt12* arg = (unk_D_86002F34_alt12*)arg0;
    Gfx* temp_s1;

    sp3C = &gMatrixStack.unk_0000[gMatrixStack.unk_10A0];
    temp_s1 = Gfx_AllocDisplayList(sizeof(Gfx) * 2);

    if (GeoRender_FindAnchorPosition(gDefaultGraphRoot, 0x64, NULL) == 0) {
        GeoRender_RecordAnchorPosition(0x64);
    }

    Vec3f_SetComponentsDuplicate(&sp9C, sp3C->mf[3][0], sp3C->mf[3][1] + arg->unk_1E, sp3C->mf[3][2]);
    sp9C.y = 0.0f;

    if (gDefaultGraphRoot->unk_000.posY & 0x40) {
        Vec3f_SetComponentsDuplicate(&sp90, 0.0f, 1.0f, 0.0f);
        MtxF_GetScale(sp3C, &sp84);

        sp80 = 1.0f - ((sp3C->mf[3][1] - sp9C.y) / 1000.0f);
        if (sp80 < 0.5f) {
            sp80 = 0.5f;
        }

        if (sp80 > 1.0f) {
            sp80 = 1.0f;
        }

        sp84.x *= (arg->unk_1A / 100.0f) * sp80;
        sp84.z *= (arg->unk_1C / 100.0f) * sp80;
        MtxF_SetOrthonormalBasis(&sp40, &sp90, &sp9C, gDefaultGraphRoot->unk_01E.y);
        MtxF_ScaleRows(&gMatrixStack.unk_0000[gMatrixStack.unk_10A0 + 1], &sp40, &sp84);

        gMatrixStack.unk_10A0++;
        GeoRender_CommitMatrix();

        if (arg->unk_18 == 0) {
            gSPBranchList(&temp_s1[1], Util_ConvertAddrToVirtAddr(D_1002480));
        } else {
            gSPBranchList(&temp_s1[1], Util_ConvertAddrToVirtAddr(D_1002508));
        }
        gDPSetEnvColor(&temp_s1[0], 0, 0, 0, (s32)(150.0f * sp80));

        if (gDefaultGraphRoot->unk_000.posY & 2) {
            GeoRender_SubmitMaterial(6, gMatrixStack.unk_1000[gMatrixStack.unk_10A0]);
        } else {
            GeoRender_SubmitMaterial(5, gMatrixStack.unk_1000[gMatrixStack.unk_10A0]);
        }

        gDPSetFogColor(gDisplayListHead++, 255, 255, 255, 0);
        gDPSetPrimColor(gDisplayListHead++, 0, gDefaultGraphRoot->unk_01D, 255, 255, 255, 255);

        GeoRender_SubmitDisplayList((u32)temp_s1 & 0x1FFFFFFF, 1);
        Geo_ProcessNodeChildren(arg0);

        gMatrixStack.unk_10A0--;
    }
}

void Geo_RenderRootNode(GraphNode* arg0) {
    unk_D_86002F34_alt1* arg = (unk_D_86002F34_alt1*)arg0;

    if (arg0->unk_01 & 1) {
        gDPPipeSync(gDisplayListHead++);

        gDPSetTextureLOD(gDisplayListHead++, G_TL_TILE);
        gDPSetTextureLUT(gDisplayListHead++, G_TT_NONE);
        gDPSetTextureDetail(gDisplayListHead++, G_TD_CLAMP);
        gDPSetTexturePersp(gDisplayListHead++, G_TP_PERSP);
        gDPSetTextureFilter(gDisplayListHead++, G_TF_BILERP);
        gDPSetTextureConvert(gDisplayListHead++, G_TC_FILT);
        gDPSetCombineKey(gDisplayListHead++, G_CK_NONE);
        gDPSetAlphaCompare(gDisplayListHead++, G_AC_NONE);
        gDPSetColorDither(gDisplayListHead++, G_CD_MAGICSQ);
        gDPSetAlphaDither(gDisplayListHead++, G_AD_PATTERN);

        gCurrentTextureNode = arg;
        Geo_ProcessNodeChildren(arg0);
        gCurrentTextureNode = NULL;
    }

    gRenderFrameCounter = 0;
}

void Geo_ProcessCallbacks(GraphNode* arg0, s32 arg1) {
    GraphNode* var_s1 = arg0;
    GraphNode** var_s0;

    do {
        if (var_s1->unk_10 != NULL) {
            var_s1->unk_10(arg1, var_s1);
        }

        if (var_s1->unk_0C != NULL) {
            switch (var_s1->posX) {
                default:
                    var_s0 = NULL;
                    break;

                case 2:
                    var_s0 = &gCurrentCameraNode;
                    break;

                case 4:
                    var_s0 = &gCurrentLightNode;
                    break;

                case 6:
                    var_s0 = &gActiveNode;
                    break;

                case 0x16:
                    var_s0 = &gDefaultGraphRoot;
                    break;
            }

            if (var_s0 != NULL) {
                *var_s0 = var_s1;
            }

            Geo_ProcessCallbacks(var_s1->unk_0C, arg1);

            if (var_s0 != NULL) {
                *var_s0 = NULL;
            }
        }

        var_s1 = var_s1->unk_08;
    } while (var_s1 != arg0);
}

void GeoRender_SetMode(s32 arg0) {
    gRenderFrameCounter = arg0;
}

void GeoRender_AdvanceFrameCounter(void) {
    gAnimationFrame++;
}

s32 GeoRender_IsModelFrameCurrent(void) {
    s32 var_v1 = 1;

    if (gCurrentLightNode != NULL) {
        var_v1 = gCurrentLightNode->unk_1A == gAnimationFrame;
    }
    return var_v1;
}

Vec3f* GeoRender_FindAnchorPosition(Fragment2_1GraphNode* arg0, s16 arg1, Vec3f* arg2) {
    s32 i;
    s32 var_v0;
    u8 temp_v1;
    Fragment2_1GraphNode* var_a2;

    for (i = 0; i < arg0->transformEntryCount; i++) {
        if (arg1 == arg0->unk_0A8[i].posX) {
            if (arg2 != NULL) {
                *arg2 = arg0->unk_0A8[i].rotation;
            }
            return &arg0->unk_0A8[i].rotation;
        }
    }

    return NULL;
}

void GeoRender_SetCombineMode(Gfx* arg0, arg1_func_81407874_014_000_010* arg1) {
    gDPSetCombine(arg0++,
                  GCCc0w0(arg1->posX, arg1->posY, arg1->rotation, arg1->unk_06) | GCCc1w0(arg1->unk_08, arg1->unk_0A),

                  GCCc0w1(arg1->unk_01, arg1->unk_03, arg1->unk_05, arg1->unk_07) |
                      GCCc1w1(arg1->unk_09, arg1->unk_0C, arg1->unk_0E, arg1->unk_0B, arg1->unk_0D, arg1->unk_0F));
}

void GeoRender_SyncMaterialState(void) {
    if (gPipeSynced == 0) {
        gPipeSynced = 1;

        gDPPipeSync(gDisplayListHead++);
    }
}

void GeoRender_SetRenderMode(void) {
    s32 var_v0 = D_8006F124[gRenderModeIndex][gCurrentRenderState->unk_24];

    gPipeSynced = 1;

    gDPPipeSync(gDisplayListHead++);

    gCurrentRenderState->unk_14.rgba = 0x00000000;

    gDPSetColor(gDisplayListHead++, G_SETFOGCOLOR, gCurrentLightNode->unk_20);

    if ((gRenderFlags & 1) && (gRenderModeIndex == 1) && (gCurrentRenderState->unk_24 == 5)) {
        var_v0 = 0x107A58;
    }

    if (gCurrentLightNode->unk_1D != 0) {
        gDPSetRenderMode(gDisplayListHead++, var_v0, 0xC8000000);
    } else {
        gDPSetRenderMode(gDisplayListHead++, var_v0, 0x0C080000);
    }
}

void GeoRender_ApplyMaterialState(void) {
    Color_RGBA8_u32 sp1C;

    sp1C.rgba = gCurrentRenderState->unk_10.rgba;

    gCurrentRenderState->unk_18 = NULL;
    gCurrentRenderState->unk_1C = NULL;
    gCurrentRenderState->unk_0C = NULL;
    gCurrentRenderState->unk_27 = 0;
    gPipeSynced = 1;

    gDPPipeSync(gDisplayListHead++);
    gDPSetPrimColor(gDisplayListHead++, 0, gCurrentRenderState->unk_26, sp1C.r, sp1C.g, sp1C.b, sp1C.a);
    gDPSetTextureLUT(gDisplayListHead++, G_TT_NONE);
    gSPTexture(gDisplayListHead++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF);

    GeoRender_SetCombineMode(gDisplayListHead++, D_8006F1B4[gCurrentRenderState->unk_25]);

    gSPSetGeometryMode(gDisplayListHead++, G_SHADE | G_CULL_BACK | G_SHADING_SMOOTH);
    gSPClearGeometryMode(gDisplayListHead++, G_FOG | G_TEXTURE_GEN);

    gSPLookAt(gDisplayListHead++, (u32)&gCurrentCameraNode->unk_60.lookat->l & 0x1FFFFFFF);

    if (gCurrentLightNode->unk_1D != 0) {
        gSPSetGeometryMode(gDisplayListHead++, G_FOG);
    }
}

void GeoRender_SetFogColor(unk_D_800ABB10* arg0) {
    if (arg0->unk_08.rgba != gCurrentRenderState->unk_14.rgba) {
        GeoRender_SyncMaterialState();

        gDPSetColor(gDisplayListHead++, G_SETFOGCOLOR, arg0->unk_08.rgba);
        gDPSetRenderMode(gDisplayListHead++, D_8006F124[gRenderModeIndex][gCurrentRenderState->unk_24], 0xC4000000);

        gCurrentRenderState->unk_14.rgba = arg0->unk_08.rgba;
    }
}

void GeoRender_RestoreRenderMode(UNUSED unk_D_800ABB10* arg0) {
    if (gCurrentRenderState->unk_14.rgba & 0xFF) {
        GeoRender_SetRenderMode();
    }
}

void GeoRender_SetPrimitiveColor(unk_D_800ABB10* arg0) {
    if ((arg0->rotation.rgba != gCurrentRenderState->unk_10.rgba) || (arg0->unk_01 != gCurrentRenderState->unk_26)) {
        GeoRender_SyncMaterialState();

        gDPSetPrimColor(gDisplayListHead++, 0, arg0->unk_01, arg0->rotation.r, arg0->rotation.g, arg0->rotation.b,
                        arg0->rotation.a);

        gCurrentRenderState->unk_10.rgba = arg0->rotation.rgba;
        gCurrentRenderState->unk_26 = arg0->unk_01;
    }
}

void GeoRender_SetCombineTableEntry(unk_D_800ABB10* arg0) {
    if (arg0->posX != gCurrentRenderState->unk_25) {
        GeoRender_SyncMaterialState();
        GeoRender_SetCombineMode(gDisplayListHead++, D_8006F1B4[arg0->posX]);
        gCurrentRenderState->unk_25 = arg0->posX;
    }
}

void GeoRender_DisableTexture(UNUSED unk_D_800ABB10* arg0) {
    if (gCurrentRenderState->unk_18 != NULL) {
        gSPTexture(gDisplayListHead++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF);
    }

    gCurrentRenderState->unk_18 = NULL;
    gCurrentRenderState->unk_1C = NULL;
    gCurrentRenderState->unk_20 = NULL;
}

void GeoRender_BindTexture(unk_D_800ABB10* arg0) {
    unk_D_86002F34_alt11_018* temp_t0;
    s32 var_a3;

    if (gCurrentRenderState->unk_18 == NULL) {
        gSPTexture(gDisplayListHead++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);
    }

    if ((arg0->unk_0C != gCurrentRenderState->unk_18) || (arg0->unk_14 != gCurrentRenderState->unk_20)) {
        temp_t0 = arg0->unk_0C;

        if (arg0->unk_10 != NULL) {
            gSPDisplayList(gDisplayListHead++, arg0->unk_10->unk_08);
        } else {
            gDPSetTextureLUT(gDisplayListHead++, G_TT_NONE);
        }

        if (temp_t0->unk_01 == 0) {
            if ((temp_t0->posY % D_8006F2A4[0]) == 0) {
                gDPSetTextureImage(gDisplayListHead++, temp_t0->fmt, G_IM_SIZ_16b, 1, temp_t0->texture);
            } else {
                gDPSetTextureImage(gDisplayListHead++, temp_t0->fmt, G_IM_SIZ_8b, temp_t0->posY >> 1,
                                   temp_t0->texture);
            }
        } else if ((temp_t0->posY % D_8006F2A4[temp_t0->unk_01]) == 0) {
            if (temp_t0->unk_01 == 3) {
                var_a3 = 3;
            } else {
                var_a3 = 2;
            }

            gDPSetTextureImage(gDisplayListHead++, temp_t0->fmt, var_a3, 1, temp_t0->texture);
        } else {
            gDPSetTextureImage(gDisplayListHead++, temp_t0->fmt, temp_t0->unk_01, temp_t0->posY, temp_t0->texture);
        }

        gSPDisplayList(gDisplayListHead++, arg0->unk_14);
    }

    gCurrentRenderState->unk_18 = arg0->unk_0C;
    gCurrentRenderState->unk_1C = arg0->unk_10;
    gCurrentRenderState->unk_20 = arg0->unk_14;
}

void GeoRender_EnableTextureGeneration(UNUSED unk_D_800ABB10* arg0) {
    if (gCurrentRenderState->unk_27 == 0) {
        gDPLoadTextureBlock(gDisplayListHead++, D_1001800, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, 0,
                            G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, 5, 5, 1, 1);
        gSPTexture(gDisplayListHead++, 0x1194, 0x1194, 0, G_TX_RENDERTILE, G_ON);

        gSPSetGeometryMode(gDisplayListHead++, G_TEXTURE_GEN);
        gSPClearGeometryMode(gDisplayListHead++, G_TEXTURE_GEN_LINEAR);
        gDPSetCombineMode(gDisplayListHead++, G_CC_MODULATEIDECALA, G_CC_PASS2);

        gCurrentRenderState->unk_27 = 1;
    }
}

void GeoRender_SelectMaterialSlot(s16 arg0) {
    if (arg0 == gRenderStateCount) {
        return;
    }

    gCurrentRenderState->unk_08 = gDisplayListHead;

    gSPBranchList(gDisplayListHead++, NULL);

    gRenderStateCount = arg0;
    gCurrentRenderState = &gLayerStates[gRenderStateCount];

    if (gCurrentRenderState->rotation == NULL) {
        gCurrentRenderState->rotation = gDisplayListHead;
    } else if (gCurrentRenderState->unk_08 != NULL) {
        gSPBranchList(gCurrentRenderState->unk_08, gDisplayListHead);
    }
}

void GeoRender_SetTextureMode(s16 arg0) {
    if (((arg0 > 0) && (arg0 < 4)) || (arg0 == 0x84) || (arg0 == 6)) {
        gRenderState.unk_03 = gRenderState.posY;
    } else {
        gRenderState.unk_03 = 0;
    }
}

s16 GeoRender_NormalizeTextureFormat(s16 arg0) {
    s16 var_v1 = arg0 & 0xF;

    if (gRenderState.unk_01 < 0xFF) {
        switch (var_v1) {
            case 1:
                var_v1 = 8;
                break;
            case 2:
                var_v1 = 6;
                break;
            case 3:
                var_v1 = 7;
                break;
            case 4:
                var_v1 = 5;
                break;
        }
    }

    return var_v1;
}

void GeoRender_SubmitMaterial(s16 arg0, MtxF* arg1) {
    if ((gIsRenderInitialized != 0) && !(gRenderFlags & 2) && (gRenderState.unk_01 > 0)) {
        GeoRender_SetTextureMode(arg0);
        GeoRender_SelectMaterialSlot(GeoRender_NormalizeTextureFormat(arg0));
        gPipeSynced = 0;

        if (gCurrentRenderState->posX == 0) {
            GeoRender_SetRenderMode();
            GeoRender_ApplyMaterialState();
            gCurrentRenderState->posX = 1;
        }

        if (gRenderState.unk_08.rgba & 0xFF) {
            GeoRender_SetFogColor(&gRenderState);
        } else {
            GeoRender_RestoreRenderMode(&gRenderState);
        }

        if (gRenderState.unk_03 != 0) {
            GeoRender_EnableTextureGeneration(&gRenderState);
        } else {
            if (gCurrentRenderState->unk_27 == 1) {
                GeoRender_ApplyMaterialState();
            }

            if (gRenderState.unk_0C != 0) {
                GeoRender_BindTexture(&gRenderState);
            } else {
                GeoRender_DisableTexture(&gRenderState);
            }

            GeoRender_SetPrimitiveColor(&gRenderState);
            GeoRender_SetCombineTableEntry(&gRenderState);
        }

        if (arg1 != gCurrentRenderState->unk_0C) {
            gCurrentRenderState->unk_0C = arg1;
            gSPMatrix(gDisplayListHead++, (u32)arg1 & 0x1FFFFFFF, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        }
    }
}

void GeoRender_SubmitDisplayList(Gfx* arg0, s32 arg1) {
    if ((gIsRenderInitialized != 0) && !(gRenderFlags & 2) && (gRenderState.unk_01 > 0)) {
        if (arg0 != NULL) {
            if (((u32)arg0 >= 0x81000000) && ((u32)arg0 < 0x90000000)) {
                gSPDisplayList(gDisplayListHead++, Memmap_GetFragmentVaddr((u32)arg0));
            } else {
                gSPDisplayList(gDisplayListHead++, arg0);
            }
        }

        if (arg1 != 0) {
            GeoRender_ApplyMaterialState();
        }
    }
}

void GeoRender_SetMaterialParams(Color_RGBA8_u32 arg0, u8 arg1, u32 arg2) {
    gRenderState.unk_08.rgba = arg0.rgba;
    gRenderState.unk_01 = arg1;
    gRenderState.posY = arg2;
}

void GeoRender_SetMaterialTexture(s32 arg0, Color_RGBA8_u32 arg1, unk_D_86002F34_alt11_018* arg2, unk_D_86002F34_alt11_018* arg3,
                   s32 arg4) {
    gRenderState.posX = arg0;
    gRenderState.rotation.rgba = arg1.rgba;
    gRenderState.unk_0C = arg2;
    gRenderState.unk_10 = arg3;
    gRenderState.unk_14 = arg4;
}

void GeoRender_InitMaterialState(s32 arg0, s32 arg1) {
    s32 i;
    unk_D_800ABB28* ptr = gLayerStates;

    gDPPipeSync(gDisplayListHead++);
    gDPSetCycleType(gDisplayListHead++, G_CYC_2CYCLE);

    if (arg0 & 1) {
        gSPSetGeometryMode(gDisplayListHead++, G_ZBUFFER);
    } else {
        gSPClearGeometryMode(gDisplayListHead++, G_ZBUFFER);
    }

    for (i = 0; i < 10; i++, ptr++) {
        ptr->rotation = NULL;
        ptr->unk_08 = NULL;

        ptr->posX = 0;
        ptr->unk_0C = 0;

        ptr->unk_10.rgba = 0xFFFFFFFF;
        ptr->unk_14.rgba = 0xFFFFFF00;

        ptr->unk_18 = NULL;
        ptr->unk_1C = NULL;
        ptr->unk_20 = NULL;

        ptr->unk_24 = i;
        ptr->unk_25 = 0;
        ptr->unk_27 = 0;
        ptr->unk_26 = 0xFF;
    }

    gRenderState.posX = 0;
    gRenderState.unk_01 = 0xFF;
    gRenderState.posY = 0;
    gRenderState.unk_03 = 0;
    gRenderState.rotation.rgba = -1;
    gRenderState.unk_08.rgba = 0xFFFFFF00;
    gRenderState.unk_0C = 0;
    gRenderState.unk_10 = 0;
    gRenderState.unk_14 = 0;

    gRenderModeIndex = arg0;
    gRenderFlags = arg1;

    gLayerStates[0].rotation = gDisplayListHead;

    gRenderStateCount = 0;
    gCurrentRenderState = gLayerStates;

    gIsRenderInitialized = 1;
}

void GeoRender_FlushMaterialSlots(void) {
    s32 sp1C = 0;
    Gfx* temp_t0;
    s32 temp_v0;

    GeoRender_SelectMaterialSlot(9);

    if (gLayerStates[0].unk_08 != NULL) {
        while (sp1C < 9) {
            temp_v0 = sp1C + 1;
            temp_t0 = gLayerStates[sp1C].unk_08;
            sp1C++;

            while (gLayerStates[temp_v0].rotation == NULL) {
                temp_v0 = sp1C + 1;
                sp1C++;
            }

            gSPBranchList(temp_t0, gLayerStates[sp1C].rotation);
        }
    }

    GeoRender_ApplyMaterialState();

    if (gRenderModeIndex & 1) {
        gSPClearGeometryMode(gDisplayListHead++, G_ZBUFFER);
    }

    gIsRenderInitialized = 0;
}
