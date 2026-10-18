#include "fragment62.h"
#include "src/1C720.h"

void Particle_FireBurstSmall(ParticleEffectInstance* arg0, s16 arg1) {
    UNUSED s32 pad[3];
    s16 sp22 = Particle_GetShortAC(arg0);

    Particle_SetScaleFactor1(arg0, 0.25f);
    func_8140A578(arg0, RandomRangeSignedPlus(0x400, 0xE00));
    Particle_RotateY(arg0, RandomRangeSigned(0x400));
    Particle_SetSpeed(arg0, 2.5f);

    switch (arg1) {
        case 0:
            SetPrimEnvColorFromPair(arg0, 0x17);
            break;

        case 1:
            SetPrimEnvColorFromPair(arg0, 0x18);
            break;
    }

    Particle_SetTimerA6(arg0, sp22 * 2);
    Particle_DisableFlag4(arg0);
    Particle_IncrementState(arg0);
}

void func_84333210(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B8) {
        case 1:
            if (Particle_StartTimer2(arg0, 2) != 0) {
                Particle_IncrementFlag2Counter(arg0);
            }
            break;

        case 2:
            Particle_DecreaseRotationXTowards(arg0, -0x400, 0x200);
            if (Particle_StartTimer2(arg0, 0x10) != 0) {
                Particle_IncrementFlag2Counter(arg0);
            }
            break;
    }

    if (arg0->unk_B8 > 0) {
        Particle_ApplyB2B4AndAddAll(arg0);
    }
}

void func_843332B4(ParticleEffectInstance* arg0) {
    s16 sp2E = Particle_GetShortCF(arg0);

    switch (arg0->unk_B2) {
        case 1:
            Particle_FireBurstSmall(arg0, sp2E);
            break;

        case 2:
            if (Particle_DecrementTimerA6ToZeroWithCallback(arg0) != 0) {
                Particle_EnableFlag2(arg0);
                Particle_EnableFlag4(arg0);
                Particle_SetTimerA6(arg0, 0xB);
            }
            break;

        case 3:
            Particle_ApproachScaleFactor1(arg0, 0.75f, 0.03f);

            switch (sp2E) {
                case 0:
                    Particle_ApproachPrimB(arg0, 0, 0x18);
                    Particle_ApproachEnvG(arg0, 0, 0x18);
                    break;

                case 1:
                    Particle_ApproachPrimR(arg0, 0, 0x18);
                    Particle_ApproachEnvG(arg0, 0x78, 0xC);
                    break;
            }

            if (Particle_DecrementTimerA6ToZeroWithCallback(arg0) != 0) {
                Particle_SetTimerA6(arg0, 0xC);
            }
            break;

        case 4:
            Particle_ApproachScaleFactor1(arg0, 0.75f, 0.02f);
            switch (sp2E) {
                case 0:
                    Particle_ApproachPrimG(arg0, 0, 0x10);
                    Particle_ApproachEnvR(arg0, 0, 0x10);
                    break;

                case 1:
                    Particle_ApproachPrimG(arg0, 0x78, 0xC);
                    Particle_ApproachEnvG(arg0, 0, 0xA);
                    break;
            }

            if ((Particle_DecrementTimerA6ToZero(arg0) != 0) && (Particle_ApproachPrimAlpha(arg0, 0, 0x18) != 0)) {
                Particle_IncrementState(arg0);
            }
            break;

        case 5:
            Particle_ClearActiveFlag(arg0);
            break;
    }

    if (Particle_HasFlag4(arg0) != 0) {
        Particle_AnimLoopForward(arg0, 0, 7, 1, 2, -1);
        func_84333210(arg0);
    }
}

void Particle_FireBurstLarge(ParticleEffectInstance* arg0) {
    UNUSED s32 pad[3];
    s16 sp22 = Particle_GetShortAC(arg0);

    Particle_SetScaleFactor1(arg0, 0.25f);
    Particle_RotateY(arg0, RandomRangeSigned(0x400));
    Particle_SetSpeed(arg0, D_84392058[0]);
    SetPrimEnvColorFromPair(arg0, 0x17);
    Particle_SetTimerA6(arg0, sp22 * 2);
    Particle_DisableFlag4(arg0);
    Particle_IncrementState(arg0);
}

void func_84333570(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B8) {
        case 1:
            if (Particle_StartTimer2(arg0, 2) != 0) {
                Particle_IncrementFlag2Counter(arg0);
                Particle_RotateX(arg0, 0x2900);
            }
            break;

        case 2:
            func_8140A578(arg0, 0xC00);
            break;
    }

    if (arg0->unk_B8 > 0) {
        Particle_ApplyB638AndAddAllAlt(arg0);
    }
}

void func_84333600(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            Particle_FireBurstLarge(arg0);
            break;

        case 2:
            if (Particle_DecrementTimerA6ToZeroWithCallback(arg0) != 0) {
                Particle_EnableFlag2(arg0);
                Particle_EnableFlag4(arg0);
                Particle_SetTimerA6(arg0, 0xB);
            }
            break;

        case 3:
            Particle_ApproachScaleFactor1(arg0, 0.75f, 0.03f);
            Particle_ApproachPrimB(arg0, 0, 0x18);
            Particle_ApproachEnvG(arg0, 0, 0x20);
            if (Particle_DecrementTimerA6ToZeroWithCallback(arg0) != 0) {
                Particle_SetTimerA6(arg0, 0xC);
            }
            break;

        case 4:
            Particle_ApproachScaleFactor1(arg0, 0.75f, 0.02f);
            Particle_ApproachPrimG(arg0, 0, 0x10);
            Particle_ApproachEnvR(arg0, 0, 0x10);
            if ((Particle_DecrementTimerA6ToZero(arg0) != 0) && (Particle_ApproachPrimAlpha(arg0, 0, 0xC) != 0)) {
                Particle_IncrementState(arg0);
            }
            break;

        case 5:
            Particle_ClearActiveFlag(arg0);
            break;
    }

    if (Particle_HasFlag4(arg0) != 0) {
        Particle_AnimLoopForward(arg0, 0, 7, 1, 2, -1);
        func_84333570(arg0);
    }
}

void Particle_SmokePuff(ParticleEffectInstance* arg0) {
    UNUSED s32 pad[3];
    s16 sp22 = Particle_GetShortAC(arg0);
    s16 sp20 = Particle_GetShortCF(arg0);

    Particle_SetScaleFactor1(arg0, 0.4f);
    func_8140A578(arg0, RandomRangeSignedPlus(0x200, 0xE00));
    Particle_RotateY(arg0, RandomRangeSigned(0x1800));
    Particle_SetSpeed(arg0, 2.0f);

    switch (sp20) {
        case 0:
            SetPrimEnvColorFromPair(arg0, 0x1A);
            break;

        case 1:
            SetPrimEnvColorFromPair(arg0, 6);
            break;
    }

    Particle_SetPrimAlpha(arg0, 0xC8);
    Particle_SetTimerA6(arg0, sp22 * 2);
    Particle_DisableFlag4(arg0);
    Particle_IncrementState(arg0);
}

void func_84333884(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B8) {
        case 1:
            if (Particle_StartTimer2(arg0, 1) != 0) {
                Particle_IncrementFlag2Counter(arg0);
            }
            break;

        case 2:
            Particle_DecreaseRotationXTowards(arg0, -0x1800, 0x800);
            if (Particle_StartTimer2(arg0, 0x10) != 0) {
                Particle_IncrementFlag2Counter(arg0);
            }
            break;
    }

    if (arg0->unk_B8 > 0) {
        Particle_ApplyB2B4AndAddAll(arg0);
    }
}

