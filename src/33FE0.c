#include "global.h"
#include "33FE0.h"
#include "12D80.h"
#include "32D10.h"
#include "memmap.h"

// .data
s16 D_800763B0[0x102] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4,
    5, 5, 5, 6, 6, 6, 7, 7, 7, 8, 8, 8, 9, 9, 9, 10,
    10, 10, 11, 11, 11, 12, 12, 12, 13, 13, 13, 14, 14, 14, 15, 15,
    15, 0, 0, 0, 1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4,
    5, 5, 5, 6, 6, 6, 7, 7, 7, 8, 8, 8, 9, 9, 9, 10,
    10, 10, 11, 11, 11, 12, 12, 12, 13, 13, 13, 14, 14, 14, 15, 15,
    15, 0, 0, 0, 1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4,
    5, 5, 5, 6, 6, 6, 7, 7, 7, 8, 8, 8, 9, 9, 9, 10,
    10, 10, 11, 11, 11, 12, 12, 12, 13, 13, 13, 14, 14, 14, 15, 15,
    15, 0, 0, 0, 1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4,
    5, 5, 5, 6, 6, 6, 7, 7, 7, 8, 8, 8, 9, 9, 9, 10,
    10, 10, 11, 11, 11, 12, 12, 12, 13, 13, 13, 14, 14, 14, 15, 15,
    15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0,
};

s16 D_800765B4[0x102] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3,
    1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3, 1,
    2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2,
    3, 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3,
    1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3, 1,
    2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2,
    3, 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3,
    1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3, 1,
    2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2,
    3, 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3,
    1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3, 1,
    2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2,
    3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0,
};

s16 D_800767B8[0x102] = {
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
    16, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0,
};

s16 D_800769BC[0x102] = {
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0,
};

s16 D_80076BC0[0x102] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
    16, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0,
};

s16 D_80076DC4[0x102] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
    16, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0,
};

s16 D_80076FC8[0x102] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
    16, 0,
};

s16 D_800771CC[0x102] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0,
};

s16 D_800773D0[0x102] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0,
};

f32 D_800775D4[16] = {
    0.7f, 0.48999998f, 0.343f, 0.2401f,
    0.16806999f, 0.11764899f, 0.08235429f, 0.057648003f,
    0.0403536f, 0.02824752f, 0.019773263f, 0.013841284f,
    0.009688899f, 0.006782229f, 0.0047475602f, 0.0033232921f,
};

// .bss
Vec3fCounter* D_800B2F50;
PosBlend D_800B2F58[0x10];
Mtx D_800B3258;

s32 func_800333E0(s32 arg0) {
    u8 stack[4];
    u8* ptr = stack;

    return ((u8*)((s32)ptr + (arg0 * 0x94)) - ptr) + 0x170;
}

s32 func_80033410(s32 arg0) {
    u8 stack[4];
    u8* ptr = stack;

    return ((u8*)(s32)ptr + (arg0 * 0x10)) - ptr;
}

f32 func_8003342C(f32 value) {
    if (value < 0.0f) {
        value = -value;
    }
    return value;
}

void func_80033450(f32 ax, f32 ay, f32 az, f32 bx, f32 by, f32 bz, f32* cx, f32* cy, f32* cz) {
    *cx = (ay * bz) - (az * by);
    *cy = (az * bx) - (ax * bz);
    *cz = (ax * by) - (ay * bx);
}

f32 func_800334C0(
    f32 px, f32 py, f32 pz,
    f32 ax, f32 ay, f32 az,
    f32 bx, f32 by, f32 bz
) {
    f32 dot;
    f32 dx;
    f32 dy;
    f32 dz;
    f32 lenSq;

    lenSq = ((bx - ax) * (bx - ax)) + ((by - ay) * (by - ay)) + ((bz - az) * (bz - az));

    if (lenSq == 0.0f) {
        return 0.0f;
    }

    dot = (((bx - ax) * (px - ax))
        + ((by - ay) * (py - ay))
        + ((bz - az) * (pz - az))) / lenSq;

    return dot;
}

f32 func_80033568(
    f32 px, f32 py, f32 pz,
    f32 ax, f32 ay, f32 az,
    f32 bx, f32 by, f32 bz,
    f32* outX, f32* outY, f32* outZ
) {
    f32 dx;
    f32 dy;
    f32 dz;
    f32 sp68;
    f32 t;
    f32 ex;
    f32 ey;
    f32 ez;
    f32 dx2;
    f32 pad[1];
    f32 lenSq;

    lenSq = SQ(bx - ax) + SQ(by - ay) + SQ(bz - az);
    if (lenSq == 0.0f) {
        return -1.0f;
    }
    dx = bx - ax;
    dy = by - ay;
    dz = bz - az;
    dx2 = px - ax;

    sp68 = t = ((dx * dx2) + (dy * (py - ay)) + (dz * (pz - az))) / lenSq;
    if (t < -0.5f || t > 1.5f) {
        return -2.0f;
    }
    *outX = ex = ax + (sp68 * dx);
    *outY = ey = ay + (sp68 * dy);
    *outZ = ez = az + (sp68 * dz);

    return sqrtf(SQ(ex - px) + SQ(ey - py) + SQ(ez - pz));
}

s16 func_800336F8(s16* table, s32 index) {
    s16 temp;
    s16 slot = table[index];
    
    temp = D_800769BC[slot];
    if (temp > 0) {
        return 0;
    }
    temp = D_800767B8[slot];
    if (temp > 0) {
        return 1;
    }
    temp = D_80076BC0[slot];
    if (temp > 0) {
        return 2;
    }
    temp = D_80076DC4[slot];
    if (temp > 0) {
        return 3;
    }
    temp = D_80076FC8[slot];
    if (temp > 0) {
        return 4;
    }
    temp = D_800771CC[slot];
    if (temp > 0) {
        return 5;
    }
    temp = D_800773D0[slot];
    if (temp > 0) {
        return 6;
    }
    return slot;
}

s16 func_800337D8(s16* arg0, s32 arg1) {
    s16 temp_v0;
    s16 temp_v1;

    temp_v0 = arg0[arg1];
    temp_v1 = D_800765B4[temp_v0];

    if (temp_v1 > 0) {
        return temp_v1;
    }

    return 0;
}

s16 func_80033810(s16* arg0, s32 arg1) {
    s16 temp_v1;
    s16 temp_a2;
    temp_v1 = *(arg0 + arg1);
    temp_a2 = D_800763B0[temp_v1];
    return temp_a2;
}

s16 func_80033830(s16* arg0, s32 arg1) {
    s16 temp_v1;
    s16 temp_a2;
    temp_v1 = *(arg0 + arg1);
    temp_a2 = D_800767B8[temp_v1];
    return temp_a2;
}

s16 func_80033850(s16* arg0, s32 arg1) {
    s16 temp_v1;
    s16 temp_a2;
    temp_v1 = *(arg0 + arg1);
    temp_a2 = D_80076BC0[temp_v1];
    return temp_a2;
}

s16 func_80033870(s16* arg0, s32 arg1) {
    s16 temp_v1;
    s16 temp_a2;
    temp_v1 = *(arg0 + arg1);
    temp_a2 = D_80076DC4[temp_v1];
    return temp_a2;
}

s16 func_80033890(s16* arg0, s32 arg1) {
    s16 temp_v1;
    s16 temp_a2;
    temp_v1 = *(arg0 + arg1);
    temp_a2 = D_80076FC8[temp_v1];
    return temp_a2;
}

