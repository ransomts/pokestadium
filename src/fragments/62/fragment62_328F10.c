#include "fragment62.h"

void BattleAnim_InitStartEffect135Descriptor1CRisingScale(ParticleEffectInstance* arg0) {
    Vec3s sp28;
    s16 sp26 = Particle_GetShortCF(arg0);
    s16 sp24 = Particle_GetShortAC(arg0);

    Particle_SetVelocityYScaled(arg0, 2.5f);
    Particle_SetScaleFactor1(arg0, 0.065789476f);
    Particle_SetSpeed(arg0, 0.0f);
    sp28.x = RandomRangeSigned(0x5000);
    sp28.y = sp24 * (0x10000 / arg0->alphaStep);
    sp28.z = 0;
    Particle_AddRotationDeltaVec(arg0, sp28);
    SetPrimColorFromPalette(arg0, sp26);
    Particle_SetPrimAlpha(arg0, 0x80);
    Particle_DisableFlag4(arg0);
    Particle_IncrementState(arg0);
}

void BattleAnim_CallbackStartEffect135Descriptor1CRisingScaleFade(ParticleEffectInstance* arg0) {
    switch (arg0->updateState) {
        case 1:
            BattleAnim_InitStartEffect135Descriptor1CRisingScale(arg0);
            break;

        case 2:
            if (Particle_ProcessTimer80(arg0, Particle_GetShortAC(arg0)) != 0) {
                Particle_EnableFlag4(arg0);
            }
            break;

        case 3:
            Particle_ApproachScaleFactor1(arg0, 1.3157895f, 0.16447368f);
            Particle_DecrementTimerA6ToZeroWithCallback(arg0);
            break;

        case 4:
            Particle_ApproachPrimAlphaWithCallback(arg0, 0, 0x10);
            break;

        case 5:
            Particle_ResetState(arg0);
            break;
    }

    Particle_RotateY(arg0, 0x400);
    Particle_ApplyB2B4AndAddAll(arg0);
}

void BattleAnim_InitStartEffect135ExpandingFlash(ParticleEffectInstance* arg0) {
    s16 sp26 = Particle_GetShortCF(arg0);

    Particle_SetScaleFactor1(arg0, 0.65789473f);
    SetPrimEnvColorFromPair(arg0, sp26);
    Particle_SetParamC7(arg0, 2);
    Particle_SetPrimAlpha(arg0, 0xC8);
    Particle_IncrementState(arg0);
}

void BattleAnim_CallbackStartEffect135ExpandingFlashFade(ParticleEffectInstance* arg0) {
    switch (arg0->updateState) {
        case 1:
            BattleAnim_InitStartEffect135ExpandingFlash(arg0);
            break;

        case 2:
            Particle_ApproachScaleFactor1(arg0, 6.5789475f, 0.32894737f);
            Particle_ProcessTimer80(arg0, 0xF);
            break;

        case 3:
            Particle_DecrementTimerA6ToZeroWithCallback(arg0);
            break;

        case 4:
            Particle_ApproachPrimAlphaWithCallback(arg0, 0, 0x20);
            break;

        case 5:
            Particle_ResetState(arg0);
            break;
    }
}

void BattleAnim_InitStartEffect139Descriptor42FallingScale(ParticleEffectInstance* arg0) {
    s16 sp2E = Particle_GetShortCF(arg0);
    s16 sp2C = Particle_GetShortAC(arg0);

    Particle_SetScaleFactor1(arg0, 0.05f);
    Particle_SetRotation(arg0, RandomMod(0x10000), RandomMod(0x10000), 0);
    Particle_SetSpeed(arg0, 1.2f);
    SetPrimEnvColorFromPair(arg0, sp2E);
    Particle_SetTimerA6(arg0, sp2C * 1);
    Particle_DisableFlag4(arg0);
    Particle_IncrementState(arg0);
}

void BattleAnim_CallbackStartEffect139Descriptor42FallingScaleFade(ParticleEffectInstance* arg0) {
    switch (arg0->updateState) {
        case 1:
            BattleAnim_InitStartEffect139Descriptor42FallingScale(arg0);
            break;

        case 2:
            if (Particle_DecrementTimerA6ToZeroWithCallback(arg0) != 0) {
                Particle_EnableFlag4(arg0);
            }
            break;

        case 3:
            if (Particle_ApproachScaleFactor1(arg0, 0.15f, 0.025f) != 0) {
                Particle_IncrementState(arg0);
            }
            break;

        case 4:
            if (Particle_ApproachScaleFactor1(arg0, 0.0f, 0.04f) != 0) {
                Particle_IncrementState(arg0);
            }
            break;

        case 5:
            Particle_ResetState(arg0);
            break;
    }

    Particle_ApproachSpeedScaled(arg0, 0.2, 0.2f);
    Particle_ApplyB2B4AndAddAll(arg0);
    Particle_AddVelocityYScaled(arg0, -1.0f);
}

