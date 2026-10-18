#include "fragment17.h"
#include "src/12D80.h"
#include "src/17300.h"
#include "src/geo_layout.h"
#include "src/19840.h"
#include "src/1C720.h"
#include "src/1CF30.h"
#include "src/20330.h"
#include "src/26820.h"
#include "src/2E110.h"
#include "src/3FB0.h"
#include "src/4BDC0.h"
#include "src/6BC0.h"
#include "src/F420.h"
#include "src/controller.h"
#include "src/fragments/34/fragment34.h"
#include "src/memory.h"
#include "src/stage_loader.h"

typedef struct unk_D_86B0E5D8 {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ u8 unk_04;
    /* 0x05 */ u8 unk_05;
    /* 0x06 */ u8 unk_06;
    /* 0x07 */ u8 unk_07;
    /* 0x08 */ s16 unk_08;
    /* 0x0A */ s16 unk_0A;
} unk_D_86B0E5D8; // size = 0xC

extern u32 D_86B0BD60[];
extern unk_D_86B0C4C8* gFragment17ObjectDefs[];
extern unk_D_86B0C160 gFragment17AnimData[];
extern unk_D_86B0C264 gFragment17PresetData[];
extern u32 D_86B0CF9C[];
extern u32 D_86B0DA9C[];

s32 Callback_UpdateColorAndPos(s32, GraphNode*);
s32 Callback_SetScaleLarge(s32, GraphNode*);
s32 Callback_SetScaleNormal(s32, GraphNode*);
s32 Callback_SetObjectState(s32, GraphNode*);

static s16 D_86B0BBF0 = -0x3C6E;
static s16 D_86B0BBF4 = 0x38E;

static u32 gFragment17GeoLayoutCommands[] = {
    0x0C00FFFF, 0x05000000, 0x0B00001E, 0x00000000, 0x014000F0,  0x0000000F,    0x00000000,    0x00000000,
    0x05000000, 0x0D000000, 0x05000000, 0x1A050000, 0x08000000,  Callback_SetObjectState, 0x00000000,    0x05000000,
    0x0F000002, 0x05000000, 0x06000000, 0x0F000002, 0x05000000,  0x06000000,    0x0F000002,    0x05000000,
    0x1F00FFFF, 0xC3920000, 0x00000000, 0xFC400000, 0x00640064,  0x00640000,    0x08000000,    Callback_SetScaleLarge,
    0x00000000, 0x05000000, 0x00000000, D_86B0CF9C, 0x06000000,  0x06000000,    0x0F000002,    0x05000000,
    0x1F00FFFF, 0x00000000, 0x00000000, 0x0514F79A, 0x00640064,  0x00640000,    0x08000000,    Callback_SetScaleNormal,
    0x00000000, 0x05000000, 0x00000000, D_86B0DA9C, 0x06000000,  0x06000000,    0x0F000002,    0x05000000,
    0x06000000, 0x06000000, 0x14000000, 0xF8E40000, 0xFFC89BFF,  0x08000000,    Callback_UpdateColorAndPos, 0x00000000,
    0x16FFFFFF, 0x0F000003, 0x05000000, 0x0A000000, &gGraphRoot0, 0x06000000,    0x06000000,    0x06000000,
    0x06000000, 0x01000000,
};

static GraphNode* gFragment17RootNode;
static unk_D_86B0E5D4* gFragment17State;
static unk_D_86B0E5D8* gFragment17ColorAnim;
s32 D_86B0E5DC;
char** D_86B0E5E0;
static BinArchive* D_86B0E5E4;
static u8* D_86B0E5E8;
static unk_D_86B0E5F0 gFragment17Objects[4];
static s32 gFragment17WindowAlpha;
static s32 gFragment17Result;
static u16 D_86B0EBB8;

s32 Callback_UpdateColorAndPos(s32 arg0, GraphNode* arg1) {
    if (arg0 == 2) {
        unk_D_86002F34_alt18* ptr = (unk_D_86002F34_alt18*)arg1;

        gFragment17ColorAnim->unk_00 += gFragment17ColorAnim->unk_08;
        gFragment17ColorAnim->unk_02 += gFragment17ColorAnim->unk_0A;

        ptr->unk_1C = gFragment17ColorAnim->unk_00;
        ptr->unk_1E = gFragment17ColorAnim->unk_02;
        ptr->r = gFragment17ColorAnim->unk_05;
        ptr->g = gFragment17ColorAnim->unk_06;
        ptr->b = gFragment17ColorAnim->unk_07;
        ptr->a = gFragment17ColorAnim->unk_04;
    }

    return 0;
}

