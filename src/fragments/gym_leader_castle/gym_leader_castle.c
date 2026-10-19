#include "gym_leader_castle.h"
#include "src/graphics_textures.h"
#include "src/ui_graphics.h"
#include "src/save_data.h"
#include "src/game_state.h"
#include "src/text_system.h"
#include "src/3FB0.h"
#include "src/audio_sfx.h"
#include "src/audio_commands_category2.h"
#include "src/DDC0.h"
#include "src/memory.h"
#include "src/stage_loader.h"

static char** gGymMessageBank;
static char** gRoomMessageBank;
static TrainerPortrait gTrainerPortraits[4];
static BinArchive* gTrainerDataArchive;
static BinArchive* gPortraitGfxArchive;
static BinArchive* D_84A03170;
static u8* gBgTexture1;
static u8* gBgTexture2;
static u8* gBgTexture3;
static SessionModeSettings D_84A03180;
static s16 gPrevRoomIndex;

static RoomDef gRoomDefinitions[] = {
    {
        0x00,      0x00, 154, 390,  118, 362, 96, 278, 48, 70, -32768, 0, 0, 0, 2, { 0x96, 0x64, 0xFF, 0x00 },
        D_3000000, 0,    30,  NULL,
    },
    {
        0x01,      0x00, 238, 416,  210, 392, 184, 304, 48, 70, -32768, 3, 0, 1, 3, { 0x00, 0x9B, 0xFF, 0x00 },
        D_3000D20, 1,    31,  NULL,
    },
    {
        0x02,      0x00, 322, 386,  282, 362, 248, 274, 48, 70, -32768, 4, 2, 2, 0, { 0xFF, 0x5F, 0x0F, 0x00 },
        D_3001A40, 2,    32,  NULL,
    },
    {
        0x03,      0x00, 270, 304,  256, 282, 234, 190, 48, 70, -32768, 5, 3, 5, 0, { 0x8C, 0x37, 0xFF, 0x00 },
        D_3002760, 3,    33,  NULL,
    },
    {
        0x04,      0x00, 214, 286,  188, 266, 168, 180, 48, 70, -32768, 6, 4, 6, 4, { 0xFF, 0x37, 0xFF, 0x00 },
        D_3003480, 4,    34,  NULL,
    },
    {
        0x05,      0x00, 164, 178,  160, 170, 116, 96, 48, 70, -32768, 7, 5, 0, 7, { 0xCD, 0x91, 0x00, 0x00 },
        D_30041A0, 5,    35,  NULL,
    },
    {
        0x06,      0x00, 284, 148,  290, 138, 250, 78, 48, 70, -32768, 0, 8, 6, 8, { 0xFF, 0x00, 0x00, 0x00 },
        D_3004EC0, 6,    36,  NULL,
    },
    {
        0x07,      0x00, 364, 243,  330, 214, 306, 110, 48, 70, -32768, 7, 0, 7, 9, { 0x37, 0xFF, 0xFF, 0x00 },
        D_3005BE0, 7,    37,  NULL,
    },
    {
        0x08,      0x00, 0,  0,    418, 204, 390, 102, 48, 70, -32768, 0, 0, 0, 0, { 0xC8, 0xFF, 0x00, 0x00 },
        D_3006900, -1,   -1, NULL,
    },
    {
        0x09,      0x00, 190, 384,  174, 424, 180, 394, 40, 27, -32768, 0, 0, 0, 0, { 0xFF, 0x64, 0x00, 0x00 },
        D_3008E50, -1,   9,   NULL,
    },
    {
        0x0A,      0x00, 446, 216,  374, 210, 356, 128, 72, 43, -32768, 12, 10, 10, 0, { 0xFF, 0x64, 0x00, 0x00 },
        D_3007620, 10,   10,  NULL,
    },
    {
        0x0B,      0x00, 0,  0,    312, 148, 274, 68, 72, 43, -32768, 0, 11, 0, 0, { 0x00, 0x64, 0xC8, 0x00 },
        D_3008238, -1,   11, NULL,
    },
};

static s16 gCurrentRoomIndex = 0;
static s16 gRoomTransitionTimer = 0;
static s16 gPanelFadeAlpha = 0xFF;
static s16 gInfoPanelHeight = 0;
static s16 gBgFadeAlpha = 0;

