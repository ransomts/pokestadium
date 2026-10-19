#include "fragment47.h"
#include "src/1AB70.h"
#include "src/1CF30.h"
#include "src/20330.h"
#include "src/232C0.h"
#include "src/2E110.h"
#include "src/3FB0.h"
#include "src/6A40.h"
#include "src/controller.h"
#include "src/fragments/39/fragment39.h"
#include "src/memory.h"
#include "src/stage_loader.h"

static s32 gSnapSelectMode;
static s32 gSnapSelectState;
static void* gSnapSelectBackground;
static unk_D_8380565C* gSnapSelectBgData;
static s32 D_83805660;
static s32 D_83805664;
static s32 D_83805668;

void SnapSelect_Init(s32 arg0) {
    gSnapSelectState = 0;
    gSnapSelectMode = arg0;
    D_83805668 = -1;
    D_83805660 = -1;
    MessageBank_Init();
    Text_LoadMessageBanks();
    SnapSelect_ConfigureGraphics();
    SnapSelect_InitBackground(0x68, 0x8A, gSnapSelectBgData);
    SnapSelect_SetupDisplay();
}

void SnapSelect_SetTimer(s32 arg0) {
    D_83805668 = arg0;
}

void SnapSelect_DrawHeader(s32 arg0, s32 arg1) {
    Gfx_DrawSpriteRGBA16(arg0, arg1, 0x40, 0x18, D_04000000, 0x40, 0);
    Gfx_DrawSpriteRGBA16(arg0, arg1 + 0x18, 0x40, 0x18, D_4000C00, 0x40, 0);
}

void SnapSelect_DrawPrompt(void) {
    char* sp2C = Text_GetMessageString_Bank2C(4);
    Color_RGBA8 sp28 = { 0x9A, 0x37, 0x54, 0xFF };
    Color_RGBA8 sp24 = { 0xC3, 0x54, 0x84, 0xFF };

    DrawPanelWithTextures(0x48, 0x28, 0x208, &sp28, &sp24);

    gSPDisplayList(gDisplayListHead++, gPrefDL_Border);

    SnapSelect_DrawHeader(0x28, 0x20);
    Text_ResetState();
    Text_SetFont(0x10, 0);
    Text_SetEnvColor(0, 0, 0, 0xFF);
    Text_Print(0x7A, 0x2D, sp2C);
    Text_SetEnvColor(0xFF, 0xFF, 0x77, 0xFF);
    Text_Print(0x78, 0x2B, sp2C);
    Text_SetupDL();
}

void SnapSelect_Update(void) {
    Stage_BeginDisplayList();
    if (D_83805668 != 0) {
        Gfx_DrawTextureAtlas(gSnapSelectBackground);
        SnapSelect_DrawPrompt();
    }
    SnapSelect_UpdateInputState(1);
    SnapSelect_UpdateCameraState(1);
    SnapSelect_UpdateUIState(1);
    Stage_Advance();
    if (D_83805668 > 0) {
        D_83805668 -= 1;
    }
}

void SnapSelect_Prepare(s32 arg0) {
    gSnapSelectState = 2;
    SnapSelect_SetTimer(0xC);

    main_pool_push_state('glpc');

    if ((D_83805664 >= 0) && (D_83805664 < 4)) {
        SnapSelect_SetCameraMode(D_83805664);
    }

    if (arg0 != 0) {
        SnapSelect_LoadModeData(D_83805664, &gGalleryFinalSelection.unk_08);
    } else {
        SnapSelect_LoadModeData(D_83805664, NULL);
    }
}

void SnapSelect_HandleResult(void) {
    D_83805660 = SnapSelect_GetResultCode(2);

    if (D_83805660 != -1) {
        if (D_83805660 == -2) {
            D_83805660 = 2;
        }

        if (D_83805660 != 2) {
            gSnapSelectState = 4;
            Stage_FadeOut(0xF);
        } else {
            gSnapSelectState = 1;
            SnapSelect_ApplySelection(D_83805664);
            D_83805660 = -1;
        }
    }
}