s32 Callback_SetScaleLarge(s32 arg0, GraphNode* arg1) {
    if (arg0 == 2) {
        Fragment2_1GraphNode* ptr = (Fragment2_1GraphNode*)arg1;

        ptr->unk_030.x = 1.5f;
        ptr->unk_030.y = 1.5f;
        ptr->unk_030.z = 1.5f;
        ptr->unk_01E.x = D_86B0BBF0;
    }

    return 0;
}

s32 Callback_SetScaleNormal(s32 arg0, GraphNode* arg1) {
    if (arg0 == 2) {
        Fragment2_1GraphNode* ptr = (Fragment2_1GraphNode*)arg1;

        ptr->unk_030.x = 1.0f;
        ptr->unk_030.y = 1.0f;
        ptr->unk_030.z = 1.0f;

        ptr->unk_01E.x = D_86B0BBF4;
    }
    return 0;
}

s32 Callback_SetObjectState(s32 arg0, GraphNode* arg1) {
    if (arg0 == 2) {
        unk_D_86002F34_alt21* ptr = (unk_D_86002F34_alt21*)arg1;

        ptr->unk_1A = gFragment17State->unk_04.unk_44;
    }
    return 0;
}

void func_86B001D8(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        gFragment17Objects[i].unk_16C = 0;
    }
}

void func_86B001FC(unk_D_86B0E5F0* arg0) {
    while (arg0->unk_16C != 1) {
        GraphNode_ClearCallback(&arg0->unk_004);
        arg0++;
    }
    main_pool_pop_state('MONS');
}

void func_86B00258(void) {
    main_pool_push_state('MONS');
}

void func_86B0027C(unk_D_86B0E5F0* arg0, unk_D_86B0C4C8* arg1) {
    Graph_AddToRootList0(&arg0->unk_004);

    arg0->unk_000 = GeoLayout_LoadById(arg1->unk_0C);

    GraphNode_InitChild(&arg0->unk_004, 0, arg1->unk_0C, arg0->unk_000->unk_08->unk_00[0]);
    GraphNode_TriggerAction(&arg0->unk_004, arg1->unk_10);

    if (arg1->unk_0C == 6) {
        arg0->unk_004.modelPhase = 0;
    } else {
        arg0->unk_004.modelPhase = 0xFF;
    }

    Anim_SetChannelBase(&arg0->unk_004, 0);
    arg0->unk_004.unk_000.unk_02 &= ~0x40;
}

void func_86B0032C(unk_D_86B0E5F0* arg0, unk_D_86B0C4C8* arg1) {
    arg0->unk_004.unk_024.x = arg1->unk_00.x;
    arg0->unk_004.unk_024.y = arg1->unk_00.y;
    arg0->unk_004.unk_024.z = arg1->unk_00.z;
}

void func_86B00348(s32 arg0) {
    gFragment17ColorAnim->unk_00 = gFragment17PresetData[arg0].unk_0C;
    gFragment17ColorAnim->unk_02 = gFragment17PresetData[arg0].unk_0E;
    gFragment17ColorAnim->unk_08 = gFragment17PresetData[arg0].unk_18;
    gFragment17ColorAnim->unk_0A = gFragment17PresetData[arg0].unk_1A;
    gFragment17ColorAnim->unk_05 = gFragment17PresetData[arg0].unk_10;
    gFragment17ColorAnim->unk_06 = gFragment17PresetData[arg0].unk_12;
    gFragment17ColorAnim->unk_07 = gFragment17PresetData[arg0].unk_14;
    gFragment17ColorAnim->unk_04 = gFragment17PresetData[arg0].unk_16;
}

void Fragment_LoadObjectsForPreset(s32 arg0) {
    unk_D_86B0C4C8* var_s0 = gFragment17ObjectDefs[arg0];
    unk_D_86B0E5F0* var_s1 = gFragment17Objects;

    func_86B001D8();
    func_86B00258();

    while (var_s0->unk_0C != 0x98) {
        func_86B0027C(var_s1, var_s0);
        func_86B0032C(var_s1, var_s0);
        var_s1->unk_16C = 1;

        var_s1++;
        var_s0++;
    }

    func_86B00348(arg0);
}

