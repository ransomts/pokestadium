#include "fragment62.h"
#include "src/1C720.h"

void BattleAnim_SetupGlobalTintColorFadeDetach(ParticleEffectInstance* arg0) {
    BattleAnim_LoadGlobalTintToParticle(arg0);
    Particle_AdvanceLifecycle(arg0);
}

void BattleAnim_CallbackGlobalTintColorFadeDetach(ParticleEffectInstance* arg0) {
    switch (arg0->updateState) {
        case 1:
            BattleAnim_SetupGlobalTintColorFadeDetach(arg0);
            break;

        case 2:
            if (ParticleGfx_ApproachPrimPalette(arg0, arg0->paletteIndex, Particle_FieldAA_GetS16_0C068(arg0)) != 0) {
                Particle_AdvanceLifecycle(arg0);
            }
            break;

        case 3:
            Particle_DisableAndDetach(arg0);
            break;
    }

    BattleAnim_SetGlobalTintFromParticle(arg0);
}

void BattleAnim_SetupOwnerModelTintRampDetach(ParticleEffectInstance* arg0) {
    ParticleGfx_RecolorPrim(arg0, Particle_FieldCF_GetS16_0C058(arg0));
    Particle_FieldAE_SetS16_0BF4C(arg0, arg0->initialAlpha);
    Particle_AdvanceLifecycle(arg0);
}

void BattleAnim_CallbackOwnerModelTintRampDetach(ParticleEffectInstance* arg0) {
    switch (arg0->updateState) {
        case 1:
            BattleAnim_SetupOwnerModelTintRampDetach(arg0);
            break;

        case 2:
            if (Particle_FieldAE_Approach_0BF60(arg0, arg0->targetAlpha, arg0->alphaStep) != 0) {
                Particle_AdvanceLifecycle(arg0);
            }
            break;

        case 3:
            Particle_DisableAndDetach(arg0);
            break;
    }

    if (Particle_IsRunning(arg0) != 0) {
        Model_SetMaterialColor(&arg0->unk_10->unk_000, arg0->prim_r, arg0->prim_g, arg0->prim_b, arg0->alpha);
    }
}

void BattleAnim_SetupOwnerModelTintPulseDetach(ParticleEffectInstance* arg0) {
    ParticleGfx_RecolorPrim(arg0, Particle_FieldCF_GetS16_0C058(arg0));
    Particle_FieldAE_SetS16_0BF4C(arg0, arg0->unk_CE);
    Particle_AdvanceLifecycle(arg0);
}

void BattleAnim_CallbackOwnerModelTintPulseDetach(ParticleEffectInstance* arg0) {
    switch (arg0->updateState) {
        case 1:
            BattleAnim_SetupOwnerModelTintPulseDetach(arg0);
            break;

        case 2:
            if (Particle_FieldAE_Approach_0BF60(arg0, arg0->targetAlpha, arg0->alphaStep) != 0) {
                Particle_AdvanceLifecycle(arg0);
            }
            break;

        case 3:
            Particle_FieldA6_DecrementToZeroStep1AndStepState_0BDD0(arg0);
            break;

        case 4:
            if (Particle_FieldAE_Approach_0BF60(arg0, 0, arg0->alphaStep) != 0) {
                Particle_AdvanceLifecycle(arg0);
            }
            break;

        case 5:
            Particle_DisableAndDetach(arg0);
            break;
    }

    if (Particle_IsRunning(arg0) != 0) {
        Model_SetMaterialColor(&arg0->unk_10->unk_000, arg0->prim_r, arg0->prim_g, arg0->prim_b, arg0->alpha);
    }
}

void func_8433209C(void) {
}

void BattleAnim_CallbackOwnerModelTintHoldFadeDetach(ParticleEffectInstance* arg0) {
    switch (arg0->updateState) {
        case 1:
            BattleAnim_SetupOwnerModelTintPulseDetach(arg0);
            break;

        case 2:
            Particle_FieldA6_DecrementToZeroStep1AndStepState_0BDD0(arg0);
            break;

        case 3:
            if (Particle_FieldAE_Approach_0BF60(arg0, 0, arg0->alphaStep) != 0) {
                Particle_AdvanceLifecycle(arg0);
            }
            break;

        case 4:
            Particle_DisableAndDetach(arg0);
            break;
    }

    if (Particle_IsRunning(arg0) != 0) {
        Model_SetMaterialColor(&arg0->unk_10->unk_000, arg0->prim_r, arg0->prim_g, arg0->prim_b, arg0->alpha);
    }
}

