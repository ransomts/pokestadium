#include "src/fragments/rental_team_selection/rental_team_selection.h"
#include "src/1AB70.h"
#include "src/1CF30.h"
#include "src/20470.h"
#include "src/232C0.h"
#include "src/2E110.h"
#include "src/49790.h"
#include "src/6BC0.h"

void Rental_DrawBoxTabFrame(s16 arg0, s16 arg1, s16 arg2) {
    gSPDisplayList(gDisplayListHead++, gPrefDL_Border);
    gDPSetEnvColor(gDisplayListHead++, 0, 0, 0, 255);

    Gfx_DrawTextureI4(arg0, arg1, 0x10, 0x1C, D_20007C0, 0x10, 0);
    Gfx_DrawTextureI4((arg0 + arg2) - 0x10, arg1, 0x10, 0x1C, D_20008A0, 0x10, 0);
    Gfx_DrawTexturedRectClipped(arg0 + 0x10, arg1, arg2 - 0x20, 0x1C, 0, 0, 0, 0x400, 0);

    gSPDisplayList(gDisplayListHead++, gPrefDL_End);
}

void Rental_DrawBoxTab(s16 arg0, s16 arg1, u8* arg2, s16 arg3) {
    if (arg3 == 0) {
        gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 150);
    } else {
        gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255);
    }
    Gfx_DrawTextureRgba16(arg0, arg1, 0x24, 0x14, arg2, 0x24, 0);
}

void Rental_DrawBoxTabs(unk_D_842168A0* arg0) {
    s16 temp_s0 = arg0->unk_00014 - 0x2C;
    s16 sp3C = arg0->unk_00016 - 0x20;

    Rental_DrawBoxTabFrame(temp_s0, sp3C, 0x208);

    gSPDisplayList(gDisplayListHead++, gPrefDL_Border);

    Rental_DrawBoxTab(temp_s0 + 8, sp3C + 4, D_2001A20, arg0->unk_0001C[0].posX);
    Rental_DrawBoxTab(temp_s0 + 0x2C, sp3C + 4, D_2002560, arg0->unk_0001C[1].posX);
    Rental_DrawBoxTab(temp_s0 + 0x50, sp3C + 4, D_2002B00, arg0->unk_0001C[2].posX);
    Rental_DrawBoxTab(temp_s0 + 0x74, sp3C + 4, D_20030A0, arg0->unk_0001C[3].posX);
    Rental_DrawBoxTab(temp_s0 + 0x98, sp3C + 4, D_2003640, arg0->unk_0001C[4].posX);
    Rental_DrawBoxTab(temp_s0 + 0xBC, sp3C + 4, D_2003BE0, arg0->unk_0001C[5].posX);
    Rental_DrawBoxTab(temp_s0 + 0xE0, sp3C + 4, D_2004180, arg0->unk_0001C[6].posX);
    Rental_DrawBoxTab(temp_s0 + 0x104, sp3C + 4, D_2004720, arg0->unk_0001C[7].posX);
    Rental_DrawBoxTab(temp_s0 + 0x128, sp3C + 4, D_2004CC0, arg0->unk_0001C[8].posX);
    Rental_DrawBoxTab(temp_s0 + 0x14C, sp3C + 4, D_2005260, arg0->unk_0001C[9].posX);
    Rental_DrawBoxTab(temp_s0 + 0x170, sp3C + 4, D_2005800, arg0->unk_0001C[10].posX);
    Rental_DrawBoxTab(temp_s0 + 0x194, sp3C + 4, D_2005DA0, arg0->unk_0001C[11].posX);
    Rental_DrawBoxTab(temp_s0 + 0x1B8, sp3C + 4, D_2006340, arg0->unk_0001C[12].posX);
    Rental_DrawBoxTab(temp_s0 + 0x1DC, sp3C + 4, D_2001FC0, 0x97);

    if (arg0->unk_00001 != 7) {
        Gfx_DrawTextureRgba16(temp_s0 + (arg0->unk_00005 * 0x24) + 4, sp3C, 0x2C, 0xE, D_2001080, 0x2C, 0);
        Gfx_DrawTextureRgba16(temp_s0 + (arg0->unk_00005 * 0x24) + 4, sp3C + 0xE, 0x2C, 0xE, D_2001550, 0x2C, 0);
    }

    gSPDisplayList(gDisplayListHead++, gPrefDL_End);
}

s32 Rental_CountAvailableBoxes(unk_D_842168A0* arg0) {
    s16 i;
    s16 var_v1 = 1;

    for (i = 0; i < 13; i++) {
        if (arg0->unk_0001C[i].posX != 0) {
            var_v1++;
        }
    }

    return var_v1;
}

s32 Rental_GetBoxNameColorIndex(unk_D_838067F0_0168* arg0) {
    s32 ret;

    switch (arg0->boxIndex) {
        case 0:
            ret = 0;
            break;

        case 13:
            ret = 2;
            break;

        default:
            ret = 1;
            break;
    }

    return ret;
}

