#include "fragment17.h"
#include "src/11BA0.h"
#include "src/12D80.h"
#include "src/18140.h"
#include "src/geo_layout.h"
#include "src/19840.h"
#include "src/1C720.h"
#include "src/1CF30.h"
#include "src/20330.h"
#include "src/29BA0.h"
#include "src/3FB0.h"
#include "src/4BDC0.h"
#include "src/4CBC0.h"
#include "src/6A40.h"
#include "src/6BC0.h"
#include "src/F420.h"
#include "src/controller.h"
#include "src/fragments/3/fragment3.h"
#include "src/fragments/34/fragment34.h"
#include "src/memory.h"
#include "src/stage_loader.h"
#include "src/util.h"
#include "src/2E460.h"

extern u8 D_3000180[];
extern u8 D_3000780[];
extern u8 D_3001220[];
extern u8 D_3001B80[];
extern u8 D_30024E0[];
extern u8 D_30032A0[];
extern u8 D_3004060[];
extern u8 D_3004E20[];
extern u8 D_3005780[];
extern u8 D_30060E0[];
extern u8 D_3006B80[];
extern u8 D_300C6D0[];

s32 ToggleCameraNodeOffsetFromCurrent(s32, GraphNode*);
s32 SetCameraNodeOffsetInverse(s32, GraphNode*);
s32 GraphNode_SetColor(s32, GraphNode*);

typedef struct unk_D_86B0DD58 {
    /* 0x00 */ u8 unk_00;
    /* 0x04 */ f32 unk_04;
    /* 0x08 */ f32 unk_08;
} unk_D_86B0DD58; // size = 0xC

static SpriteColorParams gUIElementColors[4] = {
    {
        0x00FF,
        0x00E1,
        0x0000,
        0x0000,
        0x0000,
        0x0000,
        0x0000,
        0x0000,
        0x0000,
        0x0000,
        0x0000,
        0x0000,
    },
    {
        0x00FF,
        0x00FF,
        0x00FF,
        0x00FF,
        0x00FF,
        0x0064,
        0x00FF,
        0x0007,
        0x0040,
        0x0040,
        0x0040,
        0x0019,
    },
    {
        0x00FF,
        0x00FF,
        0x009B,
        0x009B,
        0x009B,
        0x0000,
        0x00FF,
        0x00FF,
        0x0032,
        0x0032,
        0x0032,
        0x0032,
    },
    {
        0x00FF,
        0x00FF,
        0x00FF,
        0x00FF,
        0x00FF,
        0x0064,
        0x00FF,
        0x00FF,
        0x0080,
        0x0080,
        0x0080,
        0x0032,
    },
};
static u8 gUIElementColorFlat[] = {
    0, 0xFF, 0, 0xE1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xFF, 0, 3, 0, 0x11, 0, 0x11, 0, 0x11, 0, 7,
};

static unk_D_86B0DD58 gMonsterSpawnInfo[20] = {
    { 0xA7, 47.5f, 30.0f }, { 0xA8, 47.5f, 30.0f }, { 0xA9, 47.5f, 30.0f }, { 0xAA, 47.5f, 30.0f },
    { 0xA5, 66.5f, 85.0f }, { 0xA5, 66.5f, 85.0f }, { 0xA7, 0.0f, 0.0f },   { 0xA7, 0.0f, 0.0f },
    { 0xA7, 0.0f, 0.0f },   { 0xA7, 0.0f, 0.0f },   { 0xA7, 0.0f, 0.0f },   { 0xA7, 0.0f, 0.0f },
    { 0xA7, 0.0f, 0.0f },   { 0xA7, 0.0f, 0.0f },   { 0xA7, 0.0f, 0.0f },   { 0xA7, 0.0f, 0.0f },
    { 0xA7, 0.0f, 0.0f },   { 0xA7, 0.0f, 0.0f },   { 0xA7, 0.0f, 0.0f },   { 0xA7, 0.0f, 0.0f },
};

static u8 gMonsterModelIds[] = {
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x11, 0x01,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01,
};

static unk_D_8690A610 gBattleOverlayRect;
static GraphRootNode gMiniCameraRoot0;
static GraphRootNode gMiniCameraRoot1;
static GraphRootNode gMiniCameraRoot2;
static u32 gMiniCameraBgColor;
static Color_RGBA8_u32 gOverlayColor;
static u8 gMonsterSfxTriggered;
static s16 gCurrentMonsterModelId;
static s16 gCurrentMonsterSpawnIdx;
static s16 gMonsterLandingState;
static f32 gMonsterLandingYVel;
static void* gMonsterModelArchive;
static unk_D_86B0FA50* gUIElementName;
static unk_D_86B0FA50* gUIElementHealthBar;
static unk_D_86B0FA50* gUIElementHealthFill;
static unk_D_86B0FA50* gUIElementStatus;
static unk_D_86B0FA50* gUIElementBorder;
static s16 D_86B0FA64;
static s16 gCameraZoomPitch;
static s16 gCameraZoomYaw;
static f32 gCameraZoomFov;
static s32 gBattleSequenceFrameCount;
static s32 gBattleSequenceType;
unk_D_86B0FA78* gCameraTarget;
unk_D_86B0FA7C* gCameraState;
static u8 D_86B0FA80[0xBE0];
unk_70D3A0 gMonsterStageData;
static unk_D_70B10 gMonsterStageParams;
static unk_D_800AE540_0004* gMonsterDataPtr;
static unk_D_800AE540_1194* gMonsterContextPtr;