void BattleAnim_SetupOwnerModelTintPaletteApproachInactive(ParticleEffectInstance* arg0) {
    ParticleGfx_RecolorPrim(arg0, Particle_FieldCF_GetS16_0C058(arg0));
    Particle_FieldAE_SetS16_0BF4C(arg0, arg0->initialAlpha);
    Particle_AdvanceLifecycle(arg0);
}

void BattleAnim_CallbackOwnerModelTintPaletteApproachInactive(ParticleEffectInstance* arg0) {
    switch (arg0->updateState) {
        case 1:
            BattleAnim_SetupOwnerModelTintPaletteApproachInactive(arg0);
            break;

        case 2:
            if (ParticleGfx_ApproachPrimPalette(arg0, arg0->targetAlpha, arg0->alphaStep) != 0) {
                Particle_FieldAE_SetS16_0BF4C(arg0, 0);
                Particle_AdvanceLifecycle(arg0);
            }
            break;

        case 3:
            Particle_MarkInactive(arg0);
            break;
    }

    if (Particle_IsRunning(arg0) != 0) {
        Model_SetMaterialColor(&arg0->unk_10->unk_000, arg0->prim_r, arg0->prim_g, arg0->prim_b, arg0->alpha);
    }
}

void BattleAnim_SetupOwnerModelTintPaletteApproach(ParticleEffectInstance* arg0) {
    ParticleGfx_RecolorPrim(arg0, Particle_FieldCF_GetS16_0C058(arg0));
    Particle_FieldAE_SetS16_0BF4C(arg0, arg0->initialAlpha);
    Particle_AdvanceLifecycle(arg0);
}

void BattleAnim_CallbackOwnerModelTintPaletteApproach(ParticleEffectInstance* arg0) {
    switch (arg0->updateState) {
        case 1:
            BattleAnim_SetupOwnerModelTintPaletteApproach(arg0);
            break;

        case 2:
            if (ParticleGfx_ApproachPrimPalette(arg0, arg0->targetAlpha, arg0->alphaStep) != 0) {
                Particle_AdvanceLifecycle(arg0);
            }
            break;

        case 3:
            Particle_MarkInactive(arg0);
            break;
    }

    if (Particle_IsRunning(arg0) != 0) {
        Model_SetMaterialColor(&arg0->unk_10->unk_000, arg0->prim_r, arg0->prim_g, arg0->prim_b, arg0->alpha);
    }
}

void BattleAnim_SetupOwnerModelTintPaletteCycle(ParticleEffectInstance* arg0) {
    ParticleGfx_RecolorPrim(arg0, Particle_FieldCF_GetS16_0C058(arg0));
    Particle_FieldAE_SetS16_0BF4C(arg0, 0);
    Particle_AdvanceLifecycle(arg0);
}

void BattleAnim_CallbackOwnerModelTintPaletteCycle(ParticleEffectInstance* arg0) {
    switch (arg0->updateState) {
        case 1:
            BattleAnim_SetupOwnerModelTintPaletteCycle(arg0);
            break;

        case 2:
            Particle_FieldAE_ApproachAndStepState_0BF98(arg0, arg0->initialAlpha, arg0->unk_CE);
            break;

        case 3:
            if (ParticleGfx_ApproachPrimPalette(arg0, arg0->targetAlpha, arg0->alphaStep) != 0) {
                Particle_AdvanceLifecycle(arg0);
            }
            break;

        case 4:
            Particle_FieldAE_ApproachAndStepState_0BF98(arg0, 0, arg0->unk_CE);
            break;

        case 5:
            Particle_MarkInactive(arg0);
            break;
    }

    if (Particle_IsRunning(arg0) != 0) {
        Model_SetMaterialColor(&arg0->unk_10->unk_000, arg0->prim_r, arg0->prim_g, arg0->prim_b, arg0->alpha);
    }
}

void BattleAnim_SetupOwnerModelTintPaletteApproachRampDown(ParticleEffectInstance* arg0) {
    ParticleGfx_RecolorPrim(arg0, Particle_FieldCF_GetS16_0C058(arg0));
    Particle_FieldAE_SetS16_0BF4C(arg0, arg0->initialAlpha);
    Particle_AdvanceLifecycle(arg0);
}

