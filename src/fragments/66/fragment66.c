#include "fragment66.h"
#include "src/12D80.h"
#include "src/17300.h"
#include "src/19840.h"
#include "src/1C720.h"
#include "src/1CF30.h"
#include "src/20470.h"
#include "src/232C0.h"
#include "src/2E110.h"
#include "src/2E460.h"
#include "src/3FB0.h"
#include "src/485C0.h"
#include "src/48C60.h"
#include "src/49790.h"
#include "src/4F410.h"
#include "src/6A40.h"
#include "src/6BC0.h"
#include "src/DDC0.h"
#include "src/F420.h"
#include "src/geo_layout.h"
#include "src/memory.h"
#include "src/stage_loader.h"
#include "src/util.h"

static GraphNode* gCameraGraphNode;
static GraphNode* gPikachuGeoNode;
static unk_D_86002F30* gPikachuModelData;
static char** gMoveNameBank;
static char** gStadiumMessageBank;
static Fragment2_1GraphNode gPikachuNodes[4];
static unk_D_832025C8 gTextFadeState;
static unk_D_832027C8 gPikachuSession;

static s32 gPikachuActive = 0;
static s32 gPikachuVisibilityState = -1;
static char* gCurrentUIMessage = NULL;
static u32 gPikachuGeoLayout[] = {
    0x0C000000,  0x05000000, 0x0B00001E,    0x00000000, 0x014000F0, 0x00000320, 0x00000000, 0x000005DC, 0x05000000,
    0x0D000000,  0x05000000, 0x0E000002,    0x05000000, 0x22010000, 0x8C200060, 0x06000000, 0x14000000, 0x002B0012,
    0xFFFFFF32,  0x16FFFFFF, 0x0F000003,    0x05000000, 0x1F000000, 0x00000000, 0x00000000, 0x003CFF06, 0x00640064,
    0x00640000,  0x08000000, GeoCmd_AdjustNodeZOffset, 0x00000000, 0x05000000, 0x00000000, D_8C200920, 0x06000000, 0x0A000000,
    &gGraphRoot0, 0x06000000, 0x06000000,    0x06000000, 0x06000000, 0x01000000,
};

s32 GeoCmd_AdjustNodeZOffset(s32 arg0, Fragment2_1GraphNode* arg1) {
    if (arg0 == 2) {
        arg1->unk_01E.z -= 0x80;
        arg1->unk_024.x = gPikachuNodes->unk_024.x;
        arg1->unk_024.y = gPikachuNodes->unk_024.y + 70.0f;
    }
    return 0;
}

s32 Pokemon_IsStandard(PokemonData* arg0) {
    s32 i;
    s32 var_v1 = 1;

    for (i = 0; i < 4; i++) {
        if (arg0->unk_09[i] == 0) {
            break;
        }

        if (arg0->unk_09[i] >= 0xA6) {
            var_v1 = 0;
        }
    }

    return var_v1;
}

s32 Pokemon_MatchesSelectionCriteria(PokemonData* arg0, s16 arg1, s16 arg2, s16 arg3) {
    s32 sp1C = 0;

    if ((arg0->unk_00.unk_00 > 0) && (arg0->unk_00.unk_00 < 0x98)) {
        if ((Pokemon_IsStandard(arg0) != 0) && (gSpeciesDisplayTable[arg0->unk_00.unk_00 - 1].unk_0C & arg3)) {
            if ((arg0->unk_24 >= arg1) && (arg2 >= arg0->unk_24)) {
                sp1C = 1;
            }
        }
    }
    return sp1C;
}

