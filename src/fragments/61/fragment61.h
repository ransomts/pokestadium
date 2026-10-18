#ifndef _FRAGMENT61_H_
#define _FRAGMENT61_H_

#include "global.h"
#include "src/11BA0.h"
#include "src/1AB70.h"
#include "src/fragments/47/fragment47.h"

struct unk_D_842168A0;
struct unk_D_84229EB0;

typedef struct unk_D_8423D3A8 {
    /* 0x00 */ u8 unk_00;
    /* 0x01 */ u8 unk_01;
    /* 0x02 */ u8 unk_02;
    /* 0x03 */ u8 unk_03;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ s16 unk_08;
    /* 0x0A */ s16 unk_0A;
    /* 0x0C */ s16 unk_0C;
    /* 0x0E */ ClipRect unk_0E;
    /* 0x16 */ ClipRect unk_16;
    /* 0x20 */ s32 unk_20;
    /* 0x24 */ AssetManager* unk_24;
    /* 0x28 */ unk_func_8001B1FC* unk_28;
    /* 0x2C */ unk_D_838067F0_0168_0000* unk_2C;
} unk_D_8423D3A8; // size >= 0x30

typedef struct unk_D_842168A0_13608 {
    /* 0x00 */ char unk04[0x4];
} unk_D_842168A0_13608; // size >= 0x4

typedef struct unk_D_84229EB0_00024 {
    /* 0x0000 */ unk_D_838067F0_0168_0000 unk_0000[6];
    /* 0x4D10 */ u16 unk_4D10;
    /* 0x4D12 */ char unk_4D12[2];
    /* 0x4D14 */ char unk4D14[0xA];
    /* 0x4D1E */ s16 unk_4D1E;
    /* 0x4D20 */ s16 unk_4D20;
    /* 0x4D24 */ struct unk_D_84229EB0_00024* unk_4D24;
    /* 0x4D28 */ struct unk_D_84229EB0_00024* unk_4D28;
    /* 0x4D2C */ char unk4D2C[0x4];
} unk_D_84229EB0_00024; // size = 0x4D30

typedef struct gItemPanel {
    /* 0x0000 */ u8 unk_0000;
    /* 0x0001 */ u8 unk_0001;
    /* 0x0002 */ u8 unk_0002;
    /* 0x0003 */ u8 unk_0003;
    /* 0x0004 */ u8 unk_0004;
    /* 0x0006 */ s16 unk_0006;
    /* 0x0008 */ s16 unk_0008;
    /* 0x000A */ s16 unk_000A;
    /* 0x000C */ s16 unk_000C;
    /* 0x000E */ s16 unk_000E;
    /* 0x0010 */ s16 unk_0010;
    /* 0x0012 */ s16 unk_0012;
    /* 0x0014 */ s16 unk_0014;
    /* 0x0016 */ s16 unk_0016;
    /* 0x0018 */ s16 unk_0018;
    /* 0x001A */ s16 unk_001A;
    /* 0x001C */ u16 unk_001C;
    /* 0x001E */ char unk_001E[2];
    /* 0x0020 */ char unk0020[0x10];
    /* 0x0030 */ unk_D_838067F0_0168_0000 unk_0030[6];
    /* 0x4D40 */ struct unk_D_842168A0* unk_4D40;
    /* 0x4D44 */ unk_D_8423D3A8* unk_4D44;
    /* 0x4D48 */ struct unk_D_84229EB0* unk_4D48;
} gItemPanel; // size = 0x4D4C

typedef struct unk_D_842168A0_0013C {
    /* 0x00 */ u32 unk_00;
    /* 0x04 */ PokemonData unk_04[1];
} unk_D_842168A0_0013C; // size >= 0x58

