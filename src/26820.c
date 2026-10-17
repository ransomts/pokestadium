#include "26820.h"
#include "src/26820.h"
#include "src/22630.h"
#include "src/3FB0.h"
#include "src/memory.h"

static s16 gCurrentBankSlot;
static unk_D_800AE4E8 gGbsSaveBanks[4];

void GbsBankResetCallback(UNUSED MainPoolBlock* arg0, u32 arg1) {
    u32 bank_num = arg1 - 'BNK0';
    unk_D_800AE4E8* temp_v0 = &gGbsSaveBanks[bank_num];

    if ((arg1 >= 'BNK0') && (arg1 < 'BNK4')) {
        temp_v0->unk_00 &= ~3;
        temp_v0->unk_04.unk1 = NULL;
        temp_v0->unk_08.unk1 = NULL;
    }
}

u16 GbsChecksum(u8* arg0, s32 arg1) {
    u16 var_v1 = 0;

    while (arg1-- > 2) {
        var_v1 += *arg0++;
    }
    return var_v1;
}

s32 GbsValidateBlock(u8* arg0, s32 arg1) {
    u16* temp_v1 = arg1 + arg0;

    temp_v1 -= 3;

    if (temp_v1[0] != 'PO') {
        return 0;
    }

    if (temp_v1[1] != 'KE') {
        return 0;
    }

    if (temp_v1[2] != GbsChecksum(arg0, arg1)) {
        return 0;
    }

    return 1;
}

void GbsSetBlockTrailer(u8* arg0, s32 arg1, s32 arg2) {
    u16* temp_v1;

    if (arg2 != 0) {
        temp_v1 = arg1 + arg0;

        temp_v1 -= 3;
        *temp_v1++ = 'PO';
        *temp_v1++ = 'KE';
        *temp_v1++ = GbsChecksum(arg0, arg1);
    } else {
        temp_v1 = arg1 + arg0;
        temp_v1 -= 3;

        *temp_v1++ = 'XX';
        *temp_v1++ = 'XX';
        *temp_v1++ = GbsChecksum(arg0, arg1) ^ 0xFF;
    }
}

void GbsCopyBlock(u8* arg0, u8* arg1, s32 arg2, s32 arg3) {
    _bcopy(arg0, arg1, arg2);
    gGbsSaveBanks[arg3].unk_00 |= 2;
}

void GbsCommitBlock(u8* arg0, s32 arg1, s32 arg2) {
    if (*arg0 & 2) {
        *arg0 &= ~2;
        GbsSetBlockTrailer(arg0, arg1, 1);
        gGbsSaveBanks[arg2].unk_00 |= 2;
    }
}

void GbsInvalidateBlock(u8* arg0, s32 arg1, s32 arg2) {
    if (*arg0 & 2) {
        GbsSetBlockTrailer(arg0, arg1, 0);
        gGbsSaveBanks[arg2].unk_00 |= 2;
    }
}

void GbsBackupBlock(u8* arg0, s32 arg1, s32 arg2) {
    u32 tmp = arg0 - (u8*)gGbsSaveBanks[arg2].unk_04.unk1;

    _bcopy(tmp + (u8*)gGbsSaveBanks[arg2].unk_08.unk1, arg0, arg1);
}

void GbsClearBlock(u8* arg0, s32 arg1, s32 arg2) {
    bzero(arg0, arg1);
    *arg0 |= 2;
    gGbsSaveBanks[arg2].unk_00 |= 2;
}

void GbsSyncBankBlock(s32 arg0, s32 arg1) {
    s32 sp34;
    s32 sp30;
    UNUSED s32 pad;
    s32 idx2;
    u8* sp24;
    u8* sp20;

    switch (arg0) {
        case 16:
            sp30 = gCurrentBankSlot / 4;
            idx2 = gCurrentBankSlot % 4;
            sp34 = 0x160;
            sp24 = (u8*)&gGbsSaveBanks[sp30].unk_04.unk1->unk_0000[idx2][arg1];
            sp20 = (u8*)&gGbsSaveBanks[sp30].unk_08.unk1->unk_0000[idx2][arg1];
            break;

        case 17:
            sp30 = 3;
            sp34 = 0x468;
            sp24 = (u8*)&gGbsSaveBanks[3].unk_04.unk3->unk_0000[arg1];
            sp20 = (u8*)&gGbsSaveBanks[3].unk_08.unk3->unk_0000[arg1];
            break;

        case 18:
            sp30 = 3;
            sp34 = 0xE0;
            sp24 = (u8*)&gGbsSaveBanks[3].unk_04.unk3->unk_34E0[arg1];
            sp20 = (u8*)&gGbsSaveBanks[3].unk_08.unk3->unk_34E0[arg1];
            break;

        case 19:
            sp30 = 2;
            sp34 = 0xF60;
            sp24 = (u8*)&gGbsSaveBanks[2].unk_04.unk2->unk_0DC0;
            sp20 = (u8*)&gGbsSaveBanks[2].unk_08.unk2->unk_0DC0;
            break;

        case 20:
            sp30 = 2;
            sp34 = 0x28;
            sp24 = (u8*)&gGbsSaveBanks[2].unk_04.unk2->unk_1EA0;
            sp20 = (u8*)&gGbsSaveBanks[2].unk_08.unk2->unk_1EA0;
            break;

        case 21:
            sp30 = 2;
            sp34 = 0x180;
            sp24 = (u8*)&gGbsSaveBanks[2].unk_04.unk2->unk_1D20;
            sp20 = (u8*)&gGbsSaveBanks[2].unk_08.unk2->unk_1D20;
            break;

        case 22:
            sp30 = 2;
            sp34 = 0x13B8;
            sp24 = (u8*)&gGbsSaveBanks[2].unk_04.unk2->unk_1EC8;
            sp20 = (u8*)&gGbsSaveBanks[2].unk_08.unk2->unk_1EC8;
            break;

        case 23:
            sp30 = 2;
            sp34 = 0xB84;
            sp24 = (u8*)&gGbsSaveBanks[2].unk_04.unk2->unk_3280;
            sp20 = (u8*)&gGbsSaveBanks[2].unk_08.unk2->unk_3280;
            break;
    }

    switch ((GbsValidateBlock(sp24, sp34) | GbsValidateBlock(sp20, sp34) << 1)) {
        case 0:
            GbsClearAndCommitBlock(arg0, arg1);
            break;

        case 1:
            GbsCopyBlock(sp24, sp20, sp34, sp30);
            break;

        case 2:
            GbsCopyBlock(sp20, sp24, sp34, sp30);
            break;
    }
}