static u32 D_86B0DE5C[] = {
    0x0C00FFFF, 0x05000000,    0x0B00001E,  0x00000000,    0x014000F0,  0x0000000F,  0x00000000, 0x00000000,
    0x05000000, 0x0D000000,    0x05000000,  0x07000000,    &gBattleOverlayRect, 0x14000000,  0x002D0019, 0xFFFFFF28,
    0x08000000, ToggleCameraNodeOffsetFromCurrent, 0x00000000,  0x14000000,    0x002D0019,  0x80808028,  0x08000000, SetCameraNodeOffsetInverse,
    0x00000000, 0x16646464,    0x0F000002,  0x05000000,    0x1F00FFFF,  0x00000000,  0x00000000, 0x00000000,
    0x00640064, 0x00640000,    0x08000000,  GraphNode_SetColor, 0x00000000,  0x05000000,  0x07000000, &gMiniCameraRoot0,
    0x06000000, 0x06000000,    0x0F000003,  0x05000000,    0x1F00FFFF,  0x00000000,  0x00000000, 0x00000000,
    0x00640064, 0x00640000,    0x08000000,  GraphNode_SetColor, 0x00000000,  0x05000000,  0x07000000, &gMiniCameraRoot1,
    0x06000000, 0x06000000,    0x0F000002,  0x05000000,    0x1F00FFFF,  0x00000000,  0x00000000, 0x00000000,
    0x00640064, 0x00640000,    0x08000000,  GraphNode_SetColor, 0x00000000,  0x05000000,  0x07000000, &gMiniCameraRoot2,
    0x06000000, 0x06000000,    0x0F000003,  0x05000000,    0x0A000000,  &gGraphRoot0, 0x06000000, 0x0F000002,
    0x05000000, 0x0A000000,    &gGraphRoot1, 0x06000000,    0x09000000,  0x06000000,  0x06000000, 0x06000000,
    0x01000000,
};

s32 ToggleCameraNodeOffsetFromCurrent(s32 arg0, GraphNode* arg1) {
    unk_D_86002F34_alt18* ptr = (unk_D_86002F34_alt18*)arg1;
    f32 sp28;
    s16 sp26;
    s16 sp24;

    if (arg0 == 2) {
        Matrix_Decompose(&gCurrentCameraNode->unk_60.at, &gCurrentCameraNode->unk_60.eye, &sp28, &sp26, &sp24);
        ptr->unk_1C = sp26 + 0x2000;
        ptr->unk_1E = sp24 - 0x2000;
    }

    return 0;
}

s32 SetCameraNodeOffsetInverse(s32 arg0, GraphNode* arg1) {
    unk_D_86002F34_alt18* ptr = (unk_D_86002F34_alt18*)arg1;
    f32 sp28;
    s16 sp26;
    s16 sp24;

    if (arg0 == 2) {
        Matrix_Decompose(&gCurrentCameraNode->unk_60.at, &gCurrentCameraNode->unk_60.eye, &sp28, &sp26, &sp24);
        ptr->unk_1C = -0x2000 - sp26;
        ptr->unk_1E = sp24 + 0x6000;
    }

    return 0;
}

s32 GraphNode_SetColor(s32 arg0, GraphNode* arg1) {
    Fragment2_1GraphNode* ptr = (Fragment2_1GraphNode*)arg1;

    if (arg0 == 2) {
        ptr->unk_03C.rgba = gOverlayColor.rgba;
    }

    return 0;
}

void SetGlobalOverlayColor(u8 arg0, u8 arg1, u8 arg2) {
    u8 v = arg0 & arg1 & arg2;

    gOverlayColor.r = arg0;
    gOverlayColor.g = arg1;
    gOverlayColor.b = arg2;

    if (v == 0xFF) {
        if (gBattleOverlayRect.unk_00.unk_14 == 1) {
            gBattleOverlayRect.unk_00.unk_01 |= 1;
        }
    } else {
        gBattleOverlayRect.unk_00.unk_01 &= ~1;
    }
}

void LoadStageResources(void) {
    UNUSED s32 pad[2];
    u8* sp24;
    u8* temp_a1;
    u8* sp1C;

    temp_a1 = (u32)_70D3A0_ROM_START + (gStageRomOffsets[gCameraTarget->unk_174 - 1] & 0xFFFFFF);
    sp24 = (u32)_70D3A0_ROM_START +
           ((((gCameraTarget->unk_174 ^ 0) * sizeof(unk_D_70B10)) - sizeof(unk_D_70B10) + (u32)D_70B10) & 0xFFFFFF);
    sp1C = (u32)_70D3A0_ROM_START +
           (((gCameraTarget->unk_174 * sizeof(unk_70D3A0)) - sizeof(unk_70D3A0) + (u32)D_70110) & 0xFFFFFF);

    DmaCopyAsyncRange(D_86B0FA80, temp_a1, temp_a1 + 0xBC0, 0);
    DmaCopyAsyncRange(&gMonsterStageData, sp1C, sp1C + sizeof(unk_70D3A0), 0);
    DmaCopyAsyncRange(&gMonsterStageParams, sp24, sp24 + sizeof(unk_D_70B10), 0);
}

void MonsterNode_Init(void) {
    gCameraTarget->unk_174 = gMonsterDataPtr->unk_01C[gCameraTarget->unk_17C].unk_00.unk_00;
    Graph_AddToRootList0(&gCameraTarget->unk_004);
    AssetManager_LoadArchives();

    gCameraTarget->unk_000 = Model_LoadForPokemon(&gMonsterDataPtr->unk_01C[gCameraTarget->unk_17C]);
    GraphNode_InitChild(&gCameraTarget->unk_004, 0, gCameraTarget->unk_174, gCameraTarget->unk_000->unk_08->unk_00[0]);
    GraphNode_TriggerAction(&gCameraTarget->unk_004, 0);
    gCameraTarget->unk_004.modelPhase = 0;
    LoadStageResources();
    gCameraTarget->unk_004.unk_024.y += gMonsterStageData.unk_08;
    gCameraTarget->unk_170 = 0;
    SetAnimStateIndex(&gCameraTarget->unk_004, 0);
    GraphNode_TriggerSound(&gCameraTarget->unk_004, -1);
}

void MonsterNode_Reset(void) {
    GraphNode_ClearCallback(&gCameraTarget->unk_004);

    main_pool_pop_state('MONS');

    main_pool_push_state('MONS');

    MonsterNode_Init();
}

void MiniCamera_Setup(void) {
    gCameraState->unk_00->unk_24.fovy = 30.0f;
    gCameraState->unk_00->unk_24.near = 30.0f;
    gCameraState->unk_00->unk_24.far = 6400.0f;
    ComputeCameraTargetPos(gCameraTarget, &gCameraState->unk_04);
    Camera_InitFromConfig(&gScrollBarSegmentData[gCameraTarget->unk_17C], gCameraState->unk_00);
    Camera_UpdateView();
}