typedef struct unk_D_842168A0 {
    /* 0x00000 */ u8 unk_00000;
    /* 0x00001 */ u8 unk_00001;
    /* 0x00002 */ u8 unk_00002;
    /* 0x00003 */ u8 unk_00003;
    /* 0x00004 */ u8 unk_00004;
    /* 0x00005 */ u8 unk_00005;
    /* 0x00006 */ u8 unk_00006;
    /* 0x00007 */ u8 unk_00007;
    /* 0x00008 */ u8 unk_00008;
    /* 0x00009 */ u8 unk_00009;
    /* 0x0000A */ s16 unk_0000A;
    /* 0x0000C */ s16 unk_0000C;
    /* 0x0000E */ s16 unk_0000E;
    /* 0x00010 */ s16 unk_00010;
    /* 0x00012 */ s16 unk_00012;
    /* 0x00014 */ s16 unk_00014;
    /* 0x00016 */ s16 unk_00016;
    /* 0x00018 */ s16 unk_00018;
    /* 0x0001A */ s16 unk_0001A;
    /* 0x0001C */ unk_D_838067F0_003C unk_0001C[13];
    /* 0x0013A */ char unk0013A[0x2];
    /* 0x0013C */ unk_D_842168A0_0013C* unk_0013C;
    /* 0x00140 */ unk_D_838067F0_0168* unk_00140;
    /* 0x00144 */ char unk00144[0x4];
    /* 0x00148 */ unk_D_838067F0_0168 unk_00148[8];
    /* 0x13608 */ gItemPanel* unk_13608;
    /* 0x1360C */ unk_D_8423D3A8* unk_1360C;
} unk_D_842168A0; // size = 0x13610

typedef struct unk_D_84229EB0 {
    /* 0x00000 */ u8 unk_00000;
    /* 0x00001 */ u8 unk_00001;
    /* 0x00002 */ u8 unk_00002;
    /* 0x00003 */ u8 unk_00003;
    /* 0x00004 */ u8 unk_00004;
    /* 0x00005 */ s8 unk_00005;
    /* 0x00006 */ s16 unk_00006;
    /* 0x00008 */ s16 unk_00008;
    /* 0x0000A */ s16 unk_0000A;
    /* 0x0000C */ u8 unk_0000C;
    /* 0x0000D */ u8 unk_0000D;
    /* 0x0000E */ s16 unk_0000E;
    /* 0x00010 */ s16 unk_00010;
    /* 0x00012 */ s16 unk_00012;
    /* 0x00014 */ s16 unk_00014;
    /* 0x00016 */ s16 unk_00016;
    /* 0x00018 */ s16 unk_00018;
    /* 0x0001A */ s16 unk_0001A;
    /* 0x0001C */ s16 unk_0001C;
    /* 0x0001E */ u8 unk_0001E;
    /* 0x0001F */ u8 unk_0001F;
    /* 0x00020 */ u8 unk_00020;
    /* 0x00024 */ unk_D_84229EB0_00024* unk_00024;
    /* 0x00028 */ unk_D_84229EB0_00024 unk_00028[3];
    /* 0x0E7B8 */ char unk0E7B8[0x4D30];
    /* 0x134E8 */ gItemPanel* unk_134E8;
    /* 0x134EC */ unk_D_842168A0* unk_134EC;
    /* 0x134F0 */ unk_D_8423D3A8* unk_134F0;
    /* 0x134F4 */ char unk134F4[0x4];
} unk_D_84229EB0; // size = 0x134F8

typedef struct unk_D_8423D3D8 {
    /* 0x00 */ u8 unk_00;
    /* 0x01 */ u8 unk_01;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ unk_D_800AE540_0004* unk_04;
} unk_D_8423D3D8; // size = 0x8

typedef struct unk_D_84211704 {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ s16 unk_08;
    /* 0x0A */ s8 unk_0A;
    /* 0x0B */ s8 unk_0B;
    /* 0x0C */ s16 unk_0C;
    /* 0x0E */ u16 unk_0E;
} unk_D_84211704; // size = 0x10

