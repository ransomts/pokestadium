#include "fragment17.h"

void func_86B09B80(Mtx* arg0, MtxF* arg1) {
    arg0->m[0][0] =
        ((s32)(arg1->mf[0][0] * 65536.0f) & 0xFFFF0000) | (((s32)(arg1->mf[0][1] * 65536.0f) >> 0x10) & 0xFFFF);
    arg0->m[0][1] =
        ((s32)(arg1->mf[0][2] * 65536.0f) & 0xFFFF0000) | (((s32)(arg1->mf[0][3] * 65536.0f) >> 0x10) & 0xFFFF);
    arg0->m[0][2] =
        ((s32)(arg1->mf[1][0] * 65536.0f) & 0xFFFF0000) | (((s32)(arg1->mf[1][1] * 65536.0f) >> 0x10) & 0xFFFF);
    arg0->m[0][3] =
        ((s32)(arg1->mf[1][2] * 65536.0f) & 0xFFFF0000) | (((s32)(arg1->mf[1][3] * 65536.0f) >> 0x10) & 0xFFFF);
    arg0->m[1][0] =
        ((s32)(arg1->mf[2][0] * 65536.0f) & 0xFFFF0000) | (((s32)(arg1->mf[2][1] * 65536.0f) >> 0x10) & 0xFFFF);
    arg0->m[1][1] =
        ((s32)(arg1->mf[2][2] * 65536.0f) & 0xFFFF0000) | (((s32)(arg1->mf[2][3] * 65536.0f) >> 0x10) & 0xFFFF);
    arg0->m[1][2] =
        ((s32)(arg1->mf[3][0] * 65536.0f) & 0xFFFF0000) | (((s32)(arg1->mf[3][1] * 65536.0f) >> 0x10) & 0xFFFF);
    arg0->m[1][3] =
        ((s32)(arg1->mf[3][2] * 65536.0f) & 0xFFFF0000) | (((s32)(arg1->mf[3][3] * 65536.0f) >> 0x10) & 0xFFFF);
    arg0->m[2][0] = ((s32)(arg1->mf[0][0] * 65536.0f) << 0x10) | ((s32)(arg1->mf[0][1] * 65536.0f) & 0xFFFF);
    arg0->m[2][1] = ((s32)(arg1->mf[0][2] * 65536.0f) << 0x10) | ((s32)(arg1->mf[0][3] * 65536.0f) & 0xFFFF);
    arg0->m[2][2] = ((s32)(arg1->mf[1][0] * 65536.0f) << 0x10) | ((s32)(arg1->mf[1][1] * 65536.0f) & 0xFFFF);
    arg0->m[2][3] = ((s32)(arg1->mf[1][2] * 65536.0f) << 0x10) | ((s32)(arg1->mf[1][3] * 65536.0f) & 0xFFFF);
    arg0->m[3][0] = ((s32)(arg1->mf[2][0] * 65536.0f) << 0x10) | ((s32)(arg1->mf[2][1] * 65536.0f) & 0xFFFF);
    arg0->m[3][1] = ((s32)(arg1->mf[2][2] * 65536.0f) << 0x10) | ((s32)(arg1->mf[2][3] * 65536.0f) & 0xFFFF);
    arg0->m[3][2] = ((s32)(arg1->mf[3][0] * 65536.0f) << 0x10) | ((s32)(arg1->mf[3][1] * 65536.0f) & 0xFFFF);
    arg0->m[3][3] = ((s32)(arg1->mf[3][2] * 65536.0f) << 0x10) | ((s32)(arg1->mf[3][3] * 65536.0f) & 0xFFFF);
}

void func_86B09EF0(MtxF* arg0, f32 arg1) {
    arg0->mf[0][0] *= arg1;
    arg0->mf[1][0] *= arg1;
    arg0->mf[2][0] *= arg1;

    arg0->mf[0][1] *= arg1;
    arg0->mf[1][1] *= arg1;
    arg0->mf[2][1] *= arg1;

    arg0->mf[0][2] *= arg1;
    arg0->mf[1][2] *= arg1;
    arg0->mf[2][2] *= arg1;
}

#ifdef NON_MATCHING
// Stack frame and instruction mix match; FPU register allocation of the six sin/cos values differs.
void func_86B09F64(MtxF* arg0, Vec3f arg1, Vec3s arg2) {
    f32 temp[10];
    f32 sx = SINS(arg2.x);
    f32 sy = SINS(arg2.y);
    f32 cy;
    f32 cz;
    f32 cx;
    f32 sz;

    temp[0] = sx * sy;
    cy = COSS(arg2.y);
    cz = COSS(arg2.z);
    cx = COSS(arg2.x);
    sz = SINS(arg2.z);

    arg0->mf[0][0] = (cy * cz) + (temp[0] * sz);
    arg0->mf[1][0] = (-cy * sz) + (temp[0] * cz);
    arg0->mf[2][0] = cx * sy;
    arg0->mf[3][0] = arg1.x;

    arg0->mf[0][1] = cx * sz;
    arg0->mf[2][1] = -sx;
    arg0->mf[1][1] = cx * cz;
    arg0->mf[3][1] = arg1.y;

    temp[0] = sx * cy;
    arg0->mf[0][2] = (-sy * cz) + (temp[0] * sz);
    arg0->mf[1][2] = (sy * sz) + (temp[0] * cz);
    arg0->mf[2][2] = cx * cy;
    arg0->mf[3][2] = arg1.z;

    arg0->mf[0][3] = 0.0f;
    arg0->mf[1][3] = 0.0f;
    arg0->mf[2][3] = 0.0f;
    arg0->mf[3][3] = 1.0f;
}
#else
#pragma GLOBAL_ASM("asm/us/nonmatchings/fragments/17/fragment17_169510/func_86B09F64.s")
#endif
