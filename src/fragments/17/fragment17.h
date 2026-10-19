#ifndef _FRAGMENT17_H_
#define _FRAGMENT17_H_

#include "global.h"

typedef struct unk_D_86B0E5D4_04 {
    /* 0x00 */ Vec3f unk_00;
    /* 0x0C */ s16 unk_0C;
    /* 0x0E */ s16 unk_0E;
    /* 0x10 */ char unk10[0x2];
    /* 0x12 */ s16 unk_12;
    /* 0x14 */ s16 unk_14;
    /* 0x18 */ f32 unk_18;
    /* 0x1C */ f32 unk_1C;
    /* 0x20 */ s16 unk_20;
    /* 0x22 */ s16 unk_22;
    /* 0x24 */ char unk24[0x2];
    /* 0x26 */ s16 unk_26;
    /* 0x28 */ s16 unk_28;
    /* 0x2C */ f32 unk_2C;
    /* 0x30 */ f32 unk_30;
    /* 0x34 */ f32 unk_34;
    /* 0x38 */ f32 unk_38;
    /* 0x3C */ f32 unk_3C;
    /* 0x40 */ char unk40[0x4];
    /* 0x44 */ s32 unk_44;
    /* 0x48 */ s32 unk_48;
    /* 0x4C */ s32 unk_4C;
    /* 0x50 */ s32 unk_50;
    /* 0x54 */ char unk54[0x14];
    /* 0x68 */ f32 unk_68;
    /* 0x6C */ f32 unk_6C;
    /* 0x70 */ f32 unk_70;
    /* 0x74 */ f32 unk_74;
} unk_D_86B0E5D4_04; // size >= 0x78

typedef struct unk_D_86B0E5D4 {
    /* 0x00 */ CameraStruct* unk_00;
    /* 0x04 */ unk_D_86B0E5D4_04 unk_04;
} unk_D_86B0E5D4; // size = 0x7C

typedef struct unk_D_86B0C160 {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ s16 unk_08;
    /* 0x0C */ f32 unk_0C;
    /* 0x10 */ f32 unk_10;
    /* 0x14 */ s16 unk_14;
    /* 0x16 */ s16 unk_16;
    /* 0x18 */ s16 unk_18;
    /* 0x1A */ s16 unk_1A;
    /* 0x1C */ s16 unk_1C;
    /* 0x20 */ f32 unk_20;
    /* 0x24 */ f32 unk_24;
    /* 0x28 */ f32 unk_28;
    /* 0x2C */ f32 unk_2C;
    /* 0x30 */ f32 unk_30;
} unk_D_86B0C160; // size = 0x34

typedef struct unk_D_86B0E5F0 {
    /* 0x000 */ unk_D_86002F30* unk_000;
    /* 0x004 */ Fragment2_1GraphNode unk_004;
    /* 0x16C */ s32 unk_16C;
} unk_D_86B0E5F0; // size = 0x170

typedef struct unk_D_86B0C4C8 {
    /* 0x00 */ Vec3f unk_00;
    /* 0x0C */ u8 unk_0C;
    /* 0x0E */ s16 unk_0E;
    /* 0x10 */ u16 unk_10;
    /* 0x12 */ char unk12[0x2];
} unk_D_86B0C4C8; // size = 0x14

typedef struct SpriteColorParams {
    /* 0x00 */ u16 unk_00;
    /* 0x02 */ u16 unk_02;
    /* 0x04 */ u16 unk_04;
    /* 0x06 */ u16 unk_06;
    /* 0x08 */ u16 unk_08;
    /* 0x0A */ u16 unk_0A;
    /* 0x0C */ u16 unk_0C;
    /* 0x0E */ u16 unk_0E;
    /* 0x10 */ u16 unk_10;
    /* 0x12 */ u16 unk_12;
    /* 0x14 */ u16 unk_14;
    /* 0x16 */ u16 unk_16;
} SpriteColorParams; // size = 0x18

typedef struct GfxTileParams {
    /* 0x00 */ SpriteColorParams unk_00;
    /* 0x18 */ SpriteColorParams unk_18;
} GfxTileParams; // size = 0x30

typedef struct unk_D_86B0FA78 {
    /* 0x000 */ unk_D_86002F30* unk_000;
    /* 0x004 */ Fragment2_1GraphNode unk_004;
    /* 0x16C */ s32 unk_16C;
    /* 0x170 */ s32 unk_170;
    /* 0x174 */ s32 unk_174;
    /* 0x178 */ s32 unk_178;
    /* 0x17C */ s32 unk_17C;
    /* 0x180 */ s16 unk_180;
} unk_D_86B0FA78; // size = 0x184

