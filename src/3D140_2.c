#include "3D140.h"
#include "lib/ultralib/include/PR/leo.h"
#include "src/373A0.h"
#include "src/libnumus/player.h"
#include "src/3D140.h"
#include "src/435D0.h"
#include "src/libnaudio/n_libaudio_sc.h"
#include "src/libnaudio/n_libaudio_sn_sc.h"
#include "src/45720.h"
#include "src/4A3E0.h"
#include "src/4BDC0.h"

typedef union {
    struct {
        s16 type;
    } gen;
    struct {
        s16 type;
        struct AudioInfo* info;
    } done;
} AudioMsg; // size = 0x8

typedef struct AudioInfo {
    /* 0x00 */ s16* data;
    /* 0x04 */ s16 frameSamples;
    /* 0x08 */ AudioMsg msg;
} AudioInfo; // size = 0x10

#define NUM_ACMD_LISTS 2
#define NUM_OUTPUT_BUFFERS 2
#define MAX_MESGS 3
#define NUM_DMA_BUFFERS 48
#define SAMPLES 184

typedef struct AMAudioMgr {
    /* 0x000 */ Acmd* ACMDList[NUM_ACMD_LISTS];
    /* 0x008 */ AudioInfo* audioInfo[NUM_OUTPUT_BUFFERS];
    /* 0x010 */ char unk10[0x228];
    ///* 0x010 */ OSThread thread;
    ///* 0x1C0 */ OSMesgQueue audioFrameMsgQ;
    ///* 0x1D8 */ OSMesg audioFrameMsgBuf[MAX_MESGS];
    ///* 0x1E0 */ OSMesgQueue audioReplyMsgQ;
    ///* 0x1F8 */ OSMesg audioReplyMsgBuf[MAX_MESGS];
    /* 0x238 */ ALGlobals g;
} AMAudioMgr; // size = 0x288

typedef struct AMDMABuffer {
    /* 0x00 */ ALLink node;
    /* 0x08 */ u32 startAddr;
    /* 0x0C */ u32 lastFrame;
    /* 0x10 */ char* ptr;
} AMDMABuffer; // size = 0x14

typedef struct AMDMAState {
    /* 0x00 */ u8 initialized;
    /* 0x04 */ AMDMABuffer* firstUsed;
    /* 0x08 */ AMDMABuffer* firstFree;
} AMDMAState; // size = 0xC

typedef struct unk_D_800FCB48 {
    /* 0x00 */ u16 unk_00[16];
    /* 0x20 */ s32 unk_20;
    /* 0x24 */ s32 unk_24;
    /* 0x28 */ u16 unk_28[16];
    /* 0x48 */ s32 unk_48;
    /* 0x4C */ s32 unk_4C;
    /* 0x50 */ u16 unk_50[16];
    /* 0x70 */ s32 unk_70;
    /* 0x74 */ s32 unk_74;
    /* 0x78 */ u32 unk_78;
    /* 0x7C */ u32 unk_7C;
    /* 0x80 */ s32 unk_80;
} unk_D_800FCB48; // size = 0x84

typedef struct unk_D_80078548 {
    /* 0x00 */ u8 unk_00;
    /* 0x01 */ u8 unk_01;
} unk_D_80078548;

// .data
extern u8 gMusicEnabled[];// = { 0, 0, 0, 0 };
extern f32 gMusicVolume;// = 0.8000000119f;
extern u8 D_80077D98[];// = { 0, 0, 0, 0 };
extern u8 gMusicFadeState[];// = { 0, 0, 0, 0 };
extern u16 gMusicFadeTargetTrack;
extern u32 gMusicFadeTimer;
extern u8 D_80077DA8;
extern s32 gAudioUnitReady;
extern u32 audFrameCt;
extern u32 nextDMA;
extern u32 curAcmdList;
extern AudioInfo* lastInfo;
extern s32 min_only_one;
// global
extern s32 mus_active_fade_handle;
extern f32 mus_fade_start_volume;
extern u8 mus_fade_target_volume;
extern f32 mus_fade_step_rate;
extern f32 gMusicChannel2Volume;
extern f32 gMusicChannel2Step;
extern f32 D_80077DDC;
extern f32 D_80077DE0;
extern u8 mus_sound_effect_blocked;

extern u16 D_80077DF0[];
extern u16 D_80077E00[];
extern u16 D_80077E10[];
extern u16 D_80077E18[];
extern u16 D_80077E20[];
extern u16 D_80077E28[];
extern u16 D_80077E30[];
extern u16 D_80077E38[];
extern u16 D_80077E40[];
extern u16 D_80077E48[];
extern u16 D_80077E50[];
extern u16 D_80077E58[];
extern u16 D_80077E60[];
extern u16 D_80077E68[];
extern u16 D_80077E70[];
extern u16 D_80077E78[];
extern u16 D_80077E88[];
extern u16 D_80077E90[];
extern u16 D_80077E98[6];
extern u16 D_80077EA4[7];
extern u16 D_80077EB4[6];
extern u16 D_80077EC0[6];
extern u16 D_80077ECC[6];
extern u16 D_80077ED8[5];
extern u16 D_80077EE4[6];
extern u16 D_80077EF0[4];
extern u16 D_80077EF8[5];
extern u16 D_80077F04[3];
extern u16 D_80077F0C[4];
extern u16 D_80077F14[3];
extern u16 D_80077F1C[3];
extern u16 D_80077F24[3];
extern u16 D_80077F2C[3];
extern u16 D_80077F34[3];
extern u16 D_80077F3C[3];
extern u16 D_80077F44[6];
extern u16 D_80077F50[3];
extern u16 D_80077F58[3];
extern u16 D_80077F60[6];
extern u16 D_80077F6C[];
extern u16 D_80077F74[];
extern u16 D_80077F7C[];
extern u16 D_80077F88[];
extern u16 D_80077F90[];
extern u16 D_80077F98[];
extern u16 D_80077FA4[];
extern u16 D_80077FAC[];
extern u16 D_80077FB4[];
extern u16 D_80077FC0[];
extern u16 D_80077FC8[];
extern u16 D_80077FD0[];
extern u16 D_80077FD8[];
extern u16 D_80077FE4[];
extern u16 D_80077FEC[];
extern u16 D_80077FF4[];
extern u16 D_80077FFC[];
extern u16 D_80078004[];
extern u16 D_8007800C[];
extern u16 D_80078014[];
extern u8 D_8007801C[8];
extern u8 D_80078024[10];
extern u8 D_80078030[6];
extern u8 D_80078038[6];
extern u16 D_80078040[];
extern u16 D_80078048[];
extern u16 D_80078050[3];
extern u16 D_80078058[3];
extern u16 D_80078060[3];
extern u16 D_80078068[];
extern u8 D_80078070[8];
extern u16 D_80078078[3];
extern u16 D_80078080[3];
extern u16 D_80078088[3];
extern u16 D_80078090[4];
extern u16 D_80078098[3];
extern u16 D_800780A0[3];
extern u16 D_800780A8[];
extern u8 D_800780B3[]; // needs addressing
extern u8 D_800780B4[];
extern u8 D_80078180[];
extern u8 D_800781E0[];
extern u8 D_800782A4[];
extern s32 gAudioActiveFlag;
extern u8 gTeamScores[4];
extern u8 D_80078390[2];
extern u8 D_80078394[4];
extern u8 gPlayerSideMap[4];
extern u8 D_8007839C[];
extern u8 D_800783A0;
extern u32 D_800783A4[4];
extern u32 D_800783B4;
extern s32 D_800783B8;
extern u8 D_800783BC;
extern u8 D_800783C0;
extern u8 D_800783C4;
extern u32 D_800783C8;
extern u32 D_800783CC;
extern u8 D_800783D0;
extern u8 D_800783D4;
extern u8 D_800783D8;
extern u8 D_800783DC;
extern u8 D_800783E0;
extern u8 D_800783E4;
extern u8 D_800783E8;
extern u8 D_800783EC;
extern s16 D_800783F0;
extern s16 D_800783F4;
extern s16 D_800783F8;
extern u8 D_800783FC;
extern u8 D_80078400;
extern u32 D_80078404;
extern s32 D_80078408;
extern u8 D_8007840C;
extern u16 D_80078410[17][9];
extern u16 D_80078446[1][9];
extern u16 D_800784EA[1][9];
extern u32 gCommandQueueCount;
extern unk_D_80078548 D_80078548[];
extern u8 D_80078554[];
extern u8 D_80078568[];

