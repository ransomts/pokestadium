#include "fragment62.h"
#include "src/17300.h"
#include "src/1C720.h"
#include "src/F420.h"

static f32 gDefaultScales[] = { 1.0f, 2.0f };

void Entity_SetLaunchVelocity(unk_BattlePlayerEntity* arg0, f32 arg1, s16 arg2) {
    arg0->launchSpeed = arg1;
    arg0->unk_448.unk_0C.z = COSS(arg2) * arg1;
    arg0->unk_448.unk_0C.y = SINS(arg2) * arg1;
    arg0->unk_49C = 0.01f;
}

void Entity_UpdateMovement(unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1, f32 arg2, f32 arg3, s32 arg4) {
    f32 sp54;
    f32 sp50;
    f32 sp4C;
    UNUSED s32 pad;
    Vec3f sp3C;
    UNUSED s32 pad2;
    f32 temp_fa1;
    f32 temp_fa2;
    f32 var_fa0;

    sp54 = arg1->unk_49C;
    sp50 = arg1->launchSpeed;
    sp4C = 18.0f;
    arg1->launchSpeed = Math_ApproachF32(sp50, arg2, arg3, arg3);

    var_fa0 = arg1->launchSpeed;
    if (arg2 <= var_fa0) {
        if (&arg1->unk_448.unk_0C) {}
        var_fa0 = 0.0f;
    }

    sp3C.z = COSS(arg4) * var_fa0;
    sp3C.y = SINS(arg4) * var_fa0;

    temp_fa1 = -sp54 * ((sp50 * arg1->unk_448.unk_0C.z) + sp3C.z);
    temp_fa2 = -sp4C - (sp54 * ((sp50 * arg1->unk_448.unk_0C.y) + sp3C.y));

    arg1->unk_448.unk_0C.z = (arg1->unk_448.unk_0C.z + sp3C.z + (temp_fa1 * 0.05f));
    arg1->unk_448.unk_0C.y = (arg1->unk_448.unk_0C.y + sp3C.y + (temp_fa2 * 0.05f));

    sp3C.y = arg1->unk_448.unk_0C.y;
    arg1->unk_448.unk_0C.x = 0.0f;

    Vector_SetXZFromPolar(&sp3C, arg1->unk_448.unk_0C.z, arg0->unk_000.unk_01E.y + 0x4000);
    Vec3f_Add(&arg0->unk_000.unk_024, &sp3C);
}

void Entity_UpdateMovementFast(UNUSED unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1, f32 arg2, f32 arg3, s32 arg4, s32 arg5) {
    f32 sp54;
    f32 sp50;
    f32 sp4C;
    UNUSED s32 pad;
    Vec3f sp3C;
    UNUSED s32 pad2;
    f32 temp_fa1;
    f32 temp_fa2;
    f32 var_fa0;

    sp54 = arg1->unk_49C;
    sp50 = arg1->launchSpeed;
    sp4C = 20.0f;
    arg1->launchSpeed = Math_ApproachF32(sp50, arg2, arg3, arg3);

    var_fa0 = arg1->launchSpeed;
    if (arg2 <= var_fa0) {
        if (&arg1->unk_448.unk_0C) {}
        var_fa0 = 0.0f;
    }

    sp3C.z = COSS(arg4) * var_fa0;
    sp3C.y = SINS(arg4) * var_fa0;

    temp_fa1 = -sp54 * ((sp50 * arg1->unk_448.unk_0C.z) + sp3C.z);
    temp_fa2 = -sp4C - (sp54 * ((sp50 * arg1->unk_448.unk_0C.y) + sp3C.y));

    arg1->unk_448.unk_0C.z = (arg1->unk_448.unk_0C.z + sp3C.z + (temp_fa1 * 0.05f));
    arg1->unk_448.unk_0C.y = (arg1->unk_448.unk_0C.y + sp3C.y + (temp_fa2 * 0.05f));
    sp3C.y = arg1->unk_448.unk_0C.y;
    arg1->unk_448.unk_0C.x = 0.0f;

    Vector_SetXZFromPolar(&sp3C, arg1->unk_448.unk_0C.z, arg5);
    Vec3f_Add(&arg1->effectGraphNode.unk_024, &sp3C);
}

void Entity_ResetSubObjectFlags(unk_BattlePlayerEntity* arg0) {
    s32 i;

    for (i = 0; i < 2; i++) {
        Vec3f_Set(&arg0->unk_168[i].unk_000.unk_030, 1.0f, 1.0f, 1.0f);
        arg0->unk_168[i].unk_000.unk_000.unk_01 &= ~1;
        arg0->unk_168[i].unk_169 = 0;
    }
}

void Entity_InitSubObjects(unk_BattlePlayerEntity* arg0) {
    s32 i;
    s16 sp64[] = { 0x0, 0xE38, 0xF1C8 }; // D_84384608

    for (i = 0; i < 2; i++) {
        arg0->unk_168[i].unk_16C = 0;
        arg0->unk_168[i].unk_16A = sp64[i];
        arg0->unk_168[i].unk_000.unk_01D = 0;
        arg0->unk_168[i].unk_000.unk_000.unk_01 |= 1;
        Vector_Copy(&arg0->unk_168[i].unk_000.unk_024, &arg0->unk_000.unk_024);
        VectorS_Copy(&arg0->unk_168[i].unk_000.unk_01E, &arg0->unk_000.unk_01E);
        Vector_Copy(&arg0->unk_168[i].unk_000.unk_030, &arg0->unk_000.unk_030);
    }
}

void Entity_AnimateSubObjects(unk_BattlePlayerEntity* arg0) {
    s32 i;
    f32 tmp;
    Vec3f sp5C = { 0.0f, 0.0f, 0.0f };         // D_84384610
    f32 sp4C[] = { 0.3f, -0.4f, -0.2f, 0.4f }; // D_8438461C

    for (i = 0; i < 2; i++) {
        arg0->unk_168[i].unk_000.unk_01D = Math_ApproachS32(arg0->unk_168[i].unk_000.unk_01D, 0x3C, 5, 5);
        arg0->unk_168[i].unk_16C = Math_ApproachS32(arg0->unk_168[i].unk_16C, 0x38E, 0x64, 0x64);
        arg0->unk_168[i].unk_16C = Math_ApproachS32(arg0->unk_168[i].unk_16C, 0x38E, 0x64, 0x64);
        arg0->unk_168[i].unk_16A += arg0->unk_168[i].unk_16C;

        tmp = SINS(arg0->unk_168[i].unk_16A) * (GetScaledWidth(arg0) * sp4C[i]);
        Vector_SetXZFromPolar(&sp5C, tmp, arg0->unk_000.unk_01E.y);

        arg0->unk_168[i].unk_000.unk_024.x = arg0->unk_000.unk_024.x + sp5C.x;
        arg0->unk_168[i].unk_000.unk_024.y = arg0->unk_000.unk_024.y + sp5C.y;
        arg0->unk_168[i].unk_000.unk_024.z = arg0->unk_000.unk_024.z + sp5C.z;

        Anim_SetChannelBase(&arg0->unk_168[i].unk_000, arg0->unk_000.unk_040.unk_08 >> 0x10);
        GraphNode_TriggerAction(&arg0->unk_168[i].unk_000, arg0->unk_000.unk_040.unk_00);
    }
}

void Entity_ActivateSubObjects(unk_BattlePlayerEntity* arg0) {
    s32 i;

    for (i = 0; i < 2; i++) {
        arg0->unk_168[i].unk_169 = 0;
        arg0->unk_168[i].unk_000.unk_01D = 0x3C;
        arg0->unk_168[i].unk_000.unk_000.unk_01 |= 1;
        Vec3f_Set(&arg0->unk_168[i].unk_000.unk_030, 1.0f, 1.0f, 1.0f);
        Vector_Copy(&arg0->unk_168[i].unk_000.unk_024, &arg0->unk_000.unk_024);
        VectorS_Copy(&arg0->unk_168[i].unk_000.unk_01E, &arg0->unk_000.unk_01E);
    }
}

s32 Entity_ScaleSubObjects(unk_BattlePlayerEntity* arg0) {
    s32 i;
    f32 temp_fv0_2;
    f32 sp5C[] = { 0.007f, 0.005f, 0.039f }; // D_8438462C

    for (i = 0; i < 2; i++) {
        Vector_Copy(&arg0->unk_168[i].unk_000.unk_024, &arg0->unk_000.unk_024);

        temp_fv0_2 = Math_ApproachF32(arg0->unk_168[i].unk_000.unk_030.x, 0.8f, sp5C[i], sp5C[i]);
        arg0->unk_168[i].unk_000.unk_030.x = temp_fv0_2;
        arg0->unk_168[i].unk_000.unk_030.y = temp_fv0_2;
        arg0->unk_168[i].unk_000.unk_030.z = temp_fv0_2;

        Anim_SetChannelBase(&arg0->unk_168[i].unk_000, arg0->unk_000.unk_040.unk_08 >> 0x10);
        GraphNode_TriggerAction(&arg0->unk_168[i].unk_000, arg0->unk_000.unk_040.unk_00);

        if (arg0->unk_168[i].unk_000.unk_030.y < 0.8) {
            arg0->unk_168[i].unk_169 = 1;
        }
    }

    return 0;
}

