#include "battle_prep.h"
#include "src/12D80.h"
#include "src/1C720.h"
#include "src/1CF30.h"
#include "src/20470.h"
#include "src/232C0.h"
#include "src/26820.h"
#include "src/29BA0.h"
#include "src/2C1C0.h"
#include "src/2E110.h"
#include "src/49790.h"
#include "src/4CBC0.h"
#include "src/6A40.h"
#include "src/6BC0.h"
#include "src/DDC0.h"
#include "src/F420.h"
#include "src/memory.h"
#include "src/stage_loader.h"

s32 BattlePrep_StarfieldGeoCallback(s32, unk_D_86002F34_alt8*);

unk_D_84B19910 gInputBuffer[400];
s32 pad_D_84B1A590[2];
unk_D_84B1A598 gBattleGraphics;
gBannerState gErrorScreenState;
gBadgeCarouselAnim gErrorScreenAnim;
BattleUiState gUIState;
gTeamIconsState gUIElementA;
gBadgeAwardState gUIElementB;
gStarBurstState gUIBarA;
gStarBurstState gUIBarB;
unk_D_84B26640 gBattleMenuState;
SessionModeSettings gBattleProgress;
char** gBattleMessageTable;

static u8* gTrainerIconTextures[] = {
    D_3015100,
    D_3015700,
    D_3015D00,
    D_3016300,
};
static u32 gGeoLayoutCommands[] = {
    0x0C000000, 0x05000000,    0x0B00002D, 0x00000000, 0x014000F0, 0x00000000,  0xFEDF0000,  0x00000121,  0x05000000,
    0x0D000000, 0x05000000,    0x0F000000, 0x05000000, 0x20050000, 0x00000000,  0x00000000,  0x00000000,  0x00000000,
    0x08000000, BattlePrep_StarfieldGeoCallback, gInputBuffer, 0x06000000, 0x0F000002, 0x05000000,  0x0A000000,  &gGraphRoot0, 0x06000000,
    0x06000000, 0x0D000001,    0x05000000, 0x0F000002, 0x05000000, 0x0A000000,  &gGraphRoot0, 0x06000000,  0x06000000,
    0x0D000002, 0x05000000,    0x0F000000, 0x05000000, 0x0A000000, &gGraphRoot0, 0x06000000,  0x06000000,  0x0D000003,
    0x05000000, 0x14000000,    0x002B0012, 0xFFFFFF32, 0x16FFFFFF, 0x0F000003,  0x05000000,  0x0A000000,  &gGraphRoot0,
    0x06000000, 0x06000000,    0x06000000, 0x06000000, 0x01000000,
};

void BattlePrep_SaveVictoryPalaceRecords(void) {
    s16 temp_s0;
    unk_D_800AE540_0874* temp_v0;
    PokemonData* var_s1;

    temp_v0 = gSessionContext.unk_1194[0].unk_08[0]->unk_214;
    temp_s0 = temp_v0->unk_002;
    var_s1 = temp_v0->unk_028;

    if ((gSessionContext.unk_0000 == 3) || (gSessionContext.unk_0000 == 6)) {
        if (gSessionContext.unk_0002 != 3) {
            return;
        }
    } else if ((gSessionContext.unk_0000 == 7) && (gSessionContext.unk_0002 != 9)) {
        return;
    }

    while (temp_s0-- > 0) {
        VictoryPalace_SaveSpeciesRecord(var_s1++, gSessionContext.unk_0000, gSessionContext.unk_11F2);
    }

    Save_CommitTypedRecord(0x13, 0);
}

void BattlePrep_MarkFirstClearBonus(void) {
    PlayerName sp20;
    s32 sp1C = 0;

    Save_GetOptions(&sp20);

    if ((gSessionContext.unk_0000 == 3) && (gSessionContext.unk_0002 == 3) && !(gBattleProgress.posX & 8)) {
        sp1C = 1;
    }

    if ((gSessionContext.unk_0000 == 6) && (gSessionContext.unk_0002 == 3) && !(gBattleProgress.posX & 0x40)) {
        sp1C = 1;
    }

    if ((sp1C != 0) && (sp20.posX < 2)) {
        sp20.posX++;
        Save_SetOptions(&sp20);
        if (sp20.posX == 1) {
            gSessionContext.unk_11F6 |= 8;
        } else {
            gSessionContext.unk_11F6 |= 0x10;
        }
    }
}

void BattlePrep_MarkCupCleared(void) {
    if (((gSessionContext.unk_0000 != 3) || (gSessionContext.unk_0002 >= 3)) &&
        ((gSessionContext.unk_0000 != 6) || (gSessionContext.unk_0002 >= 3)) &&
        ((gSessionContext.unk_0000 != 7) || (gSessionContext.unk_0002 >= 9))) {
        gBattleProgress.posX |= (1 << gSessionContext.unk_0000);
        if (gBattleProgress.posX == 0xF8) {
            gBattleProgress.unk_07 = 1;
            gSessionContext.unk_11F5 |= 4;
        }
        Save_SetModeSettings(&gBattleProgress, gSessionContext.unk_11F2);
    }
}

void BattlePrep_MarkNewRoundRecord(void) {
    if (gSessionContext.unk_0000 == 7) {
        if ((gSessionContext.unk_0002 >= gBattleProgress.rotation) && (gSessionContext.unk_0002 < 8)) {
            gBattleProgress.rotation = gSessionContext.unk_0002 + 1;
            gSessionContext.unk_11F6 |= 0x400;
        }
    } else if (gSessionContext.unk_0000 == 3) {
        if ((gSessionContext.unk_0002 >= gBattleProgress.unk_05) && (gSessionContext.unk_0002 < 4)) {
            gBattleProgress.unk_05 = gSessionContext.unk_0002 + 1;
            gSessionContext.unk_11F6 |= 0x400;
        }
    } else if ((gSessionContext.unk_0000 == 6) && (gSessionContext.unk_0002 >= gBattleProgress.unk_06) && (gSessionContext.unk_0002 < 4)) {
        gBattleProgress.unk_06 = gSessionContext.unk_0002 + 1;
        gSessionContext.unk_11F6 |= 0x400;
    }
    Save_SetModeSettings(&gBattleProgress, gSessionContext.unk_11F2);
}

char* BattlePrep_GetString(s32 arg0) {
    return Text_GetString(NULL, 0, gBattleMessageTable, arg0);
}

char* BattlePrep_FormatString(char* arg0, s32 arg1, u32 arg2) {
    return Text_GetString(arg0, arg1, gBattleMessageTable, arg2);
}

