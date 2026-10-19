#include "fragment62.h"
#include "src/17300.h"
#include "src/12D80.h"
#include "src/6A40.h"
#include "src/F420.h"
#include "src/math_util.h"

static f32 D_84387B00[] = {
    0.0f, 1.0f,  1.0f,  1.3f, 0.8f, 0.9f, 1.3f,  0.8f,  1.0f,  0.9f,  0.6f, 1.2f,  1.2f, 0.6f,  0.9f, 1.5f, 0.8f,
    1.5f, 1.5f,  0.8f,  1.0f, 0.8f, 1.0f, 0.65f, 1.1f,  0.75f, 0.8f,  0.8f, 0.8f,  0.8f, 1.0f,  1.0f, 0.8f, 1.2f,
    1.0f, 0.8f,  1.25f, 1.0f, 1.5f, 0.8f, 1.0f,  1.0f,  0.8f,  0.8f,  1.2f, 1.35f, 0.9f, 1.2f,  1.2f, 1.1f, 0.7f,
    1.1f, 0.9f,  1.5f,  1.0f, 0.9f, 1.0f, 1.3f,  1.0f,  1.38f, 1.15f, 1.4f, 1.3f,  1.2f, 1.0f,  1.0f, 0.9f, 1.3f,
    1.2f, 0.8f,  0.9f,  1.0f, 0.9f, 1.3f, 1.35f, 1.35f, 1.4f,  1.35f, 1.3f, 1.35f, 1.4f, 1.2f,  1.2f, 1.5f, 1.0f,
    1.0f, 0.85f, 1.0f,  1.2f, 1.7f, 1.2f, 1.3f,  1.2f,  1.2f,  0.9f,  1.5f, 1.0f,  1.0f, 1.3f,  2.0f, 0.8f, 1.2f,
    1.2f, 1.2f,  0.8f,  1.2f, 0.8f, 0.8f, 1.2f,  0.8f,  1.2f,  1.25f, 1.4f, 0.9f,  1.2f, 1.25f, 0.9f, 1.2f, 0.7f,
    1.1f, 1.0f,  1.2f,  1.0f, 0.8f, 1.2f, 1.2f,  1.2f,  1.2f,  1.2f,  1.2f, 1.35f, 1.2f, 0.8f,  0.8f, 1.2f, 0.9f,
    1.0f, 1.2f,  1.0f,  1.2f, 1.0f, 1.1f, 1.5f,  1.55f, 1.5f,  1.6f,  1.6f, 1.75f, 1.6f, 1.5f,  1.6f, 1.0f,
};
static f32 gParticleYOffsetTable[] = {
    0.0f,   0.0f,   -8.0f, 0.0f,   -5.0f,  0.0f,   -10.0f, 0.0f,   -10.0f, 0.0f,   0.0f,   0.0f,   0.0f,   0.0f,
    -35.0f, 0.0f,   0.0f,  0.0f,   0.0f,   0.0f,   -10.0f, 0.0f,   0.0f,   -10.0f, -10.0f, -10.0f, -5.0f,  0.0f,
    -10.0f, -10.0f, 0.0f,  -10.0f, 0.0f,   0.0f,   -10.0f, 0.0f,   0.0f,   0.0f,   -15.0f, 0.0f,   0.0f,   0.0f,
    0.0f,   0.0f,   0.0f,  -15.0f, 0.0f,   0.0f,   0.0f,   0.0f,   -10.0f, -17.0f, 0.0f,   -10.0f, 0.0f,   0.0f,
    0.0f,   -10.0f, -5.0f, -10.0f, -10.0f, 0.0f,   0.0f,   0.0f,   0.0f,   0.0f,   0.0f,   0.0f,   0.0f,   -10.0f,
    0.0f,   0.0f,   0.0f,  0.0f,   0.0f,   0.0f,   0.0f,   0.0f,   -5.0f,  0.0f,   -22.0f, 0.0f,   -25.0f, -20.0f,
    10.0f,  0.0f,   0.0f,  0.0f,   10.0f,  -15.0f, 0.0f,   -5.0f,  0.0f,   -10.0f, 0.0f,   -10.0f, 0.0f,   10.0f,
    0.0f,   0.0f,   0.0f,  0.0f,   -35.0f, -10.0f, 0.0f,   0.0f,   0.0f,   0.0f,   -5.0f,  0.0f,   0.0f,   5.0f,
    -10.0f, 0.0f,   0.0f,  -2.0f,  0.0f,   0.0f,   -10.0f, -10.0f, 0.0f,   0.0f,   0.0f,   0.0f,   0.0f,   0.0f,
    -15.0f, 0.0f,   0.0f,  0.0f,   0.0f,   0.0f,   0.0f,   0.0f,   15.0f,  -5.0f,  0.0f,   0.0f,   0.0f,   0.0f,
    0.0f,   0.0f,   0.0f,  0.0f,   0.0f,   -15.0f, 0.0f,   -10.0f, -25.0f, -20.0f, -20.0f, 0.0f,
};

void Camera_SetLookAtReflect(void) {
    Mtx* sp3C = GfxAlloc(sizeof(Mtx) * 1);
    LookAt* sp38 = GfxAlloc(sizeof(LookAt) * 1);
    CameraStruct* temp_v0 = GetBattleCamera();

    guLookAtReflect(sp3C, sp38, temp_v0->unk_60.eye.x, temp_v0->unk_60.eye.y, temp_v0->unk_60.eye.z,
                    temp_v0->unk_60.at.x, temp_v0->unk_60.at.y, temp_v0->unk_60.at.z, temp_v0->unk_60.up.x,
                    temp_v0->unk_60.up.y, temp_v0->unk_60.up.z);
}

void ParticleEffect_ConfigureState(ParticleEffectInstance* arg0, s32 arg1) {
    f32 sp2C = 1.0f;
    s16 sp2A;
    s16 sp28;
    s16 sp26;
    s16 sp24 = Particle_GetByteCD(arg0);

    switch (Particle_GetShortCF(arg0)) {
        case 30:
            sp2A = 0x23;
            sp28 = 0x24;
            ParticleEffect_SetScaleAndSpeedByMoveId(arg0);
            break;

        case 0:
            sp2A = 0x66;
            sp28 = 0x67;
            sp2C = 0.5f;
            ParticleEffect_AdjustVerticalOffset_497A8(arg0);
            break;

        case 1:
            sp2A = 0x68;
            sp28 = 0x69;
            sp2C = 0.5f;
            break;

        case 2:
            sp2A = 0x6A;
            sp28 = 0x6B;
            sp2C = 0.5f;
            ParticleEffect_AdjustSizeByAnimId(arg0);
            break;

        case 3:
            sp2A = 0x73;
            sp28 = 0x74;
            sp2C = ParticleEffect_SpeciesAdjustA(arg0);
            break;

        case 4:
            sp2A = 0x78;
            sp28 = 0x79;
            Particle_SetPrimColor(arg0, 0x50, 0x46, 0x3C);
            Particle_SetEnvColor(arg0, 0xFF, 0, 0);
            break;

        case 5:
            sp2A = 0x7B;
            sp28 = 0x7C;
            break;

        case 6:
            sp2A = 0x7D;
            sp28 = 0x7E;
            break;

        case 7:
            sp2A = 0x7F;
            sp28 = 0x80;
            break;

        case 8:
            sp2A = 0x81;
            sp28 = 0x82;
            sp2C = 5.0f;
            SetPrimEnvColorFromPair(arg0, 0x17);
            Particle_SetPrimAlpha(arg0, 0x64);
            break;

        case 42:
            sp2A = 0x81;
            sp28 = 0x82;
            Particle_AddVelocityBackward(arg0, 300.0f);
            sp2C = 5.0f;
            SetPrimEnvColorFromPair(arg0, 0xC);
            Particle_SetPrimAlpha(arg0, 0x64);
            break;

        case 43:
            sp2A = 0x81;
            sp28 = 0x82;
            sp2C = 5.0f;
            SetPrimEnvColorFromPair(arg0, 0xF);
            Particle_SetPrimAlpha(arg0, 0x32);
            break;

        case 9:
            sp2A = 0x83;
            sp28 = 0x84;
            Particle_SetFlag(arg0, 0x800);
            Particle_AddVelocityYScaled(arg0, 5.0f);
            break;

        case 10:
            sp2A = 0x85;
            sp28 = 0x86;
            sp2C = 0.5f;
            break;

        case 11:
            sp2A = 0x88;
            sp28 = 0x89;
            sp2C = ParticleEffect_SpeciesAdjustB(arg0);
            break;

        case 12:
            sp2A = 0x8A;
            sp28 = 0x8B;
            break;

        case 13:
            sp2A = 0x9A;
            sp28 = 0x9B;
            sp2C = 1.5f;
            ParticleEffect_SpeciesAdjustC(arg0);

            switch (sp24) {
                case 1:
                    Particle_RotateY(arg0, 0x6000);
                    break;

                case 2:
                    Particle_RotateY(arg0, -0x4000);
                    break;
            }
            break;

        case 14:
            sp2A = 0x9C;
            sp2C = ParticleEffect_SpeciesAdjustD(arg0);
            Particle_SetPrimAlpha(arg0, 0);
            break;

        case 15:
            sp2A = 0x9C;
            sp2C = 1.5f;
            Particle_SetPrimAlpha(arg0, 0);
            break;

        case 16:
            sp2A = 0x9D;
            sp28 = 0x9E;

            switch (GetSpecies(arg0->unk_10)) {
                case 0x5F:
                    Particle_AddVelocityBackward(arg0, 15.0f);
                    Particle_SetVelocityYScaled(arg0, 15.0f);
                    break;

                case 0x82:
                    Particle_AddVelocityBackward(arg0, 15.0f);
                    break;
            }
            break;

        case 17:
            sp2A = 0xA3;
            sp28 = 0xA5;
            break;

        case 18:
            sp2A = 0xA3;
            sp28 = 0xA4;
            sp2C = 1.5f;
            break;

        case 19:
            sp2A = 0xA3;
            sp28 = 0xBB;
            sp2C = 1.5f;
            break;

        case 20:
            sp2A = 0xAA;
            sp28 = 0xAB;
            sp2C = 1.5f;
            break;

        case 21:
            sp2A = 0xAD;
            Particle_SetShortAE(arg0, 0xBE);
            Particle_SetPrimAlpha(arg0, 0);
            break;

        case 22:
            sp2A = 0x5C;
            sp28 = 0x5D;
            ParticleEffect_ApplySpecialEffect_495F0(arg0);
            break;

        case 23:
            sp2A = 0xAE;
            Particle_SetPrimAlpha(arg0, 0);
            break;

        case 24:
            sp2A = 0xAE;
            Particle_SetPrimAlpha(arg0, 0);
            break;

        case 25:
            sp2A = 0xAF;
            sp28 = 0xB0;
            Particle_SetPrimColor(arg0, 0xFF, 0xFF, 0);
            Particle_SetEnvColor(arg0, 0xFF, 0, 0);
            Particle_SetVelocityYScaled(arg0, 10.0f);
            break;

        case 26:
            sp2A = 0xB6;
            sp2C = GetParticleScaleForEffect(arg0);
            Particle_SetPrimAlpha(arg0, 0);
            break;

        case 27:
            sp2A = 0xB3;
            sp28 = 0xB4;
            Particle_SetPrimAlpha(arg0, 0x64);
            Particle_SetPrimColor(arg0, 0xFF, 0xFF, 0);
            Particle_SetEnvColor(arg0, 0xFF, 0, 0);
            sp2C = 0.8f;
            break;

        case 28:
            sp2A = 0xB3;
            sp28 = 0xB5;
            Particle_SetPrimAlpha(arg0, 0x64);
            Particle_SetPrimColor(arg0, 0xFF, 0xFF, 0);
            Particle_SetEnvColor(arg0, 0xFF, 0, 0);
            sp2C = 0.8f;
            break;

        case 29:
            sp2A = 0xBE;
            sp28 = 0xBF;
            break;

        case 31:
            sp2A = 0xC0;
            sp28 = 0xC1;
            SetPrimEnvColorFromPair(arg0, 0x17);
            Particle_SetPrimAlpha(arg0, 0x32);
            sp2C = 1.2f;
            break;

        case 32:
            sp2A = 0xB1;
            sp28 = 0xB2;
            SetPrimEnvColorFromPair(arg0, 0);
            Particle_SetPrimAlpha(arg0, 0);
            break;

        case 33:
            sp2A = 0xB7;
            break;

        case 34:
            sp2A = 0x2E;
            sp28 = 0x2F;
            Particle_RotateY(arg0, -0x4000);
            sp2C = 0.5f;
            break;

        case 35:
            sp2A = 0x3B;
            sp28 = 0x3C;
            break;

        case 36:
            sp2A = 0x3D;
            sp28 = 0x3E;

            switch (sp24) {
                case 0:
                    sp26 = 0x6000;
                    break;

                case 1:
                    sp26 = 0x4000;
                    break;

                case 2:
                    sp26 = 0x2000;
                    break;
            }
            Particle_RotateY(arg0, sp26);
            break;

        case 37:
            sp2A = 0x40;
            sp28 = 0x41;
            break;

        case 38:
            sp2A = 0x4B;
            sp28 = 0x4C;
            break;

        case 39:
            sp2A = 0x4D;
            sp28 = 0x4E;
            ParticleEffect_AdjustParametersByAnimId(arg0);
            Particle_SetPrimColor(arg0, 0xFF, 0xFF, 0xFF);
            Particle_SetEnvColor(arg0, 0x37, 0xFF, 0xFF);
            break;

        case 40:
            sp2A = 0x57;
            sp28 = 0x58;
            break;

        case 41:
            sp2A = 0x5A;
            sp28 = 0x5B;
            sp2C = ParticleEffect_GetScaleFactorByAnimId(arg0);
            break;
    }

    arg0->unk_14 = AllocateGraphNode(arg0);
    if (arg0->unk_14 != NULL) {
        switch (arg1) {
            case 0:
                InitWaterAnimNode(arg0->unk_14, sp2A, sp28);
                break;

            case 1:
                InitGraphNodeTexture(arg0->unk_14, sp2A);
                InitReverseAnimNode(arg0->unk_14, sp28);
                break;

            case 2:
                InitGraphNodeTexture(arg0->unk_14, sp2A);
                break;
        }
        Particle_SetScaleFactor1(arg0, sp2C);
        Particle_IncrementState(arg0);
    } else {
        Particle_ResetState(arg0);
    }
}

void ParticleEffect_StateHandlerA(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            ParticleEffect_ConfigureState(arg0, 0);
            break;

        case 2:
            if (Anim_HasReachedEnd(arg0->unk_14) != 0) {
                Particle_ClearActiveFlag(arg0);
            }
            break;
    }
}

void ParticleEffect_StateHandlerB(ParticleEffectInstance* arg0) {
    if (arg0->unk_B2 == 1) {
        ParticleEffect_ConfigureState(arg0, 0);
    }
}

void ParticleEffect_StateHandlerC(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            ParticleEffect_ConfigureState(arg0, 0);
            break;

        case 2:
            Particle_ApproachPrimAlphaWithCallback(arg0, arg0->unk_A6, Particle_GetShortCE(arg0));
            break;
    }
}

void ParticleEffect_StateHandlerD(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            ParticleEffect_ConfigureState(arg0, 1);
            break;

        case 2:
            if (IsAnimChannelFinished(arg0->unk_14) != 0) {
                Particle_IncrementState(arg0);
            }
            break;

        case 3:
            Particle_ResetState(arg0);
            break;
    }
}

void ParticleEffect_StateHandlerE(ParticleEffectInstance* arg0) {
    if (arg0->unk_B2 == 1) {
        ParticleEffect_ConfigureState(arg0, 2);
    }
}

void ParticleEffect_StateHandlerF(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            ParticleEffect_ConfigureState(arg0, 2);
            break;

        case 2:
            Particle_ApproachPrimAlphaWithCallback(arg0, arg0->unk_A6, Particle_GetShortCE(arg0));
            break;
    }
}

Gfx* Gfx_LoadParticleTextureTile(Gfx* arg0, u8* arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5, s16 arg6, s16 arg7, s16 arg8, s16 arg9,
                   s16 argA, s16 argB) {
    gDPLoadTextureTile_4b(arg0++, arg1, G_IM_FMT_I, arg2, 0, 0, 0, arg2 - 1, arg2 - 1, 0, G_TX_NOMIRROR | G_TX_WRAP,
                          G_TX_NOMIRROR | G_TX_WRAP, arg3, arg3, arg6, arg7);

    Gfx_ScrollTextureToDL(arg0++, arg4, arg5, arg2, arg2);

    gDPLoadMultiTile_4b(arg0++, arg1, 0x0100, 1, G_IM_FMT_I, arg2, 0, 0, 0, arg2 - 1, arg2 - 1, 0,
                        G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, arg3, arg3, argA, argB);

    Gfx_ScrollTexture1ToDL(arg0++, arg8, arg9, arg2, arg2);
    return arg0;
}

Gfx* Gfx_LoadParticleTextureTileFromStruct(Gfx* arg0, arg1_func_8434E21C* arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5, s16 arg6, s16 arg7,
                   s16 arg8, s16 arg9, s16 argA, s16 argB) {
    gDPLoadTextureTile_4b(arg0++, arg1->unk_00, G_IM_FMT_I, arg2, arg2, 0, 0, arg2 - 1, arg2 - 1, 0,
                          G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, arg3, arg3, arg6, arg7);

    Gfx_ScrollTextureToDL(arg0++, arg4, arg5, arg2, arg2);

    gDPLoadMultiTile_4b(arg0++, arg1->unk_04, 0x0100, 1, G_IM_FMT_I, arg2, arg2, 0, 0, arg2 - 1, arg2 - 1, 0,
                        G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, arg3, arg3, argA, argB);
    Gfx_ScrollTexture1ToDL(arg0++, arg8, arg9, arg2, arg2);
    return arg0;
}

void Gfx_SetParticlePrimEnvColors(Gfx* arg0) {
    ParticleEffectInstance* temp_v0 = GetGraphNodeData(gDefaultGraphRoot);

    gDPPipeSync(arg0++);

    gDPSetPrimColor(arg0++, 0, 0, temp_v0->prim_r, temp_v0->prim_g, temp_v0->prim_b, temp_v0->prim_a);
    gDPSetEnvColor(arg0++, temp_v0->env_r, temp_v0->env_g, temp_v0->env_b, 255);

    gSPEndDisplayList(arg0++);
}

void ParticleEffect_AllocateGfxIfNeeded(s32 arg0, arg1_func_84344CE8* arg1) {
    if (arg0 == 2) {
        arg1->unk_18 = GfxAlloc(sizeof(Gfx) * 30);
        Gfx_SetParticlePrimEnvColors(arg1->unk_18);
    }
}

void Gfx_DrawParticleTextureWithParams(Gfx* arg0, arg1_func_8434E21C* arg1, UNUSED u16 arg2) {
    s16 mask = 5;
    ParticleEffectInstance* sp40;
    s16 var_a2;
    s16 sp3C;
    s16 sp3A;
    s16 sp38;
    s16 sp36;
    s16 w = 32;
    s16 h = 32;
    s16 sp30;
    s16 sp2E;
    s16 sp2C;
    s16 sp2A;
    s32 temp_v0_2;

    sp40 = GetGraphNodeData(gDefaultGraphRoot);
    temp_v0_2 = Particle_GetShortCE(sp40);
    var_a2 = 0x80;

    switch (temp_v0_2) {
        case 0:
            var_a2 = 0x96;
            sp3C = 2;
            sp3A = 0;
            sp38 = -2;
            sp36 = 0;
            sp30 = 0xC;
            sp2E = 0;
            sp2C = 0xF;
            sp2A = 0;
            break;

        case 1:
            var_a2 = 0xFF;
            sp3C = 0;
            sp3A = 0;
            sp38 = 0xF;
            sp36 = 0;
            sp30 = 0xF;
            sp2E = 0;
            sp2C = 0xE;
            sp2A = 0xD;
            break;

        case 2:
            var_a2 = 0xFF;
            sp3C = 0;
            sp3A = 0;
            sp38 = 1;
            sp36 = 0;
            sp30 = 1;
            sp2E = 1;
            sp2C = 7;
            sp2A = 1;
            break;
    }

    gDPPipeSync(arg0++);
    gDPSetPrimColor(arg0++, 0, var_a2, sp40->prim_r, sp40->prim_g, sp40->prim_b, sp40->prim_a);
    gDPSetEnvColor(arg0++, sp40->env_r, sp40->env_g, sp40->env_b, 255);

    gDPLoadTextureTile_4b(arg0++, arg1->unk_00, G_IM_FMT_I, w, h, 0, 0, w - 1, h - 1, 0, G_TX_NOMIRROR | G_TX_WRAP,
                          G_TX_NOMIRROR | G_TX_WRAP, mask, mask, sp30, sp2E);

    Gfx_ScrollTextureToDL(arg0++, sp3C, sp3A, w, h);

    gDPLoadMultiTile_4b(arg0++, arg1->unk_04, 0x0100, 1, G_IM_FMT_I, w, h, 0, 0, w - 1, h - 1, 0,
                        G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, mask, mask, sp2C, sp2A);

    Gfx_ScrollTexture1ToDL(arg0++, sp38, sp36, w, h);

    gSPEndDisplayList(arg0++);
}

void ParticleEffect_AllocateGfxAndDraw(s32 arg0, arg1_func_84344CE8* arg1) {
    if (arg0 == 2) {
        arg1->unk_18 = GfxAlloc(sizeof(Gfx) * 30);
        Gfx_DrawParticleTextureWithParams(arg1->unk_18, arg1->unk_14, gAnimationFrame);
    }
}

void ParticleEffect_ConfigDefaultParameters(ParticleEffectInstance* arg0) {
    Particle_SetScaleFactor1(arg0, 3.0f);
    Particle_AddVelocityYScaled(arg0, 10.0f);
    Particle_AddVelocityForward(arg0, 15.0f);
    Particle_SetSpeed(arg0, -5.0f);
    SetPrimColorFromPalette(arg0, 0xA);
    SetEnvColorFromPalette(arg0, 0x19);
    Particle_SetPrimAlpha(arg0, 0x96);
    Particle_IncrementState(arg0);
}

void ParticleEffect_StateMachineHandler(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            ParticleEffect_ConfigDefaultParameters(arg0);
            break;

        case 2:
            Particle_DecrementTimerA6ToZeroWithCallback(arg0);
            break;

        case 3:
            Particle_ApproachPrimAlphaWithCallback(arg0, 0, 0x20);
            break;

        case 4:
            Particle_ResetState(arg0);
            break;
    }

    Particle_ApproachScaleFactor1(arg0, 0.0f, 0.1f);
    Particle_ApplyB278AndCopyXZAlt(arg0);
}

void ParticleEffect_SetGravityByMoveId(ParticleEffectInstance* arg0) {
    f32 sp1C = 0.0f;
    f32 sp18 = 0.0f;

    switch (GetSpecies(arg0->unk_10)) {
        case 0x2D:
            sp1C = 15.0f;
            break;

        case 0x36:
            sp18 = 10.0f;
            break;

        case 0x3B:
            sp1C = 10.0f;
            sp18 = 10.0f;
            break;

        case 0x4D:
            sp1C = 10.0f;
            break;

        case 0x4F:
            sp1C = 10.0f;
            sp18 = -10.0f;
            break;

        case 0x59:
            sp1C = 20.0f;
            sp18 = -10.0f;
            break;

        case 0x60:
            sp1C = 15.0f;
            break;

        case 0x66:
            sp1C = 10.0f;
            break;

        case 0x67:
            sp1C = 15.0f;
            break;

        case 0x6C:
            sp1C = 15.0f;
            break;

        case 0x6F:
            sp1C = 15.0f;
            break;

        case 0x73:
            sp1C = 15.0f;
            break;

        case 0x7A:
            sp1C = 15.0f;
            break;

        case 0x7D:
            sp1C = 15.0f;
            break;

        case 0x7F:
            sp18 = 15.0f;
            break;

        case 0x82:
            sp1C = 15.0f;
            sp18 = 5.0f;
            break;

        case 0x94:
            sp1C = 15.0f;
            break;
    }
    Particle_AddVelocityForward(arg0, sp1C);
    Particle_AddVelocityYScaled(arg0, sp18);
}

