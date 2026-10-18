#include "fragment62.h"
#include "src/17300.h"
#include "src/12D80.h"
#include "src/6A40.h"
#include "src/F420.h"
#include "src/math_util.h"

void Particle_SetDirectionOffsets(ParticleEffectInstance* arg0) {
    s16 sp26 = Particle_GetShortAC(arg0);
    s16 sp24 = Particle_GetShortCF(arg0);

    switch (Particle_GetShortCE(arg0)) {
        case 0:
            func_8140A578(arg0, 0x4000);
            break;

        case 1:
            func_8140A578(arg0, -0x3000);
            func_8140A594(arg0, 0x4000);
            func_8140A5B0(arg0, 0x2000);
            break;

        case 2:
            func_8140A578(arg0, 0x2000);
            func_8140A594(arg0, 0x2000);
            func_8140A5B0(arg0, 0x2000);
            break;

        case 3:
            func_8140A578(arg0, -0x8000);
            func_8140A594(arg0, 0x2000);
            func_8140A5B0(arg0, 0x6000);
            break;

        case 4:
            func_8140A578(arg0, -0x4000);
            func_8140A594(arg0, 0x4000);
            func_8140A5B0(arg0, 0x4000);
            break;
    }

    Particle_AddVelocityYScaled(arg0, 10.0f);
    Particle_AddComplexDirection(arg0, (sp26 - 1) * 10.0f);
    Particle_SetScaleFactor1(arg0, 1.0f);
    SetPrimEnvColorFromPair(arg0, sp24);
    Particle_IncrementState(arg0);
}

void Particle_HandleState(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            Particle_SetDirectionOffsets(arg0);
            break;

        case 2:
            Particle_AnimLoopForwardComplete(arg0, 0, 7, 1, 1, 0);
            break;

        case 3:
            Particle_ApproachPrimAlphaWithCallback(arg0, 0, 0x40);
            break;

        case 4:
            Particle_ClearActiveFlag(arg0);
            break;
    }
    Particle_ApproachScaleFactor1(arg0, 3.5f, 0.25f);
}

void Particle_SetupSpecialOffsets(ParticleEffectInstance* arg0) {
    s16 sp26 = Particle_GetShortAC(arg0);

    Particle_GetShortCF(arg0);

    switch (sp26) {
        case 0:
            func_8140A578(arg0, 0x5800);
            func_8140A594(arg0, 0x5800);
            func_8140A5B0(arg0, -0x6000);
            break;

        case 1:
            func_8140A578(arg0, 0x6000);
            func_8140A594(arg0, 0);
            func_8140A5B0(arg0, 0x5800);
            break;

        case 2:
            func_8140A578(arg0, 0x2000);
            func_8140A594(arg0, 0x2000);
            func_8140A5B0(arg0, 0x2000);
            break;

        case 3:
            func_8140A578(arg0, 0x6000);
            break;

        case 4:
            func_8140A578(arg0, 0);
            func_8140A594(arg0, 0);
            func_8140A5B0(arg0, 0);
            break;

        case 5:
            func_8140A578(arg0, 0x6000);
            func_8140A594(arg0, 0x2800);
            func_8140A5B0(arg0, 0x5800);
            break;
    }

    Particle_AddVelocityYScaled(arg0, 10.0f);
    Particle_SetScaleFactor1(arg0, 1.0f);
    SetPrimEnvColorFromPair(arg0, 0xC);
    Particle_SetTimerA6(arg0, sp26 * 3);
    Particle_DisableFlag4(arg0);
    Particle_IncrementState(arg0);
}

void Particle_HandleState_Special(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            Particle_SetupSpecialOffsets(arg0);
            break;

        case 2:
            if (Particle_DecrementTimerA6ToZeroWithCallback(arg0) != 0) {
                Particle_EnableFlag4(arg0);
            }
            break;

        case 3:
            Particle_AnimLoopForwardComplete(arg0, 0, 7, 1, 1, 0);
            Particle_ApproachScaleFactor1(arg0, 3.5f, 0.25f);
            break;

        case 4:
            Particle_ApproachPrimAlphaWithCallback(arg0, 0, 0x40);
            Particle_ApproachScaleFactor1(arg0, 3.5f, 0.25f);
            break;

        case 5:
            Particle_ClearActiveFlag(arg0);
            break;
    }
}

void func_8434F888(ParticleEffectInstance* arg0) {
    s16 sp26 = Particle_GetShortAC(arg0);
    s16 sp24 = Particle_GetShortCF(arg0);

    switch (sp26) {
        case 0:
            func_8140A578(arg0, 0x5800);
            func_8140A594(arg0, 0x5800);
            func_8140A5B0(arg0, -0x6000);
            break;

        case 1:
            func_8140A578(arg0, 0x6000);
            func_8140A594(arg0, 0);
            func_8140A5B0(arg0, 0x5800);
            break;

        case 2:
            func_8140A578(arg0, 0x2000);
            func_8140A594(arg0, 0x2000);
            func_8140A5B0(arg0, 0x2000);
            break;

        case 3:
            func_8140A578(arg0, 0x6000);
            break;

        case 4:
            func_8140A578(arg0, 0);
            func_8140A594(arg0, 0);
            func_8140A5B0(arg0, 0);
            break;

        case 5:
            func_8140A578(arg0, 0x6000);
            func_8140A594(arg0, 0x2800);
            func_8140A5B0(arg0, 0x5800);
            break;
    }

    switch (sp24) {
        case 0:
            Particle_SetRandomVelocityXSymmetric(arg0, 0xA, 3);
            Particle_SetRandomVelocityYOffset(arg0, 0xF, 0xA);
            Particle_SetRandomVelocityZSymmetric(arg0, 0xF, 3);
            SetPrimEnvColorFromPair(arg0, 0xD);
            break;

        case 1:
            Particle_SetRandomVelocityXSymmetric(arg0, 0xA, 5);
            Particle_SetRandomVelocityYOffset(arg0, 0x14, 5);
            Particle_SetRandomVelocityZSymmetric(arg0, 0xA, 5);
            SetPrimEnvColorFromPair(arg0, 0xE);
            break;
    }

    Particle_SetScaleFactor1(arg0, 1.0f);
    Particle_SetTimerA6(arg0, sp26 * 2);
    Particle_DisableFlag4(arg0);
    Particle_IncrementState(arg0);
}

void Particle_HandleState_SpecialColor(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            func_8434F888(arg0);
            break;

        case 2:
            if (Particle_DecrementTimerA6ToZeroWithCallback(arg0) != 0) {
                Particle_EnableFlag4(arg0);
            }
            break;

        case 3:
            Particle_AnimLoopForwardComplete(arg0, 0, 7, 2, 1, 0);
            break;

        case 4:
            Particle_ClearActiveFlag(arg0);
            break;
    }
}

void func_8434FB3C(ParticleEffectInstance* arg0) {
    s16 sp26 = func_843081BC(gParticleEffectData_42);

    Particle_SetScaleFactor1(arg0, 1.0f);
    SetPrimEnvColorFromPair(arg0, Particle_GetShortCF(arg0));

    if (sp26 == 0x42) {
        Particle_SetVelocityScaledXYZ(arg0, 320.0f, 0.0f, 0.0f);
        func_8140A5B0(arg0, -0x2800);
    } else {
        func_8140A5B0(arg0, 0x2500);
    }
    Particle_IncrementState(arg0);
}

void Particle_HandleCollisionResponse(ParticleEffectInstance* arg0) {
    s16 sp26 = Particle_GetShortCE(arg0);

    switch (arg0->unk_B2) {
        case 1:
            func_8434FB3C(arg0);
            break;

        case 2:
            Particle_ProcessTimer80(arg0, 0x14);
            break;

        case 3:
            Particle_ResetState(arg0);
            break;
    }

    Particle_ApproachScaleFactor1(arg0, 6.2f, 1.0f);

    if (sp26 == 0) {
        Particle_ApproachPrimG(arg0, 0, 0x18);
        Particle_ApproachPrimB(arg0, 0, 0x18);
        Particle_ApproachEnvG(arg0, 0, 0x18);
        Particle_ApproachEnvB(arg0, 0, 0x18);
    }
}

void func_8434FCC4(ParticleEffectInstance* arg0) {
    s16 sp26 = func_843081BC(gParticleEffectData_42);

    Particle_SetScaleFactor1(arg0, 1.0f);

    if (sp26 == 0x42) {
        func_8140A5B0(arg0, 0x2500);
    } else {
        Particle_SetVelocityScaledXYZ(arg0, 320.0f, 0.0f, 0.0f);
        func_8140A5B0(arg0, -0x2800);
    }

    SetPrimEnvColorFromPair(arg0, Particle_GetShortCF(arg0));
    Particle_IncrementState(arg0);
}

void Particle_HandleCollisionResponse_ExplosionAlt(ParticleEffectInstance* arg0) {
    s16 sp26 = Particle_GetShortCE(arg0);

    switch (arg0->unk_B2) {
        case 1:
            func_8434FCC4(arg0);
            break;

        case 2:
            Particle_ProcessTimer80(arg0, 0x14);
            break;

        case 3:
            Particle_ClearActiveFlag(arg0);
            break;
    }

    Particle_ApproachScaleFactor1(arg0, 6.0f, 1.0f);

    if (sp26 == 0) {
        Particle_ApproachPrimG(arg0, 0, 0x18);
        Particle_ApproachPrimB(arg0, 0, 0x18);
        Particle_ApproachEnvG(arg0, 0, 0x18);
        Particle_ApproachEnvB(arg0, 0, 0x18);
    }
    Particle_ApproachPrimAlpha(arg0, 0, 0x10);
}

void func_8434FE58(ParticleEffectInstance* arg0) {
    s16 sp26 = Particle_GetShortCE(arg0);
    s16 sp24 = Particle_GetShortCF(arg0);
    s16 sp22 = func_843081BC(gParticleEffectData_42);

    Particle_SetScaleFactor1(arg0, 1.0f);

    if (sp22 == 0x42) {
        func_8140A578(arg0, -0x2000);
        func_8140A594(arg0, 0x4000);
    } else {
        func_8140A578(arg0, 0x2000);
        func_8140A594(arg0, 0x4000);
    }

    switch (sp26) {
        case 0:
            Particle_AddVelocityYScaled(arg0, -10.0f);
            break;

        case 2:
            Particle_AddVelocityYScaled(arg0, 10.0f);
            break;
    }

    SetPrimEnvColorFromPair(arg0, sp24);
    Particle_IncrementState(arg0);
}

void Particle_HandleState_Directional(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            func_8434FE58(arg0);
            break;

        case 2:
            Particle_ProcessTimer80(arg0, 8);
            break;

        case 3:
            Particle_ApproachPrimAlphaWithCallback(arg0, 0, 0x20);
            break;

        case 4:
            Particle_ResetState(arg0);
            break;
    }

    Particle_AnimLoopForward(arg0, 0, 7, 1, 2, 0);
    Particle_ApproachScaleFactor1(arg0, 5.0f, 0.4f);
}

void Particle_HandleState_Directional_Scale(ParticleEffectInstance* arg0) {
    s16 sp26 = Particle_GetShortCE(arg0);
    s16 sp24 = Particle_GetShortCF(arg0);
    s16 sp22 = func_843081BC(gParticleEffectData_42);

    Particle_SetScaleFactor1(arg0, 1.0f);

    if (sp22 == 0x42) {
        func_8140A578(arg0, -0x2000);
        func_8140A594(arg0, 0x4000);
    } else {
        func_8140A578(arg0, 0x2000);
        func_8140A594(arg0, 0x4000);
    }

    switch (sp26) {
        case 0:
            Particle_AddVelocityYScaled(arg0, -10.0f);
            break;

        case 2:
            Particle_AddVelocityYScaled(arg0, 10.0f);
            break;
    }

    SetPrimEnvColorFromPair(arg0, sp24);
    Particle_SetPrimAlpha(arg0, 0x80);
    Particle_IncrementState(arg0);
}

void Particle_HandleState_Directional_ScaleAlt(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            Particle_HandleState_Directional_Scale(arg0);
            break;

        case 2:
            Particle_ProcessTimer80(arg0, 8);
            break;

        case 3:
            Particle_ApproachPrimAlphaWithCallback(arg0, 0, 0x10);
            break;

        case 4:
            Particle_ResetState(arg0);
            break;
    }

    Particle_AnimLoopForward(arg0, 0, 7, 1, 2, 0);
    Particle_ApproachScaleFactor1(arg0, 5.0f, 0.4f);
}

void func_843501CC(ParticleEffectInstance* arg0) {
    s16 sp26 = Particle_GetShortAC(arg0);
    s16 sp24 = Particle_GetShortCF(arg0);

    Particle_SetScaleFactor1(arg0, 1.0f);
    Particle_SetSpeed(arg0, 0.4f);
    SetPrimEnvColorFromPair(arg0, sp24);
    Particle_SetPrimAlpha(arg0, 0x64);
    Particle_SetTimerA6(arg0, sp26 * 4);
    Particle_DisableFlag4(arg0);
    Particle_IncrementState(arg0);
}

void func_84350260(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            func_843501CC(arg0);
            break;

        case 2:
            if (Particle_ProcessTimer80(arg0, arg0->unk_A6) != 0) {
                Particle_EnableFlag4(arg0);
            }
            break;

        case 3:
            Particle_AnimLoopForwardComplete(arg0, 0, 7, 1, 2, 0);
            Particle_ApproachPrimAlpha(arg0, 0x64, 6);
            Particle_SetTargetVelocityBackward(arg0);
            break;

        case 4:
            Particle_ClearActiveFlag(arg0);
            break;
    }
}

void func_84350330(ParticleEffectInstance* arg0) {
    s16 sp26 = Particle_GetShortAC(arg0);
    s16 sp24 = Particle_GetShortCF(arg0);

    Particle_SetScaleFactor1(arg0, 0.25f);
    arg0->unk_5C.y = (MathUtil_Random_ZeroOne() * 0.5f) + 0.25f;
    func_8140A594(arg0, 0x1800 - ((0x3000 / Particle_GetShortAA(arg0)) * sp26));
    Particle_SetSpeed(arg0, (2.0f * MathUtil_Random_ZeroOne()) + 3.0f);
    SetPrimEnvColorFromPair(arg0, sp24);
    Particle_SetPrimAlpha(arg0, 0xB4);
    Particle_IncrementState(arg0);
}

void func_8435043C(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            func_84350330(arg0);
            break;

        case 2:
            Particle_AnimLoopForwardComplete(arg0, 0, 7, 1, 2, 0);
            Particle_ApproachScaleFactor1(arg0, 0.75f, 0.025f);
            Particle_ApproachSpeedScaled(arg0, 0.5f, 0.25f);
            Particle_AddScaledVelocityY(arg0, arg0->unk_5C.y);
            Particle_ApplyB278AndCopyXZAlt(arg0);
            break;

        case 3:
            Particle_ApproachPrimAlphaWithCallback(arg0, 0, 0x20);
            break;

        case 4:
            Particle_ClearActiveFlag(arg0);
            break;
    }
}

