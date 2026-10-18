#include "fragment62.h"
#include "src/math_util.h"

void ParticleEffect_Type0_Stage1(ParticleEffectInstance* arg0) {
    s16 sp26 = Particle_GetShortAC(arg0);
    s16 sp24 = Particle_GetShortCF(arg0);

    Particle_SetScaleFactor1(arg0, (RandomMod(0xA) * 0.01f) + 0.05f);
    Particle_SetAccelerationY(arg0, (RandomMod(0x1E) * 0.1f) + 1.0f);
    Particle_SetRotationDeltaY(arg0, RandomMod(0x10000));
    Particle_SetSpeed(arg0, 5.0f);
    Particle_SetAcceleration(arg0, RandomMod(0xF) + 5.0f);
    Particle_SetShortAE(arg0, RandomModPlus(0x1000, 0x800));
    SetPrimEnvColorFromPair(arg0, sp24);
    Particle_SetTimerA6(arg0, sp26);
    Particle_DisableFlag4(arg0);
    Particle_IncrementState(arg0);
}

void ParticleEffect_Type0_Main(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            ParticleEffect_Type0_Stage1(arg0);
            break;

        case 2:
            if (Particle_DecrementTimerA6ToZeroWithCallback(arg0) != 0) {
                Particle_EnableFlag4(arg0);
                Particle_SetTimerA6(arg0, 0xA);
            }
            break;

        case 3:
            if (Particle_DecrementTimerA6ToZero(arg0) != 0) {
                Particle_AnimLoopForwardComplete(arg0, 0, 3, 1, 1, 0);
            }
            break;

        case 4:
            Particle_ResetState(arg0);
            break;
    }

    if (Particle_HasFlag4(arg0) != 0) {
        Particle_AddVelocityYFromTarget(arg0);
        Particle_ApproachSpeedScaled(arg0, arg0->unk_78, 0.5f);
        Particle_UpdatePositionAndAccelFromYaw(arg0, arg0->unk_74, arg0->unk_AE);
    }
}

void ParticleEffect_Type1_Stage1(ParticleEffectInstance* arg0, s16 arg1) {
    s16 sp2E = Particle_GetShortAC(arg0);

    Particle_SetByteCA(arg0, 7);
    Particle_SetScaleFactor1(arg0, 0.1f);
    Particle_AddRotationDeltaXYZ(arg0, RandomRangeSigned(0xC00), RandomRangeSigned(0x1000), 0);
    SetRandomEnvColor(arg0);
    Particle_SetSpeed(arg0, (RandomMod(6) * 0.5f) + 4.0f);
    Particle_SetTimerA6(arg0, sp2E * 2);
    Particle_DisableFlag4(arg0);
    Particle_IncrementState(arg0);
}

void ParticleEffect_Type1_Main(ParticleEffectInstance* arg0) {
    s16 temp_a1 = Particle_GetShortCF(arg0);

    switch (arg0->unk_B2) {
        case 1:
            ParticleEffect_Type1_Stage1(arg0, temp_a1);
            break;

        case 2:
            if (Particle_DecrementTimerA6ToZeroWithCallback(arg0) != 0) {
                Particle_SetTimerA6(arg0, RandomMod(0xA) + 0x19);
                Particle_EnableFlag4(arg0);
            }
            break;

        case 3:
            Particle_ApproachScaleFactor1(arg0, 0.15f, 0.01f);
            Particle_ApplyB2B4AndAddAll(arg0);
            if ((Particle_DecrementTimerA6ToZero(arg0) != 0) && (Particle_ApproachPrimAlpha(arg0, 0x20, 0x20) != 0)) {
                Particle_IncrementState(arg0);
            }
            break;

        case 4:
            Particle_ResetState(arg0);
            break;
    }
}

void ParticleEffect_Type2_Stage1(ParticleEffectInstance* arg0) {
    UNUSED s32 pad[3];
    s16 sp22 = Particle_GetShortAC(arg0);

    Particle_GetShortCF(arg0);
    Particle_SetScaleFactor1(arg0, 0.05f);
    Particle_SetRandomVelocityXYZ(arg0, 4, 2, 2);
    func_8140A578(arg0, RandomRangeSignedPlus(0x200, 0xE00));
    Particle_SetRotationDeltaX(arg0, RandomMod(0x1000) + 0x100);
    Particle_SetShortB0(arg0, -0x1800 - RandomMod(0x1000));
    Particle_RotateY(arg0, RandomRangeSigned(0x3000));
    Particle_SetSpeed(arg0, (RandomMod(0xF) * 0.1f) + 1.0f);
    SetRandomEnvColor(arg0);
    Particle_SetTimerA6(arg0, sp22 * 2);
    Particle_DisableFlag4(arg0);
    Particle_IncrementState(arg0);
}

void ParticleEffect_Type2_RotationAdjust(ParticleEffectInstance* arg0) {
    if (arg0->unk_B8 == 1) {
        Particle_DecreaseRotationXTowards(arg0, arg0->unk_B0, arg0->unk_9A.x);
        Particle_ApplyB2B4AndAddAll(arg0);
    }
}

void ParticleEffect_Type2_Main(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            ParticleEffect_Type2_Stage1(arg0);
            break;

        case 2:
            if (Particle_DecrementTimerA6ToZeroWithCallback(arg0) != 0) {
                Particle_EnableFlag2(arg0);
                Particle_EnableFlag4(arg0);
                Particle_SetTimerA6(arg0, RandomMod(0xA) + 8);
            }
            break;

        case 3:
            Particle_ApproachScaleFactor1(arg0, 0.15f, 0.02f);
            if (Particle_DecrementTimerA6ToZero(arg0) != 0) {
                Particle_AnimLoopForwardComplete(arg0, 0, 3, 1, 1, 0);
            }
            break;

        case 4:
            Particle_ClearActiveFlag(arg0);
            break;
    }

    if (Particle_HasFlag4(arg0) != 0) {
        ParticleEffect_Type2_RotationAdjust(arg0);
    }
}

void ParticleEffect_Type3_Stage1(ParticleEffectInstance* arg0) {
    s16 sp56 = Particle_GetShortAC(arg0);
    f32 var_fa0;
    UNUSED s32 pad[2];
    Vec3f sp3C;
    Vec3f sp30;
    s16 sp2E;

    Particle_SetByteCA(arg0, 7);
    Particle_SetScaleFactor1(arg0, 0.1f);
    Particle_SetScaleFactor2(arg0, 0.2f);
    Particle_SetScaleFactor3(arg0, 0.02f);
    GetPrimaryEffectCenterOrNode(&sp3C);
    GetSecondaryEntityNode9Position(&sp30);
    var_fa0 = sp30.x - sp3C.x;
    if (var_fa0 <= 0.0f) {
        var_fa0 = -var_fa0;
    }
    sp2E = -MathUtil_Atan2s(var_fa0, sp30.y - sp3C.y);
    Particle_AddRotationDeltaXYZ(arg0, sp2E + RandomRangeSigned(0x800), RandomRangeSigned(0x800), 0);
    Particle_SetRandomVelocityXYZ(arg0, 4, 2, 2);
    SetRandomEnvColor(arg0);
    Particle_SetSpeed(arg0, (RandomMod(6) * 0.5f) + 5.0f);
    Particle_SetTimerA6(arg0, sp56 * 2);
    Particle_DisableFlag4(arg0);
    Particle_IncrementState(arg0);
}

void ParticleEffect_Type3_Main(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            ParticleEffect_Type3_Stage1(arg0);
            break;

        case 2:
            if (Particle_DecrementTimerA6ToZeroWithCallback(arg0) != 0) {
                Particle_SetTimerA6(arg0, RandomMod(0x14) + 0xF);
                Particle_EnableFlag4(arg0);
            }
            break;

        case 3:
            Particle_ApproachScaleFactor2(arg0);
            Particle_ApplyB2B4AndAddAll(arg0);
            if (Particle_DecrementTimerA6ToZero(arg0) != 0) {
                Particle_AnimLoopForwardComplete(arg0, 0, 3, 1, 1, 0);
            }
            break;

        case 4:
            Particle_ResetState(arg0);
            break;
    }
}

