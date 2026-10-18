#include "fragment34.h"
#include "include/math.h"
#include "src/F420.h"
#include "src/math_util.h"

unk_D_8140E620* gMatrixBuffer;
s32 gMatrixBufferIdx;
s32 gMatrixBufferIdx;
unk_D_8140E634 gParticleScaleFactor;
ParticleCameraInfo* gParticleCameraInfo;
u32 gTimerCounter;
s32 gTimerMask6;
s32 gTimerMask5;
s32 gTimerMask4;
s32 gTimerMask3;
s32 gTimerMask2;
u32 gTimerMod3;
s32 gTimerMask1;
u32 gTimerShift6;
u32 gTimerShift5;
u32 gTimerShift4;
u32 gTimerShift3;
u32 gTimerShift2;
u32 gTimerDiv3;
u32 gTimerShift1;
s32 gTimerBit6;
s32 gTimerBit5;
s32 gTimerBit4;
s32 gTimerBit3;
s32 gTimerBit2;
s32 gTimerDiv3Parity;
s32 gTimerBit1;
s32 gRandomSeedCounter;
static s32 pad_D_8140E714[2];
ParticleEffectInstance* gParticleInstances;
ParticleDef* gParticleDefs;
ParticleSpawner* gParticleEmitters;
s32 gParticleAllocIndex;
s32 gParticleDefNextIdx;
s32 gParticleEmitterNextIdx;

void SetBits(s32* arg0, s32 arg1) {
    *arg0 |= arg1;
}

void ClearBits(s32* arg0, s32 arg1) {
    *arg0 &= ~arg1;
}

void ToggleBits(s32* arg0, s32 arg1) {
    *arg0 ^= arg1;
}

s32 IsBitSet(s32* arg0, s32 arg1) {
    s32 var_v1 = 0;

    if (*arg0 & arg1) {
        var_v1 = 1;
    }
    return var_v1;
}

s32 IsBitClear(s32* arg0, s32 arg1) {
    s32 var_v1 = 0;

    if (!(*arg0 & arg1)) {
        var_v1 = 1;
    }
    return var_v1;
}

s32 ApproachFloatUp(f32* arg0, f32 arg1, f32 arg2) {
    s32 var_v1 = 0;

    if (*arg0 < arg1) {
        *arg0 += arg2;
        if (arg1 <= *arg0) {
            *arg0 = arg1;
            var_v1 = 1;
        }
    }
    return var_v1;
}

s32 ApproachFloatDown(f32* arg0, f32 arg1, f32 arg2) {
    s32 var_v1 = 0;

    if (arg1 < *arg0) {
        *arg0 -= arg2;
        if (*arg0 <= arg1) {
            *arg0 = arg1;
            var_v1 = 1;
        }
    }
    return var_v1;
}

s32 ApproachIntUp(s32* arg0, s32 arg1, s32 arg2) {
    s32 var_v1 = 0;

    if (*arg0 < arg1) {
        *arg0 += arg2;
        if (*arg0 >= arg1) {
            *arg0 = arg1;
            var_v1 = 1;
        }
    }
    return var_v1;
}

s32 ApproachIntDown(s32* arg0, s32 arg1, s32 arg2) {
    s32 var_v1 = 0;

    if (arg1 < *arg0) {
        *arg0 -= arg2;
        if (arg1 >= *arg0) {
            *arg0 = arg1;
            var_v1 = 1;
        }
    }
    return var_v1;
}

s32 ApproachS16Up(s16* arg0, s16 arg1, s16 arg2) {
    s32 var_v1 = 0;

    if (*arg0 < arg1) {
        *arg0 += arg2;
        if (*arg0 >= arg1) {
            *arg0 = arg1;
            var_v1 = 1;
        }
    }
    return var_v1;
}

s32 ApproachU16Up(u16* arg0, u16 arg1, u16 arg2) {
    s32 var_v1 = 0;

    if (*arg0 < arg1) {
        *arg0 += arg2;
        if (*arg0 >= arg1) {
            *arg0 = arg1;
            var_v1 = 1;
        }
    }
    return var_v1;
}

s32 ApproachS16Down(s16* arg0, s16 arg1, s16 arg2) {
    s32 var_v1 = 0;

    if (arg1 < *arg0) {
        *arg0 -= arg2;
        if (arg1 >= *arg0) {
            *arg0 = arg1;
            var_v1 = 1;
        }
    }
    return var_v1;
}

s32 ApproachU16Down(u16* arg0, s32 arg1, s32 arg2) {
    s32 var_v1 = 0;
    s32 temp_v0 = *arg0;

    if (arg1 < temp_v0) {
        temp_v0 -= arg2;
        if (arg1 >= temp_v0) {
            temp_v0 = arg1;
            var_v1 = 1;
        }
        *arg0 = temp_v0;
    }
    return var_v1;
}

s32 ApproachFloatUpPtr(f32* arg0, f32 arg1, f32* arg2) {
    s32 var_v1 = 0;

    if (*arg0 < arg1) {
        *arg0 += *arg2;
        if (arg1 <= *arg0) {
            *arg0 = arg1;
            var_v1 = 1;
        }
    }
    return var_v1;
}