void Entity_SetSubObjectCameraOffsets(unk_BattlePlayerEntity* arg0) {
    s32 i;

    for (i = 0; i < 2; i++) {
        arg0->unk_168[i].unk_169 = 0;
        arg0->unk_168[i].unk_000.unk_01D = 0x41 - i * 4;
        arg0->unk_168[i].unk_000.unk_000.unk_01 |= 1;

        Anim_SetChannelBase(&arg0->unk_168[i].unk_000, arg0->unk_000.unk_040.unk_08 >> 0x10);
        GraphNode_TriggerAction(&arg0->unk_168[i].unk_000, arg0->unk_000.unk_040.unk_00);
        Vec3f_Set(&arg0->unk_168[i].unk_000.unk_030, 1.0f, 1.0f, 1.0f);
        Vector_Copy(&arg0->unk_168[i].unk_000.unk_024, &arg0->unk_000.unk_024);
        VectorS_Copy(&arg0->unk_168[i].unk_000.unk_01E, &arg0->unk_000.unk_01E);
        Vector_Copy(&arg0->unk_168[i].unk_000.unk_030, &arg0->unk_000.unk_030);
    }
}

void Entity_UpdateCameraFromSubObject(unk_BattlePlayerEntity* arg0, s16 arg1) {
    s32 i;
    f32 sp90;
    s16 sp8E;
    s16 sp8C;
    UNUSED s32 pad;
    f32 sp7C[3] = { 0.2f, 0.25f, 0.3f };   // D_84384638
    f32 sp70[3] = { 0.98f, 0.96f, 0.95f }; // D_84384644

    for (i = 0; i < 2; i++) {
        Anim_SetChannelBase(&arg0->unk_168[i].unk_000, arg0->unk_000.unk_040.unk_08 >> 0x10);
        GraphNode_TriggerAction(&arg0->unk_168[i].unk_000, arg0->unk_000.unk_040.unk_00);
        Matrix_Decompose(&arg0->unk_000.unk_024, &arg0->unk_168[i].unk_000.unk_024, &sp90, &sp8E, &sp8C);
        Camera_SetViewParameters(&arg0->unk_000.unk_024, &arg0->unk_168[i].unk_000.unk_024, sp7C[i] * sp90, sp8E, sp8C);
        Math_StepTowards(&arg0->unk_168[i].unk_000.unk_01E.y, arg0->unk_000.unk_01E.y, sp70[i] * arg1);
    }
}

void BattleScene_ResetParticipantModelFlags(unk_BattlePlayerEntity* arg0) {
    ApplyAnimEffectToOpponent(arg0, 0, 0);
}

void Entity_LaunchProjectile(UNUSED unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1) {
    arg1->effectGraphNode.unk_000.unk_01 |= 1;
    if (arg1 == sActivePokemon[0]) {
        Vec3f_Set(&arg1->effectGraphNode.unk_024, 35.0f, 50.0f, -250.0f);
    } else {
        Vec3f_Set(&arg1->effectGraphNode.unk_024, -35.0f, 50.0f, -250.0f);
    }
    Entity_SetLaunchVelocity(arg1, 20.0f, 0x1FFE);
    arg1->animationSubstate++;
    arg1->effectGraphNode.unk_000.unk_02 &= ~0x20;
    Anim_SetChannelBase(&arg1->effectGraphNode, 0);
}

void Entity_HandleProjectileLanding(unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1) {
    if (arg1 == gPrimaryPokemonEntity) {
        Entity_UpdateMovementFast(arg0, arg1, 0, 0, 0x1FFE, 0x4440);
    } else {
        Entity_UpdateMovementFast(arg0, arg1, 0, 0, 0x1FFE, 0x3BB8);
    }

    arg1->effectGraphNode.unk_01E.x += 0x1555;
    arg1->effectGraphNode.unk_01E.z += 0xE38;

    if (arg1->effectGraphNode.unk_024.y < 0) {
        arg1->effectGraphNode.unk_000.unk_01 &= ~1;
        arg1->effectGraphNode.unk_024.y = 0.0f;
        arg1->unk_448.unk_0C.y = 0.0f;
        BattleScene_ResetParticipantModelFlags(arg1);
    }
}

void Entity_StateMachine_Dispatch(unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1) {
    switch (arg1->animationSubstate) {
        case 0:
            Entity_LaunchProjectile(arg0, arg1);

        case 1:
            Entity_HandleProjectileLanding(arg0, arg1);
            break;
    }
}

void BattleAnim_StatusIdleCase2Sub0(UNUSED unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1) {
    Vec3f_Set(&arg1->effectGraphNode.unk_024, arg1->sideSign * -150.0f, 100.0f, 0.0f);
    arg1->animationSubstate++;
    Entity_SetLaunchVelocity(arg1, 0.0f, 0x3FFC);
    arg1->effectGraphNode.unk_000.unk_01 |= 1;
    arg1->effectGraphNode.unk_000.unk_02 &= ~0x20;
    Anim_SetChannelBase(&arg1->effectGraphNode, 0);
}

void BattleAnim_StatusIdleCase2Sub1(unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1) {
    arg1->effectGraphNode.unk_01E.x += 0x1555;
    arg1->effectGraphNode.unk_01E.z += 0xE38;

    Entity_UpdateMovementFast(arg0, arg1, 0.0f, 0.0f, 0x4000, 0);

    if (arg1->effectGraphNode.unk_024.y < 0) {
        arg1->effectGraphNode.unk_01E.x = 0;
        arg1->effectGraphNode.unk_01E.z = 0;
        if (arg1 == gPrimaryPokemonEntity) {
            arg1->effectGraphNode.unk_01E.y = 0x4000;
        } else {
            arg1->effectGraphNode.unk_01E.y = -0x4000;
        }
        arg1->unk_448.unk_0C.y = 0.0f;
        arg1->effectGraphNode.unk_024.y = 2.5f;
        BattleScene_ResetParticipantModelFlags(arg1);
    }
}

void BattleAnim_StatusIdleCase2(unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1) {
    switch (arg1->animationSubstate) {
        case 0:
            BattleAnim_StatusIdleCase2Sub0(arg0, arg1);

        case 1:
            BattleAnim_StatusIdleCase2Sub1(arg0, arg1);
            break;
    }
}

void BattleAnim_StatusIdleCase3Sub0(UNUSED unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1) {
    Vec3f_Set(&arg1->unk_448, 0.0f, 0.0f, 0.0f);
    Vec3f_Set(&arg1->unk_448.unk_0C, 0.0f, 0.0f, 0.0f);
    Entity_SetLaunchVelocity(arg1, gDefaultScales[0], 0x4000);
    Entity_SetSubObjectCameraOffsets(arg1);
    arg1->animationSubstate++;
}

void BattleAnim_StatusIdleCase3Sub1(unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1) {
    Entity_UpdateMovement(arg0, arg1, 1.45f, 0.015f, 0x4000);
    Entity_UpdateCameraFromSubObject(arg1, 0);
    if (arg0->unk_000.unk_024.y >= 200.0f) {
        arg1->unk_448.unk_0C.y = 0.0f;
        BattleScene_ResetParticipantModelFlags(arg1);
        Entity_ResetSubObjectFlags(arg1);
    }
}

void BattleAnim_StatusIdleCase3(unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1) {
    switch (arg1->animationSubstate) {
        case 0:
            BattleAnim_StatusIdleCase3Sub0(arg0, arg1);

        case 1:
            BattleAnim_StatusIdleCase3Sub1(arg0, arg1);
            break;
    }
}

void BattleAnim_StatusIdleCase14Sub0(UNUSED unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1) {
    Vec3f_Set(&arg1->unk_448, 0.0f, 0.0f, 0.0f);
    Vec3f_Set(&arg1->unk_448.unk_0C, 0.0f, 0.0f, 0.0f);
    Entity_SetLaunchVelocity(arg1, gDefaultScales[0], 0x4000);
    arg1->animationSubstate++;
}

void BattleAnim_StatusIdleCase14Sub1(unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1) {
    Entity_UpdateMovement(arg0, arg1, 2.0f, 0.002f, 0x4000);
    if ((arg0->unk_000.unk_024.y - GetModelBaseY(arg1)) >= 90.0f) {
        arg1->animationSubstate++;
        arg1->unk_448.unk_0C.y = 0.0f;
    }
}

void func_8430A4E0(UNUSED unk_BattlePlayerEntity* arg0, UNUSED unk_BattlePlayerEntity* arg1) {
}

void BattleAnim_StatusIdleCase14(unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1) {
    switch (arg1->animationSubstate) {
        case 0:
            BattleAnim_StatusIdleCase14Sub0(arg0, arg1);

        case 1:
            BattleAnim_StatusIdleCase14Sub1(arg0, arg1);
            break;

        case 2:
            func_8430A4E0(arg0, arg1);
            break;
    }
}