void Rental_DrawBoxNameBanner(s16 arg0, s16 arg1, unk_D_838067F0_0168* arg2) {
    static Color_RGB8 D_842115D0[] = {
        { 0xB4, 0x3C, 0x3C },
        { 0xBE, 0x96, 0x32 },
        { 0xAA, 0x3C, 0x96 },
    };
    static Color_RGB8 D_842115DC[] = {
        { 0x3C, 0x14, 0x14 },
        { 0x46, 0x32, 0x1E },
        { 0x50, 0x28, 0x3C },
    };

    char sp58[256];
    char* sp54;
    s32 temp_v0;

    temp_v0 = Rental_GetBoxNameColorIndex(arg2);

    gSPDisplayList(gDisplayListHead++, gDL_XluBorder);

    gDPSetEnvColor(gDisplayListHead++, D_842115D0[temp_v0].r, D_842115D0[temp_v0].g, D_842115D0[temp_v0].b, 255);
    gDPSetPrimColor(gDisplayListHead++, 0, 0, D_842115DC[temp_v0].r, D_842115DC[temp_v0].g, D_842115DC[temp_v0].b, 255);

    Gfx_DrawTextureIa8(arg0, arg1, 8, 0x1C, D_2000980, 8, 0);
    Gfx_DrawTextureIa8(arg0 + 0x184, arg1, 8, 0x1C, D_2000A60, 8, 0);
    Gfx_DrawTexturedRectClipped(arg0 + 8, arg1, 0x17C, 0x1C, 0, 0, 0, 0x400, 0);

    gSPDisplayList(gDisplayListHead++, gPrefDL_End);

    Font_BeginTranslucentTextRendering();
    Font_SetActive(8, 0);

    switch (arg2->boxIndex) {
        case 0:
            sp54 = TeamSelection_GetLabelText(0x12);
            break;

        case 13:
            sp54 = TeamSelection_GetLabelText(0x13);
            break;

        default:
            Text_SetNumberToken(1, arg2->boxIndex);
            sp54 = TeamSelection_FormatText(sp58, 0x100, 0x14);
            break;
    }

    Font_Printf((arg0 - (Font_MeasureTextExtent(8, 0, sp54) / 2)) + 0xC6, arg1 + 4, sp54);
    Font_EndTexturedTextRendering();
}

void Rental_DrawCarouselScrollbar(s16 arg0, s16 arg1, unk_D_842168A0* arg2) {
    static s16 D_842115E8 = 0;

    s16 sp5E;
    s16 temp_a3;
    s16 var_v1;

    temp_a3 = arg2->unk_00006 + arg2->unk_0000E;

    if (arg2->unk_00005 < 0xD) {
        var_v1 = ((arg2->unk_0001C[arg2->unk_00005].posX + 2) / 3);
    } else {
        var_v1 = ((arg2->roster->posX + 2) / 3);
    }

    if (var_v1 < 4) {
        var_v1 = 4;
    }

    if ((arg2->unk_00001 == 8) || (arg2->unk_00001 == 0xA)) {
        if (arg2->unk_00018 > 0) {
            sp5E = ((((temp_a3 * 4) + arg2->unk_00018) * 0x98) - 0x260) / ((var_v1 * 4) - 4);
        } else {
            sp5E = ((((temp_a3 * 4) + arg2->unk_00018) * 0x98) + 0x260) / ((var_v1 * 4) - 4);
        }
    } else {
        sp5E = (temp_a3 * 0x98) / (var_v1 - 1);
    }

    gSPDisplayList(gDisplayListHead++, gMenuDL_BackgroundFill);

    Gfx_FillRectRgb(arg0, arg1, 0x18, 0xCC, 0x3C, 0x3C, 0xA0);

    gSPDisplayList(gDisplayListHead++, gDL_XluBorder);

    gDPSetEnvColor(gDisplayListHead++, 130, 130, 220, 255);
    gDPSetPrimColor(gDisplayListHead++, 0, 0, 60, 60, 150, 255);

    Gfx_DrawTextureIa8(arg0 + 4, arg1 + 0x20, 0x10, 8, D_200A200, 0x10, 0);
    Gfx_DrawTextureIa8(arg0 + 4, arg1 + 0xC0, 0x10, 8, D_200A280, 0x10, 0);
    Gfx_DrawTexturedRectClipped(arg0 + 4, arg1 + 0x28, 0x10, 0x98, 0, 0, 0x400, 0, 0);

    gSPDisplayList(gDisplayListHead++, gPrefDL_Border);

    if (D_842115E8 < 4) {
        Gfx_DrawTextureRgba16(arg0, arg1 + sp5E + 0x1C, 0x18, 0x18, D_200A300, 0x18, 0);
    } else {
        Gfx_DrawTextureRgba16(arg0, arg1 + sp5E + 0x1C, 0x18, 0x18, D_200A780, 0x18, 0);
    }

    gSPDisplayList(gDisplayListHead++, gPrefDL_End);

    if (arg2->unk_00001 == 3) {
        D_842115E8 = (D_842115E8 + 1) % 8;
    }
}