s32 CountMatchingPokemonInBlock(s16 arg0, s16 arg1, s16 arg2) {
    UNUSED s32 pad[22];
    s32 sp34;
    s16 var_s3;
    unk_func_80022C28_ret* var_v0;
    PokemonData* ptr = &gPikachuSession.unk_04;

    sp34 = 0;
    var_s3 = 0;

    if (arg1 == 0) {
        var_v0 = CreateGbsBlock(0x20, arg0, 0, 0);
    } else {
        var_v0 = CreateGbsBlock(0x21, arg0, arg1 - 1, 0);
    }

    if (var_v0 != NULL) {
        while (GbsBlock_ReadPokemon(&ptr->unk_00.unk_00, 1, var_v0) == 1) {
            if (Pokemon_MatchesSelectionCriteria(ptr, 1, 0x64, 0x20) != 0) {
                if (!arg2--) {
                    if (ptr->unk_00.unk_00 == 0x19) {
                        sp34 = 1;
                    }
                    break;
                }
            }
            var_s3++;
        }
        CommitAndFreeGbsBlock(var_v0);
    }

    if (sp34 != 0) {
        return var_s3;
    }
    return -1;
}

s32 SnapSelect_FindPokemon(void) {
    s32 i;
    unk_D_800AE540_0004* var_v1;

    var_v1 = gBattleContext.unk_1194[0].unk_08[0];

    for (i = 0; i < var_v1->unk_002; i++) {
        if (var_v1->unk_01C[i].unk_00.unk_00 == 0x19) {
            gPikachuSession.unk_00 = (var_v1->unk_01C[i].unk_52 & 0x70) >> 4;
            gPikachuSession.unk_01 = var_v1->unk_01C[i].unk_52 & 0xF;
            if ((gPikachuSession.unk_00 < 4) && (gPikachuSession.unk_01 < 0xD)) {
                if (SnapSelect_SetCameraMode(gPikachuSession.unk_00) != 0) {
                    gPikachuSession.unk_02 = CountMatchingPokemonInBlock(gPikachuSession.unk_00, gPikachuSession.unk_01, var_v1->unk_01C[i].unk_53);
                    if (gPikachuSession.unk_02 >= 0) {
                        return 1;
                    }
                }
            }
            return 0;
        }
    }

    return 0;
}

s32 GetPokemonCount(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        if (gPikachuSession.unk_04.unk_09[i] == 0) {
            break;
        }
    }
    return i;
}

void UpdatePikachuAnimation(void) {
    static s32 D_83202004 = 0;

    if ((gPikachuNodes[0].unk_040.unk_00 != 0xA) && (gPikachuNodes[0].unk_040.unk_00 != 5)) {
        D_83202004++;
        if (D_83202004 == 0x3C) {
            D_83202004 = 0;
            GraphNode_TriggerSound(&gPikachuNodes[0], -1);
            GraphNode_TriggerSound(&gPikachuNodes[0], 0xA);
        }
    }

    if ((gPikachuNodes[0].unk_040.unk_00 != 0) && (Anim_HasReachedEnd(&gPikachuNodes[0]) != 0)) {
        if (gPikachuActive != 0) {
            gPikachuNodes[0].unk_000.unk_01 &= ~1;
        } else {
            GraphNode_TriggerAction(&gPikachuNodes[0], 0);
        }
    }
}

void UpdatePikachuVisibility(void) {
    if (gPikachuVisibilityState == -1) {
        gPikachuNodes[1].unk_000.unk_01 &= ~1;
        gPikachuNodes[2].unk_000.unk_01 &= ~1;
        gPikachuNodes[3].unk_000.unk_01 &= ~1;
        return;
    }

    switch (gPikachuVisibilityState) {
        case 0x0:
            gPikachuNodes[1].unk_000.unk_01 |= 1;
            break;

        case 0x8:
            gPikachuNodes[2].unk_000.unk_01 |= 1;
            break;

        case 0x10:
            gPikachuNodes[3].unk_000.unk_01 |= 1;
            break;

        case 0x46:
            gPikachuNodes[1].unk_000.unk_01 &= ~1;
            break;

        case 0x4E:
            gPikachuNodes[2].unk_000.unk_01 &= ~1;
            break;

        case 0x56:
            gPikachuNodes[3].unk_000.unk_01 &= ~1;
            break;
    }

    if (gPikachuVisibilityState < 0x57) {
        gPikachuVisibilityState++;
    }
}

