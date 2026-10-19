#include "fragment12.h"
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

static u32 gMiniGameGeoLayoutCommands[] = {
    0x0C00FFFF, 0x05000000, 0x0B00001E, 0x00000000, 0x014000F0, 0x0000000F, 0x00000000, 0x00000000,
    0x05000000, 0x0D000000, 0x05000000, 0x0F000002, 0x05000000, 0x1F00FFFF, 0x00000000, 0x00000000,
    0x00000000, 0x00640064, 0x00640000, 0x05000000, 0x00000000, 0x8D000020, 0x06000000, 0x06000000,
    0x14000000, 0x002B0012, 0xFFFFFF32, 0x16FFFFFF, 0x0F000003, 0x05000000, 0x0A000000, 0x800AC840,
    0x06000000, 0x06000000, 0x06000000, 0x06000000, 0x01000000,
};

static unk_D_86002F30* gMiniGameGeoLayoutData;
static GraphNode* D_86600944;
static CameraStruct* D_86600948;
static Fragment2_1GraphNode gMiniGameAnimNode;
static s16 D_86600AB8;
static s16 D_86600ABA;
static s16 D_86600ABC;

void MiniGame_PollInputs(void) {
    Cont_StartReadInputs();
    Cont_ReadInputs();
    MenuInput_Init();
}

void Minigame_Sample7Viewer_InitCamera(void) {
    D_86600948 = D_86600944->unk_0C;

    D_86600AB8 = 0x100;
    D_86600ABA = 0;
    D_86600ABC = 0x78;

    D_86600948->unk_24.near = 10.0f;
    D_86600948->unk_24.far = 6400.0f;

    Camera_SetViewParameters(&D_86600948->unk_60.at, &D_86600948->unk_60.eye, D_86600ABC, D_86600AB8, D_86600ABA);
}

void MiniGame_UpdateCamera(void) {
    if (gPlayer1Controller->buttonDown & 0x800) {
        D_86600AB8 += 256;
    }

    if (gPlayer1Controller->buttonDown & 0x400) {
        D_86600AB8 -= 256;
    }

    if (gPlayer1Controller->buttonDown & 0x200) {
        D_86600ABA += 256;
    }

    if (gPlayer1Controller->buttonDown & 0x100) {
        D_86600ABA -= 256;
    }

    if (gPlayer1Controller->buttonDown & 8) {
        D_86600ABC -= 10;
    }

    if (gPlayer1Controller->buttonDown & 4) {
        D_86600ABC += 10;
    }

    if (D_86600AB8 > 16128) {
        D_86600AB8 = 16128;
    }

    if (D_86600AB8 < 0) {
        D_86600AB8 = 0;
    }

    if (D_86600ABC < 50) {
        D_86600ABC = 50;
    }

    if (D_86600ABC > 2000) {
        D_86600ABC = 2000;
    }

    Camera_SetViewParameters(&D_86600948->unk_60.at, &D_86600948->unk_60.eye, D_86600ABC, D_86600AB8, D_86600ABA);
}

void Minigame_Sample7Viewer_DrawDebugText(s32 arg0) {
    Color_RGB8 sp2C = { 0, 0, 30 };
    Color_RGB8 sp28 = { 0, 0, 250 };

    DrawGradientPanel(0xC8, 0xBE, 0x5A, 0x20, &sp2C, &sp28);
    DrawPanel(0x1E, 0xBE, 0xA0, 0x20, 0x141);
    Text_ResetState();
    Text_BeginRender();
    Text_SetFont(4, -2);
    Text_SetEnvColor(0xFF, 0xFF, 0xFF, 0xFF);
    Text_SetPrimColor(0x50, 0x50, 0xFF, 0xFF);
    Text_Print(0x30, 0x14, "MINIGAME7 SAMPLE");
    Text_EndRender();
    Text_SetFont(2, -2);
    Text_SetEnvColor(0xFF, 0xC8, 0x32, 0xFF);

    switch (arg0) {
        case 0:
            Text_Print(0xCD, 0xC2, "OPENNING");
            break;

        case 2:
            Text_Print(0xCD, 0xC2, "PLAYING");
            break;

        case 3:
            Text_Print(0xCD, 0xC2, "ENDING");
            break;
    }

    if (arg0 == 2) {
        Text_SetEnvColor(0xFF, 0xFF, 0xFF, 0xFF);
        Text_Print(0x23, 0xC2, "CAMERA D:%d", D_86600ABC);
        Text_Print(0x23, 0xCE, "X:%04hX Y:%04hX", D_86600AB8, D_86600ABA);
    }

    Text_SetupDL();
}

