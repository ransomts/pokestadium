#include "fragment39.h"
#include "src/1CF30.h"
#include "src/2E110.h"
#include "src/fragments/2/fragment2.h"

static unk_D_8250A480 gMessageBox;
static unk_D_8250A498 gOptionMenu;
static char* gOptionMenuItems[9];

void MessageBox_SetBank(char** arg0) {
    gMessageBox.unk_00 = 0;
    gMessageBox.unk_02 = 0;
    gMessageBox.unk_14 = arg0;
}

s32 MessageBox_GetState(void) {
    return gMessageBox.unk_00;
}

void MessageBox_SetState(s16 arg0) {
    unk_D_8250A480* ptr = &gMessageBox;

    ptr->unk_00 = arg0;

    switch (ptr->unk_00) {
        case 0:
            ptr->unk_02 = 0;
            ptr->unk_0C = 0;
            ptr->unk_10 = 0.0f;
            break;

        case 1:
            ptr->unk_02 = 0xA;
            ptr->unk_04 = -0xF8;
            ptr->unk_06 = 0x5A;
            ptr->unk_08 = 0x280;
            ptr->unk_0A = 0x15E;
            ptr->unk_10 = 0.0f;
            break;

        case 2:
            ptr->unk_02 = 0x12C;
            ptr->unk_04 = 0xBC;
            ptr->unk_08 = 0x5C;
            ptr->unk_0C = 0;
            break;

        case 3:
            ptr->unk_02 = 0xA;
            ptr->unk_10 = 0.0f;
            break;
    }
}

void func_82504930(unk_D_8250A480* arg0) {
    arg0->unk_02--;
    arg0->unk_04 = ((arg0->unk_02 * -0x1B4) / 10) + 0xBC;
    arg0->unk_08 = ((arg0->unk_02 * 0x224) / 10) + 0x5C;
    if (arg0->unk_02 <= 0) {
        MessageBox_SetState(2);
    }
}

void func_82504A08(unk_D_8250A480* arg0) {
    arg0->unk_02 = 0x12C;
    arg0->unk_10 = 0.0f;
    if (arg0->unk_02 <= 0) {
        arg0->unk_0C += 0x1000;
        arg0->unk_10 += 0.05f;
        if (arg0->unk_10 > 4.0f) {
            arg0->unk_10 = 4.0f;
        }
    }
}

void func_82504A68(unk_D_8250A480* arg0) {
    arg0->unk_02--;
    arg0->unk_04 = ((arg0->unk_02 * -0x1C4) / 10) + 0x280;
    arg0->unk_08 = ((arg0->unk_02 * 0x224) / 10) - 0x1C8;
    if (arg0->unk_02 <= 0) {
        MessageBox_SetState(0);
    }
}

void SelectionScreen_HandleInput(void) {
    unk_D_8250A480* ptr = &gMessageBox;

    if (ptr->unk_00 != 0) {
        switch (ptr->unk_00) {
            case 1:
                func_82504930(ptr);
                break;
            case 2:
                func_82504A08(ptr);
                break;
            case 3:
                func_82504A68(ptr);
                break;
        }
    }
}

