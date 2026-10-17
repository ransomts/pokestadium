#include "4A3E0.h"
#include "src/4B940.h"
#include "src/373A0.h"

// Game Boy sound registers NR10..NR52 (0xFF10 + index), each a {value, dirty} byte pair.
typedef struct GbSoundReg {
    /* 0x00 */ u8 value;
    /* 0x01 */ u8 dirty;
} GbSoundReg; // size = 0x2

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

// Game Boy sound channel 2 (square) state.
typedef struct unk_D_800FCF90 {
    /* 0x00 */ u32 unk_00; // sample clock
    /* 0x04 */ s16 unk_04; // volume
    /* 0x06 */ s16 unk_06; // volume step
    /* 0x08 */ u32 unk_08; // envelope period
    /* 0x0C */ u32 unk_0C; // next envelope step
    /* 0x10 */ u16 unk_10[2]; // duty half-period lengths
    /* 0x14 */ s16 unk_14;
    /* 0x16 */ u8 unk_16; // duty phase
    /* 0x18 */ u32 unk_18; // next phase flip
    /* 0x1C */ u32 unk_1C; // period
    /* 0x20 */ u32 unk_20; // length end
    /* 0x24 */ u8 unk_24; // active
} unk_D_800FCF90; // size = 0x28

typedef struct unk_D_800FCFB8 {
    /* 0x00 */ u32 unk_00;
    /* 0x04 */ u8 unk04[0x18];
    /* 0x1C */ u8 unk_1C;
} unk_D_800FCFB8; // size = 0x20

// Game Boy sound channel 1 (square with sweep) state.
typedef struct unk_D_800FCF60 {
    /* 0x00 */ u32 unk_00; // sample clock
    /* 0x04 */ u16 unk_04; // frequency
    /* 0x08 */ u32 unk_08; // sweep period
    /* 0x0C */ s16 unk_0C; // volume
    /* 0x0E */ s16 unk_0E; // volume step
    /* 0x10 */ u32 unk_10; // envelope period
    /* 0x14 */ u32 unk_14; // next envelope step
    /* 0x18 */ u16 unk_18[2]; // duty half-period lengths
    /* 0x1C */ s16 unk_1C;
    /* 0x1E */ u8 unk_1E; // duty phase
    /* 0x20 */ u32 unk_20; // next phase flip
    /* 0x24 */ u32 unk_24; // period
    /* 0x28 */ u32 unk_28; // length end
    /* 0x2C */ u8 unk_2C; // active
} unk_D_800FCF60; // size = 0x30