void func_84350520(ParticleEffectInstance* arg0) {
    s16 sp26 = Particle_GetShortAC(arg0);
    s16 sp24 = Particle_GetShortCF(arg0);

    Particle_SetScaleFactor1(arg0, 0.5f);
    arg0->unk_5C.y = (MathUtil_Random_ZeroOne() * 0.5f) + 0.25f;
    func_8140A594(arg0, 0x1800 - ((0x3000 / Particle_GetShortAA(arg0)) * sp26));
    Particle_SetSpeed(arg0, (MathUtil_Random_ZeroOne() * 2.5f) + 3.0f);
    SetPrimEnvColorFromPair(arg0, sp24);
    Particle_SetPrimAlpha(arg0, 0xB4);
    Particle_IncrementState(arg0);
}

void func_84350634(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            func_84350520(arg0);
            break;

        case 2:
            Particle_AnimLoopForwardComplete(arg0, 0, 7, 1, 3, 0);
            Particle_ApproachScaleFactor1(arg0, 1.0f, 0.05f);
            Particle_ApproachSpeedScaled(arg0, 0.5f, 0.25f);
            Particle_AddScaledVelocityY(arg0, arg0->unk_5C.y);
            break;

        case 3:
            if (Particle_ApproachPrimAlpha(arg0, 0, 0x20) != 0) {
                Particle_IncrementState(arg0);
            }
            break;

        case 4:
            Particle_ClearActiveFlag(arg0);
            break;
    }
    Particle_ApplyB278AndCopyXZAlt(arg0);
}

void func_84350728(ParticleEffectInstance* arg0) {
    UNUSED s16 pad;
    s16 sp24 = Particle_GetShortAC(arg0);

    Particle_SetScaleFactor1(arg0, 0.25f);
    arg0->unk_5C.y = (MathUtil_Random_ZeroOne() * 0.5f) + 0.4f;
    func_8140A594(arg0, 0x800 - ((0x1000 / Particle_GetShortAA(arg0)) * sp24));
    Particle_SetSpeed(arg0, (2.0f * MathUtil_Random_ZeroOne()) + 5.0f);
    SetPrimEnvColorFromPair(arg0, 0x32);
    Particle_SetPrimAlpha(arg0, 0xFF);
    Particle_IncrementState(arg0);
}

void func_84350828(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            func_84350728(arg0);
            break;

        case 2:
            Particle_AnimLoopForwardComplete(arg0, 0, 7, 1, 2, 0);
            Particle_ApproachPrimAlpha(arg0, 0x64, 9);
            Particle_ApproachScaleFactor1(arg0, 0.4f, 0.025f);
            Particle_AddScaledVelocityY(arg0, arg0->unk_5C.y);
            Particle_ApplyB278AndCopyXZAlt(arg0);
            break;

        case 3:
            Particle_ClearActiveFlag(arg0);
            break;
    }
}

void func_843508F0(ParticleEffectInstance* arg0) {
    s16 sp26 = Particle_GetShortAC(arg0);

    Particle_SetScaleFactor1(arg0, 0.4f);
    Particle_SetRandomVelocityXYZ(arg0, 0, 0, 0xA);
    arg0->unk_5C.y = (MathUtil_Random_ZeroOne() * 0.5f) + 0.25f;
    func_8140A594(arg0, 0x2000 - ((0x4000 / Particle_GetShortAA(arg0)) * sp26));
    Particle_SetSpeed(arg0, MathUtil_Random_ZeroOne() + 1.0f);
    SetPrimEnvColorFromPair(arg0, 0xA);
    Particle_SetPrimAlpha(arg0, 0x64);
    Particle_IncrementState(arg0);
}

void func_84350A04(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            func_843508F0(arg0);
            break;

        case 2:
            Particle_AnimLoopForwardComplete(arg0, 0, 7, 1, 2, 0);
            Particle_ApproachScaleFactor1(arg0, 0.75f, 0.025f);
            Particle_ApproachSpeedScaled(arg0, 0.5f, 0.2f);
            Particle_AddScaledVelocityY(arg0, arg0->unk_5C.y);
            Particle_ApplyB278AndCopyXZAlt(arg0);
            break;

        case 3:
            if (Particle_ApproachPrimAlpha(arg0, 0, 0x20) != 0) {
                Particle_IncrementState(arg0);
            }
            break;

        case 4:
            Particle_ClearActiveFlag(arg0);
            break;
    }
}

void func_84350AFC(ParticleEffectInstance* arg0) {
    s16 sp26 = Particle_GetShortAC(arg0);

    Particle_SetScaleFactor1(arg0, 0.3f);
    Particle_SetRandomVelocityXYZ(arg0, 0xA, 5, 0xA);
    Particle_AddVelocityYScaled(arg0, 15.0f);
    Particle_SetSpeed(arg0, (RandomMod(0xA) * 0.1f) + 1.5f);
    Particle_SetTimerA6(arg0, sp26 * 2);
    SetPrimEnvColorFromPair(arg0, 0x32);
    Particle_SetPrimAlpha(arg0, 0xFF);
    Particle_DisableFlag4(arg0);
    Particle_IncrementState(arg0);
}

void func_84350BE4(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            func_84350AFC(arg0);
            break;

        case 2:
            if (Particle_ProcessTimer80(arg0, arg0->unk_A6) != 0) {
                Particle_EnableFlag4(arg0);
            }
            break;

        case 3:
            Particle_ApproachScaleFactor1(arg0, 0.5f, 0.02f);
            Particle_AnimLoopForward(arg0, 0, 7, 1, 2, 0);
            Particle_ApproachPrimAlpha(arg0, 0x64, 6);
            if (Particle_FallAndCheckGround(arg0) != 0) {
                Particle_IncrementState(arg0);
            }
            break;

        case 4:
            Particle_ClearActiveFlag(arg0);
            break;
    }
}

void func_84350CD8(ParticleEffectInstance* arg0) {
    s16 sp26 = Particle_GetShortAC(arg0);

    Particle_SetScaleFactor1(arg0, 0.25f);
    func_8140A594(arg0, sp26 << 0xC);
    Particle_SetSpeed(arg0, (2.0f * MathUtil_Random_ZeroOne()) + 6.0f);
    Particle_SetAccelerationY(arg0, (MathUtil_Random_ZeroOne() * 3.0f) + 1.0f);
    SetPrimEnvColorFromPair(arg0, 0xA);
    Particle_SetPrimAlpha(arg0, 0x64);
    Particle_SetTimerA6(arg0, 7);
    Particle_IncrementState(arg0);
}

void func_84350DAC(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            func_84350CD8(arg0);
            break;

        case 2:
            Particle_AnimLoopForwardComplete(arg0, 0, 7, 1, 2, 0);
            Particle_ApproachScaleFactor1(arg0, 0.8f, 0.1f);
            Particle_ApproachSpeedScaled(arg0, 1.0, 1.0f);
            if (Particle_DecrementTimerA6ToZero(arg0) != 0) {
                func_8140B180(arg0, 0.5f, 0.4f);
                Particle_AddVelocityYFromTarget(arg0);
            }
            break;

        case 3:
            Particle_AddVelocityYFromTarget(arg0);
            Particle_ApproachPrimAlphaWithCallback(arg0, 0, 0x20);
            break;

        case 4:
            Particle_ClearActiveFlag(arg0);
            break;
    }

    if (Particle_IsActive(arg0) != 0) {
        Particle_ApplyB278AndCopyXZAlt(arg0);
    }
}

void func_84350EC8(ParticleEffectInstance* arg0) {
    s16 sp26 = Particle_GetShortAC(arg0);

    switch (Particle_GetShortCF(arg0)) {
        case 0:
            Particle_SetScaleFactor1(arg0, 0.75f);
            Particle_SetRandomVelocityXYZ(arg0, 0xF, 0xF, 0xF);
            Particle_AddVelocityYScaled(arg0, 15.0f);
            Particle_SetSpeed(arg0, 1.0f);
            break;

        case 1:
            Particle_SetScaleFactor1(arg0, 0.5f);
            Particle_SetRandomVelocityXYZ(arg0, 3, 3, 3);
            Particle_SetSpeed(arg0, 0.4f);
            break;
    }

    Particle_SetTimerA6(arg0, sp26 * 4);
    SetPrimEnvColorFromPair(arg0, 0x13);
    Particle_SetPrimAlpha(arg0, 0xC8);
    Particle_DisableFlag4(arg0);
    Particle_IncrementState(arg0);
}

void func_84350FC0(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            func_84350EC8(arg0);
            break;

        case 2:
            if (Particle_ProcessTimer80(arg0, arg0->unk_A6) != 0) {
                Particle_EnableFlag4(arg0);
            }
            break;

        case 3:
            Particle_AnimLoopForwardComplete(arg0, 0, 7, 1, 2, 0);
            Particle_ApproachPrimAlpha(arg0, 0x64, 6);
            Particle_FallAndCheckGround(arg0);
            break;

        case 4:
            Particle_ClearActiveFlag(arg0);
            break;
    }
}

void func_84351090(ParticleEffectInstance* arg0) {
    s16 sp26 = Particle_GetShortAC(arg0);

    Particle_SetRandomRotatedVelocityXY(arg0, 0xF, 0xF);
    Particle_SetScaleFactor1(arg0, 1.0f);
    Particle_SetSpeed(arg0, 0.2f);
    Particle_SetPrimColor(arg0, 0xFF, 0xFF, 0xFF);
    Particle_SetEnvColor(arg0, 0xFF, 0x64, 0);
    Particle_SetPrimAlpha(arg0, 0xFF);
    Particle_SetTimerA6(arg0, sp26 * 4);
    Particle_DisableFlag4(arg0);
    Particle_IncrementState(arg0);
}

void func_84351144(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            func_84351090(arg0);
            break;

        case 2:
            if (Particle_ProcessTimer80(arg0, arg0->unk_A6) != 0) {
                Particle_EnableFlag4(arg0);
            }
            break;

        case 3:
            Particle_AnimLoopForwardComplete(arg0, 0, 7, 1, 2, 0);
            Particle_ApproachPrimR(arg0, 0x64, 9);
            Particle_ApproachEnvR(arg0, 0, 0x10);
            Particle_ApproachEnvG(arg0, 0x32, 3);
            Particle_ApproachEnvB(arg0, 0xFF, 0x10);
            if (Particle_StartTimer80(arg0, 8) != 0) {
                Particle_ApproachPrimAlpha(arg0, 0, 0x20);
            }
            Particle_SetTargetVelocityBackward(arg0);
            break;

        case 4:
            Particle_ResetState(arg0);
            break;
    }
}

void func_84351264(ParticleEffectInstance* arg0) {
    Particle_SetScaleFactor1(arg0, 0.1f);
    SetPrimEnvColorFromPair(arg0, 0x14);
    Particle_SetPrimAlpha(arg0, 0xFF);
    Particle_IncrementState(arg0);
}

void func_843512AC(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            func_84351264(arg0);
            break;

        case 2:
            Particle_ApproachScaleFactor1(arg0, 0.75f, 0.08125f);
            Particle_ApproachPrimAlphaWithCallback(arg0, 0, 0x20);
            break;

        case 3:
            Particle_ResetState(arg0);
            break;
    }
}

void func_84351330(ParticleEffectInstance* arg0) {
    Vec3s sp28;

    Particle_GetShortAC(arg0);
    Particle_SetScaleFactor1(arg0, 0.1f);
    sp28.x = MathUtil_Random16();
    sp28.y = MathUtil_Random16();
    sp28.z = 0;
    Particle_SetRotationFromVec3s(arg0, sp28);
    SetPrimEnvColorFromPair(arg0, 0x15);
    Particle_SetPrimAlpha(arg0, 0xFF);
    Particle_SetTimerA6(arg0, RandomMod(5) + 8);
    Particle_SetSpeed(arg0, 5.0f);
    Particle_IncrementState(arg0);
}

void func_843513F4(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            func_84351330(arg0);
            break;

        case 2:
            Particle_ApproachSpeedScaled(arg0, 2.0f, 0.5f);
            if ((Particle_DecrementTimerA6ToZero(arg0) != 0) && (Particle_ApproachPrimAlpha(arg0, 0, 0x40) != 0)) {
                Particle_IncrementState(arg0);
            }
            break;

        case 3:
            Particle_ClearActiveFlag(arg0);
            break;
    }

    if (Particle_IsActive(arg0) != 0) {
        Particle_ApplyB2B4AndAddAll(arg0);
    }
}

void func_843514B4(ParticleEffectInstance* arg0) {
    Vec3s sp28;
    s16 sp26 = Particle_GetShortCF(arg0);

    Particle_GetShortAC(arg0);

    sp28.x = RandomRangeSigned(0x2000);
    sp28.y = func_81400B28(0x2000, 0x8000);
    sp28.z = 0;
    Particle_AddRotationDeltaVec(arg0, sp28);

    switch (sp26) {
        case 0:
            Particle_SetScaleFactor1(arg0, 0.2f);
            SetPrimEnvColorFromPair(arg0, 0x15);
            break;

        case 1:
            Particle_SetScaleFactor1(arg0, 0.2f);
            SetPrimEnvColorFromPair(arg0, 0x1B);
            break;
    }

    Particle_SetPrimAlpha(arg0, 0xFF);
    Particle_SetTimerA6(arg0, RandomMod(5) + 8);
    Particle_SetSpeed(arg0, 6.0f);
    Particle_IncrementState(arg0);
}

void func_843515C8(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            func_843514B4(arg0);
            break;

        case 2:
            Particle_ApproachScaleFactor1(arg0, 0.1f, 0.01f);
            Particle_ApproachSpeedScaled(arg0, 3.0f, 0.75f);
            if ((Particle_DecrementTimerA6ToZero(arg0) != 0) && (Particle_ApproachPrimAlpha(arg0, 0, 0x40) != 0)) {
                Particle_IncrementState(arg0);
            }
            break;

        case 3:
            Particle_ClearActiveFlag(arg0);
            break;
    }

    if (Particle_IsActive(arg0) != 0) {
        Particle_ApplyB2B4AndAddAll(arg0);
    }
}

