#include "fragment62.h"
#include "src/1C720.h"

void BattleAnim_SetupGlobalTintColorFadeDetach(ParticleEffectInstance* arg0) {
    ParticleNode_RestorePrimColor(arg0);
    Particle_IncrementState(arg0);
}

void BattleAnim_CallbackGlobalTintColorFadeDetach(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            BattleAnim_SetupGlobalTintColorFadeDetach(arg0);
            break;

        case 2:
            if (IsPrimColorSupported(arg0, arg0->unk_CF, Particle_GetShortAA(arg0)) != 0) {
                Particle_IncrementState(arg0);
            }
            break;

        case 3:
            Particle_ResetState(arg0);
            break;
    }

    ParticleNode_SavePrimColor(arg0);
}

void Fragment_SetPrimColorFromPaletteAndRender(ParticleEffectInstance* arg0) {
    SetPrimColorFromPalette(arg0, Particle_GetShortCF(arg0));
    Particle_SetShortAE(arg0, arg0->unk_A6);
    Particle_IncrementState(arg0);
}

void BattleAnim_CallbackOwnerModelTintRampDetach(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            Fragment_SetPrimColorFromPaletteAndRender(arg0);
            break;

        case 2:
            if (Particle_ApproachShortAE(arg0, arg0->unk_CD, arg0->unk_AA) != 0) {
                Particle_IncrementState(arg0);
            }
            break;

        case 3:
            Particle_ResetState(arg0);
            break;
    }

    if (Particle_IsActive(arg0) != 0) {
        GraphNode_SetColorRGBA(&arg0->unk_10->unk_000, arg0->prim_r, arg0->prim_g, arg0->prim_b, arg0->unk_AE);
    }
}

void Fragment_SetPrimColorFromPaletteAndRender_WithCE(ParticleEffectInstance* arg0) {
    SetPrimColorFromPalette(arg0, Particle_GetShortCF(arg0));
    Particle_SetShortAE(arg0, arg0->unk_CE);
    Particle_IncrementState(arg0);
}

void BattleAnim_CallbackOwnerModelTintPulseDetach(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            Fragment_SetPrimColorFromPaletteAndRender_WithCE(arg0);
            break;

        case 2:
            if (Particle_ApproachShortAE(arg0, arg0->unk_CD, arg0->unk_AA) != 0) {
                Particle_IncrementState(arg0);
            }
            break;

        case 3:
            Particle_DecrementTimerA6ToZeroWithCallback(arg0);
            break;

        case 4:
            if (Particle_ApproachShortAE(arg0, 0, arg0->unk_AA) != 0) {
                Particle_IncrementState(arg0);
            }
            break;

        case 5:
            Particle_ResetState(arg0);
            break;
    }

    if (Particle_IsActive(arg0) != 0) {
        GraphNode_SetColorRGBA(&arg0->unk_10->unk_000, arg0->prim_r, arg0->prim_g, arg0->prim_b, arg0->unk_AE);
    }
}

void func_8433209C(void) {
}

void BattleAnim_CallbackOwnerModelTintHoldFadeDetach(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            Fragment_SetPrimColorFromPaletteAndRender_WithCE(arg0);
            break;

        case 2:
            Particle_DecrementTimerA6ToZeroWithCallback(arg0);
            break;

        case 3:
            if (Particle_ApproachShortAE(arg0, 0, arg0->unk_AA) != 0) {
                Particle_IncrementState(arg0);
            }
            break;

        case 4:
            Particle_ResetState(arg0);
            break;
    }

    if (Particle_IsActive(arg0) != 0) {
        GraphNode_SetColorRGBA(&arg0->unk_10->unk_000, arg0->prim_r, arg0->prim_g, arg0->prim_b, arg0->unk_AE);
    }
}

void BattleAnim_SetupOwnerModelTintPaletteApproachInactive(ParticleEffectInstance* arg0) {
    SetPrimColorFromPalette(arg0, Particle_GetShortCF(arg0));
    Particle_SetShortAE(arg0, arg0->unk_A6);
    Particle_IncrementState(arg0);
}

void BattleAnim_CallbackOwnerModelTintPaletteApproachInactive(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            BattleAnim_SetupOwnerModelTintPaletteApproachInactive(arg0);
            break;

        case 2:
            if (IsPrimColorSupported(arg0, arg0->unk_CD, arg0->unk_AA) != 0) {
                Particle_SetShortAE(arg0, 0);
                Particle_IncrementState(arg0);
            }
            break;

        case 3:
            Particle_ClearActiveFlag(arg0);
            break;
    }

    if (Particle_IsActive(arg0) != 0) {
        GraphNode_SetColorRGBA(&arg0->unk_10->unk_000, arg0->prim_r, arg0->prim_g, arg0->prim_b, arg0->unk_AE);
    }
}

