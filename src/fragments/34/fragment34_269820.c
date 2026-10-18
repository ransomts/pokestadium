#include "fragment34.h"
#include "src/12D80.h"

unk_D_8140E728_01C gParticleDefaultCallback = { 3, Particle_NoOp };

void Particle_ResetDefaults(ParticleEffectInstance* arg0) {
    Particle_Init(arg0);
    Particle_SetVelocityScaledXYZ(arg0, 0.0f, 0.0f, 0.0f);
    Particle_SetPosition(arg0, 0.0f, 0.0f, 0.0f);
    Particle_SetVelocityScaled(arg0, 0.0f, 0.0f, 0.0f);
    Particle_SetAccelerationScaled(arg0, 0.0f, 0.0f, 0.0f);
    Particle_SetAccelerationXYZ(arg0, 0.0f, 0.0f, 0.0f);
    Particle_SetSpeed(arg0, 0.0f);
    Particle_SetAcceleration(arg0, 0.0f);
    Particle_SetRotation(arg0, 0, 0, 0);
    Particle_SetRotationDelta(arg0, 0, 0, 0);
    Particle_SetParamC7(arg0, 0);
    Particle_SetTimerA6(arg0, 0);
    Particle_SetTimerA8(arg0, 0);
    Particle_SetByteCD(arg0, 0);
    Particle_SetShortCE(arg0, 0);
    Particle_SetShortAA(arg0, 0);
    Particle_SetShortAC(arg0, 0);
    Particle_SetByteCF(arg0, 0);
    Particle_SetPrimColor(arg0, 0xFF, 0xFF, 0xFF);
    Particle_SetEnvColor(arg0, 0xFF, 0xFF, 0xFF);
    Particle_SetPrimAlpha(arg0, 0xFF);

    arg0->unk_1C = 1.0f;
    arg0->unk_28 = 1.0f;
}

