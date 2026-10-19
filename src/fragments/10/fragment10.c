#include "fragment10.h"
#include "src/12D80.h"
#include "src/17300.h"
#include "src/18140.h"
#include "src/geo_layout.h"
#include "src/19840.h"
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
#include "src/memory.h"
#include "src/stage_loader.h"
#include "src/controller.h"

static unk_D_864027C0 gPlayerSpawnInfo[] = {
    { -68.0f, 0.0f, 68.0f, 1.0f, 1.0f, 1.0f, 0, 0x5E80, 0 },
    { -68.0f, 0.0f, -68.0f, 1.0f, 1.0f, 1.0f, 0, 0x1F80, 0 },
    { 68.0f, 0.0f, -68.0f, 1.0f, 1.0f, 1.0f, 0, -0x2380, 0 },
    { 68.0f, 0.0f, 68.0f, 1.0f, 1.0f, 1.0f, 0, 0x9D80, 0 },
};

static u16 D_86402840 = 0;
static u16 gPlayerButtonPressed = 0;

u8 gUseAlphaBlend = 0;

static u8 gHealthBarSegmentTable[][8] = {
    { 0x12, 0x13, 0x14, 0x15, 0x3A, 0x3B, 0x3C, 0x3D }, { 0x10, 0x11, 0x12, 0x13, 0x34, 0x35, 0x36, 0x37 },
    { 0x0E, 0x0F, 0x10, 0x11, 0x2E, 0x2F, 0x30, 0x31 }, { 0x0D, 0x0E, 0x0F, 0x10, 0x2B, 0x2C, 0x2D, 0x2E },
    { 0x0C, 0x0D, 0x0E, 0x0F, 0x28, 0x29, 0x2A, 0x2B }, { 0x0B, 0x0C, 0x0D, 0x0E, 0x25, 0x26, 0x27, 0x28 },
    { 0x0A, 0x0B, 0x0C, 0x0D, 0x22, 0x23, 0x24, 0x25 }, { 0x09, 0x0A, 0x0B, 0x0C, 0x1F, 0x20, 0x21, 0x22 },
    { 0x08, 0x09, 0x0A, 0x0B, 0x1C, 0x1D, 0x1E, 0x1F }, { 0x07, 0x08, 0x09, 0x0A, 0x19, 0x1A, 0x1B, 0x1C },
    { 0x06, 0x07, 0x08, 0x09, 0x16, 0x17, 0x18, 0x19 }, { 0x05, 0x06, 0x07, 0x08, 0x13, 0x14, 0x15, 0x16 },
    { 0x04, 0x05, 0x06, 0x07, 0x10, 0x11, 0x12, 0x13 }, { 0x03, 0x04, 0x05, 0x06, 0x0D, 0x0E, 0x0F, 0x10 },
};

static AnimFrame gPrefLayoutTable1[] = {
    { 0x0303ED80, 14 }, { 0x0303F180, 2 }, { 0x0303F580, 6 }, { 0x0303F180, 2 }, { NULL, 0 },
};

static AnimFrame gPrefLayoutTable2[] = {
    { 0x03040580, 18 }, { 0x03040980, 2 }, { 0x03040D80, 8 }, { 0x03040980, 2 }, { NULL, 0 },
};

static u32 gGeoLayoutData[] = {
    0x0C00FFFF, 0x05000000, 0x0B00001E, 0x00000000, 0x014000F0, 0x0000000F, 0x00000000, 0x00000000, 0x05000000,
    0x0D000000, 0x05000000, 0x14000000, 0x002B0012, 0xFFFFFF32, 0x16FFFFFF, 0x0F000003, 0x05000000, 0x1F00FFFF,
    0x00000000, 0x00000000, 0x00000000, 0x00640064, 0x00640000, 0x06000000, 0x05000000, 0x0A000000, 0x800AC840,
    0x06000000, 0x06000000, 0x06000000, 0x03000000, 0x87806398, 0x06000000, 0x01000000,
};

static Fragment2_1GraphNode gResultScreenNode;

static Fragment2_1GraphNode gPlayerResultNodes[4];

static HudState gPlayerHudStates[4];

static ResultGameState gGameState;

static HudState* gCurrentHudState;
static ResultGameState* D_864052CC;
static Fragment2_1GraphNode* gCurrentGraphNode;
static u8 gHealthSegmentExactMatch;
static s16 gCurrentHealthSegment;

void DrowzeeGame_UpdatePlayerTimingWindows(void) {
    u8 i;

    for (i = 0; i < 4; i++) {
        gCurrentHudState = &gPlayerHudStates[i];

        if (gCurrentHudState->unk_000 == 4) {
            continue;
        }

        gCurrentHudState->unk_008 =
            gHealthBarSegmentTable[D_864052CC->unk_000][2] + DrowzeeGame_ComputeAITimingBias(D_864052CC->unk_000, gCurrentHudState->unk_000);
        gCurrentHudState->unk_00A =
            gHealthBarSegmentTable[D_864052CC->unk_000][6] + DrowzeeGame_ComputeAITimingBias(D_864052CC->unk_000, gCurrentHudState->unk_000);
    }
}

u16 DrowzeeGame_IsWindowMatch(u8 arg0) {
    if ((gCurrentHealthSegment == gPlayerHudStates[arg0].unk_008) || (gCurrentHealthSegment == gPlayerHudStates[arg0].unk_00A)) {
        return 1;
    }
    return 0;
}

