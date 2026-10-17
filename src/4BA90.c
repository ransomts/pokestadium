#include "4BA90.h"
#include "src/49790.h"
#include "src/libnumus/player.h"
#include "src/3D140.h"

s32 gMusicChannel2MasterVolume = 0;
s32 gMusicChannel1MasterVolume = 0;
s32 gMusicTransitionSfxId = 0;

void Music_SetMasterVolumeLevel(s32 arg0, u32 arg1) {
    s32 var_a1;

    switch (arg1) {
        case 0:
            var_a1 = 0;
            break;

        case 1:
            var_a1 = 0x3FFF;
            break;

        case 2:
            var_a1 = 0x4FFF;
            break;

        case 3:
            var_a1 = 0x5FFF;
            break;

        case 4:
            var_a1 = 0x6FFF;
            break;

        case 5:
            var_a1 = 0x7FFF;
            break;

        default:
            var_a1 = 0x6FFF;
            break;
    }

    if (arg0 & 1) {
        gMusicChannel1MasterVolume = var_a1;
    }

    if (arg0 & 2) {
        gMusicChannel2MasterVolume = var_a1;
    }

    MusSetMasterVolume(arg0, var_a1);
}

void Music_SetPanMode(s32 arg0) {
    MusSetPanMode(arg0);
}

void Music_HandleStateChange(u32 arg0) {
    switch (arg0) {
        case 1:
            MusSetDurationScale(gMusicTransitionSfxId, 3);
            MusSetMasterVolume(2, gMusicChannel2MasterVolume >> 1);
            MusSetMasterVolume(1, gMusicChannel1MasterVolume / 3);
            gMusicTransitionSfxId = PlaySoundEffect(0x23);
            MusSetVolumeScale(gMusicTransitionSfxId, 0xFF);
            break;

        case 0:
            MusSetDurationScale(gMusicTransitionSfxId, 3);
            MusSetMasterVolume(2, gMusicChannel2MasterVolume);
            MusSetMasterVolume(1, gMusicChannel1MasterVolume);
            gMusicTransitionSfxId = PlaySoundEffect(0x24);
            break;

        case 2:
            MusSetVolumeScale(PlaySoundEffect(1), 0xFF);
            break;

        case 3:
            MusSetVolumeScale(PlaySoundEffect(0x21), 0xFF);
            break;

        case 4:
            MusSetDurationScale(gMusicTransitionSfxId, 3);
            MusSetMasterVolume(2, gMusicChannel2MasterVolume);
            MusSetMasterVolume(1, gMusicChannel1MasterVolume);
            break;
    }
}

void Music_StartVolumeFade(u32 arg0) {
    u32 temp_v0;

    if (arg0 == 0) {
        arg0 = 1;
    }

    temp_v0 = osSetIntMask(1);

    gMusicChannel2Volume = gMusicChannel2MasterVolume;
    gMusicChannel1Volume = gMusicChannel1MasterVolume;
    gMusicChannel2Step = gMusicChannel2Volume / arg0;
    gMusicChannel1Step = gMusicChannel1Volume / arg0;
    mus_sound_effect_blocked = 1;

    osSetIntMask(temp_v0);
}

void Music_EndVolumeFade(void) {
    u32 temp_v0 = osSetIntMask(1);

    mus_sound_effect_blocked = 0;
    gMusicChannel2Volume = 0.0f;
    gMusicChannel1Volume = 0.0f;

    osSetIntMask(temp_v0);

    MusSetMasterVolume(2, gMusicChannel2MasterVolume);
    MusSetMasterVolume(1, gMusicChannel1MasterVolume);
}