s32 RenderScene(u8 arg0) {
    Gfx_FinishFrame();
    UpdatePikachuAnimation();
    UpdatePikachuVisibility();
    Stage_BeginDisplayList();
    Gfx_FillScreen(&gDisplayListHead, 1);
    Graph_SetTextureState(gCameraGraphNode);
    return 0;
}

void Text_PrintFadingChar(s16 arg0, s16 arg1) {
    s32 var_a3;

    if (gTextFadeState.unk_00 < 0x10) {
        var_a3 = gTextFadeState.unk_00 * 0x10;
    } else if (gTextFadeState.unk_00 < 0x23) {
        var_a3 = 0xFF;
    } else if (gTextFadeState.unk_00 < 0x32) {
        var_a3 = (-gTextFadeState.unk_00 * 0x10) + 0x320;
    } else {
        var_a3 = 0;
    }

    gTextFadeState.unk_00++;
    if (gTextFadeState.unk_00 >= 0x3D) {
        gTextFadeState.unk_00 = 0;
    }

    Text_SetEnvColor(0xFF, 0xFF, 0xFF, var_a3);
    Text_PutChar(arg0, arg1, 0x23);
}

void UI_DrawGradientPanel(s16 arg0, s16 arg1, s16 arg2, s16 arg3) {
    Color_RGB8 sp24 = { 0x00, 0x00, 0x32 };
    Color_RGB8 sp20 = { 0x00, 0x00, 0xC8 };

    DrawGradientPanel(arg0, arg1, arg2, arg3, &sp24, &sp20);
}

void DrawCursorSprite(s16 arg0, s16 arg1) {
    gSPDisplayList(gDisplayListHead++, gTransferPakErrorBorderDL);

    Gfx_DrawSpriteRGBA16(arg0, arg1, 0x18, 0xE, Util_ConvertAddrToVirtAddr(D_8C200090), 0x18, 0x200000);

    gSPDisplayList(gDisplayListHead++, gPrefDL_End);
}

void UI_DisplayMessageRepeated(char* arg0, s32 arg1) {
    while (arg1-- > 0) {
        Game_UpdateInputs();
        RenderScene(0);
        UI_DrawGradientPanel(0x1E, 0x20, 0x104, 0x30);
        Text_ResetState();
        Text_SetFont(2, 0);
        Text_SetLineHeight(0x10);
        Text_Print(0x2E, 0x28, arg0);
        Text_SetupDL();
        Stage_Advance();
    }

    gCurrentUIMessage = arg0;
}

void UI_DisplayMessageWaitA(char* arg0, s32 arg1) {
    gTextFadeState.unk_00 = 0x10;

    do {
        Game_UpdateInputs();
        RenderScene(0);
        UI_DrawGradientPanel(0x1E, 0x20, 0x104, 0x30);
        Text_ResetState();
        Text_SetFont(2, 0);
        Text_SetLineHeight(0x10);
        Text_Print(0x2E, 0x28, arg0);
        Text_SetFont(4, 0);
        if (arg1 != 0) {
            Text_PrintFadingChar(0x104, 0x38);
        }
        Text_SetupDL();
        Stage_Advance();
    } while (!BTN_IS_PRESSED(gPlayer1Controller, BTN_A));

    PlaySoundEffect(1);
    gCurrentUIMessage = arg0;
}

void UI_SlideTextTransition(s8* arg0) {
    s32 i;
    s32 x1 = 0x1E;
    s32 x2 = 0x122;
    s32 y1 = 0x28;
    s32 y2 = 0x48;

    for (i = 1; i < 9; i++) {
        Game_UpdateInputs();
        RenderScene(0);
        UI_DrawGradientPanel(0x1E, 0x20, 0x104, 0x30);

        gDPSetScissor(gDisplayListHead++, G_SC_NON_INTERLACE, x1, y1, x2, y2);

        Text_ResetState();
        Text_SetFont(2, 0);
        Text_SetLineHeight(0x10);
        Text_Print(0x2E, y1 - i * 4, gCurrentUIMessage);
        Text_Print(0x2E, y2 - i * 4, arg0);
        Text_SetupDL();
        Stage_Advance();
    }

    gCurrentUIMessage = arg0;
}

