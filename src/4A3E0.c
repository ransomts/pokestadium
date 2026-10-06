#include "4A3E0.h"
#include "src/4B940.h"
#include "src/373A0.h"

typedef struct unk_D_800FD008 {
    /* 0x00 */ u16 unk_00[20];
    /* 0x28 */ u8 unk_28;
    /* 0x29 */ u8 unk_29;
    /* 0x2A */ u8 unk_2A;
    /* 0x2B */ char unk2B[1];
    /* 0x2C */ u8 unk_2C;
    /* 0x2D */ char unk2D[0x13]
} unk_D_800FD008; // size = 0x40

typedef struct unk_D_800FD068 {
    /* 0x00 */ u8* unk_00;
    /* 0x04 */ u8 unk_04;
    /* 0x06 */ u16 unk_06;
} unk_D_800FD068; // size = 0x8

typedef struct unk_D_800FCFD8 {
    /* 0x00 */ u32 unk_00;
    /* 0x04 */ u8 unk_04;
    /* 0x05 */ u8 pad05[0x3];
    /* 0x04 */ u32 unk_08;
    /* 0x04 */ f32 unk_0C;
    /* 0x04 */ f32 unk_10;
    /* 0x04 */ f32 unk_14;
    /* 0x04 */ f32 unk_18;
    /* 0x04 */ u32 unk_1C;
    /* 0x04 */ u32 unk_20;
    /* 0x04 */ u32 unk_24;
    /* 0x04 */ u8 unk_28;
} unk_D_800FCFD8; // size = 0x2C

typedef struct unk_D_800FCF90 {
    /* 0x00 */ u32 unk_00;
    /* 0x00 */ s16 unk_04;
    /* 0x00 */ s16 unk_06;
    /* 0x00 */ u32 unk_08;
    /* 0x00 */ u32 unk_0C;
    /* 0x00 */ s16 unk_10;
    /* 0x00 */ s16 unk_12;
    /* 0x00 */ s16 unk_14;
    /* 0x00 */ u8 unk_16;
    /* 0x00 */ u32 unk_18;
    /* 0x00 */ u32 unk_1C;
    /* 0x00 */ u32 unk_20;
    /* 0x24 */ u8 unk_24;
} unk_D_800FCF90; // size = 0x28

typedef struct unk_D_800FCFB8 {
    /* 0x00 */ u32 unk_00;
    /* 0x04 */ u8 unk04[0x18];
    /* 0x1C */ u8 unk_1C;
} unk_D_800FCFB8; // size = 0x20

typedef struct unk_D_800FCF60 {
    /* 0x00 */ u32 unk_00;
    /* 0x04 */ u32 unk_04;
    /* 0x08 */ u32 unk_08;
    /* 0x0C */ s16 unk_0C;
    /* 0x0E */ s16 unk_0E;
    /* 0x10 */ u32 unk_10;
    /* 0x14 */ s32 unk_14;
    /* 0x18 */ s16 unk_18;
    /* 0x1A */ s16 unk_1A;
    /* 0xCA */ s16 unk_1C;
    /* 0x1E */ s16 unk_1E;
    /* 0x20 */ u32 unk_20;
    /* 0x24 */ u32 unk_24;
    /* 0x28 */ u32 unk_28;
    /* 0x2C */ u8 unk_2C;
} unk_D_800FCF60; // size = 0x30

// .bss
unk_D_800FCF60 D_800FCF60;
unk_D_800FCF90 D_800FCF90;
unk_D_800FCFB8 D_800FCFB8;
unk_D_800FCFD8 D_800FCFD8;
u32 D_800FD004;
unk_D_800FD008 D_800FD008;
u8 D_800FD048[32];
unk_D_800FD068 D_800FD068[199];
u8 D_800FD6A0[8];
u32 D_800FD6A8;
u32 D_800FD6AC;
static u8 D_800FD6B0[0x30]; // pad
u8 D_800FD6E0;
u8 D_800FD6E1;
f32 D_800FD6E4;
s32 D_800FD6E8;
static u8 D_800FD6EC[0x4]; // pad
u32 D_800FD6F0;
u32 D_800FD6F4;
s16 D_800FD6F8[0x1140];
u32 D_800FF978;
u8 D_800FF97C;
s32 D_800FF980;