void BattleAnim_CallbackOwnerModelTintPaletteApproachRampDown(ParticleEffectInstance* arg0) {
    switch (arg0->updateState) {
        case 1:
            BattleAnim_SetupOwnerModelTintPaletteApproachRampDown(arg0);
            break;

        case 2:
            if (ParticleGfx_ApproachPrimPalette(arg0, arg0->targetAlpha, arg0->alphaStep) != 0) {
                Particle_AdvanceLifecycle(arg0);
            }
            break;

        case 3:
            Particle_FieldAE_ApproachAndStepState_0BF98(arg0, 0, arg0->unk_CE);
            break;

        case 4:
            Particle_MarkInactive(arg0);
            break;
    }

    if (Particle_IsRunning(arg0) != 0) {
        Model_SetMaterialColor(&arg0->unk_10->unk_000, arg0->prim_r, arg0->prim_g, arg0->prim_b, arg0->alpha);
    }
}

void BattleAnim_SetupOwnerModelTintPaletteFade(ParticleEffectInstance* arg0) {
    ParticleGfx_RecolorPrim(arg0, Particle_FieldCF_GetS16_0C058(arg0));
    Particle_FieldAE_SetS16_0BF4C(arg0, 0);
    Particle_AdvanceLifecycle(arg0);
}

void BattleAnim_CallbackOwnerModelTintPaletteFade(ParticleEffectInstance* arg0) {
    switch (arg0->updateState) {
        case 1:
            BattleAnim_SetupOwnerModelTintPaletteFade(arg0);
            break;

        case 2:
            if (Particle_FieldAE_Approach_0BF60(arg0, arg0->initialAlpha, arg0->unk_CE) != 0) {
                Particle_AdvanceLifecycle(arg0);
            }
            break;

        case 3:
            if (ParticleGfx_ApproachPrimPalette(arg0, arg0->targetAlpha, arg0->alphaStep) != 0) {
                Particle_AdvanceLifecycle(arg0);
            }
            break;

        case 4:
            Particle_MarkInactive(arg0);
            break;
    }

    if (Particle_IsRunning(arg0) != 0) {
        Model_SetMaterialColor(&arg0->unk_10->unk_000, arg0->prim_r, arg0->prim_g, arg0->prim_b, arg0->alpha);
    }
}

void BattleAnim_SetupOwnerModelTintRandomPaletteCycle(ParticleEffectInstance* arg0) {
    ParticleGfx_RecolorPrim(arg0, gPrimColorPalette[ParticleMath_RandomRange(6)]);
    Particle_FieldCF_SetU8_0BEEC(arg0, gPrimColorPalette[ParticleMath_RandomRange(6)]);
    Particle_SetPrimAlpha(arg0, arg0->targetAlpha);

    if (arg0->alphaStep == 0) {
        arg0->alphaStep = 1;
    }

    Particle_FieldA6_SetS16_0BCA8(arg0, 0xFF / arg0->alphaStep);
    Particle_AdvanceLifecycle(arg0);
}

void BattleAnim_CallbackOwnerModelTintRandomPaletteCycle(ParticleEffectInstance* arg0) {
    switch (arg0->updateState) {
        case 1:
            BattleAnim_SetupOwnerModelTintRandomPaletteCycle(arg0);
            break;

        case 2:
            ParticleGfx_ApproachPrimPalette(arg0, arg0->paletteIndex, arg0->alphaStep);
            if (Particle_FieldA6_DecrementToZeroStep1_0BDAC(arg0) != 0) {
                Particle_FieldA6_SetS16_0BCA8(arg0, 0xFF / arg0->alphaStep);
                Particle_FieldCF_SetU8_0BEEC(arg0, gPrimColorPalette[ParticleMath_RandomRange(6)]);
            }
            Model_SetMaterialColor(&arg0->unk_10->unk_000, arg0->prim_r, arg0->prim_g, arg0->prim_b, arg0->prim_a);
            break;
    }
}

void BattleAnim_SetupOwnerModelTintPaletteRotateFadeDetach(ParticleEffectInstance* arg0) {
    ParticleGfx_RecolorPrim(arg0, gPrimColorPalette[0]);
    Particle_FieldAE_SetS16_0BF4C(arg0, 1);
    Particle_FieldCF_SetU8_0BEEC(arg0, gPrimColorPalette[1]);
    Particle_SetPrimAlpha(arg0, arg0->targetAlpha);

    if (arg0->alphaStep == 0) {
        arg0->alphaStep = 1;
    }

    Particle_FieldA8_SetS16_0BE14(arg0, 0xFF / arg0->alphaStep);
    Particle_AdvanceLifecycle(arg0);
}

