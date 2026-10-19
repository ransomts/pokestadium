#include "fragment3.h"
#include "src/6A40.h"
#include "src/math_util.h"
#include "src/memory.h"
#include "src/12D80.h"

void ParticleSystem_Init(void) {
    gParticleInstances = main_pool_alloc(sizeof(ParticleEffectInstance) * 300, 0);
    bzero(gParticleInstances, sizeof(ParticleEffectInstance) * 300);
    gParticleAllocIndex = 0;

    gParticleEmitters = main_pool_alloc(sizeof(ParticleSpawner) * 128, 0);
    bzero(gParticleEmitters, sizeof(ParticleSpawner) * 128);
    gParticleEmitterNextIdx = 0;
}

s32 ParticleEmitter_Allocate(void) {
    s32 i;
    s32 var_v0 = gParticleEmitterNextIdx;
    ParticleSpawner* var_v1 = &gParticleEmitters[var_v0];

    for (i = 0; i < 0x80; i++) {
        if (var_v1->unk_2B == 0) {
            break;
        }

        var_v0++;
        if (var_v0 >= 0x80) {
            var_v0 = 0;
            var_v1 = gParticleEmitters;
        } else {
            var_v1++;
        }
    }

    if (i >= 0x80) {
        var_v1 = -1;
    } else {
        var_v1->unk_2B = 1;
    
        gParticleEmitterNextIdx = var_v0 + 1;
        if (gParticleEmitterNextIdx >= 0x80) {
            gParticleEmitterNextIdx = 0;
        }
    }
    return var_v1;
}

void ParticleEmitter_Reset(ParticleSpawner* arg0) {
    arg0->unk_28 = 0;
    arg0->unk_2B = 0;
    arg0->unk_2A = 0;
    arg0->unk_26 = arg0->unk_28;
}

s32 ParticleEmitter_Create(s32 arg0, s32 arg1, s8 arg2, f32 arg3, Vec3f arg4, Vec3s arg7, func_unk_D_8140E724_008 arg9,
                  ParticleEffectData* argA, s32 argB, u8 argC, s16 argD, u8 argE, u8 argF, u8 arg10) {
    ParticleSpawner* temp_v0 = (ParticleSpawner*)ParticleEmitter_Allocate();

    if ((s32)temp_v0 != -1) {
        temp_v0->unk_28 = arg0;
        temp_v0->unk_26 = arg1;
        temp_v0->unk_2A = arg2;
        temp_v0->unk_2C = argC;

        temp_v0->unk_00 = arg3;

        temp_v0->unk_04.x = arg4.x;
        temp_v0->unk_04.y = arg4.y;
        temp_v0->unk_04.z = arg4.z;

        temp_v0->unk_10.x = arg7.x;
        temp_v0->unk_10.y = arg7.y;
        temp_v0->unk_10.z = arg7.z;

        temp_v0->unk_18 = arg9;
        temp_v0->unk_1C = argA;
        temp_v0->unk_20 = argB;
        temp_v0->unk_24 = argD;
        temp_v0->unk_2D = argE;
        temp_v0->unk_2E = argF;
        temp_v0->unk_2F = arg10;
    }

    return (s32)temp_v0;
}

void ParticleEmitter_SpawnSimple(s32 arg0, f32 arg1, Vec3f arg2, func_unk_D_8140E724_008 arg3, ParticleEffectData* arg4, s16 arg5,
                   u8 arg6, u8 arg7) {
    Vec3s sp50;

    sp50.x = sp50.y = sp50.z = 0;

    ParticleEmitter_Create(arg0, 0, 1, arg1, arg2, sp50, arg3, arg4, 0, 0, arg5, arg6, arg7, 0);
}

void ParticleEmitter_Spawn(s32 arg0, s32 arg1, s8 arg2, f32 arg3, Vec3f arg4, func_unk_D_8140E724_008 arg7,
                   ParticleEffectData* arg8, s16 arg9, u8 argA, u8 argB) {
    Vec3s sp50;

    sp50.x = sp50.y = sp50.z = 0;

    ParticleEmitter_Create(arg0, arg1, arg2, arg3, arg4, sp50, arg7, arg8, 0, 0, arg9, argA, argB, 0);
}