void MonsterNode_LoadById(void) {
    GraphNode_ClearCallback(&gCameraTarget->unk_004);

    main_pool_pop_state('MONS');

    main_pool_push_state('MONS');

    gCameraTarget->unk_174 = gMonsterSpawnInfo[gCurrentMonsterSpawnIdx].unk_00;
    Graph_AddToRootList0(&gCameraTarget->unk_004);
    AssetManager_LoadArchives();
    gCameraTarget->unk_000 = GeoLayout_LoadById(gCameraTarget->unk_174);
    GraphNode_InitChild(&gCameraTarget->unk_004, 0, gCameraTarget->unk_174, gCameraTarget->unk_000->unk_08->unk_00[0]);
    GraphNode_TriggerAction(&gCameraTarget->unk_004, 0);
    Vec3f_Set(&gCameraTarget->unk_004.unk_024, 0.0f, 300.0f, 0.0f);
}

void MiniCamera_UpdateForMonster(void) {
    gMonsterLandingState = 0;
    gMonsterLandingYVel = 0.0f;
    gCameraState->unk_00->unk_24.fovy = 40.0f;
    gCameraState->unk_00->unk_24.near = 30.0f;
    gCameraState->unk_00->unk_24.far = 6400.0f;

    Vec3f_Set(&gCameraState->unk_00->unk_60.at, gCameraTarget->unk_004.unk_024.x,
                  gMonsterSpawnInfo[gCurrentMonsterSpawnIdx].unk_04 + gCameraTarget->unk_004.unk_024.y, gCameraTarget->unk_004.unk_024.z);

    if ((gCurrentMonsterSpawnIdx == 4) || (gCurrentMonsterSpawnIdx == 5)) {
        Vec3f_Set(&gCameraState->unk_00->unk_60.eye, 0, 100.0f, 328.0f);
    } else {
        Vec3f_Set(&gCameraState->unk_00->unk_60.eye, 0, 100.0f, 250.0f);
    }
}

s32 MonsterNode_UpdateYPos(Fragment2_1GraphNode* arg0, s16 arg1, s16 arg2) {
    if (arg1 > 0) {
        arg0->unk_01E.y -= arg1;
        if ((arg0->unk_01E.y < arg2) && ((arg2 - arg1) < arg0->unk_01E.y)) {
            return 1;
        }
    } else {
        arg0->unk_01E.y -= arg1;
        if ((arg2 < arg0->unk_01E.y) && (arg0->unk_01E.y < (arg2 - arg1))) {
            return 1;
        }
    }
    return 0;
}

s32 MonsterNode_EaseYPos(Fragment2_1GraphNode* arg0, s16 arg1, s16 arg2) {
    if ((((arg0->unk_01E.y - arg2) / 182) < 0x3D) && (((arg0->unk_01E.y - arg2) / 182) >= 0)) {
        arg1 = (arg0->unk_01E.y - arg2) / 9;
    }
    arg0->unk_01E.y -= arg1;

    if (arg1 > 0) {
        if ((arg2 >= arg0->unk_01E.y) && (arg0->unk_01E.y >= (arg2 - arg1))) {
            arg0->unk_01E.y = arg2;
            return 1;
        }
    } else if ((arg0->unk_01E.y >= arg2) && ((arg2 - arg1) >= arg0->unk_01E.y)) {
        arg0->unk_01E.y = arg2;
        return 1;
    }
    return 0;
}

s32 MonsterLandingSequence(void) {
    if (gMonsterLandingState < 3) {
        if ((gMonsterLandingState <= 0) && (MonsterNode_UpdateYPos(&gCameraTarget->unk_004, 0x71C, 0) != 0)) {
            gMonsterLandingState++;
        }

        if ((gMonsterLandingState > 0) && (MonsterNode_EaseYPos(&gCameraTarget->unk_004, 0x71C, 0) != 0)) {
            gMonsterLandingState++;
        }
    }

    Math_ApproachFloat(&gMonsterLandingYVel, 0.1f, 0.02f);
    Math_ApproachFloat(&gCameraTarget->unk_004.unk_024.y, 0.0f, gMonsterLandingYVel);

    if (gCameraTarget->unk_004.unk_024.y <= 0.25f) {
        gCameraTarget->unk_004.unk_024.y = 0.0f;
    }

    Vec3f_Set(&gCameraState->unk_00->unk_60.at, gCameraTarget->unk_004.unk_024.x,
                  gMonsterSpawnInfo[gCurrentMonsterSpawnIdx].unk_04 + gCameraTarget->unk_004.unk_024.y, gCameraTarget->unk_004.unk_024.z);

    if (gCameraTarget->unk_004.unk_024.y <= 0.5f) {
        return 1;
    }
    return 0;
}

void MonsterNode_SpawnParticles(void) {
    Vec3f sp44;

    if (gMonsterSfxTriggered == 0) {
        gMonsterSfxTriggered = 1;
        PlayUISfx(0x0110000F, 0, 0);
    }

    if (gCameraTarget->unk_178 & 1) {
        Vec3f_Set(&sp44, gCameraTarget->unk_004.unk_024.x,
                      gMonsterSpawnInfo[gCurrentMonsterSpawnIdx].unk_08 + (Math_RandomU16Range(0x28) - 0x14), gCameraTarget->unk_004.unk_024.z);
        Particle_CreateMultiple(1.0f, sp44, gCameraTarget->unk_004.unk_01E, MiniFx_UpdatePalette17DelayedRevealFallParticle, &D_87903E40, 1);

        if ((gCameraTarget->unk_178 >= 0xA) && (gCameraTarget->unk_178 & 1)) {
            Vec3f_Set(&sp44, gCameraTarget->unk_004.unk_024.x,
                          gMonsterSpawnInfo[gCurrentMonsterSpawnIdx].unk_08 + (Math_RandomU16Range(0x28) - 0x14), gCameraTarget->unk_004.unk_024.z);
            Particle_CreateMultiple(1.0f, sp44, gCameraTarget->unk_004.unk_01E, MiniFx_UpdatePalette17DelayedRevealFallParticle, &D_87903E40, 1);
        }

        if ((gCameraTarget->unk_178 >= 0x14) && (gCameraTarget->unk_178 & 1)) {
            Vec3f_Set(&sp44, gCameraTarget->unk_004.unk_024.x,
                          gMonsterSpawnInfo[gCurrentMonsterSpawnIdx].unk_08 + (Math_RandomU16Range(0x28) - 0x14), gCameraTarget->unk_004.unk_024.z);
            Particle_CreateMultiple(1.0f, sp44, gCameraTarget->unk_004.unk_01E, MiniFx_UpdatePalette17DelayedRevealFallParticle, &D_87903E40, 1);
        }

        if ((gCameraTarget->unk_178 >= 0x1E) && (gCameraTarget->unk_178 & 1)) {
            Vec3f_Set(&sp44, gCameraTarget->unk_004.unk_024.x,
                          gMonsterSpawnInfo[gCurrentMonsterSpawnIdx].unk_08 + (Math_RandomU16Range(0x28) - 0x14), gCameraTarget->unk_004.unk_024.z);
            Particle_CreateMultiple(1.0f, sp44, gCameraTarget->unk_004.unk_01E, MiniFx_UpdatePalette17DelayedRevealFallParticle, &D_87903E40, 1);
        }
    }
}