s32 CheckPIIdleAndReturnArg(s32 arg0);
char* GetMessageBank24String(s32 arg0);
char* GetMessageBank25String(s32 arg0);
char* GetStadiumModeString(s32 arg0);
char* GetMessageBank1AString(s32 arg0);
char* GetMessageBank06String(s32 arg0);
char* GetMessageBank1AStringCustomBuf(char* arg0, s32 arg1, s32 arg2);
void DrawBorderedBox(s16 arg0, s16 arg1, s16 arg2, s16 arg3);
void DrawColoredBox(s16 arg0, s16 arg1, s16 arg2, s16 arg3, u8 arg4, u8 arg5, u8 arg6, u8 arg7);
void DrawAnimatedGoldBorder(s16 arg0, s16 arg1, s16 arg2, s16 arg3);
void DrawTiledBorder(s16 arg0, s16 arg1, s16 arg2, s16 arg3, u8 arg4, u8 arg5, u8 arg6, u8 arg7);
void DrawSmallTiledBorder(s16 arg0, s16 arg1, s16 arg2, s16 arg3, u8 arg4, u8 arg5, u8 arg6, u8 arg7);
void DrawTopPanel(s16 arg0, s16 arg1);
void DrawAlternateTopPanel(s16 arg0, s16 arg1);
void DrawIconPanel(s16 arg0, s16 arg1, s16 arg2);
void func_84201BC4(s16 arg0, s16 arg1, s16 arg2, Color_RGBA8* arg3, Color_RGBA8* arg4);
void SetupBattleSelectionUI(void);
void PrintMenuOption(s16 arg0, s16 arg1, s16 arg2, s32 arg3);
void DrawOptionsScreen(s16 arg0, s16 arg1, s16 arg2);
void WaitForMenuConfirm(void);
s32 UpdateMenuSelectionInput(void);
s16 RunMenuSelection(void);
void DrawPartyTopPanel(s16 arg0, s16 arg1);
void DrawPartyScreenSubsystems(UNUSED s16 arg0, s16 arg1, s16 arg2);
s16 RunPartyMenuSelection(s16 arg0, s16 arg1, s16 arg2, s32 arg3);
void UpdatePartyScreenSubsystems(UNUSED s16 arg0, UNUSED s32 arg1);
void PartyScreenTransition(s16 arg0, s32 arg1, s16 arg2);
void PartyScreenInputLoop(s16 arg0, s16 arg1, s16 arg2);
void InitBattleSelectionSlots(void);
void SetupBattleSelectionSlot(unk_D_8423D3D8* arg0, s16 arg1);
s32 CommitBattleSelectionSlot(unk_D_8423D3D8* arg0, s16 arg1);
void FadeOutPartyScreen(s32 arg0);
void FadeInPartyScreen(void);
void ShowSelectedMonInfo(s16 arg0, s16 arg1);
s32 RunBattleSelectionMode(void);
s32 RunBattleSelectionModeAlt(void);
void RunRegistrationMode(void);
void RunRentalSelectionMode(void);
void RunTradeSelectionMode(void);
s32 RunMainPartyMenu(void);
void LoadBattleSelectionControllerAssets(void);
void LoadBattleSelectionBackground(void);
s32 RunPartyScreenMain(s32 arg0, UNUSED s32 arg1);

s32 RenderUIElement(s32 arg0, SimpleGfxNode* arg1);
void UpdateSelectedIconPosition(void);
void DrawPlayerInfoEntry(s32 arg0);
void DrawMainMenuScreen(void);
void DrawIconBackgroundRect(s32 arg0, s16 arg1, s16 arg2);
void func_84204760(s32 arg0);
void UpdateIconTransform(s16 arg0, f32 arg1);
void UpdateIconDepthTransform(s16 arg0, f32 arg1);
void SelectNextActiveIcon(void);
void SelectAlternateIcon(void);
void SelectLeftIcon(void);
void SelectRightIcon(void);
void func_84204E0C(void);
void func_84204F78(void);
void func_842050CC(void);
void func_84205200(void);
void func_8420545C(void);
void func_8420563C(void);
s32 func_8420570C(void);
void func_842057AC(void);
void func_8420594C(void);
void func_84205B3C(void);
s32 func_84205C18(s16 arg0);
s32 Menu_Start(s16 arg0, s32 arg1);
s16 Menu_GetSelectedIndex(void);