void Glc_DrawBackgroundCrossfade(u8* arg0, u8* arg1, u8 arg2) {
    s32 i;
    s32 j;

    gDPPipeSync(gDisplayListHead++);

    gDPSetCycleType(gDisplayListHead++, G_CYC_2CYCLE);
    gDPSetRenderMode(gDisplayListHead++, G_RM_OPA_SURF, G_RM_OPA_SURF2);
    gDPSetTexturePersp(gDisplayListHead++, G_TP_NONE);
    gDPSetScissor(gDisplayListHead++, G_SC_NON_INTERLACE, 0, 0, 640, 480);
    gDPSetCombineLERP(gDisplayListHead++, TEXEL1, TEXEL0, ENV_ALPHA, TEXEL0, TEXEL1, TEXEL0, ENVIRONMENT, TEXEL0, 0, 0,
                      0, COMBINED, 0, 0, 0, COMBINED);
    gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, arg2);

    gDPPipeSync(gDisplayListHead++);

    for (i = 0; i < 0x1E0; i += 0x20) {
        for (j = 0; j < 0x280; j += 0x20) {
            gDPLoadTextureBlock(gDisplayListHead++, arg0, G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 16, 0,
                                G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK,
                                G_TX_NOLOD, G_TX_NOLOD);
            gDPLoadMultiBlock(gDisplayListHead++, arg1, 0x0100, 1, G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 16, 0,
                              G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK,
                              G_TX_NOLOD, G_TX_NOLOD);
            gSPTextureRectangle(gDisplayListHead++, j << 2, i << 2, (j + 0x20) << 2, (i + 0x20) << 2, G_TX_RENDERTILE,
                                0, 0, 0x0200, 0x0200);
            arg0 += 0x200;
            arg1 += 0x200;
        }
    }
}

void Glc_DrawScaledTextureRgba(s16 arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, u8* arg5, f32 arg6) {
    UNUSED s32 pad;

    gDPLoadTextureBlock(gDisplayListHead++, arg5, G_IM_FMT_RGBA, G_IM_SIZ_16b, (s32)(arg4 / arg6), (s32)(arg3 / arg6),
                        0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                        G_TX_NOLOD);

    Gfx_DrawTexturedRectClipped(arg0, arg1, arg2, arg3, 0, 0, 1024.0f / arg6, 1024.0f / arg6, 0);
}

void func_84A00630(void) {
}

void Glc_DrawScaledTextureIa8(s16 arg0, s16 arg1, s16 arg2, s16 arg3, u8* arg4, f32 arg5) {
    UNUSED s32 pad;

    gDPLoadTextureBlock(gDisplayListHead++, arg4, G_IM_FMT_IA, G_IM_SIZ_8b, (s32)(arg2 / arg5), (s32)(arg3 / arg5), 0,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                        G_TX_NOLOD);

    Gfx_DrawTexturedRectClipped(arg0, arg1, arg2, arg3, 0, 0, 1024.0f / arg5, 1024.0f / arg5, 0);
}

void Glc_DrawRoomDescription(void) {
    char sp40[0x100];
    UNUSED s32 pad2;
    s16 sp3A;
    UNUSED s32 pad;
    s16 temp_v0;

    if (gInfoPanelHeight >= 0x10) {
        sp3A = 0xF0 - (gInfoPanelHeight / 2);
        Ui_DrawBorderedPanelNoFill(0x78, sp3A, 0x190, gInfoPanelHeight);
        Gfx_FillRectWithDisplayState(0x7F, sp3A + 7, 0x182, gInfoPanelHeight - 0xE, 0x14, 0x32, 0x64, 0x96);

        if (gInfoPanelHeight == 0x50) {
            Font_BeginTranslucentTextRendering();
            Font_SetActive(8, 0);
            Font_SetLineHeight(0x18);

            if (gCurrentRoomIndex == 7) {
                Font_Printf(0x88, sp3A + 0x10, Text_GetString(NULL, 0, gGymMessageBank, 0xC));
            } else if (gCurrentRoomIndex == 0xA) {
                Font_Printf(0x88, sp3A + 0x10, Text_GetString(NULL, 0, gGymMessageBank, 0xD));
            } else {
                temp_v0 = gRoomDefinitions[gCurrentRoomIndex].unk_22;
                if (temp_v0 >= 0x1E) {
                    Text_SetStringToken(0x24, Text_GetString(NULL, 0, gRoomMessageBank, temp_v0));
                } else if (temp_v0 >= 0) {
                    Text_SetStringToken(0x24, Text_GetString(NULL, 0, gGymMessageBank, temp_v0));
                } else {
                    Text_SetStringToken(0x24, " ");
                }

                temp_v0 = gRoomDefinitions[gCurrentRoomIndex + 1].unk_22;
                if (temp_v0 >= 0x1E) {
                    Text_SetStringToken(0x29, Text_GetString(NULL, 0, gRoomMessageBank, temp_v0));
                } else if (temp_v0 >= 0) {
                    Text_SetStringToken(0x29, Text_GetString(NULL, 0, gGymMessageBank, temp_v0));
                } else {
                    Text_SetStringToken(0x29, " ");
                }
                Font_Printf(0x88, sp3A + 0x10, Text_GetString(sp40, sizeof(sp40), gGymMessageBank, 0xE));
            }
            Font_EndTexturedTextRendering();
        }
    }
}