s32 BattleAnim_ApproachAngleAndCheckThreshold(unk_BattlePlayerEntity* arg0, s16 arg1, s16 arg2) {
    arg0->unk_000.unk_01E.y -= arg1;

    if (arg1 > 0) {
        if ((arg2 >= arg0->unk_000.unk_01E.y) && ((arg2 - arg1) < arg0->unk_000.unk_01E.y)) {
            return 1;
        }
    } else if ((arg0->unk_000.unk_01E.y >= arg2) && (arg0->unk_000.unk_01E.y < (arg2 - arg1))) {
        return 1;
    }

    return 0;
}

void BattleAnim_StatusIdleCase4Sub0(UNUSED unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1) {
    Entity_SetSubObjectCameraOffsets(arg1);
    arg1->unk_4A6 = 0;
    arg1->unk_4A4 = 0;
    arg1->moveAnimIndex = 0;
    arg1->animationSubstate++;
}

void BattleAnim_StatusIdleCase4Sub1(unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1) {
    arg1->unk_4A6 = Math_ApproachS32(arg1->unk_4A6, 0x3330, 0x16C, 0x16C);

    if (BattleAnim_ApproachAngleAndCheckThreshold(arg0, arg1->unk_4A6, arg1->sideSign << 0xE) != 0) {
        arg1->moveAnimIndex += 1;
    }

    Entity_UpdateCameraFromSubObject(arg1, arg1->unk_4A6);

    if (arg1->moveAnimIndex == 3) {
        arg1->animationSubstate += 1;
    }
}

void BattleAnim_StatusIdleCase4Sub2(unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1) {
    f32 tmp = 0x4000 - arg0->unk_000.unk_01E.y;
    f32 var_fa1;
    s16 sp26;
    s32 sp20;

    var_fa1 = (131072.0 - tmp) / 131072.0;
    if (var_fa1 >= 1.0f) {
        var_fa1 -= 1.0f;
    }

    sp26 = (arg1->unk_4A6 * var_fa1) * 0.8;
    if (sp26 < 0xE38) {
        sp26 = 0xE38;
    }
    sp20 = BattleAnim_ApproachAngleAndCheckThreshold(arg0, sp26, arg1->sideSign << 0xE);
    Entity_UpdateCameraFromSubObject(arg1, sp26);

    if (sp20 != 0) {
        arg0->unk_000.unk_01E.y = arg1->sideSign << 0xE;
        BattleScene_ResetParticipantModelFlags(arg1);
        Entity_ResetSubObjectFlags(arg1);
    }
}

void BattleAnim_StatusIdleCase4(unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1) {
    switch (arg1->animationSubstate) {
        case 0:
            BattleAnim_StatusIdleCase4Sub0(arg0, arg1);

        case 1:
            BattleAnim_StatusIdleCase4Sub1(arg0, arg1);
            break;

        case 2:
            BattleAnim_StatusIdleCase4Sub2(arg0, arg1);
            break;
    }
}

void BattleAnim_StatusIdleCase5Sub0(UNUSED unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1) {
    arg1->unk_4A6 = 0;
    arg1->unk_4A4 = 0;
    arg1->moveAnimIndex = 0;
    arg1->animationSubstate++;
}

void BattleAnim_StatusIdleCase5Sub1(unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1) {
    arg1->unk_4A6 = Math_ApproachS32(arg1->unk_4A6, 0x3FFC, 0x16C, 0x16C);

    if (BattleAnim_ApproachAngleAndCheckThreshold(arg0, arg1->unk_4A6, arg1->sideSign << 0xE) != 0) {
        arg1->moveAnimIndex += 1;
    }

    if (arg1->moveAnimIndex >= 3) {
        Entity_SetSubObjectCameraOffsets(arg1);
        arg1->animationSubstate += 1;
    }
}

void BattleAnim_StatusIdleCase5Sub2(unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1) {
    f32 sp34;
    f32 sp30;
    f32 sp2C;
    UNUSED s16 pad;
    u8 sp28[] = { 0x5F, 0x92 }; // D_84384650

    BattleAnim_ApproachAngleAndCheckThreshold(arg0, arg1->unk_4A6, arg1->sideSign << 0xE);

    if (Array_ContainsValue(arg1->unk_000.unk_01A, sp28, sizeof(sp28)) != 0) {
        sp30 = 10.3f;
        sp34 = 10.0f;
        sp2C = 0.035f;
    } else {
        sp30 = 3.8f;
        sp34 = 3.5f;
        sp2C = 0.045f;
    }

    Entity_UpdateCameraFromSubObject(arg1, arg1->unk_4A6);
    Math_ExponentialApproach(&arg0->unk_000.unk_024.y, -(Battle_GetEntityHeight(arg1) * sp30), sp2C);

    if (arg0->unk_000.unk_024.y <= -(Battle_GetEntityHeight(arg1) * sp34)) {
        Vec3s_Set(&arg0->unk_000.unk_01E, 0, arg1->sideSign << 0xE, 0);
        BattleScene_ResetParticipantModelFlags(arg1);
        Entity_ResetSubObjectFlags(arg1);
    }
}

void BattleAnim_StatusIdleCase5(unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1) {
    switch (arg1->animationSubstate) {
        case 0:
            BattleAnim_StatusIdleCase5Sub0(arg0, arg1);

        case 1:
            BattleAnim_StatusIdleCase5Sub1(arg0, arg1);
            break;

        case 2:
            BattleAnim_StatusIdleCase5Sub2(arg0, arg1);
            break;
    }
}

void BattleAnim_StatusIdleCase6Sub0(unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1) {
    arg1->unk_4A6 = 0;
    arg1->unk_4A4 = 0;
    arg1->moveAnimIndex = 0;
    arg1->oscillationAmplitude = 0.0f;
    UpdateEntityBasePosition(arg1);
    Vec3s_Set(&arg0->unk_000.unk_01E, 0, arg1->sideSign << 0xE, 0);
    Entity_SetSubObjectCameraOffsets(arg1);
    arg1->animationSubstate++;
}

void BattleAnim_StatusIdleCase6Sub1(unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1) {
    f32 tmp;
    Vec3f sp20 = { 0.0f, 0.0f, 0.0f }; // D_84384654

    Math_ExponentialApproach(&arg1->oscillationAmplitude, 50.0f, 0.1f);
    arg1->unk_4A6 += 0xE38;
    tmp = SINS(arg1->unk_4A6) * arg1->oscillationAmplitude;
    Vector_SetXZFromPolar(&sp20, tmp, arg0->unk_000.unk_01E.y);
    UpdateEntityBasePosition(arg1);
    Vec3f_Add(&arg0->unk_000.unk_024, &sp20);
    Entity_UpdateCameraFromSubObject(arg1, 0);

    if (arg1->oscillationAmplitude > 49.0f) {
        arg1->animationSubstate++;
    }
}

void BattleAnim_StatusIdleCase6Sub2(unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1) {
    f32 tmp;
    Vec3f sp20 = { 0.0f, 0.0f, 0.0f };

    Math_ExponentialApproach(&arg1->oscillationAmplitude, 0.0f, 0.1f);
    arg1->unk_4A6 += 0xE38;

    tmp = SINS(arg1->unk_4A6) * arg1->oscillationAmplitude;
    Vector_SetXZFromPolar(&sp20, tmp, arg0->unk_000.unk_01E.y);

    UpdateEntityBasePosition(arg1);
    Vec3f_Add(&arg0->unk_000.unk_024, &sp20);
    Entity_UpdateCameraFromSubObject(arg1, 0);

    if (arg1->oscillationAmplitude <= 0.5f) {
        UpdateEntityBasePosition(arg1);
        Vec3s_Set(&arg0->unk_000.unk_01E, 0, arg1->sideSign << 0xE, 0);
        BattleScene_ResetParticipantModelFlags(arg1);
        Entity_ResetSubObjectFlags(arg1);
    }
}

void BattleAnim_StatusIdleCase6(unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1) {
    switch (arg1->animationSubstate) {
        case 0:
            BattleAnim_StatusIdleCase6Sub0(arg0, arg1);

        case 1:
            BattleAnim_StatusIdleCase6Sub1(arg0, arg1);
            break;

        case 2:
            BattleAnim_StatusIdleCase6Sub2(arg0, arg1);
            break;
    }
}

void BattleAnim_StatusIdleCase7Sub0(unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1) {
    Entity_InitSubObjects(arg1);
    arg1->frameCounter = 0;
    UpdateEntityBasePosition(arg1);
    Vec3s_Set(&arg0->unk_000.unk_01E, 0, arg1->sideSign << 0xE, 0);
    arg1->animationSubstate++;
}

void BattleAnim_StatusIdleCase7Sub1(UNUSED unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1) {
    Entity_AnimateSubObjects(arg1);
    arg1->frameCounter++;
    if (arg1->frameCounter == 0x3C) {
        BattleScene_ResetParticipantModelFlags(arg1);
        Entity_ResetSubObjectFlags(arg1);
    }
}

void BattleAnim_StatusIdleCase7(unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1) {
    switch (arg1->animationSubstate) {
        case 0:
            BattleAnim_StatusIdleCase7Sub0(arg0, arg1);

        case 1:
            BattleAnim_StatusIdleCase7Sub1(arg0, arg1);
            break;
    }
}