void DrawSlotBackground(s16 arg0, s16 arg1, s32 arg2);
void DrawSlotGrid(gItemPanel* arg0, s16 arg1, s16 arg2);
void DrawSelectionRect(gItemPanel* arg0);
void DrawItemInfoPanel(gItemPanel* arg0, s32 arg1);
void MarkSlotForRemoval(gItemPanel* arg0);
s32 GbsSyncItemData(gItemPanel* arg0);
s32 CheckStatThresholdForMode(gItemPanel* arg0);
void SetPanelPositionOffscreen(gItemPanel* arg0);
void SetPanelPositionOnscreen(gItemPanel* arg0);
void StartItemMoveAnimation(gItemPanel* a0);
void HandleItemMoveResult(gItemPanel* arg0);
void UpdatePanelSlideDown(gItemPanel* arg0);
void UpdatePanelSlideUp(gItemPanel* arg0);
void ItemPanel_RemoveSelected(gItemPanel* arg0);
void ItemPanel_MoveCursorLeft(gItemPanel* arg0);
void ItemPanel_MoveCursorRight(gItemPanel* arg0);
void ItemPanel_MoveCursorUp(gItemPanel* arg0);
void ItemPanel_MoveCursorDown(gItemPanel* arg0);
void ItemPanel_HandleInput(gItemPanel* arg0);
void ItemPanel_CheckModeTransition(gItemPanel* arg0);
void ItemPanel_HandleMenuSelection(gItemPanel* arg0);
void ItemPanel_HandleAltMenuSelection(gItemPanel* arg0);
void ItemPanel_HandleModeSpecificSelection(gItemPanel* arg0);
void ItemPanel_HandleActionSelection(gItemPanel* arg0);
void ItemPanel_HandleCancelSelection(gItemPanel* arg0);
void ItemPanel_UpdateCursorAnim(gItemPanel* arg0);
s32 UpdateItemStateMachine(gItemPanel* arg0);
s32 ItemPanel_Init(gItemPanel* arg0, unk_D_842168A0* arg1, unk_D_8423D3A8* arg2, unk_D_84229EB0* arg3, s16 arg4, u16 arg5,
                  char* arg6, s16 arg7, s16 arg8, s16 arg9);
s32 ItemPanel_StartSlideDown(gItemPanel* arg0, s16 arg1);
s32 ItemPanel_StartSlideUp(gItemPanel*);
s32 ItemPanel_ClearAndReset(gItemPanel*);
s32 ItemPanel_ConfirmSelection(gItemPanel*);
s32 ItemPanel_AddItem(gItemPanel*, unk_D_838067F0_0168_0000*);
s32 ItemPanel_RemoveCurrent(gItemPanel*);
s32 ItemPanel_IsItemDuplicate(gItemPanel*, unk_D_838067F0_0168_0000*);
s32 ItemPanel_HasItem(gItemPanel*, unk_D_838067F0_0168_0000*);
s32 ItemPanel_IsOffscreen(gItemPanel* arg0);
void ItemPanel_LoadItems(gItemPanel* arg0, PokemonData* arg1, s16 arg2);

void DrawPokemonMenu(unk_D_842168A0*, s32);
s32 InitPokemonMenu(unk_D_842168A0*, gItemPanel*, unk_D_8423D3A8*, s16, s16, s16, s16, s16, unk_D_842168A0_0013C*);
s32 UpdateMenuState(unk_D_842168A0*);
s32 TriggerScrollUp(unk_D_842168A0*, s16);
s32 TriggerScrollDown(unk_D_842168A0*);
s32 TriggerSelectionAnim(unk_D_842168A0*);
void SetMenuActive(unk_D_842168A0*);
s32 RequestNextPokemon(unk_D_842168A0*);
s32 IsMenuInState2(unk_D_842168A0*);

void PrintMoveEntry(s16 arg0, s16 arg1, s16 arg2, s16 arg3, s8* arg4);
void DrawMoveList(s16 arg0, s16 arg1, s16 arg2, s16 arg3);
void DrawMoveTypeBackground(s16 arg0, s16 arg1, s16 arg2);
void DrawTransferPakErrorScreen(s16 arg0, s16 arg1, s32 arg2);
s16 func_8420B870(s16 arg0, s16 arg1, char* arg2);
void DrawPokemonMoveInfo(unk_D_8423D3A8* arg0, s32 arg1);
void func_8420C360(unk_D_8423D3A8* arg0);
void HandleMoveScreenInput(unk_D_8423D3A8* arg0);
void InitMoveScreenConfirm(unk_D_8423D3A8* arg0);
void InitMoveScreenExit(unk_D_8423D3A8* arg0);
s32 MoveScreen_Create(unk_D_8423D3A8* arg0);
s32 MoveScreen_Update(unk_D_8423D3A8* arg0);
s32 MoveScreen_Start(unk_D_8423D3A8* arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5,
    unk_D_838067F0_0168_0000* arg6, s16 arg7);