void Glc_DrawTrainerIntroPanels(void) {
    UNUSED s32 pad[3];
    s32 i;
    char* var_s0;
    RoomDef* sp58 = &gRoomDefinitions[gCurrentRoomIndex];

    for (i = 0; i < 4; i++) {
        if (gTrainerPortraits[i].posX != 0) {
            s16 tmp = gTrainerPortraits[i].posY;

            gSPDisplayList(gDisplayListHead++, gPrefDL_Border);

            Glc_DrawScaledTextureRgba(tmp, 0xF0, 0x80, 0x40, 0x80, D_3009290, 2.0f);
            Glc_DrawScaledTextureRgba(tmp, 0x130, 0x80, 0x40, 0x80, D_300A290, 2.0f);
            Glc_DrawScaledTextureRgba(tmp, 0x170, 0x80, 0x40, 0x80, D_300B290, 2.0f);
            Glc_DrawScaledTextureRgba(tmp + 8, 0x138, 0x70, 0x38, 0x80, gTrainerPortraits[i].rotation + 0x208, 2.0f);
            Glc_DrawScaledTextureRgba(tmp + 8, 0x170, 0x70, 0x38, 0x80, gTrainerPortraits[i].rotation + 0x1008, 2.0f);

            gSPDisplayList(gDisplayListHead++, gPrefDL_End);

            Font_BeginTranslucentTextRendering();

            if ((gCurrentRoomIndex >= 8) || (i == 3)) {
                Font_SetActive(8, 0);

                if (sp58->unk_20 >= 0) {
                    var_s0 = Text_GetString(NULL, 0, gGymMessageBank, sp58->unk_20);
                } else {
                    var_s0 = " ";
                }

                Font_Printf((tmp - (Font_MeasureTextExtent(8, 0, var_s0) / 2)) + 0x40, 0xF4, var_s0);
            }

            Font_SetActive(4, 0);

            if ((i == 3) && (gCurrentRoomIndex < 8)) {
                Font_Printf(tmp + 8, 0x10C, Text_GetString(NULL, 0, gGymMessageBank, 8));
            } else {
                Font_Printf(tmp + 8, 0x10C, Text_GetString(NULL, 0, gGymMessageBank, 0xF));
            }

            Font_SetActive(0x10, 0);
            Font_Printf((tmp - (Font_MeasureTextExtent(0x10, 0, gTrainerPortraits[i].unk_08) / 2)) + 0x40, 0x11C,
                          gTrainerPortraits[i].unk_08);
            Font_EndTexturedTextRendering();
        }
    }
}

void Glc_DrawMapBorder(void) {
    static s16 D_84A030F4 = 0;
    static s16 gScrollDirection = 1;

    s16 i;
    s16 var_s1 = (D_84A030F4 / 4) + 0x22;

    gSPDisplayList(gDisplayListHead++, gPrefDL_Border);

    for (i = 0; i < 9; i++) {
        Gfx_DrawTextureRgba16(0x24, var_s1, 0xE4, 8, D_3011A30 + i * 0xE40, 0xE4, 0);
        var_s1 += 8;
    }

    gSPDisplayList(gDisplayListHead++, gPrefDL_End);

    D_84A030F4 += gScrollDirection;
    if (D_84A030F4 == 0) {
        gScrollDirection = 1;
    }

    if (D_84A030F4 == 0x23) {
        gScrollDirection = -1;
    }
}