void Rental_DrawBoxMonRow(unk_D_842168A0* arg0, s16 arg1, s16 arg2, unk_D_838067F0_0168* arg3) {
    s32 i;

    for (i = 0; i < 3; i++) {
        if ((arg3->unk_0000[i].unk_004.posX.posX != 0) &&
            (Rental_CanAddMonToTeam(arg0->teamTray, &arg3->unk_0000[i & 0xFFFFFFFF]) != 0)) {
            TeamSelection_DrawColoredFrame(arg1 + i * 0x84, arg2, 0x84, 0x2C, 0x64, 0x64, 0xC8, 0xFF);
        } else {
            TeamSelection_DrawColoredFrame(arg1 + i * 0x84, arg2, 0x84, 0x2C, 0x3C, 0x3C, 0xA0, 0xFF);
        }
    }

    gSPDisplayList(gDisplayListHead++, gPrefDL_Border);

    for (i = 0; i < 3; i++) {
        if (arg3->unk_0000[i].unk_004.posX.posX != 0) {
            Gfx_DrawTextureRgba16(arg1 + (i * 0x84) + 2, arg2 + 2, 0x28, 0x28, arg3->unk_0000[i].unk_058, 0x28, 0);
        }
    }

    gDPSetCombineLERP(gDisplayListHead++, ENVIRONMENT, PRIMITIVE, TEXEL0, PRIMITIVE, TEXEL0, 0, ENVIRONMENT, 0,
                      ENVIRONMENT, PRIMITIVE, TEXEL0, PRIMITIVE, TEXEL0, 0, ENVIRONMENT, 0);
    gDPSetEnvColor(gDisplayListHead++, 140, 220, 240, 255);
    gDPSetPrimColor(gDisplayListHead++, 0, 0, 40, 100, 220, 255);

    for (i = 0; i < 3; i++) {
        if (Rental_TeamContainsMon(arg0->teamTray, &arg3->unk_0000[i & 0xFFFFFFFF]) != 0) {
            Gfx_DrawTextureIa8(arg1 + (i * 0x84) + 0x2E, arg2 + 0xB, 0x48, 0x1C, D_200AC00, 0x48, 0);
        }
    }

    gSPDisplayList(gDisplayListHead++, gPrefDL_End);

    Font_BeginTranslucentTextRendering();

    for (i = 0; i < 3; i++) {
        if ((arg3->unk_0000[i].unk_004.posX.posX != 0) &&
            (Rental_TeamContainsMon(arg0->teamTray, &arg3->unk_0000[i & 0xFFFFFFFF]) == 0)) {
            if (Rental_CanAddMonToTeam(arg0->teamTray, &arg3->unk_0000[i & 0xFFFFFFFF]) != 0) {
                Text_SetEnvColor(0xFF, 0xFF, 0xFF, 0xFF);
            } else {
                Text_SetEnvColor(0x32, 0x32, 0xC8, 0x80);
            }
            Font_SetActive(4, 0);
            Font_Printf(arg1 + (i * 0x84) + 0x2C, arg2 + 5, arg3->unk_0000[i].unk_004.unk_30);
            Font_SetActive(4, 0);
            Font_Printf(arg1 + (i * 0x84) + 0x2C, arg2 + 0x17, "%s%d", TeamSelection_GetInstructionText(0x15),
                          arg3->unk_0000[i].unk_004.unk_24);
        }
    }

    Font_EndTexturedTextRendering();
}

