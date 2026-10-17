#include "fragment31.h"
#include "src/6A40.h"
#include "src/12D80.h"
#include "src/32D10.h"

void func_81002CE0(Gfx* gfx) {
    Mtx* mtx;
    u8 angle;

    angle = gDefaultGraphRoot->unk_0A6 & 3;
    mtx = (Mtx*)GfxAlloc(0x40);
    guRotate(mtx, D_800AF788[angle], 1.0f, 0.0f, 0.0f);
    gSPMatrix(gfx++, mtx, G_MTX_NOPUSH | G_MTX_MUL | G_MTX_MODELVIEW);
    gSPEndDisplayList(gfx++);
}

void func_81002D80(s32 arg0, DisplayListState* state) {
    Gfx* gfx;

    if (arg0 == 2) {
        gfx = (Gfx*)GfxAlloc(0x50);
        state->gfx = gfx;
        func_81002CE0(gfx);
    }
}
