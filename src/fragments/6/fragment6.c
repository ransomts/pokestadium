#include "global.h"
#include "src/memory.h"
#include "src/3FB0.h"
#include "src/6A40.h"
#include "src/stage_loader.h"
#include "src/1CF30.h"
#include "src/4BDC0.h"
#include "src/fragments/2/fragment2.h"
#include "src/fragments/4/fragment4.h"
#include "src/fragments/6/fragment6.h"
#include "src/geo_layout.h"
#include "src/19840.h"
#include "src/1C720.h"
#include "src/32D10.h"
#include "src/49790.h"
#include "src/controller.h"
#include "src/20330.h"
#include "src/20470.h"
#include "src/6BC0.h"
#include "src/2E110.h"
#include "src/F420.h"
#include "src/12D80.h"
#include "src/17300.h"

typedef struct unk_D_86002920 {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ s16 unk_08;
    /* 0x0A */ s16 unk_0A;
} unk_D_86002920; // size = 0xC

static unk_D_86002920 gMiniHudRandomChanceTable[31] = {
    { 0x87A0, 0x1190, 0x0032, 0x0028, 0x0005, 0x0000 }, { 0x87A0, 0x1178, 0x004B, 0x0037, 0x0014, 0x0000 },
    { 0x87A0, 0x1180, 0x005C, 0x003C, 0x001E, 0x0000 }, { 0x87A0, 0x11A4, 0x0063, 0x005A, 0x0028, 0x0000 },
    { 0xFFFF, 0xFFE2, 0xFFFF, 0xFFF5, 0x0000, 0x0007 }, { 0x0000, 0x0019, 0x000D, 0x000D, 0x000B, 0x000C },
    { 0x000F, 0x000F, 0x000D, 0x000E, 0x0011, 0x0011 }, { 0x000F, 0x0010, 0x0013, 0x0013, 0x0011, 0x0012 },
    { 0xA5B3, 0xA5A4, 0xA5AD, 0xA5F3, 0xA5B0, 0xA4CE }, { 0xA4CF, 0xA4CD, 0xA4EB, 0xA4C7, 0xA5DD, 0xA5F3 },
    { 0x0000, 0x0000, 0xA1A1, 0xA1A1, 0xA1A1, 0xA1A1 }, { 0xA4C7, 0xA1A1, 0xA5B8, 0xA5E3, 0xA5F3, 0xA5D7 },
    { 0xA4B7, 0xA4C6, 0xA1A1, 0xA4A6, 0xA4A8, 0xA4CE }, { 0xA5AB, 0xA5A6, 0xA5F3, 0xA5BF, 0xA1BC, 0xA4F2 },
    { 0x0000, 0x0000, 0xA4BF, 0xA4AF, 0xA4B5, 0xA4F3 }, { 0xA1A1, 0xA4BF, 0xA4BF, 0xA4A4, 0xA4BF, 0xA4D2 },
    { 0xA4C8, 0xA4AC, 0xA1A1, 0xA4AB, 0xA4C1, 0xA1A3 }, { 0x0000, 0x0000, 0xA1A1, 0xA1A1, 0xA1A1, 0xA1A1 },
    { 0xA4F2, 0xA1A1, 0xA4CA, 0xA4AC, 0xA4AF, 0xA1A1 }, { 0xA4AA, 0xA4B5, 0xA4CA, 0xA4A4, 0xA4C8, 0xA1A1 },
    { 0xA5AB, 0xA5A6, 0xA5F3, 0xA5BF, 0xA1BC, 0xA4DE }, { 0xA4C7, 0x0000, 0xA4C8, 0xA4C9, 0xA4AB, 0xA4CA },
    { 0xA4A4, 0xA4E8, 0xA1A3, 0x0000, 0xA4C1, 0xA4E3 }, { 0xA4AF, 0xA4C1, 0xA4B9, 0xA4EB, 0xA1A1, 0xA5BF },
    { 0xA5A4, 0xA5DF, 0xA5F3, 0xA5B0, 0xA4CB, 0xA4A2 }, { 0xA4EF, 0xA4BB, 0xA4C6, 0xA1A1, 0xA5C6, 0xA5F3 },
    { 0xA5DD, 0xA4E8, 0xA4AF, 0x0000, 0xA5DC, 0xA5BF }, { 0xA5F3, 0xA4F2, 0xA4AA, 0xA4B9, 0xA4CE, 0xA4AC },
    { 0xA1A1, 0xA4B8, 0xA4E7, 0xA4A6, 0xA4BA, 0xA4CB }, { 0xA5B8, 0xA5E3, 0xA5F3, 0xA5D7, 0xA4B9, 0xA4EB },
    { 0xA5B3, 0xA5C4, 0xA4C0, 0xA1A3, 0x0000, 0x0000 },
};

static f32 D_86002A94 = 50.0f;

typedef struct unk_D_86002A98 {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ s16 unk_08;
    /* 0x0A */ s16 unk_0A;
} unk_D_86002A98; // size = 0xC

static unk_D_86002A98 gMiniHudTextureRects[4] = {
    { 0x0014, 0x00D7, 0xFFFF, 0xFFFF, 0x0000, 0xFFFF },
    { 0x005A, 0x00D7, 0xFFFF, 0xFFFF, 0x00FF, 0x00FF },
    { 0x00A0, 0x00D7, 0xFFFF, 0xFFFF, 0xFF00, 0x00FF },
    { 0x00E6, 0x00D7, 0xFFFF, 0xFFFF, 0xFFFF, 0x00FF },
};

static AnimFrame gMiniHudDL_Panel1[] = {
    {
        0x0303ED80,
        0x000E,
    },
    {
        0x0303F180,
        0x0002,
    },
    {
        0x0303F580,
        0x0006,
    },
    {
        0x0303F180,
        0x0002,
    },
    {
        NULL,
        0x0000,
    },
};

static AnimFrame gMiniHudDL_Panel2[] = {
    {
        0x03040580,
        0x0012,
    },
    {
        0x03040980,
        0x0002,
    },
    {
        0x03040D80,
        0x0008,
    },
    {
        0x03040980,
        0x0002,
    },
    {
        NULL,
        0x0000,
    },
};

static u32 gMiniHudGeoLayout[] = {
    0x0C00FFFF, (u32)&D_5000000,  0x0B00001E,      0x00000000,      0x014000F0,      0x0000000F,
    0x00000000, 0x00000000,       (u32)&D_5000000, 0x0D000000,      (u32)&D_5000000, 0x0F000002,
    0x14000000, 0x002B0012,       0xFFFFFF32,      0x16FFFFFF,      0x0F000003,      (u32)&D_5000000,
    0x0A000000, (u32)&gGraphRoot0, (u32)&D_6000000, (u32)&D_6000000, (u32)&D_6000000, (u32)&D_3000000,
    0x87806398, (u32)&D_6000000,  (u32)&D_1000000,
};