void func_86B00470(s32 arg0) {
    unk_D_86B0C4C8* sp2C = gFragment17ObjectDefs[arg0];
    unk_D_86B0E5F0* var_s1 = gFragment17Objects;

    func_86B001FC(gFragment17Objects);
    func_86B001D8();
    func_86B00258();

    while (sp2C->unk_0C != 0x98) {
        func_86B0027C(var_s1, sp2C);
        func_86B0032C(var_s1, sp2C);
        var_s1->unk_16C = 1;

        var_s1++;
        sp2C++;
    }

    func_86B00348(arg0);

    if (arg0 == 4) {
        GraphNode_TriggerSound(&gFragment17Objects[0].unk_004, 0);
    }
}

void func_86B0054C(s32 arg0) {
    if (arg0 == 4) {
        gFragment17State->unk_00->unk_60.at.x = -0.04f;
        gFragment17State->unk_00->unk_60.at.y = 24.2f;
        gFragment17State->unk_00->unk_60.at.z = -4.08f;
        gFragment17State->unk_00->unk_60.eye.x = 0.04f;
        gFragment17State->unk_00->unk_60.eye.y = 24.2f;
        gFragment17State->unk_00->unk_60.eye.z = 177.41f;
        gFragment17State->unk_00->unk_24.fovy = 25.0f;
    } else {
        gFragment17State->unk_04.unk_00.x = gFragment17PresetData[arg0].unk_00.x;
        gFragment17State->unk_04.unk_00.y = gFragment17PresetData[arg0].unk_00.y;
        gFragment17State->unk_04.unk_00.z = gFragment17PresetData[arg0].unk_00.z;

        InitCameraFromConfig(&gFragment17AnimData[arg0], gFragment17State);
        ApplyCameraViewParameters(&gFragment17State->unk_04, gFragment17State);
    }
}

void func_86B00680(void) {
}

void func_86B00688(void) {
    s32 i = 0;

    if ((gFragment17State->unk_04.unk_4C != 5) && (gFragment17State->unk_04.unk_4C != 6) && (gFragment17State->unk_04.unk_4C != 7) &&
        (gFragment17State->unk_04.unk_4C != 8)) {
        if (gFragment17State->unk_04.unk_44 != 4) {
            while (gFragment17ObjectDefs[gFragment17State->unk_04.unk_44][i].unk_0C != 0x98) {
                if (func_800174E4(&gFragment17Objects[i].unk_004) != 0) {
                    Anim_SetChannelBase(&gFragment17Objects[i].unk_004, 0);
                }
                i++;
            }
        }
    }
}

void func_86B00794(void) {
    if (gFragment17State->unk_04.unk_48 == 1) {
        Text_DrawWindowRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0, 0, gFragment17WindowAlpha);
    }
}

void func_86B007EC(void) {
    if (gFragment17State->unk_04.unk_44 == 2) {
        func_86B01D8C(&D_86B0BD60, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 4, 0x80);
    }
}

s32 func_86B00848(s32 arg0) {
    unk_D_86B0E5F0* var_v0 = gFragment17Objects;
    unk_D_86B0C4C8* var_v1 = gFragment17ObjectDefs[arg0];
    s32 var_a1 = 1;

    while (var_v1->unk_0C != 0x98) {
        var_v0->unk_004.unk_024.z += 20.0f;
        if (var_v0->unk_004.unk_024.z <= 650.0f) {
            var_a1 = 0;
        }
        var_v0++;
        var_v1++;
    }
    return var_a1;
}

void func_86B008C4(void) {
    Stage_SetFillColor(1);
    Stage_FadeOut(0xC);
    gFragment17State->unk_04.unk_4C = 0;
    gFragment17State->unk_04.unk_50 = 0;
}

void func_86B00904(void) {
    gFragment17State->unk_04.unk_4C = 9;
    gFragment17State->unk_04.unk_50 = 0;
    gFragment17Objects->unk_004.unk_000.unk_01 &= ~1;
    D_86B0E5DC = 1;
}