u8 gMusicEnabled[4] = { 0, 0, 0, 0 };
f32 gMusicVolume = 0.8f;
u8 D_80077D98[4] = { 1, 0, 0, 0 };
u8 gMusicFadeState[4] = { 0, 0, 0, 0 };
u16 gMusicFadeTargetTrack = 0;
u32 gMusicFadeTimer = 0;
u8 D_80077DA8 = 0;
s32 gAudioUnitReady = 0;
u32 audFrameCt = 0;
u32 nextDMA = 0;
u32 curAcmdList = 0;
AudioInfo* lastInfo = NULL;
s32 min_only_one = 1;
s32 mus_active_fade_handle = 0;
f32 mus_fade_start_volume = 0.0f;
u8 mus_fade_target_volume = 0;  // tail holds D_80077DCD (linker-defined symbols)
f32 mus_fade_step_rate = 0.0f;
f32 gMusicChannel2Volume = 0.0f;
f32 gMusicChannel2Step = 0.0f;
f32 D_80077DDC = 0.0f;
f32 D_80077DE0 = 0.0f;
u8 mus_sound_effect_blocked = 0;
u32 D_80077DE8[2] = { 0, 0 };
u16 D_80077DF0[8] = { 7, 0x24F, 0x250, 0x255, 0x271, 0x273, 0x289, 0x28F };
u16 D_80077E00[8] = { 6, 0x269, 0x26C, 0x26D, 0x26E, 0x287, 0x288, 0 };
u16 D_80077E10[4] = { 3, 0x281, 0x282, 0x283 };
u16 D_80077E18[4] = { 3, 0x27E, 0x27F, 0x280 };
u16 D_80077E20[4] = { 3, 0x24D, 0x278, 0x279 };
u16 D_80077E28[4] = { 3, 0x24C, 0x274, 0x275 };
u16 D_80077E30[4] = { 3, 0x24B, 0x276, 0x277 };
u16 D_80077E38[4] = { 2, 0x27C, 0x27D, 0 };
u16 D_80077E40[4] = { 2, 0x27A, 0x27B, 0 };
u16 D_80077E48[4] = { 3, 0x252, 0x270, 0x272 };
u16 D_80077E50[4] = { 3, 0x284, 0x285, 0x286 };
u16 D_80077E58[4] = { 3, 0x259, 0x28B, 0x28C };
u16 D_80077E60[4] = { 3, 0x25A, 0x28A, 0x28C };
u16 D_80077E68[4] = { 3, 0x24E, 0x258, 0x28E };
u16 D_80077E70[4] = { 2, 0x251, 0x28D, 0 };
u16 D_80077E78[8] = { 6, 0x24F, 0x250, 0x255, 0x271, 0x289, 0x28F, 0 };
u16 D_80077E88[4] = { 3, 0x253, 0x26F, 0x291 };
u16 D_80077E90[4] = { 2, 0x252, 0x270, 0 };
u16 D_80077E98[6] = { 5, 0x62, 0x67, 0x6E, 0x8D, 0x8E };
u16 D_80077EA4[7] = { 6, 0x6D, 0x72, 0x89, 0x8A, 0x8B, 0x8C };
u16 D_80077EB4[6] = { 5, 0x6F, 0x70, 0x9F, 0xA0, 0xA1 };
u16 D_80077EC0[6] = { 5, 0x60, 0x65, 0x92, 0x93, 0x94 };
u16 D_80077ECC[6] = { 5, 0x61, 0x66, 0x95, 0x96, 0x97 };
u16 D_80077ED8[5] = { 4, 0x69, 0x98, 0x99, 0x9A };
u16 D_80077EE4[6] = { 5, 0x63, 0x64, 0x8F, 0x90, 0x91 };
u16 D_80077EF0[4] = { 3, 0x6A, 0x9B, 0x9C };
u16 D_80077EF8[5] = { 4, 0x6B, 0x6C, 0x9D, 0x9E };
u16 D_80077F04[3] = { 2, 0x8A, 0x8B };
u16 D_80077F0C[4] = { 3, 0x7C, 0x86, 0xAC };
u16 D_80077F14[3] = { 2, 0x7E, 0x7F };
u16 D_80077F1C[3] = { 2, 0xAE, 0xAF };
u16 D_80077F24[3] = { 2, 0x82, 0x83 };
u16 D_80077F2C[3] = { 2, 0x72, 0x8A };
u16 D_80077F34[3] = { 2, 0x85, 0x84 };
u16 D_80077F3C[3] = { 2, 0x88, 0x71 };
u16 D_80077F44[6] = { 5, 0x62, 0x67, 0x6E, 0x8D, 0x8E };
u16 D_80077F50[3] = { 2, 0x80, 0x81 };
u16 D_80077F58[3] = { 2, 0xB3, 0xB4 };
u16 D_80077F60[6] = { 5, 0x72, 0x89, 0x8A, 0x8B, 0x8C };
u16 D_80077F6C[4] = { 3, 0x1D, 0x1E, 0x1F };
u16 D_80077F74[4] = { 3, 0x20, 0x21, 0x22 };
u16 D_80077F7C[6] = { 4, 0x19, 0x1A, 0x1B, 0x1C, 0 };
u16 D_80077F88[4] = { 2, 0x1A, 0x1B, 0 };
u16 D_80077F90[4] = { 3, 0x18, 0x1B, 0x1C };
u16 D_80077F98[6] = { 4, 0x14, 0x15, 0x16, 0x17, 0 };
u16 D_80077FA4[4] = { 2, 0x10, 0x11, 0 };
u16 D_80077FAC[4] = { 2, 0x12, 0x13, 0 };
u16 D_80077FB4[6] = { 4, 0xB7, 0xB8, 0xB9, 0xBA, 0 };
u16 D_80077FC0[4] = { 3, 0xBD, 0xBE, 0xBF };
u16 D_80077FC8[4] = { 2, 0xC0, 0xC1, 0 };
u16 D_80077FD0[4] = { 3, 0xBB, 0xC6, 0xC7 };
u16 D_80077FD8[6] = { 4, 0x50, 0x51, 0x52, 0x53, 0 };
u16 D_80077FE4[4] = { 2, 0x56, 0x57, 0 };
u16 D_80077FEC[4] = { 2, 0x59, 0x5A, 0 };
u16 D_80077FF4[4] = { 2, 0xB, 0xC, 0 };
u16 D_80077FFC[4] = { 2, 4, 3, 0 };
u16 D_80078004[4] = { 2, 5, 3, 0 };
u16 D_8007800C[4] = { 2, 8, 0xD, 0 };
u16 D_80078014[4] = { 2, 0xE, 0xF, 0 };
u8 D_8007801C[8] = { 0, 3, 1, 0x81, 1, 0x9D, 1, 0x9E };
u8 D_80078024[10] = { 0, 4, 1, 0x7C, 1, 0x82, 1, 0x9D, 1, 0x9E };
u8 D_80078030[6] = { 0, 2, 1, 0x7C, 1, 0x9E };
u8 D_80078038[6] = { 0, 2, 1, 0x80, 1, 0x98 };
u16 D_80078040[4] = { 2, 0x180, 0x17C, 0 };
u16 D_80078048[4] = { 3, 0x179, 0x19D, 0x19E };
u16 D_80078050[3] = { 2, 0x177, 0x178 };
u16 D_80078058[3] = { 2, 0x183, 0x184 };
u16 D_80078060[3] = { 2, 0x184, 0x185 };
u16 D_80078068[4] = { 3, 0x172, 0x173, 0x174 };
u8 D_80078070[8] = { 0, 3, 0, 0x71, 0, 0xA8, 0, 0xA9 };
u16 D_80078078[3] = { 2, 0x73, 0x74 };
u16 D_80078080[3] = { 2, 0x175, 0x176 };
u16 D_80078088[3] = { 2, 0x7D, 0xAA };
u16 D_80078090[4] = { 3, 0x7D, 0xAA, 0xAB };
u16 D_80078098[3] = { 2, 0x199, 0x19A };
u16 D_800780A0[3] = { 2, 0x19B, 0x19C };
u16 D_800780A8[6] = { 5, 0x5B, 0x5C, 0x5D, 0x5E, 0x5F };
u8 D_800780B4[204] = { 0, 0x28, 0, 0, 0x32, 0, 0x1D, 0xF, 0, 0x1D, 0x12, 0, 0, 0x50, 0, 0x10, 0x28, 0, 4, 0x4B, 0x14, 5, 0x4B, 0x19, 6, 0x4B, 0x17, 0, 0x28, 0, 0, 0x37, 0, 0x26, 1, 0, 0x27, 0x50, 0, 0x32, 0, 0, 0, 0x32, 0, 0, 0x28, 0, 0, 0x23, 2, 0x1C, 0, 0, 0x2B, 0x46, 2, 0x2A, 0xF, 0, 0, 0x50, 0, 0, 0x23, 0x16, 0x25, 0x41, 0, 0x2C, 0x1E, 1, 0, 0x78, 0, 0x2D, 0x46, 1, 0x25, 0x3C, 1, 0x16, 0, 0, 0x25, 0x46, 0, 0, 0x41, 0, 0x1D, 0xF, 0, 0x26, 1, 0, 0, 0x23, 0, 0x24, 0x55, 0, 0x2A, 0xF, 0, 0x30, 0x5A, 0, 0x1B, 0x5A, 0, 0x30, 0x64, 0, 0x13, 0, 0, 2, 0xF, 3, 0x4D, 0x19, 7, 0x1D, 0xE, 7, 0x13, 0, 0, 0x1F, 0x3C, 0, 0x12, 0, 0, 0x1C, 0, 0, 0x20, 0, 0, 0x31, 0, 0, 0x29, 1, 0, 0x56, 0, 0, 0x45, 0x28, 3, 4, 0x28, 0x14, 4, 0x5F, 0x14, 0x2E, 0, 0x19, 0, 0x28, 0x15, 0, 0x78, 0x15, 0, 0x5F, 0x15, 5, 0x5F, 0x19, 0x23, 0x78, 0x19, 0x4C, 0x41, 0x18, 0x46, 0x41, 0x15, 0x44, 0x41, 0x19, 0x50, 0x96, 0, 0, 0x23, 2, 0, 0x50, 2, 0x30, 0x50, 1, 0x25, 0x32, 1, 0, 1, 1 };
u8 D_80078180[96] = { 0x29, 1, 1, 0, 0x50, 0, 3, 0x14, 0x16, 3, 0x28, 0x16, 0x54, 0, 0x16, 0xD, 0, 0, 0, 0x37, 0x16, 0x27, 0x78, 0x16, 0x42, 0, 3, 0x43, 0, 0x16, 0x20, 0, 0x16, 0x1B, 0x46, 0x16, 0x14, 0, 7, 0x29, 1, 0x1A, 0x2A, 0xF, 0x14, 6, 0x28, 0x17, 6, 0x5F, 0x17, 0x43, 0, 0x17, 6, 0x78, 0x17, 0, 0x32, 5, 0, 0x64, 4, 0x26, 1, 4, 0x27, 0x64, 4, 0x42, 0, 3, 0x4C, 0x32, 0x18, 0x47, 0x5A, 0x18, 0x20, 0, 0x18, 0xA, 0, 0x18, 0x34, 0, 0x18, 0, 0x28, 0, 0x51, 0x14, 0, 0x1C, 0, 0x18 };
u8 D_800781E0[196] = { 0x29, 0, 8, 0x52, 0, 0, 0x3B, 0, 0, 0xF, 0, 0, 0x38, 0, 0, 0xB, 0, 0, 0xF, 0, 0, 0x16, 0, 0, 0x31, 0, 8, 0xB, 0, 0x15, 0xB, 0, 0, 0x33, 0, 0x18, 0x40, 0, 0x18, 0x19, 0, 0x19, 0x41, 0, 0x18, 0x2F, 0, 0, 0x1A, 0, 0, 0x53, 0, 0, 9, 0, 2, 7, 0x82, 0, 0, 0x64, 0, 0x24, 0x14, 8, 0x21, 0x14, 3, 0x21, 0x41, 3, 0x1F, 0x41, 4, 0x22, 0x78, 0x14, 0, 0x50, 0x15, 0x2A, 0x23, 0x15, 0x11, 0x3C, 0, 0x27, 0x64, 0, 0x1D, 0x14, 0, 0x46, 0xA, 0, 0x35, 0, 0x18, 0x16, 0, 0x18, 0x38, 0, 0, 0x2D, 0x55, 1, 0x43, 0, 0, 8, 0x64, 0x18, 0x42, 0, 3, 0x1D, 0xF, 0, 3, 0x14, 7, 0x20, 0, 0, 0x27, 0x8C, 2, 0x39, 0, 0, 0x46, 0x14, 0x15, 0, 0x46, 0, 0x20, 0, 0x16, 0x16, 0, 0, 0x29, 1, 0x18, 0x55, 0, 0, 0x33, 0, 3, 0, 0x5A, 0x15, 7, 0xAA, 0, 0x1D, 0x12, 0, 0x2C, 0x32, 4, 0x38, 0, 0x18, 0, 0x4B, 5, 0x1F, 0x50, 0, 0xA, 0, 0, 0x18, 0, 0, 0, 0x50, 0, 0x28, 1, 0, 0, 0x46, 0, 0x4F, 0, 0, 0x30, 0x32, 0, 0 };
u8 D_800782A4[228] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 1, 0, 0, 2, 2, 0, 3, 3, 0, 0, 0, 0, 0, 3, 2, 0, 2, 0, 3, 2, 2, 2, 0, 0, 0, 3, 0, 0, 0, 3, 0, 2, 0, 0, 3, 2, 2, 0, 0, 0, 1, 3, 0, 0, 0, 0, 2, 0, 2, 3, 0, 2, 0, 0, 2, 3, 2, 0, 2, 3, 0, 2, 0, 2, 2, 0, 3, 2, 0, 0, 3, 3, 0, 0, 3, 0, 3, 3, 0, 0, 0, 0, 3, 0, 2, 0, 2, 2, 2, 3, 1, 0, 0, 0, 0, 0, 3, 0, 0, 2, 2, 0, 0, 3, 2, 2, 0, 0, 3, 0, 3, 2, 0, 0, 3, 0, 1, 0, 2, 3, 0, 0, 0, 0, 0, 2, 3, 0, 3, 0, 0, 0, 0, 3, 2, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 0, 0, 2, 0, 0, 0, 0, 0, 2, 0, 0, 3, 0, 2, 0, 0, 2, 3, 0, 0, 2, 0, 0, 3, 0, 0, 0, 3, 2, 0, 2, 3, 0, 3, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0 };
s32 gAudioActiveFlag = 1;
u8 gTeamScores[4] = { 3, 3, 3, 3 };
u8 D_80078390[2] = { 3, 3 };
u8 D_80078394[4] = { 0, 1, 0, 0 };
u8 gPlayerSideMap[4] = { 1, 2, 1, 2 };
u8 D_8007839C[4] = { 0, 0, 0, 0 };
u8 D_800783A0 = 0;
u32 D_800783A4[4] = { 0, 0, 0, 0 };
u32 D_800783B4 = 0;
s32 D_800783B8 = 0;
u8 D_800783BC = 0;
u8 D_800783C0 = 0;
u8 D_800783C4 = 0;
u32 D_800783C8 = 0;
u32 D_800783CC = 0;
u8 D_800783D0 = 0;
u8 D_800783D4 = 0;
u8 D_800783D8 = 0;
u8 D_800783DC = 0;
u8 D_800783E0 = 0;
u8 D_800783E4 = 0;
u8 D_800783E8 = 0;
u8 D_800783EC = 0;
s16 D_800783F0 = 0;
s16 D_800783F4 = 0;
s16 D_800783F8 = 0;
u8 D_800783FC = 1;
u8 D_80078400 = 1;
u32 D_80078404 = 0;
s32 D_80078408 = 0;
u8 D_8007840C = 0;
u16 D_80078410[17][9] = { { 0x35, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A }, { 0x35, 0x2B, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A }, { 0x35, 0x2C, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A }, { 0x35, 0x2D, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A }, { 0x37, 0x2F, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A }, { 0x36, 0x2E, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A }, { 0x38, 0x30, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A }, { 0x38, 0x31, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A }, { 0x38, 0x32, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A }, { 0x38, 0x33, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A }, { 0x38, 0x30, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A }, { 0x38, 0x30, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A }, { 0, 0x39, 0x4C, 0x4E, 0x3A, 0x4A, 0x4D, 0x4F, 0x3B }, { 0, 0x4B, 0x4C, 0x4E, 0x3C, 0x4A, 0x4D, 0x4F, 0x3D }, { 0, 0x4B, 0x4C, 0x4E, 0x3E, 0x4A, 0x4D, 0x4F, 0x3F }, { 0, 0x4B, 0x4C, 0x4E, 0x40, 0x4A, 0x4D, 0x4F, 0x41 }, { 0, 0x42, 0x43, 0x44, 0x45, 0x46, 0, 0, 0 } };  // tail holds D_80078446, D_800784EA (linker-defined symbols)
u32 gCommandQueueCount = 0;
unk_D_80078548 D_80078548[6] = { { 3, 0x29 }, { 0x8C, 0x83 }, { 0x18, 0x1F }, { 0x9A, 4 }, { 0x9B, 0x2A }, { 0, 0 } };
u8 D_80078554[20] = { 0xE, 0x36, 0x4A, 0x60, 0x61, 0x68, 0x6A, 0x6B, 0x6E, 0x6F, 0x70, 0x71, 0x73, 0x74, 0x85, 0x97, 0x9F, 0, 0, 0 };
u8 D_80078568[24] = { 0x1C, 0x27, 0x2B, 0x2D, 0x51, 0x67, 0x6C, 0x86, 0x94, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

// .rodata

// const f64 D_8007C7E0 = 0.699999999999999956f;
// const f64 D_8007C7E8 = 0.599999999999999978f;
// const f64 D_8007C7F0 = 0.400000000000000022f;
// const f64 D_8007C7F8 = 0.299999999999999989f;

// const f32 D_8007CB80 = 1.100000024f;
// const f32 D_8007CB84 = 1.100000024f;
// const f32 D_8007CB88 = 1.200000048f;
// const f32 D_8007CB8C = 1.100000024f;
// const f32 D_8007CB90 = 0.009999999776f;

extern f64 D_8007C7E0;
extern f64 D_8007C7E8;
extern f64 D_8007C7F0;
extern f64 D_8007C7F8;

extern f32 D_8007CB80;
extern f32 D_8007CB84;
extern f32 D_8007CB88;
extern f32 D_8007CB8C;
extern f32 D_8007CB90;

// .bss
extern s32 D_800FC820;
extern s8 D_800FC824;
extern u8 D_800FC825;
extern s32 D_800FC828;
extern AMAudioMgr __am;
extern AMDMAState dmaState;
extern s32 minFrameSize;
extern u32 frameSize;
extern s32 maxFrameSize;
extern s32 maxRSPCmds;
extern s32 gAudioOutputRate;
extern s32 D_800FCAD8;
extern OSMesgQueue audDMAMessageQ;
extern AMDMABuffer* dmaBuffs;
extern OSIoMesg* audDMAIOMesgBuf;
extern OSMesg* audDMAMessageBuf;
extern u32 dmaBufferLen;
extern OSPiHandle* gAudioPiHandle[4];
// s32 D_800FCB0C[3];
extern unk_D_800FCB18* gAudioInfoPtr[4];
extern u32 D_800FCB28[2];
extern u8 D_800FCB30[2];
extern u8 D_800FCB38[2][8];
extern unk_D_800FCB48 gHPHistory[2];
extern s32 D_800FCC50[20];
extern u8 D_800FCCA0;
extern u8 D_800FCCA1;
extern u8 D_800FCCA2;
extern u32 D_800FCCA4;
extern s32 D_800FCCA8;
extern u8 D_800FCCAC;
extern u8 D_800FCCAD;
extern u8 D_800FCCAE;
extern u8 D_800FCCAF;
extern u8 D_800FCCB0;
extern u8 D_800FCCB1;
extern u8 D_800FCCB2;
extern u8 D_800FCCB3;
extern u8 D_800FCCB4;
extern u8 D_800FCCB5;
extern u8 D_800FCCB6;
extern u8 D_800FCCB7;
extern u8 D_800FCCB8[2];
extern u8 D_800FCCBA[2];
extern u8 D_800FCCBC[2];
extern u8 D_800FCCBE[2];
extern u8 D_800FCCC0[2];
extern u8 D_800FCCC2[2];
extern u8 D_800FCCC4[2];
extern u8 D_800FCCC6[2];
extern u8 D_800FCCC8[2];
extern u8 D_800FCCCA[2];
extern u8 D_800FCCCC[2];
extern u8 D_800FCCCE[2];
extern u8 D_800FCCD0[2];
extern u8 D_800FCCD2[2];
extern u8 D_800FCCD4[2];
extern u8 D_800FCCD6[2];
extern s8 D_800FCCD8[0x18];
extern u32 D_800FCCF0[10];
extern u8 D_800FCD18[0x28];

// function prototypes
void func_800420F0(u16, u16*, u8*);
u32 func_80042158(u32, unk_D_800FCB18*, unk_D_800FCB18*);
s32 func_80042850(u8);
ALDMAproc __amDmaNew(AMDMAState** state);

/**
 * Sets or clears a bit in an array.
 */
void SetBitInArray(u8* array, u8 index, u8 flag) {
    u8 offset = index / 8;
    u8 bitPosition = index % 8;
    u8 mask = (1 << bitPosition);
    if (flag) {
        array[offset] |= mask;   // Set the bit
    } else {
        array[offset] &= ~mask;  // Clear the bit
    }
}

/**
 * Checks if a bit is set in an array.
 */
s32 IsBitSetInArray(u8* array, u8 index) {
    u8 offset = index / 8;
    u8 bitPosition = index % 8;
    u8 flag = (array[offset] & (u8)(1 << bitPosition));
    if (flag) {
        return 1;
    }
    return 0;
}

void SetAudioActiveFlag(s32 arg0) {
    if (arg0 != 0) {
        gAudioActiveFlag = 1;
    } else {
        gAudioActiveFlag = 0;
    }
}

void SetTeamScores(u8 arg0, u8 arg1, u8 arg2, u8 arg3) {
    gTeamScores[0] = arg0;
    gTeamScores[1] = arg1;
    gTeamScores[2] = arg2;
    gTeamScores[3] = arg3;
}

void ResetPlayerData(u8 arg0) {
    s32 i;

    if (arg0 < 3) {
        for (i = 0; i < 16; i++) {
            gHPHistory[arg0].unk_00[i] = 0;
            gHPHistory[arg0].unk_28[i] = 0;
            gHPHistory[arg0].unk_50[i] = 0;
        }
        gHPHistory[arg0].unk_20 = 0;
        gHPHistory[arg0].unk_24 = 0;
        gHPHistory[arg0].unk_48 = 0;
        gHPHistory[arg0].unk_4C = 0;
        gHPHistory[arg0].unk_70 = 0;
        gHPHistory[arg0].unk_74 = 0;
        gHPHistory[arg0].unk_78 = 0;
        gHPHistory[arg0].unk_7C = 0;
        gHPHistory[arg0].unk_80 = 0;
        D_800FCCBC[arg0] = 0;
        D_800FCCBE[arg0] = 0;
        D_800FCCC4[arg0] = 0;
        D_800FCCC6[arg0] = 0;
        D_800FCCC8[arg0] = 0;
        D_800FCCCA[arg0] = 0;
        D_800FCCCC[arg0] = 0;
        D_800FCCCE[arg0] = 0;
        D_800FCCD0[arg0] = 0;
        D_800FCCD2[arg0] = 0;
        D_800FCCD4[arg0] = 0;
        D_800FCCC2[arg0] = 0;
        D_800FCCC0[arg0] = 0;
    }
}

void SetPlayerSidesAndReset(u8 arg0, u8 arg1, u8 arg2, u8 arg3) {
    s32 i;
    s32 j;

    gPlayerSideMap[0] = arg0;
    gPlayerSideMap[1] = arg1;
    gPlayerSideMap[2] = arg2;
    gPlayerSideMap[3] = arg3;
    D_80078394[0] = 0xFF;
    D_80078394[1] = 0xFF;
    D_80078390[0] = 0;
    D_80078390[1] = 0;
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 4; j++) {
            if (i + 1 == gPlayerSideMap[j]) {
                D_80078390[i] += gTeamScores[j];
            }
        }
    }
    gAudioInfoPtr[0] = 0;
    gAudioInfoPtr[1] = 0;
    D_800FCB28[0] = 0;
    D_800FCB28[1] = 0;
    ResetPlayerData(0);
    ResetPlayerData(1);
}

