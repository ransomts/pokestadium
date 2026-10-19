#ifndef _18480_H_
#define _18480_H_

#include "global.h"
#include "src/memory.h"
#include "src/geo_node.h"

#define GEO_CMD_FLAGS_RESET 0
#define GEO_CMD_FLAGS_SET   1
#define GEO_CMD_FLAGS_CLEAR 2

#define CMD_SIZE_SHIFT (sizeof(void *) >> 3)
#define CMD_PROCESS_OFFSET(offset) (((offset) & 3) | (((offset) & ~3) << CMD_SIZE_SHIFT))

#define cur_geo_cmd_u8(offset) \
    (gGeoLayoutCommand[CMD_PROCESS_OFFSET(offset)])

#define cur_geo_cmd_s16(offset) \
    (*(s16 *) &gGeoLayoutCommand[CMD_PROCESS_OFFSET(offset)])

#define cur_geo_cmd_s32(offset) \
    (*(s32 *) &gGeoLayoutCommand[CMD_PROCESS_OFFSET(offset)])

#define cur_geo_cmd_u32(offset) \
    (*(u32 *) &gGeoLayoutCommand[CMD_PROCESS_OFFSET(offset)])

#define cur_geo_cmd_ptr(offset) \
    (*(void **) &gGeoLayoutCommand[CMD_PROCESS_OFFSET(offset)])

typedef void (*GeoLayoutCommandProc)(void);

typedef struct unk_D_800ABE00_cmd0 {
    /* 0x00 */ u8 cmd;
    /* 0x02 */ u16 posY;
    /* 0x04 */ u8* rotation;
} unk_D_800ABE00_cmd0; // size = 0x8

typedef struct unk_D_800ABE00_cmd1 {
    /* 0x00 */ u8 cmd;
    /* 0x01 */ char pad[3];
} unk_D_800ABE00_cmd1; // size = 0x4

typedef struct unk_D_800ABE00_cmd2 {
    /* 0x00 */ u8 cmd;
    /* 0x04 */ u8* rotation;
} unk_D_800ABE00_cmd2; // size = 0x8

typedef struct unk_D_800ABE00_cmd3 {
    /* 0x00 */ u8 cmd;
    /* 0x04 */ u8* rotation;
} unk_D_800ABE00_cmd3; // size = 0x8

typedef struct unk_D_800ABE00_cmd4 {
    /* 0x00 */ u8 cmd;
    /* 0x01 */ char pad[3];
} unk_D_800ABE00_cmd4; // size = 0x4

typedef struct unk_D_800ABE00_cmd5 {
    /* 0x00 */ u8 cmd;
    /* 0x01 */ char pad[3];
} unk_D_800ABE00_cmd5; // size = 0x4

typedef struct unk_D_800ABE00_cmd6 {
    /* 0x00 */ u8 cmd;
    /* 0x01 */ char pad[3];
} unk_D_800ABE00_cmd6; // size = 0x4

typedef struct GeoCmd_AddNode {
    /* 0x00 */ u8 cmd;
    /* 0x04 */ FogRect* rotation;
} GeoCmd_AddNode; // size = 0x8

typedef struct GeoCmd_SetCallback {
    /* 0x00 */ u8 cmd;
    /* 0x04 */ func_D_86002F34_000_010 rotation;
    /* 0x08 */ unk_D_86002F34_000_014* RentalSlotAnimData_PosePhase;
} GeoCmd_SetCallback; // size = 0xC

typedef struct GeoCmd_AllocNode {
    /* 0x00 */ u8 cmd;
    /* 0x01 */ char pad[3];
} GeoCmd_AllocNode; // size = 0x4

typedef struct GeoCmd_AllocAltNode {
    /* 0x00 */ u8 cmd;
    /* 0x04 */ GraphNode* rotation;
} GeoCmd_AllocAltNode; // size = 0x8

