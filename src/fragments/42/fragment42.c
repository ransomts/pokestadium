#include "fragment42.h"
#include "src/19840.h"
#include "src/1C720.h"
#include "src/1CF30.h"
#include "src/20330.h"
#include "src/2E110.h"
#include "src/20470.h"
#include "src/3FB0.h"
#include "src/49790.h"
#include "src/4BDC0.h"
#include "src/6A40.h"
#include "src/6BC0.h"
#include "src/C030.h"
#include "src/controller.h"
#include "src/fragments/43/fragment43.h"
#include "src/memory.h"
#include "src/stage_loader.h"

typedef struct MenuItem {
    /* 0x00 */ u8* unk_00;
    /* 0x04 */ u16 unk_04;
    /* 0x06 */ u16 unk_06;
    /* 0x08 */ s16 unk_08;
    /* 0x0A */ s16 unk_0A;
    /* 0x0C */ s16* unk_0C;
    /* 0x10 */ s16 unk_10;
    /* 0x12 */ s16 unk_12;
    /* 0x14 */ s32 unk_14;
} MenuItem; // size = 0x18

typedef struct MenuSubPanelItem {
    /* 0x00 */ u8* unk_00;
    /* 0x04 */ u16 unk_04;
    /* 0x06 */ u16 unk_06;
    /* 0x08 */ s16 unk_08;
} MenuSubPanelItem; // size = 0xC

static s32 D_833032E0;
static s32 gMenuStep;
static unk_D_83407B38 gMenuActiveData;
static BinArchive* gMenuAssetArchive;
static s32 gMenuDirty;
static unk_D_83403C60 gSwapTempPokemon;
static s32 gMenuConfirmState;
static s32 gBackgroundFadeTimer;
static s32 gStickerStationConnected;
static s32 gFadeOutTimer;
static s32 gMenuInputLocked;

static MenuSubPanelItem gSubPanelItems[] = {
    { NULL, 0x30, 0x23, 0 },
    { D_03002A40, 0x20, 0x24, 7 },
    { NULL, 0x30, 0x23, 8 },
};

static s16 D_833031A4[] = { 0x11 };
static s16 D_833031A8[] = { 0x12 };
static s16 D_833031AC[] = { 0x13 };
static s16 D_833031B0[] = { -1, 0x15 };

static MenuItem D_833031B4[] = {
    {
        D_03001000,
        48,
        35,
        5,
        11,
        NULL,
        1,
        0,
        28,
    },
    {
        D_3001D20,
        48,
        35,
        6,
        12,
        D_833031A4,
        1,
        0,
        28,
    },
    {
        D_03002A40,
        32,
        36,
        7,
        13,
        D_833031A8,
        1,
        0,
        28,
    },
    {
        NULL,
        48,
        35,
        8,
        14,
        D_833031AC,
        1,
        0,
        28,
    },
    {
        D_03003340,
        32,
        36,
        61,
        62,
        NULL,
        1,
        0,
        2,
    },
    {
        D_03003C40,
        32,
        36,
        -1,
        -1,
        D_833031B0,
        1,
        0,
        28,
    },
    {
        NULL,
        0,
        0,
        10,
        16,
        NULL,
        2,
        0,
        3,
    },
};
static s16 gGridOffsetX[2] = { 0x108, 0x108 };
static s16 gGridOffsetY[2] = { 0x5C, 0x5C };
static s16 gGridStepX[2] = { 0x98, 0x4C };
static s16 gGridStepY[2] = { 0x7A, 0x3D };
static s32 gMenuExitFadeColors[] = { 5, 3, 3, 0, 0, 7, 8 };

void DrawPanelFrame(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u8 arg4, u8 arg5, u8 arg6, u8 arg7) {
    gSPDisplayList(gDisplayListHead++, gPrefDL_Border);
    gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, arg7);

    Gfx_DrawSpriteIA8(arg0 - 7, arg1 - 7, 8, 8, &D_300BE40, 8, 0);
    Gfx_DrawSpriteIA8((arg0 + arg2) - 1, arg1 - 7, 8, 8, &D_300BE80, 8, 0);
    Gfx_DrawTextureRect(arg0 + 1, arg1 - 7, arg2 - 2, 8, 0, 0, 0, 0x400, 0);
    Gfx_DrawSpriteIA8(arg0 - 7, (arg1 + arg3) - 1, 8, 8, &D_300BEC0, 8, 0);
    Gfx_DrawTextureRect(arg0 - 7, arg1 + 1, 8, arg3 - 2, 0, 0, 0x400, 0, 0);
    Gfx_DrawSpriteIA8((arg0 + arg2) - 1, (arg1 + arg3) - 1, 8, 8, &D_300BF00, 8, 0);
    Gfx_DrawTextureRect(arg0 + 1, (arg1 + arg3) - 1, arg2 - 2, 8, 0, 0, 0, 0x400, 0);
    Gfx_DrawTextureRect((arg0 + arg2) - 1, arg1 + 1, 8, arg3 - 2, 0, 0, 0x400, 0, 0);

    gSPDisplayList(gDisplayListHead++, gPrefDL_Fill);

    Gfx_FillRectRGBA(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7);

    gSPDisplayList(gDisplayListHead++, gPrefDL_End);
}

unk_D_83407B38* GetActiveMenu(void) {
    unk_D_83407B38* ret;

    if (gGallerySpecialUnlocked == 0) {
        ret = &gMenuActiveData;
    } else {
        ret = &gGalleryCamList;
    }
    return ret;
}

