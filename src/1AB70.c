#include "1AB70.h"
#include "src/11BA0.h"
#include "src/12D80.h"
#include "src/17300.h"
#include "src/19840.h"
#include "src/1C720.h"
#include "src/1CF30.h"
#include "src/3FB0.h"
#include "src/6BC0.h"
#include "src/F420.h"
#include "src/dp_intro.h"
#include "src/geo_layout.h"
#include "src/memory.h"

static unk_D_86002F58_004_000* gCameraNode;
static s32 gDebugMode;

s32 SetCurrentCameraNode(s32, GraphNode*);
s32 func_80019F70(s32, GraphNode*);

s32 func_80019F70(s32 arg0, GraphNode* arg1) {
    if (arg0 == 0) {
        gAssetManager.unk_A04.unk_0C = arg1;
    }
    return 0;
}

void SpriteDisplay_InitGeoLayout(unk_func_8001A024* arg0, s16 arg1, s16 arg2) {
    static u32 sSpriteGeoLayoutCommands[] = {
        0x0C00FFFF,    0x05000000, 0x0B00001E, 0x00000000, 0x00300030, 0x00000000, 0x0000000A, 0x015404E2, 0x05000000,
        0x0D000000,    0x05000000, 0x14000000, 0x002D0019, 0xFFFFFF32, 0x14000000, 0xFFD300CD, 0x80808032, 0x16646464,
        0x0F000001,    0x05000000, 0x1F000000, 0x00000000, 0x00000000, 0xFF060000, 0x00640064, 0x00640000, 0x08000000,
        func_80019F70, 0x00000000, 0x06000000, 0x06000000, 0x06000000, 0x06000000, 0x01000000, 0x00000000, 0x00000000,
    };

    unk_D_86002F34_00C* sp24;
    MemoryBlock* sp20 = state_pool_try_init(main_pool_get_available(), 0);

    arg0->unk_0C = process_geo_layout(sp20, sSpriteGeoLayoutCommands);
    arg0->unk_10 = gAssetManager.unk_A04.unk_0C;
    mem_pool_resize_block(sp20);
    sp24 = arg0->unk_0C->unk_0C;
    func_80011DAC(sp24, 0, 0, arg1, arg2);
    func_80011E68(sp24, 30.0f, 100.0f, 12800.0f);
}

unk_func_8001A024* SpriteDisplay_Alloc(unk_D_86002F58_004_000_010* arg0, s16 arg1, s16 arg2, s16 arg3) {
    s32 var_s0;
    FramebufferImage* temp_a1;
    s32 i;
    unk_func_8001A024* temp_v0 = main_pool_alloc(sizeof(unk_func_8001A024), 0);

    if (temp_v0 != NULL) {
        temp_v0->unk_00 = 0;
        temp_v0->unk_02 = 0;
        temp_v0->unk_03 = -1;
        temp_v0->unk_01 = arg1;
        temp_v0->unk_08 = main_pool_alloc(arg1 * sizeof(unk_func_8001A024_008), 0);
        temp_v0->unk_04 = arg0;
        temp_v0->unk_14 = NULL;
        temp_v0->unk_18 = D_8006FF00;

        if (arg0 != NULL) {
            temp_v0->unk_14 = FramebufferImage_Allocate(0, 2, arg2, arg3, 1);
        }

        for (i = 0; i < arg1; i++) {
            temp_v0->unk_08[i].unk_00 = 0;
            temp_v0->unk_08[i].unk_14.raw = 0;
            temp_v0->unk_08[i].unk_0C = FramebufferImage_Allocate(0, 2, arg2, arg3, 0);
            bzero(temp_v0->unk_08[i].unk_0C->img_p, arg2 * arg3 * 2);
            if (temp_v0->unk_14 != NULL) {
                FramebufferImage_AttachDepth(temp_v0->unk_08[i].unk_0C, temp_v0->unk_14);
            }
        }

        SpriteDisplay_InitGeoLayout(temp_v0, arg2, arg3);
    }
    return temp_v0;
}

