#include "fragment41.h"
#include "src/17300.h"
#include "src/19840.h"
#include "src/1AB70.h"
#include "src/1C720.h"
#include "src/1CF30.h"
#include "src/22630.h"
#include "src/232C0.h"
#include "src/2E110.h"
#include "src/49790.h"
#include "src/6BC0.h"
#include "src/math_util.h"
#include "src/memory.h"
#include "src/stage_loader.h"

static unk_D_82F21140 D_82F21140;
static FramebufferImage* gMenuFramebuffer;
static unk_D_82F21160 gMenuPanels[2];
static unk_D_82F211A0 D_82F211A0[2];
static unk_D_82F21238 gScreenTransition;

void Gfx_DrawScisTextureRect(s16 arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5, s16 arg6, s16 arg7, s32 arg8) {
    gSPScisTextureRectangle(gDisplayListHead++, arg0 << 2, arg1 << 2, (arg0 + arg2) << 2, (arg1 + arg3) << 2, 0, arg4,
                            arg5, arg6, arg7);
}

void MenuBar_ResetState(void) {
    unk_D_82F211A0* var_v1;
    s32 i;

    for (i = 0, var_v1 = &D_82F211A0[0]; i < 2; i++, var_v1++) {
        var_v1->unk_00 = 0;
    }
}

void MenuBar_SetState(s32 arg0, s16 arg1) {
    s32 i;
    unk_D_82F211A0* temp_v0 = &D_82F211A0[arg0];

    temp_v0->unk_00 = arg1;

    switch (arg1) {
        case 1:
            temp_v0->unk_02 = (arg0 * 0x5A) + 0xFA;
            temp_v0->unk_04 = 0x5A;
            temp_v0->unk_06 = 0x28;
            temp_v0->unk_0C = 0;
            temp_v0->unk_0E = 0;

            for (i = 0; i < 10; i++) {
                temp_v0->unk_10[i].unk_00 = temp_v0->unk_10[i].unk_02 = 0;
                temp_v0->unk_10[i].unk_04 = 0;
            }
            break;

        case 2:
            temp_v0->unk_06 = 0x1E;
            temp_v0->unk_0A = 0;
            temp_v0->unk_0C = 0xFF;
            break;

        case 3:
            temp_v0->unk_06 = 0;
            temp_v0->unk_0A = 0;
            temp_v0->unk_08 = 0;
            temp_v0->unk_0C = 0xFF;
            break;
    }
}

void MenuBar_UpdateFade(unk_D_82F211A0* arg0) {
    arg0->unk_06--;
    arg0->unk_0C = 0xFF - ((arg0->unk_06 * 0xFF) / 40);
    if (arg0->unk_06 <= 0) {
        MenuBar_SetState(arg0 - D_82F211A0, 2);
    }
}

void MenuBar_UpdatePulse(unk_D_82F211A0* arg0) {
    s32 sp1C;

    if (arg0->unk_06 > 0) {
        arg0->unk_06--;
    }

    arg0->unk_0A += 0x200;

    arg0->unk_0C = ROUND_MAX(((COSS(arg0->unk_0A) * 0.5f) + 0.5f) * 255.0f);

    if ((arg0->unk_06 <= 0) && (arg0->unk_0C >= 0xFF)) {
        sp1C = arg0 - D_82F211A0;
        MenuBar_SetState(sp1C, 3);
        if (sp1C == 0) {
            PlaySoundEffect(0x01200006);
        }
    }
}

void MenuBar_AddParticle(unk_D_82F211A0* arg0) {
    s32 i;
    unk_D_82F211A0_010* var_v0 = NULL;

    for (i = 0; i < 10; i++) {
        if (arg0->unk_10[i].unk_04 == 0) {
            break;
        }
    }

    if (i < 10) {
        var_v0 = &arg0->unk_10[i];
    }

    if (var_v0 != NULL) {
        var_v0->unk_00 = arg0->unk_02;
        var_v0->unk_02 = arg0->unk_04;
        var_v0->unk_04 = 0x14;
        arg0->unk_0E++;
    }
}

void MenuBar_UpdateParticles(unk_D_82F211A0* arg0) {
    s32 i;
    unk_D_82F211A0_010* ptr;

    for (i = 0, ptr = &arg0->unk_10[0]; i < 10; i++, ptr++) {
        if (ptr->unk_04 != 0) {
            ptr->unk_04--;
            if (ptr->unk_04 <= 0) {
                arg0->unk_0E--;
            }
        }
    }
}

void MenuBar_UpdateSlide(unk_D_82F211A0* arg0) {
    s32 idx = arg0 - D_82F211A0;

    if (arg0->unk_0E > 0) {
        MenuBar_UpdateParticles(arg0);
    }

    if ((arg0->unk_02 < 0xA0) || (arg0->unk_02 >= 0x1C3)) {
        if (arg0->unk_0E == 0) {
            arg0->unk_00 = 0;
            MenuPanel_SetState(idx ^ 1, 6);
        }
    } else {
        if (arg0->unk_06 > 0) {
            arg0->unk_06--;
        }

        if ((arg0->unk_06 == 0) && (arg0->unk_0E < 0xA)) {
            MenuBar_AddParticle(arg0);
            arg0->unk_06 = 2;
        }

        if (idx != 0) {
            arg0->unk_08--;
        } else {
            arg0->unk_08++;
        }

        arg0->unk_02 += arg0->unk_08;
    }
}

void MenuBar_ProcessAll(void) {
    s32 i;
    unk_D_82F211A0* var_s0 = &D_82F211A0[0];

    for (i = 0; i < 2; i++, var_s0++) {
        switch (var_s0->unk_00) {
            case 1:
                MenuBar_UpdateFade(var_s0);
                break;

            case 2:
                MenuBar_UpdatePulse(var_s0);
                break;

            case 3:
                MenuBar_UpdateSlide(var_s0);
                break;
        }
    }
}

void MenuBar_Render(void) {
    s32 i;
    s32 j;
    s32 sp84 = 0;
    s16 var_s0;
    u16* temp_s0;
    unk_D_82F211A0* var_s4;
    s16 v;
    s16 tmp;

    for (i = 0, var_s4 = &D_82F211A0[0]; i < 2; i++, var_s4++) {
        if (var_s4->unk_00 != 0) {
            temp_s0 = Picker_GetSelectedSprite(i);

            if (sp84 == 0) {
                sp84 = 1;
                Gfx_SetScissorRect(&gDisplayListHead, 0xEC, 0x50, 0xAA, 0x50);
            }

            gDPPipeSync(gDisplayListHead++);

            gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, var_s4->unk_0C);
            gDPLoadTextureBlock(gDisplayListHead++, temp_s0, G_IM_FMT_RGBA, G_IM_SIZ_16b, 40, 40, 0,
                                G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK,
                                G_TX_NOLOD, G_TX_NOLOD);

            v = 60;

            if (var_s4->unk_00 == 1) {
                for (j = 0; j < v; j++) {
                    var_s0 = ((MathUtil_Random16() % 33) * var_s4->unk_06) / 40;
                    if (MathUtil_Random16() & 0x8000) {
                        var_s0 = -var_s0;
                    }
                    Gfx_DrawTextureRect(var_s4->unk_02 + var_s0, var_s4->unk_04 + j, 0x3C, 1, 0,
                                  ROUND_MAX((j * 32.0f) / 1.5f), 0x2AB, 0x2AB, 0);
                }
            } else {
                Gfx_DrawTextureRect(var_s4->unk_02, var_s4->unk_04, 0x3C, 0x3C, 0, 0, 0x2AB, 0x2AB, 0);
            }

            if (var_s4->unk_0E == 0) {
            } else {
                for (j = 0; j < 10; j++) {
                    if (var_s4->unk_10[j].unk_04 == 0) {
                        continue;
                    }

                    tmp = (var_s4->unk_10[j].unk_04 * 0xFF) / 20;

                    gDPPipeSync(gDisplayListHead++);
                    gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, tmp);

                    Gfx_DrawTextureRect(var_s4->unk_10[j].unk_00, var_s4->unk_10[j].unk_02, 0x3C, 0x3C, 0, 0, 0x2AB, 0x2AB,
                                  0);
                }
            }
        }
    }

    if (sp84 != 0) {
        Gfx_SetScissorRect(&gDisplayListHead, 0, 0, 0x280, 0x1E0);
    }
}

void ScreenTransition_Reset(void) {
    gScreenTransition.unk_02 = 0;
}

void ScreenTransition_Init(unk_D_82F21238* arg0, s32 arg1) {
    arg0->unk_28 = AssetManager_Create(1);
    arg0->unk_2C = PokeIcon_CreateModelPreview(arg0->unk_28, 0xC0, 0xC0, 0, 0, 0xC0, 0xC0, NULL);
    arg0->unk_2C->unk_00 &= ~2;
    PokeIcon_SetPreviewMon(arg0->unk_2C, arg0->unk_24, 1);

    if (arg1 != 0) {
        arg0->unk_06 = 2;
        arg0->unk_2C->unk_00 &= ~4;
    } else {
        arg0->unk_06 = 1;
        arg0->unk_2C->unk_00 |= 4;
    }
    GraphNode_TriggerAction(arg0->unk_2C->unk_24, arg0->unk_06);
}

void ScreenTransition_Start(s16 arg0) {
    unk_func_82F00838_sp30 sp20;
    unk_D_82F21238* ptr = &gScreenTransition;

    main_pool_push_state('intr');
    Picker_GetSelectionInfo(arg0, &sp20);
    gScreenTransition.unk_00 = arg0;
    gScreenTransition.unk_02 = 1;
    gScreenTransition.unk_04 = sp20.unk_02;
    gScreenTransition.unk_06 = 1;
    gScreenTransition.unk_08 = 0;
    ptr->unk_0A = MathUtil_Random16() % 2;
    ptr->unk_0C = 0;
    ptr->unk_0E = 0x140;
    ptr->unk_10 = 0xC4;
    ptr->unk_12 = 0;
    ptr->unk_14 = 0;
    ptr->unk_16 = 0xFF;
    ptr->unk_20 = 0;
    ptr->unk_24 = &sp20.unk_0C[sp20.unk_06];
    ScreenTransition_Init(&gScreenTransition, 0);
    ptr->unk_30.unk_00 = ptr->unk_30.unk_02 = 0;
    ptr->unk_30.unk_04 = ptr->unk_30.unk_06 = -1;

    PlaySoundEffect(4);
    SaveSlot_SetPokemonOwned(ptr->unk_04, ptr->unk_24->unk_00.unk_00, 3);
}