void func_843516A0(ParticleEffectInstance* arg0) {
    Vec3s sp28;
    s16 sp26 = Particle_GetShortCF(arg0);

    Particle_GetShortAC(arg0);
    Particle_SetScaleFactor1(arg0, 1.0f);

    switch (sp26) {
        case 0:
            SetPrimEnvColorFromPair(arg0, 8);
            Particle_SetPrimAlpha(arg0, 0x64);
            Particle_SetSpeed(arg0, 5.0f);
            sp28.x = RandomRangeSigned(0x2000);
            sp28.y = func_81400B28(0x2000, 0x8000);
            sp28.z = 0;
            Particle_AddRotationDeltaVec(arg0, sp28);
            break;

        case 1:
            SetPrimEnvColorFromPair(arg0, 8);
            Particle_SetPrimAlpha(arg0, 0x64);
            Particle_SetSpeed(arg0, 5.0f);
            sp28.x = RandomRangeSigned(0x2000);
            sp28.y = func_81400B28(0x2000, 0x8000);
            sp28.z = 0;
            Particle_AddRotationDeltaVec(arg0, sp28);
            break;

        case 2:
            SetPrimEnvColorFromPair(arg0, 8);
            Particle_SetPrimAlpha(arg0, 0x64);
            Particle_SetVelocityYScaled(arg0, -10.0f);
            Particle_SetSpeed(arg0, 5.0f);
            sp28.x = RandomRangeSigned(0x2000);
            sp28.y = func_81400B28(0x2000, 0x8000);
            sp28.z = 0;
            Particle_AddRotationDeltaVec(arg0, sp28);
            break;

        case 3:
            SetPrimEnvColorFromPair(arg0, 9);
            Particle_SetPrimAlpha(arg0, 0x96);
            Particle_SetSpeed(arg0, 3.0f);
            sp28.x = RandomRangeSigned(0x2000);
            sp28.y = func_81400B28(0x2000, 0x8000);
            sp28.z = 0;
            Particle_AddRotationDeltaVec(arg0, sp28);
            break;

        case 4:
            SetPrimEnvColorFromPair(arg0, 5);
            Particle_SetPrimAlpha(arg0, 0x96);
            Particle_SetSpeed(arg0, 4.0f);
            sp28.x = RandomRangeSigned(0x3000);
            sp28.y = func_81400B28(0x3000, 0x8000);
            sp28.z = 0;
            Particle_AddRotationDeltaVec(arg0, sp28);
            break;
    }

    Particle_SetTimerA6(arg0, RandomMod(5) + 8);
    Particle_IncrementState(arg0);
}

void func_84351984(ParticleEffectInstance* arg0) {
    s16 sp2E = Particle_GetShortCF(arg0);

    switch (arg0->unk_B2) {
        case 1:
            func_843516A0(arg0);
            break;
        case 2:
            Particle_AnimLoopForwardComplete(arg0, 0, 7, 1, 2, 0);

            switch (sp2E) {
                case 3:
                    Particle_ApproachPrimR(arg0, 0, 9);
                    Particle_ApproachSpeedScaled(arg0, 1.0f, 0.75f);
                    Particle_ApproachPrimAlpha(arg0, 0x32, 6);
                    break;

                case 4:
                    Particle_ApproachSpeedScaled(arg0, 1.0f, 0.75f);
                    Particle_AddVelocityYScaled(arg0, 0.5f);
                    Particle_ApproachPrimAlpha(arg0, 0x32, 6);
                    break;

                default:
                    Particle_ApproachPrimG(arg0, 0x64, 6);
                    Particle_ApproachSpeedScaled(arg0, 2.0f, 0.5f);
                    break;
            }
            break;

        case 3:
            Particle_ClearActiveFlag(arg0);
            break;
    }

    if (Particle_IsActive(arg0) != 0) {
        Particle_ApplyB2B4AndAddAll(arg0);
    }
}

void func_84351ADC(ParticleEffectInstance* arg0) {
    s16 sp2E = Particle_GetShortAC(arg0);
    Vec3s sp28;

    Particle_SetScaleFactor1(arg0, 0.1f);
    if (arg0->unk_68.y < 0.0f) {
        arg0->unk_68.y = 0.0f;
    }
    sp28.x = RandomMod(0x10000);
    sp28.y = RandomMod(0x10000);
    sp28.z = 0;
    Particle_SetRotationFromVec3s(arg0, sp28);
    Particle_SetRotationDeltaZ(arg0, func_81400B4C(0x400, 0x400));
    Particle_SetSpeed(arg0, 8.0f);
    SetPrimEnvColorFromPair(arg0, 0x17);
    Particle_SetTimerA6(arg0, sp2E * 0);
    Particle_DisableFlag4(arg0);
    Particle_IncrementState(arg0);
}

void func_84351BCC(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            func_84351ADC(arg0);
            break;

        case 2:
            if (Particle_DecrementTimerA6ToZeroWithCallback(arg0) != 0) {
                Particle_EnableFlag4(arg0);
            }
            break;

        case 3:
            Particle_ApproachScaleFactor1WithCallback(arg0, 0.3f, 0.05f);
            Particle_ApproachSpeedScaled(arg0, 3.0f, 1.0f);
            break;

        case 4:
            Particle_ProcessTimer80(arg0, 2);
            break;

        case 5:
            Particle_ApproachScaleFactor1WithCallback(arg0, 0.05f, 0.05f);
            break;

        case 6:
            Particle_ClearActiveFlag(arg0);
            break;
    }

    if (Particle_HasFlag4(arg0) != 0) {
        Particle_AddRotationDeltaZ(arg0);
        Particle_SetVelocityFromRotationXY(arg0);
        Particle_AddVelocityFromTarget(arg0);
    }
}

void ParticleNode_CreateExplosion(ParticleEffectInstance* arg0) {
    ParticleNode_CreateMultiple(arg0, func_84351BCC, &gParticleEffectData[0x42], 0xC);
    Particle_IncrementState(arg0);
}

void func_84351D20(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            ParticleNode_CreateExplosion(arg0);
            break;

        case 2:
            Particle_ClearActiveFlag(arg0);
            break;
    }
}

void func_84351D70(ParticleEffectInstance* arg0) {
    s16 sp2E = Particle_GetShortAC(arg0);
    s16 sp2C = Particle_GetShortCE(arg0);
    s16 sp2A = Particle_GetShortCF(arg0);
    Vec3s sp24;

    sp24.x = RandomMod(0x10000);
    sp24.y = RandomMod(0x10000);
    sp24.z = 0;

    Particle_SetRotationFromVec3s(arg0, sp24);
    Particle_SetSpeed(arg0, 0.0f);
    Particle_SetAcceleration(arg0, 0.0f);
    SetPrimEnvColorFromPair(arg0, sp2A);
    Particle_SetScaleFactor1(arg0, 0.0f);
    Particle_SetScaleFactor2(arg0, 0.3f);
    Particle_SetScaleFactor3(arg0, 0.05f);
    Particle_SetTimerA6(arg0, sp2E * 2);

    switch (sp2C) {
        case 0:
            Particle_AddComplexDirection(arg0, func_81400ADC(0x1E, 0xA));
            Particle_SetScaleFactor2(arg0, 0.2f);
            break;

        case 1:
            if (arg0->unk_68.y < 0) {
                arg0->unk_68.y = 0;
            }
            Particle_AddComplexDirection(arg0, func_81400ADC(0x28, 0xA));
            Particle_SetScaleFactor2(arg0, 0.3f);
            Particle_SetScaleFactor3(arg0, 0.04f);
            break;

        case 2:
            Particle_SetScaleFactor2(arg0, 0.1f);
            Particle_SetScaleFactor3(arg0, 0.03f);
            Particle_AddComplexDirection(arg0, func_81400ADC(0xC, 5));
            Particle_SetTimerA6(arg0, sp2E * 1);
            break;

        case 3:
            Particle_SetSpeed(arg0, 0.2f);
            Particle_SetScaleFactor1(arg0, 0.1f);
            Particle_AddComplexDirection(arg0, func_81400ADC(0x14, 0x1E));
            Particle_SetTimerA6(arg0, sp2E * 4);
            break;

        case 5:
            Particle_SetRandomVelocityXYZ(arg0, 0, 0xF, 0x19);
            Particle_AddVelocityYScaled(arg0, 15.0f);
            Particle_SetScaleFactor2(arg0, 0.15f);
            Particle_SetScaleFactor3(arg0, 0.02f);
            Particle_SetSpeed(arg0, 0.1f);
            break;

        case 6:
            Particle_AddComplexDirection(arg0, func_81400ADC(0x1E, 0x14));
            Particle_SetSpeed(arg0, 0.3f);
            break;

        case 8:
            Particle_AddComplexDirection(arg0, func_81400ADC(8, 2));
            Particle_SetScaleFactor2(arg0, 0.1f);
            Particle_SetScaleFactor3(arg0, 0.04f);
            Particle_SetSpeed(arg0, 0.4f);
            Particle_SetTimerA6(arg0, 0);
            break;

        case 7:
            Particle_AddComplexDirection(arg0, func_81400ADC(0xA, 2));
            Particle_SetScaleFactor2(arg0, 0.2f);
            Particle_SetScaleFactor3(arg0, 0.025f);
            Particle_SetSpeed(arg0, 1.0f);
            break;

        case 9:
            Particle_AddComplexDirection(arg0, func_81400ADC(0x1E, 0x14));
            Particle_SetScaleFactor2(arg0, 0.3f);
            Particle_SetScaleFactor3(arg0, 0.025f);
            Particle_SetSpeed(arg0, 0.0f);
            Particle_SetAcceleration(arg0, 0.02f);
            break;

        case 10:
            Particle_AddComplexDirection(arg0, func_81400ADC(0x19, 5));
            Particle_AddVelocityYScaled(arg0, 10.0f);
            Particle_SetScaleFactor2(arg0, 0.2f);
            break;

        case 11:
            Particle_AddComplexDirection(arg0, func_81400ADC(5, 5));
            Particle_SetSpeed(arg0, RandomMod(5) + 5.0f);
            break;
    }
    Particle_DisableFlag4(arg0);
    Particle_IncrementState(arg0);
}

void func_8435226C(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            func_84351D70(arg0);
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

void ParticleEffect_FireworkStage1(ParticleEffectInstance* arg0) {
    s16 sp26 = Particle_GetShortAC(arg0);
    s16 sp24 = Particle_GetShortCF(arg0);

    Particle_SetScaleFactor1(arg0, 0.0f);
    Particle_SetScaleFactor2(arg0, 0.3f);
    Particle_SetScaleFactor3(arg0, 0.05f);
    Particle_SetRandomVelocityXYZ(arg0, 0xA, 0x14, 0x14);
    Particle_AddVelocityForward(arg0, 15.0f);
    Particle_AddVelocityYScaled(arg0, 7.0f);
    Particle_SetSpeed(arg0, RandomMod(5) + 8.0f);
    Particle_SetTimerA6(arg0, sp26 * 2);
    SetPrimEnvColorFromPair(arg0, sp24);
    Particle_DisableFlag4(arg0);
    Particle_IncrementState(arg0);
}

void ParticleEffect_FireworkHandler(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            ParticleEffect_FireworkStage1(arg0);
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
        Particle_SetTargetVelocityBackward(arg0);
    }
}

void ParticleEffect_FireworkHandler2(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            func_84351D70(arg0);
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
        Particle_ApplyB2B4AndAddAll(arg0);
        if (arg0->unk_2C.y < 0.0f) {
            Particle_ClearActiveFlag(arg0);
        }
    }
}

void func_84352620(ParticleEffectInstance* arg0) {
    s16 sp26 = Particle_GetShortAC(arg0);

    Particle_SetScaleFactor1(arg0, 0.7f);
    Particle_SetVelocityYScaled(arg0, 10.0f);
    SetPrimEnvColorFromPair(arg0, 0x19);
    Particle_SetPrimAlpha(arg0, 0xFF);
    Particle_SetTimerA6(arg0, sp26 * 4);
    Particle_DisableFlag4(arg0);
    Particle_IncrementState(arg0);
}

void ParticleEffect_SparkleHandler(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            func_84352620(arg0);
            break;

        case 2:
            if (Particle_ProcessTimer80(arg0, arg0->unk_A6) != 0) {
                Particle_EnableFlag4(arg0);
            }
            break;

        case 3:
            Particle_AnimLoopForwardComplete(arg0, 0, 5, 1, 1, 2);
            break;

        case 4:
            Particle_ClearActiveFlag(arg0);
            break;
    }
}

void func_84352754(ParticleEffectInstance* arg0) {
    s16 sp26 = Particle_GetShortAC(arg0);
    s16 sp24 = Particle_GetShortCE(arg0);

    SetPrimEnvColorFromPair(arg0, Particle_GetShortCF(arg0));

    switch (sp24) {
        case 1:
            Particle_SetSpeed(arg0, 0.2f);
            Particle_SetScaleFactor1(arg0, 1.0f);
            break;

        case 5:
            Particle_SetSpeed(arg0, 0.2f);
            Particle_SetScaleFactor1(arg0, 1.0f);
            break;

        case 6:
            Particle_SetSpeed(arg0, 0.4f);
            Particle_SetScaleFactor1(arg0, 1.5f);
            break;

        case 16:
            Particle_SetSpeed(arg0, 0.4f);
            Particle_SetScaleFactor1(arg0, 2.0f);
            break;

        case 7:
            Particle_SetSpeed(arg0, 0.4f);
            Particle_SetScaleFactor1(arg0, 1.5f);
            break;

        case 8:
            Particle_SetSpeed(arg0, 0.4f);
            Particle_SetScaleFactor1(arg0, 1.5f);
            Particle_AddVelocityYScaled(arg0, -10.0f);
            break;

        case 12:
            Particle_SetScaleFactor1(arg0, 0.75f);
            Particle_SetSpeed(arg0, 0.4f);
            Particle_SetRandomVelocityXYZ(arg0, 8, 0xA, 8);
            break;

        case 13:
            Particle_SetScaleFactor1(arg0, 1.0f);
            Particle_SetSpeed(arg0, 0.0f);
            Particle_SetRandomVelocityX(arg0, 0x1E);
            Particle_SetRandomVelocityYOffset(arg0, 0x14, 0xA);
            Particle_SetRandomVelocityZ(arg0, 0x1E);
            break;

        case 14:
            Particle_SetScaleFactor1(arg0, 1.0f);
            Particle_SetSpeed(arg0, 0.0f);
            Particle_SetRandomVelocityX(arg0, 0x14);
            Particle_SetRandomVelocityYOffset(arg0, 0x14, 0xA);
            Particle_SetRandomVelocityZ(arg0, 0xF);
            break;

        case 15:
            Particle_SetScaleFactor1(arg0, 1.5f);
            Particle_SetSpeed(arg0, 0.3f);
            Particle_SetRandomVelocityXYZ(arg0, 0xA, 0xA, 0xA);
            break;
    }

    Particle_SetPrimAlpha(arg0, 0xFF);
    Particle_SetTimerA6(arg0, sp26 * 4);
    Particle_DisableFlag4(arg0);
    Particle_IncrementState(arg0);
}

void ParticleEffect_FireworkMain(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            func_84352754(arg0);
            break;

        case 2:
            if (Particle_ProcessTimer80(arg0, arg0->unk_A6) != 0) {
                Particle_EnableFlag4(arg0);
            }
            break;

        case 3:
            Particle_AnimLoopForwardComplete(arg0, 0, 3, 1, 1, 0);
            Particle_SetTargetVelocityBackward(arg0);
            break;

        case 4:
            Particle_ClearActiveFlag(arg0);
            break;
    }
}

