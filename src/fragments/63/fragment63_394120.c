#include "fragment63.h"
#include "src/12D80.h"
#include "src/1C720.h"
#include "src/1CF30.h"
#include "src/20470.h"
#include "src/232C0.h"
#include "src/26820.h"
#include "src/29BA0.h"
#include "src/2C1C0.h"
#include "src/2E110.h"
#include "src/49790.h"
#include "src/4CBC0.h"
#include "src/6A40.h"
#include "src/6BC0.h"
#include "src/DDC0.h"
#include "src/F420.h"
#include "src/memory.h"
#include "src/stage_loader.h"

s32 Battle_ProcessResult(s32, unk_D_86002F34_alt8*);

unk_D_84B19910 gInputBuffer[400];
s32 pad_D_84B1A590[2];
unk_D_84B1A598 gBattleGraphics;
unk_D_84B259A8 D_84B259A8;
unk_D_84B259E8 D_84B259E8;
unk_D_84B25A28 D_84B25A28;
unk_D_84B25A58 D_84B25A58;
unk_D_84B25A90 D_84B25A90;
unk_D_84B25AC0 D_84B25AC0;
unk_D_84B25AC0 D_84B26080;
unk_D_84B26640 gBattleMenuState;
unk_func_80027FA0 gBattleProgress;
char** D_84B26678;

static u8* gTrainerIconTextures[] = {
    D_3015100,
    D_3015700,
    D_3015D00,
    D_3016300,
};
static u32 gGeoLayoutCommands[] = {
    0x0C000000, 0x05000000,    0x0B00002D, 0x00000000, 0x014000F0, 0x00000000,  0xFEDF0000,  0x00000121,  0x05000000,
    0x0D000000, 0x05000000,    0x0F000000, 0x05000000, 0x20050000, 0x00000000,  0x00000000,  0x00000000,  0x00000000,
    0x08000000, Battle_ProcessResult, gInputBuffer, 0x06000000, 0x0F000002, 0x05000000,  0x0A000000,  &gGraphRoot0, 0x06000000,
    0x06000000, 0x0D000001,    0x05000000, 0x0F000002, 0x05000000, 0x0A000000,  &gGraphRoot0, 0x06000000,  0x06000000,
    0x0D000002, 0x05000000,    0x0F000000, 0x05000000, 0x0A000000, &gGraphRoot0, 0x06000000,  0x06000000,  0x0D000003,
    0x05000000, 0x14000000,    0x002B0012, 0xFFFFFF32, 0x16FFFFFF, 0x0F000003,  0x05000000,  0x0A000000,  &gGraphRoot0,
    0x06000000, 0x06000000,    0x06000000, 0x06000000, 0x01000000,
};

void Battle_SavePokemonNames(void) {
    s16 temp_s0;
    unk_D_800AE540_0874* temp_v0;
    PokemonData* var_s1;

    temp_v0 = gBattleContext.unk_1194[0].unk_08[0]->unk_214;
    temp_s0 = temp_v0->unk_002;
    var_s1 = temp_v0->unk_028;

    if ((gBattleContext.unk_0000 == 3) || (gBattleContext.unk_0000 == 6)) {
        if (gBattleContext.unk_0002 != 3) {
            return;
        }
    } else if ((gBattleContext.unk_0000 == 7) && (gBattleContext.unk_0002 != 9)) {
        return;
    }

    while (temp_s0-- > 0) {
        SavePokemonNameData(var_s1++, gBattleContext.unk_0000, gBattleContext.unk_11F2);
    }

    GbsCommitBankBlock(0x13, 0);
}

void Battle_IncrementPlayerName(void) {
    unk_func_8002A728 sp20;
    s32 sp1C = 0;

    GbsGetPlayerName(&sp20);

    if ((gBattleContext.unk_0000 == 3) && (gBattleContext.unk_0002 == 3) && !(gBattleProgress.unk_00 & 8)) {
        sp1C = 1;
    }

    if ((gBattleContext.unk_0000 == 6) && (gBattleContext.unk_0002 == 3) && !(gBattleProgress.unk_00 & 0x40)) {
        sp1C = 1;
    }

    if ((sp1C != 0) && (sp20.unk_00 < 2)) {
        sp20.unk_00++;
        GbsSetPlayerName(&sp20);
        if (sp20.unk_00 == 1) {
            gBattleContext.unk_11F6 |= 8;
        } else {
            gBattleContext.unk_11F6 |= 0x10;
        }
    }
}

void Battle_SetProgressFlags(void) {
    if (((gBattleContext.unk_0000 != 3) || (gBattleContext.unk_0002 >= 3)) &&
        ((gBattleContext.unk_0000 != 6) || (gBattleContext.unk_0002 >= 3)) &&
        ((gBattleContext.unk_0000 != 7) || (gBattleContext.unk_0002 >= 9))) {
        gBattleProgress.unk_00 |= (1 << gBattleContext.unk_0000);
        if (gBattleProgress.unk_00 == 0xF8) {
            gBattleProgress.unk_07 = 1;
            gBattleContext.unk_11F5 |= 4;
        }
        func_80027FE0(&gBattleProgress, gBattleContext.unk_11F2);
    }
}

void Battle_UpdateStageProgress(void) {
    if (gBattleContext.unk_0000 == 7) {
        if ((gBattleContext.unk_0002 >= gBattleProgress.unk_04) && (gBattleContext.unk_0002 < 8)) {
            gBattleProgress.unk_04 = gBattleContext.unk_0002 + 1;
            gBattleContext.unk_11F6 |= 0x400;
        }
    } else if (gBattleContext.unk_0000 == 3) {
        if ((gBattleContext.unk_0002 >= gBattleProgress.unk_05) && (gBattleContext.unk_0002 < 4)) {
            gBattleProgress.unk_05 = gBattleContext.unk_0002 + 1;
            gBattleContext.unk_11F6 |= 0x400;
        }
    } else if ((gBattleContext.unk_0000 == 6) && (gBattleContext.unk_0002 >= gBattleProgress.unk_06) && (gBattleContext.unk_0002 < 4)) {
        gBattleProgress.unk_06 = gBattleContext.unk_0002 + 1;
        gBattleContext.unk_11F6 |= 0x400;
    }
    func_80027FE0(&gBattleProgress, gBattleContext.unk_11F2);
}