void BattleAnim_CallbackOwnerModelTintPaletteRotateFadeDetach(ParticleEffectInstance* arg0) {
    switch (arg0->updateState) {
        case 1:
            BattleAnim_SetupOwnerModelTintPaletteRotateFadeDetach(arg0);
            break;

        case 2:
            Particle_FieldA6_DecrementToZeroStep1AndStepState_0BDD0(arg0);
            if (Particle_FieldA8_DecrementToZeroStep1_0BE6C(arg0) != 0) {
                Particle_FieldA8_SetS16_0BE14(arg0, 0xFF / arg0->alphaStep);
                arg0->alpha = (arg0->alpha + 1) % 6;
                Particle_FieldCF_SetU8_0BEEC(arg0, gPrimColorPalette[arg0->alpha]);
            }
            ParticleGfx_ApproachPrimPalette(arg0, arg0->paletteIndex, arg0->alphaStep);
            Model_SetMaterialColor(&arg0->unk_10->unk_000, arg0->prim_r, arg0->prim_g, arg0->prim_b, arg0->prim_a);
            break;

        case 3:
            if (Particle_PrimAlpha_Approach_0BC2C(arg0, 0, 8) != 0) {
                Particle_AdvanceLifecycle(arg0);
            }
            Model_SetMaterialColor(&arg0->unk_10->unk_000, arg0->prim_r, arg0->prim_g, arg0->prim_b, arg0->prim_a);
            break;

        case 4:
            Particle_DisableAndDetach(arg0);
            break;
    }
}

void BattleAnim_SetupOwnerModelAlphaFade(ParticleEffectInstance* arg0) {
    arg0->prim_a = arg0->initialAlpha;
    Particle_AdvanceLifecycle(arg0);
}

void BattleAnim_CallbackOwnerModelAlphaFade(ParticleEffectInstance* arg0) {
    switch (arg0->updateState) {
        case 1:
            BattleAnim_SetupOwnerModelAlphaFade(arg0);
            break;

        case 2:
            if (Particle_PrimAlpha_Approach_0BC2C(arg0, arg0->targetAlpha, arg0->alphaStep) != 0) {
                Particle_AdvanceLifecycle(arg0);
            }
            break;

        case 3:
            Particle_MarkInactive(arg0);
            break;
    }

    if (Particle_IsRunning(arg0) != 0) {
        Model_SetMaterialAlpha(&arg0->unk_10->unk_000, arg0->prim_a);
    }
}

void BattleAnim_SetupParticleRecolorTransparent(ParticleEffectInstance* arg0) {
    ParticleGfx_RecolorPrim(arg0, Particle_FieldCF_GetS16_0C058(arg0));
    Particle_SetPrimAlpha(arg0, 0);
    Particle_AdvanceLifecycle(arg0);
}

void BattleAnim_CallbackStartEffect125OwnerColorAlphaFade(ParticleEffectInstance* arg0) {
    switch (arg0->updateState) {
        case 1:
            BattleAnim_SetupParticleRecolorTransparent(arg0);
            break;

        case 2:
            Particle_PrimAlpha_Approach_0BC2C(arg0, 0x80, 4);
            break;

        case 3:
            if (Particle_PrimAlpha_Approach_0BC2C(arg0, 0, 8) != 0) {
                Particle_DisableAndDetach(arg0);
            }
            break;
    }

    Model_SetMaterialColor(&arg0->unk_10->unk_000, arg0->prim_r, arg0->prim_g, arg0->prim_b, arg0->prim_a);
}

void BattleAnim_SetupDescriptor25AlphaFadeInHoldOut(ParticleEffectInstance* arg0) {
    ParticleGfx_RecolorPrim(arg0, Particle_FieldCF_GetS16_0C058(arg0));
    Particle_SetPrimAlpha(arg0, 0);
    Particle_AdvanceLifecycle(arg0);
}

void BattleAnim_CallbackDescriptor25AlphaFadeInHoldOut(ParticleEffectInstance* arg0) {
    switch (arg0->updateState) {
        case 1:
            BattleAnim_SetupDescriptor25AlphaFadeInHoldOut(arg0);
            break;

        case 2:
            Particle_PrimAlpha_ApproachAndStepState_0BC5C(arg0, arg0->targetAlpha, arg0->alphaStep);
            break;

        case 3:
            Particle_FieldA6_DecrementToZeroStep1AndStepState_0BDD0(arg0);
            break;

        case 4:
            if (Particle_PrimAlpha_Approach_0BC2C(arg0, 0, arg0->alphaStep) != 0) {
                Particle_MarkInactive(arg0);
            }
            break;
    }
}

void BattleAnim_SetupDescriptor25AlphaHoldFadeOut(ParticleEffectInstance* arg0) {
    ParticleGfx_RecolorPrim(arg0, Particle_FieldCF_GetS16_0C058(arg0));
    Particle_SetPrimAlpha(arg0, arg0->targetAlpha);
    Particle_AdvanceLifecycle(arg0);
}

