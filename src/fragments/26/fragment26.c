#include "fragment26.h"
#include "src/1CF30.h"
#include "src/20330.h"
#include "src/22630.h"
#include "src/2D340.h"
#include "src/2E110.h"
#include "src/2E460.h"
#include "src/49790.h"
#include "src/memmap.h"
#include "src/memory.h"
#include "src/232C0.h"

static Color_RGBA8 gDefaultColor = { 0xF0, 0xF0, 0xF0, 0xFF };

void DrawTiledTextureRect(unk_func_88500020* arg0, s32 arg1, s32 arg2) {
    s32 temp_lo = 0x1000 / (arg0->unk_00 * 2);
    s32 var_t3 = arg0->unk_04;
    u8* var_s2 = arg0->unk_0C;
    s32 var_s3 = arg2;
    s32 var_t0;

    while (var_t3 > 0) {
        if (temp_lo < var_t3) {
            var_t0 = temp_lo;
        } else {
            var_t0 = var_t3;
        }

        gDPLoadTextureBlock(gDisplayListHead++, var_s2, G_IM_FMT_RGBA, G_IM_SIZ_16b, arg0->unk_00, var_t0, 0,
                            G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                            G_TX_NOLOD);

        gSPTextureRectangle(gDisplayListHead++, arg1 << 2, var_s3 << 2, ((arg0->unk_08 + arg1) - 1) << 2,
                            ((var_s3 + var_t0) - 1) << 2, G_TX_RENDERTILE, 0, 0, 0x1000, 0x0400);

        var_s3 += var_t0;
        var_s2 += var_t0 * arg0->unk_00 * 2;
        var_t3 -= var_t0;
    }
}

void DrawTiledTextureRectWithFormat(unk_func_88500020* arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 temp_lo = 0x1000 / (arg0->unk_00 * 2);
    s32 var_t0;
    s32 var_t3 = arg0->unk_04;
    u8* var_s2 = arg0->unk_0C;
    s32 var_s3 = arg3;

    while (var_t3 > 0) {
        if (temp_lo < var_t3) {
            var_t0 = temp_lo;
        } else {
            var_t0 = var_t3;
        }

        gDPLoadTextureBlock(gDisplayListHead++, var_s2, arg1, G_IM_SIZ_16b, arg0->unk_00, var_t0, 0,
                            G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                            G_TX_NOLOD);
        gSPTextureRectangle(gDisplayListHead++, arg2 << 2, var_s3 << 2, (arg0->unk_08 + arg2) << 2,
                            (var_s3 + var_t0) << 2, G_TX_RENDERTILE, 0, 0, 0x0400, 0x0400);

        var_s3 += var_t0;
        var_s2 += var_t0 * arg0->unk_00 * 2;
        var_t3 -= var_t0;
    }
}

void ListNode_Init(unk_func_88001300_000_000* arg0, s32 arg1) {
    arg0->unk_00 = arg1;
    arg0->unk_04 = NULL;
    arg0->unk_08 = NULL;
    arg0->unk_0C = NULL;
}

void ListNode_AddChild(unk_func_88001300_000_000* arg0, unk_func_88001300_000_000* arg1) {
    arg1->unk_08 = arg0->unk_04;
    arg0->unk_04 = arg1;
}

void Fragment_SetChild(unk_func_88001300_000_000* arg0, unk_func_88001300_000_000* arg1) {
    unk_func_88001300_000_000* var_a0;
    unk_func_88001300_000_000* var_v1;

    if (arg0->unk_04 == NULL) {
        arg0->unk_04 = arg1;
        return;
    }

    var_v1 = arg0->unk_04;
    var_a0 = arg0->unk_04->unk_08;

    while (var_a0 != NULL) {
        var_v1 = var_a0;
        var_a0 = var_a0->unk_08;
    }

    var_v1->unk_08 = arg1;
}

void ListNode_FreeRecursive(unk_func_88001300_000_000* arg0, MemoryPool* arg1) {
    unk_func_88001300_000_000* temp_s1;
    unk_func_88001300_000_000* var_s0 = arg0->unk_04;

    while (var_s0 != NULL) {
        ListNode_FreeRecursive(var_s0, arg1);
        if (var_s0->unk_0C != NULL) {
            var_s0->unk_0C(var_s0, arg1);
        }
        temp_s1 = var_s0->unk_08;
        mem_pool_free(arg1, var_s0);
        var_s0 = temp_s1;
    }
    arg0->unk_04 = NULL;
}

void ListNode_DestroyRecursive(unk_func_88001300_000_000* arg0, MemoryPool* arg1) {
    unk_func_88001300_000_000* temp_s1;
    unk_func_88001300_000_000* var_s0 = arg0->unk_04;

    while (var_s0 != NULL) {
        temp_s1 = var_s0->unk_08;
        ListNode_DestroyRecursive(var_s0, arg1);
        var_s0 = temp_s1;
    }

    if (arg0->unk_0C != NULL) {
        arg0->unk_0C(arg0, arg1);
    }
    mem_pool_free(arg1, arg0);
}

void func_885007CC(unk_func_88001300_000* arg0, s32 arg1) {
    ListNode_Init(&arg0->unk_00, arg1);
    arg0->unk_10.unk_00 = 0;
    arg0->unk_10.unk_02 = 0;
    arg0->unk_14.unk_00 = 0x10;
    arg0->unk_14.unk_02 = 0x10;
    arg0->unk_18 = NULL;
    arg0->unk_1C = NULL;
    arg0->unk_20 = NULL;
    arg0->unk_24 = UIElement_SetState;
    arg0->unk_28 = 1;
    arg0->unk_2A = 0;
}

void TextObject_PostRender(unk_func_88001300_000* arg0, s32 arg1, s32 arg2) {
    s32 var_v1 = 0;
    unk_func_88001300_000_000* var_s0;

    if (arg0->unk_28 & 1) {
        arg1 += arg0->unk_10.unk_00;
        arg2 += arg0->unk_10.unk_02;

        if (arg0->unk_18 != NULL) {
            var_v1 = arg0->unk_18(arg0, arg1, arg2);
        }

        if (var_v1 == 0) {
            var_s0 = arg0->unk_00.unk_04;
            while (var_s0 != NULL) {
                TextObject_PostRender(var_s0, arg1, arg2);
                var_s0 = var_s0->unk_08;
            }
        }
    }
}

void TextObject_Render(unk_func_88001300_000* arg0) {
    s32 var_v1 = 0;
    unk_func_88001300_000_000* var_s0;

    if (arg0->unk_28 & 1) {
        if (arg0->unk_1C != NULL) {
            var_v1 = arg0->unk_1C(arg0);
        }

        if (var_v1 == 0) {
            var_s0 = arg0->unk_00.unk_04;
            while (var_s0 != NULL) {
                TextObject_Render(var_s0);
                var_s0 = var_s0->unk_08;
            }
        }
    }
}

void UIElement_SetState(unk_func_88001300_000* arg0, s32 arg1) {
    unk_func_88001300_000* var_s0 = arg0->unk_00.unk_04;

    arg0->unk_2A = arg1;

    while (var_s0 != NULL) {
        var_s0->unk_24(var_s0, arg1);
        var_s0 = var_s0->unk_00.unk_08;
    }
}

void func_88500994(unk_func_88500994* arg0, s32 arg1, s32 arg2) {
    func_885007CC(&arg0->unk_00, sizeof(unk_func_88500994));
    arg0->unk_00.unk_18 = UIContainer_HandleInput;
    arg0->unk_00.unk_10.unk_00 = arg1;
    arg0->unk_00.unk_10.unk_02 = arg2;
    arg0->unk_2C = 0;
    arg0->unk_30 = 0;
}

s32 UIContainer_HandleInput(unk_func_88500994* arg0, s32 arg1, s32 arg2) {
    s32 i;
    unk_func_88001300_000_000* var_a0;

    if (arg0->unk_30 > 0) {
        var_a0 = arg0->unk_00.unk_00.unk_04;

        for (i = 0; i < arg0->unk_2C; i++) {
            var_a0 = var_a0->unk_08;
        }
        TextObject_PostRender(var_a0, arg1, arg2);
    }
    return 1;
}

void Fragment_AddToParent(unk_func_88500994* arg0, unk_func_88001300_000* arg1) {
    Fragment_SetChild(&arg0->unk_00.unk_00, &arg1->unk_00);
    arg0->unk_30++;
}

void UIContainer_SetChildCount(unk_func_88500994* arg0, s32 arg1) {
    arg0->unk_2C = arg1;
}

