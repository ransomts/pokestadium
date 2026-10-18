#include "fragment62.h"
#include "src/11BA0.h"
#include "src/17300.h"
#include "src/2E110.h"
#include "src/373A0.h"
#include "src/F420.h"
#include "src/memory.h"
#include "src/util.h"

unk_D_84390240 gBattleState;
static s32 pad_D_84390280;
static s32 gCurrentEntityIndex;
s32 D_84390288;
static s32 pad_D_84390290[4];

void InitializeCameraForCurrentEntity(unk_D_86002F34_00C* arg0) {
    f32 sp3C;

    func_8431AFD0(arg0, 20.0f, 12800.0f);
    func_843081F0(D_84390010[gCurrentEntityIndex], &gBattleState.unk_00->unk_D0);
    sp3C = ClampScaledDistance(D_84390010[gCurrentEntityIndex], 3.5f, 300.0f);
    func_8431BAB4(D_84390010[gCurrentEntityIndex], arg0, gBattleState.unk_00->unk_D0, 0, func_84308190(D_84390010[gCurrentEntityIndex]),
                  0.0f, 0.0f);
    func_8431BBDC(arg0, 0, func_84308190(D_84390010[gCurrentEntityIndex]), sp3C, 0.0f);

    if (D_84390010[0]) {}
    gBattleState.unk_00->unk_20 += 1;
    if (gCurrentEntityIndex) {}
}

void InitializeCameraForPlayerEntity(unk_D_86002F34_00C* arg0) {
    f32 sp3C;

    func_8431AFD0(arg0, 20.0f, 12800.0f);
    func_843081F0(D_84390010[0], &gBattleState.unk_00->unk_D0);
    sp3C = ClampScaledDistance(D_84390010[0], 3.5f, 300.0f);
    func_8431BAB4(D_84390010[0], arg0, gBattleState.unk_00->unk_D0, 0, func_84308190(*D_84390010), 0.0f, 0.0f);
    func_8431BBDC(arg0, 0, func_84308190(*D_84390010), sp3C, 0.0f);

    if (D_84390010[0]) {}
    gBattleState.unk_00->unk_20 += 1;
}

void func_843296B8(unk_D_86002F34_00C* arg0, UNUSED unk_D_84390010* arg1, UNUSED unk_D_84390010* arg2) {
    gBattleState.unk_00->unk_40 = 0;
    gBattleState.unk_00->unk_60 = 30.0f;
    gBattleState.unk_00->unk_6C = 10.0f;

    switch (gBattleState.unk_00->unk_1C) {
        case 0:
            InitializeCameraForCurrentEntity(arg0);
            break;

        case 1:
            Camera_UpdateStateMachine(arg0);
            break;

        case 2:
            func_84321184(arg0);
            Battle_SetPhase(arg0, 1);
            break;

        case 3:
            InitializeCameraForPlayerEntity(arg0);
            break;

        case 4:
            Intro_SetupCamera(arg0);
            break;
    }
    gBattleState.unk_00->unk_DC = arg0;
}

void func_843297AC(void) {
    gBattleState.unk_00 = main_pool_alloc(sizeof(unk_D_84390240_000), 0);
    bzero(gBattleState.unk_00, sizeof(unk_D_84390240_000));
}

void func_843297E8(UNUSED unk_D_86002F34_00C* arg0) {
}

void func_843297F0(UNUSED unk_D_86002F34_00C* arg0) {
}

void func_843297F8(unk_D_86002F34_00C* arg0) {
    if (Math_2DDistance(arg0->unk_60.at.x, arg0->unk_60.at.z, arg0->unk_60.eye.x, arg0->unk_60.eye.z) < 0.0001f) {
        arg0->unk_60.at.z += 0.001f;
    }
}

