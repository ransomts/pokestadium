
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef signed char s8;
typedef short s16;
typedef long s32;
typedef float f32;
typedef unsigned int size_t;
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
typedef struct _PermuterTemp1 OSContStatus;
typedef struct _PermuterTemp2 OSContPad;
typedef struct 
{
  unsigned char flag;
  unsigned char v[3];
} Tri;
typedef struct 
{
  int cmd : 8;
  unsigned int par : 8;
  unsigned int len : 16;
  unsigned int addr;
} Gdma;
typedef struct 
{
  int cmd : 8;
  int pad : 24;
  Tri tri;
} Gtri;
typedef struct 
{
  int cmd : 8;
  int pad1 : 24;
  int pad2 : 24;
  unsigned char param : 8;
} Gpopmtx;
typedef struct 
{
  int cmd : 8;
  int pad0 : 8;
  int mw_index : 8;
  int number : 8;
  int pad1 : 8;
  int base : 24;
} Gsegment;
typedef struct 
{
  int cmd : 8;
  int pad0 : 8;
  int sft : 8;
  int len : 8;
  unsigned int data : 32;
} GsetothermodeL;
typedef struct 
{
  int cmd : 8;
  int pad0 : 8;
  int sft : 8;
  int len : 8;
  unsigned int data : 32;
} GsetothermodeH;
typedef struct 
{
  unsigned char cmd;
  unsigned char lodscale;
  unsigned char tile;
  unsigned char on;
  unsigned short s;
  unsigned short t;
} Gtexture;
typedef struct 
{
  int cmd : 8;
  int pad : 24;
  Tri line;
} Gline3D;
typedef struct 
{
  int cmd : 8;
  int pad1 : 24;
  short int pad2;
  short int scale;
} Gperspnorm;
typedef struct 
{
  int cmd : 8;
  unsigned int fmt : 3;
  unsigned int siz : 2;
  unsigned int pad : 7;
  unsigned int wd : 12;
  unsigned int dram;
} Gsetimg;
typedef struct 
{
  int cmd : 8;
  unsigned int muxs0 : 24;
  unsigned int muxs1 : 32;
} Gsetcombine;
typedef struct 
{
  int cmd : 8;
  unsigned char pad;
  unsigned char prim_min_level;
  unsigned char prim_level;
  unsigned long color;
} Gsetcolor;
typedef struct 
{
  int cmd : 8;
  int x0 : 10;
  int x0frac : 2;
  int y0 : 10;
  int y0frac : 2;
  unsigned int pad : 8;
  int x1 : 10;
  int x1frac : 2;
  int y1 : 10;
  int y1frac : 2;
} Gfillrect;
typedef struct 
{
  int cmd : 8;
  unsigned int fmt : 3;
  unsigned int siz : 2;
  unsigned int pad0 : 1;
  unsigned int line : 9;
  unsigned int tmem : 9;
  unsigned int pad1 : 5;
  unsigned int tile : 3;
  unsigned int palette : 4;
  unsigned int ct : 1;
  unsigned int mt : 1;
  unsigned int maskt : 4;
  unsigned int shiftt : 4;
  unsigned int cs : 1;
  unsigned int ms : 1;
  unsigned int masks : 4;
  unsigned int shifts : 4;
} Gsettile;
typedef struct 
{
  int cmd : 8;
  unsigned int sl : 12;
  unsigned int tl : 12;
  int pad : 5;
  unsigned int tile : 3;
  unsigned int sh : 12;
  unsigned int th : 12;
} Gloadtile;
typedef Gloadtile Gsettilesize;
typedef Gloadtile Gloadtlut;
typedef struct 
{
  unsigned int w0;
  unsigned int w1;
} Gwords;
typedef union 
{
  Gwords words;
  Gdma dma;
  Gtri tri;
  Gline3D line;
  Gpopmtx popmtx;
  Gsegment segment;
  GsetothermodeH setothermodeH;
  GsetothermodeL setothermodeL;
  Gtexture texture;
  Gperspnorm perspnorm;
  Gsetimg setimg;
  Gsetcombine setcombine;
  Gsetcolor setcolor;
  Gfillrect fillrect;
  Gsettile settile;
  Gloadtile loadtile;
  Gsettilesize settilesize;
  Gloadtlut loadtlut;
  long long int force_structure_alignment;
} Gfx;
typedef struct 
{
  u8 r;
  u8 g;
  u8 b;
  u8 a;
} Color_RGBA8;
extern Gfx *gDisplayListHead;
typedef s32 (*FragmentEntry)(s32, s32);
typedef struct MemoryBlock
{
  struct MemoryBlock *next;
  u32 size;
} MemoryBlock;
typedef struct MemoryPool
{
  OSMesg msgs[1];
  OSMesgQueue queue;
  size_t available;
  struct MemoryBlock *firstBlock;
  struct MemoryBlock freeList;
} MemoryPool;
typedef struct Controller
{
  s16 contId;
  s16 rawStickX;
  s16 rawStickY;
  u16 buttonDown;
  u16 buttonPressed;
  u16 unk_0A;
  char fillerC[2];
  s16 angle;
  f32 stickMag;
  f32 stickX;
  f32 stickY;
  OSContStatus *statusData;
  OSContPad *controllerData;
} Controller;
typedef struct unk_func_80026268_arg0_000
{
  u8 unk_00;
  u8 unk_01;
} unk_func_80026268_arg0_000;
typedef struct unk_func_80026268_arg0
{
  unk_func_80026268_arg0_000 unk_00;
  u16 unk_02;
  u8 unk_04;
  u8 unk_05;
  u8 unk_06;
  u8 unk_07;
  u8 unk_08;
  u8 unk_09[4];
  u8 pad0D;
  u16 unk_0E;
  u32 unk_10;
  u16 unk_14;
  u16 unk_16;
  u16 unk_18;
  u16 unk_1A;
  u16 unk_1C;
  u16 unk_1E;
  u8 unk_20[4];
  u8 unk_24;
  u8 unk_25;
  u16 unk_26;
  u16 unk_28;
  u16 unk_2A;
  u16 unk_2C;
  u16 unk_2E;
  u8 unk_30[11];
  u8 unk_3B[11];
  u8 unk_46[11];
  u8 pad51;
  u8 unk_52;
  u8 unk_53;
} unk_func_80026268_arg0;
typedef struct unk_func_88205880_00D0
{
  unk_func_80026268_arg0 unk_000[20];
  s32 unk_690;
  s32 unk_694;
  s32 unk_698;
  u32 unk_69C;
} unk_func_88205880_00D0;
typedef struct unk_func_88200FA0_030_038
{
  unk_func_88205880_00D0 **unk_00;
  s32 unk_04;
  s32 unk_08;
} unk_func_88200FA0_030_038;
typedef struct unk_func_8820BE14_06C_000
{
  s32 unk_00;
  unk_func_88200FA0_030_038 unk_04;
} unk_func_8820BE14_06C_000;
typedef struct unk_func_8820BE14_06C
{
  unk_func_8820BE14_06C_000 *unk_00;
  s32 unk_04;
  s32 unk_08;
  s32 unk_0C;
} unk_func_8820BE14_06C;
typedef struct unk_func_8830867C_02C_0CC_000_000_000
{
  char unk00[0x8];
  s32 unk_08;
} unk_func_8830867C_02C_0CC_000_000_000;
typedef struct unk_func_8830867C_02C_0CC_000_000_010_000_000
{
  struct unk_func_8830867C_02C_0CC_000_000 *unk_00;
  s32 unk_04;
  unk_func_80026268_arg0 unk_08;
} unk_func_8830867C_02C_0CC_000_000_010_000_000;
typedef struct unk_func_8830867C_02C_0CC_000_000_010_000
{
  unk_func_8830867C_02C_0CC_000_000_010_000_000 *unk_00;
} unk_func_8830867C_02C_0CC_000_000_010_000;
typedef struct unk_func_8830867C_02C_0CC_000_000_010
{
  unk_func_8830867C_02C_0CC_000_000_010_000 *unk_00;
  char unk04[0x4];
  s32 unk_08;
} unk_func_8830867C_02C_0CC_000_000_010;
typedef struct unk_func_8830867C_02C_0CC_000_000
{
  unk_func_8830867C_02C_0CC_000_000_000 *unk_00;
  s32 unk_04;
  s32 unk_08;
  s32 unk_0C;
  unk_func_8830867C_02C_0CC_000_000_010 unk_10;
} unk_func_8830867C_02C_0CC_000_000;
typedef struct unk_func_8830867C_02C_0CC_000_008
{
  u8 unk_00;
  char unk01[0x1];
  u16 unk_02;
  char unk04[0x5];
  u8 unk_09[4];
  char unk0D[0x3];
  u8 unk_10;
  u8 unk_11;
  char unk12[0x2];
  u16 unk_14;
  u16 unk_16;
  u16 unk_18;
  u16 unk_1A;
  u16 unk_1C;
  u16 unk_1E;
  u8 unk_20[4];
  u8 unk_24;
  u16 unk_26;
  u16 unk_28;
  u16 unk_2A;
  u16 unk_2C;
  u16 unk_2E;
} unk_func_8830867C_02C_0CC_000_008;
typedef struct unk_func_8830867C_02C_0CC_000
{
  unk_func_8830867C_02C_0CC_000_000 *unk_00;
  s32 unk_04;
  unk_func_8830867C_02C_0CC_000_008 unk_08;
  char unk_38[4];
  char unk3C[0x20];
} unk_func_8830867C_02C_0CC_000;
typedef struct unk_func_8830867C_02C_0CC
{
  unk_func_8830867C_02C_0CC_000 **unk_00;
  s32 unk_04;
  s32 unk_08;
} unk_func_8830867C_02C_0CC;
typedef struct unk_func_8830867C_04C_030_02C_000_000_00C
{
  s32 unk_00;
  char unk04[0x4];
  s32 unk_08;
} unk_func_8830867C_04C_030_02C_000_000_00C;
struct unk_func_88001300_000;
struct unk_func_88001300_000_000;
struct unk_func_8830867C_02C_048_000;
struct unk_func_88200FA0_030_030;
typedef s32 (*unk_func_88001300_018)(struct unk_func_88001300_000 *, s32, s32);
typedef s32 (*unk_func_88001300_01C)(struct unk_func_88001300_000 *);
typedef s32 (*unk_func_88001300_020)(struct unk_func_88001300_000 *, Controller *);
typedef void (*unk_func_88001300_024)(struct unk_func_88001300_000 *, s32);
typedef void (*unk_func_88001300_000_000_0C)(struct unk_func_88001300_000_000 *, MemoryPool *);
typedef struct unk_func_88001300_000_000
{
  s32 unk_00;
  struct unk_func_88001300_000_000 *unk_04;
  struct unk_func_88001300_000_000 *unk_08;
  unk_func_88001300_000_000_0C unk_0C;
} unk_func_88001300_000_000;
typedef struct unk_func_88001300_000_010
{
  s16 unk_00;
  s16 unk_02;
} unk_func_88001300_000_010;
typedef struct unk_func_88001300_000
{
  unk_func_88001300_000_000 unk_00;
  unk_func_88001300_000_010 unk_10;
  unk_func_88001300_000_010 unk_14;
  unk_func_88001300_018 unk_18;
  unk_func_88001300_01C unk_1C;
  unk_func_88001300_020 unk_20;
  unk_func_88001300_024 unk_24;
  u16 unk_28;
  u16 unk_2A;
} unk_func_88001300_000;
typedef struct unk_func_88001300_038 unk_func_88001300_038;
typedef struct unk_func_88001300_03C_01C unk_func_88001300_03C_01C;
typedef struct unk_func_8850B254 unk_func_8850B254;
typedef struct unk_func_8850878C unk_func_8850878C;
typedef struct unk_func_88503298 unk_func_88503298;
typedef void (*unk_func_88200FA0_030_030_040)(s32, s32, char *, s32, s32, struct unk_func_88200FA0_030_030 *);
typedef struct unk_func_88200FA0_030_030
{
  unk_func_88001300_000 unk_00;
  unk_func_8820BE14_06C *unk_2C;
  s32 unk_30;
  u16 *unk_34;
  s32 unk_38;
  s16 unk_3C;
  s16 unk_3E;
  unk_func_88200FA0_030_030_040 unk_40;
  unk_func_88001300_03C_01C *unk_44;
  s16 unk_48;
  s16 unk_4A;
  s16 unk_4C;
  s16 unk_4E;
  s16 unk_50;
  s16 unk_52;
} unk_func_88200FA0_030_030;
typedef struct unk_func_88200FA0_030_030_1CEA00
{
  unk_func_88001300_000 unk_00;
  unk_func_8830867C_02C_0CC *unk_2C;
  s32 unk_30;
  u16 *unk_34;
  s32 unk_38;
  s16 unk_3C;
  s16 unk_3E;
  unk_func_88200FA0_030_030_040 unk_40;
  unk_func_88001300_03C_01C *unk_44;
  s16 unk_48;
  s16 unk_4A;
  s16 unk_4C;
  s16 unk_4E;
  s16 unk_50;
  s16 unk_52;
} unk_func_88200FA0_030_030_1CEA00;
typedef struct unk_func_88500994
{
  unk_func_88001300_000 unk_00;
  s32 unk_2C;
  s32 unk_30;
} unk_func_88500994;
typedef struct unk_func_889000C4 unk_func_889000C4;
typedef struct unk_func_88509F48 unk_func_88509F48;
typedef struct unk_func_882173EC unk_func_882173EC;
typedef struct unk_func_8850CD44 unk_func_8850CD44;
typedef s32 (*unk_func_8830867C_02C_048_000_010)(struct unk_func_8830867C_02C_048_000 *, Controller *);
typedef void (*unk_func_8830867C_02C_048_000_014)(struct unk_func_8830867C_02C_048_000 *, s32);
typedef struct unk_func_8830867C_02C_048_000
{
  unk_func_88001300_000_000 unk_00;
  unk_func_8830867C_02C_048_000_010 unk_10;
  unk_func_8830867C_02C_048_000_014 unk_14;
  s32 unk_18;
  s32 unk_1C;
  s32 unk_20;
} unk_func_8830867C_02C_048_000;
struct unk_func_8830867C_02C;
typedef struct unk_func_8830867C_02C_034
{
  unk_func_88200FA0_030_030_1CEA00 unk_00;
  s16 unk_54;
  s32 unk_58;
  s32 unk_5C;
  char unk60[0xC];
  s32 unk_6C;
  struct unk_func_8830867C_02C *unk_70;
} unk_func_8830867C_02C_034;
typedef struct unk_func_8830867C_02C_048
{
  unk_func_8830867C_02C_048_000 unk_00;
  struct unk_func_8830867C_02C *unk_24;
} unk_func_8830867C_02C_048;
typedef struct unk_func_8830867C_04C_080
{
  unk_func_8830867C_02C_048_000 unk_00;
  struct unk_func_8830867C_04C *unk_24;
} unk_func_8830867C_04C_080;
void func_8002E8E4(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
typedef struct unk_func_8830867C_02C_04C unk_func_8830867C_02C_04C;
typedef struct unk_func_8830867C_02C_050
{
  unk_func_88001300_000 unk_00;
  struct unk_func_8830867C_02C *unk_2C;
} unk_func_8830867C_02C_050;
typedef struct unk_func_8830867C_02C_0B4 unk_func_8830867C_02C_0B4;
typedef struct unk_func_8830867C_02C_0C0 unk_func_8830867C_02C_0C0;
typedef struct unk_func_8830867C_02C_144_000
{
  s32 unk_00;
  s32 unk_04;
  char unk08[0x4];
  unk_func_8830867C_02C_0CC_000_000 *unk_0C;
  char unk10[0x4];
  s32 unk_14;
  char unk18[0x8];
} unk_func_8830867C_02C_144_000;
typedef struct unk_func_8830867C_02C_144
{
  unk_func_8830867C_02C_144_000 *unk_00;
  char unk04[0x4];
  s32 unk_08;
} unk_func_8830867C_02C_144;
typedef struct unk_func_8830867C_02C_154
{
  u8 unk_00;
  u8 unk_01;
  u8 unk_02;
  s32 unk_04;
  s32 unk_08;
  u8 *unk_0C;
  s32 unk_10;
  s32 unk_14;
  char unk18[0x4];
} unk_func_8830867C_02C_154;
typedef struct unk_func_8830867C_02C_1A8
{
  u8 *unk_00;
  unk_func_8830867C_02C_154 *unk_04;
  s32 unk_08;
  s32 unk_0C;
} unk_func_8830867C_02C_1A8;
typedef struct unk_func_8830867C_030 unk_func_8830867C_030;
typedef struct unk_func_8830867C_034 unk_func_8830867C_034;
typedef struct unk_func_8830867C_038 unk_func_8830867C_038;
typedef struct unk_func_8830867C_03C unk_func_8830867C_03C;
typedef struct unk_func_8830867C_040 unk_func_8830867C_040;
typedef struct unk_func_8830867C_044 unk_func_8830867C_044;
typedef struct unk_func_8830867C_048 unk_func_8830867C_048;
typedef struct unk_func_8830867C_04C_030_02C_000_000
{
  u8 unk_00;
  u8 unk_01;
  char unk02[0x6];
  s32 unk_08;
  unk_func_8830867C_04C_030_02C_000_000_00C unk_0C;
} unk_func_8830867C_04C_030_02C_000_000;
typedef struct unk_func_8830867C_04C_030_02C_000
{
  unk_func_8830867C_04C_030_02C_000_000 *unk_00[1];
} unk_func_8830867C_04C_030_02C_000;
typedef struct unk_func_8830867C_04C_030_02C
{
  unk_func_8830867C_04C_030_02C_000 *unk_00;
  char unk04[0x4];
  s32 unk_08;
} unk_func_8830867C_04C_030_02C;
typedef struct unk_func_8830867C_04C_030
{
  unk_func_88001300_000 unk_00;
  unk_func_8830867C_04C_030_02C *unk_2C;
  char unk30[0x4];
  u16 *unk_34;
  s32 unk_38;
  char unk3C[0x2];
  s16 unk_3E;
  char unk40[0x18];
  s32 unk_58;
  char unk5C[0x14];
} unk_func_8830867C_04C_030;
typedef struct unk_func_8830867C_04C_078 unk_func_8830867C_04C_078;
typedef struct unk_func_8830867C_04C_02C
{
  unk_func_88001300_000 unk_00;
  s32 unk_2C;
  s32 unk_30;
} unk_func_8830867C_04C_02C;
typedef struct unk_func_8830867C_04C
{
  unk_func_88001300_000 unk_00;
  unk_func_8830867C_04C_02C *unk_2C;
  unk_func_8830867C_04C_030 *unk_30;
  unk_func_88500994 *unk_34;
  char unk_38[4];
  char unk3C[0x3C];
  unk_func_8830867C_04C_078 *unk_78;
  unk_func_8830867C_030 *unk_7C;
  unk_func_8830867C_04C_080 *unk_80;
  s32 unk_84;
  unk_func_80026268_arg0 *unk_88;
  s32 unk_8C;
  unk_func_88503298 *unk_90;
} unk_func_8830867C_04C;
typedef struct unk_func_8830867C_02C_C54_014
{
  s32 unk_00;
  u8 unk_04[2];
} unk_func_8830867C_02C_C54_014;
typedef struct unk_func_8830867C_02C_C54_01C
{
  s32 unk_00;
  u8 unk_04[2];
} unk_func_8830867C_02C_C54_01C;
typedef struct unk_func_8830867C_02C_C54_024
{
  u8 unk_00[4];
  s32 unk_04;
} unk_func_8830867C_02C_C54_024;
typedef struct unk_func_8830867C_02C_C54
{
  s32 unk_00;
  s32 unk_04;
  u8 unk_08;
  u8 unk_09;
  s32 unk_0C;
  s32 unk_10;
  unk_func_8830867C_02C_C54_014 unk_14;
  unk_func_8830867C_02C_C54_01C unk_1C;
  unk_func_8830867C_02C_C54_024 unk_24;
  u8 unk_2C;
} unk_func_8830867C_02C_C54;
typedef struct unk_func_8830867C_054 unk_func_8830867C_054;
typedef struct unk_func_8830867C_02C_0E4
{
  s32 unk_00;
  s32 unk_04;
  s32 unk_08;
  unk_func_8820BE14_06C unk_0C;
  s32 unk_1C;
} unk_func_8830867C_02C_0E4;
typedef struct unk_func_8830867C_02C_0DC
{
  s32 *unk_00;
  s32 unk_04;
  s32 unk_08;
  char unk0C[0xC];
  s32 unk_18;
  char unk1C[0xC];
  s32 unk_28;
} unk_func_8830867C_02C_0DC;
typedef struct unk_func_8830867C_02C
{
  unk_func_88001300_000 unk_000;
  unk_func_88001300_038 *unk_02C;
  unk_func_8850B254 *unk_030;
  unk_func_8830867C_02C_034 *unk_034;
  unk_func_88500994 *unk_038;
  unk_func_88200FA0_030_038 unk_03C;
  unk_func_8830867C_02C_048 *unk_048;
  unk_func_8830867C_02C_04C *unk_04C;
  unk_func_8830867C_02C_050 *unk_050;
  unk_func_88001300_000 *unk_054;
  unk_func_88001300_000 *unk_058;
  unk_func_88001300_000 *unk_05C;
  unk_func_88001300_000 *unk_060;
  unk_func_88001300_000 *unk_064;
  unk_func_88001300_000 *unk_068;
  unk_func_88001300_000 *unk_06C;
  unk_func_88001300_000 *unk_070;
  unk_func_88001300_000 *unk_074;
  unk_func_88001300_000 *unk_078;
  unk_func_88001300_000 *unk_07C;
  unk_func_88001300_000 *unk_080;
  unk_func_88001300_000 *unk_084;
  unk_func_88001300_000 *unk_088;
  unk_func_8830867C_030 *unk_08C;
  unk_func_88509F48 *unk_090;
  unk_func_8830867C_034 *unk_094;
  unk_func_8830867C_038 *unk_098;
  unk_func_8830867C_03C *unk_09C;
  unk_func_8830867C_040 *unk_0A0;
  unk_func_8830867C_044 *unk_0A4;
  unk_func_8830867C_048 *unk_0A8;
  unk_func_8830867C_04C *unk_0AC;
  unk_func_889000C4 *unk_0B0;
  unk_func_8830867C_02C_0B4 *unk_0B4;
  unk_func_8850CD44 *unk_0B8;
  unk_func_882173EC *unk_0BC;
  unk_func_8830867C_02C_0C0 *unk_0C0;
  unk_func_882173EC *unk_0C4;
  unk_func_882173EC *unk_0C8;
  unk_func_88200FA0_030_038 unk_0CC;
  s32 unk_0D8;
  unk_func_8830867C_02C_0DC *unk_0DC;
  s32 unk_0E0;
  unk_func_8830867C_02C_0E4 unk_0E4[3];
  unk_func_8830867C_02C_144 unk_144;
  char unk150[0x4];
  unk_func_8830867C_02C_154 unk_154[3];
  unk_func_8830867C_02C_1A8 unk_1A8[3];
  char unk1D8[0xA70];
  unk_func_88200FA0_030_038 unk_C48;
  unk_func_8830867C_02C_C54 unk_C54;
  unk_func_8830867C_02C_C54 unk_C84;
  s32 unk_CB4;
  s32 unk_CB8;
  s32 unk_CBC;
  s32 unk_CC0;
  s32 unk_CC4;
  s32 unk_CC8;
  unk_func_8850878C *unk_CCC;
  s32 unk_CD0;
  s32 *unk_CD4;
  FragmentEntry unk_CD8;
  unk_func_8830867C_054 *unk_CDC;
} unk_func_8830867C_02C;
typedef struct unk_func_88304850_arg2
{
  s32 *unk_00;
  char unk04[4];
  u8 unk_08;
  char unk09[0xD];
  s16 unk_16;
  char unk18[0x14];
  u8 unk_2C;
  s16 unk_2E;
  s16 unk_30;
  s16 unk_32;
  s16 unk_34;
  s16 unk_36;
  char unk_38[4];
  char unk3C[0x4];
  char unk_40[3];
  char unk_43[1];
} unk_func_88304850_arg2;
extern char **D_8831A4D0;
extern Color_RGBA8 D_8831727C;
extern Color_RGBA8 D_88317280;
extern Color_RGBA8 D_88317284;
void func_88304350(s32 arg0, s32 arg1, s32 arg2, u8 *arg3, s32 arg4);
void func_88304490(s32 arg0, s32 arg1, s32 arg2, u8 *arg3, s32 arg4);
void func_883045C0(s32 arg0, s32 arg1, s32 arg2, unk_func_88304850_arg2 *arg3);
void func_88304608(s32 arg0, s32 arg1, s8 *arg2, s32 arg3);
void func_88304718(s32 arg0, s32 arg1, char *arg2, s32 arg3, u8 *arg4);
s32 func_883047CC(unk_func_8830867C_02C *arg0, unk_func_88304850_arg2 *arg1);
void func_88304850(s32 arg0, s32 arg1, unk_func_88304850_arg2 *arg2, s32 arg3, s32 arg4, unk_func_8830867C_02C_034 *arg5);
void Text_SetFont(s32 arg0, s32 arg1);
void Text_Print(s32 x, s32 y, const char *fmt, ...);
void Text_SetEnvColor(s32 r, s32 g, s32 b, s32 a);
void Text_ResetState(void);
void Text_SetupDL(void);
s32 MeasureTextWidth(s32 x, s32 y, const char *fmt, ...);
char *GetMessageString(char *arg0, s32 arg1, char **arg2, u32 file_number);
char **D_8831A4D0;
static Color_RGBA8 D_883171D0[] = {{0x31, 0x48, 0x6B, 0xFF}, {0x47, 0x5E, 0x80, 0xFF}, {0x2B, 0x40, 0x5F, 0xFF}, {0x31, 0x48, 0x6B, 0xFF}};
void func_88304350(s32 arg0, s32 arg1, s32 arg2, u8 *arg3, s32 arg4);
void func_88304490(s32 arg0, s32 arg1, s32 arg2, u8 *arg3, s32 arg4);
Color_RGBA8 D_8831727C = {0xF0, 0x96, 0x96, 0xFF};
Color_RGBA8 D_88317280 = {0xF0, 0xD2, 0x8C, 0xFF};
Color_RGBA8 D_88317284 = {0x96, 0xDC, 0xB4, 0xFF};
void func_883045C0(s32 arg0, s32 arg1, s32 arg2, unk_func_88304850_arg2 *arg3);
void func_88304608(s32 arg0, s32 arg1, s8 *arg2, s32 arg3);
void func_88304718(s32 arg0, s32 arg1, char *arg2, s32 arg3, u8 *arg4);
s32 func_883047CC(unk_func_8830867C_02C *arg0, unk_func_88304850_arg2 *arg1);
void func_88304850(s32 arg0, s32 arg1, unk_func_88304850_arg2 *a2, s32 arg3, s32 arg4, unk_func_8830867C_02C_034 *arg5)
{
  static Color_RGBA8 D_883172C0[] = {{0xF0, 0xF0, 0xF0, 0xFF}, {0xB2, 0xFF, 0xC3, 0xFF}, {0xFF, 0xB2, 0xC3, 0xFF}};
  static Color_RGBA8 D_883172CC[][2] = {{{0x50, 0x51, 0x54, 0xFF}, {0x59, 0x5B, 0x5E, 0xFF}}, {{0x43, 0x44, 0x46, 0xFF}, {0x4B, 0x4C, 0x4F, 0xFF}}};
  Color_RGBA8 spBC;
  s32 var_s1;
  s32 x;
  s32 var_s6;
  s32 temp_s7;
  s32 spA8;
  s32 color;
  s32 x0;
  s32 var_s4;
  unk_func_8830867C_02C *temp_s5;
  Color_RGBA8 *temp_v1;
  unk_func_88304850_arg2 *arg2 = a2;
  s32 pad[1];
  var_s6 = arg0;
  temp_s5 = arg5->unk_70;
  if (temp_s5->unk_0AC->unk_2C->unk_30 & 2)
  {
    var_s1 = temp_s5->unk_0AC->unk_00.unk_10.unk_00 - temp_s5->unk_000.unk_10.unk_00;
  }
  else
  {
    var_s1 = arg5->unk_00.unk_00.unk_14.unk_00;
  }
 do { { Gfx *_g = (Gfx *) (gDisplayListHead++); _g->words.w0 = (unsigned int) ((((unsigned int) 0xe7) & ((0x01 << 8) - 1)) << 24); _g->words.w1 = 0; } ; { Gfx *_g = (Gfx *) (gDisplayListHead++); _g->words.w0 = (((unsigned int) ((((unsigned int) 0xe3) & ((0x01 << 8) - 1)) << 24)) | ((unsigned int) ((((unsigned int) ((32 - 20) - 2)) & ((0x01 << 8) - 1)) << 8))) | ((unsigned int) ((((unsigned int) (2 - 1)) & ((0x01 << 8) - 1)) << 0)); _g->words.w1 = (unsigned int) (3 << 20); } ; { Gfx *_g = (Gfx *) (gDisplayListHead++); _g->words.w0 = (((unsigned int) ((((unsigned int) 0xe2) & ((0x01 << 8) - 1)) << 24)) | ((unsigned int) ((((unsigned int) ((32 - 3) - 29)) & ((0x01 << 8) - 1)) << 8))) | ((unsigned int) ((((unsigned int) (29 - 1)) & ((0x01 << 8) - 1)) << 0)); _g->words.w1 = (unsigned int) (((((0 << 30) | (0 << 26)) | (0 << 22)) | (0 << 18)) | ((((0 << 28) | (0 << 24)) | (0 << 20)) | (0 << 16))); } ; temp_v1 = ((Color_RGBA8 (*)[2]) D_883171D0)[arg3 & 1]; color = ((((temp_v1[0].r << 8) & 0xF800) | ((temp_v1[0].g << 3) & 0x7C0)) | ((temp_v1[0].b >> 2) & 0x3E)) | 1; { Gfx *_g = (Gfx *) (gDisplayListHead++); _g->words.w0 = (unsigned int) ((((unsigned int) 0xe7) & ((0x01 << 8) - 1)) << 24); _g->words.w1 = 0; } ; { Gfx *_g = (Gfx *) (gDisplayListHead++); _g->words.w0 = (unsigned int) ((((unsigned int) 0xf7) & ((0x01 << 8) - 1)) << 24); _g->words.w1 = (unsigned int) ((color << 0x10) | color); } ; { Gfx *_g = (Gfx *) (gDisplayListHead++); _g->words.w0 = (((unsigned int) ((((unsigned int) 0xf6) & ((0x01 << 8) - 1)) << 24)) | ((unsigned int) ((((unsigned int) (var_s6 + 0x25)) & ((0x01 << 10) - 1)) << 14))) | ((unsigned int) ((((unsigned int) (arg1 + 0x13)) & ((0x01 << 10) - 1)) << 2)); _g->words.w1 = ((unsigned int) ((((unsigned int) arg0) & ((0x01 << 10) - 1)) << 14)) | ((unsigned int) ((((unsigned int) arg1) & ((0x01 << 10) - 1)) << 2)); } ; if (temp_s7) { } temp_s7 = var_s1 + var_s6; color = ((((temp_v1[1].r << 8) & 0xF800) | ((temp_v1[1].g << 3) & 0x7C0)) | ((temp_v1[1].b >> 2) & 0x3E)) | 1; { Gfx *_g = (Gfx *) (gDisplayListHead++); _g->words.w0 = (unsigned int) ((((unsigned int) 0xe7) & ((0x01 << 8) - 1)) << 24); _g->words.w1 = 0; } ; { Gfx *_g = (Gfx *) (gDisplayListHead++); _g->words.w0 = (unsigned int) ((((unsigned int) 0xf7) & ((0x01 << 8) - 1)) << 24); _g->words.w1 = (unsigned int) ((color << 0x10) | color); } ; { Gfx *_g = (Gfx *) (gDisplayListHead++); _g->words.w0 = (((unsigned int) ((((unsigned int) 0xf6) & ((0x01 << 8) - 1)) << 24)) | ((unsigned int) ((((unsigned int) (arg0 + 0x81)) & ((0x01 << 10) - 1)) << 14))) | ((unsigned int) ((((unsigned int) (arg1 + 0x13)) & ((0x01 << 10) - 1)) << 2)); _g->words.w1 = ((unsigned int) ((((unsigned int) (arg0 + 0x26)) & ((0x01 << 10) - 1)) << 14)) | ((unsigned int) ((((unsigned int) arg1) & ((0x01 << 10) - 1)) << 2)); } ; PERM_RANDOMIZE(
var_s1 = 2; x0 = arg0 + 0x84; var_s6 = temp_s5->unk_CD4[temp_s5->unk_CD0]; temp_v1 = D_883172CC[arg3 & 1]; for (x = x0; x < temp_s7; var_s6++) { color = ((((temp_v1[var_s6 & 1].r << 8) & 0xF800) | ((temp_v1[var_s6 & 1].g << 3) & 0x7C0)) | ((temp_v1[var_s6 & 1].b >> var_s1) & 0x3E)) | 1; { Gfx *_g = (Gfx *) (gDisplayListHead++); _g->words.w0 = (unsigned int) ((((unsigned int) 0xe7) & ((0x01 << 8) - 1)) << 24); _g->words.w1 = 0; } ; { Gfx *_g = (Gfx *) (gDisplayListHead++); _g->words.w0 = (unsigned int) ((((unsigned int) 0xf7) & ((0x01 << 8) - 1)) << 24); _g->words.w1 = (unsigned int) ((color << 0x10) | color); } ; { Gfx *_g = (Gfx *) (gDisplayListHead++); _g->words.w0 = (((unsigned int) ((((unsigned int) 0xf6) & ((0x01 << 8) - 1)) << 24)) | ((unsigned int) ((((unsigned int) ((((s32 *) temp_s5->unk_0DC)[var_s6] + x) - 1)) & ((0x01 << 10) - 1)) << 14))) | ((unsigned int) ((((unsigned int) (arg1 + 0x13)) & ((0x01 << 10) - 1)) << 2)); _g->words.w1 = ((unsigned int) ((((unsigned int) x) & ((0x01 << 10) - 1)) << 14)) | ((unsigned int) ((((unsigned int) arg1) & ((0x01 << 10) - 1)) << 2)); } ; x += ((s32 *) temp_s5->unk_0DC)[var_s6]; } } while (0);
  if (arg2 != 0)
  {
    x = x0;
    func_8002E8E4(arg0 + 6, arg1 + 4, arg3 + 1, 3);
    spBC = D_883172C0[func_883047CC(temp_s5, arg2)];
    if (arg4 & 4)
    {
      spBC.a = 0x4D;
    }
    else
    {
      spBC.a = 0xFF;
    }
    Text_ResetState();
    Text_SetEnvColor(spBC.r, spBC.g, spBC.b, spBC.a);
    Text_SetFont(4, 0);
    spA8 = (0x5C - MeasureTextWidth(0, 0, "WWWWWWWWWW")) / var_s1;
    if ((arg2->unk_08 <= 0) || (arg2->unk_08 >= 0x98))
    {
      Text_Print((arg0 + spA8) + 0x26, var_s4 = arg1 + var_s1, "?????");
    }
    else
    {
      Text_Print((arg0 + spA8) + 0x26, var_s4 = arg1 + var_s1, GetMessageString(0, 0, D_8831A4D0, arg2->unk_08 - 1));
)
    }
    Text_SetupDL();
    var_s6 = temp_s5->unk_CD4[temp_s5->unk_CD0];
    for (; x < temp_s7; var_s6++)
    {
      switch (var_s6)
      {
        case 0:
          func_88304608(x + spA8, var_s4, arg2->unk_38, 0);
          break;

        case 1:
          func_8002E8E4(x + 4, arg1 + 4, (u16) arg2->unk_16, 5);
          break;

        case 2:
          color = (((s32 *) temp_s5->unk_0DC)[var_s6] - MeasureTextWidth(0, 0, "WWWWWWW")) / var_s1;
          func_88304608(x + color, var_s4, arg2->unk_43, 0);
          break;

        case 3:
          func_883045C0(x, arg1, ((s32 *) temp_s5->unk_0DC)[var_s6], arg2);
          break;

        case 4:

        case 5:
          func_88304350(x, var_s4, ((s32 *) temp_s5->unk_0DC)[var_s6], &arg2->unk_08, var_s6 - 4);
          break;

        case 6:

        case 7:

        case 8:

        case 9:
          func_88304490(x, var_s4, ((s32 *) temp_s5->unk_0DC)[var_s6], &arg2->unk_08, var_s6 - 6);
          break;

        case 10:
          color = ((s32 *) temp_s5->unk_0DC)[var_s6] - ((((s32 *) temp_s5->unk_0DC)[var_s6] - MeasureTextWidth(0, 0, "000")) / var_s1);
          func_88304718(x + color, var_s4, "%3d", arg2->unk_2C, &arg2->unk_08);
          break;

        case 11:
          color = ((s32 *) temp_s5->unk_0DC)[var_s6] - ((((s32 *) temp_s5->unk_0DC)[var_s6] - MeasureTextWidth(0, 0, "000")) / var_s1);
          func_88304718(x + color, var_s4, "%3d", (u16) arg2->unk_2E, &arg2->unk_08);
          break;

        case 12:
          color = ((s32 *) temp_s5->unk_0DC)[var_s6] - ((((s32 *) temp_s5->unk_0DC)[var_s6] - MeasureTextWidth(0, 0, "000")) / var_s1);
          func_88304718(x + color, var_s4, "%3d", (u16) arg2->unk_30, &arg2->unk_08);
          break;

        case 13:
          color = ((s32 *) temp_s5->unk_0DC)[var_s6] - ((((s32 *) temp_s5->unk_0DC)[var_s6] - MeasureTextWidth(0, 0, "000")) / var_s1);
          func_88304718(x + color, var_s4, "%3d", (u16) arg2->unk_32, &arg2->unk_08);
          break;

        case 14:
          color = ((s32 *) temp_s5->unk_0DC)[var_s6] - ((((s32 *) temp_s5->unk_0DC)[var_s6] - MeasureTextWidth(0, 0, "000")) / var_s1);
          func_88304718(x + color, var_s4, "%3d", (u16) arg2->unk_34, &arg2->unk_08);
          break;

        case 15:
          color = ((s32 *) temp_s5->unk_0DC)[var_s6] - ((((s32 *) temp_s5->unk_0DC)[var_s6] - MeasureTextWidth(0, 0, "000")) / var_s1);
          func_88304718(x + color, var_s4, "%3d", (u16) arg2->unk_36, &arg2->unk_08);
          break;

      }

      x += ((s32 *) temp_s5->unk_0DC)[var_s6];
    }

  }
}
