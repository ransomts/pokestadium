#include "global.h"
#include "1CF30.h"
#include "include/string.h"
#include "src/3FB0.h"
#include "src/6A40.h"
#include "src/20470.h"
#include "src/6BC0.h"
#include "src/F420.h"
#include "src/memory.h"
#include "stdarg.h"
#include "lib/ultralib/src/libc/xstdio.h"

// .bss
unk_D_800AC870* gFontManager;

void Gfx_DrawTextureRect(s16 arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5, s16 arg6, s16 arg7, s32 arg8) {
    ClipRect sp30;

    Gfx_MakeClipRect(&sp30, arg0, arg1, (arg0 + arg2) - 1, (arg1 + arg3) - 1);

    if (Gfx_IntersectClip(&sp30) != 0) {
        if (arg6 != 0) {
            arg4 += ((sp30.x1 - arg0) * arg6) >> 5;
        }

        if (arg7 != 0) {
            arg5 += ((sp30.y2 - arg1) * arg7) >> 5;
        }

        if (arg8 == 0x200000) {
            arg6 *= 4;
        } else {
            sp30.y1 += 1;
            sp30.x2 += 1;
        }

        gSPTextureRectangle(gDisplayListHead++, sp30.x1 * 4, sp30.y2 * 4, sp30.y1 * 4, sp30.x2 * 4, G_TX_RENDERTILE,
                            arg4, arg5, arg6, arg7);
    }
}

void Gfx_DrawTextureRect2(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    Gfx_DrawTextureRect(arg0, arg1, (arg2 - arg0) + 1, (arg3 - arg1) + 1, 0, 0, arg4, arg5, arg6);
}

void Gfx_FillRect(s16 arg0, s16 arg1, s16 arg2, s16 arg3, u8 arg4, u8 arg5, u8 arg6) {
    gDPSetPrimColor(gDisplayListHead++, 0, 0, arg4, arg5, arg6, 0xFF);

    Gfx_DrawTextureRect(arg0, arg1, arg2, arg3, 0, 0, 0, 0, 0);
}

void Gfx_FillRectRGBA(s16 arg0, s16 arg1, s16 arg2, s16 arg3, u8 arg4, u8 arg5, u8 arg6, u8 arg7) {
    gDPSetPrimColor(gDisplayListHead++, 0, 0, arg4, arg5, arg6, arg7);

    Gfx_DrawTextureRect(arg0, arg1, arg2, arg3, 0, 0, 0, 0, 0);
}

void Gfx_DrawSpriteRGBA16(s16 arg0, s16 arg1, s16 arg2, s16 arg3, u8* arg4, s16 arg5, s32 arg6) {
    gDPLoadTextureBlock(gDisplayListHead++, arg4, G_IM_FMT_RGBA, G_IM_SIZ_16b, arg5, arg3, 0,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                        G_TX_NOLOD);

    Gfx_DrawTextureRect(arg0, arg1, arg2, arg3, 0, 0, 0x400, 0x400, arg6);
}

void Gfx_DrawSpriteRGBA32(s16 arg0, s16 arg1, s16 arg2, s16 arg3, u8* arg4, s16 arg5, s32 arg6) {
    gDPLoadTextureBlock(gDisplayListHead++, arg4, G_IM_FMT_RGBA, G_IM_SIZ_32b, arg5, arg3, 0,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                        G_TX_NOLOD);

    Gfx_DrawTextureRect(arg0, arg1, arg2, arg3, 0, 0, 0x400, 0x400, arg6);
}

