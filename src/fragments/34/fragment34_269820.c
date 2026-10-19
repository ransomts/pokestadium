#include "fragment34.h"
#include "src/12D80.h"

ParticleEffectData gParticleDefaultCallback = { 3, Particle_NoopDraw };

void Particle_ResetDefaults(ParticleEffectInstance* arg0) {
    Particle_InitLifecycle(arg0);
    Particle_SetVelocityScaledXYZ(arg0, 0.0f, 0.0f, 0.0f);
    Particle_SetOrigin(arg0, 0.0f, 0.0f, 0.0f);
    Particle_SetVelocity(arg0, 0.0f, 0.0f, 0.0f);
    Particle_SetVelocityTarget(arg0, 0.0f, 0.0f, 0.0f);
    Particle_SetVelocityImpulse(arg0, 0.0f, 0.0f, 0.0f);
    Particle_Field74_SetScaled_0AD8C(arg0, 0.0f);
    Particle_Field78_SetScaled_0ADA4(arg0, 0.0f);
    Particle_SetRotation(arg0, 0, 0, 0);
    Particle_SetRotationSpeed(arg0, 0, 0, 0);
    Particle_SetTextureFrame(arg0, 0);
    Particle_FieldA6_SetS16_0BCA8(arg0, 0);
    Particle_FieldA8_SetS16_0BE14(arg0, 0);
    Particle_FieldCD_SetS16_0BF38(arg0, 0);
    Particle_FieldCE_SetS16_0BF24(arg0, 0);
    Particle_FieldAA_SetS16_0BF10(arg0, 0);
    Particle_FieldAC_SetS16_0BED8(arg0, 0);
    Particle_FieldCF_SetU8_0BEEC(arg0, 0);
    Particle_SetPrimColor(arg0, 0xFF, 0xFF, 0xFF);
    Particle_SetEnvColor(arg0, 0xFF, 0xFF, 0xFF);
    Particle_SetPrimAlpha(arg0, 0xFF);

    arg0->unk_1C = 1.0f;
    arg0->unk_28 = 1.0f;
}

ParticleEffectInstance* Particle_Alloc(void) {
    s32 i;
    s32 var_v0 = gParticlePoolIndex;
    ParticleEffectInstance* var_a0 = &gParticlePool[var_v0];

    for (i = 0; i < 0x12C; i++) {
        if (var_a0->unk_D0 == 0) {
            break;
        }

        var_v0++;
        if (var_v0 >= 0x12C) {
            var_v0 = 0;
            var_a0 = &gParticlePool[0];
        } else {
            var_a0++;
        }
    }

    if (i >= 0x12C) {
        var_a0 = (ParticleEffectInstance*)-1;
    } else {
        var_a0->unk_D0 = 1;

        Particle_ResetDefaults(var_a0);

        gParticlePoolIndex = var_v0 + 1;
        if (gParticlePoolIndex >= 0x12C) {
            gParticlePoolIndex = 0;
        }
    }

    return var_a0;
}

void Particle_Free(ParticleEffectInstance* arg0) {
    if (arg0->prev != NULL) {
        arg0->prev->next = arg0->next;
    }

    if (arg0->next != NULL) {
        arg0->next->prev = arg0->prev;
    }

    arg0->prev = NULL;
    arg0->next = NULL;

    arg0->unk_D0 = 0;
}

ParticleEffectInstance* Particle_New(void) {
    return Particle_Alloc();
}

ParticleEffectInstance* Particle_AllocChain(u8 arg0) {
    s32 i;
    ParticleEffectInstance* sp28;
    ParticleEffectInstance* temp_v0;
    ParticleEffectInstance* var_s0;

    sp28 = Particle_Alloc();

    if ((u32)sp28 != -1) {
        var_s0 = sp28;
        arg0--;

        for (i = 0; i < arg0; i++) {
            temp_v0 = Particle_Alloc();
            if ((u32)temp_v0 == -1) {
                break;
            }
            var_s0->next = temp_v0;
            temp_v0->prev = var_s0;
            var_s0 = temp_v0;
        }
    }

    return sp28;
}

ParticleEffectInstance* Particle_CreateAtTransform(f32 arg0, Vec3f arg1, Vec3s arg2, func_unk_D_8140E724_008 arg3, ParticleEffectData* arg4,
                              s16 arg5, s16 arg6, s16 arg7) {
    ParticleEffectInstance* sp1C = Particle_New();

    if ((u32)sp1C != -1) {
        sp1C->unk_28 = arg0;

        ParticleMath_CopyVec3f(&sp1C->unk_68, &arg1);
        ParticleMath_CopyVec3s(&sp1C->unk_94, &arg2);

        sp1C->unk_08 = arg3;
        sp1C->unk_0C = arg4;
        sp1C->unk_10 = 0;
        sp1C->unk_14 = 0;
        sp1C->unk_AC = arg5;
        sp1C->unk_CE = arg7;
        sp1C->targetAlpha = arg6;
    }
    return sp1C;
}

ParticleEffectInstance* Particle_CreateFromObjectTransform(Fragment2_1GraphNode* arg0, func_unk_D_8140E724_008 arg1, ParticleEffectData* arg2,
                              s16 arg3, s16 arg4, s16 arg5) {
    ParticleEffectInstance* sp1C = Particle_New();

    if ((u32)sp1C != -1) {
        if (arg4 == 0xFF) {
            sp1C->unk_38.x = arg0->unk_024.x;
            sp1C->unk_38.y = arg0->unk_024.y;
            sp1C->unk_38.z = arg0->unk_024.z;
        } else {
            GeoRender_FindAnchorPosition(arg0, arg4, &sp1C->unk_38);
        }

        sp1C->unk_94.x = arg0->unk_01E.x;
        sp1C->unk_94.y = arg0->unk_01E.y;
        sp1C->unk_94.z = arg0->unk_01E.z;

        sp1C->unk_08 = arg1;
        sp1C->unk_0C = arg2;

        sp1C->unk_10 = 0;
        sp1C->unk_14 = 0;

        sp1C->unk_AC = arg3;
        sp1C->unk_CE = arg5;
        sp1C->targetAlpha = arg4;
    }
    return sp1C;
}

void Particle_EmitBurstAtTransform(f32 arg0, Vec3f arg1, Vec3s arg2, func_unk_D_8140E724_008 arg3, ParticleEffectData* arg4, s16 arg5) {
    s32 i;

    for (i = 0; i < arg5; i++) {
        if ((u32)Particle_CreateAtTransform(arg0, arg1, arg2, arg3, arg4, i, 0xFF, NULL) == -1) {
            break;
        }
    }
}

void Particle_EmitBurstAtTransformWithMetadata(f32 arg0, Vec3f arg1, Vec3s arg2, func_unk_D_8140E724_008 arg3, ParticleEffectData* arg4, s16 arg5,
                   s16 arg6) {
    s32 i;

    for (i = 0; i < arg5; i++) {
        if ((u32)Particle_CreateAtTransform(arg0, arg1, arg2, arg3, arg4, i, 0xFF, arg6) == -1) {
            break;
        }
    }
}

void Particle_EmitBurstFromObject(Fragment2_1GraphNode* arg0, func_unk_D_8140E724_008 arg1, ParticleEffectData* arg2, s16 arg3,
                   s16 arg4) {
    s32 i;

    for (i = 0; i < arg3; i++) {
        if ((u32)Particle_CreateFromObjectTransform(arg0, arg1, arg2, i, arg4, 0) == -1) {
            break;
        }
    }
}

void Particle_EmitBurstFromObjectWithMetadata(Fragment2_1GraphNode* arg0, func_unk_D_8140E724_008 arg1, ParticleEffectData* arg2, s16 arg3,
                   s16 arg4, s16 arg5) {
    s32 i;

    for (i = 0; i < arg3; i++) {
        if ((u32)Particle_CreateFromObjectTransform(arg0, arg1, arg2, i, arg4, arg5) == -1) {
            break;
        }
    }
}

s32 Particle_CountActive(void) {
    s32 i;
    s32 var_v1 = 0;
    ParticleEffectInstance* ptr = gParticlePool;

    for (i = 0; i < 0x12C; i++, ptr++) {
        if (ptr->unk_D0 != 0) {
            var_v1++;
        }
    }

    return var_v1;
}

s32 Particle_CountActiveAlias(void) {
    return Particle_CountActive();
}

void Particle_InitLifecycle(ParticleEffectInstance* arg0) {
    arg0->updateState = 1;
    arg0->unk_0C = &gParticleDefaultCallback;
    arg0->unk_08 = NULL;
    arg0->unk_10 = 0;
    arg0->unk_14 = 0;
    arg0->unk_B8 = 0;
    Particle_SetFlags(arg0, 4);
}

void Particle_MarkInactive(ParticleEffectInstance* arg0) {
    arg0->updateState = 0;
}

void Particle_DisableAndDetach(ParticleEffectInstance* arg0) {
    arg0->updateState = 0;

    arg0->unk_08 = NULL;
    arg0->unk_0C = NULL;

    Particle_ResetPhase(arg0);
}

s32 Particle_IsInactive(ParticleEffectInstance* arg0) {
    s32 var_v1 = 0;

    if (arg0->updateState == 0) {
        var_v1 = 1;
    }
    return var_v1;
}

s32 Particle_IsRunning(ParticleEffectInstance* arg0) {
    s32 var_v1 = 0;

    if (arg0->updateState >= 2) {
        var_v1 = 1;
    }
    return var_v1;
}

void Particle_AdvanceLifecycle(ParticleEffectInstance* arg0) {
    Particle_ClearFlags(arg0, 1);
    arg0->updateState++;
}

s32 Particle_TickDelayTimer(ParticleEffectInstance* arg0, s16 arg1) {
    s32 sp1C = 0;

    if (Particle_LacksFlags(arg0, 0x80) != 0) {
        Particle_SetFlags(arg0, 0x80);
        arg0->unk_BC = arg1;
    }

    arg0->unk_BC--;
    if (arg0->unk_BC <= 0) {
        arg0->unk_BC = 0;
        Particle_ClearFlags(arg0, 0x80);
        sp1C = 1;
    }

    return sp1C;
}

s32 Particle_TickDelayAndAdvanceLifecycle(ParticleEffectInstance* arg0, s16 arg1) {
    s32 sp1C = Particle_TickDelayTimer(arg0, arg1);

    if (sp1C != 0) {
        Particle_AdvanceLifecycle(arg0);
    }
    return sp1C;
}

void Particle_SetFlags(ParticleEffectInstance* arg0, s32 arg1) {
    arg0->unk_18 |= arg1;
}

void Particle_ClearFlags(ParticleEffectInstance* arg0, s32 arg1) {
    arg0->unk_18 &= ~arg1;
}

void Particle_ToggleFlags(ParticleEffectInstance* arg0, s32 arg1) {
    arg0->unk_18 ^= arg1;
}

s32 Particle_HasFlags(ParticleEffectInstance* arg0, s32 arg1) {
    s32 var_v1 = 0;

    if (arg0->unk_18 & arg1) {
        var_v1 = 1;
    }
    return var_v1;
}

s32 Particle_LacksFlags(ParticleEffectInstance* arg0, s32 arg1) {
    s32 var_v1 = 0;

    if (!(arg0->unk_18 & arg1)) {
        var_v1 = 1;
    }
    return var_v1;
}

void Particle_EnableRendering(ParticleEffectInstance* arg0) {
    Particle_SetFlags(arg0, 4);
}

void Particle_DisableRendering(ParticleEffectInstance* arg0) {
    Particle_ClearFlags(arg0, 4);
}