void func_800338B0(void) {

}

s16 func_800338B8(s16* arg0, s32 arg1) {
    s16 temp_v1;
    s16 temp_a2;
    temp_v1 = *(arg0 + arg1);
    temp_a2 = D_800773D0[temp_v1];
    return temp_a2;
}

void func_800338D8(StadiumModel* model, MtxF* mtx) {
    ModelSegment* segment;
    ModelVertex* base;
    ModelVertex* mvtx;
    Vtx* vtx;
    s16* indexTable;
    s16 temp_t0;
    s16 temp_v0_2;
    s16 var_a1;
    s16* temp_s2;
    s32 i;
    s32 var_a0;
    s32 var_s3;
    UNUSED s32 pad[8];

    segment = Memmap_GetSegmentVaddr(model->modelSegment);
    base = &model->mvtx;
    mvtx = base;
    vtx = Memmap_GetSegmentVaddr(segment->vertexSegment);

    for (var_a0 = 0; var_a0 < segment->vertexCount; var_a0++) {

        mvtx->position.base.x = (f32)vtx->v.ob[0];
        mvtx->position.base.y = (f32)vtx->v.ob[1];
        mvtx->position.base.z = (f32)vtx->v.ob[2];
        mvtx->position.color.r = (s8)vtx->v.cn[0];
        mvtx->position.color.g = (s8)vtx->v.cn[1];
        mvtx->position.color.b = (s8)vtx->v.cn[2];
        mvtx->position.texS = vtx->v.tc[0];
        mvtx->position.texT = vtx->v.tc[1];
        mvtx->position.alpha = vtx->v.cn[3];
        mvtx->position.offset.x = 0.0f;
        mvtx->position.offset.y = 0.0f;
        mvtx->position.offset.z = 0.0f;
        mvtx->position.disabled = 0;
        mvtx->position.drawGroup = 0;
        mvtx++;
        vtx++;
    }

    mvtx = base;
    func_800350E4(segment, mtx, base);

    var_s3 = 0;
    i = 0;
    while (var_s3 < 0x10) {
        temp_s2 = Memmap_GetSegmentVaddr(segment->tableSegment);
        for (i = 0; i < segment->vertexCount; i++) {
            u16 temp_v0 = func_80033810(temp_s2, i);
            if (var_s3 == temp_v0) {
                mvtx->jointIndex = i;
                mvtx++;
            }
        }
        var_s3++;
    }

    mvtx = base;
    var_a1 = 0;
    indexTable = Memmap_GetSegmentVaddr(segment->unk_0C);
    for (i = 0; i < segment->vertexCount; i++) {
        mvtx->childIndex = var_a1;
        do {
            temp_v0_2 = *indexTable++;
            var_a1++;
        } while (temp_v0_2 != -1);
        mvtx++;
    }

    mvtx = base;
    for (i = 0; i < segment->vertexCount; i++) {
        ModelVertex* temp_v0 = &base[mvtx->jointIndex];
        mvtx->parentIndex = temp_v0->childIndex;
        mvtx++;
    }
}

void func_80033B2C(StadiumModel* model, void* arg1,  void* arg2, void* arg3) {
    f32 sp4C;
    f32 sp48;
    f32 sp44;
    f32 sp40;
    f32 sp3C;
    f32 sp38;
    f32 sp34;
    f32 sp30;
    f32 sp2C;
    f32 sp28;
    f32 sp24;
    f32 sp20;
    MtxF* temp_s0;
    ModelSegment* segment;
    ModelSegment* temp_v0;

    model = Memmap_GetSegmentVaddr(model);
    arg1 = Memmap_GetSegmentVaddr(arg1);
    temp_s0 = Memmap_GetSegmentVaddr(arg2);
    temp_v0 = Memmap_GetSegmentVaddr(arg3);
    segment = &model->unkSegment;
    D_800B2F50 = arg1;
    *segment = *temp_v0;
    model->unk_00 = 1;
    model->unk_02 = 0;
    model->modelSegment = segment;
    sp40 = temp_s0->xx;
    sp3C = temp_s0->yx;
    sp38 = temp_s0->zx;
    sp34 = temp_s0->xy;
    sp30 = temp_s0->yy;
    sp2C = temp_s0->zy;
    sp28 = temp_s0->xz;
    sp24 = temp_s0->yz;
    sp20 = temp_s0->zz;
    sp4C = sqrtf((sp40 * sp40) + (sp3C * sp3C) + (sp38 * sp38));
    sp48 = sqrtf((sp34 * sp34) + (sp30 * sp30) + (sp2C * sp2C));
    sp44 = sqrtf((sp28 * sp28) + (sp24 * sp24) + (sp20 * sp20));
    if (sp4C == 0.0f) {
        sp4C = 1.0f;
    }
    if (sp48 == 0.0f) {
        sp48 = 1.0f;
    }
    if (sp44 == 0.0f) {
        sp44 = 1.0f;
    }
    model->position.x = sp4C;
    model->position.y = sp48;
    model->position.z = sp44;
    guScale(&D_800B3258, 0.1f, 0.1f, 0.1f);
    func_800338D8(model, temp_s0);
    func_800357F4(model);
}

void func_80033D1C(StadiumModel* model, MtxF* mtx) {
    func_800338D8(model, mtx);
    func_800357F4(model);
}