void Particle_SmokePuffHandler(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            Particle_SmokePuff(arg0);
            break;

        case 2:
            if (Particle_DecrementTimerA6ToZeroWithCallback(arg0) != 0) {
                Particle_EnableFlag2(arg0);
                Particle_EnableFlag4(arg0);
            }
            break;

        case 3:
            Particle_AnimLoopForwardComplete(arg0, 0, 7, 1, 2, 0);
            Particle_ApproachPrimAlpha(arg0, 0x20, 4);
            Particle_ApproachScaleFactor1(arg0, 0.75f, 0.05f);
            break;

        case 4:
            Particle_ClearActiveFlag(arg0);
            break;
    }

    if (Particle_HasFlag4(arg0) != 0) {
        func_84333884(arg0);
    }
}

void func_84333A20(ParticleEffectInstance* arg0, s16 arg1) {
    UNUSED s32 pad[3];
    s16 sp22 = Particle_GetShortAC(arg0);

    Particle_SetScaleFactor1(arg0, 0.2f);
    func_8140A578(arg0, RandomRangeSignedPlus(0x200, 0xE00));
    Particle_RotateY(arg0, RandomRangeSigned(0x2000));
    Particle_SetSpeed(arg0, 2.0f);

    switch (arg1) {
        case 0:
            SetPrimEnvColorFromPair(arg0, 0x17);
            break;

        case 1:
            SetPrimEnvColorFromPair(arg0, 0x18);
            break;
    }

    Particle_SetTimerA6(arg0, sp22 * 2);
    Particle_DisableFlag4(arg0);
    Particle_IncrementState(arg0);
}

void func_84333B04(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B8) {
        case 1:
            if (Particle_StartTimer2(arg0, arg0->unk_AE) != 0) {
                Particle_IncrementFlag2Counter(arg0);
            }
            break;

        case 2:
            Particle_ApproachRotationXWrapToTarget(arg0, 0x4000, 0x800);
            if (Particle_StartTimer2(arg0, 0x10) != 0) {
                Particle_IncrementFlag2Counter(arg0);
            }
            break;
    }

    if (arg0->unk_B8 > 0) {
        Particle_ApplyB2B4AndAddAll(arg0);
    }
}

void func_84333BA8(ParticleEffectInstance* arg0) {
    s16 temp_v0 = Particle_GetShortCF(arg0);

    switch (arg0->unk_B2) {
        case 1:
            func_84333A20(arg0, temp_v0);
            break;

        case 2:
            if (Particle_DecrementTimerA6ToZeroWithCallback(arg0) != 0) {
                Particle_EnableFlag2(arg0);
                Particle_EnableFlag4(arg0);
                Particle_SetShortAE(arg0, RandomMod(3));
                Particle_SetTimerA6(arg0, 8);
            }
            break;

        case 3:
            switch (temp_v0) {
                case 0:
                    Particle_ApproachPrimB(arg0, 0, 0x20);
                    Particle_ApproachEnvG(arg0, 0, 0x20);
                    break;

                case 1:
                    Particle_ApproachPrimR(arg0, 0, 0x20);
                    Particle_ApproachEnvG(arg0, 0x78, 0x10);
                    break;
            }
            Particle_DecrementTimerA6ToZeroWithCallback(arg0);
            break;

        case 4:
            switch (temp_v0) {
                case 0:
                    Particle_ApproachPrimG(arg0, 0, 0x20);
                    Particle_ApproachEnvR(arg0, 0, 0x20);
                    break;

                case 1:
                    Particle_ApproachPrimG(arg0, 0x78, 0xC);
                    Particle_ApproachEnvG(arg0, 0, 0xA);
                    break;
            }

            if (Particle_ApproachPrimAlpha(arg0, 0, 0x18) != 0) {
                Particle_IncrementState(arg0);
            }
            break;

        case 5:
            Particle_ClearActiveFlag(arg0);
            break;
    }

    if (Particle_HasFlag4(arg0) != 0) {
        Particle_AnimLoopForward(arg0, 0, 7, 1, 2, -1);
        Particle_ApproachScaleFactor1(arg0, 0.02f, 0.015f);
        func_84333B04(arg0);
        if (arg0->unk_2C.y <= 0.0f) {
            Particle_ClearActiveFlag(arg0);
        }
    }
}

void func_84333DC4(ParticleEffectInstance* arg0) {
    Particle_AddVelocityBackward(arg0, 33.0f);
    Particle_SetScaleFactor1(arg0, 0.67f);
    SetPrimColorFromPalette(arg0, Particle_GetShortCF(arg0));
    Particle_SetPrimAlpha(arg0, 0xC8);
    Particle_IncrementState(arg0);
}

void func_84333E28(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            func_84333DC4(arg0);
            break;

        case 2:
            if (Particle_ApproachScaleFactor1(arg0, 6.67f, 0.67f) != 0) {
                Particle_IncrementState(arg0);
            }
            break;

        case 3:
            Particle_ProcessTimer80(arg0, 0);
            break;

        case 4:
            if (Particle_ApproachPrimAlpha(arg0, 0x20, 8) != 0) {
                Particle_IncrementState(arg0);
            }
            break;

        case 5:
            Particle_ResetState(arg0);
            break;
    }
}

void func_84333EE8(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            func_84333DC4(arg0);
            break;

        case 2:
            if (Particle_ApproachScaleFactor1(arg0, 8.0f, 1.0f) != 0) {
                Particle_IncrementState(arg0);
            }
            break;

        case 3:
            Particle_ProcessTimer80(arg0, 8);
            break;

        case 4:
            if (Particle_ApproachPrimAlpha(arg0, 0x20, 8) != 0) {
                Particle_IncrementState(arg0);
            }
            break;

        case 5:
            Particle_ResetState(arg0);
            break;
    }

    Particle_RotateX(arg0, 0x1000);
}

void func_84333FBC(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            func_84333DC4(arg0);
            break;

        case 2:
            if (Particle_ApproachScaleFactor1(arg0, 8.0f, 1.0f) != 0) {
                Particle_IncrementState(arg0);
            }
            break;

        case 3:
            Particle_ProcessTimer80(arg0, 8);
            break;

        case 4:
            if (Particle_ApproachPrimAlpha(arg0, 0x20, 8) != 0) {
                Particle_IncrementState(arg0);
            }
            break;

        case 5:
            Particle_ResetState(arg0);
            break;
    }

    Particle_RotateX(arg0, 0x1000);

    if (gTimerMask2 == 0) {
        func_8140D658(arg0, RandomMod(6));
    }
}

void Particle_Firework(ParticleEffectInstance* arg0) {
    s16 sp26 = Particle_GetShortAC(arg0);

    Particle_SetScaleFactor1(arg0, 0.5f);
    Particle_SetAccelerationY(arg0, 2.0f);
    Particle_SetRotationDeltaY(arg0, RandomMod(0x10000));
    SetPrimEnvColorFromPair(arg0, 0x1A);
    Particle_SetPrimAlpha(arg0, 0xFF);
    Particle_SetTimerA6(arg0, sp26 * 4);
    Particle_DisableFlag4(arg0);
    Particle_IncrementState(arg0);
}

void ParticleEffect_FireUpdate(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            Particle_Firework(arg0);
            break;

        case 2:
            if (Particle_DecrementTimerA6ToZeroWithCallback(arg0) != 0) {
                Particle_EnableFlag4(arg0);
                Particle_SetTimerA6(arg0, 0x10);
            }
            break;

        case 3:
            Particle_AnimLoopForwardComplete(arg0, 0, 7, 1, 2, -1);
            Particle_ApproachScaleFactor1(arg0, 1.0f, 0.1f);
            Particle_AddScaledVelocityY(arg0, 2.0f);
            Particle_UpdatePositionAndAccelFromYaw(arg0, 10.0f, 0x800);
            Particle_ApproachPrimG(arg0, 0, 4);
            Particle_ApproachEnvR(arg0, 0, 4);
            if ((Particle_DecrementTimerA6ToZero(arg0) != 0) && (Particle_ApproachPrimAlpha(arg0, 0, 0x18) != 0)) {
                Particle_IncrementState(arg0);
            }
            break;

        case 4:
            Particle_ResetState(arg0);
            break;
    }
}

