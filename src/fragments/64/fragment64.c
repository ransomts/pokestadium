#include "fragment64.h"
#include "src/12D80.h"
#include "src/1AB70.h"
#include "src/1CF30.h"
#include "src/20330.h"
#include "src/20470.h"
#include "src/225A0.h"
#include "src/232C0.h"
#include "src/2E110.h"
#include "src/3FB0.h"
#include "src/49790.h"
#include "src/6A40.h"
#include "src/DDC0.h"
#include "src/controller.h"
#include "src/memory.h"
#include "src/stage_loader.h"

static unk_D_84803760 gSelectionStates[2];
static BinArchive* gBinArchive;
static void* gPanelTextureAtlas;
static char** D_84803788;
static char** gModeNames;
static char** gMsgBank_Common;
static char** gPanelStrings;
static s16 gTransferPakErrorTimer;
static s16 gTransferPakScrollPos;
static s32 gPanelCount;
static unk_D_848037A0 gPanels[4];
static unk_D_800AE540* D_84816420;
static Controller gPanelController;
static s32 gInputTimerIndex;
static s32 gInputTimerValue;
static s16 gStatusIconFrames[4];

static u16 gPanelColors[] = { 0x1D, 0x341, 0x6947, 0x6A41 };
static unk_D_84803548 D_84803548[] = {
    { 0x001E, 0x0000 },
    { 0x001E, 0x4000 },
    { 0x0001, 0x8000 },
    { 0x0000, 0x0000 },
};
static unk_D_84803548 D_84803558[] = {
    { 0x001E, 0x0000 }, { 0x000A, 0x4000 }, { 0x001E, 0x0002 }, { 0x0001, 0x8000 }, { 0x0000, 0x0000 },
};
static unk_D_84803548 D_8480356C[] = {
    { 0x001E, 0x0000 }, { 0x000A, 0x4000 }, { 0x000A, 0x0002 },
    { 0x001E, 0x0008 }, { 0x0001, 0x8000 }, { 0x0000, 0x0000 },
};
static unk_D_84803548 D_84803584[] = {
    { 0x001E, 0x0000 }, { 0x000A, 0x4000 }, { 0x000A, 0x0002 }, { 0x000A, 0x0008 },
    { 0x001E, 0x8000 }, { 0x0001, 0x8000 }, { 0x0000, 0x0000 },
};
static unk_D_84803548 D_848035A0[] = {
    { 0x001E, 0x0000 }, { 0x000A, 0x4000 }, { 0x000A, 0x0002 }, { 0x000A, 0x0008 },
    { 0x000A, 0x8000 }, { 0x001E, 0x0004 }, { 0x0001, 0x8000 }, { 0x0000, 0x0000 },
};
static unk_D_84803548 D_848035C0[] = {
    { 0x001E, 0x0000 }, { 0x000A, 0x4000 }, { 0x000A, 0x0002 }, { 0x000A, 0x0008 },
    { 0x000A, 0x8000 }, { 0x000A, 0x0004 }, { 0x001E, 0x0001 }, { 0x0001, 0x8000 },
};
static unk_D_84803548* gInputTimingTable[] = {
    NULL, D_84803548, D_84803558, D_8480356C, D_84803584, D_848035A0, D_848035C0,
};
static unk_D_848035FC gModeColors[] = {
    { { 0xF0, 0xF0, 0xF0 }, D_2017740 }, { { 0xF0, 0x96, 0x32 }, D_2019040 }, { { 0x50, 0x96, 0xF0 }, D_20199A0 },
    { { 0xC8, 0x96, 0xF0 }, D_2019680 }, { { 0xF0, 0xC8, 0x78 }, D_2018D20 }, { { 0x64, 0xB4, 0xB4 }, D_2018A00 },
    { { 0x50, 0x96, 0xF0 }, D_20199A0 }, { { 0xC8, 0xF0, 0x50 }, D_2019360 }, { { 0xDC, 0xC8, 0xF0 }, D_2019FE0 },
    { { 0xF0, 0x64, 0x64 }, D_2017A60 }, { { 0x46, 0xB4, 0xF0 }, D_2017D80 }, { { 0x64, 0xC8, 0x64 }, D_20183C0 },
    { { 0xF0, 0xF0, 0x32 }, D_20186E0 }, { { 0xF0, 0x8C, 0xB4 }, D_2019CC0 }, { { 0xB4, 0xF0, 0xF0 }, D_20180A0 },
    { { 0x64, 0xDC, 0xC8 }, D_201A300 },
};
static Color_RGB8 D_8480367C = { 0x00, 0x0A, 0x41 };
static Color_RGB8 D_84803680 = { 0x00, 0x00, 0xD2 };
static u8* D_84803684[] = { D_3008FD0, D_3009720, D_3009E70 };
static u8* D_84803690[] = { D_300A5C0, D_300AD10 };
static u8* D_84803698[] = { D_300B9B8 };
static u8* D_8480369C[][3] = {
    {
        D_300C660,
        D_300D308,
        D_300DFB0,
    },
    {
        D_300EC58,
        D_3005B80,
        D_3005F40,
    },
    {
        D_3006300,
        D_30066C0,
        D_3006A80,
    },
    {
        D_3006E40,
        D_3007200,
        D_30075C0,
    },
    {
        D_3007980,
        D_3007D40,
        D_3008100,
    },
};
static u8* D_848036D8 = D_30084C0;

void TransferPakErrorScreen(void) {
    Gfx_DrawTextureAtlas(gPanelTextureAtlas);

    gSPDisplayList(gDisplayListHead++, gTransferPakErrorBorderDL);

    Gfx_DrawSpriteRGBA16(0x71, 0x1A8, 0x20, 0x18, D_3002220, 0x20, 0x200000);
    Gfx_DrawSpriteRGBA16(0x162, 0x1A8, 0x20, 0x18, D_3002820, 0x20, 0x200000);

    gSPDisplayList(gDisplayListHead++, gPrefDL_End);

    Text_ResetState();
    Text_SetFont(8, 0);
    Text_Print(0x5A, 0x1AA, "*");
    Text_Print(0x149, 0x1AA, "*");
    Text_Print(0x91, 0x1A8, GetMessageString(NULL, 0, gMsgBank_Common, 2));
    Text_Print(0x180, 0x1A8, GetMessageString(NULL, 0, gMsgBank_Common, 3));
    Text_SetupDL();
}