void DrowzeeGame_SetPlayerState(HudState* arg0, s32 arg1, u8 arg2, s32 arg3, u8 arg4) {
    arg0->unk_018 = arg1;
    arg0->unk_01C = arg2;
    arg0->unk_020 = arg3;
    arg0->unk_024 = arg4;
}

void DrowzeeGame_InitPlayerSlots(void) {
    s8 i;

    for (i = 0; i < 4; i++) {
        if (gMiniHudColorDefaults[i] == 0) {
            gPlayerHudStates[i].unk_000 = 4;
        } else {
            gPlayerHudStates[i].unk_000 = gMenuState;
        }
    }
}

void DrowzeeGame_LoopDrowzeeIdleAnim(void) {
    if (ModelAnim_IsFinished(&gResultScreenNode) != 0) {
        ModelAnim_SetFrame(&gResultScreenNode, 0);
    }
}

void DrowzeeGame_AdvanceBreathPhase(ResultGameState* arg0) {
    static u8 D_86402994 = 0;
    static u8 D_86402998[] = {
        0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x08, 0x08, 0x09,
        0x09, 0x09, 0x0A, 0x0A, 0x0A, 0x0B, 0x0B, 0x0B, 0x0C, 0x0C, 0x0C, 0x0D,
    };

    if (ModelAnim_IsFinished(&arg0->unk_004) != 0) {
        arg0->unk_001 = arg0->unk_000;

        if (arg0->unk_000 != 0xD) {
            D_86402994++;
            arg0->unk_000 = D_86402998[D_86402994];
        }

        if (arg0->unk_001 != arg0->unk_000) {
            ModelAnim_SetAnimation(&arg0->unk_004, arg0->unk_000);
        } else {
            ModelAnim_SetFrame(&arg0->unk_004, 0);
        }

        DrowzeeGame_UpdatePlayerTimingWindows();
    }
}

void DrowzeeGame_UpdatePlayerAnimations(void) {
    u8 i;
    f32 temp_fv0;
    f32 var_fv1;
    s8 temp_ft2;
    s32 temp_s1;

    if (gResultMenuVisible == 0) {
        for (i = 0; i < 4; i++) {
            gCurrentHudState = &gPlayerHudStates[i];

            if ((ModelAnim_IsFinished(&gCurrentHudState->unk_028) != 0) ||
                ((gCurrentHudState->unk_010 == 0) && (gCurrentHudState->unk_012 > 0)) ||
                ((D_87B000C8 != 0) && (gCurrentHudState->unk_00C == 1) && (D_86402840 == 0x3C) && (D_87B000D4 == 1))) {
                temp_s1 = gCurrentHudState->unk_004;

                if ((D_87B000C8 != 0) && (gCurrentHudState->unk_00C == 1) &&
                    ((D_86402840 == 0x3C) || (gCurrentHudState->unk_004 == 6))) {
                    gCurrentHudState->unk_004 = 6;
                } else {
                    temp_fv0 = (gCurrentHudState->unk_010 * 100.0f) / gCurrentHudState->unk_00E;
                    if (temp_fv0 > 0.0f) {
                        var_fv1 = 0.5f;
                    } else {
                        var_fv1 = -0.5f;
                    }
                    temp_ft2 = var_fv1 + temp_fv0;

                    if (temp_ft2 >= 0x51) {
                        gCurrentHudState->unk_004 = 0;
                    } else if (temp_ft2 >= 0x3D) {
                        gCurrentHudState->unk_004 = 1;
                    } else if (temp_ft2 >= 0x29) {
                        gCurrentHudState->unk_004 = 2;
                    } else if (temp_ft2 >= 0x15) {
                        gCurrentHudState->unk_004 = 3;
                    } else if (gCurrentHudState->unk_010 != 0) {
                        gCurrentHudState->unk_004 = 4;
                    } else {
                        gCurrentHudState->unk_004 = 5;
                    }
                }

                if (temp_s1 != gCurrentHudState->unk_004) {
                    ModelAnim_SetAnimation(&gCurrentHudState->unk_028, gCurrentHudState->unk_004);
                    if (gCurrentHudState->unk_004 != 0) {
                        ModelAnim_SetEventTrack(&gCurrentHudState->unk_028, gCurrentHudState->unk_004);
                    }
                } else if (gCurrentHudState->unk_004 == 5) {
                    ModelAnim_SetFrame(&gCurrentHudState->unk_028, 0x18);
                    ModelAnim_SetEventFrame(&gCurrentHudState->unk_028, 0x18);
                } else if (gCurrentHudState->unk_004 == 6) {
                    ModelAnim_SetFrame(&gCurrentHudState->unk_028, 0x77);
                    ModelAnim_SetEventFrame(&gCurrentHudState->unk_028, 0x77);
                } else {
                    ModelAnim_SetFrame(&gCurrentHudState->unk_028, 0);
                    if (gCurrentHudState->unk_004 != 0) {
                        ModelAnim_SetEventFrame(&gCurrentHudState->unk_028, 0);
                    }
                }
            }
        }
    }
}