void ScreenTransition_UpdateAnim(unk_D_82F21238* arg0) {
    Fragment2_1GraphNode* sp24 = arg0->unk_2C->unk_24;

    if ((Anim_HasReachedEnd(sp24) != 0) && (arg0->unk_06 == 2)) {
        arg0->unk_06 = 1;
        arg0->unk_2C->unk_00 |= 4;
        GraphNode_TriggerAction(sp24, arg0->unk_06);
    }
    arg0->unk_20 = PokeIcon_RenderPreview(arg0->unk_2C);
}

void ScreenTransition_Expand(unk_D_82F21238* arg0) {
    if (arg0->unk_12 < 0xC0) {
        arg0->unk_12 += 0x20;
        if (arg0->unk_12 >= 0xC1) {
            arg0->unk_12 = 0xC0;
        }
    } else {
        arg0->unk_14 += 0x20;
        if (arg0->unk_14 >= 0xC1) {
            arg0->unk_14 = 0xC0;
        }
    }

    arg0->unk_0E = ((arg0->unk_12 * -0x60) / 192) + 0x140;
    arg0->unk_10 = ((arg0->unk_14 * -0x60) / 192) + 0xC4;

    ScreenTransition_UpdateAnim(arg0);

    if ((arg0->unk_12 == 0xC0) && (arg0->unk_14 == 0xC0)) {
        arg0->unk_02 = 2;
        arg0->unk_0C = 0;
        arg0->unk_0E = 0xE0;
        arg0->unk_10 = 0x64;
    }
}

s32 IsSpecialPokemonId(s32 arg0) {
    s32 var_v1 = 0;

    if ((arg0 == 0x40) || (arg0 == 0x43) || (arg0 == 0x4B) || (arg0 == 0x5D)) {
        var_v1 = 1;
    }
    return var_v1;
}

void ScreenTransition_HandleInput(unk_D_82F21238* arg0) {
    ScreenTransition_UpdateAnim(arg0);

    if (arg0->unk_08 != 0) {
        arg0->unk_0C -= 1;
        if (arg0->unk_0C <= 0) {
            arg0->unk_0C = 0;
        } else {
            return;
        }
    }

    if (BTN_IS_PRESSED(gPlayer1Controller, BTN_A)) {
        if (IsSpecialPokemonId(arg0->unk_24->unk_00.unk_00) != 0) {
            arg0->unk_02 = 3;
            arg0->unk_08 = 1;
            arg0->unk_0C = 0x3C;
            arg0->unk_18 = 0;
            arg0->unk_1A = 0x800;
            arg0->unk_1C = 0;
            PlaySoundEffect(2);
            PlaySoundEffect(0x01200007);
        } else {
            arg0->unk_02 = 6;
            arg0->unk_0C = 0xA;
            if (arg0->unk_08 != 0) {
                PlaySoundEffect(0x01200009);
            } else {
                PlaySoundEffect(2);
            }
        }
    }
}

void ScreenTransition_Shrink(unk_D_82F21238* arg0) {
    arg0->unk_0C--;
    ScreenTransition_UpdateAnim(arg0);
    arg0->unk_16 = (arg0->unk_0C * 0xFF) / 60;

    switch (arg0->unk_0A) {
        case 1:
            break;

        case 0:
            arg0->unk_1C = ((0x3C - arg0->unk_0C) * 0xF0) / 60;
            arg0->unk_1A = 0x1000 - ((arg0->unk_0C << 0xB) / 60);
            arg0->unk_18 += 0x1000;
            break;
    }

    if (arg0->unk_0C <= 0) {
        arg0->unk_02 = 4;
        arg0->unk_0C = 1;
        arg0->unk_16 = 0;
        arg0->unk_20 = 0;
    }
}

s32 MessageString_Equals(s16 arg0, s8* arg1) {
    s32 sp64;
    s8* var_v1;
    char sp20[64];

    sp64 = 1;
    StrCopy(sp20, GetMessageStringBank24(arg0));

    var_v1 = sp20;
    while (*var_v1 != '\x00') {
        if (*var_v1 != *arg1) {
            sp64 = 0;
            break;
        }
        var_v1++;
        arg1++;
    }

    return sp64;
}

void PokemonData_UpdateNameIfSpecial(s16 arg0, PokemonData* arg1) {
    s16 sp2E = 0;

    if (IsSpecialPokemonId(arg1->unk_00.unk_00) != 0) {
        sp2E = arg1->unk_00.unk_00;
        arg1->unk_00.unk_00++;
    }

    if (sp2E != 0) {
        if (MessageString_Equals(sp2E, arg1->unk_30) != 0) {
            StrCopy(arg1->unk_30, GetMessageStringBank24(arg1->unk_00.unk_00));
        }
        CalculatePokemonStats(arg1);
        SaveSlot_SetPokemonOwned(arg0, arg1->unk_00.unk_00, 3);
    }
}

void ScreenTransition_ApplyPokemonUpdate(unk_D_82F21238* arg0) {
    arg0->unk_0C--;
    if (arg0->unk_0C <= 0) {
        main_pool_pop_state('intr');
        main_pool_push_state('intr');

        arg0->unk_02 = 5;
        arg0->unk_0C = 0x3C;
        arg0->unk_16 = 0;
        if (arg0->unk_0A == 0) {
            arg0->unk_1C = 0xF0;
        }
        arg0->unk_20 = 0;
        PokemonData_UpdateNameIfSpecial(arg0->unk_04, arg0->unk_24);
        Picker_SetSelectedSprite(arg0->unk_00, arg0->unk_24);
        ScreenTransition_Init(arg0, 1);
        arg0->unk_30.unk_00 = 0x38;
        arg0->unk_30.unk_02 = 0x168;
        arg0->unk_30.unk_04 = 0x210;
        arg0->unk_30.unk_06 = 0;
        PlaySoundEffect(0x01200008);
    }
}

void ScreenTransition_ShrinkReverse(unk_D_82F21238* arg0) {
    s16 var_v1;
    unk_D_82F20A40_00E* ptr = &arg0->unk_30;

    ScreenTransition_UpdateAnim(arg0);
    arg0->unk_0C--;
    arg0->unk_16 = ((0x3C - arg0->unk_0C) * 0xFF) / 60;

    switch (arg0->unk_0A) {
        case 1:
            break;

        case 0:
            arg0->unk_1C = (arg0->unk_0C * 0xF0) / 60;
            arg0->unk_1A = 0x800 - ((arg0->unk_0C * -0x800) / 60);
            arg0->unk_18 += 0x1000;
            break;
    }

    var_v1 = arg0->unk_0C;
    if (var_v1 >= 0xB) {
        var_v1 = 0xA;
    }

    ptr->unk_00 = 0x38 - (var_v1 * 0) / 10;
    ptr->unk_02 = 0x154 - ((var_v1 * -0x14) / 10);
    ptr->unk_04 = 0x210 - (var_v1 * 0) / 10;
    ptr->unk_06 = 0x28 - ((var_v1 * 0x28) / 10);

    if (arg0->unk_0C <= 0) {
        arg0->unk_02 = 2;
        arg0->unk_0C = 0x5A;
        arg0->unk_16 = 0xFF;
    }
}

void ScreenTransition_Collapse(unk_D_82F21238* arg0) {
    unk_D_82F20A40_00E* temp_v0_2 = &arg0->unk_30;

    if (arg0->unk_0C > 0) {
        arg0->unk_0C--;
    }

    if (arg0->unk_30.unk_04 != -1) {
        temp_v0_2->unk_00 = 0x38 - ((arg0->unk_0C * 0) / 10);
        temp_v0_2->unk_02 = 0x168 - ((arg0->unk_0C * 0x14) / 10);
        temp_v0_2->unk_04 = 0x210 - ((arg0->unk_0C * 0) / 10);
        temp_v0_2->unk_06 = -((arg0->unk_0C * -0x28) / 10);
    }

    if (arg0->unk_14 > 0) {
        arg0->unk_14 -= 0x20;
        if (arg0->unk_14 < 0) {
            arg0->unk_14 = 0;
        }
    } else {
        arg0->unk_12 -= 0x20;
        if (arg0->unk_12 < 0) {
            arg0->unk_12 = 0;
        }
    }

    arg0->unk_0E = ((arg0->unk_12 * -0x60) / 192) + 0x140;
    arg0->unk_10 = ((arg0->unk_14 * -0x60) / 192) + 0xC4;
    ScreenTransition_UpdateAnim(arg0);

    if ((arg0->unk_12 == 0) && (arg0->unk_14 == 0)) {
        if (arg0->unk_0C <= 0) {
            arg0->unk_02 = 0;
            arg0->unk_0C = 0;
            arg0->unk_20 = 0;

            temp_v0_2->unk_00 = temp_v0_2->unk_02 = 0;
            temp_v0_2->unk_04 = temp_v0_2->unk_06 = -1;

            main_pool_pop_state('intr');
        }
    }
}

void ScreenTransition_Process(void) {
    switch (gScreenTransition.unk_02) {
        case 0:
            break;

        case 1:
            ScreenTransition_Expand(&gScreenTransition);
            break;

        case 2:
            ScreenTransition_HandleInput(&gScreenTransition);
            break;

        case 3:
            ScreenTransition_Shrink(&gScreenTransition);
            break;

        case 4:
            ScreenTransition_ApplyPokemonUpdate(&gScreenTransition);
            break;

        case 5:
            ScreenTransition_ShrinkReverse(&gScreenTransition);
            break;

        case 6:
            ScreenTransition_Collapse(&gScreenTransition);
            break;
    }
}