void Battle_StartSequence(unk_D_86002F34_00C* arg0) {
    switch (gBattleState.unk_00->unk_30) {
        case 0:
            gBattleState.unk_00->unk_18 = 0;
            break;

        case 1:
            if (gBattleState.unk_00->unk_44 == 2) {
                ClearAllPokemonActiveFlags();
            }
            gBattleState.unk_00->unk_30++;
            break;

        case 2:
            if (D_84390010[0]->unk_728.unk_168->unk_1C == -0x48) {
                gBattleState.unk_00->unk_30++;
            }
            break;

        case 3:
            Texture_SetDefault(arg0, 0x12C, 0xA, 2, Util_ConvertAddrToVirtAddr((u32)D_1000000));
            Background_SetColor(arg0, 5, 0xA, 0, 0, 0);
            gBattleState.unk_00->unk_18 = 0;
            gBattleState.unk_00->unk_30 += 1;

        case 4:
            if (arg0->unk_CC.unk_0A == 0xA) {
                Battle_ResetSubstate();
                func_843062F0();
                func_843066E0(D_84390010[0]);
                func_843066E0(D_84390010[1]);
                gBattleState.unk_00->unk_30 += 1;
                gBattleState.unk_00->unk_18 = 1;
            }
            break;

        case 5:
            if ((func_8431FAB4() == 0) && (func_8431F998(D_84390010[gBattleState.unk_00->unk_2A]) == 0)) {
                if (gBattleState.unk_00->unk_44 == 1) {
                    func_8432E9D8(2);
                    func_8430CC84();
                }
                func_843058A8(D_84390010[0]);
                func_843058A8(D_84390010[1]);
                gBattleState.unk_00->unk_18 = 2;
                Texture_SetDefault(arg0, 0xA, 0x12C, 2, Util_ConvertAddrToVirtAddr((u32)D_1000000));
                Background_SetColor(arg0, 4, 0xA, 0, 0, 0);
                arg0->unk_24.fovy = 30.0f;
                gBattleState.unk_00->unk_60 = 30.0f;
                gBattleState.unk_00->unk_30 += 1;
            }
            break;

        case 6:
            Battle_ResetSubstate();
            arg0->unk_24.fovy = 30.0f;
            gBattleState.unk_00->unk_60 = 30.0f;
            gBattleState.unk_00->unk_18 = 0;
            if (arg0->unk_CC.unk_0A == 0xA) {
                gBattleState.unk_00->unk_30 = 0;
                if (gBattleState.unk_00->unk_44 == 1) {
                    SetAllPokemonActiveFlags();
                }
            }
            break;
    }
}

void Battle_TransitionSequence(unk_D_86002F34_00C* arg0) {
    switch (gBattleState.unk_00->unk_30) {
        case 0:
            gBattleState.unk_00->unk_18 = 0;
            break;

        case 1:
            if (gBattleState.unk_00->unk_44 == 2) {
                ClearAllPokemonActiveFlags();
            }
            gBattleState.unk_00->unk_30++;
            break;

        case 2:
            if (D_84390010[0]->unk_728.unk_168->unk_1C == -0x48) {
                gBattleState.unk_00->unk_30++;
            }
            break;

        case 3:
            func_8436EEF0(3, 0x1E);
            func_8436EF54();
            gBattleState.unk_00->unk_18 = 0;
            gBattleState.unk_00->unk_30 += 1;

        case 4:
            func_8436EF54();
            if (func_8436EF48() == 1) {
                Battle_ResetSubstate();
                func_843062F0();
                func_843066E0(D_84390010[0]);
                func_843066E0(D_84390010[1]);
                gBattleState.unk_00->unk_30 += 1;
                gBattleState.unk_00->unk_18 = 1;
            }
            break;

        case 5:
            gBattleState.unk_00->unk_18 = 1;
            gBattleState.unk_00->unk_30 += 1;
            break;

        case 6:
            gBattleState.unk_00->unk_18 = 1;
            gBattleState.unk_00->unk_30 += 1;
            break;

        case 7:
            gBattleState.unk_00->unk_18 = 1;
            gBattleState.unk_00->unk_30 += 1;
            break;

        case 8:
            if ((func_8431FAB4() == 0) && (func_8431F998(D_84390010[gBattleState.unk_00->unk_2A]) == 0)) {
                if (gBattleState.unk_00->unk_44 == 1) {
                    func_8432E9D8(2);
                    func_8430CC84();
                }
                func_843058A8(D_84390010[0]);
                func_843058A8(D_84390010[1]);
                gBattleState.unk_00->unk_18 = 2;
                func_8436EEF0(2, 0x1E);
                func_8436EF54();
                arg0->unk_24.fovy = 30.0f;
                gBattleState.unk_00->unk_60 = 30.0f;
                gBattleState.unk_00->unk_30 += 1;
            }
            break;

        case 9:
            Battle_ResetSubstate();
            arg0->unk_24.fovy = 30.0f;
            gBattleState.unk_00->unk_60 = 30.0f;
            gBattleState.unk_00->unk_18 = 0;
            func_8436EF54();
            if (func_8436EF48() == 0) {
                gBattleState.unk_00->unk_30 = 0;
                if (gBattleState.unk_00->unk_44 == 1) {
                    SetAllPokemonActiveFlags();
                }
            }
            break;
    }
}