void ProcessMenuSelection(u32 arg0, u32 arg1) {
    s32 pad[1];
    u8 sp1B = 0;
    u16 var_a0;

    func_80041A98();
    D_80078404 = arg1;
    D_80078408 = arg0;

    if (arg1 < 0x11) {
        D_800783FC = 1;
        D_8007840C = 1;

        if ((arg0 == 0) && (arg1 != 0x10) && (arg1 != 0xF)) {
            func_80041C70(0x34);
        } else if ((arg0 == 0xFF) && (arg1 != 0x10) && (arg1 != 0xF)) {
            func_80041C70(0x47);
            arg0 = 0;
            sp1B = 1;
        }

        if (arg1 < 0xC) {
            if (arg0 < 9) {
                var_a0 = D_80078410[arg1][arg0];
                D_800783FC = 1;
                D_80078400 = 1;
            } else {
                return;
            }
        } else if (arg1 == 0xC) {
            if ((arg0 < 0x21) && (arg0 != 0)) {
                var_a0 = D_800784EA[(arg0 - 1) / 8][(arg0 - 1) % 8];
                D_800783FC = 1;
                D_80078400 = 0;
            } else {
                return;
            }
        } else if (arg1 == 0xD) {
            if (arg0 < 6) {
                var_a0 = D_80078446[arg1][arg0];
                D_800783FC = 1;
                D_80078400 = 0;
            } else {
                return;
            }
        } else {
            if (arg1 == 0xE) {
                var_a0 = 0x49;
                D_800783FC = 1;
                D_80078400 = 2;
            } else if (arg1 == 0xF) {
                var_a0 = 0;
                D_800783FC = 0;
                D_80078400 = 0;
                arg0 = 1;
            } else {
                if (arg1 == 0x10) {
                    var_a0 = 0x48;
                    D_80078400 = 1;
                    arg0 = 1;
                } else {
                    var_a0 = 0;
                    D_80078400 = 1;
                }
                D_800783FC = 1;
            }
        }

        if ((arg0 == 0) && (sp1B == 0)) {
            D_80078400 = 2;
        }

        if (var_a0 != 0) {
            func_80041C70(var_a0);
        }
    }
}

