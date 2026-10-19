#ifndef _FRAGMENT63_H_
#define _FRAGMENT63_H_

#include "global.h"
#include "src/3FB0.h"
#include "src/1AB70.h"
#include "src/geo_layout.h"

typedef struct unk_D_84B19910_002 {
    /* 0x02 */ s16 unk_00;
    /* 0x04 */ s16 unk_02;
    /* 0x06 */ s16 unk_04;
} unk_D_84B19910_002; 

typedef struct unk_D_84B19910 {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ unk_D_84B19910_002 unk_02;
    ///* 0x02 */ s16 unk_02;
    ///* 0x04 */ s16 unk_04;
    ///* 0x06 */ s16 unk_06;
} unk_D_84B19910; // size = 0x8

typedef struct unk_D_84B1A598 {
    /* 0x0000 */ char unk0000[0x1];
    /* 0x0001 */ u8 unk_0001;
    /* 0x0002 */ u8 unk_0002;
    /* 0x0003 */ u8 unk_0003;
    /* 0x0004 */ GraphNode* unk_0004;
    /* 0x0008 */ Fragment2_1GraphNode unk_0008[128];
    /* 0xB408 */ BinArchive* unk_B408;
    /* 0xB40C */ BinArchive* unk_B40C;
} unk_D_84B1A598; // size >= 0xB410

typedef struct unk_D_84B2665C {
    /* 0x00 */ u8 unk_00;
    /* 0x01 */ u8 unk_01;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ char unk06[0x2];
} unk_D_84B2665C; // size >= 0x8

typedef struct unk_D_84B259A8 {
    /* 0x00 */ u8 unk_00;
    /* 0x01 */ u8 unk_01;
    /* 0x02 */ s16 unk_02[5];
    /* 0x0C */ void* unk_0C;
    /* 0x10 */ void* unk_10;
    /* 0x14 */ void* unk_14;
    /* 0x18 */ void* unk_18;
    /* 0x1C */ void* unk_1C;
    /* 0x20 */ Fragment2_1GraphNode* unk_20;
    /* 0x24 */ unk_D_86002F34* unk_24;
    /* 0x28 */ unk_D_86002F34* unk_28;
    /* 0x2C */ unk_D_86002F34* unk_2C;
    /* 0x30 */ unk_D_86002F34* unk_30;
    /* 0x34 */ unk_D_86002F34* unk_34;
    /* 0x38 */ unk_D_86002F34* unk_38;
    /* 0x3C */ char unk3C[0x4];
} unk_D_84B259A8; // size >= 0x40

typedef struct unk_D_84B259E8 {
    /* 0x00 */ u8 unk_00;
    /* 0x01 */ u8 unk_01;
    /* 0x02 */ u8 unk_02;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ Fragment2_1GraphNode* unk_08;
    /* 0x0C */ GraphNode* unk_0C;
    /* 0x10 */ u8* unk_10[4];
    /* 0x20 */ char unk20[0x10];
    /* 0x30 */ FramebufferImage* unk_30[4];
} unk_D_84B259E8; // size >= 0x40

typedef struct unk_D_84B25A58 {
    /* 0x00 */ u8 unk_00;
    /* 0x01 */ u8 unk_01;
    /* 0x02 */ u8 unk_02;
    /* 0x04 */ Fragment2_1GraphNode* unk_04;
    /* 0x08 */ unk_D_86002F34* unk_08;
    /* 0x0C */ unk_D_86002F34* unk_0C;
    /* 0x10 */ unk_D_86002F34* unk_10;
    /* 0x14 */ unk_D_86002F34* unk_14;
    /* 0x18 */ unk_D_86002F34* unk_18;
    /* 0x1C */ SpriteDisplay* unk_1C;
    /* 0x20 */ u16 (*unk_20)[0x640];
    /* 0x24 */ FramebufferImage* unk_24;
    /* 0x28 */ FramebufferImage* unk_28;
    /* 0x2C */ u8 unk_2C[12];
} unk_D_84B25A58; // size = 0x38