void ParticleEffect_ConfigByMoveId(ParticleEffectInstance* arg0) {
    Vec3f sp34;
    UNUSED s32 pad[2];
    s16 sp2A = Particle_GetByteCD(arg0);

    Particle_SetScaleFactor1(arg0, 0.05f);

    switch (sp2A) {
        case 0:
            sp34.x = 0;
            sp34.y = -5.0f;
            sp34.z = 0.0f;
            break;

        case 1:
            sp34.x = 0;
            sp34.y = 5.0f;
            sp34.z = 10.0f;
            break;

        case 2:
            sp34.x = 0;
            sp34.y = 5.0f;
            sp34.z = -10.0f;
            break;
    }

    Particle_AddVelocityScaledVec(arg0, sp34);
    Particle_AddVelocityYScaled(arg0, 10.0f);
    ParticleEffect_SetGravityByMoveId(arg0);
    Particle_SetSpeed(arg0, 0.0f);
    SetPrimColorFromPalette(arg0, 0xA);
    SetEnvColorFromPalette(arg0, 0x19);
    Particle_SetPrimAlpha(arg0, 0x96);
    Particle_IncrementState(arg0);
}

void ParticleEffect_HandleStateTransitions(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            ParticleEffect_ConfigByMoveId(arg0);
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

    Particle_ApproachScaleFactor1(arg0, 10.0f, 0.05f);
    Particle_ApplyB278AndCopyXZAlt(arg0);
}

void ParticleEffect_RegisterExplosion(void) {
    ParticleDef_CreateNullType17(0x55, 1);
    ParticleDef_CreateFull(0, 8, 0xC, ParticleEffect_HandleStateTransitions, &gParticleEffectData[0x24], 0xA, 1, 4, 0, 0, 0);
    ParticleDef_CreateFull(0, 8, 0xC, ParticleEffect_HandleStateTransitions, &gParticleEffectData[0x24], 0xA, 1, 4, 1, 0, 0);
    ParticleDef_CreateFull(0, 8, 0xC, ParticleEffect_HandleStateTransitions, &gParticleEffectData[0x24], 0xA, 1, 4, 2, 0, 0);
}

void ParticleEffect_RegisterSmoke(void) {
    ParticleDef_CreateDefault(0x30, 0x20, 0xA);
    ParticleDef_CreateFull(0, 0xC, 0xA, ParticleEffect_StateMachineHandler, &gParticleEffectData[0x24], 0x14, 1, 4, gParticleTexture_Default, 0, 0);
}

void ParticleEffect_SetParamsByMoveId(ParticleEffectInstance* arg0) {
    f32 sp24 = 0.0f;
    f32 sp20 = 0.0f;
    f32 sp1C = 0.12f;

    switch (GetSpecies(arg0->unk_10)) {
        case 0x4:
            sp24 = 5.0f;
            break;
        case 0xF:
            sp24 = 5.0f;
            break;
        case 0x16:
            sp24 = 3.0f;
            break;
        case 0x1F:
            sp24 = 5.0f;
            break;
        case 0x22:
            sp24 = 3.0f;
            break;
        case 0x24:
            sp24 = 15.0f;
            sp20 = 15.0f;
            break;
        case 0x2A:
            sp20 = 12.0f;
            break;
        case 0x2D:
            sp24 = -15.0f;
            sp20 = 20.0f;
            break;
        case 0x39:
            sp24 = 10.0f;
            break;
        case 0x41:
            sp24 = 8.0f;
            break;
        case 0x4A:
            sp24 = 10.0f;
            break;
        case 0x4C:
            sp24 = 2.0f;
            break;
        case 0x4F:
            sp20 = 8.0f;
            sp24 = 7.0f;
            break;
        case 0x50:
            sp20 = 5.0f;
            sp24 = 7.0f;
            break;
        case 0x54:
            sp20 = 20.0f;
            sp24 = 20.0f;
            break;
        case 0x55:
            sp24 = 20.0f;
            sp20 = 25.0f;
            break;
        case 0x5A:
            sp24 = -15.0f;
            sp20 = 7.0f;
            break;
        case 0x5B:
            sp24 = -10.0f;
            break;
        case 0x5E:
            sp24 = 5.0f;
            break;
        case 0x61:
            sp24 = 5.0f;
            break;
        case 0x73:
            sp24 = 12.0f;
            break;
        case 0x7F:
            sp24 = 3.0f;
            break;
        case 0x80:
            sp24 = 3.0f;
            break;
        case 0x82:
            sp1C = 0.08f;
            sp20 = 5.0f;
            break;
        case 0x83:
            sp1C = 0.08f;
            sp24 = 5.0f;
            break;
        case 0x86:
            sp24 = 3.0f;
            break;
        case 0x88:
            sp24 = 3.0f;
            break;
        case 0x8A:
            sp24 = 15.0f;
            break;
        case 0x8C:
            sp24 = 12.0f;
            sp20 = 10.0f;
            break;
        case 0x8E:
            sp24 = 10.0f;
            break;
        case 0x91:
            sp24 = 3.0f;
            break;
    }

    Particle_AddVelocityForward(arg0, sp24 + 5.0f);
    Particle_AddVelocityYScaled(arg0, sp20);
    Particle_SetScaleFactor1(arg0, sp1C);
}

void ParticleEffect_StartWithParams(ParticleEffectInstance* arg0) {
    ParticleEffect_SetParamsByMoveId(arg0);
    Particle_IncrementState(arg0);
}

void ParticleEffect_StateHandler(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            ParticleEffect_StartWithParams(arg0);
            break;

        case 3:
            Particle_ApproachPrimAlphaWithCallback(arg0, 0, 0x20);
            break;

        case 4:
            Particle_ResetState(arg0);

        case 2:
            break;
    }
}

void ParticleEffect_RegisterDefault(void) {
    ParticleDef_CreateQuick(0, ParticleEffect_StateHandler, &gParticleEffectData[0x2F], 0, 1, 0x10, gParticleTexture_Default, 0, 0);
}

void ParticleEffect_SetVerticalOffsetByMoveId(ParticleEffectInstance* arg0) {
    f32 var_fs0 = 0.0f;

    switch (GetSpecies(arg0->unk_10)) {
        case 0xF:
            var_fs0 = -13.0f;
            break;
        case 0x10:
            var_fs0 = -35.0f;
            Particle_AddVelocityForward(arg0, -5.0f);
            break;
        case 0x11:
            var_fs0 = -45.0f;
            Particle_AddVelocityForward(arg0, -10.0f);
            break;
        case 0x12:
            var_fs0 = -45.0f;
            Particle_AddVelocityForward(arg0, -10.0f);
            break;
        case 0x16:
            var_fs0 = -15.0f;
            break;
        case 0x19:
            var_fs0 = -10.0f;
            break;
        case 0x22:
            var_fs0 = 10.0f;
            break;
        case 0x29:
            Particle_AddVelocityForward(arg0, -10.0f);
            var_fs0 = -60.0f;
            break;
        case 0x34:
            var_fs0 = -10.0f;
            break;
        case 0x36:
            var_fs0 = -5.0f;
            break;
        case 0x3B:
            var_fs0 = 25.0f;
            break;
        case 0x4A:
            var_fs0 = -30.0f;
            break;
        case 0x4C:
            var_fs0 = -10.0f;
            break;
        case 0x4D:
            var_fs0 = -5.0f;
            break;
        case 0x51:
            var_fs0 = -30.0f;
            break;
        case 0x52:
            var_fs0 = -8.0f;
            break;
        case 0x5A:
            var_fs0 = -12.0f;
            break;
        case 0x5B:
            var_fs0 = -15.0f;
            break;
        case 0x64:
            var_fs0 = -12.0f;
            break;
        case 0x66:
            var_fs0 = -20.0f;
            break;
        case 0x67:
            var_fs0 = 5.0f;
            Particle_AddVelocityForward(arg0, 10.0f);
            break;
        case 0x6C:
            var_fs0 = 10.0f;
            break;
        case 0x70:
            var_fs0 = 15.0f;
            Particle_AddVelocityForward(arg0, -10.0f);
            break;
        case 0x74:
            var_fs0 = -20.0f;
            break;
        case 0x75:
            var_fs0 = -10.0f;
            break;
        case 0x79:
            var_fs0 = -8.0f;
            break;
        case 0x7A:
            var_fs0 = -5.0f;
            break;
        case 0x7B:
            var_fs0 = -5.0f;
            break;
        case 0x7F:
            var_fs0 = 5.0f;
            break;
        case 0x80:
            var_fs0 = -12.0f;
            break;
        case 0x82:
            var_fs0 = -10.0f;
            Particle_SetScaleFactor1(arg0, 0.15f);
            break;
        case 0x86:
            var_fs0 = -5.0f;
            Particle_AddVelocityLeft(arg0, 5.0f);
            break;
        case 0x87:
            var_fs0 = -15.0f;
            break;
        case 0x89:
            var_fs0 = -30.0f;
            break;
        case 0x93:
            var_fs0 = 18.0f;
            Particle_AddVelocityForward(arg0, -15.0f);
            break;
        case 0x94:
            var_fs0 = 15.0f;
            break;
        case 0x97:
            var_fs0 = -13.0f;
            break;
    }
    Particle_AddVelocityYScaled(arg0, var_fs0);
}

void ParticleEffect_CreateBurstWithRotation(ParticleEffectInstance* arg0, s16 arg1) {
    Vec3f sp24;

    arg0->unk_14 = AllocateGraphNode(arg0);

    if (arg0->unk_14 != NULL) {
        InitWaterAnimNode(arg0->unk_14, 0x21, 0x22);
        Particle_SetScaleFactor1(arg0, 0.2f);
        ParticleEffect_SetVerticalOffsetByMoveId(arg0);
        Vec3f_Set(&sp24, (arg1 * 5.0f * 2) + -10.0f, 5.0f, 10.0f);
        Particle_AddRotatedOffset(arg0, sp24);

        switch (arg1) {
            case 0:
                Particle_SetRotationZ(arg0, 0x1400);
                break;

            case 1:
                Particle_AddVelocityYScaled(arg0, 2.0f);
                Particle_SetRotationZ(arg0, 0);
                break;

            case 2:
                Particle_SetRotationZ(arg0, -0x1400);
                break;
        }

        Particle_IncrementState(arg0);
    } else {
        Particle_ResetState(arg0);
    }
}

void ParticleEffect_HandleBurstState(ParticleEffectInstance* arg0) {
    s16 sp26 = Particle_GetShortAC(arg0);

    switch (arg0->unk_B2) {
        case 1:
            Particle_SetTimerA6(arg0, sp26 * 8);
            Particle_IncrementState(arg0);
            break;

        case 2:
            if (Particle_DecrementTimerA6ToZero(arg0) != 0) {
                ParticleEffect_CreateBurstWithRotation(arg0, sp26);
            }
            break;

        case 3:
            if (Anim_HasReachedEnd(arg0->unk_14) != 0) {
                Particle_IncrementState(arg0);
            }
            break;

        case 4:
            Particle_ResetState(arg0);
            break;
    }
}

void ParticleEffect_InitBurstEffect(void) {
    ParticleDef_CreateNullType17(0x55, 1);
    ParticleDef_CreateQuick(0, ParticleEffect_HandleBurstState, &gParticleDefaultCallback, 0x1E, 3, 6, 0, 0, 0);
}

void ParticleEffect_SetScaleAndSpeedByMoveId(ParticleEffectInstance* arg0) {
    f32 sp1C = 10.0f;
    f32 sp18 = 0.0f;

    switch (GetSpecies(arg0->unk_10)) {
        case 0x5:
            sp18 = 10.0f;
            break;
        case 0xB:
            sp1C = 20.0f;
            break;
        case 0xC:
            sp1C = 8.0f;
            break;
        case 0xD:
            sp1C = 15.0f;
            break;
        case 0xF:
            sp1C = -10.0f;
            break;
        case 0x11:
            sp18 = 35.0f;
            sp1C = 0.0f;
            break;
        case 0x12:
            sp18 = 35.0f;
            sp1C = -5.0f;
            break;
        case 0x15:
            sp1C = 4.0f;
            break;
        case 0x16:
            sp18 = 5.0f;
            sp1C = 0.0f;
            break;
        case 0x18:
            sp18 = 8.0f;
            break;
        case 0x1C:
            sp18 = 5.0f;
            break;
        case 0x21:
            sp18 = 5.0f;
            break;
        case 0x26:
            sp1C = 15.0f;
            sp18 = 15.0f;
            break;
        case 0x28:
            sp1C = 15.0f;
            sp18 = 5.0f;
            break;
        case 0x29:
            sp1C = 0.0f;
            break;
        case 0x2A:
            sp18 = 20.0f;
            break;
        case 0x2B:
            sp1C = 15.0f;
            break;
        case 0x2D:
            sp1C = 10.0f;
            sp18 = 15.0f;
            Particle_AddVelocityLeft(arg0, -1.0f);
            break;
        case 0x30:
            sp18 = 30.0f;
            sp1C = -2.0f;
            Particle_AddVelocityLeft(arg0, -5.0f);
            break;
        case 0x31:
            sp1C = 5.0f;
            break;
        case 0x32:
            sp1C = 20.0f;
            break;
        case 0x33:
            sp1C = 25.0f;
            break;
        case 0x34:
            sp1C = 20.0f;
            break;
        case 0x36:
            sp1C = 15.0f;
            break;
        case 0x3B:
            sp1C = 20.0f;
            sp18 = 10.0f;
            break;
        case 0x3C:
            sp1C = 5.0f;
            break;
        case 0x3D:
            sp1C = 5.0f;
            break;
        case 0x3F:
            sp1C = 5.0f;
            break;
        case 0x40:
            sp18 = 10.0f;
            sp1C = 0.0f;
            break;
        case 0x41:
            sp1C = 20.0f;
            break;
        case 0x43:
            sp1C = 0.0f;
            break;
        case 0x44:
            sp18 = 8.0f;
            break;
        case 0x46:
            sp1C = -15.0f;
            break;
        case 0x47:
            sp1C = -5.0f;
            break;
        case 0x48:
            sp1C = -8.0f;
            break;
        case 0x49:
            sp1C = 0.0f;
            break;
        case 0x4B:
            sp1C = 0.0f;
            break;
        case 0x4C:
            sp1C = 0.0f;
            break;
        case 0x4D:
            sp1C = -10.0f;
            sp18 = 15.0f;
            break;
        case 0x4E:
            sp1C = -5.0f;
            break;
        case 0x4F:
            sp18 = 10.0f;
            break;
        case 0x51:
            sp1C = 0.0f;
            break;
        case 0x54:
            sp1C = 5.0f;
            break;
        case 0x55:
            sp1C = 5.0f;
            break;
        case 0x56:
            sp1C = 15.0f;
            sp18 = 15.0f;
            break;
        case 0x58:
            sp18 = 15.0f;
            break;
        case 0x59:
            sp18 = 40.0f;
            break;
        case 0x5B:
            sp1C = 0.0f;
            break;
        case 0x5C:
            sp18 = 10.0f;
            break;
        case 0x5D:
            sp18 = 15.0f;
            break;
        case 0x5E:
            sp1C = 5.0f;
            sp18 = 5.0f;
            break;
        case 0x5F:
            Particle_AddVelocityLeft(arg0, 23.0f);
            sp1C = -10.0f;
            sp18 = 0.0f;
            break;
        case 0x60:
            sp1C = 5.0f;
            sp18 = 10.0f;
            break;
        case 0x61:
            sp18 = 10.0f;
            break;
        case 0x62:
            sp18 = 10.0f;
            break;
        case 0x63:
            sp1C = 15.0f;
            sp18 = 60.0f;
            break;
        case 0x65:
            sp1C = 0.0f;
            sp18 = 20.0f;
            break;
        case 0x66:
            sp18 = 10.0f;
            break;
        case 0x67:
            sp18 = 40.0f;
            break;
        case 0x68:
            sp1C = 15.0f;
            break;
        case 0x6A:
            sp1C = 8.0f;
            break;
        case 0x6B:
            sp1C = 15.0f;
            break;
        case 0x6C:
            sp18 = 15.0f;
            break;
        case 0x6D:
            sp1C = 5.0f;
            break;
        case 0x6E:
            sp1C = 5.0f;
            break;
        case 0x6F:
            sp18 = 15.0f;
            sp1C = 0.0f;
            break;
        case 0x70:
            sp1C = 17.0f;
            sp18 = 10.0f;
            break;
        case 0x73:
            sp18 = 50.0f;
            break;
        case 0x75:
            sp1C = -10.0f;
            sp18 = 25.0f;
            break;
        case 0x77:
            sp1C = 0.0f;
            break;
        case 0x79:
            sp18 = 10.0f;
            sp1C = 5.0f;
            Particle_AddVelocityLeft(arg0, -3.0f);
            break;
        case 0x7B:
            sp1C = 5.0f;
            break;
        case 0x7C:
            sp18 = 10.0f;
            break;
        case 0x7D:
            sp18 = 10.0f;
            break;
        case 0x7F:
            sp1C = 25.0f;
            break;
        case 0x80:
            sp18 = 5.0f;
            sp1C = -5.0f;
            Particle_AddVelocityLeft(arg0, 3.0f);
            break;
        case 0x82:
            sp1C = 15.0f;
            sp18 = 20.0f;
            Particle_AddVelocityLeft(arg0, 3.0f);
            break;
        case 0x83:
            sp18 = 10.0f;
            break;
        case 0x84:
            sp1C = 15.0f;
            break;
        case 0x85:
            sp1C = 20.0f;
            break;
        case 0x86:
            sp18 = 10.0f;
            break;
        case 0x8B:
            sp1C = 5.0f;
            break;
        case 0x8D:
            sp18 = 15.0f;
            sp1C = 0.0f;
            break;
        case 0x8E:
            sp1C = -15.0f;
            sp18 = 25.0f;
            break;
        case 0x8F:
            sp1C = 15.0f;
            sp18 = 30.0f;
            break;
        case 0x90:
            sp18 = 15.0f;
            break;
        case 0x91:
            sp1C = 15.0f;
            sp18 = 10.0f;
            break;
        case 0x92:
            sp1C = 15.0f;
            sp18 = 20.0f;
            break;
        case 0x94:
            sp18 = 15.0f;
            break;
        case 0x95:
            Particle_AddVelocityRight(arg0, 1.0f);
            sp1C = 10.0f;
            sp18 = 15.0f;
            break;
        case 0x96:
            sp18 = 20.0f;
            sp1C = 7.0f;
            break;
        case 0x97:
            break;
    }
    Particle_AddVelocityYScaled(arg0, sp1C);
    Particle_AddVelocityForward(arg0, sp18);
}

void ParticleEffect_Init(void) {
    ParticleDef_CreateQuick(0, ParticleEffect_StateHandlerB, &gParticleDefaultCallback, 0x1E, 1, 0xB, 0, 0x1E, 0);
    ParticleSystem_AddSpawnOffset(0xF);

    switch (GetActionScriptId()) {
        case 0x70:
            ParticleDef_CreateFull(0, 0x10, 8, Particle_HandleState_Complex, &gParticleEffectData[0x44], 0, 4, 0xB, 0, 0x18, 5);
            break;

        case 0x71:
            ParticleDef_CreateDefault(0, 0x10, 0x20);
            ParticleDef_Create31FAC(0, 0, 0xA, 0, 0xFF, 0x30);
            ParticleDef_CreateFull(0, 0x10, 8, Particle_HandleState_Complex, &gParticleEffectData[0x44], 0, 8, 0xB, 0, 0x17, 5);
            ParticleDef_CreateBC20(0, 1, 0x20, 0xA, 0xFF);
            break;

        case 0x73:
            ParticleDef_CreateDefault(0, 0x10, 0x20);
            ParticleDef_Create31FAC(0, 0, 0xA, 0, 0xFF, 0x30);
            ParticleDef_CreateFull(0, 0x10, 8, Particle_HandleState_Complex, &gParticleEffectData[0x44], 0, 8, 0xB, 0, 0, 5);
            ParticleDef_CreateBC20(0, 1, 0x20, 0xA, 0xFF);
            break;
    }
}

void ParticleEffect_Render(Gfx* arg0, s32 arg1, u16 arg2) {
    Camera_SetLookAtReflect();

    switch (GetActionScriptId()) {
        case 0x70:
            gDPPipeSync(arg0++);
            gDPSetPrimColor(arg0++, 0, 0x80, 255, 255, 255, 255);
            gDPSetEnvColor(arg0++, 155, 255, 255, 255);
            break;

        case 0x71:
            gDPPipeSync(arg0++);
            gDPSetPrimColor(arg0++, 0, 0x80, 255, 255, 255, 255);
            gDPSetEnvColor(arg0++, 255, 255, 100, 255);
            break;

        case 0x73:
            gDPPipeSync(arg0++);
            gDPSetPrimColor(arg0++, 0, 0x80, 255, 255, 100, 255);
            gDPSetEnvColor(arg0++, 255, 100, 0, 255);
            break;
    }

    arg0 = Gfx_LoadParticleTextureTile(arg0, arg1, 0x20, 5, 0, 2, 0, 0, 0, 1, 0, 0);

    gSPEndDisplayList(arg0++);
}

void ParticleEffect_CreateDisplayList(s32 arg0, arg1_func_84344CE8* arg1) {
    if (arg0 == 2) {
        arg1->unk_18 = GfxAlloc(sizeof(Gfx) * 30);
        ParticleEffect_Render(arg1->unk_18, arg1->unk_14, gAnimationFrame);
    }
}

void ParticleEffect_ConfigureScale(ParticleEffectInstance* arg0) {
    f32 sp24 = 1.2f;
    f32 sp20 = 0.0f;
    s32 temp_v0 = GetSpecies(arg0->unk_10);

    if (temp_v0 < 0x98) {
        sp24 = D_84387B00[temp_v0];
        sp20 = gParticleYOffsetTable[temp_v0];
    }

    switch (temp_v0) {
        case 0x29:
            Particle_AddVelocityYScaled(arg0, 35.0f);
            break;

        case 0x57:
            Particle_AddVelocityYScaled(arg0, -10.0f);
            break;

        case 0x94:
            Particle_AddVelocityLeft(arg0, 15.0f);
            break;
    }

    Particle_SetScaleFactor1(arg0, sp24);
    Particle_AddVelocityForward(arg0, sp20);
}

void ParticleEffect_Start(ParticleEffectInstance* arg0, UNUSED s16 arg1) {
    arg0->unk_14 = AllocateGraphNode(arg0);
    if (arg0->unk_14 != NULL) {
        InitWaterAnimNode(arg0->unk_14, 0x25, 0x26);
        ParticleEffect_ConfigureScale(arg0);
        Particle_SetTimerA6(arg0, 0x20);
        Particle_IncrementState(arg0);
    } else {
        Particle_ResetState(arg0);
    }
}

void ParticleEffect_UpdateState(ParticleEffectInstance* arg0) {
    s16 temp_a1 = Particle_GetShortAC(arg0);

    switch (arg0->unk_B2) {
        case 1:
            ParticleEffect_Start(arg0, temp_a1);
            break;

        case 2:
            if (Particle_DecrementTimerA6ToZero(arg0) != 0) {
                Particle_CreateChildParticles(arg0, Particle_HandleState_Complex, &gParticleEffectData[0x42], 8, 0x18, 3);
                Particle_SetTimerA6(arg0, 0x10);
            }
            break;

        case 3:
            Particle_ApproachScaleFactor1WithCallback(arg0, 0.0f, 0.05f);
            Particle_ApproachPrimAlpha(arg0, 0, 8);
            break;

        case 4:
            Particle_ResetState(arg0);
            break;
    }
}

void ParticleEffect_DrawOverlay(Gfx* arg0, u16 arg1) {
    Fragment2_1GraphNode* tmp = gDefaultGraphRoot;

    gDPPipeSync(arg0++);

    gDPSetPrimColor(arg0++, 0, 0x80, 255, 255, 255, tmp->unk_01D);

    Gfx_ScrollTextureToDL(arg0++, 1, 1, 0x20, 0x20);
    Gfx_ScrollTexture1ToDL(arg0++, 2, 2, 0x20, 0x20);

    gSPEndDisplayList(arg0++);
}

void ParticleEffect_CreateOverlayDL(s32 arg0, arg1_func_84344CE8* arg1) {
    if (arg0 == 2) {
        arg1->unk_18 = GfxAlloc(sizeof(Gfx) * 10);
        ParticleEffect_DrawOverlay(arg1->unk_18, gAnimationFrame);
    }
}

void ParticleEffect_RegisterCallbacks(void) {
    ParticleDef_CreateQuick(0, ParticleEffect_UpdateState, &gParticleDefaultCallback, 0x1E, 1, 7, 0, 0, 0);
    ParticleDef_CreateQuick(0x14, Fragment_ProcessBC20Mode, &gParticleDefaultCallback, 0x50, 1, 0, 0, 0x35, 0);
}