void Battle_RunSequence(unk_D_86002F34_00C* arg0) {
    if (gBattleState.unk_00->unk_2E == 0) {
        Battle_StartSequence(arg0);
    } else {
        Battle_TransitionSequence(arg0);
    }
}

u16 IsPointInTriangle(unk_D_84390010* arg0, unk_D_86002F34_00C* arg1, unk_D_84390010* a2, s16 arg3, f32 arg4) {
    UNUSED s32 pad[6];
    f32 sp6C;
    f32 sp68;
    f32 sp64;
    f32 sp60;
    f32 sp5C;
    UNUSED s32 pad2;
    f32 sp54;
    f32 sp50;
    UNUSED s32 pad3;
    f32 sp48;
    s16 sp46;
    s16 sp44;
    f32 sp40;
    unk_D_84390010* arg2;
    f32 sp38;
    s32 sp34 = 0;

    Math_CalcDistAndAngles(&arg1->unk_60.at, &arg1->unk_60.eye, &sp48, &sp46, &sp44);
    sp40 = (COSS((sp44 - 0x8000)) * 50.0f) + arg1->unk_60.eye.z;
    sp38 = (SINS((sp44 - 0x8000)) * 30.0f) + arg1->unk_60.eye.x;
    sp54 = (COSS(((sp44 - arg3) + 0x8000)) * arg4) + sp40;
    sp60 = (SINS(((sp44 - arg3) + 0x8000)) * arg4) + sp38;
    sp50 = (COSS((sp44 + arg3 + 0x8000)) * arg4) + sp40;
    sp5C = (SINS((sp44 + arg3 + 0x8000)) * arg4) + sp38;

    arg2 = a2;

    sp6C = ((sp54 - arg2->unk_000.unk_024.z) * (sp5C - arg2->unk_000.unk_024.x)) -
           ((sp50 - arg2->unk_000.unk_024.z) * (sp60 - arg2->unk_000.unk_024.x));
    sp68 = ((sp50 - arg2->unk_000.unk_024.z) * (sp38 - arg2->unk_000.unk_024.x)) -
           ((sp40 - arg2->unk_000.unk_024.z) * (sp5C - arg2->unk_000.unk_024.x));
    sp64 = ((sp40 - arg2->unk_000.unk_024.z) * (sp60 - arg2->unk_000.unk_024.x)) -
           ((sp54 - arg2->unk_000.unk_024.z) * (sp38 - arg2->unk_000.unk_024.x));

    if (((sp6C >= 0.0f) && (sp68 >= 0.0f) && (sp64 >= 0.0f)) || ((sp6C <= 0.0f) && (sp68 <= 0.0f) && (sp64 <= 0.0f))) {
        sp34 = 1;
    }
    return sp34;
}