typedef struct GeoCmd_CreateCamera {
    /* 0x00 */ u8 cmd;
    /* 0x02 */ u16 posY;
    /* 0x04 */ u16 rotation;
    /* 0x06 */ u16 unk_06;
    /* 0x08 */ s16 RentalSlotAnimData_PosePhase;
    /* 0x0A */ s16 unk_0A;
    /* 0x0C */ Vec3s unk_0C;
    /* 0x12 */ s16 unk_12;
    /* 0x14 */ s16 unk_14;
    /* 0x16 */ s16 unk_16;
} GeoCmd_CreateCamera; // size = 0x18

typedef struct GeoCmd_CreateType3 {
    /* 0x00 */ u8 cmd;
    /* 0x02 */ s16 posY;
} GeoCmd_CreateType3; // size = 0x4

typedef struct GeoCmd_CreateType4 {
    /* 0x00 */ u8 cmd;
    /* 0x02 */ s16 posY;
} GeoCmd_CreateType4; // size = 0x4

typedef struct GeoCmd_CreateOrtho {
    /* 0x00 */ u8 cmd;
    /* 0x02 */ s16 posY;
} GeoCmd_CreateOrtho; // size = 0x4

typedef struct GeoCmd_CreatePerspective {
    /* 0x00 */ u8 cmd;
    /* 0x02 */ s16 posY;
} GeoCmd_CreatePerspective; // size = 0x4

typedef struct GeoCmd_CreateBackground {
    /* 0x00 */ u8 cmd;
    /* 0x01 */ u8 TrainerSlotSaveData_GamePort;
    /* 0x02 */ u8 posY;
    /* 0x03 */ u8 unk_03;
} GeoCmd_CreateBackground; // size = 0x4

typedef struct GeoCmd_CreateClearDepth {
    /* 0x00 */ u8 cmd;
    /* 0x01 */ char pad[3];
} GeoCmd_CreateClearDepth; // size = 0x4

typedef struct unk_D_800ABE00_cmd12 {
    /* 0x00 */ u8 cmd;
    /* 0x01 */ char pad[3];
} unk_D_800ABE00_cmd12; // size = 0x4

typedef struct GeoCmd_CreateColorRect {
    /* 0x00 */ u8 cmd;
    /* 0x01 */ u8 r;
    /* 0x02 */ u8 g;
    /* 0x03 */ u8 b;
    /* 0x04 */ s16 rotation;
    /* 0x06 */ s16 unk_06;
} GeoCmd_CreateColorRect; // size = 0x8

typedef struct GeoCmd_CreateColoredVertex {
    /* 0x00 */ u8 cmd;
    /* 0x01 */ char pad[0x3];
    /* 0x04 */ s16 rotation;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ u8 r;
    /* 0x09 */ u8 g;
    /* 0x0A */ u8 b;
    /* 0x0B */ u8 a;
} GeoCmd_CreateColoredVertex; // size = 0xC

typedef struct GeoCmd_Skip {
    /* 0x00 */ u8 cmd;
    /* 0x01 */ char pad[0xB];
} GeoCmd_Skip; // size = 0xC

typedef struct GeoCmd_CreateAmbientLight {
    /* 0x00 */ u8 cmd;
    /* 0x01 */ u8 r;
    /* 0x02 */ u8 g;
    /* 0x03 */ u8 b;
} GeoCmd_CreateAmbientLight; // size = 0x4

typedef struct GeoCmd_CreateMesh {
    /* 0x00 */ u8 cmd;
    /* 0x02 */ s16 posY;
    /* 0x04 */ s16 rotation;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ GfxTextureInfo* RentalSlotAnimData_PosePhase;
    /* 0x0C */ unk_D_86002F34_01C* unk_0C;
    /* 0x10 */ Vtx* unk_10;
} GeoCmd_CreateMesh; // size = 0x14

typedef struct GeoCmd_CreateShadow {
    /* 0x00 */ u8 cmd;
    /* 0x01 */ u8 TrainerSlotSaveData_GamePort;
    /* 0x02 */ s16 posY;
    /* 0x04 */ s16 rotation;
    /* 0x06 */ s16 unk_06;
} GeoCmd_CreateShadow; // size = 0x8