static unk_D_86002F30* gMiniHudGeoLayoutObj;
static unk_D_86002F34* gMiniHudMainGraph;
static CameraStruct* gMiniHudCamera;
static s16 gMiniHudCamAtY;
static s16 gMiniHudCamAtZ;
static s16 gMiniHudCamDist;
static u16 gMiniHudFrameCount;
static s16 gMiniHudWinnerCount;
static s32 gMiniHudState;
static s16 gMiniHudAlpha;
static s32 gMiniHudTilemap;

typedef struct unk_D_86002F58_004 {
    /* 0x000 */ Fragment2_1GraphNode unk_000;
    /* 0x168 */ s16 unk_168;
    /* 0x16A */ u16 unk_16A;
    /* 0x16C */ s16 unk_16C;
} unk_D_86002F58_004; // size = 0x170

typedef struct unk_D_86002F58 {
    /* 0x000 */ s16 unk_000;
    /* 0x002 */ char pad2[2];
    /* 0x004 */ unk_D_86002F58_004 unk_004;
    /* 0x174 */ u16 unk_174;
    /* 0x176 */ u16 unk_176[2];
    /* 0x17A */ u16 unk_17A;
    /* 0x17C */ u16 unk_17C[2];
    /* 0x180 */ char pad180[2];
    /* 0x182 */ s16 unk_182;
    /* 0x184 */ s16 unk_184;
    /* 0x186 */ s16 unk_186;
    /* 0x188 */ s16 unk_188;
    /* 0x18A */ s16 unk_18A;
    /* 0x18C */ s16 unk_18C;
    /* 0x18E */ char pad18E[2];
} unk_D_86002F58; // size = 0x190

static unk_D_86002F58 gMiniHudPlayerStates[4];
static unk_D_86002F58_004 D_86003598[4];
static u32 gMiniHudGameTimer;
static unk_D_86002F58* D_86003B5C;
static unk_D_86002F58_004* gCurrentPlayerGraph;
static unk_D_86002F58_004* gCurrentPlayerWheel;
static s16 gMiniHudIntroActive;
static s16 gMiniHudIntroTimer;
static s16 gMiniHudActionFlags[4];
static s16 D_86003B78;
static TextObject* gMiniHudTextObj;
static s32 gMiniHudMaxWheelValue;
static Fragment2_1GraphNode gMiniHudWheelNodes[4];

void MiniHud_UpdateControllerInput(void) {
    s32 i;
    s32 j;

    gMiniHudPlayerStates[0].unk_17A = gPlayer1Controller->buttonPressed;
    gMiniHudPlayerStates[1].unk_17A = gPlayer2Controller->buttonPressed;
    gMiniHudPlayerStates[2].unk_17A = gPlayer3Controller->buttonPressed;
    gMiniHudPlayerStates[3].unk_17A = gPlayer4Controller->buttonPressed;

    gMiniHudPlayerStates[0].unk_174 = gPlayer1Controller->buttonDown;
    gMiniHudPlayerStates[1].unk_174 = gPlayer2Controller->buttonDown;
    gMiniHudPlayerStates[2].unk_174 = gPlayer3Controller->buttonDown;
    gMiniHudPlayerStates[3].unk_174 = gPlayer4Controller->buttonDown;

    for (i = 0; i < 4; i++) {
        D_86003B5C = &gMiniHudPlayerStates[i];

        if (D_86003B5C->unk_000 == 0) {
            s32 temp = gMiniHudState;

            if ((temp != 0) && (temp != 2) && (temp != 3) && (temp != 5)) {
                D_86003B5C->unk_174 = 0;
                D_86003B5C->unk_17A = 0;
            }
        } else if (gMiniHudState == 2) {
            switch (D_86003B5C->unk_004.unk_168) {
                case 0:
                case 12:
                case 13:
                    if (GetRandomMod(0x64) < gMiniHudRandomChanceTable[gMenuState].unk_06) {
                        D_86003B5C->unk_17A = 0x8000;
                    }
                    break;

                case 5:
                case 7:
                    if (GetRandomMod(0x64) < gMiniHudRandomChanceTable[gMenuState].unk_04) {
                        D_86003B5C->unk_174 = 0x8000;
                    }
                    break;

                case 8:
                    if ((D_86003B5C->unk_004.unk_000.unk_040.unk_08 > 0x90000) &&
                        (GetRandomMod(0x64) < gMiniHudRandomChanceTable[gMenuState].unk_08)) {
                        D_86003B5C->unk_17A = 0x8000;
                    }
                    break;

                case 9:
                    if ((D_86003B5C->unk_004.unk_000.unk_040.unk_08 > 0xD0000) &&
                        (GetRandomMod(0x64) < gMiniHudRandomChanceTable[gMenuState].unk_08)) {
                        D_86003B5C->unk_17A = 0x8000;
                    }
                    break;

                case 10:
                    if ((D_86003B5C->unk_004.unk_000.unk_040.unk_08 > 0xB0000) &&
                        (GetRandomMod(0x64) < gMiniHudRandomChanceTable[gMenuState].unk_08)) {
                        D_86003B5C->unk_17A = 0x8000;
                    }
                    break;

                case 11:
                    if ((D_86003B5C->unk_004.unk_000.unk_040.unk_08 > 0xF0000) &&
                        (GetRandomMod(0x64) < gMiniHudRandomChanceTable[gMenuState].unk_08)) {
                        D_86003B5C->unk_17A = 0x8000;
                    }
                    break;
            }
        }
    }

    if (gMiniHudState == 2) {
        for (j = 0; j < 4; j++) {
            D_86003B5C = &gMiniHudPlayerStates[j];

            for (i = 1; i > 0; i--) {
                D_86003B5C->unk_176[i] = D_86003B5C->unk_176[i - 1];
                D_86003B5C->unk_17C[i] = D_86003B5C->unk_17C[i - 1];
            }
            D_86003B5C->unk_176[0] = D_86003B5C->unk_174;
            D_86003B5C->unk_17C[0] = D_86003B5C->unk_17A;
        }
    } else {
        for (j = 0; j < 4; j++) {
            D_86003B5C = &gMiniHudPlayerStates[j];

            for (i = 0; i < 2; i++) {
                D_86003B5C->unk_176[i] = 0;
                D_86003B5C->unk_17C[i] = 0;
            }
        }
    }
}

