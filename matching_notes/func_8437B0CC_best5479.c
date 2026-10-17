

#define NULL 0


typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef signed char s8;
typedef short s16;
typedef long s32;
typedef float f32;
typedef struct OSThread_s OSThread;
typedef void *OSMesg;
typedef struct OSMesgQueue_s
{
  OSThread *mtqueue;
  OSThread *fullqueue;
  s32 validCount;
  s32 first;
  s32 msgCount;
  OSMesg *msg;
} OSMesgQueue;
typedef union _PermuterTemp1 Mtx;
typedef union _PermuterTemp2 Vp;
typedef struct _PermuterTemp3 LookAt;
typedef union Color_RGBA8_u32
{
  struct 
  {
    u8 r;
    u8 g;
    u8 b;
    u8 a;
  };
  u32 rgba;
} Color_RGBA8_u32;
typedef float MtxF_t[4][4];
typedef union 
{
  MtxF_t mf;
  struct 
  {
    float xx;
    float yx;
    float zx;
    float wx;
    float xy;
    float yy;
    float zy;
    float wy;
    float xz;
    float yz;
    float zz;
    float wz;
    float xw;
    float yw;
    float zw;
    float ww;
  };
} MtxF;
typedef struct Vec3f
{
  f32 x;
  f32 y;
  f32 z;
} Vec3f;
typedef struct Vec3s
{
  s16 x;
  s16 y;
  s16 z;
} Vec3s;
struct unk_D_86002F58_004_000_00C;
typedef union arg1_func_80010CA8
{
  struct 
  {
    s16 unk_00;
    s8 unk_02;
    s8 unk_03;
  };
  u32 raw;
} arg1_func_80010CA8;
typedef struct unk_D_86002F58_004_000_00C_028 unk_D_86002F58_004_000_00C_028;
typedef unk_D_86002F58_004_000_00C_028 *(*unk_D_86002F58_004_000_00C_028_func)(s32, s32);
typedef struct unk_D_86002F58_004_000_010_024
{
  u16 unk_00;
  char unk02[0x6];
  struct unk_D_86002F58_004_000_004 *unk_08;
} unk_D_86002F58_004_000_010_024;
typedef struct unk_D_86002F58_004_000_010
{
  u8 unk_00;
  u8 unk_01;
  u8 unk_02;
  s32 unk_04[1];
  char pad8[0x10];
  s32 unk_18;
  s32 unk_1C;
  s32 unk_20;
  unk_D_86002F58_004_000_010_024 *unk_24;
  s32 unk_28;
  arg1_func_80010CA8 unk_2C;
  OSMesgQueue unk_30;
  OSMesg unk_48;
  char pad4C[0x4];
  OSMesgQueue unk_50;
  OSMesg unk_68;
  char pad6C[0x4];
} unk_D_86002F58_004_000_010;
typedef struct unk_D_86002F58_004_000_004
{
  struct unk_D_86002F58_004_000_004 *unk_00[4];
  struct unk_D_86002F58_004_000_00C *unk_10;
  unk_D_86002F58_004_000_010 *unk_14;
} unk_D_86002F58_004_000_004;
typedef struct unk_D_86002F58_004_000_00C
{
  unk_D_86002F58_004_000_004 unk_00;
  char unk_18[0x10];
  unk_D_86002F58_004_000_00C_028_func unk_28;
} unk_D_86002F58_004_000_00C;
typedef struct unk_D_86002F58_004_000_000
{
  u8 unk_00;
  u8 unk_01;
  u8 unk_02;
  u8 unk_03;
  struct unk_D_86002F58_004_000_000 *unk_04;
  struct unk_D_86002F58_004_000_000 *unk_08;
  unk_D_86002F58_004_000_00C *unk_0C;
  unk_D_86002F58_004_000_010 *unk_10;
  s32 unk_14;
} unk_D_86002F58_004_000_000;
typedef struct unk_D_86002F58_004_000_040_004
{
  s16 unk_00;
  char unk02[0x2];
  s16 unk_04;
  s16 unk_06;
  u16 unk_08;
  u16 unk_0A;
  u32 unk_0C;
  u32 unk_10;
  u32 unk_14;
  u32 unk_18;
} unk_D_86002F58_004_000_040_004;
typedef struct unk_D_86002F58_004_000_040
{
  s16 unk_00;
  unk_D_86002F58_004_000_040_004 *unk_04;
  s32 unk_08;
  u32 unk_0C;
  char unk10[0x2];
  u16 unk_12;
} unk_D_86002F58_004_000_040;
typedef struct unk_D_86002F58_004_000_054_004
{
  s16 unk_00;
  char unk_02[0x2];
  s16 unk_04;
  s16 unk_06;
  u16 unk_08;
  u16 unk_0A;
  void *unk_0C;
  void *unk_10;
} unk_D_86002F58_004_000_054_004;
typedef struct unk_D_86002F58_004_000_054
{
  s16 unk_00;
  unk_D_86002F58_004_000_054_004 *unk_04;
  s16 unk_08;
  u16 unk_0A;
} unk_D_86002F58_004_000_054;
typedef struct unk_D_86002F58_004_000_0A8
{
  u16 unk_00;
  u8 unk_02;
  Vec3f unk_04;
} unk_D_86002F58_004_000_0A8;
typedef struct unk_D_86002F58_004_000
{
  unk_D_86002F58_004_000_000 unk_000;
  s16 unk_018;
  s16 unk_01A;
  u8 unk_01C;
  u8 unk_01D;
  Vec3s unk_01E;
  Vec3f unk_024;
  Vec3f unk_030;
  Color_RGBA8_u32 unk_03C;
  unk_D_86002F58_004_000_040 unk_040;
  unk_D_86002F58_004_000_054 unk_054;
  MtxF unk_060;
  Color_RGBA8_u32 unk_0A0;
  char unk0A4[2];
  u8 unk_0A6;
  u8 unk_0A7;
  unk_D_86002F58_004_000_0A8 unk_0A8[1];
  char unk0B8[0x24];
  Vec3f unk_0DC;
  char unk0E0[0x4];
  Vec3f unk_0EC;
  char unk0F8[0x4];
  Vec3f unk_0FC;
  char unk108[0x60];
} unk_D_86002F58_004_000;
struct GraphNode;
typedef s32 (*func_D_86002F34_000_010)(s32, struct GraphNode *);
typedef struct GraphNode
{
  u8 unk_00;
  u8 unk_01;
  u8 unk_02;
  u8 unk_03;
  struct GraphNode *unk_04;
  struct GraphNode *unk_08;
  struct unk_D_86002F34_00C *unk_0C;
  func_D_86002F34_000_010 unk_10;
  void *unk_14;
} GraphNode;
typedef struct unk_D_86002F34_00C_018
{
  Vp *vp;
  s16 x;
  s16 y;
  s16 width;
  s16 height;
} unk_D_86002F34_00C_018;
typedef struct unk_D_86002F34_00C_024
{
  Mtx *mtx;
  u16 perspNorm;
  f32 fovy;
  f32 aspect;
  f32 near;
  f32 far;
  f32 scale;
} unk_D_86002F34_00C_024;
typedef struct unk_D_86002F34_00C_040
{
  Mtx *mtx;
  f32 l;
  f32 r;
  f32 b;
  f32 t;
  f32 n;
  f32 f;
  f32 scale;
} unk_D_86002F34_00C_040;
typedef struct unk_D_86002F34_00C_060
{
  MtxF *p_mtxf;
  MtxF mtxf;
  LookAt *lookat;
  Vec3f eye;
  Vec3f at;
  Vec3f up;
} unk_D_86002F34_00C_060;
typedef struct unk_D_86002F34_00C_0CC
{
  u16 unk_00;
  u16 unk_02;
  Color_RGBA8_u32 color;
  u16 unk_08;
  u16 unk_0A;
  s16 unk_0C;
  s16 unk_0E;
  s16 unk_10;
  s16 unk_12;
  s16 unk_14;
  s16 unk_16;
  s16 unk_18;
  s16 unk_1A;
  u8 *texture;
} unk_D_86002F34_00C_0CC;
typedef struct unk_D_86002F34_00C
{
  GraphNode unk_00;
  unk_D_86002F34_00C_018 unk_18;
  unk_D_86002F34_00C_024 unk_24;
  unk_D_86002F34_00C_040 unk_40;
  unk_D_86002F34_00C_060 unk_60;
  unk_D_86002F34_00C_0CC unk_CC;
  char unkEC[0x4];
} unk_D_86002F34_00C;
extern struct unk_D_86002F58_004_000_000 D_800AC840;
extern struct unk_D_86002F58_004_000_000 D_800AC858;
typedef struct unk_D_80072B00
{
  u8 unk_00;
  u8 unk_01;
  u8 unk_02;
  u8 unk_03;
  u8 unk_04;
  u8 unk_05;
} unk_D_80072B00;
extern unk_D_80072B00 D_80072B00[];
typedef struct Controller Controller;
typedef struct unk_D_800AE540_0004 unk_D_800AE540_0004;
typedef struct unk_D_800AE540_1194 unk_D_800AE540_1194;
typedef struct unk_D_800FCB18_044
{
  u8 unk_00;
  u8 unk_01;
  u8 unk_02;
  u8 unk_03;
  u8 unk_04;
  u8 unk_05;
} unk_D_800FCB18_044;
typedef struct unk_D_800FCB18
{
  u8 unk_00;
  u8 unk_01;
  char unk02[0x2];
  u8 unk_04;
  u8 unk_05;
  char unk06[0x5];
  u8 unk_0B;
  u16 unk_0C;
  u16 unk_0E;
  u16 unk_10;
  u16 unk_12;
  u8 unk_14;
  u8 unk_15;
  u8 unk_16[9];
  u8 unk_1F[4];
  char unk23[0x1];
  u16 unk_24;
  u8 unk_26;
  u16 unk_28;
  u16 unk_2A;
  u16 unk_2C;
  u16 unk_2E;
  u16 unk_30;
  u8 unk_32[4];
  u16 unk_36;
  u16 unk_38;
  u16 unk_3A;
  u16 unk_3C;
  u16 unk_3E;
  char unk40[0x4];
  unk_D_800FCB18_044 unk_44;
  u8 unk_4A;
  u8 unk_4B;
  u8 unk_4C;
  u8 unk_4D;
  u8 unk_4E;
  u8 unk_4F;
  u8 unk_50;
  u8 unk_51;
  u8 unk_52;
  u8 unk_53;
  u16 unk_54;
  u8 unk_56;
  u8 unk_57;
  u8 unk_58;
  u8 unk_59;
  u8 unk_5A;
  u8 unk_5B;
  u8 unk_5C[6];
  char unk62[0x2];
} unk_D_800FCB18;
struct unk_D_8140E720;
struct unk_D_84390010;
struct unk_D_8140E724;
typedef void (*func_unk_D_8140E724_008)(struct unk_D_8140E720 *);
typedef void (*func_unk_D_8140E724_00C)(struct unk_D_8140E720 *, unk_D_86002F34_00C *);
typedef struct unk_D_8140E728_01C_004_1 unk_D_8140E728_01C_004_1;
typedef union unk_D_8140E728_01C_004
{
  unk_D_8140E728_01C_004_1 *a;
  func_unk_D_8140E724_00C func;
} unk_D_8140E728_01C_004;
typedef struct unk_D_8140E728_01C
{
  s32 unk_00;
  unk_D_8140E728_01C_004 unk_04;
} unk_D_8140E728_01C;
typedef struct unk_D_8140E720
{
  struct unk_D_8140E720 *next;
  struct unk_D_8140E720 *prev;
  func_unk_D_8140E724_008 unk_08;
  unk_D_8140E728_01C *unk_0C;
  struct unk_D_84390010 *unk_10;
  unk_D_86002F58_004_000 *unk_14;
  u32 unk_18;
  f32 unk_1C;
  f32 unk_20;
  f32 unk_24;
  f32 unk_28;
  Vec3f unk_2C;
  Vec3f unk_38;
  char unk44[0xC];
  Vec3f unk_50;
  Vec3f unk_5C;
  Vec3f unk_68;
  f32 unk_74;
  f32 unk_78;
  Vec3f unk_7C;
  char unk88[0xC];
  Vec3s unk_94;
  Vec3s unk_9A;
  Vec3s unk_A0;
  s16 unk_A6;
  s16 unk_A8;
  s16 unk_AA;
  s16 unk_AC;
  s16 unk_AE;
  s16 unk_B0;
  s16 unk_B2;
  char unkB4[0x2];
  s16 unk_B6;
  s16 unk_B8;
  s16 unk_BA;
  s16 unk_BC;
  u8 prim_r;
  u8 prim_g;
  u8 prim_b;
  u8 env_r;
  u8 env_g;
  u8 env_b;
  u8 prim_a;
  char unkC5[0x1];
  s8 unk_C6;
  s8 unk_C7;
  char unkC8[0x2];
  u8 unk_CA;
  u8 unk_CB;
  u8 unk_CC;
  u8 unk_CD;
  u8 unk_CE;
  u8 unk_CF;
  s8 unk_D0;
} unk_D_8140E720;
typedef void (*func_unk_D_8140E724)(struct unk_D_8140E720 *);
typedef struct unk_D_8140E724
{
  func_unk_D_8140E724 unk_00;
  unk_D_8140E728_01C *unk_04;
  struct unk_D_84390010 *unk_08;
  s16 unk_0C;
  s16 unk_0E;
  s16 unk_10;
  s16 unk_12;
  s8 unk_14;
  s8 unk_15;
  u8 unk_16;
  u8 unk_17;
  u8 unk_18;
  u8 unk_19;
  u8 unk_1A;
  u8 unk_1B;
} unk_D_8140E724;
typedef struct unk_D_84390010_654_09C
{
  char unk00[0x10];
} unk_D_84390010_654_09C;
typedef struct unk_D_84390010_654_0AC
{
  char unk00[0x10];
} unk_D_84390010_654_0AC;
typedef struct unk_D_84390010_168
{
  unk_D_86002F58_004_000 unk_000;
  char unk168[0x1];
  u8 unk_169;
  s16 unk_16A;
  s16 unk_16C;
  char unk16E[0x2];
} unk_D_84390010_168;
typedef struct unk_D_84390010_654
{
  char unk00[0x4];
  u32 unk_04;
  s32 unk_08;
  s32 unk_0C;
  u32 unk_10;
  s32 unk_14;
  u32 unk_18;
  u8 unk_1C;
  u16 unk_1E;
  char unk20[0x8];
  u16 unk_28;
  u8 unk_2A;
  u8 unk_2B;
  u8 unk_2C;
  u8 unk_2D;
  u8 unk_2E;
  u8 unk_2F;
  u16 unk_30;
  char unk32[0x2];
  u16 unk_34;
  u16 unk_36;
  unk_D_800FCB18 unk_38;
  unk_D_84390010_654_09C unk_9C;
  unk_D_84390010_654_0AC unk_AC;
  s16 unk_BC;
  s16 unk_BE;
  char unkC0[1];
  u8 unk_C1[4];
  Controller *unk_C8;
} unk_D_84390010_654;
typedef struct unk_D_84390010_728_0168 unk_D_84390010_728_0168;
typedef struct unk_D_84390010_728
{
  unk_D_86002F58_004_000 unk_000;
  unk_D_84390010_728_0168 *unk_168;
  s32 unk_16C;
  s32 unk_170;
  char unk174[0x4];
  s32 unk_178;
  s32 unk_17C;
  s32 unk_180;
  s16 unk_184;
  s16 unk_186;
  f32 unk_188;
  s32 unk_18C;
  f32 unk_190;
  f32 unk_194;
  char unk198[0x4];
} unk_D_84390010_728;
typedef struct unk_D_84390010_8C4
{
  s32 unk_00;
  s32 unk_04;
  s8 unk_08[4];
  char unk0C[0x3C];
  s8 unk_48[4];
  char unk4C[0x3C];
} unk_D_84390010_8C4;
typedef struct unk_D_84390010_94C
{
  u8 unk_00[10];
  u8 unk_0A[4];
  char unk0E[0x12];
} unk_D_84390010_94C;
typedef struct unk_D_84390048
{
  Vec3f unk_00;
  Vec3f unk_0C;
  u8 unk_18;
  u8 unk_19;
  u8 unk_1A;
  u8 unk_1B;
  char unk1C[4];
} unk_D_84390048;
typedef struct unk_D_84390010_448
{
  Vec3f unk_00;
  Vec3f unk_0C;
  Vec3f unk_18;
  unk_D_84390048 unk_24;
  s16 unk_44;
  s16 unk_46;
  char unk48[0x4];
  f32 unk_4C;
} unk_D_84390010_448;
typedef struct unk_D_84390010
{
  unk_D_86002F58_004_000 unk_000;
  unk_D_84390010_168 unk_168[2];
  unk_D_84390010_448 unk_448;
  f32 unk_498;
  f32 unk_49C;
  f32 unk_4A0;
  s16 unk_4A4;
  s16 unk_4A6;
  s16 unk_4A8;
  s32 unk_4AC;
  s32 unk_4B0;
  s32 unk_4B4;
  s32 unk_4B8;
  char unk4BC[0x4];
  s32 unk_4C0;
  s32 unk_4C4;
  s32 unk_4C8;
  Vec3f unk_4CC;
  Vec3f unk_4D8;
  f32 unk_4E4;
  u8 unk_4E8;
  u8 unk_4E9;
  unk_D_86002F58_004_000 unk_4EC;
  unk_D_84390010_654 unk_654;
  unk_D_800AE540_1194 *unk_720;
  unk_D_800AE540_0004 *unk_724;
  unk_D_84390010_728 unk_728;
  unk_D_84390010_8C4 unk_8C4;
  unk_D_84390010_94C unk_94C;
  unk_D_84390010_94C unk_96C;
  unk_D_84390010_94C unk_98C;
  unk_D_84390010_94C unk_9AC;
  unk_D_84390010_94C unk_9CC;
  unk_D_84390010_94C unk_9EC;
} unk_D_84390010;
typedef struct unk_D_843C60AC
{
  u8 unk_00;
  u8 unk_01;
  u8 unk_02;
  u8 unk_03;
  u8 unk_04;
  u8 unk_05[1];
  char unk06[0xC];
  unk_D_800FCB18 unk_12;
} unk_D_843C60AC;
typedef struct unk_D_843C60A4
{
  u8 unk_00;
  u8 unk_01[2];
  u8 unk_03;
  u8 unk_04[2];
  u8 unk_06;
  u8 unk_07[1];
  u8 unk_08;
  u8 unk_09;
  u8 unk_0A[1];
  char unk0B[0x5];
  u8 unk_10;
  u8 unk_11;
  u8 unk_12;
  u8 unk_13;
  unk_D_843C60AC unk_14[1];
} unk_D_843C60A4;
typedef struct unk_func_843794CC
{
  u8 unk_00;
  u8 unk_01;
  u8 unk_02;
  u8 unk_03;
  u8 unk_04;
  u8 unk_05;
  u8 unk_06;
  u8 unk_07;
  u8 unk_08;
  s16 unk_0A;
  s16 unk_0C;
  s16 unk_0E;
  s16 unk_10;
  s16 unk_12;
  s16 unk_14;
  s16 unk_16;
  s16 unk_18;
  s16 unk_1A;
  s16 unk_1C;
  s16 unk_1E;
  s16 unk_20;
  s32 unk_24;
  s32 unk_28;
} unk_func_843794CC;
typedef struct unk_D_843C60F0_00C
{
  s32 unk_00;
  u8 unk_04;
  u8 unk_05;
  u8 unk_06;
  u8 unk_07;
  u8 unk_08;
  u8 unk_09;
  u8 unk_0A;
  u8 unk_0B;
  u8 unk_0C;
  u8 unk_0D;
  u8 unk_0E;
  u8 unk_0F;
  u8 unk_10;
  char unk11[0x3];
} unk_D_843C60F0_00C;
extern u8 D_8438AC60[];
extern unk_D_84390010 *D_84390010[2];
s32 func_843767E4(s32 arg0);
s32 func_84377068(s32 arg0, s32 arg1);
u16 func_8437731C(unk_D_800FCB18 *arg0);
u16 func_84377354(unk_D_800FCB18 *arg0);
f32 func_8437738C(u8 arg0, unk_D_800FCB18 *arg1);
s32 func_84377644(unk_D_843C60A4 *arg0, u8 arg1);
u8 func_843776FC(unk_D_843C60AC *arg0, unk_D_843C60AC *arg1, u8 arg2);
u8 func_843779C8(unk_D_843C60AC *arg0, unk_D_843C60AC *arg1, u8 arg2, u8 *arg3);
u8 func_84377FA4(unk_D_843C60AC *arg0, unk_D_843C60A4 *arg1, u8 *arg2, u8 arg3, u8 *arg4);
s32 func_843780FC(u8 arg0, u8 arg1);
u8 func_8437828C(unk_D_843C60AC *arg0, unk_D_843C60AC *arg1);
u8 func_843783CC(unk_D_843C60A4 *arg0);
u16 func_8437865C(unk_D_800FCB18 *arg0, unk_D_800FCB18 *arg1, u8 arg2);
s32 func_8437AC20(unk_func_843794CC *arg0, u8 arg1, u8 arg2);
s32 func_8437ACB0(unk_func_843794CC *arg0, u8 arg1, u8 arg2, u8 arg3);
u8 func_8437AEA4(unk_func_843794CC *arg0, u8 arg1, u8 arg2, u8 arg3);
void func_8437B0CC(unk_D_843C60A4 *arg0, unk_D_843C60A4 *arg1, u8 arg2, unk_func_843794CC *arg3, u8 arg4);
unk_D_843C60F0_00C *D_843C5564;
unk_D_800FCB18 *D_843C60B8;
s32 D_843C60BC;
s32 D_8438AFB0 = 0;
static u8 D_8438AFB4[] = {0x05, 0x0D, 0x0E, 0x12, 0x19, 0x5C, 0x20, 0x22, 0x24, 0x26, 0x3D, 0x37, 0x3A, 0x3B, 0x3F, 0x06, 0x42, 0x44, 0x45, 0x63, 0x48, 0x4C, 0x52, 0x55, 0x57, 0x59, 0x5A, 0x5B, 0x5E, 0x64, 0x66, 0x68, 0x73, 0x75, 0x76, 0x78, 0x79, 0x7E, 0x81, 0x82, 0x87, 0x8A, 0x8F, 0x9C, 0x56, 0x95, 0x99, 0x9D, 0xA1, 0xA4, 0x0F, 0x13, 0x39, 0x46, 0x94, 0x00};
static u8 D_8438AFEC[] = {0x16, 0x49, 0x4F, 0x34, 0x35, 0x7E, 0x37, 0x6E, 0x38, 0x51, 0x6A, 0x4F, 0x28, 0x6A, 0x29, 0x10, 0x12, 0x13, 0x9E, 0xA2, 0x77, 0x41, 0x23, 0x89, 0x55, 0x57, 0x1C, 0x9A, 0x2D, 0x28, 0x22, 0x1E, 0x20, 0x05, 0x76, 0x2F, 0x27, 0x6D, 0x2F, 0x66, 0x30, 0x72, 0x47, 0x4E, 0x50, 0x4A, 0x93, 0x8D, 0x3C, 0x5B, 0x59, 0x06, 0x9A, 0x32, 0x38, 0x02, 0x45, 0x2E, 0x7E, 0x91, 0x37, 0x42, 0x64, 0x86, 0x5E, 0x02, 0x43, 0x19, 0x4A, 0x23, 0x4B, 0x28, 0x5C, 0x6A, 0x58, 0x9D, 0x34, 0x53, 0x9C, 0x85, 0x31, 0x56, 0x1F, 0x1F, 0xA1, 0x3E, 0x3A, 0x8B, 0x97, 0x80, 0x83, 0x6D, 0x7A, 0x65, 0x14, 0x8A, 0x60, 0x0B, 0x98, 0x78, 0x99, 0x8C, 0x79, 0x7D, 0x9B, 0x88, 0x04, 0x6F, 0x7B, 0x7C, 0x1E, 0x20, 0x87, 0x84, 0x92, 0x6C, 0x38, 0x27, 0x7F, 0x37, 0x69, 0x70, 0xA3, 0x8E, 0x09, 0x07, 0x0C, 0x24, 0x96, 0x52, 0x39, 0x90, 0x62, 0x36, 0x2A, 0x53, 0xA0, 0x6E, 0x83, 0x6A, 0xA3, 0x13, 0x9C, 0x3B, 0x57, 0x8F, 0x23, 0x52, 0x3F, 0x5E, 0x76};
static u8 D_8438B084[] = {0x00, 0x00, 0x01, 0x00, 0x00, 0x03, 0x00, 0x03, 0x00, 0x01, 0x01, 0x00, 0x01, 0x03, 0x02, 0x00, 0x00, 0x01, 0x01, 0x00, 0x02, 0x01, 0x00, 0x03, 0x02, 0x03, 0x01, 0x03, 0x03, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x02, 0x00, 0x01, 0x01, 0x03, 0x02, 0x02, 0x03, 0x02, 0x03, 0x03, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
static u8 D_8438B0BC[] = {0x32, 0x75, 0x66, 0x76, 0x82};
static u8 D_8438B0C4[] = {0x63, 0x68, 0x80, 0x78, 0x14, 0x26, 0x99, 0x64, 0x5C, 0x24, 0x9C, 0x22, 0x3F, 0x53, 0x23, 0xA4, 0x66};
static u8 D_8438B0D8[] = {0xA, 0xB, 0xC, 0xD, 0xE, 0xF, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F, 0x40, 0x41};
static u8 D_8438B0F4[] = {0x27, 0x2B};
s32 func_843767E4(s32 arg0);
s32 func_84377068(s32 arg0, s32 arg1);
u16 func_8437731C(unk_D_800FCB18 *arg0);
u16 func_84377354(unk_D_800FCB18 *arg0);
f32 func_8437738C(u8 arg0, unk_D_800FCB18 *arg1);
s32 func_84377644(unk_D_843C60A4 *arg0, u8 arg1);
u8 func_843776FC(unk_D_843C60AC *arg0, unk_D_843C60AC *arg1, u8 arg2);
u8 func_843779C8(unk_D_843C60AC *arg0, unk_D_843C60AC *arg1, u8 arg2, u8 *arg3);
u8 func_84377FA4(unk_D_843C60AC *arg0, unk_D_843C60A4 *arg1, u8 *arg2, u8 arg3, u8 *arg4);
s32 func_843780FC(u8 arg0, u8 arg1);
u8 func_8437828C(unk_D_843C60AC *arg0, unk_D_843C60AC *arg1);
u8 func_843783CC(unk_D_843C60A4 *arg0);
u16 func_8437865C(unk_D_800FCB18 *arg0, unk_D_800FCB18 *arg1, u8 arg2);
s32 func_8437AC20(unk_func_843794CC *arg0, u8 arg1, u8 arg2);
s32 func_8437ACB0(unk_func_843794CC *arg0, u8 arg1, u8 arg2, u8 arg3);
u8 func_8437AEA4(unk_func_843794CC *arg0, u8 arg1, u8 arg2, u8 arg3);
void func_8437B0CC(unk_D_843C60A4 *arg0, unk_D_843C60A4 *arg1, u8 arg2, unk_func_843794CC *arg3, u8 arg4)
{
  u8 i;
  u8 j;
  u8 temp_s0;
  u8 sp104;
  u8 sp103;
  s32 spFC;
  s32 spF8;
  s32 var_s0;
  s32 var_s0_4;
  s32 var_s1;
  s32 var_s2;
  u8 var_s5;
  s32 var_v1_6;
  s32 var_v1_4;
  s32 var_v1_5;
  unk_D_800FCB18 *temp_s3;
  unk_D_800FCB18 *temp_s6;
  unk_D_843C60AC *temp_fp;
  unk_D_843C60AC *temp_s4;
  unk_func_843794CC *temp_s7;
  s32 spC0;
  u8 sp58;
  u8 sp78;
  u8 temp_t0;
  u8 padBC;
  u8 padBB;
  u8 spBA;
  u8 padB9;
  u8 padB8;
  u8 spB7;
  u8 spB6;
  u8 spB5;
  u8 spB4;
  unk_func_843794CC *temp_v0_4;
  unk_func_843794CC *temp_v0_5;
  s32 tmp1;
  s32 tmp2;
  s32 tmp3;
  unk_D_80072B00 *sp9C;
  s32 tmp4;
  s32 tmp5;
  s32 tmp6;
  f32 sp8C;
  sp58 = D_843C5564->unk_09;
  spBA = D_843C5564->unk_0E;
  temp_t0 = D_843C5564->unk_0A;
  spB5 = D_843C5564->unk_0B;
  spB7 = D_843C5564->unk_0C;
  spB6 = D_843C5564->unk_0D;
  sp78 = D_843C5564->unk_0F;
  spB4 = D_843C5564->unk_10;
  temp_fp = &arg0->unk_14[arg0->unk_10];
  temp_s4 = &arg1->unk_14[arg1->unk_10];
  temp_s6 = &temp_fp->unk_12;
  for (i = 0; i < arg2; i++)
  {
    spFC = 0;
    spF8 = 0;
    temp_s7 = &arg3[i];
    sp9C = &D_80072B00[temp_s7->unk_00 - 1];
    var_s5 = 1;
    temp_s0 = func_843780FC(temp_s6->unk_0B, temp_s7->unk_00);
    var_s1 = (((func_843767E4(4) * temp_s0) * sp78) * 3) / 2;
    switch (temp_s7->unk_03)
    {
      case 0x0:
        temp_s3 = &temp_s4->unk_12;
        if (arg4)
      {
        switch (temp_s7->unk_00)
        {
          case 0x44:
            if (temp_s3->unk_4C & 0x80)
          {
            var_s1 += spBA * 2;
          }
            if (func_8437AEA4(arg3, i, arg2, temp_s7->unk_0C * 2) != 0)
          {
            var_s1 = 1;
          }
            break;

          case 0x62:
            if (temp_s3->unk_4C & 0x40)
          {
            spF8 = 1;
          }
            break;

        }

      }
        break;

      case 0x1:

      case 0x20:
        if (arg4)
      {
        temp_s3 = &temp_s4->unk_12;
        if (((func_84377644(arg1, 7) == 0) && ((!(temp_s3->unk_4D & 0x10)) & 0xFFFFFFFFFFFFFFFFu)) && (temp_s3->unk_15 == 0))
        {
          var_s1 += spB7 * 5;
          if (func_843776FC(temp_fp, temp_fp, 0x8A) != 0)
          {
            var_s1 += spBA * 3;
          }
          if (func_8437ACB0(arg3, i, arg2, 0xB2) != 0)
          {
            var_s1 -= temp_t0 * 5;
          }
          if (func_8437AC20(arg3, arg2, 0xFF) != 0)
          {
            var_s1 = 1;
          }
        }
        else
        {
          spF8 = 1;
        }
      }
      else
      {
        if (func_843776FC(temp_fp, temp_fp, 0x8A) != 0)
        {
          var_s1 += spBA * 3;
        }
        var_s1 += spB7 * 5;
      }
        break;

      case 0x2:

      case 0x21:

      case 0x42:

      case 0x4D:
        temp_s3 = &temp_s4->unk_12;
        if (temp_s3)
      {
      }
        if ((((temp_s3->unk_15 == 0) && (temp_s3->unk_16[6] != 3)) && (temp_s3->unk_16[7] != 3)) && (!(temp_s3->unk_4D & 0x10)))
      {
        if (arg4)
        {
          if (temp_s7->unk_00 == 0x5C)
          {
            var_s0 = spB7;
            var_s1 += var_s0;
            var_s1 += var_s0 * func_843783CC(arg1);
            var_s1 += var_s0 * func_843779C8(temp_fp, temp_s4, 2, &sp104);
            var_s1 += var_s0 * func_843779C8(temp_fp, temp_s4, 0xE, &sp104);
            spC0 = temp_t0;
            var_s1 -= (spC0 * func_843779C8(temp_fp, temp_s4, 0, &sp104)) / 2;
            var_s1 += spBA * func_843776FC(temp_fp, temp_fp, 0x49);
            if (func_8437ACB0(arg3, i, arg2, 0xB2) != 0)
            {
              var_s1 -= spC0;
            }
          }
          var_s1 += spB7 * 2;
          var_s1 += (spB7 * 2) * func_843779C8(temp_fp, temp_s4, 0xE, &sp104);
          var_s1 -= ((temp_t0 * 2) * func_843779C8(temp_fp, temp_s4, 0, &sp104)) / 2;
          if (func_8437ACB0(arg3, i, arg2, 0xB2) != 0)
          {
            var_s1 -= temp_t0 * 2;
          }
          if ((((temp_s6->unk_2E >= temp_s3->unk_2E) && (func_8437AC20(arg3, arg2, 0xFF) != 0)) || ((temp_s4->unk_02 != 0xA5) && ((func_843776FC(temp_fp, temp_s4, 0x72) == 2) || (func_843776FC(temp_fp, temp_s4, 0x9C) == 2)))) || ((((temp_s7->unk_14 >= 0x9A) && (func_843783CC(arg0) != 0)) && (temp_s6->unk_5C[5] == 7)) && (temp_s3->unk_5C[4] == 7)))
          {
            var_s1 = 1;
          }
        }
        else
        {
          if (temp_s7->unk_00 == 0x5C)
          {
            var_s1 += spB7 * 4;
          }
          var_s1 += spB7 * 2;
        }
      }
      else
      {
        spF8 = 1;
      }
        break;

      case 0x4:

      case 0x22:
        temp_s3 = &temp_s4->unk_12;
        if (temp_s3)
      {
      }
        if ((((temp_s3->unk_15 == 0) && (temp_s3->unk_16[6] != 0x14)) && (temp_s3->unk_16[7] != 0x14)) && (!(temp_s3->unk_4D & 0x10)))
      {
        if (arg4)
        {
          var_s1 += spB7 * 2;
          if ((temp_s7->unk_14 >= 0x9A) && (func_843783CC(arg0) != 0))
          {
            var_s1 -= temp_t0 * 2;
          }
          if (func_8437ACB0(arg3, i, arg2, 0xB2) != 0)
          {
            var_s1 -= temp_t0 * 2;
          }
          if (((temp_s4->unk_02 != 0xA5) && ((func_843776FC(temp_fp, temp_s4, 0x72) == 2) || (func_843776FC(temp_fp, temp_s4, 0x9C) == 2))) || (func_8437AC20(arg3, arg2, 0xFF) != 0))
          {
            var_s1 = 1;
          }
        }
        else
        {
          var_s1 += spB7 * 2;
        }
      }
      else
      {
        spF8 = 1;
      }
        break;

      case 0x5:

      case 0x23:
        temp_s3 = &temp_s4->unk_12;
        if (((((func_84377644(arg1, 0x20) == 0) && (temp_s3->unk_15 == 0)) && (temp_s3->unk_16[6] != 0x19)) && (temp_s3->unk_16[7] != 0x19)) && (!(temp_s3->unk_4D & 0x10)))
      {
        if (arg4)
        {
          var_s1 += spB7 * 3;
          if (((func_843783CC(arg0) != 0) && (func_8437ACB0(arg3, i, arg2, 0x4D) == 0)) && (temp_s7->unk_14 >= 0x4E))
          {
            var_s1 += spB7 * 3;
          }
          if (func_8437ACB0(arg3, i, arg2, 0xB2) != 0)
          {
            var_s1 -= temp_t0 * 3;
          }
          if (func_8437AC20(arg3, arg2, 0xFF) != 0)
          {
            var_s1 = 1;
          }
        }
        else
        {
          var_s1 += spB7 * 6;
        }
      }
      else
      {
        spF8 = 1;
      }
        break;

      case 0x6:

      case 0x24:
        temp_s3 = &temp_s4->unk_12;
        if (temp_s3)
      {
      }
        if ((temp_s3->unk_16[6] == sp9C->unk_03) || (temp_s3->unk_16[7] == sp9C->unk_03))
      {
        spF8 = 1;
        break;
      }

      case 0x43:
        temp_s3 = &temp_s4->unk_12;
        if (arg4)
      {
        if (((temp_s3->unk_15 == 0) && (!(temp_s3->unk_4D & 0x10))) && ((sp9C->unk_03 != 0x17) || ((temp_s3->unk_16[6] != 4) && (temp_s3->unk_16[7] != 4))))
        {
          if (temp_s3->unk_2E >= temp_s6->unk_2E)
          {
            var_s1 += spB7 * 5;
            if (func_843779C8(temp_fp, temp_fp, 1, &sp104) == 2)
            {
              var_s1 += spBA * 3;
            }
            if (func_843779C8(temp_fp, temp_s4, 1, &sp104) == 2)
            {
              var_s1 += spB6 * 3;
            }
          }
          if ((func_84377FA4(temp_fp, arg0, &sp103, 1, &sp104) != 0) && (temp_s3->unk_2E >= arg0->unk_14[sp103].unk_12.unk_2E))
          {
            var_s1 += spBA * 3;
          }
          var_s1 += spB7 * 5;
          if (func_8437ACB0(arg3, i, arg2, 0xB2) != 0)
          {
            var_s1 -= temp_t0 * 5;
          }
          if (((temp_s4->unk_02 != 0xA5) && ((func_843776FC(temp_fp, temp_s4, 0x9C) == 2) || (func_843776FC(temp_fp, temp_s4, 0x72) == 2))) || (func_8437AC20(arg3, arg2, 0xFF) != 0))
          {
            var_s1 = 1;
          }
        }
        else
        {
          spF8 = 1;
        }
      }
      else
      {
        if (temp_s3->unk_2E >= temp_s6->unk_2E)
        {
          var_s1 += spB7 * 6;
        }
        var_s1 += spB7 * 6;
      }
        break;

      case 0x7:
        if (arg4)
      {
        if (func_843783CC(arg0) != 0)
        {
          spFC = 1;
          spF8 = 1;
        }
      }
      else
      {
        var_s1 += temp_t0 * 5;
      }
        break;

      case 0x8:
        temp_s3 = &temp_s4->unk_12;
        if (!(temp_s3->unk_15 & 7))
      {
        spF8 = 1;
      }
        break;

      case 0x9:
        temp_s3 = &temp_s4->unk_12;
        if (temp_s3)
      {
      }
        if ((temp_s6->unk_2E >= temp_s3->unk_2E) && (temp_s3->unk_58 == 0))
      {
        spF8 = 1;
      }
        break;

      case 0x32:
        if (temp_s6->unk_5C[0] < 0xC)
      {
        var_s5 = 2;
      }

      case 0xA:
        if (arg4)
      {
        if ((temp_s6->unk_5C[0] < 0xD) && (temp_s6->unk_2A < 0x3E7))
        {
          var_s0 = 1;
          var_s1 += spB7 * 6;
          if (temp_s7->unk_14 >= 0x9A)
          {
            var_s1 -= temp_t0 * 6;
          }
          else
            if (func_843776FC(temp_fp, temp_fp, 0x3F) != 0)
          {
            var_s1 += spBA * 5;
          }
          if (temp_s7->unk_14 == 0xFF)
          {
            var_s1 -= temp_t0 * 6;
          }
          var_s1 *= (0xD - temp_s6->unk_5C[0]) / 12.0f;
          for (j = 0; j < arg2; j++)
          {
            temp_v0_4 = &arg3[j];
            if ((D_80072B00[temp_v0_4->unk_00 - 1].unk_03 < 0xA) && (temp_v0_4->unk_0A != 0))
            {
              var_s0 = 0;
            }
          }

          if (var_s0 != 0)
          {
            var_s1 = 1;
          }
          if ((func_843776FC(temp_fp, temp_s4, 0x72) == 2) && (temp_s4->unk_02 != 0xA5))
          {
            var_s1 = 1;
          }
        }
        else
        {
          spF8 = 1;
        }
      }
      else
      {
        if (func_843776FC(temp_fp, temp_fp, 0x3F) != 0)
        {
          var_s1 += spBA * 5;
        }
        var_s0 = 1;
        var_s1 += spB7 * 4;
        for (j = 0; j < arg2; j++)
        {
          temp_v0_5 = &arg3[j];
          if ((D_80072B00[temp_v0_5->unk_00 - 1].unk_03 < 0xA) && (temp_v0_5->unk_0A != 0))
          {
            var_s0 = 0;
          }
        }

        if (var_s0 != 0)
        {
          var_s1 = 1;
        }
      }
        var_s1 *= var_s5;
        break;

      case 0x33:
        if (temp_s6->unk_5C[1] < 0xC)
      {
        var_s5 = 2;
      }

      case 0xB:
        if (arg4)
      {
        if ((temp_s6->unk_5C[1] < 0xD) && (temp_s6->unk_2C < 0x3E7))
        {
          var_s1 += spB6 * 6;
          if (temp_s7->unk_14 >= 0x9A)
          {
            var_s1 -= temp_t0 * 6;
          }
          else
            if (D_80072B00[temp_s7->unk_05 - 1].unk_03 < 0xA)
          {
            var_s1 += spB6 * 6;
          }
          if (temp_s7->unk_14 == 0xFF)
          {
            var_s1 -= temp_t0 * 6;
          }
          var_s1 *= (0xD - temp_s6->unk_5C[1]) / 12.0f;
          if ((func_843783CC(arg1) != 0) && (temp_s4->unk_12.unk_15 & 0x20))
          {
            var_s1 = 1;
          }
          if ((func_843776FC(temp_fp, temp_s4, 0x72) == 2) && (temp_s4->unk_02 != 0xA5))
          {
            var_s1 = 1;
          }
        }
        else
        {
          spF8 = 1;
        }
      }
      else
      {
        if (D_80072B00[temp_s7->unk_05 - 1].unk_03 < 0xA)
        {
          var_s1 += spB6 * 4;
        }
        var_s1 += spB6 * 4;
      }
        var_s1 *= var_s5;
        break;

      case 0x34:
        if (temp_s6->unk_5C[2] < 0xC)
      {
        var_s5 = 2;
      }
        if (arg4)
      {
        temp_s3 = &temp_s4->unk_12;
        if ((temp_s6->unk_5C[2] < 0xD) && ((temp_s6->unk_2E < 0x3E7) != 0))
        {
          if (temp_s3->unk_2E >= temp_s6->unk_2E)
          {
            var_s1 += spB7 * 3;
            if (temp_s3->unk_2E < func_8437731C(temp_s6))
            {
              if (func_843779C8(temp_fp, temp_fp, 1, &sp104) == 2)
              {
                var_s1 += spBA * 3;
              }
              if (func_843779C8(temp_fp, temp_s4, 1, &sp104) == 2)
              {
                var_s1 += spB6 * 3;
              }
            }
          }
          if (temp_s7->unk_14 >= 0x9A)
          {
            var_s1 -= (temp_t0 * 3) * var_s5;
          }
          if (temp_s7->unk_14 == 0xFF)
          {
            var_s1 -= (temp_t0 * 3) * var_s5;
          }
          if ((func_843776FC(temp_fp, temp_s4, 0x72) == 2) && (temp_s4->unk_02 != 0xA5))
          {
            var_s1 = 1;
          }
          if ((func_843783CC(arg1) != 0) && (func_8437731C(temp_s6) < temp_s3->unk_2E))
          {
            var_s1 = 1;
          }
        }
        else
        {
          spF8 = 1;
        }
      }
      else
      {
        if (func_843779C8(temp_fp, temp_fp, 1, &sp104) != 0)
        {
          var_s1 += spBA * 5;
        }
        var_s1 += spB7 * 3;
      }
        var_s1 *= var_s5;
        break;

      case 0x35:
        if (temp_s6->unk_5C[3] < 0xC)
      {
        var_s5 = 2;
      }

      case 0xD:
        if (arg4)
      {
        if ((temp_s6->unk_5C[3] < 0xD) && (temp_s6->unk_30 < 0x3E7))
        {
          var_s1 += spB7 * 7;
          if (temp_s7->unk_14 >= 0x9A)
          {
            var_s1 -= temp_t0 * 7;
          }
          else
            if (D_80072B00[temp_s7->unk_05 - 1].unk_03 >= 0xB)
          {
            var_s1 += spB6 * 7;
          }
          if (temp_s7->unk_14 == 0xFF)
          {
            var_s1 -= temp_t0 * 7;
          }
          var_s1 *= (0xD - temp_s6->unk_5C[3]) / 12.0f;
          if ((func_843776FC(temp_fp, temp_s4, 0x72) == 2) && (temp_s4->unk_02 != 0xA5))
          {
            var_s1 = 1;
          }
        }
        else
        {
          spF8 = 1;
        }
      }
      else
      {
        if (D_80072B00[temp_s7->unk_05 - 1].unk_03 >= 0xB)
        {
          var_s1 += spB6 * 2;
        }
        var_s1 += spB7 * 2;
        var_s1 += spB6 * 3;
      }
        var_s1 *= var_s5;
        break;

      case 0xF:
        temp_s3 = &temp_s4->unk_12;
        if (arg4)
      {
        if (temp_s6->unk_5C[5] < 0xD)
        {
          var_s1 += spB6 * 7;
          if (func_843779C8(temp_fp, temp_s4, 0, &sp104) != 0)
          {
            var_s1 += (spB6 * 7) / 2;
          }
          if ((temp_s6->unk_15 & 8) || (temp_s6->unk_4D & 0x80))
          {
            var_s1 /= 2;
          }
          if (temp_s6->unk_4E & 1)
          {
            var_s1 /= 2;
          }
          if ((func_843783CC(arg1) != 0) && (temp_s3->unk_15 & 0x20))
          {
            var_s1 = 1;
          }
          if ((func_843776FC(temp_fp, temp_s4, 0x72) == 2) && (temp_s4->unk_02 != 0xA5))
          {
            var_s1 = 1;
          }
          if ((func_843776FC(temp_fp, temp_s4, 0x81) == 2) && (temp_s7->unk_05 == 0x81))
          {
            var_s1 = 1;
          }
          var_s1 *= (0xD - temp_s6->unk_5C[5]) / 12.0f;
        }
        else
        {
          spF8 = 1;
        }
      }
      else
      {
        var_s1 += spB6 * 7;
      }
        break;

      case 0x12:

      case 0x44:
        temp_s3 = &temp_s4->unk_12;
        if (arg4)
      {
        if ((temp_s3->unk_5C[0] >= 2) && (temp_s3->unk_2A >= 2))
        {
          var_s1 += spB6 * 5;
          if (func_8437ACB0(arg3, i, arg2, 0x99) != 0)
          {
            var_s1 -= temp_t0 * 5;
          }
          if ((temp_s7->unk_14 >= 0x9A) && (func_843783CC(arg0) != 0))
          {
            var_s1 -= temp_t0 * 5;
          }
          var_s1 *= (temp_s3->unk_5C[0] - 1) / 12.0f;
          if (func_8437AC20(arg3, arg2, 0xFF) != 0)
          {
            var_s1 = 1;
          }
          if ((func_843783CC(arg1) != 0) && (temp_s3->unk_15 & 0x20))
          {
            var_s1 = 1;
          }
          if ((func_843776FC(temp_fp, temp_s4, 0x72) == 2) && (temp_s4->unk_02 != 0xA5))
          {
            var_s1 = 1;
          }
        }
        else
        {
          spF8 = 1;
        }
      }
      else
      {
        var_s1 += spB6 * 4;
      }
        break;

      case 0x3B:
        if (temp_s4->unk_12.unk_5C[1] >= 3)
      {
        var_s5 = 2;
      }

      case 0x13:

      case 0x45:
        temp_s3 = &temp_s4->unk_12;
        if (arg4)
      {
        if ((temp_s3->unk_5C[1] >= 2) && (temp_s3->unk_2C >= 2))
        {
          var_s1 += spB7 * 5;
          if (temp_s3->unk_4C & 0x80)
          {
            var_s1 += spBA * 5;
          }
          if ((temp_s7->unk_14 >= 0x9A) && (func_843783CC(arg0) != 0))
          {
            var_s1 -= temp_t0 * 5;
          }
          if (func_8437ACB0(arg3, i, arg2, 0x99) != 0)
          {
            var_s1 -= temp_t0 * 5;
          }
          var_s1 *= (temp_s3->unk_5C[1] - 1) / 12.0f;
          if (func_8437AC20(arg3, arg2, 0xFF) != 0)
          {
            var_s1 = 1;
          }
          if ((func_843776FC(temp_fp, temp_s4, 0x72) == 2) && (temp_s4->unk_02 != 0xA5))
          {
            var_s1 = 1;
          }
        }
        else
        {
          spF8 = 1;
        }
      }
      else
      {
        var_s1 += spB7 * 4;
      }
        var_s1 *= var_s5;
        break;

      case 0x14:

      case 0x46:
        temp_s3 = &temp_s4->unk_12;
        if (arg4)
      {
        if ((temp_s3->unk_5C[2] >= 2) && ((temp_s3->unk_2E < 2) == 0))
        {
          if (temp_s3->unk_2E >= temp_s6->unk_2E)
          {
            var_s1 += spB7 * 3;
            if (func_84377354(temp_s3) < temp_s6->unk_2E)
            {
              if (func_843779C8(temp_fp, temp_fp, 1, &sp104) == 2)
              {
                var_s1 += spBA * 3;
              }
              if (func_843779C8(temp_fp, temp_s4, 1, &sp104) == 2)
              {
                var_s1 += spB6 * 3;
              }
            }
          }
          if (func_84377FA4(temp_fp, arg0, &sp103, 1, &sp104) != 0)
          {
            if ((func_84377354(temp_s3) < arg0->unk_14[sp103].unk_12.unk_2E) && (temp_s3->unk_2E >= arg0->unk_14[sp103].unk_12.unk_2E))
            {
              var_s1 += spBA * 3;
            }
          }
          if (func_8437ACB0(arg3, i, arg2, 0x99) != 0)
          {
            var_s1 -= temp_t0 * 3;
          }
          if (func_8437AC20(arg3, arg2, 0xFF) != 0)
          {
            var_s1 = 1;
          }
          if ((func_843783CC(arg0) != 0) && (temp_s6->unk_2E < func_84377354(temp_s3)))
          {
            var_s1 = 1;
          }
          if ((func_843776FC(temp_fp, temp_s4, 0x72) == 2) && (temp_s4->unk_02 != 0xA5))
          {
            var_s1 = 1;
          }
        }
        else
        {
          spF8 = 1;
        }
      }
      else
      {
        if (func_843779C8(temp_fp, temp_fp, 1, &sp104) != 0)
        {
          var_s1 += spBA * 5;
        }
        var_s1 += spB7 * 3;
      }
        break;

      case 0x47:
        temp_s3 = &temp_s4->unk_12;
        if (arg4)
      {
        if ((temp_s3->unk_5C[3] >= 2) && (temp_s3->unk_30 >= 2))
        {
          var_s1 += spB7 * 7;
          var_s1 += spB6 * 7;
          if (func_8437ACB0(arg3, i, arg2, 0x99) != 0)
          {
            var_s1 -= temp_t0 * 7;
          }
          else
            if (D_80072B00[temp_s7->unk_05 - 1].unk_03 >= 0xB)
          {
            var_s1 += spB6 * 7;
          }
          if (func_8437AC20(arg3, arg2, 0xFF) != 0)
          {
            var_s1 -= temp_t0 * 7;
          }
          var_s1 *= (temp_s3->unk_5C[3] - 1) / 12.0f;
          if ((func_843783CC(arg0) != 0) && (temp_s7->unk_14 >= 0xE7))
          {
            var_s1 = 1;
          }
          if ((func_843776FC(temp_fp, temp_s4, 0x72) == 2) && (temp_s4->unk_02 != 0xA5))
          {
            var_s1 = 1;
          }
        }
        else
        {
          spF8 = 1;
        }
      }
      else
      {
        var_s1 += spB7 * 2;
        var_s1 += spB6 * 3;
      }
        break;

      case 0x16:

      case 0x48:
        temp_s3 = &temp_s4->unk_12;
        if (arg4)
      {
        if (temp_s3->unk_5C[4] >= 2)
        {
          var_s1 += spB6 * 6;
          if (func_8437ACB0(arg3, i, arg2, 0x99) != 0)
          {
            var_s1 -= temp_t0 * 7;
          }
          if ((temp_s3->unk_15 & 8) || (temp_s3->unk_4D & 0x80))
          {
            var_s1 *= 2;
          }
          var_s1 *= (temp_s3->unk_5C[4] - 1) / 12.0f;
          if ((func_843783CC(arg1) != 0) && (temp_s3->unk_15 & 0x20))
          {
            var_s1 = 1;
          }
          if ((func_843776FC(temp_fp, temp_s4, 0x72) == 2) && (temp_s4->unk_02 != 0xA5))
          {
            var_s1 = 1;
          }
          if ((func_843776FC(temp_fp, temp_s4, 0x81) == 2) && (temp_s7->unk_05 == 0x81))
          {
            var_s1 = 1;
          }
        }
        else
        {
          spF8 = 1;
        }
      }
      else
      {
        var_s1 += spB6 * 6;
      }
        break;

      case 0x18:
        temp_s3 = &temp_s4->unk_12;
        if (arg4)
      {
        if ((temp_s3->unk_16[6] != temp_s6->unk_16[6]) || (temp_s3->unk_16[7] != temp_s6->unk_16[7]))
        {
          var_s1 += spB4 * 3;
          sp8C = func_8437738C(D_80072B00[temp_s7->unk_05 - 1].unk_03, temp_s6);
          if ((sp8C - func_8437738C(D_80072B00[temp_s7->unk_05 - 1].unk_03, temp_s3)) > 0.0)
          {
            var_s1 += spB6 * 3;
          }
          if (temp_s7->unk_14 >= 0x9A)
          {
            var_s1 -= temp_t0 * 3;
          }
        }
      }
      else
        if ((temp_s3->unk_16[6] != temp_s6->unk_16[6]) || (temp_s3->unk_16[7] != temp_s6->unk_16[7]))
      {
        var_s1 += spB4 * 3;
      }
        break;

      case 0x19:
        temp_s3 = &temp_s4->unk_12;
        if (arg4)
      {
        var_s0 = 0;
        var_v1_5 = temp_s6->unk_15;
        switch (var_v1_5)
        {
          case 0x0:
            break;

          case 0x8:
            var_s1 += spB6 * 2;
            if (temp_s6->unk_4E & 1)
          {
            var_s1 += spB6;
          }
            goto case_20;

          case 0x10:
            var_s1 += spB6 * 2;
            var_s0 = 1;
            goto case_20;

          case 0x40:
            var_s1 += spB6 * 5;

          default:

          case 0x20:
            case_20:
          var_s0 = 1;

            break;

        }

        if (temp_s3->unk_15 != 0)
        {
          var_s0 = 1;
          switch (var_v1_5)
          {
            case 8:
              var_s1 -= spB7 * 2;
              if (temp_s6->unk_4E & 1)
            {
              var_s1 -= spB7 / 2;
            }
              break;

            case 16:
              var_s1 -= (spB7 * 2) / 2;
              break;

            case 32:
              var_s1 = 1;
              break;

            case 64:
              var_s1 -= spB7 * 5;
              break;

            default:
              var_s1 -= (spB7 * 5) / 2;

          }

        }
        if (temp_s6->unk_5C[0] != 7)
        {
          var_s1 += (temp_s6->unk_5C[0] * 6) - 0x2A;
          var_s0 = 1;
        }
        if (temp_s6->unk_5C[1] != 7)
        {
          var_s1 += (temp_s6->unk_5C[1] * 6) - 0x2A;
          var_s0 = 1;
        }
        if (temp_s6->unk_5C[2] != 7)
        {
          var_s1 += (temp_s6->unk_5C[2] * 3) - 0x15;
          var_s0 = 1;
        }
        if (temp_s6->unk_5C[3] != 7)
        {
          var_s1 += (temp_s6->unk_5C[3] * 7) - 0x31;
          var_s0 = 1;
        }
        if (temp_s6->unk_5C[5] != 7)
        {
          var_s1 += (temp_s6->unk_5C[4] * 7) - 0x31;
          var_s0 = 1;
        }
        if (temp_s3->unk_5C[0] != 7)
        {
          var_s1 = (var_s1 - (temp_s3->unk_5C[0] * 5)) + 0x23;
          var_s0 = 1;
        }
        if (temp_s3->unk_5C[1] != 7)
        {
          var_s1 = (var_s1 - (temp_s3->unk_5C[1] * 5)) + 0x23;
          var_s0 = 1;
        }
        if (temp_s3->unk_5C[2] != 7)
        {
          var_s1 = (var_s1 - (temp_s3->unk_5C[2] * 3)) + 0x15;
          var_s0 = 1;
        }
        if (temp_s3->unk_5C[3] != 7)
        {
          var_s1 = (0, (var_s1 - (temp_s3->unk_5C[3] * 7)) + 0x31);
          var_s0 = 1;
        }
        if (temp_s3->unk_5C[4] != 7)
        {
          var_s1 = (var_s1 - (temp_s3->unk_5C[4] * 6)) + 0x2A;
          var_s0 = 1;
        }
        if (var_s0 == 0)
        {
          spF8 = 1;
        }
      }
      else
      {
        var_s1 += spB6 * 5;
      }
        break;

      case 0x1A:
        temp_s3 = &temp_s4->unk_12;
        if (arg4)
      {
        if (temp_s3->unk_4C & 0x80)
        {
          var_s1 += spBA * 3;
          if (func_8437ACB0(arg3, i, arg2, 0x99) != 0)
          {
            var_s1 -= temp_t0 * 3;
          }
          if (temp_s7->unk_14 >= 0x81)
          {
            var_s1 = 1;
          }
        }
        if ((func_843783CC(arg1) != 0) && (temp_s3->unk_15 & 0x20))
        {
          var_s1 = 1;
        }
      }
        break;

      case 0x2E:
        if (arg4)
      {
        if (!(temp_s6->unk_4D & 2))
        {
          for (j = 0; j < 6; j++)
          {
            if (temp_s6->unk_5C[j] < 6)
            {
              break;
            }
          }

          if (!((((f32) temp_s6->unk_0C) / temp_s6->unk_28) < ((D_843C5564->unk_08 + 0x33) / 255.0f)))
          {
            var_s1 += spB6 * 2;
            if ((func_843783CC(arg1) != 0) && (temp_s4->unk_12.unk_15 & 0x20))
            {
              var_s1 = 1;
            }
          }
        }
        else
        {
          spF8 = 1;
        }
      }
      else
      {
        var_s1 += spB6 * 3;
      }
        break;

      case 0x2F:
        if (arg4)
      {
        if (!(temp_s6->unk_4D & 4))
        {
          if (D_8438AC60[0] == 1)
          {
            var_s1 += spB7 * 3;
            if (temp_s7->unk_14 >= 0x9A)
            {
              var_s1 -= temp_t0 * 3;
            }
          }
          if ((func_843776FC(temp_fp, temp_s4, 0x72) == 2) && (temp_s4->unk_02 != 0xA5))
          {
            var_s1 /= 2;
          }
        }
        else
        {
          spF8 = 1;
        }
      }
      else
        if (D_8438AC60[0] == 1)
      {
        var_s1 += spB7 * 3;
      }
        break;

      case 0x31:
        temp_s3 = &temp_s4->unk_12;
        if (arg4)
      {
        if ((!(temp_s3->unk_4C & 0x80)) && (!(temp_s3->unk_4D & 0x10)))
        {
          var_s1 += spB7 * 4;
          if (((func_843776FC(temp_fp, temp_fp, 0x75) != 0) || (func_843776FC(temp_fp, temp_fp, 0x44) != 0)) || (func_843779C8(temp_fp, temp_fp, 0x15, &sp104) != 0))
          {
            var_s1 += spBA * 4;
          }
          if (func_8437ACB0(arg3, i, arg2, 0x99) != 0)
          {
            var_s1 -= temp_t0 * 4;
          }
          if (func_8437AC20(arg3, arg2, 0xFF) != 0)
          {
            var_s1 = 1;
          }
          if ((func_843783CC(arg1) != 0) && (temp_s3->unk_15 & 0x20))
          {
            var_s1 = 1;
          }
        }
        else
        {
          spF8 = 1;
        }
      }
      else
      {
        var_s1 += spB6 * 4;
      }
        break;

      case 0x38:
        if (arg4)
      {
        if (temp_s6->unk_0C != temp_s6->unk_28)
        {
          var_s1 = 1;
          switch (temp_s7->unk_00)
          {
            case 0x69:

            case 0x87:
              temp_s3 = &temp_s4->unk_12;
              if (temp_s3)
            {
            }
              if ((temp_s3->unk_2E < temp_s6->unk_2E) || ((temp_s6->unk_2E == temp_s3->unk_2E) && (func_843767E4(1) != 0)))
            {
              if (func_84377068(temp_s6->unk_0C - temp_s7->unk_16, temp_s6->unk_28) >= (D_843C5564->unk_08 + 0x33))
              {
                if ((func_843776FC(temp_fp, temp_s4, 0x62) != 0) && (func_843767E4(1) != 0))
                {
                  var_v1_4 = func_8437865C(temp_s3, temp_s6, 0x62);
                }
                else
                {
                  var_v1_4 = 0;
                }
                if (((((temp_s6->unk_0C - temp_s7->unk_16) - temp_s7->unk_12) - var_v1_4) >= 0) || (func_8437AC20(arg3, arg2, 0xFF) != 0))
                {
                  break;
                }
              }
              var_s1 = (spB6 * 7) + 1;
            }
            else
              if (func_84377068((temp_s6->unk_0C - temp_s7->unk_12) - temp_s7->unk_16, temp_s6->unk_28) < (D_843C5564->unk_08 + 0x33))
            {
              var_s1 = (spB6 * 7) + 1;
            }
              break;

            case 0x9C:
              temp_s3 = &temp_s4->unk_12;
              if (temp_s3)
            {
            }
              if ((temp_s3->unk_2E < temp_s6->unk_2E) || ((temp_s3->unk_2E == temp_s6->unk_2E) && (func_843767E4(1) != 0)))
            {
              if ((func_84377068(temp_s6->unk_0C - temp_s7->unk_16, temp_s6->unk_28) < (D_843C5564->unk_08 - 0x33)) || (((((temp_s6->unk_0C - temp_s7->unk_16) - temp_s7->unk_12) - (((func_843776FC(temp_fp, temp_s4, 0x62) != 0) && (func_843767E4(1) != 0)) ? (func_8437865C(temp_s3, temp_s6, 0x62)) : (0))) < 0) && (func_8437AC20(arg3, arg2, 0xFF) == 0)))
              {
                var_s1 = (spB6 * 7) + 1;
              }
            }
            else
            {
              if (func_84377068((temp_s6->unk_0C - temp_s7->unk_12) - temp_s7->unk_16, temp_s6->unk_28) < (D_843C5564->unk_08 - 0x33))
              {
                var_s1 = (spB6 * 7) + 1;
              }
              if ((func_843779C8(temp_fp, temp_s4, 1, &sp104) == 2) && (temp_s6->unk_15 & 0x40))
              {
                var_s1 += spB6 * 7;
              }
            }
              switch (temp_s6->unk_15)
            {
              case 8:

              case 0x10:
                break;

              case 0x40:
                var_s1 += spB6 * 6;
                if ((func_843779C8(temp_fp, temp_s4, 1, &sp104) == 2) && (temp_s6->unk_2E < temp_s3->unk_2E))
              {
                var_s1 += spB6 * 7;
              }
                break;

            }

              if (temp_s7->unk_14 >= 0x81)
            {
              var_s1 >>= 1;
            }
              break;

          }

          if (func_843783CC(arg0) != 0)
          {
            var_s1 *= 2;
          }
          if (temp_s7->unk_14 >= 0x81)
          {
            var_s1 >>= 1;
          }
        }
        else
        {
          spF8 = 1;
        }
      }
      else
      {
        var_s1 += spB6 * 8;
      }
        break;

      case 0x39:
        temp_s3 = &temp_s4->unk_12;
        if (temp_s3)
      {
      }
        if (((temp_s3->unk_4E & 8) != 0) || (temp_s3->unk_0B == 0x84))
      {
        if ((temp_s3->unk_4E & 8) != 0)
        {
          if (temp_s3 == D_843C60B8)
          {
            var_v1_4 = D_84390010[0]->unk_654.unk_BE != 0x84;
          }
          else
          {
            var_v1_4 = D_84390010[1]->unk_654.unk_BE != 0x84;
          }
          if (var_v1_4 == 0)
          {
            break;
          }
        }
        else
        {
          break;
        }
      }
        var_s1 += spB4 * 3;
        break;

      case 0x40:
        if (arg4)
      {
        if (!(temp_s6->unk_4E & 2))
        {
          var_s1 += spB6 * 7;
          if (D_80072B00[temp_s7->unk_05 - 1].unk_03 >= 0xB)
          {
            var_s1 += spB6 * 7;
          }
          if (temp_s7->unk_14 >= 0x9A)
          {
            var_s1 -= temp_t0 * 7;
          }
          if (temp_s7->unk_14 == 0xFF)
          {
            var_s1 -= temp_t0 * 7;
          }
          if ((func_843776FC(temp_fp, temp_s4, 0x72) == 2) && (temp_s4->unk_02 != 0xA5))
          {
            var_s1 = 1;
          }
          if ((func_843783CC(arg1) != 0) && (temp_s4->unk_12.unk_15 & 0x20))
          {
            var_s1 = 1;
          }
        }
        else
        {
          spF8 = 1;
        }
      }
      else
      {
        if (D_80072B00[temp_s7->unk_05 - 1].unk_03 >= 0xB)
        {
          var_s1 += spB6 * 3;
        }
        var_s1 += spB6 * 3;
      }
        break;

      case 0x41:
        if (arg4)
      {
        if (!(temp_s6->unk_4E & 4))
        {
          var_s1 += spB6 * 6;
          if (D_80072B00[temp_s7->unk_05 - 1].unk_03 < 0xA)
          {
            var_s1 += spB6 * 6;
          }
          if (temp_s7->unk_14 >= 0x9A)
          {
            var_s1 -= temp_t0 * 6;
          }
          if (temp_s7->unk_14 == 0xFF)
          {
            var_s1 -= temp_t0 * 6;
          }
          if ((func_843776FC(temp_fp, temp_s4, 0x72) == 2) && (temp_s4->unk_02 != 0xA5))
          {
            var_s1 = 1;
          }
          if ((func_843783CC(arg1) != 0) && (temp_s4->unk_12.unk_15 & 0x20))
          {
            var_s1 = 1;
          }
        }
        else
        {
          spF8 = 1;
        }
      }
      else
      {
        if (D_80072B00[temp_s7->unk_05 - 1].unk_03 < 0xA)
        {
          var_s1 += spB6 * 3;
        }
        var_s1 += spB6 * 3;
      }
        break;

      case 0x4F:
        if (((temp_s6->unk_28 >> 2) < temp_s6->unk_0C) && (!(temp_s6->unk_4D & 0x10)))
      {
        if ((func_843783CC(arg0) != 0) && (func_843776FC(temp_fp, temp_s4, 0x90) == 0))
        {
          if ((((D_843C60BC == 0) || ((D_843C60BC != 0) && (temp_s4->unk_12.unk_2E >= temp_s6->unk_2E))) && (temp_s6->unk_15 == 0)) && ((func_843779C8(temp_fp, temp_s4, 4, &sp104) == 2) || ((func_843779C8(temp_fp, temp_s4, 4, &sp104) == 1) && (func_843767E4(2) != 0))))
          {
            var_s1 += spB6 * 7;
            if (func_8437828C(temp_fp, temp_s4) != 0)
            {
              var_s1 += spB6 * 7;
            }
          }
          if (func_84377068(temp_s7->unk_12, temp_s6->unk_28) < 0x3F)
          {
            var_s1 += spB6 * 7;
            if (func_843779C8(temp_fp, temp_fp, 2, &sp104) == 2)
            {
              var_s1 += spB6 * 7;
            }
          }
          if (func_843779C8(temp_fp, temp_s4, 1, &sp104) == 2)
          {
            var_s1 += spB6 * 7;
          }
        }
        else
        {
          var_s1 = 1;
        }
      }
      else
      {
        spF8 = 1;
      }
        break;

      case 0x52:
        if (arg4)
      {
        var_s1 += spB4 * 3;
        if (func_8437ACB0(arg3, i, arg2, 0xB2) != 0)
        {
          var_s1 -= temp_t0 * 3;
        }
        if ((temp_s7->unk_14 >= 0xFB) && (temp_s6->unk_2E < temp_s4->unk_12.unk_2E))
        {
          var_s1 -= temp_t0 * 3;
        }
      }
      else
      {
        var_s1 += spB4 * 3;
      }
        break;

      case 0x53:
        if (arg4)
      {
        if (func_8437ACB0(arg3, i, arg2, 0) == 0)
        {
          var_s1 += temp_t0 * 3;
        }
        var_s1 += spB4 * 3;
        if (func_8437ACB0(arg3, i, arg2, 0xB2) != 0)
        {
          var_s1 -= temp_t0 * 3;
        }
      }
      else
      {
        var_s1 += spB4 * 3;
      }
        break;

      case 0x54:
        temp_s3 = &temp_s4->unk_12;
        if (arg4)
      {
        if (((temp_s3->unk_16[6] != 0x16) && (temp_s3->unk_16[7] != 0x16)) && (!(temp_s3->unk_4D & 0x90)))
        {
          var_s1 += spB7 * 3;
          var_s1 += spB6 * 3;
          if (temp_s3->unk_4E & 1)
          {
            var_s1 += spBA * 3;
          }
          if ((temp_s7->unk_14 >= 0x9A) && (func_843783CC(arg0) != 0))
          {
            var_s1 -= temp_t0 * 3;
          }
          if (func_843779C8(temp_fp, temp_s4, 0, &sp104) != 0)
          {
            var_s1 -= temp_t0 * 3;
          }
          if (func_8437ACB0(arg3, i, arg2, 0x99) != 0)
          {
            var_s1 -= temp_t0 * 3;
          }
          if (func_8437AC20(arg3, arg2, 0xFF) != 0)
          {
            var_s1 = 1;
          }
          if ((func_843776FC(temp_fp, temp_s4, 0x72) == 2) && (temp_s4->unk_02 != 0xA5))
          {
            var_s1 = 1;
          }
        }
        else
        {
          spF8 = 1;
        }
      }
      else
      {
        var_s1 += spB7 * 3;
        var_s1 += spB6 * 3;
      }
        break;

      case 0x56:
        if ((arg4 != 0) && (temp_s4->unk_12.unk_57 != 0))
      {
        spF8 = 1;
      }
        break;

    }

    var_s0_4 = ((temp_s7->unk_01 + sp58) > 0xFF) ? (0xFF) : (temp_s7->unk_01 + sp58);
    spC0 = ((temp_s7->unk_06 - sp58) < 0) ? (0) : (temp_s7->unk_06 - sp58);
    var_v1_6 = ((temp_s7->unk_08 - sp58) < 0) ? (0) : (temp_s7->unk_08 - sp58);
    if (((temp_s4->unk_03 != 0) && (sp9C->unk_03 < 2)) && (temp_s7->unk_0C < 0xFF))
    {
      var_s0_4 *= (func_843767E4(3) * 0x55) / 255.0f;
    }
    if (((temp_s7->unk_00 == 0x44) && (temp_fp->unk_03 != 0)) && (!(temp_s4->unk_12.unk_4C & 0x80)))
    {
      var_s0_4 = (func_843767E4(2) * var_s0_4) / 2;
    }
    temp_s7->unk_01 = var_s0_4;
    temp_s7->unk_06 = spC0;
    temp_s7->unk_08 = var_v1_6;
    if (((temp_s7->unk_03 >= 0x12) && (temp_s7->unk_03 < 0x1A)) || ((temp_s7->unk_03 >= 0x3A) && (temp_s7->unk_03 < 0x42)))
    {
      temp_s3 = &temp_s4->unk_12;
      if (temp_s3)
      {
      }
      if (temp_s3->unk_4D & 0x12)
      {
        var_s1 = 0;
      }
      if ((temp_s3->unk_2E < temp_s6->unk_2E) && (temp_s3->unk_0B == 0x84))
      {
        var_s1 = 1;
      }
    }
    if (sp9C->unk_02 != 0)
    {
      if (func_8437738C(sp9C->unk_03, &temp_s4->unk_12) == 0.0f)
      {
        var_s1 = 0;
      }
    }
    if ((var_s1 < 0) || (spF8 != 0))
    {
      var_s1 = 0;
    }
    temp_s7->unk_24 = var_s1;
    tmp1 = temp_s7->unk_0C * (temp_t0 * 0x11);
    tmp2 = temp_s7->unk_10 * (temp_t0 * 0x11);
    tmp3 = temp_s7->unk_04 * var_s1;
    tmp4 = temp_s7->unk_14 * (spB5 * 0x14);
    tmp5 = temp_s7->unk_18 * (spB5 * 0x14);
    tmp6 = temp_s7->unk_1C * (spB5 * 0x14);
    var_s2 = temp_s7->unk_20 * (spB5 * 0x14);
    temp_s7->unk_28 = ((((((tmp1 + tmp6) + tmp3) * (var_s0_4 / 255.0f)) + tmp2) - (tmp4 * (spC0 / 255.0f))) - tmp5) - (var_s2 * (var_v1_6 / 255.0f));
    if (arg4)
    {
      if (!(D_843C5564->unk_00 & 0x30))
      {
        temp_s7->unk_28 = func_843767E4(0xFE) + 1;
        if (D_80072B00[temp_s7->unk_00 - 1].unk_02 == 0)
        {
          if (spF8 != 0)
          {
            temp_s7->unk_28 = 0;
          }
        }
        else
        {
          if (((D_80072B00[temp_s7->unk_00 - 1].unk_01 != 0x28) && (D_80072B00[temp_s7->unk_00 - 1].unk_01 != 0x29)) && (func_8437738C(D_80072B00[temp_s7->unk_00 - 1].unk_03, &temp_s4->unk_12) == 0.0f))
          {
            temp_s7->unk_28 = 0;
          }
          if (spFC != 0)
          {
            temp_s7->unk_28 = -1;
          }
        }
      }
      else
        if ((((spFC != 0) || (temp_s6->unk_32[i] <= 0)) || ((spF8 != 0) && ((sp9C->unk_02 == 0) || (temp_s7->unk_0A == 0)))) || ((sp9C->unk_02 != 0) && (func_8437738C(sp9C->unk_03, &temp_s4->unk_12) == 0.0f)))
      {
        temp_s7->unk_28 = -0x06666666;
      }
    }
  }

}