void func_80033D44(StadiumModel* model, s16 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8, MtxF* arg9) {
    f32 len;
    f32 x2;
    f32 y2;
    f32 z2;
    f32 x3;
    f32 sp138;
    f32 sp134;
    f32 sp130;
    f32 sp12C;
    f32 sp128;
    f32 sp124;
    f32 sp120;
    f32 sp11C;
    f32 sp118;
    f32 sp114;
    f32 sp110;
    f32 sp10C;
    f32 sp108;
    f32 sp104;
    f32 x;
    f32 y;
    f32 z;
    f32 spF4;
    f32 spF0;
    f32 spEC;
    f32 dx;
    f32 dy;
    f32 dz;
    f32 dist;
    f32 spD8;
    f32 spD4;
    f32 spD0;
    f32 spCC;
    f32 spC8;
    f32 spC4;
    s16 idx;
    s32 i;
    ModelSegment* segment;
    ModelBlendWeight* wt;
    StadiumTransform* xf;
    ModelVertex* mvtx;
    s32 pad[2];

    segment = Memmap_GetSegmentVaddr(model->modelSegment);
    idx = model->unk_02++;
    dx = arg6 - arg3;
    dy = arg7 - arg4;
    dz = arg8 - arg5;
    len = sqrtf((dx * dx) + (dy * dy) + (dz * dz));
    if (len != 0.0f) {
        spD8 = -1.0;
        spD4 = 0.0;
        spD0 = 0.0;
        dx = dx / len;
        dy = dy / len;
        dz = dz / len;
        if (0.9f < func_8003342C((dx * spD8) + (dy * spD4) + (dz * spD0))) {
            spD4 = 1.0f;
            spD8 = 0.0f;
            spD0 = 0.0f;
            if (0.9f < func_8003342C(dy)) {
                spD0 = 1.0f;
                spD4 = 0.0f;
            }
        }
        func_80033450(dx, dy, dz, spD8, spD4, spD0, &spCC, &spC8, &spC4);
        x2 = arg3 + spCC;
        y2 = arg4 + spC8;
        z2 = arg5 + spC4;
        func_80033450(dx, dy, dz, spCC, spC8, spC4, &spCC, &spC8, &spC4);
        x3 = arg3 + spCC;
        sp138 = arg4 + spC8;
        sp134 = arg5 + spC4;
        xf = &model->transforms[idx];
        xf->unk_00 = arg1;
        xf->maxDist = arg2;
        xf->x0 = arg3;
        xf->y0 = arg4;
        xf->z0 = arg5;
        xf->x1 = arg6;
        xf->y1 = arg7;
        xf->z1 = arg8;
        xf->x2 = x2;
        xf->y2 = y2;
        xf->z2 = z2;
        xf->x3 = x3;
        xf->y3 = sp138;
        xf->z3 = sp134;
        xf->mtx = arg9;
        guMtxXFMF(arg9->mf, arg3, arg4, arg5, &sp130, &sp12C, &sp128);
        guMtxXFMF(arg9->mf, arg6, arg7, arg8, &sp124, &sp120, &sp11C);
        guMtxXFMF(arg9->mf, x2, y2, z2, &sp118, &sp114, &sp110);
        guMtxXFMF(arg9->mf, x3, sp138, sp134, &sp10C, &sp108, &sp104);
        mvtx = &model->mvtx;
        for (i = 0; i < segment->vertexCount; i++) {
            x = mvtx->position.base.x;
            y = mvtx->position.base.y;
            z = mvtx->position.base.z;
            dist = func_80033568(x, y, z, sp130, sp12C, sp128, sp124, sp120, sp11C, &spF4, &spF0, &spEC);
            if (dist > 0.0f) {
                x = (((x - spF4) * arg2) / dist) + spF4;
                y = (((y - spF0) * arg2) / dist) + spF0;
                z = (((z - spEC) * arg2) / dist) + spEC;
            }
            wt = &mvtx->cmd.weights[idx];
            wt->w0 = func_800334C0(x, y, z, sp130, sp12C, sp128, sp124, sp120, sp11C);
            wt->w1 = func_800334C0(x, y, z, sp130, sp12C, sp128, sp118, sp114, sp110);
            wt->w2 = func_800334C0(x, y, z, sp130, sp12C, sp128, sp10C, sp108, sp104);
            wt->dist = dist;
            mvtx++;
        }
    }
}

void func_80034254(StadiumModel* model) {
    u32 pad[2];
    ModelSegment* segment;
    s16* indexTable;
    f32 var_fv0;
    s16 temp_v1;
    s32 j;
    s32 i;
    ModelVertex* temp_a1;
    ModelVertex* var_a2;
    ModelBlendWeight* var_a0;

    segment = Memmap_GetSegmentVaddr(model->modelSegment);
    indexTable = Memmap_GetSegmentVaddr(segment->remapSegment);
    temp_a1 = &model->mvtx;
    var_a2 = temp_a1;
    for(i = 0; i < segment->vertexCount; i++) {
        var_a2->position.nextIndex = -1;
        var_a2++;
    }
    var_a2 = temp_a1;
    for (i = 0; i < segment->vertexCount; i++) {
        temp_v1 = indexTable[i];
        if (temp_v1 == i) {
            var_fv0 = 10000.0f;
            for (j = 0; j < model->unk_02; j++) {
                var_a0 = &var_a2->cmd.weights[j];
                if (var_a0->dist < var_fv0) {
                    var_fv0 = var_a0->dist;
                    var_a2->position.nextIndex = j;
                }
            }
        }
        var_a2++;
    }
}