// Score 2991 (was 3031). Stack layout now matches the target exactly (sp88 at 0x88, y at 0x90, CSE temp
// arg0+arg2 at 0x34, arg0 spilled to its home 0x98); needs 4 decls in this order - dropping sp34 shrinks
// the frame to 0x40. Remaining diff is pure register allocation: target colours the two sums with
// temporaries (t8/v0, spilled right away) so the gfx constants get s2/s3 and the scissor _g lives in s1;
// ours gives the sums s4/s2 and hoists the addu's. Tried, no change (identical code): gDPSetScissor
// instead of ScissorFrac, u8* arg4, swapped sp88/sp34 statements, decl order of x/sp34, reversed
// compares, for-init forms, y = arg1 before loop. Worse: sums assigned before the scissor (7047),
// scissor using the vars (3549), loop bounds as expressions (3549/3919), sp34 recomputed in outer
// loop (3091), if (1) {} in loops (5326/6149), assignment-in-argument (3664). Good permuter candidate.
// Round 8 (agent-6): without a compiler temp the frame collapses to 0x40 (the _g slots only exist because
// the arg0+arg2 temp at 0x34 is numbered after every local), so the temp must stay. In the target the sums
// are evaluated inside the scissor in t8/v0 (t8 stored straight to 0x34, never in an s-reg; v0 also feeds
// the y guard and sp88's home) and the scissor _g gets s1; ours gives the sums s4/s2 and _g v0. Dead ends
// (identical or worse): s16/u16 params (callee then sign-extends), commuted sums in the scissor and/or
// statements, u32 sp34/sp88, sp34 declared in a block / in the outer loop / in a for-init, while and
// do-while loops, arg4 += in the for-increment, sp88 > y, x = arg0 / y = arg1 used by the scissor and
// arg2 += arg0 (both drop the temp: frame 0x40), sp34 = arg2; sp34 += arg0, const locals for 0x20 or
// a "+ k" (k = 0) on the sums (frame grows, same regs), sp88 assigned before the scissor and used by it (2802
// but the temp moves to 0x30).
void DrawTiledBackground(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4)
{
  s32 sp34;
  s32 y;
  s32 x;
  s32 sp88;
  y += 0;
  gDPPipeSync(gDisplayListHead++);
  gDPSetCycleType(gDisplayListHead++, 0 << 20);
  gDPSetRenderMode(gDisplayListHead++, (((((0 | 0x4000) | 0) | (0 << 30)) | (3 << 26)) | (0 << 22)) | (2 << 18), (((((0 | 0x4000) | 0) | (0 << 28)) | (3 << 24)) | (0 << 20)) | (2 << 16));
  gDPSetTexturePersp(gDisplayListHead++, 0 << 19);
  gDPSetTextureFilter(gDisplayListHead++, 0 << 12);
  x = arg1 + arg3;
  gDPSetCombineMode(gDisplayListHead++, G_CC_DECALRGBA, G_CC_DECALRGBA);
  gDPSetRenderMode(gDisplayListHead++, (((((0 | 0x4000) | 0) | (0 << 30)) | (3 << 26)) | (0 << 22)) | (2 << 18), (((((0 | 0x4000) | 0) | (0 << 28)) | (3 << 24)) | (0 << 20)) | (2 << 16));
  gDPSetScissorFrac(gDisplayListHead++, 0, arg0 * 4.0f, arg1 * 4.0f, (arg0 + arg2) * 4.0f, (arg1 + arg3) * 4.0f);
  sp88 = x;
  sp34 = arg0 + arg2;
  for (y = arg1; y < sp88; y += 0x20)
  {
    for (x = arg0; x < sp34; x += 0x20)
    {
      gDPLoadTextureBlock(gDisplayListHead++, arg4, G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 16, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
      gSPTextureRectangle(gDisplayListHead++, x << 2, y << 2, (x + 0x20) << 2, ((((((((((y + 0x20) << 2) & 0xFFFFFFFFu) & 0xFFFFFFFFu) & 0xFFFFFFFFu) & 0xFFFFFFFFu) & 0xFFFFFFFFu) & 0xFFFFFFFFu) & 0xFFFFFFFFu) & 0xFFFFFFFFu) & 0xFFFFFFFFu, G_TX_RENDERTILE, 0, 0, 0x0200, 0x0200);
      arg4 += 0x200;
    }

  }

  gDPPipeSync(gDisplayListHead++);
  gDPSetScissor(gDisplayListHead++, 0, 0, 0, 640, 480);
}

void UITextureRect_Create(unk_func_88500E34* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, u8* arg5) {
    func_885007CC(&arg0->unk_00, sizeof(unk_func_88500E34));
    arg0->unk_00.unk_18 = UITextureRect_Draw;
    arg0->unk_00.unk_10.unk_00 = arg1;
    arg0->unk_00.unk_10.unk_02 = arg2;
    arg0->unk_00.unk_14.unk_00 = arg3;
    arg0->unk_00.unk_14.unk_02 = arg4;
    arg0->unk_2C = arg5;
}

s32 UITextureRect_Draw(unk_func_88500E34* arg0, s32 arg1, s32 arg2) {
    DrawTiledBackground(arg1, arg2, arg0->unk_00.unk_14.unk_00, arg0->unk_00.unk_14.unk_02, arg0->unk_2C);
    return 0;
}

void UIColoredTextureRect_Create(unk_func_88500EE4* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, u8* arg5, Color_RGBA8 arg6,
                   Color_RGBA8 arg7) {
    func_885007CC(&arg0->unk_00, sizeof(unk_func_88500EE4));
    arg0->unk_00.unk_18 = UIColoredTextureRect_Draw;
    arg0->unk_00.unk_10.unk_00 = arg1;
    arg0->unk_00.unk_10.unk_02 = arg2;
    arg0->unk_00.unk_14.unk_00 = arg3;
    arg0->unk_00.unk_14.unk_02 = arg4;
    arg0->unk_2C = arg5;
    arg0->unk_30 = arg6;
    arg0->unk_34 = arg7;
}

s32 UIColoredTextureRect_Draw(unk_func_88500EE4* arg0, s32 arg1, s32 arg2) {
    s32 h = 0x80;
    s32 w = 0x40;

    gDPPipeSync(gDisplayListHead++);

    gDPSetCycleType(gDisplayListHead++, G_CYC_1CYCLE);
    gDPSetRenderMode(gDisplayListHead++, G_RM_OPA_SURF, G_RM_OPA_SURF2);
    gDPSetTexturePersp(gDisplayListHead++, G_TP_NONE);
    gDPSetTextureFilter(gDisplayListHead++, G_TF_POINT);
    gDPSetCombineLERP(gDisplayListHead++, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, 1, PRIMITIVE,
                      ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, 1);
    gDPSetPrimColor(gDisplayListHead++, 0, 0, arg0->unk_30.r, arg0->unk_30.g, arg0->unk_30.b, arg0->unk_30.a);
    gDPSetEnvColor(gDisplayListHead++, arg0->unk_34.r, arg0->unk_34.g, arg0->unk_34.b, arg0->unk_34.a);

    gDPLoadTextureBlock_4b(gDisplayListHead++, arg0->unk_2C, G_IM_FMT_I, h, w, 0, G_TX_NOMIRROR | G_TX_WRAP,
                           G_TX_NOMIRROR | G_TX_WRAP, 7, 6, G_TX_NOLOD, G_TX_NOLOD);

    gSPTextureRectangle(gDisplayListHead++, arg1 << 2, arg2 << 2, ((arg0->unk_00.unk_14.unk_00 + arg1) - 1) << 2,
                        ((arg2 + arg0->unk_00.unk_14.unk_02) - 1) << 2, G_TX_RENDERTILE, 0, 0, 0x0400, 0x0400);

    return 0;
}

void UIFrame_Create(unk_func_885012A4* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, Color_RGBA8 arg5) {
    func_885007CC(&arg0->unk_00, sizeof(unk_func_885012A4));
    arg0->unk_00.unk_18 = UIFillRect_Draw;
    arg0->unk_00.unk_10.unk_00 = arg1;
    arg0->unk_00.unk_10.unk_02 = arg2;
    arg0->unk_00.unk_14.unk_00 = arg3;
    arg0->unk_00.unk_14.unk_02 = arg4;
    arg0->unk_2C = arg5;
}

s32 UIFillRect_Draw(unk_func_885012A4* arg0, s32 arg1, s32 arg2) {
    s32 temp_t1;

    gDPPipeSync(gDisplayListHead++);

    gDPSetCycleType(gDisplayListHead++, G_CYC_FILL);
    gDPSetRenderMode(gDisplayListHead++, G_RM_NOOP, G_RM_NOOP2);

    // clang-format off
    temp_t1 = ((arg0->unk_2C.r << 8) & 0xF800) | ((arg0->unk_2C.g << 3) & 0x7C0) | ((arg0->unk_2C.b >> 2) & 0x3E) | 1; gDPPipeSync(gDisplayListHead++);
    // clang-format on
    gDPSetFillColor(gDisplayListHead++, (temp_t1 << 0x10) | temp_t1);
    gDPFillRectangle(gDisplayListHead++, arg1, arg2, (arg0->unk_00.unk_14.unk_00 + arg1) - 1,
                     (arg2 + arg0->unk_00.unk_14.unk_02) - 1);

    return 0;
}

void UIGradientRect_Create(unk_func_8850143C* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, Color_RGBA8 arg5,
                   Color_RGBA8 arg6) {
    func_885007CC(&arg0->unk_00, sizeof(unk_func_8850143C));
    arg0->unk_00.unk_18 = UIGradientRect_Draw;
    arg0->unk_00.unk_10.unk_00 = arg1;
    arg0->unk_00.unk_10.unk_02 = arg2;
    arg0->unk_00.unk_14.unk_00 = arg3;
    arg0->unk_00.unk_14.unk_02 = arg4;
    arg0->unk_2C = arg5;
    arg0->unk_30 = arg6;
}

s32 UIGradientRect_Draw(unk_func_8850143C* arg0, s32 arg1, s32 arg2) {
    gDPPipeSync(gDisplayListHead++);
    gDPSetCycleType(gDisplayListHead++, G_CYC_1CYCLE);

    if (arg0->unk_2C.a == 0xFF) {
        gDPSetRenderMode(gDisplayListHead++, G_RM_OPA_SURF, G_RM_OPA_SURF2);
    } else {
        gDPSetRenderMode(gDisplayListHead++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
    }

    gDPSetCombineLERP(gDisplayListHead++, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, PRIMITIVE, PRIMITIVE,
                      ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, PRIMITIVE);
    gDPSetTexturePersp(gDisplayListHead++, G_TP_NONE);
    gDPSetTextureFilter(gDisplayListHead++, G_TF_BILERP);

    gDPSetPrimColor(gDisplayListHead++, 0, 0, arg0->unk_2C.r, arg0->unk_2C.g, arg0->unk_2C.b, (0, arg0->unk_2C.a));
    gDPSetEnvColor(gDisplayListHead++, arg0->unk_30.r, arg0->unk_30.g, arg0->unk_30.b, (0, arg0->unk_30.a));

    gDPLoadTextureBlock(gDisplayListHead++, D_4000008, G_IM_FMT_I, G_IM_SIZ_8b, 64, 64, 0, G_TX_NOMIRROR | G_TX_WRAP,
                        G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    gSPTextureRectangle(gDisplayListHead++, arg1 << 2, arg2 << 2, (arg0->unk_00.unk_14.unk_00 + arg1) << 2,
                        (arg2 + arg0->unk_00.unk_14.unk_02) << 2, G_TX_RENDERTILE, 0, 0,
                        0x10000 / arg0->unk_00.unk_14.unk_00, 0x10000 / arg0->unk_00.unk_14.unk_02);

    return 0;
}

void func_8850182C(unk_func_8850182C* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, Color_RGBA8 arg5) {
    func_885007CC(&arg0->unk_00, sizeof(unk_func_8850182C));
    arg0->unk_00.unk_18 = UIButton_Draw;
    arg0->unk_00.unk_10.unk_00 = arg1;
    arg0->unk_00.unk_10.unk_02 = arg2;
    arg0->unk_00.unk_14.unk_00 = arg3;
    arg0->unk_00.unk_14.unk_02 = arg4;
    arg0->unk_2C = arg5;
}

s32 UIButton_Draw(unk_func_8850182C* arg0, s32 arg1, s32 arg2) {
    s32 w = 16;
    s32 h = 8;

    gDPPipeSync(gDisplayListHead++);

    gDPSetCycleType(gDisplayListHead++, G_CYC_1CYCLE);
    gDPSetRenderMode(gDisplayListHead++, G_RM_OPA_SURF, G_RM_OPA_SURF2);
    gDPSetTexturePersp(gDisplayListHead++, G_TP_NONE);
    gDPSetTextureFilter(gDisplayListHead++, G_TF_POINT);
    gDPSetCombineMode(gDisplayListHead++, G_CC_MODULATEI_PRIM, G_CC_MODULATEI_PRIM);
    gDPSetPrimColor(gDisplayListHead++, 0, 0, arg0->unk_2C.r, arg0->unk_2C.g, arg0->unk_2C.b, arg0->unk_2C.a);

    gDPLoadTextureBlock_4b(gDisplayListHead++, D_4007750, G_IM_FMT_I, w, h, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                           G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

    gSPTextureRectangle(gDisplayListHead++, arg1 << 2, arg2 << 2, ((arg0->unk_00.unk_14.unk_00 + arg1) - w) << 2,
                        (arg2 + h) << 2, G_TX_RENDERTILE, 0, 0, 0x0400, 0x0400);

    gDPLoadTextureBlock_4b(gDisplayListHead++, D_4007798, G_IM_FMT_I, w, h, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                           G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

    gSPTextureRectangle(gDisplayListHead++, ((arg0->unk_00.unk_14.unk_00 + arg1) - w) << 2, arg2 << 2,
                        (arg0->unk_00.unk_14.unk_00 + arg1) << 2, ((arg2 + arg0->unk_00.unk_14.unk_02) - h) << 2,
                        G_TX_RENDERTILE, 0, 0, 0x0400, 0x0400);

    gDPLoadTextureBlock_4b(gDisplayListHead++, D_40077E0, G_IM_FMT_I, w, h, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                           G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

    gSPTextureRectangle(gDisplayListHead++, (arg1 + w) << 2, ((arg2 + arg0->unk_00.unk_14.unk_02) - h) << 2,
                        (arg0->unk_00.unk_14.unk_00 + arg1) << 2, (arg2 + arg0->unk_00.unk_14.unk_02) << 2,
                        G_TX_RENDERTILE, (arg0->unk_00.unk_14.unk_00 * -0x20) + 0x400, 0, 0x0400, 0x0400);

    gDPLoadTextureBlock_4b(gDisplayListHead++, D_4007828, G_IM_FMT_I, w, h, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                           G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

    gSPTextureRectangle(gDisplayListHead++, arg1 << 2, (arg2 + h) << 2, (arg1 + w) << 2,
                        (arg2 + arg0->unk_00.unk_14.unk_02) << 2, G_TX_RENDERTILE, 0,
                        (arg0->unk_00.unk_14.unk_02 * -0x20) + 0x200, 0x0400, 0x0400);

    if ((arg0->unk_00.unk_14.unk_00 > 0x20) && (arg0->unk_00.unk_14.unk_02 > 0x10)) {
        gDPPipeSync(gDisplayListHead++);

        gDPSetCycleType(gDisplayListHead++, G_CYC_FILL);
        gDPSetRenderMode(gDisplayListHead++, G_RM_NOOP, G_RM_NOOP2);

        {
            // clang-format off
            s32 temp_a3 = ((arg0->unk_2C.r << 8) & 0xF800) | ((arg0->unk_2C.g << 3) & 0x7C0) | ((arg0->unk_2C.b >> 2) & 0x3E) | 1; gDPPipeSync(gDisplayListHead++);
            // clang-format on
            gDPSetFillColor(gDisplayListHead++, (temp_a3 << 0x10) | temp_a3);
        }

        gDPFillRectangle(gDisplayListHead++, arg1 + w, arg2 + h, ((arg1 + w) + arg0->unk_00.unk_14.unk_00) - 0x21,
                         ((arg2 + h) + arg0->unk_00.unk_14.unk_02) - 0x11);
    }

    return 0;
}

void Fragment_SetRect(unk_func_88001300_038* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    func_885007CC(&arg0->unk_00, sizeof(unk_func_88001300_038));

    arg0->unk_00.unk_18 = UIAnimatedElement_Draw;
    arg0->unk_00.unk_1C = UIAnimatedElement_UpdateState;
    arg0->unk_00.unk_20 = UIAnimatedElement_GetSpeed;

    arg0->unk_00.unk_10.unk_00 = arg1;
    arg0->unk_00.unk_10.unk_02 = arg2;
    arg0->unk_00.unk_14.unk_00 = arg3;
    arg0->unk_00.unk_14.unk_02 = arg4;
    arg0->unk_30 = 0;
    arg0->unk_2C = -1;
    arg0->unk_00.unk_28 |= 0x400;
    arg0->unk_00.unk_28 &= ~1;
}

s32 UIAnimatedElement_UpdateState(unk_func_88001300_038* arg0) {
    arg0->unk_2C++;
    if (arg0->unk_2C < 8) {
        arg0->unk_30 = 1;
        if (arg0->unk_2C == 1) {
            PlaySoundEffect(4);
        }
    } else if (arg0->unk_2C >= 0x14) {
        arg0->unk_2C = -1;
        arg0->unk_30 = 0;
        if (arg0->unk_00.unk_28 & 0x400) {
            arg0->unk_00.unk_28 &= ~1;
        }
    } else if (arg0->unk_2C >= 0xC) {
        arg0->unk_30 = 4;
    } else {
        arg0->unk_30 = 2;
        if (arg0->unk_2C == 0xB) {
            arg0->unk_2C--;
        } else if (arg0->unk_2C < 0xA) {
            arg0->unk_30 |= 8;
        }
    }

    return (arg0->unk_30 & 2) ? 0 : 1;
}

s32 UIAnimatedElement_Draw(unk_func_88001300_038* arg0, s32 arg1, s32 arg2) {
    s32 sp114;
    s32 sp110;
    s32 sp10C;
    s32 sp108;
    s32 val = 0x10;
    s32 temp_a0;
    s32 temp_a1;
    s32 temp_a2;
    s32 temp_t0;
    s32 temp_t2;
    s32 var_v0;
    s32 var_v1_2;
    UNUSED s32 pad;

    if (0) {}

    temp_a1 = arg2 - 7;

    if ((arg0->unk_30 & 0xD) || ((arg0->unk_30 & 2) && (arg0->unk_00.unk_28 & 0x200))) {
        temp_a0 = arg1 - 7;

        var_v0 = arg0->unk_00.unk_14.unk_00 + 0xE;
        var_v1_2 = arg0->unk_00.unk_14.unk_02 + 0xE;

        if (var_v0 < val) {
            var_v0 = val;
        }

        if (var_v1_2 < val) {
            var_v1_2 = val;
        }

        if (arg0->unk_30 & 4) {
            temp_a2 = 0x13 - arg0->unk_2C;

            sp10C = ((var_v0 - val) * temp_a2) / 8;
            sp108 = ((var_v1_2 - val) * temp_a2) / 8;

            sp114 = (((var_v0 - val) - sp10C) / 2) + temp_a0;
            sp110 = (((var_v1_2 - val) - sp108) / 2) + temp_a1;

            // clang-format off
            sp10C += val; sp108 += val;
            // clang-format on
        } else if (arg0->unk_30 & 1) {
            temp_t0 = arg0->unk_2C;

            sp10C = ((var_v0 - val) * temp_t0) / 8;
            sp108 = ((var_v1_2 - val) * temp_t0) / 8;

            sp114 = (((var_v0 - val) - sp10C) / 2) + temp_a0;
            sp110 = (((var_v1_2 - val) - sp108) / 2) + temp_a1;

            // clang-format off
            sp10C += val; sp108 += val;
            // clang-format on
        } else {
            sp114 = temp_a0;
            sp110 = temp_a1;
            sp10C = var_v0;
            sp108 = var_v1_2;
        }

        gDPPipeSync(gDisplayListHead++);
        gDPSetCycleType(gDisplayListHead++, G_CYC_1CYCLE);
        gDPSetRenderMode(gDisplayListHead++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
        gDPSetTexturePersp(gDisplayListHead++, G_TP_NONE);
        gDPSetTextureFilter(gDisplayListHead++, G_TF_POINT);
        gDPSetCombineMode(gDisplayListHead++, G_CC_DECALRGBA, G_CC_DECALRGBA);

        gDPLoadTextureBlock(gDisplayListHead++, D_4006F40, G_IM_FMT_IA, G_IM_SIZ_8b, 8, 8, 0,
                            G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK,
                            G_TX_NOLOD, G_TX_NOLOD);
        gSPTextureRectangle(gDisplayListHead++, sp114 << 2, sp110 << 2, ((sp114 + sp10C) - 8) << 2, (sp110 + 8) << 2,
                            G_TX_RENDERTILE, 0, 0, 0x0400, 0x0400);

        gDPLoadTextureBlock(gDisplayListHead++, D_4006F88, G_IM_FMT_IA, G_IM_SIZ_8b, 8, 8, 0,
                            G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK,
                            G_TX_NOLOD, G_TX_NOLOD);
        gSPTextureRectangle(gDisplayListHead++, ((sp114 + sp10C) - 8) << 2, sp110 << 2, (sp114 + sp10C) << 2,
                            ((sp110 + sp108) - 8) << 2, G_TX_RENDERTILE, 0, 0, 0x0400, 0x0400);

        gDPLoadTextureBlock(gDisplayListHead++, D_4006FD0, G_IM_FMT_IA, G_IM_SIZ_8b, 8, 8, 0,
                            G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK,
                            G_TX_NOLOD, G_TX_NOLOD);
        gSPTextureRectangle(gDisplayListHead++, (sp114 + 8) << 2, ((sp110 + sp108) - 8) << 2, (sp114 + sp10C) << 2,
                            (sp110 + sp108) << 2, G_TX_RENDERTILE, (sp10C * -0x20) + 0x200, 0, 0x0400, 0x0400);

        gDPLoadTextureBlock(gDisplayListHead++, D_4007018, G_IM_FMT_IA, G_IM_SIZ_8b, 8, 8, 0,
                            G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK,
                            G_TX_NOLOD, G_TX_NOLOD);
        gSPTextureRectangle(gDisplayListHead++, sp114 << 2, (sp110 + 8) << 2, (sp114 + 8) << 2, (sp110 + sp108) << 2,
                            G_TX_RENDERTILE, 0, (sp108 * -0x20) + 0x200, 0x0400, 0x0400);
    }

    return (arg0->unk_30 & 2) ? 0 : 1;
}

s32 UIAnimatedElement_GetSpeed(unk_func_88001300_038* arg0, UNUSED Controller* arg1) {
    s32 ret;

    if (arg0->unk_30 & 1) {
        ret = 0x10;
    } else if (arg0->unk_30 & 4) {
        ret = 0x20;
    } else if (arg0->unk_30 & 2) {
        if ((arg0->unk_2C == 0xA) && (arg0->unk_00.unk_28 & 0x100)) {
            arg0->unk_2C = 0xB;
            ret = 0x20;
        } else {
            ret = 4;
        }
    } else {
        ret = 2;
    }

    return ret;
}

void UIAnimatedElement_WaitForInput(unk_func_88001300_038* arg0) {
    if ((arg0->unk_2C >= 0xB) && (arg0->unk_00.unk_28 & 1)) {
        do {
            ControllerMsgQueue_SendAndRead(NULL);
        } while (arg0->unk_00.unk_28 & 1);
    }
    arg0->unk_00.unk_28 |= 1;
}

void UIProgressBar_Create(unk_func_88001300_000* arg0, s32 arg1, s32 arg2, s32 arg3) {
    func_885007CC(arg0, sizeof(unk_func_88001300_000));
    arg0->unk_18 = UIProgressBar_Draw;
    arg0->unk_10.unk_00 = arg1;
    arg0->unk_10.unk_02 = arg2;
    arg0->unk_14.unk_00 = arg3;
    arg0->unk_14.unk_02 = 8;
}

s32 UIProgressBar_Draw(unk_func_88001300_000* arg0, s32 arg1, s32 arg2) {
    s32 sp84;
    s32 sp80;
    s32 sp7C;

    gDPPipeSync(gDisplayListHead++);
    gDPSetCycleType(gDisplayListHead++, G_CYC_1CYCLE);
    gDPSetRenderMode(gDisplayListHead++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
    gDPSetTexturePersp(gDisplayListHead++, G_TP_NONE);
    gDPSetTextureFilter(gDisplayListHead++, G_TF_POINT);
    gDPSetCombineMode(gDisplayListHead++, G_CC_DECALRGBA, G_CC_DECALRGBA);

    // clang-format off
    sp84 = arg1 - 7; sp80 = arg2 - 1; 
    sp7C = arg0->unk_14.unk_00 + 0xE;
    // clang-format on

    gDPLoadTextureBlock(gDisplayListHead++, D_4007060, G_IM_FMT_IA, G_IM_SIZ_8b, 8, 8, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    gSPTextureRectangle(gDisplayListHead++, sp84 << 2, sp80 << 2, ((sp84 + sp7C) - 8) << 2, (sp80 + 8) << 2,
                        G_TX_RENDERTILE, 0, 0, 0x0400, 0x0400);

    gDPLoadTextureBlock(gDisplayListHead++, D_40070A8, G_IM_FMT_IA, G_IM_SIZ_8b, 8, 8, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    gSPTextureRectangle(gDisplayListHead++, ((sp84 + sp7C) - 8) << 2, sp80 << 2, (sp84 + sp7C) << 2, (sp80 + 8) << 2,
                        G_TX_RENDERTILE, 0, 0, 0x0400, 0x0400);

    return 0;
}

void UITimer_Create(unk_func_88001300_02C* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    func_885007CC(&arg0->unk_00, sizeof(unk_func_88001300_02C));
    arg0->unk_00.unk_18 = UITimer_IsReady;
    arg0->unk_00.unk_1C = UITimer_Tick;
    arg0->unk_00.unk_10.unk_00 = arg1;
    arg0->unk_00.unk_10.unk_02 = arg2;
    arg0->unk_00.unk_14.unk_00 = arg3;
    arg0->unk_00.unk_14.unk_02 = arg4;
    arg0->unk_2C = -1;
}

s32 UITimer_IsReady(unk_func_88001300_02C* arg0, s32 arg1, s32 arg2) {
    return (arg0->unk_2C < 3) ? 0 : 1;
}

s32 UITimer_Tick(unk_func_88001300_02C* arg0) {
    s32 var_v1 = 1;

    if (arg0->unk_2C < 0) {
        var_v1 = 0;
    } else if (arg0->unk_2C < 3) {
        arg0->unk_2C++;
        var_v1 = 0;
    }
    return var_v1;
}

void UIElementBase_Create(unk_func_88001300_000* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    func_885007CC(arg0, sizeof(unk_func_88001300_000));
    arg0->unk_18 = UIElementBase_IsVisible;
    arg0->unk_1C = UIElementBase_ResetFlags;
    arg0->unk_10.unk_00 = arg1;
    arg0->unk_10.unk_02 = arg2;
    arg0->unk_14.unk_00 = arg3;
    arg0->unk_14.unk_02 = arg4;
}

s32 UIElementBase_ResetFlags(unk_func_88001300_000* arg0) {
    arg0->unk_28 &= ~0x300;
    return 0;
}

s32 UIElementBase_IsVisible(unk_func_88001300_000* arg0, s32 arg1, s32 arg2) {
    return ((arg0->unk_28 & 0x100) || !(arg0->unk_28 & 0x200)) ? 0 : 1;
}

void Dialog_SetParent(unk_func_88503298* arg0, unk_func_88001300_038* arg1, unk_func_88001300_000* arg2) {
    func_885007CC(&arg0->unk_00, sizeof(unk_func_88503298));
    arg0->unk_00.unk_1C = UIComposite_Update;
    arg0->unk_2C = arg1;
    arg0->unk_30 = arg2;
}

s32 UIComposite_Update(unk_func_88503298* arg0) {
    if (!(arg0->unk_2C->unk_00.unk_28 & 1)) {
        return 0;
    }

    if (arg0->unk_2C->unk_30 & 2) {
        arg0->unk_30->unk_00.unk_28 |= 0x200;
    } else {
        arg0->unk_30->unk_00.unk_28 |= 0x100;
    }

    return 0;
}

void UIFlashingElement_Create(unk_func_88001300_03C_01C* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, Color_RGBA8 arg5) {
    func_885007CC(&arg0->unk_00, sizeof(unk_func_88001300_03C_01C));
    arg0->unk_00.unk_18 = UIFlashingElement_Draw;
    arg0->unk_00.unk_1C = UIFlashingElement_Tick;
    arg0->unk_00.unk_24 = UIFlashingElement_SetState;
    arg0->unk_00.unk_10.unk_00 = arg1;
    arg0->unk_00.unk_10.unk_02 = arg2;
    arg0->unk_00.unk_14.unk_00 = arg3;
    arg0->unk_00.unk_14.unk_02 = arg4;
    arg0->unk_2C = arg5;
    arg0->unk_30 = 0;
}

s32 UIFlashingElement_Tick(unk_func_88001300_03C_01C* arg0) {
    arg0->unk_30++;
    arg0->unk_30 &= 7;
    return 0;
}

s32 UIFlashingElement_Draw(unk_func_88001300_03C_01C* arg0, s32 arg1, s32 arg2) {
    s32 sp104;
    s32 sp100;
    s32 spFC;
    s32 spF8;
    Color_RGBA8 spF4;
    s32 var_v0;

    // clang-format off
    sp104 = arg1 - 3; sp100 = arg2 - 3;
    // clang-format on

    spFC = arg0->unk_00.unk_14.unk_00 + 6;
    spF8 = arg0->unk_00.unk_14.unk_02 + 6;
    spF4 = arg0->unk_2C;

    if (!(arg0->unk_00.unk_2A & 1) && ((arg0->unk_00.unk_28 & 0x100) || !(arg0->unk_00.unk_2A & 0x100))) {
        return 0;
    }

    gDPPipeSync(gDisplayListHead++);
    gDPSetCycleType(gDisplayListHead++, G_CYC_1CYCLE);
    gDPSetRenderMode(gDisplayListHead++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
    gDPSetTexturePersp(gDisplayListHead++, G_TP_NONE);
    gDPSetTextureFilter(gDisplayListHead++, G_TF_POINT);
    gDPSetCombineMode(gDisplayListHead++, G_CC_MODULATEIDECALA_PRIM, G_CC_MODULATEIDECALA_PRIM);

    if (arg0->unk_00.unk_2A & 0x100) {
        spF4.r /= 2;
        spF4.g /= 2;
        spF4.b /= 2;
        var_v0 = 1;
    } else {
        var_v0 = (arg0->unk_30 - 1) & 7;
        if (var_v0 >= 4) {
            var_v0 = 7 - var_v0;
        }
    }

    gDPSetPrimColor(gDisplayListHead++, 0, 0, spF4.r, spF4.g, spF4.b, spF4.a);

    gDPLoadTextureBlock(gDisplayListHead++, D_40070F0, G_IM_FMT_IA, G_IM_SIZ_8b, 8, 8, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    gSPTextureRectangle(gDisplayListHead++, (sp104 + var_v0) << 2, (sp100 + var_v0) << 2,
                        ((((sp104 + var_v0) + spFC) - (var_v0 << 1)) - 8) << 2, ((sp100 + var_v0) + 8) << 2,
                        G_TX_RENDERTILE, 0, 0, 0x0400, 0x0400);

    gDPLoadTextureBlock(gDisplayListHead++, D_4007138, G_IM_FMT_IA, G_IM_SIZ_8b, 8, 8, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    gSPTextureRectangle(gDisplayListHead++, ((((sp104 + var_v0) + spFC) - (var_v0 << 1)) - 8) << 2,
                        (sp100 + var_v0) << 2, (((sp104 + var_v0) + spFC) - (var_v0 << 1)) << 2,
                        ((((sp100 + var_v0) + spF8) - (var_v0 << 1)) - 8) << 2, G_TX_RENDERTILE, 0, 0, 0x0400, 0x0400);

    gDPLoadTextureBlock(gDisplayListHead++, D_4007180, G_IM_FMT_IA, G_IM_SIZ_8b, 8, 8, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    gSPTextureRectangle(
        gDisplayListHead++, ((sp104 + var_v0) + 8) << 2, ((((sp100 + var_v0) + spF8) - (var_v0 << 1)) - 8) << 2,
        (((sp104 + var_v0) + spFC) - (var_v0 << 1)) << 2, (((sp100 + var_v0) + spF8) - (var_v0 << 1)) << 2,
        G_TX_RENDERTILE, ((spFC - (var_v0 << 1)) * -0x20) + 0x200, 0, 0x0400, 0x0400);

    gDPLoadTextureBlock(gDisplayListHead++, D_40071C8, G_IM_FMT_IA, G_IM_SIZ_8b, 8, 8, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    gSPTextureRectangle(gDisplayListHead++, (sp104 + var_v0) << 2, ((sp100 + var_v0) + 8) << 2,
                        ((sp104 + var_v0) + 8) << 2, (((sp100 + var_v0) + spF8) - (var_v0 << 1)) << 2, G_TX_RENDERTILE,
                        0, ((spF8 - (var_v0 << 1)) * -0x20) + 0x200, 0x0400, 0x0400);

    return 0;
}

void UIFlashingElement_SetState(unk_func_88001300_03C_01C* arg0, s32 arg1) {
    arg0->unk_00.unk_2A = arg1;
    arg0->unk_30 = 0;
}

void UIFlashingElementDual_Create(unk_func_88001300_03C_01C* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, Color_RGBA8 arg5) {
    func_885007CC(&arg0->unk_00, sizeof(unk_func_88001300_03C_01C));
    arg0->unk_00.unk_18 = UIFlashingElementDual_Draw;
    arg0->unk_00.unk_1C = UIFlashingElementDual_Tick;
    arg0->unk_00.unk_24 = UIFlashingElementDual_SetState;
    arg0->unk_00.unk_10.unk_00 = arg1;
    arg0->unk_00.unk_10.unk_02 = arg2;
    arg0->unk_00.unk_14.unk_00 = arg3;
    arg0->unk_00.unk_14.unk_02 = arg4;
    arg0->unk_2C = arg5;
    arg0->unk_30 = 0;
}

s32 UIFlashingElementDual_Tick(unk_func_88001300_03C_01C* arg0) {
    arg0->unk_30++;
    arg0->unk_30 &= 7;
    return 0;
}

s32 UIFlashingElementDual_Draw(unk_func_88001300_03C_01C* arg0, s32 arg1, s32 arg2) {
    s32 sp10C;
    s32 sp108;
    s32 sp104;
    s32 sp100;
    Color_RGBA8 spFC;
    s32 var_v0;
    s32 w = 8;
    s32 h = 8;

    sp10C = arg1;
    sp108 = arg2;
    sp104 = arg0->unk_00.unk_14.unk_00;
    sp100 = arg0->unk_00.unk_14.unk_02;
    spFC = arg0->unk_2C;

    if (!(arg0->unk_00.unk_2A & 1) && ((arg0->unk_00.unk_28 & 0x100) || !(arg0->unk_00.unk_2A & 0x100))) {
        return 0;
    }

    gDPPipeSync(gDisplayListHead++);
    gDPSetCycleType(gDisplayListHead++, G_CYC_1CYCLE);
    gDPSetRenderMode(gDisplayListHead++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
    gDPSetTexturePersp(gDisplayListHead++, G_TP_NONE);
    gDPSetTextureFilter(gDisplayListHead++, G_TF_POINT);
    gDPSetCombineMode(gDisplayListHead++, G_CC_MODULATEIDECALA_PRIM, G_CC_MODULATEIDECALA_PRIM);

    if (arg0->unk_00.unk_2A & 0x100) {
        spFC.r /= 2;
        spFC.g /= 2;
        spFC.b /= 2;
        var_v0 = 1;
    } else {
        var_v0 = (arg0->unk_30 - 1) & 7;
        if (var_v0 >= 4) {
            var_v0 = 7 - var_v0;
        }
    }

    sp10C += var_v0;
    sp108 += var_v0;
    sp104 -= (var_v0 << 1);
    sp100 -= (var_v0 << 1);

    gDPSetPrimColor(gDisplayListHead++, 0, 0, var_v0 = spFC.r, spFC.g, spFC.b, spFC.a);

    gDPLoadTextureBlock(gDisplayListHead++, D_4007BF0, G_IM_FMT_IA, G_IM_SIZ_8b, w, h, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    gSPTextureRectangle(gDisplayListHead++, sp10C << 2, sp108 << 2, ((sp10C + sp104) - w) << 2, (sp108 + h) << 2,
                        G_TX_RENDERTILE, 0, 0, 0x0400, 0x0400);

    gDPLoadTextureBlock(gDisplayListHead++, D_4007BF0, G_IM_FMT_IA, G_IM_SIZ_8b, w, h, 0, G_TX_MIRROR | G_TX_WRAP,
                        G_TX_NOMIRROR | G_TX_CLAMP, 3, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    gSPTextureRectangle(gDisplayListHead++, ((sp10C + sp104) - w) << 2, sp108 << 2, (sp10C + sp104) << 2,
                        ((sp108 + sp100) - h) << 2, G_TX_RENDERTILE, 0x0100, 0, 0x0400, 0x0400);

    gDPLoadTextureBlock(gDisplayListHead++, D_4007BF0, G_IM_FMT_IA, G_IM_SIZ_8b, w, h, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_MIRROR | G_TX_WRAP, G_TX_NOMASK, 3, G_TX_NOLOD, G_TX_NOLOD);
    gSPTextureRectangle(gDisplayListHead++, (sp10C + w) << 2, ((sp108 + sp100) - h) << 2, (sp10C + sp104) << 2,
                        (sp108 + sp100) << 2, G_TX_RENDERTILE, (sp104 - 9) << 5, 0x0100, -0x0400, 0x0400);

    gDPLoadTextureBlock(gDisplayListHead++, D_4007BF0, G_IM_FMT_IA, G_IM_SIZ_8b, w, h, 0, G_TX_NOMIRROR | G_TX_WRAP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    gSPTextureRectangle(gDisplayListHead++, sp10C << 2, (sp108 + h) << 2, (sp10C + w) << 2, (sp108 + sp100) << 2,
                        G_TX_RENDERTILE, 0, (sp100 - 9) << 5, 0x0400, -0x0400);

    return 0;
}

void UIFlashingElementDual_SetState(unk_func_88001300_03C_01C* arg0, s32 arg1) {
    arg0->unk_00.unk_2A = arg1;
    arg0->unk_30 = 0;
}

void UIButtonPrompt_Create(unk_func_88001300_03C_01C* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, Color_RGBA8 arg5) {
    func_885007CC(&arg0->unk_00, sizeof(unk_func_88001300_03C_01C));
    arg0->unk_00.unk_18 = UIButtonPrompt_Draw;
    arg0->unk_00.unk_1C = UIButtonPrompt_Tick;
    arg0->unk_00.unk_24 = UIButtonPrompt_SetState;
    arg0->unk_00.unk_10.unk_00 = arg1;
    arg0->unk_00.unk_10.unk_02 = arg2;
    arg0->unk_00.unk_14.unk_00 = arg3;
    arg0->unk_00.unk_14.unk_02 = arg4;
    arg0->unk_2C = arg5;
    arg0->unk_30 = 0;
}

s32 UIButtonPrompt_Tick(unk_func_88001300_03C_01C* arg0) {
    arg0->unk_30++;
    arg0->unk_30 &= 7;
    return 0;
}

s32 UIButtonPrompt_Draw(unk_func_88001300_03C_01C* arg0, s32 arg1, s32 arg2) {
    s32 spFC;
    s32 spF8;
    s32 spF4;
    s32 spF0;
    Color_RGBA8 spEC;
    s32 var_v0;
    s32 w = 16;
    s32 h = 16;

    spFC = arg1;
    spF8 = arg2;
    spF4 = arg0->unk_00.unk_14.unk_00 + 2;
    spF0 = arg0->unk_00.unk_14.unk_02 + 2;
    spEC = arg0->unk_2C;

    if (!(arg0->unk_00.unk_2A & 1) && !(arg0->unk_00.unk_2A & 0x100)) {
        return 0;
    }

    gDPPipeSync(gDisplayListHead++);
    gDPSetCycleType(gDisplayListHead++, G_CYC_1CYCLE);
    gDPSetRenderMode(gDisplayListHead++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
    gDPSetTexturePersp(gDisplayListHead++, G_TP_NONE);
    gDPSetTextureFilter(gDisplayListHead++, G_TF_POINT);
    gDPSetCombineMode(gDisplayListHead++, G_CC_MODULATEIDECALA_PRIM, G_CC_MODULATEIDECALA_PRIM);

    if (arg0->unk_00.unk_2A & 0x100) {
        spEC.r = (spEC.r * 0x46) / 100;
        spEC.g = (spEC.g * 0x46) / 100;
        spEC.b = (spEC.b * 0x46) / 100;
        var_v0 = 1;
    } else {
        var_v0 = (arg0->unk_30 - 1) & 7;
        if (var_v0 >= 4) {
            var_v0 = 7 - var_v0;
        }
    }

    spFC += var_v0;
    spF8 += var_v0;
    spF4 -= var_v0 << 1;
    spF0 -= var_v0 << 1;

    gDPSetPrimColor(gDisplayListHead++, 0, 0, spEC.r, spEC.g, spEC.b, spEC.a);

    gDPLoadTextureBlock(gDisplayListHead++, D_4007210, G_IM_FMT_IA, G_IM_SIZ_8b, w, h, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    gSPTextureRectangle(gDisplayListHead++, spFC << 2, spF8 << 2, (spFC + w) << 2, (spF8 + h) << 2, G_TX_RENDERTILE, 0,
                        0, 0x0400, 0x0400);

    gDPLoadTextureBlock(gDisplayListHead++, D_4007318, G_IM_FMT_IA, G_IM_SIZ_8b, w, h, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    gSPTextureRectangle(gDisplayListHead++, ((spFC + spF4) - w) << 2, spF8 << 2, (spFC + spF4) << 2, (spF8 + h) << 2,
                        G_TX_RENDERTILE, 0, 0, 0x0400, 0x0400);

    gDPLoadTextureBlock(gDisplayListHead++, D_4007420, G_IM_FMT_IA, G_IM_SIZ_8b, w, h, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    gSPTextureRectangle(gDisplayListHead++, ((spFC + spF4) - w) << 2, ((spF8 + spF0) - h) << 2, (spFC + spF4) << 2,
                        (spF8 + spF0) << 2, G_TX_RENDERTILE, 0, 0, 0x0400, 0x0400);

    gDPLoadTextureBlock(gDisplayListHead++, D_4007528, G_IM_FMT_IA, G_IM_SIZ_8b, w, h, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    gSPTextureRectangle(gDisplayListHead++, spFC << 2, ((spF8 + spF0) - h) << 2, (spFC + w) << 2, (spF8 + spF0) << 2,
                        G_TX_RENDERTILE, 0, 0, 0x0400, 0x0400);

    return 0;
}

void UIButtonPrompt_SetState(unk_func_88001300_03C_01C* arg0, s32 arg1) {
    arg0->unk_00.unk_2A = arg1;
    arg0->unk_30 = 0;
}

void UIHealthBar_Create(unk_func_8820E99C_030_044* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    func_885007CC(&arg0->unk_00, sizeof(unk_func_8820E99C_030_044));
    arg0->unk_00.unk_18 = UIHealthBar_Draw;
    arg0->unk_00.unk_1C = UIHealthBar_Tick;
    arg0->unk_00.unk_24 = UIHealthBar_SetState;
    arg0->unk_00.unk_10.unk_00 = arg1;
    arg0->unk_00.unk_10.unk_02 = arg2;
    arg0->unk_00.unk_14.unk_00 = arg3;
    arg0->unk_00.unk_14.unk_02 = arg4;
    arg0->unk_30 = 0;
}

s32 UIHealthBar_Tick(unk_func_8820E99C_030_044* arg0) {
    arg0->unk_30++;
    arg0->unk_30 &= 7;
    return 0;
}

s32 UIHealthBar_Draw(unk_func_8820E99C_030_044* arg0, s32 arg1, s32 arg2) {
    UNUSED s32 pad[2];
    s32 var_t4;
    s32 sp80 = ((arg0->unk_00.unk_14.unk_00 - 0xE) / 2) + arg1;

    if (!(arg0->unk_00.unk_2A & 1) && ((arg0->unk_00.unk_28 & 0x100) || !(arg0->unk_00.unk_2A & 0x100))) {
        return 0;
    }

    if (arg0->unk_00.unk_2A & 0x100) {
        var_t4 = 2;
    } else if (gPlayer1Controller->buttonDown & 0xC00) {
        var_t4 = 2;
    } else {
        var_t4 = (arg0->unk_30 - 1) & 7;
        if (var_t4 >= 4) {
            var_t4 = 7 - var_t4;
        }
    }

    gDPPipeSync(gDisplayListHead++);
    gDPSetCycleType(gDisplayListHead++, G_CYC_COPY);
    gDPSetRenderMode(gDisplayListHead++, G_RM_NOOP, G_RM_NOOP2);
    gDPSetAlphaCompare(gDisplayListHead++, G_AC_THRESHOLD);
    gDPSetTexturePersp(gDisplayListHead++, G_TP_NONE);

    gDPLoadTextureBlock(gDisplayListHead++, (gPlayer1Controller->buttonDown & 0x800) ? D_4001428 : D_4001218,
                        G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 8, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP,
                        G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    gSPTextureRectangle(gDisplayListHead++, sp80 << 2, ((arg2 - var_t4) - 8) << 2, (sp80 + 0xD) << 2,
                        ((arg2 - var_t4) - 1) << 2, G_TX_RENDERTILE, 0, 0, 0x1000, 0x0400);

    gDPLoadTextureBlock(gDisplayListHead++, (gPlayer1Controller->buttonDown & 0x400) ? D_4001530 : D_4001320,
                        G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 8, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP,
                        G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    gSPTextureRectangle(gDisplayListHead++, sp80 << 2, (arg2 + arg0->unk_00.unk_14.unk_02 + var_t4) << 2,
                        (sp80 + 0xD) << 2, (arg2 + arg0->unk_00.unk_14.unk_02 + var_t4 + 7) << 2, G_TX_RENDERTILE, 0, 0,
                        0x1000, 0x0400);

    gDPPipeSync(gDisplayListHead++);
    gDPSetAlphaCompare(gDisplayListHead++, G_AC_NONE);

    return 0;
}

void UIHealthBar_SetState(unk_func_8820E99C_030_044* arg0, s32 arg1) {
    arg0->unk_00.unk_2A = arg1;
    arg0->unk_30 = 0;
}

void UIStatusBar_Create(unk_func_88001300_030* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, Color_RGBA8 arg5) {
    func_885007CC(&arg0->unk_00, sizeof(unk_func_88001300_030));
    arg0->unk_00.unk_18 = UIStatusBar_Draw;
    arg0->unk_00.unk_1C = UIStatusBar_Update;
    arg0->unk_00.unk_10.unk_00 = arg1;
    arg0->unk_00.unk_10.unk_02 = arg2;
    arg0->unk_00.unk_14.unk_00 = arg3;
    arg0->unk_00.unk_14.unk_02 = arg4;
    arg0->unk_2C = arg5;
    arg0->unk_30 = 0;
    arg0->unk_34 = 0;
}

s32 UIStatusBar_Update(unk_func_88001300_030* arg0) {
    if (arg0->unk_30 >= 0xB) {
        arg0->unk_30 = 0;
        arg0->unk_34 = 0;
        arg0->unk_00.unk_28 &= ~1;
    } else if (arg0->unk_30 >= 7) {
        arg0->unk_34 = 4;
        arg0->unk_30++;
    } else if (arg0->unk_30 < 4) {
        if (arg0->unk_30 == 0) {
            PlaySoundEffect(4);
        }
        arg0->unk_34 = 1;
        arg0->unk_30++;
    } else {
        arg0->unk_34 = 2;
        if (arg0->unk_30 < 6) {
            arg0->unk_34 |= 8;
            arg0->unk_30++;
        }
    }

    return (arg0->unk_34 & 2) ? 0 : 1;
}

s32 UIStatusBar_Draw(unk_func_88001300_030* arg0, s32 arg1, s32 arg2) {
    UNUSED s32 pad[2];
    s32 sp114;
    s32 sp110;
    UNUSED s32 pad2[4];
    s16 var_v0;
    s16 var_v1_2;
    s32 temp_a0;
    s32 var_s0;
    s32 var_t4;
    s32 val = 0x10;

    if (arg0->unk_34 & 0xF) {
        var_v0 = arg0->unk_00.unk_14.unk_00;
        var_v1_2 = arg0->unk_00.unk_14.unk_02;

        if (var_v0 < val) {
            var_v0 = val;
        }

        if (var_v1_2 < val) {
            do {
                var_v1_2 = val;
            } while (0);
        }

        if (arg0->unk_34 & 4) {
            temp_a0 = 0xB - arg0->unk_30;

            sp110 = ((var_v1_2 - val) * temp_a0) / 4;
            sp114 = ((var_v0 - val) * temp_a0) / 4;
            var_s0 = (((var_v0 - val) - sp114) / 2) + arg1;
            var_t4 = (((var_v1_2 - val) - sp110) / 2) + arg2;

            // clang-format off
            sp114 += val; sp110 += val;
            // clang-format on
        } else if (arg0->unk_34 & 1) {
            temp_a0 = arg0->unk_30 - 1;

            sp110 = ((var_v1_2 - val) * temp_a0) / 4;
            sp114 = ((var_v0 - val) * temp_a0) / 4;
            var_s0 = (((var_v0 - val) - sp114) / 2) + arg1;
            var_t4 = (((var_v1_2 - val) - sp110) / 2) + arg2;

            // clang-format off
            sp114 += val; sp110 += val;
            // clang-format on
        } else {
            var_s0 = arg1;
            var_t4 = arg2;
            sp114 = var_v0;
            sp110 = var_v1_2;
        }

        gDPPipeSync(gDisplayListHead++);
        gDPSetCycleType(gDisplayListHead++, G_CYC_1CYCLE);
        gDPSetRenderMode(gDisplayListHead++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
        gDPSetTexturePersp(gDisplayListHead++, G_TP_NONE);
        gDPSetTextureFilter(gDisplayListHead++, G_TF_POINT);
        gDPSetCombineMode(gDisplayListHead++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
        gDPSetPrimColor(gDisplayListHead++, 0, 0, arg0->unk_2C.r, arg0->unk_2C.g, arg0->unk_2C.b, arg0->unk_2C.a);

        gDPLoadTextureBlock(gDisplayListHead++, D_4007630, G_IM_FMT_I, G_IM_SIZ_8b, 8, 8, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                            G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
        gSPTextureRectangle(gDisplayListHead++, var_s0 << 2, var_t4 << 2, ((var_s0 + sp114) - 8) << 2,
                            ((var_t4 + sp110) - 8) << 2, G_TX_RENDERTILE, 0, 0, 0x0400, 0x0400);

        gDPLoadTextureBlock(gDisplayListHead++, D_4007678, G_IM_FMT_I, G_IM_SIZ_8b, 8, 8, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                            G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
        gSPTextureRectangle(gDisplayListHead++, ((var_s0 + sp114) - 8) << 2, var_t4 << 2, (var_s0 + sp114) << 2,
                            ((var_t4 + sp110) - 8) << 2, G_TX_RENDERTILE, 0, 0, 0x0400, 0x0400);

        gDPLoadTextureBlock(gDisplayListHead++, D_40076C0, G_IM_FMT_I, G_IM_SIZ_8b, 8, 8, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                            G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
        gSPTextureRectangle(gDisplayListHead++, (var_s0 + 8) << 2, ((var_t4 + sp110) - 8) << 2, (var_s0 + sp114) << 2,
                            (var_t4 + sp110) << 2, G_TX_RENDERTILE, (sp114 * -0x20) + 0x200, 0, 0x0400, 0x0400);

        gDPLoadTextureBlock(gDisplayListHead++, D_4007708, G_IM_FMT_I, G_IM_SIZ_8b, 8, 8, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                            G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
        gSPTextureRectangle(gDisplayListHead++, var_s0 << 2, ((var_t4 + sp110) - 8) << 2, (var_s0 + 8) << 2,
                            (var_t4 + sp110) << 2, G_TX_RENDERTILE, 0, 0, 0x0400, 0x0400);
    }

    return (arg0->unk_34 & 2) ? 0 : 1;
}

void MessageBox_Create(unk_func_88001300_034* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, Color_RGBA8 arg6,
                   TextObject* arg7) {
    func_885007CC(&arg0->unk_00, sizeof(unk_func_88001300_034));
    arg0->unk_00.unk_18 = func_88505EF4;
    arg0->unk_00.unk_1C = func_88505EC0;
    arg0->unk_00.unk_10.unk_00 = arg1;
    arg0->unk_00.unk_10.unk_02 = arg2;
    arg0->unk_34 = arg3;
    arg0->unk_35 = arg4;
    arg0->unk_36 = arg5;
    arg0->unk_38 = arg6;
    arg0->unk_3C = arg7;
    MessageBox_SetText(arg0, NULL);
}

s32 func_88505EC0(unk_func_88001300_034* arg0) {
    if ((((arg0->unk_40 * 0xF) / 5) + 1) <= arg0->unk_30) {
        arg0->unk_40++;
    }
    return 0;
}

s32 func_88505EF4(unk_func_88001300_034* arg0, s32 arg1, s32 arg2) {
    s32 temp_fp;
    s32 var_s2;
    s32 var_s3;
    s32 var_s5;
    s32 var_v1;
    u8* var_s4;
    s32 temp_v0_3;
    u8 var_s0;

    if (arg0->unk_2C == NULL) {
        return 0;
    }

    var_s2 = arg1;
    var_s5 = arg2;
    var_s4 = &arg0->unk_2C->unk_00.unk_00.unk_00;
    temp_fp = ((arg0->unk_40 * 0xF) / 5) + 1;

    Text_ResetState();
    Text_SetFont(arg0->unk_34, arg0->unk_35);
    Text_SetEnvColor(arg0->unk_38.r, arg0->unk_38.g, arg0->unk_38.b, arg0->unk_38.a);
    var_s3 = 0;
    if (temp_fp > 0) {
        var_s0 = *var_s4++;

        while (var_s0 != 0) {
            if (var_s0 == (0, 0xA)) {
                var_s2 = arg1;
                var_s5 += arg0->unk_36;
            } else {
                Text_PutChar(var_s2, var_s5, var_s0);
                temp_v0_3 = Text_GetCharWidth(&arg0->unk_3C->unk_00[arg0->unk_3C->unk_50], temp_v0_3 = var_s0);
                if (arg0->unk_3C->unk_50 >= 2) {
                    var_v1 = temp_v0_3 - 2;
                } else {
                    var_v1 = temp_v0_3 - 1;
                }
                var_s2 += var_v1 + arg0->unk_35;
            }

            var_s3++;
            if (var_s3 >= temp_fp) {
                break;
            }

            var_s0 = *var_s4++;
        }
    }

    Text_SetupDL();
    return 0;
}

void MessageBox_SetText(unk_func_88001300_034* arg0, u8* arg1) {
    s32 var_v0;
    s32 val;
    u8* arg;

    arg0->unk_2C = arg1;
    arg0->unk_40 = 0;

    if (arg0->unk_2C == NULL) {
        arg0->unk_30 = 0;
        return;
    }

    var_v0 = 0;
    arg = arg1;
    val = *arg++;
    while (val != 0) {
        var_v0++;
        val = *arg++;
    }
    arg0->unk_30 = var_v0;
}

void UIButton_Create(unk_func_88200FA0_030_030* arg0, s32 arg1, s32 arg2, unk_func_88200FA0_030_030_040 arg3, s32 arg4,
                   s32 arg5, s32 arg6, s32 arg7, MemoryPool* arg8) {
    static Color_RGBA8 Color_Yellow = { 255, 255, 0, 255 };

    s32 var_v0;
    unk_func_88001300_03C_01C* temp_v0;

    func_885007CC(&arg0->unk_00, sizeof(unk_func_88200FA0_030_030));

    arg0->unk_00.unk_18 = List_DrawItems;
    arg0->unk_00.unk_20 = List_HandleInput;
    arg0->unk_00.unk_24 = List_SetSelectionMode;

    arg0->unk_00.unk_10.unk_00 = arg1;
    arg0->unk_00.unk_10.unk_02 = arg2;
    arg0->unk_00.unk_14.unk_00 = arg4 * arg7;
    arg0->unk_00.unk_14.unk_02 = arg5 * arg6;

    arg0->unk_3C = arg4;
    arg0->unk_3E = arg5;
    arg0->unk_40 = arg3;
    arg0->unk_48 = arg7;
    arg0->unk_4A = arg6;

    arg0->unk_2C = NULL;
    arg0->unk_30 = 0;
    arg0->unk_34 = NULL;

    // clang-format off
    arg0->unk_4C = 0; arg0->unk_4E = 0;
    // clang-format on

    if (arg7 == 1) {
        arg0->unk_50 = 0;
    } else {
        // clang-format off
        arg0->unk_50 = -3;    }    arg0->unk_52 = -3;
    // clang-format on

    arg0->unk_44 = mem_pool_alloc(arg8, sizeof(unk_func_88001300_03C_01C));

    if (arg7 == 1) {
        var_v0 = 0;
    } else {
        var_v0 = 3;
    }

    UIButtonPrompt_Create(arg0->unk_44, 0, 0, (var_v0 << 1) + arg4, arg5 + 6, Color_Yellow);
    arg0->unk_44->unk_00.unk_28 &= ~1;
    Fragment_SetChild(&arg0->unk_00.unk_00, &arg0->unk_44->unk_00.unk_00);
    ((func88506BFC)Memmap_GetFragmentVaddr(Fragment_Refresh))(arg0, 0);
}

void ScrollableList_SetItemHeight(unk_func_88200FA0_030_030* arg0, s32 arg1, MemoryPool* arg2) {
    if (arg0->unk_34 != NULL) {
        mem_pool_free(arg2, arg0->unk_34);
    }
    arg0->unk_34 = mem_pool_alloc(arg2, arg1 * 2);
}

void Fragment_ClearFlags(unk_func_88200FA0_030_030* arg0) {
    s32 i;

    for (i = 0; i < arg0->unk_2C->unk_04; i++) {
        arg0->unk_34[i] = 0;
    }
}

void List_SetSelectionMode(unk_func_88200FA0_030_030* arg0, s32 arg1) {
    arg0->unk_00.unk_2A = arg1;
    arg0->unk_44->unk_00.unk_24(&arg0->unk_44->unk_00, arg1);
    arg0->unk_44->unk_00.unk_28 &= ~1;
    if (arg1 & 0x101) {
        arg0->unk_44->unk_00.unk_28 |= 1;
    }
}

void List_SetData(unk_func_88200FA0_030_030_1CEA00* arg0, unk_func_8830867C_02C_0CC* arg1) {
    arg0->unk_2C = arg1;
    arg0->unk_30 = 0;
    ((func88506BFC)Memmap_GetFragmentVaddr(Fragment_Refresh))(arg0, 0);
    Fragment_ClearFlags(arg0);
}

void List_SetItems(unk_func_88200FA0_030_030* arg0, unk_func_88200FA0_030_038* arg1, MemoryPool* arg2) {
    ScrollableList_SetItemHeight(arg0, arg1->unk_04, arg2);
    List_SetData(arg0, arg1);
}

void Fragment_SetData(unk_func_88200FA0_030_030* arg0, unk_func_88201DA0_038* arg1) {
    arg0->unk_2C = arg1;
    arg0->unk_30 = 1;
    ((func88506BFC)Memmap_GetFragmentVaddr(Fragment_Refresh))(arg0, 0);
    Fragment_ClearFlags(arg0);
}

void List_InitFromData3(unk_func_88200FA0_030_030* arg0, unk_func_8820BE14_06C* arg1, MemoryPool* arg2) {
    ScrollableList_SetItemHeight(arg0, arg1->unk_04, arg2);
    Fragment_SetData(arg0, arg1);
}

s32 List_DrawItems(unk_func_88200FA0_030_030* arg0, s32 arg1, s32 arg2) {
    s32 i;
    s16 temp_v1;
    s32 temp_lo;
    s32 var_s3;
    s32 var_s5;
    s32 var_v0;
    void* var_s2;
    void* var_a2;

    temp_lo = arg0->unk_4A * arg0->unk_48;
    var_s2 = NULL;
    var_s5 = 0;
    var_s3 = 0;
    if (arg0->unk_2C != NULL) {
        var_s2 = arg0->unk_2C->unk_00;
        if (arg0->unk_30 != 0) {
            var_s5 = arg0->unk_2C->unk_0C;
        }
        var_s3 = arg0->unk_2C->unk_08;
    }

    for (i = 0; i < temp_lo; i++) {
        var_a2 = NULL;
        var_v0 = 0;
        temp_v1 = arg0->unk_48;
        if (i < var_s3) {
            if (arg0->unk_30 != 0) {
                var_a2 = &((s8*)var_s2)[var_s5 * i];
            } else {
                var_a2 = ((s32*)var_s2)[i];
            }

            var_v0 = arg0->unk_34[i];
            if (i == arg0->unk_38) {
                var_v0 |= 1;
            }
        }
        arg0->unk_40(((i % temp_v1) * arg0->unk_3C) + arg1, ((i / temp_v1) * arg0->unk_3E) + arg2, var_a2, i, var_v0,
                     arg0);
    }

    return 0;
}

s32 List_HandleInput(unk_func_88200FA0_030_030* arg0, Controller* arg1) {
    s32 sp5C;
    s32 sp58;
    s32 sp54;
    s32 sp50;
    s32 sp4C;
    s32 sp48;
    s32 i;
    s32 j;
    s32 temp_v0_3;
    s32 sp24;
    s32 var_t4;

    var_t4 = 0;
    sp5C = 0;
    if ((arg0->unk_2C == NULL) || (arg0->unk_2C->unk_08 == 0)) {
        return 0;
    }
    sp48 = ((arg0->unk_2C->unk_08 + arg0->unk_48) - 1) / arg0->unk_48;
    sp58 = arg0->unk_38 % arg0->unk_48;
    sp54 = arg0->unk_38 / arg0->unk_48;
    sp24 = MenuInput_ReadDirection() & 0xFFFF;

    if (sp24 == 0x800) {
        for (i = 0, sp4C = sp54; i < sp48 - 1; i++) {
            sp4C = ((sp4C == 0) ? sp48 : sp4C) - 1;

            for (j = 0, sp50 = arg0->unk_4C; j < arg0->unk_48;) {
                temp_v0_3 = (arg0->unk_48 * sp4C) + sp50;
                if ((temp_v0_3 < arg0->unk_2C->unk_08) && !(arg0->unk_34[temp_v0_3] & 4)) {
                    var_t4 = 1;
                    break;
                }
                j++;
                sp50 = ((sp50 == 0) ? arg0->unk_48 : sp50) - 1;
            }

            if (var_t4 != 0) {
                break;
            }
        }

        if ((arg0->unk_00.unk_28 & 0x200) && ((var_t4 == 0) || (sp54 < sp4C))) {
            sp5C = 8;
            var_t4 = 0;
        }
    } else if (sp24 == 0x400) {
        for (i = 0, sp4C = sp54; i < sp48 - 1; i++) {
            if (sp4C + 1 == sp48) {
                sp4C = 0;
            } else {
                sp4C++;
            }

            for (j = 0, sp50 = arg0->unk_4C; j < arg0->unk_48;) {
                temp_v0_3 = (arg0->unk_48 * sp4C) + sp50;
                if ((temp_v0_3 < arg0->unk_2C->unk_08) && !(arg0->unk_34[temp_v0_3] & 4)) {
                    var_t4 = 1;
                    break;
                }
                j++;
                sp50 = ((sp50 == 0) ? arg0->unk_48 : sp50) - 1;
            }

            if (var_t4 != 0) {
                break;
            }
        }

        if ((arg0->unk_00.unk_28 & 0x200) && ((var_t4 == 0) || (sp4C < sp54))) {
            sp5C = 8;
            var_t4 = 0;
        }
    } else if (sp24 == 0x100) {
        for (j = 0, sp50 = sp58; j < arg0->unk_48 - 1; j++) {
            if (sp50 == arg0->unk_48 - 1) {
                sp50 = 0;
            } else {
                sp50++;
            }

            for (i = 0, sp4C = arg0->unk_4E; i < sp48;) {
                temp_v0_3 = (arg0->unk_48 * sp4C) + sp50;
                if ((temp_v0_3 < arg0->unk_2C->unk_08) && !(arg0->unk_34[temp_v0_3] & 4)) {
                    var_t4 = 1;
                    break;
                }
                i++;
                sp4C = ((sp4C == 0) ? sp48 : sp4C) - 1;
            }

            if (var_t4 != 0) {
                break;
            }
        }

        if ((arg0->unk_00.unk_28 & 0x100) && ((var_t4 == 0) || (sp50 < sp58))) {
            sp5C = 8;
            var_t4 = 0;
        }
    } else if (sp24 == 0x200) {
        for (j = 0, sp50 = sp58; j < arg0->unk_48 - 1; j++) {
            sp50 = ((sp50 == 0) ? arg0->unk_48 : sp50) - 1;

            for (i = 0, sp4C = arg0->unk_4E; i < sp48;) {
                temp_v0_3 = (arg0->unk_48 * sp4C) + sp50;
                if ((temp_v0_3 < arg0->unk_2C->unk_08) && !(arg0->unk_34[temp_v0_3] & 4)) {
                    var_t4 = 1;
                    break;
                }
                i++;
                sp4C = ((sp4C == 0) ? sp48 : sp4C) - 1;
            }

            if (var_t4 != 0) {
                break;
            }
        }

        if ((arg0->unk_00.unk_28 & 0x100) && ((var_t4 == 0) || (sp58 < sp50))) {
            sp5C = 8;
            var_t4 = 0;
        }
    }

    if (var_t4 != 0) {
        arg0->unk_38 = (arg0->unk_48 * sp4C) + sp50;
        arg0->unk_44->unk_00.unk_10.unk_00 = ((arg0->unk_38 % arg0->unk_48) * arg0->unk_3C) + arg0->unk_50;
        arg0->unk_44->unk_00.unk_10.unk_02 = ((arg0->unk_38 / arg0->unk_48) * arg0->unk_3E) + arg0->unk_52;
        if ((sp24 == 0x800) || (sp24 == 0x400)) {
            arg0->unk_4E = sp4C;
        } else {
            arg0->unk_4C = sp50;
        }
        sp5C = 0x80000009;
    }
    return sp5C;
}

void Fragment_Refresh(unk_func_88200FA0_030_030* arg0, s32 arg1) {
    arg0->unk_38 = arg1;
    arg0->unk_44->unk_00.unk_10.unk_00 = ((arg1 % arg0->unk_48) * arg0->unk_3C) + arg0->unk_50;
    arg0->unk_44->unk_00.unk_10.unk_02 = ((arg0->unk_38 / arg0->unk_48) * arg0->unk_3E) + arg0->unk_52;
    arg0->unk_4C = arg0->unk_38 % arg0->unk_48;
    arg0->unk_4E = arg0->unk_38 / arg0->unk_48;
}

s32 Fragment_Update(unk_func_88200FA0_030_030* arg0) {
    s32 var_a1 = arg0->unk_38;

    if (arg0->unk_38 < arg0->unk_2C->unk_08) {
        while (arg0->unk_34[var_a1] & 4) {
            var_a1++;
            if (var_a1 >= arg0->unk_2C->unk_08) {
                break;
            }
        }
    }

    if (var_a1 < arg0->unk_2C->unk_08) {
        Fragment_Refresh(arg0, var_a1);
        return var_a1;
    }

    var_a1 = arg0->unk_38 - 1;
    if (var_a1 >= 0) {
        while (arg0->unk_34[var_a1] & 4) {
            var_a1--;
            if (var_a1 < 0) {
                break;
            }
        }
    }

    if (var_a1 >= 0) {
        Fragment_Refresh(arg0, var_a1);
        return var_a1;
    }

    return -1;
}

void ScrollListFragment_Create(unk_func_8821421C_038_034* arg0, s32 arg1, s32 arg2, unk_func_88200FA0_030_030_040 arg3, s32 arg4,
                   s32 arg5, s32 arg6, MemoryPool* arg7) {
    UIButton_Create(&arg0->unk_00, arg1, arg2, arg3, arg4, arg5, arg6, 1, arg7);
    arg0->unk_00.unk_00.unk_1C = ScrollListFragment_Update;
    arg0->unk_00.unk_00.unk_18 = ScrollListFragment_Draw;
    arg0->unk_00.unk_00.unk_20 = ScrollListFragment_HandleInput;
    arg0->unk_00.unk_4A = arg6;
    arg0->unk_54 = arg0->unk_56 = 0;
    arg0->unk_64 = (arg0->unk_00.unk_3E * 4) / 10;
    arg0->unk_68 = (arg0->unk_00.unk_3E * arg0->unk_00.unk_4A * 2) / 10;
    arg0->unk_00.unk_38 = 0;
    arg0->unk_5C = 0;
    arg0->unk_60 = 0;
    arg0->unk_58 = 0;
    arg0->unk_6C = 8;
}

void ScrollListFragment_SetData(unk_func_8820BE14_02C_038* arg0, unk_func_88200FA0_030_038* arg1) {
    arg0->unk_00.unk_2C = arg1;
    arg0->unk_00.unk_30 = 0;
    arg0->unk_00.unk_38 = 0;
    arg0->unk_5C = 0;
    arg0->unk_60 = 0;
    arg0->unk_58 = 0;
    arg0->unk_6C = 0;
    Fragment_ClearFlags(&arg0->unk_00);
}

void ScrollListFragment_Init(unk_func_8830867C_02C_034* arg0, unk_func_88200FA0_030_038* arg1, MemoryPool* arg2) {
    ScrollableList_SetItemHeight(arg0, arg1->unk_04, arg2);
    ScrollListFragment_SetData(arg0, arg1);
}

void ScrollListFragment_Init2(unk_func_8821421C_038_034* arg0, unk_func_8821421C_038_050** arg1) {
    arg0->unk_00.unk_2C = arg1;
    arg0->unk_00.unk_30 = 1;
    arg0->unk_00.unk_38 = 0;
    arg0->unk_5C = 0;
    arg0->unk_60 = 0;
    arg0->unk_58 = 0;
    arg0->unk_6C = 0;
    Fragment_ClearFlags(&arg0->unk_00);
}

void ScrollListFragment_Init3(unk_func_8821421C_038_034* arg0, unk_func_8830867C_03C_0D0* arg1, MemoryPool* arg2) {
    ScrollableList_SetItemHeight(&arg0->unk_00, arg1->unk_04, arg2);
    ScrollListFragment_Init2(arg0, arg1);
}

void ScrollListFragment_UpdateMinOffset(unk_func_8820BE14_02C_038* arg0) {
    if (arg0->unk_5C < arg0->unk_58) {
        arg0->unk_58 = arg0->unk_5C;
    }
}

void ScrollListFragment_UpdateMaxOffset(unk_func_8820BE14_02C_038* arg0) {
    s32 temp_v0 = (arg0->unk_5C - (arg0->unk_00.unk_3E * arg0->unk_00.unk_4A)) + 1;

    if (arg0->unk_58 < temp_v0) {
        arg0->unk_58 = temp_v0;
    }
}

s32 ScrollListFragment_Update(unk_func_8821421C_038_034* arg0) {
    s32 sp24;
    s32 temp_a2_2;
    s32 sp1C;
    s32 temp_a2_4;
    s32 temp_a3;
    s32 temp_a3_2;
    s32 var_a3;
    s32 var_v1;

    if (arg0->unk_56 & 0x800) {
        if (!(arg0->unk_54 & 0x800)) {
            sp24 = arg0->unk_00.unk_38 * arg0->unk_00.unk_3E;
            temp_a3 = arg0->unk_5C - sp24;
            arg0->unk_5C -= (temp_a3 < arg0->unk_64) ? temp_a3 : arg0->unk_64;
            ScrollListFragment_UpdateMinOffset(arg0);
            if (sp24 == arg0->unk_5C) {
                arg0->unk_56 &= ~0x800;
            }
        }
    } else if (arg0->unk_56 & 0x400) {
        if (!(arg0->unk_54 & 0x400)) {
            sp1C = ((arg0->unk_00.unk_38 + 1) * arg0->unk_00.unk_3E) - 1;
            temp_a3_2 = sp1C - arg0->unk_5C;
            arg0->unk_5C += (temp_a3_2 < arg0->unk_64) ? temp_a3_2 : arg0->unk_64;
            ScrollListFragment_UpdateMaxOffset(arg0);
            if (sp1C == arg0->unk_5C) {
                arg0->unk_56 &= ~0x400;
                arg0->unk_5C = (arg0->unk_5C - arg0->unk_00.unk_3E) + 1;
            }
        }
    } else if (arg0->unk_56 & 0x200) {
        if (!(arg0->unk_54 & 0x200)) {
            temp_a2_2 = arg0->unk_5C - arg0->unk_60;
            var_v1 = (temp_a2_2 < arg0->unk_68) ? temp_a2_2 : arg0->unk_68;
            arg0->unk_5C -= var_v1;
            arg0->unk_58 -= (arg0->unk_58 < var_v1) ? arg0->unk_58 : var_v1;
            arg0->unk_00.unk_38 = arg0->unk_5C / arg0->unk_00.unk_3E;
            if (arg0->unk_60 == arg0->unk_5C) {
                arg0->unk_56 &= ~0x200;
            }
        }
    } else if ((arg0->unk_56 & 0x100) && !(arg0->unk_54 & 0x100)) {
        s32 tmp = arg0->unk_00.unk_3E * arg0->unk_00.unk_2C->unk_08;
        s32 tmp2 = arg0->unk_00.unk_3E * arg0->unk_00.unk_4A;

        temp_a2_4 = arg0->unk_60 - arg0->unk_5C;

        var_a3 = (temp_a2_4 < arg0->unk_68) ? temp_a2_4 : arg0->unk_68;
        arg0->unk_5C += var_a3;

        var_v1 = (tmp - arg0->unk_58) - tmp2;

        if (var_v1 <= 0) {
            var_v1 = 0;
        }

        arg0->unk_58 += (var_v1 < var_a3) ? var_v1 : var_a3;
        arg0->unk_00.unk_38 = arg0->unk_5C / arg0->unk_00.unk_3E;
        if (arg0->unk_60 == arg0->unk_5C) {
            arg0->unk_56 &= ~0x100;
        }
    }

    arg0->unk_54 = 0;
    var_v1 = arg0->unk_5C - arg0->unk_58;
    if (arg0->unk_56 & 0x400) {
        var_v1 = (var_v1 - arg0->unk_00.unk_3E) + 1;
    }
    arg0->unk_00.unk_44->unk_00.unk_10.unk_00 = arg0->unk_00.unk_50;
    arg0->unk_00.unk_44->unk_00.unk_10.unk_02 = arg0->unk_00.unk_52 + var_v1;
    return 0;
}

s32 ScrollListFragment_Draw(unk_func_8821421C_038_034* arg0, s32 arg1, s32 arg2) {
    s16 temp_v0_2;
    s32 temp_a0;
    s32 temp_lo;
    s32 temp_s5;
    s32 var_s0;
    s32 var_s2;
    s32 var_s4;
    s32 var_s6;
    s32 var_v0;
    unk_func_8820BE14_06C* temp_v0;
    void* var_s3;
    void* var_a2;

    temp_lo = arg0->unk_00.unk_3E * arg0->unk_00.unk_4A;
    var_s3 = NULL;
    var_s6 = 0;
    var_s4 = 0;

    if (arg0->unk_00.unk_2C != NULL) {
        var_s3 = arg0->unk_00.unk_2C->unk_00;
        if (arg0->unk_00.unk_30 != 0) {
            var_s6 = arg0->unk_00.unk_2C->unk_0C;
        }
        var_s4 = arg0->unk_00.unk_2C->unk_08;
    }

    gDPPipeSync(gDisplayListHead++);
    gDPSetScissorFrac(gDisplayListHead++, G_SC_NON_INTERLACE, 0, arg2 * 4.0f, 0x0A00, (arg2 + temp_lo) * 4.0f);

    var_s2 = arg2 - (arg0->unk_58 % arg0->unk_00.unk_3E);
    var_s0 = arg0->unk_58 / arg0->unk_00.unk_3E;
    temp_s5 = (((arg0->unk_58 + temp_lo) - 1) / arg0->unk_00.unk_3E) + 1;

    while (var_s0 < temp_s5) {
        var_a2 = NULL;
        var_v0 = 0;
        if (var_s0 < var_s4) {
            if (arg0->unk_00.unk_30 != 0) {
                var_a2 = &((s8*)var_s3)[var_s6 * var_s0];
            } else {
                var_a2 = ((s32*)var_s3)[var_s0];
            }

            var_v0 = arg0->unk_00.unk_34[var_s0];
            if (var_s0 == arg0->unk_00.unk_38) {
                var_v0 |= 1;
            }
        }
        arg0->unk_00.unk_40(arg1, var_s2, var_a2, var_s0, var_v0, arg0);
        var_s2 += arg0->unk_00.unk_3E;
        var_s0++;
    }

    gDPPipeSync(gDisplayListHead++);
    gDPSetScissor(gDisplayListHead++, G_SC_NON_INTERLACE, 0, 0, 640, 480);
    return 0;
}

s32 ScrollListFragment_HandleInput(unk_func_8821421C_038_034* arg0, Controller* arg1) {
    s32 temp_t0;
    s32 temp_t3;
    s32 var_t2;
    s32 var_t4;

    temp_t3 = arg0->unk_60;
    temp_t0 = arg0->unk_00.unk_38;
    var_t2 = 0;
    var_t4 = 0;

    // clang-format off
    if (arg1->buttonPressed & 0x800) {
        arg0->unk_6C = 8; arg0->unk_54 = 0x800;
    } else if (arg1->buttonPressed & 0x400) {
        arg0->unk_6C = 8; arg0->unk_54 = 0x400;
    } else if (arg1->buttonPressed & 0x200) {
        arg0->unk_6C = 8; arg0->unk_54 = 0x200;
    } else if (arg1->buttonPressed & 0x100) {
        arg0->unk_6C = 8; arg0->unk_54 = 0x100;
    } else if (arg0->unk_6C > 0) {
        arg0->unk_6C--;
    } else {
        arg0->unk_54 = arg1->buttonDown;
    }
    // clang-format on

    if ((arg0->unk_00.unk_2C == NULL) || !(arg0->unk_00.unk_2C->unk_08)) {
        return (arg1->buttonPressed & 0xF00) ? 8 : 0;
    }

    if ((arg0->unk_54 & 0x800) && ((arg0->unk_56 & ~0x800) == 0)) {
        if ((arg0->unk_56 == 0) && (arg0->unk_5C == 0)) {
            var_t4 = 1;
        }
        arg0->unk_56 |= 0x800;
        arg0->unk_5C -= (arg0->unk_5C < arg0->unk_64) ? arg0->unk_5C : arg0->unk_64;
        ScrollListFragment_UpdateMinOffset(arg0);
        arg0->unk_00.unk_38 = arg0->unk_5C / arg0->unk_00.unk_3E;
        if (temp_t0 != arg0->unk_00.unk_38) {
            var_t2 = 0x80000000;
        }
    } else if ((arg0->unk_54 & 0x400) && ((arg0->unk_56 & ~0x400) == 0)) {
        s32 temp_a3_2;
        s32 temp_lo_2 = arg0->unk_00.unk_3E * arg0->unk_00.unk_2C->unk_08;

        if (arg0->unk_56 == 0) {
            arg0->unk_5C = (arg0->unk_5C + arg0->unk_00.unk_3E) - 1;
            if (temp_lo_2 == (arg0->unk_5C + 1)) {
                var_t4 = 1;
            }
        }
        temp_a3_2 = (temp_lo_2 - arg0->unk_5C) - 1;
        arg0->unk_56 |= 0x400;
        arg0->unk_5C += (temp_a3_2 < arg0->unk_64) ? temp_a3_2 : arg0->unk_64;
        ScrollListFragment_UpdateMaxOffset(arg0);
        arg0->unk_00.unk_38 = arg0->unk_5C / arg0->unk_00.unk_3E;
        if (temp_t0 != arg0->unk_00.unk_38) {
            var_t2 = 0x80000000;
        }
    } else if ((arg0->unk_54 & 0x200) && ((arg0->unk_56 & ~0x200) == 0)) {
        s32 temp_lo_2 = arg0->unk_00.unk_3E * arg0->unk_00.unk_4A;

        if (arg0->unk_56 == 0) {
            arg0->unk_60 = arg0->unk_5C;
            if (arg0->unk_60 > 0) {
                var_t2 = 0x80000000;
            }
        }
        arg0->unk_56 |= 0x200;
        arg0->unk_5C -= (arg0->unk_5C < arg0->unk_68) ? arg0->unk_5C : arg0->unk_68;
        if (arg0->unk_5C < arg0->unk_60) {
            arg0->unk_60 -= (temp_lo_2 < arg0->unk_60) ? temp_lo_2 : arg0->unk_60;
        }
        arg0->unk_00.unk_38 = arg0->unk_5C / arg0->unk_00.unk_3E;
        arg0->unk_58 -= (arg0->unk_58 < arg0->unk_68) ? arg0->unk_58 : arg0->unk_68;
        if (temp_t3 != arg0->unk_60) {
            var_t2 |= 0x80000000;
        }
    } else if (arg0->unk_54 & 0x100) {
        if (!(arg0->unk_56 & ~0x100)) {
            s32 temp_lo_5 = arg0->unk_00.unk_3E * arg0->unk_00.unk_2C->unk_08;
            s32 temp_lo_6 = arg0->unk_00.unk_3E * arg0->unk_00.unk_4A;
            s32 temp_a2 = (temp_lo_5 - arg0->unk_5C) - arg0->unk_00.unk_3E;
            s32 var_a2;

            if (arg0->unk_56 == 0) {
                arg0->unk_60 = arg0->unk_5C;
                if (temp_a2 > 0) {
                    var_t2 = 0x80000000;
                }
            }
            arg0->unk_56 |= 0x100;
            arg0->unk_5C += (temp_a2 < arg0->unk_68) ? temp_a2 : arg0->unk_68;
            if (arg0->unk_60 < arg0->unk_5C) {
                var_a2 = (temp_lo_5 - arg0->unk_60) - arg0->unk_00.unk_3E;
                arg0->unk_60 += (temp_lo_6 < var_a2) ? temp_lo_6 : var_a2;
            }
            arg0->unk_00.unk_38 = arg0->unk_5C / arg0->unk_00.unk_3E;
            var_a2 = (temp_lo_5 - arg0->unk_58) - temp_lo_6;
            if (var_a2 <= 0) {
                var_a2 = 0;
            }

            arg0->unk_58 += (var_a2 < arg0->unk_68) ? var_a2 : arg0->unk_68;
            if (temp_t3 != arg0->unk_60) {
                var_t2 |= 0x80000000;
            }
        }
    }

    if (arg0->unk_56 == 0) {
        var_t2 = 0;
    } else {
        var_t2 |= 8;
        if (var_t4 == 0) {
            var_t2 |= 1;
        }
    }
    return var_t2;
}

void ScrollListFragment_SetRows(unk_func_8820BE14_02C_038* arg0, s32 arg1) {
    s32 temp_v1;
    s32 var_a3;

    arg0->unk_6C = 0;
    arg0->unk_5C = arg0->unk_00.unk_3E * arg1;
    arg0->unk_00.unk_38 = arg1;

    if (arg0->unk_5C < arg0->unk_58) {
        arg0->unk_58 = arg0->unk_5C;
        return;
    }

    temp_v1 = (arg0->unk_5C + arg0->unk_00.unk_3E) - (arg0->unk_00.unk_4A * arg0->unk_00.unk_3E);
    if (arg0->unk_58 < temp_v1) {
        arg0->unk_58 = temp_v1;
        return;
    }

    if (arg0->unk_00.unk_4A >= arg0->unk_00.unk_2C->unk_08) {
        var_a3 = 0;
    } else {
        var_a3 = (arg0->unk_00.unk_2C->unk_08 - arg0->unk_00.unk_4A) * arg0->unk_00.unk_3E;
    }

    if (var_a3 < arg0->unk_58) {
        arg0->unk_58 = var_a3;
    }
}

void ScrollListFragment_SetRowsAlt(unk_func_8820BE14_02C_038* arg0, s32 arg1) {
    s32 temp_a2;
    s32 temp_v0;
    s32 var_a1;
    s32 var_v0;

    arg0->unk_6C = 0;
    arg0->unk_00.unk_38 = arg1;
    temp_v0 = arg0->unk_5C - arg0->unk_58;
    arg0->unk_5C = arg0->unk_00.unk_3E * arg1;

    temp_a2 = arg0->unk_00.unk_2C->unk_08 - arg0->unk_00.unk_4A;

    var_a1 = temp_a2 = (temp_a2 > 0) ? temp_a2 : 0;
    temp_a2 *= arg0->unk_00.unk_3E;

    var_v0 = (arg0->unk_5C - temp_v0 > 0) ? arg0->unk_5C - temp_v0 : 0;

    if (var_v0 < temp_a2) {
        arg0->unk_58 = var_v0;
    } else {
        arg0->unk_58 = temp_a2;
    }
}

void ScrollListFragment_SetRowAndOffset(unk_func_8830867C_02C_034* arg0, s32 arg1, s32 arg2) {
    s32 temp_a2;
    s32 temp_a2_2;
    s32 temp_lo;
    s32 temp_v1;
    s32 var_v0_2;

    if (arg0->unk_00.unk_2C->unk_08 != 0) {
        arg0->unk_6C = 0;
        temp_v1 = arg0->unk_00.unk_2C->unk_08 - 1;
        if (arg1 >= temp_v1) {
            arg1 = temp_v1;
        }
        arg0->unk_00.unk_38 = arg1;
        arg0->unk_5C = arg0->unk_00.unk_3E * arg1;

        temp_a2 = arg0->unk_00.unk_2C->unk_08 - arg0->unk_00.unk_4A;
        temp_lo = ((temp_a2 > 0) ? temp_a2 : 0) * arg0->unk_00.unk_3E;

        temp_a2_2 = arg0->unk_5C - (arg2 * arg0->unk_00.unk_3E);
        if (temp_a2_2 > 0) {
            var_v0_2 = temp_a2_2;
        } else {
            var_v0_2 = 0;
        }

        if (var_v0_2 < temp_lo) {
            arg0->unk_58 = var_v0_2;
        } else {
            arg0->unk_58 = temp_lo;
        }
    }
}

void PtrList_InsertAtSelection(unk_func_8820BE14_02C_038* arg0, unk_func_88205880_00D0* arg1) {
    PtrList_Insert(arg0->unk_00.unk_2C, arg1, arg0->unk_00.unk_38);
}

void PtrList_RemoveCurrentAndAdjust(unk_func_8820BE14_02C_038* arg0) {
    s32 var_a1;

    PtrArray_RemoveAt(arg0->unk_00.unk_2C, arg0->unk_00.unk_38);
    var_a1 = arg0->unk_00.unk_38;
    if ((var_a1 >= arg0->unk_00.unk_2C->unk_08) && (var_a1 > 0)) {
        var_a1 = arg0->unk_00.unk_2C->unk_08 - 1;
        arg0->unk_00.unk_38 = var_a1;
    }
    ScrollListFragment_SetRowsAlt(arg0, var_a1);
}

void ItemSlot_Create(unk_func_88507D4C* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, unk_func_8820BE14_02C_038* arg5) {
    func_885007CC(&arg0->unk_00, sizeof(unk_func_88507D4C));
    arg0->unk_00.unk_18 = MoveInfoFragment_Draw;
    arg0->unk_00.unk_10.unk_00 = arg1;
    arg0->unk_00.unk_10.unk_02 = arg2;
    arg0->unk_00.unk_14.unk_00 = arg3;
    arg0->unk_00.unk_14.unk_02 = 0x10;
    arg0->unk_30 = arg4;
    arg0->unk_2C = arg5;
}

s32 MoveInfoFragment_Draw(unk_func_88507D4C* arg0, s32 arg1, s32 arg2) {
    s32 sp12C;
    s32 temp_s0;
    s32 w = 8;
    s32 h = 16;

    sp12C = arg0->unk_2C->unk_00.unk_3E * arg0->unk_2C->unk_00.unk_4A;
    temp_s0 = ((arg0->unk_00.unk_14.unk_00 / 2) + arg1) - 9;

    gDPPipeSync(gDisplayListHead++);
    gDPSetCycleType(gDisplayListHead++, G_CYC_1CYCLE);
    gDPSetRenderMode(gDisplayListHead++, G_RM_OPA_SURF, G_RM_OPA_SURF2);
    gDPSetTexturePersp(gDisplayListHead++, G_TP_NONE);
    gDPSetTextureFilter(gDisplayListHead++, G_TF_POINT);
    gDPSetCombineMode(gDisplayListHead++, G_CC_DECALRGBA, G_CC_DECALRGBA);

    gDPLoadTextureBlock(gDisplayListHead++, D_40022E0, G_IM_FMT_I, G_IM_SIZ_8b, w, h, 0, G_TX_NOMIRROR | G_TX_WRAP,
                        G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    gSPTextureRectangle(gDisplayListHead++, arg1 << 2, arg2 << 2, (arg0->unk_00.unk_14.unk_00 + arg1) << 2,
                        (arg2 + 0x10) << 2, G_TX_RENDERTILE, 0, 0, 0x0400, 0x0400);

    gDPPipeSync(gDisplayListHead++);
    gDPSetCycleType(gDisplayListHead++, G_CYC_COPY);
    gDPSetRenderMode(gDisplayListHead++, G_RM_NOOP, G_RM_NOOP2);
    gDPSetAlphaCompare(gDisplayListHead++, G_AC_THRESHOLD);
    gDPSetTexturePersp(gDisplayListHead++, G_TP_NONE);

    if (arg0->unk_30 == 0) {
        gDPLoadTextureBlock(gDisplayListHead++, (arg0->unk_2C->unk_58 > 0) ? D_4002368 : D_4002D88, G_IM_FMT_RGBA,
                            G_IM_SIZ_16b, 20, 16, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK,
                            G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
        gSPTextureRectangle(gDisplayListHead++, temp_s0 << 2, arg2 << 2, (temp_s0 + 0x11) << 2, (arg2 + 0xF) << 2,
                            G_TX_RENDERTILE, 0, 0, 0x1000, 0x0400);

        gDPLoadTextureBlock(gDisplayListHead++, (arg0->unk_2C->unk_58 > 0) ? D_4002878 : D_4003298, G_IM_FMT_RGBA,
                            G_IM_SIZ_16b, 20, 16, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK,
                            G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
        gSPTextureRectangle(gDisplayListHead++, (temp_s0 - 0x1C) << 2, arg2 << 2, (temp_s0 - 9) << 2, (arg2 + 0xF) << 2,
                            G_TX_RENDERTILE, 0, 0, 0x1000, 0x0400);
    } else {
        s32 var_t5 = 0;

        if ((arg0->unk_2C->unk_00.unk_2C != NULL) &&
            ((arg0->unk_2C->unk_58 + sp12C) < (arg0->unk_2C->unk_00.unk_3E * arg0->unk_2C->unk_00.unk_2C->unk_08))) {
            var_t5 = 1;
        }

        gDPLoadTextureBlock(gDisplayListHead++, (var_t5 != 0) ? D_40025F0 : D_4003010, G_IM_FMT_RGBA, G_IM_SIZ_16b, 20,
                            16, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK,
                            G_TX_NOLOD, G_TX_NOLOD);
        gSPTextureRectangle(gDisplayListHead++, temp_s0 << 2, arg2 << 2, (temp_s0 + 0x11) << 2, (arg2 + 0xF) << 2,
                            G_TX_RENDERTILE, 0, 0, 0x1000, 0x0400);

        gDPLoadTextureBlock(gDisplayListHead++, (var_t5 != 0) ? D_4002B00 : D_4003520, G_IM_FMT_RGBA, G_IM_SIZ_16b, 20,
                            16, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK,
                            G_TX_NOLOD, G_TX_NOLOD);
        gSPTextureRectangle(gDisplayListHead++, (temp_s0 + 0x1A) << 2, arg2 << 2, (temp_s0 + 0x2D) << 2,
                            (arg2 + 0xF) << 2, G_TX_RENDERTILE, 0, 0, 0x1000, 0x0400);
    }

    gDPPipeSync(gDisplayListHead++);
    gDPSetAlphaCompare(gDisplayListHead++, G_AC_NONE);
    return 0;
}

void TextObject_Create(unk_func_8850878C* arg0, s32 arg1, s32 arg2, char* arg3, s32 arg4) {
    Color_RGBA8 Color_TextDefault = { 240, 240, 240, 255 };

    ((func885007CC)Memmap_GetFragmentVaddr(func_885007CC))(arg0, sizeof(unk_func_8850878C));
    arg0->unk_00.unk_18 = SimpleTextFragment_Draw;
    arg0->unk_00.unk_10.unk_00 = arg1;
    arg0->unk_00.unk_10.unk_02 = arg2;
    arg0->unk_40 = arg3;
    arg0->unk_2C = arg4;
    arg0->unk_30 = Color_TextDefault;
    arg0->unk_38 = 0;
    arg0->unk_3C = 0x28;
    arg0->unk_44 = 0;
}

s32 SimpleTextFragment_Draw(unk_func_8850878C* arg0, s32 arg1, s32 arg2) {
    if (arg0->unk_40 == NULL) {
        return 0;
    }
    Text_ResetState();
    Text_SetFont(arg0->unk_2C, arg0->unk_38);
    Text_SetEnvColor(arg0->unk_30.r, arg0->unk_30.g, arg0->unk_30.b, arg0->unk_30.a);
    if (arg0->unk_44 != 0) {
        Text_BeginRender();
        Text_SetPrimColor(arg0->unk_34.r, arg0->unk_34.g, arg0->unk_34.b, arg0->unk_34.a);
    }
    Text_SetLineHeight(arg0->unk_3C);
    Text_Print(arg1, arg2, arg0->unk_40);
    if (arg0->unk_44 != 0) {
        Text_EndRender();
    }
    Text_SetupDL();
    return 0;
}

void ProgressBarFragment_Create(unk_func_885088F4* arg0, s32 arg1, s32 arg2, s32 arg3) {
    func_885007CC(&arg0->unk_00, sizeof(unk_func_885088F4));
    arg0->unk_00.unk_1C = ProgressBarFragment_Update;
    arg0->unk_00.unk_18 = ProgressBarFragment_Draw;
    arg0->unk_00.unk_10.unk_00 = 0;
    arg0->unk_00.unk_14.unk_00 = 0x280;
    arg0->unk_00.unk_14.unk_02 = arg1;
    arg0->unk_2C = -1;
    arg0->unk_00.unk_10.unk_02 = -arg0->unk_00.unk_14.unk_02;
    arg0->unk_30 = 0;
    arg0->unk_34 = arg2;
    arg0->unk_38 = arg3;
}

s32 ProgressBarFragment_Update(unk_func_885088F4* arg0) {
    arg0->unk_2C++;
    if (arg0->unk_2C < 6) {
        arg0->unk_30 = 1;
    } else if (arg0->unk_2C >= 0x10) {
        arg0->unk_2C = -1;
        arg0->unk_00.unk_10.unk_02 = -arg0->unk_00.unk_14.unk_02;
        arg0->unk_30 = 0;
        arg0->unk_00.unk_28 &= ~1;
    } else if (arg0->unk_2C >= 0xA) {
        arg0->unk_30 = 4;
    } else {
        arg0->unk_30 = 2;
        if (arg0->unk_2C == 9) {
            arg0->unk_2C--;
        } else if (arg0->unk_2C < 8) {
            arg0->unk_30 |= 8;
        }
    }

    if (arg0->unk_30 & 4) {
        s32 tmp = 0xF - arg0->unk_2C;

        arg0->unk_00.unk_10.unk_02 = ((arg0->unk_00.unk_14.unk_02 * tmp) / 6) - arg0->unk_00.unk_14.unk_02;
    } else if (arg0->unk_30 & 1) {
        s32 tmp = arg0->unk_2C;

        arg0->unk_00.unk_10.unk_02 = ((arg0->unk_00.unk_14.unk_02 * tmp) / 6) - arg0->unk_00.unk_14.unk_02;
    } else {
        arg0->unk_00.unk_10.unk_02 = 0;
    }
    return 0;
}

s32 ProgressBarFragment_Draw(unk_func_885088F4* arg0, s32 arg1, s32 arg2) {
    static Color_RGBA8 Color_ProgressBarFill = { 0x38, 0x38, 0x68, 0xFF };

    u32 color = RGBA5551(Color_ProgressBarFill.r, Color_ProgressBarFill.g, Color_ProgressBarFill.b, 1);

    gDPPipeSync(gDisplayListHead++);
    gDPSetCycleType(gDisplayListHead++, G_CYC_FILL);
    gDPSetRenderMode(gDisplayListHead++, G_RM_NOOP, G_RM_NOOP2);
    gDPSetFillColor(gDisplayListHead++, (color << 0x10) | color);

    gDPFillRectangle(gDisplayListHead++, CLAMP_MAX(arg1, 0), CLAMP_MAX(arg2, 0), CLAMP_MAX(arg1 + 0x27F, 0),
                     CLAMP_MAX((arg0->unk_00.unk_14.unk_02 + arg2) - 0x16, 0));

    gDPFillRectangle(gDisplayListHead++, CLAMP_MAX(arg1, 0), CLAMP_MAX((arg0->unk_00.unk_14.unk_02 + arg2) - 0x15, 0),
                     CLAMP_MAX((arg0->unk_34 + arg1) - 1, 0), CLAMP_MAX((arg0->unk_00.unk_14.unk_02 + arg2) - 6, 0));

    gDPFillRectangle(gDisplayListHead++, CLAMP_MAX((arg1 - arg0->unk_38) + 0x280, 0),
                     CLAMP_MAX((arg0->unk_00.unk_14.unk_02 + arg2) - 0x15, 0), CLAMP_MAX(arg1 + 0x27F, 0),
                     CLAMP_MAX((arg0->unk_00.unk_14.unk_02 + arg2) - 6, 0));

    gDPPipeSync(gDisplayListHead++);
    gDPSetCycleType(gDisplayListHead++, G_CYC_1CYCLE);
    gDPSetRenderMode(gDisplayListHead++, G_RM_OPA_SURF, G_RM_OPA_SURF2);
    gDPSetTexturePersp(gDisplayListHead++, G_TP_NONE);
    gDPSetTextureFilter(gDisplayListHead++, G_TF_POINT);
    gDPSetCombineMode(gDisplayListHead++, G_CC_MODULATEI_PRIM, G_CC_MODULATEI_PRIM);
    gDPSetPrimColor(gDisplayListHead++, 0, 0, Color_ProgressBarFill.r, Color_ProgressBarFill.g, Color_ProgressBarFill.b, Color_ProgressBarFill.a);

    gDPLoadTextureBlock(gDisplayListHead++, D_4007948, G_IM_FMT_IA, G_IM_SIZ_8b, 8, 5, 0, G_TX_NOMIRROR | G_TX_WRAP,
                        G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

    gSPScisTextureRectangle(gDisplayListHead++, arg1 << 2, ((arg0->unk_00.unk_14.unk_02 + arg2) - 5) << 2,
                            (arg0->unk_34 + arg1) << 2, (arg0->unk_00.unk_14.unk_02 + arg2) << 2, G_TX_RENDERTILE, 0, 0,
                            0x400, 0x400);

    gSPScisTextureRectangle(gDisplayListHead++, ((arg1 - arg0->unk_38) + 0x280) << 2,
                            ((arg0->unk_00.unk_14.unk_02 + arg2) - 5) << 2, (arg1 + 0x280) << 2,
                            (arg0->unk_00.unk_14.unk_02 + arg2) << 2, G_TX_RENDERTILE, 0, 0, 0x400, 0x400);

    gSPScisTextureRectangle(gDisplayListHead++, (arg0->unk_34 + arg1 + 0x10) << 2,
                            ((arg0->unk_00.unk_14.unk_02 + arg2) - 0x15) << 2, ((arg1 - arg0->unk_38) + 0x270) << 2,
                            ((arg0->unk_00.unk_14.unk_02 + arg2) - 0x10) << 2, G_TX_RENDERTILE, 0, 0, 0x400, 0x400);

    gDPPipeSync(gDisplayListHead++);
    gDPSetRenderMode(gDisplayListHead++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
    gDPSetCombineMode(gDisplayListHead++, G_CC_MODULATEIDECALA_PRIM, G_CC_MODULATEIDECALA_PRIM);

    gDPLoadTextureBlock(gDisplayListHead++, D_4007978, G_IM_FMT_IA, G_IM_SIZ_8b, 16, 21, 0, G_TX_NOMIRROR | G_TX_WRAP,
                        G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

    gSPScisTextureRectangle(gDisplayListHead++, (arg0->unk_34 + arg1) << 2,
                            ((arg0->unk_00.unk_14.unk_02 + arg2) - 0x15) << 2, ((arg1 - arg0->unk_38) + 0x270) << 2,
                            (arg0->unk_00.unk_14.unk_02 + arg2) << 2, G_TX_RENDERTILE, 0, 0, 0x400, 0x400);

    gDPLoadTextureBlock(gDisplayListHead++, D_4007978, G_IM_FMT_IA, G_IM_SIZ_8b, 16, 21, 0, G_TX_MIRROR | G_TX_WRAP,
                        G_TX_NOMIRROR | G_TX_WRAP, 4, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

    gSPScisTextureRectangle(gDisplayListHead++, ((arg1 - arg0->unk_38) + 0x270) << 2,
                            ((arg0->unk_00.unk_14.unk_02 + arg2) - 0x15) << 2, ((arg1 - arg0->unk_38) + 0x280) << 2,
                            (arg0->unk_00.unk_14.unk_02 + arg2) << 2, G_TX_RENDERTILE, 0x200, 0, 0x400, 0x400);

    return 0;
}

void TrainerMoveInfoFragment_Create(unk_func_88509A2C* arg0, s32 arg1, s32 arg2, s32 arg3, char* arg4) {
    func_885007CC(&arg0->unk_00, sizeof(unk_func_88509A2C));
    arg0->unk_00.unk_18 = TrainerMoveInfoFragment_Draw;
    arg0->unk_00.unk_10.unk_00 = arg1;
    arg0->unk_00.unk_10.unk_02 = arg2;
    // clang-format off
    arg0->unk_00.unk_14.unk_00 = 0x124; arg0->unk_00.unk_14.unk_02 = 0x18;
    // clang-format on
    arg0->unk_2C = arg3;

    if (arg3 != -1) {
        if (MenuItem_GetPokemonSpecies(arg3) != 0) {
            arg0->unk_30 = 1;
        } else {
            arg0->unk_30 = 0;
            arg0->unk_38 = func_80025084(arg3);
            SaveSlot_GetTrainerName(arg3, arg0->unk_40);
        }
        arg0->unk_34 = GetMoveTargetType(MenuItem_GetHeldItemId(arg3));
    }
    arg0->unk_3C = arg4;
}

s32 TrainerMoveInfoFragment_Draw(unk_func_88509A2C* arg0, s32 arg1, s32 arg2) {
    static Gfx* Gfx_MoveTargetIcons[] = { D_04005C48, D_04005F70, D_04006298, D_040065C0 };
    static Color_RGBA8 Color_TrainerInfoEnv = { 0xF0, 0xF0, 0xF0, 0xFF };

    char* var_a2;

    if (arg0->unk_2C != -1) {
        Text_ResetState();
        Text_SetEnvColor(Color_TrainerInfoEnv.r, Color_TrainerInfoEnv.g, Color_TrainerInfoEnv.b, Color_TrainerInfoEnv.a);
        Text_SetFont(0x10, 0);
        Text_Print(arg1 + 0x1A, arg2, "%dP", arg0->unk_2C + 1);
        if (arg0->unk_30 == 0) {
            var_a2 = arg0->unk_40;
        } else {
            var_a2 = "?????";
        }
        Text_Print(arg1 + 0x48, arg2, var_a2);
        Text_SetFont(4, 0);
        if (arg0->unk_30 == 0) {
            Text_Print(arg1 + 0xBB, arg2 + 8, "%s %05d", arg0->unk_3C, arg0->unk_38);
        } else {
            Text_Print(arg1 + 0xBB, arg2 + 8, "%s ?????", arg0->unk_3C);
        }
        Text_SetupDL();

        gDPPipeSync(gDisplayListHead++);
        gDPSetCycleType(gDisplayListHead++, G_CYC_COPY);
        gDPSetRenderMode(gDisplayListHead++, G_RM_NOOP, G_RM_NOOP2);
        gDPSetAlphaCompare(gDisplayListHead++, G_AC_THRESHOLD);
        gDPSetTexturePersp(gDisplayListHead++, G_TP_NONE);

        gDPLoadTextureBlock(gDisplayListHead++, Gfx_MoveTargetIcons[arg0->unk_34], G_IM_FMT_RGBA, G_IM_SIZ_16b, 20, 20, 0,
                            G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                            G_TX_NOLOD);
        gSPTextureRectangle(gDisplayListHead++, arg1 << 2, (arg2 + 4) << 2, (arg1 + 0x13) << 2, (arg2 + 0x17) << 2,
                            G_TX_RENDERTILE, 0, 0, 0x1000, 0x0400);

        gDPPipeSync(gDisplayListHead++);
        gDPSetAlphaCompare(gDisplayListHead++, G_AC_NONE);
    }
    return 0;
}

void LabelFragment_Create(unk_func_88509E34* arg0, s32 arg1, s32 arg2, char* arg3) {
    func_885007CC(&arg0->unk_00, sizeof(unk_func_88509E34));
    arg0->unk_00.unk_00.unk_18 = LabelFragment_Draw;
    arg0->unk_00.unk_00.unk_10.unk_00 = arg1;
    arg0->unk_00.unk_00.unk_10.unk_02 = arg2;
    arg0->unk_00.unk_2C = arg3;
}

s32 LabelFragment_Draw(unk_func_88509F0C* arg0, s32 arg1, s32 arg2) {
    static Color_RGBA8 Color_LabelEnv = { 0xF0, 0xF0, 0xF0, 0xFF };

    Text_ResetState();
    Text_SetFont(8, 0);
    Text_SetEnvColor(Color_LabelEnv.r, Color_LabelEnv.g, Color_LabelEnv.b, Color_LabelEnv.a);
    Text_Print(arg1 + 0x1AC, arg2 + 0x26, arg0->unk_2C);
    Text_SetupDL();
    return 0;
}

void func_88509F0C(unk_func_88509F0C* arg0) {
    ((func885007CC)Memmap_GetFragmentVaddr(func_885007CC))(arg0, sizeof(unk_func_88509F0C));
    arg0->unk_2C = 0;
}

void TextObjectGraphics_Init(TextObjectGraphics* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, MemoryPool* arg5,
                   TextObject* arg6) {
    static Color_RGBA8 Color_DarkRed = { 0x64, 0x1E, 0x1E, 0xFF };

    ((func885007CC)Memmap_GetFragmentVaddr(func_885007CC))(arg0, sizeof(TextObjectGraphics));
    arg0->unk_00.unk_20 = func_8850A29C;
    arg0->unk_00.unk_10.unk_00 = arg1;
    arg0->unk_00.unk_10.unk_02 = arg2;
    arg0->unk_00.unk_14.unk_00 = arg3;
    arg0->unk_00.unk_14.unk_02 = arg4;

    arg0->unk_2C = mem_pool_alloc(arg5, sizeof(unk_func_88001300_038));
    ((func88502274)Memmap_GetFragmentVaddr(Fragment_SetRect))(arg0->unk_2C, 0, 0, 0x10, 0x10);
    arg0->unk_2C->unk_00.unk_28 |= 0x200;
    arg0->unk_2C->unk_00.unk_28 |= 0x400;
    arg0->unk_2C->unk_00.unk_28 &= ~1;
    ((func8850068C)Memmap_GetFragmentVaddr(Fragment_SetChild))(arg0, arg0->unk_2C);

    arg0->unk_30 = mem_pool_alloc(arg5, sizeof(unk_func_885012A4));
    ((func885012A4)Memmap_GetFragmentVaddr(UIFrame_Create))(arg0->unk_30, 0, 0, 0x10, 0x10, Color_DarkRed);
    ((func8850068C)Memmap_GetFragmentVaddr(Fragment_SetChild))(arg0->unk_2C, arg0->unk_30);
    arg0->unk_34 = mem_pool_alloc(arg5, sizeof(unk_func_8850878C));
    ((func8850878C)Memmap_GetFragmentVaddr(TextObject_Create))(arg0->unk_34, 0, 0, "-----", 0x10);
    ((func8850068C)Memmap_GetFragmentVaddr(Fragment_SetChild))(arg0->unk_30, arg0->unk_34);
    arg0->unk_34->unk_00.unk_28 &= ~1;
    arg0->unk_38 = arg6;
}

void TextBox_Configure(TextObjectGraphics* arg0, unk_func_8850878C* arg1, s32 arg2, s32 arg3) {
    s16 temp_v1;

    *arg0->unk_34 = *arg1;
    arg0->unk_34->unk_00.unk_28 |= 1;
    Text_SetFont(arg1->unk_2C, arg1->unk_38);
    Text_SetLineHeight(arg1->unk_3C);

    if (arg3 == 0) {
        arg3 = MeasureTextWidth(0, 0, arg1->unk_40);
    }

    if (arg2 == 0) {
        arg2 = CountTextLines(arg1->unk_40);
    }

    temp_v1 = arg0->unk_38->unk_00[arg0->unk_38->unk_50].unk_02;

    arg0->unk_2C->unk_00.unk_14.unk_00 = temp_v1 + arg3;

    arg0->unk_2C->unk_00.unk_14.unk_02 = (((arg1->unk_3C * arg2) + temp_v1) - arg1->unk_3C) + temp_v1;
    arg0->unk_2C->unk_00.unk_10.unk_00 = (arg0->unk_00.unk_14.unk_00 - arg0->unk_2C->unk_00.unk_14.unk_00) / 2;
    arg0->unk_2C->unk_00.unk_10.unk_02 = (arg0->unk_00.unk_14.unk_02 - arg0->unk_2C->unk_00.unk_14.unk_02) / 2;

    arg0->unk_30->unk_00.unk_14 = arg0->unk_2C->unk_00.unk_14;

    arg0->unk_34->unk_00.unk_10.unk_00 = temp_v1 / 2;
    arg0->unk_34->unk_00.unk_10.unk_02 = temp_v1 / 2;
}

s32 func_8850A29C(TextObjectGraphics* arg0, Controller* arg1) {
    s32 var_v1 = 0;

    if (arg0->unk_2C->unk_30 & 2) {
        if (arg1->buttonPressed & 0xC000) {
            var_v1 = 0x80000002;
        }
    } else {
        var_v1 = 1;
    }

    return var_v1;
}

void Menu_ResetState(TextObjectGraphics* arg0) {
    UIAnimatedElement_WaitForInput(arg0->unk_2C);
}

void Menu_SetActiveFlag(TextObjectGraphics* arg0) {
    arg0->unk_2C->unk_2C = 0xB;
}

void func_8850A30C(TextObjectGraphics* arg0, Controller* arg1, s32 arg2) {
    s32 temp_v0;
    s32 var_s0 = 0;

    Menu_ResetState(arg0);

    while (var_s0 == 0) {
        ControllerMsgQueue_SendAndRead(var_s0);

        temp_v0 = arg0->unk_00.unk_20(arg0, arg1);
        if (!(temp_v0 & 1) && (temp_v0 & 2)) {
            var_s0 = 1;
        }

        if (arg2 != 0) {
            ((func8850BC94)Memmap_GetFragmentVaddr(Fragment_HandleResult))(temp_v0);
        }
    }

    Menu_SetActiveFlag(arg0);
}

void Menu_WaitForConfirm(TextObjectGraphics* arg0, Controller* arg1) {
    func_8850A30C(arg0, arg1, 1);
}

void Menu_WaitForCancel(TextObjectGraphics* arg0, Controller* arg1) {
    func_8850A30C(arg0, arg1, 0);
}

void WindowBorder_Init(unk_func_88001300_000* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    ((func885007CC)Memmap_GetFragmentVaddr(func_885007CC))(arg0, sizeof(unk_func_88001300_000));
    arg0->unk_18 = WindowBorder_Draw;
    arg0->unk_10.unk_00 = arg1;
    arg0->unk_10.unk_02 = arg2;
    arg0->unk_14.unk_00 = arg3;
    arg0->unk_14.unk_02 = arg4;
}

s32 WindowBorder_Draw(unk_func_88001300_000* arg0, s32 arg1, s32 arg2) {
    gDPPipeSync(gDisplayListHead++);

    gDPSetCycleType(gDisplayListHead++, G_CYC_1CYCLE);
    gDPSetRenderMode(gDisplayListHead++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
    gDPSetTexturePersp(gDisplayListHead++, G_TP_NONE);
    gDPSetTextureFilter(gDisplayListHead++, G_TF_POINT);
    gDPSetCombineMode(gDisplayListHead++, G_CC_DECALRGBA, G_CC_DECALRGBA);

    gDPLoadTextureBlock(gDisplayListHead++, D_4001638, G_IM_FMT_IA, G_IM_SIZ_8b, 8, 8, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    gSPTextureRectangle(gDisplayListHead++, arg1 << 2, arg2 << 2, ((arg0->unk_14.unk_00 + arg1) - 8) << 2,
                        (arg2 + 8) << 2, G_TX_RENDERTILE, 0, 0, 0x0400, 0x0400);

    gDPLoadTextureBlock(gDisplayListHead++, D_4001710, G_IM_FMT_IA, G_IM_SIZ_8b, 8, 8, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    gSPTextureRectangle(gDisplayListHead++, ((arg0->unk_14.unk_00 + arg1) - 8) << 2, arg2 << 2,
                        (arg0->unk_14.unk_00 + arg1) << 2, ((arg2 + arg0->unk_14.unk_02) - 8) << 2, G_TX_RENDERTILE, 0,
                        0, 0x0400, 0x0400);

    gDPLoadTextureBlock(gDisplayListHead++, D_40016C8, G_IM_FMT_IA, G_IM_SIZ_8b, 8, 8, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    gSPTextureRectangle(gDisplayListHead++, (arg1 + 8) << 2, ((arg2 + arg0->unk_14.unk_02) - 8) << 2,
                        (arg0->unk_14.unk_00 + arg1) << 2, (arg2 + arg0->unk_14.unk_02) << 2, G_TX_RENDERTILE,
                        (arg0->unk_14.unk_00 * -0x20) + 0x200, 0, 0x0400, 0x0400);

    gDPLoadTextureBlock(gDisplayListHead++, D_4001680, G_IM_FMT_IA, G_IM_SIZ_8b, 8, 8, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    gSPTextureRectangle(gDisplayListHead++, arg1 << 2, (arg2 + 8) << 2, (arg1 + 8) << 2,
                        (arg2 + arg0->unk_14.unk_02) << 2, G_TX_RENDERTILE, 0, (arg0->unk_14.unk_02 * -0x20) + 0x200,
                        0x0400, 0x0400);
    return 0;
}

void DialogBox_Init(unk_func_88001300_000* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    ((func885007CC)Memmap_GetFragmentVaddr(func_885007CC))(arg0, sizeof(unk_func_88001300_000));
    arg0->unk_18 = DialogBox_Draw;
    arg0->unk_10.unk_00 = arg1;
    arg0->unk_10.unk_02 = arg2;
    arg0->unk_14.unk_00 = arg3;
    arg0->unk_14.unk_02 = arg4;
}

s32 DialogBox_Draw(unk_func_88001300_000* arg0, s32 arg1, s32 arg2) {
    s32 spE4;
    s32 spE0;
    s32 spDC;
    s32 spD8;

    // clang-format off
    spE4 = arg1 - 2; spE0 = arg2 - 2;
    // clang-format on
    spDC = arg0->unk_14.unk_00 + 4;
    spD8 = arg0->unk_14.unk_02 + 4;

    gDPPipeSync(gDisplayListHead++);

    gDPSetCycleType(gDisplayListHead++, G_CYC_1CYCLE);
    gDPSetRenderMode(gDisplayListHead++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
    gDPSetTexturePersp(gDisplayListHead++, G_TP_NONE);
    gDPSetTextureFilter(gDisplayListHead++, G_TF_POINT);
    gDPSetCombineMode(gDisplayListHead++, G_CC_DECALRGBA, G_CC_DECALRGBA);

    gDPLoadTextureBlock(gDisplayListHead++, D_40068E8, G_IM_FMT_IA, G_IM_SIZ_8b, 8, 8, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    gSPTextureRectangle(gDisplayListHead++, spE4 << 2, spE0 << 2, ((spE4 + spDC) - 8) << 2, (spE0 + 8) << 2,
                        G_TX_RENDERTILE, 0, 0, 0x0400, 0x0400);

    gDPLoadTextureBlock(gDisplayListHead++, D_40069C0, G_IM_FMT_IA, G_IM_SIZ_8b, 8, 8, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    gSPTextureRectangle(gDisplayListHead++, ((spE4 + spDC) - 8) << 2, spE0 << 2, (spE4 + spDC) << 2,
                        ((spE0 + spD8) - 8) << 2, G_TX_RENDERTILE, 0, 0, 0x0400, 0x0400);

    gDPLoadTextureBlock(gDisplayListHead++, D_4006978, G_IM_FMT_IA, G_IM_SIZ_8b, 8, 8, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    gSPTextureRectangle(gDisplayListHead++, (spE4 + 8) << 2, ((spE0 + spD8) - 8) << 2, (spE4 + spDC) << 2,
                        (spE0 + spD8) << 2, G_TX_RENDERTILE, (spDC * -0x20) + 0x200, 0, 0x0400, 0x0400);

    gDPLoadTextureBlock(gDisplayListHead++, D_4006930, G_IM_FMT_IA, G_IM_SIZ_8b, 8, 8, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    gSPTextureRectangle(gDisplayListHead++, spE4 << 2, (spE0 + 8) << 2, (spE4 + 8) << 2, (spE0 + spD8) << 2,
                        G_TX_RENDERTILE, 0, (spD8 * -0x20) + 0x200, 0x0400, 0x0400);
    return 0;
}

void UIList_Create(unk_func_8850B254* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, Color_RGBA8 arg5,
                   Color_RGBA8 arg6) {
    func_885007CC(&arg0->unk_00, sizeof(unk_func_8850B254));
    arg0->unk_00.unk_18 = ColoredBox_Draw;
    arg0->unk_00.unk_10.unk_00 = arg1;
    arg0->unk_00.unk_10.unk_02 = arg2;
    arg0->unk_00.unk_14.unk_00 = arg3;
    arg0->unk_00.unk_14.unk_02 = arg4;
    arg0->unk_2C = arg5;
    arg0->unk_30 = arg6;
}

s32 ColoredBox_Draw(unk_func_8850B254* arg0, s32 arg1, s32 arg2) {
    s32 h = 8;
    s32 w = 8;

    gDPPipeSync(gDisplayListHead++);

    gDPSetCycleType(gDisplayListHead++, G_CYC_1CYCLE);
    gDPSetRenderMode(gDisplayListHead++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
    gDPSetTexturePersp(gDisplayListHead++, G_TP_NONE);
    gDPSetTextureFilter(gDisplayListHead++, G_TF_POINT);
    gDPSetCombineMode(gDisplayListHead++, G_CC_MODULATEIDECALA_PRIM, G_CC_MODULATEIDECALA_PRIM);
    gDPSetPrimColor(gDisplayListHead++, 0, 0, arg0->unk_2C.r, arg0->unk_2C.g, arg0->unk_2C.b, arg0->unk_2C.a);

    gDPLoadTextureBlock(gDisplayListHead++, D_4007AD0, G_IM_FMT_IA, G_IM_SIZ_8b, w, h, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    gSPTextureRectangle(gDisplayListHead++, (arg1 - 7) << 2, (arg2 - 7) << 2,
                        ((arg1 - 1) + arg0->unk_00.unk_14.unk_00) << 2, ((arg2 - 7) + h) << 2, G_TX_RENDERTILE, 0, 0, 0x0400,
                        0x0400);

    gDPLoadTextureBlock(gDisplayListHead++, D_4007B18, G_IM_FMT_IA, G_IM_SIZ_8b, w, h, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    gSPTextureRectangle(gDisplayListHead++, ((arg1 - 1) + arg0->unk_00.unk_14.unk_00) << 2, (arg2 - 7) << 2,
                        ((arg1 + 7) + arg0->unk_00.unk_14.unk_00) << 2, ((arg2 - 1) + arg0->unk_00.unk_14.unk_02) << 2,
                        G_TX_RENDERTILE, 0, 0, 0x0400, 0x0400);

    gDPLoadTextureBlock(gDisplayListHead++, D_4007B60, G_IM_FMT_IA, G_IM_SIZ_8b, w, h, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    gSPTextureRectangle(gDisplayListHead++, ((arg1 - 7) + w) << 2, ((arg2 - 1) + arg0->unk_00.unk_14.unk_02) << 2,
                        ((arg1 + 7) + arg0->unk_00.unk_14.unk_00) << 2, ((arg2 + 7) + arg0->unk_00.unk_14.unk_02) << 2,
                        G_TX_RENDERTILE, (arg0->unk_00.unk_14.unk_00 * -0x20) + 0x40, 0, 0x0400, 0x0400);

    gDPLoadTextureBlock(gDisplayListHead++, D_4007BA8, G_IM_FMT_IA, G_IM_SIZ_8b, w, h, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    gSPTextureRectangle(gDisplayListHead++, (arg1 - 7) << 2, ((arg2 - 7) + h) << 2, ((arg1 - 7) + w) << 2,
                        ((arg2 + 7) + arg0->unk_00.unk_14.unk_02) << 2, G_TX_RENDERTILE, 0,
                        (arg0->unk_00.unk_14.unk_02 * -0x20) + 0x40, 0x0400, 0x0400);

    gDPPipeSync(gDisplayListHead++);

    gDPSetCycleType(gDisplayListHead++, G_CYC_FILL);
    gDPSetRenderMode(gDisplayListHead++, G_RM_NOOP, G_RM_NOOP2);

    {
        // clang-format off
        s32 color = ((arg0->unk_30.r << 8) & 0xF800) | ((arg0->unk_30.g << 3) & 0x7C0) | ((arg0->unk_30.b >> 2) & 0x3E) | 1;gDPPipeSync(gDisplayListHead++);
        // clang-format on
        gDPSetFillColor(gDisplayListHead++, (color << 0x10) | color);
    }
    gDPFillRectangle(gDisplayListHead++, arg1, arg2, (arg0->unk_00.unk_14.unk_00 + arg1) - 1,
                     (arg2 + arg0->unk_00.unk_14.unk_02) - 1);

    return 0;
}

void Fragment_HandleResult(s32 arg0) {
    u32 var_a1 = 0;

    if (arg0 & 0x80000000) {
        arg0 &= 0x7FFFFFFF;
        arg0 &= 0x99E;

        switch (arg0) {
            case 0x2:
                var_a1 = 3;
                break;

            case 0x4:
                var_a1 = 2;
                break;

            case 0x8:
                var_a1 = 1;
                break;

            case 0x800:
                var_a1 = 0x18;
                break;

            case 0x80:
                var_a1 = 0x29;
                break;

            case 0x100:
                var_a1 = 8;
                break;
        }

        if (var_a1 != 0) {
            PlaySoundEffect(var_a1);
        }
    }
}

void MenuItemList_Init(unk_func_8850BD40* arg0, unk_func_8821421C_038_034* arg1) {
    ListNode_Init(arg0, sizeof(unk_func_8850BD40));
    arg0->unk_10 = MenuItemList_GetResult;
    arg0->unk_14 = MenuItemList_SetResult;
    arg0->unk_1C = arg1;
}

s32 MenuItemList_GetResult(unk_func_8850BD40* arg0, Controller* arg1) {
    s32 var_v1 = 0;

    if (arg0->unk_1C->unk_00.unk_00.unk_20 != NULL) {
        var_v1 = arg0->unk_1C->unk_00.unk_00.unk_20(arg0->unk_1C, arg1);
    }
    return var_v1;
}

void MenuItemList_SetResult(unk_func_8850BD40* arg0, s32 arg1) {
    arg0->unk_1C->unk_00.unk_00.unk_24(&arg0->unk_1C->unk_00.unk_00, arg1);
}

void SelectableList_Init(unk_func_8830867C_02C_048_000* arg0) {
    ListNode_Init(arg0, sizeof(unk_func_8830867C_02C_048_000));
    arg0->unk_10 = SelectableList_Update;
    arg0->unk_14 = SelectableList_SetSelected;
    arg0->unk_18 = 0;
    arg0->unk_1C = 0;
    arg0->unk_20 = 0;
}

s32 SelectableList_Update(unk_func_8830867C_02C_048_000* arg0, Controller* arg1) {
    s32 ret = 0;

    if (arg0->unk_20 > 0) {
        unk_func_8830867C_02C_048_000* var_a0 = arg0->unk_00.unk_04;
        s32 i;

        for (i = 0; i < arg0->unk_1C; i++) {
            var_a0 = var_a0->unk_00.unk_08;
        }
        ret = var_a0->unk_10(var_a0, arg1);
    }

    if (ret & 1) {
        return ret;
    }

    if (ret == 0) {
        if (arg1->buttonPressed & 0x4000) {
            ret = 0x80000002;
        } else if (arg1->buttonPressed & 0x8000) {
            ret = 0x80000004;
        }
    }

    if (ret & 2) {
        if (arg0->unk_1C > 0) {
            arg0->unk_1C--;
            SelectableList_UpdateVisuals(arg0);
            ret |= 1;
        }
    } else if (ret & 4) {
        if (arg0->unk_1C < (arg0->unk_20 - 1)) {
            arg0->unk_1C++;
            SelectableList_UpdateVisuals(arg0);
            ret |= 1;
        }
    }

    return ret;
}

void SelectableList_SetSelected(unk_func_8830867C_02C_048_000* arg0, s32 arg1) {
    arg0->unk_18 = arg1;
    SelectableList_UpdateVisuals(arg0);
}

void Screen_SetFragment(unk_func_8830867C_02C_048_000* arg0, unk_func_88001300_000_000* arg1) {
    Fragment_SetChild(&arg0->unk_00, arg1);
    arg0->unk_20++;
}

void SelectableList_UpdateVisuals(unk_func_8830867C_02C_048_000* arg0) {
    s32 temp_s3;
    s32 temp_s4;
    s32 var_v0;
    s32 var_v1;
    unk_func_8830867C_02C_048_000* var_s1;
    s32 i;

    var_s1 = arg0->unk_00.unk_04;
    temp_s4 = arg0->unk_18 & 0xFF;
    temp_s3 = arg0->unk_18 & 0xFF00;

    for (i = 0; i < arg0->unk_20; i++) {
        var_v0 = 0;
        var_v1 = temp_s3;
        if (i < arg0->unk_1C) {
            var_v1 |= 0x100;
        } else if (i == arg0->unk_1C) {
            var_v0 = 1;
        }

        var_s1->unk_14(var_s1, (var_v0 & temp_s4) | var_v1);
        var_s1 = var_s1->unk_00.unk_08;
    }
}

void Fragment_SetActive(unk_func_8830867C_02C_048_000* arg0, s32 arg1) {
    arg0->unk_1C = arg1;
    SelectableList_UpdateVisuals(arg0);
}

void GridMenu_Init(unk_func_8830867C_02C_048_000* arg0) {
    ListNode_Init(arg0, sizeof(unk_func_8830867C_02C_048_000));
    arg0->unk_10 = func_8850C0D0;
    arg0->unk_14 = func_8850C1B8;
    arg0->unk_18 = 0;
    arg0->unk_1C = 0;
    arg0->unk_20 = 0;
}

s32 func_8850C0D0(unk_func_8830867C_02C_048_000* arg0, Controller* arg1) {
    s32 var_a3 = 0;

    if (arg0->unk_20 > 0) {
        unk_func_8830867C_02C_048_000* var_a0 = arg0->unk_00.unk_04;
        s32 i;

        for (i = 0; i < arg0->unk_1C; i++) {
            var_a0 = var_a0->unk_00.unk_08;
        }
        var_a3 = var_a0->unk_10(var_a0, arg1);
    }

    if (var_a3 == 0) {
        s32 var_v0_2 = arg0->unk_1C;

        if (arg1->buttonPressed & 0x200) {
            if (var_v0_2 == 0) {
                var_v0_2 = arg0->unk_20 - 1;
            } else {
                var_v0_2--;
            }
        } else if (arg1->buttonPressed & 0x100) {
            if (var_v0_2 + 1 == arg0->unk_20) {
                var_v0_2 = 0;
            } else {
                var_v0_2++;
            }
        }

        if (var_v0_2 != arg0->unk_1C) {
            arg0->unk_1C = var_v0_2;
            func_8850C208(arg0);
            var_a3 = 0x80000008;
        }
    }
    return var_a3;
}

void func_8850C1B8(unk_func_8830867C_02C_048_000* arg0, s32 arg1) {
    arg0->unk_18 = arg1;
    func_8850C208(arg0);
}

void func_8850C1D8(unk_func_8830867C_02C_048_000* arg0, unk_func_88001300_000_000* arg1) {
    Fragment_SetChild(&arg0->unk_00, arg1);
    arg0->unk_20++;
}

void func_8850C208(unk_func_8830867C_02C_048_000* arg0) {
    unk_func_8830867C_02C_048_000* var_s0 = arg0->unk_00.unk_04;
    s32 i;

    for (i = 0; i < arg0->unk_20; i++) {
        s32 var_a1 = 0;

        if (i == arg0->unk_1C) {
            var_a1 = arg0->unk_18;
        }
        var_s0->unk_14(var_s0, var_a1);
        var_s0 = var_s0->unk_00.unk_08;
    }
}

void func_8850C284(unk_func_88001300_03C* arg0, s32 arg1, s32 arg2, MemoryPool* arg3) {
    s32 i;

    ListNode_Init(arg0, sizeof(unk_func_88001300_03C));
    arg0->unk_10 = GridMenu_HandleInput;
    arg0->unk_14 = GridMenu_SetItemCount;
    arg0->unk_18 = mem_pool_alloc(arg3, (arg2 * sizeof(unk_func_88001300_000*)) * arg1);

    for (i = 0; i < arg2 * arg1; i++) {
        arg0->unk_18[i] = NULL;
    }

    arg0->unk_20 = 0;
    arg0->unk_24 = 0;
    arg0->unk_28 = 0;
    arg0->unk_30 = arg1;
    arg0->unk_2C = arg2;
    arg0->unk_1C = NULL;
    arg0->unk_36 = 0;
    arg0->unk_34 = 0;
    arg0->unk_38 = -3;
    arg0->unk_3A = -3;
    arg0->unk_3C = 6;
    arg0->unk_3E = 6;
}

s32 GridMenu_HandleInput(unk_func_88001300_03C* arg0, Controller* arg1) {
    s32 sp5C;
    UNUSED s32 pad1;
    s32 sp54;
    s32 sp50;
    s32 sp4C;
    s32 sp48;
    UNUSED s32 pad2;
    s32 i;
    s32 j;
    s32 var_t4;
    s32 sp24;

    sp5C = 0;
    var_t4 = 0;
    if (arg0->unk_18[arg0->unk_24] != NULL) {
        if (arg0->unk_18[arg0->unk_24]->unk_20 != NULL) {
            sp5C = arg0->unk_18[arg0->unk_24]->unk_20(arg0->unk_18[arg0->unk_24], arg1);
        }
    }

    if (sp5C != 0) {
        return sp5C;
    }

    sp54 = arg0->unk_24 % arg0->unk_2C;
    sp50 = arg0->unk_24 / arg0->unk_2C;
    sp24 = MenuInput_ReadDirection() & 0xFFFF;

    if (sp24 == 0x800) {
        for (i = 0, sp48 = sp50; i < arg0->unk_30 - 1; i++) {
            sp48 = ((sp48 == 0) ? arg0->unk_30 : sp48) - 1;

            for (j = 0, sp4C = arg0->unk_34; j < arg0->unk_2C;) {
                if ((arg0->unk_18[sp48 * arg0->unk_2C + sp4C] != NULL) &&
                    !(arg0->unk_18[sp48 * arg0->unk_2C + sp4C]->unk_28 & 2)) {
                    var_t4 = 1;
                    break;
                }

                j++;
                sp4C = ((sp4C == 0) ? arg0->unk_2C : sp4C) - 1;
            }

            if (var_t4 != 0) {
                break;
            }
        }

        if ((arg0->unk_28 & 0x200) && ((var_t4 == 0) || (sp50 < sp48))) {
            sp5C = 8;
            var_t4 = 0;
        }
    } else if (sp24 == 0x400) {
        for (i = 0, sp48 = sp50; i < arg0->unk_30 - 1; i++) {
            if (sp48 == arg0->unk_30 - 1) {
                sp48 = 0;
            } else {
                sp48++;
            }

            for (j = 0, sp4C = arg0->unk_34; j < arg0->unk_2C;) {
                if ((arg0->unk_18[sp48 * arg0->unk_2C + sp4C] != NULL) &&
                    !(arg0->unk_18[sp48 * arg0->unk_2C + sp4C]->unk_28 & 2)) {
                    var_t4 = 1;
                    break;
                }

                j++;
                sp4C = ((sp4C == 0) ? arg0->unk_2C : sp4C) - 1;
            }

            if (var_t4 != 0) {
                break;
            }
        }

        if ((arg0->unk_28 & 0x200) && ((var_t4 == 0) || (sp48 < sp50))) {
            sp5C = 8;
            var_t4 = 0;
        }
    } else if (sp24 == 0x100) {
        for (j = 0, sp4C = sp54; j < arg0->unk_2C - 1; j++) {
            if (sp4C == arg0->unk_2C - 1) {
                sp4C = 0;
            } else {
                sp4C++;
            }

            for (i = 0, sp48 = arg0->unk_36; i < arg0->unk_30;) {
                if ((arg0->unk_18[sp48 * arg0->unk_2C + sp4C] != NULL) &&
                    !(arg0->unk_18[sp48 * arg0->unk_2C + sp4C]->unk_28 & 2)) {
                    var_t4 = 1;
                    break;
                }

                i++;
                sp48 = ((sp48 == 0) ? arg0->unk_30 : sp48) - 1;
            }

            if (var_t4 != 0) {
                break;
            }
        }

        if ((arg0->unk_28 & 0x100) && ((var_t4 == 0) || (sp4C < sp54))) {
            sp5C = 8;
            var_t4 = 0;
        }
    } else if (sp24 == 0x200) {
        for (j = 0, sp4C = sp54; j < arg0->unk_2C - 1; j++) {
            sp4C = ((sp4C == 0) ? arg0->unk_2C : sp4C) - 1;

            for (i = 0, sp48 = arg0->unk_36; i < arg0->unk_30;) {
                if ((arg0->unk_18[sp48 * arg0->unk_2C + sp4C] != NULL) &&
                    !(arg0->unk_18[sp48 * arg0->unk_2C + sp4C]->unk_28 & 2)) {
                    var_t4 = 1;
                    break;
                }

                i++;
                sp48 = ((sp48 == 0) ? arg0->unk_30 : sp48) - 1;
            }

            if (var_t4 != 0) {
                break;
            }
        }

        if ((arg0->unk_28 & 0x100) && ((var_t4 == 0) || (sp54 < sp4C))) {
            sp5C = 8;
            var_t4 = 0;
        }
    }

    if (var_t4 != 0) {
        arg0->unk_24 = (arg0->unk_2C * sp48) + sp4C;
        if ((sp24 == 0x800) || (sp24 == 0x400)) {
            arg0->unk_36 = sp48;
        } else {
            arg0->unk_34 = sp4C;
        }
        GridMenu_Update(arg0);
        sp5C = 0x80000009;
    }
    return sp5C;
}

void GridMenu_SetItemCount(unk_func_88001300_03C* arg0, s32 arg1) {
    arg0->unk_20 = arg1;
    GridMenu_Update(arg0);
}

void GridMenu_Update(unk_func_88001300_03C* arg0) {
    s32 i;

    if (arg0->unk_1C != NULL) {
        arg0->unk_1C->unk_00.unk_28 &= 0xFFFE;
    }

    for (i = 0; i < arg0->unk_2C * arg0->unk_30; i++) {
        unk_func_88001300_000* temp_s1 = arg0->unk_18[i];

        if (temp_s1 != NULL) {
            s32 var_s2 = 0;

            if (i == arg0->unk_24) {
                var_s2 = arg0->unk_20;
                if (arg0->unk_1C != NULL) {
                    arg0->unk_1C->unk_00.unk_10 = temp_s1->unk_10;
                    arg0->unk_1C->unk_00.unk_14 = temp_s1->unk_14;
                    arg0->unk_1C->unk_00.unk_10.unk_00 = temp_s1->unk_10.unk_00 + arg0->unk_38;
                    arg0->unk_1C->unk_00.unk_10.unk_02 = temp_s1->unk_10.unk_02 + arg0->unk_3A;
                    arg0->unk_1C->unk_00.unk_14.unk_00 = temp_s1->unk_14.unk_00 + arg0->unk_3C;
                    arg0->unk_1C->unk_00.unk_14.unk_02 = temp_s1->unk_14.unk_02 + arg0->unk_3E;
                    arg0->unk_1C->unk_00.unk_24(&arg0->unk_1C->unk_00, var_s2);
                    if (var_s2 & 0x101) {
                        arg0->unk_1C->unk_00.unk_28 |= 1;
                    }
                }
            }
            temp_s1->unk_24(temp_s1, var_s2);
        }
    }
}

void GridMenu_SelectFirstEnabled(unk_func_88001300_03C* arg0) {
    s32 i;

    for (i = 0; i < arg0->unk_2C * arg0->unk_30; i++) {
        if ((arg0->unk_18[i] != NULL) && !(arg0->unk_18[i]->unk_28 & 2)) {
            arg0->unk_24 = i;
            arg0->unk_34 = i % arg0->unk_2C;
            arg0->unk_36 = i / arg0->unk_2C;
            break;
        }
    }
}

void GridMenu_SetSelection(unk_func_88001300_03C* arg0, s32 arg1) {
    arg0->unk_24 = arg1;
    arg0->unk_34 = arg1 % arg0->unk_2C;
    arg0->unk_36 = arg1 / arg0->unk_2C;
    GridMenu_Update(arg0);
}

void UISeparator_Create(unk_func_8830867C_02C_048_000* arg0) {
    ListNode_Init(&arg0->unk_00, sizeof(unk_func_8830867C_02C_048_000));
    arg0->unk_10 = List_GetResult;
    arg0->unk_14 = List_SetResult;
    arg0->unk_18 = 0;
    arg0->unk_1C = 0;
    arg0->unk_20 = 0;
}

s32 List_GetResult(unk_func_8830867C_02C_048_000* arg0, Controller* arg1) {
    s32 i;
    s32 var_v1 = 0;

    if (arg0->unk_20 > 0) {
        unk_func_8830867C_02C_048_000* var_a0 = arg0->unk_00.unk_04;

        for (i = 0; i < arg0->unk_1C; i++) {
            var_a0 = var_a0->unk_00.unk_08;
        }
        var_v1 = var_a0->unk_10(var_a0, arg1);
    }
    return var_v1;
}

void List_SetResult(unk_func_8830867C_02C_048_000* arg0, s32 arg1) {
    arg0->unk_18 = arg1;
    List_UpdateVisuals(arg0);
}

void Fragment_LinkSiblingAlt(unk_func_8830867C_02C_048_000* arg0, unk_func_88001300_000* arg1) {
    Fragment_SetChild(&arg0->unk_00.unk_00, &arg1->unk_00);
    arg0->unk_20++;
}

void List_UpdateVisuals(unk_func_8830867C_02C_048_000* arg0) {
    s32 var_a1;
    s32 i;
    unk_func_8830867C_02C_048_000* var_s0 = arg0->unk_00.unk_04;

    for (i = 0; i < arg0->unk_20; i++) {
        if (i == arg0->unk_1C) {
            var_a1 = arg0->unk_18;
        } else {
            var_a1 = 0;
        }
        var_s0->unk_14(var_s0, var_a1);
        var_s0 = var_s0->unk_00.unk_08;
    }
}

void UIList_SelectItem(unk_func_8830867C_02C_048* arg0, s32 arg1) {
    arg0->unk_00.unk_1C = arg1;
    List_UpdateVisuals(&arg0->unk_00);
}

void Panel_Setup(unk_func_8850CD44* arg0, s32 arg1, MemoryPool* arg2) {
    s32 i;

    ((func88500668)Memmap_GetFragmentVaddr(ListNode_Init))(arg0, sizeof(unk_func_8850CD44));
    arg0->unk_10 = ItemArray_GetActiveFlag;
    arg0->unk_14 = ItemArray_PropagateResult;
    arg0->unk_18 = 0;
    arg0->unk_20 = arg1;
    arg0->unk_1C = mem_pool_alloc(arg2, arg1 * 4);

    for (i = 0; i < arg1; i++) {
        arg0->unk_1C[i] = NULL;
    }
}

s32 ItemArray_GetActiveFlag(unk_func_8850CD44* arg0, Controller* arg1) {
    s32 i;

    for (i = 0; i < arg0->unk_20; i++) {
        if (arg0->unk_1C[i]->unk_00.unk_28 & 0x100) {
            return 0x40;
        }
    }
    return 4;
}

void ItemArray_PropagateResult(unk_func_8850CD44* arg0, s32 arg1) {
    s32 i;

    for (i = 0; i < arg0->unk_20; i++) {
        arg0->unk_1C[i]->unk_00.unk_24(arg0->unk_1C[i], arg1);
    }
}

void ItemArray_WaitForSelection(unk_func_8850CD44* arg0, Controller* arg1) {
    s32 temp_v0;
    s32 var_s0 = 0;

    while (var_s0 == 0) {
        ControllerMsgQueue_SendAndRead(var_s0);
        temp_v0 = arg0->unk_10(arg0, arg1);
        if (!(temp_v0 & 1) && (temp_v0 & 4)) {
            var_s0 = 1;
        }
    }
}
