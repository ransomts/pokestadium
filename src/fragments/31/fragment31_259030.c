#include "fragment31.h"
#include "src/6A40.h"
#include "src/fragments/10/fragment10.h"

void Gfx_AllocateAndInitSmallDL(s32 arg0, DisplayListState* state) {
    Gfx* gfx;

    if (arg0 == 2) {
        gfx = (Gfx*)GfxAlloc(0x10);
        state->gfx = gfx;
        if (gUseAlphaBlend == 0) {
            {    Gfx *_gfx = (Gfx *)(gfx++);    _gfx->words.w0 = 0xFC119604;    _gfx->words.w1 = 0xFF13FFFF;    }
        } else {
            {    Gfx *_gfx = (Gfx *)(gfx++);    _gfx->words.w0 = 0xFCFFFFFF;    _gfx->words.w1 = 0xFFFDF638;    }
        }
        gSPEndDisplayList(gfx++);
    }
}