void DrowzeeGame_ProcessElimination(u8 arg0) {
    u8 i;
    u8 sp40[] = {
        0,
        0,
        0,
        0,
    };
    static s8 D_864029B4 = 4;

    sp40[arg0] = 1;

    for (i = 0; i < 4; i++) {
        if (i != arg0) {
            gCurrentHudState = &gPlayerHudStates[i];

            if ((gCurrentHudState->unk_010 <= 0) && (gCurrentHudState->unk_012 > 0)) {
                D_864029B4--;
                sp40[i] = 1;
            }
        }
    }

    for (i = 0; i < 4; i++) {
        gCurrentHudState = &gPlayerHudStates[i];

        if (sp40[i] != 0) {
            gCurrentHudState->unk_00C = D_864029B4;
            DrowzeeGame_SetPlayerState(gCurrentHudState, 0, 0, 0, 0);
        }
    }

    D_864029B4--;
    if (D_864029B4 < 2) {
        D_864052CC->unk_004.unk_040.unk_0C = 0;
        D_87B000C8 = 1;

        Audio_FadeOutAll(0xA);

        for (i = 0; i < 4; i++) {
            gCurrentHudState = &gPlayerHudStates[i];

            if (gCurrentHudState->unk_00C == 0) {
                gCurrentHudState->unk_00C = 1;
                DrowzeeGame_SetPlayerState(gCurrentHudState, 0, 0, 0, 0);
            }
        }

        D_87B000D4 = 0;

        for (i = 0; i < 4; i++) {
            if (gPlayerHudStates[i].unk_00C == 1) {
                D_87B000D4++;
            }
        }

        if (D_87B000D4 == 1) {
            for (i = 0; i < 4; i++) {
                if (gPlayerHudStates[i].unk_00C == 1) {
                    Widget_PauseMenuRecordWin(i);
                    break;
                }
            }
        }
    }
}

void DrowzeeGame_DrawPlayerOverlay(UNUSED s32 arg0) {
    u8 i;
    f32 temp_fs0;
    s16 temp_a3;
    Gfx* temp_v0;

    temp_fs0 = 0.1f;

    for (i = 0; i < 4; i++) {
        gCurrentHudState = &gPlayerHudStates[i];

        temp_v0 = Gfx_AllocDisplayList(0x80);
        gCurrentHudState->unk_190->unk_18 = temp_v0;

        if ((gCurrentHudState->unk_010 == 0) || (gCurrentHudState->unk_00C == 1)) {
            temp_a3 = gCurrentHudState->unk_028.unk_040.unk_08 >> 0x10;

            gSPDisplayList(temp_v0++, gDamageOverlayDL);
            gDPSetTileSize(temp_v0++, G_TX_RENDERTILE, 0x0000, (0x40 - (D_87B000C0 % 64)) << 2, 0x007C,
                           ((0x80 - (D_87B000C0 % 64)) & 0x3F) << 2);
            gSPDisplayList(temp_v0++, gHealthBarDL);

            if ((gCurrentHudState->unk_004 == 5) && (temp_a3 >= 0x18)) {
                if (gCurrentHudState->unk_015 == 0) {
                    gCurrentHudState->unk_015 = 1;
                    if ((gResultFlag_Special == 0) && (gResultMenuVisible == 0)) {
                        Audio_DispatchSoundBankCommand(0x70005, i + 1, 0);
                    }
                }
                gCurrentHudState->unk_190->unk_28 = temp_fs0;
            } else if ((gCurrentHudState->unk_00C == 1) && (gCurrentHudState->unk_004 == 6) && (temp_a3 >= 0x77)) {
                if (gCurrentHudState->unk_015 == 0) {
                    gCurrentHudState->unk_015 = 1;
                    if ((gResultFlag_Special == 0) && (gResultMenuVisible == 0)) {
                        Audio_DispatchSoundBankCommand(0x70006, i + 1, 0);
                    }
                }
                gCurrentHudState->unk_190->unk_28 = temp_fs0;
            } else {
                gCurrentHudState->unk_190->unk_28 = 0.0f;
            }
        } else {
            gSPDisplayList(temp_v0++, gHealthBarQuadDL);

            if (gCurrentHudState->unk_018 == 2) {
                switch (gCurrentHudState->unk_01C) {
                    default:
                        gCurrentHudState->unk_190->unk_28 = 0.5f;
                        break;

                    case 20:
                        gCurrentHudState->unk_190->unk_28 = temp_fs0;
                        if ((gResultFlag_Special == 0) && (gResultMenuVisible == 0)) {
                            Audio_DispatchSoundBankCommand(0x70004, i + 1, 0);
                        }
                        break;

                    case 19:
                        gCurrentHudState->unk_190->unk_28 = 0.2f;
                        break;

                    case 18:
                        gCurrentHudState->unk_190->unk_28 = 0.3f;
                        break;
                }
            } else {
                gCurrentHudState->unk_190->unk_28 = 0.0f;
            }
        }

        gSPEndDisplayList(temp_v0++);

        gCurrentHudState->unk_190->unk_1C = gCurrentHudState->unk_028.unk_0A8[0].unk_04;
    }
}

