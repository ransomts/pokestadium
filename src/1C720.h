#ifndef _1C720_H_
#define _1C720_H_

#include "global.h"
#include "src/29BA0.h"

typedef struct unk_func_8001C014 {
	/* 0x00 */ char posX[0x2];
	/* 0x02 */ u16 posY;
	/* 0x04 */ s8 rotation[0x10];
	/* 0x14 */ s8 unk_14[0x10];
} unk_func_8001C014; // size >= 0x24

typedef struct unk_func_8001C248 {
    /* 0x000 */ GraphRootNode unk_000;
    /* 0x018 */ s16 unk_018;
    /* 0x01A */ s16 unk_01A;
    /* 0x01C */ u8 unk_01C;
    /* 0x01D */ u8 unk_01D;
    /* 0x01E */ char unk01E[0x2];
    /* 0x020 */ s32 unk_020;
    /* 0x024 */ s32* unk_024;
} unk_func_8001C248; // size >= 0x28

void ModelRenderer_InitDisplayRoots(void);
void ModelRenderer_AttachDisplayObject(Fragment2_1GraphNode* arg0);
void ModelRenderer_AttachSecondaryDisplayObject(Fragment2_1GraphNode* arg0);
void Model_InitDisplayObject(Fragment2_1GraphNode* arg0, s16 arg1, s16 arg2, unk_D_86002F58_004_000_004* arg3);
void ModelRenderer_ClearDisplayObject(Fragment2_1GraphNode* arg0);
s32 ModelAnim_SetAnimation(Fragment2_1GraphNode* arg0, s32 arg1);
s32 ModelAnim_SetEventTrack(Fragment2_1GraphNode* arg0, s32 arg1);
void Model_SetMaterialColor(Fragment2_1GraphNode* arg0, u8 arg1, u8 arg2, u8 arg3, u8 arg4);
void Model_SetMaterialAlpha(Fragment2_1GraphNode* arg0, u8 arg1);
void Model_SetMaterialTextureMode(Fragment2_1GraphNode* arg0, u8 arg1);
unk_D_86002F58_004_000_00C_028* ModelAnim_GetAnimationRecord(Fragment2_1GraphNode* arg0, s32 arg1);
arg1_func_80010CA8* Model_ComputeSizeVariant(arg1_func_80010CA8* arg0, PokemonData* arg1);
void Model_ComputeSizeVariantFromRecord(arg1_func_80010CA8* arg0, unk_func_8001C014* arg1, u16 arg2);
void Trainer_RequestPokeIcon(unk_D_800AE540_1194* arg0);
void PokeIcon_PollFrameLoadForObject(unk_func_8001C248* arg0);
void PokeIcon_WaitFrameLoadForObject(unk_func_8001C248* arg0);
void PokeIcon_RequestBackgroundForObject(unk_func_8001C248* arg0);
void PokeIcon_PollBackgroundForObject(unk_func_8001C248* arg0);

#endif // _1C720_H_
