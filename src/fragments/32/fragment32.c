#include "fragment32.h"
#include "src/1CF30.h"
#include "src/20470.h"
#include "src/2E110.h"
#include "src/3FB0.h"
#include "src/6A40.h"
#include "src/memory.h"
#include "src/stage_loader.h"

static s32 D_81100930;
static s32 D_81100934;
static char** D_81100938;

void func_81100020(s32 arg0, s32 arg1, s32 arg2) {
    s32 i;
    s32 j;
    s32 idx;

    gDPPipeSync(gDisplayListHead++);
    gDPSetCycleType(gDisplayListHead++, G_CYC_COPY);
    gDPSetTexturePersp(gDisplayListHead++, G_TP_NONE);
    gDPSetCombineMode(gDisplayListHead++, G_CC_DECALRGBA, G_CC_DECALRGBA);
    gDPSetRenderMode(gDisplayListHead++, G_RM_NOOP, G_RM_NOOP2);

    for (i = 0; i < 0xF0; i += 0x10) {
        for (j = 0; j < 0x140; j += 0x40) {
            idx = (i % 64) * 32;
            Gfx_DrawSpriteRGBA16(j, i, 0x40, 0x10, &D_2000000[idx * 4], 0x40, 0x200000);
        }
    }

    gSPDisplayList(gDisplayListHead++, D_8006F630);
}

void func_811001C0(s32 arg0, s32 arg1) {
    gDPPipeSync(gDisplayListHead++);
    gDPSetCycleType(gDisplayListHead++, G_CYC_COPY);
    gDPSetTexturePersp(gDisplayListHead++, G_TP_NONE);
    gDPSetRenderMode(gDisplayListHead++, G_RM_NOOP, G_RM_NOOP2);
    gDPSetCombineMode(gDisplayListHead++, G_CC_DECALRGBA, G_CC_DECALRGBA);

    Gfx_DrawSpriteRGBA16(arg0, arg1, 0x18, 0x18, D_2002000, 0x18, 0x200000);

    gSPDisplayList(gDisplayListHead++, D_8006F630);
}

void func_811002D4(s32 arg0) {
    DrawPanel(0x16, 0x10, 0x114, 0x76, 0x11C5);
    func_811001C0(0x27, 0x22);
    Text_ResetState();
    Text_SetFont(2, 0);
    Text_SetLineHeight(0x10);
    Text_Print(0x52, 0x21, GetMessageString(NULL, 0, D_81100938, arg0 - 1));
    Text_SetupDL();
}

void func_81100368(s32 arg0) {
    u16 sp80[] = {
        0x00BC,
        0x00C6,
        0x00DF,
        0x00E9,
    };

    gSPDisplayList(gDisplayListHead++, D_8006F518);

    Gfx_DrawSpriteRGBA16(0x98, 0xA1, 8, 8, D_20069A0, 8, 0);

    gSPTextureRectangle(gDisplayListHead++, 0x01C8, 0x0284, 0x0260, 0x02A4, G_TX_RENDERTILE, 0, 0, 0, 0x0400);
    gSPDisplayList(gDisplayListHead++, D_8006F4E0);

    Gfx_DrawSpriteRGBA16(0x4D, 0x94, 0x40, 0x20, D_2002900, 0x40, 0x200000);
    Gfx_DrawSpriteRGBA16(0x4D, 0xB4, 0x40, 0x20, D_2003900, 0x40, 0x200000);
    Gfx_DrawSpriteRGBA16(0x4D, 0xD4, 0x40, 6, D_2004900, 0x40, 0x200000);
    Gfx_DrawSpriteRGBA16(0x5D, 0x98, 0x18, 0x18, D_2002480, 0x18, 0x200000);
    Gfx_DrawSpriteRGBA16(0xAA, 0xAA, 0x64, 0x12, D_2004C00, 0x64, 0x200000);
    Gfx_DrawSpriteRGBA16(0xAA, 0xBC, 0x64, 0x12, D_2005A10, 0x64, 0x200000);

    gSPDisplayList(gDisplayListHead++, D_8006F518);

    Gfx_DrawSpriteRGBA16(0x9B, 0xD4, 8, 8, D_20068A0, 8, 0);

    gSPTextureRectangle(gDisplayListHead++, 0x026C, 0x02A4, 0x028C, 0x0350, G_TX_RENDERTILE, 0, 0, 0x0400, 0);

    Gfx_DrawSpriteRGBA16(sp80[arg0], 0xD4, 8, 8, D_2006920, 8, 0);

    gSPTextureRectangle(gDisplayListHead++, 0x028C, 0x0350, sp80[arg0] << 2, 0x0370, G_TX_RENDERTILE, 0, 0, 0, 0x0400);

    Gfx_DrawSpriteRGBA16(sp80[arg0], 0xC0, 8, 8, D_2006820, 8, 0);

    gSPTextureRectangle(gDisplayListHead++, sp80[arg0] << 2, 0x0320, (sp80[arg0] + 8) << 2, 0x0350, G_TX_RENDERTILE, 0,
                        0x00E0, 0x0400, 0);
    gSPDisplayList(gDisplayListHead++, D_8006F630);
}

s32 func_811007AC(u8 arg0) {
    Stage_BeginDisplayList();
    func_81100020(0x55, 0x70, 0x88);
    func_811002D4(D_81100934);
    func_81100368(D_81100930);
    return 0;
}

void func_811007F8(s32 arg0, s32 arg1) {
    Stage* temp_s0;

    D_81100930 = arg0;
    D_81100934 = arg1;

    main_pool_push_state('FATL');

    Gfx_InitBuffers(0x10000, 0);
    temp_s0 = Stage_Create(0, 1, 2, 0, 2, 1);
    Text_Init(6, 0);
    ASSET_LOAD(D_1000000, common_menu1_ui, 0);
    ASSET_LOAD(D_2000000, transfer_pak_error_ui, 0);
    MessageBank_Init();
    D_81100938 = GetMessageBank(0xD);
    Stage_Set(temp_s0);

    while (true) {
        func_800078D4(func_811007AC, 8, 8);
    }
}
