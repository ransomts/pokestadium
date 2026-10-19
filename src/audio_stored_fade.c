#include "src/audio_stored_fade.h"
#include "src/audio_commands.h"
#include "src/rom_device.h"
#include "src/cry.h"
#include "src/audio_cache.h"
#include "libnumus/player.h"

// .data
u8 gMoveSoundCache[3] = { 0xFF, 0xFF, 0xFF };
u32 gMoveSoundCachePos = 0;
s32 gCurrentSoundHandle = 0;
u8 gSoundDurationScale[4] = { 0 };
u8 gSpecialMoveSoundFlag[16] = { 0 };

s32 PlayMoveSoundEffect(s32 arg0, u32 arg1, u32 arg2, u32 arg3) {
    u32 i;
    u32 temp_v0;
    u32 slot;
    s32 romAddr;
    s32 size;
    MoveSoundEntry* var_a0;
    u8 var_v1;
    u32* seq;
    u8* entry;
    u8 flag;

    flag = 0;
    gSpecialMoveSoundFlag[0] = 0;
    MusSetDurationScale(gCurrentSoundHandle, 0xA);

    if (arg2 == 0xC8) {
        flag = 1;
    } else if ((arg2 == 0) || (arg2 >= 0x98U)) {
        return 0;
    }
    if ((arg2 == 0) || (arg1 >= 0xA6U)) {
        return 0;
    }

    var_v1 = ((arg3 & 0xFF00) >> 8) & 0xFF;
    arg3 &= 0xFF;
    if (((arg3 == 0xA) || (arg3 == 0xB)) && ((var_v1 == 0x10) || (var_v1 == 0x20))) {
        return 0;
    }

    for (i = 0; i < 3; i++) {
        if (arg2 == gMoveSoundCache[i]) {
            slot = i;
            goto found;
        }
    }

    slot = gMoveSoundCachePos % 3;
    gMoveSoundCachePos++;
    gMoveSoundCache[slot] = arg2;
    if (flag) {
        arg2 = 0x97;
    }
    arg2--;
    if (arg2 < (gMoveSoundArchive->num_files - 1)) {
        romAddr = ((u32*)gMoveSoundArchive)[arg2 + 3];
        size = ((u32*)gMoveSoundArchive)[arg2 + 4] - romAddr;
    } else {
        romAddr = ((u32*)gMoveSoundArchive)[arg2 + 3];
        size = gMoveSoundSeqInfo->seqArray[3].offset - romAddr;
    }
    Rom_DmaRead(romAddr, gMoveSoundTempBuffer, size);
    Audio_CopyDataWithCacheSync(gMoveSoundTempBuffer, gMoveSoundBankData[slot], 0x3E8);
    RemapBankPointers(gMoveSoundBankData[slot]);
    if (flag) {
        arg2 = 0x97;
    }
    size = gMoveSoundSeqTable->seqArray[arg2].len;
    if (size & 1) {
        size++;
    }
    Rom_DmaRead((u32)gMoveSoundSeqTable->seqArray[arg2].offset, gMoveSoundTempBuffer, size);
    Audio_CopyDataWithCacheSync(gMoveSoundTempBuffer, gMoveSoundTables[slot], 0x44C);

found:
    switch (arg3) {
    case 0:
    case 2:
    case 3:
        size = 0;
        break;
    case 4:
        size = 2;
        break;
    case 1:
        size = 4;
        break;
    case 11:
        size = 0;
        break;
    case 16:
        arg2 = arg1;
        goto block_38;
    default:
        return 0;
    }
    if (arg3 == 0xB) {
        arg1 = 0;
    }
    var_a0 = gMoveSoundTables[slot]->entries;
    entry = &(var_a0 + arg1)->unk0[size];
    arg2 = entry[0];
    gSoundDurationScale[0] = entry[1];

block_38:
    seq = gMoveSoundBankData[slot];
    temp_v0 = *seq;
    if (!flag && (arg2 >= temp_v0)) {
        return 0;
    }
    if (flag) {
        if ((arg1 == 0x2D) || (arg1 == 0x2E)) {
            gSpecialMoveSoundFlag[0] = 1;
        }
        if (arg2 != 0) {
            Cry_Play(arg2, 0xA);
        }
        return 0;
    }
    temp_v0 = MusStartSoundEffect(gMoveSoundBankBase, seq, arg2, 0x80, 0x80, -1);
    gCurrentSoundHandle = temp_v0;
    return temp_v0;
}

void Audio_FadeStoredSound(void) {
  if (gSoundDurationScale[0] != 0) {
      MusSetDurationScale(gCurrentSoundHandle, (s32)gSoundDurationScale[0]);
  }
}
