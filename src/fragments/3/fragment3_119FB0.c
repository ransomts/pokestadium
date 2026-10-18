#include "fragment3.h"
#include "src/6A40.h"
#include "src/math_util.h"
#include "src/memory.h"
#include "src/12D80.h"

void ParticleSystem_Init(void) {
    gParticleInstances = main_pool_alloc(sizeof(unk_D_8140E720) * 300, 0);
    bzero(gParticleInstances, sizeof(unk_D_8140E720) * 300);
    D_8140E72C = 0;

    gParticleEmitters = main_pool_alloc(sizeof(unk_D_8140E728) * 128, 0);
    bzero(gParticleEmitters, sizeof(unk_D_8140E728) * 128);
    gParticleEmitterNextIdx = 0;
}

s32 ParticleEmitter_Allocate(void) {
    s32 i;
    s32 var_v0 = gParticleEmitterNextIdx;
    unk_D_8140E728* var_v1 = &gParticleEmitters[var_v0];

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

void ParticleEmitter_Reset(unk_D_8140E728* arg0) {
    arg0->unk_28 = 0;
    arg0->unk_2B = 0;
    arg0->unk_2A = 0;
    arg0->unk_26 = arg0->unk_28;
}

s32 ParticleEmitter_Create(s32 arg0, s32 arg1, s8 arg2, f32 arg3, Vec3f arg4, Vec3s arg7, func_unk_D_8140E724_008 arg9,
                  unk_D_8140E728_01C* argA, s32 argB, u8 argC, s16 argD, u8 argE, u8 argF, u8 arg10) {
    unk_D_8140E728* temp_v0 = (unk_D_8140E728*)ParticleEmitter_Allocate();

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

void ParticleEmitter_SpawnSimple(s32 arg0, f32 arg1, Vec3f arg2, func_unk_D_8140E724_008 arg3, unk_D_8140E728_01C* arg4, s16 arg5,
                   u8 arg6, u8 arg7) {
    Vec3s sp50;

    sp50.x = sp50.y = sp50.z = 0;

    ParticleEmitter_Create(arg0, 0, 1, arg1, arg2, sp50, arg3, arg4, 0, 0, arg5, arg6, arg7, 0);
}

void ParticleEmitter_Spawn(s32 arg0, s32 arg1, s8 arg2, f32 arg3, Vec3f arg4, func_unk_D_8140E724_008 arg7,
                   unk_D_8140E728_01C* arg8, s16 arg9, u8 argA, u8 argB) {
    Vec3s sp50;

    sp50.x = sp50.y = sp50.z = 0;

    ParticleEmitter_Create(arg0, arg1, arg2, arg3, arg4, sp50, arg7, arg8, 0, 0, arg9, argA, argB, 0);
}

void ParticleInstance_PopulateFromEmitter(unk_D_8140E720* arg0, unk_D_8140E728* arg1, s16 arg2) {
    if ((s32)arg0 != -1) {
        while (arg0 != NULL) {
            arg0->unk_28 = arg1->unk_00;

            Vec3f_Copy(&arg0->unk_68, &arg1->unk_04);
            func_8140094C(&arg0->unk_94, &arg1->unk_10);

            arg0->unk_AC = arg2++;

            arg0->unk_08 = arg1->unk_18;
            arg0->unk_0C = arg1->unk_1C;

            arg0->unk_CD = arg1->unk_2F;
            arg0->unk_CE = arg1->unk_2D;
            arg0->unk_AA = arg1->unk_24;
            arg0->unk_CF = arg1->unk_2E;

            arg0 = arg0->next;
        };
    }
}

void ParticleEmitter_GenerateParticles(unk_D_8140E728* arg0) {
    s16 i;
    s16 sp2C;
    unk_D_8140E728_01C* temp_v0 = arg0->unk_1C;
    s16 temp_v1 = arg0->unk_24;
    unk_D_8140E728_01C_004_1* unk_04 = temp_v0->unk_04.a;

    if ((temp_v0->unk_00 == 1) && (unk_04->unk_00 == 1)) {
        ParticleInstance_PopulateFromEmitter(func_81407B5C(temp_v1), arg0, 0);
    } else {
        for (i = 0; i < sp2C; i++) {
            ParticleInstance_PopulateFromEmitter(func_81407B3C(), arg0, i);
        }
    }
}

void ParticleEmitter_Tick(unk_D_8140E728* arg0) {
    if (arg0->unk_2C == 0) {
        ParticleEmitter_GenerateParticles(arg0);
    }
}

void ParticleEmitters_UpdateAll(void) {
    s32 i;
    unk_D_8140E728* var_s0 = gParticleEmitters;

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

void func_87901BB0(unk_D_8140E720* arg0) {
    D_8140E628.unk_00.x = arg0->unk_28;
    D_8140E628.unk_00.y = arg0->unk_28;
    D_8140E628.unk_00.z = arg0->unk_28;
}

void func_87901BD4(unk_D_8140E720* arg0) {
    if (func_81408180(arg0) != 0) {
        arg0->unk_18 = 0;
        func_81408158(arg0);
        Particle_Free(arg0);
    } else {
        func_81408AF0(arg0);
    }
}

void ParticleSystem_UpdateAndRender(void) {
    s32 i;
    unk_D_8140E720* var_s0 = gParticleInstances;

    ParticleEmitters_UpdateAll();

    for (i = 0; i < 0x12C; i++, var_s0++) {
        if (var_s0->unk_D0 != 0) {
            func_87901BB0(var_s0);

            var_s0->unk_08(var_s0);

            func_87901BD4(var_s0);
        }
    }
}

void ParticleRender_SetupMiniCamera(void) {
    gSPPerspNormalize(gDisplayListHead++, gMiniCameraPtr->unk_24.perspNorm);
    gSPMatrix(gDisplayListHead++, gMiniCameraPtr->unk_24.mtx, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
    gSPMatrix(gDisplayListHead++, gMiniCameraPtr->unk_60.p_mtxf, G_MTX_NOPUSH | G_MTX_MUL | G_MTX_PROJECTION);

    D_8140E620 = GfxAlloc(sizeof(unk_D_8140E620));
    D_8140E624 = 0;

    gSPDisplayList(gDisplayListHead++, D_8140DB30);

    func_8140C204(gMiniCameraPtr);

    gSPDisplayList(gDisplayListHead++, D_8140DAE0);
}

void func_87901DA0(unk_D_8140E720* arg0) {
    Vec3s sp28;
    s16 sp26 = func_8140C038(arg0);

    Particle_SetPrimColor(arg0, 0xC8, 0xAA, 0x64);
    func_8140BB74(arg0, 0x3A, 0x18, 0x18);
    func_8140B938(arg0, (RandomMod(0xA) * 0.03f) + 0.15f);

    sp28.x = RandomRangeSigned(0x400) - 0x3000;
    sp28.y = (RandomRangeSigned(0x400) + (sp26 << 0xD)) - 0x3000;
    sp28.z = 0;

    func_8140A4F0(arg0, sp28);
    func_8140AD8C(arg0, (RandomMod(0xA) * 0.3f) + 6.0f);
    func_8140B2B4(arg0);
    func_8140BC20(arg0, 0xFF);
    func_814081BC(arg0);
}

void func_87901F04(unk_D_8140E720* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            func_87901DA0(arg0);
            break;

        case 2:
            if (arg0->unk_2C.y < 0.0f) {
                func_81408150(arg0);
            }
            break;
    }

    if (func_8140819C(arg0) != 0) {
        func_8140B0A4(arg0, -8.0f, 1.0f);
        func_81409BDC(arg0);
    }
}

void func_87901FA0(unk_D_8140E720* arg0) {
    func_8140B938(arg0, 0.25f);
    func_8140A594(arg0, RandomMod(0x10000));
    func_8140AD8C(arg0, (2.0f * MathUtil_Random_ZeroOne()) + 4.0f);
    func_8140AF24(arg0, (MathUtil_Random_ZeroOne() * 3.0f) + 1.0f);
    func_8140D5A0(arg0, 0xA);
    func_8140BC20(arg0, 0x64);
    func_8140BCA8(arg0, 7);
    func_814081BC(arg0);
}

void func_87902068(unk_D_8140E720* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            func_87901FA0(arg0);
            break;

        case 2:
            func_814084D8(arg0, 0, 7, 1, 2, 0);
            func_8140B98C(arg0, 0.8f, 0.1f);
            func_8140ADBC(arg0, 1.0f, 1);
            if (func_8140BDAC(arg0) != 0) {
                func_8140B180(arg0, 0.5f, 0.4f);
                func_81409C6C(arg0);
            }
            break;

        case 3:
            func_81408150(arg0);
            break;
    }

    if (func_8140819C(arg0) != 0) {
        func_81409CBC(arg0);
    }
}

void func_8790215C(unk_D_8140E720* arg0) {
    func_8140B938(arg0, 0.25f);
    func_8140A594(arg0, RandomMod(0x10000));
    func_8140AD8C(arg0, (2.0f * MathUtil_Random_ZeroOne()) + 2.0f);
    func_8140AF24(arg0, (MathUtil_Random_ZeroOne() * 3.0f) + 1.0f);
    func_8140D5A0(arg0, 0xA);
    func_8140BC20(arg0, 0x64);
    func_8140BCA8(arg0, 7);
    func_814081BC(arg0);
}

void func_87902224(unk_D_8140E720* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            func_8790215C(arg0);
            break;

        case 2:
            func_814084D8(arg0, 0, 7, 1, 2, 0);
            func_8140B98C(arg0, 0.8f, 0.1f);
            func_8140ADBC(arg0, 1.0f, 1);
            if (func_8140BDAC(arg0) != 0) {
                func_8140B180(arg0, 0.5f, 0.4f);
                func_81409C6C(arg0);
            }
            break;

        case 3:
            func_81408150(arg0);
            break;
    }

    if (func_8140819C(arg0) != 0) {
        func_81409CBC(arg0);
    }
}

void func_87902318(unk_D_8140E720* arg0) {
    func_8140B938(arg0, 0.5f);
    func_8140959C(arg0, 3, 0, 3);
    func_8140A594(arg0, RandomMod(0x10000));
    func_8140AD8C(arg0, (MathUtil_Random_ZeroOne() * 3.0f) + 3.0f);
    func_8140AF24(arg0, (2.0f * MathUtil_Random_ZeroOne()) + 4.0f);
    func_8140D5A0(arg0, 0xA);
    func_8140BC20(arg0, 0x64);
    func_8140BCA8(arg0, 7);
    func_814081BC(arg0);
}

void func_879023EC(unk_D_8140E720* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            func_87902318(arg0);
            break;

        case 2:
            func_814084D8(arg0, 0, 7, 1, 2, 0);
            func_8140B98C(arg0, 1.0f, 0.05f);
            func_8140ADBC(arg0, 1.0f, 1);
            if (func_8140BDAC(arg0) != 0) {
                func_8140B180(arg0, 1.0f, 0.2f);
                func_81409C6C(arg0);
            }
            break;

        case 3:
            func_81408150(arg0);
            break;
    }

    if (func_8140819C(arg0) != 0) {
        func_81409CBC(arg0);
    }
}