void ParticleInstance_PopulateFromEmitter(ParticleEffectInstance* arg0, ParticleSpawner* arg1, s16 arg2) {
    if ((s32)arg0 != -1) {
        while (arg0 != NULL) {
            arg0->unk_28 = arg1->unk_00;

            Vec3f_Copy(&arg0->unk_68, &arg1->unk_04);
            Vec3s_CopyTo(&arg0->unk_94, &arg1->unk_10);

            arg0->unk_AC = arg2++;

            arg0->unk_08 = arg1->unk_18;
            arg0->unk_0C = arg1->unk_1C;

            arg0->targetAlpha = arg1->unk_2F;
            arg0->unk_CE = arg1->unk_2D;
            arg0->alphaStep = arg1->unk_24;
            arg0->paletteIndex = arg1->unk_2E;

            arg0 = arg0->next;
        };
    }
}

void ParticleEmitter_GenerateParticles(ParticleSpawner* arg0) {
    s16 i;
    s16 sp2C;
    ParticleEffectData* temp_v0 = arg0->unk_1C;
    s16 temp_v1 = arg0->unk_24;
    ParticleRenderSettings* unk_04 = temp_v0->unk_04.a;

    if ((temp_v0->unk_00 == 1) && (unk_04->unk_00 == 1)) {
        ParticleInstance_PopulateFromEmitter(Particle_AllocateChain(temp_v1), arg0, 0);
    } else {
        for (i = 0; i < sp2C; i++) {
            ParticleInstance_PopulateFromEmitter(Particle_AllocateInstance(), arg0, i);
        }
    }
}

void ParticleEmitter_Tick(ParticleSpawner* arg0) {
    if (arg0->unk_2C == 0) {
        ParticleEmitter_GenerateParticles(arg0);
    }
}

void ParticleEmitters_UpdateAll(void) {
    s32 i;
    ParticleSpawner* var_s0 = gParticleEmitters;

    for (i = 0; i < 0x80; i++, var_s0++) {
        if (var_s0->unk_2B != 0) {
            var_s0->unk_28--;
            if (var_s0->unk_28 < 0) {
                ParticleEmitter_Tick(var_s0);
                if (var_s0->unk_2A > 0) {
                    var_s0->unk_2A--;
                    if (var_s0->unk_2A == 0) {
                        ParticleEmitter_Reset(var_s0);
                    }
                } else {
                    var_s0->unk_28 = var_s0->unk_26;
                }
            }
        }
    }
}

void MiniFx_SetParticleRenderScale(ParticleEffectInstance* arg0) {
    gParticleScaleFactor.unk_00.x = arg0->unk_28;
    gParticleScaleFactor.unk_00.y = arg0->unk_28;
    gParticleScaleFactor.unk_00.z = arg0->unk_28;
}

void MiniFx_RetireParticle(ParticleEffectInstance* arg0) {
    if (Particle_IsInactive(arg0) != 0) {
        arg0->unk_18 = 0;
        Particle_ResetState(arg0);
        Particle_Free(arg0);
    } else {
        Particle_UpdateTransform(arg0);
    }
}

void ParticleSystem_UpdateAndRender(void) {
    s32 i;
    ParticleEffectInstance* var_s0 = gParticleInstances;

    ParticleEmitters_UpdateAll();

    for (i = 0; i < 0x12C; i++, var_s0++) {
        if (var_s0->unk_D0 != 0) {
            MiniFx_SetParticleRenderScale(var_s0);

            var_s0->unk_08(var_s0);

            MiniFx_RetireParticle(var_s0);
        }
    }
}

