#include "fragment62.h"
#include "src/11BA0.h"
#include "src/12D80.h"
#include "src/19840.h"
#include "src/1C720.h"
#include "src/1CF30.h"
#include "src/20330.h"
#include "src/32D10.h"
#include "src/3D140.h"
#include "src/3FB0.h"
#include "src/4BDC0.h"
#include "src/6A40.h"
#include "src/F420.h"
#include "src/controller.h"
#include "src/geo_layout.h"
#include "src/memmap.h"
#include "src/memory.h"

static CameraStruct gBattleMainCamera;
static unk_D_8690A610 gBattleColorRect;
static GraphNode gBattleGraphNode0;
static GraphNode gBattleGraphNode1;
static GraphNode gBattleGraphNode2;
static CameraStruct gBattlePortraitCamera0;
static CameraStruct gBattlePortraitCamera1;
u8* gPokemonPortraitImage0;
u8* gPokemonPortraitImage1;
static void* gBattleBgTexture;
static GraphNode* gBattleMainGraph;
static GraphNode* gBattlePortraitGraph0;
static GraphNode* gBattlePortraitGraph1;
static FramebufferImage* gBattlePortraitFb0;
static FramebufferImage* gBattlePortraitFb1;
static unk_D_800AE540_1194* gBattlePokemonData;
static s32 gBattleSceneState;
static s32 gPokemonSelectionIndex;
static Color_RGBA8_u32 gBattleGlobalColor;
static f32 gBattleGlobalScale;
static s32 gBattleCompletionTimer;

static u8 D_84384350[] = {
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x11, 0x01,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01,
};
static u32 D_84384364[] = {
    0x0C00FFFF,  0x05000000,  0x07000000,    &gBattleMainCamera,   0x05000000, 0x0D000000,    0x05000000,  0x07000000,
    &gBattleColorRect, 0x14000000,  0x002D0019,    0xFFFFFF28,    0x08000000, CameraNode_GetPanTiltPositive, 0x00000000,  0x14000000,
    0x002D0019,  0x80808028,  0x08000000,    CameraNode_GetPanTiltNegative, 0x00000000, 0x16646464,    0x0F000002,  0x05000000,
    0x1F00FFFF,  0x00000000,  0x00000000,    0x00000000,    0x00640064, 0x00640000,    0x08000000,  FragmentNode_SetScaleAndColor,
    0x00000000,  0x05000000,  0x07000000,    &gBattleGraphNode0,   0x06000000, 0x06000000,    0x0F000003,  0x05000000,
    0x1F00FFFF,  0x00000000,  0x00000000,    0x00000000,    0x00640064, 0x00640000,    0x08000000,  FragmentNode_SetScaleAndColor,
    0x00000000,  0x05000000,  0x07000000,    &gBattleGraphNode1,   0x06000000, 0x06000000,    0x0F000002,  0x05000000,
    0x1F00FFFF,  0x00000000,  0x00000000,    0x00000000,    0x00640064, 0x00640000,    0x08000000,  FragmentNode_SetScaleAndColor,
    0x00000000,  0x05000000,  0x07000000,    &gBattleGraphNode2,   0x06000000, 0x06000000,    0x0F000003,  0x05000000,
    0x0A000000,  &gGraphRoot0, 0x06000000,    0x0F000002,    0x05000000, 0x0A000000,    &gGraphRoot1, 0x06000000,
    0x09000000,  0x08000000,  CameraNode_UpdateCallback, 0x00000000,    0x06000000, 0x06000000,    0x06000000,  0x01000000,
};
static u32 D_843844C4[] = {
    0x0C00FFFF,  0x05000000, 0x07000000, &gBattlePortraitCamera0, 0x05000000, 0x0D000001, 0x05000000,
    0x14000000,  0x002D0019, 0xFFFFFF28, 0x16FFFFFF,  0x0F000003, 0x05000000, 0x0A000000,
    &gGraphRoot0, 0x06000000, 0x06000000, 0x06000000,  0x06000000, 0x01000000,
};
static u32 D_84384514[] = {
    0x0C00FFFF,  0x05000000, 0x07000000, &gBattlePortraitCamera1, 0x05000000, 0x0D000002, 0x05000000,
    0x14000000,  0x002D0019, 0xFFFFFF28, 0x16FFFFFF,  0x0F000003, 0x05000000, 0x0A000000,
    &gGraphRoot0, 0x06000000, 0x06000000, 0x06000000,  0x06000000, 0x01000000,
};