void BattleAnim_ResetOwnerFacingAndExitStatusIdle(unk_BattlePlayerEntity* arg0) {
    UNUSED s32 pad;
    CameraStruct* sp18 = gBattleState.unk_00->unk_DC;

    UpdateEntityBasePosition(arg0);
    Vec3s_Set(&arg0->unk_000.unk_01E, 0, arg0->sideSign << 0xE, 0);
    Vec3f_Set(&sp18->unk_60.up, 0.0f, 1.0f, 0.0f);
    BattleScene_ResetParticipantModelFlags(arg0);
}

void BattleAnim_StatusIdleCase8Sub0(unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1) {
    arg1->unk_4A6 = 0;
    arg1->tiltAngle = 0;
    arg1->unk_4A4 = 0;
    arg1->moveAnimIndex = 0;
    arg1->oscillationAmplitude = 0.0f;
    UpdateEntityBasePosition(arg1);
    Vec3s_Set(&arg0->unk_000.unk_01E, 0, arg1->sideSign << 0xE, 0);
    arg1->animationSubstate++;
}

void BattleAnim_StatusIdleCase8Sub1(UNUSED unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1) {
    CameraStruct* temp_s0 = gBattleState.unk_00->unk_DC;
    f32 temp_fa0;
    f32 temp_fa1_2;
    f32 temp_ft4;
    f32 sp2C;
    f32 sp28;
    f32 sp24;
    f32 temp_fv0_2;
    f32 temp_fv1_2;

    Math_StepTowards(&arg1->unk_4A4, 0x5B0, 0x3C);
    Math_StepTowards(&arg1->tiltAngle, -0x8000, arg1->unk_4A4);

    sp2C = temp_s0->unk_60.at.x - temp_s0->unk_60.eye.x;
    sp28 = temp_s0->unk_60.at.y - temp_s0->unk_60.eye.y;
    sp24 = temp_s0->unk_60.at.z - temp_s0->unk_60.eye.z;

    temp_fv0_2 = sqrtf(SQ(sp2C) + SQ(sp28) + SQ(sp24));

    temp_fa0 = sp2C / temp_fv0_2;
    temp_fv1_2 = sp28 / temp_fv0_2;
    temp_fa1_2 = sp24 / temp_fv0_2;

    temp_ft4 = 1.0 - COSS(arg1->tiltAngle);

    temp_s0->unk_60.up.x = (temp_ft4 * temp_fa0 * temp_fv1_2) - (SINS(arg1->tiltAngle) * temp_fa1_2);
    temp_s0->unk_60.up.y = COSS(arg1->tiltAngle) + ((temp_ft4 * temp_fv1_2) * temp_fv1_2);
    temp_s0->unk_60.up.z = (SINS(arg1->tiltAngle) * temp_fa0) + ((temp_ft4 * temp_fv1_2) * temp_fa1_2);

    if (arg1->unk_000.unk_024.y < 0.0f) {
        arg1->unk_000.unk_024.y = 0.0f;
    }
}

void BattleAnim_StatusIdleCase8(unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1) {
    switch (arg1->animationSubstate) {
        case 0:
            BattleAnim_StatusIdleCase8Sub0(arg0, arg1);

        case 1:
            BattleAnim_StatusIdleCase8Sub1(arg0, arg1);
            break;
    }
}

void BattleAnim_StatusIdleCase9Sub0(unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1) {
    if (arg0->unk_000.unk_030.y != 1.0f) {
        BattleScene_ResetParticipantModelFlags(arg1);
    } else {
        Entity_ActivateSubObjects(arg1);
        arg1->animationSubstate++;
    }
}

void BattleAnim_StatusIdleCase9Sub1(unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1) {
    f32 temp_fv0;

    temp_fv0 = Math_ApproachF32(arg0->unk_000.unk_030.x, 0.8f, 0.01f, 0.01f);
    arg0->unk_000.unk_030.x = temp_fv0;
    arg0->unk_000.unk_030.y = temp_fv0;
    arg0->unk_000.unk_030.z = temp_fv0;

    Entity_ScaleSubObjects(arg1);

    if (arg0->unk_000.unk_030.y <= 0.8) {
        BattleScene_ResetParticipantModelFlags(arg1);
        Entity_ResetSubObjectFlags(arg1);
    }
}

void BattleAnim_StatusIdleCase9(unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1) {
    switch (arg1->animationSubstate) {
        case 0:
            BattleAnim_StatusIdleCase9Sub0(arg0, arg1);

        case 1:
            BattleAnim_StatusIdleCase9Sub1(arg0, arg1);
            break;
    }
}

void BattleAnim_StatusIdleCase12Sub0(UNUSED unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1) {
    arg1->animationSubstate++;
}

void BattleAnim_StatusIdleCase12Sub1(unk_BattlePlayerEntity* arg0, UNUSED unk_BattlePlayerEntity* arg1) {
    arg0->unk_000.unk_030.x = Math_ApproachF32(arg0->unk_000.unk_030.x, 0.0f, 0.05f, 0.05f);
    arg0->unk_000.unk_030.y = Math_ApproachF32(arg0->unk_000.unk_030.y, 0.0f, 0.05f, 0.05f);
    arg0->unk_000.unk_030.z = Math_ApproachF32(arg0->unk_000.unk_030.z, 0.0f, 0.05f, 0.05f);

    if (arg0->unk_000.unk_030.y <= 0.1) {
        Vec3f_Set(&arg0->unk_000.unk_030, 0.001f, 0.001f, 0.001f);
    }
}

void BattleAnim_StatusIdleCase12(unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1) {
    switch (arg1->animationSubstate) {
        case 0:
            BattleAnim_StatusIdleCase12Sub0(arg0, arg1);

        case 1:
            BattleAnim_StatusIdleCase12Sub1(arg0, arg1);
            break;
    }
}

void BattleAnim_StatusIdleCase13Sub0(unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1) {
    arg1->unk_4A4 = 0x16C;
    arg1->unk_4A6 = 0;
    arg1->tiltAngle = 0;
    arg1->oscillationAmplitude = 0.4f;
    arg1->unk_448.unk_0C.x = arg0->unk_000.unk_030.x;
    arg1->unk_448.unk_0C.y = arg0->unk_000.unk_030.y;
    arg1->unk_448.unk_0C.z = arg0->unk_000.unk_030.z;
    arg1->animationSubstate++;
}

void BattleAnim_StatusIdleCase13Sub1(unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1) {
    f32 var_fv0;

    // clang-format off
    if ((arg1->unk_4A4 >= 0) && (arg1->unk_4A4 <= 0x8000)) { arg1->unk_4A4 += 0x2D; }
    // clang-format on

    arg1->tiltAngle = SINS(arg1->unk_4A4) * 182.0f * 15.0f;

    if ((arg1->unk_4A6 >= 0) && (arg1->unk_4A6 <= 0x4000)) {
        arg1->unk_4A6 += arg1->tiltAngle;
    }

    if (arg1->animationState.unk_38.unk_56 == 0) {
        var_fv0 = 1.0f;
    } else {
        var_fv0 = 0.8f;
    }

    arg0->unk_000.unk_030.x = var_fv0 - (SINS(arg1->unk_4A6) * arg1->oscillationAmplitude);
    arg0->unk_000.unk_030.y = (SINS(arg1->unk_4A6) * arg1->oscillationAmplitude) + var_fv0;
    arg0->unk_000.unk_030.z = var_fv0 - (SINS(arg1->unk_4A6) * arg1->oscillationAmplitude);

    if ((arg1->unk_4A6 >= 0x4000) && (arg1->unk_4A6 >= 0x4000)) {
        arg1->tiltAngle = 0x1554;
        arg1->animationSubstate++;
    }
}

void BattleAnim_StatusIdleCase13Sub2(unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1) {
    f32 var_fv0;
    f32 var_fv1;

    arg1->unk_4A6 += arg1->tiltAngle;
    var_fv1 = SINS(arg1->unk_4A6) * arg1->oscillationAmplitude;
    if (var_fv1 <= 0.01f) {
        arg1->tiltAngle += 0x444;
        arg1->oscillationAmplitude *= 0.8f;
        if (1) {}
        var_fv1 = SINS(arg1->unk_4A6) * arg1->oscillationAmplitude;
    }

    if (arg1->animationState.unk_38.unk_56 == 0) {
        var_fv0 = 1.0f;
    } else {
        var_fv0 = 0.8f;
    }

    arg0->unk_000.unk_030.x = var_fv0 - var_fv1;
    arg0->unk_000.unk_030.y = (SINS(arg1->unk_4A6) * arg1->oscillationAmplitude) + var_fv0;
    arg0->unk_000.unk_030.z = var_fv0 - (SINS(arg1->unk_4A6) * arg1->oscillationAmplitude);

    if (arg1->oscillationAmplitude <= 0.01f) {
        arg0->unk_000.unk_030.x = var_fv0;
        arg0->unk_000.unk_030.y = var_fv0;
        arg0->unk_000.unk_030.z = var_fv0;
        BattleScene_ResetParticipantModelFlags(arg1);
    }
}