void AudioFrameUpdate(s32 arg0) {
    s8 var_t0;
    s8 var_t2;
    s8 var_t4;
    s8 var_t5;
    s32 var_v0;
    s32 var_a0;
    s32 i;

    if (arg0 != 0) {
        var_v0 = osSetIntMask(1);
        D_800783BC = 1;
        D_800783C8 = 0;
        D_800783C0 = 0;
        D_800783C4 = 0;
        osSetIntMask(var_v0);
        D_800783D4 = 0;
        D_800783D8 = 0;
        D_800783DC = 0;
        D_800FCCAE = 0;
        D_800FCCAF = 0;
        D_800FCCB2 = 0;
        D_800FCCB6 = 0;
        D_800783E8 = 0;
        D_800783EC = 0;
        D_800FCCA4 = 0;
        func_800367A0(0x5A, D_80078400, 0);

        if ((gAudioInfoPtr[0] == NULL) || (gAudioInfoPtr[1] == NULL)) {
            return;
        }

        if (gAudioInfoPtr[0] != NULL) {
            D_800FCB28[0] = gAudioInfoPtr[0]->unk_0C;
        }

        if (gAudioInfoPtr[1] != NULL) {
            D_800FCB28[1] = gAudioInfoPtr[1]->unk_0C;
        }

        gHPHistory[0].unk_24++;
        gHPHistory[0].unk_00[gHPHistory[0].unk_24 & 0xF] = gAudioInfoPtr[0]->unk_0C;
        gHPHistory[1].unk_24++;
        gHPHistory[1].unk_00[gHPHistory[1].unk_24 & 0xF] = gAudioInfoPtr[1]->unk_0C;

        if (D_800783CC == 0) {
            return;
        }

        if (gAudioInfoPtr[0]->unk_26 < gAudioInfoPtr[1]->unk_26) {
            var_t2 = 0;
            var_t4 = 1;
        } else {
            var_t2 = 1;
            var_t4 = 0;
        }

        if (gAudioInfoPtr[0]->unk_0C < gAudioInfoPtr[1]->unk_0C) {
            var_t0 = 0;
            var_t5 = 1;
        } else {
            var_t0 = 1;
            var_t5 = 0;
        }

        if (D_800783CC < 2) {
            if ((gAudioInfoPtr[0]->unk_0C == 0) || (gAudioInfoPtr[1]->unk_0C == 0)) {
                var_v0 = osSetIntMask(1);
                D_800783C0 = 1;
                osSetIntMask(var_v0);

                if (gAudioInfoPtr[0]->unk_0C == 0) {
                    D_800FCCB0 = 1;
                } else {
                    D_800FCCB0 = 2;
                }

                if ((gAudioInfoPtr[0]->unk_0C == 0) && (gAudioInfoPtr[1]->unk_0C == 0)) {
                    func_800420C0(D_80077E90);
                } else {
                    func_800420C0(D_80077E48);
                }
                return;
            }

            if (((((u32)gAudioInfoPtr[0]->unk_0C * 100) / gAudioInfoPtr[0]->unk_28) < 0x1E) &&
                ((((u32)gAudioInfoPtr[1]->unk_0C * 100) / gAudioInfoPtr[1]->unk_28) < 0x1E)) {
                func_800420C0(D_80077E88);
                return;
            }

            if (((((gAudioInfoPtr[var_t4]->unk_26 - gAudioInfoPtr[var_t2]->unk_26) * 0x64U) /
                  gAudioInfoPtr[var_t2]->unk_26) >= 0x15) &&
                ((((u32)gAudioInfoPtr[var_t2]->unk_0C * 100) / gAudioInfoPtr[var_t2]->unk_28) < 0x28) &&
                ((((u32)gAudioInfoPtr[var_t4]->unk_0C * 100) / gAudioInfoPtr[var_t4]->unk_28) >= 0x51)) {
                if ((osGetTime() % 3) == 0) {
                    var_a0 = 0x256;
                    goto block_53;
                }
            }

            if (((((u32)gAudioInfoPtr[0]->unk_0C * 100) / gAudioInfoPtr[0]->unk_28) >= 0x5B) &&
                ((((u32)gAudioInfoPtr[1]->unk_0C * 100) / gAudioInfoPtr[1]->unk_28) >= 0x5B)) {
                func_800420C0(D_80077E68);
            } else if (D_80078400 == 0) {
                func_800420C0(D_80077E78);
            } else {
                func_800420C0(D_80077DF0);
            }
            return;
        }

        if ((gAudioInfoPtr[0]->unk_0C == 0) || (gAudioInfoPtr[1]->unk_0C == 0)) {
            var_v0 = osSetIntMask(1);
            D_800783C0 = 1;
            osSetIntMask(var_v0);

            if (gAudioInfoPtr[0]->unk_0C == 0) {
                D_800FCCB0 = 1;
            } else {
                D_800FCCB0 = 2;
            }

            if (D_80078390[0] >= D_80078390[1]) {
                var_v0 = D_80078390[0] - D_80078390[1];
            } else {
                var_v0 = D_80078390[1] - D_80078390[0];
            }

            if (var_v0 >= 2) {
                func_800420C0(D_80077E70);
                return;
            }

            if ((D_80078390[0] == 1) && (D_80078390[1] == 1)) {
                if (D_800783E4 != 0) {
                    D_800783E4 = 0;
                    var_a0 = 0x290;
                } else if ((osGetTime() % 2) != 0) {
                    var_a0 = 0x254;
                } else {
                    var_a0 = 0x26B;
                }
            block_53:
                func_80041C70(var_a0);
            } else if (D_80078390[D_800FCCB0 - 1] == 1) {
                func_80041C70(0x26A);
            } else {
                func_800420C0(D_80077E00);
            }
            return;
        }

        if (D_800FCCB0 != 0) {
            if (((D_80078390[0] == 1) || (D_80078390[1] == 1)) && (D_80078390[0] < 4) &&
                (D_80078390[1] < 4)) {
                if (D_80078390[0] == 1) {
                    switch (D_80078390[1]) {
                        case 1:
                            func_80041C70(0x260);
                            func_80041C70(0x266);
                            break;

                        case 2:
                            func_80041C70(0x261);
                            if (D_800FCCB0 == 1) {
                                func_80041C70(0x265);
                            } else {
                                func_80041C70(0x267);
                            }
                            break;

                        case 3:
                            func_80041C70(0x262);
                            func_80041C70(0x264);
                            break;

                        default:
                            func_80041C70(0x271);
                            break;
                    }

                    D_800FCCB0 = 0;
                    return;
                }

                switch (D_80078390[0]) {
                    case 2:
                        func_80041C70(0x25E);
                        if (D_800FCCB0 == 2) {
                            func_80041C70(0x265);
                        } else {
                            func_80041C70(0x267);
                        }
                        break;

                    case 3:
                        func_80041C70(0x25C);
                        func_80041C70(0x264);
                        break;

                    default:
                        func_80041C70(0x271);
                        break;
                }

                D_800FCCB0 = 0;
                return;
            }

            if (D_800FCCB1 != 0) {
                if ((osGetTime() % 2) != 0) {
                    D_800FCCB0 = 0;
                    func_800420C0(D_80077E10);
                    return;
                }
            }

            if (gAudioInfoPtr[0]->unk_16[6] != gAudioInfoPtr[1]->unk_16[6]) {
                if (gAudioInfoPtr[0]->unk_16[6] != gAudioInfoPtr[1]->unk_16[7]) {
                    if ((gAudioInfoPtr[0]->unk_16[7] != gAudioInfoPtr[1]->unk_16[6]) &&
                        (gAudioInfoPtr[0]->unk_16[7] != gAudioInfoPtr[1]->unk_16[7])) {
                        D_800FCCB0 = 0;
                        func_800420C0(D_80077E18);
                        return;
                    }
                }
            }

            D_800FCCB0 = 0;
            switch (D_80078390[0]) {
                case 2:
                    switch (D_80078390[1]) {
                        case 2:
                            func_80041C70(0x25D);
                            func_80041C70(0x268);
                            break;

                        case 3:
                            func_80041C70(0x25F);
                            func_80041C70(0x263);
                            break;

                        default:
                            func_80041C70(0x271);
                            break;
                    }
                    break;

                case 3:
                    if (D_80078390[1] == 2) {
                        func_80041C70(0x25B);
                        func_80041C70(0x263);
                    } else {
                        func_80041C70(0x271);
                    }
                    break;

                default:
                    if (D_80078400 == 0) {
                        func_800420C0(D_80077E78);
                    } else {
                        func_800420C0(D_80077DF0);
                    }
                    break;
            }

            return;
        }

        if (D_800FCCB3 != 0) {
            func_800420C0(D_80077E38);
            D_800FCCB3 = 0;
            return;
        }

        if (D_800FCCB4 != 0) {
            func_800420C0(D_80077E40);
            D_800FCCB4 = 0;
            return;
        }

        if (D_800FCCB5 != 0) {
            func_800420C0(D_80077E50);
            D_800FCCB5 = 0;
            return;
        }

        if ((gAudioInfoPtr[0]->unk_28 * 0.5f) <
            (gHPHistory[0].unk_00[(gHPHistory[0].unk_24 - 1) & 0xF] -
             gHPHistory[0].unk_00[gHPHistory[0].unk_24 & 0xF])) {
            if ((gAudioInfoPtr[1]->unk_28 * 0.5f) <
                (gHPHistory[1].unk_00[(gHPHistory[1].unk_24 - 1) & 0xF] -
                 gHPHistory[1].unk_00[gHPHistory[1].unk_24 & 0xF])) {
                if (((((u32)gAudioInfoPtr[0]->unk_0C * 100) / gAudioInfoPtr[0]->unk_28) < 0x14U) &&
                    ((((u32)gAudioInfoPtr[1]->unk_0C * 100) / gAudioInfoPtr[1]->unk_28) < 0x14U)) {
                    func_800420C0(D_80077E60);
                } else {
                    func_800420C0(D_80077E58);
                }
                return;
            }
        }

        if (gAudioInfoPtr[0]->unk_0C >= gAudioInfoPtr[1]->unk_0C) {
            var_v0 = gAudioInfoPtr[0]->unk_0C - gAudioInfoPtr[1]->unk_0C;
        } else {
            var_v0 = gAudioInfoPtr[1]->unk_0C - gAudioInfoPtr[0]->unk_0C;
        }

        if (((gAudioInfoPtr[var_t0]->unk_28 * 0.7) < var_v0) &&
            ((((u32)gAudioInfoPtr[var_t5]->unk_0C * 100) / gAudioInfoPtr[var_t5]->unk_28) >= 0x47) &&
            (gAudioInfoPtr[0]->unk_0C != gAudioInfoPtr[0]->unk_28) && (gAudioInfoPtr[1]->unk_0C != gAudioInfoPtr[1]->unk_28)) {
            if ((gAudioInfoPtr[var_t5]->unk_28 * 0.6) < gAudioInfoPtr[var_t5]->unk_0C) {
                if (gAudioInfoPtr[var_t0]->unk_0C < (gAudioInfoPtr[var_t0]->unk_28 * 0.4)) {
                    func_800420C0(D_80077E20);
                    return;
                }
            }
        }

        if (gAudioInfoPtr[0]->unk_0C >= gAudioInfoPtr[1]->unk_0C) {
            var_v0 = gAudioInfoPtr[0]->unk_0C - gAudioInfoPtr[1]->unk_0C;
        } else {
            var_v0 = gAudioInfoPtr[1]->unk_0C - gAudioInfoPtr[0]->unk_0C;
        }

        if (var_v0 < 0xA) {
            if ((gAudioInfoPtr[0]->unk_28 * 0.5) < gAudioInfoPtr[0]->unk_0C) {
                if (((gAudioInfoPtr[1]->unk_28 * 0.5) < gAudioInfoPtr[1]->unk_0C) &&
                    (gAudioInfoPtr[0]->unk_0C < gAudioInfoPtr[0]->unk_28) &&
                    (gAudioInfoPtr[1]->unk_0C < gAudioInfoPtr[1]->unk_28)) {
                    func_800420C0(D_80077E30);
                    return;
                }
            }
        }

        if (gAudioInfoPtr[0]->unk_0C >= gAudioInfoPtr[1]->unk_0C) {
            var_v0 = gAudioInfoPtr[0]->unk_0C - gAudioInfoPtr[1]->unk_0C;
        } else {
            var_v0 = gAudioInfoPtr[1]->unk_0C - gAudioInfoPtr[0]->unk_0C;
        }

        if (var_v0 < 0xA) {
            if (gAudioInfoPtr[0]->unk_0C < (gAudioInfoPtr[0]->unk_28 * 0.3)) {
                if (gAudioInfoPtr[1]->unk_0C < (gAudioInfoPtr[1]->unk_28 * 0.3)) {
                    func_800420C0(D_80077E28);
                    return;
                }
            }
        }

        if (D_80078400 == 0) {
            func_800420C0(D_80077E78);
        } else {
            func_800420C0(D_80077DF0);
        }

        return;
    }

    var_v0 = osSetIntMask(1);
    D_800783BC = 0;
    osSetIntMask(var_v0);
    func_80037234(0x5A, 0);
    func_80037234(0x5B, 0);

    if (gAudioInfoPtr[0] != NULL) {
        D_800FCB28[0] = gAudioInfoPtr[0]->unk_0C;
    }

    if (gAudioInfoPtr[1] != NULL) {
        D_800FCB28[1] = gAudioInfoPtr[1]->unk_0C;
    }

    D_800783CC++;

    for (i = 0; i < 2; i++) {
        gHPHistory[i].unk_78++;
        if (gHPHistory[i].unk_7C != 0) {
            gHPHistory[i].unk_7C++;
        }
    }

    D_800FCCB4 = 0;
    D_800FCCB3 = 0;
    D_800FCCB5 = 0;
    D_800783E4 = 0;

    if ((gAudioInfoPtr[0] != NULL) && (gAudioInfoPtr[1] != NULL) && (D_8007840C != 0) &&
        (gAudioInfoPtr[0]->unk_0C != 0) && (gAudioInfoPtr[1]->unk_0C != 0) && (Audio_IsChannelActive(1) == 0)) {
        if ((osGetTime() % 2) == 0) {
            func_800420C0(D_800780A8);
        }
    }
}