// Score 2582 (fd.sh; was 2760, 2905, 3485; agent-12: count/index/remap decl order fixes the remap
// spill slot 0x84, `(vertices + ia)->` gives the target addu operand order). Integer side (index/remap/ia/ib/ic and the whole first and
// last loops) now matches: the index reads are `remap[*index++]` x3 (uopt folds them into one +6).
// Left: float register allocation in the triangle loop. Pre-as1 view (cc -S, see below) of what the
// target must have been, from its final code:
//   uopt colours ay f12, az f14, by f0, bz f2, cy f16, cz f18, bx f28 (fs4); ax and cx are named but
//   uncoloured (homes 0xF0/0xD8); CSE temps by-ay f30, bz-az f22 split (spill 0x5C), cz-bz f20 split
//   (0x60), cy-by uncoloured (0x58), bx-ax f16, cx-bx f14; ny f20, nz f22, nx f24, len f26.
//   The "phantom" fs3 is len: ugen emits `mov.s $f26,$f0` after sqrtf, as1 forwards $f0 into both
//   uses and deletes the mov, leaving only the save/restore. len only lands in a callee-saved reg if
//   all six caller-saved FP regs (f0 f2 f12 f14 f16 f18) are taken in the loop block by named vars.
// Tools: `cc -S` (ugen output, pre-as1, shows uopt's register choices and split/spill points);
// a standalone harness with ~15000 generated variants (coords named/inline per coordinate, named
// edges, cross-product operand and statement orders, load orders, index styles) never produced that
// colouring: naming all nine coords gives a.* memory / b.* callee-saved / c.* caller-saved and nx/ny/
// nz split around the call; naming only ay,az,by,cy,cz gives the right caller-saved set but len f2.
// Declaration order and block scope of the locals do not change uopt's choices; load order does.
// Dead ends: clean rewrite with all nine coords named + inline cross product (~9500-11000 in-tree);
// Vec3f* / ModelVertex* pointers (13193); computing nx before ny in the m2c draft (~3600); inlining
// e1x/e2x (3280-5172); named edges (all subsets); len reused / separate scale var / inline 120/len;
// D_800B2F50[ia].x += form; -Wo,-rege/-regr (no effect on FPRs).
// Round 8 pass 4 (agent-15): 2582 -> 705: named ay loaded AFTER a block boundary placed after the by
// load (sweep of ay position x boundary position; earlier step, 1298, below). From farm j2 output-1458: a uopt basic-block boundary
// right after the bx load (`if (0) {}`, an empty goto label or `switch (0) { default:; }` all give
// the same code; `do {} while (0)` / `while (0) {}` / bare label do not) plus a named
// `e = by - ay` used only in nx (nz keeps the inline form; using e in nz too is 3700+). Block
// boundary sweep: after `ib =` 1322-1338, after `bx =` 1298-1314, every other line 2900-10000.
// pad0 dropped for e, so cx's home is 0xDC (target 0xD8); keeping pad0 and dropping a pad1 slot
// instead gives the target layout but scores 1314. Still differs: az lands in fs0 (target fa1),
// cy/cz in fa1/ft4 (target ft4/ft5), cz-bz f24 / bz-az f26 (target f20/f22), nx/ny/nz colours.
// Sweeps that did not help on top of the boundary: ay named (before/after ax, 1434-1709), any
// subset of the six edges named (copy-propagated, sunk to first use in nx; 1499+), each of ay/az/
// cy/cz named vs inline loads (48 variants, best 1314).
// Round 9 F1 (farm v2/390): 705 -> 390 with a copy `by2 = by` (decl between nx and ny) used in nx
// and both nz statements, nz split into `nz = (by2 - ay) * (cx - bx); nz = ((bx - ax) * (cy - by2)) - nz;`
// (the (by-ay)*(cx-bx) subexpression gets its own live range), AND a dead `cx` reload
// (`cx = (vertices + ic)->position.base.x;`) right after `len = 120.0f / len;`. All three edits are
// required together: new_var/nz-split without the cx reload scores 2417, single-statement nz with
// the reload 3844, the reload alone 6761, an added `if (!len) {}` at the first counter store 390.
// Still differs: az fs0 vs fa1, cy/cz fa1/ft4 vs ft4/ft5, cz-bz f24 / bz-az f26 vs f20/f22, nx/ny/nz
// colours, and the phantom len (fs3) save/restore. Re-seed the farm from this.
// Round 9 agent-2: 390 -> 130. (1) by2's slot: declare it after ia/ib/ic and drop one pad1 word
// (frame 0xF8, every slot matches). (2) Target loads ay (0x68) right after ax and az (0x6C) after the
// block boundary (fa0/fa1): swap the two loads (250). (3) The phantom fs3 is the nx CSE temp: cc -S
// showed `sub.s $f24..; mov.s $f26,$f24` and `nx *= len` reading the temp f24 (copy-propagated into
// the if-block; ny/nz are not because the dead cx reload redefines their operand), so as1 could not
// fold the mov. A dead reload of any nx operand in the if-block (cz/cy/ay/az/bz/by, before or after
// the cx reload; all 130, `by2 = by;` there 250) makes nx a real variable, as1 renames the temp away
// and only the fs3 save remains, as in the target.
// Still differs (130): only the coordinate colours. Target ay f12 az f14 by f0 bz f2 cy f16 cz f18
// and vertex pointers ia v0 ib v1 ic a0; ours ay f16 az f2 by f18 bz f0 cy f12 cz f14, ia v1 ib a0
// ic v0 (uopt colouring order).
// 130 -> 60: the by2 copy and the nz split are no longer needed. uopt colours in priority order,
// roughly refs / blocks spanned, ties in variable order: by/bz (3 refs) > ay/az > cy/cz all in ONE
// block gives exactly the target f0 f2 / f12 f14 / f16 f18, while ax/bx must span the boundary too
// (bx then falls to fs4, ax uncoloured). So the block boundary goes right after the bx load and every
// other coordinate load follows it. All floats now match. Without the boundary 6145, without the
// cz reload 180, without the cx reload 1627, without both 4314; extra dead ax/bx/ay/by reloads in the
// if-block change nothing.
// Still differs (60): vertex pointer temps, target (vertices+ia) v0, +ib v1, +ic a0; ours +ia v1,
// +ib a0, +ic v0 (the ic pointer lives in one block, so it outranks the two that span the boundary).
#ifdef NON_MATCHING
void func_80034348(ModelSegment* segment, ModelVertex* vertices) {
    s32 i;
    f32 ax;
    f32 ay;
    f32 az, bx, by, bz, cx, cy, cz;
    f32 nx, ny, nz;
    f32 len;
    s16 ia, ib, ic;
    f32 by2;
    s32 pad1[9];
    f32 count;
    s16* index;
    s16* remap;
    s16 triangleCount;
    s16 vertexCount;
    ModelVertex* vtx;
    Vec3fCounter* counter;

    triangleCount = segment->triangleCount;
    vertexCount = segment->vertexCount;
    index = Memmap_GetSegmentVaddr(segment->indexSegment);
    remap = Memmap_GetSegmentVaddr(segment->remapSegment);
    counter = D_800B2F50;
    for (i = 0; i < vertexCount; i++) {
        counter->x = 0.0f;
        counter->y = 0.0f;
        counter->z = 0.0f;
        counter->count = 0;
        counter++;
    }
    for (i = 0; i < triangleCount; i++) {
        ia = remap[*index++];
        ax = (vertices + ia)->position.base.x;
        ib = remap[*index++];
        bx = (vertices + ib)->position.base.x;
        if (0) {}
        ay = (vertices + ia)->position.base.y;
        by = (vertices + ib)->position.base.y;
        bz = (vertices + ib)->position.base.z;
        az = (vertices + ia)->position.base.z;
        ic = remap[*index++];
        cx = (vertices + ic)->position.base.x;
        cy = (vertices + ic)->position.base.y;
        cz = (vertices + ic)->position.base.z;
        nx = ((by - ay) * (cz - bz)) - ((bz - az) * (cy - by));
        ny = ((bz - az) * (cx - bx)) - ((bx - ax) * (cz - bz));
        nz = ((bx - ax) * (cy - by)) - ((by - ay) * (cx - bx));
        len = sqrtf((nx * nx) + (ny * ny) + (nz * nz));
        if ((s32) len > 0) {
            len = 120.0f / len;
            cx = (vertices + ic)->position.base.x;
            cz = (vertices + ic)->position.base.z;
            nx *= len;
            ny *= len;
            nz *= len;
        }
        counter = &D_800B2F50[ia];
        counter->x += nx;
        counter->y += ny;
        counter->z += nz;
        counter->count++;
        counter = &D_800B2F50[ib];
        counter->x += nx;
        counter->y += ny;
        counter->z += nz;
        counter->count++;
        counter = &D_800B2F50[ic];
        counter->x += nx;
        counter->y += ny;
        counter->z += nz;
        counter->count++;
    }
    counter = D_800B2F50;
    vtx = vertices;
    for (i = 0; i < vertexCount; i++) {
        if (counter->count > 0) {
            count = (f32) counter->count;
            vtx->position.color.r = (f32) (counter->x / count);
            vtx->position.color.g = (f32) (counter->y / count);
            vtx->position.color.b = (f32) (counter->z / count);
        }
        counter++;
        vtx++;
    }
}
#else
void func_80034348(ModelSegment*, ModelVertex*);
#pragma GLOBAL_ASM("asm/us/nonmatchings/33FE0/func_80034348.s")
#endif