void Mon_InitFromSaveEntry(unk_func_80026268_arg0* arg0, unk_D_800AE4E8_004_1_000_010* arg1) {
    func_80021D9C(arg0, arg1);
    CalculatePokemonStats(arg0);

    arg0->unk_52 = 0;
    arg0->unk_53 = 0;
    arg0->unk_25 = 0;

    _bcopy(arg1->unk_2C, arg0->unk_46, 0xB);
    DecodeGen1StringFromRawBuffer(arg0->unk_30, arg1->unk_21);
    DecodeGen1StringFromRawBuffer(arg0->unk_3B, arg1->unk_2C);
}

void Mon_WriteToSaveEntry(unk_func_80026268_arg0* arg0, unk_D_800AE4E8_004_1_000_010* arg1) {
    arg0->unk_04 = arg0->unk_24;

    func_80021F04(arg0, &arg1->unk_00);
    EncodeGen1String(arg1->unk_21, arg0->unk_30);

    _bcopy(arg0->unk_46, arg1->unk_2C, 0xB);
}

s32 GbsCheckBlockFlag(s32 arg0, s32 arg1, s16 arg2) {
    s32 var_v1 = 0;
    s16 idx1 = gCurrentBankSlot / 4;
    s16 idx2 = gCurrentBankSlot % 4;

    switch (arg0) {
        case 16:
            var_v1 = (gGbsSaveBanks[idx1].unk_04.unk1->unk_0000[idx2][arg1].unk_000.unk_00 & arg2) != 0;
            break;

        case 17:
            var_v1 = (gGbsSaveBanks[3].unk_04.unk3->unk_0000[arg1].unk_000.unk_00 & arg2) != 0;
            break;

        case 18:
            var_v1 = (gGbsSaveBanks[3].unk_04.unk3->unk_34E0[arg1].unk_00.unk_00 & arg2) != 0;
            break;

        case 19:
            var_v1 = (gGbsSaveBanks[2].unk_04.unk2->unk_0DC0.unk_000 & arg2) != 0;
            break;

        case 20:
            var_v1 = (gGbsSaveBanks[2].unk_04.unk2->unk_1EA0.unk_00 & arg2) != 0;
            break;

        case 21:
            var_v1 = (gGbsSaveBanks[2].unk_04.unk2->unk_1D20.unk_000 & arg2) != 0;
            break;

        case 22:
            var_v1 = (gGbsSaveBanks[2].unk_04.unk2->unk_1EC8.unk_0000 & arg2) != 0;
            break;

        case 23:
            var_v1 = (gGbsSaveBanks[2].unk_04.unk2->unk_3280.unk_0000 & arg2) != 0;
            break;
    }

    return var_v1;
}

void GbsSetBlockFlag(s32 arg0, s32 arg1, s16 arg2) {
    s16 idx1 = gCurrentBankSlot / 4;
    s16 idx2 = gCurrentBankSlot % 4;

    switch (arg0) {
        case 16:
            gGbsSaveBanks[idx1].unk_04.unk1->unk_0000[idx2][arg1].unk_000.unk_00 |= arg2;
            break;

        case 17:
            gGbsSaveBanks[3].unk_04.unk3->unk_0000[arg1].unk_000.unk_00 |= arg2;
            break;

        case 18:
            gGbsSaveBanks[3].unk_04.unk3->unk_34E0[arg1].unk_00.unk_00 |= arg2;
            break;

        case 19:
            gGbsSaveBanks[2].unk_04.unk2->unk_0DC0.unk_000 |= arg2;
            break;

        case 20:
            gGbsSaveBanks[2].unk_04.unk2->unk_1EA0.unk_00 |= arg2;
            break;

        case 21:
            gGbsSaveBanks[2].unk_04.unk2->unk_1D20.unk_000 |= arg2;
            break;

        case 22:
            gGbsSaveBanks[2].unk_04.unk2->unk_1EC8.unk_0000 |= arg2;
            break;

        case 23:
            gGbsSaveBanks[2].unk_04.unk2->unk_3280.unk_0000 |= arg2;
            break;
    }
}

void func_8002667C(void) {
}

