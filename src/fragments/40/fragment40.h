#ifndef _FRAGMENT40_H_
#define _FRAGMENT40_H_

#include "global.h"
#include "src/geo_layout.h"

typedef struct unk_D_83101F00 {
    /* 0x000 */ Fragment2_1GraphNode unk_000;
    /* 0x168 */ s16 unk_168;
    /* 0x16A */ s16 unk_16A;
    /* 0x16C */ s16 unk_16C;
    /* 0x16E */ s16 unk_16E;
    /* 0x170 */ s16 unk_170;
    /* 0x172 */ s16 unk_172;
    /* 0x174 */ s16 unk_174;
    /* 0x176 */ s16 unk_176;
    /* 0x178 */ s16 unk_178;
    /* 0x17A */ s16 unk_17A;
    /* 0x17C */ s16 unk_17C;
    /* 0x180 */ f32 unk_180;
    /* 0x184 */ f32 unk_184;
} unk_D_83101F00; // size = 0x188

void UpdateNodePosition(Fragment2_1GraphNode* arg0);
s32 DrawNodeGeometry(s32 arg0, UNUSED GraphNode* arg1);
void UpdateNodeColorAndScale(unk_D_83101F00* arg0);
s32 DrawNodeEffect(s32 arg0, GraphNode* arg1);
void InitBorderAnimation(void);
void UpdateBorderAnimation(void);
void DrawBorderEffect(void);
void StartBorderAnimation(s16 arg0);
void InitFadeAnimation(void);
void UpdateFadeAnimation(void);
void DrawTiledTexture(u8* arg0, s16 arg1);
void DrawScreenOverlay(void);
void StartFadeAnimation(s16 arg0);
void InitInput(void);
void SetNodeState(unk_D_83101F00* arg0, s16 arg1);
void DrawScissoredTexture(s16 arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5, s16 arg6, s16 arg7);
void DrawCursorEffect(void);
void InitClearScreenState(void);
void RenderClearScreen(void);
s32 UpdateClearScreenLogic(void);
void RunClearScreenSequence(void);
void InitClearScreenGraph(void);
s32 ClearScreen_Main(UNUSED s32 arg0, UNUSED s32 arg1);

#endif // _FRAGMENT40_H_