void ParticleEffect_SetPaletteColors(ParticleEffectInstance* arg0) {
    s16 sp26;
    u16 sp24;
    u16 sp22;

    sp26 = GetActionScriptId();
    sp24 = 0x19;
    sp22 = 0xA;
    Particle_SetByteCA(arg0, 7);
    Particle_SetScaleFactor1(arg0, 1.0f);
    Particle_SetVelocityScaledXYZ(arg0, 160.0f, 120.0f, 0.0f);

    switch (sp26) {
        case 0x4E:
        case 0x93:
            break;

        case 0x4D:
            sp24 = 0x3E;
            sp22 = 0;
            break;

        case 0x4F:
            sp24 = 0x35;
            break;
    }

    SetPrimColorFromPalette(arg0, sp24);
    SetEnvColorFromPalette(arg0, sp22);
    Particle_SetPrimAlpha(arg0, 0);
    Particle_IncrementState(arg0);
}

void ParticleEffect_PaletteFadeHandler(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            ParticleEffect_SetPaletteColors(arg0);
            break;

        case 2:
            Particle_ApproachPrimAlphaWithCallback(arg0, 0xFF, 4);
            break;
    }
}

void ParticleEffect_RegisterParticleNodes(void) {
    ParticleDef_CreateQuick(8, ParticleEffect_PaletteFadeHandler, &gParticleEffectData[0x32], 0, 1, 0x18, 0, 0, 0);
    ParticleDef_CreateQuick(8, ParticleEffect_PaletteFadeHandler, &gParticleEffectData[0x31], 0, 1, 0x18, 0, 0, 0);
    ParticleDef_CreateFull(0, 3, 0x14, ParticleEffect_ColorfulBurstHandler, &gParticleEffectData[0x47], 0, 1, 0x10, 0x64, 0, 0);
}

void ParticleEffect_SetPrimEnvFromPair(ParticleEffectInstance* arg0) {
    s16 sp26 = Particle_GetShortCF(arg0);

    Particle_SetByteCA(arg0, 7);
    Particle_SetScaleFactor1(arg0, 1.0f);
    Particle_SetVelocityScaledXYZ(arg0, 160.0f, 120.0f, 0.0f);
    SetPrimEnvColorFromPair(arg0, sp26);
    Particle_SetPrimAlpha(arg0, 0);
    Particle_IncrementState(arg0);
}

void ParticleEffect_StateHandler2(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            ParticleEffect_SetPrimEnvFromPair(arg0);
            break;

        case 2:
            Particle_ApproachPrimAlphaWithCallback(arg0, 0xB4, 8);
            break;
    }
}

void ParticleEffect_RegisterEffectE0(void) {
    ParticleDef_CreateQuick(8, ParticleEffect_StateHandler2, &gParticleEffectData[0x33], 0, 1, 0x18, 0, 0x1C, 0);
    ParticleDef_CreateQuick(0, ParticleEffect_ColorfulBurstHandler, &gParticleEffectData[0x47], 0, 0xF, 0x11, gParticleTexture_Default, 0, 0);
}

void ParticleEffect_RegisterEffectE0Alt(void) {
    ParticleDef_CreateQuick(8, ParticleEffect_StateHandler2, &gParticleEffectData[0x33], 0, 1, 0x18, 0, 0x1E, 0);
    ParticleDef_CreateQuick(0, ParticleEffect_ColorfulBurstHandler, &gParticleEffectData[0x47], 0, 0xF, 0x11, gParticleTexture_Default, 0, 0);
}

void ParticleEffect_RegisterEffectE0Alt2(void) {
    ParticleDef_CreateQuick(8, ParticleEffect_StateHandler2, &gParticleEffectData[0x33], 0, 1, 0x18, 0, 0x1D, 0);
    ParticleDef_CreateQuick(0, ParticleEffect_ColorfulBurstHandler, &gParticleEffectData[0x47], 0, 0xF, 0x11, gParticleTexture_Default, 0, 0);
}

void ParticleEffect_InitializeSmall(ParticleEffectInstance* arg0) {
    Particle_SetScaleFactor1(arg0, 0.2f);
    SetPrimEnvColorFromPair(arg0, 0xD);
    Particle_SetPrimAlpha(arg0, 0xFF);
    Particle_IncrementState(arg0);
}

void ParticleEffect_SmallStateHandler(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            ParticleEffect_InitializeSmall(arg0);
            break;

        case 2:
            Particle_AnimLoopForwardComplete(arg0, 0, 7, 1, 2, 0);
            Particle_ApproachPrimAlpha(arg0, 0x20, 0x18);
            break;

        case 3:
            Particle_ResetState(arg0);
            break;
    }

    Particle_ApproachScaleFactor1(arg0, 0.1f, 0.01f);
}

void ParticleEffect_FireworksInit(ParticleEffectInstance* arg0) {
    s16 sp2E = Particle_GetShortAC(arg0);

    Particle_SetScaleFactor1(arg0, 0.5f);
    Particle_SetSpeed(arg0, 4.5f);
    Particle_AddRotationDeltaXYZ(arg0, RandomRangeSignedPlus(0x800, -0x3800), RandomRangeSigned(0x1400), 0);
    Particle_SetTimerA6(arg0, sp2E * 2);
    Particle_DisableFlag4(arg0);
    Particle_IncrementState(arg0);
}

void ParticleEffect_FireworksState(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            ParticleEffect_FireworksInit(arg0);
            break;

        case 2:
            if (Particle_DecrementTimerA6ToZeroWithCallback(arg0) != 0) {
                arg0->unk_14 = AllocateGraphNode(arg0);
                InitGraphNodeTexture(arg0->unk_14, 0x9F);
                Particle_EnableFlag4(arg0);
                Particle_SetTimerA6(arg0, RandomMod(3));
            }
            break;

        case 3:
            if (Particle_DecrementTimerA6ToZeroWithCallback(arg0) != 0) {
                Particle_CreateChildParticles(arg0, Particle_HandleState_Complex, &gParticleEffectData[0x42], 1, 0x17, 4);
            }
            break;

        case 4:
            Particle_ProcessTimer80(arg0, 0x1E);
            break;

        case 5:
            Particle_ResetState(arg0);
            break;
    }

    if (Particle_HasFlag4(arg0) != 0) {
        Particle_ApproachRotationXWrapToTarget(arg0, 0x1800, 0x400);
        Particle_ApplyB2B4AndAddAll(arg0);
        Particle_RotateX(arg0, 0x2000);
        ParticleNode_CreateMultiple(arg0, ParticleEffect_SmallStateHandler, &gParticleEffectData[0x4A], 1);
    }
}

void ParticleEffect_AdjustHeight(ParticleEffectInstance* arg0) {
    f32 sp1C = 0.0f;

    if (GetSpecies(arg0->unk_10) == 0x8C) {
        sp1C = 5.0f;
    }
    Particle_AddVelocityYScaled(arg0, sp1C);
}

void ParticleEffect_RotatingInit(ParticleEffectInstance* arg0) {
    arg0->unk_14 = AllocateGraphNode(arg0);
    if (arg0->unk_14 != NULL) {
        InitWaterAnimNode(arg0->unk_14, 0x2B, 0x2C);
        Particle_SetScaleFactor1(arg0, 0.25f);
        Particle_SetRotationY(arg0, RandomMod(0x10000));
        ParticleEffect_AdjustHeight(arg0);
        Particle_IncrementState(arg0);
    } else {
        Particle_ResetState(arg0);
    }
}

void ParticleEffect_RotatingState(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            Particle_SetTimerA6(arg0, RandomMod(0x18));
            Particle_IncrementState(arg0);
            break;

        case 2:
            if (Particle_DecrementTimerA6ToZero(arg0) != 0) {
                ParticleEffect_RotatingInit(arg0);
                ParticleDef_CreateQuick(0, Particle_HandleState_Complex, &gParticleEffectData[0x42], 0, 1, 0x10, arg0->unk_CD, 0x17, 4);
            }
            break;

        case 3:
            if (Anim_HasReachedEnd(arg0->unk_14) != 0) {
                Particle_IncrementState(arg0);
            }
            break;
    }
}

void ParticleEffect_RegisterCombined(void) {
    ParticleDef_CreateFull(0, 4, 5, ParticleEffect_FireworksState, &gParticleDefaultCallback, 0, 2, 0x11, gParticleTexture_Default, 0, 0);
    ParticleDef_CreateFull(0, 8, 3, ParticleEffect_BasicSetupHandler, &gParticleEffectData[0x4A], 0, 1, 0x11, gParticleTexture_Default, 0x33, 6);
}

void ParticleEffect_RegisterMultiple(void) {
    s32 i;
    s32 var_s2 = 0;
    s32 tmp;
    s32 end = gParticleEffectEntityA->unk_000.unk_0A7;

    if (end != 0) {
        for (i = 0; i < end; i++) {
            tmp = gParticleEffectEntityA->unk_000.unk_0A8[i].unk_00;
            ParticleDef_CreateQuick(0, ParticleEffect_RotatingState, &gParticleDefaultCallback, 0, 1, 0x10, tmp, 0, 0);
            var_s2++;
            if (var_s2 >= 8) {
                break;
            }
        }
    }
}

void ParticleEffect_RegisterSpecific(void) {
    ParticleDef_CreateQuick(0, ParticleEffect_StateHandlerB, &gParticleDefaultCallback, 0, 1, 0xA, 0, 0x22, 0);
    ParticleDef_CreateFull(4, 2, 4, Particle_HandleState_Complex, &gParticleEffectData[0x42], 0, 4, 9, 0, 0x17, 1);
}

void ParticleEffect_DrawSimple(Gfx* arg0, u8* arg1) {
    Camera_SetLookAtReflect();
    arg0 = Gfx_LoadParticleTextureTile(arg0, arg1, 0x20, 5, 2, 0, 0, 0, 1, 0, 0, 0);
    gSPEndDisplayList(arg0++);
}

void ParticleEffect_CreateSimpleDL(s32 arg0, arg1_func_84344CE8* arg1) {
    if (arg0 == 2) {
        arg1->unk_18 = GfxAlloc(sizeof(Gfx) * 30);
        ParticleEffect_DrawSimple(arg1->unk_18, arg1->unk_14);
    }
}

void ParticleEffect_ExplosionInit(ParticleEffectInstance* arg0) {
    arg0->unk_14 = AllocateParticleNode(arg0);
    if (arg0->unk_14 != NULL) {
        InitGraphNodeTexture(arg0->unk_14, 0x30);
        Particle_SetFlag(arg0, 0x200);
        Particle_SetScaleRaw1(arg0, 5.3f);
        Particle_SetPrimAlpha(arg0, 0);
        Particle_IncrementState(arg0);
    } else {
        Particle_ResetState(arg0);
    }
}

void ParticleEffect_ExplosionState(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            ParticleEffect_ExplosionInit(arg0);
            break;

        case 2:
            Particle_ApproachPrimAlphaWithCallback(arg0, 0xFF, 0x20);
            break;
    }

    if (Particle_IsActive(arg0) != 0) {
        GetCameraOffsetPosition(&arg0->unk_50, 3700.0f);
    }
}

void ParticleEffect_SparkleInit(ParticleEffectInstance* arg0) {
    UNUSED s32 pad[2];
    s16 sp26 = Particle_GetShortAC(arg0);
    UNUSED s16 pad2;
    s16 sp22;

    Particle_GetShortCE(arg0);
    sp22 = Particle_GetShortCF(arg0);
    Particle_SetTimerA6(arg0, sp26 * 2);
    SetPrimEnvColorFromPair(arg0, Particle_GetShortCF(arg0));
    Particle_SetScaleFactor1(arg0, 1.2f);
    Particle_SetScaleFactor2(arg0, 1.0f);
    Particle_SetScaleFactor3(arg0, 0.02f);
    Particle_SetRandomVelocityXYZ(arg0, 5, 0xF, 0xF);
    Particle_AddVelocityYScaled(arg0, 10.0f);
    Particle_SetSpeed(arg0, (RandomMod(0xA) * 0.5f) + 8.0f);
    SetPrimEnvColorFromPair(arg0, sp22);
    Particle_SetPrimAlpha(arg0, 0xC8);
    Particle_SetShortAE(arg0, 4);
    Particle_DisableFlag4(arg0);
    Particle_IncrementState(arg0);
}

void ParticleEffect_SparkleState(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            ParticleEffect_SparkleInit(arg0);
            break;

        case 2:
            if (Particle_DecrementTimerA6ToZeroWithCallback(arg0) != 0) {
                Particle_EnableFlag4(arg0);
                Particle_SetTimerA6(arg0, 4);
            }
            break;

        case 3:
            Particle_ApproachScaleFactor2(arg0);
            Particle_AnimLoopForwardComplete(arg0, 1, 7, 1, 2, 0);
            Particle_SetTargetVelocityBackward(arg0);
            Particle_ApproachPrimAlpha(arg0, 0x40, 8);
            break;

        case 4:
            Particle_ClearActiveFlag(arg0);
            break;
    }
}

void ParticleEffect_RegisterSparkle(void) {
    ParticleDef_CreateDefault(0, 0x10, 0x35);
    ParticleDef_Create32E6CAlt(0, 0xFF, 0x10, 0xA, 0x96);
    ParticleDef_CreateQuick(0, ParticleEffect_ExplosionState, &gParticleDefaultCallback, 0x1E, 1, 0x14, 0, 0, 0);
}

void ParticleEffect_RegisterAll(void) {
    ParticleDef_CreateFull(0, 0xA, 2, ParticleEffect_StateHandlerA, &gParticleDefaultCallback, 0, 1, 0xC, 0, 0x2A, 0);
    ParticleDef_Create323BC(4, 0xA, 0x35, 8, 0xC8, 0x18);
    ParticleSystem_SetSpawnOffset(4);
    ParticleDef_CreateFull(0, 5, 5, ParticleEffect_SparkleState, &gParticleEffectData[0x4A], 0, 4, 0xB, 9, 0x13, 0);
    ParticleDef_CreateFull(0, 3, 8, ParticleEffect_FireworkHandler, &gParticleEffectData[0x44], 0, 4, 0xB, 9, 0x18, 0xB);
    ParticleDef_CreateFull(0, 7, 3, ParticleEffect_Fireball_Stage5, &gParticleEffectData[0x19], 0, 6, 0x10, gParticleTexture_Default, 0x26, 0);
    ParticleDef_CreateDefault(0x32, 0x20, 0xA);
}

void ParticleEffect_DrawNode(Gfx* arg0, s32 arg1, u16 arg2) {
    ParticleEffectInstance* temp_v0 = GetGraphNodeData(gDefaultGraphRoot);

    gDPPipeSync(arg0++);
    gDPSetPrimColor(arg0++, 0, 0x80, 255, 255, 255, temp_v0->prim_a);

    arg0 = Gfx_LoadParticleTextureTileFromStruct(arg0, arg1, 0x40, 6, -4, 0xF, 0, 0, -0xF, 5, 0, 0);

    gSPEndDisplayList(arg0++);
}

void ParticleEffect_CreateNodeDL(s32 arg0, arg1_func_84344CE8* arg1) {
    if (arg0 == 2) {
        arg1->unk_18 = GfxAlloc(sizeof(Gfx) * 30);
        ParticleEffect_DrawNode(arg1->unk_18, arg1->unk_14, gAnimationFrame);
    }
}

void ParticleEffect_DrawNodeVariant(Gfx* arg0, arg1_func_8434E21C* arg1, UNUSED u16 arg2) {
    arg0 = Gfx_LoadParticleTextureTileFromStruct(arg0, arg1, 0x40, 6, -4, 0xF, 0, 0, -5, 5, 0, 0);

    gSPEndDisplayList(arg0++);
}

void ParticleEffect_CreateNodeVariantDL(s32 arg0, arg1_func_84344CE8* arg1) {
    if (arg0 == 2) {
        arg1->unk_18 = GfxAlloc(sizeof(Gfx) * 30);
        ParticleEffect_DrawNodeVariant(arg1->unk_18, arg1->unk_14, gAnimationFrame);
    }
}

void ParticleEffect_DrawSimple2(Gfx* arg0, u8* arg1, UNUSED u16 arg2) {
    arg0 = Gfx_LoadParticleTextureTile(arg0, arg1, 0x20, 5, -8, -0x1E, 0, 0, -0xB, -0xA, 0, 0);

    gSPEndDisplayList(arg0++);
}

void ParticleEffect_CreateSimple2DL(s32 arg0, arg1_func_84344CE8* arg1) {
    if (arg0 == 2) {
        arg1->unk_18 = GfxAlloc(sizeof(Gfx) * 30);
        ParticleEffect_DrawSimple2(arg1->unk_18, arg1->unk_14, gAnimationFrame);
    }
}

void func_84345490(void) {
}

void ParticleEffect_GetVerticalOffset(ParticleEffectInstance* arg0) {
    f32 sp1C = 5.0f;

    switch (GetSpecies(arg0->unk_10)) {
        case 0xF:
            sp1C = -10.0f;
            break;

        case 0x10:
            sp1C = -30.0f;
            break;

        case 0x11:
            sp1C = -35.0f;
            break;

        case 0x12:
            sp1C = -35.0f;
            break;

        case 0x29:
            sp1C = -50.0f;
            break;

        case 0x3B:
            sp1C = 23.0f;
            break;

        case 0x4A:
            sp1C = -25.0f;
            break;

        case 0x5A:
            sp1C = -8.0f;
            break;

        case 0x5F:
            sp1C = -20.0f;
            Particle_AddVelocityLeft(arg0, 10.0f);
            break;

        case 0x64:
            sp1C = -10.0f;
            break;

        case 0x89:
            sp1C = -25.0f;
            break;

        case 0x93:
            sp1C = 17.0f;
            break;

        case 0x97:
            sp1C = -10.0f;
            break;
    }
    Particle_AddVelocityYScaled(arg0, sp1C);
}

void ParticleEffect_ConfigureFromPalette(ParticleEffectInstance* arg0) {
    s16 sp26 = Particle_GetShortCF(arg0);
    s16 sp24;

    arg0->unk_14 = AllocateGraphNode(arg0);

    if (arg0->unk_14 != NULL) {
        InitWaterAnimNode(arg0->unk_14, 0x31, 0x32);
        Particle_SetScaleFactor1(arg0, 0.25f);
        ParticleEffect_GetVerticalOffset(arg0);
        switch (sp26) {
            case 0:
                sp24 = 0;
                break;

            case 1:
                sp24 = 0x5555;
                break;

            case 2:
                sp24 = -0x5556;
                break;
        }

        Particle_RotateY(arg0, sp24);
        Particle_IncrementState(arg0);
    } else {
        Particle_ResetState(arg0);
    }
}

void ParticleEffect_PaletteState(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            ParticleEffect_ConfigureFromPalette(arg0);
            break;

        case 2:
            if (Anim_HasReachedEnd(arg0->unk_14) != 0) {
                Particle_IncrementState(arg0);
            }
            break;

        case 3:
            Particle_ResetState(arg0);
            break;
    }
}

void ParticleEffect_RegisterPaletteVariants(void) {
    ParticleDef_CreateQuick(0, ParticleEffect_PaletteState, &gParticleDefaultCallback, 0x1E, 1, 6, gParticleTexture_Default, 0, 0);
    ParticleDef_CreateQuick(0, ParticleEffect_PaletteState, &gParticleDefaultCallback, 0x1E, 1, 6, gParticleTexture_Default, 1, 0);
    ParticleDef_CreateQuick(0, ParticleEffect_PaletteState, &gParticleDefaultCallback, 0x1E, 1, 6, gParticleTexture_Default, 2, 0);
}

void ParticleEffect_SetupColorAndAnim(ParticleEffectInstance* arg0) {
    s16 sp26 = Particle_GetShortCF(arg0);
    u16 sp24;

    switch (GetActionScriptId()) {
        case 0x47:
            sp24 = 0x18;
            break;

        case 0x48:
            sp24 = 0x1F;
            break;

        case 0x8D:
            sp24 = 0x21;
            break;
    }

    SetPrimEnvColorFromPair(arg0, sp24);

    arg0->unk_14 = AllocateGraphNode(arg0);
    if (arg0->unk_14 != NULL) {
        InitGraphNodeTexture(arg0->unk_14, 0x33);
        if (sp26 == 0) {
            SetAnimChannel(arg0->unk_14, 0x34);
        } else {
            InitReverseAnimNode(arg0->unk_14, 0x34);
        }
        Particle_SetScaleFactor1(arg0, 1.0f);
        Particle_IncrementState(arg0);
    } else {
        Particle_ResetState(arg0);
    }
}

void ParticleEffect_ColorAnimState(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            ParticleEffect_SetupColorAndAnim(arg0);
            break;

        case 2:
            if (IsAnimChannelFinished(arg0->unk_14) != 0) {
                Particle_IncrementState(arg0);
            }
            break;

        case 3:
            Particle_ResetState(arg0);
            break;
    }
}

void ParticleEffect_ColorAnimStateAlt(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            ParticleEffect_SetupColorAndAnim(arg0);
            break;

        case 2:
            if (Anim_HasReachedEnd(arg0->unk_14) != 0) {
                Particle_IncrementState(arg0);
            }
            break;

        case 3:
            Particle_ResetState(arg0);
            break;
    }
}

void ParticleEffect_DrawColorNode(Gfx* arg0, UNUSED s32 arg1, UNUSED u16 arg2) {
    ParticleEffectInstance* temp_v0 = GetGraphNodeData(gDefaultGraphRoot);

    gDPPipeSync(arg0++);

    gDPSetPrimColor(arg0++, 0, 0, temp_v0->prim_r, temp_v0->prim_g, temp_v0->prim_b, temp_v0->prim_a);
    gDPSetEnvColor(arg0++, temp_v0->env_r, temp_v0->env_g, temp_v0->env_b, 0);

    gSPEndDisplayList(arg0++);
}

void ParticleEffect_CreateColorNodeDL(s32 arg0, arg1_func_84344CE8* arg1) {
    if (arg0 == 2) {
        arg1->unk_18 = GfxAlloc(sizeof(Gfx) * 30);
        ParticleEffect_DrawColorNode(arg1->unk_18, arg1->unk_14, gAnimationFrame);
    }
}

void ParticleEffect_RegisterColorAnim(void) {
    ParticleDef_CreateQuick(0, ParticleEffect_ColorAnimState, &gParticleDefaultCallback, 0, 1, 2, gParticleTexture_Default, 1, 0);
}

void ParticleEffect_RegisterModeSpecific(void) {
    switch (GetActionScriptId()) {
        case 0x8D:
            ParticleDef_Create32604(0, 0xC, 0x41, 2, 0xC8, 0x10);
            break;

        case 0x47:
            ParticleDef_Create32604(0, 0x37, 0x41, 2, 0xC8, 0x10);
            break;

        case 0x48:
            ParticleDef_Create32604(0, 0x29, 0x41, 2, 0xC8, 0x10);
            break;
    }

    ParticleDef_CreateQuick(0, ParticleEffect_ColorAnimStateAlt, &gParticleDefaultCallback, 0, 1, 2, gParticleTexture_Default, 0, 0);
}

void ParticleEffect_LargeExplosionInit(ParticleEffectInstance* arg0) {
    arg0->unk_14 = AllocateGraphNode(arg0);
    if (arg0->unk_14 != NULL) {
        InitGraphNodeTexture(arg0->unk_14, 0x35);
        Particle_SetScaleFactor1(arg0, 5.0f);
        Particle_AddVelocityYScaled(arg0, -100.0f);
        Particle_SetPrimAlpha(arg0, 0);
        Particle_IncrementState(arg0);
    } else {
        Particle_ResetState(arg0);
    }
}

void ParticleEffect_LargeExplosionState(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            ParticleEffect_LargeExplosionInit(arg0);
            break;

        case 2:
            Particle_ApproachPrimAlphaWithCallback(arg0, 0x80, 0x10);
            break;

        case 3:
            Particle_DecrementTimerA6ToZeroWithCallback(arg0);
            break;

        case 4:
            Particle_ApproachPrimAlphaWithCallback(arg0, 0, 0x20);
            break;
    }
}

void ParticleEffect_RegisterLargeExplosion(void) {
    ParticleDef_CreateQuick(0, ParticleEffect_LargeExplosionState, &gParticleDefaultCallback, 0xA, 1, 0xA, 0, 0, 0);
}

void ParticleEffect_LargeExplosionInitDup(ParticleEffectInstance* arg0) {
    arg0->unk_14 = AllocateGraphNode(arg0);
    if (arg0->unk_14 != NULL) {
        InitGraphNodeTexture(arg0->unk_14, 0x35);
        Particle_SetScaleFactor1(arg0, 5.0f);
        Particle_AddVelocityYScaled(arg0, -100.0f);
        Particle_SetPrimAlpha(arg0, 0);
        Particle_IncrementState(arg0);
    } else {
        Particle_ResetState(arg0);
    }
}

void ParticleEffect_LargeExplosionStateDup(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            ParticleEffect_LargeExplosionInitDup(arg0);
            break;

        case 2:
            Particle_ApproachPrimAlphaWithCallback(arg0, 0x80, 0x10);
            break;

        case 3:
            Particle_DecrementTimerA6ToZeroWithCallback(arg0);
            break;

        case 4:
            Particle_ApproachPrimAlphaWithCallback(arg0, 0, 0x20);
            break;
    }
}