void UpdateMenuItemStates(void) {
    MenuItem* ptr;
    s32 sp28;
    s32 i;
    s32 sp20;
    s16 sp1C[2];
    u8* sp18;
    s32 var_v0;

    sp28 = CountDisplayableMonIndices(gGalleryEntries, 0x24, 1);
    if (gGallerySpecialUnlocked == 0) {
        sp1C[1] = 0xF;
        sp1C[0] = 0x14;
        var_v0 = CountDisplayableMonIndices(gCurrentCamEntry, 4, 1);
        sp20 = 4;
        sp18 = D_3004540;
    } else {
        sp1C[1] = 0x3F;
        sp1C[0] = 0x40;
        var_v0 = CountDisplayableMonIndices(gCurrentCamEntryPage, 0x10, 1);
        sp20 = 0x10;
        sp18 = D_3005260;
    }

    ptr = &D_833031B4[0];

    for (i = 0; i < 7; i++, ptr++) {
        switch (i) {
            case 1:
            case 2:
                if (sp28 > 0) {
                    ptr->unk_12 = 0;
                } else {
                    ptr->unk_12 = 1;
                }
                break;

            case 3:
                if (var_v0 > 0) {
                    ptr->unk_12 = 0;
                } else {
                    ptr->unk_12 = 1;
                }
                ptr->unk_00 = sp18;
                break;

            case 5:
                if (gGallerySpecialViewed == 0) {
                    ptr->unk_08 = 9;
                    ptr->unk_0A = sp1C[1];
                } else {
                    ptr->unk_08 = 0x44;
                    ptr->unk_0A = 0x46;
                }

                D_833031B0[0] = sp1C[0];

                if ((var_v0 < sp20) && (gGallerySpecialViewed == 0)) {
                    ptr->unk_12 = 1;
                } else if (gStickerStationConnected == 0) {
                    ptr->unk_12 = 2;
                } else {
                    ptr->unk_12 = 0;
                }
                break;

            default:
                ptr->unk_12 = 0;
                break;
        }
    }
}

s32 Menu_HandleConfirm(void) {
    s32 sp1C = 0;

    if (Gallery_CheckForChanges() != 0) {
        gMenuStep = 6;
        Menu_SetStep(3, gPlayer1Controller);
        gBackgroundFadeTimer = 4;
    } else {
        sp1C = 1;
    }
    return sp1C;
}

s32 ProcessMenuInput(void) {
    s32 sp2C;
    s32 sp28;
    MenuItem* sp24;
    s32 sp20;
    s32 sp1C;

    sp2C = 0;
    sp28 = 0;
    sp20 = gGallerySpecialViewed;
    sp1C = D_83402E28;

    if (Cam_FindActiveIndex(GetActiveMenu()->unk_20, 0x25) != -1) {
        return 0;
    }

    if (gPlayer1Controller->buttonPressed & 0x800) {
        D_83402E28--;
        if (D_83402E28 < 0) {
            D_83402E28 = 6;
        }
    } else if (gPlayer1Controller->buttonPressed & 0x400) {
        D_83402E28++;
        if (D_83402E28 >= 7) {
            D_83402E28 = 0;
        }
    } else if (gPlayer1Controller->buttonPressed & 0x4000) {
        sp2C = 1;
        D_83402E28 = 6;
    }

    if (sp1C != D_83402E28) {
        PlaySoundEffect(1);
    }

    sp24 = &D_833031B4[D_83402E28];

    if (sp1C != D_83402E28) {
        gMenuDirty = 0;
        gMenuInputLocked = 0;
    }

    if ((gGalleryAudioStateFlag != 0) && (gMenuInputLocked == 0)) {
        if ((gPlayer1Controller->buttonDown & 0x20) && (gPlayer1Controller->buttonDown & 0x10) && (D_83402E28 == 5)) {
            gGallerySpecialViewed = 1;
        } else {
            gGallerySpecialViewed = 0;
        }
    }

    if (sp20 != gGallerySpecialViewed) {
        gMenuDirty = 0;
        UpdateMenuItemStates();
    }

    if (sp2C != 0) {
        if (Menu_HandleConfirm() != 0) {
            sp28 = 1;
        }
        PlaySoundEffect(sp24->unk_14);
    } else if (gPlayer1Controller->buttonPressed & 0x8000) {
        if (sp24->unk_12 == 0) {
            switch (D_83402E28) {
                default:
                    sp28 = 1;
                    break;

                case 3:
                    D_833032E0 = 2;
                    gMenuStep = 3;
                    break;

                case 4:
                    gGallerySpecialUnlocked ^= 1;
                    UpdateMenuItemStates();
                    break;

                case 5:
                    if (gGallerySpecialViewed != 0) {
                        sp28 = 2;
                    } else {
                        gMenuStep = 5;
                        gMenuConfirmState = 0;
                    }
                    break;

                case 6:
                    if (Menu_HandleConfirm() != 0) {
                        sp28 = 1;
                    }
                    break;
            }
            PlaySoundEffect(sp24->unk_14);
        } else if ((D_83402E28 == 5) && (gGallerySpecialViewed != 0)) {
            sp28 = 2;
            PlaySoundEffect(sp24->unk_14);
        } else {
            gMenuDirty = 1;
            PlaySoundEffect(8);
        }
    }
    return sp28;
}

void ResetMenuState(void) {
    D_833032E0 = 0;
    gMenuStep = 1;
    GallerySelection_Init(&gGalleryMainSelection);
}