u16 IsPointInTriangleAndWithinRange(unk_D_84390010* arg0, unk_D_86002F34_00C* arg1, unk_D_84390010* a2, s16 arg3, f32 arg4) {
    UNUSED s32 pad[6];
    f32 sp94;
    f32 sp90;
    f32 sp8C;
    f32 sp88;
    f32 sp84;
    UNUSED s32 pad2;
    f32 sp7C;
    f32 sp78;
    unk_D_84390010* arg2;
    f32 sp70;
    s16 sp6E;
    s16 sp6C;
    Vec3f sp60;
    s32 sp5C;

    sp5C = 0;
    Math_CalcDistAndAngles(&arg1->unk_60.at, &arg1->unk_60.eye, &sp70, &sp6E, &sp6C);
    sp60.z = (COSS((sp6C - 0x8000)) * 30.0f) + arg1->unk_60.eye.z;
    sp60.x = (SINS((sp6C - 0x8000)) * 30.0f) + arg1->unk_60.eye.x;
    sp7C = (COSS(((sp6C - arg3) + 0x8000)) * arg4) + sp60.z;
    sp88 = (SINS(((sp6C - arg3) + 0x8000)) * arg4) + sp60.x;
    sp78 = (COSS((sp6C + arg3 + 0x8000)) * arg4) + sp60.z;
    sp84 = (SINS((sp6C + arg3 + 0x8000)) * arg4) + sp60.x;

    arg2 = a2;

    sp94 = ((sp7C - arg2->unk_000.unk_024.z) * (sp84 - arg2->unk_000.unk_024.x)) -
           ((sp78 - arg2->unk_000.unk_024.z) * (sp88 - arg2->unk_000.unk_024.x));
    sp90 = ((sp78 - arg2->unk_000.unk_024.z) * (sp60.x - arg2->unk_000.unk_024.x)) -
           ((sp60.z - arg2->unk_000.unk_024.z) * (sp84 - arg2->unk_000.unk_024.x));
    sp8C = ((sp60.z - arg2->unk_000.unk_024.z) * (sp88 - arg2->unk_000.unk_024.x)) -
           ((sp7C - arg2->unk_000.unk_024.z) * (sp60.x - arg2->unk_000.unk_024.x));

    if (((sp94 >= 0.0f) && (sp90 >= 0.0f) && (sp8C >= 0.0f)) || ((sp94 <= 0.0f) && (sp90 <= 0.0f) && (sp8C <= 0.0f))) {
        sp5C = 1;
    }

    sp60.x = a2->unk_000.unk_024.x;
    sp60.y = a2->unk_000.unk_024.y;
    sp60.z = a2->unk_000.unk_024.z;

    if ((func_84308598(arg0) * 2.5f) >= Vector_Distance(arg1->unk_60.eye, sp60)) {
        sp5C = 0;
    }
    return sp5C;
}

void UpdateEntityVisibilityFromCamera(unk_D_86002F34_00C* arg0) {
    if (IsPointInTriangle(D_84390010[0], arg0, D_84390010[0], 0x2AA8, 2500.0f) != 0) {
        D_84390010[0]->unk_000.unk_000.unk_01 |= 1;
    } else {
        D_84390010[0]->unk_000.unk_000.unk_01 &= ~1;
    }

    if (IsPointInTriangle(D_84390010[1], arg0, D_84390010[1], 0x2AA8, 2500.0f) != 0) {
        D_84390010[1]->unk_000.unk_000.unk_01 |= 1;
    } else {
        D_84390010[1]->unk_000.unk_000.unk_01 &= ~1;
    }
}

void UpdateOppositeEntityVisibility(unk_D_86002F34_00C* arg0) {
    unk_D_84390010* sp24 = D_84390010[!gBattleState.unk_00->unk_2C];

    if (IsPointInTriangleAndWithinRange(sp24, arg0, sp24, 0x2AA8, 2500.0f) != 0) {
        sp24->unk_000.unk_000.unk_01 |= 1;
    } else {
        sp24->unk_000.unk_000.unk_01 &= 0xFFFE;
    }
}

void func_8432A414(void) {
}

