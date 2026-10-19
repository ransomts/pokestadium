#include "fragment62.h"
#include "src/12D80.h"
#include "src/1C720.h"
#include "src/F420.h"
#include "src/fragments/34/fragment34.h"
#include "src/memory.h"

void ParticlePools_Allocate(void) {
    gParticleDefs = main_pool_alloc(sizeof(*gParticleDefs) * 300, 0);
    gParticleInstances = main_pool_alloc(sizeof(*gParticleInstances) * 300, 0);
    bzero(gParticleDefs, sizeof(*gParticleDefs) * 300);
    bzero(gParticleInstances, sizeof(*gParticleInstances) * 300);
    gParticleDefNextIdx = 0;
    gParticleAllocIndex = 0;
}

ParticleDef* ParticleDef_Allocate(void) {
    s32 i;
    s32 var_v0 = gParticleDefNextIdx;
    ParticleDef* var_v1 = &gParticleDefs[var_v0];

    for (i = 0; i < 300; i++) {
        if (var_v1->unk_15 == 0) {
            break;
        }

        var_v0++;

        if (var_v0 >= 300) {
            var_v0 = 0;
            var_v1 = &gParticleDefs[0];
        } else {
            var_v1++;
        }
    }

    if (i >= 300) {
        var_v1 = -1;
    } else {
        var_v1->unk_15 = 1;
        
        gParticleDefNextIdx = var_v0 + 1;
        if (gParticleDefNextIdx >= 300) {
            gParticleDefNextIdx = 0;
        }
    }

    return var_v1;
}

void ParticleDef_Reset(ParticleDef* arg0) {
    arg0->unk_0E = 0;
    arg0->unk_15 = 0;
    arg0->unk_14 = 0;
    arg0->unk_0C = arg0->unk_0E;
}

void ParticleNode_Init(ParticleEffectInstance* arg0, Vec3f arg1, Vec3s arg2, s32 arg3, s32 arg4) {
    while (arg0 != NULL) {
        Vec3f_Copy(&arg0->unk_68, &arg1);
        Vec3s_CopyTo(&arg0->unk_94, &arg2);
        arg0->unk_08 = arg3;
        arg0->unk_0C = arg4;
        arg0->unk_10 = 0;
        arg0->unk_14 = 0;
        arg0->unk_CD = 0xFF;

        arg0 = arg0->next;
    }
}

void ParticleNode_CopyFrom(ParticleEffectInstance* arg0, ParticleEffectInstance* arg1, func_unk_D_8140E724_008 arg2, ParticleEffectData* arg3,
                   s32 arg4) {
    arg0->unk_08 = arg2;
    arg0->unk_0C = arg3;
    arg0->unk_10 = arg1->unk_10;
    arg0->unk_CF = arg1->unk_CF;
    arg0->unk_CA = arg1->unk_CA;
    arg0->unk_CC = 0x1C;
    arg0->unk_CD = 0xFF;
    arg0->unk_CE = arg1->unk_CE;
    arg0->unk_CB = arg1->unk_CB;
    arg0->unk_74 = arg1->unk_74;

    Particle_SetShortAC(arg0, arg4);

    Vec3f_Copy(&arg0->unk_38, &arg1->unk_38);
    Vec3f_Copy(&arg0->unk_50, &arg1->unk_50);
    Vec3f_Copy(&arg0->unk_68, &arg1->unk_68);
    Vec3f_Copy(&arg0->unk_7C, &arg1->unk_7C);
    Vec3s_CopyTo(&arg0->unk_94, &arg1->unk_94);
    Vec3s_CopyTo(&arg0->unk_9A, &arg1->unk_9A);

    if (arg1->unk_CA == 4) {
        arg0->unk_CA = 0;
    }
}

void ParticleNode_CreateMultiple(ParticleEffectInstance* arg0, func_unk_D_8140E724_008 arg1, ParticleEffectData* arg2, s16 arg3) {
    s16 i;
    ParticleEffectInstance* temp_v0;

    for (i = 0; i < arg3; i++) {
        temp_v0 = Particle_AllocateInstance();
        if ((u32)temp_v0 == -1) {
            break;
        }
        ParticleNode_CopyFrom(temp_v0, arg0, arg1, arg2, i);
    }
}

void Particle_CreateChildParticles(ParticleEffectInstance* arg0, func_unk_D_8140E724_008 arg1, ParticleEffectData* arg2, s16 arg3, s16 arg4,
                   s16 arg5) {
    s16 i;
    ParticleEffectInstance* temp_v0;

    for (i = 0; i < arg3; i++) {
        temp_v0 = Particle_AllocateInstance();
        if ((u32)temp_v0 == -1) {
            break;
        }
        ParticleNode_CopyFrom(temp_v0, arg0, arg1, arg2, i);
        temp_v0->unk_CE = arg5;
        temp_v0->unk_CF = arg4;
    }
}