void UpdateFadeColorFromHealth(void) {
    gCameraTarget->unk_180 = Math_ApproachF32(gCameraTarget->unk_180, 100.0f, 2.0f, 2.0f);
    SetGlobalOverlayColor(gCameraTarget->unk_180, gCameraTarget->unk_180, gCameraTarget->unk_180);
}

void MonsterNode_UpdateIdleAnim(void) {
    if (((gCameraTarget->unk_178 % 50) == 0) && (gCameraTarget->unk_170 == 0) && (D_86B0FA80[0xA51] != 0xFF)) {
        InitAnimState(&gCameraTarget->unk_004);
        GraphNode_TriggerSound(&gCameraTarget->unk_004, D_86B0FA80[0xA51]);
        gCameraTarget->unk_170 = 1;
    } else if ((gCameraTarget->unk_170 == 1) && (IsAnimStateSecondLast(&gCameraTarget->unk_004) == 1)) {
        gCameraTarget->unk_170 = 0;
        SetAnimStateIndex(&gCameraTarget->unk_004, 0);
        GraphNode_TriggerSound(&gCameraTarget->unk_004, -1);
    }
}

void UIElement_Init(unk_D_86B0FA50* arg0, u8* arg1, f32 arg2, s16 arg3, s16 arg4, s16 arg5) {
    arg0->unk_80 = arg1;
    arg0->unk_98 = arg2;
    arg0->unk_9C = arg3;
    arg0->unk_9E = arg4;
    arg0->unk_A0 = arg5;

    arg0->unk_88 = 0;
    arg0->unk_8C = 0;
    arg0->unk_84 = 0;
    arg0->unk_A4 = 0;
    arg0->unk_AC = 0.0f;

    arg0->unk_B0.unk_00 = gUIElementColors->unk_00;
    arg0->unk_B0.unk_02 = gUIElementColors->unk_02;
    arg0->unk_B0.unk_04 = gUIElementColors->unk_04;
    arg0->unk_B0.unk_06 = gUIElementColors->unk_06;
    arg0->unk_B0.unk_08 = gUIElementColors->unk_08;
    arg0->unk_B0.unk_0A = gUIElementColors->unk_0A;
}

void BattleUI_InitElements(void) {
    if (gBattleContext.unk_11F2 == 1) {
        UIElement_Init(gUIElementBorder, &D_300C6D0, -250.0f, 0xC8, 0x18, 0x18);
    }

    UIElement_Init(gUIElementHealthBar, &D_3000180, -250.0f, 0xC8, 0x40, 0x18);

    if (gBattleContext.unk_0002 == 0) {
        UIElement_Init(gUIElementStatus, &D_30060E0, -170.0f, 0x3C, 0x88, 0x14);
    } else if (gBattleContext.unk_0002 == 1) {
        UIElement_Init(gUIElementStatus, &D_3006B80, -170.0f, 0x3C, 0x78, 0x14);
    } else if (gBattleContext.unk_0002 == 2) {
        UIElement_Init(gUIElementStatus, &D_3004E20, -170.0f, 0x3C, 0x78, 0x14);
    } else if (gBattleContext.unk_0002 == 3) {
        UIElement_Init(gUIElementStatus, &D_3005780, -170.0f, 0x3C, 0x78, 0x14);
    }

    switch (gBattleContext.unk_0001) {
        case 1:
            UIElement_Init(gUIElementHealthFill, &D_30024E0, -100.0f, 0x1E, 0xB0, 0x14);
            break;

        case 2:
            UIElement_Init(gUIElementHealthFill, &D_30032A0, -100.0f, 0x1E, 0xB0, 0x14);
            break;

        case 3:
            UIElement_Init(gUIElementHealthFill, &D_3004060, -100.0f, 0x1E, 0xB0, 0x14);
            break;

        case 4:
            UIElement_Init(gUIElementHealthFill, &D_3000780, -100.0f, 0x1E, 0x88, 0x14);
            break;

        case 5:
            UIElement_Init(gUIElementHealthFill, &D_3001220, -100.0f, 0x1E, 0x78, 0x14);
            break;

        case 6:
            UIElement_Init(gUIElementHealthFill, &D_3001B80, -100.0f, 0x1E, 0x78, 0x14);
            break;

        default:
            UIElement_Init(gUIElementHealthFill, &D_30024E0, -100.0f, 0x1E, 0xB0, 0x14);
            break;
    }
}

void MonsterNode_SetupDefault(void) {
    gCameraTarget->unk_16C = 0;
    gCameraTarget->unk_17C = 0;
    gCameraTarget->unk_174 = 0;

    main_pool_push_state('MONS');

    MonsterNode_Init();
}

void MiniCamera_InitDefault(void) {
    gCameraState->unk_00 = gMiniCameraStruct->unk_00.unk_0C;
    gMiniCameraPtr = gCameraState->unk_00;
    MiniCamera_Setup();
}

void MonsterNode_SetupCustom(void) {
    gCameraTarget->unk_16C = 6;
    gCameraTarget->unk_17C = 6;
    gCameraTarget->unk_174 = 0;

    main_pool_push_state('MONS');

    MonsterNode_LoadById();
}