void Rental_CarouselDraw(unk_D_842168A0* arg0, s32 arg1) {
    unk_D_838067F0_0168* var_s1_2;
    s16 i;
    s16 spB0;
    s16 temp_s3_3;
    s16 temp_s7;

    spB0 = arg0->unk_00014;
    temp_s7 = arg0->unk_00016;

    if ((arg0->unk_00001 != 1) && (arg0->unk_00001 != 2) && ((arg1 != 0) || (arg0->redrawTimer != 0))) {
        Rental_DrawBoxTabs(arg0);

        TeamSelection_DrawCornerFrame(spB0, temp_s7, 0x1B4, 0xD4);
        Rental_DrawCarouselScrollbar(spB0 + 4, temp_s7 + 4, arg0);

        gSPDisplayList(gDisplayListHead++, gPrefDL_Border);

        if (Rental_CountAvailableBoxes(arg0) >= 2) {
            Gfx_DrawTextureRgba16(spB0 - 0x32, temp_s7 + 0x52, 0x30, 0x18, D_2007E00, 0x30, 0);
            Gfx_DrawTextureRgba16(spB0 - 0x32, temp_s7 + 0x6A, 0x30, 0x18, D_2008700, 0x30, 0);
            Gfx_DrawTextureRgba16(spB0 + 0x1BA, temp_s7 + 0x52, 0x30, 0x18, D_2009000, 0x30, 0);
            Gfx_DrawTextureRgba16(spB0 + 0x1BA, temp_s7 + 0x6A, 0x30, 0x18, D_2009900, 0x30, 0);
        }

        gSPDisplayList(gDisplayListHead++, gMenuDL_BackgroundFill);

        Gfx_FillRectRgb(spB0 + 0x1C, temp_s7 + 4, 8, 0xCC, 0x32, 0x32, 0x32);

        gSPDisplayList(gDisplayListHead++, gPrefDL_End);

        if (arg0->unk_00001 == 7) {
            s16 sp9E = spB0 - ((arg0->unk_00018 * 0x194) / 8);
            s16 tmp3 = (((arg0->unk_0001A > 0) ? 0x194 : -0x194) + sp9E);
            s32 pad;

            Gfx_SetScissorRect(&gDisplayListHead, spB0 + 0x24, temp_s7 + 4, 0x18C, 0xCC);
            Rental_DrawBoxNameBanner(sp9E + 0x24, temp_s7 + 4, arg0->currentPage->prevPage);
            Rental_DrawBoxNameBanner(tmp3 + 0x24, temp_s7 + 4, arg0->currentPage);

            gSPDisplayList(gDisplayListHead++, gPrefDL_Border);
            gDPLoadTextureBlock(gDisplayListHead++, D_2000C40, G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 4, 0,
                                G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK,
                                G_TX_NOLOD, G_TX_NOLOD);

            Gfx_DrawTexturedRectClipped(sp9E + 0x1B0, temp_s7 + 4, 8, 0xCC, 0, 0, 0x400, 0, 0);
            Gfx_DrawTexturedRectClipped(tmp3 + 0x1B0, temp_s7 + 4, 8, 0xCC, 0, 0, 0x400, 0, 0);

            gSPDisplayList(gDisplayListHead++, gPrefDL_End);

            var_s1_2 = arg0->currentPage;
            for (i = 0; i < 4; i++) {
                Rental_DrawBoxMonRow(arg0, tmp3 + 0x24, temp_s7 + (i * 0x2C) + 0x20, var_s1_2);
                var_s1_2 = var_s1_2->nextPage;
            }

            for (i = 0; i < 4; i++) {
                Rental_DrawBoxMonRow(arg0, sp9E + 0x24, temp_s7 + (i * 0x2C) + 0x20, var_s1_2);
                var_s1_2 = var_s1_2->nextPage;
            }

            Gfx_SetScissorRect(&gDisplayListHead, 0, 0, 0x280, 0x1E0);
        } else if (arg0->unk_00001 == 8) {
            temp_s3_3 = temp_s7 - ((arg0->unk_00018 * 0x2C) / 4);
            Rental_DrawBoxNameBanner(spB0 + 0x24, temp_s7 + 4, arg0->currentPage);
            Gfx_SetScissorRect(&gDisplayListHead, spB0 + 0x24, temp_s7 + 0x20, 0x18C, 0xB0);
            if (arg0->unk_0001A > 0) {
                var_s1_2 = arg0->currentPage->prevPage;
                for (i = 0; i < 5; i++) {
                    Rental_DrawBoxMonRow(arg0, spB0 + 0x24, temp_s3_3 + (i * 0x2C) + 0x20, var_s1_2);
                    var_s1_2 = var_s1_2->nextPage;
                }
            } else {
                var_s1_2 = arg0->currentPage;
                for (i = 0; i < 5; i++) {
                    Rental_DrawBoxMonRow(arg0, spB0 + 0x24, (temp_s3_3 + (i * 0x2C)) - 0xC, var_s1_2);
                    var_s1_2 = var_s1_2->nextPage;
                }
            }
            Gfx_SetScissorRect(&gDisplayListHead, 0, 0, 0x280, 0x1E0);
        } else {
            Rental_DrawBoxNameBanner(spB0 + 0x24, temp_s7 + 4, arg0->currentPage);
            var_s1_2 = arg0->currentPage;

            for (i = 0; i < 4; i++) {
                Rental_DrawBoxMonRow(arg0, spB0 + 0x24, temp_s7 + (i * 0x2C) + 0x20, var_s1_2);
                var_s1_2 = var_s1_2->nextPage;
            }
        }

        if (arg0->unk_00001 == 0xA) {
            s16 tmp1 = (arg0->unk_0000C * 0x84) + 0x24;
            s16 tmp2 = (arg0->unk_0000E * 0x2C) + 0x20;

            if (arg0->unk_00018 > 0) {
                tmp2 = ((tmp2 + ((arg0->unk_00018 * 0x2C) / 4)) - 0x2C);
            } else {
                tmp2 = (tmp2 + ((arg0->unk_00018 * 0x2C) / 4) + 0x2C);
            }
            TeamSelection_DrawAnimatedGoldCorners(spB0 + tmp1, temp_s7 + tmp2, 0x84, 0x2C);
        } else if (arg0->unk_00001 == 9) {
            s16 tmp1 = (arg0->unk_0000C * 0x84) + 0x24;
            s16 tmp2 = (arg0->unk_0000E * 0x2C) + 0x20;

            if (arg0->unk_00018 > 0) {
                tmp1 = ((tmp1 + ((arg0->unk_00018 * 0x84) / 4)) - 0x84);
            } else {
                tmp1 = (tmp1 + ((arg0->unk_00018 * 0x84) / 4) + 0x84);
            }
            TeamSelection_DrawAnimatedGoldCorners(spB0 + tmp1, temp_s7 + tmp2, 0x84, 0x2C);
        } else if ((arg0->unk_00001 == 3) || (arg0->unk_00001 == 8)) {
            s16 tmp1 = (arg0->unk_0000C * 0x84) + 0x24;
            s16 tmp2 = (arg0->unk_0000E * 0x2C) + 0x20;

            TeamSelection_DrawAnimatedGoldCorners(spB0 + tmp1, temp_s7 + tmp2, 0x84, 0x2C);
        }

        if (arg0->redrawTimer > 0) {
            arg0->redrawTimer--;
        }
    }
}

void func_84209CEC(void) {
}

unk_D_838067F0_0168* Rental_GetPage(unk_D_838067F0_0168* arg0, s32 arg1) {
    while (arg1-- > 0) {
        arg0 = arg0->nextPage;
    }

    return arg0;
}

void Rental_MarkMatchingPlayerPikachu(unk_D_842168A0* arg0, PokemonData* arg1) {
    Gen1StringDecodeBuffer sp38;
    Gen1StringDecodeBuffer sp28;

    if ((arg0->unk_00004 < 4) && (GbSave_GetPortGame(arg0->unk_00004) == 7) && (arg1->posX.posX == 0x19)) {
        GbSave_CopyPlayerIdentity(arg0->unk_00004, &sp28);
        _bcopy(arg1->unk_46, sp38.posY, 11);
        sp38.posX = arg1->unk_0E;
        if (GbSave_PlayerIdentityMatches(&sp38, &sp28) != 0) {
            arg1->unk_52 |= 0x80;
        }
    }
}

