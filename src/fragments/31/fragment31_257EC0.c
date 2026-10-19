#include "fragment31.h"
#include "src/6A40.h"
#include "src/12D80.h"
#include "src/32D10.h"

void DisplayList_BuildRotationMatrixSegmentAlt(Gfx* gfx) {
    Mtx* mtx;
    u8 angle;

    angle = gDefaultGraphRoot->modelPhase & 3;
    mtx = Gfx_AllocDisplayList(0x40);
    guRotate(mtx, gHpWheelDigitOffsetTens[angle], 1.0f, 0.0f, 0.0f);
    gSPMatrix(gfx++, mtx, G_MTX_NOPUSH | G_MTX_MUL | G_MTX_MODELVIEW);
    gSPEndDisplayList(gfx++);
}

void DisplayList_InitRotationMatrixSegmentAlt(s32 arg0, DisplayListState* state) {
    Gfx* gfx;

    if (arg0 == 2) {
        gfx = Gfx_AllocDisplayList(0x50);
        state->gfx = gfx;
        DisplayList_BuildRotationMatrixSegmentAlt(gfx);
    }
}