void MiniCamera_InitMonster(void) {
    gCameraState->unk_00 = gMiniCameraStruct->unk_00.unk_0C;
    gMiniCameraPtr = gCameraState->unk_00;
    MiniCamera_UpdateForMonster();
}

void BattleUI_SetStateActive(void) {
    gUIElementName->unk_90 = 3;
}

void BattleContext_SyncMonsterData(void) {
    if (gBattleContext.unk_1194[0].unk_1C == 1) {
        gMonsterDataPtr = gBattleContext.unk_1194[0].unk_08[0];
        gMonsterContextPtr = &gBattleContext.unk_1194[0];
    } else {
        gMonsterDataPtr = gBattleContext.unk_1194[1].unk_08[0];
        gMonsterContextPtr = &gBattleContext.unk_1194[1];
    }
}

void BattleInput_Update(void) {
    Cont_StartReadInputs();
    Cont_ReadInputs();
    MenuInput_Init();
}

s32 BattleSequence_Update(void) {
    switch (gCameraTarget->unk_16C) {
        case 0:
            MiniCamera_Setup();
            Intro_UpdateCameraKeyframe(gCameraState->unk_00);
            gCameraTarget->unk_170 = 0;
            gCameraTarget->unk_16C += 1;
            break;

        case 1:
            MonsterNode_UpdateIdleAnim();
            if (gCameraTarget->unk_178++ == 0x19) {
                gUIElementName->unk_90 = 0;
            }

            if (Intro_UpdateCameraKeyframe(gCameraState->unk_00) != 0) {
                if ((gBattleContext.unk_0001 == 7) && (gCameraTarget->unk_17C == 5)) {
                    return 1;
                }
                Scroll_Init(3, 0x1E);
                gCameraTarget->unk_16C += 1;
            }
            break;

        case 2:
            Scroll_Update();
            if (Scroll_GetMode() == 1) {
                gCameraTarget->unk_17C++;
                if (gCameraTarget->unk_17C == 6) {
                    gCameraTarget->unk_170 = 0;
                    MonsterNode_LoadById();
                    MiniCamera_UpdateForMonster();
                    gUIElementName->unk_90 = 3;
                    gCameraTarget->unk_178 = 0;
                    Scroll_Init(2, 0x1E);
                    gCameraTarget->unk_16C = 6;
                } else {
                    gCameraTarget->unk_170 = 0;
                    MonsterNode_Reset();
                    MiniCamera_Setup();
                    gUIElementName->unk_90 = 3;
                    gCameraTarget->unk_178 = 0;
                    Scroll_Init(2, 0x1E);
                    gCameraTarget->unk_16C++;
                }
            }
            break;

        case 3:
            Scroll_Update();
            if (gCameraTarget->unk_178++ > 0) {
                Intro_UpdateCameraKeyframe(gCameraState->unk_00);
            }

            if (Scroll_GetMode() == 0) {
                gCameraTarget->unk_178 = 0;
                gCameraTarget->unk_16C = 1;
            }
            break;

        case 6:
            gCameraTarget->unk_180 = 0xFF;
            Scroll_Update();
            MonsterLandingSequence();
            if (Scroll_GetMode() == 0) {
                gCameraTarget->unk_16C++;
            }
            break;

        case 7:
            if (MonsterLandingSequence() != 0) {
                gCameraTarget->unk_178 = 0;
                gUIElementName->unk_90 = 0;
                PlayUISfx(0x01100002, 0, 0);
                gMonsterSfxTriggered = 0;
                gCameraTarget->unk_16C++;
            }
            break;

        case 8:
            if (gUIElementHealthFill->unk_84 != 0) {
                MonsterNode_SpawnParticles();
            }
            if (gCameraTarget->unk_178++ >= 0x41) {
                D_86B0FA64 = 0;
                Matrix_Decompose(&gMiniCameraPtr->unk_60.at, &gMiniCameraPtr->unk_60.eye, &gCameraZoomFov, &gCameraZoomPitch, &gCameraZoomYaw);
                gCameraTarget->unk_16C++;
            }
            break;

        case 9:
            UpdateFadeColorFromHealth();

            if (gUIElementHealthFill->unk_84 != 0) {
                MonsterNode_SpawnParticles();
            }

            if (gPlayer1Controller->buttonDown & 0xC000) {
                return 1;
            }

            if (gCameraTarget->unk_178++ >= 0x3E9) {
                gCameraTarget->unk_178 = 0x64;
            }

            D_86B0FA64 = Math_ApproachS32(D_86B0FA64, 0x3C, 1, 1);
            gCameraZoomYaw += D_86B0FA64;
            Camera_SetViewParameters(&gMiniCameraPtr->unk_60.at, &gMiniCameraPtr->unk_60.eye, gCameraZoomFov, gCameraZoomPitch, gCameraZoomYaw);
            break;
    }

    if ((gBattleSequenceType == 2) && (gBattleSequenceFrameCount == 0x12C)) {
        ResultScreen_SetAnimation(0x5B);
    }
    return 0;
}

s32 UIElement_UpdatePos(unk_D_86B0FA50* arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5) {
    f32 temp_fa1;
    f32 sp20;
    f32 temp_fv0;
    f32 temp_fv0_2;
    f32 temp_fv0_4;
    f32* new_var;

    sp20 = arg0->unk_A4;

    temp_fv0 = Math_ApproachF32(sp20, 0.0f, 0.0f, 0.0f);
    arg0->unk_A4 = temp_fv0;
    if (temp_fv0 >= 0.0f) {
        temp_fv0 = 0;
        if ((arg0 && arg0) && arg0) {}
    }
    temp_fv0_2 = COSS(0) * temp_fv0;
    temp_fa1 = -arg3;

    new_var = &arg0->unk_AC;

    temp_fv0_4 = (-temp_fa1) - (arg2 * ((sp20 * arg0->unk_AC) + temp_fv0_2));
    arg0->unk_AC = (temp_fv0_4 * arg5) + ((*new_var) + temp_fv0_2);

    if (arg0->unk_AC >= 28.0) {
        arg0->unk_AC = 28.0f;
    }

    arg0->unk_98 += arg0->unk_AC;
    if (temp_fa1 >= 0) {
        if ((arg0->unk_98 < arg4) && (arg0->unk_98 >= 0.0f)) {
            arg0->unk_98 = arg4;
            arg0->unk_AC *= -arg1;
        }
    } else if ((arg4 < arg0->unk_98) && (arg0->unk_98 >= 0.0f)) {
        arg0->unk_98 = arg4;
        arg0->unk_AC *= -arg1;
        if (arg0->unk_A8 == arg0->unk_AC) {
            return 1;
        }
        arg0->unk_A8 = arg0->unk_AC;
    }

    return 0;
}