s32 CameraNode_UpdateCallback(s32 arg0, GraphNode* arg1) {
    if (arg0 == 2) {
        HandleCameraMode(5, &gBattleMainCamera);
    }
    return 0;
}

s32 CameraNode_GetPanTiltPositive(s32 arg0, unk_D_86002F34_alt18* arg1) {
    UNUSED s32 pad;
    f32 sp28;
    s16 sp26;
    s16 sp24;

    if (arg0 == 2) {
        Matrix_Decompose(&gCurrentCameraNode->unk_60.at, &gCurrentCameraNode->unk_60.eye, &sp28, &sp26, &sp24);
        arg1->unk_1C = sp26 + 0x2000;
        arg1->unk_1E = sp24 - 0x2000;
    }
    return 0;
}

s32 CameraNode_GetPanTiltNegative(s32 arg0, unk_D_86002F34_alt18* arg1) {
    UNUSED s32 pad;
    f32 sp28;
    s16 sp26;
    s16 sp24;

    if (arg0 == 2) {
        Matrix_Decompose(&gCurrentCameraNode->unk_60.at, &gCurrentCameraNode->unk_60.eye, &sp28, &sp26, &sp24);
        arg1->unk_1C = -0x2000 - sp26;
        arg1->unk_1E = sp24 + 0x6000;
    }
    return 0;
}

s32 FragmentNode_SetScaleAndColor(s32 arg0, Fragment2_1GraphNode* arg1) {
    if (arg0 == 2) {
        Vec3f_Set(&arg1->unk_030, gBattleGlobalScale, gBattleGlobalScale, gBattleGlobalScale);
        arg1->unk_03C.rgba = gBattleGlobalColor.rgba;
    }
    return 0;
}

void ColorRectNode_SetColor(u8 arg0, u8 arg1, u8 arg2) {
    gBattleGlobalColor.r = arg0;
    gBattleGlobalColor.g = arg1;
    gBattleGlobalColor.b = arg2;

    if (((arg0 & arg1 & arg2) & 0xFF) == 0xFF) {
        if (gBattleColorRect.unk_00.unk_14 == 1) {
            gBattleColorRect.unk_00.unk_01 |= 1;
        }
    } else {
        gBattleColorRect.unk_00.unk_01 &= ~1;
    }
}

void FragmentNode_SetGlobalScale(f32 arg0) {
    gBattleGlobalScale = arg0;
}

u16 Color_ModulateWithGlobal(u16 arg0) {
    s32 r;
    s32 g;
    s32 b;

    r = ((((((arg0 >> 11) & 0x1F) << 3) + (((arg0 >> 11) & 0x1F) >> 2)) * gBattleGlobalColor.r) / 255) >> 3;
    g = ((((((arg0 >> 6) & 0x1F) << 3) + (((arg0 >> 6) & 0x1F) >> 2)) * gBattleGlobalColor.g) / 255) >> 3;
    b = ((((((arg0 >> 1) & 0x1F) << 3) + (((arg0 >> 1) & 0x1F) >> 2)) * gBattleGlobalColor.b) / 255) >> 3;

    return (r << 11) | (g << 6) | (b << 1) | 1;
}