s32 MiniHud_HandleInput(void) {
    if (Stage_GetFadeState() != 0) {
        return -1;
    }

    Cont_StartReadInputs();
    Cont_ReadInputs();
    MenuInput_Init();

    if (gResultMenuVisible != 1) {
        MiniHud_UpdateControllerInput();
    }

    return 0;
}

void MiniHud_SetupCamera(void) {
    gMiniHudCamera = gMiniHudMainGraph->unk_00.unk_0C;
    SetProjectionInfo(gMiniHudCamera);
    gMiniHudCamAtY = 0x600;
    gMiniHudCamAtZ = 0;
    gMiniHudCamDist = 1000;

    gMiniHudCamera->unk_24.near = 100.0f;
    gMiniHudCamera->unk_24.far = 12800.0f;
    gMiniHudCamera->unk_24.fovy = 10.0f;

    gMiniHudCamera->unk_60.at.x = 0.0f;
    gMiniHudCamera->unk_60.at.y = 70.0f;
    gMiniHudCamera->unk_60.at.z = 0.0f;

    Camera_SetViewParameters(&gMiniHudCamera->unk_60.at, &gMiniHudCamera->unk_60.eye, gMiniHudCamDist, gMiniHudCamAtY, gMiniHudCamAtZ);
}

void MiniHud_UpdateCamera(void) {
    Camera_SetViewParameters(&gMiniHudCamera->unk_60.at, &gMiniHudCamera->unk_60.eye, gMiniHudCamDist, gMiniHudCamAtY, gMiniHudCamAtZ);
}

void MiniHud_RenderUI(s32 arg0) {
    s32 i;
    UNUSED u8 sp68[] = {
        0,
        0,
        30,
    };
    UNUSED u8 sp64[] = {
        0,
        0,
        150,
    };

    if (arg0 != 0) {
        gSPDisplayList(gDisplayListHead++, gPrefDL_Border);
        gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, gMiniHudAlpha);

        for (i = 0; i < 4; i++) {
            unk_D_86002A98* tmp = &gMiniHudTextureRects[i];

            if (gMiniHudPlayerStates[i].unk_000 == 0) {
                DrawUniformScaledTextureRect(i, tmp->unk_00, tmp->unk_02, 0.75f);
            } else {
                DrawUniformScaledTextureRect(-1 - i, tmp->unk_00, tmp->unk_02, 0.75f);
            }
        }

        gSPDisplayList(gDisplayListHead++, gPrefDL_End);
    }

    if (arg0 == 0) {
        DrawPanel(0x18, 0x16, 0x110, 0x90, 0x15);
        DrawPanel(0x18, 0xA5, 0x110, 0x36, 0x14B);
    }

    Text_ResetState();

    switch (arg0) {
        s32 sp50;
        s32 sp4C;
        char* temp_s0_2;

        case 1:
        case 2:
        case 3:
            break;

        case 0:
            Text_BeginRender();
            Text_SetFont(2, 0);
            Text_SetLineHeight(0xC);
            Text_SetEnvColor(0xFF, 0xFF, 0xFF, 0xFF);
            Text_SetPrimColor(0xF9, 0xF4, 0, 0xFF);
            Text_Print(0xA0 - (GetTextWidth(gMiniHudTextObj, GetMessageString(NULL, 0, gItemNamesBank, 0x15)) / 2), 0x20,
                          GetMessageString(NULL, 0, gItemNamesBank, 0x15));
            Text_SetEnvColor(0xFF, 0xFF, 0xFF, 0xFF);
            Text_SetPrimColor(0xFF, 0xFF, 0xFF, 0xFF);
            Text_Print(0x28, 0x34, GetMessageString(NULL, 0, gItemNamesBank, 0x16));
            Text_Print(0x28, 0x58, GetMessageString(NULL, 0, gItemNamesBank, 0x17));
            Text_Print(0x28, 0x7C, GetMessageString(NULL, 0, gItemNamesBank, 0x18));
            Text_SetEnvColor(0xC8, 0xC8, 0xFF, 0xFF);
            Text_SetPrimColor(0x50, 0x50, 0xFF, 0xFF);

            temp_s0_2 = GetMessageString(NULL, 0, gItemNamesBank, 0x5F);

            ParseStringAndMeasure(&sp50, &sp4C, GetMessageString(NULL, 0, gItemNamesBank, 0x16), temp_s0_2, 0xC);
            if (sp50 >= 0) {
                Text_Print(sp50 + 0x28, sp4C + 0x34, temp_s0_2);
            }

            ParseStringAndMeasure(&sp50, &sp4C, GetMessageString(NULL, 0, gItemNamesBank, 0x17), temp_s0_2, 0xC);
            if (sp50 >= 0) {
                Text_Print(sp50 + 0x28, sp4C + 0x58, temp_s0_2);
            }

            ParseStringAndMeasure(&sp50, &sp4C, GetMessageString(NULL, 0, gItemNamesBank, 0x18), temp_s0_2, 0xC);
            if (sp50 >= 0) {
                Text_Print(sp50 + 0x28, sp4C + 0x7C, temp_s0_2);
            }

            Text_SetEnvColor(0xC8, 0xC8, 0xFF, 0xFF);
            Text_SetPrimColor(0x50, 0x50, 0xFF, 0xFF);
            Text_Print(0xA2, 0xB2, GetMessageString(NULL, 0, gItemNamesBank, 0x19));
            Text_SetEnvColor(0xFF, 0xFF, 0xFF, 0xFF);
            Text_SetPrimColor(0xFF, 0x80, 0x80, 0xFF);
            Text_Print(0xA2, 0xC8, GetMessageString(NULL, 0, gItemNamesBank, 0x14));
            Text_SetEnvColor(0xFF, 0xFF, 0xFF, 0xFF);
            Text_SetPrimColor(0xFF, 0xFF, 0xFF, 0xFF);
            Text_Print(0x8B, 0xB2, GetMessageString(NULL, 0, gItemNamesBank, 0x5C));
            Text_Print(0x8B, 0xC8, GetMessageString(NULL, 0, gItemNamesBank, 0x5C));
            Text_EndRender();
            break;

        case 4:
            Text_BeginRender();
            Text_SetFont(0x20, -2);
            Text_SetEnvColor(0xFF, 0xFF, 0xFF, 0xFF);
            Text_SetPrimColor(0x1E, 0x1E, 0xFF, 0xFF);
            Text_Print(0xA0 - (GetTextWidth(gMiniHudTextObj, GetMessageString(NULL, 0, gItemNamesBank, 0x5A)) / 2), 0x64,
                          GetMessageString(NULL, 0, gItemNamesBank, 0x5A));
            Text_EndRender();
            break;
    }

    Text_SetupDL();

    if (arg0 == 0) {
        // D_800A7420 is gDisplayListHead under its second name (see variables.h).
        gSPDisplayList(D_800A7420++, gPrefDL_Border);
        DrawAnimatedSprite(0x74, 0xB0, gMiniHudDL_Panel1);
        DrawAnimatedSprite3(0x74, 0xC6, gMiniHudDL_Panel2);
        DrawDualTexturePanel(2, 0x19, 0xA6);
    }
}