void ParticleEffect_RegisterLargeExplosionAndEffects(void) {
    ParticleDef_CreateQuick(0, ParticleEffect_LargeExplosionStateDup, &gParticleDefaultCallback, 0x40, 1, 0xA, 0, 0, 0);
    ParticleDef_CreateAlphaMode(0, 0xFF, 0, 0x10);
    ParticleDef_CreateAlphaMode(0x2D, 0, 0xFF, 0x20);
}

void ParticleEffect_DrawSpecial(Gfx* arg0, s32 arg1, u16 arg2) {
    UNUSED s32 pad;
    ParticleEffectInstance* sp28 = GetGraphNodeData(gDefaultGraphRoot);

    Gfx_ScrollTextureToDL(arg0++, 1, 0x28, 0x20, 0x20);
    Gfx_ScrollTexture1ToDL(arg0++, -1, 0x1E, 0x20, 0x20);

    gDPPipeSync(arg0++);

    gDPSetPrimColor(arg0++, 0, 0x80, 255, 255, 255, sp28->prim_a);
    gDPSetEnvColor(arg0++, 255, 55, 100, 255);

    gSPEndDisplayList(arg0++);
}

void ParticleEffect_CreateSpecialDL(s32 arg0, arg1_func_84344CE8* arg1) {
    if (arg0 == 2) {
        arg1->unk_18 = GfxAlloc(sizeof(Gfx) * 30);
        ParticleEffect_DrawSpecial(arg1->unk_18, arg1->unk_14, gAnimationFrame);
    }
}

void ParticleEffect_DrawSimpleColor(Gfx* arg0, UNUSED s32 arg1, UNUSED u16 arg2) {
    ParticleEffectInstance* temp_v0 = GetGraphNodeData(gDefaultGraphRoot);

    gDPPipeSync(arg0++);

    gDPSetPrimColor(arg0++, 0, 0x80, 255, 255, 255, temp_v0->prim_a);
    gDPSetEnvColor(arg0++, 255, 255, 100, 255);

    gSPEndDisplayList(arg0++);
}

void ParticleEffect_CreateSimpleColorDL(s32 arg0, arg1_func_84344CE8* arg1) {
    if (arg0 == 2) {
        arg1->unk_18 = GfxAlloc(sizeof(Gfx) * 30);
        ParticleEffect_DrawSimpleColor(arg1->unk_18, arg1->unk_14, gAnimationFrame);
    }
}

void ParticleEffect_SetAnimByPalette(ParticleEffectInstance* arg0) {
    s16 sp26 = Particle_GetShortCF(arg0);

    arg0->unk_14 = AllocateGraphNode(arg0);
    if (arg0->unk_14 != NULL) {
        if (sp26 == 0) {
            InitWaterAnimNode(arg0->unk_14, 0x36, 0x37);
            Particle_SetScaleFactor1(arg0, 0.75f);
        } else {
            InitWaterAnimNode(arg0->unk_14, 0x61, 0x62);
            Particle_SetScaleFactor1(arg0, 1.0f);
        }
        Particle_IncrementState(arg0);
    } else {
        Particle_ResetState(arg0);
    }
}

void ParticleEffect_AnimState(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            ParticleEffect_SetAnimByPalette(arg0);
            break;

        case 2:
            if (Anim_HasReachedEnd(arg0->unk_14) != 0) {
                Particle_IncrementState(arg0);
            }
            break;

        case 3:
            Particle_ResetState(arg0);
            break;
    }
}

void ParticleEffect_SetOffsetsByPalette(ParticleEffectInstance* arg0) {
    u16 sp26 = Particle_GetShortCF(arg0);

    arg0->unk_14 = AllocateGraphNode(arg0);
    if (arg0->unk_14 != NULL) {
        InitWaterAnimNode(arg0->unk_14, 0x39, 0x3A);
        Particle_SetScaleFactor1(arg0, 0.5f);

        switch (sp26) {
            case 0:
                break;

            case 1:
                Particle_AddVelocityScaledXYZ(arg0, -10.0f, 0.0f, 20.0f);
                break;

            case 2:
                Particle_AddVelocityScaledXYZ(arg0, 10.0f, 0.0f, -20.0f);
                break;

            case 3:
                Particle_AddVelocityScaledXYZ(arg0, 20.0f, 0.0f, -20.0f);
                break;

            case 4:
                Particle_AddVelocityScaledXYZ(arg0, -20.0f, 0.0f, 20.0f);
                break;

            case 5:
                Particle_AddVelocityScaledXYZ(arg0, 15.0f, 0.0f, -25.0f);
                break;

            case 6:
                Particle_AddVelocityScaledXYZ(arg0, 20.0f, 0.0f, 30.0f);
                break;

            case 7:
                Particle_AddVelocityScaledXYZ(arg0, 15.0f, 0.0f, -10.0f);
                break;

            case 8:
                Particle_SetScaleFactor1(arg0, 1.5f);
                break;
        }
        Particle_SetPrimColor(arg0, 0xFF, 0xFF, 0xFF);
        Particle_IncrementState(arg0);
    } else {
        Particle_ResetState(arg0);
    }
}

void ParticleEffect_OffsetState(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            ParticleEffect_SetOffsetsByPalette(arg0);
            break;

        case 2:
            Particle_ProcessTimer80(arg0, 0xA);
            break;

        case 3:
            Particle_ApproachPrimR(arg0, 0, 0x10);
            Particle_ApproachPrimG(arg0, 0, 0x20);
            if (Anim_HasReachedEnd(arg0->unk_14) != 0) {
                Particle_IncrementState(arg0);
            }
            break;

        case 4:
            Particle_ResetState(arg0);
            break;
    }
}

void Particle_ConfigureScaleSpeed(ParticleEffectInstance* arg0) {
    f32 sp1C = 0.6f;
    f32 sp18 = 0.0f;

    switch (GetSpecies(arg0->unk_10)) {
        case 0x3:
            sp1C = 1.0f;
            sp18 = 5.0f;
            break;

        case 0x22:
            sp1C = 1.0f;
            sp18 = 5.0f;
            break;

        case 0x4C:
            sp1C = 0.8f;
            sp18 = 5.0f;
            break;

        case 0x5E:
            sp1C = 0.8f;
            sp18 = 5.0f;
            break;

        case 0x80:
            sp1C = 0.8f;
            sp18 = 10.0f;
            break;

        case 0x82:
            sp18 = 20.0f;
            break;

        case 0x88:
            sp1C = 1.2f;
            sp18 = 10.0f;
            break;

        case 0x8E:
            sp1C = 1.2f;
            sp18 = 20.0f;
            break;

        case 0x91:
            sp1C = 1.2f;
            sp18 = 15.0f;
            break;

        case 0x95:
            sp18 = 10.0f;
            break;
    }

    Particle_SetScaleFactor1(arg0, sp1C);
    Particle_AddVelocityBackward(arg0, sp18);
}

void ParticleEffect_InitWithResource(ParticleEffectInstance* arg0) {
    arg0->unk_14 = AllocateGraphNode(arg0);
    if (arg0->unk_14 != NULL) {
        InitGraphNodeTexture(arg0->unk_14, 0x38);
        Particle_ConfigureScaleSpeed(arg0);
        Particle_SetPrimAlpha(arg0, 0);
        Particle_IncrementState(arg0);
    } else {
        Particle_ResetState(arg0);
    }
}

void ParticleEffect_StateHandler_4669C(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            ParticleEffect_InitWithResource(arg0);
            break;

        case 2:
            Particle_ApproachPrimAlphaWithCallback(arg0, 0xFF, 4);
            break;
    }
}

void Gfx_DrawParticleAlpha(Gfx* arg0, s32 arg1, u16 arg2) {
    ParticleEffectInstance* temp_v0 = GetGraphNodeData(gDefaultGraphRoot);

    gDPPipeSync(arg0++);

    gDPSetPrimColor(arg0++, 0, 0xC8, 255, 255, 255, temp_v0->prim_a);
    gDPSetEnvColor(arg0++, 255, 155, 0, 255);

    arg0 = Gfx_LoadParticleTextureTileFromStruct(arg0, arg1, 0x20, 5, 1, 0, 0, 0, -1, 0, 0, 0);

    gSPEndDisplayList(arg0++);
}

void Particle_CreateDisplayList_TypeA(s32 arg0, arg1_func_84344CE8* arg1) {
    if (arg0 == 2) {
        arg1->unk_18 = GfxAlloc(sizeof(Gfx) * 30);
        Gfx_DrawParticleAlpha(arg1->unk_18, arg1->unk_14, gAnimationFrame);
    }
}

void Gfx_DrawParticleTexture4b(Gfx* arg0, u8* arg1, UNUSED u16 arg2) {
    ParticleEffectInstance* temp_v0 = GetGraphNodeData(gDefaultGraphRoot);

    gDPPipeSync(arg0++);

    gDPSetPrimColor(arg0++, 0, 0, 255, 255, 255, temp_v0->prim_r);
    gDPSetEnvColor(arg0++, 255, 155, 0, 255);
    gDPSetCombineLERP(arg0++, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED,
                      0, 0, 0, COMBINED);
    gDPSetTextureLUT(arg0++, G_TT_NONE);
    gSPTexture(arg0++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);
    gDPLoadTextureBlock_4b(arg0++, arg1, G_IM_FMT_I, 32, 32, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                           G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

    gSPEndDisplayList(arg0++);
}

void Particle_CreateDisplayList_Texture4b(s32 arg0, arg1_func_84344CE8* arg1) {
    if (arg0 == 2) {
        arg1->unk_18 = GfxAlloc(sizeof(Gfx) * 30);
        Gfx_DrawParticleTexture4b(arg1->unk_18, arg1->unk_14, gAnimationFrame);
    }
}

void Gfx_DrawParticleGreenPrim(Gfx* arg0, u8* arg1, UNUSED u16 arg2) {
    ParticleEffectInstance* temp_v0 = GetGraphNodeData(gDefaultGraphRoot);

    gDPPipeSync(arg0++);

    gDPSetPrimColor(arg0++, 0, 0, 255, 255, 255, temp_v0->prim_g);
    gDPSetEnvColor(arg0++, 255, 255, 0, 255);
    gDPSetCombineLERP(arg0++, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED,
                      0, 0, 0, COMBINED);
    gDPSetTextureLUT(arg0++, G_TT_NONE);
    gSPTexture(arg0++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);
    gDPLoadTextureBlock_4b(arg0++, arg1, G_IM_FMT_I, 32, 32, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                           G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

    gSPEndDisplayList(arg0++);
}

void Particle_CreateDisplayList_GreenPrim(s32 arg0, arg1_func_84344CE8* arg1) {
    if (arg0 == 2) {
        arg1->unk_18 = GfxAlloc(sizeof(Gfx) * 30);
        Gfx_DrawParticleGreenPrim(arg1->unk_18, arg1->unk_14, gAnimationFrame);
    }
}

void ParticleEffect_RegisterHandlers_Default(void) {
    ParticleDef_CreateQuick(0, ParticleEffect_AnimState, &gParticleDefaultCallback, 0, 1, 0xA, 0, 0, 0);
    ParticleDef_CreateQuick(0, ParticleEffect_StateHandler_4669C, &gParticleDefaultCallback, 0, 1, 0xA, 0, 0, 0);
}

void ParticleEffect_RegisterAnimationCallbacks(void) {
    ParticleDef_CreateQuick(0, ParticleEffect_OffsetState, &gParticleDefaultCallback, 0, 1, 0xA, 0, 1, 0);
    ParticleDef_CreateQuick(2, ParticleEffect_OffsetState, &gParticleDefaultCallback, 0, 1, 0xA, 0, 2, 0);
    ParticleDef_CreateQuick(5, ParticleEffect_OffsetState, &gParticleDefaultCallback, 0, 1, 0xA, 0, 3, 0);
    ParticleDef_CreateQuick(8, ParticleEffect_OffsetState, &gParticleDefaultCallback, 0, 1, 0xA, 0, 0, 0);
    ParticleDef_CreateQuick(9, ParticleEffect_OffsetState, &gParticleDefaultCallback, 0, 1, 0xA, 0, 5, 0);
    ParticleDef_CreateQuick(0xA, ParticleEffect_OffsetState, &gParticleDefaultCallback, 0, 1, 0xA, 0, 6, 0);
    ParticleDef_CreateQuick(0xD, ParticleEffect_OffsetState, &gParticleDefaultCallback, 0, 1, 0xA, 0, 7, 0);
    ParticleDef_CreateFull(0xA, 3, 2, ParticleEffect_StateHandler_50DAC, &gParticleEffectData[0x3F], 0, 0x10, 0xA, 0, 0x11, 0);
}

void ParticleEffect_RegisterHandlers_Alternate(void) {
    ParticleDef_CreateQuick(0, ParticleEffect_AnimState, &gParticleDefaultCallback, 0, 1, 0xA, 0, 1, 0);
    ParticleDef_CreateQuick(0, ParticleEffect_StateHandler_4669C, &gParticleDefaultCallback, 0, 1, 0xA, 0, 0, 0);
}

void ParticleEffect_RegisterHandler_WithParticleData(void) {
    ParticleDef_CreateQuick(0, ParticleEffect_OffsetState, &gParticleDefaultCallback, 0, 1, 0xA, 0, 8, 0);
    ParticleDef_CreateFull(0xA, 3, 2, ParticleEffect_StateHandler_50DAC, &gParticleEffectData[0x3E], 0, 0x10, 0xA, 0, 0x11, 0);
}

void ParticleEffect_RegisterHandler_416B0(void) {
    ParticleDef_CreateQuick(0, ParticleEffect_StateHandlerA, &gParticleDefaultCallback, 0, 1, 0xA, 0, 0x23, 0);
}

void ParticleEffect_RegisterMultipleHandlers(void) {
    ParticleDef_CreateQuick(0, ParticleEffect_StateHandlerA, &gParticleDefaultCallback, 0, 1, 0xA, 0, 0x24, 0);
    ParticleDef_CreateQuick(8, ParticleEffect_StateHandlerA, &gParticleDefaultCallback, 0, 1, 0xA, 1, 0x24, 0);
    ParticleDef_CreateQuick(0x10, ParticleEffect_StateHandlerA, &gParticleDefaultCallback, 0, 1, 0xA, 2, 0x24, 0);
    ParticleDef_Create31FAC(0x5F, 0, 0xA, 0, 0xFF, 8);
    ParticleDef_CreateFull(0x5F, 8, 0xC, Particle_HandleState_Complex, &gParticleEffectData[0x42], 0, 8, 9, 0, 0x17, 6);
}

void ParticleEffect_InitLargeScale(ParticleEffectInstance* arg0) {
    arg0->unk_14 = AllocateGraphNode(arg0);
    if (arg0->unk_14 != NULL) {
        InitGraphNodeTexture(arg0->unk_14, 0x60);
        Particle_SetByteCA(arg0, 7);
        Particle_SetFlag(arg0, 0x200);
        Particle_SetScaleRaw1(arg0, 3.3f);
        Particle_SetPrimAlpha(arg0, 0);
        Particle_IncrementState(arg0);
    } else {
        Particle_ResetState(arg0);
    }
}

void ParticleEffect_StateHandler_47108(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            ParticleEffect_InitLargeScale(arg0);
            break;

        case 2:
            Particle_ApproachPrimAlpha(arg0, 0x9B, 8);
            break;

        case 3:
            Particle_ClearActiveFlag(arg0);
            break;
    }

    if (Particle_IsActive(arg0) != 0) {
        GetCameraOffsetPosition(&arg0->unk_50, 200.0f);
    }
}

void Gfx_DrawParticleCyanEnv(Gfx* arg0, arg1_func_8434E21C* arg1, UNUSED u16 arg2) {
    GetGraphNodeData(gDefaultGraphRoot);

    gDPPipeSync(arg0++);
    gDPSetEnvColor(arg0++, 155, 255, 255, 255);

    arg0 = Gfx_LoadParticleTextureTileFromStruct(arg0, arg1, 0x20, 5, 2, 1, 0xE, 0xF, 0, 4, 0xC, 5);

    gSPEndDisplayList(arg0++);
}

void Particle_CreateDisplayList_CyanEnv(s32 arg0, arg1_func_84344CE8* arg1) {
    if (arg0 == 2) {
        arg1->unk_18 = GfxAlloc(sizeof(Gfx) * 30);
        Gfx_DrawParticleCyanEnv(arg1->unk_18, arg1->unk_14, gAnimationFrame);
    }
}

void Gfx_DrawParticleBluePrim(Gfx* arg0, arg1_func_8434E21C* arg1, UNUSED u16 arg2) {
    ParticleEffectInstance* temp_v0 = GetGraphNodeData(gDefaultGraphRoot);

    gDPPipeSync(arg0++);
    gDPSetPrimColor(arg0++, 0, 0x80, 255, 255, 255, temp_v0->prim_a);
    gDPSetEnvColor(arg0++, 0, 255, 255, 255);

    arg0 = Gfx_LoadParticleTextureTileFromStruct(arg0, arg1, 0x20, 5, -3, -5, 0xD, 3, 0, -2, 0xF, 2);

    gSPEndDisplayList(arg0++);
}

void Particle_CreateDisplayList_BluePrim(s32 arg0, arg1_func_84344CE8* arg1) {
    if (arg0 == 2) {
        arg1->unk_18 = GfxAlloc(sizeof(Gfx) * 30);
        Gfx_DrawParticleBluePrim(arg1->unk_18, arg1->unk_14, gAnimationFrame);
    }
}

void ParticleEffect_RegisterHandlers_473BC(void) {
    ParticleDef_CreateQuick(0, ParticleEffect_StateHandlerA, &gParticleDefaultCallback, 0, 1, 0xE, 0, 0x25, 0);
    ParticleDef_CreateQuick(0, ParticleEffect_StateHandler_47108, &gParticleDefaultCallback, 0, 1, 0x14, 0, 0, 0);
}

void ParticleEffect_RegisterHandler_47448(void) {
    ParticleDef_CreateQuick(0, ParticleEffect_StateHandlerA, &gParticleDefaultCallback, 0, 1, 0xE, 0, 0x25, 0);
}

void ParticleEffect_AdjustParametersByAnimId(ParticleEffectInstance* arg0) {
    f32 var_fs0 = 0.0f;

    switch (GetSpecies(arg0->unk_10)) {
        case 0x5:
            Particle_AddVelocityBackward(arg0, 10.0f);
            break;

        case 0xC:
            var_fs0 = 20.0f;
            break;

        case 0xD:
            var_fs0 = -5.0f;
            Particle_AddVelocityBackward(arg0, 15.0f);
            break;

        case 0x34:
            var_fs0 = -10.0f;
            break;

        case 0x4A:
            var_fs0 = 10.0f;
            break;

        case 0x4D:
            var_fs0 = 10.0f;
            Particle_AddVelocityForward(arg0, 10.0f);
            break;

        case 0x5A:
            var_fs0 = -5.0f;
            Particle_AddVelocityForward(arg0, 5.0f);
            break;

        case 0x66:
            var_fs0 = -5.0f;
            break;

        case 0x6A:
            var_fs0 = 15.0f;
            break;

        case 0x91:
            var_fs0 = 15.0f;
            break;

        case 0x94:
            var_fs0 = -15.0f;
            break;

        case 0x97:
            var_fs0 = 20.0f;
            break;
    }

    if (var_fs0 != 0.0f) {
        Particle_AddVelocityYScaled(arg0, var_fs0);
    }
}

void ParticleEffect_StateHandler_47670(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            ParticleEffect_ConfigureState(arg0, 0);
            break;

        case 2:
            Particle_ProcessTimer80(arg0, arg0->unk_A6);
            break;

        case 3:
            Particle_ResetState(arg0);
            break;
    }
}

void ParticleEffect_InitStandard(ParticleEffectInstance* arg0) {
    Particle_SetScaleFactor1(arg0, 2.0f);
    Particle_AddVelocityBackward(arg0, 10.0f);
    SetPrimEnvColorFromPair(arg0, Particle_GetShortCF(arg0));
    Particle_SetPrimAlpha(arg0, 0xC8);
    Particle_SetParamC7(arg0, 1);
    Particle_SetRotationZ(arg0, RandomMod(0x10000));
    Particle_IncrementState(arg0);
}

void ParticleEffect_StateHandler_4775C(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            ParticleEffect_InitStandard(arg0);
            break;

        case 2:
            Particle_ApproachScaleFactor1WithCallback(arg0, 10.0f, 1.0f);
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

void ParticleEffect_InitRandomized(ParticleEffectInstance* arg0) {
    UNUSED s16 pad;
    s16 sp34;
    Vec3s sp2C;
    UNUSED s32 pad2[3];

    Particle_GetShortAC(arg0);
    sp34 = Particle_GetShortCF(arg0);
    Particle_SetRandomVelocityXYZ(arg0, 5, 5, 5);
    Particle_SetScaleFactor1(arg0, 1.5f);
    Particle_SetSpeed(arg0, 1.5f);
    sp2C.x = RandomMod(0x2000) - 0x1000;
    sp2C.y = RandomMod(0x10000);
    sp2C.z = 0;
    Particle_AddRotationDeltaVec(arg0, sp2C);
    Particle_AddTargetRotationXY(arg0, sp2C.x, sp2C.y);
    Particle_SetRotationDeltaXY(arg0, 0, 0);
    SetPrimEnvColorFromPair(arg0, sp34);
    Particle_SetPrimAlpha(arg0, 0x80);
    Particle_SetTimerA6(arg0, arg0->unk_AC * 2);
    Particle_DisableFlag4(arg0);
    Particle_IncrementState(arg0);
}

void ParticleEffect_StateHandler_47904(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            ParticleEffect_InitRandomized(arg0);
            break;

        case 2:
            if (Particle_DecrementTimerA6ToZeroWithCallback(arg0) != 0) {
                Particle_SetTimerA6(arg0, 0xA);
                Particle_EnableFlag4(arg0);
            }
            break;

        case 3:
            Particle_AnimLoopForwardComplete(arg0, 0, 7, 1, 2, 0);
            Particle_ApproachScaleFactor1(arg0, 2.5f, 0.25f);
            Particle_ApplyB2B4AndAddAll(arg0);
            Particle_AddVelocityYScaled(arg0, 0.5f);
            if (Particle_DecrementTimerA6ToZero(arg0) != 0) {
                Particle_ApproachPrimAlpha(arg0, 0x20, 0x10);
                Particle_ApproachPrimG(arg0, 0, 0x14);
                Particle_ApproachEnvR(arg0, 0, 0x14);
            }
            break;

        case 4:
            Particle_ClearActiveFlag(arg0);
            break;
    }
}

void ParticleEffect_InitVariantA(ParticleEffectInstance* arg0) {
    UNUSED s32 pad[2];
    UNUSED s16 pad2;
    s16 sp24;

    Particle_GetShortAC(arg0);
    sp24 = Particle_GetShortCF(arg0);
    Particle_GetShortCE(arg0);
    Particle_SetScaleFactor1(arg0, 1.0f);
    Particle_SetRandomVelocityXYZ(arg0, 0xF, 0xF, 0x14);
    Particle_SetSpeed(arg0, (RandomMod(0x32) * 0.02f) + 1.0f);
    SetPrimEnvColorFromPair(arg0, sp24);
    Particle_SetPrimAlpha(arg0, 0x80);
    Particle_DisableFlag4(arg0);
    Particle_IncrementState(arg0);
}

void ParticleEffect_StateHandler_47AF0(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            ParticleEffect_InitVariantA(arg0);
            break;

        case 2:
            if (Particle_DecrementTimerA6ToZeroWithCallback(arg0) != 0) {
                Particle_EnableFlag4(arg0);
                Particle_SetTimerA6(arg0, 5);
            }
            break;

        case 3:
            Particle_AnimLoopForwardComplete(arg0, 0, 7, 1, 2, 0);
            Particle_SetTargetVelocityY(arg0);
            if (Particle_DecrementTimerA6ToZero(arg0) != 0) {
                Particle_ApproachPrimG(arg0, 0, 0x14);
                Particle_ApproachEnvR(arg0, 0, 0x14);
                Particle_ApproachPrimAlpha(arg0, 0x20, 4);
            }
            break;

        case 4:
            Particle_ClearActiveFlag(arg0);
            break;
    }
}