void BattleAnim_InitStartEffect139Descriptor22SpinFade(ParticleEffectInstance* arg0) {
    UNUSED s16 pad;
    s16 sp2C;

    Particle_GetShortAC(arg0);
    sp2C = Particle_GetShortCF(arg0);
    Particle_SetScaleFactor1(arg0, 0.175f);
    Particle_SetRotation(arg0, RandomMod(0x10000), RandomMod(0x10000), 0);
    SetPrimEnvColorFromPair(arg0, sp2C);
    Particle_SetPrimAlpha(arg0, 0x80);
    Particle_IncrementState(arg0);
}

void BattleAnim_CallbackStartEffect139Descriptor22SpinFadeSpark(ParticleEffectInstance* arg0) {
    switch (arg0->updateState) {
        case 1:
            BattleAnim_InitStartEffect139Descriptor22SpinFade(arg0);
            break;

        case 2:
            Particle_ApproachScaleFactor1(arg0, 0.1f, 0.01f);
            Particle_ApproachPrimAlpha(arg0, 0, 8);
            Particle_ApplyB2B4AndAddAll(arg0);
            Particle_DecrementTimerA6ToZeroWithCallback(arg0);
            break;

        case 3:
            Particle_ResetState(arg0);
            break;
    }
}

void BattleAnim_InitStartEffect141Descriptor1CGridRise(ParticleEffectInstance* arg0) {
    s16 sp2E;
    s16 sp2C;
    s16 temp_v0;
    Vec3s sp24;

    temp_v0 = Particle_GetShortAC(arg0);
    sp2E = temp_v0 / 8;
    sp2C = temp_v0 % 8;

    Particle_SetScaleFactor1(arg0, 0.5f);
    sp24.x = 0x6000 - (sp2E * 0xC00);
    sp24.y = (sp2C << 0xC) + 0xB000;
    sp24.z = 0;
    Particle_AddRotationDeltaVec(arg0, sp24);
    Particle_SetPrimColor(arg0, 0xC8, 0xFF, 0xFF);
    Particle_SetPrimAlpha(arg0, 0x60);
    Particle_SetTimerA6(arg0, sp2E);
    Particle_DisableFlag4(arg0);
    Particle_IncrementState(arg0);
}

void BattleAnim_CallbackStartEffect141Descriptor1CGridRiseFade(ParticleEffectInstance* arg0) {
    switch (arg0->updateState) {
        case 1:
            BattleAnim_InitStartEffect141Descriptor1CGridRise(arg0);
            break;

        case 2:
            if (Particle_DecrementTimerA6ToZeroWithCallback(arg0) != 0) {
                Particle_SetTimerA6(arg0, 0xA);
                Particle_EnableFlag4(arg0);
            }
            break;

        case 3:
            Particle_RotateY(arg0, 0x200);
            Particle_ApproachScaleFactor1(arg0, 2.0f, 0.01f);
            Particle_DecrementTimerA6ToZeroWithCallback(arg0);
            break;

        case 4:
            Particle_ApproachPrimAlphaWithCallback(arg0, 0, 0x10);
            break;

        case 5:
            Particle_ClearActiveFlag(arg0);
            break;
    }
}

