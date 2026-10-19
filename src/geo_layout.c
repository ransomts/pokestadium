#include "geo_layout.h"
#include "src/11BA0.h"
#include "src/F420.h"
#include "src/util.h"

static GeoLayoutCommandProc GeoLayoutJumpTable[] = {
    geo_layout_cmd_branch_and_link,
    geo_layout_cmd_end,
    geo_layout_cmd_jump,
    geo_layout_cmd_branch,
    geo_layout_cmd_return,
    geo_layout_cmd_open_node,
    geo_layout_cmd_close_node,
    GeoLayoutCmd_AddNodeFromCmd,
    GeoLayoutCmd_SetNodeCallback,
    GeoLayoutCmd_AllocNode,
    GeoLayoutCmd_AllocAltNodeWithParent,
    GeoLayoutCmd_CreateCameraNode,
    geo_layout_cmd_create_type3,
    geo_layout_cmd_create_type4,
    geo_layout_cmd_create_ortho,
    geo_layout_cmd_create_perspective,
    geo_layout_cmd_create_background,
    geo_layout_cmd_create_clear_depth,
    geo_layout_cmd_noop,
    GeoLayoutCmd_CreateColorRectNode,
    GeoLayoutCmd_CreateColoredVertexNode,
    geo_layout_cmd_skip,
    geo_layout_cmd_create_ambient_light,
    GeoLayoutCmd_CreateMeshNode,
    geo_layout_cmd_create_shadow,
    geo_layout_cmd_create_cull_distance,
    geo_layout_cmd_create_switch_case,
    GeoLayoutCmd_CreateTransformNode,
    GeoLayoutCmd_CreateScaleNode,
    geo_layout_cmd_create_animated_part,
    GeoLayoutCmd_CreateDisplayListNode,
    GeoLayoutCmd_CreateShadowNode,
    GeoLayoutCmd_CreateBillboardNode,
    geo_layout_cmd_create_scale,
    geo_layout_cmd_create_display_list,
    geo_layout_cmd_create_shadow_texture,
    geo_layout_cmd_create_anchor,
    geo_layout_cmd_set_node_flag4,
    geo_layout_cmd_create_group,
};

static MemoryBlock* gGraphNodePool;
static GraphNode* gCurRootGraphNode;
static u32 gGeoLayoutStack[16];
static GraphNode* gCurGraphNodeList[32];
static s16 gCurGraphNodeIndex;
static s16 gGeoLayoutStackIndex;
static s16 gGeoLayoutStackDepth;
static s16 gGeoLayoutReturnIndex;
static u8* gGeoLayoutCommand;

/*
  0x00: Branch and store return address
   cmd+0x04: void *branchTarget
*/
void geo_layout_cmd_branch_and_link(void) {
    u8* cmd = (void*)gGeoLayoutCommand;

    cmd += 0;

    gGeoLayoutStack[gGeoLayoutStackIndex++] = (uintptr_t)(cmd + CMD_PROCESS_OFFSET(8));
    gGeoLayoutStack[gGeoLayoutStackIndex++] = (gCurGraphNodeIndex << 16) + gGeoLayoutReturnIndex;
    gGeoLayoutReturnIndex = gGeoLayoutStackIndex;
    gGeoLayoutCommand = Util_ConvertAddrToVirtAddr(cur_geo_cmd_ptr(0x04));
}

// 0x01: Terminate geo layout
void geo_layout_cmd_end(void) {
    gGeoLayoutStackIndex = gGeoLayoutReturnIndex;
    gGeoLayoutReturnIndex = gGeoLayoutStack[--gGeoLayoutStackIndex] & 0xFFFF;
    gCurGraphNodeIndex = gGeoLayoutStack[gGeoLayoutStackIndex] >> 16;
    gGeoLayoutCommand = (u8*)gGeoLayoutStack[--gGeoLayoutStackIndex];
}