typedef struct unk_D_86B0FA50 {
    /* 0x00 */ char unk00[0x80];
    /* 0x80 */ s32 unk_80;
    /* 0x84 */ s32 unk_84;
    /* 0x88 */ s32 unk_88;
    /* 0x8C */ s32 unk_8C;
    /* 0x90 */ s32 unk_90;
    /* 0x94 */ char unk94[0x4];
    /* 0x98 */ f32 unk_98;
    /* 0x9C */ s16 unk_9C;
    /* 0x9E */ s16 unk_9E;
    /* 0xA0 */ s16 unk_A0;
    /* 0xA4 */ f32 unk_A4;
    /* 0xA8 */ f32 unk_A8;
    /* 0xAC */ f32 unk_AC;
    /* 0xB0 */ SpriteColorParams unk_B0;
} unk_D_86B0FA50; // size = 0xC8

typedef struct unk_D_86B0FA7C {
    /* 0x00 */ CameraStruct* unk_00;
    /* 0x04 */ Vec3f unk_04;
    /* 0x10 */ s16 unk_10;
    /* 0x12 */ s16 unk_12;
    /* 0x14 */ char unk14[0x2];
    /* 0x16 */ s16 unk_16;
    /* 0x18 */ s16 unk_18;
    /* 0x1C */ f32 unk_1C;
    /* 0x20 */ f32 unk_20;
    /* 0x24 */ s16 unk_24;
    /* 0x26 */ s16 unk_26;
    /* 0x28 */ char unk28[0x2];
    /* 0x2A */ s16 unk_2A;
    /* 0x2C */ s16 unk_2C;
    /* 0x30 */ f32 unk_30;
    /* 0x34 */ f32 unk_34;
    /* 0x38 */ f32 unk_38;
    /* 0x3C */ f32 unk_3C;
    /* 0x40 */ f32 unk_40;
    /* 0x44 */ f32 unk_44;
    /* 0x48 */ char unk48[0x34];
} unk_D_86B0FA7C; // size = 0x7C

typedef struct unk_D_86B0C264 {
    /* 0x00 */ Vec3f unk_00;
    /* 0x0C */ s16 unk_0C;
    /* 0x0E */ s16 unk_0E;
    /* 0x10 */ u16 unk_10;
    /* 0x10 */ u16 unk_12;
    /* 0x14 */ u16 unk_14;
    /* 0x14 */ u16 unk_16;
    /* 0x18 */ s16 unk_18;
    /* 0x1A */ s16 unk_1A;
} unk_D_86B0C264; // size = 0x1C

extern unk_D_86B0C160 gScrollBarSegmentData[];
extern s32 D_86B0E5DC;
extern char** D_86B0E5E0;
extern unk_D_86B0FA78* gCameraTarget;
extern unk_D_86B0FA7C* gCameraState;
extern unk_70D3A0 gMonsterStageData;

s32 BattleContext_HandleState(UNUSED s32 arg0, UNUSED s32 arg1);

s32 Callback_UpdateColorAndPos(s32 arg0, GraphNode* arg1);
s32 Callback_SetScaleLarge(s32 arg0, GraphNode* arg1);
s32 Callback_SetScaleNormal(s32 arg0, GraphNode* arg1);
s32 Callback_SetObjectState(s32 arg0, GraphNode* arg1);
void Diorama_ClearModelSlots(void);
void Diorama_FreeModelSlots(unk_D_86B0E5F0* arg0);
void Diorama_PushModelPool(void);
void Diorama_InitModelSlot(unk_D_86B0E5F0* arg0, unk_D_86B0C4C8* arg1);
void Diorama_SetModelSlotPosition(unk_D_86B0E5F0* arg0, unk_D_86B0C4C8* arg1);
void Diorama_SetGlowFromGroup(s32 arg0);
void Fragment_LoadObjectsForPreset(s32 arg0);
void Diorama_SwitchModelGroup(s32 arg0);
void Diorama_SetGroupCamera(s32 arg0);
void func_86B00680(void);
void Diorama_LoopIdleAnimations(void);
void Diorama_DrawFadeOverlay(void);
void Diorama_DrawGroupTransitionOverlay(void);
s32 Diorama_SlideModelsForward(s32 arg0);
void Diorama_BeginGroupTransition(void);
void Diorama_FinishSequence(void);
void Diorama_UpdateProximityHighlight(s32 arg0);
void Diorama_ReadControllerInput(void);
void Diorama_InitSceneState(void);
s32 StateMachine_Update(void);
void func_86B01004(void);
void Diorama_RenderFrame(void);
void Diorama_RunLoop(void);
void Diorama_RenderFinalFrame(void);
void Diorama_InitScene(void);
s32 BattleState_Handle18(void);

