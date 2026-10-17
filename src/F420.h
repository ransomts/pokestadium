#ifndef _F420_H_
#define _F420_H_

#include "global.h"

extern Vec3f gRootNodePosition;
extern Vec3s gSpriteAnimUpdateFunc;
extern Vec3f gRootNodeScale;
extern u16 D_8006F070[];

Color_RGBA8* GfxColor_SetRGB(Color_RGBA8* arg0, u8 r, u8 g, u8 b);
Color_RGBA8* GfxColor_SetRGBA(Color_RGBA8* arg0, u8 arg1, u8 arg2, u8 arg3, u8 arg4);
Vec3f* Vec3f_SetXYZ(Vec3f* arg0, f32 arg1, f32 arg2, f32 arg3);
Vec3f* Vec3f_Set(Vec3f* arg0, f32 arg1, f32 arg2, f32 arg3);
Vec3f* Vec3f_Add(Vec3f* arg0, Vec3f* arg1);
Vec3f* Vec3f_Sum(Vec3f* arg0, Vec3f* arg1, Vec3f* arg2);
Vec3f* Vec3f_Subtract(Vec3f* arg0, Vec3f* arg1);
Vec3f* func_8000E958(Vec3f* arg0, Vec3f* arg1, Vec3f* arg2);
Vec3f* GraphNode_SetPositionFromVec3s(Vec3f* arg0, Vec3s* arg1);
Vec3f* func_8000E9D4(Vec3f* arg0, Vec3f* arg1, Vec3f* arg2, Vec3f* arg3);
Vec3f* Vec3f_CrossProduct(Vec3f* arg0, Vec3f* arg1, Vec3f* arg2);
Vec3f* Vec3f_Normalize(Vec3f* arg0);
Vec3s* Vec3s_Set(Vec3s* arg0, s16 arg1, s16 arg2, s16 arg3);
Vec3s* Vec3s_Add(Vec3s* arg0, Vec3s* arg1);
Vec3s* Vec3s_Sum(Vec3s* arg0, Vec3s* arg1, Vec3s* arg2);
Vec3s* Vec3s_Subtract(Vec3s* arg0, Vec3s* arg1);
Vec3s* func_8000EC50(Vec3s* arg0, Vec3s* arg1, Vec3s* arg2);
Vec3s* Vec3s_FromVec3f_Round(Vec3s* arg0, Vec3f* arg1);
void Matrix_Copy(MtxF* dest, MtxF* src);
void Matrix_Identity(MtxF* arg0);
void Matrix_FromTranslation(MtxF* arg0, Vec3f* arg1);
void Matrix_LookAtBetween(MtxF* mtx, Vec3f* from, Vec3f* to, u16 roll);
void Matrix_FromSRT(MtxF* dest, Vec3s* translate, Vec3s* rotate);
void Matrix_RotateTranslate(MtxF* arg0, Vec3f* arg1, Vec3s* arg2);
void Matrix_RotateTranslateScale(MtxF* arg0, Vec3f* arg1, Vec3s* arg2);
void Matrix_TransformPoint(MtxF* dest, Vec3f* b, Vec3s* c, Vec3f* arg3);
void Matrix_TransformPointScale(MtxF* dest, Vec3f* b, Vec3s* c, Vec3f* arg3);
void Matrix_ComposeTR(MtxF* arg0, MtxF* arg1, MtxF* arg2, Vec3f* arg3, f32 arg4);
void Matrix_LookAtYaw(MtxF* dest, Vec3f* upDir, Vec3f* pos, s16 yaw);
void Matrix_Multiply(MtxF* arg0, MtxF* arg1, MtxF* arg2);
void Matrix_Scale(MtxF* dest, MtxF* mtx, Vec3f* s);
void Matrix_GetScale(MtxF* arg0, Vec3f* arg1);
void Matrix_TransformVec3sInPlace(MtxF* arg0, Vec3s* arg1);
void Matrix_ConvertToMtx(MtxF* dest, MtxF* src);
void Matrix_BuildObjectTransform(MtxF* arg0, Vec3f* arg1, Vec3s* arg2, Vec3f* arg3, MtxF* arg4, MtxF* arg5);
void Matrix_Decompose(Vec3f* arg0, Vec3f* arg1, f32* arg2, s16* arg3, s16* arg4);
void Camera_SetViewParameters(Vec3f* from, Vec3f* to, f32 dist, s16 pitch, s16 yaw);
s16 Math_ApproachS16(s16 current, s16 target, s16 inc);
s32 Math_ApproachS32(s32 current, s32 target, s32 inc, s32 dec);
f32 Math_ApproachF32(f32 current, f32 target, f32 inc, f32 dec);
s16 func_80010500(s16* arg0, s32 arg1, s32 arg2);
void RGB_ToHSV(f32 arg0, f32 arg1, f32 arg2, Vec3f* arg3);
void func_80010720(Color_RGBA8_u32 arg0, Vec3f* arg1);
void func_80010780(u16 arg0, Vec3f* arg1);
f32 func_800107F0(f32 arg0, f32 arg1, f32 arg2);
void HSV_ToRGB(f32* arg0, f32* arg1, f32* arg2, Vec3f* arg3);
u16 func_80010B20(Vec3f* arg0);
Color_RGBA8_u32* func_80010BD4(Color_RGBA8_u32* arg0, Vec3f* arg1, s32 arg2);
u16 func_80010CA8(u16 arg0, arg1_func_80010CA8 arg1);
u32 func_80010E20(u32 arg0, arg1_func_80010CA8 arg1);

#endif // _F420_H_
