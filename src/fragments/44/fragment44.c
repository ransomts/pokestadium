#include "fragment44.h"
#include "src/19840.h"
#include "src/1CF30.h"
#include "src/20330.h"
#include "src/2E110.h"
#include "src/3FB0.h"
#include "src/49790.h"
#include "src/4CBC0.h"
#include "src/6A40.h"
#include "src/controller.h"
#include "src/memory.h"
#include "src/stage_loader.h"
#include "src/fragments/39/fragment39.h"
#include "src/fragments/43/fragment43.h"

static s32 gItemSelectState;
static unk_D_83407B38 gItemSelectContext;
static s32 gItemSelectMode;
static s32 ItemSelect_ShowResult;
static BinArchive* gStadiumModelArchive;
static u16 ItemSelect_HighlightFlags;
static s32 ItemSelect_FadeInFlag;
static u16 gSlotStatusFlags[0x24];
static s32 ItemSelect_ResultAnimTimer;

s32 ItemSelect_HandleInput(unk_D_83407B38* arg0) {
    s32 sp64;
    s32 sp60;
    s32 sp5C;
    s32 sp58;
    s32 sp54;
    s32 sp50;
    s32 sp4C;
    s32 sp48;
    s32 i;
    Camera* sp40;
    s32 sp3C;
    Camera* sp38;
    s16 tmp;
    s32 idx;
    Camera* ptr;

    sp64 = 0;
    sp60 = arg0->unk_08;
    sp5C = arg0->unk_00;

    sp58 = arg0->unk_00 % 3;
    sp54 = arg0->unk_00 / 3;

    sp4C = 0;
    sp48 = 0;

    if (ItemSelect_ShowResult != 0) {
        sp50 = 3;
    } else {
        sp50 = 2;
    }

    if (Cam_FindActiveIndex(arg0->unk_20, 0x25) != -1) {
        return 0;
    }

    if (gPlayer1Controller->buttonPressed & 0x800) {
        sp54--;
        if (sp54 < 0) {
            sp54 = sp50 - 1;
        }
    }

    if (gPlayer1Controller->buttonPressed & 0x400) {
        sp54++;
        if (sp54 >= sp50) {
            sp54 = 0;
        }
    }

    if (sp54 < 2) {
        if (gPlayer1Controller->buttonPressed & 0x200) {
            sp58--;
            if (sp58 < 0) {
                if (arg0->unk_08 > 0) {
                    sp58 = 2;
                } else {
                    sp58 = 0;
                }
                sp4C = 1;
            }
        }

        if (gPlayer1Controller->buttonPressed & 0x100) {
            sp58++;
            if (sp58 >= 3) {
                if (arg0->unk_08 < (arg0->unk_0C - 1)) {
                    sp58 = 0;
                } else {
                    sp58 = 2;
                }
                sp48 = 1;
            }
        }
    }

    arg0->unk_00 = (sp54 * 3) + sp58;
    if (sp5C != arg0->unk_00) {
        PlaySoundEffect(1);
    }

    if ((gPlayer1Controller->buttonPressed & 0x20) || (sp4C != 0)) {
        arg0->unk_08--;
        if (arg0->unk_08 < 0) {
            arg0->unk_08 = 0;
        }
    } else if ((gPlayer1Controller->buttonPressed & 0x10) || (sp48 != 0)) {
        arg0->unk_08++;
        if (arg0->unk_0C - 1 < arg0->unk_08) {
            arg0->unk_08 = arg0->unk_0C - 1;
        }
    }

    if (sp60 != arg0->unk_08) {
        PlaySoundEffect(0x27);

        for (i = 0; i < arg0->unk_14; i++) {
            sp40 = arg0->unk_20[arg0->unk_08 * arg0->unk_14 + i];
            if (Cam_IsMonIndexDisplayable(sp40) != 0) {
                sp40->unk_00 = 0;
            }
        }
    }

    if (gPlayer1Controller->buttonPressed & 0x8000) {
        sp3C = (arg0->unk_08 * arg0->unk_14) + arg0->unk_00;
        sp38 = arg0->unk_20[sp3C];

        if (arg0->unk_04 == -1) {
            if ((sp54 * 3) < 6) {
                if (Cam_IsMonIndexDisplayable(sp38) != 0) {
                    arg0->unk_04 = sp3C;
                    arg0->unk_B0->unk_18 = sp38->unk_18;
                    arg0->unk_B0->unk_00 = 0;
                    if (gItemSelectMode == 2) {
                        gItemSelectState = 3;
                        PlaySoundEffect(0xD);
                        D_83407B30.unk_04 = arg0->unk_04;
                    } else {
                        PlaySoundEffect(2);
                    }
                } else {
                    PlaySoundEffect(8);
                }
            } else {
                sp64 = 1;
                PlaySoundEffect(3);
            }
        } else if ((sp54 * 3) < 6) {
            if (sp3C != arg0->unk_04) {
                PlaySoundEffect(0x29);
                func_83400590(sp38->unk_18, arg0->unk_20[arg0->unk_04]->unk_18);

                tmp = gSlotStatusFlags[sp3C];
                gSlotStatusFlags[sp3C] = gSlotStatusFlags[arg0->unk_04];
                gSlotStatusFlags[arg0->unk_04] = tmp;

                arg0->unk_20[arg0->unk_04]->unk_00 = 0;
                sp38->unk_00 = 0;
            } else {
                PlaySoundEffect(3);
            }
            arg0->unk_04 = -1;
        } else {
            gItemSelectState = 2;
            ItemSelect_ResultAnimTimer = 0;
            PlayResultScreenSfx(0x0120000C, 0, 0);
        }
    } else if (gPlayer1Controller->buttonPressed & 0x4000) {
        if (arg0->unk_04 == -1) {
            sp64 = 1;
            if (gItemSelectMode == 2) {
                GallerySelection_Init(&D_83407B30);
            }
        } else {
            arg0->unk_04 = -1;
        }
        PlaySoundEffect(3);
    } else if (gPlayer1Controller->buttonPressed & 4) {
        idx = arg0->unk_08 * arg0->unk_14 + arg0->unk_00;
        ptr = arg0->unk_20[idx];

        if (((sp54 * 3) < 6) && (arg0->unk_04 == -1) && (Cam_IsMonIndexDisplayable(ptr) != 0)) {
            sp64 = 2;
            PlaySoundEffect(0x19);
            func_83400694(ptr->unk_18);
        } else {
            PlaySoundEffect(8);
        }
    }
    return sp64;
}