void Gfx_DrawParticleCustomColors(Gfx* arg0, arg1_func_8434E21C* arg1, UNUSED u16 arg2) {
    ParticleEffectInstance* temp_v0 = GetGraphNodeData(gDefaultGraphRoot);

    gDPPipeSync(arg0++);

    gDPSetPrimColor(arg0++, 0, 0x78, temp_v0->prim_r, temp_v0->prim_g, temp_v0->prim_b, temp_v0->prim_a);
    gDPSetEnvColor(arg0++, temp_v0->env_r, temp_v0->env_g, temp_v0->env_b, temp_v0->unk_B0);
    gDPSetCombineLERP(arg0++, TEXEL1, TEXEL0, PRIM_LOD_FRAC, TEXEL0, TEXEL1, TEXEL0, PRIM_LOD_FRAC, TEXEL0, PRIMITIVE,
                      ENVIRONMENT, COMBINED, ENVIRONMENT, COMBINED, 0, PRIMITIVE, ENVIRONMENT);

    arg0 = Gfx_LoadParticleTextureTileFromStruct(arg0, arg1, 0x20, 5, 2, 0xA, 0xD, 0xF, -2, 5, 0xE, 0xF);

    gSPEndDisplayList(arg0++);
}

void Particle_CreateDisplayList_CustomColors(s32 arg0, arg1_func_84344CE8* arg1) {
    if (arg0 == 2) {
        arg1->unk_18 = GfxAlloc(sizeof(Gfx) * 30);
        Gfx_DrawParticleCustomColors(arg1->unk_18, arg1->unk_14, gAnimationFrame);
    }
}

void ParticleEffect_StateHandler_47D74(ParticleEffectInstance* arg0) {
    Particle_GetShortCE(arg0);

    switch (arg0->unk_B2) {
        case 1:
            ParticleEffect_ConfigureState(arg0, 2);
            Particle_SetScaleFactor1(arg0, 0.5f);
            Particle_SetShortB0(arg0, 0x64);
            SetPrimEnvColorFromPair(arg0, 0x17);
            Particle_SetTimerA6(arg0, 5);
            break;

        case 2:
            Particle_ApproachScaleFactor1(arg0, 7.0f, 0.25f);
            if (Particle_DecrementTimerA6ToZeroWithCallback(arg0) != 0) {
                Particle_SetTimerA6(arg0, 5);
            }
            break;

        case 3:
            Particle_ApproachScaleFactor1(arg0, 7.0f, 0.25f);
            AreBothColorsSupported(arg0, 0x1A, 0x19);
            if (Particle_DecrementTimerA6ToZero(arg0) != 0) {
                Particle_ApproachShortB0(arg0, 0, 8);
                Particle_ApproachPrimAlphaWithCallback(arg0, 0, 0x10);
            }
            break;

        case 4:
            Particle_ClearActiveFlag(arg0);
            break;
    }
}

void ParticleEffect_StateHandler_47E9C(ParticleEffectInstance* arg0) {
    s16 sp26 = Particle_GetShortCE(arg0);

    switch (arg0->unk_B2) {
        case 1:
            ParticleEffect_ConfigureState(arg0, 2);
            Particle_SetScaleFactor1(arg0, 0.5f);
            Particle_SetShortB0(arg0, 0x64);
            SetPrimEnvColorFromPair(arg0, 0x17);
            Particle_SetTimerA6(arg0, 5);

            switch (sp26) {
                case 0:
                    Particle_SetVelocityXScaled(arg0, 15.0f);
                    Particle_SetVelocityYScaled(arg0, 15.0f);
                    break;

                case 1:
                    Particle_SetVelocityXScaled(arg0, -15.0f);
                    Particle_SetVelocityZScaled(arg0, 15.0f);
                    Particle_SetVelocityYScaled(arg0, -10.0f);
                    break;

                case 2:
                    Particle_SetVelocityXScaled(arg0, -10.0f);
                    Particle_SetVelocityZScaled(arg0, -15.0f);
                    break;
            }
            break;

        case 2:
            Particle_ApproachScaleFactor1(arg0, 5.0f, 0.15f);
            if (Particle_DecrementTimerA6ToZeroWithCallback(arg0) != 0) {
                Particle_SetTimerA6(arg0, 5);
            }
            break;

        case 3:
            Particle_ApproachScaleFactor1(arg0, 5.0f, 0.15f);
            AreBothColorsSupported(arg0, 0x1A, 0x19);
            if (Particle_DecrementTimerA6ToZero(arg0) != 0) {
                Particle_ApproachShortB0(arg0, 0, 8);
                Particle_ApproachPrimAlphaWithCallback(arg0, 0, 0x10);
            }
            break;

        case 4:
            Particle_ClearActiveFlag(arg0);
            break;
    }
}

void ParticleEffect_StateHandler_48058(ParticleEffectInstance* arg0) {
    Particle_GetShortCE(arg0);

    switch (arg0->unk_B2) {
        case 1:
            ParticleEffect_ConfigureState(arg0, 2);
            Particle_SetScaleFactor1(arg0, 0.25f);
            Particle_SetShortB0(arg0, 0x64);
            SetPrimEnvColorFromPair(arg0, 0x17);
            Particle_SetTimerA6(arg0, 5);
            Particle_AddVelocityForward(arg0, 30.0f);
            break;

        case 2:
            Particle_ApproachScaleFactor1(arg0, 5.0f, 0.3f);
            if (Particle_DecrementTimerA6ToZeroWithCallback(arg0) != 0) {
                Particle_SetTimerA6(arg0, 5);
            }
            break;

        case 3:
            Particle_ApproachScaleFactor1(arg0, 5.0f, 0.3f);
            AreBothColorsSupported(arg0, 0x1A, 0x19);
            if (Particle_DecrementTimerA6ToZero(arg0) != 0) {
                Particle_ApproachShortB0(arg0, 0, 8);
                Particle_ApproachPrimAlphaWithCallback(arg0, 0, 0x10);
            }
            break;

        case 4:
            Particle_ClearActiveFlag(arg0);
            break;
    }
}

void ParticleEffect_InitComplex_48194(ParticleEffectInstance* arg0) {
    UNUSED s32 pad[2];
    s16 sp26 = Particle_GetShortAC(arg0);

    Particle_GetShortCE(arg0);
    Particle_GetShortCF(arg0);
    Particle_SetTimerA6(arg0, sp26 * 2);
    SetPrimEnvColorFromPair(arg0, Particle_GetShortCF(arg0));
    Particle_SetScaleFactor1(arg0, 1.2f);
    Particle_SetScaleFactor2(arg0, 1.0f);
    Particle_SetScaleFactor3(arg0, 0.02f);
    Particle_SetRandomVelocityXYZ(arg0, 5, 0xF, 0xF);
    Particle_AddVelocityYScaled(arg0, 10.0f);
    Particle_SetSpeed(arg0, (RandomMod(0xA) * 0.5f) + 8.0f);
    SetPrimColorFromPalette(arg0, 0x19);
    SetEnvColorFromPalette(arg0, 0x19);
    Particle_SetPrimAlpha(arg0, 0xC8);
    Particle_SetShortAE(arg0, 4);
    Particle_DisableFlag4(arg0);
    Particle_IncrementState(arg0);
}

void ParticleEffect_StateHandler_482D4(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            ParticleEffect_InitComplex_48194(arg0);
            break;

        case 2:
            if (Particle_DecrementTimerA6ToZeroWithCallback(arg0) != 0) {
                Particle_EnableFlag4(arg0);
                Particle_SetTimerA6(arg0, 4);
            }
            break;

        case 3:
            Particle_ApproachScaleFactor2(arg0);
            Particle_AnimLoopForwardComplete(arg0, 1, 7, 1, 2, 0);
            Particle_SetTargetVelocityBackward(arg0);
            Particle_ApproachPrimG(arg0, 0, 0x20);
            Particle_ApproachEnvG(arg0, 0, 0x20);
            if (Particle_DecrementTimerA6ToZero(arg0) != 0) {
                break;
            }
            break;

        case 4:
            Particle_ClearActiveFlag(arg0);
            break;
    }
}

void ParticleEffect_InitComplex_483D4(ParticleEffectInstance* arg0) {
    UNUSED s32 pad[2];
    s16 sp26 = Particle_GetShortAC(arg0);
    UNUSED s16 pad2;
    s16 sp22;

    Particle_GetShortCE(arg0);
    sp22 = Particle_GetShortCF(arg0);
    Particle_SetTimerA6(arg0, sp26 * 2);
    SetPrimEnvColorFromPair(arg0, Particle_GetShortCF(arg0));
    Particle_SetScaleFactor1(arg0, 1.0f);
    Particle_SetScaleFactor2(arg0, 0.5f);
    Particle_SetScaleFactor3(arg0, 0.01f);
    Particle_SetRandomVelocityXYZ(arg0, 0xA, 0, 0xF);
    Particle_AddVelocityForward(arg0, 10.0f);
    Particle_AddVelocityYScaled(arg0, 5.0f);
    Particle_SetSpeed(arg0, (RandomMod(0xA) * 0.5f) + 8.0f);
    SetPrimEnvColorFromPair(arg0, sp22);
    Particle_SetPrimAlpha(arg0, 0xB4);
    Particle_SetShortAE(arg0, 4);
    Particle_DisableFlag4(arg0);
    Particle_IncrementState(arg0);
}

void ParticleEffect_StateHandler_48514(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            ParticleEffect_InitComplex_483D4(arg0);
            break;

        case 2:
            if (Particle_DecrementTimerA6ToZeroWithCallback(arg0) != 0) {
                Particle_EnableFlag4(arg0);
                Particle_SetTimerA6(arg0, 4);
            }
            break;

        case 3:
            Particle_ApproachPrimAlphaWithCallback(arg0, 0x40, 0x10);
            if (Particle_DecrementTimerA6ToZero(arg0) != 0) {
                AreBothColorsSupported(arg0, 0x16, 0x20);
            }
            Particle_ApproachSpeedScaled(arg0, 4.0f, 0.5f);
            Particle_SetTargetVelocityBackward(arg0);
            break;

        case 4:
            Particle_ClearActiveFlag(arg0);
            break;
    }

    if (Particle_HasFlag4(arg0) != 0) {
        Particle_ApproachScaleFactor2(arg0);
        Particle_AnimLoopForward(arg0, 0, 7, 1, 2, 0);
    }
}

void ParticleEffect_RegisterAll_48630(void) {
    ParticleDef_CreateDefault(0, 0x10, 6);
    ParticleDef_CreateQuick(0, ParticleEffect_StateHandler_47670, &gParticleDefaultCallback, 0x19, 1, 0xE, 0, 0x27, 0);
    ParticleDef_Create32E6CAlt(0, 0, 4, 0x1C, 0x80);
    ParticleDef_CreateQuick(0x16, ParticleEffect_StateHandler_4775C, &gParticleEffectData[0x54], 0, 1, 0xC, 0, 0x25, 0);
    ParticleDef_CreateBC20CDAlt(0x1A, 3, 0x20, 0x1C, 0x96);
    ParticleDef_CreateQuick(0x1B, ParticleEffect_StateHandler_47D74, &gParticleDefaultCallback, 0, 1, 9, 0, 0x21, 0);
    ParticleDef_CreateQuick(0x1E, ParticleEffect_StateHandler_47E9C, &gParticleDefaultCallback, 0, 1, 9, 0, 0x21, 0);
    ParticleDef_CreateQuick(0x22, ParticleEffect_StateHandler_47E9C, &gParticleDefaultCallback, 0, 1, 9, 0, 0x21, 1);
    ParticleDef_CreateQuick(0x26, ParticleEffect_StateHandler_47E9C, &gParticleDefaultCallback, 0, 1, 9, 0, 0x21, 2);
    ParticleDef_CreateQuick(0x28, ParticleEffect_StateHandler_47904, &gParticleEffectData[0x48], 0, 6, 0x10, 9, 0x1A, 0);
    ParticleDef_CreateFull(0x32, 2, 2, ParticleEffect_StateHandler_47AF0, &gParticleEffectData[0x4A], 0, 1, 9, 0, 0x1A, 0);
    ParticleDef_CreateFull(0x33, 2, 2, ParticleEffect_StateHandler_47AF0, &gParticleEffectData[0x4A], 0, 1, 9, 0, 0x1A, 0);
    ParticleDef_CreateFull(0x34, 2, 2, ParticleEffect_StateHandler_47AF0, &gParticleEffectData[0x4A], 0, 1, 9, 0, 0x1A, 0);
    ParticleDef_CreateFull(0x36, 2, 2, ParticleEffect_StateHandler_47AF0, &gParticleEffectData[0x4A], 0, 1, 9, 0, 0x1A, 0);
    ParticleDef_Create31EAC(0x16, 0xA, 0, 0xFF, 0x40);
    ParticleDef_Create31EAC(0x24, 0xA, 0xFF, 0xDC, 0xC);
    ParticleDef_Create321BCAlt(0x28, 0xA, 0x19, 0x10, 0xDC);
    ParticleDef_Create321BCAlt(0x38, 0x19, 0x13, 0x10, 0xDC);
    ParticleDef_Create321BCAlt(0x40, 0x13, 0x10, 0x10, 0xDC);
    ParticleDef_Create31EAC(0x48, 0x10, 0xDC, 0xB4, 6);
}

void ParticleEffect_RegisterAll_489FC(void) {
    ParticleDef_CreateDefault(0, 0xFF, 6);
    ParticleDef_CreateQuick(0, ParticleEffect_StateHandler_48058, &gParticleDefaultCallback, 0, 1, 0xB, 0, 0x21, 0);
    ParticleDef_CreateQuick(4, ParticleEffect_StateHandler_48058, &gParticleDefaultCallback, 0, 1, 0xB, 0, 0x21, 0);
    ParticleDef_CreateFull(0xA, 8, 4, ParticleEffect_StateHandlerA, &gParticleDefaultCallback, 0, 1, 0xC, 0, 0x2B, 0);
    ParticleDef_CreateFull(0xC, 8, 5, ParticleEffect_StateHandler_34F84, &gParticleEffectData[0x46], 0, 5, 0x10, 9, 0x48, 0);
    ParticleDef_CreateFull(0xC, 4, 0xA, ParticleEffect_StateHandler_482D4, &gParticleEffectData[0x4A], 0, 4, 0xB, 9, 0, 0);
    ParticleDef_CreateFull(0xC, 4, 0xA, ParticleEffect_StateHandler_48514, &gParticleEffectData[0x4F], 0, 4, 0xE, 9, 0x1A, 0);
    ParticleDef_Create31EAC(3, 0xA, 0, 0xFF, 0x40);
    ParticleDef_Create31EAC(0xA, 0xA, 0xFF, 0xE6, 5);
    ParticleDef_Create321BCAlt(0x10, 0xA, 0x19, 0x10, 0xDC);
    ParticleDef_Create321BCAlt(0x18, 0x19, 0xB, 0x10, 0xD2);
    ParticleDef_Create321BCAlt(0x28, 0xB, 0x10, 0x10, 0xC8);
    ParticleDef_Create31EAC(0x30, 0x10, 0xC8, 0xB4, 6);
}

void ParticleEffect_Noop_48C6C(UNUSED s32 arg0, UNUSED s32 arg1) {
}

void ParticleEffect_Noop_48C78(UNUSED s32 arg0, UNUSED s32 arg1) {
}

void ParticleEffect_InitSparkle(ParticleEffectInstance* arg0) {
    s16 sp26 = Particle_GetShortCF(arg0);

    arg0->unk_14 = AllocateParticleNode(arg0);
    if (arg0->unk_14 != NULL) {
        if (sp26 == 0) {
            InitGraphNodeTexture(arg0->unk_14, 0x55);
        } else {
            InitGraphNodeTexture(arg0->unk_14, 0x63);
        }
        SetAnimChannel(arg0->unk_14, 0x56);
        Particle_SetFlag(arg0, 0x200);
        Particle_SetByteCA(arg0, 7);
        Particle_SetScaleRaw1(arg0, 1.0f);
        SetPrimEnvColorFromPair(arg0, 0x24);
        Particle_SetPrimAlpha(arg0, 0);
        Particle_IncrementState(arg0);
    } else {
        Particle_ResetState(arg0);
    }
}

void ParticleEffect_StateHandler_48D4C(ParticleEffectInstance* arg0) {
    s16 sp26 = Particle_GetShortCF(arg0);
    s32 sp20 = 0;
    f32 var_fv0;

    switch (arg0->unk_B2) {
        case 1:
            ParticleEffect_InitSparkle(arg0);
            break;

        case 2:
            Particle_ProcessTimer80(arg0, 0xE);
            Particle_ApproachPrimG(arg0, 0xFF, 7);
            Particle_ApproachPrimB(arg0, 0xFF, 0x13);
            Particle_ApproachEnvG(arg0, 0xFF, 0x13);
            Particle_ApproachPrimAlpha(arg0, 0xFF, 0x13);
            break;

        case 3:
            Particle_ProcessTimer80(arg0, 0x10);
            Particle_ApproachPrimB(arg0, 0, 0x11);
            Particle_ApproachEnvG(arg0, 0, 0x11);
            Particle_ApproachPrimAlpha(arg0, 0, 0x11);
            break;

        case 4:
            if (Anim_HasReachedEnd(arg0->unk_14) != 0) {
                Particle_ClearActiveFlag(arg0);
            }
            break;
    }

    if (Particle_IsActive(arg0) != 0) {
        if (GetSpecies(arg0->unk_10) == 0x5F) {
            sp20 = 1;
        } else if (GetSpecies(arg0->unk_10) == 0x82) {
            sp20 = 1;
        }

        if (sp26 == 0) {
            if (sp20 != 0) {
                var_fv0 = 120.0f;
            } else {
                var_fv0 = 170.0f;
            }
            GetCameraOffsetPosition(&arg0->unk_50, var_fv0);
        } else {
            if (sp20 != 0) {
                var_fv0 = 90.0f;
            } else {
                var_fv0 = 140.0f;
            }
            GetCameraOffsetPosition(&arg0->unk_50, var_fv0);
        }
    }
}

void Gfx_DrawParticleFromTempColors(Gfx* arg0, s32 arg1, u16 arg2) {
    ParticleEffectInstance* temp_v0 = GetGraphNodeData(gDefaultGraphRoot);

    gDPPipeSync(arg0++);

    gDPSetPrimColor(arg0++, 0, 0, temp_v0->prim_r, temp_v0->prim_g, temp_v0->prim_b, temp_v0->prim_a);
    gDPSetEnvColor(arg0++, temp_v0->env_r, temp_v0->env_g, temp_v0->env_b, 0);

    arg0 = Gfx_LoadParticleTextureTileFromStruct(arg0, arg1, 0x20, 5, 0, 0, 0, 0, 0, 0, 0, 0);

    gSPEndDisplayList(arg0++);
}

void Particle_CreateDisplayList_TempColors(s32 arg0, arg1_func_84344CE8* arg1) {
    if (arg0 == 2) {
        arg1->unk_18 = GfxAlloc(sizeof(Gfx) * 30);
        Gfx_DrawParticleFromTempColors(arg1->unk_18, arg1->unk_14, gAnimationFrame);
    }
}

void ParticleEffect_RegisterHandler_49058(void) {
    ParticleDef_CreateQuick(0, ParticleEffect_StateHandler_48D4C, &gParticleDefaultCallback, 0, 1, 0x14, 0, 0, 0);
}

void ParticleEffect_RegisterHandler_490A8(void) {
    ParticleDef_CreateDefault(0, 0x20, 0);
    ParticleDef_CreateQuick(0, ParticleEffect_StateHandler_48D4C, &gParticleDefaultCallback, 0, 1, 0x14, 0, 0, 0);
}

void ParticleEffect_RegisterHandler_49108(void) {
    ParticleDef_CreateQuick(0, ParticleEffect_StateHandler_48D4C, &gParticleDefaultCallback, 0, 1, 0x14, 0, 1, 0);
}

void ParticleEffect_Trigger56A74(void) {
    ParticleEffect_SimpleSetup();
}

void ParticleEffect_ConfigureAndTrigger_4917C(void) {
    ParticleDef_Create31EAC(0, 0xC, 0, 0xFF, 0x40);
    ParticleEffect_SimpleSetup();
    ParticleDef_Create31EAC(0x30, 0xC, 0xFF, 0, 2);
}

void Gfx_DrawParticleVariant_D4(Gfx* arg0, u8* arg1, UNUSED u16 arg2) {
    GetGraphNodeData(gDefaultGraphRoot);
    arg0 = Gfx_LoadParticleTextureTile(arg0, arg1, 0x20, 5, -4, -4, 0xD, 6, 4, 4, 0xF, 1);

    gSPEndDisplayList(arg0++);
}

void Particle_CreateDisplayList_Variant_D4(s32 arg0, arg1_func_84344CE8* arg1) {
    if (arg0 == 2) {
        arg1->unk_18 = GfxAlloc(sizeof(Gfx) * 30);
        Gfx_DrawParticleVariant_D4(arg1->unk_18, arg1->unk_14, gAnimationFrame);
    }
}

void Gfx_DrawParticleVariant_AC(Gfx* arg0, u8* arg1, UNUSED u16 arg2) {
    GetGraphNodeData(gDefaultGraphRoot);
    arg0 = Gfx_LoadParticleTextureTile(arg0, arg1, 0x20, 5, 1, -1, 0xE, 0xE, -1, 1, 2, 2);

    gSPEndDisplayList(arg0++);
}

void Particle_CreateDisplayList_Variant_AC(s32 arg0, arg1_func_84344CE8* arg1) {
    if (arg0 == 2) {
        arg1->unk_18 = GfxAlloc(sizeof(Gfx) * 30);
        Gfx_DrawParticleVariant_AC(arg1->unk_18, arg1->unk_14, gAnimationFrame);
    }
}

void ParticleEffect_RegisterHandler_49384(void) {
    ParticleDef_CreateQuick(0, ParticleEffect_StateHandlerA, &gParticleDefaultCallback, 0, 1, 2, 0, 0x28, 0);
    ParticleDef_CreateFull(4, 8, 0xC, Particle_HandleState_Complex, &gParticleEffectData[0x42], 0, 8, 9, 0, 0x22, 6);
}

f32 ParticleEffect_GetScaleFactorByAnimId(ParticleEffectInstance* arg0) {
    f32 sp1C = 1.0f;

    switch (GetSpecies(arg0->unk_10)) {
        case 0x3B:
            sp1C = 1.45f;
            break;

        case 0x5F:
            Particle_AddVelocityLeft(arg0, 20.0f);
            sp1C = 0.9f;
            break;

        case 0x82:
            sp1C = 0.9f;
            break;
    }
    return sp1C;
}

void ParticleEffect_StateHandler_494AC(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            ParticleEffect_ConfigureState(arg0, 0);
            break;

        case 2:
            break;

        case 3:
            Particle_ResetState(arg0);
            break;
    }
}

void ParticleEffect_RegisterHandlers_49504(void) {
    ParticleDef_CreateQuick(0, ParticleEffect_StateHandler_494AC, &gParticleDefaultCallback, 0, 1, 0xA, 0, 0x29, 0);
    ParticleDef_CreateFull(5, 2, 0xA, ParticleEffect_GravityAdjust, &gParticleEffectData[0x4A], 0, 2, 0xA, 0, 0x44, 9);
    ParticleDef_CreateFull(0xA, 5, 6, ParticleEffect_ConditionalStop, &gParticleEffectData[0x30], 0, 3, 0xA, 0, 0x44, 0xB);
}

void ParticleEffect_ApplySpecialEffect_495F0(ParticleEffectInstance* arg0) {
    if (GetSpecies(arg0->unk_10) == 0x5F) {
        Particle_AddVelocityLeft(arg0, 20.0f);
    }
}

void ParticleEffect_RegisterHandler_49628(void) {
    ParticleDef_CreateQuick(0, ParticleEffect_StateHandlerB, &gParticleDefaultCallback, 0, 1, 0xA, 0, 0x16, 0);
}

void ParticleEffect_RegisterHandlers_4967C(void) {
    ParticleDef_CreateQuick(0, ParticleEffect_StateHandlerB, &gParticleDefaultCallback, 0, 1, 0xA, 0, 0x1D, 0);
    ParticleDef_CreateFull(0, 3, 3, ParticleEffect_FireworkMain, &gParticleEffectData[0x34], 0, 1, 0xE, 9, 0, 0xF);
    ParticleDef_CreateFull(4, 1, 4, ParticleEffect_GravityAdjust, &gParticleEffectData[0x4A], 0, 8, 0x1B, 0, 0x44, 0xA);
    ParticleDef_CreateQuick(4, ParticleEffect_ConditionalStop, &gParticleEffectData[0x30], 0, 0xC, 0x1B, 0, 0x44, 0xB);
}

void ParticleEffect_AdjustVerticalOffset_497A8(ParticleEffectInstance* arg0) {
    f32 sp1C = 0.0f;

    switch (GetSpecies(arg0->unk_10)) {
        case 0x57:
            sp1C = -20.0f;
            Particle_AddVelocityLeft(arg0, 10.0f);
            break;

        case 0x5F:
            sp1C = -20.0f;
            Particle_AddVelocityLeft(arg0, 15.0f);
            break;
    }
    Particle_AddVelocityYScaled(arg0, sp1C);
}