s32 Particle_IsRenderingEnabled(ParticleEffectInstance* arg0) {
    return Particle_HasFlags(arg0, 4);
}

void Particle_EnableFlag40(ParticleEffectInstance* arg0) {
    Particle_SetFlags(arg0, 0x40);
}

void Particle_DisableFlag40(ParticleEffectInstance* arg0) {
    Particle_ClearFlags(arg0, 0x40);
}

void Particle_HasFlag40(ParticleEffectInstance* arg0) {
    Particle_HasFlags(arg0, 0x40);
}

void Particle_SetTextureFrame(ParticleEffectInstance* arg0, s16 arg1) {
    arg0->rampValue = arg1;
}

s32 Particle_AnimateFramesForward(ParticleEffectInstance* arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5) {
    s32 sp1C = 0;

    if (Particle_LacksFlags(arg0, 1) != 0) {
        arg0->rampStepTimer = arg4;
        arg0->rampValue = arg1;
        arg0->rampRepeatCount = arg5;
        Particle_SetFlags(arg0, 1);
    } else {
        arg0->rampStepTimer--;
        if (arg0->rampStepTimer <= 0) {
            arg0->rampStepTimer = arg4;

            arg0->rampValue += arg3;
            if (arg2 < arg0->rampValue) {
                if (arg0->rampRepeatCount > 0) {
                    arg0->rampRepeatCount--;
                }

                if (arg0->rampRepeatCount == 0) {
                    arg0->rampValue = arg2;
                    sp1C = 1;
                } else {
                    arg0->rampValue = arg1;
                }
            }
        }
    }
    return sp1C;
}

s32 Particle_AnimateFramesForwardAndAdvanceLifecycle(ParticleEffectInstance* arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5) {
    s32 sp24 = Particle_AnimateFramesForward(arg0, arg1, arg2, arg3, arg4, arg5);

    if (sp24 != 0) {
        Particle_AdvanceLifecycle(arg0);
    }

    return sp24;
}

s32 Particle_AnimateFramesReverse(ParticleEffectInstance* arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5) {
    s32 sp1C = 0;

    if (Particle_LacksFlags(arg0, 1) != 0) {
        arg0->rampStepTimer = arg4;
        arg0->rampValue = arg1;
        arg0->rampRepeatCount = arg5;
        Particle_SetFlags(arg0, 1);
    } else {
        arg0->rampStepTimer--;
        if (arg0->rampStepTimer <= 0) {
            arg0->rampStepTimer = arg4;

            arg0->rampValue -= arg3;
            if (arg0->rampValue < arg2) {
                if (arg0->rampRepeatCount > 0) {
                    arg0->rampRepeatCount--;
                }

                if (arg0->rampRepeatCount == 0) {
                    arg0->rampValue = arg2;
                    sp1C = 1;
                } else {
                    arg0->rampValue = arg1;
                }
            }
        }
    }

    return sp1C;
}

s32 Particle_AnimateFramesReverseAndAdvanceLifecycle(ParticleEffectInstance* arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5) {
    s32 sp24 = Particle_AnimateFramesReverse(arg0, arg1, arg2, arg3, arg4, arg5);

    if (sp24 != 0) {
        Particle_AdvanceLifecycle(arg0);
    }
    return sp24;
}

s32 Particle_AnimateFramesPingPong(ParticleEffectInstance* arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5) {
    s32 sp24 = 0;

    if (Particle_LacksFlags(arg0, 1) != 0) {
        arg0->rampStepTimer = arg4;
        arg0->rampValue = arg1;
        arg0->rampRepeatCount = arg5;
        Particle_SetFlags(arg0, 1);
        Particle_ClearFlags(arg0, 0x10);
    } else {
        arg0->rampStepTimer--;
        if (arg0->rampStepTimer <= 0) {
            arg0->rampStepTimer = arg4;

            if (Particle_LacksFlags(arg0, 0x10) != 0) {
                arg0->rampValue += arg3;
                if (arg0->rampValue >= arg2) {
                    arg0->rampValue = arg2;
                    Particle_SetFlags(arg0, 0x10);
                }
            } else {
                arg0->rampValue -= arg3;
                if (arg1 >= arg0->rampValue) {
                    arg0->rampValue = arg1;
                    if (arg0->rampRepeatCount > 0) {
                        arg0->rampRepeatCount--;
                    }

                    if (arg0->rampRepeatCount == 0) {
                        Particle_ClearFlags(arg0, 0x20);
                        Particle_ClearFlags(arg0, 1);
                        sp24 = 1;
                    } else {
                        Particle_ClearFlags(arg0, 0x10);
                        Particle_SetFlags(arg0, 0x20);
                    }
                }
            }
        }
    }

    return sp24;
}

s32 Particle_AnimateFramesPingPongAndAdvanceLifecycle(ParticleEffectInstance* arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5) {
    s32 sp24 = Particle_AnimateFramesPingPong(arg0, arg1, arg2, arg3, arg4, arg5);

    if (sp24 != 0) {
        Particle_AdvanceLifecycle(arg0);
    }
    return sp24;
}

s32 Particle_AnimateFramesReverseFirstPingPong(ParticleEffectInstance* arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5) {
    s32 sp24 = 0;

    if (Particle_LacksFlags(arg0, 1) != 0) {
        arg0->rampStepTimer = arg4;
        arg0->rampValue = arg1;
        arg0->rampRepeatCount = arg5;
        Particle_SetFlags(arg0, 1);
        Particle_ClearFlags(arg0, 0x10);
    } else {
        arg0->rampStepTimer--;
        if (arg0->rampStepTimer <= 0) {
            arg0->rampStepTimer = arg4;
            if (Particle_LacksFlags(arg0, 0x10) != 0) {
                arg0->rampValue -= arg3;
                if (arg2 >= arg0->rampValue) {
                    arg0->rampValue = arg2;
                    Particle_SetFlags(arg0, 0x10);
                }
            } else {
                arg0->rampValue += arg3;
                if (arg0->rampValue >= arg1) {
                    arg0->rampValue = arg1;
                    if (arg0->rampRepeatCount > 0) {
                        arg0->rampRepeatCount--;
                    }

                    if (arg0->rampRepeatCount == 0) {
                        Particle_ClearFlags(arg0, 1);
                        sp24 = 1;
                    } else {
                        Particle_ClearFlags(arg0, 0x10);
                    }
                }
            }
        }
    }
    return sp24;
}

s32 Particle_AnimateFramesReverseFirstPingPongAndAdvanceLifecycle(ParticleEffectInstance* arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5) {
    s32 sp24 = Particle_AnimateFramesReverseFirstPingPong(arg0, arg1, arg2, arg3, arg4, arg5);

    if (sp24 != 0) {
        Particle_AdvanceLifecycle(arg0);
    }
    return sp24;
}

void Particle_BeginPhase(ParticleEffectInstance* arg0) {
    arg0->unk_B8 = 1;
    Particle_ClearFlags(arg0, 2);
}

void Particle_ResetPhase(ParticleEffectInstance* arg0) {
    arg0->unk_B8 = 0;
    Particle_ClearFlags(arg0, 2);
}

void Particle_AdvancePhase(ParticleEffectInstance* arg0) {
    arg0->unk_B8++;
}

s32 Particle_TickPhaseTimer(ParticleEffectInstance* arg0, s16 arg1) {
    s32 sp1C = 0;

    if (Particle_LacksFlags(arg0, 2) != 0) {
        Particle_SetFlags(arg0, 2);
        arg0->durationTimer = arg1;
    }

    arg0->durationTimer--;
    if (arg0->durationTimer < 0) {
        Particle_ClearFlags(arg0, 2);
        sp1C = 1;
    }
    return sp1C;
}

void Particle_UpdateWorldTransform(ParticleEffectInstance* arg0) {
    arg0->unk_2C.x = arg0->unk_68.x + arg0->unk_38.x + arg0->unk_50.x;
    arg0->unk_2C.y = arg0->unk_68.y + arg0->unk_38.y + arg0->unk_50.y;
    arg0->unk_2C.z = arg0->unk_68.z + arg0->unk_38.z + arg0->unk_50.z;

    if (arg0->unk_14 != NULL) {
        arg0->unk_14->unk_024.x = arg0->unk_2C.x;
        arg0->unk_14->unk_024.y = arg0->unk_2C.y;
        arg0->unk_14->unk_024.z = arg0->unk_2C.z;

        arg0->unk_14->unk_030.x = arg0->unk_1C;
        arg0->unk_14->unk_030.y = arg0->unk_1C;
        arg0->unk_14->unk_030.z = arg0->unk_1C;

        if (Particle_LacksFlags(arg0, 0x200) != 0) {
            arg0->unk_14->unk_01E.x = arg0->unk_94.x;
            arg0->unk_14->unk_01E.y = arg0->unk_94.y;
            arg0->unk_14->unk_01E.z = arg0->unk_94.z;
        }
        arg0->unk_14->unk_01D = arg0->prim_a;
    }
}

void Particle_SetVelocityScaledXYZ(ParticleEffectInstance* arg0, f32 arg1, f32 arg2, f32 arg3) {
    arg0->unk_38.x = arg1 * gParticleRenderContext.unk_00.y;
    arg0->unk_38.y = arg2 * gParticleRenderContext.unk_00.y;
    arg0->unk_38.z = arg3 * gParticleRenderContext.unk_00.y;
}

void Particle_Field38_SetVecFromVec3fScaled_08C20(ParticleEffectInstance* arg0, Vec3f arg1) {
    arg0->unk_38.x = arg1.x * gParticleRenderContext.unk_00.y;
    arg0->unk_38.y = arg1.y * gParticleRenderContext.unk_00.y;
    arg0->unk_38.z = arg1.z * gParticleRenderContext.unk_00.y;
}

void Particle_Field38_SetVec_08C68(ParticleEffectInstance* arg0, f32 arg1, f32 arg2, f32 arg3) {
    arg0->unk_38.x = arg1;
    arg0->unk_38.y = arg2;
    arg0->unk_38.z = arg3;
}

void Particle_Field38_SetXScaled_08C88(ParticleEffectInstance* arg0, f32 arg1) {
    arg0->unk_38.x = arg1 * gParticleRenderContext.unk_00.y;
}

void Particle_Field38_SetYScaled_08CA0(ParticleEffectInstance* arg0, f32 arg1) {
    arg0->unk_38.y = arg1 * gParticleRenderContext.unk_00.y;
}

void Particle_Field38_SetZScaled_08CB8(ParticleEffectInstance* arg0, f32 arg1) {
    arg0->unk_38.z = arg1 * gParticleRenderContext.unk_00.y;
}

void Particle_SetPositionFromRotationTemplate1(ParticleEffectInstance* arg0, f32 arg1) {
    Vec3f sp1C;

    Particle_ComputeVectorFromRotationXYZAlt(arg0, arg1, &sp1C);
    Particle_Field38_SetVecFromVec3fScaled_08C20(arg0, sp1C);
}

void Particle_SetPositionFromRotationTemplate2(ParticleEffectInstance* arg0, f32 arg1) {
    Vec3f sp1C;

    Particle_ComputeVectorFromRotationYZVariant(arg0, arg1, &sp1C);
    Particle_Field38_SetVecFromVec3fScaled_08C20(arg0, sp1C);
}

void Particle_Field38_AddVecScaledFromVec3f_08D78(ParticleEffectInstance* arg0, Vec3f arg1) {
    arg0->unk_38.x += arg1.x * gParticleRenderContext.unk_00.y;
    arg0->unk_38.y += arg1.y * gParticleRenderContext.unk_00.y;
    arg0->unk_38.z += arg1.z * gParticleRenderContext.unk_00.y;
}