ParticleEffectInstance* ParticleNode_CreateAt(s16 arg0, s16 arg1, s32 arg2, f32 arg3) {
    ParticleEffectInstance* temp_v0 = Particle_AllocateInstance();

    if ((u32)temp_v0 != -1) {
        Vec3f_Set(&temp_v0->unk_38, arg0, arg1, 0.0f);
        Particle_UpdateTransform(temp_v0);
        Vec3s_Set(&temp_v0->unk_94, arg2, arg2, arg2);
        temp_v0->unk_1C = arg3;
        Particle_SetFlag(temp_v0, 0x108);
    }
    return temp_v0;
}

void ParticleNode_ProcessChild(ParticleEffectInstance* arg0) {
    if (arg0->unk_14 != NULL) {
        if (Particle_HasFlag(arg0, 0x400) != 0) {
            FreeParticleNode(arg0->unk_14);
        } else {
            FreeGraphNode(arg0->unk_14);
        }
    }
}

void ParticleNode_Destroy(ParticleEffectInstance* arg0) {
    ParticleNode_ProcessChild(arg0);
    arg0->unk_18 = 0;
    Particle_ResetState(arg0);
    Particle_Free(arg0);
}

void ParticleNode_UpdateBehavior(ParticleEffectInstance* arg0) {
    Vec3f sp3C;
    Vec3f sp30;
    Vec3s sp28;

    switch (arg0->unk_CC) {
        case 0:
            GetEntityPosition(arg0->unk_10, &arg0->unk_68);
            break;

        case 1:
            GetEntityCenterPosition(arg0->unk_10, &arg0->unk_68);
            break;

        case 27:
            GetEntityCenterPosition(arg0->unk_10, &arg0->unk_68);
            arg0->unk_68.y = 0.0f;
            break;

        case 9:
            Model_GetNodePosition(arg0->unk_10, 0x64, &arg0->unk_68);
            break;

        case 10:
            Model_GetNodePosition(arg0->unk_10, 0x64, &arg0->unk_68);
            arg0->unk_68.y = 0.0f;
            break;

        case 11:
            Model_GetNodePosition(arg0->unk_10, 0x64, &arg0->unk_68);
            GetEntityRotation(arg0->unk_10, &sp28);
            GetEntityScaleDimensions(arg0->unk_10, &sp30);
            Vec3f_SetPolarXZ(&sp3C, sp30.x * 25.0f, sp28.y);
            Vec3f_Offset(&arg0->unk_68, &sp3C);
            break;

        case 12:
            Model_GetNodePosition(arg0->unk_10, 0x64, &arg0->unk_68);
            GetEntityRotation(arg0->unk_10, &sp28);
            GetEntityScaleDimensions(arg0->unk_10, &sp30);
            Vec3f_SetPolarXZ(&sp3C, sp30.x * 25.0f, sp28.y + 0x8000);
            Vec3f_Offset(&arg0->unk_68, &sp3C);
            break;

        case 13:
            Model_GetNodePosition(arg0->unk_10, 0x64, &arg0->unk_68);
            GetEntityScaleDimensions(arg0->unk_10, &sp30);
            arg0->unk_68.y += sp30.y * 25.0f;
            break;

        case 14:
            Model_GetNodePosition(arg0->unk_10, 0x64, &arg0->unk_68);
            GetEntityScaleDimensions(arg0->unk_10, &sp30);
            arg0->unk_68.y -= sp30.y * 25.0f;
            if (arg0->unk_68.y <= 0.0f) {
                arg0->unk_68.y = 0.0f;
            }
            break;

        case 15:
            Model_GetNodePosition(arg0->unk_10, 0x64, &arg0->unk_68);
            GetEntityRotation(arg0->unk_10, &sp28);
            GetEntityScaleDimensions(arg0->unk_10, &sp30);
            Vec3f_SetPolarXZ(&sp3C, sp30.x * 25.0f, sp28.y);
            Vec3f_Offset(&arg0->unk_68, &sp3C);
            arg0->unk_68.y = 0.0f;
            break;

        case 17:
            Model_GetNodePosition(arg0->unk_10, arg0->unk_CD, &arg0->unk_68);
            break;

        case 19:
            Model_GetNodePosition(arg0->unk_10, arg0->unk_CD, &arg0->unk_68);
            GetEntityRotation(arg0->unk_10, &sp28);
            GetEntityScaleDimensions(arg0->unk_10, &sp30);
            Vec3f_SetPolarXZ(&sp3C, sp30.x * 25.0f, sp28.y);
            Vec3f_Offset(&arg0->unk_68, &sp3C);
            break;

        case 30:
            GetEntityOffsetPosition(arg0->unk_10, &arg0->unk_68);
            break;
    }
}