void DrowzeeGame_UpdateRoundTick(s32 arg0) {
    s32 temp;
    s16 sp24[] = {
        0xFB1E,
        0xFED4,
        0x0120,
        0x04B0,
    };
    u8 i;

    Widget_CountdownUpdate();

    if (gResultMenuVisible == 0) {
        if (arg0 == 2) {
            static u8 D_864029C0 = 0;

            gCurrentHealthSegment = D_864052CC->unk_004.unk_040.unk_08 >> 0x10;
            gHealthSegmentExactMatch = 0;

            for (i = 0; i < 8; i++) {
                temp = gCurrentHealthSegment;
                if (temp == gHealthBarSegmentTable[D_864052CC->unk_000][i]) {
                    gHealthSegmentExactMatch = 1;
                    break;
                }
            }

            gUseAlphaBlend = 0;

            if (D_87B000C8 == 0) {
                for (i = 0; i < 8; i++) {
                    temp = gCurrentHealthSegment;
                    if ((temp + 1) == gHealthBarSegmentTable[D_864052CC->unk_000][i]) {
                        gUseAlphaBlend = 1;
                        break;
                    }
                }
            }

            for (i = 0; i < 4; i++) {
                gCurrentHudState = &gPlayerHudStates[i];

                gCurrentHudState->unk_012 = gCurrentHudState->unk_010;

                if ((D_87B000C8 != 0) && (gCurrentHudState->unk_00C == 1) && (D_86402840 >= 0x3C) && (D_87B000D4 == 1) &&
                    (D_864029C0 < 0x10)) {
                    gCurrentHudState->unk_028.unk_01E.y += sp24[i];
                }
            }

            if (D_87B000C8 != 0) {
                if (D_86402840 < 0x3C) {
                    D_86402840++;
                } else {
                    if (D_86402840 < 0x6A) {
                        if (D_86402840 == 0x69) {
                            D_87B000CC = 1;
                            Widget_PauseMenuTrigger(1);
                        }
                        D_86402840++;
                    }

                    if (D_864029C0 < 0x10) {
                        D_864029C0++;
                    }
                }
            }
        }

        if (D_87B000C8 != 0) {
            static f32 D_864029C4 = 1.0f;

            D_864029C4 -= 0.06f;
            if (D_864029C4 < 0.0f) {
                D_864029C4 = 0.0f;
            }

            gGameState.unk_004.unk_030.x = gGameState.unk_004.unk_030.y = gGameState.unk_004.unk_030.z = D_864029C4;
        }
    }
}

