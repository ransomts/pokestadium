#include "fragment55.h"
#include "src/1AB70.h"
#include "src/1CF30.h"
#include "src/20330.h"
#include "src/20470.h"
#include "src/26820.h"
#include "src/2E110.h"
#include "src/3FB0.h"
#include "src/49790.h"
#include "src/controller.h"
#include "src/memory.h"
#include "src/stage_loader.h"

static s16 D_83003C80;
static s16 gMenuFadeTimer;
static u16 D_83003C84;
static BinArchive* gBattleAssetArchive;
static void* gBattleBackgroundAtlas;
static s16 gMenuBackgroundTimer;
static s16 gMenuFadeAlpha;
static s16 gLoadingBarProgress;
static s32 gCurrentBattleModeTitle;
static char* gCurrentBattleModeSubtitle;
static s16* gCurrentMenuOptionIds;
static s16 gCurrentMenuOptionCount;
static s16 gCurrentMenuSelectedIndex;
static char* gBattleModeTitle_Default;
static char* gBattleModeTitle_0;
static char* gBattleModeTitle_10;
static char* gBattleModeTitle_7;
static char* gBattleModeTitle_8;
static char* gBattleModeSubtitle_0;
static char* gBattleModeSubtitle_1;
static char* gBattleModeSubtitle_2;
static char* gBattleModeSubtitle_3;
static char* gBattleModeSubtitle_4;
static char* gBattleModeSubtitle_5;
static char* gBattleModeSubtitle_6;
static char* gBattleModeSubtitle_7;
static char* gBattleModeSubtitle_8;
unk_D_83003CE0 gMenuStaticStrings;
unk_D_83003CE0 gMenuOptionStrings;

char** D_830039C0 = NULL;
static char** gBattleModeMessageBank = NULL;
static u8 gBattleModeAssetIndices[] = {
    0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0F,
};
static s16 gMenuOptions_Mode1_S1[] = {
    0x0007, 0x0000, 0x0001, 0x0002, 0x0003, 0x0004, 0x0005, 0x0006, 0x0023, 0xFFFF,
};
static s16 gMenuOptions_Mode1_S10[] = {
    0x0007, 0x0000, 0x0001, 0x001D, 0x0003, 0x0004, 0x0005, 0x0009, 0x0023, 0xFFFF,
};
static s16 gMenuOptions_Mode1_S0[] = {
    0x0007, 0x0000, 0x0001, 0x0002, 0x0003, 0x0004, 0x0005, 0x0023, 0xFFFF, 0x0000,
};
static s16 gMenuOptions_Mode2_S2[] = {
    0x000B, 0x0000, 0x0001, 0x000A, 0x0004, 0x0005, 0x0006, 0x0023, 0xFFFF, 0x0000,
};
static s16 gMenuOptions_Mode2_S10[] = {
    0x000B, 0x0000, 0x0001, 0x001E, 0x0004, 0x0005, 0x0009, 0x0023, 0xFFFF, 0x0000,
};
static s16 gMenuOptions_Mode2_S0[] = {
    0x000B, 0x0000, 0x0001, 0x000A, 0x0004, 0x0005, 0x0023, 0xFFFF, 0x000E, 0x0000, 0x0001, 0x000C, 0x000D,
    0x0004, 0x0005, 0x0006, 0x0023, 0xFFFF, 0x000E, 0x0000, 0x0001, 0x001F, 0x000D, 0x0004, 0x0005, 0x0009,
    0x0023, 0xFFFF, 0x000E, 0x0000, 0x0001, 0x000C, 0x000D, 0x0004, 0x0005, 0x0023, 0xFFFF, 0x0000,
};
static s16 gMenuOptions_Mode4_S4[] = {
    0x0013, 0x0000, 0x0001, 0x000F, 0x0010, 0x0011, 0x0012, 0x0004, 0x0005, 0x0006, 0x0023, 0xFFFF,
};
static s16 gMenuOptions_Mode4_S10[] = {
    0x0013, 0x0000, 0x0001, 0x0020, 0x0010, 0x0011, 0x0012, 0x0004, 0x0005, 0x0009, 0x0023, 0xFFFF,
};
static s16 gMenuOptions_Mode4_S0[] = {
    0x0013, 0x0000, 0x0001, 0x000F, 0x0010, 0x0011, 0x0012, 0x0004, 0x0005, 0x0023, 0xFFFF, 0x0000,
};
static s16 gMenuOptions_Mode5_S5[] = {
    0x0000, 0x0001, 0x0016, 0x0017, 0x0004, 0x0005, 0x0006, 0x0023, 0xFFFF, 0x0000,
};
static s16 gMenuOptions_Mode5_S10[] = {
    0x0000, 0x0001, 0x0021, 0x0017, 0x0004, 0x0005, 0x0009, 0x0023, 0xFFFF, 0x0000,
};
static s16 gMenuOptions_Mode5_S0[] = {
    0x0000, 0x0001, 0x0016, 0x0017, 0x0004, 0x0005, 0x0023, 0xFFFF,
};
static s16 gMenuOptions_Mode6_S6[] = {
    0x0015, 0x0000, 0x0001, 0x0024, 0x0004, 0x0006, 0x0023, 0xFFFF,
};
static s16 gMenuOptions_Mode6_S10[] = {
    0x0015, 0x0000, 0x0001, 0x0014, 0x0004, 0x0009, 0x0023, 0xFFFF,
};
static s16 gMenuOptions_Mode6_S0[] = {
    0x0015, 0x0000, 0x0001, 0x0014, 0x0004, 0x0023, 0xFFFF, 0x0000,
};
static s16 gMenuOptions_Mode0_S0[] = {
    0x0015, 0x001A, 0x0014, 0x0025, 0x0022, 0x0026, 0x0023, 0xFFFF,
};
static s16 gMenuOptions_Mode7_S7[] = {
    0x0015, 0x0000, 0x0001, 0x0014, 0x0019, 0x0004, 0x0023, 0xFFFF,
};
static s16 gMenuOptions_Mode8_S8[] = {
    0x0015, 0x001C, 0x001B, 0x0014, 0x0023, 0xFFFF,
};