char* Battle_GetMessageString(s32 arg0) {
    return GetMessageString(NULL, 0, D_84B26678, arg0);
}

char* Battle_GetMessageStringBuffer(char* arg0, s32 arg1, u32 arg2) {
    return GetMessageString(arg0, arg1, D_84B26678, arg2);
}

s32 Battle_ProcessResult(s32 arg0, unk_D_86002F34_alt8* arg1) {
    if (arg0 == 5) {
        func_84B0345C(arg1->unk_00.unk_14);
        func_80015684();
    }
}

void GraphNode_Reset(Fragment2_1GraphNode* arg0) {
    GraphNode_ClearCallback(arg0);
    Vec3f_Set(&arg0->unk_024, 0.0f, 0.0f, 0.0f);
    Vec3f_Set(&arg0->unk_030, 1.0f, 1.0f, 1.0f);
    Vec3s_Set(&arg0->unk_01E, 0, 0, 0);
}

void Battle_ResetGraphNodes(void) {
    s32 i;

    for (i = 0; i < 128; i++) {
        GraphNode_Reset(&gBattleGraphics.unk_0008[i]);
    }
}

void Text_DrawCentered(s16 arg0, s16 arg1, char* arg2) {
    s32 sp1C = MeasureTextWidth(2, 0, arg2);

    Text_ResetState();
    Text_SetLineHeight(0xC);
    Text_SetFont(2, 0);
    Text_Print(0x20 - (sp1C / 2), arg1, arg2);
    Text_SetupDL();
}

void Gfx_DrawPanel(s16 arg0, s16 arg1, s16 arg2, s16 arg3, u8 arg4, u8 arg5, u8 arg6, u8 arg7) {
    s16 temp_a2;
    s16 temp_s0_32;
    s16 var_s2;
    s16 var_s3;

    if (arg2 >= 0x10) {
        var_s3 = 8;
    } else {
        var_s3 = arg2 / 2;
    }
    if (arg3 >= 0x10) {
        var_s2 = 8;
    } else {
        var_s2 = arg3 / 2;
    }
    temp_a2 = arg2 - (var_s3 * 2);
    temp_s0_32 = arg3 - (var_s2 * 2);

    gSPDisplayList(gDisplayListHead++, gPrefDL_Border);
    gDPSetEnvColor(gDisplayListHead++, arg4, arg5, arg6, arg7);

    gDPLoadTextureBlock_4b(gDisplayListHead++, D_3015080, G_IM_FMT_I, 16, 8, 0, G_TX_NOMIRROR | G_TX_WRAP,
                           G_TX_NOMIRROR | G_TX_WRAP, 5, 5, G_TX_NOLOD, G_TX_NOLOD);

    Gfx_DrawTextureRect(arg0, arg1, var_s3, var_s2, 0, 0, 0x2000 / var_s3, 0x2000 / var_s2, 0);

    gDPLoadTextureBlock_4b(gDisplayListHead++, D_30150C0, G_IM_FMT_I, 16, 8, 0, G_TX_NOMIRROR | G_TX_WRAP,
                           G_TX_NOMIRROR | G_TX_WRAP, 5, 5, G_TX_NOLOD, G_TX_NOLOD);

    Gfx_DrawTextureRect((arg0 + arg2) - var_s3, arg1, var_s3, var_s2, 0, 0, 0x2000 / var_s3, 0x2000 / var_s2, 0);

    gDPLoadTextureBlock_4b(gDisplayListHead++, D_3015000, G_IM_FMT_I, 16, 8, 0, G_TX_NOMIRROR | G_TX_WRAP,
                           G_TX_NOMIRROR | G_TX_WRAP, 5, 5, G_TX_NOLOD, G_TX_NOLOD);

    Gfx_DrawTextureRect(arg0, (arg1 + arg3) - var_s2, var_s3, var_s2, 0, 0, 0x2000 / var_s3, 0x2000 / var_s2, 0);

    gDPLoadTextureBlock_4b(gDisplayListHead++, D_3015040, G_IM_FMT_I, 16, 8, 0, G_TX_NOMIRROR | G_TX_WRAP,
                           G_TX_NOMIRROR | G_TX_WRAP, 5, 5, G_TX_NOLOD, G_TX_NOLOD);

    Gfx_DrawTextureRect((arg0 + arg2) - var_s3, (arg1 + arg3) - var_s2, var_s3, var_s2, 0, 0, 0x2000 / var_s3,
                  0x2000 / var_s2, 0);

    gSPDisplayList(gDisplayListHead++, gPrefDL_Fill);

    if ((temp_a2 > 0) && (temp_s0_32 > 0)) {
        Gfx_FillRectRGBA(arg0 + var_s3, arg1, temp_a2, var_s2, arg4, arg5, arg6, arg7);
        Gfx_FillRectRGBA(arg0, arg1 + var_s3, arg2, temp_s0_32, arg4, arg5, arg6, arg7);
        Gfx_FillRectRGBA(arg0 + var_s3, arg1 + var_s3 + temp_s0_32, temp_a2, var_s2, arg4, arg5, arg6, arg7);
    } else if (temp_a2 > 0) {
        Gfx_FillRectRGBA(arg0 + var_s3, arg1, temp_a2, arg3, arg4, arg5, arg6, arg7);
    } else if (temp_s0_32 > 0) {
        Gfx_FillRectRGBA(arg0, arg1 + var_s2, arg2, temp_s0_32, arg4, arg5, arg6, arg7);
    }

    gSPDisplayList(gDisplayListHead++, gPrefDL_End);
}