void RenderBackgroundScreen(void) {
    s16 sp4E;
    s16 sp4C;
    s16 sp4A;
    s16 sp48;
    s16 sp46;
    s16 sp44;

    if ((u32)gBattleBgTexture == NULL) {
        Gfx_FillDepthRectangle(&gDisplayListHead, 0, 0, 0x140, 0xF0);
        return;
    }

    if ((u32)gBattleBgTexture == -1) {
        Gfx_FillScreen(&gDisplayListHead, 1);
        return;
    }

    if ((u32)gBattleBgTexture < 0x10000) {
        Gfx_FillScreen(&gDisplayListHead, Color_ModulateWithGlobal(gBattleBgTexture));
        return;
    }

    sp4E = gBattleMainCamera.unk_18.x;
    sp4A = gBattleMainCamera.unk_18.y;
    sp4C = gBattleMainCamera.unk_18.width + sp4E;
    sp48 = (gBattleMainCamera.unk_18.height / 2) + sp4A;
    sp46 = gBattleMainCamera.unk_18.height + sp4A;
    sp44 = 0x10000 / (gBattleMainCamera.unk_18.height / 2);

    if ((gBattleMainCamera.unk_18.width < 0x140) || (gBattleMainCamera.unk_18.height < 0xF0)) {
        Gfx_FillScreen(&gDisplayListHead, 1);
    } else {
        Gfx_FillDepthRectangle(&gDisplayListHead, 0, 0, 0x140, 0xF0);
    }

    gDPSetCycleType(gDisplayListHead++, G_CYC_1CYCLE);
    gDPSetTexturePersp(gDisplayListHead++, G_TP_NONE);
    gDPSetCombineMode(gDisplayListHead++, G_CC_MODULATEI_PRIM, G_CC_MODULATEI_PRIM);
    gDPSetPrimColor(gDisplayListHead++, 0, 0, gBattleGlobalColor.r, gBattleGlobalColor.g, gBattleGlobalColor.b, 255);
    gSPClearGeometryMode(gDisplayListHead++, G_ZBUFFER | G_LIGHTING);

    gDPLoadTextureBlock(gDisplayListHead++, Memmap_GetFragmentVaddr(gBattleBgTexture), G_IM_FMT_RGBA, G_IM_SIZ_32b, 4, 64, 0,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                        G_TX_NOLOD);
    gSPTextureRectangle(gDisplayListHead++, sp4E << 2, sp4A << 2, sp4C << 2, sp48 << 2, G_TX_RENDERTILE, 0, 0, 0, sp44);
    gSPTextureRectangle(gDisplayListHead++, sp4E << 2, sp48 << 2, sp4C << 2, sp46 << 2, G_TX_RENDERTILE, 0, 0x07E0, 0,
                        0);
    gSPDisplayList(gDisplayListHead++, gPrefDL_End);
}

void FramebufferNode_Init(GraphNode* arg0, FramebufferImage* arg1) {
    CameraStruct* sp2C = arg0->unk_0C;
    unk_D_86002F34_00C_018 sp20;

    if (sp2C->unk_00.unk_01 & 0x10) {
        sp20 = sp2C->unk_18;

        sp2C->unk_18.x = 0;
        sp2C->unk_18.y = 0;
        sp2C->unk_18.width = 0x4C;
        sp2C->unk_18.height = 0x4C;

        Gfx_SetupFrameBuffer(&gDisplayListHead, arg1);
        Gfx_FillScreen(&gDisplayListHead, 0x10D);
        Graph_SetTextureState(arg0);

        sp2C->unk_00.unk_01 &= ~0x10;

        sp2C->unk_18 = sp20;
    }
}

void Gfx_DrawClippedTextureRect(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    ClipRect sp38;
    u16 tmp5;
    u16 tmp6;

    Gfx_MakeClipRect(&sp38, arg0, arg1, arg2, arg3);

    if (Gfx_IntersectClip(&sp38) != 0) {
        if (!arg2) {}

        tmp5 = ((sp38.x1 - arg0) << 5);
        tmp6 = ((sp38.y2 - arg1) << 5);

        tmp5 += 0x10;
        tmp6 += 0x10;

        gSPTextureRectangle(gDisplayListHead++, sp38.x1 << 2, sp38.y2 << 2, ((sp38.y1 + 1) ^ 0) << 2,
                            ((sp38.x2 + 1) ^ 0) << 2, G_TX_RENDERTILE, tmp5, tmp6, 0x0800, 0x0800);

        if ((arg2 && arg2) ^ 0) {}
    }
}

void Gfx_LoadTextureDrawClippedRect(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u8* arg4, s32 arg5) {
    gDPLoadTextureBlock(gDisplayListHead++, arg4, G_IM_FMT_RGBA, G_IM_SIZ_16b, arg5, (arg3 * 2) + 2, 0,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                        G_TX_NOLOD);

    Gfx_DrawClippedTextureRect(arg0, arg1, (arg0 + arg2) - 1, (arg1 + arg3) - 1);
}

