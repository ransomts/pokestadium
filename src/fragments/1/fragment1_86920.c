#include "global.h"

typedef struct unk_func_81206FA0 {
  /* 0x00 */ s32 unk_00;
  /* 0x04 */ s32 unk_04;
  /* 0x08 */ s32 unk_08;
  /* 0x0C */ s32 unk_0C;
} unk_func_81206FA0; // size = 0x10

typedef struct unk_D_81234690 {
    /* 0x00 */ u8  pad0[2];
    /* 0x02 */ u16 unk_02;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ s16 unk_08;
    /* 0x0A */ s16 unk_0A;
    /* 0x0C */ s16 unk_0C;
    /* 0x0E */ u8 pad0E[0x2A];
} unk_D_81234690; // size = 0x38

// .data
extern s32 D_812286EC;
extern s32 D_812286F0;

// .rodata

// .bss
extern u64 gAudioArenaBuffer[0x640];
extern u64 gAudioWorkBuffer[0x6];
extern unk_func_81206FA0 gAudioArena;
extern unk_D_81234690 gAudioConfig;
extern volatile s32 gAudioTaskPending;
extern s32 gAudioTaskId;
extern f32 gAudioTimer;
extern s32 gAudioFramesPerSec;
extern s16* D_812346E0[3];
extern s16 D_812346EC[3];
extern s16 D_812346F2;
extern s32 D_81234700;
extern volatile u32 D_812346FC;

u32 GbApu_AllocZeroed(unk_func_81206FA0* arg0, s32 arg1) {
  s32 temp_v0;
  u32 temp_a2;
  u32 var_a1;
  temp_v0 = ALIGN16(arg1);
  temp_a2 = arg0->unk_04;
  if ((arg0->unk_00 + arg0->unk_08) >= (temp_a2 + temp_v0)) {
      arg0->unk_04 += temp_v0;
      var_a1 = temp_a2;
      while (var_a1 < arg0->unk_04) {
          *((u8*)var_a1++) = 0;
      }
  } else {
      return 0;
  }
  arg0->unk_0C++;
  return temp_a2;
}

s32 GbApu_Alloc(unk_func_81206FA0* arg0, s32 arg1) {
  s32 temp_a2;
  u32 temp_v0;

  temp_v0 = ALIGN16(arg1);
  temp_a2 = arg0->unk_04;
  if ((arg0->unk_00 + arg0->unk_08) >= (arg0->unk_04 + temp_v0)) {
      arg0->unk_04 = temp_v0 + temp_a2;
  } else {
      return 0;
  }
  arg0->unk_0C++;
  return temp_a2;
}

void GbApu_InitAllocator(unk_func_81206FA0* arg0, s32 arg1, s32 arg2) {
  arg0->unk_00 = ALIGN16(arg1);
  arg0->unk_04 = ALIGN16(arg1);
  arg0->unk_08 = (s32) (arg2 - (arg1 & 0xF));
  arg0->unk_0C = 0;
}

void GbPak_InitGfx(void) {
    u64* var_v0_2;
    s16* var_v1_2;
    s32 var_a0;
    u32 var_v1;
    s16* var_v1_3;
    s32 i;

    D_812346FC = 0;
    for (i = 0; i < D_812286EC / 8; i++) {
        gAudioArenaBuffer[i] = 0;
    }
    var_v0_2 = gAudioWorkBuffer;
    var_v1 = (u32) ((s32) &D_81234700 - (s32) gAudioWorkBuffer) >> 3;
    if ((s32) var_v1 >= 0) {
        do {
            var_v1--;
            *var_v0_2 = 0;
            ++var_v0_2;
        } while ((s32) var_v1 >= 0);
    }
    gAudioTimer = 16.713f;
    gAudioFramesPerSec = 0x3C;
    do {} while (0);
    gAudioConfig.unk_02 = 0xBB80;
    gAudioConfig.unk_04 = osAiSetFrequency(gAudioConfig.unk_02);
    gAudioConfig.unk_06 = (s16) (((gAudioConfig.unk_02 / gAudioFramesPerSec) + 0xF) & ~0xF);
    var_v1_2 = (s16*) &D_812346EC;
    gAudioConfig.unk_0A = (s16) (gAudioConfig.unk_06 - 0x10);
    gAudioConfig.unk_08 = (s16) (gAudioConfig.unk_06 + 0x10);
    do {
        *var_v1_2 = 0xA0;
        var_v1_2++;
    } while (var_v1_2 < (s16*) &D_812346F2);
    gAudioTaskPending = 0;
    gAudioTaskId = 0;
    GbApu_InitAllocator(&gAudioArena, (s32) gAudioArenaBuffer, D_812286F0);
    for (i = 0; i < 3; i++) {
        D_812346E0[i] = (s16*) GbApu_Alloc(&gAudioArena, 0xFC0);
        var_v1_3 = D_812346E0[i];
        for (var_a0 = 0; var_a0 != 0xFC0 / 2; var_a0++) {
            *var_v1_3 = 0;
            var_v1_3++;
        }
    }
}
