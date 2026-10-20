#include "src/fragments/particle_math/particle_math.h"
#include "src/geo_render.h"

ParticleEffectData gParticleDefaultCallback = { 3, Particle_NoopDraw };

void Particle_ResetDefaults(ParticleEffectInstance* arg0) {
    Particle_InitLifecycle(arg0);
    Particle_SetVelocityScaledXYZ(arg0, 0.0f, 0.0f, 0.0f);
    Particle_SetOrigin(arg0, 0.0f, 0.0f, 0.0f);
    Particle_SetVelocity(arg0, 0.0f, 0.0f, 0.0f);
    Particle_SetVelocityTarget(arg0, 0.0f, 0.0f, 0.0f);
    Particle_SetVelocityImpulse(arg0, 0.0f, 0.0f, 0.0f);
    Particle_SetSpeed(arg0, 0.0f);
    Particle_SetAcceleration(arg0, 0.0f);
    Particle_SetRotation(arg0, 0, 0, 0);
    Particle_SetRotationSpeed(arg0, 0, 0, 0);
    Particle_SetTextureFrame(arg0, 0);
    Particle_SetTimerA6(arg0, 0);
    Particle_SetTimerA8(arg0, 0);
    Particle_SetTargetAlpha(arg0, 0);
    Particle_SetMetadata(arg0, 0);
    Particle_SetAlphaStep(arg0, 0);
    Particle_SetFieldOffsetAC(arg0, 0);
    Particle_SetPaletteIndex(arg0, 0);
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

        sp1C->RentalSlotAnimData_PosePhase = arg3;
        sp1C->unk_0C = arg4;
        sp1C->unk_10 = 0;
        sp1C->unk_14 = 0;
        sp1C->unk_AC = arg5;
        sp1C->metadata = arg7;
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

        sp1C->RentalSlotAnimData_PosePhase = arg1;
        sp1C->unk_0C = arg2;

        sp1C->unk_10 = 0;
        sp1C->unk_14 = 0;

        sp1C->unk_AC = arg3;
        sp1C->metadata = arg5;
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
    arg0->RentalSlotAnimData_PosePhase = NULL;
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

    arg0->RentalSlotAnimData_PosePhase = NULL;
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
    arg0->unk_38.x = arg1 * gParticleRenderContext.posX.y;
    arg0->unk_38.y = arg2 * gParticleRenderContext.posX.y;
    arg0->unk_38.z = arg3 * gParticleRenderContext.posX.y;
}

void Particle_SetVelocityScaledVec(ParticleEffectInstance* arg0, Vec3f arg1) {
    arg0->unk_38.x = arg1.x * gParticleRenderContext.posX.y;
    arg0->unk_38.y = arg1.y * gParticleRenderContext.posX.y;
    arg0->unk_38.z = arg1.z * gParticleRenderContext.posX.y;
}

void Particle_SetVelocityDirectXYZ(ParticleEffectInstance* arg0, f32 arg1, f32 arg2, f32 arg3) {
    arg0->unk_38.x = arg1;
    arg0->unk_38.y = arg2;
    arg0->unk_38.z = arg3;
}

void Particle_SetVelocityXScaled(ParticleEffectInstance* arg0, f32 arg1) {
    arg0->unk_38.x = arg1 * gParticleRenderContext.posX.y;
}

void Particle_SetVelocityYScaled(ParticleEffectInstance* arg0, f32 arg1) {
    arg0->unk_38.y = arg1 * gParticleRenderContext.posX.y;
}

void Particle_SetVelocityZScaled(ParticleEffectInstance* arg0, f32 arg1) {
    arg0->unk_38.z = arg1 * gParticleRenderContext.posX.y;
}

void Particle_SetPositionFromRotationXYZAlt(ParticleEffectInstance* arg0, f32 arg1) {
    Vec3f sp1C;

    Particle_ComputeVectorFromRotationXYZAlt(arg0, arg1, &sp1C);
    Particle_SetVelocityScaledVec(arg0, sp1C);
}

void Particle_SetPositionFromRotationYZ(ParticleEffectInstance* arg0, f32 arg1) {
    Vec3f sp1C;

    Particle_ComputeVectorFromRotationYAndRotationX(arg0, arg1, &sp1C);
    Particle_SetVelocityScaledVec(arg0, sp1C);
}

void Particle_AddVelocityScaledVec(ParticleEffectInstance* arg0, Vec3f arg1) {
    arg0->unk_38.x += arg1.x * gParticleRenderContext.posX.y;
    arg0->unk_38.y += arg1.y * gParticleRenderContext.posX.y;
    arg0->unk_38.z += arg1.z * gParticleRenderContext.posX.y;
}

void Particle_AddVelocityDirectVec(ParticleEffectInstance* arg0, Vec3f arg1) {
    arg0->unk_38.x += arg1.x;
    arg0->unk_38.y += arg1.y;
    arg0->unk_38.z += arg1.z;
}

void Particle_AddVelocityScaledXYZ(ParticleEffectInstance* arg0, f32 arg1, f32 arg2, f32 arg3) {
    arg0->unk_38.x += arg1 * gParticleRenderContext.posX.y;
    arg0->unk_38.y += arg2 * gParticleRenderContext.posX.y;
    arg0->unk_38.z += arg3 * gParticleRenderContext.posX.y;
}

void Particle_AddVelocityXScaled(ParticleEffectInstance* arg0, f32 arg1) {
    arg0->unk_38.x += arg1 * gParticleRenderContext.posX.y;
}

void Particle_AddVelocityYScaled(ParticleEffectInstance* arg0, f32 arg1) {
    arg0->unk_38.y += arg1 * gParticleRenderContext.posX.y;
}

void Particle_AddVelocityZScaled(ParticleEffectInstance* arg0, f32 arg1) {
    arg0->unk_38.z += arg1 * gParticleRenderContext.posX.y;
}

void Particle_AddVelocityForward(ParticleEffectInstance* arg0, f32 arg1) {
    arg0->unk_38.x += arg1 * SINS(arg0->unk_94.y) * gParticleRenderContext.posX.y;
    arg0->unk_38.z += arg1 * COSS(arg0->unk_94.y) * gParticleRenderContext.posX.y;
}

void Particle_AddVelocityBackward(ParticleEffectInstance* arg0, f32 arg1) {
    arg0->unk_38.x += arg1 * SINS(arg0->unk_94.y + 0x8000) * gParticleRenderContext.posX.y;
    arg0->unk_38.z += arg1 * COSS(arg0->unk_94.y + 0x8000) * gParticleRenderContext.posX.y;
}

void Particle_AddVelocityRight(ParticleEffectInstance* arg0, f32 arg1) {
    arg0->unk_38.x += arg1 * SINS(arg0->unk_94.y + 0x4000) * gParticleRenderContext.posX.y;
    arg0->unk_38.z += arg1 * COSS(arg0->unk_94.y + 0x4000) * gParticleRenderContext.posX.y;
}

void Particle_AddVelocityLeft(ParticleEffectInstance* arg0, f32 arg1) {
    arg0->unk_38.x += arg1 * SINS(arg0->unk_94.y - 0x4000) * gParticleRenderContext.posX.y;
    arg0->unk_38.z += arg1 * COSS(arg0->unk_94.y - 0x4000) * gParticleRenderContext.posX.y;
}

void Particle_AddVelocityFromDirVector(ParticleEffectInstance* arg0, f32 arg1) {
    Vec3f sp1C;

    Particle_ComputeVectorFromRotationY(arg0, arg1, &sp1C);
    arg0->unk_38.x += sp1C.x * gParticleRenderContext.posX.y;
    arg0->unk_38.y += sp1C.y * gParticleRenderContext.posX.y;
    arg0->unk_38.z += sp1C.z * gParticleRenderContext.posX.y;
}

