#include "17300.h"
#include "src/util.h"
#include "src/F420.h"
#include "src/18140.h"

typedef struct unk_func_80016B30_arg0 {
    /* 0x00 */ Vec3s vec;
    /* 0x06 */ s16 unk_06;
} unk_func_80016B30_arg0; // size = 0x8

static unk_D_800ABCC0 gAnimChannels[2];
static s32 gCurrentAnimChannelIdx;

f32 Anim_GetScalar(unk_D_800ABCC0* arg0, s32 arg1) {
    f32 ret;
    s32 var_a2;
    unk_D_800ABCC0_008* temp_v0 = &arg0->unk_08[arg1];

    if (temp_v0->unk_00 == 1) {
        ret = temp_v0->unk_04 / 1000.0f;
    } else {
        if (arg0->unk_02 < temp_v0->unk_00) {
            var_a2 = temp_v0->unk_04 + arg0->unk_02;
        } else {
            var_a2 = (temp_v0->unk_04 + temp_v0->unk_00) - 1;
        }

        ret = arg0->unk_0C[var_a2] / 1000.0f;
    }

    return ret;
}

s16 Anim_GetRotation(unk_D_800ABCC0* arg0, s32 arg1) {
    s32 var_a1;
    s16 var_v1;
    unk_D_800ABCC0_008* temp_v0 = &arg0->unk_08[arg1];

    if (temp_v0->unk_01 == 1) {
        var_v1 = temp_v0->unk_06 * 0x10;
    } else {
        if (arg0->unk_02 < temp_v0->unk_01) {
            var_a1 = temp_v0->unk_06 + arg0->unk_02;
        } else {
            var_a1 = (temp_v0->unk_06 + temp_v0->unk_01) - 1;
        }
        var_v1 = func_80010500(arg0->unk_10, var_a1, 0xC) * 0x10;
    }
    return var_v1;
}

f32 Anim_GetPosition(unk_D_800ABCC0* arg0, s32 arg1) {
    f32 var_fv1;
    s16 var_a2;
    s32 var_a1;
    unk_D_800ABCC0_008* temp_v0 = &arg0->unk_08[arg1];

    if (temp_v0->unk_02 == 1) {
        if (arg0->unk_01 & 4) {
            var_fv1 = (s16)temp_v0->unk_08;
        } else {
            var_a2 = temp_v0->unk_08 * 0x10;
            var_fv1 = var_a2 >> 4;
        }
    } else {
        if (arg0->unk_02 < temp_v0->unk_02) {
            var_a1 = temp_v0->unk_08 + arg0->unk_02;
        } else {
            var_a1 = (temp_v0->unk_08 + temp_v0->unk_02) - 1;
        }

        if (arg0->unk_01 & 4) {
            var_fv1 = func_80010500(arg0->unk_14, var_a1, 0x10);
        } else {
            var_fv1 = func_80010500(arg0->unk_14, var_a1, 0xC);
        }
    }

    return var_fv1;
}

f32 Anim_InterpolateCubic(Vec3s* arg0, s16 arg1, s16 arg2) {
    f32 y;
    s32 i;
    f32 x;
    f32 var_fv1;

    if (arg0->x >= arg2) {
        var_fv1 = arg0->y;
    } else {
        if (arg2 >= arg0[arg1 - 1].x) {
            var_fv1 = arg0[arg1 - 1].y;
        } else {
            for (i = 0; i < arg1 - 2; i++) {
                if (arg2 < arg0[i + 1].x) {
                    break;
                }
            }

            x = (arg2 - arg0[i].x) / 30.0f;
            y = 30.0f / (arg0[i + 1].x - arg0[i].x);

            var_fv1 = (arg0[i].y * (((2.0f * x * x * x * y * y * y) - 3.0f * x * x * y * y) + 1.0f))
                    + (arg0[i + 1].y * ((-2.0f * x * x * x * y * y * y) + 3.0f * x * x * y * y))
                    + (arg0[i].z * ((x * x * x * y * y - (2.0f * x * x * y)) + x))
                    + (arg0[i + 1].z * (x * x * x * y * y - (x * x * y)));
        }
    }
    return var_fv1;
}