typedef struct unk_D_84B25A90 {
    /* 0x00 */ u8 unk_00;
    /* 0x00 */ u8 unk_01;
    /* 0x04 */ Fragment2_1GraphNode* unk_04;
    /* 0x08 */ unk_D_86002F34* unk_08;
    /* 0x0C */ unk_D_86002F34* unk_0C;
    /* 0x10 */ unk_D_86002F34* unk_10;
    /* 0x14 */ unk_D_86002F34* unk_14;
    /* 0x18 */ unk_D_86002F34* unk_18;
    /* 0x1C */ u8* unk_1C;
    /* 0x20 */ u8* unk_20;
    /* 0x24 */ u8** unk_24;
    /* 0x28 */ s8 unk_28[4];
    /* 0x2C */ char unk2C[0x4];
} unk_D_84B25A90; // size = 0x30

typedef struct unk_D_84B25AC0_000 {
    /* 0x00 */ Fragment2_1GraphNode* unk_00;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ Color_RGB8 unk_08;
    /* 0x0C */ u8* unk_0C;
} unk_D_84B25AC0_000; // size = 0x10

typedef struct unk_D_84B25AC0_0A0 {
    /* 0x00 */ Fragment2_1GraphNode* unk_00;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ s16 unk_08;
    /* 0x0A */ Color_RGBA8 unk_0A;
} unk_D_84B25AC0_0A0; // size = 0x10

typedef struct unk_D_84B25AC0 {
    /* 0x000 */ unk_D_84B25AC0_000 unk_000[10];
    /* 0x0A0 */ unk_D_84B25AC0_0A0 unk_0A0[10][8];
    /* 0x5A0 */ u8 unk_5A0;
    /* 0x5A1 */ s8 unk_5A1;
    /* 0x5A2 */ s8 unk_5A2;
    /* 0x5A3 */ s8 unk_5A3;
    /* 0x5A4 */ f32 unk_5A4;
    /* 0x5A8 */ Fragment2_1GraphNode* unk_5A8;
    /* 0x5AC */ Fragment2_1GraphNode* unk_5AC;
    /* 0x5B0 */ unk_D_86002F34* unk_5B0;
    /* 0x5B4 */ unk_D_86002F34* unk_5B4;
    /* 0x5B8 */ unk_D_86002F34* unk_5B8;
    /* 0x5BC */ char unk5BC[0x4];
} unk_D_84B25AC0; // size = 0x5C0

typedef struct unk_D_84B26640_010_010 {
    /* 0x00 */ u8 unk_00;
    /* 0x01 */ s8 unk_01;
    /* 0x02 */ s8 unk_02;
    /* 0x04 */ Fragment2_1GraphNode* unk_04;
    /* 0x08 */ unk_D_86002F34* unk_08;
} BarState; // size = 0xC

typedef struct unk_D_84B26640 {
    /* 0x00 */ BarState unk_00;
    /* 0x00 */ char unk0C[0x4];
    /* 0x00 */ BarState unk_10;
    /* 0x00 */ unk_D_84B2665C unk_1C;
    /* 0x00 */ unk_D_84B2665C unk_28;
} unk_D_84B26640; // size = 0x30

typedef struct unk_func_84B067B4 {
    /* 0x000 */ char unk00[0x10];
    /* 0x010 */ char unk_010[4];
    /* 0x014 */ char unk14[0x24];
    /* 0x038 */ u16 unk_038;
    /* 0x03A */ char unk03A[0x1F6];
} unk_func_84B067B4; // size = 0x230

typedef struct unk_D_84B17550 {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ s16 unk_08;
    /* 0x0A */ s16 unk_0A;
    /* 0x0C */ s16 unk_0C;
    /* 0x0E */ s16 unk_0E;
    /* 0x10 */ s16 unk_10;
} unk_D_84B17550; // size = 0x12

extern SpeciesDisplayParams gSpeciesDisplayParamsFront[];
extern SpeciesDisplayParams gSpeciesDisplayParamsBack[];