void BattleAnim_StatusIdleCase13(unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1) {
    switch (arg1->animationSubstate) {
        case 0:
            BattleAnim_StatusIdleCase13Sub0(arg0, arg1);

        case 1:
            BattleAnim_StatusIdleCase13Sub1(arg0, arg1);
            break;

        case 2:
            BattleAnim_StatusIdleCase13Sub2(arg0, arg1);
            break;
    }
}

void BattleAnim_StatusIdleCase15Sub0(unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1) {
    arg1->tiltAngle = 0x71C;
    arg1->oscillationAmplitude = 0.4f;
    arg1->unk_448.unk_0C.x = arg0->unk_000.unk_030.x;
    arg1->unk_448.unk_0C.y = arg0->unk_000.unk_030.y;
    arg1->unk_448.unk_0C.z = arg0->unk_000.unk_030.z;
    arg1->animationSubstate++;
}

void BattleAnim_StatusIdleCase15Sub1(unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1) {
    PokemonAudioInfo* temp_a0 = &arg1->animationState.unk_38;
    s16 sp22;

    arg1->tiltAngle += 0xCCC;
    sp22 = arg1->tiltAngle;

    arg1->oscillationAmplitude = Math_ApproachF32(arg1->oscillationAmplitude, 0.0f, 0.02f, 0.02f);

    if (sp22 > 0) {
        sp22 *= -1;
    }

    if (temp_a0->unk_56 == 0) {
        arg0->unk_000.unk_030.x = 1.0f - (SINS(sp22) * arg1->oscillationAmplitude);
        arg0->unk_000.unk_030.y = (SINS(sp22) * arg1->oscillationAmplitude) + 1.0f;
        arg0->unk_000.unk_030.z = 1.0f - (SINS(sp22) * arg1->oscillationAmplitude);
    } else {
        arg0->unk_000.unk_030.x = 0.8 - (SINS(sp22) * arg1->oscillationAmplitude);
        arg0->unk_000.unk_030.y = (SINS(sp22) * arg1->oscillationAmplitude) + 0.8;
        arg0->unk_000.unk_030.z = 0.8 - (SINS(sp22) * arg1->oscillationAmplitude);
    }

    if (arg1->oscillationAmplitude <= 0.01f) {
        if (temp_a0->unk_56 == 0) {
            Vec3f_Set(&arg0->unk_000.unk_030, 1.0f, 1.0f, 1.0f);
        } else {
            Vec3f_Set(&arg0->unk_000.unk_030, 0.8f, 0.8f, 0.8f);
        }
        BattleScene_ResetParticipantModelFlags(arg1);
    }
}

void BattleAnim_StatusIdleCase15(unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1) {
    switch (arg1->animationSubstate) {
        case 0:
            BattleAnim_StatusIdleCase15Sub0(arg0, arg1);

        case 1:
            BattleAnim_StatusIdleCase15Sub1(arg0, arg1);
            break;
    }
}

void BattleAnim_StatusIdleCase16Sub0(UNUSED unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1) {
    arg1->frameCounter = 0;
    arg1->animationSubstate++;
}

void BattleAnim_StatusIdleCase16Sub1(unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1) {
    PokemonAudioInfo* ptr = &arg1->animationState.unk_38;
    UNUSED s32 pad;
    f32 temp_fs0;

    if (ptr->unk_56 == 0) {
        temp_fs0 = (1.0f - Trail_GetWidthScale()) * 0.6f;
        Math_ExponentialApproach(&arg0->unk_000.unk_030.x, 1.0f - temp_fs0, 0.5f);
        Math_ExponentialApproach(&arg0->unk_000.unk_030.y, 1.0f + temp_fs0, 0.5f);
        Math_ExponentialApproach(&arg0->unk_000.unk_030.z, 1.0f - temp_fs0, 0.5f);
    } else {
        temp_fs0 = (1.0f - Trail_GetWidthScale()) * 0.3f;
        Math_ExponentialApproach(&arg0->unk_000.unk_030.x, 0.8 - temp_fs0, 0.5f);
        Math_ExponentialApproach(&arg0->unk_000.unk_030.y, temp_fs0 + 0.8, 0.5f);
        Math_ExponentialApproach(&arg0->unk_000.unk_030.z, 0.8 - temp_fs0, 0.5f);
    }
}

void BattleAnim_StatusIdleCase16(unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1) {
    switch (arg1->animationSubstate) {
        case 0:
            BattleAnim_StatusIdleCase16Sub0(arg0, arg1);

        case 1:
            BattleAnim_StatusIdleCase16Sub1(arg0, arg1);
            break;
    }
}

void BattleAnim_StatusIdleCase10Sub0(UNUSED unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1) {
    arg1->moveAnimIndex = 0;
    arg1->animationSubstate++;
}

void BattleAnim_StatusIdleCase10Sub1(unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1) {
    f32 sp24;
    f32 sp20;

    arg1->moveAnimIndex++;
    sp20 = TerrainGrid_SampleHeightAndSlope(arg0->unk_000.unk_024.x, arg0->unk_000.unk_024.z, &sp24);
    arg0->unk_000.unk_024.y = GetModelBaseY(arg1) + sp20;
    arg0->unk_000.unk_01E.x = (s16)sp24 * 0xB6;

    if (arg1->moveAnimIndex == 0x12C) {
        arg0->unk_000.unk_024.y = GetModelBaseY(arg1);
        arg0->unk_000.unk_01E.x = 0;
        BattleScene_ResetParticipantModelFlags(arg1);
    }
}

void BattleAnim_StatusIdleCase10(unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1) {
    switch (arg1->animationSubstate) {
        case 0:
            BattleAnim_StatusIdleCase10Sub0(arg0, arg1);

        case 1:
            BattleAnim_StatusIdleCase10Sub1(arg0, arg1);
            break;
    }
}

void BattleAnim_StatusIdleCase0(UNUSED unk_BattlePlayerEntity* arg0, UNUSED unk_BattlePlayerEntity* arg1) {
}

void Battle_ClearAnimFlags(s32 arg0) {
    unk_BattlePlayerEntity* temp_a1 = sActivePokemon[arg0];
    unk_BattlePlayerEntity* temp_a2 = sActivePokemon[arg0];

    switch (sActivePokemon[arg0]->animationMode) {
        case 0:
            BattleAnim_StatusIdleCase0(temp_a1, temp_a2);
            break;

        case 1:
            Entity_StateMachine_Dispatch(temp_a1, temp_a2);
            break;

        case 2:
            BattleAnim_StatusIdleCase2(temp_a1, temp_a2);
            break;

        case 3:
            BattleAnim_StatusIdleCase3(temp_a1, temp_a2);
            break;

        case 4:
            BattleAnim_StatusIdleCase4(temp_a1, temp_a2);
            break;

        case 5:
            BattleAnim_StatusIdleCase5(temp_a1, temp_a2);
            break;

        case 6:
            BattleAnim_StatusIdleCase6(temp_a1, temp_a2);
            break;

        case 7:
            BattleAnim_StatusIdleCase7(temp_a1, temp_a2);
            break;

        case 8:
            BattleAnim_StatusIdleCase8(temp_a1, temp_a2);
            break;

        case 9:
            BattleAnim_StatusIdleCase9(temp_a1, temp_a2);
            break;

        case 10:
            BattleAnim_StatusIdleCase10(temp_a1, temp_a2);
            break;

        case 12:
            BattleAnim_StatusIdleCase12(temp_a1, temp_a2);
            break;

        case 13:
            BattleAnim_StatusIdleCase13(temp_a1, temp_a2);
            break;

        case 14:
            BattleAnim_StatusIdleCase14(temp_a1, temp_a2);
            break;

        case 15:
            BattleAnim_StatusIdleCase15(temp_a1, temp_a2);
            break;

        case 16:
            BattleAnim_StatusIdleCase16(temp_a1, temp_a2);
            break;

        default:
            BattleScene_ResetParticipantModelFlags(temp_a2);
            break;
    }
}

void BattleAnim_SetOwnerSecondaryStatusFlags(unk_BattlePlayerEntity* arg0, u8 arg1, u8 arg2) {
    arg0->secondaryStatusId = arg1;
    arg0->secondaryStatusState = arg2;
}

void BattleAnim_ClearOwnerSecondaryStatusFlags(unk_BattlePlayerEntity* arg0) {
    arg0->secondaryStatusId = 0;
    arg0->secondaryStatusState = 0;
}

void BattleAnim_InitSecondarySwayOffset(unk_BattlePlayerEntity* arg0, f32 arg1, s16 arg2) {
    arg0->swayMagnitude = arg1;
    arg0->secondarySwayOffset.z = COSS(arg2) * arg1;
    arg0->secondarySwayOffset.y = SINS(arg2) * arg1;
}

