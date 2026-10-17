#include "fragment13.h"
#include "src/12D80.h"
#include "src/17300.h"
#include "src/18140.h"
#include "src/geo_layout.h"
#include "src/19840.h"
#include "src/1C720.h"
#include "src/1CF30.h"
#include "src/20330.h"
#include "src/20470.h"
#include "src/3FB0.h"
#include "src/6A40.h"
#include "src/6BC0.h"
#include "src/F420.h"
#include "src/controller.h"
#include "src/memory.h"
#include "src/stage_loader.h"

static u32 gMiniGameGeoLayout[] = {
    0x0C00FFFF, 0x05000000, 0x0B00001E, 0x00000000, 0x014000F0, 0x0000000F, 0x00000000, 0x00000000,
    0x05000000, 0x0D000000, 0x05000000, 0x0F000002, 0x05000000, 0x1F00FFFF, 0x00000000, 0x00000000,
    0x00000000, 0x00640064, 0x00640000, 0x05000000, 0x00000000, 0x8D000020, 0x06000000, 0x06000000,
    0x14000000, 0x002B0012, 0xFFFFFF32, 0x16FFFFFF, 0x0F000003, 0x05000000, 0x0A000000, 0x800AC840,
    0x06000000, 0x06000000, 0x06000000, 0x06000000, 0x01000000,
};

static unk_D_86002F30* D_86700930;
static GraphNode* gMiniGameRootNode;
static unk_D_86002F34_00C* gMiniGameCameraNode;
static unk_D_86002F58_004_000 D_86700940;

static s16 gMiniGameCamX;
static s16 gMiniGameCamY;
static s16 gMiniGameCamDist;

void MiniGame_PollController(void) {
    Cont_StartReadInputs();
    Cont_ReadInputs();
    MenuInput_Init();
}

void MiniGame_InitCamera(void) {
    gMiniGameCameraNode = gMiniGameRootNode->unk_0C;
    gMiniGameCamX = 0x100;
    gMiniGameCamY = 0;
    gMiniGameCamDist = 0x78;

    gMiniGameCameraNode->unk_24.near = 50.0f;
    gMiniGameCameraNode->unk_24.far = 6400.0f;
    Camera_SetViewParameters(&gMiniGameCameraNode->unk_60.at, &gMiniGameCameraNode->unk_60.eye, gMiniGameCamDist, gMiniGameCamX, gMiniGameCamY);
}

void MiniGame_HandleCameraInput(void) {
    if (gPlayer1Controller->buttonDown & 0x800) {
        gMiniGameCamX += 256;
    }

    if (gPlayer1Controller->buttonDown & 0x400) {
        gMiniGameCamX -= 256;
    }

    if (gPlayer1Controller->buttonDown & 0x200) {
        gMiniGameCamY += 256;
    }

    if (gPlayer1Controller->buttonDown & 0x100) {
        gMiniGameCamY -= 256;
    }

    if (gPlayer1Controller->buttonDown & 8) {
        gMiniGameCamDist -= 10;
    }

    if (gPlayer1Controller->buttonDown & 4) {
        gMiniGameCamDist += 10;
    }

    if (gMiniGameCamX > 16128) {
        gMiniGameCamX = 16128;
    }

    if (gMiniGameCamX < 0) {
        gMiniGameCamX = 0;
    }

    if (gMiniGameCamDist < 50) {
        gMiniGameCamDist = 50;
    }

    Camera_SetViewParameters(&gMiniGameCameraNode->unk_60.at, &gMiniGameCameraNode->unk_60.eye, gMiniGameCamDist, gMiniGameCamX, gMiniGameCamY);
}