void func_80034824(ModelSegment* segment, StadiumTransform* xf, s32 index, ModelVertex* vertices) {
    f32 x0, y0, z0;
    f32 temp_fs0, temp_fs1, temp_fs2;
    f32 temp_fs3, temp_fs4, temp_fs5;
    MtxF* mtx;
    s32 pad0[4];
    f32 sp184, sp180, sp17C;
    f32 sp178, sp174, sp170;
    f32 sp16C, sp168, sp164;
    f32 sp160, sp15C, sp158;
    f32 sp154, sp150, sp14C;
    f32 sp148, sp144, sp140;
    f32 sp13C, sp138, sp134;
    f32 sp130, sp12C, sp128;
    f32 w0, w1, w2;
    f32 bx, by, bz;
    s32 pad1[24];
    UNUSED f32 sumX, sumY, sumZ;
    s16* spA0;
    s16 temp_s6;
    s16* temp_v0;
    s32 i;
    s32 temp_s0;
    PosBlend* temp_v0_2;
    s32 pad2[1];
    ModelVertex* vtx;

    temp_s6 = segment->vertexCount;
    spA0 = Memmap_GetSegmentVaddr(segment->remapSegment);
    temp_v0 = Memmap_GetSegmentVaddr(segment->tableSegment);
    x0 = xf->x0;
    y0 = xf->y0;
    z0 = xf->z0;
    temp_fs0 = xf->x1;
    temp_fs1 = xf->y1;
    temp_fs2 = xf->z1;
    temp_fs3 = xf->x2;
    temp_fs4 = xf->y2;
    temp_fs5 = xf->z2;
    sp184 = xf->x3;
    sp180 = xf->y3;
    sp17C = xf->z3;
    mtx = xf->mtx;
    guMtxXFMF(mtx->mf, x0, y0, z0, &sp178, &sp174, &sp170);
    guMtxXFMF(mtx->mf, temp_fs0, temp_fs1, temp_fs2, &sp16C, &sp168, &sp164);
    guMtxXFMF(mtx->mf, temp_fs3, temp_fs4, temp_fs5, &sp160, &sp15C, &sp158);
    guMtxXFMF(mtx->mf, sp184, sp180, sp17C, &sp154, &sp150, &sp14C);
    sp148 = sp16C - sp178;
    sp144 = sp168 - sp174;
    sp140 = sp164 - sp170;
    sp13C = sp160 - sp178;
    sp138 = sp15C - sp174;
    sp134 = sp158 - sp170;
    sp130 = sp154 - sp178;
    sp12C = sp150 - sp174;
    sp128 = sp14C - sp170;
    vtx = vertices;

    for (i = 0; i < temp_s6; i++) {
        temp_s0 = spA0[i];
        if (func_800336F8(temp_v0, temp_s0) != 0) {
            temp_v0_2 = &vtx->position;
            if (temp_s0 == i) {
                if (index == temp_v0_2->nextIndex) {
                    w0 = vtx->cmd.weights[index].w0;
                    w1 = vtx->cmd.weights[index].w1;
                    w2 = vtx->cmd.weights[index].w2;
                    temp_fs0 = (w0 * sp148) + sp178 + (w1 * sp13C) + (w2 * sp130);
                    temp_fs1 = (w0 * sp144) + sp174 + (w1 * sp138) + (w2 * sp12C);
                    temp_fs2 = (w0 * sp140) + sp170 + (w1 * sp134) + (w2 * sp128);
                    bx = temp_v0_2->base.x;
                    by = temp_v0_2->base.y;
                    bz = temp_v0_2->base.z;
                    temp_v0_2->disabled |= (1 << index);
                    temp_v0_2->offset.x = temp_fs0 - bx;
                    temp_v0_2->offset.y = temp_fs1 - by;
                    temp_v0_2->offset.z = temp_fs2 - bz;
                }
            }
        }
        vtx++;
    }
}

void func_80034B28(StadiumModel* model) {
    ModelSegment* segment;
    s32 count;
    s32 i;
    ModelVertex* mvtx;

    segment = Memmap_GetSegmentVaddr(model->modelSegment);
    mvtx = &model->mvtx;
    count = model->unk_02;

    for (i = 0; i < count; i++) {
        func_80034824(segment, &model->transforms[i], i, mvtx);
    }

    func_80035FA8(segment, mvtx);
    func_800359FC(segment, mvtx, model, 1.0f);
}

void func_80034BD4(u32 modelSegment, StadiumTransform* xf, s32 index, ModelVertex* vertices) {
    s32 pad0[5];
    f32 sp180;
    f32 sp17C;
    f32 sp178;
    f32 sp174;
    f32 sp170;
    f32 sp16C;
    f32 sp168;
    f32 sp164;
    f32 sp160;
    f32 sp15C;
    f32 sp158;
    f32 sp154;
    f32 sp150;
    f32 sp14C;
    f32 sp148;
    f32 sp144;
    f32 sp140;
    f32 sp13C;
    f32 sp138;
    f32 sp134;
    f32 sp130;
    s32 pad1[10];
    f32 sp104, sp100, spFC;
    f32 one = 1.0f;
    f32 w0, w1, w2, x, y, z, temp_fv0;
    s32 pad2[4];
    s16 spCA;
    s16* temp_s1;
    s16* spC0;
    ModelVertex* var_s0;
    MtxF* mtx;
    f32 temp_fs0, temp_fs1, temp_fs2;
    s16 temp_s1_2;
    ModelSegment* temp_v0;
    s32 i;
    PosBlend* temp_v0_2;

    temp_v0 = Memmap_GetSegmentVaddr(modelSegment);
    spCA = temp_v0->vertexCount;
    temp_s1 = Memmap_GetSegmentVaddr(temp_v0->remapSegment);
    spC0 = Memmap_GetSegmentVaddr(temp_v0->tableSegment);
    mtx = xf->mtx;
    guMtxXFMF(mtx->mf, xf->x0, xf->y0, xf->z0, &sp180, &sp17C, &sp178);
    guMtxXFMF(mtx->mf, xf->x1, xf->y1, xf->z1, &sp174, &sp170, &sp16C);
    guMtxXFMF(mtx->mf, xf->x2, xf->y2, xf->z2, &sp168, &sp164, &sp160);
    guMtxXFMF(mtx->mf, xf->x3, xf->y3, xf->z3, &sp15C, &sp158, &sp154);
    sp150 = sp174 - sp180;
    sp14C = sp170 - sp17C;
    sp148 = sp16C - sp178;
    sp144 = sp168 - sp180;
    sp140 = sp164 - sp17C;
    sp13C = sp160 - sp178;
    sp138 = sp15C - sp180;
    sp134 = sp158 - sp17C;
    sp130 = sp154 - sp178;
    var_s0 = vertices;
    for (i = 0; i < spCA; i++) {
        temp_s1_2 = temp_s1[i];
        if ((func_800336F8(spC0, temp_s1_2) != 0) && (temp_s1_2 == i)) {
            temp_fs0 = var_s0->position.base.x;
            temp_fs1 = var_s0->position.base.y;
            temp_fs2 = var_s0->position.base.z;
            temp_fv0 = func_80033568(temp_fs0, temp_fs1, temp_fs2, sp180, sp17C, sp178, sp174, sp170, sp16C, &sp104, &sp100, &spFC);
            temp_v0_2 = &var_s0->position;
            if ((temp_fv0 > 0.0f) && (temp_fv0 < xf->maxDist)) {
                ModelBlendWeight* wt = &var_s0->cmd.weights[index];

                w0 = wt->w0;
                w1 = wt->w1;
                w2 = wt->w2;
                x = (w0 * sp150) + sp180 + (w1 * sp144) + (w2 * sp138);
                y = (w0 * sp14C) + sp17C + (w1 * sp140) + (w2 * sp134);
                z = (w0 * sp148) + sp178 + (w1 * sp13C) + (w2 * sp130);
                temp_v0_2->disabled |= (1 << index);
                temp_v0_2->offset.x = (x - temp_fs0) * one;
                temp_v0_2->offset.y = (y - temp_fs1) * one;
                temp_v0_2->offset.z = (z - temp_fs2) * one;
            } else {
                temp_v0_2->disabled &= ~(1 << index);
            }
        }
        var_s0++;
    }
}

void func_80034F68(MtxF* mtx, Vec3f* out, s16 (*in)[3]) {
    f32 sp34;
    f32 sp30;
    f32 sp2C;

    sp34 = (f32) (*in)[0];
    sp30 = (f32) (*in)[1];
    sp2C = (f32) (*in)[2];

    guMtxXFMF(mtx->mf, sp34, sp30, sp2C, &sp34, &sp30, &sp2C);

    out->x = sp34;
    out->y = sp30;
    out->z = sp2C;
}

void func_80035000(MtxF* mtx, PosBlend* position, s16 (*target)[3], f32 alpha) {
    f32 sp44;
    f32 sp40;
    f32 sp3C;
    f32 dx;
    f32 dy;
    f32 dz;

    sp44 = (f32) (*target)[0];
    sp40 = (f32) (*target)[1];
    sp3C = (f32) (*target)[2];

    guMtxXFMF(mtx->mf, sp44, sp40, sp3C, &sp44, &sp40, &sp3C);

    dx = sp44 - position->base.x;
    dy = sp40 - position->base.y;
    dz = sp3C - position->base.z;

    dx *= alpha;
    dy *= alpha;
    dz *= alpha;

    position->offset.x += dx;
    position->offset.y += dy;
    position->offset.z += dz;
}

