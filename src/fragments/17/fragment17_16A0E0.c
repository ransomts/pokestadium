#include "fragment17.h"
#include "src/12D80.h"
#include "src/17300.h"
#include "src/geo_layout.h"
#include "src/19840.h"
#include "src/1C720.h"
#include "src/1CF30.h"
#include "src/20330.h"
#include "src/2E110.h"
#include "src/3FB0.h"
#include "src/4BDC0.h"
#include "src/6A40.h"
#include "src/6BC0.h"
#include "src/F420.h"
#include "src/controller.h"
#include "src/memory.h"
#include "src/stage_loader.h"

typedef struct unk_D_86B10BD0 {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
} unk_D_86B10BD0; // size >= 0xC

typedef struct unk_D_86B10BE0 {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ s32 unk_10;
} unk_D_86B10BE0; // size >= 0x14

static u32 D_86B0E2B0[] = {
    0xA4AAA4E1, 0xA4C7A4C8, 0xA4A6A1AA, 0x20A5C9A1, 0xBCA5C9A1, 0xBCA4CE0A, 0xA5B2A1BC, 0xA5E0A5DC, 0xA1BCA5A4,
    0xA4F2A5B2, 0xA5C3A5C8, 0xA4C0A1AA, 0x00000000, 0x4742A5D3, 0xA5EBA4CE, 0xA5B2A1BC, 0xA5E0A5DC, 0xA1BCA5A4,
    0xA4AC0A20, 0x20A5B9A5, 0xD4A1BCA5, 0xC9A5A2A5, 0xC3A5D7A1, 0xAA000000, 0xA4B9A4B4, 0xA4A4A4BE, 0xA1AA20A5,
    0xC9A1BCA5, 0xC9A5EAA5, 0xAAA4CE0A, 0xA5B2A1BC, 0xA5E0A5DC, 0xA1BCA5A4, 0xA4F2A5B2, 0xA5C3A5C8, 0xA4C0A1AA,
    0x00000000, 0x4742A5D3, 0xA5EBA4CE, 0xA5B2A1BC, 0xA5E0A5DC, 0xA1BCA5A4, 0xA4AC0AA4, 0xB5A4E9A4, 0xCBA5B9A5,
    0xD4A1BCA5, 0xC9A5A2A5, 0xC3A5D7A4, 0xC0A1AA00,
};

static u32 D_86B0E374[] = {
    0x0C00FFFF, 0x05000000, 0x0B00001E,  0x00000000, 0x014000F0, 0x00000000, 0x00000000, 0x00000118,
    0x05000000, 0x0D000000, 0x05000000,  0x14000000, 0x002B0012, 0xFFFFFF32, 0x16FFFFFF, 0x0F000003,
    0x05000000, 0x0A000000, &gGraphRoot0, 0x06000000, 0x06000000, 0x06000000, 0x06000000, 0x01000000,
};

static char** D_86B10840;
static unk_D_86002F30* D_86B10844;
static GraphNode* D_86B10848;
static Fragment2_1GraphNode D_86B10850;
static CameraStruct* D_86B109B8;
static BinArchive* D_86B109BC;
static u8* D_86B109C0;
static s8 D_86B109C8[0x100];
static s8 D_86B10AC8[0x100];
static s16 D_86B10BC8;
static s16 D_86B10BCA;
static s16 D_86B10BCC;
static unk_D_86B10BD0 D_86B10BD0;
static unk_D_86B10BE0 gMessageBoxState;

void Camera_SetupView(void) {
    D_86B109B8 = D_86B10848->unk_0C;

    D_86B10BC8 = 0;
    D_86B10BCA = 0;
    D_86B10BCC = 0x78;

    Camera_SetViewParameters(&D_86B109B8->unk_60.at, &D_86B109B8->unk_60.eye, D_86B10BCC, D_86B10BC8, D_86B10BCA);

    D_86B109B8->unk_24.near = 50.0f;
    D_86B109B8->unk_24.far = 6400.0f;
}

void MessageState_Reset(void) {
    D_86B10BD0.unk_00 = 0;
    D_86B10BD0.unk_04 = 0;
    D_86B10BD0.unk_08 = 0;
    gMessageBoxState.unk_10 = 0xA;
}

void func_86B0A81C(void) {
}