void Battle_DrawTrainerInfo(FramebufferImage* arg0, s16 arg1, u8* arg2, u8* arg3) {
    unk_D_800AE540_1194* temp_v1 = &gBattleContext.unk_1194[arg1];

    Gfx_SetupFrameBuffer(&gDisplayListHead, arg0);

    gSPDisplayList(gDisplayListHead++, gTransferPakErrorBorderDL);

    Gfx_DrawSpriteRGBA16(0, 0, 0x40, 0x20, arg3, 0x40, 0x200000);
    Gfx_DrawSpriteRGBA16(0, 0x20, 0x40, 0x20, arg3 + 0x1000, 0x40, 0x200000);
    Gfx_DrawSpriteRGBA16(0, 0x40, 0x40, 0x20, arg3 + 0x2000, 0x40, 0x200000);
    Gfx_DrawSpriteRGBA16(4, 0x24, 0x38, 0x1C, arg2 + 0x208, 0x40, 0x200000);
    Gfx_DrawSpriteRGBA16(4, 0x40, 0x38, 0x1C, arg2 + 0x1008, 0x40, 0x200000);

    if (gBattleContext.unk_0000 == 0 || gBattleContext.unk_0000 == 9) {
        if (temp_v1->unk_08[0]->unk_000 & 2) {
            Gfx_DrawSpriteRGBA16(8, 4, 0x30, 0x10, &D_3016900, 0x30, 0x200000);
        } else if (temp_v1->unk_01 == 1) {
            Gfx_DrawSpriteRGBA16(8, 4, 0x30, 0x10, gTrainerIconTextures[temp_v1->unk_08[0]->unk_001], 0x30, 0x200000);
        } else {
            if (temp_v1->unk_08[0]->unk_001 < temp_v1->unk_08[1]->unk_001) {
                Gfx_DrawSpriteRGBA16(8, 4, 0x30, 0x10, gTrainerIconTextures[temp_v1->unk_08[0]->unk_001], 0x30, 0x200000);
                Gfx_DrawSpriteRGBA16(8, 0x14, 0x30, 0x10, gTrainerIconTextures[temp_v1->unk_08[1]->unk_001], 0x30, 0x200000);
            } else {
                Gfx_DrawSpriteRGBA16(8, 4, 0x30, 0x10, gTrainerIconTextures[temp_v1->unk_08[1]->unk_001], 0x30, 0x200000);
                Gfx_DrawSpriteRGBA16(8, 0x14, 0x30, 0x10, gTrainerIconTextures[temp_v1->unk_08[0]->unk_001], 0x30, 0x200000);
            }
        }

        gSPDisplayList(gDisplayListHead++, gPrefDL_End);
    } else if ((arg1 == 0) || (gBattleContext.unk_0000 == 0xA)) {
        Gfx_DrawSpriteRGBA16(8, 4, 0x30, 0x10, gTrainerIconTextures[temp_v1->unk_08[0]->unk_001], 0x30, 0x200000);

        gSPDisplayList(gDisplayListHead++, gPrefDL_End);

        Text_DrawCentered(arg1, 0x14, temp_v1->unk_08[0]->unk_214->unk_014);
    } else {
        gSPDisplayList(gDisplayListHead++, gPrefDL_End);

        Text_DrawCentered(arg1, 6, temp_v1->unk_08[0]->unk_214->unk_220);
    }
}

void Battle_AnimateSprites(s16 arg0) {
    static s16 D_84B0FC0C[] = {
        0x0300, 0x0150, 0xFEB0, 0xFD00, 0xFD00, 0xFEB0, 0x0150, 0x0300,
    };
    static f32 D_84B0FC1C[] = {
        -3.0f, -2.0f, 2.0f, 3.0f, -3.0f, -2.0f, 2.0f, 3.0f,
    };

    s32 i;

    if (arg0 < 0x10) {
        for (i = 0; i < 4; i++) {
            gBattleGraphics.unk_0008[i + 0].unk_024.y += 2.0f * arg0 * 0.5f;
            gBattleGraphics.unk_0008[i + 0].unk_01E.x += 0x300;
            gBattleGraphics.unk_0008[i + 8].unk_024.y += 2.0f * arg0 * 0.5f;
            gBattleGraphics.unk_0008[i + 8].unk_01E.x += 0x300;
            gBattleGraphics.unk_0008[i + 4].unk_01E.x -= 0x300;
            // clang-format off
            gBattleGraphics.unk_0008[i + 4].unk_024.y -= 2.0f * arg0 * 0.5f; gBattleGraphics.unk_0008[i + 12].unk_01E.x -= 0x300;
            // clang-format on
            gBattleGraphics.unk_0008[i + 12].unk_024.y -= 2.0f * arg0 * 0.5f;
        }

        for (i = 0; i < 8; i++) {
            gBattleGraphics.unk_0008[i + 0].unk_01E.z += D_84B0FC0C[i];
            gBattleGraphics.unk_0008[i + 8].unk_01E.z += D_84B0FC0C[i];

            gBattleGraphics.unk_0008[i + 0].unk_024.x += arg0 * D_84B0FC1C[i] * 0.5f;
            gBattleGraphics.unk_0008[i + 8].unk_024.x += arg0 * D_84B0FC1C[i] * 0.5f;
        }
    }
}

void Battle_SetSpriteAlpha(s16 arg0) {
    s32 i;

    if (arg0 < 0x10) {
        for (i = 0; i < 16; i++) {
            gBattleGraphics.unk_0008[i].unk_01D = (-arg0 * 0x10) + 0xF0;
        }

        for (i = 28; i < 32; i++) {
            gBattleGraphics.unk_0008[i].unk_01D = (-arg0 * 0x10) + 0xF0;
        }
    }
}

