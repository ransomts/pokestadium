#include "global.h"
#include "src/fragments/gb_tower_emulator/gb_tower_emulator.h"
#include "src/game_state.h"
#include "src/3FB0.h"
#include "src/scheduler.h"
#include "src/gfx_rect.h"
#include "src/controller.h"
#include "src/memory.h"
#include "include/variables.h"

typedef struct unk_D_8122C4FA {
  /* 0x00 */ u8 posX;
  /* 0x01 */ u8 TrainerSlotSaveData_GamePort;
} unk_D_8122C4FA; // size >= 0x2

typedef struct TileAssetFragment {
  /* 0x000000 */ char unk000000[0x1FEAE8];
} TileAssetFragment; // size = 0x1FEAE8

typedef struct GbPakThreadContext {
  /* 0x00 */ OSMesg mesg[1];
  /* 0x04 */ OSMesgQueue queue;
  /* 0x1C */ char unk1C[0x4];
  /* 0x20 */ s32 unk_20;
  /* 0x24 */ s32 unk_24;
  /* 0x28 */ s32 unk_28;
  /* 0x2C */ s32 unk_2C;
  /* 0x30 */ char unk30[0x8];
  /* 0x38 */ s32 unk_38;
  /* 0x3C */ s32 unk_3C;
  /* 0x40 */ s32 unk_40;
  /* 0x44 */ s32 unk_44;
  /* 0x48 */ s32 unk_48;
  /* 0x4C */ s32 unk_4C;
  /* 0x50 */ s32 unk_50;
  /* 0x54 */ s32 unk_54;
  /* 0x58 */ s32 unk_58;
  /* 0x5C */ u32 unk_5C;
  /* 0x60 */ char unk60[0x8];
} GbPakThreadContext; // size = 0x68

typedef struct GbPakHeader {
  /* 0x00 */ u8 unk00[0x34];
  /* 0x34 */ u8 data[0x10];  
  /* 0x44 */ u16 unk_44;
  /* 0x46 */ u8 unk_46;
  /* 0x47 */ u8 unk47;
  /* 0x48 */ u8 unk_48;
  /* 0x49 */ u8 unk_49;
  /* 0x4A */ u8 unk_4A;
} GbPakHeader; // size = 0x4B

typedef struct GbPakAssetData {
  /* 0x0000 */ u8 unk0000[0x9790];
  /* 0x9790 */ s32 unk_9790;
  /* 0x9794 */ u8 unk9794[0xFC];
  /* 0x9890 */ s32 unk_9890;
  /* 0x9894 */ u8 unk9894[0xFC];
  /* 0x9990 */ s32 unk_9990;
  /* 0x9994 */ u8 unk9994[0xFC];
  /* 0x9A90 */ u16 unk_9A90[0x42];
  /* 0x9B14 */ u8 unk9B14[0x82];
  /* 0x9B96 */ u16 unk_9B96[0x42];
} GbPakAssetData; // size = 0x9C1A

typedef struct unk_D_8120D7F3 {
    u8 pad[0x116];
    u8 unk116;
} unk_D_8120D7F3; // size = 0x10A ??

// ??
extern unk_D_8120D7F3 gStadiumUILayout;

// .data
extern s16 gGbEmuTextPaletteGray[];
extern s16 gGbEmuTextPaletteYellow[];
extern s16 gGbEmuTextPaletteBlackWhite[];
extern s16 gGbEmuTextPaletteBlackGray[];
extern s16 gGbEmuTextPaletteRed[];
extern s16 gGbEmuTextPaletteGreen[];
extern s16 gGbEmuTextPaletteBlue[];
extern s16 gGbEmuTextPaletteGrayAlt[];
extern s16 gGbEmuTextPaletteYellowPale[];
extern s16 gGbEmuTextPaletteCyan[];
extern s16 gGbEmuTextPaletteGrayDark[];
extern s16 gGbEmuTextPalettePink[];
extern u8 TileMap_8x8[0x100];
extern u8 TileMap_12x12[256];
extern u16 gGbPakBorderColors[4];

// .rodata
const u8 gStadiumScreenText[] = {
    0x74, 0x73, 0x72, 0xAA, 0xB0, 0xAA, 0xA4, 0xA0, 0xAD, 0x89, 0x73, 0x72, 0x71, 0xA9, 0xAF, 0xA9, 0xB5, 0x9F, 0x90, 0x00,
};

// .bss
extern FramebufferImage* gGbScreenFb0;
extern FramebufferImage* gGbScreenFb1;
extern u8 gStadiumUIMap[234];
extern u8 gGameTitle_PokemonYellow[16];
extern GbPakThreadContext GbPakThreadData[2];
extern s32 gGbPakMessageQueue[];
extern s32 gGbPakTaskBufferIndex;
extern GbPakDeviceState* GbPakDevice;
extern TileAssetFragment* TileAssetFragments[3];
extern FramebufferImage* FramebufferImages[2];
extern s32 ScreenBasePtr;
extern void* UnknownPtr;
extern s32 UnknownCounter;
extern u8* TempScreenBufferPtr;
extern TileAssetFragment* TileAssetPtr;
extern s32 UnknownFlag;
typedef struct {
    /* 0x0000 */ OSThread thread;
    /* 0x01B0 */ u8 stack[0x1000];
} GbPakThreadStruct; // size = 0x11B0

extern GbPakThreadStruct gGbPakServiceThread;
extern OSMesg gGbPakServiceQueueMessages[4];
extern OSMesgQueue gGbPakServiceQueue;
extern s16 Msg_FadeCounter;
extern u8 gGbEmuMenuState;
extern u8 gMenuAnimCounter;
extern s32 gEmuSavedBindingSelection;
extern Controller* gPlayer1Controller;
extern u8 UnknownBufferC[];
extern u8 UnknownBufferE[];
extern u8 fragment2_ROM_START[];
extern u8 fragment1_misc_yay0_ROM_START[];
extern u8 D_102BA0_END[];
extern OSMesgQueue D_8122B1EC;
extern OSMesgQueue D_8122B254;
extern OSMesg D_8122B250;
extern OSMesgQueue* gGbPakSiEventQueue;
extern s32 gGbEmuRunState;
extern volatile u8 gGbPakServiceThreadActive;
extern u8 Buffer_GbPakReadFirstPass[];
extern u8 Buffer_GbPakReadSecondPass[];
extern u8 gGbEmuPresentationMode;
extern u8 gAudioInitialized;
extern u8 gPrevDataSetIndex;
extern u8 gDataSetLoadResult;
extern u8 gMarkerAnimFrame;
extern s32 gCurrentBufferIndex;
extern u8 Flag_GbPakError;
extern u8 gText_MenuTitle[];
extern u8 gText_ContinueGame[];
extern u8 gText_QuitGame[];
extern u8 gText_HelpConfig[];
extern u8 gText_ExitMenuPrompt[];
extern u8 gText_QuitGameBoyPrompt[];
extern u8 gText_StartSelectInfo[];
extern u8 gText_GameSavedPrompt[];
extern u8 gText_Yes[];
extern u8 gText_Empty[];
extern u8 gText_No[];
extern u8 gText_ButtonDoubleSpeed[];
extern u8 gText_EachPressPokemon[];
extern u8 gText_Config[];
extern u8 gText_ButtonCancel[];
extern u8 gText_UnableToSave[];
extern u8 gText_GBGamePakInfo[];
extern u8 gText_LeavingN64[];
extern u8 GbPakStateByte;
extern u16 gGbEmuBoundButtonMask0;
extern u16 gGbEmuBoundButtonMask1;
extern unk_D_8122C4FA gGbEmuButtonBindingSelections;
extern u8 GbPakStatusByte;
extern u8 TempBuffer_GbPakReg[0x1F];
// extern s8 D_8122C51F;
extern u8 gGbPakProbeBuffer[0x20];
extern u8* gGbEmuFont1Data;
extern u8* gGbEmuFont2Data;
extern u8* DataStruct_TileAssets;
extern s32 Ptr_TempScreenBuffer;
extern s32 Ptr_TempScreenBuffer2;
extern u8* gCurrentFramebufferPtr;
extern u8 D_8120D8FD;
extern u8 D_8120D8FE;
extern u8 D_8120D906;
extern u8* gImageDataPtrs[2];
extern u32 gStadiumTimer;
extern u32 gSubTimer;
extern u32 gTimerInterval;
extern u32 gStadiumInterval;
extern u8 gStadiumScreenFlag0;
extern u8 gPlayerInfoBoxPort;

s32 GbPak_CheckConnectorReady(GbPakDeviceState* arg0) {
  s32 result;

  result = osGbpakCheckConnector(&arg0->pfs, &arg0->status);
  if ((result == 0) && ((arg0->status & 9) != 9)) {
      return 0x63;
  }
  return result;
}

s32 GbPak_WriteFilledRegisterBlock(GbPakDeviceState* arg0, u16 arg1, s32 arg2) {
  s32 i;
  for (i = 0x1F; i >= 0; i--) {
      TempBuffer_GbPakReg[i] = arg2;
  }
  return osGbpakReadWrite(&arg0->pfs, 1, arg1, &TempBuffer_GbPakReg, 0x20);
}

s32 GbPak_InitializeCartridgeMapper(GbPakDeviceState* arg0) {
  s32 ret;

  if (!(ret = GbPak_WriteFilledRegisterBlock(arg0, 0, 0xA))    && !(ret = GbPak_WriteFilledRegisterBlock(arg0, 0x6000, 1))
   && !(ret = GbPak_WriteFilledRegisterBlock(arg0, 0x4000, 0)) && !(ret = GbPak_WriteFilledRegisterBlock(arg0, 0x6000, 0))
   && !(ret = GbPak_WriteFilledRegisterBlock(arg0, 0x4000, 0)) && !(ret = GbPak_WriteFilledRegisterBlock(arg0, 0x2100, 1))) {
      arg0->romBank = 1;
      arg0->ramBank = 0;
      arg0->bankingMode = 0;
  }
  
  return ret;
}

s32 GbPak_CheckTransferStatus(GbPakDeviceState* arg0) {
  s32 ret;

  ret = osGbpakGetStatus(&arg0->pfs, &arg0->status);
  if (ret == 0) {
    ret = (arg0->status & 0xC0) ^ 0x80;
  }
  return ret;
}

s32 GbPak_SelectRomAddress(GbPakDeviceState* arg0, s32 arg1) {
  s32 temp_a2;
  s32 var_v1;

  var_v1 = 0;
  arg0->ramBank = 0xFF;
  if (arg0->bankingMode != 0) {
      arg0->romBank = 0xFFFFU;
      var_v1 = GbPak_WriteFilledRegisterBlock(arg0, 0x6000, 0);
      if (var_v1 == 0) {
          arg0->bankingMode = 0U;
      }
  }
  if (var_v1 == 0) {
      if (arg1 != arg0->romBank) {
          temp_a2 = arg1 / 32;
          if (temp_a2 != ((s32) arg0->romBank / 32)) {
              arg0->romBank = 0xFFFEU;
              var_v1 = GbPak_WriteFilledRegisterBlock(arg0, 0x4000, temp_a2);
          }
          if (var_v1 == 0) {
              arg0->romBank = 0xFFFDU;
              var_v1 = GbPak_WriteFilledRegisterBlock(arg0, 0x2100, arg1);
              if (var_v1 == 0) {
                  arg0->romBank = (u16) arg1;
              }
          }
      }
  }
  return var_v1;
}

s32 GbPak_SelectRamBank(GbPakDeviceState* arg0, s32 arg1) {
  s32 var_v1;

  var_v1 = 0;
  arg0->romBank = 0xFFFF;
  if (arg0->bankingMode != 1) {
      arg0->ramBank = 0xFFU;
      var_v1 = GbPak_WriteFilledRegisterBlock(arg0, 0x6000, 1);
      if (var_v1 == 0) {
          arg0->bankingMode = 1U;
      }
  }
  if ((var_v1 == 0) && (arg1 != arg0->ramBank)) {
      var_v1 = GbPak_WriteFilledRegisterBlock(arg0, 0x4000, arg1);
      if (var_v1 == 0) {
          arg0->ramBank = arg1;
      }
  }
  return var_v1;
}

s32 GbPak_VerifyProbeBlock(GbPakDeviceState* arg0) {
  s32 ret;

  ret = GbPak_SelectRamBank(arg0, arg0->probeRamAddress / 8192);
  if (ret == 0) {
      ret = osGbpakReadWrite(&arg0->pfs, 0, ((arg0->probeRamAddress & 0x1FFF) | 0xA000), gGbPakProbeBuffer, sizeof(gGbPakProbeBuffer));
      if (ret == 0) {
          ret = bcmp(gGbPakProbeBuffer, &arg0->probeData0, sizeof(gGbPakProbeBuffer));
      }
  }
  return ret;
}

void GbPak_PrepareProbeBlock(GbPakDeviceState* arg0, s32 arg1) {
  s32 i;

  switch (arg1) {
      case 3:
          for (i = 0; i < 8; i++) {
              arg0->probeData0[i] = 0;
          }
          break;
      case 2:
          for (i = 0; i < 8; i++) {
              arg0->probeData0[i] = -1;
          }
          break;
      case 1:
          osDpGetCounters(arg0->probeData0);
          arg0->probeData0[3] = osGetCount();
          osWritebackDCacheAll();
          osDpGetCounters(arg0->probeData1);
          arg0->probeData1[3] = osGetCount();
          break;
  }
}

s32 GbPak_VerifyWritableProbeBlock(GbPakDeviceState* arg0) {
    s32 ret;
    s32 count;

    count = 3;
    do {
        GbPak_PrepareProbeBlock(arg0, count);
        ret = GbPak_SelectRamBank(arg0, arg0->probeRamAddress / 8192);
        if (ret == 0) {
            ret = osGbpakReadWrite(&arg0->pfs, 1, ((arg0->probeRamAddress & 0x1FFF) | 0xA000), &arg0->probeData0, sizeof(gGbPakProbeBuffer));
            if (ret == 0) {
                ret = osGbpakReadWrite(&arg0->pfs, 0, ((arg0->probeRamAddress & 0x1FFF) | 0xA000), gGbPakProbeBuffer, sizeof(gGbPakProbeBuffer));
                if (ret == 0) {
                    ret = bcmp(gGbPakProbeBuffer, &arg0->probeData0, sizeof(gGbPakProbeBuffer));
                    if (ret == 0) {
                        count -= 1;
                        if (count == 0) {
                            arg0->ramWriteVerified = 1;
                            break;
                        }
                    }
                }
            }
        }
    } while ((ret == 0));
    return ret;
}

s32 GbPak_ProbeCartridge(GbPakDeviceState* arg0) {
  s32 ret;

  ret = 0;
  if (!(arg0->status & 1)) {
    ret = GbPak_CheckConnectorReady(arg0);
      if (ret == 0) {
        ret = GbPak_InitializeCartridgeMapper(arg0);
          if (ret == 0) {
            ret = osGbpakReadId(&arg0->pfs, &arg0->gbpakId, &arg0->status);
              if (ret == 0) {
                ret = bcmp(&arg0->detectedGbpakId, &arg0->gbpakId, sizeof(arg0->detectedGbpakId));
                  if ((ret == 0) && (arg0->ramWriteVerified != 0)) {
                      arg0->ramWriteVerified = 0U;
                      ret = GbPak_VerifyProbeBlock(arg0);
                      if (ret == 0) {
                        ret = GbPak_VerifyWritableProbeBlock(arg0);
                      }
                      arg0->ramWriteVerified = 1U;
                  }
              }
          }
      }
  }
  if (ret != 0) {
      arg0->status = (u8) (arg0->status & 0xFFFE);
  }
  return ret;
}

s32 GbPak_ReadRomAndChecksum(GbPakDeviceState* arg0) {
    s32 var_s1 = 0;
    s32 var_s2;
    s32 var_s2_2;
    s32 var_s4;
    s32 var_v1;
    u32 var_s3;
    u8* var_s0;
    u32 offset;
    s32 i;
    u32 temp;
    var_v1 = GbPak_ProbeCartridge(arg0);
    var_s0 = arg0->transferBuffer;
    var_s3 = arg0->gbAddress;
    var_s4 = arg0->transferSize;

    if (var_v1 == 0 && var_s3 < 0x4000U) {
        temp = var_s3;
        temp += var_s4;
        if (temp >= 0x4001U) {
            var_s2 = 0x4000 - var_s3;
        } else {
            var_s2 = var_s4;
        }

        var_v1 = osGbpakReadWrite(&arg0->pfs, 0, var_s3, var_s0, var_s2);

        if (var_v1 == 0) {
            var_v1 = var_s2;

            while (var_v1 != 0) {
                var_s1 += *var_s0;
                var_s0++;
                var_v1--;
            }
            var_s4 -= var_s2;
            var_s3 = 0x4000;
        }
    }

    while (var_v1 == 0 && var_s4 != 0) {
        var_v1 = GbPak_SelectRomAddress(arg0, var_s3 >> 14);
        if (var_v1 == 0) {
            offset = var_s3 & 0x3FFF;
            temp = offset;
            temp += var_s4;
            if (temp >= 0x4001U) {
                var_s2_2 = 0x4000 - offset;
            } else {
                var_s2_2 = var_s4;
            }
    
            var_v1 = osGbpakReadWrite(&arg0->pfs, 0, (offset | 0x4000), var_s0, var_s2_2);
    
            if (var_v1 == 0) {
                var_v1 = var_s2_2;
    
                    while (var_v1 != 0) {
                        var_s1 += *var_s0;
                        var_s0++;
                        var_v1--;
                    }
    
                var_s4 -= var_s2_2;
                var_s3 = (var_s3 + 0x4000) & ~0x3FFF;
            }
        }
    }

    if (var_v1 == 0) {
        var_v1 = GbPak_CheckTransferStatus(arg0);
        if (var_v1 == 0) {
            arg0->gameVariantData[0] += var_s1;
        }
    }

    return var_v1;
}

s32 GbPak_TransferBankedRam(GbPakDeviceState* arg0, s32 arg1) {
  s32 temp_v0;
  s32 var_s0;
  s32 var_s1;
  u8* var_s3;
  s32 var_v0;
  s32 var_v1;
  u32 var_s2;

  var_v0 = GbPak_ProbeCartridge(arg0);
  var_v1 = var_v0;
  var_s3 = arg0->transferBuffer;
  var_s2 = arg0->gbAddress;
  var_s1 = arg0->transferSize;
  while ((var_v0 == 0) && (var_s1 != 0)) {
      var_v0 = GbPak_SelectRamBank(arg0, var_s2 >> 0xD);
      var_v1 = var_v0;
      if (var_v0 == 0) {
          temp_v0 = var_s2 & 0x1FFF;
          if ((u32) (temp_v0 + var_s1) >= 0x2001U) {
              var_s0 = 0x2000 - temp_v0;
          } else {
              var_s0 = var_s1;
          }
          var_v0 = osGbpakReadWrite(&arg0->pfs, arg1, (temp_v0 | 0xA000) & 0xFFFF, var_s3, var_s0);
          var_v1 = var_v0;
          var_s3 += var_s0;
          var_s1 -= var_s0;
          var_s2 = (var_s2 + 0x2000) & ~0x1FFF;
      }
  }
  if (var_v0 == 0) {
      var_v1 = GbPak_CheckTransferStatus(arg0);
  }
  return var_v1;
}