void Particle_Spark(ParticleEffectInstance* arg0) {
    s16 sp26 = Particle_GetShortAC(arg0);

    Particle_SetScaleFactor1(arg0, 0.5f);
    Particle_SetVelocityYScaled(arg0, 10.0f);
    Particle_SetAccelerationY(arg0, 1.0f);
    SetPrimEnvColorFromPair(arg0, 0x1A);
    Particle_SetPrimAlpha(arg0, 0xFF);
    Particle_DisableFlag4(arg0);
    Particle_SetRotationDeltaY(arg0, (sp26 << 0x10) / 18);
    Particle_SetTimerA6(arg0, sp26 * 3);
    Particle_IncrementState(arg0);
}

void func_84334350(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            Particle_Spark(arg0);
            break;

        case 2:
            if (Particle_DecrementTimerA6ToZeroWithCallback(arg0) != 0) {
                Particle_EnableFlag4(arg0);
            }
            break;

        case 3:
            Particle_ApproachScaleFactor1(arg0, 1.0f, 0.1f);
            break;
    }

    if (Particle_HasFlag4(arg0) != 0) {
        Particle_UpdatePositionAndAccelFromYaw(arg0, 50.0f, 0);
    }
}

void func_843343F8(ParticleEffectInstance* arg0) {
    s16 sp26 = Particle_GetShortAC(arg0);

    Particle_SetScaleFactor1(arg0, 1.0f);
    Particle_SetVelocityYScaled(arg0, 10.0f);
    Particle_SetAccelerationY(arg0, 1.0f);
    SetPrimEnvColorFromPair(arg0, 0x1A);
    Particle_SetPrimAlpha(arg0, 0xFF);
    Particle_DisableFlag4(arg0);
    Particle_SetRotationDeltaY(arg0, (sp26 << 0x10) / 18);
    Particle_SetTimerA6(arg0, 0);
    Particle_IncrementState(arg0);
}

void func_843344A0(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 3:
            break;

        case 1:
            func_843343F8(arg0);
            break;

        case 2:
            if (Particle_DecrementTimerA6ToZeroWithCallback(arg0) != 0) {
                Particle_EnableFlag4(arg0);
            }
            break;

        case 4:
            Particle_ApproachPrimAlphaWithCallback(arg0, 0, 0x10);
            break;

        case 5:
            Particle_ResetState(arg0);
            break;
    }

    if (Particle_HasFlag4(arg0) != 0) {
        Particle_UpdatePositionAndAccelFromYaw(arg0, 50.0f, 0);
    }
}

void func_84334558(ParticleEffectInstance* arg0) {
    Particle_SetScaleFactor1(arg0, 0.4f);
    SetPrimEnvColorFromPair(arg0, 0x1A);
    Particle_SetPrimAlpha(arg0, 0xA0);
    Particle_IncrementState(arg0);
}

void func_843345A0(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            func_84334558(arg0);
            break;

        case 2:
            Particle_AnimLoopForwardComplete(arg0, 2, 7, 1, 2, 0);
            Particle_ApproachPrimAlpha(arg0, 0x20, 0x18);
            break;

        case 3:
            Particle_ResetState(arg0);
            break;
    }

    Particle_ApproachScaleFactor1(arg0, 0.6f, 0.05f);
}

void func_84334654(ParticleEffectInstance* arg0) {
    Particle_SetScaleFactor1(arg0, 0.4f);
    Particle_SetSpeed(arg0, 8.0f);
    SetPrimEnvColorFromPair(arg0, 0x29);
    Particle_SetParamC7(arg0, 2);
    Particle_SetPrimAlpha(arg0, 0xFF);
    Particle_IncrementState(arg0);
}

void func_843346BC(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            func_84334654(arg0);
            break;

        case 2:
            Particle_AnimLoopForwardComplete(arg0, 3, 5, 1, 1, 0);
            break;

        case 3:
            Particle_ProcessTimer80(arg0, 0xF);
            break;

        case 4:
            Particle_ResetState(arg0);
            break;
    }

    if (Particle_HasFlag4(arg0) != 0) {
        AreBothColorsSupported(arg0, 0x2A, 0x1C);
        Particle_ApplyB2B4AndAddAll(arg0);
        ParticleNode_CreateMultiple(arg0, func_843345A0, &gParticleEffectData[0x4A], 1);
    }
}

void func_843347A4(ParticleEffectInstance* arg0) {
    Particle_GetShortAC(arg0);
    Particle_SetSpeed(arg0, 0.2f);
    Particle_SetScaleFactor1(arg0, 1.0f);
    SetPrimEnvColorFromPair(arg0, 0x1D);
    Particle_SetPrimAlpha(arg0, 0xFF);
    Particle_IncrementState(arg0);
}

void func_84334808(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            func_843347A4(arg0);
            break;

        case 2:
            Particle_ProcessTimer80(arg0, 1);
            break;

        case 3:
            Particle_AnimLoopForwardComplete(arg0, 0, 3, 1, 2, 0);
            Particle_SetTargetVelocityBackward(arg0);
            AreBothColorsSupported(arg0, 0, 0x20);
            Particle_ApproachScaleFactor1(arg0, 1.5f, 0.1f);
            break;

        case 4:
            Particle_ClearActiveFlag(arg0);
            break;
    }
}

void func_843348DC(ParticleEffectInstance* arg0) {
    Vec3s sp28;
    UNUSED s32 pad[1];

    Particle_GetShortCF(arg0);
    Particle_GetShortAC(arg0);
    Particle_SetScaleFactor1(arg0, 0.45f);
    sp28.x = RandomRangeSigned(0x2000);
    sp28.y = RandomRangeSignedPlus(0x3000, 0);
    sp28.z = 0;
    Particle_AddRotationDeltaVec(arg0, sp28);
    SetPrimEnvColorFromPair(arg0, 0x1D);
    Particle_SetPrimAlpha(arg0, 0x64);
    Particle_SetSpeed(arg0, 2.5f);
    Particle_IncrementState(arg0);
}

void func_84334994(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            func_843348DC(arg0);
            break;

        case 2:
            Particle_AnimLoopForwardComplete(arg0, 0, 7, 1, 2, 0);
            Particle_ApproachSpeedScaled(arg0, 0.5, 0.5f);
            Particle_ApproachPrimAlpha(arg0, 0x20, 4);
            break;

        case 3:
            Particle_ClearActiveFlag(arg0);
            break;
    }

    if (Particle_IsActive(arg0) != 0) {
        Particle_ApproachScaleFactor1(arg0, 0.75f, 0.1f);
        Particle_ApplyB2B4AndAddAll(arg0);
        AreBothColorsSupported(arg0, 0x1A, 0x10);
    }
}

void Particle_SetColorByIndex(ParticleEffectInstance* arg0, u8 arg1) {
    u16 sp1E;

    func_8140BEF8(arg0, arg1);

    switch (arg1) {
        case 0:
            sp1E = 0x1A;
            break;

        case 1:
            sp1E = 0x2A;
            break;

        case 2:
            sp1E = 0x24;
            break;

        case 3:
            sp1E = 0x2C;
            break;
    }

    SetPrimEnvColorFromPair(arg0, sp1E);
}

void func_84334B04(void) {
}