void GbsCommitBankBlock(s32 arg0, s32 arg1) {
    s16 idx1 = gCurrentBankSlot / 4;
    s16 idx2 = gCurrentBankSlot % 4;

    switch (arg0) {
        case 16:
            GbsCommitBlock((u8*)&gGbsSaveBanks[idx1].unk_04.unk1->unk_0000[idx2][arg1], 0x160, idx1);
            break;

        case 17:
            GbsCommitBlock((u8*)&gGbsSaveBanks[3].unk_04.unk3->unk_0000[arg1], 0x468, 3);
            break;

        case 18:
            GbsCommitBlock((u8*)&gGbsSaveBanks[3].unk_04.unk3->unk_34E0[arg1], 0xE0, 3);
            break;

        case 19:
            GbsCommitBlock((u8*)&gGbsSaveBanks[2].unk_04.unk2->unk_0DC0, 0xF60, 2);
            break;

        case 20:
            GbsCommitBlock((u8*)&gGbsSaveBanks[2].unk_04.unk2->unk_1EA0, 0x28, 2);
            break;

        case 21:
            GbsCommitBlock((u8*)&gGbsSaveBanks[2].unk_04.unk2->unk_1D20, 0x180, 2);
            break;

        case 22:
            GbsCommitBlock((u8*)&gGbsSaveBanks[2].unk_04.unk2->unk_1EC8, 0x13B8, 2);
            break;

        case 23:
            GbsCommitBlock((u8*)&gGbsSaveBanks[2].unk_04.unk2->unk_3280, 0xB84, 2);
            break;
    }
}

void GbsInvalidateBankBlock(s32 arg0, s32 arg1) {
    s16 idx1 = gCurrentBankSlot / 4;
    s16 idx2 = gCurrentBankSlot % 4;

    switch (arg0) {
        case 16:
            GbsInvalidateBlock((u8*)&gGbsSaveBanks[idx1].unk_04.unk1->unk_0000[idx2][arg1], 0x160, idx1);
            break;

        case 17:
            GbsInvalidateBlock((u8*)&gGbsSaveBanks[3].unk_04.unk3->unk_0000[arg1], 0x468, 3);
            break;

        case 18:
            GbsInvalidateBlock((u8*)&gGbsSaveBanks[3].unk_04.unk3->unk_34E0[arg1], 0xE0, 3);
            break;

        case 19:
            GbsInvalidateBlock((u8*)&gGbsSaveBanks[2].unk_04.unk2->unk_0DC0, 0xF60, 2);
            break;

        case 20:
            GbsInvalidateBlock((u8*)&gGbsSaveBanks[2].unk_04.unk2->unk_1EA0, 0x28, 2);
            break;

        case 21:
            GbsInvalidateBlock((u8*)&gGbsSaveBanks[2].unk_04.unk2->unk_1D20, 0x180, 2);
            break;

        case 22:
            GbsInvalidateBlock((u8*)&gGbsSaveBanks[2].unk_04.unk2->unk_1EC8, 0x13B8, 2);
            break;

        case 23:
            GbsInvalidateBlock((u8*)&gGbsSaveBanks[2].unk_04.unk2->unk_3280, 0xB84, 2);
            break;
    }
}

void GbsBackupBankBlock(s32 arg0, s32 arg1) {
    s16 idx1 = gCurrentBankSlot / 4;
    s16 idx2 = gCurrentBankSlot % 4;

    switch (arg0) {
        case 16:
            GbsBackupBlock((u8*)&gGbsSaveBanks[idx1].unk_04.unk1->unk_0000[idx2][arg1], 0x160, idx1);
            break;

        case 17:
            GbsBackupBlock((u8*)&gGbsSaveBanks[3].unk_04.unk3->unk_0000[arg1], 0x468, 3);
            break;

        case 18:
            GbsBackupBlock((u8*)&gGbsSaveBanks[3].unk_04.unk3->unk_34E0[arg1], 0xE0, 3);
            break;

        case 19:
            GbsBackupBlock((u8*)&gGbsSaveBanks[2].unk_04.unk2->unk_0DC0, 0xF60, 2);
            break;

        case 20:
            GbsBackupBlock((u8*)&gGbsSaveBanks[2].unk_04.unk2->unk_1EA0, 0x28, 2);
            break;

        case 21:
            GbsBackupBlock((u8*)&gGbsSaveBanks[2].unk_04.unk2->unk_1D20, 0x180, 2);
            break;

        case 22:
            GbsBackupBlock((u8*)&gGbsSaveBanks[2].unk_04.unk2->unk_1EC8, 0x13B8, 2);
            break;

        case 23:
            GbsBackupBlock((u8*)&gGbsSaveBanks[2].unk_04.unk2->unk_3280, 0xB84, 2);
            break;
    }
}