s32 BattlePrep_StarfieldGeoCallback(s32 arg0, unk_D_86002F34_alt8* arg1) {
    if (arg0 == 5) {
        BattlePrep_DrawStarfield(arg1->posX.unk_14);
        GeoRender_ApplyMaterialState();
    }
}

void BattlePrep_ResetDisplayObject(Fragment2_1GraphNode* arg0) {
    ModelRenderer_ClearDisplayObject(arg0);
    Vec3f_SetComponentsDuplicate(&arg0->unk_024, 0.0f, 0.0f, 0.0f);
    Vec3f_SetComponentsDuplicate(&arg0->unk_030, 1.0f, 1.0f, 1.0f);
    Vec3s_SetComponents(&arg0->unk_01E, 0, 0, 0);
}

void BattlePrep_ResetAllDisplayObjects(void) {
    s32 i;

    for (i = 0; i < 128; i++) {
        BattlePrep_ResetDisplayObject(&gBattleGraphics.unk_0008[i]);
    }
}

void BattlePrep_DrawCenteredText(s16 arg0, s16 arg1, char* arg2) {
    s32 sp1C = Font_MeasureTextExtent(2, 0, arg2);

    Font_BeginTranslucentTextRendering();
    Font_SetLineHeight(0xC);
    Font_SetActive(2, 0);
    Font_Printf(0x20 - (sp1C / 2), arg1, arg2);
    Font_EndTexturedTextRendering();
}

void BattlePrep_DrawBorderedRect(s16 arg0, s16 arg1, s16 arg2, s16 arg3, u8 arg4, u8 arg5, u8 arg6, u8 arg7) {
    s16 temp_a2;
    s16 temp_s0_32;
    s16 var_s2;
    s16 var_s3;

    if (arg2 >= 0x10) {
        var_s3 = 8;
    } else {
        var_s3 = arg2 / 2;
    }
    if (arg3 >= 0x10) {
        var_s2 = 8;
    } else {
        var_s2 = arg3 / 2;
    }
    temp_a2 = arg2 - (var_s3 * 2);
    temp_s0_32 = arg3 - (var_s2 * 2);

    gSPDisplayList(gDisplayListHead++, gPrefDL_Border);
    gDPSetEnvColor(gDisplayListHead++, arg4, arg5, arg6, arg7);

    gDPLoadTextureBlock_4b(gDisplayListHead++, D_3015080, G_IM_FMT_I, 16, 8, 0, G_TX_NOMIRROR | G_TX_WRAP,
                           G_TX_NOMIRROR | G_TX_WRAP, 5, 5, G_TX_NOLOD, G_TX_NOLOD);

    Gfx_DrawTexturedRectClipped(arg0, arg1, var_s3, var_s2, 0, 0, 0x2000 / var_s3, 0x2000 / var_s2, 0);

    gDPLoadTextureBlock_4b(gDisplayListHead++, D_30150C0, G_IM_FMT_I, 16, 8, 0, G_TX_NOMIRROR | G_TX_WRAP,
                           G_TX_NOMIRROR | G_TX_WRAP, 5, 5, G_TX_NOLOD, G_TX_NOLOD);

    Gfx_DrawTexturedRectClipped((arg0 + arg2) - var_s3, arg1, var_s3, var_s2, 0, 0, 0x2000 / var_s3, 0x2000 / var_s2, 0);

    gDPLoadTextureBlock_4b(gDisplayListHead++, D_3015000, G_IM_FMT_I, 16, 8, 0, G_TX_NOMIRROR | G_TX_WRAP,
                           G_TX_NOMIRROR | G_TX_WRAP, 5, 5, G_TX_NOLOD, G_TX_NOLOD);

    Gfx_DrawTexturedRectClipped(arg0, (arg1 + arg3) - var_s2, var_s3, var_s2, 0, 0, 0x2000 / var_s3, 0x2000 / var_s2, 0);

    gDPLoadTextureBlock_4b(gDisplayListHead++, D_3015040, G_IM_FMT_I, 16, 8, 0, G_TX_NOMIRROR | G_TX_WRAP,
                           G_TX_NOMIRROR | G_TX_WRAP, 5, 5, G_TX_NOLOD, G_TX_NOLOD);

    Gfx_DrawTexturedRectClipped((arg0 + arg2) - var_s3, (arg1 + arg3) - var_s2, var_s3, var_s2, 0, 0, 0x2000 / var_s3,
                  0x2000 / var_s2, 0);

    gSPDisplayList(gDisplayListHead++, gPrefDL_Fill);

    if ((temp_a2 > 0) && (temp_s0_32 > 0)) {
        Gfx_FillRectRgba(arg0 + var_s3, arg1, temp_a2, var_s2, arg4, arg5, arg6, arg7);
        Gfx_FillRectRgba(arg0, arg1 + var_s3, arg2, temp_s0_32, arg4, arg5, arg6, arg7);
        Gfx_FillRectRgba(arg0 + var_s3, arg1 + var_s3 + temp_s0_32, temp_a2, var_s2, arg4, arg5, arg6, arg7);
    } else if (temp_a2 > 0) {
        Gfx_FillRectRgba(arg0 + var_s3, arg1, temp_a2, arg3, arg4, arg5, arg6, arg7);
    } else if (temp_s0_32 > 0) {
        Gfx_FillRectRgba(arg0, arg1 + var_s2, arg2, temp_s0_32, arg4, arg5, arg6, arg7);
    }

    gSPDisplayList(gDisplayListHead++, gPrefDL_End);
}