void Minigame_Sample7Viewer_DrawFrame(s32 arg0) {
    Stage_BeginDisplayList();
    Gfx_FillScreen(&gDisplayListHead, 0xA6BF);
    Gfx_FinishFrame();
    Graph_SetTextureState(D_86600944);
    Minigame_Sample7Viewer_DrawDebugText(arg0);
    Stage_Advance();
}

void Minigame_Sample7Viewer_OpeningLoop(void) {
    Stage_FadeIn(0x10);
    GraphNode_TriggerAction(&gMiniGameAnimNode, 8);
    if (Anim_HasReachedEnd(&gMiniGameAnimNode) == 0) {
        do {
            MiniGame_PollInputs();
            Minigame_Sample7Viewer_DrawFrame(0);
        } while (Anim_HasReachedEnd(&gMiniGameAnimNode) == 0);
    }
}

void Minigame_Sample7Viewer_PlayingLoop(void) {
    s32 var_s1 = 1;
    s32 var_s0 = 0;

    GraphNode_TriggerAction(&gMiniGameAnimNode, 0);

    while (var_s1 != 0) {
        MiniGame_PollInputs();
        MiniGame_UpdateCamera();

        var_s0++;

        if (gPlayer1Controller->buttonPressed & 0x1000) {
            var_s1 = 0;
        }

        if (var_s0 == 60) {
            var_s0 = 0;
            InitAnimState(&gMiniGameAnimNode);
            GraphNode_TriggerSound(&gMiniGameAnimNode, 0xA);
        }

        Minigame_Sample7Viewer_DrawFrame(2);
    }
}

void Minigame_Sample7Viewer_EndingLoop(void) {
    s32 i;

    GraphNode_TriggerAction(&gMiniGameAnimNode, 0xB);
    GraphNode_TriggerSound(&gMiniGameAnimNode, 0xB);

    while (Anim_HasReachedEnd(&gMiniGameAnimNode) == 0) {
        MiniGame_PollInputs();
        Minigame_Sample7Viewer_DrawFrame(3);
    }

    Stage_FadeOut(30);

    for (i = 0; i < 30; i++) {
        MiniGame_PollInputs();
        Minigame_Sample7Viewer_DrawFrame(3);
    }
}

void Minigame_Sample7Viewer_Init(void) {
    MemoryBlock* sp1C = state_pool_try_init(main_pool_get_available(), 0);

    D_86600944 = process_geo_layout(sp1C, &gMiniGameGeoLayoutCommands);
    mem_pool_resize_block(sp1C);
    Graph_InitRoots();
    Graph_AddToRootList0(&gMiniGameAnimNode);
    AssetManager_LoadArchives();
    gMiniGameGeoLayoutData = GeoLayout_LoadById(0x19);
    GraphNode_InitChild(&gMiniGameAnimNode, 0, 0x19, gMiniGameGeoLayoutData->unk_08->unk_00[0]);
    GraphNode_TriggerAction(&gMiniGameAnimNode, 0);
    Minigame_Sample7Viewer_InitCamera();
}

s32 Minigame_Sample7Viewer(UNUSED s32 arg0, UNUSED s32 arg1) {
    Stage* sp24;

    main_pool_push_state('MINI');

    Gfx_InitBuffers(0x10000, 0);
    sp24 = Stage_Create(0, 1, 3, 1, 2, 1);
    Text_Init(6, 0);

    ASSET_LOAD(D_1000000, common_menu1_ui, 0);

    FRAGMENT_LOAD(fragment31);
    Fragment_Load((((u32)D_8D000000 & 0x0FF00000) >> 0x14) - 0x10, _5C7A70_ROM_START, pokedex_area_model_ROM_START);

    Minigame_Sample7Viewer_Init();
    Stage_Set(sp24);
    Minigame_Sample7Viewer_OpeningLoop();
    Minigame_Sample7Viewer_PlayingLoop();
    Minigame_Sample7Viewer_EndingLoop();
    Stage_Destroy();
    FontManager_Free();
    Gfx_FreeBuffers();

    main_pool_pop_state('MINI');
    return 0;
}