void ParticleNode_UpdateBehaviorAlt(ParticleEffectInstance* arg0) {
    Vec3f sp3C;
    Vec3f sp30;
    Vec3s sp28;

    switch (arg0->unk_CC) {
        case 2:
            Model_GetNodePosition(arg0->unk_10, 0x64, &arg0->unk_68);
            break;

        case 3:
            Model_GetNodePosition(arg0->unk_10, 0x64, &arg0->unk_68);
            arg0->unk_68.y = 0.0f;
            break;

        case 4:
            Model_GetNodePosition(arg0->unk_10, 0x64, &arg0->unk_68);
            GetEntityRotation(arg0->unk_10, &sp28);
            GetEntityScaleDimensions(arg0->unk_10, &sp30);
            Vec3f_SetPolarXZ(&sp3C, sp30.x * 25.0f, sp28.y);
            Vec3f_Offset(&arg0->unk_68, &sp3C);
            break;

        case 5:
            Model_GetNodePosition(arg0->unk_10, 0x64, &arg0->unk_68);
            GetEntityRotation(arg0->unk_10, &sp28);
            GetEntityScaleDimensions(arg0->unk_10, &sp30);
            Vec3f_SetPolarXZ(&sp3C, sp30.x * 25.0f, sp28.y + 0x8000);
            Vec3f_Offset(&arg0->unk_68, &sp3C);
            break;

        case 6:
            Model_GetNodePosition(arg0->unk_10, 0x64, &arg0->unk_68);
            GetEntityScaleDimensions(arg0->unk_10, &sp30);
            arg0->unk_68.y += sp30.y * 25.0f;
            break;

        case 7:
            Model_GetNodePosition(arg0->unk_10, 0x64, &arg0->unk_68);
            GetEntityScaleDimensions(arg0->unk_10, &sp30);
            arg0->unk_68.y -= sp30.y * 25.0f;
            if (arg0->unk_68.y <= 0.0f) {
                arg0->unk_68.y = 0.0f;
            }
            break;

        case 8:
            Model_GetNodePosition(arg0->unk_10, 0x64, &arg0->unk_68);
            GetEntityRotation(arg0->unk_10, &sp28);
            GetEntityScaleDimensions(arg0->unk_10, &sp30);
            Vec3f_SetPolarXZ(&sp3C, sp30.x * 25.0f, sp28.y);
            Vec3f_Offset(&arg0->unk_68, &sp3C);
            arg0->unk_68.y = 0.0f;
            break;

        case 16:
            Model_GetNodePosition(arg0->unk_10, arg0->unk_CD, &arg0->unk_68);
            break;

        case 18:
            Model_GetNodePosition(arg0->unk_10, arg0->unk_CD, &arg0->unk_68);
            break;

        case 29:
            GetEntityOffsetPosition(arg0->unk_10, &arg0->unk_68);
            break;
    }
}

void ParticleNode_UpdateScale(ParticleEffectInstance* arg0) {
    if ((arg0->unk_10 == NULL) || (Particle_HasFlag(arg0, 0x108) != 0)) {
        gParticleScaleFactor.unk_00.x = 1.0f;
        gParticleScaleFactor.unk_00.y = 1.0f;
        gParticleScaleFactor.unk_00.z = 1.0f;
    } else if (Particle_CanSetFlag(arg0, 0x800) != 0) {
        gParticleScaleFactor.unk_00.x = GetEntityScaleFactor(arg0->unk_10);
        gParticleScaleFactor.unk_00.y = GetEntityScaleFactor(arg0->unk_10);
        gParticleScaleFactor.unk_00.z = GetEntityScaleFactor(arg0->unk_10);
    }
}

void ParticleNode_UpdateOrDestroy(ParticleEffectInstance* arg0) {
    if (Particle_IsInactive(arg0) != 0) {
        ParticleNode_Destroy(arg0);
    } else {
        Particle_UpdateTransform(arg0);
    }
}

void ParticleSystem_Update(void) {
    s32 i;
    ParticleEffectInstance* var_s0 = gParticleInstances;

    for (i = 0; i < 300; i++, var_s0++) {
        if (var_s0->unk_D0 != 0) {
            ParticleNode_UpdateBehaviorAlt(var_s0);
            ParticleNode_UpdateScale(var_s0);
            var_s0->unk_08(var_s0);
            ParticleNode_UpdateOrDestroy(var_s0);
        }
    }
}

void ParticleInstance_Configure(ParticleEffectInstance* arg0, unk_BattlePlayerEntity* arg1, ParticleDef* arg2, s16 arg3) {
    if ((u32)arg0 == -1) {
        return;
    }

    if (1) {}
    if (1) {}
    if (1) {}
    if (1) {}
    if (1) {}
    if (1) {}

    while (arg0 != NULL) {
        arg0->unk_10 = arg1;
        arg0->unk_AC = arg3++;
        arg0->unk_08 = arg2->unk_00;
        arg0->unk_0C = arg2->unk_04;
        arg0->unk_CD = arg2->unk_19;
        arg0->unk_CE = arg2->unk_1A;
        arg0->unk_AA = arg2->unk_12;
        arg0->unk_CF = arg2->unk_1B;
        arg0->unk_CA = arg2->unk_17;
        arg0->unk_CC = arg2->unk_16;
        arg0->unk_CB = arg2->unk_18;
        arg0->unk_A6 = arg2->unk_10;

        if (arg1 != NULL) {
            ParticleNode_UpdateBehavior(arg0);
            GetEntityRotation(arg0->unk_10, &arg0->unk_94);
        }

        if ((arg2->unk_16 & 0xFFFFu) == 0x12) {
            arg0->unk_A6 = arg2->unk_10 * arg3;
        }

        arg0 = arg0->next;
    }
}

