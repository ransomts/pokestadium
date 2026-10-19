#include "fragment11.h"
#include "src/12D80.h"
#include "src/17300.h"
#include "src/18140.h"
#include "src/geo_layout.h"
#include "src/1C720.h"
#include "src/1CF30.h"
#include "src/20470.h"
#include "src/2E110.h"
#include "src/3FB0.h"
#include "src/49790.h"
#include "src/4BDC0.h"
#include "src/4CBC0.h"
#include "src/50860.h"
#include "src/6A40.h"
#include "src/6BC0.h"
#include "src/F420.h"
#include "src/fragments/2/fragment2.h"
#include "src/fragments/5/fragment5.h"
#include "src/stage_loader.h"
#include "src/controller.h"

static Fragment2_1GraphNode D_865092E0;
static Fragment2_1GraphNode D_86509448;
static Fragment2_1GraphNode D_865095B0;
static Fragment2_1GraphNode D_86509718;
static Fragment2_1GraphNode D_86509880;
static Fragment2_1GraphNode D_865099E8;
static Fragment2_1GraphNode D_86509B50;
static Fragment2_1GraphNode D_86509CB8;
static Fragment2_1GraphNode D_86509E20;
static Fragment2_1GraphNode D_86509F88;
static Fragment2_1GraphNode D_8650A0F0;
static Fragment2_1GraphNode D_8650A258;
static Fragment2_1GraphNode D_8650A3C0;

static unk_D_864027C0 gHealthBarPositions[] = {
    { -60.0f, 7.5f, 0.0f, 1.0f, 1.0f, 1.0f, 0, 0xA00, 0 },
    { -20.0f, 7.5f, 0.0f, 1.0f, 1.0f, 1.0f, 0, 0x300, 0 },
    { 20.0f, 7.5f, 0.0f, 1.0f, 1.0f, 1.0f, 0, -0x300, 0 },
    { 60.0f, 7.5f, 0.0f, 1.0f, 1.0f, 1.0f, 0, -0xA00, 0 },
};

static Fragment2_1GraphNode* gHealthBarGraphNodePtrs[] = {
    &D_865092E0, &D_86509448, &D_865095B0, &D_86509718, &D_86509880, &D_865099E8, &D_86509B50,
    &D_86509CB8, &D_86509E20, &D_86509F88, &D_8650A0F0, &D_8650A258, &D_8650A3C0,
};

static u8 gHealthBarUpdateCounter = 0;
static u16 gResultTimer = 0;

static AnimFrame gResultScreenUIElements1[] = {
    { 0x0303F980, 2 }, { 0x0303FD80, 2 }, { 0x03040180, 2 },    { 0x0303FD80, 2 }, { 0x0303F980, 2 },
    { 0x0303FD80, 2 }, { 0x03040180, 2 }, { 0x0303FD80, 2 },    { 0x0303F980, 2 }, { 0x0303FD80, 2 },
    { 0x03040180, 2 }, { 0x0303FD80, 2 }, { 0x0303F980, 0x18 }, { NULL, 0 },
};

static AnimFrame gResultScreenUIElements2[] = {
    { 0x0303ED80, 0x18 }, { 0x0303F180, 2 }, { 0x0303F580, 2 }, { 0x0303F180, 2 }, { 0x0303ED80, 2 },
    { 0x0303F180, 2 },    { 0x0303F580, 2 }, { 0x0303F180, 2 }, { 0x0303ED80, 2 }, { 0x0303F180, 2 },
    { 0x0303F580, 2 },    { 0x0303F180, 2 }, { 0x0303ED80, 2 }, { NULL, 0 },
};

static AnimFrame gResultScreenUIElements3[] = {
    { 0x03040580, 0x12 }, { 0x03040980, 2 }, { 0x03040D80, 8 }, { 0x03040980, 2 }, { NULL, 0 },
};

static u32 gResultScreenGeoLayoutData[] = {
    0x0C00FFFF, 0x05000000, 0x0B00001E, 0x00000000, 0x014000F0, 0x0000000F, 0x00000000, 0x00000000, 0x05000000,
    0x0D000000, 0x05000000, 0x14000000, 0x002B0012, 0xFFFFFF32, 0x16FFFFFF, 0x0F000003, 0x05000000, 0x1F00FFFF,
    0x00000000, 0x00000000, 0x00000000, 0x00640064, 0x00640000, 0x06000000, 0x05000000, 0x0A000000, 0x800AC840,
    0x06000000, 0x06000000, 0x06000000, 0x03000000, 0x87806398, 0x06000000, 0x01000000,
};

static u8 gHealthBarAnimFlagA = 0;
static u8 gHealthBarAnimFlagB = 0;