void BattlePrep_DrawTrainerStatusIcon(FramebufferImage* arg0, s16 arg1, u8* arg2, u8* arg3) {
    BattlePokemon* temp_v1 = &gSessionContext.unk_1194[arg1];

    GfxImage_SetRenderTarget(&gDisplayListHead, arg0);

    gSPDisplayList(gDisplayListHead++, gTransferPakErrorBorderDL);

    Gfx_DrawTextureRgba16(0, 0, 0x40, 0x20, arg3, 0x40, 0x200000);
    Gfx_DrawTextureRgba16(0, 0x20, 0x40, 0x20, arg3 + 0x1000, 0x40, 0x200000);
    Gfx_DrawTextureRgba16(0, 0x40, 0x40, 0x20, arg3 + 0x2000, 0x40, 0x200000);
    Gfx_DrawTextureRgba16(4, 0x24, 0x38, 0x1C, arg2 + 0x208, 0x40, 0x200000);
    Gfx_DrawTextureRgba16(4, 0x40, 0x38, 0x1C, arg2 + 0x1008, 0x40, 0x200000);

    if (gSessionContext.unk_0000 == 0 || gSessionContext.unk_0000 == 9) {
        if (temp_v1->unk_08[0]->unk_000 & 2) {
            Gfx_DrawTextureRgba16(8, 4, 0x30, 0x10, &D_3016900, 0x30, 0x200000);
        } else if (temp_v1->unk_01 == 1) {
            Gfx_DrawTextureRgba16(8, 4, 0x30, 0x10, gTrainerIconTextures[temp_v1->unk_08[0]->unk_001], 0x30, 0x200000);
        } else {
            if (temp_v1->unk_08[0]->unk_001 < temp_v1->unk_08[1]->unk_001) {
                Gfx_DrawTextureRgba16(8, 4, 0x30, 0x10, gTrainerIconTextures[temp_v1->unk_08[0]->unk_001], 0x30, 0x200000);
                Gfx_DrawTextureRgba16(8, 0x14, 0x30, 0x10, gTrainerIconTextures[temp_v1->unk_08[1]->unk_001], 0x30, 0x200000);
            } else {
                Gfx_DrawTextureRgba16(8, 4, 0x30, 0x10, gTrainerIconTextures[temp_v1->unk_08[1]->unk_001], 0x30, 0x200000);
                Gfx_DrawTextureRgba16(8, 0x14, 0x30, 0x10, gTrainerIconTextures[temp_v1->unk_08[0]->unk_001], 0x30, 0x200000);
            }
        }

        gSPDisplayList(gDisplayListHead++, gPrefDL_End);
    } else if ((arg1 == 0) || (gSessionContext.unk_0000 == 0xA)) {
        Gfx_DrawTextureRgba16(8, 4, 0x30, 0x10, gTrainerIconTextures[temp_v1->unk_08[0]->unk_001], 0x30, 0x200000);

        gSPDisplayList(gDisplayListHead++, gPrefDL_End);

        BattlePrep_DrawCenteredText(arg1, 0x14, temp_v1->unk_08[0]->unk_214->unk_014);
    } else {
        gSPDisplayList(gDisplayListHead++, gPrefDL_End);

        BattlePrep_DrawCenteredText(arg1, 6, temp_v1->unk_08[0]->unk_214->unk_220);
    }
}

void BattlePrep_AnimateBallBurstEffect(s16 arg0) {
    static s16 D_84B0FC0C[] = {
        0x0300, 0x0150, 0xFEB0, 0xFD00, 0xFD00, 0xFEB0, 0x0150, 0x0300,
    };
    static f32 D_84B0FC1C[] = {
        -3.0f, -2.0f, 2.0f, 3.0f, -3.0f, -2.0f, 2.0f, 3.0f,
    };

    s32 i;

    if (arg0 < 0x10) {
        for (i = 0; i < 4; i++) {
            gBattleGraphics.unk_0008[i + 0].unk_024.y += 2.0f * arg0 * 0.5f;
            gBattleGraphics.unk_0008[i + 0].unk_01E.x += 0x300;
            gBattleGraphics.unk_0008[i + 8].unk_024.y += 2.0f * arg0 * 0.5f;
            gBattleGraphics.unk_0008[i + 8].unk_01E.x += 0x300;
            gBattleGraphics.unk_0008[i + 4].unk_01E.x -= 0x300;
            // clang-format off
            gBattleGraphics.unk_0008[i + 4].unk_024.y -= 2.0f * arg0 * 0.5f; gBattleGraphics.unk_0008[i + 12].unk_01E.x -= 0x300;
            // clang-format on
            gBattleGraphics.unk_0008[i + 12].unk_024.y -= 2.0f * arg0 * 0.5f;
        }

        for (i = 0; i < 8; i++) {
            gBattleGraphics.unk_0008[i + 0].unk_01E.z += D_84B0FC0C[i];
            gBattleGraphics.unk_0008[i + 8].unk_01E.z += D_84B0FC0C[i];

            gBattleGraphics.unk_0008[i + 0].unk_024.x += arg0 * D_84B0FC1C[i] * 0.5f;
            gBattleGraphics.unk_0008[i + 8].unk_024.x += arg0 * D_84B0FC1C[i] * 0.5f;
        }
    }
}

void BattlePrep_FadeInBallBurstObjects(s16 arg0) {
    s32 i;

    if (arg0 < 0x10) {
        for (i = 0; i < 16; i++) {
            gBattleGraphics.unk_0008[i].unk_01D = (-arg0 * 0x10) + 0xF0;
        }

        for (i = 28; i < 32; i++) {
            gBattleGraphics.unk_0008[i].unk_01D = (-arg0 * 0x10) + 0xF0;
        }
    }
}

void BattlePrep_RenderFrame(void) {
    BgStage_DrawFrame();
    GfxImage_FillCurrent(&gDisplayListHead, 1);
    Geo_RenderRootNode(gBattleGraphics.unk_0004);
    BattlePrep_DrawRuleWindow(&gBattleMenuState.unk_1C);
    BattlePrep_DrawRuleWindow(&gBattleMenuState.unk_28);
    BgStage_AdvanceFrame();
}

void BattlePrep_UpdateSingleBattleIntroFrame(void) {
    Controller_PollInputs();
    BattlePrep_UpdateStarfield(gInputBuffer);
    BattlePrepRoster_Update(&gUIState);
    BattlePrep_RenderFrame();
}

s32 BattlePrep_ShowSingleBattleIntro(void) {
    s32 i;
    s32 var_s1 = 0;

    Team_LoadOpponentPreset();
    BattlePrepRoster_Init(&gUIState, gBattleGraphics.unk_0004->unk_0C);
    BattlePrepRoster_Load(&gUIState, gBattleGraphics.unk_B40C);
    Audio_PlayMusicIfChanged(0x31);

    for (i = 0; i < 16; i++) {
        BattlePrep_UpdateSingleBattleIntroFrame();
    }

    StageFade_StartFromOpaque(8);

    while (BattlePrepRoster_InitDisplayObjects(&gUIState, gBattleGraphics.unk_0008) == 0) {
        BattlePrep_UpdateSingleBattleIntroFrame();
        var_s1++;
    }

    while (var_s1 < 0x1E) {
        BattlePrep_UpdateSingleBattleIntroFrame();
        var_s1++;
    }

    for (i = 0; i < 90; i++) {
        BattlePrep_UpdateSingleBattleIntroFrame();
    }

    Audio_StopMusic(0x20);
    StageContext_SetClearColor(1);
    StageFade_StartFromTransparent(0x10);

    for (i = 0; i < 18; i++) {
        BattlePrep_UpdateSingleBattleIntroFrame();
    }

    if (gSessionContext.unk_11F5 & 1) {
        gSessionContext.unk_11F5 &= ~1;
        Save_ResetAndCommitTypedRecord(0x15, 0);
        Save_FlushBank(2);
    }

    return 4;
}