void ParticleDef_SpawnInstances(ParticleDef* arg0, s32 arg1) {
    s16 i;
    s16 var_s2;
    ParticleEffectData* temp_a2 = arg0->unk_04;
    ParticleRenderSettings* temp_a3 = arg0->unk_04->unk_04.a;
    unk_BattlePlayerEntity* tmp08 = arg0->unk_08;
    s16 tmp12 = arg0->unk_12;

    switch (arg1) {
        case 0:
            var_s2 = tmp12;
            break;

        case 1:
            var_s2 = arg0->unk_10 / tmp12;
            arg0->unk_10 = tmp12;
            break;
    }

    if ((temp_a2->unk_00 == 1) && (temp_a3->unk_00 == 1)) {
        ParticleInstance_Configure(Particle_AllocateChain(var_s2), tmp08, arg0, 0);
        return;
    }

    for (i = 0; i < var_s2; i++) {
        ParticleInstance_Configure(Particle_AllocateInstance(), tmp08, arg0, i);
    }
}

void ParticleDef_SpawnAll(ParticleDef* arg0) {
    ParticleDef_SpawnInstances(arg0, 0);
}

void ParticleDef_SpawnBurst(ParticleDef* arg0) {
    ParticleDef_SpawnInstances(arg0, 1);
}

void ParticleDef_SpawnSingle(ParticleDef* arg0) {
    UNUSED s32 pad;
    unk_BattlePlayerEntity* sp18 = arg0->unk_08;

    ParticleInstance_Configure(Particle_AllocateInstance(), sp18, arg0, 0);
}

void ParticleDef_SpawnByType(ParticleDef* arg0) {
    switch (arg0->unk_16) {
        case 18:
            ParticleDef_SpawnBurst(arg0);
            break;

        case 22:
            ParticleInstance_Configure(ParticleNode_CreateAt(0xA0, 0x78, 0, 1.0f), 0, arg0, 0);
            break;

        case 24:
            ParticleInstance_Configure(ParticleNode_CreateAt(0, 0, 0, 1.0f), 0, arg0, 0);
            break;

        case 23:
            SetGameStateFlag(arg0->unk_19);
            break;

        case 25:
            InitWaterEffect(arg0->unk_19);
            break;

        case 26:
            ParticleDef_SpawnSingle(arg0);
            break;

        default:
            ParticleDef_SpawnAll(arg0);
            break;
    }
}

void ParticleDefs_Update(void) {
    s32 i;
    ParticleDef* var_s0 = gParticleDefs;

    for (i = 0; i < 300; i++, var_s0++) {
        if (var_s0->unk_15 != 0) {
            var_s0->unk_0E--;
            if (var_s0->unk_0E <= 0) {
                if (var_s0->unk_14 >= 0) {
                    ParticleDef_SpawnByType(var_s0);
                    if (var_s0->unk_14 != 0x7F) {
                        var_s0->unk_14--;
                    }

                    if (var_s0->unk_14 <= 0) {
                        ParticleDef_Reset(var_s0);
                    } else {
                        var_s0->unk_0E = var_s0->unk_0C;
                    }
                } else if (var_s0->unk_14 == -1) {
                    var_s0->unk_0E = var_s0->unk_0C;
                    ParticleDef_SpawnByType(var_s0);
                }
            }
        }
    }
}

void Particles_UpdateAll(void) {
    ParticleDefs_Update();
    ParticleSystem_Update();
}

void ParticleSystem_ResetKeepSpecial(void) {
    s32 i;
    ParticleDef* var_s0 = gParticleDefs;
    ParticleEffectInstance* var_s2 = gParticleInstances;

    ParticleSystem_ResetSpawnOffset();

    for (i = 0; i < 300; i++, var_s0++) {
        if (var_s0->unk_15 != 0) {
            if ((var_s0->unk_17 != 4) && (var_s0->unk_17 != 7)) {
                ParticleDef_Reset(var_s0);
            }
        }
    }

    for (i = 0; i < 300; i++, var_s2++) {
        if (var_s2->unk_D0 != 0) {
            if ((var_s2->unk_CA != 4) && (var_s2->unk_CA != 7)) {
                ParticleNode_Destroy(var_s2);
            }
        }
    }
}

void ParticleSystem_ResetKeepType4(void) {
    s32 i;
    ParticleDef* var_s0 = gParticleDefs;
    ParticleEffectInstance* var_s2 = gParticleInstances;

    for (i = 0; i < 300; i++, var_s0++) {
        if ((var_s0->unk_15 != 0) && (var_s0->unk_17 != 4)) {
            ParticleDef_Reset(var_s0);
        }
    }

    for (i = 0; i < 300; i++, var_s2++) {
        if ((var_s2->unk_D0 != 0) && (var_s2->unk_CA != 4)) {
            ParticleNode_Destroy(var_s2);
        }
    }

    GraphNode_SetColorRGBA(&sActivePokemon[0]->unk_000, 0xFF, 0xFF, 0xFF, 0);
    GraphNode_SetColorRGBA(&sActivePokemon[1]->unk_000, 0xFF, 0xFF, 0xFF, 0);
    GraphNode_SetState(&sActivePokemon[0]->unk_000, 0xFF);
    GraphNode_SetState(&sActivePokemon[1]->unk_000, 0xFF);

    gSavedPrimColorB = 0xFF;
    gSavedPrimColorG = gSavedPrimColorB;
    gSavedPrimColorR = gSavedPrimColorG;
}