char* RentalRules_GetPokemonName(s32 arg0) {
    return Text_GetString(NULL, 0, gBattleModeMessageBank, arg0 - 1);
}

void RentalRules_LoadBackgroundArchive(void) {
    unk_func_80027FA0 sp20;

    if (gSessionContext.unk_0000 != 0xA) {
        gBattleAssetArchive = BinArchive_Open(backgrounds_ROM_START, battle_headers_ROM_START, 1, 1);
        if (gSessionContext.unk_0000 == 7) {
            Save_EnsureBankLoaded(2);
            Save_GetModeSettings(&sp20, gSessionContext.unk_11F2);
            if (sp20.unk_04 < 8) {
                gBattleBackgroundAtlas = BinArchive_GetFile(gBattleAssetArchive, 0xD);
            } else {
                gBattleBackgroundAtlas = BinArchive_GetFile(gBattleAssetArchive, 0x10);
            }
        } else {
            gBattleBackgroundAtlas = BinArchive_GetFile(gBattleAssetArchive, gBattleModeAssetIndices[gSessionContext.unk_0000]);
        }
    }
}

void RentalRules_PollInput(void) {
    Cont_StartReadInputs();
    Cont_ReadInputs();
    Input_ResetRepeatState();
}

s16* RentalRules_GetRuleIdList(unk_D_800AE540* arg0) {
    s16* var_v1 = NULL;

    switch (arg0->unk_0001) {
        case 1:
            switch (arg0->unk_0000) {
                case 1:
                    var_v1 = gMenuOptions_Mode1_S1;
                    break;
                case 10:
                    var_v1 = gMenuOptions_Mode1_S10;
                    break;
                case 0:
                    var_v1 = gMenuOptions_Mode1_S0;
                    break;
            }
            break;

        case 2:
            switch (arg0->unk_0000) {
                case 2:
                    var_v1 = gMenuOptions_Mode2_S2;
                    break;
                case 10:
                    var_v1 = gMenuOptions_Mode2_S10;
                    break;
                case 0:
                    var_v1 = gMenuOptions_Mode2_S0;
                    break;
            }
            break;

        case 3:
            switch (arg0->unk_0000) {
                case 3:
                    var_v1 = gMenuOptions_Mode1_S1;
                    break;
                case 10:
                    var_v1 = gMenuOptions_Mode1_S10;
                    break;
                case 0:
                    var_v1 = gMenuOptions_Mode1_S0;
                    break;
            }
            break;

        case 4:
            switch (arg0->unk_0000) {
                case 4:
                    var_v1 = gMenuOptions_Mode4_S4;
                    break;
                case 10:
                    var_v1 = gMenuOptions_Mode4_S10;
                    break;
                case 0:
                    var_v1 = gMenuOptions_Mode4_S0;
                    break;
            }
            break;

        case 5:
            switch (arg0->unk_0000) {
                case 5:
                    var_v1 = gMenuOptions_Mode5_S5;
                    break;
                case 10:
                    var_v1 = gMenuOptions_Mode5_S10;
                    break;
                case 0:
                    var_v1 = gMenuOptions_Mode5_S0;
                    break;
            }
            break;

        case 6:
            switch (arg0->unk_0000) {
                case 6:
                    var_v1 = gMenuOptions_Mode6_S6;
                    break;
                case 10:
                    var_v1 = gMenuOptions_Mode6_S10;
                    break;
                case 0:
                    var_v1 = gMenuOptions_Mode6_S0;
                    break;
            }
            break;

        case 0:
            switch (arg0->unk_0000) {
                case 0:
                    var_v1 = gMenuOptions_Mode0_S0;
                    break;
            }
            break;

        case 7:
            switch (arg0->unk_0000) {
                case 7:
                    var_v1 = gMenuOptions_Mode7_S7;
                    break;
            }
            break;

        case 8:
            switch (arg0->unk_0000) {
                case 8:
                    var_v1 = gMenuOptions_Mode8_S8;
                    break;
            }
            break;
    }

    return var_v1;
}