void ParticleEffect_FireworkColors(ParticleEffectInstance* arg0) {
    s16 sp26 = Particle_GetShortAC(arg0);

    switch (Particle_GetShortCF(arg0)) {
        case 0:
            SetPrimEnvColorFromPair(arg0, 0);
            Particle_SetSpeed(arg0, 0.2f);
            Particle_SetScaleFactor1(arg0, 1.0f);
            Particle_SetTimerA6(arg0, sp26 * 2);
            Particle_AddVelocityYScaled(arg0, 15.0f);
            break;

        case 1:
            SetPrimEnvColorFromPair(arg0, 0);
            Particle_SetSpeed(arg0, 0.2f);
            Particle_SetScaleFactor1(arg0, 1.0f);
            Particle_SetTimerA6(arg0, sp26 * 2);
            break;

        case 2:
            SetPrimEnvColorFromPair(arg0, 0);
            Particle_SetSpeed(arg0, 0.2f);
            Particle_SetScaleFactor1(arg0, 1.0f);
            Particle_SetTimerA6(arg0, sp26 * 2);
            Particle_AddVelocityYScaled(arg0, -10.0f);
            break;

        case 3:
            SetPrimEnvColorFromPair(arg0, 1);
            Particle_SetScaleFactor1(arg0, 0.5f);
            Particle_SetSpeed(arg0, 0.4f);
            Particle_SetTimerA6(arg0, sp26 * 2);
            break;

        case 4:
            SetPrimEnvColorFromPair(arg0, 2);
            Particle_SetScaleFactor1(arg0, 0.5f);
            Particle_SetSpeed(arg0, 0.4f);
            Particle_SetTimerA6(arg0, sp26 * 2);
            break;

        case 5:
            SetPrimEnvColorFromPair(arg0, 3);
            Particle_SetSpeed(arg0, 0.2f);
            Particle_SetScaleFactor1(arg0, 1.0f);
            Particle_SetTimerA6(arg0, sp26 * 2);
            break;

        case 6:
            SetPrimEnvColorFromPair(arg0, 0);
            Particle_SetSpeed(arg0, 0.4f);
            Particle_SetScaleFactor1(arg0, 1.5f);
            Particle_SetTimerA6(arg0, sp26 * 2);
            break;

        case 9:
            SetPrimEnvColorFromPair(arg0, 0);
            Particle_SetSpeed(arg0, 0.2f);
            Particle_SetScaleFactor1(arg0, 1.0f);
            Particle_SetRandomVelocityXYZ(arg0, 0xF, 0xF, 0xF);
            Particle_AddVelocityYScaled(arg0, 10.0f);
            Particle_SetTimerA6(arg0, sp26 * 2);
            break;

        case 10:
            SetPrimEnvColorFromPair(arg0, 0);
            Particle_SetSpeed(arg0, 0.2f);
            Particle_SetScaleFactor1(arg0, 1.0f);
            Particle_SetRandomVelocityXYZ(arg0, 0x14, 0, 0x14);
            Particle_SetVelocityYScaled(arg0, 0.0f);
            Particle_SetTimerA6(arg0, sp26 * 2);
            break;

        case 11:
            SetPrimEnvColorFromPair(arg0, 0);
            Particle_SetSpeed(arg0, 0.2f);
            Particle_SetScaleFactor1(arg0, 1.0f);
            Particle_SetRandomVelocityXYZ(arg0, 0xA, 0, 0xA);
            Particle_SetVelocityYScaled(arg0, 30.0f - (sp26 * 5.0f));
            Particle_SetTimerA6(arg0, sp26 * 2);
            break;
    }

    Particle_SetPrimAlpha(arg0, 0xFF);
    Particle_DisableFlag4(arg0);
    Particle_IncrementState(arg0);
}

void ParticleEffect_FireworkMain2(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            ParticleEffect_FireworkColors(arg0);
            break;

        case 2:
            if (Particle_ProcessTimer80(arg0, arg0->unk_A6) != 0) {
                Particle_EnableFlag4(arg0);
                Particle_SetTimerA6(arg0, 2);
            }
            break;

        case 3:
            Particle_AnimLoopForwardComplete(arg0, 0, 3, 1, 1, 0);
            Particle_SetTargetVelocityBackward(arg0);
            if ((Particle_DecrementTimerA6ToZero != 0) && (arg0->unk_B8 == 0)) {
                Particle_IncrementFlag2Counter(arg0);
            }
            break;

        case 4:
            Particle_ClearActiveFlag(arg0);
            break;
    }

    if (arg0->unk_B8 == 1) {
        func_8432D8E8(arg0, func_84350260, &gParticleEffectData[0x3D], 1, 8, 0);
        Particle_IncrementFlag2Counter(arg0);
    }
}

void ParticleEffect_ModeSpecificColors(ParticleEffectInstance* arg0) {
    s16 sp26 = Particle_GetShortAC(arg0);

    switch (Particle_GetShortCF(arg0)) {
        case 3:
            SetPrimEnvColorFromPair(arg0, 1);
            Particle_SetScaleFactor1(arg0, 1.5f);
            Particle_SetSpeed(arg0, 0.4f);
            Particle_SetTimerA6(arg0, sp26 * 2);
            Particle_SetByteCF(arg0, 0);
            break;

        case 4:
            SetPrimEnvColorFromPair(arg0, 2);
            Particle_SetScaleFactor1(arg0, 1.5f);
            Particle_SetSpeed(arg0, 0.4f);
            Particle_SetTimerA6(arg0, sp26 * 2);
            Particle_SetByteCF(arg0, 1);
            break;
    }

    Particle_SetPrimAlpha(arg0, 0xFF);
    Particle_DisableFlag4(arg0);
    Particle_IncrementState(arg0);
}

s32 ParticleEffect_ModeSpecificHandler(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            ParticleEffect_ModeSpecificColors(arg0);
            break;

        case 2:
            if (Particle_ProcessTimer80(arg0, arg0->unk_A6) != 0) {
                Particle_EnableFlag4(arg0);
                Particle_SetTimerA6(arg0, 2);
            }
            break;

        case 3:
            Particle_AnimLoopForwardComplete(arg0, 0, 3, 1, 1, 0);
            Particle_SetTargetVelocityBackward(arg0);
            if ((Particle_DecrementTimerA6ToZero != NULL) && (arg0->unk_B8 == 0)) {
                Particle_IncrementFlag2Counter(arg0);
            }
            break;

        case 4:
            Particle_ClearActiveFlag(arg0);
            break;
    }

    switch (arg0->unk_B8) {
        case 1:
            ParticleNode_CreateMultiple(arg0, func_843515C8, &gParticleEffectData[0x38], 8);
            Particle_IncrementFlag2Counter(arg0);
            break;

        case 2:
            if (Particle_StartTimer2(arg0, 1) != 0) {
                ParticleNode_CreateMultiple(arg0, func_843515C8, &gParticleEffectData[0x38], 4);
                Particle_IncrementFlag2Counter(arg0);
            }
            break;

        case 3:
            if (Particle_StartTimer2(arg0, 1) != 0) {
                ParticleNode_CreateMultiple(arg0, func_843515C8, &gParticleEffectData[0x38], 4);
                Particle_IncrementFlag2Counter(arg0);
            }
            break;
    }
}

void ParticleEffect_SmallBurst(ParticleEffectInstance* arg0) {
    Particle_GetShortAC(arg0);
    Particle_SetScaleFactor1(arg0, 0.05f);
    SetPrimEnvColorFromPair(arg0, 7);
    Particle_SetPrimAlpha(arg0, 0xFF);
    Particle_SetTimerA6(arg0, 0x32);
    Particle_IncrementState(arg0);
}

void ParticleEffect_SmallBurstHandler(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            ParticleEffect_SmallBurst(arg0);
            break;

        case 2:
            Particle_AnimLoopForward(arg0, 0, 5, 1, 1, -1);
            Particle_ApproachScaleFactor1(arg0, 0.3f, 0.01f);
            Particle_DecrementTimerA6ToZeroWithCallback(arg0);
            break;

        case 3:
            Particle_ClearActiveFlag(arg0);
            break;
    }
}

void ParticleEffect_RandomDirection(ParticleEffectInstance* arg0) {
    s16 sp2E;
    s16 sp2C;
    Vec3s sp24;

    sp2E = Particle_GetShortAC(arg0);
    sp2C = sp2E % 3;
    Particle_SetScaleFactor1(arg0, 0.4f);
    Particle_SetSpeed(arg0, 1.0f);

    sp24.x = MathUtil_Random16();
    sp24.y = MathUtil_Random16();
    sp24.z = 0;
    Particle_SetRotationFromVec3s(arg0, sp24);

    switch (sp2C) {
        case 0:
            Particle_SetVelocityScaledXYZ(arg0, 0.0f, -2.0f, 0.0f);
            break;

        case 1:
            Particle_SetVelocityScaledXYZ(arg0, 0.0f, 2.0f, 2.0f);
            break;

        case 2:
            Particle_SetVelocityScaledXYZ(arg0, 0.0f, 2.0f, -2.0f);
            break;
    }

    SetPrimEnvColorFromPair(arg0, 0x17);
    Particle_SetTimerA6(arg0, sp2E * 4);
    Particle_DisableFlag4(arg0);
    Particle_IncrementState(arg0);
}

void ParticleEffect_RandomDirectionHandler(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            ParticleEffect_RandomDirection(arg0);
            break;

        case 2:
            if (Particle_ProcessTimer80(arg0, arg0->unk_A6) != 0) {
                Particle_EnableFlag4(arg0);
            }
            break;

        case 3:
            Particle_AnimLoopForwardComplete(arg0, 0, 7, 1, 1, 0);
            Particle_ApproachSpeedScaled(arg0, 0.2f, 0.25f);
            Particle_ApproachScaleFactor1(arg0, 0.5f, 0.02f);
            Particle_ApproachPrimB(arg0, 0, 0x20);
            Particle_ApproachEnvG(arg0, 0, 0x20);
            if (arg0->unk_C7 >= 6) {
                Particle_ApproachPrimG(arg0, 0, 0x20);
                Particle_ApproachPrimAlpha(arg0, 0x64, 0x4E);
            }
            Particle_ApplyB278AndCopyXZAlt(arg0);
            break;

        case 4:
            Particle_ClearActiveFlag(arg0);
            break;
    }
}

void ParticleEffect_RandomDirectionDuplicate(ParticleEffectInstance* arg0) {
    s16 sp2E = Particle_GetShortAC(arg0);
    s16 sp2C = sp2E % 3;
    Vec3s sp24;

    Particle_SetScaleFactor1(arg0, 0.4f);
    Particle_SetSpeed(arg0, 1.0f);

    sp24.x = MathUtil_Random16();
    sp24.y = MathUtil_Random16();
    sp24.z = 0;
    Particle_SetRotationFromVec3s(arg0, sp24);

    switch (sp2C) {
        case 0:
            Particle_SetVelocityScaledXYZ(arg0, 0.0f, -2.0f, 0.0f);
            break;

        case 1:
            Particle_SetVelocityScaledXYZ(arg0, 0.0f, 2.0f, 2.0f);
            break;

        case 2:
            Particle_SetVelocityScaledXYZ(arg0, 0.0f, 2.0f, -2.0f);
            break;
    }

    SetPrimEnvColorFromPair(arg0, 0x17);
    Particle_SetTimerA6(arg0, sp2E * 4);
    Particle_DisableFlag4(arg0);
    Particle_IncrementState(arg0);
}

void ParticleEffect_RandomDirectionHandler2(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            ParticleEffect_RandomDirectionDuplicate(arg0);
            break;

        case 2:
            if (Particle_ProcessTimer80(arg0, arg0->unk_A6) != 0) {
                Particle_EnableFlag4(arg0);
            }
            break;

        case 3:
            Particle_AnimLoopForwardComplete(arg0, 0, 7, 1, 1, 0);
            Particle_ApproachSpeedScaled(arg0, 0.2f, 0.25f);
            Particle_ApproachScaleFactor1(arg0, 0.5f, 0.02f);
            Particle_ApproachPrimB(arg0, 0, 0x20);
            Particle_ApproachEnvG(arg0, 0, 0x20);
            if (arg0->unk_C7 >= 6) {
                Particle_ApproachPrimG(arg0, 0, 0x20);
                Particle_ApproachPrimAlpha(arg0, 0x64, 0x4E);
            }
            Particle_ApplyB278AndCopyXZAlt(arg0);
            break;

        case 4:
            Particle_ClearActiveFlag(arg0);
            break;
    }
}

void ParticleEffect_SetColorFromMode(ParticleEffectInstance* arg0) {
    s16 sp1E;

    switch (GetActionScriptId()) {
        case 0x4D:
            sp1E = 0x43;
            break;
        case 0x4E:
            sp1E = 5;
            break;
        case 0x4F:
            sp1E = 0xC;
            break;
        case 0x93:
            sp1E = 5;
            break;
        case 0x1C:
            sp1E = 0x31;
            break;
        case 0x6C:
            sp1E = 0x1C;
            break;
        case 0x7B:
            sp1E = 0x1E;
            break;
        case 0x36:
            sp1E = 0x1D;
            break;
        case 0x72:
            sp1E = 0x1E;
            break;
        case 0x8B:
            sp1E = 0x1E;
            break;
    }
    SetPrimEnvColorFromPair(arg0, sp1E);
}

void ParticleEffect_ColorfulBurst(ParticleEffectInstance* arg0) {
    Vec3s sp28;
    s16 sp26 = Particle_GetShortAC(arg0);
    s16 sp24 = Particle_GetShortCF(arg0);

    Particle_SetScaleFactor1(arg0, 1.0f);
    sp28.x = MathUtil_Random16();
    sp28.y = MathUtil_Random16();
    sp28.z = 0;
    Particle_SetRotationFromVec3s(arg0, sp28);

    switch (sp24) {
        case 0:
            Particle_SetRandomVelocityXYZ(arg0, 0xF, 0xF, 0xF);
            Particle_AddVelocityYScaled(arg0, 10.0f);
            Particle_SetSpeed(arg0, 1.0f);
            Particle_SetTimerA6(arg0, sp26 * 2);
            break;

        case 1:
            Particle_SetRandomVelocityXYZ(arg0, 0xA, 0xA, 0xA);
            Particle_AddVelocityYScaled(arg0, 10.0f);
            Particle_SetSpeed(arg0, 0.0f);
            Particle_SetTimerA6(arg0, sp26 * 2);
            break;
    }

    ParticleEffect_SetColorFromMode(arg0);
    Particle_SetPrimAlpha(arg0, 0xC8);
    Particle_DisableFlag4(arg0);
    Particle_IncrementState(arg0);
}

void ParticleEffect_ColorfulBurstHandler(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            ParticleEffect_ColorfulBurst(arg0);
            break;

        case 2:
            if (Particle_ProcessTimer80(arg0, arg0->unk_A6) != 0) {
                Particle_EnableFlag4(arg0);
            }
            break;

        case 3:
            Particle_AnimLoopForwardComplete(arg0, 0, 7, 1, 2, 0);
            Particle_ApproachPrimAlpha(arg0, 0x64, 6);
            Particle_ApproachScaleFactor1(arg0, 2.0f, 0.075f);
            Particle_ApplyB2B4AndAddAll(arg0);
            break;

        case 4:
            Particle_ClearActiveFlag(arg0);
            break;
    }
}

void ParticleEffect_SimpleColor(ParticleEffectInstance* arg0) {
    Particle_SetScaleFactor1(arg0, 0.2f);
    SetPrimEnvColorFromPair(arg0, Particle_GetShortCF(arg0));
    Particle_SetPrimAlpha(arg0, 0xC8);
    Particle_SetTimerA6(arg0, 0x18);
    arg0->unk_74 = 0.02f;
    Particle_IncrementState(arg0);
}