void BattlePrep_UpdateRoundIntroFrame(void) {
    Controller_PollInputs();
    BattlePrep_UpdateStarfield(gInputBuffer);
    BattlePrep_UpdateCarouselState(&gErrorScreenState);
    BattlePrep_UpdateBadgeCarousel(&gErrorScreenAnim);
    BattlePrepRoster_Update(&gUIState);
    BattlePrep_RenderFrame();
}

void BattlePrep_InitRoundIntroScene(void) {
    BattlePrep_InitBannerScene(&gErrorScreenState);
    BattlePrep_InitBadgeCarouselScene(&gErrorScreenAnim, gBattleGraphics.unk_B408, gBattleGraphics.unk_B40C);
    BattlePrepRoster_Init(&gUIState, gBattleGraphics.unk_0004->unk_0C);
}

s32 BattlePrep_ShowRoundIntro(void) {
    s32 i;
    s32 var_s1;

    if (osTvType == OS_TV_PAL) {
        var_s1 = 0x4B;
    } else {
        var_s1 = 0x5A;
    }

    Team_LoadOpponentPreset();
    BattlePrep_InitRoundIntroScene();
    BattlePrepRoster_Load(&gUIState, gBattleGraphics.unk_B40C);

    for (i = 0; i < 16; i++) {
        BattlePrep_UpdateRoundIntroFrame();
    }

    StageFade_StartFromOpaque(8);

    for (i = 0; i < 20; i++) {
        BattlePrep_UpdateRoundIntroFrame();
    }

    BattlePrep_InitCarouselEntry(&gErrorScreenState, &gBattleGraphics.unk_0008[0x10]);
    BattlePrep_InitBadgeCarousel(&gErrorScreenAnim, gBattleGraphics.unk_0008, 0);
    Audio_PlayMusicIfChanged(0x33);

    for (i = 0; i < var_s1; i++) {
        BattlePrep_UpdateRoundIntroFrame();
    }

    BattlePrep_StartCarouselExit(&gErrorScreenState);
    gErrorScreenAnim.posX = 2;

    for (i = 0; i < 16; i++) {
        BattlePrep_UpdateRoundIntroFrame();
    }

    while (BattlePrepRoster_InitDisplayObjects(&gUIState, gBattleGraphics.unk_0008) == 0) {
        BattlePrep_UpdateRoundIntroFrame();
    }

    for (i = 0; i < var_s1; i++) {
        BattlePrep_UpdateRoundIntroFrame();
    }

    Audio_StopMusic(0x20);
    StageContext_SetClearColor(1);
    StageFade_StartFromTransparent(0x10);

    for (i = 0; i < 18; i++) {
        BattlePrep_UpdateRoundIntroFrame();
    }

    if (gSessionContext.unk_11F5 & 1) {
        gSessionContext.unk_11F5 &= ~1;
        Save_ResetAndCommitTypedRecord(0x15, 0);
        Save_FlushBank(2);
    }

    return 4;
}

void BattlePrep_CheckPikachuNeedsSurf(void) {
    s32 i;
    s32 j;
    BattleAI_TeamContext* var_a1;
    unk_D_800AE540_0874* temp_v1;

    if (!(gSessionContext.unk_11F5 & 2) && (gSessionContext.unk_11F2 == 1) && (gSessionContext.unk_0000 == 6) &&
        (gSessionContext.unk_0002 == 3)) {
        var_a1 = gSessionContext.unk_1194[0].unk_08[0];
        temp_v1 = var_a1->unk_214;

        for (i = 0; i < temp_v1->unk_002; i++) {
            s32 tmp = (temp_v1->unk_028[i].unk_52 & 0x70) >> 4;
            s32 tmp2 = temp_v1->unk_028[i].unk_52 & 0xF;

            if ((tmp >= 4) || (tmp2 >= 13)) {
                return;
            }
        }

        for (i = 0; i < var_a1->unk_002; i++) {
            PokemonData* ptr = &var_a1->unk_01C[i];

            if (ptr->posX.posX == 0x19) {
                for (j = 0; j < 4; j++) {
                    if (ptr->unk_09[j] == 0) {
                        break;
                    } else if (ptr->unk_09[j] == 0x39) {
                        return;
                    }
                }
                gSessionContext.unk_11F6 |= 0x1000;
                break;
            }
        }
    }
}

void BattlePrep_UpdateRoundIntroScene(void) {
    Controller_PollInputs();
    BattlePrep_UpdateStarfield(gInputBuffer);
    BattlePrepTeamIcons_Update(&gUIElementA);
    BattlePrep_UpdateBadgeCarousel(&gErrorScreenAnim);
    BattlePrepBadgeAward_Update(&gUIElementB);
    BattlePrepStarBurst_Update(&gUIBarA);
    BattlePrepStarBurst_Update(&gUIBarB);
    BattlePrep_UpdateTrophyModel(&gBattleMenuState.posX);
    BattlePrep_UpdateTrophyModel(&gBattleMenuState.unk_10);
    BattlePrep_UpdateRuleWindow(&gBattleMenuState.unk_1C);
    BattlePrep_UpdateRuleWindow(&gBattleMenuState.unk_28);
    BattlePrep_RenderFrame();
}

void BattlePrep_InitRoundIntroSubScenes(void) {
    s32 tmp;

    BattlePrepTeamIcons_Init(&gUIElementA);
    BattlePrep_InitBadgeCarouselScene(&gErrorScreenAnim, gBattleGraphics.unk_B408, gBattleGraphics.unk_B40C);
    BattlePrepBadgeAward_Init(&gUIElementB);

    if (gBattleGraphics.unk_0003 != 0) {
        BattlePrepStarBurst_Init(&gUIBarA, 1, -1);
        BattlePrepStarBurst_Init(&gUIBarB, 0, -1);
    } else {
        BattlePrepStarBurst_Init(&gUIBarA, 1, gBattleGraphics.unk_0001);
        tmp = gBattleGraphics.unk_0001 == 0;
        BattlePrepStarBurst_Init(&gUIBarB, 0, tmp);
    }

    BattlePrep_InitTrophyModel(&gBattleMenuState.posX, 0);
    BattlePrep_InitTrophyModel(&gBattleMenuState.unk_10, 1);
}