void ParticleEffect_Type4_Stage1(ParticleEffectInstance* arg0) {
    UNUSED s32 pad[2];
    f32 temp_fv0;
    Vec3f sp40;
    Vec3f sp34;
    s16 sp32;
    s16 sp30 = Particle_GetShortAC(arg0);
    s16 sp2E = Particle_GetShortCE(arg0);

    Particle_SetByteCA(arg0, 7);
    Particle_SetScaleFactor1(arg0, 0.1f);
    GetPrimaryEffectCenterOrNode(&sp40);
    GetSecondaryEntityNode9Position(&sp34);

    temp_fv0 = sp34.x - sp40.x;
    if (temp_fv0 <= 0.0f) {
        temp_fv0 = -temp_fv0;
    }

    sp32 = MathUtil_Atan2s(temp_fv0, sp34.y - sp40.y) * -1;
    Particle_RotateY(arg0, RandomRangeSigned(0x400));

    switch (sp2E) {
        case 0:
            Particle_SetShortAE(arg0, sp32 + 0x800);
            Particle_SetShortB0(arg0, 0x1800);
            break;

        case 1:
            Particle_SetShortAE(arg0, sp32 - 0x1000);
            Particle_SetShortB0(arg0, 0x1000);
            break;

        case 2:
            Particle_SetShortAE(arg0, sp32 + 0xC00);
            Particle_SetShortB0(arg0, -0x1400);
            break;

        case 3:
            Particle_SetShortAE(arg0, sp32 - 0xA00);
            Particle_SetShortB0(arg0, -0x2000);
            break;
    }

    Particle_SetSpeed(arg0, 5.25f);
    SetRandomEnvColor(arg0);
    Particle_SetTimerA6(arg0, sp30 * 2);
    Particle_DisableFlag4(arg0);
    Particle_IncrementState(arg0);
}

void ParticleEffect_Type4_PostStage(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B8) {
        case 1:
            if (Particle_StartTimer2(arg0, 2) != 0) {
                Particle_IncrementFlag2Counter(arg0);
                func_8140A578(arg0, arg0->unk_AE);
            }
            break;

        case 2:
            Particle_RotateX(arg0, arg0->unk_B0);
            break;
    }

    if (arg0->unk_B8 > 0) {
        Particle_ApplyB568AndAddAll(arg0);
    }
}

void ParticleEffect_Type4_Main(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            ParticleEffect_Type4_Stage1(arg0);
            break;

        case 2:
            if (Particle_DecrementTimerA6ToZeroWithCallback(arg0) != 0) {
                Particle_EnableFlag2(arg0);
                Particle_EnableFlag4(arg0);
                Particle_SetTimerA6(arg0, 0x1E);
            }
            break;

        case 3:
            Particle_DecrementTimerA6ToZeroWithCallback(arg0);
            break;

        case 4:
            Particle_ClearActiveFlag(arg0);
            break;
    }

    if (Particle_HasFlag4(arg0) != 0) {
        ParticleEffect_Type4_PostStage(arg0);
    }
}

void ParticleEffect_Type5_Stage1(ParticleEffectInstance* arg0) {
    s16 sp4E = Particle_GetShortCE(arg0);
    Vec3f sp40;
    Vec3f sp34;
    s16 temp_v1;

    Particle_SetByteCA(arg0, 7);
    Particle_SetScaleFactor1(arg0, 0.1f);
    Particle_SetScaleFactor2(arg0, 0.1f);
    GetPrimaryEffectCenterOrNode(&sp40);
    GetSecondaryEntityNode9Position(&sp34);

    temp_v1 = Vec3f_AngleXTo(sp40, sp34);

    switch (sp4E) {
        case 0:
            func_8140A578(arg0, temp_v1 + 0x2000);
            Particle_RotateY(arg0, -0x4000);
            break;

        case 1:
            func_8140A578(arg0, temp_v1 + 0x6000);
            Particle_RotateY(arg0, -0x4000);
            break;
    }

    SetPrimEnvColorFromPair(arg0, Particle_GetShortCF(arg0));
    Particle_IncrementState(arg0);
}

void ParticleEffect_Type5_Main(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            ParticleEffect_Type5_Stage1(arg0);
            break;

        case 2:
            Particle_ApproachPrimAlphaWithCallback(arg0, 0xFF, 4);
            break;

        case 3:
            Particle_ProcessTimer80(arg0, 0x46);
            break;

        case 4:
            Particle_ApproachPrimAlphaWithCallback(arg0, 0, 0x10);
            break;

        case 5:
            Particle_ResetState(arg0);
            break;
    }

    Particle_ApproachScaleFactor1(arg0, 50.0f, 0.2f);
    Particle_ApproachScaleFactor3(arg0, 1.0f, 0.1f);
}

void ParticleEffect_SmallGlow_Stage1(ParticleEffectInstance* arg0) {
    switch (Particle_GetShortCE(arg0)) {
        case 0:
            Particle_SetScaleFactor1(arg0, 0.5f);
            Particle_SetScaleFactor2(arg0, 1.2f);
            Particle_SetScaleFactor3(arg0, 0.1f);
            break;

        case 1:
            Particle_SetScaleFactor1(arg0, 0.3f);
            Particle_SetScaleFactor2(arg0, 0.8f);
            Particle_SetScaleFactor3(arg0, 0.05f);
            break;
    }

    SetPrimEnvColorFromPair(arg0, 0x26);
    Particle_IncrementState(arg0);
}

void ParticleEffect_SmallGlow(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            ParticleEffect_SmallGlow_Stage1(arg0);
            break;

        case 2:
            Particle_ApproachScaleFactor2(arg0);
            Particle_AnimLoopForwardComplete(arg0, 0, 7, 1, 2, 0);
            Particle_ApproachPrimAlpha(arg0, 0x20, 8);
            break;

        case 3:
            Particle_ClearActiveFlag(arg0);
            break;
    }
}

void ParticleEffect_SlowGlow_Stage1(ParticleEffectInstance* arg0) {
    UNUSED s32 pad;

    Particle_GetShortAC(arg0);
    Particle_SetScaleFactor1(arg0, 0.5f);
    Particle_AddRotationDeltaXYZ(arg0, RandomMod(0x10000), RandomMod(0x10000), 0);
    Particle_SetSpeed(arg0, 1.0f);
    SetPrimEnvColorFromPair(arg0, 0x27);
    Particle_IncrementState(arg0);
}

void ParticleEffect_ComplexExplosion_Stage2(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            ParticleEffect_SlowGlow_Stage1(arg0);
            break;

        case 2:
            Particle_ApproachScaleFactor1(arg0, 0.3f, 0.05f);
            Particle_ApproachPrimAlpha(arg0, 0x20, 0x10);
            Particle_ApproachSpeedScaled(arg0, 0.5f, 0.05f);
            Particle_ApplyB2B4AndAddAll(arg0);
            Particle_AddVelocityYScaled(arg0, -1.0f);
            Particle_ProcessTimer80(arg0, 0x10);
            break;

        case 3:
            Particle_ClearActiveFlag(arg0);
            break;
    }
}

void ParticleEffect_DirectionalBurst_Stage1(ParticleEffectInstance* arg0) {
    s16 sp26 = Particle_GetShortCE(arg0);

    Particle_SetScaleFactor1(arg0, 0.6f);

    if (sp26 == 1) {
        Particle_AddVelocityBackward(arg0, 6.0f);
    }

    SetPrimEnvColorFromPair(arg0, 0x28);
    Particle_SetPrimAlpha(arg0, 0xC8);
    Particle_IncrementState(arg0);
}

void ParticleEffect_DirectionalBurst(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            ParticleEffect_DirectionalBurst_Stage1(arg0);
            break;

        case 2:
            if (Particle_ApproachPrimAlpha(arg0, 0x80, 0x20) != 0) {
                Particle_IncrementState(arg0);
            }
            break;

        case 3:
            Particle_ResetState(arg0);
            break;
    }

    Particle_ApproachScaleFactor1(arg0, 0.35f, 0.05f);
}

void ParticleEffect_FastFlash(ParticleEffectInstance* arg0) {
    Particle_SetScaleFactor1(arg0, 0.7f);
    Particle_SetSpeed(arg0, 12.0f);
    SetPrimEnvColorFromPair(arg0, 0x28);
    Particle_SetPrimAlpha(arg0, 0xFF);
    Particle_IncrementState(arg0);
}

void ParticleEffect_ComplexExplosion(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            ParticleEffect_FastFlash(arg0);
            break;

        case 2:
            Particle_CreateChildParticles(arg0, ParticleEffect_DirectionalBurst, &gParticleEffectData[8], 1, 0, 0);
            Particle_CreateChildParticles(arg0, ParticleEffect_DirectionalBurst, &gParticleEffectData[8], 1, 0, 1);
            ParticleNode_CreateMultiple(arg0, ParticleEffect_ComplexExplosion_Stage2, &gParticleEffectData[0xA], 4);
            Particle_ProcessTimer80(arg0, 0x14);
            break;

        case 3:
            Particle_ResetState(arg0);
            break;
    }

    Particle_ApplyB2B4AndAddAll(arg0);
}