void func_86B0A824(s16 arg0, s16 arg1, s16 arg2, s16 arg3, u8 arg4, u8 arg5, u8 arg6, u8 arg7) {
    s16 sp48;
    s16 sp44;
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

    sp48 = arg2 - (var_s3 * 2);
    sp44 = arg3 - (var_s2 * 2);

    gSPDisplayList(gDisplayListHead++, gPrefDL_Border);
    gDPSetEnvColor(gDisplayListHead++, arg4, arg5, arg6, arg7);

    gDPLoadTextureBlock_4b(gDisplayListHead++, D_2028A60, G_IM_FMT_I, 16, 8, 0, G_TX_NOMIRROR | G_TX_WRAP,
                           G_TX_NOMIRROR | G_TX_WRAP, 5, 5, G_TX_NOLOD, G_TX_NOLOD);

    Gfx_DrawTextureRect(arg0, arg1, var_s3, var_s2, 0, 0, 0x2000 / var_s3, 0x2000 / var_s2, 0);

    gDPLoadTextureBlock_4b(gDisplayListHead++, D_2028AA0, G_IM_FMT_I, 16, 8, 0, G_TX_NOMIRROR | G_TX_WRAP,
                           G_TX_NOMIRROR | G_TX_WRAP, 5, 5, G_TX_NOLOD, G_TX_NOLOD);

    Gfx_DrawTextureRect((arg0 + arg2) - var_s3, arg1, var_s3, var_s2, 0, 0, 0x2000 / var_s3, 0x2000 / var_s2, 0);

    gDPLoadTextureBlock_4b(gDisplayListHead++, D_20289E0, G_IM_FMT_I, 16, 8, 0, G_TX_NOMIRROR | G_TX_WRAP,
                           G_TX_NOMIRROR | G_TX_WRAP, 5, 5, G_TX_NOLOD, G_TX_NOLOD);

    Gfx_DrawTextureRect(arg0, (arg1 + arg3) - var_s2, var_s3, var_s2, 0, 0, 0x2000 / var_s3, 0x2000 / var_s2, 0);

    gDPLoadTextureBlock_4b(gDisplayListHead++, D_2028A20, G_IM_FMT_I, 16, 8, 0, G_TX_NOMIRROR | G_TX_WRAP,
                           G_TX_NOMIRROR | G_TX_WRAP, 5, 5, G_TX_NOLOD, G_TX_NOLOD);

    Gfx_DrawTextureRect((arg0 + arg2) - var_s3, (arg1 + arg3) - var_s2, var_s3, var_s2, 0, 0, 0x2000 / var_s3,
                  0x2000 / var_s2, 0);

    gSPDisplayList(gDisplayListHead++, gPrefDL_Fill);

    if ((sp48 > 0) && (sp44 > 0)) {
        Gfx_FillRectRGBA(arg0 + var_s3, arg1, sp48, var_s2, arg4, arg5, arg6, arg7);
        Gfx_FillRectRGBA(arg0, arg1 + var_s3, arg2, sp44, arg4, arg5, arg6, arg7);
        Gfx_FillRectRGBA(arg0 + var_s3, (arg1 + var_s3) + sp44, sp48, var_s2, arg4, arg5, arg6, arg7);
    } else if (sp48 > 0) {
        Gfx_FillRectRGBA(arg0 + var_s3, arg1, sp48, arg3, arg4, arg5, arg6, arg7);
    } else if (sp44 > 0) {
        Gfx_FillRectRGBA(arg0, arg1 + var_s2, arg2, sp44, arg4, arg5, arg6, arg7);
    }

    gSPDisplayList(gDisplayListHead++, gPrefDL_End);
}

void MessageState_SetFinished(void) {
    gMessageBoxState.unk_00 = 0xFF;
}

void MessageState_Clear(void) {
    gMessageBoxState.unk_00 = 0;
}

s32 MessageState_CopyNextChars(void) {
    if (D_86B109C8[gMessageBoxState.unk_04] == 0) {
        return 1;
    }

    D_86B10AC8[gMessageBoxState.unk_04++] = D_86B109C8[gMessageBoxState.unk_04];

    if (D_86B109C8[gMessageBoxState.unk_04] == 0) {
        return 1;
    }

    D_86B10AC8[gMessageBoxState.unk_04++] = D_86B109C8[gMessageBoxState.unk_04];
    return 0;
}

void MessageBox_Draw(void) {
    func_86B0A824(0x3C, 0xBE - (gMessageBoxState.unk_10 / 2), gMessageBoxState.unk_0C, gMessageBoxState.unk_10, 0x50, 0x50, 0xF0, 0x80);
}