void SetAllEntitiesActiveFlag(void) {
    D_84390010[0]->unk_000.unk_000.unk_01 |= 1;
    D_84390010[1]->unk_000.unk_000.unk_01 |= 1;
}

void DeactivateOppositeEntity(void) {
    func_843087F8(D_84390010[!gBattleState.unk_00->unk_2C]);
    D_84390010[!gBattleState.unk_00->unk_2C]->unk_000.unk_000.unk_01 &= ~1;
}

void DeactivateCurrentEntity(void) {
    D_84390010[gBattleState.unk_00->unk_2C]->unk_000.unk_000.unk_01 &= ~1;
    func_843087F8(D_84390010[gBattleState.unk_00->unk_2C]);
}

void ClearEntityFlagIfInState(void) {
    unk_D_84390010* ptr1 = D_84390010[0];
    unk_D_84390010* ptr2 = D_84390010[1];

    if ((ptr1->unk_654.unk_2D == 0x10) || ((ptr1 = D_84390010[0])->unk_654.unk_2D == 0x13)) {
        ptr1->unk_000.unk_000.unk_01 &= ~1;
    }

    if ((ptr2->unk_654.unk_2D == 0x10) || (ptr2->unk_654.unk_2D == 0x13)) {
        ptr2->unk_000.unk_000.unk_01 &= ~1;
    }
}