void DrowzeeGame_JudgePlayerTiming(void) {
    static u8 D_864029C8 = 0;

    u8 i;
    u8 j;
    s32 var_a2;
    UNUSED s32 pad;

    if ((gResultFlag_Special == 0) && (gResultMenuVisible == 0)) {
        D_864052CC->previousHealthState = D_864052CC->unk_16C;
        if (gCurrentHealthSegment < (D_864052CC->unk_004.unk_040.unk_04->unk_0A / 2)) {
            D_864052CC->unk_16C = 0;
        } else {
            D_864052CC->unk_16C = 1;
        }

        if (D_864052CC->unk_16C != D_864052CC->previousHealthState) {
            Audio_DispatchSoundBankCommand(0x70003, 1 - D_864052CC->unk_16C, 0);

            for (i = 0; i < 4; i++) {
                gCurrentHudState = &gPlayerHudStates[i];

                if ((gCurrentHudState->unk_274 == 0) && (gCurrentHudState->unk_010 > 0)) {
                    if (D_864052CC->previousHealthState != 0) {
                        gCurrentHudState->unk_194[D_864052CC->unk_001][7]++;
                    } else {
                        gCurrentHudState->unk_194[D_864052CC->unk_000][7]++;
                    }
                } else {
                    gCurrentHudState->unk_274 = 0;
                }
            }
        }

        for (i = 0; i < 4; i++) {
            gCurrentHudState = &gPlayerHudStates[i];

            if (gCurrentHudState->unk_012 != 0) {
                if (gCurrentHudState->unk_01C >= 2) {
                    gCurrentHudState->unk_01C--;
                } else {
                    DrowzeeGame_SetPlayerState(gCurrentHudState, gCurrentHudState->unk_020, gCurrentHudState->unk_024, 0, 0);
                }

                if (gCurrentHudState->unk_000 == 4) {
                    gPlayerButtonPressed = gControllers[i].buttonPressed & 0x8000;
                } else {
                    gPlayerButtonPressed = DrowzeeGame_IsWindowMatch(i);
                }

                if (gPlayerButtonPressed != 0) {
                    if (gHealthSegmentExactMatch != 0) {
                        if (gCurrentHudState->unk_014 == 0) {
                            if (D_864029C8 == 0) {
                                Audio_DispatchSoundBankCommand(0x70009, 0, 0);
                                D_864029C8 = 1;
                            }

                            gCurrentHudState->unk_014 = 1;
                            ModelAnim_SetFrame(&gPlayerResultNodes[i], 0);

                            for (j = 0; j < 4; j++) {
                                if (i != j) {
                                    gPlayerHudStates[j].unk_010 -= 2;
                                }
                            }

                            if (gCurrentHudState->unk_018 == 0) {
                                DrowzeeGame_SetPlayerState(gCurrentHudState, 1, 0x14, 0, 0);
                            } else {
                                DrowzeeGame_SetPlayerState(gCurrentHudState, 0, 1, 1, 0x14);
                            }
                        }
                    } else {
                        gCurrentHudState->unk_010 -= 1;
                        if (gCurrentHudState->unk_018 == 0) {
                            DrowzeeGame_SetPlayerState(gCurrentHudState, 2, 0x14, 0, 0);
                        } else {
                            DrowzeeGame_SetPlayerState(gCurrentHudState, 0, 1, 2, 0x14);
                        }
                    }

                    gCurrentHudState->unk_274 = 1;
                    if (D_864052CC->unk_16C == 0) {
                        var_a2 = 2;
                    } else {
                        var_a2 = 6;
                    }

                    if ((gHealthBarSegmentTable[D_864052CC->unk_000][var_a2] - 3) >= gCurrentHealthSegment) {
                        gCurrentHudState->unk_194[D_864052CC->unk_000][0]++;
                    } else if ((gCurrentHealthSegment + 2) == gHealthBarSegmentTable[D_864052CC->unk_000][var_a2]) {
                        gCurrentHudState->unk_194[D_864052CC->unk_000][1]++;
                    } else if ((gCurrentHealthSegment + 1) == gHealthBarSegmentTable[D_864052CC->unk_000][var_a2]) {
                        gCurrentHudState->unk_194[D_864052CC->unk_000][2]++;
                    } else if (gCurrentHealthSegment == gHealthBarSegmentTable[D_864052CC->unk_000][var_a2]) {
                        gCurrentHudState->unk_194[D_864052CC->unk_000][3]++;
                    } else if (gCurrentHealthSegment == (gHealthBarSegmentTable[D_864052CC->unk_000][var_a2] + 1)) {
                        gCurrentHudState->unk_194[D_864052CC->unk_000][4]++;
                    } else if (gCurrentHealthSegment == (gHealthBarSegmentTable[D_864052CC->unk_000][var_a2] + 2)) {
                        gCurrentHudState->unk_194[D_864052CC->unk_000][5]++;
                    } else if (gCurrentHealthSegment >= (gHealthBarSegmentTable[D_864052CC->unk_000][var_a2] + 3)) {
                        gCurrentHudState->unk_194[D_864052CC->unk_000][6]++;
                    }
                }

                if ((gCurrentHealthSegment == gHealthBarSegmentTable[D_864052CC->unk_000][3]) ||
                    (gCurrentHealthSegment == gHealthBarSegmentTable[D_864052CC->unk_000][7])) {
                    if (gCurrentHudState->unk_014 == 0) {
                        gCurrentHudState->unk_010--;
                        if (gCurrentHudState->unk_018 == 0) {
                            DrowzeeGame_SetPlayerState(gCurrentHudState, 2, 0x14, 0, 0);
                        } else {
                            DrowzeeGame_SetPlayerState(gCurrentHudState, 0, 1, 2, 0x14);
                        }
                    } else {
                        gCurrentHudState->unk_014 = 0;
                    }
                }
            }
        }

        if ((gCurrentHealthSegment == gHealthBarSegmentTable[D_864052CC->unk_000][3]) || (gCurrentHealthSegment == gHealthBarSegmentTable[D_864052CC->unk_000][7])) {
            D_864029C8 = 0;
        }

        for (i = 0; i < 4; i++) {
            gCurrentHudState = &gPlayerHudStates[i];

            if (gCurrentHudState->unk_010 <= 0) {
                gCurrentHudState->unk_010 = 0;
                if ((gCurrentHudState->unk_012 > 0) && (gCurrentHudState->unk_00C == 0)) {
                    DrowzeeGame_ProcessElimination(i);
                }
            }
        }
    }
}