s32 HandlePokemonGridInput(unk_D_83407B38* arg0) {
    s32 sp4C;
    s32 sp48;
    s32 sp44;
    s32 sp40;
    s32 sp3C;
    Camera* sp38;
    UNUSED s32 pad[2];
    s32 idx;
    Camera* sp28;

    sp4C = 0;
    sp48 = arg0->unk_00;
    Gallery_GetPageAndIndex(arg0, &sp44, &sp40, sp48);
    if (Cam_FindActiveIndex(arg0->unk_20, 0x25) != -1) {
        return 0;
    }

    if (gPlayer1Controller->buttonPressed & 0x800) {
        sp40--;
        if (sp40 < 0) {
            sp40 = arg0->unk_1C - 1;
        }
    }

    if (gPlayer1Controller->buttonPressed & 0x400) {
        sp40++;
        if (sp40 >= arg0->unk_1C) {
            sp40 = 0;
        }
    }

    if (gPlayer1Controller->buttonPressed & 0x200) {
        sp44--;
        if (sp44 < 0) {
            sp44 = arg0->unk_18 - 1;
        }
    }

    if (gPlayer1Controller->buttonPressed & 0x100) {
        sp44++;
        if (sp44 >= arg0->unk_18) {
            sp44 = 0;
        }
    }

    arg0->unk_00 = Gallery_GetGlobalIndex(arg0, sp44, sp40);
    if (arg0->unk_00 != sp48) {
        PlaySoundEffect(1);
    }

    if (gPlayer1Controller->buttonPressed & 0x8000) {
        sp3C = (arg0->unk_08 * arg0->unk_14) + arg0->unk_00;
        sp38 = arg0->unk_20[sp3C];
        if (arg0->unk_04 == -1) {
            if (Cam_IsMonIndexDisplayable(sp38) != 0) {
                arg0->unk_04 = sp3C;
                arg0->unk_B0->unk_18 = sp38->unk_18;
                arg0->unk_B0->unk_00 = 0;
                PlaySoundEffect(2);
            } else {
                PlaySoundEffect(8);
            }
        } else {
            if ((arg0->unk_04 >= 0) && (arg0->unk_04 < arg0->unk_14)) {
                if (sp3C != arg0->unk_04) {
                    sp38->unk_00 = 0;
                    arg0->unk_20[arg0->unk_04]->unk_00 = 0;
                    Gallery_SwapEntries(sp38->unk_18, arg0->unk_B0->unk_18);
                    PlaySoundEffect(0x29);
                } else {
                    PlaySoundEffect(3);
                }
            } else {
                if (Gallery_IsEntryEqual(arg0->unk_B0->unk_18, sp38->unk_18) == 0) {
                    PlaySoundEffect(0x31);
                    gMenuStep = 4;

                    gSwapTempPokemon = *sp38->unk_18;
                    *sp38->unk_18 = *arg0->unk_B0->unk_18;

                    sp38->unk_00 = 0;
                } else {
                    PlaySoundEffect(3);
                    ResetMenuState();
                }
            }
            arg0->unk_04 = -1;
        }
    } else if (gPlayer1Controller->buttonPressed & 0x4000) {
        if (arg0->unk_04 == -1) {
            D_833032E0 = 0;
            gMenuStep = 1;
        } else {
            if (arg0->unk_04 >= 4) {
                GallerySelection_Init(&gGalleryMainSelection);
                D_833032E0 = 0;
                gMenuStep = 1;
            }
            arg0->unk_04 = -1;
        }
        PlaySoundEffect(3);
    } else if (gPlayer1Controller->buttonPressed & 4) {
        idx = (arg0->unk_08 * arg0->unk_14) + arg0->unk_00;
        if (arg0->unk_04 == -1) {
            sp28 = arg0->unk_20[idx];
        } else {
            sp28 = arg0->unk_B0;
        }

        if ((arg0->unk_04 == -1) && (Cam_IsMonIndexDisplayable(sp28) != 0)) {
            sp4C = 1;
            PlaySoundEffect(0x19);
            Gallery_SetCurrentEntry(sp28->unk_18);
        } else {
            PlaySoundEffect(8);
        }
    }

    return sp4C;
}