void RenderPokemonPortraits(GraphNode* arg0, FramebufferImage* arg1) {
    s32 temp_s2;
    s32 temp_s3;
    CameraStruct* temp_v1 = arg0->unk_0C;
    unk_D_86002F34_00C_018* ptr = &arg0->unk_0C->unk_18;
    s32 img;

    temp_s2 = ptr->x;
    temp_s3 = ptr->y;

    temp_v1++;

    gDPPipeSync(gDisplayListHead++);

    gDPSetCycleType(gDisplayListHead++, G_CYC_1CYCLE);
    gDPSetRenderMode(gDisplayListHead++, G_RM_OPA_SURF, G_RM_OPA_SURF2);
    gDPSetCombineMode(gDisplayListHead++, G_CC_DECALRGBA, G_CC_DECALRGBA);
    gDPSetTexturePersp(gDisplayListHead++, G_TP_NONE);
    gDPSetTextureFilter(gDisplayListHead++, G_TF_AVERAGE);

    img = arg1->img_p;
    Gfx_LoadTextureDrawClippedRect(temp_s2, temp_s3, 0x25, 0xA, img, 0x4C);
    img = arg1->img_p + 0xBE0;
    Gfx_LoadTextureDrawClippedRect(temp_s2, temp_s3 + 0xA, 0x25, 0xA, img, 0x4C);
    img = arg1->img_p + 0x17C0;
    Gfx_LoadTextureDrawClippedRect(temp_s2, temp_s3 + 0x14, 0x25, 0xA, img, 0x4C);
    img = arg1->img_p + 0x23A0;
    Gfx_LoadTextureDrawClippedRect(temp_s2, temp_s3 + 0x1E, 0x25, 7, img, 0x4C);

    gDPPipeSync(gDisplayListHead++);

    gDPSetTexturePersp(gDisplayListHead++, G_TP_PERSP);
    gDPSetTextureFilter(gDisplayListHead++, G_TF_BILERP);
}

void PokemonSelection_ClearFlags(void) {
    s32 i;
    s32 j;
    s32 x;
    unk_D_800AE540_0004* temp_a2;
    unk_D_800AE540_1194* ptr = &gBattlePokemonData[0];

    for (i = 0; i < 2; i++, ptr++) {
        for (j = 0; j < ptr->unk_01; j++) {
            temp_a2 = ptr->unk_08[j];
            for (x = 0; x < temp_a2->unk_002; x++) {
                temp_a2->unk_01C[x].unk_25 = 0;
            }
        }
    }
}

void PokemonSelection_AssignIndices(void) {
    s32 i;
    s32 j;
    s32 x;
    s32 var_v0 = 0;
    unk_D_800AE540_0004* temp_a3;
    unk_D_800AE540_1194* ptr = &gBattlePokemonData[0];

    for (i = 0; i < 2; i++, ptr++) {
        for (j = 0; j < ptr->unk_01; j++) {
            temp_a3 = ptr->unk_08[j];
            for (x = 0; x < temp_a3->unk_002; x++) {
                if ((temp_a3->unk_01C[x].unk_25 == 0) && (temp_a3->unk_01C[x].unk_02 == 0)) {
                    var_v0 = 1;
                    temp_a3->unk_01C[x].unk_25 = gPokemonSelectionIndex;
                }
            }
        }
    }

    if (var_v0 != 0) {
        gPokemonSelectionIndex += 1;
    }
}

void func_84300E78(void) {
}

void func_84300E80(void) {
}

s32 BattleScene_UpdateFrame(s32 arg0) {
    s32 sp1C;

    Gfx_FinishFrame();
    AnimationFrame_StallCheck();
    BattleInitDispatch(2, gBattlePokemonData);
    HandleBattlePhase(2, &gBattlePortraitCamera0, &gBattlePortraitCamera1);
    sp1C = BattleScene_Dispatch(2, &gBattleMainCamera);
    HandleCameraMode(2, &gBattleMainCamera);
    FramebufferNode_Init(gBattlePortraitGraph0, gBattlePortraitFb0);
    FramebufferNode_Init(gBattlePortraitGraph1, gBattlePortraitFb1);
    Stage_BeginDisplayList();
    RenderBackgroundScreen();
    Graph_SetTextureState(gBattleMainGraph);
    BattleInitDispatch(5, gBattlePokemonData);
    RenderPokemonPortraits(gBattlePortraitGraph0, gBattlePortraitFb0);
    RenderPokemonPortraits(gBattlePortraitGraph1, gBattlePortraitFb1);
    PokemonSelection_AssignIndices();

    if (sp1C == 1) {
        gBattlePokemonData[0].unk_1C = 1;
    }

    if (sp1C == 2) {
        gBattlePokemonData[1].unk_1C = 1;
    }

    return sp1C;
}

