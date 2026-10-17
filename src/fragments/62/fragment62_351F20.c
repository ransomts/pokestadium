#include "fragment62.h"
#include "src/30640.h"
#include "src/6A40.h"

static Gfx D_84389780[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPClearGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN |
                          G_TEXTURE_GEN_LINEAR | G_LOD | G_SHADING_SMOOTH | G_CLIPPING | 0x0040F9FA),
    gsSPSetGeometryMode(G_SHADE | G_SHADING_SMOOTH),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPPipeSync(),
    gsDPLoadTextureBlock_4b(D_8438A648, G_IM_FMT_I, 32, 32, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, 5,
                            5, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetCombineMode(G_CC_BLENDIA, G_CC_BLENDIA),
    gsDPSetAlphaDither(G_AD_NOISE),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsSPEndDisplayList(),
};
static Vtx D_84389810[] = {
    VTX(0, 20, 0, 1024, 2048, 0xFF, 0xFF, 0xFF, 0x00), VTX(30, 20, 0, 1024, 2048, 0xFF, 0xFF, 0xFF, 0x00),
    VTX(-20, 10, 0, 0, 1024, 0xFF, 0xFF, 0xFF, 0x00),  VTX(50, 10, 0, 2048, 1024, 0xFF, 0xFF, 0xFF, 0x00),
    VTX(0, 0, 0, 1024, 1024, 0xFF, 0xFF, 0xFF, 0xFF),  VTX(30, 0, 0, 1024, 1024, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(-20, -10, 0, 0, 1024, 0xFF, 0xFF, 0xFF, 0x00), VTX(50, -10, 0, 2048, 1024, 0xFF, 0xFF, 0xFF, 0x00),
    VTX(0, -20, 0, 1024, 0, 0xFF, 0xFF, 0xFF, 0x00),   VTX(30, -20, 0, 1024, 0, 0xFF, 0xFF, 0xFF, 0x00),
};

#ifdef NON_MATCHING
// Score 85 (was 229). Stack layout now matches; only the fa0/ft4 swap remains (a3_z should be in fa0,
// 2*a3_y in ft4, and both sp128 loads in ft4 not ft5).
// Round 6 finding: the six spilled values (sp8C..sp78 at 0x8C..0x78) are uopt temps whose slot order
// follows the first occurrence of their expressions; the target's 3 never-stored slots below them are
// temps that occur LATER (probably the a3_x/y/z * 2.0f CSEs). The dead early copy of the six 1.2/0.2
// expressions right after a3_z (overwritten below) reproduces that order; it is a fake - the real
// source probably computed them before the vertex writes in some way that keeps the late schedule.
// Moving the six real assignments earlier (anywhere from before a3_x to after tmp1) wrecks the schedule
// (4600-9400). Dead copy must be full expressions (plain `sp8C = a1_x;` does nothing), all six.
// `if (a3_z) {}` (or `if (sp128) {}`, `if (a3_x) {}`) still required; tmp1 hack worth 25.
// Dead ends this round for the swap: sp128 * arg4 operand order, named 2*a3 temps, extra tmpN for any
// v8/v9 component, (a3_y + a3_y), moving the if, reordering the dead copies, indexed vertex writes
// (1466), loop forms of the copy loop, named call-arg temps, block-scoped pads.
// Round 8 (agent 4) model: a3_x/y/z, 2*a3_x/y/z and the sp128 reloads are colored by uopt
// first-fit over [f0, f2, f12, f14, f16, f18] in priority order. The target colors a3_z before
// 2*a3_x and 2*a3_y (a3_z=f12, then f14/f16/f18); here 2*a3_y and 2*a3_x win (f12/f14) and a3_z
// gets f16. Evidence: "if (a3_y) {}" right before guTranslate lowers a3_y below a3_z (a3_z -> f2).
// Changing where ranges END does not change the order (statement permutations inside vertex
// blocks, v9 x/y/z order, dropping tmp1). New dead ends: a fresh variable for the late a3_x, y
// or z (it is colored callee-saved, fs0, 5600-9200); moving "if (a3_z) {}" before the a3_y/a3_z
// assignments or after v0/v1/v2/v3 (5700-13500; after tmp1 is identical); a second if on
// a3_x/y/z before/after guTranslate (120-695); if (sp84/sp78/sp128) there (identical);
// (a3_z + a3_z), 2.0f * a3_z, "* 2", "* 2.0" forms; sp130 *= arg4 forms (1390); permuting the
// x/y/z lines of any vertex (105-666); dead tmp2 copies of 2*a3_z / v2.z / v6.z after a3_z, the
// if or tmp1; inlining the six 1.2/0.2 expressions (no sp8C..sp78, pad4[13]): 279, the spills
// land 3 slots low and the v2/v3 adds flip operands. Farm: 750k iterations, best 85.
// Round 8 pass 2 (agent 10): the empty if is a uopt block boundary, not just an a3_z use.
// With no boundary the code is wrecked (9805); "goto lbl; lbl:", "do { ... } while (0)" and
// "if (1) { ... }" around the vertex code give 105 (arg4 -> f12, sp128 -> f14). A second
// boundary anywhere (another if, or a goto after any vertex block) is 8500-12500, so there is
// exactly one, at this position (moving it before the dead copies, a3_x, a3_y or a3_z:
// 4500-12800). Conditions: a3_x/y/z, a3_z != 0 / < 0, sp128, arg4 * sp128, (a3_z, a3_z) = 85;
// arg4, temp_v1, sp1E8, a1_x, a2_x, arg0/3/5, tmp1 = 105; anything else worse.
// The register choice is consistent with Chow block-granular colouring (B2 = up to the if,
// B3 = vertex writes): target order a3_x, a3_y, a3_z (f12), arg4 (f14), then sp128 (f16; its
// B1 SQ load and B2 load are one candidate, so it shares a3_z's B2), 2*a3_x f14,
// 2*a3_y f16, 2*a3_z f18. Here 2*a3_y and 2*a3_x are coloured before a3_z.
// New dead ends (all 85 or worse): a3_z double/self/dead defs, tmp2 = a3_z copies, a3_z
// declared first/last, permutations of the a3 decls, a3 assignment orders (148-231),
// tmp2 = arg4 scale (1065), a3_z via tmp3, a3_* inlined as arg4 * spXXX (10000+), tmp1 or
// tmp2 (2*a3_x) moved before the if, fake ifs in B1 or before guTranslate, named b_x/y/z for
// 2*a3 (the 3 never-stored temps are not the 2*a3 CSEs: they survive that).
Gfx* func_84367660(Gfx* arg0, Vec3f* arg1, Vec3f* arg2, Vec3f* arg3, f32 arg4, u8 arg5, u8 arg6, u8 arg7, u8 arg8) {
    s32 i;
    Vtx* sp1E8;
    s32 pad[2];
    Mtx* sp1DC;
    s32 pad2[42];
    f32 sp130;
    f32 sp12C;
    f32 sp128;
    f32 sp8C;
    f32 sp88;
    f32 sp84;
    f32 sp80;
    f32 sp7C;
    f32 sp78;
    s32 pad4[7];
    Vtx* var_a1;
    Vtx* temp_v1;
    f32 a1_x;
    f32 a1_y;
    f32 a1_z;
    f32 a2_x;
    f32 a2_y;
    f32 a2_z;
    f32 a3_x;
    f32 a3_y;
    f32 a3_z;
    f32 tmp1;
    f32 tmp2;
    f32 tmp3;

    sp1DC = func_80005F5C(sizeof(Mtx) * 1);
    sp1E8 = func_80005F5C(sizeof(Vtx) * 10);

    temp_v1 = sp1E8;
    var_a1 = &D_84389810[0];
    for (i = 0; i < 10; i++) {
        *temp_v1 = *var_a1++;
        if ((i == 4) || (i == 5)) {
            temp_v1->v.cn[0] = arg5;
            temp_v1->v.cn[1] = arg6;
            temp_v1->v.cn[2] = arg7;
            temp_v1->v.cn[3] = arg8;
        }
        temp_v1++;
    }

    a1_x = arg1->x;
    a1_y = arg1->y;
    a1_z = arg1->z;
    a2_x = arg2->x;
    a2_y = arg2->y;
    a2_z = arg2->z;
    a3_x = arg3->x;
    a3_y = arg3->y;
    a3_z = arg3->z;

    func_80031A94(a2_x - a1_x, a2_y - a1_y, a2_z - a1_z, a1_x - a3_x, a1_y - a3_y, a1_z - a3_z, &sp130, &sp12C, &sp128);
    if ((SQ(sp130) + SQ(sp12C) + SQ(sp128)) > 0.0f) {
        func_80031B04(&sp130, &sp12C, &sp128);
    }

    gSPDisplayList(arg0++, D_84389780);
    gDPPipeSync(arg0++);
    gDPSetEnvColor(arg0++, arg5, arg6, arg7, arg8);

    a3_x = arg4 * sp130;
    a3_y = arg4 * sp12C;
    a3_z = arg4 * sp128;
    sp8C = (-a2_x * 0.2f) + (a1_x * 1.2f);
    sp88 = (-a2_y * 0.2f) + (a1_y * 1.2f);
    sp84 = (-a2_z * 0.2f) + (a1_z * 1.2f);
    sp80 = (a2_x * 1.2f) - (a1_x * 0.2f);
    sp7C = (a2_y * 1.2f) - (a1_y * 0.2f);
    sp78 = (a2_z * 1.2f) - (a1_z * 0.2f);

    temp_v1 = sp1E8;

    if (a3_z) {}

    tmp1 = a2_y - a3_y * 2.0f;

    temp_v1->v.ob[0] = a3_x * 2.0f + a1_x;
    temp_v1->v.ob[1] = a3_y * 2.0f + a1_y;
    temp_v1->v.ob[2] = a3_z * 2.0f + a1_z;
    temp_v1++;

    temp_v1->v.ob[0] = a3_x * 2.0f + a2_x;
    temp_v1->v.ob[1] = a3_y * 2.0f + a2_y;
    temp_v1->v.ob[2] = a3_z * 2.0f + a2_z;
    temp_v1++;

    sp8C = (-a2_x * 0.2f) + (a1_x * 1.2f);
    sp88 = (-a2_y * 0.2f) + (a1_y * 1.2f);
    sp84 = (-a2_z * 0.2f) + (a1_z * 1.2f);

    sp80 = (a2_x * 1.2f) - (a1_x * 0.2f);
    sp7C = (a2_y * 1.2f) - (a1_y * 0.2f);
    sp78 = (a2_z * 1.2f) - (a1_z * 0.2f);

    temp_v1->v.ob[0] = a3_x + sp8C;
    temp_v1->v.ob[1] = a3_y + sp88;
    temp_v1->v.ob[2] = a3_z + sp84;
    temp_v1++;

    temp_v1->v.ob[0] = a3_x + sp80;
    temp_v1->v.ob[1] = a3_y + sp7C;
    temp_v1->v.ob[2] = a3_z + sp78;
    temp_v1++;

    temp_v1->v.ob[0] = a1_x;
    temp_v1->v.ob[1] = a1_y;
    temp_v1->v.ob[2] = a1_z;
    temp_v1++;

    temp_v1->v.ob[0] = a2_x;
    temp_v1->v.ob[1] = a2_y;
    temp_v1->v.ob[2] = a2_z;
    temp_v1++;

    temp_v1->v.ob[0] = sp8C - a3_x;
    temp_v1->v.ob[1] = sp88 - a3_y;
    temp_v1->v.ob[2] = sp84 - a3_z;
    temp_v1++;

    temp_v1->v.ob[0] = sp80 - a3_x;
    temp_v1->v.ob[1] = sp7C - a3_y;
    temp_v1->v.ob[2] = sp78 - a3_z;
    temp_v1++;

    temp_v1->v.ob[0] = a1_x - a3_x * 2.0f;
    temp_v1->v.ob[1] = a1_y - a3_y * 2.0f;
    temp_v1->v.ob[2] = a1_z - a3_z * 2.0f;
    temp_v1++;

    temp_v1->v.ob[0] = a2_x - a3_x * 2.0f;
    temp_v1->v.ob[1] = tmp1;
    temp_v1->v.ob[2] = a2_z - a3_z * 2.0f;
    temp_v1++;

    guTranslate(sp1DC, 0.0f, 0.0f, 0.0f);

    gSPMatrix(arg0++, sp1DC, G_MTX_PUSH | G_MTX_MUL | G_MTX_MODELVIEW);
    gSPVertex(arg0++, sp1E8, 10, 0);
    gSP2Triangles(arg0++, 0, 4, 2, 0, 2, 4, 6, 0);
    gSP2Triangles(arg0++, 0, 1, 4, 0, 1, 5, 4, 0);
    gSP2Triangles(arg0++, 1, 3, 5, 0, 3, 7, 5, 0);
    gSP2Triangles(arg0++, 6, 4, 8, 0, 4, 5, 8, 0);
    gSP2Triangles(arg0++, 8, 5, 9, 0, 5, 7, 9, 0);
    gSPPopMatrix(arg0++, G_MTX_MODELVIEW);

    return arg0;
}
#else
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/62/fragment62_351F20/func_84367660.s")
#endif