void TransferPakMessageScroll(void) {
    s32 i;
    s32 var_s2;
    s32 var_s4;
    s8 temp_v0;
    s8* var_v0;
    FramebufferImage* sp58;
    Color_RGB8 sp54;
    Color_RGB8 sp50;

    var_s4 = 0x30 - (gTransferPakScrollPos % 24);
    var_s2 = gTransferPakScrollPos / 24;
    sp58 = Stage_GetFrameBuffer();
    sp54 = D_8480367C;
    sp50 = D_84803680;
    DrawGradientPanel(0x228, 0x20, 0x2E, 0x186, &sp54, &sp50);

    gDPSetScissor(gDisplayListHead++, G_SC_NON_INTERLACE, 563, 48, 587, 408);

    Text_ResetState();
    Text_SetFont(0x10, 0);
    Text_SetEnvColor(0xA5, 0xDE, 0x8C, 0xFF);

    if ((D_84816420->unk_0001 == 0) || (D_84816420->unk_0001 == 8)) {
        var_v0 = GetMessageString(NULL, 0, gMsgBank_Common, 1);
    } else {
        var_v0 = GetMessageString(NULL, 0, gMsgBank_Common, 0);
    }

    for (i = 0; i < 16; i++) {
        Text_PutChar(((0x2E - MeasureCharWidth(0x10, var_v0[var_s2])) / 2) + 0x228, var_s4, var_v0[var_s2]);
        var_s2 += 1;
        if (strlen(var_v0) < var_s2) {
            var_s2 = 0;
        }
        var_s4 += 0x18;
    }
    Text_SetupDL();

    gDPSetScissorFrac(gDisplayListHead++, G_SC_NON_INTERLACE, 0, 0, sp58->width * 4.0f, sp58->height * 4.0f);

    gTransferPakScrollPos += 2;
    if (gTransferPakScrollPos >= ((strlen(var_v0) * 0x18) + 0x18)) {
        gTransferPakScrollPos = 0;
    }
}

void SelectionState_Init(unk_D_84803760* arg0, unk_D_800AE540_1194* arg1, s32 arg2) {
    s32 i;

    arg0->unk_00 = 0;
    arg0->unk_01 = 0;

    for (i = 0; i < 6; i++) {
        arg0->unk_02[i] = 0;
        arg0->unk_08[i] = 1;
    }

    if (arg2 != 0) {
        if (arg2 != 8) {
            // clang-format off
            for (i = 3; i < 6; i++) { arg0->unk_02[i] = -1; }
            // clang-format on
        }
    }

    if (arg1->unk_01 == 1) {
        arg0->unk_0E = arg1->unk_08[0]->unk_001;
        arg0->unk_0F = -1;
        arg0->unk_01 = (arg1->unk_08[0]->unk_000 & 2) != 0;
    } else if (arg1->unk_08[0]->unk_001 < arg1->unk_08[1]->unk_001) {
        arg0->unk_0E = arg1->unk_08[0]->unk_001;
        arg0->unk_0F = arg1->unk_08[1]->unk_001;
    } else {
        arg0->unk_0E = arg1->unk_08[1]->unk_001;
        arg0->unk_0F = arg1->unk_08[0]->unk_001;
    }
}

void SelectionState_DrawSprite(s32 arg0, s32 arg1, unk_D_84803760* arg2) {
    u8* sp2C;

    if (arg2->unk_0F == -1) {
        if (arg2->unk_01 != 0) {
            Gfx_DrawSpriteRGBA16(arg0, arg1, 0x24, 0x1A, D_3008880, 0x24, 0x200000);
        } else {
            Gfx_DrawSpriteRGBA16(arg0, arg1, 0x24, 0x1A, D_84803684[arg2->unk_0E], 0x24, 0x200000);
        }
    } else {
        switch (arg2->unk_0E) {
            case 0:
                sp2C = D_84803690[arg2->unk_0F];
                break;

            case 1:
                sp2C = D_84803698[arg2->unk_0F];
                break;

            case 2:
                sp2C = D_8480369C[0][arg2->unk_0F];
                break;
        }
        Gfx_DrawSpriteRGBA16(arg0, arg1, 0x24, 0x2D, sp2C, 0x24, 0x200000);
    }
}

s32 SelectionState_UpdateValue(s32 arg0, s32 arg1, s8 arg2, s8 arg3) {
    s32 sp34;
    s32 sp30;

    if (arg2 != 0) {
        if (arg2 == -1) {
            Gfx_DrawSpriteRGBA16(arg0, arg1, 0x20, 0x14, D_3005680, 0x20, 0x200000);
        } else {
            sp34 = (arg2 >> 4) & 0xF;
            sp30 = arg2 & 0xF;

            if (arg3 > 0) {
                if (sp30 < 3) {
                    sp30++;
                }
            } else if (sp30 > 0) {
                sp30--;
            }

            if (sp30 > 0) {
                Gfx_DrawSpriteRGBA16(arg0 + 6, arg1, 0x18, 0x14, D_8480369C[sp34][sp30], 0x18, 0x200000);
                arg2 = (sp34 * 0x10) | sp30;
            } else {
                arg2 = 0;
            }
        }
    }
    return arg2;
}

void PlayerPanel_DrawLeft(void) {
    unk_D_84803760* temp_v0 = &gSelectionStates[0];
    s32 i;
    s16 var_s2;
    s32 var_s1;

    if (temp_v0->unk_0F == -1) {
        var_s2 = 0x3F;
    } else {
        var_s2 = 0x4A;
    }

    gSPDisplayList(gDisplayListHead++, gTransferPakErrorBorderDL);

    Gfx_DrawSpriteRGBA16(0x2D, var_s2, 0x20, 0xC, D_3003C80, 0x20, 0x200000);
    Gfx_DrawSpriteRGBA16(0x2D, var_s2 + 0xC, 0x20, 0x17, D_30050C0, 0x20, 0x200000);
    Gfx_DrawSpriteRGBA16(0x2D, var_s2 + 0x23, 0x20, 0x17, D_30050C0, 0x20, 0x200000);
    Gfx_DrawSpriteRGBA16(0x2D, var_s2 + 0x3A, 0x20, 0x17, D_30050C0, 0x20, 0x200000);
    Gfx_DrawSpriteRGBA16(0x2D, var_s2 + 0x51, 0x20, 0x17, D_30050C0, 0x20, 0x200000);
    Gfx_DrawSpriteRGBA16(0x25, var_s2 + 0x68, 0x28, 0x2E, D_3002E20, 0x28, 0x200000);

    if (temp_v0->unk_0F == -1) {
        SelectionState_DrawSprite(0x2D, 0x21, &gSelectionStates[0]);
    } else {
        SelectionState_DrawSprite(0x2D, 0x1D, &gSelectionStates[0]);
    }

    var_s1 = var_s2 + 0x76;
    for (i = 0; i < 6; i++) {
        temp_v0->unk_02[i] = SelectionState_UpdateValue(0x2D, var_s1 - i * 0x17, temp_v0->unk_02[i], temp_v0->unk_08[i]);
    }

    gSPDisplayList(gDisplayListHead++, gPrefDL_End);
}