s32 GbPak_MatchCartridgeTitleIndex(GbPakHeader* arg0) {
  u8* var_s1;
  s32 i;

  var_s1 = gGameTitle_PokemonYellow;
  for (i = 4; i > 0; i--) {
      if (
          (bcmp(var_s1, arg0->data, 0x10) == 0) &&
          (arg0->unk_44 == 0x3031) &&
          (arg0->unk_46 == 3) &&
          (arg0->unk_48 == 5) &&
          (arg0->unk_49 == 3) &&
          (arg0->unk_4A != 0)
      ) {
         return i;
      }
      var_s1 -= 0x10;
  }
  return i;
}

void GbPak_ThreadMain(s32 arg0) {
    u16* entry;
    s32 retries;
    GbPakDeviceState* emu;
    u32 value;
    u16 sum;
    u8* ptr;
    s32 i;

    gGbPakServiceThreadActive = 1;

    for (;;) {
        osRecvMesg(&gGbPakServiceQueue, (OSMesg*)&emu, OS_MESG_BLOCK);
        if (emu == NULL) {
            gGbPakServiceThreadActive = 0;
            osDestroyThread(NULL);
        }
        emu->unk_5DC8 = 1;
        if ((emu->unk_5DCA == 0) && (emu->controllerChannel < 4)) {
            emu->command = 0;
            emu->unk_5DC8 = 0;
            continue;
        }

        emu->retryBudget = 0x49;
    retry:
        emu->retryBudget--;
        if (emu->retryBudget <= 0) {
            goto disconnect;
        }
        switch (emu->unk_5DC9) {
            case 0:
                emu->unk_5DC9 = 1;
                bzero(&emu->detectedGbpakId, sizeof(emu->detectedGbpakId));
                /* fallthrough */
            case 1:
                emu->retryBudget -= 9;
                if (osGbpakInit(gGbPakSiEventQueue, (OSPfs*)&emu->pfs, emu->controllerChannel) != 0) {
                    goto retry;
                }
                if (osGbpakReadId((OSPfs*)&emu->pfs, &emu->detectedGbpakId, &emu->status) != 0) {
                    goto retry;
                }
                if (GbPak_CheckConnectorReady(emu) != 0) {
                    goto retry;
                }
                if (GbPak_InitializeCartridgeMapper(emu) != 0) {
                    goto retry;
                }
                emu->transferBuffer = emu->romSignature;
                emu->gbAddress = 0x9C000;
                emu->transferSize = 0x20;
                if (GbPak_ReadRomAndChecksum(emu) != 0) {
                    goto retry;
                }
                if (!(emu->status & 1)) {
                    goto retry;
                }
                emu->headerMatchIndex = GbPak_MatchCartridgeTitleIndex((GbPakHeader*)&emu->detectedGbpakId);
                emu->unk_5DC9 = 2;
                /* fallthrough */
            case 2:
                switch (emu->command) {
                    case 1:
                        emu->retryBudget -= 0x17;
                        if (GbPak_ReadRomAndChecksum(emu) != 0) {
                            goto retry;
                        }
                        break;
                    case 2:
                        emu->retryBudget -= 0x17;
                        if (GbPak_TransferBankedRam(emu, 0) != 0) {
                            goto retry;
                        }
                        break;
                    case 3:
                        emu->retryBudget -= 0x17;
                        if (GbPak_TransferBankedRam(emu, 1) != 0) {
                            goto retry;
                        }
                        break;
                    case 5:
                        emu->transferBuffer = Buffer_GbPakReadFirstPass;
                        emu->transferSize = 0x100;
                        if ((GbPak_TransferBankedRam(emu, 1) == 0) &&
                            (emu->transferBuffer = Buffer_GbPakReadSecondPass, GbPak_TransferBankedRam(emu, 0) == 0) &&
                            (bcmp(Buffer_GbPakReadFirstPass, Buffer_GbPakReadSecondPass, 0x100) == 0)) {
                            if (emu->blockReadStatus[emu->gbAddress >> 8] != 0) {
                                emu->blockReadStatus[emu->gbAddress >> 8] = 2;
                            }
                            break;
                        }
                        emu->status &= ~1;
                        osGbpakPower((OSPfs*)&emu->pfs, 0);
                        retries = 0x3C;
                        emu->unk_5DC9 = 8;
                        goto retry;
                    case 6:
                        emu->retryBudget -= 2;
                        entry = (u16*)emu->gameVariantData[1];
                        do {
                            value = *entry;
                            if (*entry & 0x8000) {
                                if (emu->unk_559C[value & 0xF] == 0) {
                                    emu->gbAddress = (value & 0xF) << 13;
                                    emu->transferBuffer = (u8*)emu + emu->gbAddress + 0x12DF0;
                                    emu->transferSize = 0x2000;
                                    if (GbPak_TransferBankedRam(emu, 0) != 0) {
                                        goto disconnect;
                                    }
                                    emu->unk_559C[entry[0] & 0xF] = 0xFF;
                                }
                                entry += 1;
                            } else {
                                if (emu->unk_549C[*entry] == 0) {
                                    emu->gbAddress = value << 14;
                                    emu->transferBuffer = (u8*)emu->romImage + emu->gbAddress;
                                    emu->transferSize = 0x4000;
                                    if (GbPak_ReadRomAndChecksum(emu) != 0) {
                                        goto retry;
                                    }
                                    sum = 0;
                                    ptr = emu->transferBuffer;
                                    for (i = 0; i < 0x2000; i++) {
                                        sum += *ptr;
                                        ptr++;
                                    }
                                    if (sum != entry[1]) {
                                        goto retry;
                                    }
                                    sum = 0;
                                    for (i = 0; i != 0x2000U; i++) {
                                        sum += *ptr;
                                        ptr++;
                                    }
                                    if (sum != entry[2]) {
                                        goto retry;
                                    }
                                    emu->unk_549C[entry[0]] = 0xFF;
                                }
                                entry += 3;
                            }
                        } while (*entry);
                        break;
                    case 8:
                        emu->ramWriteVerified = 0;
                        if (GbPak_ProbeCartridge(emu) != 0) {
                            goto retry;
                        }
                        if (GbPak_VerifyWritableProbeBlock(emu) != 0) {
                            goto retry;
                        }
                        break;
                    case 7:
                        if (GbPak_CheckTransferStatus(emu) != 0) {
                            goto retry;
                        }
                        break;
                    case 4:
                        emu->retryBudget -= 0x17;
                        emu->status &= ~1;
                        if (osGbpakPower((OSPfs*)&emu->pfs, 0) != 0) {
                            goto retry;
                        }
                        break;
                    case 0:
                    default:
                        break;
                }
                emu->command = 0;
                break;
            case 8:
            case 11:
                if (emu->command != 7) {
                    break;
                }
                if (GbPak_CheckTransferStatus(emu) != 0) {
                    if (--retries == 0) {
                        retries = 5;
                        emu->unk_5DC9 = 9;
                    }
                } else {
                    retries = 0x3C;
                }
                break;
            case 9:
                if (osGbpakInit(gGbPakSiEventQueue, (OSPfs*)&emu->pfs, emu->controllerChannel) != 0) {
                    retries = 5;
                } else {
                    if (GbPak_CheckTransferStatus(emu) == 0) {
                        if (--retries == 0) {
                            i = GbPak_ProbeCartridge(emu);
                            if (i != 0) {
                                goto power_off;
                            } else if (i == 0) {
                                emu->unk_5DC9 = 10;
                            }
                        }
                    } else {
                        retries = 5;
                    }
                }
                break;
            case 10:
                emu->transferBuffer = Buffer_GbPakReadFirstPass;
                if ((GbPak_TransferBankedRam(emu, 1) == 0) &&
                    (emu->transferBuffer = Buffer_GbPakReadSecondPass, GbPak_TransferBankedRam(emu, 0) == 0) &&
                    (bcmp(Buffer_GbPakReadFirstPass, Buffer_GbPakReadSecondPass, 0x100) == 0)) {
                    if (emu->blockReadStatus[emu->gbAddress >> 8] != 0) {
                        emu->blockReadStatus[emu->gbAddress >> 8] = 2;
                    }
                    emu->unk_5DC9 = 2;
                    emu->command = 0;
                    break;
                }
            power_off:
                retries = 0x3C;
                emu->status &= ~1;
                osGbpakPower((OSPfs*)&emu->pfs, 0);
                emu->unk_5DC9 = 11;
                break;
            default:
            disconnect:
                emu->unk_5DCA = 0;
                break;
        }
        emu->unk_5DC8 = 0;
    }
}

void Gfx_DrawTileMap(u16* fb, u8* cmd) {
    u8* ptr;
    u8* map;
    u8* data;
    u8* src;
    u16* dst;
    u16* pal;
    u8 flags;
    u8 y;
    s32 tile;
    s32 width;
    s32 x;
    s32 dir;
    long trans;
    s32 tileSize;
    s32 count;
    s32 row;
    s32 col;

    flags = *cmd;
    ptr = cmd;
    while (((unsigned int) flags) != 0) {
        trans = flags;
        x = ptr[1] + ((flags & 1) << 8);
        y = ptr[2];
        if (flags & 0x40) {
            dir = -1;
        } else {
            dir = 0;
        }
        dst = fb + (y * 0x140 + x);
        trans &= 0x20;

        switch (ptr[3]) {
            default:
                map = TileMap_8x8;
                data = gGbEmuFont1Data;
                tileSize = 0xA;
                break;
            case 0xC:
                tileSize = 0xC;
                map = TileMap_12x12;
                data = gGbEmuFont2Data;
                break;
            case 0xA:
                map = TileMap_8x8, data = gGbEmuFont1Data;
                tileSize = 0xA;
                break;
        }

        switch (ptr[4]) {
            case 1:
                pal = (u16*) &gGbEmuTextPaletteYellow;
                break;
            case 2:
                pal = (u16*) &gGbEmuTextPaletteBlackWhite;
                break;
            case 3:
                pal = (u16*) &gGbEmuTextPaletteBlackGray;
                break;
            case 4:
                pal = (u16*) &gGbEmuTextPaletteRed;
                break;
            case 5:
                pal = (u16*) &gGbEmuTextPaletteGreen;
                break;
            case 6:
                pal = (u16*) &gGbEmuTextPaletteBlue;
                break;
            case 7:
                pal = (u16*) &gGbEmuTextPaletteGrayAlt;
                break;
            case 8:
                pal = (u16*) &gGbEmuTextPaletteYellowPale;
                break;
            case 9:
                pal = (u16*) &gGbEmuTextPaletteCyan;
                break;
            case 10:
                pal = (u16*) &gGbEmuTextPaletteGrayDark;
                break;
            case 11:
                pal = (u16*) &gGbEmuTextPalettePink;
                break;
            case 0:
            default:
                pal = (u16*) &gGbEmuTextPaletteGray;
                break;
        }

        count = ptr[5];
        while (count != 0) {
            count--;
            tile = map[ptr[6] + 0x80];
            width = map[tile];
            src = data + tile * tileSize * 0x10;

            for (row = 0; row != tileSize; row++) {
                for (col = 0; col != width; col++) {
                    if (trans || (pal[*src & 0xF] != 0)) {
                        *dst = pal[*src & 0xF];
                    }
                    dst++;
                    src++;
                }
                dst = dst - width + 0x140;
                src = src - width + 0x10;
            }
            ptr++;
            dst -= tileSize * 0x140 - width - dir;
        }
        flags = ptr[6];
        ptr += 6;
    }
}

s32 GbEmu_PixelOpDitherA(s32 arg0, s32 arg1) {
  return (arg1 & 1) ? arg1 : arg0;
}

s32 GbEmu_PixelOpDitherB(s32 arg0, s32 arg1) {
  return (arg1 & 1) ? arg0 : arg1;
}

s32 GbEmu_PixelOpAverage555(s32 arg0, s32 arg1) {
  return (((s32) ((arg0 & 0xF800) + (arg1 & 0xF800)) >> 1) & 0xF800) | (((s32) ((arg0 & 0x7C0) + (arg1 & 0x7C0)) >> 1) & 0x7C0) | (((s32) ((arg0 & 0x3E) + (arg1 & 0x3E)) >> 1) & 0x3E);
}

s32 GbEmu_PixelOpReplace(UNUSED s32 arg0, s32 arg1) {
  return arg1;
}

void GbEmu_BlitWithPixelOp(u16* dst, u16* src, s32 mode, s32 width, s32 height) {
  s32 (*operation)(s32, s32);
  s32 x;
  s32 y;
  width = ((width + 3) & 0xFFC);
  switch (mode) {
      case 0:  operation = GbEmu_PixelOpDitherA; break;
      case 1:  operation = GbEmu_PixelOpDitherB; break;
      case 2:  operation = GbEmu_PixelOpAverage555; break;
      default: operation = GbEmu_PixelOpReplace; break;
  }

  for (x = 0; x != height; x++) {
      for (y = 0; y != width; y++) {
          *dst = operation(*dst, *src);
          dst++;
          src++;
      }
      dst = dst - width + 0x140;
  }
}

void GbEmu_DrawFramedPanel(u16* dst) {
    s32 i;
    s32 y;

    for (i = 1; i < 5; i++) {
        GbEmu_BlitWithPixelOp(dst + i * 8, (u16*) (DataStruct_TileAssets + 0x1180), 0xFFFF, 8, 8);
        GbEmu_BlitWithPixelOp(dst + 38 * 320 + i * 8, (u16*) (DataStruct_TileAssets + 0x1400), 0xFFFF, 8, 8);
        GbEmu_BlitWithPixelOp(dst + i * 8 * 320, (u16*) (DataStruct_TileAssets + 0x1280), 0xFFFF, 8, 8);
        GbEmu_BlitWithPixelOp(dst + i * 8 * 320 + 38, (u16*) (DataStruct_TileAssets + 0x1300), 0xFFFF, 8, 8);
    }

    GbEmu_BlitWithPixelOp(dst, (u16*) (DataStruct_TileAssets + 0x1100), 0, 8, 8);
    GbEmu_BlitWithPixelOp(dst + 38, (u16*) (DataStruct_TileAssets + 0x1200), 0, 8, 8);
    GbEmu_BlitWithPixelOp(dst + 38 * 320, (u16*) (DataStruct_TileAssets + 0x1380), 0, 8, 8);
    GbEmu_BlitWithPixelOp(dst + 38 * 320 + 38, (u16*) (DataStruct_TileAssets + 0x1480), 0, 8, 8);

    for (y = 0; y < 30; y++) {
        for (i = 0; i < 30; i++) {
            dst[(y + 8) * 320 + (i + 8)] = 0xC14;
        }
    }
}

void ApplyColorIntensity(u16* dst, u16* src, s32 color, s32 width, s32 height) {
    s32 x;
    s32 y;
    s32 intensity;

    for (y = 0; y < height; y++) {
        for (x = 0; x < width; x++) {
            intensity = (src[y * width + x] & 0x3E) >> 1;
            dst[y * 320 + x] = ((((color & 0xF800) * intensity) / 31) & 0xF800) |
                               ((((color & 0x7C0) * intensity) / 31) & 0x7C0) |
                               ((((color & 0x3E) * intensity) / 31) & 0x3E);
        }
    }
}

void BlendWithAlphaMap(u16* dst, u8* alpha_map, s32 color, s32 width, s32 height, u32 alpha_stride) {
    u16* dst_row;
    u8* alpha_row;
    s32 x;
    s32 y;
    s32 var_t0;
    s32 var_t4;
    s32 var_a0;

    for (y = 0; y < height; y++) {
        for (x = 0; x < width; x++) {
            var_a0 = alpha_map[y * alpha_stride + x] & 0xF;

            var_t0 = (dst[y * 320 + x] & 0xF800) + ((((color & 0xF800) * (var_a0)) / 15) & 0xF800);
            if (var_t0 > 0xF800) var_t0 = 0xF800;

            var_t4 = var_t0;

            var_t0 = (dst[y * 320 + x] & 0x07C0) + ((((color & 0x07C0) * (var_a0)) / 15) & 0x07C0);
            if (var_t0 > 0x07C0) var_t0 = 0x07C0;
            
            var_t4 |= var_t0;

            var_t0 = (dst[y * 320 + x] & 0x003E) + ((((color & 0x003E) * (var_a0)) / 15) & 0x003E);
            if (var_t0 > 0x003E) var_t0 = 0x003E;

            dst[y * 320 + x] = (s16)(var_t4 | var_t0);
        }
    }
}

void GbEmu_DrawStretchedBorderRow(s32 arg0, s32 arg1, s32 arg2) {
  s32 var_s0;
  s32 var_s1;
  s32 i;

  for (i = 8; i < arg2 - 8; i += 8) {
      ApplyColorIntensity(arg0 + i * 2, &((GbPakAssetData*) DataStruct_TileAssets)->unk_9890, arg1, 8, 0x10);
  }
  ApplyColorIntensity(arg0, &((GbPakAssetData*) DataStruct_TileAssets)->unk_9790, arg1, 8, 0x10);
  ApplyColorIntensity(arg0 + (arg2 - 8) * 2, &((GbPakAssetData*) DataStruct_TileAssets)->unk_9990, arg1, 8, 0x10);
}

void DrawVerticalMarker(u16* dst, s32 arg1, s32 arg2) {
  u16* src;
  s32 offset;
  s32 row;
  s32 col;
  u16 val;

  offset = arg2 * 132;
  if (arg1 != 0) {
      src = (u16*) (offset * 2 + DataStruct_TileAssets + 0x9A90);
      arg1 = 1;
  } else {
      src = (u16*) (offset * 2 + DataStruct_TileAssets + 0x9B96);
      arg1 = -1;
  }

  for (row = 0; row < 11; row++) {
      for (col = 0; col < 12; col++) {
          val = *src;
          if (val & 1) {
              dst[row * 320 + col + 730] = val;
          }
          src += arg1;
      }
  }
}