void func_84334B0C(ParticleEffectInstance* arg0) {
    UNUSED u16 pad;
    u16 sp1C;
    u16 sp1A;

    switch (Particle_GetShortCF(arg0)) {
        case 0:
            sp1C = 0x2E;
            sp1A = 0x10;
            break;

        case 1:
            sp1C = 0x2D;
            sp1A = 0x10;
            break;

        case 2:
            sp1C = 0x2D;
            sp1A = 0x10;
            break;

        case 3:
            sp1C = 0x2B;
            sp1A = 0x10;
            break;
    }

    AreBothColorsSupported(arg0, sp1C, sp1A);
}

void Particle_Explosion(ParticleEffectInstance* arg0) {
    s16 sp26 = Particle_GetShortAC(arg0);
    s16 sp24 = Particle_GetShortCF(arg0);
    s16 sp22 = Particle_GetShortCE(arg0);

    switch (sp26) {
        case 0:
            Particle_SetVelocityScaledXYZ(arg0, 0.0f, -5.0f, 0.0f);
            break;

        case 1:
            Particle_SetVelocityScaledXYZ(arg0, 0.0f, 5.0f, 5.0f);
            break;

        case 2:
            Particle_SetVelocityScaledXYZ(arg0, 0.0f, 5.0f, -5.0f);
            break;
    }

    switch (sp22) {
        case 0:
            Particle_SetScaleFactor1(arg0, 0.5f);
            Particle_SetScaleFactor2(arg0, 1.0f);
            Particle_SetScaleFactor3(arg0, 0.1f);
            break;

        case 1:
            Particle_SetScaleFactor1(arg0, 0.75f);
            Particle_SetScaleFactor2(arg0, 1.5f);
            Particle_SetScaleFactor3(arg0, 0.15f);
            break;

        case 2:
            Particle_SetScaleFactor1(arg0, 1.0f);
            Particle_SetScaleFactor2(arg0, 2.0f);
            Particle_SetScaleFactor3(arg0, 0.2f);
            break;
    }

    SetPrimEnvColorFromPair(arg0, sp24);
    Particle_SetParamC7(arg0, 1);
    Particle_SetPrimAlpha(arg0, 0xC8);
    Particle_SetTimerA6(arg0, sp26 * 2);
    Particle_DisableFlag4(arg0);
    Particle_IncrementState(arg0);
}

void func_84334D7C(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            Particle_Explosion(arg0);
            break;

        case 2:
            if (Particle_DecrementTimerA6ToZeroWithCallback(arg0) != 0) {
                Particle_EnableFlag4(arg0);
            }
            break;

        case 3:
            Particle_ApproachScaleFactor2(arg0);
            Particle_AnimLoopForwardComplete(arg0, 2, 7, 1, 1, 0);
            if (arg0->unk_C7 >= 6) {
                Particle_ApproachPrimAlpha(arg0, 0x64, 0x4E);
            }
            break;

        case 4:
            Particle_ClearActiveFlag(arg0);
            break;
    }
}

void Particle_Firefly(ParticleEffectInstance* arg0) {
    Vec3f sp2C;
    s16 sp2A;
    s16 sp28;

    sp2A = Particle_GetShortAC(arg0);
    sp28 = Particle_GetShortCF(arg0);
    sp2C.x = RandomRangeSigned(0xA);
    sp2C.y = RandomRangeSignedPlus(0xF, 0xA);
    sp2C.z = RandomRangeSigned(0xF);
    Particle_AddVelocityScaledVec(arg0, sp2C);
    Particle_SetSpeed(arg0, (RandomMod(5) * 0.25f) + 3.0f);
    Particle_SetScaleFactor1(arg0, 0.75f);
    SetPrimEnvColorFromPair(arg0, sp28);
    Particle_SetPrimAlpha(arg0, 0xFF);
    Particle_SetTimerA6(arg0, sp2A * 2);
    Particle_DisableFlag4(arg0);
    Particle_IncrementState(arg0);
}

void ParticleEffect_StateHandler_34F84(ParticleEffectInstance* arg0) {
    Particle_GetShortCE(arg0);

    switch (arg0->unk_B2) {
        case 1:
            Particle_Firefly(arg0);
            break;
        case 2:
            if (Particle_DecrementTimerA6ToZeroWithCallback(arg0) != 0) {
                Particle_EnableFlag4(arg0);
            }
            break;

        case 3:
            Particle_SetTargetVelocityBackward(arg0);
            Particle_ApproachScaleFactor2(arg0);
            Particle_AnimLoopForwardComplete(arg0, 1, 7, 1, 1, 0);

            if (arg0->unk_C7 >= 6) {
                Particle_ApproachPrimAlpha(arg0, 0x64, 0x4E);
            }

            if (arg0->unk_C7 >= 4) {}
            break;

        case 4:
            Particle_ClearActiveFlag(arg0);
            break;
    }
}

void Particle_Sparkle(ParticleEffectInstance* arg0) {
    Vec3s sp30;
    Vec3f sp24;
    s16 sp22;
    s16 sp20;

    sp22 = Particle_GetShortAC(arg0);
    sp20 = Particle_GetShortCF(arg0);
    sp24.x = RandomRangeSigned(0xA);
    sp24.y = RandomRangeSignedPlus(0xA, 5);
    sp24.z = RandomRangeSigned(0xA);
    Particle_AddVelocityScaledVec(arg0, sp24);
    Particle_SetScaleFactor1(arg0, 1.0f);
    Particle_SetSpeed(arg0, 0.5f);
    sp30.x = RandomRangeSigned(0x2000);
    sp30.y = RandomRangeSigned(0x2000);
    sp30.z = 0;
    Particle_AddRotationDeltaVec(arg0, sp30);
    SetPrimEnvColorFromPair(arg0, sp20);
    Particle_SetPrimAlpha(arg0, 0xC8);
    Particle_SetTimerA6(arg0, sp22 * 2);
    Particle_SetParamC7(arg0, 2);
    Particle_DisableFlag4(arg0);
    Particle_IncrementState(arg0);
}

void func_843351C8(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            Particle_Sparkle(arg0);
            break;

        case 2:
            if (Particle_DecrementTimerA6ToZeroWithCallback(arg0) != 0) {
                Particle_EnableFlag4(arg0);
            }
            break;

        case 3:
            Particle_AnimLoopForwardComplete(arg0, 2, 7, 1, 1, 0);
            Particle_ApproachScaleFactor1(arg0, 1.2f, 0.05f);
            Particle_ApproachPrimAlpha(arg0, 0x64, 0x10);
            Particle_ApplyB2B4AndAddAll(arg0);
            break;

        case 4:
            Particle_ResetState(arg0);
            break;
    }
}

void func_843352AC(ParticleEffectInstance* arg0) {
    s16 sp36 = Particle_GetShortAC(arg0);
    Vec3s sp30;
    UNUSED s32 pad[3];

    Particle_SetRandomVelocityXYZ(arg0, 5, 5, 5);
    Particle_SetScaleFactor1(arg0, 0.5f);
    Particle_SetSpeed(arg0, 1.0f);
    sp30.x = 0x2000 - RandomMod(0x4000);
    sp30.y = 0x2000 - RandomMod(0x4000);
    sp30.z = 0;
    Particle_AddRotationDeltaVec(arg0, sp30);
    Particle_AddTargetRotationXY(arg0, sp30.x, sp30.y);
    Particle_SetRotationDeltaXY(arg0, 0, 0);
    SetPrimEnvColorFromPair(arg0, 0x1A);
    Particle_SetPrimAlpha(arg0, 0xC8);
    Particle_SetTimerA6(arg0, sp36 * 3);
    Particle_DisableFlag4(arg0);
    Particle_IncrementState(arg0);
}

