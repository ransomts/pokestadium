#include "fragment43.h"
#include "src/1CF30.h"
#include "src/20470.h"
#include "src/22630.h"
#include "src/26820.h"
#include "src/6BC0.h"
#include "src/C030.h"
#include "src/memory.h"

unk_D_83402EE0 gDisplayableMonIndices[24];
s32 gMonSelectionFlags[24];
unk_D_83403C60 gGalleryEntries[36];
static unk_D_83403C60 gGalleryEntriesBackup[36];
unk_D_83403C60 gGalleryCamEntries[21];
static unk_D_83403C60 gGalleryCamEntriesBackup[21];
unk_D_83403C60* gCurrentCamEntry;
unk_D_83403C60* gCurrentCamEntryPage;
static unk_D_83406EB0* gCurrentCamEntrySpecial;
unk_D_83407AC8 D_83407AC8;
s32 gGallerySpecialUnlocked;
s32 gGallerySpecialViewed;
s32 gGalleryAudioStateFlag;
static unk_func_80027FA0 D_83407AF0;
unk_D_83407B00 gGallerySelection;
unk_D_83407B00 gGalleryMainSelectionCam;
unk_D_83407B00 gGallerySubSelection;
unk_D_83407B00 gGalleryTertiarySelection;
unk_D_83407B18 gGalleryFinalSelection;
unk_D_83407B00 gGalleryMainSelection;
unk_D_83407B38 gGalleryCamList;

s32 D_83402E20 = 0;
s32 D_83402E24 = 1;
s32 D_83402E28 = 0;
unk_D_83403C60* gCurrentGalleryEntryPtr = NULL;

void Gallery_Init(void) {
    s32 i;

    main_pool_push_state('bkgl');

    GbsEnsureBankLoaded(2);
    bzero(gGalleryEntries, sizeof(unk_D_83403C60) * 36);
    bzero(gGalleryEntriesBackup, sizeof(unk_D_83403C60) * 36);
    bzero(&gGalleryCamEntries, sizeof(unk_D_83403C60) * 21);
    bzero(&gGalleryCamEntriesBackup, sizeof(unk_D_83403C60) * 21);

    for (i = 0; i < 36; i++) {
        GbsReadBlockEntry(0x16, 0, i, &gGalleryEntries[i]);
    }

    _bcopy(&gGalleryEntries, &gGalleryEntriesBackup, sizeof(unk_D_83403C60) * 36);

    for (i = 0; i < 21; i++) {
        GbsReadBlockEntry(0x17, 0, i, &gGalleryCamEntries[i]);
    }

    GBAudio_ResetState(&D_83407AF0, 1);
    if (D_83407AF0.unk_00 == 0x1F8) {
        gGalleryAudioStateFlag = 1;
    } else {
        gGalleryAudioStateFlag = 0;
    }

    gCurrentCamEntry = &gGalleryCamEntries[0];
    gCurrentCamEntryPage = &gGalleryCamEntries[4];
    gCurrentCamEntrySpecial = &gGalleryCamEntries[20];

    if (Gallery_IsUnlocked(gCurrentCamEntrySpecial) != 0) {
        gGallerySpecialUnlocked = 1;
    } else {
        gGallerySpecialUnlocked = 0;
    }

    if (Gallery_IsViewed(gCurrentCamEntrySpecial) != 0) {
        gGallerySpecialViewed = 1;
        gCurrentCamEntrySpecial->unk_6C &= ~2;

        for (i = 0; i < 21; i++) {
            GbsWriteBlockEntry(0x17, 0, i, &gGalleryCamEntries[i]);
        }

        GbsProcessBankWrites(2);
        GbsSyncBank(2);
    } else {
        gGallerySpecialViewed = 0;
    }

    _bcopy(&gGalleryCamEntries, &gGalleryCamEntriesBackup, sizeof(unk_D_83403C60) * 21);

    main_pool_pop_state('bkgl');

    GallerySelection_Init(&gGalleryMainSelection);
    Selection_Reset(&gGalleryMainSelectionCam);
    Selection_Reset(&gGallerySubSelection);
    Selection_Reset(&gGalleryTertiarySelection);
    Selection_Reset(&gGalleryFinalSelection.unk_00);
    Cam_ResetUnkF90();
    CamList_Init(&gGalleryCamList, 0x3C, 0x2D, 0x10, 4, 0, 0, gCurrentCamEntryPage, 0x10, 0);
}