s32 BattleScene_UpdatePausedFrame(s32 arg0) {
    s32 sp1C = 0;

    if ((arg0 == 0) && BTN_IS_PRESSED(gPlayer1Controller, BTN_A)) {
        sp1C = BattleScene_UpdateFrame(arg0);
    } else {
        AnimationFrame_StallCheck();
        Stage_BeginDisplayList();
        RenderBackgroundScreen();
        Graph_SetTextureState(gBattleMainGraph);
        BattleInitDispatch(5, gBattlePokemonData);
        RenderPokemonPortraits(gBattlePortraitGraph0, gBattlePortraitFb0);
        RenderPokemonPortraits(gBattlePortraitGraph1, gBattlePortraitFb1);
    }

    if ((arg0 == 0) && BTN_IS_PRESSED(gPlayer1Controller, BTN_START)) {
        gBattleSceneState = 0;
    }
    return sp1C;
}

void Battle_UpdateCompletionGate(void) {
    if (gBattleCompletionTimer < 0) {
        gBattleCompletionTimer++;
    } else if ((gBattleCompletionTimer == 0) && (gBattleContext.unk_0000 == 0x10) && gPlayer1Controller->buttonPressed) {
        gBattleCompletionTimer = 1;
    }
}

s32 PokemonSelectScreen_Update(s32 arg0) {
    s32 sp1C = 0;

    Cont_StartReadInputs();
    ProcessPokemonSelection(&gBattlePokemonData[0]);
    UpdatePokemonStateOnExit(&gBattlePokemonData[0]);
    ProcessPokemonSelection(&gBattlePokemonData[1]);
    UpdatePokemonStateOnExit(&gBattlePokemonData[1]);
    Cont_ReadInputs();
    MenuInput_Init();

    switch (gBattleSceneState) {
        case 0:
            sp1C = BattleScene_UpdateFrame(arg0);
            break;

        case 1:
            sp1C = BattleScene_UpdatePausedFrame(arg0);
            break;
    }

    if ((sp1C != 0) && (gBattleCompletionTimer <= 0)) {
        gBattleCompletionTimer = 1;
    }

    Battle_UpdateCompletionGate();
    StartPokemonAnimation(&gBattlePokemonData[0]);
    StartPokemonAnimation(&gBattlePokemonData[1]);

    if ((arg0 != 2) && (gBattleCompletionTimer == 1)) {
        gBattleCompletionTimer = 2;
        AudioFrameUpdate(0);
        if (gBattleContext.unk_0000 != 0x11) {
            Stage_SetFadeColor(0x1E);
        }
        return 1;
    }
    return 0;
}

void Battle_CompleteRosterOrder(u8* arg0, s32 arg1) {
    s32 i;
    s32 j;

    for (i = 0; i < 6; i++) {
        for (j = 0; j < arg1; j++) {
            if (i == arg0[j]) {
                break;
            }
        }

        if (j == arg1) {
            arg0[arg1++] = i;
        }
    }
}