void func_843353C4(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            func_843352AC(arg0);
            break;

        case 2:
            if (Particle_DecrementTimerA6ToZeroWithCallback(arg0) != 0) {
                Particle_SetTimerA6(arg0, 0xA);
                Particle_EnableFlag4(arg0);
            }
            break;

        case 3:
            Particle_ApproachScaleFactor1(arg0, 1.0f, 0.1f);
            Particle_ApproachPrimR(arg0, 0, 0xC);
            Particle_ApproachPrimG(arg0, 0, 0x20);
            Particle_ApplyB2B4AndAddAll(arg0);
            Particle_AddVelocityYScaled(arg0, 0.4f);
            func_84334B0C(arg0);
            if ((Particle_DecrementTimerA6ToZero(arg0) != 0) && (Particle_ApproachPrimAlpha(arg0, 0x20, 0x10) != 0)) {
                Particle_IncrementState(arg0);
            }
            break;

        case 4:
            Particle_ResetState(arg0);
            break;
    }
}

void Particle_Star(ParticleEffectInstance* arg0) {
    s16 sp36 = Particle_GetShortAC(arg0);
    Vec3s sp30;
    Vec3f sp24;

    sp24.x = RandomRangeSigned(0x19);
    sp24.y = RandomRangeSignedPlus(0xF, 5);
    sp24.z = RandomRangeSigned(0xA);
    Particle_AddVelocityScaledVec(arg0, sp24);
    Particle_SetScaleFactor1(arg0, 0.15f);
    Particle_SetSpeed(arg0, 0.5f);
    sp30.x = 0x2000 - RandomMod(0x4000);
    sp30.y = 0x2000 - RandomMod(0x4000);
    sp30.z = 0;
    Particle_AddRotationDeltaVec(arg0, sp30);
    Particle_AddTargetRotationXY(arg0, sp30.x, sp30.y);
    Particle_SetRotationDeltaXY(arg0, 0, 0);
    Particle_SetColorByIndex(arg0, (sp36 % 4) & 0xFF);
    Particle_SetPrimAlpha(arg0, 0xC8);
    Particle_SetTimerA6(arg0, sp36 * 1);
    Particle_SetParamC7(arg0, 2);
    Particle_DisableFlag4(arg0);
    Particle_IncrementState(arg0);
}

void func_84335668(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            Particle_Star(arg0);
            break;

        case 2:
            if (Particle_DecrementTimerA6ToZeroWithCallback(arg0) != 0) {
                Particle_EnableFlag4(arg0);
            }
            break;

        case 3:
            Particle_AnimLoopForwardComplete(arg0, 2, 7, 1, 1, 0);
            Particle_ApproachScaleFactor1(arg0, 0.45000002f, 0.075f);
            Particle_ApproachPrimAlpha(arg0, 0x64, 0x10);
            Particle_ApplyB2B4AndAddAll(arg0);
            break;

        case 4:
            Particle_ResetState(arg0);
            break;
    }
}

void Particle_Twinkle(ParticleEffectInstance* arg0) {
    s16 sp36 = Particle_GetShortAC(arg0);
    Vec3s sp30;
    UNUSED s32 pad[3];

    Particle_SetRandomVelocityXYZ(arg0, 5, 0xA, 0xA);
    Particle_SetScaleFactor1(arg0, 0.90000004f);
    Particle_SetSpeed(arg0, 1.0f);
    sp30.x = RandomRangeSigned(0x2000);
    sp30.y = RandomMod(0x10000);
    sp30.z = 0;
    Particle_AddRotationDeltaVec(arg0, sp30);
    Particle_SetColorByIndex(arg0, (sp36 % 4) & 0xFF);
    Particle_SetPrimAlpha(arg0, 0xC8);
    Particle_SetTimerA6(arg0, 0);
    Particle_SetParamC7(arg0, 2);
    Particle_DisableFlag4(arg0);
    Particle_IncrementState(arg0);
}

void func_84335848(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            Particle_Twinkle(arg0);
            break;

        case 2:
            if (Particle_DecrementTimerA6ToZeroWithCallback(arg0) != 0) {
                Particle_SetTimerA6(arg0, 5);
                Particle_EnableFlag4(arg0);
            }
            break;

        case 3:
            Particle_AnimLoopForwardComplete(arg0, 0, 7, 1, 2, 0);
            Particle_ApproachScaleFactor1(arg0, 1.05f, 0.075f);
            Particle_ApproachSpeedScaled(arg0, 0.5, 0.5f);
            Particle_ApplyB2B4AndAddAll(arg0);
            if (Particle_DecrementTimerA6ToZero(arg0) != 0) {
                Particle_AddScaledVelocityY(arg0, 0.5f);
                Particle_ApproachPrimAlpha(arg0, 0x64, 0x10);
            }
            break;

        case 4:
            Particle_ClearActiveFlag(arg0);
            break;
    }
}

void Particle_Glitter(ParticleEffectInstance* arg0) {
    s16 sp36 = Particle_GetShortAC(arg0);
    Vec3s sp30;
    UNUSED s32 pad[3];

    Particle_SetRandomVelocityXYZ(arg0, 5, 5, 5);
    Particle_SetScaleFactor1(arg0, 0.75f);
    Particle_SetSpeed(arg0, 1.0f);
    sp30.x = 0x2000 - RandomMod(0x4000);
    sp30.y = RandomMod(0x10000);
    sp30.z = 0;
    Particle_AddRotationDeltaVec(arg0, sp30);
    Particle_AddTargetRotationXY(arg0, sp30.x, sp30.y);
    Particle_SetRotationDeltaXY(arg0, 0, 0);
    Particle_SetColorByIndex(arg0, (sp36 % 4) & 0xFF);
    Particle_SetPrimAlpha(arg0, 0xC8);
    Particle_SetTimerA6(arg0, sp36 * 3);
    Particle_DisableFlag4(arg0);
    Particle_IncrementState(arg0);
}

void func_84335A84(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            Particle_Glitter(arg0);
            break;

        case 2:
            if (Particle_DecrementTimerA6ToZeroWithCallback(arg0) != 0) {
                Particle_SetTimerA6(arg0, 0xA);
                Particle_EnableFlag4(arg0);
            }
            break;

        case 3:
            Particle_ApproachPrimR(arg0, 0, 0xC);
            Particle_ApproachPrimG(arg0, 0, 0x20);
            Particle_ApproachScaleFactor1(arg0, 1.5f, 0.15f);
            func_84334B0C(arg0);
            Particle_ApplyB2B4AndAddAll(arg0);
            Particle_AddVelocityYScaled(arg0, 0.4f);
            if ((Particle_DecrementTimerA6ToZero(arg0) != 0) && (Particle_ApproachPrimAlpha(arg0, 0x20, 0x10) != 0)) {
                Particle_IncrementState(arg0);
            }
            break;

        case 4:
            Particle_ResetState(arg0);
            break;
    }
}

void func_84335BA0(ParticleEffectInstance* arg0) {
    s16 sp36;
    Vec3s sp30;
    Vec3f sp24;

    sp36 = Particle_GetShortAC(arg0);
    sp24.x = RandomRangeSigned(0x14);
    sp24.y = RandomRangeSignedPlus(0xF, 0xA);
    sp24.z = RandomRangeSigned(0xF);
    Particle_AddVelocityScaledVec(arg0, sp24);
    Particle_SetScaleFactor1(arg0, 0.1f);
    sp30.x = RandomMod(0x10000);
    sp30.y = RandomMod(0x10000);
    sp30.z = 0;
    Particle_AddRotationDeltaVec(arg0, sp30);
    Particle_AddTargetRotationXY(arg0, sp30.x, sp30.y);
    Particle_SetRotationDeltaXY(arg0, 0, 0);
    Particle_SetColorByIndex(arg0, (sp36 % 4) & 0xFF);
    Particle_SetPrimAlpha(arg0, 0xC8);
    Particle_SetTimerA6(arg0, sp36 * 2);
    Particle_SetParamC7(arg0, 2);
    Particle_DisableFlag4(arg0);
    Particle_IncrementState(arg0);
}

