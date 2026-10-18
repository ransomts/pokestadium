#include "fragment62.h"
#include "src/math_util.h"

void func_8433CC10(ParticleEffectInstance* arg0) {
    UNUSED s32 pad;
    Vec3s sp2C;

    Particle_GetShortAC(arg0);
    Particle_SetScaleFactor1(arg0, 0.05f);
    sp2C.x = RandomMod(0x8000) - 0x4000;
    sp2C.y = RandomMod(0x10000);
    sp2C.z = RandomMod(0x800) - 0x400;
    Particle_AddRotationDeltaVec(arg0, sp2C);
    Particle_AddComplexDirection(arg0, RandomMod(0xA));
    func_8140A578(arg0, 0x4000);
    SetPrimEnvColorFromPair(arg0, Particle_GetShortCF(arg0));
    Particle_IncrementState(arg0);
}

void ParticleEffect_CollisionHandler(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            func_8433CC10(arg0);
            break;

        case 2:
            Particle_DecrementTimerA6ToZeroWithCallback(arg0);
            break;

        case 3:
            Particle_ApproachPrimAlphaWithCallback(arg0, 0, 0x40);
            break;

        case 4:
            Particle_ResetState(arg0);
            break;
    }

    Particle_ApproachScaleFactor1(arg0, 1.0f, 0.05f);
    Particle_ApplyB568AndAddAll(arg0);
}

void func_8433CDAC(ParticleEffectInstance* arg0) {
    f32 sp1C = 0.0f;

    switch (GetSpecies(arg0->unk_10)) {
        case 0x6:
            sp1C = 15.0f;
            break;

        case 0x73:
            sp1C = 15.0f;
            break;

        case 0x87:
            sp1C = 10.0f;
            break;

        case 0x95:
            sp1C = 10.0f;
            break;

        case 0x1F:
            sp1C = 10.0f;
            break;

        case 0x22:
            sp1C = 10.0f;
            break;

        case 0x71:
            sp1C = 10.0f;
            break;
    }

    Particle_AddVelocityBackward(arg0, sp1C);
    Particle_AddVelocityRight(arg0, 5.0f);
}

void func_8433CEA4(ParticleEffectInstance* arg0) {
    Particle_SetScaleFactor1(arg0, 0.1f);
    Particle_SetSpeed(arg0, 0.0f);
    func_8433CDAC(arg0);
    SetPrimEnvColorFromPair(arg0, 0x17);
    Particle_IncrementState(arg0);
}

void func_8433CEFC(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            func_8433CEA4(arg0);
            break;

        case 2:
            Particle_ApproachScaleFactor1(arg0, 4.0f, 0.5f);
            Particle_DecrementTimerA6ToZeroWithCallback(arg0);
            break;

        case 3:
            Particle_ApproachScaleFactor1(arg0, 0.1f, 0.5f);
            Particle_ApproachPrimAlphaWithCallback(arg0, 0, 0x20);
            break;

        case 4:
            Particle_ResetState(arg0);
            break;
    }
}

void func_8433CFA8(ParticleEffectInstance* arg0) {
    s16 sp2E = Particle_GetShortAC(arg0);
    Vec3s sp28;

    Particle_SetVelocityYScaled(arg0, 15.0f);
    Particle_SetScaleFactor1(arg0, 0.1f);
    Particle_SetSpeed(arg0, 0.0f);
    sp28.x = 0x4000 - RandomMod(0x8000);
    sp28.y = sp2E << 0xD;
    sp28.z = 0;
    Particle_AddRotationDeltaVec(arg0, sp28);
    SetPrimEnvColorFromPair(arg0, Particle_GetShortCF(arg0));
    Particle_DisableFlag4(arg0);
    Particle_IncrementState(arg0);
}