void DrawTransitionOverlay(s16 arg0, s16 arg1, s16 arg2) {
    static Gfx D_82F13F90[] = {
        gsDPPipeSync(),
        gsDPSetCycleType(G_CYC_2CYCLE),
        gsDPSetRenderMode(G_RM_PASS, G_RM_XLU_SURF2),
        gsDPSetCombineLERP(TEXEL0, TEXEL1, PRIM_LOD_FRAC, TEXEL1, TEXEL0, TEXEL1, PRIM_LOD_FRAC, TEXEL1, PRIMITIVE,
                           ENVIRONMENT, COMBINED, ENVIRONMENT, COMBINED, 0, PRIMITIVE, ENVIRONMENT),
        gsDPSetPrimColor(0, 0x80, 0, 0, 255, 0),
        gsSPEndDisplayList(),
    };
    static f32 D_82F13FC0 = 0.0f;
    static f32 D_82F13FC4 = 0.0f;
    static f32 D_82F13FC8 = 0.0f;
    static f32 D_82F13FCC = 0.0f;

    UNUSED s32 pad[2];
    f32 temp_fa0;
    f32 temp_fa4;
    f32 temp_fa8;
    f32 temp_faC;

    gSPDisplayList(gDisplayListHead++, D_82F13F90);
    gDPSetEnvColor(gDisplayListHead++, 0, 0, 50, (arg2 << 7) / 255);

    gDPLoadMultiBlock_4b(gDisplayListHead++, D_3026368, 0x0100, 1, G_IM_FMT_I, 32, 32, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, 5, 5, 1, G_TX_NOLOD);
    temp_fa0 = D_82F13FC0 + 31.0f;
    temp_fa4 = D_82F13FC4 + 31.0f;
    gDPSetTileSize(gDisplayListHead++, 1, D_82F13FC0 * 4.0f, D_82F13FC4 * 4.0f, temp_fa0 * 4.0f, temp_fa4 * 4.0f);

    gDPLoadTextureBlock_4b(gDisplayListHead++, D_3026168, G_IM_FMT_I, 32, 32, 0, G_TX_NOMIRROR | G_TX_WRAP,
                           G_TX_NOMIRROR | G_TX_WRAP, 5, 5, G_TX_NOLOD, 1);
    temp_fa8 = D_82F13FC8 + 31.0f;
    temp_faC = D_82F13FCC + 31.0f;
    gDPSetTileSize(gDisplayListHead++, G_TX_RENDERTILE, D_82F13FC8 * 4.0f, D_82F13FCC * 4.0f, temp_fa8 * 4.0f,
                   temp_faC * 4.0f);

    Gfx_DrawScisTextureRect(arg0, arg1, 0xC0, 0xC0, 0, 0, 0xAB, 0xAB, 0x100000);

    D_82F13FC0 -= 0.25f;
    if (D_82F13FC0 < 0.0f) {
        D_82F13FC0 += 32.0f;
    }

    D_82F13FC4 -= 0.25f;
    if (D_82F13FC4 < 0.0f) {
        D_82F13FC4 += 32.0f;
    }

    D_82F13FC8 += 0.25f;
    if (D_82F13FC8 >= 32.0f) {
        D_82F13FC8 -= 32.0f;
    }

    D_82F13FCC -= 0.5f;
    if (D_82F13FCC < 0.0f) {
        D_82F13FCC += 32.0f;
    }
}

void DrawMenuPanelBorder(s16 arg0, s16 arg1, s16 arg2, s16 arg3) {
    s16 tmp = (arg1 + (arg3 / 2)) - 8;

    gSPDisplayList(gDisplayListHead++, gPrefDL_Border);

    Gfx_DrawSpriteRGBA16(arg0 - 0xD, arg1 - 0xD, 0x10, 0x10, D_3026568, 0x10, 0);
    Gfx_DrawTextureRect(arg0 - 0xD, arg1 + 3, 0x10, (arg3 / 2) - 3, 0, 0x1E0, 0x400, 0, 0);
    Gfx_DrawSpriteRGBA16((arg0 + arg2) - 3, arg1 - 0xD, 0x10, 0x10, D_3026768, 0x10, 0);
    Gfx_DrawTextureRect(arg0 + 3, arg1 - 0xD, arg2 - 6, 0x10, 0, 0, 0, 0x400, 0);
    Gfx_DrawTextureRect((arg0 + arg2) - 3, arg1 + 3, 0x10, (arg3 / 2) - 3, 0, 0x1E0, 0x400, 0, 0);
    Gfx_DrawSpriteRGBA16(arg0 - 0xD, (arg1 + arg3) - 3, 0x10, 0x10, D_3026D68, 0x10, 0);

    Gfx_DrawTextureRect(arg0 - 0xD, tmp + 8, 0x10, (arg3 / 2) - 3, 0, 0, 0x400, 0, 0);
    Gfx_DrawSpriteRGBA16((arg0 + arg2) - 3, (arg1 + arg3) - 3, 0x10, 0x10, D_3026F68, 0x10, 0);
    Gfx_DrawTextureRect(arg0 + 3, (arg1 + arg3) - 3, arg2 - 6, 0x10, 0, 0, 0, 0x400, 0);
    Gfx_DrawTextureRect((arg0 + arg2) - 3, tmp + 8, 0x10, (arg3 / 2) - 3, 0, 0, 0x400, 0, 0);

    if (arg3 >= 0x10) {
        Gfx_DrawSpriteRGBA16(arg0 - 0xD, tmp, 0x10, 0x10, D_3026968, 0x10, 0);
        Gfx_DrawSpriteRGBA16((arg0 + arg2) - 3, tmp, 0x10, 0x10, D_3026B68, 0x10, 0);
    }

    gSPDisplayList(gDisplayListHead++, gPrefDL_End);
}

void DrawTransitionImage(unk_D_82F21238* arg0) {
    UNUSED s32 pad;
    s16 i;
    s32 sp5C;
    s16 var_a0;
    s16 var_s2;
    s16 var_s3;

    sp5C = 0;
    if (arg0->unk_0A == 1) {
        sp5C = 1;
    }

    gSPDisplayList(gDisplayListHead++, gPrefDL_Border);
    gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, arg0->unk_16);

    if (sp5C != 0) {
        gDPSetAlphaCompare(gDisplayListHead++, G_AC_DITHER);
    }

    var_s3 = 8;
    if ((arg0->unk_02 == 3) || (arg0->unk_02 == 5)) {
        var_s3 = 1;
    }

    for (i = 0; i < 0xC0; i += var_s3) {
        var_s2 = CLAMP_MIN(0xC0 - i, var_s3);

        gDPLoadTextureTile(gDisplayListHead++, arg0->unk_20 + (i * 0x180), G_IM_FMT_RGBA, G_IM_SIZ_16b, 192, 0, 0, 0,
                           191, var_s2 - 1, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK,
                           G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

        if (var_s3 != 1) {
            var_a0 = 0xE0;
        } else {
            var_a0 = (s16)(SINS(arg0->unk_18 + (arg0->unk_1A * i)) * arg0->unk_1C) + 0xE0;
        }
        Gfx_DrawTextureRect(var_a0, i + 0x64, 0xC0, var_s2, 0, 0, 0x400, 0x400, 0);
    }

    if (sp5C != 0) {
        gDPPipeSync(gDisplayListHead++);
        gDPSetAlphaCompare(gDisplayListHead++, G_AC_NONE);
    }
}

void func_82F0ECA4(void) {
}

void DrawTransitionText(unk_D_82F20A40_00E* arg0, PokemonData* arg1) {
    s16 spC6;
    s8 sp44[0x80];
    char* sp40;
    char* sp3C;
    char* sp38;
    s16 tmp1;

    sp44[0] = '\x00';
    sp3C = NULL;
    sp40 = NULL;

    if (IsSpecialPokemonId(arg1->unk_00.unk_00 - 1) != 0) {
        sp40 = GetMessageStringBank24(arg1->unk_00.unk_00 - 1);
        sp3C = GetMessageStringBank24(arg1->unk_00.unk_00);
    }

    if (sp40 != NULL) {
        MessageBank_SetPointer_0x14_0x2A(0x21, sp40);
        MessageBank_SetPointer_0x14_0x2A(0x22, sp3C);
        sp38 = GetMessageString(sp44, 0x80, D_82F13B70, 0x19);
    }

    if ((sp44[0] != '\x00') && ((arg0->unk_04 != 0x210) || (arg0->unk_06 != 0))) {
        Picker_DrawLargePanelBorder(arg0->unk_00, arg0->unk_02, arg0->unk_04, arg0->unk_06, 0x1E, 0x1E, 0x82, 0xFF);
        if ((arg0->unk_04 == 0x210) && (arg0->unk_06 == 0x28)) {
            Text_ResetState();
            Text_SetFont(0x10, 0);
            Text_SetEnvColor(0xFF, 0xFF, 0xFF, 0xFF);
            spC6 = arg0->unk_00 + (arg0->unk_04 / 2);
            tmp1 = MeasureTextWidth(0, 0, sp38) / 2;
            Text_Print(spC6 - tmp1, arg0->unk_02 + 8, sp38);
            Text_SetupDL();
        }
    }
}