void Particle_Field38_AddVecFromVec3f_08DD8(ParticleEffectInstance* arg0, Vec3f arg1) {
    arg0->unk_38.x += arg1.x;
    arg0->unk_38.y += arg1.y;
    arg0->unk_38.z += arg1.z;
}

void Particle_Field38_AddVecScaled_08E18(ParticleEffectInstance* arg0, f32 arg1, f32 arg2, f32 arg3) {
    arg0->unk_38.x += arg1 * gParticleRenderContext.unk_00.y;
    arg0->unk_38.y += arg2 * gParticleRenderContext.unk_00.y;
    arg0->unk_38.z += arg3 * gParticleRenderContext.unk_00.y;
}

void Particle_Field38_AddXScaled_08E70(ParticleEffectInstance* arg0, f32 arg1) {
    arg0->unk_38.x += arg1 * gParticleRenderContext.unk_00.y;
}

void Particle_Field38_AddYScaled_08E90(ParticleEffectInstance* arg0, f32 arg1) {
    arg0->unk_38.y += arg1 * gParticleRenderContext.unk_00.y;
}

void Particle_Field38_AddZScaled_08EB0(ParticleEffectInstance* arg0, f32 arg1) {
    arg0->unk_38.z += arg1 * gParticleRenderContext.unk_00.y;
}

void Particle_Field38_AddXZFromField94Y_08ED0(ParticleEffectInstance* arg0, f32 arg1) {
    arg0->unk_38.x += arg1 * SINS(arg0->unk_94.y) * gParticleRenderContext.unk_00.y;
    arg0->unk_38.z += arg1 * COSS(arg0->unk_94.y) * gParticleRenderContext.unk_00.y;
}

void Particle_Field38_AddXZFromField94YOffset180_08F38(ParticleEffectInstance* arg0, f32 arg1) {
    arg0->unk_38.x += arg1 * SINS(arg0->unk_94.y + 0x8000) * gParticleRenderContext.unk_00.y;
    arg0->unk_38.z += arg1 * COSS(arg0->unk_94.y + 0x8000) * gParticleRenderContext.unk_00.y;
}

void Particle_Field38_AddXZFromField94YOffset90_08FAC(ParticleEffectInstance* arg0, f32 arg1) {
    arg0->unk_38.x += arg1 * SINS(arg0->unk_94.y + 0x4000) * gParticleRenderContext.unk_00.y;
    arg0->unk_38.z += arg1 * COSS(arg0->unk_94.y + 0x4000) * gParticleRenderContext.unk_00.y;
}

void Particle_Field38_AddXZFromField94YOffsetMinus90_0901C(ParticleEffectInstance* arg0, f32 arg1) {
    arg0->unk_38.x += arg1 * SINS(arg0->unk_94.y - 0x4000) * gParticleRenderContext.unk_00.y;
    arg0->unk_38.z += arg1 * COSS(arg0->unk_94.y - 0x4000) * gParticleRenderContext.unk_00.y;
}

void Particle_AddVelocityFromDirVector(ParticleEffectInstance* arg0, f32 arg1) {
    Vec3f sp1C;

    Particle_ComputeVectorFromRotationY(arg0, arg1, &sp1C);
    arg0->unk_38.x += sp1C.x * gParticleRenderContext.unk_00.y;
    arg0->unk_38.y += sp1C.y * gParticleRenderContext.unk_00.y;
    arg0->unk_38.z += sp1C.z * gParticleRenderContext.unk_00.y;
}

void Particle_AddPositionFromRotationTemplate1(ParticleEffectInstance* arg0, f32 arg1) {
    Vec3f sp1C;

    Particle_ComputeVectorFromRotationXYZAlt(arg0, arg1, &sp1C);
    Particle_Field38_AddVecScaledFromVec3f_08D78(arg0, sp1C);
}

void Particle_AddPositionFromRotationTemplate2(ParticleEffectInstance* arg0, f32 arg1) {
    Vec3f sp1C;

    Particle_ComputeVectorFromRotationYZVariant(arg0, arg1, &sp1C);
    Particle_Field38_AddVecScaledFromVec3f_08D78(arg0, sp1C);
}

void Particle_AddPositionRotatedVectorByYaw(ParticleEffectInstance* arg0, Vec3f arg1) {
    Vec3f sp24;

    ParticleMath_RotateVec3fY(&sp24, arg1, arg0->unk_94);
    Particle_Field38_AddVecScaledFromVec3f_08D78(arg0, sp24);
}

void Particle_SetRandomVelocityX(ParticleEffectInstance* arg0, s32 arg1) {
    arg0->unk_38.x = ParticleMath_RandomSigned(arg1) * gParticleRenderContext.unk_00.y;
}

void Particle_SetRandomVelocityY(ParticleEffectInstance* arg0, s32 arg1) {
    arg0->unk_38.y = ParticleMath_RandomSigned(arg1) * gParticleRenderContext.unk_00.y;
}

void Particle_SetRandomVelocityZ(ParticleEffectInstance* arg0, s32 arg1) {
    arg0->unk_38.z = ParticleMath_RandomSigned(arg1) * gParticleRenderContext.unk_00.y;
}

void Particle_SetRandomVelocityXOffset(ParticleEffectInstance* arg0, s32 arg1, s32 arg2) {
    arg0->unk_38.x = (ParticleMath_RandomSigned(arg1) * gParticleRenderContext.unk_00.y) + arg2;
}

void Particle_SetRandomVelocityYOffset(ParticleEffectInstance* arg0, s32 arg1, s32 arg2) {
    arg0->unk_38.y = (ParticleMath_RandomSigned(arg1) * gParticleRenderContext.unk_00.y) + arg2;
}

void Particle_SetRandomVelocityZOffset(ParticleEffectInstance* arg0, s32 arg1, s32 arg2) {
    arg0->unk_38.z = (ParticleMath_RandomSigned(arg1) * gParticleRenderContext.unk_00.y) + arg2;
}

void Particle_SetRandomVelocityXSymmetric(ParticleEffectInstance* arg0, s32 arg1, s32 arg2) {
    f32 temp_fv0 = ParticleMath_RandomSigned(arg1);

    if (temp_fv0 >= 0.0f) {
        arg0->unk_38.x = (temp_fv0 + arg2) * gParticleRenderContext.unk_00.y;
    } else {
        arg0->unk_38.x = (temp_fv0 - arg2) * gParticleRenderContext.unk_00.y;
    }
}

void Particle_SetRandomVelocityYSymmetric(ParticleEffectInstance* arg0, s32 arg1, s32 arg2) {
    f32 temp_fv0 = ParticleMath_RandomSigned(arg1);

    if (temp_fv0 >= 0.0f) {
        arg0->unk_38.y = (temp_fv0 + arg2) * gParticleRenderContext.unk_00.y;
    } else {
        arg0->unk_38.y = (temp_fv0 - arg2) * gParticleRenderContext.unk_00.y;
    }
}

void Particle_SetRandomVelocityZSymmetric(ParticleEffectInstance* arg0, s32 arg1, s32 arg2) {
    f32 temp_fv0 = ParticleMath_RandomSigned(arg1);

    if (temp_fv0 >= 0.0f) {
        arg0->unk_38.z = (temp_fv0 + arg2) * gParticleRenderContext.unk_00.y;
    } else {
        arg0->unk_38.z = (temp_fv0 - arg2) * gParticleRenderContext.unk_00.y;
    }
}

void Particle_SetRandomVelocityXYZ(ParticleEffectInstance* arg0, s32 arg1, s32 arg2, s32 arg3) {
    Vec3f sp18;

    sp18.x = ParticleMath_RandomSigned(arg1);
    sp18.y = ParticleMath_RandomSigned(arg2);
    sp18.z = ParticleMath_RandomSigned(arg3);

    arg0->unk_38.x = sp18.x * gParticleRenderContext.unk_00.y;
    arg0->unk_38.y = sp18.y * gParticleRenderContext.unk_00.y;
    arg0->unk_38.z = sp18.z * gParticleRenderContext.unk_00.y;
}

void Particle_SetRandomModVelocityXYZ(ParticleEffectInstance* arg0, s32 arg1, s32 arg2, s32 arg3) {
    Vec3f sp1C;

    sp1C.x = ParticleMath_RandomRange(arg1);
    sp1C.y = ParticleMath_RandomRange(arg2);
    sp1C.z = ParticleMath_RandomRange(arg3);

    arg0->unk_38.x = sp1C.x * gParticleRenderContext.unk_00.y;
    arg0->unk_38.y = sp1C.y * gParticleRenderContext.unk_00.y;
    arg0->unk_38.z = sp1C.z * gParticleRenderContext.unk_00.y;
}

void Particle_SetRandomRotatedVelocityXY(ParticleEffectInstance* arg0, s32 arg1, s32 arg2) {
    Vec3f sp2C;
    Vec3f sp20;

    sp2C.x = ParticleMath_RandomSigned(arg1);
    sp2C.y = ParticleMath_RandomSigned(arg2);
    sp2C.z = 0.0f;

    ParticleMath_RotateVec3fY(&sp20, sp2C, arg0->unk_94);

    arg0->unk_38.x = sp20.x * gParticleRenderContext.unk_00.y;
    arg0->unk_38.y = sp20.y * gParticleRenderContext.unk_00.y;
    arg0->unk_38.z = sp20.z * gParticleRenderContext.unk_00.y;
}

void Particle_AddRandomVelocityXYZ(ParticleEffectInstance* arg0, s32 arg1, s32 arg2, s32 arg3) {
    Vec3f sp24;

    sp24.x = ParticleMath_RandomSigned(arg1);
    sp24.y = ParticleMath_RandomSigned(arg2);
    sp24.z = ParticleMath_RandomSigned(arg3);

    arg0->unk_38.x += sp24.x * gParticleRenderContext.unk_00.y;
    arg0->unk_38.y += sp24.y * gParticleRenderContext.unk_00.y;
    arg0->unk_38.z += sp24.z * gParticleRenderContext.unk_00.y;
}

void Particle_SetOrigin(ParticleEffectInstance* arg0, f32 arg1, f32 arg2, f32 arg3) {
    arg0->unk_68.x = arg1;
    arg0->unk_68.y = arg2;
    arg0->unk_68.z = arg3;
}

void Particle_SetVelocity(ParticleEffectInstance* arg0, f32 arg1, f32 arg2, f32 arg3) {
    arg0->unk_50.x = arg1 * gParticleRenderContext.unk_00.y;
    arg0->unk_50.y = arg2 * gParticleRenderContext.unk_00.y;
    arg0->unk_50.z = arg3 * gParticleRenderContext.unk_00.y;
}

void Particle_Field50_SetXScaled_098E8(ParticleEffectInstance* arg0, f32 arg1) {
    arg0->unk_50.x = arg1 * gParticleRenderContext.unk_00.y;
}

void Particle_Field50_SetYScaled_09900(ParticleEffectInstance* arg0, f32 arg1) {
    arg0->unk_50.y = arg1 * gParticleRenderContext.unk_00.y;
}

void Particle_Field50_SetZScaled_09918(ParticleEffectInstance* arg0, f32 arg1) {
    arg0->unk_50.z = arg1 * gParticleRenderContext.unk_00.y;
}

void Particle_SetVelocityRandomDirection(ParticleEffectInstance* arg0, f32 arg1) {
    ParticleMath_RandomDirection(&arg0->unk_50, arg1 * gParticleRenderContext.unk_00.y);
}

