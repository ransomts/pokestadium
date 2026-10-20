#include "src/audio_sfx.h"
#include "src/libnumus/player.h"
#include "src/audio_sfx.h"
#include "src/audio_commands_category2.h"
#include "src/audio_commands.h"
#include "src/audio_data.h"

static s32 gLastSfxHandle = 0;
static s32 gSfxHandle_MenuCursorMove = 0;
static s32 gSfxHandle_MenuCancel = 0;
static s32 gSfxHandle_MenuAccept = 0;
static s32 gSfxHandle_MenuScreenOpen = 0;
static s32 gSfxHandle_MenuError = 0;
static s32 gSfxHandle_GalleryCameraShutter = 0;
static s32 gSfxHandle_GalleryCameraExit = 0;
static u8 gSfx3CCooldown = 0;

s32 Audio_PlaySoundEffectById(u32 arg0) {
    u32 temp_v0_3;
    s32 sp28;
    f32 sp24;

    temp_v0_3 = arg0 & 0xFFFF0000;
    sp28 = 0x80;
    sp24 = 0.0f;

    if (temp_v0_3 == 0x01200000) {
        return Audio_PlayCategory12SoundCommand(arg0, 0, 0);
    }

    if (temp_v0_3 == 0x01100000) {
        return Audio_PlayCategory11SoundCommand(arg0, 0, 0);
    }

    if (arg0 == 0xF) {
        if (!(gAudioDMAFlags & 0x80000000)) {
            return 0;
        }
        gLastSfxHandle = MusStartSoundEffect(gSfxBankSpecial, gSfxTable, 0xF, 0x70, 0x80, -1);
        MusSetDurationScale(gMusicHandle, 0x28);
        return gLastSfxHandle;
    }

    if (arg0 == 0x30) {
        arg0 = 0x26;
    }

    if (arg0 == 0x3C) {
        if (gSfx3CCooldown != 0) {
            gSfx3CCooldown++;
            if (gSfx3CCooldown > 0) {
                gSfx3CCooldown = 0;
            }
            return 0;
        }
        gSfx3CCooldown++;
        if (1) {}
        arg0 = 5;
        sp24 = -12.0f;
        sp28 = 0x38;
    }

    switch (arg0) {
        case 0x1:
            MusSetDurationScale(gSfxHandle_MenuCursorMove, 1);
            break;

        case 0x5:
        case 0x6:
        case 0x7:
        case 0x9:
        case 0xD:
        case 0xE:
        case 0x10:
        case 0x11:
        case 0x12:
        case 0x13:
        case 0x14:
        case 0x15:
        case 0x16:
        case 0x17:
        case 0x18:
        case 0x19:
        case 0x1A:
        case 0x1B:
        case 0x1C:
        case 0x1D:
        case 0x1E:
        case 0x1F:
        case 0x20:
        case 0x21:
        case 0x22:
        case 0x23:
        case 0x24:
        case 0x25:
        case 0x26:
        case 0x27:
        case 0x28:
        case 0x29:
        case 0x2F:
            break;

        case 0x2:
            MusSetDurationScale(gSfxHandle_MenuAccept, 1);
            break;

        case 0x3:
            MusSetDurationScale(gSfxHandle_MenuCancel, 1);
            break;

        case 0x4:
            MusSetDurationScale(gSfxHandle_MenuScreenOpen, 0x14);
            break;

        case 0x8:
            MusSetDurationScale(gSfxHandle_MenuError, 2);
            break;

        case 0x2C:
            MusSetDurationScale(gSfxHandle_GalleryCameraShutter, 2);
            sp28 = 0xA0;
            break;

        case 0x2D:
            MusSetDurationScale(gSfxHandle_GalleryCameraShutter, 2);
            break;

        case 0x2E:
            MusSetDurationScale(gSfxHandle_GalleryCameraExit, 2);
            break;

        case 0xA:
            sp28 = 0xE0;
            break;

        case 0x31:
            arg0 -= 1;
            break;

        case 0xB:
        case 0xC:
            sp28 = 0xD0;
            break;

        case 0x2A:
        case 0x2B:
            Audio_PlaySoundEffectById(0x1B);
            break;

        case 0x32:
            gLastSfxHandle = Audio_PlayDirectSoundCommand(0x01000001, 0, 0);
            return gLastSfxHandle;

        case 0x33:
            gLastSfxHandle = Audio_PlayDirectSoundCommand(0x01000002, 0, 0);
            return gLastSfxHandle;

        default:
            return 0;
    }

    gLastSfxHandle = MusStartSoundEffect(gSfxBankStandard, gSfxTable, arg0, sp28, 0x80, -1);
    if (sp24 != 0.0f) {
        MusSetFrequencyOffset(gLastSfxHandle, sp24);
    }

    switch (arg0) {
        case 1:
            gSfxHandle_MenuCursorMove = gLastSfxHandle;
            break;

        case 2:
            gSfxHandle_MenuAccept = gLastSfxHandle;
            break;

        case 3:
            gSfxHandle_MenuCancel = gLastSfxHandle;
            break;

        case 4:
            gSfxHandle_MenuScreenOpen = gLastSfxHandle;
            break;

        case 8:
            gSfxHandle_MenuError = gLastSfxHandle;
            break;

        case 44:
            gSfxHandle_GalleryCameraShutter = gLastSfxHandle;
            break;

        case 45:
            gSfxHandle_GalleryCameraExit = gLastSfxHandle;
            break;
    }

    return gLastSfxHandle;
}