void func_80049A60(u32);
void func_8004AC9C();
void func_8004ACD0();

void func_800497E0(s16* arg0, s32 arg1, u32 arg2, f32 arg3) {
    func_80049A60(arg2);
}

void func_8004980C(u16 arg0, u8 arg1, u16 arg2) {
    D_800FD068[D_800FD6AC].unk_00 = (u8*)&D_800FD008.unk_00[(arg0 & 0xFF) - 0x10];
    D_800FD068[D_800FD6AC].unk_04 = arg1;
    D_800FD068[D_800FD6AC].unk_06 = arg2 + 1;
    D_800FD6A0[arg0 & 0xFF] = arg1;
    D_800FD6AC++;
    D_800FD6AC %= 200;
    D_800FD068[D_800FD6AC].unk_06 = 0;
}

u8 func_80049890(u16 arg0) {
    return D_800FD6A0[arg0 & 0xFF];
}

void func_800498A8(u32 arg0, u8 arg1, u32 arg2) {
    u32 temp_t3;
    u8* p;
    s32 i;
    D_800FD004 = arg0 >> 1;
    D_800FD6E4 = 1048576.0f / (f32) D_800FD004;

    p = (u8*) &D_800FD008;
    for (i = 0; i < 48; i++) {
       p[i * 2 + 1] = 1;
    }
    p = (u8*) &D_800FD008;
    p[0x00] = 8;
    p[0x02] = 0;
    p[0x04] = 0;
    p[0x06] = 0;
    p[0x08] = 0x40;
    p[0x0C] = 0;
    p[0x0E] = 0;
    p[0x10] = 0;
    p[0x12] = 0x40;
    p[0x14] = 0;
    p[0x16] = 0;
    p[0x18] = 0;
    p[0x1A] = 0;
    p[0x1C] = 0x40;
    p[0x20] = 0;
    p[0x22] = 0;
    p[0x24] = 0;
    p[0x26] = 0x40;
    p[0x28] = 0;
    p[0x2A] = 0;
    p[0x2C] = 0;

    p = D_800FD048;
    for (i = 0; i < 16; i++) {
        p[i * 2] = 0;
    }
    D_800FD6AC = 0;
    D_800FD068[0].unk_06 = 0;
    D_800FD6A8 = 0;
    D_800FCF60.unk_00 = 0;
    D_800FCF60.unk_2C = 0;

    D_800FCF90.unk_00 = 0;
    D_800FCF90.unk_24 = 0;

    D_800FCFB8.unk_00 = 0;
    D_800FCFB8.unk_1C = 0;

    D_800FCFD8.unk_00 = 0;
    D_800FCFD8.unk_28 = 0;
    D_800FCFD8.unk_04 = 0xFF;

    func_8004ACD0();
    func_8004AC9C();

    D_800FF97C = arg1;
    D_800FF980 = arg2;
    D_800FF980 *= 2;
    if (D_800FF980 >= 0x1141U) {
        D_800FF980 = 0x1140;
    }
    D_800FD6E8 = 2;
}

void func_80049D5C(u16);
s16 func_80049DF0(void);
s16 func_8004A474(void);
s16 func_8004A89C(void);

