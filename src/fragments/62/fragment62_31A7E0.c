#include "fragment62.h"

void Particle_WhiteFlashInit(unk_D_8140E720* arg0) {
    func_8140B938(arg0, 0.1f);
    Particle_SetPrimColor(arg0, 0xFF, 0xFF, 0xFF);
    func_8140BB74(arg0, 0x64, 0xC8, 0xFF);
    func_8140BC20(arg0, 0xFF);
    func_814081BC(arg0);
}

void Particle_WhiteFlashUpdate(unk_D_8140E720* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            Particle_WhiteFlashInit(arg0);
            break;

        case 2:
            func_814084D8(arg0, 0, 7, 1, 2, 0);
            func_8140BC2C(arg0, 0x20, 8);
            break;

        case 3:
            func_81408150(arg0);
            break;
    }

    if (func_8140819C(arg0) != 0) {
        func_8140B98C(arg0, 0.5f, 0.05f);
    }
}

void Particle_WhiteFlashAltInit(unk_D_8140E720* arg0) {
    func_8140B938(arg0, 0.1f);
    Particle_SetPrimColor(arg0, 0xFF, 0xFF, 0xFF);
    func_8140BB74(arg0, 0x64, 0xC8, 0xFF);
    func_8140BC20(arg0, 0xFF);
    func_814081BC(arg0);
}

void Particle_WhiteFlashAltUpdate(unk_D_8140E720* arg0) {
    if (arg0->unk_B2 == 1) {
        Particle_WhiteFlashAltInit(arg0);
    }

    if (func_8140819C(arg0) != 0) {
        func_8140B98C(arg0, 0.8f, 0.08f);
    }
}

void Particle_SetWhiteFlashHandler(unk_D_8140E720* arg0, u8 arg1) {
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