s32 Rental_FillPageFromRoster(unk_D_842168A0* arg0, unk_D_838067F0_0168* arg1, s32 arg2, unk_D_842168A0_0013C* arg3) {
    s16 i;
    s16 j;
    s16 var_s3;
    unk_D_838067F0_003C* temp_s5;
    DeckHandle* var_v0;

    arg1->gbPort = arg0->unk_00004;
    arg1->boxIndex = arg0->unk_00005;
    var_s3 = 0;

    for (i = 0; i < 3; i++) {
        arg1->unk_0000[i].unk_004.posX.posX = 0;
        arg1->unk_0000[i].raw = 0;
    }

    if (arg0->unk_00005 < 0xD) {
        temp_s5 = &arg0->unk_0001C[arg0->unk_00005];

        if (arg0->unk_00004 < 4) {
            if (arg0->unk_00005 == 0) {
                var_v0 = Deck_Open(0x20, arg0->unk_00004, 0, 0);
            } else {
                var_v0 = Deck_Open(0x21, arg0->unk_00004, arg0->unk_00005 - 1, 0);
            }

            if (var_v0 != NULL) {
                i = arg2 * 3;
                for (j = 0; j < 3; j++) {
                    if (i < temp_s5->posX) {
                        if (Deck_SetCursor(var_v0, temp_s5->posY[i++]) != 0) {
                            var_s3 += Deck_ReadEntries(&arg1->unk_0000[j].unk_004.posX.posX, 1, var_v0);
                        }
                    }
                }
                Deck_CloseAndFlush(var_v0);
            }
        }
    } else if (arg3 != NULL) {
        i = arg2 * 3;
        for (j = 0; j < 3; j++) {
            if (i < arg3->posX) {
                _bcopy(&arg3->rotation[i++], &arg1->unk_0000[var_s3].unk_004, sizeof(arg3->rotation[0]));
                Pokemon_SetDisplayNameFromOt(&arg1->unk_0000[var_s3++].unk_004);
            }
        }
    }

    for (i = 0; i < var_s3; i++) {
        PokeIcon_LoadModelTextureForMon(arg1->unk_0000[i].unk_058, 0, &arg1->unk_0000[i].unk_004);

        arg1->unk_0000[i].unk_000 = arg0->unk_00004;
        arg1->unk_0000[i].unk_001 = arg0->unk_00005;
        arg1->unk_0000[i].unk_002 = (arg2 * 3) + i;
        arg1->unk_0000[i].unk_003 = arg1->unk_0000[i].unk_004.posX.posX;

        arg1->unk_0000[i].unk_004.unk_53 = (arg2 * 3) + i;
        arg1->unk_0000[i].unk_004.unk_52 = (arg0->unk_00004 * 0x10) | arg0->unk_00005;

        Rental_MarkMatchingPlayerPikachu(arg0, &arg1->unk_0000[i].unk_004);
    }

    return var_s3;
}

void Rental_CarouselHiddenTick(unk_D_842168A0* arg0) {
    arg0->unk_00014 = arg0->unk_00010;
    arg0->unk_00016 = arg0->unk_00012 + 0x1E0;
}

void Rental_CarouselSettledTick(unk_D_842168A0* arg0) {
    arg0->unk_00014 = arg0->unk_00010;
    arg0->unk_00016 = arg0->unk_00012;
    if (arg0->unk_00002 != 0) {
        arg0->unk_00001 = arg0->unk_00002;
        arg0->unk_00002 = 0;
    }
}

void Rental_CarouselConfirmDialogTick(unk_D_842168A0* arg0) {
    unk_D_838067F0_0168* sp2C;
    s32 temp_v0;

    sp2C = Rental_GetPage(arg0->currentPage, arg0->unk_0000E);
    temp_v0 = TeamSelection_Preview_GetSelectionState(arg0->moveScreen);

    if (temp_v0 == 1) {
        if (Rental_AssignMonToSlot(arg0->teamTray, &sp2C->unk_0000[arg0->unk_0000C]) != 0) {
            arg0->redrawTimer = 2;
            arg0->unk_00001 = 4;
        }
    } else if ((s16)temp_v0 == 2) {
        arg0->unk_00001 = 3;
    }

    arg0->unk_00014 = arg0->unk_00010;
    arg0->unk_00016 = arg0->unk_00012;
}

void Rental_CarouselSlideInTick(unk_D_842168A0* arg0) {
    arg0->unk_0000A++;
    if (arg0->unk_0000A <= 0) {
        arg0->unk_00016 = arg0->unk_00012 + 0x1E0;
    } else if (arg0->unk_0000A == 0xA) {
        arg0->unk_00001 = 4;
        arg0->unk_0000A = 0;
        arg0->unk_00016 = arg0->unk_00012;
    } else {
        arg0->unk_00016 = (arg0->unk_00012 - (arg0->unk_0000A * 0x30)) + 0x1E0;
    }
    arg0->unk_00014 = arg0->unk_00010;
    arg0->redrawTimer = 2;
}

void Rental_CarouselSlideOutTick(unk_D_842168A0* arg0) {
    arg0->unk_0000A++;
    if (arg0->unk_0000A == 0xA) {
        arg0->unk_00001 = 2;
        arg0->unk_0000A = 0;
        arg0->unk_00016 = arg0->unk_00012 + 0x1E0;
    } else {
        arg0->unk_00016 = arg0->unk_00012 + (arg0->unk_0000A * 0x30);
    }
    arg0->unk_00014 = arg0->unk_00010;
    arg0->redrawTimer = 2;
}

void Rental_CarouselConfirmMon(unk_D_842168A0* arg0) {
    unk_D_838067F0_0168* sp3C = Rental_GetPage(arg0->currentPage, arg0->unk_0000E);
    s32 var_t1;
    s16 tmp1;
    s16 tmp2;

    if (Rental_CanAddMonToTeam(arg0->teamTray, &sp3C->unk_0000[arg0->unk_0000C]) != 0) {
        if (arg0->unk_00000 == 0) {
            var_t1 = 1;
        } else {
            var_t1 = 3;
        }

        tmp1 = arg0->unk_00010 + (arg0->unk_0000C * 0x84) + 0x20;
        tmp2 = arg0->unk_00012 + (arg0->unk_0000E * 0x2C) + 0x1C;
        tmp1 = TeamSelection_Preview_StartFull(arg0->moveScreen, arg0->unk_00003, 0x30, 0xEC, tmp1, tmp2, &sp3C->unk_0000[arg0->unk_0000C],
                             var_t1);

        if (tmp1 != 0) {
            Audio_PlaySoundEffectById(2);
            arg0->unk_00001 = 0xB;
        }
    } else {
        Audio_PlaySoundEffectById(8);
    }
}

