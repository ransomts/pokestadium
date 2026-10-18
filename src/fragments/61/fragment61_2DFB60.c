#include "fragment61.h"
#include "src/1AB70.h"
#include "src/1CF30.h"
#include "src/20470.h"
#include "src/232C0.h"
#include "src/2E110.h"
#include "src/49790.h"
#include "src/6BC0.h"

void DrawBoxBorder(s16 arg0, s16 arg1, s16 arg2) {
    gSPDisplayList(gDisplayListHead++, gPrefDL_Border);
    gDPSetEnvColor(gDisplayListHead++, 0, 0, 0, 255);

    Gfx_DrawSpriteI4(arg0, arg1, 0x10, 0x1C, D_20007C0, 0x10, 0);
    Gfx_DrawSpriteI4((arg0 + arg2) - 0x10, arg1, 0x10, 0x1C, D_20008A0, 0x10, 0);
    Gfx_DrawTextureRect(arg0 + 0x10, arg1, arg2 - 0x20, 0x1C, 0, 0, 0, 0x400, 0);

    gSPDisplayList(gDisplayListHead++, gPrefDL_End);
}

void DrawSlotIcon(s16 arg0, s16 arg1, u8* arg2, s16 arg3) {
    if (arg3 == 0) {
        gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 150);
    } else {
        gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255);
    }
    Gfx_DrawSpriteRGBA16(arg0, arg1, 0x24, 0x14, arg2, 0x24, 0);
}

void DrawPokemonSlots(unk_D_842168A0* arg0) {
    s16 temp_s0 = arg0->unk_00014 - 0x2C;
    s16 sp3C = arg0->unk_00016 - 0x20;

    DrawBoxBorder(temp_s0, sp3C, 0x208);

    gSPDisplayList(gDisplayListHead++, gPrefDL_Border);

    DrawSlotIcon(temp_s0 + 8, sp3C + 4, D_2001A20, arg0->unk_0001C[0].unk_00);
    DrawSlotIcon(temp_s0 + 0x2C, sp3C + 4, D_2002560, arg0->unk_0001C[1].unk_00);
    DrawSlotIcon(temp_s0 + 0x50, sp3C + 4, D_2002B00, arg0->unk_0001C[2].unk_00);
    DrawSlotIcon(temp_s0 + 0x74, sp3C + 4, D_20030A0, arg0->unk_0001C[3].unk_00);
    DrawSlotIcon(temp_s0 + 0x98, sp3C + 4, D_2003640, arg0->unk_0001C[4].unk_00);
    DrawSlotIcon(temp_s0 + 0xBC, sp3C + 4, D_2003BE0, arg0->unk_0001C[5].unk_00);
    DrawSlotIcon(temp_s0 + 0xE0, sp3C + 4, D_2004180, arg0->unk_0001C[6].unk_00);
    DrawSlotIcon(temp_s0 + 0x104, sp3C + 4, D_2004720, arg0->unk_0001C[7].unk_00);
    DrawSlotIcon(temp_s0 + 0x128, sp3C + 4, D_2004CC0, arg0->unk_0001C[8].unk_00);
    DrawSlotIcon(temp_s0 + 0x14C, sp3C + 4, D_2005260, arg0->unk_0001C[9].unk_00);
    DrawSlotIcon(temp_s0 + 0x170, sp3C + 4, D_2005800, arg0->unk_0001C[10].unk_00);
    DrawSlotIcon(temp_s0 + 0x194, sp3C + 4, D_2005DA0, arg0->unk_0001C[11].unk_00);
    DrawSlotIcon(temp_s0 + 0x1B8, sp3C + 4, D_2006340, arg0->unk_0001C[12].unk_00);
    DrawSlotIcon(temp_s0 + 0x1DC, sp3C + 4, D_2001FC0, 0x97);

    if (arg0->unk_00001 != 7) {
        Gfx_DrawSpriteRGBA16(temp_s0 + (arg0->unk_00005 * 0x24) + 4, sp3C, 0x2C, 0xE, D_2001080, 0x2C, 0);
        Gfx_DrawSpriteRGBA16(temp_s0 + (arg0->unk_00005 * 0x24) + 4, sp3C + 0xE, 0x2C, 0xE, D_2001550, 0x2C, 0);
    }

    gSPDisplayList(gDisplayListHead++, gPrefDL_End);
}

s32 CountActiveSlots(unk_D_842168A0* arg0) {
    s16 i;
    s16 var_v1 = 1;

    for (i = 0; i < 13; i++) {
        if (arg0->unk_0001C[i].unk_00 != 0) {
            var_v1++;
        }
    }

    return var_v1;
}