s32 GetParticleSpecialFlag(void) {
    return D_84390340;
}

void SetParticleSpecialFlagFromGlobal(void) {
    if (gSpecialFlag != 0) {
        D_84390340 = 1;
    } else {
        D_84390340 = 0;
    }
}

void ParticleCameraCallbacks_Clear(void) {
    s32 i;

    for (i = 0; i < 8; i++) {
        if (gCameraCallbackFuncs[i] != NULL) {
            gCameraCallbackFuncs[i] = NULL;
            gCameraUpdateFuncs[i] = NULL;
        }
    }

    D_84390340 = 0;
}

s32 ParticleSystem_IsResettable(void) {
    s32 var_v1 = 0;

    if (D_843902F8 == 0) {
        var_v1 = 1;
    }
    return var_v1;
}

void ParticleSystem_SetResetLock(void) {
    D_843902F8 = 1;
}

void ParticleSystem_ClearResetLock(void) {
    D_843902F8 = 0;
}

void ParticleSystem_ForceResetLock(void) {
    ParticleSystem_SetResetLock();
}

void Battle_SetAnimChannelFlag(s32 arg0) {
    ParticleSystem_ResetSpawnOffset();
    switch (arg0) {
        case 1:
            ParticleSystem_ResetKeepSpecial();
            if (ParticleSystem_IsResettable() != 0) {
                ParticleCameraCallbacks_Clear();
            }
            break;

        case 2:
            ParticleSystem_ResetKeepType4();
            ParticleCameraCallbacks_Clear();
            ParticleSystem_ClearResetLock();
            BattleAnim_ReinitAuxiliaryEffects();
            break;
    }
}

void ParticleNode_TriggerByEntity(u8 arg0, unk_BattlePlayerEntity* arg1) {
    s32 i;
    ParticleEffectInstance* var_s0 = gParticleInstances;

    for (i = 0; i < 300; i++, var_s0++) {
        if ((var_s0->unk_D0 != 0) && (var_s0->unk_CA == 4) && (var_s0->unk_CB == arg0) && (arg1 == var_s0->unk_10)) {
            Particle_SetFlag(var_s0, 0x1000);
            Particle_IncrementState(var_s0);
        }
    }
}

void ParticleSystem_ResetSpawnOffset(void) {
    D_843902A8 = 0;
}

void ParticleSystem_SetSpawnOffset(s32 arg0) {
    D_843902A8 = arg0;
}

void ParticleSystem_AddSpawnOffset(s32 arg0) {
    D_843902A8 += arg0;
}

void ParticleSystem_ResetSpawnOffset2(void) {
    ParticleSystem_ResetSpawnOffset();
}

ParticleDef* ParticleDef_Create(s32 arg0, s32 arg1, s8 arg2, func_unk_D_8140E724 arg3, ParticleEffectData* arg4,
                              unk_BattlePlayerEntity* arg5, s16 arg6, s16 arg7, u8 arg8, u8 arg9, u8 argA, u8 argB) {
    ParticleDef* sp1C = ParticleDef_Allocate();

    if ((u32)sp1C != -1) {
        sp1C->unk_0E = arg0 + D_843902A8;
        sp1C->unk_0C = arg1;
        sp1C->unk_14 = arg2;
        sp1C->unk_00 = arg3;
        sp1C->unk_04 = arg4;
        sp1C->unk_08 = arg5;
        sp1C->unk_16 = arg8;
        sp1C->unk_10 = arg6;
        sp1C->unk_12 = arg7;
        sp1C->unk_19 = arg9;
        sp1C->unk_1A = argB;
        sp1C->unk_1B = argA;
        sp1C->unk_17 = GetActionScriptSubIndex();
        sp1C->unk_18 = GetActionScriptMode();
    }
    return sp1C;
}

ParticleDef* ParticleDef_CreateQuick(s32 arg0, func_unk_D_8140E724 arg1, ParticleEffectData* arg2, s16 arg3, s16 arg4, u8 arg5,
                              u8 arg6, u8 arg7, u8 arg8) {
    return ParticleDef_Create(arg0, 0, 1, arg1, arg2, gParticleEffectEntityA, arg3, arg4, arg5, arg6, arg7, arg8);
}

ParticleDef* ParticleDef_CreateFull(s32 arg0, s32 arg1, s8 arg2, func_unk_D_8140E724 arg3, ParticleEffectData* arg4, s16 arg5,
                              s16 arg6, u8 arg7, u8 arg8, u8 arg9, u8 argA) {
    return ParticleDef_Create(arg0, arg1, arg2, arg3, arg4, gParticleEffectEntityA, arg5, arg6, arg7, arg8, arg9, argA);
}

ParticleDef* ParticleDef_CreateDefault(s32 arg0, s16 arg1, u8 arg2) {
    return ParticleDef_Create(arg0, 0, 1, BattleAnim_CallbackGlobalTintColorFadeDetach, &gParticleDefaultCallback, NULL, 0, arg1, 0x16, 0, arg2, 0);
}