f32 Anim_InterpolateCubicVec(unk_func_80016B30_arg0* arg0, s16 arg1, s16 arg2) {
    f32 y;
    s32 i;
    f32 x;
    f32 var_fv1;

    if (arg0->vec.x >= arg2) {
        var_fv1 = arg0->vec.y;
    } else {
        if (arg2 >= arg0[arg1 - 1].vec.x) {
            var_fv1 = arg0[arg1 - 1].vec.y;
        } else {
            for (i = 0; i < arg1 - 2; i++) {
                if (arg2 < arg0[i + 1].vec.x) {
                    break;
                }
            }

            x = (arg2 - arg0[i].vec.x) / 30.0f;
            y = 30.0f / (arg0[i + 1].vec.x - arg0[i].vec.x);

            var_fv1 = (arg0[i].vec.y * (((2.0f * x * x * x * y * y * y) - 3.0f * x * x * y * y) + 1.0f))
                    + (arg0[i + 1].vec.y * ((-2.0f * x * x * x * y * y * y) + 3.0f * x * x * y * y))
                    + (arg0[i].unk_06 * ((x * x * x * y * y - (2.0f * x * x * y)) + x))
                    + (arg0[i + 1].vec.z * (x * x * x * y * y - (x * x * y)));
        }
    }
    return var_fv1;
}

f32 Anim_GetScaleInterpolated(unk_D_800ABCC0* arg0, s32 arg1) {
    f32 var_fv1;
    unk_D_800ABCC0_008* temp_v0 = &arg0->unk_08[arg1];
    s16* tmp;

    if (temp_v0->unk_00 < 2) {
        var_fv1 = (s16)temp_v0->unk_04 / 100.0f;
    } else {
        tmp = &arg0->unk_0C[temp_v0->unk_04];
        if (temp_v0->unk_03 & 4) {
            var_fv1 = Anim_InterpolateCubicVec(tmp, temp_v0->unk_00, arg0->unk_02) / 100.0f;
        } else {
            var_fv1 = Anim_InterpolateCubic(tmp, temp_v0->unk_00, arg0->unk_02) / 100.0f;
        }
    }
    return var_fv1;
}

s16 Anim_GetRotationInterpolated(unk_D_800ABCC0* arg0, s32 arg1) {
    f32 var_fv1;
    s16* temp_a0;
    unk_D_800ABCC0_008* temp_v0 = &arg0->unk_08[arg1];

    if (temp_v0->unk_01 < 2) {
        var_fv1 = (s16)temp_v0->unk_06 / 10.0f;
    } else {
        temp_a0 = &arg0->unk_10[temp_v0->unk_06];
        if (temp_v0->unk_03 & 2) {
            var_fv1 = Anim_InterpolateCubicVec(temp_a0, temp_v0->unk_01, arg0->unk_02) / 10.0f;
        } else {
            var_fv1 = Anim_InterpolateCubic(temp_a0, temp_v0->unk_01, arg0->unk_02) / 10.0f;
        }
    }

    while (var_fv1 < 0.0f) {
        var_fv1 += 360.0f;
    }

    while (var_fv1 >= 360.0f) {
        var_fv1 -= 360.0f;
    }

    return (var_fv1 / 360.0f) * 65536.0f;
}

f32 Anim_GetPositionInterpolated(unk_D_800ABCC0* arg0, s32 arg1) {
    s16* temp_a0;
    f32 var_fv0;
    f32 var_fv1;
    unk_D_800ABCC0_008* temp_v0 = &arg0->unk_08[arg1];

    if (temp_v0->unk_02 < 2) {
        var_fv1 = (s16)temp_v0->unk_08;
    } else {
        temp_a0 = &arg0->unk_14[temp_v0->unk_08];
        if (temp_v0->unk_03 & 1) {
            var_fv0 = Anim_InterpolateCubicVec(temp_a0, temp_v0->unk_02, arg0->unk_02);
        } else {
            var_fv0 = Anim_InterpolateCubic(temp_a0, temp_v0->unk_02, arg0->unk_02);
        }
        var_fv1 = var_fv0;
    }
    return var_fv1;
}