void Gfx_DrawBorderedBox(s16 arg0, s16 arg1, s16 arg2, s16 arg3, u8 arg4, u8 arg5, u8 arg6, u8 arg7) {
    s16 sp48;
    s16 temp_s0_32;
    s16 var_s2;
    s16 var_s3;

    if (arg2 >= 0x20) {
        var_s3 = 0x10;
    } else {
        var_s3 = arg2 / 2;
    }

    if (arg3 >= 0x20) {
        var_s2 = 0x10;
    } else {
        var_s2 = arg3 / 2;
    }

    sp48 = arg2 - (var_s3 * 2);
    temp_s0_32 = arg3 - (var_s2 * 2);

    gSPDisplayList(gDisplayListHead++, gPrefDL_Border);
    gDPSetEnvColor(gDisplayListHead++, arg4, arg5, arg6, arg7);
    gDPLoadTextureBlock_4b(gDisplayListHead++, D_30CD490, G_IM_FMT_I, 16, 16, 0, G_TX_NOMIRROR | G_TX_WRAP,
                           G_TX_NOMIRROR | G_TX_WRAP, 5, 5, G_TX_NOLOD, G_TX_NOLOD);

    Gfx_DrawTextureRect(arg0, arg1, var_s3, var_s2, 0, 0, 0x4000 / var_s3, 0x4000 / var_s2, 0);

    gDPLoadTextureBlock_4b(gDisplayListHead++, D_30CD510, G_IM_FMT_I, 16, 16, 0, G_TX_NOMIRROR | G_TX_WRAP,
                           G_TX_NOMIRROR | G_TX_WRAP, 5, 5, G_TX_NOLOD, G_TX_NOLOD);

    Gfx_DrawTextureRect((arg0 + arg2) - var_s3, arg1, var_s3, var_s2, 0, 0, 0x4000 / var_s3, 0x4000 / var_s2, 0);

    gDPLoadTextureBlock_4b(gDisplayListHead++, D_30CD390, G_IM_FMT_I, 16, 16, 0, G_TX_NOMIRROR | G_TX_WRAP,
                           G_TX_NOMIRROR | G_TX_WRAP, 5, 5, G_TX_NOLOD, G_TX_NOLOD);

    Gfx_DrawTextureRect(arg0, (arg1 + arg3) - var_s2, var_s3, var_s2, 0, 0, 0x4000 / var_s3, 0x4000 / var_s2, 0);

    gDPLoadTextureBlock_4b(gDisplayListHead++, D_30CD410, G_IM_FMT_I, 16, 16, 0, G_TX_NOMIRROR | G_TX_WRAP,
                           G_TX_NOMIRROR | G_TX_WRAP, 5, 5, G_TX_NOLOD, G_TX_NOLOD);

    Gfx_DrawTextureRect((arg0 + arg2) - var_s3, (arg1 + arg3) - var_s2, var_s3, var_s2, 0, 0, 0x4000 / var_s3,
                  0x4000 / var_s2, 0);

    gSPDisplayList(gDisplayListHead++, gPrefDL_Fill);

    if ((sp48 > 0) && (temp_s0_32 > 0)) {
        Gfx_FillRectRGBA(arg0 + var_s3, arg1, sp48, var_s2, arg4, arg5, arg6, arg7);
        Gfx_FillRectRGBA(arg0, arg1 + var_s3, arg2, temp_s0_32, arg4, arg5, arg6, arg7);
        Gfx_FillRectRGBA(arg0 + var_s3, arg1 + var_s3 + temp_s0_32, sp48, var_s2, arg4, arg5, arg6, arg7);
    } else if (sp48 > 0) {
        Gfx_FillRectRGBA(arg0 + var_s3, arg1, sp48, arg3, arg4, arg5, arg6, arg7);
    } else if (temp_s0_32 > 0) {
        Gfx_FillRectRGBA(arg0, arg1 + var_s2, arg2, temp_s0_32, arg4, arg5, arg6, arg7);
    }

    gSPDisplayList(gDisplayListHead++, gPrefDL_End);
}

void Text_PrintWavy(s16 arg0, s16 arg1, s8* arg2, f32 arg3, s16 arg4) {
    s16 var_s2;
    s8* var_v1;
    s32 i;
    char sp50[4];
    s16 tmp;

    var_s2 = 0;
    while (*arg2) {
        var_v1 = sp50;
        if (*arg2 < 0) {
            for (i = 0; i < 2; i++) {
                *var_v1++ = *arg2++;
            }
            *var_v1 = '\x00';
        } else {
            *var_v1++ = *arg2++;
            *var_v1++ = 0;
        }

        tmp = SINS(arg4 + var_s2) * arg3;
        Text_Print(arg0, arg1 + tmp, sp50);
        var_s2 += 0x3000;
        arg0 += 0x18;
    }
}