void Particle_AddPositionFromRotationXYZAlt(ParticleEffectInstance* arg0, f32 arg1) {
    Vec3f sp1C;

    Particle_ComputeVectorFromRotationXYZAlt(arg0, arg1, &sp1C);
    Particle_AddVelocityScaledVec(arg0, sp1C);
}

void Particle_AddPositionFromRotationYZ(ParticleEffectInstance* arg0, f32 arg1) {
    Vec3f sp1C;

    Particle_ComputeVectorFromRotationYAndRotationX(arg0, arg1, &sp1C);
    Particle_AddVelocityScaledVec(arg0, sp1C);
}

void Particle_AddPositionRotatedVectorByYaw(ParticleEffectInstance* arg0, Vec3f arg1) {
    Vec3f sp24;

    ParticleMath_RotateVec3fY(&sp24, arg1, arg0->unk_94);
    Particle_AddVelocityScaledVec(arg0, sp24);
}

void Particle_SetRandomVelocityX(ParticleEffectInstance* arg0, s32 arg1) {
    arg0->unk_38.x = ParticleMath_RandomSigned(arg1) * gParticleRenderContext.posX.y;
}

void Particle_SetRandomVelocityY(ParticleEffectInstance* arg0, s32 arg1) {
    arg0->unk_38.y = ParticleMath_RandomSigned(arg1) * gParticleRenderContext.posX.y;
}

void Particle_SetRandomVelocityZ(ParticleEffectInstance* arg0, s32 arg1) {
    arg0->unk_38.z = ParticleMath_RandomSigned(arg1) * gParticleRenderContext.posX.y;
}

void Particle_SetRandomVelocityXOffset(ParticleEffectInstance* arg0, s32 arg1, s32 arg2) {
    arg0->unk_38.x = (ParticleMath_RandomSigned(arg1) * gParticleRenderContext.posX.y) + arg2;
}

void Particle_SetRandomVelocityYOffset(ParticleEffectInstance* arg0, s32 arg1, s32 arg2) {
    arg0->unk_38.y = (ParticleMath_RandomSigned(arg1) * gParticleRenderContext.posX.y) + arg2;
}

void Particle_SetRandomVelocityZOffset(ParticleEffectInstance* arg0, s32 arg1, s32 arg2) {
    arg0->unk_38.z = (ParticleMath_RandomSigned(arg1) * gParticleRenderContext.posX.y) + arg2;
}

void Particle_SetRandomVelocityXSymmetric(ParticleEffectInstance* arg0, s32 arg1, s32 arg2) {
    f32 temp_fv0 = ParticleMath_RandomSigned(arg1);

    if (temp_fv0 >= 0.0f) {
        arg0->unk_38.x = (temp_fv0 + arg2) * gParticleRenderContext.posX.y;
    } else {
        arg0->unk_38.x = (temp_fv0 - arg2) * gParticleRenderContext.posX.y;
    }
}

void Particle_SetRandomVelocityYSymmetric(ParticleEffectInstance* arg0, s32 arg1, s32 arg2) {
    f32 temp_fv0 = ParticleMath_RandomSigned(arg1);

    if (temp_fv0 >= 0.0f) {
        arg0->unk_38.y = (temp_fv0 + arg2) * gParticleRenderContext.posX.y;
    } else {
        arg0->unk_38.y = (temp_fv0 - arg2) * gParticleRenderContext.posX.y;
    }
}

void Particle_SetRandomVelocityZSymmetric(ParticleEffectInstance* arg0, s32 arg1, s32 arg2) {
    f32 temp_fv0 = ParticleMath_RandomSigned(arg1);

    if (temp_fv0 >= 0.0f) {
        arg0->unk_38.z = (temp_fv0 + arg2) * gParticleRenderContext.posX.y;
    } else {
        arg0->unk_38.z = (temp_fv0 - arg2) * gParticleRenderContext.posX.y;
    }
}

void Particle_SetRandomVelocityXYZ(ParticleEffectInstance* arg0, s32 arg1, s32 arg2, s32 arg3) {
    Vec3f sp18;

    sp18.x = ParticleMath_RandomSigned(arg1);
    sp18.y = ParticleMath_RandomSigned(arg2);
    sp18.z = ParticleMath_RandomSigned(arg3);

    arg0->unk_38.x = sp18.x * gParticleRenderContext.posX.y;
    arg0->unk_38.y = sp18.y * gParticleRenderContext.posX.y;
    arg0->unk_38.z = sp18.z * gParticleRenderContext.posX.y;
}

void Particle_SetRandomModVelocityXYZ(ParticleEffectInstance* arg0, s32 arg1, s32 arg2, s32 arg3) {
    Vec3f sp1C;

    sp1C.x = ParticleMath_RandomRange(arg1);
    sp1C.y = ParticleMath_RandomRange(arg2);
    sp1C.z = ParticleMath_RandomRange(arg3);

    arg0->unk_38.x = sp1C.x * gParticleRenderContext.posX.y;
    arg0->unk_38.y = sp1C.y * gParticleRenderContext.posX.y;
    arg0->unk_38.z = sp1C.z * gParticleRenderContext.posX.y;
}

void Particle_SetRandomRotatedVelocityXY(ParticleEffectInstance* arg0, s32 arg1, s32 arg2) {
    Vec3f sp2C;
    Vec3f sp20;

    sp2C.x = ParticleMath_RandomSigned(arg1);
    sp2C.y = ParticleMath_RandomSigned(arg2);
    sp2C.z = 0.0f;

    ParticleMath_RotateVec3fY(&sp20, sp2C, arg0->unk_94);

    arg0->unk_38.x = sp20.x * gParticleRenderContext.posX.y;
    arg0->unk_38.y = sp20.y * gParticleRenderContext.posX.y;
    arg0->unk_38.z = sp20.z * gParticleRenderContext.posX.y;
}

void Particle_AddRandomVelocityXYZ(ParticleEffectInstance* arg0, s32 arg1, s32 arg2, s32 arg3) {
    Vec3f sp24;

    sp24.x = ParticleMath_RandomSigned(arg1);
    sp24.y = ParticleMath_RandomSigned(arg2);
    sp24.z = ParticleMath_RandomSigned(arg3);

    arg0->unk_38.x += sp24.x * gParticleRenderContext.posX.y;
    arg0->unk_38.y += sp24.y * gParticleRenderContext.posX.y;
    arg0->unk_38.z += sp24.z * gParticleRenderContext.posX.y;
}

void Particle_SetOrigin(ParticleEffectInstance* arg0, f32 arg1, f32 arg2, f32 arg3) {
    arg0->unk_68.x = arg1;
    arg0->unk_68.y = arg2;
    arg0->unk_68.z = arg3;
}

void Particle_SetVelocity(ParticleEffectInstance* arg0, f32 arg1, f32 arg2, f32 arg3) {
    arg0->unk_50.x = arg1 * gParticleRenderContext.posX.y;
    arg0->unk_50.y = arg2 * gParticleRenderContext.posX.y;
    arg0->unk_50.z = arg3 * gParticleRenderContext.posX.y;
}

void Particle_SetVelocityX(ParticleEffectInstance* arg0, f32 arg1) {
    arg0->unk_50.x = arg1 * gParticleRenderContext.posX.y;
}

void Particle_SetVelocityY(ParticleEffectInstance* arg0, f32 arg1) {
    arg0->unk_50.y = arg1 * gParticleRenderContext.posX.y;
}

void Particle_SetVelocityZ(ParticleEffectInstance* arg0, f32 arg1) {
    arg0->unk_50.z = arg1 * gParticleRenderContext.posX.y;
}

