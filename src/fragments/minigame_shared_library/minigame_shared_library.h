#ifndef _FRAGMENT5_H_
#define _FRAGMENT5_H_

#include "global.h"

extern u16 gDrowzeeFrameCounter;
extern u16 gDrowzeeStartCountdown;
extern u8 gDrowzeeGameIsOver;
extern u8 gDrowzeePauseTriggered;
extern u8 gDrowzeeTutorialPage;
extern u8 gDrowzeeWinnerCount;

extern TextObject* gCurrentTextObject;
extern ModelData* gDrowzeeModelTemp;
extern MiniHudMainGraph* gDrowzeeStageRoot;
extern CameraStruct* gDrowzeeCamera;
extern s16 gDrowzeeCamDist;
extern s16 gDrowzeeCamYaw;
extern s16 gDrowzeeCamPitch;

void MenuInput_FrameUpdate(void);
u32 MiniGame_RandomRange(u32);


#endif // _FRAGMENT5_H_