void PlayerPanel_DrawRight(void) {
    unk_D_84803760* temp_v0 = &gSelectionStates[1];
    s32 i;
    s16 var_s2;
    s32 var_s1;

    if (temp_v0->unk_0F == -1) {
        var_s2 = 0xF1;
    } else {
        var_s2 = 0xE6;
    }

    gSPDisplayList(gDisplayListHead++, gTransferPakErrorBorderDL);

    Gfx_DrawSpriteRGBA16(0x2D, var_s2, 0x28, 0x2C, D_3003F80, 0x28, 0x200000);
    Gfx_DrawSpriteRGBA16(0x2D, var_s2 + 0x2C, 0x20, 0x17, D_30050C0, 0x20, 0x200000);
    Gfx_DrawSpriteRGBA16(0x2D, var_s2 + 0x43, 0x20, 0x17, D_30050C0, 0x20, 0x200000);
    Gfx_DrawSpriteRGBA16(0x2D, var_s2 + 0x5A, 0x20, 0x17, D_30050C0, 0x20, 0x200000);
    Gfx_DrawSpriteRGBA16(0x2D, var_s2 + 0x71, 0x20, 0x17, D_30050C0, 0x20, 0x200000);
    Gfx_DrawSpriteRGBA16(0x2D, var_s2 + 0x88, 0x20, 0xE, D_3004D40, 0x20, 0x200000);

    if (temp_v0->unk_0F == -1) {
        SelectionState_DrawSprite(0x2D, 0x189, &gSelectionStates[1]);
    } else {
        SelectionState_DrawSprite(0x2D, 0x17C, &gSelectionStates[1]);
    }

    var_s1 = var_s2 + 0xC;
    for (i = 0; i < 6; i++) {
        temp_v0->unk_02[i] = SelectionState_UpdateValue(0x2D, var_s1 + i * 0x17, temp_v0->unk_02[i], temp_v0->unk_08[i]);
    }

    gSPDisplayList(gDisplayListHead++, gPrefDL_End);
}

void MoveSelection_Record(s32 arg0, s32 arg1) {
    unk_D_84803760* temp_v0 = &gSelectionStates[arg0];

    temp_v0->unk_02[temp_v0->unk_00] = ((arg1 + 1) << 4) | (temp_v0->unk_02[temp_v0->unk_00] & 0xF);
    temp_v0->unk_08[temp_v0->unk_00] = 1;
    temp_v0->unk_00++;
}

void SelectionState_Reset(s32 arg0) {
    unk_D_84803760* ptr = &gSelectionStates[arg0];
    s32 i;

    for (i = 0; i < 6; i++) {
        ptr->unk_08[i] = -1;
    }
    ptr->unk_00 = 0;
}

void func_84800CA4(s16 arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4) {
    DrawPanelAlt(arg0, arg1, arg2, arg3, gPanelColors[arg4]);
}

void DrawPanelContents(unk_D_848037A0* arg0) {
    s32 i;
    s16 temp_s7;
    s16 temp_fp;
    s32 temp_s1_2;
    s32 temp_s2_3;
    s32 temp_v0_4;

    temp_s7 = arg0->unk_0012;
    temp_fp = arg0->unk_0014;

    func_84800CA4(temp_s7, temp_fp, 0x1D7, 0x5E, arg0->unk_0001);

    gSPDisplayList(gDisplayListHead++, gTransferPakErrorBorderDL);

    Gfx_DrawSpriteRGBA16(temp_s7 + 7, temp_fp + 0xB, 0x1A, 0x1A, &D_30005B0, 0x1C, 0x200000);
    Gfx_DrawSpriteRGBA16(temp_s7 + 0xA1, temp_fp + 0xB, 0x1A, 0x1A, &D_3001110, 0x1C, 0x200000);
    Gfx_DrawSpriteRGBA16(temp_s7 + 0x13B, temp_fp + 0xB, 0x1A, 0x1A, &D_3001C70, 0x1C, 0x200000);
    Gfx_DrawSpriteRGBA16(temp_s7 + 7, temp_fp + 0x35, 0x1A, 0x1A, D_3000000, 0x1C, 0x200000);
    Gfx_DrawSpriteRGBA16(temp_s7 + 0xA1, temp_fp + 0x35, 0x1A, 0x1A, &D_3000B60, 0x1C, 0x200000);
    Gfx_DrawSpriteRGBA16(temp_s7 + 0x13B, temp_fp + 0x35, 0x1A, 0x1A, &D_30016C0, 0x1C, 0x200000);

    gSPDisplayList(gDisplayListHead++, gPrefDL_Border);

    Gfx_DrawSpriteRGBA16(temp_s7 + 0x23, temp_fp + 6, 0x28, 0x28, arg0->unk_0020[0], 0x28, 0);
    Gfx_DrawSpriteRGBA16(temp_s7 + 0xBD, temp_fp + 6, 0x28, 0x28, arg0->unk0CA0, 0x28, 0);
    Gfx_DrawSpriteRGBA16(temp_s7 + 0x157, temp_fp + 6, 0x28, 0x28, &arg0->unk0CA0[0xC80], 0x28, 0);
    Gfx_DrawSpriteRGBA16(temp_s7 + 0x23, temp_fp + 0x30, 0x28, 0x28, &arg0->unk0CA0[0x1900], 0x28, 0);
    Gfx_DrawSpriteRGBA16(temp_s7 + 0xBD, temp_fp + 0x30, 0x28, 0x28, &arg0->unk0CA0[0x2580], 0x28, 0);
    Gfx_DrawSpriteRGBA16(temp_s7 + 0x157, temp_fp + 0x30, 0x28, 0x28, &arg0->unk0CA0[0x3200], 0x28, 0);

    gSPDisplayList(gDisplayListHead++, gPrefDL_End);

    Text_ResetState();
    Text_SetFont(4, 0);

    for (i = 0; i < arg0->unk_0017; i++) {
        temp_v0_4 = Panel_IsPokemonSelected(arg0, i);
        if ((arg0->unk_0009 != 0) && (temp_v0_4 != 0)) {
            Text_SetEnvColor(0xFF, 0xFF, 0, 0xFF);
        }
        temp_s1_2 = temp_s7 + ((i % 3) * 0x9A) + 0x4C;
        temp_s2_3 = temp_fp + ((i / 3) * 0x2A) + 8;
        Text_Print(temp_s1_2, temp_s2_3, arg0->unk_0018[i].unk_30);
        if ((arg0->unk_0009 != 0) && (temp_v0_4 != 0)) {
            Text_SetEnvColor(0xFF, 0xFF, 0xFF, 0xFF);
        }
        Text_Print(temp_s1_2, temp_s2_3 + 0x14, "%s%d", GetMessageString(NULL, 0, gPanelStrings, 0x15),
                      arg0->unk_0018[i].unk_24);
    }

    Text_SetupDL();

    if (arg0->unk_0007 > 0) {
        if (arg0->unk_0003 == 0) {
            Gfx_DrawClippedTextureRegion(gPanelTextureAtlas, 0xC8, 0x81, 0x15F, 0x53);
        } else {
            Gfx_DrawClippedTextureRegion(gPanelTextureAtlas, 0x50, 0xF0, 0x15F, 0x53);
        }
        arg0->unk_0007 -= 1;
    }
}