s32 Gallery_IsUnlocked(unk_D_83406EB0* arg0) {
    s32 var_v1 = 0;

    if (arg0->unk_6C & 1) {
        var_v1 = 1;
    }
    return var_v1;
}

s32 Gallery_IsViewed(unk_D_83406EB0* arg0) {
    s32 var_v1 = 0;

    if (arg0->unk_6C & 2) {
        var_v1 = 1;
    }
    return var_v1;
}

s32 Gallery_CompareEntries(unk_D_83403C60* arg0, unk_D_83403C60* arg1, s32 arg2) {
    s32 sp1C = 0;

    if (bcmp(arg0, arg1, arg2) != 0) {
        sp1C = 1;
    }
    return sp1C;
}

s32 Gallery_CheckForChanges(void) {
    s32 sp1C = 0;

    if (gGallerySpecialUnlocked != 0) {
        gCurrentCamEntrySpecial->unk_6C |= 1;
    } else {
        gCurrentCamEntrySpecial->unk_6C &= ~1;
    }

    if (gGallerySpecialViewed != 0) {
        gCurrentCamEntrySpecial->unk_6C |= 2;
    } else {
        gCurrentCamEntrySpecial->unk_6C &= ~2;
    }

    if ((Gallery_CompareEntries(gGalleryEntries, gGalleryEntriesBackup, 0x13B0) != 0) || (Gallery_CompareEntries(gGalleryCamEntries, gGalleryCamEntriesBackup, 0xB7C) != 0)) {
        sp1C = 1;
    }
    return sp1C;
}

s32 Gallery_SaveChanges(s32 arg0, s32 arg1) {
    s32 i;
    s32 sp28;

    if (arg1 != 0) {
        StickerStation_SetCommand(0xCC);
    }

    main_pool_push_state('bkgl');

    GbsEnsureBankLoaded(2);
    if (arg0 != 0) {
        sp28 = Gallery_CheckForChanges();
    } else {
        sp28 = 1;
    }

    if (sp28 != 0) {
        for (i = 0; i < 36; i++) {
            GbsWriteBlockEntry(0x16, 0, i, &gGalleryEntries[i]);
        }

        for (i = 0; i < 21; i++) {
            GbsWriteBlockEntry(0x17, 0, i, &gGalleryCamEntries[i]);
        }

        GbsProcessBankWrites(2);
        GbsSyncBank(2);
    }

    main_pool_pop_state('bkgl');

    if (arg1 != 0) {
        StickerStation_SetCommand(0x33);
    }

    return sp28;
}

void Gallery_Terminate(void) {
}

void Gallery_Reset(void) {
    D_83402E20 = 0;
    bzero(gDisplayableMonIndices, 0xD20);
    bzero(gMonSelectionFlags, 0x60);
    Selection_Reset(&gGallerySelection);
}

void Gallery_ClearEntry(unk_D_83403C60* arg0) {
    bzero(arg0, sizeof(unk_D_83403C60));
}

void Gallery_SwapEntries(unk_D_83403C60* arg0, unk_D_83403C60* arg1) {
    unk_D_83403C60 sp4;

    sp4 = *arg0;
    *arg0 = *arg1;
    *arg1 = sp4;
}

s32 Gallery_IsEntryEqual(unk_D_83403C60* arg0, unk_D_83403C60* arg1) {
    s32 sp1C = 0;

    if (bcmp(arg0, arg1, sizeof(unk_D_83403C60)) == 0) {
        sp1C = 1;
    }
    return sp1C;
}

void Gallery_SetCurrentEntry(unk_D_83403C60* arg0) {
    gCurrentGalleryEntryPtr = arg0;
}

unk_D_83403C60* Gallery_GetCurrentEntry(s32 arg0) {
    unk_D_83403C60* ret = gCurrentGalleryEntryPtr;

    if (arg0 != 0) {
        gCurrentGalleryEntryPtr = NULL;
    }

    return ret;
}