void ParticleEffect_SimpleColorHandler(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            ParticleEffect_SimpleColor(arg0);
            break;

        case 2:
            Particle_ApproachScaleFactor1(arg0, 2.0f, 0.02f);
            Particle_ApproachEnvG(arg0, 0xC8, 2);
            Particle_DecrementTimerA6ToZeroWithCallback(arg0);
            break;

        case 3:
            ApproachF32(&arg0->unk_74, 0.008f, 0.001f);
            Particle_ApproachScaleFactor1(arg0, 2.0f, arg0->unk_74);
            Particle_ApproachEnvG(arg0, 0xC8, 2);
            Particle_ApproachPrimAlphaWithCallback(arg0, 0, 0xC);
            break;

        case 4:
            Particle_ClearActiveFlag(arg0);
            break;
    }
}

void ParticleEffect_RandomSpeed(ParticleEffectInstance* arg0) {
    s16 sp26 = Particle_GetShortAC(arg0);

    Particle_SetScaleFactor1(arg0, 1.0f);
    Particle_SetRandomVelocityXYZ(arg0, 0xF, 0xF, 0xF);
    Particle_SetSpeed(arg0, (RandomMod(0x32) * 0.02f) + 0.5f);
    SetPrimEnvColorFromPair(arg0, Particle_GetShortCF(arg0));
    Particle_SetPrimAlpha(arg0, 0x64);
    Particle_SetTimerA6(arg0, sp26 * 4);
    Particle_DisableFlag4(arg0);
    Particle_IncrementState(arg0);
}

void ParticleEffect_RandomSpeedHandler(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            ParticleEffect_RandomSpeed(arg0);
            break;

        case 2:
            if (Particle_DecrementTimerA6ToZeroWithCallback(arg0) != 0) {
                Particle_SetTimerA6(arg0, RandomMod(4) + 4);
                Particle_EnableFlag4(arg0);
            }
            break;

        case 3:
            Particle_DecrementTimerA6ToZeroWithCallback(arg0);
            Particle_SetTargetVelocityY(arg0);
            break;

        case 4:
            Particle_AnimLoopForwardComplete(arg0, 0, 7, 1, 2, 0);
            Particle_ApproachPrimAlpha(arg0, 0x40, 4);
            Particle_SetTargetVelocityY(arg0);
            break;

        case 5:
            Particle_ClearActiveFlag(arg0);
            break;
    }
}

void ParticleEffect_ApplyModeSpecifics(ParticleEffectInstance* arg0) {
    f32 sp24 = 0.0f;
    f32 sp20 = 0.0f;
    s32 sp1C = 0;

    switch (func_843081BC(arg0->unk_10)) {
        case 0x9:
            sp20 = 5.0f;
            break;

        case 0x19:
            sp20 = 0.0f;
            Particle_SetScaleFactor1(arg0, 1.0f);
            break;

        case 0x37:
            sp20 = 8.0f;
            break;

        case 0x49:
            sp1C = 1;
            break;

        case 0x50:
            sp1C = 1;
            break;

        case 0x74:
            sp20 = 5.0f;
            break;

        case 0x82:
            Particle_SetScaleFactor1(arg0, 1.5f);
            sp24 = -5.0f;
            sp20 = 10.0f;
            sp1C = 1;
            break;

        case 0x83:
            Particle_SetScaleFactor1(arg0, 1.5f);
            sp20 = 5.0f;
            sp1C = 1;
            break;

        case 0x86:
            sp20 = 10.0f;
            break;

        case 0x95:
            sp20 = 10.0f;
            break;
    }

    if (sp1C == 0) {
        Particle_SetRandomVelocityXYZ(arg0, 0xA, 0, 0x23);
    } else {
        Particle_SetRandomVelocityXYZ(arg0, 0xF, 0, 0x2D);
    }

    Particle_AddVelocityForward(arg0, 10.0f + sp24);
    Particle_AddVelocityYScaled(arg0, 5.0f + sp20);
}

void ParticleEffect_BasicSetup(ParticleEffectInstance* arg0) {
    Vec3s sp30;
    s16 sp2E = Particle_GetShortAC(arg0);
    u16 sp2C = Particle_GetShortCE(arg0);

    Particle_SetShortB0(arg0, 2);
    Particle_SetTimerA6(arg0, sp2E * 2);
    SetPrimEnvColorFromPair(arg0, Particle_GetShortCF(arg0));

    switch (sp2C) {
        case 0:
            Particle_SetScaleFactor1(arg0, 1.0f);
            Particle_SetRandomVelocityXYZ(arg0, 0xA, 0xA, 0xA);
            Particle_SetSpeed(arg0, (RandomMod(0x32) * 0.02f) + 0.5f);
            Particle_SetPrimAlpha(arg0, 0x64);
            Particle_SetShortAE(arg0, 4);
            break;

        case 1:
            Particle_SetScaleFactor1(arg0, 1.0f);
            Particle_SetRandomVelocityXYZ(arg0, 0xA, 0xF, 0x3C);
            Particle_SetSpeed(arg0, (RandomMod(0x32) * 0.04f) + 1.0f);
            Particle_SetPrimAlpha(arg0, 0x64);
            Particle_SetShortAE(arg0, 4);
            break;

        case 2:
            Particle_SetScaleFactor1(arg0, 1.5f);
            Particle_SetRandomVelocityXYZ(arg0, 0xF, 0x14, 0x19);
            Particle_SetSpeed(arg0, (RandomMod(0x32) * 0.07f) + 4.0f);
            Particle_SetPrimAlpha(arg0, 0xA0);
            Particle_SetTimerA6(arg0, sp2E);
            Particle_SetShortAE(arg0, 0xA);
            break;

        case 3:
            Particle_SetScaleFactor1(arg0, 1.0f);
            Particle_SetRandomVelocityXYZ(arg0, 0xA, 0, 0x19);
            Particle_AddVelocityForward(arg0, 10.0f);
            Particle_AddVelocityYScaled(arg0, 5.0f);
            Particle_SetSpeed(arg0, (RandomMod(0xA) * 0.05f) + 0.2f);
            Particle_SetPrimAlpha(arg0, 0xFF);
            Particle_SetShortAE(arg0, 2);
            Particle_SetShortB0(arg0, 2);
            break;

        case 8:
            Particle_SetScaleFactor1(arg0, 1.2f);
            ParticleEffect_ApplyModeSpecifics(arg0);
            Particle_SetSpeed(arg0, (RandomMod(0xA) * 0.05f) + 0.2f);
            Particle_SetPrimAlpha(arg0, 0xFF);
            Particle_SetShortAE(arg0, 2);
            Particle_SetShortB0(arg0, 2);
            Particle_SetTimerA6(arg0, sp2E);
            break;

        case 12:
            Particle_SetScaleFactor1(arg0, 1.2f);
            Particle_SetRandomVelocityXYZ(arg0, 0xA, 0, 0x28);
            Particle_AddVelocityForward(arg0, 10.0f);
            Particle_AddVelocityYScaled(arg0, 5.0f);
            Particle_SetSpeed(arg0, (RandomMod(0xA) * 0.05f) + 0.2f);
            Particle_SetPrimAlpha(arg0, 0xFF);
            Particle_SetShortAE(arg0, 2);
            Particle_SetShortB0(arg0, 2);
            Particle_SetTimerA6(arg0, sp2E);
            break;

        case 4:
            Particle_SetScaleFactor1(arg0, 0.5f);
            Particle_SetRandomVelocityXYZ(arg0, 0xA, 0, 0x14);
            Particle_SetSpeed(arg0, (RandomMod(0xA) * 0.05f) + 0.5f);
            Particle_SetPrimAlpha(arg0, 0xFF);
            Particle_SetShortAE(arg0, 2);
            Particle_SetShortB0(arg0, 2);
            break;

        case 5:
            Particle_SetScaleFactor1(arg0, 1.0f);
            Particle_SetRandomVelocityXYZ(arg0, 0xF, 0xF, 0xF);
            Particle_SetSpeed(arg0, (RandomMod(0x32) * 0.02f) + 1.0f);
            Particle_SetPrimAlpha(arg0, 0x80);
            Particle_SetShortAE(arg0, 4);
            break;

        case 6:
            Particle_SetScaleFactor1(arg0, 0.5f);
            Particle_SetRandomVelocityXYZ(arg0, 5, 5, 5);
            Particle_SetSpeed(arg0, 0.5f);
            Particle_SetPrimAlpha(arg0, 0xC8);
            Particle_SetShortAE(arg0, 4);
            break;

        case 7:
            Particle_SetScaleFactor1(arg0, 0.5f);
            Particle_SetRandomVelocityXYZ(arg0, 0xA, 0, 5);
            Particle_AddVelocityYScaled(arg0, 10.0f);
            Particle_SetSpeed(arg0, (RandomMod(0x14) * 0.02f) + 0.5f);
            Particle_SetPrimAlpha(arg0, 0xC8);
            Particle_SetShortAE(arg0, 4);
            break;

        case 9:
            Particle_SetScaleFactor1(arg0, 1.0f);
            Particle_SetRandomVelocityXYZ(arg0, 0xA, 0, 0xA);
            sp30.x = RandomRangeSigned(0x1800) - 0x4000;
            sp30.y = RandomMod(0x10000);
            sp30.z = 0;
            Particle_AddRotationDeltaVec(arg0, sp30);
            Particle_SetSpeed(arg0, (RandomMod(0x14) * 0.15f) + 3.0f);
            Particle_SetVelocityFromRotationXY(arg0);
            Particle_SetTimerA6(arg0, sp2E);
            Particle_SetShortAE(arg0, 0xA);
            break;

        case 10:
            Particle_SetScaleFactor1(arg0, 0.8f);
            Particle_SetRandomVelocityXYZ(arg0, 0xF, 0, 0xF);
            sp30.x = RandomRangeSigned(0x1000) - 0x4000;
            sp30.y = RandomMod(0x10000);
            sp30.z = 0;
            Particle_AddRotationDeltaVec(arg0, sp30);
            Particle_SetSpeed(arg0, (RandomMod(0x14) * 0.15f) + 4.0f);
            Particle_SetVelocityFromRotationXY(arg0);
            Particle_SetTimerA6(arg0, 0);
            Particle_SetShortAE(arg0, 0xA);
            break;

        case 11:
            Particle_SetScaleFactor1(arg0, 0.05f);
            Particle_SetRandomVelocityXYZ(arg0, 0xA, 0, 0xA);
            sp30.x = RandomRangeSigned(0x1000) - 0x4000;
            sp30.y = RandomMod(0x10000);
            sp30.z = 0;
            Particle_AddRotationDeltaVec(arg0, sp30);
            Particle_SetSpeed(arg0, (RandomMod(0x14) * 0.3f) + 6.0f);
            Particle_SetVelocityFromRotationXY(arg0);
            Particle_SetPrimAlpha(arg0, 0xFF);
            Particle_SetTimerA6(arg0, sp2E);
            Particle_SetShortAE(arg0, 0xA);
            break;
    }

    Particle_DisableFlag4(arg0);
    Particle_IncrementState(arg0);
}

void ParticleEffect_BasicSetupHandler(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            ParticleEffect_BasicSetup(arg0);
            break;

        case 2:
            if (Particle_DecrementTimerA6ToZeroWithCallback(arg0) != 0) {
                Particle_EnableFlag4(arg0);
            }
            break;

        case 3:
            Particle_AnimLoopForwardComplete(arg0, 0, 7, 1, arg0->unk_B0, 0);
            Particle_ApproachPrimAlpha(arg0, 0x40, arg0->unk_AE);
            Particle_SetTargetVelocityY(arg0);
            break;

        case 4:
            Particle_ClearActiveFlag(arg0);
            break;
    }
}

void ParticleEffect_AdjustLifetime(ParticleEffectInstance* arg0) {
    f32 sp1C = 50.0f;
    f32 sp18 = 30.0f;

    switch (func_843081BC(arg0->unk_10)) {
        case 3:
            sp1C = 40.0f;
            break;

        case 0x5F:
            sp1C = 25.0f;
            break;

        case 0x67:
            sp1C = 35.0f;
            break;

        case 0x71:
            sp18 = 35.0f;
            break;

        case 0x73:
            sp1C = 40.0f;
            break;

        case 0x82:
            sp1C = 20.0f;
            break;

        case 0x83:
            sp1C = 30.0f;
            break;
    }

    Particle_AddVelocityForward(arg0, sp1C);
    Particle_AddVelocityYScaled(arg0, sp18);
    Particle_SetAcceleration(arg0, 0.4f);
}

void ParticleEffect_AdvancedSetup(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            ParticleEffect_BasicSetup(arg0);
            ParticleEffect_AdjustLifetime(arg0);
            break;

        case 2:
            if (Particle_DecrementTimerA6ToZeroWithCallback(arg0) != 0) {
                Particle_EnableFlag4(arg0);
                Particle_EnableFlag2(arg0);
                Particle_SetTimerA6(arg0, 0x14);
            }
            break;

        case 3:
            Particle_AnimLoopForward(arg0, 0, 7, 1, 2, 0);
            Particle_ApproachPrimAlpha(arg0, 0x40, 2);
            Particle_FallAccelerateAndCheckGround(arg0);
            Particle_SetTargetVelocityCustom(arg0, 10.0f);
            Particle_DecrementTimerA6ToZeroWithCallback(arg0);
            break;

        case 4:
            Particle_ClearActiveFlag(arg0);
            break;
    }

    switch (arg0->unk_B8) {
        case 1:
            Particle_ApproachAcceleration(arg0, 1.0f, 0.1f);
            if (Particle_StartTimer2(arg0, 4) != 0) {
                Particle_IncrementFlag2Counter(arg0);
                Particle_SetAcceleration(arg0, 0.2f);
            }
            break;

        case 2:
            Particle_ApproachAcceleration(arg0, -0.5f, 0.2f);
            break;
    }
}

void ParticleEffect_GravityAdjust(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            ParticleEffect_BasicSetup(arg0);
            break;

        case 2:
            if (Particle_DecrementTimerA6ToZeroWithCallback(arg0) != 0) {
                Particle_EnableFlag4(arg0);
            }
            break;

        case 3:
            Particle_AnimLoopForwardComplete(arg0, 0, 7, 1, arg0->unk_B0, 0);
            Particle_ApproachPrimAlpha(arg0, 0x40, arg0->unk_AE);
            break;

        case 4:
            Particle_ClearActiveFlag(arg0);
            break;
    }

    if (Particle_IsActive(arg0) != 0) {
        Particle_DecrementAccelerationYClamp(arg0, -2.0f, 0.3f);
        Particle_AddVelocityFromTarget(arg0);
    }
}

void ParticleEffect_ConditionalStop(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            ParticleEffect_BasicSetup(arg0);
            break;

        case 2:
            if (Particle_DecrementTimerA6ToZeroWithCallback(arg0) != 0) {
                Particle_EnableFlag4(arg0);
            }
            break;

        case 3:
            if (arg0->unk_2C.y < 0.0f) {
                Particle_ClearActiveFlag(arg0);
            }
            break;
    }

    if (Particle_IsActive(arg0) != 0) {
        Particle_DecrementAccelerationYClamp(arg0, -10.0f, 0.8f);
        Particle_AddVelocityFromTarget(arg0);
    }
}