void StatusIcon_DrawAnimated(s16 arg0, s16 arg1, s16 arg2) {
    if (gStatusIconFrames[arg2] < 6) {
        arg0 += gStatusIconFrames[arg2];
    } else {
        arg0 = (arg0 - gStatusIconFrames[arg2]) + 0xC;
    }
    DrawStatusIcon(arg0, arg1);
    gStatusIconFrames[arg2] = (gStatusIconFrames[arg2] + 1) % 12;
}

void ModeSelectionPanel_Draw(unk_D_848037A0* arg0) {
    s32 sp38;
    s16 var_s1;
    s16 var_s2;

    if (arg0->unk_0002 == -1) {
        if (arg0->unk_0003 == 0) {
            var_s1 = 0xC8;
            var_s2 = 0x81;
        } else {
            var_s1 = 0x50;
            var_s2 = 0xF0;
        }

        DrawPanelContents(arg0);
        func_84800CA4(var_s1, var_s2, 0x15F, 0x53, arg0->unk_0001);

        if (arg0->unk_000A == 0) {
            StatusIcon_DrawAnimated(var_s1 + 0x26, var_s2 + 0x30, arg0->unk_0000);
        } else {
            StatusIcon_DrawAnimated(var_s1 + 0x86, var_s2 + 0x30, arg0->unk_0000);
        }

        Text_ResetState();
        Text_SetFont(0x10, 0);
        Text_Print(var_s1 + 0x1F, var_s2 + 0xB, GetMessageString(NULL, 0, gMsgBank_Common, 4));
        Text_Print(var_s1 + 0x4F, var_s2 + 0x30, GetMessageString(NULL, 0, gMsgBank_Common, 5));
        Text_Print(var_s1 + 0xAF, var_s2 + 0x30, GetMessageString(NULL, 0, gMsgBank_Common, 6));
        Text_SetupDL();
        arg0->unk_0007 = 2;
    } else {
        var_s1 = arg0->unk_0012;
        var_s2 = arg0->unk_0014;

        DrawPanelContents(arg0);
        Text_DrawWindowRect(var_s1 + 5, var_s2 + 5, 0x1CD, 0x54, 0, 0, 0, 0x80);
        if (arg0->unk_000A == 0) {
            StatusIcon_DrawAnimated(var_s1 + 0x5C, var_s2 + 0x3C, arg0->unk_0000);
        } else {
            StatusIcon_DrawAnimated(var_s1 + 0xBC, var_s2 + 0x3C, arg0->unk_0000);
        }
        Text_ResetState();
        Text_SetFont(0x10, 0);
        Text_SetEnvColor(0xFF, 0xFF, 0xFF, 0xFF);
        Text_Print(var_s1 + 0x50, var_s2 + 0x14, GetMessageString(NULL, 0, gMsgBank_Common, 4));
        Text_Print(var_s1 + 0x80, var_s2 + 0x3C, GetMessageString(NULL, 0, gMsgBank_Common, 5));
        Text_Print(var_s1 + 0xE0, var_s2 + 0x3C, GetMessageString(NULL, 0, gMsgBank_Common, 6));
        Text_SetupDL();
    }
}

void ResultMessage_Draw(unk_D_848037A0* arg0) {
    char sp38[0x100];
    s32 sp34;
    s32 sp30;
    s32 sp2C;

    switch (D_84816420->unk_0001) {
        case 3:
            sp2C = 0x9B;
            break;

        case 4:
            sp2C = 0x50;
            break;

        case 5:
            sp2C = 0x32;
            break;
    }

    if (arg0->unk_0002 == -1) {
        // clang-format off
        if (arg0->unk_0003 == 0) {
            sp34 = 0xC8; sp30 = 0x81;
        } else {
            sp34 = 0x50; sp30 = 0xF0;
        }
        // clang-format on

        func_84800CA4(sp34, sp30, 0x15F, 0x53, arg0->unk_0001);
        Text_ResetState();
        Text_SetFont(0x10, 0);
        Text_SetEnvColor(0xFF, 0x63, 0x63, 0xFF);
        Text_SetLineHeight(0x25);
        MessageBank_SetPointer_1_9(3, sp2C);
        Text_Print(sp34 + 0x10, sp30 + 0xB, GetMessageString(sp38, sizeof(sp38), gMsgBank_Common, 7));
        Text_SetupDL();
        arg0->unk_0007 = 2;
    } else {
        sp34 = arg0->unk_0012;
        sp30 = arg0->unk_0014;

        DrawPanelContents(arg0);
        Text_DrawWindowRect(sp34 + 5, sp30 + 5, 0x1CD, 0x54, 0, 0, 0, 0x80);
        Text_ResetState();
        Text_SetFont(0x10, 0);
        Text_SetEnvColor(0xFF, 0x63, 0x63, 0xFF);
        Text_SetLineHeight(0x28);
        MessageBank_SetPointer_1_9(3, sp2C);
        Text_Print(sp34 + 0x50, sp30 + 0x14, GetMessageString(NULL, 0, gMsgBank_Common, 7));
        Text_SetupDL();
    }
}

void CenteredMessage_Draw(unk_D_848037A0* arg0) {
    s32 sp3C;
    s32 sp38;
    s32 sp34;
    char* temp_v0;

    if (arg0->unk_0002 == -1) {
        // clang-format off
        if (arg0->unk_0003 == 0) {
            sp3C = 0xC8; sp38 = 0x81;
        } else {
            sp3C = 0x50; sp38 = 0xF0;
        }
        // clang-format on
        arg0->unk_0007 = 0;
        DrawPanelContents(arg0);
        func_84800CA4(sp3C, sp38, 0x15F, 0x53, arg0->unk_0001);
        Text_ResetState();
        Text_SetFont(0x20, 0);
        Text_BeginRender();
        Text_SetPrimColor(0x1C, 0x74, 0xFF, 0xFF);
        temp_v0 = GetMessageString(NULL, 0, gMsgBank_Common, 8);
        Text_Print((sp3C - (MeasureTextWidth(0x20, 0, temp_v0) / 2)) + 0xAF, sp38 + 0x19, temp_v0);
        Text_EndRender();
        Text_SetupDL();
    } else {
        sp3C = arg0->unk_0012;
        sp38 = arg0->unk_0014;

        if (arg0->unk_0008 < 0x10) {
            sp34 = arg0->unk_0008 * 0x10;
        } else if (arg0->unk_0008 < 0x23) {
            sp34 = 0xFF;
        } else if (arg0->unk_0008 < 0x32) {
            sp34 = (-arg0->unk_0008 * 0x10) + 0x320;
        } else {
            sp34 = 0;
        }

        arg0->unk_0008++;
        if (arg0->unk_0008 >= 0x3D) {
            arg0->unk_0008 = 0;
        }

        DrawPanelContents(arg0);
        Text_DrawWindowRect(sp3C + 5, sp38 + 5, 0x1CD, 0x54, 0, 0, 0, 0x80);
        Text_ResetState();
        Text_SetFont(0x20, 0);
        Text_BeginRender();
        Text_SetEnvColor(0xFF, 0xFF, 0xFF, sp34);
        Text_SetPrimColor(0x1C, 0x74, 0xFF, sp34);
        temp_v0 = GetMessageString(NULL, 0, gMsgBank_Common, 8);
        Text_Print((sp3C - (MeasureTextWidth(0x20, 0, temp_v0) / 2)) + 0xEB, sp38 + 0x25, temp_v0);
        Text_EndRender();
        Text_SetupDL();
    }
}