void ProcessAudioInfo(s32 arg0, unk_D_800FCB18* arg1) {
    u8 pad;
    u8 value;
    u8 side;
    u8 changed = 0;
    u32 i;
    u8 pad2;

    D_800FCCB1 = 0;
    D_800783F0 = 0;
    D_800783F4 = 0;
    D_800783F8 = 0;

    if (arg1 == NULL) {
        return;
    }
    if ((arg0 == 0) || ((u32)arg0 >= 5)) {
        return;
    }

    arg0--;
    side = gPlayerSideMap[arg0];
    if ((side <= 0) || (side >= 3)) {
        return;
    }
    side--;
    side &= 0xFF;

    if (D_80078394[side] != arg0) {
        changed = 1;
        D_80078394[side] = arg0;
    }

    gAudioInfoPtr[side] = arg1;

    ResetPlayerData(side);

    D_800FCCC8[side ^ 1] = 0;

    D_800FCB28[side] = gAudioInfoPtr[side]->unk_0C;
    gHPHistory[side].unk_24++;
    gHPHistory[side].unk_00[gHPHistory[side].unk_24 & 0xF] = gAudioInfoPtr[side]->unk_0C;

    value = gAudioInfoPtr[side]->unk_0B;
    if ((value <= 0) || (value >= 0x98)) {
        return;
    }

    for (i = 0; i < D_8007839C[side]; i++) {
        if (D_800FCB38[side][i] == value) {
            goto found_value;
        }
    }

    D_800FCB38[side][D_8007839C[side]] = value;
    D_8007839C[side]++;
    if (D_8007839C[side] >= 8) {
        D_8007839C[side] = 7;
    }

    D_800FCB30[side] = 0;
    if (D_800783CC != 0) {
        func_80041C70(value + 0xCB);
        if (changed) {
            func_800420C0(D_80077FEC);
        }

        if (gAudioInfoPtr[side ^ 1] == NULL) {
            return;
        }

        if (((f32)gAudioInfoPtr[side ^ 1]->unk_26 - (f32)(gAudioInfoPtr[side])->unk_26) > ((f32)(gAudioInfoPtr[side])->unk_26 * 2.0f)) {
            D_800FCCB1 = 1;
            D_800FCCBA[side] = 0;
            return;
        }

        if (((f32)(gAudioInfoPtr[side])->unk_26 * 0.3f) < ((f32)gAudioInfoPtr[side ^ 1]->unk_26 - (f32)(gAudioInfoPtr[side])->unk_26)) {
            D_800FCCB1 = 1;
            D_800FCCBA[side] = 0;
            return;
        }

        if (((f32)gAudioInfoPtr[side ^ 1]->unk_26 * 0.3f) < ((f32)(gAudioInfoPtr[side])->unk_26 - (f32)gAudioInfoPtr[side ^ 1]->unk_26)) {
            D_800FCCB1 = 1;
            if ((D_800FCCD6[side] != 0) && (D_800FCCBA[side] != 0)) {
                if (changed == 0) {
                    func_800420C0(D_80078014);
                }
            } else if (changed == 0) {
                func_800420F0(9, D_80077FF4, &D_800FCCBA[side]);
            } else {
                D_800FCCBA[side]++;
            }

            D_800FCCB8[side] = 0;
            D_800FCCD6[side] = 0;
            return;
        }

        if ((D_80078390[side] == 2) && (D_80078390[side ^ 1] == 3)) {
            if ((((u32)gAudioInfoPtr[side ^ 1]->unk_0C * 100) / gAudioInfoPtr[side ^ 1]->unk_28) < 0x32) {
                if (D_800783E0 == 0) {
                    if (changed == 0) {
                        func_80041C70(0xA);
                    }
                    D_800783E0 = 1;
                }
            }
        }
    }
    D_800FCCB8[side] = 0;
    D_800FCCBA[side] = 0;
    return;

found_value:
    if (D_800FCB30[side] == 0) {
        if (D_800783DC == 0) {
            if (D_80078390[side] < 2) {
                if ((osGetTime() % 2) == 0) {
                    func_80041C70(2);
                } else {
                    func_80041C70(1);
                }
            } else {
                func_80041C70(0x50);
                if (changed != 0) {
                    func_800420C0(D_80077FEC);
                }
            }
            D_800783DC = 1;
        } else {
            func_80041C70(0x58);
            D_800783DC = 0;
            if (changed != 0) {
                func_800420C0(D_80077FEC);
            }
        }
    } else if (changed != 0) {
        func_800420C0(D_80077FEC);
    }

    D_800FCB30[side] = 0;

    if (gAudioInfoPtr[side ^ 1] == NULL) {
        return;
    }

    if (changed != 0) {
        return;
    }

    if ((gAudioInfoPtr[side])->unk_15 & 0x20) {
        func_800420C0(D_80077FFC);
        return;
    }

    if ((gAudioInfoPtr[side])->unk_15 & 7) {
        func_800420C0(D_80078004);
        return;
    }

    if ((gAudioInfoPtr[side])->unk_15 & 8) {
        func_80041C70(6);
        return;
    }

    if ((gAudioInfoPtr[side])->unk_15 & 0x10) {
        func_80041C70(7);
        return;
    }

    if ((((f32)(gAudioInfoPtr[side])->unk_0C / (f32)(gAudioInfoPtr[side])->unk_28) < 0.2f) && ((gAudioInfoPtr[side])->unk_0C < gAudioInfoPtr[side ^ 1]->unk_0C)) {
        func_800420C0(D_8007800C);
    }
}

void RemovePlayer(u32 arg0) {
    u8 sp1F;

    if (arg0 == 0 || arg0 >= 5) {
        return;
    }
    arg0--;
    sp1F = gPlayerSideMap[arg0];
    if (sp1F <= 0 || sp1F >= 3) {
        return;
    }
    sp1F--;
    gTeamScores[arg0]--;
    D_80078390[sp1F]--;
    D_800FCB30[sp1F] = 0;
    if (gAudioInfoPtr[0] == 0 || gAudioInfoPtr[1] == 0) {
        return;
    }
    func_800367A0(0x16, D_80078400, 0);
    if (D_800783D8 != 0) {
        func_80041C70(0xC3);
        D_800783D8 = 0;
        D_800783E4 = 1;
        return;
    }
    D_800783D8 = 1;
    if (D_800783D4 != 0) {
        func_80041C70(0xB9);
        D_800783D4 = 0;
        return;
    }
    if (D_800783CC < 2) {
        if (osGetTime() % 2 == 0) {
            func_80041C70(0xBC);
        } else {                
            func_80041C70(0xC5);
        }
    } else if (D_800783D0 != 0) {
        func_80041C70(0xC4);
        D_800783D0 = 0;
    } else if ((D_800FCCA4 >= 0x64U) && (D_800FCCB2 == 0) && (D_800783EC == 0)) {
        if (((f32)gAudioInfoPtr[sp1F]->unk_26 * (3.0 / 10.0)) < ((f32)gAudioInfoPtr[sp1F ^ 1]->unk_26 - gAudioInfoPtr[sp1F]->unk_26)) {
            func_800420C0(D_80077FC0);
        } else {
            func_800420C0(D_80077FD0);
        }
        D_800FCCD6[sp1F] = 1;
    } else if ((gHPHistory[sp1F].unk_78 >= 8U) && (D_800FCCB2 == 0)) {
        if (((u32) D_800FCCA4 < 5U) && (D_800783E8 == 0)) {
            func_80041C70(0xC2);
        } else {
            func_800420C0(D_80077FC8);
        }
    } else {
        func_800420C0(D_80077FB4);
    }
}

void PlayerDefeated(u32 arg0) {
    u8 temp_v0;
    
    if (arg0 == 0 || arg0 >= 5) {
        return;
    }
    
    arg0--;
    temp_v0 = gPlayerSideMap[arg0];

    if (temp_v0 <= 0 || temp_v0 >= 3) {
        return;
    }
    
    temp_v0--;

    if (gAudioInfoPtr[0] == 0 || gAudioInfoPtr[1] == 0) {
        return;
    }

    if (gAudioInfoPtr[temp_v0]->unk_0C <= 0) {
       return; 
    }
    
    D_800FCB30[temp_v0] = 1;
    D_800FCCB5 = 1;
    
    if (D_800783DC != 0) {
        func_80041C70(0x58);
        D_800783DC = 0;
        return;
    }
    
    D_800783DC = 1;
    
    if (D_800783CC < 2) {
        if (osGetTime() % 2 == 0) {
            func_80041C70(0x54);
        } else {
            func_80041C70(0x55);
        }
    } else if (gHPHistory[temp_v0].unk_78 < 2) {
        func_800420C0(D_80077FE4);
    } else {
        func_800420C0(D_80077FD8);
    }
}

void ProcessCommandQueue(u32 arg0) {
    D_800FCCF0[gCommandQueueCount] = arg0;
    gCommandQueueCount++;
    if (gCommandQueueCount >= 0xA) {
        gCommandQueueCount--;
    }
}