void Battle_SelectComRoster(void) {
    unk_D_800AE540_0004* temp_s0;
    unk_D_800AE540_0004* temp_s1;
    u8 sp48[8];
    unk_D_800AE540_0004* temp_s2;
    s32 i;
    s32 var_s1;

    temp_s1 = gBattleContext.unk_1194[0].unk_08[0];
    temp_s2 = gBattleContext.unk_1194[0].unk_08[1];
    temp_s0 = gBattleContext.unk_1194[1].unk_08[0];

    if (temp_s0->unk_000 & 2) {
        if (gBattleContext.unk_0000 == 0) {
            if (gBattleContext.unk_0001 == 0) {
                var_s1 = temp_s0->unk_214->unk_002;
            } else {
                var_s1 = 3;
            }
            func_843831A0(temp_s1, temp_s2, temp_s0, gBattleContext.unk_11EC, sp48, gBattleContext.unk_0001, var_s1);
        } else {
            if (gBattleContext.unk_0001 == 8) {
                var_s1 = temp_s0->unk_214->unk_002;
            } else {
                var_s1 = 3;
            }
            func_843831A0(temp_s1, NULL, temp_s0, temp_s0->unk_018 & 0xFF, sp48, gBattleContext.unk_0001, var_s1);
        }
        Battle_CompleteRosterOrder(sp48, var_s1);
        temp_s0->unk_002 = var_s1;

        for (i = 0; i < temp_s0->unk_214->unk_002; i++) {
            temp_s0->unk_01C[i] = temp_s0->unk_214->unk_028[sp48[i]];
        }
    }
}

void PokemonSelection_InitPlayer(unk_D_800AE540_1194* arg0, unk_D_86002F30* arg1) {
    unk_D_800AE540_0004* temp_v0 = arg0->unk_08[0];

    arg0->unk_18 = arg1->unk_08->unk_00[0];
    arg0->unk_00 |= 0xA0;
    arg0->unk_1C = 0;
    arg0->unk_02 = temp_v0->unk_01C[0].unk_00.unk_00;
    arg0->unk_04 = temp_v0->unk_01C;
    ProcessPokemonSelection(arg0);
}