s32 ApproachFloatDownPtr(f32* arg0, f32 arg1, f32* arg2) {
    s32 var_v1 = 0;

    if (arg1 < *arg0) {
        *arg0 -= *arg2;
        if (*arg0 <= arg1) {
            *arg0 = arg1;
            var_v1 = 1;
        }
    }
    return var_v1;
}

s32 ApproachS32UpPtr(s32* arg0, s32 arg1, s32* arg2) {
    s32 var_v1 = 0;

    if (*arg0 < arg1) {
        *arg0 += *arg2;
        if (*arg0 >= arg1) {
            *arg0 = arg1;
            var_v1 = 1;
        }
    }
    return var_v1;
}

s32 ApproachS32DownPtr(s32* arg0, s32 arg1, s32* arg2) {
    s32 var_v1 = 0;

    if (arg1 < *arg0) {
        *arg0 -= *arg2;
        if (arg1 >= *arg0) {
            *arg0 = arg1;
            var_v1 = 1;
        }
    }
    return var_v1;
}

s32 ApproachS16UpPtr(s16* arg0, s16 arg1, s16* arg2) {
    s32 var_v1 = 0;

    if (*arg0 < arg1) {
        *arg0 += *arg2;
        if (*arg0 >= arg1) {
            *arg0 = arg1;
            var_v1 = 1;
        }
    }
    return var_v1;
}

s32 ApproachS16DownPtr(s16* arg0, s16 arg1, s16* arg2) {
    s32 var_v1 = 0;

    if (arg1 < *arg0) {
        *arg0 -= *arg2;
        if (arg1 >= *arg0) {
            *arg0 = arg1;
            var_v1 = 1;
        }
    }
    return var_v1;
}

s32 ApproachS8(s8* arg0, s8 arg1, s8 arg2) {
    s32 var_v1 = 0;
    s32 var_a3 = *arg0;

    if (var_a3 < arg1) {
        if (arg2 >= 0) {
            var_a3 += arg2;
        } else {
            var_a3 -= arg2;
        }

        if (var_a3 >= arg1) {
            var_a3 = arg1;
            var_v1 = 1;
        }
    } else if (arg1 < var_a3) {
        if (arg2 >= 0) {
            var_a3 -= arg2;
        } else {
            var_a3 += arg2;
        }

        if (arg1 >= var_a3) {
            var_a3 = arg1;
            var_v1 = 1;
        }
    } else {
        var_v1 = 1;
    }

    *arg0 = var_a3;
    return var_v1;
}

s32 ApproachU8(u8* arg0, u8 arg1, u8 arg2) {
    s32 var_v1 = 0;
    s32 var_a3 = *arg0;

    if (var_a3 < arg1) {
        var_a3 += arg2;
        if (var_a3 >= arg1) {
            var_a3 = arg1;
            var_v1 = 1;
        }
    } else if (arg1 < var_a3) {
        var_a3 -= arg2;
        if (arg1 >= var_a3) {
            var_a3 = arg1;
            var_v1 = 1;
        }
    } else {
        var_v1 = 1;
    }

    *arg0 = var_a3;
    return var_v1;
}

s32 ApproachS16Signed(s16* arg0, s16 arg1, s16 arg2) {
    s32 var_v1 = 0;
    s32 var_a3 = *arg0;

    if (var_a3 < arg1) {
        if (arg2 >= 0) {
            var_a3 += arg2;
        } else {
            var_a3 -= arg2;
        }

        if (var_a3 >= arg1) {
            var_a3 = arg1;
            var_v1 = 1;
        }
    } else if (arg1 < var_a3) {
        if (arg2 >= 0) {
            var_a3 -= arg2;
        } else {
            var_a3 += arg2;
        }

        if (arg1 >= var_a3) {
            var_a3 = arg1;
            var_v1 = 1;
        }
    } else {
        var_v1 = 1;
    }

    *arg0 = var_a3;
    return var_v1;
}

s32 ApproachU16Wrap(s16* arg0, s16 arg1, s16 arg2) {
    s32 a0 = *(u16*)arg0;
    s32 var_v1 = 0;
    s32 var_a1 = (u16)arg1;

    if ((u16)arg1 == a0) {
        var_a1 = (u16)arg1;
        var_v1 = 1;
    } else {
        var_a1 = (u16)arg1 - a0;
        if (var_a1 < -0x8000) {
            var_a1 = arg2 + a0;
            if (((u16)arg1 - var_a1) <= -65536) {
                var_a1 = (u16)arg1;
                var_v1 = 1;
            }
        } else if (var_a1 < 0) {
            var_a1 = a0 - arg2;
            if (((u16)arg1 - var_a1) >= 0) {
                var_a1 = (u16)arg1;
                var_v1 = 1;
            }
        } else if (var_a1 < 0x8000) {
            var_a1 = arg2 + a0;
            if (((u16)arg1 - var_a1) <= 0) {
                var_a1 = (u16)arg1;
                var_v1 = 1;
            }
        } else {
            var_a1 = a0 - arg2;
            if (((u16)arg1 - var_a1) >= 0x10000) {
                var_a1 = (u16)arg1;
                var_v1 = 1;
            }
        }
    }

    *arg0 = var_a1;
    return var_v1;
}