void func_80049A60(u32 arg0) {
    s32 pad[3];
    s16 sp4C[4];
    u32 i;
    f32 var_fs0;
    s16 var_a0;
    u32 tmp2;
    s32 var_s4;
    s16 tmp;

    var_fs0 = 0.0f;
    var_s4 = 1;
    arg0 >>= 1;

    if ((tmp2 = D_800FD6F4) < D_800FD6F0) {
        if ((0xB80 - (arg0 * 4)) < (D_800FD6F0 - tmp2)) {
            arg0++;
        }
    } else if ((tmp2 - D_800FD6F0) < (arg0 * 4)) {
        arg0++;
    }

    for (i = 0; i < arg0; i++) {
        if (var_fs0 <= i) {
            func_80049D5C(var_s4);
        }

        if (D_800FD008.unk_2C & 0x80) {
            if (D_800FD008.unk_29 != 0) {
                D_800FD6E0 = D_800FD008.unk_28 & 7;
                D_800FD6E1 = (D_800FD008.unk_28 & 0x70) >> 4;
                D_800FD008.unk_29 = 0;
            }

            sp4C[0] = func_80049DF0();
            sp4C[1] = func_8004A474();
            sp4C[3] = func_8004A89C();

            tmp2 = D_800FD008.unk_2A;
            var_a0 = ((u32)((sp4C[0] & ((tmp2 & 1) ? -1 : 0)) + (sp4C[1] & ((tmp2 & 2) ? -1 : 0)) +
                            (sp4C[3] & ((tmp2 & 8) ? -1 : 0))) >>
                      5) *
                     (D_800FD6E0 + 1);
        } else {
            var_a0 = 0;
        }

        tmp2 = D_800FD6F4;
        if (D_800FF97C != 0) {
            if (1) {}
            if (1) {}
            if (1) {}
            if (1) {}
            tmp = (f32)D_800FD6F8[((D_800FF978 - D_800FF980) + 0x1140) % 4416];

            var_a0 += (s16)(((tmp - var_a0) * D_800FF97C) >> 8);
            D_800FD6F8[D_800FF978++] = var_a0;
            if (D_800FF978 >= 0x1140) {
                D_800FF978 -= 0x1140;
            }
        }

        D_800FC6D8[tmp2 + 0] = var_a0;
        D_800FC6D8[D_800FD6F4 + 1] = var_a0;

        D_800FD6F4 += 2;
        if (D_800FD6F4 >= 0xB80) {
            D_800FD6F4 -= 0xB80;
        }

        var_s4++;
        var_fs0 += D_800FD6E4;
    }
}

