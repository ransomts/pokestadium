#include "fragment62.h"
#include "src/30640.h"
#include "src/6A40.h"
#include "include/math.h"
#include "src/math_util.h"

u8* gWaterTexture[256];
s16 gMessageBuffer[0x10];
arg1_func_80019420* gMessageStringLists[40];
static s16 gEffectPhaseCounterA;
static s16 gEffectPhaseCounterB;
static Mtx gEffectMatrix;
static s16 gParticleSpawnTimerI;
static s16 gParticleSpawnTimerD0;
static s16 gParticleSpawnTimerH;
static s16 gParticleSpawnTimerA;
static s16 gParticleSpawnTimerB;
static s16 gParticleSpawnTimerC;
static s16 gParticleSpawnTimerD;
static s16 gParticleSpawnTimerE;
static s16 gParticleSpawnTimerF;
static s16 gParticleSpawnTimerG;

static const char gCalcVectorATtoDMErrorMsg[] = "calc_vector_ATtoDM() normal error!!!\n";
static const char gCalcVectorATtoDM2ErrorMsg[] = "calc_vector_ATtoDM2() normal error!!!\n";

void func_843592E0(void) {
}

void func_843592E8(void) {
}

void func_843592F0(void) {
}

void func_843592F8(void) {
}

void func_84359300(void) {
}

void func_84359308(void) {
}

void func_84359310(void) {
}

void func_84359318(void) {
}

void func_84359320(void) {
}

void func_84359328(void) {
}

void func_84359330(UNUSED s32 arg0) {
}

void func_84359338(UNUSED s32 arg0) {
}

void func_84359340(void) {
}

void func_84359348(void) {
    RenderPrimColorRect(gSavedPrimColorR, gSavedPrimColorG, gSavedPrimColorB, 0xFF);
}

void func_84359380(void) {
    GlowEmitters_Reset();
}

void func_843593A0(void) {
}

void func_843593A8(void) {
}

s32 func_843593B0(void) {
    return -1;
}

s32 func_843593B8(void) {
    return -1;
}

void func_843593C0(void) {
}

void func_843593C8(void) {
}

void func_843593D0(Vec3f* arg0) {
    GetSecondaryEntityNodePosition(arg0);
}

void func_843593F0(Vec3f* arg0) {
    GetPrimaryEffectCenterOrNode(arg0);
}

void func_84359410(Vec3f* arg0) {
    GetSecondaryEntityNodePosition(arg0);
}

void func_84359430(Vec3f* arg0) {
    GetPrimaryEffectNodePosition(arg0);
}

f32 func_84359450(void) {
    return GetSecondaryEntityScale();
}

f32 func_84359470(void) {
    return GetPrimaryEntityScale();
}

void CalcVectorATtoDM(f32* arg0, f32* arg1, f32* arg2, f32* arg3, f32* arg4, f32* arg5) {
    Vec3f sp4C;
    Vec3f sp40;
    f32 sp3C;
    f32 sp38;
    f32 sp34;
    UNUSED s32 pad[3];
    f32 sp24;
    f32 sp20;
    f32 sp1C;

    func_843593F0(&sp4C);
    func_84359410(&sp40);

    sp3C = sp4C.x;
    sp38 = sp4C.y;
    sp34 = sp4C.z;

    sp24 = sp40.x - sp4C.x;
    sp20 = sp40.y - sp4C.y;
    sp1C = sp40.z - sp4C.z;

    if (sp24 == 0.0f || sp20 == 0.0f || sp1C == 0.0f) {}

    Math_NormalizeVector(&sp24, &sp20, &sp1C);

    *arg0 = sp3C;
    *arg1 = sp38;
    *arg2 = sp34;
    *arg3 = sp24;
    *arg4 = sp20;
    *arg5 = sp1C;
}

void CalcVectorATtoDM2(f32* arg0, f32* arg1, f32* arg2, f32* arg3, f32* arg4, f32* arg5) {
    Vec3f sp4C;
    Vec3f sp40;
    f32 sp3C;
    f32 sp38;
    f32 sp34;
    UNUSED s32 pad[2];
    f32 tmp;
    f32 sp24;
    f32 sp20;
    f32 sp1C;

    func_843593F0(&sp4C);
    func_84359410(&sp40);

    sp3C = sp4C.x;
    sp38 = sp4C.y;
    sp34 = sp4C.z;

    tmp = sp40.y;
    if (tmp < 0.0f) {
        tmp = 0.0f;
    }

    sp24 = sp40.x - sp4C.x;
    sp20 = tmp - sp4C.y;
    sp1C = sp40.z - sp4C.z;

    if (sp24 == 0.0f || sp20 == 0.0f || sp1C == 0.0f) {}

    Math_NormalizeVector(&sp24, &sp20, &sp1C);

    *arg0 = sp3C;
    *arg1 = sp38;
    *arg2 = sp34;
    *arg3 = sp24;
    *arg4 = sp20;
    *arg5 = sp1C;
}

void InitEffectMatrix(void) {
    guRotateRPY(&gEffectMatrix, 0.0f, 0.0f, 0.0f);
}

void SpawnParticleEmitters_Default(void) {
    Vec3f sp24;
    f32 sp20;

    InitEffectMatrix();
    func_84359430(&sp24);
    sp20 = func_84359470();
    ParticleEmitters_Reset();
    func_8435CAE8(sp24.x, sp24.y, sp24.z, 40.0f, sp20, 0);
}