s32 UI_PromptYesNo(char* arg0) {
    s32 temp_s3;
    s32 var_a2;
    s32 var_s1;
    s32 var_s2;

    var_s2 = 1;
    var_s1 = 0;

    while (var_s2 != 0) {
        Game_UpdateInputs();
        if (BTN_IS_PRESSED(gPlayer1Controller, BTN_DUP | BTN_DDOWN)) {
            PlaySoundEffect(1);
            var_s1 ^= 1;
        } else if (BTN_IS_PRESSED(gPlayer1Controller, BTN_A)) {
            var_s2 = 0;
        } else if (BTN_IS_PRESSED(gPlayer1Controller, BTN_B)) {
            var_s1 = 1;
            var_s2 = 0;
        }

        temp_s3 = var_s1 == 0;
        RenderScene(0);
        UI_DrawGradientPanel(0x1E, 0x20, 0x104, 0x30);
        UI_DrawGradientPanel(0xD2, 0x54, 0x50, 0x2C);
        DrawCursorSprite(0xDA, (var_s1 * 0x10) + 0x5C);
        Text_ResetState();
        Text_SetFont(2, 0);
        Text_SetLineHeight(0x10);
        Text_Print(0x2E, 0x28, arg0);

        if (temp_s3 != 0) {
            var_a2 = 0;
        } else {
            var_a2 = 0xFF;
        }

        Text_SetEnvColor(0xFF, 0xFF, var_a2, 0xFF);
        Text_Print(0xF2, 0x5C, GetMessageString(NULL, 0, gStadiumMessageBank, 0x10));

        if (var_s1 == 1) {
            var_a2 = 0;
        } else {
            var_a2 = 0xFF;
        }

        Text_SetEnvColor(0xFF, 0xFF, var_a2, 0xFF);
        Text_Print(0xF2, 0x6C, GetMessageString(NULL, 0, gStadiumMessageBank, 0x11));
        Text_SetupDL();
        Stage_Advance();
    }

    if (temp_s3 != 0) {
        PlaySoundEffect(2);
    } else {
        PlaySoundEffect(3);
    }
    return temp_s3;
}