void ParticleRender_SetupMiniCamera(void) {
    gSPPerspNormalize(gDisplayListHead++, gMiniCameraPtr->unk_24.perspNorm);
    gSPMatrix(gDisplayListHead++, gMiniCameraPtr->unk_24.mtx, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
    gSPMatrix(gDisplayListHead++, gMiniCameraPtr->unk_60.p_mtxf, G_MTX_NOPUSH | G_MTX_MUL | G_MTX_PROJECTION);

    gMatrixBuffer = GfxAlloc(sizeof(unk_D_8140E620));
    gMatrixBufferIdx = 0;

    gSPDisplayList(gDisplayListHead++, gDL_Begin3D);

    Particle_UpdateForCamera(gMiniCameraPtr);

    gSPDisplayList(gDisplayListHead++, gDL_End3D);
}

void MiniFx_InitRandomVelocityGravityParticle(ParticleEffectInstance* arg0) {
    Vec3s sp28;
    s16 sp26 = Particle_GetShortAC(arg0);

    Particle_SetPrimColor(arg0, 0xC8, 0xAA, 0x64);
    Particle_SetEnvColor(arg0, 0x3A, 0x18, 0x18);
    Particle_SetScaleFactor1(arg0, (RandomMod(0xA) * 0.03f) + 0.15f);

    sp28.x = RandomRangeSigned(0x400) - 0x3000;
    sp28.y = (RandomRangeSigned(0x400) + (sp26 << 0xD)) - 0x3000;
    sp28.z = 0;

    Particle_AddRotationDeltaVec(arg0, sp28);
    Particle_SetSpeed(arg0, (RandomMod(0xA) * 0.3f) + 6.0f);
    Particle_SetVelocityFromRotationXY(arg0);
    Particle_SetPrimAlpha(arg0, 0xFF);
    Particle_IncrementState(arg0);
}

void MiniFx_UpdateRandomVelocityGravityParticle(ParticleEffectInstance* arg0) {
    switch (arg0->updateState) {
        case 1:
            MiniFx_InitRandomVelocityGravityParticle(arg0);
            break;

        case 2:
            if (arg0->unk_2C.y < 0.0f) {
                Particle_ClearActiveFlag(arg0);
            }
            break;
    }

    if (Particle_IsActive(arg0) != 0) {
        Particle_DecrementAccelerationYClamp(arg0, -8.0f, 1.0f);
        Particle_AddVelocityFromTarget(arg0);
    }
}

void MiniFx_InitPalette10FastRiseFadeParticle(ParticleEffectInstance* arg0) {
    Particle_SetScaleFactor1(arg0, 0.25f);
    Particle_RotateY(arg0, RandomMod(0x10000));
    Particle_SetSpeed(arg0, (2.0f * MathUtil_Random_ZeroOne()) + 4.0f);
    Particle_SetAccelerationY(arg0, (MathUtil_Random_ZeroOne() * 3.0f) + 1.0f);
    SetPrimEnvColorFromPair(arg0, 0xA);
    Particle_SetPrimAlpha(arg0, 0x64);
    Particle_SetTimerA6(arg0, 7);
    Particle_IncrementState(arg0);
}

void MiniFx_UpdatePalette10FastRiseFadeParticle(ParticleEffectInstance* arg0) {
    switch (arg0->updateState) {
        case 1:
            MiniFx_InitPalette10FastRiseFadeParticle(arg0);
            break;

        case 2:
            Particle_AnimLoopForwardComplete(arg0, 0, 7, 1, 2, 0);
            Particle_ApproachScaleFactor1(arg0, 0.8f, 0.1f);
            Particle_ApproachSpeedScaled(arg0, 1.0f, 1);
            if (Particle_DecrementTimerA6ToZero(arg0) != 0) {
                Particle_Field7C_ApproachY_0B180(arg0, 0.5f, 0.4f);
                Particle_AddVelocityYFromTarget(arg0);
            }
            break;

        case 3:
            Particle_ClearActiveFlag(arg0);
            break;
    }

    if (Particle_IsActive(arg0) != 0) {
        Particle_ApplyB278AndCopyXZAlt(arg0);
    }
}

void MiniFx_InitPalette10SlowRiseFadeParticle(ParticleEffectInstance* arg0) {
    Particle_SetScaleFactor1(arg0, 0.25f);
    Particle_RotateY(arg0, RandomMod(0x10000));
    Particle_SetSpeed(arg0, (2.0f * MathUtil_Random_ZeroOne()) + 2.0f);
    Particle_SetAccelerationY(arg0, (MathUtil_Random_ZeroOne() * 3.0f) + 1.0f);
    SetPrimEnvColorFromPair(arg0, 0xA);
    Particle_SetPrimAlpha(arg0, 0x64);
    Particle_SetTimerA6(arg0, 7);
    Particle_IncrementState(arg0);
}

void MiniFx_UpdatePalette10SlowRiseFadeParticle(ParticleEffectInstance* arg0) {
    switch (arg0->updateState) {
        case 1:
            MiniFx_InitPalette10SlowRiseFadeParticle(arg0);
            break;

        case 2:
            Particle_AnimLoopForwardComplete(arg0, 0, 7, 1, 2, 0);
            Particle_ApproachScaleFactor1(arg0, 0.8f, 0.1f);
            Particle_ApproachSpeedScaled(arg0, 1.0f, 1);
            if (Particle_DecrementTimerA6ToZero(arg0) != 0) {
                Particle_Field7C_ApproachY_0B180(arg0, 0.5f, 0.4f);
                Particle_AddVelocityYFromTarget(arg0);
            }
            break;

        case 3:
            Particle_ClearActiveFlag(arg0);
            break;
    }

    if (Particle_IsActive(arg0) != 0) {
        Particle_ApplyB278AndCopyXZAlt(arg0);
    }
}

void MiniFx_InitRandomOffsetPalette10RiseFadeParticle(ParticleEffectInstance* arg0) {
    Particle_SetScaleFactor1(arg0, 0.5f);
    Particle_SetRandomVelocityXYZ(arg0, 3, 0, 3);
    Particle_RotateY(arg0, RandomMod(0x10000));
    Particle_SetSpeed(arg0, (MathUtil_Random_ZeroOne() * 3.0f) + 3.0f);
    Particle_SetAccelerationY(arg0, (2.0f * MathUtil_Random_ZeroOne()) + 4.0f);
    SetPrimEnvColorFromPair(arg0, 0xA);
    Particle_SetPrimAlpha(arg0, 0x64);
    Particle_SetTimerA6(arg0, 7);
    Particle_IncrementState(arg0);
}

void MiniFx_UpdateRandomOffsetPalette10RiseFadeParticle(ParticleEffectInstance* arg0) {
    switch (arg0->updateState) {
        case 1:
            MiniFx_InitRandomOffsetPalette10RiseFadeParticle(arg0);
            break;

        case 2:
            Particle_AnimLoopForwardComplete(arg0, 0, 7, 1, 2, 0);
            Particle_ApproachScaleFactor1(arg0, 1.0f, 0.05f);
            Particle_ApproachSpeedScaled(arg0, 1.0f, 1);
            if (Particle_DecrementTimerA6ToZero(arg0) != 0) {
                Particle_Field7C_ApproachY_0B180(arg0, 1.0f, 0.2f);
                Particle_AddVelocityYFromTarget(arg0);
            }
            break;

        case 3:
            Particle_ClearActiveFlag(arg0);
            break;
    }

    if (Particle_IsActive(arg0) != 0) {
        Particle_ApplyB278AndCopyXZAlt(arg0);
    }
}

void MiniFx_InitSurfaceCrossingGravityParticle(ParticleEffectInstance* arg0) {
    Vec3s sp28;

    Particle_SetPrimColor(arg0, 0xC8, 0xAA, 0x64);
    Particle_SetEnvColor(arg0, 0x3A, 0x18, 0x18);
    Particle_SetScaleFactor1(arg0, (MathUtil_Random_ZeroOne() * 0.1f) + 0.1f);

    sp28.x = RandomRangeSigned(0x800) - 0x3800;
    sp28.y = RandomRangeSigned(0x1000) + 0x8000;
    sp28.z = 0;

    Particle_AddRotationDeltaVec(arg0, sp28);
    Particle_SetSpeed(arg0, (RandomMod(0xA) * 0.3f) + 6.0f);
    Particle_SetVelocityFromRotationXY(arg0);
    Particle_SetPrimAlpha(arg0, 0xFF);
    Particle_IncrementState(arg0);
}

void MiniFx_UpdateSurfaceCrossingGravityParticle(ParticleEffectInstance* arg0) {
    switch (arg0->updateState) {
        case 1:
            MiniFx_InitSurfaceCrossingGravityParticle(arg0);
            break;

        case 2:
            if (arg0->unk_50.y < 0.0f) {
                Particle_ClearActiveFlag(arg0);
            }
            break;
    }

    if (Particle_IsActive(arg0) != 0) {
        if (arg0->unk_2C.y > 0.0f) {
            Particle_EnableFlag4(arg0);
        } else {
            Particle_DisableFlag4(arg0);
        }
        Particle_DecrementAccelerationYClamp(arg0, -8.0f, 1.0f);
        Particle_AddVelocityFromTarget(arg0);
    }
}

void MiniFx_InitPalette17DelayedRevealFallParticle(ParticleEffectInstance* arg0) {
    Vec3s sp28;
    s16 sp26 = Particle_GetShortAC(arg0);

    Particle_GetShortCE(arg0);

    sp28.x = RandomMod(0x10000);
    sp28.y = RandomMod(0x10000);
    sp28.z = 0;

    Particle_SetRotationFromVec3s(arg0, sp28);
    Particle_SetSpeed(arg0, 0.0f);
    Particle_SetAcceleration(arg0, 0);
    SetPrimEnvColorFromPair(arg0, 0x17);
    Particle_SetScaleFactor1(arg0, 0.0f);
    Particle_SetScaleFactor2(arg0, 0.6f);
    Particle_SetScaleFactor3(arg0, 0.1f);
    Particle_SetRandomVelocityXSymmetric(arg0, 0x14, 0xA);
    Particle_SetRandomVelocityYOffset(arg0, 0xF, 0xF);
    Particle_SetRandomVelocityZSymmetric(arg0, 0x14, 0xA);
    Particle_SetTimerA6(arg0, sp26);
    Particle_DisableFlag4(arg0);
    Particle_IncrementState(arg0);
}

void MiniFx_UpdatePalette17DelayedRevealFallParticle(ParticleEffectInstance* arg0) {
    switch (arg0->updateState) {
        case 1:
            MiniFx_InitPalette17DelayedRevealFallParticle(arg0);
            break;

        case 2:
            if (Particle_DecrementTimerA6ToZeroWithCallback(arg0) != 0) {
                Particle_EnableFlag4(arg0);
            }
            break;

        case 3:
            if (Particle_ApproachScaleFactor2WithCallback(arg0) != 0) {
                Particle_SetScaleFactor2(arg0, 0.0f);
            }
            break;

        case 4:
            Particle_ApproachScaleFactor2WithCallback(arg0);
            break;

        case 5:
            Particle_ClearActiveFlag(arg0);
            break;
    }

    if (Particle_HasFlag4(arg0) != 0) {
        Particle_FallAccelerateAndCheckGround(arg0);
        if (arg0->unk_2C.y < 0.0f) {
            Particle_ClearActiveFlag(arg0);
        }
    }
}

void MiniFx_InitPalette17SmallDelayedRevealFallParticle(ParticleEffectInstance* arg0) {
    Vec3s sp28;
    s16 sp26 = Particle_GetShortAC(arg0);

    sp28.x = RandomMod(0x10000);
    sp28.y = RandomMod(0x10000);
    sp28.z = 0;

    Particle_SetRotationFromVec3s(arg0, sp28);
    Particle_SetSpeed(arg0, 0.0f);
    Particle_SetAcceleration(arg0, 0.0f);
    SetPrimEnvColorFromPair(arg0, 0x17);
    Particle_SetScaleFactor1(arg0, 0.0f);
    Particle_SetScaleFactor2(arg0, 0.2f);
    Particle_SetScaleFactor3(arg0, 0.035f);
    Particle_SetRandomVelocityXSymmetric(arg0, 7, 3);
    Particle_SetRandomVelocityYOffset(arg0, 0x14, 0xA);
    Particle_SetRandomVelocityZSymmetric(arg0, 7, 3);
    Particle_SetTimerA6(arg0, sp26);
    Particle_DisableFlag4(arg0);
    Particle_IncrementState(arg0);
}

void MiniFx_UpdatePalette17SmallDelayedRevealFallParticle(ParticleEffectInstance* arg0) {
    switch (arg0->updateState) {
        case 1:
            MiniFx_InitPalette17SmallDelayedRevealFallParticle(arg0);
            break;

        case 2:
            if (Particle_DecrementTimerA6ToZeroWithCallback(arg0) != 0) {
                Particle_EnableFlag4(arg0);
            }
            break;

        case 3:
            if (Particle_ApproachScaleFactor2WithCallback(arg0) != 0) {
                Particle_SetScaleFactor2(arg0, 0.0f);
            }
            break;

        case 4:
            Particle_ApproachScaleFactor2WithCallback(arg0);
            break;

        case 5:
            Particle_ClearActiveFlag(arg0);
            break;
    }

    if (Particle_HasFlag4(arg0) != 0) {
        Particle_FallAccelerateAndCheckGround(arg0);
        if (arg0->unk_2C.y < 0.0f) {
            Particle_ClearActiveFlag(arg0);
        }
    }
}

void MiniFx_InitCoolGravityParticle(ParticleEffectInstance* arg0) {
    Vec3s sp30;

    Particle_SetPrimColor(arg0, 0xFF, 0xFF, 0xFF);
    Particle_SetEnvColor(arg0, 0x64, 0xC8, 0xFF);
    Particle_SetScaleFactor1(arg0, (MathUtil_Random_ZeroOne() * 0.2f) + 0.3f);

    sp30.x = RandomRangeSigned(0x1800) - 0x3000;
    sp30.y = RandomRangeSigned(0x10000);
    sp30.z = 0;

    Particle_AddRotationDeltaVec(arg0, sp30);

    Particle_AddVelocityScaledXYZ(arg0, RandomRangeSigned(0xA) * 0.1f, RandomMod(0xA) * 0.25f, RandomRangeSigned(0xA) * 0.1f);
    Particle_SetSpeed(arg0, (RandomMod(5) * 0.35f) + 4.0f);
    Particle_SetVelocityFromRotationXY(arg0);
    Particle_SetPrimAlpha(arg0, 0xFF);
    Particle_IncrementState(arg0);
}

void MiniFx_UpdateCoolGravityParticle(ParticleEffectInstance* arg0) {
    switch (arg0->updateState) {
        case 1:
            MiniFx_InitCoolGravityParticle(arg0);
            break;

        case 2:
            if (arg0->unk_50.y < -2.5f) {
                Particle_ClearActiveFlag(arg0);
            }
            break;
    }

    if (Particle_IsActive(arg0) != 0) {
        Particle_DecrementAccelerationYClamp(arg0, -8.0f, 0.8f);
        Particle_AddVelocityFromTarget(arg0);
    }
}

void MiniFx_BuildParticleRenderListVariantA(Gfx* arg0, unk_D_86002F34_000_014* arg1, UNUSED u16 arg2) {
    gDPPipeSync(arg0++);

    gDPSetPrimColor(arg0++, 0, 0xB4, 255, 255, 255, 128);
    gDPSetEnvColor(arg0++, 255, 255, 255, 255);
    gDPSetCombineLERP(arg0++, TEXEL0, TEXEL1, PRIM_LOD_FRAC, TEXEL1, TEXEL0, TEXEL1, PRIMITIVE, TEXEL1, 0, 0, 0,
                      COMBINED, COMBINED, 0, SHADE, 0);

    gDPLoadTextureTile(arg0++, arg1->unk_00, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 0, 0, 0, 31, 31, 0,
                       G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, 5, 5, 12, G_TX_NOLOD);

    Gfx_ScrollTextureToDL(arg0++, 0xA, 0xE, 0x20, 0x20);

    gDPLoadMultiTile(arg0++, arg1->unk_04, 0x0100, 1, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 0, 0, 0, 31, 31, 0,
                     G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, 5, 5, 1, G_TX_NOLOD);

    Gfx_ScrollTexture1ToDL(arg0++, 5, 7, 0x20, 0x20);

    gSPEndDisplayList(arg0++);
}

void MiniFx_GraphNodeBuildParticleRenderListVariantA(s32 arg0, arg1_func_87902F80* arg1) {
    if (arg0 == 2) {
        arg1->unk_18 = GfxAlloc(sizeof(Gfx) * 30);
        MiniFx_BuildParticleRenderListVariantA(arg1->unk_18, arg1->unk_00.unk_14, gAnimationFrame);
    }
}

void MiniFx_BuildParticleRenderListVariantB(Gfx* arg0, unk_D_86002F34_000_014* arg1, UNUSED u16 arg2) {
    gDPPipeSync(arg0++);

    gDPSetPrimColor(arg0++, 0, 0xC8, 255, 255, 255, 180);
    gDPSetEnvColor(arg0++, 255, 255, 255, 255);
    gDPSetCombineLERP(arg0++, TEXEL0, TEXEL1, PRIM_LOD_FRAC, TEXEL1, TEXEL0, TEXEL1, PRIMITIVE, TEXEL1, 0, 0, 0,
                      COMBINED, COMBINED, 0, SHADE, 0);

    gDPLoadTextureTile(arg0++, arg1->unk_00, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 0, 0, 0, 31, 31, 0,
                       G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, 5, 5, 15, 1);

    Gfx_ScrollTextureToDL(arg0++, 2, 6, 0x20, 0x20);

    gDPLoadMultiTile(arg0++, arg1->unk_04, 0x0100, 1, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 0, 0, 0, 31, 31, 0,
                     G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, 5, 5, 1, G_TX_NOLOD);

    Gfx_ScrollTexture1ToDL(arg0++, -2, 0xC, 0x20, 0x20);

    gSPEndDisplayList(arg0++);
}

void MiniFx_GraphNodeBuildParticleRenderListVariantB(s32 arg0, arg1_func_87902F80* arg1) {
    if (arg0 == 2) {
        arg1->unk_18 = GfxAlloc(sizeof(Gfx) * 30);
        MiniFx_BuildParticleRenderListVariantB(arg1->unk_18, arg1->unk_00.unk_14, gAnimationFrame);
    }
}