void BattleAnim_SetupOwnerModelTintPaletteApproach(ParticleEffectInstance* arg0) {
    SetPrimColorFromPalette(arg0, Particle_GetShortCF(arg0));
    Particle_SetShortAE(arg0, arg0->unk_A6);
    Particle_IncrementState(arg0);
}

void BattleAnim_CallbackOwnerModelTintPaletteApproach(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            BattleAnim_SetupOwnerModelTintPaletteApproach(arg0);
            break;

        case 2:
            if (IsPrimColorSupported(arg0, arg0->unk_CD, arg0->unk_AA) != 0) {
                Particle_IncrementState(arg0);
            }
            break;

        case 3:
            Particle_ClearActiveFlag(arg0);
            break;
    }

    if (Particle_IsActive(arg0) != 0) {
        GraphNode_SetColorRGBA(&arg0->unk_10->unk_000, arg0->prim_r, arg0->prim_g, arg0->prim_b, arg0->unk_AE);
    }
}

void BattleAnim_SetupOwnerModelTintPaletteCycle(ParticleEffectInstance* arg0) {
    SetPrimColorFromPalette(arg0, Particle_GetShortCF(arg0));
    Particle_SetShortAE(arg0, 0);
    Particle_IncrementState(arg0);
}

void BattleAnim_CallbackOwnerModelTintPaletteCycle(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            BattleAnim_SetupOwnerModelTintPaletteCycle(arg0);
            break;

        case 2:
            Particle_ApproachShortAEWithCallback(arg0, arg0->unk_A6, arg0->unk_CE);
            break;

        case 3:
            if (IsPrimColorSupported(arg0, arg0->unk_CD, arg0->unk_AA) != 0) {
                Particle_IncrementState(arg0);
            }
            break;

        case 4:
            Particle_ApproachShortAEWithCallback(arg0, 0, arg0->unk_CE);
            break;

        case 5:
            Particle_ClearActiveFlag(arg0);
            break;
    }

    if (Particle_IsActive(arg0) != 0) {
        GraphNode_SetColorRGBA(&arg0->unk_10->unk_000, arg0->prim_r, arg0->prim_g, arg0->prim_b, arg0->unk_AE);
    }
}

void BattleAnim_SetupOwnerModelTintPaletteApproachRampDown(ParticleEffectInstance* arg0) {
    SetPrimColorFromPalette(arg0, Particle_GetShortCF(arg0));
    Particle_SetShortAE(arg0, arg0->unk_A6);
    Particle_IncrementState(arg0);
}

void BattleAnim_CallbackOwnerModelTintPaletteApproachRampDown(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            BattleAnim_SetupOwnerModelTintPaletteApproachRampDown(arg0);
            break;

        case 2:
            if (IsPrimColorSupported(arg0, arg0->unk_CD, arg0->unk_AA) != 0) {
                Particle_IncrementState(arg0);
            }
            break;

        case 3:
            Particle_ApproachShortAEWithCallback(arg0, 0, arg0->unk_CE);
            break;

        case 4:
            Particle_ClearActiveFlag(arg0);
            break;
    }

    if (Particle_IsActive(arg0) != 0) {
        GraphNode_SetColorRGBA(&arg0->unk_10->unk_000, arg0->prim_r, arg0->prim_g, arg0->prim_b, arg0->unk_AE);
    }
}

void BattleAnim_SetupOwnerModelTintPaletteFade(ParticleEffectInstance* arg0) {
    SetPrimColorFromPalette(arg0, Particle_GetShortCF(arg0));
    Particle_SetShortAE(arg0, 0);
    Particle_IncrementState(arg0);
}

void BattleAnim_CallbackOwnerModelTintPaletteFade(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            BattleAnim_SetupOwnerModelTintPaletteFade(arg0);
            break;

        case 2:
            if (Particle_ApproachShortAE(arg0, arg0->unk_A6, arg0->unk_CE) != 0) {
                Particle_IncrementState(arg0);
            }
            break;

        case 3:
            if (IsPrimColorSupported(arg0, arg0->unk_CD, arg0->unk_AA) != 0) {
                Particle_IncrementState(arg0);
            }
            break;

        case 4:
            Particle_ClearActiveFlag(arg0);
            break;
    }

    if (Particle_IsActive(arg0) != 0) {
        GraphNode_SetColorRGBA(&arg0->unk_10->unk_000, arg0->prim_r, arg0->prim_g, arg0->prim_b, arg0->unk_AE);
    }
}

