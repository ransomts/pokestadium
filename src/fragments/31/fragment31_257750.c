#include "fragment31.h"
#include "12D80.h"

void Fragment_BuildDisplayList(Gfx* gfx, DisplayListAddresses* addresses) {
    if (D_8006F09C->unk_01C == 0) {
        gSPDisplayList(gfx++, addresses->segments[0]);
    }
    gSPDisplayList(gfx++, addresses->segments[1]);
    gSPEndDisplayList(gfx++);
}

void Fragment_InitDisplayList(s32 arg0, DisplayListState* state) {
    Gfx* gfx;
    DisplayListAddresses* addresses;

    if (arg0 == 2) {
        addresses = state->addresses;
        gfx = GfxAlloc(0x50);
        state->gfx = gfx;
        Fragment_BuildDisplayList(gfx, addresses);
    }
}