ParticleEffectInstance* Particle_Allocate(void) {
    s32 i;
    s32 var_v0 = gParticleAllocIndex;
    ParticleEffectInstance* var_a0 = &gParticleInstances[var_v0];

    for (i = 0; i < 0x12C; i++) {
        if (var_a0->unk_D0 == 0) {
            break;
        }

        var_v0++;
        if (var_v0 >= 0x12C) {
            var_v0 = 0;
            var_a0 = &gParticleInstances[0];
        } else {
            var_a0++;
        }
    }

    if (i >= 0x12C) {
        var_a0 = (ParticleEffectInstance*)-1;
    } else {
        var_a0->unk_D0 = 1;

        Particle_ResetDefaults(var_a0);

        gParticleAllocIndex = var_v0 + 1;
        if (gParticleAllocIndex >= 0x12C) {
            gParticleAllocIndex = 0;
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

ParticleEffectInstance* Particle_AllocateInstance(void) {
    return Particle_Allocate();
}

ParticleEffectInstance* Particle_AllocateChain(u8 arg0) {
    s32 i;
    ParticleEffectInstance* sp28;
    ParticleEffectInstance* temp_v0;
    ParticleEffectInstance* var_s0;

    sp28 = Particle_Allocate();

    if ((u32)sp28 != -1) {
        var_s0 = sp28;
        arg0--;

        for (i = 0; i < arg0; i++) {
            temp_v0 = Particle_Allocate();
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

ParticleEffectInstance* Particle_Create(f32 arg0, Vec3f arg1, Vec3s arg2, func_unk_D_8140E724_008 arg3, unk_D_8140E728_01C* arg4,
                              s16 arg5, s16 arg6, s16 arg7) {
    ParticleEffectInstance* sp1C = Particle_AllocateInstance();

    if ((u32)sp1C != -1) {
        sp1C->unk_28 = arg0;

        Vec3f_Copy(&sp1C->unk_68, &arg1);
        func_8140094C(&sp1C->unk_94, &arg2);

        sp1C->unk_08 = arg3;
        sp1C->unk_0C = arg4;
        sp1C->unk_10 = 0;
        sp1C->unk_14 = 0;
        sp1C->unk_AC = arg5;
        sp1C->unk_CE = arg7;
        sp1C->unk_CD = arg6;
    }
    return sp1C;
}

ParticleEffectInstance* Particle_CreateFromEntity(Fragment2_1GraphNode* arg0, func_unk_D_8140E724_008 arg1, unk_D_8140E728_01C* arg2,
                              s16 arg3, s16 arg4, s16 arg5) {
    ParticleEffectInstance* sp1C = Particle_AllocateInstance();

    if ((u32)sp1C != -1) {
        if (arg4 == 0xFF) {
            sp1C->unk_38.x = arg0->unk_024.x;
            sp1C->unk_38.y = arg0->unk_024.y;
            sp1C->unk_38.z = arg0->unk_024.z;
        } else {
            func_80015390(arg0, arg4, &sp1C->unk_38);
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
        sp1C->unk_CD = arg4;
    }
    return sp1C;
}

void Particle_CreateMultiple(f32 arg0, Vec3f arg1, Vec3s arg2, func_unk_D_8140E724_008 arg3, unk_D_8140E728_01C* arg4, s16 arg5) {
    s32 i;

    for (i = 0; i < arg5; i++) {
        if ((u32)Particle_Create(arg0, arg1, arg2, arg3, arg4, i, 0xFF, NULL) == -1) {
            break;
        }
    }
}

void Particle_CreateMultipleWithExtra(f32 arg0, Vec3f arg1, Vec3s arg2, func_unk_D_8140E724_008 arg3, unk_D_8140E728_01C* arg4, s16 arg5,
                   s16 arg6) {
    s32 i;

    for (i = 0; i < arg5; i++) {
        if ((u32)Particle_Create(arg0, arg1, arg2, arg3, arg4, i, 0xFF, arg6) == -1) {
            break;
        }
    }
}

void Particle_CreateFromEntityMultiple(Fragment2_1GraphNode* arg0, func_unk_D_8140E724_008 arg1, unk_D_8140E728_01C* arg2, s16 arg3,
                   s16 arg4) {
    s32 i;

    for (i = 0; i < arg3; i++) {
        if ((u32)Particle_CreateFromEntity(arg0, arg1, arg2, i, arg4, 0) == -1) {
            break;
        }
    }
}

void Particle_CreateFromEntityMultipleWithExtra(Fragment2_1GraphNode* arg0, func_unk_D_8140E724_008 arg1, unk_D_8140E728_01C* arg2, s16 arg3,
                   s16 arg4, s16 arg5) {
    s32 i;

    for (i = 0; i < arg3; i++) {
        if ((u32)Particle_CreateFromEntity(arg0, arg1, arg2, i, arg4, arg5) == -1) {
            break;
        }
    }
}

s32 Particle_CountActive(void) {
    s32 i;
    s32 var_v1 = 0;
    ParticleEffectInstance* ptr = gParticleInstances;

    for (i = 0; i < 0x12C; i++, ptr++) {
        if (ptr->unk_D0 != 0) {
            var_v1++;
        }
    }

    return var_v1;
}

s32 Particle_GetActiveCount(void) {
    return Particle_CountActive();
}

void Particle_Init(ParticleEffectInstance* arg0) {
    arg0->unk_B2 = 1;
    arg0->unk_0C = &gParticleDefaultCallback;
    arg0->unk_08 = NULL;
    arg0->unk_10 = 0;
    arg0->unk_14 = 0;
    arg0->unk_B8 = 0;
    Particle_SetFlag(arg0, 4);
}

void Particle_ClearActiveFlag(ParticleEffectInstance* arg0) {
    arg0->unk_B2 = 0;
}

void Particle_ResetState(ParticleEffectInstance* arg0) {
    arg0->unk_B2 = 0;

    arg0->unk_08 = NULL;
    arg0->unk_0C = NULL;

    Particle_DisableFlag2(arg0);
}

s32 Particle_IsInactive(ParticleEffectInstance* arg0) {
    s32 var_v1 = 0;

    if (arg0->unk_B2 == 0) {
        var_v1 = 1;
    }
    return var_v1;
}

s32 Particle_IsActive(ParticleEffectInstance* arg0) {
    s32 var_v1 = 0;

    if (arg0->unk_B2 >= 2) {
        var_v1 = 1;
    }
    return var_v1;
}

void Particle_IncrementState(ParticleEffectInstance* arg0) {
    Particle_ClearFlag(arg0, 1);
    arg0->unk_B2++;
}

s32 Particle_StartTimer80(ParticleEffectInstance* arg0, s16 arg1) {
    s32 sp1C = 0;

    if (Particle_CanSetFlag(arg0, 0x80) != 0) {
        Particle_SetFlag(arg0, 0x80);
        arg0->unk_BC = arg1;
    }

    arg0->unk_BC--;
    if (arg0->unk_BC <= 0) {
        arg0->unk_BC = 0;
        Particle_ClearFlag(arg0, 0x80);
        sp1C = 1;
    }

    return sp1C;
}

s32 Particle_ProcessTimer80(ParticleEffectInstance* arg0, s16 arg1) {
    s32 sp1C = Particle_StartTimer80(arg0, arg1);

    if (sp1C != 0) {
        Particle_IncrementState(arg0);
    }
    return sp1C;
}

void Particle_SetFlag(ParticleEffectInstance* arg0, s32 arg1) {
    arg0->unk_18 |= arg1;
}

void Particle_ClearFlag(ParticleEffectInstance* arg0, s32 arg1) {
    arg0->unk_18 &= ~arg1;
}

void Particle_ToggleFlag(ParticleEffectInstance* arg0, s32 arg1) {
    arg0->unk_18 ^= arg1;
}

s32 Particle_HasFlag(ParticleEffectInstance* arg0, s32 arg1) {
    s32 var_v1 = 0;

    if (arg0->unk_18 & arg1) {
        var_v1 = 1;
    }
    return var_v1;
}

s32 Particle_CanSetFlag(ParticleEffectInstance* arg0, s32 arg1) {
    s32 var_v1 = 0;

    if (!(arg0->unk_18 & arg1)) {
        var_v1 = 1;
    }
    return var_v1;
}

void Particle_EnableFlag4(ParticleEffectInstance* arg0) {
    Particle_SetFlag(arg0, 4);
}

void Particle_DisableFlag4(ParticleEffectInstance* arg0) {
    Particle_ClearFlag(arg0, 4);
}

s32 Particle_HasFlag4(ParticleEffectInstance* arg0) {
    return Particle_HasFlag(arg0, 4);
}

void Particle_EnableFlag40(ParticleEffectInstance* arg0) {
    Particle_SetFlag(arg0, 0x40);
}

void Particle_DisableFlag40(ParticleEffectInstance* arg0) {
    Particle_ClearFlag(arg0, 0x40);
}

void Particle_HasFlag40(ParticleEffectInstance* arg0) {
    Particle_HasFlag(arg0, 0x40);
}

void Particle_SetParamC7(ParticleEffectInstance* arg0, s16 arg1) {
    arg0->unk_C7 = arg1;
}

s32 Particle_AnimLoopForward(ParticleEffectInstance* arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5) {
    s32 sp1C = 0;

    if (Particle_CanSetFlag(arg0, 1) != 0) {
        arg0->unk_B6 = arg4;
        arg0->unk_C7 = arg1;
        arg0->unk_C6 = arg5;
        Particle_SetFlag(arg0, 1);
    } else {
        arg0->unk_B6--;
        if (arg0->unk_B6 <= 0) {
            arg0->unk_B6 = arg4;

            arg0->unk_C7 += arg3;
            if (arg2 < arg0->unk_C7) {
                if (arg0->unk_C6 > 0) {
                    arg0->unk_C6--;
                }

                if (arg0->unk_C6 == 0) {
                    arg0->unk_C7 = arg2;
                    sp1C = 1;
                } else {
                    arg0->unk_C7 = arg1;
                }
            }
        }
    }
    return sp1C;
}

s32 Particle_AnimLoopForwardComplete(ParticleEffectInstance* arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5) {
    s32 sp24 = Particle_AnimLoopForward(arg0, arg1, arg2, arg3, arg4, arg5);

    if (sp24 != 0) {
        Particle_IncrementState(arg0);
    }

    return sp24;
}

s32 Particle_AnimLoopBackward(ParticleEffectInstance* arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5) {
    s32 sp1C = 0;

    if (Particle_CanSetFlag(arg0, 1) != 0) {
        arg0->unk_B6 = arg4;
        arg0->unk_C7 = arg1;
        arg0->unk_C6 = arg5;
        Particle_SetFlag(arg0, 1);
    } else {
        arg0->unk_B6--;
        if (arg0->unk_B6 <= 0) {
            arg0->unk_B6 = arg4;

            arg0->unk_C7 -= arg3;
            if (arg0->unk_C7 < arg2) {
                if (arg0->unk_C6 > 0) {
                    arg0->unk_C6--;
                }

                if (arg0->unk_C6 == 0) {
                    arg0->unk_C7 = arg2;
                    sp1C = 1;
                } else {
                    arg0->unk_C7 = arg1;
                }
            }
        }
    }

    return sp1C;
}

s32 Particle_AnimLoopBackwardComplete(ParticleEffectInstance* arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5) {
    s32 sp24 = Particle_AnimLoopBackward(arg0, arg1, arg2, arg3, arg4, arg5);

    if (sp24 != 0) {
        Particle_IncrementState(arg0);
    }
    return sp24;
}

s32 Particle_AnimPingPong(ParticleEffectInstance* arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5) {
    s32 sp24 = 0;

    if (Particle_CanSetFlag(arg0, 1) != 0) {
        arg0->unk_B6 = arg4;
        arg0->unk_C7 = arg1;
        arg0->unk_C6 = arg5;
        Particle_SetFlag(arg0, 1);
        Particle_ClearFlag(arg0, 0x10);
    } else {
        arg0->unk_B6--;
        if (arg0->unk_B6 <= 0) {
            arg0->unk_B6 = arg4;

            if (Particle_CanSetFlag(arg0, 0x10) != 0) {
                arg0->unk_C7 += arg3;
                if (arg0->unk_C7 >= arg2) {
                    arg0->unk_C7 = arg2;
                    Particle_SetFlag(arg0, 0x10);
                }
            } else {
                arg0->unk_C7 -= arg3;
                if (arg1 >= arg0->unk_C7) {
                    arg0->unk_C7 = arg1;
                    if (arg0->unk_C6 > 0) {
                        arg0->unk_C6--;
                    }

                    if (arg0->unk_C6 == 0) {
                        Particle_ClearFlag(arg0, 0x20);
                        Particle_ClearFlag(arg0, 1);
                        sp24 = 1;
                    } else {
                        Particle_ClearFlag(arg0, 0x10);
                        Particle_SetFlag(arg0, 0x20);
                    }
                }
            }
        }
    }

    return sp24;
}

s32 Particle_AnimPingPongComplete(ParticleEffectInstance* arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5) {
    s32 sp24 = Particle_AnimPingPong(arg0, arg1, arg2, arg3, arg4, arg5);

    if (sp24 != 0) {
        Particle_IncrementState(arg0);
    }
    return sp24;
}

s32 Particle_AnimReversePingPong(ParticleEffectInstance* arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5) {
    s32 sp24 = 0;

    if (Particle_CanSetFlag(arg0, 1) != 0) {
        arg0->unk_B6 = arg4;
        arg0->unk_C7 = arg1;
        arg0->unk_C6 = arg5;
        Particle_SetFlag(arg0, 1);
        Particle_ClearFlag(arg0, 0x10);
    } else {
        arg0->unk_B6--;
        if (arg0->unk_B6 <= 0) {
            arg0->unk_B6 = arg4;
            if (Particle_CanSetFlag(arg0, 0x10) != 0) {
                arg0->unk_C7 -= arg3;
                if (arg2 >= arg0->unk_C7) {
                    arg0->unk_C7 = arg2;
                    Particle_SetFlag(arg0, 0x10);
                }
            } else {
                arg0->unk_C7 += arg3;
                if (arg0->unk_C7 >= arg1) {
                    arg0->unk_C7 = arg1;
                    if (arg0->unk_C6 > 0) {
                        arg0->unk_C6--;
                    }

                    if (arg0->unk_C6 == 0) {
                        Particle_ClearFlag(arg0, 1);
                        sp24 = 1;
                    } else {
                        Particle_ClearFlag(arg0, 0x10);
                    }
                }
            }
        }
    }
    return sp24;
}

s32 Particle_AnimReversePingPongComplete(ParticleEffectInstance* arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5) {
    s32 sp24 = Particle_AnimReversePingPong(arg0, arg1, arg2, arg3, arg4, arg5);

    if (sp24 != 0) {
        Particle_IncrementState(arg0);
    }
    return sp24;
}

void Particle_EnableFlag2(ParticleEffectInstance* arg0) {
    arg0->unk_B8 = 1;
    Particle_ClearFlag(arg0, 2);
}

void Particle_DisableFlag2(ParticleEffectInstance* arg0) {
    arg0->unk_B8 = 0;
    Particle_ClearFlag(arg0, 2);
}

void Particle_IncrementFlag2Counter(ParticleEffectInstance* arg0) {
    arg0->unk_B8++;
}

s32 Particle_StartTimer2(ParticleEffectInstance* arg0, s16 arg1) {
    s32 sp1C = 0;

    if (Particle_CanSetFlag(arg0, 2) != 0) {
        Particle_SetFlag(arg0, 2);
        arg0->unk_BA = arg1;
    }

    arg0->unk_BA--;
    if (arg0->unk_BA < 0) {
        Particle_ClearFlag(arg0, 2);
        sp1C = 1;
    }
    return sp1C;
}

void Particle_UpdateTransform(ParticleEffectInstance* arg0) {
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

        if (Particle_CanSetFlag(arg0, 0x200) != 0) {
            arg0->unk_14->unk_01E.x = arg0->unk_94.x;
            arg0->unk_14->unk_01E.y = arg0->unk_94.y;
            arg0->unk_14->unk_01E.z = arg0->unk_94.z;
        }
        arg0->unk_14->unk_01D = arg0->prim_a;
    }
}

void Particle_SetVelocityScaledXYZ(ParticleEffectInstance* arg0, f32 arg1, f32 arg2, f32 arg3) {
    arg0->unk_38.x = arg1 * gParticleScaleFactor.unk_00.y;
    arg0->unk_38.y = arg2 * gParticleScaleFactor.unk_00.y;
    arg0->unk_38.z = arg3 * gParticleScaleFactor.unk_00.y;
}

void Particle_SetVelocityScaledVec(ParticleEffectInstance* arg0, Vec3f arg1) {
    arg0->unk_38.x = arg1.x * gParticleScaleFactor.unk_00.y;
    arg0->unk_38.y = arg1.y * gParticleScaleFactor.unk_00.y;
    arg0->unk_38.z = arg1.z * gParticleScaleFactor.unk_00.y;
}

void Particle_SetVelocityDirectXYZ(ParticleEffectInstance* arg0, f32 arg1, f32 arg2, f32 arg3) {
    arg0->unk_38.x = arg1;
    arg0->unk_38.y = arg2;
    arg0->unk_38.z = arg3;
}

void Particle_SetVelocityXScaled(ParticleEffectInstance* arg0, f32 arg1) {
    arg0->unk_38.x = arg1 * gParticleScaleFactor.unk_00.y;
}

void Particle_SetVelocityYScaled(ParticleEffectInstance* arg0, f32 arg1) {
    arg0->unk_38.y = arg1 * gParticleScaleFactor.unk_00.y;
}

void Particle_SetVelocityZScaled(ParticleEffectInstance* arg0, f32 arg1) {
    arg0->unk_38.z = arg1 * gParticleScaleFactor.unk_00.y;
}

void Particle_SetVelocityFromComplexDir(ParticleEffectInstance* arg0, f32 arg1) {
    Vec3f sp1C;

    Particle_CalcComplexDirection(arg0, arg1, &sp1C);
    Particle_SetVelocityScaledVec(arg0, sp1C);
}

void Particle_SetVelocityFromAnotherDir(ParticleEffectInstance* arg0, f32 arg1) {
    Vec3f sp1C;

    Particle_CalcAnotherDirection(arg0, arg1, &sp1C);
    Particle_SetVelocityScaledVec(arg0, sp1C);
}

void Particle_AddVelocityScaledVec(ParticleEffectInstance* arg0, Vec3f arg1) {
    arg0->unk_38.x += arg1.x * gParticleScaleFactor.unk_00.y;
    arg0->unk_38.y += arg1.y * gParticleScaleFactor.unk_00.y;
    arg0->unk_38.z += arg1.z * gParticleScaleFactor.unk_00.y;
}

void Particle_AddVelocityDirectVec(ParticleEffectInstance* arg0, Vec3f arg1) {
    arg0->unk_38.x += arg1.x;
    arg0->unk_38.y += arg1.y;
    arg0->unk_38.z += arg1.z;
}

void Particle_AddVelocityScaledXYZ(ParticleEffectInstance* arg0, f32 arg1, f32 arg2, f32 arg3) {
    arg0->unk_38.x += arg1 * gParticleScaleFactor.unk_00.y;
    arg0->unk_38.y += arg2 * gParticleScaleFactor.unk_00.y;
    arg0->unk_38.z += arg3 * gParticleScaleFactor.unk_00.y;
}

void Particle_AddVelocityXScaled(ParticleEffectInstance* arg0, f32 arg1) {
    arg0->unk_38.x += arg1 * gParticleScaleFactor.unk_00.y;
}

void Particle_AddVelocityYScaled(ParticleEffectInstance* arg0, f32 arg1) {
    arg0->unk_38.y += arg1 * gParticleScaleFactor.unk_00.y;
}

void Particle_AddVelocityZScaled(ParticleEffectInstance* arg0, f32 arg1) {
    arg0->unk_38.z += arg1 * gParticleScaleFactor.unk_00.y;
}

void Particle_AddVelocityForward(ParticleEffectInstance* arg0, f32 arg1) {
    arg0->unk_38.x += arg1 * SINS(arg0->unk_94.y) * gParticleScaleFactor.unk_00.y;
    arg0->unk_38.z += arg1 * COSS(arg0->unk_94.y) * gParticleScaleFactor.unk_00.y;
}

void Particle_AddVelocityBackward(ParticleEffectInstance* arg0, f32 arg1) {
    arg0->unk_38.x += arg1 * SINS(arg0->unk_94.y + 0x8000) * gParticleScaleFactor.unk_00.y;
    arg0->unk_38.z += arg1 * COSS(arg0->unk_94.y + 0x8000) * gParticleScaleFactor.unk_00.y;
}

void Particle_AddVelocityRight(ParticleEffectInstance* arg0, f32 arg1) {
    arg0->unk_38.x += arg1 * SINS(arg0->unk_94.y + 0x4000) * gParticleScaleFactor.unk_00.y;
    arg0->unk_38.z += arg1 * COSS(arg0->unk_94.y + 0x4000) * gParticleScaleFactor.unk_00.y;
}

void Particle_AddVelocityLeft(ParticleEffectInstance* arg0, f32 arg1) {
    arg0->unk_38.x += arg1 * SINS(arg0->unk_94.y - 0x4000) * gParticleScaleFactor.unk_00.y;
    arg0->unk_38.z += arg1 * COSS(arg0->unk_94.y - 0x4000) * gParticleScaleFactor.unk_00.y;
}

void Particle_AddVelocityFromDirVector(ParticleEffectInstance* arg0, f32 arg1) {
    Vec3f sp1C;

    Particle_CalcDirectionVector(arg0, arg1, &sp1C);
    arg0->unk_38.x += sp1C.x * gParticleScaleFactor.unk_00.y;
    arg0->unk_38.y += sp1C.y * gParticleScaleFactor.unk_00.y;
    arg0->unk_38.z += sp1C.z * gParticleScaleFactor.unk_00.y;
}

void Particle_AddComplexDirection(ParticleEffectInstance* arg0, f32 arg1) {
    Vec3f sp1C;

    Particle_CalcComplexDirection(arg0, arg1, &sp1C);
    Particle_AddVelocityScaledVec(arg0, sp1C);
}

void Particle_AddAnotherDirection(ParticleEffectInstance* arg0, f32 arg1) {
    Vec3f sp1C;

    Particle_CalcAnotherDirection(arg0, arg1, &sp1C);
    Particle_AddVelocityScaledVec(arg0, sp1C);
}

void Particle_AddRotatedOffset(ParticleEffectInstance* arg0, Vec3f arg1) {
    Vec3f sp24;

    func_81400D00(&sp24, arg1, arg0->unk_94);
    Particle_AddVelocityScaledVec(arg0, sp24);
}

void Particle_SetRandomVelocityX(ParticleEffectInstance* arg0, s32 arg1) {
    arg0->unk_38.x = RandomRangeSigned(arg1) * gParticleScaleFactor.unk_00.y;
}

void Particle_SetRandomVelocityY(ParticleEffectInstance* arg0, s32 arg1) {
    arg0->unk_38.y = RandomRangeSigned(arg1) * gParticleScaleFactor.unk_00.y;
}

void Particle_SetRandomVelocityZ(ParticleEffectInstance* arg0, s32 arg1) {
    arg0->unk_38.z = RandomRangeSigned(arg1) * gParticleScaleFactor.unk_00.y;
}

void Particle_SetRandomVelocityXOffset(ParticleEffectInstance* arg0, s32 arg1, s32 arg2) {
    arg0->unk_38.x = (RandomRangeSigned(arg1) * gParticleScaleFactor.unk_00.y) + arg2;
}

void Particle_SetRandomVelocityYOffset(ParticleEffectInstance* arg0, s32 arg1, s32 arg2) {
    arg0->unk_38.y = (RandomRangeSigned(arg1) * gParticleScaleFactor.unk_00.y) + arg2;
}

void Particle_SetRandomVelocityZOffset(ParticleEffectInstance* arg0, s32 arg1, s32 arg2) {
    arg0->unk_38.z = (RandomRangeSigned(arg1) * gParticleScaleFactor.unk_00.y) + arg2;
}

void Particle_SetRandomVelocityXSymmetric(ParticleEffectInstance* arg0, s32 arg1, s32 arg2) {
    f32 temp_fv0 = RandomRangeSigned(arg1);

    if (temp_fv0 >= 0.0f) {
        arg0->unk_38.x = (temp_fv0 + arg2) * gParticleScaleFactor.unk_00.y;
    } else {
        arg0->unk_38.x = (temp_fv0 - arg2) * gParticleScaleFactor.unk_00.y;
    }
}

void Particle_SetRandomVelocityYSymmetric(ParticleEffectInstance* arg0, s32 arg1, s32 arg2) {
    f32 temp_fv0 = RandomRangeSigned(arg1);

    if (temp_fv0 >= 0.0f) {
        arg0->unk_38.y = (temp_fv0 + arg2) * gParticleScaleFactor.unk_00.y;
    } else {
        arg0->unk_38.y = (temp_fv0 - arg2) * gParticleScaleFactor.unk_00.y;
    }
}

void Particle_SetRandomVelocityZSymmetric(ParticleEffectInstance* arg0, s32 arg1, s32 arg2) {
    f32 temp_fv0 = RandomRangeSigned(arg1);

    if (temp_fv0 >= 0.0f) {
        arg0->unk_38.z = (temp_fv0 + arg2) * gParticleScaleFactor.unk_00.y;
    } else {
        arg0->unk_38.z = (temp_fv0 - arg2) * gParticleScaleFactor.unk_00.y;
    }
}

void Particle_SetRandomVelocityXYZ(ParticleEffectInstance* arg0, s32 arg1, s32 arg2, s32 arg3) {
    Vec3f sp18;

    sp18.x = RandomRangeSigned(arg1);
    sp18.y = RandomRangeSigned(arg2);
    sp18.z = RandomRangeSigned(arg3);

    arg0->unk_38.x = sp18.x * gParticleScaleFactor.unk_00.y;
    arg0->unk_38.y = sp18.y * gParticleScaleFactor.unk_00.y;
    arg0->unk_38.z = sp18.z * gParticleScaleFactor.unk_00.y;
}

void Particle_SetRandomModVelocityXYZ(ParticleEffectInstance* arg0, s32 arg1, s32 arg2, s32 arg3) {
    Vec3f sp1C;

    sp1C.x = RandomMod(arg1);
    sp1C.y = RandomMod(arg2);
    sp1C.z = RandomMod(arg3);

    arg0->unk_38.x = sp1C.x * gParticleScaleFactor.unk_00.y;
    arg0->unk_38.y = sp1C.y * gParticleScaleFactor.unk_00.y;
    arg0->unk_38.z = sp1C.z * gParticleScaleFactor.unk_00.y;
}

void Particle_SetRandomRotatedVelocityXY(ParticleEffectInstance* arg0, s32 arg1, s32 arg2) {
    Vec3f sp2C;
    Vec3f sp20;

    sp2C.x = RandomRangeSigned(arg1);
    sp2C.y = RandomRangeSigned(arg2);
    sp2C.z = 0.0f;

    func_81400D00(&sp20, sp2C, arg0->unk_94);

    arg0->unk_38.x = sp20.x * gParticleScaleFactor.unk_00.y;
    arg0->unk_38.y = sp20.y * gParticleScaleFactor.unk_00.y;
    arg0->unk_38.z = sp20.z * gParticleScaleFactor.unk_00.y;
}

void Particle_AddRandomVelocityXYZ(ParticleEffectInstance* arg0, s32 arg1, s32 arg2, s32 arg3) {
    Vec3f sp24;

    sp24.x = RandomRangeSigned(arg1);
    sp24.y = RandomRangeSigned(arg2);
    sp24.z = RandomRangeSigned(arg3);

    arg0->unk_38.x += sp24.x * gParticleScaleFactor.unk_00.y;
    arg0->unk_38.y += sp24.y * gParticleScaleFactor.unk_00.y;
    arg0->unk_38.z += sp24.z * gParticleScaleFactor.unk_00.y;
}

void Particle_SetPosition(ParticleEffectInstance* arg0, f32 arg1, f32 arg2, f32 arg3) {
    arg0->unk_68.x = arg1;
    arg0->unk_68.y = arg2;
    arg0->unk_68.z = arg3;
}

void Particle_SetVelocityScaled(ParticleEffectInstance* arg0, f32 arg1, f32 arg2, f32 arg3) {
    arg0->unk_50.x = arg1 * gParticleScaleFactor.unk_00.y;
    arg0->unk_50.y = arg2 * gParticleScaleFactor.unk_00.y;
    arg0->unk_50.z = arg3 * gParticleScaleFactor.unk_00.y;
}

void Particle_SetVelocityX(ParticleEffectInstance* arg0, f32 arg1) {
    arg0->unk_50.x = arg1 * gParticleScaleFactor.unk_00.y;
}

void Particle_SetVelocityY(ParticleEffectInstance* arg0, f32 arg1) {
    arg0->unk_50.y = arg1 * gParticleScaleFactor.unk_00.y;
}

void Particle_SetVelocityZ(ParticleEffectInstance* arg0, f32 arg1) {
    arg0->unk_50.z = arg1 * gParticleScaleFactor.unk_00.y;
}

void Particle_ScaleVelocity(ParticleEffectInstance* arg0, f32 arg1) {
    func_814010D8(&arg0->unk_50, arg1 * gParticleScaleFactor.unk_00.y);
}

void Particle_AddVelocity(ParticleEffectInstance* arg0, f32 arg1, f32 arg2, f32 arg3) {
    arg0->unk_50.x += arg1 * gParticleScaleFactor.unk_00.y;
    arg0->unk_50.y += arg2 * gParticleScaleFactor.unk_00.y;
    arg0->unk_50.z += arg3 * gParticleScaleFactor.unk_00.y;
}

void Particle_AddScaledVelocityX(ParticleEffectInstance* arg0, f32 arg1) {
    arg0->unk_50.x += arg1 * gParticleScaleFactor.unk_00.y;
}

void Particle_AddScaledVelocityY(ParticleEffectInstance* arg0, f32 arg1) {
    arg0->unk_50.y += arg1 * gParticleScaleFactor.unk_00.y;
}

void Particle_AddScaledVelocityZ(ParticleEffectInstance* arg0, f32 arg1) {
    arg0->unk_50.z += arg1 * gParticleScaleFactor.unk_00.y;
}

void Particle_SubtractScaledVelocityXYZ(ParticleEffectInstance* arg0, f32 arg1, f32 arg2, f32 arg3) {
    arg0->unk_50.x -= arg1 * gParticleScaleFactor.unk_00.y;
    arg0->unk_50.y -= arg2 * gParticleScaleFactor.unk_00.y;
    arg0->unk_50.z -= arg3 * gParticleScaleFactor.unk_00.y;
}

void Particle_SubtractScaledVelocityX(ParticleEffectInstance* arg0, f32 arg1) {
    arg0->unk_50.x -= arg1 * gParticleScaleFactor.unk_00.y;
}

void Particle_SubtractScaledVelocityY(ParticleEffectInstance* arg0, f32 arg1) {
    arg0->unk_50.y -= arg1 * gParticleScaleFactor.unk_00.y;
}

void Particle_SubtractScaledVelocityZ(ParticleEffectInstance* arg0, f32 arg1) {
    arg0->unk_50.z -= arg1 * gParticleScaleFactor.unk_00.y;
}

s32 Particle_ApproachVelocityX(ParticleEffectInstance* arg0, f32 arg1) {
    return ApproachF32(&arg0->unk_50.x, arg1 * gParticleScaleFactor.unk_00.y, arg0->unk_5C.x);
}

s32 Particle_ApproachVelocityY(ParticleEffectInstance* arg0, f32 arg1) {
    return ApproachF32(&arg0->unk_50.y, arg1 * gParticleScaleFactor.unk_00.y, arg0->unk_5C.y);
}

s32 Particle_ApproachVelocityZ(ParticleEffectInstance* arg0, f32 arg1) {
    return ApproachF32(&arg0->unk_50.z, arg1 * gParticleScaleFactor.unk_00.y, arg0->unk_5C.z);
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
    Particle_SetVelocityXZFromRotationY(arg0);
    Particle_CopyVelocityXZFromTarget(arg0);
}

void Particle_ApplyB278AndCopyXZAlt(ParticleEffectInstance* arg0) {
    Particle_SetVelocityXZFromRotationY(arg0);
    Particle_AddVelocityXZFromTarget(arg0);
}

void Particle_ApplyB23CAndCopyXY(ParticleEffectInstance* arg0) {
    Particle_SetVelocityXYFromRotationZ(arg0);
    Particle_AddVelocityXYFromTarget(arg0);
}

void Particle_ApplyB2B4AndAddAll(ParticleEffectInstance* arg0) {
    Particle_SetVelocityFromRotationXY(arg0);
    Particle_AddVelocityFromTarget(arg0);
}

void Particle_ApplyB330AndAddAll(ParticleEffectInstance* arg0) {
    Particle_SetVelocityFromRotationXZ(arg0);
    Particle_AddVelocityFromTarget(arg0);
}

void Particle_ApplyB3ACAndAddAll(ParticleEffectInstance* arg0) {
    Particle_SetVelocityFromRotationYX(arg0);
    Particle_AddVelocityFromTarget(arg0);
}

void Particle_ApplyB42CAndAddAll(ParticleEffectInstance* arg0) {
    Particle_SetVelocityFromRotationYZ(arg0);
    Particle_AddVelocityFromTarget(arg0);
}

void Particle_ApplyB568AndAddAll(ParticleEffectInstance* arg0) {
    Particle_SetVelocityComplexB(arg0);
    Particle_AddVelocityFromTarget(arg0);
}

void Particle_ApplyB4A0AndAddAll(ParticleEffectInstance* arg0) {
    Particle_SetVelocityComplexA(arg0);
    Particle_AddVelocityFromTarget(arg0);
}

void Particle_ApplyB638AndAddAll(ParticleEffectInstance* arg0) {
    Particle_SetVelocityComplexC(arg0);
    Particle_AddVelocityFromTarget(arg0);
}

void Particle_ApplyB638AndAddAllAlt(ParticleEffectInstance* arg0) {
    Particle_SetVelocityComplexC(arg0);
    Particle_AddVelocityFromTarget(arg0);
}

void Particle_SetTargetVelocityForward(ParticleEffectInstance* arg0) {
    arg0->unk_7C.x = arg0->unk_74 * SINS(arg0->unk_94.y);
    arg0->unk_7C.z = arg0->unk_74 * COSS(arg0->unk_94.y);

    Particle_AddVelocityXZFromTarget(arg0);
}

void Particle_SetTargetVelocityBackward(ParticleEffectInstance* arg0) {
    arg0->unk_7C.x = arg0->unk_74 * SINS(arg0->unk_94.y + 0x8000);
    arg0->unk_7C.z = arg0->unk_74 * COSS(arg0->unk_94.y + 0x8000);

    Particle_AddVelocityXZFromTarget(arg0);
}

void Particle_SetTargetVelocityCustom(ParticleEffectInstance* arg0, f32 arg1) {
    arg0->unk_7C.x = SINS(arg0->unk_94.y + 0x8000) * arg1;
    arg0->unk_7C.z = COSS(arg0->unk_94.y + 0x8000) * arg1;

    Particle_AddVelocityXZFromTarget(arg0);
}

void Particle_SetTargetVelocityY(ParticleEffectInstance* arg0) {
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

void Particle_SetAccelerationScaled(ParticleEffectInstance* arg0, f32 arg1, f32 arg2, f32 arg3) {
    arg0->unk_5C.x = arg1 * gParticleScaleFactor.unk_00.y;
    arg0->unk_5C.y = arg2 * gParticleScaleFactor.unk_00.y;
    arg0->unk_5C.z = arg3 * gParticleScaleFactor.unk_00.y;
}

void Particle_SetAccelerationXScaled(ParticleEffectInstance* arg0, f32 arg1) {
    arg0->unk_5C.x = arg1 * gParticleScaleFactor.unk_00.y;
}

void Particle_SetAccelerationYScaled(ParticleEffectInstance* arg0, f32 arg1) {
    arg0->unk_5C.y = arg1 * gParticleScaleFactor.unk_00.y;
}

void Particle_SetAccelerationZScaled(ParticleEffectInstance* arg0, f32 arg1) {
    arg0->unk_5C.z = arg1 * gParticleScaleFactor.unk_00.y;
}

s32 Particle_ApproachAccelerationY(ParticleEffectInstance* arg0, f32 arg1, f32 arg2) {
    return ApproachF32(&arg0->unk_5C.y, arg1 * gParticleScaleFactor.unk_00.y, arg2 * gParticleScaleFactor.unk_00.y);
}

f32 Particle_ScaleFactor40Percent(f32 arg0) {
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
        ApproachF32(&arg0->unk_38.x, arg1.x, Particle_ScaleFactor40Percent(temp_fa0));
    }

    if (!(sp20 <= 0.01f) || !(sp20 >= -0.01f)) {
        ApproachF32(&arg0->unk_38.y, arg1.y, Particle_ScaleFactor40Percent(sp20));
    }

    if (!(sp24 <= 0.01f) || !(sp24 >= -0.01f)) {
        ApproachF32(&arg0->unk_38.z, arg1.z, Particle_ScaleFactor40Percent(sp24));
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

void Particle_SetRotationDelta(ParticleEffectInstance* arg0, s16 arg1, s16 arg2, s16 arg3) {
    arg0->unk_9A.x = arg1;
    arg0->unk_9A.y = arg2;
    arg0->unk_9A.z = arg3;
}

void Particle_SetRotationDeltaFromVec3s(ParticleEffectInstance* arg0, Vec3s arg1) {
    arg0->unk_9A.x = arg1.x;
    arg0->unk_9A.y = arg1.y;
    arg0->unk_9A.z = arg1.z;
}

void Particle_SetRotationDeltaXY(ParticleEffectInstance* arg0, s16 arg1, s16 arg2) {
    arg0->unk_9A.x = arg1;
    arg0->unk_9A.y = arg2;
}

void Particle_SetRotationDeltaX(ParticleEffectInstance* arg0, s16 arg1) {
    arg0->unk_9A.x = arg1;
}

void Particle_SetRotationDeltaY(ParticleEffectInstance* arg0, s16 arg1) {
    arg0->unk_9A.y = arg1;
}

void Particle_SetRotationDeltaZ(ParticleEffectInstance* arg0, s16 arg1) {
    arg0->unk_9A.z = arg1;
}

void Particle_SetTargetRotationX(ParticleEffectInstance* arg0, s16 arg1) {
    arg0->unk_A0.x = arg1;
}

void Particle_SetTargetRotationY(ParticleEffectInstance* arg0, s16 arg1) {
    arg0->unk_A0.y = arg1;
}

void Particle_SetTargetRotationXY(ParticleEffectInstance* arg0, s16 arg1, s16 arg2) {
    Particle_SetTargetRotationX(arg0, arg1);
    Particle_SetTargetRotationY(arg0, arg2);
}

void Particle_CopyRotationToTarget(ParticleEffectInstance* arg0) {
    arg0->unk_A0.x = arg0->unk_94.x;
    arg0->unk_A0.y = arg0->unk_94.y;
    arg0->unk_A0.z = arg0->unk_94.z;
}

void Particle_AddRotationDelta(ParticleEffectInstance* arg0) {
    arg0->unk_94.x += arg0->unk_9A.x;
    arg0->unk_94.y += arg0->unk_9A.y;
    arg0->unk_94.z += arg0->unk_9A.z;
}

void Particle_AddRotationDeltaX(ParticleEffectInstance* arg0) {
    arg0->unk_94.x += arg0->unk_9A.x;
}

void Particle_AddRotationDeltaY(ParticleEffectInstance* arg0) {
    arg0->unk_94.y += arg0->unk_9A.y;
}

void Particle_AddRotationDeltaZ(ParticleEffectInstance* arg0) {
    arg0->unk_94.z += arg0->unk_9A.z;
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

void func_8140A578(ParticleEffectInstance* arg0, s16 arg1) {
    arg0->unk_94.x += arg1;
}

void func_8140A594(ParticleEffectInstance* arg0, s16 arg1) {
    arg0->unk_94.y += arg1;
}

void func_8140A5B0(ParticleEffectInstance* arg0, s16 arg1) {
    arg0->unk_94.z += arg1;
}

void Particle_AddTargetRotationXY(ParticleEffectInstance* arg0, s16 arg1, s16 arg2) {
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

void Particle_ApproachRotationXWrap(ParticleEffectInstance* arg0) {
    ApproachU16Wrap(&arg0->unk_94.x, arg0->unk_A0.x, arg0->unk_9A.x);
}

void Particle_ApproachRotationYWrap(ParticleEffectInstance* arg0) {
    ApproachU16Wrap(&arg0->unk_94.y, arg0->unk_A0.y, arg0->unk_9A.y);
}

void Particle_ApproachRotationZWrap(ParticleEffectInstance* arg0) {
    ApproachU16Wrap(&arg0->unk_94.z, arg0->unk_A0.z, arg0->unk_9A.z);
}

void Particle_ApproachRotationAllWrap(ParticleEffectInstance* arg0) {
    Particle_ApproachRotationXWrap(arg0);
    Particle_ApproachRotationYWrap(arg0);
}

void Particle_ApproachRotationAllWrapFull(ParticleEffectInstance* arg0) {
    Particle_ApproachRotationXWrap(arg0);
    Particle_ApproachRotationYWrap(arg0);
    Particle_ApproachRotationZWrap(arg0);
}

void Particle_ApproachRotationXWrapToTarget(ParticleEffectInstance* arg0, s16 arg1, s16 arg2) {
    ApproachU16Wrap(&arg0->unk_94.x, arg1, arg2);
}

void Particle_ApproachRotationYWrapToTarget(ParticleEffectInstance* arg0, s16 arg1, s16 arg2) {
    ApproachU16Wrap(&arg0->unk_94.y, arg1, arg2);
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

void Particle_RandomizeRotationXY(ParticleEffectInstance* arg0, s32 arg1, s32 arg2) {
    func_8140A578(arg0, RandomRangeSigned(arg1));
    func_8140A594(arg0, RandomRangeSigned(arg2));
}

void Particle_RandomizeRotationXWithMaskY(ParticleEffectInstance* arg0, s32 arg1, s32 arg2) {
    func_8140A578(arg0, func_81400B28(arg1, 0x8000));
    func_8140A594(arg0, RandomRangeSigned(arg2));
}

void Particle_RandomizeRotationY(ParticleEffectInstance* arg0, s32 arg1) {
    func_8140A594(arg0, RandomRangeSigned(arg1));
}

void Particle_RandomizeRotationYWithMask(ParticleEffectInstance* arg0, s32 arg1) {
    func_8140A594(arg0, func_81400B28(arg1, 0x8000));
}

void Particle_RandomizeRotationXYFixedY(ParticleEffectInstance* arg0) {
    func_8140A578(arg0, RandomRangeSigned(0x10000));
    func_8140A594(arg0, 0x4000);
}

void Particle_CalcDirectionVector(ParticleEffectInstance* arg0, f32 arg1, Vec3f* arg2) {
    arg2->x = SINS(arg0->unk_94.y) * arg1;
    arg2->y = 0.0f;
    arg2->z = COSS(arg0->unk_94.y) * arg1;
}

void Particle_CalcDirectionVectorXYZ(ParticleEffectInstance* arg0, f32 arg1, Vec3f* arg2) {
    arg2->x = arg1 * COSS(arg0->unk_94.x) * SINS(arg0->unk_94.y);
    arg2->y = -arg1 * SINS(arg0->unk_94.x);
    arg2->z = arg1 * COSS(arg0->unk_94.x) * COSS(arg0->unk_94.y);
}

void Particle_CalcDirectionVectorXZ(ParticleEffectInstance* arg0, f32 arg1, Vec3f* arg2) {
    arg2->x = arg1 * SINS(arg0->unk_94.x) * SINS(arg0->unk_94.z);
    arg2->y = -arg1 * SINS(arg0->unk_94.x) * COSS(arg0->unk_94.z);
    arg2->z = arg1 * COSS(arg0->unk_94.x);
}

void Particle_CalcComplexDirection(ParticleEffectInstance* arg0, f32 arg1, Vec3f* arg2) {
    arg2->x = arg1 * (SINS(arg0->unk_94.x) * COSS(arg0->unk_94.y) * SINS(arg0->unk_94.z) +
                      COSS(arg0->unk_94.x) * SINS(arg0->unk_94.y));
    arg2->y = -arg1 * SINS(arg0->unk_94.x) * COSS(arg0->unk_94.z);
    arg2->z = arg1 * (COSS(arg0->unk_94.x) * COSS(arg0->unk_94.y) -
                      SINS(arg0->unk_94.x) * SINS(arg0->unk_94.y) * SINS(arg0->unk_94.z));
}

void Particle_CalcAnotherDirection(ParticleEffectInstance* arg0, f32 arg1, Vec3f* arg2) {
    arg2->x = arg1 * (SINS(arg0->unk_94.y) * COSS(arg0->unk_94.z) +
                      SINS(arg0->unk_94.x) * COSS(arg0->unk_94.y) * SINS(arg0->unk_94.z));
    arg2->y = arg1 * (SINS(arg0->unk_94.y) * SINS(arg0->unk_94.z) -
                      SINS(arg0->unk_94.x) * COSS(arg0->unk_94.y) * COSS(arg0->unk_94.z));
    arg2->z = arg1 * (COSS(arg0->unk_94.x) * COSS(arg0->unk_94.y));
}

void Particle_SetSpeed(ParticleEffectInstance* arg0, f32 arg1) {
    arg0->unk_74 = arg1 * gParticleScaleFactor.unk_00.y;
}

void Particle_SetAcceleration(ParticleEffectInstance* arg0, f32 arg1) {
    arg0->unk_78 = arg1 * gParticleScaleFactor.unk_00.y;
}

s32 Particle_ApproachSpeedScaled(ParticleEffectInstance* arg0, f32 arg1, f32 arg2) {
    return ApproachF32(&arg0->unk_74, arg1 * gParticleScaleFactor.unk_00.y, arg2 * gParticleScaleFactor.unk_00.y);
}

s32 Particle_ApproachSpeed(ParticleEffectInstance* arg0, f32 arg1) {
    return ApproachF32(&arg0->unk_74, arg1 * gParticleScaleFactor.unk_00.y, arg0->unk_78);
}

s32 Particle_ApproachAcceleration(ParticleEffectInstance* arg0, f32 arg1, f32 arg2) {
    return ApproachF32(&arg0->unk_78, arg1 * gParticleScaleFactor.unk_00.y, arg2 * gParticleScaleFactor.unk_00.y);
}

void Particle_SetAccelerationVector(ParticleEffectInstance* arg0, Vec3f arg1) {
    arg0->unk_7C.x = arg1.x * gParticleScaleFactor.unk_00.y;
    arg0->unk_7C.y = arg1.y * gParticleScaleFactor.unk_00.y;
    arg0->unk_7C.z = arg1.z * gParticleScaleFactor.unk_00.y;
}

void Particle_SetAccelerationXYZ(ParticleEffectInstance* arg0, f32 arg1, f32 arg2, f32 arg3) {
    arg0->unk_7C.x = arg1 * gParticleScaleFactor.unk_00.y;
    arg0->unk_7C.y = arg2 * gParticleScaleFactor.unk_00.y;
    arg0->unk_7C.z = arg3 * gParticleScaleFactor.unk_00.y;
}

void Particle_SetAccelerationX(ParticleEffectInstance* arg0, f32 arg1) {
    arg0->unk_7C.x = arg1 * gParticleScaleFactor.unk_00.y;
}

void Particle_SetAccelerationY(ParticleEffectInstance* arg0, f32 arg1) {
    arg0->unk_7C.y = arg1 * gParticleScaleFactor.unk_00.y;
}

void Particle_SetAccelerationZ(ParticleEffectInstance* arg0, f32 arg1) {
    arg0->unk_7C.z = arg1 * gParticleScaleFactor.unk_00.y;
}

s32 Particle_IncrementAccelerationXClamp(ParticleEffectInstance* arg0, f32 arg1, f32 arg2) {
    f32 temp_fv0;
    s32 var_v1 = 0;

    arg0->unk_7C.x += arg2 * gParticleScaleFactor.unk_00.y;

    temp_fv0 = arg1 * gParticleScaleFactor.unk_00.y;
    if (temp_fv0 <= arg0->unk_7C.x) {
        arg0->unk_7C.x = temp_fv0;
        var_v1 = 1;
    }
    return var_v1;
}

s32 Particle_IncrementAccelerationYClamp(ParticleEffectInstance* arg0, f32 arg1, f32 arg2) {
    f32 temp_fv0;
    s32 var_v1 = 0;

    arg0->unk_7C.y += arg2 * gParticleScaleFactor.unk_00.y;

    temp_fv0 = arg1 * gParticleScaleFactor.unk_00.y;
    if (temp_fv0 <= arg0->unk_7C.y) {
        arg0->unk_7C.y = temp_fv0;
        var_v1 = 1;
    }
    return var_v1;
}

s32 Particle_IncrementAccelerationZClamp(ParticleEffectInstance* arg0, f32 arg1, f32 arg2) {
    f32 temp_fv0;
    s32 var_v1 = 0;

    arg0->unk_7C.z += arg2 * gParticleScaleFactor.unk_00.y;

    temp_fv0 = arg1 * gParticleScaleFactor.unk_00.y;
    if (temp_fv0 <= arg0->unk_7C.z) {
        arg0->unk_7C.z = temp_fv0;
        var_v1 = 1;
    }
    return var_v1;
}

s32 Particle_DecrementAccelerationXClamp(ParticleEffectInstance* arg0, f32 arg1, f32 arg2) {
    f32 temp_fv0;
    s32 var_v1 = 0;

    arg0->unk_7C.x -= arg2 * gParticleScaleFactor.unk_00.y;

    temp_fv0 = arg1 * gParticleScaleFactor.unk_00.y;
    if (arg0->unk_7C.x <= temp_fv0) {
        arg0->unk_7C.x = temp_fv0;
        var_v1 = 1;
    }
    return var_v1;
}

s32 Particle_DecrementAccelerationYClamp(ParticleEffectInstance* arg0, f32 arg1, f32 arg2) {
    s32 var_v1 = 0;
    f32 temp_fv0;

    arg0->unk_7C.y -= arg2 * gParticleScaleFactor.unk_00.y;

    temp_fv0 = arg1 * gParticleScaleFactor.unk_00.y;
    if (arg0->unk_7C.y <= temp_fv0) {
        arg0->unk_7C.y = temp_fv0;
        var_v1 = 1;
    }
    return var_v1;
}

s32 Particle_DecrementAccelerationZClamp(ParticleEffectInstance* arg0, f32 arg1, f32 arg2) {
    f32 temp_fv0;
    s32 var_v1 = 0;

    arg0->unk_7C.z -= arg2 * gParticleScaleFactor.unk_00.y;

    temp_fv0 = arg1 * gParticleScaleFactor.unk_00.y;
    if (arg0->unk_7C.z <= temp_fv0) {
        arg0->unk_7C.z = temp_fv0;
        var_v1 = 1;
    }
    return var_v1;
}

void Particle_ScaleAccelerationVector(ParticleEffectInstance* arg0, f32 arg1) {
    arg0->unk_7C.x *= arg1;
    arg0->unk_7C.y *= arg1;
    arg0->unk_7C.z *= arg1;
}

s32 func_8140B180(ParticleEffectInstance* arg0, f32 arg1, f32 arg2) {
    return ApproachF32(&arg0->unk_7C.y, arg1 * gParticleScaleFactor.unk_00.y, arg2 * gParticleScaleFactor.unk_00.y);
}

void Particle_SetVelocityYFromRotationX(ParticleEffectInstance* arg0) {
    arg0->unk_7C.y = COSS(arg0->unk_94.x) * arg0->unk_74;
}

void Particle_SetVelocityXFromRotationY(ParticleEffectInstance* arg0) {
    arg0->unk_7C.x = SINS(arg0->unk_94.y) * arg0->unk_74;
}

void Particle_SetVelocityZFromRotationY(ParticleEffectInstance* arg0) {
    arg0->unk_7C.z = COSS(arg0->unk_94.y) * arg0->unk_74;
}

void Particle_SetVelocityXYFromRotationZ(ParticleEffectInstance* arg0) {
    arg0->unk_7C.x = COSS(arg0->unk_94.z) * arg0->unk_74;
    arg0->unk_7C.y = SINS(arg0->unk_94.z) * arg0->unk_74;
}

void Particle_SetVelocityXZFromRotationY(ParticleEffectInstance* arg0) {
    arg0->unk_7C.x = SINS(arg0->unk_94.y) * arg0->unk_74;
    arg0->unk_7C.z = COSS(arg0->unk_94.y) * arg0->unk_74;
}

void Particle_SetVelocityFromRotationXY(ParticleEffectInstance* arg0) {
    arg0->unk_7C.x = arg0->unk_74 * COSS(arg0->unk_94.x) * SINS(arg0->unk_94.y);
    arg0->unk_7C.y = -arg0->unk_74 * SINS(arg0->unk_94.x);
    arg0->unk_7C.z = arg0->unk_74 * COSS(arg0->unk_94.x) * COSS(arg0->unk_94.y);
}

void Particle_SetVelocityFromRotationXZ(ParticleEffectInstance* arg0) {
    arg0->unk_7C.x = arg0->unk_74 * SINS(arg0->unk_94.x) * SINS(arg0->unk_94.z);
    arg0->unk_7C.y = -arg0->unk_74 * SINS(arg0->unk_94.x) * COSS(arg0->unk_94.z);
    arg0->unk_7C.z = arg0->unk_74 * COSS(arg0->unk_94.x);
}

void Particle_SetVelocityFromRotationYX(ParticleEffectInstance* arg0) {
    arg0->unk_7C.x = arg0->unk_74 * SINS(arg0->unk_94.y);
    arg0->unk_7C.y = -arg0->unk_74 * SINS(arg0->unk_94.x) * COSS(arg0->unk_94.y);
    arg0->unk_7C.z = arg0->unk_74 * COSS(arg0->unk_94.x) * COSS(arg0->unk_94.y);
}

void Particle_SetVelocityFromRotationYZ(ParticleEffectInstance* arg0) {
    arg0->unk_7C.x = arg0->unk_74 * SINS(arg0->unk_94.y) * COSS(arg0->unk_94.z);
    arg0->unk_7C.y = arg0->unk_74 * SINS(arg0->unk_94.y) * SINS(arg0->unk_94.z);
    arg0->unk_7C.z = COSS(arg0->unk_94.y);
}

void Particle_SetVelocityComplexA(ParticleEffectInstance* arg0) {
    arg0->unk_7C.x = arg0->unk_74 * (COSS(arg0->unk_94.x) * SINS(arg0->unk_94.y) * COSS(arg0->unk_94.z) +
                                     SINS(arg0->unk_94.x) * SINS(arg0->unk_94.z));
    arg0->unk_7C.y = -arg0->unk_74 * (COSS(arg0->unk_94.x) * SINS(arg0->unk_94.y) * SINS(arg0->unk_94.z) -
                                      SINS(arg0->unk_94.x) * COSS(arg0->unk_94.z));
    arg0->unk_7C.z = arg0->unk_74 * (COSS(arg0->unk_94.x) * COSS(arg0->unk_94.y));
}

void Particle_SetVelocityComplexB(ParticleEffectInstance* arg0) {
    arg0->unk_7C.x = arg0->unk_74 * (SINS(arg0->unk_94.x) * COSS(arg0->unk_94.y) * SINS(arg0->unk_94.z) +
                                     COSS(arg0->unk_94.x) * SINS(arg0->unk_94.y));
    arg0->unk_7C.y = -arg0->unk_74 * SINS(arg0->unk_94.x) * COSS(arg0->unk_94.z);

    arg0->unk_7C.z = arg0->unk_74 * (-SINS(arg0->unk_94.x) * SINS(arg0->unk_94.y) * SINS(arg0->unk_94.z) +
                                     COSS(arg0->unk_94.x) * COSS(arg0->unk_94.y));
}

void Particle_SetVelocityComplexC(ParticleEffectInstance* arg0) {
    arg0->unk_7C.x = arg0->unk_74 * SINS(arg0->unk_94.y) * COSS(arg0->unk_94.z);
    arg0->unk_7C.y = arg0->unk_74 * (COSS(arg0->unk_94.x) * SINS(arg0->unk_94.y) * SINS(arg0->unk_94.z) -
                                     SINS(arg0->unk_94.x) * COSS(arg0->unk_94.y));
    arg0->unk_7C.z = arg0->unk_74 * (SINS(arg0->unk_94.x) * SINS(arg0->unk_94.y) * SINS(arg0->unk_94.z) +
                                     COSS(arg0->unk_94.x) * COSS(arg0->unk_94.y));
}

void Particle_SetVelocityComplexD(ParticleEffectInstance* arg0) {
    arg0->unk_7C.x = arg0->unk_74 * (SINS(arg0->unk_94.y) * COSS(arg0->unk_94.z) +
                                     SINS(arg0->unk_94.x) * COSS(arg0->unk_94.y) * SINS(arg0->unk_94.z));
    arg0->unk_7C.y = arg0->unk_74 * (SINS(arg0->unk_94.y) * SINS(arg0->unk_94.z) -
                                     SINS(arg0->unk_94.x) * COSS(arg0->unk_94.y) * COSS(arg0->unk_94.z));
    arg0->unk_7C.z = arg0->unk_74 * (COSS(arg0->unk_94.x) * COSS(arg0->unk_94.y));
}

void Particle_UpdatePositionAndAccelFromYaw(ParticleEffectInstance* arg0, f32 arg1, s16 arg2) {
    f32 tmp1 = arg0->unk_50.x;
    f32 tmp2 = arg0->unk_50.z;

    arg0->unk_9A.y += arg2;

    arg0->unk_50.x = arg1 * gParticleScaleFactor.unk_00.y * SINS(arg0->unk_9A.y);
    arg0->unk_50.z = arg1 * gParticleScaleFactor.unk_00.y * COSS(arg0->unk_9A.y);

    arg0->unk_7C.x = arg0->unk_50.x - tmp1;
    arg0->unk_7C.z = arg0->unk_50.z - tmp2;
}

s32 Particle_StartVerticalMotionTimer(ParticleEffectInstance* arg0, f32 arg1, f32 arg2, f32 arg3, s16 arg4, s16 arg5) {
    s32 sp24 = 0;

    if (Particle_CanSetFlag(arg0, 2) != 0) {
        Particle_SetFlag(arg0, 2);
        arg0->unk_50.x = arg0->unk_50.y = arg0->unk_50.z = 0.0f;
        arg0->unk_74 = arg3 * gParticleScaleFactor.unk_00.y;
        arg0->unk_7C.y = arg1 * gParticleScaleFactor.unk_00.y;
        arg0->unk_94.y = arg4;
        Particle_SetVelocityXZFromRotationY(arg0);
        arg0->unk_BA = arg5;
    }

    arg0->unk_BA--;
    if (arg0->unk_BA < 0) {
        sp24 = 1;
    } else {
        arg0->unk_7C.y -= arg2 * gParticleScaleFactor.unk_00.y;
        Particle_AddVelocityFromTarget(arg0);
    }

    return sp24;
}

void Particle_SetScaleFactor1(ParticleEffectInstance* arg0, f32 arg1) {
    arg0->unk_1C = arg1 * gParticleScaleFactor.unk_00.y;
}

void Particle_SetScaleRaw1(ParticleEffectInstance* arg0, f32 arg1) {
    arg0->unk_1C = arg1;
}

void Particle_SetScaleFactor2(ParticleEffectInstance* arg0, f32 arg1) {
    arg0->unk_20 = arg1 * gParticleScaleFactor.unk_00.y;
}

void Particle_SetScaleFactor3(ParticleEffectInstance* arg0, f32 arg1) {
    arg0->unk_24 = arg1 * gParticleScaleFactor.unk_00.y;
}

s32 Particle_ApproachScaleFactor1(ParticleEffectInstance* arg0, f32 arg1, f32 arg2) {
    return ApproachF32(&arg0->unk_1C, arg1 * gParticleScaleFactor.unk_00.y, arg2 * gParticleScaleFactor.unk_00.y);
}

s32 Particle_ApproachScaleFactor1WithCallback(ParticleEffectInstance* arg0, f32 arg1, f32 arg2) {
    s32 sp1C = Particle_ApproachScaleFactor1(arg0, arg1, arg2);

    if (sp1C != 0) {
        Particle_IncrementState(arg0);
    }
    return sp1C;
}

s32 Particle_ApproachScaleFactor2(ParticleEffectInstance* arg0) {
    return ApproachF32(&arg0->unk_1C, arg0->unk_20, arg0->unk_24);
}

s32 Particle_ApproachScaleFactor2WithCallback(ParticleEffectInstance* arg0) {
    s32 sp1C = Particle_ApproachScaleFactor2(arg0);

    if (sp1C != 0) {
        Particle_IncrementState(arg0);
    }
    return sp1C;
}

s32 Particle_ApproachScaleFactor3(ParticleEffectInstance* arg0, f32 arg1, f32 arg2) {
    return ApproachF32(&arg0->unk_20, arg1 * gParticleScaleFactor.unk_00.y, arg2 * gParticleScaleFactor.unk_00.y);
}

void Particle_SetPrimColor(ParticleEffectInstance* arg0, u8 arg1, u8 arg2, u8 arg3) {
    arg0->prim_r = arg1;
    arg0->prim_g = arg2;
    arg0->prim_b = arg3;
}

s32 Particle_ApproachPrimR(ParticleEffectInstance* arg0, u8 arg1, u8 arg2) {
    return ApproachU8(&arg0->prim_r, arg1, arg2);
}

s32 Particle_ApproachPrimG(ParticleEffectInstance* arg0, u8 arg1, u8 arg2) {
    return ApproachU8(&arg0->prim_g, arg1, arg2);
}

s32 Particle_ApproachPrimB(ParticleEffectInstance* arg0, u8 arg1, u8 arg2) {
    return ApproachU8(&arg0->prim_b, arg1, arg2);
}

void Particle_SetEnvColor(ParticleEffectInstance* arg0, u8 arg1, u8 arg2, u8 arg3) {
    arg0->env_r = arg1;
    arg0->env_g = arg2;
    arg0->env_b = arg3;
}

s32 Particle_ApproachEnvR(ParticleEffectInstance* arg0, u8 arg1, u8 arg2) {
    return ApproachU8(&arg0->env_r, arg1, arg2);
}

s32 Particle_ApproachEnvB(ParticleEffectInstance* arg0, u8 arg1, u8 arg2) {
    return ApproachU8(&arg0->env_b, arg1, arg2);
}

s32 Particle_ApproachEnvG(ParticleEffectInstance* arg0, u8 arg1, u8 arg2) {
    return ApproachU8(&arg0->env_g, arg1, arg2);
}

void Particle_SetPrimAlpha(ParticleEffectInstance* arg0, u8 arg1) {
    arg0->prim_a = arg1;
}

s32 Particle_ApproachPrimAlpha(ParticleEffectInstance* arg0, u8 arg1, u8 arg2) {
    return ApproachU8(&arg0->prim_a, arg1, arg2);
}

s32 Particle_ApproachPrimAlphaWithCallback(ParticleEffectInstance* arg0, u8 arg1, u8 arg2) {
    s32 sp1C = Particle_ApproachPrimAlpha(arg0, arg1, arg2);

    if (sp1C != 0) {
        Particle_IncrementState(arg0);
    }
    return sp1C;
}

void Particle_SetTimerA6(ParticleEffectInstance* arg0, s16 arg1) {
    arg0->unk_A6 = arg1;
}

s16 Particle_GetTimerA6(ParticleEffectInstance* arg0) {
    return arg0->unk_A6;
}

s32 Particle_DecrementTimerA6Clamp(ParticleEffectInstance* arg0, s16 arg1, s16 arg2) {
    s32 var_v1 = 0;

    arg0->unk_A6 -= arg2;
    if (arg1 >= arg0->unk_A6) {
        arg0->unk_A6 = arg1;
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
        Particle_IncrementState(arg0);
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
        Particle_IncrementState(arg0);
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
        Particle_IncrementState(arg0);
    }
    return sp1C;
}

void Particle_SetByteCA(ParticleEffectInstance* arg0, u8 arg1) {
    arg0->unk_CA = arg1;
}

void Particle_SetShortAC(ParticleEffectInstance* arg0, s16 arg1) {
    arg0->unk_AC = arg1;
}

void Particle_SetByteCF(ParticleEffectInstance* arg0, u8 arg1) {
    arg0->unk_CF = arg1;
}

void func_8140BEF8(ParticleEffectInstance* arg0, u8 arg1) {
    arg0->unk_CF = arg1;
}

void Particle_SetByteCC(ParticleEffectInstance* arg0, u8 arg1) {
    arg0->unk_CC = arg1;
}

void Particle_SetShortAA(ParticleEffectInstance* arg0, s16 arg1) {
    arg0->unk_AA = arg1;
}

void Particle_SetShortCE(ParticleEffectInstance* arg0, s16 arg1) {
    arg0->unk_CE = arg1;
}

void Particle_SetByteCD(ParticleEffectInstance* arg0, s16 arg1) {
    arg0->unk_CD = arg1;
}

void Particle_SetShortAE(ParticleEffectInstance* arg0, s16 arg1) {
    arg0->unk_AE = arg1;
}

s32 Particle_ApproachShortAE(ParticleEffectInstance* arg0, s16 arg1, s16 arg2) {
    return ApproachS16Signed(&arg0->unk_AE, arg1, arg2);
}

s32 Particle_ApproachShortAEWithCallback(ParticleEffectInstance* arg0, s16 arg1, s16 arg2) {
    s32 sp1C = Particle_ApproachShortAE(arg0, arg1, arg2);

    if (sp1C != 0) {
        Particle_IncrementState(arg0);
    }
    return sp1C;
}

void Particle_SetShortB0(ParticleEffectInstance* arg0, s16 arg1) {
    arg0->unk_B0 = arg1;
}

s32 Particle_ApproachShortB0(ParticleEffectInstance* arg0, s16 arg1, s16 arg2) {
    return ApproachS16Signed(&arg0->unk_B0, arg1, arg2);
}

s16 Particle_GetShortAC(ParticleEffectInstance* arg0) {
    return arg0->unk_AC;
}

s32 Particle_GetShortCE(ParticleEffectInstance* arg0) {
    return arg0->unk_CE;
}

u8 Particle_GetByteCD(ParticleEffectInstance* arg0) {
    return arg0->unk_CD;
}

s16 Particle_GetShortAE(ParticleEffectInstance* arg0) {
    return arg0->unk_AE;
}

s16 Particle_GetShortCF(ParticleEffectInstance* arg0) {
    s32 tmp = arg0->unk_CF;
    return tmp;
}

s16 Particle_GetShortAA(ParticleEffectInstance* arg0) {
    return arg0->unk_AA;
}

void Particle_SetShortACIfValid(ParticleEffectInstance* arg0, s16 arg1) {
    if ((u32)arg0 != -1) {
        Particle_SetShortAC(arg0, arg1);
    }
}

void Particle_SetByteCFIfValid(ParticleEffectInstance* arg0, u8 arg1) {
    if ((u32)arg0 != -1) {
        Particle_SetByteCF(arg0, arg1);
    }
}

void Particle_SetTimerA6IfValid(ParticleEffectInstance* arg0, s16 arg1) {
    if ((u32)arg0 != -1) {
        Particle_SetTimerA6(arg0, arg1);
    }
}

void Particle_SetTimerA8IfValid(ParticleEffectInstance* arg0, s16 arg1) {
    if ((u32)arg0 != -1) {
        Particle_SetTimerA8(arg0, arg1);
    }
}

void Particle_SetByteCEIfValid(ParticleEffectInstance* arg0, u8 arg1) {
    if ((u32)arg0 != -1) {
        arg0->unk_CE = arg1;
    }
}

void Particle_SetByteCDIfValid(ParticleEffectInstance* arg0, u8 arg1) {
    if ((u32)arg0 != -1) {
        arg0->unk_CD = arg1;
    }
}

void Particle_SetShortAAIfValid(ParticleEffectInstance* arg0, s16 arg1) {
    if ((u32)arg0 != -1) {
        arg0->unk_AA = arg1;
    }
}

void Particle_SetPrimAlphaIfValid(ParticleEffectInstance* arg0, u8 arg1) {
    if ((u32)arg0 != -1) {
        Particle_SetPrimAlpha(arg0, arg1);
    }
}

void Particle_SetShortAEIfValid(ParticleEffectInstance* arg0, s16 arg1) {
    if ((u32)arg0 != -1) {
        arg0->unk_AE = arg1;
    }
}

void Particle_SetShortB0IfValid(ParticleEffectInstance* arg0, s16 arg1) {
    if ((u32)arg0 != -1) {
        arg0->unk_B0 = arg1;
    }
}

void Particle_UpdateForCamera(CameraStruct* arg0) {
    s32 i;
    ParticleEffectInstance* var_s0;
    ParticleEffectInstance* var_s2 = gParticleInstances;

    for (i = 0; i < 0x12C; i++, var_s2++) {
        if ((var_s2->unk_D0 != 0) && (var_s2->prev == NULL) && (Particle_CanSetFlag(var_s2, 8) != 0)) {
            Particle_HandleDisplayList(var_s2);
            var_s0 = var_s2;
            while (var_s0 != NULL) {
                if ((Particle_HasFlag(var_s0, 4) != 0) && (var_s0->unk_B2 >= 2)) {
                    Particle_RenderWithCamera(var_s0, arg0);
                }
                var_s0 = var_s0->next;
            }
        }
    }
}

void Particle_ProcessAllForCamera(CameraStruct* arg0) {
    s32 i;
    ParticleEffectInstance* var_s0 = gParticleInstances;

    for (i = 0; i < 0x12C; i++, var_s0++) {
        if ((var_s0->unk_D0 != 0) && (Particle_HasFlag(var_s0, 8) != 0)) {
            Particle_HandleDisplayList(var_s0);
            if ((Particle_HasFlag(var_s0, 4) != 0) && (var_s0->unk_B2 >= 2)) {
                Particle_RenderWithCamera(var_s0, arg0);
            }
        }
    }
}

void Particle_RenderUIOverlay(s16 arg0) {
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

void Particle_ExecuteCallbackBasedOnType(ParticleEffectInstance* arg0, unk_D_8140E728_01C_004_1* arg1) {
    switch (arg1->unk_01) {
        case 0:
            arg1->unk_04(arg0, arg1->unk_0C.arg, arg1);
            break;

        case 1:
            arg1->unk_04(arg0, arg1->unk_0C.s->arg, arg1);
            break;
    }
}

void Particle_HandleDisplayList(ParticleEffectInstance* arg0) {
    UNUSED s32 pad;
    unk_D_8140E728_01C_004_1* sp18 = arg0->unk_0C->unk_04.a;

    if (arg0->unk_0C->unk_00 == 1) {
        Particle_RenderUIOverlay(sp18->unk_02);
        if (sp18->unk_00 == 1) {
            Particle_ExecuteCallbackBasedOnType(arg0, sp18);
        }
    }
}

void Particle_RenderWithCamera(ParticleEffectInstance* arg0, CameraStruct* arg1) {
    UNUSED s32 pad;
    unk_D_8140E728_01C_004_1* sp18 = arg0->unk_0C->unk_04.a;

    switch (arg0->unk_0C->unk_00) {
        case 1:
            if (sp18->unk_00 == 0) {
                Particle_ExecuteCallbackBasedOnType(arg0, sp18);
            }
            sp18->unk_08(arg0, arg1, sp18);
            break;

        case 3:
            arg0->unk_0C->unk_04.func(arg0, arg1);
            break;
    }
}

void Particle_NoOp(UNUSED ParticleEffectInstance* arg0, UNUSED CameraStruct* arg1) {
}
