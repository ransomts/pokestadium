#include "fragment39.h"
#include "src/12D80.h"
#include "src/1C720.h"
#include "src/1CF30.h"
#include "src/20330.h"
#include "src/20470.h"
#include "src/26820.h"
#include "src/2E110.h"
#include "src/3FB0.h"
#include "src/49790.h"
#include "src/4BDC0.h"
#include "src/6A40.h"
#include "src/F420.h"
#include "src/controller.h"
#include "src/fragments/2/fragment2.h"
#include "src/geo_layout.h"
#include "src/memmap.h"
#include "src/memory.h"
#include "src/stage_loader.h"

typedef struct ItemSelectionCoords {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ s16 unk_08;
    /* 0x0A */ s16 unk_0A;
    /* 0x0C */ s16 unk_0C;
    /* 0x0E */ s16 unk_0E;
} ItemSelectionCoords; // size >= 0x10

static u16 gSelectionFlags;
static s32 gSelectionFrameCounter;
static unk_D_82508B00* gControllerInputs;
static unk_D_82508B00 gControllerStates[4];
static UIElement gUIElements[14];
static unk_D_8250A228* gUIElementArray[2];
static unk_D_8250A228* gComputerUIElements[2];
static unk_D_8250A228* gComputerUIRoot;
static unk_D_8250A228* gItemGridElements[9];
static BinArchive* gItemArchive;
static void* gItemDataPtr;
static s16 D_8250A26C;
static s16 gSubMenuState;
static GraphNode* gCursorNode;
static GraphNode* gStatusIconNode;
static GraphNode* gComputerSelectionNode;
static GraphNode* gItemSelectionNode;
static GraphNode* gBackgroundNode;
static GraphNode* gSelectionHighlightNode;
static unk_D_8250A288 D_8250A288;
static s16 gSelectionTimer;
static s16 gSelectionDelay;
static s16 gItemSelectionTimer;
static s16 gItemSelectionRandom;
static ItemSelectionCoords gSelectionCoords;
static s32 pad_D_8250A2B0[18];
static s32 pad_D_8250A2F8;
static s16 gUnused0;
static s16 gUnused1;
static s16 gUnused2;
TextObject* gTextObjectHandle;
static unk_D_8250A308 gCursor;
static char** gStringTable;