void ParticleEffect_SlowGlow(ParticleEffectInstance* arg0) {
    UNUSED s32 pad;

    Particle_GetShortAC(arg0);
    Particle_SetScaleFactor1(arg0, 0.2f);
    Particle_AddRotationDeltaXYZ(arg0, RandomMod(0x10000), RandomMod(0x10000), 0);
    Particle_SetSpeed(arg0, 0.5f);
    SetPrimEnvColorFromPair(arg0, 0x27);
    Particle_IncrementState(arg0);
}

void ParticleEffect_FadeOut(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            ParticleEffect_SlowGlow(arg0);
            break;

        case 2:
            Particle_ApproachScaleFactor1(arg0, 0.1f, 0.02f);
            Particle_ApproachPrimAlpha(arg0, 0x20, 0xC);
            Particle_ApplyB2B4AndAddAll(arg0);
            Particle_AddVelocityYScaled(arg0, -0.5f);
            Particle_ProcessTimer80(arg0, 0x10);
            break;

        case 3:
            Particle_ClearActiveFlag(arg0);
            break;
    }
}

void ParticleEffect_GravityVariant(ParticleEffectInstance* arg0) {
    s16 sp26 = Particle_GetShortCE(arg0);

    Particle_SetScaleFactor1(arg0, 0.2f);

    switch (sp26) {
        case 1:
            Particle_AddVelocityBackward(arg0, 3.0f);
            break;

        case 2:
            Particle_AddVelocityBackward(arg0, 6.0f);
            break;
    }

    SetPrimEnvColorFromPair(arg0, 0x28);
    Particle_SetPrimAlpha(arg0, 0xC8);
    Particle_IncrementState(arg0);
}

void ParticleEffect_GravityWithColor(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            ParticleEffect_GravityVariant(arg0);
            break;

        case 2:
            if (Particle_ApproachPrimAlpha(arg0, 0x80, 0x20) != 0) {
                Particle_IncrementState(arg0);
            }
            break;

        case 3:
            Particle_ResetState(arg0);
            break;
    }

    Particle_ApproachScaleFactor1(arg0, 0.1f, 0.02f);
}

void ParticleEffect_HighSpeedFlash(ParticleEffectInstance* arg0) {
    Particle_SetScaleFactor1(arg0, 0.2f);
    Particle_SetSpeed(arg0, 10.0f);
    SetPrimEnvColorFromPair(arg0, 0x28);
    Particle_SetPrimAlpha(arg0, 0xFF);
    Particle_IncrementState(arg0);
}

void ParticleEffect_HighSpeedFlash_Main(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            ParticleEffect_HighSpeedFlash(arg0);
            break;

        case 2:
            Particle_CreateChildParticles(arg0, ParticleEffect_GravityWithColor, &gParticleEffectData[8], 1, 0, 0);
            Particle_CreateChildParticles(arg0, ParticleEffect_GravityWithColor, &gParticleEffectData[8], 1, 0, 1);
            Particle_CreateChildParticles(arg0, ParticleEffect_GravityWithColor, &gParticleEffectData[8], 1, 0, 2);
            ParticleNode_CreateMultiple(arg0, ParticleEffect_FadeOut, &gParticleEffectData[0xA], 4);
            Particle_ProcessTimer80(arg0, 0x20);
            break;

        case 3:
            Particle_ResetState(arg0);
            break;
    }
    Particle_ApplyB2B4AndAddAll(arg0);
}

void ParticleEffect_FadeOut_Stage1(ParticleEffectInstance* arg0) {
    UNUSED s32 pad[3];
    s16 sp22 = Particle_GetShortAC(arg0);
    s16 sp20 = Particle_GetShortCF(arg0);

    Particle_SetScaleFactor1(arg0, 0.25f);
    Particle_SetRandomVelocityXYZ(arg0, 4, 2, 2);
    func_8140A578(arg0, RandomRangeSignedPlus(0x200, -0xE00));
    Particle_SetRotationDeltaX(arg0, RandomMod(0x400) + 0x100);
    Particle_SetShortB0(arg0, RandomMod(0x1000) + 0x1000);
    Particle_RotateY(arg0, RandomRangeSigned(0x1800));
    Particle_SetSpeed(arg0, (RandomMod(0x28) * 0.1f) + 1.0f);
    SetPrimEnvColorFromPair(arg0, sp20);
    Particle_SetPrimAlpha(arg0, 0xC8);
    Particle_SetTimerA6(arg0, sp22 * 2);
    Particle_DisableFlag4(arg0);
    Particle_IncrementState(arg0);
}

void ParticleEffect_GravityVariant_Stage2(ParticleEffectInstance* arg0) {
    if (arg0->unk_B8 == 1) {
        Particle_ApproachRotationXWrapToTarget(arg0, arg0->unk_B0, arg0->unk_9A.x);
        Particle_ApplyB2B4AndAddAll(arg0);
        Particle_AddVelocityYScaled(arg0, -0.2f);
    }
}

void ParticleEffect_GravityVariant_Main(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            ParticleEffect_FadeOut_Stage1(arg0);
            break;

        case 2:
            if (Particle_DecrementTimerA6ToZeroWithCallback(arg0) != 0) {
                Particle_EnableFlag2(arg0);
                Particle_EnableFlag4(arg0);
            }
            break;

        case 3:
            Particle_ApproachScaleFactor1(arg0, 0.7f, 0.1f);
            Particle_AnimLoopForwardComplete(arg0, 0, 7, 1, 2, 0);
            break;

        case 4:
            Particle_ClearActiveFlag(arg0);
            break;
    }

    if (Particle_HasFlag4(arg0) != 0) {
        ParticleEffect_GravityVariant_Stage2(arg0);
    }
}

void ParticleEffect_LargeBurst_Stage1(ParticleEffectInstance* arg0) {
    s16 sp26 = Particle_GetShortAC(arg0);

    Particle_SetScaleFactor1(arg0, 0.75f - (sp26 * 0.1f));
    Particle_SetSpeed(arg0, 10.0f);
    SetPrimEnvColorFromPair(arg0, 0x28);
    Particle_SetPrimAlpha(arg0, (0xFF - (sp26 << 5)) & 0xFF);
    Particle_SetTimerA6(arg0, sp26 + 1);
    Particle_DisableFlag4(arg0);
    Particle_IncrementState(arg0);
}

void ParticleEffect_LargeBurst(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            ParticleEffect_LargeBurst_Stage1(arg0);
            break;

        case 2:
            if (Particle_DecrementTimerA6ToZeroWithCallback(arg0) != 0) {
                Particle_EnableFlag4(arg0);
            }
            break;

        case 3:
            Particle_ProcessTimer80(arg0, 0xA);
            Particle_ApplyB2B4AndAddAll(arg0);
            break;

        case 4:
            Particle_ResetState(arg0);
            break;
    }
}

void ParticleEffect_MediumBurst(ParticleEffectInstance* arg0) {
    Particle_SetScaleFactor1(arg0, 1.0f);
    Particle_SetScaleFactor2(arg0, 2.0f);
    Particle_SetScaleFactor3(arg0, 0.75f);
    SetPrimEnvColorFromPair(arg0, Particle_GetShortCF(arg0));
    Particle_IncrementState(arg0);
}

void ParticleEffect_MediumBurst_Main(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            ParticleEffect_MediumBurst(arg0);
            break;

        case 2:
            Particle_AnimLoopForwardComplete(arg0, 0, 3, 1, 1, 0);
            Particle_ApproachScaleFactor2(arg0);
            break;

        case 3:
            Particle_ResetState(arg0);
            break;
    }
}

void ParticleEffect_RotatingBurst(ParticleEffectInstance* arg0) {
    Particle_SetScaleFactor1(arg0, 0.4f);
    Particle_SetScaleFactor2(arg0, 0.7f);
    Particle_SetScaleFactor3(arg0, 0.1f);
    SetPrimEnvColorFromPair(arg0, Particle_GetShortCF(arg0));
    Particle_SetParamC7(arg0, 1);
    Particle_SetRotationZ(arg0, RandomMod(0x10000));
    Particle_IncrementState(arg0);
}

void ParticleEffect_RotatingBurst_Main(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            ParticleEffect_RotatingBurst(arg0);
            break;

        case 2:
            if (Particle_ApproachScaleFactor2WithCallback(arg0) != 0) {
                Particle_SetScaleFactor2(arg0, 0.2f);
            }
            break;

        case 3:
            Particle_ApproachScaleFactor2WithCallback(arg0);
            break;

        case 4:
            Particle_SetScaleFactor2(arg0, 0.7f);
            Particle_SetScaleFactor3(arg0, 0.1f);
            arg0->unk_B2 = 2;
            break;
    }

    if (Particle_DecrementTimerA6ToZero(arg0) != 0) {
        Particle_ResetState(arg0);
    }
}