void Particle_Field50_AddVecScaled_09968(ParticleEffectInstance* arg0, f32 arg1, f32 arg2, f32 arg3) {
    arg0->unk_50.x += arg1 * gParticleRenderContext.unk_00.y;
    arg0->unk_50.y += arg2 * gParticleRenderContext.unk_00.y;
    arg0->unk_50.z += arg3 * gParticleRenderContext.unk_00.y;
}

void Particle_Field50_AddXScaled_099C0(ParticleEffectInstance* arg0, f32 arg1) {
    arg0->unk_50.x += arg1 * gParticleRenderContext.unk_00.y;
}

void Particle_Field50_AddYScaled_099E0(ParticleEffectInstance* arg0, f32 arg1) {
    arg0->unk_50.y += arg1 * gParticleRenderContext.unk_00.y;
}

void Particle_Field50_AddZScaled_09A00(ParticleEffectInstance* arg0, f32 arg1) {
    arg0->unk_50.z += arg1 * gParticleRenderContext.unk_00.y;
}

void Particle_Field50_SubVecScaled_09A20(ParticleEffectInstance* arg0, f32 arg1, f32 arg2, f32 arg3) {
    arg0->unk_50.x -= arg1 * gParticleRenderContext.unk_00.y;
    arg0->unk_50.y -= arg2 * gParticleRenderContext.unk_00.y;
    arg0->unk_50.z -= arg3 * gParticleRenderContext.unk_00.y;
}

void Particle_Field50_SubXScaled_09A78(ParticleEffectInstance* arg0, f32 arg1) {
    arg0->unk_50.x -= arg1 * gParticleRenderContext.unk_00.y;
}

void Particle_Field50_SubYScaled_09A98(ParticleEffectInstance* arg0, f32 arg1) {
    arg0->unk_50.y -= arg1 * gParticleRenderContext.unk_00.y;
}

void Particle_Field50_SubZScaled_09AB8(ParticleEffectInstance* arg0, f32 arg1) {
    arg0->unk_50.z -= arg1 * gParticleRenderContext.unk_00.y;
}

s32 Particle_Field50_ApproachXToField5C_09AD8(ParticleEffectInstance* arg0, f32 arg1) {
    return ParticleMath_ApproachFloat(&arg0->unk_50.x, arg1 * gParticleRenderContext.unk_00.y, arg0->unk_5C.x);
}

s32 Particle_Field50_ApproachYToField5C_09B18(ParticleEffectInstance* arg0, f32 arg1) {
    return ParticleMath_ApproachFloat(&arg0->unk_50.y, arg1 * gParticleRenderContext.unk_00.y, arg0->unk_5C.y);
}

s32 Particle_Field50_ApproachZToField5C_09B58(ParticleEffectInstance* arg0, f32 arg1) {
    return ParticleMath_ApproachFloat(&arg0->unk_50.z, arg1 * gParticleRenderContext.unk_00.y, arg0->unk_5C.z);
}

void Particle_Field50_SetVecFromField7C_09B98(ParticleEffectInstance* arg0) {
    arg0->unk_50.x = arg0->unk_7C.x;
    arg0->unk_50.y = arg0->unk_7C.y;
    arg0->unk_50.z = arg0->unk_7C.z;
}

void Particle_Field50_SetXZFromField7C_09BB4(ParticleEffectInstance* arg0) {
    arg0->unk_50.x = arg0->unk_7C.x;
    arg0->unk_50.z = arg0->unk_7C.z;
}

void Particle_Field50_SetXYFromField7C_09BC8(ParticleEffectInstance* arg0) {
    arg0->unk_50.x = arg0->unk_7C.x;
    arg0->unk_50.y = arg0->unk_7C.y;
}

void Particle_Field50_AddVecFromField7C_09BDC(ParticleEffectInstance* arg0) {
    arg0->unk_50.x += arg0->unk_7C.x;
    arg0->unk_50.y += arg0->unk_7C.y;
    arg0->unk_50.z += arg0->unk_7C.z;
}

void Particle_Field50_AddXZFromField7C_09C10(ParticleEffectInstance* arg0) {
    arg0->unk_50.x += arg0->unk_7C.x;
    arg0->unk_50.z += arg0->unk_7C.z;
}

void Particle_Field50_AddXYFromField7C_09C34(ParticleEffectInstance* arg0) {
    arg0->unk_50.x += arg0->unk_7C.x;
    arg0->unk_50.y += arg0->unk_7C.y;
}

void Particle_Field50_AddXFromField7C_09C58(ParticleEffectInstance* arg0) {
    arg0->unk_50.x += arg0->unk_7C.x;
}

void Particle_Field50_AddYFromField7C_09C6C(ParticleEffectInstance* arg0) {
    arg0->unk_50.y += arg0->unk_7C.y;
}

void Particle_Field50_AddZFromField7C_09C80(ParticleEffectInstance* arg0) {
    arg0->unk_50.z += arg0->unk_7C.z;
}

void Particle_ApplyB278AndCopyXZ(ParticleEffectInstance* arg0) {
    Particle_Field7C_SetXZFromField74AngleY_0B278(arg0);
    Particle_Field50_SetXZFromField7C_09BB4(arg0);
}

void Particle_AddVelocityXZFromRotationYViaImpulse(ParticleEffectInstance* arg0) {
    Particle_Field7C_SetXZFromField74AngleY_0B278(arg0);
    Particle_Field50_AddXZFromField7C_09C10(arg0);
}

void Particle_AddVelocityXYFromRotationZViaImpulse(ParticleEffectInstance* arg0) {
    Particle_Field7C_SetXYFromField74AngleZ_0B23C(arg0);
    Particle_Field50_AddXYFromField7C_09C34(arg0);
}

void Particle_AddVelocityFromRotationTemplate1(ParticleEffectInstance* arg0) {
    Particle_Field7C_SetVecFromField74AnglesXY_0B2B4(arg0);
    Particle_Field50_AddVecFromField7C_09BDC(arg0);
}

void Particle_AddVelocityFromRotationTemplate2(ParticleEffectInstance* arg0) {
    Particle_Field7C_SetVecFromField74AnglesXZ_0B330(arg0);
    Particle_Field50_AddVecFromField7C_09BDC(arg0);
}

void Particle_AddVelocityFromRotationTemplate3(ParticleEffectInstance* arg0) {
    Particle_Field7C_SetVecFromField74AnglesXYAlt_0B3AC(arg0);
    Particle_Field50_AddVecFromField7C_09BDC(arg0);
}

void Particle_AddVelocityFromRotationTemplate4(ParticleEffectInstance* arg0) {
    Particle_Field7C_SetVecFromField74AnglesYZ_0B42C(arg0);
    Particle_Field50_AddVecFromField7C_09BDC(arg0);
}

void Particle_AddVelocityFromRotationTemplate5(ParticleEffectInstance* arg0) {
    Particle_Field7C_SetVecFromField74AnglesXYZAlt_0B568(arg0);
    Particle_Field50_AddVecFromField7C_09BDC(arg0);
}

void Particle_AddVelocityFromRotationTemplate6(ParticleEffectInstance* arg0) {
    Particle_Field7C_SetVecFromField74AnglesXYZ_0B4A0(arg0);
    Particle_Field50_AddVecFromField7C_09BDC(arg0);
}

void Particle_AddVelocityFromRotationTemplate7A(ParticleEffectInstance* arg0) {
    Particle_Field7C_SetVecFromField74AnglesYZAlt_0B638(arg0);
    Particle_Field50_AddVecFromField7C_09BDC(arg0);
}

void Particle_AddVelocityFromRotationTemplate7B(ParticleEffectInstance* arg0) {
    Particle_Field7C_SetVecFromField74AnglesYZAlt_0B638(arg0);
    Particle_Field50_AddVecFromField7C_09BDC(arg0);
}

void Particle_AddVelocityXZFromRotationY(ParticleEffectInstance* arg0) {
    arg0->unk_7C.x = arg0->unk_74 * SINS(arg0->unk_94.y);
    arg0->unk_7C.z = arg0->unk_74 * COSS(arg0->unk_94.y);

    Particle_Field50_AddXZFromField7C_09C10(arg0);
}

void Particle_AddVelocityXZFromRotationYPlusHalfTurn(ParticleEffectInstance* arg0) {
    arg0->unk_7C.x = arg0->unk_74 * SINS(arg0->unk_94.y + 0x8000);
    arg0->unk_7C.z = arg0->unk_74 * COSS(arg0->unk_94.y + 0x8000);

    Particle_Field50_AddXZFromField7C_09C10(arg0);
}

void Particle_AddVelocityXZFromRotationYPlusHalfTurnFromArgument(ParticleEffectInstance* arg0, f32 arg1) {
    arg0->unk_7C.x = SINS(arg0->unk_94.y + 0x8000) * arg1;
    arg0->unk_7C.z = COSS(arg0->unk_94.y + 0x8000) * arg1;

    Particle_Field50_AddXZFromField7C_09C10(arg0);
}

void Particle_AddVelocityYFromFieldOffset74(ParticleEffectInstance* arg0) {
    arg0->unk_7C.y = arg0->unk_74;

    Particle_Field50_AddYFromField7C_09C6C(arg0);
}

s32 Particle_Field50_AddNegField74Y_CheckField2CYNonPositive_09F84(ParticleEffectInstance* arg0) {
    s32 sp1C = 0;

    arg0->unk_7C.y = -arg0->unk_74;
    Particle_Field50_AddYFromField7C_09C6C(arg0);

    if (arg0->unk_2C.y <= 0.0f) {
        sp1C = 1;
    }
    return sp1C;
}

s32 Particle_Field74_AdvanceAndAddNegY_CheckField2CYNonPositive_09FD8(ParticleEffectInstance* arg0) {
    s32 sp1C = 0;

    arg0->unk_74 += arg0->unk_78;
    arg0->unk_7C.y = -arg0->unk_74;

    Particle_Field50_AddYFromField7C_09C6C(arg0);

    if (arg0->unk_2C.y <= 0.0f) {
        sp1C = 1;
    }
    return sp1C;
}

void Particle_SetVelocityTarget(ParticleEffectInstance* arg0, f32 arg1, f32 arg2, f32 arg3) {
    arg0->unk_5C.x = arg1 * gParticleRenderContext.unk_00.y;
    arg0->unk_5C.y = arg2 * gParticleRenderContext.unk_00.y;
    arg0->unk_5C.z = arg3 * gParticleRenderContext.unk_00.y;
}

void Particle_Field5C_SetXScaled_0A07C(ParticleEffectInstance* arg0, f32 arg1) {
    arg0->unk_5C.x = arg1 * gParticleRenderContext.unk_00.y;
}

void Particle_Field5C_SetYScaled_0A094(ParticleEffectInstance* arg0, f32 arg1) {
    arg0->unk_5C.y = arg1 * gParticleRenderContext.unk_00.y;
}

void Particle_Field5C_SetZScaled_0A0AC(ParticleEffectInstance* arg0, f32 arg1) {
    arg0->unk_5C.z = arg1 * gParticleRenderContext.unk_00.y;
}

s32 Particle_Field5C_ApproachY_0A0C4(ParticleEffectInstance* arg0, f32 arg1, f32 arg2) {
    return ParticleMath_ApproachFloat(&arg0->unk_5C.y, arg1 * gParticleRenderContext.unk_00.y, arg2 * gParticleRenderContext.unk_00.y);
}

f32 ParticleMath_ScaleApproachStep(f32 arg0) {
    return arg0 * 0.4f;
}