void Rental_CarouselCursorUp(unk_D_842168A0* arg0) {
    if (arg0->repeatDelay == 0) {
        if (arg0->unk_0000E != 0) {
            arg0->unk_0000E--;
            arg0->unk_00018 = -1;
            arg0->unk_0001A = -4;
            arg0->unk_00001 = 0xA;
            Audio_PlaySoundEffectById(1);
        } else if ((arg0->unk_00006 > 0) &&
                   (Rental_FillPageFromRoster(arg0, arg0->currentPage->prevPage, arg0->unk_00006 - 1, arg0->roster) != 0)) {
            arg0->unk_00006--;
            arg0->currentPage = arg0->currentPage->prevPage;
            arg0->unk_00018 = -1;
            arg0->unk_0001A = -4;
            arg0->unk_00001 = 8;
            Audio_PlaySoundEffectById(1);
        }

        arg0->repeatDelay = arg0->unk_00008;
        arg0->unk_00008 = 2;
    }
}

void Rental_CarouselCursorDown(unk_D_842168A0* arg0) {
    if (arg0->repeatDelay == 0) {
        if (arg0->unk_0000E != 3) {
            arg0->unk_0000E++;
            arg0->unk_00018 = 1;
            arg0->unk_0001A = 4;
            arg0->unk_00001 = 0xA;
            Audio_PlaySoundEffectById(1);
        } else if (Rental_FillPageFromRoster(arg0, Rental_GetPage(arg0->currentPage, 4), arg0->unk_00006 + 4, arg0->roster) != 0) {
            arg0->unk_00006++;
            arg0->currentPage = arg0->currentPage->nextPage;
            arg0->unk_00018 = 1;
            arg0->unk_0001A = 4;
            arg0->unk_00001 = 8;
            Audio_PlaySoundEffectById(1);
        }
        arg0->repeatDelay = arg0->unk_00008;
        arg0->unk_00008 = 2;
    }
}

void Rental_CarouselCursorLeft(unk_D_842168A0* arg0) {
    if (arg0->repeatDelay == 0) {
        if (arg0->unk_0000C > 0) {
            arg0->unk_0000C--;
            arg0->unk_00018 = -1;
            arg0->unk_0001A = -4;
            arg0->unk_00001 = 9;
            Audio_PlaySoundEffectById(1);
        }
        arg0->repeatDelay = arg0->unk_00008;
        arg0->unk_00008 = 2;
    }
}

void Rental_CarouselCursorRight(unk_D_842168A0* arg0) {
    if (arg0->repeatDelay == 0) {
        if (arg0->unk_0000C < 2) {
            arg0->unk_0000C++;
            arg0->unk_00018 = 1;
            arg0->unk_0001A = 4;
            arg0->unk_00001 = 9;
            Audio_PlaySoundEffectById(1);
        }
        arg0->repeatDelay = arg0->unk_00008;
        arg0->unk_00008 = 2;
    }
}

void Rental_CarouselNextBox(unk_D_842168A0* arg0) {
    s16 var_s0;
    s16 i;
    unk_D_838067F0_0168* var_s1;

    var_s0 = (arg0->unk_00005 + 1) % 14;
    while ((var_s0 < 0xD) && (arg0->unk_0001C[var_s0].posX == 0)) {
        var_s0 = (var_s0 + 1) % 14;
    }

    if (var_s0 != arg0->unk_00005) {
        Audio_PlaySoundEffectById(0x27);
        arg0->unk_00005 = var_s0;
        arg0->currentPage = Rental_GetPage(arg0->currentPage, 4);
        arg0->unk_00006 = 0;

        var_s1 = arg0->currentPage;
        for (i = 0; i < 4; i++) {
            Rental_FillPageFromRoster(arg0, var_s1, arg0->unk_00006 + i, arg0->roster);
            var_s1 = var_s1->nextPage;
        }

        arg0->unk_00018 = 0;
        arg0->unk_0001A = 8;
        arg0->unk_00001 = 7;
    }
}

void Rental_CarouselPrevBox(unk_D_842168A0* arg0) {
    s16 var_s0;
    s16 i;
    unk_D_838067F0_0168* var_s1;

    var_s0 = (arg0->unk_00005 + 0xD) % 14;
    while ((var_s0 < 0xD) && (arg0->unk_0001C[var_s0].posX == 0)) {
        var_s0 = (var_s0 + 0xD) % 14;
    }

    if (var_s0 != arg0->unk_00005) {
        Audio_PlaySoundEffectById(0x27);
        arg0->unk_00005 = var_s0;
        arg0->currentPage = Rental_GetPage(arg0->currentPage, 4);
        arg0->unk_00006 = 0;

        var_s1 = arg0->currentPage;
        for (i = 0; i < 4; i++) {
            Rental_FillPageFromRoster(arg0, var_s1, arg0->unk_00006 + i, arg0->roster);
            var_s1 = var_s1->nextPage;
        }

        arg0->unk_00018 = 0;
        arg0->unk_0001A = -8;
        arg0->unk_00001 = 7;
    }
}