ParticleDef* ParticleDef_CreateBC20(s32 arg0, s16 arg1, s16 arg2, u8 arg3, u8 arg4) {
    return ParticleDef_Create(arg0, 0, 1, Fragment_ProcessBC20Variant, &gParticleEffectData[37], NULL, arg1, arg2, 0x16, arg4, arg3, 0);
}

ParticleDef* ParticleDef_CreateBC20CD(s32 arg0, s16 arg1, s16 arg2, u8 arg3) {
    return ParticleDef_Create(arg0, 0, 1, Fragment_ProcessBC20WithCDMode, &gParticleEffectData[37], NULL, arg1, arg2, 0x16, 0xFF, arg3, 0);
}

ParticleDef* ParticleDef_CreateBC20CDAlt(s32 arg0, s16 arg1, s16 arg2, u8 arg3, u8 arg4) {
    return ParticleDef_Create(arg0, 0, 1, Fragment_ProcessBC20WithCDMode, &gParticleEffectData[37], NULL, arg1, arg2, 0x16, arg4, arg3, 0);
}

ParticleDef* ParticleDef_CreateBC20CDFull(s32 arg0, s32 arg1, s8 arg2, s16 arg3, s16 arg4, u8 arg5, u8 arg6) {
    return ParticleDef_Create(arg0, arg1, arg2, Fragment_ProcessBC20WithCDMode, &gParticleEffectData[37], NULL, arg3, arg4, 0x16, arg6, arg5, 0);
}

ParticleDef* ParticleDef_Create32E6C(s32 arg0, s16 arg1, s16 arg2, u8 arg3) {
    return ParticleDef_Create(arg0, 0, 1, BattleAnim_CallbackDescriptor25AlphaFadeInHold, &gParticleEffectData[37], NULL, arg1, arg2, 0x16, 0xFF, arg3, 0);
}

ParticleDef* ParticleDef_Create32E6CAlt(s32 arg0, s16 arg1, s16 arg2, u8 arg3, u8 arg4) {
    return ParticleDef_Create(arg0, 0, 1, BattleAnim_CallbackDescriptor25AlphaFadeInHold, &gParticleEffectData[37], NULL, arg1, arg2, 0x16, arg4, arg3, 0);
}

ParticleDef* ParticleDef_Create32E6CFull(s32 arg0, s32 arg1, s8 arg2, s16 arg3, s16 arg4, u8 arg5, u8 arg6) {
    return ParticleDef_Create(arg0, arg1, arg2, BattleAnim_CallbackDescriptor25AlphaFadeInHold, &gParticleEffectData[37], NULL, arg3, arg4, 0x16, arg6, arg5, 0);
}

ParticleDef* ParticleDef_Create32F30(s32 arg0, s16 arg1, u8 arg2) {
    return ParticleDef_Create(arg0, 0, 1, BattleAnim_CallbackDescriptor25AlphaHoldDetach, &gParticleEffectData[37], NULL, arg1, 0, 0x16, 0xFF, arg2, 0);
}

ParticleDef* ParticleDef_Create32F30Alt(s32 arg0, s16 arg1, u8 arg2, u8 arg3) {
    return ParticleDef_Create(arg0, 0, 1, BattleAnim_CallbackDescriptor25AlphaHoldDetach, &gParticleEffectData[37], NULL, arg1, 0, 0x16, arg3, arg2, 0);
}

ParticleDef* ParticleDef_Create32F30Full(s32 arg0, s32 arg1, s8 arg2, s16 arg3, u8 arg4, u8 arg5) {
    return ParticleDef_Create(arg0, arg1, arg2, BattleAnim_CallbackDescriptor25AlphaHoldDetach, &gParticleEffectData[37], NULL, arg3, 0, 0x16, arg5, arg4, 0);
}

ParticleDef* ParticleDef_Create32FD0(s32 arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4) {
    return ParticleDef_Create(arg0, 0, 1, BattleAnim_CallbackDescriptor25PaletteFadeOut, &gParticleEffectData[37], NULL, arg1, arg2, 0x16, arg4, arg3, 0);
}

ParticleDef* ParticleDef_Create330A0(s32 arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4) {
    return ParticleDef_Create(arg0, 0, 1, BattleAnim_CallbackDescriptor25PaletteFadeIn, &gParticleEffectData[37], NULL, arg1, arg2, 0x16, arg4, arg3, 0);
}

ParticleDef* ParticleDef_Create31EAC(s32 arg0, u8 arg1, s16 arg2, s16 arg3, s16 arg4) {
    return ParticleDef_Create(arg0, 0, 1, BattleAnim_CallbackOwnerModelTintRampDetach, &gParticleDefaultCallback, gParticleEffectEntityA, arg2, arg4, 0x1A, arg3, arg1, 0);
}

ParticleDef* ParticleDef_Create31FAC(s32 arg0, s16 arg1, u8 arg2, s16 arg3, s16 arg4, s16 arg5) {
    return ParticleDef_Create(arg0, 0, 1, BattleAnim_CallbackOwnerModelTintPulseDetach, &gParticleDefaultCallback, gParticleEffectEntityA, arg1, arg5, 0x1A, arg4, arg2, arg3);
}