void Menu_DrawAnimatedSprite(u16* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, f32 arg5, f32 arg6) {
    s32 temp_fa0;
    s32 temp_fa0_2;
    s32 temp_fv1;
    s32 temp_fv1_2;
    s32 tmp = G_TX_NOMIRROR | G_TX_CLAMP;

    if ((arg5 == 0.0f) || (arg6 == 0.0f)) {
        return;
    }

    gDPLoadTextureTile(gDisplayListHead++, arg0, G_IM_FMT_RGBA, G_IM_SIZ_16b, arg3, 0, 0, 0, arg3, arg4 - 1, 0, tmp,
                       tmp, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

    temp_fv1 = ROUND_MAX(arg3 * arg5);
    temp_fa0 = ROUND_MAX(arg4 * arg6);
    temp_fv1_2 = ROUND_MAX(arg3 * (arg5 - 1.0f) * 0.5f);
    temp_fv1_2 = -temp_fv1_2;
    temp_fa0_2 = ROUND_MAX(arg4 * (arg6 - 1.0f) * 0.5f);

    Gfx_DrawTextureRect(arg1 + temp_fv1_2, arg2 - temp_fa0_2, temp_fv1, temp_fa0, 0, 0, 1024.0f / arg5, 1024.0f / arg6, 0);
}

void DrawMenuScreen(void) {
    static s16 gBackgroundAnimPhase = 0;
    static s16 gBackgroundAnimOffset = 0x3200;

    f32 temp_fs0;
    f32 temp_fs1;
    s32 temp_s2;
    s32 temp_t0;
    char* temp_v0_4;
    s32 i;
    u8 tmp;
    u8 tmp2;
    u8 r;

    temp_fs0 = (SINS(gBackgroundAnimPhase) * 0.2f) + 1.0f;
    temp_fs1 = (SINS(gBackgroundAnimPhase + gBackgroundAnimOffset) * 0.2f) + 1.0f;

    gBackgroundAnimPhase += 0x2000;

    for (i = 0; i < 7; i++) {
        tmp = (D_833031B4[i].unk_12 == 0) ? 0xFF : 0x40;

        if (D_833031B4[i].unk_10 == 1) {
            DrawPanelFrame(0x46, 0x4E + i * 0x36, 0x7F, 0x18, 0x1E, 0x1E, 0x82, tmp);
        } else {
            DrawPanelFrame(0x46, 0x4E + i * 0x36, 0x7F, 0x18, 0x1E, 0x64, 0x1E, tmp);
        }
    }

    DrawSelectionHighlight(GetActiveMenu());

    gSPDisplayList(gDisplayListHead++, gPrefDL_Border);

    for (i = 0; i < 7; i++) {
        temp_t0 = -D_833031B4[i].unk_04 + 0xC;

        if (D_833031B4[i].unk_12 == 0) {
            r = 0xFF;
        } else {
            r = 0x40;
        }

        if (D_833031B4[i].unk_00 != NULL) {
            gDPPipeSync(gDisplayListHead++);

            gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, r);

            if ((i == D_83402E28) && (D_833031B4[i].unk_12 == 0)) {
                Menu_DrawAnimatedSprite(D_833031B4[i].unk_00, temp_t0 + 0x46, (i * 0x36) + 0x48, D_833031B4[i].unk_04,
                              D_833031B4[i].unk_06, temp_fs0, temp_fs1);
            } else {
                DrawVerticalTextureStrip(D_833031B4[i].unk_00, temp_t0 + 0x46, (i * 0x36) + 0x48, D_833031B4[i].unk_04,
                              D_833031B4[i].unk_06, 0);
            }
        }
    }

    Text_ResetState();
    Text_SetFont(8, 0);

    for (i = 0; i < 7; i++) {
        temp_v0_4 = Text_GetMessageString_Bank2C(D_833031B4[i].unk_08);
        temp_s2 = ((0x73 - MeasureTextWidth(0, 0, temp_v0_4)) / 2) + 0xC;
        tmp2 = (D_833031B4[i].unk_12 == 0) ? 0xFFu : 0x40u;

        Text_SetEnvColor(0xFF, 0xFF, 0xFF, tmp2);
        Text_Print(temp_s2 + 0x46, 0x50 + i * 0x36, temp_v0_4);
    }

    Text_SetupDL();
}

void DrawSubPanel(s32 arg0, s32 arg1, s32 arg2) {
    s32 sp3C;
    UNUSED s32 pad;
    char* sp34;
    Color_RGBA8 sp30 = { 0x9A, 0x37, 0x54, 0xFF };
    Color_RGBA8 sp2C = { 0xC3, 0x54, 0x84, 0xFF };
    MenuSubPanelItem* sp20;

    DrawPanelWithTextures(arg0, arg1, 0x186, &sp30, &sp2C);

    if ((D_833032E0 != 0) && (D_833032E0 != 2)) {
        sp20 = &gSubPanelItems[arg2];
    } else if (gGallerySpecialUnlocked == 0) {
        sp20 = &gSubPanelItems[arg2];
        do {
            sp20->unk_00 = D_3004540;
        } while (0);
    } else {
        sp20 = &gSubPanelItems[arg2];
        sp20->unk_00 = D_3005260;
    }

    if (sp20->unk_00 != NULL) {
        gSPDisplayList(gDisplayListHead++, gPrefDL_Border);

        DrawVerticalTextureStrip(sp20->unk_00, arg0 + 0x10, arg1 - 1, sp20->unk_04, sp20->unk_06, 0);
    }

    Text_ResetState();
    Text_SetFont(0x10, 0);
    sp34 = Text_GetMessageString_Bank2C(sp20->unk_08);
    sp3C = (0x186 - MeasureTextWidth(0, 0, sp34)) / 2;
    Text_SetEnvColor(0, 0, 0, 0xFF);
    Text_Print(arg0 + sp3C + 2, arg1 + 5, sp34);
    Text_SetEnvColor(0xFF, 0xFF, 0x77, 0xFF);
    Text_Print(arg0 + sp3C, arg1 + 3, sp34);
    Text_SetupDL();
}

void DrawMessageBox(unk_D_83407B38* arg0, s32 arg1, s32 arg2) {
    MenuItem* temp_v1 = &D_833031B4[D_83402E28];
    char* sp18 = NULL;

    switch (D_833032E0) {
        case 0:
            if (gMenuStep == 5) {
                switch (gMenuConfirmState) {
                    case 0:
                        if (gGallerySpecialViewed == 0) {
                            sp18 = Text_GetMessageString_Bank2C(0x1B);
                        } else {
                            sp18 = Text_GetMessageString_Bank2C(0x45);
                        }
                        break;

                    case 1:
                        sp18 = Text_GetMessageString_Bank2C(0x1D);
                }
                break;
            } else if ((gMenuDirty != 0) && (temp_v1->unk_0C != NULL)) {
                sp18 = Text_GetMessageString_Bank2C(temp_v1->unk_0C[temp_v1->unk_12 - 1]);
            } else {
                sp18 = Text_GetMessageString_Bank2C(temp_v1->unk_0A);
            }
            break;

        case 1:
            if (gMenuStep == 4) {
                sp18 = Text_GetMessageString_Bank2C(0x17);
            } else {
                sp18 = Text_GetMessageString_Bank2C(0x16);
            }
            break;

        case 2:
            if (arg0->unk_04 == -1) {
                sp18 = Text_GetMessageString_Bank2C(0x19);
            } else {
                sp18 = Text_GetMessageString_Bank2C(0x1A);
            }
            break;
    }

    Gallery_DrawGradientPanel(arg1, arg2, 0x186, 0x4C);

    if (sp18 != NULL) {
        if (1) {}
        if (1) {}
        if (1) {}
        Text_ResetState();
        Text_SetFont(8, 0);
        Text_SetLineHeight(0x14);
        Text_Print(arg1 + 0xA, arg2 + 8, sp18);
        Text_SetupDL();
    }
}

