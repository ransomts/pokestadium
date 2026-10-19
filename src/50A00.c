#include "50A00.h"
#include "src/libnumus/player.h"
#include "src/4B940.h"
#include "src/51740.h"
#include "src/50860.h"
#include "src/373A0.h"

u8* gSfxBankSpecial;

s32 Audio_LoadWaveTablesAndMusic(u8* arg0) {
    UNUSED s32 pad[2];
    u8* sp1C;

    Audio_FadeCategoriesAndStreams(1);
    gSfxBankSpecial = arg0;
    sp1C = gSfxBankSpecial + 0x4120;

    if (1) {}

    Rom_DmaRead(D_800FC6E4->offset1, gMoveSoundTempBuffer, D_800FC6E4->wave_tables_offset - D_800FC6E4->offset1);
    Audio_CopyDataWithCacheSync(gMoveSoundTempBuffer, gSfxBankSpecial, 0x4120);
    Rom_DmaRead(D_800FC6E4->wave_tables_offset, sp1C, D_800FC6E4->files[0] - D_800FC6E4->wave_tables_offset);
    MusBankInitialize(gSfxBankSpecial, sp1C);
    gAudioDMAFlags |= 0x80000000;
    Rom_DmaRead(D_800FC6E4->files[0], gMoveSoundTempBuffer, D_800FC6E4->files[1] - D_800FC6E4->files[0]);
    Audio_CopyDataWithCacheSync(gMoveSoundTempBuffer, D_800FC680, 0x98D8);
    gMusicHandle = MusLoadSong(gSfxBankSpecial, D_800FC680);
    MusSetVolumeScale(gMusicHandle, 0x70);

    return gMusicHandle;
}

void Audio_ClearWaveDataLoaded(void) {
    gAudioDMAFlags &= ~0x80000000;
}