void Battle_SavePokemonNames(void);
void Battle_IncrementPlayerName(void);
void Battle_SetProgressFlags(void);
void Battle_UpdateStageProgress(void);
char* Battle_GetMessageString(s32);
char* Battle_GetMessageStringBuffer(char* arg0, s32 arg1, u32 arg2);
s32 Battle_ProcessResult(s32 arg0, unk_D_86002F34_alt8* arg1);
void GraphNode_Reset(Fragment2_1GraphNode* arg0);
void Battle_ResetGraphNodes(void);
void Gfx_DrawPanel(s16, s16, s16, s16, u8, u8, u8, u8);
void Battle_DrawTrainerInfo(FramebufferImage*, s16, u8*, u8*);
void Battle_AnimateSprites(s16 arg0);
void Battle_SetSpriteAlpha(s16 arg0);
void Battle_BeginFrame(void);
void Battle_ProcessFrame(void);
s32 Battle_MainLoop(void);
void Battle_UpdateAndRender(void);
void Battle_InitGraphics(void);
s32 Battle_ErrorSequence(void);
void Battle_CheckPokemonSpecies(void);
void BattlePrep_UpdateRoundIntroScene(void);
void BattlePrep_InitRoundIntroSubScenes(void);
void BattlePrep_RunNormalRoundIntro(void);
void BattlePrep_RunFinalRoundIntro(void);
void BattlePrep_RunBadgeCarouselIntro(void);
void BattlePrep_RunBallBurstTransition(void);
void BattlePrep_FadeInBallBurstTransition(void);
void BattlePrep_FadeToTransparentEnding(void);
s32 Battle_HandleMenuNext(void);
s32 Battle_HandleMenuPrev(void);
s32 Battle_HandleExit(void);
s32 Battle_HandleWait(void);
s32 Battle_ProcessBattleStep(void);
s32 Battle_ProcessSpecialStep(void);
s32 Battle_ProcessFinalStep(void);
u8 Battle_CheckPokemonReady(void);
s32 Battle_RunStateDispatcher(void);
s32 Battle_ExitSequence(void);
void Battle_InitGraphRoots(void);
s32 Battle_Run(s32 arg0, UNUSED s32 arg1);

s16 BattlePrep_RandomStarOffset(void);
void BattleResult_ProcessGraphics(unk_D_84B19910* arg0);
void Battle_UpdateInputBuffer(unk_D_84B19910* arg0);
void Input_UpdateBuffer(unk_D_84B19910* arg0);

s32 RenderUI_BackgroundSegment(s32 arg0, SimpleGfxNode* arg1);
s32 RenderUI_FrontLayerSegment(s32 arg0, SimpleGfxNode* arg1);
s32 RenderUI_TwoLayerSegment(s32 arg0, SimpleGfxNode* arg1);
s32 RenderUI_MiddleLayerSegment(s32 arg0, SimpleGfxNode* arg1);
s32 SetNodeZFromAnim(s32 arg0, unk_D_86002F34_alt5* arg1);
void BattlePrep_CarouselStepFirstItem(unk_D_84B259A8* arg0, s16 arg1);
void BattlePrep_CarouselStepNTSC(unk_D_84B259A8* arg0, s16 arg1);
void BattlePrep_CarouselStepPAL(unk_D_84B259A8* arg0, s16 arg1);
void BattlePrep_CarouselStepFinalNTSC(unk_D_84B259A8* arg0, s16 arg1);
void BattlePrep_CarouselStepFinalPAL(unk_D_84B259A8* arg0, s16 arg1);
void BattlePrep_UpdateCarousel(unk_D_84B259A8* arg0);
void BattlePrep_CarouselExitAnimation(unk_D_84B259A8* arg0);
void BattlePrep_CarouselEntryAnimation(unk_D_84B259A8* arg0);
void ErrorScreen_Update(unk_D_84B259A8* arg0);
void BattlePrep_InitCarouselBanner(unk_D_84B259A8* arg0, s16 arg1, s16 arg2);
void BattlePrep_InitCarouselGymBadgeSlot(unk_D_84B259A8* arg0, s16 arg1, s16 arg2, s16 arg3);
void BattlePrep_InitCarouselLeftIcon(unk_D_84B259A8* arg0, s16 arg1);
void BattlePrep_InitCarouselRightIcon(unk_D_84B259A8* arg0, s16 arg1);
void BattlePrep_InitCarouselCupIcon(unk_D_84B259A8* arg0, s16 arg1);
void ErrorScreen_SetupNodes(unk_D_84B259A8* arg0, Fragment2_1GraphNode* arg1);
void ErrorScreen_Finish(unk_D_84B259A8* arg0);
void BattlePrep_InitCarouselExit(unk_D_84B259A8* arg0, Fragment2_1GraphNode* arg1);
void BattlePrep_LoadBannerAssets(unk_D_84B259A8* arg0);
void BattlePrep_AdjustBannerTextureOffset(unk_D_84B259A8* arg0);
void BattlePrep_LoadBannerGeoLayouts(unk_D_84B259A8* arg0);
void SetBarSegmentColors(unk_D_86002F34* arg0, Color_RGBA8* arg1, Color_RGBA8* arg2);
void UpdateBarSegmentColors(unk_D_84B259A8* arg0);
void ResetBarSegmentState(unk_D_84B259A8* arg0);
s32 RenderUI_BarSegment(s32 arg0, SimpleGfxNode* arg1);
s32 RenderUI_HighlightedBar(s32 arg0, SimpleGfxNode* arg1);
s32 RenderUI_SegmentImage(s32 arg0, SimpleGfxNode* arg1);
s32 RenderUI_HighlightedSegment(s32 arg0, SimpleGfxNode* arg1);
void DrawTransferPakError(s32 arg0);
void ResetErrorScreenGraphNodes(unk_D_84B259E8* arg0);
void AnimateErrorScreenSlideIn(unk_D_84B259E8* arg0);
void AnimateErrorScreenSlideOut(unk_D_84B259E8* arg0);
void AnimateErrorScreenShow(unk_D_84B259E8* arg0);
void AnimateErrorScreenHide(unk_D_84B259E8* arg0);
void UpdateErrorScreenAnimation(unk_D_84B259E8* arg0);
void SetupErrorScreenGraphNodes(unk_D_84B259E8* arg0, Fragment2_1GraphNode* arg1, s16 arg2);
void BattlePrep_RenderBadgeBackground(unk_D_84B259E8* arg0, s16 arg1, char* arg2);
s32 AlignMemoryBlockTo64(s32* arg0);
void LoadTransferPakErrorImages(unk_D_84B259E8* arg0, BinArchive* arg1, BinArchive* arg2);
void InitTransferPakErrorScreen(unk_D_84B259E8* arg0, BinArchive* arg1, BinArchive* arg2);