void func_879024DC(unk_D_8140E720* arg0) {
    Vec3s sp28;

    Particle_SetPrimColor(arg0, 0xC8, 0xAA, 0x64);
    func_8140BB74(arg0, 0x3A, 0x18, 0x18);
    func_8140B938(arg0, (MathUtil_Random_ZeroOne() * 0.1f) + 0.1f);

    sp28.x = RandomRangeSigned(0x800) - 0x3800;
    sp28.y = RandomRangeSigned(0x1000) + 0x8000;
    sp28.z = 0;

    func_8140A4F0(arg0, sp28);
    func_8140AD8C(arg0, (RandomMod(0xA) * 0.3f) + 6.0f);
    func_8140B2B4(arg0);
    func_8140BC20(arg0, 0xFF);
    func_814081BC(arg0);
}

void func_87902608(unk_D_8140E720* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            func_879024DC(arg0);
            break;

        case 2:
            if (arg0->unk_50.y < 0.0f) {
                func_81408150(arg0);
            }
            break;
    }

    if (func_8140819C(arg0) != 0) {
        if (arg0->unk_2C.y > 0.0f) {
            func_81408328(arg0);
        } else {
            func_81408348(arg0);
        }
        func_8140B0A4(arg0, -8.0f, 1.0f);
        func_81409BDC(arg0);
    }
}

