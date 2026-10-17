#pragma _permuter latedefine start
#pragma _permuter latedefine end
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef signed char s8;
typedef short s16;
typedef long s32;
typedef float f32;
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
typedef struct unk_D_86002F58_004_000_010 unk_D_86002F58_004_000_010;
typedef struct unk_D_86002F58_004_000_00C unk_D_86002F58_004_000_00C;
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
typedef struct unk_D_86002F58_004_000_040_004 unk_D_86002F58_004_000_040_004;
typedef struct unk_D_86002F58_004_000_040
{
  s16 unk_00;
  unk_D_86002F58_004_000_040_004 *unk_04;
  s32 unk_08;
  u32 unk_0C;
  char unk10[0x2];
  u16 unk_12;
} unk_D_86002F58_004_000_040;
typedef struct unk_D_86002F58_004_000_054_004 unk_D_86002F58_004_000_054_004;
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
extern struct unk_D_86002F58_004_000_000 D_800AC840;
extern struct unk_D_86002F58_004_000_000 D_800AC858;
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
typedef struct unk_D_8140E728_01C unk_D_8140E728_01C;
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
typedef struct unk_D_8438E7B0_A50
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
  u8 unk_09;
  u8 unk_0A;
  u8 unk_0B;
  u8 unk_0C;
  u8 unk_0D;
  u8 unk_0E;
  u8 unk_0F;
} unk_D_8438E7B0_A50;
typedef struct unk_D_8438E7B0
{
  unk_D_8438E7B0_A50 unk_000[165];
  unk_D_8438E7B0_A50 unk_A50;
  char unkA60[0x10];
  unk_D_8438E7B0_A50 unk_A70;
  unk_D_8438E7B0_A50 unk_A80;
  char unkA90[0x60];
  unk_D_8438E7B0_A50 unk_AF0;
  unk_D_8438E7B0_A50 unk_B00;
  unk_D_8438E7B0_A50 unk_B10;
  unk_D_8438E7B0_A50 unk_B20;
  char unkB30[0x51];
  u8 unk_B81;
  char unkB82[0x5E];
} unk_D_8438E7B0;
typedef struct unk_D_84384588
{
  u8 unk_00;
  u8 unk_01;
  char unk02[0xE];
} unk_D_84384588;
typedef struct unk_D_8438FF70
{
  Vec3f unk_00;
  s16 unk_0C;
  s16 unk_0E;
  s16 unk_10;
  u16 unk_12;
  char unk14[0xC];
} unk_D_8438FF70;
extern unk_D_8438E7B0 *D_84384570[];
extern u8 D_84384590[];
extern u8 D_843845F0;
extern u8 D_843845F4;
extern u8 D_843845F8;
extern u8 D_843845FC[];
extern u8 D_843C4DA4;
extern s32 D_843C4DEC;
extern u8 D_843C4E44;
extern unk_D_84390010 *D_84390010[2];
void func_8430506C(unk_D_84390010 *arg0);
void func_843058C4(unk_D_84390010 *arg0, s32 arg1);
s32 func_84307AE0(u8 arg0, u8 *arg1, s32 arg2);
s32 func_84307F00(unk_D_84390010 *arg0);
void func_84308654(unk_D_84390010 *arg0, s32 arg1, s32 arg2);
void func_80017464(unk_D_86002F58_004_000 *arg0, s16 arg1);
s32 func_8001BD04(unk_D_86002F58_004_000 *arg0, s32 arg1);
static unk_D_8438E7B0 D_8438E7B0;
static unk_D_8438E7B0 D_8438F390;
static unk_D_8438FF70 D_8438FF70;
static unk_D_8438FF70 D_8438FF90;
static unk_D_8438FF70 D_8438FFB0;
static unk_D_8438FF70 D_8438FFD0;
static unk_D_84384588 D_8438FFF0;
static unk_D_84384588 D_84390000;
unk_D_84390010 *D_84390010[2];
static unk_D_8438E7B0_A50 *D_84390020;
unk_D_8438E7B0 *D_84384570[] = {&D_8438E7B0, &D_8438F390};
unk_D_8438FF70 *D_84384578[] = {&D_8438FF70, &D_8438FF90};
unk_D_8438FF70 *D_84384580[] = {&D_8438FFB0, &D_8438FFD0};
unk_D_84384588 *D_84384588[] = {&D_8438FFF0, &D_84390000};
u8 D_84384590[] = {0x39, 0x67, 0x64, 0x6D, 0x28, 0x6E, 0x2A, 0x47};
static u8 D_84384598[] = {0x64, 0x6E};
static u8 D_8438459C[] = {0x06, 0x0C, 0x30, 0x31, 0x32, 0x33, 0x8D, 0x96, 0x97};
static u8 D_843845A8[] = {0x06, 0x2E};
static u8 D_843845AC[] = {0x06, 0x42};
static u8 D_843845B0[] = {0x06, 0x42};
static u8 D_843845B4[] = {0x06, 0x42};
static u8 D_843845B8[] = {0x06, 0x06};
static u8 D_843845BC[] = {0x06, 0x06};
static u8 D_843845C0[] = {0x06, 0x16};
static u8 D_843845C4[] = {0x01, 0x7F};
static u8 D_843845C8[] = {0x06, 0x7F};
static u8 *D_843845CC[] = {D_843845A8, D_843845AC, D_843845B0, D_843845B4, D_843845B8, D_843845BC, D_843845C0, D_843845C4, D_843845C8};
u8 D_843845F0 = 0x8E;
u8 D_843845F4 = 0x16;
u8 D_843845F8 = 0x53;
u8 D_843845FC[] = {0x55, 0x54};
void func_8430506C(unk_D_84390010 *arg0)
{
  unk_D_8438E7B0 *ptr;
  s32 sp48;
  unk_D_8438E7B0 *ptr2;
  s32 sp40;
  unk_D_84390010_654 *sp3C;
  s32 pad[2];
  unk_D_84390010 *sp30;
  unk_D_800FCB18 *sp28;
  sp48 = 0xA5;
  sp40 = func_84307F00(arg0) == 0;
  sp3C = &D_84390010[sp40]->unk_654;
  sp30 = D_84390010[sp40];
  sp28 = &arg0->unk_654.unk_38;
  D_84390020 = &D_84384570[sp40]->unk_A80;
  if (sp3C->unk_34 & 1)
  {
    if (func_84307AE0(sp30->unk_000.unk_01A, D_84384598, 2) != 0)
    {
      D_84390020 = &D_84384570[sp40]->unk_B20;
    }
  }
  if ((sp3C->unk_34 & 1) && func_84307AE0(sp30->unk_000.unk_01A, D_84384590, 8))
  {
    sp48 = 0xAF;
  }
  D_84390010[sp40]->unk_4C4 = 0;
  if ((!(sp3C->unk_34 & 0x4000)) && (!(sp3C->unk_34 & 2)))
  {
    if ((sp28->unk_5A == 0x91) && (D_843C4DEC < 0xA))
    {
      D_84390020 = &D_84384570[sp40]->unk_000[sp48];
    }
    if ((D_843C4E44 == 0) || (D_843C4DA4 != 0))
    {
      D_84390020 = &D_84384570[sp40]->unk_000[sp48];
      if (sp3C->unk_34 & 0x200)
      {
        D_84390020 = &D_84384570[sp40]->unk_000[0xB0];
      }
    }
    else
      if (!(sp3C->unk_34 & 1))
    {
      func_843058C4(D_84390010[sp40], 0xA8);
    }
    func_80017464(&D_84390010[sp40]->unk_000, 0);
    func_8001BD04(&D_84390010[sp40]->unk_000, D_84390020->unk_00);
    if (((sp28->unk_44.unk_00 == 0x17) || (sp28->unk_44.unk_00 == 0x22)) || (sp28->unk_44.unk_00 == 0x45))
    {
      func_84308654(D_84390010[sp40], 0xF, 0);
    }
  }
}

void func_843058C4(unk_D_84390010 *arg0, s32 arg1);
