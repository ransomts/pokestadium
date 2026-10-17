#include "490A0.h"
#include "src/libnumus/player.h"
#include "src/45720.h"
#include "src/3D140.h"
#include "src/373A0.h"

void Music_RequestHandle(s32 arg0) {
    MusHandleAsk(arg0);
}

s32 Music_GetState(s32 arg0) {
    return MusAsk(arg0);
}

s32 Audio_CalcLoadScore(void) {
    s32 i;
    s32 temp_v0;
    s32 var_s1;

    var_s1 = 0;
    if (mus_free_voices_count != mus_num_vvoices) {
        var_s1 = mus_num_vvoices - mus_free_voices_count;
    }

    for (i = 0; i < 2; i++) {
        if (Audio_IsChannelActive(i) != 0) {
            var_s1 += 100;
        }
    }

    temp_v0 = Audio_IsMusicEnabled();
    if (temp_v0 != 0) {
        var_s1 += temp_v0 * 1000;
    }

    return var_s1;
}

s32 Audio_GetFreeVoiceCount(void) {
    return mus_free_voices_count;
}

s32 Audio_GetReleasingVoiceCount(void) {
    return mus_releasing_voices_count;
}
