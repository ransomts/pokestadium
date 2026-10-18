#include "30640.h"
#include "include/math.h"
#include "src/fragments/15/fragment15.h"
#include "src/fragments/31/fragment31.h"
#include "src/fragments/34/fragment34.h"
#include "src/11BA0.h"
#include "src/12D80.h"
#include "src/17300.h"
#include "src/18140.h"
#include "src/geo_layout.h"
#include "src/19840.h"
#include "src/1C720.h"
#include "src/1CF30.h"
#include "src/29BA0.h"
#include "src/3FB0.h"
#include "src/37370.h"
#include "src/4BDC0.h"
#include "src/F420.h"
#include "src/math_util.h"
#include "src/memory.h"
#include "src/util.h"

typedef struct {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;

    /* 0x08 */ s16 unk_08;
    /* 0x0A */ s16 unk_0A;
    /* 0x0C */ s16 unk_0C;
    /* 0x0E */ s16 unk_0E;
} unk_D_800761B0; /* size = 0x40 */

typedef struct unk_func_8003013C_arg1 {
    /* 0x00 */ u8 pad00[0x1C];
    /* 0x1C */ s16 unk_1C;
    /* 0x1E */ s16 unk_1E;
} unk_func_8003013C_arg1; // size >= 0x20

typedef struct unk_func_80031660_sp24 {
    /* 0x00 */ u8 pad00[0x18];
    /* 0x18 */ s32 unk_18;
} unk_func_80031660_sp24; // size = 0x1C

extern Camera* gCamPrimary;
extern Camera* gCamSecondary;
extern u32 gCamFovTable[2];
extern FramebufferImage* gCamFramebuffer;
extern s32 gCamTexWidth;
extern s32 gCamTexHeight;
extern s32 gCamTextWidth;
extern u32 gCamGeoLayoutCmdTable[];
extern u32 gCamGeoLayoutIndices[];
extern unk_D_800761B0 gCamQuadVertices[12];

s32 Cam_SetupCameraParams(s32 arg0, CameraStruct* arg1);
s32 Cam_SetActiveCameraParams(s32 arg0, unk_func_80031270_024* arg1);
s32 Cam_GetCameraAngles(s32 arg0, unk_func_8003013C_arg1* arg1);
s32 Cam_GetCameraAnglesInverse(s32 arg0, unk_func_8003013C_arg1* arg1);
s32 Cam_SetActiveGraphNode(s32 arg0, GraphNode* arg1);
s32 Cam_SetActiveNode(s32 arg0, Fragment2_1GraphNode* arg1);
s32 Cam_SetupDefaultCamera(s32 arg0, CameraStruct* arg1);
s32 Cam_RenderView(s32 arg0, UNUSED GraphNode* arg1);

s16 gCamDistances[160] = { 0, 105, 150, 220, 70, 120, 188, 75, 110, 160, 60, 80, 120, 60, 70, 100, 70, 130, 170, 80, 110, 65, 160, 120, 180, 85, 105, 100, 130, 80, 100, 160, 100, 120, 160, 100, 140, 80, 130, 90, 120, 110, 160, 90, 100, 160, 80, 125, 130, 150, 60, 120, 70, 105, 105, 170, 90, 120, 100, 190, 100, 140, 170, 90, 150, 150, 80, 120, 160, 80, 165, 170, 140, 160, 120, 140, 160, 110, 170, 140, 160, 80, 110, 100, 140, 150, 110, 90, 140, 220, 85, 170, 150, 180, 150, 250, 120, 160, 102, 160, 100, 130, 110, 160, 60, 100, 150, 140, 150, 110, 140, 130, 200, 150, 120, 220, 80, 140, 80, 140, 90, 110, 140, 160, 140, 130, 130, 150, 160, 90, 270, 250, 100, 65, 120, 120, 110, 120, 70, 120, 90, 140, 200, 180, 170, 180, 180, 100, 200, 180, 180, 85, 100, 40, 0, 0, 0, 0, 0, 0 };
Camera* gCamPrimary = NULL;
Camera* gCamSecondary = NULL;
u32 gCamFovTable[2] = { 0x42200000, 0x41C80000 };
FramebufferImage* gCamFramebuffer = NULL;
s32 gCamTexWidth = 200;
s32 gCamTexHeight = 43;
s32 gCamTextWidth = 0;
u32 gCamGeoLayoutCmdTable[115] = { 0xC00FFFF, 0x5000000, 0xB00001E, 0, 0x14000F0, 0xF, 0, 0, 0x8000000, (u32)&Cam_SetupCameraParams, 0, 0x5000000, 0xD000000, 0x5000000, 0x13FFFFFF, 0x3C003E8, 0x8000000, (u32)&Cam_SetActiveCameraParams, 0, 0x14000000, 0x2D0019, 0xFFFFFF28, 0x8000000, (u32)&Cam_GetCameraAngles, 0, 0x14000000, 0x2D0019, 0x80808028, 0x8000000, (u32)&Cam_GetCameraAnglesInverse, 0, 0x16646464, 0xF000002, 0x5000000, 0x1F00FFFF, 0, 0, 0, 0x640064, 0x640000, 0x5000000, 0x9000000, 0x8000000, (u32)&Cam_SetActiveGraphNode, 0, 0x6000000, 0x6000000, 0xF000003, 0x5000000, 0x1F00FFFF, 0, 0, 0, 0x640064, 0x640000, 0x5000000, 0x9000000, 0x8000000, (u32)&Cam_SetActiveGraphNode, 1, 0x6000000, 0x6000000, 0xF000002, 0x5000000, 0x1F00FFFF, 0, 0, 0, 0x640064, 0x640000, 0x5000000, 0x9000000, 0x8000000, (u32)&Cam_SetActiveGraphNode, 2, 0x6000000, 0x6000000, 0xF000003, 0x5000000, 0x1F000000, 0, 0, 0xFF060000, 0x640064, 0x640000, 0x8000000, (u32)&Cam_SetActiveNode, 0, 0x6000000, 0x6000000, 0x6000000, 0xB00002D, 0, 0x14000F0, 0, 0xFDBD0000, 0x243, 0x8000000, (u32)&Cam_SetupDefaultCamera, 0, 0x5000000, 0xD000000, 0x5000000, 0xF000002, 0x5000000, 0x22010000, 0, 0x8000000, (u32)&Cam_RenderView, 0, 0x6000000, 0x6000000, 0x6000000, 0x6000000, 0x1000000 };
u32 gCamGeoLayoutIndices[17] = { 0, 1, 3, 4, 5, 6, 7, 8, 9, 0xA, 0xB, 0xC, 0xD, 0xE, 0xF, 0x11, 0 };
unk_D_800761B0 gCamQuadVertices[12] = { { 0, 0, -579, 0, 0, 0, 127, -256 }, { 0, 0, -579, 0, 0, 0, 127, -256 }, { 0, 0, -579, 0, 0, 0, 127, -256 }, { 0, 0, -579, 0, 0, 0, 127, -256 }, { 0, 0, -579, 0, 0, 0, 127, -256 }, { 0, 0, -579, 0, 0, 0, 127, -256 }, { 0, 0, -579, 0, 0, 0, 127, -256 }, { 0, 0, -579, 0, 0, 0, 127, -256 }, { 0, 0, -579, 0, 0, 0, 127, -256 }, { 0, 0, -579, 0, 0, 0, 127, -256 }, { 0, 0, -579, 0, 0, 0, 127, -256 }, { 0, 0, -579, 0, 0, 0, 127, -256 } };
extern f64 D_8007C538;
extern f64 D_8007C540;
extern f64 D_8007C548;
extern f64 D_8007C550;
extern f64 D_8007C558;
extern f64 D_8007C560;
extern f64 D_8007C568;
extern f64 D_8007C570;