void BattleAnim_CallbackDescriptor25AlphaHoldFadeOut(ParticleEffectInstance* arg0) {
    switch (arg0->updateState) {
        case 1:
            BattleAnim_SetupDescriptor25AlphaHoldFadeOut(arg0);
            break;

        case 2:
            Particle_FieldA6_DecrementToZeroStep1AndStepState_0BDD0(arg0);
            break;

        case 3:
            if (Particle_PrimAlpha_Approach_0BC2C(arg0, 0, arg0->alphaStep) != 0) {
                Particle_MarkInactive(arg0);
            }
            break;
    }
}

void BattleAnim_SetupDescriptor25AlphaFadeInHold(ParticleEffectInstance* arg0) {
    ParticleGfx_RecolorPrim(arg0, Particle_FieldCF_GetS16_0C058(arg0));
    Particle_SetPrimAlpha(arg0, 0);
    Particle_AdvanceLifecycle(arg0);
}

void BattleAnim_CallbackDescriptor25AlphaFadeInHold(ParticleEffectInstance* arg0) {
    switch (arg0->updateState) {
        case 1:
            BattleAnim_SetupDescriptor25AlphaFadeInHold(arg0);
            break;

        case 2:
            Particle_PrimAlpha_ApproachAndStepState_0BC5C(arg0, arg0->targetAlpha, arg0->alphaStep);
            break;

        case 3:
            if (Particle_FieldA6_DecrementToZeroStep1_0BDAC(arg0) != 0) {
                Particle_MarkInactive(arg0);
            }
            break;
    }
}

void BattleAnim_SetupDescriptor25AlphaHoldDetach(ParticleEffectInstance* arg0) {
    ParticleGfx_RecolorPrim(arg0, Particle_FieldCF_GetS16_0C058(arg0));
    Particle_SetPrimAlpha(arg0, arg0->targetAlpha);
    Particle_AdvanceLifecycle(arg0);
}

void BattleAnim_CallbackDescriptor25AlphaHoldDetach(ParticleEffectInstance* arg0) {
    switch (arg0->updateState) {
        case 1:
            BattleAnim_SetupDescriptor25AlphaHoldDetach(arg0);
            break;

        case 2:
            if (Particle_FieldA6_DecrementToZeroStep1_0BDAC(arg0) != 0) {
                Particle_DisableAndDetach(arg0);
            }
            break;
    }
}

void BattleAnim_SetupDescriptor25PaletteFadeOut(ParticleEffectInstance* arg0) {
    ParticleGfx_RecolorPrim(arg0, Particle_FieldCF_GetS16_0C058(arg0));
    Particle_SetPrimAlpha(arg0, 0xFF);
    Particle_AdvanceLifecycle(arg0);
}

void BattleAnim_CallbackDescriptor25PaletteFadeOut(ParticleEffectInstance* arg0) {
    switch (arg0->updateState) {
        case 1:
            BattleAnim_SetupDescriptor25PaletteFadeOut(arg0);
            break;

        case 2:
            Particle_FieldA6_DecrementToZeroStep1AndStepState_0BDD0(arg0);
            break;

        case 3:
            ParticleGfx_ApproachPrimPalette(arg0, arg0->targetAlpha, arg0->alphaStep);
            if (Particle_PrimAlpha_Approach_0BC2C(arg0, 0, arg0->alphaStep) != 0) {
                Particle_MarkInactive(arg0);
            }
            break;
    }
}

void BattleAnim_SetupDescriptor25PaletteFadeIn(ParticleEffectInstance* arg0) {
    ParticleGfx_RecolorPrim(arg0, Particle_FieldCF_GetS16_0C058(arg0));
    Particle_SetPrimAlpha(arg0, 0);
    Particle_AdvanceLifecycle(arg0);
}

void BattleAnim_CallbackDescriptor25PaletteFadeIn(ParticleEffectInstance* arg0) {
    switch (arg0->updateState) {
        case 1:
            BattleAnim_SetupDescriptor25PaletteFadeIn(arg0);
            break;

        case 2:
            ParticleGfx_ApproachPrimPalette(arg0, arg0->targetAlpha, arg0->alphaStep);
            Particle_PrimAlpha_ApproachAndStepState_0BC5C(arg0, 0xFF, arg0->alphaStep);
            break;

        case 3:
            if (Particle_FieldA6_DecrementToZeroStep1_0BDAC(arg0) != 0) {
                Particle_MarkInactive(arg0);
            }
            break;
    }
}
