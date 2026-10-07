

#define NULL 0


typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef signed char s8;
typedef short s16;
typedef long s32;
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
extern void osWritebackDCache(void *, s32);
extern void bzero(void *, int);
typedef struct unk_D_800FCED8_0000
{
  char unk000[0x166];
  s16 unk_166;
  char unk168[0x22];
  s16 unk_18A;
  s16 unk_18C;
  s16 unk18E;
} unk_D_800FCED8_0000;
typedef struct unk_D_800FCED8_0198
{
  char unk_0000[0x1400];
} unk_D_800FCED8_0198;
typedef struct unk_D_800FCED8_01598
{
  char unk00[0x4];
  u32 unk_04;
} unk_D_800FCED8_01598;
typedef void (*unk_D_800FCED8_190)(s32, unk_D_800FCED8_01598 *, s32, OSMesgQueue *);
typedef struct unk_D_800FCED8
{
  unk_D_800FCED8_0000 unk_0000;
  unk_D_800FCED8_190 unk_0190;
  s32 unk_0194;
  unk_D_800FCED8_0198 unk_0198;
  unk_D_800FCED8_01598 unk_1598[1];
  u32 unk_15A0;
  char unk_15A4[0xFF4];
  u16 unk_2598;
  u16 unk_259A;
  u32 unk_259C;
  OSMesgQueue unk_25A0;
  OSMesg unk_25B8;
  u32 unk_25BC;
  u32 unk_25C0;
  u32 unk_25C4;
  s32 unk_25C8;
  u32 unk_25CC;
  s8 unk_25D0;
  s8 unk_25D1;
  s8 unk_25D2;
  char unk25D3[0x5];
} unk_D_800FCED8;
typedef struct unk_D_800FCF28
{
  s16 unk_000[0x8A0];
} unk_D_800FCF28;
extern unk_D_800FCF28 *D_800FCF28[2];
extern u32 D_800FCF30[2];
void func_80044EA4(void);
void func_800455DC(u32 arg0, u32 arg1, u32 arg2, OSMesgQueue *arg3);
void func_800456D0(unk_D_800FCED8 *, s32, s32);
void func_80045780(unk_D_800FCED8 *);
u32 func_800459E0(unk_D_800FCED8 *, u32);
void func_80045A48(unk_D_800FCED8 *);
void func_80045A68(unk_D_800FCED8 *);
u8 D_800785F0 = 0;
s32 D_800FCED0;
unk_D_800FCED8 *D_800FCED8[2];
s16 *D_800FCEE0[2];
u32 D_800FCEE8;
u32 D_800FCEEC;
u8 D_800FCEF0[2];
s32 D_800FCEF8[2];
u32 D_800FCF00[2];
s32 D_800FCF08[2];
s32 D_800FCF10[2];
s16 D_800FCF1C[2];
u8 D_800FCF20[2];
unk_D_800FCF28 *D_800FCF28[2];
u32 D_800FCF30[2];
u32 D_800FCF38[2];
void func_80044EA4(void)
{
  u32 j;
  u32 var_s7;
  u32 temp_a2;
  s32 i;
  unsigned char new_var;
  s16 temp;
  s32 temp_v0_9;
  s32 pad;
  s32 pad2;
  u8 *p;
  p = D_800FCEF0;
  for (i = 0; i < 2; i++, p++)
  {
    if ((*p) != 2)
    {
      if (D_800FCF30[i] < D_800FCF38[i])
      {
        if ((D_800FCF38[i] - D_800FCF30[i]) < D_800FCEEC)
        {
          var_s7 = D_800FCEEC;
        }
        else
        {
          var_s7 = D_800FCEE8;
        }
      }
      else
        if ((0x8A0 - D_800FCEEC) < (D_800FCF30[i] - D_800FCF38[i]))
      {
        var_s7 = D_800FCEEC;
      }
      else
      {
        var_s7 = D_800FCEE8;
      }
      func_80045780(D_800FCED8[i]);
      if (((u8) D_800FCED8[i]->unk_25D1) == 2)
      {
        osWritebackDCache(D_800FCF28[i], 0x1140);
        func_80045A48(D_800FCED8[i]);
        D_800FCED0 = 1;
        D_800FCF20[i] = 0;
      }
      else
        if ((((*p) != 0) && ((*p) != 3)) && (((u8) D_800FCED8[i]->unk_25D1) == 4))
      {
        if (D_800FCF20[i] == 0)
        {
          func_80045A68(D_800FCED8[i]);
          D_800FCF20[i] = 1;
        }
        D_800FCED0 = 0;
        *p = 2;
        bzero(D_800FCEE0[i], 0x1400);
        bzero(D_800FCF28[i], 0x1140);
      }
      func_800459E0(D_800FCED8[i], var_s7);
      temp_a2 = D_800FCED8[i]->unk_25C8 - var_s7;
      for (j = 0; j < var_s7; j++)
      {
        temp = (D_800FCF00[i] * D_800FCEE0[i][(temp_a2 + j) % 2560]) >> 7;
        new_var = j;
        D_800FCF28[i]->unk_000[((D_800FCF38[i] + (new_var * 2)) + 1) % 2208] = temp;
        D_800FCF28[i]->unk_000[(D_800FCF38[i] + (new_var * 2)) % 2208] = temp;
      }

      D_800FCF38[i] += var_s7 * 2;
      D_800FCF38[i] %= 2208;
      osWritebackDCache(D_800FCF28[i], 0x1140);
      switch (*p)
      {
        case 2:

        case 4:
          break;

        case 0:
          func_800456D0(D_800FCED8[i], D_800FCEF8[i], func_800455DC);
          *p = 4;
          if (D_800FCED0 != 0)
        {
          D_800FCED0 = 0;
        }
          D_800FCF00[i] = D_800FCF08[i];
          break;

        case 1:
          func_80045A68(D_800FCED8[i]);
          bzero(D_800FCEE0[i], 0x1400);
          D_800FCF20[i] = 1;
          break;

        case 3:
          D_800FCF10[i]--;
          if (D_800FCF10[i] == 0)
        {
          *p = 0;
        }
          break;

        case 5:
          temp_v0_9 = D_800FCF00[i] - D_800FCF1C[i];
          if (temp_v0_9 <= 0)
        {
          D_800FCF00[i] = 0;
          *p = 1;
        }
        else
        {
          D_800FCF00[i] = temp_v0_9;
        }
          break;

      }

    }
  }

}

void func_800455DC(u32 arg0, u32 arg1, u32 arg2, OSMesgQueue *arg3);
void func_800456D0(unk_D_800FCED8 *arg0, s32 arg1, s32 arg2);
void func_80045780(unk_D_800FCED8 *arg0);
u32 func_800459E0(unk_D_800FCED8 *arg0, u32 arg1);
void func_80045A48(unk_D_800FCED8 *arg0);
void func_80045A68(unk_D_800FCED8 *arg0);
