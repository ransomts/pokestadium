#include "fragment62.h"

void Particle_SetWhiteColor(ParticleEffectInstance* arg0) {
    Particle_SetPrimColor(arg0, 0xFF, 0xFF, 0xFF);
    Particle_SetPrimAlpha(arg0, 0xFF);
    Particle_IncrementState(arg0);
}

void Particle_StateHandler(ParticleEffectInstance* arg0) {
    switch (arg0->updateState) {
        case 0:
            break;

        case 1:
            Particle_SetWhiteColor(arg0);
            break;

        case 2:
            Particle_ApproachScaleFactor1(arg0, 3.0f, 0.025f);
            Particle_ProcessTimer80(arg0, 0x12C);
            break;

        case 3:
            if (Particle_ApproachPrimAlpha(arg0, 0x20, 0x20) != 0) {
                Particle_IncrementState(arg0);
            }
            break;

        case 4:
            Particle_ResetState(arg0);
            break;
    }

    Particle_UpdatePositionAndAccelFromYaw(arg0, 32.0f, 0x400);
}

void Particle_InitializeBasic(ParticleEffectInstance* arg0) {
    s16 sp26 = Particle_GetShortAC(arg0);

    Particle_SetScaleFactor1(arg0, 0.2f);
    Particle_SetAccelerationY(arg0, 1.0f);
    Particle_SetRotationX(arg0, RandomMod(0x10000));
    Particle_SetRotationZ(arg0, RandomMod(0x10000));
    Particle_SetRotationDeltaY(arg0, RandomMod(0x10000));
    Particle_SetSpeed(arg0, 5.0f);
    Particle_SetTimerA6(arg0, sp26 * 4);
    Particle_DisableFlag4(arg0);
    Particle_IncrementState(arg0);
}

void Particle_UpdateStateAndScale(ParticleEffectInstance* arg0) {
    switch (arg0->updateState) {
        case 1:
            Particle_InitializeBasic(arg0);
            break;

        case 2:
            if (Particle_DecrementTimerA6ToZeroWithCallback(arg0) != 0) {
                Particle_EnableFlag4(arg0);
                Particle_EnableFlag2(arg0);
            }
            break;

        case 3:
            if (Particle_ProcessTimer80(arg0, 0x32) != 0) {
                Particle_IncrementFlag2Counter(arg0);
            }
            break;

        case 4:
            if (Particle_ProcessTimer80(arg0, 0x14) != 0) {}
            break;

        case 5:
            Particle_ResetState(arg0);
            break;
    }

    switch (arg0->unk_B8) {
        case 1:
            Particle_ApproachSpeedScaled(arg0, 50.0f, 0.5f);
            Particle_AddScaledVelocityY(arg0, 1.0f);
            Particle_UpdatePositionAndAccelFromYaw(arg0, arg0->unk_74, 0x1000);
            Particle_Field94_AddX_0A578(arg0, 0x2000);
            Particle_RotateX(arg0, 0x3000);
            break;

        case 2:
            Particle_ApproachSpeedScaled(arg0, 0.0f, 1.0f);
            Particle_AddScaledVelocityY(arg0, -2.0f);
            Particle_UpdatePositionAndAccelFromYaw(arg0, arg0->unk_74, 0x1000);
            Particle_Field94_AddX_0A578(arg0, 0x2000);
            Particle_RotateX(arg0, 0x3000);
            break;
    }
}

void Particle_SetPaletteColors24(ParticleEffectInstance* arg0) {
    s16 sp2E = Particle_GetShortAC(arg0);

    Particle_SetScaleFactor1(arg0, 0.5f);
    Particle_SetSpeed(arg0, 10.0f);
    Particle_AddRotationDeltaXYZ(arg0, RandomRangeSigned(0x1000), RandomRangeSigned(0x1000), 0);
    Particle_SetTimerA6(arg0, sp2E * 4);
    SetPrimColorFromPalette(arg0, 0x24);
    SetEnvColorFromPalette(arg0, 0x24);
    Particle_DisableFlag4(arg0);
    Particle_IncrementState(arg0);
}

void Particle_HandleCollisionAndFade(ParticleEffectInstance* arg0) {
    switch (arg0->updateState) {
        case 1:
            Particle_SetPaletteColors24(arg0);
            break;

        case 2:
            if (Particle_DecrementTimerA6ToZeroWithCallback(arg0) != 0) {
                Particle_EnableFlag4(arg0);
            }
            break;

        case 3:
            Particle_ProcessTimer80(arg0, 0x46);
            break;

        case 4:
            Particle_ResetState(arg0);
            break;
    }

    if (Particle_HasFlag4(arg0) != 0) {
        Particle_ApplyB2B4AndAddAll(arg0);
        Particle_RotateX(arg0, 0x2000);
    }
}