char* RentalRules_GetModeLabel(s8 arg0) {
    char* ret;

    switch (arg0) {
        case 0:
            ret = gBattleModeTitle_0;
            break;

        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
            ret = gBattleModeTitle_Default;
            break;

        case 7:
            ret = gBattleModeTitle_7;
            break;

        case 8:
            ret = gBattleModeTitle_8;
            break;

        case 10:
            ret = gBattleModeTitle_10;
            break;

        default:
            ret = NULL;
            break;
    }

    return ret;
}

char* RentalRules_GetCategoryLabel(s8 arg0) {
    char* ret;

    switch (arg0) {
        case 0:
            ret = gBattleModeSubtitle_0;
            break;

        case 1:
            ret = gBattleModeSubtitle_1;
            break;

        case 2:
            ret = gBattleModeSubtitle_2;
            break;

        case 3:
            ret = gBattleModeSubtitle_3;
            break;

        case 4:
            ret = gBattleModeSubtitle_4;
            break;

        case 5:
            ret = gBattleModeSubtitle_5;
            break;

        case 6:
            ret = gBattleModeSubtitle_6;
            break;

        case 7:
            ret = gBattleModeSubtitle_7;
            break;

        case 8:
            ret = gBattleModeSubtitle_8;
            break;

        default:
            ret = NULL;
            break;
    }

    return ret;
}

s32 RentalRules_RuleListHasEmptyEntry(s16* arg0) {
    s32 ret = 0;

    while (*arg0 != -1) {
        if (gMenuOptionStrings.unk_00[*arg0] == '\x00') {
            ret = 1;
            break;
        }
        arg0++;
    }

    return ret;
}

void RentalRules_UpdateFadeIn(void) {
    s32 temp_lo;

    gMenuFadeTimer--;

    gMenuFadeAlpha = temp_lo = ((0xA - gMenuFadeTimer) << 0xA) / 10;

    if (D_83003C84 & 4) {
        gLoadingBarProgress = temp_lo;
    }

    if (gMenuFadeTimer <= 0) {
        D_83003C80 = 1;
        gMenuBackgroundTimer = 2;
    }
}