void DrowzeeGame_DrawTutorialScreen(s32 arg0) {
    if ((arg0 == 0) || ((arg0 == 3) && (D_87B000D0 == 1))) {
        Ui_DrawBorderedPanel(0x18, 0x16, 0x110, 0x90, 0x15);
        Ui_DrawBorderedPanel(0x18, 0xA5, 0x110, 0x36, 0x14B);

        gSPDisplayList(gDisplayListHead++, gPrefDL_Border);

        Widget_DrawSplitBanner(2, 0x19, 0xA6);
        Widget_DrawAnimIcon16(0x74, 0xB0, gPrefLayoutTable1);
        Widget_DrawAnimIcon16C(0x74, 0xC6, gPrefLayoutTable2);

        gSPDisplayList(gDisplayListHead++, gPrefDL_End);

    } else if ((arg0 == 1) || (arg0 == 2) || ((arg0 == 3) && (D_87B000D0 == 0))) {
        u8 i;
        s16 sp74[] = {
            0x0025,
            0x003D,
            0x00E5,
            0x00FD,
        };
        s16 sp6C[] = {
            0x00BA,
            0x0034,
            0x0034,
            0x00BA,
        };

        gSPDisplayList(gDisplayListHead++, gPrefDL_Border);
        gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255);

        for (i = 0; i < 4; i++) {
            if (gPlayerHudStates[i].unk_000 == 4) {
                Widget_DrawPlayerIcon(i, sp74[i], sp6C[i], 0.75f);
            } else {
                Widget_DrawPlayerIcon(-1 - i, sp74[i], sp6C[i], 0.75f);
            }
        }

        gSPDisplayList(gDisplayListHead++, gPrefDL_End);
    }

    Font_BeginTranslucentTextRendering();
    Font_EnableTwoCycleTexturing();

    if ((arg0 == 0) || ((arg0 == 3) && (D_87B000D0 == 1))) {
        char* temp_s2 = Text_GetString(NULL, 0, gItemNamesBank, 0x29);
        s32 sp58;
        s32 sp54;
        s32 temp_s0;

        Font_SetActive(2, 0);
        Font_SetLineHeight(0xC);
        Text_SetEnvColor(0xFF, 0xFF, 0xFF, 0xFF);
        Text_SetPrimColor(0xF9, 0xF4, 0, 0xFF);
        Font_Printf(0xA0 - (Text_MeasureStringWidth(gCurrentTextObject, Text_GetString(NULL, 0, gItemNamesBank, 0x28)) / 2), 0x20,
                      Text_GetString(NULL, 0, gItemNamesBank, 0x28));
        Text_SetEnvColor(0xFF, 0xFF, 0xFF, 0xFF);
        Text_SetPrimColor(0xFF, 0xFF, 0xFF, 0xFF);
        Font_Printf(0x28, 0x34, temp_s2);

        temp_s0 = ((CountTextLines(temp_s2) * 0xC) + 0xC);
        Font_Printf(0x28, temp_s0 + 0x34, Text_GetString(NULL, 0, gItemNamesBank, 0x2A));
        Font_Printf(0x8B, 0xB2, Text_GetString(NULL, 0, gItemNamesBank, 0x5C));
        Font_Printf(0x8B, 0xC8, Text_GetString(NULL, 0, gItemNamesBank, 0x5C));
        Text_SetEnvColor(0xC8, 0xC8, 0xFF, 0xFF);
        Text_SetPrimColor(0x50, 0x50, 0xFF, 0xFF);
        Widget_MeasureLabelBox(&sp58, &sp54, temp_s2, Text_GetString(NULL, 0, gItemNamesBank, 0x5F), 0xC);
        Font_Printf(sp58 + 0x28, sp54 + 0x34, Text_GetString(NULL, 0, gItemNamesBank, 0x5F));
        Text_SetEnvColor(0xC8, 0xC8, 0xFF, 0xFF);
        Text_SetPrimColor(0x50, 0x50, 0xFF, 0xFF);
        Font_Printf(0xA2, 0xB2, Text_GetString(NULL, 0, gItemNamesBank, 0x2B));
        Text_SetEnvColor(0xFF, 0xFF, 0xFF, 0xFF);
        Text_SetPrimColor(0xFF, 0x80, 0x80, 0xFF);
        Font_Printf(0xA2, 0xC8, Text_GetString(NULL, 0, gItemNamesBank, 0x14));
    }

    Font_DisableTwoCycleTexturing();
    Font_EndTexturedTextRendering();
}

void DrowzeeGame_DrawFrame(s32 arg0) {
    BgStage_DrawFrame();
    GfxImage_FillCurrent(&gDisplayListHead, 0xA6BF);

    if (gResultMenuVisible == 0) {
        GeoRender_AdvanceFrameCounter();
    }

    Geo_RenderRootNode(D_87B000E8);

    if (gResultConfirmPressed == 0) {
        DrowzeeGame_DrawTutorialScreen(arg0);
    }

    Widget_PauseMenuUpdate();
    BgStage_AdvanceFrame();

    if (gResultMenuVisible == 0) {
        D_87B000C0++;
    }
}

void DrowzeeGame_WaitForStart(void) {
    u8 i;
    u8 var_s1;
    s32 var_s2;

    var_s1 = 0;
    var_s2 = 1;
    StageLoader_RunFrames(5);
    StageFade_StartFromOpaque(0x10);

    while (var_s2 != 0) {
        if (var_s1 >= 0x11) {
            if (gPlayer1Controller->buttonPressed & 0x1000) {
                var_s2 = 0;
            } else if ((gMenuCursorX == 0) && (gPlayer1Controller->buttonPressed & 0x4000)) {
                Audio_PlaySoundEffectById(3);
                Widget_PauseMenuTrigger(2);
                D_87B000D0 = 1;
                return;
            }
        }

        MenuInput_FrameUpdate();
        DrowzeeGame_UpdateRoundTick(0);
        DrowzeeGame_DrawPlayerOverlay(0);
        DrowzeeGame_UpdatePlayerAnimations();
        DrowzeeGame_LoopDrowzeeIdleAnim();
        DrowzeeGame_DrawFrame(0);

        if (var_s1 < 0x11) {
            var_s1++;
        }
    }

    Audio_FadeOutAll(0x3C);
    if (gResultFlag_Special == 0) {
        while (true) {
            if (D_87B000C4 <= 0) {
                break;
            }

            for (i = 3; i > 0; i--) {
                if (D_87B000C4 == ((i * 0x3C) / 2)) {
                    if (i == 3) {
                        Widget_CountdownStart(1);
                    }
                    Audio_DispatchSoundBankCommand(0x70001, 0, 0);
                }
            }

            D_87B000C4--;

            MenuInput_FrameUpdate();
            DrowzeeGame_UpdateRoundTick(1);
            DrowzeeGame_DrawPlayerOverlay(1);
            DrowzeeGame_UpdatePlayerAnimations();
            DrowzeeGame_LoopDrowzeeIdleAnim();
            DrowzeeGame_DrawFrame(1);
        }
    }
}

