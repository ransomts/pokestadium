#ifndef _12D80_H_
#define _12D80_H_

#include "global.h"

typedef struct unk_D_800AB970 {
    /* 0x000 */ Vec3f unk_000[1];
    /* 0x00C */ char unk00C[0x174];
    /* 0x180 */ s32 unk_180;
    /* 0x184 */ char unk184[0xC];
} unk_D_800AB970; // size = 0x190?

typedef struct unk_D_800ABB00 {
    /* 0x00 */ void* unk_00;
    /* 0x04 */ void* unk_04;
    /* 0x08 */ char unk08[0x8];
} unk_D_800ABB00; // size >= 0x10?

typedef struct unk_D_800ABB28 {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ Gfx* unk_04;
    /* 0x08 */ Gfx* unk_08;
    /* 0x0C */ MtxF* unk_0C;
    /* 0x10 */ Color_RGBA8_u32 unk_10;
    /* 0x14 */ Color_RGBA8_u32 unk_14;
    /* 0x18 */ unk_D_86002F34_alt11_018* unk_18;
    /* 0x1C */ struct unk_D_800ABB28* unk_1C;
    /* 0x20 */ Gfx* unk_20;
    /* 0x24 */ u8 unk_24;
    /* 0x24 */ u8 unk_25;
    /* 0x24 */ u8 unk_26;
    /* 0x24 */ u8 unk_27;
} unk_D_800ABB28; // size = 0x28

typedef struct unk_D_800ABB10 {
    /* 0x00 */ u8 unk_00;
    /* 0x01 */ u8 unk_01;
    /* 0x02 */ u8 unk_02;
    /* 0x03 */ u8 unk_03;
    /* 0x04 */ Color_RGBA8_u32 unk_04;
    /* 0x08 */ Color_RGBA8_u32 unk_08;
    /* 0x0C */ unk_D_86002F34_alt11_018* unk_0C;
    /* 0x10 */ unk_D_800ABB28* unk_10;
    /* 0x14 */ Gfx* unk_14;
} unk_D_800ABB10; // size = 0x18?

extern s32 gRenderFrameCounter;
extern u16 gAnimationFrame;
extern CameraStruct* gCurrentCameraNode;
extern unk_D_86002F34_alt1* gCurrentTextureNode;
extern unk_D_86002F34_alt1* gCurrentLightNode;
extern CameraStruct* gActiveCameraNode;
extern unk_D_86002F34_alt1* gActiveNode;
extern Fragment2_1GraphNode* gDefaultGraphRoot;
extern unk_D_86002F34_alt11* gActiveLayerNode;

