#include "fragment23.h"
#include "src/1CF30.h"
#include "src/29BA0.h"
#include "src/3FB0.h"
#include "src/memory.h"
#include "src/stage_loader.h"

TextObject* Fragment23_Init(void) {
    TextObject* sp1C;

    main_pool_push_state('TERM');

    sp1C = Text_Init(0x1C, 0);

    ASSET_LOAD(D_04000000, fragment29_misc_1, 0);
    FRAGMENT_LOAD(fragment26);
    FRAGMENT_LOAD(fragment29);

    func_80007754();
    return sp1C;
}

void Fragment23_Terminate(void) {
    Stage_Terminate();

    main_pool_pop_state('TERM');
}

s32 Fragment23_Execute(UNUSED s32 arg0, UNUSED s32 arg1) {
    TextObject_Show(Fragment23_Init(), 1);
    Stage_SetFillColor(1);
    Stage_FadeOut(0xA);
    Fragment23_Terminate();

    FRAGMENT_LOAD_AND_CALL2(fragment22, 1, 0);
    return 0x25;
}

s32 Fragment23_HandleState(s32 arg0, s32 arg1) {
    TextObject* temp_s0;
    s32 var_s1;

    if (arg0 == 5) {
        return Fragment23_Execute(arg0, arg1);
    }
    temp_s0 = Fragment23_Init();

    var_s1 = Fragment23_GetNextState(arg0, arg1);
    while (var_s1 != 0) {
        switch (var_s1) {
            case 1:
                TextObject_Show(temp_s0, 0);
                break;

            case 2:
                TextObject_Confirm(temp_s0);
                break;

            case 3:
                TextObject_Cancel(temp_s0);
                break;
        }
        var_s1 = Fragment23_GetNextState(var_s1, arg1);
    }

    Fragment23_Terminate();

    return 0x25;
}