void Cam_ClearActive2(void);
void Gallery_Terminate(void);

void Gallery_Run(void) {
    s32 var_s6;
    u32* temp_s0;
    u32 var_s0;
    u32 var_s2;
    u32 sp64;
    u32 var_s5;
    u32 sp5C;
    s32 var_v0;
    unk_D_83407B00* val;

    val = &D_83407B30;
    var_s2 = 0;
    var_s5 = 0;

    main_pool_push_state('SNPM');
    func_8004B1CC(0x4B);

    FRAGMENT_LOAD(fragment43)();
    FRAGMENT_LOAD(fragment34);

    do {
        temp_s0 = Util_ConvertAddrToVirtAddr((u32)val);
        var_s6 = 1;

        main_pool_push_state('galy');

        switch (var_s5) {
            case 0:
                var_v0 = 0;
                if (*temp_s0 != 0) {
                    var_s0 = 1;
                } else {

                    switch (var_s2) {
                        case 4:
                            var_s0 = 2;
                            break;

                        default:
                            var_s0 = 0;
                            if (var_s2 == 7) {
                                var_v0 = 1;
                            }
                            break;
                    }
                }
                sp64 = FRAGMENT_LOAD_AND_CALL(fragment42, var_s0, var_v0);
                break;

            case 1:
            case 6:
                FRAGMENT_LOAD(fragment2)();
                // loaded, but doesnt use any GFX from it. speculated to have intended using the
                // button GFX for How to Snap, but it doesnt use them.
                ASSET_LOAD(D_3000000, kids_club_game_ui, 0);
                FRAGMENT_LOAD(fragment3);
                FRAGMENT_LOAD(fragment31);

                // determine if this is "How to Snap" or regular Snap Mode.
                if (var_s5 == 1) {
                    var_s0 = 0;
                } else {
                    var_s0 = 1;
                }

                switch (FRAGMENT_LOAD_AND_CALL(fragment15, var_s0, 0)) {
                    case 1:
                        sp64 = 5;
                        break;

                    case 2:
                        if (var_s0 == 1) {
                            sp64 = 5;
                        } else {
                            sp64 = 2;
                        }
                        break;

                    default:
                        sp64 = 5;
                        break;
                }
                break;

            case 2:
                if (var_s2 == 4) {
                    var_s0 = 0;
                } else {
                    var_s0 = 1;
                }
                sp64 = FRAGMENT_LOAD_AND_CALL(fragment45, var_s0, 0);
                break;

            case 3:
                var_v0 = 1;
                switch (var_s2) {
                    case 4:
                        var_s0 = sp5C;
                        var_v0 = 0;
                        break;

                    case 2:
                        var_s0 = 1;
                        break;

                    default:
                        if (*temp_s0 != 0) {
                            var_s0 = 2;
                        } else {
                            var_s0 = 0;
                        }
                        break;
                }

                sp64 = FRAGMENT_LOAD_AND_CALL(fragment44, var_s0, var_v0);
                if (sp64 == 4) {
                    sp5C = var_s0;
                }
                break;

            case 4:
                FRAGMENT_LOAD_AND_CALL(fragment46, 0, 0);
                sp64 = var_s2;
                break;

            case 5:
                FRAGMENT_LOAD(fragment61);
                switch (var_s2) {
                    case 1:
                        var_s0 = 1;
                        break;

                    case 6:
                        var_s0 = 2;
                        break;

                    default:
                        var_s0 = 0;
                        break;
                }
                sp64 = FRAGMENT_LOAD_AND_CALL(fragment47, var_s0, 0);
                break;

            case 7:
                FRAGMENT_LOAD_AND_CALL(fragment49, 0, 0);
                sp64 = 0;
                break;

            default:
                var_s6 = 0;
                break;
        }

        var_s2 = var_s5;
        var_s5 = sp64;

        main_pool_pop_state('galy');

    } while (var_s6 != 0);

    ((ret_func_80004454)Util_ConvertAddrToVirtAddr(Gallery_Terminate))();

    main_pool_pop_state('SNPM');
}