s32 ApproachS32(s32* arg0, s32 arg1, s32 arg2) {
    s32 temp_v0 = *arg0;
    s32 var_v1 = 0;

    if (temp_v0 < arg1) {
        if (arg2 >= 0) {
            *arg0 = temp_v0 + arg2;
        } else {
            *arg0 = temp_v0 - arg2;
        }

        if (*arg0 >= arg1) {
            *arg0 = arg1;
            var_v1 = 1;
        }
    } else if (arg1 < temp_v0) {
        if (arg2 >= 0) {
            *arg0 = temp_v0 - arg2;
        } else {
            *arg0 = temp_v0 + arg2;
        }

        if (arg1 >= *arg0) {
            *arg0 = arg1;
            var_v1 = 1;
        }
    } else {
        var_v1 = 1;
    }

    return var_v1;
}

s32 ApproachF32(f32* arg0, f32 arg1, f32 arg2) {
    s32 var_v1 = 0;

    if (*arg0 < arg1) {
        if (arg2 >= 0.0f) {
            *arg0 += arg2;
        } else {
            *arg0 -= arg2;
        }

        if (arg1 <= *arg0) {
            *arg0 = arg1;
            var_v1 = 1;
        }
    } else if (arg1 < *arg0) {
        if (arg2 >= 0.0f) {
            *arg0 -= arg2;
        } else {
            *arg0 += arg2;
        }

        if (*arg0 <= arg1) {
            *arg0 = arg1;
            var_v1 = 1;
        }
    } else {
        var_v1 = 1;
    }

    return var_v1;
}

void BounceFloat(f32* arg0, f32 arg1, f32 arg2, f32* arg3) {
    *arg0 += *arg3;

    if (*arg3 >= 0.0f) {
        if (arg2 <= *arg0) {
            *arg0 = arg2;
            *arg3 = -*arg3;
        }
    } else if (*arg0 <= arg1) {
        *arg0 = arg1;
        *arg3 = -*arg3;
    }
}

void BounceS16(s16* arg0, s16 arg1, s16 arg2, s16* arg3) {
    *arg0 += *arg3;
    if (*arg3 >= 0) {
        if (*arg0 >= arg2) {
            *arg0 = arg2;
            *arg3 = -*arg3;
        }
    } else if (arg1 >= *arg0) {
        *arg0 = arg1;
        *arg3 = -*arg3;
    }
}

void Vec3f_Copy(Vec3f* arg0, Vec3f* arg1) {
    arg0->x = arg1->x;
    arg0->y = arg1->y;
    arg0->z = arg1->z;
}

void Vec3s_CopyTo(Vec3s* arg0, Vec3s* arg1) {
    arg0->x = arg1->x;
    arg0->y = arg1->y;
    arg0->z = arg1->z;
}

void Vec3f_Offset(Vec3f* arg0, Vec3f* arg1) {
    arg0->x += arg1->x;
    arg0->y += arg1->y;
    arg0->z += arg1->z;
}

void Vec3s_Offset(Vec3s* arg0, Vec3s* arg1) {
    arg0->x += arg1->x;
    arg0->y += arg1->y;
    arg0->z += arg1->z;
}

f32 Vec3f_Dot(Vec3f arg0, Vec3f arg1) {
    return (arg0.x * arg1.x) + (arg0.y * arg1.y) + (arg0.z * arg1.z);
}

s32 IsWithinRadius2D(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4) {
    s32 var_v1 = 0;

    if ((SQ(arg2 - arg0) + SQ(arg3 - arg1)) <= SQ(arg4)) {
        var_v1 = 1;
    }
    return var_v1;
}

void func_81400A60(void) {
    gRandomSeedCounter++;
}

u32 RandomMod(s32 arg0) {
    u32 temp_a0 = guRandom() + gRandomSeedCounter;
    u32 var_v1;

    if (arg0 == 0) {
        var_v1 = 0;
    } else {
        var_v1 = (temp_a0 / 10) % arg0;
    }
    return var_v1;
}

s32 RandomModPlus(s32 arg0, s32 arg1) {
    return RandomMod(arg0) + arg1;
}

s32 RandomRangeSigned(s32 arg0) {
    return RandomMod(arg0 * 2) - arg0;
}

s32 RandomRangeSignedPlus(s32 arg0, s32 arg1) {
    return RandomRangeSigned(arg0) + arg1;
}

s32 func_81400B4C(s32 arg0, s32 arg1) {
    s32 temp_v0 = RandomRangeSigned(arg0);

    if (temp_v0 >= 0) {
        temp_v0 += arg1;
    } else {
        temp_v0 -= arg1;
    }
    return temp_v0;
}

void func_81400B84(UNUSED s32 arg0) {
}

s16 Vec3f_AngleX(Vec3f arg0) {
    return MathUtil_Atan2s(arg0.y, arg0.z);
}