/*
  0x02: Jump to address
    cmd+0x04: void *jumpTarget
*/
void geo_layout_cmd_jump(void) {
    u8* cmd = (void*)gGeoLayoutCommand;

    cmd += 0;

    gGeoLayoutCommand = Util_ConvertAddrToVirtAddr(cur_geo_cmd_ptr(0x04));
}

/*
  0x03: Branch
    cmd+0x04: void *branchTarget
*/
void geo_layout_cmd_branch(void) {
    u8* cmd = (void*)gGeoLayoutCommand;

    cmd += 0;

    // unlike in sm64, this argument doesnt seem to be optional.
    gGeoLayoutStack[gGeoLayoutStackIndex++] = (uintptr_t)(cmd + CMD_PROCESS_OFFSET(8));
    gGeoLayoutCommand = Util_ConvertAddrToVirtAddr(cur_geo_cmd_ptr(0x04));
}

// 0x04: Return from branch
void geo_layout_cmd_return(void) {
    gGeoLayoutCommand = (u8*)gGeoLayoutStack[--gGeoLayoutStackIndex];
}

// 0x05: Open node
void geo_layout_cmd_open_node(void) {
    gCurGraphNodeList[gCurGraphNodeIndex + 1] = gCurGraphNodeList[gCurGraphNodeIndex];
    gCurGraphNodeIndex++;
    gGeoLayoutCommand += 0x04 << CMD_SIZE_SHIFT;
}

// 0x06: Close node
void geo_layout_cmd_close_node(void) {
    gCurGraphNodeIndex--;
    gGeoLayoutCommand += 0x04 << CMD_SIZE_SHIFT;
}

void GraphNode_AddToCurrent(GraphNode* arg0) {
    if (arg0 != NULL) {
        gCurGraphNodeList[gCurGraphNodeIndex] = arg0;
        if (gCurGraphNodeIndex == 0) {
            if (gCurRootGraphNode == NULL) {
                gCurRootGraphNode = arg0;
            }
        } else {
            GraphNode_AddChild(gCurGraphNodeList[gCurGraphNodeIndex - 1], arg0);
        }
    }
}

void GeoLayoutCmd_AddNodeFromCmd(void) {
    GeoCmd_AddNode* cmd = (GeoCmd_AddNode*)gGeoLayoutCommand;

    GraphNode_AddToCurrent(&cmd->unk_04->unk_00);

    gGeoLayoutCommand += sizeof(GeoCmd_AddNode);
}

void GeoLayoutCmd_SetNodeCallback(void) {
    GeoCmd_SetCallback* cmd = (GeoCmd_SetCallback*)gGeoLayoutCommand;

    if (gCurGraphNodeList[gCurGraphNodeIndex] != NULL) {
        GraphNode_SetCallback(gCurGraphNodeList[gCurGraphNodeIndex], cmd->unk_04, cmd->unk_08);
    }

    gGeoLayoutCommand += sizeof(GeoCmd_SetCallback);
}

void GeoLayoutCmd_AllocNode(void) {
    GraphNode_AddToCurrent(GraphNode_AllocInit(gGraphNodePool, NULL));

    gGeoLayoutCommand += sizeof(GeoCmd_AllocNode);
}

void GeoLayoutCmd_AllocAltNodeWithParent(void) {
    GeoCmd_AllocAltNode* cmd = (GeoCmd_AllocAltNode*)gGeoLayoutCommand;

    GraphNode_AddToCurrent(GraphNodeAlt_AllocInitParent(gGraphNodePool, NULL, cmd->unk_04));

    gGeoLayoutCommand += sizeof(GeoCmd_AllocAltNode);
}