void func_879026D8(unk_D_8140E720* arg0) {
    Vec3s sp28;
    s16 sp26 = func_8140C038(arg0);

    func_8140C040(arg0);

    sp28.x = RandomMod(0x10000);
    sp28.y = RandomMod(0x10000);
    sp28.z = 0;

    func_8140A24C(arg0, sp28);
    func_8140AD8C(arg0, 0.0f);
    func_8140ADA4(arg0, 0);
    func_8140D5A0(arg0, 0x17);
    func_8140B938(arg0, 0.0f);
    func_8140B95C(arg0, 0.6f);
    func_8140B974(arg0, 0.1f);
    func_81409404(arg0, 0x14, 0xA);
    func_8140935C(arg0, 0xF, 0xF);
    func_81409514(arg0, 0x14, 0xA);
    func_8140BCA8(arg0, sp26);
    func_81408348(arg0);
    func_814081BC(arg0);
}

void func_879027F0(unk_D_8140E720* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            func_879026D8(arg0);
            break;

        case 2:
            if (func_8140BDD0(arg0) != 0) {
                func_81408328(arg0);
            }
            break;

        case 3:
            if (func_8140BA48(arg0) != 0) {
                func_8140B95C(arg0, 0.0f);
            }
            break;

        case 4:
            func_8140BA48(arg0);
            break;

        case 5:
            func_81408150(arg0);
            break;
    }

    if (func_81408368(arg0) != 0) {
        func_81409FD8(arg0);
        if (arg0->unk_2C.y < 0.0f) {
            func_81408150(arg0);
        }
    }
}

