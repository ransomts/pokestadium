#include "src/gb_audio_render.h"
#include "src/rom_device.h"
#include "src/audio_commands.h"

// Game Boy sound registers NR10..NR52 (0xFF10 + index), each a {value, dirty} byte pair.
typedef struct GbSoundReg {
    /* 0x00 */ u8 value;
    /* 0x01 */ u8 dirty;
} GbSoundReg; // size = 0x2

typedef struct unk_D_800FD068 {
    /* 0x00 */ u8* posX;
    /* 0x04 */ u8 rotation;
    /* 0x06 */ u16 unk_06;
} unk_D_800FD068; // size = 0x8

typedef struct unk_D_800FCFD8 {
    /* 0x00 */ u32 posX;
    /* 0x04 */ u8 rotation;
    /* 0x05 */ u8 pad05[0x3];
    /* 0x04 */ u32 RentalSlotAnimData_PosePhase;
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
    /* 0x00 */ u32 posX; // sample clock
    /* 0x04 */ s16 rotation; // volume
    /* 0x06 */ s16 unk_06; // volume step
    /* 0x08 */ u32 RentalSlotAnimData_PosePhase; // envelope period
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
    /* 0x00 */ u32 posX;
    /* 0x04 */ u8 unk04[0x18];
    /* 0x1C */ u8 unk_1C;
} unk_D_800FCFB8; // size = 0x20