s32 HealthBar_SetSegment(s32 arg0, SimpleGfxNode* arg1);
s32 PowerGauge_SetSegment(s32 arg0, SimpleGfxNode* arg1);
s32 SpriteDisplay_DrawSegment(s32 arg0, SimpleGfxNode* arg1);
s32 UI_ShimmerEffect(s32 arg0, SimpleGfxNode* arg1);
s32 UI_SlideElements(BattleUiState* arg0, s16 arg1);
void Camera_Shake(BattleUiState* arg0, s16 arg1);
s32 PowerGauge_AnimateStepA(BattleUiState* arg0, s16 arg1);
s32 PowerGauge_AnimateStepB(BattleUiState* arg0, s16 arg1);
void PowerGauge_Update(BattleUiState* arg0);
void SpriteAnimation_Tick(BattleUiState* arg0);
void UI_StateMachine(BattleUiState* arg0);
void SpriteDisplay_SetupBattle(BattleUiState* arg0);
void SpriteDisplay_SetupDoubleBattle(BattleUiState* arg0);
void UI_Init(BattleUiState* arg0, BinArchive* arg1);
void UI_SetSingleBattlePositions(BattleUiState* arg0);
void UI_SetDoubleBattlePositions(BattleUiState* arg0);
s32 UI_WaitUntilFinished(BattleUiState* arg0, Fragment2_1GraphNode* arg1);
void UI_SetupGraphNodes(BattleUiState* arg0, CameraStruct* arg1);

