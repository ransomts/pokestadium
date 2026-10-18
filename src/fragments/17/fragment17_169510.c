#include "fragment17.h"

void Matrix_ConvertFloatToFixed(Mtx* arg0, MtxF* arg1) {
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

void Matrix_ScaleUniform(MtxF* arg0, f32 arg1) {
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

void Matrix_SetTransformFromPosRot(MtxF* arg0, Vec3f arg1, Vec3s arg2) {
    UNUSED s32 pad[2];
    f32 sx = SINS(arg2.x);
    f32 cx = COSS(arg2.x);
    f32 sy = SINS(arg2.y);
    f32 cy = COSS(arg2.y);
    f32 sz = SINS(arg2.z);
    f32 cz = COSS(arg2.z);

    arg0->mf[0][0] = (cy * cz) + (sx * sy * sz);
    arg0->mf[1][0] = (-cy * sz) + (sx * sy * cz);
    arg0->mf[2][0] = cx * sy;
    arg0->mf[3][0] = arg1.x;

    arg0->mf[0][1] = cx * sz;
    arg0->mf[1][1] = cx * cz;
    arg0->mf[2][1] = -sx;
    arg0->mf[3][1] = arg1.y;

    arg0->mf[0][2] = (-sy * cz) + (sx * cy * sz);
    arg0->mf[1][2] = (sy * sz) + (sx * cy * cz);
    arg0->mf[2][2] = cx * cy;
    arg0->mf[3][2] = arg1.z;

    arg0->mf[0][3] = arg0->mf[1][3] = arg0->mf[2][3] = 0.0f;
    arg0->mf[3][3] = 1.0f;
}
