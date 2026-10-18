#include "fragment31.h"
#include "src/6A40.h"
#include "src/12D80.h"

void Gfx_AppendTwoSegments(Gfx* gfx, DisplayListAddresses* addresses) {
    gSPDisplayList(gfx++, addresses->segments[0]);
    gSPDisplayList(gfx++, addresses->segments[1]);
    gSPEndDisplayList(gfx++);
}

void Gfx_CreateTwoSegmentDL(s32 arg0, DisplayListState* state) {
    Gfx* gfx;
    DisplayListAddresses* addresses;

    if (arg0 == 2) {
        addresses = state->addresses;
        gfx = GfxAlloc(0x18);
        state->gfx = gfx;
        Gfx_AppendTwoSegments(gfx, addresses);
    }
}

void Gfx_ConditionalAppendSegment(Gfx* gfx, s32* address) {
    if (gDefaultGraphRoot->unk_01C == 0) {
        gSPDisplayList(gfx++, *address);
    }
    gSPEndDisplayList(gfx++);
}

void Gfx_CreateConditionalDL(s32 arg0, DisplayListState* state) {
    Gfx* gfx;
    DisplayListAddresses* addresses;

    if (arg0 == 2) {
        addresses = state->addresses;
        gfx = GfxAlloc(0x50);
        state->gfx = gfx;
        Gfx_ConditionalAppendSegment(gfx, addresses);
    }
}