void Particle_SetVelocityRandomDirection(ParticleEffectInstance* arg0, f32 arg1) {
    ParticleMath_RandomDirection(&arg0->unk_50, arg1 * gParticleRenderContext.posX.y);
}

void Particle_AddVelocity(ParticleEffectInstance* arg0, f32 arg1, f32 arg2, f32 arg3) {
    arg0->unk_50.x += arg1 * gParticleRenderContext.posX.y;
    arg0->unk_50.y += arg2 * gParticleRenderContext.posX.y;
    arg0->unk_50.z += arg3 * gParticleRenderContext.posX.y;
}

void Particle_AddScaledVelocityX(ParticleEffectInstance* arg0, f32 arg1) {
    arg0->unk_50.x += arg1 * gParticleRenderContext.posX.y;
}

void Particle_AddScaledVelocityY(ParticleEffectInstance* arg0, f32 arg1) {
    arg0->unk_50.y += arg1 * gParticleRenderContext.posX.y;
}

void Particle_AddScaledVelocityZ(ParticleEffectInstance* arg0, f32 arg1) {
    arg0->unk_50.z += arg1 * gParticleRenderContext.posX.y;
}

void Particle_SubtractScaledVelocityXYZ(ParticleEffectInstance* arg0, f32 arg1, f32 arg2, f32 arg3) {
    arg0->unk_50.x -= arg1 * gParticleRenderContext.posX.y;
    arg0->unk_50.y -= arg2 * gParticleRenderContext.posX.y;
    arg0->unk_50.z -= arg3 * gParticleRenderContext.posX.y;
}

void Particle_SubtractScaledVelocityX(ParticleEffectInstance* arg0, f32 arg1) {
    arg0->unk_50.x -= arg1 * gParticleRenderContext.posX.y;
}

void Particle_SubtractScaledVelocityY(ParticleEffectInstance* arg0, f32 arg1) {
    arg0->unk_50.y -= arg1 * gParticleRenderContext.posX.y;
}

void Particle_SubtractScaledVelocityZ(ParticleEffectInstance* arg0, f32 arg1) {
    arg0->unk_50.z -= arg1 * gParticleRenderContext.posX.y;
}

s32 Particle_ApproachVelocityX(ParticleEffectInstance* arg0, f32 arg1) {
    return ParticleMath_ApproachFloat(&arg0->unk_50.x, arg1 * gParticleRenderContext.posX.y, arg0->unk_5C.x);
}

s32 Particle_ApproachVelocityY(ParticleEffectInstance* arg0, f32 arg1) {
    return ParticleMath_ApproachFloat(&arg0->unk_50.y, arg1 * gParticleRenderContext.posX.y, arg0->unk_5C.y);
}

s32 Particle_ApproachVelocityZ(ParticleEffectInstance* arg0, f32 arg1) {
    return ParticleMath_ApproachFloat(&arg0->unk_50.z, arg1 * gParticleRenderContext.posX.y, arg0->unk_5C.z);
}

void Particle_CopyVelocityFromTarget(ParticleEffectInstance* arg0) {
    arg0->unk_50.x = arg0->unk_7C.x;
    arg0->unk_50.y = arg0->unk_7C.y;
    arg0->unk_50.z = arg0->unk_7C.z;
}

void Particle_CopyVelocityXZFromTarget(ParticleEffectInstance* arg0) {
    arg0->unk_50.x = arg0->unk_7C.x;
    arg0->unk_50.z = arg0->unk_7C.z;
}

void Particle_CopyVelocityXYFromTarget(ParticleEffectInstance* arg0) {
    arg0->unk_50.x = arg0->unk_7C.x;
    arg0->unk_50.y = arg0->unk_7C.y;
}

void Particle_AddVelocityFromTarget(ParticleEffectInstance* arg0) {
    arg0->unk_50.x += arg0->unk_7C.x;
    arg0->unk_50.y += arg0->unk_7C.y;
    arg0->unk_50.z += arg0->unk_7C.z;
}

void Particle_AddVelocityXZFromTarget(ParticleEffectInstance* arg0) {
    arg0->unk_50.x += arg0->unk_7C.x;
    arg0->unk_50.z += arg0->unk_7C.z;
}

void Particle_AddVelocityXYFromTarget(ParticleEffectInstance* arg0) {
    arg0->unk_50.x += arg0->unk_7C.x;
    arg0->unk_50.y += arg0->unk_7C.y;
}

void Particle_AddVelocityXFromTarget(ParticleEffectInstance* arg0) {
    arg0->unk_50.x += arg0->unk_7C.x;
}

void Particle_AddVelocityYFromTarget(ParticleEffectInstance* arg0) {
    arg0->unk_50.y += arg0->unk_7C.y;
}

void Particle_AddVelocityZFromTarget(ParticleEffectInstance* arg0) {
    arg0->unk_50.z += arg0->unk_7C.z;
}

void Particle_ApplyB278AndCopyXZ(ParticleEffectInstance* arg0) {
    Particle_SetVelocityImpulseXZFromRotationY(arg0);
    Particle_CopyVelocityXZFromTarget(arg0);
}

void Particle_AddVelocityXZFromRotationYViaImpulse(ParticleEffectInstance* arg0) {
    Particle_SetVelocityImpulseXZFromRotationY(arg0);
    Particle_AddVelocityXZFromTarget(arg0);
}

void Particle_AddVelocityXYFromRotationZViaImpulse(ParticleEffectInstance* arg0) {
    Particle_SetVelocityImpulseXYFromRotationZ(arg0);
    Particle_AddVelocityXYFromTarget(arg0);
}

void Particle_AddVelocityFromRotationXY(ParticleEffectInstance* arg0) {
    Particle_SetVelocityImpulseFromRotationXY(arg0);
    Particle_AddVelocityFromTarget(arg0);
}

void Particle_AddVelocityFromRotationXZ(ParticleEffectInstance* arg0) {
    Particle_SetVelocityImpulseFromRotationXZ(arg0);
    Particle_AddVelocityFromTarget(arg0);
}

void Particle_AddVelocityFromRotationXYAlt(ParticleEffectInstance* arg0) {
    Particle_SetVelocityImpulseFromRotationXYAlt(arg0);
    Particle_AddVelocityFromTarget(arg0);
}

void Particle_AddVelocityFromRotationYZ(ParticleEffectInstance* arg0) {
    Particle_SetVelocityImpulseFromRotationYZ(arg0);
    Particle_AddVelocityFromTarget(arg0);
}

void Particle_AddVelocityFromRotationXYZAlt(ParticleEffectInstance* arg0) {
    Particle_SetVelocityImpulseFromRotationXYZAlt(arg0);
    Particle_AddVelocityFromTarget(arg0);
}

void Particle_AddVelocityFromRotationXYZ(ParticleEffectInstance* arg0) {
    Particle_SetVelocityImpulseFromRotationXYZ(arg0);
    Particle_AddVelocityFromTarget(arg0);
}

void Particle_AddVelocityFromRotationTemplate7A(ParticleEffectInstance* arg0) {
    Particle_SetVelocityImpulseFromRotationYZAlt(arg0);
    Particle_AddVelocityFromTarget(arg0);
}

void Particle_AddVelocityFromRotationTemplate7B(ParticleEffectInstance* arg0) {
    Particle_SetVelocityImpulseFromRotationYZAlt(arg0);
    Particle_AddVelocityFromTarget(arg0);
}

void Particle_AddVelocityXZFromRotationY(ParticleEffectInstance* arg0) {
    arg0->unk_7C.x = arg0->unk_74 * SINS(arg0->unk_94.y);
    arg0->unk_7C.z = arg0->unk_74 * COSS(arg0->unk_94.y);

    Particle_AddVelocityXZFromTarget(arg0);
}