void SpriteDisplay_SetDepthBuffer(unk_func_8001A024* arg0, unk_D_86002F58_004_000_010* arg1, FramebufferImage* arg2) {
    s32 i;

    arg0->unk_04 = arg1;
    arg0->unk_14 = arg2;

    for (i = 0; i < arg0->unk_01; ++i) {
        FramebufferImage_AttachDepth(arg0->unk_08[i].unk_0C, arg2);
    }
}

void SpriteDisplay_SetScaleTable(unk_func_8001A024* arg0, unk_D_8006FF00* arg1) {
    arg0->unk_18 = arg1;
}

void SpriteDisplay_Clear(unk_func_8001A024* arg0) {
    // s32 var_s0;
    s32 i;
    u16 w;
    u16 h;
    unk_func_8001A024_008* tempImg_p;
    FramebufferImage* tempDepth_p;

    if (arg0->unk_00 & 1) {
        func_80019CA8(arg0->unk_04);
        GraphNode_ClearCallback(arg0->unk_10);
    }

    arg0->unk_00 = 0;
    arg0->unk_02 = 0;
    arg0->unk_03 = -1;

    for (i = 0; i < arg0->unk_01; ++i) {
        tempImg_p = &arg0->unk_08[i];
        tempDepth_p = tempImg_p->unk_0C;
        w = tempDepth_p->width;
        h = tempDepth_p->height;
        tempImg_p->unk_00 = 0;
        arg0->unk_08[i].unk_14.raw = 0;
        bzero(arg0->unk_08[i].unk_0C->img_p, w * h * 2);
    }
}

void SpriteDisplay_SetupSlot(unk_func_8001A024* arg0, s32 arg1, s32 arg2, u16 arg3) {
    s32 w;
    s32 h;

    if (arg1 < arg0->unk_01) {
        w = arg0->unk_08[arg1].unk_0C->width;
        h = arg0->unk_08[arg1].unk_0C->height;
        bzero(arg0->unk_08[arg1].unk_0C->img_p, w * h * 2);
    
        if ((arg2 <= 0) || (arg2 >= 0x98)) {
            arg2 = 0x98;
        }
    
        arg0->unk_08[arg1].unk_00 = 1;
        arg0->unk_08[arg1].unk_02 = arg3 & ~1;
        arg0->unk_08[arg1].unk_14.raw = arg2;
        arg0->unk_08[arg1].unk_08 = arg0->unk_18[arg2 - 1].unk_02 / 100.0f;
        arg0->unk_08[arg1].unk_10.raw = 0;
    
        if (arg0->unk_18[arg2 - 1].name == NULL) {
            arg0->unk_08[arg1].unk_04 = arg0->unk_18[arg2 - 1].unk_08 - 0xE38;
        } else {
            arg0->unk_08[arg1].unk_04 = -0xE38;
        }
    }
}

void SpriteDisplay_ConfigSlotWithAnim(unk_func_8001A024* arg0, s32 arg1, unk_func_80026268_arg0* arg2, u16 arg3) { // or u16 arg3
    s32 w;
    s32 h;

    if (arg1 < arg0->unk_01) {
        w = arg0->unk_08[arg1].unk_0C->width;
        h = arg0->unk_08[arg1].unk_0C->height;
        bzero(arg0->unk_08[arg1].unk_0C->img_p, w * h * 2);
        if (((s32) arg2->unk_00.unk_00 > 0) && ((s32) arg2->unk_00.unk_00 < 0x98)) {
            arg0->unk_08[arg1].unk_00 = 3;
            arg0->unk_08[arg1].unk_14.raw = arg2;;
            arg0->unk_08[arg1].unk_02 = arg3 & ~1;
            arg0->unk_08[arg1].unk_08 = arg0->unk_18[arg2->unk_00.unk_00 - 1].unk_02 / 100.0f;
            ComputeStatFromName(&arg0->unk_08[arg1].unk_10, arg2);
            if (arg0->unk_18[arg2->unk_00.unk_00 - 1].name == NULL) {
                arg0->unk_08[arg1].unk_04 = arg0->unk_18[arg2->unk_00.unk_00 - 1].unk_08 - 0xE38;;
                return;
            }
            arg0->unk_08[arg1].unk_04  = -0xE38;
            return;
        }
        arg0->unk_08[arg1].unk_00 = 1;
        arg0->unk_08[arg1].unk_02 = arg3 & ~1;
        arg0->unk_08[arg1].unk_14.raw = 0x98;
        arg0->unk_08[arg1].unk_08 = (f32) ((f32) arg0->unk_18[151].unk_02 / 100.0f);
        arg0->unk_08[arg1].unk_10.raw = 0;
        arg0->unk_08[arg1].unk_04 = -0xE38;
    }
}

