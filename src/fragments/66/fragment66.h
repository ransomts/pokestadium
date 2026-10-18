#ifndef _FRAGMENT66_H_
#define _FRAGMENT66_H_

#include "global.h"
#include "src/29BA0.h"

typedef struct unk_D_832025C8 {
    /* 0x000 */ s32 unk_00;
    /* 0x004 */ char unk04[0x1FC];
} unk_D_832025C8; // size = 0x200

typedef struct unk_D_832027C8 {
    /* 0x00 */ u8 unk_00;
    /* 0x01 */ u8 unk_01;
    /* 0x02 */ u8 unk_02;
    /* 0x04 */ PokemonData unk_04;
} unk_D_832027C8; // size = 0x58

s32 GeoCmd_AdjustNodeZOffset(s32 arg0, Fragment2_1GraphNode* arg1);
s32 Pokemon_IsStandard(PokemonData* arg0);
s32 Pokemon_MatchesSelectionCriteria(PokemonData* arg0, s16 arg1, s16 arg2, s16 arg3);
s32 CountMatchingPokemonInBlock(s16 arg0, s16 arg1, s16 arg2);
s32 SnapSelect_FindPokemon(void);
s32 GetPokemonCount(void);
void UpdatePikachuAnimation(void);
void UpdatePikachuVisibility(void);
s32 RenderScene(u8 arg0);
void Text_PrintFadingChar(s16 arg0, s16 arg1);
void UI_DrawGradientPanel(s16 arg0, s16 arg1, s16 arg2, s16 arg3);
void DrawCursorSprite(s16 arg0, s16 arg1);
void UI_DisplayMessageRepeated(char* arg0, s32 arg1);
void UI_DisplayMessageWaitA(char* arg0, s32 arg1);
void UI_SlideTextTransition(s8* arg0);
s32 UI_PromptYesNo(char* arg0);
s32 UI_PromptMoveSelection(char* arg0);
void Event_PikachuExit(void);
void Event_PikachuEnter(void);
void Camera_PanDown(void);
s32 UI_StartDialogue(void);
s32 UI_SelectMoveAndExecute(void);
void UI_DrawSaveStatus(s32 arg0);
void Save_WritePokemonData(void);
void Event_GrantMove(s32 arg0);
void Event_PikachuSequence(void);
void Pikachu_InitNode(Fragment2_1GraphNode* arg0, s16 arg1, s16 arg2, s16 arg3);
void Pikachu_SetupScene(void);
s32 Fragment66_Main(UNUSED s32 arg0, UNUSED s32 arg1);

#endif // _FRAGMENT66_H_
