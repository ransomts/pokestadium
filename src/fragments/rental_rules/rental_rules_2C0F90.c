#include "rental_rules.h"
#include "src/graphics_textures.h"
#include "src/audio_sfx.h"

static s16 gDialogState;
static s16 gDialogTimer;
static s16 gDialogMessageId;
static s16 gDialogAnimProgress;
static s16 gDialogYPos;
static s16 gDialogHeight;

s32 RentalRules_CountTextLines(s8* arg0) {
    s16 var_v1 = 1;

    while (*arg0 != 0) {
        if (*arg0 == '\n') {
            var_v1++;
        }
        arg0++;
    }

    return var_v1;
}

void RentalRules_PopupUpdateOpen(void) {
    gDialogTimer--;
    gDialogAnimProgress = ((5 - gDialogTimer) << 0xA) / 5;
    if (gDialogTimer <= 0) {
        gDialogState = 2;
        gDialogTimer = 0;
    }
}

void RentalRules_PopupUpdateShown(void) {
    if (BTN_IS_PRESSED(gPlayer1Controller, BTN_A | BTN_B)) {
        gDialogState = 3;
        gDialogTimer = 5;
        Audio_PlaySoundEffectById(3);
    }
}

void RentalRules_PopupUpdateClose(void) {
    gDialogTimer--;
    gDialogAnimProgress = (gDialogTimer << 0xA) / 5;
    if (gDialogTimer <= 0) {
        gDialogState = 0;
        gDialogTimer = 0;
    }
}

void RentalRules_PopupReset(void) {
    gDialogState = 0;
    gDialogAnimProgress = 0;
}

void RentalRules_PopupUpdate(void) {
    if (gDialogState != 0) {
        switch (gDialogState) {
            case 1:
                RentalRules_PopupUpdateOpen();
                break;

            case 2:
                RentalRules_PopupUpdateShown();
                break;

            case 3:
                RentalRules_PopupUpdateClose();
                break;
        }
    }
}

void RentalRules_PopupDraw(void) {
    s16 temp_s0;

    if (gDialogAnimProgress != 0) {
        temp_s0 = gDialogYPos + (((gDialogHeight / 2) * (0x400 - gDialogAnimProgress)) / 1024);
        RentalRules_DrawWindowFrame(0x48, temp_s0, 0x1F0, (gDialogHeight * gDialogAnimProgress) / 1024);
        if (gDialogAnimProgress >= 0x400) {
            RentalRules_DrawFilledPanel(0x48, temp_s0, 0x1F0, 0x20, 0x1E, 0x64, 0x64);
            RentalRules_DrawFilledPanel(0x48, temp_s0 + 0x20, 0x1F0, gDialogHeight - 0x20, 0x3C, 0x3C, 0xA0);
            Font_BeginTranslucentTextRendering();
            Font_SetActive(8, 0);
            Text_SetEnvColor(0xFF, 0xFF, 0xFF, 0xFF);
            Font_SetLineHeight(0x18);
            Font_Printf(0x50, temp_s0 + 6, gMenuStaticStrings.posX[gDialogMessageId]);
            Font_SetActive(8, 0);
            Font_Printf(0x50, temp_s0 + 0x28, gMenuOptionStrings.posX[gDialogMessageId]);
            Font_EndTexturedTextRendering();
        }
    }
}

void RentalRules_PopupOpen(s16 arg0) {
    s32 tmp;

    gDialogState = 1;
    gDialogTimer = 5;
    gDialogAnimProgress = 0;
    gDialogMessageId = arg0;
    tmp = (RentalRules_CountTextLines(gMenuOptionStrings.posX[gDialogMessageId]) * 0x18);
    gDialogHeight = 0x2C + tmp;
    gDialogYPos = ((0x1E0 - gDialogHeight) / 2) + 0x14;
}

s32 RentalRules_PopupIsActive(void) {
    s32 ret;

    if (gDialogState != 0) {
        ret = 1;
    } else {
        ret = 0;
    }
    return ret;
}

s32 RentalRules_PopupGetProgress(void) {
    return gDialogAnimProgress;
}
