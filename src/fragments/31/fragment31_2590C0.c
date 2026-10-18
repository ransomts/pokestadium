#include "fragment31.h"
#include "src/6A40.h"
#include "src/12D80.h"

typedef struct GraphNodeRange {
    /* 0x00 */ u16 unk_00;
    /* 0x02 */ u16 unk_02;
    /* 0x04 */ u16 unk_04;
} GraphNodeRange; // size = 0x6

typedef struct GraphFlag {
    /* 0x00 */ char unk00[0x1];
    /* 0x01 */ u8 unk_01;
} GraphFlag; // size = 0x2

typedef struct GraphCondition {
    /* 0x00 */ char unk00[0x4];
    /* 0x04 */ GraphFlag* unk_04;
    /* 0x08 */ char unk08[0xC];
    /* 0x14 */ GraphNodeRange* unk_14;
} GraphCondition; // size = 0x18

void GraphFlag_UpdateOnMatch(s32 arg0, GraphCondition* arg1) {
    s32 temp_a2;
    s32 var_v1;
    GraphNodeRange* temp_v0;
    GraphFlag* temp_v0_2;

    if (arg0 == 2) {
        temp_v0 = arg1->unk_14;
        var_v1 = 0;
        if (gDefaultGraphRoot->unk_040.unk_00 == temp_v0->unk_00) {
            temp_a2 = ((s32) gDefaultGraphRoot->unk_040.unk_08 >> 0x10) & 0xFFFF;
            if ((temp_a2 >= (s32) temp_v0->unk_02) && ((s32) temp_v0->unk_04 >= temp_a2)) {
                var_v1 = 1;
            }
        }
        if (var_v1 == 1) {
            temp_v0_2 = arg1->unk_04;
            temp_v0_2->unk_01 |= 1;
            return;
        }
        temp_v0_2 = arg1->unk_04;
        temp_v0_2->unk_01 &= 0xFFFE;
    }
}

void GraphFlag_SetIfOutOfRange(s32 arg0, GraphCondition* arg1) {
    s32 temp_a2;
    s32 var_v1;
    GraphNodeRange* temp_v0;
    GraphFlag* temp_v0_2;

    if (arg0 == 2) {
        temp_v0 = arg1->unk_14;
        var_v1 = 1;
        if (gDefaultGraphRoot->unk_040.unk_00 == temp_v0->unk_00) {
            temp_a2 = ((s32) gDefaultGraphRoot->unk_040.unk_08 >> 0x10) & 0xFFFF;
            if ((temp_a2 >= (s32) temp_v0->unk_02) && ((s32) temp_v0->unk_04 >= temp_a2)) {
                var_v1 = 0;
            }
        }
        if (var_v1 == 1) {
            temp_v0_2 = arg1->unk_04;
            temp_v0_2->unk_01 |= 1;
            return;
        }
        temp_v0_2 = arg1->unk_04;
        temp_v0_2->unk_01 &= 0xFFFE;
    }
}

void GraphOverlay_Draw(s32 arg0, DisplayListState* state) {
    Gfx* gfx;

    if (arg0 == 2) {
        gfx = GfxAlloc(0xA0);
        state->gfx = gfx;
        gDPSetAlphaDither(gfx++, G_AD_NOISE);
        gDPSetPrimColor(gfx++, 0, 0, 10, 10, 10, gDefaultGraphRoot->unk_0A6 & 0xFF);
        gDPSetEnvColor(gfx++, 0x37, 0x14, 0x14, 0xB4);
        gDPSetCombineLERP(gfx++, 0, 0, 0, 0, TEXEL0, 1, PRIMITIVE, 1, 0, 0, 0, 0, COMBINED, 0, ENVIRONMENT, 0);
        gSPEndDisplayList(gfx++);
    }
}