void ParticleEffect_LargeFireball(ParticleEffectInstance* arg0) {
    Particle_SetScaleFactor1(arg0, 2.0f);
    Particle_AddVelocityBackward(arg0, 10.0f);
    SetPrimEnvColorFromPair(arg0, Particle_GetShortCF(arg0));
    Particle_SetPrimAlpha(arg0, 0xFF);
    Particle_SetParamC7(arg0, 1);
    Particle_SetRotationZ(arg0, RandomMod(0x10000));
    Particle_IncrementState(arg0);
}

void ParticleEffect_LargeFireball_Main(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            ParticleEffect_LargeFireball(arg0);
            break;

        case 2:
            Particle_ApproachScaleFactor1WithCallback(arg0, 5.0f, 1.0f);
            break;

        case 3:
            Particle_ApproachScaleFactor1WithCallback(arg0, 0.0f, 1.0f);
            Particle_ApproachPrimAlpha(arg0, 0x40, 0x20);
            break;

        case 4:
            Particle_ResetState(arg0);
            break;
    }
}

void ParticleEffect_TimedFireball_Stage1(ParticleEffectInstance* arg0) {
    Particle_GetShortCF(arg0);
    Particle_SetScaleFactor1(arg0, 2.0f);
    Particle_AddVelocityBackward(arg0, 10.0f);
    func_8140D658(arg0, RandomMod(6));
    func_8140D68C(arg0, RandomMod(6));
    Particle_SetParamC7(arg0, 1);
    Particle_SetRotationZ(arg0, RandomMod(0x10000));
    Particle_IncrementState(arg0);
}

void ParticleEffect_TimedFireball(ParticleEffectInstance* arg0) {
    Particle_GetShortCF(arg0);

    switch (arg0->unk_B2) {
        case 1:
            ParticleEffect_TimedFireball_Stage1(arg0);
            break;

        case 2:
            Particle_ApproachScaleFactor1WithCallback(arg0, 5.0f, 1.0f);
            break;

        case 3:
            Particle_ApproachScaleFactor1WithCallback(arg0, 0.0f, 1.0f);
            Particle_ApproachPrimAlpha(arg0, 0x40, 0x20);
            break;

        case 4:
            Particle_ResetState(arg0);
            break;
    }

    if (gTimerMask4 == 0) {
        func_8140D658(arg0, RandomMod(6));
        func_8140D68C(arg0, RandomMod(6));
    }
}

void ParticleEffect_Fireball_Stage1(ParticleEffectInstance* arg0) {
    UNUSED s16 pad;
    s16 sp24;

    Particle_GetShortCF(arg0);
    sp24 = Particle_GetShortAC(arg0);
    Particle_SetScaleFactor1(arg0, 2.0f);
    Particle_AddVelocityBackward(arg0, 10.0f);
    SetPrimColorFromPalette(arg0, 0xA);
    SetEnvColorFromPreset(arg0, sp24 % 6);
    Particle_SetParamC7(arg0, 1);
    Particle_SetTimerA6(arg0, sp24 * 2);
    Particle_RotateX(arg0, (sp24 << 0x10) / 10);
    Particle_SetRotationDeltaZ(arg0, Particle_GetRandomRotation(0x800, 0x400));
    Particle_DisableFlag4(arg0);
    Particle_IncrementState(arg0);
}

void ParticleEffect_Fireball_Main(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            ParticleEffect_Fireball_Stage1(arg0);
            break;

        case 2:
            if (Particle_DecrementTimerA6ToZeroWithCallback(arg0) != 0) {
                Particle_EnableFlag4(arg0);
            }
            break;

        case 3:
            Particle_ApproachScaleFactor1WithCallback(arg0, 4.0f, 1.0f);
            break;

        case 4:
            Particle_ProcessTimer80(arg0, 8);
            break;

        case 5:
            Particle_ApproachScaleFactor1WithCallback(arg0, 0.0f, 1.0f);
            break;

        case 6:
            Particle_ResetState(arg0);
            break;
    }

    Particle_AddRotationDeltaZ(arg0);
}

void ParticleEffect_Fireball_Stage2(ParticleEffectInstance* arg0) {
    Particle_GetShortAC(arg0);
    SetPrimEnvColorFromPair(arg0, Particle_GetShortCF(arg0));
    Particle_SetScaleFactor1(arg0, 1.35f);
    Particle_AddVelocityForward(arg0, 5.0f);
    Particle_SetSpeed(arg0, 5.5f);
    Particle_AddRotationDeltaXYZ(arg0, RandomMod(0x10000), RandomMod(0x10000), 0);
    Particle_IncrementState(arg0);
}

void ParticleEffect_Fireball_Stage3(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            ParticleEffect_Fireball_Stage2(arg0);
            break;

        case 2:
            Particle_ApproachPrimAlpha(arg0, 0x20, 0x16);
            Particle_AnimLoopForwardComplete(arg0, 0, 7, 1, 2, 0);
            break;

        case 3:
            Particle_ClearActiveFlag(arg0);
            break;
    }

    if (Particle_IsActive(arg0) != 0) {
        Particle_ApproachSpeedScaled(arg0, 3.4f, 1.0f);
        Particle_ApplyB2B4AndAddAll(arg0);
    }
}

void ParticleEffect_Fireball_Stage4(ParticleEffectInstance* arg0) {
    Particle_GetShortAC(arg0);
    SetPrimEnvColorFromPair(arg0, Particle_GetShortCF(arg0));
    Particle_SetScaleFactor1(arg0, 1.0f);
    Particle_AddVelocityForward(arg0, 5.0f);
    Particle_SetSpeed(arg0, 4.0f);
    Particle_AddRotationDeltaXYZ(arg0, RandomMod(0x10000), RandomMod(0x10000), 0);
    Particle_IncrementState(arg0);
}

void ParticleEffect_Fireball_Stage5(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            ParticleEffect_Fireball_Stage4(arg0);
            break;

        case 2:
            Particle_ApproachPrimAlpha(arg0, 0x20, 0x16);
            Particle_AnimLoopForwardComplete(arg0, 0, 7, 1, 2, 0);
            break;

        case 3:
            Particle_ClearActiveFlag(arg0);
            break;
    }

    if (Particle_IsActive(arg0) != 0) {
        Particle_ApproachSpeedScaled(arg0, 2.5f, 0.75f);
        Particle_ApplyB2B4AndAddAll(arg0);
    }
}

void ParticleEffect_Fireball_Stage6(ParticleEffectInstance* arg0) {
    Particle_GetShortAC(arg0);
    SetPrimEnvColorFromPair(arg0, Particle_GetShortCF(arg0));
    Particle_SetScaleFactor1(arg0, 0.6f);
    Particle_AddVelocityForward(arg0, 5.0f);
    Particle_SetSpeed(arg0, 3.0f);
    Particle_AddRotationDeltaXYZ(arg0, RandomMod(0x10000), RandomMod(0x10000), 0);
    Particle_IncrementState(arg0);
}

void ParticleEffect_Fireball_Stage7(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            ParticleEffect_Fireball_Stage6(arg0);
            break;

        case 2:
            Particle_ApproachPrimAlpha(arg0, 0x20, 0x16);
            Particle_AnimLoopForwardComplete(arg0, 0, 7, 1, 2, 0);
            break;

        case 3:
            Particle_ClearActiveFlag(arg0);
            break;
    }

    if (Particle_IsActive(arg0) != 0) {
        Particle_ApproachSpeedScaled(arg0, 1.5f, 0.4f);
        Particle_ApplyB2B4AndAddAll(arg0);
    }
}

void ParticleEffect_RandomColor_Stage1(ParticleEffectInstance* arg0) {
    UNUSED s32 pad;

    switch (Particle_GetShortCF(arg0)) {
        case 0:
            SetPrimColorFromPalette(arg0, 0xA);
            SetEnvColorFromPreset(arg0, RandomMod(6));
            break;

        case 1:
            func_8140D658(arg0, RandomMod(6));
            func_8140D68C(arg0, RandomMod(6));
            break;

        case 2:
            func_8140D708(arg0, RandomMod(6));
            break;
    }

    Particle_SetScaleFactor1(arg0, 0.8f);
    Particle_AddVelocityForward(arg0, 5.0f);
    Particle_SetSpeed(arg0, 3.0f);
    Particle_AddRotationDeltaXYZ(arg0, RandomMod(0x10000), RandomMod(0x10000), 0);
    Particle_IncrementState(arg0);
}