void Battle_BeginFrame(void) {
    Stage_BeginDisplayList();
    Gfx_FillScreen(&gDisplayListHead, 1);
    Graph_SetTextureState(gBattleGraphics.unk_0004);
    RenderMenuPanel(&gBattleMenuState.unk_1C);
    RenderMenuPanel(&gBattleMenuState.unk_28);
    Stage_Advance();
}

void Battle_ProcessFrame(void) {
    Game_UpdateInputs();
    func_84B03814(gInputBuffer);
    UI_StateMachine(&D_84B25A28);
    Battle_BeginFrame();
}

s32 Battle_MainLoop(void) {
    s32 i;
    s32 var_s1 = 0;

    Battle_InitializeFromMode();
    func_84B07CF8(&D_84B25A28, gBattleGraphics.unk_0004->unk_0C);
    UI_Init(&D_84B25A28, gBattleGraphics.unk_B40C);
    Music_ChangeTrack(0x31);

    for (i = 0; i < 16; i++) {
        Battle_ProcessFrame();
    }

    Stage_FadeIn(8);

    while (func_84B07AB8(&D_84B25A28, gBattleGraphics.unk_0008) == 0) {
        Battle_ProcessFrame();
        var_s1++;
    }

    while (var_s1 < 0x1E) {
        Battle_ProcessFrame();
        var_s1++;
    }

    for (i = 0; i < 90; i++) {
        Battle_ProcessFrame();
    }

    Music_StopTrack(0x20);
    Stage_SetFillColor(1);
    Stage_FadeOut(0x10);

    for (i = 0; i < 18; i++) {
        Battle_ProcessFrame();
    }

    if (gBattleContext.unk_11F5 & 1) {
        gBattleContext.unk_11F5 &= ~1;
        GbsClearAndCommitBlock(0x15, 0);
        GbsSyncBank(2);
    }

    return 4;
}

void Battle_UpdateAndRender(void) {
    Game_UpdateInputs();
    func_84B03814(gInputBuffer);
    func_84B04A7C(&D_84B259A8);
    func_84B062E4(&D_84B259E8);
    UI_StateMachine(&D_84B25A28);
    Battle_BeginFrame();
}

void Battle_InitGraphics(void) {
    func_84B05728(&D_84B259A8);
    func_84B06A54(&D_84B259E8, gBattleGraphics.unk_B408, gBattleGraphics.unk_B40C);
    func_84B07CF8(&D_84B25A28, gBattleGraphics.unk_0004->unk_0C);
}

s32 func_84B017AC(void) {
    s32 i;
    s32 var_s1;

    if (osTvType == OS_TV_PAL) {
        var_s1 = 0x4B;
    } else {
        var_s1 = 0x5A;
    }

    Battle_InitializeFromMode();
    Battle_InitGraphics();
    UI_Init(&D_84B25A28, gBattleGraphics.unk_B40C);

    for (i = 0; i < 16; i++) {
        Battle_UpdateAndRender();
    }

    Stage_FadeIn(8);

    for (i = 0; i < 20; i++) {
        Battle_UpdateAndRender();
    }

    func_84B04F78(&D_84B259A8, &gBattleGraphics.unk_0008[0x10]);
    func_84B06364(&D_84B259E8, gBattleGraphics.unk_0008, 0);
    Music_ChangeTrack(0x33);

    for (i = 0; i < var_s1; i++) {
        Battle_UpdateAndRender();
    }

    func_84B0509C(&D_84B259A8);
    D_84B259E8.unk_00 = 2;

    for (i = 0; i < 16; i++) {
        Battle_UpdateAndRender();
    }

    while (func_84B07AB8(&D_84B25A28, gBattleGraphics.unk_0008) == 0) {
        Battle_UpdateAndRender();
    }

    for (i = 0; i < var_s1; i++) {
        Battle_UpdateAndRender();
    }

    Music_StopTrack(0x20);
    Stage_SetFillColor(1);
    Stage_FadeOut(0x10);

    for (i = 0; i < 18; i++) {
        Battle_UpdateAndRender();
    }

    if (gBattleContext.unk_11F5 & 1) {
        gBattleContext.unk_11F5 &= ~1;
        GbsClearAndCommitBlock(0x15, 0);
        GbsSyncBank(2);
    }

    return 4;
}

void func_84B01994(void) {
    s32 i;
    s32 j;
    unk_D_800AE540_0004* var_a1;
    unk_D_800AE540_0874* temp_v1;

    if (!(gBattleContext.unk_11F5 & 2) && (gBattleContext.unk_11F2 == 1) && (gBattleContext.unk_0000 == 6) &&
        (gBattleContext.unk_0002 == 3)) {
        var_a1 = gBattleContext.unk_1194[0].unk_08[0];
        temp_v1 = var_a1->unk_214;

        for (i = 0; i < temp_v1->unk_002; i++) {
            s32 tmp = (temp_v1->unk_028[i].unk_52 & 0x70) >> 4;
            s32 tmp2 = temp_v1->unk_028[i].unk_52 & 0xF;

            if ((tmp >= 4) || (tmp2 >= 13)) {
                return;
            }
        }

        for (i = 0; i < var_a1->unk_002; i++) {
            PokemonData* ptr = &var_a1->unk_01C[i];

            if (ptr->unk_00.unk_00 == 0x19) {
                for (j = 0; j < 4; j++) {
                    if (ptr->unk_09[j] == 0) {
                        break;
                    } else if (ptr->unk_09[j] == 0x39) {
                        return;
                    }
                }
                gBattleContext.unk_11F6 |= 0x1000;
                break;
            }
        }
    }
}