void func_800350E4(ModelSegment* segment, MtxF* mtx, ModelVertex* mvtx) {
    s16* indexTable;
    s32 i;
    Vtx* vtx;
    PosBlend* position;
    ModelVertex* tmp;

    indexTable = Memmap_GetSegmentVaddr(segment->tableSegment);
    vtx = Memmap_GetSegmentVaddr(segment->vertexSegment);
    Memmap_GetSegmentVaddr(segment->remapSegment);
    tmp = mvtx;
    
    for(i = 0; i < segment->vertexCount; i++) {
        position = &tmp->position;
        switch (func_800336F8(indexTable, i)) {
            case 0:
            default:
                func_80034F68(mtx, &position->base, &vtx->v.ob);
                position->offset.x = 0.0f;
                position->offset.y = 0.0f;
                position->offset.z = 0.0f;
                break;
            case 4:
                func_80034F68(mtx + func_80033890(indexTable, i), &position->base, &vtx->v.ob);
                position->offset.x = 0.0f;
                position->offset.y = 0.0f;
                position->offset.z = 0.0f;
                break;
        }
        vtx++;
        tmp++;
    }
}

void func_80035208(struct PosBlend* src, struct PosBlend* dst) {
    *dst = *src;
}

void func_80035208_empty() {

}

void func_80035248(ModelSegment* segment, MtxF* mtx, ModelVertex* mvtx) {
    ModelVertex* tmp;
    Vtx* vtx;
    PosBlend* position;
    s16* var_s7;
    s32 i;
    s16* temp_s5;
    temp_s5 = Memmap_GetSegmentVaddr(segment->tableSegment);
    vtx = Memmap_GetSegmentVaddr(segment->vertexSegment);
    var_s7 = Memmap_GetSegmentVaddr(segment->remapSegment);
    tmp = mvtx;

    for(i = 0; i < segment->vertexCount; i++) {
        position = &tmp->position;
        if (i == *var_s7) {
            switch (func_800336F8(temp_s5, i)) {
            case 0:
                func_80034F68(mtx, &position->base, &vtx->v.ob);
                break;
            case 4:
                func_80034F68(mtx + func_80033890(temp_s5, i), &position->base, &vtx->v.ob);
                break;
            case 1:
                func_80035000(mtx, position, &vtx->v.ob, D_800775D4[func_80033830(temp_s5, i)]);
                break;
            case 2:
                func_80034F68(mtx, &position->base, &vtx->v.ob);
                func_80035208(position, &D_800B2F58[func_80033850(temp_s5, i)]);
                break;
            case 3:
                func_80034F68(mtx, &position->base, &vtx->v.ob);
                func_80035208(position, &D_800B2F58[func_80033870(temp_s5, i)]);
                break;
            default:
                break;
            }
        }
        vtx++;
        var_s7++;
        tmp++;
    }
}

f32 func_80035434(Vec3f* a, Vec3f* b, Vec3f* scale) {
    f32 dx;
    f32 dy;
    f32 dz;

    dx = (a->x - b->x) / scale->x;
    dy = (a->y - b->y) / scale->y;
    dz = (a->z - b->z) / scale->z;

    if (func_8003342C(dx) < 10e-05f) {
        dx = 0.0f;
    }
    if (func_8003342C(dy) < 10e-05f) {
        dy = 0.0f;
    }
    if (func_8003342C(dz) < 10e-05f) {
        dz = 0.0f;
    }
    return sqrtf((dx * dx) + (dy * dy) + (dz * dz));
}

f32 func_80035538(s16 (*a)[3], s16 (*b)[3]) {
    f32 dx;
    f32 dy;
    f32 dz;

    dx = (f32) ((*a)[0] - (*b)[0]);
    dy = (f32) ((*a)[1] - (*b)[1]);
    dz = (f32) ((*a)[2] - (*b)[2]);
    return sqrtf((dx * dx) + (dy * dy) + (dz * dz));
}

void func_800355A8(Vec3f* from, Vec3f* to, f32 currentTime, f32 deltaTime, f32 scale) {
    s32 pad;
    f32 temp_fv0;
    f32 temp_fa1;
    f32 temp_ft5;

    if (deltaTime < 10e-05f) {
        return;
    }

    temp_fv0 = to->x - from->x;
    temp_fa1 = to->y - from->y;
    temp_ft5 = to->z - from->z;

    scale *= (currentTime - deltaTime) / deltaTime;
    if (deltaTime < currentTime) {
        scale /= 2.0f;
    }

    to->x += temp_fv0 * scale;
    to->y += temp_fa1 * scale;
    to->z += temp_ft5 * scale;
}

void func_80035660(PosBlend* src, PosBlend* dst, f32 totalTime, f32 elapsed, f32 stiffness) {
    f32 sp3C;
    f32 sp38;
    f32 sp34;
    f32 var_fv0;

    if (!(elapsed < 10e-05f)) {
        if (func_8003342C(dst->base.x) < 10e-05f) {
            dst->base.x = 0.0f;
        }
        if (func_8003342C(dst->base.y) < 10e-05f) {
            dst->base.y = 0.0f;
        }
        if (func_8003342C(dst->base.z) < 10e-05f) {
            dst->base.z = 0.0f;
        }
        sp3C = dst->base.x - src->base.x;
        sp38 = dst->base.y - src->base.y;
        sp34 = dst->base.z - src->base.z;
        stiffness *= ((totalTime - elapsed) / elapsed);
        if (elapsed < totalTime) {
            stiffness /= 2.0f;
        }
        dst->base.x += sp3C * stiffness;
        dst->base.y += sp38 * stiffness;
        dst->base.z += sp34 * stiffness;
        dst->offset.x += sp3C * stiffness;
        dst->offset.y += sp38 * stiffness;
        dst->offset.z += sp34 * stiffness;
    }
}