void func_8003F660(s32 arg0) {
    u32 mask;
    u32 sp40;
    s32 sp3C;
    u8 temp_s0;
    u8 sp3A;
    u8 sp39;
    u8 sp38;
    u8 sp37;
    u8 sp36;
    u8 pad1;
    u8 sp34;
    u8 pad2;
    u8 sp32;

    sp3A = 0;
    sp39 = 0;
    sp38 = 0;
    sp37 = 0;
    sp36 = 0;
    sp34 = 0;
    sp32 = 0;
    mask = osSetIntMask(1);
    sp3C = D_800FCCA2;
    D_800FCCA2 = 0;
    osSetIntMask(mask);
    D_800783D0 = 0;
    D_800FCCB2 = 0;
    if (arg0 == 0 || arg0 >= 5U) {
        return;
    }
    arg0--;
    temp_s0 = gPlayerSideMap[arg0];
    if (temp_s0 <= 0 || temp_s0 >= 3) {
        return;
    }
    temp_s0--;
    if (gAudioInfoPtr[0] == 0 || gAudioInfoPtr[1] == 0) {
        return;
    }
    for (sp40 = 0; sp40 < gCommandQueueCount; sp40++) {
        switch (D_800FCCF0[sp40]) {
        case 0x1D:
            sp3A = 1;
            D_800783A0 = 1;
            break;
        case 0x1E:
            sp37 = 1;
            D_800783A0 = 1;
            break;
        case 0x29:
            sp39 = 1;
            D_800783A0 = 1;
            break;
        case 0x2A:
            sp38 = 1;
            D_800783A0 = 1;
            break;
        case 0x66:
            sp36 = 1;
            break;
        case 0x6F:
            sp34 = 1;
            break;
        case 0x6B:
        case 0x6C:
            gHPHistory[temp_s0].unk_24++;
            gHPHistory[temp_s0].unk_00[gHPHistory[temp_s0].unk_24 & 0xF] = gAudioInfoPtr[temp_s0]->unk_0C;
            mask = osSetIntMask(1);
            D_800FCCA2 = sp3C;
            osSetIntMask(mask);
            break;
        case 0x6E:
        case 0x70:
        case 0x9E:
        case 0xAB:
            mask = osSetIntMask(1);
            D_800FCCA2 = sp3C;
            osSetIntMask(mask);
            break;
        case 0x0:
        case 0x1:
        case 0x2:
            D_800FCCB2 = 1;
            D_800783EC = 1;
            break;
        case 0x9D:
            D_800783D0 = 1;
            D_800FCCB2 = 1;
            break;
        case 0x6D:
            func_80041C70(0x165);
            gCommandQueueCount = 0;
            D_800FCCBE[temp_s0] = 0;
            func_800367A0(0x16, D_80078400, 0);
            return;
        case 0x6:
            if (gHPHistory[temp_s0].unk_7C == 1) {
                func_80041C70(0x19F);
            } else if (gHPHistory[temp_s0].unk_7C >= 4) {
                func_80041C70(0x164);
            } else {
                func_80041C70(0x163);
            }
            gCommandQueueCount = 0;
            gHPHistory[temp_s0].unk_7C = 0;
            D_800FCCBC[temp_s0] = 0;
            D_800FCCB4 = 0;
            func_800367A0(0x16, D_80078400, 0);
            return;
        case 0xB:
            func_80041C70(0x17B);
            gCommandQueueCount = 0;
            return;
        case 0xC:
            func_80041C70(0x186);
            D_800FCCC4[temp_s0] = 0;
            gCommandQueueCount = 0;
            return;
        case 0x11:
            func_80041C70(0x192);
            D_800FCCD4[temp_s0] = 0;
            gCommandQueueCount = 0;
            return;
        case 0x5:
            if ((D_80078390[0] == 1) && (D_80078390[1] == 1)) {
                func_800420F0(0x17D, &D_80078040, &D_800FCCBC[temp_s0]);
            } else {
                func_800420F0(0x17D, D_8007801C, &D_800FCCBC[temp_s0]);
            }
            gCommandQueueCount = 0;
            return;
        case 0x7:
            if ((D_80078390[0] == 1) && (D_80078390[1] == 1)) {
                func_800420F0(0x17E, D_80078038, &D_800FCCBE[temp_s0]);
            } else {
                func_800420F0(0x17E, D_80078024, &D_800FCCBE[temp_s0]);
            }
            gCommandQueueCount = 0;
            return;
        case 0x10:
            if ((D_80078390[0] == 1) && (D_80078390[1] == 1)) {
                func_800420F0(0x17F, &D_80078040, &D_800FCCC0[temp_s0]);
            } else {
                func_800420F0(0x17F, D_80078030, &D_800FCCC0[temp_s0]);
            }
            gCommandQueueCount = 0;
            return;
        case 0x8:
            if ((D_80078390[0] == 1) && (D_80078390[1] == 1)) {
                func_800420F0(0x17C, &D_80078040, &D_800FCCC2[temp_s0]);
            } else {
                func_800420F0(0x17C, &D_80078048, &D_800FCCC2[temp_s0]);
            }
            gCommandQueueCount = 0;
            return;
        case 0x9:
        case 0xA:
            if ((D_80078390[0] == 1) && (D_80078390[1] == 1)) {
                func_80041C70(0x180);
            } else {
                func_80041C70(0x17C);
            }
            gCommandQueueCount = 0;
            return;
        case 0x13:
            func_800420C0(D_80078050);
            D_800FCCB6 = 1;
            gCommandQueueCount = 0;
            return;
        case 0xF:
            func_80041C70(0x17A);
            gCommandQueueCount = 0;
            return;
        case 0xE:
            D_800783D0 = 1;
            if (D_800FCCC4[temp_s0] != 0) {
                func_800420C0(D_80078060);
            } else {
                func_800420C0(D_80078058);
                D_800FCCC4[temp_s0] = 1;
            }
            gCommandQueueCount = 0;
            func_800367A0(0x16, D_80078400, 0);
            return;
        case 0x12:
            if (D_800FCCCA[temp_s0] == 0) {
                func_80041C70(0x18C);
            } else {
                func_80041C70(0x18E);
            }
            D_800FCCCA[temp_s0] ^= 1;
            gCommandQueueCount = 0;
            func_800367A0(0x16, D_80078400, 0);
            return;
        case 0x71:
        case 0x77:
            func_800420F0(0x16A, &D_80078068, &D_800FCCC6[temp_s0]);
            gCommandQueueCount = 0;
            return;
        case 0x72:
        case 0x78:
            func_800420F0(0x16B, &D_80078068, &D_800FCCC6[temp_s0]);
            gCommandQueueCount = 0;
            return;
        case 0x73:
        case 0x79:
            func_800420F0(0x16C, &D_80078068, &D_800FCCC6[temp_s0]);
            gCommandQueueCount = 0;
            return;
        case 0x74:
        case 0x7A:
            func_800420F0(0x16D, &D_80078068, &D_800FCCC6[temp_s0]);
            gCommandQueueCount = 0;
            return;
        case 0x75:
        case 0x7B:
            func_800420F0(0x16E, &D_80078068, &D_800FCCC6[temp_s0]);
            gCommandQueueCount = 0;
            return;
        case 0x76:
        case 0x7C:
            func_800420F0(0x16F, &D_80078068, &D_800FCCC6[temp_s0]);
            gCommandQueueCount = 0;
            return;
        case 0xB5:
            func_800420F0(0x170, &D_80078068, &D_800FCCC6[temp_s0]);
            gCommandQueueCount = 0;
            return;
        case 0xB7:
            func_800420F0(0x171, &D_80078068, &D_800FCCC6[temp_s0]);
            gCommandQueueCount = 0;
            return;
        case 0x9A:
            func_800420F0(0x169, &D_80078068, &D_800FCCC6[temp_s0]);
            gCommandQueueCount = 0;
            return;
        case 0x9C:
            func_800420F0(0x194, &D_80078068, &D_800FCCC6[temp_s0]);
            gCommandQueueCount = 0;
            return;
        case 0xAE:
            func_80041C70(0x1A0);
            gCommandQueueCount = 0;
            return;
        case 0x7E:
        case 0x84:
            if (D_800FCCC8[temp_s0] < 3) {
                func_800420F0(0xA2, D_80078070, &D_800FCCC8[temp_s0]);
            } else {
                func_800420C0(D_80078078);
            }
            gCommandQueueCount = 0;
            return;
        case 0x7F:
        case 0x85:
            if (D_800FCCC8[temp_s0] < 3) {
                func_800420F0(0xA3, D_80078070, &D_800FCCC8[temp_s0]);
            } else {
                func_800420C0(D_80078078);
            }
            gCommandQueueCount = 0;
            return;
        case 0x80:
        case 0x86:
            if (D_800FCCC8[temp_s0] < 3) {
                func_800420F0(0xA7, D_80078070, &D_800FCCC8[temp_s0]);
            } else {
                func_800420C0(D_80078078);
            }
            gCommandQueueCount = 0;
            return;
        case 0x81:
        case 0x87:
            if (D_800FCCC8[temp_s0] < 3) {
                func_800420F0(0xA4, D_80078070, &D_800FCCC8[temp_s0]);
            } else {
                func_800420C0(D_80078078);
            }
            gCommandQueueCount = 0;
            return;
        case 0x82:
        case 0x88:
            if (D_800FCCC8[temp_s0] < 3) {
                func_800420F0(0xA5, D_80078070, &D_800FCCC8[temp_s0]);
            } else {
                func_800420C0(D_80078078);
            }
            gCommandQueueCount = 0;
            return;
        case 0x83:
        case 0x89:
            if (D_800FCCC8[temp_s0] < 3) {
                func_800420F0(0xA6, D_80078070, &D_800FCCC8[temp_s0]);
            } else {
                func_800420C0(D_80078078);
            }
            gCommandQueueCount = 0;
            return;
        case 0x19:
        case 0x1B:
            if ((D_800780B3[D_800FCCAC * 3] == 0) && ((gAudioInfoPtr[temp_s0]->unk_16[6] == 8) || (gAudioInfoPtr[temp_s0]->unk_16[7] == 8))) {
                func_800420C0(D_80077F24);
            } else {
                func_800420C0(D_80077F14);
            }
            gCommandQueueCount = 0;
            return;
        case 0x1A:
        case 0x1C:
            if (D_800FCCD2[temp_s0 ^ 1] != 0) {
                func_800420C0(D_80077F50);
            } else {
                if ((D_800783D4 != 0) || ((D_80078390[temp_s0 ^ 1] == 1) && (gAudioInfoPtr[temp_s0 ^ 1]->unk_0C < 0x13))) {
                    func_800420C0(D_80077F1C);
                    func_800367A0(0x16, D_80078400, 0);
                } else {
                    func_800420C0(D_80077F0C);
                }
                D_800FCCD2[temp_s0 ^ 1] = 1;
            }
            gCommandQueueCount = 0;
            return;
        case 0xA7:
            func_800420C0(D_80077F0C);
            gCommandQueueCount = 0;
            return;
        case 0x20:
        case 0x7D:
        case 0x8C:
        case 0x99:
        case 0x9B:
        case 0xA5:
        case 0xAD:
        case 0xB2:
        case 0xB4:
        case 0xB6:
        case 0xB8:
        case 0xB9:
        case 0xBA:
        case 0xBC:
            func_800420C0(D_80078088);
            gCommandQueueCount = 0;
            return;
        case 0x64:
        case 0x65:
        case 0x67:
        case 0x6A:
        case 0x8A:
        case 0x8B:
        case 0x8D:
        case 0x91:
        case 0x92:
        case 0xA0:
        case 0xA2:
        case 0xA3:
        case 0xAA:
            func_800420C0(D_80078090);
            gCommandQueueCount = 0;
            return;
        case 0x1F:
            func_80041C70(0x18D);
            gCommandQueueCount = 0;
            return;
        case 0x93:
        case 0x94:
        case 0x95:
        case 0x96:
            func_80041C70(0x18F);
            gCommandQueueCount = 0;
            return;
        case 0x97:
            func_800420F0(0x18A, D_80078098, &D_800FCCCE[temp_s0]);
            gCommandQueueCount = 0;
            func_800367A0(0x16, D_80078400, 0);
            return;
        case 0x98:
            func_800420F0(0x18B, D_800780A0, &D_800FCCD0[temp_s0]);
            gCommandQueueCount = 0;
            func_800367A0(0x16, D_80078400, 0);
            return;
        case 0x2B:
            func_80041C70(0x76);
            gCommandQueueCount = 0;
            return;
        case 0x2C:
            func_800420C0(D_80078080);
            gCommandQueueCount = 0;
            return;
        case 0xBB:
            func_80041C70(0x189);
            gCommandQueueCount = 0;
            func_800367A0(0x16, D_80078400, 0);
            D_800783D0 = 1;
            return;
        case 0x68:
            func_800420C0(D_80077F34);
            gCommandQueueCount = 0;
            return;
        case 0x69:
            func_800420C0(D_80077F3C);
            gCommandQueueCount = 0;
            return;
        case 0xA1:
            func_80041C70(0x7A);
            gCommandQueueCount = 0;
            return;
        case 0xA6:
            func_800420C0(D_80077F2C);
            gCommandQueueCount = 0;
            return;
        case 0xAF:
        case 0xB0:
            func_80041C70(0x167);
            gHPHistory[temp_s0].unk_24++;
            gHPHistory[temp_s0].unk_00[gHPHistory[temp_s0].unk_24 & 0xF] = gAudioInfoPtr[temp_s0]->unk_0C;
            gCommandQueueCount = 0;
            return;
        case 0xB1:
            func_80041C70(0x166);
            gHPHistory[temp_s0].unk_24++;
            gHPHistory[temp_s0].unk_00[gHPHistory[temp_s0].unk_24 & 0xF] = gAudioInfoPtr[temp_s0]->unk_0C;
            gCommandQueueCount = 0;
            return;
        case 0xB3:
            func_80041C70(0x188);
            gCommandQueueCount = 0;
            func_800367A0(0x16, D_80078400, 0);
            return;
        case 0xA8:
            func_80041C70(0x197);
            gCommandQueueCount = 0;
            return;
        case 0xA9:
            func_80041C70(0x193);
            gCommandQueueCount = 0;
            return;
        case 0xA4:
            func_80041C70(0x195);
            gCommandQueueCount = 0;
            return;
        case 0xAC:
            func_80041C70(0x196);
            gCommandQueueCount = 0;
            return;
        case 0x9F:
            func_80041C70(0x87);
            gCommandQueueCount = 0;
            return;
        case 0x4:
            sp32 = 1;
            break;
        default:
            break;
        }
    }
    gCommandQueueCount = 0;

    if (sp34 != 0) {
        mask = osSetIntMask(1);
        D_800FCCA2 = 0;
        osSetIntMask(mask);
        func_80041C70(0x79);
        D_800FCCB3 = 1;
        func_800367A0(0x16, D_80078400, 0);
    } else if (sp36 != 0) {
        mask = osSetIntMask(1);
        D_800FCCA2 = 0;
        osSetIntMask(mask);
        if (D_800FCCCC[temp_s0] != 0) {
            func_80041C70(0xAD);
        } else {
            func_80041C70(0x78);
        }
        gHPHistory[temp_s0].unk_7C = 1;
        D_800FCCCC[temp_s0] = 1;
        D_800FCCB4 = 1;
        func_800367A0(0x16, D_80078400, 0);
    } else if (sp37 != 0) {
        mask = osSetIntMask(1);
        D_800FCCA2 = 0;
        osSetIntMask(mask);
        D_800783E8 = 1;
        func_80041C70(0x77);
        func_800367A0(0x16, D_80078400, 0);
    } else if (sp3A != 0) {
        mask = osSetIntMask(1);
        D_800FCCA2 = 0;
        osSetIntMask(mask);
        D_800783E8 = 1;
        if (sp39 != 0) {
            if (D_800FCCA4 < 0xA) {
                if ((gAudioInfoPtr[temp_s0]->unk_0C > 0) && (gAudioInfoPtr[temp_s0 ^ 1]->unk_0C >= 0xB)) {
                    func_800420C0(D_80077EF0);
                } else {
                    func_800420C0(D_80077F04);
                }
            } else if (D_800783CC < 2) {
                func_80041C70(0x68);
                func_800367A0(0x16, D_80078400, 0);
            } else {
                if ((gHPHistory[temp_s0 ^ 1].unk_78 < 2U) && (D_80078390[temp_s0 ^ 1] >= 2)) {
                    func_800420C0(D_80077F58);
                } else {
                    func_800420C0(D_80077EE4);
                }
                func_800367A0(0x16, D_80078400, 0);
            }
        } else if (D_800FCCA4 < 0xA) {
            if ((gAudioInfoPtr[temp_s0]->unk_0C > 0) && (gAudioInfoPtr[temp_s0 ^ 1]->unk_0C >= 0xB)) {
                func_800420C0(D_80077EF0);
            } else {
                func_800420C0(D_80077F04);
            }
        } else {
            func_800420C0(D_80077EC0);
            func_800367A0(0x16, D_80078400, 0);
        }
    } else if (sp39 != 0) {
        mask = osSetIntMask(1);
        D_800FCCA2 = 0;
        osSetIntMask(mask);
        D_800783E8 = 1;
        if ((gHPHistory[temp_s0 ^ 1].unk_78 < 2U) && (D_80078390[temp_s0 ^ 1] >= 2)) {
            func_800420C0(D_80077F58);
        } else {
            func_800420C0(D_80077ECC);
        }
        func_800367A0(0x16, D_80078400, 0);
    } else if (sp38 != 0) {
        mask = osSetIntMask(1);
        D_800FCCA2 = 0;
        osSetIntMask(mask);
        if (D_800FCCA4 >= 0x29) {
            func_800420C0(D_80077EF8);
            func_800367A0(0x16, D_80078400, 0);
        } else if ((gAudioInfoPtr[0]->unk_0C > 0) && (gAudioInfoPtr[1]->unk_0C > 0)) {
            func_800420C0(D_80077ED8);
        } else {
            func_800420C0(D_80077F04);
            func_800367A0(0x16, D_80078400, 0);
        }
    } else if ((sp32 != 0) && (D_800FCCA4 != 0)) {
        if (D_800FCCA4 >= 0x29) {
            func_800420C0(D_80077E98);
            func_800367A0(0x16, D_80078400, 0);
        } else if (D_800FCCA4 >= 6) {
            if ((gAudioInfoPtr[0]->unk_0C > 0) && (gAudioInfoPtr[1]->unk_0C > 0)) {
                func_800420C0(D_80077EA4);
            } else {
                func_800420C0(D_80077F60);
            }
        } else if ((gAudioInfoPtr[0]->unk_0C > 0) && (gAudioInfoPtr[1]->unk_0C > 0)) {
            func_800420C0(D_80077EB4);
        } else {
            func_800420C0(D_80077F04);
        }
    }
}