void PokemonInfo_Draw(unk_D_848037A0* arg0) {
    s32 i;
    s16 temp_fp;
    s8 temp_s1;
    unk_D_848035FC* temp_v1;
    s32 idx;
    s32 sp7C;
    PokemonData* sp78;

    temp_fp = arg0->unk_0012;
    temp_s1 = arg0->unk_0016;
    sp7C = arg0->unk_0014;
    sp78 = &arg0->unk_0018[temp_s1];

    func_84800CA4(temp_fp, sp7C, 0x1D7, 0x5E, arg0->unk_0001);

    gSPDisplayList(gDisplayListHead++, gPrefDL_Border);

    Gfx_DrawSpriteRGBA16(temp_fp + 8, sp7C + 7, 0x28, 0x28, &arg0->unk_0020[temp_s1], 0x28, 0);

    gSPDisplayList(gDisplayListHead++, gPrefDL_End);

    Text_ResetState();
    Text_SetFont(4, 0);
    Text_Print(temp_fp + 0x32, sp7C + 7, arg0->unk_0018[temp_s1].unk_30);
    Text_Print(temp_fp + 0x32, sp7C + 0x1B, "%s", GetMessageString(NULL, 0, gPanelStrings, 8));
    Text_Print(temp_fp + 0xBE, sp7C + 7, GetMessageString(NULL, 0, gMsgBank_Common, 9));
    Text_Print(temp_fp + 0xBE, sp7C + 0x1B, GetMessageString(NULL, 0, gMsgBank_Common, 0xA));
    Text_Print(temp_fp + 0xBE, sp7C + 0x2F, GetMessageString(NULL, 0, gMsgBank_Common, 0xB));
    Text_Print(temp_fp + 0xBE, sp7C + 0x43, GetMessageString(NULL, 0, gMsgBank_Common, 0xC));
    Text_Print(temp_fp + 0x32, sp7C + 0x2F, GetMessageString(NULL, 0, gMsgBank_Common, 0xD));

    if (sp78->unk_06 != sp78->unk_07) {
        Text_Print(temp_fp + 0x32, sp7C + 0x43, GetMessageString(NULL, 0, gMsgBank_Common, 0xE));
    }

    idx = RemapStadiumModeIndex(sp78->unk_06);
    Text_SetEnvColor(gModeColors[idx].unk_00.r, gModeColors[idx].unk_00.g, gModeColors[idx].unk_00.b, 0xFF);
    Text_Print(temp_fp + 0x7A, sp7C + 0x2F, GetMessageString(NULL, 0, gModeNames, RemapStadiumModeIndex(sp78->unk_06)));

    if (sp78->unk_06 != sp78->unk_07) {
        idx = RemapStadiumModeIndex(sp78->unk_07);
        Text_SetEnvColor(gModeColors[idx].unk_00.r, gModeColors[idx].unk_00.g, gModeColors[idx].unk_00.b, 0xFF);
        Text_Print(temp_fp + 0x7A, sp7C + 0x43, GetMessageString(NULL, 0, gModeNames, RemapStadiumModeIndex(sp78->unk_07)));
    }

    Text_SetFont(4, 0);
    Text_SetEnvColor(0xFF, 0xFF, 0xFF, 0xFF);
    Text_Print(temp_fp + 0x8C, sp7C + 7, "%s%d", GetMessageString(NULL, 0, gPanelStrings, 0x15),
                  arg0->unk_0018[temp_s1].unk_24);
    Text_Print(temp_fp + 0x52, sp7C + 0x1B, "%3d", sp78->unk_26);
    Text_Print(temp_fp + 0xFA, sp7C + 7, "%3d", sp78->unk_28);
    Text_Print(temp_fp + 0xFA, sp7C + 0x1B, "%3d", sp78->unk_2A);
    Text_Print(temp_fp + 0xFA, sp7C + 0x2F, "%3d", sp78->unk_2C);
    Text_Print(temp_fp + 0xFA, sp7C + 0x43, "%3d", sp78->unk_2E);

    for (i = 0; i < 4; i++) {
        if (sp78->unk_09[i] == 0) {
            break;
        }
        temp_v1 = &gModeColors[gMoveStrings[sp78->unk_09[i] - 1].unk_01];
        Text_SetFont(4, 0);
        Text_SetEnvColor(temp_v1->unk_00.r, temp_v1->unk_00.g, temp_v1->unk_00.b, 0xFF);
        Text_Print(temp_fp + 0x14C, (i * 0x14) + sp7C + 7, GetMessageString(NULL, 0, D_84803788, sp78->unk_09[i] - 1));
        Text_SetFont(4, 0);
        Text_SetEnvColor(0xFF, 0xFF, 0xFF, 0xFF);
        Text_Print(temp_fp + 0x1B3, (i * 0x14) + sp7C + 7, "%2d", sp78->unk_20[i] & 0x3F);
    }

    Text_SetupDL();

    gSPDisplayList(gDisplayListHead++, gPrefDL_Border);

    for (i = 0; i < 4; i++) {
        if (sp78->unk_09[i] == 0) {
            break;
        }
        Gfx_DrawSpriteRGBA16(temp_fp + 0x136, (i * 0x14) + sp7C + 7, 0x14, 0x14,
                      gModeColors[gMoveStrings[sp78->unk_09[i] - 1].unk_01].unk_04, 0x14, 0);
    }

    gSPDisplayList(gDisplayListHead++, gPrefDL_End);

    if (arg0->unk_0007 > 0) {
        if (arg0->unk_0003 == 0) {
            Gfx_DrawClippedTextureRegion(gPanelTextureAtlas, 0xC8, 0x81, 0x15F, 0x53);
        } else {
            Gfx_DrawClippedTextureRegion(gPanelTextureAtlas, 0x50, 0xF0, 0x15F, 0x53);
        }
        arg0->unk_0007--;
    }
}