s32 UI_PromptMoveSelection(char* arg0) {
    s32 var_a2;
    s32 var_s0;
    s32 var_s4;

    var_s4 = 1;
    var_s0 = 0;

    while (var_s4 != 0) {
        Game_UpdateInputs();

        if (BTN_IS_PRESSED(gPlayer1Controller, BTN_DUP)) {
            PlaySoundEffect(1);
            var_s0--;
            if (var_s0 < 0) {
                var_s0 = 3;
            }
        }

        if (BTN_IS_PRESSED(gPlayer1Controller, BTN_DDOWN)) {
            PlaySoundEffect(1);
            var_s0++;
            if (var_s0 >= 4) {
                var_s0 = 0;
            }
        } else if (BTN_IS_PRESSED(gPlayer1Controller, BTN_A)) {
            if ((gPikachuSession.unk_04.unk_09[var_s0] == 0xF) || (gPikachuSession.unk_04.unk_09[var_s0] == 0x13) ||
                (gPikachuSession.unk_04.unk_09[var_s0] == 0x46) || (gPikachuSession.unk_04.unk_09[var_s0] == 0x94)) {
                PlaySoundEffect(8);
            } else {
                var_s4 = 0;
                PlaySoundEffect(2);
            }
        } else if (BTN_IS_PRESSED(gPlayer1Controller, BTN_B)) {
            var_s4 = 0;
            var_s0 = -1;
            PlaySoundEffect(3);
        }

        RenderScene(0);
        UI_DrawGradientPanel(0x1E, 0x20, 0x82, 0x30);
        Text_ResetState();
        Text_SetFont(2, 0);
        Text_SetLineHeight(0x10);
        Text_Print(0x2E, 0x28, arg0);
        Text_SetupDL();
        UI_DrawGradientPanel(0x96, 0x20, 0x8C, 0x4C);
        DrawCursorSprite(0x9E, (var_s0 * 0x10) + 0x28);
        Text_ResetState();
        Text_SetFont(2, 0);
        Text_SetLineHeight(0x10);

        if (var_s0 == 0) {
            var_a2 = 0;
        } else {
            var_a2 = 0xFF;
        }

        Text_SetEnvColor(0xFF, 0xFF, var_a2, 0xFF);
        Text_Print(0xB6, 0x28, GetMessageString(NULL, 0, gMoveNameBank, gPikachuSession.unk_04.unk_09[0] - 1));

        if (var_s0 == 1) {
            var_a2 = 0;
        } else {
            var_a2 = 0xFF;
        }

        Text_SetEnvColor(0xFF, 0xFF, var_a2, 0xFF);
        Text_Print(0xB6, 0x38, GetMessageString(NULL, 0, gMoveNameBank, gPikachuSession.unk_04.unk_09[1] - 1));

        if (var_s0 == 2) {
            var_a2 = 0;
        } else {
            var_a2 = 0xFF;
        }

        Text_SetEnvColor(0xFF, 0xFF, var_a2, 0xFF);
        Text_Print(0xB6, 0x48, GetMessageString(NULL, 0, gMoveNameBank, gPikachuSession.unk_04.unk_09[2] - 1));

        if (var_s0 == 3) {
            var_a2 = 0;
        } else {
            var_a2 = 0xFF;
        }

        Text_SetEnvColor(0xFF, 0xFF, var_a2, 0xFF);
        Text_Print(0xB6, 0x58, GetMessageString(NULL, 0, gMoveNameBank, gPikachuSession.unk_04.unk_09[3] - 1));

        Text_SetupDL();
        Stage_Advance();
    }

    return var_s0;
}

void Event_PikachuExit(void) {
    UI_SlideTextTransition(GetMessageString(NULL, 0, gStadiumMessageBank, 4));
    gPikachuNodes->unk_01E.y = -0x800;
    GraphNode_TriggerAction(gPikachuNodes, 5);
    GraphNode_TriggerSound(gPikachuNodes, 0);
    gPikachuActive = 1;
    UI_DisplayMessageRepeated(GetMessageString(NULL, 0, gStadiumMessageBank, 4), 0x46);
    Stage_StartFade(0x1E);
    Music_StopTrack(0x3C);
    UI_DisplayMessageRepeated(GetMessageString(NULL, 0, gStadiumMessageBank, 4), 0x1E);
}

void Event_PikachuEnter(void) {
    GraphNode_TriggerAction(gPikachuNodes, 0xA);
    GraphNode_TriggerSound(gPikachuNodes, 7);
    PlayMoveSoundEffect(0, 0x39, 0x19, 0);
    gPikachuActive = 1;
    Music_ChangeTrack(0x4A);
    UI_SlideTextTransition(GetMessageString(NULL, 0, gStadiumMessageBank, 0xF));
    UI_DisplayMessageRepeated(GetMessageString(NULL, 0, gStadiumMessageBank, 0xF), 0x98);
    Stage_StartFade(0x1E);
    UI_DisplayMessageRepeated(GetMessageString(NULL, 0, gStadiumMessageBank, 0xF), 0x1E);
}

void Camera_PanDown(void) {
    s32 i;
    CameraStruct* temp_s1 = gCameraGraphNode->unk_0C;

    gPikachuNodes->unk_01E.y = 0x1000;

    for (i = 0; i < 120; i++) {
        Game_UpdateInputs();
        temp_s1->unk_60.at.y = 0x320 - ((i * 0x1E0) / 120);
        temp_s1->unk_60.eye.y = 0x320 - ((i * 0x1E0) / 120);
        gPikachuNodes->unk_01E.y += 0x200;
        RenderScene(0);
        Stage_Advance();
    }
}