s32 DrawPokemonFrontSprite(s32 arg0, SimpleGfxNode* arg1);
s32 DrawPokemonStatusIcon(s32 arg0, SimpleGfxNode* arg1);
s32 DrawPokemonItemIcon(s32 arg0, SimpleGfxNode* arg1);
s32 DrawHPBarSegment(s32 arg0, SimpleGfxNode* arg1);
s32 DrawHPBarSegmentAlt(s32 arg0, SimpleGfxNode* arg1);
void DrawPlayerHealthBars(unk_D_84B25A58* arg0, s32 arg1);
void DrawDoubleBattleHealthBars(unk_D_84B25A58* arg0, s32 arg1);
void SetHPBarCriticalFlag(unk_D_84B25A58* arg0, s32 arg1);
void SetDoubleBattleHPBarCriticalFlag(unk_D_84B25A58* arg0, s32 arg1);
void InitHealthBarGraphNodes(unk_D_84B25A58* arg0);
void InitDoubleBattleHealthBarGraphNodes(unk_D_84B25A58* arg0);
void InitDoubleBattleHealthBarGraphNodes_Alt(unk_D_84B25A58* arg0);
void InitDoubleBattleHealthBarGraphNodes_Alt2(unk_D_84B25A58* arg0);
void AnimateHealthBarSlideIn(unk_D_84B25A58* arg0, s16 arg1);
void AnimateDoubleHealthBarSlideIn(unk_D_84B25A58* arg0, s16 arg1);
void AnimateHealthBarDrain(unk_D_84B25A58* arg0, s16 arg1);
void AnimateDoubleHealthBarDrain(unk_D_84B25A58* arg0, s16 arg1);
void AnimateHealthBarDrainFast(unk_D_84B25A58* arg0, s16 arg1);
void AnimateDoubleHealthBarDrainFast(unk_D_84B25A58* arg0, s16 arg1);
void AnimateHealthBarEntry(unk_D_84B25A58* arg0, s16 arg1);
void AnimateDoubleHealthBarEntry(unk_D_84B25A58* arg0, s16 arg1);
void UpdateHealthBarAnimation(unk_D_84B25A58* arg0);
void AdvanceSpriteAnimation(unk_D_84B25A58* arg0);
void UI_UpdateState(unk_D_84B25A58* arg0);
void SetupSingleBattleSpriteSlots(unk_D_84B25A58* arg0);
void SetupDoubleBattleSpriteSlots(unk_D_84B25A58* arg0);
void UI_Setup(unk_D_84B25A58* arg0, BinArchive* arg1);
s32 UI_WaitUntilReady(unk_D_84B25A58* arg0, Fragment2_1GraphNode* arg1);
void UpdateSingleBattleSpriteImages(unk_D_84B25A58* arg0);
void UpdateDoubleBattleSpriteImages(unk_D_84B25A58* arg0);
void UI_InitElement(unk_D_84B25A58* arg0);

s32 SetBattleBackgroundTexture0(s32 arg0, SimpleGfxNode* arg1);
s32 BattlePrepBadgeAward_DrawBadgeIconAlt(s32 arg0, SimpleGfxNode* arg1);
s32 BattlePrepBadgeAward_DrawSparkle(s32 arg0, SimpleGfxNode* arg1);
s32 BattlePrepBadgeAward_DrawGlowFade(s32 arg0, SimpleGfxNode* arg1);
void func_84B0B054(void);
void BattlePrepBadgeAward_SlideInStep(unk_D_84B25A90* arg0);
void BattlePrepBadgeAward_RevealStep(unk_D_84B25A90* arg0);
void BattlePrepBadgeAward_SpawnSparkleParticle(unk_D_84B25A90* arg0, Fragment2_1GraphNode* arg1, s16 arg2);
void BattlePrepBadgeAward_UpdateSparkleStep(unk_D_84B25A90* arg0);
void BattlePrepBadgeAward_ScatterStep(unk_D_84B25A90* arg0);
void UI_UpdateElement(unk_D_84B25A90* arg0);
void UI_AnimateBar(unk_D_84B25A90* arg0, Fragment2_1GraphNode* arg1);
void BattlePrepBadgeAward_StartScatter(unk_D_84B25A90* arg0);
void UI_InitElement2(unk_D_84B25A90* arg0);