void DrawPanelHeader(unk_D_848037A0* arg0) {
    s16 sp26;
    s16 sp24;

    if (arg0->unk_0003 == 0) {
        // clang-format off
        sp26 = 0x50; sp24 = 0x81;
        // clang-format on
    } else {
        sp26 = 0x1B1;
        sp24 = 0x123;
    }

    func_84800CA4(sp26, sp24, 0x76, 0x20, arg0->unk_0001);
    Text_ResetState();
    Text_SetFont(8, 0);
    Text_Print((sp26 - (MeasureTextWidth(8, 0, arg0->unk_001C->unk_008) / 2)) + 0x3B, sp24 + 5,
                  arg0->unk_001C->unk_008);
    Text_SetupDL();
}

void Panel_DrawState(unk_D_848037A0* arg0) {
    if ((gTransferPakErrorTimer != 0) || (arg0->unk_0006 != 0)) {
        if ((gTransferPakErrorTimer != 0) && (arg0->unk_0002 == -1)) {
            DrawPanelHeader(arg0);
        }

        switch (arg0->unk_0005) {
            case 0:
                DrawPanelContents(arg0);
                break;

            case 1:
                ModeSelectionPanel_Draw(arg0);
                break;

            case 2:
                ResultMessage_Draw(arg0);
                break;

            case 3:
                CenteredMessage_Draw(arg0);
                break;

            case 4:
                PokemonInfo_Draw(arg0);
                break;
        }

        if (arg0->unk_0006 != 0) {
            arg0->unk_0006--;
        }
    } else if (arg0->unk_0005 == 3) {
        CenteredMessage_Draw(arg0);
    }
}

void Panel_UpdateInputTimer(void) {
    s32 i;
    s8 var_v0;
    unk_D_84803548* ptr;

    for (i = 0; i < 4; i++) {
        if ((gPanels[i].unk_001C != NULL) && (gPanels[i].unk_001C->unk_000 & 2)) {
            break;
        }
    }

    if (i < 4) {
        if ((D_84816420->unk_0001 != 0) && (D_84816420->unk_0001 != 8)) {
            var_v0 = 3;
        } else {
            var_v0 = gPanels[i].unk_0017;
        }
        gPanelController.buttonPressed = 0;
        if (gInputTimerValue == 0) {
            ptr = gInputTimingTable[var_v0];

            gInputTimerValue = ptr[gInputTimerIndex].unk_00;
            if (gInputTimerValue != 0) {
                gPanelController.buttonPressed = ptr[gInputTimerIndex].unk_02;
                gInputTimerIndex++;
            }
        }

        if (gInputTimerValue > 0) {
            gInputTimerValue--;
        }
    }
}

s32 Panel_IsPokemonSelected(unk_D_848037A0* arg0, s8 arg1) {
    s32 i;
    s8 temp_v1;
    unk_D_848037A0* var_a2;

    for (i = 0; i < arg0->unk_000B; i++) {
        if (arg1 == arg0->unk_000C[i]) {
            return 1;
        }
    }

    return 0;
}

s32 Panel_CheckSelectionLimit(unk_D_848037A0* arg0) {
    s32 i;
    s32 var_v0 = 0;

    if (!(arg0->unk_001C->unk_000 & 2)) {
        for (i = 0; i < arg0->unk_000B; i++) {
            var_v0 += arg0->unk_0018[arg0->unk_000C[i]].unk_24;
        }

        if (D_84816420->unk_0001 == 3) {
            if ((arg0->unk_000B == 2) && (var_v0 >= 0x6A)) {
                return 1;
            }

            if ((arg0->unk_000B == 3) && (var_v0 >= 0x9C)) {
                return 1;
            }
        } else if (D_84816420->unk_0001 == 4) {
            if ((arg0->unk_000B == 2) && (var_v0 >= 0x38)) {
                return 1;
            }

            if ((arg0->unk_000B == 3) && (var_v0 >= 0x51)) {
                return 1;
            }
        } else if (D_84816420->unk_0001 == 5) {
            if ((arg0->unk_000B == 2) && (var_v0 >= 0x24)) {
                return 1;
            }

            if ((arg0->unk_000B == 3) && (var_v0 >= 0x33)) {
                return 1;
            }
        }
    }

    return 0;
}

s32 Panel_IsSelectionComplete(unk_D_848037A0* arg0) {
    s8 var_v1;

    if ((D_84816420->unk_0001 != 0) && (D_84816420->unk_0001 != 8)) {
        var_v1 = 3;
    } else if (arg0->unk_001C->unk_000 & 2) {
        var_v1 = arg0->unk_0017;
    } else {
        var_v1 = arg0->unk_0017;
        if ((arg0->unk_0002 != -1) && (var_v1 >= 4)) {
            var_v1 = 3;
        }
    }

    return arg0->unk_000B >= var_v1;
}

void Panel_SelectPokemon(unk_D_848037A0* arg0, s8 arg1, s32 arg2) {
    if (arg1 >= arg0->unk_0017) {
        PlaySoundEffect(8);
        return;
    }

    if (arg2 != 0) {
        PlaySoundEffect(1);
        arg0->unk_0005 = 4;
        arg0->unk_0006 = 2;
        arg0->unk_0016 = arg1;
        return;
    }

    if (Panel_IsPokemonSelected(arg0, arg1) != 0) {
        PlaySoundEffect(8);
        return;
    }

    arg0->unk_000C[arg0->unk_000B] = arg1;
    arg0->unk_000B++;
    MoveSelection_Record(arg0->unk_0003, arg0->unk_0001);

    if (arg0->unk_0009 != 0) {
        arg0->unk_0006 = 2;
    }

    if (Panel_CheckSelectionLimit(arg0) != 0) {
        PlaySoundEffect(8);
        arg0->unk_0005 = 2;
        arg0->unk_0006 = 2;
        return;
    }

    PlaySoundEffect(2);
    if (Panel_IsSelectionComplete(arg0) != 0) {
        arg0->unk_0005 = 1;
        arg0->unk_000A = 0;
        arg0->unk_0006 = 2;
    }
}

void Panel_ClearSelection(unk_D_848037A0* arg0) {
    unk_D_848037A0* temp_v0;

    if (arg0->unk_000B > 0) {
        arg0->unk_000B = 0;

        SelectionState_Reset(arg0->unk_0003);

        if (arg0->unk_0009 != 0) {
            arg0->unk_0006 = 2;
        }

        PlaySoundEffect(3);

        if (arg0->unk_0002 != -1) {
            temp_v0 = &gPanels[arg0->unk_0002];
            temp_v0->unk_0005 = 0;
            temp_v0->unk_000B = 0;
            temp_v0->unk_0009 = 0;
            temp_v0->unk_0006 = 2;
        }
    }
}