void Glc_DrawRoomMarkers(void) {
    s32 i;
    s32 var_a0;
    s32 var_s2;
    RoomDef* var_s0;

    if (gCurrentRoomIndex < 9) {
        var_s0 = &gRoomDefinitions[0];
        var_s2 = 9;
    } else {
        var_s0 = &gRoomDefinitions[9];
        var_s2 = 3;
    }

    gDPPipeSync(gDisplayListHead++);
    gDPSetCycleType(gDisplayListHead++, G_CYC_1CYCLE);
    gDPSetTexturePersp(gDisplayListHead++, G_TP_NONE);
    gDPSetCombineLERP(gDisplayListHead++, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, ENVIRONMENT, 0,
                      PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, ENVIRONMENT, 0);
    gDPSetRenderMode(gDisplayListHead++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
    gSPClearGeometryMode(gDisplayListHead++, G_ZBUFFER | G_LIGHTING);

    for (; var_s2 > 0; var_s2--, var_s0++) {
        if (var_s0->unk_01 != 0) {
            var_a0 = 0xFF;
            if (var_s0->unk_01 == 1) {
                var_a0 = (s32)((COSS(var_s0->unk_12) + 1.0f) * 96.0f);
                var_a0 += 0x3F;
                var_s0->unk_12 += 0x200;
            } else {
                var_s0->unk_12 = 0;
                var_s0->unk_01--;
            }

            gDPSetEnvColor(gDisplayListHead++, var_s0->unk_18.r, var_s0->unk_18.g, var_s0->unk_18.b, var_a0);

            if (var_s0->posX == 9) {
                gDPSetPrimColor(gDisplayListHead++, 0, 0, 255, 255, 0, 255);
            } else {
                gDPSetPrimColor(gDisplayListHead++, 0, 0, 255, 255, 255, 255);
            }

            Glc_DrawScaledTextureIa8(var_s0->unk_0A, var_s0->unk_0C, var_s0->unk_0E * 2, var_s0->unk_10 * 2, var_s0->unk_1C, 2.0f);
        }
    }

    gSPDisplayList(gDisplayListHead++, gPrefDL_End);
}

void Glc_DrawRoomLabels(void) {
    s32 var_s2;
    char* var_s0;
    RoomDef* var_s1;
    s16 tmp;

    if (gCurrentRoomIndex < 9) {
        var_s1 = &gRoomDefinitions[0];
        var_s2 = 8;
    } else {
        var_s1 = &gRoomDefinitions[9];
        var_s2 = 3;
    }

    Font_BeginTranslucentTextRendering();
    Font_EnableTwoCycleTexturing();
    Font_SetActive(4, 0);
    Text_SetPrimColor(0x50, 0x64, 0xDC, 0xFF);

    for (; var_s2 > 0; var_s2--, var_s1++) {
        if (var_s1->unk_01 != 0) {
            if (var_s1->unk_22 >= 0x1E) {
                var_s0 = Text_GetString(NULL, 0, gRoomMessageBank, var_s1->unk_22);
            } else if (var_s1->unk_22 >= 0) {
                var_s0 = Text_GetString(NULL, 0, gGymMessageBank, var_s1->unk_22);
            } else {
                var_s0 = " ";
            }
            tmp = var_s1->posY - (Font_MeasureTextExtent(4, 0, var_s0) / 2);
            Font_Printf(tmp, var_s1->rotation, var_s0);
        }
    }

    Font_DisableTwoCycleTexturing();
    Font_EndTexturedTextRendering();
}

void Glc_DrawGymLeaderInfoPanel(RoomDef* arg0, u8 arg1, u8 arg2) {
    char* sp54;

    if (arg0->unk_24 != NULL) {
        gSPDisplayList(gDisplayListHead++, gPrefDL_Border);
        gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, arg1);

        Glc_DrawScaledTextureRgba(0x1F6, 0x160, 0x60, 0x30, 0x60, arg0->unk_24, 1.5f);
        Glc_DrawScaledTextureRgba(0x1F6, 0x190, 0x60, 0x30, 0x60, arg0->unk_24 + 0x1000, 1.5f);

        gSPDisplayList(gDisplayListHead++, gDL_XluBorder);
        gDPSetEnvColor(gDisplayListHead++, arg0->unk_18.r, arg0->unk_18.g, arg0->unk_18.b, (arg2 * 0x96) / 255);

        Gfx_DrawTextureIa16(0x166, 0x174, 0x10, 0x4C, D_300C290, 0x10, 0);
        Gfx_DrawTexturedRectClipped(0x176, 0x174, 0x80, 0x4C, 0x1E0, 0, 0, 0x400, 0);

        gSPDisplayList(gDisplayListHead++, gPrefDL_End);

        Font_BeginTranslucentTextRendering();
        Font_EnableTwoCycleTexturing();
        Text_SetEnvColor(0x8C, 0x90, 0x90, arg2);
        Text_SetPrimColor(0xFF, 0xFF, 0xFF, arg2);
        Font_SetActive(8, 0);

        if (arg0->unk_20 >= 0) {
            sp54 = Text_GetString(NULL, 0, gGymMessageBank, arg0->unk_20);
        } else {
            sp54 = " ";
        }
        Font_Printf(0x1AE - (Font_MeasureTextExtent(8, 0, sp54) / 2), 0x17A, sp54);
        Font_SetActive(0x20, 0);

        if (arg0->unk_22 >= 0x1E) {
            sp54 = Text_GetString(NULL, 0, gRoomMessageBank, arg0->unk_22);
        } else if (arg0->unk_22 >= 0) {
            sp54 = Text_GetString(NULL, 0, gGymMessageBank, arg0->unk_22);
        } else {
            sp54 = " ";
        }

        Font_Printf(0x1AE - (Font_MeasureTextExtent(0x20, 0, sp54) / 2), 0x196, sp54);
        Font_DisableTwoCycleTexturing();
        Font_EndTexturedTextRendering();
    }
}