void BattleAnim_InitStartEffects133And134And143Descriptor44ModeOrbit(ParticleEffectInstance* arg0) {
    s16 sp36;
    s16 sp34;
    s16 sp32 = Particle_GetShortAC(arg0);
    s16 sp30 = Particle_GetShortCF(arg0);
    s16 sp2E = Particle_GetShortCE(arg0);

    Particle_SetRotation(arg0, RandomMod(0x10000), RandomMod(0x10000), 0);
    Particle_SetScaleFactor1(arg0, 0.01f);
    SetPrimEnvColorFromPair(arg0, sp30);

    switch (sp2E) {
        case 0:
            Particle_SetShortAE(arg0, RandomModPlus(0x14, 0x14));
            Particle_SetShortB0(arg0, 0);
            sp36 = Particle_GetRandomRotation(0x200, 0x200);
            sp34 = Particle_GetRandomRotation(0x200, 0x200);
            Particle_SetTimerA8(arg0, 8);
            break;

        case 1:
            Particle_SetShortAE(arg0, RandomModPlus(0x28, 0x14));
            Particle_SetShortB0(arg0, 1);
            sp36 = Particle_GetRandomRotation(0x200, 0x200);
            sp34 = Particle_GetRandomRotation(0x200, 0x200);
            Particle_SetTimerA8(arg0, 0x10);
            break;

        case 2:
            Particle_SetShortAE(arg0, RandomModPlus(0x1E, 0x14));
            Particle_SetShortB0(arg0, 2);
            sp36 = Particle_GetRandomRotation(0x200, 0x200);
            sp34 = Particle_GetRandomRotation(0x200, 0x200);
            Particle_SetTimerA8(arg0, 0xA);
            break;

        case 3:
            Particle_SetShortAE(arg0, 0x1E - sp32);
            Particle_SetShortB0(arg0, 2);
            sp36 = Particle_GetRandomRotation(0x200, 0x200);
            sp34 = Particle_GetRandomRotation(0x200, 0x200);
            Particle_SetTimerA8(arg0, 0xA);
            break;
    }

    Particle_SetRotationDeltaX(arg0, sp36);
    Particle_SetRotationDeltaY(arg0, sp34);
    Particle_SetTimerA6(arg0, sp32 * 2);
    Particle_DisableFlag4(arg0);
    Particle_IncrementState(arg0);
}

void BattleAnim_CallbackStartEffects133And134And143Descriptor44ModeOrbitSwirl(ParticleEffectInstance* arg0) {
    Particle_GetShortCE(arg0);

    switch (arg0->updateState) {
        case 1:
            BattleAnim_InitStartEffects133And134And143Descriptor44ModeOrbit(arg0);
            break;

        case 2:
            if (Particle_DecrementTimerA6ToZeroWithCallback(arg0) != 0) {
                Particle_EnableFlag4(arg0);
                Particle_IncrementFlag2Counter(arg0);
            }
            break;

        case 3:
            if (Particle_ApproachScaleFactor1WithCallback(arg0, 0.3f, 0.05f) != 0) {}
            break;

        case 4:
            if (Particle_ProcessTimer80(arg0, arg0->unk_A8) != 0) {
                Particle_IncrementFlag2Counter(arg0);
            }
            break;

        case 5:
            Particle_ApproachScaleFactor1WithCallback(arg0, 0.0f, 0.05f);
            break;

        case 6:
            Particle_ClearActiveFlag(arg0);
            break;
    }

    if (Particle_HasFlag4(arg0) != 0) {
        switch (arg0->unk_B8) {
            case 1:
                Particle_AddRotationDeltaX(arg0);
                Particle_SetVelocityFromComplexDir(arg0, arg0->alpha);
                break;

            case 2:
                Particle_AddRotationDeltaX(arg0);
                Particle_ApproachShortAE(arg0, 0, arg0->unk_B0);
                Particle_SetVelocityFromComplexDir(arg0, arg0->alpha);
                break;
        }
    }

    Particle_AddVelocityYScaled(arg0, 10.0f);
}

void BattleAnim_InitStartEffects133And134And143Descriptor38MetadataBurst(ParticleEffectInstance* arg0) {
    s16 sp26 = Particle_GetShortCF(arg0);

    Particle_SetScaleFactor1(arg0, 0.2f);
    Particle_AddVelocityYScaled(arg0, 5.0f);
    SetPrimEnvColorFromPair(arg0, sp26);
    Particle_SetPrimAlpha(arg0, 0x40);
    Particle_IncrementState(arg0);
}

void BattleAnim_CallbackStartEffects133And134And143Descriptor38MetadataBurstEmitter(ParticleEffectInstance* arg0) {
    switch (arg0->updateState) {
        case 1:
            BattleAnim_InitStartEffects133And134And143Descriptor38MetadataBurst(arg0);
            break;

        case 2:
            Particle_ApproachScaleFactor1(arg0, 4.0f, 0.1f);
            Particle_ApproachPrimAlpha(arg0, 0xC8, 8);
            Particle_DecrementTimerA6ToZeroWithCallback(arg0);
            break;

        case 3:
            Particle_ApproachScaleFactor1(arg0, 0.25f, 0.5f);
            Particle_CreateChildParticles(arg0, Particle_HandleState_Complex, &gParticleEffectData[0x42], 6, 0x18, 7);
            if (Particle_ProcessTimer80(arg0, 6) != 0) {
                Particle_SetByteCC(arg0, 9);
            }
            break;

        case 4:
            Particle_AddScaledVelocityY(arg0, 15.0f);
            Particle_ProcessTimer80(arg0, 0xA);
            Particle_CreateChildParticles(arg0, Particle_HandleState_Complex, &gParticleEffectData[0x42], 6, 0x18, 7);
            break;

        case 5:
            Particle_ResetState(arg0);
            break;
    }
}