void func_84335D10(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            func_84335BA0(arg0);
            break;

        case 2:
            if (Particle_DecrementTimerA6ToZeroWithCallback(arg0) != 0) {
                Particle_EnableFlag4(arg0);
            }
            break;

        case 3:
            Particle_AnimLoopForwardComplete(arg0, 2, 7, 1, 1, 0);
            Particle_ApproachScaleFactor1(arg0, 0.3f, 0.05f);
            Particle_ApproachPrimAlpha(arg0, 0x64, 0x10);
            break;

        case 4:
            Particle_ResetState(arg0);
            break;
    }
}

void Particle_FireRing(ParticleEffectInstance* arg0) {
    s16 temp_s1 = Particle_GetShortAC(arg0);

    Particle_SetScaleFactor1(arg0, 0.75f);

    switch (temp_s1) {
        case 0:
            Particle_SetVelocityScaledXYZ(arg0, 0.0f, -3.0f, 0.0f);
            break;

        case 1:
            Particle_SetVelocityScaledXYZ(arg0, 0.0f, 3.0f, 3.0f);
            break;

        case 2:
            Particle_SetVelocityScaledXYZ(arg0, 0.0f, 3.0f, -3.0f);
            break;
    }

    SetPrimEnvColorFromPair(arg0, 0x17);
    Particle_SetPrimAlpha(arg0, 0xFF);
    Particle_SetTimerA6(arg0, temp_s1 * 4);
    Particle_DisableFlag4(arg0);
    Particle_IncrementState(arg0);
}

void func_84335EF8(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            Particle_FireRing(arg0);
            break;

        case 2:
            if (Particle_ProcessTimer80(arg0, arg0->unk_A6) != 0) {
                Particle_EnableFlag4(arg0);
            }
            break;

        case 3:
            Particle_AnimLoopForwardComplete(arg0, 0, 7, 1, 1, 0);
            Particle_ApproachScaleFactor1(arg0, 1.0f, 0.02f);
            Particle_ApproachPrimB(arg0, 0, 0x20);
            Particle_ApproachEnvG(arg0, 0, 0x20);
            if (arg0->unk_C7 >= 6) {
                Particle_ApproachPrimG(arg0, 0, 0x20);
                Particle_ApproachPrimAlpha(arg0, 0x64, 0x4E);
            }
            break;

        case 4:
            Particle_ClearActiveFlag(arg0);
            break;
    }
}

void Particle_ExplosionVariant(ParticleEffectInstance* arg0, s16 arg1, s16 arg2) {
    UNUSED s32 pad[2];
    s16 sp26 = Particle_GetShortAC(arg0);

    Particle_SetVelocityYScaled(arg0, -10.0f);
    Particle_AddVelocityForward(arg0, 50.0f);
    Particle_SetScaleFactor1(arg0, 0.5f);
    Particle_SetSpeed(arg0, 5.0f);

    switch (arg1) {
        case 0:
            func_8140A578(arg0, RandomRangeSigned(0x800));
            Particle_RotateY(arg0, RandomRangeSignedPlus(0x1000, 0x8000));
            break;

        case 1:
            func_8140A578(arg0, RandomRangeSigned(0xA00));
            Particle_RotateY(arg0, func_81400B4C(0xD00, 0xF400) + 0x8000);
            break;
    }

    switch (arg2) {
        case 0:
            SetPrimEnvColorFromPair(arg0, 0x1A);
            break;

        case 1:
            SetPrimEnvColorFromPair(arg0, 6);
            break;
    }

    Particle_SetPrimAlpha(arg0, 0xC8);
    Particle_SetTimerA6(arg0, sp26 * 4);
    Particle_DisableFlag4(arg0);
    Particle_IncrementState(arg0);
}

void func_8433617C(ParticleEffectInstance* arg0, s32 arg1) {
    s16 temp_v0 = Particle_GetShortCF(arg0);

    switch (arg0->unk_B2) {
        case 1:
            Particle_ExplosionVariant(arg0, arg1, temp_v0);
            break;

        case 2:
            if (Particle_DecrementTimerA6ToZeroWithCallback(arg0) != 0) {
                Particle_EnableFlag4(arg0);
            }
            break;

        case 3:
            Particle_SetTimerA6(arg0, 0xC);
            Particle_IncrementState(arg0);
            break;

        case 4:
            switch (temp_v0) {
                case 0:
                    Particle_ApproachPrimG(arg0, 0, 0x10);
                    Particle_ApproachEnvR(arg0, 0, 0x10);
                    break;

                case 1:
                    Particle_ApproachPrimG(arg0, 0, 0xA);
                    Particle_ApproachEnvG(arg0, 0, 5);
                    break;
            }

            if ((Particle_DecrementTimerA6ToZero(arg0) != 0) && (Particle_ApproachPrimAlpha(arg0, 0, 0x18) != 0)) {
                Particle_IncrementState(arg0);
            }
            break;

        case 5:
            Particle_ResetState(arg0);
            break;
    }

    if (Particle_HasFlag4(arg0) != 0) {
        Particle_ApproachRotationXWrapToTarget(arg0, -0xC00, 0x100);
        Particle_ApproachScaleFactor1(arg0, 1.2f, 0.04f);
        Particle_ApplyB2B4AndAddAll(arg0);
        Particle_AnimLoopForward(arg0, 0, 7, 1, 2, -1);
    }
}

void func_84336320(ParticleEffectInstance* arg0) {
    func_8433617C(arg0, 0);
}

void func_84336340(ParticleEffectInstance* arg0) {
    func_8433617C(arg0, 1);
}

void func_84336360(ParticleEffectInstance* arg0) {
    s16 sp36 = Particle_GetShortCF(arg0);
    UNUSED s32 pad[3];
    s16 sp26 = Particle_GetShortAC(arg0);

    Particle_SetScaleFactor1(arg0, 0.4f);
    Particle_AddVelocityForward(arg0, 15.0f);
    func_8140A578(arg0, RandomRangeSignedPlus(0x200, 0xE00));
    Particle_RotateY(arg0, RandomRangeSignedPlus(0x3800, 0x8000));
    Particle_SetTargetRotationX(arg0, -0x4000);
    Particle_SetRotationDeltaX(arg0, 0x1000);
    Particle_SetSpeed(arg0, 3.0f);

    switch (sp36) {
        case 0:
            SetPrimEnvColorFromPair(arg0, 0x1A);
            break;

        case 1:
            SetPrimEnvColorFromPair(arg0, 6);
            break;
    }

    Particle_SetPrimAlpha(arg0, 0xC8);
    Particle_SetTimerA6(arg0, sp26 * 2);
    Particle_DisableFlag4(arg0);
    Particle_IncrementState(arg0);
}

void func_84336480(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B8) {
        case 1:
            if (Particle_StartTimer2(arg0, 1) != 0) {
                Particle_IncrementFlag2Counter(arg0);
            }
            break;

        case 2:
            Particle_ApproachRotationXWrap(arg0);
            if (Particle_StartTimer2(arg0, 0x10) != 0) {
                Particle_IncrementFlag2Counter(arg0);
            }
            break;
    }

    if (arg0->unk_B8 > 0) {
        Particle_ApplyB2B4AndAddAll(arg0);
    }
}