void GeoLayoutCmd_CreateCameraNode(void) {
    GeoCmd_CreateCamera* cmd = (GeoCmd_CreateCamera*)gGeoLayoutCommand;
    CameraStruct* temp_v0 =
        CameraNode_Create(gGraphNodePool, NULL, cmd->unk_04, cmd->unk_06, cmd->unk_08, cmd->unk_0A);

    if (temp_v0 != NULL) {
        temp_v0->unk_24.fovy = cmd->unk_02;
        GraphNode_SetPositionFromVec3s(&temp_v0->unk_60.at, &cmd->unk_0C);
        Camera_SetViewParameters(&temp_v0->unk_60.at, &temp_v0->unk_60.eye, cmd->unk_16, (cmd->unk_12 << 0xF) / 180,
                      (cmd->unk_14 << 0xF) / 180);
    }

    GraphNode_AddToCurrent(&temp_v0->unk_00);

    gGeoLayoutCommand += sizeof(GeoCmd_CreateCamera);
}

void geo_layout_cmd_create_type3(void) {
    GeoCmd_CreateType3* cmd = (GeoCmd_CreateType3*)gGeoLayoutCommand;

    GraphNode_AddToCurrent(GeoNode_CreateType3(gGraphNodePool, NULL, cmd->unk_02));

    gGeoLayoutCommand += sizeof(GeoCmd_CreateType3);
}

void geo_layout_cmd_create_type4(void) {
    GeoCmd_CreateType4* cmd = (GeoCmd_CreateType4*)gGeoLayoutCommand;

    GraphNode_AddToCurrent(GeoNode_CreateType4(gGraphNodePool, NULL, cmd->unk_02));

    gGeoLayoutCommand += sizeof(GeoCmd_CreateType4);
}

void geo_layout_cmd_create_ortho(void) {
    GeoCmd_CreateOrtho* cmd = (GeoCmd_CreateOrtho*)gGeoLayoutCommand;

    GraphNode_AddToCurrent(GeoNode_CreateOrtho(gGraphNodePool, NULL, cmd->unk_02));

    gGeoLayoutCommand += sizeof(GeoCmd_CreateOrtho);
}

void geo_layout_cmd_create_perspective(void) {
    GeoCmd_CreatePerspective* cmd = (GeoCmd_CreatePerspective*)gGeoLayoutCommand;

    GraphNode_AddToCurrent(GeoNode_CreatePerspective(gGraphNodePool, NULL, cmd->unk_02));

    gGeoLayoutCommand += sizeof(GeoCmd_CreatePerspective);
}

void geo_layout_cmd_create_background(void) {
    GeoCmd_CreateBackground* cmd = (GeoCmd_CreateBackground*)gGeoLayoutCommand;

    GraphNode_AddToCurrent(GeoNode_CreateBackground(gGraphNodePool, NULL, cmd->unk_01, cmd->unk_02, cmd->unk_03));

    gGeoLayoutCommand += sizeof(GeoCmd_CreateBackground);
}

void geo_layout_cmd_create_clear_depth(void) {
    GraphNode_AddToCurrent(GeoNode_CreateClearDepth(gGraphNodePool, NULL));

    gGeoLayoutCommand += sizeof(GeoCmd_CreateClearDepth);
}

void geo_layout_cmd_noop(void) {
}

void GeoLayoutCmd_CreateColorRectNode(void) {
    GeoCmd_CreateColorRect* cmd = (GeoCmd_CreateColorRect*)gGeoLayoutCommand;

    GraphNode_AddToCurrent(ColorRectNode_Create(gGraphNodePool, NULL, cmd->unk_04, cmd->unk_06, cmd->r, cmd->g, cmd->b, 0xFF));

    gGeoLayoutCommand += sizeof(GeoCmd_CreateColorRect);
}

void GeoLayoutCmd_CreateColoredVertexNode(void) {
    GeoCmd_CreateColoredVertex* cmd = (GeoCmd_CreateColoredVertex*)gGeoLayoutCommand;

    GraphNode_AddToCurrent(ColoredVertexNode_Create(gGraphNodePool, NULL, (cmd->unk_04 << 0xF) / 180, (cmd->unk_06 << 0xF) / 180, cmd->r,
                                cmd->g, cmd->b, cmd->a));

    gGeoLayoutCommand += sizeof(GeoCmd_CreateColoredVertex);
}