void Particle_InitializeTwirl(ParticleEffectInstance* arg0) {
    s16 sp26 = Particle_GetShortAC(arg0);

    Particle_SetScaleFactor1(arg0, 0.12f);
    Particle_SetAccelerationY(arg0, (RandomMod(0x14) * 0.02f) + 0.25f);
    Particle_SetRotationX(arg0, RandomMod(0x10000));
    Particle_SetRotationZ(arg0, RandomMod(0x10000));
    Particle_SetSpeed(arg0, 5.0f);
    Particle_SetShortAE(arg0, RandomMod(0x800) + 0xC00);
    Particle_SetRotationDeltaX(arg0, Particle_GetRandomRotation(0x800, 0x300));
    Particle_SetShortB0(arg0, Particle_GetRandomRotation(0x800, 0x300));
    Particle_SetRotationDeltaY(arg0, RandomMod(0x10000));
    Particle_SetRotationDeltaZ(arg0, Particle_GetRandomRotation(0x800, 0x300));
    Particle_AddVelocityYScaled(arg0, RandomMod(0x1E));
    Particle_SetTimerA6(arg0, sp26 * 2);
    Particle_DisableFlag4(arg0);
    Particle_IncrementState(arg0);
}

void Particle_UpdateComplexMovement(ParticleEffectInstance* arg0) {
    switch (arg0->updateState) {
        case 1:
            Particle_InitializeTwirl(arg0);
            break;

        case 2:
            if (Particle_DecrementTimerA6ToZeroWithCallback(arg0) != 0) {
                Particle_EnableFlag4(arg0);
                Particle_EnableFlag2(arg0);
                Particle_SetTimerA6(arg0, RandomMod(0xA) + 0x1E);
            }
            break;

        case 3:
            if (Particle_DecrementTimerA6ToZeroWithCallback(arg0) != 0) {
                Particle_SetTimerA6(arg0, 8);
                Particle_IncrementFlag2Counter(arg0);
            }
            break;

        case 4:
            if (Particle_DecrementTimerA6ToZeroWithCallback(arg0) != 0) {
                Particle_SetRotationDeltaX(arg0, Particle_GetRandomRotation(0x1000, 0x600));
                Particle_SetShortB0(arg0, Particle_GetRandomRotation(0x400, 0x400));
                Particle_SetRotationDeltaZ(arg0, Particle_GetRandomRotation(0x1000, 0x600));
                arg0->unk_38.x += arg0->unk_50.x;
                arg0->unk_50.x = 0;
                arg0->unk_38.z += arg0->unk_50.z;
                arg0->unk_50.z = 0;
                Particle_IncrementFlag2Counter(arg0);
                arg0->unk_7C.y = -((RandomMod(8) * 0.1f) + 0.5f);
            }
            break;

        case 5:
            Particle_ProcessTimer80(arg0, 0x46);
            break;

        case 6:
            Particle_ClearActiveFlag(arg0);
            break;
    }

    switch (arg0->unk_B8) {
        case 1:
            Particle_ApproachSpeedScaled(arg0, 20.0f, 0.5f);
            Particle_AddScaledVelocityY(arg0, arg0->unk_7C.y);
            Particle_UpdatePositionAndAccelFromYaw(arg0, arg0->unk_74, arg0->alpha);
            break;

        case 2:
            Particle_ApproachShortAE(arg0, 0, 0x200);
            Particle_AddScaledVelocityY(arg0, arg0->unk_7C.y);
            Particle_UpdatePositionAndAccelFromYaw(arg0, arg0->unk_74, arg0->alpha);
            break;

        case 3:
            Particle_AddScaledVelocityY(arg0, arg0->unk_7C.y);
            Particle_UpdatePositionAndAccelFromYaw(arg0, 5.0f, 0x400);
            break;
    }

    if (Particle_HasFlag4(arg0) != 0) {
        Particle_AddRotationDeltaX(arg0);
        Particle_RotateY(arg0, arg0->unk_B0);
        Particle_AddRotationDeltaZ(arg0);
        if (arg0->unk_2C.y < 0.0f) {
            Particle_ClearActiveFlag(arg0);
        }
    }
}