static Gfx D_86002B90[] = {
    gsSPEndDisplayList(),
};

static u32 D_86002B98[] = {
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x000A000F, 0x00140014, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x0000000A, 0x00190021, 0x002A0033, 0x0036003B, 0x00000000, 0x00000000,
    0x00000000, 0x0000000A, 0x0019002A, 0x003B004B, 0x00550060, 0x00640067, 0x00000000, 0x00000000, 0x00000000,
    0x00140025, 0x003B0052, 0x00670076, 0x0082008B, 0x00900094, 0x00000000, 0x00000000, 0x00000014, 0x002F0046,
    0x00600079, 0x008D009F, 0x00A900B1, 0x00B600B9, 0x00000000, 0x00000000, 0x00140033, 0x0052006D, 0x0088009F,
    0x00B100C1, 0x00CA00D1, 0x00D400D6, 0x00000000, 0x00000014, 0x002F0052, 0x0071008D, 0x00A900BE, 0x00CF00D9,
    0x00E200E6, 0x00EA00EA, 0x00000000, 0x000A0025, 0x0046006D, 0x008D00AD, 0x00C400D6, 0x00E300EC, 0x00F100F4,
    0x00F600F7, 0x00000000, 0x0019003B, 0x00600088, 0x00A900C4, 0x00D900E6, 0x00F000F6, 0x00F900FB, 0x00FC00FC,
    0x0000000A, 0x002A0052, 0x0079009F, 0x00BE00D6, 0x00E600F2, 0x00F800FC, 0x00FD00FE, 0x00FE00FE, 0x00000019,
    0x003B0067, 0x008D00B1, 0x00CF00E3, 0x00F000F8, 0x00FC00FE, 0x00FE00FF, 0x00FF00FF, 0x00000021, 0x004B0076,
    0x009F00C1, 0x00D900EC, 0x00F600FC, 0x00FE00FE, 0x00FF00FF, 0x00FF00FF, 0x000A002A, 0x00550082, 0x00A900CA,
    0x00E200F1, 0x00F900FD, 0x00FE00FF, 0x00FF00FF, 0x00FF00FF, 0x000F0033, 0x0060008B, 0x00B100D1, 0x00E600F4,
    0x00FB00FE, 0x00FF00FF, 0x00FF00FF, 0x00FF00FF, 0x00140036, 0x00640090, 0x00B600D4, 0x00EA00F6, 0x00FC00FE,
    0x00FF00FF, 0x00FF00FF, 0x00FF00FF, 0x0014003B, 0x00670094, 0x00B900D6, 0x00EA00F7, 0x00FC00FE, 0x00FF00FF,
    0x00FF00FF, 0x00FF00FF,
};

static Vtx D_86002D98[] = {
    VTX(-25, 0, -25, 0, 0, 0x00, 0x00, 0x00, 0xFF),
    VTX(-25, 0, 25, 0, 1024, 0x00, 0x00, 0x00, 0xFF),
    VTX(25, 0, 25, 1024, 1024, 0x00, 0x00, 0x00, 0xFF),
    VTX(25, 0, -25, 1024, 0, 0x00, 0x00, 0x00, 0xFF),
};

