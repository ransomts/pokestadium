#include "fragment62.h"
#include "src/1C720.h"

void func_84331DA0(ParticleEffectInstance* arg0) {
    func_8432FEEC(arg0);
    Particle_IncrementState(arg0);
}

void func_84331DC8(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            func_84331DA0(arg0);
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

    func_8432FEC4(arg0);
}

void Fragment_SetPrimColorFromPaletteAndRender(ParticleEffectInstance* arg0) {
    SetPrimColorFromPalette(arg0, Particle_GetShortCF(arg0));
    Particle_SetShortAE(arg0, arg0->unk_A6);
    Particle_IncrementState(arg0);
}

void func_84331EAC(ParticleEffectInstance* arg0) {
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

void func_84331FAC(ParticleEffectInstance* arg0) {
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

void func_843320A4(ParticleEffectInstance* arg0) {
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

void func_84332174(ParticleEffectInstance* arg0) {
    SetPrimColorFromPalette(arg0, Particle_GetShortCF(arg0));
    Particle_SetShortAE(arg0, arg0->unk_A6);
    Particle_IncrementState(arg0);
}

void func_843321BC(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            func_84332174(arg0);
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

void func_8433227C(ParticleEffectInstance* arg0) {
    SetPrimColorFromPalette(arg0, Particle_GetShortCF(arg0));
    Particle_SetShortAE(arg0, arg0->unk_A6);
    Particle_IncrementState(arg0);
}

void func_843322C4(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            func_8433227C(arg0);
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

void func_8433237C(ParticleEffectInstance* arg0) {
    SetPrimColorFromPalette(arg0, Particle_GetShortCF(arg0));
    Particle_SetShortAE(arg0, 0);
    Particle_IncrementState(arg0);
}

void func_843323BC(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            func_8433237C(arg0);
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

void func_843324A4(ParticleEffectInstance* arg0) {
    SetPrimColorFromPalette(arg0, Particle_GetShortCF(arg0));
    Particle_SetShortAE(arg0, arg0->unk_A6);
    Particle_IncrementState(arg0);
}

void func_843324EC(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            func_843324A4(arg0);
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

void func_843325C4(ParticleEffectInstance* arg0) {
    SetPrimColorFromPalette(arg0, Particle_GetShortCF(arg0));
    Particle_SetShortAE(arg0, 0);
    Particle_IncrementState(arg0);
}

void func_84332604(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            func_843325C4(arg0);
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

void func_843327B8(ParticleEffectInstance* arg0) {
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

void func_84332E6C(ParticleEffectInstance* arg0) {
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

void func_84332EE8(ParticleEffectInstance* arg0) {
    SetPrimColorFromPalette(arg0, Particle_GetShortCF(arg0));
    Particle_SetPrimAlpha(arg0, arg0->unk_CD);
    Particle_IncrementState(arg0);
}

void func_84332F30(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            func_84332EE8(arg0);
            break;

        case 2:
            if (Particle_DecrementTimerA6ToZero(arg0) != 0) {
                Particle_ResetState(arg0);
            }
            break;
    }
}

void func_84332F90(ParticleEffectInstance* arg0) {
    SetPrimColorFromPalette(arg0, Particle_GetShortCF(arg0));
    Particle_SetPrimAlpha(arg0, 0xFF);
    Particle_IncrementState(arg0);
}

void func_84332FD0(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            func_84332F90(arg0);
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

void func_84333060(ParticleEffectInstance* arg0) {
    SetPrimColorFromPalette(arg0, Particle_GetShortCF(arg0));
    Particle_SetPrimAlpha(arg0, 0);
    Particle_IncrementState(arg0);
}

void func_843330A0(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            func_84333060(arg0);
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