u16 Math_RandomU16Range(s32);
Vec3f* func_86B01404(Vec3f*, Vec3f*);
void Math_ApproachFloat(f32*, f32, f32);

u16 IsPointInSector(CameraStruct* arg0, Fragment2_1GraphNode* arg1, s16 arg2, s16 arg3, f32 arg4, f32 arg5);
void SetCameraOrientationParams(unk_D_86B0E5D4_04* arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4);
void SetCameraFov(unk_D_86B0E5D4_04* arg0, f32 arg1, f32 arg2);
void SetCameraEyeAngles(unk_D_86B0E5D4_04* arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4);
void SetCameraTargetFov(unk_D_86B0E5D4_04* arg0, f32 arg1, f32 arg2);
void SetCameraSmoothing(unk_D_86B0E5D4_04* arg0, f32 arg1, f32 arg2);
void InitCameraFromConfig(unk_D_86B0C160* arg0, unk_D_86B0E5D4* arg1);
void ApplyCameraViewParameters(unk_D_86B0E5D4_04* arg0, unk_D_86B0E5D4* arg1);
s32 UpdateCameraTransition(unk_D_86B0E5D4_04* arg0, unk_D_86B0E5D4* arg1);

void Diorama_DrawEndBackgroundTiles(u8*);
void Diorama_DrawFullscreenTexture(u8*, s32, s32, s32, s32, u8, u8);
void Diorama_DrawEndCaption(void);

s32 Camera_UpdatePrimaryAngles(s32 arg0, GraphNode* arg1);
s32 Camera_UpdateSecondaryAngles(s32 arg0, GraphNode* arg1);
void BattleIntroPanel_InitAnimTables(void);
void BattleIntroPanel_InitSpriteTables(void);
void BattleIntroPanel_InitSoundTables(void);
void BattleIntroPanel_InitInputTables(void);
void Completion_PositionBonusModel(void);
void BattleIntroPanel_InitCameraTables(void);
void BattleIntroPanel_InitColorTables(void);
s32 Completion_WrapDialogText(void);
void Completion_DrawSpeciesRewardText(s16 arg0, s16 arg1);
void Completion_DrawWrappedDialogText(s16 arg0, s16 arg1);
void Completion_ResetDialogText(void);
void Completion_DrawDialogBox(void);
void Completion_UpdateGiftDialogFirstTime(void);
void Completion_UpdateGiftDialogWithExisting(void);
void Gfx_DrawBattleIntroPanels(void);
s32 BattleIntroPanel_ApproachColorAnim(void);
Gfx* BattleIntroPanel_DrawSpriteAnim(void);
s32 BattleIntroPanel_SlideInAnim(void);
s32 BattleIntroPanel_SlideOutAnim(void);
s32 BattleIntro_CameraApproachAnim(void);
void BattleIntroPanel_ResetState(void);
void BattleIntroPanel_SetupChoice(void);
void BattleIntroPanel_HandleChoiceInput(void);
void BattleIntroPanel_HandleConfirmInput(void);
void BattleIntroPanel_AnimSoundTick(void);
void BattleIntroPanel_AnimResetIfDone(void);
void BattleIntroPanel_AnimClamp(void);
void BattleIntroPanel_InputInit(void);
s32 BattleIntroPanel_StateMachine(void);
void BattleIntroPanel_DrawFrame(void);
void BattleIntroPanel_DrawFrameWrapper(UNUSED s32 arg0);
void BattleIntroPanel_FadeInSequence(void);
void BattleIntroPanel_MainLoop(void);
void BattleIntroPanel_FadeOutSequence(void);
void BattleIntroPanel_AllocAndInit(void);
s32 BattleState_Handle21Or26(void);

void Gfx_DrawTexturedRect(u8* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, u8 width, u8 height, u8 uls, u8 ult, u8 lrs, u8 lrt, u8 argB, u8 argC, GfxTileParams* argD, s32 argE);
void UI_DrawAlphaQuad(s32, s32, s32, s32, s32);