void DrawStadiumScreen(s32 arg0, s32 arg1) {
    u8* fb;
    s32 x;
    s32 i;
    s32 count;
    s32 off;

    fb = (u8*) FramebufferImages[arg0];
    bzero(FramebufferImages[arg0], 0x2800);
    fb += 0xAA;

    i = GbPakDevice->headerMatchIndex;
    if (i != 0) {
        i--;
    }
    GbEmu_DrawStretchedBorderRow((s32) fb, gGbPakBorderColors[i], 0x70);

    if (arg1 != 0) {
        count = 8;
        arg1 = 0xA;
    } else {
        count = 9;
    }
    x = 0;

    for (i = 0; i <= count; i++) {
        BlendWithAlphaMap((u16*) ((x * 2) + fb + 0x788),
                      &gGbEmuFont1Data[TileMap_8x8[gStadiumScreenText[arg1 + count - i] - i + 0x43] * 0xA0], 0xFFFE, 0xC, 0xA,
                      0x10);
        x += TileMap_8x8[TileMap_8x8[gStadiumScreenText[arg1 + count - i] - i + 0x43]];
    }

    GbEmu_BlitWithPixelOp((u16*) (fb + 0x7FE), (u16*) (DataStruct_TileAssets + 0xAD18), 0, 0x10, 0xA);

    i = GbPakDevice->headerMatchIndex;
    if (i != 0) {
        i--;
    }
    off = i * 0x90;
    GbEmu_BlitWithPixelOp((u16*) (fb + 0x5C2), (u16*) ((off * 2) + DataStruct_TileAssets + 0xAE58), 0, 0xC, 0xC);

    DrawVerticalMarker((u16*) (fb - 0x10), arg1, 0);
    gMarkerAnimFrame = 0;
}

void DrawStadiumUI(void) {
    u8* var_s2;
    s32 temp_s0;
    s32 var_s0;
    s32 var_s1;
    s32 var_s4;
    u16 temp_v1;

    temp_v1 = GbPakDevice->headerMatchIndex;
    temp_s0 = ScreenBasePtr - 0x14;
    temp_v1 = gGbPakBorderColors[(temp_v1 != 0) ? (temp_v1 - 1) : 0];
    switch (gGbEmuPresentationMode) {
        case 1:
            GbEmu_DrawStretchedBorderRow(temp_s0 + 0xA4, temp_v1, 0x8C);
            GbEmu_BlitWithPixelOp((u16*) (temp_s0 + 0x5AA), (u16*) (DataStruct_TileAssets + 0xA778), 0, 0x18, 0xD);
            GbEmu_BlitWithPixelOp((u16*) (temp_s0 + 0x1762), (u16*) (DataStruct_TileAssets + 0xA6D8), 0, 0x10, 5);
            GbEmu_BlitWithPixelOp((u16*) (temp_s0 + 0x5DE), (u16*) (DataStruct_TileAssets + 0xAC58), 0, 8, 6);
            GbEmu_BlitWithPixelOp((u16*) (temp_s0 + 0x5EE), (u16*) (DataStruct_TileAssets + 0xACB8), 0, 8, 6);
            var_s4 = temp_s0 + 0x600;
            break;
        case 2:
            GbEmu_DrawStretchedBorderRow(temp_s0 + 0x9C, temp_v1, 0x94);
            GbEmu_BlitWithPixelOp((u16*) (temp_s0 + 0x5A4), (u16*) (DataStruct_TileAssets + 0xA9E8), 0, 0x18, 0xD);
            GbEmu_BlitWithPixelOp((u16*) (temp_s0 + 0x175C), (u16*) (DataStruct_TileAssets + 0xA5E8), 0, 0x18, 5);
            GbEmu_BlitWithPixelOp((u16*) (temp_s0 + 0x5D8), (u16*) (DataStruct_TileAssets + 0xAC58), 0, 8, 6);
            GbEmu_BlitWithPixelOp((u16*) (temp_s0 + 0x5E8), (u16*) (DataStruct_TileAssets + 0xACB8), 0, 8, 6);
            GbEmu_BlitWithPixelOp((u16*) (temp_s0 + 0x5F8), (u16*) (DataStruct_TileAssets + 0xACB8), 0, 8, 6);
            var_s4 = temp_s0 + 0x608;
            break;
        default:
        case 0:
            GbEmu_DrawStretchedBorderRow(temp_s0 + 0xCE, temp_v1, 0x60);
            var_s4 = temp_s0 + 0x5D6;
            break;
    }
    GbEmu_BlitWithPixelOp((u16*) var_s4, (u16*) (DataStruct_TileAssets + 0xC1D8), 0, 0xC, 0xC);

    var_s0 = 0;
    var_s4 -= 0x266;
    for (var_s2 = (u8*) &gStadiumUILayout, var_s1 = 0x37; var_s1 < 0x42; var_s1++, var_s2--) {
        BlendWithAlphaMap((u16*) ((var_s0 * 2) + var_s4), (TileMap_12x12[var_s2[0x116] - var_s1 + 0x80] * 0xC0) + gGbEmuFont2Data,
                      0xFFFE, 0xC, 0xC, 0x10);
        var_s0 += TileMap_12x12[TileMap_12x12[var_s2[0x116] - var_s1 + 0x80]];
        if (var_s1 == 0x3C) {
            var_s0 -= 1;
        }
        if (var_s1 == 0x3D) {
            var_s0 += 1;
        }
    }
}

void DrawPlayerInfoBox(s32 arg0, s32 arg1) {
    s32 temp_s4;
    s32 temp_s6;
    s32 i;

    temp_s4 = (arg1 * 0x28) << 1;
    for (i = 0; i < 6; i++) {
        GbEmu_BlitWithPixelOp((u16*) (arg0), (u16*) (temp_s4 + DataStruct_TileAssets + 0x8910), 0, 8, 5);
        arg0 += 0x10;
    }
    temp_s6 = arg1 << 6;
    temp_s6 <<= 1;
    GbEmu_BlitWithPixelOp((u16*) (arg0), (u16*) (temp_s6 + DataStruct_TileAssets + 0x8F90), 0, 8, 8);
    arg0 += 0x1406;
    for (i = 0; i < 5; i++) {
        GbEmu_BlitWithPixelOp((u16*) (arg0), (u16*) (temp_s6 + DataStruct_TileAssets + 0x8090), 0, 8, 8);
        arg0 += 0x1400;
    }
    GbEmu_BlitWithPixelOp((u16*) (arg0), (u16*) (temp_s6 + DataStruct_TileAssets + 0x8510), 0, 8, 8);
    arg0 += 0x10;
    switch (gPlayerInfoBoxPort) {
    case 1:
        i = 7;
        break;
    case 2:
        i = 0xA;
        break;
    case 3:
        i = 0xB;
        break;
    default:
        i = 6;
        break;
    }
    while (i > 0) {
        GbEmu_BlitWithPixelOp((u16*) (arg0 + 0x780), (u16*) (temp_s4 + DataStruct_TileAssets + 0x8910), 0, 8, 5);
        arg0 += 0x10;
        i--;
    }
    GbEmu_BlitWithPixelOp((u16*) (arg0), (u16*) (temp_s6 + DataStruct_TileAssets + 0x8B90), 0, 8, 8);
    arg0 -= 0x13FA;
    GbEmu_BlitWithPixelOp((u16*) (arg0), (u16*) (temp_s6 + DataStruct_TileAssets + 0x9390), 0, 8, 8);
    arg0 -= 0x1400;
    GbEmu_BlitWithPixelOp((u16*) (arg0), (u16*) (temp_s6 + DataStruct_TileAssets + 0x9390), 0, 8, 8);
    arg0 -= 0x1400;
    GbEmu_BlitWithPixelOp((u16*) (arg0), (u16*) (DataStruct_TileAssets + 0x8490), 0, 8, 8);
}
void DrawFullScreenBackground(u16* dst, u16 (*arg1)[6][0x640], s32 arg2, s32 arg3) {
    s32 x;
    s32 y;
    s32 step;
    u16* row;
    s32 xpos;
    s32 i;
    s32 n;
    s32 j;

    step = 0x5000;
    for (y = 0; y < 0x14000; y += step) {
        row = dst + y;
        for (x = 0; x != 320u; x += 64) {
            GbEmu_BlitWithPixelOp(row, (u16*) ((u8*) DataStruct_TileAssets + 0x1500), 0xFFFF, 64, (y == 0xF000) ? 48 : 64);
            row += 64;
        }
    }

    if (Ptr_TempScreenBuffer == 0) {
        xpos = 0;
        Ptr_TempScreenBuffer = (s32) TempScreenBufferPtr;
        TempScreenBufferPtr += 0x2580;
        j = 9;
        x = 8; // FAKE: x = 8 ... x++ ... if (x != 0) keeps the "li s0,9; beqz" loop guard
        _bcopy(dst + 0x10540, (void*) Ptr_TempScreenBuffer, 0x2580);
        Ptr_TempScreenBuffer2 = (s32) TempScreenBufferPtr;
        TempScreenBufferPtr += 0x2580;
        bzero((void*) Ptr_TempScreenBuffer2, 0x2580);
        x++;

        if (x != 0) {
            for (i = j; i != 0; i++) {
                BlendWithAlphaMap((u16*) ((xpos * 2) + Ptr_TempScreenBuffer2 + 0x280),
                              (TileMap_12x12[gStadiumUIMap[0xE7 - i] - i * 2 + 0x5B] * 0xC0) + gGbEmuFont2Data, 0xFFFE, 0xC, 0xC,
                              0x10);
                xpos += TileMap_12x12[TileMap_12x12[gStadiumUIMap[0xE7 - i] - i * 2 + 0x5B]];
                if (gStadiumUIMap[0xE6 - i] < 0x40) {
                    break;
                }
            }
        }
    }

    for (x = 0; x < 6; x++) {
        GbEmu_DrawFramedPanel(dst + 0xB916 + x * 46);
        if (arg1 != NULL) {
            osInvalDCache((*arg1) + (0, x), sizeof((*arg1)[x])); // FAKE: (0, x)
            GbEmu_BlitWithPixelOp(dst + 0xBCD9 + x * 46, (*arg1) + (0, x), 0, 40, 40);
        }
    }

    for (j = 0; j < 6; j++) {
        for (x = 0; x < 320; x++) {
            dst[(j + 27) * 320 + x] = 0x25A;
            dst[(j + 121) * 320 + x] = 0x25A;
        }
    }

    for (x = 0; x < 320; x += 8) {
        GbEmu_BlitWithPixelOp(dst + 33 * 320 + x, (u16*) ((u8*) DataStruct_TileAssets + 0x3500), 0xFFFF, 8, 8);
        GbEmu_BlitWithPixelOp(dst + 113 * 320 + x, (u16*) ((u8*) DataStruct_TileAssets + 0x3580), 0xFFFF, 8, 8);
    }

    for (j = 0; j < 72; j++) {
        for (x = 0; x < 320; x++) {
            dst[(j + 41) * 320 + x] = 0x2BA4;
        }
    }

    switch (arg2) {
        case 1:
            gCurrentFramebufferPtr = (u8*) dst + 2;
            break;
        case 2:
            gCurrentFramebufferPtr = (u8*) dst + 4;
            break;
        case 3:
            gCurrentFramebufferPtr = (u8*) dst + 6;
            break;
        default:
            gCurrentFramebufferPtr = (u8*) dst;
            break;
    }

    GbEmu_BlitWithPixelOp(dst + 0x4E38, (u16*) ((u8*) DataStruct_TileAssets + 0x3600), 0, 0x56, 0x21);
    GbEmu_BlitWithPixelOp((u16*) (gCurrentFramebufferPtr + 0x61E0), (u16*) ((u8*) DataStruct_TileAssets + 0x4CB0), 0, 0x3C, 0x4B);

    switch (arg3) {
        case 0:
            GbEmu_BlitWithPixelOp((u16*) (gCurrentFramebufferPtr + 0x6706), (u16*) ((u8*) DataStruct_TileAssets + 0x6FD8), 0, 0x17, 0x19);
            break;
        case 1:
            break;
        case 2:
            GbEmu_BlitWithPixelOp((u16*) (gCurrentFramebufferPtr + 0x6706), (u16*) ((u8*) DataStruct_TileAssets + 0x7730), 0, 0x17, 0x19);
            break;
        case 3:
            GbEmu_BlitWithPixelOp((u16*) (gCurrentFramebufferPtr + 0x6706), (u16*) ((u8*) DataStruct_TileAssets + 0x7BE0), 0, 0x17, 0x19);
            break;
    }

    gPlayerInfoBoxPort = arg2;
    DrawPlayerInfoBox((s32) (gCurrentFramebufferPtr + 0x87BA), 0);
    gStadiumScreenFlag0 = 0;
    gTimerInterval = 0x800000;
    gSubTimer = 0xA0;
}

void BlendImagesClamp(u16* arg0, u16* arg1, s16* arg2, s32 arg3, s32 arg4) {
    s32 i;
    s32 j;
    s32 var_v1;
    s32 var_t4;

    for (j = 0; j < arg3; j++) {
        for (i = 0; i < 320; i++) {
            var_v1 = (arg0[(j * 320) + ((arg4 + i) % 320)] & 0xF800) + (arg1[(j * 320) + i] & 0xF800);
            if (var_v1 > 0xF800) {
                var_v1 = 0xF800;
            }
            var_t4 = var_v1;
            var_v1 = (arg0[(j * 320) + ((arg4 + i) % 320)] & 0x7C0) + (arg1[(j * 320) + i] & 0x7C0);
            if (var_v1 > 0x7C0) {
                var_v1 = 0x7C0;
            }
            var_t4 |= var_v1;
            var_v1 = (arg0[(j * 320) + ((arg4 + i) % 320)] & 0x3E) + (arg1[(j * 320) + i] & 0x3E);
            if (var_v1 > 0x3E) {
                var_v1 = 0x3E;
            }
            arg2[(j * 320) + i] = var_t4 | var_v1;
        }
    }
}

s32 EmuTick(s32 arg0, s32 arg1) {
    s32 var_s0;

    var_s0 = 0;
    if (gTimerInterval < (osGetCount() - gStadiumInterval)) {
        var_s0 = 1;
        gStadiumInterval = osGetCount();
        gStadiumScreenFlag0 = (gStadiumScreenFlag0 + 1) & 7;
        if (gTimerInterval >= 0x80001U) {
            gTimerInterval -= gTimerInterval >> 8;
        }
    }
    if ((osGetCount() - gStadiumTimer) >= 0x200001U) {
        var_s0 = 1;
        gStadiumTimer = osGetCount();
        gSubTimer++;
        if (gSubTimer >= 0x140U) {
            gSubTimer = 0;
        }
    }
    if (var_s0 != 0) {
        DrawPlayerInfoBox(arg0 + 0x87BA, gStadiumScreenFlag0);
        BlendImagesClamp(Ptr_TempScreenBuffer2, Ptr_TempScreenBuffer, arg1 + 0x20A80, 0xF, gSubTimer);
    }
    return var_s0;
}

void GbEmu_ResetEmulatorState(GbPakDeviceState* arg0) {
  s32 i;
  s32 var_a0;
  u8* var_a1;

  bzero(arg0->posX, 0x208);
  bzero(arg0->unk_208, 0x40);
  bzero(arg0->unk_248, 0x40);
  bzero(arg0->unk_388, 0x400);
  bzero(arg0->uiMap, 0x4000);
  bzero(arg0->unk_549C, 0x100);
  bzero(arg0->unk_559C, 0x10);
  bzero(arg0->memoryBases, 0x40);
  bzero(arg0->memoryWriteHandlers, 0x40);
  bzero(arg0->blockWriteMask, 0x200);
  bzero(arg0->blockReadStatus, 0x200);
  bzero(arg0->ioWriteHandlers, 0x200);
  bzero(arg0->tileCache, 0x6000);

  for (i = 0; i < 0x80; i++) {
      arg0->blockWriteMask[i] = 0xFE;
      arg0->blockReadStatus[i] = 0xFF;
  }

  for (i = 0; i < 0x400; i++) {
      arg0->unk_388[i] = 0xFF;
  }

  var_a0 = 0;
  for (i = 0x10; i < 0x1A0; i += 2) {
      arg0->uiMap[i] = gStadiumUIMap[var_a0];
      var_a0++;
  }

  var_a0 = 1;
  for (i = 0x1904; i < 0x1910; i++) {
      arg0->uiMap[i] = var_a0;
      arg0->uiMap[i + 32] = var_a0 + 0xC;
      var_a0 += 1;
  }
  arg0->uiMap[i] = 0x19;

  for (i = 1; i < 0x1A; i++) {
      arg0->unk_388[i] = 0;
  }

  for (i = 0x190; i < 0x193; i++) {
      arg0->unk_388[i] = 0;
  }

  arg0->unk_539C = 0x25800;
  arg0->unk_53FC = 0;
  arg0->unk_53FD = 0;
  arg0->unk_53EE = 0x140;
  arg0->unk_53FE = 0x30;
  arg0->unk_53F0 = 0x7C;
  arg0->monoGame = 1;
  arg0->mapperType = 0;
  arg0->audioMode = 1;
  arg0->romSize = 0x8000;
  arg0->ramSize = 0x8000;

  GbEmu_InitContext(arg0);
}

void GbEmu_ClearFramebuffers(void) {
  bzero(gGbScreenFb0->img_p, 0x2D000);
  bzero(gGbScreenFb1->img_p, 0x2D000);
}

void GbEmu_Delay(OSTime arg0) {
  OSMesgQueue sp68;
  void* sp64;
  OSTimer sp40;

  osCreateMesgQueue(&sp68, &sp64, 1);
  osSetTimer(&sp40, (1000 * arg0) * 64 / 3, 0, &sp68, NULL);
  osRecvMesg(&sp68, NULL, 1);
}

void DrawStadiumScreen(s32, s32);
void DrawStadiumUI(void);
void GbAudio_Init(void);
void GbApu_SelectRegionClock(s32);
void GbAudio_QueueWrite(u16, u8, u16);
void GbAudio_Reset(void);
void GbApu_Reset(TileAssetFragment*);
void func_81208F94(void);
void GbAudio_SetAlternateRendererEnabled(s32);