void ParticleEffect_RegisterHandler_49830(void) {
    ParticleDef_CreateQuick(0, ParticleEffect_StateHandlerA, &gParticleDefaultCallback, 0, 1, 0xB, 0, 0, 0);
    ParticleDef_CreateNullType19(0x28, 1);
    ParticleDef_CreateFull(4, 4, 3, Particle_HandleState_Complex, &gParticleEffectData[0x42], 0, 4, 0xB, 0, 0x17, 0xA);
}

void ParticleEffect_RegisterHandler_498D8(void) {
    ParticleDef_CreateQuick(0, ParticleEffect_StateHandlerA, &gParticleDefaultCallback, 0, 1, 4, 0, 1, 0);
    ParticleDef_CreateBC20CD(0x1D, 2, 0x20, 0x14);
}

void ParticleEffect_AdjustSizeByAnimId(ParticleEffectInstance* arg0) {
    f32 sp1C = 0.0f;
    f32 sp18 = 0.0f;

    switch (GetSpecies(arg0->unk_10)) {
        case 0x3B:
            sp1C = 30.0f;
            break;

        case 0x4F:
            sp18 = 10.0f;
            break;

        case 0x66:
            sp1C = 15.0f;
            break;
    }

    if (sp18 != 0.0f) {
        Particle_AddVelocityForward(arg0, sp18);
    }

    if (sp1C != 0.0f) {
        Particle_SetVelocityYScaled(arg0, sp1C);
    }
}

void ParticleEffect_RegisterDefaultTexture(void) {
    ParticleDef_CreateQuick(0, ParticleEffect_StateHandlerA, &gParticleDefaultCallback, 0, 1, 0xB, gParticleTexture_Default, 2, 0);
}

void ParticleEffect_InitWithResource_A70(ParticleEffectInstance* arg0) {
    Particle_GetByteCD(arg0);
    arg0->unk_14 = AllocateGraphNode(arg0);
    if (arg0->unk_14 != NULL) {
        InitWaterAnimNode(arg0->unk_14, 0x71, 0x72);
        Particle_SetScaleFactor1(arg0, 1.0f);
        Particle_SetTimerA6(arg0, 0x1E);
        Particle_IncrementState(arg0);
    } else {
        Particle_ResetState(arg0);
    }
}

void ParticleEffect_StateHandler_49AE8(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            ParticleEffect_InitWithResource_A70(arg0);
            break;

        case 2:
            if (Anim_HasReachedEnd(arg0->unk_14) != 0) {
                Particle_ClearActiveFlag(arg0);
            }
            break;
    }
}

void ParticleEffect_InitWithOffsets_B50(ParticleEffectInstance* arg0) {
    s16 sp26 = Particle_GetByteCD(arg0);

    arg0->unk_14 = AllocateGraphNode(arg0);
    if (arg0->unk_14 != NULL) {
        switch (sp26) {
            case 0:
                Particle_SetVelocityScaledXYZ(arg0, 8.0f, 0.0f, -10.0f);
                break;

            case 1:
                Particle_SetVelocityScaledXYZ(arg0, -10.0f, 0.0f, 12.0f);
                break;

            case 2:
                Particle_SetVelocityScaledXYZ(arg0, 0.0f, 0.0f, -2.0f);
                break;

            case 3:
                Particle_SetVelocityScaledXYZ(arg0, 15.0f, 0.0f, 3.0f);
                break;
        }

        InitWaterAnimNode(arg0->unk_14, 0x6E, 0x6F);
        Particle_SetScaleFactor1(arg0, 1.0f);
        Particle_SetTimerA6(arg0, 0x1E);
        Particle_IncrementState(arg0);
    } else {
        Particle_ResetState(arg0);
    }
}

void ParticleEffect_StateHandler_49C74(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            ParticleEffect_InitWithOffsets_B50(arg0);
            break;

        case 2:
            Particle_DecrementTimerA6ToZeroWithCallback(arg0);
            break;

        case 3:
            Particle_ApproachScaleFactor1WithCallback(arg0, 0.0f, 0.05f);
            Particle_ApproachPrimAlphaWithCallback(arg0, 0, 0x10);
            break;

        case 4:
            Particle_ResetState(arg0);
            break;
    }
}

void Gfx_DrawParticlePaletteBased(Gfx* arg0, u8* arg1, UNUSED u16 arg2) {
    UNUSED s32 pad[2];
    s16 sp2E = Particle_GetShortCF(GetGraphNodeData(gDefaultGraphRoot));
    u8 sp2D;
    u8 sp2C;
    u8 sp2B;
    u8 sp2A;
    u8 sp29;
    u8 sp28;

    gDPLoadTextureBlock(arg0++, arg1, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, 0, G_TX_NOMIRROR | G_TX_WRAP,
                        G_TX_NOMIRROR | G_TX_WRAP, 5, 5, G_TX_NOLOD, G_TX_NOLOD);

    Gfx_ScrollTextureToDL(arg0++, 5, 0, 0x20, 0x20);

    switch (sp2E) {
        case 0:
            sp2D = 0x96;
            sp2C = 0x32;
            sp2B = 0x32;
            sp2A = 0;
            sp29 = 0;
            sp28 = 0;
            break;

        case 1:
            sp2D = 0x78;
            sp2C = 0x96;
            sp2B = 0;
            sp2A = 0x64;
            sp29 = 0x78;
            sp28 = 0;
            break;

        case 2:
            sp2D = 0x46;
            sp2C = 0;
            sp2B = 0x78;
            sp2A = 0x64;
            sp29 = 0;
            sp28 = 0x96;
            break;

        case 3:
            sp2D = 0x64;
            sp2C = 0x96;
            sp2B = 0x96;
            sp2A = 0x64;
            sp29 = 0x96;
            sp28 = 0x96;
            break;
    }

    gDPSetPrimColor(arg0++, 0, 0xFF, sp2D, sp2C, sp2B, 255);
    gDPSetEnvColor(arg0++, sp2A, sp29, sp28, 255);

    gSPEndDisplayList(arg0++);
}

void Gfx_ParticlePaletteCallback(s32 arg0, arg1_func_84344CE8* arg1) {
    if (arg0 == 2) {
        arg1->unk_18 = GfxAlloc(sizeof(Gfx) * 30);
        Gfx_DrawParticlePaletteBased(arg1->unk_18, arg1->unk_14, gAnimationFrame);
    }
}

void func_84349FC8(Gfx* arg0, UNUSED arg1_func_8434E21C* arg1, UNUSED u16 arg2) {
    Fragment2_1GraphNode* sp24 = gDefaultGraphRoot;
    s32 tmp = GetGraphNodeData(gDefaultGraphRoot);
    UNUSED u8 sp1F;
    UNUSED u8 sp1E;
    u8 sp1D;
    u8 sp1C;
    u8 sp1B;
    u8 sp1A;
    u8 sp19;
    u8 sp18;

    switch (Particle_GetShortCF(tmp)) {
        case 0:
            sp1D = 0xFF;
            sp1C = 0x96;
            sp1B = 0x32;
            sp1A = 0;
            sp19 = 0;
            sp18 = 0;
            break;

        case 1:
            sp1D = 0xFF;
            sp1C = 0xFF;
            sp1B = 0xFF;
            sp1A = 0x96;
            sp19 = 0xB4;
            sp18 = 0;
            break;

        case 2:
            sp1D = 0xFF;
            sp1C = 0xFF;
            sp1B = 0xFF;
            sp1A = 0x96;
            sp19 = 0;
            sp18 = 0xC8;
            break;

        case 3:
            sp1D = 0x64;
            sp1C = 0xFF;
            sp1B = 0xFF;
            sp1A = 0xC8;
            sp19 = 0xFF;
            sp18 = 0xFF;
            break;
    }

    gDPSetCombineLERP(arg0++, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED,
                      0, 0, 0, COMBINED);
    gDPSetPrimColor(arg0++, 0, 0xFF, sp1D, sp1C, sp1B, sp24->unk_01D);
    gDPSetEnvColor(arg0++, sp1A, sp19, sp18, 255);

    gSPEndDisplayList(arg0++);
}

void Gfx_ParticlePaletteCallback2(s32 arg0, arg1_func_84344CE8* arg1) {
    if (arg0 == 2) {
        arg1->unk_18 = GfxAlloc(sizeof(Gfx) * 30);
        func_84349FC8(arg1->unk_18, arg1->unk_14, gAnimationFrame);
    }
}

s16 Particle_GetPaletteIndex(void) {
    s16 sp1E;

    switch (GetActionScriptId()) {
        case 0x7C:
            sp1E = 0;
            break;

        case 0x33:
            sp1E = 1;
            break;

        case 0x5C:
            sp1E = 2;
            break;

        case 0x7A:
            sp1E = 3;
            break;
    }

    return sp1E;
}

s16 Particle_GetPaletteColorA(void) {
    s16 sp1E;

    switch (GetActionScriptId()) {
        case 0x7C:
            sp1E = 0x12;
            break;

        case 0x33:
            sp1E = 0x2B;
            break;

        case 0x5C:
            sp1E = 0x3E;
            break;

        case 0x7A:
            sp1E = 0x39;
            break;
    }

    return sp1E;
}

s16 Particle_GetPaletteColorB(void) {
    s16 sp1E;

    switch (GetActionScriptId()) {
        case 0x7C:
            sp1E = 8;
            break;

        case 0x33:
            sp1E = 0x33;
            break;

        case 0x5C:
            sp1E = 0x33;
            break;

        case 0x7A:
            sp1E = 0x33;
            break;
    }

    return sp1E;
}

void ParticleEffect_PaletteBurst(void) {
    ParticleDef_CreateQuick(0, ParticleEffect_StateHandler_49AE8, &gParticleDefaultCallback, 0, 1, 0x11, gParticleTexture_Default, Particle_GetPaletteIndex(), 0);
}

void ParticleEffect_PaletteMultiBurst(void) {
    s16 sp4E;
    s16 sp44;
    s16 sp4A;

    sp4E = Particle_GetPaletteIndex();
    sp44 = Particle_GetPaletteColorA();
    sp4A = Particle_GetPaletteColorB();

    ParticleDef_Create31EAC(4, sp44, 0, 0xFF, 0x10);
    ParticleDef_CreateQuick(0, ParticleEffect_StateHandler_49C74, &gParticleDefaultCallback, 0, 1, 0xA, 0, sp4E, 0);
    ParticleDef_CreateQuick(4, ParticleEffect_StateHandler_49C74, &gParticleDefaultCallback, 0, 1, 0xA, 1, sp4E, 0);
    ParticleDef_CreateQuick(8, ParticleEffect_StateHandler_49C74, &gParticleDefaultCallback, 0, 1, 0xA, 2, sp4E, 0);
    ParticleDef_CreateQuick(0xC, ParticleEffect_StateHandler_49C74, &gParticleDefaultCallback, 0, 1, 0xA, 3, sp4E, 0);
    ParticleDef_Create31EAC(0x28, sp44, 0xFF, 0, 0x10);
    ParticleDef_CreateFull(6, 4, 0xA, ParticleEffect_BasicSetupHandler, &gParticleEffectData[0x3D], 0, 1, 9, 0, sp4A, 0);
    ParticleDef_CreateFull(7, 8, 5, ParticleEffect_BasicSetupHandler, &gParticleEffectData[0x3D], 0, 1, 9, 0, sp4A, 0);
}

f32 ParticleEffect_SpeciesAdjustA(ParticleEffectInstance* arg0) {
    f32 sp1C = 0.5f;
    f32 sp18 = 0.0f;

    switch (GetSpecies(arg0->unk_10)) {
        case 0x57:
            sp18 = -15.0f;
            break;

        case 0x5F:
            sp1C = 0.3f;
            break;

        case 0x82:
            sp18 = 10.0f;
            break;

        case 0x83:
            sp1C = 0.4f;
            sp18 = 7.0f;
            break;
    }

    Particle_SetPrimAlpha(arg0, 0);
    Particle_AddVelocityYScaled(arg0, sp18 + 5.0f);
    return sp1C;
}

void Gfx_ParticleTextureTileCallback(Gfx* arg0, arg1_func_8434E21C* arg1, UNUSED u16 arg2) {
    GetGraphNodeData(gDefaultGraphRoot);
    arg0 = Gfx_LoadParticleTextureTileFromStruct(arg0, arg1, 0x20, 5, 0, 0, 1, 1, 0, -3, 1, 1);

    gSPEndDisplayList(arg0++);
}

void Gfx_ParticleTextureTileCallback2(s32 arg0, arg1_func_84344CE8* arg1) {
    if (arg0 == 2) {
        arg1->unk_18 = GfxAlloc(sizeof(Gfx) * 30);
        Gfx_ParticleTextureTileCallback(arg1->unk_18, arg1->unk_14, gAnimationFrame);
    }
}

void Gfx_ParticleRedPrimCallback(Gfx* arg0, UNUSED arg1_func_8434E21C* arg1, UNUSED u16 arg2) {
    ParticleEffectInstance* temp_v0 = GetGraphNodeData(gDefaultGraphRoot);

    gDPPipeSync(arg0++);

    gDPSetPrimColor(arg0++, 0, 0, 255, 0, 0, temp_v0->prim_a);
    gSPEndDisplayList(arg0++);
}

void Gfx_ParticleRedPrimCallback2(s32 arg0, arg1_func_84344CE8* arg1) {
    if (arg0 == 2) {
        arg1->unk_18 = GfxAlloc(sizeof(Gfx) * 30);
        Gfx_ParticleRedPrimCallback(arg1->unk_18, arg1->unk_14, gAnimationFrame);
    }
}

void ParticleEffect_SimpleBurst(void) {
    ParticleDef_CreateDefault(0, 0x10, 6);
    ParticleDef_CreateQuick(0, ParticleEffect_StateHandlerC, &gParticleDefaultCallback, 0x64, 1, 0xB, 0, 3, 6);
}

void ParticleEffect_SimpleCallback(void) {
    ParticleDef_CreateQuick(0, ParticleEffect_StateHandlerA, &gParticleDefaultCallback, 0, 1, 0xA, 0, 0x26, 0);
}

void ParticleEffect_SimpleBurstScript(void) {
    UNUSED s16 pad;
    s16 sp34;

    switch (GetActionScriptId()) {
        case 0x59:
            sp34 = 0x10;
            break;

        case 0x5A:
            sp34 = 0;
            break;
    }

    ParticleDef_CreateDefault(0, 0x10, sp34);
    ParticleDef_CreateQuick(0, ParticleEffect_StateHandlerA, &gParticleDefaultCallback, 0, 1, 0xA, 0, 0x26, 0);
}

void func_8434A930(void) {
    ParticleDef_CreateQuick(6, ParticleEffect_StateHandlerB, &gParticleDefaultCallback, 0, 1, 0xA, 0, 4, 2);
    ParticleDef_CreateQuick(0, ParticleEffect_StateHandlerA, &gParticleDefaultCallback, 0, 1, 0xA, 0, 5, 0);
    ParticleEffect_MultiNodeA();
}

void ParticleEffect_MultiNodeAEntry(void) {
    func_8434A930();
}

void func_8434A9EC(void) {
    ParticleDef_Create31EAC(4, 0xA, 0, 0xFF, 0x40);
    ParticleDef_CreateAlphaModeZero(8);
    ParticleDef_CreateQuick(0xC, ParticleEffect_StateHandlerB, &gParticleDefaultCallback, 0, 1, 0xE, 0, 6, 0);
    ParticleEffect_MultiNodeC();
}

void ParticleEffect_MultiNodeC2(void) {
    ParticleDef_Create31EAC(6, 0xA, 0, 0xFF, 0x40);
    ParticleDef_CreateAlphaModeZero(0xA);
    ParticleDef_CreateQuick(0xC, ParticleEffect_StateHandlerB, &gParticleDefaultCallback, 0, 1, 0xA, 0, 7, 0);
    ParticleEffect_MultiNodeC();
}