void func_879028E0(unk_D_8140E720* arg0) {
    Vec3s sp28;
    s16 sp26 = func_8140C038(arg0);

    sp28.x = RandomMod(0x10000);
    sp28.y = RandomMod(0x10000);
    sp28.z = 0;

    func_8140A24C(arg0, sp28);
    func_8140AD8C(arg0, 0.0f);
    func_8140ADA4(arg0, 0.0f);
    func_8140D5A0(arg0, 0x17);
    func_8140B938(arg0, 0.0f);
    func_8140B95C(arg0, 0.2f);
    func_8140B974(arg0, 0.035f);
    func_81409404(arg0, 7, 3);
    func_8140935C(arg0, 0x14, 0xA);
    func_81409514(arg0, 7, 3);
    func_8140BCA8(arg0, sp26);
    func_81408348(arg0);
    func_814081BC(arg0);
}

void func_879029F0(unk_D_8140E720* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            func_879028E0(arg0);
            break;

        case 2:
            if (func_8140BDD0(arg0) != 0) {
                func_81408328(arg0);
            }
            break;

        case 3:
            if (func_8140BA48(arg0) != 0) {
                func_8140B95C(arg0, 0.0f);
            }
            break;

        case 4:
            func_8140BA48(arg0);
            break;

        case 5:
            func_81408150(arg0);
            break;
    }

    if (func_81408368(arg0) != 0) {
        func_81409FD8(arg0);
        if (arg0->unk_2C.y < 0.0f) {
            func_81408150(arg0);
        }
    }
}