void MiniGame_DrawOverlay(s32 arg0) {
    Color_RGB8 sp2C = { 0, 0, 30 };
    Color_RGB8 sp28 = { 0, 0, 250 };

    DrawGradientPanel(0xC8, 0xBE, 0x5A, 0x20, &sp2C, &sp28);
    DrawPanel(0x1E, 0xBE, 0xA0, 0x20, 0x141);
    Text_ResetState();
    Text_BeginRender();
    Text_SetFont(4, -2);
    Text_SetEnvColor(0xFF, 0xFF, 0xFF, 0xFF);
    Text_SetPrimColor(0x50, 0x50, 0xFF, 0xFF);
    Text_Print(0x30, 0x14, "MINIGAME8 SAMPLE");
    Text_EndRender();
    Text_SetFont(2, -2);
    Text_SetEnvColor(0xFF, 0xC8, 0x32, 0xFF);

    switch (arg0) {
        case 0:
            Text_Print(0xCD, 0xC2, "OPENNING");
            break;

        case 1:
            Text_Print(0xCD, 0xC2, "PLAYING");
            break;

        case 2:
            Text_Print(0xCD, 0xC2, "ENDING");
            break;
    }

    if (arg0 == 1) {
        Text_SetEnvColor(0xFF, 0xFF, 0xFF, 0xFF);
        Text_Print(0x23, 0xC2, "CAMERA D:%d", gMiniGameCamDist);
        Text_Print(0x23, 0xCE, "X:%04hX Y:%04hX", gMiniGameCamX, gMiniGameCamY);
    }

    Text_SetupDL();
}

void MiniGame_RenderFrame(s32 arg0) {
    Stage_BeginDisplayList();
    Gfx_FillScreen(&gDisplayListHead, 0xA6BF);
    Gfx_FinishFrame();
    Graph_SetTextureState(gMiniGameRootNode);
    MiniGame_DrawOverlay(arg0);
    Stage_Advance();
}

void MiniGame_RunOpening(void) {
    func_80006C6C(0x10);
    GraphNode_TriggerAction(&D_86700940, 8);

    while (Anim_HasReachedEnd(&D_86700940) == 0) {
        MiniGame_PollController();
        MiniGame_RenderFrame(0);
    }
}

void MiniGame_RunPlaying(void) {
    s32 var_s1 = 1;
    s32 var_s0 = 0;

    GraphNode_TriggerAction(&D_86700940, 0);

    while (var_s1 != 0) {
        MiniGame_PollController();
        MiniGame_HandleCameraInput();

        var_s0++;

        if (gPlayer1Controller->buttonPressed & 0x1000) {
            var_s1 = 0;
        }

        if (var_s0 == 0x3C) {
            var_s0 = 0;
            InitAnimState(&D_86700940);
            GraphNode_TriggerSound(&D_86700940, 0xA);
        }

        MiniGame_RenderFrame(1);
    }
}

void MiniGame_RunEnding(void) {
    s32 i;

    GraphNode_TriggerAction(&D_86700940, 0xB);
    GraphNode_TriggerSound(&D_86700940, 0xB);

    while (Anim_HasReachedEnd(&D_86700940) == 0) {
        MiniGame_PollController();
        MiniGame_RenderFrame(2);
    }

    func_80006CB4(0x1E);

    for (i = 0; i < 30; i++) {
        MiniGame_PollController();
        MiniGame_RenderFrame(2);
    }
}

void MiniGame_InitGraph(void) {
    MemoryBlock* sp1C = state_pool_try_init(main_pool_get_available(), 0);

    gMiniGameRootNode = process_geo_layout(sp1C, &gMiniGameGeoLayout);
    mem_pool_resize_block(sp1C);
    Graph_InitRoots();
    Graph_AddToRootList0(&D_86700940);
    AssetManager_LoadArchives();
    D_86700930 = GeoLayout_LoadById(0x19);
    GraphNode_InitChild(&D_86700940, 0, 0x19, D_86700930->unk_08->unk_00[0]);
    GraphNode_TriggerAction(&D_86700940, 0);
    MiniGame_InitCamera();
}

s32 func_867006FC(UNUSED s32 arg0, UNUSED s32 arg1) {
    Stage* sp24;

    main_pool_push_state('MINI');

    Gfx_InitBuffers(0x10000, 0);
    sp24 = Stage_Create(0, 1, 3, 1, 2, 1);
    Text_Init(6, 0);

    ASSET_LOAD(D_1000000, common_menu1_ui, 0);

    FRAGMENT_LOAD(fragment31);
    Fragment_Load((((u32)D_8D000000 & 0x0FF00000) >> 0x14) - 0x10, _5C7A70_ROM_START, pokedex_area_model_ROM_START);

    MiniGame_InitGraph();
    Stage_Set(sp24);
    MiniGame_RunOpening();
    MiniGame_RunPlaying();
    MiniGame_RunEnding();
    Stage_Destroy();
    FontManager_Free();
    Gfx_FreeBuffers();

    main_pool_pop_state('MINI');

    return 0;
}