void Particle_ApproachPosition(ParticleEffectInstance* arg0, Vec3f arg1) {
    f32 sp24;
    f32 sp20;
    f32 temp_fa0;

    temp_fa0 = arg1.x - arg0->unk_38.x;
    sp20 = arg1.y - arg0->unk_38.y;
    sp24 = arg1.z - arg0->unk_38.z;

    if (!(temp_fa0 <= 0.01f) || !(temp_fa0 >= -0.01f)) {
        ParticleMath_ApproachFloat(&arg0->unk_38.x, arg1.x, ParticleMath_ScaleApproachStep(temp_fa0));
    }

    if (!(sp20 <= 0.01f) || !(sp20 >= -0.01f)) {
        ParticleMath_ApproachFloat(&arg0->unk_38.y, arg1.y, ParticleMath_ScaleApproachStep(sp20));
    }

    if (!(sp24 <= 0.01f) || !(sp24 >= -0.01f)) {
        ParticleMath_ApproachFloat(&arg0->unk_38.z, arg1.z, ParticleMath_ScaleApproachStep(sp24));
    }
}

void Particle_Field94_SetVecFromVec3s_0A24C(ParticleEffectInstance* arg0, Vec3s arg1) {
    arg0->unk_94.x = arg1.x;
    arg0->unk_94.y = arg1.y;
    arg0->unk_94.z = arg1.z;
}

void Particle_SetRotation(ParticleEffectInstance* arg0, s16 arg1, s16 arg2, s16 arg3) {
    arg0->unk_94.x = arg1;
    arg0->unk_94.y = arg2;
    arg0->unk_94.z = arg3;
}

void Particle_Field94_SetX_0A2A4(ParticleEffectInstance* arg0, s16 arg1) {
    arg0->unk_94.x = arg1;
}

void Particle_Field94_SetY_0A2B8(ParticleEffectInstance* arg0, s16 arg1) {
    arg0->unk_94.y = arg1;
}

void Particle_Field94_SetZ_0A2CC(ParticleEffectInstance* arg0, s16 arg1) {
    arg0->unk_94.z = arg1;
}

void Particle_Field94_AddConstantAll_0A2E0(ParticleEffectInstance* arg0) {
    arg0->unk_94.x += 0x8000;
    arg0->unk_94.y += 0x8000;
    arg0->unk_94.z += 0x8000;
}

void Particle_Field94_AddXConstant_0A30C(ParticleEffectInstance* arg0) {
    arg0->unk_94.x += 0x8000;
}

void Particle_Field94_AddYConstant_0A320(ParticleEffectInstance* arg0) {
    arg0->unk_94.y += 0x8000;
}

void Particle_Field94_AddZConstant_0A334(ParticleEffectInstance* arg0) {
    arg0->unk_94.z += 0x8000;
}

void Particle_SetRotationSpeed(ParticleEffectInstance* arg0, s16 arg1, s16 arg2, s16 arg3) {
    arg0->rotationDelta.x = arg1;
    arg0->rotationDelta.y = arg2;
    arg0->rotationDelta.z = arg3;
}

void Particle_Field9A_SetVecFromVec3s_0A37C(ParticleEffectInstance* arg0, Vec3s arg1) {
    arg0->rotationDelta.x = arg1.x;
    arg0->rotationDelta.y = arg1.y;
    arg0->rotationDelta.z = arg1.z;
}

void Particle_Field9A_SetXY_0A3A0(ParticleEffectInstance* arg0, s16 arg1, s16 arg2) {
    arg0->rotationDelta.x = arg1;
    arg0->rotationDelta.y = arg2;
}

void Particle_Field9A_SetX_0A3C4(ParticleEffectInstance* arg0, s16 arg1) {
    arg0->rotationDelta.x = arg1;
}

void Particle_Field9A_SetY_0A3D8(ParticleEffectInstance* arg0, s16 arg1) {
    arg0->rotationDelta.y = arg1;
}

void Particle_Field9A_SetZ_0A3EC(ParticleEffectInstance* arg0, s16 arg1) {
    arg0->rotationDelta.z = arg1;
}

void Particle_FieldA0_SetX_0A400(ParticleEffectInstance* arg0, s16 arg1) {
    arg0->unk_A0.x = arg1;
}

void Particle_FieldA0_SetY_0A414(ParticleEffectInstance* arg0, s16 arg1) {
    arg0->unk_A0.y = arg1;
}

void Particle_SetRotationTargetXY(ParticleEffectInstance* arg0, s16 arg1, s16 arg2) {
    Particle_FieldA0_SetX_0A400(arg0, arg1);
    Particle_FieldA0_SetY_0A414(arg0, arg2);
}

void Particle_SetRotationTargetFromCurrent(ParticleEffectInstance* arg0) {
    arg0->unk_A0.x = arg0->unk_94.x;
    arg0->unk_A0.y = arg0->unk_94.y;
    arg0->unk_A0.z = arg0->unk_94.z;
}

void Particle_Field94_AddVecFromField9A_0A480(ParticleEffectInstance* arg0) {
    arg0->unk_94.x += arg0->rotationDelta.x;
    arg0->unk_94.y += arg0->rotationDelta.y;
    arg0->unk_94.z += arg0->rotationDelta.z;
}

void Particle_Field94_AddXFromField9A_0A4B4(ParticleEffectInstance* arg0) {
    arg0->unk_94.x += arg0->rotationDelta.x;
}

void Particle_Field94_AddYFromField9A_0A4C8(ParticleEffectInstance* arg0) {
    arg0->unk_94.y += arg0->rotationDelta.y;
}

void Particle_Field94_AddZFromField9A_0A4DC(ParticleEffectInstance* arg0) {
    arg0->unk_94.z += arg0->rotationDelta.z;
}

void Particle_Field94_AddVecFromVec3s_0A4F0(ParticleEffectInstance* arg0, Vec3s arg1) {
    arg0->unk_94.x += arg1.x;
    arg0->unk_94.y += arg1.y;
    arg0->unk_94.z += arg1.z;
}

void Particle_Field94_AddVec_0A52C(ParticleEffectInstance* arg0, s16 arg1, s16 arg2, s16 arg3) {
    arg0->unk_94.x += arg1;
    arg0->unk_94.y += arg2;
    arg0->unk_94.z += arg3;
}

void Particle_Field94_AddX_0A578(ParticleEffectInstance* arg0, s16 arg1) {
    arg0->unk_94.x += arg1;
}

void Particle_Field94_AddY_0A594(ParticleEffectInstance* arg0, s16 arg1) {
    arg0->unk_94.y += arg1;
}

void Particle_Field94_AddZ_0A5B0(ParticleEffectInstance* arg0, s16 arg1) {
    arg0->unk_94.z += arg1;
}

void Particle_AddRotationTargetXY(ParticleEffectInstance* arg0, s16 arg1, s16 arg2) {
    arg0->unk_A0.x += arg1;
    arg0->unk_A0.y += arg2;
}

void Particle_Field94_SubVecFromVec3s_0A600(ParticleEffectInstance* arg0, Vec3s arg1) {
    arg0->unk_94.x -= arg1.x;
    arg0->unk_94.y -= arg1.y;
    arg0->unk_94.z -= arg1.z;
}

void Particle_Field94_SubX_0A63C(ParticleEffectInstance* arg0, s16 arg1) {
    arg0->unk_94.x -= arg1;
}

void Particle_Field94_SubY_0A658(ParticleEffectInstance* arg0, s16 arg1) {
    arg0->unk_94.y -= arg1;
}

void Particle_Field94_SubZ_0A674(ParticleEffectInstance* arg0, s16 arg1) {
    arg0->unk_94.z -= arg1;
}

void Particle_ApproachRotationTargetX(ParticleEffectInstance* arg0) {
    ParticleMath_ApproachAngle(&arg0->unk_94.x, arg0->unk_A0.x, arg0->rotationDelta.x);
}

void Particle_ApproachRotationTargetY(ParticleEffectInstance* arg0) {
    ParticleMath_ApproachAngle(&arg0->unk_94.y, arg0->unk_A0.y, arg0->rotationDelta.y);
}

void Particle_ApproachRotationTargetZ(ParticleEffectInstance* arg0) {
    ParticleMath_ApproachAngle(&arg0->unk_94.z, arg0->unk_A0.z, arg0->rotationDelta.z);
}

void Particle_ApproachRotationTargetXY(ParticleEffectInstance* arg0) {
    Particle_ApproachRotationTargetX(arg0);
    Particle_ApproachRotationTargetY(arg0);
}

void Particle_ApproachRotationTargetXYZ(ParticleEffectInstance* arg0) {
    Particle_ApproachRotationTargetX(arg0);
    Particle_ApproachRotationTargetY(arg0);
    Particle_ApproachRotationTargetZ(arg0);
}

void Particle_ApproachRotationXTo(ParticleEffectInstance* arg0, s16 arg1, s16 arg2) {
    ParticleMath_ApproachAngle(&arg0->unk_94.x, arg1, arg2);
}

void Particle_ApproachRotationYTo(ParticleEffectInstance* arg0, s16 arg1, s16 arg2) {
    ParticleMath_ApproachAngle(&arg0->unk_94.y, arg1, arg2);
}

s32 Particle_Field94_DecrementXTo_0A7DC(ParticleEffectInstance* arg0, s32 arg1, s32 arg2) {
    s32 var_v1 = 0;
    s32 var_v0 = arg0->unk_94.x;

    if (arg1 < var_v0) {
        var_v0 -= arg2;
        if (arg1 >= var_v0) {
            var_v0 = arg1;
            var_v1 = 1;
        }
        arg0->unk_94.x = var_v0;
    }

    return var_v1;
}

s32 Particle_Field94_DecrementYTo_0A810(ParticleEffectInstance* arg0, s32 arg1, s32 arg2) {
    s32 var_v1 = 0;
    s32 var_v0 = arg0->unk_94.y;

    if (arg1 < var_v0) {
        var_v0 -= arg2;
        if (arg1 >= var_v0) {
            var_v0 = arg1;
            var_v1 = 1;
        }
        arg0->unk_94.y = var_v0;
    }

    return var_v1;
}

s32 Particle_Field94_DecrementZTo_0A844(ParticleEffectInstance* arg0, s32 arg1, s32 arg2) {
    s32 var_v0 = arg0->unk_94.z;
    s32 var_v1 = 0;

    if (arg1 < var_v0) {
        var_v0 -= arg2;
        if (arg1 >= var_v0) {
            var_v0 = arg1;
            var_v1 = 1;
        }
        arg0->unk_94.z = var_v0;
    }
    return var_v1;
}

void Particle_AddRotationRandomSignedXY(ParticleEffectInstance* arg0, s32 arg1, s32 arg2) {
    Particle_Field94_AddX_0A578(arg0, ParticleMath_RandomSigned(arg1));
    Particle_Field94_AddY_0A594(arg0, ParticleMath_RandomSigned(arg2));
}

void Particle_AddRotationRandomSignedXYWithXHalfTurn(ParticleEffectInstance* arg0, s32 arg1, s32 arg2) {
    Particle_Field94_AddX_0A578(arg0, ParticleMath_RandomSignedOffset(arg1, 0x8000));
    Particle_Field94_AddY_0A594(arg0, ParticleMath_RandomSigned(arg2));
}

void Particle_AddRotationRandomSignedY(ParticleEffectInstance* arg0, s32 arg1) {
    Particle_Field94_AddY_0A594(arg0, ParticleMath_RandomSigned(arg1));
}

void Particle_AddRotationRandomSignedYWithHalfTurn(ParticleEffectInstance* arg0, s32 arg1) {
    Particle_Field94_AddY_0A594(arg0, ParticleMath_RandomSignedOffset(arg1, 0x8000));
}