// Game Boy sound channel 1 (square with sweep) state.
typedef struct unk_D_800FCF60 {
    /* 0x00 */ u32 posX; // sample clock
    /* 0x04 */ u16 rotation; // frequency
    /* 0x08 */ u32 RentalSlotAnimData_PosePhase; // sweep period
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
unk_D_800FCF60 gSquare1State;
unk_D_800FCF90 gSquare2State;
unk_D_800FCFB8 gNoiseState;
unk_D_800FCFD8 gWaveState;
u32 D_800FD004;
GbSoundReg gGbSoundRegs[0x20];
u8 D_800FD048[32];
unk_D_800FD068 gQueuedRegisterWrites[199];
u8 gGbRegCache[8];
u32 gQueuedWriteIndex;
u32 D_800FD6AC;
static u8 D_800FD6B0[0x30]; // pad
u8 D_800FD6E0;
u8 D_800FD6E1;
f32 D_800FD6E4;
s32 D_800FD6E8;
static u8 D_800FD6EC[0x4]; // pad
u32 gMusicFadePos;
u32 gOutputBufferPos;
s16 gInterpolationHistory[0x1140];
u32 gInterpolationPos;
u8 D_800FF97C;
s32 D_800FF980;

void GbAudio_RenderSamples(u32);
void GbAudio_ClearInterpolationHistory();
void GbAudio_ClearOutputBuffer();

void GbAudio_GenerateSamples(s16* arg0, s32 arg1, u32 arg2, f32 arg3) {
    GbAudio_RenderSamples(arg2);
}

void GbAudio_QueueRegisterWrite(u16 arg0, u8 arg1, u16 arg2) {
    gQueuedRegisterWrites[D_800FD6AC].posX = &gGbSoundRegs[(arg0 & 0xFF) - 0x10].value;
    gQueuedRegisterWrites[D_800FD6AC].rotation = arg1;
    gQueuedRegisterWrites[D_800FD6AC].unk_06 = arg2 + 1;
    gGbRegCache[arg0 & 0xFF] = arg1;
    D_800FD6AC++;
    D_800FD6AC %= 200;
    gQueuedRegisterWrites[D_800FD6AC].unk_06 = 0;
}

u8 GbAudio_GetRegisterValue(u16 arg0) {
    return gGbRegCache[arg0 & 0xFF];
}

void Audio_LoadMusicTrack(u32 arg0, u8 arg1, u32 arg2) {
    u32 temp_t3;
    u8* p;
    s32 i;
    D_800FD004 = arg0 >> 1;
    D_800FD6E4 = 1048576.0f / (f32) D_800FD004;

    p = (u8*) gGbSoundRegs;
    for (i = 0; i < 48; i++) {
       p[i * 2 + 1] = 1;
    }
    p = (u8*) gGbSoundRegs;
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
    gQueuedRegisterWrites[0].unk_06 = 0;
    gQueuedWriteIndex = 0;
    gSquare1State.posX = 0;
    gSquare1State.unk_2C = 0;

    gSquare2State.posX = 0;
    gSquare2State.unk_24 = 0;

    gNoiseState.posX = 0;
    gNoiseState.unk_1C = 0;

    gWaveState.posX = 0;
    gWaveState.unk_28 = 0;
    gWaveState.rotation = 0xFF;

    GbAudio_ClearOutputBuffer();
    GbAudio_ClearInterpolationHistory();

    D_800FF97C = arg1;
    D_800FF980 = arg2;
    D_800FF980 *= 2;
    if (D_800FF980 >= 0x1141U) {
        D_800FF980 = 0x1140;
    }
    D_800FD6E8 = 2;
}

void GbAudio_ApplyQueuedWrites(u16);
s16 GbAudio_RenderSquare1(void);
s16 GbAudio_RenderSquare2(void);
s16 GbAudio_RenderWave(void);

void GbAudio_RenderSamples(u32 arg0) {
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

    if ((tmp2 = gOutputBufferPos) < gMusicFadePos) {
        if ((0xB80 - (arg0 * 4)) < (gMusicFadePos - tmp2)) {
            arg0++;
        }
    } else if ((tmp2 - gMusicFadePos) < (arg0 * 4)) {
        arg0++;
    }

    for (i = 0; i < arg0; i++) {
        if (var_fs0 <= i) {
            GbAudio_ApplyQueuedWrites(var_s4);
        }

        if (gGbSoundRegs[0x16].value & 0x80) {
            if (gGbSoundRegs[0x14].dirty != 0) {
                D_800FD6E0 = gGbSoundRegs[0x14].value & 7;
                D_800FD6E1 = (gGbSoundRegs[0x14].value & 0x70) >> 4;
                gGbSoundRegs[0x14].dirty = 0;
            }

            sp4C[0] = GbAudio_RenderSquare1();
            sp4C[1] = GbAudio_RenderSquare2();
            sp4C[3] = GbAudio_RenderWave();

            tmp2 = gGbSoundRegs[0x15].value;
            var_a0 = ((u32)((sp4C[0] & ((tmp2 & 1) ? -1 : 0)) + (sp4C[1] & ((tmp2 & 2) ? -1 : 0)) +
                            (sp4C[3] & ((tmp2 & 8) ? -1 : 0))) >>
                      5) *
                     (D_800FD6E0 + 1);
        } else {
            var_a0 = 0;
        }

        tmp2 = gOutputBufferPos;
        if (D_800FF97C != 0) {
            if (1) {}
            if (1) {}
            if (1) {}
            if (1) {}
            tmp = (f32)gInterpolationHistory[((gInterpolationPos - D_800FF980) + 0x1140) % 4416];

            var_a0 += (s16)(((tmp - var_a0) * D_800FF97C) >> 8);
            gInterpolationHistory[gInterpolationPos++] = var_a0;
            if (gInterpolationPos >= 0x1140) {
                gInterpolationPos -= 0x1140;
            }
        }

        gMusicFadeBuffer[tmp2 + 0] = var_a0;
        gMusicFadeBuffer[gOutputBufferPos + 1] = var_a0;

        gOutputBufferPos += 2;
        if (gOutputBufferPos >= 0xB80) {
            gOutputBufferPos -= 0xB80;
        }

        var_s4++;
        var_fs0 += D_800FD6E4;
    }
}

void GbAudio_ApplyQueuedWrites(u16 arg0) {
    while (gQueuedRegisterWrites[gQueuedWriteIndex].unk_06 >= arg0) {
        gQueuedRegisterWrites[gQueuedWriteIndex].posX[0] = gQueuedRegisterWrites[gQueuedWriteIndex].rotation;
        gQueuedRegisterWrites[gQueuedWriteIndex].posX[1] = 1;
        gQueuedWriteIndex++;
        if (gQueuedWriteIndex >= 0xC8) {
            gQueuedWriteIndex -= 0xC8;
        }
    }
}

// Game Boy sound channel 1 (square wave with frequency sweep), registers NR10-NR14.
// Matching notes: `dir` is ONE variable shared by the trigger and the tail (t2 in both), declared as a
// one-element array: as a plain s32 uopt computes `duty & 8` into a global temp (t3) and copies it to dir,
// and as1 cannot fold that move because the remu's divide-by-zero break keeps t3 live (permuter farm,
// job t). NR12/NR11 in the sweep are read through `p = (u8*)gGbSoundRegs` (fresh lui loads straight into
// the variable instead of the a1 base); dir and duty are assigned in each predecessor (goto path and
// before `skip:`; both sweep directions); `(u8)duty & 0xF0` for unk_0C; `default:` last with no break.
s16 GbAudio_RenderSquare1(void) {
    s32 changed;
    s32 i;
    u32 nr14;
    u32 nr12;
    s32 nr11;
    s32 freq;
    u32 duty;
    u8 phase;
    u32 pos;
    s32 dir[1];
    s16 value;
    u8* p;

    p = (u8*)gGbSoundRegs;
    changed = 0;
    for (i = 0; i < 5; i++) {
        if (gGbSoundRegs[i].dirty != 0) {
            changed = 1;
            gGbSoundRegs[i].dirty = 0;
        }
    }

    if (changed) {
        nr14 = gGbSoundRegs[4].value;
        gSquare1State.rotation = gGbSoundRegs[3].value | ((u8)(nr14 & 7) << 8);
        gSquare1State.unk_24 = ((0x800 - gSquare1State.rotation) * D_800FD004) >> 11;
        duty = (gGbSoundRegs[1].value & 0xC0) >> 6;
        nr11 = gGbSoundRegs[1].value;
        switch (duty) {
            case 0:
                gSquare1State.unk_18[1] = gSquare1State.unk_24 >> 3;
                if (gSquare1State.unk_18[1] < 0x40) {
                    gSquare1State.unk_18[1] = 0x40;
                }
                gSquare1State.unk_18[0] = gSquare1State.unk_24 - gSquare1State.unk_18[1];
                phase = 1;
                break;
            case 1:
                gSquare1State.unk_18[1] = gSquare1State.unk_24 >> 2;
                if (gSquare1State.unk_18[1] < 0x40) {
                    gSquare1State.unk_18[1] = 0x40;
                }
                gSquare1State.unk_18[0] = gSquare1State.unk_24 - gSquare1State.unk_18[1];
                phase = 0;
                break;
            case 2:
                gSquare1State.unk_18[1] = gSquare1State.unk_24 >> 1;
                if (gSquare1State.unk_18[1] < 0x40) {
                    gSquare1State.unk_18[1] = 0x40;
                }
                gSquare1State.unk_18[0] = gSquare1State.unk_24 - gSquare1State.unk_18[1];
                phase = 0;
                break;
            case 3:
                gSquare1State.unk_18[0] = gSquare1State.unk_24 >> 2;
                if (gSquare1State.unk_18[0] < 0x40) {
                    gSquare1State.unk_18[0] = 0x40;
                }
                gSquare1State.unk_18[1] = gSquare1State.unk_24 - gSquare1State.unk_18[0];
                phase = 1;
                break;
            default:
                gSquare1State.unk_18[1] = 0;
                gSquare1State.unk_18[0] = gSquare1State.unk_24;
                phase = 1;
        }

        duty = gGbSoundRegs[2].value;
        dir[0] = duty & 8;
        if (!dir[0] && !(duty & 0xF0)) {
            gSquare1State.unk_2C = 0;
            gGbSoundRegs[0x16].value &= ~1;
            return 0;
        }
        if (dir[0] && !(duty & 0xF0) && !(duty & 7)) {
            gSquare1State.unk_2C = 0;
            gGbSoundRegs[0x16].value &= ~1;
            return 0;
        }

        if (nr14 & 0x80) {
            gSquare1State.posX = 0;
            gSquare1State.unk_2C = 1;
            gSquare1State.unk_1E = phase;
            gSquare1State.unk_1C = 0;
            gSquare1State.unk_20 = 0;
            gSquare1State.unk_0C = ((u8)duty & 0xF0) << 7;
            if (duty & 7) {
                if (dir[0]) {
                    gSquare1State.unk_0E = 0x800;
                } else {
                    gSquare1State.unk_0E = -0x800;
                }
                gSquare1State.unk_14 = gSquare1State.unk_10 = (duty & 7) * D_800FD004;
            } else {
                gSquare1State.unk_0E = 0;
                gSquare1State.unk_10 = -1;
                gSquare1State.unk_14 = -1;
            }
            gSquare1State.RentalSlotAnimData_PosePhase = (((gGbSoundRegs[0].value & 0x70) >> 4) * D_800FD004) >> 1;
            if (gSquare1State.RentalSlotAnimData_PosePhase == 0) {
                gSquare1State.RentalSlotAnimData_PosePhase = -1;
            }
            if (nr14 & 0x40) {
                gSquare1State.unk_28 = ((0x40 - (nr11 & 0x3F)) * D_800FD004) >> 2;
            } else {
                gSquare1State.unk_28 = -1;
            }
            gGbSoundRegs[4].value = nr14 & ~0x80;
        }
        if (gSquare1State.unk_2C == 0) {
            return 0;
        }
    } else if (gSquare1State.unk_2C == 0) {
        return 0;
    }

    if (gSquare1State.unk_28 < gSquare1State.posX) {
        gSquare1State.unk_2C = 0;
        gGbSoundRegs[0x16].value &= ~1;
        return 0;
    }

    if ((gSquare1State.RentalSlotAnimData_PosePhase - (gSquare1State.posX % gSquare1State.RentalSlotAnimData_PosePhase)) <= 0x40) {
        duty = gGbSoundRegs[0].value;
        if (!(duty & 8)) {
            freq = (u16)((gSquare1State.rotation >> (duty & 7)) + gSquare1State.rotation);
            if (freq >= 0x800) {
                gSquare1State.unk_2C = 0;
                gGbSoundRegs[0x16].value &= ~1;
                return 0;
            }
            gSquare1State.rotation = freq;
            duty = (p[2] & 0xC0) >> 6;
        } else {
            freq = (u16)(gSquare1State.rotation - (gSquare1State.rotation >> (duty & 7)));
            if (freq >= 0x800 || freq < 0) {
                dir[0] = p[4] & 8;
                goto skip;
            }
            gSquare1State.rotation = freq;
            duty = (p[2] & 0xC0) >> 6;
        }
        gSquare1State.unk_24 = ((0x800 - gSquare1State.rotation) * D_800FD004) >> 11;
        switch (duty) {
            case 0:
                gSquare1State.unk_18[1] = gSquare1State.unk_24 >> 3;
                if (gSquare1State.unk_18[1] < 0x40) {
                    gSquare1State.unk_18[1] = 0x40;
                }
                gSquare1State.unk_18[0] = gSquare1State.unk_24 - gSquare1State.unk_18[1];
                break;
            case 1:
                gSquare1State.unk_18[1] = gSquare1State.unk_24 >> 2;
                if (gSquare1State.unk_18[1] < 0x40) {
                    gSquare1State.unk_18[1] = 0x40;
                }
                gSquare1State.unk_18[0] = gSquare1State.unk_24 - gSquare1State.unk_18[1];
                break;
            case 2:
                gSquare1State.unk_18[1] = gSquare1State.unk_24 >> 1;
                if (gSquare1State.unk_18[1] < 0x40) {
                    gSquare1State.unk_18[1] = 0x40;
                }
                gSquare1State.unk_18[0] = gSquare1State.unk_24 - gSquare1State.unk_18[1];
                break;
            case 3:
                gSquare1State.unk_18[0] = gSquare1State.unk_24 >> 2;
                if (gSquare1State.unk_18[0] < 0x40) {
                    gSquare1State.unk_18[0] = 0x40;
                }
                gSquare1State.unk_18[1] = gSquare1State.unk_24 - gSquare1State.unk_18[0];
                break;
            default:
                gSquare1State.unk_18[1] = 0;
                gSquare1State.unk_18[0] = gSquare1State.unk_24;
        }
    }
    dir[0] = p[4] & 8;
skip:
    if (gSquare1State.unk_14 < gSquare1State.posX) {
        gSquare1State.unk_0C += gSquare1State.unk_0E;
        gSquare1State.unk_14 += gSquare1State.unk_10;
    }
    while (gSquare1State.unk_20 < gSquare1State.posX) {
        gSquare1State.unk_1E ^= 1;
        gSquare1State.unk_20 += gSquare1State.unk_18[gSquare1State.unk_1E];
    }

    if (!dir[0] && (gSquare1State.unk_0C < 0)) {
        gSquare1State.unk_2C = 0;
        return 0;
    }

    if ((u16)gSquare1State.unk_0C > 0x7800) {
        gSquare1State.unk_0C = 0x7800;
        gSquare1State.unk_0E = 0;
        gSquare1State.unk_14 = -1;
    }

    value = gSquare1State.unk_0C;
    if (gSquare1State.unk_1E == 0) {
        value = -value;
    }
    gSquare1State.posX = gSquare1State.posX + 0x40;
    return value;
}

// Game Boy sound channel 2 (square wave), registers NR21-NR24. Same shape as GbAudio_RenderSquare1 minus the sweep.
// Matching notes: NR22 is read through p (a pointer local) in the tail so uopt does not fold it into the
// a0-based CSE; `dir` must be one real variable shared by the trigger and the tail (so it gets t1 in both).
// `dir = duty & 8` alone is copy-propagated away (its uses become a `duty & 8` temp and the tail dir is
// then colored separately into v0); the redundant `duty = gGbSoundRegs[7].value` between the two kill
// tests redefines duty (no code: the load is CSE'd) and so blocks that propagation.
s16 GbAudio_RenderSquare2(void) {
    s32 changed;
    s32 i;
    u32 nr24;
    u32 duty;
    s32 nr21;
    u8 phase;
    u32 pos;
    s32 dir;
    s16 value;
    u8* p;

    p = (u8*)gGbSoundRegs;
    changed = 0;
    for (i = 6; i < 10; i++) {
        if (gGbSoundRegs[i].dirty != 0) {
            changed = 1;
            gGbSoundRegs[i].dirty = 0;
        }
    }

    if (changed) {
        nr24 = gGbSoundRegs[9].value;
        gSquare2State.unk_1C = ((0x800 - (gGbSoundRegs[8].value | ((u8)(nr24 & 7) << 8))) * D_800FD004) >> 11;
        duty = (gGbSoundRegs[6].value & 0xC0) >> 6;
        switch (duty) {
            case 0:
                gSquare2State.unk_10[1] = gSquare2State.unk_1C >> 3;
                if (gSquare2State.unk_10[1] < 0x40) {
                    gSquare2State.unk_10[1] = 0x40;
                }
                gSquare2State.unk_10[0] = gSquare2State.unk_1C - gSquare2State.unk_10[1];
                phase = 1;
                break;
            case 1:
                gSquare2State.unk_10[1] = gSquare2State.unk_1C >> 2;
                if (gSquare2State.unk_10[1] < 0x40) {
                    gSquare2State.unk_10[1] = 0x40;
                }
                gSquare2State.unk_10[0] = gSquare2State.unk_1C - gSquare2State.unk_10[1];
                phase = 0;
                break;
            case 2:
                gSquare2State.unk_10[1] = gSquare2State.unk_1C >> 1;
                if (gSquare2State.unk_10[1] < 0x40) {
                    gSquare2State.unk_10[1] = 0x40;
                }
                gSquare2State.unk_10[0] = gSquare2State.unk_1C - gSquare2State.unk_10[1];
                phase = 0;
                break;
            case 3:
                gSquare2State.unk_10[0] = gSquare2State.unk_1C >> 2;
                if (gSquare2State.unk_10[0] < 0x40) {
                    gSquare2State.unk_10[0] = 0x40;
                }
                gSquare2State.unk_10[1] = gSquare2State.unk_1C - gSquare2State.unk_10[0];
                phase = 1;
                break;
            default:
                gSquare2State.unk_10[1] = 0;
                gSquare2State.unk_10[0] = gSquare2State.unk_1C;
                phase = 1;
        }

        duty = gGbSoundRegs[7].value;
        dir = duty & 8;
        if (!dir && !(duty & 0xF0)) {
            gSquare2State.unk_24 = 0;
            gGbSoundRegs[0x16].value &= ~2;
            return 0;
        }
        duty = gGbSoundRegs[7].value;
        if (dir && !(duty & 0xF0) && !(duty & 7)) {
            gSquare2State.unk_24 = 0;
            gGbSoundRegs[0x16].value &= ~2;
            return 0;
        }

        if (nr24 & 0x80) {
            gSquare2State.posX = 0;
            gSquare2State.unk_24 = 1;
            gSquare2State.unk_16 = phase;
            gSquare2State.unk_14 = 0;
            gSquare2State.unk_18 = 0;
            gSquare2State.rotation = ((u8)duty & 0xF0) << 7;
            if (duty & 7) {
                if (dir) {
                    gSquare2State.unk_06 = 0x800;
                } else {
                    gSquare2State.unk_06 = -0x800;
                }
                gSquare2State.unk_0C = gSquare2State.RentalSlotAnimData_PosePhase = (duty & 7) * D_800FD004;
            } else {
                gSquare2State.unk_06 = 0;
                gSquare2State.RentalSlotAnimData_PosePhase = -1;
                gSquare2State.unk_0C = -1;
            }
            if (nr24 & 0x40) {
                gSquare2State.unk_20 = ((0x40 - (gGbSoundRegs[6].value & 0x3F)) * D_800FD004) >> 2;
            } else {
                gSquare2State.unk_20 = -1;
            }
            gGbSoundRegs[9].value = nr24 & ~0x80;
        }
        if (gSquare2State.unk_24 == 0) {
            return 0;
        }
    } else if (gSquare2State.unk_24 == 0) {
        return 0;
    }

    pos = gSquare2State.posX;
    if (gSquare2State.unk_20 < pos) {
        gSquare2State.unk_24 = 0;
        gGbSoundRegs[0x16].value &= ~2;
        return 0;
    }

    dir = p[0xE] & 8;
    if (gSquare2State.unk_0C < pos) {
        gSquare2State.rotation += gSquare2State.unk_06;
        gSquare2State.unk_0C += gSquare2State.RentalSlotAnimData_PosePhase;
    }
    while (gSquare2State.unk_18 <= pos) {
        gSquare2State.unk_16 ^= 1;
        gSquare2State.unk_18 += gSquare2State.unk_10[gSquare2State.unk_16];
    }

    if (!dir && (gSquare2State.rotation < 0)) {
        gSquare2State.unk_24 = 0;
        return 0;
    }

    if ((u16)gSquare2State.rotation > 0x7800) {
        gSquare2State.rotation = 0x7800;
        gSquare2State.unk_06 = 0;
        gSquare2State.unk_0C = -1;
    }

    value = gSquare2State.rotation;
    if (gSquare2State.unk_16 == 0) {
        value = -value;
    }
    gSquare2State.posX = pos + 0x40;
    return value;
}

typedef struct unk_D_80078A60 {
    /* 0x00 */ u8 posX;
    /* 0x04 */ f32 rotation;
} unk_D_80078A60; // size = 0x8

unk_D_80078A60 D_80078A60[8][16] = { { { 0, 1.0f }, { 1, 1.0f }, { 2, 1.0f }, { 3, 1.0f }, { 4, 1.0f }, { 5, 1.0f }, { 6, 1.0f }, { 7, 1.0f }, { 8, 1.0f }, { 9, 1.0f }, { 0xA, 1.0f }, { 0xB, 1.0f }, { 0xC, 1.0f }, { 0xD, 1.0f }, { 0xFF, 1.0f }, { 0xFF, 1.0f } }, { { 1, 1.0f }, { 2, 1.0f }, { 3, 1.0f }, { 4, 1.0f }, { 5, 1.0f }, { 6, 1.0f }, { 7, 1.0f }, { 8, 1.0f }, { 9, 1.0f }, { 0xA, 1.0f }, { 0xB, 1.0f }, { 0xC, 1.0f }, { 0xD, 1.0f }, { 0xD, 2.0f }, { 0xFF, 1.0f }, { 0xFF, 1.0f } }, { { 2, 1.0f }, { 3, 1.0f }, { 4, 1.0f }, { 5, 1.0f }, { 6, 1.0f }, { 7, 1.0f }, { 8, 1.0f }, { 9, 1.0f }, { 0xA, 1.0f }, { 0xB, 1.0f }, { 0xC, 1.0f }, { 0xD, 1.0f }, { 0xD, 2.0f }, { 0xD, 4.0f }, { 0xFF, 1.0f }, { 0xFF, 1.0f } }, { { 2, 1.5f }, { 3, 1.5f }, { 4, 1.5f }, { 5, 1.5f }, { 6, 1.5f }, { 7, 1.5f }, { 8, 1.5f }, { 9, 1.5f }, { 0xA, 1.5f }, { 0xB, 1.5f }, { 0xC, 1.5f }, { 0xD, 1.5f }, { 0xD, 3.0f }, { 0xD, 6.0f }, { 0xFF, 1.0f }, { 0xFF, 1.0f } }, { { 3, 1.0f }, { 4, 1.0f }, { 5, 1.0f }, { 6, 1.0f }, { 7, 1.0f }, { 8, 1.0f }, { 9, 1.0f }, { 0xA, 1.0f }, { 0xB, 1.0f }, { 0xC, 1.0f }, { 0xD, 1.0f }, { 0xD, 2.0f }, { 0xD, 4.0f }, { 0xD, 8.0f }, { 0xFF, 1.0f }, { 0xFF, 1.0f } }, { { 3, 1.25f }, { 4, 1.25f }, { 5, 1.25f }, { 6, 1.25f }, { 7, 1.25f }, { 8, 1.25f }, { 9, 1.25f }, { 0xA, 1.25f }, { 0xB, 1.25f }, { 0xC, 1.25f }, { 0xD, 1.25f }, { 0xD, 2.5f }, { 0xD, 5.0f }, { 0xD, 10.0f }, { 0xFF, 1.0f }, { 0xFF, 1.0f } }, { { 3, 1.5f }, { 4, 1.5f }, { 5, 1.5f }, { 6, 1.5f }, { 7, 1.5f }, { 8, 1.5f }, { 9, 1.5f }, { 0xA, 1.5f }, { 0xB, 1.5f }, { 0xC, 1.5f }, { 0xD, 1.5f }, { 0xD, 3.0f }, { 0xD, 6.0f }, { 0xD, 12.0f }, { 0xFF, 1.0f }, { 0xFF, 1.0f } }, { { 3, 1.75f }, { 4, 1.75f }, { 5, 1.75f }, { 6, 1.75f }, { 7, 1.75f }, { 8, 1.75f }, { 9, 1.75f }, { 0xA, 1.75f }, { 0xB, 1.75f }, { 0xC, 1.75f }, { 0xD, 1.75f }, { 0xD, 3.5f }, { 0xD, 7.0f }, { 0xD, 14.0f }, { 0xFF, 1.0f }, { 0xFF, 1.0f } } };
// Score 955 (diff.py without -s; was 3355, 5415). Wins: no len local, `(nr & 7)` written twice (farm
// candidate p2, 970 -> 955); ONE local for the dirty flag and the final
// sample value (`value`, s16: 1000 -> 970; idx and sample then get the target a1/a0) and pos merged into
// nr (1035 -> 1000) -- the target keeps one register per variable across disjoint ranges; NR41 read into the sample local before the
// unk_24 length computation (farm candidate n1; 1120 -> 1035; into nr 1075, dir/changed 1110, len 1135,
// idx 1170, i 1415, flags 1935); `if (unk_20 < posX)` re-reading the field
// instead of pos (farm candidate func_8004A89C__l1, 1510 -> 1120: no pos copy into v0); tail `dir = gGbSoundRegs[k].value & 8` with a
// non-constant index (k = 0x11 set after pos; trick from the GbAudio_RenderSquare2 farm candidate) right after
// `sample = rotation`, tested `!dir`: fresh-lui load + andi in the unk_20 beqz delay slot, in a1 like the
// target (2000 -> 1510; with a constant index or a u8* pointer the load folds into the t0 base; other
// locals for it 2345-2400); clamp stores in 14/18/20 order (2195 -> 2000); `unk_10 = 0` (int literal) stops IDO sharing one
// 0.0f register across the function; table row read TWICE as D_80078A60[..][..].posX / .rotation (no entry
// pointer) puts the unk_0C store in the beq delay slot with 0xc(v1) addressing (3215 -> 2195);
// `unk_20 = unk_1C = len*D_800FD004*4` (no pos temp; 0x1C stored first like the target); `sample = rotation`
// before the unk_20 test, NR42&8 read inline in the final test (fresh lui like the target), ent2 taken
// BEFORE the value load, `value = value * unk_14; return value;` (trunc result in a0 like the target).
// Remaining (mostly regalloc): target keeps idx in a1, (u16)col in a2 (computed in place), row ptr in a3,
// sample in a0 (v0 copy); NR42&8 andi sits in the unk_20 beqz delay slot (ours is late); pos split into
// v0 in the unk_24 test (target reloads unk_20 into v0 in a beqzl slot); li 1 / D_8007D4D0 order.
// Dead ends (all worse or equal): other 0/0.0f literal mixes, nr as full byte or `dir`, NR42 read before
// pos, u8* access, &= 0xF7, ternary +0x10, comma-expr unk_0C, gAudioSeqTOC[sample] in the call (2865 but
// loses the target's andi 0xFF re-read), entry pointer variable, u16/s32 `col` local (back to 2985),
// NR42&8 into any local (dir/idx/len/i/nr/flags, before or after the unk_20 test: 3235+), idx re-read
// from gGbSoundRegs instead of a local, reusing idx for dir / sample for len, s32/u16 value/sample/idx,
// declaration order (no effect), chained 0x20-first store; single (u8) casts on idx/nr/flags/len/dir uses
// (best 2110 = (u8)flags or (u8)nr in the kill tests, before the clamp fix; pairs of them are worse).
// At 955: tail `value = rotation` (sample through the value local; target a0 + uopt copy t5 suggests
// this) gives the right tail v0/a0 but 1245 overall; ent2 from a re-read of rotation after the lh 1020;
// col in a u16/s32/u32 local, entry+col locals, row/col locals (1765-2300); merge sweep over all local
// pairs after the changed/value + pos/nr merges: no further gain; inline dir / `if (nr & 7)`: worse.
// Round 8 pass 4 (agent-14): 955 -> 345: `f32 fv = D_8007D4D0` right after `if (flags & 0x80) {` used for unk_14 and
// unk_18 (farm candidate t, 470 -> 345: fixes the li 1 / lwc1 order); before that 955 -> 470: `(u8)(nr & 0xF0) * D_8007D4D0` for unk_14 (810 -> 695) and NR41 read inline
// in the unk_24 length (no sample local there: 695 -> 470; into nr/value 625, i 930, via p 690), on top of
// (a) + (b) below + the call index written `gAudioSeqTOC[gWaveState.rotation & 0xFF]`
// (both args; the extra and consumes the target's missing ring temp t6, like the (u8) trick in GbAudio_RenderSquare1;
// (u8)/(u16)/(s8)/(s16) casts there: 1045-1655). Leads (see GbAudio_RenderSquare1's notes):
// (a) the target's col is a REAL variable (a2: andi/sra/andi 0xffff in place, no ring temps), which shifts
// every later ring temp by the target's offset. `u16 col = (idx & 0xF0) >> 4` alone is copy-propagated
// away (expression of a register variable); `col = ...; if (idx) {} idx = gGbSoundRegs[0x12].value;` (block
// boundary + no-code redefinition of idx) keeps it real: the whole top block then matches except col/row
// colours swapped (col a3, row ptr a2; target a2/a3): 960. u32/s32/s16/u8 col 1065-1250, an ent pointer
// local, col read from gGbSoundRegs (2275-2620) worse. (b) on top of (a), `p = (u8*)gGbSoundRegs` + tail
// `dir = p[0x22] & 8` + reload `nr = gGbSoundRegs[0x11].value` between the kill tests makes dir ONE shared
// variable with the target's tail shape (lui/lbu/andi into dir): 1045, but dir lands in a2 and flags in a1
// (target dir a1, flags a2, pos a2). Tail pos into flags/k/i instead of nr: 1095-1400 (860 at 810).
// Remaining at 345: top idx a0 / row a1 / sample v0 / load temp a3 (target a1/a3/a0/v0); tail sample a3 and
// no `move t5,a0` copy before the value lh (target a0 + copy). `ent2 = &gAudioSeqTOC[(u8)value]` with value =
// rotation materialises the copy early (andi instead of move): 375. One-element arrays (the GbAudio_RenderSquare1
// fix) for dir/sample/idx/col/flags/nr/ent2: 640-2390.
// Remaining at 810: col/row ptr a3/a2 (target a2/a3), dir/flags a2/a1 (target a1/a2), pos a3 (target a2),
// `li 1` for unk_28 scheduled after the lui, tail sample/value v0/a0 (target a0 + move t5,a0).
// Round 9 F1 (farm v1/v2/v3/320): writing the unk_20 wrap test as `(gWaveState.unk_20 < gWaveState.posX) != 0`
// (an explicit boolean compare instead of the bare condition): 345 -> 320. The other candidate edits
// (`!= 0U`, comma-noise `((0, gWaveState)).rotation`, statement line joins) are equivalent or worse noise.

extern unk_D_80078A60 D_80078A60[8][16];
extern f32 D_8007D4D0;
extern f32 D_8007D4D4;

s16 GbAudio_RenderWave(void) {
    s32 i;
    s32 nr43;
    s32 row;
    s32 changed;
    u32 nr44;
    u16 col;
    unk_D_80078A60* entry;
    u8 sampleId;
    s16 sample;
    f32 fv;
    unk_D_800FC6CC* ent;

    changed = 0;
    for (i = 0x10; i < 0x14; i++) {
        if (((u8*)&gGbSoundRegs[i])[1] != 0) {
            changed = 1;
            ((u8*)&gGbSoundRegs[i])[1] = 0;
        }
    }

    if (changed) {
        nr43 = ((u8*)&gGbSoundRegs[0x12])[0];
        row = nr43 & 7;
        col = (((u8*)&gGbSoundRegs[0x12])[0] & 0xF0) >> 4;
        entry = &D_80078A60[row][col];
        sampleId = entry->posX;
        if (sampleId == 0xFF) {
            gWaveState.unk_28 = 0;
            return 0;
        }
        if (((u8*)&gGbSoundRegs[0x12])[0] & 8) {
            sampleId += 0x10;
        }
        gWaveState.unk_0C = D_80078A60[nr43 & 7][col].rotation;
        if (sampleId != gWaveState.rotation) {
            gWaveState.rotation = sampleId;
            ent = (unk_D_800FC6CC*)((u32*)gAudioSeqTOC + (gWaveState.rotation << 1));
            Rom_DmaRead(ent->posX, (u32)gAudioSfxDataBuffer, ent->rotation);
        }

        gWaveState.RentalSlotAnimData_PosePhase = 0;
        gWaveState.unk_10 = 0;
        if (!(((u8*)&gGbSoundRegs[0x11])[0] & 8) && !(((u8*)&gGbSoundRegs[0x11])[0] & 0xF0)) {
            gWaveState.unk_28 = 0;
            ((u8*)&gGbSoundRegs[0x16])[0] &= 0xFFF7;
            return 0;
        }
        if ((((u8*)&gGbSoundRegs[0x11])[0] & 8) && !(((u8*)&gGbSoundRegs[0x11])[0] & 0xF0) && !(((u8*)&gGbSoundRegs[0x11])[0] & 7)) {
            gWaveState.unk_28 = 0;
            ((u8*)&gGbSoundRegs[0x16])[0] &= 0xFFF7;
            return 0;
        }

        nr44 = ((u8*)&gGbSoundRegs[0x13])[0];
        if (nr44 & 0x80) {
            fv = D_8007D4D0;
            gWaveState.posX = 0;
            gWaveState.unk_28 = 1;
            gWaveState.unk_14 = (u8)(((u8*)&gGbSoundRegs[0x11])[0] & 0xF0) * fv;
            if (((u8*)&gGbSoundRegs[0x11])[0] & 7) {
                if (((u8*)&gGbSoundRegs[0x11])[0] & 8) {
                    gWaveState.unk_18 = fv;
                } else {
                    gWaveState.unk_18 = D_8007D4D4;
                }
                gWaveState.unk_20 = gWaveState.unk_1C = (((u8*)&gGbSoundRegs[0x11])[0] & 7) * D_800FD004 * 4;
            } else {
                gWaveState.unk_1C = -1;
                gWaveState.unk_20 = -1;
                gWaveState.unk_18 = 0.0f;
            }
            if (nr44 & 0x40) {
                gWaveState.unk_24 = (0x40 - (((u8*)&gGbSoundRegs[0x10])[0] & 0x3F)) * D_800FD004;
            } else {
                gWaveState.unk_24 = -1;
            }
            ((u8*)&gGbSoundRegs[0x13])[0] = nr44 & 0xFF7F;
        }
        if (gWaveState.unk_28 == 0) {
            return 0;
        }
    } else if (gWaveState.unk_28 == 0) {
        return 0;
    }

    if (gWaveState.unk_24 < gWaveState.posX) {
        gWaveState.unk_28 = 0;
        ((u8*)&gGbSoundRegs[0x16])[0] &= 0xFFF7;
        return 0;
    }

    if (gWaveState.unk_20 < gWaveState.posX) {
        gWaveState.unk_20 += gWaveState.unk_1C;
        gWaveState.unk_14 += gWaveState.unk_18;
    }

    ent = (unk_D_800FC6CC*)((u32*)gAudioSeqTOC + (gWaveState.rotation << 1));
    if (1) {}
    sample = ((s16*)gAudioSfxDataBuffer)[gWaveState.RentalSlotAnimData_PosePhase];
    gWaveState.unk_10 += 1.0f;
    if (gWaveState.unk_0C <= gWaveState.unk_10) {
        gWaveState.RentalSlotAnimData_PosePhase++;
        gWaveState.unk_10 -= gWaveState.unk_0C;
        if (gWaveState.RentalSlotAnimData_PosePhase >= (ent->rotation >> 1)) {
            gWaveState.RentalSlotAnimData_PosePhase = 0;
        }
    }

    if (!(((u8*)&gGbSoundRegs[0x11])[0] & 8) && (gWaveState.unk_14 < 0.0f)) {
        gWaveState.unk_28 = 0;
        return 0;
    }
    if (gWaveState.unk_14 > 0.75f) {
        gWaveState.unk_14 = 0.75f;
        gWaveState.unk_18 = 0.0f;
        gWaveState.unk_20 = -1;
    }
    sample = sample * gWaveState.unk_14;
    gWaveState.posX += 0x100;
    return sample;
}

void GbAudio_ClearInterpolationHistory(void) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(gInterpolationHistory); i++) {
        gInterpolationHistory[i] = 0;
    }
    gInterpolationPos = 0;
}

void GbAudio_ClearOutputBuffer(void) {
    s32 i;

    for (i = 0; i < 0xB80; i++) {
        gMusicFadeBuffer[i] = 0;
    }
    gMusicFadePos = 0;
    gOutputBufferPos = 0;
}

void func_8004AD2C(void) {

}
