#include "minigame_sample8_viewer.h"
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
static CameraStruct* gMiniGameCameraNode;
static Fragment2_1GraphNode D_86700940;

static s16 gMiniGameCamX;
static s16 gMiniGameCamY;
static s16 gMiniGameCamDist;

void Minigame_Sample8Viewer_PollInput(void) {
    Cont_StartReadInputs();
    Cont_ReadInputs();
    Input_ResetRepeatState();
}

void Minigame_Sample8Viewer_InitCamera(void) {
    gMiniGameCameraNode = gMiniGameRootNode->unk_0C;
    gMiniGameCamX = 0x100;
    gMiniGameCamY = 0;
    gMiniGameCamDist = 0x78;

    gMiniGameCameraNode->unk_24.near = 50.0f;
    gMiniGameCameraNode->unk_24.far = 6400.0f;
    Camera_ComputeEyeFromAngles(&gMiniGameCameraNode->unk_60.at, &gMiniGameCameraNode->unk_60.eye, gMiniGameCamDist, gMiniGameCamX, gMiniGameCamY);
}

void Minigame_Sample8Viewer_UpdateCameraControls(void) {
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

    Camera_ComputeEyeFromAngles(&gMiniGameCameraNode->unk_60.at, &gMiniGameCameraNode->unk_60.eye, gMiniGameCamDist, gMiniGameCamX, gMiniGameCamY);
}

void Minigame_Sample8Viewer_DrawDebugText(s32 arg0) {
    Color_RGB8 sp2C = { 0, 0, 30 };
    Color_RGB8 sp28 = { 0, 0, 250 };

    Ui_DrawGradientPanel(0xC8, 0xBE, 0x5A, 0x20, &sp2C, &sp28);
    Ui_DrawBorderedPanel(0x1E, 0xBE, 0xA0, 0x20, 0x141);
    Font_BeginTranslucentTextRendering();
    Font_EnableTwoCycleTexturing();
    Font_SetActive(4, -2);
    Text_SetEnvColor(0xFF, 0xFF, 0xFF, 0xFF);
    Text_SetPrimColor(0x50, 0x50, 0xFF, 0xFF);
    Font_Printf(0x30, 0x14, "MINIGAME8 SAMPLE");
    Font_DisableTwoCycleTexturing();
    Font_SetActive(2, -2);
    Text_SetEnvColor(0xFF, 0xC8, 0x32, 0xFF);

    switch (arg0) {
        case 0:
            Font_Printf(0xCD, 0xC2, "OPENNING");
            break;

        case 1:
            Font_Printf(0xCD, 0xC2, "PLAYING");
            break;

        case 2:
            Font_Printf(0xCD, 0xC2, "ENDING");
            break;
    }

    if (arg0 == 1) {
        Text_SetEnvColor(0xFF, 0xFF, 0xFF, 0xFF);
        Font_Printf(0x23, 0xC2, "CAMERA D:%d", gMiniGameCamDist);
        Font_Printf(0x23, 0xCE, "X:%04hX Y:%04hX", gMiniGameCamX, gMiniGameCamY);
    }

    Font_EndTexturedTextRendering();
}

void Minigame_Sample8Viewer_DrawFrame(s32 arg0) {
    BgStage_DrawFrame();
    GfxImage_FillCurrent(&gDisplayListHead, 0xA6BF);
    GeoRender_AdvanceFrameCounter();
    Geo_RenderRootNode(gMiniGameRootNode);
    Minigame_Sample8Viewer_DrawDebugText(arg0);
    BgStage_AdvanceFrame();
}

void Minigame_Sample8Viewer_OpeningLoop(void) {
    StageFade_StartFromOpaque(0x10);
    ModelAnim_SetAnimation(&D_86700940, 8);

    while (ModelAnim_IsFinished(&D_86700940) == 0) {
        Minigame_Sample8Viewer_PollInput();
        Minigame_Sample8Viewer_DrawFrame(0);
    }
}

void Minigame_Sample8Viewer_PlayingLoop(void) {
    s32 var_s1 = 1;
    s32 var_s0 = 0;

    ModelAnim_SetAnimation(&D_86700940, 0);

    while (var_s1 != 0) {
        Minigame_Sample8Viewer_PollInput();
        Minigame_Sample8Viewer_UpdateCameraControls();

        var_s0++;

        if (gPlayer1Controller->buttonPressed & 0x1000) {
            var_s1 = 0;
        }

        if (var_s0 == 0x3C) {
            var_s0 = 0;
            ModelAnim_ClearEventTrack(&D_86700940);
            ModelAnim_SetEventTrack(&D_86700940, 0xA);
        }

        Minigame_Sample8Viewer_DrawFrame(1);
    }
}

void Minigame_Sample8Viewer_EndingLoop(void) {
    s32 i;

    ModelAnim_SetAnimation(&D_86700940, 0xB);
    ModelAnim_SetEventTrack(&D_86700940, 0xB);

    while (ModelAnim_IsFinished(&D_86700940) == 0) {
        Minigame_Sample8Viewer_PollInput();
        Minigame_Sample8Viewer_DrawFrame(2);
    }

    StageFade_StartFromTransparent(0x1E);

    for (i = 0; i < 30; i++) {
        Minigame_Sample8Viewer_PollInput();
        Minigame_Sample8Viewer_DrawFrame(2);
    }
}

void Minigame_Sample8Viewer_Init(void) {
    MemoryBlock* sp1C = MainPool_AllocState(main_pool_get_available(), 0);

    gMiniGameRootNode = process_geo_layout(sp1C, &gMiniGameGeoLayout);
    MainPool_FinalizeAllocation(sp1C);
    ModelRenderer_InitDisplayRoots();
    ModelRenderer_AttachDisplayObject(&D_86700940);
    PokeIcon_OpenModelArchives();
    D_86700930 = Model_LoadByArchiveIndex(0x19);
    Model_InitDisplayObject(&D_86700940, 0, 0x19, D_86700930->unk_08->unk_00[0]);
    ModelAnim_SetAnimation(&D_86700940, 0);
    Minigame_Sample8Viewer_InitCamera();
}

s32 Minigame_Sample8Viewer(UNUSED s32 arg0, UNUSED s32 arg1) {
    Stage* sp24;

    main_pool_push_state('MINI');

    Gfx_InitDisplayListBuffers(0x10000, 0);
    sp24 = StageContext_Allocate(0, 1, 3, 1, 2, 1);
    Font_Init(6, 0);

    ASSET_LOAD(D_1000000, common_menu1_ui, 0);

    FRAGMENT_LOAD(fragment31);
    Fragment_Load((((u32)D_8D000000 & 0x0FF00000) >> 0x14) - 0x10, _5C7A70_ROM_START, pokedex_area_model_ROM_START);

    Minigame_Sample8Viewer_Init();
    StageContext_Activate(sp24);
    Minigame_Sample8Viewer_OpeningLoop();
    Minigame_Sample8Viewer_PlayingLoop();
    Minigame_Sample8Viewer_EndingLoop();
    StageContext_Deactivate();
    Font_Free();
    Gfx_FreeDisplayListBuffers();

    main_pool_pop_state('MINI');

    return 0;
}