void Particle_AddRotationRandomSignedXWithFixedYQuarterTurn(ParticleEffectInstance* arg0) {
    Particle_Field94_AddX_0A578(arg0, ParticleMath_RandomSigned(0x10000));
    Particle_Field94_AddY_0A594(arg0, 0x4000);
}

void Particle_ComputeVectorFromRotationY(ParticleEffectInstance* arg0, f32 arg1, Vec3f* arg2) {
    arg2->x = SINS(arg0->unk_94.y) * arg1;
    arg2->y = 0.0f;
    arg2->z = COSS(arg0->unk_94.y) * arg1;
}

void Particle_ComputeVectorFromRotationXY(ParticleEffectInstance* arg0, f32 arg1, Vec3f* arg2) {
    arg2->x = arg1 * COSS(arg0->unk_94.x) * SINS(arg0->unk_94.y);
    arg2->y = -arg1 * SINS(arg0->unk_94.x);
    arg2->z = arg1 * COSS(arg0->unk_94.x) * COSS(arg0->unk_94.y);
}

void Particle_ComputeVectorFromRotationXZ(ParticleEffectInstance* arg0, f32 arg1, Vec3f* arg2) {
    arg2->x = arg1 * SINS(arg0->unk_94.x) * SINS(arg0->unk_94.z);
    arg2->y = -arg1 * SINS(arg0->unk_94.x) * COSS(arg0->unk_94.z);
    arg2->z = arg1 * COSS(arg0->unk_94.x);
}

void Particle_ComputeVectorFromRotationXYZAlt(ParticleEffectInstance* arg0, f32 arg1, Vec3f* arg2) {
    arg2->x = arg1 * (SINS(arg0->unk_94.x) * COSS(arg0->unk_94.y) * SINS(arg0->unk_94.z) +
                      COSS(arg0->unk_94.x) * SINS(arg0->unk_94.y));
    arg2->y = -arg1 * SINS(arg0->unk_94.x) * COSS(arg0->unk_94.z);
    arg2->z = arg1 * (COSS(arg0->unk_94.x) * COSS(arg0->unk_94.y) -
                      SINS(arg0->unk_94.x) * SINS(arg0->unk_94.y) * SINS(arg0->unk_94.z));
}

void Particle_ComputeVectorFromRotationYZVariant(ParticleEffectInstance* arg0, f32 arg1, Vec3f* arg2) {
    arg2->x = arg1 * (SINS(arg0->unk_94.y) * COSS(arg0->unk_94.z) +
                      SINS(arg0->unk_94.x) * COSS(arg0->unk_94.y) * SINS(arg0->unk_94.z));
    arg2->y = arg1 * (SINS(arg0->unk_94.y) * SINS(arg0->unk_94.z) -
                      SINS(arg0->unk_94.x) * COSS(arg0->unk_94.y) * COSS(arg0->unk_94.z));
    arg2->z = arg1 * (COSS(arg0->unk_94.x) * COSS(arg0->unk_94.y));
}

void Particle_Field74_SetScaled_0AD8C(ParticleEffectInstance* arg0, f32 arg1) {
    arg0->unk_74 = arg1 * gParticleRenderContext.unk_00.y;
}

void Particle_Field78_SetScaled_0ADA4(ParticleEffectInstance* arg0, f32 arg1) {
    arg0->unk_78 = arg1 * gParticleRenderContext.unk_00.y;
}

s32 Particle_Field74_Approach_0ADBC(ParticleEffectInstance* arg0, f32 arg1, f32 arg2) {
    return ParticleMath_ApproachFloat(&arg0->unk_74, arg1 * gParticleRenderContext.unk_00.y, arg2 * gParticleRenderContext.unk_00.y);
}

s32 Particle_Field74_ApproachUsingField78_0AE00(ParticleEffectInstance* arg0, f32 arg1) {
    return ParticleMath_ApproachFloat(&arg0->unk_74, arg1 * gParticleRenderContext.unk_00.y, arg0->unk_78);
}

s32 Particle_Field78_Approach_0AE40(ParticleEffectInstance* arg0, f32 arg1, f32 arg2) {
    return ParticleMath_ApproachFloat(&arg0->unk_78, arg1 * gParticleRenderContext.unk_00.y, arg2 * gParticleRenderContext.unk_00.y);
}

void Particle_Field7C_SetVecScaled_0AE84(ParticleEffectInstance* arg0, Vec3f arg1) {
    arg0->unk_7C.x = arg1.x * gParticleRenderContext.unk_00.y;
    arg0->unk_7C.y = arg1.y * gParticleRenderContext.unk_00.y;
    arg0->unk_7C.z = arg1.z * gParticleRenderContext.unk_00.y;
}

void Particle_SetVelocityImpulse(ParticleEffectInstance* arg0, f32 arg1, f32 arg2, f32 arg3) {
    arg0->unk_7C.x = arg1 * gParticleRenderContext.unk_00.y;
    arg0->unk_7C.y = arg2 * gParticleRenderContext.unk_00.y;
    arg0->unk_7C.z = arg3 * gParticleRenderContext.unk_00.y;
}

void Particle_Field7C_SetXScaled_0AF0C(ParticleEffectInstance* arg0, f32 arg1) {
    arg0->unk_7C.x = arg1 * gParticleRenderContext.unk_00.y;
}

void Particle_Field7C_SetYScaled_0AF24(ParticleEffectInstance* arg0, f32 arg1) {
    arg0->unk_7C.y = arg1 * gParticleRenderContext.unk_00.y;
}

void Particle_Field7C_SetZScaled_0AF3C(ParticleEffectInstance* arg0, f32 arg1) {
    arg0->unk_7C.z = arg1 * gParticleRenderContext.unk_00.y;
}

s32 Particle_Field7C_IncrementXUntilAtLeast_0AF54(ParticleEffectInstance* arg0, f32 arg1, f32 arg2) {
    f32 temp_fv0;
    s32 var_v1 = 0;

    arg0->unk_7C.x += arg2 * gParticleRenderContext.unk_00.y;

    temp_fv0 = arg1 * gParticleRenderContext.unk_00.y;
    if (temp_fv0 <= arg0->unk_7C.x) {
        arg0->unk_7C.x = temp_fv0;
        var_v1 = 1;
    }
    return var_v1;
}

s32 Particle_Field7C_IncrementYUntilAtLeast_0AFA8(ParticleEffectInstance* arg0, f32 arg1, f32 arg2) {
    f32 temp_fv0;
    s32 var_v1 = 0;

    arg0->unk_7C.y += arg2 * gParticleRenderContext.unk_00.y;

    temp_fv0 = arg1 * gParticleRenderContext.unk_00.y;
    if (temp_fv0 <= arg0->unk_7C.y) {
        arg0->unk_7C.y = temp_fv0;
        var_v1 = 1;
    }
    return var_v1;
}

s32 Particle_Field7C_IncrementZUntilAtLeast_0AFFC(ParticleEffectInstance* arg0, f32 arg1, f32 arg2) {
    f32 temp_fv0;
    s32 var_v1 = 0;

    arg0->unk_7C.z += arg2 * gParticleRenderContext.unk_00.y;

    temp_fv0 = arg1 * gParticleRenderContext.unk_00.y;
    if (temp_fv0 <= arg0->unk_7C.z) {
        arg0->unk_7C.z = temp_fv0;
        var_v1 = 1;
    }
    return var_v1;
}

s32 Particle_Field7C_DecrementXUntilAtMost_0B050(ParticleEffectInstance* arg0, f32 arg1, f32 arg2) {
    f32 temp_fv0;
    s32 var_v1 = 0;

    arg0->unk_7C.x -= arg2 * gParticleRenderContext.unk_00.y;

    temp_fv0 = arg1 * gParticleRenderContext.unk_00.y;
    if (arg0->unk_7C.x <= temp_fv0) {
        arg0->unk_7C.x = temp_fv0;
        var_v1 = 1;
    }
    return var_v1;
}

s32 Particle_Field7C_DecrementYUntilAtMost_0B0A4(ParticleEffectInstance* arg0, f32 arg1, f32 arg2) {
    s32 var_v1 = 0;
    f32 temp_fv0;

    arg0->unk_7C.y -= arg2 * gParticleRenderContext.unk_00.y;

    temp_fv0 = arg1 * gParticleRenderContext.unk_00.y;
    if (arg0->unk_7C.y <= temp_fv0) {
        arg0->unk_7C.y = temp_fv0;
        var_v1 = 1;
    }
    return var_v1;
}

s32 Particle_Field7C_DecrementZUntilAtMost_0B0F8(ParticleEffectInstance* arg0, f32 arg1, f32 arg2) {
    f32 temp_fv0;
    s32 var_v1 = 0;

    arg0->unk_7C.z -= arg2 * gParticleRenderContext.unk_00.y;

    temp_fv0 = arg1 * gParticleRenderContext.unk_00.y;
    if (arg0->unk_7C.z <= temp_fv0) {
        arg0->unk_7C.z = temp_fv0;
        var_v1 = 1;
    }
    return var_v1;
}

void Particle_Field7C_ScaleVec_0B14C(ParticleEffectInstance* arg0, f32 arg1) {
    arg0->unk_7C.x *= arg1;
    arg0->unk_7C.y *= arg1;
    arg0->unk_7C.z *= arg1;
}

s32 Particle_Field7C_ApproachY_0B180(ParticleEffectInstance* arg0, f32 arg1, f32 arg2) {
    return ParticleMath_ApproachFloat(&arg0->unk_7C.y, arg1 * gParticleRenderContext.unk_00.y, arg2 * gParticleRenderContext.unk_00.y);
}

void Particle_Field7C_SetYFromField74AngleX_0B1C4(ParticleEffectInstance* arg0) {
    arg0->unk_7C.y = COSS(arg0->unk_94.x) * arg0->unk_74;
}

void Particle_Field7C_SetXFromField74AngleY_0B1EC(ParticleEffectInstance* arg0) {
    arg0->unk_7C.x = SINS(arg0->unk_94.y) * arg0->unk_74;
}

void Particle_Field7C_SetZFromField74AngleY_0B214(ParticleEffectInstance* arg0) {
    arg0->unk_7C.z = COSS(arg0->unk_94.y) * arg0->unk_74;
}

void Particle_Field7C_SetXYFromField74AngleZ_0B23C(ParticleEffectInstance* arg0) {
    arg0->unk_7C.x = COSS(arg0->unk_94.z) * arg0->unk_74;
    arg0->unk_7C.y = SINS(arg0->unk_94.z) * arg0->unk_74;
}

void Particle_Field7C_SetXZFromField74AngleY_0B278(ParticleEffectInstance* arg0) {
    arg0->unk_7C.x = SINS(arg0->unk_94.y) * arg0->unk_74;
    arg0->unk_7C.z = COSS(arg0->unk_94.y) * arg0->unk_74;
}

void Particle_Field7C_SetVecFromField74AnglesXY_0B2B4(ParticleEffectInstance* arg0) {
    arg0->unk_7C.x = arg0->unk_74 * COSS(arg0->unk_94.x) * SINS(arg0->unk_94.y);
    arg0->unk_7C.y = -arg0->unk_74 * SINS(arg0->unk_94.x);
    arg0->unk_7C.z = arg0->unk_74 * COSS(arg0->unk_94.x) * COSS(arg0->unk_94.y);
}