void Glc_DrawEliteFourRoomInfoPanel(RoomDef* arg0, u8 arg1, u8 arg2) {
    char* var_s0;

    gSPDisplayList(gDisplayListHead++, gPrefDL_Border);
    gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, arg1);

    Glc_DrawScaledTextureRgba(0x1D6, 0x13E, 0x80, 0x1A, 0x80, arg0->unk_24, 1.28f);
    Glc_DrawScaledTextureRgba(0x1D6, 0x158, 0x80, 0x1A, 0x80, arg0->unk_24 + 0xFA0, 1.28f);
    Glc_DrawScaledTextureRgba(0x1D6, 0x172, 0x80, 0x1A, 0x80, arg0->unk_24 + 0x1F40, 1.28f);
    Glc_DrawScaledTextureRgba(0x1D6, 0x18C, 0x80, 0x1A, 0x80, arg0->unk_24 + 0x2EE0, 1.28f);
    Glc_DrawScaledTextureRgba(0x1D6, 0x1A6, 0x80, 0x1A, 0x80, arg0->unk_24 + 0x3E80, 1.28f);

    gSPDisplayList(gDisplayListHead++, gDL_XluBorder);
    gDPSetEnvColor(gDisplayListHead++, arg0->unk_18.r, arg0->unk_18.g, arg0->unk_18.b, (arg2 * 0x96) / 255);
    gDPLoadTextureBlock(gDisplayListHead++, D_300C290, G_IM_FMT_IA, G_IM_SIZ_16b, 16, 76, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

    Gfx_DrawTexturedRectClipped(0x15A, 0x174, 0x10, 0x4C, 0, 0, 0x400, 0x400, 0);
    Gfx_DrawTexturedRectClipped(0x16A, 0x174, 0x6C, 0x4C, 0x1E0, 0, 0, 0x400, 0);

    gSPDisplayList(gDisplayListHead++, gPrefDL_End);

    Font_BeginTranslucentTextRendering();
    Font_EnableTwoCycleTexturing();
    Text_SetEnvColor(0x8C, 0x90, 0x90, arg2);
    Text_SetPrimColor(0xFF, 0xFF, 0xFF, arg2);
    Font_SetActive(0x10, 0);

    if (arg0->unk_22 >= 0x1E) {
        var_s0 = Text_GetString(NULL, 0, gRoomMessageBank, arg0->unk_22);
    } else if (arg0->unk_22 >= 0) {
        var_s0 = Text_GetString(NULL, 0, gGymMessageBank, arg0->unk_22);
    } else {
        var_s0 = " ";
    }

    Font_Printf(0x198 - (Font_MeasureTextExtent(0x10, 0, var_s0) / 2), 0x196, var_s0);
    Font_DisableTwoCycleTexturing();
    Font_EndTexturedTextRendering();
}

void Glc_UpdateRoomInfoPanelFade(void) {
    u8 sp1F;

    if (gPanelFadeAlpha > 0) {
        if (gPanelFadeAlpha < 0xFF) {
            if (gCurrentRoomIndex == 0xA) {
                Glc_DrawEliteFourRoomInfoPanel(&gRoomDefinitions[gCurrentRoomIndex], gPanelFadeAlpha, gPanelFadeAlpha);
            } else {
                Glc_DrawGymLeaderInfoPanel(&gRoomDefinitions[gCurrentRoomIndex], gPanelFadeAlpha, gPanelFadeAlpha);
            }
        } else if (gRoomTransitionTimer == 0) {
            if (gCurrentRoomIndex == 0xA) {
                Glc_DrawEliteFourRoomInfoPanel(&gRoomDefinitions[gCurrentRoomIndex], 0xFF, 0xFF);
            } else {
                Glc_DrawGymLeaderInfoPanel(&gRoomDefinitions[gCurrentRoomIndex], 0xFF, 0xFF);
            }
        } else {
            sp1F = ((gRoomTransitionTimer * 0xFF) / 4) & 0xFF;
            if (gCurrentRoomIndex == 0xA) {
                Glc_DrawEliteFourRoomInfoPanel(&gRoomDefinitions[gCurrentRoomIndex], 0xFF, 0xFF - sp1F);
            } else {
                Glc_DrawGymLeaderInfoPanel(&gRoomDefinitions[gCurrentRoomIndex], 0xFF, 0xFF - sp1F);
            }

            if (gPrevRoomIndex == 0xA) {
                Glc_DrawEliteFourRoomInfoPanel(&gRoomDefinitions[gPrevRoomIndex], sp1F, sp1F);
            } else {
                Glc_DrawGymLeaderInfoPanel(&gRoomDefinitions[gPrevRoomIndex], sp1F, sp1F);
            }
        }
    }
}

void Glc_UpdateMapCursor(void) {
    s16 sp1E;
    s16 sp1C;
    RoomDef* temp_a1 = &gRoomDefinitions[gCurrentRoomIndex];

    if (gRoomTransitionTimer == 0) {
        sp1E = temp_a1->unk_06 - 0x20;
        sp1C = temp_a1->unk_08 - 0xD;
    } else {
        sp1E = ((((gRoomDefinitions[gPrevRoomIndex].unk_06 - temp_a1->unk_06) * gRoomTransitionTimer) / 4) + temp_a1->unk_06) - 0x20;
        sp1C = ((((gRoomDefinitions[gPrevRoomIndex].unk_08 - temp_a1->unk_08) * gRoomTransitionTimer) / 4) + temp_a1->unk_08) - 0xD;

        gRoomTransitionTimer--;
        if ((gRoomTransitionTimer == 0) && ((gCurrentRoomIndex == 8) || (gCurrentRoomIndex == 9))) {
            StageContext_SetClearColor(1);
            StageFade_StartFromTransparent(8);
        }
    }

    Ui_DrawAnimatedTextureMarker(sp1E - 3, sp1C);
}