typedef union unk_D_86002F58_004_000_040_raw_08 {
    struct {
        s16 unk_00;
        s16 unk_02;
    };
    s32 raw;
} unk_D_86002F58_004_000_040_raw_08; // size = 0x4

typedef struct unk_D_86002F58_004_000_040_raw {
    /* 0x00 */ s16 unk_00;
    /* 0x04 */ unk_D_86002F58_004_000_040_004* unk_04;
    /* 0x08 */ unk_D_86002F58_004_000_040_raw_08 unk_08;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ char unk10[0x2];
    /* 0x12 */ u16 unk_12;
} unk_D_86002F58_004_000_040_raw; // size >= 0x14

s32 Anim_ComputeKeyframeIndex(unk_D_86002F58_004_000_040_raw* arg0, u16 arg1) {
    unk_D_86002F58_004_000_040_raw_08 spC;
    unk_D_86002F58_004_000_040_raw_08* ptr;
    unk_D_86002F58_004_000_040_004* temp_v0;

    ptr = &spC;
    temp_v0 = arg0->unk_04;
    spC.raw = arg0->unk_08.raw;
    if (arg0->unk_12 != arg1) {
        spC.raw += arg0->unk_0C;
        if (arg0->unk_0C >= 0) {
            if (ptr->unk_00 >= temp_v0->unk_0A) {
                if (temp_v0->unk_00 & 2) {
                    ptr->unk_00 = temp_v0->unk_0A - 1;
                } else {
                    ptr->unk_00 = temp_v0->unk_06;
                }
            }
        } else {
            if (ptr->unk_00 < temp_v0->unk_06) {
                if (temp_v0->unk_00 & 2) {
                    ptr->unk_00 = temp_v0->unk_06;
                } else {
                    ptr->unk_00 = temp_v0->unk_0A - 1;
                }
            }
        }
    }

    return spC.raw;
}

void Anim_ResetChannelIndex(void) {
    gCurrentAnimChannelIdx = -1;
}

void Anim_StartChannel(unk_D_86002F58_004_000_040* arg0, u16 arg1, s32 arg2) {
    unk_D_86002F58_004_000_040_004* temp_s1;
    unk_D_800ABCC0* temp_s0;

    temp_s1 = arg0->unk_04;

    gCurrentAnimChannelIdx++;
    if (gCurrentAnimChannelIdx < 2) {
        temp_s0 = &gAnimChannels[gCurrentAnimChannelIdx];
        if (arg0->unk_04 != NULL) {
            if (arg2 != 0) {
                arg0->unk_08 = Anim_ComputeKeyframeIndex(arg0, arg1);
            }

            arg0->unk_12 = arg1;

            temp_s0->unk_00 = 1;
            temp_s0->unk_01 = arg0->unk_04->unk_00;
            temp_s0->unk_02 = arg0->unk_08 >> 0x10;
            temp_s0->unk_04 = temp_s1;
            temp_s0->unk_08 = Util_ConvertAddrToVirtAddr(temp_s1->unk_0C);
            temp_s0->unk_0C = Util_ConvertAddrToVirtAddr(temp_s1->unk_10);
            temp_s0->unk_10 = Util_ConvertAddrToVirtAddr(temp_s1->unk_14);
            temp_s0->unk_14 = Util_ConvertAddrToVirtAddr(temp_s1->unk_18);

            if (temp_s0->unk_02 < 0) {
                temp_s0->unk_02 = 0;
            }
        } else {
            temp_s0->unk_00 = 0;
        }
    }
}

void Anim_EndChannel(void) {
    if (gCurrentAnimChannelIdx >= 0) {
        gCurrentAnimChannelIdx--;
    }
}