void func_8433D070(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            func_8433CFA8(arg0);
            break;

        case 2:
            if (Particle_ProcessTimer80(arg0, Particle_GetShortAC(arg0)) != 0) {
                Particle_EnableFlag4(arg0);
            }
            break;

        case 3:
            Particle_ApproachScaleFactor1(arg0, 3.0f, 0.1f);
            Particle_DecrementTimerA6ToZeroWithCallback(arg0);
            break;

        case 4:
            Particle_ApproachPrimAlphaWithCallback(arg0, 0, 0x40);
            break;

        case 5:
            Particle_ResetState(arg0);
            break;
    }

    Particle_RotateY(arg0, 0x400);
    Particle_ApplyB2B4AndAddAll(arg0);
}

void func_8433D154(ParticleEffectInstance* arg0) {
    s16 sp2E = Particle_GetShortAC(arg0);
    Vec3s sp28;

    Particle_SetVelocityYScaled(arg0, 15.0f);
    Particle_SetScaleFactor1(arg0, 0.1f);
    Particle_SetSpeed(arg0, MathUtil_Random_ZeroOne());
    sp28.x = 0x3000 - RandomMod(0x6000);
    sp28.y = sp2E << 0xD;
    sp28.z = 0;
    Particle_AddRotationDeltaVec(arg0, sp28);
    SetPrimEnvColorFromPair(arg0, Particle_GetShortCF(arg0));
    Particle_DisableFlag4(arg0);
    Particle_IncrementState(arg0);
}

void func_8433D224(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            func_8433D154(arg0);
            break;

        case 2:
            if (Particle_ProcessTimer80(arg0, Particle_GetShortAC(arg0)) != 0) {
                Particle_EnableFlag4(arg0);
            }
            break;

        case 3:
            Particle_ApproachScaleFactor1(arg0, 3.5f, 0.1f);
            Particle_DecrementTimerA6ToZeroWithCallback(arg0);
            break;

        case 4:
            Particle_ApproachPrimAlphaWithCallback(arg0, 0, 0x40);
            break;

        case 5:
            Particle_ResetState(arg0);
            break;
    }

    Particle_RotateY(arg0, 0x400);
    Particle_ApplyB2B4AndAddAll(arg0);
}

void func_8433D308(ParticleEffectInstance* arg0) {
    Vec3s sp28;

    Particle_GetShortAC(arg0);
    Particle_SetScaleFactor1(arg0, 0.5f);
    Particle_SetSpeed(arg0, 0.0f);
    sp28.x = -0x4000;
    sp28.y = 0;
    sp28.z = (RandomMod(0x10) << 0xB) - 0x4000;
    Particle_AddRotationDeltaVec(arg0, sp28);
    SetPrimEnvColorFromPair(arg0, Particle_GetShortCF(arg0));
    Particle_IncrementState(arg0);
}

void func_8433D3B0(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            func_8433D308(arg0);
            break;

        case 2:
            Particle_ApproachScaleFactor1(arg0, 2.0f, 0.2f);
            Particle_DecrementTimerA6ToZeroWithCallback(arg0);
            break;

        case 3:
            Particle_ApproachPrimAlphaWithCallback(arg0, 0, 0x40);
            break;

        case 4:
            Particle_ResetState(arg0);
            break;
    }
    Particle_ApplyB568AndAddAll(arg0);
}

void func_8433D460(ParticleEffectInstance* arg0) {
    UNUSED s32 pad;
    Vec3s sp2C;

    Particle_GetShortAC(arg0);
    Particle_SetScaleFactor1(arg0, 0.5f);
    Particle_SetScaleFactor2(arg0, (MathUtil_Random_ZeroOne() * 5.0f) + 1.0f);
    Particle_SetScaleFactor3(arg0, 0.2f);
    Particle_SetSpeed(arg0, MathUtil_Random_ZeroOne() * 4.0f);
    sp2C.x = -0x4000;
    sp2C.y = 0;
    sp2C.z = (RandomMod(0x10) << 0xB) - 0x4000;
    Particle_AddRotationDeltaVec(arg0, sp2C);
    SetPrimEnvColorFromPair(arg0, Particle_GetShortCF(arg0));
    Particle_IncrementState(arg0);
}