void Gfx_PokemonPortraitCallback(Gfx* arg0, u8 arg1, UNUSED u16 arg2) {
    u8* var_a3;
    s32 idx = arg1 * 0xB48;

    if (IsPrimaryEntity(GetGraphNodeData(gDefaultGraphRoot)->unk_10) == 0) {
        var_a3 = gPokemonPortraitImage0 + idx;
    } else {
        var_a3 = gPokemonPortraitImage1 + idx;
    }

    gDPLoadTextureTile(arg0++, var_a3, G_IM_FMT_RGBA, G_IM_SIZ_16b, 76, 0, 0, 0, 75, 18, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                       G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

    gSPEndDisplayList(arg0++);
}

void Gfx_PokemonPortraitCallback2(s32 arg0, arg1_func_84344CE8* arg1) {
    if (arg0 == 2) {
        arg1->unk_18 = GfxAlloc(sizeof(Gfx) * 30);
        Gfx_PokemonPortraitCallback(arg1->unk_18, arg1->unk_14, gAnimationFrame);
    }
}

void ParticleEffect_PortraitBurst(void) {
    ParticleDef_CreateFull(0, 8, 6, ParticleEffect_StateHandlerA, &gParticleDefaultCallback, 0, 1, 9, 0, 8, 0);
}

void ParticleEffect_PortraitBurstInit(void) {
    ParticleDef_CreateDefault(0, 0x20, 0x10);
    ParticleEffect_PortraitBurst();
}

void ParticleEffect_PortraitBurstNode(void) {
    ParticleDef_CreateQuick(0, ParticleEffect_StateHandlerB, &gParticleDefaultCallback, 0, 1, 0xE, 0, 9, 0);
}

void ParticleEffect_PortraitBurstCheck(void) {
    s32 var_s0 = 0;

    if (IsEntityASpecies(0x5C) != 0) {
        var_s0 = 1;
    } else if (IsEntityASpecies(0x5D) != 0) {
        var_s0 = 1;
    } else if (IsEntityASpecies(0x5E) != 0) {
        var_s0 = 1;
    } else if (IsEntityASpecies(0x5A) != 0) {
        var_s0 = 1;
    } else if (IsEntityASpecies(0x6C) != 0) {
        var_s0 = 1;
    } else if (IsEntityASpecies(0x2A) != 0) {
        var_s0 = 1;
    }

    if (var_s0 == 0) {
        ParticleDef_CreateQuick(0, ParticleEffect_StateHandlerA, &gParticleDefaultCallback, 0, 1, 0x10, gParticleTexture_Default, 0xA, 0);
    }
}

f32 ParticleEffect_SpeciesAdjustB(ParticleEffectInstance* arg0) {
    f32 sp1C = 0.0f;
    f32 sp18 = 1.0f;

    switch (GetSpecies(arg0->unk_10)) {
        case 0x24:
            sp18 = 1.2f;
            sp1C = 10.0f;
            break;

        case 0x34:
            sp18 = 0.8f;
            break;

        case 0x36:
            sp1C = 15.0f;
            break;

        case 0x3B:
            sp1C = 30.0f;
            sp18 = 0.8f;
            break;

        case 0x5A:
            sp1C = 10.0f;
            break;

        case 0x5F:
            Particle_AddVelocityLeft(arg0, 15.0f);
            sp1C = 10.0f;
            sp18 = 0.5f;
            break;

        case 0x66:
            sp1C = 15.0f;
            sp18 = 0.8f;
            break;

        case 0x7D:
            sp1C = 8.0f;
            break;

        case 0x7E:
            sp1C = 15.0f;
            sp18 = 0.8f;
            break;

        case 0x82:
            sp1C = 10.0f;
            sp18 = 0.4f;
            break;

        case 0x83:
            sp1C = 10.0f;
            sp18 = 0.4f;
            break;
    }

    Particle_AddVelocityYScaled(arg0, sp1C);
    return sp18;
}

void ParticleEffect_SimpleBurst2(void) {
    ParticleDef_CreateQuick(0, ParticleEffect_StateHandlerA, &gParticleDefaultCallback, 0, 1, 0xB, 0, 0xB, 0);
    ParticleDef_CreateDefault(0x2A, 0x10, 0x17);
}

void ParticleEffect_SimpleBurst3(void) {
    ParticleDef_Create31FAC(0, 1, 0x18, 0xFF, 0, 8);
    ParticleDef_CreateQuick(0, ParticleEffect_StateHandlerA, &gParticleDefaultCallback, 0, 1, 9, 0, 0xC, 0);
}

void ParticleEffect_SpeciesAdjustC(ParticleEffectInstance* arg0) {
    f32 sp1C = 0.0f;

    switch (GetSpecies(arg0->unk_10)) {
        case 0x34:
            sp1C = 12.0f;
            break;

        case 0x36:
            sp1C = 20.0f;
            break;
    }
    Particle_AddVelocityYScaled(arg0, sp1C);
}

void ParticleEffect_PaletteInit(ParticleEffectInstance* arg0) {
    s16 sp26 = Particle_GetByteCD(arg0);

    arg0->unk_14 = AllocateGraphNode(arg0);

    if (arg0->unk_14 != NULL) {
        if ((sp26 == 0) || (sp26 == 1)) {
            InitGraphNodeTexture(arg0->unk_14, 0x8C);
        } else if ((sp26 == 2) || (sp26 == 3)) {
            InitGraphNodeTexture(arg0->unk_14, 0x8E);
        } else {
            InitGraphNodeTexture(arg0->unk_14, 0x8D);
        }

        Particle_SetScaleFactor1(arg0, 1.0f);
        ParticleEffect_SpeciesAdjustC(arg0);
        Particle_SetPrimAlpha(arg0, 0);
        Particle_IncrementState(arg0);
    } else {
        Particle_ResetState(arg0);
    }
}

void ParticleEffect_PaletteStateHandler(ParticleEffectInstance* arg0) {
    u32 temp_v0 = Particle_GetByteCD(arg0);

    switch (arg0->unk_B2) {
        case 1:
            ParticleEffect_PaletteInit(arg0);
            break;

        case 2:
            if ((temp_v0 == 0) || ((s32)temp_v0 == 1)) {
                Particle_ApproachPrimAlphaWithCallback(arg0, 0x80, 8);
            } else if (temp_v0 == 3) {
                Particle_ApproachPrimAlphaWithCallback(arg0, 0xFF, 0xFF);
            } else {
                Particle_ApproachPrimAlphaWithCallback(arg0, 0xFF, 4);
            }
            break;
    }
}

void Gfx_PaletteParticleDL(Gfx* arg0, u8* arg1, UNUSED u16 arg2) {
    u8* a1;
    ParticleEffectInstance* spC8;
    u8 var_t0;
    s16 spC4;
    s16 spC2;
    s16 spC0;
    s16 spBE;
    s16 var_a1;
    s16 var_a2;
    s16 var_a3;
    s16 var_s1;
    UNUSED s16 pad2;
    s16 spB2;
    s16 spB0;
    s16 spAE;
    s16 spAC;
    u16 temp_v0_2;
    s16 var_t2;
    s16 var_t1;

    spC8 = GetGraphNodeData(gDefaultGraphRoot);
    temp_v0_2 = Particle_GetByteCD(spC8);
    var_s1 = 0x20;
    var_t1 = 5;
    var_t2 = 5;
    var_a3 = 0;
    var_a1 = 0;
    var_a2 = 0;
    var_t0 = spC8->prim_a;

    switch (temp_v0_2) {
        case 0:
            spC4 = -1;
            spC2 = -1;
            spC0 = 1;
            spBE = -1;
            spB2 = 0xF;
            spB0 = 0;
            spAE = 0xE;
            spAC = 0xF;
            break;

        case 1:
            spC4 = -1;
            spC2 = 1;
            spC0 = 1;
            spBE = 1;
            spB2 = 0xF;
            spB0 = 0;
            spAE = 0xE;
            spAC = 0xF;
            break;

        case 2:
            spC4 = -2;
            spC2 = 2;
            spC0 = 2;
            var_a3 = 0xFF;
            spBE = 3;
            spB2 = 0xC;
            spB0 = 1;
            spAE = 0xC;
            spAC = 0;
            break;

        case 3:
            spC4 = -2;
            spC2 = -2;
            spC0 = 2;
            var_a3 = 0xFF;
            spBE = -3;
            spB2 = 0xC;
            spB0 = 1;
            spAE = 0xC;
            spAC = 0;
            break;

        case 4:
            var_a2 = 0xFF;
            var_a1 = 0x9B;
            spC4 = 1;
            spC2 = 1;
            spC0 = -1;
            spBE = -1;
            spB2 = 0xC;
            spB0 = 1;
            spAE = 0xC;
            spAC = 0;

            break;

        case 5:
            spC0 = -0xA;
            spBE = -0xF;
            spC4 = 0;
            spC2 = 0;
            spB2 = 0xF;
            spB0 = 1;
            spAE = 0xF;
            spAC = 1;
            var_a2 = 0xFF;
            var_a1 = 0xFF;
            var_a3 = 0xFF;
            var_t0 = 0x32;
            break;

        case 6:
            spC4 = 2;
            spC2 = -1;
            spC0 = -2;
            spBE = -2;
            spB2 = 0xD;
            spB0 = 0xE;
            spAE = 0xC;
            spAC = 0xE;
            var_a2 = 0xFF;
            var_a1 = 0xFF;
            var_a3 = 0xFF;
            var_s1 = 0x40;
            var_t1 = 6;
            var_t2 = 6;
            break;

        case 7:
            spC4 = 1;
            spC2 = 1;
            spC0 = -1;
            spBE = -1;
            spB2 = 0xD;
            spB0 = 0xF;
            spAE = 0xF;
            spAC = 0xE;
            var_a2 = 0xFF;
            var_a3 = 0x80;
            break;

        case 8:
            spC4 = 1;
            spC2 = 1;
            spC0 = -1;
            spBE = -1;
            spB2 = 0xD;
            spB0 = 0xF;
            spAE = 0xF;
            spAC = 0xE;
            var_a1 = 0xFF;
            var_a3 = 0xFF;
            break;

        case 9:
            spC4 = 1;
            spC2 = 1;
            spC0 = -1;
            spBE = -1;
            spB2 = 0xD;
            spB0 = 0xF;
            spAE = 0xF;
            spAC = 0xE;
            var_a2 = 0x64;
            var_a1 = 0xFF;
            break;

        case 10:
            spC4 = -1;
            spC2 = -1;
            spC0 = 1;
            spBE = -1;
            spB2 = 0xD;
            spB0 = 0;
            spAE = 0xC;
            spAC = 0xF;
            var_a2 = 0xC8;
            var_a1 = 0x64;
            break;

        case 11:
            spC4 = -1;
            spC2 = -1;
            spC0 = 1;
            spBE = -1;
            spB2 = 0xD;
            spB0 = 0;
            spAE = 0xC;
            spAC = 0xF;
            var_a1 = 0xFF;
            var_a3 = 0xFF;
            break;

        case 12:
            spC4 = -1;
            spC2 = -1;
            spC0 = 1;
            spBE = -1;
            spB2 = 0xD;
            spB0 = 0;
            spAE = 0xC;
            spAC = 0xF;
            var_a2 = 0xC8;
            var_a1 = 0xFF;
            break;

        case 13:
            spC4 = -1;
            spC2 = -1;
            spC0 = 1;
            spBE = -1;
            spB2 = 0xD;
            spB0 = 0;
            spAE = 0xC;
            spAC = 0xF;
            var_a2 = 0xFF;
            break;
    }

    a1 = arg1;

    gDPPipeSync(arg0++);
    gDPSetPrimColor(arg0++, 0, 0x80, var_a2, var_a1, var_a3, var_t0);

    gDPLoadTextureTile_4b(arg0++, arg1, G_IM_FMT_I, var_s1, var_s1, 0, 0, var_s1 - 1, var_s1 - 1, 0,
                          G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, var_t2, var_t1, spB2, spB0);

    Gfx_ScrollTextureToDL(arg0++, spC4, spC2, var_s1, var_s1);

    gDPLoadMultiTile_4b(arg0++, a1, 0x0100, 1, G_IM_FMT_I, var_s1, var_s1, 0, 0, var_s1 - 1, var_s1 - 1, 0,
                        G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, var_t2, var_t1, spAE, spAC);

    Gfx_ScrollTexture1ToDL(arg0++, spC0, spBE, var_s1, var_s1);

    gSPEndDisplayList(arg0++);
}

void Gfx_PaletteParticleDLCallback(s32 arg0, arg1_func_84344CE8* arg1) {
    if (arg0 == 2) {
        arg1->unk_18 = GfxAlloc(sizeof(Gfx) * 30);
        Gfx_PaletteParticleDL(arg1->unk_18, arg1->unk_14, gAnimationFrame);
    }
}

void ParticleEffect_PaletteMultiBurst2(void) {
    ParticleDef_CreateQuick(0, ParticleEffect_PaletteStateHandler, &gParticleDefaultCallback, 0, 1, 0xC, 0, 0, 0);
    ParticleDef_CreateQuick(0, ParticleEffect_StateHandlerD, &gParticleDefaultCallback, 0, 1, 9, 0, 0xD, 0);
    ParticleDef_CreateQuick(4, ParticleEffect_StateHandlerD, &gParticleDefaultCallback, 0, 1, 9, 1, 0xD, 0);
    ParticleDef_CreateQuick(8, ParticleEffect_StateHandlerD, &gParticleDefaultCallback, 0, 1, 9, 2, 0xD, 0);
    ParticleDef_CreateQuick(0xC, ParticleEffect_StateHandlerD, &gParticleDefaultCallback, 0, 1, 9, 0, 0xD, 0);
    ParticleDef_CreateQuick(0x10, ParticleEffect_StateHandlerD, &gParticleDefaultCallback, 0, 1, 9, 1, 0xD, 0);
    ParticleDef_CreateQuick(0x14, ParticleEffect_StateHandlerD, &gParticleDefaultCallback, 0, 1, 9, 2, 0xD, 0);
    ParticleDef_CreateQuick(0x18, ParticleEffect_StateHandlerD, &gParticleDefaultCallback, 0, 1, 9, 0, 0xD, 0);
    ParticleDef_CreateQuick(0x1C, ParticleEffect_StateHandlerD, &gParticleDefaultCallback, 0, 1, 9, 1, 0xD, 0);
    ParticleDef_CreateQuick(0x20, ParticleEffect_StateHandlerD, &gParticleDefaultCallback, 0, 1, 9, 2, 0xD, 0);
    ParticleDef_CreateDefault(0, 8, 0x35);
}

void ParticleEffect_PaletteMultiBurst3(void) {
    ParticleDef_CreateQuick(0, ParticleEffect_PaletteStateHandler, &gParticleDefaultCallback, 0, 1, 0xC, 1, 0, 0);
    ParticleDef_CreateQuick(0, ParticleEffect_StateHandlerA, &gParticleDefaultCallback, 0, 1, 9, 0, 0xD, 0);
    ParticleDef_CreateQuick(4, ParticleEffect_StateHandlerA, &gParticleDefaultCallback, 0, 1, 9, 1, 0xD, 0);
    ParticleDef_CreateQuick(8, ParticleEffect_StateHandlerA, &gParticleDefaultCallback, 0, 1, 9, 2, 0xD, 0);
    ParticleDef_CreateQuick(0xC, ParticleEffect_StateHandlerA, &gParticleDefaultCallback, 0, 1, 9, 0, 0xD, 0);
    ParticleDef_CreateQuick(0x10, ParticleEffect_StateHandlerA, &gParticleDefaultCallback, 0, 1, 9, 1, 0xD, 0);
    ParticleDef_CreateQuick(0x14, ParticleEffect_StateHandlerA, &gParticleDefaultCallback, 0, 1, 9, 2, 0xD, 0);
    ParticleDef_CreateQuick(0x18, ParticleEffect_StateHandlerA, &gParticleDefaultCallback, 0, 1, 9, 0, 0xD, 0);
    ParticleDef_CreateQuick(0x1C, ParticleEffect_StateHandlerA, &gParticleDefaultCallback, 0, 1, 9, 1, 0xD, 0);
    ParticleDef_CreateQuick(0x20, ParticleEffect_StateHandlerA, &gParticleDefaultCallback, 0, 1, 9, 2, 0xD, 0);
}

void ParticleEffect_PaletteScriptBurst(void) {
    switch (GetActionScriptId()) {
        case 0x8D:
            ParticleDef_CreateDefault(0, 0x10, 6);
            ParticleDef_CreateQuick(0, ParticleEffect_StateHandlerF, &gParticleDefaultCallback, 0x80, 1, 0xC, 0xD, 0x1A, 0x20);
            break;

        case 0x47:
            ParticleDef_CreateDefault(0, 0x10, 0x3A);
            ParticleDef_CreateQuick(0, ParticleEffect_StateHandlerF, &gParticleDefaultCallback, 0x80, 1, 0xC, 0xB, 0x1A, 0x20);
            break;

        case 0x48:
            ParticleDef_CreateDefault(0, 0x10, 0x21);
            ParticleDef_CreateQuick(0, ParticleEffect_StateHandlerF, &gParticleDefaultCallback, 0x80, 1, 0xC, 0xC, 0x1A, 0x20);
            break;
    }
}

void ParticleEffect_PaletteBurst4(void) {
    ParticleDef_CreateQuick(0, ParticleEffect_PaletteStateHandler, &gParticleDefaultCallback, 0, 1, 0xC, 4, 0, 0);
}

void ParticleEffect_PaletteBurst5(void) {
    ParticleDef_CreateQuick(0, ParticleEffect_PaletteStateHandler, &gParticleDefaultCallback, 0, 1, 0xC, 2, 0, 0);
    ParticleDef_CreateDefault(0, 8, 0);
    ParticleSystem_AddSpawnOffset(0x40);
    ParticleDef_CreateBC20CD(0, 2, 0x10, 0xA);
}

void ParticleEffect_FireworkBurst(void) {
    ParticleDef_CreateBC20CD(0, 2, 0x10, 0xA);
    ParticleDef_Create31EAC(4, 0xA, 0xFF, 0, 8);
    ParticleDef_CreateQuick(0, ParticleEffect_PaletteStateHandler, &gParticleDefaultCallback, 0, 1, 0xC, 3, 0, 0);
    ParticleDef_CreateFull(4, 4, 4, ParticleEffect_FireworkMain, &gParticleEffectData[0x34], 0, 3, 9, 0, 0x18, 0xD);
}

void ParticleEffect_WaterAnimInit(ParticleEffectInstance* arg0) {
    arg0->unk_14 = AllocateGraphNode(arg0);
    if (arg0->unk_14 != NULL) {
        InitWaterAnimNode(arg0->unk_14, 0x42, 0xC2);
        Particle_SetScaleFactor1(arg0, 1.0f);
        SetPrimEnvColorFromPair(arg0, 0x23);
        Particle_SetPrimAlpha(arg0, 0);
        Particle_SetShortAE(arg0, 0);
        Particle_IncrementState(arg0);
    } else {
        Particle_ResetState(arg0);
    }
}

void ParticleEffect_WaterAnimStateHandler(ParticleEffectInstance* arg0) {
    s16 sp26;

    switch (arg0->unk_B2) {
        case 1:
            ParticleEffect_WaterAnimInit(arg0);
            break;

        case 2:
            Particle_ApproachPrimAlpha(arg0, 0xFF, 8);
            Particle_ApproachShortAE(arg0, 0xC8, 6);
            break;
    }

    GetCameraYawFromEyeToAt(&sp26);
    Particle_SetRotationY(arg0, sp26);
}

void ParticleEffect_WaterAnimInit2(ParticleEffectInstance* arg0) {
    arg0->unk_14 = AllocateGraphNode(arg0);
    if (arg0->unk_14 != NULL) {
        InitWaterAnimNode(arg0->unk_14, 0x42, 0xC2);
        SetAnimChannelBase(arg0->unk_14, 0x28);
        Particle_SetScaleFactor1(arg0, 1.0f);
        SetPrimEnvColorFromPair(arg0, 0x23);
        Particle_SetShortAE(arg0, 0xFF);
        Particle_IncrementState(arg0);
    } else {
        Particle_ResetState(arg0);
    }
}

void ParticleEffect_WaterAnimStateHandler2(ParticleEffectInstance* arg0) {
    s16 sp1E;

    if (arg0->unk_B2 == 1) {
        ParticleEffect_WaterAnimInit2(arg0);
    }
    GetCameraYawFromEyeToAt(&sp1E);
    Particle_SetRotationY(arg0, sp1E);
}

void Gfx_WaterAnimPrimEnvDL(Gfx* arg0, u8 arg1, UNUSED u16 arg2) {
    ParticleEffectInstance* temp_v0 = GetGraphNodeData(gDefaultGraphRoot);

    switch (arg1) {
        case 0:
            gDPPipeSync(arg0++);
            gDPSetPrimColor(arg0++, 0, 0, temp_v0->prim_r, temp_v0->prim_g, temp_v0->prim_b, temp_v0->prim_a);
            break;

        case 1:
            gDPPipeSync(arg0++);
            gDPSetPrimColor(arg0++, 0, 0, temp_v0->prim_r, temp_v0->prim_g, temp_v0->prim_b, temp_v0->unk_AE);
            break;
    }

    gDPSetEnvColor(arg0++, temp_v0->env_r, temp_v0->env_g, temp_v0->env_b, 0);
    gDPSetCombineLERP(arg0++, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED,
                      0, 0, 0, COMBINED);

    gSPEndDisplayList(arg0++);
}

void Gfx_WaterAnimPrimEnvDLCallback(s32 arg0, arg1_func_84344CE8* arg1) {
    if (arg0 == 2) {
        arg1->unk_18 = GfxAlloc(sizeof(Gfx) * 30);
        Gfx_WaterAnimPrimEnvDL(arg1->unk_18, arg1->unk_14, gAnimationFrame);
    }
}

void ParticleEffect_WaterAnimBurst(void) {
    ParticleDef_CreateDefault(0, 8, 3);
    ParticleDef_CreateQuick(0, ParticleEffect_WaterAnimStateHandler, &gParticleDefaultCallback, 0, 1, 0xA, 0, 0, 0);
}

void ParticleEffect_WaterAnimBurst2(void) {
    ParticleDef_CreateDefault(0x10, 0x10, 0xA);
}

void ParticleEffect_WaterAnimFirework(void) {
    ParticleDef_CreateQuick(0, ParticleEffect_WaterAnimStateHandler, &gParticleDefaultCallback, 0, 1, 0xA, 0, 0, 0);
    ParticleDef_CreateDefault(0, 0x20, 3);
    ParticleDef_Create31EAC(8, 0xA, 0, 0xFF, 0x40);
    ParticleDef_Create32E6C(0xC, 5, 0x10, 0xA);
    ParticleDef_CreateQuick(0xC, ParticleEffect_FireworkMain, &gParticleEffectData[0x34], 0, 4, 9, 0, 0x18, 0xD);
    ParticleSystem_AddSpawnOffset(0x21);
    ParticleDef_CreateBC20CD(0, 0, 0x10, 0xA);
    ParticleDef_Create31EAC(0, 0xA, 0xFF, 0, 0x10);
}

void ParticleEffect_WaterAnimFirework2(void) {
    ParticleDef_CreateQuick(0, ParticleEffect_WaterAnimStateHandler2, &gParticleDefaultCallback, 0, 1, 0xA, 0, 0, 0);
    ParticleDef_CreateBC20CD(0, 0, 0x10, 0xA);
    ParticleDef_CreateDefault(0, 0x20, 3);
    ParticleDef_Create31EAC(8, 0xA, 0, 0xFF, 0x40);
    ParticleDef_CreateQuick(0xC, ParticleEffect_FireworkMain, &gParticleEffectData[0x34], 0, 4, 9, 0, 0x18, 0xD);
    ParticleSystem_AddSpawnOffset(0x21);
    ParticleDef_Create31EAC(0, 0xA, 0xFF, 0, 0x10);
}

void Gfx_WaterAnimDL(Gfx* arg0, u8* arg1, UNUSED u16 arg2) {
    ParticleEffectInstance* temp_v0 = GetGraphNodeData(gDefaultGraphRoot);

    gDPPipeSync(arg0++);
    gDPSetPrimColor(arg0++, 0, 0x80, 100, 200, 255, temp_v0->prim_a);

    gDPLoadTextureTile_4b(arg0++, arg1, G_IM_FMT_I, 32, 0, 0, 0, 31, 31, 0, G_TX_NOMIRROR | G_TX_WRAP,
                          G_TX_NOMIRROR | G_TX_WRAP, 5, 5, 14, 15);

    Gfx_ScrollTextureY(arg0++, -0xB, -8, 0x20, 0x20);

    gDPLoadMultiTile_4b(arg0++, arg1, 0x0100, 1, G_IM_FMT_I, 32, 0, 0, 0, 31, 31, 0, G_TX_NOMIRROR | G_TX_WRAP,
                        G_TX_NOMIRROR | G_TX_WRAP, 5, 5, 13, 15);

    Gfx_ScrollTextureY1(arg0++, 0x35, -4, 0x20, 0x20);

    gSPEndDisplayList(arg0++);
}

void Gfx_WaterAnimDLCallback(s32 arg0, arg1_func_84344CE8* arg1) {
    if (arg0 == 2) {
        arg1->unk_18 = GfxAlloc(sizeof(Gfx) * 30);
        Gfx_WaterAnimDL(arg1->unk_18, arg1->unk_14, gAnimationFrame);
    }
}

f32 ParticleEffect_SpeciesAdjustD(ParticleEffectInstance* arg0) {
    f32 sp1C = 2.5f;

    if (GetSpecies(arg0->unk_10) == 0x5F) {
        sp1C = 1.75f;
    }
    return sp1C;
}

void ParticleEffect_BasicMultiBurst(void) {
    ParticleDef_CreateQuick(0, ParticleEffect_StateHandlerF, &gParticleDefaultCallback, 0xFF, 1, 0xC, 0, 0xE, 8);
    ParticleSystem_AddSpawnOffset(4);
    ParticleDef_CreateFull(0, 4, 0x10, ParticleEffect_BasicSetupHandler, &gParticleEffectData[0x4A], 0, 2, 0xE, 0, 0x4E, 3);
    ParticleDef_CreateFull(0, 4, 0x10, ParticleEffect_BasicSetupHandler, &gParticleEffectData[0x19], 0, 2, 0xE, 0, 0x4D, 3);
    ParticleDef_CreateFull(0, 4, 0x10, ParticleEffect_BasicSetupHandler, &gParticleEffectData[0xE], 0, 2, 0xE, 0, 0x4D, 3);
    ParticleDef_CreateFull(0, 8, 5, ParticleEffect_BasicSetupHandler, &gParticleEffectData[0xA], 0, 2, 0xE, 0, 0x4D, 4);
}

void ParticleEffect_FireballBurst(void) {
    ParticleDef_CreateQuick(0, ParticleEffect_StateHandlerF, &gParticleDefaultCallback, 0xFF, 1, 0xC, 0, 0xF, 0x40);
    ParticleDef_Create321BC(4, 0xA, 0x35, 0xC, 0xFF);
    ParticleDef_CreateQuick(0, Particle_SootPuff_Handler, &gParticleEffectData[4], 0, 1, 0x10, gParticleTexture_Default, 0x35, 0);
    ParticleDef_CreateFull(0, 5, 3, ParticleEffect_Fireball_Stage3, &gParticleEffectData[0x19], 0, 8, 0x10, gParticleTexture_Default, 0x4D, 0);
    ParticleDef_CreateFull(0xA, 1, 3, ParticleEffect_SmallBurst_Main, &gParticleEffectData[0x19], 0, 8, 0x11, gParticleTexture_Default, 0x4D, 0);
    ParticleSystem_AddSpawnOffset(0x10);
    ParticleDef_CreateFull(0, 4, 5, ParticleEffect_BasicSetupHandler, &gParticleEffectData[0xA], 0, 1, 0xE, 0, 0x4D, 4);
}

void ParticleEffect_BasicMultiBurst2(void) {
    ParticleSystem_AddSpawnOffset(0x41);
    ParticleDef_CreateFull(0, 4, 0x20, ParticleEffect_BasicSetupHandler, &gParticleEffectData[0x4A], 0, 2, 7, 0, 0x33, 8);
    ParticleDef_CreateFull(0, 4, 0x20, ParticleEffect_BasicSetupHandler, &gParticleEffectData[0x19], 0, 2, 7, 0, 0xC, 8);
    ParticleDef_CreateFull(0, 4, 0x20, ParticleEffect_BasicSetupHandler, &gParticleEffectData[0xE], 0, 2, 7, 0, 0xC, 8);
    ParticleDef_CreateFull(0, 8, 0xA, ParticleEffect_BasicSetupHandler, &gParticleEffectData[0xA], 0, 2, 7, 0, 0xC, 4);
}

void ParticleEffect_AdvancedMultiBurst(void) {
    ParticleDef_CreateFull(0, 4, 4, ParticleEffect_AdvancedSetup, &gParticleEffectData[0x4A], 0, 3, 0xE, 0, 0x33, 0xC);
    ParticleDef_CreateFull(0, 4, 4, ParticleEffect_AdvancedSetup, &gParticleEffectData[0x19], 0, 3, 0xE, 0, 0xC, 0xC);
    ParticleDef_CreateFull(0, 4, 4, ParticleEffect_AdvancedSetup, &gParticleEffectData[0xE], 0, 3, 0xE, 0, 0xC, 0xC);
    ParticleDef_CreateFull(0, 4, 4, ParticleEffect_AdvancedSetup, &gParticleEffectData[0xA], 0, 3, 0xE, 0, 0xC, 4);
    ParticleDef_CreateFull(0, 2, 0xC, ParticleEffect_Type0_Main, &gParticleEffectData[0x45], 0, 4, 0x11, 7, 0x33, 0);
}

void ParticleEffect_SimpleBurst4(void) {
    ParticleDef_CreateQuick(0, ParticleEffect_StateHandlerA, &gParticleDefaultCallback, 0, 1, 0x13, gParticleTexture_Default, 0x10, 0);
    ParticleDef_CreateBC20CD(0x22, 0, 0x10, 0xA);
}

void ParticleEffect_SimpleStateInit(ParticleEffectInstance* arg0) {
    Particle_SetScaleFactor1(arg0, 0.2f);
    SetPrimEnvColorFromPair(arg0, 0x33);
    Particle_SetPrimAlpha(arg0, 0xFF);
    Particle_IncrementState(arg0);
}

void ParticleEffect_SimpleStateHandler(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            ParticleEffect_SimpleStateInit(arg0);
            break;

        case 2:
            Particle_AnimLoopForwardComplete(arg0, 0, 7, 1, 2, 0);
            Particle_ApproachPrimAlpha(arg0, 0x20, 0x40);
            break;

        case 3:
            Particle_ResetState(arg0);
            break;
    }
    Particle_ApproachScaleFactor1(arg0, 0.5f, 0.1f);
}

void ParticleEffect_RotationInit(ParticleEffectInstance* arg0) {
    Particle_GetShortAC(arg0);
    Particle_SetScaleFactor1(arg0, 0.3f);
    Particle_AddRotationDeltaXYZ(arg0, -0x1000, 0, 0);
    Particle_SetTargetRotationY(arg0, ParticleNode_GetAngleToSecondary(arg0));
    Particle_SetRotationDeltaY(arg0, 0x80);
    Particle_DisableFlag4(arg0);
    Particle_IncrementState(arg0);
}

void ParticleEffect_RotationStateHandler(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            ParticleEffect_RotationInit(arg0);
            break;

        case 2:
            if (Particle_DecrementTimerA6ToZeroWithCallback(arg0) != 0) {
                arg0->unk_14 = AllocateGraphNode(arg0);
                InitWaterAnimNode(arg0->unk_14, 0xA0, 0xA1);
                Particle_EnableFlag4(arg0);
            }
            break;

        case 3:
            if (Particle_ProcessTimer80(arg0, 0xA) != 0) {
                Particle_SetSpeed(arg0, 8.0f);
                ParticleNode_CreateMultiple(arg0, ParticleEffect_SimpleStateHandler, &gParticleEffectData[0x4A], 1);
                Particle_CreateChildParticles(arg0, ParticleEffect_RandomRotationHandler, &gParticleEffectData[0x3D], 0xC, 0x33, 0);
            }
            break;

        case 4:
            ParticleNode_CreateMultiple(arg0, ParticleEffect_SimpleStateHandler, &gParticleEffectData[0x4A], 1);
            Particle_ApproachRotationXWrapToTarget(arg0, 0x1000, 0x200);
            Particle_ApproachRotationYWrap(arg0);
            Particle_ProcessTimer80(arg0, 0xF);
            break;

        case 5:
            Particle_ResetState(arg0);
            break;
    }

    if (Particle_HasFlag4(arg0) != 0) {
        Particle_ApplyB2B4AndAddAll(arg0);
    }
}

void ParticleEffect_RotationEntry(void) {
    ParticleDef_CreateQuick(0, ParticleEffect_RotationStateHandler, &gParticleDefaultCallback, 0, 1, 0x11, gParticleTexture_Default, 0, 0);
}

void ParticleEffect_FireworkInit(ParticleEffectInstance* arg0) {
    Particle_GetShortAC(arg0);
    Particle_SetScaleFactor1(arg0, 0.4f);
    Particle_SetVelocityYScaled(arg0, 15.0f);
    Particle_AddVelocityForward(arg0, 50.0f);
    Particle_AddRotationDeltaXYZ(arg0, 0x800, -0x8000, 0);
    Particle_SetSpeed(arg0, 8.0f);
    Particle_IncrementState(arg0);
    arg0->unk_14 = AllocateGraphNode(arg0);
    InitGraphNodeTexture(arg0->unk_14, 0xA0);
}