void Gfx_DrawSpriteIA8(s16 arg0, s16 arg1, s16 arg2, s16 arg3, u8* arg4, s16 arg5, s32 arg6) {
    gDPLoadTextureBlock(gDisplayListHead++, arg4, G_IM_FMT_IA, G_IM_SIZ_8b, arg5, arg3, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    Gfx_DrawTextureRect(arg0, arg1, arg2, arg3, 0, 0, 0x400, 0x400, arg6);
}

void Gfx_DrawSpriteIA16(s16 arg0, s16 arg1, s16 arg2, s16 arg3, u8* arg4, s16 arg5, s32 arg6) {
    gDPLoadTextureBlock(gDisplayListHead++, arg4, G_IM_FMT_IA, G_IM_SIZ_16b, arg5, arg3, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    Gfx_DrawTextureRect(arg0, arg1, arg2, arg3, 0, 0, 0x400, 0x400, arg6);
}

void Gfx_DrawSpriteI4(s16 arg0, s16 arg1, s16 arg2, s16 arg3, u8* arg4, s16 arg5, s32 arg6) {
    gDPLoadTextureBlock_4b(gDisplayListHead++, arg4, G_IM_FMT_I, arg5, arg3, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                           G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

    Gfx_DrawTextureRect(arg0, arg1, arg2, arg3, 0, 0, 0x400, 0x400, arg6);
}

void Gfx_DrawSpriteI8(s16 arg0, s16 arg1, s16 arg2, s16 arg3, u8* arg4, s16 arg5, s32 arg6) {
    gDPLoadTextureBlock(gDisplayListHead++, arg4, G_IM_FMT_I, G_IM_SIZ_8b, arg5, arg3, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

    Gfx_DrawTextureRect(arg0, arg1, arg2, arg3, 0, 0, 0x400, 0x400, arg6);
}

void Gfx_DrawSpriteI16(s16 arg0, s16 arg1, s16 arg2, s16 arg3, u8* arg4, s16 arg5, s32 arg6) {
    gDPLoadTextureBlock(gDisplayListHead++, arg4, G_IM_FMT_I, G_IM_SIZ_16b, arg5, arg3, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

    Gfx_DrawTextureRect(arg0, arg1, arg2, arg3, 0, 0, 0x400, 0x400, arg6);
}

void func_8001D560(s16 arg0, s16 arg1, s16 arg2, s16 arg3, u8* arg4, u8* arg5, s16 arg6, s32 arg7) {
    gDPLoadTextureBlock(gDisplayListHead++, arg4, G_IM_FMT_RGBA, G_IM_SIZ_16b, arg6, arg3, 0,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                        G_TX_NOLOD);
    gDPLoadMultiBlock(gDisplayListHead++, arg5, 0x0100, 1, G_IM_FMT_I, G_IM_SIZ_8b, arg6, arg3, 0,
                      G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                      G_TX_NOLOD);

    Gfx_DrawTextureRect(arg0, arg1, arg2, arg3, 0, 0, 0x400, 0x400, arg7);
}

void Gfx_DrawTextureAtlas(u8* arg0) {
    s32 i;
    s32 j;

    gDPPipeSync(gDisplayListHead++);
    gDPSetCycleType(gDisplayListHead++, G_CYC_1CYCLE);
    gDPSetRenderMode(gDisplayListHead++, G_RM_OPA_SURF, G_RM_OPA_SURF2);
    gDPSetTexturePersp(gDisplayListHead++, G_TP_NONE);
    gDPSetScissor(gDisplayListHead++, G_SC_NON_INTERLACE, 0, 0, 640, 480);
    gDPSetCombineMode(gDisplayListHead++, G_CC_DECALRGB, G_CC_DECALRGB);
    gDPPipeSync(gDisplayListHead++);

    for (i = 0; i < 0x1E0; i += 0x20) {
        for (j = 0; j < 0x280; j += 0x20) {
            gDPLoadTextureBlock(gDisplayListHead++, arg0, G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 16, 0,
                                G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK,
                                G_TX_NOLOD, G_TX_NOLOD);
            gSPTextureRectangle(gDisplayListHead++, j << 2, i << 2, (j + 0x20) << 2, (i + 0x20) << 2, G_TX_RENDERTILE,
                                0, 0, 0x0200, 0x0200);
            arg0 += 0x200;
        }
    }
}

void Gfx_DrawClippedTextureRegion(u32 arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4) {
    s32 div = 32;
    s16 sp9A;
    s16 sp98;
    s16 sp36;
    s16 sp30;
    s16 j;
    s16 i;
    s16 temp_t4;
    s16 temp_t5;
    s16 var_s2;
    s16 var_t1;
    s16 s1;
    s16 s2;

    sp9A = arg1 + arg3;
    sp98 = arg2 + arg4;

    gDPPipeSync(gDisplayListHead++);
    gDPSetCycleType(gDisplayListHead++, G_CYC_1CYCLE);
    gDPSetRenderMode(gDisplayListHead++, G_RM_OPA_SURF, G_RM_OPA_SURF2);
    gDPSetTexturePersp(gDisplayListHead++, G_TP_NONE);
    gDPSetScissor(gDisplayListHead++, G_SC_NON_INTERLACE, 0, 0, 640, 480);
    gDPSetCombineMode(gDisplayListHead++, G_CC_DECALRGB, G_CC_DECALRGB);
    gDPPipeSync(gDisplayListHead++);

    for (i = (arg2 >> 5) << 5; i < sp98; i += 0x20) {
        for (j = (arg1 >> 5) << 5; j < sp9A; j += 0x20) {
            if (j < arg1) {
                temp_t5 = arg1;
            } else {
                temp_t5 = j;
            }

            if (sp9A < j + 0x20) {
                var_s2 = sp9A;
            } else {
                var_s2 = j + 0x20;
            }

            if (i < arg2) {
                temp_t4 = arg2;
            } else {
                temp_t4 = i;
            }

            if (sp98 < i + 0x20) {
                var_t1 = sp98;
            } else {
                var_t1 = i + 0x20;
            }

            s1 = temp_t5 - j;
            s2 = temp_t4 - i;

            gDPLoadTextureBlock(gDisplayListHead++, ((((i / div) * 0x14) + (j / div)) << 9) + arg0, G_IM_FMT_RGBA,
                                G_IM_SIZ_16b, 16, 16, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                                G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
            gSPTextureRectangle(gDisplayListHead++, temp_t5 * 4, temp_t4 * 4, var_s2 * 4, var_t1 * 4, G_TX_RENDERTILE,
                                s1 << 4, s2 << 4, 0x0200, 0x0200);
        }
    }
}

void Gfx_DrawTileMap16x16(s16 arg0, s16 arg1, s16 arg2, f32 arg3, Vtx* arg4, u32 arg5) {
    s16 j;
    s16 i;
    Vec3s spCC;
    Vec3f spC0;
    Vec3f spB4;
    MtxF* temp_s4;
    FramebufferImage* temp_s1;
    Vp* temp_s2;
    MtxF* temp_s0;
    MtxF* temp_s3;

    temp_s3 = GfxAlloc(0x40);
    temp_s4 = GfxAlloc(0x40);
    temp_s0 = GfxAlloc(0x40);
    temp_s2 = GfxAlloc(0x10);
    temp_s1 = Gfx_GetCurrentFramebuffer();

    func_8000EB70(&spCC, 0, 0, arg2);
    Vec3f_Set(&spC0, arg0, arg1, 0.0f);
    Vec3f_Set(&spB4, arg3, arg3, 1.0f);
    Matrix_RotateTranslate(temp_s0, &spC0, &spCC);
    Matrix_Scale(temp_s0, temp_s0, &spB4);
    Matrix_ConvertToMtx(temp_s3, temp_s0);
    SetViewport(temp_s2, temp_s1->width, temp_s1->height);

    gSPViewport(gDisplayListHead++, (u32)temp_s2 & 0x1FFFFFFF);

    guOrtho(temp_s4, 0.5f, temp_s1->width - 0.5f, temp_s1->height - 0.5f, 0.5f, -2.0f, 2.0f, 1.0f);

    gSPMatrix(gDisplayListHead++, (u32)temp_s4 & 0x1FFFFFFF, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
    gSPMatrix(gDisplayListHead++, (u32)temp_s3 & 0x1FFFFFFF, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gDPPipeSync(gDisplayListHead++);
    gDPSetCycleType(gDisplayListHead++, G_CYC_1CYCLE);
    gDPSetTexturePersp(gDisplayListHead++, G_TP_PERSP);
    gDPSetRenderMode(gDisplayListHead++, G_RM_OPA_SURF, G_RM_OPA_SURF2);
    gDPSetCombineMode(gDisplayListHead++, G_CC_DECALRGB, G_CC_DECALRGB);
    gSPClearGeometryMode(gDisplayListHead++, G_ZBUFFER | G_CULL_BOTH | G_LIGHTING);
    gSPTexture(gDisplayListHead++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);

    for (i = 0; i < 15; i++) {
        for (j = 0; j < 20; j++) {
            gDPLoadTextureBlock(gDisplayListHead++, arg5, G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 16, 0,
                                G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, 4, 4, G_TX_NOLOD, G_TX_NOLOD);
            gSPVertex(gDisplayListHead++, arg4, 4, 0);
            gSP2Triangles(gDisplayListHead++, 0, 1, 2, 0, 0, 2, 3, 0);

            arg5 += 0x200;
            arg4 += 4;
        }
    }
}

Vtx* AllocateTileMapVertices(void) {
    Vtx* sp54;
    Vtx* var_s0;
    s16 i;
    s16 j;

    sp54 = main_pool_alloc(0x4B00, 0);
    if (sp54 != NULL) {
        var_s0 = sp54;

        for (i = -0xF0; i < 0xF0; i += 0x20) {
            for (j = -0x140; j < 0x140; j += 0x20) {
                SetTileVertex(var_s0++, j + 0, i + 0, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF);
                SetTileVertex(var_s0++, j + 0, i + 0x20, 0, 0, 0x200, 0xFF, 0xFF, 0xFF, 0xFF);
                SetTileVertex(var_s0++, j + 0x20, i + 0x20, 0, 0x200, 0x200, 0xFF, 0xFF, 0xFF, 0xFF);
                SetTileVertex(var_s0++, j + 0x20, i + 0, 0, 0x200, 0, 0xFF, 0xFF, 0xFF, 0xFF);
            }
        }
    }

    return sp54;
}

void SetTileVertex(Vtx* arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5, u8 arg6, u8 arg7, u8 arg8, u8 arg9) {
    arg0->v.ob[0] = arg1;
    arg0->v.ob[1] = arg2;
    arg0->v.ob[2] = arg3;
    arg0->v.flag = 0;
    arg0->v.tc[0] = arg4;
    arg0->v.tc[1] = arg5;
    arg0->v.cn[0] = arg6;
    arg0->v.cn[1] = arg7;
    arg0->v.cn[2] = arg8;
    arg0->v.cn[3] = arg9;
}

void SetViewport(Vp* arg0, s16 arg1, s16 arg2) {
    arg0->vp.vtrans[0] = arg1 * 2;
    arg0->vp.vtrans[1] = arg2 * 2;
    arg0->vp.vtrans[2] = 0x1FF;
    arg0->vp.vtrans[3] = 0;
    arg0->vp.vscale[0] = arg1 * 2;
    arg0->vp.vscale[1] = arg2 * 2;
    arg0->vp.vscale[2] = 0x1FF;
    arg0->vp.vscale[3] = 0;
}

u8 GetCharIndexFromFontTables(u16 arg0) {
    u8 var_v1 = 0;

    if ((arg0 >= 0x20) && (arg0 < 0x80)) {
        var_v1 = ((u8*)D_8006F630)[arg0];
    } else if ((arg0 >= 0xA0) && (arg0 < 0x100)) {
        var_v1 = ((u8*)D_8006F608)[sizeof(Gfx) + arg0];
    }

    return var_v1;
}

u8 Text_GetCharWidth(FontBankInfo* arg0, u16 arg1) {
    s32 idx = GetCharIndexFromFontTables(arg1);

    return arg0->unk_04[idx];
}

void func_8001E7C0(UNUSED s32 arg0, UNUSED s32 arg1) {
    gFontManager = NULL;
}

void Text_UnloadFont(UNUSED s32 arg0, s32 arg1) {
    if (gFontManager != NULL) {
        gFontManager->unk_00[arg1].unk_04 = 0;
        gFontManager->unk_00[arg1].unk_08 = 0;
    }
}

s32 GetFontBank(s32 arg0) {
    s32 var_v1 = 0;

    if (arg0 != 1) {
        if (arg0 == 2) {
            var_v1 = 1;
        } else if (arg0 == 4) {
            var_v1 = 2;
        } else if (arg0 == 8) {
            var_v1 = 3;
        } else if (arg0 == 0x10) {
            var_v1 = 4;
        } else if (arg0 == 0x20) {
            var_v1 = 5;
        }
    }

    return var_v1;
}

void LoadFontBank(s32 arg0, s32 arg1, s32 arg2) {
    s32 sp1C;
    ret_func_8000484C* temp_v0_2;

    sp1C = GetFontBank(arg0);
    if (gFontManager->unk_00[sp1C].unk_04 == 0) {
        temp_v0_2 = BinArchive_GetFile(gFontManager->unk_48, sp1C);
        gFontManager->unk_50 = sp1C;
        gFontManager->unk_00[sp1C].unk_00 = arg1;
        gFontManager->unk_00[sp1C].unk_02 = arg2;
        gFontManager->unk_00[sp1C].unk_04 = temp_v0_2;
        gFontManager->unk_00[sp1C].unk_08 = &temp_v0_2->unk_90;
        main_pool_set_func(temp_v0_2, sp1C, &Text_UnloadFont);
    }
}

unk_D_800AC870* Text_Init(s32 arg0, s32 arg1) {
    gFontManager = main_pool_alloc_with_func(sizeof(*gFontManager), arg1, 'PRNT', func_8001E7C0);
    bzero(gFontManager, sizeof(*gFontManager));
    gFontManager->unk_48 = ASSET_LOAD2(fonts, 1, 1);
    LoadFontBanksFromMask(arg0);

    return gFontManager;
}

void func_8001E9CC(void) {
    main_pool_try_free(gFontManager);
}

void LoadFontBanksFromMask(s32 arg0) {
    if (gFontManager != NULL) {
        if (arg0 & 0x20) {
            LoadFontBank(0x20, 0x20, 0x20);
        }

        if (arg0 & 0x10) {
            LoadFontBank(0x10, 0x18, 0x18);
        }

        if (arg0 & 8) {
            LoadFontBank(8, 0x18, 0x14);
        }

        if (arg0 & 4) {
            LoadFontBank(4, 0x10, 0x10);
        }

        if (arg0 & 2) {
            LoadFontBank(2, 0x10, 0xC);
        }

        if (arg0 & 1) {
            LoadFontBank(1, 0x10, 0xA);
        }
    }
}

void FreeFontBanks(s32 arg0) {
    if (gFontManager != NULL) {
        if (arg0 & 1) {
            if (gFontManager->unk_00[0].unk_04 != NULL) {
                main_pool_try_free(gFontManager->unk_00[0].unk_04);
            }
        }

        if (arg0 & 2) {
            if (gFontManager->unk_00[1].unk_04 != NULL) {
                main_pool_try_free(gFontManager->unk_00[1].unk_04);
            }
        }

        if (arg0 & 4) {
            if (gFontManager->unk_00[2].unk_04 != NULL) {
                main_pool_try_free(gFontManager->unk_00[2].unk_04);
            }
        }

        if (arg0 & 8) {
            if (gFontManager->unk_00[3].unk_04 != NULL) {
                main_pool_try_free(gFontManager->unk_00[3].unk_04);
            }
        }

        if (arg0 & 0x10) {
            if (gFontManager->unk_00[4].unk_04 != NULL) {
                main_pool_try_free(gFontManager->unk_00[4].unk_04);
            }
        }

        if (arg0 & 0x20) {
            if (gFontManager->unk_00[5].unk_04 != NULL) {
                main_pool_try_free(gFontManager->unk_00[5].unk_04);
            }
        }
    }
}

void Text_SetFont(s32 arg0, s32 arg1) {
    if (gFontManager != NULL) {
        gFontManager->unk_50 = GetFontBank(arg0);
        gFontManager->unk_51 = arg1;
        gFontManager->unk_53 &= ~2;
    }
}

s32 GetFontBankInfo(s32 arg0, FontBankInfo* arg1) {
    s32 var_v1 = 0;

    if ((arg1 != NULL) && (gFontManager != NULL)) {
        *arg1 = gFontManager->unk_00[GetFontBank(arg0)];
        var_v1 = 1;
    }

    return var_v1;
}

s16 Text_DrawGlyph(s16 arg0, s16 arg1, s16 arg2) {
    FontBankInfo* temp_s0;
    s32 sp88;
    s16 sp86;

    temp_s0 = &gFontManager->unk_00[gFontManager->unk_50];
    sp88 = GetCharIndexFromFontTables(arg2) * temp_s0->unk_00 * temp_s0->unk_02;
    sp86 = Text_GetCharWidth(temp_s0, arg2);

    if ((gFontManager->unk_53 & 1) && !(gFontManager->unk_53 & 2)) {
        gFontManager->unk_53 |= 2;

        gDPLoadMultiBlock(gDisplayListHead++, (u32)temp_s0->unk_08 + (temp_s0->unk_00 * 0x90 * temp_s0->unk_02), 0x0100,
                          1, G_IM_FMT_I, G_IM_SIZ_8b, temp_s0->unk_00, temp_s0->unk_02, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                          G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    }

    if ((u32)temp_s0->unk_08 + sp88 != gFontManager->unk_4C) {
        gFontManager->unk_4C = (u32)temp_s0->unk_08 + sp88;

        gDPLoadTextureBlock(gDisplayListHead++, (u32)temp_s0->unk_08 + sp88, G_IM_FMT_IA, G_IM_SIZ_8b, temp_s0->unk_00,
                            temp_s0->unk_02, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK,
                            G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    }

    Gfx_DrawTextureRect(arg0, arg1, sp86, temp_s0->unk_02, 0, 0, 0x400, 0x400, 0);

    arg0 += sp86 + gFontManager->unk_51;
    if (gFontManager->unk_50 >= 2) {
        arg0 -= 2;
    } else {
        arg0 -= 1;
    }

    return arg0;
}

char* func_8001F1C4(char* buffer, const char* data, u32 size) {
    return (char*)memcpy(buffer, data, size) + size;
}

void Text_Print(s32 x, s32 y, const char* fmt, ...) {
    char sp50[0x100];
    s32 temp_s5 = x - 1;
    s32 var_s1 = x - 1;
    s32 temp_v0;
    s32 var_v0;
    char* var_s0;
    s16 chr;

    va_list args;
    va_start(args, fmt);

    temp_v0 = _Printf(func_8001F1C4, sp50, fmt, args);

    if (temp_v0 > 0) {
        sp50[temp_v0] = 0;
        chr = *sp50;
        var_s0 = &sp50[1];

        while (chr != 0) {
            var_v0 = 1;

            if (!(gFontManager->unk_53 & 4) && (chr == 0xA)) {
                var_s1 = temp_s5;
                var_v0 = 0;
                y += gFontManager->unk_52;
            }

            if (var_v0 != 0) {
                var_s1 = Text_DrawGlyph(var_s1, y, chr & 0xFF);
            }

            chr = *var_s0;
            var_s0++;
        }
    }

    va_end(args);
}

void Text_PutChar(s32 arg0, s32 arg1, s32 arg2) {
    Text_DrawGlyph(arg0 - 1, arg1, arg2 & 0xFF);
}

void Text_SetEnvColor(s32 r, s32 g, s32 b, s32 a) {
    gDPSetEnvColor(gDisplayListHead++, r, g, b, a);
}

void Text_SetPrimColor(s32 r, s32 g, s32 b, s32 a) {
    gDPSetPrimColor(gDisplayListHead++, 0, 0, r, g, b, a);
}

void Text_SetLineHeight(s32 arg0) {
    gFontManager->unk_52 = arg0;
}

void Text_SetNoWordWrap(void) {
    gFontManager->unk_53 |= 4;
}

void Text_EnableWordWrap(void) {
    gFontManager->unk_53 &= ~4;
}

void Text_ResetState(void) {
    gFontManager->unk_53 = 0;
    gFontManager->unk_52 = 0x28;
    gFontManager->unk_4C = 0;

    gSPDisplayList(gDisplayListHead++, D_8006F710);
}

void Text_SetupDL(void) {
    gSPDisplayList(gDisplayListHead++, D_8006F750);
}

void Text_BeginRender(void) {
    gFontManager->unk_53 |= 1;
    gFontManager->unk_53 &= ~2;

    gSPDisplayList(gDisplayListHead++, D_8006F768);
}

void Text_EndRender(void) {
    gFontManager->unk_53 &= ~3;
    gSPDisplayList(gDisplayListHead++, D_8006F798);
}

void Text_DrawWindowRect(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7) {
    gSPDisplayList(gDisplayListHead++, D_8006F498);

    Gfx_FillRectRGBA(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7);

    gSPDisplayList(gDisplayListHead++, D_8006F630);
}

s32 MeasureTextWidth(s32 x, s32 y, const char* fmt, ...) {
    s32 temp_s0;
    s32 temp_v0;
    s32 var_s2;
    char sp5C[0x100];
    s32 var_a0;
    s32 chr;
    u8* var_s1;
    FontBankInfo* temp_s4;

    va_list args;
    va_start(args, fmt);

    var_s2 = 0;
    if (x == 0) {
        var_a0 = gFontManager->unk_50;
    } else {
        var_a0 = GetFontBank(x);
    }

    temp_s4 = &gFontManager->unk_00[var_a0];
    if (temp_s4->unk_04 != NULL) {
        temp_s0 = 0;
        temp_v0 = _Printf(func_8001F1C4, sp5C, fmt, args);
        if (temp_v0 > 0) {
            sp5C[temp_v0] = 0;

            chr = *sp5C;
            var_s1 = &sp5C[1];

            while (chr != 0) {
                if (chr == 0xA) {
                    temp_s0 = 0;
                } else {
                    temp_s0 += Text_GetCharWidth(temp_s4, chr & 0xFF) + y;
                    if (var_a0 >= 2) {
                        temp_s0 -= 2;
                    } else {
                        temp_s0 -= 1;
                    }
                }

                if (var_s2 < temp_s0) {
                    var_s2 = temp_s0;
                }

                chr = *var_s1;
                var_s1++;
            }
        }
    }

    va_end(args);

    return var_s2;
}

u8 MeasureCharWidth(s32 arg0, s32 arg1) {
    return Text_GetCharWidth(&gFontManager->unk_00[gFontManager->unk_50], arg1 & 0xFF);
}
