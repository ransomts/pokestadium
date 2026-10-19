#include "50860.h"
#include "45720.h"
#include "libnumus/player.h"
#include "3D140.h"

void Audio_SetVolumeFadeAndDuration(s32 arg0, u32 arg1) {
    s32 i;

    if (arg0 & 4) {
        for (i = 0; i < 2; i++) {
            Audio_SetVolumeFade(i, arg1);
        }
        arg0 &= ~4;
    }
    MusSetAllChannelsDuration(arg0, arg1);
}

void Audio_ResetAndSetFade(s32 arg0) {
    s32 i;

    gAudioStadiumSfxEnabled = 0;
    AudioFrameUpdate(0);
    Audio_SetVolumeFadeAndDuration(3, arg0);

    for (i = 0; i < 2; i++) {
        Audio_SetVolumeFade(i, arg0);
    }
}

void Audio_FadeAllChannelsDefault(void) {
    Audio_ResetAndSetFade(1);
}

void Audio_FadeAllChannels(s32 arg0) {
    Audio_ResetAndSetFade(arg0);
}