void ParticleEffect_FireworkStateHandler(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            ParticleEffect_FireworkInit(arg0);
            break;

        case 2:
            ParticleNode_CreateMultiple(arg0, ParticleEffect_SimpleStateHandler, &gParticleEffectData[0x4A], 1);
            Particle_ApproachRotationXWrapToTarget(arg0, 0x1000, 0x80);
            Particle_ProcessTimer80(arg0, 7);
            break;

        case 3:
            Particle_ResetState(arg0);
            break;
    }

    if (Particle_HasFlag4(arg0) != 0) {
        Particle_ApplyB2B4AndAddAll(arg0);
    }
}

void ParticleEffect_FireworkEntry(void) {
    ParticleDef_CreateQuick(0, ParticleEffect_FireworkStateHandler, &gParticleDefaultCallback, 0, 1, 0x11, gParticleTexture_Default, 0, 0);
    ParticleDef_CreateQuick(5, ParticleEffect_FireworkMain, &gParticleEffectData[0x34], 0, 1, 0x11, 9, 0, 6);
    ParticleDef_CreateQuick(7, Particle_HandleState_MultiColorDot, &gParticleEffectData[0x3D], 0, 8, 0x11, 9, 0, 0);
}

void ParticleEffect_SimpleNodeInit(ParticleEffectInstance* arg0) {
    arg0->unk_14 = AllocateGraphNode(arg0);
    if (arg0->unk_14 != NULL) {
        InitGraphNodeTexture(arg0->unk_14, 0xA2);
        Particle_SetScaleFactor1(arg0, 1.0f);
        Particle_SetPrimAlpha(arg0, 0);
        Particle_IncrementState(arg0);
    } else {
        Particle_ResetState(arg0);
    }
}

void ParticleEffect_SimpleNodeStateHandler(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            ParticleEffect_SimpleNodeInit(arg0);
            break;

        case 2:
            Particle_ApproachPrimAlphaWithCallback(arg0, 0x80, 8);
            break;
    }
}

void Gfx_SimpleNodeDL(Gfx* arg0, arg1_func_8434E21C* arg1, UNUSED u16 arg2) {
    UNUSED s32 pad;
    ParticleEffectInstance* sp48 = GetGraphNodeData(gDefaultGraphRoot);
    UNUSED s16 pad2;
    s16 sp44;
    s16 sp42;

    switch (Particle_GetShortCF(sp48)) {
        case 0:
            sp44 = -5;
            sp42 = 3;
            break;

        case 1:
            sp44 = 5;
            sp42 = -3;
            break;
    }

    gDPPipeSync(arg0++);
    gDPSetPrimColor(arg0++, 0, 0x80, 55, 255, 255, sp48->prim_a);

    arg0 = Gfx_LoadParticleTextureTileFromStruct(arg0++, arg1, 0x20, 5, 1, sp44, 0xD, 0xC, -1, sp42, 0xB, 0xD);
    gSPEndDisplayList(arg0++);
}

void Gfx_SimpleNodeDLCallback(s32 arg0, arg1_func_84344CE8* arg1) {
    if (arg0 == 2) {
        arg1->unk_18 = GfxAlloc(sizeof(Gfx) * 30);
        Gfx_SimpleNodeDL(arg1->unk_18, arg1->unk_14, gAnimationFrame);
    }
}

void ParticleEffect_SimpleNodeEntry(void) {
    ParticleDef_CreateDefault(0, 0x10, 0);
    ParticleDef_CreateQuick(0, ParticleEffect_SimpleNodeStateHandler, &gParticleDefaultCallback, 0, 1, 9, 0, 0, 0);
}

void ParticleEffect_SimpleNodeBurst(void) {
    ParticleDef_Create31FAC(0, 2, 0xA, 0xFF, 0, 0x10);
    ParticleDef_CreateQuick(0, ParticleEffect_SimpleNodeStateHandler, &gParticleDefaultCallback, 0, 1, 9, 0, 1, 0);
    ParticleDef_CreateFull(4, 4, 4, ParticleEffect_FireworkMain, &gParticleEffectData[0x34], 0, 3, 9, 0, 0x18, 0xD);
}

void ParticleEffect_AlphaStateHandler(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            ParticleEffect_ConfigureState(arg0, 2);
            break;

        case 2:
            Particle_ApproachPrimAlphaWithCallback(arg0, arg0->unk_A6, Particle_GetShortCE(arg0));
            break;

        case 3:
            Particle_ProcessTimer80(arg0, 0x20);
            break;

        case 4:
            Particle_ApproachPrimAlphaWithCallback(arg0, 0, 0xA);
            break;

        case 5:
            Particle_ResetState(arg0);
            break;
    }
}

void ParticleEffect_AlphaBurst(void) {
    ParticleDef_CreateDefault(0, 5, 0);
    ParticleDef_CreateQuick(0, ParticleEffect_StateHandlerF, &gParticleDefaultCallback, 0xFF, 1, 0xC, 8, 0x18, 5);
    ParticleDef_Create31FAC(0x32, 1, 0xA, 0, 0xFF, 0x20);
    ParticleDef_CreateBC20(0x32, 1, 0x20, 0xA, 0xFF);
}

void ParticleEffect_AlphaBurst2(void) {
    ParticleDef_CreateDefault(0, 6, 0);
    ParticleDef_CreateQuick(0, ParticleEffect_StateHandlerF, &gParticleDefaultCallback, 0xFF, 1, 0xC, 7, 0x17, 6);
    ParticleDef_CreateBC20(0x32, 1, 0x20, 0xA, 0xFF);
    ParticleDef_Create31FAC(0x32, 1, 0xA, 0, 0xFF, 0x20);
}

void ParticleEffect_AlphaFirework(void) {
    ParticleDef_CreateDefault(0, 0x40, 0);
    ParticleDef_CreateQuick(0, ParticleEffect_AlphaStateHandler, &gParticleDefaultCallback, 0xFF, 1, 0xC, 8, 0x18, 0x20);
    ParticleDef_CreateFull(4, 4, 4, ParticleEffect_FireworkMain, &gParticleEffectData[0x34], 0, 3, 9, 0, 0x18, 0xD);
    ParticleDef_Create31EAC(8, 0xA, 0, 0xFF, 0x40);
    ParticleDef_CreateBC20CD(0, 0, 0x10, 0xA);
    ParticleSystem_AddSpawnOffset(0x21);
    ParticleDef_Create31EAC(0, 0xA, 0xFF, 0, 4);
    ParticleDef_CreateDefault(8, 4, 0xA);
}

void ParticleEffect_AlphaFirework2(void) {
    ParticleDef_CreateDefault(0, 0x40, 0);
    ParticleDef_CreateQuick(0, ParticleEffect_AlphaStateHandler, &gParticleDefaultCallback, 0xFF, 1, 0xC, 7, 0x17, 0x20);
    ParticleDef_CreateFull(4, 4, 4, ParticleEffect_FireworkMain, &gParticleEffectData[0x34], 0, 3, 9, 0, 0x18, 0xD);
    ParticleDef_Create31EAC(8, 0xA, 0, 0xFF, 0x40);
    ParticleDef_CreateBC20CD(0, 0, 0x10, 0xA);
    ParticleSystem_AddSpawnOffset(0x21);
    ParticleDef_Create31EAC(0, 0xA, 0xFF, 0, 4);
    ParticleDef_CreateDefault(8, 4, 0xA);
}

f32 GetParticleScaleForEffect(ParticleEffectInstance* arg0) {
    f32 sp1C = 1.0f;

    if (GetSpecies(arg0->unk_10) == 0x34) {
        sp1C = 1.75f;
    }
    return sp1C;
}

void ParticleEffect_InitSmallExplosion(void) {
    s16 sp46 = 7;

    if (IsEntityASpecies(0x14) != 0) {
        sp46 = gParticleTexture_Default;
    }
    ParticleDef_CreateDefault(0, 0x10, 6);
    ParticleDef_CreateQuick(0, ParticleEffect_StateHandlerF, &gParticleDefaultCallback, 0x80, 1, 0xC, 0xA, 0x1A, 4);
    ParticleDef_Create31FAC(0, 1, 0xC, 0, 0xC8, 3);
    ParticleDef_CreateFull(0x3C, 4, 0xE, ParticleEffect_BasicSetupHandler, &gParticleEffectData[0x3D], 0, 1, 0x11, sp46, 0x33, 7);
    ParticleDef_CreateFull(0x3D, 8, 7, ParticleEffect_BasicSetupHandler, &gParticleEffectData[0x3D], 0, 1, 0x11, sp46, 0x33, 7);
}

void ParticleEffect_InitLargeExplosion(void) {
    ParticleDef_CreateDefault(0, 0x20, 6);
    ParticleDef_CreateQuick(0, ParticleEffect_StateHandlerF, &gParticleDefaultCallback, 0x80, 1, 0xC, 0xA, 0x1A, 0x20);
}

void ParticleEffect_InitFire(void) {
    ParticleEffect_CreateMultipleNodes(0xE);
    ParticleDef_CreateDefault(0, 2, 0x10);
    ParticleDef_Create31EAC(0, 0xC, 0, 0xC8, 4);
    ParticleDef_Create321BC(0x32, 0xC, 0x19, 2, 0xC8);
    ParticleDef_CreateQuick(0x40, ParticleEffect_FireUpdate, &gParticleEffectData[0x4F], 0, 0x20, 7, 0, 0, 0);
}

void ParticleEffect_InitSmoke(void) {
    ParticleDef_CreateDefault(0, 0x20, 6);
    ParticleDef_Create31EAC(0, 0x14, 0, 0x80, 0x10);
    ParticleDef_CreateAlphaMode(0, 0xFF, 0, 0x10);
    ParticleDef_CreateQuick(0, ParticleEffect_StateHandlerC, &gParticleDefaultCallback, 0xFF, 1, 9, gParticleTexture_Default, 0x12, 0x20);
    ParticleDef_CreateFull(0, 1, 0xC, ParticleEffect_BasicSetupHandler, &gParticleEffectData[0x3D], 0, 1, 9, 0, 0x16, 5);
}

void ParticleEffect_PlaySoundAndReset(void) {
    ParticleDef_CreateQuick(0, ParticleEffect_StateHandlerA, &gParticleDefaultCallback, 0, 1, 9, 0, 0x13, 0);
    ParticleSystem_SetSpawnOffset(4);
    InitParticleEffectSet_Variant4();
}

void ParticleEffect_DrawQuad(Gfx* arg0, arg1_func_8434E21C* arg1, UNUSED u16 arg2) {
    ParticleEffectInstance* temp_v0;
    UNUSED s32 pad;
    s16 var_t2;
    s16 tmp;
    s16 sp82;
    s16 sp80;
    s16 sp7E;
    s16 sp7C;
    s16 sp7A;
    s16 sp78;
    s16 sp76;
    s16 sp74;
    s16 var_s1;
    s16 var_t1;
    UNUSED s16 pad2;
    s16 var_t5;

    temp_v0 = GetGraphNodeData(gDefaultGraphRoot);
    var_t1 = 0x96;
    var_t2 = 0xFF;
    var_s1 = 0x20;
    var_t5 = 5;
    tmp = arg1->unk_0A;

    switch (tmp) {
        case 1:
            sp82 = -5;
            sp80 = -0xF;
            sp7E = -0xA;
            sp7C = -0xA;
            sp7A = 0;
            sp78 = 1;
            sp76 = 0;
            sp74 = 1;
            break;

        case 2:
            sp82 = 5;
            sp80 = -0xF;
            sp7E = 0;
            sp7C = -0xA;
            sp7A = 0;
            sp78 = 0xF;
            sp76 = 0;
            sp74 = 0xF;
            break;

        case 3:
            sp82 = 5;
            sp80 = -0xF;
            sp7C = -0xA;
            sp7E = 0;
            sp7A = 1;
            sp78 = 1;
            sp76 = 1;
            sp74 = 1;
            break;

        case 4:
            sp82 = 5;
            sp80 = -0xF;
            sp7E = 0;
            sp7C = -0xA;
            sp7A = 0;
            sp78 = 0;
            sp76 = 0;
            sp74 = 0;
            break;

        case 5:
            sp82 = -5;
            sp80 = -0xA;
            sp7E = 0;
            sp7C = 0;
            sp7A = 1;
            sp78 = 0;
            sp76 = 0;
            sp74 = 0;
            var_t1 = 0x78;
            var_t2 = 0xC8;
            var_s1 = 0x40;
            var_t5 = 6;
            break;

        case 6:
            sp82 = 0;
            sp80 = -0xA;
            sp7E = 0;
            sp7C = 0;
            sp7A = 1;
            sp78 = 1;
            sp76 = 0;
            sp74 = 0;
            var_t1 = 0x78;
            var_t2 = 0xC8;
            var_s1 = 0x40;
            var_t5 = 6;
            break;
    }

    gDPPipeSync(arg0++);
    gDPSetPrimColor(arg0++, 0, var_t1, 255, var_t2, 0, temp_v0->prim_a);

    gDPLoadTextureTile_4b(arg0++, arg1->unk_00, G_IM_FMT_I, 32, 32, 0, 0, 31, 31, 0, G_TX_NOMIRROR | G_TX_WRAP,
                          G_TX_NOMIRROR | G_TX_WRAP, 5, 5, sp7A, sp78);

    Gfx_ScrollTextureToDL(arg0++, sp82, sp80, 0x20, 0x20);

    gDPLoadMultiTile_4b(arg0++, arg1->unk_04, 0x0100, 1, G_IM_FMT_I, var_s1, 0, 0, 0, var_s1 - 1, var_s1 - 1, 0,
                        G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, var_t5, var_t5, sp76, sp74);

    Gfx_ScrollTexture1ToDL(arg0++, sp7E, sp7C, var_s1, var_s1);

    gSPEndDisplayList(arg0++);
}

void ParticleEffect_AllocateDisplayList(s32 arg0, arg1_func_84344CE8* arg1) {
    if (arg0 == 2) {
        arg1->unk_18 = GfxAlloc(sizeof(Gfx) * 30);
        ParticleEffect_DrawQuad(arg1->unk_18, arg1->unk_14, gAnimationFrame);
    }
}

void ParticleEffect_TriggerEffect(void) {
    ParticleDef_CreateQuick(0, ParticleEffect_StateHandlerA, &gParticleDefaultCallback, 0, 1, 0xE, 5, 0x14, 0);
}

void ParticleEffect_TriggerSpecial(void) {
    ParticleDef_CreateQuick(0, ParticleEffect_StateHandlerF, &gParticleDefaultCallback, 0xBE, 1, 9, 6, 0x15, 2);
    ParticleDef_Create31EAC(8, 0xA, 0, 0xFF, 4);
    ParticleEffect_GroupSetupB();
}

void ParticleEffect_AlphaFadeHandler(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            ParticleEffect_ConfigureState(arg0, 0);
            Particle_SetTimerA6(arg0, 2);
            break;

        case 2:
            Particle_ApproachPrimG(arg0, 0, 0x20);

            if (Particle_DecrementTimerA6ToZero != NULL) {
                Particle_ApproachPrimAlpha(arg0, 0, 0x20);
            }

            if (Anim_HasReachedEnd(arg0->unk_14) != 0) {
                Particle_ClearActiveFlag(arg0);
            }
            break;
    }
}

void ParticleEffect_TriggerAnother(void) {
    ParticleDef_Create31EAC(4, 0xA, 0xFF, 0, 0x20);
    ParticleDef_CreateQuick(4, ParticleEffect_AlphaFadeHandler, &gParticleDefaultCallback, 0, 1, 9, 0, 0x19, 0);
}

void ParticleEffect_TriggerDefault1(void) {
    ParticleDef_CreateQuick(0, ParticleEffect_StateHandlerA, &gParticleDefaultCallback, 0, 1, 0x11, gParticleTexture_Default, 0x1B, 1);
}

void ParticleEffect_TriggerDefault2(void) {
    ParticleDef_CreateQuick(0, ParticleEffect_StateHandlerA, &gParticleDefaultCallback, 0, 1, 0x11, gParticleTexture_Default, 0x1C, 1);
}

void ParticleEffect_TriggerDefault3(void) {
    ParticleDef_CreateDefault(0, 0x20, 0);
    ParticleDef_CreateQuick(0, ParticleEffect_StateHandlerA, &gParticleDefaultCallback, 0, 1, 0x11, gParticleTexture_Default, 0x1B, 1);
}

void ParticleEffect_TriggerDefault4(void) {
    ParticleDef_Create31EAC(0, 0xC, 0, 0xFF, 0x40);
    ParticleDef_CreateQuick(0, ParticleEffect_StateHandlerA, &gParticleDefaultCallback, 0, 1, 0x11, gParticleTexture_Default, 0x1C, 1);
    ParticleDef_Create31EAC(0x30, 0xC, 0xFF, 0, 2);
}

void ParticleEffect_ColorStateHandler(ParticleEffectInstance* arg0) {
    s16 sp26 = Particle_GetShortCE(arg0);

    switch (arg0->unk_B2) {
        case 1:
            ParticleEffect_ConfigureState(arg0, 0);
            if (sp26 == 1) {
                Particle_SetScaleFactor1(arg0, 1.5f);
                Particle_AddVelocityBackward(arg0, 40.0f);
            }
            break;

        case 2:
            AreBothColorsSupported(arg0, 0x33, 0x40);
            Particle_ApproachPrimAlphaWithCallback(arg0, 0xFF, 0x40);
            break;

        case 3:
            AreBothColorsSupported(arg0, 0, 0x40);
            Particle_ApproachPrimAlphaWithCallback(arg0, 0, 0x40);
            break;

        case 4:
            Particle_ClearActiveFlag(arg0);
            break;
    }
}

void ParticleEffect_CreateWithCallback(void) {
    ParticleDef_CreateFull(0, 2, 3, ParticleEffect_ColorStateHandler, &gParticleDefaultCallback, 0, 1, 0x11, gParticleTexture_Default, 0x20, 0);
}

void ParticleEffect_CreateCallback(void) {
    ParticleDef_CreateQuick(0, ParticleEffect_ColorStateHandler, &gParticleDefaultCallback, 0, 1, 0x11, gParticleTexture_Default, 0x20, 1);
}

void ParticleEffect_ColorStateHandler2(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            ParticleEffect_ConfigureState(arg0, 0);
            break;

        case 2:
            AreBothColorsSupported(arg0, 0x33, 0x24);
            Particle_ApproachPrimAlpha(arg0, 0xFF, 0x1D);
            if (Anim_HasReachedEnd(arg0->unk_14) != 0) {
                Particle_ClearActiveFlag(arg0);
            }
            break;
    }
}

void ParticleEffect_CreateColorVariant(void) {
    ParticleDef_CreateQuick(0, ParticleEffect_ColorStateHandler2, &gParticleDefaultCallback, 0, 1, 0xA, 0, 0x1F, 0);
}

void ParticleEffect_SetMode(void) {
    ParticleDef_CreateDefault(0, 8, 0x22);
}

void ParticleEffect_ConfigureParameters(ParticleEffectInstance* arg0) {
    s16 sp26 = Particle_GetShortAC(arg0);
    s16 sp24 = Particle_GetShortCF(arg0);

    Particle_GetShortCE(arg0);

    switch (sp26) {
        case 0:
            Particle_SetVelocityScaledXYZ(arg0, 0.0f, 0.0f, 0.0f);
            break;

        case 1:
            Particle_SetVelocityScaledXYZ(arg0, 0.0f, 10.0f, 10.0f);
            break;

        case 2:
            Particle_SetVelocityScaledXYZ(arg0, 0.0f, 15.0f, -15.0f);
            break;
    }

    Particle_SetScaleFactor1(arg0, 0.1f);
    Particle_SetScaleFactor2(arg0, 2.0f);
    Particle_SetScaleFactor3(arg0, 0.0625f);
    SetPrimEnvColorFromPair(arg0, sp24);
    Particle_SetPrimAlpha(arg0, 0xFF);
    Particle_SetTimerA6(arg0, sp26 * 8);
    Particle_DisableFlag4(arg0);
    Particle_IncrementState(arg0);
}

void ParticleEffect_MainStateHandler(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            ParticleEffect_ConfigureParameters(arg0);
            break;

        case 2:
            if (Particle_DecrementTimerA6ToZeroWithCallback(arg0) != 0) {
                Particle_EnableFlag4(arg0);
                Particle_SetTimerA6(arg0, 0xA);
            }
            break;

        case 3:
            Particle_ApproachScaleFactor2(arg0);
            if (Particle_DecrementTimerA6ToZero(arg0) != 0) {
                Particle_ApproachPrimAlphaWithCallback(arg0, 0, 0x10);
            }
            break;

        case 4:
            Particle_ClearActiveFlag(arg0);
            break;
    }
}

void ParticleEffect_CreateVariant45(void) {
    ParticleDef_CreateQuick(0, ParticleEffect_MainStateHandler, &gParticleEffectData[0x39], 8, 3, 2, 0, 0x45, 0);
}

void ParticleEffect_CreateVariant47(void) {
    ParticleDef_CreateQuick(0, ParticleEffect_MainStateHandler, &gParticleEffectData[0x39], 8, 3, 2, 0, 0x47, 0);
}

void ParticleEffect_CreateTypeX(void) {
    ParticleDef_CreateQuick(0, ParticleEffect_HandleBurstState, &gParticleDefaultCallback, 0x1E, 3, 6, 0, 0, 0);
}

void ParticleEffect_CreateSmoke(void) {
    ParticleDef_CreateQuick(0, ParticleEffect_FireworkMain, &gParticleEffectData[0x34], 0, 1, 0x11, 9, 0, 6);
}

void ParticleEffect_CreateSmokeHighPriority(void) {
    ParticleDef_CreateQuick(0x10, ParticleEffect_FireworkMain, &gParticleEffectData[0x34], 0, 1, 0x11, 9, 0, 6);
}

void ParticleEffect_ConfigureParameters_Slow(ParticleEffectInstance* arg0) {
    s16 sp26 = Particle_GetShortAC(arg0);
    s16 sp24 = Particle_GetShortCF(arg0);

    Particle_GetShortCE(arg0);

    switch (sp26) {
        case 0:
            Particle_SetVelocityScaledXYZ(arg0, 0.0f, 0.0f, 0.0f);
            break;

        case 1:
            Particle_SetVelocityScaledXYZ(arg0, 0.0f, 10.0f, 10.0f);
            break;

        case 2:
            Particle_SetVelocityScaledXYZ(arg0, 0.0f, 15.0f, -15.0f);
            break;
    }

    Particle_SetScaleFactor1(arg0, 0.01f);
    Particle_SetScaleFactor2(arg0, 0.5f);
    Particle_SetScaleFactor3(arg0, 0.05f);
    SetPrimEnvColorFromPair(arg0, sp24);
    Particle_SetPrimAlpha(arg0, 0xFF);
    Particle_SetTimerA6(arg0, sp26 * 8);
    Particle_DisableFlag4(arg0);
    Particle_IncrementState(arg0);
}

void BattleAnim_CallbackStartEffect132Descriptor39DelayedRiseFade(ParticleEffectInstance* arg0) {
    switch (arg0->unk_B2) {
        case 1:
            ParticleEffect_ConfigureParameters_Slow(arg0);
            break;

        case 2:
            if (Particle_DecrementTimerA6ToZeroWithCallback(arg0) != 0) {
                Particle_EnableFlag4(arg0);
                Particle_SetTimerA6(arg0, 0xA);
            }
            break;

        case 3:
            Particle_ApproachScaleFactor2(arg0);
            Particle_AddScaledVelocityY(arg0, 1.0f);
            if (Particle_DecrementTimerA6ToZeroWithCallback(arg0) != 0) {
                Particle_SetTimerA6(arg0, 0x10);
            }
            break;

        case 4:
            Particle_ApproachSpeedScaled(arg0, 4.0f, 0.5f);
            Particle_AddScaledVelocityY(arg0, arg0->unk_74);
            Particle_ApproachPrimAlpha(arg0, 0, 0x10);
            if (Particle_DecrementTimerA6ToZeroWithCallback(arg0) != 0) {
                break;
            }
            break;

        case 5:
            Particle_ClearActiveFlag(arg0);
            break;
    }
}

void ParticleEffect_CreateDual(void) {
    ParticleDef_CreateQuick(0, BattleAnim_CallbackStartEffect132Descriptor39DelayedRiseFade, &gParticleEffectData[0x39], 8, 3, 2, 0, 0x46, 0);
    ParticleDef_CreateQuick(0x10, BattleAnim_CallbackStartEffect132Descriptor39DelayedRiseFade, &gParticleEffectData[0x39], 8, 3, 2, 0, 0x46, 0);
}