void ItemSelect_Init(s32 arg0, s32 arg1) {
    s32 i;
    s32 j;
    AssetManager* tmp;

    gItemSelectState = 0;
    gItemSelectMode = arg0;

    if (arg1 != 0) {
        ItemSelect_FadeInFlag = 1;
    } else {
        ItemSelect_FadeInFlag = 0;
    }

    if (gItemSelectMode != 2) {
        ItemSelect_ShowResult = 1;
    } else {
        ItemSelect_ShowResult = 0;
    }

    ItemSelect_HighlightFlags = -1;
    ItemSelect_ResultAnimTimer = 0;

    tmp = AssetManager_Create(5);
    CamList_Init(&gItemSelectContext, 0x88, 0x66, 6, 3, tmp, gStadiumModelArchive, D_83403C60, 0x24, 1);
    if (gItemSelectMode == 2) {
        func_834021EC(&gItemSelectContext, &D_83407B18.unk_00);
    } else if (arg1 == 0) {
        func_834021EC(&gItemSelectContext, &D_83407B10);
    }

    for (i = 0; i < 36; i++) {
        unk_D_83403C60* ptr = &D_83403C60[i];

        gSlotStatusFlags[i] = 0;
        if (IsMonIndexDisplayable(ptr) != 0) {
            for (j = 0; j < 21; j++) {
                if ((IsMonIndexDisplayable(&D_834063C0[j]) != 0) && (func_83400660(&D_834063C0[j], ptr) != 0)) {
                    if (j < 4) {
                        gSlotStatusFlags[i] |= 1;
                    } else {
                        gSlotStatusFlags[i] |= 2;
                    }
                }
            }
        }
    }
}

void DrawGridCellTexture(s32 arg0, s32 arg1) {
    s32 temp_v0;
    s32 i;
    s32 tmp = 8;
    s32 new_var = 48;
    s32 tmp2 = 0;
    s32 tmp3 = 64;

    for (i = 0; i < new_var; i += tmp) {
        temp_v0 = CLAMP_MIN(new_var - i, tmp);

        gDPLoadTextureTile(gDisplayListHead++, D_04001000 + ((i << 6) << 1), G_IM_FMT_RGBA, G_IM_SIZ_16b, 64, 64, tmp2,
                           tmp2, 64, temp_v0 - 1, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                           G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

        Gfx_DrawTextureRect(arg0, arg1 + i, 64, temp_v0, 0, 0, 0x400, 0x400, 0);
    }
}

void DrawGridPanelTexture(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    gDPSetCombineMode(gDisplayListHead++, G_CC_BLENDPEDECALA, G_CC_BLENDPEDECALA);
    gDPSetRenderMode(gDisplayListHead++, G_RM_OPA_SURF, G_RM_OPA_SURF2);
    gDPSetPrimColor(gDisplayListHead++, 0, 0, 155, 140, 155, 255);
    gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255);
    gDPLoadTextureBlock_4b(gDisplayListHead++, D_4003900, G_IM_FMT_I, 128, 64, 0, G_TX_NOMIRROR | G_TX_WRAP,
                           G_TX_NOMIRROR | G_TX_WRAP, 7, 6, G_TX_NOLOD, G_TX_NOLOD);

    Gfx_DrawTextureRect(arg0, arg1, arg2, arg3, 0, 0, 0x400, 0x400, 0);
}