void func_84B01AA0(void) {
    Game_UpdateInputs();
    func_84B03814(gInputBuffer);
    func_84B0A1F4(&D_84B25A58);
    func_84B062E4(&D_84B259E8);
    func_84B0BBEC(&D_84B25A90);
    func_84B0D4B4(&D_84B25AC0);
    func_84B0D4B4(&D_84B26080);
    BarUpdateCallback(&gBattleMenuState.unk_00);
    BarUpdateCallback(&gBattleMenuState.unk_10);
    func_84B0F8E8(&gBattleMenuState.unk_1C);
    func_84B0F8E8(&gBattleMenuState.unk_28);
    Battle_BeginFrame();
}

void func_84B01B40(void) {
    s32 tmp;

    func_84B0A9D0(&D_84B25A58);
    func_84B06A54(&D_84B259E8, gBattleGraphics.unk_B408, gBattleGraphics.unk_B40C);
    func_84B0BE28(&D_84B25A90);

    if (gBattleGraphics.unk_0003 != 0) {
        func_84B0D7A8(&D_84B25AC0, 1, -1);
        func_84B0D7A8(&D_84B26080, 0, -1);
    } else {
        func_84B0D7A8(&D_84B25AC0, 1, gBattleGraphics.unk_0001);
        tmp = gBattleGraphics.unk_0001 == 0;
        func_84B0D7A8(&D_84B26080, 0, tmp);
    }

    BarCreate(&gBattleMenuState.unk_00, 0);
    BarCreate(&gBattleMenuState.unk_10, 1);
}

void func_84B01C2C(void) {
    s32 i;

    func_84B0A544(&D_84B25A58, gBattleGraphics.unk_B40C);

    for (i = 0; i < 8; i++) {
        func_84B01AA0();
    }

    if (gBattleContext.unk_1194[1].unk_08[0]->unk_000 & 2) {
        if (gBattleContext.unk_1194[0].unk_1C == 1) {
            Music_ChangeTrack(0x32);
        } else {
            Music_ChangeTrack(0x45);
        }
    } else {
        Music_ChangeTrack(0x32);
    }

    Stage_FadeIn(8);

    while (func_84B0A634(&D_84B25A58, gBattleGraphics.unk_0008) == 0) {
        func_84B01AA0();
    }

    while (D_84B25A58.unk_00 != 0) {
        func_84B01AA0();
    }

    func_84B0D54C(&D_84B25AC0, &gBattleGraphics.unk_0008[0x1C], &gBattleGraphics.unk_0008[0x20]);
    func_84B0D54C(&D_84B26080, &gBattleGraphics.unk_0008[0x1E], &gBattleGraphics.unk_0008[0x20]);

    while ((D_84B259E8.unk_00 != 0) || (D_84B26080.unk_5A0 != 0)) {
        func_84B01AA0();
    }
}

void func_84B01DBC(void) {
    s32 i;

    func_84B0A544(&D_84B25A58, gBattleGraphics.unk_B40C);

    for (i = 0; i < 8; i++) {
        func_84B01AA0();
    }

    Music_ChangeTrack(0x32);
    Stage_FadeIn(8);

    while (func_84B0A634(&D_84B25A58, gBattleGraphics.unk_0008) == 0) {
        func_84B01AA0();
    }

    for (i = 0; i < 50; i++) {
        func_84B01AA0();
    }

    BarInit(&gBattleMenuState.unk_00, &gBattleGraphics.unk_0008[0x1A]);
    PlayUISfx(0x01100013, 0, 0);

    while (D_84B25A58.unk_00 != 0) {
        func_84B01AA0();
    }

    BarStartShrink(&gBattleMenuState.unk_00);
    func_84B0D54C(&D_84B25AC0, &gBattleGraphics.unk_0008[0x1C], &gBattleGraphics.unk_0008[0x20]);
    func_84B0D54C(&D_84B26080, &gBattleGraphics.unk_0008[0x1E], &gBattleGraphics.unk_0008[0x20]);

    if (gBattleContext.unk_0003 < 8) {
        for (i = 0; i < 16; i++) {
            func_84B01AA0();
        }
        BarInit(&gBattleMenuState.unk_10, &gBattleGraphics.unk_0008[0x1B]);
        PlaySoundEffect(0x28);
    }

    while ((D_84B259E8.unk_00 != 0) || (D_84B26080.unk_5A0 != 0)) {
        func_84B01AA0();
    }
}

void func_84B01F94(void) {
    s32 i;
    s32 tmp;

    func_84B0D718(&D_84B26080);
    tmp = gBattleGraphics.unk_0001 == 0;
    func_84B06364(&D_84B259E8, gBattleGraphics.unk_0008, tmp + 1);

    while ((D_84B259E8.unk_00 != 0) || (D_84B26080.unk_5A0 != 0)) {
        func_84B01AA0();
    }

    for (i = 0; i < 16; i++) {
        func_84B01AA0();
    }
}

void func_84B0204C(void) {
    s32 i;
    s32 j;

    while ((D_84B25AC0.unk_5A0 != 0) || (D_84B26080.unk_5A0 != 0)) {
        func_84B01AA0();
    }

    for (i = 16; i < ARRAY_COUNT(gBattleGraphics.unk_0008); i++) {
        GraphNode_Reset(&gBattleGraphics.unk_0008[i]);
    }

    PlayUISfx(0x01100017, 0, 0);

    for (j = 0; j < 16; j++) {
        Game_UpdateInputs();
        Battle_AnimateSprites(j);
        func_84B03814(gInputBuffer);
        Battle_BeginFrame();
    }

    for (i = 0; i < 16; i++) {
        GraphNode_Reset(&gBattleGraphics.unk_0008[i]);
    }

    for (j = 0; j < 16; j++) {
        Game_UpdateInputs();
        func_84B03814(gInputBuffer);
        Battle_BeginFrame();
    }
}