void func_84336520(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            func_84336360(arg0);
            break;

        case 2:
            if (Particle_DecrementTimerA6ToZeroWithCallback(arg0) != 0) {
                Particle_EnableFlag2(arg0);
                Particle_EnableFlag4(arg0);
            }
            break;

        case 3:
            Particle_AnimLoopForwardComplete(arg0, 0, 7, 1, 2, 0);
            Particle_ApproachPrimAlpha(arg0, 0x20, 4);
            Particle_ApproachScaleFactor1(arg0, 1.2f, 0.1f);
            break;

        case 4:
            Particle_ClearActiveFlag(arg0);
            break;
    }

    if (Particle_HasFlag4(arg0) != 0) {
        func_84336480(arg0);
    }
}

void func_8433661C(ParticleEffectInstance* arg0) {
    UNUSED s32 pad[3];
    s16 sp22 = Particle_GetShortAC(arg0);
    s16 sp20 = Particle_GetShortCF(arg0);

    Particle_SetScaleFactor1(arg0, 0.6f);
    Particle_AddVelocityYScaled(arg0, 15.0f);
    Particle_AddVelocityBackward(arg0, 20.0f);

    switch (sp20) {
        case 0:
            Particle_SetSpeed(arg0, 1.5f);
            func_8140A578(arg0, -0x4000);
            break;

        case 1:
            Particle_SetSpeed(arg0, 2.0f);
            Particle_RotateY(arg0, 0x4000);
            func_8140A578(arg0, -0xE00);
            break;

        case 2:
            Particle_SetSpeed(arg0, 2.0f);
            Particle_RotateY(arg0, -0x4000);
            func_8140A578(arg0, -0xE00);
            break;

        case 3:
            Particle_SetSpeed(arg0, 2.5f);
            Particle_RotateY(arg0, 0x4000);
            func_8140A578(arg0, 0x2000);
            break;

        case 4:
            Particle_SetSpeed(arg0, 2.5f);
            Particle_RotateY(arg0, -0x4000);
            func_8140A578(arg0, 0x2000);
            break;
    }

    SetPrimEnvColorFromPair(arg0, 0x17);
    Particle_SetTimerA6(arg0, sp22 * 2);
    Particle_DisableFlag4(arg0);
    Particle_IncrementState(arg0);
}

void func_8433679C(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B8) {
        case 1:
            if (Particle_StartTimer2(arg0, 2) != 0) {
                Particle_IncrementFlag2Counter(arg0);
            }
            break;

        case 2:
            if (Particle_StartTimer2(arg0, 0x10) != 0) {
                Particle_IncrementFlag2Counter(arg0);
            }
            break;
    }

    if (arg0->unk_B8 > 0) {
        Particle_ApplyB568AndAddAll(arg0);
    }
}

void func_84336830(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            func_8433661C(arg0);
            break;

        case 2:
            if (Particle_DecrementTimerA6ToZeroWithCallback(arg0) != 0) {
                Particle_EnableFlag2(arg0);
                Particle_EnableFlag4(arg0);
                Particle_SetTimerA6(arg0, 0xB);
            }
            break;

        case 3:
            Particle_ApproachPrimB(arg0, 0, 0x18);
            Particle_ApproachEnvG(arg0, 0, 0x18);
            if (Particle_DecrementTimerA6ToZeroWithCallback(arg0) != 0) {
                Particle_SetTimerA6(arg0, 0xC);
            }
            break;

        case 4:
            Particle_ApproachPrimG(arg0, 0, 0x10);
            Particle_ApproachEnvR(arg0, 0, 0x10);
            if ((Particle_DecrementTimerA6ToZero(arg0) != 0) && (Particle_ApproachPrimAlpha(arg0, 0, 0x40) != 0)) {
                Particle_IncrementState(arg0);
            }
            break;

        case 5:
            Particle_ClearActiveFlag(arg0);
            break;
    }

    if (Particle_HasFlag4(arg0) != 0) {
        Particle_ApproachScaleFactor1(arg0, 0.8f, 0.025f);
        Particle_AnimLoopForward(arg0, 0, 7, 1, 2, -1);
        func_8433679C(arg0);
    }
}

void func_843369AC(ParticleEffectInstance* arg0) {
    UNUSED s32 pad[3];
    s16 sp22 = Particle_GetShortAC(arg0);

    Particle_GetShortCF(arg0);
    Particle_SetScaleFactor1(arg0, 0.7f);
    Particle_SetRandomVelocityX(arg0, 0xF);
    Particle_SetRandomVelocityYOffset(arg0, 0xF, 0xA);
    Particle_SetRandomVelocityZ(arg0, 0xF);
    SetPrimEnvColorFromPair(arg0, 0x1A);
    Particle_SetPrimAlpha(arg0, 0xC8);
    Particle_SetTimerA6(arg0, sp22 * 4);
    Particle_DisableFlag4(arg0);
    Particle_IncrementState(arg0);
}

void func_84336A58(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            func_843369AC(arg0);
            break;

        case 2:
            if (Particle_DecrementTimerA6ToZeroWithCallback(arg0) != 0) {
                Particle_EnableFlag2(arg0);
                Particle_EnableFlag4(arg0);
                Particle_SetTimerA6(arg0, 8);
            }
            break;

        case 3:
            Particle_ApproachPrimG(arg0, 0, 0x10);
            Particle_ApproachEnvR(arg0, 0, 0x10);
            if ((Particle_DecrementTimerA6ToZero(arg0) != 0) && (Particle_ApproachPrimAlpha(arg0, 0x20, 0x18) != 0)) {
                Particle_IncrementState(arg0);
            }
            break;

        case 4:
            Particle_ClearActiveFlag(arg0);
            break;
    }

    if (Particle_HasFlag4(arg0) != 0) {
        Particle_ApproachScaleFactor1(arg0, 1.0f, 0.025f);
        Particle_AnimLoopForward(arg0, 0, 7, 1, 2, 0);
    }
}

void func_84336B8C(void) {
    ParticleDef_CreateBC20CDAlt(0, 0, 0x40, 0xA, 0xC8);
    ParticleDef_CreateQuick(1, func_84334808, &gParticleEffectData[0x34], 0, 1, 0x10, gParticleTexture_Default, 0, 0);
    ParticleDef_CreateQuick(2, func_84334994, &gParticleEffectData[0x3D], 0, 3, 0x11, gParticleTexture_Default, 0, 0);
    ParticleDef_CreateQuick(4, func_843346BC, &gParticleEffectData[0x46], 0, 1, 0x11, gParticleTexture_Default, 0, 0);
}

void func_84336C80(void) {
    ParticleDef_CreateBC20CDAlt(2, 0, 0x40, 0xA, 0xC8);
    ParticleDef_Create31EAC(0, 0xC, 0xFF, 0, 0x30);
    ParticleDef_CreateQuick(4, func_84335668, &gParticleEffectData[0x46], 0, 6, 0x10, 9, 0, 0);
    ParticleDef_CreateQuick(8, func_84335668, &gParticleEffectData[0x46], 0, 6, 0x10, 9, 0, 0);
    ParticleDef_CreateFull(0, 2, 2, func_84335A84, &gParticleEffectData[0x3D], 0, 4, 0x10, 9, 0, 0);
    ParticleDef_CreateFull(0, 2, 2, func_84335848, &gParticleEffectData[0x47], 0, 4, 0x10, 9, 0, 0);
}

void func_84336DD8(void) {
    ParticleDef_CreateBC20CDAlt(2, 0, 0x40, 0xA, 0xC8);
    ParticleDef_Create31EAC(2, 0xB, 0xC8, 0, 0x10);
    ParticleDef_CreateQuick(0, func_84335EF8, &gParticleEffectData[0x46], 0, 3, 0x10, 9, 0, 0);
    ParticleDef_CreateQuick(0xA, func_84335D10, &gParticleEffectData[0x46], 0, 8, 0x11, 9, 0, 0);
    ParticleDef_CreateFull(0xC, 2, 2, func_84335A84, &gParticleEffectData[0x3D], 0, 4, 0x11, 9, 0, 0);
}