void GbsClearBankBlock(s32 arg0, s32 arg1) {
    UNUSED s32 pad;
    unk_D_800AE4E8_004_1_000* sp38;
    unk_D_800AE4E8_004_3_0000* sp34;
    unk_D_800AE4E8_004_3_34E0* sp30;
    unk_D_800AE4E8_004_2_0DC0* sp2C;
    unk_D_800AE4E8_004_2_1EA0* sp28;
    unk_D_800AE4E8_004_2_1D20* sp24;
    unk_D_800AE4E8_004_2_1EC8* sp20;
    unk_D_800AE4E8_004_2_3280* sp1C;
    s16 idx1 = gCurrentBankSlot / 4;
    s16 idx2 = gCurrentBankSlot % 4;

    switch (arg0) {
        case 16:
            sp38 = &gGbsSaveBanks[idx1].unk_04.unk1->unk_0000[idx2][arg1];
            GbsClearBlock(sp38, 0x160, idx1);
            sp38->unk_000.unk_01 = 0x50;
            break;

        case 17:
            sp34 = &gGbsSaveBanks[3].unk_04.unk3->unk_0000[arg1];
            GbsClearBlock(sp34, 0x468, 3);
            sp34->unk_000.unk_01 = 0x50;
            break;

        case 18:
            sp30 = &gGbsSaveBanks[3].unk_04.unk3->unk_34E0[arg1];
            GbsClearBlock(sp30, 0xE0, 3);
            sp30->unk_00.unk_01 = 0x50;
            break;

        case 19:
            sp2C = &gGbsSaveBanks[2].unk_04.unk2->unk_0DC0;
            GbsClearBlock(sp2C, 0xF60, 2);
            sp2C->unk_000 |= 1;
            break;

        case 20:
            sp28 = &gGbsSaveBanks[2].unk_04.unk2->unk_1EA0;
            GbsClearBlock(sp28, 0x28, 2);
            sp28->unk_00 |= 1;
            break;

        case 21:
            sp24 = &gGbsSaveBanks[2].unk_04.unk2->unk_1D20;
            GbsClearBlock(sp24, 0x180, 2);
            break;

        case 22:
            sp20 = &gGbsSaveBanks[2].unk_04.unk2->unk_1EC8;
            GbsClearBlock(sp20, 0x13B8, 2);
            sp20->unk_0000 |= 1;
            break;

        case 23:
            sp1C = &gGbsSaveBanks[2].unk_04.unk2->unk_3280;
            GbsClearBlock(sp1C, 0xB84, 2);
            sp1C->unk_0000 |= 1;
            break;
    }
}

void GbsProcessBankWrites(s16 arg0) {
    s32 i;
    s32 sp28;

    if (gGbsSaveBanks[arg0].unk_00 & 1) {
        sp28 = gCurrentBankSlot;

        switch (arg0) {
            case 0:
                for (gCurrentBankSlot = 0; gCurrentBankSlot < 4; gCurrentBankSlot++) {
                    for (i = 0; i < 10; i++) {
                        GbsCommitBankBlock(0x10, i);
                    }
                }
                break;

            case 1:
                for (gCurrentBankSlot = 4; gCurrentBankSlot < 8; gCurrentBankSlot++) {
                    for (i = 0; i < 10; i++) {
                        GbsCommitBankBlock(0x10, i);
                    }
                }
                break;

            case 2:
                gCurrentBankSlot = 8;

                for (i = 0; i < 10; i++) {
                    GbsCommitBankBlock(0x10, i);
                }

                GbsCommitBankBlock(0x13, 0);
                GbsCommitBankBlock(0x14, 0);
                GbsCommitBankBlock(0x15, 0);
                GbsCommitBankBlock(0x16, 0);
                GbsCommitBankBlock(0x17, 0);
                break;

            case 3:
                for (i = 0; i < 12; i++) {
                    GbsCommitBankBlock(0x11, i);
                }

                for (i = 0; i < 4; i++) {
                    GbsCommitBankBlock(0x12, i);
                }

                break;
        }

        gCurrentBankSlot = sp28;
    }
}

void GbsProcessAllBanks(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        GbsProcessBankWrites(i);
    }
}

void GbsClearAndCommitBlock(s32 arg0, s32 arg1) {
    GbsClearBankBlock(arg0, arg1);
    GbsCommitBankBlock(arg0, arg1);
}

s32 GbsGetBlockEntryCount(s32 arg0) {
    s32 var_v1 = 0;

    switch (arg0) {
        case 16:
            var_v1 = 6;
            break;

        case 17:
            var_v1 = 0x14;
            break;

        case 18:
            var_v1 = 0x64;
            break;

        case 19:
            var_v1 = 0x97;
            break;

        case 22:
            var_v1 = 0x24;
            break;

        case 23:
            var_v1 = 0x15;
            break;
    }

    return var_v1;
}

s32 GbsGetBlockDataSize(s32 arg0) {
    s32 var_v1 = 0;

    switch (arg0) {
        case 16:
            var_v1 = 0x54;
            break;

        case 17:
            var_v1 = 0x54;
            break;

        case 18:
            var_v1 = 2;
            break;

        case 19:
            var_v1 = 0x1A;
            break;

        case 22:
            var_v1 = 0x8C;
            break;

        case 23:
            var_v1 = 0x8C;
            break;
    }

    return var_v1;
}

s32 GbsIsBlockActive(s32 arg0, s32 arg1) {
    return GbsCheckBlockFlag(arg0, arg1, 1);
}

s32 GbsGetBlockStatusField(s32 arg0, s32 arg1) {
    s32 sp1C = -1;

    if (GbsIsBlockActive(arg0, arg1) != 0) {
        s16 idx1 = gCurrentBankSlot / 4;
        s16 idx2 = gCurrentBankSlot % 4;

        switch (arg0) {
            case 16:
                sp1C = gGbsSaveBanks[idx1].unk_04.unk1->unk_0000[idx2][arg1].unk_000.unk_0C;
                break;

            case 17:
                sp1C = gGbsSaveBanks[3].unk_04.unk3->unk_0000[arg1].unk_000.unk_0C;
                break;

            case 18:
                sp1C = gGbsSaveBanks[3].unk_04.unk3->unk_34E0[arg1].unk_00.unk_0C;
                break;
        }
    }
    return sp1C;
}