void ScreenTransition_Render(void) {
    unk_D_82F21238* ptr = &gScreenTransition;
    UNUSED s32 pad;
    s32 sp24;

    if (ptr->unk_02 != 0) {
        sp24 = 0;
        if (ptr->unk_12 > 0) {
            if (ptr->unk_14 > 0) {
                sp24 = 1;
                Gfx_SetScissorRect(&gDisplayListHead, ptr->unk_0E, ptr->unk_10, ptr->unk_12, ptr->unk_14);
                if (ptr->unk_20 != 0) {
                    DrawTransitionImage(&gScreenTransition);
                }
                DrawTransitionOverlay(0xE0, 0x64, ptr->unk_16);
            }
        }

        if (sp24 != 0) {
            Gfx_SetScissorRect(&gDisplayListHead, 0, 0, 0x280, 0x1E0);
        }

        DrawMenuPanelBorder(ptr->unk_0E, ptr->unk_10, ptr->unk_12, ptr->unk_14);

        if (ptr->unk_30.unk_04 != -1) {
            DrawTransitionText(&ptr->unk_30, ptr->unk_24);
        }
    }
}

void MenuPanel_ResetState(void) {
    s32 i;
    unk_D_82F21160* var_v1;

    for (i = 0, var_v1 = &gMenuPanels[0]; i < 2; i++, var_v1++) {
        var_v1->unk_00 = 0;
        var_v1->unk_02 = 0;
        var_v1->unk_04 = 0;
        var_v1->unk_06 = 0;
        var_v1->unk_08 = 0;
        var_v1->unk_0A = 0;
        var_v1->unk_0C = 0;
        var_v1->unk_0E = 0;
        var_v1->unk_10 = 0;
        var_v1->unk_12 = 0;
        var_v1->unk_14 = 0.0f;
        var_v1->unk_18 = 0.0f;
        var_v1->unk_1C = 0.0f;
    }
}

void MenuPanel_SetState(s32 arg0, s16 arg1) {
    static s16 D_82F13FD0[] = { 0x64, 0x2C8 };
    static s16 D_82F13FD4[] = { 0x50, 0x236, 0, 0, 0x3F80, 0 };

    unk_D_82F21160* temp_v0 = &gMenuPanels[arg0];

    temp_v0->unk_00 = arg1;

    switch (arg1) {
        case 1:
            temp_v0->unk_02 = D_82F13FD0[arg0];
            temp_v0->unk_04 = D_82F21140.unk_02 + temp_v0->unk_02;
            temp_v0->unk_06 = 0xFA;
            temp_v0->unk_08 = temp_v0->unk_04 - 0x40;
            temp_v0->unk_0A = 0xAE;
            temp_v0->unk_0C = 0x80;
            temp_v0->unk_0E = 0x48;
            temp_v0->unk_10 = 0;
            temp_v0->unk_12 = 0;
            temp_v0->unk_14 = 1.0f;
            temp_v0->unk_18 = 0.0f;
            temp_v0->unk_1C = 9.0f;
            break;

        case 2:
            temp_v0->unk_08 = 0;
            temp_v0->unk_0A = 0;
            temp_v0->unk_0C = 0;
            temp_v0->unk_0E = 0;
            temp_v0->unk_06 = 0xBE;
            break;

        case 3:
            temp_v0->unk_08 = 0;
            temp_v0->unk_0A = 0;
            temp_v0->unk_0C = 0;
            temp_v0->unk_0E = 0;
            temp_v0->unk_10 = D_82F21140.unk_18;
            break;

        case 4:
            if (arg0 == 0) {
                temp_v0->unk_02 = 0x50;
            } else {
                temp_v0->unk_02 = 0x236;
            }
            temp_v0->unk_04 = D_82F21140.unk_02 + temp_v0->unk_02;
            temp_v0->unk_14 = 0.75f;
            break;

        case 5:
            temp_v0->unk_12 = 0;
            temp_v0->unk_08 = temp_v0->unk_04 - 0x40;
            if (temp_v0->unk_08 < 0) {
                temp_v0->unk_08 = 0;
            }
            temp_v0->unk_0A = 0xC2;
            temp_v0->unk_0C = 0x80;
            temp_v0->unk_0E = 0x3C;
            break;

        case 6:
            temp_v0->unk_02 = D_82F13FD4[arg0];
            temp_v0->unk_04 = D_82F21140.unk_02 + temp_v0->unk_02;
            temp_v0->unk_06 = 0xA0;
            temp_v0->unk_08 = temp_v0->unk_04 - 0x40;
            if (temp_v0->unk_08 < 0) {
                temp_v0->unk_08 = 0;
            }
            temp_v0->unk_0A = 0xC2;
            temp_v0->unk_0C = 0x80;
            temp_v0->unk_0E = 0x3C;
            temp_v0->unk_10 = 0;
            temp_v0->unk_12 = 0;
            temp_v0->unk_14 = 0.75f;
            temp_v0->unk_18 = 0.0f;
            temp_v0->unk_1C = 1.0f;
            break;

        case 8:
            temp_v0->unk_02 = D_82F13FD4[arg0];
            temp_v0->unk_04 = D_82F21140.unk_02 + temp_v0->unk_02;
            temp_v0->unk_06 = 0xA0;
            temp_v0->unk_08 = temp_v0->unk_04 - 0x40;
            if (temp_v0->unk_08 < 0) {
                temp_v0->unk_08 = 0;
            }
            temp_v0->unk_0A = 0xC2;
            temp_v0->unk_0C = 0x80;
            temp_v0->unk_0E = 0x3C;
            temp_v0->unk_10 = 0;
            temp_v0->unk_12 = 0;
            temp_v0->unk_14 = 0.75f;
            temp_v0->unk_18 = 0.0f;
            temp_v0->unk_1C = 1.0f;
            break;
    }
}

void MenuPanel_UpdateFade(unk_D_82F21160* arg0) {
    arg0->unk_06 -= 2;
    if (arg0->unk_06 < 0xBF) {
        MenuPanel_SetState(arg0 - gMenuPanels, 2);
    }
}

void MenuPanel_UpdatePulse(unk_D_82F21160* arg0) {
    arg0->unk_04 = D_82F21140.unk_02 + arg0->unk_02;
    arg0->unk_06 = (s16)ROUND_MAX(SINS(arg0->unk_12) * 3.0f) + 0xBE;

    arg0->unk_12 += 0x800;

    arg0->unk_1C -= 0.2f;
    if (arg0->unk_1C < 1.0f) {
        arg0->unk_1C = 1.0f;
    }
}

void MenuPanel_UpdateExpand(unk_D_82F21160* arg0) {
    f32 one = 1.0f;
    s16 var_v0;
    s16 tmp1;
    s32 temp_a1;
    s32 temp_a3;
    f32 tmpf1;

    var_v0 = D_82F21140.unk_18;
    if (arg0->unk_10 < var_v0) {
        var_v0 = 0;
    }
    temp_a1 = (var_v0 * -0x14);

    temp_a3 = arg0 - gMenuPanels;
    if (temp_a3 == 0) {
        arg0->unk_02 = ((var_v0 * 0x14) / arg0->unk_10) + 0x50;
    } else {
        arg0->unk_02 = ((var_v0 * 0x92) / arg0->unk_10) + 0x236;
    }

    arg0->unk_04 = D_82F21140.unk_02 + arg0->unk_02;

    tmp1 = (temp_a1 / arg0->unk_10) + 0xD2;
    tmpf1 = (((var_v0 * one) / arg0->unk_10) + 2.0f);

    arg0->unk_06 = (s16)ROUND_MAX(SINS(arg0->unk_12) * tmpf1) + tmp1;

    arg0->unk_12 += 0x800;
    arg0->unk_14 = ((var_v0 * 0.25f) / arg0->unk_10) + 0.75f;

    if (temp_a1 >= -0x13) {
        MenuPanel_SetState(temp_a3, 4);
    }
}

void MenuPanel_UpdateBounce(unk_D_82F21160* arg0) {
    arg0->unk_04 = D_82F21140.unk_02 + arg0->unk_02;
    arg0->unk_06 = (s16)ROUND_MAX(2.0f * SINS(arg0->unk_12)) + 0xD2;
    arg0->unk_12 += 0x800;
}

void MenuPanel_SlideOut(unk_D_82F21160* arg0) {
    arg0->unk_04 = D_82F21140.unk_02 + arg0->unk_02;
    arg0->unk_12--;
    arg0->unk_06 += arg0->unk_12;
    if (arg0->unk_06 < 0x79) {
        arg0->unk_00 = 0;
        arg0->unk_06 = 0x78;
    }
}

void MenuPanel_SlideIn(unk_D_82F21160* arg0) {
    s16 idx;

    arg0->unk_12++;
    arg0->unk_06 += arg0->unk_12;
    if (arg0->unk_06 >= 0xD2) {
        arg0->unk_00 = 7;
        arg0->unk_06 = 0xD2;
        arg0->unk_18 = MathUtil_Random16() % 16;
        arg0->unk_12 = MathUtil_Random16();
        idx = arg0 - gMenuPanels;
        if (idx == 0) {
            D_82F21140.unk_0C &= ~0x40;
        }
    }
}

void MenuPanel_BounceLoop(unk_D_82F21160* arg0) {
    arg0->unk_04 = D_82F21140.unk_02 + arg0->unk_02;
    arg0->unk_06 = (s16)ROUND_MAX(2.0f * SINS(arg0->unk_12)) + 0xD2;
    arg0->unk_12 += 0x800;
}

void MenuPanel_ShrinkOut(unk_D_82F21160* arg0) {
    if (arg0->unk_1C < 9.0f) {
        arg0->unk_04 = D_82F21140.unk_02 + arg0->unk_02;
        arg0->unk_06 = (s16)ROUND_MAX(2.0f * SINS(arg0->unk_12)) + 0xD2;
        arg0->unk_12 += 0x800;

        arg0->unk_1C += 0.2f;
        if (arg0->unk_1C >= 9.0f) {
            arg0->unk_1C = 9.0f;
        }
    } else {
        arg0->unk_1C = 9.0f;
        arg0->unk_06 += 2;
        if (arg0->unk_06 >= 0x104) {
            arg0->unk_00 = 0;
            arg0->unk_06 = 0;
        }
    }
}

