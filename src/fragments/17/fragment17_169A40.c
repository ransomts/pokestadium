#include "fragment17.h"
#include "src/12D80.h"
#include "src/17300.h"
#include "src/geo_layout.h"
#include "src/19840.h"
#include "src/1C720.h"
#include "src/1CF30.h"
#include "src/20330.h"
#include "src/26820.h"
#include "src/3FB0.h"
#include "src/6A40.h"
#include "src/6BC0.h"
#include "src/DDC0.h"
#include "src/F420.h"
#include "src/controller.h"
#include "src/memory.h"
#include "src/stage_loader.h"

static u32 gStageGeoLayoutCommands[] = {
    0x0C00FFFF, 0x05000000, 0x0B00001E,  0x00000000, 0x014000F0, 0x00000032, 0x00000000, 0x00000118,
    0x05000000, 0x0D000000, 0x05000000,  0x14000000, 0x002B0012, 0xFFFFFF32, 0x16FFFFFF, 0x0F000003,
    0x05000000, 0x0A000000, &gGraphRoot0, 0x06000000, 0x06000000, 0x06000000, 0x06000000, 0x01000000,
};

static unk_D_86002F30* gStageGeoLayout;
static GraphNode* gStageRootGraphNode;
static Fragment2_1GraphNode gStageRootFragmentNode;
static unk_D_86002F34_00C* gStageCamera;
static BinArchive* D_86B10824;
static u8* gBackgroundTextureData;
static u8 gStageFadeAlpha;
static unk_func_80027FA0 D_86B10830;

void func_86B0A0B0(void) {
}

void Stage_SetupCamera(void) {
    gStageCamera = gStageRootGraphNode->unk_0C;
    Vec3f_Set(&gStageCamera->unk_60.at, 0.0f, 0.0f, 0.0f);
    Vec3f_Set(&gStageCamera->unk_60.eye, 0.0f, 0.0f, 200.0f);
    gStageCamera->unk_24.near = 16.0f;
    gStageCamera->unk_24.far = 32768.0f;
    gStageCamera->unk_24.fovy = 45.0f;
}

void Input_Update(void) {
    Cont_StartReadInputs();
    Cont_ReadInputs();
    MenuInput_Init();
}

void Stage_DrawBackgroundSprites(u8* arg0) {
    s32 i;
    s32 j;

    if (1) {}

    gDPPipeSync(gDisplayListHead++);

    gDPSetCycleType(gDisplayListHead++, G_CYC_1CYCLE);
    gDPSetRenderMode(gDisplayListHead++, G_RM_OPA_SURF, G_RM_OPA_SURF2);
    gDPSetTexturePersp(gDisplayListHead++, G_TP_NONE);
    gDPSetCombineMode(gDisplayListHead++, G_CC_DECALRGB, G_CC_DECALRGB);

    gDPPipeSync(gDisplayListHead++);

    for (i = 0; i < 15; i++) {
        for (j = 0; j < 20; j++, arg0 += 0x200) {
            Gfx_DrawSpriteRGBA16(j * 0x10, i * 0x10, 0x10, 0x10, arg0, 0x10, 0);
        }
    }

    gSPDisplayList(gDisplayListHead++, gPrefDL_End);
}

void Stage_RenderFrame(void) {
    Stage_BeginDisplayList();
    Stage_DrawBackgroundSprites(gBackgroundTextureData);
    Gfx_FillDepthRectangle(&gDisplayListHead, 0, 0, 0x140, 0xF0);
    Gfx_FinishFrame();
    Graph_SetTextureState(gStageRootGraphNode);
    func_86B0A0B0();
    Stage_Advance();
}

s32 Stage_HandleFade(void) {
    s32 var_v0;

    if ((gStageRootFragmentNode.unk_040.unk_08 >> 0x10) >= 0x5F) {
        GraphNode_SetColorRGBA(&gStageRootFragmentNode, 0, 0, 0, gStageFadeAlpha += 0x14);
    }

    if ((gStageRootFragmentNode.unk_040.unk_08 >> 0x10) == 0x64) {
        Stage_SetFillColor(1);
        Stage_FadeOut(3);
    }

    var_v0 = func_800174E4(&gStageRootFragmentNode) != 0;
    if (var_v0) {
        return 1;
    }
}

void BattleState_Run(void) {
    s32 var_s0 = 1;

    Stage_FadeIn(0xC);
    Music_ChangeTrack(0x30);

    while (var_s0 != 0) {
        Input_Update();
        if (Stage_HandleFade() != 0) {
            var_s0 = 0;
        }
        Stage_RenderFrame();
    }

    Stage_AdvanceN(2);
}

void Stage_Initialize(void) {
    MemoryBlock* sp1C = state_pool_try_init(main_pool_get_available(), 0);

    gStageRootGraphNode = process_geo_layout(sp1C, &gStageGeoLayoutCommands);

    mem_pool_resize_block(sp1C);
    Graph_InitRoots();
    Stage_SetupCamera();
    Graph_AddToRootList0(&gStageRootFragmentNode);
    AssetManager_LoadArchives();

    gStageGeoLayout = GeoLayout_LoadById(0xD6);
    GraphNode_InitChild(&gStageRootFragmentNode, 0, 0xD6, gStageGeoLayout->unk_08->unk_00[0]);
    GraphNode_TriggerAction(&gStageRootFragmentNode, 1);
    Vec3f_Set(&gStageRootFragmentNode.unk_024, 0.0f, 0.0f, 0.0f);
    gStageFadeAlpha = 0;
}

s32 BattleState_Handle24(void) {
    Stage* sp24;

    main_pool_push_state('MTWO');

    Gfx_InitBuffers(0x10000, 0);
    sp24 = Stage_Create(0, 1, 3, 1, 2, 1);
    Text_Init(6, 0);

    ASSET_LOAD(D_1000000, common_menu1_ui, 0);
    FRAGMENT_LOAD(fragment31);

    GbsEnsureBankLoaded(2);
    func_80027FA0(&D_86B10830, gBattleContext.unk_11F2);

    if (gBattleContext.unk_11F2 == 1) {
        D_86B10824 = ASSET_LOAD2(backgrounds, 1, 1);
        gBackgroundTextureData = BinArchive_GetFile(D_86B10824, 2);
    } else if (D_86B10830.unk_00 & 0x100) {
        D_86B10824 = ASSET_LOAD2(backgrounds, 1, 1);
        gBackgroundTextureData = BinArchive_GetFile(D_86B10824, 1);
    } else {
        D_86B10824 = ASSET_LOAD2(backgrounds, 1, 1);
        gBackgroundTextureData = BinArchive_GetFile(D_86B10824, 2);
    }

    Stage_Initialize();
    Stage_Set(sp24);
    BattleState_Run();
    Stage_Destroy();
    FontManager_Free();
    Gfx_FreeBuffers();

    main_pool_pop_state('MTWO');

    return 0;
}