unk_D_8650A528 gHealthBarData[4];
unk_D_8650A528* gCurrentHealthBar;
static Fragment2_1GraphNode* gCurrentHealthBarNode;
unk_D_8650AB30 D_8650AB30[4];
unk_D_8650AB30* gHealthBarEffectData;

void HealthBar_CalcNextDelay(unk_D_8650A528* arg0, u8 arg1) {
    if (arg0->unk_000 == 4) {
        arg0->unk_00D = 0;
        return;
    }

    if (arg1 == 0) {
        arg0->unk_00D = HealthBar_ValueToPixel(3);
    } else if ((gHealthBarTimer + 1) == gHealthBarDuration) {
        arg0->unk_00D = HealthBar_GetAnimStateIndex(arg0->unk_000, 1);
    } else {
        arg0->unk_00D = HealthBar_GetAnimStateIndex(arg0->unk_000, 0);
    }
}

void HealthBar_InitState(void) {
    s8 i;

    for (i = 0; i < 4; i++) {
        if (gMiniHudColorDefaults[i] == 0) {
            gHealthBarData[i].unk_000 = 4;
        } else {
            gHealthBarData[i].unk_000 = gMenuState;
        }
    }
}

void HealthBar_SetDirection(void) {
    u8 i;

    for (i = 0; i < 4; i++) {
        switch (gMenuOptionFlags[i]) {
            case 1:
                gHealthBarData[i].unk_004 = 1;
                break;

            case 2:
                gHealthBarData[i].unk_004 = 0;
                break;

            default:
                if (HealthBar_ValueToPixel(2) != 0) {
                    gHealthBarData[i].unk_004 = 0;
                } else {
                    gHealthBarData[i].unk_004 = 1;
                }
                break;
        }
    }
}