void Fragment_SetRandomPrimColorAndRender(ParticleEffectInstance* arg0) {
    SetPrimColorFromPalette(arg0, gPrimColorPalette[RandomMod(6)]);
    Particle_SetByteCF(arg0, gPrimColorPalette[RandomMod(6)]);
    Particle_SetPrimAlpha(arg0, arg0->unk_CD);

    if (arg0->unk_AA == 0) {
        arg0->unk_AA = 1;
    }

    Particle_SetTimerA6(arg0, 0xFF / arg0->unk_AA);
    Particle_IncrementState(arg0);
}

void BattleAnim_CallbackOwnerModelTintRandomPaletteCycle(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            Fragment_SetRandomPrimColorAndRender(arg0);
            break;

        case 2:
            IsPrimColorSupported(arg0, arg0->unk_CF, arg0->unk_AA);
            if (Particle_DecrementTimerA6ToZero(arg0) != 0) {
                Particle_SetTimerA6(arg0, 0xFF / arg0->unk_AA);
                Particle_SetByteCF(arg0, gPrimColorPalette[RandomMod(6)]);
            }
            GraphNode_SetColorRGBA(&arg0->unk_10->unk_000, arg0->prim_r, arg0->prim_g, arg0->prim_b, arg0->prim_a);
            break;
    }
}

void Fragment_SetFixedPrimColorsAndRender(ParticleEffectInstance* arg0) {
    SetPrimColorFromPalette(arg0, gPrimColorPalette[0]);
    Particle_SetShortAE(arg0, 1);
    Particle_SetByteCF(arg0, gPrimColorPalette[1]);
    Particle_SetPrimAlpha(arg0, arg0->unk_CD);

    if (arg0->unk_AA == 0) {
        arg0->unk_AA = 1;
    }

    Particle_SetTimerA8(arg0, 0xFF / arg0->unk_AA);
    Particle_IncrementState(arg0);
}

void Fragment_ComplexColorMode(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            Fragment_SetFixedPrimColorsAndRender(arg0);
            break;

        case 2:
            Particle_DecrementTimerA6ToZeroWithCallback(arg0);
            if (Particle_DecrementTimerA8ToZero(arg0) != 0) {
                Particle_SetTimerA8(arg0, 0xFF / arg0->unk_AA);
                arg0->unk_AE = (arg0->unk_AE + 1) % 6;
                Particle_SetByteCF(arg0, gPrimColorPalette[arg0->unk_AE]);
            }
            IsPrimColorSupported(arg0, arg0->unk_CF, arg0->unk_AA);
            GraphNode_SetColorRGBA(&arg0->unk_10->unk_000, arg0->prim_r, arg0->prim_g, arg0->prim_b, arg0->prim_a);
            break;

        case 3:
            if (Particle_ApproachPrimAlpha(arg0, 0, 8) != 0) {
                Particle_IncrementState(arg0);
            }
            GraphNode_SetColorRGBA(&arg0->unk_10->unk_000, arg0->prim_r, arg0->prim_g, arg0->prim_b, arg0->prim_a);
            break;

        case 4:
            Particle_ResetState(arg0);
            break;
    }
}

void Fragment_SetAlphaFromUnkA6AndRender(ParticleEffectInstance* arg0) {
    arg0->prim_a = arg0->unk_A6;
    Particle_IncrementState(arg0);
}

void Fragment_ProcessAlphaMode(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            Fragment_SetAlphaFromUnkA6AndRender(arg0);
            break;

        case 2:
            if (Particle_ApproachPrimAlpha(arg0, arg0->unk_CD, arg0->unk_AA) != 0) {
                Particle_IncrementState(arg0);
            }
            break;

        case 3:
            Particle_ClearActiveFlag(arg0);
            break;
    }

    if (Particle_IsActive(arg0) != 0) {
        GraphNode_SetState(&arg0->unk_10->unk_000, arg0->prim_a);
    }
}

void Fragment_SetPrimColorFromPaletteAndRender_ZeroBC20(ParticleEffectInstance* arg0) {
    SetPrimColorFromPalette(arg0, Particle_GetShortCF(arg0));
    Particle_SetPrimAlpha(arg0, 0);
    Particle_IncrementState(arg0);
}

void Fragment_ProcessBC20Mode(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            Fragment_SetPrimColorFromPaletteAndRender_ZeroBC20(arg0);
            break;

        case 2:
            Particle_ApproachPrimAlpha(arg0, 0x80, 4);
            break;

        case 3:
            if (Particle_ApproachPrimAlpha(arg0, 0, 8) != 0) {
                Particle_ResetState(arg0);
            }
            break;
    }

    GraphNode_SetColorRGBA(&arg0->unk_10->unk_000, arg0->prim_r, arg0->prim_g, arg0->prim_b, arg0->prim_a);
}

void Fragment_SetPrimColorFromPaletteAndRender_ZeroBC20_Alt(ParticleEffectInstance* arg0) {
    SetPrimColorFromPalette(arg0, Particle_GetShortCF(arg0));
    Particle_SetPrimAlpha(arg0, 0);
    Particle_IncrementState(arg0);
}