static Gfx D_86002DD8[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_2CYCLE),
    gsDPSetRenderMode(G_RM_ZB_XLU_SURF, G_RM_ZB_XLU_SURF2),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsSPClearGeometryMode(G_CULL_BACK | G_LIGHTING),
    gsSPSetGeometryMode(G_ZBUFFER),
    gsDPSetCombineMode(G_CC_MODULATEIA_PRIM, G_CC_PASS2),
    gsDPSetPrimColor(0, 0, 0, 0, 0, 200),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPLoadTextureBlock(D_86002B98, G_IM_FMT_IA, G_IM_SIZ_16b, 16, 16, 0, G_TX_MIRROR | G_TX_WRAP,
                         G_TX_MIRROR | G_TX_WRAP, 4, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsSPVertex(D_86002D98, 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsSPEndDisplayList(),
};

void func_86000C10(void) {
}

void MiniHud_DrawPlayerIndicators(void) {
    Gfx* gfx = gDisplayListHead;
    Mtx* var_s1 = (Mtx*)GfxAlloc(sizeof(MtxF) * 4);
    Mtx sp100;
    Mtx spC0;
    UNUSED Mtx sp80;
    f32 temp_f20;
    s32 i;

    for (i = 0; i < 4; i++) {
        gCurrentPlayerGraph = &gMiniHudPlayerStates[i].unk_004;
        temp_f20 = (410.0f - gCurrentPlayerGraph->unk_000.unk_0A8[0].unk_04.y) / 510.0f;
        guTranslate(&sp100, gCurrentPlayerGraph->unk_000.unk_0A8[0].unk_04.x, 0.0f, 0.0f);
        guScale(&spC0, temp_f20, temp_f20, temp_f20);
        guMtxCatL(&spC0, &sp100, var_s1);

        gSPMatrix(gfx++, var_s1, G_MTX_PUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(gfx++, D_86002DD8);
        gSPPopMatrix(gfx++, G_MTX_MODELVIEW);
        var_s1++;
    }

    gDisplayListHead = gfx;
}

void MiniHud_MainLoop(s32 arg0) {
    Stage_BeginDisplayList();
    Gfx_FillDepthRectangle(&gDisplayListHead, 0, 0, 0x140, 0xF0);
    Gfx_DrawTilemap(gMiniHudTilemap);

    if (gResultMenuVisible != 1) {
        Gfx_FinishFrame();
    }

    Fragment2_1_Update();
    Graph_SetTextureState(gMiniHudMainGraph);
    gDisplayListHead = Gfx_ApplyProjection(gDisplayListHead);
    MiniHud_DrawPlayerIndicators();

    if (gResultConfirmPressed == 0) {
        MiniHud_RenderUI(arg0);
    }

    ResultScreen_UpdateAndRender();
    Stage_Advance();

    gMiniHudFrameCount++;
}

void MiniHud_UpdateAnimations(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        gCurrentPlayerGraph = gCurrentPlayerWheel = &D_86003598[i];

        if (gCurrentPlayerGraph->unk_000.unk_024.y > 140.0f) {
            gCurrentPlayerGraph->unk_000.unk_024.y -= 2.0f;
        }

        switch (gCurrentPlayerWheel->unk_16C) {
            case 0:
                if (gCurrentPlayerGraph->unk_000.unk_01E.y < 0x800) {
                    gCurrentPlayerGraph->unk_000.unk_01E.y += 0x400;
                } else {
                    gCurrentPlayerWheel->unk_16C = 1;
                }
                break;

            case 1:
                if (gCurrentPlayerGraph->unk_000.unk_01E.y > 0) {
                    gCurrentPlayerGraph->unk_000.unk_01E.y -= 0x200;
                } else {
                    gCurrentPlayerWheel->unk_16C = 2;
                }
                break;

            case 2:
            default:
                gCurrentPlayerGraph->unk_000.unk_01E.y = 0;
                break;
        }
    }
}

s32 MiniHud_InitAndWait(void) {
    s32 var_s0_2;
    s32 i;

    Stage_AdvanceN(0xA);
    Stage_FadeIn(0x10);

    for (i = 0; i < 4; i++) {
        D_86003B5C = &gMiniHudPlayerStates[i];
        gCurrentPlayerGraph = &D_86003B5C->unk_004;
        GraphNode_TriggerAction(&gCurrentPlayerGraph->unk_000, 0);
        gCurrentPlayerGraph->unk_000.unk_040.unk_0C = 0x10000;
        gCurrentPlayerGraph->unk_000.unk_040.unk_08 = (GetRandomMod(0x14) << 0x10);
        gMiniHudActionFlags[i] = 0;
    }

    for (i = 0; i < 4; i++) {
        D_86003B5C = &gMiniHudPlayerStates[i];
        D_86003B5C->unk_000 = (gMiniHudColorDefaults[i] == 0) ? 0 : gMenuState + 1;
    }

    gMiniHudState = 0;

    var_s0_2 = true;
    while (var_s0_2 == true) {
        if (MiniHud_HandleInput() == 0) {
            if (gPlayer1Controller->buttonPressed & 0x1000) {
                var_s0_2 = false;
            }

            if ((gMenuCursorX == 0) && (gPlayer1Controller->buttonPressed & 0x4000)) {
                PlaySoundEffect(3);
                SetResultFlag(2);
                return -1;
            }
        }

        MiniHud_MainLoop(gMiniHudState);
    }

    return 0;
}

void MiniHud_PlayIntro(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        D_86003B5C = &gMiniHudPlayerStates[i];
        gCurrentPlayerGraph = &D_86003B5C->unk_004;
        GraphNode_TriggerAction(&gCurrentPlayerGraph->unk_000, 0);
        gCurrentPlayerGraph->unk_000.unk_040.unk_0C = 0x10000;
        gCurrentPlayerGraph->unk_000.unk_040.unk_08 = GetRandomMod(0x14) << 0x10;
        gMiniHudActionFlags[i] = 0;
    }

    gMiniHudIntroActive = 1;
    gMiniHudIntroTimer = 90;
    Fragment2_1_SetStartFlag(1);
    gMiniHudState = 1;

    while (gMiniHudIntroActive == 1) {
        switch (Fragment2_1_GetResult()) {
            case 1:
            case 2:
            case 3:
                PlaySoundIfEnabled(0x20001, 0, 0);
                break;

            case 0:
                gMiniHudIntroActive = 0;
                break;
        }

        MiniHud_UpdateAnimations();
        MiniHud_HandleInput();
        MiniHud_MainLoop(gMiniHudState);
    }
}

void MiniHud_TriggerAction_5(s16 arg0) {
    switch (arg0) {
        case 0:
        case 1:
            PlaySoundIfEnabled(0x20006, D_86003B5C->unk_18A + 1, 4);
            break;

        case 2:
            PlaySoundIfEnabled(0x20005, D_86003B5C->unk_18A + 1, 4);
            break;

        default:
            PlaySoundIfEnabled(0x20004, D_86003B5C->unk_18A + 1, 4);
            break;
    }

    D_86003B5C->unk_004.unk_168 = 5;
    D_86003B5C->unk_004.unk_16A = arg0;

    GraphNode_TriggerAction(&gCurrentPlayerGraph->unk_000, 8);

    gCurrentPlayerGraph->unk_000.unk_040.unk_08 = 0;
    gCurrentPlayerGraph->unk_000.unk_040.unk_0C = 0x10000;
}

void MiniHud_TriggerAction_6(void) {
    D_86003B5C->unk_004.unk_168 = 6;
    GraphNode_TriggerAction(&gCurrentPlayerGraph->unk_000, 9);
    gCurrentPlayerGraph->unk_000.unk_040.unk_08 = 0;
    gCurrentPlayerGraph->unk_000.unk_040.unk_0C = 0x10000;
}

void MiniHud_TriggerAction_7(void) {
    D_86003B5C->unk_004.unk_168 = 7;
    GraphNode_TriggerAction(&gCurrentPlayerGraph->unk_000, 0xA);
    gCurrentPlayerGraph->unk_000.unk_040.unk_08 = 0;
    gCurrentPlayerGraph->unk_000.unk_040.unk_0C = 0x10000;
}

void MiniHud_TriggerAction_8(void) {
    D_86003B5C->unk_004.unk_168 = 8;
    GraphNode_TriggerAction(&gCurrentPlayerGraph->unk_000, 0xB);
    gCurrentPlayerGraph->unk_000.unk_040.unk_08 = 0;
    gCurrentPlayerGraph->unk_000.unk_040.unk_0C = 0x10000;
}

void MiniHud_TriggerAction_9(void) {
    D_86003B5C->unk_004.unk_168 = 9;
    GraphNode_TriggerAction(&gCurrentPlayerGraph->unk_000, 0xC);
    gCurrentPlayerGraph->unk_000.unk_040.unk_08 = 0;
    gCurrentPlayerGraph->unk_000.unk_040.unk_0C = 0x10000;
}