void ParticleEffect_RandomRotationSetup(ParticleEffectInstance* arg0) {
    UNUSED s32 pad;

    Particle_GetShortAC(arg0);
    Particle_GetByteCD(arg0);
    SetPrimEnvColorFromPair(arg0, Particle_GetShortCF(arg0));
    Particle_SetScaleFactor1(arg0, 0.5f);
    Particle_AddRotationDeltaXYZ(arg0, RandomMod(0x10000), RandomMod(0x10000), 0);
    Particle_SetSpeed(arg0, 0.75f);
    Particle_SetPrimAlpha(arg0, 0xFF);
    Particle_IncrementState(arg0);
}

void ParticleEffect_RandomRotationHandler(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            ParticleEffect_RandomRotationSetup(arg0);
            break;

        case 2:
            Particle_AnimLoopForwardComplete(arg0, 0, 7, 1, 2, 0);
            Particle_ApproachPrimAlpha(arg0, 0x80, 8);
            Particle_ApplyB2B4AndAddAll(arg0);
            break;

        case 3:
            Particle_ClearActiveFlag(arg0);
            break;
    }
}

void ParticleEffect_SmallScatter(ParticleEffectInstance* arg0) {
    Vec3s sp28;
    s16 sp26 = Particle_GetShortCF(arg0);

    Particle_GetShortAC(arg0);
    sp28.x = func_81400B28(0x1000, -0x2000);
    sp28.y = func_81400B28(0x1000, 0x8000);
    sp28.z = 0;
    Particle_AddRotationDeltaVec(arg0, sp28);
    Particle_SetScaleFactor1(arg0, 0.05f);
    Particle_SetScaleFactor2(arg0, 0.25f);
    Particle_SetScaleFactor3(arg0, 0.02f);
    SetPrimEnvColorFromPair(arg0, sp26);
    Particle_SetTimerA6(arg0, 8);
    Particle_SetSpeed(arg0, (RandomMod(8) * 0.25f) + 2.0f);
    Particle_SetVelocityFromRotationXY(arg0);
    Particle_IncrementState(arg0);
}

void ParticleEffect_SmallScatterHandler(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            ParticleEffect_SmallScatter(arg0);
            break;

        case 2:
            Particle_AnimLoopForwardComplete(arg0, 1, 7, 1, 2, 0);
            if (Particle_DecrementTimerA6ToZero(arg0) != 0) {
                Particle_ApproachPrimAlpha(arg0, 0x64, 0x10);
            }
            break;

        case 3:
            Particle_ClearActiveFlag(arg0);
            break;
    }

    if (Particle_IsActive(arg0) != 0) {
        Particle_ApproachScaleFactor2(arg0);
        Particle_DecrementAccelerationYClamp(arg0, -1.5f, 0.1f);
        Particle_AddVelocityFromTarget(arg0);
    }
}

void ParticleEffect_DirectionalInit(ParticleEffectInstance* arg0) {
    switch (arg0->unk_A6) {
        case 0:
            Particle_SetVelocityScaledXYZ(arg0, 0.0f, -5.0f, -10.0f);
            break;

        case 1:
            Particle_SetVelocityScaledXYZ(arg0, 0.0f, 8.0f, 8.0f);
            break;

        case 2:
            Particle_SetVelocityScaledXYZ(arg0, 0.0f, 3.0f, 0.0f);
            break;

        case 3:
            Particle_SetVelocityScaledXYZ(arg0, 0.0f, -3.0f, 5.0f);
            break;
    }

    Particle_SetTimerA6(arg0, 6);
    Particle_IncrementState(arg0);
}

void func_84355330(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            ParticleEffect_DirectionalInit(arg0);
            break;

        case 2:
            ParticleNode_CreateMultiple(arg0, ParticleEffect_SmallScatterHandler, &gParticleEffectData[0x50], 1);
            Particle_DecrementTimerA6ToZeroWithCallback(arg0);
            break;

        case 3:
            Particle_ClearActiveFlag(arg0);
            break;
    }
}

void func_843553B4(void) {
}

void func_843553BC(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            ParticleEffect_BasicSetup(arg0);
            break;

        case 2:
            Particle_AnimLoopForwardComplete(arg0, 1, 7, 1, 2, 0);
            if (Particle_DecrementTimerA6ToZero(arg0) != 0) {
                Particle_ApproachPrimAlpha(arg0, 0x64, 0x10);
            }
            break;

        case 3:
            Particle_ClearActiveFlag(arg0);
            break;
    }

    if (Particle_IsActive(arg0) != 0) {
        Particle_ApproachScaleFactor2(arg0);
        Particle_DecrementAccelerationYClamp(arg0, -1.5f, 0.2f);
        Particle_AddVelocityFromTarget(arg0);
    }
}

void ParticleEffect_FadeAndScale(ParticleEffectInstance* arg0) {
    s16 sp26 = Particle_GetShortCF(arg0);

    Particle_SetScaleFactor1(arg0, 0.2f);
    Particle_AddVelocityYScaled(arg0, 5.0f);
    SetPrimEnvColorFromPair(arg0, sp26);
    Particle_SetPrimAlpha(arg0, 0x40);
    Particle_IncrementState(arg0);
}

void ParticleEffect_SpeedAndAlpha(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            ParticleEffect_FadeAndScale(arg0);
            break;

        case 2:
            Particle_ApproachScaleFactor1(arg0, 8.0f, 0.1f);
            Particle_ApproachPrimAlpha(arg0, 0xFF, 4);
            break;

        case 3:
            Particle_ResetState(arg0);
            break;
    }
}

void ParticleEffect_RotationAndColor(ParticleEffectInstance* arg0) {
    s16 sp26 = Particle_GetShortAC(arg0);
    s16 sp24 = Particle_GetShortCF(arg0);

    Particle_SetSpeed(arg0, 100.0f);
    Particle_SetAcceleration(arg0, 3.0f);
    Particle_SetAccelerationYScaled(arg0, 2.0f);
    Particle_SetRotationDeltaY(arg0, 0x400);
    SetPrimEnvColorFromPair(arg0, sp24);
    Particle_SetScaleFactor1(arg0, 0.5f - (sp26 * 0.04f));
    Particle_SetPrimAlpha(arg0, (0xFF - (sp26 * 0x10)) & 0xFF);
    Particle_SetTimerA6(arg0, sp26 + 1);
    Particle_DisableFlag4(arg0);
    Particle_IncrementState(arg0);
}

void ParticleEffect_ConditionalUpdate(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            ParticleEffect_RotationAndColor(arg0);
            break;

        case 2:
            if (Particle_DecrementTimerA6ToZeroWithCallback(arg0) != 0) {
                Particle_EnableFlag4(arg0);
                Particle_SetTimerA6(arg0, 0x18);
            }
            break;

        case 3:
            if ((Particle_DecrementTimerA6ToZero(arg0) != 0) && (Particle_ApproachScaleFactor1(arg0, 0.0f, 0.05f) != 0)) {
                Particle_IncrementState(arg0);
            }
            break;

        case 4:
            Particle_ResetState(arg0);
            break;
    }

    if (Particle_HasFlag4(arg0) != 0) {
        Particle_ApproachSpeed(arg0, 0.0f);
        Particle_AddRotationDeltaY(arg0);
        Particle_ApplyB278AndCopyXZ(arg0);
        Particle_ApproachVelocityY(arg0, 0.0f);
        Particle_ApproachEnvB(arg0, 0xFF, 4);
        Particle_ApproachEnvG(arg0, 0xFF, 4);
    }
}

void ParticleEffect_RandomRotation(ParticleEffectInstance* arg0) {
    Particle_GetShortAC(arg0);
    Particle_SetRotationY(arg0, RandomMod(0x10000));
    Particle_SetVelocityY(arg0, func_81400B4C(0x28, 0x28));
    ParticleNode_CreateMultiple(arg0, ParticleEffect_ConditionalUpdate, &gParticleEffectData[0x44], 5);
    Particle_IncrementState(arg0);
}

void func_8435581C(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            ParticleEffect_RandomRotation(arg0);
            break;

        case 2:
            Particle_ResetState(arg0);
            break;
    }
}

void ParticleEffect_PrimColorAndEnv(ParticleEffectInstance* arg0) {
    s16 sp26 = Particle_GetShortAC(arg0);

    Particle_SetPrimColor(arg0, 0xDC, 0xFF, 0xFF);
    SetEnvColorFromPalette(arg0, 0x35);
    arg0->unk_1C = (sp26 * 0.05f) + 0.5f;
    Particle_SetSpeed(arg0, 2.0f);
    Particle_SetPrimAlpha(arg0, (0xFF - (sp26 << 5)) & 0xFF);
    Particle_SetTimerA6(arg0, sp26 + 1);
    Particle_SetParamC7(arg0, 0xF);
    Particle_DisableFlag4(arg0);
    Particle_IncrementState(arg0);
}

void ParticleEffect_ComplexSequence(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            ParticleEffect_PrimColorAndEnv(arg0);
            break;

        case 2:
            if (Particle_DecrementTimerA6ToZeroWithCallback(arg0) != 0) {
                Particle_EnableFlag4(arg0);
                Particle_ComputeLifespan(&arg0->unk_7C, arg0->unk_50, gCameraLookAtPos, arg0->unk_74);
            }
            break;

        case 3:
            Particle_ScaleAccelerationVector(arg0, 1.5f);
            if (Particle_ProcessTimer80(arg0, 4) != 0) {
                Particle_SetSpeed(arg0, 10.0f);
                Particle_SetTimerA6(arg0, Particle_ComputeLifespan(&arg0->unk_7C, arg0->unk_50, gCameraLookAtPos, arg0->unk_74));
            }
            break;

        case 4:
            Particle_ApproachScaleFactor1(arg0, 0.1f, 0.02f);
            Particle_ApproachPrimR(arg0, 0xFF, 4);
            Particle_ApproachEnvR(arg0, 0xFF, 8);
            Particle_ApproachEnvG(arg0, 0xFF, 8);
            Particle_DecrementTimerA6ToZeroWithCallback(arg0);
            break;

        case 5:
            Particle_ResetState(arg0);
            break;
    }

    if (Particle_HasFlag4(arg0) != 0) {
        Particle_AddVelocityFromTarget(arg0);
    }
}

void ParticleEffect_Sparkle(ParticleEffectInstance* arg0) {
    s16 sp26 = Particle_GetShortAC(arg0);

    Particle_SetScaleFactor1(arg0, 0.5f);
    Particle_ScaleVelocity(arg0, 100.0f);
    Particle_SetTimerA6(arg0, sp26 + 1);
    SetPrimColorFromPalette(arg0, 0xA);
    SetEnvColorFromPalette(arg0, 0x35);
    Particle_DisableFlag4(arg0);
    Particle_IncrementState(arg0);
}

void func_84355B8C(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            ParticleEffect_Sparkle(arg0);
            break;

        case 2:
            if (Particle_DecrementTimerA6ToZeroWithCallback(arg0) != 0) {
                Particle_EnableFlag4(arg0);
            }
            break;

        case 3:
            if (Particle_AnimLoopForwardComplete(arg0, 0, 0xF, 2, 1, 0) != 0) {
                ParticleNode_CreateMultiple(arg0, ParticleEffect_ComplexSequence, &gParticleEffectData[0x26], 5);
            }
            break;

        case 4:
            Particle_ResetState(arg0);
            break;
    }
}

void ParticleEffect_ExplosionScale(ParticleEffectInstance* arg0) {
    f32 sp24;
    s16 sp22 = Particle_GetShortAC(arg0);

    sp24 = (sp22 + 15.0f) / 20.0f;
    if (sp24 >= 1.0f) {
        sp24 = 1.0f;
    }

    Particle_SetScaleFactor1(arg0, sp24);
    Particle_SetScaleFactor2(arg0, 8.0f * sp24);
    Particle_SetScaleFactor3(arg0, 0.35f * sp24);
    Particle_AddVelocityYScaled(arg0, 10.0f);
    Particle_SetParamC7(arg0, 0xF);
    SetPrimColorFromPalette(arg0, 0xA);
    SetEnvColorFromPalette(arg0, 0x35);
    Particle_SetPrimAlpha(arg0, 0xFF);
    Particle_SetTimerA6(arg0, sp22 * 8);
    Particle_DisableFlag4(arg0);
    Particle_IncrementState(arg0);
}

void ParticleEffect_ExplosionVariant(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            ParticleEffect_ExplosionScale(arg0);
            break;

        case 2:
            if (Particle_DecrementTimerA6ToZeroWithCallback(arg0) != 0) {
                Particle_EnableFlag4(arg0);
            }
            break;

        case 3:
            Particle_ProcessTimer80(arg0, 0xC);
            break;

        case 4:
            Particle_ApproachPrimAlphaWithCallback(arg0, 0x20, 0x20);
            break;

        case 5:
            Particle_ResetState(arg0);
            break;
    }

    if (Particle_HasFlag4(arg0) != 0) {
        Particle_ApproachScaleFactor2(arg0);
        Particle_ApproachEnvG(arg0, 0, 0x10);
        Particle_ApproachEnvB(arg0, 0, 8);
    }
}

void ParticleEffect_InitializeGroup(void) {
    func_8432EC28(0, ParticleEffect_FireworkMain, &gParticleEffectData[0x34], 0, 1, 0x11, 7, 0, 7);
    func_8432EC28(2, func_84351984, &gParticleEffectData[0x3D], 0, 8, 0x11, 7, 1, 0);
}

void ParticleEffect_ConfigB(void) {
    func_8432EC28(0, ParticleEffect_FireworkMain, &gParticleEffectData[0x34], 0, 1, 0x11, 7, 0, 6);
    func_8432EC28(2, func_84351984, &gParticleEffectData[0x3D], 0, 8, 0x11, 7, 1, 0);
}

void ParticleEffect_ConfigA(void) {
    func_8432EC28(0, ParticleEffect_FireworkMain, &gParticleEffectData[0x34], 0, 1, 0x11, 9, 0, 8);
    func_8432EC28(2, func_84351984, &gParticleEffectData[0x3D], 0, 8, 0x11, 9, 2, 0);
}

void ParticleEffect_ConfigVariantA(void) {
    func_8432EC28(0, ParticleEffect_FireworkMain, &gParticleEffectData[0x34], 0, 1, 0x11, 9, 0, 6);
    func_8432EC28(2, func_84351984, &gParticleEffectData[0x3D], 0, 8, 0x11, 9, 0, 0);
}

void ParticleEffect_ConfigVariantB(void) {
    func_8432EC28(0, ParticleEffect_FireworkMain, &gParticleEffectData[0x34], 0, 1, 0x11, 9, 0, 0x10);
    func_8432EC28(2, func_84351984, &gParticleEffectData[0x3D], 0, 8, 0x11, 9, 0, 0);
}