void HealthBar_Update(void) {
    u8 i;
    s8 temp_ft2;
    u8 var_s1;
    s32 sp58;
    UNUSED s32 pad;
    u32 var_s0_2;

    if (gResultMenuVisible != 1) {
        for (i = 0; i < 4; i++) {
            gCurrentHealthBar = &gHealthBarData[i];
            sp58 = gCurrentHealthBar->unk_008;

            var_s1 = 0;
            if (D_87B000C8 != 0) {
                if (gResultTimer < 0x57) {
                    var_s1 = 2;
                } else if (gResultTimer == 0x57) {
                    var_s1 = 1;
                    if (gCurrentHealthBar->unk_00C == 1) {
                        gCurrentHealthBar->unk_008 = 3;
                    } else {
                        gCurrentHealthBar->unk_008 = 4;
                    }
                } else if (gResultTimer == 0xB4) {
                    var_s1 = 1;
                    if (gCurrentHealthBar->unk_00C == 1) {
                        gCurrentHealthBar->unk_008 = 6;
                    } else {
                        gCurrentHealthBar->unk_008 = 5;
                    }
                } else if (Anim_HasReachedEnd(&gCurrentHealthBar->unk_014) != 0) {
                    switch (gCurrentHealthBar->unk_008) {
                        case 6:
                            var_s1 = 1;
                            if (gCurrentHealthBar->unk_004 == 0) {
                                gHealthBarAnimFlagA = 1;
                            } else if (gCurrentHealthBar->unk_004 == 1) {
                                gHealthBarAnimFlagB = 1;
                            }
                            break;

                        case 4:
                            var_s1 = 1;
                            gCurrentHealthBar->unk_008 = 5;
                            break;

                        case 0:
                        case 3:
                            var_s1 = 1;
                            gCurrentHealthBar->unk_008 = 0;
                            break;
                    }
                } else if ((gCurrentHealthBar->unk_008 == 6) &&
                           (((gHealthBarAnimFlagA != 0) && ((gCurrentHealthBar->unk_014.unk_040.unk_08 >> 0x10) == 0x37)) ||
                            ((gHealthBarAnimFlagB != 0) && ((gCurrentHealthBar->unk_014.unk_040.unk_08 >> 0x10) == 0x5E)))) {
                    var_s1 = 1;
                }
            } else if ((gHealthBarUpdateCounter == 0) && (gCurrentHealthBar->unk_00E >= 3) &&
                       ((gCurrentHealthBar->unk_008 == 0) || (gCurrentHealthBar->unk_008 == 3))) {
                gCurrentHealthBar->unk_008 = 1;
                var_s1 = 1;
                if ((gResultFlag_Special == 0) && (gResultMenuVisible == 0)) {
                    PlaySoundByCategory(0x80001, i, 0);
                }
            } else if ((gHealthBarUpdateCounter == 0) && (gCurrentHealthBar->unk_00E < 3) && (gCurrentHealthBar->unk_008 == 2)) {
                gCurrentHealthBar->unk_008 = 3;
                var_s1 = 1;
                if ((gResultFlag_Special == 0) && (gResultMenuVisible == 0)) {
                    PlaySoundByCategory(0x80001, i, 5);
                }
            } else {
                if ((gResultFlag_Special == 0) && (gResultMenuVisible == 0)) {
                    temp_ft2 = ROUND_MAX((gCurrentHealthBar->unk_010 * 100.0f) / gCurrentHealthBar->unk_012);

                    if (temp_ft2 >= 0x4B) {
                        var_s0_2 = 4;
                    } else if (temp_ft2 >= 0x32) {
                        var_s0_2 = 3;
                    } else if (temp_ft2 >= 0x19) {
                        var_s0_2 = 2;
                    } else {
                        var_s0_2 = 1;
                    }

                    PlaySoundByCategory(0x80001, i, var_s0_2);
                    PlaySoundByCategory(0x80002, i, var_s0_2);
                }

                if (Anim_HasReachedEnd(&gCurrentHealthBar->unk_014) != 0) {
                    switch (gCurrentHealthBar->unk_008) {
                        case 0:
                        case 3:
                            var_s1 = 1;
                            gCurrentHealthBar->unk_008 = 0;
                            break;

                        case 1:
                        case 2:
                            var_s1 = 1;
                            gCurrentHealthBar->unk_008 = 2;
                            break;
                    }
                }
            }

            if (!!var_s1) {
                if (gCurrentHealthBar->unk_008 != sp58) {
                    GraphNode_TriggerAction(&gCurrentHealthBar->unk_014, gCurrentHealthBar->unk_008);
                    if (gCurrentHealthBar->unk_008 != 0) {
                        GraphNode_TriggerSound(&gCurrentHealthBar->unk_014, gCurrentHealthBar->unk_008);
                    }
                } else if (gCurrentHealthBar->unk_008 == 6) {
                    if (gCurrentHealthBar->unk_004 == 0) {
                        Anim_SetChannelBase(&gCurrentHealthBar->unk_014, 0x1B);
                        SetAnimStateIndex(&gCurrentHealthBar->unk_014, 0x1B);
                    } else if (gCurrentHealthBar->unk_004 == 1) {
                        Anim_SetChannelBase(&gCurrentHealthBar->unk_014, 0x4B);
                        SetAnimStateIndex(&gCurrentHealthBar->unk_014, 0x4B);
                    }
                } else if (var_s1 == 2) {
                    Anim_SetChannelBase(&gCurrentHealthBar->unk_014, gCurrentHealthBar->unk_014.unk_040.unk_08 >> 0x10);
                    if (gCurrentHealthBar->unk_008 != 0) {
                        SetAnimStateIndex(&gCurrentHealthBar->unk_014, gCurrentHealthBar->unk_014.unk_040.unk_08 >> 0x10);
                    }
                } else {
                    Anim_SetChannelBase(&gCurrentHealthBar->unk_014, 0);
                    if (gCurrentHealthBar->unk_008 != 0) {
                        SetAnimStateIndex(&gCurrentHealthBar->unk_014, 0);
                    }
                }
            }
        }
    }
}

void HealthBar_ResetAnimations(void) {
    u8 i;
    u32 var_a0;

    for (i = 0; i < 13; i++) {
        var_a0 = 0;

        switch (i) {
            case 0:
                var_a0 = 1;
                break;

            case 1:
            case 2:
            case 3:
            case 4:
                if (gHealthBarData[i - 1].unk_00C != 1) {
                    var_a0 = 1;
                    if (gHealthBarData[i - 1].unk_004 == 0) {
                        gHealthBarGraphNodePtrs[i]->unk_024 = gHealthBarData[i - 1].unk_014.unk_0EC;
                    } else if (gHealthBarData[i - 1].unk_004 == 1) {
                        gHealthBarGraphNodePtrs[i]->unk_024 = gHealthBarData[i - 1].unk_014.unk_0DC;
                    }
                }
                break;

            case 5:
            case 6:
            case 7:
            case 8:
                if (gHealthBarData[i - 5].unk_00C == 1) {
                    var_a0 = 1;
                }
                break;

            case 9:
            case 10:
            case 11:
            case 12:
                if (gHealthBarData[i - 9].unk_00C != 1) {
                    var_a0 = 1;
                }
                break;
        }

        if (var_a0 != 0) {
            Anim_SetChannelBase(gHealthBarGraphNodePtrs[i], 0);
            GraphNode_TriggerSound(gHealthBarGraphNodePtrs[i], 0);
            SetAnimStateIndex(gHealthBarGraphNodePtrs[i], 0);
        }
    }
}