void geo_layout_cmd_skip(void) {
    gGeoLayoutCommand += sizeof(GeoCmd_Skip);
}

void geo_layout_cmd_create_ambient_light(void) {
    GeoCmd_CreateAmbientLight* cmd = (GeoCmd_CreateAmbientLight*)gGeoLayoutCommand;

    GraphNode_AddToCurrent(GeoNode_CreateAmbientLight(gGraphNodePool, NULL, cmd->r, cmd->g, cmd->b));

    gGeoLayoutCommand += sizeof(GeoCmd_CreateAmbientLight);
}

void GeoLayoutCmd_CreateMeshNode(void) {
    GeoCmd_CreateMesh* cmd = (GeoCmd_CreateMesh*)gGeoLayoutCommand;

    GraphNode_AddToCurrent(MeshNode_Create(gGraphNodePool, NULL, cmd->unk_02, cmd->unk_08, cmd->unk_04, cmd->unk_0C, cmd->unk_06,
                                cmd->unk_10));

    gGeoLayoutCommand += sizeof(GeoCmd_CreateMesh);
}

void geo_layout_cmd_create_shadow(void) {
    GeoCmd_CreateShadow* cmd = (GeoCmd_CreateShadow*)gGeoLayoutCommand;

    GraphNode_AddToCurrent(GeoNode_CreateShadow(gGraphNodePool, NULL, cmd->unk_01, cmd->unk_04, cmd->unk_06, cmd->unk_02));

    gGeoLayoutCommand += sizeof(GeoCmd_CreateShadow);
}

void geo_layout_cmd_create_cull_distance(void) {
    GeoCmd_CreateCullDist* cmd = (GeoCmd_CreateCullDist*)gGeoLayoutCommand;

    GraphNode_AddToCurrent(GeoNode_CreateCullDistance(gGraphNodePool, NULL, cmd->unk_04, cmd->unk_06));

    gGeoLayoutCommand += sizeof(GeoCmd_CreateCullDist);
}

void geo_layout_cmd_create_switch_case(void) {
    GeoCmd_CreateSwitchCase* cmd = (GeoCmd_CreateSwitchCase*)gGeoLayoutCommand;

    GraphNode_AddToCurrent(GeoNode_CreateSwitchCase(gGraphNodePool, NULL, cmd->unk_01, cmd->unk_02));

    gGeoLayoutCommand += sizeof(GeoCmd_CreateSwitchCase);
}

void GeoLayoutCmd_CreateTransformNode(void) {
    Vec3s sp30;
    Vec3f sp24;
    UNUSED s32 pad;
    GeoCmd_CreateTransform* cmd = (GeoCmd_CreateTransform*)gGeoLayoutCommand;

    GraphNode_SetPositionFromVec3s(&sp24, &cmd->unk_0A);
    Vec3s_Set(&sp30, (cmd->unk_04 << 0xF) / 180, (cmd->unk_06 << 0xF) / 180, (cmd->unk_08 << 0xF) / 180);
    GraphNode_AddToCurrent(TransformNode_Create(gGraphNodePool, NULL, &sp24, &sp30));

    gGeoLayoutCommand += sizeof(GeoCmd_CreateTransform);
}

void GeoLayoutCmd_CreateScaleNode(void) {
    Vec3f sp24;
    GeoCmd_CreateScale* cmd = (GeoCmd_CreateScale*)gGeoLayoutCommand;

    sp24.x = cmd->unk_04 / 65536.0f;
    sp24.y = cmd->unk_08 / 65536.0f;
    sp24.z = cmd->unk_0C / 65536.0f;
    GraphNode_AddToCurrent(GeoNode_CreateTranslate(gGraphNodePool, NULL, &sp24));

    gGeoLayoutCommand += sizeof(GeoCmd_CreateScale);
}