void DrowzeeGame_MainLoop(void) {
    static u8 D_864029DC = 0;
    static u8 D_864029E0 = 0;

    s32 var_s2 = 1;

    if (gResultFlag_Special == 0) {
        Audio_DispatchSoundBankCommand(0x70002, 0, 0);
        MenuInput_FrameUpdate();
        DrowzeeGame_UpdateRoundTick(2);
        DrowzeeGame_DrawPlayerOverlay(2);
        DrowzeeGame_UpdatePlayerAnimations();
        DrowzeeGame_LoopDrowzeeIdleAnim();
        DrowzeeGame_DrawFrame(2);

        while (var_s2 != 0) {
            if (gResultFlag_Special != 0) {
                break;
            }

            if ((D_864029DC == 0) && (Widget_CountdownGetState() == -2)) {
                Audio_StartMusicTrack(0x18);
                D_864029DC = 1;
            }

            MenuInput_FrameUpdate();
            DrowzeeGame_UpdateRoundTick(2);

            if (D_87B000C8 == 0) {
                if (D_864029E0 < 0x1E) {
                    if (gResultMenuVisible == 0) {
                        D_864029E0++;
                    }
                } else if (D_864029E0 == 0x1E) {
                    if (gResultMenuVisible == 0) {
                        Audio_DispatchSoundBankCommand(0x70003, 1, 0);
                        D_864029E0++;
                    }
                    ModelAnim_SetFrame(&D_864052CC->unk_004, 1);
                } else {
                    DrowzeeGame_JudgePlayerTiming();
                    DrowzeeGame_AdvanceBreathPhase(D_864052CC);
                }
            } else if (gResultExitPending != 0) {
                var_s2 = 0;
            }

            DrowzeeGame_DrawPlayerOverlay(2);
            DrowzeeGame_UpdatePlayerAnimations();
            DrowzeeGame_LoopDrowzeeIdleAnim();
            DrowzeeGame_DrawFrame(2);
        }
    }
}

void DrowzeeGame_ShowResultText(void) {
    u8 i;

    Audio_FadeCategories(1, 0x1E);
    Audio_FadeCategories(2, 0x1E);
    StageFade_StartFromTransparent(0x1E);

    for (i = 0; i < 30; i++) {
        MenuInput_FrameUpdate();
        DrowzeeGame_UpdateRoundTick(3);
        DrowzeeGame_DrawPlayerOverlay(3);
        DrowzeeGame_UpdatePlayerAnimations();
        DrowzeeGame_LoopDrowzeeIdleAnim();
        DrowzeeGame_DrawFrame(3);
    }
}

void DrowzeeGame_InitCamera(void) {
    D_87B000EC = D_87B000E8->unk_00.unk_0C;

    D_87B000F0 = 0x900;
    D_87B000F2 = 0;
    D_87B000F4 = 0x190;

    D_87B000EC->unk_24.near = 50.0f;
    D_87B000EC->unk_24.far = 6400.0f;
    D_87B000EC->unk_24.fovy = 27.5f;

    D_87B000EC->unk_60.at.y = 25.0f;

    Camera_ComputeEyeFromAngles(&D_87B000EC->unk_60.at, &D_87B000EC->unk_60.eye, D_87B000F4, D_87B000F0, D_87B000F2);
}

void DrowzeeGame_InitPlayerOverlays(void) {
    u8 i;
    MemoryBlock* temp_s5 = MainPool_AllocState(main_pool_get_available(), 0);

    for (i = 0; i < 4; i++) {
        gCurrentHudState = &gPlayerHudStates[i];
        gCurrentHudState->unk_190 = GeoNode_CreateScale(temp_s5, NULL, 4, NULL, &gRootNodePosition, 0.0f);
        GraphNode_AppendChild(&gGraphRoot0, &gCurrentHudState->unk_190->unk_00);
    }

    MainPool_FinalizeAllocation(temp_s5);
}