void HealthBar_DetermineWinner(void) {
    u8 i;
    s16 var_s4 = 0;

    for (i = 0; i < 4; i++) {
        gCurrentHealthBar = &gHealthBarData[i];

        if ((gCurrentHealthBar->unk_010 >= gCurrentHealthBar->unk_012) && (var_s4 < gCurrentHealthBar->unk_010)) {
            var_s4 = gCurrentHealthBar->unk_010;
        }
    }

    for (i = 0; i < 4; i++) {
        gCurrentHealthBar = &gHealthBarData[i];

        if ((gCurrentHealthBar->unk_010 >= gCurrentHealthBar->unk_012) && (var_s4 == gCurrentHealthBar->unk_010)) {
            gCurrentHealthBar->unk_00C = 1;
            IncrementPlayerScore(i);

            D_87B000D4++;

            if ((gResultFlag_Special == 0) && (gResultMenuVisible == 0)) {
                PlaySoundByCategory(0x80003, i, 0);
            }
        }
    }

    for (i = 0; i < 4; i++) {
        gCurrentHealthBar = &gHealthBarData[i];

        if (gCurrentHealthBar->unk_010 >= gCurrentHealthBar->unk_012) {
            if (gCurrentHealthBar->unk_00C == 1) {
                gCurrentHealthBar->unk_010 = gCurrentHealthBar->unk_012 + 1;
            } else {
                gCurrentHealthBar->unk_010 = gCurrentHealthBar->unk_012;
            }
        }
    }
}

void HealthBar_FrameUpdate(UNUSED s32 arg0) {
    Fragment2_1_Update();
    HealthBar_BuildDisplayList();
}

void HealthBar_HandleInput(void) {
    u8 i;

    if ((gResultFlag_Special != 0) || (gResultMenuVisible != 0) || (D_87B000C8 != 0)) {
        return;
    }

    for (i = 0; i < 4; i++) {
        gCurrentHealthBar = &gHealthBarData[i];

        if (gCurrentHealthBar->unk_000 == 4) {
            if ((gHealthBarPaletteIndex == 1) || (gHealthBarPaletteIndex == 3) || ((gHealthBarPaletteIndex == 0) && (gHealthBarMode == 1))) {
                if (gControllers[i].buttonPressed & 0x8000) {
                    gCurrentHealthBar->unk_00D += 1;
                }

                if (gControllers[i].buttonPressed & 0x4000) {
                    gCurrentHealthBar->unk_00D -= 2;
                }
            } else if ((gHealthBarPaletteIndex == 2) || (gHealthBarPaletteIndex == 4) || ((gHealthBarPaletteIndex == 0) && (gHealthBarMode == 2))) {
                if (gControllers[i].buttonPressed & 0x8000) {
                    gCurrentHealthBar->unk_00D -= 2;
                }

                if (gControllers[i].buttonPressed & 0x4000) {
                    gCurrentHealthBar->unk_00D += 1;
                }
            }
        }
    }

    gHealthBarTimer++;
    if (gHealthBarTimer == 2) {
        switch (gHealthBarPaletteIndex) {
            case 3:
                gHealthBarPaletteIndex = 1;
                break;

            case 4:
                gHealthBarPaletteIndex = 2;
                break;
        }
    } else if ((gHealthBarTimer + 4) == gHealthBarDuration) {
        gHealthBarMode = gHealthBarPaletteIndex;

        switch (gHealthBarPaletteIndex) {
            case 1:
                gHealthBarPaletteIndex = 3;
                break;

            case 2:
                gHealthBarPaletteIndex = 4;
                break;
        }
    } else {
        if ((gHealthBarTimer + 2) == gHealthBarDuration) {
            gHealthBarPaletteIndex = 0;
        } else if (gHealthBarTimer >= gHealthBarDuration) {
            HealthBar_Init();
        }
    }
}