void BattlePrep_RunNormalRoundIntro(void) {
    s32 i;

    BattlePrepTeamIcons_Load(&gUIElementA, gBattleGraphics.unk_B40C);

    for (i = 0; i < 8; i++) {
        BattlePrep_UpdateRoundIntroScene();
    }

    if (gSessionContext.unk_1194[1].unk_08[0]->unk_000 & 2) {
        if (gSessionContext.unk_1194[0].unk_1C == 1) {
            Audio_PlayMusicIfChanged(0x32);
        } else {
            Audio_PlayMusicIfChanged(0x45);
        }
    } else {
        Audio_PlayMusicIfChanged(0x32);
    }

    StageFade_StartFromOpaque(8);

    while (BattlePrepTeamIcons_InitDisplayObjects(&gUIElementA, gBattleGraphics.unk_0008) == 0) {
        BattlePrep_UpdateRoundIntroScene();
    }

    while (gUIElementA.posX != 0) {
        BattlePrep_UpdateRoundIntroScene();
    }

    BattlePrepStarBurst_Launch(&gUIBarA, &gBattleGraphics.unk_0008[0x1C], &gBattleGraphics.unk_0008[0x20]);
    BattlePrepStarBurst_Launch(&gUIBarB, &gBattleGraphics.unk_0008[0x1E], &gBattleGraphics.unk_0008[0x20]);

    while ((gErrorScreenAnim.posX != 0) || (gUIBarB.unk_5A0 != 0)) {
        BattlePrep_UpdateRoundIntroScene();
    }
}

void BattlePrep_RunFinalRoundIntro(void) {
    s32 i;

    BattlePrepTeamIcons_Load(&gUIElementA, gBattleGraphics.unk_B40C);

    for (i = 0; i < 8; i++) {
        BattlePrep_UpdateRoundIntroScene();
    }

    Audio_PlayMusicIfChanged(0x32);
    StageFade_StartFromOpaque(8);

    while (BattlePrepTeamIcons_InitDisplayObjects(&gUIElementA, gBattleGraphics.unk_0008) == 0) {
        BattlePrep_UpdateRoundIntroScene();
    }

    for (i = 0; i < 50; i++) {
        BattlePrep_UpdateRoundIntroScene();
    }

    BattlePrep_StartTrophyModelGrow(&gBattleMenuState.posX, &gBattleGraphics.unk_0008[0x1A]);
    Audio_PlayCategory11SoundCommand(0x01100013, 0, 0);

    while (gUIElementA.posX != 0) {
        BattlePrep_UpdateRoundIntroScene();
    }

    BattlePrep_StartTrophyModelShrink(&gBattleMenuState.posX);
    BattlePrepStarBurst_Launch(&gUIBarA, &gBattleGraphics.unk_0008[0x1C], &gBattleGraphics.unk_0008[0x20]);
    BattlePrepStarBurst_Launch(&gUIBarB, &gBattleGraphics.unk_0008[0x1E], &gBattleGraphics.unk_0008[0x20]);

    if (gSessionContext.unk_0003 < 8) {
        for (i = 0; i < 16; i++) {
            BattlePrep_UpdateRoundIntroScene();
        }
        BattlePrep_StartTrophyModelGrow(&gBattleMenuState.unk_10, &gBattleGraphics.unk_0008[0x1B]);
        Audio_PlaySoundEffectById(0x28);
    }

    while ((gErrorScreenAnim.posX != 0) || (gUIBarB.unk_5A0 != 0)) {
        BattlePrep_UpdateRoundIntroScene();
    }
}

void BattlePrep_RunBadgeCarouselIntro(void) {
    s32 i;
    s32 tmp;

    BattlePrepStarBurst_StartExit(&gUIBarB);
    tmp = gBattleGraphics.unk_0001 == 0;
    BattlePrep_InitBadgeCarousel(&gErrorScreenAnim, gBattleGraphics.unk_0008, tmp + 1);

    while ((gErrorScreenAnim.posX != 0) || (gUIBarB.unk_5A0 != 0)) {
        BattlePrep_UpdateRoundIntroScene();
    }

    for (i = 0; i < 16; i++) {
        BattlePrep_UpdateRoundIntroScene();
    }
}

void BattlePrep_RunBallBurstTransition(void) {
    s32 i;
    s32 j;

    while ((gUIBarA.unk_5A0 != 0) || (gUIBarB.unk_5A0 != 0)) {
        BattlePrep_UpdateRoundIntroScene();
    }

    for (i = 16; i < ARRAY_COUNT(gBattleGraphics.unk_0008); i++) {
        BattlePrep_ResetDisplayObject(&gBattleGraphics.unk_0008[i]);
    }

    Audio_PlayCategory11SoundCommand(0x01100017, 0, 0);

    for (j = 0; j < 16; j++) {
        Controller_PollInputs();
        BattlePrep_AnimateBallBurstEffect(j);
        BattlePrep_UpdateStarfield(gInputBuffer);
        BattlePrep_RenderFrame();
    }

    for (i = 0; i < 16; i++) {
        BattlePrep_ResetDisplayObject(&gBattleGraphics.unk_0008[i]);
    }

    for (j = 0; j < 16; j++) {
        Controller_PollInputs();
        BattlePrep_UpdateStarfield(gInputBuffer);
        BattlePrep_RenderFrame();
    }
}

void BattlePrep_FadeInBallBurstTransition(void) {
    s32 i;

    Audio_StopMusic(0x3C);

    for (i = 0; i < 16; i++) {
        Controller_PollInputs();
        BattlePrep_FadeInBallBurstObjects(i);
        BattlePrep_UpdateStarfield(gInputBuffer);
        BattlePrep_RenderFrame();
    }
}

void BattlePrep_FadeToTransparentEnding(void) {
    s32 i;

    Audio_StopMusic(0x3C);
    StageContext_SetClearColor(1);
    StageFade_StartFromTransparent(0x10);

    for (i = 0; i < 18; i++) {
        Controller_PollInputs();
        BattlePrep_UpdateStarfield(gInputBuffer);
        BattlePrep_RenderFrame();
    }

    for (i = 0; i < 16; i++) {
        Controller_PollInputs();
        BattlePrep_UpdateStarfield(gInputBuffer);
        BattlePrep_RenderFrame();
    }
}