void InitializeMenuState(s32 arg0, s32 arg1) {
    unk_D_83407B38* temp_v0_2;
    AssetManager* sp30;

    switch (arg0) {
        case 1:
            D_833032E0 = 1;
            break;

        case 2:
            D_833032E0 = 2;
            break;

        default:
            D_833032E0 = 0;
            break;
    }

    gMenuStep = 0;
    gBackgroundFadeTimer = -1;
    gMenuDirty = 0;
    gMenuConfirmState = 0;
    gMenuInputLocked = 0;

    if (arg1 == 0) {
        gGallerySpecialViewed = 0;
    } else {
        gGallerySpecialViewed = 1;
        gMenuInputLocked = 1;
    }

    if (IsStickerStationConnected() != 0) {
        gStickerStationConnected = 1;
    } else {
        gStickerStationConnected = 0;
    }

    Gallery_Reset();
    UpdateMenuItemStates();
    Graph_InitRoots();
    sp30 = AssetManager_Create(5);
    CamList_Init(&gMenuActiveData, 0x3C, 0x2D, 4, 2, sp30, gMenuAssetArchive, gCurrentCamEntry, 4, 1);
    Gallery_UpdateCameraAssets(&gGalleryCamList, sp30, gMenuAssetArchive);

    if (D_833032E0 == 1) {
        temp_v0_2 = GetActiveMenu();
        temp_v0_2->unk_04 = 0x400;
        temp_v0_2->unk_B0->unk_18 = &gGalleryEntries[gGalleryMainSelection.unk_04];
        temp_v0_2->unk_B0->unk_00 = 0;
    } else if (D_833032E0 == 2) {
        Gallery_SyncCamToSelection(&gMenuActiveData, &gGalleryMainSelectionCam);
        Gallery_SyncCamToSelection(&gGalleryCamList, &gGallerySubSelection);
    }

    SnapSelect_SetupDisplay();
}