void Cam_CallInit318B8(void) {
    Cam_ClearActive2();
}

void Cam_ResetUnkF90(void) {
    gCamFramebuffer = 0;
}

s32 Cam_GetMode(unk_D_83403C60* arg0) {
    return ((s32) arg0->unk_6C >> 2) & 3;
}

f32 Cam_GetFov(unk_D_83403C60* arg0) {
    s32 index;
    f32* table;
    index = ((s32) arg0->unk_6C >> 1) & 1;
    table = (f32*)Util_ConvertAddrToVirtAddr(gCamFovTable);
    return table[index];
}

u32 Cam_GetUnk6CHigh(unk_D_83403C60* arg0) {
    u8 v1 = arg0->unk_6C;
    v1 = v1 >> 4;
    return v1 & 0xF;
}

s32 Cam_GetActive(s32 arg0) {
    Camera* var_a1;
    UNUSED Camera* sp1C;

    var_a1 = NULL;
    switch (arg0) {
    case 0:
        var_a1 = gCamPrimary;
        break;
    case 2:
        var_a1 = gCamSecondary;
        break;
    case 5:
        var_a1 = gCamSecondary;
        break;
    }
    sp1C = var_a1;
    if (Cam_IsMonIndexDisplayable(var_a1) != 0) {
        return Cam_GetMode(var_a1->unk_18);
    }
    return 0;
}

s32 Cam_SetupCameraParams(s32 arg0, CameraStruct* arg1) {
    s32 pad;
    unk_D_83403C60_050_00C* src;

    if (arg0 == 2) {
        src = (unk_D_83403C60_050_00C*)((u8*)gCamSecondary->unk_18 + 0x50);
        Viewport_SetRect(arg1, 0, 0, gCamSecondary->unk_04, gCamSecondary->unk_06);
        Perspective_SetParams(arg1, Cam_GetFov(gCamSecondary->unk_18), 20.0f, 10000.0f);
        ((unk_D_83403C60_050_00C*)((u8*)arg1 + 0xA8))[0] = src[0];
        ((unk_D_83403C60_050_00C*)((u8*)arg1 + 0xA8))[1] = src[1];
        pad = 0;
    }
    return 0;
}

s32 Cam_SetupDefaultCamera(s32 arg0, CameraStruct* arg1) {
    if (Cam_GetActive(arg0) != 0) {
        if (arg0 == 2) {
            Viewport_SetRect(arg1, 0, 0, gCamSecondary->unk_04, gCamSecondary->unk_06);
            Perspective_SetParams(arg1, 45.0f, 20.0f, 8000.0f);
        }
    }
    return 0;
}

s32 Cam_GetCameraAngles(s32 arg0, unk_func_8003013C_arg1* arg1) {
    UNUSED s32 pad;
    f32 sp28;
    s16 sp26;
    s16 sp24;

    if (arg0 == 2) {
        Matrix_Decompose(&gCurrentCameraNode->unk_60.at, &gCurrentCameraNode->unk_60.eye, &sp28, &sp26, &sp24);
        arg1->unk_1C = (s16) (sp26 + 0x2000);
        arg1->unk_1E = (s16) (sp24 - 0x2000);
    }
    return 0;
}

s32 Cam_GetCameraAnglesInverse(s32 arg0, unk_func_8003013C_arg1* arg1) {
    UNUSED s32 pad;
    f32 sp28;
    s16 sp26;
    s16 sp24;

    if (arg0 == 2) {
        Matrix_Decompose(&gCurrentCameraNode->unk_60.at, &gCurrentCameraNode->unk_60.eye, &sp28, &sp26, &sp24);
        arg1->unk_1C = (s16) (-0x2000 - sp26);
        arg1->unk_1E = (s16) (sp24 + 0x6000);
    }
    return 0;
}

s32 Cam_SetActiveNode(s32 arg0, Fragment2_1GraphNode* arg1) {
    if (arg0 == 0) {
        gCamPrimary->unk_20 = arg1;
    }
    return 0;
}

s32 Cam_SetActiveCameraParams(s32 arg0, unk_func_80031270_024* arg1) {
    if (arg0 == 0) {
        gCamPrimary->unk_24 = arg1;
    }
    return 0;
}

s32 Cam_SetActiveGraphNode(s32 arg0, GraphNode* arg1) {
    s32 temp_v0;

    if (arg0 == 0) {
        temp_v0 = arg1->unk_14;
        switch (temp_v0) {                          /* irregular */
        case 0:
            gCamPrimary->unk_28 = arg1;
            break;
        case 1:
            gCamPrimary->unk_2C = arg1;
            break;
        case 2:
            gCamPrimary->unk_30 = arg1;
            break;
        }
        arg1->unk_14 = 0;
    }
    return 0;
}