// .bss
unk_D_800FCF60 D_800FCF60;
unk_D_800FCF90 D_800FCF90;
unk_D_800FCFB8 D_800FCFB8;
unk_D_800FCFD8 D_800FCFD8;
u32 D_800FD004;
GbSoundReg D_800FD008[0x20];
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
    D_800FD068[D_800FD6AC].unk_00 = &D_800FD008[(arg0 & 0xFF) - 0x10].value;
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

    p = (u8*) D_800FD008;
    for (i = 0; i < 48; i++) {
       p[i * 2 + 1] = 1;
    }
    p = (u8*) D_800FD008;
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

        if (D_800FD008[0x16].value & 0x80) {
            if (D_800FD008[0x14].dirty != 0) {
                D_800FD6E0 = D_800FD008[0x14].value & 7;
                D_800FD6E1 = (D_800FD008[0x14].value & 0x70) >> 4;
                D_800FD008[0x14].dirty = 0;
            }

            sp4C[0] = func_80049DF0();
            sp4C[1] = func_8004A474();
            sp4C[3] = func_8004A89C();

            tmp2 = D_800FD008[0x15].value;
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

#ifdef NON_MATCHING
// Game Boy sound channel 1 (square wave with frequency sweep), registers NR10-NR14.
// Hand-written (no m2c). Score 1250 over the whole function (diff.py without -s and with func_8004A474 left as
// GLOBAL_ASM; fd.sh's -s stops at the first jr ra; was 3565). Wins: `default:` last with no break,
// one u32 temp for duty / NR12 / NR10 (target t0), `(u8)(nr14 & 7) << 8`, fail-first
// `if (f >= 0x800 || f < 0) goto skip`, `unk_14 = unk_10 = x` (stores 0x10 first) and separate -1 stores
// (keeps -1 in a3). Round 8: the swept frequency is its own s32 local `freq` (sharing nr11 put
// D_800FD004 in t0 and nr11 in v0); BOTH switches written `duty = (D_800FD008[1].value & 0xC0) >> 6`
// with `nr11 = D_800FD008[1].value` (s32) read AFTER it in the trigger: uopt then computes the sweep
// switch value in each predecessor like the target (3565 -> 2530). `unk_0C = ((u8)duty & 0xF0) << 7` (the
// cast's andi 0xFF is folded by as1 but consumes a temp: the whole trigger block now matches, incl. the old
// stray `move t7,a0`; same trick as func_8004A474) and `(unk_04 >> shift) + unk_04` (addu order): 1520.
// `skip: changed = NR12 & 8` (the loop flag reused; tested `!changed`): NR12 is now loaded in place with its
// lui hoisted into the decrement path like the target, and unk_14/unk_20/phase/value regs match (1250).
// Other locals for it: dir 1520, nr12 1520, duty 1820, nr11 1855, nr14 1900, freq 2225, i 6630.
// Remaining: the sweep switch value lands in a0 (target t0, which it was before the (u8) cast); at skip the
// NR12 load is a1 and `& 8` goes to v0 (target: both t2, the trigger dir's register). Older notes: the `goto skip` path loads NR12 via v0 and puts dir in
// a1 (target: dir in t2 loaded in place, lui t2 hoisted into the decrement path), phase a2 vs a1, unk_14
// a2 vs v0. Dead ends: pos as direct field reads everywhere (worse), u32<->s32 field types (no change),
// explicit casts (u16)/(s32) on the freq high bits, other spellings of the NR13|NR14 expression
// ((u16), (s32), *256, unk_04 + ..., u8 nr14), freq stored in i/changed (worse) or dir (3195 at the time,
// breaks the loop pointer regs), nr11 u32 (3040) / u8 / u16 (2640), switch on the expression without
// duty, `duty = NR11; duty = ...`, NR12&8 at skip: into nr12/duty/freq/nr11 or inline (all worse),
// `dir = NR12; dir &= 8` (no change).
s16 func_80049DF0(void) {
    s32 changed;
    s32 i;
    u32 nr14;
    u32 nr12;
    s32 nr11;
    s32 freq;
    u32 duty;
    u8 phase;
    u32 pos;
    s32 dir;
    s16 value;

    changed = 0;
    for (i = 0; i < 5; i++) {
        if (D_800FD008[i].dirty != 0) {
            changed = 1;
            D_800FD008[i].dirty = 0;
        }
    }

    if (changed) {
        nr14 = D_800FD008[4].value;
        D_800FCF60.unk_04 = D_800FD008[3].value | ((u8)(nr14 & 7) << 8);
        D_800FCF60.unk_24 = ((0x800 - D_800FCF60.unk_04) * D_800FD004) >> 11;
        duty = (D_800FD008[1].value & 0xC0) >> 6;
        nr11 = D_800FD008[1].value;
        switch (duty) {
            case 0:
                D_800FCF60.unk_18[1] = D_800FCF60.unk_24 >> 3;
                if (D_800FCF60.unk_18[1] < 0x40) {
                    D_800FCF60.unk_18[1] = 0x40;
                }
                D_800FCF60.unk_18[0] = D_800FCF60.unk_24 - D_800FCF60.unk_18[1];
                phase = 1;
                break;
            case 1:
                D_800FCF60.unk_18[1] = D_800FCF60.unk_24 >> 2;
                if (D_800FCF60.unk_18[1] < 0x40) {
                    D_800FCF60.unk_18[1] = 0x40;
                }
                D_800FCF60.unk_18[0] = D_800FCF60.unk_24 - D_800FCF60.unk_18[1];
                phase = 0;
                break;
            case 2:
                D_800FCF60.unk_18[1] = D_800FCF60.unk_24 >> 1;
                if (D_800FCF60.unk_18[1] < 0x40) {
                    D_800FCF60.unk_18[1] = 0x40;
                }
                D_800FCF60.unk_18[0] = D_800FCF60.unk_24 - D_800FCF60.unk_18[1];
                phase = 0;
                break;
            case 3:
                D_800FCF60.unk_18[0] = D_800FCF60.unk_24 >> 2;
                if (D_800FCF60.unk_18[0] < 0x40) {
                    D_800FCF60.unk_18[0] = 0x40;
                }
                D_800FCF60.unk_18[1] = D_800FCF60.unk_24 - D_800FCF60.unk_18[0];
                phase = 1;
                break;
            default:
                D_800FCF60.unk_18[1] = 0;
                D_800FCF60.unk_18[0] = D_800FCF60.unk_24;
                phase = 1;
        }

        duty = D_800FD008[2].value;
        dir = duty & 8;
        if (!dir && !(duty & 0xF0)) {
            D_800FCF60.unk_2C = 0;
            D_800FD008[0x16].value &= ~1;
            return 0;
        }
        if (dir && !(duty & 0xF0) && !(duty & 7)) {
            D_800FCF60.unk_2C = 0;
            D_800FD008[0x16].value &= ~1;
            return 0;
        }

        if (nr14 & 0x80) {
            D_800FCF60.unk_00 = 0;
            D_800FCF60.unk_2C = 1;
            D_800FCF60.unk_1E = phase;
            D_800FCF60.unk_1C = 0;
            D_800FCF60.unk_20 = 0;
            D_800FCF60.unk_0C = ((u8)duty & 0xF0) << 7;
            if (duty & 7) {
                if (dir) {
                    D_800FCF60.unk_0E = 0x800;
                } else {
                    D_800FCF60.unk_0E = -0x800;
                }
                D_800FCF60.unk_14 = D_800FCF60.unk_10 = (duty & 7) * D_800FD004;
            } else {
                D_800FCF60.unk_0E = 0;
                D_800FCF60.unk_10 = -1;
                D_800FCF60.unk_14 = -1;
            }
            D_800FCF60.unk_08 = (((D_800FD008[0].value & 0x70) >> 4) * D_800FD004) >> 1;
            if (D_800FCF60.unk_08 == 0) {
                D_800FCF60.unk_08 = -1;
            }
            if (nr14 & 0x40) {
                D_800FCF60.unk_28 = ((0x40 - (nr11 & 0x3F)) * D_800FD004) >> 2;
            } else {
                D_800FCF60.unk_28 = -1;
            }
            D_800FD008[4].value = nr14 & ~0x80;
        }
        if (D_800FCF60.unk_2C == 0) {
            return 0;
        }
    } else if (D_800FCF60.unk_2C == 0) {
        return 0;
    }

    if (D_800FCF60.unk_28 < D_800FCF60.unk_00) {
        D_800FCF60.unk_2C = 0;
        D_800FD008[0x16].value &= ~1;
        return 0;
    }

    if ((D_800FCF60.unk_08 - (D_800FCF60.unk_00 % D_800FCF60.unk_08)) <= 0x40) {
        duty = D_800FD008[0].value;
        if (!(duty & 8)) {
            freq = (u16)((D_800FCF60.unk_04 >> (duty & 7)) + D_800FCF60.unk_04);
            if (freq >= 0x800) {
                D_800FCF60.unk_2C = 0;
                D_800FD008[0x16].value &= ~1;
                return 0;
            }
            D_800FCF60.unk_04 = freq;
        } else {
            freq = (u16)(D_800FCF60.unk_04 - (D_800FCF60.unk_04 >> (duty & 7)));
            if (freq >= 0x800 || freq < 0) {
                goto skip;
            } else {
                D_800FCF60.unk_04 = freq;
            }
        }
        D_800FCF60.unk_24 = ((0x800 - D_800FCF60.unk_04) * D_800FD004) >> 11;
        duty = (D_800FD008[1].value & 0xC0) >> 6;
        switch (duty) {
            case 0:
                D_800FCF60.unk_18[1] = D_800FCF60.unk_24 >> 3;
                if (D_800FCF60.unk_18[1] < 0x40) {
                    D_800FCF60.unk_18[1] = 0x40;
                }
                D_800FCF60.unk_18[0] = D_800FCF60.unk_24 - D_800FCF60.unk_18[1];
                break;
            case 1:
                D_800FCF60.unk_18[1] = D_800FCF60.unk_24 >> 2;
                if (D_800FCF60.unk_18[1] < 0x40) {
                    D_800FCF60.unk_18[1] = 0x40;
                }
                D_800FCF60.unk_18[0] = D_800FCF60.unk_24 - D_800FCF60.unk_18[1];
                break;
            case 2:
                D_800FCF60.unk_18[1] = D_800FCF60.unk_24 >> 1;
                if (D_800FCF60.unk_18[1] < 0x40) {
                    D_800FCF60.unk_18[1] = 0x40;
                }
                D_800FCF60.unk_18[0] = D_800FCF60.unk_24 - D_800FCF60.unk_18[1];
                break;
            case 3:
                D_800FCF60.unk_18[0] = D_800FCF60.unk_24 >> 2;
                if (D_800FCF60.unk_18[0] < 0x40) {
                    D_800FCF60.unk_18[0] = 0x40;
                }
                D_800FCF60.unk_18[1] = D_800FCF60.unk_24 - D_800FCF60.unk_18[0];
                break;
            default:
                D_800FCF60.unk_18[1] = 0;
                D_800FCF60.unk_18[0] = D_800FCF60.unk_24;
        }
    }
skip:
    changed = D_800FD008[2].value & 8;
    if (D_800FCF60.unk_14 < D_800FCF60.unk_00) {
        D_800FCF60.unk_0C += D_800FCF60.unk_0E;
        D_800FCF60.unk_14 += D_800FCF60.unk_10;
    }
    while (D_800FCF60.unk_20 < D_800FCF60.unk_00) {
        D_800FCF60.unk_1E ^= 1;
        D_800FCF60.unk_20 += D_800FCF60.unk_18[D_800FCF60.unk_1E];
    }

    if (!changed && (D_800FCF60.unk_0C < 0)) {
        D_800FCF60.unk_2C = 0;
        return 0;
    }

    if ((u16)D_800FCF60.unk_0C > 0x7800) {
        D_800FCF60.unk_0C = 0x7800;
        D_800FCF60.unk_0E = 0;
        D_800FCF60.unk_14 = -1;
    }

    value = D_800FCF60.unk_0C;
    if (D_800FCF60.unk_1E == 0) {
        value = -value;
    }
    D_800FCF60.unk_00 = D_800FCF60.unk_00 + 0x40;
    return value;
}
#else
#pragma GLOBAL_ASM("asm/us/nonmatchings/4A3E0/func_80049DF0.s")
#endif

#ifdef NON_MATCHING
// Game Boy sound channel 2 (square wave), registers NR21-NR24. Same shape as func_80049DF0 minus the sweep.
// Hand-written (no m2c). Score 540 over the whole function (diff.py without -s, func_80049DF0 as GLOBAL_ASM;
// fd.sh -s and ido_bisect both report 0 because they stop at the first jr ra; was 1420). Wins:
// `(u8)(nr24 & 7) << 8`, NR21 read twice (no local) so duty lives in a2 and NR21 in a3; round 8: NR22 & 8
// read inline in the final `!(NR22 & 8) && unk_04 < 0` test (no dir local in the tail) -> fresh lui load
// hoisted to the right block like the target (1420 -> 980); `((u8)duty & 0xF0) << 7` for unk_04: the cast's
// andi 0xFF is folded away by as1 but still consumes the temp register, which realigns every t-register
// of the trigger block with the target (980 -> 690; the trigger block now matches). Then the tail
// `duty = NR22 & 8` before the unk_0C test, tested as `!duty`: every tail register except that one now
// matches (690 -> 670). Better: `changed = NR22 & 8` AFTER the env-step if, just before the while (the
// loop flag reused; tested `!changed`): uopt hoists the NR22 load with a fresh lui up to the unk_0C test
// block like the target (670 -> 540). Same spot with duty/dir/nr24: 640, nr21 4545; at the final test
// instead: 1000-1040.
// Remaining (540): the hoisted load lands in a0 and the `& 8` stays in the loop-guard block into v0
// (target: load and andi both in t1 inside the unk_0C test block). Older notes:
// Remaining: that tail value lives in a2 and is loaded via the a0 base (target: fresh lui into t1, the
// trigger dir's register; bnezl t1 at the final test). A new local or `dir` there gives 790-1420 (it then
// takes v0 and shifts unk_0C/phase/value); the inline `!(NR22 & 8)` (690) gets the fresh lui but leaves the
// andi at the use. nr21/nr24/changed/i/phase for that value: 790-5265.
// Dead ends: explicit 4 if-statements for the dirty flags (4685), duty s32, nr21 u32, decl reordering;
// NR22&8 into dir before/after the unk_0C test or before the while (1000-1420, a0-based load), `dir = NR22`
// + `dir & 8` (1755), u8/u32/s16/u16 dir, `(x & 8) != 0`, both dir and inline NR22 test (1900);
// deleting trigger stores; `(u8)`/`(s32)` casts or a dir local with casts on the tail NR22 read (690-1275);
// kill-path spellings (`= x & ~2`, `&= 0xFD`, u8* access, store order: no change); `register` dir.
s16 func_8004A474(void) {
    s32 changed;
    s32 i;
    u32 nr24;
    u32 duty;
    s32 nr21;
    u8 phase;
    u32 pos;
    s32 dir;
    s16 value;

    changed = 0;
    for (i = 6; i < 10; i++) {
        if (D_800FD008[i].dirty != 0) {
            changed = 1;
            D_800FD008[i].dirty = 0;
        }
    }

    if (changed) {
        nr24 = D_800FD008[9].value;
        D_800FCF90.unk_1C = ((0x800 - (D_800FD008[8].value | ((u8)(nr24 & 7) << 8))) * D_800FD004) >> 11;
        duty = (D_800FD008[6].value & 0xC0) >> 6;
        switch (duty) {
            case 0:
                D_800FCF90.unk_10[1] = D_800FCF90.unk_1C >> 3;
                if (D_800FCF90.unk_10[1] < 0x40) {
                    D_800FCF90.unk_10[1] = 0x40;
                }
                D_800FCF90.unk_10[0] = D_800FCF90.unk_1C - D_800FCF90.unk_10[1];
                phase = 1;
                break;
            case 1:
                D_800FCF90.unk_10[1] = D_800FCF90.unk_1C >> 2;
                if (D_800FCF90.unk_10[1] < 0x40) {
                    D_800FCF90.unk_10[1] = 0x40;
                }
                D_800FCF90.unk_10[0] = D_800FCF90.unk_1C - D_800FCF90.unk_10[1];
                phase = 0;
                break;
            case 2:
                D_800FCF90.unk_10[1] = D_800FCF90.unk_1C >> 1;
                if (D_800FCF90.unk_10[1] < 0x40) {
                    D_800FCF90.unk_10[1] = 0x40;
                }
                D_800FCF90.unk_10[0] = D_800FCF90.unk_1C - D_800FCF90.unk_10[1];
                phase = 0;
                break;
            case 3:
                D_800FCF90.unk_10[0] = D_800FCF90.unk_1C >> 2;
                if (D_800FCF90.unk_10[0] < 0x40) {
                    D_800FCF90.unk_10[0] = 0x40;
                }
                D_800FCF90.unk_10[1] = D_800FCF90.unk_1C - D_800FCF90.unk_10[0];
                phase = 1;
                break;
            default:
                D_800FCF90.unk_10[1] = 0;
                D_800FCF90.unk_10[0] = D_800FCF90.unk_1C;
                phase = 1;
        }

        duty = D_800FD008[7].value;
        dir = duty & 8;
        if (!dir && !(duty & 0xF0)) {
            D_800FCF90.unk_24 = 0;
            D_800FD008[0x16].value &= ~2;
            return 0;
        }
        if (dir && !(duty & 0xF0) && !(duty & 7)) {
            D_800FCF90.unk_24 = 0;
            D_800FD008[0x16].value &= ~2;
            return 0;
        }

        if (nr24 & 0x80) {
            D_800FCF90.unk_00 = 0;
            D_800FCF90.unk_24 = 1;
            D_800FCF90.unk_16 = phase;
            D_800FCF90.unk_14 = 0;
            D_800FCF90.unk_18 = 0;
            D_800FCF90.unk_04 = ((u8)duty & 0xF0) << 7;
            if (duty & 7) {
                if (dir) {
                    D_800FCF90.unk_06 = 0x800;
                } else {
                    D_800FCF90.unk_06 = -0x800;
                }
                D_800FCF90.unk_0C = D_800FCF90.unk_08 = (duty & 7) * D_800FD004;
            } else {
                D_800FCF90.unk_06 = 0;
                D_800FCF90.unk_08 = -1;
                D_800FCF90.unk_0C = -1;
            }
            if (nr24 & 0x40) {
                D_800FCF90.unk_20 = ((0x40 - (D_800FD008[6].value & 0x3F)) * D_800FD004) >> 2;
            } else {
                D_800FCF90.unk_20 = -1;
            }
            D_800FD008[9].value = nr24 & ~0x80;
        }
        if (D_800FCF90.unk_24 == 0) {
            return 0;
        }
    } else if (D_800FCF90.unk_24 == 0) {
        return 0;
    }

    pos = D_800FCF90.unk_00;
    if (D_800FCF90.unk_20 < pos) {
        D_800FCF90.unk_24 = 0;
        D_800FD008[0x16].value &= ~2;
        return 0;
    }

    if (D_800FCF90.unk_0C < pos) {
        D_800FCF90.unk_04 += D_800FCF90.unk_06;
        D_800FCF90.unk_0C += D_800FCF90.unk_08;
    }
    changed = D_800FD008[7].value & 8;
    while (D_800FCF90.unk_18 <= pos) {
        D_800FCF90.unk_16 ^= 1;
        D_800FCF90.unk_18 += D_800FCF90.unk_10[D_800FCF90.unk_16];
    }

    if (!changed && (D_800FCF90.unk_04 < 0)) {
        D_800FCF90.unk_24 = 0;
        return 0;
    }

    if ((u16)D_800FCF90.unk_04 > 0x7800) {
        D_800FCF90.unk_04 = 0x7800;
        D_800FCF90.unk_06 = 0;
        D_800FCF90.unk_0C = -1;
    }

    value = D_800FCF90.unk_04;
    if (D_800FCF90.unk_16 == 0) {
        value = -value;
    }
    D_800FCF90.unk_00 = pos + 0x40;
    return value;
}
#else
#pragma GLOBAL_ASM("asm/us/nonmatchings/4A3E0/func_8004A474.s")
#endif

typedef struct unk_D_80078A60 {
    /* 0x00 */ u8 unk_00;
    /* 0x04 */ f32 unk_04;
} unk_D_80078A60; // size = 0x8

unk_D_80078A60 D_80078A60[8][16] = { { { 0, 1.0f }, { 1, 1.0f }, { 2, 1.0f }, { 3, 1.0f }, { 4, 1.0f }, { 5, 1.0f }, { 6, 1.0f }, { 7, 1.0f }, { 8, 1.0f }, { 9, 1.0f }, { 0xA, 1.0f }, { 0xB, 1.0f }, { 0xC, 1.0f }, { 0xD, 1.0f }, { 0xFF, 1.0f }, { 0xFF, 1.0f } }, { { 1, 1.0f }, { 2, 1.0f }, { 3, 1.0f }, { 4, 1.0f }, { 5, 1.0f }, { 6, 1.0f }, { 7, 1.0f }, { 8, 1.0f }, { 9, 1.0f }, { 0xA, 1.0f }, { 0xB, 1.0f }, { 0xC, 1.0f }, { 0xD, 1.0f }, { 0xD, 2.0f }, { 0xFF, 1.0f }, { 0xFF, 1.0f } }, { { 2, 1.0f }, { 3, 1.0f }, { 4, 1.0f }, { 5, 1.0f }, { 6, 1.0f }, { 7, 1.0f }, { 8, 1.0f }, { 9, 1.0f }, { 0xA, 1.0f }, { 0xB, 1.0f }, { 0xC, 1.0f }, { 0xD, 1.0f }, { 0xD, 2.0f }, { 0xD, 4.0f }, { 0xFF, 1.0f }, { 0xFF, 1.0f } }, { { 2, 1.5f }, { 3, 1.5f }, { 4, 1.5f }, { 5, 1.5f }, { 6, 1.5f }, { 7, 1.5f }, { 8, 1.5f }, { 9, 1.5f }, { 0xA, 1.5f }, { 0xB, 1.5f }, { 0xC, 1.5f }, { 0xD, 1.5f }, { 0xD, 3.0f }, { 0xD, 6.0f }, { 0xFF, 1.0f }, { 0xFF, 1.0f } }, { { 3, 1.0f }, { 4, 1.0f }, { 5, 1.0f }, { 6, 1.0f }, { 7, 1.0f }, { 8, 1.0f }, { 9, 1.0f }, { 0xA, 1.0f }, { 0xB, 1.0f }, { 0xC, 1.0f }, { 0xD, 1.0f }, { 0xD, 2.0f }, { 0xD, 4.0f }, { 0xD, 8.0f }, { 0xFF, 1.0f }, { 0xFF, 1.0f } }, { { 3, 1.25f }, { 4, 1.25f }, { 5, 1.25f }, { 6, 1.25f }, { 7, 1.25f }, { 8, 1.25f }, { 9, 1.25f }, { 0xA, 1.25f }, { 0xB, 1.25f }, { 0xC, 1.25f }, { 0xD, 1.25f }, { 0xD, 2.5f }, { 0xD, 5.0f }, { 0xD, 10.0f }, { 0xFF, 1.0f }, { 0xFF, 1.0f } }, { { 3, 1.5f }, { 4, 1.5f }, { 5, 1.5f }, { 6, 1.5f }, { 7, 1.5f }, { 8, 1.5f }, { 9, 1.5f }, { 0xA, 1.5f }, { 0xB, 1.5f }, { 0xC, 1.5f }, { 0xD, 1.5f }, { 0xD, 3.0f }, { 0xD, 6.0f }, { 0xD, 12.0f }, { 0xFF, 1.0f }, { 0xFF, 1.0f } }, { { 3, 1.75f }, { 4, 1.75f }, { 5, 1.75f }, { 6, 1.75f }, { 7, 1.75f }, { 8, 1.75f }, { 9, 1.75f }, { 0xA, 1.75f }, { 0xB, 1.75f }, { 0xC, 1.75f }, { 0xD, 1.75f }, { 0xD, 3.5f }, { 0xD, 7.0f }, { 0xD, 14.0f }, { 0xFF, 1.0f }, { 0xFF, 1.0f } } };
#ifdef NON_MATCHING
// Score 2000 (diff.py without -s; was 3355, 5415). Wins: clamp stores in 14/18/20 order (2195 -> 2000); `unk_10 = 0` (int literal) stops IDO sharing one
// 0.0f register across the function; table row read TWICE as D_80078A60[..][..].unk_00 / .unk_04 (no entry
// pointer) puts the unk_0C store in the beq delay slot with 0xc(v1) addressing (3215 -> 2195);
// `unk_20 = unk_1C = len*D_800FD004*4` (no pos temp; 0x1C stored first like the target); `sample = unk_04`
// before the unk_20 test, NR42&8 read inline in the final test (fresh lui like the target), ent2 taken
// BEFORE the value load, `value = value * unk_14; return value;` (trunc result in a0 like the target).
// Remaining (mostly regalloc): target keeps idx in a1, (u16)col in a2 (computed in place), row ptr in a3,
// sample in a0 (v0 copy); NR42&8 andi sits in the unk_20 beqz delay slot (ours is late); pos split into
// v0 in the unk_24 test (target reloads unk_20 into v0 in a beqzl slot); li 1 / D_8007D4D0 order.
// Dead ends (all worse or equal): other 0/0.0f literal mixes, nr as full byte or `dir`, NR42 read before
// pos, u8* access, &= 0xF7, ternary +0x10, comma-expr unk_0C, D_800FC6CC[sample] in the call (2865 but
// loses the target's andi 0xFF re-read), entry pointer variable, u16/s32 `col` local (back to 2985),
// NR42&8 into any local (dir/idx/len/i/nr/flags, before or after the unk_20 test: 3235+), idx re-read
// from D_800FD008 instead of a local, reusing idx for dir / sample for len, s32/u16 value/sample/idx,
// declaration order (no effect), chained 0x20-first store; single (u8) casts on idx/nr/flags/len/dir uses
// (best 2110 = (u8)flags or (u8)nr in the kill tests, before the clamp fix; pairs of them are worse).

extern unk_D_80078A60 D_80078A60[8][16];
extern f32 D_8007D4D0;
extern f32 D_8007D4D4;

s16 func_8004A89C(void) {
    s32 changed;
    s32 i;
    unk_D_800FC6CC* ent2;
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
        if (D_800FD008[i].dirty != 0) {
            changed = 1;
            D_800FD008[i].dirty = 0;
        }
    }

    if (changed) {
        idx = D_800FD008[0x12].value;
        sample = D_80078A60[idx & 7][(u16)((idx & 0xF0) >> 4)].unk_00;
        if (sample == 0xFF) {
            D_800FCFD8.unk_28 = 0;
            return 0;
        }
        if (idx & 8) {
            sample += 0x10;
        }
        D_800FCFD8.unk_0C = D_80078A60[idx & 7][(u16)((idx & 0xF0) >> 4)].unk_04;
        if (sample != D_800FCFD8.unk_04) {
            D_800FCFD8.unk_04 = sample;
            func_8004ADB0(D_800FC6CC[D_800FCFD8.unk_04].unk_00, (u32)D_800FC6D0,
                          D_800FC6CC[D_800FCFD8.unk_04].unk_04);
        }

        D_800FCFD8.unk_08 = 0;
        D_800FCFD8.unk_10 = 0;
        nr = D_800FD008[0x11].value;
        dir = nr & 8;
        if (!dir && !(nr & 0xF0)) {
            D_800FCFD8.unk_28 = 0;
            D_800FD008[0x16].value &= ~8;
            return 0;
        }
        if (dir && !(nr & 0xF0) && !(nr & 7)) {
            D_800FCFD8.unk_28 = 0;
            D_800FD008[0x16].value &= ~8;
            return 0;
        }

        flags = D_800FD008[0x13].value;
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
                D_800FCFD8.unk_20 = D_800FCFD8.unk_1C = len * D_800FD004 * 4;
            } else {
                D_800FCFD8.unk_1C = -1;
                D_800FCFD8.unk_20 = -1;
                D_800FCFD8.unk_18 = 0.0f;
            }
            if (flags & 0x40) {
                D_800FCFD8.unk_24 = (0x40 - (D_800FD008[0x10].value & 0x3F)) * D_800FD004;
            } else {
                D_800FCFD8.unk_24 = -1;
            }
            D_800FD008[0x13].value = flags & ~0x80;
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
        D_800FD008[0x16].value &= ~8;
        return 0;
    }

    sample = D_800FCFD8.unk_04;
    if (D_800FCFD8.unk_20 < pos) {
        D_800FCFD8.unk_20 += D_800FCFD8.unk_1C;
        D_800FCFD8.unk_14 += D_800FCFD8.unk_18;
    }

    ent2 = &D_800FC6CC[sample];
    value = ((s16*)D_800FC6D0)[D_800FCFD8.unk_08];
    D_800FCFD8.unk_10 += 1.0f;
    if (D_800FCFD8.unk_0C <= D_800FCFD8.unk_10) {
        D_800FCFD8.unk_08++;
        D_800FCFD8.unk_10 -= D_800FCFD8.unk_0C;
        if (D_800FCFD8.unk_08 >= (ent2->unk_04 >> 1)) {
            D_800FCFD8.unk_08 = 0;
        }
    }

    if (!(D_800FD008[0x11].value & 8) && (D_800FCFD8.unk_14 < 0.0f)) {
        D_800FCFD8.unk_28 = 0;
        return 0;
    }

    if (D_800FCFD8.unk_14 > 0.75f) {
        D_800FCFD8.unk_14 = 0.75f;
        D_800FCFD8.unk_18 = 0.0f;
        D_800FCFD8.unk_20 = -1;
    }

    D_800FCFD8.unk_00 += 0x100;
    value = value * D_800FCFD8.unk_14;
    return value;
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