ParticleDef* ParticleDef_Create320A4(s32 arg0, s16 arg1, u8 arg2, s16 arg3, s16 arg4) {
    return ParticleDef_Create(arg0, 0, 1, BattleAnim_CallbackOwnerModelTintHoldFadeDetach, &gParticleDefaultCallback, gParticleEffectEntityA, arg1, arg4, 0x1A, 0, arg2, arg3);
}

ParticleDef* ParticleDef_Create321BC(s32 arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4) {
    return ParticleDef_Create(arg0, 0, 1, BattleAnim_CallbackOwnerModelTintPaletteApproachInactive, &gParticleDefaultCallback, gParticleEffectEntityA, arg4, arg3, 0x1A, arg2, arg1, 0);
}

ParticleDef* ParticleDef_Create321BCAlt(s32 arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4) {
    return ParticleDef_Create(arg0, 0, 1, BattleAnim_CallbackOwnerModelTintPaletteApproachInactive, &gParticleDefaultCallback, gParticleEffectEntityA, arg4, arg3, 0x1A, arg2, arg1, 0);
}

ParticleDef* ParticleDef_Create323BC(s32 arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5) {
    return ParticleDef_Create(arg0, 0, 1, BattleAnim_CallbackOwnerModelTintPaletteCycle, &gParticleDefaultCallback, gParticleEffectEntityA, arg4, arg3, 0x1A, arg2, arg1, arg5);
}

ParticleDef* ParticleDef_Create323BCAlt(s32 arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5) {
    return ParticleDef_Create(arg0, 0, 1, BattleAnim_CallbackOwnerModelTintPaletteCycle, &gParticleDefaultCallback, gParticleEffectEntityA, arg4, arg3, 0x1A, arg2, arg1, arg5);
}

ParticleDef* ParticleDef_Create32604(s32 arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5) {
    return ParticleDef_Create(arg0, 0, 1, BattleAnim_CallbackOwnerModelTintPaletteFade, &gParticleDefaultCallback, gParticleEffectEntityA, arg4, arg3, 0x1A, arg2, arg1, arg5);
}

ParticleDef* ParticleDef_Create327B8(s32 arg0, s16 arg1, u8 arg2) {
    return ParticleDef_Create(arg0, 0, 1, BattleAnim_CallbackOwnerModelTintRandomPaletteCycle, &gParticleDefaultCallback, gParticleEffectEntityA, 0, arg1, 0x1A, arg2, 0, 0);
}

ParticleDef* ParticleDef_CreateComplexColor(s32 arg0, s16 arg1, s16 arg2, u8 arg3) {
    return ParticleDef_Create(arg0, 0, 1, Fragment_ComplexColorMode, &gParticleDefaultCallback, gParticleEffectEntityA, arg1, arg2, 0x1A, arg3, 0, 0);
}

ParticleDef* ParticleDef_CreateAlphaMode(s32 arg0, s16 arg1, s16 arg2, s16 arg3) {
    return ParticleDef_Create(arg0, 0, 1, Fragment_ProcessAlphaMode, &gParticleDefaultCallback, gParticleEffectEntityA, arg1, arg3, 0x1A, arg2, 0, 0);
}

ParticleDef* ParticleDef_CreateAlphaModeFF(s32 arg0) {
    return ParticleDef_Create(arg0, 0, 1, Fragment_ProcessAlphaMode, &gParticleDefaultCallback, gParticleEffectEntityA, 0xFF, 0xFF, 0x1A, 0xFF, 0, 0);
}

ParticleDef* ParticleDef_CreateAlphaModeZero(s32 arg0) {
    return ParticleDef_Create(arg0, 0, 1, Fragment_ProcessAlphaMode, &gParticleDefaultCallback, gParticleEffectEntityA, 0, 0xFF, 0x1A, 0, 0, 0);
}

ParticleDef* ParticleDef_CreateNullType17(s32 arg0, u8 arg1) {
    return ParticleDef_Create(arg0, 0, 1, NULL, NULL, 0, 0, 0, 0x17, arg1, 0, 0);
}

ParticleDef* ParticleDef_CreateNullType19(s32 arg0, u8 arg1) {
    return ParticleDef_Create(arg0, 0, 1, NULL, NULL, gParticleEffectEntityA, 0, 0, 0x19, arg1, 0, 0);
}

void BattleAnim_EffectStartNop(void) {
}

void BattleAnim_EffectEndNop(void) {
}

void SetGameStateFlag(s32 arg0) {
    gGameStateFlag = arg0;
}

void ClearGameStateFlag(void) {
    gGameStateFlag = 0;
}

s32 GetGameStateFlag(void) {
    return gGameStateFlag;
}

s32 IsEntityASpecies(s32 arg0) {
    s32 sp1C = 0;

    if (GetSpecies(gParticleEffectEntityA) == arg0) {
        sp1C = 1;
    }
    return sp1C;
}

s32 GetSpeciesPrimaryEffect(void) {
    return GetSpecies(gParticleEffectData_42);
}

s32 GetSpeciesSecondaryEffect(void) {
    return GetSpecies(gParticleEffectEntityB);
}