void MiniHud_TriggerAction_10(void) {
    D_86003B5C->unk_004.unk_168 = 0xA;
    GraphNode_TriggerAction(&gCurrentPlayerGraph->unk_000, 0xD);
    gCurrentPlayerGraph->unk_000.unk_040.unk_08 = 0;
    gCurrentPlayerGraph->unk_000.unk_040.unk_0C = 0x10000;
}

void MiniHud_TriggerAction_11(void) {
    D_86003B5C->unk_004.unk_168 = 0xB;
    GraphNode_TriggerAction(&gCurrentPlayerGraph->unk_000, 0xE);
    gCurrentPlayerGraph->unk_000.unk_040.unk_08 = 0;
    gCurrentPlayerGraph->unk_000.unk_040.unk_0C = 0x10000;
}

void MiniHud_HandleActionTimeout(s32 arg0) {
    s32 i;

    gMiniHudActionFlags[arg0] = 0;

    for (i = 0; i < 2; i++) {
        if (D_86003B5C->unk_17C[i] & 0x8000) {
            MiniHud_TriggerAction_5(i);
            return;
        }
    }

    D_86003B5C->unk_004.unk_168 = 0xC;
    GraphNode_TriggerAction(&gCurrentPlayerGraph->unk_000, 5);
    gCurrentPlayerGraph->unk_000.unk_040.unk_08 = 0;
    gCurrentPlayerGraph->unk_000.unk_040.unk_0C = 0x10000;
}

void MiniHud_TriggerAction_6_Alt(s32 arg0) {
    gMiniHudActionFlags[arg0] = 0;
    D_86003B5C->unk_004.unk_168 = 0xD;
    GraphNode_TriggerAction(&gCurrentPlayerGraph->unk_000, 6);
    gCurrentPlayerGraph->unk_000.unk_040.unk_08 = 0;
    gCurrentPlayerGraph->unk_000.unk_040.unk_0C = 0x10000;
}

void MiniHud_TriggerAction_0_Alt(s32 arg0) {
    gMiniHudActionFlags[arg0] = 0;
    D_86003B5C->unk_004.unk_168 = 0;
    GraphNode_TriggerAction(&gCurrentPlayerGraph->unk_000, 0);
    gCurrentPlayerGraph->unk_000.unk_040.unk_08 = 0;
    gCurrentPlayerGraph->unk_000.unk_040.unk_0C = 0x10000;
}

void MiniHud_UpdatePlayerState(s32 arg0) {
    D_86003B5C = &gMiniHudPlayerStates[arg0];
    gCurrentPlayerWheel = &D_86003598[arg0];
    gCurrentPlayerGraph = &D_86003B5C->unk_004;

    if (gResultMenuVisible != 1) {
        switch (D_86003B5C->unk_004.unk_168) {
            case 12:
                if (D_86003B5C->unk_17C[1] & 0x8000) {
                    MiniHud_TriggerAction_5(2);
                } else if (Anim_HasReachedEnd(&gCurrentPlayerGraph->unk_000)) {
                    MiniHud_TriggerAction_6_Alt(arg0);
                }
                break;

            case 13:
                if (D_86003B5C->unk_17C[1] & 0x8000) {
                    MiniHud_TriggerAction_5(3);
                } else if (Anim_HasReachedEnd(&gCurrentPlayerGraph->unk_000)) {
                    MiniHud_TriggerAction_0_Alt(arg0);
                }
                break;

            case 0:
                if (D_86003B5C->unk_17C[1] & 0x8000) {
                    if (D_86003B5C->unk_18C == 1) {
                        MiniHud_TriggerAction_5(2);
                        D_86003B5C->unk_18C = 0;
                    } else {
                        MiniHud_TriggerAction_5(4);
                    }
                }
                break;

            case 5:
                if (Anim_HasReachedEnd(&gCurrentPlayerGraph->unk_000)) {
                    if (D_86003B5C->unk_176[1] & 0x8000) {
                        MiniHud_TriggerAction_7();
                    } else {
                        MiniHud_TriggerAction_6();
                    }
                }
                break;

            case 7:
                if (Anim_HasReachedEnd(&gCurrentPlayerGraph->unk_000)) {
                    if (D_86003B5C->unk_176[1] & 0x8000) {
                        s16 tmp = D_86003B5C->unk_004.unk_16A;

                        if (tmp < 2) {
                            MiniHud_TriggerAction_10();
                        } else if (tmp == 2) {
                            MiniHud_TriggerAction_9();
                        } else {
                            MiniHud_TriggerAction_11();
                        }
                    } else {
                        MiniHud_TriggerAction_8();
                    }
                }
                break;

            case 6:
            case 8:
            case 9:
            case 10:
            case 11:
                if (Anim_HasReachedEnd(&gCurrentPlayerGraph->unk_000)) {
                    MiniHud_HandleActionTimeout(arg0);
                }
                break;

            case 1:
                if (Anim_HasReachedEnd(&gCurrentPlayerGraph->unk_000)) {
                    GraphNode_TriggerAction(&gCurrentPlayerGraph->unk_000, 7);
                    gCurrentPlayerGraph->unk_000.unk_040.unk_08 = 0;
                    gCurrentPlayerGraph->unk_000.unk_040.unk_0C = 0x10000;
                }
                break;

            default:
                if (Anim_HasReachedEnd(&gCurrentPlayerGraph->unk_000)) {
                    GraphNode_TriggerAction(&gCurrentPlayerGraph->unk_000, 0);
                    gCurrentPlayerGraph->unk_000.unk_040.unk_08 = 0;
                    gCurrentPlayerGraph->unk_000.unk_040.unk_0C = 0x10000;
                    gMiniHudActionFlags[arg0] = 0;
                }
                break;
        }

        if (((D_86003B5C->unk_004.unk_168 == 9) && ((gCurrentPlayerGraph->unk_000.unk_040.unk_08 >> 0x10) == 2)) ||
            ((D_86003B5C->unk_004.unk_168 == 10) && ((gCurrentPlayerGraph->unk_000.unk_040.unk_08 >> 0x10) == 2)) ||
            ((D_86003B5C->unk_004.unk_168 == 11) && ((gCurrentPlayerGraph->unk_000.unk_040.unk_08 >> 0x10) == 2))) {
            if (gMiniHudActionFlags[arg0] == 0) {
                gCurrentPlayerWheel->unk_16A++;
                gMiniHudActionFlags[arg0] = 1;
                GraphNode_TriggerAction(&gCurrentPlayerWheel->unk_000, 0);
                gCurrentPlayerWheel->unk_000.unk_040.unk_0C = 0x10000;
                gCurrentPlayerWheel->unk_000.unk_040.unk_08 = 0;
                PlaySoundIfEnabled(0x20008, arg0, 4);
            }
        }

        if (gResultMenuVisible != 1) {
            HpWheel_SetDigitsSmooth(arg0, gCurrentPlayerWheel->unk_16A);
        }

        if (D_86003B5C->unk_188 > 0) {
            D_86003B5C->unk_188--;
            if (D_86003B5C->unk_188 == 0) {
                GraphNode_SetColorRGBA(&D_86003B5C->unk_004.unk_000, 0xFF, 0xFF, 0xFF, 0);
            }
        }
    }
}