void func_800357F4(StadiumModel* model) {
    s32 i;
    s32 pad1[4];
    s16* sp70;
    s32 pad2[1];
    s16* sp68;
    s32 pad3[7];
    ModelVertex* sp48;
    f32 temp_fv0;
    ModelSegment* sp40;
    s16 temp_s0;
    s16 temp_s1;
    s16 temp_s1_2;
    s16 temp_s2;
    s16 temp_s4;
    s16 temp_s4_2;
    s16 temp_s5;
    s16 temp_v0_2;
    s16* var_s6;
    s32 temp_t4;
    s32 temp_t7;
    Vtx* temp_fp;
    s16* temp_s3;
    ModelSegment* segment;
    ModelTransformCmd* cmd;
    ModelVertex* mvtx;

    segment = Memmap_GetSegmentVaddr(model->modelSegment);
    sp40 = segment;
    temp_s3 = Memmap_GetSegmentVaddr(segment->tableSegment);
    sp70 = Memmap_GetSegmentVaddr(sp40->remapSegment);
    temp_fp = Memmap_GetSegmentVaddr(sp40->vertexSegment);
    sp68 = Memmap_GetSegmentVaddr(sp40->unk_0C);
    mvtx = &model->mvtx;
    sp48 = mvtx;
    for (i = 0; i < sp40->vertexCount; i++) {
        temp_s2 = sp48->jointIndex;
        var_s6 = &sp68[sp48->parentIndex];
        while (1) {
            temp_v0_2 = *var_s6;
            var_s6++;
            if (temp_v0_2 == -1) {
                break;
            }
            temp_s0 = *(&sp70[temp_v0_2]);
            temp_s4 = func_80033810(temp_s3, temp_s2);
            temp_s5 = func_80033810(temp_s3, temp_s0);
            temp_s1 = func_800337D8(temp_s3, temp_s2);
            temp_t7 = func_800337D8(temp_s3, temp_s0) << 0x10;
            if ((temp_s4 < temp_s5) && (temp_s1 == (temp_t7 >> 0x10)) && (temp_s1 > 0)) {
                temp_s1_2 = func_800336F8(temp_s3, temp_s2);
                temp_s4_2 = func_800336F8(temp_s3, temp_s0);
                temp_fv0 = func_80035538(&temp_fp[temp_s2].v.ob, &temp_fp[temp_s0].v.ob);
                cmd = &mvtx->cmd;
                mvtx++;
                cmd->targetIndex = temp_s2;
                cmd->sourceIndex = temp_s0;
                cmd->enableFrom = temp_s1_2;
                cmd->enableTo = temp_s4_2;
                cmd->blendWeight = temp_fv0;
            }
        }
        sp48++;
    }
    mvtx->cmd.targetIndex = -1;
    mvtx->cmd.sourceIndex = -1;
    mvtx->cmd.blendWeight = -1.0f;
}

void func_800359FC(ModelSegment* segment, ModelVertex* vertices, StadiumModel* model, f32 deltaTime) {
    f32 temp_fs0;
    f32 temp_fv0;
    s16 temp_v1;
    s16 var_a0;
    s16 var_a1;
    s16 var_a2;
    ModelTransformCmd* temp_v0;
    ModelVertex* temp_a3;
    Vec3f* temp_s0;
    Vec3f* temp_s1;
    ModelVertex* temp_v0_2;
    ModelVertex* var_s2;

    Memmap_GetSegmentVaddr(segment->remapSegment);
    var_s2 = vertices;

    while (1) {
        temp_v0 = &var_s2->cmd;
        var_s2++;
        temp_v1 = temp_v0->targetIndex;
        if (temp_v1 == -1) {
            break;
        }
    
        var_a1 = temp_v0->sourceIndex;
        var_a2 = temp_v0->enableFrom;
        var_a0 = temp_v0->enableTo;
        temp_fs0 = temp_v0->blendWeight;
        temp_a3 = &vertices[temp_v1];
    
        if (temp_a3->position.disabled != 0) {
            var_a2 = 0;
        }
    
        temp_v0_2 = &vertices[var_a1];
        if (temp_v0_2->position.disabled != 0) {
            var_a0 = 0;
        }
    
        if ((var_a0 != 0) || (var_a2 != 0)) {
            temp_fv0 = func_80035434(&temp_a3->position.base, &temp_v0_2->position.base, &model->position);
            func_800355A8(&temp_a3->position.base, &temp_v0_2->position.base, temp_fs0, temp_fv0, deltaTime);
        }
        
    }
}

void func_80035B20(ModelSegment* segment, ModelVertex* vertices, StadiumModel* model, f32 deltaTime) {
    f32 temp_fs0;
    s16 temp_v1;
    s16 var_a0;
    s16 var_a1;
    s16 var_a2;
    ModelVertex* temp_a3;
    PosBlend* temp_s0;
    PosBlend* temp_s1;
    ModelTransformCmd* temp_v0;
    ModelVertex* temp_v0_2;
    ModelVertex* var_s2;

    Memmap_GetSegmentVaddr(segment->tableSegment);
    Memmap_GetSegmentVaddr(segment->remapSegment);
    var_s2 = vertices;
    while (1) {
        temp_v0 = &var_s2->cmd;
        var_s2++;
        temp_v1 = temp_v0->targetIndex;
        if (temp_v1 != -1) {
            var_a1 = temp_v0->sourceIndex;
            var_a2 = temp_v0->enableFrom;
            var_a0 = temp_v0->enableTo;
            temp_fs0 = temp_v0->blendWeight;
            temp_a3 = &vertices[temp_v1];
            if (temp_a3->position.disabled != 0) {
                var_a2 = 0;
            }
            temp_v0_2 = &vertices[var_a1];
            if (temp_v0_2->position.disabled != 0) {
                var_a0 = 0;
            }
            if ((var_a0 != 0) || (var_a2 != 0)) {
                temp_s0 = &temp_a3->position;
                temp_s1 = &temp_v0_2->position;
                func_80035660(temp_s0, temp_s1, temp_fs0, func_80035434(&temp_s0->base, &temp_s1->base, &model->position), deltaTime);
            }
            continue;
        }
        break;
    }
}

void func_80035C4C(ModelSegment* segment, ModelVertex* vertices, f32 yOffset) {
    s16* indexTable;
    s16* remap;
    s32 i;
    ModelVertex* tmp;

    indexTable = Memmap_GetSegmentVaddr(segment->tableSegment);
    remap = Memmap_GetSegmentVaddr(segment->remapSegment);
    tmp = vertices;
    for(i = 0; i < segment->vertexCount; i++) {
        if ((func_800336F8(indexTable, i) != 0) && (i == *remap)) {
            tmp->position.base.y += yOffset;
        }
        tmp++;
        remap++;
    }
}

void func_80035D08(ModelSegment* segment, ModelVertex* vertices, f32 yOffset) {
    s16* indexTable;
    s16* var_s2;
    s32 temp_v0;
    ModelVertex* tmp;
    s32 i;
    PosBlend* temp_v0_2;

    indexTable = Memmap_GetSegmentVaddr(segment->tableSegment);
    var_s2 = Memmap_GetSegmentVaddr(segment->remapSegment);
    tmp = vertices;
    for(i = 0; i < segment->vertexCount; i++) {
        if ((func_800336F8(indexTable, i) != 0) && (i == *var_s2)) {
            temp_v0 = func_800338B8(indexTable, i);
            temp_v0_2 = &tmp->position;
            switch (temp_v0) {
            case 1:
                temp_v0_2->base.y += yOffset;
                break;
            case 2:
                temp_v0_2->base.y += yOffset * 0.25f;
                break;
            }
        }
        tmp++;
        var_s2++;
    }
}

void func_80035E2C(ModelSegment* segment, ModelVertex* vertices, f32 arg2, StadiumModel* arg3) {
    s16* temp_s3;
    s16* var_s2;
    s32 temp_v0;
    ModelVertex* var_s1;
    s32 i;
    PosBlend* temp_v0_2;
    f32 zero = 0.0f;
    f32 one = 1.0f;
    f32 quarter = 0.25f;

    temp_s3 = Memmap_GetSegmentVaddr(segment->tableSegment);
    var_s2 = Memmap_GetSegmentVaddr(segment->remapSegment);
    var_s1 = vertices;
    for (i = 0; i < segment->vertexCount; i++) {
        if ((func_800336F8(temp_s3, i) != 0) && (i == *var_s2)) {
            temp_v0 = func_800338B8(temp_s3, i);
            temp_v0_2 = &var_s1->position;
            switch (temp_v0) {
            case 1:
                temp_v0_2->base.x += zero;
                temp_v0_2->base.y += arg2 * one;
                temp_v0_2->base.z += zero;
                break;
            case 2:
                temp_v0_2->base.x = temp_v0_2->base.x + zero;
                temp_v0_2->base.y = temp_v0_2->base.y + (quarter * arg2 * one);
                temp_v0_2->base.z = temp_v0_2->base.z + zero;
                break;
            }
        }
        var_s1 += 1;
        var_s2 += 1;
    }
}