void MenuPanel_ProcessAll(void) {
    s32 var_s1;
    unk_D_82F21160* var_s0;
    s32 i;

    var_s0 = gMenuPanels;

    for (i = 0; i < 2; i++, var_s0++) {
        var_s1 = 1;

        switch (var_s0->unk_00) {
            case 0:
                var_s1 = 0;
                break;

            case 1:
                MenuPanel_UpdateFade(var_s0);
                break;

            case 2:
                MenuPanel_UpdatePulse(var_s0);
                break;

            case 3:
                MenuPanel_UpdateExpand(var_s0);
                break;

            case 4:
                MenuPanel_UpdateBounce(var_s0);
                break;

            case 5:
                MenuPanel_SlideOut(var_s0);
                break;

            case 6:
                MenuPanel_SlideIn(var_s0);
                break;

            case 7:
                MenuPanel_BounceLoop(var_s0);
                break;

            case 8:
                MenuPanel_ShrinkOut(var_s0);
                break;
        }

        if (var_s1 != 0) {
            s32 tmp;

            var_s0->unk_18 += var_s0->unk_1C;

            tmp = var_s0->unk_18;
            tmp /= 16;

            var_s0->unk_18 -= (tmp * 0x10);
        }
    }
}

void DrawMenuPanel(s16 arg0, s16 arg1, f32 arg2, s16 arg3) {
    static u8* D_82F13FE0[] = {
        D_300D868, D_300EA68, D_300FC68, D_3010E68, D_3012068, D_3013268, D_3013268, D_3013268,
        D_3013268, D_3013268, D_3013268, D_3013268, D_3012068, D_3010E68, D_300FC68, D_300EA68,
    };

    s32 i;
    s16 var_fv0_4;
    s16 sp60;
    s16 sp5E;
    s16 sp5C;
    f32 var_fv0;
    u8* var_s2;

    if ((arg0 < 0x281) && (arg0 >= -0x30) && (arg1 < 0x1E1)) {
        sp60 = 0;
        if (arg1 >= -0x30) {
            var_fv0 = arg2;
            if ((arg3 >= 0xC) && (arg3 < 0x10)) {
                sp60 = 0x600;
                var_fv0 = 0.0f - arg2;
            }

            sp5E = ROUND_MAX(1024.0f / var_fv0);
            sp5C = ROUND_MAX(1024.0f / arg2);
            var_fv0_4 = ROUND_MAX(24.0f * arg2);

            var_s2 = D_82F13FE0[arg3];
            for (i = 0; i < 2; i++) {
                gDPLoadTextureBlock(gDisplayListHead++, var_s2, G_IM_FMT_RGBA, G_IM_SIZ_16b, 48, 24, 0,
                                    G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK,
                                    G_TX_NOLOD, G_TX_NOLOD);

                Gfx_DrawScisTextureRect(arg0, arg1 + (var_fv0_4 * i), 0x30, 0x18, sp60, 0, sp5E, sp5C, 0);
                var_s2 += 0x900;
            }
        }
    }
}

void MenuPanel_RenderAll(void) {
    s32 i;
    s32 var_s3 = 0;
    unk_D_82F21160* var_s0;

    for (i = 0, var_s0 = gMenuPanels; i < 2; i++, var_s0++) {
        if (var_s0->unk_00 == 0) {
            continue;
        }

        if ((var_s0->unk_0C != 0) && (var_s0->unk_0E != 0)) {
            var_s3 = 1;
            var_s0->unk_08 = var_s0->unk_04 - 0x40;
            if (var_s0->unk_08 < 0) {
                var_s0->unk_08 = 0;
            }
            Gfx_SetScissorRect(&gDisplayListHead, var_s0->unk_08, var_s0->unk_0A, var_s0->unk_0C, var_s0->unk_0E);
        }

        DrawMenuPanel(var_s0->unk_04, var_s0->unk_06, var_s0->unk_14, var_s0->unk_18);
    }

    if (var_s3 != 0) {
        Gfx_SetScissorRect(&gDisplayListHead, 0, 0, 0x280, 0x1E0);
    }
}

s32 MenuPanel_IsAnimating(void) {
    s32 var_v1 = 0;

    if (D_82F21140.unk_0E != 0) {
        var_v1 = 1;
    }
    return var_v1;
}

void MenuPanel_SetMainState(s16 arg0) {
    UNUSED s32 pad;
    unk_D_82F21140* ptr = &D_82F21140;
    unk_D_82F21160* ptr2;
    s32 i;
    u16 tmp = 0;

    if (arg0 < 0x12) {
        ptr->unk_00 = arg0;
    }

    switch (arg0) {
        case 0:
            ptr->unk_02 = -0x14;
            ptr->unk_04 = 0x18;
            ptr->unk_10 = 1.5f;
            ptr->unk_06 = 0xB4;
            ptr->unk_08 = 0xE4;
            ptr->unk_0A = 0xAA;
            ptr->unk_0E = -1;
            ptr->unk_14 = 0x80;
            ptr->unk_16 = 0x40;
            ptr->unk_0C = tmp;
            ptr->unk_0C |= 0x1F;
            break;

        case 1:
            ptr->unk_18 = 0x1E;
            ptr->unk_0C |= 0x20;
            PlaySoundEffect(0x01200002);
            break;

        case 2:
        case 4:
            ptr->unk_18 = 0xA;
            break;

        case 3:
            ptr->unk_18 = 2;
            break;

        case 6:
            ptr->unk_18 = 0xA;
            break;

        case 7:
            ptr->unk_18 = 2;
            break;

        case 8:
        case 9:
            ptr->unk_18 = 0xA;

            ptr2 = &gMenuPanels[0];
            for (i = 0; i < 2; i++, ptr2++) {
                if (ptr2->unk_00 != 0) {
                    MenuPanel_SetState(i, 3);
                }
            }
            break;

        case 11:
            MenuPanel_SetState(0, 8);
            MenuPanel_SetState(1, 8);
            break;

        case 12:
            ptr->unk_18 = 0xA;
            break;

        case 14:
            ptr->unk_18 = 0xA;
            break;

        case 16:
            ptr->unk_18 = 0xA;
            break;

        case 5:
        case 17:
            ptr->unk_18 = 0x1E;
            break;

        case 19:
            MenuPanel_SetState(0, 1);
            PlaySoundEffect(0x01200004);
            break;

        case 20:
            MenuPanel_SetState(1, 1);
            PlaySoundEffect(0x01200004);
            break;

        case 21:
            if (1) {}
            if (1) {}
            MenuPanel_SetState(0, 5);
            MenuPanel_SetState(1, 5);
            break;
    }
}

void MenuPanel_UpdateState(unk_D_82F21140* arg0) {
    if (Trade_GetBoxMachineFlowState() != 0) {
        switch (Trade_GetBoxMachineFlowState()) {
            case 1:
            case 11:
                arg0->unk_0E = -1;
                arg0->unk_0C |= 0x1E;
                break;

            default:
                arg0->unk_0C &= ~0x1E;
                break;
        }
    } else if (Trade_GetSaveSeqState() != 0) {
        switch (Trade_GetSaveSeqState()) {
            case 1:
            case 8:
                arg0->unk_0E = -1;
                arg0->unk_0C |= 0x1E;
                break;

            default:
                arg0->unk_0C &= ~0x1E;
                break;
        }
    } else {
        arg0->unk_0E = -1;
        arg0->unk_0C |= 0x1E;
    }
}

void MenuPanel_AnimateIntro(unk_D_82F21140* arg0) {
    arg0->unk_18--;
    arg0->unk_14 = ((arg0->unk_18 * 0x60) / 30) + 0x20;
    arg0->unk_16 = ((arg0->unk_18 * -0x40) / 30) + 0x80;
    if (arg0->unk_18 <= 0) {
        MenuPanel_SetMainState(2);
    }
}

void MenuPanel_AnimateSlide(unk_D_82F21140* arg0) {
    s16 var_v0;

    arg0->unk_18--;
    var_v0 = arg0->unk_18;
    if (arg0->unk_00 == 4) {
        var_v0 = 0xA - var_v0;
    }

    arg0->unk_02 = ((var_v0 * -0xAE) / 10) + 0x9A;
    arg0->unk_04 = ((var_v0 * 0x43) / 10) - 0x2B;
    arg0->unk_10 = ((var_v0 * -0.39999998f) / 10) + 1.9f;
    arg0->unk_0A = ((var_v0 * 3) / 10) + 0xA7;

    if (arg0->unk_18 <= 0) {
        if (arg0->unk_00 == 4) {
            MenuPanel_SetMainState(5);
        } else {
            MenuPanel_SetMainState(3);
        }
    }
}

void MenuPanel_AnimateWait(unk_D_82F21140* arg0) {
    if (arg0->unk_18 > 0) {
        arg0->unk_18--;
    }

    switch (GetPickerState()) {
        case 3:
            break;

        case 2:
        case 4:
            if (arg0->unk_0E == -1) {
                arg0->unk_0E = 2;
            }
            arg0->unk_0C &= ~1;
            break;

        case 1:
            arg0->unk_0C &= ~0x1E;
            break;

        default:
            arg0->unk_0E = -1;
            arg0->unk_0C |= 0x1F;
            break;
    }

    if (MenuPanel_CheckState(4) != 0) {
        MenuPanel_SetMainState(6);
    }
}

void MenuPanel_AnimateExit(unk_D_82F21140* arg0) {
    arg0->unk_18--;
    arg0->unk_02 = ((arg0->unk_18 * 0x1F8) / 10) - 0x15E;
    if (arg0->unk_18 <= 0) {
        MenuPanel_SetMainState(7);
    }
}

void MenuPanel_AnimateWait2(unk_D_82F21140* arg0) {
    if (arg0->unk_18 > 0) {
        arg0->unk_18--;
    }

    switch (GetPickerState()) {
        case 3:
            break;

        case 2:
        case 4:
            if (arg0->unk_0E == -1) {
                arg0->unk_0E = 2;
            }
            arg0->unk_0C &= ~1;
            break;

        case 1:
            arg0->unk_0C &= ~0x1E;
            break;

        default:
            arg0->unk_0E = -1;
            arg0->unk_0C |= 0x1F;
            break;
    }

    if (MenuPanel_CheckState(5) != 0) {
        MenuPanel_SetMainState(9);
    }
}