void func_8433D560(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            func_8433D460(arg0);
            break;

        case 2:
            Particle_ApproachScaleFactor2(arg0);
            Particle_DecrementTimerA6ToZeroWithCallback(arg0);
            break;

        case 3:
            Particle_ApproachPrimAlphaWithCallback(arg0, 0, 0x40);
            break;

        case 4:
            Particle_ResetState(arg0);
            break;
    }

    Particle_ApplyB568AndAddAll(arg0);
}

void func_8433D604(ParticleEffectInstance* arg0) {
    UNUSED s32 pad;
    Vec3s sp2C;
    UNUSED s32 pad2[2];

    Particle_GetShortAC(arg0);
    Particle_SetScaleFactor1(arg0, 0.1f);
    Particle_SetScaleFactor2(arg0, 1.4f);
    Particle_SetScaleFactor3(arg0, 0.1f);
    MathUtil_Random_ZeroOne();
    Particle_SetSpeed(arg0, 0.0f);
    sp2C.x = -0x4000;
    sp2C.y = 0;
    sp2C.z = (RandomMod(0x10) << 0xB) - 0x4000;
    Particle_AddRotationDeltaVec(arg0, sp2C);
    Particle_AddComplexDirection(arg0, 150.0f);
    Particle_AddRotationZ(arg0);
    SetPrimEnvColorFromPair(arg0, Particle_GetShortCF(arg0));
    Particle_IncrementState(arg0);
}

void func_8433D6EC(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            func_8433D604(arg0);
            break;

        case 2:
            Particle_DecrementTimerA6ToZeroWithCallback(arg0);
            break;

        case 3:
            Particle_ApproachPrimAlphaWithCallback(arg0, 0, 0x10);
            break;

        case 4:
            Particle_ResetState(arg0);
            break;
    }

    Particle_ApproachScaleFactor2(arg0);
    Particle_ApplyB568AndAddAll(arg0);
}

void func_8433D790(ParticleEffectInstance* arg0) {
    UNUSED s32 pad;
    Vec3s sp2C;
    UNUSED s32 pad2[2];

    Particle_GetShortAC(arg0);
    Particle_SetScaleFactor1(arg0, 0.1f);
    Particle_SetScaleFactor2(arg0, 1.4f);
    Particle_SetScaleFactor3(arg0, 0.1f);
    MathUtil_Random_ZeroOne();
    Particle_SetSpeed(arg0, 0.0f);
    sp2C.x = -0x4000;
    sp2C.y = 0;
    sp2C.z = 0;
    Particle_AddRotationDeltaVec(arg0, sp2C);
    Particle_AddComplexDirection(arg0, 150.0f);
    Particle_AddRotationZ(arg0);
    SetPrimEnvColorFromPair(arg0, Particle_GetShortCF(arg0));
    Particle_IncrementState(arg0);
}

void func_8433D868(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            func_8433D790(arg0);
            break;

        case 2:
            Particle_DecrementTimerA6ToZeroWithCallback(arg0);
            break;

        case 3:
            Particle_ApproachPrimAlphaWithCallback(arg0, 0, 0x10);
            break;

        case 4:
            Particle_ResetState(arg0);
            break;
    }

    Particle_ApproachScaleFactor2(arg0);
    Particle_ApplyB568AndAddAll(arg0);
}

void func_8433D90C(ParticleEffectInstance* arg0) {
    UNUSED s32 pad;
    Vec3f sp30;
    Vec3s sp28;

    Particle_GetShortAC(arg0);
    Particle_SetScaleFactor1(arg0, 0.1f);
    Particle_SetScaleFactor2(arg0, 2.0f);
    Particle_SetScaleFactor3(arg0, 0.1f);
    sp28.x = 0;
    sp28.y = 0;
    sp28.z = -0x8000;
    Particle_AddRotationDeltaVec(arg0, sp28);
    sp30.x = RandomMod(0x64) + -50.0f;
    sp30.y = 200.0f;
    sp30.z = RandomMod(0x64) + -50.0f;
    Particle_AddVelocityScaledVec(arg0, sp30);
    SetPrimEnvColorFromPair(arg0, Particle_GetShortCF(arg0));
    Particle_IncrementState(arg0);
}