void Particle_AddVelocityXZFromRotationYPlusHalfTurn(ParticleEffectInstance* arg0) {
    arg0->unk_7C.x = arg0->unk_74 * SINS(arg0->unk_94.y + 0x8000);
    arg0->unk_7C.z = arg0->unk_74 * COSS(arg0->unk_94.y + 0x8000);

    Particle_AddVelocityXZFromTarget(arg0);
}

void Particle_AddVelocityXZFromRotationYPlusHalfTurnFromArgument(ParticleEffectInstance* arg0, f32 arg1) {
    arg0->unk_7C.x = SINS(arg0->unk_94.y + 0x8000) * arg1;
    arg0->unk_7C.z = COSS(arg0->unk_94.y + 0x8000) * arg1;

    Particle_AddVelocityXZFromTarget(arg0);
}

void Particle_AddVelocityYFromSpeed(ParticleEffectInstance* arg0) {
    arg0->unk_7C.y = arg0->unk_74;

    Particle_AddVelocityYFromTarget(arg0);
}

s32 Particle_FallAndCheckGround(ParticleEffectInstance* arg0) {
    s32 sp1C = 0;

    arg0->unk_7C.y = -arg0->unk_74;
    Particle_AddVelocityYFromTarget(arg0);

    if (arg0->unk_2C.y <= 0.0f) {
        sp1C = 1;
    }
    return sp1C;
}

s32 Particle_FallAccelerateAndCheckGround(ParticleEffectInstance* arg0) {
    s32 sp1C = 0;

    arg0->unk_74 += arg0->unk_78;
    arg0->unk_7C.y = -arg0->unk_74;

    Particle_AddVelocityYFromTarget(arg0);

    if (arg0->unk_2C.y <= 0.0f) {
        sp1C = 1;
    }
    return sp1C;
}

void Particle_SetVelocityTarget(ParticleEffectInstance* arg0, f32 arg1, f32 arg2, f32 arg3) {
    arg0->unk_5C.x = arg1 * gParticleRenderContext.posX.y;
    arg0->unk_5C.y = arg2 * gParticleRenderContext.posX.y;
    arg0->unk_5C.z = arg3 * gParticleRenderContext.posX.y;
}

void Particle_SetVelocityStepXScaled(ParticleEffectInstance* arg0, f32 arg1) {
    arg0->unk_5C.x = arg1 * gParticleRenderContext.posX.y;
}

void Particle_SetVelocityStepYScaled(ParticleEffectInstance* arg0, f32 arg1) {
    arg0->unk_5C.y = arg1 * gParticleRenderContext.posX.y;
}

void Particle_SetVelocityStepZScaled(ParticleEffectInstance* arg0, f32 arg1) {
    arg0->unk_5C.z = arg1 * gParticleRenderContext.posX.y;
}