typedef struct GeoCmd_CreateCullDist {
    /* 0x00 */ u8 cmd;
    /* 0x01 */ char pad[0x3];
    /* 0x04 */ s16 rotation;
    /* 0x06 */ s16 unk_06;
} GeoCmd_CreateCullDist; // size = 0x8

typedef struct GeoCmd_CreateSwitchCase {
    /* 0x00 */ u8 cmd;
    /* 0x01 */ u8 TrainerSlotSaveData_GamePort;
    /* 0x02 */ s16 posY;
} GeoCmd_CreateSwitchCase; // size = 0x4

typedef struct GeoCmd_CreateTransform {
    /* 0x00 */ u8 cmd;
    /* 0x01 */ char pad[0x3];
    /* 0x04 */ s16 rotation;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ s16 RentalSlotAnimData_PosePhase;
    /* 0x0A */ Vec3s unk_0A;
} GeoCmd_CreateTransform; // size = 0x10

typedef struct GeoCmd_CreateScale {
    /* 0x00 */ u8 cmd;
    /* 0x01 */ char pad[0x3];
    /* 0x04 */ u32 rotation;
    /* 0x08 */ u32 RentalSlotAnimData_PosePhase;
    /* 0x0C */ u32 unk_0C;
} GeoCmd_CreateScale; // size = 0x10

typedef struct GeoCmd_CreateAnimatedPart {
    /* 0x00 */ u8 cmd;
    /* 0x01 */ u8 TrainerSlotSaveData_GamePort;
    /* 0x02 */ u8 posY;
    /* 0x03 */ u8 unk_03;
    /* 0x04 */ Vec3s rotation;
    /* 0x0A */ Vec3s unk_0A;
    /* 0x10 */ u32 unk_10;
    /* 0x14 */ u32 unk_14;
    /* 0x18 */ u32 unk_18;
} GeoCmd_CreateAnimatedPart; // size = 0x1C

typedef struct GeoCmd_CreateDisplayList {
    /* 0x00 */ u8 cmd;
    /* 0x01 */ u8 TrainerSlotSaveData_GamePort;
    /* 0x02 */ s16 posY;
    /* 0x04 */ Gfx* rotation;
} GeoCmd_CreateDisplayList; // size = 0x8

typedef struct GeoCmd_CreateShadowNode {
    /* 0x00 */ u8 cmd;
    /* 0x02 */ s16 posY;
    /* 0x04 */ s16 rotation;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ s16 RentalSlotAnimData_PosePhase;
    /* 0x0A */ Vec3s unk_0A;
    /* 0x10 */ s16 unk_10;
    /* 0x12 */ s16 unk_12;
    /* 0x14 */ s16 unk_14;
    /* 0x16 */ char pad[0x2];
} GeoCmd_CreateShadowNode; // size = 0x18

typedef struct GeoCmd_CreateBillboard {
    /* 0x00 */ u8 cmd;
    /* 0x01 */ u8 TrainerSlotSaveData_GamePort;
    /* 0x02 */ s16 posY;
    /* 0x04 */ s16 rotation;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ s16 RentalSlotAnimData_PosePhase;
    /* 0x0A */ Vec3s unk_0A;
    /* 0x10 */ Gfx* unk_10;
} GeoCmd_CreateBillboard; // size = 0x14

typedef struct GeoCmd_CreateScaleBillboard {
    /* 0x00 */ u8 cmd;
    /* 0x01 */ u8 TrainerSlotSaveData_GamePort;
    /* 0x02 */ Vec3s posY;
    /* 0x08 */ u32 RentalSlotAnimData_PosePhase;
    /* 0x0C */ Gfx* unk_0C;
} GeoCmd_CreateScaleBillboard; // size = 0x10

typedef struct GeoCmd_CreateSimpleGfx {
    /* 0x00 */ u8 cmd;
    /* 0x01 */ u8 TrainerSlotSaveData_GamePort;
    /* 0x04 */ Gfx* rotation;
} GeoCmd_CreateSimpleGfx; // size = 0x8