void Rental_CarouselCancel(unk_D_842168A0* arg0) {
    s32 temp_v0 = Rental_RemoveHighlightedSlot(arg0->teamTray);

    if (temp_v0 != -1) {
        if (temp_v0 == 1) {
            arg0->redrawTimer = 2;
            arg0->unk_00001 = 4;
            Audio_PlaySoundEffectById(3);
        }
    } else {
        arg0->redrawTimer = 2;
        arg0->unk_0000A = 0;
        arg0->unk_00001 = 6;
        Audio_PlaySoundEffectById(3);
    }
}

void Rental_CarouselStartPressed(unk_D_842168A0* arg0) {
    if (Rental_ClearCurrentSlotSelection(arg0->teamTray) != 0) {
        arg0->redrawTimer = 2;
        arg0->unk_00001 = 4;
        Audio_PlaySoundEffectById(2);
    }
}

void Rental_CarouselHandleInput(unk_D_842168A0* arg0) {
    Controller* cont = &gControllers[arg0->unk_00003];

    if (BTN_IS_PRESSED(cont, BTN_A)) {
        Rental_CarouselConfirmMon(arg0);
    } else if (BTN_IS_PRESSED(cont, BTN_B)) {
        Rental_CarouselCancel(arg0);
    } else if (BTN_IS_PRESSED(cont, BTN_START)) {
        Rental_CarouselStartPressed(arg0);
    } else if (BTN_IS_PRESSED(cont, BTN_R)) {
        Rental_CarouselNextBox(arg0);
    } else if (BTN_IS_PRESSED(cont, BTN_L)) {
        Rental_CarouselPrevBox(arg0);
    } else if (BTN_IS_DOWN(cont, BTN_DLEFT)) {
        Rental_CarouselCursorLeft(arg0);
    } else if (BTN_IS_DOWN(cont, BTN_DRIGHT)) {
        Rental_CarouselCursorRight(arg0);
    } else if (BTN_IS_DOWN(cont, BTN_DUP)) {
        Rental_CarouselCursorUp(arg0);
    } else if (BTN_IS_DOWN(cont, BTN_DDOWN)) {
        Rental_CarouselCursorDown(arg0);
    } else {
        arg0->unk_00008 = 8;
        arg0->repeatDelay = 0;
    }

    arg0->unk_00014 = arg0->unk_00010;
    arg0->unk_00016 = arg0->unk_00012;
    arg0->redrawTimer = 2;
}

void Rental_CarouselScrollTick(unk_D_842168A0* arg0) {
    if (arg0->unk_0001A > 0) {
        arg0->unk_00018++;
        if (arg0->unk_00018 >= arg0->unk_0001A) {
            arg0->unk_00001 = 3;
        }
    } else {
        arg0->unk_00018--;
        if (arg0->unk_0001A >= arg0->unk_00018) {
            arg0->unk_00001 = 3;
        }
    }
    arg0->unk_00014 = arg0->unk_00010;
    arg0->unk_00016 = arg0->unk_00012;
    arg0->redrawTimer = 2;
}

s32 Rental_MonHasLegalMoveset(PokemonData* arg0) {
    s32 i;
    s32 var_v1 = 1;

    for (i = 0; i < 4; i++) {
        if (arg0->unk_09[i] == 0) {
            break;
        }

        if (arg0->unk_09[i] >= 0xA6) {
            var_v1 = 0;
        }
    }

    return var_v1;
}

s32 Rental_MonMeetsCategoryFilter(PokemonData* arg0, s16 arg1, s16 arg2, s16 arg3) {
    s32 sp1C = 0;

    if ((arg0->posX.posX > 0) && (arg0->posX.posX < 0x98)) {
        if ((Rental_MonHasLegalMoveset(arg0) != 0) && (D_8006FEE8[arg0->posX.posX][8] & arg3)) {
            if ((arg0->unk_24 >= arg1) && (arg2 >= arg0->unk_24)) {
                sp1C = 1;
            }
        }
    }
    return sp1C;
}

s32 Rental_BuildBoxFilterIndex(unk_D_842168A0* arg0, s16 arg1, s16 arg2) {
    unk_D_838067F0_003C* ptr = &arg0->unk_0001C[arg1];
    PokemonData sp50;
    s32 var_s0;
    s16 var_s2;
    unk_D_838067F0_003C* temp_v0;
    DeckHandle* var_v0;

    ptr->posX = 0;
    var_s2 = 0;

    if (arg0->unk_00004 < 4) {
        if (arg1 == 0) {
            var_v0 = Deck_Open(0x20, arg0->unk_00004, 0, 0);
        } else {
            var_v0 = Deck_Open(0x21, arg0->unk_00004, arg1 - 1, 0);
        }

        if (var_v0 != NULL) {
            while (Deck_ReadEntries(&sp50, 1, var_v0) == 1) {
                switch (arg2) {
                    case 0:
                        var_s0 = Rental_MonMeetsCategoryFilter(&sp50, 1, 0x64, 0x20);
                        break;

                    case 1:
                        var_s0 = Rental_MonMeetsCategoryFilter(&sp50, 0x32, 0x37, 1);
                        break;

                    case 2:
                        var_s0 = Rental_MonMeetsCategoryFilter(&sp50, 0x32, 0x37, 1);
                        break;

                    case 3:
                        var_s0 = Rental_MonMeetsCategoryFilter(&sp50, 0x32, 0x37, 1);
                        break;
                    case 4:
                        var_s0 = Rental_MonMeetsCategoryFilter(&sp50, 0x19, 0x1E, 8);
                        break;

                    case 5:
                        var_s0 = Rental_MonMeetsCategoryFilter(&sp50, 0xF, 0x14, 0x10);
                        break;

                    case 6:
                        var_s0 = Rental_MonMeetsCategoryFilter(&sp50, 1, 0x64, 0x20);
                        break;

                    case 7:
                        var_s0 = Rental_MonMeetsCategoryFilter(&sp50, 1, 0x64, 0x20);
                        break;

                    case 8:
                        var_s0 = Rental_MonMeetsCategoryFilter(&sp50, 1, 0x64, 0x20);
                        break;
                }

                if (var_s0 != 0) {
                    temp_v0 = ptr;
                    temp_v0->posY[temp_v0->posX] = var_s2;
                    temp_v0->posX += 1;
                }

                var_s2++;
            }
            Deck_CloseAndFlush(var_v0);
        }
    }
    return ptr->posX;
}