void func_84B02188(void) {
    s32 i;

    Music_StopTrack(0x3C);

    for (i = 0; i < 16; i++) {
        Game_UpdateInputs();
        Battle_SetSpriteAlpha(i);
        func_84B03814(gInputBuffer);
        Battle_BeginFrame();
    }
}

void func_84B021FC(void) {
    s32 i;

    Music_StopTrack(0x3C);
    Stage_SetFillColor(1);
    Stage_FadeOut(0x10);

    for (i = 0; i < 18; i++) {
        Game_UpdateInputs();
        func_84B03814(gInputBuffer);
        Battle_BeginFrame();
    }

    for (i = 0; i < 16; i++) {
        Game_UpdateInputs();
        func_84B03814(gInputBuffer);
        Battle_BeginFrame();
    }
}

s32 func_84B022A0(void) {
    s32 var_s2;
    s32 var_v0_2;

    if (gBattleContext.unk_0000 == 7) {
        func_84B0F950(&gBattleMenuState.unk_1C, 2);
    } else {
        func_84B0F950(&gBattleMenuState.unk_1C, 1);
    }

    var_s2 = func_84B0FADC(&gBattleMenuState.unk_1C);
    while (var_s2 == -1) {
        func_84B01AA0();
        var_s2 = func_84B0FADC(&gBattleMenuState.unk_1C);
    }

    if (var_s2 == 1) {
        if (func_8002847C() != 0) {
            func_84B0F950(&gBattleMenuState.unk_1C, 0xA);

            var_v0_2 = func_84B0FADC(&gBattleMenuState.unk_1C);
            while (var_v0_2 == -1) {
                func_84B01AA0();
                var_v0_2 = func_84B0FADC(&gBattleMenuState.unk_1C);
            }

            if (var_v0_2 == 1) {
                var_s2 = 0;
            }
        }
        if (var_s2 == 1) {
            gBattleContext.unk_0003 = gBattleContext.unk_0003 + 1;
            Battle_PackStateForSave();
            GbsSyncBank(2);
        }
    }
    return var_s2;
}

s32 func_84B023C0(void) {
    s32 sp24 = 1;
    s32 var_v0;

    if (func_8002847C() != 0) {
        func_84B0F950(&gBattleMenuState.unk_1C, 0xA);

        var_v0 = func_84B0FADC(&gBattleMenuState.unk_1C);
        while (var_v0 == -1) {
            func_84B01AA0();
            var_v0 = func_84B0FADC(&gBattleMenuState.unk_1C);
        }

        if (var_v0 == 1) {
            sp24 = 0;
        }
    }

    if (sp24 != 0) {
        gBattleContext.unk_11F3--;
        Battle_PackStateForSave();
        GbsSyncBank(2);
    }
    return sp24;
}

s32 func_84B02474(void) {
    s32 var_v0;

    if (gBattleContext.unk_1194[0].unk_1C == 1) {
        gBattleContext.unk_1194[0].unk_1E += 1;
    }

    if (gBattleContext.unk_1194[1].unk_1C == 1) {
        gBattleContext.unk_1194[1].unk_1E += 1;
    }

    func_84B01C2C();
    PlayUISfx(0x0110000F, 0, 0);
    func_84B0F950(&gBattleMenuState.unk_1C, 9);
    func_84B0F950(&gBattleMenuState.unk_28, 5);

    var_v0 = func_84B0FADC(&gBattleMenuState.unk_28);
    while (var_v0 == -1) {
        func_84B01AA0();
        var_v0 = func_84B0FADC(&gBattleMenuState.unk_28);
    }

    switch (var_v0) {
        case 0:
            gBattleContext.unk_11F6 |= 0x21;
            break;

        case 1:
            gBattleContext.unk_11F6 |= 0x81;
            break;

        case 2:
            gBattleContext.unk_11F6 |= 1;
            break;
    }

    func_84B0D718(&D_84B26080);
    func_84B0D718(&D_84B25AC0);
    PlayUISfx(0x0110000D, 0, 0);
    func_84B0204C();
    func_84B021FC();

    return 4;
}

s32 func_84B025D0(void) {
    func_84B01C2C();

    do {
        func_84B01AA0();
    } while (!(BTN_IS_PRESSED(gPlayer1Controller, BTN_A)));

    func_84B0D718(&D_84B26080);
    func_84B0D718(&D_84B25AC0);
    PlayUISfx(0x0110000D, 0, 0);
    func_84B0204C();
    func_84B021FC();

    return 4;
}