s32 func_843596DC(void) {
    return ParticleEmitters_Tick();
}

void func_843596FC(void) {
    gSPMatrix(gDisplayListHead++, &gEffectMatrix, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    gDisplayListHead = ParticleEmitters_Render(gDisplayListHead);
}

void SpawnParticleEmitters_Alt(void) {
    Vec3f sp24;
    f32 sp20;

    InitEffectMatrix();
    func_84359430(&sp24);
    sp20 = func_84359450();
    ParticleEmitters_Reset();
    func_8435CAE8(sp24.x, sp24.y, sp24.z, 40.0f, sp20, 1);
}

s32 func_843597AC(void) {
    return ParticleEmitters_Tick();
}

void func_843597CC(void) {
    gSPMatrix(gDisplayListHead++, &gEffectMatrix, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    gDisplayListHead = ParticleEmitters_Render(gDisplayListHead);
}

void SpawnParticleEmitters_Dual(void) {
    Vec3f sp24;
    f32 sp20;

    InitEffectMatrix();
    func_84359430(&sp24);
    sp20 = func_84359450();
    ParticleEmitters_Reset();
    func_8435CAE8(sp24.x, sp24.y, sp24.z, 40.0f, sp20, 0);
    func_8435CAE8(sp24.x, sp24.y, sp24.z, 38.0f, sp20, 1);
}

s32 func_8435989C(void) {
    return ParticleEmitters_Tick();
}

void func_843598BC(void) {
    gSPMatrix(gDisplayListHead++, &gEffectMatrix, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    gDisplayListHead = ParticleEmitters_Render(gDisplayListHead);
}

void SpawnParticleEmitters_Alt2(void) {
    Vec3f sp24;
    f32 sp20;

    InitEffectMatrix();
    func_84359430(&sp24);
    sp20 = func_84359470();
    ParticleEmitters_Reset();
    func_8435CAE8(sp24.x, sp24.y, sp24.z, 40.0f, sp20, 0);
    func_8435CAE8(sp24.x, sp24.y, sp24.z, 38.0f, sp20, 1);
}

s32 func_8435998C(void) {
    return ParticleEmitters_Tick();
}

void func_843599AC(void) {
    gSPMatrix(gDisplayListHead++, &gEffectMatrix, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    gDisplayListHead = ParticleEmitters_Render(gDisplayListHead);
}

void WaterHeightMap_InitByCameraX(void) {
    Vec3f sp1C;

    func_843593F0(&sp1C);
    InitEffectMatrix();

    if (sp1C.x < 0.0) {
        WaterHeightMap_Init(1, 0, 0x4650);
    } else {
        WaterHeightMap_Init(-1, 0, 0x4650);
    }
}

s32 func_84359A6C(void) {
    return func_8435EDF8();
}

void func_84359A8C(void) {
    gSPMatrix(gDisplayListHead++, &gEffectMatrix, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    gDisplayListHead = WaterSurface_Render(gDisplayListHead);
}

void func_84359AE0(void) {
}

s32 func_84359AE8(void) {
    return -1;
}

void func_84359AF0(void) {
}

void SpawnRandomizedParticleEffect(void) {
    f32 sp74;
    f32 sp70;
    f32 sp6C;
    f32 sp68;
    f32 sp64;
    f32 sp60;
    f32 sp5C;
    UNUSED s32 pad;
    s32 sp54;

    CalcVectorATtoDM(&sp74, &sp70, &sp6C, &sp68, &sp64, &sp60);
    sp68 *= 8.0f;
    sp64 *= 4.0f;
    sp60 = 0.0f;
    sp64 += 6.0f;
    sp5C = func_84359470();
    sp54 = guRandom();
    func_84360EFC(sp74, sp70, sp6C, sp68, (((sp54 % 4) * 0.01f) + sp64) - 0.02f,
                  (sp60 - ((guRandom() % 5) * 0.3f)) + 0.6f, 3, 0x64, 0xC8, 0xFF, 0xC8, 0, 0x64, 0xC8, 0.1f, sp5C,
                  4.0f * sp5C, 0x3C);
}

void StartParticleEffectA(void) {
    gParticleSpawnTimerA = 0;
    InitEffectMatrix();
    func_843605C0();
    SpawnRandomizedParticleEffect();
}

s32 UpdateParticleEffectA(void) {
    gParticleSpawnTimerA++;
    if (gParticleSpawnTimerA >= 0xB5) {
        return -1;
    }

    if ((gParticleSpawnTimerA < 0x78) && ((gParticleSpawnTimerA % 7) == 0)) {
        SpawnRandomizedParticleEffect();
    }
    return func_84361FB0();
}

void RenderParticleEffectA(void) {
    gSPMatrix(gDisplayListHead++, &gEffectMatrix, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    gDisplayListHead = func_84362084(gDisplayListHead);
}

void InitTrailEffect(void) {
    Vec3f sp34;
    f32 sp30;

    InitEffectMatrix();
    func_84359410(&sp34);
    sp30 = func_84359450();
    InitEffectMatrix();
    Trail_Init(sp34.x, sp34.y, sp34.z, sp30, 0x64, 0xC8, 0xFF, 0, 0x64, 0xC8);
}

s32 UpdateTrailEffect(void) {
    return Trail_Update();
}

void RenderTrailEffect(void) {
    gSPMatrix(gDisplayListHead++, &gEffectMatrix, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    gDisplayListHead = Trail_Render(gDisplayListHead);
}

void SpawnWaterParticleEffect(void) {
    UNUSED s32 pad[3];
    f32 sp58;
    f32 sp54;
    f32 sp50;
    f32 sp4C;
    f32 sp48;
    f32 sp44;
    f32 sp40;

    sp40 = func_84359470();
    CalcVectorATtoDM2(&sp58, &sp54, &sp50, &sp4C, &sp48, &sp44);
    sp4C *= 20.0f;
    sp48 *= 20.0f;
    sp44 *= 20.0f;
    sp58 += sp40 * (30.0f - (guRandom() % 60));
    sp54 += sp40 * (30.0f - (guRandom() % 60));
    sp50 += sp40 * (30.0f - (guRandom() % 60));
    WaterParticle_Spawn(sp58, sp54, sp50, sp4C, sp48, sp44, 0xFF, 0xFF, 0, 0x3C, 0.3f, 0x1E);
}

void StartWaterParticleEffectB(void) {
    gParticleSpawnTimerB = 0;
    InitEffectMatrix();
    WaterParticle_Reset();
    SpawnWaterParticleEffect();
}

s32 UpdateWaterParticleEffectB(void) {
    gParticleSpawnTimerB++;
    if (gParticleSpawnTimerB >= 0x709) {
        return -1;
    }

    if ((gParticleSpawnTimerB < 0x6EA) && ((gParticleSpawnTimerB % 3) == 0)) {
        SpawnWaterParticleEffect();
    }

    return WaterParticle_TickAll();
}

void RenderWaterParticleEffectB(void) {
    gSPMatrix(gDisplayListHead++, &gEffectMatrix, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    gDisplayListHead = WaterParticle_RenderAll(gDisplayListHead);
}

void SpawnRandomizedParticleEffectC(void) {
    f32 sp74;
    f32 sp70;
    f32 sp6C;
    f32 sp68;
    f32 sp64;
    f32 sp60;
    f32 sp5C;
    UNUSED s32 pad;
    s32 sp54;

    CalcVectorATtoDM(&sp74, &sp70, &sp6C, &sp68, &sp64, &sp60);
    sp68 *= 8.0f;
    sp64 *= 4.0f;
    sp60 = 0.0f;
    sp64 += 6.0f;
    sp5C = func_84359470();
    sp54 = guRandom();
    ParticleEmitter_AddRandomized(sp74, sp70, sp6C, sp68, (((sp54 % 5) * 0.1f) + sp64) - 0.2f,
                  (sp60 - ((guRandom() % 5) * 0.3f)) + 0.6f, 3, 0xFF, 0xFF, 0xFF, 0x64, 0x64, 0x96, 0x96, 0.1f, sp5C,
                  3.0f * sp5C, 0x3C);
}

void StartParticleEffectC(void) {
    gParticleSpawnTimerC = 0;
    InitEffectMatrix();
    func_843605C0();
    SpawnRandomizedParticleEffectC();
}

s32 UpdateParticleEffectC(void) {
    gParticleSpawnTimerC++;
    if (gParticleSpawnTimerC >= 0xB5) {
        return -1;
    }

    if ((gParticleSpawnTimerC < 0x78) && ((gParticleSpawnTimerC % 7) == 0)) {
        SpawnRandomizedParticleEffectC();
    }

    return func_84361FB0();
}

void RenderParticleEffectC(void) {
    gSPMatrix(gDisplayListHead++, &gEffectMatrix, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    gDisplayListHead = func_84362084(gDisplayListHead);
}

void InitTrailEffectVariant(void) {
    Vec3f sp34;
    f32 sp30;

    InitEffectMatrix();
    func_84359430(&sp34);
    sp30 = func_84359450();
    InitEffectMatrix();
    Trail_Init(sp34.x, sp34.y, sp34.z, sp30, 0xFF, 0xFF, 0xFF, 0x64, 0x96, 0x96);
}

s32 UpdateTrailEffectVariant(void) {
    return Trail_Update();
}

void RenderTrailEffectVariant(void) {
    gSPMatrix(gDisplayListHead++, &gEffectMatrix, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    gDisplayListHead = Trail_Render(gDisplayListHead);
}

void InitTrailEffectVariant2(void) {
    Vec3f sp34;
    f32 sp30;

    InitEffectMatrix();
    func_84359430(&sp34);
    sp30 = func_84359450();
    InitEffectMatrix();
    Trail_Init(sp34.x, sp34.y, sp34.z, sp30, 0xFF, 0xFF, 0x64, 0x96, 0x96, 0);
}

s32 UpdateTrailEffectVariant2(void) {
    return Trail_Update();
}

void RenderTrailEffectVariant2(void) {
    gSPMatrix(gDisplayListHead++, &gEffectMatrix, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    gDisplayListHead = Trail_Render(gDisplayListHead);
}

void SpawnRandomizedParticleEffectD(void) {
    f32 sp74;
    f32 sp70;
    f32 sp6C;
    f32 sp68;
    f32 sp64;
    f32 sp60;
    f32 sp5C;
    UNUSED s32 pad;
    s32 sp54;

    CalcVectorATtoDM(&sp74, &sp70, &sp6C, &sp68, &sp64, &sp60);
    sp68 *= 8.0f;
    sp64 *= 4.0f;
    sp60 = 0.0f;
    sp64 += 6.0f;
    sp5C = func_84359470();
    sp54 = guRandom();
    func_84360EFC(sp74, sp70, sp6C, sp68, (((sp54 % 4) * 0.01f) + sp64) - 0.02f,
                  (sp60 - ((guRandom() % 5) * 0.3f)) + 0.6f, 3, 0xFF, 0xFF, 0x64, 0xFF, 0x96, 0x96, 0, 0.1f, sp5C,
                  4.0f * sp5C, 0x3C);
}

void StartParticleEffectE(void) {
    gParticleSpawnTimerE = 0;
    InitEffectMatrix();
    func_843605C0();
    SpawnRandomizedParticleEffectD();
}

s32 UpdateParticleEffectE(void) {
    gParticleSpawnTimerE++;
    if (gParticleSpawnTimerE >= 0xB5) {
        return -1;
    }

    if ((gParticleSpawnTimerE < 0x78) && ((gParticleSpawnTimerE % 7) == 0)) {
        SpawnRandomizedParticleEffectD();
    }

    return func_84361FB0();
}

void RenderParticleEffectE(void) {
    gSPMatrix(gDisplayListHead++, &gEffectMatrix, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    gDisplayListHead = func_84362084(gDisplayListHead);
}

void StartEffectF(void) {
    gParticleSpawnTimerF = 0;
    InitEffectMatrix();
    WaterParticlePool_InitAlt();
}

s32 UpdateEffectF(void) {
    UNUSED s32 pad[1];
    Vec3f sp60;
    f32 sp5C;
    f32 sp58;
    f32 sp54;
    UNUSED s32 pad2[2];
    f32 var_fv0;
    f32 sp44;

    gParticleSpawnTimerF++;
    if (!(gParticleSpawnTimerF & 1)) {
        sp44 = func_84359470();
        func_843593F0(&sp60);
        sp5C = (((guRandom() % 50) - 0x19) * sp44) + sp60.x;
        sp58 = (((guRandom() % 60) - 0x1E) * sp44) + sp60.y;
        sp54 = (((guRandom() % 50) - 0x19) * sp44) + sp60.z;
        var_fv0 = 10.0f;
        if (sp5C > 0.0) {
            var_fv0 = -var_fv0;
        }
        WaterParticlePool_SpawnAlt(sp5C, sp58, sp54, var_fv0, 0.0f, 0.0f, 0xFF, 0xFF, 0xFF, 0x64, 0.3f, 1.0f, 4.0f, 0x1E);
    }
    WaterParticle_UpdateAll();
    return 0;
}

void RenderWaterParticleEffectF(void) {
    gSPMatrix(gDisplayListHead++, &gEffectMatrix, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    gDisplayListHead = WaterParticle_Render(gDisplayListHead);
}

void StartWaterParticlePoolG(void) {
    gParticleSpawnTimerG = 0;
    InitEffectMatrix();
    WaterParticlePool_Init();
}

s32 UpdateWaterParticlePoolG(void) {
    UNUSED s32 pad[1];
    Vec3f sp60;
    f32 sp5C;
    f32 sp58;
    f32 sp54;
    UNUSED s32 pad2[2];
    f32 var_fv0;
    f32 sp44;

    gParticleSpawnTimerG++;
    if (!(gParticleSpawnTimerG & 1)) {
        sp44 = func_84359470();
        func_843593F0(&sp60);
        sp5C = (((guRandom() % 50) - 0x19) * sp44) + sp60.x;
        sp58 = (((guRandom() % 60) - 0x1E) * sp44) + sp60.y;
        sp54 = (((guRandom() % 50) - 0x19) * sp44) + sp60.z;
        var_fv0 = 10.0f;
        if (sp5C > 0.0) {
            var_fv0 = -var_fv0;
        }
        WaterParticlePool_Spawn(sp5C, sp58, sp54, var_fv0, 0.0f, 0.0f, 0xFF, 0xFF, 0xFF, 0x64, 0.3f, 1.0f, 4.0f, 0x1E);
    }
    WaterParticlePool_Tick();
    return 0;
}

void RenderWaterParticlePoolG(void) {
    gSPMatrix(gDisplayListHead++, &gEffectMatrix, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    gDisplayListHead = WaterParticlePool_Render(gDisplayListHead);
}

void InitWaterSurface(void) {
    Vec3f sp1C;

    InitEffectMatrix();
    func_843593F0(&sp1C);
    WaterSurface_Init(0x708);
}

s32 UpdateWaterSurface(void) {
    return WaterSurface_Update();
}

void RenderWaterSurface(void) {
    gSPMatrix(gDisplayListHead++, &gEffectMatrix, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    gDisplayListHead = WaterSurface_Draw(gDisplayListHead);
}

void InitWaterSurfaceVariant(void) {
    Vec3f sp1C;

    InitEffectMatrix();
    func_843593F0(&sp1C);
    WaterSurface_Initialize(0x708);
}

s32 UpdateWaterSurfaceVariant(void) {
    return WaterSurface_Tick();
}

void RenderWaterSurfaceVariant(void) {
    gSPMatrix(gDisplayListHead++, &gEffectMatrix, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    gDisplayListHead = WaterSurface_DrawLit(gDisplayListHead);
}

void InitWaterEffectVariant(void) {
    Vec3f sp1C;

    InitEffectMatrix();
    func_843593F0(&sp1C);
    func_84365A10(0x708);
}

s32 UpdateWaterEffectVariant(void) {
    return func_843661D0();
}

void RenderWaterEffectVariant(void) {
    gSPMatrix(gDisplayListHead++, &gEffectMatrix, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    gDisplayListHead = func_84366560(gDisplayListHead);
}

void ResetAllParticleSystems(void) {
    gEffectPhaseCounterA = 0;
    InitEffectMatrix();
    WaterParticleSystem_ResetAll();
}

s32 UpdateWaterParticleSystemPhaseA(void) {
    s32 var_v1;
    Vec3f sp68;
    f32 sp64;
    f32 sp60;
    f32 sp5C;
    f32 sp58;
    f32 sp54;
    f32 sp50;
    f32 sp4C;

    gEffectPhaseCounterA++;
    if (gEffectPhaseCounterA >= 0x32) {
        return -1;
    }

    if (gEffectPhaseCounterA < 4) {
        func_84359430(&sp68);
        sp64 = sp68.x;
        sp60 = sp68.y;
        sp5C = sp68.z;
        sp58 = 1.0f;
        sp4C = (((gEffectPhaseCounterA % 3) * M_PI_F) / 3.0) + 0.5235987901687622;
        sp54 = (f64)__sinf(sp4C);
        sp50 = (f64)__cosf(sp4C);
        Math_NormalizeVector(&sp58, &sp54, &sp50);
        sp54 *= 20.0;
        sp50 *= 20.0;
        sp58 = 10.0f;
        if (sp64 < 0.0) {
            sp58 = -sp58;
        }
        WaterParticleSystem_Spawn(sp64, sp60, sp5C, sp58, sp54, sp50, 0xC0, 0xFF, 0xFF, 0x80, (((guRandom() % 2) * 2) - 1) * 0.3,
                      2.0f, 13.0f, 0x28);
    }

    if (gEffectPhaseCounterA >= 2) {
        var_v1 = WaterParticleSystem_UpdateAll();
    } else {
        var_v1 = 0;
    }
    return var_v1;
}

void RenderWaterParticleSystemPhaseA(void) {
    if (gEffectPhaseCounterA >= 2) {
        gSPMatrix(gDisplayListHead++, &gEffectMatrix, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

        gDisplayListHead = WaterParticleSystem_Render(gDisplayListHead);
    }
}

void ResetParticleEmittersPhaseB(void) {
    gEffectPhaseCounterB = 0;
    InitEffectMatrix();
    ResetParticleEmitters();
}

s32 UpdateParticleEmittersPhaseB(void) {
    s32 var_v1;
    f32 sp60;
    f32 sp5C;
    f32 sp58;
    f32 sp54;
    f32 sp50;
    f32 sp4C;
    f32 sp48;

    gEffectPhaseCounterB++;
    if (((gEffectPhaseCounterB >> 2) < 4) && !(gEffectPhaseCounterB & 3)) {
        CalcVectorATtoDM(&sp60, &sp5C, &sp58, &sp54, &sp50, &sp4C);
        sp48 = ((2 - (((gEffectPhaseCounterB >> 2) + 2) % 3)) * 0.5235988f) + 0.34906587f;
        sp54 *= 7.0f * __cosf(sp48);
        sp50 = __sinf(sp48) * 10.0f;
        sp4C = 0.0f;
        CreateParticleEmitter(sp60, sp5C, sp58, sp54, sp50, 0.0f, 0xD0, 0xFF, 0xFF, 0x80, 0.8f, 2.0f, 4.0f, 0x28);
    }

    if (gEffectPhaseCounterB >= 2) {
        var_v1 = TickParticleEmitters();
    } else {
        var_v1 = 0;
    }
    return var_v1;
}

void RenderParticleEmittersPhaseB(void) {
    if (gEffectPhaseCounterB >= 2) {
        gSPMatrix(gDisplayListHead++, &gEffectMatrix, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

        gDisplayListHead = RenderParticleEmitters(gDisplayListHead);
    }
}

void StartParticleSystemI(void) {
    Vec3f sp5C;
    f32 sp58;
    f32 sp54;
    f32 sp50;
    f32 sp4C;
    f32 sp48;
    f32 sp44;

    gParticleSpawnTimerI = 0;
    InitEffectMatrix();
    ParticleSystem_ResetAll();
    CalcVectorATtoDM(&sp58, &sp54, &sp50, &sp4C, &sp48, &sp44);
    sp4C *= 5.0;
    sp48 *= 5.0;
    sp44 *= 5.0;
    ParticleSystem_Spawn(sp58, sp54, sp50, sp4C, sp48, sp44, 0xC0, 0xFF, 0xFF, 0xA0, 0.6f, 2.0f, 4.0f, 0x28);
    sp5C.x = sp58;
    sp5C.y = sp54;
    sp5C.z = sp50;
    ParticleNode_CreateWhiteFlash(sp5C, 1);
}

s32 UpdateParticleSystemI(void) {
    gParticleSpawnTimerI++;
    if (gParticleSpawnTimerI >= 0x32) {
        return -1;
    }

    return ParticleSystem_TickAll();
}

void RenderParticleSystemI(void) {
    gSPMatrix(gDisplayListHead++, &gEffectMatrix, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    gDisplayListHead = ParticleSystem_RenderAll(gDisplayListHead);
}

void CreateSimpleParticleEmitter(void) {
    f32 sp5C;
    f32 sp58;
    f32 sp54;
    f32 sp50;
    f32 sp4C;
    f32 sp48;

    CalcVectorATtoDM(&sp5C, &sp58, &sp54, &sp50, &sp4C, &sp48);
    sp50 *= 6.0f;
    sp4C *= 6.0f;
    sp48 *= 6.0f;
    ParticleEmitter_AddSimple(sp5C, sp58, sp54, sp50, sp4C, sp48, 8, 0xFF, 0xFF, 0xFF, 0xB4, 0.3f, 2.0f, 20.0f, 0x3C);
}

void StartParticleEffectD(void) {
    gParticleSpawnTimerD0 = 0;
    InitEffectMatrix();
    func_843605C0();
    CreateSimpleParticleEmitter();
}

s32 UpdateParticleEffectD(void) {
    gParticleSpawnTimerD0++;
    if (gParticleSpawnTimerD0 >= 0xB5) {
        return -1;
    }
    return func_84361FB0();
}

void RenderParticleEffectD(void) {
    gSPMatrix(gDisplayListHead++, &gEffectMatrix, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    gDisplayListHead = func_84362084(gDisplayListHead);
}

void ConfigureWaterParticleSystemCombine(void) {
    static CombineParams D_84387FC0 = { 2, 1, 0xE, 1, 2, 2, 3, 1 };
    static CombineParams D_84387FE0 = { 3, 5, 0, 5, 3, 7, 0, 5 };
    static CombineParams D_84388000 = { 2, 1, 0xE, 1, 2, 1, 3, 1 };
    static CombineParams D_84388020 = { 3, 5, 0, 5, 0, 7, 5, 7 };

    f32 spB4;
    f32 spB0;
    f32 spAC;
    f32 spA8;
    f32 spA4;
    f32 spA0;

    CalcVectorATtoDM(&spB4, &spB0, &spAC, &spA8, &spA4, &spA0);
    spA8 *= 10.0f;
    spA4 *= 10.0f;
    spA0 *= 10.0f;
    WaterParticleSystems_Spawn(spB4, spB0, spAC, spA8, spA4, spA0, 0.0f, 5.0f, 1.2f, 2.0f, 10.0f, 0x14, 0x8F, 0x8F, 6, 0xA, 0xF, 0xE,
                  -3, 5, 0, 0xF, &D_84387FC0, &D_84387FE0, 0xFF, 0xFF, 0, 0x96, 0x64, 0xFF, 0, 0xC8, 0x32, 0xFF, 0x96,
                  0xFF, 0x78);
    WaterParticleSystems_Spawn(spB4, spB0, spAC, spA8, spA4, spA0, 0.0f, 5.0f, 1.2f, 3.0f, 15.0f, 0x14, 0x8F, 0x90, 2, 6, 0, 0xF, -4,
                  2, 0, 0, &D_84388000, &D_84388020, 0, 0xFF, 0x64, 0x96, 0x64, 0x64, 0, 0xFF, 0xC8, 0, 0, 0, 0);
}

void InitWaterParticleSystemsCombined(void) {
    InitEffectMatrix();
    WaterParticleSystems_ResetAll();
    ConfigureWaterParticleSystemCombine();
}

s32 UpdateWaterParticleSystemsCombined(void) {
    return WaterParticleSystems_Tick();
}

void RenderCombinedWaterEffect(void) {
    gSPMatrix(gDisplayListHead++, &gEffectMatrix, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    gDisplayListHead = WaterParticleSystems_Render(gDisplayListHead);
}

void SpawnWaterEffectVariant1(void) {
    static CombineParams D_84388040 = { 3, 5, 1, 5, 1, 7, 3, 7 };
    static CombineParams D_84388060 = { 0x1F, 0x1F, 0x1F, 0, 7, 7, 7, 0 };

    f32 spA4;
    f32 spA0;
    f32 sp9C;
    f32 sp98;
    f32 sp94;
    f32 sp90;

    CalcVectorATtoDM(&spA4, &spA0, &sp9C, &sp98, &sp94, &sp90);
    sp94 += 0.2f * __cosf((RAND(10) * M_PI_F) / 10.0f);
    sp90 += 0.2f * __cosf((RAND(10) * M_PI_F) / 10.0f);

    sp98 *= 12.0f;
    sp94 *= 12.0f;
    sp90 *= 12.0f;

    WaterEffect_Spawn(0, spA4, spA0, sp9C, sp98, sp94, sp90, 0xFF, 0xFF, 0xFF, 0xFF, 0, 0, 0x64, 0xFF, 0xFF, 0.4f, 2.0f,
                  20.0f, 0x3C, 0x95, 0x95, 0, 0xA, 0, 0xD, 0, 0, 0, 0, &D_84388040, &D_84388060);
}

void StartWaterEffectH(void) {
    gParticleSpawnTimerH = 0;
    InitEffectMatrix();
    WaterEffect_Init();
    SpawnWaterEffectVariant1();
}

s32 UpdateWaterEffectH(void) {
    gParticleSpawnTimerH++;
    if ((gParticleSpawnTimerH % 10) == 0) {
        SpawnWaterEffectVariant1();
    }
    return WaterEffect_Process();
}

void RenderWaterEffectH(void) {
    gSPMatrix(gDisplayListHead++, &gEffectMatrix, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    gDisplayListHead = WaterEffect_RenderAll(gDisplayListHead);
}

void ConfigureWaterEffectVariant2(void) {
    static CombineParams D_84388080 = { 3, 5, 1, 5, 6, 7, 2, 3 };
    static CombineParams D_843880A0 = { 0x1F, 0x1F, 0x1F, 0, 0, 7, 5, 7 };
    static CombineParams D_843880C0 = { 3, 5, 2, 5, 1, 7, 3, 7 };
    static CombineParams D_843880E0 = { 0x1F, 0x1F, 0x1F, 0, 0, 7, 5, 7 };

    f32 spB4;
    f32 spB0;
    f32 spAC;
    f32 spA8;
    f32 spA4;
    f32 spA0;

    CalcVectorATtoDM(&spB4, &spB0, &spAC, &spA8, &spA4, &spA0);
    spA8 *= 10.0f;
    spA4 *= 10.0f;
    spA0 *= 10.0f;
    WaterParticleSystems_Spawn(spB4, spB0, spAC, spA8, spA4, spA0, 0.0f, 5.0f, 1.2f, 2.0f, 10.0f, 0x14, 0x93, 0x93, 5, 0xA, 0xF, 0xF,
                  -5, 5, 0xF, 0xF, &D_84388080, &D_843880A0, 0xC8, 0xC8, 0, 0x64, 0, 0, 0xC8, 0, 0xFF, 0, 0xFF, 0,
                  0x5A);
    WaterParticleSystems_Spawn(spB4, spB0, spAC, spA8, spA4, spA0, 0.0f, 5.0f, 1.2f, 3.0f, 15.0f, 0x14, 0x91, 0x91, -2, 0xA, 0xF,
                  0xF, 5, 0xF, 0xF, 0xF, &D_843880C0, &D_843880E0, 0xFF, 0x32, 0x64, 0xC8, 0, 0x64, 0x32, 0xFF, 0xFF, 0,
                  0, 0, 0);
}

void InitWaterEffectVariant2(void) {
    InitEffectMatrix();
    WaterParticleSystems_ResetAll();
    ConfigureWaterEffectVariant2();
}

s32 UpdateWaterEffectVariant2(void) {
    return WaterParticleSystems_Tick();
}

void RenderWaterEffectVariant2(void) {
    gSPMatrix(gDisplayListHead++, &gEffectMatrix, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    gDisplayListHead = WaterParticleSystems_Render(gDisplayListHead);
}

void ConfigureWaterEffectVariant3(void) {
    static CombineParams D_84388100 = { 2, 1, 0xE, 1, 2, 7, 1, 3 };
    static CombineParams D_84388120 = { 3, 5, 0, 5, 0, 7, 5, 7 };
    static CombineParams D_84388140 = { 2, 1, 0xE, 1, 2, 7, 1, 3 };
    static CombineParams D_84388160 = { 3, 5, 0, 5, 0, 7, 5, 7 };

    f32 spB4;
    f32 spB0;
    f32 spAC;
    f32 spA8;
    f32 spA4;
    f32 spA0;

    CalcVectorATtoDM(&spB4, &spB0, &spAC, &spA8, &spA4, &spA0);
    spA8 *= 10.0f;
    spA4 *= 10.0f;
    spA0 *= 10.0f;
    WaterParticleSystems_Spawn(spB4, spB0, spAC, spA8, spA4, spA0, 0.0f, 5.0f, 1.2f, 2.0f, 10.0f, 0x14, 0x97, 0x98, -5, 0x14, 0xF,
                  0xD, -5, 0x14, 0, 0xE, &D_84388100, &D_84388120, 0xFF, 0xFF, 0xFF, 0x32, 0x64, 0x64, 0, 0xFF, 0xFF,
                  0xC8, 0xFF, 0xFF, 0x96);
    WaterParticleSystems_Spawn(spB4, spB0, spAC, spA8, spA4, spA0, 0.0f, 5.0f, 1.2f, 3.0f, 15.0f, 0x14, 0x97, 0x98, 5, 0xF, 0xF, 0xE,
                  0, 0xF, 0xF, 0xF, &D_84388140, &D_84388160, 0xFF, 0xFF, 0xFF, 0x32, 0x64, 0x64, 0x64, 0xFF, 0xFF, 0,
                  0, 0, 0);
}

void InitWaterEffectVariant3(void) {
    InitEffectMatrix();
    WaterParticleSystems_ResetAll();
    ConfigureWaterEffectVariant3();
}

s32 UpdateWaterEffectVariant3(void) {
    return WaterParticleSystems_Tick();
}

void RenderWaterEffectVariant3(void) {
    gSPMatrix(gDisplayListHead++, &gEffectMatrix, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    gDisplayListHead = WaterParticleSystems_Render(gDisplayListHead);
}

void ConfigureWaterEffectVariant4(void) {
    static CombineParams D_84388180 = { 2, 1, 0xE, 1, 2, 1, 3, 1 };
    static CombineParams D_843881A0 = { 3, 5, 0, 5, 0, 7, 5, 7 };

    f32 spB4;
    f32 spB0;
    f32 spAC;
    f32 spA8;
    f32 spA4;
    f32 spA0;

    CalcVectorATtoDM(&spB4, &spB0, &spAC, &spA8, &spA4, &spA0);
    spA8 *= 10.0f;
    spA4 *= 10.0f;
    spA0 *= 10.0f;
    WaterParticleSystems_Spawn(spB4, spB0, spAC, spA8, spA4, spA0, 0.0f, 5.0f, 1.2f, 3.0f, 15.0f, 0x14, 0x97, 0x94, 0, 0x14, 0xE,
                  0xF, 0, 0x14, 0xF, 0xE, &D_84388180, &D_843881A0, 0xFF, 0xFF, 0xFF, 0x96, 0x96, 0xFF, 0xFF, 0, 0xFF,
                  0xFF, 0xFF, 0, 0x96);
}

void InitWaterEffectVariant4(void) {
    InitEffectMatrix();
    WaterParticleSystems_ResetAll();
    ConfigureWaterEffectVariant4();
}

s32 UpdateWaterEffectVariant4(void) {
    return WaterParticleSystems_Tick();
}

void RenderWaterEffectVariant4(void) {
    gSPMatrix(gDisplayListHead++, &gEffectMatrix, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    gDisplayListHead = WaterParticleSystems_Render(gDisplayListHead);
}

void ConfigureWaterEffectVariant5(void) {
    static CombineParams D_843881C0 = {
        0x00000002, 0x00000001, 0x0000000E, 0x00000001, 0x00000007, 0x00000007, 0x00000007, 0x00000003,
    };
    static CombineParams D_843881E0 = {
        0x00000003, 0x00000005, 0x00000000, 0x00000005, 0x00000007, 0x00000007, 0x00000007, 0x00000000,
    };
    static CombineParams D_84388200 = {
        0x00000002, 0x00000001, 0x0000000E, 0x00000001, 0x00000002, 0x00000001, 0x00000003, 0x00000001,
    };
    static CombineParams D_84388220 = {
        0x00000003, 0x00000005, 0x00000000, 0x00000005, 0x00000000, 0x00000007, 0x00000005, 0x00000007,
    };

    f32 spB4;
    f32 spB0;
    f32 spAC;
    f32 spA8;
    f32 spA4;
    f32 spA0;

    CalcVectorATtoDM(&spB4, &spB0, &spAC, &spA8, &spA4, &spA0);
    spA8 *= 12.0f;
    spA4 *= 12.0f;
    spA0 *= 12.0f;
    WaterParticleSystems_Spawn(spB4, spB0, spAC, spA8, spA4, spA0, 0.0f, 5.0f, 1.2f, 2.0f, 10.0f, 0x14, 0x91, 0x92, 5, 0x1E, 0, 0xD,
                  -5, 0x1E, 0xF, 0xD, &D_843881C0, &D_843881E0, 0xFF, 0xFF, 0, 0xFF, 0x96, 0x32, 0, 0, 0xFF, 0xFF, 0xC8,
                  0x64, 0xC8);
    WaterParticleSystems_Spawn(spB4, spB0, spAC, spA8, spA4, spA0, 0.0f, 5.0f, 1.2f, 3.0f, 15.0f, 0x14, 0x97, 0x96, 6, 0x14, 0xE,
                  0xF, -3, 0xA, 0, 0xF, &D_84388200, &D_84388220, 0xFF, 0xFF, 0x64, 0x96, 0xFF, 0xFF, 0x64, 0, 0xC8, 0,
                  0, 0, 0);
}

void SpawnWaterEffectVariant5(void) {
    static CombineParams D_84388240 = {
        0x00000002, 0x00000001, 0x0000000E, 0x00000001, 0x00000002, 0x00000001, 0x00000003, 0x00000001,
    };
    static CombineParams D_84388260 = {
        0x00000003, 0x00000005, 0x00000000, 0x00000005, 0x00000000, 0x00000007, 0x00000005, 0x00000007,
    };

    f32 spA4;
    f32 spA0;
    f32 sp9C;
    f32 sp98;
    f32 sp94;
    f32 sp90;

    CalcVectorATtoDM(&spA4, &spA0, &sp9C, &sp98, &sp94, &sp90);

    sp94 += (0.4f * __cosf((RAND(10) * M_PI_F) / 10));
    sp90 += (0.4f * __cosf((RAND(10) * M_PI_F) / 10));

    sp98 *= 12.0f;
    sp94 *= 12.0f;
    sp90 *= 12.0f;

    WaterEffect_Spawn(0, spA4, spA0, sp9C, sp98, sp94, sp90, 0xFF, 0xFF, 0x64, 0x32, 0xC8, 0xFF, 0x32, 0, 0xFF, 0.4f, 2.0f,
                  5.0f, 0x3C, 0x95, 0x95, 0, 0x14, 0, 0xD, 0, 0x19, 0, 0xD, &D_84388240, &D_84388260);
}

void InitWaterEffectVariant5(void) {
    InitEffectMatrix();
    WaterParticleSystems_ResetAll();
    ConfigureWaterEffectVariant5();
    WaterEffect_Init();
    SpawnWaterEffectVariant5();
}

s32 UpdateWaterEffectD(void) {
    gParticleSpawnTimerD++;
    if ((gParticleSpawnTimerD % 10) == 0) {
        SpawnWaterEffectVariant5();
    }
    WaterEffect_Process();
    return WaterParticleSystems_Tick();
}

void RenderCombinedWaterEffectD(void) {
    gSPMatrix(gDisplayListHead++, &gEffectMatrix, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    gDisplayListHead = WaterParticleSystems_Render(gDisplayListHead);
    gDisplayListHead = WaterEffect_RenderAll(gDisplayListHead);
}
