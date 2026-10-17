#include "E890.h"
#include "PR/leo.h"
#include "src/dma.h"

unk_D_800AA680 gBootIDData;
static unk_D_800AA690 gBootState;
static OSMesgQueue gBootMsgQueue;
static OSMesg gBootMsgBuffer;

s32 Boot_ValidateAndCopy(void) {
    static char D_8006F000[] = "P2J";
    static char D_8006F004[] = "01";

    if (osMemSize < 0x800000) {
        return 2;
    }

    if (bcmp(D_800818E0.company, D_8006F004, sizeof(D_800818E0.company)) != 0) {
        return 1;
    }

    if (bcmp(&D_800818E0.gameName[1], D_8006F000, 3) != 0) {
        return 1;
    }

    if (D_800818E0.gameName[0] < 'E') {
        return 1;
    }

    if (D_800818E0.gameName[0] > 'Z') {
        return 1;
    }

    if (D_800818E0.diskNumber != 1) {
        return 1;
    }

    _bcopy(&D_800818E0, &leoBootID, sizeof(LEODiskID));
    return 0;
}

s32 BootID_StoreIfValid(unk_D_800AA680* arg0) {
    s32 var_v1 = 0;

    if (arg0->unk_00 == 'POKE') {
        var_v1 = 1;
        gBootIDData = *arg0;
    }

    return var_v1;
}

s32 func_8000DDB0(void) {
    func_80001124(&gBootMsgQueue, 0);
    gBootState.unk_00 = 3;
    return 0;
}

s32 func_8000DDE4(void) {
    func_8000123C(&gBootMsgQueue, 0);
    gBootState.unk_00 = 5;
    return 0;
}

s32 Boot_DMAReadHeader(unk_D_800AA680* arg0) {
    func_80001098(0, arg0, 0x230, 1, &gBootMsgQueue, 1);
    gBootState.unk_04 = 0;
    gBootState.unk_02 = 0;
    gBootState.unk_00 = 7;
    return 0;
}

s32 Boot_DMAReadData(void) {
    func_80001098(0, gBootIDData.unk_08, gBootIDData.unk_04, gBootIDData.unk_06, &gBootMsgQueue, 1);
    gBootState.unk_04 = 0;
    gBootState.unk_02 = 0;
    gBootState.unk_00 = 9;
    return 0;
}

s32 Boot_ProcessMessage(void) {
    s32 sp1C;

    if (osRecvMesg(&gBootMsgQueue, &sp1C, 0) != -1) {
        switch (sp1C) {
            case 0:
                switch (Boot_ValidateAndCopy()) {
                    case 0:
                        gBootState.unk_04 = sp1C;
                        gBootState.unk_02 = 0;
                        gBootState.unk_00 = 6;
                        break;

                    case 1:
                        gBootState.unk_04 = sp1C;
                        gBootState.unk_02 = 5;
                        gBootState.unk_00 = 4;
                        break;

                    case 2:
                        gBootState.unk_02 = 4;
                        gBootState.unk_00 = 4;
                        gBootState.unk_04 = 0x2C;
                        break;
                }
                break;

            case 42:
                gBootState.unk_00 = 2;
                break;

            case 35:
                gBootState.unk_00 = 2;
                break;

            case 49:
                gBootState.unk_04 = sp1C;
                gBootState.unk_02 = 2;
                gBootState.unk_00 = 2;
                break;

            case 2:
                gBootState.unk_04 = sp1C;
                gBootState.unk_02 = 3;
                gBootState.unk_00 = 4;
                break;

            case 11:
                gBootState.unk_04 = sp1C;
                gBootState.unk_02 = 1;
                gBootState.unk_00 = 4;
                break;

            case 34:
                gBootState.unk_04 = sp1C;
                gBootState.unk_02 = 1;
                gBootState.unk_00 = 4;
                break;

            case 43:
                if (gBootState.unk_06++ >= 0x1F) {
                    gBootState.unk_02 = 1;
                }
                LeoResetClear();
                gBootState.unk_00 = 2;
                break;

            default:
                gBootState.unk_04 = sp1C;
                gBootState.unk_02 = 1;
                gBootState.unk_00 = 4;
                break;
        }

        return 1;
    }

    return 0;
}

s32 Boot_ProcessMessageStage2(void) {
    s32 sp1C;

    if (osRecvMesg(&gBootMsgQueue, &sp1C, 0) != -1) {
        switch (sp1C) {
            default:
                gBootState.unk_02 = 1;
                gBootState.unk_00 = 1;
                gBootState.unk_04 = sp1C;
                break;

            case 0:
                gBootState.unk_00 = 4;
                break;

            case 35:
                gBootState.unk_00 = 4;
                break;

            case 2:
                gBootState.unk_00 = 4;
                break;

            case 42:
                gBootState.unk_04 = 0;
                gBootState.unk_02 = 0;
                gBootState.unk_00 = 2;
                break;

            case 47:
                gBootState.unk_04 = 0;
                gBootState.unk_02 = 0;
                gBootState.unk_00 = 2;
                break;

            case 34:
                gBootState.unk_04 = sp1C;
                gBootState.unk_02 = 1;
                gBootState.unk_00 = 1;
                break;
        }
        return 1;
    }

    return 0;
}