void BattleUI_Render(void) {
    if (gCameraTarget->unk_17C == 6) {
        switch (gUIElementName->unk_90) {
            case 3:
                break;

            case 0:
                BattleUI_InitElements();
                gUIElementName->unk_90++;
                break;

            case 1:
                UIElement_UpdatePos(gUIElementHealthBar, 0.25f, 0.0f, 3.0f, 0xA3 - (gUIElementHealthBar->unk_9E / 2), 1.7f);
                Gfx_DrawSpriteWithColors(gUIElementHealthBar->unk_80, gUIElementHealthBar->unk_98, gUIElementHealthBar->unk_9C, gUIElementHealthBar->unk_9E,
                              gUIElementHealthBar->unk_A0, &gUIElementHealthBar->unk_B0);
                gUIElementHealthFill->unk_84 =
                    UIElement_UpdatePos(gUIElementHealthFill, 0.25f, 0.0f, 3.0f, 0xA3 - (gUIElementHealthFill->unk_9E / 2), 1.7f);
                Gfx_DrawSpriteWithColors(gUIElementHealthFill->unk_80, gUIElementHealthFill->unk_98, gUIElementHealthFill->unk_9C, gUIElementHealthFill->unk_9E,
                              gUIElementHealthFill->unk_A0, &gUIElementHealthBar->unk_B0);

                if (gBattleContext.unk_11F2 == 1) {
                    Gfx_DrawBorderSprite(gUIElementBorder->unk_80, (s16)gUIElementHealthFill->unk_98 + gUIElementHealthFill->unk_9E,
                                  gUIElementHealthFill->unk_9C - 2, gUIElementBorder->unk_9E, gUIElementBorder->unk_A0);
                }

                if ((gCurrentMonsterSpawnIdx != 4) && (gCurrentMonsterSpawnIdx != 5)) {
                    UIElement_UpdatePos(gUIElementStatus, 0.25f, 0.0f, 3.0f, 0xA3 - (gUIElementStatus->unk_9E / 2), 1.7f);
                    Gfx_DrawSpriteWithColors(gUIElementStatus->unk_80, gUIElementStatus->unk_98, gUIElementStatus->unk_9C, gUIElementStatus->unk_9E,
                                  gUIElementStatus->unk_A0, &gUIElementHealthBar->unk_B0);
                }

                if (gUIElementHealthFill->unk_84 != 0) {
                    gUIElementHealthBar->unk_B0.unk_00 = Math_ApproachS32(
                        gUIElementHealthBar->unk_B0.unk_00, gUIElementColors[gUIElementHealthBar->unk_88 + 1].unk_00,
                        gUIElementColors[gUIElementHealthBar->unk_88 + 1].unk_0C, gUIElementColors[gUIElementHealthBar->unk_88 + 1].unk_0C);
                    gUIElementHealthBar->unk_B0.unk_02 = Math_ApproachS32(
                        gUIElementHealthBar->unk_B0.unk_02, gUIElementColors[gUIElementHealthBar->unk_88 + 1].unk_02,
                        gUIElementColors[gUIElementHealthBar->unk_88 + 1].unk_0E, gUIElementColors[gUIElementHealthBar->unk_88 + 1].unk_0E);
                    gUIElementHealthBar->unk_B0.unk_04 = Math_ApproachS32(
                        gUIElementHealthBar->unk_B0.unk_04, gUIElementColors[gUIElementHealthBar->unk_88 + 1].unk_04,
                        gUIElementColors[gUIElementHealthBar->unk_88 + 1].unk_10, gUIElementColors[gUIElementHealthBar->unk_88 + 1].unk_10);
                    gUIElementHealthBar->unk_B0.unk_06 = Math_ApproachS32(
                        gUIElementHealthBar->unk_B0.unk_06, gUIElementColors[gUIElementHealthBar->unk_88 + 1].unk_06,
                        gUIElementColors[gUIElementHealthBar->unk_88 + 1].unk_12, gUIElementColors[gUIElementHealthBar->unk_88 + 1].unk_12);
                    gUIElementHealthBar->unk_B0.unk_08 = Math_ApproachS32(
                        gUIElementHealthBar->unk_B0.unk_08, gUIElementColors[gUIElementHealthBar->unk_88 + 1].unk_08,
                        gUIElementColors[gUIElementHealthBar->unk_88 + 1].unk_14, gUIElementColors[gUIElementHealthBar->unk_88 + 1].unk_14);
                    gUIElementHealthBar->unk_B0.unk_0A = Math_ApproachS32(
                        gUIElementHealthBar->unk_B0.unk_0A, gUIElementColors[gUIElementHealthBar->unk_88 + 1].unk_0A,
                        gUIElementColors[gUIElementHealthBar->unk_88 + 1].unk_16, gUIElementColors[gUIElementHealthBar->unk_88 + 1].unk_16);
                    if ((gUIElementHealthBar->unk_B0.unk_00 == gUIElementColors[gUIElementHealthBar->unk_88 + 1].unk_00) &&
                        (gUIElementHealthBar->unk_B0.unk_02 == gUIElementColors[gUIElementHealthBar->unk_88 + 1].unk_02) &&
                        (gUIElementHealthBar->unk_B0.unk_04 == gUIElementColors[gUIElementHealthBar->unk_88 + 1].unk_04) &&
                        (gUIElementHealthBar->unk_B0.unk_06 == gUIElementColors[gUIElementHealthBar->unk_88 + 1].unk_06) &&
                        (gUIElementHealthBar->unk_B0.unk_08 == gUIElementColors[gUIElementHealthBar->unk_88 + 1].unk_08) &&
                        (gUIElementHealthBar->unk_B0.unk_0A == gUIElementColors[gUIElementHealthBar->unk_88 + 1].unk_0A)) {

                        gUIElementHealthBar->unk_88++;
                        if (gUIElementHealthBar->unk_88 == 4) {
                            gUIElementName->unk_90++;
                        }
                    }
                }
                break;

            case 2:
                Gfx_DrawSpriteWithColors(gUIElementHealthBar->unk_80, gUIElementHealthBar->unk_98, gUIElementHealthBar->unk_9C, gUIElementHealthBar->unk_9E,
                              gUIElementHealthBar->unk_A0, gUIElementColorFlat);
                Gfx_DrawSpriteWithColors(gUIElementHealthFill->unk_80, gUIElementHealthFill->unk_98, gUIElementHealthFill->unk_9C, gUIElementHealthFill->unk_9E,
                              gUIElementHealthFill->unk_A0, gUIElementColorFlat);

                if (gBattleContext.unk_11F2 == 1) {
                    Gfx_DrawBorderSprite(gUIElementBorder->unk_80, (s16)gUIElementHealthFill->unk_98 + gUIElementHealthFill->unk_9E,
                                  gUIElementHealthFill->unk_9C - 2, gUIElementBorder->unk_9E, gUIElementBorder->unk_A0);
                }

                if ((gCurrentMonsterSpawnIdx != 4) && (gCurrentMonsterSpawnIdx != 5)) {
                    Gfx_DrawSpriteWithColors(gUIElementStatus->unk_80, gUIElementStatus->unk_98, gUIElementStatus->unk_9C, gUIElementStatus->unk_9E,
                                  gUIElementStatus->unk_A0, gUIElementColorFlat);
                }
                break;
        }
    } else {
        switch (gUIElementName->unk_90) {
            case 3:
                break;

            case 0:
                gUIElementName->unk_98 = -80.0f;
                gUIElementName->unk_9C = 0xB4;
                gUIElementName->unk_A4 = 0.0f;
                gUIElementName->unk_AC = 0.0f;
                sprintf(gUIElementName->unk00, "%s", gMonsterDataPtr->unk_01C[gCameraTarget->unk_17C].unk_30);
                gUIElementName->unk_90++;
                break;

            case 1:
                Text_ResetState();
                Text_BeginRender();
                Text_SetFont(0x10, 0);
                Text_SetPrimColor(0, 0x82, 0xFF, 0xFF);
                Text_SetEnvColor(0xC8, 0xFF, 0xFF, 0xFF);
                UIElement_UpdatePos(gUIElementName, 0.35f, 0.0f, 4.0f, 160.0f, 1.4f);
                Text_Print((s32)gUIElementName->unk_98 - (MeasureTextWidth(0x10, 0, gUIElementName->unk00) / 2),
                              gUIElementName->unk_9C, gUIElementName->unk00);
                Text_EndRender();
                Text_SetupDL();
                break;
        }
    }

    Scroll_RenderIfActive();
}