static Vtx gStatusBarVertices0[] = {
    VTX(0, 40, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(0, 36, 0, 0, 128, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(300, 36, 0, 9600, 128, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(300, 40, 0, 9600, 0, 0xFF, 0xFF, 0xFF, 0xFF),
};

static Vtx gStatusBarVertices1[] = {
    VTX(0, 36, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(0, 32, 0, 0, 128, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(300, 32, 0, 9600, 128, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(300, 36, 0, 9600, 0, 0xFF, 0xFF, 0xFF, 0xFF),
};

static Vtx gStatusBarVertices2[] = {
    VTX(0, 32, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(0, 28, 0, 0, 128, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(300, 28, 0, 9600, 128, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(300, 32, 0, 9600, 0, 0xFF, 0xFF, 0xFF, 0xFF),
};
static Vtx gStatusBarVertices3[] = {
    VTX(0, 28, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(0, 24, 0, 0, 128, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(300, 24, 0, 9600, 128, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(300, 28, 0, 9600, 0, 0xFF, 0xFF, 0xFF, 0xFF),
};
static Vtx gStatusBarVertices4[] = {
    VTX(0, 24, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(0, 20, 0, 0, 128, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(300, 20, 0, 9600, 128, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(300, 24, 0, 9600, 0, 0xFF, 0xFF, 0xFF, 0xFF),
};
static Vtx gStatusBarVertices5[] = {
    VTX(0, 20, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(0, 16, 0, 0, 128, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(300, 16, 0, 9600, 128, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(300, 20, 0, 9600, 0, 0xFF, 0xFF, 0xFF, 0xFF),
};
static Vtx gStatusBarVertices6[] = {
    VTX(0, 16, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(0, 12, 0, 0, 128, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(300, 12, 0, 9600, 128, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(300, 16, 0, 9600, 0, 0xFF, 0xFF, 0xFF, 0xFF),
};
static Vtx gStatusBarVertices7[] = {
    VTX(0, 12, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(0, 8, 0, 0, 128, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(300, 8, 0, 9600, 128, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(300, 12, 0, 9600, 0, 0xFF, 0xFF, 0xFF, 0xFF),
};
static Vtx gStatusBarVertices8[] = {
    VTX(0, 8, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(0, 4, 0, 0, 128, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(300, 4, 0, 9600, 128, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(300, 8, 0, 9600, 0, 0xFF, 0xFF, 0xFF, 0xFF),
};
static Vtx gStatusBarVertices9[] = {
    VTX(0, 4, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(0, 0, 0, 0, 128, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(300, 0, 0, 9600, 128, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(300, 4, 0, 9600, 0, 0xFF, 0xFF, 0xFF, 0xFF),
};
static Vtx gStatusBarVertices10[] = {
    VTX(0, 0, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(0, -4, 0, 0, 128, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(300, -4, 0, 9600, 128, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(300, 0, 0, 9600, 0, 0xFF, 0xFF, 0xFF, 0xFF),
};
static Vtx gStatusBarVertices11[] = {
    VTX(0, -4, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(0, -8, 0, 0, 128, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(300, -8, 0, 9600, 128, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(300, -4, 0, 9600, 0, 0xFF, 0xFF, 0xFF, 0xFF),
};
static Vtx gStatusBarVertices12[] = {
    VTX(0, -8, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(0, -12, 0, 0, 128, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(300, -12, 0, 9600, 128, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(300, -8, 0, 9600, 0, 0xFF, 0xFF, 0xFF, 0xFF),
};
static Vtx gStatusBarVertices13[] = {
    VTX(0, -12, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(0, -16, 0, 0, 128, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(300, -16, 0, 9600, 128, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(300, -12, 0, 9600, 0, 0xFF, 0xFF, 0xFF, 0xFF),
};
static Vtx gStatusBarVertices14[] = {
    VTX(0, -16, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(0, -20, 0, 0, 128, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(300, -20, 0, 9600, 128, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(300, -16, 0, 9600, 0, 0xFF, 0xFF, 0xFF, 0xFF),
};
static Vtx gStatusBarVertices15[] = {
    VTX(0, -20, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(0, -24, 0, 0, 128, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(300, -24, 0, 9600, 128, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(300, -20, 0, 9600, 0, 0xFF, 0xFF, 0xFF, 0xFF),
};
static Vtx gStatusBarVertices16[] = {
    VTX(0, -24, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(0, -28, 0, 0, 128, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(300, -28, 0, 9600, 128, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(300, -24, 0, 9600, 0, 0xFF, 0xFF, 0xFF, 0xFF),
};
static Vtx gStatusBarVertices17[] = {
    VTX(0, -28, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(0, -32, 0, 0, 128, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(300, -32, 0, 9600, 128, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(300, -28, 0, 9600, 0, 0xFF, 0xFF, 0xFF, 0xFF),
};
static Vtx gStatusBarVertices18[] = {
    VTX(0, -32, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(0, -36, 0, 0, 128, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(300, -36, 0, 9600, 128, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(300, -32, 0, 9600, 0, 0xFF, 0xFF, 0xFF, 0xFF),
};
static Vtx gStatusBarVertices19[] = {
    VTX(0, -36, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(0, -40, 0, 0, 128, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(300, -40, 0, 9600, 128, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(300, -36, 0, 9600, 0, 0xFF, 0xFF, 0xFF, 0xFF),
};
static Vtx gComputerSelectionVertices0[] = {
    VTX(130, 35, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(130, 25, 0, 0, 320, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(290, 25, 0, 5120, 320, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(290, 35, 0, 5120, 0, 0xFF, 0xFF, 0xFF, 0xFF),
};
static Vtx gComputerSelectionVertices1[] = {
    VTX(130, 25, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(130, 15, 0, 0, 320, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(290, 15, 0, 5120, 320, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(290, 25, 0, 5120, 0, 0xFF, 0xFF, 0xFF, 0xFF),
};
static Vtx gComputerSelectionVertices2[] = {
    VTX(130, 15, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(130, 5, 0, 0, 320, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(290, 5, 0, 5120, 320, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(290, 15, 0, 5120, 0, 0xFF, 0xFF, 0xFF, 0xFF),
};
static Vtx gComputerSelectionVertices3[] = {
    VTX(130, 5, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(130, -5, 0, 0, 320, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(290, -5, 0, 5120, 320, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(290, 5, 0, 5120, 0, 0xFF, 0xFF, 0xFF, 0xFF),
};
static Vtx gComputerSelectionVertices4[] = {
    VTX(130, -5, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(130, -15, 0, 0, 320, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(290, -15, 0, 5120, 320, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(290, -5, 0, 5120, 0, 0xFF, 0xFF, 0xFF, 0xFF),
};
static Vtx gComputerSelectionVertices5[] = {
    VTX(130, -15, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(130, -25, 0, 0, 320, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(290, -25, 0, 5120, 320, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(290, -15, 0, 5120, 0, 0xFF, 0xFF, 0xFF, 0xFF),
};
static Vtx gComputerSelectionVertices6[] = {
    VTX(130, -25, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(130, -35, 0, 0, 320, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(290, -35, 0, 5120, 320, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(290, -25, 0, 5120, 0, 0xFF, 0xFF, 0xFF, 0xFF),
};
static Vtx gComputerSelectionVertices7[] = {
    VTX(150, 35, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(150, 25, 0, 0, 320, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(260, 25, 0, 3520, 320, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(260, 35, 0, 3520, 0, 0xFF, 0xFF, 0xFF, 0xFF),
};
static Vtx gComputerSelectionVertices8[] = {
    VTX(150, 25, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(150, 15, 0, 0, 320, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(260, 15, 0, 3520, 320, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(260, 25, 0, 3520, 0, 0xFF, 0xFF, 0xFF, 0xFF),
};
static Vtx gComputerSelectionVertices9[] = {
    VTX(150, 15, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(150, 5, 0, 0, 320, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(260, 5, 0, 3520, 320, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(260, 15, 0, 3520, 0, 0xFF, 0xFF, 0xFF, 0xFF),
};
static Vtx gComputerSelectionVertices10[] = {
    VTX(150, 5, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(150, -5, 0, 0, 320, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(260, -5, 0, 3520, 320, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(260, 5, 0, 3520, 0, 0xFF, 0xFF, 0xFF, 0xFF),
};
static Vtx gComputerSelectionVertices11[] = {
    VTX(150, -5, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(150, -15, 0, 0, 320, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(260, -15, 0, 3520, 320, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(260, -5, 0, 3520, 0, 0xFF, 0xFF, 0xFF, 0xFF),
};
static Vtx gComputerSelectionVertices12[] = {
    VTX(150, -15, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(150, -25, 0, 0, 320, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(260, -25, 0, 3520, 320, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(260, -15, 0, 3520, 0, 0xFF, 0xFF, 0xFF, 0xFF),
};
static Vtx gComputerSelectionVertices13[] = {
    VTX(150, -25, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(150, -35, 0, 0, 320, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(260, -35, 0, 3520, 320, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(260, -25, 0, 3520, 0, 0xFF, 0xFF, 0xFF, 0xFF),
};

static Gfx gStatusIconDL[] = {
    gsSPSetGeometryMode(G_CULL_BACK),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_PASS2),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPLoadTextureTile(0x0F000000, G_IM_FMT_RGBA, G_IM_SIZ_16b, 300, 0, 0, 0, 299, 3, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(gStatusBarVertices0, 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsDPLoadTextureTile(0x0F000960, G_IM_FMT_RGBA, G_IM_SIZ_16b, 300, 0, 0, 0, 299, 3, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(gStatusBarVertices1, 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsDPLoadTextureTile(0x0F0012C0, G_IM_FMT_RGBA, G_IM_SIZ_16b, 300, 0, 0, 0, 299, 3, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(gStatusBarVertices2, 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsDPLoadTextureTile(0x0F001C20, G_IM_FMT_RGBA, G_IM_SIZ_16b, 300, 0, 0, 0, 299, 3, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(gStatusBarVertices3, 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsDPLoadTextureTile(0x0F002580, G_IM_FMT_RGBA, G_IM_SIZ_16b, 300, 0, 0, 0, 299, 3, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(gStatusBarVertices4, 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsDPLoadTextureTile(0x0F002EE0, G_IM_FMT_RGBA, G_IM_SIZ_16b, 300, 0, 0, 0, 299, 3, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(gStatusBarVertices5, 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsDPLoadTextureTile(0x0F003840, G_IM_FMT_RGBA, G_IM_SIZ_16b, 300, 0, 0, 0, 299, 3, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(gStatusBarVertices6, 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsDPLoadTextureTile(0x0F0041A0, G_IM_FMT_RGBA, G_IM_SIZ_16b, 300, 0, 0, 0, 299, 3, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(gStatusBarVertices7, 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsDPLoadTextureTile(0x0F004B00, G_IM_FMT_RGBA, G_IM_SIZ_16b, 300, 0, 0, 0, 299, 3, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(gStatusBarVertices8, 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsDPLoadTextureTile(0x0F005460, G_IM_FMT_RGBA, G_IM_SIZ_16b, 300, 0, 0, 0, 299, 3, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(gStatusBarVertices9, 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsDPLoadTextureTile(0x0F005DC0, G_IM_FMT_RGBA, G_IM_SIZ_16b, 300, 0, 0, 0, 299, 3, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(gStatusBarVertices10, 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsDPLoadTextureTile(0x0F006720, G_IM_FMT_RGBA, G_IM_SIZ_16b, 300, 0, 0, 0, 299, 3, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(gStatusBarVertices11, 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsDPLoadTextureTile(0x0F007080, G_IM_FMT_RGBA, G_IM_SIZ_16b, 300, 0, 0, 0, 299, 3, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(gStatusBarVertices12, 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsDPLoadTextureTile(0x0F0079E0, G_IM_FMT_RGBA, G_IM_SIZ_16b, 300, 0, 0, 0, 299, 3, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(gStatusBarVertices13, 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsDPLoadTextureTile(0x0F008340, G_IM_FMT_RGBA, G_IM_SIZ_16b, 300, 0, 0, 0, 299, 3, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(gStatusBarVertices14, 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsDPLoadTextureTile(0x0F008CA0, G_IM_FMT_RGBA, G_IM_SIZ_16b, 300, 0, 0, 0, 299, 3, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(gStatusBarVertices15, 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsDPLoadTextureTile(0x0F009600, G_IM_FMT_RGBA, G_IM_SIZ_16b, 300, 0, 0, 0, 299, 3, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(gStatusBarVertices16, 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsDPLoadTextureTile(0x0F009F60, G_IM_FMT_RGBA, G_IM_SIZ_16b, 300, 0, 0, 0, 299, 3, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(gStatusBarVertices17, 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsDPLoadTextureTile(0x0F00A8C0, G_IM_FMT_RGBA, G_IM_SIZ_16b, 300, 0, 0, 0, 299, 3, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(gStatusBarVertices18, 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsDPLoadTextureTile(0x0F00B220, G_IM_FMT_RGBA, G_IM_SIZ_16b, 300, 0, 0, 0, 299, 3, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(gStatusBarVertices19, 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSPEndDisplayList(),
};
static Gfx gStatusIconAnimDL[] = {
    gsDPLoadTextureTile(0x0E000000, G_IM_FMT_RGBA, G_IM_SIZ_16b, 160, 0, 0, 0, 159, 9, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(gComputerSelectionVertices0, 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsDPLoadTextureTile(0x0E000C80, G_IM_FMT_RGBA, G_IM_SIZ_16b, 160, 0, 0, 0, 159, 9, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(gComputerSelectionVertices1, 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsDPLoadTextureTile(0x0E001900, G_IM_FMT_RGBA, G_IM_SIZ_16b, 160, 0, 0, 0, 159, 9, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(gComputerSelectionVertices2, 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsDPLoadTextureTile(0x0E002580, G_IM_FMT_RGBA, G_IM_SIZ_16b, 160, 0, 0, 0, 159, 9, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(gComputerSelectionVertices3, 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsDPLoadTextureTile(0x0E003200, G_IM_FMT_RGBA, G_IM_SIZ_16b, 160, 0, 0, 0, 159, 9, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(gComputerSelectionVertices4, 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsDPLoadTextureTile(0x0E003E80, G_IM_FMT_RGBA, G_IM_SIZ_16b, 160, 0, 0, 0, 159, 9, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(gComputerSelectionVertices5, 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsDPLoadTextureTile(0x0E004B00, G_IM_FMT_RGBA, G_IM_SIZ_16b, 160, 0, 0, 0, 159, 9, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(gComputerSelectionVertices6, 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSPEndDisplayList(),
};
static Gfx gStatusIconAltAnimDL[] = {
    gsDPLoadTextureTile(0x0E000000, G_IM_FMT_RGBA, G_IM_SIZ_16b, 110, 0, 0, 0, 109, 9, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(gComputerSelectionVertices7, 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsDPLoadTextureTile(0x0E000898, G_IM_FMT_RGBA, G_IM_SIZ_16b, 110, 0, 0, 0, 109, 9, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(gComputerSelectionVertices8, 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsDPLoadTextureTile(0x0E001130, G_IM_FMT_RGBA, G_IM_SIZ_16b, 110, 0, 0, 0, 109, 9, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(gComputerSelectionVertices9, 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsDPLoadTextureTile(0x0E0019C8, G_IM_FMT_RGBA, G_IM_SIZ_16b, 110, 0, 0, 0, 109, 9, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(gComputerSelectionVertices10, 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsDPLoadTextureTile(0x0E002260, G_IM_FMT_RGBA, G_IM_SIZ_16b, 110, 0, 0, 0, 109, 9, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(gComputerSelectionVertices11, 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsDPLoadTextureTile(0x0E002AF8, G_IM_FMT_RGBA, G_IM_SIZ_16b, 110, 0, 0, 0, 109, 9, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(gComputerSelectionVertices12, 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsDPLoadTextureTile(0x0E003390, G_IM_FMT_RGBA, G_IM_SIZ_16b, 110, 0, 0, 0, 109, 9, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(gComputerSelectionVertices13, 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSPEndDisplayList(),
};

static u32 gStatusIconDescriptor[] = {
    0x17000000, 0x00000000, 0x00000000,    0x00000000, gStatusBarVertices0, 0x05000000, 0x22040000,
    0x00000000, 0x08000000, DrawStatusIconForPlayer, 0x00000000, 0x06000000, 0x01000000, 0x00000000,
};

static Vtx gComputerSelectionBarVertices0[] = {
    VTX(0, 40, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(0, 35, 0, 0, 160, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(300, 35, 0, 9600, 160, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(300, 40, 0, 9600, 0, 0xFF, 0xFF, 0xFF, 0xFF),
};
static Vtx gComputerSelectionBarVertices1[] = {
    VTX(0, 35, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(0, 30, 0, 0, 160, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(300, 30, 0, 9600, 160, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(300, 35, 0, 9600, 0, 0xFF, 0xFF, 0xFF, 0xFF),
};
static Vtx gComputerSelectionBarVertices2[] = {
    VTX(0, 30, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(0, 25, 0, 0, 160, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(300, 25, 0, 9600, 160, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(300, 30, 0, 9600, 0, 0xFF, 0xFF, 0xFF, 0xFF),
};
static Vtx gComputerSelectionBarVertices3[] = {
    VTX(0, 25, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(0, 20, 0, 0, 160, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(300, 20, 0, 9600, 160, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(300, 25, 0, 9600, 0, 0xFF, 0xFF, 0xFF, 0xFF),
};
static Vtx gComputerSelectionBarVertices4[] = {
    VTX(0, 20, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(0, 15, 0, 0, 160, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(300, 15, 0, 9600, 160, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(300, 20, 0, 9600, 0, 0xFF, 0xFF, 0xFF, 0xFF),
};
static Vtx gComputerSelectionBarVertices5[] = {
    VTX(0, 15, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(0, 10, 0, 0, 160, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(300, 10, 0, 9600, 160, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(300, 15, 0, 9600, 0, 0xFF, 0xFF, 0xFF, 0xFF),
};
static Vtx gComputerSelectionBarVertices6[] = {
    VTX(0, 10, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(0, 5, 0, 0, 160, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(300, 5, 0, 9600, 160, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(300, 10, 0, 9600, 0, 0xFF, 0xFF, 0xFF, 0xFF),
};
static Vtx gComputerSelectionBarVertices7[] = {
    VTX(0, 5, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(0, 0, 0, 0, 160, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(300, 0, 0, 9600, 160, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(300, 5, 0, 9600, 0, 0xFF, 0xFF, 0xFF, 0xFF),
};
static Vtx gComputerSelectionBarVertices8[] = {
    VTX(0, 0, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(0, -5, 0, 0, 160, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(300, -5, 0, 9600, 160, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(300, 0, 0, 9600, 0, 0xFF, 0xFF, 0xFF, 0xFF),
};
static Vtx gComputerSelectionBarVertices9[] = {
    VTX(0, -5, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(0, -10, 0, 0, 160, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(300, -10, 0, 9600, 160, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(300, -5, 0, 9600, 0, 0xFF, 0xFF, 0xFF, 0xFF),
};
static Vtx gComputerSelectionBarVertices10[] = {
    VTX(0, -10, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(0, -15, 0, 0, 160, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(300, -15, 0, 9600, 160, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(300, -10, 0, 9600, 0, 0xFF, 0xFF, 0xFF, 0xFF),
};
static Vtx gComputerSelectionBarVertices11[] = {
    VTX(0, -15, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(0, -20, 0, 0, 160, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(300, -20, 0, 9600, 160, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(300, -15, 0, 9600, 0, 0xFF, 0xFF, 0xFF, 0xFF),
};
static Vtx gComputerSelectionBarVertices12[] = {
    VTX(0, -20, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(0, -25, 0, 0, 160, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(300, -25, 0, 9600, 160, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(300, -20, 0, 9600, 0, 0xFF, 0xFF, 0xFF, 0xFF),
};
static Vtx gComputerSelectionBarVertices13[] = {
    VTX(0, -25, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(0, -30, 0, 0, 160, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(300, -30, 0, 9600, 160, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(300, -25, 0, 9600, 0, 0xFF, 0xFF, 0xFF, 0xFF),
};
static Vtx gComputerSelectionBarVertices14[] = {
    VTX(0, -30, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(0, -35, 0, 0, 160, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(300, -35, 0, 9600, 160, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(300, -30, 0, 9600, 0, 0xFF, 0xFF, 0xFF, 0xFF),
};
static Vtx gComputerSelectionBarVertices15[] = {
    VTX(0, -35, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(0, -40, 0, 0, 160, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(300, -40, 0, 9600, 160, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(300, -35, 0, 9600, 0, 0xFF, 0xFF, 0xFF, 0xFF),
};

static Gfx gComputerSelectionDL[] = {
    gsSPSetGeometryMode(G_CULL_BACK),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_PASS2),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPLoadTextureTile(0x0F000000, G_IM_FMT_RGBA, G_IM_SIZ_16b, 300, 0, 0, 0, 299, 4, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(gComputerSelectionBarVertices0, 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsDPLoadTextureTile(0x0F000BB8, G_IM_FMT_RGBA, G_IM_SIZ_16b, 300, 0, 0, 0, 299, 4, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(gComputerSelectionBarVertices1, 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsDPLoadTextureTile(0x0F001770, G_IM_FMT_RGBA, G_IM_SIZ_16b, 300, 0, 0, 0, 299, 4, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(gComputerSelectionBarVertices2, 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsDPLoadTextureTile(0x0F002328, G_IM_FMT_RGBA, G_IM_SIZ_16b, 300, 0, 0, 0, 299, 4, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(gComputerSelectionBarVertices3, 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsDPLoadTextureTile(0x0F002EE0, G_IM_FMT_RGBA, G_IM_SIZ_16b, 300, 0, 0, 0, 299, 4, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(gComputerSelectionBarVertices4, 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsDPLoadTextureTile(0x0F003A98, G_IM_FMT_RGBA, G_IM_SIZ_16b, 300, 0, 0, 0, 299, 4, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(gComputerSelectionBarVertices5, 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsDPLoadTextureTile(0x0F004650, G_IM_FMT_RGBA, G_IM_SIZ_16b, 300, 0, 0, 0, 299, 4, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(gComputerSelectionBarVertices6, 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsDPLoadTextureTile(0x0F005208, G_IM_FMT_RGBA, G_IM_SIZ_16b, 300, 0, 0, 0, 299, 4, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(gComputerSelectionBarVertices7, 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsDPLoadTextureTile(0x0F005DC0, G_IM_FMT_RGBA, G_IM_SIZ_16b, 300, 0, 0, 0, 299, 4, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(gComputerSelectionBarVertices8, 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsDPLoadTextureTile(0x0F006978, G_IM_FMT_RGBA, G_IM_SIZ_16b, 300, 0, 0, 0, 299, 4, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(gComputerSelectionBarVertices9, 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsDPLoadTextureTile(0x0F007530, G_IM_FMT_RGBA, G_IM_SIZ_16b, 300, 0, 0, 0, 299, 4, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(gComputerSelectionBarVertices10, 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsDPLoadTextureTile(0x0F0080E8, G_IM_FMT_RGBA, G_IM_SIZ_16b, 300, 0, 0, 0, 299, 4, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(gComputerSelectionBarVertices11, 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsDPLoadTextureTile(0x0F008CA0, G_IM_FMT_RGBA, G_IM_SIZ_16b, 300, 0, 0, 0, 299, 4, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(gComputerSelectionBarVertices12, 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsDPLoadTextureTile(0x0F009858, G_IM_FMT_RGBA, G_IM_SIZ_16b, 300, 0, 0, 0, 299, 4, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(gComputerSelectionBarVertices13, 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsDPLoadTextureTile(0x0F00A410, G_IM_FMT_RGBA, G_IM_SIZ_16b, 300, 0, 0, 0, 299, 4, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(gComputerSelectionBarVertices14, 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsDPLoadTextureTile(0x0F00AFC8, G_IM_FMT_RGBA, G_IM_SIZ_16b, 300, 0, 0, 0, 299, 4, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(gComputerSelectionBarVertices15, 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSPEndDisplayList(),
};

static u32 gComputerSelectionDescriptor[] = {
    0x17000000, 0x00000000, 0x00000000,    0x00000000, gComputerSelectionBarVertices0, 0x05000000, 0x22040000,
    0x00000000, 0x08000000, DrawComputerSelection, 0x00000000, 0x06000000, 0x01000000, 0x00000000,
};

static Vtx gComputerSelectionVertices[] = {
    VTX(0, 40, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF),         VTX(0, 35, 0, 0, 160, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(300, 35, 0, 9600, 160, 0xFF, 0xFF, 0xFF, 0xFF),  VTX(300, 40, 0, 9600, 0, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(0, 35, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF),         VTX(0, 30, 0, 0, 160, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(300, 30, 0, 9600, 160, 0xFF, 0xFF, 0xFF, 0xFF),  VTX(300, 35, 0, 9600, 0, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(0, 30, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF),         VTX(0, 25, 0, 0, 160, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(300, 25, 0, 9600, 160, 0xFF, 0xFF, 0xFF, 0xFF),  VTX(300, 30, 0, 9600, 0, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(0, 25, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF),         VTX(0, 20, 0, 0, 160, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(300, 20, 0, 9600, 160, 0xFF, 0xFF, 0xFF, 0xFF),  VTX(300, 25, 0, 9600, 0, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(0, 20, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF),         VTX(0, 15, 0, 0, 160, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(300, 15, 0, 9600, 160, 0xFF, 0xFF, 0xFF, 0xFF),  VTX(300, 20, 0, 9600, 0, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(0, 15, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF),         VTX(0, 10, 0, 0, 160, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(300, 10, 0, 9600, 160, 0xFF, 0xFF, 0xFF, 0xFF),  VTX(300, 15, 0, 9600, 0, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(0, 10, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF),         VTX(0, 5, 0, 0, 160, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(300, 5, 0, 9600, 160, 0xFF, 0xFF, 0xFF, 0xFF),   VTX(300, 10, 0, 9600, 0, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(0, 5, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF),          VTX(0, 0, 0, 0, 160, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(300, 0, 0, 9600, 160, 0xFF, 0xFF, 0xFF, 0xFF),   VTX(300, 5, 0, 9600, 0, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(0, 0, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF),          VTX(0, -5, 0, 0, 160, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(300, -5, 0, 9600, 160, 0xFF, 0xFF, 0xFF, 0xFF),  VTX(300, 0, 0, 9600, 0, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(0, -5, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF),         VTX(0, -10, 0, 0, 160, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(300, -10, 0, 9600, 160, 0xFF, 0xFF, 0xFF, 0xFF), VTX(300, -5, 0, 9600, 0, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(0, -10, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF),        VTX(0, -15, 0, 0, 160, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(300, -15, 0, 9600, 160, 0xFF, 0xFF, 0xFF, 0xFF), VTX(300, -10, 0, 9600, 0, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(0, -15, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF),        VTX(0, -20, 0, 0, 160, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(300, -20, 0, 9600, 160, 0xFF, 0xFF, 0xFF, 0xFF), VTX(300, -15, 0, 9600, 0, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(0, -20, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF),        VTX(0, -25, 0, 0, 160, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(300, -25, 0, 9600, 160, 0xFF, 0xFF, 0xFF, 0xFF), VTX(300, -20, 0, 9600, 0, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(0, -25, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF),        VTX(0, -30, 0, 0, 160, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(300, -30, 0, 9600, 160, 0xFF, 0xFF, 0xFF, 0xFF), VTX(300, -25, 0, 9600, 0, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(0, -30, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF),        VTX(0, -35, 0, 0, 160, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(300, -35, 0, 9600, 160, 0xFF, 0xFF, 0xFF, 0xFF), VTX(300, -30, 0, 9600, 0, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(0, -35, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF),        VTX(0, -40, 0, 0, 160, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(300, -40, 0, 9600, 160, 0xFF, 0xFF, 0xFF, 0xFF), VTX(300, -35, 0, 9600, 0, 0xFF, 0xFF, 0xFF, 0xFF),
};
static Gfx gComputerRootDL[] = {
    gsSPSetGeometryMode(G_CULL_BACK),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_PASS2),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPLoadTextureTile(0x0F000000, G_IM_FMT_RGBA, G_IM_SIZ_16b, 300, 0, 0, 0, 299, 4, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(gComputerSelectionBarVertices0, 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsDPLoadTextureTile(0x0F000BB8, G_IM_FMT_RGBA, G_IM_SIZ_16b, 300, 0, 0, 0, 299, 4, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(gComputerSelectionBarVertices1, 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsDPLoadTextureTile(0x0F001770, G_IM_FMT_RGBA, G_IM_SIZ_16b, 300, 0, 0, 0, 299, 4, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(gComputerSelectionBarVertices2, 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsDPLoadTextureTile(0x0F002328, G_IM_FMT_RGBA, G_IM_SIZ_16b, 300, 0, 0, 0, 299, 4, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(gComputerSelectionBarVertices3, 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsDPLoadTextureTile(0x0F002EE0, G_IM_FMT_RGBA, G_IM_SIZ_16b, 300, 0, 0, 0, 299, 4, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(gComputerSelectionBarVertices4, 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsDPLoadTextureTile(0x0F003A98, G_IM_FMT_RGBA, G_IM_SIZ_16b, 300, 0, 0, 0, 299, 4, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(gComputerSelectionBarVertices5, 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsDPLoadTextureTile(0x0F004650, G_IM_FMT_RGBA, G_IM_SIZ_16b, 300, 0, 0, 0, 299, 4, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(gComputerSelectionBarVertices6, 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsDPLoadTextureTile(0x0F005208, G_IM_FMT_RGBA, G_IM_SIZ_16b, 300, 0, 0, 0, 299, 4, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(gComputerSelectionBarVertices7, 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsDPLoadTextureTile(0x0F005DC0, G_IM_FMT_RGBA, G_IM_SIZ_16b, 300, 0, 0, 0, 299, 4, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(gComputerSelectionBarVertices8, 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsDPLoadTextureTile(0x0F006978, G_IM_FMT_RGBA, G_IM_SIZ_16b, 300, 0, 0, 0, 299, 4, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(gComputerSelectionBarVertices9, 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsDPLoadTextureTile(0x0F007530, G_IM_FMT_RGBA, G_IM_SIZ_16b, 300, 0, 0, 0, 299, 4, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(gComputerSelectionBarVertices10, 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsDPLoadTextureTile(0x0F0080E8, G_IM_FMT_RGBA, G_IM_SIZ_16b, 300, 0, 0, 0, 299, 4, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(gComputerSelectionBarVertices11, 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsDPLoadTextureTile(0x0F008CA0, G_IM_FMT_RGBA, G_IM_SIZ_16b, 300, 0, 0, 0, 299, 4, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(gComputerSelectionBarVertices12, 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsDPLoadTextureTile(0x0F009858, G_IM_FMT_RGBA, G_IM_SIZ_16b, 300, 0, 0, 0, 299, 4, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(gComputerSelectionBarVertices13, 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsDPLoadTextureTile(0x0F00A410, G_IM_FMT_RGBA, G_IM_SIZ_16b, 300, 0, 0, 0, 299, 4, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(gComputerSelectionBarVertices14, 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsDPLoadTextureTile(0x0F00AFC8, G_IM_FMT_RGBA, G_IM_SIZ_16b, 300, 0, 0, 0, 299, 4, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                        G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(gComputerSelectionBarVertices15, 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSPEndDisplayList(),
};
static u32 gItemSelectionDescriptor[] = {
    0x17000000, 0x00000000, 0x00000000,    0x00000000, gComputerSelectionVertices, 0x05000000, 0x22040000,
    0x00000000, 0x08000000, DrawComputerRootUI, 0x00000000, 0x06000000, 0x01000000, 0x00000000,
};

static Vtx gItemSelectionVertices[][4] = {
    {
        VTX(-32, 32, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF),
        VTX(-32, 16, 0, 0, 512, 0xFF, 0xFF, 0xFF, 0xFF),
        VTX(32, 16, 0, 2048, 512, 0xFF, 0xFF, 0xFF, 0xFF),
        VTX(32, 32, 0, 2048, 0, 0xFF, 0xFF, 0xFF, 0xFF),
    },
    {
        VTX(-32, 16, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF),
        VTX(-32, 0, 0, 0, 512, 0xFF, 0xFF, 0xFF, 0xFF),
        VTX(32, 0, 0, 2048, 512, 0xFF, 0xFF, 0xFF, 0xFF),
        VTX(32, 16, 0, 2048, 0, 0xFF, 0xFF, 0xFF, 0xFF),
    },
    {
        VTX(-32, 0, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF),
        VTX(-32, -16, 0, 0, 512, 0xFF, 0xFF, 0xFF, 0xFF),
        VTX(32, -16, 0, 2048, 512, 0xFF, 0xFF, 0xFF, 0xFF),
        VTX(32, 0, 0, 2048, 0, 0xFF, 0xFF, 0xFF, 0xFF),
    },
    {
        VTX(-32, -16, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF),
        VTX(-32, -32, 0, 0, 512, 0xFF, 0xFF, 0xFF, 0xFF),
        VTX(32, -32, 0, 2048, 512, 0xFF, 0xFF, 0xFF, 0xFF),
        VTX(32, -16, 0, 2048, 0, 0xFF, 0xFF, 0xFF, 0xFF),
    },
};
static Gfx gItemSelectionBaseDL[] = {
    gsSPClearGeometryMode(G_CULL_BACK),
    gsDPSetCombineLERP(TEXEL0, TEXEL1, PRIM_LOD_FRAC, TEXEL1, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsSPEndDisplayList(),
};
static u32 gItemSelectionUIDescriptor[] = {
    0x17000000, 0x00000000, 0x00000000,    0x00000000, gItemSelectionVertices, 0x05000000, 0x22040000,
    0x00000000, 0x08000000, DrawItemSelectionUI, 0x00000000, 0x06000000, 0x01000000, 0x00000000,
};

static Vtx gIconQuadVertices[] = {
    VTX(-32, 22, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(-32, 0, 0, 0, 704, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(0, 0, 0, 1024, 704, 0xFF, 0xFF, 0xFF, 0xFF),
    VTX(0, 22, 0, 1024, 0, 0xFF, 0xFF, 0xFF, 0xFF),
};
static Gfx gIconDL[] = {
    gsSPSetGeometryMode(G_CULL_BACK),
    gsDPSetCombineLERP(0, 0, 0, TEXEL0, TEXEL0, 0, ENVIRONMENT, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPLoadTextureBlock(0x010031D0, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 22, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                         G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(gIconQuadVertices, 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSPEndDisplayList(),
};
static u32 gUIDrawIconDescriptor[] = {
    0x17000000, 0x00000000, 0x00000000,    0x00000000, gIconQuadVertices, 0x05000000, 0x22040000,
    0x00000000, 0x08000000, UI_DrawIcon, 0x00000000, 0x06000000, 0x01000000,
};
static u32 gUILayoutConfig[] = {
    0x0C000000,  0x05000000, 0x0B00002D, 0x00000000, 0x028001E0, 0x00000000, 0xFDBD0000,
    0x00000243,  0x05000000, 0x0D000000, 0x05000000, 0x0F000002, 0x05000000, 0x0A000000,
    &gGraphRoot0, 0x06000000, 0x06000000, 0x06000000, 0x06000000, 0x01000000,
};

static s32 gItemIdList[] = { 1, 2, 3, 5, 6, 9, 0xD, 0xF, 0x10 };
static u8* gStatusIconTextures0[] = {
    D_0302EE00, D_03034580, D_03039D00, D_0303F480, D_03044C00,
    D_0304A380, D_0304FB00, D_03055280, D_0305AA00, D_03060180,
};
static u8* gStatusIconTextures1[] = {
    D_03065900, D_03069528, D_0306D150, D_03070D78, D_030749A0,
    D_030785C8, D_0307C1F0, D_0307FE18, D_03083A40, D_03087668,
};
static s16 gCategoryMapA[] = { 2, 1, 0, 0 };
static s16 gCategoryMapB[] = { 3, 2, 1, 0 };
static s16 gItemCategoryMap[] = { 4, 0, 1, 6, 3, 2, 7, 8, 5, 0 };
static s16 gExtendedItemMap[] = { 2, 0, 1, 4, 5, 3, 8, 6, 7, 0, 0x8250, 0x8A20 };
static u8* gIconTexturePointers[] = { D_0300BB80, D_03017700 };
static u8* gItemSelectionIconTextures[9][4] = {
    D_0308B290, D_0308D290, D_0308F290, D_0308D290, D_03091290, D_03093290, D_03095290, D_03093290, D_03097290,
    D_03099290, D_0309B290, D_03099290, D_0309D290, D_0309F290, D_030A1290, D_0309F290, D_030A3290, D_030A5290,
    D_030A7290, D_030A5290, D_030A9290, D_030AB290, D_030AD290, D_030AB290, D_030AF290, D_030B1290, D_030B3290,
    D_030B1290, D_030B5290, D_030B7290, D_030B9290, D_030B7290, D_030BB290, D_030BD290, D_030BF290, D_030BD290,
};

s32 DrawStatusIconForPlayer(s32 arg0, GraphNode* arg1) {
    s32 var_v0;
    s32 tmp;
    u32 var_a2;
    Gfx* var_a3;

    if (arg0 == 5) {
        tmp = gDefaultGraphRoot->unk_000.unk_14;
        var_v0 = 0;
        if ((tmp == D_8250A288.unk_00) && (D_8250A26C != 7)) {
            var_v0 = (gSelectionFrameCounter % 30u) / 3;
        }

        if (tmp == 0) {
            var_a2 = gStatusIconTextures0[var_v0];
            var_a3 = gStatusIconAnimDL;
        } else {
            var_a2 = gStatusIconTextures1[var_v0];
            var_a3 = gStatusIconAltAnimDL;
        }

        gDPPipeSync(gDisplayListHead++);
        gSPSegment(gDisplayListHead++, 0x0F, Memmap_GetSegmentVaddr(gIconTexturePointers[tmp]));
        gSPSegment(gDisplayListHead++, 0x0E, Memmap_GetSegmentVaddr(var_a2));
        gSPDisplayList(gDisplayListHead++, gStatusIconDL);
        gSPDisplayList(gDisplayListHead++, var_a3);

        Gfx_ResetRenderState();
    }
    return 0;
}

s32 DrawComputerSelection(s32 arg0, GraphNode* arg1) {
    if (arg0 == 5) {
        s32 tmp = gDefaultGraphRoot->unk_000.unk_14;

        gDPPipeSync(gDisplayListHead++);

        if (tmp == 0) {
            gSPSegment(gDisplayListHead++, 0x0F, (u32)gComputerUIElements[tmp]->unk_38->img_p & 0x1FFFFFFF);
            gSPDisplayList(gDisplayListHead++, gComputerSelectionDL);
        } else {
            u8* var_a2;
            s32 temp_lo = (gSelectionFrameCounter % 30u) / 3;
            Gfx* var_a3;

            if (gComputerUIElements[1]->unk_0A == 0) {
                var_a2 = gStatusIconTextures0[temp_lo];
                var_a3 = gStatusIconAnimDL;
            } else {
                var_a2 = gStatusIconTextures1[temp_lo];
                var_a3 = gStatusIconAltAnimDL;
            }

            gSPSegment(gDisplayListHead++, 0x0F, Memmap_GetSegmentVaddr(D_3023280));
            gSPSegment(gDisplayListHead++, 0x0E, Memmap_GetSegmentVaddr(var_a2));
            gSPDisplayList(gDisplayListHead++, gComputerSelectionDL);
            gSPDisplayList(gDisplayListHead++, var_a3);
        }
        Gfx_ResetRenderState();
    }

    return 0;
}

s32 DrawComputerRootUI(s32 arg0, GraphNode* arg1) {
    if (arg0 == 5) {
        gDPPipeSync(gDisplayListHead++);
        gSPSegment(gDisplayListHead++, 0x0F, (u32)gComputerUIRoot->unk_38->img_p & 0x1FFFFFFF);
        gSPDisplayList(gDisplayListHead++, gComputerRootDL);

        Gfx_ResetRenderState();
    }
    return 0;
}

s32 DrawItemSelectionUI(s32 arg0, GraphNode* arg1) {
    UNUSED s32 pad;
    s32 var_a0;
    u32 var_a2;
    s32 i;
    void* ptr1;
    void* ptr2;
    s32 idx;
    s32 idx2;
    s32 idx3;

    if (arg0 == 5) {
        idx = gDefaultGraphRoot->unk_000.unk_14;

        idx2 = gItemGridElements[idx]->unk_0A;
        idx3 = gItemGridElements[idx]->unk_0C;

        var_a0 = 0;

        if ((D_8250A288.unk_06 == idx2) && (D_8250A26C == 5)) {
            var_a0 = 1;
        }

        if (var_a0 != 0) {
            var_a2 = (gSelectionFrameCounter % 12u) / 3;
        } else {
            var_a2 = 0;
        }

        ptr1 = gItemSelectionIconTextures[idx2][var_a2];
        ptr2 = gItemSelectionIconTextures[idx3][var_a2];

        gSPSegment(gDisplayListHead++, 0x0F, Memmap_GetSegmentVaddr(ptr1));
        gSPSegment(gDisplayListHead++, 0x0E, Memmap_GetSegmentVaddr(ptr2));
        gSPDisplayList(gDisplayListHead++, gItemSelectionBaseDL);

        for (i = 0; i < 4; i++) {
            gDPPipeSync(gDisplayListHead++);

            var_a2 = i * 0x800;

            gDPSetPrimColor(gDisplayListHead++, 0, gItemGridElements[idx]->unk_0E[i], 0, 0, 0, 255);
            gDPLoadTextureBlock(gDisplayListHead++, 0x0F000000 + var_a2, G_IM_FMT_RGBA, G_IM_SIZ_16b, 64, 16, 0,
                                G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK,
                                G_TX_NOLOD, G_TX_NOLOD);

            gDPLoadMultiBlock(gDisplayListHead++, 0x0E000000 + var_a2, 0x0100, 1, G_IM_FMT_RGBA, G_IM_SIZ_16b, 64, 16,
                              0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK,
                              G_TX_NOLOD, G_TX_NOLOD);
            gSPVertex(gDisplayListHead++, &gItemSelectionVertices[i], 4, 0);
            gSP2Triangles(gDisplayListHead++, 0, 1, 2, 0, 0, 2, 3, 0);
        }

        Gfx_ResetRenderState();
    }
    return 0;
}

void UI_Cursor_Init(void) {
    GraphRootNode* ptr = &gCursor.unk_000.unk_000;

    gCursor.unk_16C = 0;
    gCursor.unk_168 = 0;
    gCursor.unk_16A = 0;
    gCursor.unk_16E = 0;
    gCursor.unk_170 = 0;
    Graph_AddToRootList0(&gCursor.unk_000);
    Vec3f_Set(&gCursor.unk_000.unk_024, -220.0f, 140.0f, -579.0f);
    GraphNode_InitChild(&gCursor.unk_000, 0, 0, gSelectionHighlightNode);
    ptr->unk_01 &= ~1;
}

void UI_Cursor_Update(Fragment2_1GraphNode* a0) {
    unk_D_8250A308* arg0 = (unk_D_8250A308*)a0;
    s32 var_v0;

    arg0->unk_16E = 0;
    arg0->unk_170 = 0;

    switch (D_8250A26C) {
        case 1:
            if (UI_Element_IsState(gUIElementArray[0], 2) != 0) {
                arg0->unk_16E = 1;
                arg0->unk_168 = 0x8C;
                arg0->unk_16A = (D_8250A288.unk_00 * 0x58) + 0xBA;
                break;
            }
            break;

        case 2:
            if (UI_Element_IsState(gComputerUIElements[0], 2) != 0) {
                arg0->unk_16E = 1;
                arg0->unk_168 = 0x96;
                arg0->unk_16A = (D_8250A288.unk_02 * 0x62) + 0xBA;
            }
            break;

        case 3:
            if (UI_Element_IsState(gComputerUIRoot, 2) != 0) {
                arg0->unk_16E = 1;
                arg0->unk_168 = 0xE4;
                arg0->unk_16A = 0xDA;
            }
            break;

        case 4:
            if (gSelectionCoords.unk_00 == 2) {
                arg0->unk_16E = 1;
                arg0->unk_168 = 0xF0;
                if (gSelectionFlags & 1) {
                    var_v0 = 0x36;
                } else {
                    var_v0 = 0x48;
                }
                arg0->unk_16A = var_v0 + 0xA4 + (D_8250A288.unk_08 * 0x18);
            }
            break;

        case 5:
            if ((UI_Element_IsState(gItemGridElements[0], 2) != 0) && (gMenuSelectedOption != -1)) {
                arg0->unk_16E = 1;
                arg0->unk_170 = 1;
                arg0->unk_168 = ((D_8250A288.unk_06 % 3) * 0x60) + 0xA5;
                arg0->unk_16A = ((D_8250A288.unk_06 / 3) * 0x60) + 0xAA;
            }
            break;
    }

    if (arg0->unk_16E != 0) {
        f32 tmp1;
        f32 tmp2;

        a0->unk_01E.z = ((SINS(arg0->unk_16C) * 0.5f) + 0.5f) * -8192.0f;

        tmp1 = (((SINS(arg0->unk_16C) * 0.5f) + 0.5f) * 6.0f) + arg0->unk_168 + 32.0f;
        tmp2 = arg0->unk_16A + 22.0f;

        a0->unk_024.x = tmp1 - 320.0f;
        a0->unk_024.y = 240.0f - tmp2;
        a0->unk_01D = 0xFF;
    } else {
        a0->unk_01D = 0;
    }
    arg0->unk_16C += 0x1000;
}

s32 UI_DrawIcon(s32 arg0, GraphNode* arg1) {
    switch (arg0) {
        case 0:
            break;

        case 2:
            UI_Cursor_Update(gDefaultGraphRoot);
            break;

        case 5:
            gDPPipeSync(gDisplayListHead++);
            gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, gDefaultGraphRoot->unk_01D);
            gSPDisplayList(gDisplayListHead++, gIconDL);

            Gfx_ResetRenderState();
            break;
    }
    return 0;
}

void ControllerInput_Clear(void) {
    s32 i;
    unk_D_82508B00* ptr = &gControllerStates[0];

    for (i = 0; i < 4; i++, ptr++) {
        ptr->unk_00 = 0;
        ptr->unk_02 = 0;
        ptr->unk_04 = 0;
        ptr->unk_06 = 0;
        ptr->unk_08 = 0;
        ptr->unk_0A = 0xA;
    }
}

void ControllerInput_Update(void) {
    Controller* var_a0;
    unk_D_82508B00* var_v1;
    s32 i;
    u16 tmp;

    for (i = 0, var_v1 = &gControllerStates[0], var_a0 = &gControllers[0]; i < 4; i++, var_a0++, var_v1++) {
        var_v1->unk_00 = var_v1->unk_02;

        if (var_a0->rawStickX < -0x32) {
            var_v1->unk_02 = 0x200;
        } else if (var_a0->rawStickX > 0x32) {
            var_v1->unk_02 = 0x100;
        } else {
            var_v1->unk_02 = 0;
        }

        if (var_a0->rawStickY < -0x32) {
            var_v1->unk_02 |= 0x400;
        } else if (var_a0->rawStickY > 0x32) {
            var_v1->unk_02 |= 0x800;
        }

        tmp = var_v1->unk_00 ^ var_v1->unk_02;
        var_v1->unk_04 = tmp & var_v1->unk_02;
        var_v1->unk_06 = tmp & var_v1->unk_00;
        var_v1->unk_02 |= var_a0->buttonDown;
        var_v1->unk_04 |= var_a0->buttonPressed;
        var_v1->unk_08 = 0;

        if (var_v1->unk_04 & 0x800) {
            var_v1->unk_0A = 0xA;
            var_v1->unk_08 = 0x800;
        } else if (var_v1->unk_04 & 0x400) {
            var_v1->unk_0A = 0xA;
            var_v1->unk_08 = 0x400;
        } else if (var_v1->unk_04 & 0x200) {
            var_v1->unk_0A = 0xA;
            var_v1->unk_08 = 0x200;
        } else if (var_v1->unk_04 & 0x100) {
            var_v1->unk_0A = 0xA;
            var_v1->unk_08 = 0x100;
        } else {
            var_v1->unk_0A--;
            if (var_v1->unk_0A <= 0) {
                var_v1->unk_0A = 0;
                if (var_v1->unk_02 & 0x800) {
                    var_v1->unk_0A = 2;
                    var_v1->unk_08 = 0x800;
                } else if (var_v1->unk_02 & 0x400) {
                    var_v1->unk_0A = 2;
                    var_v1->unk_08 = 0x400;
                } else if (var_v1->unk_02 & 0x200) {
                    var_v1->unk_0A = 2;
                    var_v1->unk_08 = 0x200;
                } else if (var_v1->unk_02 & 0x100) {
                    var_v1->unk_0A = 2;
                    var_v1->unk_08 = 0x100;
                }
            }
        }
    }
}

void ToggleInputUpdate(void) {
    Cont_StartReadInputs();
    Cont_ReadInputs();
    MenuInput_Init();
    ControllerInput_Update();
}

s32 GetSelectedItemId(void) {
    s32 sp1C;

    if ((D_8250A288.unk_06 >= 0) && (D_8250A288.unk_06 < 9)) {
        sp1C = gItemIdList[D_8250A288.unk_06];
    } else {
        sp1C = 0;
    }

    if (sp1C != 0) {
        SetCurrentMenuIndex(sp1C);
    } else {
        SetCurrentMenuIndex(-1);
    }
    return sp1C;
}

s32 GetItemIndexById(s32 arg0) {
    s32 ret = 0;
    s32 i;

    for (i = 0; i < 9; i++) {
        if (arg0 == gItemIdList[i]) {
            ret = i;
            break;
        }
    }

    return ret;
}

s32 GetCategoryIndex(s16 arg0, s32 arg1) {
    s16* var_a0;
    s32 var_v0;
    s32 ret = 0;
    s32 i;

    if (arg1 != 0) {
        var_v0 = 4;
        var_a0 = gCategoryMapB;
    } else {
        var_v0 = 3;
        var_a0 = gCategoryMapA;
    }

    for (i = 0; i < var_v0; i++) {
        if (arg0 == var_a0[i]) {
            ret = i;
            break;
        }
    }

    return ret;
}

void InitItemSelectionTimer(void) {
    gItemSelectionTimer = 0x78;
    gItemSelectionRandom = GetRandomMod(3);
}

void ResetUIElement(UIElement* arg0) {
    arg0->unk_00C = 0;
    arg0->unk_000 = 0;
    arg0->unk_002 = 0;
    arg0->unk_004 = 0;
    arg0->unk_006 = 0;
    arg0->unk_008 = 0;
    arg0->unk_00E[0] = 0;
    arg0->unk_00E[1] = 0;
    arg0->unk_00E[2] = 0;
    arg0->unk_00E[3] = 0;
    arg0->unk_034 = 0;
    arg0->unk_030 = NULL;
    arg0->unk_02C = NULL;
    arg0->unk_038 = 0;
    arg0->unk_00A = arg0->unk_00C;
}

void UI_AnimatedBackground_Draw(UIElement* arg0) {
    static s16 gGradientPanelPhase = 0;
    static s16 gGradientPanelPhaseOffset = 0x3200;

    u8* var_s2;
    f32 temp_fs3 = (SINS(gGradientPanelPhase) * 0.2f) + 1.0f;
    f32 temp_fs4 = (SINS(gGradientPanelPhase + gGradientPanelPhaseOffset) * 0.2f) + 1.0f;
    s16 temp_fa0;
    s16 temp_fv1;
    s32 i;

    gGradientPanelPhase += 0x2000;

    Gfx_SetupFrameBuffer(&gDisplayListHead, arg0->unk_038);
    Gfx_FillScreen(&gDisplayListHead, 0);

    gSPDisplayList(gDisplayListHead++, gPrefDL_Border);
    gDPSetBlendColor(gDisplayListHead++, 255, 255, 255, 128);
    gDPSetAlphaCompare(gDisplayListHead++, G_AC_THRESHOLD);

    var_s2 = D_30C1290;
    for (i = 0; i < 16; i++) {
        gDPLoadTextureTile(gDisplayListHead++, var_s2, G_IM_FMT_RGBA, G_IM_SIZ_16b, 300, 0, 0, 0, 299, 4, 0,
                           G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                           G_TX_NOLOD);

        Gfx_DrawTextureRect(0, i * 5, 0x12C, 5, 0, 0, 0x400, 0x400, 0);
        var_s2 += 0xBB8;
    }

    gSPDisplayList(gDisplayListHead++, gPrefDL_End);
    gSPDisplayList(gDisplayListHead++, gPrefDL_Border);

    for (i = 0; i < 4; i++) {
        if (gMiniHudColorDefaults[i] == 0) {
            temp_fv1 = ROUND_MAX((temp_fs3 - 1.0f) * 36.0f * 0.5f);
            temp_fa0 = ROUND_MAX((temp_fs4 - 1.0f) * 26.0f * 0.5f);

            DrawScaledTextureRect(i, ((i * 0x48) - temp_fv1) + 0x1A, 0x1A - temp_fa0, temp_fs3, temp_fs4);
        } else {
            DrawUniformScaledTextureRect(-5, (i * 0x48) + 0x1A, 0x1A, 1.0f);
        }
    }

    gSPDisplayList(gDisplayListHead++, gPrefDL_End);
}

static const char gStr_ComputerStrength[] = "コンピュータのつよさ";

void UI_GradientPanel_Draw(UIElement* arg0) {
    s32 var_v1;
    u8* var_s2;
    s16 temp_v0;
    s16 sp90[3];
    s32 i;

    Gfx_SetupFrameBuffer(&gDisplayListHead, arg0->unk_038);
    Gfx_FillScreen(&gDisplayListHead, 0);

    gSPDisplayList(gDisplayListHead++, gPrefDL_Border);
    gDPSetBlendColor(gDisplayListHead++, 255, 255, 255, 128);
    gDPSetAlphaCompare(gDisplayListHead++, G_AC_THRESHOLD);

    var_s2 = D_3000000;
    for (i = 0; i < 16; i++) {
        gDPLoadTextureTile(gDisplayListHead++, var_s2, G_IM_FMT_RGBA, G_IM_SIZ_16b, 300, 0, 0, 0, 299, 4, 0,
                           G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                           G_TX_NOLOD);

        Gfx_DrawTextureRect(0, i * 5, 0x12C, 5, 0, 0, 0x400, 0x400, 0);
        var_s2 += 0xBB8;
    }

    gSPDisplayList(gDisplayListHead++, gPrefDL_End);

    if ((gUnused0 == 1) || (gUnused0 == 2)) {
        var_v1 = D_8250A288.unk_04 - 1;
        for (i = 0; i < 3; i++) {
            temp_v0 = var_v1++;
            if ((temp_v0 <= 0) || (temp_v0 >= 0xA)) {
                temp_v0 = -1;
            }
            sp90[i] = temp_v0;
        }
    } else {
        for (i = 0; i < 3; i++) {
            sp90[i] = -1;
        }
        sp90[1] = D_8250A288.unk_04;
    }

    Gfx_SetScissorRect(&gDisplayListHead, 0x6E, 0xE, 0x1C, 0x1A);
    Text_ResetState();
    Text_SetFont(0x10, 0);
    Text_SetEnvColor(0xFF, 0xFF, 0xFF, 0xFF);

    for (i = 0; i < 3; i++) {
        if (sp90[i] == -1) {
            continue;
        }
        Text_Print(0x76, (gUnused2 - (i * 0x1A)) + 0x28, "%d", sp90[i]);
    }

    Text_SetupDL();
}

unk_D_8250A228* UI_Element_Allocate(void) {
    s32 i;
    UIElement* var_v1 = gUIElements;

    for (i = 0; i < 14; i++, var_v1++) {
        if (var_v1->unk_000 == 0) {
            break;
        }
    }

    if (i == 0xE) {
        var_v1 = NULL;
    }
    return var_v1;
}

unk_D_8250A228* UI_Element_Create(s16 arg0, s16 arg1, GraphNode* arg2) {
    unk_D_8250A228* temp_v0 = UI_Element_Allocate();
    UIElementNode* temp_s1;

    if (temp_v0 == NULL) {
        return NULL;
    }

    temp_s1 = &temp_v0->unk_3C;

    temp_v0->unk_00 = arg0;
    temp_v0->unk_02 = 0;
    temp_v0->unk_04 = arg1;
    Graph_AddToRootList0(temp_s1);
    temp_s1->unk_1E = -0x4000;
    GraphNode_InitChild(temp_s1, 0, 0, arg2);
    temp_s1->unk_01 &= ~1;

    switch (temp_v0->unk_00) {
        case 1:
            temp_v0->unk_38 = NULL;
            Vec3f_Set(&temp_s1->unk_24, -150.0f, 240.0f - ((arg1 * 88.0f) + 196.0f), -579.0f);
            temp_s1->unk_14 = arg1;
            break;

        case 2:
            if (arg1 == 0) {
                temp_v0->unk_38 = FramebufferImage_Allocate(0, 2, 0x12C, 0x50, 1);
                temp_v0->unk_06 |= 1;
            } else {
                temp_v0->unk_38 = NULL;
            }
            Vec3f_Set(&temp_s1->unk_24, -150.0f, 240.0f - ((arg1 * 98.0f) + 190.0f), -579.0f);
            temp_s1->unk_14 = arg1;
            break;

        case 3:
            temp_v0->unk_38 = FramebufferImage_Allocate(0, 2, 0x12C, 0x50, 1);
            temp_v0->unk_06 |= 1;
            Vec3f_Set(&temp_s1->unk_24, -150.0f, 0.0f, -579.0f);
            break;

        case 4:
            temp_v0->unk_38 = NULL;
            temp_v0->unk_0C = temp_v0->unk_04;
            temp_v0->unk_0A = temp_v0->unk_04;
            Vec3f_Set(&temp_s1->unk_24, (((arg1 % 3) * 96.0f) + 224.0f) - 320.0f,
                          240.0f - (((arg1 / 3) * 96.0f) + 156.0f), -579.0f);
            temp_s1->unk_14 = arg1;
            temp_s1->unk_30.x = temp_s1->unk_30.y = temp_s1->unk_30.z = 1.2f;
            break;
    }
    return temp_v0;
}

void LinkUIElementsForward(unk_D_8250A228* arg0, unk_D_8250A228* arg1) {
    if (arg0 != NULL) {
        arg0->unk_30 = arg1;
    }

    if (arg1 != NULL) {
        arg1->unk_2C = arg0;
    }
}

void SetUIElementNext(unk_D_8250A228* arg0, unk_D_8250A228* arg1) {
    if (arg0 != NULL) {
        arg0->unk_34 = arg1;
    }
}

void SetUIElementState(unk_D_8250A228* arg0, s16 arg1) {
    s32 var_v0;
    s32 i;

    arg0->unk_02 = arg1;

    if ((arg0 == NULL) || (arg0->unk_00 == 0)) {
        return;
    }

    var_v0 = 0;

    switch (arg0->unk_02) {
        case 1:
            arg0->unk_06 |= 1;
            arg0->unk_08 = 0xA;
            arg0->unk_3C.unk_01 |= 1;
            arg0->unk_0E[0] = 0xFF;
            arg0->unk_0E[1] = 0xFF;
            arg0->unk_0E[2] = 0xFF;
            arg0->unk_0E[3] = 0xFF;

            if (arg0->unk_34 != NULL) {
                var_v0 = 1;
            }

            if ((arg0->unk_00 == 4) && (gMenuSelectedOption == -1)) {
                arg0->unk_06 |= 2;
            }
            break;

        case 3:
            arg0->unk_08 = 0xA;
            if (arg0->unk_34 != NULL) {
                var_v0 = 1;
            }
            break;

        case 5:
            arg0->unk_08 = 0xA;
            arg0->unk_0C = D_8250A288.unk_06;

            for (i = 0; i < 4; i++) {
                arg0->unk_0E[i] = 0xFF;
            }

            if (arg0->unk_34 != NULL) {
                var_v0 = 1;
            }
            break;

        case 8:
            arg0->unk_08 = 0xA;
            if (arg0->unk_34 != NULL) {
                var_v0 = 1;
            }
            break;

        case 7:
            arg0->unk_08 = 0xA;
            if (arg0->unk_34 != NULL) {
                var_v0 = 1;
            }
            arg0->unk_3C.unk_01 |= 1;
            break;
    }

    if (var_v0 != 0) {
        SetUIElementState(arg0->unk_34, arg0->unk_02);
    }
}

void SetUIElementSelection(unk_D_8250A228* arg0, s16 arg1, s32 arg2) {
    if (arg2 != 0) {
        if (arg0->unk_0A != arg0->unk_0C) {
            arg0->unk_0A = arg0->unk_0C;
        }
    }
    arg0->unk_08 = 6;
    arg0->unk_0C = arg1;
}

s32 UI_Element_IsState(unk_D_8250A228* arg0, s16 arg1) {
    s32 ret = 0;

    if (arg0 == NULL) {
        return 0;
    }

    if (arg0->unk_00 == 0) {
        return 0;
    }

    if (arg1 == arg0->unk_02) {
        ret = 1;
    }
    return ret;
}

void FadeOutUIElement(UIElement* arg0) {
    s32 i;

    arg0->unk_008 -= 1;
    arg0->unk_00E[0] = (arg0->unk_008 * 0xFF) / 6;

    for (i = 1; i < 4; i++) {
        arg0->unk_00E[i] = arg0->unk_00E[0];
    }

    if (arg0->unk_008 <= 0) {
        arg0->unk_00A = arg0->unk_00C;
    }
}

s32 CountUIElementColors(unk_D_8250A228* arg0, s16 arg1) {
    s32 var_v1 = 0;
    s32 i;

    for (i = 0; i < 4; i++) {
        if (arg0->unk_0E[i] == arg1) {
            var_v1++;
        }
    }

    return var_v1;
}

s32 UpdateUIElementAnimation(UIElement* arg0) {
    s16 var_v0;
    s32 var_a1;
    s32 var_v1;
    s32 i;

    if (arg0->unk_008 >= -0x10) {
        arg0->unk_008--;
    }

    for (i = 0; i < 4; i++) {
        if (arg0->unk_004 & 1) {
            var_a1 = 3 - i;
        } else {
            var_a1 = i;
        }

        var_v0 = arg0->unk_008 + (i * 4);
        if (var_v0 < 0) {
            var_v0 = 0;
        }

        if (var_v0 >= 0xB) {
            var_v0 = 0xA;
        }

        arg0->unk_00E[var_a1] = (var_v0 * 0xFF) / 10;
    }

    if (CountUIElementColors(arg0, 0) >= 2) {
        var_v1 = 1;
    } else {
        var_v1 = 0;
    }

    return var_v1;
}

void UpdateAllUIElements(void) {
    UNUSED s32 pad;
    s32 i;
    f32 temp_fa1;
    UIElement* var_s0 = &gUIElements;
    UIElementNode* temp_v0;

    for (i = 0; i < 14; i++, var_s0++) {
        temp_v0 = &var_s0->unk_03C;

        if (var_s0->unk_000 == 0) {
            continue;
        }

        switch (var_s0->unk_002) {
            case 0:
                break;

            case 1:
                var_s0->unk_008--;
                temp_v0->unk_1E = (((0xA - var_s0->unk_008) << 0xE) / 10) - 0x4000;
                if (var_s0->unk_008 <= 0) {
                    temp_v0->unk_1E = 0;
                    var_s0->unk_002 = 2;
                    var_s0->unk_008 = 0;
                }
                break;

            case 2:
                if ((var_s0->unk_006 & 2) && (var_s0->unk_00A != var_s0->unk_00C)) {
                    FadeOutUIElement(var_s0);
                }
                break;

            case 3:
                var_s0->unk_008--;
                temp_v0->unk_1E = ((0xA - var_s0->unk_008) << 0xE) / 10;
                if (var_s0->unk_008 <= 0) {
                    var_s0->unk_002 = 4;
                    var_s0->unk_008 = 0;
                    temp_v0->unk_1E = 0x4000;
                    temp_v0->unk_01 &= ~1;
                    if (var_s0->unk_030 != NULL) {
                        SetUIElementState(var_s0->unk_030, 1);
                    }
                }
                break;

            case 5:
                if (UpdateUIElementAnimation(var_s0) != 0) {
                    Vec3f sp58[] = {
                        { -1.0f, 1.0f, -1.0f }, { 0.0f, 1.0f, -1.0f }, { 1.0f, 1.0f, -1.0f },
                        { -1.0f, 0.0f, 0.0f },  { 0.0f, 0.0f, 1.0f },  { 1.0f, 0.0f, 0.0f },
                        { -1.0f, -1.0f, 1.0f }, { 0.0f, -1.0f, 1.0f }, { 1.0f, -1.0f, 1.0f },
                    };

                    var_s0->unk_002 = 6;
                    var_s0->unk_018 = 5.0f;
                    var_s0->unk_01C = 10.0f;
                    var_s0->unk_020 = sp58[var_s0->unk_004];

                    temp_fa1 = SQ(var_s0->unk_020.x) + SQ(var_s0->unk_020.y) + SQ(var_s0->unk_020.z);
                    if (temp_fa1 > 0.001f) {
                        temp_fa1 = 1.0f / sqrtf(temp_fa1);
                        var_s0->unk_020.x *= temp_fa1;
                        var_s0->unk_020.y *= temp_fa1;
                        var_s0->unk_020.z *= temp_fa1;
                    }
                }
                break;

            case 6:
                UpdateUIElementAnimation(var_s0);
                var_s0->unk_018 -= 0.5f;
                if (var_s0->unk_018 < 0.0f) {
                    var_s0->unk_018 = 0.0f;
                }

                var_s0->unk_01C += var_s0->unk_018;
                temp_v0->unk_24.x += (var_s0->unk_020.x * var_s0->unk_01C);
                temp_v0->unk_24.y += (var_s0->unk_020.y * var_s0->unk_01C);
                temp_v0->unk_24.z += (var_s0->unk_020.z * var_s0->unk_01C);

                if ((var_s0->unk_004 & 0xFFFFFFFF) != 4) {
                    if (var_s0->unk_004 & 1) {
                        temp_v0->unk_22 += 0x1400;
                    } else {
                        temp_v0->unk_22 -= 0x1400;
                    }
                    temp_v0->unk_1E += 0x1000;
                    temp_v0->unk_20 += 0x1000;
                } else {
                    temp_v0->unk_30.x += 0.05f;
                    temp_v0->unk_30.y = temp_v0->unk_30.z = temp_v0->unk_30.x;
                }
                break;

            case 8:
                var_s0->unk_008--;
                temp_v0->unk_1E = ((0xA - var_s0->unk_008) * -0x4000) / 10;
                if (var_s0->unk_008 <= 0) {
                    temp_v0->unk_1E = -0x4000;
                    var_s0->unk_002 = 0;
                    var_s0->unk_008 = 0;
                    temp_v0->unk_01 &= ~1;
                    if (var_s0->unk_02C != NULL) {
                        SetUIElementState(var_s0->unk_02C, 7);
                    }
                }
                break;

            case 7:
                var_s0->unk_008--;
                temp_v0->unk_1E = 0x4000 - (((0xA - var_s0->unk_008) << 0xE) / 10);
                if (var_s0->unk_008 <= 0) {
                    var_s0->unk_002 = 2;
                    var_s0->unk_008 = 0;
                    temp_v0->unk_1E = 0;
                }

                break;
        }
    }
}

void SelectionState_Clear(void) {
    gSelectionCoords.unk_00 = 0;
    gSelectionCoords.unk_02 = 0;
    gSelectionCoords.unk_04 = 0;
    gSelectionCoords.unk_06 = 0;
    gSelectionCoords.unk_08 = 0;
    gSelectionCoords.unk_0A = 0;
    gSelectionCoords.unk_0C = 0;
    gSelectionCoords.unk_0E = 0;
}

void SelectionState_InitDefaults(void) {
    D_8250A288.unk_00 = 0;
    D_8250A288.unk_02 = 0;
    D_8250A288.unk_04 = 3;
    D_8250A288.unk_06 = 0;

    if (gSelectionFlags & 1) {
        D_8250A288.unk_08 = 2;
    } else {
        D_8250A288.unk_08 = 1;
    }
}

void SelectionCursor_Update(s16 arg0, s16 arg1) {
    D_8250A288.unk_00 = gMenuCursorX;
    D_8250A288.unk_02 = arg0;
    D_8250A288.unk_04 = gMenuSubState;
    D_8250A288.unk_06 = GetItemIndexById(arg1);
    D_8250A288.unk_08 = GetCategoryIndex(gMenuState, gSelectionFlags & 1);
}

void SelectionUI_Init(s16 arg0, s16 arg1) {
    s32 i;
    s32 j;
    UIElement* ptr;

    gSubMenuState = arg0;
    if (arg1 == 0) {
        UpdateMenuRandomSeed();
    }

    D_8250A26C = 0;
    gSelectionFlags = 0;
    if (gMenuRandomSeed & 1) {
        gSelectionFlags |= 1;
    }

    SelectionState_InitDefaults();
    KidsClub_ResetTournamentState(gSubMenuState);
    gSelectionTimer = -1;

    switch (gSubMenuState) {
        case 0:
            break;

        case 1:
            SelectionCursor_Update(0, arg1);
            if (gMiniHudColorDefaults[gMenuSelectedOption] == 0) {
                gSelectionTimer = -1;
            } else {
                gSelectionTimer = GetRandomUnusedMenuSlot();
                gSelectionDelay = 0x1E;
            }
            break;

        case 4:
            SelectionCursor_Update(1, arg1);
            if (gMenuCursorX == 0) {
                gMenuSelectedOption = 0;
            } else {
                gMenuSelectedOption = -1;
                InitItemSelectionTimer();
            }

            // clang-format off
            for (i = 0; i < 9; i++) {                gMenuOptionUsedFlags[i] = 0;            }
            // clang-format on
            break;
    }

    ptr = gUIElements;
    for (i = 0; i < 14; i++, ptr++) {
        ResetUIElement(ptr);
    }

    for (i = 0; i < 2; i++) {
        gUIElementArray[i] = UI_Element_Create(1, i, gStatusIconNode);
    }

    for (i = 0; i < 2; i++) {
        gComputerUIElements[i] = UI_Element_Create(2, i, gComputerSelectionNode);
    }

    gComputerUIRoot = UI_Element_Create(3, 0, gItemSelectionNode);

    for (i = 0; i < 9; i++) {
        if (i != 4) {
            gItemGridElements[i] = UI_Element_Create(4, i, gBackgroundNode);
        }
    }

    gItemGridElements[4] = UI_Element_Create(4, 4, gBackgroundNode);
    LinkUIElementsForward(gUIElementArray[0], gComputerUIElements[0]);

    for (i = 0; i < 1; i++) {
        SetUIElementNext(gUIElementArray[i], gUIElementArray[i + 1]);
    }

    for (i = 0; i < 1; i++) {
        SetUIElementNext(gComputerUIElements[i], gComputerUIElements[i + 1]);
    }

    for (i = 0; i < 8; i++) {
        SetUIElementNext(gItemGridElements[i], gItemGridElements[i + 1]);
    }

    MessageBox_SetBank(gStringTable);
    OptionMenu_Init(gStringTable);
    SelectionState_Clear();
    UI_Cursor_Init();
}

void UI_DrawStatusIcon(void) {
    u32 var_a2_2;
    s32 sp40;
    s32 pad3C;
    s32 sp38;
    s32 pad34;
    s32 sp30 = 0;
    s32 sp2C = 0;
    s32 pad[4];
    s32 sp18;
    s32 tmp;

    switch (D_8250A26C) {
        case 1:
            sp30 = 0;
            if (UI_Element_IsState(gUIElementArray[0], 2) != 0) {
                sp30 = 1;
                sp40 = 0x8C;
                sp38 = D_8250A288.unk_00 * 0x58 + 0xBA;
                break;
            }
            break;

        case 2:
            sp30 = 0;
            gMenuSelectedOption += 0;
            if (UI_Element_IsState(gComputerUIElements[0], 2) != 0) {
                sp30 = 1;
                sp40 = 0x96;
                sp38 = D_8250A288.unk_02 * 0x62 + 0xBA;
                break;
            }
            break;

        case 3:
            sp30 = 0;
            if (UI_Element_IsState(gComputerUIRoot, 2) != 0) {
                sp30 = 1;
                sp40 = 0xE4;
                sp38 = 0xDA;
                break;
            }
            break;

        case 4:
            if (gSelectionCoords.unk_00 == 2) {
                sp30 = 1;
                sp40 = 0xDC;
                sp38 = ((gSelectionFlags & 1) ? 0x36 : 0x48) + (D_8250A288.unk_08 * 0x18) + 0xA4;
                break;
            }
            break;

        case 5:
            sp30 = 0;
            if ((UI_Element_IsState(gItemGridElements[0], 2) != 0) && (gMenuSelectedOption != -1)) {
                sp30 = 1;
                sp2C = 1;
                sp40 = ((D_8250A288.unk_06 % 3) * 0x60) + 0xA5;
                sp38 = ((D_8250A288.unk_06 / 3) * 0x60) + 0xAA;
                if (1) {}
                break;
            }
            break;
    }

    if (sp30 != 0) {
        tmp = gSelectionFrameCounter & 7;

        var_a2_2 = (tmp * 6) / 7u;
        if (gSelectionFrameCounter & 8) {
            var_a2_2 = 6 - var_a2_2;
        }
        sp18 = sp40 + var_a2_2;
        DrawStatusIcon(sp18, sp38);

        if ((sp2C != 0) && (gMenuSelectedOption >= 0)) {
            gSPDisplayList(gDisplayListHead++, gPrefDL_Border);
            gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255);

            var_a2_2 = gMenuSelectedOption;
            if (gMiniHudColorDefaults[var_a2_2] == 0) {
                DrawUniformScaledTextureRect(var_a2_2, sp18 - 0x20, sp38 - 2, 1.0f);
            } else {
                DrawUniformScaledTextureRect(-1 - (s32)var_a2_2, sp18 - 0x20, sp38 - 2, 1.0f);
            }

            gSPDisplayList(gDisplayListHead++, gPrefDL_End);
        }
    }
}

void UI_DrawPendingElements(void) {
    s32 i;
    UIElement* var_s0 = gUIElements;

    for (i = 0; i < 14; i++, var_s0++) {
        if (!(var_s0->unk_006 & 1)) {
            continue;
        }

        switch (var_s0->unk_000) {
            case 2:
                if (var_s0->unk_004 == 0) {
                    UI_AnimatedBackground_Draw(var_s0);
                }
                break;

            case 3:
                UI_GradientPanel_Draw(var_s0);
                break;
        }
        var_s0->unk_006 &= ~1;
    }
}

void UI_DrawGradientPanelWithText(void) {
    char** var_v0;
    s32 i;
    s32 var_s5;
    Color_RGB8 sp80 = { 0, 0, 30 };
    Color_RGB8 sp7C = { 0, 0, 250 };
    s32 var_s4;
    char* sp6C[3];
    char* sp5C[4];

    sp6C[0] = GetMessageString(NULL, 0, gStringTable, 4);
    sp6C[1] = GetMessageString(NULL, 0, gStringTable, 5);
    sp6C[2] = GetMessageString(NULL, 0, gStringTable, 6);
    sp5C[0] = GetMessageString(NULL, 0, gStringTable, 3);
    sp5C[1] = GetMessageString(NULL, 0, gStringTable, 4);
    sp5C[2] = GetMessageString(NULL, 0, gStringTable, 5);
    sp5C[3] = GetMessageString(NULL, 0, gStringTable, 6);

    if (gSelectionCoords.unk_00 != 0) {
        DrawGradientPanel(gSelectionCoords.unk_08, gSelectionCoords.unk_0A, gSelectionCoords.unk_0C, gSelectionCoords.unk_0E, &sp80, &sp7C);
        if (gSelectionCoords.unk_00 == 2) {
            Text_ResetState();
            Text_SetFont(0x10, 0);
            Text_SetEnvColor(0xFF, 0xFF, 0xFF, 0xFF);
            Text_Print(0x140 - (GetTextWidth(gTextObjectHandle, GetMessageString(NULL, 0, gStringTable, 2)) / 2),
                          gSelectionCoords.unk_0A + 0x18, GetMessageString(NULL, 0, gStringTable, 2));

            if (gSelectionFlags & 1) {
                var_s4 = 4;
                var_s5 = 0x36;
                var_v0 = sp5C;
            } else {
                var_s4 = 3;
                var_s5 = 0x48;
                var_v0 = sp6C;
            }

            for (i = 0; i < var_s4; i++) {
                if (i != D_8250A288.unk_08) {
                    Text_SetEnvColor(0xFF, 0xFF, 0xFF, 0xFF);
                } else {
                    Text_SetEnvColor(0xFF, 0xFF, 0, 0xFF);
                }
                Text_Print(0x140 - (GetTextWidth(gTextObjectHandle, var_v0[i]) / 2),
                              gSelectionCoords.unk_0A + var_s5 + (i * 0x18), var_v0[i]);
            }

            Text_SetupDL();
        }
    }
}

void SelectionUI_Render(void) {
    UI_DrawPendingElements();
    Stage_BeginDisplayList();
    Gfx_DrawTextureAtlas(gItemDataPtr);
    Graph_SetTextureState(gCursorNode);
    MessageBox_Render();
    OptionMenu_Render();
    UI_DrawGradientPanelWithText();
    UI_DrawStatusIcon();
    Stage_Advance();
}

void SelectionUI_Reset(void) {
    s16 tmp = D_8250A26C;
    s16 sp1C;
    s32 sp18;

    sp18 = 0;
    if (tmp == 0) {
        sp18 = 1;
    }

    D_8250A26C = 1;
    sp1C = D_8250A288.unk_00;
    SelectionState_InitDefaults();

    if (sp18 == 0) {
        D_8250A288.unk_00 = sp1C;
    }
    gSubMenuState = 0;
    KidsClub_ResetTournamentState(gSubMenuState);
}

void UI_HandleMainSelectionInput(void) {
    s32 i;
    s32 tmp;

    if (UI_Element_IsState(gUIElementArray[0], 2) == 0) {
        return;
    }

    GetRandomMod(0x80);

    tmp = D_8250A288.unk_00;
    if (gControllerInputs->unk_04 & 0x800) {
        D_8250A288.unk_00--;
        if (D_8250A288.unk_00 < 0) {
            D_8250A288.unk_00 = 1;
        }
    }

    if (gControllerInputs->unk_04 & 0x400) {
        D_8250A288.unk_00++;
        if (D_8250A288.unk_00 >= 2) {
            D_8250A288.unk_00 = 0;
        }
    }

    if (tmp != D_8250A288.unk_00) {
        PlaySoundEffect(1);
    }

    if (gControllerInputs->unk_04 & 0x8000) {
        gMenuCursorX = D_8250A288.unk_00;
        D_8250A26C = 2;
        MessageBox_SetState(1);
        D_8250A288.unk_02 = 0;

        for (i = 0; i < 4; i++) {
            gMiniHudColorDefaults[i] = 1;
        }

        gComputerUIElements[0]->unk_06 |= 1;
        if (gMenuCursorX == 0) {
            gMenuSelectedOption = 0;
            PlaySoundEffect(0xB);
        } else {
            gMenuSelectedOption = -1;
            InitItemSelectionTimer();
            PlaySoundEffect(0xC);
        }
        SetUIElementState(gUIElementArray[0], 3);
    } else if (gControllerInputs->unk_04 & 0x4000) {
        D_8250A26C = 7;
        D_8250A288.unk_06 = -1;
        Stage_SetFillColor(1);
        Stage_FadeOut(0xF);
        Stage_SetFadeColor(0xF);
        PlaySoundEffect(3);
    }
}

void SelectionUI_ConfirmChoice(void) {
    MessageBox_SetState(3);
    if (D_8250A288.unk_00 == 0) {
        D_8250A26C = 5;
        LinkUIElementsForward(gComputerUIElements[0], gItemGridElements[0]);
        OptionMenu_SetState(1, D_8250A288.unk_06);
    } else {
        D_8250A26C = 3;
        gUnused0 = 0;
        gUnused1 = 0;
        gUnused2 = 0;
        LinkUIElementsForward(gComputerUIElements[0], gComputerUIRoot);
        LinkUIElementsForward(gComputerUIRoot, gItemGridElements[0]);
    }
    SetUIElementState(*gComputerUIElements, 3);
}

void ComputerUI_HandleInput(void) {
    s32 temp_a1;
    s32 var_v1;
    s32 var_s4;
    s32 i;

    gComputerUIElements[1]->unk_0A = gMenuCursorX;
    if ((UI_Element_IsState(gComputerUIElements[0], 2) != 0) && (MessageBox_GetState() == 2)) {
        var_v1 = D_8250A288.unk_02;
        if ((gControllerInputs->unk_04 & 0x800) && (gMiniHudColorDefaults[0] == 0)) {
            D_8250A288.unk_02--;
            if (D_8250A288.unk_02 < 0) {
                D_8250A288.unk_02 = 1;
            }
        }

        if ((gControllerInputs->unk_04 & 0x400) && (gMiniHudColorDefaults[0] == 0)) {
            D_8250A288.unk_02++;
            if (D_8250A288.unk_02 >= 2) {
                D_8250A288.unk_02 = 0;
            }
        }

        if (var_v1 != D_8250A288.unk_02) {
            PlaySoundEffect(1);
        }

        var_s4 = 0;
        switch (D_8250A288.unk_02) {
            case 0:
                for (i = 0; i < 4; i++) {
                    if ((gControllerStates[i].unk_04 & 0x8000) && (gMiniHudColorDefaults[i] != 0)) {
                        var_s4 = 1;
                        gMiniHudColorDefaults[i] = 0;
                        PlaySoundEffect(0xD);
                    } else if (gControllerStates[i].unk_04 & 0x4000) {
                        if (gMiniHudColorDefaults[i] != 1) {
                            var_s4 = 1;
                            gMiniHudColorDefaults[i] = 1;
                            PlaySoundEffect(3);
                        }
                    }
                }
                break;

            case 1:
                if (gControllerInputs->unk_04 & 0x8000) {
                    var_s4 = 1;
                    gMenuCursorY = 0;

                    for (i = 0; i < 4; i++) {
                        if (gMiniHudColorDefaults[i] == 0) {
                            gMenuCursorY++;
                        }
                    }

                    if (gMenuCursorY != 4) {
                        D_8250A26C = 4;
                    } else {
                        SelectionUI_ConfirmChoice();
                    }
                    PlaySoundEffect(0xE);
                }
                break;
        }

        if ((var_s4 == 0) && (gControllerInputs->unk_04 & 0x4000)) {
            SelectionUI_Reset();
            MessageBox_SetState(3);
            SetUIElementState(gComputerUIElements[0], 8);
            PlaySoundEffect(3);
        }

        if (D_8250A26C == 2) {
            gComputerUIElements[0]->unk_06 |= 1;
        }
    }
}

void GradientPanel_Animate(void) {
    s32 var_a2;
    s32 var_v0;
    s32 tmp;

    switch (gSelectionCoords.unk_00) {
        case 0:
            gSelectionCoords.unk_00 = 1;
            gSelectionCoords.unk_02 = 0;
            gSelectionCoords.unk_04 = 8;
            gSelectionCoords.unk_06 = 0x12C;
            gSelectionCoords.unk_08 = 0x140;
            gSelectionCoords.unk_0A = 0xF0;
            gSelectionCoords.unk_0C = gSelectionCoords.unk_0E = 0;
            break;

        case 1:
            gSelectionCoords.unk_04 -= 1;
            gSelectionCoords.unk_08 = ((gSelectionCoords.unk_04 * 0x8C) / 8) + 0xB4;
            gSelectionCoords.unk_0A = ((gSelectionCoords.unk_04 * 0x54) / 8) + 0x9C;
            gSelectionCoords.unk_0C = 0x118 - ((gSelectionCoords.unk_04 * 0x118) / 8);
            gSelectionCoords.unk_0E = 0xA8 - ((gSelectionCoords.unk_04 * 0xA8) / 8);
            if (gSelectionCoords.unk_04 <= 0) {
                gSelectionCoords.unk_00 = 2;
            }
            break;

        case 2:
            var_v0 = 0;
            if (gSelectionFlags & 1) {
                var_a2 = 4;
                if (!(gControllerInputs->unk_02 & 0xCC00)) {
                    var_v0 = 1;
                }
            } else {
                var_a2 = 3;
            }

            if (var_v0 == 0) {
                gSelectionCoords.unk_06 = 0x12C;
            } else if (gSelectionCoords.unk_06 > 0) {
                gSelectionCoords.unk_06 -= 1;
            }

            tmp = D_8250A288.unk_08;
            if (gControllerInputs->unk_04 & 0x800) {
                D_8250A288.unk_08 -= 1;
                if (D_8250A288.unk_08 < 0) {
                    D_8250A288.unk_08 = var_a2 - 1;
                }
            }

            if (gControllerInputs->unk_04 & 0x400) {
                D_8250A288.unk_08 += 1;
                if (D_8250A288.unk_08 >= var_a2) {
                    D_8250A288.unk_08 = 0;
                }
            }

            if (tmp != D_8250A288.unk_08) {
                PlaySoundEffect(1);
            }

            if (gControllerInputs->unk_04 & 0x8000) {
                if (gSelectionFlags & 1) {
                    gMenuState = gCategoryMapB[D_8250A288.unk_08];
                } else {
                    gMenuState = gCategoryMapA[D_8250A288.unk_08];
                }
                gSelectionCoords.unk_00 = 3;
                gSelectionCoords.unk_02 = 1;
                gSelectionCoords.unk_04 = 8;
                gSelectionCoords.unk_08 = 0xB4;
                gSelectionCoords.unk_0A = 0x9C;
                gSelectionCoords.unk_0C = 0x118;
                gSelectionCoords.unk_0E = 0xA8;
                PlaySoundEffect(2);
            } else if (gControllerInputs->unk_04 & 0x4000) {
                gSelectionCoords.unk_00 = 3;
                gSelectionCoords.unk_02 = 0;
                gSelectionCoords.unk_04 = 8;
                gSelectionCoords.unk_08 = 0xB4;
                gSelectionCoords.unk_0A = 0x9C;
                gSelectionCoords.unk_0C = 0x118;
                gSelectionCoords.unk_0E = 0xA8;
                PlaySoundEffect(3);
            }
            break;

        case 3:
            gSelectionCoords.unk_04 -= 1;
            gSelectionCoords.unk_08 = ((gSelectionCoords.unk_04 * -0x8C) / 8) + 0x140;
            gSelectionCoords.unk_0A = ((gSelectionCoords.unk_04 * -0x54) / 8) + 0xF0;
            gSelectionCoords.unk_0C = (gSelectionCoords.unk_04 * 0x118) / 8;
            gSelectionCoords.unk_0E = (gSelectionCoords.unk_04 * 0xA8) / 8;
            if (gSelectionCoords.unk_04 <= 0) {
                gSelectionCoords.unk_00 = 0;
                if (gSelectionCoords.unk_02 != 0) {
                    SelectionUI_ConfirmChoice();
                } else {
                    D_8250A26C = 2;
                }
            }
            break;
    }

    if (gSelectionCoords.unk_00 != 2) {
        gComputerUIElements[0]->unk_06 |= 1;
    }
}

void ComputerUIRoot_HandleInput(void) {
    s32 i;

    if (UI_Element_IsState(gComputerUIRoot, 2) != 0) {
        switch (gUnused0) {
            case 0:
                if (gControllerInputs->unk_04 & 0x8000) {
                    gMenuSubState = D_8250A288.unk_04;

                    for (i = 0; i < 4; i++) {
                        gMenuOptionTimers[i] = 0;
                    }

                    ResetSelectionState();
                    D_8250A26C = 5;
                    SetUIElementState(gComputerUIRoot, 3);
                    PlaySoundEffect(0xE);
                    OptionMenu_SetState(1, D_8250A288.unk_06);
                } else if (gControllerInputs->unk_04 & 0x4000) {
                    D_8250A26C = 2;
                    MessageBox_SetState(1);
                    SetUIElementState(gComputerUIRoot, 8);
                    PlaySoundEffect(3);
                } else if ((gControllerInputs->unk_08 & 0x800) && (D_8250A288.unk_04 < 9)) {
                    gUnused0 = 2;
                    gUnused1 = 5;
                } else if ((gControllerInputs->unk_08 & 0x400) && (D_8250A288.unk_04 >= 2)) {
                    gUnused0 = 1;
                    gUnused1 = 5;
                }

                if ((gUnused0 == 2) || (gUnused0 == 1)) {
                    PlaySoundEffect(0x10);
                }
                break;

            case 1:
                gUnused1 -= 1;
                gUnused2 = ((gUnused1 * 0x1A) / 5) - 0x1A;
                if (gUnused1 <= 0) {
                    gUnused0 = 0;
                    gUnused2 = 0;
                    D_8250A288.unk_04 -= 1;
                }
                break;

            case 2:
                gUnused1 -= 1;
                gUnused2 = 0x1A - ((gUnused1 * 0x1A) / 5);
                if (gUnused1 <= 0) {
                    gUnused0 = 0;
                    gUnused2 = 0;
                    D_8250A288.unk_04 += 1;
                }
                break;
        }
        gComputerUIRoot->unk_06 |= 1;
    }
}

s32 ItemGrid_Navigate(s16* arg0, s16 arg1) {
    s32 var_a3;
    s32 var_t0;
    s32 sp2C;
    UNUSED s32 pad[2];
    s32 temp_v0_2;
    s16 sp1E;
    s32 temp_v0_3;

    sp1E = 0;
    sp2C = *arg0;
    var_a3 = *arg0 % 3;
    var_t0 = *arg0 / 3;

    if (gSelectionTimer == -1) {
        if (gControllerStates[arg1].unk_04 & 0x800) {
            var_t0 -= 1;
            if (var_t0 < 0) {
                var_t0 = 2;
            }
        }

        if (gControllerStates[arg1].unk_04 & 0x400) {
            var_t0 += 1;
            if (var_t0 >= 3) {
                var_t0 = 0;
            }
        }

        if (gControllerStates[arg1].unk_04 & 0x200) {
            var_a3 -= 1;
            if (var_a3 < 0) {
                var_a3 = 2;
            }
        }

        if (gControllerStates[arg1].unk_04 & 0x100) {
            var_a3 += 1;
            if (var_a3 >= 3) {
                var_a3 = 0;
            }
        }

        if (gControllerStates[arg1].unk_04 & 0x8000) {
            sp1E = 1;
        } else if (gControllerStates[arg1].unk_04 & 0x4000) {
            switch (gSubMenuState) {
                case 0:
                    sp1E = -1;
                    break;

                case 1:
                case 4:
                    if (D_8250A288.unk_00 == 0) {
                        sp1E = -1;
                        gSubMenuState = 0;
                        LinkUIElementsForward(gComputerUIElements[0], gItemGridElements[0]);
                    }
                    break;
            }
        }
    } else {
        gSelectionDelay -= 1;
        if (gSelectionDelay <= 0) {
            gSelectionDelay = 0xF;

            temp_v0_2 = (gSelectionTimer % 3) - var_a3;
            if (temp_v0_2 > 0) {
                var_a3 += 1;
            } else if (temp_v0_2 < 0) {
                var_a3 -= 1;
            } else {
                temp_v0_2 = (gSelectionTimer / 3) - var_t0;
                if (temp_v0_2 > 0) {
                    var_t0 += 1;
                } else if (temp_v0_2 < 0) {
                    var_t0 -= 1;
                } else {
                    sp1E = 1;
                }
            }
        }
    }

    *arg0 = (var_t0 * 3) + var_a3;
    if (sp2C != *arg0) {
        OptionMenu_SetSelection(*arg0);
        PlaySoundEffect(1);
    }

    return sp1E;
}

s32 SelectionScreen_ProcessRandomSelection(s16* arg0, s16 arg1) {
    s32 i;
    s32 sp68;
    s16 temp_s3;
    s16 tmp;
    s16 sp50[9];

    sp68 = 0;
    if (arg1 >= 0) {
        GetRandomMod(2);
        if ((arg1 % 6) == 0) {
            *arg0 = GetRandomMod(9);
            OptionMenu_SetSelection(*arg0);

            if (arg1 != 0) {
                for (i = 0; i < 9; i++) {
                    sp50[i] = gItemGridElements[i]->unk_0C;
                }
            }

            for (i = 0; i < 9; i++) {
                if (arg1 != 0) {
                    switch (gItemSelectionRandom) {
                        case 0:
                            tmp = GetRandomMod(9);
                            temp_s3 = gItemGridElements[i]->unk_0C;
                            SetUIElementSelection(gItemGridElements[i], gItemGridElements[tmp]->unk_0C, 0);
                            gItemGridElements[tmp]->unk_0C = temp_s3;
                            break;

                        case 1:
                            tmp = gItemCategoryMap[i];
                            SetUIElementSelection(gItemGridElements[i], sp50[tmp], 0);
                            break;

                        case 2:
                            tmp = gExtendedItemMap[i];
                            SetUIElementSelection(gItemGridElements[i], sp50[tmp], 0);
                            break;
                    }
                } else {
                    SetUIElementSelection(gItemGridElements[i], *arg0, 1);
                }
            }
            PlaySoundEffect(1);
        }
    }

    if (arg1 < -0x1D) {
        sp68 = 1;
    }

    return sp68;
}

void SelectionScreen_HandleOptionUse(void) {
    s32 sp1C;
    s32 sp18;
    s32 temp_v0;
    s32 var_a2;
    s32 var_v1;

    IncrementRandomCounter();
    if (UI_Element_IsState(gItemGridElements[0], 2) != 0) {
        sp1C = 0;
        sp18 = 0;
        if (gMenuSelectedOption >= 0) {
            switch (ItemGrid_Navigate(&D_8250A288.unk_06, gMenuSelectedOption)) {
                case 1:
                    sp1C = 1;

                case -1:
                    sp18 = 1;
                    break;
            }
        } else {
            gItemSelectionTimer -= 1;
            sp1C = SelectionScreen_ProcessRandomSelection(&D_8250A288.unk_06, gItemSelectionTimer);
        }

        if (sp1C != 0) {
            D_8250A26C = 6;
            SetUIElementState(gItemGridElements[0], 5);
            gMenuOptionUsedFlags[D_8250A288.unk_06] = 1;
            PlaySoundEffect(0x11);
        } else if (sp18 != 0) {
            OptionMenu_SetState(3, -1);
            SetUIElementState(gItemGridElements[0], 8);
            D_8250A26C = 2;
            MessageBox_SetState(1);
            PlaySoundEffect(3);
        }
    }
}

void SelectionScreen_CheckMiniHudAndFade(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        if (gMiniHudColorDefaults[i] != 0) {
            continue;
        }

        if (gControllerStates[i].unk_02 & 0x20) {
            gMenuOptionFlags[i] = 1;
        } else if (gControllerStates[i].unk_02 & 0x10) {
            gMenuOptionFlags[i] = 2;
        }
    }

    if (CountUIElementColors(gItemGridElements[4], 0) >= 3) {
        D_8250A26C = 7;
        Stage_SetFillColor(1);
        Stage_FadeOut(0xA);
    }
}

void RunSelectionScreen(s16 arg0, s16 arg1) {
    s32 var_s6 = 1;
    s32 i;

    SelectionUI_Init(arg0, arg1);
    ResultScreen_SetAnimation(0x16);
    Stage_FadeIn(0xF);
    gSelectionFrameCounter = 0;

    while (var_s6 != 0) {
        ToggleInputUpdate();
        SelectionScreen_HandleInput();
        OptionMenu_Update();
        UpdateAllUIElements();
        SelectionUI_Render();

        switch (D_8250A26C) {
            case 0:
                if (Stage_GetFadeState() == 0) {
                    switch (gSubMenuState) {
                        case 0:
                            SelectionUI_Reset();
                            SetUIElementState(gUIElementArray[0], 1);
                            break;

                        case 1:
                            D_8250A26C = 5;
                            for (i = 0; i < 9; i++) {
                                SetUIElementState(gItemGridElements[i], 1);
                            }
                            OptionMenu_SetState(1, D_8250A288.unk_06);
                            break;

                        case 4:
                            D_8250A26C = 2;
                            for (i = 0; i < 2; i++) {
                                SetUIElementState(gComputerUIElements[i], 1);
                            }
                            MessageBox_SetState(1);
                            break;
                    }
                }
                break;

            case 1:
                UI_HandleMainSelectionInput();
                break;

            case 2:
                ComputerUI_HandleInput();
                break;

            case 4:
                GradientPanel_Animate();
                break;

            case 3:
                ComputerUIRoot_HandleInput();
                break;

            case 5:
                SelectionScreen_HandleOptionUse();
                break;

            case 6:
                SelectionScreen_CheckMiniHudAndFade();
                break;

            case 7:
                if (Stage_GetFadeState() == 1) {
                    var_s6 = 0;
                }
                break;
        }
        gSelectionFrameCounter++;
    }
}

void SelectionScreen_InitResources(void) {
    MemoryBlock* temp_v0;

    gControllerInputs = &gControllerStates;
    temp_v0 = state_pool_try_init(main_pool_get_available(), 0);
    gCursorNode = process_geo_layout(temp_v0, gUILayoutConfig);
    gStatusIconNode = process_geo_layout(temp_v0, gStatusIconDescriptor);
    gComputerSelectionNode = process_geo_layout(temp_v0, gComputerSelectionDescriptor);
    gItemSelectionNode = process_geo_layout(temp_v0, gItemSelectionDescriptor);
    gBackgroundNode = process_geo_layout(temp_v0, gItemSelectionUIDescriptor);
    gSelectionHighlightNode = process_geo_layout(temp_v0, gUIDrawIconDescriptor);
    mem_pool_resize_block(temp_v0);
    Graph_InitRoots();
    ControllerInput_Clear();
}

s32 SelectionScreen_Entry(s32 arg0, s32 arg1) {
    Stage* sp24;
    BinArchive* temp_v0;

    main_pool_push_state('KIDC');

    Gfx_InitBuffers(0x10000, 0);
    sp24 = Stage_Create(1, 0, 2, 0, 2, 1);
    gTextObjectHandle = Text_Init(0x10, 0);

    ASSET_LOAD(D_1000000, common_menu1_ui, 0);
    ASSET_LOAD(D_3000000, kids_club_select_ui, 0);
    gItemArchive = ASSET_LOAD2(backgrounds, 1, 1);

    gItemDataPtr = BinArchive_GetFile(gItemArchive, 4);
    gStringTable = gItemNamesBank;
    GbsEnsureBankLoaded(2);
    SelectionScreen_InitResources();
    Stage_Set(sp24);
    RunSelectionScreen(arg0, arg1);
    Stage_AdvanceN(2);
    Stage_Destroy();
    FontManager_Free();
    Gfx_FreeBuffers();

    main_pool_pop_state('KIDC');

    return GetSelectedItemId();
}