s32 GetBorderColorIndex(unk_D_838067F0_0168* arg0) {
    s32 ret;

    switch (arg0->unk_2692) {
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

void func_842088A0(s16 arg0, s16 arg1, unk_D_838067F0_0168* arg2) {
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

    temp_v0 = GetBorderColorIndex(arg2);

    gSPDisplayList(gDisplayListHead++, gDL_XluBorder);

    gDPSetEnvColor(gDisplayListHead++, D_842115D0[temp_v0].r, D_842115D0[temp_v0].g, D_842115D0[temp_v0].b, 255);
    gDPSetPrimColor(gDisplayListHead++, 0, 0, D_842115DC[temp_v0].r, D_842115DC[temp_v0].g, D_842115DC[temp_v0].b, 255);

    Gfx_DrawSpriteIA8(arg0, arg1, 8, 0x1C, D_2000980, 8, 0);
    Gfx_DrawSpriteIA8(arg0 + 0x184, arg1, 8, 0x1C, D_2000A60, 8, 0);
    Gfx_DrawTextureRect(arg0 + 8, arg1, 0x17C, 0x1C, 0, 0, 0, 0x400, 0);

    gSPDisplayList(gDisplayListHead++, gPrefDL_End);

    Text_ResetState();
    Text_SetFont(8, 0);

    switch (arg2->unk_2692) {
        case 0:
            sp54 = GetMessageBank1AString(0x12);
            break;

        case 13:
            sp54 = GetMessageBank1AString(0x13);
            break;

        default:
            MessageBank_SetPointer_1_9(1, arg2->unk_2692);
            sp54 = GetMessageBank1AStringCustomBuf(sp58, 0x100, 0x14);
            break;
    }

    Text_Print((arg0 - (MeasureTextWidth(8, 0, sp54) / 2)) + 0xC6, arg1 + 4, sp54);
    Text_SetupDL();
}

void func_84208B04(s16 arg0, s16 arg1, unk_D_842168A0* arg2) {
    static s16 D_842115E8 = 0;

    s16 sp5E;
    s16 temp_a3;
    s16 var_v1;

    temp_a3 = arg2->unk_00006 + arg2->unk_0000E;

    if (arg2->unk_00005 < 0xD) {
        var_v1 = ((arg2->unk_0001C[arg2->unk_00005].unk_00 + 2) / 3);
    } else {
        var_v1 = ((arg2->unk_0013C->unk_00 + 2) / 3);
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

    Gfx_FillRect(arg0, arg1, 0x18, 0xCC, 0x3C, 0x3C, 0xA0);

    gSPDisplayList(gDisplayListHead++, gDL_XluBorder);

    gDPSetEnvColor(gDisplayListHead++, 130, 130, 220, 255);
    gDPSetPrimColor(gDisplayListHead++, 0, 0, 60, 60, 150, 255);

    Gfx_DrawSpriteIA8(arg0 + 4, arg1 + 0x20, 0x10, 8, D_200A200, 0x10, 0);
    Gfx_DrawSpriteIA8(arg0 + 4, arg1 + 0xC0, 0x10, 8, D_200A280, 0x10, 0);
    Gfx_DrawTextureRect(arg0 + 4, arg1 + 0x28, 0x10, 0x98, 0, 0, 0x400, 0, 0);

    gSPDisplayList(gDisplayListHead++, gPrefDL_Border);

    if (D_842115E8 < 4) {
        Gfx_DrawSpriteRGBA16(arg0, arg1 + sp5E + 0x1C, 0x18, 0x18, D_200A300, 0x18, 0);
    } else {
        Gfx_DrawSpriteRGBA16(arg0, arg1 + sp5E + 0x1C, 0x18, 0x18, D_200A780, 0x18, 0);
    }

    gSPDisplayList(gDisplayListHead++, gPrefDL_End);

    if (arg2->unk_00001 == 3) {
        D_842115E8 = (D_842115E8 + 1) % 8;
    }
}

void DrawPokemonEntry(unk_D_842168A0* arg0, s16 arg1, s16 arg2, unk_D_838067F0_0168* arg3) {
    s32 i;

    for (i = 0; i < 3; i++) {
        if ((arg3->unk_0000[i].unk_004.unk_00.unk_00 != 0) &&
            (ItemPanel_IsItemDuplicate(arg0->unk_13608, &arg3->unk_0000[i & 0xFFFFFFFF]) != 0)) {
            DrawColoredBox(arg1 + i * 0x84, arg2, 0x84, 0x2C, 0x64, 0x64, 0xC8, 0xFF);
        } else {
            DrawColoredBox(arg1 + i * 0x84, arg2, 0x84, 0x2C, 0x3C, 0x3C, 0xA0, 0xFF);
        }
    }

    gSPDisplayList(gDisplayListHead++, gPrefDL_Border);

    for (i = 0; i < 3; i++) {
        if (arg3->unk_0000[i].unk_004.unk_00.unk_00 != 0) {
            Gfx_DrawSpriteRGBA16(arg1 + (i * 0x84) + 2, arg2 + 2, 0x28, 0x28, arg3->unk_0000[i].unk_058, 0x28, 0);
        }
    }

    gDPSetCombineLERP(gDisplayListHead++, ENVIRONMENT, PRIMITIVE, TEXEL0, PRIMITIVE, TEXEL0, 0, ENVIRONMENT, 0,
                      ENVIRONMENT, PRIMITIVE, TEXEL0, PRIMITIVE, TEXEL0, 0, ENVIRONMENT, 0);
    gDPSetEnvColor(gDisplayListHead++, 140, 220, 240, 255);
    gDPSetPrimColor(gDisplayListHead++, 0, 0, 40, 100, 220, 255);

    for (i = 0; i < 3; i++) {
        if (ItemPanel_HasItem(arg0->unk_13608, &arg3->unk_0000[i & 0xFFFFFFFF]) != 0) {
            Gfx_DrawSpriteIA8(arg1 + (i * 0x84) + 0x2E, arg2 + 0xB, 0x48, 0x1C, D_200AC00, 0x48, 0);
        }
    }

    gSPDisplayList(gDisplayListHead++, gPrefDL_End);

    Text_ResetState();

    for (i = 0; i < 3; i++) {
        if ((arg3->unk_0000[i].unk_004.unk_00.unk_00 != 0) &&
            (ItemPanel_HasItem(arg0->unk_13608, &arg3->unk_0000[i & 0xFFFFFFFF]) == 0)) {
            if (ItemPanel_IsItemDuplicate(arg0->unk_13608, &arg3->unk_0000[i & 0xFFFFFFFF]) != 0) {
                Text_SetEnvColor(0xFF, 0xFF, 0xFF, 0xFF);
            } else {
                Text_SetEnvColor(0x32, 0x32, 0xC8, 0x80);
            }
            Text_SetFont(4, 0);
            Text_Print(arg1 + (i * 0x84) + 0x2C, arg2 + 5, arg3->unk_0000[i].unk_004.unk_30);
            Text_SetFont(4, 0);
            Text_Print(arg1 + (i * 0x84) + 0x2C, arg2 + 0x17, "%s%d", GetMessageBank06String(0x15),
                          arg3->unk_0000[i].unk_004.unk_24);
        }
    }

    Text_SetupDL();
}

void DrawPokemonMenu(unk_D_842168A0* arg0, s32 arg1) {
    unk_D_838067F0_0168* var_s1_2;
    s16 i;
    s16 spB0;
    s16 temp_s3_3;
    s16 temp_s7;

    spB0 = arg0->unk_00014;
    temp_s7 = arg0->unk_00016;

    if ((arg0->unk_00001 != 1) && (arg0->unk_00001 != 2) && ((arg1 != 0) || (arg0->unk_00009 != 0))) {
        DrawPokemonSlots(arg0);

        DrawBorderedBox(spB0, temp_s7, 0x1B4, 0xD4);
        func_84208B04(spB0 + 4, temp_s7 + 4, arg0);

        gSPDisplayList(gDisplayListHead++, gPrefDL_Border);

        if (CountActiveSlots(arg0) >= 2) {
            Gfx_DrawSpriteRGBA16(spB0 - 0x32, temp_s7 + 0x52, 0x30, 0x18, D_2007E00, 0x30, 0);
            Gfx_DrawSpriteRGBA16(spB0 - 0x32, temp_s7 + 0x6A, 0x30, 0x18, D_2008700, 0x30, 0);
            Gfx_DrawSpriteRGBA16(spB0 + 0x1BA, temp_s7 + 0x52, 0x30, 0x18, D_2009000, 0x30, 0);
            Gfx_DrawSpriteRGBA16(spB0 + 0x1BA, temp_s7 + 0x6A, 0x30, 0x18, D_2009900, 0x30, 0);
        }

        gSPDisplayList(gDisplayListHead++, gMenuDL_BackgroundFill);

        Gfx_FillRect(spB0 + 0x1C, temp_s7 + 4, 8, 0xCC, 0x32, 0x32, 0x32);

        gSPDisplayList(gDisplayListHead++, gPrefDL_End);

        if (arg0->unk_00001 == 7) {
            s16 sp9E = spB0 - ((arg0->unk_00018 * 0x194) / 8);
            s16 tmp3 = (((arg0->unk_0001A > 0) ? 0x194 : -0x194) + sp9E);
            s32 pad;

            Gfx_SetScissorRect(&gDisplayListHead, spB0 + 0x24, temp_s7 + 4, 0x18C, 0xCC);
            func_842088A0(sp9E + 0x24, temp_s7 + 4, arg0->unk_00140->unk_268C);
            func_842088A0(tmp3 + 0x24, temp_s7 + 4, arg0->unk_00140);

            gSPDisplayList(gDisplayListHead++, gPrefDL_Border);
            gDPLoadTextureBlock(gDisplayListHead++, D_2000C40, G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 4, 0,
                                G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK,
                                G_TX_NOLOD, G_TX_NOLOD);

            Gfx_DrawTextureRect(sp9E + 0x1B0, temp_s7 + 4, 8, 0xCC, 0, 0, 0x400, 0, 0);
            Gfx_DrawTextureRect(tmp3 + 0x1B0, temp_s7 + 4, 8, 0xCC, 0, 0, 0x400, 0, 0);

            gSPDisplayList(gDisplayListHead++, gPrefDL_End);

            var_s1_2 = arg0->unk_00140;
            for (i = 0; i < 4; i++) {
                DrawPokemonEntry(arg0, tmp3 + 0x24, temp_s7 + (i * 0x2C) + 0x20, var_s1_2);
                var_s1_2 = var_s1_2->unk_2688;
            }

            for (i = 0; i < 4; i++) {
                DrawPokemonEntry(arg0, sp9E + 0x24, temp_s7 + (i * 0x2C) + 0x20, var_s1_2);
                var_s1_2 = var_s1_2->unk_2688;
            }

            Gfx_SetScissorRect(&gDisplayListHead, 0, 0, 0x280, 0x1E0);
        } else if (arg0->unk_00001 == 8) {
            temp_s3_3 = temp_s7 - ((arg0->unk_00018 * 0x2C) / 4);
            func_842088A0(spB0 + 0x24, temp_s7 + 4, arg0->unk_00140);
            Gfx_SetScissorRect(&gDisplayListHead, spB0 + 0x24, temp_s7 + 0x20, 0x18C, 0xB0);
            if (arg0->unk_0001A > 0) {
                var_s1_2 = arg0->unk_00140->unk_268C;
                for (i = 0; i < 5; i++) {
                    DrawPokemonEntry(arg0, spB0 + 0x24, temp_s3_3 + (i * 0x2C) + 0x20, var_s1_2);
                    var_s1_2 = var_s1_2->unk_2688;
                }
            } else {
                var_s1_2 = arg0->unk_00140;
                for (i = 0; i < 5; i++) {
                    DrawPokemonEntry(arg0, spB0 + 0x24, (temp_s3_3 + (i * 0x2C)) - 0xC, var_s1_2);
                    var_s1_2 = var_s1_2->unk_2688;
                }
            }
            Gfx_SetScissorRect(&gDisplayListHead, 0, 0, 0x280, 0x1E0);
        } else {
            func_842088A0(spB0 + 0x24, temp_s7 + 4, arg0->unk_00140);
            var_s1_2 = arg0->unk_00140;

            for (i = 0; i < 4; i++) {
                DrawPokemonEntry(arg0, spB0 + 0x24, temp_s7 + (i * 0x2C) + 0x20, var_s1_2);
                var_s1_2 = var_s1_2->unk_2688;
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
            DrawAnimatedGoldBorder(spB0 + tmp1, temp_s7 + tmp2, 0x84, 0x2C);
        } else if (arg0->unk_00001 == 9) {
            s16 tmp1 = (arg0->unk_0000C * 0x84) + 0x24;
            s16 tmp2 = (arg0->unk_0000E * 0x2C) + 0x20;

            if (arg0->unk_00018 > 0) {
                tmp1 = ((tmp1 + ((arg0->unk_00018 * 0x84) / 4)) - 0x84);
            } else {
                tmp1 = (tmp1 + ((arg0->unk_00018 * 0x84) / 4) + 0x84);
            }
            DrawAnimatedGoldBorder(spB0 + tmp1, temp_s7 + tmp2, 0x84, 0x2C);
        } else if ((arg0->unk_00001 == 3) || (arg0->unk_00001 == 8)) {
            s16 tmp1 = (arg0->unk_0000C * 0x84) + 0x24;
            s16 tmp2 = (arg0->unk_0000E * 0x2C) + 0x20;

            DrawAnimatedGoldBorder(spB0 + tmp1, temp_s7 + tmp2, 0x84, 0x2C);
        }

        if (arg0->unk_00009 > 0) {
            arg0->unk_00009--;
        }
    }
}

void func_84209CEC(void) {
}

unk_D_838067F0_0168* GetPokemonNode(unk_D_838067F0_0168* arg0, s32 arg1) {
    while (arg1-- > 0) {
        arg0 = arg0->unk_2688;
    }

    return arg0;
}

void CheckHeldItemEffect(unk_D_842168A0* arg0, PokemonData* arg1) {
    Gen1StringDecodeBuffer sp38;
    Gen1StringDecodeBuffer sp28;

    if ((arg0->unk_00004 < 4) && (MenuItem_GetHeldItemId(arg0->unk_00004) == 7) && (arg1->unk_00.unk_00 == 0x19)) {
        Controller_ReadInput(arg0->unk_00004, &sp28);
        _bcopy(arg1->unk_46, sp38.unk_02, 11);
        sp38.unk_00 = arg1->unk_0E;
        if (IsPokemonNameMatch(&sp38, &sp28) != 0) {
            arg1->unk_52 |= 0x80;
        }
    }
}

s32 LoadPokemonIntoSlots(unk_D_842168A0* arg0, unk_D_838067F0_0168* arg1, s32 arg2, unk_D_842168A0_0013C* arg3) {
    s16 i;
    s16 j;
    s16 var_s3;
    unk_D_838067F0_003C* temp_s5;
    unk_func_80022C28_ret* var_v0;

    arg1->unk_2690 = arg0->unk_00004;
    arg1->unk_2692 = arg0->unk_00005;
    var_s3 = 0;

    for (i = 0; i < 3; i++) {
        arg1->unk_0000[i].unk_004.unk_00.unk_00 = 0;
        arg1->unk_0000[i].raw = 0;
    }

    if (arg0->unk_00005 < 0xD) {
        temp_s5 = &arg0->unk_0001C[arg0->unk_00005];

        if (arg0->unk_00004 < 4) {
            if (arg0->unk_00005 == 0) {
                var_v0 = CreateGbsBlock(0x20, arg0->unk_00004, 0, 0);
            } else {
                var_v0 = CreateGbsBlock(0x21, arg0->unk_00004, arg0->unk_00005 - 1, 0);
            }

            if (var_v0 != NULL) {
                i = arg2 * 3;
                for (j = 0; j < 3; j++) {
                    if (i < temp_s5->unk_00) {
                        if (GbsBlock_SetLimit(var_v0, temp_s5->unk_02[i++]) != 0) {
                            var_s3 += GbsBlock_ReadPokemon(&arg1->unk_0000[j].unk_004.unk_00.unk_00, 1, var_v0);
                        }
                    }
                }
                CommitAndFreeGbsBlock(var_v0);
            }
        }
    } else if (arg3 != NULL) {
        i = arg2 * 3;
        for (j = 0; j < 3; j++) {
            if (i < arg3->unk_00) {
                _bcopy(&arg3->unk_04[i++], &arg1->unk_0000[var_s3].unk_004, sizeof(arg3->unk_04[0]));
                SetMonNickname(&arg1->unk_0000[var_s3++].unk_004);
            }
        }
    }

    for (i = 0; i < var_s3; i++) {
        func_8001B0DC(arg1->unk_0000[i].unk_058, 0, &arg1->unk_0000[i].unk_004);

        arg1->unk_0000[i].unk_000 = arg0->unk_00004;
        arg1->unk_0000[i].unk_001 = arg0->unk_00005;
        arg1->unk_0000[i].unk_002 = (arg2 * 3) + i;
        arg1->unk_0000[i].unk_003 = arg1->unk_0000[i].unk_004.unk_00.unk_00;

        arg1->unk_0000[i].unk_004.unk_53 = (arg2 * 3) + i;
        arg1->unk_0000[i].unk_004.unk_52 = (arg0->unk_00004 * 0x10) | arg0->unk_00005;

        CheckHeldItemEffect(arg0, &arg1->unk_0000[i].unk_004);
    }

    return var_s3;
}

void ResetMenuPosition(unk_D_842168A0* arg0) {
    arg0->unk_00014 = arg0->unk_00010;
    arg0->unk_00016 = arg0->unk_00012 + 0x1E0;
}

void ResetMenuPositionAndState(unk_D_842168A0* arg0) {
    arg0->unk_00014 = arg0->unk_00010;
    arg0->unk_00016 = arg0->unk_00012;
    if (arg0->unk_00002 != 0) {
        arg0->unk_00001 = arg0->unk_00002;
        arg0->unk_00002 = 0;
    }
}

void HandleMoveSelection(unk_D_842168A0* arg0) {
    unk_D_838067F0_0168* sp2C;
    s32 temp_v0;

    sp2C = GetPokemonNode(arg0->unk_00140, arg0->unk_0000E);
    temp_v0 = GetSelectedMoveIndex(arg0->unk_1360C);

    if (temp_v0 == 1) {
        if (ItemPanel_AddItem(arg0->unk_13608, &sp2C->unk_0000[arg0->unk_0000C]) != 0) {
            arg0->unk_00009 = 2;
            arg0->unk_00001 = 4;
        }
    } else if ((s16)temp_v0 == 2) {
        arg0->unk_00001 = 3;
    }

    arg0->unk_00014 = arg0->unk_00010;
    arg0->unk_00016 = arg0->unk_00012;
}

void ScrollMenuUp(unk_D_842168A0* arg0) {
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
    arg0->unk_00009 = 2;
}

void ScrollMenuDown(unk_D_842168A0* arg0) {
    arg0->unk_0000A++;
    if (arg0->unk_0000A == 0xA) {
        arg0->unk_00001 = 2;
        arg0->unk_0000A = 0;
        arg0->unk_00016 = arg0->unk_00012 + 0x1E0;
    } else {
        arg0->unk_00016 = arg0->unk_00012 + (arg0->unk_0000A * 0x30);
    }
    arg0->unk_00014 = arg0->unk_00010;
    arg0->unk_00009 = 2;
}

void SelectPokemon(unk_D_842168A0* arg0) {
    unk_D_838067F0_0168* sp3C = GetPokemonNode(arg0->unk_00140, arg0->unk_0000E);
    s32 var_t1;
    s16 tmp1;
    s16 tmp2;

    if (ItemPanel_IsItemDuplicate(arg0->unk_13608, &sp3C->unk_0000[arg0->unk_0000C]) != 0) {
        if (arg0->unk_00000 == 0) {
            var_t1 = 1;
        } else {
            var_t1 = 3;
        }

        tmp1 = arg0->unk_00010 + (arg0->unk_0000C * 0x84) + 0x20;
        tmp2 = arg0->unk_00012 + (arg0->unk_0000E * 0x2C) + 0x1C;
        tmp1 = MoveScreen_Start(arg0->unk_1360C, arg0->unk_00003, 0x30, 0xEC, tmp1, tmp2, &sp3C->unk_0000[arg0->unk_0000C],
                             var_t1);

        if (tmp1 != 0) {
            PlaySoundEffect(2);
            arg0->unk_00001 = 0xB;
        }
    } else {
        PlaySoundEffect(8);
    }
}

void MoveCursorUp(unk_D_842168A0* arg0) {
    if (arg0->unk_00007 == 0) {
        if (arg0->unk_0000E != 0) {
            arg0->unk_0000E--;
            arg0->unk_00018 = -1;
            arg0->unk_0001A = -4;
            arg0->unk_00001 = 0xA;
            PlaySoundEffect(1);
        } else if ((arg0->unk_00006 > 0) &&
                   (LoadPokemonIntoSlots(arg0, arg0->unk_00140->unk_268C, arg0->unk_00006 - 1, arg0->unk_0013C) != 0)) {
            arg0->unk_00006--;
            arg0->unk_00140 = arg0->unk_00140->unk_268C;
            arg0->unk_00018 = -1;
            arg0->unk_0001A = -4;
            arg0->unk_00001 = 8;
            PlaySoundEffect(1);
        }

        arg0->unk_00007 = arg0->unk_00008;
        arg0->unk_00008 = 2;
    }
}

void MoveCursorDown(unk_D_842168A0* arg0) {
    if (arg0->unk_00007 == 0) {
        if (arg0->unk_0000E != 3) {
            arg0->unk_0000E++;
            arg0->unk_00018 = 1;
            arg0->unk_0001A = 4;
            arg0->unk_00001 = 0xA;
            PlaySoundEffect(1);
        } else if (LoadPokemonIntoSlots(arg0, GetPokemonNode(arg0->unk_00140, 4), arg0->unk_00006 + 4, arg0->unk_0013C) != 0) {
            arg0->unk_00006++;
            arg0->unk_00140 = arg0->unk_00140->unk_2688;
            arg0->unk_00018 = 1;
            arg0->unk_0001A = 4;
            arg0->unk_00001 = 8;
            PlaySoundEffect(1);
        }
        arg0->unk_00007 = arg0->unk_00008;
        arg0->unk_00008 = 2;
    }
}

void MoveCursorLeft(unk_D_842168A0* arg0) {
    if (arg0->unk_00007 == 0) {
        if (arg0->unk_0000C > 0) {
            arg0->unk_0000C--;
            arg0->unk_00018 = -1;
            arg0->unk_0001A = -4;
            arg0->unk_00001 = 9;
            PlaySoundEffect(1);
        }
        arg0->unk_00007 = arg0->unk_00008;
        arg0->unk_00008 = 2;
    }
}

void MoveCursorRight(unk_D_842168A0* arg0) {
    if (arg0->unk_00007 == 0) {
        if (arg0->unk_0000C < 2) {
            arg0->unk_0000C++;
            arg0->unk_00018 = 1;
            arg0->unk_0001A = 4;
            arg0->unk_00001 = 9;
            PlaySoundEffect(1);
        }
        arg0->unk_00007 = arg0->unk_00008;
        arg0->unk_00008 = 2;
    }
}

void SwitchPageRight(unk_D_842168A0* arg0) {
    s16 var_s0;
    s16 i;
    unk_D_838067F0_0168* var_s1;

    var_s0 = (arg0->unk_00005 + 1) % 14;
    while ((var_s0 < 0xD) && (arg0->unk_0001C[var_s0].unk_00 == 0)) {
        var_s0 = (var_s0 + 1) % 14;
    }

    if (var_s0 != arg0->unk_00005) {
        PlaySoundEffect(0x27);
        arg0->unk_00005 = var_s0;
        arg0->unk_00140 = GetPokemonNode(arg0->unk_00140, 4);
        arg0->unk_00006 = 0;

        var_s1 = arg0->unk_00140;
        for (i = 0; i < 4; i++) {
            LoadPokemonIntoSlots(arg0, var_s1, arg0->unk_00006 + i, arg0->unk_0013C);
            var_s1 = var_s1->unk_2688;
        }

        arg0->unk_00018 = 0;
        arg0->unk_0001A = 8;
        arg0->unk_00001 = 7;
    }
}

void SwitchPageLeft(unk_D_842168A0* arg0) {
    s16 var_s0;
    s16 i;
    unk_D_838067F0_0168* var_s1;

    var_s0 = (arg0->unk_00005 + 0xD) % 14;
    while ((var_s0 < 0xD) && (arg0->unk_0001C[var_s0].unk_00 == 0)) {
        var_s0 = (var_s0 + 0xD) % 14;
    }

    if (var_s0 != arg0->unk_00005) {
        PlaySoundEffect(0x27);
        arg0->unk_00005 = var_s0;
        arg0->unk_00140 = GetPokemonNode(arg0->unk_00140, 4);
        arg0->unk_00006 = 0;

        var_s1 = arg0->unk_00140;
        for (i = 0; i < 4; i++) {
            LoadPokemonIntoSlots(arg0, var_s1, arg0->unk_00006 + i, arg0->unk_0013C);
            var_s1 = var_s1->unk_2688;
        }

        arg0->unk_00018 = 0;
        arg0->unk_0001A = -8;
        arg0->unk_00001 = 7;
    }
}

void HandleCancelAction(unk_D_842168A0* arg0) {
    s32 temp_v0 = ItemPanel_ConfirmSelection(arg0->unk_13608);

    if (temp_v0 != -1) {
        if (temp_v0 == 1) {
            arg0->unk_00009 = 2;
            arg0->unk_00001 = 4;
            PlaySoundEffect(3);
        }
    } else {
        arg0->unk_00009 = 2;
        arg0->unk_0000A = 0;
        arg0->unk_00001 = 6;
        PlaySoundEffect(3);
    }
}

void HandleStartAction(unk_D_842168A0* arg0) {
    if (ItemPanel_RemoveCurrent(arg0->unk_13608) != 0) {
        arg0->unk_00009 = 2;
        arg0->unk_00001 = 4;
        PlaySoundEffect(2);
    }
}

void func_8420AA08(unk_D_842168A0* arg0) {
    Controller* cont = &gControllers[arg0->unk_00003];

    if (BTN_IS_PRESSED(cont, BTN_A)) {
        SelectPokemon(arg0);
    } else if (BTN_IS_PRESSED(cont, BTN_B)) {
        HandleCancelAction(arg0);
    } else if (BTN_IS_PRESSED(cont, BTN_START)) {
        HandleStartAction(arg0);
    } else if (BTN_IS_PRESSED(cont, BTN_R)) {
        SwitchPageRight(arg0);
    } else if (BTN_IS_PRESSED(cont, BTN_L)) {
        SwitchPageLeft(arg0);
    } else if (BTN_IS_DOWN(cont, BTN_DLEFT)) {
        MoveCursorLeft(arg0);
    } else if (BTN_IS_DOWN(cont, BTN_DRIGHT)) {
        MoveCursorRight(arg0);
    } else if (BTN_IS_DOWN(cont, BTN_DUP)) {
        MoveCursorUp(arg0);
    } else if (BTN_IS_DOWN(cont, BTN_DDOWN)) {
        MoveCursorDown(arg0);
    } else {
        arg0->unk_00008 = 8;
        arg0->unk_00007 = 0;
    }

    arg0->unk_00014 = arg0->unk_00010;
    arg0->unk_00016 = arg0->unk_00012;
    arg0->unk_00009 = 2;
}

void UpdateScrollAnimation(unk_D_842168A0* arg0) {
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
    arg0->unk_00009 = 2;
}

s32 CheckPokemonValidity(PokemonData* arg0) {
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

s32 CheckPokemonStatRange(PokemonData* arg0, s16 arg1, s16 arg2, s16 arg3) {
    s32 sp1C = 0;

    if ((arg0->unk_00.unk_00 > 0) && (arg0->unk_00.unk_00 < 0x98)) {
        if ((CheckPokemonValidity(arg0) != 0) && (D_8006FEE8[arg0->unk_00.unk_00][8] & arg3)) {
            if ((arg0->unk_24 >= arg1) && (arg2 >= arg0->unk_24)) {
                sp1C = 1;
            }
        }
    }
    return sp1C;
}

s32 FilterPokemonByStat(unk_D_842168A0* arg0, s16 arg1, s16 arg2) {
    unk_D_838067F0_003C* ptr = &arg0->unk_0001C[arg1];
    PokemonData sp50;
    s32 var_s0;
    s16 var_s2;
    unk_D_838067F0_003C* temp_v0;
    unk_func_80022C28_ret* var_v0;

    ptr->unk_00 = 0;
    var_s2 = 0;

    if (arg0->unk_00004 < 4) {
        if (arg1 == 0) {
            var_v0 = CreateGbsBlock(0x20, arg0->unk_00004, 0, 0);
        } else {
            var_v0 = CreateGbsBlock(0x21, arg0->unk_00004, arg1 - 1, 0);
        }

        if (var_v0 != NULL) {
            while (GbsBlock_ReadPokemon(&sp50, 1, var_v0) == 1) {
                switch (arg2) {
                    case 0:
                        var_s0 = CheckPokemonStatRange(&sp50, 1, 0x64, 0x20);
                        break;

                    case 1:
                        var_s0 = CheckPokemonStatRange(&sp50, 0x32, 0x37, 1);
                        break;

                    case 2:
                        var_s0 = CheckPokemonStatRange(&sp50, 0x32, 0x37, 1);
                        break;

                    case 3:
                        var_s0 = CheckPokemonStatRange(&sp50, 0x32, 0x37, 1);
                        break;
                    case 4:
                        var_s0 = CheckPokemonStatRange(&sp50, 0x19, 0x1E, 8);
                        break;

                    case 5:
                        var_s0 = CheckPokemonStatRange(&sp50, 0xF, 0x14, 0x10);
                        break;

                    case 6:
                        var_s0 = CheckPokemonStatRange(&sp50, 1, 0x64, 0x20);
                        break;

                    case 7:
                        var_s0 = CheckPokemonStatRange(&sp50, 1, 0x64, 0x20);
                        break;

                    case 8:
                        var_s0 = CheckPokemonStatRange(&sp50, 1, 0x64, 0x20);
                        break;
                }

                if (var_s0 != 0) {
                    temp_v0 = ptr;
                    temp_v0->unk_02[temp_v0->unk_00] = var_s2;
                    temp_v0->unk_00 += 1;
                }

                var_s2++;
            }
            CommitAndFreeGbsBlock(var_v0);
        }
    }
    return ptr->unk_00;
}

s32 InitPokemonMenu(unk_D_842168A0* arg0, gItemPanel* arg1, unk_D_8423D3A8* arg2, s16 arg3, s16 arg4, s16 arg5,
                  s16 arg6, s16 arg7, unk_D_842168A0_0013C* arg8) {
    s16 i;

    arg0->unk_00000 = arg3;
    arg0->unk_00001 = 1;
    arg0->unk_00002 = 0;
    arg0->unk_00003 = arg6;
    arg0->unk_00004 = arg7;
    arg0->unk_00005 = 0xD;
    arg0->unk_00006 = 0;
    arg0->unk_00007 = 0;
    arg0->unk_00008 = 8;
    arg0->unk_0000A = 0;
    arg0->unk_0000C = 0;
    arg0->unk_0000E = 0;
    arg0->unk_00016 = arg5 + 0x1E0;
    arg0->unk_00010 = arg4;
    arg0->unk_00014 = arg4;
    arg0->unk_00012 = arg5;
    arg0->unk_0013C = arg8;
    arg0->unk_13608 = arg1;
    arg0->unk_1360C = arg2;
    arg0->unk_00140 = &arg0->unk_00148[0];

    for (i = 0; i < 8; i++) {
        arg0->unk_00148[i].unk_2688 = &arg0->unk_00148[(i + 1) & 7];
        arg0->unk_00148[i].unk_268C = &arg0->unk_00148[(i - 1) & 7];
    }

    for (i = 12; i >= 0; i--) {
        if (FilterPokemonByStat(arg0, i, gBattleContext.unk_0001) > 0) {
            arg0->unk_00005 = i;
        }
    }

    for (i = 0; i < 4; i++) {
        LoadPokemonIntoSlots(arg0, &arg0->unk_00148[i], i, arg0->unk_0013C);
    }

    return 2;
}

s32 UpdateMenuState(unk_D_842168A0* arg0) {
    s32 sp1C = 0;

    if (arg0->unk_00007 > 0) {
        arg0->unk_00007--;
    }

    switch (arg0->unk_00001) {
        case 1:
            ResetMenuPosition(arg0);
            break;

        case 2:
            ResetMenuPosition(arg0);
            break;

        case 4:
            ResetMenuPositionAndState(arg0);
            break;

        case 3:
            func_8420AA08(arg0);
            break;

        case 7:
            UpdateScrollAnimation(arg0);
            break;

        case 8:
            UpdateScrollAnimation(arg0);
            break;

        case 9:
            UpdateScrollAnimation(arg0);
            break;

        case 10:
            UpdateScrollAnimation(arg0);
            break;

        case 5:
            ScrollMenuUp(arg0);
            sp1C = 1;
            break;

        case 6:
            ScrollMenuDown(arg0);
            sp1C = 1;
            break;

        case 11:
            HandleMoveSelection(arg0);
            break;
    }
    return sp1C;
}

s32 TriggerScrollUp(unk_D_842168A0* arg0, s16 arg1) {
    if (arg0->unk_00001 != 1) {
        return 0;
    }
    arg0->unk_00001 = 5;
    arg0->unk_0000A = -arg1;
    return 1;
}

s32 TriggerScrollDown(unk_D_842168A0* arg0) {
    if (arg0->unk_00001 != 2) {
        return 0;
    }
    arg0->unk_00001 = 5;
    arg0->unk_0000A = 0;
    return 1;
}

s32 TriggerSelectionAnim(unk_D_842168A0* arg0) {
    if (arg0->unk_00001 != 4) {
        return 0;
    }
    arg0->unk_00002 = 6;
    arg0->unk_0000A = 0;
    return 1;
}

void SetMenuActive(unk_D_842168A0* arg0) {
    arg0->unk_00009 = 2;
}

void FindNextValidPokemon(unk_D_842168A0* arg0) {
    s32 i;

    for (i = 0; i < 12; i++) {
        if (ItemPanel_IsItemDuplicate(arg0->unk_13608,
                          &GetPokemonNode(arg0->unk_00140, arg0->unk_0000E)->unk_0000[arg0->unk_0000C]) != 0) {
            break;
        }

        arg0->unk_0000C++;
        if (arg0->unk_0000C == 3) {
            arg0->unk_0000C = 0;
            arg0->unk_0000E = (arg0->unk_0000E + 1) & 3;
        }
    }
}

s32 RequestNextPokemon(unk_D_842168A0* arg0) {
    if (arg0->unk_00001 == 4) {
        FindNextValidPokemon(arg0);
        arg0->unk_00002 = 3;
        return 1;
    }
    return 0;
}

s32 IsMenuInState2(unk_D_842168A0* arg0) {
    return arg0->unk_00001 == 2;
}
