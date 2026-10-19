#include "fragment5.h"
#include "src/20330.h"
#include "src/controller.h"

u16 gDrowzeeFrameCounter = 0;
u16 gDrowzeeStartCountdown = 0x0069;
u8 gDrowzeeGameIsOver = 0;
u8 gDrowzeePauseTriggered = 0;
u8 gDrowzeeTutorialPage = 0;
u8 gDrowzeeWinnerCount = 0;

TextObject* gCurrentTextObject;
ModelData* gDrowzeeModelTemp;
MiniHudMainGraph* gDrowzeeStageRoot;
CameraStruct* gDrowzeeCamera;
s16 gDrowzeeCamDist;
s16 gDrowzeeCamYaw;
s16 gDrowzeeCamPitch;

void MenuInput_FrameUpdate(void) {
    Cont_StartReadInputs();
    Cont_ReadInputs();
    Input_ResetRepeatState();
}

u32 MiniGame_RandomRange(u32 arg0) {
    if (arg0 == 0) {
        return 0;
    }
    return ((guRandom() + osGetCount()) / 10) % arg0;
}