void func_80040A70(unk_D_800FCB18* arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 i;
    s32 sp40;
    u32 temp_lo;
    u32 temp_v0;
    s32 sp34;
    u32 tmp;
    OSIntMask sp2C;

    if (arg0 == NULL) {
        return;
    }

    if (arg0 == gAudioInfoPtr[0]) {
        sp40 = 0;
    } else if (arg0 == gAudioInfoPtr[1]) {
        sp40 = 1;
    } else {
        return;
    }

    if ((gAudioInfoPtr[0] == NULL) || (gAudioInfoPtr[1] == NULL)) {
        return;
    }

    D_800FCCAC = arg1;

    switch (arg3) {
        case 1:
            D_800FCCB7 = 0;
            func_80041CEC();
            sp40 ^= 1;

            if (gAudioInfoPtr[sp40]->unk_0C != 0) {
                for (i = 0; i < 5; i++) {
                    // FAKE
                    if (arg2) {}
                    if (arg1 == D_80078548[i].unk_00) {
                        if (gAudioInfoPtr[sp40]->unk_0C < gHPHistory[sp40].unk_00[gHPHistory[sp40].unk_24 & 0xF]) {
                            tmp = (gHPHistory[sp40].unk_00[gHPHistory[sp40].unk_24 & 0xF] - gAudioInfoPtr[sp40]->unk_0C);
                            D_800FCCA4 = (tmp * 0x64) / gAudioInfoPtr[sp40]->unk_28;
                        } else {
                            D_800FCCA4 = 0;
                        }
                        D_800FCCAD = arg2;
                        return;
                    }

                    if (arg1 == D_80078548[i].unk_01) {
                        if (gAudioInfoPtr[sp40]->unk_0C < gHPHistory[sp40].unk_00[gHPHistory[sp40].unk_24 & 0xF]) {
                            tmp = gHPHistory[sp40].unk_00[gHPHistory[sp40].unk_24 & 0xF] - gAudioInfoPtr[sp40]->unk_0C;
                            D_800FCCA4 = (tmp * 0x64) / gAudioInfoPtr[sp40]->unk_28;
                        } else {
                            D_800FCCA4 = 0;
                        }
                        D_800FCCAD = arg2;
                        return;
                    }
                }
            }

            temp_v0 = osSetIntMask(sp2C);

            D_800FCCA2 = 0x1E;
            if (gAudioInfoPtr[sp40]->unk_0C < gHPHistory[sp40].unk_00[gHPHistory[sp40].unk_24 & 0xF]) {
                tmp = gHPHistory[sp40].unk_00[gHPHistory[sp40].unk_24 & 0xF] - gAudioInfoPtr[sp40]->unk_0C;
                D_800FCCA4 = (tmp * 0x64) / gAudioInfoPtr[sp40]->unk_28;
            } else {
                D_800FCCA4 = 0;
            }
            D_800FCCAD = arg2;

            osSetIntMask(temp_v0);

            if (D_800FCCA4 >= 0x29) {
                func_800367A0(0x16, D_80078400, 0);
            }
            break;

        case 0:
        case 2:
            func_80041CEC();
            D_800FCCC0[sp40] = 0;
            D_800FCCC2[sp40] = 0;

            if (arg1 != 0x13) {
                D_800FCCCE[sp40] = 0;
            }

            if (arg1 != 0x5B) {
                D_800FCCD0[sp40] = 0;
            }

            if (arg3 != 2) {
                D_800FCCD2[sp40] = 0;
            }

            D_800FCCAE += 1;

            for (i = 0; i < 17; i++) {
                if (arg1 == D_80078554[i]) {
                    goto loop1_end;
                }
            }

            D_800FCCC6[sp40] = 0;
        loop1_end:

            for (i = 0; i < 9; i++) {
                if (arg1 == D_80078568[i]) {
                    goto loop2_end;
                }
            }

            D_800FCCC8[sp40] = 0;
        loop2_end:

            D_800FCCA2 = 0;
            if (D_800FCCB7 == 0) {
                tmp = func_80042158(arg1, gAudioInfoPtr[sp40], gAudioInfoPtr[sp40 ^ 1]);

                if (tmp == -1) {
                    if (IsBitSetInArray(D_800FCCD8, arg1 - 1) == 0) {
                        sp34 = arg1 + 0x1A2;
                        SetBitInArray(D_800FCCD8, arg1 - 1, 1);
                        func_80041C70(sp34);
                    } else {
                        func_800420C0(D_80077F6C);
                    }
                } else if (tmp == -2) {
                    if (IsBitSetInArray(D_800FCCD8, arg1 - 1) == 0) {
                        sp34 = arg1 + 0x1A2;
                        SetBitInArray(D_800FCCD8, arg1 - 1, 1);
                        func_80041C70(sp34);
                    } else {
                        func_800420C0(D_80077F74);
                    }
                } else if (tmp == -3) {
                    D_800783D4 = 1;
                    if (IsBitSetInArray(D_800FCCD8, arg1 - 1) == 0) {
                        sp34 = arg1 + 0x1A2;
                        SetBitInArray(D_800FCCD8, arg1 - 1, 1);
                        func_80041C70(sp34);
                    } else {
                        func_80041C70(0x187);
                    }
                } else if (tmp == -4) {
                    if (IsBitSetInArray(D_800FCCD8, arg1 - 1) == 0) {
                        sp34 = arg1 + 0x1A2;
                        SetBitInArray(D_800FCCD8, arg1 - 1, 1);
                        func_80041C70(sp34);
                    } else {
                        func_800420C0(D_80077F98);
                    }
                } else if (tmp != -5) {
                    if ((gHPHistory[sp40 ^ 1].unk_00[gHPHistory[sp40 ^ 1].unk_24 & 0xF] < tmp) && (D_800FCCB6 == 0)) {
                        if (IsBitSetInArray(D_800FCCD8, arg1 - 1) == 0) {
                            sp34 = arg1 + 0x1A2;
                            SetBitInArray(D_800FCCD8, arg1 - 1, 1);
                            func_80041C70(sp34);
                        } else {
                            func_800420C0(D_80077F90);
                            D_800FCCB6 = 0;
                        }
                    } else {
                        D_800FCCB6 = 0;
                        temp_lo = (tmp * 0x64) / gAudioInfoPtr[sp40 ^ 1]->unk_28;
                        if (temp_lo >= 0x51) {
                            if (D_800FCCAF == 0) {
                                D_800FCCAF = 1;
                                func_800420C0(D_80077F6C);
                            } else {
                                func_800420C0(D_80077F74);
                            }
                        } else if (temp_lo >= 0x33) {
                            if (D_800783CC == 1) {
                                func_800420C0(D_80077F88);
                            } else {
                                func_800420C0(D_80077F7C);
                            }
                        } else if (Audio_IsChannelActive(1) == 0) {
                            if (D_800783CC == 1) {
                                if (D_800FCCAE == 2) {
                                    func_800420C0(D_80077FAC);
                                } else {
                                    func_800420C0(D_80077FA4);
                                }
                            } else {
                                func_800420C0(D_80077F98);
                            }
                        }
                    }
                }
            }
            break;

        case 3:
            if (D_800FCCB7 == 0) {
                D_800FCCB7 = 1;
                D_800FCCA2 = 0;
                tmp = func_80042158(arg1, gAudioInfoPtr[sp40], gAudioInfoPtr[sp40 ^ 1]);
                if ((tmp >> 0x10) == 0) {
                    tmp = tmp << 1;

                    if (gHPHistory[sp40 ^ 1].unk_00[gHPHistory[sp40 ^ 1].unk_24 & 0xF] < tmp) {
                        if (IsBitSetInArray(D_800FCCD8, arg1 - 1) == 0) {
                            sp34 = arg1 + 0x1A2;
                            SetBitInArray(D_800FCCD8, arg1 - 1, 1);
                            func_80041C70(sp34);
                        } else {
                            func_800420C0(D_80077F90);
                        }
                    } else {
                        temp_lo = (tmp * 0x64u) / gAudioInfoPtr[sp40 ^ 1]->unk_28;
                        if (temp_lo >= 0x51) {
                            if (D_800FCCAF == 0) {
                                D_800FCCAF = 1;
                                func_800420C0(D_80077F6C);
                            } else {
                                func_800420C0(D_80077F74);
                            }
                        } else if (temp_lo >= 0x33) {
                            if (D_800783CC == 1) {
                                func_800420C0(D_80077F88);
                            } else {
                                func_800420C0(D_80077F7C);
                            }
                        } else if (Audio_IsChannelActive(1) == 0) {
                            if (D_800783CC == 1) {
                                if (D_800FCCAE == 2) {
                                    func_800420C0(D_80077FAC);
                                } else {
                                    func_800420C0(D_80077FA4);
                                }
                            } else {
                                func_800420C0(D_80077F98);
                            }
                        }
                    }
                }
            }
            break;

        case 4:
            D_800FCCAE += 1;
            D_800FCCB7 = 0;
            D_800FCCA2 = 0;
            break;

        case 5:
            D_800FCCB7 = 0;
            D_800FCCA2 = 0;
            break;

        default:
            D_800FCCB7 = 0;
            D_800FCCA2 = 0;
            break;
    }
}

void func_800414B8(s32 arg0) {
    u8 temp_v0;

    if (arg0 == 0 || arg0 >= 5U) {
        return;
    }
    arg0--;
    temp_v0 = gPlayerSideMap[arg0];
    if (temp_v0 <= 0 || temp_v0 >= 3) {
        return;
    }
    temp_v0--;
    if (D_800FCCD4[temp_v0] == 0) {
        func_80041C70(0x190);
        D_800FCCD4[temp_v0] = 1;
    } else {
        func_80041C70(0x191);   
    }
}

void func_8004153C(void) {
    if (D_80078E80 == 0) {
        func_8004B1CC(0x3D);
        func_800367A0(0x16, D_80078400, 0);
        if (D_80078404 == 0xC) {
            if (!(D_80078408 & 3) && (*D_80078390 != 0)) {
                func_80041C70(0xCA);
                return;
            }
            func_80041C70(0xC8);
            return;
        }
        if (D_80078404 == 0xD) {
            if ((D_80078408 == 4) && (*D_80078390 != 0)) {
                func_80041C70(0xCA);
                return;
            }
            if ((D_80078408 == 5) && (*D_80078390 != 0)) {
                func_80041C70(0xCB);
                return;
            }
            func_80041C70(0xC8);
            return;
        }
        if ((D_80078408 == 8) && (*D_80078390 != 0)) {
            func_80041C70(0xC9);
            return;
        }
        func_80041C70(0xC8);
    }
}

void func_80041688(void) {
    func_800367A0(0x16, D_80078400, 0);
    func_80041C70(0x1A2);
}