void MenuPanel_AnimateSlideOut(unk_D_82F21140* arg0) {
    arg0->unk_18--;
    arg0->unk_02 = ((arg0->unk_18 * -0x14A) / 10) - 0x14;
    arg0->unk_04 = ((arg0->unk_18 * -0x43) / 10) + 0x18;
    arg0->unk_10 = ((arg0->unk_18 * 0.39999998f) / 10.0f) + 1.5f;
    arg0->unk_0A = ((arg0->unk_18 * -3) / 10) + 0xAA;

    if (arg0->unk_18 <= 0) {
        if (arg0->unk_00 == 8) {
            MenuPanel_SetMainState(5);
        } else {
            MenuPanel_SetMainState(0xA);
        }
    }
}

void MenuPanel_HandleBarConfirm(unk_D_82F21140* arg0) {
    if (Trade_GetSaveSeqState() == 2) {
        arg0->unk_0C &= ~0x10;
        arg0->unk_0C &= ~2;
    } else {
        arg0->unk_0C |= 0x12;
    }

    if (MenuPanel_CheckState(7) != 0) {
        if (!(arg0->unk_0C & 0x40)) {
            arg0->unk_0C |= 0x40;
            MenuBar_SetState(0, 1);
            MenuBar_SetState(1, 1);
            PlaySoundEffect(0x01200005);
        }
    }
}

void MenuPanel_WaitForBarConfirm(unk_D_82F21140* arg0) {
    if (MenuPanel_CheckState(7) != 0) {
        MenuPanel_SetMainState(5);
    }
}

void MenuPanel_AnimateFadeOutLeft(unk_D_82F21140* arg0) {
    s16 var_v1 = arg0->unk_18;

    arg0->unk_18--;
    if (var_v1 < 0) {
        var_v1 = 0;
    }

    arg0->unk_02 = ((var_v1 * -0x1E4) / 10) + 0x1D0;
    arg0->unk_04 = ((var_v1 * 0) / 10) + 0x18;
    if (arg0->unk_18 < -5) {
        MenuPanel_SetMainState(0xD);
        ScreenTransition_Start(0);
    }
}

void MenuPanel_WaitForScreenTransitionLeft(unk_D_82F21140* arg0) {
    if (MenuPanel_CheckState(0xB) != 0) {
        MenuPanel_SetMainState(0xE);
    }
}

void MenuPanel_AnimateFadeOutRight(unk_D_82F21140* arg0) {
    s16 var_v1 = arg0->unk_18;

    arg0->unk_18--;
    if (var_v1 < 0) {
        var_v1 = 0;
    }

    arg0->unk_02 = ((var_v1 * 0x3A0) / 10) - 0x1D0;
    arg0->unk_04 = ((var_v1 * 0) / 10) + 0x18;
    if (arg0->unk_18 < -5) {
        MenuPanel_SetMainState(0xF);
        ScreenTransition_Start(1);
    }
}

void MenuPanel_WaitForScreenTransitionRight(unk_D_82F21140* arg0) {
    if (MenuPanel_CheckState(0xB) != 0) {
        MenuPanel_SetMainState(0x10);
    }
}

void MenuPanel_AnimateExitDown(unk_D_82F21140* arg0) {
    arg0->unk_18--;
    arg0->unk_02 = ((arg0->unk_18 * -0x1BC) / 10) - 0x14;
    arg0->unk_04 = ((arg0->unk_18 * 0) / 10) + 0x18;
    if (arg0->unk_18 <= 0) {
        MenuPanel_SetMainState(0x11);
        MenuPanel_SetState(0, 8);
        MenuPanel_SetState(1, 8);
    }
}

void MenuPanel_AnimateOutro(unk_D_82F21140* arg0) {
    s32 i;

    if (arg0->unk_00 == 5) {
        for (i = 0; i < 2; i++) {
            if (gMenuPanels[i].unk_00 == 4) {
                MenuPanel_SetState(i, 8);
            }
        }

        if ((gMenuPanels->unk_00 != 0) || (gMenuPanels[1].unk_00 != 0)) {
            return;
        }
    } else if ((arg0->unk_00 == 0x11) && (MenuPanel_CheckState(9) == 0)) {
        return;
    }

    if (arg0->unk_0C & 0x20) {
        arg0->unk_0C &= ~0x20;
        PlaySoundEffect(0x01200003);
    }

    arg0->unk_18--;
    arg0->unk_14 = ((arg0->unk_18 * -0x60) / 30) + 0x80;
    arg0->unk_16 = ((arg0->unk_18 << 6) / 30) + 0x40;
    if (arg0->unk_18 <= 0) {
        MenuPanel_SetMainState(0);
    }
}

void MenuPanel_DrawMainBG(s16 arg0, s16 arg1, f32 arg2) {
    s16 sp58;
    s16 temp_ft1;
    s16 temp_ft2;
    s32 temp_ft0;
    s32 i;
    u8* var_s6 = D_3000008;

    temp_ft2 = ROUND_MAX(228.0f * arg2);
    temp_ft1 = ROUND_MAX(19.0f * arg2);
    temp_ft0 = ROUND_MAX(1024.0f / arg2);
    sp58 = ROUND_MAX(-1024.0f / arg2);

    for (i = 0; i < 11; i++, var_s6 += 0x876) {
        gDPLoadTextureTile_4b(gDisplayListHead++, var_s6, G_IM_FMT_I, 228, 0, 0, 0, 227, 18, 0,
                              G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK,
                              G_TX_NOLOD, G_TX_NOLOD);

        Gfx_DrawScisTextureRect(arg0, arg1 + i * temp_ft1, temp_ft2, temp_ft1, 0, 0, temp_ft0, temp_ft0, 0);
        Gfx_DrawScisTextureRect(arg0 + temp_ft2, arg1 + i * temp_ft1, temp_ft2, temp_ft1, 0x1C60, 0, sp58, temp_ft0, 0);
    }
}

