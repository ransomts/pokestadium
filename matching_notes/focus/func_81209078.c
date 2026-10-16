

#define NULL 0


typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef signed char s8;
typedef short s16;
typedef long s32;
typedef float f32;
extern u32 osAiGetLength(void);
extern void osWritebackDCache(void *, s32);
extern u32 osGetCount(void);
u32 osGetCount(void);
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
extern s16 D_8122C790;
extern s16 D_8122C792;
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
extern s16 *D_812346E0[3];
extern volatile s32 D_812346C8;
extern s32 D_812346D0;
extern s32 D_812346D4;
extern u32 D_812346F4;
extern volatile u32 D_812346FC;
extern s16 D_81234690[];
extern s16 D_812346EC[];
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
void func_81208828(s32 numSamples, s16 *out);
s32 func_81209078(void)
{
  u32 aiLen;
  s32 pad1;
  s32 idx;
  s32 pad2[2];
  s16 *buf;
  s32 pad3;
  s16 *len;
  s16 **bufPtr;
  s16 *p;
  D_812346C8++;
  D_812346D0 ^= 1;
  D_812346D4++;
  D_812346D4 %= 3;
  idx = (D_812346D4 + 2) % 3;
  aiLen = osAiGetLength() >> 2;
  if (D_812346FC < 16)
  {
    len = &D_812346EC[idx];
    if ((*len) != 0)
    {
      bufPtr = &D_812346E0[idx];
PERM_RANDOMIZE(
      if (osGbSetNextBuffer(*bufPtr, (*len) * 4) == (-1))
      {
        if (bufPtr)
        {
        }
      }
      else
      {
        p = *bufPtr;
        p += (*len) * 2;
        D_8122C790 = p[-2];
        D_8122C792 = p[-1];
      }
      if (!p)
      {
      }
)
    }
  }
  if (D_812346FC > 16)
  {
    return 0;
  }
  if (D_812346FC != 0)
  {
    D_812346FC++;
  }
  idx = D_812346D4;
  bufPtr = &D_812346E0[idx];
  len = &D_812346EC[idx];
  buf = *bufPtr;
  *len = (((D_81234690[3] - aiLen) + 0x80) & 0xFFF0) + 0x10;
  if ((*len) < D_81234690[5])
  {
    len = &D_812346EC[idx];
    *len = D_81234690[5];
  }
  if (D_81234690[4] < (*len))
  {
    *len = D_81234690[4];
  }
  if (D_8120EB78 == 0)
  {
    func_81208828(*len, buf);
  }
  else
  {
    func_81209374(*len, buf);
  }
  osWritebackDCache(buf, (*len) * 4);
PERM_RANDOMIZE(
  D_812346F4 = osGetCount() * (D_812346F4 + D_812346C8);
  D_812346F4 = (*bufPtr)[D_812346C8 & 0xFF] + D_812346F4;
)
  return 0;
}

void func_81209374(s32 numSamples, s16 *out);