void MiniHud_PlayGame(void) {
    s32 i;
    s32 temp_lo;
    s32 temp_v1;
    s32 var_s6 = 1;

    PlaySoundIfEnabled(0x20002, 0, 0);

    for (i = 0; i < 4; i++) {
        D_86003B5C = &gMiniHudPlayerStates[i];
        gCurrentPlayerGraph = &D_86003B5C->unk_004;

        D_86003B5C->unk_004.unk_168 = 0;
        GraphNode_TriggerAction(&gCurrentPlayerGraph->unk_000, 0);
        gCurrentPlayerGraph->unk_000.unk_040.unk_0C = 0x10000;

        gMiniHudActionFlags[i] = 0;

        D_86003B5C->unk_18C = 1;
    }

    gMiniHudGameTimer = 0;
    D_86003B78 = 0;
    gMiniHudState = 2;

    while (var_s6 != 0) {
        MiniHud_HandleInput();
        MiniHud_UpdateCamera();

        if (gMiniHudGameTimer == 0xF) {
            ResultScreen_SetAnimation(10);
        }

        if (gResultMenuVisible != 1) {
            for (i = 0; i < 4; i++) {
                MiniHud_UpdatePlayerState(i);
            }

            MiniHud_UpdateAnimations();

            gMiniHudGameTimer++;
            if (gMiniHudGameTimer >= 0x258) {
                PlaySoundIfEnabled(0x20009, 0, 0);
                var_s6 = 0;
            } else {
                temp_v1 = 0x258 - gMiniHudGameTimer;
                if ((temp_v1 % 30) == 0) {
                    temp_lo = temp_v1 / 30;
                    if ((temp_lo < 6) && (temp_lo > 0)) {
                        PlaySoundIfEnabled(0x2000A, 0, 0);
                        if (1) {}
                        if (1) {}
                        if (1) {}
                    }
                }
            }
        }

        if (gResultFlag_Special != 0) {
            var_s6 = 0;
        }

        MiniHud_MainLoop(gMiniHudState);
    }

    Stage_SetFadeColor(0xA);
}

s32 MiniHud_CheckAllIdle(void) {
    s32 var_v0 = 0;
    s32 i;

    for (i = 0; i < 4; i++) {
        D_86003B5C = &gMiniHudPlayerStates[i];
        switch (D_86003B5C->unk_004.unk_168) {
            case 5:
            case 6:
            case 7:
            case 8:
            case 9:
            case 10:
            case 11:
                break;

            default:
                var_v0++;
                break;
        }
    }

    if (var_v0 == 4) {
        return 1;
    }

    return 0;
}

void MiniHud_ResolveWinner(void) {
    s32 i;
    s32 j;
    s32 var_s1;
    s32 var_s5;

    var_s5 = 1;
    gMiniHudState = 3;
    var_s1 = 1;

    while (var_s1 != 0) {
        MiniHud_HandleInput();
        MiniHud_UpdateCamera();

        for (i = 0; i < 4; i++) {
            MiniHud_UpdatePlayerState(i);
        }

        if (MiniHud_CheckAllIdle() != 0) {
            var_s1 = 0;
        }

        MiniHud_MainLoop(gMiniHudState);

        if (gResultFlag_Special != 0) {
            return;
        }
    }

    gMiniHudMaxWheelValue = 0;

    for (i = 0; i < 4; i++) {
        if (D_86003598[i].unk_16A >= gMiniHudMaxWheelValue) {
            gMiniHudMaxWheelValue = D_86003598[i].unk_16A;
        }
    }

    gMiniHudWinnerCount = 0;

    for (i = 0; i < 4; i++) {
        if ((gMiniHudMaxWheelValue == D_86003598[i].unk_16A) && (gMiniHudMaxWheelValue != 0)) {
            IncrementPlayerScore(i);
            gMiniHudWinnerCount++;
        }
    }

    for (i = 0; i < 4; i++) {
        D_86003B5C = &gMiniHudPlayerStates[i];
        gCurrentPlayerGraph = &D_86003B5C->unk_004;
        if ((gMiniHudMaxWheelValue == D_86003598[i].unk_16A) && (gMiniHudMaxWheelValue > 0)) {
            D_86003B5C->unk_004.unk_168 = 1;
            GraphNode_TriggerAction(&gCurrentPlayerGraph->unk_000, 7);
            gCurrentPlayerGraph->unk_000.unk_040.unk_08 = 0;
        } else {
            D_86003B5C->unk_004.unk_168 = 2;
            GraphNode_TriggerAction(&gCurrentPlayerGraph->unk_000, 0);
            gCurrentPlayerGraph->unk_000.unk_040.unk_08 = GetRandomMod(5) << 0x10;
        }
        gCurrentPlayerGraph->unk_000.unk_040.unk_0C = 0x10000;
    }

    j = 30;
    while (j > 0) {
        MiniHud_HandleInput();
        MiniHud_UpdateCamera();

        for (i = 0; i < 4; i++) {
            MiniHud_UpdatePlayerState(i);
        }

        MiniHud_MainLoop(gMiniHudState);

        if (gResultFlag_Special != 0) {
            return;
        }

        if (gResultMenuVisible != 1) {
            j -= 1;
        }
    }

    SetResultFlag(1);

    while (var_s5 != 0) {
        MiniHud_HandleInput();
        MiniHud_UpdateCamera();

        for (i = 0; i < 4; i++) {
            MiniHud_UpdatePlayerState(i);
        }

        for (i = 0; i < 4; i++) {
            D_86003B5C = &gMiniHudPlayerStates[i];
            if (D_86003B5C->unk_17A & 0x8000) {
                var_s5 = 0;
            }
        }

        MiniHud_MainLoop(gMiniHudState);

        if (gResultFlag_Special != 0) {
            return;
        }
    }
}