s32 ToggleCameraNodeOffsetFromCurrent(s32 arg0, GraphNode* arg1);
s32 SetCameraNodeOffsetInverse(s32 arg0, GraphNode* arg1);
s32 GraphNode_SetColor(s32 arg0, GraphNode* arg1);
void SetGlobalOverlayColor(u8 arg0, u8 arg1, u8 arg2);
void LoadStageResources(void);
void MonsterNode_Init(void);
void MonsterNode_Reset(void);
void MiniCamera_Setup(void);
void MonsterNode_LoadById(void);
void MiniCamera_UpdateForMonster(void);
s32 MonsterNode_UpdateYPos(Fragment2_1GraphNode* arg0, s16 arg1, s16 arg2);
s32 MonsterNode_EaseYPos(Fragment2_1GraphNode* arg0, s16 arg1, s16 arg2);
s32 MonsterLandingSequence(void);
void MonsterNode_SpawnParticles(void);
void UpdateFadeColorFromHealth(void);
void MonsterNode_UpdateIdleAnim(void);
void UIElement_Init(unk_D_86B0FA50* arg0, u8* arg1, f32 arg2, s16 arg3, s16 arg4, s16 arg5);
void BattleUI_InitElements(void);
void MonsterNode_SetupDefault(void);
void MiniCamera_InitDefault(void);
void MonsterNode_SetupCustom(void);
void MiniCamera_InitMonster(void);
void BattleUI_SetStateActive(void);
void BattleContext_SyncMonsterData(void);
void BattleInput_Update(void);
s32 BattleSequence_Update(void);
s32 UIElement_UpdatePos(unk_D_86B0FA50* arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5);
void BattleUI_Render(void);
void BattleScene_Render(void);
void BattleScene_RenderBlank(void);
void BattleSequence_IntroFade(void);
void BattleSequence_MainLoop(void);
void BattleSequence_Outro(void);
void BattleSequence_Init(void);
s32 BattleState_Handle17(void);

s16 GetCameraBaseY(void);
s32 ByteArrayContains(u8 arg0, u8* arg1, s32 arg2);
void ComputeCameraTargetPos(unk_D_86B0FA78* arg0, Vec3f* arg1);
void Camera_UpdateView(void);
f32 ClampFloatByScale(f32 arg0, f32 arg1);
void Camera_SetBaseParams(s16 arg0, s16 arg1, s16 arg2, s16 arg3);
void IntroCamKeyframe_SetDistance(f32 arg0, f32 arg1);
void Camera_SetEyeParams(s16 arg0, s16 arg1, s16 arg2, s16 arg3);
void IntroCamKeyframe_SetAtDistance(f32 arg0, f32 arg1);
void Camera_SetApproachParams(f32 arg0, f32 arg1);
void Camera_InitFromConfig(unk_D_86B0C160* arg0, CameraStruct* arg1);
s32 Intro_UpdateCameraKeyframe(CameraStruct* arg0);

void Scroll_Init(s32 arg0, s32 arg1);
s32 Scroll_GetMode(void);
void Scroll_Update(void);
Gfx* Scroll_Draw(Gfx* gfx, u32 arg1);
void Scroll_RenderIfActive(void);
void Gfx_DrawClippedRect(s16 arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5, s16 arg6, s16 arg7);
void Gfx_LoadTextureAndDrawRect(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u8* arg4, UNUSED s32 arg5);
void Gfx_DrawSpriteWithColors(u8* arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, SpriteColorParams* arg5);
void Gfx_DrawBorderSprite(u8* arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4);

void MewtwoIntro_DrawOverlay(void);
void Stage_SetupCamera(void);
void Input_Update(void);
void Stage_DrawBackgroundSprites(u8* arg0);
void Stage_RenderFrame(void);
s32 Stage_HandleFade(void);
void BattleState_Run(void);
void Stage_Initialize(void);
s32 BattleState_Handle24(void);

void Camera_SetupView(void);
void MessageState_Reset(void);
void func_86B0A81C(void);
void FirstClearBonus_DrawDialogFrame(s16 arg0, s16 arg1, s16 arg2, s16 arg3, u8 arg4, u8 arg5, u8 arg6, u8 arg7);
void MessageState_SetFinished(void);
void MessageState_Clear(void);
s32 MessageState_CopyNextChars(void);
void MessageBox_Draw(void);
void MessageBox_RenderText(void);
void MessageBox_Update(void);
void FirstClearBonus_ReadControllerInput(void);
void func_86B0B4C8(void);
void DrawBackgroundTiles(u8* arg0);
void FirstClearBonus_RenderFrame(void);
s32 BattleCutscene_Process(void);
void FirstClearBonus_RunLoop(void);
void FirstClearBonus_InitScene(void);
s32 BattleState_Handle22Or23(void);

#endif // _FRAGMENT17_H_