s32 func_84B02654(void) {
    UNUSED s32 pad[2];
    s32 sp2C = 4;
    s32 i;
    s32 var_s2;
    s32 var_v0;

    if (gBattleGraphics.unk_0002 != 0) {
        func_84B01DBC();
    } else {
        func_84B01C2C();
    }

    func_84B01F94();

    if (gBattleContext.unk_1194[0].unk_1C == 1) {
        gBattleContext.unk_11F3 += gBattleGraphics.unk_0002;
        if ((gBattleGraphics.unk_0002 != 0) && (gBattleContext.unk_0003 < 8)) {
            BarStartShrink(&gBattleMenuState.unk_10);
        }

        func_84B0D718(&D_84B25AC0);
        func_84B0BC6C(&D_84B25A90, gBattleGraphics.unk_0008);

        while (D_84B25A90.unk_00 != 3) {
            func_84B01AA0();
        }

        if (gBattleContext.unk_0003 == 8) {
            for (i = 0; i < 120; i++) {
                func_84B01AA0();
                if (BTN_IS_PRESSED(gPlayer1Controller, BTN_A)) {
                    break;
                }
            }

            Battle_SavePokemonNames();
            Battle_IncrementPlayerName();
            Battle_SetProgressFlags();
            Battle_UpdateStageProgress();
            GbsCommitBankBlock(0x14, 0);
            GbsSyncBank(2);
            func_84B0204C();
            func_84B021FC();
            func_84B01994();
            gBattleContext.unk_11F6 |= 3;
        } else if (func_84B022A0() == 1) {
            func_84B0204C();
            func_84B021FC();
            gBattleContext.unk_11F6 |= 0x41;
        } else {
            func_84B0204C();
            Music_StopTrack(0x50);
            gBattleContext.unk_0003++;
            sp2C = 1;
        }
    } else {
        var_s2 = 1;
        while (var_s2 != 0) {
            func_84B0F950(&gBattleMenuState.unk_1C, 7);
            func_84B0F950(&gBattleMenuState.unk_28, 3);

            var_v0 = func_84B0FADC(&gBattleMenuState.unk_28);
            while (var_v0 == -1) {
                func_84B01AA0();
                var_v0 = func_84B0FADC(&gBattleMenuState.unk_28);
            }

            switch (var_v0) {
                case 0:
                    sp2C = 1;
                    gBattleContext.unk_11F3--;
                    var_s2 = 0;
                    break;

                case 1:
                    if (func_84B023C0() != 0) {
                        var_s2 = 0;
                        gBattleContext.unk_11F6 |= 0x41;
                    }
                    break;

                case 2:
                    var_s2 = 0;
                    gBattleContext.unk_11F6 |= 0x21;
                    break;

                case 3:
                    var_s2 = 0;
                    gBattleContext.unk_11F6 |= 0x801;
                    break;

                case 4:
                    var_s2 = 0;
                    gBattleContext.unk_11F6 |= 1;
                    break;
            }
        }

        if (sp2C == 4) {
            func_84B0D718(&D_84B25AC0);
            func_84B0204C();
            func_84B021FC();
        } else {
            func_84B02188();
            Battle_ResetGraphNodes();
        }
    }

    return sp2C;
}

s32 func_84B02984(void) {
    s32 sp28;
    s32 i;
    s32 sp24 = 4;
    s32 var_v0;

    func_84B01C2C();
    func_84B01F94();

    if (gBattleContext.unk_1194[0].unk_1C == 1) {
        if ((gBattleContext.unk_0003 == 4) || (gBattleContext.unk_0002 == 9)) {
            Battle_SetProgressFlags();
            Battle_UpdateStageProgress();
            Battle_SavePokemonNames();
            GbsCommitBankBlock(0x14, 0);
            GbsSyncBank(2);

            for (i = 0; i < 60; i++) {
                func_84B01AA0();
                if (BTN_IS_PRESSED(gPlayer1Controller, BTN_A)) {
                    break;
                }
            }

            func_84B0D718(&D_84B25AC0);
            PlayUISfx(0x0110000D, 0, 0);
            func_84B0204C();
            Music_StopTrack(0x10);

            gBattleContext.unk_11F6 |= 1;
            if (gBattleContext.unk_0002 == 8) {
                gBattleContext.unk_11F6 |= 0x400;
            }

            if (gBattleContext.unk_0002 == 9) {
                gBattleContext.unk_11F6 |= 0x200;
            } else {
                gBattleContext.unk_11F6 |= 0x100;
            }
            sp24 = 3;
        } else if (func_84B022A0() == 1) {
            func_84B0D718(&D_84B25AC0);
            PlayUISfx(0x0110000D, 0, 0);
            func_84B0204C();
            func_84B021FC();
            gBattleContext.unk_11F6 |= 0x41;
        } else {
            func_84B0D718(&D_84B25AC0);
            PlayUISfx(0x0110000D, 0, 0);
            func_84B0204C();
            Music_StopTrack(0x50);
            gBattleContext.unk_0003++;
            sp24 = 1;
        }
    } else {
        func_84B0F950(&gBattleMenuState.unk_1C, 8);
        func_84B0F950(&gBattleMenuState.unk_28, 4);

        var_v0 = func_84B0FADC(&gBattleMenuState.unk_28);
        while (var_v0 == -1) {
            func_84B01AA0();
            var_v0 = func_84B0FADC(&gBattleMenuState.unk_28);
        }

        switch (var_v0) {
            case 0:
                gBattleContext.unk_11F6 |= 0x21;
                break;

            case 1:
                gBattleContext.unk_11F6 |= 0x801;
                break;

            case 2:
                gBattleContext.unk_11F6 |= 1;
                break;
        }

        func_84B0D718(&D_84B25AC0);
        func_84B0204C();
        func_84B021FC();

        if (gBattleContext.unk_0002 == 9) {
            gBattleContext.unk_0002 = 8;
        }
    }
    return sp24;
}

s32 func_84B02C40(void) {
    s32 var_v0;
    u16 sp2A;

    func_84B01C2C();
    if (gBattleContext.unk_1194[0].unk_1C == 1) {
        s32 tmp1 = !!(gBattleProgress.unk_00 & 0x100);

        if ((gBattleContext.unk_11F2 == 0) & !tmp1) {
            GbsGetPlayerMoney(&sp2A);
            sp2A |= 4;
            GbsSetPlayerMoney(&sp2A);
        }

        Battle_SetProgressFlags();
        GbsCommitBankBlock(0x14, 0);
        GbsSyncBank(2);
        func_84B0D718(&D_84B26080);
        func_84B0D718(&D_84B25AC0);
        PlayUISfx(0x0110000D, 0, 0);
        func_84B0204C();
        func_84B021FC();
        gBattleContext.unk_11F6 |= 5;
    } else {
        func_84B0F950(&gBattleMenuState.unk_28, 6);

        var_v0 = func_84B0FADC(&gBattleMenuState.unk_28);
        while (var_v0 == -1) {
            func_84B01AA0();
            var_v0 = func_84B0FADC(&gBattleMenuState.unk_28);
        }

        switch (var_v0) {
            case 0:
                gBattleContext.unk_11F6 |= 0x21;
                break;

            case 1:
                gBattleContext.unk_11F6 |= 1;
                break;
        }

        func_84B0D718(&D_84B26080);
        func_84B0D718(&D_84B25AC0);
        PlayUISfx(0x0110000D, 0, 0);
        func_84B0204C();
        func_84B021FC();
    }
    return 4;
}