void ParticleEffect_RandomColor_Main(ParticleEffectInstance* arg0) {
    s16 sp2E = Particle_GetShortCF(arg0);

    switch (arg0->unk_B2) {
        case 1:
            ParticleEffect_RandomColor_Stage1(arg0);
            break;

        case 2:
            Particle_ApproachPrimAlpha(arg0, 0x20, 0x16);
            Particle_AnimLoopForwardComplete(arg0, 0, 7, 1, 2, 0);
            break;

        case 3:
            Particle_ClearActiveFlag(arg0);
            break;
    }

    if (Particle_IsActive(arg0) != 0) {
        Particle_ApproachSpeedScaled(arg0, 1.5f, 0.5f);
        Particle_ApplyB2B4AndAddAll(arg0);

        switch (sp2E) {
            case 0:
                SetEnvColorFromPreset(arg0, RandomMod(6));
                break;

            case 1:
                if (gTimerMask3 == 0) {
                    func_8140D658(arg0, RandomMod(6));
                    func_8140D68C(arg0, RandomMod(6));
                }
                break;

            case 2:
                func_8140D708(arg0, RandomMod(6));
                break;
        }
    }
}

void ParticleEffect_ThreeWayBurst_Stage1(ParticleEffectInstance* arg0) {
    s16 sp2E;
    s16 sp2C;
    s16 sp2A;

    sp2E = Particle_GetShortAC(arg0);
    sp2C = Particle_GetShortCF(arg0);
    sp2A = Particle_GetShortCE(arg0);

    SetPrimEnvColorFromPair(arg0, sp2C);
    Particle_SetScaleFactor1(arg0, 0.6f);
    Particle_SetScaleFactor2(arg0, 1.2f);
    Particle_SetScaleFactor3(arg0, 0.2f);

    switch (sp2A) {
        case 0:
            Particle_SetVelocityScaledXYZ(arg0, 0.0f, 10.0f, 0.0f);
            break;

        case 1:
            Particle_SetVelocityScaledXYZ(arg0, 0.0f, -5.0f, 10.0f);
            break;

        case 2:
            Particle_SetVelocityScaledXYZ(arg0, 0.0f, -5.0f, -10.0f);
            break;
    }

    Particle_AddVelocityForward(arg0, 5.0f);
    Particle_SetSpeed(arg0, 1.0f);
    Particle_AddRotationDeltaXYZ(arg0, RandomMod(0x10000), RandomMod(0x10000), 0);
    Particle_SetTimerA6(arg0, sp2E);
    Particle_DisableFlag4(arg0);
    Particle_IncrementState(arg0);
}

void ParticleEffect_ThreeWayBurst_Main(ParticleEffectInstance* arg0) {
    Particle_GetShortCE(arg0);

    switch (arg0->unk_B2) {
        case 1:
            ParticleEffect_ThreeWayBurst_Stage1(arg0);
            break;

        case 2:
            if (Particle_DecrementTimerA6ToZeroWithCallback(arg0) != 0) {
                Particle_EnableFlag4(arg0);
            }
            break;

        case 3:
            Particle_ApproachScaleFactor2(arg0);
            Particle_ApproachPrimAlpha(arg0, 0x20, 0x16);
            Particle_AnimLoopForwardComplete(arg0, 0, 7, 1, 2, 0);
            Particle_ApproachSpeedScaled(arg0, 1.5f, 0.1f);
            Particle_ApplyB2B4AndAddAll(arg0);
            break;

        case 4:
            Particle_ClearActiveFlag(arg0);
            break;
    }
}

void ParticleEffect_SmallBurst_Stage1(ParticleEffectInstance* arg0) {
    s16 sp2E = Particle_GetShortAC(arg0);
    s16 sp2C = Particle_GetShortCF(arg0);

    Particle_SetRandomVelocityXYZ(arg0, 0, 0xF, 0x14);
    Particle_AddVelocityYScaled(arg0, 5.0f);
    Particle_SetScaleFactor1(arg0, 0.2f);
    Particle_SetSpeed(arg0, 2.5f);
    Particle_AddRotationDeltaXYZ(arg0, RandomRangeSigned(0x2000), RandomRangeSigned(0x2000), 0);
    SetPrimEnvColorFromPair(arg0, sp2C);
    Particle_SetTimerA6(arg0, sp2E * 4);
    Particle_DisableFlag4(arg0);
    Particle_IncrementState(arg0);
}

void ParticleEffect_SmallBurst_Main(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            ParticleEffect_SmallBurst_Stage1(arg0);
            break;

        case 2:
            if (Particle_ProcessTimer80(arg0, arg0->unk_A6) != 0) {
                Particle_SetTimerA6(arg0, 2);
                Particle_EnableFlag4(arg0);
            }
            break;

        case 3:
            Particle_AnimLoopForwardComplete(arg0, 0, 7, 1, 1, 0);
            Particle_ApproachScaleFactor1(arg0, 0.5f, 0.1f);
            Particle_ApplyB2B4AndAddAll(arg0);
            if (Particle_DecrementTimerA6ToZero(arg0) != 0) {
                Particle_ApproachPrimAlpha(arg0, 0, 0x20);
            }
            break;

        case 4:
            Particle_ResetState(arg0);
            break;
    }
}

void ParticleEffect_MediumBurst_Stage1(ParticleEffectInstance* arg0) {
    s16 sp2E = Particle_GetShortAC(arg0);

    Particle_GetShortCF(arg0);
    Particle_SetRandomVelocityXYZ(arg0, 0xA, 0x14, 0x14);
    Particle_SetScaleFactor1(arg0, 0.25f);
    Particle_SetSpeed(arg0, 2.5f);
    Particle_AddRotationDeltaXYZ(arg0, RandomRangeSigned(0x2000), RandomRangeSigned(0x2000), 0);
    SetRandomPrimColor(arg0);
    Particle_SetPrimAlpha(arg0, 0xC8);
    Particle_SetTimerA6(arg0, sp2E * 4);
    Particle_DisableFlag4(arg0);
    Particle_IncrementState(arg0);
}

void func_8433A858(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            ParticleEffect_MediumBurst_Stage1(arg0);
            break;

        case 2:
            if (Particle_ProcessTimer80(arg0, arg0->unk_A6) != 0) {
                Particle_SetTimerA6(arg0, 2);
                Particle_EnableFlag4(arg0);
            }
            break;

        case 3:
            Particle_AnimLoopForwardComplete(arg0, 0, 7, 1, 1, 0);
            Particle_ApproachScaleFactor1(arg0, 0.4f, 0.1f);
            Particle_ApplyB2B4AndAddAll(arg0);
            if (Particle_DecrementTimerA6ToZero(arg0) != 0) {
                Particle_ApproachPrimAlpha(arg0, 0, 0x20);
            }
            break;

        case 4:
            Particle_ClearActiveFlag(arg0);
            break;
    }
}

void ParticleEffect_BrightBurst_Stage1(ParticleEffectInstance* arg0) {
    s16 sp2E = Particle_GetShortAC(arg0);

    Particle_GetShortCF(arg0);
    Particle_SetRandomVelocityXYZ(arg0, 0xA, 0x14, 0x14);
    Particle_SetScaleFactor1(arg0, 0.4f);
    Particle_SetSpeed(arg0, 2.5f);
    Particle_AddRotationDeltaXYZ(arg0, RandomRangeSigned(0x2000), RandomRangeSigned(0x2000), 0);
    Particle_SetPrimColor(arg0, 0xFF, 0xFF, 0xFF);
    SetRandomEnvColor(arg0);
    Particle_SetTimerA6(arg0, sp2E * 4);
    Particle_DisableFlag4(arg0);
    Particle_IncrementState(arg0);
}

void ParticleEffect_BrightBurst_Main(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            ParticleEffect_BrightBurst_Stage1(arg0);
            break;

        case 2:
            if (Particle_ProcessTimer80(arg0, arg0->unk_A6) != 0) {
                Particle_EnableFlag4(arg0);
                Particle_SetParamC7(arg0, 1);
            }
            break;

        case 3:
            Particle_ApproachScaleFactor1(arg0, 0.5f, 0.025f);
            Particle_AnimLoopForwardComplete(arg0, 2, 7, 1, 1, 0);
            Particle_ApplyB2B4AndAddAll(arg0);
            break;

        case 4:
            Particle_ClearActiveFlag(arg0);
            break;
    }
}