void Fragment_ProcessBC20Variant(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            Fragment_SetPrimColorFromPaletteAndRender_ZeroBC20_Alt(arg0);
            break;

        case 2:
            Particle_ApproachPrimAlphaWithCallback(arg0, arg0->unk_CD, arg0->unk_AA);
            break;

        case 3:
            Particle_DecrementTimerA6ToZeroWithCallback(arg0);
            break;

        case 4:
            if (Particle_ApproachPrimAlpha(arg0, 0, arg0->unk_AA) != 0) {
                Particle_ClearActiveFlag(arg0);
            }
            break;
    }
}

void Fragment_SetPrimColorFromPaletteAndRender_WithCD_BC20(ParticleEffectInstance* arg0) {
    SetPrimColorFromPalette(arg0, Particle_GetShortCF(arg0));
    Particle_SetPrimAlpha(arg0, arg0->unk_CD);
    Particle_IncrementState(arg0);
}

void Fragment_ProcessBC20WithCDMode(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            Fragment_SetPrimColorFromPaletteAndRender_WithCD_BC20(arg0);
            break;

        case 2:
            Particle_DecrementTimerA6ToZeroWithCallback(arg0);
            break;

        case 3:
            if (Particle_ApproachPrimAlpha(arg0, 0, arg0->unk_AA) != 0) {
                Particle_ClearActiveFlag(arg0);
            }
            break;
    }
}

void Fragment_SetPrimColorFromPaletteAndRender_ZeroBC20_Third(ParticleEffectInstance* arg0) {
    SetPrimColorFromPalette(arg0, Particle_GetShortCF(arg0));
    Particle_SetPrimAlpha(arg0, 0);
    Particle_IncrementState(arg0);
}

void BattleAnim_CallbackDescriptor25AlphaFadeInHold(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            Fragment_SetPrimColorFromPaletteAndRender_ZeroBC20_Third(arg0);
            break;

        case 2:
            Particle_ApproachPrimAlphaWithCallback(arg0, arg0->unk_CD, arg0->unk_AA);
            break;

        case 3:
            if (Particle_DecrementTimerA6ToZero(arg0) != 0) {
                Particle_ClearActiveFlag(arg0);
            }
            break;
    }
}

void BattleAnim_SetupDescriptor25AlphaHoldDetach(ParticleEffectInstance* arg0) {
    SetPrimColorFromPalette(arg0, Particle_GetShortCF(arg0));
    Particle_SetPrimAlpha(arg0, arg0->unk_CD);
    Particle_IncrementState(arg0);
}

void BattleAnim_CallbackDescriptor25AlphaHoldDetach(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            BattleAnim_SetupDescriptor25AlphaHoldDetach(arg0);
            break;

        case 2:
            if (Particle_DecrementTimerA6ToZero(arg0) != 0) {
                Particle_ResetState(arg0);
            }
            break;
    }
}

void BattleAnim_SetupDescriptor25PaletteFadeOut(ParticleEffectInstance* arg0) {
    SetPrimColorFromPalette(arg0, Particle_GetShortCF(arg0));
    Particle_SetPrimAlpha(arg0, 0xFF);
    Particle_IncrementState(arg0);
}

void BattleAnim_CallbackDescriptor25PaletteFadeOut(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            BattleAnim_SetupDescriptor25PaletteFadeOut(arg0);
            break;

        case 2:
            Particle_DecrementTimerA6ToZeroWithCallback(arg0);
            break;

        case 3:
            IsPrimColorSupported(arg0, arg0->unk_CD, arg0->unk_AA);
            if (Particle_ApproachPrimAlpha(arg0, 0, arg0->unk_AA) != 0) {
                Particle_ClearActiveFlag(arg0);
            }
            break;
    }
}

void BattleAnim_SetupDescriptor25PaletteFadeIn(ParticleEffectInstance* arg0) {
    SetPrimColorFromPalette(arg0, Particle_GetShortCF(arg0));
    Particle_SetPrimAlpha(arg0, 0);
    Particle_IncrementState(arg0);
}

void BattleAnim_CallbackDescriptor25PaletteFadeIn(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            BattleAnim_SetupDescriptor25PaletteFadeIn(arg0);
            break;

        case 2:
            IsPrimColorSupported(arg0, arg0->unk_CD, arg0->unk_AA);
            Particle_ApproachPrimAlphaWithCallback(arg0, 0xFF, arg0->unk_AA);
            break;

        case 3:
            if (Particle_DecrementTimerA6ToZero(arg0) != 0) {
                Particle_ClearActiveFlag(arg0);
            }
            break;
    }
}
