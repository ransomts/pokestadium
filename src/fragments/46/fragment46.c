#include "fragment46.h"
#include "src/19840.h"
#include "src/1CF30.h"
#include "src/20330.h"
#include "src/30640.h"
#include "src/3FB0.h"
#include "src/49790.h"
#include "src/6A40.h"
#include "src/controller.h"
#include "src/fragments/43/fragment43.h"
#include "src/memory.h"
#include "src/stage_loader.h"

static s32 gFragment46_State;
static BinArchive* gStadiumModelsArchive;
static Stage* gFragment46_Stage;

static Camera* gFragment46_Camera = NULL;

void Fragment46_InitCamera(void) {
    UNUSED s32 pad;
    AssetManager* sp28;

    gFragment46_State = 0;
    sp28 = AssetManager_Create(1);
    Cam_CallInit318B8();
    gFragment46_Camera = Cam_Create(0x280, 0x1E0, NULL, gFragment46_Stage->unk_18[0], sp28, gStadiumModelsArchive, func_834006A0(1));
}

void func_83700090(void) {
}

void Fragment46_DrawFrame(void) {
    static s16 gFragment46_FrameCounter = 0;

    Stage_BeginDisplayList();
    if (gFragment46_Camera->unk_00 == 2) {
        func_834018C0(gFragment46_Camera->unk_08->img_p, 0, 0, gFragment46_Camera->unk_04, gFragment46_Camera->unk_06, 1, 0);
    }
    Stage_Advance();
    gFragment46_FrameCounter += 0x1000;
}

s32 Fragment46_CheckStartInput(void) {
    s32 sp1C = 0;

    if (Cam_FindActiveIndex(&gFragment46_Camera, 1) != -1) {
        return 0;
    }

    if (BTN_IS_PRESSED(gPlayer1Controller, BTN_A | BTN_B | BTN_CDOWN)) {
        sp1C = 1;
    }

    return sp1C;
}

s32 Fragment46_RunStateMachine(void) {
    static s32 gFragment46_FadeDelay = 2;

    s32 sp1C = 1;

    switch (gFragment46_State) {
        case 0:
            if (Stage_GetFadeState() == 0) {
                gFragment46_FadeDelay--;
                if (gFragment46_FadeDelay <= 0) {
                    gFragment46_State = 1;
                }
            }
            break;

        case 1:
            if (Fragment46_CheckStartInput() != 0) {
                gFragment46_State = 2;
                PlaySoundEffect(0x1A);
                Stage_FadeOut(1);
            }
            break;

        case 2:
            if (Stage_GetFadeState() == 1) {
                sp1C = 0;
            }
            break;
    }
    return sp1C;
}

void Fragment46_ReadInputs(void) {
    Cont_StartReadInputs();
    Cont_ReadInputs();
    MenuInput_Init();
}

void Fragment46_MainLoop(void) {
    do {
        Cam_Update(gFragment46_Camera);
    } while (gFragment46_Camera->unk_00 != 2);

    Stage_FadeIn(1);

    do {
        Fragment46_ReadInputs();
        Fragment46_DrawFrame();
    } while (Fragment46_RunStateMachine() != 0);
}

s32 Fragment46_Entry(UNUSED s32 arg0, UNUSED s32 arg1) {
    Stage* sp24;

    main_pool_push_state('ELRG');

    Gfx_InitBuffers(0x10000, 0);

    sp24 = Stage_Create(1, 0, 1, 0, 2, 1);
    gFragment46_Stage = sp24;

    Text_Init(0x18, 0);

    ASSET_LOAD(D_1000000, common_menu1_ui, 0);
    ASSET_LOAD(D_5000000, snap_mode_ui, 0);
    ASSET_LOAD(D_3000000, gallery_ui, 0);
    ASSET_LOAD(D_04000000, album_ui, 0);

    FRAGMENT_LOAD(fragment31);

    AssetManager_LoadArchives();

    gStadiumModelsArchive = ASSET_LOAD2(stadium_models, 1, 1);

    Fragment46_InitCamera();
    Stage_Set(sp24);
    Fragment46_MainLoop();
    Stage_Destroy();
    FontManager_Free();
    Gfx_FreeBuffers();

    main_pool_pop_state('ELRG');

    return 0;
}