s32 func_8420C6D8(unk_D_8423D3A8* arg0, s16 arg1, s16 arg2, unk_D_838067F0_0168_0000* arg3);
s32 GetSelectedMoveIndex(unk_D_8423D3A8* arg0);
void Menu_PrintItem(s16 arg0, s16 arg1, s16 arg2, char* arg3);
void func_8420C844(unk_D_84211704* arg0);
void func_8420C930(unk_D_84211704* arg0);
void func_8420CA00(unk_D_84211704* arg0);
void func_8420CAD0(unk_D_84211704* arg0);
void func_8420CBA0(unk_D_84211704* arg0);
void func_8420CC54(unk_D_84211704* arg0);
void func_8420CCAC(unk_D_84211704* arg0);
void func_8420CE24(unk_D_84211704* arg0);
void func_8420CFC4(unk_D_84211704* arg0);
void func_8420D144(unk_D_84211704* arg0);
void func_8420D2BC(unk_D_84211704* arg0);
void func_8420D370(unk_D_84211704* arg0, s16 arg1);
void func_8420D464(unk_D_84211704* arg0, s16 arg1);
void func_8420D4F8(s32 arg0);
void func_8420D75C(void);
void func_8420D938(void);
void func_8420D978(void);
s32 func_8420D9B0(void);
s32 func_8420DA28(s16 arg0, Controller* arg1);
s32 func_8420DAF4(s16 arg0);
s16 func_8420DB48(s16 arg0);
s32 func_8420DBA0(unk_D_84229EB0_00024* arg0);
void func_8420DC78(unk_D_84229EB0_00024* arg0);
void DrawPokemonSlot(unk_D_84229EB0* arg0, s16 arg1, s16 arg2, unk_D_84229EB0_00024* arg3);
void DrawHeaderBar(s16 arg0, s16 arg1);
void DrawVerticalScrollBar(unk_D_84229EB0* arg0);
void DrawBottomBar(unk_D_84229EB0* arg0);
void DrawSideBar(unk_D_84229EB0* arg0);
void RenderVisiblePokemonEntries(unk_D_84229EB0* arg0);
void UpdateAndRenderPokemonListScreen(unk_D_84229EB0* arg0, s32 arg1);
unk_D_84229EB0_00024* GetPrevPage(unk_D_84229EB0_00024* arg0, s32 arg1);
unk_D_84229EB0_00024* GetNextPage(unk_D_84229EB0_00024* arg0, s32 arg1);
s32 LoadPokemonPageFromGbs(unk_D_84229EB0_00024* arg0, s16 arg1);
void UpdateSelectionHighlight(unk_D_84229EB0* arg0);
void ResetPokemonListState(unk_D_84229EB0* arg0);
void func_8420F524(unk_D_84229EB0* arg0);
void ScrollUpStep(unk_D_84229EB0* arg0);
void ScrollDownStep(unk_D_84229EB0* arg0);
void func_8420F5F0(unk_D_84229EB0* arg0);
void func_8420F654(unk_D_84229EB0* arg0);
void func_8420F754(unk_D_84229EB0* arg0);
void ProcessPokemonListInput(unk_D_84229EB0* arg0);
void func_8420F9C8(unk_D_84229EB0* arg0);
void func_8420FA88(unk_D_84229EB0* arg0);
void func_8420FB4C(unk_D_84229EB0* arg0);
void func_8420FC0C(unk_D_84229EB0* arg0);
void func_8420FCCC(unk_D_84229EB0* arg0);
void func_8420FDDC(unk_D_84229EB0* arg0);
void func_8420FE50(unk_D_84229EB0* arg0);
void func_8420FE90(unk_D_84229EB0* arg0);
void func_8420FEC0(unk_D_84229EB0* arg0);
void func_8420FFB0(unk_D_84229EB0* arg0);
void func_8421009C(unk_D_84229EB0* arg0);
void func_8421015C(unk_D_84229EB0* arg0);
void func_84210328(unk_D_84229EB0* arg0);
void func_8421059C(unk_D_84229EB0* arg0);
void func_84210668(unk_D_84229EB0* arg0);
s32 func_842106FC(unk_D_84229EB0* arg0);
s32 func_8421089C(unk_D_84229EB0* arg0, gItemPanel* arg1, unk_D_842168A0* arg2, unk_D_8423D3A8* arg3,
                  s16 arg4, s16 arg5, s16 arg6, s16 arg7);
s32 func_84210A18(unk_D_84229EB0* arg0);
s32 func_84210A48(unk_D_84229EB0* arg0, u16 arg1, char* arg2, unk_D_838067F0_0168_0000* arg3);
s32 func_84210B54(unk_D_84229EB0* arg0);
s32 func_84210B60(unk_D_84229EB0* arg0, unk_D_84229EB0_00024** arg1);
void func_84210C80(unk_D_84229EB0* arg0, s16 arg1);

#endif // _FRAGMENT61_H_