void BattleScreen_Init(Stage* arg0) {
    MemoryBlock* sp44;
    u32* temp_v0_4;
    FragmentEntry sp3C;
    unk_D_8690A610_018* temp_v0_7;
    s32 pad;
    s16 sp32;
    FramebufferImage* sp2C;
    unk_D_86002F30* sp28;

    ColorRectNode_SetColor(0xFF, 0xFF, 0xFF);
    FragmentNode_SetGlobalScale(1.0f);

    if (gBattleContext.unk_0000 == 0x11) {
        Text_Init(4, 0);
    } else if (gBattleContext.unk_0000 == 0x10) {
        Text_Init(7, 0);
    } else {
        Text_Init(3, 0);
    }

    gBattlePokemonData[0].unk_10 = AssetManager_Create(3);
    gBattlePokemonData[1].unk_10 = AssetManager_Create(3);
    AssetManager_LoadArchives();

    sp2C = main_pool_alloc(0x10, 0);
    FramebufferImage_Init(sp2C, 0, 2, 0x4C, 0x4C, arg0->unk_18[0]->depth_p->img_p);
    gBattlePortraitFb0 = FramebufferImage_Allocate(0, 2, 0x4C, 0x4C, 0);
    gBattlePortraitFb1 = FramebufferImage_Allocate(0, 2, 0x4C, 0x4C, 0);

    FramebufferImage_AttachDepth(gBattlePortraitFb0, sp2C);
    FramebufferImage_AttachDepth(gBattlePortraitFb1, sp2C);

    gPokemonPortraitImage0 = gBattlePortraitFb0->img_p;
    gPokemonPortraitImage1 = gBattlePortraitFb1->img_p;

    FRAGMENT_LOAD(fragment31);
    ASSET_LOAD(D_1000000, common_menu1_ui, 0);
    ASSET_LOAD(D_3000000, battle_ui, 0);

    if ((gBattleContext.unk_0000 == 0x10) || (gBattleContext.unk_0000 == 0xA)) {
        sp32 = D_84384350[gBattleContext.unk_0001];
        if (gBattleContext.unk_0001 == 7) {
            sp32 += gBattleContext.unk_0002;
        }
    } else {
        sp32 = D_84384350[gBattleContext.unk_0000];
        if (gBattleContext.unk_0000 == 7) {
            sp32 += gBattleContext.unk_0002;
        }
    }

    sp3C = BinArchive_GetFile(ASSET_LOAD2(stadium_models, 1, 1), sp32);
    gBattleBgTexture = sp3C(2, 0);

    sp28 = GeoLayout_LoadById(0x9A);
    Battle_SelectComRoster();
    PokemonSelection_InitPlayer(&gBattlePokemonData[0], sp28);
    PokemonSelection_InitPlayer(&gBattlePokemonData[1], sp28);

    PokemonSelection_ClearFlags();
    CameraNode_Create(NULL, &gBattleMainCamera, 0, 0, 0x140, 0xF0);
    CameraNode_Create(NULL, &gBattlePortraitCamera0, 0x1E, 0x50, 0x4C, 0x4C);
    CameraNode_Create(NULL, &gBattlePortraitCamera1, 0xE2, 0x50, 0x4C, 0x4C);
    ColorRectNode_Create(0, &gBattleColorRect, 0x3C0, 0x3E8, 0xFF, 0xFF, 0xFF, 0xFF);
    GraphNode_AllocInit(NULL, &gBattleGraphNode0);
    GraphNode_AllocInit(NULL, &gBattleGraphNode1);
    GraphNode_AllocInit(NULL, &gBattleGraphNode2);
    Perspective_SetParams(&gBattleMainCamera, 30.0f, 192.0f, 24576.0f);
    Graph_InitRoots();
    BattleInitDispatch(0, gBattlePokemonData);
    HandleBattlePhase(0, &gBattlePortraitCamera0, &gBattlePortraitCamera1);
    BattleScene_Dispatch(0, &gBattleMainCamera);
    HandleCameraMode(0, &gBattleMainCamera);

    sp44 = state_pool_try_init(main_pool_get_available(), 0);
    gBattleMainGraph = process_geo_layout(sp44, D_84384364);
    gBattlePortraitGraph0 = process_geo_layout(sp44, D_843844C4);
    gBattlePortraitGraph1 = process_geo_layout(sp44, D_84384514);

    temp_v0_4 = sp3C(0, 0);
    if (temp_v0_4 != NULL) {
        GraphNode_AddChild(&gBattleGraphNode0, process_geo_layout(sp44, temp_v0_4));
    }

    temp_v0_4 = sp3C(1, 0);
    if (temp_v0_4 != NULL) {
        GraphNode_AddChild(&gBattleGraphNode1, process_geo_layout(sp44, temp_v0_4));
    }

    temp_v0_4 = sp3C(3, 0);
    if (temp_v0_4 != NULL) {
        GraphNode_AddChild(&gBattleGraphNode2, process_geo_layout(sp44, temp_v0_4));
    }

    mem_pool_resize_block(sp44);

    temp_v0_7 = sp3C(4, 0);
    if (temp_v0_7 == NULL) {
        gBattleColorRect.unk_00.unk_14 = 0;
        gBattleColorRect.unk_00.unk_01 &= ~1;
    } else {
        gBattleColorRect.unk_18.unk_00 = temp_v0_7->unk_00;
        gBattleColorRect.unk_18.unk_02 = temp_v0_7->unk_02;
        gBattleColorRect.unk_18.unk_04.rgba = temp_v0_7->unk_04.rgba;
        gBattleColorRect.unk_00.unk_14 = 1;
    }

    BattleInitDispatch(3, gBattlePokemonData);
    HandleBattlePhase(3, &gBattlePortraitCamera0, &gBattlePortraitCamera1);
    BattleScene_Dispatch(3, &gBattleMainCamera);
    HandleCameraMode(3, &gBattleMainCamera);

    gPokemonSelectionIndex = 1;
    gBattleSceneState = 0;
}

void func_84301A24(void) {
}

s32 BattleScreen_Run(s32 arg0, unk_D_800AE540* arg1) {
    Stage* sp24;

    gBattlePokemonData = gBattleContext.unk_1194;
    gBattleCompletionTimer = -2;

    main_pool_push_state('BATL');

    Gfx_InitBuffers(0x20000, 0);
    sp24 = Stage_Create(0, 1, 3, 1, 2, 1);
    BattleScreen_Init(sp24);
    Stage_Set(sp24);
    Stage_AdvanceN(1);
    Stage_RunFadeSequence(PokemonSelectScreen_Update, 0x20, 0x10);
    Stage_AdvanceN(2);
    Stage_Destroy();
    Gfx_FreeBuffers();

    main_pool_pop_state('BATL');

    return 0;
}