void func_8433DA54(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            func_8433D90C(arg0);
            break;

        case 2:
            Particle_DecrementTimerA6ToZeroWithCallback(arg0);
            break;

        case 3:
            Particle_ApproachPrimAlphaWithCallback(arg0, 0, 0x40);
            break;

        case 4:
            Particle_ResetState(arg0);
            break;
    }

    Particle_ApproachScaleFactor2(arg0);
    Particle_ApplyB568AndAddAll(arg0);
}

void func_8433DAF8(ParticleEffectInstance* arg0) {
    UNUSED s32 pad[4];
    Vec3s sp28;

    Particle_GetShortAC(arg0);
    Particle_SetScaleFactor1(arg0, 0.1f);
    Particle_SetScaleFactor2(arg0, 2.0f);
    Particle_SetScaleFactor3(arg0, 0.1f);
    sp28.x = -0x1000 - RandomMod(0x6000);
    sp28.y = RandomMod(0x10000);
    sp28.z = RandomMod(0x800) - 0x400;
    Particle_AddRotationDeltaVec(arg0, sp28);
    Particle_AddComplexDirection(arg0, 200.0f);
    func_8140A578(arg0, -0x4000);
    SetPrimEnvColorFromPair(arg0, Particle_GetShortCF(arg0));
    Particle_IncrementState(arg0);
}

void func_8433DBDC(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            func_8433DAF8(arg0);
            break;

        case 2:
            Particle_DecrementTimerA6ToZeroWithCallback(arg0);
            break;

        case 3:
            Particle_ApproachPrimAlphaWithCallback(arg0, 0, 0x40);
            break;

        case 4:
            Particle_ResetState(arg0);
            break;
    }

    Particle_ApproachScaleFactor2(arg0);
    Particle_ApplyB568AndAddAll(arg0);
}

void func_8433DC80(void) {
    ParticleDef_CreateNullType17(0x64, 1);
    ParticleDef_CreateDefault(0, 0x20, 3);
    ParticleDef_CreateFull(0, 3, 8, ParticleEffect_CollisionHandler, &gParticleEffectData[0x11], 8, 4, 2, 0, 0x25, 0);
    ParticleSystem_AddSpawnOffset(0x19);
    ParticleDef_CreateQuick(0, func_8433CEFC, &gParticleEffectData[0x15], 0xE, 1, 2, 0, 0x25, 0);
    ParticleDef_CreateQuick(0, func_8433CEFC, &gParticleEffectData[0x16], 0xE, 1, 2, 0, 0x25, 0);
    ParticleDef_CreateBC20CDAlt(8, 2, 8, 0xA, 0xFF);
    ParticleDef_CreateFull(8, 4, 2, func_8433D070, &gParticleEffectData[0xF], 0x14, 4, 7, 0, 0x25, 0);
    ParticleDef_CreateFull(8, 4, 2, func_8433D224, &gParticleEffectData[0xF], 0x14, 4, 7, 0, 0x25, 0);
    ParticleDef_CreateFull(8, 4, 2, func_8433D560, &gParticleEffectData[0x13], 0x14, 4, 7, 0, 0x25, 0);
    ParticleDef_CreateFull(8, 4, 2, func_8433D3B0, &gParticleEffectData[0x13], 0x14, 4, 7, 0, 0x25, 0);
}

void func_8433DECC(void) {
    ParticleDef_CreateBC20CDAlt(0x2C, 4, 0x10, 0xA, 0xFF);
    ParticleDef_CreateDefault(0x30, 0x20, 0xA);
    ParticleDef_CreateFull(0, 8, 5, func_8433D3B0, &gParticleEffectData[0x12], 8, 3, 3, 0, 0x25, 0);
    ParticleDef_CreateFull(0, 4, 2, func_8433D070, &gParticleEffectData[0xF], 0x14, 4, 3, 0, 0x25, 0);
    ParticleDef_CreateFull(0, 4, 2, func_8433D224, &gParticleEffectData[0xF], 0x14, 4, 3, 0, 0x25, 0);
}