void BattleScene_Render(void) {
    Stage_BeginDisplayList();

    if ((gMiniCameraBgColor == -1) || (gMiniCameraBgColor == 0)) {
        Gfx_FillScreen(&gDisplayListHead, 1);
    } else if (gMiniCameraBgColor < 0x10000) {
        Gfx_FillScreen(&gDisplayListHead, gMiniCameraBgColor);
    } else {
        Gfx_FillScreen(&gDisplayListHead, 0xA6BF);
    }

    Gfx_FinishFrame();
    Graph_SetTextureState(&gMiniCameraStruct->unk_00);
    BattleUI_Render();
    ParticleRender_SetupMiniCamera();
    Stage_Advance();
}

void BattleScene_RenderBlank(void) {
    Stage_BeginDisplayList();
    Gfx_FillScreen(&gDisplayListHead, 1);
    Gfx_FinishFrame();
    Graph_SetTextureState(&gMiniCameraStruct->unk_00);
    Text_DrawWindowRect(0, 0, 0x140, 0xF0, 0, 0, 0, 0xFF);
    Stage_Advance();
}

void BattleSequence_IntroFade(void) {
    s32 i;

    for (i = 0; i < 18; i++) {
        BattleInput_Update();

        if (i < 3) {
            Stage_SetFillColor(1);
            Stage_FadeIn(0x10);
            BattleScene_RenderBlank();
        }
    }

    if (gBattleSequenceType == 2) {
        ResultScreen_SetAnimation(0x44);
    } else {
        ResultScreen_SetAnimation(8);
    }
}

void BattleSequence_MainLoop(void) {
    s32 var_s0 = 1;
    void (*temp_s2)(void) = (void*)Util_ConvertAddrToVirtAddr(Timer_Tick);

    gBattleSequenceFrameCount = 0;
    while (var_s0 != 0) {
        gBattleSequenceFrameCount++;

        BattleInput_Update();
        ParticleSystem_UpdateAndRender();

        if (BattleSequence_Update() != 0) {
            var_s0 = 0;
        }

        temp_s2();
        BattleScene_Render();
    }
}

void BattleSequence_Outro(void) {
    s32 i;
    s32 var_s1;
    void (*temp_s2)(void) = Util_ConvertAddrToVirtAddr(Timer_Tick);

    if (gBattleContext.unk_0001 == 7) {
        for (i = 0; i < 100; i++) {
            BattleInput_Update();
            ParticleSystem_UpdateAndRender();

            temp_s2();

            BattleScene_Render();
        }
    }

    if (gBattleContext.unk_0001 == 7) {
        var_s1 = 0x64;
    } else {
        var_s1 = 0xA;
    }

    Stage_FadeOut(var_s1);
    Stage_SetFadeColor(var_s1 - 2);

    for (i = 0; i < var_s1; i++) {
        if (gBattleContext.unk_0001 == 7) {
            BattleInput_Update();
            ParticleSystem_UpdateAndRender();
            temp_s2();
            BattleScene_Render();
        } else {
            BattleInput_Update();
            ParticleSystem_UpdateAndRender();
            BattleSequence_Update();
            temp_s2();
            BattleScene_Render();
        }
    }

    if (gBattleContext.unk_0001 == 7) {
        for (i = 0; i < 30; i++) {
            BattleInput_Update();
            ParticleSystem_UpdateAndRender();

            temp_s2();

            BattleScene_Render();
        }
    }
}

