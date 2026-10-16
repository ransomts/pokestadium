

#define NULL 0


typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef signed char s8;
typedef short s16;
typedef long s32;
typedef float f32;
extern u8 D_8120EB24[];
extern u8 D_8120EB28[];
extern u8 D_8120EB38[];
extern f32 D_8120EAC0;
extern s32 D_8120EAC8;
extern s32 D_8120EACC;
extern s32 D_8120EAC4;
extern s32 D_8120EA60;
extern u32 D_8120EA80;
extern s32 D_8120EAD0;
extern u16 D_8120EAD4[32];
extern u8 D_8120EB14[];
extern u32 D_8120EB48[9];
extern s32 D_8120EB78;
typedef struct GbAudioStream
{
  s32 id;
  s32 pos;
} GbAudioStream;
extern GbAudioStream D_8120EB7C;
extern GbAudioStream D_8120EB84;
extern GbAudioStream D_8120EB8C;
extern s32 D_81228678[];
extern s8 *D_81228654[];
extern u8 D_8120EA70[];
s32 D_8120EA60 = 0;
static u32 pad_D_8120EA60_0[3] = {0, 0, 0};
u8 D_8120EA70[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
u32 D_8120EA80 = 0;
static u32 D_8120EA80_tail_0[15] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
f32 D_8120EAC0 = 1500.0f;
s32 D_8120EAC4 = 17784;
s32 D_8120EAC8 = 2048;
s32 D_8120EACC = 16384;
s32 D_8120EAD0 = 0;
u16 D_8120EAD4[32] = {0x1120, 0x201, 0x1100, 0xF50, 0x800, 0x723, 0x800, 0x922, 0x800, 0x980, 0x1010, 0xBA6, 0x800, 0xBA6, 0x800, 0xBA5, 0x800, 0x800, 0x800, 0x800, 0x800, 0x800, 0x800, 0x800, 0x800, 0x800, 0x800, 0x800, 0x800, 0x800, 0x800, 0x800};
u8 D_8120EB14[16] = {0, 1, 3, 6, 0xA, 0xE, 0x12, 0x15, 0x18, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F, 0x20};
u8 D_8120EB24[4] = {0, 0x20, 0x10, 8};
u8 D_8120EB28[16] = {0, 6, 0xA, 0xE, 0x11, 0x16, 0x1A, 0x1D, 0x20, 0x22, 0x24, 0x26, 0x28, 0x2B, 0x2E, 0x32};
u8 D_8120EB38[16] = {0, 6, 0xA, 0xE, 0x11, 0x16, 0x1A, 0x1D, 0x20, 0x22, 0x24, 0x26, 0x29, 0x2C, 0x2F, 0x34};
u32 D_8120EB48[9] = {0x20000, 0x10000, 0x8000, 0x5555, 0x4000, 0x3333, 0x2AAA, 0x2492, 0x12345678};
void func_81209374(s32 arg0, s16 *arg1);
static s32 pad_D_8120EB6C[2] = {0, 0};
s32 D_8120EB78 = 0;
GbAudioStream D_8120EB7C = {0, 0};
GbAudioStream D_8120EB84 = {0, 0};
GbAudioStream D_8120EB8C = {0, 0};
extern u32 D_8120EB94[6864];
extern u32 D_812156D4[5820];
extern u32 D_8121B1C4[2612];
extern u32 D_8121DA94[1720];
extern u32 D_8121F574[4196];
extern u32 D_81223704[3224];
extern u32 D_81226964[1850];
u32 D_8122864C[2] = {0, 0};
s8 *D_81228654[9] = {(void *) D_8122864C, (void *) D_8122864C, (void *) D_8120EB94, (void *) D_812156D4, (void *) D_8121B1C4, (void *) D_8121DA94, (void *) D_8121F574, (void *) D_81223704, (void *) D_81226964};
s32 D_81228678[9] = {8, 8, 27456, 23280, 10448, 6880, 16784, 12896, 7392};
void func_81209374(s32 numSamples, s16 *out)
{
  static u32 D_8122869C = 0;
  s32 i;
  s8 *mainData;
  s8 *altData;
  s32 a;
  s32 b;
  s32 mainEnd;
  s32 altEnd;
  mainData = NULL;
  altData = NULL;
  if (D_8120EB7C.id != 0)
  {
    D_8120EB8C = D_8120EB84;
    D_8120EB84 = D_8120EB7C;
    D_8120EB84.pos = 0;
    D_8120EB7C.id = 0;
    D_8122869C = 0x400;
  }
  if (D_8120EB84.id != 0)
  {
    mainData = D_81228654[D_8120EB84.id];
    mainEnd = D_81228678[D_8120EB84.id];
  }
  if (D_8120EB8C.id != 0)
  {
    altData = D_81228654[D_8120EB8C.id];
    altEnd = D_81228678[D_8120EB8C.id];
  }
PERM_RANDOMIZE(
  for (i = 0; i < numSamples; i++)
  {
    if (mainData != NULL)
    {
 ;
      if (mainEnd == D_8120EB84.pos)
      {
        D_8120EB84.id = 0;
        mainData = NULL;
        a = 0;
      }
      else
      {
        a = mainData[D_8120EB84.pos++];
      }
    }
    else
    {
      a = 0;
    }
    if (altData != NULL)
    {
      if (altEnd == D_8120EB8C.pos)
      {
        D_8120EB8C.id = 0;
        altData = NULL;
        b = 0;
      }
      else
      {
        b = altData[D_8120EB8C.pos++];
        b = ((s32) (b * D_8122869C)) / 1024;
      }
    }
    else
    {
      b = 0;
    }
    out[(i * 2) + 0] = (a + b) << 6;
    out[(i * 2) + 1] = (unsigned long long) ((a - b) << 6);
  }
)

}