void func_80049D5C(u16 arg0) {
    while (D_800FD068[D_800FD6A8].unk_06 >= arg0) {
        D_800FD068[D_800FD6A8].unk_00[0] = D_800FD068[D_800FD6A8].unk_04;
        D_800FD068[D_800FD6A8].unk_00[1] = 1;
        D_800FD6A8++;
        if (D_800FD6A8 >= 0xC8) {
            D_800FD6A8 -= 0xC8;
        }
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/4A3E0/func_80049DF0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/4A3E0/func_8004A474.s")

#ifdef NON_MATCHING
// Mostly regalloc differences; also IDO here hoists/CSEs the 0.0f and -1 constants and uses an %lo(at) store
// for unk_0C where the original rematerializes them per use.
typedef struct unk_D_80078A60 {
    /* 0x00 */ u8 unk_00;
    /* 0x04 */ f32 unk_04;
} unk_D_80078A60; // size = 0x8

extern unk_D_80078A60 D_80078A60[8][16];
extern f32 D_8007D4D0;
extern f32 D_8007D4D4;

typedef struct GbSoundReg {
    /* 0x00 */ u8 value;
    /* 0x01 */ u8 dirty;
} GbSoundReg; // size = 0x2

#define GB_SOUND_REGS ((GbSoundReg*)&D_800FD008)
#define GB_REG(offset) (((u8*)&D_800FD008)[offset])

s16 func_8004A89C(void) {
    s32 changed;
    s32 i;
    unk_D_80078A60* entry;
    u8 sample;
    u32 nr;
    u8 idx;
    s32 dir;
    s32 len;
    u32 flags;
    u32 pos;
    s16 value;

    changed = 0;
    for (i = 0x10; i < 0x14; i++) {
        if (GB_SOUND_REGS[i].dirty != 0) {
            changed = 1;
            GB_SOUND_REGS[i].dirty = 0;
        }
    }

    if (changed) {
        idx = GB_REG(0x24);
        entry = &D_80078A60[idx & 7][(u16)((idx & 0xF0) >> 4)];
        sample = entry->unk_00;
        if (sample == 0xFF) {
            D_800FCFD8.unk_28 = 0;
            return 0;
        }
        if (idx & 8) {
            sample += 0x10;
        }
        D_800FCFD8.unk_0C = entry->unk_04;
        if (sample != D_800FCFD8.unk_04) {
            D_800FCFD8.unk_04 = sample;
            func_8004ADB0(D_800FC6CC[D_800FCFD8.unk_04].unk_00, (u32)D_800FC6D0,
                          D_800FC6CC[D_800FCFD8.unk_04].unk_04);
        }

        D_800FCFD8.unk_08 = 0;
        D_800FCFD8.unk_10 = 0.0f;
        nr = GB_REG(0x22);
        dir = nr & 8;
        if (!dir && !(nr & 0xF0)) {
            D_800FCFD8.unk_28 = 0;
            D_800FD008.unk_2C &= ~8;
            return 0;
        }
        if (dir && !(nr & 0xF0) && !(nr & 7)) {
            D_800FCFD8.unk_28 = 0;
            D_800FD008.unk_2C &= ~8;
            return 0;
        }

        flags = GB_REG(0x26);
        if (flags & 0x80) {
            D_800FCFD8.unk_00 = 0;
            D_800FCFD8.unk_28 = 1;
            D_800FCFD8.unk_14 = (nr & 0xF0) * D_8007D4D0;
            len = nr & 7;
            if (len != 0) {
                if (dir) {
                    D_800FCFD8.unk_18 = D_8007D4D0;
                } else {
                    D_800FCFD8.unk_18 = D_8007D4D4;
                }
                pos = len * D_800FD004 * 4;
                D_800FCFD8.unk_1C = pos;
                D_800FCFD8.unk_20 = pos;
            } else {
                D_800FCFD8.unk_1C = -1;
                D_800FCFD8.unk_20 = -1;
                D_800FCFD8.unk_18 = 0.0f;
            }
            if (flags & 0x40) {
                D_800FCFD8.unk_24 = (0x40 - (GB_REG(0x20) & 0x3F)) * D_800FD004;
            } else {
                D_800FCFD8.unk_24 = -1;
            }
            GB_REG(0x26) = flags & ~0x80;
        }
        if (D_800FCFD8.unk_28 == 0) {
            return 0;
        }
    } else if (D_800FCFD8.unk_28 == 0) {
        return 0;
    }

    pos = D_800FCFD8.unk_00;
    if (D_800FCFD8.unk_24 < pos) {
        D_800FCFD8.unk_28 = 0;
        D_800FD008.unk_2C &= ~8;
        return 0;
    }

    if (D_800FCFD8.unk_20 < pos) {
        D_800FCFD8.unk_20 += D_800FCFD8.unk_1C;
        D_800FCFD8.unk_14 += D_800FCFD8.unk_18;
    }

    D_800FCFD8.unk_10 += 1.0f;
    value = ((s16*)D_800FC6D0)[D_800FCFD8.unk_08];
    if (D_800FCFD8.unk_0C <= D_800FCFD8.unk_10) {
        D_800FCFD8.unk_08++;
        D_800FCFD8.unk_10 -= D_800FCFD8.unk_0C;
        if (D_800FCFD8.unk_08 >= (D_800FC6CC[D_800FCFD8.unk_04].unk_04 >> 1)) {
            D_800FCFD8.unk_08 = 0;
        }
    }

    if (!(GB_REG(0x22) & 8) && (D_800FCFD8.unk_14 < 0.0f)) {
        D_800FCFD8.unk_28 = 0;
        return 0;
    }

    if (D_800FCFD8.unk_14 > 0.75f) {
        D_800FCFD8.unk_14 = 0.75f;
        D_800FCFD8.unk_20 = -1;
        D_800FCFD8.unk_18 = 0.0f;
    }

    D_800FCFD8.unk_00 += 0x100;
    return value * D_800FCFD8.unk_14;
}
#else
#pragma GLOBAL_ASM("asm/us/nonmatchings/4A3E0/func_8004A89C.s")
#endif

void func_8004AC9C(void) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(D_800FD6F8); i++) {
        D_800FD6F8[i] = 0;
    }
    D_800FF978 = 0;
}

void func_8004ACD0(void) {
    s32 i;

    for (i = 0; i < 0xB80; i++) {
        D_800FC6D8[i] = 0;
    }
    D_800FD6F0 = 0;
    D_800FD6F4 = 0;
}

void func_8004AD2C(void) {

}