void ProcessBattleState(unk_D_86002F34_00C* arg0) {
    UNUSED s32 pad;
    unk_D_84390010_654* sp40 = &gCurrentPlayer->unk_654;
    s32 temp_lo;
    unk_D_84390010_654* sp38 = &gOpponentPlayer->unk_654;
    f32 sp34;
    s16 sp32;
    s16 sp30;

    switch (gBattleState.unk_00->unk_1C) {
        case 0:
        case 3:
            break;

        case 1:
            SetAllEntitiesActiveFlag();

            switch (gBattleState.unk_00->unk_20) {
                case 12:
                case 13:
                case 14:
                case 15:
                case 21:
                    SetAllEntitiesActiveFlag();
                    break;

                case 16:
                case 17:
                case 18:
                case 19:
                    D_84390010[gBattleState.unk_00->unk_2C]->unk_000.unk_000.unk_01 &= ~1;
                    break;

                default:
                    UpdateOppositeEntityVisibility(arg0);
                    break;
            }
            break;

        case 2:
            SetAllEntitiesActiveFlag();

            switch (gBattleState.unk_00->unk_38) {
                case 2:
                case 3:
                    switch (gBattleState.unk_00->unk_20) {
                        case 0:
                            if ((sp40->unk_2D == 0xF) && (gBattleState.unk_00->unk_34 == 1)) {
                                DeactivateCurrentEntity();
                            } else {
                                Matrix_Decompose(&gBattleState.unk_00->unk_B8, &gBattleState.unk_00->unk_C4, &sp34, &sp32,
                                              &sp30);
                                temp_lo = sp30 / 182;
                                if (((temp_lo == 0x5A) || (temp_lo == -0x5A)) && (gBattleState.unk_00->unk_34 == 1)) {
                                    DeactivateOppositeEntity();
                                } else {
                                    UpdateOppositeEntityVisibility(arg0);
                                }
                            }
                            break;

                        case 1:
                            gBattleState.unk_00->unk_08 = 0;
                            if (!(sp40->unk_34 & 0x4400)) {
                                DeactivateOppositeEntity();
                            }
                            break;

                        case 2:
                            if ((gBattleState.unk_00->unk_3C == 0) && (gBattleState.unk_00->unk_24 >= 0) &&
                                (gBattleState.unk_00->unk_24 < 2) && (sp38->unk_34 & 0x800)) {
                                DeactivateOppositeEntity();
                            } else if (((gBattleState.unk_00->unk_3C == 0) || (gBattleState.unk_00->unk_3C == 1)) &&
                                       (gBattleState.unk_00->unk_48 == 0) && (gBattleState.unk_00->unk_1A != 1)) {
                                func_843087F8(gCurrentPlayer);
                                gCurrentPlayer->unk_000.unk_01D = 0;
                            } else {
                                if (sp40->unk_34 & 0x4000) {
                                    if ((gCurrentPlayer->unk_000.unk_01A != 0x32) &&
                                        (gCurrentPlayer->unk_000.unk_01A != 0x33)) {
                                        gCurrentPlayer->unk_000.unk_01D = 0;
                                    } else {
                                        gCurrentPlayer->unk_000.unk_01D = 0xFF;
                                    }
                                } else {
                                    gCurrentPlayer->unk_000.unk_01D = 0xFF;
                                }
                                DeactivateCurrentEntity();
                            }
                            gBattleState.unk_00->unk_08 = 1;
                            break;
                    }
                    break;

                case 36:
                    if (gBattleState.unk_00->unk_08 == 1) {
                        DeactivateOppositeEntity();
                    } else if (gBattleState.unk_00->unk_08 == 2) {
                        D_84390010[!gBattleState.unk_00->unk_2C]->unk_000.unk_000.unk_01 &= ~1;
                    } else if (gBattleState.unk_00->unk_08 == 3) {
                        D_84390010[gBattleState.unk_00->unk_2C]->unk_000.unk_000.unk_01 &= ~1;
                    } else if (gBattleState.unk_00->unk_08 == 4) {
                        D_84390010[gBattleState.unk_00->unk_2C]->unk_000.unk_000.unk_01 &= ~1;
                    }
                    break;

                case 4:
                    if (gBattleState.unk_00->unk_08 == 1) {
                        DeactivateCurrentEntity();
                    } else if (gBattleState.unk_00->unk_08 == 2) {
                        D_84390010[!gBattleState.unk_00->unk_2C]->unk_000.unk_000.unk_01 &= ~1;
                    } else if (gBattleState.unk_00->unk_08 == 3) {
                        D_84390010[!gBattleState.unk_00->unk_2C]->unk_000.unk_000.unk_01 &= ~1;
                    } else if (gBattleState.unk_00->unk_08 == 4) {
                        D_84390010[!gBattleState.unk_00->unk_2C]->unk_000.unk_000.unk_01 &= ~1;
                    }
                    break;

                case 11:
                    gBattleState.unk_00->unk_08 = 4;
                    if (gBattleState.unk_00->unk_34 == 1) {
                        DeactivateOppositeEntity();
                    } else if (gBattleState.unk_00->unk_20 == 0) {
                        UpdateEntityVisibilityFromCamera(arg0);
                    } else {
                        DeactivateOppositeEntity();
                    }
                    break;

                case 18:
                    gBattleState.unk_00->unk_08 = 3;
                    switch (gBattleState.unk_00->unk_20) {
                        case 0:
                            UpdateEntityVisibilityFromCamera(arg0);
                            break;

                        default:
                            DeactivateOppositeEntity();
                            break;
                    }
                    break;

                case 12:
                    gBattleState.unk_00->unk_08 = 0;
                    switch (gBattleState.unk_00->unk_20) {
                        case 2:
                        case 3:
                        case 4:
                            SetAllEntitiesActiveFlag();
                            break;

                        default:
                            DeactivateOppositeEntity();
                            break;
                    }
                    break;

                case 37:
                    gBattleState.unk_00->unk_08 = 0;
                    DeactivateOppositeEntity();
                    break;

                case 7:
                case 13:
                case 14:
                case 15:
                case 16:
                case 17:
                case 20:
                case 21:
                case 25:
                case 27:
                case 28:
                case 29:
                case 31:
                case 38:
                    gBattleState.unk_00->unk_08 = 3;
                    DeactivateOppositeEntity();
                    break;

                case 9:
                case 35:
                    gBattleState.unk_00->unk_08 = 3;
                    DeactivateOppositeEntity();
                    break;

                case 6:
                    gBattleState.unk_00->unk_08 = 0;
                    DeactivateOppositeEntity();
                    break;

                case 8:
                case 10:
                    gBattleState.unk_00->unk_08 = 0;
                    DeactivateCurrentEntity();
                    break;

                case 30:
                    gBattleState.unk_00->unk_08 = 0;

                    switch (gBattleState.unk_00->unk_20) {
                        case 0:
                        case 1:
                        case 2:
                            DeactivateOppositeEntity();
                            break;

                        default:
                            DeactivateCurrentEntity();
                            break;
                    }
                    break;

                case 5:
                case 34:
                    gBattleState.unk_00->unk_08 = 0;
                    switch (gBattleState.unk_00->unk_20) {
                        case 0:
                        case 1:
                            D_84390010[gBattleState.unk_00->unk_2C]->unk_000.unk_000.unk_01 &= ~1;
                            break;
                    }
                    break;
            }
            break;
    }
    ClearEntityFlagIfInState();
}