void Particle_InitializeBurst(ParticleEffectInstance* arg0) {
    s16 sp26 = Particle_GetShortAC(arg0);
    s16 sp24 = Particle_GetShortCE(arg0);

    Particle_SetAccelerationY(arg0, 0.5f);

    switch (sp24) {
        case 0:
            Particle_SetScaleFactor1(arg0, 0.12f);
            arg0->unk_5C.y = -((RandomMod(0xA) * 0.1f) + 0.5f);
            Particle_AddVelocityYScaled(arg0, RandomMod(0x28) + 0x1E);
            Particle_SetRandomVelocityXSymmetric(arg0, 0x1E, 0);
            Particle_SetRandomVelocityZSymmetric(arg0, 0x1E, 0);
            break;

        case 1:
            Particle_SetScaleFactor1(arg0, 0.2f);
            arg0->unk_5C.y = -((RandomMod(4) * 0.1f) + 0.2f);
            Particle_AddVelocityYScaled(arg0, RandomRangeSigned(0x14) + 0x1E);
            Particle_SetRandomVelocityXSymmetric(arg0, 0xF, 5);
            Particle_SetRandomVelocityZSymmetric(arg0, 0x14, 5);
            break;
    }

    Particle_SetRotationX(arg0, RandomMod(0x10000));
    Particle_SetRotationZ(arg0, RandomMod(0x10000));
    Particle_SetSpeed(arg0, RandomMod(0x14) + 15.0f);
    Particle_SetShortAE(arg0, RandomMod(0x300) + 0x400);
    Particle_SetRotationDeltaY(arg0, RandomMod(0x10000));
    Particle_SetRotationDeltaX(arg0, Particle_GetRandomRotation(0x800, 0x400));
    Particle_SetRotationDeltaZ(arg0, Particle_GetRandomRotation(0x800, 0x400));
    Particle_SetTimerA6(arg0, sp26 * 2);
    Particle_DisableFlag4(arg0);
    Particle_IncrementState(arg0);
}

void Particle_UpdateBurstState(ParticleEffectInstance* arg0) {
    s16 sp26 = Particle_GetShortCE(arg0);

    switch (arg0->updateState) {
        case 1:
            Particle_InitializeBurst(arg0);
            break;

        case 2:
            if (Particle_DecrementTimerA6ToZeroWithCallback(arg0) != 0) {
                Particle_EnableFlag4(arg0);
                Particle_EnableFlag2(arg0);
                switch (sp26) {
                    case 0:
                        Particle_SetTimerA6(arg0, RandomMod(0x1E) + 0x32);
                        break;

                    case 1:
                        Particle_SetTimerA6(arg0, RandomMod(0x1E) + 0x64);
                        break;
                }
            }
            break;

        case 3:
            Particle_DecrementTimerA6ToZeroWithCallback(arg0);
            break;

        case 4:
            Particle_ClearActiveFlag(arg0);
            break;
    }

    if (arg0->unk_B8 == 1) {
        Particle_AddScaledVelocityY(arg0, arg0->unk_5C.y);
        Particle_UpdatePositionAndAccelFromYaw(arg0, 5.0f, 0x400);
    }

    if (Particle_HasFlag4(arg0) != 0) {
        Particle_AddRotationDeltaX(arg0);
        Particle_AddRotationDeltaY(arg0);
        Particle_AddRotationDeltaZ(arg0);
        if (arg0->unk_2C.y < 0.0f) {
            Particle_ClearActiveFlag(arg0);
        }
    }
}

void func_84340AC4(void) {
}

void RegisterParticleEffects_62_32A640(void) {
    ParticleDef_CreateNullType17(0x80, 1);
    ParticleDef_CreateQuick(0, Particle_UpdateStateAndScale, &gParticleEffectData[0x2B], 0, 0x10, 0xA, 0, 0, 0);
    ParticleDef_CreateQuick(2, Particle_UpdateStateAndScale, &gParticleEffectData[0x2B], 0, 0x10, 0xA, 0, 0, 0);
    ParticleDef_CreateQuick(4, Particle_UpdateStateAndScale, &gParticleEffectData[0x2B], 0, 0x10, 0xA, 0, 0, 0);
    ParticleDef_CreateQuick(8, Particle_UpdateStateAndScale, &gParticleEffectData[0x2B], 0, 8, 0xA, 0, 0, 0);
    ParticleSystem_AddSpawnOffset(0x3A);
    ParticleDef_CreateQuick(0, Particle_HandleCollisionAndFade, &gParticleEffectData[0x2E], 0, 0x10, 2, 0, 0, 0);
    ParticleDef_CreateQuick(0, Particle_HandleCollisionAndFade, &gParticleEffectData[0x2E], 0, 0x10, 2, 0, 0, 0);
    ParticleDef_CreateQuick(0, Particle_HandleCollisionAndFade, &gParticleEffectData[0x2E], 0, 0x10, 2, 0, 0, 0);
    ParticleDef_CreateQuick(0, Particle_HandleCollisionAndFade, &gParticleEffectData[0x2E], 0, 0x10, 2, 0, 0, 0);
}

void RegisterParticleEffect_ComplexMovement(void) {
    ParticleDef_CreateFull(0, 2, 0x14, Particle_UpdateComplexMovement, &gParticleEffectData[0x2C], 0, 4, 0xE, 0, 0, 0);
    ParticleEffect_MultiNodeSetup();
}

void RegisterParticleEffect_Burst(void) {
    ParticleDef_CreateFull(0, 2, 5, Particle_UpdateBurstState, &gParticleEffectData[0x2D], 0, 1, 0xE, 0, 0, 1);
    ParticleDef_CreateFull(0, 4, 5, Particle_UpdateBurstState, &gParticleEffectData[0x2D], 0, 1, 0xE, 0, 0, 1);
}