void Panel_HandleSelectionInput(Controller* arg0, unk_D_848037A0* arg1) {
    s32 temp_a2 = BTN_IS_DOWN(arg0, BTN_R);

    if (BTN_IS_PRESSED(arg0, BTN_R)) {
        // clang-format off
        arg1->unk_0009 = 1; arg1->unk_0006 = 2;
        // clang-format on
    }

    if (arg0->unk_0A & 0x10) {
        arg1->unk_0009 = 0;
        arg1->unk_0006 = 2;
    }

    if (BTN_IS_PRESSED(arg0, BTN_L)) {
        Panel_ClearSelection(arg1);
    } else if (BTN_IS_PRESSED(arg0, BTN_B)) {
        Panel_SelectPokemon(arg1, 0, temp_a2);
    } else if (BTN_IS_PRESSED(arg0, BTN_CLEFT)) {
        Panel_SelectPokemon(arg1, 1, temp_a2);
    } else if (BTN_IS_PRESSED(arg0, BTN_CUP)) {
        Panel_SelectPokemon(arg1, 2, temp_a2);
    } else if (BTN_IS_PRESSED(arg0, BTN_A)) {
        Panel_SelectPokemon(arg1, 3, temp_a2);
    } else if (BTN_IS_PRESSED(arg0, BTN_CDOWN)) {
        Panel_SelectPokemon(arg1, 4, temp_a2);
    } else if (BTN_IS_PRESSED(arg0, BTN_CRIGHT)) {
        Panel_SelectPokemon(arg1, 5, temp_a2);
    }
}

void Panel_HandleModeInput(Controller* arg0, unk_D_848037A0* arg1) {
    unk_D_848037A0* temp_v0_2;

    if (BTN_IS_PRESSED(arg0, BTN_R)) {
        arg1->unk_0009 = 1;
        arg1->unk_0006 = 2;
    }
    if (arg0->unk_0A & 0x10) {
        arg1->unk_0009 = 0;
        arg1->unk_0006 = 2;
    }

    if (BTN_IS_PRESSED(arg0, BTN_DLEFT | BTN_DRIGHT)) {
        arg1->unk_0006 = 2;
        arg1->unk_000A ^= 1;
        PlaySoundEffect(1);
    } else if (BTN_IS_PRESSED(arg0, BTN_A)) {
        if (arg1->unk_000A == 0) {
            arg1->unk_0006 = 2;
            arg1->unk_0005 = 3;
            arg1->unk_0008 = 0;
            PlaySoundEffect(9);
        } else {
            arg1->unk_0006 = 2;
            arg1->unk_0005 = 0;
            arg1->unk_000B = 0;
            arg1->unk_0009 = 0;
            SelectionState_Reset(arg1->unk_0003);
            PlaySoundEffect(3);
            if (arg1->unk_0002 != -1) {
                temp_v0_2 = &gPanels[arg1->unk_0002];
                temp_v0_2->unk_0005 = 0;
                temp_v0_2->unk_000B = 0;
                temp_v0_2->unk_0009 = 0;
                temp_v0_2->unk_0006 = 2;
            }
        }
    }
    arg1->unk_0006 = 2;
}

void Panel_HandleCancelInput(Controller* arg0, unk_D_848037A0* arg1) {
    if (BTN_IS_PRESSED(arg0, BTN_A | BTN_B)) {
        arg1->unk_0005 = 0;
        arg1->unk_000B = 0;
        arg1->unk_0009 = 0;
        arg1->unk_0006 = 2;
        SelectionState_Reset(arg1->unk_0003);
        PlaySoundEffect(3);
    }
}

void Panel_HandlePokemonDeselect(Controller* arg0, unk_D_848037A0* arg1) {
    s32 var_v0 = 0;

    switch (arg1->unk_0016) {
        case 0:
            if (arg0->unk_0A & 0x4000) {
                var_v0 = 1;
            }
            break;

        case 1:
            if (arg0->unk_0A & 2) {
                var_v0 = 1;
            }
            break;

        case 2:
            if (arg0->unk_0A & 8) {
                var_v0 = 1;
            }
            break;

        case 3:
            if (arg0->unk_0A & 0x8000) {
                var_v0 = 1;
            }
            break;

        case 4:
            if (arg0->unk_0A & 4) {
                var_v0 = 1;
            }
            break;

        case 5:
            if (arg0->unk_0A & 1) {
                var_v0 = 1;
            }
            break;
    }

    if (var_v0 != 0) {
        if (!(arg0->buttonDown & 0x10)) {
            arg1->unk_0009 = 0;
        }
        arg1->unk_0005 = 0;
        arg1->unk_0006 = 2;
    }
}

s32 Panel_ProcessInput(s32 arg0, unk_D_848037A0* arg1) {
    Controller* var_a0;
    s32 sp18 = 0;

    if (arg1->unk_001C->unk_000 & 2) {
        var_a0 = &gPanelController;
    } else {
        var_a0 = &gControllers[arg1->unk_0001];
    }

    if (arg0 == 0) {
        switch (arg1->unk_0005) {
            case 0:
                Panel_HandleSelectionInput(var_a0, arg1);
                break;

            case 1:
                Panel_HandleModeInput(var_a0, arg1);
                break;

            case 2:
                Panel_HandleCancelInput(var_a0, arg1);
                break;

            case 3:
                sp18 = 1;
                break;

            case 4:
                Panel_HandlePokemonDeselect(var_a0, arg1);
                break;
        }
    }
    return sp18;
}

s32 Panel_MainLoop(s32 arg0) {
    UNUSED s32 pad;
    s32 i;
    s32 var_s2;
    s32 sp30;

    var_s2 = 0;
    sp30 = 0;

    Cont_StartReadInputs();
    Cont_ReadInputs();
    MenuInput_Init();
    Panel_UpdateInputTimer();
    Gfx_FinishFrame();
    Stage_BeginDisplayList();

    if (gTransferPakErrorTimer != 0) {
        TransferPakErrorScreen();
    }

    for (i = 0; i < gPanelCount; i++) {
        var_s2 += Panel_ProcessInput(arg0, &gPanels[i]);
        Panel_DrawState(&gPanels[i]);
    }

    PlayerPanel_DrawLeft();
    PlayerPanel_DrawRight();
    TransferPakMessageScroll();

    if (arg0 == 0) {
        if (var_s2 == gPanelCount) {
            sp30 = 1;
            Stage_SetFillColor(0xFFFF);
            Music_StopTrack(0x10);
        }

        if (gTransferPakErrorTimer > 0) {
            gTransferPakErrorTimer -= 1;
        }
    } else {
        gTransferPakErrorTimer = 2;
    }
    return sp30;
}

void Panel_UpdatePokemonOrder(unk_D_800AE540_1194* arg0, unk_D_84803760* arg1) {
    unk_D_800AE540_0004* temp_v0;
    s32 tmp;

    if (arg0->unk_01 == 2) {
        tmp = ((arg1->unk_02[0] >> 4) & 0xF) - 1;
        if (tmp == arg0->unk_08[1]->unk_001) {
            temp_v0 = arg0->unk_08[0];
            arg0->unk_08[0] = arg0->unk_08[1];
            arg0->unk_08[1] = temp_v0;
        }
    }
}