void geo_layout_cmd_create_animated_part(void) {
    Vec3f sp3C;
    s16 var_a3 = 1;
    GeoCmd_CreateAnimatedPart* cmd = (GeoCmd_CreateAnimatedPart*)gGeoLayoutCommand;

    sp3C.x = cmd->unk_10 / 65536.0f;
    sp3C.y = cmd->unk_14 / 65536.0f;
    sp3C.z = cmd->unk_18 / 65536.0f;

    if (cmd->unk_02 & 1) {
        var_a3 = 0;
    }

    if (cmd->unk_02 & 2) {
        var_a3 |= 2;
    }

    GraphNode_AddToCurrent(
        GeoNode_CreateAnimatedPart(gGraphNodePool, NULL, cmd->unk_01, var_a3, cmd->unk_03, &cmd->unk_04, &cmd->unk_0A, &sp3C));

    gGeoLayoutCommand += sizeof(GeoCmd_CreateAnimatedPart);
}

void GeoLayoutCmd_CreateDisplayListNode(void) {
    GeoCmd_CreateDisplayList* cmd = (GeoCmd_CreateDisplayList*)gGeoLayoutCommand;

    GraphNode_AddToCurrent(DisplayListNode_Create(gGraphNodePool, NULL, cmd->unk_01, cmd->unk_04, cmd->unk_02));

    gGeoLayoutCommand += sizeof(GeoCmd_CreateDisplayList);
}

void GeoLayoutCmd_CreateShadowNode(void) {
    Vec3s sp40;
    Vec3f sp34;
    Vec3f sp28;
    Fragment2_1GraphNode* tmp;
    GeoCmd_CreateShadowNode* cmd = (GeoCmd_CreateShadowNode*)gGeoLayoutCommand;

    GraphNode_SetPositionFromVec3s(&sp34, &cmd->unk_0A);

    sp28.x = cmd->unk_10 / 100.0f;
    sp28.y = cmd->unk_12 / 100.0f;
    sp28.z = cmd->unk_14 / 100.0f;

    Vec3s_Set(&sp40, (cmd->unk_04 << 0xF) / 180, (cmd->unk_06 << 0xF) / 180, (cmd->unk_08 << 0xF) / 180);
    tmp = GeoNode_CreateModelPart(gGraphNodePool, NULL, cmd->unk_02, &sp34, &sp40, &sp28);
    GraphNode_AddToCurrent(tmp);

    gGeoLayoutCommand += sizeof(GeoCmd_CreateShadowNode);
}

void GeoLayoutCmd_CreateBillboardNode(void) {
    Vec3f sp34;
    Vec3s sp2C;
    unk_D_86002F34_alt8* tmp;
    GeoCmd_CreateBillboard* cmd = (GeoCmd_CreateBillboard*)gGeoLayoutCommand;

    GraphNode_SetPositionFromVec3s(&sp34, &cmd->unk_0A);
    Vec3s_Set(&sp2C, (cmd->unk_04 << 0xF) / 180, (cmd->unk_06 << 0xF) / 180, (cmd->unk_08 << 0xF) / 180);
    tmp = GeoNode_CreateDisplayListMatrixFromTransform(gGraphNodePool, NULL, cmd->unk_01, cmd->unk_10, &sp34, &sp2C);
    GraphNode_AddToCurrent(tmp);

    gGeoLayoutCommand += sizeof(GeoCmd_CreateBillboard);
}