void MenuPanel_DrawLargeButton(s16 arg0, s16 arg1, f32 arg2, s16 arg3, s16 arg4, s16 arg5) {
    s16 sp6E;
    s16 sp6C;
    s16 sp6A;
    s16 sp68;
    s16 sp66;
    s32 temp_fv1_4;
    s32 sp5C;

    sp6E = ROUND_MAX(48.0f * arg2);
    sp6C = ROUND_MAX(30.0f * arg2);
    sp6A = ROUND_MAX(arg3 * arg2);
    sp68 = ROUND_MAX(arg4 * arg2);
    sp66 = ROUND_MAX(arg5 * arg2);
    sp5C = ROUND_MAX(1024.0f / arg2);
    temp_fv1_4 = ROUND_MAX(-1024.0f / arg2);

    gDPLoadTextureTile_4b(gDisplayListHead++, D_3005D28, G_IM_FMT_I, 48, 0, 0, 0, 47, 29, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                          G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

    Gfx_DrawScisTextureRect(arg0 + sp6A, arg1 + sp66, sp6E, sp6C, 0, 0, sp5C, sp5C, 0);
    Gfx_DrawScisTextureRect(arg0 + sp68, arg1 + sp66, sp6E, sp6C, 0x5E0, 0, temp_fv1_4, sp5C, 0);
}

void MenuPanel_DrawMediumButton(s16 arg0, s16 arg1, f32 arg2, s16 arg3, s16 arg4, s16 arg5) {
    s16 sp6E;
    s16 sp6C;
    s16 sp6A;
    s16 sp68;
    s16 sp66;
    s32 temp_fv1_4;
    s32 sp5C;

    sp6E = ROUND_MAX(24.0f * arg2);
    sp6C = ROUND_MAX(30.0f * arg2);
    sp6A = ROUND_MAX(arg3 * arg2);
    sp68 = ROUND_MAX(arg4 * arg2);
    sp66 = ROUND_MAX(arg5 * arg2);
    sp5C = ROUND_MAX(1024.0f / arg2);
    temp_fv1_4 = ROUND_MAX(-1024.0f / arg2);

    gDPLoadTextureTile_4b(gDisplayListHead++, D_300D108, G_IM_FMT_I, 24, 0, 0, 0, 23, 29, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                          G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

    Gfx_DrawScisTextureRect(arg0 + sp6A, arg1 + sp66, sp6E, sp6C, 0, 0, sp5C, sp5C, 0);
    Gfx_DrawScisTextureRect(arg0 + sp68, arg1 + sp66, sp6E, sp6C, 0x2E0, 0, temp_fv1_4, sp5C, 0);
}

void MenuPanel_DrawSmallButton(s16 arg0, s16 arg1, f32 arg2, s16 arg3, s16 arg4, s16 arg5) {
    s16 sp6E;
    s16 sp6C;
    s16 sp6A;
    s16 sp68;
    s16 sp66;
    s32 temp_fv1_4;
    s32 sp5C;

    sp6E = ROUND_MAX(16.0f * arg2);
    sp6C = ROUND_MAX(14.0f * arg2);
    sp6A = ROUND_MAX(arg3 * arg2);
    sp68 = ROUND_MAX(arg4 * arg2);
    sp66 = ROUND_MAX(arg5 * arg2);
    sp5C = ROUND_MAX(1024.0f / arg2);
    temp_fv1_4 = ROUND_MAX(-1024.0f / arg2);

    gDPLoadTextureTile_4b(gDisplayListHead++, D_300D278, G_IM_FMT_I, 16, 0, 0, 0, 15, 13, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                          G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

    Gfx_DrawScisTextureRect(arg0 + sp6A, arg1 + sp66, sp6E, sp6C, 0, 0, sp5C, sp5C, 0);
    Gfx_DrawScisTextureRect(arg0 + sp68, arg1 + sp66, sp6E, sp6C, 0x1E0, 0, temp_fv1_4, sp5C, 0);
}

void MenuPanel_DrawTallBar(s16 arg0, s16 arg1, f32 arg2, s16 arg3, s16 arg4, s16 arg5) {
    s16 spB6;
    s16 i;
    s32 sp60;
    u8* var_s5;
    s16 temp_fa0;
    s16 temp_fa0_2;
    s16 temp_fv1_2;
    s16 var_s4;
    s16 var_t3;
    s16 temp_ft0;
    s32 temp_ft1;

    spB6 = ROUND_MAX(100.0f * arg2);
    temp_fa0 = ROUND_MAX(arg3 * arg2);
    temp_fv1_2 = ROUND_MAX(arg4 * arg2);
    temp_fa0_2 = ROUND_MAX(arg5 * arg2);
    temp_ft1 = ROUND_MAX(1024.0f / arg2);
    sp60 = ROUND_MAX(-1024.0f / arg2);

    var_s4 = 0;
    var_s5 = D_3006000;
    var_t3 = 0;
    for (i = 0x83; i > 0;) {
        if ((i - 0x48) >= 0) {
            var_t3 = 0x48;
        } else {
            var_t3 = i;
        }

        gDPLoadTextureTile_4b(gDisplayListHead++, var_s5, G_IM_FMT_I, 100, 0, 0, 0, 99, var_t3, 0,
                              G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK,
                              G_TX_NOLOD, G_TX_NOLOD);

        i -= var_t3;
        temp_ft0 = var_t3 * arg2;
        Gfx_DrawScisTextureRect(arg0 + temp_fa0, arg1 + temp_fa0_2 + var_s4, spB6, temp_ft0, 0, 0, temp_ft1, temp_ft1, 0);
        Gfx_DrawScisTextureRect(arg0 + temp_fv1_2, arg1 + temp_fa0_2 + var_s4, spB6, temp_ft0, 0xC60, 0, sp60, temp_ft1, 0);
        var_s5 += 0xE10;
        var_s4 += temp_ft0;
    }
}

void MenuPanel_DrawTallBarHighlight(s16 arg0, s16 arg1, f32 arg2, s16 arg3, s16 arg4, s16 arg5, s16 arg6) {
    static Gfx gMenuPanelTallBarHighlightDL[] = {
        gsDPPipeSync(),
        gsDPSetCycleType(G_CYC_2CYCLE),
        gsDPSetRenderMode(G_RM_PASS, G_RM_XLU_SURF2),
        gsDPSetCombineLERP(NOISE, 0, TEXEL1, 0, TEXEL0, 0, PRIMITIVE, 0, PRIMITIVE, ENVIRONMENT, COMBINED, ENVIRONMENT,
                           0, 0, 0, COMBINED),
        gsDPSetEnvColor(200, 255, 255, 255),
        gsSPEndDisplayList(),
    };

    s16 spE6;
    s16 i;
    s32 sp6C;
    s32 sp60;
    u8* var_fp;
    u8* var_s7;
    s16 temp_fa0;
    s16 temp_fv1_2;
    s16 temp_fv1_3;
    s16 var_ra;
    s16 var_s6;
    s16 temp_ft0;

    spE6 = ROUND_MAX(100.0f * arg2);
    if (1) {}
    temp_fv1_2 = ROUND_MAX(arg3 * arg2);
    temp_fa0 = ROUND_MAX(arg4 * arg2);
    temp_fv1_3 = ROUND_MAX(arg5 * arg2);
    sp6C = ROUND_MAX(1024.0f / arg2);
    sp60 = ROUND_MAX(-1024.0f / arg2);

    var_s6 = 0;
    var_s7 = D_3009DC8;
    var_fp = D_300B768;
    i = 0x83;

    gSPDisplayList(gDisplayListHead++, gMenuPanelTallBarHighlightDL);
    gDPSetPrimColor(gDisplayListHead++, 0, 0, 100, 100, 255, arg6);

    for (; i > 0;) {
        if ((i - 0x20) >= 0) {
            var_ra = 0x20;
        } else {
            var_ra = i;
        }

        gDPLoadMultiTile_4b(gDisplayListHead++, var_fp, 0x0100, 1, G_IM_FMT_I, 100, 0, 0, 0, 99, var_ra, 0,
                            G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK,
                            G_TX_NOLOD, G_TX_NOLOD);

        i -= var_ra;
        temp_ft0 = var_ra * arg2;

        gDPLoadMultiTile_4b(gDisplayListHead++, var_s7, 0x0000, G_TX_RENDERTILE, G_IM_FMT_I, 100, 0, 0, 0, 99, var_ra,
                            0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK,
                            G_TX_NOLOD, G_TX_NOLOD);

        Gfx_DrawScisTextureRect(arg0 + temp_fv1_2, arg1 + temp_fv1_3 + var_s6, spE6, temp_ft0, 0, 0, sp6C, sp6C, 0x100000);
        Gfx_DrawScisTextureRect(arg0 + temp_fa0, arg1 + temp_fv1_3 + var_s6, spE6, temp_ft0, 0xC60, 0, sp60, sp6C, 0x100000);
        var_s7 += 0x640;
        var_fp += 0x640;
        var_s6 += temp_ft0;
    }
}

void MenuPanel_DrawSquareBG(s16 arg0, s16 arg1, f32 arg2, s16 arg3, s16 arg4, s16 arg5) {
    s16 sp76;
    s16 sp74;
    s16 sp72;
    s16 sp70;
    s16 sp6E;
    UNUSED s32 pad;
    s16 sp5C;
    s32 sp60;

    sp76 = ROUND_MAX(64.0f * arg2);
    sp74 = ROUND_MAX(64.0f * arg2);
    sp72 = ROUND_MAX(arg3 * arg2);
    sp70 = ROUND_MAX(arg4 * arg2);
    sp6E = ROUND_MAX(arg5 * arg2);
    sp60 = ROUND_MAX(1024.0f / arg2);
    sp5C = ROUND_MAX(-1024.0f / arg2);

    gDPLoadTextureTile_4b(gDisplayListHead++, D_30079A0, G_IM_FMT_I, 64, 0, 0, 0, 63, 63, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                          G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

    Gfx_DrawScisTextureRect(arg0 + sp72, arg1 + sp6E, sp76, sp74, 0, 0, sp60, sp60, 0);
    Gfx_DrawScisTextureRect(arg0 + sp70, arg1 + sp6E, sp76, sp74, 0x7E0, 0, sp5C, sp60, 0);
}

void MenuPanel_DrawAnimatedBG(void) {
    static f32 gMenuPanelBGScrollX = 0.0f;
    static f32 gMenuPanelBGScrollY = 0.0f;
    static f32 gMenuPanelBGScrollX2 = 0.0f;
    static f32 gMenuPanelBGScrollY2 = 0.0f;
    static Gfx gMenuPanelBGDL[] = {
        gsDPPipeSync(),
        gsDPSetCycleType(G_CYC_2CYCLE),
        gsDPSetRenderMode(G_RM_OPA_SURF, G_RM_OPA_SURF2),
        gsDPSetCombineLERP(TEXEL0, TEXEL1, PRIM_LOD_FRAC, TEXEL1, 0, 0, 0, PRIMITIVE, PRIMITIVE, ENVIRONMENT, COMBINED,
                           ENVIRONMENT, 0, 0, 0, COMBINED),
        gsDPSetPrimColor(0, 0x80, 55, 255, 255, 255),
        gsDPSetEnvColor(0, 0, 255, 255),
        gsSPEndDisplayList(),
    };

    f32 temp_fa0;
    f32 temp_fa4;
    f32 temp_fa8;
    f32 temp_faC;

    Gfx_SetupFrameBuffer(&gDisplayListHead, gMenuFramebuffer);

    gSPDisplayList(gDisplayListHead++, gMenuPanelBGDL);

    gDPLoadMultiBlock_4b(gDisplayListHead++, D_3009BC0, 0x0100, 1, G_IM_FMT_I, 32, 32, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, 5, 5, G_TX_NOLOD, 1);

    temp_fa8 = gMenuPanelBGScrollX2 + 31.0f;
    temp_faC = gMenuPanelBGScrollY2 + 31.0f;
    if (1) {}
    gDPSetTileSize(gDisplayListHead++, 1, gMenuPanelBGScrollX2 * 4.0f, gMenuPanelBGScrollY2 * 4.0f, temp_fa8 * 4.0f, temp_faC * 4.0f);

    gDPLoadTextureBlock_4b(gDisplayListHead++, D_30099B8, G_IM_FMT_I, 32, 32, 0, G_TX_NOMIRROR | G_TX_WRAP,
                           G_TX_NOMIRROR | G_TX_WRAP, 5, 5, G_TX_NOLOD, 2);

    temp_fa0 = gMenuPanelBGScrollX + 31.0f;
    temp_fa4 = gMenuPanelBGScrollY + 31.0f;
    gDPSetTileSize(gDisplayListHead++, G_TX_RENDERTILE, gMenuPanelBGScrollX * 4.0f, gMenuPanelBGScrollY * 4.0f, temp_fa0 * 4.0f,
                   temp_fa4 * 4.0f);

    Gfx_DrawTextureRect(0, 0, 0x20, 0x20, 0, 0, 0x400, 0x400, 0x100000);

    gMenuPanelBGScrollX += 0.75f;
    if (gMenuPanelBGScrollX >= 32.0f) {
        gMenuPanelBGScrollX -= 32.0f;
    }

    gMenuPanelBGScrollY += 5.75f;
    if (gMenuPanelBGScrollY >= 32.0f) {
        gMenuPanelBGScrollY -= 32.0f;
    }

    gMenuPanelBGScrollY2 -= 2.5f;
    if (gMenuPanelBGScrollY2 < 0.0f) {
        gMenuPanelBGScrollY2 += 32.0f;
    }

    gDPPipeSync(gDisplayListHead++);

    Stage_BeginDisplayList();
}

void MenuPanel_DrawSquareBGWithAlpha(s16 arg0, s16 arg1, f32 arg2, s16 arg3, s16 arg4, s16 arg5) {
    static Gfx gMenuPanelSquareBGAlphaDL[] = {
        gsDPPipeSync(),
        gsDPSetCycleType(G_CYC_2CYCLE),
        gsDPSetRenderMode(G_RM_PASS, G_RM_XLU_SURF2),
        gsDPSetCombineLERP(0, 0, 0, TEXEL1, TEXEL0, 0, ENVIRONMENT, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
        gsDPSetEnvColor(0, 0, 0, 60),
        gsSPEndDisplayList(),
    };

    s16 sp96;
    s16 sp94;
    s16 sp92;
    s16 sp90;
    s16 sp8E;
    UNUSED s32 pad;
    s32 temp_fa0_3;
    s32 sp80;

    MenuPanel_DrawAnimatedBG();

    sp96 = ROUND_MAX(64.0f * arg2);
    sp94 = ROUND_MAX(64.0f * arg2);
    sp92 = ROUND_MAX(arg3 * arg2);
    sp90 = ROUND_MAX(arg4 * arg2);
    sp8E = ROUND_MAX(arg5 * arg2);
    sp80 = ROUND_MAX(1024.0f / arg2);
    temp_fa0_3 = ROUND_MAX(-1024.0f / arg2);

    gSPDisplayList(gDisplayListHead++, gMenuPanelSquareBGAlphaDL);
    gDPLoadMultiBlock(gDisplayListHead++, gMenuFramebuffer->img_p, 0x0100, 1, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, 0,
                      G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, 5, 5, 1, 1);
    gDPLoadTextureBlock_4b(gDisplayListHead++, D_30081A8, G_IM_FMT_I, 64, 64, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                           G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

    Gfx_DrawScisTextureRect(arg0 + sp92, arg1 + sp8E, sp96, sp94, 0, 0, sp80, sp80, 0x100000);
    Gfx_DrawScisTextureRect(arg0 + sp90, arg1 + sp8E, sp96, sp94, 0x7E0, 0, temp_fa0_3, sp80, 0x100000);
}

void MenuPanel_Init(void) {
    MenuPanel_SetMainState(0);
    MenuPanel_ResetState();
    MenuBar_ResetState();
    ScreenTransition_Reset();
    gMenuFramebuffer = FramebufferImage_Allocate(0, 2, 0x20, 0x20, 1);
}

void MenuPanel_Update(void) {
    switch (D_82F21140.unk_00) {
        case 0:
            MenuPanel_UpdateState(&D_82F21140);
            break;

        case 1:
            MenuPanel_AnimateIntro(&D_82F21140);
            break;

        case 2:
        case 4:
            MenuPanel_AnimateSlide(&D_82F21140);
            break;

        case 3:
            MenuPanel_AnimateWait(&D_82F21140);
            break;

        case 6:
            MenuPanel_AnimateExit(&D_82F21140);
            break;

        case 7:
            MenuPanel_AnimateWait2(&D_82F21140);
            break;

        case 8:
        case 9:
            MenuPanel_AnimateSlideOut(&D_82F21140);
            break;

        case 10:
            MenuPanel_HandleBarConfirm(&D_82F21140);
            break;

        case 11:
            MenuPanel_WaitForBarConfirm(&D_82F21140);
            break;

        case 12:
            MenuPanel_AnimateFadeOutLeft(&D_82F21140);
            break;

        case 13:
            MenuPanel_WaitForScreenTransitionLeft(&D_82F21140);
            break;

        case 14:
            MenuPanel_AnimateFadeOutRight(&D_82F21140);
            break;

        case 15:
            MenuPanel_WaitForScreenTransitionRight(&D_82F21140);
            break;

        case 16:
            MenuPanel_AnimateExitDown(&D_82F21140);
            break;

        case 5:
        case 17:
            MenuPanel_AnimateOutro(&D_82F21140);
            break;
    }
    MenuPanel_ProcessAll();
    MenuBar_ProcessAll();
    ScreenTransition_Process();
}

void MenuPanel_Render(void) {
    unk_D_82F21140* ptr = &D_82F21140;
    u8 sp83;
    s32 var_v0_2;
    s32 tmp1;

    if (ptr->unk_0E > 0) {
        ptr->unk_0E--;
    }

    gSPDisplayList(gDisplayListHead++, gPrefDL_Border);
    gDPSetRenderMode(gDisplayListHead++, G_RM_OPA_SURF, G_RM_OPA_SURF2);
    gDPSetEnvColor(gDisplayListHead++, ptr->unk_14, ptr->unk_14, ptr->unk_14, 255);

    MenuPanel_DrawMainBG(ptr->unk_02, ptr->unk_04, ptr->unk_10);
    tmp1 = gFragment41FrameCounter & 0x3F;
    sp83 = (ptr->unk_16 * tmp1) / 63u;
    if (gFragment41FrameCounter & 0x40) {
        sp83 = ptr->unk_16 - sp83;
    }

    if (ptr->unk_0C & 1) {
        if (GetTextBoxState() == 1) {
            tmp1 = gFragment41FrameCounter & 3;
            sp83 = (tmp1 * 0xFF) / 3u;
            if (gFragment41FrameCounter & 4) {
                sp83 = 0xFF - sp83;
            }
        }
    }

    gDPPipeSync(gDisplayListHead++);
    gDPSetRenderMode(gDisplayListHead++, G_RM_XLU_SURF, G_RM_XLU_SURF2);

    if (ptr->unk_0C & 0x10) {
        gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, sp83);
        MenuPanel_DrawLargeButton(ptr->unk_02, ptr->unk_04, ptr->unk_10, ptr->unk_06, ptr->unk_08, ptr->unk_0A);
    }

    gDPPipeSync(gDisplayListHead++);
    gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255);

    MenuPanel_RenderAll();
    MenuBar_Render();

    tmp1 = gFragment41FrameCounter & 0x3F;
    sp83 = (tmp1 * 0xFF) / 63u;
    if (gFragment41FrameCounter & 0x40) {
        sp83 = 0xFF - sp83;
    }

    gDPPipeSync(gDisplayListHead++);
    gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, sp83);

    tmp1 = gFragment41FrameCounter & 0x3F;
    sp83 = ((tmp1) << 7) / 63u;
    if (gFragment41FrameCounter & 0x40) {
        sp83 = 0x80 - sp83;
    }

    gDPPipeSync(gDisplayListHead++);
    gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, sp83);

    if (ptr->unk_0C & 2) {
        MenuPanel_DrawMediumButton(ptr->unk_02, ptr->unk_04, ptr->unk_10, 0xB4, 0xFA, 0x73);
    }

    if (ptr->unk_0C & 4) {
        MenuPanel_DrawSmallButton(ptr->unk_02, ptr->unk_04, ptr->unk_10, 0xD4, 0xE4, 2);
    }

    if (ptr->unk_0C & 4) {
        if (ptr->unk_0C & 0x40) {
            var_v0_2 = 0x64;
        } else {
            var_v0_2 = 0x32;
        }
        MenuPanel_DrawTallBarHighlight(ptr->unk_02, ptr->unk_04, ptr->unk_10, 0x81, 0xE5, 0, var_v0_2);

        gSPDisplayList(gDisplayListHead++, gPrefDL_Border);
        gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, sp83);

        if (!(ptr->unk_0C & 0x40)) {
            MenuPanel_DrawTallBar(ptr->unk_02, ptr->unk_04, ptr->unk_10, 0x81, 0xE5, 0);
        }
    }

    if (ptr->unk_0C & 8) {
        if (ptr->unk_0C & 0x20) {
            MenuPanel_DrawSquareBGWithAlpha(ptr->unk_02, ptr->unk_04, ptr->unk_10, 0x23, 0x164, 0x68);
        } else {
            MenuPanel_DrawSquareBG(ptr->unk_02, ptr->unk_04, ptr->unk_10, 0x23, 0x164, 0x68);
        }
    }

    ScreenTransition_Render();
    gSPDisplayList(gDisplayListHead++, gPrefDL_End);
}

s32 MenuPanel_CheckState(s16 arg0) {
    unk_D_82F21160* ptr = &gMenuPanels[0];
    s32 var_v1 = 0;

    switch (arg0) {
        case 1:
            if ((D_82F21140.unk_00 == 3) && (D_82F21140.unk_18 == 0)) {
                var_v1 = 1;
            }
            break;

        case 2:
            if ((D_82F21140.unk_00 == 7) && (D_82F21140.unk_18 == 0)) {
                var_v1 = 1;
            }
            break;

        case 3:
            if (D_82F21140.unk_00 == 0) {
                var_v1 = 1;
            }
            break;

        case 4:
            if ((gMenuPanels[0].unk_00 == 2) && (ptr[0].unk_1C <= 1.0f)) {
                var_v1 = 1;
            }
            break;

        case 5:
            if ((gMenuPanels[1].unk_00 == 2) && (ptr[1].unk_1C <= 1.0f)) {
                var_v1 = 1;
            }
            break;

        case 6:
            if (D_82F21140.unk_00 == 0xA) {
                var_v1 = 1;
            }
            break;

        case 8:
            if ((gMenuPanels[0].unk_00 == 7) && (gMenuPanels[1].unk_00 == 7)) {
                var_v1 = 1;
            }
            break;

        case 7:
        case 9:
            if ((gMenuPanels[0].unk_00 == 0) && (gMenuPanels[1].unk_00 == 0)) {
                var_v1 = 1;
            }
            break;

        case 10:
            if (D_82F21140.unk_00 == 0) {
                var_v1 = 1;
            }
            break;

        case 11:
            if (gScreenTransition.unk_02 == 0) {
                var_v1 = 1;
            }
            break;

        case 12:
            if (gScreenTransition.unk_02 == 2) {
                var_v1 = 1;
            }
            break;
    }

    return var_v1;
}

void MenuPanel_SetStateVar(s16 arg0) {
    D_82F21140.unk_0E = arg0;
}

s16 MenuPanel_GetState(void) {
    return D_82F21140.unk_00;
}