void Glc_Draw(void) {
    BgStage_DrawFrame();

    if (gCurrentRoomIndex < 9) {
        if (gBgFadeAlpha == 0) {
            Gfx_DrawTiledRgba16Image(gBgTexture1);
        } else if (gBgFadeAlpha == 0xFF) {
            Gfx_DrawTiledRgba16Image(gBgTexture2);
        } else {
            Glc_DrawBackgroundCrossfade(gBgTexture1, gBgTexture2, gBgFadeAlpha);
            if (gBgFadeAlpha < 0xFF) {
                gBgFadeAlpha += 5;
            }
        }
    } else {
        Gfx_DrawTiledRgba16Image(gBgTexture3);
        gBgFadeAlpha = 0xFF;
    }

    if (gSessionContext.inRound2 == 1) {
        gSPDisplayList(gDisplayListHead++, gPrefDL_Border);

        Gfx_DrawTextureRgba16(0x22C, 0x28, 0x24, 0x24, D_3019C38, 0x24, 0);

        gSPDisplayList(gDisplayListHead++, gPrefDL_End);
    }

    Glc_DrawRoomMarkers();
    Glc_DrawRoomLabels();
    Glc_UpdateRoomInfoPanelFade();
    Glc_UpdateMapCursor();
    Glc_DrawTrainerIntroPanels();
    Glc_DrawMapBorder();
    Glc_DrawRoomDescription();
    BgStage_AdvanceFrame();
}

s32 Glc_GetInputStatus(void) {
    return 0;
}

s32 Glc_SelectRoom(void) {
    s16 var_s4;
    s16 var_s1;
    s16 var_s3;
    RoomDef* temp_s0;

    var_s4 = 0x1E;
    var_s3 = 2;

    while (var_s3 == 2) {
        var_s1 = -1;
        temp_s0 = &gRoomDefinitions[gCurrentRoomIndex];

        Controller_PollInputs();

        if (Glc_GetInputStatus() == 0) {
            if (StageContext_GetFadeMode() == 0) {
                if (gRoomTransitionTimer == 0) {
                    gPrevRoomIndex = gCurrentRoomIndex;
                    if (gCurrentRoomIndex == 0xB) {
                        var_s4--;
                        if (var_s4 == 0) {
                            var_s3 = 3;
                        }
                    } else if (BTN_IS_PRESSED(gPlayer1Controller, BTN_A)) {
                        Audio_PlaySoundEffectById(2);
                        var_s3 = 3;
                    } else if (BTN_IS_PRESSED(gPlayer1Controller, BTN_B)) {
                        Audio_PlaySoundEffectById(3);
                        if (temp_s0->posX >= 0xA) {
                            gCurrentRoomIndex = 9;
                            gRoomTransitionTimer = 3;
                        } else {
                            var_s3 = 1;
                        }
                    } else if (BTN_IS_PRESSED(gPlayer1Controller, BTN_DUP) && (temp_s0->unk_14 != 0)) {
                        var_s1 = temp_s0->unk_14 - 1;
                    } else if (BTN_IS_PRESSED(gPlayer1Controller, BTN_DDOWN) && (temp_s0->unk_15 != 0)) {
                        var_s1 = temp_s0->unk_15 - 1;
                    } else if (BTN_IS_PRESSED(gPlayer1Controller, BTN_DLEFT) && (temp_s0->unk_16 != 0)) {
                        var_s1 = temp_s0->unk_16 - 1;
                    } else if (BTN_IS_PRESSED(gPlayer1Controller, BTN_DRIGHT) && (temp_s0->unk_17 != 0)) {
                        var_s1 = temp_s0->unk_17 - 1;
                    }

                    if ((var_s1 >= 0) && (gRoomDefinitions[var_s1].unk_01 != 0)) {
                        Audio_PlaySoundEffectById(1);
                        gCurrentRoomIndex = var_s1;
                        gRoomTransitionTimer = 3;
                    }
                }
            } else if (StageContext_GetFadeMode() == 1) {
                if (gCurrentRoomIndex == 8) {
                    gCurrentRoomIndex = 0xA;
                }

                if (gCurrentRoomIndex == 9) {
                    gCurrentRoomIndex = 7;
                }
                StageFade_StartFromOpaque(8);
            }
        }
        Glc_Draw();
    }
    return var_s3;
}