void MessageBox_RenderText(void) {
    Text_ResetState();
    Text_SetFont(2, 0);
    Text_SetLineHeight(0x10);
    Text_Print(0x56, 0xAF, "%s", D_86B10AC8);
    Text_SetupDL();
}

void MessageBox_Update(void) {
    s32 i;

    switch (gMessageBoxState.unk_00) {
        case 0x0:
            if (gBattleContext.unk_0000 == 0x16) {
                sprintf(D_86B109C8, GetMessageString(NULL, 0, D_86B10840, 0x91));
            } else {
                sprintf(D_86B109C8, GetMessageString(NULL, 0, D_86B10840, 0x93));
            }

            gMessageBoxState.unk_04 = 0;
            gMessageBoxState.unk_08 = 0;
            gMessageBoxState.unk_0C = 0xC8;
            gMessageBoxState.unk_10 = 0xA;

            // clang-format off
            for (i = 0; i < 255; i++) { D_86B10AC8[i] = 0; }
            // clang-format on

            MessageBox_Draw();
            gMessageBoxState.unk_00++;
            break;

        case 0x1:
            gMessageBoxState.unk_10 = Math_ApproachS32(gMessageBoxState.unk_10, 0x28, 8, 8);
            if (gMessageBoxState.unk_10 == 0x28) {
                gMessageBoxState.unk_00++;
            }
            MessageBox_Draw();
            break;

        case 0x2:
            MessageBox_Draw();
            if (MessageState_CopyNextChars() != 0) {
                gMessageBoxState.unk_00++;
            }
            MessageBox_RenderText();
            break;

        case 0x3:
            MessageBox_Draw();
            MessageBox_RenderText();

            if (gMessageBoxState.unk_08++ == 0x3C) {
                if (gBattleContext.unk_0000 == 0x16) {
                    sprintf(D_86B109C8, GetMessageString(NULL, 0, D_86B10840, 0x92));
                } else {
                    sprintf(D_86B109C8, GetMessageString(NULL, 0, D_86B10840, 0x94));
                }

                gMessageBoxState.unk_04 = 0;
                gMessageBoxState.unk_08 = 0;

                // clang-format off
                for (i = 0; i < 255; i++) { D_86B10AC8[i] = 0; }
                // clang-format on

                gMessageBoxState.unk_00++;
            }
            break;

        case 0x4:
            MessageBox_Draw();
            if (MessageState_CopyNextChars() != 0) {
                gMessageBoxState.unk_00++;
            }
            MessageBox_RenderText();
            break;

        case 0x5:
            MessageBox_Draw();
            MessageBox_RenderText();

            if (gMessageBoxState.unk_08++ == 0x41) {
                gMessageBoxState.unk_00 = 0xFF;
            }
            break;

        case 0xFF:
            gMessageBoxState.unk_10 = Math_ApproachS32(gMessageBoxState.unk_10, 0, 8, 8);
            if (gMessageBoxState.unk_10 >= 0xB) {
                MessageBox_Draw();
            }
            break;
    }
}

void func_86B0B498(void) {
    Cont_StartReadInputs();
    Cont_ReadInputs();
    MenuInput_Init();
}

void func_86B0B4C8(void) {
}

void DrawBackgroundTiles(u8* arg0) {
    s32 i;
    s32 j;

    if (1) {}

    gDPPipeSync(gDisplayListHead++);

    gDPSetCycleType(gDisplayListHead++, G_CYC_1CYCLE);
    gDPSetRenderMode(gDisplayListHead++, G_RM_OPA_SURF, G_RM_OPA_SURF2);
    gDPSetTexturePersp(gDisplayListHead++, G_TP_NONE);
    gDPSetCombineMode(gDisplayListHead++, G_CC_DECALRGB, G_CC_DECALRGB);

    gDPPipeSync(gDisplayListHead++);

    for (i = 0; i < 15; i++) {
        for (j = 0; j < 20; j++, arg0 += 0x200) {
            Gfx_DrawSpriteRGBA16(j * 0x10, i * 0x10, 0x10, 0x10, arg0, 0x10, 0);
        }
    }

    gSPDisplayList(gDisplayListHead++, gPrefDL_End);
}

void func_86B0B650(void) {
    Stage_BeginDisplayList();
    DrawBackgroundTiles(D_86B109C0);
    Gfx_FillDepthRectangle(&gDisplayListHead, 0, 0, 0x140, 0xF0);
    Gfx_FinishFrame();
    Graph_SetTextureState(D_86B10848);
    MessageBox_Update();
    Stage_Advance();
}