s16 Vec3f_AngleY(Vec3f arg0) {
    return MathUtil_Atan2s(arg0.z, arg0.x);
}

s16 Vec3f_AngleZ(Vec3f arg0) {
    return MathUtil_Atan2s(arg0.x, arg0.y);
}

void Vec3f_ToAngles(Vec3s* arg0, Vec3f arg1) {
    arg0->x = MathUtil_Atan2s(arg1.y, arg1.z);
    arg0->y = MathUtil_Atan2s(arg1.z, arg1.x);
    arg0->z = MathUtil_Atan2s(arg1.x, arg1.y);
}

f32 func_81400C80(f32 arg0, f32 arg1, s16 arg2) {
    return (COSS(arg2) * arg0) - (SINS(arg2) * arg1);
}

f32 func_81400CC0(f32 arg0, f32 arg1, s16 arg2) {
    return (SINS(arg2) * arg0) + (COSS(arg2) * arg1);
}

Vec3f* Vec3f_RotateY(Vec3f* arg0, Vec3f arg1, Vec3s arg2) {
    f32 temp_fv0 = SINS(arg2.y);
    f32 temp_fv1 = COSS(arg2.y);

    arg0->x = (arg1.x * temp_fv1) + (arg1.z * temp_fv0);
    arg0->y = arg1.y;
    arg0->z = (-arg1.x * temp_fv0) + (arg1.z * temp_fv1);

    return arg0;
}

Vec3f* Vec3f_SetPolarXZ(Vec3f* arg0, f32 arg1, s16 arg2) {
    f32 temp_fv0 = SINS(arg2);
    f32 temp_fv1 = COSS(arg2);

    arg0->x = arg1 * temp_fv0;
    arg0->y = 0.0f;
    arg0->z = arg1 * temp_fv1;

    return arg0;
}

Vec3f* Vec3f_RotateXY(Vec3f* arg0, Vec3f arg1, Vec3s arg4) {
    f32 x = arg1.x;
    f32 y = arg1.y;
    f32 z = arg1.z;
    f32 temp_fv0 = SINS(arg4.x);
    f32 temp_fv1 = COSS(arg4.x);
    f32 temp_ft4 = SINS(arg4.y);
    f32 temp_ft5 = COSS(arg4.y);

    arg0->x = (x * temp_ft5) + (z * temp_ft4);
    arg0->y = ((x * temp_fv0 * temp_ft4) + (y * temp_fv1)) - (z * temp_fv0 * temp_ft5);
    arg0->z = (-x * temp_fv1 * temp_ft4) + (y * temp_fv0) + (z * temp_fv1 * temp_ft5);

    return arg0;
}

f32 Vec3f_Dist(Vec3f arg0, Vec3f arg1) {
    return sqrtf(SQ(arg1.x - arg0.x) + SQ(arg1.y - arg0.y) + SQ(arg1.z - arg0.z));
}

f32 Vec3f_DistXZ(Vec3f arg0, Vec3f arg1) {
    return sqrtf(SQ(arg1.x - arg0.x) + SQ(arg1.z - arg0.z));
}

Vec3f* Vec3f_GetDirection(Vec3f* arg0, Vec3f arg1, Vec3f arg2) {
    arg0->x = arg2.x - arg1.x;
    arg0->y = arg2.y - arg1.y;
    arg0->z = arg2.z - arg1.z;

    Vec3f_Normalize(arg0);

    return arg0;
}

s32 func_81400FA4(Vec3f arg0, Vec3f arg1, f32 arg2) {
    return Vec3f_Dist(arg0, arg1) / arg2;
}

s32 Particle_ComputeLifespan(Vec3f* arg0, Vec3f arg1, Vec3f arg2, f32 arg3) {
    f32 temp_fv1;

    arg0->x = arg2.x - arg1.x;
    arg0->y = arg2.y - arg1.y;
    arg0->z = arg2.z - arg1.z;

    temp_fv1 = arg3 / sqrtf(SQ(arg0->x) + SQ(arg0->y) + SQ(arg0->z));

    arg0->x = arg0->x * temp_fv1;
    arg0->y = arg0->y * temp_fv1;
    arg0->z = arg0->z * temp_fv1;

    return 1.0f / temp_fv1;
}

Vec3f* Vec3f_SetRandomDirection(Vec3f* arg0, f32 arg1) {
    Vec3f sp2C;
    Vec3s sp24;

    sp2C.x = 0.0f;
    sp2C.y = 0.0f;
    sp2C.z = arg1;

    sp24.x = RandomMod(0x10000);
    sp24.y = RandomMod(0x10000);

    Vec3f_RotateXY(arg0, sp2C, sp24);
    return arg0;
}

Vec3f* Vec3f_Scale(Vec3f* arg0, f32 arg1) {
    arg0->x *= arg1;
    arg0->y *= arg1;
    arg0->z *= arg1;

    return arg0;
}

s16 Vec3f_AngleXTo(Vec3f arg0, Vec3f arg1) {
    return MathUtil_Atan2s(arg1.y - arg0.y, arg1.z - arg0.z);
}