void ResultScreen_Draw(s32 arg0) {
    u8 i;

    if ((arg0 == 0) || ((arg0 == 3) && (D_87B000D0 == 1))) {
        DrawPanel(0x18, 0x16, 0x110, 0x90, 0x15);
        DrawPanel(0x18, 0xA5, 0x110, 0x36, 0x14B);

        gSPDisplayList(gDisplayListHead++, gPrefDL_Border);

        DrawDualTexturePanel(2, 0x19, 0xA6);
        DrawAnimatedSprite2(0x62, 0xB0, gResultScreenUIElements1);
        DrawAnimatedSprite(0x74, 0xB0, gResultScreenUIElements2);
        DrawAnimatedSprite3(0x74, 0xC6, gResultScreenUIElements3);

        gSPDisplayList(gDisplayListHead++, gPrefDL_End);
    } else if ((arg0 == 1) || (arg0 == 2) || ((arg0 == 3) && (D_87B000D0 == 0))) {
        s16 sp5C[] = {
            0x002B,
            0x0071,
            0x00B7,
            0x00FD,
        };

        gSPDisplayList(gDisplayListHead++, gPrefDL_Border);
        gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255);

        for (i = 0; i < 4; i++) {
            if (gHealthBarData[i].unk_000 == 4) {
                DrawUniformScaledTextureRect(i, sp5C[i], 0xC6, 0.75f);
            } else {
                DrawUniformScaledTextureRect(-1 - i, sp5C[i], 0xC6, 0.75f);
            }
        }

        gSPDisplayList(gDisplayListHead++, gPrefDL_End);
    }

    if ((arg0 == 1) || (arg0 == 2) || ((arg0 == 3) && (D_87B000D0 == 0))) {
        for (i = 0; i < 4; i++) {
            gCurrentHealthBar = &gHealthBarData[i];

            DrawBorderRect((i * 0x47) + 0x1C, 0xDB, 0x32, gCurrentHealthBar->unk_010, gCurrentHealthBar->unk_012 + 1);
        }
    }

    Text_ResetState();
    Text_BeginRender();

    if ((arg0 == 0) || ((arg0 == 3) && (D_87B000D0 == 1))) {
        s32 temp_s0;
        s32 sp48;
        s32 sp44;
        char* sp40 = GetMessageString(NULL, 0, gItemNamesBank, 0x2D);

        Text_SetFont(2, 0);
        Text_SetLineHeight(0xC);
        Text_SetEnvColor(0xFF, 0xFF, 0xFF, 0xFF);
        Text_SetPrimColor(0xF9, 0xF4, 0, 0xFF);
        Text_Print(0xA0 - (GetTextWidth(gCurrentTextObject, GetMessageString(NULL, 0, gItemNamesBank, 0x2C)) / 2), 0x20,
                      GetMessageString(NULL, 0, gItemNamesBank, 0x2C));
        Text_SetEnvColor(0xFF, 0xFF, 0xFF, 0xFF);
        Text_SetPrimColor(0xFF, 0xFF, 0xFF, 0xFF);
        Text_Print(0x28, 0x34, sp40);

        temp_s0 = (CountTextLines(sp40) * 0xC) + 0xC;
        Text_Print(0x28, temp_s0 + 0x34, GetMessageString(NULL, 0, gItemNamesBank, 0x2E));

        temp_s0 += (CountTextLines(GetMessageString(NULL, 0, gItemNamesBank, 0x2E)) * 0xC) + 0xC;
        Text_Print(0x28, temp_s0 + 0x34, GetMessageString(NULL, 0, gItemNamesBank, 0x2F));

        Text_Print(0x8B, 0xB2, GetMessageString(NULL, 0, gItemNamesBank, 0x5C));
        Text_Print(0x8B, 0xC8, GetMessageString(NULL, 0, gItemNamesBank, 0x5C));
        Text_SetEnvColor(0xC8, 0xC8, 0xFF, 0xFF);
        Text_SetPrimColor(0x50, 0x50, 0xFF, 0xFF);
        ParseStringAndMeasure(&sp48, &sp44, sp40, GetMessageString(NULL, 0, gItemNamesBank, 0x5F), 0xC);
        Text_Print(sp48 + 0x28, sp44 + 0x34, GetMessageString(NULL, 0, gItemNamesBank, 0x5F));
        Text_SetEnvColor(0xC8, 0xFA, 0xD2, 0xFF);
        Text_SetPrimColor(0x32, 0xE6, 0x82, 0xFF);
        ParseStringAndMeasure(&sp48, &sp44, sp40, GetMessageString(NULL, 0, gItemNamesBank, 0x60), 0xC);
        Text_Print(sp48 + 0x28, sp44 + 0x34, GetMessageString(NULL, 0, gItemNamesBank, 0x60));
        Text_SetEnvColor(0xC8, 0xC8, 0xFF, 0xFF);
        Text_SetPrimColor(0x50, 0x50, 0xFF, 0xFF);
        Text_Print(0xA2, 0xB2, GetMessageString(NULL, 0, gItemNamesBank, 0x30));
        Text_SetEnvColor(0xFF, 0xFF, 0xFF, 0xFF);
        Text_SetPrimColor(0xFF, 0x80, 0x80, 0xFF);
        Text_Print(0xA2, 0xC8, GetMessageString(NULL, 0, gItemNamesBank, 0x14));
    }

    Text_EndRender();
    Text_SetupDL();
}