void MessageBox_Render(void) {
    UNUSED s32 pad;
    unk_D_8250A480* ptr = &gMessageBox;
    char* sp2C = GetMessageString(NULL, 0, ptr->unk_14, 0);
    char* sp28 = GetMessageString(NULL, 0, ptr->unk_14, 1);

    if (ptr->unk_00 != 0) {
        Gfx_DrawBorderedBox(ptr->unk_04, ptr->unk_06, 0xF8, 0x2C, 0x1E, 0x1E, 0x82, 0x80);
        Gfx_DrawBorderedBox(ptr->unk_08, ptr->unk_0A, 0x1C8, 0x2C, 0x64, 0, 0x50, 0x80);
        Text_ResetState();
        Text_SetFont(0x10, 0);
        Text_SetEnvColor(0xFF, 0xFF, 0xFF, 0xFF);
        if (ptr->unk_10 <= 0.0f) {
            Text_Print((ptr->unk_04 - (MeasureTextWidth(0, 0, sp2C) / 2)) + 0x7C, ptr->unk_06 + 0xA, sp2C);
            Text_Print((ptr->unk_08 - (MeasureTextWidth(0, 0, sp28) / 2)) + 0xE4, ptr->unk_0A + 0xA, sp28);
        } else {
            Text_PrintWavy(ptr->unk_04 + 0x18, ptr->unk_06 + 0xA, sp2C, ptr->unk_10, ptr->unk_0C);
            Text_PrintWavy(ptr->unk_08 + 0x18, ptr->unk_0A + 0xA, sp28, ptr->unk_10, ptr->unk_0C);
        }
        Text_SetupDL();
    }
}

void OptionMenu_Init(char** arg0) {
    s32 i;

    gOptionMenu.unk_00 = 0;
    gOptionMenu.unk_02 = 0;
    gOptionMenu.unk_14 = arg0;

    for (i = 0; i < 9; i++) {
        gOptionMenuItems[i] = GetMessageString(NULL, 0, arg0, i + 7);
    }
}

void func_825057A0(void) {
}

void OptionMenu_SetSelection(s16 arg0) {
    unk_D_8250A498* ptr = &gOptionMenu;

    if (ptr->unk_12 != ptr->unk_10) {
        ptr->unk_10 = ptr->unk_12;
        ptr->unk_0C = ptr->unk_0E;
        ptr->unk_04 = ptr->unk_06;
    }
    ptr->unk_12 = arg0;
    ptr->unk_0E = MeasureTextWidth(0, 0, gOptionMenuItems[ptr->unk_12], arg0) + 0x30;
    ptr->unk_06 = (0x280 - ptr->unk_0E) / 2;
    ptr->unk_02 = 5;
}

void OptionMenu_SetState(s16 arg0, s16 arg1) {
    unk_D_8250A498* ptr = &gOptionMenu;

    ptr->unk_00 = arg0;

    switch (ptr->unk_00) {
        case 0:
            ptr->unk_02 = 0;
            break;

        case 1:
            ptr->unk_02 = 0xA;
            ptr->unk_10 = ptr->unk_12 = arg1;
            ptr->unk_0C = ptr->unk_0E = MeasureTextWidth(0, 0, gOptionMenuItems[ptr->unk_12], arg1) + 0x30;
            ptr->unk_04 = ptr->unk_06 = (0x280 - ptr->unk_0C) / 2;
            ptr->unk_08 = -0x2C;
            ptr->unk_0A = 0x1E0;
            break;

        case 2:
            ptr->unk_08 = 0x3C;
            break;

        case 3:
            ptr->unk_02 = 0xA;
            break;
    }
}

void func_82505998(unk_D_8250A498* arg0) {
    arg0->unk_02--;
    arg0->unk_08 = ((arg0->unk_02 * -0x68) / 10) + 0x3C;
    arg0->unk_0A = ((arg0->unk_02 * 0x56) / 10) + 0x18A;
    if (arg0->unk_02 <= 0) {
        OptionMenu_SetState(2, -1);
    }
}