void U16Buffer_Transform(u16* arg0, s32 a1, arg1_func_80010CA8 arg2) {
    s32 cond;
    s32 arg1 = a1;

    if (!arg0) {}

    arg1 *= 2;
    osInvalDCache(arg0, arg1);

    cond = arg1 >= 2;
    arg1 -= 2;
    // clang-format off
    while (cond != 0) {        
        *arg0 = func_80010CA8(*arg0, arg2);        cond = arg1 >= 2;        arg1 -= 2;        
        arg0++;    
    }
    // clang-format on
}

void SpriteImage_Transform(FramebufferImage* arg0, arg1_func_80010CA8 arg1) {
    s32 size = arg0->width * arg0->height;

    U16Buffer_Transform(arg0->img_p, size, arg1);
}

void SpriteDisplay_RenderSlot(unk_func_8001A024* arg0, s32 arg1) {
    Vec3s sp38;
    unk_D_86002F34_00C* sp34;
    unk_func_8001A024_008* temp_s1;
    unk_D_86002F58_004_000_004* sp2C;

    sp34 = arg0->unk_0C->unk_0C;
    temp_s1 = &arg0->unk_08[arg1];
    sp2C = arg0->unk_04->unk_24->unk_08->unk_00[0];

    GraphNode_ClearCallback(arg0->unk_10);
    func_800173CC(arg0->unk_10);

    if (temp_s1->unk_00 & 2) {
        sp38.x = (s16)(arg0->unk_18[*temp_s1->unk_14.ptr - 1].unk_14 >> 0x10) >> 6;
        sp38.y = (s16)(arg0->unk_18[*temp_s1->unk_14.ptr - 1].unk_14 >> 6) >> 4;
        sp38.z = (s16)(arg0->unk_18[*temp_s1->unk_14.ptr - 1].unk_14 << 6) >> 6;
        GraphNode_InitChild(arg0->unk_10, 0, *temp_s1->unk_14.ptr, sp2C);
        GraphNode_TriggerAction(arg0->unk_10, 1);
        func_80017464(arg0->unk_10, arg0->unk_18[*temp_s1->unk_14.ptr - 1].unk_01);
    } else {
        sp38.x = (s16)(arg0->unk_18[temp_s1->unk_14.raw - 1].unk_14 >> 0x10) >> 6;
        sp38.y = (s16)(arg0->unk_18[temp_s1->unk_14.raw - 1].unk_14 >> 6) >> 4;
        sp38.z = (s16)(arg0->unk_18[temp_s1->unk_14.raw - 1].unk_14 << 6) >> 6;
        GraphNode_InitChild(arg0->unk_10, 0, temp_s1->unk_14.unk_02, sp2C);
        GraphNode_TriggerAction(arg0->unk_10, 1);
        func_80017464(arg0->unk_10, arg0->unk_18[temp_s1->unk_14.raw - 1].unk_01);
    }
    func_8000E990(&arg0->unk_10->unk_024, &sp38);
    arg0->unk_10->unk_000.unk_02 &= ~0x40;
    arg0->unk_10->unk_000.unk_02 |= 0x80;
    Vec3f_Set(&arg0->unk_10->unk_030, temp_s1->unk_08, temp_s1->unk_08, temp_s1->unk_08);
    func_80010354(&sp34->unk_60.at, &sp34->unk_60.eye, 1250.0f, 0x71C, temp_s1->unk_04);
    Gfx_SetupFrameBuffer(&gDisplayListHead, arg0->unk_08[arg1].unk_0C);
    func_80015348();
    func_8001533C(3);
    Graph_SetTextureState(arg0->unk_0C);
    Gfx_FillScreen(&gDisplayListHead, arg0->unk_08[arg1].unk_02);
    func_8001533C(1);
    Graph_SetTextureState(arg0->unk_0C);
}