void BattleAnim_UpdateSecondarySwayPhysics(unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1, UNUSED f32 arg2, UNUSED f32 arg3, UNUSED s32 arg4) {
    f32 tmp1 = 0.01f;
    f32 tmp2 = 18.0f;
    Vec3f sp2C;
    f32 temp_fa1;
    f32 temp_fa2;

    temp_fa1 = -tmp1 * arg1->secondarySwayOffset.z;
    temp_fa2 = -tmp2 - (tmp1 * arg1->secondarySwayOffset.y);

    arg1->secondarySwayOffset.z = arg1->secondarySwayOffset.z + (temp_fa1 * 0.05f);
    arg1->secondarySwayOffset.y = arg1->secondarySwayOffset.y + (temp_fa2 * 0.05f);
    sp2C.y = arg1->secondarySwayOffset.y;
    arg1->secondarySwayOffset.x = 0.0f;

    Vector_SetXZFromPolar(&sp2C, arg1->secondarySwayOffset.z, arg0->unk_000.unk_01E.y + 0x4000);
    Vec3f_Add(&arg0->unk_000.unk_024, &sp2C);
}

void BattleAnim_SecondaryStatusCaseBSub0(UNUSED unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1) {
    Vec3f_Set(&arg1->unk_4CC, 0.0f, 0.0f, 0.0f);
    Vec3f_Set(&arg1->secondarySwayOffset, 0.0f, 0.0f, 0.0f);
    BattleAnim_InitSecondarySwayOffset(arg1, 23.0f, 0x2E36);
    arg1->secondaryStatusState++;
}

void BattleAnim_SecondaryStatusCaseBSub1(unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1) {
    BattleAnim_UpdateSecondarySwayPhysics(arg0, arg1, 0, 0, 0x2E36);
    if (arg1->unk_000.unk_024.y < GetModelBaseY(arg1)) {
        arg1->secondarySwayOffset.y = 0.0f;
        arg1->unk_000.unk_024.y = GetModelBaseY(arg1);
        BattleAnim_ClearOwnerSecondaryStatusFlags(arg1);
    }
}

void BattleAnim_SecondaryStatusCaseB(unk_BattlePlayerEntity* arg0, unk_BattlePlayerEntity* arg1) {
    switch (arg1->secondaryStatusState) {
        case 0:
            BattleAnim_SecondaryStatusCaseBSub0(arg0, arg1);

        case 1:
            BattleAnim_SecondaryStatusCaseBSub1(arg0, arg1);
            break;
    }
}

void BattleAnim_SecondaryStatusDefault(UNUSED unk_BattlePlayerEntity* arg0, UNUSED unk_BattlePlayerEntity* arg1) {
}

void BattleAnim_UpdateOwnerSecondaryStatusAnimation(s32 arg0) {
    unk_BattlePlayerEntity* temp_v0 = sActivePokemon[arg0];
    unk_BattlePlayerEntity* temp_v1 = sActivePokemon[arg0];

    if (temp_v1->secondaryStatusId == 0xB) {
        BattleAnim_SecondaryStatusCaseB(temp_v0, temp_v1);
    } else {
        BattleAnim_SecondaryStatusDefault(temp_v0, temp_v1);
    }
}

static s32 pad_D_8438466C = 0;

s16 gAnimLookupTable[] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,    0,    0, 0xA9, 0, 0, 0, 0, 0, 0xAA, 0, 0, 0, 0, 0, 0,    0, 0, 0, 0, 0, 0,    0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,    0,    0, 0,    0, 0, 0, 0, 0, 0,    0, 0, 0, 0, 0, 0,    0, 0, 0, 0, 0, 0,    0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0xAB, 0,    0, 0,    0, 0, 0, 0, 0, 0,    0, 0, 0, 0, 0, 0xAC, 0, 0, 0, 0, 0, 0,    0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,    0,    0, 0,    0, 0, 0, 0, 0, 0,    0, 0, 0, 0, 0, 0,    0, 0, 0, 0, 0, 0xAD, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,    0xAE, 0, 0,    0, 0, 0, 0, 0, 0,    0, 0, 0, 0, 0, 0,    0, 0, 0, 0, 0, 0,    0, 0,
};

unk_D_843847BC gEntityInitParams[2] = {
    {
        0xFFB8,
        0x0048,
        0x0020,
        10.0f,
        10.0f,
        1280.0f,
        0x0001,
    },
    {
        0x015F,
        0x0080,
        0x0020,
        10.0f,
        10.0f,
        1280.0f,
        0xFFFF,
    },
};

unk_D_86B0C160 gCameraFovyPresetRandom[] = {
    {
        0,
        0,
        0,
        0,
        14563,
        0.0f,
        4.5f,
        0,
        0,
        0,
        9102,
        0,
        0.0f,
        8.5f,
        0.10000000149011612f,
        0.019999999552965164f,
        30.0f,
    },
    {
        0,
        0,
        0,
        0,
        12743,
        0.0f,
        8.0f,
        0,
        0,
        0,
        0,
        0,
        0.0f,
        4.0f,
        0.15000000596046448f,
        0.009999999776482582f,
        30.0f,
    },
    {
        0,
        16384,
        0,
        0,
        7281,
        3.5f,
        3.0f,
        0,
        -16384,
        0,
        0,
        0,
        0.0f,
        3.0f,
        0.15000000596046448f,
        0.019999999552965164f,
        50.0f,
    },
};
unk_D_86B0C160 gCameraFovyPresetSpecial[] = {
    {
        0,
        0,
        0,
        364,
        7281,
        0.0f,
        8.0f,
        0,
        0,
        0,
        364,
        0,
        1.0f,
        2.0f,
        0.30000001192092896f,
        0.009999999776482582f,
        70.0f,
    },
    {
        0,
        0,
        0,
        0,
        30030,
        0.0f,
        3.5f,
        0,
        0,
        0,
        1820,
        3640,
        0.0f,
        20.0f,
        0.15000000596046448f,
        0.009999999776482582f,
        50.0f,
    },
};

unk_D_86B0C160 gCameraPosB = {
    0, 0, 0, 0, 0, 0.0f, 0.0f, 0, 0, 0, 0, 5461, 0.0f, 3.5f, 0.20000000298023224f, 0.05999999865889549f, 200.0f,
};

unk_D_86B0C160 gCameraPosD = {
    0, 0, 0, 0, 0, 0.0f, 0.0f, 0, 0, 0, 4550, 31850, 0.0f, 6.0f, 0.20000000298023224f, 0.03999999910593033f, 200.0f,
};

unk_D_86B0C160 gCameraPosC = {
    0, 0, 0, 0, 0, 0.0f, 0.0f, 0, 0, 0, 3640, -32768, 0.0f, 6.0f, 0.20000000298023224f, 0.07999999821186066f, 200.0f,
};

unk_D_86B0C160 gCameraPosA = {
    0, 0, 0, 0, 0, 0.0f, 0.0f, 0, 0, 0, 0, 0, 0.0f, 3.5f, 0.20000000298023224f, 0.05999999865889549f, 200.0f,
};

unk_D_86B0C160 gBattleCameraPresetTable[] = {
    {
        0,
        0,
        0,
        0,
        14563,
        1.0f,
        4.5f,
        0,
        0,
        0,
        9102,
        0,
        0.0f,
        8.5f,
        0.10000000149011612f,
        0.019999999552965164f,
        200.0f,
    },
    {
        0,
        0,
        0,
        10922,
        0,
        0.0f,
        8.5f,
        0,
        0,
        0,
        0,
        0,
        0.0f,
        4.0f,
        0.25f,
        0.019999999552965164f,
        200.0f,
    },
    {
        0,
        0,
        0,
        0,
        14563,
        0.0f,
        3.5f,
        0,
        0,
        0,
        9102,
        7281,
        0.0f,
        8.5f,
        0.15000000596046448f,
        0.019999999552965164f,
        200.0f,
    },
    {
        0,
        0,
        0,
        0,
        14563,
        0.0f,
        6.5f,
        0,
        0,
        0,
        0,
        0,
        0.0f,
        4.0f,
        0.20000000298023224f,
        0.019999999552965164f,
        200.0f,
    },
    {
        0,
        0,
        0,
        7281,
        16384,
        0.0f,
        7.5f,
        0,
        0,
        0,
        0,
        0,
        0.0f,
        3.5f,
        0.20000000298023224f,
        0.019999999552965164f,
        200.0f,
    },
    {
        0,
        0,
        0,
        -1820,
        16384,
        0.0f,
        4.5f,
        0,
        0,
        0,
        1820,
        0,
        0.0f,
        3.5f,
        0.20000000298023224f,
        0.019999999552965164f,
        200.0f,
    },
};

unk_D_86B0C160 gBattleCameraPresetE = {
    0, 0, 0, 2184, 0, 0.0f, 10.5f, 0, 0, 0, 182, 0, 0.0f, 2.0f, 0.20000000298023224f, 0.014999999664723873f, 50.0f,
};