void func_800416BC(void) {
    u8* seq;

    if ((D_800783B4 < D_800783B8) && (gAudioActiveFlag != 0) && (Audio_IsChannelActive(1) == 0)) {
        if (D_800783A4[D_800783B4 & 3] != 0) {
            seq = D_800FC714->seqArray[D_800783A4[D_800783B4 & 3] - 1].offset;
            Audio_StartChannel(1, seq, 0x7E, 0);
        }
        D_800783B4++;
    }

    if (D_800783BC != 0) {
        if ((D_800783C8 >= 0x3E9) && (D_800783C0 == 0) && (D_800783CC != 0)) {
            func_80041C70(0x248);
            D_800783C0 = 1;
        } else if ((D_800783C8 >= 0x7D1) && (D_800783C0 == 0) && (D_800783CC == 0)) {
            func_80041C70(0x248);
            D_800783C0 = 1;
            D_800783C8 = 0x3E8;
        } else if ((D_800783C8 >= 0x641) && (D_800783C0 == 1)) {
            func_80041C70(0x249);
            if (D_800783C4 == 0) {
                func_800367A0(0x5B, D_80078400, 0);
                D_800783C4 = 1;
            }
            D_800783C0 = 2;
        } else if ((D_800783C8 >= 0x899) && (D_800783C0 == 2)) {
            func_80041C70(0x24A);
            D_800783C8 = 0x3E8;
            D_800783C0 = 1;
        }

        D_800783C8++;
    }

    if (D_800FCCA2 != 0) {
        if (D_800FCCA2 == 1) {
            if (D_800FCCA4 != 0) {
                if (D_800FCCA4 >= 0x29) {
                    if (((D_800FCCAD == 0x10) || (D_800FCCAD == 0x11) || (D_800FCCAD == 0x12) || (D_800FCCAD == 0x15) ||
                         (D_800FCCAD == 0x16) || (D_800FCCAD == 0x53) || (D_800FCCAD == 0x54) ||
                         (D_800FCCAD == 0x55)) &&
                        ((D_800FCCAC == 0x34) || (D_800FCCAC == 0x35) || (D_800FCCAC == 0x7E))) {
                        func_800420C0(D_80077F44);
                    } else {
                        func_800420C0(D_80077E98);
                    }
                } else if (D_800FCCA4 >= 6) {
                    if ((gAudioInfoPtr[0]->unk_0C > 0) && (gAudioInfoPtr[1]->unk_0C > 0)) {
                        func_800420C0(D_80077EA4);
                    } else {
                        func_800420C0(D_80077F60);
                    }
                } else if ((gAudioInfoPtr[0]->unk_0C > 0) && (gAudioInfoPtr[1]->unk_0C > 0)) {
                    func_800420C0(D_80077EB4);
                } else {
                    func_800420C0(D_80077F04);
                }
            }
            D_800FCCA8 = D_800FCCA4;
        }
        D_800FCCA2--;
    }
}

void func_80041A98(void) {
    s32 i;
    s32 j;

    D_800783CC = 0;
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 8; j++) {
            D_800FCB38[i][j] = 0;
        }
    }
    D_8007839C[0] = 0;
    D_8007839C[1] = 0;
    D_800FCCA0 = D_800FCCA1 = 0;
    D_800FCCA2 = 0;
    D_800FCCA4 = 0;
    D_800FCCAC = 0;
    D_800783E0 = 0;
    D_800FCCAF = 0;
    D_800FCCB0 = 0;
    D_800FCCB2 = 0;
    D_800FCCB3 = 0;
    D_800FCCB4 = 0;
    D_800FCCB5 = 0;
    D_800FCCB7 = 0;
    D_800FCCB6 = 0;
    D_800783E4 = 0;
    D_800783E8 = 0;
    D_800783EC = 0;
    D_800783F0 = 0;
    D_800783F4 = 0;
    D_800783F8 = 0;
    for (i = 0; i < 0x15; i++) {
        D_800FCCD8[i] = 0;
    }
    for (i = 0; i < 20; i++) {
        D_800FCC50[i] = 0;
    }
    for (i = 0; i < 2; i++) {
        D_800FCCB8[i] = 0;
        D_800FCCBA[i] = 0;
        D_800FCCBC[i] = 0;
        D_800FCCBE[i] = 0;
        D_800FCCC0[i] = 0;
        D_800FCCC2[i] = 0;
        D_800FCCD4[i] = 0;
        D_800FCCD6[i] = 0;
    }
}

void func_80041C70(u32 arg0) {
    OSIntMask mask;

    if ((gAudioActiveFlag != 0) && (D_800783FC != 0) && (arg0 != 0)) {
        mask = osSetIntMask(OS_IM_NONE);
        D_800783A4[D_800783B8 & 3] = arg0;
        D_800783B8++;
        osSetIntMask(mask);
    }
}

void func_80041CEC(void) {
    OSIntMask mask;

    if ((gAudioActiveFlag != 0) && (D_800783FC != 0)) {
        mask = osSetIntMask(OS_IM_NONE);
        D_800783A4[(D_800783B8 - 1) & 3] = 0;
        osSetIntMask(mask);
    }
}

void func_80041D50(u8* arg0, u8* arg1) {
    u8 temp_v0 = *arg0;
    u8 temp_v1 = *arg1;

    if (temp_v1 != temp_v0) {
        *arg0 = temp_v1;
        *arg1 = temp_v0;
    }
}

u16 func_80041D70(u16 arg0) {
    s32 i;

    for (i = 0; i < 20; i++) {
        if (arg0 == D_800FCC50[i]) {
            return 0;
        }
    }

    return arg0;
}

void func_80041DF4(u16 arg0) {
    u16 i;

    for (i = 0; i < 19; i++) {
        D_800FCC50[i] = D_800FCC50[i + 1];
    }

    D_800FCC50[19] = arg0;
}

void func_80041E40(u16 arg0) {
    u32 i;

    for (i = arg0; i > 0; i--) {
        D_800FCC50[i] = D_800FCC50[i - 1];
    }

    D_800FCC50[0] = 0;
}

u32 func_80041EF4(u16* arg0) {
    u16 temp_v0 = *arg0;
    u32 i;
    u32 j;
    u16 sp5A;

    for (i = 0; i < temp_v0; i++) {
        D_800FCD18[i] = i + 1;
    }

    for (i = 0; i < temp_v0 << 1; i++) {
        func_80041D50(D_800FCD18, D_800FCD18 + (osGetTime() % (s32)temp_v0));
    }

    for (i = 0; i < temp_v0; i++) {
        sp5A = func_80041D70(arg0[D_800FCD18[i]]);
        if (sp5A != 0) {
            func_80041DF4(sp5A);
            return sp5A;
        }
    }

    for (i = 0; i < 20; i++) {
        for (j = 1; j <= temp_v0; j++) {
            if (D_800FCC50[i] == arg0[j]) {
                func_80041E40(i);
                func_80041DF4(arg0[j]);
                return arg0[j];
            }
        }
    }

    return 0;
}

void func_800420C0(u16* arg0) {
    u32 temp_v0 = func_80041EF4(arg0);

    if (temp_v0 != 0) {
        func_80041C70(temp_v0);
    }
}

void func_800420F0(u16 arg0, u16* arg1, u8* arg2) {
    u8 temp_v0;

    if (*arg2 == 0) {
        func_80041C70(arg0);
    } else {
        func_800420C0(arg1);
    }
    temp_v0 = *arg2;
    if (temp_v0 < 0xFF) {
        *arg2 = temp_v0 + 1;
    }
}

void func_800420F0_empty() {
    
}

u32 func_80042158(u32 arg0, unk_D_800FCB18* arg1, unk_D_800FCB18* arg2) {
    u32 power;
    f32 atk;
    f32 def;
    f32 base;
    f32 dmg;
    f32 prevA;
    f32 hpA;
    f32 mulA;
    f32 prevB;
    f32 hpB;
    f32 mulB;
    u8 mode;
    f32 status;
    u8 conv1;
    u8 conv2;
    u8 conv0;
    u8 type;
    f32 eff2;
    f32 stab;
    u8* entry;
    u32 ret;
    s32 side;

    if ((arg0 == 0) || (arg0 >= 0xA6)) {
        arg0 = 1;
    }

    if (arg1 == gAudioInfoPtr[0]) {
        side = 0;
    } else if (arg1 == gAudioInfoPtr[1]) {
        side = 1;
    } else {
        return 0;
    }

    entry = &D_800780B4[(arg0 - 1) * 3];
    conv0 = func_80042850(entry[2]);
    type = entry[0];
    power = entry[1];

    switch (type) {
        case 0x26:
            return -1;

        case 0x28:
            return arg2->unk_28 / 2;

        case 0x29:
            switch (arg0) {
                case 0x31:
                    return 0x14;
                case 0x45:
                    return arg1->unk_26;
                case 0x52:
                    return 0x28;
                case 0x65:
                    return arg1->unk_26;
                case 0x95:
                    return (u32)arg1->unk_26 * 1.5f;
                default:
                    return 0;
            }

        case 0x7:
            return -3;

        case 0x9:
        case 0xA:
        case 0xB:
        case 0xD:
        case 0xF:
        case 0x18:
        case 0x19:
        case 0x1A:
        case 0x2E:
        case 0x2F:
        case 0x32:
        case 0x33:
        case 0x34:
        case 0x35:
        case 0x38:
        case 0x39:
        case 0x40:
        case 0x41:
        case 0x4F:
        case 0x52:
        case 0x53:
        case 0x55:
            return -5;

        case 0x12:
        case 0x13:
        case 0x14:
        case 0x16:
        case 0x20:
        case 0x31:
        case 0x3B:
        case 0x42:
        case 0x43:
        case 0x54:
        case 0x56:
            return -4;

        case 0x1C:
            if (D_800781E0 == &D_800780B4[arg0 * 3]) {
                return -5;
            }
            return -4;
    }

    if (D_80078180 == &D_800780B4[arg0 * 3]) {
        return -2;
    }

    if (arg1->unk_2A != 0) {
        atk = (u32)arg1->unk_2A;
    } else {
        atk = 1.0f;
    }

    if (arg2->unk_2C != 0) {
        def = (u32)arg2->unk_2C;
    } else {
        def = 1.0f;
    }

    base = (f32)(((arg1->unk_26 * 2) / 5) + 2) * power * atk / def / 50.0f;

    conv1 = func_80042850(arg2->unk_16[6]);
    conv2 = func_80042850(arg2->unk_16[7]);

    mode = D_800782A4[conv0 * 15 + conv1];
    switch (mode) {
        case 1:
            mulB = 0.0f;
            break;
        case 2:
            mulB = 0.5f;
            break;
        case 3:
            mulB = 2.0f;
            break;
        default:
            mulB = 1.0f;
    }

    mode = D_800782A4[conv0 * 15 + conv2];
    switch (mode) {
        case 1:
            eff2 = 0.0f;
            break;
        case 2:
            eff2 = 0.5f;
            break;
        case 3:
            eff2 = 2.0f;
            break;
        default:
            eff2 = 1.0f;
    }

    if ((arg1->unk_16[6] == entry[2]) || (arg1->unk_16[7] == entry[2])) {
        stab = 1.5f;
    } else {
        stab = 1.0f;
    }

    dmg = base * mulB * eff2 * stab;

    prevA = (u32)gHPHistory[side ^ 1].unk_00[gHPHistory[side ^ 1].unk_24 & 0xF];
    if (prevA == 0) {
        prevA = 1;
    }
    hpA = (u32)arg2->unk_28;
    if (D_80078390[side ^ 1] == 1) {
        mulA = 1.1f;
    } else {
        mulA = 1.0f;
    }

    prevB = (u32)gHPHistory[side].unk_00[gHPHistory[side].unk_24 & 0xF];
    if (prevB == 0) {
        prevB = 1;
    }
    hpB = (u32)arg1->unk_28;
    if (D_80078390[side] == 1) {
        mulB = 1.1f;
    } else {
        mulB = 1.0f;
    }

    if (arg2->unk_15 & 0x20) {
        status = 1.2f;
    } else if (arg2->unk_15 & 7) {
        status = 1.1f;
    } else {
        status = 1.0f;
    }

    ret = (((hpA / prevA) * 0.01f) + 1) * dmg * (1 + ((hpB / prevB) * 0.01f)) * mulA * mulB * status;

    if (ret >= 0x8000) {
        ret = 0x7FFF;
    }
    return ret;
}

s32 func_80042850(u8 arg0) {
    switch (arg0) {
    case 0:
        return 0;
    case 20:
        return 1;
    case 21:
        return 2;
    case 23:
        return 3;
    case 22:
        return 4;
    case 25:
        return 5;
    case 1:
        return 6;
    case 3:
        return 7;
    case 4:
        return 8;
    case 2:
        return 9;
    case 24:
        return 0xA;
    case 7:
        return 0xB;
    case 5:
        return 0xC;
    case 8:
        return 0xD;
    case 26:
        return 0xE;
    default:
        return 0;
    }
}

void func_800428FC(u32 arg0) {
    func_80041C70(arg0);
}