void ParticleEffect_InitRotationAndSpeed(ParticleEffectInstance* arg0) {
    Vec3s sp28;
    UNUSED s16 pad;
    s16 sp24;

    Particle_GetShortCF(arg0);
    sp24 = Particle_GetShortAC(arg0);
    Particle_SetScaleFactor1(arg0, 0.05f);
    Particle_SetTargetRotationXY(arg0, arg0->unk_94.x, arg0->unk_94.y + 0x8000);
    Particle_SetRotationDeltaXY(arg0, 0x800, 0x300);
    sp28.x = sp24 << 0xC;
    sp28.y = Particle_GetRandomRotation(0x3000, 0x1000);
    sp28.z = 0;
    Particle_AddRotationDeltaVec(arg0, sp28);
    SetRandomEnvColor(arg0);
    Particle_SetTimerA6(arg0, RandomMod(0x10) + 8);
    Particle_SetSpeed(arg0, 4.0f);
    Particle_IncrementState(arg0);
}

void ParticleEffect_UpdateStateMachine(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            ParticleEffect_InitRotationAndSpeed(arg0);
            break;

        case 2:
            Particle_ApproachScaleFactor1(arg0, 0.15f, 0.01f);
            Particle_ApproachSpeedScaled(arg0, 1.0f, 0.7f);
            Particle_ApproachRotationYWrap(arg0);
            if (Particle_DecrementTimerA6ToZeroWithCallback(arg0) != 0) {
                Particle_SetTimerA6(arg0, RandomModPlus(0xC, 0x20));
                if (arg0->unk_94.y >= arg0->unk_A0.y) {
                    Particle_SetTargetRotationX(arg0, -0x4000);
                } else {
                    Particle_SetTargetRotationX(arg0, 0x4000);
                }
            }
            break;

        case 3:
            Particle_ApproachRotationXWrap(arg0);
            Particle_ApproachSpeedScaled(arg0, 0.5f, 0.2f);
            Particle_DecrementTimerA6ToZeroWithCallback(arg0);
            break;

        case 4:
            Particle_ApproachRotationXWrap(arg0);
            Particle_AnimLoopForwardComplete(arg0, 0, 3, 1, 1, 0);
            break;

        case 5:
            Particle_ClearActiveFlag(arg0);
            break;
    }

    if (Particle_IsActive(arg0) != 0) {
        Particle_ApplyB3ACAndAddAll(arg0);
    }
}

void ParticleEffect_SetGlowParameters(ParticleEffectInstance* arg0) {
    Particle_SetScaleFactor1(arg0, 0.2f);
    SetPrimEnvColorFromPair(arg0, Particle_GetShortCF(arg0));
    Particle_SetPrimAlpha(arg0, 0xC8);
    Particle_SetTimerA6(arg0, 0x18);
    arg0->unk_74 = 0.02f;
    Particle_IncrementState(arg0);
}

void ParticleEffect_HandleMultiStage(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            ParticleEffect_SetGlowParameters(arg0);
            break;

        case 2:
            Particle_ApproachScaleFactor1(arg0, 2.0f, 0.02f);
            Particle_ApproachEnvG(arg0, 0xC8, 2);
            Particle_DecrementTimerA6ToZeroWithCallback(arg0);
            break;

        case 3:
            ApproachF32(&arg0->unk_74, 0.008f, 0.001f);
            Particle_ApproachScaleFactor1(arg0, 2.0f, arg0->unk_74);
            Particle_ApproachPrimR(arg0, 0x78, 8);
            Particle_ApproachPrimB(arg0, 0x96, 8);
            Particle_ApproachPrimG(arg0, 0x96, 8);
            Particle_ApproachEnvR(arg0, 0x78, 8);
            Particle_ApproachEnvB(arg0, 0x96, 8);
            Particle_ApproachEnvG(arg0, 0x96, 8);
            Particle_ApproachPrimAlphaWithCallback(arg0, 0, 0xC);
            break;

        case 4:
            Particle_ClearActiveFlag(arg0);
            break;
    }
}

void ParticleEffect_SetRotationBasedOnState(ParticleEffectInstance* arg0) {
    s16 sp26 = Particle_GetShortCE(arg0);

    Particle_SetScaleFactor1(arg0, 0.05f);
    Particle_SetScaleFactor2(arg0, 0.3f);
    Particle_SetScaleFactor3(arg0, 0.005f);

    switch (sp26) {
        case 0:
            Particle_SetRotationY(arg0, 0);
            break;

        case 1:
            Particle_SetRotationY(arg0, 0x5500);
            break;

        case 2:
            Particle_SetRotationY(arg0, -0x5600);
            break;
    }

    Particle_AddVelocityFromDirVector(arg0, 10.0f);
    SetPrimEnvColorFromPair(arg0, Particle_GetShortCF(arg0));
    Particle_SetPrimAlpha(arg0, 0xC8);
    Particle_SetTimerA6(arg0, 0x18);
    Particle_IncrementState(arg0);
}

void ParticleEffect_StageBasedUpdate(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            ParticleEffect_SetRotationBasedOnState(arg0);
            break;

        case 2:
            Particle_ApproachEnvG(arg0, 0xC8, 2);
            Particle_DecrementTimerA6ToZeroWithCallback(arg0);
            break;

        case 3:
            Particle_ApproachPrimR(arg0, 0x78, 8);
            Particle_ApproachPrimB(arg0, 0x96, 8);
            Particle_ApproachPrimG(arg0, 0x96, 8);
            Particle_ApproachEnvR(arg0, 0x78, 8);
            Particle_ApproachEnvB(arg0, 0x96, 8);
            Particle_ApproachEnvG(arg0, 0x96, 8);
            Particle_ApproachPrimAlphaWithCallback(arg0, 0, 0xC);
            break;

        case 4:
            Particle_ClearActiveFlag(arg0);
            break;
    }

    Particle_ApproachScaleFactor2(arg0);
}

void ParticleEffect_RandomizedPosition(ParticleEffectInstance* arg0) {
    UNUSED s16 pad;
    s16 sp2C;

    Particle_GetShortAC(arg0);
    sp2C = Particle_GetShortCF(arg0);
    Particle_SetScaleFactor1(arg0, 0.5f);
    Particle_AddRotationDeltaXYZ(arg0, RandomMod(0x10000), RandomMod(0x10000), 0);
    Particle_AddVelocityForward(arg0, 5.0f);
    Particle_SetSpeed(arg0, 1.0f);
    SetPrimEnvColorFromPair(arg0, sp2C);
    Particle_IncrementState(arg0);
}

void ParticleEffect_ConditionalTerminate(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            ParticleEffect_RandomizedPosition(arg0);
            break;

        case 2:
            Particle_ApproachScaleFactor1(arg0, 0.3f, 0.02f);
            Particle_ApproachPrimAlpha(arg0, 0x20, 0xC);
            Particle_ApplyB2B4AndAddAll(arg0);
            Particle_AddVelocityYScaled(arg0, -1.0f);
            Particle_ProcessTimer80(arg0, 0x10);
            break;

        case 3:
            Particle_ClearActiveFlag(arg0);
            break;
    }

    if (arg0->unk_2C.y < 0.0f) {
        Particle_ClearActiveFlag(arg0);
    }
}

void SpawnLargeBurstEffect(void) {
    ParticleDef_CreateQuick(4, ParticleEffect_LargeBurst, &gParticleEffectData[8], 0, 4, 0x11, gParticleTexture_Default, 0, 0);
}

void SpawnLargeBurstIfNotActive(void) {
    s32 sp34 = 0;

    if (IsEntityASpecies(0x7C) != 0) {
        sp34 = 1;
    }

    if (IsEntityASpecies(4) != 0) {
        sp34 = 1;
    }

    if (sp34 == 0) {
        ParticleDef_CreateQuick(0, ParticleEffect_LargeBurst, &gParticleEffectData[8], 0, 4, 0x11, gParticleTexture_Default, 0, 0);
    }
}

void SpawnTimedFireballEffect(void) {
    ParticleDef_CreateFull(0, 1, 0x3C, ParticleEffect_Type1_Main, &gParticleEffectData[0x45], 0, 1, 0x11, gParticleTexture_Default, 0, 0);
}

void InitParticleEffectGroup_Basic(void) {
    ParticleDef_CreateQuick(0, ParticleEffect_FireworkMain, &gParticleEffectData[0x34], 0, 1, 0x11, 9, 3, 5);
    ParticleDef_CreateQuick(0, ParticleEffect_UpdateStateMachine, &gParticleEffectData[0x45], 0, 0x10, 0x11, 9, 0, 0);
    ParticleDef_CreateQuick(8, ParticleEffect_UpdateStateMachine, &gParticleEffectData[0x45], 0, 0x10, 0x11, 9, 0, 0);
}