void ParticleEffect_SpecialSetupA(void) {
    func_8432EC28(0, ParticleEffect_ModeSpecificHandler, &gParticleEffectData[0x34], 0, 1, 0x11, 9, 3, 0);
}

void ParticleEffect_SpecialSetupB(void) {
    func_8432EC28(0, ParticleEffect_ModeSpecificHandler, &gParticleEffectData[0x34], 0, 1, 0x11, 9, 4, 0);
}

void ParticleEffect_SpecialSetupC(void) {
    func_8432EC28(0, ParticleEffect_FireworkMain, &gParticleEffectData[0x34], 0, 7, 0x11, 9, 1, 0xC);
}

void ParticleEffect_TextureSetup(void) {
    s32 temp_s1 = gParticleTexture_Default & 0xFF;

    func_8432ECA0(0, 8, 6, func_8435226C, &gParticleEffectData[0x42], 0, 8, 0x11, temp_s1, 0x18, 2);
    func_8432ECA0(1, 8, 6, func_8435226C, &gParticleEffectData[0x42], 0, 8, 0x11, temp_s1, 0x18, 2);
    func_8432ECA0(2, 8, 6, func_8435226C, &gParticleEffectData[0x42], 0, 8, 0x11, temp_s1, 0x18, 2);
    func_8432ECA0(4, 8, 6, func_8435226C, &gParticleEffectData[0x42], 0, 8, 0x11, temp_s1, 0x18, 2);
    func_8432ECA0(0, 6, 0xC, func_84350FC0, &gParticleEffectData[0x4A], 0, 2, 0x11, temp_s1, 1, 0);
    func_8432ECA0(1, 6, 0xA, func_84350FC0, &gParticleEffectData[0x4A], 0, 2, 0x11, temp_s1, 1, 0);
}

void ParticleEffect_ModeSetup(void) {
    UNUSED s32 pad;

    func_8432EC28(0, ParticleEffect_FireworkMain, &gParticleEffectData[0x34], 0, 1, 0x11, 9, 3, 5);
    func_8432EC28(2, func_84350FC0, &gParticleEffectData[0x3D], 0, 8, 0x10, 0x64, 0, 0);
    func_8432EC28(3, func_84350FC0, &gParticleEffectData[0x3D], 0, 8, 0x10, 0x64, 0, 0);
    func_8432EC28(4, func_8435226C, &gParticleEffectData[0x42], 0, 8, 9, 0, 0x18, 0);
    func_8432EC28(8, func_8435226C, &gParticleEffectData[0x42], 0, 4, 9, 0, 0x18, 0);
    func_8432EC28(0xC, func_8435226C, &gParticleEffectData[0x42], 0, 4, 9, 0, 0x18, 0);
    func_8432F2C8(0, 0x35, 0xE0, 0, 0x20);
}

void ParticleEffect_CollisionSetup(void) {
    func_8432EC28(0, ParticleEffect_FireworkMain, &gParticleEffectData[0x34], 0, 1, 0x11, 9, 3, 5);
    func_8432EC28(4, ParticleEffect_SparkleHandler, &gParticleEffectData[0x40], 0, 1, 0x10, 0x64, 0, 0);
    func_8432ECA0(0, 4, 5, func_8433CCFC, &gParticleEffectData[0x11], 8, 4, 2, 0, 0, 0);
    func_8432EE5C(0, 0, 0x40, 0xA, 0xC8);
    func_8432F2C8(0, 0x19, 0xE1, 0, 0x40);
}

void ParticleEffect_TextureAssign(void) {
    func_8432EC28(0, func_84351144, &gParticleEffectData[0x34], 0, 5, 0x11, gParticleTexture_Default, 0, 0);
}

void ParticleEffect_AdditionalSetupA(void) {
    func_8432ECA0(0, 3, 2, func_84350DAC, &gParticleEffectData[0x3F], 0, 0x10, 0xA, 0, 0x11, 0);
    func_8432ECA0(0x28, 3, 2, func_84350DAC, &gParticleEffectData[0x3F], 0, 0x10, 0xA, 0, 0x11, 0);
}

void ParticleEffect_AdditionalSetupB(void) {
    func_8432EC28(0, ParticleEffect_FireworkMain2, &gParticleEffectData[0x34], 0, 1, 0x11, 9, 0, 0);
    func_8432EC28(0, func_843512AC, &gParticleEffectData[0x36], 0, 1, 0xA, 0, 0, 0);
    func_8432ECA0(4, 3, 2, func_84350DAC, &gParticleEffectData[0x3F], 0, 0x10, 0xA, 0, 0x11, 0);
}

void ParticleEffect_CombinedSetupA(void) {
    func_8432EC28(0, ParticleEffect_FireworkMain2, &gParticleEffectData[0x34], 0, 5, 0x11, 0x64, 9, 0);
    func_8432EC28(8, func_843512AC, &gParticleEffectData[0x36], 0, 1, 0xA, 0, 0, 0);
    func_8432ECA0(0xC, 3, 2, func_84350DAC, &gParticleEffectData[0x3F], 0, 0x10, 0xA, 0, 0x11, 0);
}

void ParticleEffect_CombinedSetupB(void) {
    func_8432EC28(0, ParticleEffect_FireworkMain2, &gParticleEffectData[0x34], 0, 5, 0xA, 0, 0xA, 0);
    func_8432EC28(8, func_843512AC, &gParticleEffectData[0x36], 0, 1, 0xA, 0, 0, 0);
    func_8432ECA0(0xC, 3, 2, func_84350DAC, &gParticleEffectData[0x3F], 0, 0x10, 0xA, 0, 0x11, 0);
}

void ParticleEffect_SimpleSetup(void) {
    func_8432EC28(0, ParticleEffect_FireworkMain2, &gParticleEffectData[0x34], 0, 7, 0xA, 0, 0xB, 0);
}

void ParticleEffect_SmallSetup(void) {
    func_8432ED0C(0, 8, 0x22);
}

void ParticleEffect_MultiHandleSetup(void) {
    func_8432EC28(0xC, func_8435226C, &gParticleEffectData[0x42], 0, 8, 9, 0, 0x17, 1);
    func_8432EC28(0x12, func_8435226C, &gParticleEffectData[0x42], 0, 0xA, 9, 0, 0x17, 1);
    func_8432EC28(0x20, func_8435226C, &gParticleEffectData[0x42], 0, 5, 9, 0, 0x17, 1);
    func_8432EC28(0, func_84351D20, &gParticleDefaultCallback, 0, 2, 9, 0, 0, 0);
    func_8432EC28(3, func_84351D20, &gParticleDefaultCallback, 0, 2, 9, 0, 0, 0);
    func_8432EC28(5, func_84351D20, &gParticleDefaultCallback, 0, 2, 9, 0, 0, 0);
    func_8432EC28(8, func_84351D20, &gParticleDefaultCallback, 0, 2, 9, 0, 0, 0);
}

void ParticleEffect_ExtraNodeSetup(void) {
    func_8432ECA0(0, 3, 2, func_84350DAC, &gParticleEffectData[0x3F], 0, 0x10, 0xA, 0, 0x11, 0);
}

void ParticleEffect_TextureNodeSetup(void) {
    func_8432ECA0(0, 3, 2, func_8435043C, &gParticleEffectData[0x4A], 0, 3, 0x11, gParticleTexture_Default, 0x11, 0);
    func_8432ECA0(0, 4, 2, func_84350634, &gParticleEffectData[0x4A], 0, 2, 0x11, gParticleTexture_Default, 0x11, 0);
}

void ParticleEffect_HandleStateSetup(void) {
    UNUSED s32 pad;

    func_8432EC28(0, Particle_HandleState, &gParticleEffectData[0x29], 0, 1, 0x10, gParticleTexture_Default, 0xB, 0);
    func_8432EC28(4, Particle_HandleState, &gParticleEffectData[0x29], 0, 1, 0x10, gParticleTexture_Default, 0xB, 1);
    func_8432EC28(0xA, Particle_HandleState, &gParticleEffectData[0x29], 0, 1, 0x10, gParticleTexture_Default, 0xB, 2);
    func_8432EC28(0x1E, Particle_HandleCollisionResponse, &gParticleEffectData[0x41], 0, 1, 0x18, 0, 0xF, 0);
    func_8432EDE8(0x23, 0, 0x10, 0x14);
}

void ParticleEffect_HandleCollisionSetup(void) {
    func_8432EE5C(0, 2, 0x10, 0x14, 0xFF);
    func_8432EC28(3, Particle_HandleState_Directional, &gParticleEffectData[0x2A], 0, 1, 0x10, gParticleTexture_Default, 0x10, 2);
    func_8432EC28(3, Particle_HandleCollisionResponse_ExplosionAlt, &gParticleEffectData[0x41], 0, 1, 0x18, 0, 0xF, 0);
}

void ParticleEffect_DynamicStateSetup(void) {
    s16 tmp = func_843081BC(gParticleEffectData_42);

    if (tmp == 0x7B) {
        ParticleEffect_HandleStateSetup();
        return;
    }

    func_8432EC28(0, Particle_HandleState, &gParticleEffectData[0x29], 0, 3, 0x10, gParticleTexture_Default, 0xB, 0);
    func_8432EC28(4, Particle_HandleState, &gParticleEffectData[0x29], 0, 3, 0x10, gParticleTexture_Default, 0xB, 1);
    func_8432EC28(0xA, Particle_HandleState, &gParticleEffectData[0x29], 0, 3, 0x10, gParticleTexture_Default, 0xB, 2);
    func_8432EC28(0x1E, Particle_HandleCollisionResponse, &gParticleEffectData[0x28], 0, 1, 0x18, 0, 0xF, 0);
    func_8432EDE8(0x23, 0, 0x10, 0x14);
}

void ParticleEffect_DynamicCollisionSetup(void) {
    s16 tmp = func_843081BC(gParticleEffectData_42);

    if (tmp == 0x7B) {
        ParticleEffect_HandleCollisionSetup();
        return;
    }

    func_8432EE5C(0, 2, 0x10, 0x14, 0xFF);
    func_8432EC28(3, Particle_HandleState_Directional, &gParticleEffectData[0x2A], 0, 1, 0x10, gParticleTexture_Default, 0x10, 0);
    func_8432EC28(3, Particle_HandleState_Directional, &gParticleEffectData[0x2A], 0, 1, 0x10, gParticleTexture_Default, 0x10, 1);
    func_8432EC28(3, Particle_HandleState_Directional, &gParticleEffectData[0x2A], 0, 1, 0x10, gParticleTexture_Default, 0x10, 2);
    func_8432EC28(3, Particle_HandleCollisionResponse_ExplosionAlt, &gParticleEffectData[0x28], 0, 1, 0x18, 0, 0xF, 0);
}

void ParticleEffect_ConditionalStateSetup(void) {
    UNUSED s16 pad;
    s16 sp3C = func_843081BC(gParticleEffectData_42);
    s16 sp3A = 3;

    if (sp3C == 0x7B) {
        sp3A = 1;
    }

    func_8432EC28(0, Particle_HandleState, &gParticleEffectData[0x29], 0, sp3A, 0x10, gParticleTexture_Default, 0xB, 0);
    func_8432EC28(4, Particle_HandleState, &gParticleEffectData[0x29], 0, sp3A, 0x10, gParticleTexture_Default, 0xB, 1);
    func_8432EC28(0xA, Particle_HandleState, &gParticleEffectData[0x29], 0, sp3A, 0x10, gParticleTexture_Default, 0xB, 2);

    if (sp3C == 0x7B) {
        func_8432EC28(0x1E, Particle_HandleCollisionResponse, &gParticleEffectData[0x41], 0, 1, 0x18, 0, 0xF, 0);
    } else {
        func_8432EC28(0x1E, Particle_HandleCollisionResponse, &gParticleEffectData[0x28], 0, 1, 0x18, 0, 0xF, 0);
    }
    func_8432EDE8(0x23, 0, 0x10, 0x14);
}

void ParticleEffect_CollisionResponseSwitch(void) {
    s16 tmp = func_843081BC(gParticleEffectData_42);

    if (tmp == 0x7B) {
        func_8432EC28(0, Particle_HandleCollisionResponse, &gParticleEffectData[0x41], 0, 1, 0x18, 0, 0xF, 0);
    } else {
        func_8432EC28(0, Particle_HandleCollisionResponse, &gParticleEffectData[0x28], 0, 1, 0x18, 0, 0xF, 0);
    }
    func_8432EE5C(5, 0, 8, 0x14, 0x80);
}

void ParticleEffect_CollisionAndBurstSetup(void) {
    s16 tmp = func_843081BC(gParticleEffectData_42);

    if (tmp == 0x7B) {
        func_8432EE5C(0, 2, 8, 0x14, 0x80);
        func_8432EC28(3, Particle_HandleState_Directional_ScaleAlt, &gParticleEffectData[0x2A], 0, 1, 0x10, gParticleTexture_Default, 0x10, 2);
        func_8432EC28(3, Particle_HandleCollisionResponse_ExplosionAlt, &gParticleEffectData[0x41], 0, 1, 0x18, 0, 0xF, 0);
    } else {
        func_8432EE5C(0, 2, 8, 0x14, 0x80);
        func_8432EC28(3, Particle_HandleState_Directional_ScaleAlt, &gParticleEffectData[0x2A], 0, 1, 0x10, gParticleTexture_Default, 0x10, 0);
        func_8432EC28(3, Particle_HandleState_Directional_ScaleAlt, &gParticleEffectData[0x2A], 0, 1, 0x10, gParticleTexture_Default, 0x10, 1);
        func_8432EC28(3, Particle_HandleState_Directional_ScaleAlt, &gParticleEffectData[0x2A], 0, 1, 0x10, gParticleTexture_Default, 0x10, 2);
        func_8432EC28(3, Particle_HandleCollisionResponse_ExplosionAlt, &gParticleEffectData[0x28], 0, 1, 0x18, 0, 0xF, 0);
    }
}

void ParticleEffect_StateCollisionSetupA(void) {
    UNUSED s32 pad;

    func_8432EC28(0, Particle_HandleState, &gParticleEffectData[0x29], 0, 1, 0x10, gParticleTexture_Default, 0xD, 0);
    func_8432EC28(4, Particle_HandleState, &gParticleEffectData[0x29], 0, 1, 0x10, gParticleTexture_Default, 0xD, 1);
    func_8432EC28(0xA, Particle_HandleState, &gParticleEffectData[0x29], 0, 1, 0x10, gParticleTexture_Default, 0xD, 2);
    func_8432EC28(0x1E, Particle_HandleCollisionResponse, &gParticleEffectData[0x41], 0, 1, 0x18, 0, 0xD, 1);
    func_8432EDE8(0x23, 0, 0x10, 0x29);
}