s32 SpriteDisplay_TryAdvance(unk_func_8001A024* arg0, s32 arg1) {
    s32 i;
    s32 var_v0;
    s32 sp24;
    s32 sp20;
    unk_func_8001A024_008* temp_v0_2;

    sp24 = -1;
    sp20 = arg0->unk_02;
    if (arg0->unk_00 & 1) {
        if (arg1 == 1) {
            var_v0 = func_80019CA8(arg0->unk_04);
        } else {
            var_v0 = func_80019C08(arg0->unk_04);
        }
        if (var_v0 != 0) {
            arg0->unk_00 &= 0xFFFE;
            arg0->unk_08[sp20].unk_00 &= 0xFFFE;
            SpriteDisplay_RenderSlot(arg0, sp20);
            arg0->unk_03 = sp20;
            sp24 = sp20;
            arg0->unk_02++;
            if (arg0->unk_02 >= arg0->unk_01) {
                arg0->unk_02 = 0;
            }
        }
    } else {
        for (i = 0; i < arg0->unk_01; i++) {
            temp_v0_2 = &arg0->unk_08[sp20];
            if (temp_v0_2->unk_00 & 1) {
                arg0->unk_00 |= 1;
                if (temp_v0_2->unk_00 & 2) {
                    func_800198E4(arg0->unk_04, *temp_v0_2->unk_14.ptr, temp_v0_2->unk_10);
                } else {
                    func_800198E4(arg0->unk_04, temp_v0_2->unk_14.unk_02, temp_v0_2->unk_10);
                }
                arg0->unk_02 = sp20;
                break;
            } else {
                sp20 += 1;
                if (sp20 >= arg0->unk_01) {
                    sp20 = 0;
                }
            }
        }
    }
    return sp24;
}

s32 func_8001ABAC(unk_func_8001A024* arg0, s32 arg1) {
    UNUSED s32 pad;
    arg1_func_80010CA8 sp48;
    s32 sp44;
    s32 var_s1;
    unk_func_8001A024_008* temp_s0;
    unk_func_8001A024_008* temp_s1;
    s32 i;

    sp44 = -1;
    var_s1 = arg0->unk_02;
    if (arg0->unk_03 >= 0) {
        temp_s0 = &arg0->unk_08[arg0->unk_03];
        if (temp_s0->unk_00 & 4) {
            while (func_80001C90() == 0) {}
            SpriteImage_Transform(temp_s0->unk_0C, temp_s0->unk_10);
            temp_s0->unk_00 &= ~4;
        }
    }

    for (i = 0; i < arg0->unk_01; i++) {
        temp_s1 = &arg0->unk_08[var_s1];
        if (temp_s1->unk_00 & 1) {
            if (func_80001C90() == 0) {
                do { } while (func_80001C90() == 0); }

            sp48.raw = 0;
            if (temp_s1->unk_00 & 2) {
                func_800198E4(arg0->unk_04, *temp_s1->unk_14.ptr, sp48);
                if (temp_s1->unk_10.raw != 0) {
                    temp_s1->unk_00 |= 4;
                }
            } else {
                func_800198E4(arg0->unk_04, temp_s1->unk_14.unk_02, sp48);
            }

            func_80019CA8(arg0->unk_04);
            arg0->unk_08[var_s1].unk_00 &= ~1;
            SpriteDisplay_RenderSlot(arg0, var_s1);
            sp44 = var_s1;
            arg0->unk_02 = var_s1;
            arg0->unk_03 = var_s1;
            arg0->unk_02++;
            if (arg0->unk_02 >= arg0->unk_01) {
                arg0->unk_02 = 0;
            }
            break;
        }

        var_s1 += 1;
        if (var_s1 >= arg0->unk_01) {
            var_s1 = 0;
        }
    }

    return sp44;
}