void geo_layout_cmd_create_scale(void) {
    Vec3f sp2C;
    unk_D_86002F34_alt9* tmp;
    GeoCmd_CreateScaleBillboard* cmd = (GeoCmd_CreateScaleBillboard*)gGeoLayoutCommand;

    GraphNode_SetPositionFromVec3s(&sp2C, &cmd->unk_02);
    tmp = BillboardNode_Create(gGraphNodePool, NULL, cmd->unk_01, cmd->unk_0C, &sp2C, cmd->unk_08 / 65536.0f);
    GraphNode_AddToCurrent(tmp);

    gGeoLayoutCommand += sizeof(GeoCmd_CreateScaleBillboard);
}

void geo_layout_cmd_create_display_list(void) {
    GeoCmd_CreateSimpleGfx* cmd = (GeoCmd_CreateSimpleGfx*)gGeoLayoutCommand;

    GraphNode_AddToCurrent(SimpleGfxNode_Create(gGraphNodePool, NULL, cmd->unk_01, cmd->unk_04));

    gGeoLayoutCommand += sizeof(GeoCmd_CreateSimpleGfx);
}

void geo_layout_cmd_create_shadow_texture(void) {
    GeoCmd_CreateShadowTex* cmd = (GeoCmd_CreateShadowTex*)gGeoLayoutCommand;

    GraphNode_AddToCurrent(GeoNode_CreateShadowTexture(gGraphNodePool, NULL, cmd->unk_01, cmd->unk_02, cmd->unk_04, cmd->unk_08, cmd->unk_0A,
                                cmd->r, cmd->g, cmd->b, cmd->a));

    gGeoLayoutCommand += sizeof(GeoCmd_CreateShadowTex);
}

void geo_layout_cmd_create_anchor(void) {
    GeoCmd_CreateAnchor* cmd = (GeoCmd_CreateAnchor*)gGeoLayoutCommand;

    GraphNode_AddToCurrent(GeoNode_CreateAnchor(gGraphNodePool, NULL, cmd->unk_02));

    gGeoLayoutCommand += sizeof(GeoCmd_CreateAnchor);
}

void geo_layout_cmd_set_node_flag4(void) {
    GeoCmd_SetNodeFlag4* cmd = (GeoCmd_SetNodeFlag4*)gGeoLayoutCommand;

    if (gCurGraphNodeList[gCurGraphNodeIndex] != NULL) {
        gCurGraphNodeList[gCurGraphNodeIndex]->unk_02 |= 4;
    }

    gGeoLayoutCommand += sizeof(GeoCmd_SetNodeFlag4);
}

void geo_layout_cmd_create_group(void) {
    GeoCmd_CreateGroup* cmd = (GeoCmd_CreateGroup*)gGeoLayoutCommand;

    GraphNode_AddToCurrent(GeoNode_CreateGroup(gGraphNodePool, NULL, cmd->unk_01, cmd->unk_04, cmd->unk_06, cmd->unk_08, cmd->unk_0A,
                                cmd->unk_02, cmd->unk_03, cmd->unk_0C, cmd->r, cmd->g, cmd->b, cmd->a));

    gGeoLayoutCommand += sizeof(GeoCmd_CreateGroup);
}

GraphNode* process_geo_layout(MemoryBlock* pool, void* segptr) {
    // set by register_scene_graph_node when gCurGraphNodeIndex is 0
    // and gCurRootGraphNode is NULL
    gCurRootGraphNode = NULL;

    // gGeoNumViews seems to have been removed in this version of geo_script.c
    gCurGraphNodeIndex = 0;

    gGeoLayoutStackIndex = 2;
    gGeoLayoutReturnIndex = 2; // stack index is often copied here?

    gGeoLayoutCommand = Util_ConvertAddrToVirtAddr(segptr);

    gGraphNodePool = pool;

    gCurGraphNodeList[0] = 0;

    gGeoLayoutStack[0] = 0;
    gGeoLayoutStack[1] = 0;

    while (gGeoLayoutCommand != NULL) {
        GeoLayoutJumpTable[gGeoLayoutCommand[0x00]]();
    }

    return gCurRootGraphNode;
}