void Glc_LoadTrainerPanels(void) {
    s32 i;
    s32 var_a1;
    s32 var_s7;
    TrainerData* var_s1;
    s32 portrait_file_idx;

    if (gCurrentRoomIndex == 0xB) {
        var_s7 = 1;
    } else {
        var_s7 = 4;
    }

    if (gCurrentRoomIndex < 8) {
        var_a1 = gCurrentRoomIndex + 0xC;
    } else {
        var_a1 = gCurrentRoomIndex + 0xA;
    }

    if (gSessionContext.inRound2 != 0) {
        var_a1 += 0x1F;
    }

    var_s1 = BinArchive_GetFile(gTrainerDataArchive, var_a1);

    for (i = 0; i < var_s7; i++) {
        portrait_file_idx = (var_s1[i].gfx_file_idx >> 8) & 0xFF;
        gTrainerPortraits[i].posX = 1;
        gTrainerPortraits[i].posY = 0x280;
        gTrainerPortraits[i].unk_08 = var_s1[i].name1;
        gTrainerPortraits[i].rotation = BinArchive_GetFile(gPortraitGfxArchive, portrait_file_idx);
    }
}

void Glc_ClearTrainerPanels(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        gTrainerPortraits[i].posX = 0;
    }
}

void Glc_AnimateTrainerPanelsIn(s16 arg0, s16 arg1, s16 arg2, s16 arg3) {
    s32 i;

    while (arg2-- > 0) {
        for (i = arg0; i <= arg1; i++) {
            gTrainerPortraits[i].posY += arg3;
        }
        Controller_PollInputs();
        Glc_Draw();
    }
}

s32 GymLeaderCastle_ShowIntro(void) {
    s16 i;
    s32 var_s1;
    s32 var_s1_2 = 0;

    main_pool_push_state('itro');

    Glc_LoadTrainerPanels();
    Audio_StopMusic(8);

    for (i = 3; i >= 0; i--) {
        gPanelFadeAlpha = i << 6;
        Controller_PollInputs();
        Glc_Draw();
    }

    Audio_PlayMusicIfChanged(0x2B);
    if (gCurrentRoomIndex == 0xB) {
        Glc_AnimateTrainerPanelsIn(0, 0, 6, -0x40);
    } else {
        Glc_AnimateTrainerPanelsIn(0, 3, 3, -0x40);
        Glc_AnimateTrainerPanelsIn(0, 2, 2, -0x40);
        Glc_AnimateTrainerPanelsIn(0, 1, 2, -0x40);
        Glc_AnimateTrainerPanelsIn(0, 0, 2, -0x40);
    }

    while (var_s1_2 == 0) {
        Controller_PollInputs();
        Glc_Draw();
        if (BTN_IS_PRESSED(gPlayer1Controller, BTN_A)) {
            var_s1_2 = 1;
        } else if (BTN_IS_PRESSED(gPlayer1Controller, BTN_B)) {
            if (gCurrentRoomIndex == 0xB) {
                var_s1_2 = 1;
            } else {
                var_s1_2 = 2;
            }
        }
    }

    if (var_s1_2 == 1) {
        Audio_PlaySoundEffectById(0x1C);
        var_s1 = 0;
        if (gCurrentRoomIndex == 0xB) {
            Glc_AnimateTrainerPanelsIn(0, 0, 6, -0x40);
        } else {
            Glc_AnimateTrainerPanelsIn(3, 3, 2, -0x40);
            Glc_AnimateTrainerPanelsIn(2, 3, 2, -0x40);
            Glc_AnimateTrainerPanelsIn(1, 3, 2, -0x40);
            Glc_AnimateTrainerPanelsIn(0, 3, 3, -0x40);
        }
        Glc_ClearTrainerPanels();
        Glc_Draw();
    } else {
        Audio_PlaySoundEffectById(3);
        var_s1 = 2;
        Audio_StopMusic(0x12);
        if (gCurrentRoomIndex == 0xB) {
            Glc_AnimateTrainerPanelsIn(0, 0, 6, 0x40);
        } else {
            Glc_AnimateTrainerPanelsIn(0, 0, 2, 0x40);
            Glc_AnimateTrainerPanelsIn(0, 1, 2, 0x40);
            Glc_AnimateTrainerPanelsIn(0, 2, 2, 0x40);
            Glc_AnimateTrainerPanelsIn(0, 3, 3, 0x40);
        }
        Glc_ClearTrainerPanels();

        if (D_84A03180.rotation < 8) {
            Audio_PlayMusicIfChanged(0x2A);
        } else {
            Audio_PlayMusicIfChanged(0x27);
        }

        for (i = 1; i < 5; i++) {
            gPanelFadeAlpha = (i << 6) - 1;
            Controller_PollInputs();
            Glc_Draw();
        }
    }

    main_pool_pop_state('itro');

    return var_s1;
}