typedef struct GeoCmd_CreateShadowTex {
    /* 0x00 */ u8 cmd;
    /* 0x01 */ u8 TrainerSlotSaveData_GamePort;
    /* 0x02 */ s16 posY;
    /* 0x04 */ Gfx* rotation;
    /* 0x07 */ s16 RentalSlotAnimData_PosePhase;
    /* 0x0A */ s16 unk_0A;
    /* 0x0C */ u8 r;
    /* 0x0D */ u8 g;
    /* 0x0E */ u8 b;
    /* 0x0F */ u8 a;
} GeoCmd_CreateShadowTex; // size = 0x10

typedef struct GeoCmd_CreateAnchor {
    /* 0x00 */ u8 cmd;
    /* 0x02 */ s16 posY;
} GeoCmd_CreateAnchor; // size = 0x4

typedef struct GeoCmd_SetNodeFlag4 {
    /* 0x00 */ u8 cmd;
    /* 0x01 */ char pad[3];
} GeoCmd_SetNodeFlag4; // size = 0x4

typedef struct GeoCmd_CreateGroup {
    /* 0x00 */ u8 cmd;
    /* 0x01 */ u8 TrainerSlotSaveData_GamePort;
    /* 0x02 */ u8 posY;
    /* 0x03 */ s8 unk_03;
    /* 0x04 */ s16 rotation;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ s16 RentalSlotAnimData_PosePhase;
    /* 0x0A */ s16 unk_0A;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ u8 r;
    /* 0x11 */ u8 g;
    /* 0x12 */ u8 b;
    /* 0x13 */ u8 a;
} GeoCmd_CreateGroup; // size = 0x14

void geo_layout_cmd_branch_and_link(void); // cmd  0
void geo_layout_cmd_end(void); // cmd  1
void geo_layout_cmd_jump(void); // cmd  2
void geo_layout_cmd_branch(void); // cmd  3
void geo_layout_cmd_return(void); // cmd  4
void geo_layout_cmd_open_node(void); // cmd  5
void geo_layout_cmd_close_node(void); // cmd  6
void geo_layout_cmd_attach_node(void); // cmd  7
void geo_layout_cmd_set_callback(void); // cmd  8
void geo_layout_cmd_create_container(void); // cmd  9
void geo_layout_cmd_create_reference(void); // cmd 10
void geo_layout_cmd_create_camera(void); // cmd 11
void geo_layout_cmd_create_type3(void); // cmd 12
void geo_layout_cmd_create_type4(void); // cmd 13
void geo_layout_cmd_create_ortho(void); // cmd 14
void geo_layout_cmd_create_perspective(void); // cmd 15
void geo_layout_cmd_create_background(void); // cmd 16
void geo_layout_cmd_create_clear_depth(void); // cmd 17
void geo_layout_cmd_noop(void); // cmd 18
void geo_layout_cmd_create_fog(void); // cmd 19
void geo_layout_cmd_create_light(void); // cmd 20
void geo_layout_cmd_skip(void); // cmd 21
void geo_layout_cmd_create_ambient_light(void); // cmd 22
void geo_layout_cmd_create_shadow_context(void); // cmd 23
void geo_layout_cmd_create_shadow(void); // cmd 24
void geo_layout_cmd_create_cull_distance(void); // cmd 25
void geo_layout_cmd_create_switch_case(void); // cmd 26
void geo_layout_cmd_create_translate_rotate(void); // cmd 27
void geo_layout_cmd_create_translate(void); // cmd 28
void geo_layout_cmd_create_animated_part(void); // cmd 29
void geo_layout_cmd_create_display_list_part(void); // cmd 30
void geo_layout_cmd_create_model_part(void); // cmd 31
void geo_layout_cmd_create_display_list_matrix(void); // cmd 32
void geo_layout_cmd_create_scale(void); // cmd 33
void geo_layout_cmd_create_display_list(void); // cmd 34
void geo_layout_cmd_create_shadow_texture(void); // cmd 35
void geo_layout_cmd_create_anchor(void); // cmd 36
void geo_layout_cmd_set_node_flag4(void); // cmd 37
void geo_layout_cmd_create_group(void); // cmd 38
GraphNode* process_geo_layout(MemoryBlock*, void*);

#endif // _18480_H_
