#include "fragment62.h"

void Particle_WhiteFlashInit(ParticleEffectInstance* arg0) {
    Particle_SetScaleFactor1(arg0, 0.1f);
    Particle_SetPrimColor(arg0, 0xFF, 0xFF, 0xFF);
    Particle_SetEnvColor(arg0, 0x64, 0xC8, 0xFF);
    Particle_SetPrimAlpha(arg0, 0xFF);
    Particle_IncrementState(arg0);
}

void Particle_WhiteFlashUpdate(ParticleEffectInstance* arg0) {
    switch (arg0->updateState) {
        case 1:
            Particle_WhiteFlashInit(arg0);
            break;

        case 2:
            Particle_AnimLoopForwardComplete(arg0, 0, 7, 1, 2, 0);
            Particle_ApproachPrimAlpha(arg0, 0x20, 8);
            break;

        case 3:
            Particle_ClearActiveFlag(arg0);
            break;
    }

    if (Particle_IsActive(arg0) != 0) {
        Particle_ApproachScaleFactor1(arg0, 0.5f, 0.05f);
    }
}

void Particle_WhiteFlashAltInit(ParticleEffectInstance* arg0) {
    Particle_SetScaleFactor1(arg0, 0.1f);
    Particle_SetPrimColor(arg0, 0xFF, 0xFF, 0xFF);
    Particle_SetEnvColor(arg0, 0x64, 0xC8, 0xFF);
    Particle_SetPrimAlpha(arg0, 0xFF);
    Particle_IncrementState(arg0);
}

void Particle_WhiteFlashAltUpdate(ParticleEffectInstance* arg0) {
    if (arg0->updateState == 1) {
        Particle_WhiteFlashAltInit(arg0);
    }

    if (Particle_IsActive(arg0) != 0) {
        Particle_ApproachScaleFactor1(arg0, 0.8f, 0.08f);
    }
}

void Particle_SetWhiteFlashHandler(ParticleEffectInstance* arg0, u8 arg1) {
    switch (arg1) {
        case 1:
            arg0->unk_08 = Particle_WhiteFlashUpdate;
            arg0->unk_0C = &gParticleEffectData[25];
            break;

        case 2:
            arg0->unk_08 = Particle_WhiteFlashAltUpdate;
            arg0->unk_0C = &gParticleEffectData[22];
            break;
    }
}