void ParticleEffect_StateCollisionSetupB(void) {
    UNUSED s32 pad;

    func_8432EE5C(0, 2, 0x10, 0x29, 0xFF);
    func_8432EC28(3, Particle_HandleState_Directional, &gParticleEffectData[0x2A], 0, 1, 0x10, gParticleTexture_Default, 0xD, 2);
    func_8432EC28(3, Particle_HandleCollisionResponse_ExplosionAlt, &gParticleEffectData[0x41], 0, 1, 0x18, 0, 0xD, 1);
    func_8432ECA0(0, 1, 5, Particle_UpdateBurstState, &gParticleEffectData[0x2B], 0, 2, 0xE, 0, 0, 0);
    func_8432ECA0(0, 1, 5, Particle_UpdateBurstState, &gParticleEffectData[0x2B], 0, 2, 0xE, 0, 0, 0);
    func_8432ECA0(0, 2, 0xF, Particle_UpdateBurstState, &gParticleEffectData[0x2B], 0, 1, 0xE, 0, 0, 0);
}

void ParticleEffect_AdditionalNodeSetup(void) {
    func_8432ECA0(0, 1, 0x24, ParticleEffect_RandomDirectionHandler, &gParticleEffectData[0x46], 0, 1, 0x11, gParticleTexture_Default, 0, 0);
    func_8432EC28(0, ParticleEffect_SmallBurstHandler, &gParticleEffectData[0x40], 0, 1, 0x10, gParticleTexture_Default, 0, 0);
}

void ParticleEffect_SpecialCollisionSetup(void) {
    func_8432EC28(0, Particle_HandleState_Special, &gParticleEffectData[0x29], 0, 6, 0x10, 0x64, 0, 0);
}

void ParticleEffect_SmallNodeSetup(void) {
    func_8432ED0C(0, 8, 0x28);
}

void ParticleEffect_MultiTextureSetup(void) {
    func_8432EC28(0, Particle_HandleState_SpecialColor, &gParticleEffectData[0x29], 0, 8, 0x10, 9, 0, 0);
    func_8432EC28(0x10, Particle_HandleState_SpecialColor, &gParticleEffectData[0x29], 0, 0xA, 0x10, 9, 0, 0);
    func_8432ED0C(0x46, 4, 0xA);
}

void ParticleEffect_SmallNodeSetupB(void) {
    func_8432ED0C(0, 8, 0x17);
}

void ParticleEffect_MultiNodeSetup(void) {
    func_8432EB2C(0x10);
    func_8432EC28(0, Particle_HandleState_SpecialColor, &gParticleEffectData[0x29], 0, 8, 0x10, 9, 1, 0);
    func_8432EC28(0x10, Particle_HandleState_SpecialColor, &gParticleEffectData[0x29], 0, 8, 0x10, 9, 1, 0);
    func_8432EC28(0x20, Particle_HandleState_SpecialColor, &gParticleEffectData[0x29], 0, 8, 0x10, 9, 1, 0);
    func_8432EC28(0x30, Particle_HandleState_SpecialColor, &gParticleEffectData[0x29], 0, 8, 0x10, 9, 1, 0);
}

void ParticleEffect_ModeSpecificSetup(void) {
    switch (GetActionScriptId()) {
        case 0x4D:
            func_8432F344(0, 0x64, 0x3E, 0, 0xA0, 4);
            break;

        case 0x4E:
            func_8432F344(0, 0x64, 0x19, 0, 0xA0, 4);
            break;

        case 0x4F:
            func_8432F344(0, 0x64, 0x2F, 0, 0xA0, 4);
            break;

        case 0x93:
            func_8432F344(0, 0x64, 0x19, 0, 0xA0, 4);
            break;

        case 0x7B:
            func_8432F344(0, 0x64, 0x3E, 0, 0xA0, 4);
            break;

        case 0x8B:
            func_8432F344(0, 0x64, 0x3E, 0, 0xA0, 4);
            break;
    }
    func_8432EC28(0, ParticleEffect_ColorfulBurstHandler, &gParticleEffectData[0x47], 0, 7, 0x10, 0x64, 1, 0);
}

void ParticleEffect_ComplexNodeSetup(void) {
    func_8432ECA0(0, 2, 3, func_84350828, &gParticleEffectData[0x49], 0, 8, 0x11, gParticleTexture_Default, 0, 0);
    func_8432ECA0(0, 3, 2, func_8435043C, &gParticleEffectData[0x47], 0, 6, 0x11, gParticleTexture_Default, 0x31, 0);
    func_8432ECA0(0, 4, 2, func_84350634, &gParticleEffectData[0x47], 0, 4, 0x11, gParticleTexture_Default, 0x31, 0);
}

void ParticleEffect_SimpleNodeSetup(void) {
    func_8432EC28(0, func_84350BE4, &gParticleEffectData[0x49], 0, 5, 0x10, 0x64, 0, 0);
    func_8432EC28(3, func_84350BE4, &gParticleEffectData[0x49], 0, 5, 0x10, 0x64, 0, 0);
    func_8432EC28(0, ParticleEffect_ColorfulBurstHandler, &gParticleEffectData[0x47], 0, 7, 0x10, 0x64, 1, 0);
}

void ParticleEffect_AdvancedModeSetup(void) {
    func_8432F7A0(0, 0xFF, 0x30, 6);
    func_8432F7A0(0x24, 0, 0, 0xFF);
    func_8432F2C8(0, 0x23, 0, 0xFF, 8);
    func_8432EB2C(6);
    func_8432EC28(2, ParticleEffect_SimpleColorHandler, &gParticleEffectData[0x4B], 0, 1, 0xA, 0, 0x2F, 0);
    func_8432ECA0(0, 8, 4, ParticleEffect_RandomSpeedHandler, &gParticleEffectData[0x3D], 0, 3, 9, 0, 0x30, 0);
}

void ParticleEffect_FullSetupA(void) {
    func_8432ED0C(0, 0x20, 6);
    func_8432F2C8(8, 0xA, 0, 0xFF, 0x40);
    func_8432EF40(0xC, 5, 0x10, 0xA);
    func_8432EC28(0xC, ParticleEffect_FireworkMain, &gParticleEffectData[0x34], 0, 4, 9, 0, 0x18, 0xD);
    func_8432EB2C(0x21);
    func_8432EDE8(0, 0, 0x10, 0xA);
    func_8432ED0C(0, 0x10, 0xA);
    func_8432F2C8(0, 0xA, 0xFF, 0, 0x10);
}

void ParticleEffect_FullSetupB(void) {
    func_8432ED0C(0, 0x20, 6);
    func_8432F2C8(8, 0xA, 0, 0xFF, 0x40);
    func_8432EDE8(0, 0, 0x10, 0xA);
    func_8432EB2C(0x21);
    func_8432ED0C(0, 0x10, 0xA);
    func_8432F2C8(0, 0xA, 0xFF, 0, 0x10);
}

void ParticleEffect_FinalSetupA(void) {
    UNUSED s32 pad;

    func_8432F344(0, 1, 0xC, 0, 0xC8, 0x10);
    func_8432ECA0(6, 4, 0xE, ParticleEffect_BasicSetupHandler, &gParticleEffectData[0x3D], 0, 1, 0x11, 7, 0x1A, 0);
    func_8432ECA0(7, 8, 7, ParticleEffect_BasicSetupHandler, &gParticleEffectData[0x3D], 0, 1, 0x11, 7, 0x1A, 0);
    func_8432EC28(0, func_84334154, &gParticleEffectData[0x4F], 0, 0x20, 7, 0, 0, 0);
    ParticleEffect_InitLargeExplosion();
}

void ParticleEffect_FinalSetupB(void) {
    func_8432F344(0, 1, 0xC, 0, 0xC8, 4);
    func_8432ECA0(4, 3, 2, func_84350DAC, &gParticleEffectData[0x3F], 0, 0x10, 0xA, 0, 0x11, 0);
    func_8432ECA0(6, 4, 0xE, ParticleEffect_BasicSetupHandler, &gParticleEffectData[0x3D], 0, 1, 0x11, 7, 0x33, 7);
    func_8432ECA0(7, 8, 7, ParticleEffect_BasicSetupHandler, &gParticleEffectData[0x3D], 0, 1, 0x11, 7, 0x33, 7);
}

void ParticleEffect_FinalSetupC(void) {
    func_8432ED0C(0, 0x20, 6);
    func_8434AC8C();
    func_8432ECA0(8, 3, 2, func_84350DAC, &gParticleEffectData[0x3F], 0, 0x10, 0xA, 0, 0x11, 0);
}

void ParticleEffect_AdditionalNodeA(void) {
    func_8432ECA0(4, 3, 2, func_84350DAC, &gParticleEffectData[0x3F], 0, 0x10, 0xA, 0, 0x11, 0);
}

void ParticleEffect_MultiNodeA(void) {
    func_8432EC28(4, ParticleEffect_BasicSetupHandler, &gParticleEffectData[0x4A], 0, 8, 0xA, 0, 0x33, 1);
    func_8432EC28(5, ParticleEffect_BasicSetupHandler, &gParticleEffectData[0x4A], 0, 8, 0xA, 0, 0x33, 1);
    func_8432EC28(6, ParticleEffect_BasicSetupHandler, &gParticleEffectData[0x4A], 0, 8, 0xA, 0, 0x33, 1);
    func_8432EC28(7, ParticleEffect_BasicSetupHandler, &gParticleEffectData[0x4A], 0, 8, 0xA, 0, 0x33, 1);
    func_8432EC28(8, ParticleEffect_FireworkMain, &gParticleEffectData[0x51], 0, 5, 0x11, 9, 0x17, 0xE);
    func_8432EC28(0x10, ParticleEffect_FireworkMain, &gParticleEffectData[0x51], 0, 5, 0x11, 9, 0x17, 0xE);
}

void ParticleEffect_MultiNodeB(void) {
    func_8432EC28(4, ParticleEffect_BasicSetupHandler, &gParticleEffectData[0x4A], 0, 8, 0xA, 0, 0x33, 1);
    func_8432EC28(5, ParticleEffect_BasicSetupHandler, &gParticleEffectData[0x4A], 0, 8, 0xA, 0, 0x33, 1);
    func_8432EC28(6, ParticleEffect_BasicSetupHandler, &gParticleEffectData[0x4A], 0, 8, 0xA, 0, 0x33, 1);
    func_8432EC28(7, ParticleEffect_BasicSetupHandler, &gParticleEffectData[0x4A], 0, 8, 0xA, 0, 0x33, 1);
    func_8432EC28(8, ParticleEffect_FireworkMain, &gParticleEffectData[0x51], 0, 5, 0x11, 9, 0x17, 0xE);
    func_8432EC28(0x10, ParticleEffect_FireworkMain, &gParticleEffectData[0x51], 0, 5, 0x11, 9, 0x17, 0xE);
}

void ParticleEffect_MultiNodeC(void) {
    func_8432EC28(0, ParticleEffect_BasicSetupHandler, &gParticleEffectData[0x3D], 0, 8, 0xE, 0, 0x33, 2);
    func_8432EC28(0, ParticleEffect_BasicSetupHandler, &gParticleEffectData[0x3D], 0, 2, 0xE, 0, 0x33, 2);
    func_8432EC28(0, ParticleEffect_BasicSetupHandler, &gParticleEffectData[0x3D], 0, 2, 0xE, 0, 0x33, 2);
    func_8432EC28(0, ParticleEffect_BasicSetupHandler, &gParticleEffectData[0x3D], 0, 2, 0xE, 0, 0x33, 2);
    func_8432EC28(4, ParticleEffect_BasicSetupHandler, &gParticleEffectData[0x3D], 0, 8, 0xE, 0, 0x33, 2);
    func_8432EC28(8, ParticleEffect_BasicSetupHandler, &gParticleEffectData[0x3D], 0, 8, 0xE, 0, 0x33, 2);
}

void ParticleEffect_MultiNodeD(void) {
    func_8432F2C8(4, 0xA, 0, 0xFF, 0x40);
    func_8432F2C8(9, 0xA, 0xFF, 0, 0x40);
    func_8432EC28(0, ParticleEffect_BasicSetupHandler, &gParticleEffectData[0x3D], 0, 8, 0xE, 0, 0x33, 2);
    func_8432EC28(1, ParticleEffect_BasicSetupHandler, &gParticleEffectData[0x3D], 0, 8, 0xE, 0, 0x33, 2);
    func_8432EC28(2, ParticleEffect_BasicSetupHandler, &gParticleEffectData[0x3D], 0, 8, 0xE, 0, 0x33, 2);
    func_8432EC28(4, ParticleEffect_BasicSetupHandler, &gParticleEffectData[0x3D], 0, 8, 0xE, 0, 0x33, 2);
    func_8432EC28(4, ParticleEffect_BasicSetupHandler, &gParticleEffectData[0x3D], 0, 8, 0xE, 0, 0x33, 2);
    func_8432EC28(8, ParticleEffect_BasicSetupHandler, &gParticleEffectData[0x3D], 0, 8, 0xE, 0, 0x33, 2);
}

void ParticleEffect_CreateMultipleNodes(s32 arg0) {
    func_8432ECA0(0, 1, 4, func_8435581C, &gParticleDefaultCallback, 0, 1, 2, 0, arg0, 0);
    func_8432ECA0(8, 1, 4, func_8435581C, &gParticleDefaultCallback, 0, 1, 2, 0, arg0, 0);
    func_8432ECA0(0x10, 1, 8, func_8435581C, &gParticleDefaultCallback, 0, 1, 2, 0, arg0, 0);
    func_8432ECA0(0x18, 1, 8, func_8435581C, &gParticleDefaultCallback, 0, 1, 2, 0, arg0, 0);
    func_8432ECA0(0x20, 1, 8, func_8435581C, &gParticleDefaultCallback, 0, 1, 2, 0, arg0, 0);
    func_8432ECA0(0x30, 1, 8, func_8435581C, &gParticleDefaultCallback, 0, 1, 2, 0, arg0, 0);
    func_8432ECA0(0x3C, 1, 8, func_8435581C, &gParticleDefaultCallback, 0, 1, 2, 0, arg0, 0);
}

void ParticleEffect_GroupSetupA(void) {
    func_8432ED0C(0, 8, 6);
    ParticleEffect_CreateMultipleNodes(0xE);
    func_8432ED0C(0x64, 0x20, 0xA);
}

void ParticleEffect_GroupSetupB(void) {
    func_8432ED0C(0, 8, 6);
    ParticleEffect_CreateMultipleNodes(0x17);
    func_8432EC28(0xA, ParticleEffect_SpeedAndAlpha, &gParticleEffectData[0x3C], 0x1A, 1, 5, 0, 0x33, 0);
    func_8432ED0C(0x64, 0x20, 0xA);
}

void ParticleEffect_SimpleGroupSetup(void) {
    func_8432F344(0xA, 1, 0xA, 0, 0xFF, 0x20);
}

void ParticleEffect_ComplexGroupSetup(void) {
    func_8432ED0C(0, 8, 6);
    ParticleEffect_CreateMultipleNodes(0xC);
    func_8432F728(4, 0x32, 0x20, 0xA0);
    func_8432ECA0(4, 8, 5, func_8435226C, &gParticleEffectData[0x42], 0, 8, 9, 0, 0xC, 9);
}

void ParticleEffect_FinalGroupSetup(void) {
    func_8432F2C8(0, 0xA, 0xFF, 0, 0x20);
    func_8432ECA0(4, 2, 2, func_8435226C, &gParticleEffectData[0x42], 0, 8, 9, 0, 0x17, 1);
}
