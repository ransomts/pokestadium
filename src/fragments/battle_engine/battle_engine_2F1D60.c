#include "battle_engine.h"
#include "src/17300.h"
#include "src/1C720.h"
#include "src/334D0.h"
#include "src/F420.h"

void BattleScene_TriggerOwnerModelAnimation(BattlePlayerEntity* arg0) {
    ModelAnim_SetFrame(&arg0->unk_728.unk_000, arg0->unk_728.unk_180);
    ModelAnim_SetAnimation(&arg0->unk_728.unk_000, arg0->unk_728.unk_17C);
    BattleScene_SetOwnerPoseFlag(arg0->unk_728.unk_168);
}

void BattleScene_ClearParticipantOwnerActiveFlag(BattlePlayerEntity* arg0) {
    arg0->unk_728.unk_170 = 0;
}

void BattleScene_SetParticipantOwnerActiveFlag(BattlePlayerEntity* arg0) {
    arg0->unk_728.unk_170 = 1;
}

void BattleScene_ClearBothOwnerActiveFlags(void) {
    sActivePokemon[0]->unk_728.unk_170 = 0;
    sActivePokemon[1]->unk_728.unk_170 = 0;
}

void BattleScene_SetBothOwnerActiveFlags(void) {
    sActivePokemon[0]->unk_728.unk_170 = 1;
    sActivePokemon[1]->unk_728.unk_170 = 1;
}

void BattleScene_SetOwnerPoseFlag(unk_D_84390010_728_0168* arg0) {
    arg0->posX.unk_01 |= 0x10;
}

void BattleScene_LoadOwnerCameraFramingConstants(BattlePlayerEntity* arg0) {
    s32 var_v0;

    if (arg0 == sActivePokemon[0]) {
        var_v0 = 0;
    } else {
        var_v0 = 1;
    }

    arg0->unk_728.unk_168->unk_20 = gEntityInitParams[var_v0].rotation;
    arg0->unk_728.unk_168->unk_1C = gEntityInitParams[var_v0].posX;
    arg0->unk_728.unk_168->unk_1E = gEntityInitParams[var_v0].posY;

    arg0->unk_728.unk_178 = gEntityInitParams[var_v0].unk_14;

    arg0->unk_728.unk_168->unk_34 = gEntityInitParams[var_v0].unk_0C;
    arg0->unk_728.unk_168->unk_38 = gEntityInitParams[var_v0].unk_10;
    arg0->unk_728.unk_168->unk_2C = gEntityInitParams[var_v0].unk_08;
}

void BattleScene_SetupOwnerCameraFraming(BattlePlayerEntity* arg0, BattlePlayerEntity* arg1) {
    if (gBattleScene.posX->unk_1C == 1) {
        BattleScene_SetBothOwnerActiveFlags();
    } else {
        BattleScene_ClearBothOwnerActiveFlags();
    }
    BattleScene_LoadOwnerCameraFramingConstants(arg0);
    BattleScene_LoadOwnerCameraFramingConstants(arg1);
}

void func_84307630(void) {
}

void BattleScene_ApplyOwnerCameraFraming(BattlePlayerEntity* arg0) {
    s32 temp_v0;
    unk_D_84390010_728_0168* sp30;
    f32 tmp;
    f32 tmp2;

    sp30 = arg0->unk_728.unk_168;
    temp_v0 = BattleScene_GetParticipantSideIndex(arg0);

    arg0->unk_728.unk_184 = gAnimDataSetB[temp_v0]->unk_0C;
    if (gAnimDataSetB[temp_v0]->unk_10 == 0xFF) {
        arg0->unk_728.unk_186 = gAnimDataSetB[temp_v0]->unk_0E * arg0->unk_728.unk_178;
        tmp = gAnimDataSetB[temp_v0]->posX.z * arg0->unk_728.unk_178;
    } else {
        arg0->unk_728.unk_186 = gAnimDataSetB[temp_v0]->unk_0E;
        tmp = gAnimDataSetB[temp_v0]->posX.z;
    }

    arg0->unk_728.unk_190 = tmp;
    arg0->unk_728.unk_188 = gAnimDataSetB[temp_v0]->posX.x;
    arg0->unk_728.unk_180 = gAnimDataSetB[temp_v0]->unk_12;
    tmp2 = gAnimDataSetB[temp_v0]->posX.y;
    arg0->unk_728.unk_194 = tmp2;

    BattleScene_SetCameraAtAndEyeFromAngles(sp30, arg0->unk_728.unk_000.unk_024.x + arg0->unk_728.unk_190, arg0->unk_728.unk_000.unk_024.y + tmp2,
                  arg0->unk_728.unk_000.unk_024.z, arg0->unk_728.unk_188, arg0->unk_728.unk_184, arg0->unk_728.unk_186);
}