s16 Vec3f_AngleYTo(Vec3f arg0, Vec3f arg1) {
    return MathUtil_Atan2s(arg1.z - arg0.z, arg1.x - arg0.x);
}

s16 Vec3f_AngleZTo(Vec3f arg0, Vec3f arg1) {
    return MathUtil_Atan2s(arg1.x - arg0.x, arg1.y - arg0.y);
}

s16 func_81401268(s16 arg0, s16 arg1) {
    s16 temp_v0 = arg1 - arg0;

    if ((arg0 >> 8) != (arg1 >> 8)) {
        if (temp_v0 < 0x400) {
            arg0 += 0x80;
        } else if (temp_v0 < 0x800) {
            arg0 += 0x200;
        } else if (temp_v0 < 0x4000) {
            arg0 += 0x400;
        } else if (temp_v0 < 0x8000) {
            arg0 += 0x700;
        } else if (temp_v0 < 0xC000) {
            arg0 -= 0x700;
        } else if (temp_v0 < 0xF800) {
            arg0 -= 0x400;
        } else if (temp_v0 < 0xFC00) {
            arg0 -= 0x200;
        } else {
            arg0 -= 0x80;
        }
    } else {
        arg0 = arg1;
    }

    return arg0;
}

void func_8140138C(void) {
}