s32 UI_StartDialogue(void) {
    s16 var_s0 = 0x14;
    s16 var_s1 = 0x10;
    s32 i;

    GraphNode_TriggerAction(gPikachuNodes, 8);

    for (i = 0; i < 8; i++) {
        Game_UpdateInputs();
        RenderScene(0);
        UI_DrawGradientPanel(0xA0 - (var_s0 / 2), 0x38 - (var_s1 / 2), var_s0, var_s1);
        Stage_Advance();
        var_s0 += 0x1E;
        var_s1 += 4;
    }

    UI_DisplayMessageWaitA(GetMessageString(NULL, 0, gStadiumMessageBank, 0), 1);
    UI_SlideTextTransition(GetMessageString(NULL, 0, gStadiumMessageBank, 1));
    UI_DisplayMessageWaitA(GetMessageString(NULL, 0, gStadiumMessageBank, 1), 1);

    while (true) {
        UI_SlideTextTransition(GetMessageString(NULL, 0, gStadiumMessageBank, 2));
        if (UI_PromptYesNo(GetMessageString(NULL, 0, gStadiumMessageBank, 2)) != 0) {
            return 1;
        }

        UI_SlideTextTransition(GetMessageString(NULL, 0, gStadiumMessageBank, 3));
        if (UI_PromptYesNo(GetMessageString(NULL, 0, gStadiumMessageBank, 3)) != 0) {
            Event_PikachuExit();
            return 0;
        }
    }
}

s32 UI_SelectMoveAndExecute(void) {
    s32 spAC;
    char sp2C[0x80];
    s32 temp_v0;

    temp_v0 = GetPokemonCount();
    if (temp_v0 == 4) {
        while (true) {
            UI_SlideTextTransition(GetMessageString(NULL, 0, gStadiumMessageBank, 5));
            UI_DisplayMessageWaitA(GetMessageString(NULL, 0, gStadiumMessageBank, 5), 1);
            UI_SlideTextTransition(GetMessageString(NULL, 0, gStadiumMessageBank, 6));
            UI_DisplayMessageWaitA(GetMessageString(NULL, 0, gStadiumMessageBank, 6), 1);
            UI_SlideTextTransition(GetMessageString(NULL, 0, gStadiumMessageBank, 7));

            if (UI_PromptYesNo(GetMessageString(NULL, 0, gStadiumMessageBank, 7)) != 0) {
                UI_SlideTextTransition(GetMessageString(NULL, 0, gStadiumMessageBank, 9));

                spAC = UI_PromptMoveSelection(GetMessageString(NULL, 0, gStadiumMessageBank, 9));
                if (spAC >= 0) {
                    UI_DisplayMessageRepeated(GetMessageString(NULL, 0, gStadiumMessageBank, 0xA), 0x1E);
                    GraphNode_TriggerAction(gPikachuNodes, 9);
                    gPikachuVisibilityState = 0;
                    Effect_TriggerMoveVisual(0x85, 0x19, 0);
                    UI_DisplayMessageWaitA(GetMessageString(NULL, 0, gStadiumMessageBank, 0xB), 1);
                    MessageBank_SetPointer_0x14_0x2A(0x1D, GetMessageString(NULL, 0, gMoveNameBank, gPikachuSession.unk_04.unk_09[spAC] - 1));
                    GetMessageString(sp2C, sizeof(sp2C), gStadiumMessageBank, 0xC);
                    Music_StopTrack(0x3C);
                    UI_SlideTextTransition(sp2C);
                    UI_DisplayMessageWaitA(sp2C, 1);
                    UI_SlideTextTransition(GetMessageString(NULL, 0, gStadiumMessageBank, 0xD));
                    UI_DisplayMessageWaitA(GetMessageString(NULL, 0, gStadiumMessageBank, 0xD), 1);
                    gPikachuVisibilityState = -1;
                    return spAC;
                }
            }

            UI_SlideTextTransition(GetMessageString(NULL, 0, gStadiumMessageBank, 8));

            if (UI_PromptYesNo(GetMessageString(NULL, 0, gStadiumMessageBank, 8)) != 0) {
                Event_PikachuExit();
                return -1;
            }
        }
    }

    Music_StopTrack(0x3C);
    return temp_v0;
}