void EmuMainInit(s32 arg0, s32 arg1, OSId arg2, s32 arg3, OSMesgQueue* arg4, u16 (*arg5)[6][0x640]) {
    GbPakDeviceState* emu;
    s32 pad[2];
    s32 i;

    gGbScreenFb0 = GfxImage_Allocate(0, 2, 320, 288, 1);
    gGbScreenFb1 = GfxImage_Allocate(0, 2, 320, 288, 1);
    TileAssetPtr = main_pool_alloc(0x1FEAE8, 0);
    if (TileAssetPtr == NULL) {
        gGbEmuRunState = 1;
        UnknownFlag = 4;
        return;
    }
    TempScreenBufferPtr = (u8*)TileAssetPtr;

    osCreateMesgQueue(&GbPakThreadData[0].queue, GbPakThreadData[0].mesg, 1);
    osCreateMesgQueue(&GbPakThreadData[1].queue, GbPakThreadData[1].mesg, 1);
    UnknownCounter = 0;

    switch (osTvType) {
        case OS_TV_PAL:
            osViSetMode(&gViMode);
            break;
        case OS_TV_MPAL:
            osViSetMode(&osViModeMpalLpn1);
            break;
        case OS_TV_NTSC:
            osViSetMode(&osViModeNtscLpn1);
            break;
    }
    osViSetSpecialFeatures(OS_VI_GAMMA_OFF | OS_VI_GAMMA_DITHER_OFF | OS_VI_DIVOT_OFF);
    osViSetSpecialFeatures(OS_VI_DITHER_FILTER_OFF);
    osViBlack(TRUE);

    gGbPakServiceThreadActive = 0;
    gGbPakSiEventQueue = arg4;
    osCreateMesgQueue(&gGbPakServiceQueue, gGbPakServiceQueueMessages, ARRAY_COUNT(gGbPakServiceQueueMessages));
    osCreateThread(&gGbPakServiceThread.thread, arg2, (void (*)(void*)) GbPak_ThreadMain, NULL, gGbPakServiceThread.stack + sizeof(gGbPakServiceThread.stack), arg3);
    osStartThread(&gGbPakServiceThread.thread);

    gGbPakTaskBufferIndex = 0;
    UnknownPtr = TempScreenBufferPtr;
    TempScreenBufferPtr += 0xC410;

    for (i = 0; i < 1; i++) {
        emu = (GbPakDeviceState*)TempScreenBufferPtr;
        (&GbPakDevice)[i] = emu;
        bzero(emu, sizeof(GbPakDeviceState));
        TempScreenBufferPtr += sizeof(GbPakDeviceState);
        emu->tileCache = TempScreenBufferPtr;
        TempScreenBufferPtr += 0x6000;
        if (i == 0) {
            emu->activeFrameBuffer = TempScreenBufferPtr;
            TempScreenBufferPtr += 0x4D40;
            emu->nextFrameBuffer = TempScreenBufferPtr;
            TempScreenBufferPtr += 0x4D40;
            emu->spareFrameBuffer = TempScreenBufferPtr;
            TempScreenBufferPtr += 0x4D40;
            emu->rspTaskStatus = 0x400;
            if (i == 0) {
                emu->romImage = TempScreenBufferPtr;
                TempScreenBufferPtr += 0x100000;
            } else {
                emu->romImage = GbPakDevice->romImage;
            }
            GbEmu_ResetEmulatorState(emu);
            if ((i == 0) && (arg1 >= 0)) {
                if (arg1 < 4) {
                    emu->unk_5DCA = 1;
                }
                emu->controllerChannel = arg1;
                osSendMesg(&gGbPakServiceQueue, emu, OS_MESG_BLOCK);
            }
        }
    }

    Dma_WriteChunks((u32)(TempScreenBufferPtr + 0xC5C0), (u32)D_102BA0, ((u32)fragment2_ROM_START + 1) & ~1, 0);
    Yay0_Decompress((void*)((u32)TempScreenBufferPtr + 0xC5C0), TempScreenBufferPtr);
    DataStruct_TileAssets = TempScreenBufferPtr;
    TempScreenBufferPtr += 0xC5C0;
    GbPakDevice->tileAssets = DataStruct_TileAssets;
    Ptr_TempScreenBuffer = 0;

    for (i = 0; i < 2; i++) {
        GbPakThreadData[i].unk_20 = 2;
        GbPakThreadData[i].unk_24 = 0;
        DrawFullScreenBackground((u16*)(&gGbScreenFb0)[i]->img_p, arg5, arg1, 0);
        gImageDataPtrs[i] = gCurrentFramebufferPtr;
    }

    GbAudio_Init();
    Dma_WriteChunks((u32)(TempScreenBufferPtr + 0x80000), (u32)fragment1_misc_yay0_ROM_START, ((u32)D_F4130 + 1) & ~1, 0);
    Yay0_Decompress((void*)((u32)TempScreenBufferPtr + 0x80000), TempScreenBufferPtr);
    GbApu_Reset((TileAssetFragment*)TempScreenBufferPtr);
    GbAudio_SetAlternateRendererEnabled(0);
    GbApu_SelectRegionClock(0);
    GbAudio_Reset();
    GbAudio_QueueWrite(0xFF26, 0, 0);
    GbAudio_QueueWrite(0xFF26, 0x8F, 0x10);
    GbAudio_QueueWrite(0xFF24, 0x77, 0x20);
    GbAudio_QueueWrite(0xFF25, 0xFF, 0x30);
    func_81208F94();
    TempScreenBufferPtr += 0x80000;

    gPrevDataSetIndex = gGbEmuPresentationMode;
    gAudioInitialized = 0;
    if (gGbEmuPresentationMode == 2) {
        gDataSetLoadResult = 2;
    } else {
        gDataSetLoadResult = 1;
    }

    for (i = 0; i < 3; i++) {
        ((u8**)TileAssetFragments)[i] = TempScreenBufferPtr;
        TempScreenBufferPtr += 0xE200;
        bzero(TempScreenBufferPtr, 0x2800);
        ((u8**)FramebufferImages)[i] = TempScreenBufferPtr;
        TempScreenBufferPtr += 0x2800;
    }

    switch (gGbEmuPresentationMode) {
        case 2:
            Dma_WriteChunks((u32)TileAssetFragments[0], (u32)D_FDE40, ((u32)D_102BA0_END + 1) & ~1, 0);
            Yay0_Decompress(TileAssetFragments[0], TileAssetFragments[2]);
            /* fallthrough */
        case 1:
            Dma_WriteChunks((u32)TileAssetFragments[0], (u32)D_F5450, ((u32)D_FDE40 + 1) & ~1, 0);
            Yay0_Decompress(TileAssetFragments[0], TileAssetFragments[1]);
            break;
        case 0:
        default:
            Dma_WriteChunks((u32)TileAssetFragments[0], (u32)D_F4920, ((u32)D_F5450 + 1) & ~1, 0);
            Yay0_Decompress(TileAssetFragments[0], TileAssetFragments[1]);
            break;
    }

    while ((TempScreenBufferPtr - (u8*)TileAssetPtr) != 0x1FEAE8) {}

    osWritebackDCacheAll();

    emu = GbPakDevice;
    if (emu->unk_5DCA != 0) {
        while (emu->unk_5DC8 != 0) {}
        for (i = ((emu->headerMatchIndex != 0) ? 0x500 : 0) / 256; i < 0x80; i++) {
            emu->blockWriteMask[i] = 0;
        }
        if (emu->unk_5DCA == 0) {
            gGbEmuRunState = 1;
            UnknownFlag = 1;
            GbEmu_ClearFramebuffers();
            return;
        }
        GbPakStateByte = 0xFF;
        DrawStadiumScreen(0, 1);
        DrawStadiumScreen(1, 1);
        DrawStadiumUI();
        if ((emu->headerMatchIndex == 0) || (emu->headerMatchIndex == 2)) {
            gGbEmuRunState = 1;
            UnknownFlag = 1;
            GbEmu_ClearFramebuffers();
            return;
        }
        gGbEmuRunState = 5;
        DrawFullScreenBackground((u16*)gGbScreenFb0->img_p, arg5, arg1, (emu->headerMatchIndex != 0) ? emu->headerMatchIndex - 1 : 0);
        DrawFullScreenBackground((u16*)gGbScreenFb1->img_p, arg5, arg1, (emu->headerMatchIndex != 0) ? emu->headerMatchIndex - 1 : 0);
    }

    gStadiumTimer = osGetCount();
    gStadiumInterval = gStadiumTimer;
    osViSwapBuffer((&gGbScreenFb0)[gGbPakTaskBufferIndex]->img_p);
    gGbPakTaskBufferIndex ^= 1;
}
void LoadCompressedBank(GbPakDeviceState* arg0) {
    u16* list;
    s32 i;
    s32 count;
    s32 bank;
    u32 rom;
    s32 j;
    u8* src;
    u8* dst;

    // FAKE
    if ((u16*) arg0->gameVariantData[2]) {}

    list = (u16*) arg0->gameVariantData[2];
    if (list != 0) {
        rom = arg0->gameVariantData[3] + 0x7C0000;
        do {
            bank = *list & 0xFF;
            count = *list / 256;
            Dma_WriteChunks((u32) arg0->romImage + 0xEC000, rom, list[1] + rom, 0);
            rom += list[1];
            list += 2;
            Yay0_Decompress((void*) ((u32) arg0->romImage + 0xEC000), (void*) ((u32) arg0->romImage + (bank << 14)));
            for (i = 0; i < count; i++) {
                if (i + 1 >= arg0->unk_5DC6) {
                    Dma_WriteChunks((u32) arg0->romImage + 0xF0000, rom, *list + rom, 0);
                    Yay0_Decompress((void*) ((u32) arg0->romImage + 0xF0000), (void*) ((u32) arg0->romImage + 0xEC000));
                    src = (u8*) ((u32) arg0->romImage + 0xEC000);
                    dst = (u8*) ((u32) arg0->romImage + (bank << 14));
                    for (j = 0; j < 0x1000; j++) {
                        dst[j] ^= src[j];
                    }
                }
                rom += *list++;
            }
            arg0->unk_549C[bank] = 0xFF;
        } while (*list);
    }
}

void GbEmu_ApplyButtonMapping(void) {
  if ((gGbEmuButtonBindingSelections.TrainerSlotSaveData_GamePort == gGbEmuButtonBindingSelections.posX) || (gGbEmuButtonBindingSelections.posX >= 5) || (gGbEmuButtonBindingSelections.TrainerSlotSaveData_GamePort >= 5)) {
      gGbEmuButtonBindingSelections.posX = 0;
      gGbEmuButtonBindingSelections.TrainerSlotSaveData_GamePort = 1;
  }

  gGbEmuBoundButtonMask0 = (gGbEmuButtonBindingSelections.posX == 1) ?   0x20 : (gGbEmuButtonBindingSelections.posX == 2) ? 0x10 : (gGbEmuButtonBindingSelections.posX == 3) ? 2 : (gGbEmuButtonBindingSelections.posX == 4) ? 4 : 0x1000;
  gGbEmuBoundButtonMask1 = (gGbEmuButtonBindingSelections.TrainerSlotSaveData_GamePort == 0) ? 0x1000 : (gGbEmuButtonBindingSelections.TrainerSlotSaveData_GamePort == 2) ? 0x10 : (gGbEmuButtonBindingSelections.TrainerSlotSaveData_GamePort == 3) ? 2 : (gGbEmuButtonBindingSelections.TrainerSlotSaveData_GamePort == 4) ? 4 : 0x20;
}

void AudioStateMachine(GbPakDeviceState* arg0) {
    u8 var_v0;
    u8 var_v0_2;

    switch (arg0->unk_5DC9) {
        case 8:
            gGbEmuMenuState = 0x12;
            goto block_9;
        case 9:
            gGbEmuMenuState = 0x13;
            goto block_9;
        case 10:
            gGbEmuMenuState = 0x14;
            goto block_9;
        case 11:
            gGbEmuMenuState = 0x15;
        block_9:
            GbAudio_SetAlternateRendererEnabled(1);
            GbAudio_SetAlternateStreamId(1);

            gGbEmuButtonBindingSelections.posX = (gGbEmuBoundButtonMask0 == 0x20)   ? 1
                                : (gGbEmuBoundButtonMask0 == 0x10) ? 2
                                : (gGbEmuBoundButtonMask0 == 2)    ? 3
                                : (gGbEmuBoundButtonMask0 == 4)    ? 4
                                                       : 0;
            gGbEmuButtonBindingSelections.TrainerSlotSaveData_GamePort = (gGbEmuBoundButtonMask0 == 0x1000) ? 0
                                : (gGbEmuBoundButtonMask0 == 0x10) ? 2
                                : (gGbEmuBoundButtonMask0 == 2)    ? 3
                                : (gGbEmuBoundButtonMask0 == 4)    ? 4
                                                       : 1;

            if (gGbEmuButtonBindingSelections.TrainerSlotSaveData_GamePort == gGbEmuButtonBindingSelections.posX) {
                gGbEmuButtonBindingSelections.posX = 0;
                gGbEmuButtonBindingSelections.TrainerSlotSaveData_GamePort = 1;
            }
            return;
        default:
            if ((gGbEmuMenuState == 0x12) || (gGbEmuMenuState == 0x13) || (gGbEmuMenuState == 0x14) || (gGbEmuMenuState == 0x15)) {
                GbAudio_SetAlternateStreamId(1);
                GbAudio_SetAlternateRendererEnabled(0);
                gGbEmuMenuState = 0;
                return;
            }
            if (gGbEmuMenuState == 0) {
                if ((gPlayer1Controller->buttonPressed & 8) && (arg0->inputCooldown == 0) && (Msg_FadeCounter == 0x40)) {
                    arg0->unk_53FD = 0x40;
                    GbAudio_SetAlternateRendererEnabled(1);
                    GbAudio_SetAlternateStreamId(1);
                    gGbEmuMenuState = 1;
                }
                return;
            }
            {
                ((GbPakThreadContext*) gGbPakMessageQueue)[gGbPakTaskBufferIndex].mesg[0] = NULL;
                switch (gGbEmuMenuState) {
                    case 1:
                        arg0->unk_53FD -= 4;
                        if (arg0->unk_53FD <= 0) {
                            arg0->unk_53FD = 0;
                            if (gPlayer1Controller->buttonPressed & 0xD000) {
                            set_11:
                                gGbEmuMenuState = 0x11;
                                return;
                            }
                            if (gPlayer1Controller->buttonPressed & 0x800) {
                            set_3:
                                GbAudio_SetAlternateStreamId(7);
                                gGbEmuMenuState = 3;
                                return;
                            }
                            if (gPlayer1Controller->buttonPressed & 0x400) {
                            set_2:
                                GbAudio_SetAlternateStreamId(7);
                                gGbEmuMenuState = 2;
                                return;
                            }
                        }
                        break;
                    case 17:
                        if (gPlayer1Controller->buttonDown == 0) {
                            GbEmu_ApplyButtonMapping();
                            arg0->unk_53FD = 0x40;
                            GbAudio_SetAlternateStreamId(1);
                            GbAudio_SetAlternateRendererEnabled(0);
                            gGbEmuMenuState = 0;
                        }
                        break;
                    case 2:
                        if (gPlayer1Controller->buttonPressed & 0x800) {
                        set_1:
                            GbAudio_SetAlternateStreamId(7);
                            gGbEmuMenuState = 1;
                            return;
                        }
                        if (gPlayer1Controller->buttonPressed & 0x400) {
                            goto set_3;
                        }
                        if (gPlayer1Controller->buttonPressed & 0x9000) {
                            GbAudio_SetAlternateStreamId(2);
                            gGbEmuMenuState = 4;
                            return;
                        }
                        if (gPlayer1Controller->buttonPressed & 0x4000) {
                            goto set_11;
                        }
                        break;
                    case 3:
                        if (gPlayer1Controller->buttonPressed & 0x800) {
                            goto set_2;
                        }
                        if (gPlayer1Controller->buttonPressed & 0x400) {
                            goto set_1;
                        }
                        if (gPlayer1Controller->buttonPressed & 0x9000) {
                            GbAudio_SetAlternateStreamId(6);
                            gGbEmuMenuState = 6;
                            return;
                        }
                        if (gPlayer1Controller->buttonPressed & 0x4000) {
                            goto set_11;
                        }
                        break;
                    case 4:
                    case 5:
                        if (gPlayer1Controller->buttonPressed & 0x4000) {
                            GbAudio_SetAlternateStreamId(8);
                            gGbEmuMenuState = 2;
                            return;
                        }
                        if (gPlayer1Controller->buttonPressed & 0x300) {
                            GbAudio_SetAlternateStreamId(5);
                            gGbEmuMenuState = gGbEmuMenuState == 4 ? 5 : 4;
                            return;
                        }
                        if (gPlayer1Controller->buttonPressed & 0x9000) {
                            if (gGbEmuMenuState == 4) {
                                gGbEmuMenuState = 0xF;
                                return;
                            }
                            gGbEmuMenuState = 1;
                            return;
                        }
                        break;
                    case 6:
                        switch (gPlayer1Controller->buttonPressed) {
                            case 0x4000:
                            back_to_3:
                                GbAudio_SetAlternateStreamId(8);
                                gGbEmuMenuState = 3;
                                return;
                            case 0x8000:
                                GbAudio_SetAlternateStreamId(6);
                                gEmuSavedBindingSelection = (s32) gGbEmuButtonBindingSelections.posX;
                                gMenuAnimCounter = 0;
                                gGbEmuMenuState = 7;
                                return;
                            case 0x1000:
                                var_v0 = 0;
                                goto block_96;
                            case 0x20:
                                var_v0 = 1;
                                goto block_96;
                            case 0x10:
                                var_v0 = 2;
                                goto block_96;
                            case 0x2:
                                var_v0 = 3;
                                goto block_96;
                            case 0x4:
                                var_v0 = 4;
                            block_96:
                                if (gGbEmuButtonBindingSelections.TrainerSlotSaveData_GamePort == var_v0) {
                                    GbAudio_SetAlternateStreamId(3);
                                    return;
                                }
                                gGbEmuButtonBindingSelections.posX = var_v0;
                                GbAudio_SetAlternateStreamId(6);
                                if (gGbEmuMenuState == 8) {
                                    gGbEmuMenuState = 9;
                                    return;
                                }
                                break;
                            case 0x400:
                            case 0x800:
                                GbAudio_SetAlternateStreamId(7);
                                gGbEmuMenuState = 0xA;
                                return;
                        }
                        break;
                    case 10:
                        switch (gPlayer1Controller->buttonPressed) {
                            case 0x4000:
                                goto back_to_3;
                            case 0x8000:
                                GbAudio_SetAlternateStreamId(6);
                                gMenuAnimCounter = 0;
                                gEmuSavedBindingSelection = (s32) gGbEmuButtonBindingSelections.TrainerSlotSaveData_GamePort;
                                gGbEmuMenuState = 0xB;
                                return;
                            case 0x1000:
                                var_v0_2 = 0;
                                goto block_119;
                            case 0x20:
                                var_v0_2 = 1;
                                goto block_119;
                            case 0x10:
                                var_v0_2 = 2;
                                goto block_119;
                            case 0x2:
                                var_v0_2 = 3;
                                goto block_119;
                            case 0x4:
                                var_v0_2 = 4;
                            block_119:
                                if (gGbEmuButtonBindingSelections.posX == var_v0_2) {
                                    GbAudio_SetAlternateStreamId(3);
                                    return;
                                }
                                gGbEmuButtonBindingSelections.TrainerSlotSaveData_GamePort = var_v0_2;
                                GbAudio_SetAlternateStreamId(6);
                                if (gGbEmuMenuState == 0xC) {
                                    gGbEmuMenuState = 0xD;
                                    return;
                                }
                                break;
                            case 0x400:
                            case 0x800:
                                GbAudio_SetAlternateStreamId(7);
                                gGbEmuMenuState = 6;
                                return;
                        }
                        break;
                    case 7:
                    case 11:
                        if ((s32) gMenuAnimCounter < 0xA) {
                            gMenuAnimCounter += 1;
                            return;
                        }
                        if (gGbEmuMenuState == 7) {
                            gGbEmuMenuState = 8;
                            return;
                        }
                        gGbEmuMenuState = 0xC;
                        return;
                    case 8:
                        switch (gPlayer1Controller->buttonPressed) {
                            case 0x4000:
                                GbAudio_SetAlternateStreamId(8);
                                gGbEmuButtonBindingSelections.posX = gEmuSavedBindingSelection;
                                gGbEmuMenuState = 9;
                                return;
                            case 0x8000:
                                if (gGbEmuButtonBindingSelections.posX == gGbEmuButtonBindingSelections.TrainerSlotSaveData_GamePort) {
                                    GbAudio_SetAlternateStreamId(3);
                                } else {
                                    GbAudio_SetAlternateStreamId(6);
                                    gGbEmuMenuState = 9;
                                }
                                return;
                            case 0x200:
                                gGbEmuButtonBindingSelections.posX--;
                                if ((gGbEmuButtonBindingSelections.posX < 0) || (gGbEmuButtonBindingSelections.posX >= 5)) {
                                    gGbEmuButtonBindingSelections.posX = 0U;
                                }
                                GbAudio_SetAlternateStreamId(5);
                                return;
                            case 0x100:
                                gGbEmuButtonBindingSelections.posX++;
                                if (gGbEmuButtonBindingSelections.posX >= 5) {
                                    gGbEmuButtonBindingSelections.posX = 4U;
                                }
                                GbAudio_SetAlternateStreamId(5);
                                return;
                            case 0x1000:
                                var_v0 = 0;
                                goto block_96;
                            case 0x20:
                                var_v0 = 1;
                                goto block_96;
                            case 0x10:
                                var_v0 = 2;
                                goto block_96;
                            case 0x2:
                                var_v0 = 3;
                                goto block_96;
                            case 0x4:
                                var_v0 = 4;
                                goto block_96;
                        }
                        break;
                    case 12:
                        switch (gPlayer1Controller->buttonPressed) {
                            case 0x4000:
                                GbAudio_SetAlternateStreamId(8);
                                gGbEmuButtonBindingSelections.TrainerSlotSaveData_GamePort = gEmuSavedBindingSelection;
                                gGbEmuMenuState = 0xD;
                                return;
                            case 0x8000:
                                if (gGbEmuButtonBindingSelections.posX == gGbEmuButtonBindingSelections.TrainerSlotSaveData_GamePort) {
                                    GbAudio_SetAlternateStreamId(3);
                                } else {
                                    GbAudio_SetAlternateStreamId(6);
                                    gGbEmuMenuState = 0xD;
                                }
                                return;
                            case 0x200:
                                gGbEmuButtonBindingSelections.TrainerSlotSaveData_GamePort--;
                                if ((gGbEmuButtonBindingSelections.TrainerSlotSaveData_GamePort < 0) || (gGbEmuButtonBindingSelections.TrainerSlotSaveData_GamePort >= 5)) {
                                    gGbEmuButtonBindingSelections.TrainerSlotSaveData_GamePort = 0U;
                                }
                                GbAudio_SetAlternateStreamId(5);
                                return;
                            case 0x100:
                                gGbEmuButtonBindingSelections.TrainerSlotSaveData_GamePort++;
                                if (gGbEmuButtonBindingSelections.TrainerSlotSaveData_GamePort >= 5) {
                                    gGbEmuButtonBindingSelections.TrainerSlotSaveData_GamePort = 4U;
                                }
                                GbAudio_SetAlternateStreamId(5);
                                return;
                            case 0x1000:
                                var_v0_2 = 0;
                                goto block_119;
                            case 0x20:
                                var_v0_2 = 1;
                                goto block_119;
                            case 0x10:
                                var_v0_2 = 2;
                                goto block_119;
                            case 0x2:
                                var_v0_2 = 3;
                                goto block_119;
                            case 0x4:
                                var_v0_2 = 4;
                                goto block_119;
                        }
                        break;
                    case 9:
                    case 13:
                        if (gMenuAnimCounter != 0) {
                            gMenuAnimCounter -= 1;
                            return;
                        }
                        if (gGbEmuMenuState == 9) {
                            gGbEmuMenuState = 6;
                            return;
                        }
                        gGbEmuMenuState = 0xA;
                        return;
                    case 14:
                        if (gPlayer1Controller->buttonDown == 0) {
                            GbEmu_ApplyButtonMapping();
                            gGbEmuMenuState = 0xF;
                        }
                        break;
                    case 15:
                        Msg_FadeCounter -= 4;
                        if (Msg_FadeCounter > 0) {
                            return;
                        }
                        Msg_FadeCounter = 0;
                        gGbEmuMenuState = 0x10;
                        /* fallthrough */
                    case 16:
                        GbAudio_SetAlternateStreamId(1);
                        GbAudio_SetAlternateRendererEnabled(0);
                        GbAudio_Reset();
                        break;
                }
            }
            break;
    }
}