void GallerySelection_Init(unk_D_83407B00* arg0) {
    arg0->unk_00 = 0;
    arg0->unk_04 = -1;
}

s32 Text_CountLines(s8* arg0) {
    s32 var_v1 = 1;

    while (*arg0 != '\x00') {
        if (*arg0 == '\n') {
            var_v1++;
        }
        arg0++;
    }

    return var_v1;
}

s32 CountDisplayableMonIndices(unk_D_83403C60* arg0, s32 arg1, s32 arg2) {
    s32 var_s0 = 0;
    s32 i;

    for (i = 0; i < arg1; i++) {
        if (arg2 != 0) {
            if (IsMonIndexDisplayable(&arg0[i]) != 0) {
                var_s0++;
            }
        } else if (IsMonIndexDisplayable(&arg0[i]) == 0) {
            var_s0++;
        }
    }

    return var_s0;
}

s32 FindNthDisplayableMonIndex(unk_D_83403C60* arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 var_s0 = arg2;
    s32 var_s1 = -1;

    while (true) {
        if (IsMonIndexDisplayable(&arg0[var_s0]) == 0) {
            var_s1++;
        }

        if (var_s1 == arg3) {
            break;
        }

        var_s0 = (var_s0 + 1) % arg1;
    }
    return var_s0;
}

s32 FindFirstUndisplayedMonIndex(unk_D_83403C60* arg0, s32 arg1) {
    s32 i;
    s32 sp28 = -1;

    for (i = 0; i < arg1; i++) {
        if (IsMonIndexDisplayable(&arg0[i]) == 0) {
            sp28 = i;
            break;
        }
    }

    return sp28;
}

void Gallery_DrawGradientPanel(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    Color_RGB8 sp24 = { 0x00, 0x64, 0xFF };
    Color_RGB8 sp20 = { 0x64, 0xFF, 0xFF };

    DrawGradientPanel(arg0, arg1, arg2, arg3, &sp24, &sp20);
}

void Gallery_DrawBorderedRect(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u8 arg4, u8 arg5, u8 arg6, u8 arg7) {
    s16 var_s2;
    s16 var_s3;
    s16 tmp1;
    s16 tmp2;

    if (arg2 >= 0x20) {
        var_s3 = 0x10;
    } else {
        var_s3 = arg2 / 2;
    }

    if (arg3 >= 0x20) {
        var_s2 = 0x10;
    } else {
        var_s2 = arg3 / 2;
    }

    tmp1 = arg2 - (var_s3 * 2);
    tmp2 = arg3 - (var_s2 * 2);

    gSPDisplayList(gDisplayListHead++, gPrefDL_Border);
    gDPSetEnvColor(gDisplayListHead++, arg4, arg5, arg6, arg7);

    gDPLoadTextureBlock_4b(gDisplayListHead++, D_300C440, G_IM_FMT_I, 16, 16, 0, G_TX_NOMIRROR | G_TX_WRAP,
                           G_TX_NOMIRROR | G_TX_WRAP, 5, 5, G_TX_NOLOD, G_TX_NOLOD);

    Gfx_DrawTextureRect(arg0, arg1, var_s3, var_s2, 0, 0, 0x4000 / var_s3, 0x4000 / var_s2, 0);

    gDPLoadTextureBlock_4b(gDisplayListHead++, D_300C4C0, G_IM_FMT_I, 16, 16, 0, G_TX_NOMIRROR | G_TX_WRAP,
                           G_TX_NOMIRROR | G_TX_WRAP, 5, 5, G_TX_NOLOD, G_TX_NOLOD);

    Gfx_DrawTextureRect((arg0 + arg2) - var_s3, arg1, var_s3, var_s2, 0, 0, 0x4000 / var_s3, 0x4000 / var_s2, 0);

    gDPLoadTextureBlock_4b(gDisplayListHead++, D_300C340, G_IM_FMT_I, 16, 16, 0, G_TX_NOMIRROR | G_TX_WRAP,
                           G_TX_NOMIRROR | G_TX_WRAP, 5, 5, G_TX_NOLOD, G_TX_NOLOD);

    Gfx_DrawTextureRect(arg0, (arg1 + arg3) - var_s2, var_s3, var_s2, 0, 0, 0x4000 / var_s3, 0x4000 / var_s2, 0);

    gDPLoadTextureBlock_4b(gDisplayListHead++, D_300C3C0, G_IM_FMT_I, 16, 16, 0, G_TX_NOMIRROR | G_TX_WRAP,
                           G_TX_NOMIRROR | G_TX_WRAP, 5, 5, G_TX_NOLOD, G_TX_NOLOD);

    Gfx_DrawTextureRect((arg0 + arg2) - var_s3, (arg1 + arg3) - var_s2, var_s3, var_s2, 0, 0, 0x4000 / var_s3,
                  0x4000 / var_s2, 0);

    gSPDisplayList(gDisplayListHead++, gPrefDL_Fill);

    if ((tmp1 > 0) && (tmp2 > 0)) {
        Gfx_FillRectRGBA(var_s3 + arg0, arg1, tmp1, var_s2, arg4, arg5, arg6, arg7);
        Gfx_FillRectRGBA(arg0, var_s3 + arg1, arg2, tmp2, arg4, arg5, arg6, arg7);
        Gfx_FillRectRGBA(var_s3 + arg0, (var_s3 + arg1) + tmp2, tmp1, var_s2, arg4, arg5, arg6, arg7);
    } else if (tmp1 > 0) {
        Gfx_FillRectRGBA(var_s3 + arg0, arg1, tmp1, arg3, arg4, arg5, arg6, arg7);
    } else if (tmp2 > 0) {
        Gfx_FillRectRGBA(arg0, var_s2 + arg1, arg2, tmp2, arg4, arg5, arg6, arg7);
    }

    gSPDisplayList(gDisplayListHead++, gPrefDL_End);
}