void func_86B00944(s32 arg0) {
    unk_D_86B0C4C8* ptr1 = gFragment17ObjectDefs[arg0];
    unk_D_86B0E5F0* ptr2 = &gFragment17Objects[0];
    s16 sp88[] = {
        // D_86B0BD20
        0x1554,
        0x1554,
        0x1554,
        0x1554,
    };
    s16 sp80[] = {
        // D_86B0BD28
        0x18E2,
        0x11C6,
        0x1554,
        0x1554,
    };
    f32 sp70[] = { 1000.0f, 1000.0f, 2000.0f, 2000.0f }; // D_86B0BD30
    f32 sp60[] = { 1.0f, 1.0f, 100.0f, 50.0f };          // D_86B0BD40

    while (ptr1->unk_0C != 0x98) {
        if (IsPointInSector(gFragment17State->unk_00, &ptr2->unk_004, sp88[arg0], sp80[arg0], sp70[arg0], sp60[arg0]) != 0) {
            ptr2->unk_004.unk_000.unk_01 |= 1;
        } else {
            ptr2->unk_004.unk_000.unk_01 &= ~1;
        }
        ptr2++;
        ptr1++;
    }
}

void func_86B00AE4(void) {
    Cont_StartReadInputs();
    Cont_ReadInputs();
    MenuInput_Init();
}

void func_86B00B14(void) {
    gFragment17State = main_pool_alloc(sizeof(unk_D_86B0E5D4), 0);
    bzero(gFragment17State, sizeof(unk_D_86B0E5D4));

    gFragment17ColorAnim = main_pool_alloc(sizeof(unk_D_86B0E5D8), 0);
    bzero(gFragment17ColorAnim, sizeof(unk_D_86B0E5D8));

    gFragment17State->unk_00 = gFragment17RootNode->unk_0C;

    gFragment17State->unk_00->unk_24.near = 50.0f;
    gFragment17State->unk_00->unk_24.far = 8400.0f;
    gFragment17State->unk_00->unk_24.fovy = 30.0f;
    gFragment17State->unk_00->unk_60.at.x = 50.0f;
    gFragment17State->unk_00->unk_60.at.y = 50.0f;
    gFragment17State->unk_00->unk_60.at.z = 50.0f;
    gFragment17State->unk_00->unk_60.eye.x = 0.0f;
    gFragment17State->unk_00->unk_60.eye.y = 0.0f;
    gFragment17State->unk_00->unk_60.eye.z = 0.0f;
    gFragment17State->unk_04.unk_4C = 8;
    gFragment17State->unk_04.unk_50 = 0;
    gFragment17State->unk_04.unk_48 = 0;
}

s32 StateMachine_Update(void) {
    if (((gPlayer1Controller->buttonPressed & 0x1000) || (gPlayer1Controller->buttonPressed & 0x8000) ||
         (gPlayer1Controller->buttonPressed & 0x4000)) &&
        (gFragment17State->unk_04.unk_48 == 0)) {
        if ((gFragment17State->unk_04.unk_4C != 8) && (gFragment17State->unk_04.unk_4C != 5)) {
            gFragment17State->unk_04.unk_48 = 1;
            func_8004B9C4(0xA);
            gFragment17WindowAlpha = 0;
            gFragment17Result = 2;
        }
    }

    if (gFragment17State->unk_04.unk_48 == 1) {
        gFragment17WindowAlpha = Math_ApproachS32(gFragment17WindowAlpha, 0xFF, 0x1E, 0x1E);
        if (gFragment17WindowAlpha == 0xFF) {
            return 1;
        }
    }

    switch (gFragment17State->unk_04.unk_4C) {
        case 5:
            if (gFragment17State->unk_04.unk_48 == 1) {
                return 1;
            }

            if (gFragment17State->unk_04.unk_44 == 4) {
                gFragment17State->unk_04.unk_50 = 0;
                gFragment17Result = 1;
                return 1;
            }

            gFragment17State->unk_04.unk_44++;
            func_86B0054C(gFragment17State->unk_04.unk_44);
            func_86B00470(gFragment17State->unk_04.unk_44);
            gFragment17State->unk_04.unk_4C = 6;
            gFragment17State->unk_04.unk_50 = 0;
            break;

        case 6:
            if (gFragment17State->unk_04.unk_50++ >= 4) {
                Stage_SetFillColor(1);
                Stage_FadeIn(0x20);
                gFragment17State->unk_04.unk_4C = 7;
                if ((gFragment17State->unk_04.unk_44 == 0) || (gFragment17State->unk_04.unk_44 == 1)) {
                    UpdateCameraTransition(&gFragment17State->unk_04, gFragment17State);
                }
            }
            break;

        case 7:
            if (gFragment17State->unk_04.unk_44 == 4) {
                if (func_800174E4(&gFragment17Objects[0].unk_004) != 0) {
                    func_86B00904();
                }
            } else {
                if (gFragment17State->unk_04.unk_44 >= 2) {
                    if (func_86B00848(gFragment17State->unk_04.unk_44) != 0) {
                        func_86B008C4();
                    }
                } else if (gFragment17State->unk_04.unk_6C < gFragment17State->unk_04.unk_30) {
                    func_86B008C4();
                }

                if ((gFragment17State->unk_04.unk_44 == 0) || (gFragment17State->unk_04.unk_44 == 1)) {
                    UpdateCameraTransition(&gFragment17State->unk_04, gFragment17State);
                }

                func_86B00944(gFragment17State->unk_04.unk_44);
            }
            break;

        case 8:
            if (gFragment17State->unk_04.unk_50++ >= 0xB) {
                gFragment17State->unk_04.unk_44 = 0;
                func_86B0054C(gFragment17State->unk_04.unk_44);
                gFragment17State->unk_04.unk_4C = 6;
                gFragment17State->unk_04.unk_50 = 0;
                Fragment_LoadObjectsForPreset(gFragment17State->unk_04.unk_44);
                func_8004B1CC(0x29);
            }
            break;

        case 9:
            if (gFragment17State->unk_04.unk_50++ >= 3) {
                gFragment17State->unk_04.unk_4C = 5;
                gFragment17State->unk_04.unk_50 = 0;
            }
            break;

        default:
            if (gFragment17State->unk_04.unk_44 != 4) {
                if (gFragment17State->unk_04.unk_44 >= 2) {
                    func_86B00848(gFragment17State->unk_04.unk_44);
                } else {
                    UpdateCameraTransition(&gFragment17State->unk_04, gFragment17State);
                }
            }

            if (gFragment17State->unk_04.unk_50++ >= 0xE) {
                gFragment17State->unk_04.unk_4C = 5;
                gFragment17State->unk_04.unk_50 = 0;
            }
            break;
    }

    return 0;
}