void GbPak_DrawMenu(s32 arg0) {
    s32 pad;
    s32 j;
    s32 i;
    s32 c1;
    s32 c2 = 0;
    s32 c3;
    s32 y;
    s32 x;
    u16* volatile fb;
    u16* base;
    s32 row;
    u16* p;

    if (gGbEmuMenuState == 0) {
        return;
    }

    fb = (u16*)arg0;
    base = (u16*)arg0 - 14;

    switch (gGbEmuMenuState) {
        case 0x12:
        case 0x13:
            Gfx_DrawTileMap(base, gText_UnableToSave);
            goto transition;
        case 0x14:
            gCurrentBufferIndex ^= 1;
            gMarkerAnimFrame++;
            if (gMarkerAnimFrame >= 11) {
                gMarkerAnimFrame = 0;
            }
            goto transition;
        case 0x15:
            Gfx_DrawTileMap(base, gText_GBGamePakInfo);
        transition:
            DrawVerticalMarker((u16*)((u8*)FramebufferImages[gCurrentBufferIndex] + 0x9C), 1, gMarkerAnimFrame);
            GbPakThreadData[gGbPakTaskBufferIndex].unk_3C = 0x1010;
            GbPakThreadData[gGbPakTaskBufferIndex].unk_38 = (s32)FramebufferImages[gCurrentBufferIndex];
            GbPakThreadData[gGbPakTaskBufferIndex].unk_5C &= 0xFFFF;
            Gfx_DrawTileMap(base, gText_LeavingN64);
            return;

        default:
            switch (gGbEmuMenuState) {
        case 1:
        case 17:
            base = fb + 0x3C3E;
            GbEmu_BlitWithPixelOp(base + 0x1B8A, (u16*)(DataStruct_TileAssets + 0xC2F8), 0, 16, 10);
            c1 = 0xB;
            c2 = 8;
            c3 = 8;
            goto draw_items;
        case 4:
        case 5:
            c1 = 8;
            c2 = 0xB;
            c3 = 8;
            base = fb + 0x3C3E;
            goto draw_items;
        case 2:
            base = fb + 0x3C3E;
            GbEmu_BlitWithPixelOp(base + 0x348A, (u16*)(DataStruct_TileAssets + 0xC2F8), 0, 16, 10);
            c1 = 8;
            c2 = 0xB;
            c3 = 8;
            goto draw_items;
        case 3:
            base = fb + 0x3C3E;
            GbEmu_BlitWithPixelOp(base + 0x4D8A, (u16*)(DataStruct_TileAssets + 0xC2F8), 0, 16, 10);
            c1 = 8;
            c2 = 8;
            c3 = 0xB;
        draw_items:
            Gfx_DrawTileMap(base, gText_MenuTitle);
            gText_ContinueGame[4] = c1;
            Gfx_DrawTileMap(base, gText_ContinueGame);
            gText_QuitGame[4] = c2;
            Gfx_DrawTileMap(base, gText_QuitGame);
            gText_HelpConfig[4] = c3;
            Gfx_DrawTileMap(base, gText_HelpConfig);
            for (i = 8; i < 0x94; i++) {
                base[80 * 320 + i] = 0xFFFF;
            }
            break;
            }
            break;
    }

    switch (gGbEmuMenuState) {
        case 1:
        case 17:
            Gfx_DrawTileMap(fb + 0x3C3E, gText_ExitMenuPrompt);
            break;
        case 2:
            Gfx_DrawTileMap(fb + 0x3C3E, gText_QuitGameBoyPrompt);
            break;
        case 3:
            Gfx_DrawTileMap(fb + 0x3C3E, gText_StartSelectInfo);
            break;
        case 4:
            GbEmu_BlitWithPixelOp(fb + 0xDC48, (u16*)(DataStruct_TileAssets + 0xC2F8), 0, 16, 10);
            /* fallthrough */
        case 14:
            c1 = 0xB;
            c2 = 8;
            base = fb + 0x3C3E;
            goto draw_submenu;
        case 5:
            base = fb + 0x3C3E;
            GbEmu_BlitWithPixelOp(base + 0xA050, (u16*)(DataStruct_TileAssets + 0xC2F8), 0, 16, 10);
            c1 = 8;
            c2 = 0xB;
        draw_submenu:
            Gfx_DrawTileMap(base, gText_GameSavedPrompt);
            gText_Yes[4] = c1;
            gText_No[0] = c2;
            Gfx_DrawTileMap(base, gText_Yes);
            Gfx_DrawTileMap(base, gText_Empty);
            break;
    }

    switch (gGbEmuMenuState) {
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
        case 11:
        case 12:
        case 13:
            base = fb + 0x3C3E;
            y = 0x4A;
            if (gGbEmuPresentationMode == 1) {
                GbEmu_BlitWithPixelOp(base + 0x784, (u16*)(DataStruct_TileAssets + 0xB758), 0, 16, 12);
                Gfx_DrawTileMap(base, gText_ButtonDoubleSpeed);
            } else if (gGbEmuPresentationMode == 2) {
                GbEmu_BlitWithPixelOp(base + 0x784, (u16*)(DataStruct_TileAssets + 0xB758), 0, 16, 12);
                Gfx_DrawTileMap(base, gText_EachPressPokemon);
            } else {
                y = 0x32;
            }
            for (j = 1; j < 0x3F; j++) {
                base[(y + j) * 320 + 1] = base[(y + j) * 320 + 2] = base[(y + j) * 320 + 0x9D] =
                    base[(y + j) * 320 + 0x9E] = 0xFFFF;
            }
            for (i = 2; i < 0x9E; i++) {
                if ((i < 0x10) || (i >= 0x43)) {
                    base[y * 320 + i] = base[(y + 1) * 320 + i] = 0xFFFF;
                }
                base[(y + 62) * 320 + i] = base[(y + 63) * 320 + i] = 0xFFFF;
            }
            gText_Config[2] = y - 5;
            Gfx_DrawTileMap(base, gText_Config);
            GbEmu_BlitWithPixelOp(y * 320 + base + 0x3C1C, (u16*)(DataStruct_TileAssets + 0xB2D8), 0, 16, 12);
            gText_ButtonCancel[2] = y + 0x30;
            Gfx_DrawTileMap(base, gText_ButtonCancel);
            break;
    }

    x = 0x28 - gMenuAnimCounter * 4;
    switch (gGbEmuMenuState) {
        case 7:
        case 8:
        case 9:
            i = 0;
            row = y * 320;
            base = fb + 0x3C3E;
            goto draw_second;
        case 11:
        case 12:
        case 13:
            i = 0;
            row = y * 320;
            base = fb + 0x3C3E;
            goto draw_first;
        case 6:
            i = 0;
            row = y * 320;
            base = fb + 0x3C3E;
            goto draw_cursor;
        case 10:
            i = 0x14;
            row = y * 320;
            base = fb + 0x3C3E;
        draw_cursor:
            GbEmu_BlitWithPixelOp((y + i) * 320 + base + 0xF14, (u16*)(DataStruct_TileAssets + 0xC2F8), 0, 16, 10);
            x = 0x28;
            i = 1;
        draw_first:
            switch (gGbEmuButtonBindingSelections.posX) {
                case 0:
                default:
                    j = 0xBBD8;
                    break;
                case 1:
                    j = 0xB8D8;
                    break;
                case 2:
                    j = 0xBA58;
                    break;
                case 3:
                    j = 0xB5D8;
                    break;
                case 4:
                    j = 0xB458;
                    break;
            }
            GbEmu_BlitWithPixelOp((((i == 0) ? 0x28 : x) + row) + base + 0xCBC, (u16*)(DataStruct_TileAssets + j), 0, 16, 12);
            if (i == 0) {
                break;
            }
        draw_second:
            switch (gGbEmuButtonBindingSelections.TrainerSlotSaveData_GamePort) {
                case 0:
                    j = 0xBBD8;
                    break;
                case 1:
                default:
                    j = 0xB8D8;
                    break;
                case 2:
                    j = 0xBA58;
                    break;
                case 3:
                    j = 0xB5D8;
                    break;
                case 4:
                    j = 0xB458;
                    break;
            }
            GbEmu_BlitWithPixelOp((((i == 0) ? 0x28 : x) + row) + base + 0x25BC, (u16*)(DataStruct_TileAssets + j), 0, 16, 12);
            break; } switch (gGbEmuMenuState) { case 6: case 7: case 8: case 9: i = x + 8; row = y * 320; j = 0x30; base = fb + 0x3C3E; goto draw_arrows; case 10: case 11: case 12: case 13: i = 0x30; row = y * 320; j = x + 8; base = fb + 0x3C3E; draw_arrows: p = (row + i) + base; // single line needed to match
            GbEmu_BlitWithPixelOp(p + 0xC80, (u16*)(DataStruct_TileAssets + 0xBF98), 0, 24, 12);
            GbEmu_BlitWithPixelOp(p + 0xC98, (u16*)(DataStruct_TileAssets + 0xC438), 0, 16, 12);
            p = (row + j) + base;
            GbEmu_BlitWithPixelOp(p + 0x257E, (u16*)(DataStruct_TileAssets + 0xBD58), 0, 24, 12);
            GbEmu_BlitWithPixelOp(p + 0x2598, (u16*)(DataStruct_TileAssets + 0xC438), 0, 16, 12);
            break;
    }

    switch (gGbEmuMenuState) {
        case 8:
            j = gGbEmuButtonBindingSelections.posX;
            i = 0;
            base = fb + 0x3C3E;
            break;
        case 12:
            i = 0x14;
            j = gGbEmuButtonBindingSelections.TrainerSlotSaveData_GamePort;
            base = fb + 0x3C3E;
            break;
        default:
            return;
    }
    row = y + i;
    p = row * 320 + base;
    GbEmu_BlitWithPixelOp(p + 0xCBA, (u16*)(DataStruct_TileAssets + 0xBBD8), 0, 16, 12);
    GbEmu_BlitWithPixelOp(p + 0xCCC, (u16*)(DataStruct_TileAssets + 0xB8D8), 0, 16, 12);
    GbEmu_BlitWithPixelOp(p + 0xCDE, (u16*)(DataStruct_TileAssets + 0xBA58), 0, 16, 12);
    GbEmu_BlitWithPixelOp(p + 0xCF0, (u16*)(DataStruct_TileAssets + 0xB5D8), 0, 16, 12);
    GbEmu_BlitWithPixelOp(p + 0xD02, (u16*)(DataStruct_TileAssets + 0xB458), 0, 16, 12);
    row += 7;
    x = j * 0x12 + 0x37;
    for (j = 1; j < 0x11; j++) {
        base[(row + j) * 320 + x] = base[(row + j) * 320 + x + 1] = base[(row + j) * 320 + x + 0x10] =
            base[(row + j) * 320 + x + 0x11] = 0xE71C;
    }
    for (i = 1; i < 0x10; i++) {
        base[row * 320 + x + i] = base[(row + 1) * 320 + x + i] = base[(row + 16) * 320 + x + i] =
            base[(row + 17) * 320 + x + i] = 0xE71C;
    }
}

extern u8 gPendingDataSetIndex;
extern u8 gGbBankLoadedFlag;
extern u8 gGbScreenRefreshCounter;
extern s32 gAudioBufferPtr;
extern u8 D_812297C0[];
extern u8 D_8122A1A4[];
extern u8 D_8122A260[];
extern u8 D_8122ACA0[];
extern u8 gGbCartVerifyList_Red[];
extern u8 gGbCartVerifyList_Blue[];
extern u8 gGbCartVerifyList_Yellow[];
extern u8 gGbCompressedBankList_RedBlue[];
extern u8 gGbCompressedBankList_Yellow[];
extern s32 gGbCartTypeTable[];
extern s32 gPowerOfTwoTable[8];
extern s32 gGbRamSizeTable[16];

extern u8 gFragments[];
extern u8 gRdpOutputBuffer[];