void ResultScreen_RenderFrame(s32 arg0) {
    u8 i;

    Stage_BeginDisplayList();
    Gfx_FillScreen(&gDisplayListHead, 0xA6BF);

    if (gResultMenuVisible == 0) {
        Gfx_FinishFrame();
    }

    Graph_SetTextureState(D_87B000E8);

    if (gResultConfirmPressed == 0) {
        ResultScreen_Draw(arg0);
    }

    ResultScreen_UpdateAndRender();
    Stage_Advance();

    if (gResultMenuVisible == 0) {
        D_87B000C0++;

        if (arg0 == 2) {
            if (D_87B000C8 == 0) {
                gHealthBarUpdateCounter++;
                if (gHealthBarUpdateCounter >= 0xF) {
                    gHealthBarUpdateCounter = 0;

                    for (i = 0; i < 4; i++) {
                        gCurrentHealthBar = &gHealthBarData[i];

                        gCurrentHealthBar->unk_010 += gCurrentHealthBar->unk_00D;
                        if (gCurrentHealthBar->unk_010 < 0) {
                            gCurrentHealthBar->unk_010 = 0;
                        } else if (gCurrentHealthBar->unk_010 >= gCurrentHealthBar->unk_012) {
                            D_87B000C8 = 1;
                        }
                        gCurrentHealthBar->unk_00E = gCurrentHealthBar->unk_00D;
                        HealthBar_CalcNextDelay(gCurrentHealthBar, 1);
                    }

                    if (D_87B000C8 != 0) {
                        HealthBar_DetermineWinner();
                        HealthBar_ResetAnimations();
                    }
                }
            } else if (gResultTimer < 0xC4) {
                gResultTimer++;

                switch (gResultTimer) {
                    case 0x5B:
                    case 0x6F:
                    case 0x83:
                        if ((D_87B000D4 != 4) && (gResultFlag_Special == 0)) {
                            PlaySoundByCategory(0x80004, 0, 0);
                            PlaySoundByCategory(0x80005, 0, 0);
                        }
                        break;

                    case 0x96:
                        if ((D_87B000D4 != 4) && (gResultFlag_Special == 0)) {
                            PlaySoundByCategory(0x80006, 0, 0);
                        }
                        break;

                    case 0xC3:
                        SetResultFlag(1);
                        break;
                }
            }
        }
    }
}

void ResultScreen_MainLoop(void) {
    u8 i;
    u8 var_s1;
    s32 var_s2;

    var_s1 = 0;
    var_s2 = 1;

    Stage_AdvanceN(5);
    Stage_FadeIn(0x10);

    while (var_s2 != 0) {
        if (var_s1 >= 0x11) {
            if (gPlayer1Controller->buttonPressed & 0x1000) {
                var_s2 = 0;
            } else if ((gMenuCursorX == 0) && (gPlayer1Controller->buttonPressed & 0x4000)) {
                PlaySoundEffect(3);
                SetResultFlag(2);
                D_87B000D0 = 1;
                return;
            }
        }

        MenuInput_FrameUpdate();
        HealthBar_FrameUpdate(0);
        HealthBar_Update();
        ResultScreen_RenderFrame(0);

        if (var_s1 < 0x11) {
            var_s1++;
        }
    }

    Stage_SetFadeColor(0x3C);

    if (gResultFlag_Special == 0) {
        while (true) {
            if (D_87B000C4 <= 0) {
                break;
            }

            for (i = 3; i > 0; i--) {
                s32 tmp = (i * 0x3C) / 2;
                if (tmp == D_87B000C4) {
                    if (i == 3) {
                        Fragment2_1_SetStartFlag(1);
                    }
                    PlaySoundByCategory(0x80007, 0, 0);
                }
            }

            D_87B000C4--;

            MenuInput_FrameUpdate();
            HealthBar_FrameUpdate(1);
            HealthBar_Update();
            ResultScreen_RenderFrame(1);
        }
    }
}

void HealthBar_MainLoop(void) {
    static u8 D_86502E7C = 0;

    s32 var_s0 = 1;

    if (gResultFlag_Special == 0) {
        HealthBar_Init();
        PlaySoundByCategory(0x80008, 0, 0);
        MenuInput_FrameUpdate();
        HealthBar_FrameUpdate(2);
        HealthBar_Update();
        ResultScreen_RenderFrame(2);

        while (var_s0 != 0) {
            if (gResultFlag_Special != 0) {
                break;
            }

            if ((D_86502E7C == 0) && (Fragment2_1_GetResult() == -2)) {
                ResultScreen_SetAnimation(0x1D);
                D_86502E7C = 1;
            }

            MenuInput_FrameUpdate();
            HealthBar_FrameUpdate(2);

            if (D_87B000C8 == 0) {
                HealthBar_HandleInput();
            } else if (gResultExitPending != 0) {
                var_s0 = 0;
            }

            RenderHealthBar(2);
            HealthBar_Update();
            ResultScreen_RenderFrame(2);
        }
    }
}