void RentalRules_UpdateMainInput(void) {
    s16 tmp = gCurrentMenuSelectedIndex;

    if (BTN_IS_PRESSED(gPlayer1Controller, BTN_DUP)) {
        gCurrentMenuSelectedIndex--;
        if (gCurrentMenuSelectedIndex < 0) {
            gCurrentMenuSelectedIndex = gCurrentMenuOptionCount - 1;
        }
    }

    if (BTN_IS_PRESSED(gPlayer1Controller, BTN_DDOWN)) {
        gCurrentMenuSelectedIndex++;
        if (gCurrentMenuSelectedIndex >= gCurrentMenuOptionCount) {
            gCurrentMenuSelectedIndex = 0;
        }
    }

    if (gCurrentMenuSelectedIndex != tmp) {
        Audio_PlaySoundEffectById(1);
    }

    if (BTN_IS_PRESSED(gPlayer1Controller, BTN_A)) {
        D_83003C80 = 2;
        gMenuFadeTimer = 0;

        if (gMenuOptionStrings.unk_00[gCurrentMenuOptionIds[gCurrentMenuSelectedIndex]] != NULL) {
            RentalRules_PopupOpen(gCurrentMenuOptionIds[gCurrentMenuSelectedIndex]);
        } else {
            RentalRules_QualifyingSpeciesWindowOpen();
            Audio_PlaySoundEffectById(4);
        }

        Audio_PlaySoundEffectById(2);
    } else if (BTN_IS_PRESSED(gPlayer1Controller, BTN_B)) {
        D_83003C80 = 3;
        gMenuFadeTimer = 0xA;
        gMenuBackgroundTimer = -1;
        Audio_PlaySoundEffectById(3);
    }
}

void RentalRules_UpdateWaitPopupClose(void) {
    if ((RentalRules_PopupIsActive() == 0) && (RentalRules_QualifyingSpeciesWindowIsActive() == 0)) {
        D_83003C80 = 1;
    }
}

void RentalRules_UpdateFadeOut(void) {
    s32 temp_lo;

    gMenuFadeTimer--;
    temp_lo = (gMenuFadeTimer << 0xA) / 10;

    gMenuFadeAlpha = temp_lo;
    if (D_83003C84 & 4) {
        gLoadingBarProgress = temp_lo;
    }

    if (gMenuFadeTimer <= 0) {
        D_83003C80 = 4;
        gMenuFadeTimer = 2;
        gMenuBackgroundTimer = -1;
    }
}

s32 RentalRules_UpdateExitDelay(void) {
    s32 var_v1 = 0;

    gMenuFadeTimer--;
    if (gMenuFadeTimer <= 0) {
        var_v1 = 1;
    }
    return var_v1;
}

void RentalRules_DrawBackgroundFallback(void) {
    gDPPipeSync(gDisplayListHead++);

    gDPSetCycleType(gDisplayListHead++, G_CYC_1CYCLE);
    gDPSetTexturePersp(gDisplayListHead++, G_TP_NONE);
    gDPSetCombineLERP(gDisplayListHead++, ENVIRONMENT, PRIMITIVE, TEXEL0, PRIMITIVE, TEXEL0, 0, ENVIRONMENT, 0,
                      ENVIRONMENT, PRIMITIVE, TEXEL0, PRIMITIVE, TEXEL0, 0, ENVIRONMENT, 0);
    gDPSetRenderMode(gDisplayListHead++, G_RM_OPA_SURF, G_RM_OPA_SURF2);
    gDPSetEnvColor(gDisplayListHead++, 140, 190, 200, 255);
    gDPSetPrimColor(gDisplayListHead++, 0, 0, 110, 160, 170, 255);
    gSPClearGeometryMode(gDisplayListHead++, G_ZBUFFER | G_LIGHTING);

    gDPLoadTextureBlock_4b(gDisplayListHead++, D_302EBC0, G_IM_FMT_I, 128, 64, 0, G_TX_NOMIRROR | G_TX_WRAP,
                           G_TX_NOMIRROR | G_TX_WRAP, 7, 6, G_TX_NOLOD, G_TX_NOLOD);

    Gfx_DrawTexturedRectClipped(0, 0, 0x280, 0x1E0, 0, 0, 0x400, 0x400, 0);

    gSPDisplayList(gDisplayListHead++, gPrefDL_End);
}