void DrawResultPanelTexture(s32 arg0, s32 arg1, s32 arg2) {
    gDPSetCombineMode(gDisplayListHead++, G_CC_BLENDPEDECALA, G_CC_BLENDPEDECALA);
    gDPSetRenderMode(gDisplayListHead++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
    gDPSetPrimColor(gDisplayListHead++, 0, 0, 195, 175, 175, 255);
    gDPSetEnvColor(gDisplayListHead++, 0, 0, 0, 255);
    gDPLoadTextureBlock(gDisplayListHead++, D_4002900, G_IM_FMT_IA, G_IM_SIZ_8b, 64, 64, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

    Gfx_DrawTextureRect(arg0, arg1, 0x40, 0x40, 0x7E0, 0, -0x400, 0x400, 0);
    Gfx_DrawTextureRect(arg0 - 0x40, arg1, 0x40, 0x40, 0, 0, 0x400, 0x400, 0);
    Gfx_DrawTextureRect((arg0 + arg2) - 0x40, arg1, 0x40, 0x40, 0, 0, 0x400, 0x400, 0);
    Gfx_DrawTextureRect(arg0 + 0x40, arg1, arg2 - 0x80, 0x40, 0, 0, 0, 0x400, 0);
}

void DrawResultPanelHighlight(s32 arg0, s32 arg1, s32 arg2) {
    gDPSetCombineMode(gDisplayListHead++, G_CC_BLENDPEDECALA, G_CC_BLENDPEDECALA);
    gDPSetRenderMode(gDisplayListHead++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
    gDPSetPrimColor(gDisplayListHead++, 0, 0, 100, 100, 200, 255);
    gDPSetEnvColor(gDisplayListHead++, 255, 255, 155, 255);
    gDPLoadTextureBlock(gDisplayListHead++, D_04002800, G_IM_FMT_IA, G_IM_SIZ_8b, 16, 16, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

    Gfx_DrawTextureRect(arg0, arg1, 0x10, 0x10, 0x1E0, 0, -0x400, 0x400, 0);
    Gfx_DrawTextureRect(arg0 - 0x10, arg1, 0x10, 0x10, 0, 0, 0x400, 0x400, 0);
    Gfx_DrawTextureRect((arg0 + arg2) - 0x10, arg1, 0x10, 0x10, 0, 0, 0x400, 0x400, 0);
}

void DrawGridPageCounter(unk_D_83407B38* arg0, s32 arg1, s32 arg2) {
    s32 temp_s1;
    s32 temp_v1;
    char* temp_v0;
    UNUSED s32 pad[2];
    char sp30[4];

    Text_ResetState();
    Text_BeginRender();
    Text_SetFont(8, 0);
    Text_SetEnvColor(0, 0x64, 0xDC, 0xFF);
    Text_SetPrimColor(0xFF, 0xFF, 0xFF, 0xFF);

    temp_v0 = Text_GetMessageString_Bank2C(0x3A);

    temp_v1 = (0xDF - (MeasureTextWidth(0, 0, temp_v0) + MeasureTextWidth(0, 0, "99/99"))) / 2;
    temp_s1 = temp_v1 + 0x133;

    Text_Print((arg1 + temp_v1) + 0x133, arg2 + 0x108, temp_v0);
    temp_s1 += MeasureTextWidth(0, 0, temp_v0) + MeasureTextWidth(0, 0, "99/99");
    temp_s1 += 0x14;
    sprintf(sp30, "%d", arg0->unk_0C);
    Text_Print((arg1 + temp_s1) - MeasureTextWidth(0, 0, sp30), arg2 + 0x108, sp30);
    temp_s1 -= MeasureTextWidth(0, 0, "99");
    sprintf(sp30, "/");
    Text_Print((arg1 + temp_s1) - MeasureTextWidth(0, 0, sp30), arg2 + 0x108, sp30);
    temp_s1 -= MeasureTextWidth(0, 0, sp30);
    if (sp30) {}
    sprintf(sp30, "%d", arg0->unk_08 + 1);
    Text_Print((arg1 + temp_s1) - MeasureTextWidth(0, 0, sp30), arg2 + 0x108, sp30);
    Text_EndRender();
    Text_SetupDL();
}

void DrawGridCellBorder(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    UNUSED s32 pad[2];

    arg0 -= 4;
    arg1 -= 4;
    arg2 += 8;
    arg3 += 8;

    Gfx_DrawSpriteIA8(arg0, arg1, 0x18, 0x18, D_400D780, 0x18, 0);
    Gfx_DrawTextureRect((arg0 + arg2) - 0x18, arg1 & 0xFFFFFFFF, 0x18, 0x18, 0x2E0, 0, -0x400, 0x400, 0);
    Gfx_DrawSpriteIA8(arg0 & 0xFFFFFFFF, (arg1 + arg3) - 0x14, 0x18, 0x18, D_400D9C0, 0x18, 0);
    Gfx_DrawTextureRect((arg0 + arg2) - 0x18, (arg1 + arg3) - 0x14, 0x18, 0x18, 0x2E0, 0, -0x400, 0x400, 0);
}

void DrawSlotStatusIcons(s32 arg0, s32 arg1, u16 arg2) {
    s32 var_s2;
    s8* var_s0;
    s32 i;
    s32 tmp;

    var_s2 = 0;
    for (i = 1; i >= 0; i--) {
        if ((arg2 >> i) & 1) {
            gDPPipeSync(gDisplayListHead++);

            gDPSetCombineLERP(gDisplayListHead++, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0,
                              PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0);
            gDPSetPrimColor(gDisplayListHead++, 0, 0, 255, 255, 255, 255);

            if (i == 0) {
                gDPSetEnvColor(gDisplayListHead++, 0, 100, 0, 255);
            } else {
                gDPSetEnvColor(gDisplayListHead++, 0, 120, 100, 255);
            }

            Gfx_DrawSpriteIA8(arg0 + 0x6C, (arg1 - (var_s2 * 0x32)) + 0x36, 0x20, 0x2E, &D_4011638, 0x20, 0);
            var_s2++;
        }
    }

    Text_ResetState();
    Text_SetFont(8, 0);
    Text_SetEnvColor(0xFF, 0xFF, 0, 0xFF);

    var_s2 = 0;
    for (i = 1; i >= 0; i--) {
        if ((arg2 >> i) & 1) {
            if (i == 0) {
                var_s0 = "4";
            } else {
                var_s0 = "16";
            }
            tmp = (0x16 - MeasureTextWidth(8, 0, var_s0)) / 2;
            Text_Print(arg0 + 0x6C + tmp, (arg1 - (var_s2 * 0x32)) + 0x4E, var_s0);
            var_s2++;
        }
    }

    Text_SetupDL();
}

void CalcResultPanelSize(s32 arg0, s32* arg1, s32* arg2, f32* arg3) {
    static f32 D_83503E70 = 69.0f;
    static f32 D_83503E74 = 5.3f;
    static f32 D_83503E78 = -0.6f;
    static f32 D_83503E7C = 350.0f;
    static f32 D_83503E80 = -16.0f;
    static f32 D_83503E84 = 1.7f;
    static f32 D_83503E88 = 1.0f;

    f32 var_fa0;
    f32 var_fa1;
    f32 var_ft4;
    f32 var_fv0;
    f32 var_fv1;
    s32 temp_v0;
    s32 num = 10;

    if (arg0 < num) {
        if (arg0 > 0) {
            var_fv0 = (COSS(arg0 << 15) * D_83503E88) + D_83503E70;
        } else {
            var_fv0 = D_83503E70;
        }
        var_fa1 = D_83503E7C;
        var_ft4 = 0.5f;
    } else {
        temp_v0 = arg0 - num;
        if (temp_v0 > 0) {
            var_fv1 = D_83503E74;
            var_fa0 = D_83503E80;
        } else {
            var_fv1 = 0.0f;
            var_fa0 = 0.0f;
        }
        var_fv0 = (temp_v0 * ((temp_v0 * D_83503E78) + var_fv1)) + D_83503E70;
        var_fa1 = (temp_v0 * ((temp_v0 * D_83503E84) + var_fa0)) + D_83503E7C;
        var_ft4 = ((num - temp_v0) * 0.5f) / num;
    }

    *arg1 = ROUND_MAX(var_fv0);
    *arg2 = ROUND_MAX(var_fa1);
    *arg3 = var_ft4;
}

// tmp2 is computed before the early return and the x position is written as arg1 + tmp2 at each use
// (no named x): that is what puts its spilled CSE temp at 0x90 below six unused temp slots.
void DrawResultPanelImage(u16* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, f32 arg5) {
    s32 i;
    s32 tmp;
    f32 a;
    s32 sp100;
    s32 temp_ft7;
    s32 temp_ft8;
    s32 spF4;
    s32 temp_ft0;
    s32 temp_ft3;
    s32 spE8;
    s32 temp_fv1_3;
    s32 temp_fv0_3;
    s32 var_t0;
    s32 tmp2;

    sp100 = arg4;
    temp_ft0 = arg3;
    tmp = 0xC;

    temp_ft8 = ROUND_MAX((arg3 * 0.5f) + 0.4f);
    temp_ft7 = ROUND_MAX((arg4 * 0.5f) + 0.4f);
    spF4 = ROUND_MAX((arg3 * arg5) + 0.4f);
    temp_ft3 = ROUND_MAX((arg4 * arg5) + 0.4f);

    spE8 = (temp_ft7 - temp_ft3) / 2;

    tmp2 = (temp_ft8 - spF4) / 2;

    if (arg5 <= 0.0f) {
        return;
    }

    gSPDisplayList(gDisplayListHead++, gPrefDL_Fill);

    Gfx_FillRectRGBA(arg1 + tmp2 + 0xA, arg2 + spE8 + 0xA, spF4 + 4, temp_ft3 + 4, 0, 0, 0, 0x80);
    DrawRectBorder(arg1 + tmp2, arg2 + spE8, spF4, temp_ft3, 2);

    gSPDisplayList(gDisplayListHead++, gPrefDL_Border);
    gDPSetRenderMode(gDisplayListHead++, G_RM_OPA_SURF, G_RM_OPA_SURF2);

    for (i = 0; i < sp100; i += tmp) {
        var_t0 = (sp100 - i < tmp) ? sp100 - i : tmp;
        a = 1024.0f / arg5;

        temp_fv0_3 = ROUND_MAX((var_t0 * arg5) + 0.4f);
        temp_fv1_3 = ROUND_MAX((i * arg5) + 0.4f);

        gDPLoadTextureTile(gDisplayListHead++, &arg0[i * temp_ft0], G_IM_FMT_RGBA, G_IM_SIZ_16b, temp_ft0, 0, 0, 0,
                           temp_ft0, var_t0 - 1, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK,
                           G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

        Gfx_DrawTextureRect(arg1 + tmp2, arg2 + spE8 + temp_fv1_3, spF4, temp_fv0_3, 0, 0, a, a, 0);
    }
}

void ItemSelect_DrawGrid(s32 arg0, s32 arg1, unk_D_83407B38* arg2) {
    UNUSED s32 pad;
    s32 temp_s3;
    s32 var_s4;
    Camera* ptr;
    s32 idx;
    s32 i;

    for (i = 0; i < arg2->unk_14; i++) {
        idx = i;
        temp_s3 = idx + (arg2->unk_08 * arg2->unk_14);
        ptr = arg2->unk_20[temp_s3];

        var_s4 = 0;
        if ((temp_s3 != arg2->unk_04) && (Cam_IsMonIndexDisplayable(ptr) != 0) && (ptr->unk_00 == 2)) {
            var_s4 = 1;
            func_834018C0(ptr->unk_08->img_p, ((idx % 3) * 0xA0) + arg0, ((idx / 3) * 0x76) + arg1, 0x88, 0x66, 0xF, 1);
        }

        gSPDisplayList(gDisplayListHead++, gPrefDL_Border);

        DrawGridCellBorder(((idx % 3) * 0xA0) + arg0, ((idx / 3) * 0x76) + arg1, 0x88, 0x66);

        if ((var_s4 != 0) && (gSlotStatusFlags[temp_s3] != 0)) {
            DrawSlotStatusIcons(((idx % 3) * 0xA0) + arg0, ((idx / 3) * 0x76) + arg1, gSlotStatusFlags[temp_s3]);
        }
    }

    if (arg2->unk_04 != -1) {
        s32 sp70;
        s32 sp6C;
        s32 sp68;
        s32 sp64;
        f32 sp60;

        func_83402210(arg2, &sp70, &sp6C, arg2->unk_00);

        ptr = arg2->unk_B0;
        if ((Cam_IsMonIndexDisplayable(ptr) != 0) && (ptr->unk_00 == 2)) {
            if (sp6C < 2) {
                func_83401818((sp70 * 0xA0) + arg0, (sp6C * 0x76) + arg1, 0x88, 0x66);
                func_834018C0(ptr->unk_08->img_p, ((sp70 * 0xA0) + arg0) - 0x10, ((sp6C * 0x76) + arg1) - 0x10, 0x88,
                              0x66, 8, 1);
            } else {
                CalcResultPanelSize(ItemSelect_ResultAnimTimer, &sp68, &sp64, &sp60);
                DrawResultPanelImage(ptr->unk_08->img_p, sp68, sp64, 0x88, 0x66, sp60);
            }
        }
    }
}

void ItemSelect_DrawHeader(unk_D_83407B38* arg0, s32 arg1, s32 arg2) {
    static Color_RGBA8 D_83503E8C = { 0x9A, 0x37, 0x54, 0xFF };
    static Color_RGBA8 D_83503E90 = { 0xC3, 0x54, 0x84, 0xFF };
    static s16 D_83503E94 = 0;

    char* sp5C;
    s32 temp_s0;
    s32 sp54;
    s32 var_t1;
    Color_RGBA8 sp4C = D_83503E8C;
    Color_RGBA8 sp48 = D_83503E90;

    sp54 = SINS(D_83503E94) * 4.0f;

    if (gItemSelectMode != 2) {
        sp5C = Text_GetMessageString_Bank2C(1);
    } else {
        sp5C = Text_GetMessageString_Bank2C(3);
    }
    temp_s0 = (0x1B6 - MeasureTextWidth(0x10, 0, sp5C)) / 2;
    DrawPanelWithTextures(arg1, arg2, 0x1B6, &sp4C, &sp48);

    gSPDisplayList(gDisplayListHead++, gPrefDL_Border);

    DrawVerticalTextureStrip(D_3001D20, (arg1 + temp_s0) - 0x44, arg2 - 3, 0x30, 0x23, 0);
    DrawVerticalTextureStrip(D_3001D20, MeasureTextWidth(0x10, 0, sp5C) + arg1 + temp_s0 + 0x14, arg2 - 3, 0x30, 0x23, 1);

    if (arg0->unk_08 > 0) {
        temp_s0 = sp54;
        var_t1 = 0xFF;
    } else {
        temp_s0 = 0;
        var_t1 = 0x80;
    }

    gDPPipeSync(gDisplayListHead++);
    gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, var_t1);

    func_83401D0C((arg1 - temp_s0) - 0x21, arg2 + 6, 0);

    if (arg0->unk_08 < (arg0->unk_0C - 1)) {
        temp_s0 = sp54;
        var_t1 = 0xFF;
    } else {
        temp_s0 = 0;
        var_t1 = 0x80;
    }

    gDPPipeSync(gDisplayListHead++);
    gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, var_t1);

    func_83401D0C(arg1 + temp_s0 + 0x19C, arg2 + 6, 1);
    Text_ResetState();
    Text_SetFont(0x10, 0);
    temp_s0 = 0x1B6 - MeasureTextWidth(0x10, 0, sp5C);
    temp_s0 /= 2;
    Text_SetEnvColor(0, 0, 0, 0xFF);
    Text_Print((arg1 + temp_s0) + 2, arg2 + 5, sp5C);
    Text_SetEnvColor(0xFF, 0xFF, 0x77, 0xFF);
    Text_Print(arg1 + temp_s0, arg2 + 3, sp5C);
    Text_SetupDL();

    D_83503E94 += 0x1000;
}

void DrawGridHelpPrompt(s32 arg0) {
    char* sp2C;
    s32 sp28;
    s32 temp_v1;

    sp2C = Text_GetMessageString_Bank2C(0x3C);
    temp_v1 = (0xF3 - MeasureTextWidth(8, 0, sp2C)) / 2;
    sp28 = temp_v1 + 0x5E;

    gSPDisplayList(gDisplayListHead++, gPrefDL_Border);

    Gfx_DrawSpriteRGBA16(temp_v1 + 0x3E, arg0 - 2, 0x18, 0x18, D_30099B8, 0x18, 0);
    Text_ResetState();
    Text_SetFont(8, 0);
    Text_SetEnvColor(0xFF, 0xFF, 0xFF, 0xFF);
    Text_Print(sp28, arg0, sp2C);
    Text_SetupDL();
}

void DrawGridBackground(s32 arg0, s32 arg1, unk_D_83407B38* arg2) {
    s32 i;

    gSPDisplayList(gDisplayListHead++, gPrefDL_Border);

    for (i = 0; i < 6; i++) {
        DrawGridCellTexture(arg0, arg1 + i * 0x30);
    }

    DrawGridPanelTexture(arg0 + 0x40, arg1, 0x1E7, 0x120);
    DrawResultPanelTexture(arg0 + 0x20, arg1 + 0x113, 0x207);
    DrawResultPanelHighlight(arg0 + 0x20, arg1, 0x207);
    ItemSelect_DrawHeader(&gItemSelectContext, 0x65, 0x24);

    if (gItemSelectContext.unk_04 == -1) {
        DrawGridHelpPrompt(arg1 + 0x108);
    }

    DrawGridPageCounter(&gItemSelectContext, arg0, arg1);
}

void DrawHighlightBars(void) {
    static Color_RGBA8 D_83503E98 = { 0xCD, 0xE1, 0x73, 0 };
    static Color_RGBA8 D_83503E9C = { 0xB4, 0, 0x91, 0 };
    static Color_RGBA8 D_83503EA0 = { 0xD7, 0xEB, 0x7D, 0 };
    static Color_RGBA8 D_83503EA4 = { 0xA0, 0x50, 0x91, 0 };

    s32 temp_v0_11;
    s32 i;
    s32 idx;
    s32 r;
    s32 g;
    s32 b;
    s32 end = 0x1E0;

    gSPDisplayList(gDisplayListHead++, gPrefDL_Border);
    gDPSetCombineMode(gDisplayListHead++, G_CC_BLENDPEDECALA, G_CC_BLENDPEDECALA);
    gDPSetRenderMode(gDisplayListHead++, G_RM_OPA_SURF, G_RM_OPA_SURF2);
    gDPLoadTextureBlock_4b(gDisplayListHead++, D_04000000, G_IM_FMT_I, 128, 64, 0, G_TX_NOMIRROR | G_TX_WRAP,
                           G_TX_NOMIRROR | G_TX_WRAP, 7, 6, G_TX_NOLOD, G_TX_NOLOD);

    idx = 0;
    for (i = 0; i < end; i += 0x40, idx++) {
        temp_v0_11 = CLAMP_MIN(end - i, 0x40);

        if (ItemSelect_HighlightFlags & (1 << idx)) {
            r = (((D_83503EA0.r - D_83503E98.r) * idx) / 8) + D_83503E98.r;
            g = (((D_83503EA0.g - D_83503E98.g) * idx) / 8) + D_83503E98.g;
            b = (((D_83503EA0.b - D_83503E98.b) * idx) / 8) + D_83503E98.b;

            gDPPipeSync(gDisplayListHead++);

            gDPSetPrimColor(gDisplayListHead++, 0, 0, r, g, b, 255);

            r = (((D_83503EA4.r - D_83503E9C.r) * idx) / 8) + D_83503E9C.r;
            g = (((D_83503EA4.g - D_83503E9C.g) * idx) / 8) + D_83503E9C.g;
            b = (((D_83503EA4.b - D_83503E9C.b) * idx) / 8) + D_83503E9C.b;

            gDPSetEnvColor(gDisplayListHead++, r, g, b, 255);

            Gfx_DrawTextureRect(0, i, 0x280, temp_v0_11, 0, 0, 0x400, 0x400, 0);
        }
    }
}

typedef struct unk_D_83503EA8 {
    /* 0x00 */ u8* unk_00;
    /* 0x04 */ s32 unk_04;
} unk_D_83503EA8; // size = 0x8

void DrawAnimatedMonPanel(s32 arg0, s32 arg1, s32 arg2) {
    static unk_D_83503EA8 D_83503EA8[] = {
        {
            NULL,
            0x0000003C,
        },
        {
            D_04017990,
            0x00000002,
        },
        {
            NULL,
            0x00000002,
        },
        {
            D_04017990,
            0x00000002,
        },
        {
            NULL,
            0x00000002,
        },
        {
            D_04017990,
            0x00000002,
        },
        {
            NULL,
            0x00000002,
        },
        {
            D_04017990,
            0x00000002,
        },
        {
            NULL,
            -1,
        },
    };
    static unk_D_83503EA8 D_83503EF0[] = {
        {
            D_04004900,
            0x00000002,
        },
        {
            D_04006CA0,
            0x00000002,
        },
        {
            D_04009040,
            0x00000002,
        },
        {
            D_0400B3E0,
            0x00000002,
        },
        {
            D_04009040,
            0x00000002,
        },
        {
            D_04006CA0,
            0x00000002,
        },
        {
            D_04004900,
            0x00000002,
        },
        {
            0x00000000,
            -1,
        },
    };
    static s32 D_83503F30 = 0;
    static s32 D_83503F34 = 2;
    static s32 D_83503F38 = 0;
    static s32 D_83503F3C = 2;

    s32 spFC;
    s32 i;
    s32 end;
    u8* spF0;
    u8* spEC = NULL;
    u16* spE8 = NULL;
    s32 var_ra;
    s32 var_s2;
    UNUSED s32 pad;

    Text_GetMessageString_Bank2C(0x3B);

    if (arg2 != 0) {
        spF0 = D_4015080;
        var_ra = 0x64;
        end = 0x69;
        spFC = 0;
        var_s2 = 0x1E;
        D_83503F34--;
        if (D_83503F34 <= 0) {
            D_83503F30++;
            D_83503F34 = D_83503EA8[D_83503F30].unk_04;
            if (D_83503F34 < 0) {
                D_83503F30 = 0;
                D_83503F34 = D_83503EA8[0].unk_04;
            }
        }
    } else {
        spF0 = D_4011BF8;
        var_ra = 0x80;
        end = 0x69;
        spFC = -0x1C;
        var_s2 = 0x14;
        D_83503F3C--;
        if (D_83503F3C <= 0) {
            D_83503F38++;
            D_83503F3C = D_83503EF0[D_83503F38].unk_04;
            if (D_83503F3C < 0) {
                D_83503F38 = 0;
                D_83503F3C = D_83503EF0[0].unk_04;
            }
        }
    }

    gSPDisplayList(gDisplayListHead++, gPrefDL_Border);

    for (i = 0; i < end; i += var_s2) {
        s32 temp_v0_11 = CLAMP_MIN(end - i, var_s2);

        gDPLoadTextureTile(gDisplayListHead++, &spF0[i * var_ra], G_IM_FMT_IA, G_IM_SIZ_8b, var_ra, 0, 0, 0, var_ra,
                           temp_v0_11 - 1, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK,
                           G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

        Gfx_DrawTextureRect(arg0 + spFC, arg1 + i, var_ra, temp_v0_11, 0, 0, 0x400, 0x400, 0);
    }

    if (arg2 != 0) {
        spEC = D_83503EA8[D_83503F30].unk_00;
    }

    if (spEC != NULL) {
        var_ra = 0x64;
        end = 0x37;
        for (i = 0; i < end; i += var_s2) {
            s32 temp_v0_11 = CLAMP_MIN(end - i, var_s2);

            gDPLoadTextureTile(gDisplayListHead++, &spEC[i * var_ra], G_IM_FMT_IA, G_IM_SIZ_8b, var_ra, 0, 0, 0, var_ra,
                               temp_v0_11 - 1, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK,
                               G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

            Gfx_DrawTextureRect(arg0, arg1 + i + 7, var_ra, temp_v0_11, 0, 0, 0x400, 0x400, 0);
        }
    }

    if (arg2 == 0) {
        spE8 = D_83503EF0[D_83503F38].unk_00;
    }

    if (spE8 != NULL) {
        var_ra = 0x4C;
        var_s2 = 0x14;
        end = 0x3C;
        for (i = 0; i < end; i += var_s2) {
            s32 temp_v0_11 = CLAMP_MIN(end - i, var_s2);

            gDPLoadTextureTile(gDisplayListHead++, &spE8[i * var_ra], G_IM_FMT_RGBA, G_IM_SIZ_16b, var_ra, 0, 0, 0,
                               var_ra, temp_v0_11 - 1, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                               G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

            Gfx_DrawTextureRect(arg0 + spFC + 0x30, arg1 + i, var_ra, temp_v0_11, 0, 0, 0x400, 0x400, 0);
        }
    }
}

void DrawResultScreen(int arg0, int arg1, s32 arg2, f32 arg3) {
    s32 i;
    s32 iter = 16;
    f32 tmp = 1024.0f;
    s32 temp_s2;
    s32 spFC = 0x6C;
    s32 spF8 = 0x45;
    s32 temp_s3;
    s32 temp_ft2 = ROUND_MAX((spFC * arg3) + 0.4f);
    s32 temp_fv1 = ROUND_MAX((spF8 * arg3) + 0.4f);
    u16* spE4[] = { D_03005F80, D_0400DC00 };
    s16 spE0[] = { 0x0037, 0x0038 };
    u16* spDC = spE4[arg2];
    char* spD8 = Text_GetMessageString_Bank2C(spE0[arg2]);
    Color_RGB8 spD0[] = {
        { 0xE6, 0x6E, 0x82 },
        { 0x6E, 0xFF, 0x0F },
    };

    if (arg3 <= 0.0f) {
        return;
    }

    gSPDisplayList(gDisplayListHead++, gPrefDL_Border);

    for (i = 0; i < spF8; i += iter) {
        s32 temp_v0_2 = CLAMP_MIN(spF8 - i, iter);
        s32 temp_fv1_2 = ROUND_MAX((temp_v0_2 * arg3) + 0.4f);
        s32 temp_fa0 = ROUND_MAX((i * arg3) + 0.4f);

        gDPLoadTextureTile(gDisplayListHead++, &spDC[i * spFC], G_IM_FMT_RGBA, G_IM_SIZ_16b, spFC, 0, 0, 0, spFC,
                           temp_v0_2 - 1, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK,
                           G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

        Gfx_DrawTextureRect(arg0 + ((spFC - temp_ft2) / 2), arg1 + ((spF8 - temp_fv1) / 2) + temp_fa0, temp_ft2, temp_fv1_2,
                      0, 0, tmp / arg3, tmp / arg3, 0);
    }

    temp_s3 = (spFC - MeasureTextWidth(0, 0, spD8)) / 2;
    temp_s2 = (spF8 - (func_834006CC(spD8) * 0x14)) / 2;

    Text_ResetState();
    Text_SetFont(8, 0);
    Text_SetLineHeight(0x14);
    Text_SetEnvColor(0, 0, 0, 0xFF);
    Text_Print(arg0 + temp_s3 + 2, arg1 + temp_s2 + 2, spD8);
    Text_BeginRender();
    Text_SetEnvColor(spD0[arg2].r, spD0[arg2].g, spD0[arg2].b, 0xFF);
    Text_SetPrimColor(0xFF, 0xFF, 0xFF, 0xFF);
    Text_Print(arg0 + temp_s3, arg1 + temp_s2, spD8);
    Text_EndRender();
    Text_SetupDL();
}

char* GetGridHelpString(unk_D_83407B38* arg0) {
    s32 tmp = arg0->unk_00 / 3;
    char* var_v0;

    if (gItemSelectMode == 2) {
        var_v0 = Text_GetMessageString_Bank2C(0x29);
    } else if (tmp < 2) {
        var_v0 = Text_GetMessageString_Bank2C(0x25);
    } else if (arg0->unk_04 != -1) {
        var_v0 = Text_GetMessageString_Bank2C(0x26);
    } else if (gItemSelectMode == 1) {
        var_v0 = Text_GetMessageString_Bank2C(0x28);
    } else {
        var_v0 = Text_GetMessageString_Bank2C(0x27);
    }
    return var_v0;
}

void DrawGridHelpBox(unk_D_83407B38* arg0, s32 arg1, s32 arg2) {
    char* sp1C = GetGridHelpString(arg0);

    func_834008DC(arg1, arg2, 0x13F, 0x4C);
    if (sp1C != NULL) {
        Text_ResetState();
        Text_SetFont(8, 0);
        Text_SetLineHeight(0x14);
        Text_Print(arg1 + 0xA, arg2 + 8, sp1C);
        Text_SetupDL();
    }
}

f32 UpdateFadeTimer(s32* arg0, u32* arg1, s32 arg2) {
    f32 tmp;

    if (*arg0 < arg2) {
        *arg0 += 1;
        tmp = 1.0f;
    } else {
        tmp = (COSS(*arg1) * 0.1f) + 0.9f;
        *arg1 += 0x2000;
        if (*arg1 >= 0x10000) {
            *arg0 = 0;
            *arg1 = 0;
        }
    }

    return tmp;
}

void DrawGridSelectionHighlight(unk_D_83407B38* arg0) {
    s32 temp_hi = arg0->unk_00 % 3;
    s32 temp_lo = arg0->unk_00 / 3;
    s32 var_v0;

    gSPDisplayList(gDisplayListHead++, gPrefDL_Border);

    if (arg0->unk_04 == -1) {
        var_v0 = 0;
    } else {
        var_v0 = -0x10;
    }

    if (temp_lo < 2) {
        func_83401B48((temp_hi * 0xA0) + var_v0 + 0x67, (temp_lo * 0x76) + var_v0 + 0x4A, 0x90, 0x6E);
    } else if (arg0->unk_04 != -1) {
        func_83401B48(0x41, 0x15A, 0x4C, 0x3B);
    } else {
        func_83401B48(0x1E1, 0x172, 0x6C, 0x45);
    }
}

void ItemSelect_MainDraw(void) {
    static s32 D_83503F54 = 0;
    static s32 D_83503F58 = 0;
    static s32 D_83503F5C = 0;
    static s32 D_83503F60 = 0;

    UNUSED s32 pad;
    s32 sp38;
    f32 temp_fv0;
    s32 sp30;
    s32 sp2C;
    s32 var_a2;
    f32 sp24;
    f32 var_fv1;

    func_83402210(&gItemSelectContext, &sp30, &sp2C, gItemSelectContext.unk_00);
    Stage_BeginDisplayList();
    DrawHighlightBars();
    DrawGridBackground(0x1E, 0x2A, &gItemSelectContext);
    if (ItemSelect_ShowResult != 0) {
        if (gItemSelectContext.unk_04 == -1) {
            var_a2 = 1;
        } else {
            var_a2 = 0;
        }
        DrawAnimatedMonPanel(0x35, 0x15E, var_a2);

        switch (gItemSelectMode) {
            case 0:
                sp38 = 0;
                break;

            case 1:
                sp38 = 1;
                break;

            default:
                sp38 = 0;
                break;
        }

        sp24 = UpdateFadeTimer(&D_83503F54, &D_83503F58, 0x1E);
        temp_fv0 = UpdateFadeTimer(&D_83503F5C, &D_83503F60, 0xF);
        if ((gItemSelectContext.unk_04 == -1) && (sp2C >= 2)) {
            var_fv1 = temp_fv0;
        } else {
            var_fv1 = sp24;
        }
        DrawResultScreen(0x1E1, 0x172, sp38, var_fv1);
    }
    ItemSelect_DrawGrid(0x6B, 0x4E, &gItemSelectContext);
    DrawGridSelectionHighlight(&gItemSelectContext);
    DrawGridHelpBox(&gItemSelectContext, 0x9E, 0x16B);
    Stage_Advance();
}

void AdvanceResultAnim(unk_D_83407B38* arg0) {
    ItemSelect_ResultAnimTimer++;
    if (ItemSelect_ResultAnimTimer >= 0x15) {
        func_83400570(arg0->unk_20[arg0->unk_04]->unk_18);
        gSlotStatusFlags[arg0->unk_04] = 0;
        arg0->unk_04 = -1;
        gItemSelectState = 1;
        ItemSelect_ResultAnimTimer = 0;
    }
}

void BeginFadeOutAfterResult(unk_D_83407B38* arg0) {
    Camera* sp1C = arg0->unk_B0;

    if ((Cam_IsMonIndexDisplayable(sp1C) != 0) && (sp1C->unk_00 == 2)) {
        gItemSelectState = 4;
        ItemSelect_HighlightFlags = 0xFFFF;
        Stage_SetFillColor(0xFFFF);
        Stage_FadeOut(0xF);
    }
}

s32 ItemSelect_StateMachine(void) {
    static s32 D_83503F64 = 2;

    s32 sp1C = 1;
    s32 temp_v0_2;
    s32 var_a0;

    switch (gItemSelectState) {
        case 0:
            if (Stage_GetFadeState() == 0) {
                D_83503F64--;
                if (D_83503F64 <= 0) {
                    gItemSelectState = 1;
                }
            }
            break;

        case 1:
            ItemSelect_HighlightFlags &= 0xFF60;
            temp_v0_2 = ItemSelect_HandleInput(&gItemSelectContext);
            if (temp_v0_2 != 0) {
                gItemSelectState = 4;
                ItemSelect_HighlightFlags = 0xFFFF;
                if (temp_v0_2 != 2) {
                    Stage_SetFillColor(0xFFFF);
                    var_a0 = 0xF;
                } else {
                    Stage_SetFillColor(1);
                    var_a0 = 1;
                }
                Stage_FadeOut(var_a0);
            }
            break;

        case 2:
            AdvanceResultAnim(&gItemSelectContext);
            break;

        case 3:
            BeginFadeOutAfterResult(&gItemSelectContext);
            break;

        case 4:
            if (Stage_GetFadeState() == 1) {
                sp1C = 0;
            }
            break;
    }
    return sp1C;
}

void ItemSelect_ReadInputs(void) {
    Cont_StartReadInputs();
    Cont_ReadInputs();
    MenuInput_Init();
}

void ItemSelect_Loop(void) {
    if (ItemSelect_FadeInFlag != 0) {
        Stage_FadeIn(7);
    } else {
        Stage_FadeIn(1);
    }

    do {
        ItemSelect_ReadInputs();

        switch (gItemSelectState) {
            case 0:
            case 4:
                break;

            default:
                CamList_Update(&gItemSelectContext);
                break;
        }

        ItemSelect_MainDraw();
        func_834020D8();
    } while (ItemSelect_StateMachine() != 0);
}

s32 ItemSelect_ApplySelection(unk_D_83407B38* arg0) {
    UNUSED s32 pad[2];
    s32 sp1C;

    switch (gItemSelectMode) {
        case 0:
            sp1C = 0;
            break;

        case 1:
            sp1C = 2;
            break;

        default:
            sp1C = 0;
            break;
    }

    if (func_834006A0(0) != 0) {
        sp1C = 4;
    }

    if (gItemSelectMode == 2) {
        func_834021D8(arg0, &D_83407B18.unk_00);
    } else {
        func_834021D8(arg0, &D_83407B10);
        if (sp1C == 0) {
            Selection_Reset(&D_83407B10);
        }
    }

    return sp1C;
}

void func_83503C9C(s32 arg0, s32 arg1) {
    Stage* sp24;

    main_pool_push_state('ALBM');

    Gfx_InitBuffers(0x10000, 0);
    sp24 = Stage_Create(1, 0, 2, 0, 2, 1);
    gTextObjectHandle = Text_Init(0x18, 0);

    ASSET_LOAD(D_1000000, common_menu1_ui, 0);
    ASSET_LOAD(D_5000000, snap_mode_ui, 0);
    ASSET_LOAD(D_3000000, gallery_ui, 0);
    ASSET_LOAD(D_04000000, album_ui, 0);

    FRAGMENT_LOAD(fragment31);

    AssetManager_LoadArchives();
    gStadiumModelArchive = ASSET_LOAD2(stadium_models, 1, 1);
    MessageBank_Init();
    Text_LoadMessageBanks();
    ItemSelect_Init(arg0, arg1);
    Stage_Set(sp24);
    ItemSelect_Loop();
    Stage_Destroy();
    FontManager_Free();
    Gfx_FreeBuffers();

    main_pool_pop_state('ALBM');

    ItemSelect_ApplySelection(&gItemSelectContext);
}