s16 BattleAnim_GetSessionModeEffectParam(void) {
    s16 var_v1 = 0x3B;

    switch (gBattleContext.unk_0000) {
        case 0:
            var_v1 = 0xD;
            break;

        case 1:
            var_v1 = 0x3C;
            break;

        case 2:
            var_v1 = 0x3C;
            break;

        case 3:
            var_v1 = 3;
            break;

        case 4:
            var_v1 = 3;
            break;

        case 5:
            var_v1 = 3;
            break;
    }
    return var_v1;
}

void BattleAnim_StartEffect139DualRepeatingSparks(void) {
    s16 sp3E = BattleAnim_GetSessionModeEffectParam();

    ParticleDef_CreateFull(0, 1, 0x1E, BattleAnim_CallbackStartEffect139Descriptor22SpinFadeSpark, &gParticleEffectData[0x22], 0x10, 1, 0x1E, 0, sp3E, 0);
    ParticleDef_CreateFull(0, 1, 0x1E, BattleAnim_CallbackStartEffect139Descriptor42FallingScaleFade, &gParticleEffectData[0x42], 0x10, 2, 0x1E, 0, sp3E, 0);
}

void BattleAnim_StartEffect140StartEffect139Alias(void) {
    BattleAnim_StartEffect139DualRepeatingSparks();
}

void BattleAnim_StartEffect141GridRiseAndFallingBurst(void) {
    ParticleDef_CreateFull(0xB, 1, 5, Particle_HandleState_Complex, &gParticleEffectData[0x42], 0, 5, 0x1E, 0, BattleAnim_GetSessionModeEffectParam(), 8);
    ParticleDef_Create32E6CAlt(0xA, 2, 0x16, 7, 0xFF);
    ParticleSystem_SetSpawnOffset(0x10);
    ParticleDef_CreateQuick(0, BattleAnim_CallbackStartEffect141Descriptor1CGridRiseFade, &gParticleEffectData[0x1C], 0, 0x40, 0x1E, 0, 0xA, 0);
}

void BattleAnim_StartEffect142StartEffect141Alias(void) {
    BattleAnim_StartEffect141GridRiseAndFallingBurst();
}

void BattleAnim_StartEffect135ExpandingFlashAndRisingScaleFade(void) {
    UNUSED s32 pad;

    ParticleDef_CreateBC20CD(0, 0, 0x10, 7);
    ParticleDef_Create31EAC(0, 0xA, 0xFF, 0xFF, 0xFF);
    ParticleDef_CreateAlphaMode(0, 0xFF, 0xFF, 0xFF);
    ParticleDef_Create31EAC(0x14, 0xA, 0xFF, 0, 8);
    ParticleDef_CreateQuick(0, BattleAnim_CallbackStartEffect135ExpandingFlashFade, &gParticleEffectData[0x21], 4, 1, 2, 0, 0x50, 0);
    ParticleDef_CreateQuick(0, BattleAnim_CallbackStartEffect135ExpandingFlashFade, &gParticleEffectData[0x23], 4, 1, 2, 0, 0x50, 0);
    ParticleDef_CreateQuick(0, BattleAnim_CallbackStartEffect135ExpandingFlashFade, &gParticleEffectData[0x17], 4, 1, 2, 0, 0x50, 0);
    ParticleDef_CreateFull(0, 1, 4, BattleAnim_CallbackStartEffect135Descriptor1CRisingScaleFade, &gParticleEffectData[0x1C], 5, 0x10, 7, 0, 0x39, 0);
    ParticleDef_CreateDefault(0x32, 0x10, 0xA);
}

void BattleAnim_StartEffect134ModeOrbitAndMetadataBurst(void) {
    ParticleDef_CreateDefault(0, 8, 6);
    ParticleDef_CreateFull(0, 4, 5, BattleAnim_CallbackStartEffects133And134And143Descriptor44ModeOrbitSwirl, &gParticleEffectData[0x44], 0, 4, 9, 0, 0x3C, 1);
    ParticleDef_CreateFull(0, 4, 5, BattleAnim_CallbackStartEffects133And134And143Descriptor44ModeOrbitSwirl, &gParticleEffectData[0x44], 0, 4, 9, 0, 0x3C, 1);
    ParticleDef_CreateFull(0x18, 1, 4, BattleAnim_CallbackStartEffects133And134And143Descriptor44ModeOrbitSwirl, &gParticleEffectData[0x44], 0, 8, 9, 0, 0x3C, 2);
    ParticleDef_CreateFull(0x1E, 1, 8, BattleAnim_CallbackStartEffects133And134And143Descriptor44ModeOrbitSwirl, &gParticleEffectData[0x44], 0, 8, 9, 0, 0x3C, 3);
    ParticleDef_CreateFull(0x1E, 1, 8, BattleAnim_CallbackStartEffects133And134And143Descriptor44ModeOrbitSwirl, &gParticleEffectData[0x44], 0, 8, 9, 0, 0x3C, 3);
    ParticleDef_Create31EAC(0x26, 0xA, 0, 0xFF, 4);
    ParticleDef_CreateQuick(0x2D, BattleAnim_CallbackStartEffects133And134And143Descriptor38MetadataBurstEmitter, &gParticleEffectData[0x38], 0x1A, 1, 2, 0, 0x3C, 0);
    ParticleDef_CreateAlphaMode(0x48, 0x40, 0, 0xFF);
    ParticleDef_CreateDefault(0x55, 6, 0xA);
}

