#include "minigame_sample2_viewer.h"
#include "src/12D80.h"
#include "src/19840.h"
#include "src/1C720.h"
#include "src/1CF30.h"
#include "src/20330.h"
#include "src/3FB0.h"
#include "src/6A40.h"
#include "src/6BC0.h"
#include "src/controller.h"
#include "src/fragments/51/fragment51.h"
#include "src/geo_layout.h"
#include "src/memory.h"
#include "src/stage_loader.h"

static unk_D_86002F30* gGeoLayout_StageBackground;
static GraphNode* gStageTextureNode;
static Fragment2_1GraphNode D_82800538;
static BinArchive* D_828006A0;
static u8* D_828006A4;

static u32 D_828004D0[] = {
    0x0C00FFFF, 0x05000000, 0x0B00001E,  0x00000000, 0x014000F0, 0x00000032, 0x00000000, 0x00000118,
    0x05000000, 0x0D000000, 0x05000000,  0x14000000, 0x002B0012, 0xFFFFFF32, 0x16FFFFFF, 0x0F000003,
    0x05000000, 0x0A000000, &gGraphRoot0, 0x06000000, 0x06000000, 0x06000000, 0x06000000, 0x01000000,
};

void Input_PollAndMenuInit(void) {
    Cont_StartReadInputs();
    Cont_ReadInputs();
    Input_ResetRepeatState();
}

void func_82800050(u8* arg0) {
    s32 i;
    s32 j;

    gDPPipeSync(gDisplayListHead++);

    gDPSetCycleType(gDisplayListHead++, G_CYC_1CYCLE);
    gDPSetRenderMode(gDisplayListHead++, G_RM_OPA_SURF, G_RM_OPA_SURF2);
    gDPSetTexturePersp(gDisplayListHead++, G_TP_NONE);
    gDPSetCombineMode(gDisplayListHead++, G_CC_DECALRGB, G_CC_DECALRGB);

    gDPPipeSync(gDisplayListHead++);

    if (1) {}

    for (i = 0; i < 15; i++) {
        for (j = 0; j < 20; j++, arg0 += 0x200) {
            Gfx_DrawTextureRgba16(j * 0x10, i * 0x10, 0x10, 0x10, arg0, 0x10, 0);
        }
    }

    gSPDisplayList(gDisplayListHead++, gPrefDL_End);
}

void func_828001D0(void) {
    BgStage_DrawFrame();
    func_82800050(D_828006A4);
    GfxImage_ClearDepthRectangle(&gDisplayListHead, 0, 0, 0x140, 0xF0);
    GeoRender_AdvanceFrameCounter();
    Geo_RenderRootNode(gStageTextureNode);
    BgStage_AdvanceFrame();
}

void func_82800238(void) {
    s32 i;

    StageFade_StartFromOpaque(0x10);

    for (i = 0; i < 16; i++) {
        Input_PollAndMenuInit();
        func_828001D0();
    }

    do {
        Input_PollAndMenuInit();
        func_828001D0();
    } while (!(BTN_IS_PRESSED(gPlayer1Controller, BTN_A)));

    StageFade_StartFromTransparent(0x10);

    for (i = 0; i < 16; i++) {
        Input_PollAndMenuInit();
        func_828001D0();
    }

    StageLoader_RunFrames(2);
}

void func_828002E4(void) {
    MemoryBlock* sp1C = MainPool_AllocState(main_pool_get_available(), 0);

    gStageTextureNode = process_geo_layout(sp1C, D_828004D0);
    MainPool_FinalizeAllocation(sp1C);
    ModelRenderer_InitDisplayRoots();
    ModelRenderer_AttachDisplayObject(&D_82800538);
    PokeIcon_OpenModelArchives();
    gGeoLayout_StageBackground = Model_LoadByArchiveIndex(0x96);
    Model_InitDisplayObject(&D_82800538, 0, 0x96, gGeoLayout_StageBackground->unk_08->posX[0]);
    ModelAnim_SetAnimation(&D_82800538, 0);
}

s32 Fragment52_Main(UNUSED s32 arg0, UNUSED s32 arg1) {
    Stage* sp24;

    main_pool_push_state('MTWO');

    Gfx_InitDisplayListBuffers(0x10000, 0);
    sp24 = StageContext_Allocate(0, 1, 3, 1, 2, 1);
    Font_Init(6, 0);

    ASSET_LOAD(D_1000000, common_menu1_ui, 0);
    FRAGMENT_LOAD(fragment31);

    D_828006A0 = ASSET_LOAD2(backgrounds, 1, 1);
    D_828006A4 = BinArchive_GetFile(D_828006A0, 2);

    func_828002E4();
    StageContext_Activate(sp24);
    func_82800238();
    StageContext_Deactivate();
    Font_Free();
    Gfx_FreeDisplayListBuffers();

    main_pool_pop_state('MTWO');

    return 0;
}