void RentalRules_DrawHeaderBanner(void) {
    UNUSED s32 pad;
    s16 temp_s1;
    s16 spD8;

    if (gLoadingBarProgress == 0) {
        return;
    }

    temp_s1 = (((-gLoadingBarProgress * 0x10) + 0x4000) / 1024) + 0x28;
    spD8 = (gLoadingBarProgress << 5) / 1024;

    gSPDisplayList(gDisplayListHead++, gDL_XluBorder);
    gDPSetEnvColor(gDisplayListHead++, 100, 100, 200, 255);
    gDPSetPrimColor(gDisplayListHead++, 0, 0, 40, 40, 140, 255);

    gDPLoadTextureBlock(gDisplayListHead++, D_20003C0, G_IM_FMT_IA, G_IM_SIZ_8b, 16, 32, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

    Gfx_DrawTexturedRectClipped(0x38, temp_s1, 0x10, spD8, 0, 0, 0x3F0, 0x8000 / spD8, 0);

    gDPLoadTextureBlock(gDisplayListHead++, D_20005C0, G_IM_FMT_IA, G_IM_SIZ_8b, 16, 32, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

    Gfx_DrawTexturedRectClipped(0x240, temp_s1, 0x10, spD8, 0, 0, 0x400, 0x8000 / spD8, 0);
    Gfx_DrawTexturedRectClipped(0x48, temp_s1, 0x1F8, spD8, 0, 0, 0, 0x8000 / spD8, 0);

    if (gLoadingBarProgress < 0x400) {
        gSPDisplayList(gDisplayListHead++, gPrefDL_End);
    } else {
        gSPDisplayList(gDisplayListHead++, gPrefDL_Border);

        Gfx_DrawTextureRgba16(0x30, temp_s1 - 8, 0x30, 0x18, D_2006C00, 0x30, 0);
        Gfx_DrawTextureRgba16(0x30, temp_s1 + 0x10, 0x30, 0x18, D_2007500, 0x30, 0);

        gSPDisplayList(gDisplayListHead++, gPrefDL_End);

        Font_BeginTranslucentTextRendering();
        Font_SetActive(0x10, 0);

        if (gCurrentBattleModeTitle != 0) {
            char sp48[0x40];
            char* temp_v0_21;

            Text_SetEnvColor(0, 0, 0, 0xFF);
            Text_SetStringToken(0x26, gCurrentBattleModeTitle);
            temp_v0_21 = Text_GetString(sp48, sizeof(sp48), D_830039C0, 0);
            Font_Printf(0x6A, temp_s1 + 4, temp_v0_21);
            Text_SetEnvColor(0xFF, 0xFF, 0x77, 0xFF);
            Font_Printf(0x68, temp_s1 + 2, temp_v0_21);
        }

        Font_EndTexturedTextRendering();
    }
}

void RentalRules_DrawWindowFrame(s16 arg0, s16 arg1, s16 arg2, s16 arg3) {
    gSPDisplayList(gDisplayListHead++, gPrefDL_Border);

    Gfx_DrawTextureIa8(arg0 - 7, arg1 - 7, 8, 8, D_2000340, 8, 0);
    Gfx_DrawTextureIa8((arg0 + arg2) - 1, arg1 - 7, 8, 8, D_2000380, 8, 0);
    Gfx_DrawTexturedRectClipped(arg0 + 1, arg1 - 7, arg2 - 2, 8, 0, 0, 0, 0x400, 0);
    Gfx_DrawTextureIa8(arg0 - 7, (arg1 + arg3) - 1, 8, 8, D_20002C0, 8, 0);
    Gfx_DrawTexturedRectClipped(arg0 - 7, arg1 + 1, 8, arg3 - 2, 0, 0, 0x400, 0, 0);
    Gfx_DrawTextureIa8((arg0 + arg2) - 1, (arg1 + arg3) - 1, 8, 8, D_2000300, 8, 0);
    Gfx_DrawTexturedRectClipped(arg0 + 1, (arg1 + arg3) - 1, arg2 - 2, 8, 0, 0, 0, 0x400, 0);
    Gfx_DrawTexturedRectClipped((arg0 + arg2) - 1, arg1 + 1, 8, arg3 - 2, 0, 0, 0x400, 0, 0);

    gSPDisplayList(gDisplayListHead++, gPrefDL_End);
}

void RentalRules_DrawFilledPanel(s16 arg0, s16 arg1, s16 arg2, s16 arg3, u8 arg4, u8 arg5, u8 arg6) {
    gSPDisplayList(gDisplayListHead++, gPrefDL_Border);

    gDPSetRenderMode(gDisplayListHead++, G_RM_AA_OPA_SURF, G_RM_AA_OPA_SURF2);
    gDPSetEnvColor(gDisplayListHead++, arg4, arg5, arg6, 255);

    Gfx_DrawTextureIa8(arg0, arg1, 8, 8, D_2000B40, 8, 0);
    Gfx_DrawTextureIa8((arg0 + arg2) - 8, arg1, 8, 8, D_2000B80, 8, 0);
    Gfx_DrawTexturedRectClipped(arg0 + 8, arg1, arg2 - 0x10, 8, 0, 0, 0, 0x400, 0);
    Gfx_DrawTextureIa8(arg0, (arg1 + arg3) - 8, 8, 8, D_2000BC0, 8, 0);
    Gfx_DrawTexturedRectClipped(arg0, arg1 + 8, 8, arg3 - 0x10, 0, 0, 0x400, 0, 0);
    Gfx_DrawTextureIa8((arg0 + arg2) - 8, (arg1 + arg3) - 8, 8, 8, D_2000C00, 8, 0);
    Gfx_DrawTexturedRectClipped(arg0 + 8, (arg1 + arg3) - 8, arg2 - 0x10, 8, 0, 0, 0, 0x400, 0);
    Gfx_DrawTexturedRectClipped((arg0 + arg2) - 8, arg1 + 8, 8, arg3 - 0x10, 0, 0, 0x400, 0, 0);

    gSPDisplayList(gDisplayListHead++, gPrefDL_Fill);

    Gfx_FillRectRgba(arg0 + 8, arg1 + 8, arg2 - 0x10, arg3 - 0x10, arg4, arg5, arg6, 0xFF);

    gSPDisplayList(gDisplayListHead++, gPrefDL_End);
}

void RentalRules_DrawBulletIcon(s16 arg0, s16 arg1) {
    gDPLoadTextureTile(gDisplayListHead++, D_4000C40, G_IM_FMT_IA, G_IM_SIZ_8b, 20, 0, 0, 0, 19, 19, 0,
                       G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                       G_TX_NOLOD);

    Gfx_DrawTexturedRectClipped(arg0, arg1, 0x14, 0x14, 0, 0, 0x400, 0x400, 0);
}

void RentalRules_DrawRuleListText(s16 arg0, s16 arg1) {
    s16 tmp;
    s32 i;
    char sp48[0x40];

    Font_SetActive(0x10, 0);
    Text_SetEnvColor(0xFF, 0xFF, 0xFF, 0xFF);

    if (gCurrentBattleModeSubtitle != NULL) {
        if (gCurrentBattleModeSubtitle != gBattleModeSubtitle_0) {
            Text_SetStringToken(0x27, gCurrentBattleModeSubtitle);
            Font_Printf(arg0 + 0x10, arg1 + 4, Text_GetString(sp48, sizeof(sp48), D_830039C0, 1));
        } else {
            Font_Printf(arg0 + 0x10, arg1 + 4, gCurrentBattleModeSubtitle);
        }
    }

    Font_Printf(arg0 + 0x30, arg1 + 0x134, Text_GetString(NULL, 0, D_830039C0, 2));
    Font_SetActive(8, 0);

    for (i = 0; i < gCurrentMenuOptionCount; i++) {
        if (i != gCurrentMenuSelectedIndex) {
            Text_SetEnvColor(0xFF, 0xFF, 0xFF, 0xFF);
        } else {
            Text_SetEnvColor(0xFF, 0xFF, 0, 0xFF);
        }
        tmp = gCurrentMenuOptionIds[i];
        Font_Printf(arg0 + 0x54, arg1 + 0x26 + i * 0x18, gMenuStaticStrings.unk_00[tmp]);
    }
}

void RentalRules_DrawRuleListPanel(void) {
    static s16 D_83003B60 = 0;

    s32 i;
    s16 temp_s3;
    s16 temp_s2;

    if (gMenuFadeAlpha == 0) {
        return;
    }

    temp_s3 = (((-gMenuFadeAlpha * 0xA8) + 0x2A000) / 1024) + 0x5C;
    temp_s2 = (gMenuFadeAlpha * 0x150) / 1024;
    RentalRules_DrawWindowFrame(0x38, temp_s3, 0x210, temp_s2);

    if (gMenuFadeAlpha >= 0x400) {
        RentalRules_DrawFilledPanel(0x38, temp_s3, 0x210, 0x20, 0x3C, 0x3C, 0xA0);
        RentalRules_DrawFilledPanel(0x38, temp_s3 + 0x20, 0x210, 0x110, 0x1E, 0x1E, 0x64);
        RentalRules_DrawFilledPanel(0x38, temp_s3 + 0x130, 0x210, 0x20, 0x3C, 0x3C, 0xA0);
        if ((RentalRules_PopupGetProgress() == 0) && (RentalRules_GetQualifyingSpeciesDisplayOpeningProgress() == 0)) {
            s16 sins = SINS(D_83003B60) * 3.0f;

            Ui_DrawTextureMarker(sins + 0x48, temp_s3 + (gCurrentMenuSelectedIndex * 0x18) + 0x2A);
            D_83003B60 += 0x1000;
        }

        gSPDisplayList(gDisplayListHead++, gPrefDL_Border);

        Gfx_DrawTextureRgba16(0x48, temp_s3 + 0x132, 0x1C, 0x1C, D_04000000, 0x1C, 0);

        for (i = 0; i < gCurrentMenuOptionCount; i++) {
            RentalRules_DrawBulletIcon(0x74, temp_s3 + 0x28 + i * 0x18);
        }

        gSPDisplayList(gDisplayListHead++, gPrefDL_End);

        Font_BeginTranslucentTextRendering();
        RentalRules_DrawRuleListText(0x38, temp_s3);
        Font_EndTexturedTextRendering();
    }
}

void RentalRules_DrawFrame(void) {
    BgStage_DrawFrame();
    if (gMenuBackgroundTimer != 0) {
        if (gSessionContext.unk_0000 == 0xA) {
            RentalRules_DrawBackgroundFallback();
        } else {
            Gfx_DrawTiledRgba16Image(gBattleBackgroundAtlas);
        }

        RentalRules_DrawHeaderBanner();

        if (gMenuBackgroundTimer > 0) {
            gMenuBackgroundTimer--;
        }
    }

    if ((RentalRules_PopupGetProgress() < 0x400) && (RentalRules_GetQualifyingSpeciesDisplayOpeningProgress() < 0x400)) {
        RentalRules_DrawRuleListPanel();
    }

    RentalRules_PopupDraw();
    RentalRules_QualifyingSpeciesWindowDraw();
    BgStage_AdvanceFrame();
}

void RentalRules_LoadCategoryStrings(void) {
    s32 i;

    for (i = 0; i < 29; i++) {
        gMenuStaticStrings.unk_00[i] = Text_GetString(NULL, 0, D_830039C0, i + 4);
    }

    gMenuStaticStrings.unk_74 = gMenuStaticStrings.unk_00[2];
    gMenuStaticStrings.unk_78 = gMenuStaticStrings.unk_00[10];
    gMenuStaticStrings.unk_7C = gMenuStaticStrings.unk_00[12];
    gMenuStaticStrings.unk_80 = gMenuStaticStrings.unk_00[15];
    gMenuStaticStrings.unk_84 = gMenuStaticStrings.unk_00[22];
    gMenuStaticStrings.unk_88 = gMenuStaticStrings.unk_00[27];
    gMenuStaticStrings.unk_8C = Text_GetString(NULL, 0, D_830039C0, 0x21);
    gMenuStaticStrings.unk_90 = gMenuStaticStrings.unk_00[20];
    gMenuStaticStrings.unk_94 = gMenuStaticStrings.unk_00[4];
    gMenuStaticStrings.unk_98 = Text_GetString(NULL, 0, D_830039C0, 0x22);
}

void RentalRules_LoadDescriptionStrings(void) {
    s32 i;
    s32 var_s2 = 0;

    for (i = 0; i < 39; i++) {
        switch (i) {
            case 7:
            case 11:
            case 14:
            case 19:
            case 24:
                gMenuOptionStrings.unk_00[i] = NULL;
                break;

            default:
                gMenuOptionStrings.unk_00[i] = Text_GetString(NULL, 0, D_830039C0, var_s2 + 0x23);
                var_s2++;
                break;
        }
    }
}

void RentalRules_Init(void) {
    D_83003C80 = 0;
    gMenuFadeTimer = 0xA;
    gMenuBackgroundTimer = -1;
    gMenuFadeAlpha = 0;
    Audio_PlaySoundEffectById(4);
    gCurrentBattleModeTitle = 0;
    gCurrentBattleModeSubtitle = NULL;
    gCurrentMenuSelectedIndex = 0;
    D_83003C84 = 0;

    gCurrentMenuOptionIds = RentalRules_GetRuleIdList(&gSessionContext);
    if (gCurrentMenuOptionIds == 0) {
        gCurrentMenuOptionCount = 0;
    } else {
        gCurrentMenuOptionCount = 0;
        while (gCurrentMenuOptionIds[gCurrentMenuOptionCount] != -1) {
            gCurrentMenuOptionCount++;
        }
    }

    RentalRules_LoadCategoryStrings();
    RentalRules_LoadDescriptionStrings();

    gBattleModeTitle_Default = Text_GetString(NULL, 0, D_830039C0, 0x46);
    gBattleModeTitle_0 = Text_GetString(NULL, 0, D_830039C0, 0x45);
    gBattleModeTitle_10 = Text_GetString(NULL, 0, D_830039C0, 0x49);
    gBattleModeTitle_7 = Text_GetString(NULL, 0, D_830039C0, 0x47);
    gBattleModeTitle_8 = Text_GetString(NULL, 0, D_830039C0, 0x48);
    gBattleModeSubtitle_0 = Text_GetString(NULL, 0, D_830039C0, 0x4A);
    gBattleModeSubtitle_1 = Text_GetString(NULL, 0, D_830039C0, 0x4D);
    gBattleModeSubtitle_2 = Text_GetString(NULL, 0, D_830039C0, 0x4C);
    gBattleModeSubtitle_3 = Text_GetString(NULL, 0, D_830039C0, 0x4B);
    gBattleModeSubtitle_4 = Text_GetString(NULL, 0, D_830039C0, 0x4E);
    gBattleModeSubtitle_5 = Text_GetString(NULL, 0, D_830039C0, 0x4F);
    gBattleModeSubtitle_6 = Text_GetString(NULL, 0, D_830039C0, 0x50);

    gBattleModeSubtitle_7 = gBattleModeTitle_7;
    gBattleModeSubtitle_8 = gBattleModeTitle_8;

    gCurrentBattleModeTitle = RentalRules_GetModeLabel(gSessionContext.unk_0000);
    gCurrentBattleModeSubtitle = RentalRules_GetCategoryLabel(gSessionContext.unk_0001);

    if (gSessionContext.unk_11F2 != 0) {
        D_83003C84 |= 1;
    }

    if (RentalRules_RuleListHasEmptyEntry(gCurrentMenuOptionIds) != 0) {
        D_83003C84 |= 2;
    }

    if (D_83003C84 & 4) {
        gLoadingBarProgress = 0;
    } else {
        gLoadingBarProgress = 0x400;
    }

    RentalRules_PopupReset();

    RentalRules_QualifyingSpeciesWindowInit((D_83003C84 & 2) ? 1 : 0);
}

s32 RentalRules_Update(void) {
    s32 sp1C = 1;

    switch (D_83003C80) {
        case 0:
            RentalRules_UpdateFadeIn();
            break;

        case 1:
            RentalRules_UpdateMainInput();
            break;

        case 2:
            RentalRules_UpdateWaitPopupClose();
            break;

        case 3:
            RentalRules_UpdateFadeOut();
            break;

        case 4:
            if (RentalRules_UpdateExitDelay() != 0) {
                sp1C = 0;
            }
            break;
    }
    return sp1C;
}

void RentalRules_Loop(void) {
    RentalRules_Init();
    do {
        RentalRules_PollInput();
        RentalRules_PopupUpdate();
        RentalRules_QualifyingSpeciesWindowUpdate();
        RentalRules_DrawFrame();
    } while (RentalRules_Update() != 0);
}

s32 RentalRules_Main(UNUSED s32 arg0, UNUSED s32 arg1) {
    main_pool_push_state('EXPL');

    Font_Init(0x1C, 0);

    ASSET_LOAD(D_1000000, common_menu1_ui, 0);
    ASSET_LOAD(D_2000000, common_menu2_ui, 0);
    ASSET_LOAD(D_3000000, menu_select_ui, 0);
    ASSET_LOAD(D_04000000, rental_rules_ui, 0);

    RentalRules_LoadBackgroundArchive();
    PokeIcon_OpenModelArchive();
    Text_InitStringTables();
    D_830039C0 = Text_GetStringTable(0x20);
    gBattleModeMessageBank = Text_GetStringTable(0x24);
    StageLoader_UpdateSegments();
    RentalRules_Loop();
    StageLoader_WaitForRetrace();

    main_pool_pop_state('EXPL');

    return 0;
}