void UI_DrawSaveStatus(s32 arg0) {
    RenderScene(0);
    UI_DrawGradientPanel(0x1E, 0x20, 0x104, 0x30);

    if (arg0 == 0) {
        UI_DrawGradientPanel(0x4C, 0x64, 0xA8, 0x28);
    } else {
        UI_DrawGradientPanel(0x30, 0x54, 0xE0, 0x78);
    }

    Text_ResetState();
    Text_SetFont(2, 0);
    Text_SetLineHeight(0x10);
    Text_Print(0x2E, 0x28, GetMessageString(NULL, 0, gStadiumMessageBank, 0xE));

    if (arg0 == 0) {
        Text_ResetState();
        Text_SetFont(4, 0);
        Text_Print(0x5C, 0x70, GetMessageString(NULL, 0, gStadiumMessageBank, 0x12));
        Text_SetupDL();
    } else {
        Text_SetLineHeight(0x10);
        Text_Print(0x40, 0x84, GetMessageString(NULL, 0, gStadiumMessageBank, 0x13));
        Text_SetEnvColor(0xFF, 0xFF, 0x64, 0xFF);

        if (arg0 == 2) {
            Text_SetFont(4, 0);
            Text_Print(0x4C, 0x64, GetMessageString(NULL, 0, gStadiumMessageBank, 0x14));
        } else if (arg0 == 3) {
            Text_SetLineHeight(0x10);
            Text_Print(0x40, 0x5C, GetMessageString(NULL, 0, gStadiumMessageBank, 0x15));
        }
    }

    Text_SetupDL();
    Stage_Advance();
}

void Save_WritePokemonData(void) {
    s32 var_s0;
    s32 temp_v0;
    unk_func_80022C28_ret* var_v0;

    if (gPikachuSession.unk_01 == 0) {
        var_v0 = CreateGbsBlock(0x20, gPikachuSession.unk_00, 0, 2);
    } else {
        var_v0 = CreateGbsBlock(0x21, gPikachuSession.unk_00, gPikachuSession.unk_01 - 1, 2);
    }

    GbsBlock_SetLimit(var_v0, gPikachuSession.unk_02);
    GbsBlock_WriteEntries(&gPikachuSession.unk_04, 1, var_v0);
    CommitAndFreeGbsBlock(var_v0);
    UI_DrawSaveStatus(0);
    UI_DrawSaveStatus(0);
    PlayerSave_VerifyPresence(gPikachuSession.unk_00);

    while (PlayerSave_FullSave(gPikachuSession.unk_00) == 0) {
        var_s0 = 2;
        do {
            temp_v0 = PlayerSave_UpdateState(gPikachuSession.unk_00);
            if (temp_v0 == 1) {
                var_s0 = 1;
            }

            if (temp_v0 == 3) {
                var_s0 = 3;
            }

            UI_DrawSaveStatus(var_s0);
        } while (temp_v0 != 2);

        UI_DrawSaveStatus(0);
        UI_DrawSaveStatus(0);
    }
    PlayerSave_PowerOff(gPikachuSession.unk_00);
}

void Event_GrantMove(s32 arg0) {
    s32 i;

    Audio_PlaySequence(0x19, 0);
    UI_SlideTextTransition(GetMessageString(NULL, 0, gStadiumMessageBank, 0xE));
    UI_DisplayMessageRepeated(GetMessageString(NULL, 0, gStadiumMessageBank, 0xE), 1);

    for (i = GetPokemonCount(); i < 4; i++) {
        gPikachuSession.unk_04.unk_09[i] = 0;
        gPikachuSession.unk_04.unk_20[i] = 0;
    }

    gPikachuSession.unk_04.unk_09[arg0] = 0x39;
    gPikachuSession.unk_04.unk_20[arg0] = gMoveBattleData[0x38].unk_05;

    Save_WritePokemonData();
    UI_DisplayMessageWaitA(GetMessageString(NULL, 0, gStadiumMessageBank, 0xE), 1);
    Event_PikachuEnter();
}