void func_80035FA8(ModelSegment* segment, ModelVertex* vertices) {
    f32 var_fv0;
    s16* temp_s6;
    s16* var_s3;
    s32 i;
    u16 temp_v0;
    PosBlend* temp_s0;
    ModelVertex* var_s2;

    var_s2 = vertices;
    temp_s6 = Memmap_GetSegmentVaddr(segment->tableSegment);
    var_s3 = Memmap_GetSegmentVaddr(segment->remapSegment);

    for (i = 0; i < segment->vertexCount; i++) {
        temp_s0 = &var_s2->position;
        if ((func_800336F8(temp_s6, i) != 0) && (i == *var_s3)) {
            if (func_8003342C(temp_s0->offset.x) < 9.999999747e-05f) {
                temp_s0->offset.x = 0.0f;
            }
            if (func_8003342C(temp_s0->offset.y) < 9.999999747e-05f) {
                temp_s0->offset.y = 0.0f;
            }
            if (func_8003342C(temp_s0->offset.z) < 9.999999747e-05f) {
                temp_s0->offset.z = 0.0f;
            }
            if ((s32) temp_s0->drawGroup > 0) {
                var_fv0 = (f32) temp_s0->drawGroup;
                temp_s0->base.x = temp_s0->base.x + (temp_s0->offset.x / var_fv0);
                temp_s0->base.y = temp_s0->base.y + (temp_s0->offset.y / var_fv0);
                temp_s0->base.z = temp_s0->base.z + (temp_s0->offset.z / var_fv0);
                temp_s0->offset.x = temp_s0->offset.x - (0.3f * temp_s0->offset.x);
                temp_s0->offset.y = temp_s0->offset.y - (0.3f * temp_s0->offset.y);
                temp_s0->offset.z = temp_s0->offset.z - (0.3f * temp_s0->offset.z);
            } else {
                temp_s0->base.x = temp_s0->base.x + temp_s0->offset.x;
                temp_s0->base.y = temp_s0->base.y + temp_s0->offset.y;
                temp_s0->base.z = temp_s0->base.z + temp_s0->offset.z;
                temp_s0->offset.x = temp_s0->offset.x - (0.3f * temp_s0->offset.x);
                temp_s0->offset.y = temp_s0->offset.y - (0.3f * temp_s0->offset.y);
                temp_s0->offset.z = temp_s0->offset.z - (0.3f * temp_s0->offset.z);
            }
        }
        temp_s0->drawGroup = 0U;
        var_s2++;
        var_s3++;
    }
}

void func_800361C4(StadiumModel* model, MtxF* mtx) {
    s32 var_s0;
    s32 var_v1;

    ModelVertex* mvtx = &model->mvtx;
    ModelSegment* segment = Memmap_GetSegmentVaddr(model->modelSegment);
    switch (segment->type) {
    case 3:
        func_80035248(segment, mtx, mvtx);
        func_80035C4C(segment, mvtx, model->position.y * -10.0f);
        func_80034348(segment, mvtx);
        for(var_s0 = 0; var_s0 < model->unk_02; var_s0++) {
            func_80034BD4(segment, &model->transforms[var_s0], var_s0, mvtx);
        }
        func_80035FA8(segment, mvtx);
        func_800359FC(segment, mvtx, model, 0.7f);        
        break;
    case 4:
        func_80035248(segment, mtx, mvtx);
        func_80035C4C(segment, mvtx, model->position.y * -10.0f);
        func_80034348(segment, mvtx);
        func_80035FA8(segment, mvtx);
        break;
    case 10:
        func_80035248(segment, mtx, mvtx);
        func_80035D08(segment, mvtx, model->position.y * 160.0f);
        func_80035FA8(segment, mvtx);
        func_80035B20(segment, mvtx, model, 1.0f);
        break;
    case 11:
        func_80035248(segment, mtx, mvtx);
        func_80035E2C(segment, mvtx, 160.0f, model);
        func_80035FA8(segment, mvtx);
        func_80035B20(segment, mvtx, model, 1.0f);
        break;
    case 1:
        func_80035248(segment, mtx, mvtx);
        func_80034348(segment, mvtx);
        func_80035FA8(segment, mvtx);
        break;
    case 2:
        func_80035248(segment, mtx, mvtx);
        func_80035C4C(segment, mvtx, model->position.y * -10.0f);
        func_80034348(segment, mvtx);
        func_80035FA8(segment, mvtx);
        break;
    case 5:
        func_80035248(segment, mtx, mvtx);
        func_80034348(segment, mvtx);
        func_80035FA8(segment, mvtx);
        break;
    case 6:
        func_80035248(segment, mtx, mvtx);
        func_80034348(segment, mvtx);
        func_80035FA8(segment, mvtx);
        break;
    case 9:
        func_80035248(segment, mtx, mvtx);
        func_80034B28(model);
        func_80034348(segment, mvtx);
        break;
    default:
        return;
    }
    {
        s16* var_a0 = Memmap_GetSegmentVaddr(segment->remapSegment);
        for(var_v1 = 0; var_v1 < segment->vertexCount; var_v1++) {
            s16 segment_2 = *var_a0;
            if (segment_2 != var_v1) {
                 *(PosBlend*)&(var_v1 + mvtx)->position = *(PosBlend*)&mvtx[segment_2].position;
            }
            var_a0++;
        }
    }
}

void func_8003658C(StadiumModel* model, Vtx* vtxBuf) {
    ModelSegment* segment;
    ModelVertex* mvtx;
    Vtx* vtx;
    s32 i;

    segment = Memmap_GetSegmentVaddr(model->modelSegment);
    if ((s32) segment->type >= 0xC) {
        return;
    }
    mvtx = &model->mvtx;
    vtx = vtxBuf;
    for(i = 0; i < segment->vertexCount; i++) {
        vtx->v.ob[0] = (s16)(mvtx->position.base.x * 10.0f);
        vtx->v.ob[1] = (s16)(mvtx->position.base.y * 10.0f);
        vtx->v.ob[2] = (s16)(mvtx->position.base.z * 10.0f);
        vtx->v.cn[0] = (s16)mvtx->position.color.r;
        vtx->v.cn[1] = (s16)mvtx->position.color.g;
        vtx->v.cn[2] = (s16)mvtx->position.color.b;
        vtx->v.tc[0] = mvtx->position.texS;
        vtx->v.tc[1] = mvtx->position.texT;
        vtx->v.cn[3] = mvtx->position.alpha;
        vtx++;
        mvtx++;
    }
}

Gfx* func_800366A4(Gfx* gfx, StadiumModel* model, Vtx* vtxBuf) {
    ModelSegment* segment;

    segment = Memmap_GetSegmentVaddr(model->modelSegment);
    if ((s32) segment->type >= 0xC) {
        return gfx;
    }
    func_8003658C(model, vtxBuf);
    gSPSegment(gfx++, 0x0E, vtxBuf);
    gSPMatrix(gfx++, &D_800B3258, G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_PUSH);
    gSPDisplayList(gfx++, segment->displayList);
    gSPPopMatrixN(gfx++, G_MTX_MODELVIEW, 1);
    return gfx;
}