void ResultScreen_FadeAndLoop(void) {
    u8 i;

    Audio_SetVolumeFadeAndDuration(1, 0x1E);
    Audio_SetVolumeFadeAndDuration(2, 0x1E);
    Stage_FadeOut(0x1E);

    for (i = 0; i < 30; i++) {
        MenuInput_FrameUpdate();
        HealthBar_FrameUpdate(3);
        RenderHealthBar(3);
        HealthBar_Update();
        ResultScreen_RenderFrame(3);
    }
}

void Camera_SetupResultScreen(void) {
    D_87B000EC = D_87B000E8->unk_00.unk_0C;

    D_87B000F0 = -0x200;
    D_87B000F2 = 0;
    D_87B000F4 = 0xBE;

    D_87B000EC->unk_24.near = 50.0f;
    D_87B000EC->unk_24.far = 6400.0f;
    D_87B000EC->unk_24.fovy = 40.0f;

    D_87B000EC->unk_60.at.y = 51.0f;

    Camera_SetViewParameters(&D_87B000EC->unk_60.at, &D_87B000EC->unk_60.eye, D_87B000F4, D_87B000F0, D_87B000F2);
}

void DynamoGame_LoadAssets(void) {
    u8 j;
    u8 i;
    MemoryBlock* temp_v0;

    temp_v0 = state_pool_try_init(main_pool_get_available(), 0);
    D_87B000E8 = process_geo_layout(temp_v0, gResultScreenGeoLayoutData);
    mem_pool_resize_block(temp_v0);
    Graph_InitRoots();
    AssetManager_LoadArchives();
    HealthBar_InitState();
    HealthBar_SetDirection();

    for (i = 0; i < 2; i++) {
        if (i == 0) {
            D_87B000E4 = GeoLayout_LoadById(0xC5);
        } else {
            D_87B000E4 = GeoLayout_LoadById(0xC6);
        }

        for (j = 0; j < 4; j++) {
            if (i == gHealthBarData[j].unk_004) {
                gCurrentHealthBar = &gHealthBarData[j];
                gCurrentHealthBarNode = &gCurrentHealthBar->unk_014;

                Graph_AddToRootList0(gCurrentHealthBarNode);

                if (i == 0) {
                    GraphNode_InitChild(gCurrentHealthBarNode, 0, 0xC5, D_87B000E4->unk_08->unk_00[0]);
                } else {
                    GraphNode_InitChild(gCurrentHealthBarNode, 0, 0xC6, D_87B000E4->unk_08->unk_00[0]);
                }

                gCurrentHealthBar->unk_008 = 0;
                GraphNode_TriggerAction(gCurrentHealthBarNode, gCurrentHealthBar->unk_008);
                Anim_SetChannelBase(gCurrentHealthBarNode, HealthBar_ValueToPixel(gCurrentHealthBarNode->unk_040.unk_04->unk_0A));

                gCurrentHealthBarNode->unk_024.x = gHealthBarPositions[j].unk_00;
                gCurrentHealthBarNode->unk_024.y = gHealthBarPositions[j].unk_04;

                if (i == 0) {
                    gCurrentHealthBarNode->unk_024.y += 0.15f;
                }

                gCurrentHealthBarNode->unk_024.z = gHealthBarPositions[j].unk_08;

                gCurrentHealthBarNode->unk_030.x = gHealthBarPositions[j].unk_0C;
                gCurrentHealthBarNode->unk_030.y = gHealthBarPositions[j].unk_10;
                gCurrentHealthBarNode->unk_030.z = gHealthBarPositions[j].unk_14;

                gCurrentHealthBarNode->unk_01E.x = gHealthBarPositions[j].unk_18;
                gCurrentHealthBarNode->unk_01E.y = gHealthBarPositions[j].unk_1A;
                gCurrentHealthBarNode->unk_01E.z = gHealthBarPositions[j].unk_1C;

                gCurrentHealthBar->unk_00C = 0;
                gCurrentHealthBar->unk_00E = 0;

                HealthBar_CalcNextDelay(gCurrentHealthBar, 0);

                gCurrentHealthBar->unk_010 = 0;
                gCurrentHealthBar->unk_012 = 0x28;
            }
        }
    }

    {
        u16 sp5C[] = {
            0x00C9, 0x00C8, 0x00C8, 0x00C8, 0x00C8, 0x00CA, 0x00CB, 0x00CC, 0x00CD, 0x00CE, 0x00CF, 0x00D0, 0x00D1,
        };

        for (j = 0; j < 13; j++) {
            if ((j != 2) && (j != 3) && (j != 4)) {
                D_87B000E4 = GeoLayout_LoadById(sp5C[j]);
            }

            gCurrentHealthBarNode = gHealthBarGraphNodePtrs[j];

            Graph_AddToRootList0(gCurrentHealthBarNode);
            GraphNode_InitChild(gCurrentHealthBarNode, 0, sp5C[j], D_87B000E4->unk_08->unk_00[0]);
            GraphNode_TriggerAction(gCurrentHealthBarNode, 0);
            Anim_SetChannelBase(gCurrentHealthBarNode, gCurrentHealthBarNode->unk_040.unk_04->unk_0A);
        }
    }

    HealthBar_CreateNode();
    InitHealthBar();
    Camera_SetupResultScreen();
    Fragment2_1_Init();
    ResultScreen_Init();
    DrawAnimatedSprite(0, 0, NULL);
    DrawAnimatedSprite2(0, 0, NULL);
}

