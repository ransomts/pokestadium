#include "fragment19.h"
#include "src/12D80.h"
#include "src/19840.h"
#include "src/1C720.h"
#include "src/1CF30.h"
#include "src/3FB0.h"
#include "src/6A40.h"
#include "src/6BC0.h"
#include "src/fragments/3/fragment3.h"
#include "src/memory.h"
#include "src/stage_loader.h"
#include "src/geo_layout.h"

static u32 D_86D00530[] = {
    0x0C00FFFF, 0x05000000, 0x0B00001E,  0x00000000, 0x014000F0, 0x0000000F, 0x00000000, 0x00000000, 0x05000000,
    0x0D000000, 0x05000000, 0x0F000002,  0x05000000, 0x1F00FFFF, 0x00000000, 0x00000000, 0x00000000, 0x00640064,
    0x00640000, 0x05000000, 0x06000000,  0x06000000, 0x14000000, 0x002B0012, 0xFFFFFF32, 0x16FFFFFF, 0x0F000003,
    0x05000000, 0x0A000000, &gGraphRoot0, 0x06000000, 0x06000000, 0x06000000, 0x06000000, 0x01000000, 0x00000000,
};

void func_86D00020(void) {
    gMiniCameraPtr = D_87906050->unk_00.unk_0C;

    miniCameraXRot = 0xA00;
    miniCameraYRot = 0;
    miniCameraDistance = 0x17C;
    miniCameraFov = 0x1E;
    miniCameraNear = 0x32;
    miniCameraFar = 0x1900;

    miniCameraCoords.x = 0;
    miniCameraCoords.y = 0x1E;
    miniCameraCoords.z = 0;

    miniUpdateCamera();
}

void miniUnkUpdateCamera(void) {
    minigameDebuggModeControl();
    miniUpdateCamera();
}

void miniUnkDrawHUB(UNUSED s32 arg0) {
    Stage_BeginDisplayList();
    Gfx_FillScreen(&gDisplayListHead, 1);
    Gfx_FinishFrame();
    Graph_SetTextureState(&D_87906050->unk_00);

    if (miniDebugMode != 0) {
        showDebuggCameraInfo();
    }

    Stage_Advance();
}

void func_86D00134(void) {
    func_80006C6C(0x10);
    miniTutoScreenState = 3;
}

void miniUnkControls(void) {
    s32 var_s1 = 1;

    while (var_s1 != 0) {
        MiniGame_ReadInputs();

        if (BTN_IS_PRESSED(gPlayer1Controller, BTN_A)) {
            func_879037D0(0.2f, 0.0f, 50.0f, 50.0f, 0x2000, 0, 0x1000);
        }

        if (BTN_IS_PRESSED(gPlayer1Controller, BTN_B)) {
            func_87903838(0.2f, 50.0f, 50.0f, 50.0f, 0, 0, 0);
        }

        if (BTN_IS_PRESSED(gPlayer1Controller, BTN_CLEFT)) {
            func_879038AC(0.2f, -50.0f, 50.0f, 50.0f, -0x6000, 0, 0x2000);
        }

        if (BTN_IS_PRESSED(gPlayer1Controller, BTN_Z)) {
            miniDebugMode = (miniDebugMode + 1) & 1;
        }

        if ((miniDebugMode == 0) && BTN_IS_PRESSED(gPlayer1Controller, BTN_START)) {
            minigameState = 1;
        }

        func_8790370C();
        miniUnkUpdateCamera();

        if ((miniDebugMode == 0) && BTN_IS_PRESSED(gPlayer1Controller, BTN_CDOWN)) {
            var_s1 = 0;
        }

        miniUnkDrawHUB(1);
    }
}

void func_86D0032C(void) {
    s32 i;

    func_80006CB4(0x1E);

    for (i = 0; i < 30; i++) {
        MiniGame_ReadInputs(); //  inputs
        miniUnkDrawHUB(2);
    }
}

void func_86D0037C(void) {
    UNUSED s32 pad[2];
    MemoryBlock* sp1C = state_pool_try_init(main_pool_get_available(), 0);

    D_87906050 = process_geo_layout(sp1C, &D_86D00530);
    mem_pool_resize_block(sp1C);
    Graph_InitRoots();
    AssetManager_LoadArchives();
    func_87903600();
    func_86D00020();
}

s32 func_86D003EC(s32 arg0, s32 arg1) {
    Stage* sp24;

    main_pool_push_state('MINI');

    Gfx_InitBuffers(0x20000, 0);
    sp24 = Stage_Create(0, 1, 3, 1, 2, 1);
    Text_Init(6, 0);

    ASSET_LOAD(D_1000000, common_menu1_ui, 0);
    FRAGMENT_LOAD(fragment31);
    Fragment_Load((((u32)D_8D000000 & 0x0FF00000) >> 0x14) - 0x10, _5C7A70_ROM_START, pokedex_area_model_ROM_START);

    func_86D0037C();
    Stage_Set(sp24);
    func_86D00134();
    miniUnkControls();
    func_86D0032C();
    Stage_Destroy();
    FontManager_Free();
    Gfx_FreeBuffers();

    main_pool_pop_state('MINI');

    return 0;
}