s32 func_8001AD90(unk_func_8001A024* arg0, s32 arg1) {
    s32 i;
    s32 var_a2;
    s32 var_s0;
    unk_func_8001A024_008* temp_a0;
    unk_func_8001A024_008* temp_s1;
    
    var_a2 = -1;
    var_s0 = arg0->unk_02;
    temp_a0 = arg0->unk_08;
    
    for (i = 0; i < arg0->unk_01; i++) {
        temp_s1 = &arg0->unk_08[var_s0];
        if (temp_s1->unk_00 & 1) {
            while (func_80001C90() == 0) {}
            
            if (temp_s1->unk_00 & 2) {
                func_800198E4(arg0->unk_04, *temp_s1->unk_14.ptr, temp_s1->unk_10);
            } else {
                func_800198E4(arg0->unk_04, temp_s1->unk_14.unk_02, temp_s1->unk_10);
            }
            func_80019CA8(arg0->unk_04);
            arg0->unk_08[var_s0].unk_00 &= ~1;
            SpriteDisplay_RenderSlot(arg0, var_s0);
            arg0->unk_02 = var_s0;
            var_a2 = var_s0;
            arg0->unk_02++;
            arg0->unk_03 = var_s0;
            if (arg0->unk_02 >= arg0->unk_01) {
                arg0->unk_02 = 0;
            }
            break;
        } else {
            var_s0 += 1;
            if (var_s0 >= arg0->unk_01) {
                var_s0 = 0;
            }
        }
    }
    return var_a2;
}

void SpriteDisplay_SetCurrentSlotFramebuffer(unk_func_8001A024* arg0, s32 arg1) {
    s32 i;

    if (arg1 == arg0->unk_03) {
        Gfx_SetupFrameBuffer(&gDisplayListHead, arg0->unk_08[arg1].unk_0C);
        Gfx_FillScreen(&gDisplayListHead, arg0->unk_08[arg1].unk_02);
        func_8001533C(1);
        Graph_SetTextureState(arg0->unk_0C);
        return;
    }
    for (i = arg0->unk_01; i > 0; i--) {
        if (arg0->unk_08[i - 1].unk_00 & 1) {
            break;
        }
    }
    if (i == 0) {
        arg0->unk_08[arg1].unk_00 |= 1;
    }
}

u8* SpriteDisplay_GetImagePtr(unk_func_8001A024* arg0, s32 arg1) {
    u8* image;
    image = NULL;
    if (arg1 < (s32)arg0->unk_01) {
        image = arg0->unk_08[arg1].unk_0C->img_p;
    }
    return image;
}

s32 func_8001B010(unk_func_8001A024* arg0) {
    s32 i;
    
    for (i = 0; i < arg0->unk_01; i++) {
        if (arg0->unk_08[i].unk_00 & 5) {
            return 0;
        }
    }
    return 1;
}

void SpriteAssets_Load(void) {
    gAssetManager.unk_A04.unk_10 = Asset_Load2(0x820000, NULL, 1, 1);
}