void SpawnSmallGlowAndCustomEffect(void) {
    ParticleDef_CreateQuick(3, ParticleEffect_SmallGlow, &gParticleEffectData[0xE], 0, 1, 0x11, gParticleTexture_Default, 0, 1);
    ParticleDef_CreateQuick(3, ParticleEffect_SmallGlow, &gParticleEffectData[0x19], 0, 1, 0x11, gParticleTexture_Default, 0, 1);
    ParticleDef_CreateQuick(4, ParticleEffect_HighSpeedFlash_Main, &gParticleDefaultCallback, 0, 1, 0x11, gParticleTexture_Default, 0, 0);
}

void InitComplexParticleSequence(void) {
    ParticleDef_CreateFull(0, 1, 0xF, ParticleEffect_Fireball_Stage7, &gParticleEffectData[0x19], 0, 1, 0x10, gParticleTexture_Default, 0x26, 0);
    ParticleDef_CreateQuick(0xC, ParticleEffect_StageBasedUpdate, &gParticleEffectData[0x4B], 0, 1, 0xA, 0, 0x4C, 0);
    ParticleDef_CreateQuick(0xC, ParticleEffect_StageBasedUpdate, &gParticleEffectData[0x4B], 0, 1, 0xA, 0, 0x4C, 1);
    ParticleDef_CreateQuick(0xC, ParticleEffect_StageBasedUpdate, &gParticleEffectData[0x4B], 0, 1, 0xA, 0, 0x4C, 2);
    ParticleDef_CreateFull(4, 1, 0x10, ParticleEffect_ConditionalTerminate, &gParticleEffectData[0xA], 0, 2, 0x11, gParticleTexture_Default, 0x4C, 0);
}

void InitExplosionEffectSet(void) {
    ParticleDef_CreateDefault(0, 0x40, 6);
    ParticleDef_CreateQuick(3, ParticleEffect_SmallGlow, &gParticleEffectData[0xE], 0, 1, 0x11, gParticleTexture_Default, 0, 0);
    ParticleDef_CreateQuick(3, ParticleEffect_SmallGlow, &gParticleEffectData[0x19], 0, 1, 0x11, gParticleTexture_Default, 0, 0);
    ParticleDef_CreateQuick(4, ParticleEffect_ComplexExplosion, &gParticleEffectData[8], 0, 1, 0x11, gParticleTexture_Default, 0, 0);
}

void InitAdvancedParticleCombo(void) {
    ParticleDef_Create321BC(4, 0xA, 0x35, 0x10, 0xFF);
    ParticleDef_CreateQuick(0, Particle_SootPuff_Handler, &gParticleEffectData[4], 0, 1, 0x10, gParticleTexture_Default, 0x35, 0);
    ParticleDef_CreateFull(0, 5, 3, ParticleEffect_Fireball_Stage3, &gParticleEffectData[0x19], 0, 8, 0x10, gParticleTexture_Default, 0x26, 0);
    ParticleDef_CreateFull(0xA, 1, 8, ParticleEffect_SmallBurst_Main, &gParticleEffectData[0x19], 0, 3, 0x11, gParticleTexture_Default, 0x26, 0);
    ParticleDef_CreateQuick(0xC, ParticleEffect_HandleMultiStage, &gParticleEffectData[0x4B], 0, 1, 0xA, 0, 0x4C, 0);
    ParticleDef_CreateFull(2, 1, 0x10, ParticleEffect_ConditionalTerminate, &gParticleEffectData[0xA], 0, 4, 0x11, gParticleTexture_Default, 0x4C, 0);
}

void InitParticleEffectSet_WithTexture53(void) {
    ParticleDef_CreateBC20(0, 0, 0x20, 0xA, 0xA0);
    ParticleDef_CreateDefault(0, 8, 0x35);
    ParticleDef_CreateQuick(0, ParticleEffect_MediumBurst_Main, &gParticleEffectData[0x53], 0, 1, 0x10, gParticleTexture_Default, 0x40, 0);
    ParticleDef_CreateQuick(6, ParticleEffect_RotatingBurst_Main, &gParticleEffectData[0x53], 0x6E, 1, 0x10, gParticleTexture_Default, 0x40, 1);
    ParticleDef_CreateFull(0, 3, 0x1E, ParticleEffect_GravityVariant_Main, &gParticleEffectData[0x4A], 0, 1, 0x11, gParticleTexture_Default, 0x13, 0);
}

void InitParticleEffectSet_Alt(void) {
    ParticleDef_CreateBC20(0, 0, 0x20, 0xA, 0xA0);
    ParticleDef_CreateDefault(0, 8, 6);
    ParticleDef_CreateQuick(0, ParticleEffect_MediumBurst_Main, &gParticleEffectData[0x53], 0, 1, 0x10, gParticleTexture_Default, 0xD, 0);
    ParticleDef_CreateQuick(6, ParticleEffect_RotatingBurst_Main, &gParticleEffectData[0x53], 0x46, 1, 0x10, gParticleTexture_Default, 0xD, 1);
}

void InitSmallGlowEffectSet(void) {
    ParticleDef_CreateDefault(0, 8, 6);
    ParticleDef_CreateFull(0, 1, 0x3C, ParticleEffect_Type3_Main, &gParticleEffectData[0x45], 0, 4, 0x11, gParticleTexture_Default, 0, 0);
    ParticleDef_CreateFull(0, 1, 0x3C, ParticleEffect_Type2_Main, &gParticleEffectData[0x45], 0, 1, 0x11, gParticleTexture_Default, 0, 0);
}

void InitParticleEffectSet_Alt2(void) {
    ParticleDef_CreateBC20(0, 0, 0x20, 0xA, 0xA0);
    ParticleDef_CreateDefault(0, 8, 6);
    ParticleDef_CreateQuick(0, ParticleEffect_MediumBurst_Main, &gParticleEffectData[0x53], 0, 1, 0x10, gParticleTexture_Default, 0x41, 0);
    ParticleDef_CreateQuick(6, ParticleEffect_RotatingBurst_Main, &gParticleEffectData[0x53], 0x46, 1, 0x10, gParticleTexture_Default, 0x41, 1);
}

void InitParticleEffectSet_WithFade(void) {
    ParticleDef_CreateBC20(0, 0, 0x20, 0xA, 0xA0);
    ParticleDef_Create31EAC(0, 0xA, 0xFF, 0, 0x10);
    ParticleDef_CreateDefault(0, 0x20, 0x10);
    ParticleDef_CreateQuick(0, ParticleEffect_MediumBurst_Main, &gParticleEffectData[0x53], 0, 1, 0x10, gParticleTexture_Default, 0x2C, 0);
    ParticleEffect_SimpleCallback();
    ParticleDef_CreateQuick(6, ParticleEffect_RotatingBurst_Main, &gParticleEffectData[0x53], 0x46, 1, 0x10, gParticleTexture_Default, 0x2C, 1);
}

void InitParticleEffectSet_WithDifferentTiming(void) {
    ParticleDef_CreateBC20(0, 0, 0x20, 0xA, 0xA0);
    ParticleDef_CreateDefault(0, 8, 0x22);
    ParticleDef_CreateQuick(0, ParticleEffect_MediumBurst_Main, &gParticleEffectData[0x53], 0, 1, 0x10, gParticleTexture_Default, 0x17, 0);
    ParticleDef_CreateQuick(6, ParticleEffect_RotatingBurst_Main, &gParticleEffectData[0x53], 0x46, 1, 0x10, gParticleTexture_Default, 0x17, 1);
}

void InitParticleEffectSet_Single(void) {
    ParticleDef_CreateBC20(0, 0, 0x20, 0xA, 0xA0);
    ParticleDef_CreateDefault(0, 8, 0x22);
    ParticleDef_CreateQuick(0, ParticleEffect_MediumBurst_Main, &gParticleEffectData[0x53], 0, 1, 0x10, gParticleTexture_Default, 0x17, 0);
}

void InitParticleComboVariant(void) {
    ParticleDef_Create321BC(4, 0xA, 0x35, 0xC, 0xFF);
    ParticleDef_CreateQuick(0, Particle_SootPuff_Handler, &gParticleEffectData[4], 0, 1, 0x10, gParticleTexture_Default, 0x35, 0);
    ParticleDef_CreateFull(0, 5, 3, ParticleEffect_Fireball_Stage3, &gParticleEffectData[0x19], 0, 8, 0x10, gParticleTexture_Default, 0x26, 0);
    ParticleDef_CreateFull(0xA, 1, 3, ParticleEffect_SmallBurst_Main, &gParticleEffectData[0x19], 0, 8, 0x11, gParticleTexture_Default, 0x26, 0);
}

