#ifndef _334D0_H_
#define _334D0_H_

#include "global.h"

extern s16 gModelPhase[4];

void ModelRenderer_OnSlotReady(s32);
s32 ModelRenderer_IsReady(s32);
void ModelSlot_Reset(s32);
void Model_DrawIfReady(void);
void Model_CopyCurrentToBuffer(u8);
void Model_ConcatCameraMatrix(u8);
void Model_ApplyScaleAndTranslation(u8);
Gfx* Model_RenderStateMachine(Gfx*);

#endif // _334D0_H_