s32 BattlePrep_HandleRoundContinue(void) {
    s32 var_s2;
    s32 var_v0_2;

    if (gSessionContext.unk_0000 == 7) {
        BattlePrep_InitRuleWindow(&gBattleMenuState.unk_1C, 2);
    } else {
        BattlePrep_InitRuleWindow(&gBattleMenuState.unk_1C, 1);
    }

    var_s2 = BattlePrep_PollRuleWindow(&gBattleMenuState.unk_1C);
    while (var_s2 == -1) {
        BattlePrep_UpdateRoundIntroScene();
        var_s2 = BattlePrep_PollRuleWindow(&gBattleMenuState.unk_1C);
    }

    if (var_s2 == 1) {
        if (Save_ContinueRecordExists() != 0) {
            BattlePrep_InitRuleWindow(&gBattleMenuState.unk_1C, 0xA);

            var_v0_2 = BattlePrep_PollRuleWindow(&gBattleMenuState.unk_1C);
            while (var_v0_2 == -1) {
                BattlePrep_UpdateRoundIntroScene();
                var_v0_2 = BattlePrep_PollRuleWindow(&gBattleMenuState.unk_1C);
            }

            if (var_v0_2 == 1) {
                var_s2 = 0;
            }
        }
        if (var_s2 == 1) {
            gSessionContext.unk_0003 = gSessionContext.unk_0003 + 1;
            Session_SaveContinueData();
            Save_FlushBank(2);
        }
    }
    return var_s2;
}

s32 BattlePrep_ConsumeContinueToken(void) {
    s32 sp24 = 1;
    s32 var_v0;

    if (Save_ContinueRecordExists() != 0) {
        BattlePrep_InitRuleWindow(&gBattleMenuState.unk_1C, 0xA);

        var_v0 = BattlePrep_PollRuleWindow(&gBattleMenuState.unk_1C);
        while (var_v0 == -1) {
            BattlePrep_UpdateRoundIntroScene();
            var_v0 = BattlePrep_PollRuleWindow(&gBattleMenuState.unk_1C);
        }

        if (var_v0 == 1) {
            sp24 = 0;
        }
    }

    if (sp24 != 0) {
        gSessionContext.unk_11F3--;
        Session_SaveContinueData();
        Save_FlushBank(2);
    }
    return sp24;
}

s32 BattlePrep_ConfirmDefaultRules(void) {
    s32 var_v0;

    if (gSessionContext.unk_1194[0].unk_1C == 1) {
        gSessionContext.unk_1194[0].unk_1E += 1;
    }

    if (gSessionContext.unk_1194[1].unk_1C == 1) {
        gSessionContext.unk_1194[1].unk_1E += 1;
    }

    BattlePrep_RunNormalRoundIntro();
    Audio_PlayCategory11SoundCommand(0x0110000F, 0, 0);
    BattlePrep_InitRuleWindow(&gBattleMenuState.unk_1C, 9);
    BattlePrep_InitRuleWindow(&gBattleMenuState.unk_28, 5);

    var_v0 = BattlePrep_PollRuleWindow(&gBattleMenuState.unk_28);
    while (var_v0 == -1) {
        BattlePrep_UpdateRoundIntroScene();
        var_v0 = BattlePrep_PollRuleWindow(&gBattleMenuState.unk_28);
    }

    switch (var_v0) {
        case 0:
            gSessionContext.unk_11F6 |= 0x21;
            break;

        case 1:
            gSessionContext.unk_11F6 |= 0x81;
            break;

        case 2:
            gSessionContext.unk_11F6 |= 1;
            break;
    }

    BattlePrepStarBurst_StartExit(&gUIBarB);
    BattlePrepStarBurst_StartExit(&gUIBarA);
    Audio_PlayCategory11SoundCommand(0x0110000D, 0, 0);
    BattlePrep_RunBallBurstTransition();
    BattlePrep_FadeToTransparentEnding();

    return 4;
}

s32 BattlePrep_ConfirmSimpleRules(void) {
    BattlePrep_RunNormalRoundIntro();

    do {
        BattlePrep_UpdateRoundIntroScene();
    } while (!(BTN_IS_PRESSED(gPlayer1Controller, BTN_A)));

    BattlePrepStarBurst_StartExit(&gUIBarB);
    BattlePrepStarBurst_StartExit(&gUIBarA);
    Audio_PlayCategory11SoundCommand(0x0110000D, 0, 0);
    BattlePrep_RunBallBurstTransition();
    BattlePrep_FadeToTransparentEnding();

    return 4;
}

s32 BattlePrep_ConfirmCupRules(void) {
    UNUSED s32 pad[2];
    s32 sp2C = 4;
    s32 i;
    s32 var_s2;
    s32 var_v0;

    if (gBattleGraphics.unk_0002 != 0) {
        BattlePrep_RunFinalRoundIntro();
    } else {
        BattlePrep_RunNormalRoundIntro();
    }

    BattlePrep_RunBadgeCarouselIntro();

    if (gSessionContext.unk_1194[0].unk_1C == 1) {
        gSessionContext.unk_11F3 += gBattleGraphics.unk_0002;
        if ((gBattleGraphics.unk_0002 != 0) && (gSessionContext.unk_0003 < 8)) {
            BattlePrep_StartTrophyModelShrink(&gBattleMenuState.unk_10);
        }

        BattlePrepStarBurst_StartExit(&gUIBarA);
        BattlePrepBadgeAward_InitDisplayObjects(&gUIElementB, gBattleGraphics.unk_0008);

        while (gUIElementB.posX != 3) {
            BattlePrep_UpdateRoundIntroScene();
        }

        if (gSessionContext.unk_0003 == 8) {
            for (i = 0; i < 120; i++) {
                BattlePrep_UpdateRoundIntroScene();
                if (BTN_IS_PRESSED(gPlayer1Controller, BTN_A)) {
                    break;
                }
            }

            BattlePrep_SaveVictoryPalaceRecords();
            BattlePrep_MarkFirstClearBonus();
            BattlePrep_MarkCupCleared();
            BattlePrep_MarkNewRoundRecord();
            Save_CommitTypedRecord(0x14, 0);
            Save_FlushBank(2);
            BattlePrep_RunBallBurstTransition();
            BattlePrep_FadeToTransparentEnding();
            BattlePrep_CheckPikachuNeedsSurf();
            gSessionContext.unk_11F6 |= 3;
        } else if (BattlePrep_HandleRoundContinue() == 1) {
            BattlePrep_RunBallBurstTransition();
            BattlePrep_FadeToTransparentEnding();
            gSessionContext.unk_11F6 |= 0x41;
        } else {
            BattlePrep_RunBallBurstTransition();
            Audio_StopMusic(0x50);
            gSessionContext.unk_0003++;
            sp2C = 1;
        }
    } else {
        var_s2 = 1;
        while (var_s2 != 0) {
            BattlePrep_InitRuleWindow(&gBattleMenuState.unk_1C, 7);
            BattlePrep_InitRuleWindow(&gBattleMenuState.unk_28, 3);

            var_v0 = BattlePrep_PollRuleWindow(&gBattleMenuState.unk_28);
            while (var_v0 == -1) {
                BattlePrep_UpdateRoundIntroScene();
                var_v0 = BattlePrep_PollRuleWindow(&gBattleMenuState.unk_28);
            }

            switch (var_v0) {
                case 0:
                    sp2C = 1;
                    gSessionContext.unk_11F3--;
                    var_s2 = 0;
                    break;

                case 1:
                    if (BattlePrep_ConsumeContinueToken() != 0) {
                        var_s2 = 0;
                        gSessionContext.unk_11F6 |= 0x41;
                    }
                    break;

                case 2:
                    var_s2 = 0;
                    gSessionContext.unk_11F6 |= 0x21;
                    break;

                case 3:
                    var_s2 = 0;
                    gSessionContext.unk_11F6 |= 0x801;
                    break;

                case 4:
                    var_s2 = 0;
                    gSessionContext.unk_11F6 |= 1;
                    break;
            }
        }

        if (sp2C == 4) {
            BattlePrepStarBurst_StartExit(&gUIBarA);
            BattlePrep_RunBallBurstTransition();
            BattlePrep_FadeToTransparentEnding();
        } else {
            BattlePrep_FadeInBallBurstTransition();
            BattlePrep_ResetAllDisplayObjects();
        }
    }

    return sp2C;
}