void func_87902AE0(unk_D_8140E720* arg0) {
    Vec3s sp30;

    Particle_SetPrimColor(arg0, 0xFF, 0xFF, 0xFF);
    func_8140BB74(arg0, 0x64, 0xC8, 0xFF);
    func_8140B938(arg0, (MathUtil_Random_ZeroOne() * 0.2f) + 0.3f);

    sp30.x = RandomRangeSigned(0x1800) - 0x3000;
    sp30.y = RandomRangeSigned(0x10000);
    sp30.z = 0;

    func_8140A4F0(arg0, sp30);

    func_81408E18(arg0, RandomRangeSigned(0xA) * 0.1f, RandomMod(0xA) * 0.25f, RandomRangeSigned(0xA) * 0.1f);
    func_8140AD8C(arg0, (RandomMod(5) * 0.35f) + 4.0f);
    func_8140B2B4(arg0);
    func_8140BC20(arg0, 0xFF);
    func_814081BC(arg0);
}

void func_87902C9C(unk_D_8140E720* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            func_87902AE0(arg0);
            break;

        case 2:
            if (arg0->unk_50.y < -2.5f) {
                func_81408150(arg0);
            }
            break;
    }

    if (func_8140819C(arg0) != 0) {
        func_8140B0A4(arg0, -8.0f, 0.8f);
        func_81409BDC(arg0);
    }
}

void func_87902D3C(Gfx* arg0, unk_D_86002F34_000_014* arg1, UNUSED u16 arg2) {
    gDPPipeSync(arg0++);

    gDPSetPrimColor(arg0++, 0, 0xB4, 255, 255, 255, 128);
    gDPSetEnvColor(arg0++, 255, 255, 255, 255);
    gDPSetCombineLERP(arg0++, TEXEL0, TEXEL1, PRIM_LOD_FRAC, TEXEL1, TEXEL0, TEXEL1, PRIMITIVE, TEXEL1, 0, 0, 0,
                      COMBINED, COMBINED, 0, SHADE, 0);

    gDPLoadTextureTile(arg0++, arg1->unk_00, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 0, 0, 0, 31, 31, 0,
                       G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, 5, 5, 12, G_TX_NOLOD);

    func_81406204(arg0++, 0xA, 0xE, 0x20, 0x20);

    gDPLoadMultiTile(arg0++, arg1->unk_04, 0x0100, 1, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 0, 0, 0, 31, 31, 0,
                     G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, 5, 5, 1, G_TX_NOLOD);

    func_81406288(arg0++, 5, 7, 0x20, 0x20);

    gSPEndDisplayList(arg0++);
}

void func_87902F80(s32 arg0, arg1_func_87902F80* arg1) {
    if (arg0 == 2) {
        arg1->unk_18 = GfxAlloc(sizeof(Gfx) * 30);
        func_87902D3C(arg1->unk_18, arg1->unk_00.unk_14, gAnimationFrame);
    }
}

void func_87902FC8(Gfx* arg0, unk_D_86002F34_000_014* arg1, UNUSED u16 arg2) {
    gDPPipeSync(arg0++);

    gDPSetPrimColor(arg0++, 0, 0xC8, 255, 255, 255, 180);
    gDPSetEnvColor(arg0++, 255, 255, 255, 255);
    gDPSetCombineLERP(arg0++, TEXEL0, TEXEL1, PRIM_LOD_FRAC, TEXEL1, TEXEL0, TEXEL1, PRIMITIVE, TEXEL1, 0, 0, 0,
                      COMBINED, COMBINED, 0, SHADE, 0);

    gDPLoadTextureTile(arg0++, arg1->unk_00, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 0, 0, 0, 31, 31, 0,
                       G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, 5, 5, 15, 1);

    func_81406204(arg0++, 2, 6, 0x20, 0x20);

    gDPLoadMultiTile(arg0++, arg1->unk_04, 0x0100, 1, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 0, 0, 0, 31, 31, 0,
                     G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, 5, 5, 1, G_TX_NOLOD);

    func_81406288(arg0++, -2, 0xC, 0x20, 0x20);

    gSPEndDisplayList(arg0++);
}

void func_8790320C(s32 arg0, arg1_func_87902F80* arg1) {
    if (arg0 == 2) {
        arg1->unk_18 = GfxAlloc(sizeof(Gfx) * 30);
        func_87902FC8(arg1->unk_18, arg1->unk_00.unk_14, gAnimationFrame);
    }
}