void func_86B01004(void) {
}

void func_86B0100C(void) {
    Stage_BeginDisplayList();
    Gfx_FillScreen(&gDisplayListHead, 1);
    Gfx_FinishFrame();
    func_86B007EC();
    func_86B01C00(D_86B0E5E8);
    Graph_SetTextureState(gFragment17RootNode);
    func_86B00794();
    func_86B02348();
    Stage_Advance();
}

void func_86B0107C(void) {
    s32 var_s1 = 1;
    s32 var_s0 = 0;

    while (var_s1 != 0) {
        func_86B00AE4();
        Timer_UpdateCounters();

        if (StateMachine_Update() != 0) {
            var_s1 = 0;
        }

        var_s0++;
        if (var_s0 == 0x50) {
            var_s0 = 0;
        }

        func_86B00688();
        func_86B0100C();
    }
}

void func_86B010FC(void) {
    func_86B0100C();
}

void func_86B0111C(void) {
    MemoryBlock* sp1C;

    sp1C = state_pool_try_init(main_pool_get_available(), 0);
    gFragment17RootNode = process_geo_layout(sp1C, &gFragment17GeoLayoutCommands);

    mem_pool_resize_block(sp1C);
    Graph_InitRoots();
    AssetManager_LoadArchives();
    func_86B00B14();

    gFragment17WindowAlpha = 0;
    D_86B0E5DC = 0;
}

s32 BattleState_Handle18(void) {
    main_pool_push_state('MINI');

    Text_Init(6, 0);

    ASSET_LOAD(D_1000000, common_menu1_ui, 0);
    FRAGMENT_LOAD(fragment31);
    Fragment_Load((((u32)D_8D000000 & 0x0FF00000) >> 0x14) - 0x10, _5C7A70_ROM_START, _5C7A70_ROM_END);

    GbsEnsureBankLoaded(2);
    GBAudio_ResetState(&D_86B0EBB8, 0);
    D_86B0E5E4 = ASSET_LOAD2(backgrounds, 1, 1);

    if (D_86B0EBB8 == 0x1F8) {
        D_86B0E5E8 = BinArchive_GetFile(D_86B0E5E4, 0x11);
    } else {
        D_86B0E5E8 = BinArchive_GetFile(D_86B0E5E4, 0);
    }

    MessageBank_Init();
    D_86B0E5E0 = GetMessageBank(0x14);
    func_86B0111C();
    func_80007754();
    func_86B0107C();
    func_86B010FC();
    Stage_Terminate();
    FontManager_Free();

    main_pool_pop_state('MINI');

    return gFragment17Result;
}