void func_8001B088(u16* arg0, s32 arg1) {
    BinArchive* temp_v1;
    u8* temp_a1;

    if ((arg1 > 0) && (arg1 < 0x99)) {
        temp_v1 = gAssetManager.unk_A04.unk_10;
        temp_a1 = temp_v1->unk_04 + temp_v1[arg1].raw;
        func_80003B30(arg0, temp_a1, temp_v1[arg1].unk_04 + temp_a1, 0);
    }
}

void func_8001B0DC(u16* arg0, s32 arg1, unk_func_80026268_arg0* arg2) {
    arg1_func_80010CA8 sp1C;

    if (arg2 == NULL) {
        func_8001B088(arg0, arg1);
        return;
    }

    ComputeStatFromName(&sp1C, arg2);
    func_8001B088(arg0, arg2->unk_00.unk_00);
    U16Buffer_Transform(arg0, 0x640, sp1C);
}

s32 SetCurrentCameraNode(s32 arg0, GraphNode* arg1) {
    if (arg0 == 0) {
        gCameraNode = arg1;
    }
    return 0;
}

void func_8001B154(unk_func_8001B1FC* arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4) {
    static u32 D_8006F3E0[] = {
        0x0C00FFFF,    0x05000000, 0x0B00001E, 0x00000000, 0x010000E0, 0x00000000, 0x0000000A, 0x015404E2, 0x05000000,
        0x0D000000,    0x05000000, 0x14000000, 0x002D013B, 0xFFFFFF32, 0x14000000, 0xFFD30087, 0x80808032, 0x16646464,
        0x0F000001,    0x05000000, 0x1F000000, 0x00000000, 0x00000000, 0xFF060000, 0x00640064, 0x00640000, 0x08000000,
        SetCurrentCameraNode, 0x00000000, 0x06000000, 0x06000000, 0x06000000, 0x06000000, 0x01000000, 0x00000000, 0x00000000,
    };
    MemoryBlock* sp24;
    MemoryBlock* temp_v0;

    sp24 = state_pool_try_init(main_pool_get_available(), 0);
    arg0->unk_20 = process_geo_layout(sp24, D_8006F3E0);
    arg0->unk_24 = gCameraNode;
    mem_pool_resize_block(sp24);
    func_80011DAC(arg0->unk_20->unk_0C, arg1, arg2, arg3, arg4);
    func_80011E68(arg0->unk_20->unk_0C, 30.0f, 100.0f, 12800.0f);
}

unk_func_8001B1FC* func_8001B1FC(unk_D_86002F58_004_000_010* arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5,
                                 s16 arg6, u8* arg7) {
    unk_func_8001B1FC* temp_v0 = main_pool_alloc(sizeof(unk_func_8001B1FC), 0);

    if (temp_v0 != NULL) {
        temp_v0->unk_00 = 6;
        temp_v0->unk_1C = arg0;
        temp_v0->unk_14 = 0;
        temp_v0->unk_04 = arg1;
        temp_v0->unk_06 = arg2;
        temp_v0->unk_08 = arg5;
        temp_v0->unk_0A = arg6;
        temp_v0->unk_0C = arg7;
        temp_v0->unk_28 = FramebufferImage_Allocate(0, 2, arg1, arg2, 0);
        temp_v0->unk_2C = FramebufferImage_Allocate(0, 2, arg1, arg2, 1);
        FramebufferImage_AttachDepth(temp_v0->unk_28, temp_v0->unk_2C);
        func_8001B154(temp_v0, arg3, arg4, arg5, arg6);
    }
    return temp_v0;
}