void func_8433DFF4(void) {
    ParticleDef_CreateBC20CDAlt(0, 4, 8, 0xA, 0xC8);
    ParticleDef_CreateDefault(0x30, 0x20, 0xA);
    ParticleDef_CreateFull(0, 8, 5, func_8433D3B0, &gParticleEffectData[0x12], 8, 3, 3, 0, 0x25, 0);
    ParticleDef_CreateFull(0, 4, 2, func_8433D070, &gParticleEffectData[0xF], 0x14, 4, 3, 0, 0x25, 0);
    ParticleDef_CreateFull(0, 4, 2, func_8433D224, &gParticleEffectData[0xF], 0x14, 4, 3, 0, 0x25, 0);
    ParticleEffect_TriggerEffect();
}

void func_8433E124(void) {
    ParticleDef_CreateNullType17(0x64, 1);
    ParticleDef_CreateDefault(0, 0x10, 3);
    ParticleDef_CreateFull(0, 8, 3, func_8433D6EC, &gParticleEffectData[0x14], 2, 1, 2, 0, 0x25, 0);
    ParticleDef_CreateFull(0, 5, 5, func_8433D6EC, &gParticleEffectData[0x13], 2, 1, 2, 0, 0x25, 0);
    ParticleSystem_AddSpawnOffset(0x23);
    ParticleDef_CreateBC20CD(8, 4, 8, 0xA);
    ParticleDef_CreateFull(0, 4, 2, func_8433D560, &gParticleEffectData[0x13], 0x14, 4, 2, 0, 0x25, 0);
    ParticleDef_CreateFull(0, 5, 2, func_8433D3B0, &gParticleEffectData[0x13], 0x14, 4, 2, 0, 0x25, 0);
    ParticleDef_CreateFull(0, 6, 2, func_8433D070, &gParticleEffectData[0xF], 0x14, 2, 1, 0, 0x25, 0);
    ParticleDef_CreateFull(0, 4, 2, func_8433D224, &gParticleEffectData[0xF], 0x14, 2, 1, 0, 0x25, 0);
}

void func_8433E33C(void) {
    ParticleDef_CreateBC20CD(0x22, 4, 0x10, 0xA);
    ParticleDef_CreateDefault(0, 0x20, 3);
    ParticleDef_CreateDefault(0x30, 0x20, 0xA);
    ParticleDef_CreateFull(0, 0xA, 2, func_8433DA54, &gParticleEffectData[0x10], 0xC, 1, 3, 0, 0x25, 0);
    ParticleDef_CreateFull(0, 5, 3, func_8433DBDC, &gParticleEffectData[0x10], 0xC, 2, 3, 0, 0x25, 0);
    ParticleDef_CreateFull(0, 8, 2, func_8433D6EC, &gParticleEffectData[0x13], 0xC, 3, 3, 0, 0x25, 0);
}

void func_8433E46C(void) {
    ParticleDef_CreateFull(0, 4, 5, ParticleEffect_CollisionHandler, &gParticleEffectData[0x11], 8, 4, 0x10, gParticleTexture_Default, 0x25, 0);
    ParticleDef_CreateFull(0, 1, 0x24, ParticleEffect_RandomDirectionHandler2, &gParticleEffectData[0x15], 0, 1, 0x11, gParticleTexture_Default, 0, 0);
}

void func_8433E524(void) {
    ParticleDef_CreateFull(8, 4, 2, func_8433D560, &gParticleEffectData[0x13], 0x14, 4, 7, 0, 0x2C, 0);
    ParticleDef_CreateFull(8, 4, 2, func_8433D3B0, &gParticleEffectData[0x13], 0x14, 3, 7, 0, 0xF, 0);
    ParticleDef_CreateQuick(8, func_8433D070, &gParticleEffectData[0xF], 0x14, 1, 7, 0, 0x2C, 0);
    ParticleDef_CreateQuick(8, func_8433D224, &gParticleEffectData[0xF], 0x14, 1, 7, 0, 0xF, 0);
}