void Cam_SetupQuadVertices(s32 arg0, s32 arg1) {
    s16 temp_a0;
    s16 temp_a1;
    s32 temp_a3;
    s32 temp_v0;
    s32 temp_v1;
    s32 temp_a2;
    s32 i;
    unk_D_800761B0* var = &gCamQuadVertices[10];
    unk_D_800761B0* var2 = &gCamQuadVertices[11];

    temp_v0 = arg0 - 0xC8;
    temp_v1 = arg0 + 0xC8;
    temp_a2 = arg1 + 0x2B;
    temp_a3 = arg1 - 0x2B;
    for(i = 0; i < 12; i+=2) {
        gCamQuadVertices[i].unk_00 = temp_v0;
        gCamQuadVertices[i].unk_08 = 0;
        gCamQuadVertices[i + 1].unk_00 = temp_v1;
        gCamQuadVertices[i + 1].unk_08 = 0x18E0;
        if (i < 10) {
            temp_a0 = temp_a2 - (i * 0xA);
            gCamQuadVertices[i].unk_02 = temp_a0;
            gCamQuadVertices[i + 1].unk_02 = temp_a0;
            temp_a1 = (i * 5) << 5;
            gCamQuadVertices[i].unk_0A = temp_a1;
            gCamQuadVertices[i + 1].unk_0A = temp_a1;
        } else {
            gCamQuadVertices[10].unk_02 = temp_a3;
            var->unk_0A = 0x540;
            gCamQuadVertices[11].unk_02 = temp_a3;
            var2->unk_0A = 0x540;
        }
    }
}