unk_D_86B0C160 gBattleCameraPresetTable2[] = {
    {
        0,
        0,
        0,
        10922,
        0,
        0.0f,
        600.0f,
        0,
        0,
        0,
        0,
        0,
        0.0f,
        550.0f,
        0.20000000298023224f,
        0.03999999910593033f,
        40.0f,
    },
    {
        0,
        0,
        0,
        10922,
        12743,
        0.0f,
        625.0f,
        0,
        0,
        0,
        0,
        0,
        0.0f,
        450.0f,
        0.20000000298023224f,
        0.029999999329447746f,
        40.0f,
    },
    {
        0,
        0,
        0,
        -546,
        0,
        0.0f,
        450.0f,
        0,
        0,
        0,
        10922,
        0,
        0.0f,
        500.0f,
        0.20000000298023224f,
        0.02500000037252903f,
        40.0f,
    },
    {
        0,
        0,
        0,
        0,
        -12743,
        0.0f,
        750.0f,
        0,
        0,
        0,
        0,
        0,
        0.0f,
        450.0f,
        0.20000000298023224f,
        0.03999999910593033f,
        40.0f,
    },
    {
        0,
        0,
        0,
        -546,
        0,
        0.0f,
        50.0f,
        0,
        0,
        0,
        -546,
        0,
        0.0f,
        400.0f,
        0.20000000298023224f,
        0.029999999329447746f,
        80.0f,
    },
};