void DrowzeeGame_LoadAssets(void) {
    u8 i;
    u8 x;
    u8 y;
    MemoryBlock* temp_v0 = MainPool_AllocState(main_pool_get_available(), 0);

    D_87B000E8 = process_geo_layout(temp_v0, gGeoLayoutData);
    MainPool_FinalizeAllocation(temp_v0);
    ModelRenderer_InitDisplayRoots();
    PokeIcon_OpenModelArchives();
    D_87B000E4 = Model_LoadByArchiveIndex(0xC7);
    gCurrentGraphNode = &gResultScreenNode;
    ModelRenderer_AttachDisplayObject(gCurrentGraphNode);
    Model_InitDisplayObject(gCurrentGraphNode, 0, 0xC7, D_87B000E4->unk_08->unk_00[0]);
    ModelAnim_SetAnimation(gCurrentGraphNode, 0);
    ModelAnim_SetFrame(gCurrentGraphNode, 0);
    D_87B000E4 = Model_LoadByArchiveIndex(0xC4);

    for (i = 0; i < 4; i++) {
        gCurrentHudState = &gPlayerHudStates[i];
        gCurrentGraphNode = &gCurrentHudState->unk_028;

        ModelRenderer_AttachDisplayObject(gCurrentGraphNode);
        Model_InitDisplayObject(gCurrentGraphNode, 0, 0xC4, D_87B000E4->unk_08->unk_00[0]);
        gCurrentHudState->unk_004 = 0;
        ModelAnim_SetAnimation(gCurrentGraphNode, gCurrentHudState->unk_004);
        ModelAnim_SetFrame(gCurrentGraphNode, MiniGame_RandomRange(gCurrentGraphNode->unk_040.unk_04->unk_0A));

        gCurrentGraphNode->unk_024.x = gPlayerSpawnInfo[i].unk_00;
        gCurrentGraphNode->unk_024.y = gPlayerSpawnInfo[i].unk_04;
        gCurrentGraphNode->unk_024.z = gPlayerSpawnInfo[i].unk_08;

        gCurrentGraphNode->unk_030.x = gPlayerSpawnInfo[i].unk_0C;
        gCurrentGraphNode->unk_030.y = gPlayerSpawnInfo[i].unk_10;
        gCurrentGraphNode->unk_030.z = gPlayerSpawnInfo[i].unk_14;

        gCurrentGraphNode->unk_01E.x = gPlayerSpawnInfo[i].unk_18;
        gCurrentGraphNode->unk_01E.y = gPlayerSpawnInfo[i].unk_1A;
        gCurrentGraphNode->unk_01E.z = gPlayerSpawnInfo[i].unk_1C;

        gCurrentHudState->unk_00C = 0;
        gCurrentHudState->unk_00E = 0x14A;
        gCurrentHudState->unk_010 = gCurrentHudState->unk_00E;
        gCurrentHudState->unk_014 = 0;
        gCurrentHudState->unk_015 = 0;

        DrowzeeGame_SetPlayerState(gCurrentHudState, 0, 0, 0, 0);

        for (x = 0; x < 14; x++) {
            for (y = 0; y < 8; y++) {
                gCurrentHudState->unk_194[x][y] = 0;
            }
        }

        gCurrentHudState->unk_274 = 0;
    }

    D_87B000E4 = Model_LoadByArchiveIndex(0xC3);
    D_864052CC = &gGameState;
    gCurrentGraphNode = &D_864052CC->unk_004;
    ModelRenderer_AttachDisplayObject(gCurrentGraphNode);
    Model_InitDisplayObject(gCurrentGraphNode, 0, 0xC3, D_87B000E4->unk_08->unk_00[0]);

    D_864052CC->unk_001 = D_864052CC->unk_000 = 0;

    ModelAnim_SetAnimation(gCurrentGraphNode, D_864052CC->unk_000);
    ModelAnim_SetFrame(gCurrentGraphNode, gCurrentGraphNode->unk_040.unk_04->unk_0A);

    gCurrentGraphNode->unk_024.y = 20.0f;
    gCurrentGraphNode->unk_030.x = 1.0f;
    gCurrentGraphNode->unk_030.y = 1.0f;
    gCurrentGraphNode->unk_030.z = 1.0f;
    gCurrentGraphNode->unk_01E.x = -0xB00;

    D_864052CC->unk_16C = 0;
    D_864052CC->previousHealthState = 0;
    D_87B000E4 = Model_LoadByArchiveIndex(0xD2);

    for (i = 0; i < 4; i++) {
        gCurrentGraphNode = &gPlayerResultNodes[i];

        ModelRenderer_AttachDisplayObject(gCurrentGraphNode);
        Model_InitDisplayObject(gCurrentGraphNode, 0, 0xD2, D_87B000E4->unk_08->unk_00[0]);
        ModelAnim_SetAnimation(gCurrentGraphNode, 0);
        ModelAnim_SetFrame(gCurrentGraphNode, gCurrentGraphNode->unk_040.unk_04->unk_0A);

        gCurrentGraphNode->unk_024.x = gPlayerSpawnInfo[i].unk_00;
        gCurrentGraphNode->unk_024.y = 25.0f;
        gCurrentGraphNode->unk_024.z = gPlayerSpawnInfo[i].unk_08;
        gCurrentGraphNode->unk_01E.x = gPlayerSpawnInfo[i].unk_18;
        gCurrentGraphNode->unk_01E.y = gPlayerSpawnInfo[i].unk_1A;
        gCurrentGraphNode->unk_01E.z = gPlayerSpawnInfo[i].unk_1C;
    }

    DrowzeeGame_InitPlayerOverlays();
    DrowzeeGame_InitPlayerSlots();
    DrowzeeGame_UpdatePlayerTimingWindows();
    DrowzeeGame_InitCamera();
    Widget_CountdownInit();
    Widget_PauseMenuInit();
}

void DrowzeeGame_Main(UNUSED s32 arg0, UNUSED s32 arg1) {
    Stage* sp24;

    main_pool_push_state('MINI');

    Gfx_InitDisplayListBuffers(0x18000, 0);
    sp24 = StageContext_Allocate(0, 1, 3, 1, 2, 1);
    gCurrentTextObject = Font_Init(0x16, 0);
    ASSET_LOAD(D_1000000, common_menu1_ui, 0);
    FRAGMENT_LOAD(fragment31);
    DrowzeeGame_LoadAssets();
    StageContext_Activate(sp24);
    DrowzeeGame_WaitForStart();
    DrowzeeGame_MainLoop();
    DrowzeeGame_ShowResultText();
    StageContext_Deactivate();
    Font_Free();
    Gfx_FreeDisplayListBuffers();

    main_pool_pop_state('MINI');

    Widget_PauseMenuGetResult();
}