char* GbsGetBlockString(s32 arg0, s32 arg1, char* arg2) {
    char* sp1C = NULL;
    char* var_a1;

    *arg2 = '\x00';

    if (GbsIsBlockActive(arg0, arg1) != 0) {
        s16 idx1 = gCurrentBankSlot / 4;
        s16 idx2 = gCurrentBankSlot % 4;

        var_a1 = NULL;

        switch (arg0) {
            case 16:
                var_a1 = &gGbsSaveBanks[idx1].unk_04.unk1->unk_0000[idx2][arg1].unk_000.unk_01;
                break;

            case 17:
                var_a1 = &gGbsSaveBanks[3].unk_04.unk3->unk_0000[arg1].unk_000.unk_01;
                break;

            case 18:
                var_a1 = &gGbsSaveBanks[3].unk_04.unk3->unk_34E0[arg1].unk_00.unk_01;
                break;
        }

        if (var_a1 != NULL) {
            sp1C = DecodeGen1String(arg2, var_a1);
        }
    }

    return sp1C;
}

void func_80027410(s32 arg0, s32 arg1, char* arg2) {
    GbsGetBlockString(arg0, arg1, arg2);
}

void GbsSetBlockStringAndValue(s32 arg0, s32 arg1, s32 arg2, char* arg3, u16 arg4) {
    unk_D_800AE4E8_004_1_000* temp_v0;
    unk_D_800AE4E8_004_3_0000* temp_v0_2;
    unk_D_800AE4E8_004_3_34E0* temp_v0_3;
    s16 idx1 = gCurrentBankSlot / 4;
    s16 idx2 = gCurrentBankSlot % 4;

    switch (arg0) {
        case 16:
            temp_v0 = &gGbsSaveBanks[idx1].unk_04.unk1->unk_0000[idx2][arg1];
            if (arg4 >= 0) {
                temp_v0->unk_000.unk_0C = arg4;
            }

            if (arg3 != NULL) {
                EncodeGen1String(&temp_v0->unk_000.unk_01, arg3);
            }

            GbsSetBlockFlag(arg0, arg1, 3);
            break;

        case 17:
            temp_v0_2 = &gGbsSaveBanks[3].unk_04.unk3->unk_0000[arg1];
            if (arg4 >= 0) {
                temp_v0_2->unk_000.unk_0C = arg4;
            }

            if (arg3 != NULL) {
                EncodeGen1String(&temp_v0_2->unk_000.unk_01, arg3);
            }

            GbsSetBlockFlag(arg0, arg1, 3);
            break;

        case 18:
            temp_v0_3 = &gGbsSaveBanks[3].unk_04.unk3->unk_34E0[arg1];
            if (arg4 >= 0) {
                temp_v0_3->unk_00.unk_0C = arg4;
            }

            if (arg3 != NULL) {
                EncodeGen1String(&temp_v0_3->unk_00.unk_01, arg3);
            }

            GbsSetBlockFlag(arg0, arg1, 3);
            break;
    }
}

s16 func_800275E0(s32 arg0, s32 arg1) {
    s16 var_v1 = 0;
    s32 idx1 = gCurrentBankSlot / 4;
    s32 idx2 = gCurrentBankSlot % 4;

    switch (arg0) {
        case 16:
            var_v1 = gGbsSaveBanks[idx1].unk_04.unk1->unk_0000[idx2][arg1].unk_000.unk_0E;
            break;

        case 17:
            var_v1 = gGbsSaveBanks[3].unk_04.unk3->unk_0000[arg1].unk_000.unk_0E;
            break;

        case 18:
            var_v1 = gGbsSaveBanks[3].unk_04.unk3->unk_34E0[arg1].unk_00.unk_0E;
            break;

        case 19:
            var_v1 = 0x97;
            break;

        case 22:
            var_v1 = 0x24;
            break;

        case 23:
            var_v1 = 0x15;
            break;
    }

    return var_v1;
}

void func_800276F0(s32 arg0, s32 arg1, s32 arg2) {
    s32 sp1C = gCurrentBankSlot / 4;
    s32 sp18 = gCurrentBankSlot % 4;

    if (arg2 < func_800275E0(arg0, arg1)) {
        switch (arg0) {
            case 16:
                gGbsSaveBanks[sp1C].unk_04.unk1->unk_0000[sp18][arg1].unk_000.unk_0E = arg2;
                break;

            case 17:
                gGbsSaveBanks[3].unk_04.unk3->unk_0000[arg1].unk_000.unk_0E = arg2;
                break;

            case 18:
                gGbsSaveBanks[3].unk_04.unk3->unk_34E0[arg1].unk_00.unk_0E = arg2;
                break;
        }

        GbsSetBlockFlag(arg0, arg1, 2);
    }
}

void func_8002782C(s32 arg0, s32 arg1) {
    s32 idx1;
    s32 idx2;
    s32 sp1C;

    idx1 = gCurrentBankSlot / 4;
    idx2 = gCurrentBankSlot % 4;

    sp1C = func_800275E0(arg0, arg1);
    if (sp1C < GbsGetBlockEntryCount(arg0)) {
        switch (arg0) {
            case 16:
                gGbsSaveBanks[idx1].unk_04.unk1->unk_0000[idx2][arg1].unk_000.unk_0E = sp1C + 1;
                break;

            case 17:
                gGbsSaveBanks[3].unk_04.unk3->unk_0000[arg1].unk_000.unk_0E = sp1C + 1;
                break;

            case 18:
                gGbsSaveBanks[3].unk_04.unk3->unk_34E0[arg1].unk_00.unk_0E = sp1C + 1;
                break;
        }
        GbsSetBlockFlag(arg0, arg1, 2);
    }
}