void DynamoGame_Main(UNUSED s32 arg0, UNUSED s32 arg1) {
    Stage* sp24;

    main_pool_push_state('MINI');

    Gfx_InitBuffers(0x18000, 0);
    sp24 = Stage_Create(0, 1, 3, 1, 2, 1);
    gCurrentTextObject = Text_Init(0x16, 0);

    ASSET_LOAD(D_1000000, common_menu1_ui, 0);
    FRAGMENT_LOAD(fragment31);

    DynamoGame_LoadAssets();
    Stage_Set(sp24);
    ResultScreen_MainLoop();
    HealthBar_MainLoop();
    ResultScreen_FadeAndLoop();
    Stage_Destroy();
    FontManager_Free();
    Gfx_FreeBuffers();

    main_pool_pop_state('MINI');

    GetCurrentOptionCount();
}

static s32 pad_D_86502E98 = 0;

s8 HealthBar_GetAnimStateIndex(s32 arg0, s32 arg1) {
    static u16 sHealthBarAnimStateTableNormal[4][8] = {
        { 0x0001, 0x0001, 0x0001, 0x0032, 0x0032, 0x0005, 0x0000, 0x0000 },
        { 0x0000, 0x0001, 0x0001, 0x0005, 0x0032, 0x0032, 0x0001, 0x0000 },
        { 0x0000, 0x0000, 0x0001, 0x0001, 0x0005, 0x005A, 0x001E, 0x0005 },
        { 0x0000, 0x0000, 0x0000, 0x0000, 0x0005, 0x001E, 0x005A, 0x000A },
    };

    static u16 sHealthBarAnimStateTableExtended[4][13] = {
        { 0x0003, 0x0006, 0x0014, 0x0014, 0x0014, 0x0014, 0x000A, 0x0005, 0x0003, 0x0001, 0x0000, 0x0000, 0x0000 },
        { 0x0003, 0x0006, 0x0014, 0x0014, 0x0014, 0x0014, 0x000A, 0x000A, 0x0005, 0x0003, 0x0001, 0x0000, 0x0000 },
        { 0x0003, 0x0006, 0x0014, 0x0014, 0x0014, 0x0014, 0x000A, 0x000A, 0x000A, 0x0007, 0x0005, 0x0003, 0x0001 },
        { 0x0000, 0x0003, 0x0006, 0x000A, 0x0014, 0x0014, 0x0014, 0x0014, 0x000A, 0x000A, 0x0007, 0x0005, 0x0003 },
    };

    u8 i;
    u16 var_a0;
    u16 var_a2;
    u16* sp24;
    s8 sp23;
    u8 sp22;
    u16 temp_v0;

    if (arg1 == 0) {
        sp24 = sHealthBarAnimStateTableNormal[arg0];
        sp23 = -1;
        sp22 = 8;
    } else if (arg1 == 1) {
        sp24 = sHealthBarAnimStateTableExtended[arg0];
        sp23 = -8;
        sp22 = 0xD;
    }

    var_a0 = 0;

    for (i = 0; i < sp22; i++) {
        var_a0 += sp24[i];
    }

    temp_v0 = HealthBar_ValueToPixel(var_a0);

    var_a2 = 0;
    for (i = 0; i < sp22; i++) {
        if ((temp_v0 >= var_a2) && (temp_v0 < (sp24[i] + var_a2))) {
            return i + sp23;
        }
        var_a2 += sp24[i];
    }

    return 0;
}