void Gfx_DrawFadeOverlay(s32 arg0, s32 arg1, s32 arg2, s32 arg3, Color_RGBA8* arg4, Color_RGBA8* arg5) {
    FramebufferImage* temp_s1 = Gfx_GetCurrentFramebuffer();
    Vtx* temp_s2 = GfxAlloc(sizeof(Vtx) * 4);
    Mtx* sp84 = GfxAlloc(sizeof(Mtx) * 1);
    Vp* sp80 = GfxAlloc(sizeof(Vp) * 1);

    SetViewport(sp80, temp_s1->width, temp_s1->height);

    gSPViewport(gDisplayListHead++, (u32)sp80 & 0x1FFFFFFF);

    guOrtho(sp84, 0.5f, temp_s1->width - 0.5f, temp_s1->height - 0.5f, 0.5f, -2.0f, 2.0f, 1.0f);
    SetTileVertex(&temp_s2[0], arg0, arg1, -1, 0, 0, arg4->r, arg4->g, arg4->b, arg4->a);
    SetTileVertex(&temp_s2[1], arg0 + arg2, arg1, -1, 0, 0, arg5->r, arg5->g, arg5->b, arg5->a);
    SetTileVertex(&temp_s2[2], arg0, arg1 + arg3, -1, 0, 0, arg4->r, arg4->g, arg4->b, arg4->a);
    SetTileVertex(&temp_s2[3], arg0 + arg2, arg1 + arg3, -1, 0, 0, arg5->r, arg5->g, arg5->b, arg5->a);

    gDPPipeSync(gDisplayListHead++);
    gDPSetCycleType(gDisplayListHead++, G_CYC_1CYCLE);
    gSPClearGeometryMode(gDisplayListHead++, G_ZBUFFER | G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN |
                                                 G_TEXTURE_GEN_LINEAR | G_LOD | G_SHADING_SMOOTH);
    gSPSetGeometryMode(gDisplayListHead++, G_SHADE | G_CULL_BACK | G_SHADING_SMOOTH);
    gDPSetCombineMode(gDisplayListHead++, G_CC_SHADE, G_CC_SHADE);
    gDPSetRenderMode(gDisplayListHead++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
    gSPPerspNormalize(gDisplayListHead++, 0xFFFF);
    gSPMatrix(gDisplayListHead++, (u32)sp84 & 0x1FFFFFFF, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
    gSPMatrix(gDisplayListHead++, (u32)&gCamProjectionMatrix & 0x1FFFFFFF, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPVertex(gDisplayListHead++, (u32)temp_s2 & 0x1FFFFFFF, 4, 0);
    gSP2Triangles(gDisplayListHead++, 0, 2, 3, 0, 0, 3, 1, 0);
}

void DrawBackground(void) {
    static Color_RGBA8 D_83303298 = { 0, 0, 0, 0xFF };
    static Color_RGBA8 D_8330329C = { 0, 0, 0, 0 };
    static s32 gBackgroundStartX = 0xBE;
    static s32 gBackgroundEndX = 0xFA;

    s32 var_ra;
    Color_RGBA8 sp80 = D_83303298;
    Color_RGBA8 sp7C = D_8330329C;

    if (gBackgroundFadeTimer > 0) {
        gBackgroundFadeTimer--;
    }

    if (gBackgroundFadeTimer == 0) {
        var_ra = 0x12C;
    } else {
        var_ra = 0x280;
    }

    gSPDisplayList(gDisplayListHead++, gPrefDL_Border);
    gDPSetCombineLERP(gDisplayListHead++, ENVIRONMENT, PRIMITIVE, TEXEL0, PRIMITIVE, 0, 0, 0, TEXEL0, ENVIRONMENT,
                      PRIMITIVE, TEXEL0, PRIMITIVE, 0, 0, 0, TEXEL0);
    gDPSetRenderMode(gDisplayListHead++, G_RM_OPA_SURF, G_RM_OPA_SURF2);
    gDPSetPrimColor(gDisplayListHead++, 0, 0, 40, 40, 55, 255);
    gDPSetEnvColor(gDisplayListHead++, 150, 95, 110, 255);

    gDPLoadTextureBlock_4b(gDisplayListHead++, D_3000000, G_IM_FMT_I, 128, 64, 0, G_TX_NOMIRROR | G_TX_WRAP,
                           G_TX_NOMIRROR | G_TX_WRAP, 7, 6, G_TX_NOLOD, G_TX_NOLOD);

    Gfx_DrawTextureRect(gBackgroundStartX, 0, var_ra - gBackgroundStartX, 0x1E0, 0, 0, 0x400, 0x400, 0);

    gSPDisplayList(gDisplayListHead++, gPrefDL_End);
    gSPDisplayList(gDisplayListHead++, gDL_FillCycle);
    gDPSetFillColor(gDisplayListHead++, 0x00000001);
    gDPFillRectangle(gDisplayListHead++, 0, 0, gBackgroundStartX - 1, 479);
    gSPDisplayList(gDisplayListHead++, gPrefDL_End);

    Gfx_DrawFadeOverlay(gBackgroundStartX, 0, gBackgroundEndX - gBackgroundStartX, 0x1E0, &sp80, &sp7C);
}

void DrawPokemonGrid(unk_D_83407B38* arg0) {
    s32 temp_fp;
    s32 temp_s4;
    s32 temp_s5;
    s32 temp_s0;
    s32 sp8C;
    s32 var_s6;
    Camera* temp_s1;
    s32 i;
    s32 j;
    s32 sp78;
    s32 sp74;
    UNUSED s32 pad[2];
    s32 sp68;
    s32 sp64;
    s32 tmp1;
    s32 tmp2;

    temp_fp = gGridOffsetX[gGallerySpecialUnlocked];
    temp_s4 = gGridStepX[gGallerySpecialUnlocked];
    temp_s5 = gGridStepY[gGallerySpecialUnlocked];
    sp8C = gGridOffsetY[gGallerySpecialUnlocked];

    if (gGallerySpecialUnlocked == 0) {
        var_s6 = 4;
    } else {
        var_s6 = 1;
    }

    for (i = 0; i < arg0->unk_14; i++) {
        temp_s0 = (arg0->unk_08 * arg0->unk_14) + i;
        Gallery_GetPageAndIndex(arg0, &sp78, &sp74, i);
        temp_s1 = arg0->unk_20[temp_s0];

        if ((i != arg0->unk_04) && (Cam_IsMonIndexDisplayable(temp_s1) != 0) && (temp_s1->unk_00 == 2)) {
            for (j = 0; j < var_s6; j++) {
                Gallery_DrawTextureList(temp_s1->unk_08->img_p, (temp_s4 * sp78) + temp_fp + ((temp_s4 / 2) * (j % 2)),
                              (temp_s5 * sp74) + sp8C + ((temp_s5 / 2) * (j / 2)), temp_s1->unk_04, temp_s1->unk_06, 8,
                              1);
            }
        }
    }

    if (arg0->unk_04 != -1) {
        Gallery_GetPageAndIndex(arg0, &sp68, &sp64, arg0->unk_00);
        temp_s1 = arg0->unk_B0;
        if ((Cam_IsMonIndexDisplayable(temp_s1) != 0) && (temp_s1->unk_00 == 2)) {
            for (j = 0; j < var_s6; j++) {
                tmp1 = j % 2;
                tmp2 = j / 2;
                Gallery_DrawShadow((temp_s4 * sp68) + temp_fp + ((temp_s4 / 2) * tmp1),
                              (temp_s5 * sp64) + sp8C + ((temp_s5 / 2) * tmp2), temp_s1->unk_04, temp_s1->unk_06);

                Gallery_DrawTextureList(temp_s1->unk_08->img_p, ((temp_s4 * sp68) + temp_fp + ((temp_s4 / 2) * tmp1)) - 0x10,
                              ((temp_s5 * sp64) + sp8C + ((temp_s5 / 2) * tmp2)) - 0x10, temp_s1->unk_04,
                              temp_s1->unk_06, 8, 1);
            }
        }
    }
}

void DrawSelectionHighlight(unk_D_83407B38* arg0) {
    Camera* temp_s0;
    s32 sp58;
    s32 sp54;
    s32 sp50;
    s32 sp4C;
    s32 sp48;
    s32 sp44;
    s32 var_a2;
    s32 var_a3;
    s32 var_v0;

    sp50 = gGridOffsetX[gGallerySpecialUnlocked];
    sp4C = gGridOffsetY[gGallerySpecialUnlocked];
    sp48 = gGridStepX[gGallerySpecialUnlocked];
    sp44 = gGridStepY[gGallerySpecialUnlocked];
    temp_s0 = arg0->unk_B0;
    Gallery_GetPageAndIndex(arg0, &sp58, &sp54, arg0->unk_00);

    switch (D_833032E0) {
        case 0:
            gSPDisplayList(gDisplayListHead++, gPrefDL_Border);
            Gallery_DrawAnimatedCorners(0x3E, (D_83402E28 * 0x36) + 0x46, 0x8F, 0x28);
            break;

        case 2:
            gSPDisplayList(gDisplayListHead++, gPrefDL_Border);

            if (arg0->unk_04 == -1) {
                var_v0 = 0;
            } else {
                var_v0 = -0x10;
            }

            if (gGallerySpecialUnlocked == 0) {
                var_a2 = (temp_s0->unk_04 * 2) + 0x18;
                var_a3 = (temp_s0->unk_06 * 2) + 0x18;
            } else {
                var_a2 = temp_s0->unk_04 + 8;
                var_a3 = temp_s0->unk_06 + 8;
            }
            Gallery_DrawAnimatedCorners(((sp48 * sp58) + sp50 + var_v0) - 4, ((sp44 * sp54) + sp4C + var_v0) - 4, var_a2, var_a3);
            break;

        case 1:
            if ((arg0->unk_04 != -1) && (Cam_IsMonIndexDisplayable(temp_s0) != 0) && (temp_s0->unk_00 == 2)) {
                gSPDisplayList(gDisplayListHead++, gPrefDL_Border);

                if (gGallerySpecialUnlocked == 0) {
                    var_a2 = (temp_s0->unk_04 * 2) + 0x18;
                    var_a3 = (temp_s0->unk_06 * 2) + 0x18;
                } else {
                    var_a2 = temp_s0->unk_04 + 8;
                    var_a3 = temp_s0->unk_06 + 8;
                }
                Gallery_DrawAnimatedCorners(((sp48 * sp58) + sp50) - 0x14, ((sp44 * sp54) + sp4C) - 0x14, var_a2, var_a3);
            }
            break;
    }
}

void Menu_DrawHeader(s32 arg0) {
    s8* sp2C;
    s32 temp_v1;

    sp2C = Text_GetMessageString_Bank2C(0x3C);
    temp_v1 = ((0x186 - MeasureTextWidth(0, 0, sp2C)) / 2) + 0xD5;

    gSPDisplayList(gDisplayListHead++, gPrefDL_Border);

    Gfx_DrawSpriteRGBA16(temp_v1 - 0x20, arg0 - 2, 0x18, 0x18, D_30099B8, 0x18, 0);
    Text_ResetState();
    Text_SetFont(8, 0);
    Text_SetEnvColor(0xFF, 0xFF, 0xFF, 0xFF);
    Text_Print(temp_v1, arg0, sp2C);
    Text_SetupDL();
}

void RenderFrame(void) {
    UNUSED s32 pad;
    unk_D_83407B38* sp18 = GetActiveMenu();

    Stage_BeginDisplayList();
    DrawBackground();
    DrawSubPanel(0xD5, 0x24, D_833032E0);
    DrawPokemonGrid(sp18);
    DrawMenuScreen();

    if ((D_833032E0 == 2) && (sp18->unk_04 == -1)) {
        Menu_DrawHeader(0x158);
    }

    DrawMessageBox(sp18, 0xD5, 0x172);
    SnapSelect_UpdateUIState(1);
    Stage_Advance();
}

void Menu_HandleSwapInput(unk_D_83407B38* arg0) {
    s32 var_a2 = 0;
    s32 idx = (arg0->unk_08 * arg0->unk_14) + arg0->unk_00;
    Camera* temp_v1 = arg0->unk_20[idx];

    if (gPlayer1Controller->buttonPressed & 0x8000) {
        PlaySoundEffect(0x29);
        var_a2 = 1;
        UpdateMenuItemStates();
    } else if (gPlayer1Controller->buttonPressed & 0x4000) {
        *temp_v1->unk_18 = gSwapTempPokemon;
        temp_v1->unk_00 = 0;
        PlaySoundEffect(3);
        var_a2 = 1;
    }

    if (var_a2 != 0) {
        ResetMenuState();
    }
}

void Menu_HandleConfirmTimer(void) {
    static s32 gConfirmTimer = 0;

    if (gMenuDirty != 0) {
        if (gConfirmTimer > 0) {
            gConfirmTimer--;
            if (gConfirmTimer == 0) {
                gMenuConfirmState = 1;
                PlaySoundEffect(8);
            }
        }
    }

    if (gConfirmTimer <= 0) {
        if (gPlayer1Controller->buttonPressed & 0x8000) {
            PlaySoundEffect(0x1C);
            Gallery_SaveChanges(1, gStickerStationConnected);
            if (gStickerStationConnected != 0) {
                StickerStation_SetCommand(0x5A);
            }
            gMenuDirty = 1;
            gConfirmTimer = 4;
        } else if (gPlayer1Controller->buttonPressed & 0x4000) {
            PlaySoundEffect(3);
            gMenuStep = 1;
            gMenuDirty = 0;
            gMenuConfirmState = 0;
        }
    }
}

void Menu_ProcessResult(void) {
    s16 temp_v0;
    s32 var_a2;

    temp_v0 = SnapSelect_GetResultCode(3);
    if (temp_v0 != -1) {
        var_a2 = 0;
        if (temp_v0 == -2) {
            temp_v0 = 2;
        }

        switch (temp_v0) {
            case 0:
                gMenuStep = 7;
                Menu_SetStep(4, gPlayer1Controller);
                var_a2 = 0;
                gFadeOutTimer = 6;
                break;

            case 1:
                var_a2 = 1;
                break;

            default:
                gMenuStep = 1;
                break;
        }

        if (var_a2 != 0) {
            gMenuStep = 8;
            Stage_SetFillColor(0xFFFF);
            Stage_FadeOut(0xF);
            if (gMenuExitFadeColors[D_83402E28] == 8) {
                Stage_SetFadeColor(0xF);
            }
        }
    }
}

void Menu_FadeOutStep(void) {
    gFadeOutTimer--;
    if (gFadeOutTimer <= 0) {
        Menu_ExitToGallery(4);
        Gallery_SaveChanges(0, gStickerStationConnected);
        gMenuStep = 8;
        Stage_SetFillColor(0xFFFF);
        Stage_FadeOut(0xF);
        if (gMenuExitFadeColors[D_83402E28] == 8) {
            Stage_SetFadeColor(0xF);
        }
    }
}

s32 Menu_MainLoopStep(void) {
    static s32 gInitialDelayCounter = 2;

    s32 temp_v0_2;
    s32 sp28;
    s32 sp24;
    s32 sp20;
    MenuItem* sp1C;
    s32 sp18;

    sp28 = 1;
    sp24 = gMenuStep;
    sp20 = gGallerySpecialUnlocked;
    sp1C = &D_833031B4[D_83402E28];

    switch (gMenuStep) {
        case 0:
            if (Stage_GetFadeState() == 0) {
                gInitialDelayCounter--;
                if (gInitialDelayCounter <= 0) {
                    switch (D_833032E0) {
                        case 0:
                            if (gGallerySpecialViewed != 0) {
                                if (sp1C->unk_12 == 0) {
                                    gMenuStep = 5;
                                    gMenuConfirmState = 0;
                                } else {
                                    gMenuStep = 1;
                                    gMenuDirty = 1;
                                    PlaySoundEffect(8);
                                }
                            } else {
                                gMenuStep = 1;
                            }
                            break;

                        case 1:
                            gMenuStep = 2;
                            break;

                        case 2:
                            gMenuStep = 3;
                            break;
                    }
                }
            }
            break;

        case 1:
            temp_v0_2 = ProcessMenuInput();
            if (temp_v0_2 != 0) {
                gMenuStep = 8;
                if (temp_v0_2 == 2) {
                    Stage_SetFillColor(1);
                    sp18 = 8;
                } else {
                    sp18 = 0xF;
                    if (sp18) {}
                    Stage_SetFillColor(0xFFFF);
                }
                Stage_FadeOut(sp18);
                if (gMenuExitFadeColors[D_83402E28] == 8) {
                    Stage_SetFadeColor(sp18);
                }
            }

            if (gMenuStep != 1) {
                gBackgroundFadeTimer = -1;
            }
            break;

        case 2:
        case 3:
            if (HandlePokemonGridInput(GetActiveMenu()) != 0) {
                gMenuStep = 8;
                Stage_SetFillColor(1);
                Stage_FadeOut(1);
            }
            break;

        case 4:
            Menu_HandleSwapInput(GetActiveMenu());
            break;

        case 5:
            Menu_HandleConfirmTimer();
            break;

        case 6:
            Menu_ProcessResult();
            break;

        case 7:
            Menu_FadeOutStep();
            break;

        case 8:
            if (Stage_GetFadeState() == 1) {
                sp28 = 0;
            }
            break;
    }

    if (((sp24 != gMenuStep) && (gMenuStep == 1)) || (sp20 != gGallerySpecialUnlocked)) {
        gBackgroundFadeTimer = 4;
    }
    return sp28;
}

void Menu_PollInputs(void) {
    Cont_StartReadInputs();
    Cont_ReadInputs();
    MenuInput_Init();
}

void Menu_RunLoop(void) {
    s32 var_a0;

    if (D_833032E0 == 2) {
        var_a0 = 1;
    } else {
        var_a0 = 7;
    }
    Stage_FadeIn(var_a0);

    do {
        Menu_PollInputs();

        if ((Menu_IsExitPressed() != 0) && (gBackgroundFadeTimer == 0)) {
            gBackgroundFadeTimer = -1;
        }

        switch (gMenuStep) {
            case 0:
            case 8:
                break;

            default:
                CamList_Update(GetActiveMenu());
                break;
        }

        RenderFrame();
        Gallery_ClearActiveCamera();
    } while (Menu_MainLoopStep() != 0);
}

s32 Menu_GetResult(void) {
    s32 sp1C = gMenuExitFadeColors[D_83402E28];

    if (Gallery_GetCurrentEntry(0) != NULL) {
        sp1C = 4;
    }

    if (D_83402E28 == 2) {
        gGalleryMainSelection.unk_00 = 1;
    }

    Gallery_SyncSelectionToCam(&gMenuActiveData, &gGalleryMainSelectionCam);
    Gallery_SyncSelectionToCam(&gGalleryCamList, &gGallerySubSelection);

    return sp1C;
}

void Menu_InitializeAndRun(s32 arg0, s32 arg1) {
    Stage* sp24;

    main_pool_push_state('SNAP');

    Gfx_InitBuffers(0x20000, 0);
    sp24 = Stage_Create(1, 0, 2, 0, 2, 1);
    Text_Init(0x18, 0);

    ASSET_LOAD(D_1000000, common_menu1_ui, 0);
    ASSET_LOAD(D_3000000, gallery_ui, 0);
    ASSET_LOAD(D_5000000, snap_mode_ui, 0);

    FRAGMENT_LOAD(fragment31);

    AssetManager_LoadArchives();
    gMenuAssetArchive = ASSET_LOAD2(stadium_models, 1, 1);
    MessageBank_Init();
    Text_LoadMessageBanks();
    InitializeMenuState(arg0, arg1);
    Stage_Set(sp24);
    Menu_RunLoop();
    Stage_Destroy();
    FontManager_Free();
    Gfx_FreeBuffers();

    main_pool_pop_state('SNAP');

    Menu_GetResult();
}