s32 Glc_AdvanceRoom(void) {
    s16 i;

    if (gSessionContext.unk_0002 == 7) {
        Audio_PlayCategory11SoundCommand(0x01100015, 0, 0);
        gBgFadeAlpha = 5;
    }

    for (i = 1; i < 5; i++) {
        gInfoPanelHeight = i * 0x14;
        Controller_PollInputs();
        Glc_Draw();
    }

    do {
        Controller_PollInputs();
        Glc_Draw();
    } while (!BTN_IS_PRESSED(gPlayer1Controller, BTN_A | BTN_B));

    Audio_PlaySoundEffectById(0x01100011);

    if (gSessionContext.unk_0002 == 8) {
        gRoomDefinitions[11].unk_01 = 0x3C;
    } else {
        gRoomDefinitions[D_84A03180.rotation].unk_01 = 0x3C;
    }

    if (D_84A03180.rotation == 8) {
        gRoomDefinitions[9].unk_01 = 0x3C;
        gRoomDefinitions[10].unk_01 = 0x3C;
    }

    for (i = 3; i >= 0; i--) {
        gInfoPanelHeight = i * 0x14;
        Controller_PollInputs();
        Glc_Draw();
    }

    gPrevRoomIndex = gCurrentRoomIndex;
    gCurrentRoomIndex += 1;
    gRoomTransitionTimer = 3;
    return 2;
}

s16 Glc_RunMenu(s16 arg0) {
    s16 i;

    if (StageContext_GetFadeMode() == 1) {
        StageFade_StartFromOpaque(8);
        for (i = 0; i < 9; i++) {
            Controller_PollInputs();
            Glc_Draw();
        }
    }

    while ((arg0 != 0) && (arg0 != 1)) {
        switch (arg0) {
            case 2:
                arg0 = Glc_SelectRoom();
                break;

            case 3:
                arg0 = GymLeaderCastle_ShowIntro();
                break;

            case 4:
                arg0 = Glc_AdvanceRoom();
                break;
        }
    }

    gSessionContext.unk_0003 = 1;
    if (gCurrentRoomIndex < 8) {
        gSessionContext.unk_0002 = gCurrentRoomIndex;
    } else {
        gSessionContext.unk_0002 = gCurrentRoomIndex - 2;
    }
    return arg0;
}

s16 Glc_InitMenu(s16 arg0) {
    s16 i;
    s16 sp2C = 2;
    s16 var_v1 = D_84A03180.rotation;

    if (gSessionContext.unk_0002 < 8) {
        gCurrentRoomIndex = gSessionContext.unk_0002;
    } else {
        gCurrentRoomIndex = gSessionContext.unk_0002 + 2;
    }

    if (arg0 == 1) {
        sp2C = 4;
        if (gSessionContext.unk_0002 < 8) {
            var_v1--;
        }
    }

    if (var_v1 >= 8) {
        gBgFadeAlpha = 0xFF;
    } else {
        gBgFadeAlpha = 0;
    }

    for (i = 0; i <= var_v1; i++) {
        gRoomDefinitions[i].unk_01 = 1;
    }

    if (gRoomDefinitions[8].unk_01 != 0) {
        gRoomDefinitions[9].unk_01 = 1;
        gRoomDefinitions[10].unk_01 = 1;
    }

    for (i = 0; i < 4; i++) {
        gTrainerPortraits[i].posX = 0;
    }

    for (i = 0; i < 8; i++) {
        gRoomDefinitions[i].unk_24 = BinArchive_GetFile(gPortraitGfxArchive, i + 2);
    }

    gRoomDefinitions[10].unk_24 = D_300CC10;
    gRoomDefinitions[11].unk_24 = BinArchive_GetFile(gPortraitGfxArchive, 0xE);
    return sp2C;
}

s32 GymLeaderCastle_Main(s32 arg0, UNUSED s32 arg1) {
    s16 sp1E;

    main_pool_push_state('PNLV');

    Font_Init(0x3C, 0);
    ASSET_LOAD(D_1000000, common_menu1_ui, 0);
    ASSET_LOAD(D_3000000, gym_leader_castle_ui, 0);
    Text_InitStringTables();
    gGymMessageBank = Text_GetStringTable(0x19);
    gRoomMessageBank = Text_GetStringTable(0x22);
    Save_EnsureBankLoaded(2);
    Save_GetModeSettings(&D_84A03180, gSessionContext.inRound2);
    gTrainerDataArchive = BinArchive_Open(0x898000, NULL, 1, 1);
    gPortraitGfxArchive = ASSET_LOAD2(battle_portraits, 1, 1);
    D_84A03170 = ASSET_LOAD2(backgrounds, 1, 1);
    gBgTexture1 = BinArchive_GetFile(D_84A03170, 0xD);
    gBgTexture2 = BinArchive_GetFile(D_84A03170, 0x10);
    gBgTexture3 = BinArchive_GetFile(D_84A03170, 0xE);
    StageLoader_UpdateSegments();

    sp1E = Glc_InitMenu(arg0);
    if (D_84A03180.rotation < 8) {
        Audio_PlayMusicIfChanged(0x2A);
    } else {
        Audio_PlayMusicIfChanged(0x27);
    }

    sp1E = Glc_RunMenu(sp1E);
    StageLoader_WaitForRetrace();
    Font_Free();

    main_pool_pop_state('PNLV');
    return sp1E == 0;
}