void func_84336EE8(void) {
    ParticleDef_CreateNullType17(0x64, 1);
    ParticleDef_CreateDefault(0, 8, 6);
    ParticleDef_CreateFull(0, 2, 0x3C, func_843332B4, &gParticleEffectData[0x4F], 0, 1, 0x11, gParticleTexture_Default, 0, 0);
    ParticleDef_CreateFull(0, 4, 0x1E, Particle_SmokePuffHandler, &gParticleEffectData[0x3D], 0, 1, 0x11, gParticleTexture_Default, 0, 0);
    ParticleDef_CreateFull(0, 4, 0x1E, func_84333BA8, &gParticleEffectData[0x4F], 0, 1, 0x11, gParticleTexture_Default, 0, 0);
}

void func_84337000(void) {
    ParticleDef_Create32604(0xA, 0xB, 0x10, 8, 0xC8, 0x10);
    ParticleDef_CreateFull(0, 2, 0x14, func_84336320, &gParticleEffectData[0x4E], 0, 1, 0x11, 9, 0, 0);
    ParticleDef_CreateFull(0, 2, 2, func_84336340, &gParticleEffectData[0x4E], 0, 0xC, 0x11, 9, 0, 0);
    ParticleDef_CreateFull(0xE, 8, 5, func_84336520, &gParticleEffectData[0x3D], 0, 2, 0x11, 9, 0, 0);
    ParticleDef_Create31EAC(0x3C, 0x10, 0xC8, 0, 8);
    ParticleDef_CreateFull(0x3A, 2, 2, ParticleEffect_BasicSetupHandler, &gParticleEffectData[0x3D], 0, 1, 9, 0, 0x33, 0);
    ParticleDef_CreateFull(0x3C, 2, 2, ParticleEffect_BasicSetupHandler, &gParticleEffectData[0x3D], 0, 1, 9, 0, 0x33, 0);
}

void func_843371C0(void) {
    ParticleDef_CreateDefault(0, 8, 6);
    ParticleDef_CreateFull(0, 2, 0x3C, func_843332B4, &gParticleEffectData[0x4F], 0, 1, 0x11, gParticleTexture_Default, 1, 0);
    ParticleDef_CreateFull(0, 4, 0x1E, Particle_SmokePuffHandler, &gParticleEffectData[0x3D], 0, 1, 0x11, gParticleTexture_Default, 1, 0);
    ParticleDef_CreateFull(0, 4, 0x1E, func_84333BA8, &gParticleEffectData[0x4F], 0, 1, 0x11, gParticleTexture_Default, 1, 0);
}

void func_843372D8(void) {
    ParticleDef_Create32604(0xA, 0x35, 0x2E, 8, 0xC8, 0x10);
    ParticleDef_CreateFull(0, 2, 0x14, func_84336320, &gParticleEffectData[0x4E], 0, 1, 0x11, 9, 1, 0);
    ParticleDef_CreateFull(0, 2, 2, func_84336340, &gParticleEffectData[0x4E], 0, 0xC, 0x11, 9, 1, 0);
    ParticleDef_CreateFull(0xE, 8, 5, func_84336520, &gParticleEffectData[0x3D], 0, 2, 0x11, 9, 1, 0);
    ParticleDef_Create31EAC(0x3C, 0x2E, 0xC8, 0, 8);
    ParticleDef_CreateFull(0x3A, 2, 2, ParticleEffect_BasicSetupHandler, &gParticleEffectData[0x3D], 0, 1, 9, 0, 0x18, 0);
    ParticleDef_CreateFull(0x3C, 2, 2, ParticleEffect_BasicSetupHandler, &gParticleEffectData[0x3D], 0, 1, 9, 0, 0x18, 0);
}

void func_843374A4(void) {
    ParticleDef_CreateDefault(0, 8, 6);
    ParticleDef_CreateFull(0, 2, 0x50, func_843332B4, &gParticleEffectData[0x4F], 0, 1, 0x11, gParticleTexture_Default, 0, 0);
    ParticleDef_CreateFull(0, 4, 0x28, Particle_SmokePuffHandler, &gParticleEffectData[0x3D], 0, 1, 0x11, gParticleTexture_Default, 0, 0);
    ParticleDef_CreateFull(0, 4, 0x28, func_84333BA8, &gParticleEffectData[0x4F], 0, 1, 0x11, gParticleTexture_Default, 0, 0);
}

void func_843375B0(void) {
    ParticleDef_CreateQuick(0, func_84334350, &gParticleEffectData[2], 0, 0x12, 0xE, 0, 0, 0);
    ParticleDef_CreateQuick(8, ParticleEffect_FireUpdate, &gParticleEffectData[0x4F], 0, 0x20, 7, 0, 0, 0);
    ParticleDef_Create32604(8, 0xB, 0x10, 8, 0xC8, 0x10);
}

void func_8433765C(void) {
}

void func_84337664(void) {
}

void func_8433766C(void) {
    ParticleDef_CreateQuick(0, func_84333E28, &gParticleEffectData[4], 0, 1, 0x10, 9, 0x14, 0);
    ParticleDef_CreateBC20CDAlt(0, 0, 0x40, 0xA, 0xC8);
    ParticleDef_Create321BC(4, 0xA, 0x19, 0x20, 0xFF);
    ParticleDef_CreateQuick(0, func_84334D7C, &gParticleEffectData[0x46], 0, 3, 0x10, 9, 0x17, 2);
    ParticleDef_CreateQuick(6, func_84334D7C, &gParticleEffectData[0x46], 0, 3, 0x10, 9, 0x2C, 1);
    ParticleDef_CreateQuick(0xC, func_84334D7C, &gParticleEffectData[0x46], 0, 3, 0x10, 9, 0x1A, 1);
    ParticleDef_CreateQuick(0x12, func_84334D7C, &gParticleEffectData[0x46], 0, 2, 0x10, 9, 0x1A, 0);
    ParticleDef_CreateQuick(0x14, func_843351C8, &gParticleEffectData[0x48], 0, 3, 0x11, 9, 0x1A, 0);
    ParticleDef_CreateFull(0x14, 2, 2, func_843353C4, &gParticleEffectData[0x3D], 0, 6, 0x11, 9, 0, 0);
    ParticleDef_CreateQuick(0x18, func_84335D10, &gParticleEffectData[0x46], 0, 8, 0x11, 9, 0, 0);
}

void func_843378CC(void) {
}

void func_843378D4(void) {
    ParticleDef_CreateDefault(0, 0xFF, 0);
    ParticleDef_Create32604(0xA, 0xB, 0x10, 8, 0xC8, 0x10);
    ParticleDef_CreateFull(4, 8, 0x14, func_84336520, &gParticleEffectData[0x3D], 0, 2, 0xE, 0, 0, 0);
    ParticleDef_CreateFull(4, 8, 0x14, func_84336A58, &gParticleEffectData[0x4F], 0, 2, 9, 0, 0, 0);
    ParticleDef_CreateFull(0, 6, 0x28, func_84336830, &gParticleEffectData[0x4F], 0, 1, 9, 0, 0, 0);
    ParticleDef_CreateFull(0, 4, 0x3C, func_84336830, &gParticleEffectData[0x4F], 0, 1, 9, 0, 1, 0);
    ParticleDef_CreateFull(0, 4, 0x3C, func_84336830, &gParticleEffectData[0x4F], 0, 1, 9, 0, 2, 0);
    ParticleDef_CreateFull(0, 3, 0x50, func_84336830, &gParticleEffectData[0x4F], 0, 1, 9, 0, 3, 0);
    ParticleDef_CreateFull(0, 3, 0x50, func_84336830, &gParticleEffectData[0x4F], 0, 1, 9, 0, 4, 0);
}