void Particle_Field7C_SetVecFromField74AnglesXZ_0B330(ParticleEffectInstance* arg0) {
    arg0->unk_7C.x = arg0->unk_74 * SINS(arg0->unk_94.x) * SINS(arg0->unk_94.z);
    arg0->unk_7C.y = -arg0->unk_74 * SINS(arg0->unk_94.x) * COSS(arg0->unk_94.z);
    arg0->unk_7C.z = arg0->unk_74 * COSS(arg0->unk_94.x);
}

void Particle_Field7C_SetVecFromField74AnglesXYAlt_0B3AC(ParticleEffectInstance* arg0) {
    arg0->unk_7C.x = arg0->unk_74 * SINS(arg0->unk_94.y);
    arg0->unk_7C.y = -arg0->unk_74 * SINS(arg0->unk_94.x) * COSS(arg0->unk_94.y);
    arg0->unk_7C.z = arg0->unk_74 * COSS(arg0->unk_94.x) * COSS(arg0->unk_94.y);
}

void Particle_Field7C_SetVecFromField74AnglesYZ_0B42C(ParticleEffectInstance* arg0) {
    arg0->unk_7C.x = arg0->unk_74 * SINS(arg0->unk_94.y) * COSS(arg0->unk_94.z);
    arg0->unk_7C.y = arg0->unk_74 * SINS(arg0->unk_94.y) * SINS(arg0->unk_94.z);
    arg0->unk_7C.z = COSS(arg0->unk_94.y);
}

void Particle_Field7C_SetVecFromField74AnglesXYZ_0B4A0(ParticleEffectInstance* arg0) {
    arg0->unk_7C.x = arg0->unk_74 * (COSS(arg0->unk_94.x) * SINS(arg0->unk_94.y) * COSS(arg0->unk_94.z) +
                                     SINS(arg0->unk_94.x) * SINS(arg0->unk_94.z));
    arg0->unk_7C.y = -arg0->unk_74 * (COSS(arg0->unk_94.x) * SINS(arg0->unk_94.y) * SINS(arg0->unk_94.z) -
                                      SINS(arg0->unk_94.x) * COSS(arg0->unk_94.z));
    arg0->unk_7C.z = arg0->unk_74 * (COSS(arg0->unk_94.x) * COSS(arg0->unk_94.y));
}

void Particle_Field7C_SetVecFromField74AnglesXYZAlt_0B568(ParticleEffectInstance* arg0) {
    arg0->unk_7C.x = arg0->unk_74 * (SINS(arg0->unk_94.x) * COSS(arg0->unk_94.y) * SINS(arg0->unk_94.z) +
                                     COSS(arg0->unk_94.x) * SINS(arg0->unk_94.y));
    arg0->unk_7C.y = -arg0->unk_74 * SINS(arg0->unk_94.x) * COSS(arg0->unk_94.z);

    arg0->unk_7C.z = arg0->unk_74 * (-SINS(arg0->unk_94.x) * SINS(arg0->unk_94.y) * SINS(arg0->unk_94.z) +
                                     COSS(arg0->unk_94.x) * COSS(arg0->unk_94.y));
}

void Particle_Field7C_SetVecFromField74AnglesYZAlt_0B638(ParticleEffectInstance* arg0) {
    arg0->unk_7C.x = arg0->unk_74 * SINS(arg0->unk_94.y) * COSS(arg0->unk_94.z);
    arg0->unk_7C.y = arg0->unk_74 * (COSS(arg0->unk_94.x) * SINS(arg0->unk_94.y) * SINS(arg0->unk_94.z) -
                                     SINS(arg0->unk_94.x) * COSS(arg0->unk_94.y));
    arg0->unk_7C.z = arg0->unk_74 * (SINS(arg0->unk_94.x) * SINS(arg0->unk_94.y) * SINS(arg0->unk_94.z) +
                                     COSS(arg0->unk_94.x) * COSS(arg0->unk_94.y));
}

void Particle_Field7C_SetVecFromField74AnglesYZVariant_0B700(ParticleEffectInstance* arg0) {
    arg0->unk_7C.x = arg0->unk_74 * (SINS(arg0->unk_94.y) * COSS(arg0->unk_94.z) +
                                     SINS(arg0->unk_94.x) * COSS(arg0->unk_94.y) * SINS(arg0->unk_94.z));
    arg0->unk_7C.y = arg0->unk_74 * (SINS(arg0->unk_94.y) * SINS(arg0->unk_94.z) -
                                     SINS(arg0->unk_94.x) * COSS(arg0->unk_94.y) * COSS(arg0->unk_94.z));
    arg0->unk_7C.z = arg0->unk_74 * (COSS(arg0->unk_94.x) * COSS(arg0->unk_94.y));
}

void Particle_UpdateRotatingVelocityXZ(ParticleEffectInstance* arg0, f32 arg1, s16 arg2) {
    f32 tmp1 = arg0->unk_50.x;
    f32 tmp2 = arg0->unk_50.z;

    arg0->rotationDelta.y += arg2;

    arg0->unk_50.x = arg1 * gParticleRenderContext.unk_00.y * SINS(arg0->rotationDelta.y);
    arg0->unk_50.z = arg1 * gParticleRenderContext.unk_00.y * COSS(arg0->rotationDelta.y);

    arg0->unk_7C.x = arg0->unk_50.x - tmp1;
    arg0->unk_7C.z = arg0->unk_50.z - tmp2;
}

s32 Particle_Field50_AdvanceField7CWithTimer_0B854(ParticleEffectInstance* arg0, f32 arg1, f32 arg2, f32 arg3, s16 arg4, s16 arg5) {
    s32 sp24 = 0;

    if (Particle_LacksFlags(arg0, 2) != 0) {
        Particle_SetFlags(arg0, 2);
        arg0->unk_50.x = arg0->unk_50.y = arg0->unk_50.z = 0.0f;
        arg0->unk_74 = arg3 * gParticleRenderContext.unk_00.y;
        arg0->unk_7C.y = arg1 * gParticleRenderContext.unk_00.y;
        arg0->unk_94.y = arg4;
        Particle_Field7C_SetXZFromField74AngleY_0B278(arg0);
        arg0->durationTimer = arg5;
    }

    arg0->durationTimer--;
    if (arg0->durationTimer < 0) {
        sp24 = 1;
    } else {
        arg0->unk_7C.y -= arg2 * gParticleRenderContext.unk_00.y;
        Particle_Field50_AddVecFromField7C_09BDC(arg0);
    }

    return sp24;
}

void Particle_Field1C_SetScaled_0B938(ParticleEffectInstance* arg0, f32 arg1) {
    arg0->unk_1C = arg1 * gParticleRenderContext.unk_00.y;
}

void Particle_SetScale(ParticleEffectInstance* arg0, f32 arg1) {
    arg0->unk_1C = arg1;
}

void Particle_SetScaleSpeed(ParticleEffectInstance* arg0, f32 arg1) {
    arg0->unk_20 = arg1 * gParticleRenderContext.unk_00.y;
}

void Particle_SetScaleTarget(ParticleEffectInstance* arg0, f32 arg1) {
    arg0->unk_24 = arg1 * gParticleRenderContext.unk_00.y;
}

s32 Particle_Field1C_Approach_0B98C(ParticleEffectInstance* arg0, f32 arg1, f32 arg2) {
    return ParticleMath_ApproachFloat(&arg0->unk_1C, arg1 * gParticleRenderContext.unk_00.y, arg2 * gParticleRenderContext.unk_00.y);
}

s32 Particle_Field1C_ApproachAndStepState_0B9D0(ParticleEffectInstance* arg0, f32 arg1, f32 arg2) {
    s32 sp1C = Particle_Field1C_Approach_0B98C(arg0, arg1, arg2);

    if (sp1C != 0) {
        Particle_AdvanceLifecycle(arg0);
    }
    return sp1C;
}

s32 Particle_Field1C_ApproachField24ByField20_0BA1C(ParticleEffectInstance* arg0) {
    return ParticleMath_ApproachFloat(&arg0->unk_1C, arg0->unk_20, arg0->unk_24);
}

s32 Particle_Field1C_ApproachField24AndStepState_0BA48(ParticleEffectInstance* arg0) {
    s32 sp1C = Particle_Field1C_ApproachField24ByField20_0BA1C(arg0);

    if (sp1C != 0) {
        Particle_AdvanceLifecycle(arg0);
    }
    return sp1C;
}

s32 Particle_Field20_Approach_0BA84(ParticleEffectInstance* arg0, f32 arg1, f32 arg2) {
    return ParticleMath_ApproachFloat(&arg0->unk_20, arg1 * gParticleRenderContext.unk_00.y, arg2 * gParticleRenderContext.unk_00.y);
}

void Particle_SetPrimColor(ParticleEffectInstance* arg0, u8 arg1, u8 arg2, u8 arg3) {
    arg0->prim_r = arg1;
    arg0->prim_g = arg2;
    arg0->prim_b = arg3;
}

s32 Particle_PrimR_Approach_0BAE4(ParticleEffectInstance* arg0, u8 arg1, u8 arg2) {
    return ParticleMath_ApproachU8(&arg0->prim_r, arg1, arg2);
}

s32 Particle_PrimG_Approach_0BB14(ParticleEffectInstance* arg0, u8 arg1, u8 arg2) {
    return ParticleMath_ApproachU8(&arg0->prim_g, arg1, arg2);
}

s32 Particle_PrimB_Approach_0BB44(ParticleEffectInstance* arg0, u8 arg1, u8 arg2) {
    return ParticleMath_ApproachU8(&arg0->prim_b, arg1, arg2);
}

void Particle_SetEnvColor(ParticleEffectInstance* arg0, u8 arg1, u8 arg2, u8 arg3) {
    arg0->env_r = arg1;
    arg0->env_g = arg2;
    arg0->env_b = arg3;
}

s32 Particle_EnvR_Approach_0BB90(ParticleEffectInstance* arg0, u8 arg1, u8 arg2) {
    return ParticleMath_ApproachU8(&arg0->env_r, arg1, arg2);
}

s32 Particle_EnvB_Approach_0BBC0(ParticleEffectInstance* arg0, u8 arg1, u8 arg2) {
    return ParticleMath_ApproachU8(&arg0->env_b, arg1, arg2);
}

s32 Particle_EnvG_Approach_0BBF0(ParticleEffectInstance* arg0, u8 arg1, u8 arg2) {
    return ParticleMath_ApproachU8(&arg0->env_g, arg1, arg2);
}

void Particle_SetPrimAlpha(ParticleEffectInstance* arg0, u8 arg1) {
    arg0->prim_a = arg1;
}

s32 Particle_PrimAlpha_Approach_0BC2C(ParticleEffectInstance* arg0, u8 arg1, u8 arg2) {
    return ParticleMath_ApproachU8(&arg0->prim_a, arg1, arg2);
}

s32 Particle_PrimAlpha_ApproachAndStepState_0BC5C(ParticleEffectInstance* arg0, u8 arg1, u8 arg2) {
    s32 sp1C = Particle_PrimAlpha_Approach_0BC2C(arg0, arg1, arg2);

    if (sp1C != 0) {
        Particle_AdvanceLifecycle(arg0);
    }
    return sp1C;
}

void Particle_FieldA6_SetS16_0BCA8(ParticleEffectInstance* arg0, s16 arg1) {
    arg0->initialAlpha = arg1;
}

s16 Particle_FieldA6_GetS16_0BCBC(ParticleEffectInstance* arg0) {
    return arg0->initialAlpha;
}

s32 Particle_FieldA6_DecrementTo_0BCC4(ParticleEffectInstance* arg0, s16 arg1, s16 arg2) {
    s32 var_v1 = 0;

    arg0->initialAlpha -= arg2;
    if (arg1 >= arg0->initialAlpha) {
        arg0->initialAlpha = arg1;
        var_v1 = 1;
    }
    return var_v1;
}