s32 func_8002797C(s32 arg0, s32 arg1, s32 arg2, void* arg3) {
    s32 sp2C = 0;
    s32 idx1 = gCurrentBankSlot / 4;
    s32 idx2 = gCurrentBankSlot % 4;

    if (arg2 < func_800275E0(arg0, arg1)) {
        switch (arg0) {
            case 16:
                Mon_InitFromSaveEntry(arg3, &gGbsSaveBanks[idx1].unk_04.unk1->unk_0000[idx2][arg1].unk_010[arg2]);
                break;

            case 17:
                Mon_InitFromSaveEntry(arg3, &gGbsSaveBanks[3].unk_04.unk3->unk_0000[arg1].unk_010[arg2]);
                break;

            case 18:
                *(unk_D_800AE4E8_004_3_34E0_010*)arg3 = gGbsSaveBanks[3].unk_04.unk3->unk_34E0[arg1].unk_10[arg2];
                break;

            case 19:
                *(unk_D_800AE4E8_004_2_0DC0_002*)arg3 = gGbsSaveBanks[2].unk_04.unk2->unk_0DC0.unk_002[arg2];
                break;

            case 22:
                _bcopy(&gGbsSaveBanks[2].unk_04.unk2->unk_1EC8.unk_0002[arg2], arg3,
                       sizeof(unk_D_800AE4E8_004_2_1EC8_0002));
                break;

            case 23:
                _bcopy(&gGbsSaveBanks[2].unk_04.unk2->unk_3280.unk_0002[arg2], arg3,
                       sizeof(unk_D_800AE4E8_004_2_1EC8_0002));
                break;
        }
        sp2C = 1;
    }

    return sp2C;
}

s32 func_80027C24(s32 arg0, s32 arg1, s32 arg2, void* arg3) {
    s32 sp34 = 0;
    s32 idx1 = gCurrentBankSlot / 4;
    s32 idx2 = gCurrentBankSlot % 4;
    s32 sp28 = GbsGetBlockEntryCount(arg0);
    s32 sp24 = func_800275E0(arg0, arg1);

    if ((arg2 < sp24) || ((arg2 == sp24) && (arg2 < sp28))) {
        switch (arg0) {
            case 16:
                Mon_WriteToSaveEntry(arg3, &gGbsSaveBanks[idx1].unk_04.unk1->unk_0000[idx2][arg1].unk_010[arg2]);
                break;
            case 17:
                Mon_WriteToSaveEntry(arg3, &gGbsSaveBanks[3].unk_04.unk3->unk_0000[arg1].unk_010[arg2]);
                break;
            case 18:
                gGbsSaveBanks[3].unk_04.unk3->unk_34E0[arg1].unk_10[arg2] = *(unk_D_800AE4E8_004_3_34E0_010*)arg3;
                break;
            case 19:
                gGbsSaveBanks[2].unk_04.unk2->unk_0DC0.unk_002[arg2] = *(unk_D_800AE4E8_004_2_0DC0_002*)arg3;
                break;
            case 22:
                _bcopy(arg3, &gGbsSaveBanks[2].unk_04.unk2->unk_1EC8.unk_0002[arg2], 0x8C);
                break;
            case 23:
                _bcopy(arg3, &gGbsSaveBanks[2].unk_04.unk2->unk_3280.unk_0002[arg2], 0x8C);
                break;
        }

        if (arg2 == sp24) {
            func_8002782C(arg0, arg1);
        } else {
            GbsSetBlockFlag(arg0, arg1, 2);
        }

        sp34 = 1;
    }
    return sp34;
}

void func_80027F24(unk_func_8002A728* arg0) {
    *arg0 = gGbsSaveBanks[2].unk_04.unk2->unk_1EA0.unk_04;
}

void func_80027F40(unk_func_8002A728* arg0) {
    if (bcmp(arg0, &gGbsSaveBanks[2].unk_04.unk2->unk_1EA0.unk_04, 8) != 0) {
        gGbsSaveBanks[2].unk_04.unk2->unk_1EA0.unk_04 = *arg0;
        GbsSetBlockFlag(0x14, 0, 2);
    }
}

void func_80027FA0(unk_func_80027FA0* arg0, s16 arg1) {
    *arg0 = gGbsSaveBanks[2].unk_04.unk2->unk_1EA0.unk_0C[arg1];
}

void func_80027FE0(unk_func_80027FA0* arg0, s16 arg1) {
    if (bcmp(arg0, &gGbsSaveBanks[2].unk_04.unk2->unk_1EA0.unk_0C[arg1], sizeof(unk_func_80027FA0)) != 0) {
        gGbsSaveBanks[2].unk_04.unk2->unk_1EA0.unk_0C[arg1] = *arg0;
        GbsSetBlockFlag(0x14, 0, 2);
    }
}

void func_80028070(u16* arg0) {
    *arg0 = gGbsSaveBanks[2].unk_04.unk2->unk_1EA0.unk_02;
}

void func_80028084(u16* arg0) {
    u16 tmp = *arg0;
    unk_D_800AE4E8_004_2* temp_v1 = gGbsSaveBanks[2].unk_04.unk2;

    if (temp_v1->unk_1EA0.unk_02 != tmp) {
        temp_v1->unk_1EA0.unk_02 = tmp;
        GbsSetBlockFlag(0x14, 0, 2);
    }
}

s32 func_800280C4(void) {
    return gGbsSaveBanks[2].unk_04.unk2->unk_1EA0.unk_1E;
}

void func_800280D4(u8 arg0) {
    unk_D_800AE4E8_004_2* temp_v0 = gGbsSaveBanks[2].unk_04.unk2;

    if (temp_v0->unk_1EA0.unk_1E != arg0) {
        temp_v0->unk_1EA0.unk_1E = arg0;
        GbsSetBlockFlag(0x14, 0, 2);
    }
}