s32 Rental_PrimeCarousel(unk_D_842168A0* arg0, gItemPanel* arg1, unk_D_8423D3A8* arg2, s16 arg3, s16 arg4, s16 arg5,
                  s16 arg6, s16 arg7, unk_D_842168A0_0013C* arg8) {
    s16 i;

    arg0->unk_00000 = arg3;
    arg0->unk_00001 = 1;
    arg0->unk_00002 = 0;
    arg0->unk_00003 = arg6;
    arg0->unk_00004 = arg7;
    arg0->unk_00005 = 0xD;
    arg0->unk_00006 = 0;
    arg0->repeatDelay = 0;
    arg0->unk_00008 = 8;
    arg0->unk_0000A = 0;
    arg0->unk_0000C = 0;
    arg0->unk_0000E = 0;
    arg0->unk_00016 = arg5 + 0x1E0;
    arg0->unk_00010 = arg4;
    arg0->unk_00014 = arg4;
    arg0->unk_00012 = arg5;
    arg0->roster = arg8;
    arg0->teamTray = arg1;
    arg0->moveScreen = arg2;
    arg0->currentPage = &arg0->pages[0];

    for (i = 0; i < 8; i++) {
        arg0->pages[i].nextPage = &arg0->pages[(i + 1) & 7];
        arg0->pages[i].prevPage = &arg0->pages[(i - 1) & 7];
    }

    for (i = 12; i >= 0; i--) {
        if (Rental_BuildBoxFilterIndex(arg0, i, gSessionContext.unk_0001) > 0) {
            arg0->unk_00005 = i;
        }
    }

    for (i = 0; i < 4; i++) {
        Rental_FillPageFromRoster(arg0, &arg0->pages[i], i, arg0->roster);
    }

    return 2;
}

s32 Rental_CarouselTick(unk_D_842168A0* arg0) {
    s32 sp1C = 0;

    if (arg0->repeatDelay > 0) {
        arg0->repeatDelay--;
    }

    switch (arg0->unk_00001) {
        case 1:
            Rental_CarouselHiddenTick(arg0);
            break;

        case 2:
            Rental_CarouselHiddenTick(arg0);
            break;

        case 4:
            Rental_CarouselSettledTick(arg0);
            break;

        case 3:
            Rental_CarouselHandleInput(arg0);
            break;

        case 7:
            Rental_CarouselScrollTick(arg0);
            break;

        case 8:
            Rental_CarouselScrollTick(arg0);
            break;

        case 9:
            Rental_CarouselScrollTick(arg0);
            break;

        case 10:
            Rental_CarouselScrollTick(arg0);
            break;

        case 5:
            Rental_CarouselSlideInTick(arg0);
            sp1C = 1;
            break;

        case 6:
            Rental_CarouselSlideOutTick(arg0);
            sp1C = 1;
            break;

        case 11:
            Rental_CarouselConfirmDialogTick(arg0);
            break;
    }
    return sp1C;
}

s32 Rental_CarouselOpen(unk_D_842168A0* arg0, s16 arg1) {
    if (arg0->unk_00001 != 1) {
        return 0;
    }
    arg0->unk_00001 = 5;
    arg0->unk_0000A = -arg1;
    return 1;
}

s32 Rental_CarouselResumeAfterAssign(unk_D_842168A0* arg0) {
    if (arg0->unk_00001 != 2) {
        return 0;
    }
    arg0->unk_00001 = 5;
    arg0->unk_0000A = 0;
    return 1;
}

s32 Rental_CarouselAcknowledgeAssign(unk_D_842168A0* arg0) {
    if (arg0->unk_00001 != 4) {
        return 0;
    }
    arg0->unk_00002 = 6;
    arg0->unk_0000A = 0;
    return 1;
}

void Rental_CarouselRequestRedraw(unk_D_842168A0* arg0) {
    arg0->redrawTimer = 2;
}

void Rental_CarouselSkipToSelectableMon(unk_D_842168A0* arg0) {
    s32 i;

    for (i = 0; i < 12; i++) {
        if (Rental_CanAddMonToTeam(arg0->teamTray,
                          &Rental_GetPage(arg0->currentPage, arg0->unk_0000E)->unk_0000[arg0->unk_0000C]) != 0) {
            break;
        }

        arg0->unk_0000C++;
        if (arg0->unk_0000C == 3) {
            arg0->unk_0000C = 0;
            arg0->unk_0000E = (arg0->unk_0000E + 1) & 3;
        }
    }
}

s32 Rental_CarouselResumeInput(unk_D_842168A0* arg0) {
    if (arg0->unk_00001 == 4) {
        Rental_CarouselSkipToSelectableMon(arg0);
        arg0->unk_00002 = 3;
        return 1;
    }
    return 0;
}

s32 Rental_CarouselIsIdle(unk_D_842168A0* arg0) {
    return arg0->unk_00001 == 2;
}