s32 Boot_ProcessMessageWithID(unk_D_800AA680* arg0) {
    s32 sp24;
    UNUSED s32 pad;

    if (osRecvMesg(&gBootMsgQueue, &sp24, 0) != -1) {
        switch (sp24) {
            case 0:
                if (BootID_StoreIfValid(arg0) != 0) {
                    gBootState.unk_00 = 8;
                } else {
                    gBootState.unk_02 = 5;
                    gBootState.unk_00 = 4;
                }
                break;

            case 0x23:
                gBootState.unk_00 = 8;
                break;

            case 0x2A:
                gBootState.unk_00 = 2;
                break;

            case 0x2F:
                gBootState.unk_00 = 2;
                break;

            case 0x31:
                gBootState.unk_04 = sp24;
                gBootState.unk_02 = 2;
                gBootState.unk_00 = 2;
                break;

            case 2:
                gBootState.unk_04 = sp24;
                gBootState.unk_02 = 3;
                gBootState.unk_00 = 4;
                break;

            case 0x22:
                gBootState.unk_04 = sp24;
                gBootState.unk_02 = 1;
                gBootState.unk_00 = 4;
                break;

            default:
                gBootState.unk_04 = sp24;
                gBootState.unk_02 = 1;
                gBootState.unk_00 = 4;
                break;
        }
        return 1;
    }

    return 0;
}

s32 Boot_ProcessMessageStage3(void) {
    s32 sp1C;

    if (osRecvMesg(&gBootMsgQueue, &sp1C, 0) != -1) {
        switch (sp1C) {
            case 0:
                gBootState.unk_00 = 0xA;
                break;

            case 0x23:
                gBootState.unk_00 = 8;
                break;

            case 0x2A:
                gBootState.unk_00 = 2;
                break;

            case 0x2F:
                gBootState.unk_00 = 2;
                break;

            case 0x31:
                gBootState.unk_04 = sp1C;
                gBootState.unk_02 = 2;
                gBootState.unk_00 = 2;
                break;

            case 2:
                gBootState.unk_04 = sp1C;
                gBootState.unk_02 = 3;
                gBootState.unk_00 = 4;
                break;

            case 0x22:
                gBootState.unk_04 = sp1C;
                gBootState.unk_02 = 1;
                gBootState.unk_00 = 4;
                break;

            default:
                gBootState.unk_04 = sp1C;
                gBootState.unk_02 = 1;
                gBootState.unk_00 = 4;
                break;
        }
        return 1;
    }

    return 0;
}

s32 Boot_CheckUnitReady(void) {
    UNUSED s32 pad;
    u8 sp23;
    s32 temp_v0 = LeoTestUnitReady(&sp23);

    switch (temp_v0) {
        case 0:
        case 8:
        case 35:
            break;

        default:
            gBootState.unk_04 = temp_v0;
            gBootState.unk_02 = 1;
            break;

        case 42:
            gBootState.unk_04 = 0;
            gBootState.unk_02 = 0;
            gBootState.unk_00 = 2;
            break;

        case 47:
            gBootState.unk_04 = 0;
            gBootState.unk_02 = 0;
            gBootState.unk_00 = 2;
            break;
    }
    return 0;
}

void func_8000E5B4(void) {
}

s32 Boot_MainLoop(unk_D_800AA680* arg0) {
    s32 sp24 = 1;

    if (func_800012F8() != 0) {
        while (sp24 != 0) {
            switch (gBootState.unk_00) {
                case 0:
                    sp24 = 0;
                    break;

                case 1:
                    sp24 = Boot_CheckUnitReady();
                    break;

                case 2:
                    sp24 = func_8000DDB0();
                    break;

                case 3:
                    sp24 = Boot_ProcessMessage();
                    break;

                case 4:
                    sp24 = func_8000DDE4();
                    break;

                case 5:
                    sp24 = Boot_ProcessMessageStage2();
                    break;

                case 6:
                    sp24 = Boot_DMAReadHeader(arg0);
                    break;

                case 7:
                    sp24 = Boot_ProcessMessageWithID(arg0);
                    break;

                case 8:
                    sp24 = Boot_DMAReadData();
                    break;

                case 9:
                    sp24 = Boot_ProcessMessageStage3();
                    break;

                case 10:
                    sp24 = 0;
                    break;
            }
        }
    }

    return (gBootState.unk_00 << 0x10) | (gBootState.unk_02 << 8) | gBootState.unk_04;
}

s32 Boot_Init(void) {
    s32 sp1C = func_800012F8();

    if (sp1C != 0) {
        gBootState.unk_00 = 2;
    } else {
        gBootState.unk_00 = 0;
    }

    gBootState.unk_04 = 0;
    gBootState.unk_02 = 0;
    gBootState.unk_06 = 0;

    osCreateMesgQueue(&gBootMsgQueue, &gBootMsgBuffer, 1);
    return sp1C;
}

void func_8000E760(void) {
    s32 tmp = gBootState.unk_00;

    if (tmp == 3) {
        osRecvMesg(&gBootMsgQueue, NULL, 1);
        gBootState.unk_00 = 2;
    } else {
        switch (tmp) {
            case 5:
            case 7:
            case 9:
                osRecvMesg(&gBootMsgQueue, NULL, 1);
                gBootState.unk_00 = 4;
                break;
        }
    }
}

void func_8000E7E4(void) {
    if (func_800012F8() != 0) {
        gBootState.unk_00 = 2;
        gBootState.unk_04 = 0;
        gBootState.unk_02 = 0;
    }
}