void Panel_SortSelection(s8* arg0, s32 arg1) {
    s32 i;
    s32 j;

    for (i = 0; i < 6; i++) {
        for (j = 0; j < arg1; j++) {
            if (i == arg0[j]) {
                break;
            }
        }

        if (j == arg1) {
            arg0[arg1] = i;
            arg1 += 1;
        }
    }
}

void Panel_SyncSelectionToData(void) {
    s32 i;
    s32 var_s4;
    unk_D_800AE540_0004* temp_s1;
    unk_D_848037A0* var_s2;

    var_s2 = gPanels;
    var_s4 = gPanelCount;

    while (var_s4-- > 0) {
        temp_s1 = var_s2->unk_001C;
        if (temp_s1->unk_000 & 2) {
            temp_s1->unk_002 = temp_s1->unk_214->unk_002;
            _bcopy(temp_s1->unk_214->unk_028, temp_s1->unk_01C, 0x1F8);
        } else {
            Panel_SortSelection(var_s2->unk_000C, var_s2->unk_000B);
            temp_s1->unk_002 = var_s2->unk_000B;

            for (i = 0; i < temp_s1->unk_214->unk_002; i++) {
                temp_s1->unk_01C[i] = var_s2->unk_0018[var_s2->unk_000C[i]];
            }
        }
        var_s2++;
    }

    Panel_UpdatePokemonOrder(&D_84816420->unk_1194[0], &gSelectionStates[0]);
    Panel_UpdatePokemonOrder(&D_84816420->unk_1194[1], &gSelectionStates[1]);
}

void func_84802F7C(s16 arg0, s16 arg1, unk_D_800AE540_0004* arg2, s32 arg3, s32 arg4) {
    s32 i;
    unk_D_848037A0* temp_v1;
    PokemonData* temp_s0;

    temp_v1 = &gPanels[gPanelCount];
    temp_v1->unk_0000 = gPanelCount;
    temp_v1->unk_0001 = arg2->unk_001;
    temp_v1->unk_0002 = arg4;
    temp_v1->unk_0003 = arg3;
    temp_v1->unk_0005 = 0;
    temp_v1->unk_000B = 0;
    temp_v1->unk_0006 = 2;
    temp_v1->unk_0007 = 0;
    temp_v1->unk_0009 = 0;
    temp_v1->unk_000A = 0;
    temp_v1->unk_0012 = arg0;
    temp_v1->unk_0014 = arg1;
    temp_v1->unk_0017 = arg2->unk_214->unk_002;
    temp_v1->unk_0018 = arg2->unk_214->unk_028;
    temp_v1->unk_001C = arg2;

    for (i = 0; i < arg2->unk_214->unk_002; i++) {
        temp_s0 = &arg2->unk_214->unk_028[i];
        ApplyPPUps(temp_s0);
        temp_s0->unk_06 = gSpeciesBaseStats[temp_s0->unk_00.unk_00 - 1].unk_06;
        temp_s0->unk_07 = gSpeciesBaseStats[temp_s0->unk_00.unk_00 - 1].unk_07;
        func_8001B0DC(temp_v1->unk_0020[i], 0, temp_s0);
    }

    gPanelCount++;
}

void func_84803110(unk_D_800AE540* arg0) {
    unk_D_800AE540_1194* temp_s0 = &arg0->unk_1194[0];

    D_84816420 = arg0;
    gPanelCount = 0;
    gTransferPakErrorTimer = 2;
    gTransferPakScrollPos = 0;
    gInputTimerIndex = 0;
    gInputTimerValue = 0;
    gPanelController.buttonPressed = 0;

    SelectionState_Init(&gSelectionStates[0], &D_84816420->unk_1194[0], D_84816420->unk_0001);
    SelectionState_Init(&gSelectionStates[1], &D_84816420->unk_1194[1], D_84816420->unk_0001);

    if (temp_s0->unk_01 == 1) {
        func_84802F7C(0x50, 0x21, temp_s0->unk_08[0], 0, -1);
    } else if (temp_s0->unk_08[0]->unk_001 < temp_s0->unk_08[1]->unk_001) {
        func_84802F7C(0x50, 0x21, temp_s0->unk_08[0], 0, gPanelCount + 1);
        func_84802F7C(0x50, 0x81, temp_s0->unk_08[1], 0, gPanelCount - 1);
    } else {
        func_84802F7C(0x50, 0x21, temp_s0->unk_08[1], 0, gPanelCount + 1);
        func_84802F7C(0x50, 0x81, temp_s0->unk_08[0], 0, gPanelCount - 1);
    }

    temp_s0++;
    if (temp_s0->unk_01 == 1) {
        func_84802F7C(0x50, 0x146, temp_s0->unk_08[0], 1, -1);
    } else if (temp_s0->unk_08[0]->unk_001 < temp_s0->unk_08[1]->unk_001) {
        func_84802F7C(0x50, 0xE6, temp_s0->unk_08[0], 1, gPanelCount + 1);
        func_84802F7C(0x50, 0x146, temp_s0->unk_08[1], 1, gPanelCount - 1);
    } else {
        func_84802F7C(0x50, 0xE6, temp_s0->unk_08[1], 1, gPanelCount + 1);
        func_84802F7C(0x50, 0x146, temp_s0->unk_08[0], 1, gPanelCount - 1);
    }
}

s32 func_84803368(s32 arg0, s32 arg1) {
    Stage* sp24;

    main_pool_push_state('MSEL');

    Gfx_InitBuffers(0x10000, 0);
    sp24 = Stage_Create(1, 1, 2, 0, 2, 1);
    MessageBank_Init();
    Text_Init(0x3C, 0);
    SpriteAssets_Load();
    gBinArchive = ASSET_LOAD2(backgrounds, 1, 1);
    gPanelTextureAtlas = BinArchive_GetFile(gBinArchive, 5);

    ASSET_LOAD(D_1000000, common_menu1_ui, 0);
    ASSET_LOAD(D_3000000, order_select_ui, 0);
    ASSET_LOAD(D_2000000, common_menu2_ui, 0);

    D_84803788 = GetMessageBank(0x25);
    gModeNames = GetMessageBank(0x26);
    gMsgBank_Common = GetMessageBank(0x12);
    gPanelStrings = GetMessageBank(6);

    func_84803110(&gBattleContext);
    Music_ChangeTrack(7);
    Stage_Set(sp24);
    Stage_RunFadeSequence(Panel_MainLoop, 8, 8);
    Stage_Destroy();
    Panel_SyncSelectionToData();
    FontManager_Free();
    Gfx_FreeBuffers();

    main_pool_pop_state('MSEL');
    return 0;
}