void BattleSequence_Init(void) {
    MemoryBlock* sp34;
    UNUSED s32 pad;
    FragmentEntry sp2C;
    void* temp_v0_3;
    unk_D_8690A610_018* temp_v0_6;

    gCurrentMonsterModelId = gMonsterModelIds[gBattleContext.unk_0001];
    if (gBattleContext.unk_0001 == 7) {
        gCurrentMonsterModelId += gBattleContext.unk_0002;
    }

    switch (gBattleContext.unk_0001) {
        case 1:
            gCurrentMonsterSpawnIdx = 4;
            break;

        case 2:
            gCurrentMonsterSpawnIdx = 4;
            break;

        case 3:
            gCurrentMonsterSpawnIdx = gBattleContext.unk_0002;
            break;

        case 4:
            gCurrentMonsterSpawnIdx = 5;
            break;

        case 5:
            gCurrentMonsterSpawnIdx = 5;
            break;

        case 6:
            gCurrentMonsterSpawnIdx = gBattleContext.unk_0002;
            break;

        default:
            gCurrentMonsterSpawnIdx = 0;
            break;
    }

    sp2C = BinArchive_GetFile(Asset_Load2(stadium_models_ROM_START, _5C7A70_ROM_START, 1, 1), gCurrentMonsterModelId);

    gMonsterModelArchive = sp2C(2, 0);
    ColorRectNode_Create(0, &gBattleOverlayRect, 0x3C0, 0x3E8, 0xFF, 0xFF, 0xFF, 0xFF);
    GraphNode_AllocInit(NULL, &gMiniCameraRoot0);
    GraphNode_AllocInit(NULL, &gMiniCameraRoot1);
    GraphNode_AllocInit(NULL, &gMiniCameraRoot2);
    sp34 = state_pool_try_init(main_pool_get_available(), 0);
    gMiniCameraStruct = process_geo_layout(sp34, D_86B0DE5C);

    temp_v0_3 = sp2C(0, 0);
    if (temp_v0_3 != NULL) {
        GraphNode_AddChild(&gMiniCameraRoot0, process_geo_layout(sp34, temp_v0_3));
    }

    temp_v0_3 = sp2C(1, 0);
    if (temp_v0_3 != NULL) {
        GraphNode_AddChild(&gMiniCameraRoot1, process_geo_layout(sp34, temp_v0_3));
    }

    temp_v0_3 = sp2C(3, 0);
    if (temp_v0_3 != NULL) {
        GraphNode_AddChild(&gMiniCameraRoot2, process_geo_layout(sp34, temp_v0_3));
    }

    gMiniCameraBgColor = sp2C(2, 0);
    mem_pool_resize_block(sp34);

    temp_v0_6 = sp2C(4, 0);
    if (temp_v0_6 == NULL) {
        gBattleOverlayRect.unk_00.unk_14 = 0;
        gBattleOverlayRect.unk_00.unk_01 &= ~1;
    } else {
        gBattleOverlayRect.unk_18.unk_00 = temp_v0_6->unk_00;
        gBattleOverlayRect.unk_18.unk_02 = temp_v0_6->unk_02;
        gBattleOverlayRect.unk_18.unk_04.rgba = temp_v0_6->unk_04.rgba;
        gBattleOverlayRect.unk_00.unk_14 = 1;
    }

    Graph_InitRoots();
    SetGlobalOverlayColor(0xFF, 0xFF, 0xFF);
    ParticleSystem_Init();

    gCameraTarget = main_pool_alloc(sizeof(unk_D_86B0FA78), 0);
    bzero(gCameraTarget, sizeof(unk_D_86B0FA78));

    gCameraState = main_pool_alloc(sizeof(unk_D_86B0FA7C), 0);
    bzero(gCameraState, sizeof(unk_D_86B0FA7C));

    gUIElementName = main_pool_alloc(sizeof(unk_D_86B0FA50), 0);
    bzero(gUIElementName, sizeof(unk_D_86B0FA50));

    gUIElementHealthBar = main_pool_alloc(sizeof(unk_D_86B0FA50), 0);
    bzero(gUIElementHealthBar, sizeof(unk_D_86B0FA50));

    gUIElementHealthFill = main_pool_alloc(sizeof(unk_D_86B0FA50), 0);
    bzero(gUIElementHealthFill, sizeof(unk_D_86B0FA50));

    gUIElementStatus = main_pool_alloc(sizeof(unk_D_86B0FA50), 0);
    bzero(gUIElementStatus, sizeof(unk_D_86B0FA50));

    gUIElementBorder = main_pool_alloc(sizeof(unk_D_86B0FA50), 0);
    bzero(gUIElementBorder, sizeof(unk_D_86B0FA50));

    BattleContext_SyncMonsterData();

    switch (gBattleContext.unk_0001) {
        case 1:
        case 2:
        case 4:
        case 5:
        case 7:
            MonsterNode_SetupDefault();
            MiniCamera_InitDefault();
            BattleUI_SetStateActive();
            gBattleSequenceType = 0;
            break;

        default:
            if (gBattleContext.unk_0002 == 3) {
                gBattleSequenceType = 1;
                MonsterNode_SetupDefault();
                MiniCamera_InitDefault();
                BattleUI_SetStateActive();
            } else {
                gBattleSequenceType = 2;
                MonsterNode_SetupCustom();
                MiniCamera_InitMonster();
                BattleUI_SetStateActive();
            }
            break;
    }
}

s32 BattleState_Handle17(void) {
    Stage* sp24;

    main_pool_push_state('DEMO');

    Gfx_InitBuffers(0x10000, 0);
    sp24 = Stage_Create(0, 1, 3, 1, 2, 1);
    Text_Init(0x10, 0);

    ASSET_LOAD(D_1000000, common_menu1_ui, 0);
    ASSET_LOAD(D_3000000, cup_clear_ui, 0);

    FRAGMENT_LOAD(fragment31);

    BattleSequence_Init();
    Stage_Set(sp24);
    BattleSequence_IntroFade();
    BattleSequence_MainLoop();
    BattleSequence_Outro();
    Stage_Destroy();
    FontManager_Free();
    Gfx_FreeBuffers();

    main_pool_pop_state('DEMO');

    return 0;
}