s32 SnapSelect_Process(void) {
    static s32 D_83804CB8 = 4;

    s32 sp7C = 1;
    s32 sp78 = 0;
    s32 sp74;
    PokemonData sp20;

    switch (gSnapSelectState) {
        case 0:
            if (Stage_GetFadeState() == 0) {
                D_83804CB8--;
                if (D_83804CB8 <= 0) {
                    gSnapSelectState = 1;
                    if (gSnapSelectMode == 1) {
                        D_83805664 = gGalleryFinalSelection.unk_08.unk_00;
                        SnapSelect_Prepare(1);
                    } else {
                        if (gSnapSelectMode == 2) {
                            D_83805664 = 5;
                        } else {
                            D_83805664 = -1;
                        }
                        SnapSelect_ApplySelection(D_83805664);
                    }
                }
            }
            break;

        case 1:
            D_83805664 = SnapSelect_GetUserChoice();
            switch (D_83805664) {
                case -2:
                    if (D_83402E20 > 0) {
                        gSnapSelectState = 3;
                        Menu_SetStep(2, gPlayer1Controller);
                    } else {
                        sp78 = 1;
                    }
                    break;

                case 0:
                case 1:
                case 2:
                case 3:
                case 4:
                    SnapSelect_Prepare(0);
                    break;

                case 5:
                    sp78 = 1;
                    _bcopy(&gSnapSelectBgData->unk_7E4, &sp20, sizeof(PokemonData));
                    Cam_ConvertInputToState(&D_83407AC8, &sp20);
                    break;
            }

            if (sp78 != 0) {
                gSnapSelectState = 4;
                Stage_FadeOut(0xF);
            }
            break;

        case 2:
            sp74 = Gallery_RentalViewerGetLoadState();
            if (sp74 != 0) {
                main_pool_pop_state('glpc');

                D_83805668 = -1;
                if (sp74 > 0) {
                    gSnapSelectState = 4;
                    Stage_FadeOut(0xF);
                } else {
                    gSnapSelectState = 1;
                    SnapSelect_ApplySelection(D_83805664);
                }
            }
            break;

        case 3:
            SnapSelect_HandleResult();
            break;

        case 4:
            if (Stage_GetFadeState() == 1) {
                sp7C = 0;
            }
            break;
    }
    return sp7C;
}

void SnapSelect_ReadInputs(void) {
    Cont_StartReadInputs();
    Cont_ReadInputs();
    MenuInput_Init();
}

void SnapSelect_MainLoop(void) {
    Stage_FadeIn(7);
    do {
        SnapSelect_ReadInputs();
        PlayerSelectStateUpdate();
        Gallery_RentalViewerUpdateBoxPicker();
        Menu_IsExitPressed();
        SnapSelect_Update();
    } while (SnapSelect_Process() != 0);
}

s32 SnapSelect_FinalizeResult(void) {
    s32 var_v1;
    unk_D_83407B18_008* temp_a0 = &gGalleryFinalSelection.unk_08;
    temp_a0 += 0;

    if (D_83805660 == 0) {
        var_v1 = 2;
    } else if (D_83805660 == 1) {
        var_v1 = 0;
    } else {
        switch (D_83805664) {
            case -2:
                var_v1 = 0;
                break;

            case 5:
                var_v1 = 6;
                break;

            default:
                var_v1 = 1;
                break;
        }
    }

    temp_a0->unk_00 = D_83805664;
    SnapSelect_CopyStateToInfo(temp_a0);
    return var_v1;
}

s32 SnapSelect_Run(s32 arg0, s32 arg1) {
    Stage* sp24;

    main_pool_push_state('SLCT');

    Gfx_InitBuffers(0x20000, 0);
    sp24 = Stage_Create(1, 0, 2, 0, 2, 1);
    gTextObjectHandle = Text_Init(0x1C, 0);

    ASSET_LOAD(D_1000000, common_menu1_ui, 0);
    ASSET_LOAD(D_2000000, common_menu2_ui, 0);
    ASSET_LOAD(D_3000000, gallery_ui, 0);
    ASSET_LOAD(D_04000000, snap_select_ui, 0);

    gSnapSelectBackground = BinArchive_GetFile(ASSET_LOAD2(backgrounds, 1, 1), 0x14);
    gSnapSelectBgData = BinArchive_GetFile(Asset_Load2(0x898000, NULL, 1, 0), 0x1A);

    SpriteAssets_Load();
    SnapSelect_Init(arg0);
    Stage_Set(sp24);
    SnapSelect_MainLoop();
    Stage_Destroy();
    FontManager_Free();
    Gfx_FreeBuffers();

    main_pool_pop_state('SLCT');

    return SnapSelect_FinalizeResult();
}