void Matrix_ResetStack(void);
void Matrix_SetIdentityAtCurrent(void);
void Matrix_SetCurrent(MtxF* arg0);
void Matrix_PushMultiply(MtxF* arg0);
void Matrix_PushScale(Vec3f* arg0);
MtxF* Matrix_GetRelative(s32 arg0);
MtxF* Matrix_GetAbsolute(s32 arg0);
void Graph_ResetScaleStack(void);
void Graph_PushScale(Vec3f* arg0);
Vtx* Graph_MakeQuadVertices(unk_D_86002F34_00C_0CC* arg0, unk_D_86002F34_00C_040* arg1);
void Graph_DrawColoredQuad(unk_D_86002F34_00C_0CC* arg0, unk_D_86002F34_00C_040* arg1);
void Graph_MakeRotatedVertex(Vtx* arg0, unk_D_86002F34_00C_0CC* arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5, s16 arg6, s16 arg7);
Vtx* Graph_MakeInterpOctagon(unk_D_86002F34_00C_0CC* arg0);
void Graph_DrawOctagon(unk_D_86002F34_00C_0CC* arg0, UNUSED unk_D_86002F34_00C_040* arg1);
void Graph_RenderNode(unk_D_86002F34_00C_0CC* arg0, unk_D_86002F34_00C_040* arg1);
void Graph_VisitVisibleChildren(GraphNode* arg0);
void Graph_VisitNodePre(GraphNode* arg0);
void Graph_SetupCamera(GraphNode* arg0);
void TextureNode_VisitChildren(GraphNode* arg0);
void Graph_SetupLights(GraphNode* arg0);
void CameraNode_Render(GraphNode* arg0);
void CameraNode_SetProjection(GraphNode* arg0);
void CameraNode_SetLookAtProjection(GraphNode* arg0);
void CameraNode_FillRect(GraphNode* arg0);
void Graph_FillDepthRect(UNUSED GraphNode* arg0);
void Graph_NoOp(UNUSED GraphNode* arg0);
void Graph_SetFog(GraphNode* arg0);
void Graph_AddLight(GraphNode* arg0);
void Graph_NoOp2(UNUSED GraphNode* arg0);
void Graph_ApplyLights(GraphNode* arg0);
void LayerNode_Process(GraphNode* arg0);
void Graph_ConditionalDepthRender(GraphNode* arg0);
void Graph_VisitChildOffset(GraphNode* arg0);
void Graph_PushRotateTranslate(GraphNode* arg0);
void Graph_PushScaleNode(GraphNode* arg0);
void ObjectNode_Transform(GraphNode* arg0);
void Graph_DrawModel(GraphNode* arg0);
void Graph_RenderComplexObject(GraphNode* arg0);
void Graph_DrawModelWithTransform(GraphNode* arg0);
void Graph_DrawModelWithCompose(GraphNode* arg0);
void Graph_DrawModelSimple(GraphNode* arg0);
void Graph_DrawAnimatedSprite(GraphNode* arg0);
void Graph_RecordNodePosition(s32 arg0);
void Graph_RecordPosAndVisit(GraphNode* arg0);
void Graph_VisitChildrenOnly(GraphNode* arg0);
void Graph_RenderBillboard(GraphNode* arg0);
void Graph_SetTextureState(GraphNode* arg0);
void Graph_TraverseAndSetGlobals(GraphNode* arg0, s32 arg1);
void Gfx_SetRenderMode(s32 arg0);
void Gfx_FinishFrame(void);
s32 Graph_IsFrameCurrent(void);
Vec3f* Graph_GetRecordedPosition(Fragment2_1GraphNode* arg0, s16 arg1, Vec3f* arg2);
void Gfx_SetCombineMode(Gfx* arg0, arg1_func_81407874_014_000_010* arg1);
void Gfx_SyncPipe(void);
void Graph_SetRenderMode(void);
void Gfx_ResetRenderState(void);
void Gfx_UpdateFogColor(unk_D_800ABB10* arg0);
void Gfx_ApplyRenderMode(UNUSED unk_D_800ABB10* arg0);
void Gfx_UpdatePrimColor(unk_D_800ABB10* arg0);
void GeoRender_SetCombineTableEntry(unk_D_800ABB10* arg0);
void Gfx_DisableTexture(UNUSED unk_D_800ABB10* arg0);
void Gfx_EnableTexture(unk_D_800ABB10* arg0);
void Gfx_SetupTextureBlock(UNUSED unk_D_800ABB10* arg0);
void Gfx_SetRenderLayer(s16 arg0);
void Gfx_UpdateLayerAlpha(s16 arg0);
s16 Gfx_GetLayerIndex(s16 arg0);
void Graph_BeginLayerRender(s16 arg0, MtxF* arg1);
void Gfx_DrawDisplayList(Gfx* arg0, s32 arg1);
void Gfx_SetColor(Color_RGBA8_u32 arg0, u8 arg1, u32 arg2);
void Gfx_SetTextureParams(s32 arg0, Color_RGBA8_u32 arg1, unk_D_86002F34_alt11_018* arg2, unk_D_86002F34_alt11_018* arg3, s32 arg4);
void Gfx_InitRenderState(s32 arg0, s32 arg1);
void Gfx_FlushLayers(void);

#endif // _12D80_H_
