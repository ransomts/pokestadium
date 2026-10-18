#include "fragment39.h"
#include "src/fragments/2/fragment2.h"
#include "26820.h"

void UpdateMenuRandomSeed(void) {
    gMenuRandomSeed = func_800280C4() & 0xFF;
}

void SetCurrentMenuIndex(s16 arg0) {
    gCurrentMenuIndex = arg0;
}

void func_82505FE0(s16 arg0) {
    s32 i;
    s32 j;

    for (i = 0; i < 4; i++) {
        gMenuOptionFlags[i] = 0;
    }

    switch (arg0) {
        case 0:
            gCurrentMenuIndex = -1;
            gMenuCursorX = 0;
            gMenuCursorY = 0;

            for (i = 0; i < 4; i++) {
                gMiniHudColorDefaults[i] = 1;
            }

            gMenuState = 1;
            gMenuSubState = 3;

            for (i = 0; i < 4; i++) {
                gMenuOptionTimers[i] = 0;
            }

            gMenuSelectedOption = 0;
            // clang-format off
            for (i = 0; i < 9; i++) { gMenuOptionUsedFlags[i] = 0; }
            // clang-format on
            break;

        case 1:
        case 4:
            break;
    }
}

s16 GetRandomUnusedMenuSlot(void) {
    u32 var_a2;
    s32 i;
    s16 sp24[9];

    var_a2 = 0;

    for (i = 0; i < 9; i++) {
        if (gMenuOptionUsedFlags[i] == 0) {
            sp24[var_a2++] = i;
        }
    }

    if (var_a2 == 0) {
        var_a2 = 9;

        for (i = 0; i < 9; i++) {
            gMenuOptionUsedFlags[i] = 0;
            sp24[i] = i;
        }
    }

    return sp24[GetRandomMod(var_a2)];
}