void DrawPanelWithTextures(s32 arg0, s32 arg1, s32 arg2, Color_RGBA8* arg3, Color_RGBA8* arg4) {
    gSPDisplayList(gDisplayListHead++, gDL_XluBorder);
    gDPSetEnvColor(gDisplayListHead++, arg4->r, arg4->g, arg4->b, arg4->a);
    gDPSetPrimColor(gDisplayListHead++, 0, 0, arg3->r, arg3->g, arg3->b, arg3->a);
    gDPLoadTextureBlock(gDisplayListHead++, D_300BF40, G_IM_FMT_IA, G_IM_SIZ_8b, 16, 32, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

    Gfx_DrawTextureRect(arg0, arg1, 0x10, 0x20, 0, 0, 0x400, 0x400, 0);

    gDPLoadTextureBlock(gDisplayListHead++, D_300C140, G_IM_FMT_IA, G_IM_SIZ_8b, 16, 32, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

    Gfx_DrawTextureRect((arg0 + arg2) - 0x10, arg1, 0x10, 0x20, 0, 0, 0x400, 0x400, 0);
    Gfx_DrawTextureRect(arg0 + 0x10, arg1, arg2 - 0x20, 0x20, 0, 0, 0, 0x400, 0);
}

void DrawVerticalTextureStrip(u16* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    s32 temp_v0;
    s32 tmp = 8;
    s32 i;

    for (i = 0; i < arg4; i += tmp) {
        temp_v0 = CLAMP_MIN(arg4 - i, tmp);

        gDPLoadTextureTile(gDisplayListHead++, &arg0[i * arg3], G_IM_FMT_RGBA, G_IM_SIZ_16b, arg3, 0, 0, 0, arg3,
                           temp_v0 - 1, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK,
                           G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

        if (arg5 != 0) {
            Gfx_DrawTextureRect(arg1, arg2 + i, arg3, temp_v0, (arg3 - 1) << 5, 0, -0x400, 0x400, 0);
        } else {
            Gfx_DrawTextureRect(arg1, arg2 + i, arg3, temp_v0, 0, 0, 0x400, 0x400, 0);
        }
    }
}

void Gallery_FillRect(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    gDPFillRectangle(gDisplayListHead++, arg0, arg1, (arg0 + arg2) - 1, (arg1 + arg3) - 1);
}

void DrawRectBorder(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    UNUSED s32 pad;

    gSPDisplayList(gDisplayListHead++, gDL_FillCycle);
    gDPSetFillColor(gDisplayListHead++, 0xFFFFFFFF);

    Gallery_FillRect(arg0 - arg4, arg1 - arg4, (arg4 * 2) + arg2, arg4);
    Gallery_FillRect(arg0 - arg4, arg1 + arg3, (arg4 * 2) + arg2, arg4);
    Gallery_FillRect(arg0 - arg4, arg1, arg4, arg3);
    Gallery_FillRect(arg0 + arg2, arg1, arg4, arg3);
}

void Gallery_DrawShadow(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    gSPDisplayList(gDisplayListHead++, gPrefDL_Fill);

    Gfx_FillRectRGBA(arg0 - 4, arg1 - 4, arg2 + 8, arg3 + 8, 0, 0, 0, 0x80);
}

void Gallery_DrawTextureList(u16* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    UNUSED s32 pad;
    s32 temp_v0;
    s32 i;

    if (arg6 != 0) {
        DrawRectBorder(arg1, arg2, arg3, arg4, 4);
    }

    gSPDisplayList(gDisplayListHead++, gPrefDL_Border);
    gDPSetRenderMode(gDisplayListHead++, G_RM_OPA_SURF, G_RM_OPA_SURF2);

    for (i = 0; i < arg4; i += arg5) {
        temp_v0 = CLAMP_MIN(arg4 - i, arg5);

        gDPLoadTextureTile(gDisplayListHead++, &arg0[i * arg3], G_IM_FMT_RGBA, G_IM_SIZ_16b, arg3, 0, 0, 0, arg3 - 1,
                           temp_v0 - 1, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK,
                           G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

        Gfx_DrawTextureRect(arg1, arg2 + i, arg3, temp_v0, 0, 0, 0x400, 0x400, 0);
    }
}

void Gallery_DrawAnimatedCorners(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    static s16 D_83402E38 = 0;

    s16 sp4E = SINS(D_83402E38) * 2;
    UNUSED s32 pad[4];

    gDPPipeSync(gDisplayListHead++);
    gDPSetEnvColor(gDisplayListHead++, 240, 212, 104, 255);

    Gfx_DrawSpriteIA8(sp4E + arg0, sp4E + arg1, 0x10, 0x10, D_300C540, 0x10, 0);
    Gfx_DrawSpriteIA8(sp4E + arg0, ((arg1 + arg3) - sp4E) - 0x10, 0x10, 0x10, D_300C840, 0x10, 0);
    Gfx_DrawSpriteIA8(((arg0 + arg2) - sp4E) - 0x10, sp4E + arg1, 0x10, 0x10, D_300C640, 0x10, 0);
    Gfx_DrawSpriteIA8(((arg0 + arg2) - sp4E) - 0x10, ((arg1 + arg3) - sp4E) - 0x10, 0x10, 0x10, D_300C740, 0x10, 0);
    D_83402E38 += 0x2000;
}

void Gallery_DrawCursor(s32 arg0, s32 arg1, s32 arg2) {
    u8* var_v0;

    if (arg2 != 0) {
        var_v0 = D_300AE38;
    } else {
        var_v0 = D_3009E38;
    }

    Gfx_DrawSpriteRGBA16(arg0, arg1, 0x40, 0x20, var_v0, 0x40, 0);
}

void CamList_Init(unk_D_83407B38* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, AssetManager* arg5,
                   BinArchive* arg6, unk_D_83403C60* arg7, s32 arg8, s32 arg9) {
    UNUSED s32 pad;
    FramebufferImage* sp168;
    FramebufferImage* sp68[64];
    UNUSED s32 pad2;
    s32 i;

    arg0->unk_00 = 0;
    arg0->unk_04 = -1;
    arg0->unk_08 = 0;

    arg0->unk_0C = arg8 / arg3;
    if ((arg8 % arg3) > 0) {
        arg0->unk_0C++;
    }

    arg0->unk_10 = 0;
    arg0->unk_14 = arg3;
    arg0->unk_18 = arg4;
    arg0->unk_1C = arg3 / arg4;

    sp168 = FramebufferImage_Allocate(G_IM_FMT_RGBA, IMAGE_SIZE_BITS_16b, arg1, arg2, 1);

    for (i = 0; i < arg3; i++) {
        sp68[i] = FramebufferImage_Allocate(G_IM_FMT_RGBA, IMAGE_SIZE_BITS_16b, arg1, arg2, 0);
    }

    if (arg9 != 0) {
        Cam_CallInit318B8();
    }

    for (i = 0; i < 36; i++) {
        if (i < arg8) {
            arg0->unk_20[i] = Cam_Create(arg1, arg2, sp68[i % arg3], sp168, arg5, arg6, &arg7[i]);
        } else {
            arg0->unk_20[i] = 0;
        }
    }

    arg0->unk_B0 = Cam_Create(arg1, arg2, 0, sp168, arg5, arg6, NULL);
}

void CamList_Update(unk_D_83407B38* arg0) {
    s32 temp_v0 = Cam_FindActiveIndex(arg0->unk_20, 0x25);
    Camera* var_s0;
    s32 i;

    if (temp_v0 == -1) {
        for (i = 0; i < arg0->unk_14 + 1; i++) {
            if (i < arg0->unk_14) {
                var_s0 = arg0->unk_20[arg0->unk_08 * arg0->unk_14 + i];
            } else if (arg0->unk_04 != -1) {
                var_s0 = arg0->unk_B0;
            } else {
                var_s0 = NULL;
            }

            if ((Cam_IsMonIndexDisplayable(var_s0) != 0) && (var_s0->unk_00 == 0)) {
                main_pool_push_state('albu');
                Cam_Update(var_s0);
                break;
            }
        }
    } else {
        Cam_Update(arg0->unk_20[temp_v0]);
    }
}

void Gallery_ClearActiveCamera(void) {
    Camera* temp_v0 = Cam_GetCurrent();

    if ((temp_v0 != NULL) && (temp_v0->unk_00 == 2)) {
        main_pool_pop_state('albu');
        Cam_ClearActive2();
    }
}

s32 Gallery_CountDisplayableInPage(unk_D_83407B38* arg0, s32 arg1) {
    s32 i;
    s32 idx;
    s32 var_s2 = 0;

    if ((arg1 >= 0) && (arg1 < arg0->unk_0C)) {
        for (i = 0; i < arg0->unk_14; i++) {
            idx = (arg0->unk_14 * arg1) + i;
            if (Cam_IsMonIndexDisplayable(arg0->unk_20[idx]) != 0) {
                var_s2++;
            }
        }
    }
    return var_s2;
}

void Selection_Reset(unk_D_83407B00* arg0) {
    arg0->unk_00 = -1;
    arg0->unk_04 = -1;
}

void Gallery_SyncSelectionToCam(unk_D_83407B38* arg0, unk_D_83407B00* arg1) {
    arg1->unk_00 = arg0->unk_00;
    arg1->unk_04 = arg0->unk_08;
}

void Gallery_SyncCamToSelection(unk_D_83407B38* arg0, unk_D_83407B00* arg1) {
    if (arg1->unk_00 != -1) {
        arg0->unk_00 = arg1->unk_00;
        arg0->unk_08 = arg1->unk_04;
    }
}

void Gallery_GetPageAndIndex(unk_D_83407B38* arg0, s32* arg1, s32* arg2, s32 arg3) {
    *arg1 = arg3 % arg0->unk_18;
    *arg2 = arg3 / arg0->unk_18;
}

s32 Gallery_GetGlobalIndex(unk_D_83407B38* arg0, s32 arg1, s32 arg2) {
    return (arg0->unk_18 * arg2) + arg1;
}

void Gallery_UpdateCameraAssets(unk_D_83407B38* arg0, AssetManager* arg1, BinArchive* arg2) {
    s32 i;

    for (i = 0; i < 37; i++) {
        if (arg0->unk_20[i] != NULL) {
            arg0->unk_20[i]->unk_10 = arg1;
            arg0->unk_20[i]->unk_14 = arg2;
        }
    }
}