void func_8432ABBC(unk_D_86002F34_00C* arg0) {
    switch (gBattleState.unk_00->unk_1C) {
        case 1:
            SetAllEntitiesActiveFlag();

            switch (gBattleState.unk_00->unk_20) {
                case 12:
                case 13:
                case 14:
                case 15:
                case 21:
                    SetAllEntitiesActiveFlag();
                    break;

                case 16:
                case 17:
                case 18:
                case 19:
                    D_84390010[gBattleState.unk_00->unk_2C]->unk_000.unk_000.unk_01 &= ~1;
                    break;

                default:
                    UpdateOppositeEntityVisibility(arg0);
                    break;
            }
            break;

        case 2:
            switch (gBattleState.unk_00->unk_38) {
                case 30:
                    switch (gBattleState.unk_00->unk_20) {
                        case 0:
                        case 1:
                        case 2:
                        case 5:
                            D_84390010[!gBattleState.unk_00->unk_2C]->unk_000.unk_000.unk_01 &= ~1;
                            D_84390010[gBattleState.unk_00->unk_2C]->unk_000.unk_000.unk_01 |= 1;
                            break;

                        default:
                            D_84390010[gBattleState.unk_00->unk_2C]->unk_000.unk_000.unk_01 &= ~1;
                            D_84390010[!gBattleState.unk_00->unk_2C]->unk_000.unk_000.unk_01 |= 1;
                    }
                    break;

                case 5:
                case 34:
                    switch (gBattleState.unk_00->unk_20) {
                        case 0:
                        case 1:
                            D_84390010[gBattleState.unk_00->unk_2C]->unk_000.unk_000.unk_01 &= ~1;
                            D_84390010[!gBattleState.unk_00->unk_2C]->unk_000.unk_000.unk_01 |= 1;
                            break;
                    }
                    break;
            }
            break;
    }
    ClearEntityFlagIfInState();
}

void Battle_Update(unk_D_86002F34_00C* arg0) {
    Battle_RunSequence(arg0);
    func_8431B004();
    ProcessBattleState(arg0);

    switch (gBattleState.unk_00->unk_1C) {
        case 0:
            func_843297E8(arg0);
            break;

        case 1:
            Camera_MainUpdate(arg0);
            break;

        case 2:
            func_8430CCC8();
            func_84328734(arg0);
            break;

        case 3:
            func_843297F0(arg0);
            break;

        case 4:
            Intro_StateMachine(arg0);
            break;

        default:
            gBattleState.unk_00->unk_40 = 3;
            break;
    }

    func_8432ABBC(arg0);
    Anim_ProcessQueue();
    func_84306914(gPrimaryPokemonEntity);
    func_84306914(D_8439001C);
    func_8431B174(arg0);
    func_8431B830(arg0);
    func_8431BD10(arg0);
    func_843297F8(arg0);
}

s32 func_8432AEE4(s32 arg0, unk_D_86002F34_00C* arg1) {
    switch (arg0) {
        case 0:
            func_843297AC();
            break;

        case 1:
        case 2:
            Battle_Update(arg1);
            break;

        case 3:
            func_843296B8(arg1, D_84390010[0], D_84390010[1]);
            break;
    }
    return gBattleState.unk_00->unk_40;
}