Vec3f gCameraOffsetTable[] = {
    { 0.17000000178813934f, 11.5f, -1.5f },
    { 0.10999999940395355f, 27.0f, -2.5f },
    { 0.12999999523162842f, 55.0f, 15.0f },
    { 0.2199999988079071f, 0.0f, -0.5f },
    { 0.1599999964237213f, 14.5f, 2.5f },
    { 0.3199999928474426f, 0.0f, 0.0f },
    { 0.20000000298023224f, 7.0f, 0.5f },
    { 0.20999999344348907f, 12.0f, -3.5f },
    { 0.23000000417232513f, -18.5f, 9.5f },
    { 0.4099999964237213f, -2.5f, -1.5f },
    { 0.1899999976158142f, 7.0f, 1.0f },
    { 0.2800000011920929f, 0.0f, 4.0f },
    { 0.2800000011920929f, 2.5f, 0.5f },
    { 0.23999999463558197f, -1.5f, -3.0f },
    { 0.2199999988079071f, 6.0f, 6.5f },
    { 0.6800000071525574f, -1.5f, -1.5f },
    { 0.800000011920929f, 0.0f, -3.5f },
    { 0.49000000953674316f, -0.5f, -55.0f },
    { 0.27000001072883606f, 2.5f, 2.5f },
    { 0.2800000011920929f, 0.0f, 0.0f },
    { 0.28999999165534973f, 4.0f, -2.5f },
    { 0.23999999463558197f, 0.0f, 2.5f },
    { 0.27000001072883606f, 0.0f, -6.0f },
    { 0.2800000011920929f, 7.5f, 17.5f },
    { 0.33000001311302185f, 0.0f, -3.0f },
    { 0.4000000059604645f, 0.0f, -6.0f },
    { 0.4000000059604645f, 0.0f, -7.0f },
    { 0.28999999165534973f, 0.0f, -5.5f },
    { 0.20999999344348907f, 5.5f, 5.0f },
    { 0.20999999344348907f, 6.5f, 0.0f },
    { 0.2199999988079071f, 11.0f, -7.5f },
    { 0.23999999463558197f, 8.5f, 3.0f },
    { 0.1599999964237213f, 17.5f, 0.0f },
    { 0.20999999344348907f, 14.0f, -6.5f },
    { 0.18000000715255737f, 0.0f, 3.0f },
    { 0.15000000596046448f, 9.0f, 9.0f },
    { 0.3100000023841858f, 0.0f, -2.5f },
    { 0.18000000715255737f, 0.0f, 4.5f },
    { 0.23000000417232513f, 0.0f, 0.0f },
    { 0.1899999976158142f, 0.0f, 15.0f },
    { 0.4099999964237213f, -2.0f, 0.0f },
    { 0.5400000214576721f, -34.5f, -43.5f },
    { 0.20999999344348907f, 0.0f, -2.0f },
    { 0.20999999344348907f, 0.0f, 0.0f },
    { 0.23999999463558197f, 0.0f, 14.0f },
    { 0.27000001072883606f, 0.0f, -2.5f },
    { 0.12999999523162842f, 8.5f, 2.5f },
    { 0.12999999523162842f, 14.0f, 11.5f },
    { 0.4000000059604645f, 0.0f, 0.0f },
    { 0.2199999988079071f, 0.0f, 0.0f },
    { 0.20000000298023224f, 0.0f, 0.0f },
    { 0.4000000059604645f, 0.0f, 0.0f },
    { 0.15000000596046448f, 19.5f, -2.5f },
    { 0.1599999964237213f, 3.5f, 3.5f },
    { 0.1899999976158142f, 10.5f, -8.0f },
    { 0.4000000059604645f, 0.0f, 0.0f },
    { 0.20999999344348907f, 0.0f, -5.5f },
    { 0.23999999463558197f, 3.5f, 1.5f },
    { 0.1899999976158142f, 21.5f, 6.0f },
    { 0.28999999165534973f, 0.0f, 0.0f },
    { 0.23000000417232513f, 0.0f, 0.0f },
    { 0.2199999988079071f, -4.5f, -0.5f },
    { 0.23000000417232513f, 4.0f, 0.0f },
    { 0.1899999976158142f, 16.0f, -2.5f },
    { 0.18000000715255737f, 14.0f, -4.0f },
    { 0.15000000596046448f, 11.0f, 0.0f },
    { 0.25f, 8.5f, -6.0f },
    { 0.25f, 10.0f, -4.0f },
    { 0.3700000047683716f, 0.0f, -5.0f },
    { 0.20000000298023224f, 0.0f, 0.0f },
    { 0.14000000059604645f, 17.5f, 16.5f },
    { 0.23999999463558197f, 0.0f, 0.0f },
    { 0.23999999463558197f, 0.0f, 0.0f },
    { 0.28999999165534973f, 0.0f, 0.0f },
    { 0.1899999976158142f, 0.0f, 0.0f },
    { 0.1899999976158142f, 11.0f, 0.0f },
    { 0.1599999964237213f, 8.0f, 0.0f },
    { 0.17000000178813934f, -7.5f, -7.0f },
    { 0.25999999046325684f, 12.5f, 5.0f },
    { 0.1899999976158142f, 0.0f, 2.5f },
    { 0.2800000011920929f, 0.0f, 0.0f },
    { 0.23000000417232513f, 0.0f, 0.0f },
    { 0.28999999165534973f, 0.0f, -3.0f },
    { 0.25f, 0.0f, 0.0f },
    { 0.23000000417232513f, 0.0f, 0.0f },
    { 0.25999999046325684f, 8.5f, 2.5f },
    { 0.23000000417232513f, 22.5f, 7.5f },
    { 0.25f, 0.0f, -2.5f },
    { 0.18000000715255737f, 0.0f, 5.0f },
    { 0.20000000298023224f, 0.0f, 2.0f },
    { 0.28999999165534973f, 0.0f, 0.0f },
    { 0.1599999964237213f, 0.0f, 0.0f },
    { 0.17000000178813934f, 5.0f, 0.0f },
    { 0.25999999046325684f, 0.0f, -10.5f },
    { 0.03999999910593033f, 74.0f, -7.5f },
    { 0.20999999344348907f, 7.5f, -1.0f },
    { 0.20000000298023224f, 0.0f, -0.5f },
    { 0.2199999988079071f, 0.0f, 0.0f },
    { 0.20000000298023224f, 0.0f, 9.5f },
    { 0.17000000178813934f, 0.0f, 0.0f },
    { 0.1899999976158142f, 0.0f, 0.0f },
    { 0.1899999976158142f, 0.0f, -3.5f },
    { 0.25f, 0.0f, 9.0f },
    { 0.2199999988079071f, 1.5f, -1.0f },
    { 0.23999999463558197f, -2.5f, -4.5f },
    { 0.23000000417232513f, -4.0f, 0.0f },
    { 0.23000000417232513f, 0.0f, 0.0f },
    { 0.27000001072883606f, 0.0f, 0.0f },
    { 0.17000000178813934f, 0.0f, 4.0f },
    { 0.20999999344348907f, -11.0f, 5.5f },
    { 0.17000000178813934f, 8.0f, 0.0f },
    { 0.2199999988079071f, 0.0f, 4.5f },
    { 0.1599999964237213f, 0.0f, 12.5f },
    { 0.15000000596046448f, 4.5f, 8.0f },
    { 0.28999999165534973f, 0.0f, 0.0f },
    { 0.25f, 0.0f, 5.0f },
    { 0.25f, 6.5f, 3.0f },
    { 0.3100000023841858f, 0.0f, 0.5f },
    { 0.23999999463558197f, 18.0f, 0.0f },
    { 0.1899999976158142f, 0.0f, 0.0f },
    { 0.14000000059604645f, 0.0f, 0.0f },
    { 0.23999999463558197f, 0.0f, 0.0f },
    { 0.23999999463558197f, 12.5f, 0.0f },
    { 0.18000000715255737f, 0.0f, 0.0f },
    { 0.18000000715255737f, 9.0f, 0.0f },
    { 0.20999999344348907f, 10.0f, -2.5f },
    { 0.20999999344348907f, 0.0f, 0.0f },
    { 0.1599999964237213f, 12.0f, 5.0f },
    { 0.4000000059604645f, -1.5f, 23.0f },
    { 0.14000000059604645f, 49.0f, 28.0f },
    { 0.20000000298023224f, 22.5f, 8.5f },
    { 0.25999999046325684f, 0.0f, 0.0f },
    { 0.2800000011920929f, 0.0f, 0.0f },
    { 0.25999999046325684f, 0.0f, 4.0f },
    { 0.25f, 11.0f, 0.0f },
    { 0.23000000417232513f, 8.0f, 0.0f },
    { 0.18000000715255737f, 5.5f, 4.5f },
    { 0.2199999988079071f, -0.5f, 2.5f },
    { 0.25f, 0.0f, 0.0f },
    { 0.25999999046325684f, 0.0f, -1.5f },
    { 0.20999999344348907f, 0.0f, 3.5f },
    { 0.1599999964237213f, 32.5f, 26.5f },
    { 0.05000000074505806f, -15.5f, -133.5f },
    { 0.27000001072883606f, 5.5f, -10.0f },
    { 0.4000000059604645f, 0.0f, 0.0f },
    { 0.2199999988079071f, 7.5f, -2.5f },
    { 0.3499999940395355f, 0.0f, 0.0f },
    { 0.23999999463558197f, -9.5f, 0.0f },
    { 0.1899999976158142f, 0.0f, 2.5f },
    { 0.25999999046325684f, 0.0f, -6.5f },
    { 0.30000001192092896f, 0.0f, 3.0f },
    { 0.3499999940395355f, -45.0f, -5.0f },
    { 0.4000000059604645f, 0.0f, 0.0f },
    { 0.4000000059604645f, 0.0f, 0.0f },
    { 0.4000000059604645f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f },
};
unk_D_84385384_func gAnimStateIdle = Anim_NullHandler;
unk_D_84385384 gMoveAnimData[] = {
    {
        0,
        {
            AnimChannel_TriggerMoveEffect,
            Anim_NullHandler,
            Anim_NullHandler,
            AnimChannel_SetupAndTrigger,
            AnimChannel_CheckModelBaseY,
            Pokemon_HandleGroundedAnim,
            Pokemon_HandleAirborneAnim,
        },
        167,
        5,
        255,
    },
    {
        1,
        {
            Pokemon_HandleSpecialMoveAnimation,
            ResetAnimChannelToDefault,
            Anim_ResetPlayer,
            PlayBattleMusicIfReady,
            Anim_NullHandler,
            Anim_NullHandler,
            Anim_NullHandler,
        },
        166,
        255,
        255,
    },
    {
        2,
        {
            Anim_NullHandler,
            AnimChannel_TriggerMoveEffect,
            Anim_NullHandler,
            Pokemon_HandleMoveHit,
            Anim_NullHandler,
            Anim_NullHandler,
            Anim_NullHandler,
        },
        255,
        2,
        255,
    },
    {
        3,
        {
            Pokemon_StartMoveAnimation,
            Anim_NullHandler,
            Anim_NullHandler,
            Pokemon_HandleMoveCompletion,
            AnimChannel_CheckAndAdvance,
            AnimChannel_HandleSpecialMoves,
            Anim_NullHandler,
        },
        255,
        255,
        255,
    },
    {
        4,
        {
            Pokemon_EnterBattleState,
            Anim_NullHandler,
            Anim_NullHandler,
            Pokemon_HandleSwitchIn,
            Pokemon_HandleSwitchOut,
            Anim_NullHandler,
            Anim_NullHandler,
        },
        255,
        255,
        255,
    },
    {
        5,
        {
            AnimHandler_AttackStart,
            AnimChannel_HandleBattleState,
            Anim_NullHandler,
            AnimHandler_AttackHit,
            AnimHandler_AttackEnd,
            AnimHandler_DamageStart,
            AnimHandler_DamageHit,
        },
        255,
        255,
        255,
    },
    {
        6,
        {
            AnimHandler_AttackStart,
            AnimChannel_HandleBattleState,
            Anim_NullHandler,
            AnimHandler_ItemUse,
            AnimHandler_StatusEffect,
            AnimHandler_FaintEnd,
            AnimHandler_FaintStart,
        },
        255,
        255,
        255,
    },
    {
        7,
        {
            AnimChannel_TriggerMoveEffect,
            Anim_NullHandler,
            Anim_NullHandler,
            AnimChannel_SetupAndTrigger,
            AnimHandler_Defeat,
            AnimHandler_DamageEnd,
            Pokemon_HandleAirborneAnim,
        },
        167,
        5,
        255,
    },
    {
        8,
        {
            Pokemon_TriggerAnimByLookup,
            Anim_NullHandler,
            Anim_NullHandler,
            Pokemon_HandleSpecialMoveEffect,
            Anim_NullHandler,
            Anim_NullHandler,
            Anim_NullHandler,
        },
        255,
        255,
        255,
    },
    {
        9,
        {
            Pokemon_SetSpecialAnimChannel,
            Pokemon_HandleSpecialCondition,
            Anim_NullHandler,
            Anim_NullHandler,
            Anim_NullHandler,
            Anim_NullHandler,
            Anim_NullHandler,
        },
        255,
        255,
        255,
    },
    {
        10,
        {
            Anim_NullHandler,
            AnimChannel_TriggerMoveEffect,
            Anim_NullHandler,
            Pokemon_HandleMoveHit,
            Pokemon_HandleFaint,
            Anim_NullHandler,
            Anim_NullHandler,
        },
        255,
        3,
        255,
    },
    {
        11,
        {
            UpdateAnimChannelForEntity,
            Anim_NullHandler,
            Anim_NullHandler,
            Pokemon_HandleSwitchIn,
            ApplyAnimStateEffect,
            TriggerAnimStateSound,
            Anim_NullHandler,
        },
        255,
        255,
        255,
    },
    {
        12,
        {
            Anim_ResetPlayer,
            Pokemon_TriggerAnimIfMatch,
            Anim_NullHandler,
            Anim_NullHandler,
            Anim_NullHandler,
            Anim_NullHandler,
            Anim_NullHandler,
        },
        255,
        255,
        255,
    },
    {
        13,
        {
            Pokemon_PlaySoundBasedOnFlags,
            Anim_NullHandler,
            Anim_NullHandler,
            Anim_NullHandler,
            Anim_NullHandler,
            Anim_NullHandler,
            Anim_NullHandler,
        },
        255,
        255,
        255,
    },
    {
        14,
        {
            UpdateAnimChannelForEntity,
            Anim_NullHandler,
            Anim_NullHandler,
            ProcessAnimStateMatch,
            Anim_NullHandler,
            Anim_NullHandler,
            Anim_NullHandler,
        },
        255,
        255,
        255,
    },
    {
        15,
        {
            Pokemon_StartBattleIntro,
            Anim_NullHandler,
            Anim_NullHandler,
            Anim_NullHandler,
            Anim_NullHandler,
            Anim_NullHandler,
            Anim_NullHandler,
        },
        255,
        255,
        255,
    },
    {
        16,
        {
            Pokemon_HandleSpecialMoveAnimation,
            ResetAnimChannelToDefault,
            Anim_ResetPlayer,
            PlayBattleMusicAndSound,
            Anim_NullHandler,
            Anim_NullHandler,
            Anim_NullHandler,
        },
        166,
        255,
        255,
    },
    {
        17,
        {
            Anim_NullHandler,
            Anim_NullHandler,
            Anim_NullHandler,
            AnimChannel_SetupAndTrigger,
            CheckAnimStateCompletion,
            Anim_NullHandler,
            Anim_NullHandler,
        },
        177,
        255,
        255,
    },
    {
        18,
        {
            Pokemon_HandleSpecialMoveAnimation,
            ResetAnimChannelToDefault,
            Anim_ResetPlayer,
            PlayBattleMusicAndSoundAlt,
            Anim_NullHandler,
            Anim_NullHandler,
            Anim_NullHandler,
        },
        166,
        255,
        255,
    },
    {
        19,
        {
            Pokemon_TriggerAnimIfUnlocked,
            Anim_NullHandler,
            Anim_NullHandler,
            Pokemon_HandleMoveEnd,
            Pokemon_HandleSpecialMoveEnd,
            Anim_NullHandler,
            Anim_NullHandler,
        },
        255,
        255,
        255,
    },
    {
        20,
        {
            Anim_NullHandler,
            AnimChannel_TriggerMoveEffect,
            Anim_NullHandler,
            Pokemon_HandleMoveHit,
            Pokemon_HandleFaintEffect,
            Anim_NullHandler,
            Anim_NullHandler,
        },
        255,
        1,
        255,
    },
    {
        21,
        {
            Pokemon_GenericActionTrigger,
            Anim_NullHandler,
            Anim_NullHandler,
            Pokemon_PlayMoveEffect,
            Anim_NullHandler,
            Anim_NullHandler,
            Anim_NullHandler,
        },
        255,
        255,
        255,
    },
};