void Anim_GetTransformTriple(Vec3f* arg0, Vec3s* arg1, Vec3f* arg2, s32 arg3) {
    if ((gCurrentAnimChannelIdx >= 0) && (gCurrentAnimChannelIdx < 2)) {
        unk_D_800ABCC0* temp_s0 = &gAnimChannels[gCurrentAnimChannelIdx];

        if ((temp_s0->unk_00 == 1) && (arg3 >= 0) && (arg3 + 2 < temp_s0->unk_04->unk_08)) {
            if (temp_s0->unk_01 & 8) {
                arg0->x = Anim_GetPositionInterpolated(temp_s0, arg3 + 0);
                arg0->y = Anim_GetPositionInterpolated(temp_s0, arg3 + 1);
                arg0->z = Anim_GetPositionInterpolated(temp_s0, arg3 + 2);

                arg1->x = Anim_GetRotationInterpolated(temp_s0, arg3 + 0);
                arg1->y = Anim_GetRotationInterpolated(temp_s0, arg3 + 1);
                arg1->z = Anim_GetRotationInterpolated(temp_s0, arg3 + 2);

                arg2->x = Anim_GetScaleInterpolated(temp_s0, arg3 + 0);
                arg2->y = Anim_GetScaleInterpolated(temp_s0, arg3 + 1);
                arg2->z = Anim_GetScaleInterpolated(temp_s0, arg3 + 2);
            } else {
                arg0->x = Anim_GetPosition(temp_s0, arg3 + 0);
                arg0->y = Anim_GetPosition(temp_s0, arg3 + 1);
                arg0->z = Anim_GetPosition(temp_s0, arg3 + 2);

                arg1->x = Anim_GetRotation(temp_s0, arg3 + 0);
                arg1->y = Anim_GetRotation(temp_s0, arg3 + 1);
                arg1->z = Anim_GetRotation(temp_s0, arg3 + 2);

                arg2->x = Anim_GetScalar(temp_s0, arg3 + 0);
                arg2->y = Anim_GetScalar(temp_s0, arg3 + 1);
                arg2->z = Anim_GetScalar(temp_s0, arg3 + 2);
            }
        }
    }
}

void Anim_ClearChannelState(Fragment2_1GraphNode* arg0) {
    arg0->unk_040.unk_00 = -1;
    arg0->unk_040.unk_04 = NULL;
}

s32 Anim_SetChannel(Fragment2_1GraphNode* arg0, s16 arg1, void* arg2, s32 arg3) {
    unk_D_86002F58_004_000_040_004* temp_v0 = Util_ConvertAddrToVirtAddr(arg2);
    unk_D_86002F58_004_000_040* ptr = &arg0->unk_040;

    if ((temp_v0 != ptr->unk_04) || (arg1 != ptr->unk_00)) {
        ptr->unk_00 = arg1;
        ptr->unk_04 = temp_v0;
        ptr->unk_08 = (temp_v0->unk_04 << 0x10) - arg3;
    }

    ptr->unk_0C = arg3;
    return ptr->unk_08 >> 0x10;
}

s32 Anim_SetChannelOffset(Fragment2_1GraphNode* arg0, s32 arg1) {
    arg0->unk_040.unk_0C = arg1;
    return arg0->unk_040.unk_08 >> 0x10;
}

void Anim_SetChannelBase(Fragment2_1GraphNode* arg0, s16 arg1) {
    arg0->unk_040.unk_08 = (arg1 << 0x10) - arg0->unk_040.unk_0C;
}

s32 Anim_IsFrameInRange(Fragment2_1GraphNode* arg0, s16 arg1) {
    unk_D_86002F58_004_000_040* ptr = &arg0->unk_040;
    s32 temp_v0 = ptr->unk_08 + ptr->unk_0C;
    s32 arg = arg1 << 0x10;
    s32 var_a2;
    s32 v = ptr->unk_0C;

    if (v >= 0) {
        var_a2 = ptr->unk_08 < arg;
        if (var_a2 != 0) {
            var_a2 = temp_v0 >= arg;
        }
    } else {
        var_a2 = (arg < ptr->unk_08);
        if (var_a2 != 0) {
            var_a2 = arg >= temp_v0;
        }
    }

    return var_a2;
}

s32 GraphNode_IsAnimationFinished(Fragment2_1GraphNode* arg0) {
    return Anim_IsFrameInRange(arg0, arg0->unk_040.unk_04->unk_0A - 1);
}

s32 Anim_HasReachedEnd(Fragment2_1GraphNode* arg0) {
    return arg0->unk_040.unk_08 >= ((arg0->unk_040.unk_04->unk_0A - 1) << 0x10);
}