s32 BattlePrep_ConfirmCastleRules(void) {
    s32 sp28;
    s32 i;
    s32 sp24 = 4;
    s32 var_v0;

    BattlePrep_RunNormalRoundIntro();
    BattlePrep_RunBadgeCarouselIntro();

    if (gSessionContext.unk_1194[0].unk_1C == 1) {
        if ((gSessionContext.unk_0003 == 4) || (gSessionContext.unk_0002 == 9)) {
            BattlePrep_MarkCupCleared();
            BattlePrep_MarkNewRoundRecord();
            BattlePrep_SaveVictoryPalaceRecords();
            Save_CommitTypedRecord(0x14, 0);
            Save_FlushBank(2);

            for (i = 0; i < 60; i++) {
                BattlePrep_UpdateRoundIntroScene();
                if (BTN_IS_PRESSED(gPlayer1Controller, BTN_A)) {
                    break;
                }
            }

            BattlePrepStarBurst_StartExit(&gUIBarA);
            Audio_PlayCategory11SoundCommand(0x0110000D, 0, 0);
            BattlePrep_RunBallBurstTransition();
            Audio_StopMusic(0x10);

            gSessionContext.unk_11F6 |= 1;
            if (gSessionContext.unk_0002 == 8) {
                gSessionContext.unk_11F6 |= 0x400;
            }

            if (gSessionContext.unk_0002 == 9) {
                gSessionContext.unk_11F6 |= 0x200;
            } else {
                gSessionContext.unk_11F6 |= 0x100;
            }
            sp24 = 3;
        } else if (BattlePrep_HandleRoundContinue() == 1) {
            BattlePrepStarBurst_StartExit(&gUIBarA);
            Audio_PlayCategory11SoundCommand(0x0110000D, 0, 0);
            BattlePrep_RunBallBurstTransition();
            BattlePrep_FadeToTransparentEnding();
            gSessionContext.unk_11F6 |= 0x41;
        } else {
            BattlePrepStarBurst_StartExit(&gUIBarA);
            Audio_PlayCategory11SoundCommand(0x0110000D, 0, 0);
            BattlePrep_RunBallBurstTransition();
            Audio_StopMusic(0x50);
            gSessionContext.unk_0003++;
            sp24 = 1;
        }
    } else {
        BattlePrep_InitRuleWindow(&gBattleMenuState.unk_1C, 8);
        BattlePrep_InitRuleWindow(&gBattleMenuState.unk_28, 4);

        var_v0 = BattlePrep_PollRuleWindow(&gBattleMenuState.unk_28);
        while (var_v0 == -1) {
            BattlePrep_UpdateRoundIntroScene();
            var_v0 = BattlePrep_PollRuleWindow(&gBattleMenuState.unk_28);
        }

        switch (var_v0) {
            case 0:
                gSessionContext.unk_11F6 |= 0x21;
                break;

            case 1:
                gSessionContext.unk_11F6 |= 0x801;
                break;

            case 2:
                gSessionContext.unk_11F6 |= 1;
                break;
        }

        BattlePrepStarBurst_StartExit(&gUIBarA);
        BattlePrep_RunBallBurstTransition();
        BattlePrep_FadeToTransparentEnding();

        if (gSessionContext.unk_0002 == 9) {
            gSessionContext.unk_0002 = 8;
        }
    }
    return sp24;
}

s32 BattlePrep_ConfirmMewtwoRules(void) {
    s32 var_v0;
    u16 sp2A;

    BattlePrep_RunNormalRoundIntro();
    if (gSessionContext.unk_1194[0].unk_1C == 1) {
        s32 tmp1 = !!(gBattleProgress.posX & 0x100);

        if ((gSessionContext.unk_11F2 == 0) & !tmp1) {
            Save_GetOptionsField02(&sp2A);
            sp2A |= 4;
            Save_SetOptionsField02(&sp2A);
        }

        BattlePrep_MarkCupCleared();
        Save_CommitTypedRecord(0x14, 0);
        Save_FlushBank(2);
        BattlePrepStarBurst_StartExit(&gUIBarB);
        BattlePrepStarBurst_StartExit(&gUIBarA);
        Audio_PlayCategory11SoundCommand(0x0110000D, 0, 0);
        BattlePrep_RunBallBurstTransition();
        BattlePrep_FadeToTransparentEnding();
        gSessionContext.unk_11F6 |= 5;
    } else {
        BattlePrep_InitRuleWindow(&gBattleMenuState.unk_28, 6);

        var_v0 = BattlePrep_PollRuleWindow(&gBattleMenuState.unk_28);
        while (var_v0 == -1) {
            BattlePrep_UpdateRoundIntroScene();
            var_v0 = BattlePrep_PollRuleWindow(&gBattleMenuState.unk_28);
        }

        switch (var_v0) {
            case 0:
                gSessionContext.unk_11F6 |= 0x21;
                break;

            case 1:
                gSessionContext.unk_11F6 |= 1;
                break;
        }

        BattlePrepStarBurst_StartExit(&gUIBarB);
        BattlePrepStarBurst_StartExit(&gUIBarA);
        Audio_PlayCategory11SoundCommand(0x0110000D, 0, 0);
        BattlePrep_RunBallBurstTransition();
        BattlePrep_FadeToTransparentEnding();
    }
    return 4;
}