void func_8001B2D8(unk_func_8001B1FC* arg0, unk_func_80026268_arg0* arg1, u16 arg2) {
    arg1_func_80010CA8 sp2C;
    s16 tmp1 = (s16)(D_8006FF00[arg1->unk_00.unk_00 - 1].unk_14 >> 0x10) >> 6;
    s16 tmp2 = (s16)(D_8006FF00[arg1->unk_00.unk_00 - 1].unk_14 >> 6) >> 4;
    s16 tmp3 = (s16)(D_8006FF00[arg1->unk_00.unk_00 - 1].unk_14 << 6) >> 6;

    arg0->unk_00 |= 1;
    arg0->unk_14 = arg1;
    arg0->unk_12 = 0x100;
    arg0->unk_10 = 0;
    arg0->unk_02 = arg2;
    arg0->unk_18 = D_8006FF00[arg1->unk_00.unk_00 - 1].unk_02 / 100.0f;

    arg0->unk_24->unk_024.x = tmp1;
    arg0->unk_24->unk_024.y = tmp2;
    arg0->unk_24->unk_024.z = tmp3;

    arg0->unk_24->unk_01E = D_8006F05C;
    ComputeStatFromName(&sp2C, arg1);
    func_800198E4(arg0->unk_1C, arg1->unk_00.unk_00, sp2C);
    func_80019CA8(arg0->unk_1C);
    GraphNode_ClearCallback(arg0->unk_24);
    GraphNode_InitChild(arg0->unk_24, 0, arg1->unk_00.unk_00, arg0->unk_1C->unk_24->unk_08->unk_00[0]);
    GraphNode_TriggerAction(arg0->unk_24, 1);
    arg0->unk_24->unk_000.unk_02 &= ~0x40;
    arg0->unk_24->unk_000.unk_02 |= 0x80;
}

void func_8001B480(unk_func_8001B1FC* arg0, s32 arg1, u16 arg2) {
    arg1_func_80010CA8 sp34;
    s16 tmp1 = (s16)(D_8006FF00[arg1 - 1].unk_14 >> 0x10) >> 6;
    s16 tmp2 = (s16)(D_8006FF00[arg1 - 1].unk_14 >> 6) >> 4;
    s16 tmp3 = (s16)(D_8006FF00[arg1 - 1].unk_14 << 6) >> 6;

    arg0->unk_00 &= ~1;
    arg0->unk_14 = arg1;
    arg0->unk_12 = 0x100;
    arg0->unk_10 = 0;
    arg0->unk_02 = arg2;
    arg0->unk_18 = D_8006FF00[arg1 - 1].unk_02 / 100.0f;

    arg0->unk_24->unk_024.x = tmp1;
    arg0->unk_24->unk_024.y = tmp2;
    arg0->unk_24->unk_024.z = tmp3;

    arg0->unk_24->unk_01E = D_8006F05C;
    sp34.raw = 0;
    func_800198E4(arg0->unk_1C, arg1, sp34);
    func_80019CA8(arg0->unk_1C);
    GraphNode_ClearCallback(arg0->unk_24);
    GraphNode_InitChild(arg0->unk_24, 0, arg1, arg0->unk_1C->unk_24->unk_08->unk_00[0]);
    GraphNode_TriggerAction(arg0->unk_24, 1);
    arg0->unk_24->unk_000.unk_02 &= ~0x40;
    arg0->unk_24->unk_000.unk_02 |= 0x80;
}

s32 func_8001B610(Vec3s* arg0) {
    s32 var_v1 = 0;

    if (gPlayer1Controller->buttonDown & 0x800) {
        var_v1 = 1;
        arg0->x += 0x400;
    }

    if (gPlayer1Controller->buttonDown & 0x400) {
        var_v1 = 1;
        arg0->x -= 0x400;
    }

    if (gPlayer1Controller->buttonDown & 0x200) {
        var_v1 = 1;
        arg0->y += 0x400;
    }

    if (gPlayer1Controller->buttonDown & 0x100) {
        var_v1 = 1;
        arg0->y -= 0x400;
    }

    return var_v1;
}

s32 func_8001B6BC(Vec3s* arg0) {
    return 0;
}