u8 func_84B02DF8(void) {
    s32 i;
    u8 var_v1 = 0;

    if ((gBattleContext.unk_0000 > 0) && (gBattleContext.unk_0000 < 7)) {
        if (gBattleContext.unk_1194[0].unk_1C == 1) {
            var_v1 = 1;
            for (i = 0; i < 3; i++) {
                if (gBattleContext.unk_1194[0].unk_08[0]->unk_01C[i].unk_02 == 0) {
                    var_v1 = 0;
                }
            }
        }
    }

    return var_v1;
}

s32 func_84B02E5C(void) {
    s32 var_v0;

    gBattleGraphics.unk_0002 = func_84B02DF8();
    func_84B01B40();

    switch (gBattleContext.unk_0000) {
        case 0:
            var_v0 = func_84B02474();
            break;

        case 1:
            var_v0 = func_84B02654();
            break;

        case 2:
            var_v0 = func_84B02654();
            break;

        case 3:
            var_v0 = func_84B02654();
            break;

        case 4:
            var_v0 = func_84B02654();
            break;

        case 5:
            var_v0 = func_84B02654();
            break;

        case 6:
            var_v0 = func_84B02654();
            break;

        case 7:
            var_v0 = func_84B02984();
            break;

        case 8:
            var_v0 = func_84B02C40();
            break;

        case 9:
            var_v0 = func_84B025D0();
            break;

        case 10:
            var_v0 = func_84B025D0();
            break;
    }
    return var_v0;
}

s32 func_84B02F60(void) {
    s32 i;
    s32 var_s1;

    if (gBattleContext.unk_0002 == 9) {
        var_s1 = 0x3C;
    } else {
        var_s1 = 0x4B;
    }

    func_84B05728(&D_84B259A8);
    func_84B050AC(&D_84B259A8, &gBattleGraphics.unk_0008[0x10]);
    Music_ChangeTrack(0x3F);

    for (i = 0; i < var_s1; i++) {
        Game_UpdateInputs();
        func_84B03814(gInputBuffer);
        func_84B04A7C(&D_84B259A8);
        Battle_BeginFrame();
    }

    Stage_SetFillColor(1);
    Stage_FadeOut(0x10);

    for (i = 0; i < 18; i++) {
        Game_UpdateInputs();
        func_84B03814(gInputBuffer);
        func_84B04A7C(&D_84B259A8);
        Battle_BeginFrame();
    }

    return 4;
}

void func_84B03064(void) {
    MemoryBlock* temp_v0;
    CameraStruct* ptr;
    Fragment2_1GraphNode* ptr2;
    s32 i;

    gBattleGraphics.unk_0001 = 0;
    gBattleGraphics.unk_0003 = 0;
    if (gBattleContext.unk_1194[0].unk_1C == gBattleContext.unk_1194[1].unk_1C) {
        gBattleGraphics.unk_0003 = 1;
    } else if (gBattleContext.unk_1194[0].unk_1C == 1) {
        gBattleGraphics.unk_0001 = 1;
    }

    Graph_InitRoots();

    for (i = 0, ptr2 = &gBattleGraphics.unk_0008[0]; i < 128; ptr2++, i++) {
        Graph_AddToRootList0(ptr2);
        gBattleGraphics.unk_0008[i].unk_0A6 = i;
    }

    temp_v0 = state_pool_try_init(main_pool_get_available(), 0);
    gBattleGraphics.unk_0004 = process_geo_layout(temp_v0, &gGeoLayoutCommands);
    mem_pool_resize_block(temp_v0);

    ptr = gBattleGraphics.unk_0004->unk_0C;
    ptr->unk_24.near = 10.0f;
    ptr->unk_24.far = 6000.0f;

    func_84B038F8(&gInputBuffer);
    func_84B0FACC(&gBattleMenuState.unk_1C);
    func_84B0FACC(&gBattleMenuState.unk_28);
}

s32 Battle_Run(s32 arg0, UNUSED s32 arg1) {
    Stage* sp2C;

    main_pool_push_state('EYEC');
    GbsEnsureBankLoaded(2);
    func_80027FA0(&gBattleProgress, gBattleContext.unk_11F2);
    Gfx_InitBuffers(0x18000, 0);
    sp2C = Stage_Create(0, 1, 3, 1, 2, 1);
    Text_Init(0x17, 0);

    ASSET_LOAD(D_1000000, common_menu1_ui, 0);
    ASSET_LOAD(D_2000000, badge_ui, 0);
    ASSET_LOAD(D_3000000, common_menu0_ui, 0);

    MessageBank_Init();
    D_84B26678 = GetMessageBank(0x1B);
    SpriteAssets_Load();

    gBattleGraphics.unk_B408 = Asset_Load2(0x898000, NULL, 1, 1);
    gBattleGraphics.unk_B40C = ASSET_LOAD2(battle_portraits, 1, 1);

    Stage_Set(sp2C);
    func_84B03064();

    while (arg0 < 4) {
        main_pool_push_state('eye0');

        switch (arg0) {
            case 0:
                arg0 = Battle_MainLoop();
                break;

            case 1:
                arg0 = func_84B017AC();
                break;

            case 2:
                arg0 = func_84B02E5C();
                break;

            case 3:
                arg0 = func_84B02F60();
                break;
        }

        main_pool_pop_state('eye0');
    }

    Stage_Destroy();
    FontManager_Free();
    Gfx_FreeBuffers();

    main_pool_pop_state('EYEC');

    return 0;
}