s32 Cam_RenderView(s32 arg0, UNUSED GraphNode* arg1) {
    s32 temp_v0;
    s32 i;
    char* sp16C;

    temp_v0 = Cam_GetActive(arg0);
    if ((temp_v0 != 0) && (arg0 == 2)) {
        sp16C = (char*)((u8*)gCamSecondary->unk_18 + 0x73);
        gCamTextWidth = MeasureTextWidth(0x10, 0, sp16C);
        Cam_SetupQuadVertices(0, -0x96);
        Gfx_SetupFrameBuffer(&gDisplayListHead, gCamFramebuffer);
        Gfx_FillScreen(&gDisplayListHead, 0);
        gDPPipeSync(gDisplayListHead++);
        gDPSetTexturePersp(gDisplayListHead++, G_TP_NONE);
        gDPSetTextureFilter(gDisplayListHead++, G_TF_BILERP);
        gDPSetTextureConvert(gDisplayListHead++, G_TC_FILT);
        gDPSetTextureLOD(gDisplayListHead++, G_TL_TILE);
        gDPSetTextureDetail(gDisplayListHead++, G_TD_CLAMP);
        gDPSetCycleType(gDisplayListHead++, G_CYC_1CYCLE);
        gDPSetCombineMode(gDisplayListHead++, G_CC_DECALRGBA, G_CC_DECALRGBA);
        gDPSetRenderMode(gDisplayListHead++, G_RM_AA_TEX_EDGE, G_RM_AA_TEX_EDGE2);

        if (temp_v0 == 1) {
            for (i = 0; i < 2; i++) {
                gDPLoadTextureTile(gDisplayListHead++, D_5001950, G_IM_FMT_RGBA, G_IM_SIZ_16b, 100, 0, 0, (i * 15), 99, ((i + 1) * 15) - 1, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
                gSPTextureRectangle(gDisplayListHead++, 0, (i * 15) << 2, 100 << 2, ((i + 1) * 15) << 2, 0, 0, (i * 15) << 5, 1 << 10, 1 << 10);
                gSPTextureRectangle(gDisplayListHead++, 100 << 2, (i * 15) << 2, 200 << 2, ((i + 1) * 15) << 2, 0, 100 << 5, (i * 15) << 5, -(1 << 10), 1 << 10);
            }
            gDPLoadTextureTile(gDisplayListHead++, D_5001950, G_IM_FMT_RGBA, G_IM_SIZ_16b, 100, 0, 0, 30, 99, 42, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
            gSPTextureRectangle(gDisplayListHead++, 0, 30 << 2, 100 << 2, 43 << 2, 0, 0, 30 << 5, 1 << 10, 1 << 10);
            gSPTextureRectangle(gDisplayListHead++, 100 << 2, 30 << 2, 200 << 2, 43 << 2, 0, 100 << 5, 30 << 5, -(1 << 10), 1 << 10);
            Text_ResetState();
            Text_BeginRender();
            Text_SetEnvColor(0xF0, 0x78, 0x6E, 0xFF);
            Text_SetPrimColor(0xF0, 0xF0, 0x78, 0xFF);
            Text_SetFont(0x10, 0);
            Text_Print(0x64 - ((s32) gCamTextWidth / 2), 5, sp16C);
            Text_EndRender();
            Text_SetupDL();
        } else {
            gDPLoadTextureTile(gDisplayListHead++, D_5003AE8, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 40, 0, 0, 31, 39, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
            gSPTextureRectangle(gDisplayListHead++, 16 << 2, 0 << 2, 152 << 2, 40 << 2, 0, 0, 0, 1 << 10, 1 << 10);
            gSPTextureRectangle(gDisplayListHead++, 152 << 2, 0 << 2, 185 << 2, 40 << 2, 0, 32 << 5, 0, -(1 << 10), 1 << 10);
            Text_ResetState();
            Text_BeginRender();
            Text_SetEnvColor(0xDC, 0xFF, 0xDC, 0xFF);
            Text_SetPrimColor(0x78, 0xB4, 0xFF, 0xFF);
            Text_SetFont(0x10, 0);
            Text_Print(0x64 - ((s32) gCamTextWidth / 2), 7, sp16C);
            Text_EndRender();
            Text_SetupDL();
        }
        Gfx_SetupFrameBuffer(&gDisplayListHead, gCamSecondary->unk_08);
        gDPPipeSync(gDisplayListHead++);
        gDPSetCycleType(gDisplayListHead++, G_CYC_1CYCLE);
        gDPSetCombineMode(gDisplayListHead++, G_CC_DECALRGBA, G_CC_DECALRGBA);
        gDPSetRenderMode(gDisplayListHead++, G_RM_AA_TEX_EDGE, G_RM_AA_TEX_EDGE2);
        gSPTexture(gDisplayListHead++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);
        gSPMatrix(gDisplayListHead++, &gCamProjectionMatrix, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPVertex(gDisplayListHead++, gCamQuadVertices, 12, 0);
        for (i = 0; i < 10; i += 2) {
            gDPLoadMultiTile(gDisplayListHead++, gCamFramebuffer->img_p, 0, 0, G_IM_FMT_RGBA, G_IM_SIZ_16b, gCamTexWidth, gCamTexHeight, 0, i * 5, gCamTexWidth - 1, (i + 2) * 5 - 1, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
            gSP2Triangles(gDisplayListHead++, i, 2 + i, 1 + i, i, 1 + i, 2 + i, 3 + i, i);
        }
        gDPLoadMultiTile(gDisplayListHead++, gCamFramebuffer->img_p, 0, 0, G_IM_FMT_RGBA, G_IM_SIZ_16b, gCamTexWidth, gCamTexHeight, 0, 40, gCamTexWidth - 1, gCamTexHeight - 1, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
        gSP2Triangles(gDisplayListHead++, 9, 8, 10, 0, 11, 9, 10, 0);
        gSPTexture(gDisplayListHead++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF);
    }
    return 0;
}

void Cam_ConvertInputToState(unk_D_83402EE0_070* arg0, PokemonData* arg1) {
    s32 i;

    bzero(arg0, sizeof(unk_D_83402EE0_070));
    arg0->unk_00 = arg1->unk_0E;
    arg0->unk_02 = arg1->unk_00.unk_00;

    for (i = 0; i < 11; i++) {
        arg0->unk_03[i] = ((s8*)arg1->unk_30)[i];
    }

    for (i = 0; i < 11; i++) {
        arg0->unk_0E[i] = ((s8*)arg1->unk_3B)[i];
    }
}

void Cam_ConvertStateToInput(PokemonData* arg0, unk_D_83407AC8* arg1) {
    s32 i;

    bzero(arg0, sizeof(PokemonData));

    arg0->unk_0E = arg1->unk_00;
    arg0->unk_00.unk_00 = arg1->unk_02;

    for (i = 0; i < 11; i++) {
        arg0->unk_30[i] = arg1->unk_03[i];
    }

    for (i = 0; i < 11; i++) {
        arg0->unk_3B[i] = arg1->unk_0E[i];
    }
}

void Cam_ProcessGeoLayout(Camera* arg0, UNUSED s16 arg1, UNUSED s16 arg2) {
    UNUSED s32 pad;
    MemoryBlock* sp18;

    sp18 = state_pool_try_init(main_pool_get_available(), 0);
    gCamPrimary = arg0;
    arg0->unk_1C = process_geo_layout(sp18, gCamGeoLayoutCmdTable);
    gCamPrimary = NULL;
    mem_pool_resize_block(sp18);
}

Camera* Cam_Create(s16 arg0, s16 arg1, FramebufferImage* arg2, FramebufferImage* arg3,
                                 AssetManager* arg4, BinArchive* arg5, unk_D_83403C60* arg6) {
    UNUSED FramebufferImage* var_v0;
    Camera* temp_v0 = main_pool_alloc(sizeof(Camera), 0);

    if (temp_v0 != NULL) {
        temp_v0->unk_00 = 0;
        temp_v0->unk_02 = 0;
        temp_v0->unk_04 = arg0;
        temp_v0->unk_06 = arg1;

        if (arg2 != NULL) {
            temp_v0->unk_08 = arg2;
        } else {
            temp_v0->unk_08 = FramebufferImage_Allocate(0, 2, arg0, arg1, 0);
        }

        if (arg3 != NULL) {
            temp_v0->unk_0C = arg3;
        } else {
            temp_v0->unk_0C = FramebufferImage_Allocate(0, 2, arg0, arg1, 1);
        }

        FramebufferImage_AttachDepth(temp_v0->unk_08, temp_v0->unk_0C);

        temp_v0->unk_10 = arg4;
        temp_v0->unk_14 = arg5;
        temp_v0->unk_18 = arg6;
        temp_v0->unk_34 = 0;

        if (gCamFramebuffer == 0) {
            gCamFramebuffer = FramebufferImage_Allocate(0, 2, 0xC8, 0x2B, 0);
        }

        Cam_ProcessGeoLayout(temp_v0, arg0, arg1);
    }
    return temp_v0;
}

typedef union unk_func_80026268_arg0_000_raw {
    struct {
        u8 unk_00;
        u8 unk_01;
        u16 unk_02;
    };
    f32 raw;
} unk_func_80026268_arg0_000_raw; // size = 0x4

typedef struct unk_func_80026268_arg0_raw {
    /* 0x00 */ unk_func_80026268_arg0_000_raw unk_00;
    /* 0x04 */ u8 unk_04;
    /* 0x05 */ u8 unk_05;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ u8 unk_08;
    /* 0x09 */ u8 unk_09[4];
    /* 0x0D */ u8 pad0D;
    /* 0x0E */ u16 unk_0E;
    /* 0x10 */ u32 unk_10;
    /* 0x14 */ u16 unk_14;
    /* 0x16 */ u16 unk_16;
    /* 0x18 */ u16 unk_18;
    /* 0x1A */ u16 unk_1A;
    /* 0x1C */ u16 unk_1C;
    /* 0x1E */ u16 unk_1E;
    /* 0x20 */ u8 unk_20[4];
    /* 0x24 */ u8 unk_24;
    /* 0x25 */ u8 unk_25;
    /* 0x26 */ u16 unk_26;
    /* 0x28 */ u16 unk_28;
    /* 0x2A */ u16 unk_2A;
    /* 0x2C */ u16 unk_2C;
    /* 0x2E */ u16 unk_2E;
    /* 0x30 */ u8 unk_30[11];
    /* 0x3B */ u8 unk_3B[11];
    /* 0x46 */ u8 unk_46[11];
    /* 0x51 */ char unk51[0x1];
    /* 0x52 */ u8 unk_52;
    /* 0x53 */ u8 unk_53;
} unk_func_80026268_arg0_raw; // size = 0x54

typedef struct unk_D_83403C60_raw {
    /* 0x00 */ unk_func_80026268_arg0_raw unk_00;
    /* 0x54 */ char unk54[0x18];
    /* 0x6C */ u8 unk_6C;
    /* 0x6D */ char unk6D[0x3];
    /* 0x70 */ unk_D_83407AC8 unk_70;
    /* 0x8A */ char unk8A[0x2];
} unk_D_83403C60_raw; // size = 0x8C

void Cam_Initialize(Camera* arg0) {
    s32 sp94;
    arg1_func_80010CA8 sp90;
    UNUSED s32 pad[3]; // PokemonData potentially bigger?
    PokemonData sp30;
    unk_D_83403C60_raw* temp_s1;
    void (*sp28)(void*, u32);

    temp_s1 = (unk_D_83403C60_raw*)arg0->unk_18;
    Cam_ConvertStateToInput(&sp30, &temp_s1->unk_70);
    Vec3f_Set(&arg0->unk_20->unk_024, 0, temp_s1->unk_00.unk_00.raw, 0); //?
    arg0->unk_20->modelPhase = 0xFE;
    sp94 = sp30.unk_00.unk_00;
    if (sp30.unk_00.unk_00 == 0x99) {
        sp30.unk_00.unk_00 = 0x19;
    }
    ComputeStatFromName(&sp90, &sp30);
    sp30.unk_00.unk_00 = sp94;
    AssetManager_RequestLoad(arg0->unk_10, sp30.unk_00.unk_00, sp90);
    AssetManager_WaitLoadQueue(arg0->unk_10);
    GraphNode_ClearCallback(arg0->unk_20);
    GraphNode_InitChild(arg0->unk_20, 0, sp30.unk_00.unk_00, arg0->unk_10->unk_24->unk_08->unk_00[0]);
    sp28 = Util_ConvertAddrToVirtAddr(&Particle_Deserialize);
    sp28(arg0->unk_20, Util_ConvertAddrToVirtAddr(&temp_s1->unk_00.unk_09[1]));
    GraphNode_TriggerAction(arg0->unk_20, temp_s1->unk_00.unk_05);
    Anim_SetChannelBase(arg0->unk_20, temp_s1->unk_00.unk_06);
    GraphNode_TriggerSound(arg0->unk_20, temp_s1->unk_00.unk_08);
    SetAnimStateIndex(arg0->unk_20, (s16)temp_s1->unk_00.unk_09[0]);
}

void Cam_LoadGeometry(Camera* arg0) {
    MemoryBlock* sp24;
    FragmentEntry sp20;
    u32* temp_v0;
    u32* temp_v0_2;
    u32* temp_v0_3;
    unk_func_800314BC_temp_v4* temp_v0_4;
    unk_func_80031270_024* temp_v1;

    GraphNode_AllocInit(0, arg0->unk_28);
    GraphNode_AllocInit(0, arg0->unk_2C);
    GraphNode_AllocInit(0, arg0->unk_30);
    sp20 = BinArchive_GetFile(arg0->unk_14, gCamGeoLayoutIndices[Cam_GetUnk6CHigh(arg0->unk_18)]);
    sp24 = state_pool_try_init(main_pool_get_available(), 0);
    temp_v0 = sp20(0, 0);
    if (temp_v0 != NULL) {
        GraphNode_AddChild(arg0->unk_28, process_geo_layout(sp24, temp_v0));
    }
    temp_v0_2 = sp20(1, 0);
    if (temp_v0_2 != NULL) {
        GraphNode_AddChild(arg0->unk_2C, process_geo_layout(sp24, temp_v0_2));
    }
    temp_v0_3 = sp20(3, 0);
    if (temp_v0_3 != NULL) {
        GraphNode_AddChild(arg0->unk_30, process_geo_layout(sp24, temp_v0_3));
    }
    arg0->unk_34 = sp20(2, 0);
    mem_pool_resize_block(sp24);
    temp_v0_4 = sp20(4, 0);
    if (temp_v0_4 == NULL) {
        temp_v1 = arg0->unk_24;
        temp_v1->unk_01 = (u8) (temp_v1->unk_01 & 0xFFFE);
        arg0->unk_24->unk_14 = 0;
        return;
    }
    arg0->unk_24->unk_18 = (s16) temp_v0_4->unk_00;
    arg0->unk_24->unk_1A = (s16) temp_v0_4->unk_02;
    arg0->unk_24->unk_1C = (s32) temp_v0_4->unk_04;
    arg0->unk_24->unk_14 = 1;
    temp_v1 = arg0->unk_24;
    temp_v1->unk_01 = (u8) (temp_v1->unk_01 | 1);
}

u8* Cam_Update(Camera* arg0) {
    unk_func_80031660_sp24* sp24;
    void (*sp20)();

    sp24 = (unk_func_80031660_sp24*)((u8*)arg0->unk_18 + 0x50);
    sp20 = Util_ConvertAddrToVirtAddr(&Timer_Tick);
    gCamSecondary = arg0;
    if (arg0->unk_00 == 1) {
        switch (arg0->unk_02) {
            case 2:
                Cam_Initialize(arg0);
                Cam_LoadGeometry(arg0);
                break;
            case 1:
                Gfx_SetupFrameBuffer(&gDisplayListHead, arg0->unk_08);

                if ((arg0->unk_34 == -1) || (arg0->unk_34 == 0)) {
                    Gfx_FillScreen(&gDisplayListHead, 1);
                } else if (arg0->unk_34 < 0x10000U) {
                    Gfx_FillScreen(&gDisplayListHead, arg0->unk_34);
                } else {
                    Gfx_FillScreen(&gDisplayListHead, 0xA6BF);
                }
                Gfx_FinishFrame();
                *((s32*)Util_ConvertAddrToVirtAddr(&gTimerCounter)) = sp24->unk_18;
                sp20();
                Graph_SetTextureState(arg0->unk_1C);
                break;
            default:
                break;
        }
 
    }
    switch (arg0->unk_00) {
        case 0:
            arg0->unk_00 = 1;
            arg0->unk_02 = 2;
            break;
        case 1:
            arg0->unk_02--;
            if (arg0->unk_02 <= 0) {
                arg0->unk_00 = 2;
            }
            break;
        case 2:
            break;
    }
    return arg0->unk_08->img_p;
}

s32 Cam_IsMonIndexDisplayable(Camera* arg0) {
    s32 var_v1;
    s32 sp1C;
    unk_D_83403C60* temp_a0;

    var_v1 = 0;
    if (arg0 != NULL) {
        temp_a0 = arg0->unk_18;
        if (temp_a0 != 0) {
            sp1C = 0;
            var_v1 = sp1C;
            if (IsMonIndexDisplayable(temp_a0) != 0) {
                var_v1 = 1;
            }
        }
    }
    return var_v1;
}

s32 Cam_FindActiveIndex(Camera** arg0, s32 arg1) {
    Camera* temp_s1;
    s32 sp30;
    s32 i;

    sp30 = -1;

    for (i = 0; i < arg1; i++) {
        temp_s1 = arg0[i];
        if ((Cam_IsMonIndexDisplayable(temp_s1) != 0) && (temp_s1->unk_00 == 1)) {
            sp30 = i;
            break;
        }
    }
    return sp30;
}

Camera* Cam_GetCurrent(void) {
    return gCamSecondary;
}

void Cam_ClearActive2(void) {
    gCamSecondary = 0;
}

s32 IsMonIndexDisplayable(unk_D_83403C60* arg0) {
    s32 v1 = 0;

    if ((arg0->unk_00.unk_04 > 0 && arg0->unk_00.unk_04 < 0x98) || arg0->unk_00.unk_04 == 0x99) {
        v1 = 1;
    }
    return v1;
}

void func_800318F0(void) {
    func_80036790();
}

void Matrix_BillboardBetween(Mtx* mtx, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6) {
    f32 sp144;
    f32 sp140;
    f32 temp_fa0;
    f32 temp_fa1;
    UNUSED s32 pad[1];
    Mtx spF0;
    Mtx spB0;
    Mtx sp70;
    UNUSED s32 pad2[16];

    temp_fa1 = arg4 - arg1;
    temp_fa0 = arg6 - arg3;
    sp140 = (f32) (((f64) (f32) MathUtil_Atan2s(temp_fa0, temp_fa1) * D_8007C538) / D_8007C540);
    sp144 = (f32) (((f64) (f32) MathUtil_Atan2s(arg5 - arg2, sqrtf((temp_fa1 * temp_fa1) + (temp_fa0 * temp_fa0))) * D_8007C548) / D_8007C550);
    guRotate(&spB0, sp140, 0.0f, 1.0f, 0.0f);
    guRotate(&sp70, sp144, 0.0f, 0.0f, 1.0f);
    guMtxCatL(&spB0, &sp70, &spF0);
    *mtx = spF0;
}

f32 Math_AbsF(f32 arg0) {
    if (arg0 < 0.0) {
        arg0 = -arg0;
    }
    return arg0;
}

void Math_CrossProductComponents(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32* arg6, f32* arg7, f32* arg8) {
    *arg6 = (arg1 * arg5) - (arg2 * arg4);
    *arg7 = (arg2 * arg3) - (arg0 * arg5);
    *arg8 = (arg0 * arg4) - (arg1 * arg3);
}

void Math_NormalizeVector(f32* arg0, f32* arg1, f32* arg2) {
    f32 temp_fv1;
    f32 temp_fa1;
    f32 temp_ft4;
    f32 temp_fv0;

    temp_fv1 = *arg0;
    temp_fa1 = *arg1;
    temp_ft4 = *arg2;
    temp_fv0 = sqrtf((temp_fv1 * temp_fv1) + (temp_fa1 * temp_fa1) + (temp_ft4 * temp_ft4));
    if (temp_fv0 > 0.0f) {
        temp_fv1 /= temp_fv0;
        temp_fa1 /= temp_fv0;
        temp_ft4 /= temp_fv0;
    }
    *arg0 = temp_fv1;
    *arg1 = temp_fa1;
    *arg2 = temp_ft4;
}

void func_80031B98(const f32* a, const f32* b, f32* out) {
    f32 ax = a[0];
    f32 ay = a[1];
    f32 az = a[2];

    f32 bx = b[0];
    f32 by = b[1];
    f32 bz = b[2];

    out[0] = (ay * bz) - (az * by);
    out[1] = (az * bx) - (ax * bz);
    out[2] = (ax * by) - (ay * bx);
}

void func_80031BE8(Vec3f* vec) {
    f32 x;
    f32 y;
    f32 z;
    f32 len;

    x = vec->x;
    y = vec->y;
    z = vec->z;

    len = sqrtf((x * x) + (y * y) + (z * z));

    if (len > 0.0f) {
        x = x / len;
        y = y / len;
        z = z / len;
    }

    vec->x = x;
    vec->y = y;
    vec->z = z;
}

void func_80031C6C(Mtx* mtx, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6) {
    f32 sp10C;
    f32 sp108;
    UNUSED s32 pad;
    UNUSED s32 pad2;
    f32 temp_fa1;
    f32 temp_fv0;
    Mtx spB8;
    Mtx sp78;
    Mtx sp38;

    temp_fa1 = arg4 - arg1;
    temp_fv0 = arg6 - arg3;
    sp108 = (f32) (((f64) (f32) MathUtil_Atan2s(-temp_fv0, temp_fa1) * D_8007C558) / D_8007C560);
    sp10C = (f32) (((f64) (f32) MathUtil_Atan2s(-(arg5 - arg2), sqrtf((temp_fa1 * temp_fa1) + (temp_fv0 * temp_fv0))) * D_8007C568) / D_8007C570);
    guTranslate(&spB8, arg1, arg2, arg3);
    guRotate(&sp78, sp108, 0.0f, -1.0f, 0.0f);
    guMtxCatL(&sp78, &spB8, &spB8);
    guRotate(&sp38, sp10C, 1.0f, 0.0f, 0.0f);
    guMtxCatL(&sp38, &spB8, &spB8);
    *mtx = spB8;
}

void Math_ClosestPointOnLineSegment(
    f32 px, f32 py, f32 pz,
    f32 ax, f32 ay, f32 az,
    f32 bx, f32 by, f32 bz,
    f32* outX, f32* outY, f32* outZ
) {
    f32 dx;
    f32 dy;
    f32 dz;
    f32 t;
    f32 lenSq = SQ(bx - ax) + SQ(by - ay) + SQ(bz - az);
    f32 dx2;
    f32 dy2;
    f32 dz2;

    if (lenSq == 0.0) {
        *outX = ax;
        *outY = ay;
        *outZ = az;
        return;
    }

    
    dx = bx - ax;
    dy = by - ay;
    dz = bz - az;
    dx2 = px - ax;
    dy2 = py - ay;
    dz2 = pz - az;

    t = ((dx * dx2) + (dy * dy2) + (dz * dz2)) / lenSq;

    *outX = ax + (t * dx);
    *outY = ay + (t * dy);
    *outZ = az + (t * dz);
}

void Camera_CopyMatrixF(MtxF* arg0, MtxF* arg1) {
    f32 sp24 = sqrtf(SQ(arg1->mf[0][0]) + SQ(arg1->mf[0][1]) + SQ(arg1->mf[0][2]));
    f32 sp20 = sqrtf(SQ(arg1->mf[1][0]) + SQ(arg1->mf[1][1]) + SQ(arg1->mf[1][2]));
    f32 sp1C = sqrtf(SQ(arg1->mf[2][0]) + SQ(arg1->mf[2][1]) + SQ(arg1->mf[2][2]));

    arg0->mf[0][0] = arg1->mf[0][0] * sp24;
    arg0->mf[0][1] = arg1->mf[1][0] * sp24;
    arg0->mf[0][2] = arg1->mf[2][0] * sp24;
    arg0->mf[0][3] = 0.0f;

    arg0->mf[1][0] = arg1->mf[0][1] * sp20;
    arg0->mf[1][1] = arg1->mf[1][1] * sp20;
    arg0->mf[1][2] = arg1->mf[2][1] * sp20;
    arg0->mf[1][3] = 0.0f;

    arg0->mf[2][0] = arg1->mf[0][2] * sp1C;
    arg0->mf[2][1] = arg1->mf[1][2] * sp1C;
    arg0->mf[2][2] = arg1->mf[2][2] * sp1C;
    arg0->mf[2][3] = 0.0f;

    arg0->mf[3][0] = 0.0f;
    arg0->mf[3][1] = 0.0f;
    arg0->mf[3][2] = 0.0f;
    arg0->mf[3][3] = 1.0f;
}

void Matrix_GetScaleVector(MtxF* arg0, Vec3f* arg1) {
    f32 temp_fa1;
    f32 temp_fv0;
    f32 temp_fv1;
    f32 sp30;
    f32 sp2C;
    f32 sp28;
    f32 sp24;
    f32 sp20;
    f32 sp1C;

    temp_fv0 = arg0->mf[0][0];
    temp_fv1 = arg0->mf[0][1];
    temp_fa1 = arg0->mf[0][2];

    sp30 = arg0->mf[1][0];
    sp2C = arg0->mf[1][1];
    sp28 = arg0->mf[1][2];

    sp24 = arg0->mf[2][0];
    sp20 = arg0->mf[2][1];
    sp1C = arg0->mf[2][2];

    arg1->x = sqrtf(SQ(temp_fv0) + SQ(temp_fv1) + SQ(temp_fa1));
    arg1->y = sqrtf(SQ(sp30) + SQ(sp2C) + SQ(sp28));
    arg1->z = sqrtf(SQ(sp24) + SQ(sp20) + SQ(sp1C));
}