s32 func_80028118(void) {
    return gGbsSaveBanks[2].unk_04.unk2->unk_1EA0.unk_1F;
}

void func_80028128(u8 arg0) {
    unk_D_800AE4E8_004_2* temp_v0 = gGbsSaveBanks[2].unk_04.unk2;

    if (temp_v0->unk_1EA0.unk_1F != arg0) {
        temp_v0->unk_1EA0.unk_1F = arg0;
        GbsSetBlockFlag(0x14, 0, 2);
    }
}

s32 func_8002816C(void) {
    return gGbsSaveBanks[2].unk_04.unk2->unk_1EA0.unk_1C;
}

void func_8002817C(u8 arg0, u8 arg1) {
    s32 temp_v0 = (((arg1 & 1) << 8) | arg0) & 0xFFFF;
    unk_D_800AE4E8_004_2* temp_v1 = gGbsSaveBanks[2].unk_04.unk2;

    if (temp_v1->unk_1EA0.unk_1C != temp_v0) {
        temp_v1->unk_1EA0.unk_1C = temp_v0;
        GbsSetBlockFlag(0x14, 0, 2);
    }
}

void func_800281D4(unk_func_800281D4* arg0, unk_func_80026268_arg0* arg1, s32 arg2) {
    unk_D_800AE4E8_004_2_1D20* temp_v0;
    s32 i;

    if (gGbsSaveBanks[2].unk_00 & 1) {
        temp_v0 = &gGbsSaveBanks[2].unk_04.unk2->unk_1D20;

        temp_v0->unk_000 |= 3;
        temp_v0->unk_002 = *arg0;
        temp_v0->unk_022 = arg2;

        for (i = 0; i < arg2; i++) {
            Mon_WriteToSaveEntry(&arg1[i], &temp_v0->unk_024[i]);
            temp_v0->unk_16E[i] = arg1[i].unk_52;
            temp_v0->unk_174[i] = arg1[i].unk_53;
        }
    }
}

s32 func_80028320(unk_func_800281D4* arg0, unk_func_80026268_arg0* arg1) {
    s16 var_s5 = -1;
    unk_D_800AE4E8_004_2_1D20* temp_v0;
    s32 i;

    if (gGbsSaveBanks[2].unk_00 & 1) {
        temp_v0 = &gGbsSaveBanks[2].unk_04.unk2->unk_1D20;

        if (temp_v0->unk_000 & 1) {
            *arg0 = temp_v0->unk_002;
            var_s5 = temp_v0->unk_022;
            if (arg1 != NULL) {
                for (i = 0; i < var_s5; i++) {
                    Mon_InitFromSaveEntry(&arg1[i], &temp_v0->unk_024[i]);
                    arg1[i].unk_52 = temp_v0->unk_16E[i];
                    arg1[i].unk_53 = temp_v0->unk_174[i];
                }
            }
        }
    }
    return var_s5;
}

s32 func_8002847C(void) {
    s32 var_v1 = 0;

    if (gGbsSaveBanks[2].unk_00 & 1) {
        unk_D_800AE4E8_004_2_1D20* temp_v0 = &gGbsSaveBanks[2].unk_04.unk2->unk_1D20;

        var_v1 = (temp_v0->unk_000 & 1) != 0;
    }
    return var_v1;
}

s32 func_800284B4(s16 arg0) {
    static u32 D_80073650[] = {
        0x3700,
        0x3700,
        0x3F80,
        0x3880,
    };

    s32 sp38;
    s32 var_s0;
    s16 temp_s5;

    temp_s5 = D_80073650[arg0] >> 7;

    if ((gGbsSaveBanks[arg0].unk_00 & 1) && (gGbsSaveBanks[arg0].unk_00 & 2)) {
        _bcopy(gGbsSaveBanks[arg0].unk_04.unk1, gGbsSaveBanks[arg0].unk_08.unk1, D_80073650[arg0]);
        var_s0 = 0;
        while (func_80003B04(arg0) == -1) {
            var_s0++;
            if (var_s0 == 4) {
                return -1;
            }
        }

        var_s0 = 0;
        sp38 = arg0 << 7;
        while (DmaCopyAsyncBlock((u8*)gGbsSaveBanks[arg0].unk_04.unk1, sp38, temp_s5, 1) == -1) {
            var_s0++;
            if (var_s0 == 4) {
                return -1;
            }
        }

        var_s0 = 0;
        while (func_80003B04(arg0 + 4) == -1) {
            var_s0 += 1;
            if (var_s0 == 4) {
                return -1;
            }
        }

        sp38 = arg0 << 7;
        sp38 += 0x200;
        var_s0 = 0;
        while (DmaCopyAsyncBlock((u8*)gGbsSaveBanks[arg0].unk_08.unk1, sp38, temp_s5, 1) == -1) {
            var_s0++;
            if (var_s0 == 4) {
                return 0;
            }
        }

        gGbsSaveBanks[arg0].unk_00 &= ~2;
    }

    return 0;
}

s32 func_800286D8(void) {
    s32 i;
    s32 var_s1 = 0;

    for (i = 0; i < 4; i++) {
        if (func_800284B4(i) != 0) {
            var_s1 |= 1 << i;
        }
    }

    return var_s1;
}