u8 gStadiumUIMap[234] = { 0xF0, 0xF0, 0xFC, 0xFC, 0xFC, 0xFC, 0xF3, 0xF3, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0xF0, 0xF0, 0xF0, 0xF0, 0, 0, 0xF3, 0xF3, 0, 0, 0, 0, 0, 0, 0xCF, 0xCF, 0, 0, 0xF, 0xF, 0x3F, 0x3F, 0xF, 0xF, 0, 0, 0, 0, 0xC0, 0xC0, 0xF, 0xF, 0, 0, 0, 0, 0, 0, 0xF0, 0xF0, 0, 0, 0, 0, 0, 0, 0xF3, 0xF3, 0, 0, 0, 0, 0, 0, 0xC0, 0xC0, 3, 3, 3, 3, 3, 3, 0xFF, 0xFF, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC3, 0xC3, 0, 0, 0, 0, 0, 0, 0xFC, 0xFC, 0xF3, 0xF3, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0x3C, 0x3C, 0xFC, 0xFC, 0xFC, 0xFC, 0x3C, 0x3C, 0xF3, 0xF3, 0xF3, 0xF3, 0xF3, 0xF3, 0xF3, 0xF3, 0xF3, 0xF3, 0xC3, 0xC3, 0xC3, 0xC3, 0xC3, 0xC3, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0x3C, 0x3C, 0x3F, 0x3F, 0x3C, 0x3C, 0xF, 0xF, 0x3C, 0x3C, 0xFC, 0xFC, 0, 0, 0xFC, 0xFC, 0xFC, 0xFC, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF3, 0xF3, 0xF3, 0xF3, 0xF3, 0xF3, 0xF0, 0xF0, 0xC3, 0xC3, 0xC3, 0xC3, 0xC3, 0xC3, 0xFF, 0xFF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0xC3, 0xC3, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xFC, 0xFC, 0x3C, 0x42, 0xB9, 0xA5, 0xB9, 0xA5, 0x42, 0x3C, 0x91, 0x8F, 0x8D, 0xD1, 0xC4, 0xBA, 0xCE, 0x75, 0xB8, 0xC4, 0xB0, 0xB2, 0xB7, 0x99, 0x67, 0x73, 0xAA, 0xAF, 0xA8, 0xA1, 0x9C, 0xA8, 0x83, 0xB6, 0xAE, 0xA4, 0x8B, 0x77, 0xAA, 0xAA, 0xAE, 0xAD, 0xAD, 0x79 };  // tail holds D_8120D8FD, D_8120D8FE, D_8120D906 (linker-defined symbols)
s32 gGbCartTypeTable[256] = { 1, 16, 18, 22, 0, 32, 36, 0, 2, 6, 0, 0, 0, 0, 0, 76, 78, 64, 66, 70, 0, 0, 0, 0, 0, 256, 0, 262, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 32768, 0, 0, 4096 };
s32 gPowerOfTwoTable[8] = { 32768, 65536, 131072, 262144, 524288, 1048576, 2097152, 4194304 };
s32 gGbRamSizeTable[16] = { 0, 2048, 8192, 32768, 131072, 1347373893, 1297042976, 1380271104, 0, 1347373893, 1297042976, 1196574021, 1308688383, 1347373893, 1297042976, 1112298821 };
static u32 pad_D_8120DD2C[1] = { 0 };
u8 gGameTitle_PokemonYellow[16] = { 0x50, 0x4F, 0x4B, 0x45, 0x4D, 0x4F, 0x4E, 0x20, 0x59, 0x45, 0x4C, 0x4C, 0x4F, 0x57, 0, 0x80 };
u8 gGbCartVerifyList_Red[396] = { 0, 0, 0xD3, 0x9A, 2, 0x47, 0x80, 0, 0x80, 1, 0x80, 2, 0x80, 3, 0, 1, 0x56, 0xC0, 0xA3, 0xD6, 0, 2, 0x19, 0x1C, 0x43, 0xC1, 0, 0x13, 0x90, 0x64, 0xE4, 0xD6, 0, 0x1C, 0x71, 0xBB, 0xCF, 0x58, 0, 4, 0xBD, 0x4D, 5, 0xF0, 0, 6, 0xC1, 0x61, 0xC1, 0, 0, 0x10, 0x8D, 0x71, 0xFA, 0xAE, 0, 0x1F, 0x51, 0xC5, 0x72, 0x55, 0, 0x1E, 0xB4, 0x12, 0x61, 0xCC, 0, 3, 0xFD, 0xAD, 0xAA, 0xC, 0, 0x1A, 0x54, 0x38, 0xC, 0xF3, 0, 0xE, 0x99, 0x20, 0x97, 0x73, 0, 0xD, 0xB, 0x4E, 0x96, 0x3E, 0, 0xF, 0xDD, 0x43, 0xE1, 9, 0, 5, 0x7F, 0x3A, 8, 0x34, 0, 7, 0xE, 0x32, 1, 0x14, 0, 0x15, 0xE7, 0x68, 0x19, 0x98, 0, 0x19, 0x2C, 0x1F, 0x21, 0xE8, 0, 0x1D, 0xF, 0x3A, 0x7C, 0x20, 0, 0x22, 0x90, 0x69, 0xB5, 0x2E, 0, 0xB, 0x65, 0x81, 0xEF, 0xA0, 0, 0x25, 0x13, 0x11, 0x23, 2, 0, 0x11, 0x46, 0x87, 7, 0x1F, 0, 0x14, 0xC4, 0x80, 0xBF, 0x59, 0, 0x17, 0x42, 0x32, 0, 0, 0, 0x12, 0xAD, 0x8D, 0xC7, 0x56, 0, 8, 0x5A, 0x42, 0x6B, 0xF0, 0, 9, 0x95, 6, 0xF4, 0x8B, 0, 0xA, 0x9D, 0x35, 0x8D, 0x38, 0, 0xC, 0x35, 0xB9, 0xCC, 0x9E, 0, 0x16, 0x84, 0x33, 7, 0xED, 0, 0x18, 0xDB, 0x64, 0xB8, 0x77, 0, 0x1B, 0x30, 0x82, 0xC5, 0x60, 0, 0x20, 0x3A, 9, 0x65, 4, 0, 0x21, 0x43, 0x7E, 0xB1, 0x41, 0, 0x23, 0x38, 0x21, 0x3B, 0x7F, 0, 0x24, 8, 0xD6, 0x6C, 0xA4, 0, 0x26, 0x6F, 0xCF, 0, 0xAC, 0, 0x27, 0x32, 0x6C, 0x67, 0xF3, 0, 0x28, 0x54, 0x1C, 0xB, 0xC6, 0, 0x29, 0xFB, 0x98, 0xB6, 0xF1, 0, 0x2A, 0xC2, 0x23, 0, 0, 0, 0x2B, 0xAC, 0x93, 0xE9, 0xAE, 0, 0x2C, 0x1F, 0x51, 0, 0, 0, 0x2D, 0, 0, 0, 0, 0, 0x2E, 0, 0, 0, 0, 0, 0x2F, 0, 0, 0, 0, 0, 0x30, 0, 0, 0, 0, 0, 0x31, 0, 0, 0, 0, 0, 0x32, 0, 0, 0, 0, 0, 0x33, 0, 0, 0, 0, 0, 0x34, 0, 0, 0, 0, 0, 0x35, 0, 0, 0, 0, 0, 0x36, 0, 0, 0, 0, 0, 0x37, 0, 0, 0, 0, 0, 0x38, 0, 0, 0, 0, 0, 0x39, 0, 0, 0, 0, 0, 0x3A, 0, 0, 0, 0, 0, 0x3B, 0, 0, 0, 0, 0, 0x3C, 0, 0, 0, 0, 0, 0x3D, 0, 0, 0, 0, 0, 0x3E, 0, 0, 0, 0, 0, 0x3F, 0, 0, 0, 0, 0, 0, 0, 0 };
u8 gGbCartVerifyList_Blue[396] = { 0, 0, 0xD3, 0xE2, 2, 0x4C, 0x80, 0, 0x80, 1, 0x80, 2, 0x80, 3, 0, 1, 0x57, 0xAC, 0xA3, 0xDA, 0, 2, 0x19, 0x1C, 0x43, 0xC1, 0, 0x13, 0x90, 0x64, 0xE4, 0xD6, 0, 0x1C, 0x71, 0xBB, 0xE8, 0x45, 0, 4, 0xBD, 0x4D, 5, 0xF0, 0, 6, 0xC1, 0x62, 0xC1, 0, 0, 0x10, 0x8D, 0x71, 0xBE, 0x4F, 0, 0x1F, 0x52, 0x57, 0x72, 0x55, 0, 0x1E, 0xBC, 0x53, 0x61, 0xCC, 0, 3, 2, 0x5A, 0xAA, 0xD, 0, 0x1A, 0x4F, 0x47, 0xA, 0xFD, 0, 0xE, 0x99, 0x20, 0x97, 0x73, 0, 0xD, 0xB, 0x4E, 0xB8, 0x8F, 0, 0xF, 0xDD, 0x43, 0xE1, 9, 0, 5, 0x7F, 0x3A, 8, 0x35, 0, 7, 0xE, 0x32, 1, 0x14, 0, 0x15, 0xE7, 0x68, 0x19, 0x98, 0, 0x19, 0x2C, 0x1F, 0x21, 0xE8, 0, 0x1D, 0x10, 0xD1, 0x7D, 0x54, 0, 0x22, 0x90, 0x69, 0xB5, 0x2E, 0, 0xB, 0x65, 0x81, 0xEF, 0xA0, 0, 0x25, 0x13, 0x11, 0x23, 2, 0, 0x11, 0x48, 5, 7, 0x61, 0, 0x14, 0xC4, 0x80, 0xBE, 0x6A, 0, 0x17, 0x42, 0x32, 0, 0, 0, 0x12, 0xAD, 0x8D, 0xC7, 0x56, 0, 8, 0x5A, 0x42, 0x6B, 0xF0, 0, 9, 0x95, 6, 0xF4, 0x8B, 0, 0xA, 0x9D, 0x35, 0x8D, 0x38, 0, 0xC, 0x35, 0xB9, 0xCC, 0x9E, 0, 0x16, 0x84, 0x33, 7, 0xED, 0, 0x18, 0xDB, 0x64, 0xB8, 0x77, 0, 0x1B, 0x30, 0x82, 0xC5, 0x60, 0, 0x20, 0x3A, 9, 0x65, 4, 0, 0x21, 0x43, 0x7E, 0xB1, 0x41, 0, 0x23, 0x38, 0x21, 0x3B, 0x7F, 0, 0x24, 8, 0xD6, 0x6C, 0xA4, 0, 0x26, 0x6F, 0xCF, 0, 0xAC, 0, 0x27, 0x32, 0x6C, 0x67, 0xF3, 0, 0x28, 0x54, 0x1C, 0xB, 0xC6, 0, 0x29, 0xFB, 0x98, 0xB6, 0xF1, 0, 0x2A, 0xC2, 0x23, 0, 0, 0, 0x2B, 0xAC, 0x93, 0xE9, 0xAE, 0, 0x2C, 0x1F, 0x51, 0, 0, 0, 0x2D, 0, 0, 0, 0, 0, 0x2E, 0, 0, 0, 0, 0, 0x2F, 0, 0, 0, 0, 0, 0x30, 0, 0, 0, 0, 0, 0x31, 0, 0, 0, 0, 0, 0x32, 0, 0, 0, 0, 0, 0x33, 0, 0, 0, 0, 0, 0x34, 0, 0, 0, 0, 0, 0x35, 0, 0, 0, 0, 0, 0x36, 0, 0, 0, 0, 0, 0x37, 0, 0, 0, 0, 0, 0x38, 0, 0, 0, 0, 0, 0x39, 0, 0, 0, 0, 0, 0x3A, 0, 0, 0, 0, 0, 0x3B, 0, 0, 0, 0, 0, 0x3C, 0, 0, 0, 0, 0, 0x3D, 0, 0, 0, 0, 0, 0x3E, 0, 0, 0, 0, 0, 0x3F, 0, 0, 0, 0, 0, 0, 0, 0 };
u8 gGbCartVerifyList_Yellow[396] = { 0, 0, 0x73, 0xDE, 0x18, 0x5A, 0x80, 0, 0x80, 1, 0x80, 2, 0x80, 3, 0, 2, 0x28, 0x15, 0x9A, 0x70, 0, 8, 0xD0, 0x27, 0x90, 0x80, 0, 1, 0xF9, 0xED, 0xE6, 0xF9, 0, 0x3D, 0x86, 0xAD, 0x2E, 0x7C, 0, 0x1C, 0x73, 0xFE, 0x4D, 0xCF, 0, 3, 0xDB, 0xD0, 0x13, 0x41, 0, 0x10, 0xF5, 0x91, 0, 0, 0, 4, 0x72, 0xC5, 0x44, 0xE7, 0, 0x1E, 0xD7, 0xC1, 0x18, 0x82, 0, 0x1F, 0x26, 0xD1, 0x52, 0x71, 0, 0x3E, 0x7E, 0x93, 0xB3, 0xB7, 0, 0x3C, 0xF, 0xCE, 0xD5, 0x23, 0, 0x21, 0x23, 0xEF, 0x20, 0x9C, 0, 0x24, 0x26, 0xB1, 0x52, 0x98, 0, 0x3F, 0xD2, 0x81, 0xD0, 8, 0, 6, 0xD6, 0x89, 0x4B, 0x99, 0, 5, 0x2F, 0xD, 0xAB, 0xBD, 0, 7, 2, 0xDC, 0xBC, 0x1E, 0, 0x15, 0xCB, 0x6E, 0xBA, 0xD2, 0, 0x19, 0x2E, 0xEE, 0x36, 0xB3, 0, 0x3A, 0x17, 0xFA, 0x89, 0xD0, 0, 0xF, 0xE5, 0x2F, 0xBA, 0x81, 0, 0x14, 0xDB, 0x93, 0x76, 0xF3, 0, 0x29, 0x19, 0x36, 0xD9, 0xE, 0, 0x13, 0x90, 0x64, 0xD5, 0x90, 0, 0x28, 6, 0x55, 0xF7, 0x47, 0, 0xE, 0x4A, 0xD9, 0x4C, 0x88, 0, 0xB, 0xF3, 0x2A, 9, 0x22, 0, 0x17, 0x86, 0x2F, 0, 0, 0, 0x27, 0x43, 0x8E, 0x23, 0x9B, 0, 9, 0x74, 0x49, 0xD3, 6, 0, 0xA, 0xAE, 0x10, 0xD1, 0xF5, 0, 0xC, 0xF9, 0x7D, 0xAC, 0xB2, 0, 0xD, 0xE3, 0xEE, 0x21, 0xB, 0, 0x11, 0xC6, 0x6A, 0x87, 0x38, 0, 0x12, 0xE2, 0xAD, 0x73, 0, 0, 0x16, 0x8C, 0xF6, 0xDF, 0x57, 0, 0x18, 0x23, 0xA8, 0x95, 0xA7, 0, 0x1A, 0x41, 0xAD, 0xB, 0x25, 0, 0x1B, 0x30, 0x82, 0xC5, 0x60, 0, 0x1D, 0x58, 0xB0, 0x84, 0x51, 0, 0x20, 0x97, 0xF9, 0x44, 0x22, 0, 0x22, 0x64, 0xD9, 0xDD, 0x45, 0, 0x23, 3, 0xF1, 0x65, 0x6F, 0, 0x25, 0xD2, 0x46, 0x63, 0xCC, 0, 0x26, 0x36, 0xCF, 0x16, 0xBB, 0, 0x2A, 0x22, 0x49, 0xA7, 0, 0, 0x2B, 0x77, 0xCA, 0x92, 0x97, 0, 0x2C, 0x42, 0x8A, 0xF6, 0x13, 0, 0x2D, 0xB, 0x68, 0x20, 0x45, 0, 0x2E, 0xBA, 0x3E, 0xC3, 0x37, 0, 0x2F, 0x24, 0xD4, 0x98, 0x8D, 0, 0x30, 0xA8, 0x32, 0x98, 0x1C, 0, 0x31, 0xFB, 0xCA, 0x50, 0x5D, 0, 0x32, 0x79, 0x76, 0x99, 0xF8, 0, 0x33, 0x6C, 0x79, 0x1B, 0xC2, 0, 0x34, 0x35, 0xE, 0x74, 0x28, 0, 0x35, 0x19, 0xFD, 0x4D, 0x4C, 0, 0x36, 0xFB, 0xF7, 0xE4, 0x44, 0, 0x37, 0xCE, 0x4B, 0xDA, 0x69, 0, 0x38, 0x1F, 0xF6, 0xDE, 0xF8, 0, 0x39, 0xAE, 0xC5, 0x25, 0x57, 0, 0x3B, 0, 0, 0, 0, 0, 0, 0, 0 };
u8 gGbCompressedBankList_RedBlue[44] = { 0, 0x17, 0x18, 0xF8, 0, 0x18, 0x1A, 0xA0, 0, 0x20, 0x1A, 0x7C, 0, 0x23, 0x1A, 0x40, 0, 0x24, 0x19, 0, 0, 0x25, 0x1A, 0x54, 0, 0x26, 0x1A, 0xAC, 0, 0x28, 0x1A, 0x7C, 0, 0x2A, 3, 4, 0, 0x2C, 5, 0x64, 0, 0, 0, 0 };
u8 gGbCompressedBankList_Yellow[176] = { 0, 5, 0x26, 0x94, 0, 6, 0x1F, 0x28, 0, 7, 0x1D, 0xB8, 0, 0x10, 0x1A, 0x2C, 0, 0x11, 0x22, 0xD4, 0, 0x12, 0x1D, 0x6C, 0, 0x14, 0x1E, 0xA8, 0, 0x15, 0x1D, 0x38, 0, 0x16, 0x1C, 0x88, 0, 0x17, 0x19, 0x14, 0, 0x18, 0x1B, 0x90, 0, 0x19, 0x25, 0x38, 0, 0x1A, 0x23, 0xF0, 0, 0x1B, 0x22, 0x84, 0, 0x1D, 0x1B, 0xA8, 0, 0x20, 0x25, 0x70, 0, 0x21, 0x1C, 0x7C, 0, 0x22, 0x24, 0x28, 0, 0x24, 0x18, 0xEC, 0, 0x25, 0x1C, 0xFC, 0, 0x26, 0x23, 0x48, 0, 0x27, 0x23, 0x88, 0, 0x28, 0x23, 0x44, 0, 0x29, 0x20, 0xB4, 0, 0x2A, 0x23, 0x30, 0, 0x2B, 0x23, 0x54, 0, 0x2C, 0x23, 0x10, 0, 0x2D, 0x1F, 0x10, 0, 0x2E, 0x21, 0x94, 0, 0x2F, 7, 4, 0, 0x30, 0xD, 0xA0, 0, 0x31, 0x1F, 0xC4, 0, 0x32, 0x13, 0x68, 0, 0x33, 0x1D, 0x98, 0, 0x34, 0x11, 0x8C, 0, 0x35, 0x1C, 0x54, 0, 0x36, 0x1B, 0xEC, 0, 0x37, 0x1D, 0x74, 0, 0x38, 0x22, 0x74, 0, 0x39, 0x20, 0xD4, 0, 0x3A, 0x1D, 0xBC, 0, 0x3C, 0x21, 0x6C, 0, 0x3D, 0x20, 0x9C, 0, 0, 0, 0 };
s16 gGbEmuTextPaletteGray[16] = { 0, 4228, 8456, 12684, 16912, 21140, 25368, 29596, -31712, -27484, -23256, -19028, -14800, -10572, -6344, -2116 };
s16 gGbEmuTextPaletteYellow[16] = { 0, 4226, 8452, 12612, 16838, 21064, 25290, 29452, -29810, -25586, -21360, -17134, -12972, -8746, -4522, -296 };
s16 gGbEmuTextPaletteBlackWhite[16] = { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1 };
s16 gGbEmuTextPaletteBlackGray[16] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 21140 };
s16 gGbEmuTextPaletteRed[16] = { -2048, -2048, -2048, -2048, -2048, -2048, -2048, -2048, -2048, -2048, -2048, -2048, -2048, -2048, -2048, -2048 };
s16 gGbEmuTextPaletteGreen[16] = { 1984, 1984, 1984, 1984, 1984, 1984, 1984, 1984, 1984, 1984, 1984, 1984, 1984, 1984, 1984, 1984 };
s16 gGbEmuTextPaletteBlue[16] = { 62, 62, 62, 62, 62, 62, 62, 62, 62, 62, 62, 62, 62, 62, 62, 62 };
s16 gGbEmuTextPaletteGrayAlt[16] = { 0, 2114, 6342, 10570, 14798, 19026, 23254, 27482, 31710, -29598, -25370, -21142, -16914, -12686, -8458, -4230 };
s16 gGbEmuTextPaletteYellowPale[16] = { 0, 4226, 8452, 12680, 16906, 21132, 25358, 29586, -29612, -25386, -21160, -16934, -12706, -8480, -4254, -28 };
s16 gGbEmuTextPaletteCyan[16] = { 0, 2180, 4360, 8588, 10768, 12948, 15128, 19356, 21602, 23782, 25962, 28142, 32370, -30986, -28806, -26626 };
s16 gGbEmuTextPaletteGrayDark[16] = { 0, 4228, 6342, 10570, 14798, 16912, 21140, 23254, 27482, 31710, -31712, -27484, -25370, -21142, -16914, -14800 };
s16 gGbEmuTextPalettePink[16] = { 0, 4228, 8390, 12618, 16846, 21008, 25236, 29398, -29862, -25634, -21472, -17244, -13082, -8854, -4626, -464 };
u8 TileMap_8x8[256] = { 4, 0, 7, 7, 7, 7, 7, 7, 7, 0, 7, 0, 0, 7, 7, 0, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 5, 7, 7, 5, 7, 7, 5, 7, 4, 7, 5, 7, 7, 7, 5, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 3, 7, 7, 3, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x34, 0x35, 0, 0, 6, 0xD, 0x37, 3, 4, 0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x3E, 0x42, 0, 0x3E, 0, 0x40, 0x76, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F, 0x30, 0x31, 0x32, 0x33, 7, 0, 8, 0, 0, 0, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F, 0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5A, 0x5B, 0x5C, 0x5D, 0x5E, 0, 0x50, 0, 0xE, 0 };
u8 TileMap_12x12[256] = { 4, 0, 7, 7, 7, 7, 7, 7, 7, 0, 7, 0, 0, 7, 7, 0, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 5, 7, 7, 5, 7, 7, 5, 7, 4, 7, 5, 7, 7, 7, 5, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 3, 7, 7, 3, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x34, 0x35, 0, 0, 6, 0xD, 0x37, 3, 4, 0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x3E, 0x42, 0, 0x3E, 0, 0x40, 0x76, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F, 0x30, 0x31, 0x32, 0x33, 7, 0, 8, 0, 0, 0, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F, 0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5A, 0x5B, 0x5C, 0x5D, 0x5E, 0, 0x50, 0, 0xE, 0 };
u16 gGbPakBorderColors[4] = { 0xFCA4, 0xCFE4, 0x96BE, 0xFFE4 };
u8 gText_MenuTitle[12] = { 0x80, 0x44, 0, 0xC, 9, 4, 0x4D, 0x65, 0x6E, 0x75, 0, 0 };
u8 gText_ContinueGame[20] = { 0x80, 0x1A, 0x14, 0xC, 8, 0xD, 0x43, 0x6F, 0x6E, 0x74, 0x69, 0x6E, 0x75, 0x65, 0x20, 0x47, 0x61, 0x6D, 0x65, 0 };
u8 gText_QuitGame[16] = { 0x80, 0x1A, 0x28, 0xC, 8, 9, 0x51, 0x75, 0x69, 0x74, 0x20, 0x47, 0x61, 0x6D, 0x65, 0 };
u8 gText_HelpConfig[24] = { 0x80, 0x1A, 0x3C, 0xC, 8, 0xE, 0x48, 0x65, 0x6C, 0x70, 0x20, 0x26, 0x20, 0x43, 0x6F, 0x6E, 0x66, 0x69, 0x67, 0x2E, 0, 0, 0, 0 };
u8 gText_ExitMenuPrompt[72] = { 0x80, 0xA, 0x5A, 0xC, 9, 0xE, 0x45, 0x78, 0x69, 0x74, 0x20, 0x74, 0x68, 0x69, 0x73, 0x20, 0x4D, 0x65, 0x6E, 0x75, 0x80, 0xA, 0x6C, 0xC, 9, 0x15, 0x61, 0x6E, 0x64, 0x20, 0x63, 0x6F, 0x6E, 0x74, 0x69, 0x6E, 0x75, 0x65, 0x20, 0x77, 0x69, 0x74, 0x68, 0x20, 0x74, 0x68, 0x65, 0x80, 0xA, 0x7E, 0xC, 9, 0x11, 0x47, 0x61, 0x6D, 0x65, 0x20, 0x42, 0x6F, 0x79, 0x20, 0x50, 0x4F, 0x4B, 0x40, 0x4D, 0x4F, 0x4E, 0x2E, 0, 0 };
u8 gText_QuitGameBoyPrompt[72] = { 0x80, 0xA, 0x5A, 0xC, 9, 0x15, 0x51, 0x75, 0x69, 0x74, 0x20, 0x47, 0x61, 0x6D, 0x65, 0x20, 0x42, 0x6F, 0x79, 0x20, 0x50, 0x4F, 0x4B, 0x40, 0x4D, 0x4F, 0x4E, 0x80, 0xA, 0x6C, 0xC, 9, 0xD, 0x61, 0x6E, 0x64, 0x20, 0x72, 0x65, 0x74, 0x75, 0x72, 0x6E, 0x20, 0x74, 0x6F, 0x80, 0xA, 0x7E, 0xC, 9, 0x10, 0x50, 0x4F, 0x4B, 0x40, 0x4D, 0x4F, 0x4E, 0x20, 0x53, 0x54, 0x41, 0x44, 0x49, 0x55, 0x4D, 0x2E, 0, 0, 0, 0 };
u8 gText_StartSelectInfo[64] = { 0x80, 0xA, 0x5A, 0xC, 9, 0x14, 0x54, 0x68, 0x65, 0x20, 0x53, 0x54, 0x41, 0x52, 0x54, 0x20, 0x61, 0x6E, 0x64, 0x20, 0x53, 0x45, 0x4C, 0x45, 0x43, 0x54, 0x80, 0xA, 0x6C, 0xC, 9, 0xF, 0x73, 0x65, 0x74, 0x74, 0x69, 0x6E, 0x67, 0x73, 0x20, 0x6D, 0x61, 0x79, 0x20, 0x62, 0x65, 0x80, 0xA, 0x7E, 0xC, 9, 8, 0x63, 0x68, 0x61, 0x6E, 0x67, 0x65, 0x64, 0x2E, 0, 0, 0 };
u8 gText_GameSavedPrompt[44] = { 0x80, 0xA, 0x5A, 0xC, 9, 0xB, 0x47, 0x61, 0x6D, 0x65, 0x20, 0x73, 0x61, 0x76, 0x65, 0x64, 0x3F, 0x80, 0xA, 0x6C, 0xC, 9, 0x11, 0x49, 0x73, 0x20, 0x69, 0x74, 0x20, 0x4F, 0x4B, 0x20, 0x74, 0x6F, 0x20, 0x71, 0x75, 0x69, 0x74, 0x3F, 0, 0, 0, 0 };
u8 gText_Yes[12] = { 0x80, 0x1A, 0x7E, 0xC, 8, 3, 0x59, 0x65, 0x73, 0, 0, 0 };
u8 gText_Empty[4] = { 0x80, 0x60, 0x7E, 0xC };
u8 gText_No[8] = { 8, 2, 0x4E, 0x6F, 0, 0, 0, 0 };
u8 gText_ButtonDoubleSpeed[80] = { 0x80, 0x14, 0xA, 0xA, 0xB, 0x14, 0x42, 0x75, 0x74, 0x74, 0x6F, 0x6E, 0x3A, 0x20, 0x44, 0x6F, 0x75, 0x62, 0x6C, 0x65, 0x20, 0x53, 0x70, 0x65, 0x65, 0x64, 0x80, 0xA, 0x1E, 0xA, 9, 0x14, 0x50, 0x72, 0x65, 0x73, 0x73, 0x20, 0x6F, 0x6E, 0x63, 0x65, 0x20, 0x74, 0x6F, 0x20, 0x64, 0x6F, 0x75, 0x62, 0x6C, 0x65, 0x80, 0xA, 0x30, 0xA, 9, 0x15, 0x50, 0x4F, 0x4B, 0x40, 0x4D, 0x4F, 0x4E, 0x27, 0x73, 0x20, 0x70, 0x6C, 0x61, 0x79, 0x20, 0x73, 0x70, 0x65, 0x65, 0x64, 0x2E, 0 };
u8 gText_EachPressPokemon[100] = { 0x80, 0x14, 6, 0xA, 0xB, 0x14, 0x42, 0x75, 0x74, 0x74, 0x6F, 0x6E, 0x3A, 0x20, 0x44, 0x6F, 0x75, 0x62, 0x6C, 0x65, 0x20, 0x53, 0x70, 0x65, 0x65, 0x64, 0x80, 0xA, 0x18, 0xA, 9, 0x15, 0x45, 0x61, 0x63, 0x68, 0x20, 0x74, 0x69, 0x6D, 0x65, 0x20, 0x79, 0x6F, 0x75, 0x20, 0x70, 0x72, 0x65, 0x73, 0x73, 0x2C, 0x20, 0x80, 0xA, 0x28, 0xA, 9, 0x12, 0x74, 0x68, 0x65, 0x20, 0x50, 0x4F, 0x4B, 0x40, 0x4D, 0x4F, 0x4E, 0x20, 0x67, 0x61, 0x6D, 0x65, 0x27, 0x73, 0x80, 0xA, 0x38, 0xA, 9, 0xE, 0x73, 0x70, 0x65, 0x65, 0x64, 0x20, 0x63, 0x68, 0x61, 0x6E, 0x67, 0x65, 0x73, 0x2E, 0, 0, 0 };
u8 gText_Config[16] = { 0x80, 0x14, 0x4A, 0xA, 0xA, 7, 0x43, 0x6F, 0x6E, 0x66, 0x69, 0x67, 0x2E, 0, 0, 0 };
u8 gText_ButtonCancel[24] = { 0x80, 0x2C, 0x7A, 0xA, 0xA, 0xE, 0x42, 0x75, 0x74, 0x74, 0x6F, 0x6E, 0x3A, 0x20, 0x43, 0x61, 0x6E, 0x63, 0x65, 0x6C, 0, 0, 0, 0 };
u8 gText_UnableToSave[24] = { 0x80, 0x64, 0x3C, 0xC, 8, 0xF, 0x55, 0x6E, 0x61, 0x62, 0x6C, 0x65, 0x20, 0x74, 0x6F, 0x20, 0x53, 0x41, 0x56, 0x45, 0x2E, 0, 0, 0 };
u8 gText_LeavingN64[128] = { 0x80, 0x28, 0x78, 0xC, 7, 0x10, 0x4C, 0x65, 0x61, 0x76, 0x69, 0x6E, 0x67, 0x20, 0x79, 0x6F, 0x75, 0x72, 0x20, 0x4E, 0x36, 0x34, 0x80, 0xCC, 0x78, 0xC, 7, 8, 0x2C, 0x20, 0x64, 0x65, 0x74, 0x61, 0x63, 0x68, 0x80, 0x91, 0x78, 0xC, 0xB, 9, 0x74, 0x75, 0x72, 0x6E, 0x65, 0x64, 0x20, 0x4F, 0x4E, 0x80, 0x28, 0x8C, 0xC, 7, 0x24, 0x74, 0x68, 0x65, 0x20, 0x47, 0x42, 0x20, 0x47, 0x61, 0x6D, 0x65, 0x20, 0x50, 0x61, 0x6B, 0x2C, 0x20, 0x63, 0x6C, 0x65, 0x61, 0x6E, 0x20, 0x74, 0x68, 0x65, 0x20, 0x63, 0x6F, 0x6E, 0x6E, 0x65, 0x63, 0x74, 0x6F, 0x72, 0x80, 0x28, 0xA0, 0xC, 7, 0x19, 0x73, 0x65, 0x63, 0x74, 0x69, 0x6F, 0x6E, 0x20, 0x61, 0x6E, 0x64, 0x20, 0x72, 0x65, 0x2D, 0x61, 0x74, 0x74, 0x61, 0x63, 0x68, 0x20, 0x69, 0x74, 0x2E, 0, 0, 0, 0 };
u8 gText_GBGamePakInfo[248] = { 0x80, 0x32, 0x32, 0xC, 8, 0x20, 0x54, 0x68, 0x65, 0x20, 0x47, 0x42, 0x20, 0x47, 0x61, 0x6D, 0x65, 0x20, 0x50, 0x61, 0x6B, 0x20, 0x6F, 0x72, 0x20, 0x74, 0x68, 0x65, 0x20, 0x64, 0x61, 0x74, 0x61, 0x20, 0x68, 0x61, 0x73, 0x20, 0x80, 0x32, 0x40, 0xC, 8, 0xD, 0x62, 0x65, 0x65, 0x6E, 0x20, 0x63, 0x68, 0x61, 0x6E, 0x67, 0x65, 0x64, 0x2E, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x25, 0x78, 0x20, 0x25, 0x78, 0x20, 0x25, 0x78, 0xA, 0, 0, 0, 0x41, 0x75, 0x64, 0x69, 0x6F, 0x3A, 0x4D, 0x65, 0x6D, 0x6F, 0x72, 0x79, 0x3A, 0x48, 0x65, 0x61, 0x70, 0x20, 0x4F, 0x76, 0x65, 0x72, 0x46, 0x6C, 0x6F, 0x77, 0x20, 0x3A, 0x20, 0x4E, 0x6F, 0x74, 0x20, 0x41, 0x6C, 0x6C, 0x6F, 0x63, 0x61, 0x74, 0x65, 0x20, 0x25, 0x64, 0x21, 0xA, 0, 0, 0x25, 0x78, 0x20, 0x25, 0x78, 0x20, 0x25, 0x78, 0xA, 0, 0, 0, 0x41, 0x75, 0x64, 0x69, 0x6F, 0x3A, 0x4D, 0x65, 0x6D, 0x6F, 0x72, 0x79, 0x3A, 0x48, 0x65, 0x61, 0x70, 0x20, 0x4F, 0x76, 0x65, 0x72, 0x46, 0x6C, 0x6F, 0x77, 0x20, 0x3A, 0x20, 0x4E, 0x6F, 0x74, 0x20, 0x41, 0x6C, 0x6C, 0x6F, 0x63, 0x61, 0x74, 0x65, 0x20, 0x25, 0x64, 0x21, 0xA, 0, 0, 0x43, 0x6C, 0x65, 0x61, 0x72, 0x20, 0x57, 0x6F, 0x72, 0x6B, 0x61, 0x72, 0x65, 0x61, 0x20, 0x25, 0x78, 0x20, 0x2D, 0x25, 0x78, 0x20, 0x73, 0x69, 0x7A, 0x65, 0x20, 0x25, 0x78, 0x20, 0xA, 0, 0x48, 0x65, 0x61, 0x70, 0x20, 0x25, 0x78, 0x20, 0x25, 0x78, 0x20, 0x25, 0x78, 0xA, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
u8 GbMem_ReadIoRegister(u16);
s32 GbCpu_Execute(GbPakDeviceState*, s32);
void GbCpu_InitOpcodeTables(GbPakDeviceState*, TileAssetFragment*);

s32 EmuMainLoop(s32);
// emu must live in arg0: a separate pointer local takes a stack slot and the frame grows to 0x50.
s32 EmuMainLoop(s32 arg0) {
#define emu ((GbPakDeviceState*) arg0)
    s32 btn;
    s32 i;

    arg0 = (s32) (&GbPakDevice)[arg0];

    switch (gGbEmuRunState) {
        case 1:
            if (UnknownFlag == 4) {
                UnknownFlag = 3;
                goto reset;
            }
            goto stop;

        case 0xFF:
            osViBlack(0);
            i = 0;
            while (i < 0x100) {
                emu->unk_549C[i++] = 0xFF;
            }
            for (i = 0; i < 0x10; i++) {
                emu->unk_559C[i] = 0xFF;
            }
            GbPakThreadData[gGbPakTaskBufferIndex].unk_3C = 0x1010;
            GbPakThreadData[gGbPakTaskBufferIndex].unk_38 = ScreenBasePtr;
        case 0:
            if (emu->unk_5DC8 == 0) {
                Cont_StartReadInputs();
                i = 0;
                if (emu->unk_5DC9 == 2) {
                    for (; i < (emu->ramSize >> 8); i++) {
                        if ((emu->blockReadStatus[i] < 2) && (emu->blockWriteMask[i] == 0)) {
                            _bcopy((u8*) emu + (i << 8) + 0x12DF0, Buffer_GbPakReadFirstPass, 0x100);
                            emu->gbAddress = i << 8;
                            emu->blockReadStatus[i] = 1;
                            i = 0xFFFF;
                            break;
                        }
                    }
                }
                Cont_ReadInputs();
                emu->buttonsHeld = (gPlayer1Controller->buttonDown & 0xCFFF) |
                                ((gPlayer1Controller->buttonDown & gGbEmuBoundButtonMask0) ? 0x1000 : 0) |
                                ((gPlayer1Controller->buttonDown & gGbEmuBoundButtonMask1) ? 0x2000 : 0);
                emu->buttonsPressed = gPlayer1Controller->buttonPressed;
                if (emu->unk_5DCA != 0) {
                    if (i == 0xFFFF) {
                        emu->command = 5;
                        osSendMesg(&gGbPakServiceQueue, emu, 1);
                        emu->inputCooldown = 8;
                        emu->buttonsPressed &= 0xDFF7;
                    } else {
                        if (((emu->inputCooldown == 0) || (emu->unk_5DC9 != 2)) && (gGbEmuMenuState != 0xE) && (gGbEmuMenuState != 0xF)) {
                            emu->command = 7;
                            osSendMesg(&gGbPakServiceQueue, emu, 1);
                        } else {
                            if (emu->inputCooldown != 0) {
                                emu->inputCooldown = emu->inputCooldown - 1;
                                if (emu->inputCooldown == 0) {
                                    emu->command = 4;
                                    osSendMesg(&gGbPakServiceQueue, emu, 1);
                                }
                            }
                            emu->buttonsPressed &= 0xDFF7;
                        }
                    }
                }
            }
            if (emu->unk_5DC9 == 2) {
                if (emu->inputCooldown != 0) {
                    gCurrentBufferIndex ^= 1;
                    gMarkerAnimFrame++;
                    if (gMarkerAnimFrame >= 11) {
                        gMarkerAnimFrame = 0;
                    }
                    DrawVerticalMarker((u16*) ((u8*) FramebufferImages[gCurrentBufferIndex] + 0x9C), emu->inputCooldown, gMarkerAnimFrame);
                    GbPakThreadData[gGbPakTaskBufferIndex].unk_3C = 0x1010;
                    GbPakThreadData[gGbPakTaskBufferIndex].unk_38 = (s32) FramebufferImages[gCurrentBufferIndex];
                } else {
                    gCurrentBufferIndex ^= 1;
                    if (!(GbPakStateByte & (1 << gCurrentBufferIndex))) {
                        GbPakStateByte |= (1 << gCurrentBufferIndex);
                        DrawStadiumScreen(gCurrentBufferIndex, 1);
                    }
                    GbPakThreadData[gGbPakTaskBufferIndex].unk_3C = 0x1010;
                    GbPakThreadData[gGbPakTaskBufferIndex].unk_38 = ScreenBasePtr;
                }
            }
            break;

        case 2:
        case2:
            if (emu->unk_5DC8 != 0) {
                return 0;
            }
            if (emu->unk_5DCA == 0) {
                UnknownFlag = 1;
                goto stop;
            }
            if (emu->ramWriteVerified == 0) {
                emu->command = 8;
                emu->probeRamAddress = 0;
                osSendMesg(&gGbPakServiceQueue, emu, 1);
                return 0;
            }
            emu->gameVariantData[0] = 0;
            emu->command = 1;
            emu->gbAddress = 0;
            emu->transferBuffer = emu->romImage;
            emu->transferSize = 0x4000;
            osSendMesg(&gGbPakServiceQueue, emu, 1);
            gGbEmuRunState = 3;
            osViBlack(0);
            goto swap;

        case 3:
            if ((emu->unk_5DC8 == 0) && (emu->unk_5DCA != 0)) {
                emu->unk_549C[emu->gbAddress >> 14] = 0xFF;
                emu->gbAddress += 0x4000;
                if (emu->gbAddress == 0x100000) {
                    emu->gameVariantData[0] -= (emu->detectedGbpakId.sum / 256) + (emu->detectedGbpakId.sum & 0xFF);
                    if (emu->detectedGbpakId.sum != (emu->gameVariantData[0] & 0xFFFF)) {
                        UnknownFlag = 1;
                        goto stop;
                    }
                    if (((u8*) emu->romImage)[0x143] & 0x80) {
                        emu->monoGame = 0;
                    } else {
                        emu->monoGame = 1;
                    }
                    emu->mapperType = gGbCartTypeTable[((u8*) emu->romImage)[0x147]];
                    if (((u8*) emu->romImage)[0x148] < 8U) {
                        emu->romSize = gPowerOfTwoTable[((u8*) emu->romImage)[0x148]];
                    } else {
                        emu->romSize = 0x8000;
                    }
                    if (((u8*) emu->romImage)[0x149] < 5U) {
                        emu->ramSize = gGbRamSizeTable[((u8*) emu->romImage)[0x149]];
                    } else {
                        emu->ramSize = 0;
                    }
                    GbEmu_InitContext(emu);
                    emu->command = 2;
                    if (emu->headerMatchIndex != 0) {
                        emu->gbAddress = 0x500;
                    } else {
                        emu->gbAddress = 0;
                    }
                    emu->transferBuffer = (u8*) emu + emu->gbAddress + 0x12DF0;
                    emu->transferSize = emu->ramSize - emu->gbAddress;
                    gGbEmuRunState = 4;
                } else {
                    emu->transferBuffer += 0x4000;
                    emu->command = 1;
                }
                osSendMesg(&gGbPakServiceQueue, emu, 1);
            }
            goto swap;

        case 4:
            if ((emu->unk_5DC8 == 0) && (emu->unk_5DCA != 0)) {
                emu->unk_559C[0] = emu->unk_559C[1] = emu->unk_559C[2] = emu->unk_559C[3] = 0xFF;
                emu->inputCooldown = 1;
                GbEmu_ClearFramebuffers();
                if (osTvType == OS_TV_PAL) {
                    GbEmu_Delay(25);
                    osViSetYScale(0.833f);
                }
                osViSetXScale(0.888f);
                gGbEmuRunState = 0;
            }
        swap:
            if (emu->unk_5DCA == 0) {
                UnknownFlag = 1;
                goto stop;
            }
            if ((gGbEmuRunState != 0) &&
                (EmuTick((s32) gImageDataPtrs[gGbPakTaskBufferIndex], (&gGbScreenFb0)[gGbPakTaskBufferIndex]->img_p) != 0)) {
                osWritebackDCacheAll();
                osViSwapBuffer((&gGbScreenFb0)[gGbPakTaskBufferIndex]->img_p);
                gGbPakTaskBufferIndex ^= 1;
            }
            return 0;

        case 5:
            if (emu->unk_5DC8 != 0) {
                return 0;
            }
            if (emu->unk_5DCA == 0) {
                UnknownFlag = 1;
                goto stop;
            }
            if (emu->ramWriteVerified == 0) {
                emu->command = 8;
                emu->probeRamAddress = 0;
                osSendMesg(&gGbPakServiceQueue, emu, 1);
                return 0;
            }
            emu->gameVariantData[0] = 0;
            emu->command = 6;
            emu->gameVariantData[2] = 0;
            switch (emu->headerMatchIndex) {
                case 1:
                    if ((emu->detectedGbpakId.version != 0) || (emu->detectedGbpakId.sum != 0x91E6) ||
                        (emu->romSignature[1] != 0x80) || (emu->romSignature[2] != 0x7F) || (emu->romSignature[3] != 0xAB) ||
                        (emu->romSignature[4] != 0xA8)) {
                        goto case2;
                    }
                    emu->gameVariantData[1] = (u32) gGbCartVerifyList_Red;
                    emu->gameVariantData[3] = 0;
                    emu->gameVariantData[2] = (u32) gGbCompressedBankList_RedBlue;
                    emu->unk_5DC6 = 1;
                    bzero((u8*) emu->romImage + 0xB4000, 0x4C000);
                    for (i = 0x2D; i < 0x40; i++) {
                        emu->unk_549C[i] = 0xFF;
                    }
                    break;
                case 3:
                    if ((emu->detectedGbpakId.version != 0) || (emu->detectedGbpakId.sum != 0x9D0A) ||
                        (emu->romSignature[1] != 0x80) || (emu->romSignature[2] != 0x7F) || (emu->romSignature[3] != 0xAB) ||
                        (emu->romSignature[4] != 0xA8)) {
                        goto case2;
                    }
                    emu->gameVariantData[1] = (u32) gGbCartVerifyList_Blue;
                    emu->gameVariantData[3] = 0;
                    emu->gameVariantData[2] = (u32) gGbCompressedBankList_RedBlue;
                    emu->unk_5DC6 = 0;
                    bzero((u8*) emu->romImage + 0xB4000, 0x4C000);
                    for (i = 0x2D; i < 0x40; i++) {
                        emu->unk_549C[i] = 0xFF;
                    }
                    break;
                case 4:
                    if ((emu->detectedGbpakId.version != 0) || (emu->detectedGbpakId.sum != 0x47C) ||
                        (emu->romSignature[1] != 0x8F) || (emu->romSignature[2] != 0x91) || (emu->romSignature[3] != 0x84) ||
                        (emu->romSignature[4] != 0x92)) {
                        goto case2;
                    }
                    emu->gameVariantData[1] = (u32) gGbCartVerifyList_Yellow;
                    emu->gameVariantData[3] = 0xD938;
                    emu->gameVariantData[2] = (u32) gGbCompressedBankList_Yellow;
                    emu->unk_5DC6 = 0;
                    bzero((u8*) emu->romImage + 0xEC000, 0x4000);
                    emu->unk_549C[0x3B] = 0xFF;
                    break;
                default:
                    goto case2;
            }
            GbEmu_ClearFramebuffers();
            osViSwapBuffer((&gGbScreenFb0)[gGbPakTaskBufferIndex]->img_p);
            gGbPakTaskBufferIndex ^= 1;
            osViBlack(0);
            osViSetXScale(0.888f);
            osSendMesg(&gGbPakServiceQueue, emu, 1);
            if (osTvType == OS_TV_PAL) {
                GbEmu_Delay(25);
                osViSetYScale(0.833f);
            }
            GbPakStateByte = 0;
            DrawStadiumScreen(0, 0);
            DrawStadiumScreen(1, 0);
            if (gGbEmuPresentationMode == 0) {
                gGbScreenRefreshCounter = 2;
            } else {
                gGbScreenRefreshCounter = 0x20;
            }
            gGbEmuRunState = 6;

        case 6:
            if (emu->unk_5DC8 != 0) {
                gCurrentBufferIndex ^= 1;
                gMarkerAnimFrame++;
                if (gMarkerAnimFrame >= 11) {
                    gMarkerAnimFrame = 0;
                }
                DrawVerticalMarker((u16*) ((u8*) FramebufferImages[gCurrentBufferIndex] + 0x9C), 0, gMarkerAnimFrame);
                if ((gGbScreenRefreshCounter >= 3) && (gGbScreenRefreshCounter < 0x20)) {
                    gGbScreenRefreshCounter++;
                }
                GbPakThreadData[gGbPakTaskBufferIndex].unk_3C = (gGbScreenRefreshCounter / 2) | 0x1000;
                GbPakThreadData[gGbPakTaskBufferIndex].unk_38 = (s32) FramebufferImages[gCurrentBufferIndex];
            } else {
                GbPakThreadData[gGbPakTaskBufferIndex].unk_3C = 0x1010;
                GbPakThreadData[gGbPakTaskBufferIndex].unk_38 = ScreenBasePtr;
                if ((emu->command == 0) && (emu->unk_5DCA != 0)) {
                    gGbEmuRunState = 0;
                }
            }
            if (emu->unk_5DCA == 0) {
                UnknownFlag = 1;
                goto stop;
            }
            if ((gGbBankLoadedFlag == 0) && (emu->unk_549C[0] != 0) && (emu->unk_549C[1] != 0) &&
                (emu->unk_559C[0] != 0) && (emu->unk_559C[1] != 0) && (emu->unk_559C[2] != 0) &&
                (emu->unk_559C[3] != 0) && (emu->programCounter == 0x100)) {
                if (gGbEmuPresentationMode == 0) {
                    gGbScreenRefreshCounter = 3;
                }
                gGbBankLoadedFlag = 1;
                LoadCompressedBank(emu);
                if (((u8*) emu->romImage)[0x143] & 0x80) {
                    emu->monoGame = 0;
                } else {
                    emu->monoGame = 1;
                }
                emu->mapperType = gGbCartTypeTable[((u8*) emu->romImage)[0x147]];
                emu->romSize = 0x100000;
                GbEmu_InitContext(emu);
            }
            break;

stop:
        while (emu->unk_5DC8 != 0) {}
        if (emu->unk_5DCA != 0) {
            emu->command = 4;
            osSendMesg(&gGbPakServiceQueue, emu, 1);
            while ((emu->unk_5DCA != 0) && ((emu->unk_5DC8 != 0) || (emu->command != 0))) {}
        }
        while (emu->unk_5DC8 != 0) {}
        osSendMesg(&gGbPakServiceQueue, NULL, 1);
        while (gGbPakServiceThreadActive != 0) {}
reset:
        if (osTvType == OS_TV_PAL) {
            osViSetYScale(1.0f);
            GbEmu_Delay(25);
        }
        osViSetXScale(1.0f);
        osViBlack(1);
        GbPakStatusByte = 4;
        GbEmu_Delay(40);
        return -1;

    }

    emu->posX[0x126] = GbMem_ReadIoRegister(0xFF26);
    GbApu_SelectRegionClock(emu->posX[0x14D] >> 7);
    emu->unk_53C0 = 0;
    emu->unk_5490 = emu->audioMode;
    if (gGbEmuMenuState == 0) {
        gAudioBufferPtr = GbCpu_Execute(emu, emu->audioMode * 154);
    } else if (UnknownCounter != 0) {
        while (!(IO_READ(SP_STATUS_REG) & 0x400)) {}
        IO_WRITE(SP_STATUS_REG, 0x8000);
    }
    AudioStateMachine(emu);
    if ((gAudioInitialized == 0) && (emu->gameSoundInit != 0)) {
        GbCpu_InitOpcodeTables(emu, TileAssetFragments[0]);
        gAudioInitialized = 1;
        if (gGbEmuPresentationMode == 0) {
            gPendingDataSetIndex = 0;
            Msg_FadeCounter = -0x40;
        }
    }
    if ((gGbEmuMenuState == 0) && (emu->inputCooldown == 0)) {
        btn = emu->buttonsPressed;
        if ((btn & 0x2000) && (Msg_FadeCounter == 0x40) && (gAudioInitialized != 0) && (gGbEmuPresentationMode != 0)) {
            gPendingDataSetIndex = gDataSetLoadResult + 1;
            if (gPrevDataSetIndex < gPendingDataSetIndex) {
                gPendingDataSetIndex = 0;
            }
            Msg_FadeCounter = -0x40;
            btn = emu->buttonsPressed;
        }
        if (btn & 1) {
            i = emu->audioMode;
            switch (i) {
                case 1:
                default:
                    if (gGbEmuPresentationMode != 0) {
                        i = 2;
                    } else {
                        i = 1;
                    }
                    break;
                case 2:
                    i = 4;
                    if (gGbEmuPresentationMode == 2) {
                        GbPakStatusByte = 1;
                    } else {
                        i = 1;
                    }
                    break;
                case 4:
                    GbPakStatusByte = 3;
                    i = 1;
                    break;
            }
            if (i != emu->audioMode) {
                emu->audioMode = i;
                switch (gGbEmuPresentationMode) {
                    case 2:
                        GbEmu_BlitWithPixelOp((u16*) (ScreenBasePtr + 0x5D4), (u16*) (DataStruct_TileAssets + ((i >= 2) ? 0xAC58 : 0xACB8)), 0, 8, 6);
                        GbEmu_BlitWithPixelOp((u16*) (ScreenBasePtr + 0x5E4), (u16*) (DataStruct_TileAssets + ((i == 4) ? 0xAC58 : 0xACB8)), 0, 8, 6);
                        break;
                    case 1:
                        GbEmu_BlitWithPixelOp((u16*) (ScreenBasePtr + 0x5DA), (u16*) (DataStruct_TileAssets + ((i >= 2) ? 0xAC58 : 0xACB8)), 0, 8, 6);
                        break;
                }
            }
        }
    }
    if (Msg_FadeCounter != 0x40) {
        Msg_FadeCounter++;
        if (Msg_FadeCounter == 0) {
            gDataSetLoadResult = gPendingDataSetIndex;
        }
    }
    emu->unk_53FC = (Msg_FadeCounter <= 0) ? -Msg_FadeCounter : Msg_FadeCounter;
    if ((gGbEmuMenuState == 0) && (emu->unk_53FD < 0x40)) {
        emu->unk_53FD++;
    }
    if ((gGbEmuRunState == 0xFF) && (gGbBankLoadedFlag == 0) && (emu->programCounter == 0x100)) {
        gGbBankLoadedFlag = 1;
        emu->mapperType = gGbCartTypeTable[((u8*) emu->romImage)[0x147]];
        emu->romSize = (((u8*) emu->romImage)[0x148] < 8U) ? gPowerOfTwoTable[((u8*) emu->romImage)[0x148]] : 0x8000;
        emu->ramSize = (((u8*) emu->romImage)[0x149] < 5U) ? gGbRamSizeTable[((u8*) emu->romImage)[0x149]] : 0;
        GbEmu_InitContext(emu);
    }
    if ((emu->unk_5DC8 != 0) && (emu->command == 7)) {
        while ((emu->unk_5DC8 != 0) && (emu->unk_5DCA != 0) && (emu->command != 0)) {}
    }
    if (emu->unk_5DCA == 0) {
        UnknownFlag = 1;
        goto stop;
    }
    if (emu->reservedOpcodeHit != 0) {
        UnknownFlag = 3;
        goto stop;
    }
    if (gGbEmuMenuState == 0x10) {
        goto stop;
    }
    if (emu->monoGame != 0) {
        GbPakThreadData[gGbPakTaskBufferIndex].unk_28 = (s32) D_8122A260;
        GbPakThreadData[gGbPakTaskBufferIndex].unk_2C = D_8122ACA0 - D_8122A260;
    } else {
        GbPakThreadData[gGbPakTaskBufferIndex].unk_28 = (s32) D_812297C0;
        GbPakThreadData[gGbPakTaskBufferIndex].unk_2C = D_8122A1A4 - D_812297C0;
    }
    GbPakThreadData[gGbPakTaskBufferIndex].unk_40 = (s32) emu->tileCache;
    GbPakThreadData[gGbPakTaskBufferIndex].unk_48 = (s32) (&gGbScreenFb0)[gGbPakTaskBufferIndex]->img_p;
    GbPakThreadData[gGbPakTaskBufferIndex].unk_4C = (s32) UnknownPtr;
    GbPakThreadData[gGbPakTaskBufferIndex].unk_50 = emu->readyFrameBuffer;
    GbPakThreadData[gGbPakTaskBufferIndex].unk_54 = (emu->unk_53FE << 24) | emu->unk_539C;
    GbPakThreadData[gGbPakTaskBufferIndex].unk_58 = (s32) TileAssetFragments[gDataSetLoadResult];
    GbPakThreadData[gGbPakTaskBufferIndex].unk_5C = (emu->unk_53FC << 24) | (emu->unk_53FD << 16) | (emu->unk_53EE << 6) | emu->unk_53F0;
    if (UnknownCounter != 0) {
        osRecvMesg(&GbPakThreadData[gGbPakTaskBufferIndex ^ 1].queue, NULL, 1);
        GbPak_DrawMenu((&gGbScreenFb0)[gGbPakTaskBufferIndex ^ 1]->img_p);
    }
    if (gRspTaskManager.preNmiState == 0) {
        osWritebackDCacheAll();
        osViSwapBuffer((&gGbScreenFb0)[gGbPakTaskBufferIndex ^ 1]->img_p);
        if (emu->readyFrameBuffer != 0) {
            emu->rspTaskStatus = 0;
            Sched_SubmitTask((UnkStruct80001380*) &GbPakThreadData[gGbPakTaskBufferIndex], 0);
        }
        gGbPakTaskBufferIndex ^= 1;
        UnknownCounter = 1;
    } else {
        UnknownCounter = 0;
    }
    return 0;

}
#undef emu

void GbEmu_Init(GbEmuState* arg0) {
  GbPakStatusByte = 0;
  gGbEmuPresentationMode = arg0->inputConfig.posY;
  if ((gGbEmuPresentationMode < 0) || (gGbEmuPresentationMode >= 3)) {
      gGbEmuPresentationMode = 0;
  }
  gGbEmuButtonBindingSelections.posX = ((arg0->inputConfig.posX & 0xFF00) >> 8);
  gGbEmuButtonBindingSelections.TrainerSlotSaveData_GamePort = (arg0->inputConfig.posX + 1) & 0xFF;
  GbEmu_ApplyButtonMapping();
  gGbEmuFont1Data = arg0->font1 + 0x90;
  gGbEmuFont2Data = arg0->font2 + 0x90;
  EmuMainInit(0, GbSave_GetActivePort(), 5, 0x50, &gSIEventMesgQueue, arg0->inputConfig.rotation);
}

void GbEmu_RunFrame(GbEmuState* arg0) {
  if (EmuMainLoop(0) != 0) {
      arg0->inputConfig.posX = ((gGbEmuButtonBindingSelections.TrainerSlotSaveData_GamePort - 1) & 0xFF) | (gGbEmuButtonBindingSelections.posX << 8);
      IO_WRITE(SP_STATUS_REG, 0x8000);
      osSendMesg(&arg0->queue2, UnknownFlag, 0);
  }

  if (GbPakStatusByte == 0) {
      if ((gGbEmuRunState == 0) || (gGbEmuRunState == 6)) {
          GbAudio_Update();
      }
  } else if (GbPakStatusByte == 1) {
      GbPakStatusByte = 2;
  } else if (GbPakStatusByte == 3) {
      GbPakStatusByte = 0;
  }
}

void GbEmu_AudioVideoTick(UNUSED GbEmuThreadInfo* arg0) {
  if ((gRspTaskManager.preNmiState == 0) && (GbPakStatusByte == 2) && ((gGbEmuRunState == 0) || (gGbEmuRunState == 6))) {
      GbAudio_Update();
  }
}
