#ifndef _FRAGMENT4_H_
#define _FRAGMENT4_H_

#include "global.h"

extern u32 gTextTable_StageNames[];
extern u32 gTextTable_StageSubtitles[];
extern u32 gStageSubtitles_Alt1[];
extern u32 gStageSubtitles_Alt2[];
extern u32 gStageSubtitles_Alt3[];

void MiniCam_SetActive(CameraStruct*);
Gfx* MiniCam_ApplyProjection(Gfx*);
Gfx* MiniGfx_DrawTexturedQuad(Gfx*, Mtx*, f32, f32, f32, f32, void*, s32, s32);
void Gfx_DrawTilemap(s32);
s32 MiniSound_DispatchCommand(s32, s32, s32);

#endif // _FRAGMENT4_H_