void func_8001B6C8(unk_func_8001B1FC* arg0) {
    s32 var_a0;
    Vec3s* sp18 = &arg0->unk_24->unk_01E;
    s16 var_a2;
    s16 temp_lo;

    if (arg0->unk_12 < 0x100) {
        arg0->unk_12 += 0x10;
    }
    sp18->y += arg0->unk_12;
    var_a2 = arg0->unk_12;

    if (sp18->x < 0) {
        var_a0 = -sp18->x;
    } else {
        var_a0 = sp18->x;
    }

    temp_lo = var_a0 / 12;
    if (temp_lo < 8) {
        temp_lo = 8;
    }

    if (temp_lo < var_a2) {
        var_a2 = temp_lo;
    }
    sp18->x = func_800103F0(sp18->x, 0, var_a2);
}

void func_8001B778(unk_func_8001B1FC* arg0) {
    f32 temp_fv0;
    s16 temp_v0_2;
    s32 temp_v0;
    s32 var_v1;

    var_v1 = 0;
    if (arg0->unk_00 & 2) {
        var_v1 = func_8001B610(&arg0->unk_24->unk_01E);
        if (var_v1 == 0) {
            var_v1 = func_8001B6BC(&arg0->unk_24->unk_01E);
        }
    }

    if (var_v1 != 0) {
        arg0->unk_12 = 0;
        arg0->unk_10 = 0x78;
    } else if (arg0->unk_00 & 4) {
        if (arg0->unk_10 > 0) {
            arg0->unk_10--;
        } else {
            func_8001B6C8(arg0);
        }
    }

    Vec3f_Set(&gCameraNode->unk_030, arg0->unk_18, arg0->unk_18, arg0->unk_18);
}

void func_8001B834(unk_func_8001B1FC* arg0) {
    s32 var_v0;
    s32 var_s2;
    s32 i;

    if (arg0->unk_0C == 0) {
        Gfx_FillScreen(&gDisplayListHead, arg0->unk_02);
        return;
    }

    var_s2 = arg0->unk_0C;

    gDPPipeSync(gDisplayListHead++);
    gDPSetCycleType(gDisplayListHead++, G_CYC_COPY);
    gDPSetRenderMode(gDisplayListHead++, G_RM_NOOP, G_RM_NOOP2);
    gDPSetTexturePersp(gDisplayListHead++, G_TP_NONE);

    for (i = 0; i < arg0->unk_0A; i += 8) {
        var_v0 = arg0->unk_0A - i;
        if (var_v0 >= 9) {
            var_v0 = 8;
        }
        Gfx_DrawSpriteRGBA16(0, i, arg0->unk_08, var_v0, var_s2, arg0->unk_04, 0x200000);
        var_s2 += arg0->unk_04 * 0x10;
    }

    gDPPipeSync(gDisplayListHead++);
    gDPSetTexturePersp(gDisplayListHead++, G_TP_PERSP);

    Gfx_FillDepthRectangle(&gDisplayListHead, 0, 0, arg0->unk_08, arg0->unk_0A);
}

u8* func_8001B9D4(unk_func_8001B1FC* arg0) {
    func_8001B778(arg0);
    Gfx_SetupFrameBuffer(&gDisplayListHead, arg0->unk_28);
    func_8001B834(arg0);
    func_80015348();
    Graph_SetTextureState(arg0->unk_20);

    if (gDebugMode > 0) {
        Text_ResetState();
        Text_SetFont(8, -4);

        switch (gDebugMode) {
            case 1:
                Text_Print(0, 0x64, "S:%5.2f  H:%4d", arg0->unk_18, (s32)arg0->unk_24->unk_024.y);
                break;

            case 2:
                Text_Print(0, 0x64, "X:%4d  Z:%4d", (s32)arg0->unk_24->unk_024.x, (s32)arg0->unk_24->unk_024.z);
                break;

            case 3:
                Text_Print(0, 0x64, "A:%04X  F:%3d", *(u16*)&arg0->unk_24->unk_01E.y,
                              arg0->unk_24->unk_040.unk_08 >> 0x10);
                break;
        }
        Text_SetupDL();
    }
    return arg0->unk_28->img_p;
}
