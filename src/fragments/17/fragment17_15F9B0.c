#include "fragment17.h"
#include "29BA0.h"

s32 BattleContext_HandleState(UNUSED s32 arg0, UNUSED s32 arg1) {
    switch (gBattleContext.unk_0000) {
        case 18:
            return BattleState_Handle18();

        case 17:
            return BattleState_Handle17();

        case 21:
            return BattleState_Handle21Or26();

        case 26:
            return BattleState_Handle21Or26();

        case 22:
        case 23:
            return BattleState_Handle22Or23();

        case 24:
            return BattleState_Handle24();
    }
}