void Matrix_SendToDisplayList(MtxF* arg0) {
    if (gMatrixBufferIdx < 0x16C) {
        Matrix_ConvertToMtx(&gMatrixBuffer->unk_0000[gMatrixBufferIdx], arg0);

        gSPMatrix(gDisplayListHead++, (u32)&gMatrixBuffer->unk_0000[gMatrixBufferIdx] & 0x1FFFFFFF,
                  G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

        gMatrixBufferIdx++;
    }
}

void func_81401430(MtxF* arg0, s16 arg1, s16 arg2, s16 arg3, f32 arg4) {
    f32 temp_fv0 = SINS(arg3) * arg4;
    f32 temp_fv1 = COSS(arg3) * arg4;

    arg0->mf[0][0] = temp_fv1;
    arg0->mf[0][1] = -temp_fv0;
    arg0->mf[0][2] = 0.0f;
    arg0->mf[0][3] = 0.0f;

    arg0->mf[1][0] = temp_fv0;
    arg0->mf[1][1] = temp_fv1;
    arg0->mf[1][2] = 0.0f;
    arg0->mf[1][3] = 0.0f;

    arg0->mf[2][0] = 0.0f;
    arg0->mf[2][1] = 0.0f;
    arg0->mf[2][2] = 1.0f;
    arg0->mf[2][3] = 0.0f;

    arg0->mf[3][0] = arg1;
    arg0->mf[3][1] = arg2;
    arg0->mf[3][2] = 0.0f;
    arg0->mf[3][3] = 1.0f;
}

void func_814014E8(MtxF* arg0, s16 arg1, s16 arg2, s16 arg3, f32 arg4) {
    f32 temp_fv0 = SINS(arg3);
    f32 temp_fv1 = COSS(arg3);

    arg0->mf[0][0] = temp_fv1;
    arg0->mf[0][1] = -temp_fv0;
    arg0->mf[0][2] = 0.0f;
    arg0->mf[0][3] = 0.0f;

    arg0->mf[1][0] = temp_fv0 * arg4;
    arg0->mf[1][1] = temp_fv1 * arg4;
    arg0->mf[1][2] = 0.0f;
    arg0->mf[1][3] = 0.0f;

    arg0->mf[2][0] = 0.0f;
    arg0->mf[2][1] = 0.0f;
    arg0->mf[2][2] = 1.0f;
    arg0->mf[2][3] = 0.0f;

    arg0->mf[3][0] = arg1;
    arg0->mf[3][1] = arg2;
    arg0->mf[3][2] = 0.0f;
    arg0->mf[3][3] = 1.0f;
}

void Matrix_Submit2DRotateTranslateScale(s16 arg0, s16 arg1, s16 arg2, f32 arg3) {
    MtxF sp20;

    func_81401430(&sp20, arg0, arg1, arg2 + 0x8000, arg3);
    Matrix_SendToDisplayList(&sp20);
}

void Matrix_Submit2DRotateTranslateScaleY(s16 arg0, s16 arg1, s16 arg2, f32 arg3) {
    MtxF sp20;

    func_814014E8(&sp20, arg0, arg1, arg2 + 0x8000, arg3);
    Matrix_SendToDisplayList(&sp20);
}

void func_81401650(MtxF* arg0, Vec3f arg1, Vec3s arg2, f32 arg3) {
    f32 temp_fa1;
    f32 temp_fs0;
    f32 temp_fs1;
    f32 temp_ft4;
    f32 temp_fv0;
    f32 temp_fv1;

    temp_ft4 = SINS(arg2.x);
    temp_fv0 = COSS(arg2.x);

    temp_fv1 = SINS(arg2.y);
    temp_fa1 = COSS(arg2.y);

    temp_fs0 = SINS(arg2.z);
    temp_fs1 = COSS(arg2.z);

    arg0->mf[0][0] = ((temp_fa1 * temp_fs1) + (temp_ft4 * temp_fv1 * temp_fs0)) * arg3;
    arg0->mf[0][1] = temp_fv0 * temp_fs0 * arg3;
    arg0->mf[0][2] = ((-temp_fv1 * temp_fs1) + (temp_ft4 * temp_fa1 * temp_fs0)) * arg3;
    arg0->mf[0][3] = 0.0f;

    arg0->mf[1][0] = ((-temp_fa1 * temp_fs0) + (temp_ft4 * temp_fv1 * temp_fs1)) * arg3;
    arg0->mf[1][1] = temp_fv0 * temp_fs1 * arg3;
    arg0->mf[1][2] = ((temp_fv1 * temp_fs0) + (temp_ft4 * temp_fa1 * temp_fs1)) * arg3;
    arg0->mf[1][3] = 0.0f;

    arg0->mf[2][0] = temp_fv0 * temp_fv1 * arg3;
    arg0->mf[2][1] = -temp_ft4 * arg3;
    arg0->mf[2][2] = temp_fv0 * temp_fa1 * arg3;
    arg0->mf[2][3] = 0.0f;

    arg0->mf[3][0] = arg1.x;
    arg0->mf[3][1] = arg1.y;
    arg0->mf[3][2] = arg1.z;
    arg0->mf[3][3] = 1.0f;
}

void func_814017E0(MtxF* arg0, Vec3f arg1, Vec3s arg2, f32 arg3) {
    f32 temp_fa0;
    f32 temp_fa1;
    f32 temp_fs0;
    f32 temp_ft5;
    f32 temp_fv0;
    f32 temp_fv1;

    temp_fa1 = SINS(arg2.x);
    temp_fv0 = COSS(arg2.x);

    temp_fv1 = SINS(arg2.y);
    temp_fa0 = COSS(arg2.y);

    temp_ft5 = SINS(arg2.z);
    temp_fs0 = COSS(arg2.z);

    arg0->mf[0][0] = (temp_fa0 * temp_fs0) + (temp_fa1 * temp_fv1 * temp_ft5);
    arg0->mf[0][1] = temp_fv0 * temp_ft5;
    arg0->mf[0][2] = (-temp_fv1 * temp_fs0) + (temp_fa1 * temp_fa0 * temp_ft5);
    arg0->mf[0][3] = 0.0f;

    arg0->mf[1][0] = ((-temp_fa0 * temp_ft5) + (temp_fa1 * temp_fv1 * temp_fs0)) * arg3;
    arg0->mf[1][1] = temp_fv0 * temp_fs0 * arg3;
    arg0->mf[1][2] = ((temp_fv1 * temp_ft5) + (temp_fa1 * temp_fa0 * temp_fs0)) * arg3;
    arg0->mf[1][3] = 0.0f;

    arg0->mf[2][0] = temp_fv0 * temp_fv1;
    arg0->mf[2][1] = -temp_fa1;
    arg0->mf[2][2] = temp_fv0 * temp_fa0;
    arg0->mf[2][3] = 0.0f;

    arg0->mf[3][0] = arg1.x;
    arg0->mf[3][1] = arg1.y;
    arg0->mf[3][2] = arg1.z;
    arg0->mf[3][3] = 1.0f;
}

void func_81401940(MtxF* arg0, Vec3f arg1, Vec3s arg2, f32 arg3, f32 arg4) {
    f32 temp_fa0;
    f32 temp_fa1;
    f32 temp_fs0;
    f32 temp_ft5;
    f32 temp_fv0;
    f32 temp_fv1;

    temp_fa1 = SINS(arg2.x);
    temp_fv0 = COSS(arg2.x);

    temp_fv1 = SINS(arg2.y);
    temp_fa0 = COSS(arg2.y);

    temp_ft5 = SINS(arg2.z);
    temp_fs0 = COSS(arg2.z);

    arg0->mf[0][0] = ((temp_fa0 * temp_fs0) + (temp_fa1 * temp_fv1 * temp_ft5)) * arg3;
    arg0->mf[0][1] = temp_fv0 * temp_ft5 * arg3;
    arg0->mf[0][2] = ((-temp_fv1 * temp_fs0) + (temp_fa1 * temp_fa0 * temp_ft5)) * arg3;
    arg0->mf[0][3] = 0.0f;

    arg0->mf[1][0] = ((-temp_fa0 * temp_ft5) + (temp_fa1 * temp_fv1 * temp_fs0)) * arg4;
    arg0->mf[1][1] = temp_fv0 * temp_fs0 * arg4;
    arg0->mf[1][2] = ((temp_fv1 * temp_ft5) + (temp_fa1 * temp_fa0 * temp_fs0)) * arg4;
    arg0->mf[1][3] = 0.0f;

    arg0->mf[2][0] = temp_fv0 * temp_fv1;
    arg0->mf[2][1] = -temp_fa1;
    arg0->mf[2][2] = temp_fv0 * temp_fa0;
    arg0->mf[2][3] = 0.0f;

    arg0->mf[3][0] = arg1.x;
    arg0->mf[3][1] = arg1.y;
    arg0->mf[3][2] = arg1.z;
    arg0->mf[3][3] = 1.0f;
}

void Matrix_ComposeBillboard(MtxF* arg0, MtxF* arg1, Vec3f arg2, f32 arg3) {
    arg0->mf[0][0] = arg1->mf[0][0] * arg3;
    arg0->mf[0][1] = arg1->mf[1][0] * arg3;
    arg0->mf[0][2] = arg1->mf[2][0] * arg3;
    arg0->mf[0][3] = 0.0f;

    arg0->mf[1][0] = arg1->mf[0][1] * arg3;
    arg0->mf[1][1] = arg1->mf[1][1] * arg3;
    arg0->mf[1][2] = arg1->mf[2][1] * arg3;
    arg0->mf[1][3] = 0.0f;

    arg0->mf[2][0] = arg1->mf[0][2] * arg3;
    arg0->mf[2][1] = arg1->mf[1][2] * arg3;
    arg0->mf[2][2] = arg1->mf[2][2] * arg3;
    arg0->mf[2][3] = 0.0f;

    arg0->mf[3][0] = arg2.x;
    arg0->mf[3][1] = arg2.y;
    arg0->mf[3][2] = arg2.z;
    arg0->mf[3][3] = 1.0f;
}

void Matrix_ComposeBillboardY(MtxF* arg0, MtxF* arg1, Vec3f arg2, f32 arg3) {
    arg0->mf[0][0] = arg1->mf[0][0];
    arg0->mf[0][1] = arg1->mf[1][0];
    arg0->mf[0][2] = arg1->mf[2][0];
    arg0->mf[0][3] = 0.0f;

    arg0->mf[1][0] = arg1->mf[0][1] * arg3;
    arg0->mf[1][1] = arg1->mf[1][1] * arg3;
    arg0->mf[1][2] = arg1->mf[2][1] * arg3;
    arg0->mf[1][3] = 0.0f;

    arg0->mf[2][0] = arg1->mf[0][2];
    arg0->mf[2][1] = arg1->mf[1][2];
    arg0->mf[2][2] = arg1->mf[2][2];
    arg0->mf[2][3] = 0.0f;

    arg0->mf[3][0] = arg2.x;
    arg0->mf[3][1] = arg2.y;
    arg0->mf[3][2] = arg2.z;
    arg0->mf[3][3] = 1.0f;
}

void Matrix_ComposeBillboardRoll(MtxF* arg0, MtxF* arg1, Vec3f arg2, f32 arg3, s16 arg4) {
    f32 temp_fv0 = SINS(arg4);
    f32 temp_fv1 = COSS(arg4);

    arg0->mf[0][0] = ((arg1->mf[0][0] * temp_fv1) + (arg1->mf[0][1] * temp_fv0)) * arg3;
    arg0->mf[0][1] = ((arg1->mf[1][0] * temp_fv1) + (arg1->mf[1][1] * temp_fv0)) * arg3;
    arg0->mf[0][2] = ((arg1->mf[2][0] * temp_fv1) + (arg1->mf[2][1] * temp_fv0)) * arg3;
    arg0->mf[0][3] = 0.0f;

    arg0->mf[1][0] = ((arg1->mf[0][0] * -temp_fv0) + (arg1->mf[0][1] * temp_fv1)) * arg3;
    arg0->mf[1][1] = ((arg1->mf[1][0] * -temp_fv0) + (arg1->mf[1][1] * temp_fv1)) * arg3;
    arg0->mf[1][2] = ((arg1->mf[2][0] * -temp_fv0) + (arg1->mf[2][1] * temp_fv1)) * arg3;
    arg0->mf[1][3] = 0.0f;

    arg0->mf[2][0] = arg1->mf[0][2] * arg3;
    arg0->mf[2][1] = arg1->mf[1][2] * arg3;
    arg0->mf[2][2] = arg1->mf[2][2] * arg3;
    arg0->mf[2][3] = 0.0f;

    arg0->mf[3][0] = arg2.x;
    arg0->mf[3][1] = arg2.y;
    arg0->mf[3][2] = arg2.z;
    arg0->mf[3][3] = 1.0f;
}

void Matrix_ComposeBillboardRollY(MtxF* arg0, MtxF* arg1, Vec3f arg2, f32 arg3, s16 arg4) {
    f32 temp_fv0 = SINS(arg4);
    f32 temp_fv1 = COSS(arg4);

    arg0->mf[0][0] = (arg1->mf[0][0] * temp_fv1) + (arg1->mf[0][1] * temp_fv0);
    arg0->mf[0][1] = (arg1->mf[1][0] * temp_fv1) + (arg1->mf[1][1] * temp_fv0);
    arg0->mf[0][2] = (arg1->mf[2][0] * temp_fv1) + (arg1->mf[2][1] * temp_fv0);
    arg0->mf[0][3] = 0.0f;

    arg0->mf[1][0] = ((arg1->mf[0][0] * -temp_fv0) + (arg1->mf[0][1] * temp_fv1)) * arg3;
    arg0->mf[1][1] = ((arg1->mf[1][0] * -temp_fv0) + (arg1->mf[1][1] * temp_fv1)) * arg3;
    arg0->mf[1][2] = ((arg1->mf[2][0] * -temp_fv0) + (arg1->mf[2][1] * temp_fv1)) * arg3;
    arg0->mf[1][3] = 0.0f;

    arg0->mf[2][0] = arg1->mf[0][2];
    arg0->mf[2][1] = arg1->mf[1][2];
    arg0->mf[2][2] = arg1->mf[2][2];
    arg0->mf[2][3] = 0.0f;

    arg0->mf[3][0] = arg2.x;
    arg0->mf[3][1] = arg2.y;
    arg0->mf[3][2] = arg2.z;
    arg0->mf[3][3] = 1.0f;
}

void func_81401E84(MtxF* arg0, Vec3f arg1, Vec3f arg2, s16 arg3, f32 arg4) {
    Vec3f sp3C;
    Vec3f sp30;
    Vec3f sp24;

    Vec3f_Set(&sp3C, SINS(arg3), 0.0f, COSS(arg3));
    Vec3f_Normalize(&arg1);
    Vec3f_CrossProduct(&sp30, &arg1, &sp3C);
    Vec3f_Normalize(&sp30);
    Vec3f_CrossProduct(&sp24, &sp30, &arg1);
    Vec3f_Normalize(&sp24);

    arg0->mf[0][0] = sp30.x * arg4;
    arg0->mf[0][1] = sp30.y * arg4;
    arg0->mf[0][2] = sp30.z * arg4;
    arg0->mf[3][0] = arg2.x;

    arg0->mf[1][0] = arg1.x * arg4;
    arg0->mf[1][1] = arg1.y * arg4;
    arg0->mf[1][2] = arg1.z * arg4;
    arg0->mf[3][1] = arg2.y;

    arg0->mf[2][0] = sp24.x * arg4;
    arg0->mf[2][1] = sp24.y * arg4;
    arg0->mf[2][2] = sp24.z * arg4;
    arg0->mf[3][2] = arg2.z;

    arg0->mf[0][3] = 0.0f;
    arg0->mf[1][3] = 0.0f;
    arg0->mf[2][3] = 0.0f;
    arg0->mf[3][3] = 1.0f;
}

void Matrix_SubmitRotateTranslateScale(Vec3f arg0, Vec3s arg1, f32 arg2) {
    MtxF sp28;

    func_81401650(&sp28, arg0, arg1, arg2);
    Matrix_SendToDisplayList(&sp28);
}

void Matrix_SubmitRotateTranslateScaleY(Vec3f arg0, Vec3s arg1, f32 arg2) {
    MtxF sp28;

    func_814017E0(&sp28, arg0, arg1, arg2);
    Matrix_SendToDisplayList(&sp28);
}

void Matrix_SubmitRotateTranslateScaleXY(Vec3f arg0, Vec3s arg1, f32 arg2, f32 arg3) {
    MtxF sp28;

    func_81401940(&sp28, arg0, arg1, arg2, arg3);
    Matrix_SendToDisplayList(&sp28);
}

void Matrix_SubmitBillboard(CameraStruct* arg0, Vec3f arg1, f32 arg4) {
    MtxF sp20;

    Matrix_ComposeBillboard(&sp20, &arg0->unk_60.mtxf, arg1, arg4);
    Matrix_SendToDisplayList(&sp20);
}

void Matrix_SubmitBillboardRoll(CameraStruct* arg0, Vec3f arg1, f32 arg4, s16 arg5) {
    MtxF sp28;

    Matrix_ComposeBillboardRoll(&sp28, &arg0->unk_60.mtxf, arg1, arg4, arg5);
    Matrix_SendToDisplayList(&sp28);
}

void Matrix_SubmitBillboardY(CameraStruct* arg0, Vec3f arg1, f32 arg4) {
    MtxF sp20;

    Matrix_ComposeBillboardY(&sp20, &arg0->unk_60.mtxf, arg1, arg4);
    Matrix_SendToDisplayList(&sp20);
}

void Matrix_SubmitBillboardRollY(CameraStruct* arg0, Vec3f arg1, f32 arg4, s16 arg5) {
    MtxF sp28;

    Matrix_ComposeBillboardRollY(&sp28, &arg0->unk_60.mtxf, arg1, arg4, arg5);
    Matrix_SendToDisplayList(&sp28);
}

void func_814022EC(Vec3f arg0, Vec3s arg3, f32 arg5) {
    MtxF sp30;
    Vec3s sp28;

    sp28.x = arg3.x + 0x8000;
    sp28.y = arg3.y + 0x8000;
    sp28.z = arg3.z;

    func_81401650(&sp30, arg0, sp28, arg5);
    Matrix_SendToDisplayList(&sp30);
}

void func_8140238C(Vec3f arg0, Vec3f arg3, f32 arg6) {
    MtxF sp30;

    func_81401E84(&sp30, arg3, arg0, 0, arg6);
    Matrix_SendToDisplayList(&sp30);
}