s32 func_8002873C(s16 arg0, u32 arg1) {
    s32 sp2C = 0;
    u8* sp28;

    if (gGbsSaveBanks[arg0].unk_04.unk1 == NULL) {
        sp28 = main_pool_alloc_with_func(arg1 * 2, 0, 'BNK0' + arg0, GbsBankResetCallback);
        if (sp28 != NULL) {
            bzero(sp28, arg1 * 2);
            gGbsSaveBanks[arg0].unk_04.unk1 = sp28;
            gGbsSaveBanks[arg0].unk_08.unk1 = sp28 + arg1;
            DmaCopyAsyncBlock(sp28, arg0 << 7, arg1 >> 7, 0);
            DmaCopyAsyncBlock(gGbsSaveBanks[arg0].unk_08.unk1, (arg0 << 7) + 0x200, arg1 >> 7, 0);
            sp2C = 1;
        }
    }

    return sp2C;
}

void func_80028840(void) {
    s32 j;
    s32 sp28;

    if (func_8002873C(0, 0x3700) != 0) {
        sp28 = gCurrentBankSlot;

        for (gCurrentBankSlot = 0; gCurrentBankSlot < 4; gCurrentBankSlot++) {
            for (j = 0; j < 10; j++) {
                GbsSyncBankBlock(0x10, j);
            }
        }

        gGbsSaveBanks->unk_00 |= 1;
        gCurrentBankSlot = sp28;
    }
}

void func_800288F4(void) {
    s32 i;
    s32 sp28;

    if (func_8002873C(1, 0x3700) != 0) {
        sp28 = gCurrentBankSlot;
        gCurrentBankSlot = 4;
        while (gCurrentBankSlot < 8) {
            for (i = 0; i < 10; i++) {
                GbsSyncBankBlock(16, i);
            }
            gCurrentBankSlot++;
        }
        gGbsSaveBanks[1].unk_00 |= 1;
        gCurrentBankSlot = sp28;
    }
}

void func_800289AC(void) {
    s32 i;
    s32 sp20;

    if (func_8002873C(2, 0x3F80) != 0) {
        sp20 = gCurrentBankSlot;
        gCurrentBankSlot = 8;

        for (i = 0; i < 10; i++) {
            GbsSyncBankBlock(16, i);
        }

        GbsSyncBankBlock(19, 0);
        GbsSyncBankBlock(20, 0);
        GbsSyncBankBlock(21, 0);
        GbsSyncBankBlock(22, 0);
        GbsSyncBankBlock(23, 0);

        gGbsSaveBanks[2].unk_00 |= 1;
        gCurrentBankSlot = sp20;
    }
}

void func_80028A74(void) {
    s32 i;

    if (func_8002873C(3, 0x3880) != 0) {
        for (i = 0; i < 12; i++) {
            GbsSyncBankBlock(17, i);
        }

        for (i = 0; i < 4; i++) {
            GbsSyncBankBlock(18, i);
        }

        gGbsSaveBanks[3].unk_00 |= 1;
    }
}

s32 func_80028AFC(s16 arg0) {
    if (!((gGbsSaveBanks[arg0].unk_00 & 1) != 0)) {
        switch (arg0) {
            case 0:
                func_80028840();
                break;

            case 1:
                func_800288F4();
                break;

            case 2:
                func_800289AC();
                break;

            case 3:
                func_80028A74();
                break;
        }
    }

    return (gGbsSaveBanks[arg0].unk_00 & 1) != 0;
}

void func_80028BE4(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        func_80028AFC(i);
    }
}

void func_80028C28(void) {
    func_80028AFC(3);
}

s32 func_80028C48(s16 arg0) {
    s32 tmp = gCurrentBankSlot;

    if ((arg0 >= 0) && (arg0 < 9)) {
        gCurrentBankSlot = arg0;
    }
    return tmp;
}

s32 func_80028C7C(unk_D_800AE4E8_004_1_000* arg0, s32 arg1) {
    s32 var_v1 = 0;
    s32 idx1 = gCurrentBankSlot / 4;
    s32 idx2 = gCurrentBankSlot % 4;

    if ((arg1 >= 0) && (arg1 < 0xA)) {
        *arg0 = gGbsSaveBanks[idx1].unk_04.unk1->unk_0000[idx2][arg1];
        var_v1 = 1;
    }
    return var_v1;
}

s32 func_80028D60(unk_D_800AE4E8_004_1_000* arg0, s32 arg1) {
    s32 var_v1 = 0;
    s32 idx1 = gCurrentBankSlot / 4;
    s32 idx2 = gCurrentBankSlot % 4;

    if ((arg1 >= 0) && (arg1 < 0xA)) {
        gGbsSaveBanks[idx1].unk_04.unk1->unk_0000[idx2][arg1] = *arg0;
        GbsSetBlockFlag(0x10, arg1, 2);
        var_v1 = 1;
    }
    return var_v1;
}

s32 func_80028E68(void) {
    s32 i;

    for (i = 0; i < 10; i++) {
        if (GbsIsBlockActive(0x10, i) == 0) {
            break;
        }
    }

    return i;
}

void func_80028EB8(void) {
    unk_D_800AE4E8_004_1_000 sp40;
    s32 i;
    s32 j;

    for (i = 9; i >= 0; i--) {
        if (GbsIsBlockActive(0x10, i) != 0) {
            break;
        }
    }

    for (j = i - 1; j >= 0; j--) {
        if (GbsIsBlockActive(0x10, j) != 0) {
            continue;
        }

        for (i = j; i < 9; i++) {
            if (i && i) {}

            func_80028C7C(&sp40, i + 1);
            func_80028D60(&sp40, i);
            GbsCommitBankBlock(0x10, i);
        }

        GbsClearAndCommitBlock(0x10, 9);
    }
}