s32 Fragment63_RenderCallbackBarA(s32 arg0, SimpleGfxNode* arg1);
s32 Fragment63_RenderCallbackBarB(s32 arg0, SimpleGfxNode* arg1);
s32 Fragment63_RenderCallbackBarEnv(s32 arg0, SimpleGfxNode* arg1);
void BattlePrepStarBurst_InitSparkSlot(unk_D_84B25AC0_000* arg0, unk_D_86002F34* arg1, s16 arg2, s16 arg3, s16 arg4);
void BattlePrepStarBurst_UpdateSparkSlot(unk_D_84B25AC0_000* arg0);
s32 Fragment63_RenderCallbackIconEnv(s32 arg0, SimpleGfxNode* arg1);
void BattlePrepStarBurst_InitRainbowParticle(unk_D_84B25AC0_0A0* arg0, unk_D_86002F34* arg1, s16 arg2, s16 arg3, s16 arg4);
void BattlePrepStarBurst_SpawnTrailCopy(unk_D_84B25AC0_0A0* arg0, unk_D_84B25AC0_0A0* arg1);
void BattlePrepStarBurst_SpawnFlashCopy(unk_D_84B25AC0_0A0* arg0, unk_D_84B25AC0_0A0* arg1, s16 arg2);
void BattlePrepStarBurst_SpawnScatterParticle(unk_D_84B25AC0_0A0* arg0, unk_D_86002F34* arg1, Vec3f* arg2);
void BattlePrepStarBurst_UpdateRainbowGradientStep(unk_D_84B25AC0_0A0* arg0);
void BattlePrepStarBurst_UpdateTrailFadeStep(unk_D_84B25AC0_0A0* arg0);
void BattlePrepStarBurst_UpdateFlashFadeStep(unk_D_84B25AC0_0A0* arg0);
void BattlePrepStarBurst_UpdateScatterFallStep(unk_D_84B25AC0_0A0* arg0);
void BattlePrepStarBurst_UpdateRainbowParticle(unk_D_84B25AC0_0A0* arg0);
void BattlePrepStarBurst_UpdateBurstEffect(unk_D_84B25AC0* arg0);
void BattlePrepStarBurst_UpdateFlightArc(unk_D_84B25AC0* arg0);
void BattlePrepStarBurst_UpdateRainbowAftermath(unk_D_84B25AC0* arg0);
void BattlePrepStarBurst_UpdateSparkAftermath(unk_D_84B25AC0* arg0);
void BattlePrepStarBurst_UpdateExitSlide(unk_D_84B25AC0* arg0);
void BattlePrepStarBurst_UpdateFirstClearExit(unk_D_84B25AC0* arg0);
void UI_UpdateBar(unk_D_84B25AC0* arg0);
void UI_LinkBarToNode(unk_D_84B25AC0* arg0, Fragment2_1GraphNode* arg1, Fragment2_1GraphNode* arg2);
void UI_ResetElement(unk_D_84B25AC0* arg0);
void UI_SetBarPosition(unk_D_84B25AC0* arg0, s8 arg1, s8 arg2);
void BarIdleCallback(BarState* arg0);
void BarGrowStep(BarState* arg0);
void BarShrinkStep(BarState* arg0);
void BarUpdateCallback(BarState* arg0);
void BarInit(BarState* arg0, Fragment2_1GraphNode* arg1);
void BarStartShrink(BarState* arg0);
void BarCreate(BarState* arg0, u8 arg1);
void BattlePrep_DrawCursorArrow(unk_D_84B2665C* arg0, s16 arg1, s16 arg2);
void MenuItem_Print(unk_D_84B2665C* arg0, s16 arg1, s16 arg2, s16 arg3, s32 arg4, s8* arg5);
void RenderBattleStatusPanel(unk_D_84B2665C* arg0, unk_D_84B17550* arg1);
void RenderBattleOptionsPanel(unk_D_84B2665C* arg0, unk_D_84B17550* arg1);
void RenderBattleSummaryPanel(unk_D_84B2665C* arg0, unk_D_84B17550* arg1);
void RenderBattleHPPanel(unk_D_84B2665C* arg0, unk_D_84B17550* arg1);
void RenderBattleScorePanel(unk_D_84B2665C* arg0, unk_D_84B17550* arg1);
void RenderBattleModeTitle(unk_D_84B2665C* arg0, unk_D_84B17550* arg1);
void RenderBattleMatchupPanel(unk_D_84B2665C* arg0, unk_D_84B17550* arg1);
void RenderBattleItemIcons(s16 arg0, s16 arg1, unk_D_800AE540_1194* arg2);
void UpdateFlashingTextColor(unk_D_800AE540_1194* arg0);
void BattlePrep_DrawTeamPreview(unk_D_84B2665C* arg0, unk_D_84B17550* arg1);
void BattlePrep_DrawStreakGiveUpPrompt(unk_D_84B2665C* arg0, unk_D_84B17550* arg1);
void RenderMenuPanel(unk_D_84B2665C* arg0);
void BattlePrep_RunQuitMenu(unk_D_84B2665C* arg0);
void BattlePrep_RuleWindowExpanding(unk_D_84B2665C* arg0);
void BattlePrep_RuleWindowCollapsing(unk_D_84B2665C* arg0);
void UI_UpdatePanel(unk_D_84B2665C* arg0);
void Menu_SetOption(unk_D_84B2665C* arg0, s16 arg1);
void BattleMenu_UpdateState(unk_D_84B2665C* arg0);
s32 Menu_GetInput(unk_D_84B2665C* arg0);


#endif // _FRAGMENT63_H_