void func_82505A70(unk_D_8250A498* arg0) {
    if (arg0->unk_10 != arg0->unk_12) {
        arg0->unk_02--;
        if (arg0->unk_02 <= 0) {
            arg0->unk_10 = arg0->unk_12;
            arg0->unk_0C = arg0->unk_0E;
            arg0->unk_04 = arg0->unk_06;
        }
    }
}

void func_82505AB8(unk_D_8250A498* arg0) {
    arg0->unk_02--;
    arg0->unk_08 = ((arg0->unk_02 * 0x68) / 10) - 0x2C;
    arg0->unk_0A = ((arg0->unk_02 * -0x56) / 10) + 0x1E0;
    if (arg0->unk_02 <= 0) {
        OptionMenu_SetState(0, -1);
    }
}

void OptionMenu_Update(void) {
    unk_D_8250A498* ptr = &gOptionMenu;

    if (ptr->unk_00 != 0) {
        switch (ptr->unk_00) {
            case 1:
                func_82505998(ptr);
                break;

            case 2:
                func_82505A70(ptr);
                break;

            case 3:
                func_82505AB8(ptr);
                break;
        }
    }
}

void OptionMenu_Render(void) {
    UNUSED s32 pad;
    unk_D_8250A498* ptr = &gOptionMenu;
    char* sp3C;
    s16 tmp;
    char* sp34 = GetMessageString(NULL, 0, ptr->unk_14, 0x10);

    if (ptr->unk_00 != 0) {
        if (ptr->unk_10 == ptr->unk_12) {
            Gfx_DrawBorderedBox(ptr->unk_04, ptr->unk_08, ptr->unk_0C, 0x2C, 0x1E, 0x1E, 0x82, 0x80);
        } else {
            tmp = (ptr->unk_02 << 7) / 5;
            Gfx_DrawBorderedBox(ptr->unk_04, ptr->unk_08, ptr->unk_0C, 0x2C, 0x1E, 0x1E, 0x82, tmp);
            tmp = ((-ptr->unk_02 * 0x80) + 0x280) / 5;
            Gfx_DrawBorderedBox(ptr->unk_06, ptr->unk_08, ptr->unk_0E, 0x2C, 0x1E, 0x1E, 0x82, tmp);
        }

        if (gMenuSelectedOption == -1) {
            Gfx_DrawBorderedBox(0x98, ptr->unk_0A, 0x140, 0x2C, 0x64, 0, 0x50, 0x80);
        }

        Text_ResetState();
        Text_SetFont(0x10, 0);
        sp3C = gOptionMenuItems[ptr->unk_10];
        if (ptr->unk_10 == ptr->unk_12) {
            Text_SetEnvColor(0xFF, 0xFF, 0xFF, 0xFF);
            Text_Print(ptr->unk_04 + 0x18, ptr->unk_08 + 0xA, sp3C);
        } else {
            tmp = (ptr->unk_02 * 0xFF) / 5;
            Text_SetEnvColor(0xFF, 0xFF, 0xFF, tmp);
            Text_Print(ptr->unk_04 + 0x18, ptr->unk_08 + 0xA, sp3C);
            sp3C = gOptionMenuItems[ptr->unk_12];
            tmp = ((5 - ptr->unk_02) * 0xFF) / 5;
            Text_SetEnvColor(0xFF, 0xFF, 0xFF, tmp);
            Text_Print(ptr->unk_06 + 0x18, ptr->unk_08 + 0xA, sp3C);
        }

        if (gMenuSelectedOption == -1) {
            Text_SetEnvColor(0xFF, 0xFF, 0xFF, 0xFF);
            Text_Print(0x140 - (GetTextWidth(D_8250A304, sp34) / 2), ptr->unk_0A + 0xA, sp34);
        }
        Text_SetupDL();
    }
}