void Event_PikachuSequence(void) {
    s32 temp_v0;

    Music_ChangeTrack(0x49);
    Stage_AdvanceN(2);
    Stage_StartFade(0x28);
    Stage_AdvanceUntil(0xA, RenderScene);
    Camera_PanDown();
    if (UI_StartDialogue() != 0) {
        temp_v0 = UI_SelectMoveAndExecute();
        if (temp_v0 >= 0) {
            Event_GrantMove(temp_v0);
        }
    }
    Stage_AdvanceN(2);
}

void Pikachu_InitNode(Fragment2_1GraphNode* arg0, s16 arg1, s16 arg2, s16 arg3) {
    GraphNode_InitChild(arg0, 0, 0, gPikachuGeoNode);
    Anim_SetChannel(arg0, 0, D_8C2011C4, 0x10000);
    arg0->unk_000.unk_01 &= ~1;
    Vec3f_Set(&arg0->unk_030, 1.5f, 1.5f, 1.5f);
    arg0->unk_024.x = arg1;
    arg0->unk_024.y = arg2;
    arg0->unk_01E.z = arg3;
}

void Pikachu_SetupScene(void) {
    MemoryBlock* temp_v0;
    s32 i;

    temp_v0 = state_pool_try_init(main_pool_get_available(), 0);
    gCameraGraphNode = process_geo_layout(temp_v0, gPikachuGeoLayout);
    gPikachuGeoNode = process_geo_layout(temp_v0, D_8C201070);

    mem_pool_resize_block(temp_v0);
    Graph_InitRoots();

    for (i = 0; i < 4; i++) {
        Graph_AddToRootList0(&gPikachuNodes[i]);
    }

    GraphNode_InitChild(&gPikachuNodes[0], 0, 0, gPikachuModelData->unk_08->unk_00[0]);
    Vec3f_Set(&gPikachuNodes[0].unk_030, 16.0f, 16.0f, 16.0f);
    GraphNode_TriggerAction(&gPikachuNodes[0], 0);
    gPikachuNodes->unk_000.unk_02 &= ~0x40;
    Pikachu_InitNode(&gPikachuNodes[1], -0x50, 0x17C, 0x1800);
    Pikachu_InitNode(&gPikachuNodes[2], 0, 0x17C, 0);
    Pikachu_InitNode(&gPikachuNodes[3], 0x50, 0x17C, -0x1800);
}

s32 Fragment66_Main(UNUSED s32 arg0, UNUSED s32 arg1) {
    UNUSED s32 pad;
    Stage* sp20;

    main_pool_push_state('PIKA');

    if (SnapSelect_FindPokemon() != 0) {
        Gfx_InitBuffers(0x10000, 0);
        sp20 = Stage_Create(0, 1, 3, 1, 2, 1);
        Text_Init(6, 0);

        FRAGMENT_LOAD(fragment31);
        Fragment_Load(FRAGMENT_ID(_798CD0), _798CD0_ROM_START, _798CD0_ROM_END);
        ASSET_LOAD(D_1000000, common_menu1_ui, 0);

        MessageBank_Init();
        gMoveNameBank = GetMessageBank(0x25);
        gStadiumMessageBank = GetMessageBank(0x1C);
        AssetManager_LoadArchives();
        gPikachuModelData = func_80019D90(&gPikachuSession.unk_04);
        Pikachu_SetupScene();
        Stage_Set(sp20);
        Event_PikachuSequence();
        Stage_Destroy();
        FontManager_Free();
        Gfx_FreeBuffers();
    }

    main_pool_pop_state('PIKA');
    return 0;
}