u8 BattlePrep_CheckTeamChosen(void) {
    s32 i;
    u8 var_v1 = 0;

    if ((gSessionContext.unk_0000 > 0) && (gSessionContext.unk_0000 < 7)) {
        if (gSessionContext.unk_1194[0].unk_1C == 1) {
            var_v1 = 1;
            for (i = 0; i < 3; i++) {
                if (gSessionContext.unk_1194[0].unk_08[0]->unk_01C[i].posY == 0) {
                    var_v1 = 0;
                }
            }
        }
    }

    return var_v1;
}

s32 BattlePrep_DispatchRuleConfirm(void) {
    s32 var_v0;

    gBattleGraphics.unk_0002 = BattlePrep_CheckTeamChosen();
    BattlePrep_InitRoundIntroSubScenes();

    switch (gSessionContext.unk_0000) {
        case 0:
            var_v0 = BattlePrep_ConfirmDefaultRules();
            break;

        case 1:
            var_v0 = BattlePrep_ConfirmCupRules();
            break;

        case 2:
            var_v0 = BattlePrep_ConfirmCupRules();
            break;

        case 3:
            var_v0 = BattlePrep_ConfirmCupRules();
            break;

        case 4:
            var_v0 = BattlePrep_ConfirmCupRules();
            break;

        case 5:
            var_v0 = BattlePrep_ConfirmCupRules();
            break;

        case 6:
            var_v0 = BattlePrep_ConfirmCupRules();
            break;

        case 7:
            var_v0 = BattlePrep_ConfirmCastleRules();
            break;

        case 8:
            var_v0 = BattlePrep_ConfirmMewtwoRules();
            break;

        case 9:
            var_v0 = BattlePrep_ConfirmSimpleRules();
            break;

        case 10:
            var_v0 = BattlePrep_ConfirmSimpleRules();
            break;
    }
    return var_v0;
}

s32 BattlePrep_ShowCastleClearOutro(void) {
    s32 i;
    s32 var_s1;

    if (gSessionContext.unk_0002 == 9) {
        var_s1 = 0x3C;
    } else {
        var_s1 = 0x4B;
    }

    BattlePrep_InitBannerScene(&gErrorScreenState);
    BattlePrep_InitCarouselExit(&gErrorScreenState, &gBattleGraphics.unk_0008[0x10]);
    Audio_PlayMusicIfChanged(0x3F);

    for (i = 0; i < var_s1; i++) {
        Controller_PollInputs();
        BattlePrep_UpdateStarfield(gInputBuffer);
        BattlePrep_UpdateCarouselState(&gErrorScreenState);
        BattlePrep_RenderFrame();
    }

    StageContext_SetClearColor(1);
    StageFade_StartFromTransparent(0x10);

    for (i = 0; i < 18; i++) {
        Controller_PollInputs();
        BattlePrep_UpdateStarfield(gInputBuffer);
        BattlePrep_UpdateCarouselState(&gErrorScreenState);
        BattlePrep_RenderFrame();
    }

    return 4;
}

void BattlePrep_InitScene(void) {
    MemoryBlock* temp_v0;
    CameraStruct* ptr;
    Fragment2_1GraphNode* ptr2;
    s32 i;

    gBattleGraphics.unk_0001 = 0;
    gBattleGraphics.unk_0003 = 0;
    if (gSessionContext.unk_1194[0].unk_1C == gSessionContext.unk_1194[1].unk_1C) {
        gBattleGraphics.unk_0003 = 1;
    } else if (gSessionContext.unk_1194[0].unk_1C == 1) {
        gBattleGraphics.unk_0001 = 1;
    }

    ModelRenderer_InitDisplayRoots();

    for (i = 0, ptr2 = &gBattleGraphics.unk_0008[0]; i < 128; ptr2++, i++) {
        ModelRenderer_AttachDisplayObject(ptr2);
        gBattleGraphics.unk_0008[i].modelPhase = i;
    }

    temp_v0 = MainPool_AllocState(main_pool_get_available(), 0);
    gBattleGraphics.unk_0004 = process_geo_layout(temp_v0, &gGeoLayoutCommands);
    MainPool_FinalizeAllocation(temp_v0);

    ptr = gBattleGraphics.unk_0004->unk_0C;
    ptr->unk_24.near = 10.0f;
    ptr->unk_24.far = 6000.0f;

    BattlePrep_InitStarfield(&gInputBuffer);
    BattlePrep_CloseRuleWindow(&gBattleMenuState.unk_1C);
    BattlePrep_CloseRuleWindow(&gBattleMenuState.unk_28);
}

s32 BattlePrep_RunRulesScreen(s32 arg0, UNUSED s32 arg1) {
    Stage* sp2C;

    main_pool_push_state('EYEC');
    Save_EnsureBankLoaded(2);
    Save_GetModeSettings(&gBattleProgress, gSessionContext.unk_11F2);
    Gfx_InitDisplayListBuffers(0x18000, 0);
    sp2C = StageContext_Allocate(0, 1, 3, 1, 2, 1);
    Font_Init(0x17, 0);

    ASSET_LOAD(D_1000000, common_menu1_ui, 0);
    ASSET_LOAD(D_2000000, badge_ui, 0);
    ASSET_LOAD(D_3000000, common_menu0_ui, 0);

    Text_InitStringTables();
    gBattleMessageTable = Text_GetStringTable(0x1B);
    PokeIcon_OpenModelArchive();

    gBattleGraphics.unk_B408 = BinArchive_Open(0x898000, NULL, 1, 1);
    gBattleGraphics.unk_B40C = ASSET_LOAD2(battle_portraits, 1, 1);

    StageContext_Activate(sp2C);
    BattlePrep_InitScene();

    while (arg0 < 4) {
        main_pool_push_state('eye0');

        switch (arg0) {
            case 0:
                arg0 = BattlePrep_ShowSingleBattleIntro();
                break;

            case 1:
                arg0 = BattlePrep_ShowRoundIntro();
                break;

            case 2:
                arg0 = BattlePrep_DispatchRuleConfirm();
                break;

            case 3:
                arg0 = BattlePrep_ShowCastleClearOutro();
                break;
        }

        main_pool_pop_state('eye0');
    }

    StageContext_Deactivate();
    Font_Free();
    Gfx_FreeDisplayListBuffers();

    main_pool_pop_state('EYEC');

    return 0;
}