void InitParticleEffectSet_WithMultiple(void) {
    ParticleDef_Create323BC(0, 0xA, 0x35, 0x10, 0xDC, 0x20);
    ParticleDef_CreateQuick(3, Particle_SootPuff_Handler, &gParticleEffectData[4], 0, 1, 0x10, gParticleTexture_Default, 0x35, 0);
    ParticleDef_CreateFull(0, 5, 3, ParticleEffect_Fireball_Stage3, &gParticleEffectData[0x19], 0, 8, 0x10, gParticleTexture_Default, 0x26, 0);
    ParticleDef_CreateFull(4, 4, 2, ParticleEffect_LargeFireball_Main, &gParticleEffectData[0x54], 0, 1, 0x10, gParticleTexture_Default, 0x33, 0);
    ParticleDef_CreateFull(0xC, 1, 3, ParticleEffect_SmallBurst_Main, &gParticleEffectData[0x19], 0, 8, 0x11, gParticleTexture_Default, 0x26, 0);
    ParticleDef_CreateFull(0xE, 4, 2, Particle_HandleState_Smoke, &gParticleEffectData[0x3D], 0, 6, 0x10, 0x64, 0, 0);
    ParticleDef_CreateFull(0, 2, 6, ParticleEffect_FireworkHandler2, &gParticleEffectData[0x42], 0, 8, 0x11, 9, 0x18, 0xB);
    ParticleDef_CreateDefault(0x30, 0x20, 0xA);
}

void InitParticleEffectSet_WithTimedFireball(void) {
    ParticleDef_CreateComplexColor(4, 0x32, 0x20, 0xA0);
    ParticleDef_CreateFull(4, 4, 3, ParticleEffect_TimedFireball, &gParticleEffectData[0x54], 0, 1, 0x10, gParticleTexture_Default, 0, 0);
    ParticleDef_CreateQuick(3, Particle_SootPuff_Handler_Alt, &gParticleEffectData[0x1B], 0, 1, 0x10, gParticleTexture_Default, 0x23, 0);
    ParticleDef_CreateFull(3, 5, 3, ParticleEffect_RandomColor_Main, &gParticleEffectData[0x19], 0, 8, 0x10, gParticleTexture_Default, 1, 0);
    ParticleDef_CreateDefault(0x30, 0x20, 0xA);
}

void InitParticleEffectSet_WithCustomCallback(void) {
    ParticleDef_Create321BC(4, 0xA, 0x23, 0x10, 0xFF);
    ParticleDef_CreateQuick(3, Particle_SootPuff_Handler, &gParticleEffectData[4], 0, 1, 0x10, gParticleTexture_Default, 0x35, 0);
    ParticleDef_CreateFull(3, 5, 3, ParticleEffect_RandomColor_Main, &gParticleEffectData[0x19], 0, 8, 0x10, gParticleTexture_Default, 0, 0);
    ParticleDef_CreateQuick(0, ParticleEffect_UpdateStateMachine, &gParticleEffectData[0x45], 0, 0x10, 0x11, 9, 0, 0);
    ParticleDef_CreateQuick(8, ParticleEffect_UpdateStateMachine, &gParticleEffectData[0x45], 0, 0x10, 0x11, 9, 0, 0);
    ParticleDef_CreateDefault(0x30, 0x20, 0xA);
}

void InitParticleEffectSet_Variant2(void) {
    ParticleDef_CreateComplexColor(4, 0x32, 0x20, 0xA0);
    ParticleDef_CreateQuick(4, ParticleEffect_Fireball_Main, &gParticleEffectData[0x54], 0, 9, 0x10, gParticleTexture_Default, 0, 0);
    ParticleDef_CreateFull(3, 5, 3, ParticleEffect_RandomColor_Main, &gParticleEffectData[0x19], 0, 8, 0x10, gParticleTexture_Default, 0, 0);
    ParticleDef_CreateFull(0xC, 1, 3, ParticleEffect_SmallBurst_Main, &gParticleEffectData[0x19], 0, 8, 0x11, gParticleTexture_Default, 0x39, 0);
    ParticleDef_CreateDefault(0x16, 0x20, 0xA);
}

void InitParticleEffectSet_WithComplex(void) {
    UNUSED s32 pad;

    ParticleDef_Create31EAC(0, 0x19, 0xFF, 0, 8);
    ParticleDef_Create321BC(4, 0x19, 0x19, 0x10, 0xFF);
    ParticleDef_CreateQuick(3, Particle_SootPuff_Handler, &gParticleEffectData[4], 0, 1, 0x10, gParticleTexture_Default, 0x19, 0);
    ParticleDef_CreateQuick(0, ParticleEffect_LargeFireball_Main, &gParticleEffectData[0x34], 0, 1, 0x10, gParticleTexture_Default, 0x2C, 0);
    ParticleDef_CreateFull(4, 8, 1, ParticleEffect_LargeFireball_Main, &gParticleEffectData[0x54], 0, 1, 0x10, gParticleTexture_Default, 0x2C, 0);
    ParticleDef_CreateFull(3, 5, 2, ParticleEffect_Fireball_Stage3, &gParticleEffectData[0x19], 0, 8, 0x10, gParticleTexture_Default, 0xF, 0);
    func_8433E524();
}

void InitParticleEffectSet_Variant3(void) {
    UNUSED s32 pad;

    ParticleDef_Create321BC(4, 0xA, 0x19, 0x10, 0xFF);
    ParticleDef_CreateQuick(0, ParticleEffect_LargeFireball_Main, &gParticleEffectData[0x34], 0, 1, 0x10, gParticleTexture_Default, 0x17, 0);
    ParticleDef_CreateFull(4, 4, 1, ParticleEffect_LargeFireball_Main, &gParticleEffectData[0x54], 0, 1, 0x10, gParticleTexture_Default, 0x17, 0);
    ParticleDef_CreateQuick(3, Particle_SootPuff_Handler, &gParticleEffectData[4], 0, 1, 0x10, gParticleTexture_Default, 0x1A, 0);
    ParticleDef_CreateFull(3, 5, 3, ParticleEffect_Fireball_Stage3, &gParticleEffectData[0x19], 0, 8, 0x10, gParticleTexture_Default, 0x17, 0);
    ParticleDef_CreateFull(0xC, 1, 3, ParticleEffect_SmallBurst_Main, &gParticleEffectData[0x19], 0, 8, 0x11, gParticleTexture_Default, 0x17, 0);
    ParticleDef_CreateDefault(0x16, 0x20, 0xA);
}

void InitParticleEffectSet_Variant4(void) {
    UNUSED s32 pad;

    ParticleDef_Create321BC(4, 0xA, 0x19, 0x10, 0xFF);
    ParticleDef_CreateQuick(0, ParticleEffect_LargeFireball_Main, &gParticleEffectData[0x34], 0, 1, 0x10, gParticleTexture_Default, 0x29, 0);
    ParticleDef_CreateFull(4, 4, 1, ParticleEffect_LargeFireball_Main, &gParticleEffectData[0x54], 0, 1, 0x10, gParticleTexture_Default, 0x29, 0);
    ParticleDef_CreateQuick(3, Particle_SootPuff_Handler, &gParticleEffectData[4], 0, 1, 0x10, gParticleTexture_Default, 0x1A, 0);
    ParticleDef_CreateFull(3, 5, 3, ParticleEffect_Fireball_Stage3, &gParticleEffectData[0x19], 0, 8, 0x10, gParticleTexture_Default, 0x29, 0);
    ParticleDef_CreateFull(0xC, 1, 3, ParticleEffect_SmallBurst_Main, &gParticleEffectData[0x19], 0, 8, 0x11, gParticleTexture_Default, 0x29, 0);
    ParticleDef_CreateDefault(0x16, 0x20, 0xA);
}

void InitParticleEffectSet_ThreeInstances(void) {
    ParticleDef_CreateFull(0, 2, 8, ParticleEffect_ThreeWayBurst_Main, &gParticleEffectData[0x19], 0, 1, 0x11, gParticleTexture_Default, 0x49, 0);
    ParticleDef_CreateFull(0, 2, 8, ParticleEffect_ThreeWayBurst_Main, &gParticleEffectData[0x19], 0, 1, 0x11, gParticleTexture_Default, 0x4A, 1);
    ParticleDef_CreateFull(0, 2, 8, ParticleEffect_ThreeWayBurst_Main, &gParticleEffectData[0x19], 0, 1, 0x11, gParticleTexture_Default, 0x4B, 2);
}