s32 Particle_FieldA6_DecrementToZero_0BD08(ParticleEffectInstance* arg0, s16 arg1) {
    return Particle_FieldA6_DecrementTo_0BCC4(arg0, 0, arg1);
}

s32 Particle_FieldA6_DecrementToZeroAndStepState_0BD34(ParticleEffectInstance* arg0, s16 arg1) {
    s32 sp1C = Particle_FieldA6_DecrementTo_0BCC4(arg0, 0, arg1);

    if (sp1C != 0) {
        Particle_AdvanceLifecycle(arg0);
    }
    return sp1C;
}

s32 Particle_FieldA6_DecrementToStep1_0BD80(ParticleEffectInstance* arg0, s16 arg1) {
    return Particle_FieldA6_DecrementTo_0BCC4(arg0, arg1, 1);
}

s32 Particle_FieldA6_DecrementToZeroStep1_0BDAC(ParticleEffectInstance* arg0) {
    return Particle_FieldA6_DecrementTo_0BCC4(arg0, 0, 1);
}

s32 Particle_FieldA6_DecrementToZeroStep1AndStepState_0BDD0(ParticleEffectInstance* arg0) {
    s32 sp1C = Particle_FieldA6_DecrementTo_0BCC4(arg0, 0, 1);

    if (sp1C != 0) {
        Particle_AdvanceLifecycle(arg0);
    }
    return sp1C;
}

void Particle_FieldA8_SetS16_0BE14(ParticleEffectInstance* arg0, s16 arg1) {
    arg0->unk_A8 = arg1;
}

s16 Particle_FieldA8_GetS16_0BE28(ParticleEffectInstance* arg0) {
    return arg0->unk_A8;
}

s32 Particle_FieldA8_DecrementTo_0BE30(ParticleEffectInstance* arg0, s16 arg1) {
    s32 var_v1 = 0;

    arg0->unk_A8--;
    if (arg1 >= arg0->unk_A8) {
        arg0->unk_A8 = arg1;
        var_v1 = 1;
    }
    return var_v1;
}

s32 Particle_FieldA8_DecrementToZeroStep1_0BE6C(ParticleEffectInstance* arg0) {
    return Particle_FieldA8_DecrementTo_0BE30(arg0, 0);
}

s32 Particle_FieldA8_DecrementToZeroStep1AndStepState_0BE8C(ParticleEffectInstance* arg0) {
    s32 sp1C = Particle_FieldA8_DecrementTo_0BE30(arg0, 0);

    if (sp1C != 0) {
        Particle_AdvanceLifecycle(arg0);
    }
    return sp1C;
}

void Particle_FieldCA_SetU8_0BECC(ParticleEffectInstance* arg0, u8 arg1) {
    arg0->effectType = arg1;
}

void Particle_FieldAC_SetS16_0BED8(ParticleEffectInstance* arg0, s16 arg1) {
    arg0->unk_AC = arg1;
}

void Particle_FieldCF_SetU8_0BEEC(ParticleEffectInstance* arg0, u8 arg1) {
    arg0->paletteIndex = arg1;
}

void Particle_FieldCF_SetU8Alt_0BEF8(ParticleEffectInstance* arg0, u8 arg1) {
    arg0->paletteIndex = arg1;
}

void Particle_FieldCC_SetU8_0BF04(ParticleEffectInstance* arg0, u8 arg1) {
    arg0->unk_CC = arg1;
}

void Particle_FieldAA_SetS16_0BF10(ParticleEffectInstance* arg0, s16 arg1) {
    arg0->alphaStep = arg1;
}

void Particle_FieldCE_SetS16_0BF24(ParticleEffectInstance* arg0, s16 arg1) {
    arg0->unk_CE = arg1;
}

void Particle_FieldCD_SetS16_0BF38(ParticleEffectInstance* arg0, s16 arg1) {
    arg0->targetAlpha = arg1;
}

void Particle_FieldAE_SetS16_0BF4C(ParticleEffectInstance* arg0, s16 arg1) {
    arg0->alpha = arg1;
}

s32 Particle_FieldAE_Approach_0BF60(ParticleEffectInstance* arg0, s16 arg1, s16 arg2) {
    return ParticleMath_ApproachS16(&arg0->alpha, arg1, arg2);
}

s32 Particle_FieldAE_ApproachAndStepState_0BF98(ParticleEffectInstance* arg0, s16 arg1, s16 arg2) {
    s32 sp1C = Particle_FieldAE_Approach_0BF60(arg0, arg1, arg2);

    if (sp1C != 0) {
        Particle_AdvanceLifecycle(arg0);
    }
    return sp1C;
}

void Particle_FieldB0_SetS16_0BFEC(ParticleEffectInstance* arg0, s16 arg1) {
    arg0->unk_B0 = arg1;
}

s32 Particle_FieldB0_Approach_0C000(ParticleEffectInstance* arg0, s16 arg1, s16 arg2) {
    return ParticleMath_ApproachS16(&arg0->unk_B0, arg1, arg2);
}

s16 Particle_FieldAC_GetS16_0C038(ParticleEffectInstance* arg0) {
    return arg0->unk_AC;
}

s32 Particle_FieldCE_GetS32_0C040(ParticleEffectInstance* arg0) {
    return arg0->unk_CE;
}

u8 Particle_FieldCD_GetU8_0C048(ParticleEffectInstance* arg0) {
    return arg0->targetAlpha;
}

s16 Particle_FieldAE_GetS16_0C050(ParticleEffectInstance* arg0) {
    return arg0->alpha;
}

s16 Particle_FieldCF_GetS16_0C058(ParticleEffectInstance* arg0) {
    s32 tmp = arg0->paletteIndex;
    return tmp;
}

s16 Particle_FieldAA_GetS16_0C068(ParticleEffectInstance* arg0) {
    return arg0->alphaStep;
}

void Particle_SetFieldOffsetACIfNotSentinel(ParticleEffectInstance* arg0, s16 arg1) {
    if ((u32)arg0 != -1) {
        Particle_FieldAC_SetS16_0BED8(arg0, arg1);
    }
}

void Particle_SetFieldOffsetCFIfNotSentinel(ParticleEffectInstance* arg0, u8 arg1) {
    if ((u32)arg0 != -1) {
        Particle_FieldCF_SetU8_0BEEC(arg0, arg1);
    }
}

void Particle_SetFieldOffsetA6IfNotSentinel(ParticleEffectInstance* arg0, s16 arg1) {
    if ((u32)arg0 != -1) {
        Particle_FieldA6_SetS16_0BCA8(arg0, arg1);
    }
}

void Particle_SetFieldOffsetA8IfNotSentinel(ParticleEffectInstance* arg0, s16 arg1) {
    if ((u32)arg0 != -1) {
        Particle_FieldA8_SetS16_0BE14(arg0, arg1);
    }
}

void Particle_SetFieldOffsetCEIfNotSentinel(ParticleEffectInstance* arg0, u8 arg1) {
    if ((u32)arg0 != -1) {
        arg0->unk_CE = arg1;
    }
}

void Particle_SetFieldOffsetCDIfNotSentinel(ParticleEffectInstance* arg0, u8 arg1) {
    if ((u32)arg0 != -1) {
        arg0->targetAlpha = arg1;
    }
}

void Particle_SetFieldOffsetAAIfNotSentinel(ParticleEffectInstance* arg0, s16 arg1) {
    if ((u32)arg0 != -1) {
        arg0->alphaStep = arg1;
    }
}

void Particle_SetPrimAlphaIfNotSentinel(ParticleEffectInstance* arg0, u8 arg1) {
    if ((u32)arg0 != -1) {
        Particle_SetPrimAlpha(arg0, arg1);
    }
}

void Particle_SetFieldOffsetAEIfNotSentinel(ParticleEffectInstance* arg0, s16 arg1) {
    if ((u32)arg0 != -1) {
        arg0->alpha = arg1;
    }
}

void Particle_SetFieldOffsetB0IfNotSentinel(ParticleEffectInstance* arg0, s16 arg1) {
    if ((u32)arg0 != -1) {
        arg0->unk_B0 = arg1;
    }
}

void Particle_RenderWorldChains(CameraStruct* arg0) {
    s32 i;
    ParticleEffectInstance* var_s0;
    ParticleEffectInstance* var_s2 = gParticlePool;

    for (i = 0; i < 0x12C; i++, var_s2++) {
        if ((var_s2->unk_D0 != 0) && (var_s2->prev == NULL) && (Particle_LacksFlags(var_s2, 8) != 0)) {
            Particle_PrepareRender(var_s2);
            var_s0 = var_s2;
            while (var_s0 != NULL) {
                if ((Particle_HasFlags(var_s0, 4) != 0) && (var_s0->updateState >= 2)) {
                    Particle_DispatchDraw(var_s0, arg0);
                }
                var_s0 = var_s0->next;
            }
        }
    }
}

void Particle_RenderOrthoParticles(CameraStruct* arg0) {
    s32 i;
    ParticleEffectInstance* var_s0 = gParticlePool;

    for (i = 0; i < 0x12C; i++, var_s0++) {
        if ((var_s0->unk_D0 != 0) && (Particle_HasFlags(var_s0, 8) != 0)) {
            Particle_PrepareRender(var_s0);
            if ((Particle_HasFlags(var_s0, 4) != 0) && (var_s0->updateState >= 2)) {
                Particle_DispatchDraw(var_s0, arg0);
            }
        }
    }
}

void Particle_SetRenderMode(s16 arg0) {
    switch (arg0) {
        case 0:
            gSPDisplayList(gDisplayListHead++, gDL_OverlayUI);
            break;

        case 2:
            gSPDisplayList(gDisplayListHead++, gDL_OverlayUI2);
            break;

        case 1:
            gSPDisplayList(gDisplayListHead++, gDL_BaseUI);
            break;

        case 3:
            gSPDisplayList(gDisplayListHead++, gDL_BaseUI2);
            break;
    }
}

void Particle_InvokeRenderSetup(ParticleEffectInstance* arg0, ParticleRenderSettings* arg1) {
    switch (arg1->unk_01) {
        case 0:
            arg1->unk_04(arg0, arg1->unk_0C.arg, arg1);
            break;

        case 1:
            arg1->unk_04(arg0, arg1->unk_0C.s->arg, arg1);
            break;
    }
}

void Particle_PrepareRender(ParticleEffectInstance* arg0) {
    UNUSED s32 pad;
    ParticleRenderSettings* sp18 = arg0->unk_0C->unk_04.a;

    if (arg0->unk_0C->unk_00 == 1) {
        Particle_SetRenderMode(sp18->unk_02);
        if (sp18->unk_00 == 1) {
            Particle_InvokeRenderSetup(arg0, sp18);
        }
    }
}

void Particle_DispatchDraw(ParticleEffectInstance* arg0, CameraStruct* arg1) {
    UNUSED s32 pad;
    ParticleRenderSettings* sp18 = arg0->unk_0C->unk_04.a;

    switch (arg0->unk_0C->unk_00) {
        case 1:
            if (sp18->unk_00 == 0) {
                Particle_InvokeRenderSetup(arg0, sp18);
            }
            sp18->unk_08(arg0, arg1, sp18);
            break;

        case 3:
            arg0->unk_0C->unk_04.func(arg0, arg1);
            break;
    }
}

void Particle_NoopDraw(UNUSED ParticleEffectInstance* arg0, UNUSED CameraStruct* arg1) {
}