void BattleAnim_StartEffect143ModeOrbitAndMetadataBurst(void) {
    UNUSED s32 pad;

    ParticleDef_CreateDefault(0, 8, 6);
    ParticleDef_CreateFull(0, 1, 4, BattleAnim_CallbackStartEffects133And134And143Descriptor44ModeOrbitSwirl, &gParticleEffectData[0x44], 0, 8, 9, 0, 0x3C, 2);
    ParticleDef_CreateFull(6, 1, 8, BattleAnim_CallbackStartEffects133And134And143Descriptor44ModeOrbitSwirl, &gParticleEffectData[0x44], 0, 8, 9, 0, 0x3C, 3);
    ParticleDef_CreateFull(6, 1, 8, BattleAnim_CallbackStartEffects133And134And143Descriptor44ModeOrbitSwirl, &gParticleEffectData[0x44], 0, 8, 9, 0, 0x3C, 3);
    ParticleDef_Create31EAC(0xE, 0xA, 0, 0xFF, 4);
    ParticleDef_CreateQuick(0x14, BattleAnim_CallbackStartEffects133And134And143Descriptor38MetadataBurstEmitter, &gParticleEffectData[0x38], 0x1A, 1, 2, 0, 0x3C, 0);
    ParticleDef_CreateAlphaMode(0x2D, 0x40, 0, 0xFF);
    ParticleDef_CreateDefault(0x32, 6, 0xA);
}

void BattleAnim_StartEffect133ModeOrbitBurstAndEffect135Followup(void) {
    ParticleDef_CreateDefault(0, 8, 6);
    ParticleDef_CreateFull(0, 4, 5, BattleAnim_CallbackStartEffects133And134And143Descriptor44ModeOrbitSwirl, &gParticleEffectData[0x44], 0, 4, 9, 0, 0x3C, 1);
    ParticleDef_CreateFull(0, 4, 5, BattleAnim_CallbackStartEffects133And134And143Descriptor44ModeOrbitSwirl, &gParticleEffectData[0x44], 0, 4, 9, 0, 0x3C, 1);
    ParticleDef_CreateFull(0x18, 1, 4, BattleAnim_CallbackStartEffects133And134And143Descriptor44ModeOrbitSwirl, &gParticleEffectData[0x44], 0, 8, 9, 0, 0x3C, 2);
    ParticleDef_CreateFull(0x1E, 1, 8, BattleAnim_CallbackStartEffects133And134And143Descriptor44ModeOrbitSwirl, &gParticleEffectData[0x44], 0, 8, 9, 0, 0x3C, 3);
    ParticleDef_CreateFull(0x1E, 1, 8, BattleAnim_CallbackStartEffects133And134And143Descriptor44ModeOrbitSwirl, &gParticleEffectData[0x44], 0, 8, 9, 0, 0x3C, 3);
    ParticleDef_Create31EAC(0x26, 0xA, 0, 0xFF, 8);
    ParticleDef_CreateQuick(0x28, BattleAnim_CallbackStartEffects133And134And143Descriptor38MetadataBurstEmitter, &gParticleEffectData[0x38], 0x18, 1, 2, 0, 0x3C, 0);
    ParticleDef_CreateBC20(0x3C, 0, 0x40, 0xA, 0xFF);
    ParticleDef_CreateAlphaMode(0x40, 0xFF, 0, 0xFF);
    ParticleSystem_SetSpawnOffset(0x50);
    BattleAnim_StartEffect135ExpandingFlashAndRisingScaleFade();
}

void BattleAnim_StartEffect122GlobalAndOwnerTintFade(void) {
    ParticleDef_CreateDefault(0, 0xFF, 0);
    ParticleDef_Create31EAC(0x14, 0, 0, 0xFF, 0x10);
}