void Model_GetNodePosition(unk_BattlePlayerEntity* arg0, s16 arg1, Vec3f* arg2) {
    s32 sp24 = 0;

    if (arg0 != NULL) {
        if (arg1 == 0x64) {
            if (Graph_GetRecordedPosition(&arg0->unk_000, 0xA, arg2) != NULL) {
                sp24 = 1;
            } else if (Graph_GetRecordedPosition(&arg0->unk_000, 0x64, arg2) != NULL) {
                sp24 = 2;
            }
        } else {
            if (Graph_GetRecordedPosition(&arg0->unk_000, arg1, arg2) == NULL) {
                if (Graph_GetRecordedPosition(&arg0->unk_000, 0x64, arg2) != NULL) {
                    sp24 = 3;
                }
            } else {
                sp24 = 4;
            }
        }
    }

    if (sp24 == 0) {
        arg2->x = 0.0f;
        arg2->y = 0.0f;
        arg2->z = 0.0f;
    }
}

void GetPrimaryEntityNodePosition(Vec3f* arg0) {
    Model_GetNodePosition(gParticleEffectEntityA, 0x64, arg0);
}

void GetPrimaryEffectNodePosition(Vec3f* arg0) {
    Model_GetNodePosition(gParticleEffectData_42, 0x64, arg0);
}

void GetSecondaryEntityNodePosition(Vec3f* arg0) {
    Model_GetNodePosition(gParticleEffectEntityB, 0x64, arg0);
}

void GetPrimaryEffectCenterOrNode(Vec3f* arg0) {
    if (gParticleEffectPrimaryId == 0xFF) {
        GetEntityCenterPosition(gParticleEffectData_42, arg0);
    } else {
        Model_GetNodePosition(gParticleEffectData_42, gParticleTexture_Default, arg0);
    }
}

void GetSecondaryEntityNode9Position(Vec3f* arg0) {
    Model_GetNodePosition(gParticleEffectEntityB, 9, arg0);
}

void GetEntityDirectionVector(unk_BattlePlayerEntity* arg0, Vec3f* arg1) {
    GetEntityScaleDimensions(arg0, arg1);
}

f32 GetEntityCameraDistance(unk_BattlePlayerEntity* arg0) {
    f32 ret = gCamDistances[arg0->unk_000.unk_01A] * 0.01f;

    return ret;
}

f32 GetEntityScaleFactor(unk_BattlePlayerEntity* arg0) {
    return GetEntityCameraDistance(arg0);
}

void ComputeEntityScaleFactor(unk_BattlePlayerEntity* arg0) {
    GetEntityCameraDistance(arg0);
}

f32 GetPrimaryEntityScale(void) {
    return GetEntityScaleFactor(gParticleEffectData_42);
}

void ComputePrimaryEffectScale(void) {
    ComputeEntityScaleFactor(gParticleEffectData_42);
}

f32 GetSecondaryEntityScale(void) {
    return GetEntityScaleFactor(gParticleEffectEntityB);
}

void ComputeSecondaryEntityScale(void) {
    ComputeEntityScaleFactor(gParticleEffectEntityB);
}

CameraStruct* GetBattleCamera(void) {
    return gParticleScaleFactor.unk_0C;
}

ParticleEffectInstance* ParticleNode_CreateWhiteFlash(Vec3f arg0, u8 arg1) {
    ParticleEffectInstance* sp1C = Particle_AllocateInstance();

    if ((u32)sp1C != -1) {
        Vec3f_Copy(&sp1C->unk_68, &arg0);
        Particle_SetWhiteFlashHandler(sp1C, arg1);
        sp1C->unk_10 = gParticleEffectData_42;
        sp1C->unk_14 = NULL;
        sp1C->unk_CD = 0xFF;
        sp1C->unk_CC = 0x15;
        sp1C->unk_CA = 0;
    }
    return sp1C;
}

void ParticleNode_SetPosition(ParticleEffectInstance* arg0, Vec3f arg1) {
    if ((u32)arg0 != -1) {
        arg0->unk_68.x = arg1.x;
        arg0->unk_68.y = arg1.y;
        arg0->unk_68.z = arg1.z;
    }
}

void ParticleNode_ClearActiveFlag(ParticleEffectInstance* arg0) {
    Particle_ClearActiveFlag(arg0);
}

s16 ParticleNode_GetAngleToSecondary(ParticleEffectInstance* arg0) {
    Vec3f sp24;
    s16 ret;

    GetEntityCenterPosition(gParticleEffectEntityB, &sp24);
    ret = Vec3f_AngleYTo(arg0->unk_68, sp24) + arg0->unk_94.y;
    return ret;
}

void ParticleNode_SavePrimColor(ParticleEffectInstance* arg0) {
    gSavedPrimColorR = arg0->prim_r;
    gSavedPrimColorG = arg0->prim_g;
    gSavedPrimColorB = arg0->prim_b;
}

void ParticleNode_RestorePrimColor(ParticleEffectInstance* arg0) {
    arg0->prim_r = gSavedPrimColorR;
    arg0->prim_g = gSavedPrimColorG;
    arg0->prim_b = gSavedPrimColorB;
}