s32 Particle_ApproachVelocityStepY(ParticleEffectInstance* arg0, f32 arg1, f32 arg2) {
    return ParticleMath_ApproachFloat(&arg0->unk_5C.y, arg1 * gParticleRenderContext.posX.y, arg2 * gParticleRenderContext.posX.y);
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

void Particle_SetRotationFromVec3s(ParticleEffectInstance* arg0, Vec3s arg1) {
    arg0->unk_94.x = arg1.x;
    arg0->unk_94.y = arg1.y;
    arg0->unk_94.z = arg1.z;
}

void Particle_SetRotation(ParticleEffectInstance* arg0, s16 arg1, s16 arg2, s16 arg3) {
    arg0->unk_94.x = arg1;
    arg0->unk_94.y = arg2;
    arg0->unk_94.z = arg3;
}

void Particle_SetRotationX(ParticleEffectInstance* arg0, s16 arg1) {
    arg0->unk_94.x = arg1;
}

void Particle_SetRotationY(ParticleEffectInstance* arg0, s16 arg1) {
    arg0->unk_94.y = arg1;
}

void Particle_SetRotationZ(ParticleEffectInstance* arg0, s16 arg1) {
    arg0->unk_94.z = arg1;
}

void Particle_AddRotationAllAxes(ParticleEffectInstance* arg0) {
    arg0->unk_94.x += 0x8000;
    arg0->unk_94.y += 0x8000;
    arg0->unk_94.z += 0x8000;
}

void Particle_AddRotationX(ParticleEffectInstance* arg0) {
    arg0->unk_94.x += 0x8000;
}

void Particle_AddRotationY(ParticleEffectInstance* arg0) {
    arg0->unk_94.y += 0x8000;
}

void Particle_AddRotationZ(ParticleEffectInstance* arg0) {
    arg0->unk_94.z += 0x8000;
}

void Particle_SetRotationSpeed(ParticleEffectInstance* arg0, s16 arg1, s16 arg2, s16 arg3) {
    arg0->rotationDelta.x = arg1;
    arg0->rotationDelta.y = arg2;
    arg0->rotationDelta.z = arg3;
}

void Particle_SetRotationDeltaFromVec3s(ParticleEffectInstance* arg0, Vec3s arg1) {
    arg0->rotationDelta.x = arg1.x;
    arg0->rotationDelta.y = arg1.y;
    arg0->rotationDelta.z = arg1.z;
}

void Particle_SetRotationDeltaXY(ParticleEffectInstance* arg0, s16 arg1, s16 arg2) {
    arg0->rotationDelta.x = arg1;
    arg0->rotationDelta.y = arg2;
}

void Particle_SetRotationDeltaX(ParticleEffectInstance* arg0, s16 arg1) {
    arg0->rotationDelta.x = arg1;
}

void Particle_SetRotationDeltaY(ParticleEffectInstance* arg0, s16 arg1) {
    arg0->rotationDelta.y = arg1;
}

void Particle_SetRotationDeltaZ(ParticleEffectInstance* arg0, s16 arg1) {
    arg0->rotationDelta.z = arg1;
}

void Particle_SetTargetRotationX(ParticleEffectInstance* arg0, s16 arg1) {
    arg0->unk_A0.x = arg1;
}

void Particle_SetTargetRotationY(ParticleEffectInstance* arg0, s16 arg1) {
    arg0->unk_A0.y = arg1;
}

void Particle_SetRotationTargetXY(ParticleEffectInstance* arg0, s16 arg1, s16 arg2) {
    Particle_SetTargetRotationX(arg0, arg1);
    Particle_SetTargetRotationY(arg0, arg2);
}

void Particle_SetRotationTargetFromCurrent(ParticleEffectInstance* arg0) {
    arg0->unk_A0.x = arg0->unk_94.x;
    arg0->unk_A0.y = arg0->unk_94.y;
    arg0->unk_A0.z = arg0->unk_94.z;
}

void Particle_AddRotationDelta(ParticleEffectInstance* arg0) {
    arg0->unk_94.x += arg0->rotationDelta.x;
    arg0->unk_94.y += arg0->rotationDelta.y;
    arg0->unk_94.z += arg0->rotationDelta.z;
}

void Particle_AddRotationDeltaX(ParticleEffectInstance* arg0) {
    arg0->unk_94.x += arg0->rotationDelta.x;
}

void Particle_AddRotationDeltaY(ParticleEffectInstance* arg0) {
    arg0->unk_94.y += arg0->rotationDelta.y;
}

void Particle_AddRotationDeltaZ(ParticleEffectInstance* arg0) {
    arg0->unk_94.z += arg0->rotationDelta.z;
}

void Particle_AddRotationDeltaVec(ParticleEffectInstance* arg0, Vec3s arg1) {
    arg0->unk_94.x += arg1.x;
    arg0->unk_94.y += arg1.y;
    arg0->unk_94.z += arg1.z;
}

void Particle_AddRotationDeltaXYZ(ParticleEffectInstance* arg0, s16 arg1, s16 arg2, s16 arg3) {
    arg0->unk_94.x += arg1;
    arg0->unk_94.y += arg2;
    arg0->unk_94.z += arg3;
}

void Particle_RotateX(ParticleEffectInstance* arg0, s16 arg1) {
    arg0->unk_94.x += arg1;
}

void Particle_RotateY(ParticleEffectInstance* arg0, s16 arg1) {
    arg0->unk_94.y += arg1;
}

void Particle_RotateZ(ParticleEffectInstance* arg0, s16 arg1) {
    arg0->unk_94.z += arg1;
}

void Particle_AddRotationTargetXY(ParticleEffectInstance* arg0, s16 arg1, s16 arg2) {
    arg0->unk_A0.x += arg1;
    arg0->unk_A0.y += arg2;
}

void Particle_SubtractRotationDeltaVec(ParticleEffectInstance* arg0, Vec3s arg1) {
    arg0->unk_94.x -= arg1.x;
    arg0->unk_94.y -= arg1.y;
    arg0->unk_94.z -= arg1.z;
}

void Particle_SubtractRotationDeltaX(ParticleEffectInstance* arg0, s16 arg1) {
    arg0->unk_94.x -= arg1;
}

void Particle_SubtractRotationDeltaY(ParticleEffectInstance* arg0, s16 arg1) {
    arg0->unk_94.y -= arg1;
}

void Particle_SubtractRotationDeltaZ(ParticleEffectInstance* arg0, s16 arg1) {
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

s32 Particle_DecreaseRotationXTowards(ParticleEffectInstance* arg0, s32 arg1, s32 arg2) {
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

s32 Particle_DecreaseRotationYTowards(ParticleEffectInstance* arg0, s32 arg1, s32 arg2) {
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

s32 Particle_DecreaseRotationZTowards(ParticleEffectInstance* arg0, s32 arg1, s32 arg2) {
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
    Particle_RotateX(arg0, ParticleMath_RandomSigned(arg1));
    Particle_RotateY(arg0, ParticleMath_RandomSigned(arg2));
}

void Particle_AddRotationRandomSignedXYWithXHalfTurn(ParticleEffectInstance* arg0, s32 arg1, s32 arg2) {
    Particle_RotateX(arg0, ParticleMath_RandomSignedOffset(arg1, 0x8000));
    Particle_RotateY(arg0, ParticleMath_RandomSigned(arg2));
}

void Particle_AddRotationRandomSignedY(ParticleEffectInstance* arg0, s32 arg1) {
    Particle_RotateY(arg0, ParticleMath_RandomSigned(arg1));
}

void Particle_AddRotationRandomSignedYWithHalfTurn(ParticleEffectInstance* arg0, s32 arg1) {
    Particle_RotateY(arg0, ParticleMath_RandomSignedOffset(arg1, 0x8000));
}

void Particle_AddRotationRandomSignedXWithFixedYQuarterTurn(ParticleEffectInstance* arg0) {
    Particle_RotateX(arg0, ParticleMath_RandomSigned(0x10000));
    Particle_RotateY(arg0, 0x4000);
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

void Particle_ComputeVectorFromRotationYAndRotationX(ParticleEffectInstance* arg0, f32 arg1, Vec3f* arg2) {
    arg2->x = arg1 * (SINS(arg0->unk_94.y) * COSS(arg0->unk_94.z) +
                      SINS(arg0->unk_94.x) * COSS(arg0->unk_94.y) * SINS(arg0->unk_94.z));
    arg2->y = arg1 * (SINS(arg0->unk_94.y) * SINS(arg0->unk_94.z) -
                      SINS(arg0->unk_94.x) * COSS(arg0->unk_94.y) * COSS(arg0->unk_94.z));
    arg2->z = arg1 * (COSS(arg0->unk_94.x) * COSS(arg0->unk_94.y));
}

void Particle_SetSpeed(ParticleEffectInstance* arg0, f32 arg1) {
    arg0->unk_74 = arg1 * gParticleRenderContext.posX.y;
}

void Particle_SetAcceleration(ParticleEffectInstance* arg0, f32 arg1) {
    arg0->unk_78 = arg1 * gParticleRenderContext.posX.y;
}

s32 Particle_ApproachSpeedScaled(ParticleEffectInstance* arg0, f32 arg1, f32 arg2) {
    return ParticleMath_ApproachFloat(&arg0->unk_74, arg1 * gParticleRenderContext.posX.y, arg2 * gParticleRenderContext.posX.y);
}

s32 Particle_ApproachSpeed(ParticleEffectInstance* arg0, f32 arg1) {
    return ParticleMath_ApproachFloat(&arg0->unk_74, arg1 * gParticleRenderContext.posX.y, arg0->unk_78);
}

s32 Particle_ApproachAcceleration(ParticleEffectInstance* arg0, f32 arg1, f32 arg2) {
    return ParticleMath_ApproachFloat(&arg0->unk_78, arg1 * gParticleRenderContext.posX.y, arg2 * gParticleRenderContext.posX.y);
}

void Particle_SetVelocityImpulseVec(ParticleEffectInstance* arg0, Vec3f arg1) {
    arg0->unk_7C.x = arg1.x * gParticleRenderContext.posX.y;
    arg0->unk_7C.y = arg1.y * gParticleRenderContext.posX.y;
    arg0->unk_7C.z = arg1.z * gParticleRenderContext.posX.y;
}

void Particle_SetVelocityImpulse(ParticleEffectInstance* arg0, f32 arg1, f32 arg2, f32 arg3) {
    arg0->unk_7C.x = arg1 * gParticleRenderContext.posX.y;
    arg0->unk_7C.y = arg2 * gParticleRenderContext.posX.y;
    arg0->unk_7C.z = arg3 * gParticleRenderContext.posX.y;
}

void Particle_SetVelocityImpulseX(ParticleEffectInstance* arg0, f32 arg1) {
    arg0->unk_7C.x = arg1 * gParticleRenderContext.posX.y;
}

void Particle_SetVelocityImpulseY(ParticleEffectInstance* arg0, f32 arg1) {
    arg0->unk_7C.y = arg1 * gParticleRenderContext.posX.y;
}

void Particle_SetVelocityImpulseZ(ParticleEffectInstance* arg0, f32 arg1) {
    arg0->unk_7C.z = arg1 * gParticleRenderContext.posX.y;
}

s32 Particle_IncrementVelocityImpulseXUntilAtLeast(ParticleEffectInstance* arg0, f32 arg1, f32 arg2) {
    f32 temp_fv0;
    s32 var_v1 = 0;

    arg0->unk_7C.x += arg2 * gParticleRenderContext.posX.y;

    temp_fv0 = arg1 * gParticleRenderContext.posX.y;
    if (temp_fv0 <= arg0->unk_7C.x) {
        arg0->unk_7C.x = temp_fv0;
        var_v1 = 1;
    }
    return var_v1;
}

s32 Particle_IncrementVelocityImpulseYUntilAtLeast(ParticleEffectInstance* arg0, f32 arg1, f32 arg2) {
    f32 temp_fv0;
    s32 var_v1 = 0;

    arg0->unk_7C.y += arg2 * gParticleRenderContext.posX.y;

    temp_fv0 = arg1 * gParticleRenderContext.posX.y;
    if (temp_fv0 <= arg0->unk_7C.y) {
        arg0->unk_7C.y = temp_fv0;
        var_v1 = 1;
    }
    return var_v1;
}

s32 Particle_IncrementVelocityImpulseZUntilAtLeast(ParticleEffectInstance* arg0, f32 arg1, f32 arg2) {
    f32 temp_fv0;
    s32 var_v1 = 0;

    arg0->unk_7C.z += arg2 * gParticleRenderContext.posX.y;

    temp_fv0 = arg1 * gParticleRenderContext.posX.y;
    if (temp_fv0 <= arg0->unk_7C.z) {
        arg0->unk_7C.z = temp_fv0;
        var_v1 = 1;
    }
    return var_v1;
}

s32 Particle_DecrementVelocityImpulseXUntilAtMost(ParticleEffectInstance* arg0, f32 arg1, f32 arg2) {
    f32 temp_fv0;
    s32 var_v1 = 0;

    arg0->unk_7C.x -= arg2 * gParticleRenderContext.posX.y;

    temp_fv0 = arg1 * gParticleRenderContext.posX.y;
    if (arg0->unk_7C.x <= temp_fv0) {
        arg0->unk_7C.x = temp_fv0;
        var_v1 = 1;
    }
    return var_v1;
}

s32 Particle_DecrementVelocityImpulseYUntilAtMost(ParticleEffectInstance* arg0, f32 arg1, f32 arg2) {
    s32 var_v1 = 0;
    f32 temp_fv0;

    arg0->unk_7C.y -= arg2 * gParticleRenderContext.posX.y;

    temp_fv0 = arg1 * gParticleRenderContext.posX.y;
    if (arg0->unk_7C.y <= temp_fv0) {
        arg0->unk_7C.y = temp_fv0;
        var_v1 = 1;
    }
    return var_v1;
}

s32 Particle_DecrementVelocityImpulseZUntilAtMost(ParticleEffectInstance* arg0, f32 arg1, f32 arg2) {
    f32 temp_fv0;
    s32 var_v1 = 0;

    arg0->unk_7C.z -= arg2 * gParticleRenderContext.posX.y;

    temp_fv0 = arg1 * gParticleRenderContext.posX.y;
    if (arg0->unk_7C.z <= temp_fv0) {
        arg0->unk_7C.z = temp_fv0;
        var_v1 = 1;
    }
    return var_v1;
}

void Particle_ScaleVelocityImpulse(ParticleEffectInstance* arg0, f32 arg1) {
    arg0->unk_7C.x *= arg1;
    arg0->unk_7C.y *= arg1;
    arg0->unk_7C.z *= arg1;
}

s32 Particle_ApproachVelocityImpulseY(ParticleEffectInstance* arg0, f32 arg1, f32 arg2) {
    return ParticleMath_ApproachFloat(&arg0->unk_7C.y, arg1 * gParticleRenderContext.posX.y, arg2 * gParticleRenderContext.posX.y);
}

void Particle_SetVelocityImpulseYFromRotationX(ParticleEffectInstance* arg0) {
    arg0->unk_7C.y = COSS(arg0->unk_94.x) * arg0->unk_74;
}

void Particle_SetVelocityImpulseXFromRotationY(ParticleEffectInstance* arg0) {
    arg0->unk_7C.x = SINS(arg0->unk_94.y) * arg0->unk_74;
}

void Particle_SetVelocityImpulseZFromRotationY(ParticleEffectInstance* arg0) {
    arg0->unk_7C.z = COSS(arg0->unk_94.y) * arg0->unk_74;
}

void Particle_SetVelocityImpulseXYFromRotationZ(ParticleEffectInstance* arg0) {
    arg0->unk_7C.x = COSS(arg0->unk_94.z) * arg0->unk_74;
    arg0->unk_7C.y = SINS(arg0->unk_94.z) * arg0->unk_74;
}

void Particle_SetVelocityImpulseXZFromRotationY(ParticleEffectInstance* arg0) {
    arg0->unk_7C.x = SINS(arg0->unk_94.y) * arg0->unk_74;
    arg0->unk_7C.z = COSS(arg0->unk_94.y) * arg0->unk_74;
}

void Particle_SetVelocityImpulseFromRotationXY(ParticleEffectInstance* arg0) {
    arg0->unk_7C.x = arg0->unk_74 * COSS(arg0->unk_94.x) * SINS(arg0->unk_94.y);
    arg0->unk_7C.y = -arg0->unk_74 * SINS(arg0->unk_94.x);
    arg0->unk_7C.z = arg0->unk_74 * COSS(arg0->unk_94.x) * COSS(arg0->unk_94.y);
}

void Particle_SetVelocityImpulseFromRotationXZ(ParticleEffectInstance* arg0) {
    arg0->unk_7C.x = arg0->unk_74 * SINS(arg0->unk_94.x) * SINS(arg0->unk_94.z);
    arg0->unk_7C.y = -arg0->unk_74 * SINS(arg0->unk_94.x) * COSS(arg0->unk_94.z);
    arg0->unk_7C.z = arg0->unk_74 * COSS(arg0->unk_94.x);
}

void Particle_SetVelocityImpulseFromRotationXYAlt(ParticleEffectInstance* arg0) {
    arg0->unk_7C.x = arg0->unk_74 * SINS(arg0->unk_94.y);
    arg0->unk_7C.y = -arg0->unk_74 * SINS(arg0->unk_94.x) * COSS(arg0->unk_94.y);
    arg0->unk_7C.z = arg0->unk_74 * COSS(arg0->unk_94.x) * COSS(arg0->unk_94.y);
}

void Particle_SetVelocityImpulseFromRotationYZ(ParticleEffectInstance* arg0) {
    arg0->unk_7C.x = arg0->unk_74 * SINS(arg0->unk_94.y) * COSS(arg0->unk_94.z);
    arg0->unk_7C.y = arg0->unk_74 * SINS(arg0->unk_94.y) * SINS(arg0->unk_94.z);
    arg0->unk_7C.z = COSS(arg0->unk_94.y);
}

void Particle_SetVelocityImpulseFromRotationXYZ(ParticleEffectInstance* arg0) {
    arg0->unk_7C.x = arg0->unk_74 * (COSS(arg0->unk_94.x) * SINS(arg0->unk_94.y) * COSS(arg0->unk_94.z) +
                                     SINS(arg0->unk_94.x) * SINS(arg0->unk_94.z));
    arg0->unk_7C.y = -arg0->unk_74 * (COSS(arg0->unk_94.x) * SINS(arg0->unk_94.y) * SINS(arg0->unk_94.z) -
                                      SINS(arg0->unk_94.x) * COSS(arg0->unk_94.z));
    arg0->unk_7C.z = arg0->unk_74 * (COSS(arg0->unk_94.x) * COSS(arg0->unk_94.y));
}

void Particle_SetVelocityImpulseFromRotationXYZAlt(ParticleEffectInstance* arg0) {
    arg0->unk_7C.x = arg0->unk_74 * (SINS(arg0->unk_94.x) * COSS(arg0->unk_94.y) * SINS(arg0->unk_94.z) +
                                     COSS(arg0->unk_94.x) * SINS(arg0->unk_94.y));
    arg0->unk_7C.y = -arg0->unk_74 * SINS(arg0->unk_94.x) * COSS(arg0->unk_94.z);

    arg0->unk_7C.z = arg0->unk_74 * (-SINS(arg0->unk_94.x) * SINS(arg0->unk_94.y) * SINS(arg0->unk_94.z) +
                                     COSS(arg0->unk_94.x) * COSS(arg0->unk_94.y));
}

void Particle_SetVelocityImpulseFromRotationYZAlt(ParticleEffectInstance* arg0) {
    arg0->unk_7C.x = arg0->unk_74 * SINS(arg0->unk_94.y) * COSS(arg0->unk_94.z);
    arg0->unk_7C.y = arg0->unk_74 * (COSS(arg0->unk_94.x) * SINS(arg0->unk_94.y) * SINS(arg0->unk_94.z) -
                                     SINS(arg0->unk_94.x) * COSS(arg0->unk_94.y));
    arg0->unk_7C.z = arg0->unk_74 * (SINS(arg0->unk_94.x) * SINS(arg0->unk_94.y) * SINS(arg0->unk_94.z) +
                                     COSS(arg0->unk_94.x) * COSS(arg0->unk_94.y));
}

void Particle_SetVelocityImpulseFromRotationYZFactored(ParticleEffectInstance* arg0) {
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

    arg0->unk_50.x = arg1 * gParticleRenderContext.posX.y * SINS(arg0->rotationDelta.y);
    arg0->unk_50.z = arg1 * gParticleRenderContext.posX.y * COSS(arg0->rotationDelta.y);

    arg0->unk_7C.x = arg0->unk_50.x - tmp1;
    arg0->unk_7C.z = arg0->unk_50.z - tmp2;
}

s32 Particle_AdvanceBallisticWithTimer(ParticleEffectInstance* arg0, f32 arg1, f32 arg2, f32 arg3, s16 arg4, s16 arg5) {
    s32 sp24 = 0;

    if (Particle_LacksFlags(arg0, 2) != 0) {
        Particle_SetFlags(arg0, 2);
        arg0->unk_50.x = arg0->unk_50.y = arg0->unk_50.z = 0.0f;
        arg0->unk_74 = arg3 * gParticleRenderContext.posX.y;
        arg0->unk_7C.y = arg1 * gParticleRenderContext.posX.y;
        arg0->unk_94.y = arg4;
        Particle_SetVelocityImpulseXZFromRotationY(arg0);
        arg0->durationTimer = arg5;
    }

    arg0->durationTimer--;
    if (arg0->durationTimer < 0) {
        sp24 = 1;
    } else {
        arg0->unk_7C.y -= arg2 * gParticleRenderContext.posX.y;
        Particle_AddVelocityFromTarget(arg0);
    }

    return sp24;
}

void Particle_SetScaleScaled(ParticleEffectInstance* arg0, f32 arg1) {
    arg0->unk_1C = arg1 * gParticleRenderContext.posX.y;
}

void Particle_SetScale(ParticleEffectInstance* arg0, f32 arg1) {
    arg0->unk_1C = arg1;
}

void Particle_SetScaleSpeed(ParticleEffectInstance* arg0, f32 arg1) {
    arg0->unk_20 = arg1 * gParticleRenderContext.posX.y;
}

void Particle_SetScaleTarget(ParticleEffectInstance* arg0, f32 arg1) {
    arg0->unk_24 = arg1 * gParticleRenderContext.posX.y;
}

s32 Particle_ApproachScaleScaled(ParticleEffectInstance* arg0, f32 arg1, f32 arg2) {
    return ParticleMath_ApproachFloat(&arg0->unk_1C, arg1 * gParticleRenderContext.posX.y, arg2 * gParticleRenderContext.posX.y);
}

s32 Particle_ApproachScaleFactor1WithCallback(ParticleEffectInstance* arg0, f32 arg1, f32 arg2) {
    s32 sp1C = Particle_ApproachScaleScaled(arg0, arg1, arg2);

    if (sp1C != 0) {
        Particle_AdvanceLifecycle(arg0);
    }
    return sp1C;
}

s32 Particle_ApproachScaleTarget(ParticleEffectInstance* arg0) {
    return ParticleMath_ApproachFloat(&arg0->unk_1C, arg0->unk_20, arg0->unk_24);
}

s32 Particle_ApproachScaleFactor2WithCallback(ParticleEffectInstance* arg0) {
    s32 sp1C = Particle_ApproachScaleTarget(arg0);

    if (sp1C != 0) {
        Particle_AdvanceLifecycle(arg0);
    }
    return sp1C;
}

s32 Particle_ApproachScaleSpeed(ParticleEffectInstance* arg0, f32 arg1, f32 arg2) {
    return ParticleMath_ApproachFloat(&arg0->unk_20, arg1 * gParticleRenderContext.posX.y, arg2 * gParticleRenderContext.posX.y);
}

void Particle_SetPrimColor(ParticleEffectInstance* arg0, u8 arg1, u8 arg2, u8 arg3) {
    arg0->prim_r = arg1;
    arg0->prim_g = arg2;
    arg0->prim_b = arg3;
}

s32 Particle_ApproachPrimR(ParticleEffectInstance* arg0, u8 arg1, u8 arg2) {
    return ParticleMath_ApproachU8(&arg0->prim_r, arg1, arg2);
}

s32 Particle_ApproachPrimG(ParticleEffectInstance* arg0, u8 arg1, u8 arg2) {
    return ParticleMath_ApproachU8(&arg0->prim_g, arg1, arg2);
}

s32 Particle_ApproachPrimB(ParticleEffectInstance* arg0, u8 arg1, u8 arg2) {
    return ParticleMath_ApproachU8(&arg0->prim_b, arg1, arg2);
}

void Particle_SetEnvColor(ParticleEffectInstance* arg0, u8 arg1, u8 arg2, u8 arg3) {
    arg0->env_r = arg1;
    arg0->env_g = arg2;
    arg0->env_b = arg3;
}

s32 Particle_ApproachEnvR(ParticleEffectInstance* arg0, u8 arg1, u8 arg2) {
    return ParticleMath_ApproachU8(&arg0->env_r, arg1, arg2);
}

s32 Particle_ApproachEnvB(ParticleEffectInstance* arg0, u8 arg1, u8 arg2) {
    return ParticleMath_ApproachU8(&arg0->env_b, arg1, arg2);
}

s32 Particle_ApproachEnvG(ParticleEffectInstance* arg0, u8 arg1, u8 arg2) {
    return ParticleMath_ApproachU8(&arg0->env_g, arg1, arg2);
}

void Particle_SetPrimAlpha(ParticleEffectInstance* arg0, u8 arg1) {
    arg0->prim_a = arg1;
}

s32 Particle_ApproachPrimAlpha(ParticleEffectInstance* arg0, u8 arg1, u8 arg2) {
    return ParticleMath_ApproachU8(&arg0->prim_a, arg1, arg2);
}

s32 Particle_ApproachPrimAlphaWithCallback(ParticleEffectInstance* arg0, u8 arg1, u8 arg2) {
    s32 sp1C = Particle_ApproachPrimAlpha(arg0, arg1, arg2);

    if (sp1C != 0) {
        Particle_AdvanceLifecycle(arg0);
    }
    return sp1C;
}

void Particle_SetTimerA6(ParticleEffectInstance* arg0, s16 arg1) {
    arg0->initialAlpha = arg1;
}

s16 Particle_GetTimerA6(ParticleEffectInstance* arg0) {
    return arg0->initialAlpha;
}

s32 Particle_DecrementTimerA6Clamp(ParticleEffectInstance* arg0, s16 arg1, s16 arg2) {
    s32 var_v1 = 0;

    arg0->initialAlpha -= arg2;
    if (arg1 >= arg0->initialAlpha) {
        arg0->initialAlpha = arg1;
        var_v1 = 1;
    }
    return var_v1;
}

s32 Particle_DecrementTimerA6By(ParticleEffectInstance* arg0, s16 arg1) {
    return Particle_DecrementTimerA6Clamp(arg0, 0, arg1);
}

s32 Particle_DecrementTimerA6ByWithCallback(ParticleEffectInstance* arg0, s16 arg1) {
    s32 sp1C = Particle_DecrementTimerA6Clamp(arg0, 0, arg1);

    if (sp1C != 0) {
        Particle_AdvanceLifecycle(arg0);
    }
    return sp1C;
}

s32 Particle_DecrementTimerA6To(ParticleEffectInstance* arg0, s16 arg1) {
    return Particle_DecrementTimerA6Clamp(arg0, arg1, 1);
}

s32 Particle_DecrementTimerA6ToZero(ParticleEffectInstance* arg0) {
    return Particle_DecrementTimerA6Clamp(arg0, 0, 1);
}

s32 Particle_DecrementTimerA6ToZeroWithCallback(ParticleEffectInstance* arg0) {
    s32 sp1C = Particle_DecrementTimerA6Clamp(arg0, 0, 1);

    if (sp1C != 0) {
        Particle_AdvanceLifecycle(arg0);
    }
    return sp1C;
}

void Particle_SetTimerA8(ParticleEffectInstance* arg0, s16 arg1) {
    arg0->unk_A8 = arg1;
}

s16 Particle_GetTimerA8(ParticleEffectInstance* arg0) {
    return arg0->unk_A8;
}

s32 Particle_DecrementTimerA8Clamp(ParticleEffectInstance* arg0, s16 arg1) {
    s32 var_v1 = 0;

    arg0->unk_A8--;
    if (arg1 >= arg0->unk_A8) {
        arg0->unk_A8 = arg1;
        var_v1 = 1;
    }
    return var_v1;
}

s32 Particle_DecrementTimerA8ToZero(ParticleEffectInstance* arg0) {
    return Particle_DecrementTimerA8Clamp(arg0, 0);
}

s32 Particle_DecrementTimerA8ToZeroWithCallback(ParticleEffectInstance* arg0) {
    s32 sp1C = Particle_DecrementTimerA8Clamp(arg0, 0);

    if (sp1C != 0) {
        Particle_AdvanceLifecycle(arg0);
    }
    return sp1C;
}

void Particle_SetEffectType(ParticleEffectInstance* arg0, u8 arg1) {
    arg0->effectType = arg1;
}

void Particle_SetFieldOffsetAC(ParticleEffectInstance* arg0, s16 arg1) {
    arg0->unk_AC = arg1;
}

void Particle_SetPaletteIndex(ParticleEffectInstance* arg0, u8 arg1) {
    arg0->paletteIndex = arg1;
}

void Particle_SetPaletteIndexAlt(ParticleEffectInstance* arg0, u8 arg1) {
    arg0->paletteIndex = arg1;
}

void Particle_SetAnchorMode(ParticleEffectInstance* arg0, u8 arg1) {
    arg0->unk_CC = arg1;
}

void Particle_SetAlphaStep(ParticleEffectInstance* arg0, s16 arg1) {
    arg0->alphaStep = arg1;
}

void Particle_SetMetadata(ParticleEffectInstance* arg0, s16 arg1) {
    arg0->metadata = arg1;
}

void Particle_SetTargetAlpha(ParticleEffectInstance* arg0, s16 arg1) {
    arg0->targetAlpha = arg1;
}

void Particle_SetAlpha(ParticleEffectInstance* arg0, s16 arg1) {
    arg0->alpha = arg1;
}

s32 Particle_ApproachAlpha(ParticleEffectInstance* arg0, s16 arg1, s16 arg2) {
    return ParticleMath_ApproachS16(&arg0->alpha, arg1, arg2);
}

s32 Particle_ApproachAlphaWithCallback(ParticleEffectInstance* arg0, s16 arg1, s16 arg2) {
    s32 sp1C = Particle_ApproachAlpha(arg0, arg1, arg2);

    if (sp1C != 0) {
        Particle_AdvanceLifecycle(arg0);
    }
    return sp1C;
}

void Particle_SetFieldB0(ParticleEffectInstance* arg0, s16 arg1) {
    arg0->unk_B0 = arg1;
}

s32 Particle_ApproachFieldB0(ParticleEffectInstance* arg0, s16 arg1, s16 arg2) {
    return ParticleMath_ApproachS16(&arg0->unk_B0, arg1, arg2);
}

s16 Particle_GetFieldOffsetAC(ParticleEffectInstance* arg0) {
    return arg0->unk_AC;
}

s32 Particle_GetMetadata(ParticleEffectInstance* arg0) {
    return arg0->metadata;
}

u8 Particle_GetTargetAlpha(ParticleEffectInstance* arg0) {
    return arg0->targetAlpha;
}

s16 Particle_GetAlpha(ParticleEffectInstance* arg0) {
    return arg0->alpha;
}

s16 Particle_GetPaletteIndex(ParticleEffectInstance* arg0) {
    s32 tmp = arg0->paletteIndex;
    return tmp;
}

s16 Particle_GetAlphaStep(ParticleEffectInstance* arg0) {
    return arg0->alphaStep;
}

void Particle_SetFieldOffsetACIfNotSentinel(ParticleEffectInstance* arg0, s16 arg1) {
    if ((u32)arg0 != -1) {
        Particle_SetFieldOffsetAC(arg0, arg1);
    }
}

void Particle_SetFieldOffsetCFIfNotSentinel(ParticleEffectInstance* arg0, u8 arg1) {
    if ((u32)arg0 != -1) {
        Particle_SetPaletteIndex(arg0, arg1);
    }
}

void Particle_SetFieldOffsetA6IfNotSentinel(ParticleEffectInstance* arg0, s16 arg1) {
    if ((u32)arg0 != -1) {
        Particle_SetTimerA6(arg0, arg1);
    }
}

void Particle_SetFieldOffsetA8IfNotSentinel(ParticleEffectInstance* arg0, s16 arg1) {
    if ((u32)arg0 != -1) {
        Particle_SetTimerA8(arg0, arg1);
    }
}

void Particle_SetFieldOffsetCEIfNotSentinel(ParticleEffectInstance* arg0, u8 arg1) {
    if ((u32)arg0 != -1) {
        arg0->metadata = arg1;
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
            gSPDisplayList(gDisplayListHead++, gDL_UI_ModulateBilerpXlu);
            break;

        case 1:
            gSPDisplayList(gDisplayListHead++, gDL_BaseUI);
            break;

        case 3:
            gSPDisplayList(gDisplayListHead++, gDL_UI_DecalBilerpTexEdge);
            break;
    }
}

void Particle_InvokeRenderSetup(ParticleEffectInstance* arg0, ParticleRenderSettings* arg1) {
    switch (arg1->TrainerSlotSaveData_GamePort) {
        case 0:
            arg1->rotation(arg0, arg1->unk_0C.arg, arg1);
            break;

        case 1:
            arg1->rotation(arg0, arg1->unk_0C.s->arg, arg1);
            break;
    }
}

void Particle_PrepareRender(ParticleEffectInstance* arg0) {
    UNUSED s32 pad;
    ParticleRenderSettings* sp18 = arg0->unk_0C->rotation.a;

    if (arg0->unk_0C->posX == 1) {
        Particle_SetRenderMode(sp18->posY);
        if (sp18->posX == 1) {
            Particle_InvokeRenderSetup(arg0, sp18);
        }
    }
}

void Particle_DispatchDraw(ParticleEffectInstance* arg0, CameraStruct* arg1) {
    UNUSED s32 pad;
    ParticleRenderSettings* sp18 = arg0->unk_0C->rotation.a;

    switch (arg0->unk_0C->posX) {
        case 1:
            if (sp18->posX == 0) {
                Particle_InvokeRenderSetup(arg0, sp18);
            }
            sp18->RentalSlotAnimData_PosePhase(arg0, arg1, sp18);
            break;

        case 3:
            arg0->unk_0C->rotation.func(arg0, arg1);
            break;
    }
}

void Particle_NoopDraw(UNUSED ParticleEffectInstance* arg0, UNUSED CameraStruct* arg1) {
}
