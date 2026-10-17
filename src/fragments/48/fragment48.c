#include "fragment48.h"
#include "src/1CF30.h"
#include "src/20330.h"
#include "src/26820.h"
#include "src/3FB0.h"
#include "src/6A40.h"
#include "src/controller.h"
#include "src/memory.h"
#include "src/stage_loader.h"

typedef struct unk_D_839006B0 {
    /* 0x00 */ unk_func_80026268_arg0 unk_00;
    /* 0x54 */ char unk54[0x38];
} unk_D_839006B0; // size = 0x8C

typedef struct unk_D_83902700 {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ char unk04[0x70];
} unk_D_83902700; // size >= 0x74

static unk_D_839006B0 gGalleryLoadData[37];
static unk_D_839006B0 gGallerySaveData[22];
static void* gGalleryBackgroundTexture;
static s32 gGalleryState;
static unk_D_83902700 D_83902700;
static s32 D_83902774;

static Gfx D_83900630[] = {
    gsSPEndDisplayList(),
};

static Gfx D_83900638[] = {
    gsSPEndDisplayList(),
};

void Gallery_Debugger_PostLoad(void) {
}

void func_83900028(void) {
}

void func_83900030(void) {
}

void Gallery_Debugger_Init(void) {
    s32 i;

    gGalleryState = 0;
    D_83902700.unk_00 = 0;
    GbsEnsureBankLoaded(2);

    for (i = 0; i < 36; i++) {
        GbsReadBlockEntry(0x16, 0, i, &gGalleryLoadData[i]);
    }

    for (i = 0; i < 21; i++) {
        GbsReadBlockEntry(0x17, 0, i, &gGallerySaveData[i]);
    }

    Gallery_Debugger_PostLoad();
}

void func_839000E4(void) {
    s32 i;

    for (i = 0; i < 36; i++) {
        GbsWriteBlockEntry(0x16, 0, i, &gGalleryLoadData[i]);
    }

    for (i = 0; i < 21; i++) {
        GbsWriteBlockEntry(0x17, 0, i, &gGallerySaveData[i]);
    }

    GbsProcessBankWrites(2);
    GbsSyncBank(2);
}

void Gallery_Debugger_DrawMenu(void) {
    static char* D_83900640[] = { "Load Controller Pak", "Save Controller Pak", "Quit" };

    s32 i;
    s32 sp30;
    char* temp_s0 = "GALLERY DEBUGGER";

    Text_ResetState();
    Text_SetFont(8, 0);
    Text_SetEnvColor(0xFF, 0xFF, 0xFF, 0xFF);
    sp30 = (0x280 - MeasureTextWidth(0, 0, temp_s0)) / 2;
    Text_Print(sp30, 0x64, temp_s0);

    for (i = 0; i < 3; i++) {
        s32 tmp = i * 0x16;
        if (i != D_83902700.unk_00) {
            Text_SetEnvColor(0xFF, 0xFF, 0xFF, 0xFF);
        } else {
            Text_SetEnvColor(0xFF, 0xFF, 0, 0xFF);
        }
        Text_Print(0x78, 0x82 + tmp, D_83900640[i]);
    }

    Text_Print(sp30, 0xC8, "PFS ERROR : %d", D_83902774);
    Text_SetupDL();
}

void Gallery_Debugger_Render(void) {
    Stage_BeginDisplayList();
    Gfx_DrawTextureAtlas(gGalleryBackgroundTexture);
    Gallery_Debugger_DrawMenu();
    Stage_Advance();
}

s32 Gallery_Debugger_HandleInput(void) {
    s32 var_a2 = 0;
    s32 temp_a1 = D_83902700.unk_00;

    if (BTN_IS_PRESSED(gPlayer1Controller, BTN_DUP)) {
        D_83902700.unk_00--;
        if (D_83902700.unk_00 < 0) {
            D_83902700.unk_00 = 0;
        }
    }

    if (BTN_IS_PRESSED(gPlayer1Controller, BTN_DDOWN)) {
        D_83902700.unk_00++;
        if (D_83902700.unk_00 >= 3) {
            D_83902700.unk_00 = 2;
        }
    }

    if (temp_a1 != D_83902700.unk_00) {
        D_83902774 = 0;
    }

    if (BTN_IS_PRESSED(gPlayer1Controller, BTN_A)) {
        switch (D_83902700.unk_00) {
            case 0:
                func_83900030();
                var_a2 = 0;
                break;

            case 1:
                func_83900028();
                var_a2 = 0;
                break;

            case 2:
                var_a2 = 1;
                break;
        }
    }

    return var_a2;
}

s32 Gallery_Debugger_MainLoop(void) {
    s32 sp1C = 1;

    switch (gGalleryState) {
        case 0:
            if (func_80007604() == 0) {
                gGalleryState = 1;
            }
            break;

        case 1:
            if (Gallery_Debugger_HandleInput() != 0) {
                gGalleryState = 2;
                func_80006CB4(0xF);
            }
            break;

        case 2:
            if (func_80007604() == 1) {
                sp1C = 0;
            }
            break;
    }
    return sp1C;
}

void Gallery_Debugger_UpdateController(void) {
    Cont_StartReadInputs();
    Cont_ReadInputs();
    MenuInput_Init();
}

void Gallery_Debugger_Run(void) {
    func_80006C6C(0xF);
    do {
        Gallery_Debugger_UpdateController();
        Gallery_Debugger_Render();
    } while (Gallery_Debugger_MainLoop() != 0);
}

s32 Gallery_Debugger_Entry(s32 arg0, s32 arg1) {
    Stage* sp24;

    main_pool_push_state('GLDB');

    Gfx_InitBuffers(0x10000, 0);
    sp24 = Stage_Create(1, 0, 2, 0, 2, 1);
    Text_Init(0x18, 0);
    ASSET_LOAD(D_1000000, common_menu1_ui, 0);
    ASSET_LOAD(D_3000000, gallery_ui, 0);
    gGalleryBackgroundTexture = BinArchive_GetFile(ASSET_LOAD2(backgrounds, 1, 1), 0x14);
    Gallery_Debugger_Init();
    Stage_Set(sp24);
    Gallery_Debugger_Run();
    func_839000E4();
    Stage_Destroy();
    FontManager_Free();
    Gfx_FreeBuffers();

    main_pool_pop_state('GLDB');

    return 0;
}
