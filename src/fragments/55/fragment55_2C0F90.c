#include "fragment55.h"
#include "src/1CF30.h"
#include "src/49790.h"

static s16 gDialogState;
static s16 gDialogTimer;
static s16 gDialogMessageId;
static s16 gDialogAnimProgress;
static s16 gDialogYPos;
static s16 gDialogHeight;

s32 GetStringLineCount(s8* arg0) {
    s16 var_v1 = 1;

    while (*arg0 != 0) {
        if (*arg0 == '\n') {
            var_v1++;
        }
        arg0++;
    }

    return var_v1;
}

void Dialog_UpdateOpening(void) {
    gDialogTimer--;
    gDialogAnimProgress = ((5 - gDialogTimer) << 0xA) / 5;
    if (gDialogTimer <= 0) {
        gDialogState = 2;
        gDialogTimer = 0;
    }
}

void Dialog_WaitForInput(void) {
    if (BTN_IS_PRESSED(gPlayer1Controller, BTN_A | BTN_B)) {
        gDialogState = 3;
        gDialogTimer = 5;
        PlaySoundEffect(3);
    }
}

void Dialog_UpdateClosing(void) {
    gDialogTimer--;
    gDialogAnimProgress = (gDialogTimer << 0xA) / 5;
    if (gDialogTimer <= 0) {
        gDialogState = 0;
        gDialogTimer = 0;
    }
}

void Dialog_CloseImmediately(void) {
    gDialogState = 0;
    gDialogAnimProgress = 0;
}

void Dialog_UpdateStateMachine(void) {
    if (gDialogState != 0) {
        switch (gDialogState) {
            case 1:
                Dialog_UpdateOpening();
                break;

            case 2:
                Dialog_WaitForInput();
                break;

            case 3:
                Dialog_UpdateClosing();
                break;
        }
    }
}

void Dialog_Render(void) {
    s16 temp_s0;

    if (gDialogAnimProgress != 0) {
        temp_s0 = gDialogYPos + (((gDialogHeight / 2) * (0x400 - gDialogAnimProgress)) / 1024);
        RentalRules_DrawWindowFrame(0x48, temp_s0, 0x1F0, (gDialogHeight * gDialogAnimProgress) / 1024);
        if (gDialogAnimProgress >= 0x400) {
            DrawColoredPanel(0x48, temp_s0, 0x1F0, 0x20, 0x1E, 0x64, 0x64);
            DrawColoredPanel(0x48, temp_s0 + 0x20, 0x1F0, gDialogHeight - 0x20, 0x3C, 0x3C, 0xA0);
            Text_ResetState();
            Text_SetFont(8, 0);
            Text_SetEnvColor(0xFF, 0xFF, 0xFF, 0xFF);
            Text_SetLineHeight(0x18);
            Text_Print(0x50, temp_s0 + 6, gMenuStaticStrings.unk_00[gDialogMessageId]);
            Text_SetFont(8, 0);
            Text_Print(0x50, temp_s0 + 0x28, gMenuOptionStrings.unk_00[gDialogMessageId]);
            Text_SetupDL();
        }
    }
}

void Dialog_Start(s16 arg0) {
    s32 tmp;

    gDialogState = 1;
    gDialogTimer = 5;
    gDialogAnimProgress = 0;
    gDialogMessageId = arg0;
    tmp = (GetStringLineCount(gMenuOptionStrings.unk_00[gDialogMessageId]) * 0x18);
    gDialogHeight = 0x2C + tmp;
    gDialogYPos = ((0x1E0 - gDialogHeight) / 2) + 0x14;
}

s32 Dialog_IsActive(void) {
    s32 ret;

    if (gDialogState != 0) {
        ret = 1;
    } else {
        ret = 0;
    }
    return ret;
}

s32 Dialog_GetAnimProgress(void) {
    return gDialogAnimProgress;
}