s32 BattleCutscene_Process(void) {
    s32 sp24 = 0;

    switch (D_86B10BD0.unk_00) {
        case 0:
            D_86B10850.unk_000.unk_02 |= 0x20;
            D_86B10850.unk_000.unk_01 |= 1;
            D_86B10BD0.unk_00++;
            break;

        case 1:
            if ((D_86B10850.unk_040.unk_08 >> 0x10) == 0xA) {
                ResultScreen_SetAnimation(0x38);
            }

            if ((D_86B10850.unk_040.unk_08 >> 0x10) == 0x72) {
                D_86B10BD0.unk_08 = 0;
                D_86B10850.unk_000.unk_02 &= 0xFFDF;
                MessageState_Clear();
                ResultScreen_SetAnimation(0x13);
                D_86B10BD0.unk_00++;
            }
            break;

        case 2:
            if (gMessageBoxState.unk_00 == 0xFF) {
                D_86B10BD0.unk_08 = 0;
                D_86B10850.unk_000.unk_02 |= 0x20;
                MessageState_SetFinished();
                D_86B10BD0.unk_00++;
            }
            break;

        case 3:
            if (GraphNode_IsAnimationFinished(&D_86B10850) != 0) {
                D_86B10BD0.unk_00++;
            }
            break;

        case 4:
            sp24 = 1;
            break;
    }

    return sp24;
}

void func_86B0B810(void) {
    s32 i;
    s32 var_s2 = 1;

    Stage_SetFillColor(1);
    Stage_FadeIn(0xA);

    for (i = 0; i < 10; i++) {
        func_86B0B498();
        func_86B0B650();
    }

    while (var_s2 != 0) {
        func_86B0B498();
        if (BattleCutscene_Process() != 0) {
            var_s2 = 0;
        }
        func_86B0B650();
    }

    Stage_SetFillColor(0xFFFF);
    Stage_FadeOut(8);

    for (i = 0; i < 8; i++) {
        func_86B0B498();
        func_86B0B650();
    }

    Stage_AdvanceN(2);
}

void func_86B0B8DC(void) {
    MemoryBlock* temp_v0 = state_pool_try_init(main_pool_get_available(), 0);

    D_86B10848 = process_geo_layout(temp_v0, &D_86B0E374);
    mem_pool_resize_block(temp_v0);

    Graph_InitRoots();
    Camera_SetupView();
    MessageState_Reset();
    MessageState_SetFinished();
    Graph_AddToRootList0(&D_86B10850);
    AssetManager_LoadArchives();

    if (gBattleContext.unk_0000 == 0x16) {
        D_86B10844 = GeoLayout_LoadById(0xD5);
        GraphNode_InitChild(&D_86B10850, 0, 0xD5, D_86B10844->unk_08->unk_00[0]);
    } else {
        D_86B10844 = GeoLayout_LoadById(0xD4);
        GraphNode_InitChild(&D_86B10850, 0, 0xD4, D_86B10844->unk_08->unk_00[0]);
    }

    GraphNode_TriggerAction(&D_86B10850, 0);

    D_86B10850.unk_000.unk_02 &= ~0x20;
    D_86B10850.unk_000.unk_01 &= ~1;

    Vec3f_Set(&D_86B10850.unk_024, 0.0f, 11.0f, -105.0f);
}

s32 BattleState_Handle22Or23(void) {
    Stage* sp24;

    main_pool_push_state('GBOY');

    Gfx_InitBuffers(0x10000, 0);
    sp24 = Stage_Create(0, 1, 3, 1, 2, 1);
    Text_Init(2, 0);

    ASSET_LOAD(D_1000000, common_menu1_ui, 0);
    ASSET_LOAD(D_2000000, common_menu2_ui, 0);
    FRAGMENT_LOAD(fragment31);

    MessageBank_Init();
    D_86B10840 = GetMessageBank(0x1E);

    if (gBattleContext.unk_0000 == 0x16) {
        D_86B109BC = ASSET_LOAD2(backgrounds, 1, 1);
        D_86B109C0 = BinArchive_GetFile(D_86B109BC, 0x12);
    } else {
        D_86B109BC = ASSET_LOAD2(backgrounds, 1, 1);
        D_86B109C0 = BinArchive_GetFile(D_86B109BC, 0x13);
    }

    func_86B0B8DC();
    Stage_Set(sp24);
    func_86B0B810();
    Stage_Destroy();
    FontManager_Free();
    Gfx_FreeBuffers();

    main_pool_pop_state('GBOY');

    return 0;
}