void BattleScene_TickOwnerCameraFraming(BattlePlayerEntity* arg0) {
    BattleScene_ApplyOwnerCameraFraming(arg0);
}

void BattleScene_InitializeOwnerCameraFraming(CameraStruct* arg0, BattlePlayerEntity* arg1, CameraStruct* arg2, BattlePlayerEntity* arg3) {
    arg1->unk_728.unk_168 = arg0;
    arg3->unk_728.unk_168 = arg2;
    BattleScene_SetupOwnerCameraFraming(arg1, arg3);
    BattleScene_TickOwnerCameraFraming(arg1);
    BattleScene_TickOwnerCameraFraming(arg3);
}

void BattleScene_TickOwnerSlideIn(BattlePlayerEntity* arg0, s32 arg1) {
    s16 var_a0;
    unk_D_84390010_728_0168* temp_v0;

    arg0->unk_728.unk_168->posX.unk_01 |= 1;
    arg0->unk_728.unk_000.unk_000.unk_01 |= 1;

    if (arg0->unk_728.unk_178 == 1) {
        if ((arg0->unk_728.unk_168->unk_1C == -0x48) && !(arg0->animationState.unk_34 & 0x800)) {
            BattleScene_TriggerOwnerModelAnimation(arg0);
        }

        if ((ModelRenderer_IsReady(0) != 0) && (arg0->unk_728.unk_18C == 0)) {
            arg0->unk_728.unk_18C = 2;
            ModelRenderer_OnSlotReady(0);
        }
        arg0->unk_728.unk_168->unk_1C = Math_StepToS32(arg0->unk_728.unk_168->unk_1C, 0x17, arg1, arg1);
    } else {
        if ((arg0->unk_728.unk_168->unk_1C == 0x15F) && !(arg0->animationState.unk_34 & 0x800)) {
            BattleScene_TriggerOwnerModelAnimation(arg0);
        }

        arg0->unk_728.unk_168->unk_1C = Math_StepToS32(arg0->unk_728.unk_168->unk_1C, 0x103, arg1, arg1);

        if ((ModelRenderer_IsReady(1) != 0) && (arg0->unk_728.unk_18C == 0)) {
            arg0->unk_728.unk_18C = 2;
            ModelRenderer_OnSlotReady(1);
        }
    }
}

void BattleScene_TickOwnerSlideOut(BattlePlayerEntity* arg0, s32 arg1) {
    if (arg0->unk_728.unk_178 == 1) {
        arg0->unk_728.unk_18C = 0;
        arg0->unk_728.unk_168->unk_1C = Math_StepToS32(arg0->unk_728.unk_168->unk_1C, -0x48, arg1, arg1);
        if (arg0->unk_728.unk_168->unk_1C == -0x48) {
            arg0->unk_728.unk_168->posX.unk_01 &= ~1;
            arg0->unk_728.unk_000.unk_000.unk_01 &= ~1;
        }
    } else {
        arg0->unk_728.unk_18C = 0;
        arg0->unk_728.unk_168->unk_1C = Math_StepToS32(arg0->unk_728.unk_168->unk_1C, 0x15F, arg1, arg1);
        if (arg0->unk_728.unk_168->unk_1C == 0x15F) {
            arg0->unk_728.unk_168->posX.unk_01 &= ~1;
            arg0->unk_728.unk_000.unk_000.unk_01 &= ~1;
        }
    }
}

void BattleScene_TickOwnerSlideAnimation(BattlePlayerEntity* arg0) {
    switch (arg0->unk_728.unk_170) {
        case 0:
            BattleScene_TickOwnerSlideOut(arg0, 9);
            break;

        case 1:
            BattleScene_TickOwnerSlideIn(arg0, 9);
            break;
    }
}

void BattleScene_TickBothOwnerSlideAnimations(BattlePlayerEntity* arg0, BattlePlayerEntity* arg1) {
    if (gSessionContext.unk_0000 != 0x10) {
        BattleScene_TickOwnerSlideAnimation(arg0);
        BattleScene_TickOwnerSlideAnimation(arg1);
    }
}

s32 BattleScene_DispatchOwnerCameraLifecycle(s32 arg0, CameraStruct* arg1, CameraStruct* arg2) {
    switch (arg0) {
        case 0:
            func_84307630();
            break;

        case 1:
        case 2:
            BattleScene_TickBothOwnerSlideAnimations(sActivePokemon[0], sActivePokemon[1]);
            break;

        case 3:
            BattleScene_InitializeOwnerCameraFraming(arg1, sActivePokemon[0], arg2, sActivePokemon[1]);
            break;
    }
    return 0;
}