void MiniHud_Exit(void) {
    s32 i;
    s32 j;

    Stage_SetFadeColor(30);
    Stage_FadeOut(30);

    for (i = 0; i < 30; i++) {
        MiniHud_HandleInput();

        for (j = 0; j < 4; j++) {
            MiniHud_UpdatePlayerState(j);
        }

        MiniHud_MainLoop(gMiniHudState);
    }
}

void MiniHud_WaitFrames(s32 arg0) {
    s32 i;

    gMiniHudState = 6;

    for (i = 0; i < arg0; i++) {
        MiniHud_HandleInput();
        MiniHud_MainLoop(gMiniHudState);
    }
}

void MiniHud_WaitForExit(void) {
    s32 i;

    gMiniHudState = 5;

    while (gResultExitPending == 0) {
        if ((gMenuCursorX == 1) && (gMiniHudAlpha > 0)) {
            gMiniHudAlpha -= 10;
            if (gMiniHudAlpha < 0) {
                gMiniHudAlpha = 0;
            }
        }

        for (i = 0; i < 4; i++) {
            MiniHud_UpdatePlayerState(i);
        }

        MiniHud_HandleInput();
        MiniHud_MainLoop(gMiniHudState);
    }
}

void MiniHud_InitGraphics(void) {
    s32 i;
    MemoryBlock* temp_v0;

    temp_v0 = (MemoryBlock*)state_pool_try_init(main_pool_get_available(), 0);
    gMiniHudMainGraph = (unk_D_86002F34*)process_geo_layout(temp_v0, gMiniHudGeoLayout);
    mem_pool_resize_block(temp_v0);
    Graph_InitRoots();
    AssetManager_LoadArchives();
    gMiniHudAlpha = 0xFF;
    gMiniHudGeoLayoutObj = (unk_D_86002F30*)GeoLayout_LoadById(0xAD);

    for (i = 0; i < 4; i++) {
        D_86003B5C = &gMiniHudPlayerStates[i];
        gCurrentPlayerGraph = &D_86003B5C->unk_004;

        Graph_AddToRootList0(&gCurrentPlayerGraph->unk_000);
        GraphNode_InitChild(&gCurrentPlayerGraph->unk_000, 0, 0xAD, gMiniHudGeoLayoutObj->unk_08->unk_00[0]);

        gCurrentPlayerGraph->unk_000.unk_024.x = (i - 1.5f) * D_86002A94;

        gCurrentPlayerGraph->unk_000.unk_024.y = 0.0f;
        gCurrentPlayerGraph->unk_000.unk_024.z = 0.0f;
        gCurrentPlayerGraph->unk_000.unk_030.x = 0.8f;
        gCurrentPlayerGraph->unk_000.unk_030.y = 0.8f;
        gCurrentPlayerGraph->unk_000.unk_030.z = 0.8f;

        D_86003B5C->unk_182 = 0;
        D_86003B5C->unk_184 = 0;
        D_86003B5C->unk_186 = 0;
        D_86003B5C->unk_188 = 0;
        D_86003B5C->unk_18A = i;

        if (i == 0) {
            D_86003B5C->unk_000 = 0;
        } else {
            D_86003B5C->unk_000 = gMenuState + 1;
        }

        GraphNode_TriggerAction(&gCurrentPlayerGraph->unk_000, 0);

        gCurrentPlayerGraph->unk_000.unk_040.unk_08 = GetRandomMod(5) << 0x10;
        gCurrentPlayerGraph->unk_000.unk_01E.y = -0x2800;
    }

    gMiniHudGeoLayoutObj = (unk_D_86002F30*)GeoLayout_LoadById(0xAE);

    for (i = 0; i < 4; i++) {
        gCurrentPlayerWheel = &D_86003598[i];
        gCurrentPlayerGraph = gCurrentPlayerWheel;

        Graph_AddToRootList0(&gCurrentPlayerGraph->unk_000);
        GraphNode_InitChild(&gCurrentPlayerGraph->unk_000, 0, 0xAE, gMiniHudGeoLayoutObj->unk_08->unk_00[0]);
        gCurrentPlayerGraph->unk_000.unk_024.x = (i - 1.5f) * D_86002A94;
        gCurrentPlayerGraph->unk_000.unk_024.z = 0.0f;
        gCurrentPlayerGraph->unk_000.unk_024.y = 200.0f;
        gCurrentPlayerGraph->unk_000.unk_01E.y = -0x8000;
        gCurrentPlayerGraph->unk_000.unk_030.x = 1.4f;
        gCurrentPlayerGraph->unk_000.unk_030.y = 1.4f;
        gCurrentPlayerGraph->unk_000.unk_030.z = 1.4f;
        gCurrentPlayerWheel->unk_168 = 0;
        gCurrentPlayerWheel->unk_16A = 0;
        gCurrentPlayerWheel->unk_16C = 0;
        HpWheel_SetDigits(i, 0);
        gCurrentPlayerWheel->unk_000.modelPhase = i;
        GraphNode_TriggerAction(&gCurrentPlayerGraph->unk_000, 0);
        Anim_ClearChannelState(&gCurrentPlayerGraph->unk_000);
    }

    gMiniHudTilemap = Asset_Load(0, (void*)&D_124570, (void*)fragment7_ROM_START, 0);
    MiniHud_SetupCamera();
    Fragment2_1_Init();
}

void MiniHud_Init(UNUSED s32 arg0, UNUSED s32 arg1) {
    Stage* sp24;

    main_pool_push_state('MINI');

    Gfx_InitBuffers(0x20000, 0);
    sp24 = (Stage*)Stage_Create(0, 1, 3, 1, 2, 1);
    gMiniHudTextObj = Text_Init(0x36, 0);

    ASSET_LOAD(D_1000000, common_menu1_ui, 0);
    FRAGMENT_LOAD(fragment31);

    Fragment_Load((((u32)D_8D000000 & 0x0FF00000) >> 0x14) - 0x10, _5C7A70_ROM_START, _5C7A70_ROM_END);

    MiniHud_InitGraphics();
    ResultScreen_Init();
    Stage_Set(sp24);

    if (MiniHud_InitAndWait() != -1) {
        Stage_SetFadeColor(0x3C);
        MiniHud_WaitFrames(5);
        MiniHud_PlayIntro();
        MiniHud_PlayGame();

        if (gResultFlag_Special == 0) {
            MiniHud_ResolveWinner();
        }

        if (gResultFlag_Special == 0) {
            MiniHud_WaitForExit();
        }
    }

    MiniHud_Exit();
    Stage_Destroy();
    FontManager_Free();
    Gfx_FreeBuffers();

    main_pool_pop_state('MINI');

    GetCurrentOptionCount();
}
