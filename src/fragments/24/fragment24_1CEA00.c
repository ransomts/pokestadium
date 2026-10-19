#include "fragment24.h"
#include "src/1CF30.h"
#include "src/20330.h"
#include "src/22630.h"
#include "src/232C0.h"
#include "src/26820.h"
#include "src/29BA0.h"
#include "src/2D340.h"
#include "src/2E110.h"
#include "src/225A0.h"
#include "src/2E460.h"
#include "src/3FB0.h"
#include "src/49790.h"
#include "src/memmap.h"
#include "src/memory.h"
#include "src/stage_loader.h"
#include "src/fragments/25/fragment25.h"

char** D_8831A4C0;
char** gMoveListMessageTable;
char** gMsgBank_ItemNames;
char** gMoveNamesTable;
char** D_8831A4D0;
char** gMessageBank_MoveNames;
char** gMsgBank_StatNames;
s32 pad_D_8831A4DC[8];

static Color_RGBA8 D_883171D0[] = {
    { 0x31, 0x48, 0x6B, 0xFF },
    { 0x47, 0x5E, 0x80, 0xFF },
    { 0x2B, 0x40, 0x5F, 0xFF },
    { 0x31, 0x48, 0x6B, 0xFF },
};

void LabPCList_InitHeaderSelectIcon(unk_func_88001300_000* arg0, s32 arg1, s32 arg2) {
    ((func885007CC)Memmap_GetFragmentVaddr(WidgetTree_InitWidget))(arg0, sizeof(unk_func_88001300_000));
    arg0->unk_18 = LabPCList_HeaderSelectIcon_Draw;
    arg0->unk_10.posX = arg1;
    arg0->unk_10.posY = arg2;
    // clang-format off
    arg0->unk_14.posX = 0x26; arg0->unk_14.posY = 0x14;
    // clang-format on
}

s32 LabPCList_HeaderSelectIcon_Draw(unk_func_88001300_000* arg0, s32 arg1, s32 arg2) {
    u32 temp_t2;

    gDPPipeSync(gDisplayListHead++);

    gDPSetCycleType(gDisplayListHead++, G_CYC_FILL);
    gDPSetRenderMode(gDisplayListHead++, G_RM_NOOP, G_RM_NOOP2);

    // clang-format off
    temp_t2 = ((D_883171D0[0].r << 8) & 0xF800) | ((D_883171D0[0].g << 3) & 0x7C0) | ((D_883171D0[0].b >> 2) & 0x3E) | 1; gDPPipeSync(gDisplayListHead++);
    // clang-format on

    gDPSetFillColor(gDisplayListHead++, (temp_t2 << 0x10) | temp_t2);

    gDPFillRectangle(gDisplayListHead++, arg1, arg2, (arg0->unk_14.posX + arg1) - 1,
                     (arg2 + arg0->unk_14.posY) - 1);

    gDPPipeSync(gDisplayListHead++);

    gDPSetCycleType(gDisplayListHead++, G_CYC_1CYCLE);
    gDPSetRenderMode(gDisplayListHead++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
    gDPSetTexturePersp(gDisplayListHead++, G_TP_NONE);
    gDPSetTextureFilter(gDisplayListHead++, G_TF_POINT);
    gDPSetCombineMode(gDisplayListHead++, G_CC_DECALRGBA, G_CC_DECALRGBA);

    gDPLoadTextureBlock(gDisplayListHead++, gTitleScreenImageData_1, G_IM_FMT_IA, G_IM_SIZ_8b, 32, 18, 0, G_TX_NOMIRROR | G_TX_WRAP,
                        G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

    gSPTextureRectangle(gDisplayListHead++, (arg1 + 4) << 2, (arg2 + 1) << 2, (arg1 + 0x22) << 2, (arg2 + 0x13) << 2,
                        G_TX_RENDERTILE, 0, 0, 0x0400, 0x0400);

    return 0;
}

void LabPCList_DrawHeaderPokemon(unk_func_88001300_000* arg0, s32 arg1, s32 arg2) {
    ((func885007CC)Memmap_GetFragmentVaddr(WidgetTree_InitWidget))(arg0, sizeof(unk_func_88001300_000));
    arg0->unk_18 = LabPCList_HeaderPokemon_Draw;
    arg0->unk_10.posX = arg1;
    arg0->unk_10.posY = arg2;
    // clang-format off
    arg0->unk_14.posX = 0x5C; arg0->unk_14.posY = 0x14;
    // clang-format on
}

s32 LabPCList_HeaderPokemon_Draw(unk_func_88001300_000* arg0, s32 arg1, s32 arg2) {
    static Color_RGBA8 D_883171E0 = { 0xF0, 0xF0, 0xF0, 0xFF };

    char* sp1C;
    s32 temp_t2;

    gDPPipeSync(gDisplayListHead++);

    gDPSetCycleType(gDisplayListHead++, G_CYC_FILL);
    gDPSetRenderMode(gDisplayListHead++, G_RM_NOOP, G_RM_NOOP2);

    // clang-format off
    temp_t2 = ((D_883171D0[1].r << 8) & 0xF800) | ((D_883171D0[1].g << 3) & 0x7C0) | ((D_883171D0[1].b >> 2) & 0x3E) | 1; gDPPipeSync(gDisplayListHead++);
    // clang-format on

    gDPSetFillColor(gDisplayListHead++, (temp_t2 << 0x10) | temp_t2);
    gDPFillRectangle(gDisplayListHead++, arg1, arg2, (arg0->unk_14.posX + arg1) - 1,
                     (arg2 + arg0->unk_14.posY) - 1);

    Font_BeginTranslucentTextRendering();
    Text_SetEnvColor(D_883171E0.r, D_883171E0.g, D_883171E0.b, D_883171E0.a);
    Font_SetActive(4, 0);

    sp1C = Text_GetString(NULL, 0, gMoveListMessageTable, 3);
    Font_Printf(((arg0->unk_14.posX - Font_MeasureTextExtent(0, 0, sp1C)) / 2) + arg1, arg2 + 2, sp1C);
    Font_EndTexturedTextRendering();

    return 0;
}

void LabPCList_DrawHeaderNickname(unk_func_88001300_000* arg0, s32 arg1, s32 arg2) {
    ((func885007CC)Memmap_GetFragmentVaddr(WidgetTree_InitWidget))(arg0, sizeof(unk_func_88001300_000));
    arg0->unk_18 = LabPCList_HeaderNickname_Draw;
    arg0->unk_10.posX = arg1;
    arg0->unk_10.posY = arg2;
    // clang-format off
    arg0->unk_14.posX = 0x5C; arg0->unk_14.posY = 0x14;
    // clang-format on
}

s32 LabPCList_HeaderNickname_Draw(unk_func_88001300_000* arg0, s32 arg1, s32 arg2) {
    static Color_RGBA8 D_883171E4 = { 0xF0, 0xF0, 0xF0, 0xFF };

    char* sp1C;
    s32 temp_t2;

    gDPPipeSync(gDisplayListHead++);

    gDPSetCycleType(gDisplayListHead++, G_CYC_FILL);
    gDPSetRenderMode(gDisplayListHead++, G_RM_NOOP, G_RM_NOOP2);

    // clang-format off
    temp_t2 = ((D_883171D0[0].r << 8) & 0xF800) | ((D_883171D0[0].g << 3) & 0x7C0) | ((D_883171D0[0].b >> 2) & 0x3E) | 1; gDPPipeSync(gDisplayListHead++);
    // clang-format on

    gDPSetFillColor(gDisplayListHead++, (temp_t2 << 0x10) | temp_t2);
    gDPFillRectangle(gDisplayListHead++, arg1, arg2, (arg0->unk_14.posX + arg1) - 1,
                     (arg2 + arg0->unk_14.posY) - 1);

    Font_BeginTranslucentTextRendering();
    Text_SetEnvColor(D_883171E4.r, D_883171E4.g, D_883171E4.b, D_883171E4.a);
    Font_SetActive(4, 0);

    sp1C = Text_GetString(NULL, 0, gMoveListMessageTable, 4);
    Font_Printf(((arg0->unk_14.posX - Font_MeasureTextExtent(0, 0, sp1C)) / 2) + arg1, arg2 + 2, sp1C);
    Font_EndTexturedTextRendering();
    return 0;
}

void LabPCList_DrawHeaderID(unk_func_88001300_000* arg0, s32 arg1, s32 arg2) {
    ((func885007CC)Memmap_GetFragmentVaddr(WidgetTree_InitWidget))(arg0, sizeof(unk_func_88001300_000));
    arg0->unk_18 = LabPCList_HeaderID_Draw;
    arg0->unk_10.posX = arg1;
    arg0->unk_10.posY = arg2;
    // clang-format off
    arg0->unk_14.posX = 0x34; arg0->unk_14.posY = 0x14;
    // clang-format on
}

s32 LabPCList_HeaderID_Draw(unk_func_88001300_000* arg0, s32 arg1, s32 arg2) {
    static Color_RGBA8 D_883171E8 = { 0xF0, 0xF0, 0xF0, 0xFF };

    char* sp1C;
    s32 temp_t2;

    gDPPipeSync(gDisplayListHead++);

    gDPSetCycleType(gDisplayListHead++, G_CYC_FILL);
    gDPSetRenderMode(gDisplayListHead++, G_RM_NOOP, G_RM_NOOP2);

    // clang-format off
    temp_t2 = ((D_883171D0[1].r << 8) & 0xF800) | ((D_883171D0[1].g << 3) & 0x7C0) | ((D_883171D0[1].b >> 2) & 0x3E) | 1; gDPPipeSync(gDisplayListHead++);
    // clang-format on

    gDPSetFillColor(gDisplayListHead++, (temp_t2 << 0x10) | temp_t2);
    gDPFillRectangle(gDisplayListHead++, arg1, arg2, (arg0->unk_14.posX + arg1) - 1,
                     (arg2 + arg0->unk_14.posY) - 1);

    Font_BeginTranslucentTextRendering();
    Text_SetEnvColor(D_883171E8.r, D_883171E8.g, D_883171E8.b, D_883171E8.a);
    Font_SetActive(4, 0);

    sp1C = Text_GetString(NULL, 0, gMoveListMessageTable, 5);
    Font_Printf(((arg0->unk_14.posX - Font_MeasureTextExtent(0, 0, sp1C)) / 2) + arg1, arg2 + 2, sp1C);
    Font_EndTexturedTextRendering();
    return 0;
}

void LabPCList_DrawHeaderOT(unk_func_88001300_000* arg0, s32 arg1, s32 arg2) {
    ((func885007CC)Memmap_GetFragmentVaddr(WidgetTree_InitWidget))(arg0, sizeof(unk_func_88001300_000));
    arg0->unk_18 = LabPCList_HeaderOT_Draw;
    arg0->unk_10.posX = arg1;
    arg0->unk_10.posY = arg2;
    // clang-format off
    arg0->unk_14.posX = 0x4C; arg0->unk_14.posY = 0x14;
    // clang-format on
}

s32 LabPCList_HeaderOT_Draw(unk_func_88001300_000* arg0, s32 arg1, s32 arg2) {
    static Color_RGBA8 D_883171EC = { 0xF0, 0xF0, 0xF0, 0xFF };

    char* sp1C;
    s32 temp_t2;

    gDPPipeSync(gDisplayListHead++);

    gDPSetCycleType(gDisplayListHead++, G_CYC_FILL);
    gDPSetRenderMode(gDisplayListHead++, G_RM_NOOP, G_RM_NOOP2);

    // clang-format off
    temp_t2 = ((D_883171D0[0].r << 8) & 0xF800) | ((D_883171D0[0].g << 3) & 0x7C0) | ((D_883171D0[0].b >> 2) & 0x3E) | 1; gDPPipeSync(gDisplayListHead++);
    // clang-format on

    gDPSetFillColor(gDisplayListHead++, (temp_t2 << 0x10) | temp_t2);
    gDPFillRectangle(gDisplayListHead++, arg1, arg2, (arg0->unk_14.posX + arg1) - 1,
                     (arg2 + arg0->unk_14.posY) - 1);

    Font_BeginTranslucentTextRendering();
    Text_SetEnvColor(D_883171EC.r, D_883171EC.g, D_883171EC.b, D_883171EC.a);
    Font_SetActive(4, 0);

    sp1C = Text_GetString(NULL, 0, gMoveListMessageTable, 6);
    Font_Printf(((arg0->unk_14.posX - Font_MeasureTextExtent(0, 0, sp1C)) / 2) + arg1, arg2 + 2, sp1C);
    Font_EndTexturedTextRendering();
    return 0;
}

void LabPCList_DrawHeaderArea(unk_func_88001300_000* arg0, s32 arg1, s32 arg2) {
    ((func885007CC)Memmap_GetFragmentVaddr(WidgetTree_InitWidget))(arg0, sizeof(unk_func_88001300_000));
    arg0->unk_18 = LabPCList_HeaderArea_Draw;
    arg0->unk_10.posX = arg1;
    arg0->unk_10.posY = arg2;
    // clang-format off
    arg0->unk_14.posX = 0x38; arg0->unk_14.posY = 0x14;
    // clang-format on
}

s32 LabPCList_HeaderArea_Draw(unk_func_88001300_000* arg0, s32 arg1, s32 arg2) {
    static Color_RGBA8 D_883171F0 = { 0xF0, 0xF0, 0xF0, 0xFF };

    char* sp1C;
    s32 temp_t2;

    gDPPipeSync(gDisplayListHead++);

    gDPSetCycleType(gDisplayListHead++, G_CYC_FILL);
    gDPSetRenderMode(gDisplayListHead++, G_RM_NOOP, G_RM_NOOP2);

    // clang-format off
    temp_t2 = ((D_883171D0[1].r << 8) & 0xF800) | ((D_883171D0[1].g << 3) & 0x7C0) | ((D_883171D0[1].b >> 2) & 0x3E) | 1; gDPPipeSync(gDisplayListHead++);
    // clang-format on

    gDPSetFillColor(gDisplayListHead++, (temp_t2 << 0x10) | temp_t2);
    gDPFillRectangle(gDisplayListHead++, arg1, arg2, (arg0->unk_14.posX + arg1) - 1,
                     (arg2 + arg0->unk_14.posY) - 1);

    Font_BeginTranslucentTextRendering();
    Text_SetEnvColor(D_883171F0.r, D_883171F0.g, D_883171F0.b, D_883171F0.a);
    Font_SetActive(4, 0);

    sp1C = Text_GetString(NULL, 0, gMoveListMessageTable, 7);
    Font_Printf(((arg0->unk_14.posX - Font_MeasureTextExtent(0, 0, sp1C)) / 2) + arg1, arg2 + 2, sp1C);
    Font_EndTexturedTextRendering();
    return 0;
}

void LabPCList_DrawHeaderTypes(unk_func_88001300_000* arg0, s32 arg1, s32 arg2) {
    ((func885007CC)Memmap_GetFragmentVaddr(WidgetTree_InitWidget))(arg0, sizeof(unk_func_88001300_000));
    arg0->unk_18 = LabPCList_HeaderTypes_Draw;
    arg0->unk_10.posX = arg1;
    arg0->unk_10.posY = arg2;
    // clang-format off
    arg0->unk_14.posX = 0x90; arg0->unk_14.posY = 0x14;
    // clang-format on
}

s32 LabPCList_HeaderTypes_Draw(unk_func_88001300_000* arg0, s32 arg1, s32 arg2) {
    static Color_RGBA8 D_883171F4 = { 0xF0, 0xF0, 0xF0, 0xFF };

    char* sp54;

    gDPPipeSync(gDisplayListHead++);

    gDPSetCycleType(gDisplayListHead++, G_CYC_FILL);
    gDPSetRenderMode(gDisplayListHead++, G_RM_NOOP, G_RM_NOOP2);

    {
        // clang-format off
        s32 temp_t3 = ((D_883171D0[0].r << 8) & 0xF800) | ((D_883171D0[0].g << 3) & 0x7C0) | ((D_883171D0[0].b >> 2) & 0x3E) | 1; gDPPipeSync(gDisplayListHead++);
        // clang-format on
        gDPSetFillColor(gDisplayListHead++, (temp_t3 << 0x10) | temp_t3);
        gDPFillRectangle(gDisplayListHead++, arg1, arg2, arg1 + 0x47, (arg2 + arg0->unk_14.posY) - 1);
    }

    {
        // clang-format off
        s32 sp34 = ((D_883171D0[1].r << 8) & 0xF800) | ((D_883171D0[1].g * 8) & 0x7C0) | ((D_883171D0[1].b >> 2) & 0x3E) | 1; gDPPipeSync(gDisplayListHead++);
        // clang-format on
        gDPSetFillColor(gDisplayListHead++, (sp34 << 0x10) | sp34);
        gDPFillRectangle(gDisplayListHead++, arg1 + 0x48, arg2, (arg1 + (u32)arg0->unk_14.posX) - 1,
                         (arg2 + arg0->unk_14.posY) - 1);
    }

    Font_BeginTranslucentTextRendering();
    Text_SetEnvColor(D_883171F4.r, D_883171F4.g, D_883171F4.b, D_883171F4.a);
    Font_SetActive(4, 0);

    sp54 = Text_GetString(NULL, 0, gMoveListMessageTable, 8);
    Font_Printf(((0x48 - Font_MeasureTextExtent(0, 0, sp54)) / 2) + arg1, arg2 + 2, sp54);

    sp54 = Text_GetString(NULL, 0, gMoveListMessageTable, 9);
    Font_Printf(((0x48 - Font_MeasureTextExtent(0, 0, sp54)) / 2) + arg1 + 0x48, arg2 + 2, sp54);

    Font_EndTexturedTextRendering();
    return 0;
}

void LabPCList_DrawHeaderMoves(unk_func_88001300_000* arg0, s32 arg1, s32 arg2) {
    ((func885007CC)Memmap_GetFragmentVaddr(WidgetTree_InitWidget))(arg0, sizeof(unk_func_88001300_000));
    arg0->unk_18 = LabPCList_HeaderMoves_Draw;
    arg0->unk_10.posX = arg1;
    arg0->unk_10.posY = arg2;
    // clang-format off
    arg0->unk_14.posX = 0x1A4; arg0->unk_14.posY = 0x14;
    // clang-format on
}

s32 LabPCList_HeaderMoves_Draw(unk_func_88001300_000* arg0, s32 arg1, s32 arg2) {
    static Color_RGBA8 D_883171F8 = { 0xF0, 0xF0, 0xF0, 0xFF };

    char* temp_v0_16;

    gDPPipeSync(gDisplayListHead++);

    gDPSetCycleType(gDisplayListHead++, G_CYC_FILL);
    gDPSetRenderMode(gDisplayListHead++, G_RM_NOOP, G_RM_NOOP2);

    {
        // clang-format off
        s32 temp_t3 = ((D_883171D0[0].r << 8) & 0xF800) | ((D_883171D0[0].g << 3) & 0x7C0) | ((D_883171D0[0].b >> 2) & 0x3E) | 1; gDPPipeSync(gDisplayListHead++);
        // clang-format on

        gDPSetFillColor(gDisplayListHead++, (temp_t3 << 0x10) | temp_t3);
        gDPFillRectangle(gDisplayListHead++, arg1, arg2, arg1 + 0x68, (arg2 + arg0->unk_14.posY) - 1);
    }

    {
        // clang-format off
        s32 sp5C = ((D_883171D0[1].r << 8) & 0xF800) | ((D_883171D0[1].g << 3) & 0x7C0) | ((D_883171D0[1].b >> 2) & 0x3E) | 1; gDPPipeSync(gDisplayListHead++);
        // clang-format on

        gDPSetFillColor(gDisplayListHead++, (sp5C << 0x10) | sp5C);
        gDPFillRectangle(gDisplayListHead++, arg1 + 0x69, arg2, arg1 + 0xD1, (arg2 + arg0->unk_14.posY) - 1);
    }

    {
        // clang-format off
        s32 temp_a2 = ((D_883171D0[0].r << 8) & 0xF800) | ((D_883171D0[0].g << 3) & 0x7C0) | ((D_883171D0[0].b >> 2) & 0x3E) | 1; gDPPipeSync(gDisplayListHead++);
        // clang-format on

        gDPSetFillColor(gDisplayListHead++, (temp_a2 << 0x10) | temp_a2);
        gDPFillRectangle(gDisplayListHead++, arg1 + 0xD2, arg2, arg1 + 0x13A, (arg2 + arg0->unk_14.posY) - 1);
    }

    {
        // clang-format off
        s32 temp_a0 = ((D_883171D0[1].r << 8) & 0xF800) | ((D_883171D0[1].g << 3) & 0x7C0) | ((D_883171D0[1].b >> 2) & 0x3E) | 1; gDPPipeSync(gDisplayListHead++);
        // clang-format on

        gDPSetFillColor(gDisplayListHead++, (temp_a0 << 0x10) | temp_a0);
        gDPFillRectangle(gDisplayListHead++, arg1 + 0x13B, arg2, arg1 + 0x1A3, (arg2 + arg0->unk_14.posY) - 1);
    }

    Font_BeginTranslucentTextRendering();
    Text_SetEnvColor(D_883171F8.r, D_883171F8.g, D_883171F8.b, D_883171F8.a);
    Font_SetActive(4, 0);

    temp_v0_16 = Text_GetString(NULL, 0, gMoveListMessageTable, 0xA);
    Font_Printf(((0x69 - Font_MeasureTextExtent(0, 0, temp_v0_16)) / 2) + arg1, arg2 + 2, temp_v0_16);

    temp_v0_16 = Text_GetString(NULL, 0, gMoveListMessageTable, 0xB);
    Font_Printf(((0x69 - Font_MeasureTextExtent(0, 0, temp_v0_16)) / 2) + arg1 + 0x69, arg2 + 2, temp_v0_16);

    temp_v0_16 = Text_GetString(NULL, 0, gMoveListMessageTable, 0xC);
    Font_Printf(((0x69 - Font_MeasureTextExtent(0, 0, temp_v0_16)) / 2) + arg1 + 0xD2, arg2 + 2, temp_v0_16);

    temp_v0_16 = Text_GetString(NULL, 0, gMoveListMessageTable, 0xD);
    Font_Printf(((0x69 - Font_MeasureTextExtent(0, 0, temp_v0_16)) / 2) + arg1 + 0x13B, arg2 + 2, temp_v0_16);

    Font_EndTexturedTextRendering();
    return 0;
}

void LabPCList_DrawHeaderLevel(unk_func_88001300_000* arg0, s32 arg1, s32 arg2) {
    ((func885007CC)Memmap_GetFragmentVaddr(WidgetTree_InitWidget))(arg0, sizeof(unk_func_88001300_000));
    arg0->unk_18 = LabPCList_HeaderLevel_Draw;
    arg0->unk_10.posX = arg1;
    arg0->unk_10.posY = arg2;
    // clang-format off
    arg0->unk_14.posX = 0x46; arg0->unk_14.posY = 0x14;
    // clang-format on
}

s32 LabPCList_HeaderLevel_Draw(unk_func_88001300_000* arg0, s32 arg1, s32 arg2) {
    static Color_RGBA8 D_883171FC = { 0xF0, 0xF0, 0xF0, 0xFF };

    char* sp1C;
    s32 temp_t2;

    gDPPipeSync(gDisplayListHead++);

    gDPSetCycleType(gDisplayListHead++, G_CYC_FILL);
    gDPSetRenderMode(gDisplayListHead++, G_RM_NOOP, G_RM_NOOP2);

    // clang-format off
    temp_t2 = ((D_883171D0[0].r << 8) & 0xF800) | ((D_883171D0[0].g << 3) & 0x7C0) | ((D_883171D0[0].b >> 2) & 0x3E) | 1; gDPPipeSync(gDisplayListHead++);
    // clang-format on

    gDPSetFillColor(gDisplayListHead++, (temp_t2 << 0x10) | temp_t2);
    gDPFillRectangle(gDisplayListHead++, arg1, arg2, (arg0->unk_14.posX + arg1) - 1,
                     (arg2 + arg0->unk_14.posY) - 1);

    Font_BeginTranslucentTextRendering();
    Text_SetEnvColor(D_883171FC.r, D_883171FC.g, D_883171FC.b, D_883171FC.a);
    Font_SetActive(4, 0);

    sp1C = Text_GetString(NULL, 0, gMoveListMessageTable, 0xE);
    Font_Printf(((arg0->unk_14.posX - Font_MeasureTextExtent(0, 0, sp1C)) / 2) + arg1, arg2 + 2, sp1C);

    Font_EndTexturedTextRendering();
    return 0;
}

void LabPCList_DrawHeaderHp(unk_func_88001300_000* arg0, s32 arg1, s32 arg2) {
    ((func885007CC)Memmap_GetFragmentVaddr(WidgetTree_InitWidget))(arg0, sizeof(unk_func_88001300_000));
    arg0->unk_18 = LabPCList_HeaderHp_Draw;
    arg0->unk_10.posX = arg1;
    arg0->unk_10.posY = arg2;
    // clang-format off
    arg0->unk_14.posX = 0x46; arg0->unk_14.posY = 0x14;
    // clang-format on
}

s32 LabPCList_HeaderHp_Draw(unk_func_88001300_000* arg0, s32 arg1, s32 arg2) {
    static Color_RGBA8 D_88317200 = { 0xF0, 0xF0, 0xF0, 0xFF };

    char* sp1C;
    s32 temp_t2;

    gDPPipeSync(gDisplayListHead++);

    gDPSetCycleType(gDisplayListHead++, G_CYC_FILL);
    gDPSetRenderMode(gDisplayListHead++, G_RM_NOOP, G_RM_NOOP2);

    // clang-format off
    temp_t2 = ((D_883171D0[1].r << 8) & 0xF800) | ((D_883171D0[1].g << 3) & 0x7C0) | ((D_883171D0[1].b >> 2) & 0x3E) | 1; gDPPipeSync(gDisplayListHead++);
    // clang-format on

    gDPSetFillColor(gDisplayListHead++, (temp_t2 << 0x10) | temp_t2);
    gDPFillRectangle(gDisplayListHead++, arg1, arg2, (arg0->unk_14.posX + arg1) - 1,
                     (arg2 + arg0->unk_14.posY) - 1);

    Font_BeginTranslucentTextRendering();
    Text_SetEnvColor(D_88317200.r, D_88317200.g, D_88317200.b, D_88317200.a);
    Font_SetActive(4, 0);

    sp1C = Text_GetString(NULL, 0, gMoveListMessageTable, 0xF);
    Font_Printf(((arg0->unk_14.posX - Font_MeasureTextExtent(0, 0, sp1C)) / 2) + arg1, arg2 + 2, sp1C);

    Font_EndTexturedTextRendering();
    return 0;
}

void LabPCList_DrawHeaderAttack(unk_func_88001300_000* arg0, s32 arg1, s32 arg2) {
    ((func885007CC)Memmap_GetFragmentVaddr(WidgetTree_InitWidget))(arg0, sizeof(unk_func_88001300_000));
    arg0->unk_18 = LabPCList_HeaderAttack_Draw;
    arg0->unk_10.posX = arg1;
    arg0->unk_10.posY = arg2;
    // clang-format off
    arg0->unk_14.posX = 0x46; arg0->unk_14.posY = 0x14;
    // clang-format on
}

s32 LabPCList_HeaderAttack_Draw(unk_func_88001300_000* arg0, s32 arg1, s32 arg2) {
    static Color_RGBA8 D_88317204 = { 0xF0, 0xF0, 0xF0, 0xFF };

    s32 temp_t2;

    gDPPipeSync(gDisplayListHead++);

    gDPSetCycleType(gDisplayListHead++, G_CYC_FILL);
    gDPSetRenderMode(gDisplayListHead++, G_RM_NOOP, G_RM_NOOP2);

    // clang-format off
    temp_t2 = ((D_883171D0[0].r << 8) & 0xF800) | ((D_883171D0[0].g << 3) & 0x7C0) | ((D_883171D0[0].b >> 2) & 0x3E) | 1; gDPPipeSync(gDisplayListHead++);
    // clang-format on

    gDPSetFillColor(gDisplayListHead++, (temp_t2 << 0x10) | temp_t2);
    gDPFillRectangle(gDisplayListHead++, arg1, arg2, (arg0->unk_14.posX + arg1) - 1,
                     (arg2 + arg0->unk_14.posY) - 1);

    Font_BeginTranslucentTextRendering();
    Text_SetEnvColor(D_88317204.r, D_88317204.g, D_88317204.b, D_88317204.a);
    Font_SetActive(4, 0);
    Font_Printf(arg1 + 4, arg2 + 2, Text_GetString(NULL, 0, gMoveListMessageTable, 0x10));
    Font_EndTexturedTextRendering();
    return 0;
}

void LabPCList_DrawHeaderDefense(unk_func_88001300_000* arg0, s32 arg1, s32 arg2) {
    ((func885007CC)Memmap_GetFragmentVaddr(WidgetTree_InitWidget))(arg0, sizeof(unk_func_88001300_000));
    arg0->unk_18 = LabPCList_HeaderDefense_Draw;
    arg0->unk_10.posX = arg1;
    arg0->unk_10.posY = arg2;
    // clang-format off
    arg0->unk_14.posX = 0x46; arg0->unk_14.posY = 0x14;
    // clang-format on
}

s32 LabPCList_HeaderDefense_Draw(unk_func_88001300_000* arg0, s32 arg1, s32 arg2) {
    static Color_RGBA8 D_88317208 = { 0xF0, 0xF0, 0xF0, 0xFF };

    char* sp1C;
    s32 temp_t2;

    gDPPipeSync(gDisplayListHead++);

    gDPSetCycleType(gDisplayListHead++, G_CYC_FILL);
    gDPSetRenderMode(gDisplayListHead++, G_RM_NOOP, G_RM_NOOP2);

    // clang-format off
    temp_t2 = ((D_883171D0[1].r << 8) & 0xF800) | ((D_883171D0[1].g << 3) & 0x7C0) | ((D_883171D0[1].b >> 2) & 0x3E) | 1; gDPPipeSync(gDisplayListHead++);
    // clang-format on

    gDPSetFillColor(gDisplayListHead++, (temp_t2 << 0x10) | temp_t2);
    gDPFillRectangle(gDisplayListHead++, arg1, arg2, (arg0->unk_14.posX + arg1) - 1,
                     (arg2 + arg0->unk_14.posY) - 1);

    Font_BeginTranslucentTextRendering();
    Text_SetEnvColor(D_88317208.r, D_88317208.g, D_88317208.b, D_88317208.a);
    Font_SetActive(4, 0);
    sp1C = Text_GetString(NULL, 0, gMoveListMessageTable, 0x11);
    Font_Printf(((arg0->unk_14.posX - Font_MeasureTextExtent(0, 0, sp1C)) / 2) + arg1, arg2 + 2, sp1C);
    Font_EndTexturedTextRendering();
    return 0;
}

void LabPCList_DrawHeaderSpeed(unk_func_88001300_000* arg0, s32 arg1, s32 arg2) {
    ((func885007CC)Memmap_GetFragmentVaddr(WidgetTree_InitWidget))(arg0, sizeof(unk_func_88001300_000));
    arg0->unk_18 = LabPCList_HeaderSpeed_Draw;
    arg0->unk_10.posX = arg1;
    arg0->unk_10.posY = arg2;
    // clang-format off
    arg0->unk_14.posX = 0x46; arg0->unk_14.posY = 0x14;
    // clang-format on
}

s32 LabPCList_HeaderSpeed_Draw(unk_func_88001300_000* arg0, s32 arg1, s32 arg2) {
    static Color_RGBA8 D_8831720C = { 0xF0, 0xF0, 0xF0, 0xFF };

    char* sp1C;
    s32 temp_t2;

    gDPPipeSync(gDisplayListHead++);

    gDPSetCycleType(gDisplayListHead++, G_CYC_FILL);
    gDPSetRenderMode(gDisplayListHead++, G_RM_NOOP, G_RM_NOOP2);

    // clang-format off
    temp_t2 = ((D_883171D0[0].r << 8) & 0xF800) | ((D_883171D0[0].g << 3) & 0x7C0) | ((D_883171D0[0].b >> 2) & 0x3E) | 1; gDPPipeSync(gDisplayListHead++);
    // clang-format on

    gDPSetFillColor(gDisplayListHead++, (temp_t2 << 0x10) | temp_t2);
    gDPFillRectangle(gDisplayListHead++, arg1, arg2, (arg0->unk_14.posX + arg1) - 1,
                     (arg2 + arg0->unk_14.posY) - 1);

    Font_BeginTranslucentTextRendering();
    Text_SetEnvColor(D_8831720C.r, D_8831720C.g, D_8831720C.b, D_8831720C.a);
    Font_SetActive(4, 0);
    sp1C = Text_GetString(NULL, 0, gMoveListMessageTable, 0x12);
    Font_Printf(((arg0->unk_14.posX - Font_MeasureTextExtent(0, 0, sp1C)) / 2) + arg1, arg2 + 2, sp1C);
    Font_EndTexturedTextRendering();
    return 0;
}

void LabPCList_DrawHeaderSpecial(unk_func_88001300_000* arg0, s32 arg1, s32 arg2) {
    ((func885007CC)Memmap_GetFragmentVaddr(WidgetTree_InitWidget))(arg0, sizeof(unk_func_88001300_000));
    arg0->unk_18 = LabPCList_HeaderSpecial_Draw;
    arg0->unk_10.posX = arg1;
    arg0->unk_10.posY = arg2;
    // clang-format off
    arg0->unk_14.posX = 0x46; arg0->unk_14.posY = 0x14;
    // clang-format on
}

s32 LabPCList_HeaderSpecial_Draw(unk_func_88001300_000* arg0, s32 arg1, s32 arg2) {
    static Color_RGBA8 D_88317210 = { 0xF0, 0xF0, 0xF0, 0xFF };

    char* sp1C;
    s32 temp_t2;

    gDPPipeSync(gDisplayListHead++);

    gDPSetCycleType(gDisplayListHead++, G_CYC_FILL);
    gDPSetRenderMode(gDisplayListHead++, G_RM_NOOP, G_RM_NOOP2);

    // clang-format off
    temp_t2 = ((D_883171D0[1].r << 8) & 0xF800) | ((D_883171D0[1].g << 3) & 0x7C0) | ((D_883171D0[1].b >> 2) & 0x3E) | 1; gDPPipeSync(gDisplayListHead++);
    // clang-format on

    gDPSetFillColor(gDisplayListHead++, (temp_t2 << 0x10) | temp_t2);
    gDPFillRectangle(gDisplayListHead++, arg1, arg2, (arg0->unk_14.posX + arg1) - 1,
                     (arg2 + arg0->unk_14.posY) - 1);

    Font_BeginTranslucentTextRendering();
    Text_SetEnvColor(D_88317210.r, D_88317210.g, D_88317210.b, D_88317210.a);
    Font_SetActive(4, 0);
    sp1C = Text_GetString(NULL, 0, gMoveListMessageTable, 0x13);
    Font_Printf(((arg0->unk_14.posX - Font_MeasureTextExtent(0, 0, sp1C)) / 2) + arg1, arg2 + 2, sp1C);
    Font_EndTexturedTextRendering();
    return 0;
}

void LabPCList_InitColumnDivider(unk_func_8830867C_02C_050* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4,
                   unk_func_8830867C_02C* arg5) {
    ((func885007CC)Memmap_GetFragmentVaddr(WidgetTree_InitWidget))(arg0, sizeof(unk_func_8830867C_02C_050));
    arg0->posX.unk_18 = LabPCList_DrawColumnDivider;
    arg0->posX.unk_10.posX = arg1;
    arg0->posX.unk_10.posY = arg2;
    arg0->posX.unk_14.posX = arg3;
    arg0->posX.unk_14.posY = arg4;
    arg0->unk_2C = arg5;
}

s32 LabPCList_DrawColumnDivider(unk_func_8830867C_02C_050* arg0, s32 arg1, s32 arg2) {
    static Color_RGBA8 D_88317214 = { 0xFF, 0xFF, 0xFF, 0xFF };

    UNUSED s32 pad;

    gDPPipeSync(gDisplayListHead++);

    gDPSetCycleType(gDisplayListHead++, G_CYC_FILL);
    gDPSetRenderMode(gDisplayListHead++, G_RM_NOOP, G_RM_NOOP2);

    {
        s32 temp_t7 = ((D_88317214.r << 8) & 0xF800) | ((D_88317214.g << 3) & 0x7C0) | ((D_88317214.b >> 2) & 0x3E) | 1;
        gDPPipeSync(gDisplayListHead++);
        gDPSetFillColor(gDisplayListHead++, (temp_t7 << 0x10) | temp_t7);
        gDPFillRectangle(gDisplayListHead++, arg1, arg2 + 0x14, (arg0->posX.unk_14.posX + arg1) - 1, arg2 + 0x15);
    }

    {
        s32 temp_t7 = ((D_88317214.r << 8) & 0xF800) | ((D_88317214.g << 3) & 0x7C0) | ((D_88317214.b >> 2) & 0x3E) | 1;
        gDPPipeSync(gDisplayListHead++);
        gDPSetFillColor(gDisplayListHead++, (temp_t7 << 0x10) | temp_t7);
        gDPFillRectangle(gDisplayListHead++, arg1 + 0x82, arg2, arg1 + 0x83, arg2 + 0x12D);
    }

    return 0;
}

void LabPCList_InitCornerIcon(unk_func_88001300_000* arg0, s32 arg1, s32 arg2) {
    ((func885007CC)Memmap_GetFragmentVaddr(WidgetTree_InitWidget))(arg0, sizeof(unk_func_88001300_000));
    arg0->unk_18 = LabPCList_DrawCornerIcon;
    arg0->unk_10.posX = arg1;
    arg0->unk_10.posY = arg2;
}

s32 LabPCList_DrawCornerIcon(unk_func_88001300_000* arg0, s32 arg1, s32 arg2) {
    gDPPipeSync(gDisplayListHead++);

    gDPSetCycleType(gDisplayListHead++, G_CYC_COPY);
    gDPSetRenderMode(gDisplayListHead++, G_RM_NOOP, G_RM_NOOP2);
    gDPSetAlphaCompare(gDisplayListHead++, G_AC_THRESHOLD);
    gDPSetTexturePersp(gDisplayListHead++, G_TP_NONE);

    gDPLoadTextureBlock(gDisplayListHead++, gFontBitmapData, G_IM_FMT_RGBA, G_IM_SIZ_16b, 40, 28, 0,
                        G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                        G_TX_NOLOD);
    gSPTextureRectangle(gDisplayListHead++, (arg1 + 0x100) << 2, (arg2 + 2) << 2, (arg1 + 0x127) << 2,
                        (arg2 + 0x1D) << 2, G_TX_RENDERTILE, 0, 0, 0x1000, 0x0400);

    gDPPipeSync(gDisplayListHead++);

    gDPSetAlphaCompare(gDisplayListHead++, G_AC_NONE);
    return 0;
}

void LabPCList_LoadDecks(unk_func_8830867C_02C* arg0, MemoryPool* arg1) {
    s32 i;

    LabPCList_InitDeckCategories(arg0->unk_154, arg1);

    for (i = 0; i < 3; i++) {
        if (arg0->unk_154[i].rotation != 0) {
            LabPCList_ReadDeckCategory(&arg0->unk_154[i]);
        }
    }
}

void LabPCList_SaveDirtyDecks(unk_func_8830867C_02C* arg0) {
    s32 i;

    for (i = 0; i < 3; i++) {
        if ((arg0->unk_154[i].rotation != 0) && (arg0->unk_154[i].unk_08 != 0)) {
            LabPCList_WriteDeckCategory(&arg0->unk_154[i]);
        }
    }
}

void LabPCList_InitDeckSlots(unk_func_8830867C_02C* arg0, MemoryPool* arg1) {
    UNUSED s32 pad;

    arg0->unk_0E4[0].posX = 0x20;
    arg0->unk_0E4[0].rotation = GbSave_GetActivePort();
    arg0->unk_0E4[0].unk_08 = 0;
    arg0->unk_0E4[0].unk_1C = 6;
    ByteMatrix_Allocate(&arg0->unk_0E4[0].unk_0C, 0x1C, 1, arg1);
    LabPCList_AllocateBoxSlots(&arg0->unk_0E4[0], 6, 1, arg1);

    arg0->unk_0E4[1].posX = 0x21;
    arg0->unk_0E4[1].rotation = arg0->unk_0E4[0].rotation;
    arg0->unk_0E4[1].unk_08 = 1;
    arg0->unk_0E4[1].unk_1C = 0x14;
    ByteMatrix_Allocate(&arg0->unk_0E4[1].unk_0C, 0x1C, 0xC, arg1);
    LabPCList_AllocateBoxSlots(&arg0->unk_0E4[1], 0x14, 0, arg1);

    arg0->unk_0E4[2].posX = 0x11;
    arg0->unk_0E4[2].rotation = 0;
    arg0->unk_0E4[2].unk_08 = 2;
    arg0->unk_0E4[2].unk_1C = 0x14;
    ByteMatrix_Allocate(&arg0->unk_0E4[2].unk_0C, 0x1C, 0xC, arg1);
    LabPCList_AllocateBoxSlots(&arg0->unk_0E4[2], 0x14, 0, arg1);

    TableView_Initialize(&arg0->unk_144, arg0->unk_0E4, 0x20, 3, 3);
}

void LabPCList_InitPageHeader(unk_func_88302D98* arg0, s32 arg1, s32 arg2, unk_func_8830867C_02C* arg3) {
    ((func885007CC)Memmap_GetFragmentVaddr(WidgetTree_InitWidget))(arg0, sizeof(unk_func_88302D98));
    arg0->posX.unk_18 = LabPCList_DrawPageHeader;
    arg0->posX.unk_10.posX = arg1;
    arg0->posX.unk_10.posY = arg2;
    arg0->unk_2C = arg3;
}

s32 LabPCList_DrawPageHeader(unk_func_88302D98* arg0, s32 arg1, s32 arg2) {
    static Color_RGBA8 D_88317218 = { 0xF0, 0xF0, 0xF0, 0xFF };

    UNUSED s32 pad[4];
    char spF0[0x10];
    char* spEC;
    s32 spE8;
    s32 spE4;

    Text_SetNumberToken(1, arg0->unk_2C->unk_CD0 + 1);
    Text_GetString(spF0, 0x20, gMoveListMessageTable, 2);
    Font_BeginTranslucentTextRendering();
    Text_SetEnvColor(D_88317218.r, D_88317218.g, D_88317218.b, D_88317218.a);
    Font_SetActive(8, 0);
    spEC = Text_GetString(NULL, 0, gMoveListMessageTable, 1);
    spE8 = Font_MeasureTextExtent(0, 0, spEC);
    Font_Printf(arg1 + 0x22, arg2 + 5, spEC);
    spE4 = 0x206 - Font_MeasureTextExtent(0, 0, spF0);
    Font_Printf(arg1 + spE4, arg2 + 5, spF0);
    Font_EndTexturedTextRendering();

    gDPPipeSync(gDisplayListHead++);

    gDPSetCycleType(gDisplayListHead++, G_CYC_COPY);
    gDPSetRenderMode(gDisplayListHead++, G_RM_NOOP, G_RM_NOOP2);
    gDPSetAlphaCompare(gDisplayListHead++, G_AC_THRESHOLD);
    gDPSetTexturePersp(gDisplayListHead++, G_TP_NONE);

    gDPLoadTextureBlock(gDisplayListHead++, gTitleScreenImageData_2, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 24, 0,
                        G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                        G_TX_NOLOD);
    gSPTextureRectangle(gDisplayListHead++, (arg1 + 4) << 2, (arg2 + 3) << 2, (arg1 + 0x1D) << 2, (arg2 + 0x1A) << 2,
                        G_TX_RENDERTILE, 0, 0, 0x1000, 0x0400);

    gDPLoadTextureBlock(gDisplayListHead++, gTitleScreenImageData_3, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 24, 0,
                        G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                        G_TX_NOLOD);
    gSPTextureRectangle(gDisplayListHead++, ((arg1 + spE8) + 0x26) << 2, (arg2 + 3) << 2, ((arg1 + spE8) + 0x3F) << 2,
                        (arg2 + 0x1A) << 2, G_TX_RENDERTILE, 0, 0, 0x1000, 0x0400);

    gDPLoadTextureBlock(gDisplayListHead++, D_4005570, G_IM_FMT_RGBA, G_IM_SIZ_16b, 28, 26, 0,
                        G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                        G_TX_NOLOD);
    gSPTextureRectangle(gDisplayListHead++, ((arg1 + spE4) - 0x1E) << 2, (arg2 + 2) << 2, ((arg1 + spE4) - 5) << 2,
                        (arg2 + 0x1B) << 2, G_TX_RENDERTILE, 0, 0, 0x1000, 0x0400);

    gDPLoadTextureBlock(gDisplayListHead++, D_4004A00, G_IM_FMT_RGBA, G_IM_SIZ_16b, 28, 26, 0,
                        G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                        G_TX_NOLOD);
    gSPTextureRectangle(gDisplayListHead++, (arg1 + 0x20A) << 2, (arg2 + 2) << 2, (arg1 + 0x223) << 2,
                        (arg2 + 0x1B) << 2, G_TX_RENDERTILE, 0, 0, 0x1000, 0x0400);

    gDPPipeSync(gDisplayListHead++);

    gDPSetAlphaCompare(gDisplayListHead++, G_AC_NONE);

    return 0;
}

void LabPCList_SwitchColumnPage(unk_func_8830867C_02C* arg0) {
    s32 sp1C;
    unk_func_8830867C_02C_04C* ptr = arg0->unk_04C;

    sp1C = ptr->unk_24;

    switch (arg0->unk_038->unk_2C) {
        case 0:
            ptr = arg0->unk_04C;
            ptr->unk_18->unk_08 = arg0->unk_058;

            ptr = arg0->unk_04C;
            ptr->unk_18->unk_0C = arg0->unk_05C;

            ptr = arg0->unk_04C;
            ptr->unk_18->unk_10 = arg0->unk_060;

            ptr = arg0->unk_04C;
            ptr->unk_18->unk_14 = arg0->unk_064;

            ptr = arg0->unk_04C;
            ptr->unk_18->unk_18 = arg0->unk_068;

            ptr = arg0->unk_04C;
            ptr->unk_18->unk_1C = 0;

            if (sp1C >= 7) {
                sp1C = 6;
            }
            break;

        case 1:
            ptr = arg0->unk_04C;
            ptr->unk_18->unk_08 = arg0->unk_06C;

            ptr = arg0->unk_04C;
            ptr->unk_18->unk_0C = 0;

            ptr = arg0->unk_04C;
            ptr->unk_18->unk_10 = 0;

            ptr = arg0->unk_04C;
            ptr->unk_18->unk_14 = 0;

            ptr = arg0->unk_04C;
            ptr->unk_18->unk_18 = 0;

            ptr = arg0->unk_04C;
            ptr->unk_18->unk_1C = 0;

            if (sp1C >= 3) {
                sp1C = 2;
            }
            break;

        case 2:
            ptr = arg0->unk_04C;
            ptr->unk_18->unk_08 = arg0->unk_070;

            ptr = arg0->unk_04C;
            ptr->unk_18->unk_0C = arg0->unk_074;

            ptr = arg0->unk_04C;
            ptr->unk_18->unk_10 = arg0->unk_078;

            ptr = arg0->unk_04C;
            ptr->unk_18->unk_14 = arg0->unk_07C;

            ptr = arg0->unk_04C;
            ptr->unk_18->unk_18 = arg0->unk_080;

            ptr = arg0->unk_04C;
            ptr->unk_18->unk_1C = arg0->unk_084;
            break;
    }

    ((func8850CB48)Memmap_GetFragmentVaddr(WidgetTree_SetGridMenuSelection))(arg0->unk_04C, sp1C);
}

void LabPCList_BuildListScreen(unk_func_8830867C_02C* arg0, s32 arg1, s32 arg2, unk_func_88001300_000* arg3,
                   unk_func_8830867C_030* arg4, unk_func_8830867C_034* arg5, unk_func_8830867C_038* arg6,
                   unk_func_8830867C_03C* arg7, unk_func_8830867C_040* arg8, unk_func_8830867C_044* arg9,
                   unk_func_8830867C_048* argA, unk_func_8830867C_04C* argB, unk_func_889000C4* argC,
                   FragmentEntry argD, unk_func_8830867C_054* argE, MemoryPool* argF, TextObject* arg10) {
    static s32 D_8831721C[] = {
        0x0000005C,
        0x00000034,
        0x0000004C,
    };
    static s32 D_88317228[] = { 0x38, 0x48, 0x48 };
    static s32 D_88317234[] = { 0x69, 0x69, 0x69, 0x69 };
    static s32 D_88317244[] = { 0x46, 0x46, 0x46, 0x46, 0x46, 0x46 };
    static s32 D_8831725C[] = {
        0x00000000,
        0x00000006,
        0x0000000A,
        0x00000010,
    };
    static Color_RGBA8 D_8831726C = { 0x64, 0x96, 0xB4, 0xFF };
    static Color_RGBA8 D_88317270 = { 0x3C, 0x64, 0x78, 0xFF };
    static Color_RGBA8 D_88317274 = { 0xFF, 0xFF, 0x00, 0xFF };

    UNUSED s32 pad[2];
    GridMenu* tmp;
    unk_func_88302D98* sp70;
    unk_func_88001300_000* sp6C;
    unk_func_88001300_000* sp68;
    unk_func_88001300_000* sp64;
    WidgetAnimatedFrame* sp60;
    unk_func_8850BD40* sp5C;
    unk_func_88507D4C* sp58;
    unk_func_88507D4C* sp54;
    WidgetVisibilityGate* sp50;

    LabPCList_InitDeckSlots(arg0, argF);
    PointerList_Allocate(&arg0->unk_03C, 0x1E6, argF);
    PointerList_Allocate(&arg0->unk_0CC, 0x1E6, argF);
    LabPCList_LoadAllBoxes(&arg0->unk_144);

    arg0->unk_0DC = D_8831721C;

    LabPCList_FlattenEntries(&arg0->unk_03C, &arg0->unk_144);
    LabPCList_LoadDecks(arg0, argF);

    PointerList_Allocate(&arg0->unk_C48, 0xAA, argF);
    LabPCList_BuildTmHmList(&arg0->unk_C48, arg0->unk_1A8, arg0->unk_154, 3, 0xAA);

    arg0->unk_08C = arg4;
    arg0->unk_094 = arg5;
    arg0->unk_098 = arg6;
    arg0->unk_09C = arg7;
    arg0->unk_0A0 = arg8;
    arg0->unk_0A4 = arg9;
    arg0->unk_0A8 = argA;
    arg0->unk_0AC = argB;
    arg0->unk_0B0 = argC;
    arg0->unk_CC4 = 0;
    arg0->unk_CC8 = 0;
    arg0->unk_0D8 = 0;
    arg0->unk_CD0 = 0;
    arg0->unk_CD4 = D_8831725C;
    arg0->unk_0E0 = 0;
    arg0->unk_CD8 = argD;
    arg0->unk_CDC = argE;

    ((func885007CC)Memmap_GetFragmentVaddr(WidgetTree_InitWidget))(arg0, sizeof(unk_func_8830867C_02C));

    arg0->unk_000.unk_20 = LabPCList_RowMenuHandleInput;
    arg0->unk_000.unk_24 = LabPCList_SetRowMenuState;
    arg0->unk_000.unk_10.posX = arg1;
    arg0->unk_000.unk_10.posY = arg2;

    arg0->unk_048 = mem_pool_alloc(argF, sizeof(ChildSelectionProxy));
    LabPCList_InitColumnSelectionProxy(arg0->unk_048, arg0);

    arg0->unk_04C = mem_pool_alloc(argF, sizeof(GridMenu));
    ((func8850C284)Memmap_GetFragmentVaddr(WidgetTree_InitGridMenu))(arg0->unk_04C, 1, 8, argF);
    arg0->unk_04C->unk_28 |= 0x200;
    arg0->unk_04C->unk_38 = -4;
    arg0->unk_04C->unk_3A = -4;
    arg0->unk_04C->unk_3C = 8;
    arg0->unk_04C->unk_3E = 8;

    arg0->unk_02C = mem_pool_alloc(argF, sizeof(unk_func_88001300_038));
    ((func88502274)Memmap_GetFragmentVaddr(WidgetTree_InitAnimatedPanel))(arg0->unk_02C, 0, 0, 0x228, 0x172);
    arg0->unk_02C->posX.unk_28 |= 0x200;
    arg0->unk_02C->posX.unk_28 |= 0x400;
    ((func8850068C)Memmap_GetFragmentVaddr(WidgetTree_AppendChild))(arg0, arg0->unk_02C);

    arg0->unk_030 = mem_pool_alloc(argF, sizeof(DashedBorderFrame));
    ((func8850B254)Memmap_GetFragmentVaddr(WidgetTree_InitDashedBorderFrame))(arg0->unk_030, 0, 0, 0x228, 0x20, D_8831726C, D_88317270);
    ((func8850068C)Memmap_GetFragmentVaddr(WidgetTree_AppendChild))(arg0->unk_02C, arg0->unk_030);

    sp70 = mem_pool_alloc(argF, sizeof(unk_func_88302D98));
    LabPCList_InitPageHeader(sp70, 0, 1, arg0);
    ((func8850068C)Memmap_GetFragmentVaddr(WidgetTree_AppendChild))(arg0->unk_030, sp70);

    arg0->unk_088 = mem_pool_alloc(argF, sizeof(unk_func_88001300_000));
    LabPCList_InitCornerIcon(arg0->unk_088, 0, 0);
    ((func8850068C)Memmap_GetFragmentVaddr(WidgetTree_AppendChild))(arg0->unk_030, arg0->unk_088);

    arg0->unk_050 = mem_pool_alloc(argF, sizeof(unk_func_8830867C_02C_050));
    LabPCList_InitColumnDivider(arg0->unk_050, 0, 0x34, 0x228, 0x12E, arg0);

    sp6C = mem_pool_alloc(argF, sizeof(unk_func_88001300_000));
    LabPCList_InitHeaderSelectIcon(sp6C, 0, 0);
    ((func8850068C)Memmap_GetFragmentVaddr(WidgetTree_AppendChild))(arg0->unk_050, sp6C);
    tmp = arg0->unk_04C;
    tmp->unk_18[0] = sp6C;

    arg0->unk_054 = mem_pool_alloc(argF, sizeof(unk_func_88001300_000));
    LabPCList_DrawHeaderPokemon(arg0->unk_054, 0x26, 0);
    ((func8850068C)Memmap_GetFragmentVaddr(WidgetTree_AppendChild))(arg0->unk_050, arg0->unk_054);
    tmp = arg0->unk_04C;
    tmp->unk_18[1] = arg0->unk_054;

    arg0->unk_038 = mem_pool_alloc(argF, sizeof(unk_func_88500994));
    ((func88500994)Memmap_GetFragmentVaddr(WidgetTree_InitPagedContainer))(arg0->unk_038, 0, 0);
    ((func8850068C)Memmap_GetFragmentVaddr(WidgetTree_AppendChild))(arg0->unk_050, arg0->unk_038);

    sp68 = mem_pool_alloc(argF, sizeof(unk_func_88001300_000));
    ((func885007CC)Memmap_GetFragmentVaddr(WidgetTree_InitWidget))(sp68, 0x2C);
    sp68->unk_10.posX = 0;
    sp68->unk_10.posY = 0;
    ((func88500A3C)Memmap_GetFragmentVaddr(WidgetTree_AddPage))(arg0->unk_038, sp68);

    arg0->unk_058 = mem_pool_alloc(argF, sizeof(unk_func_88001300_000));
    LabPCList_DrawHeaderNickname(arg0->unk_058, 0x84, 0);
    ((func8850068C)Memmap_GetFragmentVaddr(WidgetTree_AppendChild))(sp68, arg0->unk_058);

    arg0->unk_05C = mem_pool_alloc(argF, sizeof(unk_func_88001300_000));
    LabPCList_DrawHeaderID(arg0->unk_05C, 0xE0, 0);
    ((func8850068C)Memmap_GetFragmentVaddr(WidgetTree_AppendChild))(sp68, arg0->unk_05C);

    arg0->unk_060 = mem_pool_alloc(argF, sizeof(unk_func_88001300_000));
    LabPCList_DrawHeaderOT(arg0->unk_060, 0x114, 0);
    ((func8850068C)Memmap_GetFragmentVaddr(WidgetTree_AppendChild))(sp68, arg0->unk_060);

    arg0->unk_064 = mem_pool_alloc(argF, sizeof(unk_func_88001300_000));
    LabPCList_DrawHeaderArea(arg0->unk_064, 0x160, 0);
    ((func8850068C)Memmap_GetFragmentVaddr(WidgetTree_AppendChild))(sp68, arg0->unk_064);

    arg0->unk_068 = mem_pool_alloc(argF, sizeof(unk_func_88001300_000));
    LabPCList_DrawHeaderTypes(arg0->unk_068, 0x198, 0);
    ((func8850068C)Memmap_GetFragmentVaddr(WidgetTree_AppendChild))(sp68, arg0->unk_068);

    arg0->unk_06C = mem_pool_alloc(argF, sizeof(unk_func_88001300_000));
    LabPCList_DrawHeaderMoves(arg0->unk_06C, 0x84, 0);
    ((func88500A3C)Memmap_GetFragmentVaddr(WidgetTree_AddPage))(arg0->unk_038, arg0->unk_06C);

    sp64 = mem_pool_alloc(argF, sizeof(unk_func_88001300_000));
    ((func885007CC)Memmap_GetFragmentVaddr(WidgetTree_InitWidget))(sp64, 0x2C);
    sp64->unk_10.posX = 0;
    sp64->unk_10.posY = 0;
    ((func88500A3C)Memmap_GetFragmentVaddr(WidgetTree_AddPage))(arg0->unk_038, sp64);

    arg0->unk_070 = mem_pool_alloc(argF, sizeof(unk_func_88001300_000));
    LabPCList_DrawHeaderLevel(arg0->unk_070, 0x84, 0);
    ((func8850068C)Memmap_GetFragmentVaddr(WidgetTree_AppendChild))(sp64, arg0->unk_070);

    arg0->unk_074 = mem_pool_alloc(argF, sizeof(unk_func_88001300_000));
    LabPCList_DrawHeaderHp(arg0->unk_074, 0xCA, 0);
    ((func8850068C)Memmap_GetFragmentVaddr(WidgetTree_AppendChild))(sp64, arg0->unk_074);

    arg0->unk_078 = mem_pool_alloc(argF, sizeof(unk_func_88001300_000));
    LabPCList_DrawHeaderAttack(arg0->unk_078, 0x110, 0);
    ((func8850068C)Memmap_GetFragmentVaddr(WidgetTree_AppendChild))(sp64, arg0->unk_078);

    arg0->unk_07C = mem_pool_alloc(argF, sizeof(unk_func_88001300_000));
    LabPCList_DrawHeaderDefense(arg0->unk_07C, 0x156, 0);
    ((func8850068C)Memmap_GetFragmentVaddr(WidgetTree_AppendChild))(sp64, arg0->unk_07C);

    arg0->unk_080 = mem_pool_alloc(argF, sizeof(unk_func_88001300_000));
    LabPCList_DrawHeaderSpeed(arg0->unk_080, 0x19C, 0);
    ((func8850068C)Memmap_GetFragmentVaddr(WidgetTree_AppendChild))(sp64, arg0->unk_080);

    arg0->unk_084 = mem_pool_alloc(argF, sizeof(unk_func_88001300_000));
    LabPCList_DrawHeaderSpecial(arg0->unk_084, 0x1E2, 0);
    ((func8850068C)Memmap_GetFragmentVaddr(WidgetTree_AppendChild))(sp64, arg0->unk_084);

    sp60 = mem_pool_alloc(argF, sizeof(WidgetAnimatedFrame));
    ((func88504570)Memmap_GetFragmentVaddr(WidgetTree_InitAnimatedFrameVariantC))(sp60, 0, 0, 0x10, 0x10, D_88317274);
    ((func8850068C)Memmap_GetFragmentVaddr(WidgetTree_AppendChild))(arg0->unk_050, sp60);
    arg0->unk_04C->unk_1C = sp60;
    ((func8850CB48)Memmap_GetFragmentVaddr(WidgetTree_SetGridMenuSelection))(arg0->unk_04C, 1);
    LabPCList_SwitchColumnPage(arg0);

    arg0->unk_034 = mem_pool_alloc(argF, sizeof(unk_func_8830867C_02C_034));
    ((func88506DCC)Memmap_GetFragmentVaddr(WidgetTree_InitScrollableGrid))(arg0->unk_034, 0, 0x4A, func_88304850, 0x228, 0x14, 0xE,
                                                           argF);
    ((func88506F1C)Memmap_GetFragmentVaddr(WidgetTree_BindScrollableGridPage))(arg0->unk_034, &arg0->unk_03C, argF);
    arg0->unk_034->unk_70 = arg0;
    arg0->unk_034->posX.unk_50 = 0x22;
    arg0->unk_034->posX.unk_52 = -4;
    arg0->unk_034->posX.unk_44->posX.unk_14.posX = 0x64;
    arg0->unk_034->posX.unk_44->posX.unk_14.posY = 0x1C;

    sp5C = mem_pool_alloc(argF, sizeof(unk_func_8850BD40));
    ((func8850BD40)Memmap_GetFragmentVaddr(WidgetTree_InitScrollableGridInputProxy))(sp5C, arg0->unk_034);
    ((func8850CC74)Memmap_GetFragmentVaddr(WidgetTree_AppendChildSelectionProxyItem))(arg0->unk_048, sp5C);
    ((func8850CC74)Memmap_GetFragmentVaddr(WidgetTree_AppendChildSelectionProxyItem))(arg0->unk_048, arg0->unk_04C);

    sp54 = mem_pool_alloc(argF, sizeof(unk_func_88507D4C));
    ((func88507D4C)Memmap_GetFragmentVaddr(WidgetTree_InitScrollableGridScrollbar))(sp54, 0, 0x24, 0x228, 0, arg0->unk_034);
    ((func8850068C)Memmap_GetFragmentVaddr(WidgetTree_AppendChild))(arg0->unk_02C, sp54);

    sp58 = mem_pool_alloc(argF, sizeof(unk_func_88507D4C));
    ((func88507D4C)Memmap_GetFragmentVaddr(WidgetTree_InitScrollableGridScrollbar))(sp58, 0, arg0->unk_02C->posX.unk_14.posY - 0x10, 0x228,
                                                           1, arg0->unk_034);
    ((func8850068C)Memmap_GetFragmentVaddr(WidgetTree_AppendChild))(arg0->unk_02C, sp58);
    ((func8850068C)Memmap_GetFragmentVaddr(WidgetTree_AppendChild))(arg0->unk_02C, arg0->unk_050);
    ((func8850068C)Memmap_GetFragmentVaddr(WidgetTree_AppendChild))(arg0->unk_02C, arg0->unk_034);

    sp50 = mem_pool_alloc(argF, sizeof(WidgetVisibilityGate));
    ((func88503298)Memmap_GetFragmentVaddr(WidgetTree_InitVisibilityGateBridge))(sp50, arg0->unk_02C, arg3);
    ((func8850068C)Memmap_GetFragmentVaddr(WidgetTree_AppendChild))(arg0, sp50);

    arg0->unk_0B4 = mem_pool_alloc(argF, sizeof(YesNoDialog));
    BattleInfoWidget_BuildSaveConfirmDialog(arg0->unk_0B4, 0x65, 0x228, argF);
    ((func8850068C)Memmap_GetFragmentVaddr(WidgetTree_AppendChild))(arg0, arg0->unk_0B4);

    BattleInfoWidget_BindMoveDestinationData(arg0->unk_0A8, &arg0->unk_144);

    arg0->unk_08C->unk_4C = 0x228;
    arg0->unk_08C->unk_50 = 0x13E;

    arg0->unk_090 = mem_pool_alloc(argF, sizeof(WidgetTree_InitMessagePanel));
    ((func88509F48)Memmap_GetFragmentVaddr(TextObjectGraphics_Init))(arg0->unk_090, 0, 0, 0x228, 0x1A0, argF, arg10);
    ((func8850068C)Memmap_GetFragmentVaddr(WidgetTree_AppendChild))(arg0, arg0->unk_090);

    arg0->unk_CCC = mem_pool_alloc(argF, sizeof(unk_func_8850878C));
    ((func8850878C)Memmap_GetFragmentVaddr(WidgetTree_InitTextLabel))(arg0->unk_CCC, 0, 0,
                                                           mem_pool_alloc(argF, sizeof(char) * 0x140), 0x10);
    arg0->unk_CCC->unk_3C = 0x20;

    arg0->unk_0B8 = mem_pool_alloc(argF, sizeof(ChildWidgetGroup));
    ((func8850CD44)Memmap_GetFragmentVaddr(WidgetTree_InitChildWidgetGroup))(arg0->unk_0B8, 4, argF);

    arg0->unk_0BC = mem_pool_alloc(argF, sizeof(unk_func_882173EC));
    LabPCList_InitTextFadeWidget(arg0->unk_0BC, 0, 0, D_88317234[0], 0x14);
    ((func8850068C)Memmap_GetFragmentVaddr(WidgetTree_AppendChild))(arg0->unk_034, arg0->unk_0BC);
    arg0->unk_0B8->unk_1C[0] = arg0->unk_0BC;

    arg0->unk_0C0 = mem_pool_alloc(argF, sizeof(PpChangeBanner));
    LabPCList_InitPpUpAnimWidget(arg0->unk_0C0, 0, 0, D_88317234[0], 0x14);
    ((func8850068C)Memmap_GetFragmentVaddr(WidgetTree_AppendChild))(arg0->unk_034, arg0->unk_0C0);
    arg0->unk_0B8->unk_1C[1] = &arg0->unk_0C0->posX;

    arg0->unk_0C4 = mem_pool_alloc(argF, sizeof(unk_func_882173EC));
    LabPCList_InitVitaminAnimWidget(arg0->unk_0C4, 0, 0, D_88317244[0], 0x14);

    ((func8850068C)Memmap_GetFragmentVaddr(WidgetTree_AppendChild))(arg0->unk_034, arg0->unk_0C4);
    arg0->unk_0B8->unk_1C[2] = arg0->unk_0C4;

    arg0->unk_0C8 = mem_pool_alloc(argF, sizeof(unk_func_882173EC));
    LabPCList_InitLocationCrossfadeWidget(arg0->unk_0C8, 0, 0, D_88317228[0], 0x14);
    ((func8850068C)Memmap_GetFragmentVaddr(WidgetTree_AppendChild))(arg0->unk_034, arg0->unk_0C8);
    arg0->unk_0B8->unk_1C[3] = arg0->unk_0C8;
    arg0->unk_CB8 = 0;

    LabPCList_ResetFilterState(arg0);
    LabPCList_DiscardFilterBackup(arg0);
    LabPCList_ApplyFiltersAndSort(arg0);
}

void LabPCList_DrawTypeName(s32 arg0, s32 arg1, s32 arg2, u8* arg3, s32 arg4) {
    Color_RGBA8 sp2C;
    s32 sp28;
    UNUSED s32 pad;
    char* sp20;

    if ((*arg3 <= 0) || (*arg3 >= 0x98)) {
        if (arg4 != 1) {
            sp2C = ((func884000C4)Memmap_GetFragmentVaddr(LabPC_GetTypeColor))(0)->rotation;
            sp20 = "????";
        } else {
            return;
        }
    } else {
        sp28 = Species_GetMoveSlot(arg3, arg4);
        if (sp28 != -1) {
            sp2C = ((func884000C4)Memmap_GetFragmentVaddr(LabPC_GetTypeColor))(sp28)->rotation;
            sp20 = Text_GetString(NULL, 0, gMessageBank_MoveNames, PokemonType_ToDisplayIndex(sp28));
        } else {
            return;
        }
    }

    Font_BeginTranslucentTextRendering();
    Font_SetActive(4, 0);
    Text_SetEnvColor(sp2C.r, sp2C.g, sp2C.b, sp2C.a);
    Font_Printf(((arg2 - Font_MeasureTextExtent(0, 0, sp20)) / 2) + arg0, arg1, sp20);
    Font_EndTexturedTextRendering();
}

void LabPCList_DrawMoveNameCell(s32 arg0, s32 arg1, s32 arg2, u8* arg3, s32 arg4) {
    static Color_RGBA8 D_88317278 = { 0xF0, 0xF0, 0xF0, 0xFF };

    char* sp2C;
    Color_RGBA8 sp28;
    ret_func_8002ED08* sp24;
    u8* sp18 = &arg3[arg4];

    if (arg4 < BattleMon_CountMoves(arg3)) {
        sp24 = Move_GetDisplayInfo(sp18[9]);
        if (sp24 == NULL) {
            sp28 = D_88317278;
            sp2C = " ????? ";
        } else {
            sp28 = ((func884000C4)Memmap_GetFragmentVaddr(LabPC_GetTypeColor))(sp24->posX[1])->rotation;
            sp2C = Text_GetString(NULL, 0, gMoveNamesTable, sp18[9] - 1);
        }
        Font_BeginTranslucentTextRendering();
        Font_SetActive(4, 0);
        Text_SetEnvColor(sp28.r, sp28.g, sp28.b, sp28.a);
        Font_Printf(((arg2 - Font_MeasureTextExtent(0, 0, sp2C)) / 2) + arg0, arg1, sp2C);
        Font_EndTexturedTextRendering();
    }
}

Color_RGBA8 gPartyLabelColor = { 0xF0, 0x96, 0x96, 0xFF };
Color_RGBA8 gGbLabelColor = { 0xF0, 0xD2, 0x8C, 0xFF };
Color_RGBA8 gN64LabelColor = { 0x96, 0xDC, 0xB4, 0xFF };

void LabPCList_DrawAreaCell(s32 arg0, s32 arg1, s32 arg2, unk_func_88304850_arg2* arg3) {
    LabPCList_DrawLocationCaption(arg0, arg1, arg2, 0x14, *(s32*)arg3->posX[0], arg3->posX[1], 0xFF);
}

void LabPCList_DrawPlainText(s32 arg0, s32 arg1, s8* arg2, s32 arg3) {
    static Color_RGBA8 D_88317288 = { 0xF0, 0xF0, 0xF0, 0xFF };

    Font_BeginTranslucentTextRendering();
    Text_SetEnvColor(D_88317288.r, D_88317288.g, D_88317288.b, D_88317288.a);
    Font_SetActive(4, 0);
    Font_Printf(arg0, arg1, arg2, arg3);
    Font_EndTexturedTextRendering();
}

void LabPCList_DrawFormattedNumber(s32 arg0, s32 arg1, char* arg2, s32 arg3) {
    static Color_RGBA8 D_8831728C = { 0xF0, 0xF0, 0xF0, 0xFF };
    char sp1C[12];

    Font_BeginTranslucentTextRendering();
    Text_SetEnvColor(D_8831728C.r, D_8831728C.g, D_8831728C.b, D_8831728C.a);
    Font_SetActive(4, 0);

    sprintf(&sp1C, arg2, arg3);

    Font_Printf(arg0 - Font_MeasureTextExtent(0, 0, sp1C), arg1, sp1C);
    Font_EndTexturedTextRendering();
}

void LabPCList_DrawStatNumber(s32 arg0, s32 arg1, char* arg2, s32 arg3, u8* arg4) {
    static Color_RGBA8 D_88317290 = { 0xF0, 0xF0, 0xF0, 0xFF };
    static char D_88317294[] = "?";

    if ((*arg4 <= 0) || (*arg4 >= 0x98)) {
        Font_BeginTranslucentTextRendering();
        Text_SetEnvColor(D_88317290.r, D_88317290.g, D_88317290.b, D_88317290.a);
        Font_SetActive(4, 0);
        Font_Printf(arg0 - Font_MeasureTextExtent(0, 0, D_88317294), arg1, D_88317294);
        Font_EndTexturedTextRendering();
    } else {
        LabPCList_DrawFormattedNumber(arg0, arg1, arg2, arg3);
    }
}

typedef struct unk_D_88317298 {
    /* 0x00 */ s32 posX;
    /* 0x04 */ s32 rotation;
} unk_D_88317298; // size = 0x8

s32 LabPCList_CheckStatFilterRange(unk_func_8830867C_02C* arg0, unk_func_88304850_arg2* arg1) {
    static unk_D_88317298 D_88317298[] = {
        { 0x19, 0x1E }, { 0xF, 0x14 }, { 0x32, 0x37 }, { 0x1, 0x1E }, { 0x1, 0x32 },
    };

    unk_D_88317298* ptr;
    s32 sp18 = 0;

    if (LabPCList_HasFilterFlag(arg0, 0x20) != 0) {
        ptr = &D_88317298[arg0->unk_C54.unk_2C];
        if (arg1->unk_2C < ptr->posX) {
            sp18 = 1;
        } else if (ptr->rotation < arg1->unk_2C) {
            sp18 = 2;
        }
    }
    return sp18;
}

// Score 5776 -> 3777 (round 7). Stack layout now matches. Confirmed shapes:
// - sp50/sp58 were not variables: 0x50 (arg0 + 0x84) and 0x58 (arg1 + 4) are compiler CSE temps,
//   pad[2] keeps the frame at 0xC0.
// - D_883172CC[arg3 & 1] must be hoisted into temp_v1 before the first loop so that (arg3 & 1) << 3
//   is CSE'd (target keeps it in s0, used for both D_883171D0 and D_883172CC rows).
// - var_s4 is assigned inside the Font_Printf argument list (target computes arg1 + 2 after the
//   nested Text_GetString call).
// - cases 2 and 10-15 compute the x offset into a variable first (t0 in target, `x + var` operand
//   order); reusing `color` for it works, a separate variable gives the same code.
// Remaining diffs are global register allocation in the first half: target has
// gDisplayListHead address in t0, color webs in a3 / a0, s1 = var_s1, s2 = arg2, s3 = x, arg0 + 0x84
// spilled to 0x50 (ours keeps it in s0 and spills temp_s7 to 0x48), li a3,3 / lui ra,0xF600 issued
// in block 2. Target BattleAnimDataEntry reads arg0 into s6 for (arg0 + 0x25, temp_s7) but reloads arg0 for the
// FillRectangle w1 words. Dead ends: x/var_s6/temp_s7 = arg0 copies (copy-propagated, identical),
// ternary for var_s1, s16 var_s1, (arg3 & 1) * 2 indexing of a 1D D_883171D0, 2D cast lvalue,
// temp_s7 as an inline expression (worse), separate temp var for the case offsets (identical).
// Moving `temp_s7 = var_s1 + arg0;` after the var_s6 load scores 3453 but adds stray spills.
// Good permuter candidate from this state.
// Round 8 second pass (agent-11): a local copy `arg2 = a2` (as in the matched sibling BattleInfoWidget_DrawItemGridCell) puts
// arg2 in s2 like the target: 3777 -> 3567 (pad[2] -> pad[1] keeps the frame at 0xC0).
// `var_s6 = arg0;` at the top (s6 holds arg0 early in the target; the later reassignment of var_s6 stops
// uopt from folding the copy) used for rect1 lrx and temp_s7: 3567 -> 3364, temp_s7 no longer spilled.
// Agent-11 findings from this state: uopt treats var_s6 and arg0 as one value (any mix of the two in rect1/
// rect2 gives identical code). The colour temps are ugen locals; they land in t0 because uopt never gives
// t0 to a global here (gDisplayListHead gets a0 after t1-t5/ra), while the target gives gDLH t0 and the
// colours fall to a3/a0. Not changed by: separate/block-scoped colour vars (as in LabPCList_HeaderTypes_Draw), u16/s16/
// u32 colours, inline GPACK expressions (colours go to s0/s1), computing colour1 earlier, separate case
// variable, removing the `3` constant, cutting either rect, the cycle-type cmds or the loop. x0 =
// arg0 + 0x84 in memory (target 0x50) happens with `for (x = arg0 + 0x84; ...)` on loop 2 as well, but then
// arg0 itself gets s0 (3513). No effect: while-loops, early return for arg2, redundant x defs, var_s1 +=
// var_s6 as the limit (5351), var_s4 = arg1 + 2 as its own statement (3705+).
// The whole switch region differs only by a one-step t-register rotation: the target reloads x0 from 0x50
// for the loop-2 guard (`lw t7,0x50(sp)`), consuming one ugen temp that ours does not (x0 lives in s0).
// Farm leads r1/r3 fix the rotation with noise in case 1 (u64 casts / hoisting arg2->unk_16 into a local):
// 2839 / 2967 in tree. Getting x0 spilled like the target should fix the rotation for free. Also no change:
// unk_16/unk_2E..36 as u16 fields without the (u16) casts.
// Round 8 (agent-6) dead ends (all 3777 or worse): a separate (s32/u32/u8*) copy of arg0 for rect1's lrx and
// temp_s7 (copy-propagated); separate variables for each of the three colour webs (identical: uopt splits
// webs anyway); temp_s7 placed before PipeSync / SetCycleType / temp_v1 / the first FillRectangle (3959+);
// commuting any arg0 + K / arg1 + K / var_s1 + arg0; var_s6 load vs temp_v1 order; x = arg0 + 0x84 before
// var_s6 load, after Gfx_DrawNumberDigits, after Font_EndTexturedTextRendering or in the second for-init; var_s1 if/else after
// PipeSync (5453); constant locals in place of pad (h = 0x14 / 0x13 on the heights: 5744; w = 0x26: 4857;
// w = 0x5C for rect2 lrx/spA8: 3772; w = 0x84: 4791).
// Target shape notes: s6 holds arg0 only for rect1's lrx and temp_s7 (addu s7 is scheduled inside rect1's
// w1); rect1's w1 reloads arg0/arg1 (t2/t1) and rect2 reuses those; arg0 + 0x84 is a memory temp at 0x50
// (x = s3 is recomputed from it), temp_s7 stays in s7 the whole function.
// Round 8 fourth pass (agent-16): 3364 -> 2834 with `if (temp_s7) {}` right BEFORE `temp_s7 = ...` (an
// uninitialised read: temp_s7's live range then reaches back to the function entry). Effect: rect2 gets its
// own arg0 load (like the target's t2) and the constant 3 is no longer held in a3 from block 3. Fake, but
// it says temp_s7's range (or something live across the top) is longer in the target. Same `if` at other
// statement positions (3364-4940), with other variables (var_s1/var_s6/x/arg0/color: up to 4875), and
// real early defs of temp_s7 (`temp_s7 = arg0; ... temp_s7 += var_s1;`, `s32 temp_s7 = 0`: copy-propagated,
// 3364) do not reproduce it. Empty-if block boundaries before `var_s6 = temp_s5->unk_CD4[...]` (any
// variable): 3364 -> 3054 alone, no gain on top of 2834.
// Model (agent-16): the target splits arg0's loads into three groups {rect1 lrx, temp_s7} = s6,
// {rect1 ulx, rect2 lrx/ulx} = t2, {x0 = arg0 + 0x84} = v0 (spilled to 0x50); ours puts rect1 ulx with s6.
// Placing `var_s6 = arg0`, temp_s7 or the uninit if anywhere else does not reproduce it. gDLH register:
// the target gets t0 because the constant 3 already holds a3 and a0-a2 are busy; at 3364 const 3 is in a3
// but gDLH takes a0; at 2834 const 3 is not held in a register at all and gDLH takes a3.
// More dead ends at 2834: empty-if sweep (temp_s7/var_s1/x/var_s4/var_s6/arg0/color/temp_v1 at every
// top-level statement: best 2818), declaration reordering (2834-2947), `x = arg0 + 0x84` as an early
// statement (4099-8023), loop-2 for-init `x = arg0 + 0x84` (2973), loop limits as an inline
// `var_s1 + arg0` expression (4030+), `var_s6 = (&arg0)[0]` (address taken: rect1 ulx gets its own load
// like the target, but the frame shrinks to 0xb8: 5192), `arg0 = var_s6;` (emits a store, 4291), s16/u32
// var_s6 or casts on the rect1 operands. Farm d1-d3 candidates (2415 in tree) are not equivalent C
// (frame 0xc8, `color + color` in cases 11-15).
// Round 9 F1 (farm w1/1676, real 1716): hoisting `x0 = arg0 + 0x84` into a named local declared
// between `color` and `var_s4`, assigned BEFORE the `var_s6 = temp_s5->unk_CD4[...]` load and used as
// both for-inits (`x = x0`) and the second-block reassignment: 2834 -> 1716. This is the "x0 spills
// to 0x50" prediction: x0 now spills to 0x50 like the target and the switch's t-register rotation
// fixed itself. The candidate's other edit (case 10 statements on one source line) changes nothing.
// The decl POSITION matters: `s32 x0;` after temp_s7 (before spA8) or the assignment right before the
// for (after the var_s6 load) scores 3011. Remaining: gDLH still not t0 / colour webs in a3/a0 vs
// t-regs, and the arg0 load groups. Re-seed the farm from this.
void func_88304850(s32 arg0, s32 arg1, unk_func_88304850_arg2 *arg2, s32 arg3, s32 arg4, unk_func_8830867C_02C_034 *arg5)
{
  static Color_RGBA8 D_883172C0[] = {{0xF0, 0xF0, 0xF0, 0xFF}, {0xB2, 0xFF, 0xC3, 0xFF}, {0xFF, 0xB2, 0xC3, 0xFF}};
  static Color_RGBA8 D_883172CC[][2] = {{{0x50, 0x51, 0x54, 0xFF}, {0x59, 0x5B, 0x5E, 0xFF}}, {{0x43, 0x44, 0x46, 0xFF}, {0x4B, 0x4C, 0x4F, 0xFF}}};
  Color_RGBA8 spBC;
  Color_RGBA8 (*tbl)[2];
  unk_func_88304850_arg2 *mon;
  s32 var_s1;
  s32 temp_a0;
  s32 spA8;
  s32 temp_a0_2;
  s32 temp_a3;
  s32 temp_s7;
  s32 var_s6;
  s32 var_s7;
  unk_func_8830867C_02C *temp_s5;
  temp_s5 = arg5->unk_70;
  spA8 = 0x13;
  tbl = (Color_RGBA8 (*)[2]) D_883171D0;
  temp_a0 = (arg3 & 1) * 8;
  var_s7 = ((temp_s5->unk_0AC->unk_2C->unk_30 & 2) ? (temp_s5->unk_0AC->posX.unk_10.posX - temp_s5->unk_000.unk_10.posX) : (arg5->posX.posX.unk_14.posX)) + arg0;
  var_s1 = arg0 + 0x84;
  gDPPipeSync(gDisplayListHead++);
  gDPSetCycleType(gDisplayListHead++, 3 << 20);
  gDPSetRenderMode(gDisplayListHead++, (((0 << 30) | (0 << 26)) | (0 << 22)) | (0 << 18), (((0 << 28) | (0 << 24)) | (0 << 20)) | (0 << 16));
  temp_s7 = arg3 & 1;
  temp_a3 = ((((tbl[temp_s7][0].r << 8) & 0xF800) | ((tbl[temp_s7][0].g << 3) & 0x7C0)) | ((tbl[temp_s7][0].b >> 2) & 0x3E)) | 1;
  gDPPipeSync(gDisplayListHead++);
  gDPSetFillColor(gDisplayListHead++, (temp_a3 << 0x10) | temp_a3);
  gDPFillRectangle(gDisplayListHead++, arg0, arg1, arg0 + 0x25, arg1 + spA8);
  temp_a0 = ((((tbl[temp_s7][1].r << 8) & 0xF800) | ((tbl[temp_s7][1].g << 3) & 0x7C0)) | ((tbl[temp_s7][1].b >> 2) & 0x3E)) | 1;
  gDPPipeSync(gDisplayListHead++);
  gDPSetFillColor(gDisplayListHead++, (temp_a0 << 0x10) | temp_a0);
  gDPFillRectangle(gDisplayListHead++, arg0 + 0x26, arg1, arg0 + 0x81, arg1 + spA8);
  var_s6 = temp_s5->unk_CD4[temp_s5->unk_CD0]; for (var_s1 = arg0 + 0x84; var_s1 < var_s7; var_s1 += ((s32 *) temp_s5->unk_0DC)[var_s6], var_s6++)
  {
    temp_a0_2 = ((((((Color_RGBA8 *) (((u8 *) D_883172CC) + (temp_s7 * 8)))[var_s6 & 1].r << 8) & 0xF800) | ((((Color_RGBA8 *) (((u8 *) D_883172CC) + (temp_s7 * 8)))[var_s6 & 1].g << 3) & 0x7C0)) | ((((Color_RGBA8 *) (((u8 *) D_883172CC) + (temp_s7 * 8)))[var_s6 & 1].b >> 2) & 0x3E)) | 1;
    gDPPipeSync(gDisplayListHead++);
    gDPSetFillColor(gDisplayListHead++, (temp_a0_2 << 0x10) | temp_a0_2);
    gDPFillRectangle(gDisplayListHead++, var_s1, arg1, (((s32 *) temp_s5->unk_0DC)[var_s6] + var_s1) - 1, arg1 + spA8);
  }

  mon = arg2;
  if (mon == NULL)
  {
    return;
  }
    Gfx_DrawNumberDigits(arg0 + 6, arg1 + 4, arg3 + 1, 3);
    spBC = D_883172C0[LabPCList_CheckStatFilterRange(temp_s5, mon)];
    if (arg4 & 4)
    {
      spBC.a = 0x4D;
    }
    else
    {
      spBC.a = 0xFF;
    }
    Font_BeginTranslucentTextRendering();
    Text_SetEnvColor(spBC.r, spBC.g, spBC.b, spBC.a);
    Font_SetActive(4, 0);
    spA8 = (0x5C - Font_MeasureTextExtent(0, 0, "WWWWWWWWWW")) / 2;
    if ((mon->unk_08 <= 0) || (mon->unk_08 >= 0x98))
    {
      Font_Printf((arg0 + spA8) + 0x26, arg1 + 2, "?????");
    }
    else
    {
      Font_Printf((arg0 + spA8) + 0x26, arg1 + 2, Text_GetString(NULL, 0, D_8831A4D0, mon->unk_08 - 1));
    }
    Font_EndTexturedTextRendering();
    var_s6 = temp_s5->unk_CD4[temp_s5->unk_CD0];
    for (var_s1 = arg0 + 0x84; var_s1 < var_s7; var_s1 += ((s32 *) temp_s5->unk_0DC)[var_s6], var_s6++)
    {
      switch (var_s6)
      {
        case 0:
          LabPCList_DrawPlainText(var_s1 + spA8, arg1 + 2, mon->unk_38, 0);
          break;

        case 1:
          Gfx_DrawNumberDigits(var_s1 + 4, arg1 + 4, (u16) mon->unk_16, 5);
          break;

        case 2:
          temp_s7 = (((s32 *) temp_s5->unk_0DC)[var_s6] - Font_MeasureTextExtent(0, 0, "WWWWWWW")) / 2;
          LabPCList_DrawPlainText(var_s1 + temp_s7, arg1 + 2, mon->unk_43, 0);
          break;

        case 3:
          LabPCList_DrawAreaCell(var_s1, arg1, ((s32 *) temp_s5->unk_0DC)[var_s6], mon);
          break;

        case 4:

        case 5:
          LabPCList_DrawTypeName(var_s1, arg1 + 2, ((s32 *) temp_s5->unk_0DC)[var_s6], &mon->unk_08, var_s6 - 4);
          break;

        case 6:

        case 7:

        case 8:

        case 9:
          LabPCList_DrawMoveNameCell(var_s1, arg1 + 2, ((s32 *) temp_s5->unk_0DC)[var_s6], &mon->unk_08, var_s6 - 6);
          break;

        case 10:
          temp_s7 = ((s32 *) temp_s5->unk_0DC)[var_s6] - ((((s32 *) temp_s5->unk_0DC)[var_s6] - Font_MeasureTextExtent(0, 0, "000")) / 2);
          LabPCList_DrawStatNumber(var_s1 + temp_s7, arg1 + 2, "%3d", mon->unk_2C, &mon->unk_08);
          break;

        case 11:
          temp_s7 = ((s32 *) temp_s5->unk_0DC)[var_s6] - ((((s32 *) temp_s5->unk_0DC)[var_s6] - Font_MeasureTextExtent(0, 0, "000")) / 2);
          LabPCList_DrawStatNumber(var_s1 + temp_s7, arg1 + 2, "%3d", (u16) mon->unk_2E, &mon->unk_08);
          break;

        case 12:
          temp_s7 = ((s32 *) temp_s5->unk_0DC)[var_s6] - ((((s32 *) temp_s5->unk_0DC)[var_s6] - Font_MeasureTextExtent(0, 0, "000")) / 2);
          LabPCList_DrawStatNumber(var_s1 + temp_s7, arg1 + 2, "%3d", (u16) mon->unk_30, &mon->unk_08);
          break;

        case 13:
          temp_s7 = ((s32 *) temp_s5->unk_0DC)[var_s6] - ((((s32 *) temp_s5->unk_0DC)[var_s6] - Font_MeasureTextExtent(0, 0, "000")) / 2);
          LabPCList_DrawStatNumber(var_s1 + temp_s7, arg1 + 2, "%3d", (u16) mon->unk_32, &mon->unk_08);
          break;

        case 14:
          temp_s7 = ((s32 *) temp_s5->unk_0DC)[var_s6] - ((((s32 *) temp_s5->unk_0DC)[var_s6] - Font_MeasureTextExtent(0, 0, "000")) / 2);
          LabPCList_DrawStatNumber(var_s1 + temp_s7, arg1 + 2, "%3d", (u16) mon->unk_34, &mon->unk_08);
          break;

        case 15:
          temp_s7 = ((s32 *) temp_s5->unk_0DC)[var_s6] - ((((s32 *) temp_s5->unk_0DC)[var_s6] - Font_MeasureTextExtent(0, 0, "000")) / 2);
          LabPCList_DrawStatNumber(var_s1 + temp_s7, arg1 + 2, "%3d", (u16) mon->unk_36, &mon->unk_08);
          break;

      }

    }


}

void LabPCList_SaveFilterState(unk_func_8830867C_02C* arg0) {
    arg0->unk_C84 = arg0->unk_C54;

    arg0->unk_CBC = arg0->unk_034->posX.unk_38;
    arg0->unk_CC0 = arg0->unk_034->posX.unk_38 - (arg0->unk_034->unk_58 / arg0->unk_034->posX.unk_3E);
    arg0->unk_CB4 = 1;
    arg0->unk_CB8 = 1;

    arg0->unk_088->unk_28 |= 1;
}

void LabPCList_RestoreFilterState(unk_func_8830867C_02C* arg0) {
    arg0->unk_C54 = arg0->unk_C84;

    arg0->unk_CB4 = 0;
    arg0->unk_088->unk_28 &= ~1;
}

void LabPCList_DiscardFilterBackup(unk_func_8830867C_02C* arg0) {
    arg0->unk_C84 = arg0->unk_C54;
    arg0->unk_CB4 = 0;
    arg0->unk_088->unk_28 &= ~1;
}

void LabPCList_ResetFilterState(unk_func_8830867C_02C* arg0) {
    arg0->unk_C54.rotation = NULL;
    arg0->unk_C54.posX = 0;
    // clang-format off
    arg0->unk_C54.unk_08 = 1; arg0->unk_C54.unk_09 = 0x64;
    // clang-format on
    arg0->unk_C54.unk_0C = 0;
    arg0->unk_C54.unk_1C.posX = 0;
    arg0->unk_C54.unk_24.rotation = 0;
}

s32 LabPCList_HasFilterFlag(unk_func_8830867C_02C* arg0, s32 arg1) {
    return (arg0->unk_C54.rotation & arg1) != 0;
}

void LabPCList_SetFilterFlag(unk_func_8830867C_02C* arg0, s32 arg1) {
    arg0->unk_C54.rotation |= arg1;
}

void LabPCList_ClearFilterFlag(unk_func_8830867C_02C* arg0, s32 arg1) {
    arg0->unk_C54.rotation &= ~arg1;
}

s32 LabPCList_ToggleFilterFlag(unk_func_8830867C_02C* arg0, s32 arg1) {
    arg0->unk_C54.rotation ^= arg1;
    return arg0->unk_C54.rotation & arg1;
}

void LabPCList_SetSortMode(unk_func_8830867C_02C* arg0, s32 arg1) {
    arg0->unk_C54.posX = arg1;
}

void LabPCList_ApplyFiltersAndSort(unk_func_8830867C_02C* arg0) {
    ((func88506EE4)Memmap_GetFragmentVaddr(WidgetTree_BindScrollableGridData))(arg0->unk_034, &arg0->unk_03C);

    if (arg0->unk_C54.rotation != 0) {
        if (arg0->unk_C54.rotation & 1) {
            PointerList_Filter(arg0->unk_034->posX.unk_2C, &arg0->unk_0CC, LabPCList_FilterByLevelRange, &arg0->unk_C54.unk_08);
            ((func88506EE4)Memmap_GetFragmentVaddr(WidgetTree_BindScrollableGridData))(arg0->unk_034, &arg0->unk_0CC);
        }

        if (arg0->unk_C54.rotation & 2) {
            PointerList_Filter(arg0->unk_034->posX.unk_2C, &arg0->unk_0CC, LabPCList_FilterByAnyType, &arg0->unk_C54.unk_1C);
            ((func88506EE4)Memmap_GetFragmentVaddr(WidgetTree_BindScrollableGridData))(arg0->unk_034, &arg0->unk_0CC);
        }

        if (arg0->unk_C54.rotation & 4) {
            PointerList_Filter(arg0->unk_034->posX.unk_2C, &arg0->unk_0CC, LabPCList_FilterByAnyMove, &arg0->unk_C54.unk_24);
            ((func88506EE4)Memmap_GetFragmentVaddr(WidgetTree_BindScrollableGridData))(arg0->unk_034, &arg0->unk_0CC);
        }

        if (arg0->unk_C54.rotation & 8) {
            PointerList_Filter(arg0->unk_034->posX.unk_2C, &arg0->unk_0CC, LabPCList_FilterBySpeciesId, &arg0->unk_C54.unk_10);
            ((func88506EE4)Memmap_GetFragmentVaddr(WidgetTree_BindScrollableGridData))(arg0->unk_034, &arg0->unk_0CC);
        }

        if (arg0->unk_C54.rotation & 0x10) {
            PointerList_Filter(arg0->unk_034->posX.unk_2C, &arg0->unk_0CC, LabPCList_FilterByExactTypePair, &arg0->unk_C54.unk_14);
            ((func88506EE4)Memmap_GetFragmentVaddr(WidgetTree_BindScrollableGridData))(arg0->unk_034, &arg0->unk_0CC);
        }

        if (arg0->unk_C54.rotation & 0x20) {
            PointerList_Filter(arg0->unk_034->posX.unk_2C, &arg0->unk_0CC, LabPCList_FilterByCategoryBit, &arg0->unk_C54.unk_2C);
            ((func88506EE4)Memmap_GetFragmentVaddr(WidgetTree_BindScrollableGridData))(arg0->unk_034, &arg0->unk_0CC);
        }
    }

    PointerList_Sort(arg0->unk_034->posX.unk_2C, gListSortComparators[arg0->unk_C54.posX]);
}

s32 LabPCList_CheckAnyDirty(unk_func_8830867C_02C* arg0) {
    s32 var_a0 = LabPCList_CheckDirtyBoxes(&arg0->unk_144);
    s32 i;

    for (i = 0; i < 3; i++) {
        if ((arg0->unk_154[i].rotation != 0) && (arg0->unk_154[i].unk_08 != 0)) {
            if (i == 0) {
                var_a0 |= 2;
            } else if (i == 1) {
                var_a0 |= 8;
            } else {
                var_a0 |= 0x20;
            }
        }
    }

    return var_a0;
}

s32 LabPCList_FindEntryIndex(unk_func_8830867C_02C_0CC* arg0, unk_func_8830867C_02C_0CC_000* arg1) {
    unk_func_8830867C_02C_0CC_000** ptr = arg0->posX;
    s32 i;

    for (i = 0; i < arg0->unk_08; i++) {
        if (arg1 == ptr[i]) {
            return i;
        }
    }

    return -1;
}

void LabPCList_PerformMoveMon(unk_func_8830867C_02C* arg0, unk_func_8830867C_02C_0CC_000* arg1, Controller* arg2) {
    func88500A6C temp_v0_4;
    s32 sp90;
    s32 sp8C;
    s32 sp88;
    s32 sp84;
    s32 sp80;
    s32 sp7C;
    unk_func_88001300_000_010 sp78;
    unk_func_8830867C_02C_0CC_000* sp74;
    s32 sp70;
    char sp50[0x20];
    char sp30[0x20];
    unk_func_88500994* tmp;

    sp84 = 0;
    sp80 = (arg1->posX->posX->unk_08 << 0x10) | arg1->posX->rotation;
    sp88 = arg0->unk_0A8->unk_34->unk_38;

    if (sp88 != 0) {
        sp84 = arg0->unk_0A8->unk_38[arg0->unk_0A8->unk_4C->unk_1C]->unk_38;
    }

    sp90 = arg0->unk_034->posX.unk_38;
    sp8C = arg0->unk_034->posX.unk_38 - (arg0->unk_034->unk_58 / arg0->unk_034->posX.unk_3E);
    sp74 = arg0->unk_034->posX.unk_2C->posX[sp90];

    LabPCList_MoveEntryToBox(arg0, sp74, sp88, sp84);
    sp7C = (arg1->posX->posX->unk_08 << 0x10) | arg1->posX->rotation;

    temp_v0_4 = ((func88500A6C)Memmap_GetFragmentVaddr(WidgetTree_SelectPage));
    tmp = arg0->unk_038;
    arg0->unk_CD0 = 0;
    temp_v0_4(tmp, 0);

    LabPCList_SwitchColumnPage(arg0);

    sp78.posX = arg0->unk_0DC->unk_08 + (s32)arg0->unk_0DC->posX + arg0->unk_0DC->rotation + 0x84;
    sp78.posY = arg0->unk_034->unk_5C - arg0->unk_034->unk_58;

    LabPCList_LocationCrossfadeWidget_Start(arg0->unk_0C8, sp80, sp7C, sp78);
    Audio_PlaySoundEffectById(0x0120000D);

    ((func8850CF00)Memmap_GetFragmentVaddr(WidgetTree_RunChildWidgetGroup))(arg0->unk_0B8, arg2);

    Audio_PlaySoundEffectById(0x29);
    LabPCList_FlattenEntries(&arg0->unk_03C, &arg0->unk_144);
    LabPCList_ApplyFiltersAndSort(arg0);
    LabPCList_DiscardFilterBackup(arg0);

    sp70 = LabPCList_FindEntryIndex(arg0->unk_034->posX.unk_2C, sp74);
    if (sp70 == -1) {
        ((func88507C0C)Memmap_GetFragmentVaddr(WidgetTree_SetPagedGridSelectionWithOffset))(arg0->unk_034, sp90, sp8C);
        Text_SetStringToken(0x1A, arg1->unk_38);
        BattleInfoWidget_FormatLocationName(sp50, sp80 >> 0x10, sp80 & 0xFFFF);
        Text_SetStringToken(0x25, sp50);
        BattleInfoWidget_FormatLocationName(sp30, sp88, sp84);
        Text_SetStringToken(0x28, sp30);
        Text_GetString(arg0->unk_CCC->unk_40, 0x140, gMoveListMessageTable, 0x5C);
        ((func8850A10C)Memmap_GetFragmentVaddr(WidgetTree_SetMessagePanelText))(arg0->unk_090, arg0->unk_CCC, 0, 0);
        ((func8850A3CC)Memmap_GetFragmentVaddr(WidgetTree_RunMessagePanelWithSound))(arg0->unk_090, arg2);
    } else {
        ((func88507C0C)Memmap_GetFragmentVaddr(WidgetTree_SetPagedGridSelectionWithOffset))(arg0->unk_034, sp70, sp8C);
    }
}

void LabPCList_ReindexBoxSlots(unk_func_8830867C_02C_0CC_000_000* arg0) {
    unk_func_8830867C_02C_0CC_000_000_010_000* ptr = arg0->unk_10.posX;
    s32 i;

    for (i = 0; i < arg0->unk_10.unk_08; i++, ptr++) {
        ptr->posX->rotation = i;
    }
}

void LabPCList_MoveEntryToBox(unk_func_8830867C_02C* arg0, unk_func_8830867C_02C_0CC_000* arg1, s32 arg2, s32 arg3) {
    unk_func_8830867C_02C_144_000* ptr = arg0->unk_144.posX;
    unk_func_8830867C_02C_0CC_000_000* temp_s0 = &ptr[arg2].unk_0C[arg3];
    unk_func_8830867C_02C_0CC_000_000* sp24 = arg1->posX;

    PointerList_Remove(&sp24->unk_10, arg1->rotation);
    LabPCList_ReindexBoxSlots(sp24);

    arg1->posX = &temp_s0->posX;
    arg1->rotation = temp_s0->unk_10.unk_08;

    PointerList_Insert(&temp_s0->unk_10, arg1, temp_s0->unk_10.unk_08);

    sp24->unk_0C = 1;
    temp_s0->unk_0C = 1;
}

s32 LabPCList_ApplyVitaminItem(unk_func_8830867C_02C_0CC_000* arg0, unk_func_8830867C_04C_030_02C_000* arg1, u32** arg2,
                  u32** arg3) {
    unk_func_8830867C_02C_0CC_000_008* temp_s0 = &arg0->unk_08;
    u16 sp3A;
    s32 sp34;

    switch (arg1->posX[0]->posX) {
        case 35:
            sp34 = 1;

            *arg2 = temp_s0->unk_26;
            temp_s0->unk_14 += 0xA00;
            if (temp_s0->unk_14 >= 0x6401) {
                temp_s0->unk_14 = 0x6400;
            }
            temp_s0->unk_26 = CalculateStatValue(STAT_HP, temp_s0->posX, temp_s0->unk_14, temp_s0->unk_24, temp_s0->unk_1E);
            *arg3 = temp_s0->unk_26;
            break;

        case 36:
            sp34 = 2;
            *arg2 = temp_s0->unk_28;
            temp_s0->unk_16 += 0xA00;
            if (temp_s0->unk_16 >= 0x6401) {
                temp_s0->unk_16 = 0x6400;
            }
            temp_s0->unk_28 = CalculateStatValue(STAT_SPECIAL, temp_s0->posX, temp_s0->unk_16, temp_s0->unk_24, temp_s0->unk_1E);
            *arg3 = temp_s0->unk_28;
            break;

        case 37:
            sp34 = 3;
            *arg2 = temp_s0->unk_2A;
            temp_s0->unk_18 += 0xA00;
            if (temp_s0->unk_18 >= 0x6401) {
                temp_s0->unk_18 = 0x6400;
            }
            temp_s0->unk_2A = CalculateStatValue(STAT_SPEED, temp_s0->posX, temp_s0->unk_18, temp_s0->unk_24, temp_s0->unk_1E);
            *arg3 = temp_s0->unk_2A;
            break;

        case 38:
            sp34 = 4;
            *arg2 = temp_s0->unk_2C;
            temp_s0->unk_1A += 0xA00;
            if (temp_s0->unk_1A >= 0x6401) {
                temp_s0->unk_1A = 0x6400;
            }
            temp_s0->unk_2C = CalculateStatValue(STAT_DEFENSE, temp_s0->posX, temp_s0->unk_1A, temp_s0->unk_24, temp_s0->unk_1E);
            *arg3 = temp_s0->unk_2C;
            break;

        case 39:
            sp34 = 5;
            *arg2 = temp_s0->unk_2E;
            temp_s0->unk_1C += 0xA00;
            if (temp_s0->unk_1C >= 0x6401) {
                temp_s0->unk_1C = 0x6400;
            }
            temp_s0->unk_2E = CalculateStatValue(STAT_ATTACK, temp_s0->posX, temp_s0->unk_1C, temp_s0->unk_24, temp_s0->unk_1E);
            *arg3 = temp_s0->unk_2E;
            break;

        case 40:
            sp34 = 0;
            *arg2 = temp_s0->unk_24;
            sp3A = temp_s0->unk_26;
            *(s32*)&temp_s0->unk_10 = Pokemon_ExpForLevel(temp_s0->posX, (temp_s0->unk_24 + 1) & 0xFFFF);
            Pokemon_RecalcStats(&arg0->unk_08);
            temp_s0->posY = (temp_s0->posY + temp_s0->unk_26) - sp3A;
            *arg3 = temp_s0->unk_24;
            break;
    }

    LabPCList_ConsumeUsedTmItem(arg1);
    arg0->posX->unk_0C = 1;
    return sp34;
}

void LabPCList_ApplyPpUpItem(unk_func_8830867C_02C_0CC_000* arg0, unk_func_8830867C_04C_030_02C_000* arg1, s32 arg2, s32* arg3,
                   s32* arg4) {
    s32 var_v1;
    MoveBattleData* temp_v0;
    unk_func_8830867C_02C_0CC_000_008* ptr = &arg0->unk_08;

    temp_v0 = Move_GetData(ptr->unk_09[arg2]);

    var_v1 = temp_v0->unk_05 / 5;
    if (var_v1 >= 7) {
        var_v1 = 7;
    }

    *arg3 = ((ptr->unk_20[arg2] >> 6) * var_v1) + temp_v0->unk_05;
    *arg4 = *arg3 + var_v1;

    ptr->unk_20[arg2] += var_v1 + 0x40;

    LabPCList_ConsumeUsedTmItem(arg1);

    arg0->posX->unk_0C = 1;
}

void LabPCList_ClearMovesFrom(unk_func_8830867C_02C_0CC_000_008* arg0, s32 arg1) {
    s32 i;

    for (i = arg1; i < 4; i++) {
        arg0->unk_09[i] = 0;
    }
}

void LabPCList_TeachTmMove(unk_func_8830867C_02C_0CC_000* arg0, unk_func_8830867C_04C_030_02C_000* arg1, s32 arg2) {
    unk_func_8830867C_02C_0CC_000_008* ptr = &arg0->unk_08;
    s32 var_a0;

    if (arg1->posX[0]->posX >= 0xC9) {
        var_a0 = arg1->posX[0]->posX - 0xC9;
    } else {
        var_a0 = arg1->posX[0]->posX - 0x92;
    }

    ptr->unk_09[arg2] = Move_GetIdFromTableIndex(var_a0);
    ptr->unk_20[arg2] = Move_GetData(ptr->unk_09[arg2])->unk_05;

    if (arg1->posX[0]->posX >= 0xC9) {
        LabPCList_ConsumeUsedTmItem(arg1);
    }
    arg0->posX->unk_0C = 1;
}

void LabPCList_SetRowMenuState(unk_func_8830867C_02C* arg0, s32 arg1) {
    arg0->unk_000.unk_2A = arg1;
    arg0->unk_048->posX.unk_14(arg0->unk_048, arg1);
}

s32 LabPCList_RowMenuHandleInput(unk_func_8830867C_02C* arg0, Controller* arg1) {
    s32 var_v1;

    if (arg0->unk_02C->unk_30 & 2) {
        var_v1 = arg0->unk_048->posX.unk_10(arg0->unk_048, arg1);
    } else {
        var_v1 = 1;
    }
    return var_v1;
}

void LabPCList_RunPartySelectionModal(unk_func_8830867C_02C* arg0, Controller* arg1) {
    s32 var_s3 = 0;
    s32 temp_v0;

    arg0->unk_048->posX.unk_14(arg0->unk_048, 1);

    ((func88502C98)Memmap_GetFragmentVaddr(WidgetTree_OpenAnimatedPanel))(arg0->unk_02C);

    while (!(arg0->unk_02C->unk_30 & 2)) {
        Ui_SendMessageAndPollInput(NULL);
    }

    BattleInfoWidget_BindData(arg0->unk_094, &arg0->unk_144);
    if (BattleInfoWidget_RunSelectionModal(arg0->unk_094, arg1) == 1) {
        LabPCList_FlattenEntries(&arg0->unk_03C, &arg0->unk_144);
        LabPCList_ApplyFiltersAndSort(arg0);
    }

    while (var_s3 == 0) {
        Ui_SendMessageAndPollInput(NULL);
        temp_v0 = LabPCList_RowMenuHandleInput(arg0, arg1);
        if (!(temp_v0 & 1) && (temp_v0 & 2)) {
            var_s3 = 1;
        }
        ((func8850BC94)Memmap_GetFragmentVaddr(Ui_PlayInputActionSound))(temp_v0);
    }
    arg0->unk_02C->unk_2C = 0xB;
}

void func_88305F28(unk_func_8830867C_02C* arg0) {
    unk_func_8830867C_04C_030_02C_000_000* spDC;
    unk_func_8830867C_02C_0CC_000* spD8;
    s32 spD4;
    s32 spD0;
    s32 spCC;
    unk_func_88001300_000_010 spC8;
    func88500A6C temp_v0_4;
    s32 spC0;
    s32 spBC;
    unk_func_88001300_000_010 spB8;
    s32 spB4;
    s32 spB0;
    s32 spAC;
    unk_func_88001300_000_010 spA8;
    unk_func_8830867C_02C_0CC_000 sp4C;
    char* sp48;
    char* sp44;
    s32 sp40;
    UNUSED s32 pad;

    spDC = arg0->unk_0AC->unk_30->unk_2C->posX->posX[arg0->unk_0AC->unk_30->unk_38];
    spD8 = arg0->unk_034->posX.unk_2C->posX[arg0->unk_034->posX.unk_38];
    spD0 = arg0->unk_034->posX.unk_38;
    spCC = spD0 - (arg0->unk_034->unk_58 / arg0->unk_034->posX.unk_3E);

    if (spDC->unk_08 >= 0x64) {
        spC0 = BattleMon_CountMoves(&spD8->unk_08);
        if (spC0 < 4) {
            LabPCList_ClearMovesFrom(&spD8->unk_08, spC0);
            spBC = -1;
        } else {
            if (1) {}
            spC0 = arg0->unk_0AC->unk_78->unk_30->unk_38;
            spBC = spD8->unk_08.unk_09[spC0];
        }
        LabPCList_TeachTmMove(spD8, spDC, spC0);

        temp_v0_4 = ((func88500A6C)Memmap_GetFragmentVaddr(WidgetTree_SelectPage));
        arg0->unk_CD0 = 1;
        temp_v0_4(arg0->unk_038, 1);

        spC8.posX = (arg0->unk_0DC->unk_18 * spC0) + 0x84;
        spC8.posY = arg0->unk_034->unk_5C - arg0->unk_034->unk_58;

        LabPCList_TextFadeWidget_Start(arg0->unk_0BC, spBC, spD8->unk_08.unk_09[spC0], spC8);
        LabPCList_SwitchColumnPage(arg0);
        ((func8850CF00)Memmap_GetFragmentVaddr(WidgetTree_RunChildWidgetGroup))(arg0->unk_0B8, gPlayer1Controller);
        LabPCList_ApplyFiltersAndSort(arg0);
        LabPCList_DiscardFilterBackup(arg0);
        spD4 = LabPCList_FindEntryIndex(arg0->unk_034->posX.unk_2C, spD8);
        if (spD4 == -1) {
            ((func88507C0C)Memmap_GetFragmentVaddr(WidgetTree_SetPagedGridSelectionWithOffset))(arg0->unk_034, spD0, spCC);
            Text_SetStringToken(0x1A, spD8->unk_38);
            Text_SetStringToken(0x1D, Text_GetString(NULL, 0, gMoveNamesTable, spBC - 1));
            Text_SetStringToken(0x1E, Text_GetString(NULL, 0, gMoveNamesTable, spD8->unk_08.unk_09[spC0] - 1));
            Text_GetString(arg0->unk_CCC->unk_40, 0x140, gMoveListMessageTable, 0x5D);
            ((func8850A10C)Memmap_GetFragmentVaddr(WidgetTree_SetMessagePanelText))(arg0->unk_090, arg0->unk_CCC, 0, 0);
            ((func8850A3CC)Memmap_GetFragmentVaddr(WidgetTree_RunMessagePanelWithSound))(arg0->unk_090, gPlayer1Controller);
        } else {
            ((func88507C0C)Memmap_GetFragmentVaddr(WidgetTree_SetPagedGridSelectionWithOffset))(arg0->unk_034, spD4, spCC);
        }
    } else if (spDC->unk_08 >= 0x32) {
        spB4 = arg0->unk_0AC->unk_78->unk_30->unk_38;
        LabPCList_ApplyPpUpItem(spD8, spDC, spB4, &spB0, &spAC);

        temp_v0_4 = ((func88500A6C)Memmap_GetFragmentVaddr(WidgetTree_SelectPage));
        arg0->unk_CD0 = 1;
        temp_v0_4(arg0->unk_038, 1);

        spB8.posX = (arg0->unk_0DC->unk_18 * spB4) + 0x84;
        spB8.posY = arg0->unk_034->unk_5C - arg0->unk_034->unk_58;
        LabPCList_PpUpAnimWidget_Start(arg0->unk_0C0, spD8->unk_08.unk_09[spB4], spB0, spAC, spB8);
        LabPCList_SwitchColumnPage(arg0);
        ((func8850CF00)Memmap_GetFragmentVaddr(WidgetTree_RunChildWidgetGroup))(arg0->unk_0B8, gPlayer1Controller);
    } else {
        sp4C = *spD8;

        sp40 = LabPCList_ApplyVitaminItem(&sp4C, spDC, &sp48, &sp44);

        temp_v0_4 = ((func88500A6C)Memmap_GetFragmentVaddr(WidgetTree_SelectPage));
        arg0->unk_CD0 = 2;
        temp_v0_4(arg0->unk_038, 2);

        spA8.posX = (arg0->unk_0DC->unk_28 * sp40) + 0x84;
        spA8.posY = arg0->unk_034->unk_5C - arg0->unk_034->unk_58;

        LabPCList_TextCrossfadeWidget_Start(arg0->unk_0C4, sp48, sp44, spA8);
        LabPCList_SwitchColumnPage(arg0);
        ((func8850CF00)Memmap_GetFragmentVaddr(WidgetTree_RunChildWidgetGroup))(arg0->unk_0B8, gPlayer1Controller);

        *spD8 = sp4C;

        LabPCList_ApplyFiltersAndSort(arg0);
        LabPCList_DiscardFilterBackup(arg0);
        spD4 = LabPCList_FindEntryIndex(arg0->unk_034->posX.unk_2C, spD8);
        if (spD4 == -1) {
            ((func88507C0C)Memmap_GetFragmentVaddr(WidgetTree_SetPagedGridSelectionWithOffset))(arg0->unk_034, spD0, spCC);
            Text_SetStringToken(0x1A, spD8->unk_38);
            Text_SetNumberToken(2, sp48);
            Text_SetNumberToken(3, sp44);
            Text_GetString(arg0->unk_CCC->unk_40, 0x140, gMoveListMessageTable, 0x5E);
            ((func8850A10C)Memmap_GetFragmentVaddr(WidgetTree_SetMessagePanelText))(arg0->unk_090, arg0->unk_CCC, 0, 0);
            ((func8850A3CC)Memmap_GetFragmentVaddr(WidgetTree_RunMessagePanelWithSound))(arg0->unk_090, gPlayer1Controller);
        } else {
            ((func88507C0C)Memmap_GetFragmentVaddr(WidgetTree_SetPagedGridSelectionWithOffset))(arg0->unk_034, spD4, spCC);
        }
    }
    LabPCList_BuildTmHmList(&arg0->unk_C48, arg0->unk_1A8, arg0->unk_154, 3, 0xAA);
}

s32 LabPCList_OpenListMenu(unk_func_8830867C_02C* arg0, Controller* arg1) {
    char* sp28[6];
    u32 sp24;

    sp28[0] = Text_GetString(NULL, 0, gMoveListMessageTable, 0x17);
    sp28[1] = Text_GetString(NULL, 0, gMoveListMessageTable, 0x18);
    sp28[2] = Text_GetString(NULL, 0, gMoveListMessageTable, 0x19);
    sp28[3] = Text_GetString(NULL, 0, gMoveListMessageTable, 0x1A);
    sp28[4] = Text_GetString(NULL, 0, gMoveListMessageTable, 0x1B);
    sp28[5] = Text_GetString(NULL, 0, gMoveListMessageTable, 0x1C);

    BattleInfoWidget_SetLabels(arg0->unk_08C, sp28, 6);

    arg0->unk_08C->unk_30 = arg0->unk_054->unk_10;
    arg0->unk_08C->unk_34 = arg0->unk_054->unk_14;

    BattleInfoWidget_UpdateViewport(arg0->unk_08C);

    if ((arg0->unk_034->posX.unk_2C->unk_08 == 0) || (arg0->unk_C48.unk_08 == 0)) {
        arg0->unk_08C->unk_3C->unk_34[3] |= 4;
    }

    if ((arg0->unk_C54.posX == 0) && (arg0->unk_C54.rotation == 0)) {
        arg0->unk_08C->unk_3C->unk_34[5] |= 4;
    }

    arg0->unk_04C->unk_14(arg0->unk_04C, 0x100);
    sp24 = BattleInfoWidget_RunEntryModal(arg0->unk_08C, arg1, arg0->unk_CC4);
    arg0->unk_04C->unk_14(arg0->unk_04C, 1);

    arg0->unk_CC4 = arg0->unk_08C->unk_3C->unk_38;

    switch (sp24) {
        case 0:
            sp24 = 0;
            break;

        case 1:
            LabPCList_SaveFilterState(arg0);
            LabPCList_SetSortMode(arg0, 0x11);
            PointerList_Sort(arg0->unk_034->posX.unk_2C, gListSortComparators[arg0->unk_C54.posX]);
            ((func88507AE4)Memmap_GetFragmentVaddr(WidgetTree_SetScrollableGridIndex))(arg0->unk_034, 0);
            sp24 = 0;
            break;

        case 2:
            LabPCList_SaveFilterState(arg0);
            LabPCList_SetSortMode(arg0, 0x12);
            PointerList_Sort(arg0->unk_034->posX.unk_2C, gListSortComparators[arg0->unk_C54.posX]);
            ((func88507AE4)Memmap_GetFragmentVaddr(WidgetTree_SetScrollableGridIndex))(arg0->unk_034, 0);
            sp24 = 0;
            break;

        case 3:
            sp24 = 1;
            break;

        case 4:
            sp24 = 2;
            break;

        case 5:
            sp24 = 3;
            break;

        case 6:
            LabPCList_ResetFilterState(arg0);
            LabPCList_ApplyFiltersAndSort(arg0);
            LabPCList_DiscardFilterBackup(arg0);
            arg0->unk_CB8 = 0;
            sp24 = 0;
            break;
    }

    return sp24;
}

s32 LabPCList_OpenRowMenu(unk_func_8830867C_02C* arg0, Controller* arg1) {
    static char D_8831A500[0x20];

    char* sp44[5];
    u32 sp40;
    unk_func_8830867C_02C_0CC_000* sp3C;
    u32 sp38;
    s32 sp34;
    s32 sp30;
    s32 sp2C;

    sp3C = arg0->unk_034->posX.unk_2C->posX[arg0->unk_034->posX.unk_38];
    if (arg0->unk_C54.rotation & 8) {
        sp38 = 0x24;
    } else {
        sp38 = 0x23;
    }

    Text_SetStringToken(0x19, Text_GetString(NULL, 0, D_8831A4D0, sp3C->unk_08.posX - 1));
    Text_GetString(D_8831A500, 0x20, gMoveListMessageTable, sp38);

    sp44[0] = D_8831A500;
    sp38 = (arg0->unk_C54.rotation & 0x10) ? (0x26) : (0x25);
    sp44[1] = Text_GetString(NULL, 0, gMoveListMessageTable, sp38);
    sp44[2] = Text_GetString(NULL, 0, gMoveListMessageTable, 0x27);
    sp44[3] = Text_GetString(NULL, 0, gMoveListMessageTable, 0x28);
    sp44[4] = Text_GetString(NULL, 0, gMoveListMessageTable, 0x29);

    BattleInfoWidget_SetLabels(arg0->unk_08C, sp44, 5);

    arg0->unk_08C->unk_30.posX = 0x26;
    arg0->unk_08C->unk_30.posY = (arg0->unk_034->unk_5C - arg0->unk_034->unk_58) + 0x16;
    arg0->unk_08C->unk_34.posX = 0x50;
    arg0->unk_08C->unk_34.posY = 0x14;

    BattleInfoWidget_UpdateViewport(arg0->unk_08C);

    if (arg0->unk_C48.unk_08 == 0) {
        arg0->unk_08C->unk_3C->unk_34[3] |= 4;
    }

    if ((sp3C->unk_08.posX <= 0) || (sp3C->unk_08.posX >= 0x98)) {
        arg0->unk_08C->unk_3C->unk_34[0] |= 4;
        arg0->unk_08C->unk_3C->unk_34[1] |= 4;
        arg0->unk_08C->unk_3C->unk_34[3] |= 4;
    }

    arg0->unk_034->posX.posX.unk_24(&arg0->unk_034->posX.posX, 0x100);

    sp40 = BattleInfoWidget_RunEntryModal(arg0->unk_08C, arg1, arg0->unk_CC8);

    arg0->unk_034->posX.posX.unk_24(&arg0->unk_034->posX.posX, 1);
    arg0->unk_CC8 = arg0->unk_08C->unk_3C->unk_38;

    switch (sp40) {
        case 0:
            sp40 = 0;
            break;

        case 1:
            sp34 = arg0->unk_034->posX.unk_38 - (arg0->unk_034->unk_58 / arg0->unk_034->posX.unk_3E);

            LabPCList_SaveFilterState(arg0);
            if (LabPCList_ToggleFilterFlag(arg0, 8) != 0) {
                arg0->unk_C54.unk_10 = sp3C->unk_08.posX;
            }
            LabPCList_ApplyFiltersAndSort(arg0);
            ((func88507C0C)Memmap_GetFragmentVaddr(WidgetTree_SetPagedGridSelectionWithOffset))(
                arg0->unk_034, LabPCList_FindEntryIndex(arg0->unk_034->posX.unk_2C, sp3C), sp34);
            sp40 = 0;
            break;

        case 2:
            sp30 = arg0->unk_034->posX.unk_38 - (arg0->unk_034->unk_58 / arg0->unk_034->posX.unk_3E);

            LabPCList_SaveFilterState(arg0);
            if (LabPCList_ToggleFilterFlag(arg0, 0x10) != 0) {
                sp2C = sp3C->unk_08.posX - 1;

                arg0->unk_C54.unk_14.posX = 1;

                arg0->unk_C54.unk_14.rotation[0] = gSpeciesBaseStats[sp2C].unk_06;

                if (gSpeciesBaseStats[sp2C].unk_06 != gSpeciesBaseStats[sp2C].unk_07) {
                    arg0->unk_C54.unk_14.rotation[1] = gSpeciesBaseStats[sp2C].unk_07;
                    arg0->unk_C54.unk_14.posX++;
                }
            }

            LabPCList_ApplyFiltersAndSort(arg0);
            ((func88507C0C)Memmap_GetFragmentVaddr(WidgetTree_SetPagedGridSelectionWithOffset))(
                arg0->unk_034, LabPCList_FindEntryIndex(arg0->unk_034->posX.unk_2C, sp3C), sp30);
            sp40 = 0;
            break;

        case 3:
            sp40 = 1;
            break;

        case 4:
            sp40 = 2;
            break;

        case 5:
            sp40 = 3;
            break;
    }

    return sp40;
}

typedef struct unk_D_883172F4 {
    /* 0x00 */ u16* posX;
    /* 0x04 */ s32 rotation;
} unk_D_883172F4; // size = 0x8

s32 LabPCList_HandleColumnHeaderClick(unk_func_8830867C_02C* arg0, unk_func_88001300_000* arg1, s32 arg2, Controller* arg3) {
    static s16 D_883172DC[] = {
        0x001E,
        0x001F,
        0x0020,
        0x0000,
    };
    static s16 D_883172E4[] = {
        0x001E,
        0x001F,
    };
    static s16 D_883172E8[] = {
        0x001D,
        0x0000,
    };
    static s16 D_883172EC[] = {
        0x0021,
        0x0000,
    };
    static s16 D_883172F0[] = {
        0x0022,
        0x0000,
    };
    static unk_D_883172F4 D_883172F4[] = {
        {
            D_883172EC,
            0x00000001,
        },
        {
            D_883172E8,
            0x00000001,
        },
        {
            D_883172EC,
            0x00000001,
        },
        {
            D_883172F0,
            0x00000001,
        },
        {
            NULL,
            0x00000000,
        },
        {
            NULL,
            0x00000000,
        },
        {
            D_883172DC,
            0x00000003,
        },
        {
            D_883172E4,
            0x00000002,
        },
        {
            D_883172E4,
            0x00000002,
        },
        {
            D_883172E4,
            0x00000002,
        },
        {
            D_883172E4,
            0x00000002,
        },
        {
            D_883172E4,
            0x00000002,
        },
    };

    u32 var_s0;
    s32 sp50;
    s32 i;
    char* sp40[3];

    for (i = 0; i < D_883172F4[arg2 - 2].rotation; i++) {
        sp40[i] = Text_GetString(NULL, 0, gMoveListMessageTable, D_883172F4[arg2 - 2].posX[i]);
    }

    BattleInfoWidget_SetLabels(arg0->unk_08C, sp40, D_883172F4[arg2 - 2].rotation);

    arg0->unk_08C->unk_30 = arg1->unk_10;
    arg0->unk_08C->unk_34 = arg1->unk_14;

    BattleInfoWidget_UpdateViewport(arg0->unk_08C);
    arg0->unk_04C->unk_14(arg0->unk_04C, 0x100);
    var_s0 = BattleInfoWidget_RunEntryModal(arg0->unk_08C, arg3, 0);
    arg0->unk_04C->unk_14(arg0->unk_04C, 1);

    switch (var_s0) {
        case 0:
            var_s0 = 0;
            break;

        case 1:
            switch (arg2) {
                case 2:
                    sp50 = 0x10;
                    break;

                case 3:
                    sp50 = 0xE;
                    break;

                case 4:
                    sp50 = 0xF;
                    break;

                case 5:
                    sp50 = 1;
                    break;

                case 8:
                    sp50 = 3;
                    break;

                case 9:
                    sp50 = 5;
                    break;

                case 10:
                    sp50 = 7;
                    break;

                case 11:
                    sp50 = 9;
                    break;

                case 12:
                    sp50 = 0xB;
                    break;

                case 13:
                    sp50 = 0xD;
                    break;
            }

            LabPCList_SaveFilterState(arg0);
            LabPCList_SetSortMode(arg0, sp50);
            PointerList_Sort(arg0->unk_034->posX.unk_2C, gListSortComparators[arg0->unk_C54.posX]);
            ((func88507AE4)Memmap_GetFragmentVaddr(WidgetTree_SetScrollableGridIndex))(arg0->unk_034, 0);
            var_s0 = 0;
            break;

        case 2:
            switch (arg2) {
                case 8:
                    sp50 = 2;
                    break;

                case 9:
                    sp50 = 4;
                    break;

                case 10:
                    sp50 = 6;
                    break;

                case 11:
                    sp50 = 8;
                    break;

                case 12:
                    sp50 = 0xA;
                    break;

                case 13:
                    sp50 = 0xC;
                    break;
            }

            LabPCList_SaveFilterState(arg0);
            LabPCList_SetSortMode(arg0, sp50);
            PointerList_Sort(arg0->unk_034->posX.unk_2C, gListSortComparators[arg0->unk_C54.posX]);

            ((func88507AE4)Memmap_GetFragmentVaddr(WidgetTree_SetScrollableGridIndex))(arg0->unk_034, 0);
            var_s0 = 0;
            break;

        case 3:
            var_s0 = 1;
            break;
    }

    return var_s0;
}

u32 LabPCList_GetColumnMenuIndex(unk_func_8830867C_02C* arg0) {
    s32 var_v1 = arg0->unk_04C->unk_24;

    if (var_v1 >= 2) {
        switch (arg0->unk_038->unk_2C) {
            case 0:
                break;

            case 1:
                var_v1 += 5;
                break;

            case 2:
                var_v1 += 6;
                break;
        }
    }

    return var_v1;
}

void func_88306FE4(void) {
}

void LabPCList_InitColumnSelectionProxy(ChildSelectionProxy* arg0, unk_func_8830867C_02C* arg1) {
    ((func8850CBA8)Memmap_GetFragmentVaddr(WidgetTree_InitChildSelectionProxy))(arg0);
    arg0->posX.unk_10 = LabPCList_HandleTopLevelInput;
    arg0->unk_24 = arg1;
}

void LabPCList_SaveAll(unk_func_8830867C_02C* arg0, s32 arg1) {
    s32 sp24 = GbSave_GetActivePort();

    ((func88500A6C)Memmap_GetFragmentVaddr(WidgetTree_SelectPage))(arg0->unk_0B0->unk_40, 2);

    Ui_SendMessageAndPollInput(NULL);
    LabPCList_SaveDirtyBoxes(&arg0->unk_144, arg1);
    LabPCList_SaveDirtyDecks(arg0);

    if (arg1 & 0x30) {
        Save_FlushBank(3);
    }

    if (arg1 & 0xF) {
        if (arg1 & 5) {
            GbSave_RebuildSeenBitfield(sp24);
        }
        ((func88900970)Memmap_GetFragmentVaddr(LabUI_ShowSavingPrompt))(arg0->unk_0B0, sp24);
    }

    if (arg1 & 0x30) {
        Save_CommitBankRecords(3);
        Save_FlushBank(3);
    }
}

void LabPCList_MarkIneligibleEntries(unk_func_8830867C_02C* arg0) {
    s32 i;
    s32 var_v0;
    unk_func_8830867C_02C_0CC_000** temp_v0_2;
    unk_func_8830867C_04C_030_02C_000_000* temp_s1;

    temp_s1 = arg0->unk_0AC->unk_30->unk_2C->posX[arg0->unk_0AC->unk_30->unk_38].posX[0];
    temp_v0_2 = arg0->unk_034->posX.unk_2C->posX;

    for (i = 0; i < arg0->unk_034->posX.unk_2C->unk_08; i++) {
        if ((temp_v0_2[i]->unk_08.posX <= 0) || (temp_v0_2[i]->unk_08.posX >= 0x98)) {
            arg0->unk_034->posX.unk_34[i] |= 4;
        } else {
            if (temp_s1->unk_08 >= 0x64) {
                var_v0 = LabPCList_CheckTmHmIneligibility(**(u8**)&temp_s1->posX, &temp_v0_2[i]->unk_08);
            } else if (temp_s1->unk_08 >= 0x32) {
                var_v0 = LabPCList_CheckPpUpIneligibility(&temp_v0_2[i]->unk_08);
            } else {
                var_v0 = LabPCList_CheckVitaminIneligibility(**(u8**)&temp_s1->posX, &temp_v0_2[i]->unk_08);
            }

            if (var_v0 != 0) {
                arg0->unk_034->posX.unk_34[i] |= 4;
            }
        }
    }
}

s32 LabPCList_IsGamePakBoxEmpty(unk_func_8830867C_02C* arg0) {
    return arg0->unk_144.posX->unk_0C->unk_10.unk_08 == 0;
}

s32 LabPCList_ConfirmExit(unk_func_8830867C_02C* arg0, Controller* arg1, s32 arg2) {
    s32 sp34;
    s32 sp30;
    s32 temp_v0_2;

    sp34 = 1;
    sp30 = LabPCList_CheckAnyDirty(arg0);
    if (sp30 != 0) {
        arg0->unk_048->posX.unk_14(arg0->unk_048, 0);
        ((func889006D4)Memmap_GetFragmentVaddr(LabUI_OpenConfirmDialog))(arg0->unk_0B0, LabPCList_IsGamePakBoxEmpty(arg0));

        temp_v0_2 = ((func88900808)Memmap_GetFragmentVaddr(LabUI_RunConfirmDialog))(arg0->unk_0B0, arg1, 1);
        if (temp_v0_2 == 0) {
            LabPCList_SaveAll(arg0, sp30);
            ((func889007AC)Memmap_GetFragmentVaddr(LabUI_CloseConfirmDialog))(arg0->unk_0B0);
        } else if (temp_v0_2 == 1) {
            ((func889007AC)Memmap_GetFragmentVaddr(LabUI_CloseConfirmDialog))(arg0->unk_0B0);
        } else if (temp_v0_2 == 2) {
            ((func889007AC)Memmap_GetFragmentVaddr(LabUI_CloseConfirmDialog))(arg0->unk_0B0);
            sp34 = 0;
        }

        arg0->unk_048->posX.unk_14(arg0->unk_048, 1);
    } else if ((arg2 == 0) && (arg0->unk_CB8 != 0)) {
        arg0->unk_048->posX.unk_14(arg0->unk_048, 0);
        if (BattleInfoWidget_RunSaveConfirmModal(arg0->unk_0B4, arg1) == 1) {
            sp34 = 0;
        }
        arg0->unk_048->posX.unk_14(arg0->unk_048, 1);
    }
    return sp34;
}

void LabPCList_SetGridInteractive(unk_func_8830867C_02C* arg0, s32 arg1) {
    if (arg1 != 0) {
        arg0->unk_02C->posX.unk_28 |= 0x200;
        arg0->unk_030->posX.unk_28 |= 1;
        arg0->unk_04C->unk_14(arg0->unk_04C, 1);
    } else {
        arg0->unk_02C->posX.unk_28 &= ~0x200;
        arg0->unk_030->posX.unk_28 &= ~1;
        arg0->unk_04C->unk_14(arg0->unk_04C, 0);
    }
}

void LabPCList_ResetGridSelection(ChildSelectionProxy* arg0) {
    ((func8850628C)Memmap_GetFragmentVaddr(WidgetTree_ClearEntryFlags))(arg0->unk_24->unk_034);
    arg0->unk_24->unk_0E0 = 0;
    ((func8850CD24)Memmap_GetFragmentVaddr(WidgetTree_SetChildSelectionProxySelection))(arg0, 1);
}

void LabPCList_HandleGridSelectionEntry(ChildSelectionProxy* arg0, Controller* arg1) {
    LabPCList_SetGridInteractive(arg0->unk_24, 0);
    Ui_SendMessageAndPollInput(NULL);
    Ui_SendMessageAndPollInput(NULL);

    if (BattleInfoWidget_RunItemMenuModal(arg0->unk_24->unk_0AC, arg1) == 2) {
        arg0->unk_24->unk_0E0 = 1;
        LabPCList_MarkIneligibleEntries(arg0->unk_24);
        ((func8850CD24)Memmap_GetFragmentVaddr(WidgetTree_SetChildSelectionProxySelection))(arg0, 0);
    } else {
        Ui_SendMessageAndPollInput(NULL);
        LabPCList_SetGridInteractive(arg0->unk_24, 1);
    }
}

s32 LabPCList_HandleBackButton(ChildSelectionProxy* arg0, Controller* arg1) {
    s32 sp1C = 2;

    Audio_PlaySoundEffectById(3);

    if (arg0->unk_24->unk_CB4 != 0) {
        LabPCList_RestoreFilterState(arg0->unk_24);
        LabPCList_ApplyFiltersAndSort(arg0->unk_24);
        ((func88507C0C)Memmap_GetFragmentVaddr(WidgetTree_SetPagedGridSelectionWithOffset))(arg0->unk_24->unk_034, arg0->unk_24->unk_CBC,
                                                               arg0->unk_24->unk_CC0);
        sp1C = 3;
    } else if (LabPCList_ConfirmExit(arg0->unk_24, arg1, 0) == 0) {
        sp1C = 3;
    }
    return sp1C;
}

s32 LabPCList_HandlePageSwitchInput(ChildSelectionProxy* arg0, Controller* arg1) {
    s32 var_v1 = 0;

    if (gPlayer1Controller->buttonPressed & 2) {
        Audio_PlaySoundEffectById(2);
        if (arg0->unk_24->unk_CD0 == 0) {
            arg0->unk_24->unk_CD0 += 3;
        }
        arg0->unk_24->unk_CD0--;
        ((func88500A6C)Memmap_GetFragmentVaddr(WidgetTree_SelectPage))(arg0->unk_24->unk_038, arg0->unk_24->unk_CD0);
        LabPCList_SwitchColumnPage(arg0->unk_24);
        var_v1 = 0x80000005;
    } else if (gPlayer1Controller->buttonPressed & 1) {
        Audio_PlaySoundEffectById(2);
        if (arg0->unk_24->unk_CD0 >= 2) {
            arg0->unk_24->unk_CD0 -= 3;
        }
        arg0->unk_24->unk_CD0++;
        ((func88500A6C)Memmap_GetFragmentVaddr(WidgetTree_SelectPage))(arg0->unk_24->unk_038, arg0->unk_24->unk_CD0);
        LabPCList_SwitchColumnPage(arg0->unk_24);
        var_v1 = 0x80000005;
    }

    return var_v1;
}

s32 LabPCList_HandleGridInput(ChildSelectionProxy* arg0, Controller* arg1, s32 arg2) {
    UNUSED s32 pad;
    s32 temp_v0;
    unk_func_8830867C_02C_0CC_000* sp24;
    unk_func_8830867C_02C_0CC_000* sp20;

    if (arg0->unk_24->unk_0E0 != 0) {
        if (arg2 & 2) {
            Audio_PlaySoundEffectById(3);
            LabPCList_ResetGridSelection(arg0);
            LabPCList_HandleGridSelectionEntry(arg0, arg1);
            arg2 = 1;
        } else if (arg2 & 4) {
            if (arg0->unk_24->unk_034->posX.unk_34[arg0->unk_24->unk_034->posX.unk_38] & 4) {
                Audio_PlaySoundEffectById(8);
                arg2 = 1;
            } else {
                Audio_PlaySoundEffectById(2);
                BattleInfoWidget_SetItemMenuMon(
                    arg0->unk_24->unk_0AC,
                    &arg0->unk_24->unk_034->posX.unk_2C->posX[arg0->unk_24->unk_034->posX.unk_38]->unk_08);

                arg0->unk_24->unk_034->posX.posX.unk_24(&arg0->unk_24->unk_034->posX.posX, 0x100);

                if (BattleInfoWidget_RunItemMenuModal(arg0->unk_24->unk_0AC, arg1) == 1) {
                    Ui_SendMessageAndPollInput(NULL);
                    func_88305F28(arg0->unk_24);
                    LabPCList_ResetGridSelection(arg0);
                    LabPCList_SetGridInteractive(arg0->unk_24, 1);
                } else {
                    arg0->unk_24->unk_034->posX.posX.unk_24(&arg0->unk_24->unk_034->posX.posX, 1);
                }
            }
        }
        arg2 = 1;
    } else if (arg2 & 8) {
        if (arg1->buttonPressed & 0x800) {
            ((func8850CD24)Memmap_GetFragmentVaddr(WidgetTree_SetChildSelectionProxySelection))(arg0, 1);
            ((func8850CB48)Memmap_GetFragmentVaddr(WidgetTree_SetGridMenuSelection))(arg0->unk_24->unk_04C, 1);
            arg2 |= 0x80000001;
        }
    } else {
        if (arg2 & 2) {
            arg2 = LabPCList_HandleBackButton(arg0, arg1);
        } else if (arg2 & 4) {
            if (arg0->unk_24->unk_034->posX.unk_2C->unk_08 == 0) {
                Audio_PlaySoundEffectById(8);
                arg2 = 1;
            } else {
                Audio_PlaySoundEffectById(2);
                temp_v0 = LabPCList_OpenRowMenu(arg0->unk_24, arg1);
                if (temp_v0 == 1) {
                    sp24 = arg0->unk_24->unk_034->posX.unk_2C->posX[arg0->unk_24->unk_034->posX.unk_38];

                    BattleInfoWidget_SetMoveDestinationTitle(arg0->unk_24->unk_0A8, sp24->posX->posX->unk_08, sp24->posX->rotation);
                    BattleInfoWidget_MarkIneligibleDestinations(arg0->unk_24->unk_0A8, sp24);

                    arg0->unk_24->unk_034->posX.posX.unk_24(&arg0->unk_24->unk_034->posX.posX, 0x100);

                    Ui_SendMessageAndPollInput(NULL);
                    Ui_SendMessageAndPollInput(NULL);
                    if (BattleInfoWidget_RunMoveDestinationModal(arg0->unk_24->unk_0A8, arg1) == 1) {
                        LabPCList_PerformMoveMon(arg0->unk_24, sp24, arg1);
                    }
                    Ui_SendMessageAndPollInput(NULL);

                    arg0->unk_24->unk_034->posX.posX.unk_24(&arg0->unk_24->unk_034->posX.posX, 1);

                    arg2 = 1;
                } else if (temp_v0 == 2) {
                    BattleInfoWidget_RebindItemGrid(arg0->unk_24->unk_0AC, &arg0->unk_24->unk_C48);
                    BattleInfoWidget_SetItemMenuMon(
                        arg0->unk_24->unk_0AC,
                        &arg0->unk_24->unk_034->posX.unk_2C->posX[arg0->unk_24->unk_034->posX.unk_38]->unk_08);
                    BattleInfoWidget_SetItemMenuMode(arg0->unk_24->unk_0AC, 0);

                    arg0->unk_24->unk_034->posX.posX.unk_24(&arg0->unk_24->unk_034->posX.posX, 0x100);

                    Ui_SendMessageAndPollInput(NULL);
                    Ui_SendMessageAndPollInput(NULL);
                    if (BattleInfoWidget_RunItemMenuModal(arg0->unk_24->unk_0AC, arg1) == 1) {
                        func_88305F28(arg0->unk_24);
                    }
                    Ui_SendMessageAndPollInput(NULL);

                    arg0->unk_24->unk_034->posX.posX.unk_24(&arg0->unk_24->unk_034->posX.posX, 1);

                    arg2 = 1;
                } else {
                    if (temp_v0 == 3) {
                        sp20 = arg0->unk_24->unk_034->posX.unk_2C->posX[arg0->unk_24->unk_034->posX.unk_38];

                        arg0->unk_24->unk_CDC->unk_0C = &sp20->unk_08;
                        arg0->unk_24->unk_CDC->unk_10 = sp20->posX->posX->unk_08;

                        arg0->unk_24->unk_CD8(1, arg0->unk_24->unk_CDC);

                        arg0->unk_24->unk_034->posX.posX.unk_24(&arg0->unk_24->unk_034->posX.posX, 0x100);

                        if (arg0->unk_24->unk_CD8(4, arg0->unk_24->unk_CDC) == 1) {
                            sp20->posX->unk_0C = 1;
                        }
                        Ui_SendMessageAndPollInput(NULL);

                        arg0->unk_24->unk_034->posX.posX.unk_24(&arg0->unk_24->unk_034->posX.posX, 1);
                    }
                    arg2 = 1;
                }
            }
        } else if (gPlayer1Controller->buttonPressed & 0x10) {
            ((func8850CD24)Memmap_GetFragmentVaddr(WidgetTree_SetChildSelectionProxySelection))(arg0, 1);
            arg2 = 0x80000005;
        } else {
            arg2 = LabPCList_HandlePageSwitchInput(arg0, arg1);
        }
    }

    return arg2;
}

s32 LabPCList_HandleColumnMenuInput(ChildSelectionProxy* arg0, Controller* arg1, s32 arg2) {
    u32 sp34;
    s32 temp_s0_11;
    s32 sp2C;
    s32 sp28;
    s32 sp24;
    s32 temp_s0_23;
    s32 temp_s0_27;
    s32 temp_v0_2;

    if (arg2 & 8) {
        if ((arg1->buttonPressed == 0x400) && (arg0->unk_24->unk_04C->unk_24 == 1)) {
            ((func8850CD24)Memmap_GetFragmentVaddr(WidgetTree_SetChildSelectionProxySelection))(arg0, 0);
            ((func88507AE4)Memmap_GetFragmentVaddr(WidgetTree_SetScrollableGridIndex))(
                arg0->unk_24->unk_034, arg0->unk_24->unk_034->unk_58 / arg0->unk_24->unk_034->posX.unk_3E);
            arg0->unk_24->unk_034->unk_6C = 8;
            arg0->unk_24->unk_034->unk_54 = 0x400;
            arg2 |= 0x80000001;
        }
    } else {
        if (arg2 & 2) {
            arg2 = LabPCList_HandleBackButton(arg0, arg1);
        } else if (arg2 & 4) {
            sp34 = LabPCList_GetColumnMenuIndex(arg0->unk_24);
            switch (sp34) {
                case 0:
                    Audio_PlaySoundEffectById(3);
                    arg2 = 2;
                    if (LabPCList_ConfirmExit(arg0->unk_24, arg1, 1) == 0) {
                        arg2 = 3;
                    }
                    break;

                case 1:
                    Audio_PlaySoundEffectById(2);
                    temp_v0_2 = LabPCList_OpenListMenu(arg0->unk_24, arg1);
                    if (temp_v0_2 == 1) {
                        sp2C = -1;
                        if (LabPCList_HasFilterFlag(arg0->unk_24, 0x20) != 0) {
                            sp2C = arg0->unk_24->unk_C54.unk_2C;
                        }
                        BattleInfoWidget_SetStatusSelection(arg0->unk_24->unk_098, sp2C);

                        arg0->unk_24->unk_04C->unk_14(arg0->unk_24->unk_04C, 0x100);

                        Ui_SendMessageAndPollInput(NULL);
                        Ui_SendMessageAndPollInput(NULL);

                        sp2C = BattleInfoWidget_RunStatusModal(arg0->unk_24->unk_098, arg1);
                        Ui_SendMessageAndPollInput(NULL);

                        arg0->unk_24->unk_04C->unk_14(arg0->unk_24->unk_04C, 1);

                        if (sp2C > 0) {
                            sp2C--;
                            LabPCList_SaveFilterState(arg0->unk_24);

                            if ((sp2C + 1) == arg0->unk_24->unk_098->unk_30->unk_2C->unk_08) {
                                LabPCList_ClearFilterFlag(arg0->unk_24, 0x20);
                            } else {
                                LabPCList_SetFilterFlag(arg0->unk_24, 0x20);
                                arg0->unk_24->unk_C54.unk_2C = sp2C;
                            }

                            LabPCList_ApplyFiltersAndSort(arg0->unk_24);
                            arg2 = 1;
                        }
                    } else if (temp_v0_2 == 2) {
                        BattleInfoWidget_RebindItemGrid(arg0->unk_24->unk_0AC, &arg0->unk_24->unk_C48);
                        BattleInfoWidget_SetItemMenuMon(arg0->unk_24->unk_0AC, 0);
                        BattleInfoWidget_SetItemMenuMode(arg0->unk_24->unk_0AC, 1);
                        LabPCList_HandleGridSelectionEntry(arg0, arg1);
                        arg2 = 1;
                    } else {
                        if (temp_v0_2 == 3) {
                            BattleInfoWidget_BindData(arg0->unk_24->unk_094, &arg0->unk_24->unk_144);

                            arg0->unk_24->unk_04C->unk_14(arg0->unk_24->unk_04C, 0x100);

                            Ui_SendMessageAndPollInput(NULL);
                            Ui_SendMessageAndPollInput(NULL);
                            if (BattleInfoWidget_RunSelectionModal(arg0->unk_24->unk_094, arg1) == 1) {
                                LabPCList_FlattenEntries(&arg0->unk_24->unk_03C, &arg0->unk_24->unk_144);
                                LabPCList_ApplyFiltersAndSort(arg0->unk_24);
                                LabPCList_DiscardFilterBackup(arg0->unk_24);
                            }
                            Ui_SendMessageAndPollInput(NULL);
                            arg0->unk_24->unk_04C->unk_14(arg0->unk_24->unk_04C, 1);
                        }
                    }
                    arg2 = 1;
                    break;

                case 2:
                    Audio_PlaySoundEffectById(2);
                    LabPCList_HandleColumnHeaderClick(arg0->unk_24, arg0->unk_24->unk_058, sp34, arg1);
                    arg2 = 1;
                    break;

                case 3:
                    Audio_PlaySoundEffectById(2);
                    LabPCList_HandleColumnHeaderClick(arg0->unk_24, arg0->unk_24->unk_05C, sp34, arg1);
                    arg2 = 1;
                    break;

                case 4:
                    Audio_PlaySoundEffectById(2);
                    LabPCList_HandleColumnHeaderClick(arg0->unk_24, arg0->unk_24->unk_060, sp34, arg1);
                    arg2 = 1;
                    break;

                case 5:
                    Audio_PlaySoundEffectById(2);
                    LabPCList_HandleColumnHeaderClick(arg0->unk_24, arg0->unk_24->unk_064, sp34, arg1);
                    arg2 = 1;
                    break;

                case 8:
                    Audio_PlaySoundEffectById(2);
                    if (LabPCList_HandleColumnHeaderClick(arg0->unk_24, arg0->unk_24->unk_070, sp34, arg1) == 1) {
                        if (arg0->unk_24->unk_C54.unk_0C != 0) {
                            sp28 = arg0->unk_24->unk_C54.unk_09;
                            sp24 = arg0->unk_24->unk_C54.unk_08;
                        } else {
                            sp28 = arg0->unk_24->unk_C54.unk_08;
                            sp24 = arg0->unk_24->unk_C54.unk_09;
                        }
                        BattleInfoWidget_SetLevelRange(arg0->unk_24->unk_0A4, sp28, sp24, LabPCList_HasFilterFlag(arg0->unk_24, 1));

                        arg0->unk_24->unk_04C->unk_14(arg0->unk_24->unk_04C, 0x100);

                        Ui_SendMessageAndPollInput(NULL);
                        Ui_SendMessageAndPollInput(NULL);
                        temp_s0_11 = BattleInfoWidget_RunLevelRangeModal(arg0->unk_24->unk_0A4, arg1);
                        Ui_SendMessageAndPollInput(NULL);

                        arg0->unk_24->unk_04C->unk_14(arg0->unk_24->unk_04C, 1);

                        if (temp_s0_11 != 0) {
                            if (temp_s0_11 == 1) {
                                LabPCList_SaveFilterState(arg0->unk_24);
                                if (arg0->unk_24->unk_0A4->unk_3C->unk_30.posX >=
                                    arg0->unk_24->unk_0A4->unk_38->unk_30.posX) {
                                    arg0->unk_24->unk_C54.unk_0C = 0;
                                    arg0->unk_24->unk_C54.unk_08 = arg0->unk_24->unk_0A4->unk_38->unk_30.posX;
                                    arg0->unk_24->unk_C54.unk_09 = arg0->unk_24->unk_0A4->unk_3C->unk_30.posX;
                                    LabPCList_SetSortMode(arg0->unk_24, 2);
                                } else {
                                    arg0->unk_24->unk_C54.unk_0C = 1;
                                    arg0->unk_24->unk_C54.unk_09 = arg0->unk_24->unk_0A4->unk_38->unk_30.posX;
                                    arg0->unk_24->unk_C54.unk_08 = arg0->unk_24->unk_0A4->unk_3C->unk_30.posX;
                                    LabPCList_SetSortMode(arg0->unk_24, 3);
                                }
                                LabPCList_SetFilterFlag(arg0->unk_24, 1);
                                LabPCList_ApplyFiltersAndSort(arg0->unk_24);
                                arg2 = 1;
                            } else {
                                if (temp_s0_11 == 2) {
                                    LabPCList_SaveFilterState(arg0->unk_24);
                                    arg0->unk_24->unk_C54.unk_08 = 1;
                                    arg0->unk_24->unk_C54.unk_09 = 0x64;
                                    arg0->unk_24->unk_C54.unk_0C = 0;
                                    LabPCList_ClearFilterFlag(arg0->unk_24, 1);
                                    LabPCList_ApplyFiltersAndSort(arg0->unk_24);
                                }
                            }
                        }
                    }
                    arg2 = 1;
                    break;

                case 9:
                    Audio_PlaySoundEffectById(2);
                    LabPCList_HandleColumnHeaderClick(arg0->unk_24, arg0->unk_24->unk_074, sp34, arg1);
                    arg2 = 1;
                    break;

                case 10:
                    Audio_PlaySoundEffectById(2);
                    LabPCList_HandleColumnHeaderClick(arg0->unk_24, arg0->unk_24->unk_078, sp34, arg1);
                    arg2 = 1;
                    break;

                case 11:
                    Audio_PlaySoundEffectById(2);
                    LabPCList_HandleColumnHeaderClick(arg0->unk_24, arg0->unk_24->unk_07C, sp34, arg1);
                    arg2 = 1;
                    break;

                case 12:
                    Audio_PlaySoundEffectById(2);
                    LabPCList_HandleColumnHeaderClick(arg0->unk_24, arg0->unk_24->unk_080, sp34, arg1);
                    arg2 = 1;
                    break;

                case 13:
                    Audio_PlaySoundEffectById(2);
                    LabPCList_HandleColumnHeaderClick(arg0->unk_24, arg0->unk_24->unk_084, sp34, arg1);
                    arg2 = 1;
                    break;

                case 6:
                    Audio_PlaySoundEffectById(2);
                    BattleInfoWidget_SetTypeEntries(arg0->unk_24->unk_09C, &arg0->unk_24->unk_C54.unk_1C);

                    arg0->unk_24->unk_04C->unk_14(arg0->unk_24->unk_04C, 0x100);

                    temp_s0_23 = BattleInfoWidget_RunTypeSelectionModal(arg0->unk_24->unk_09C, arg1);
                    arg0->unk_24->unk_04C->unk_14(arg0->unk_24->unk_04C, 1);

                    if (temp_s0_23 != 0) {
                        if (temp_s0_23 == 1) {
                            LabPCList_SaveFilterState(arg0->unk_24);
                            BattleInfoWidget_GetTypeEntries(arg0->unk_24->unk_09C, &arg0->unk_24->unk_C54.unk_1C);
                            if (arg0->unk_24->unk_C54.unk_1C.posX == 0) {
                                LabPCList_ClearFilterFlag(arg0->unk_24, 2);
                            } else {
                                LabPCList_SetFilterFlag(arg0->unk_24, 2);
                            }
                            LabPCList_ApplyFiltersAndSort(arg0->unk_24);
                        } else if (temp_s0_23 == 2) {
                            LabPCList_SaveFilterState(arg0->unk_24);
                            LabPCList_ClearFilterFlag(arg0->unk_24, 2);
                            arg0->unk_24->unk_C54.unk_1C.posX = 0;
                            LabPCList_ApplyFiltersAndSort(arg0->unk_24);
                        }
                    }
                    arg2 = 1;
                    break;

                case 7:
                    Audio_PlaySoundEffectById(2);
                    BattleInfoWidget_SetMoveSlots(arg0->unk_24->unk_0A0, &arg0->unk_24->unk_C54.unk_24);

                    arg0->unk_24->unk_04C->unk_14(arg0->unk_24->unk_04C, 0x100);

                    temp_s0_27 = BattleInfoWidget_RunMovePanelModal(arg0->unk_24->unk_0A0, arg1);

                    arg0->unk_24->unk_04C->unk_14(arg0->unk_24->unk_04C, 1);

                    if (temp_s0_27 != 0) {
                        if (temp_s0_27 == 1) {
                            LabPCList_SaveFilterState(arg0->unk_24);
                            BattleInfoWidget_GetMoveSlots(arg0->unk_24->unk_0A0, &arg0->unk_24->unk_C54.unk_24);
                            if (arg0->unk_24->unk_C54.unk_24.rotation == 0) {
                                LabPCList_ClearFilterFlag(arg0->unk_24, 4);
                            } else {
                                LabPCList_SetFilterFlag(arg0->unk_24, 4);
                            }
                            LabPCList_ApplyFiltersAndSort(arg0->unk_24);
                            arg2 = 1;
                        } else if (temp_s0_27 == 2) {
                            LabPCList_SaveFilterState(arg0->unk_24);
                            LabPCList_ClearFilterFlag(arg0->unk_24, 4);
                            arg0->unk_24->unk_C54.unk_24.rotation = 0;
                            LabPCList_ApplyFiltersAndSort(arg0->unk_24);
                        }
                    }
                    arg2 = 1;
                    break;
            }
        } else if (gPlayer1Controller->buttonPressed & 0x20) {
            ((func8850CD24)Memmap_GetFragmentVaddr(WidgetTree_SetChildSelectionProxySelection))(arg0, 0);
            arg2 = 0x80000005;
        } else {
            arg2 = LabPCList_HandlePageSwitchInput(arg0, arg1);
        }
    }

    return arg2;
}

s32 LabPCList_HandleTopLevelInput(ChildSelectionProxy* arg0, Controller* arg1) {
    s32 i;
    s32 var_a2 = 0;
    ChildSelectionProxy* var_a0;

    if (arg0->posX.unk_20 > 0) {
        var_a0 = arg0->posX.posX.rotation;

        for (i = 0; i < arg0->posX.unk_1C; i++) {
            var_a0 = var_a0->posX.posX.unk_08;
        }

        var_a2 = var_a0->posX.unk_10(var_a0, arg1);
    }

    if (var_a2 & 1) {
        return var_a2;
    }

    if (var_a2 == 0) {
        if (arg1->buttonPressed & 0x4000) {
            var_a2 = 0x80000002;
        } else if (arg1->buttonPressed & 0x8000) {
            var_a2 = 0x80000004;
        }
    }

    switch (arg0->posX.unk_1C) {
        case 0:
            var_a2 = LabPCList_HandleGridInput(arg0, arg1, var_a2);
            break;

        case 1:
            var_a2 = LabPCList_HandleColumnMenuInput(arg0, arg1, var_a2);
            break;
    }

    return var_a2;
}

void LabPCList_BuildWidget(unk_func_8830867C* arg0, s32 arg1, s32 arg2, MemoryPool* arg3, TextObject* arg4, char** arg5,
                   char** arg6, char** arg7, char** arg8, char** arg9) {
    static Color_RGBA8 D_88317354 = { 0x1E, 0x50, 0x50, 0xFF };
    static Color_RGBA8 D_88317358 = { 0x00, 0x0A, 0x0A, 0xFF };

    unk_func_88001300_000* sp8C;
    unk_func_88001300_000* sp88;
    FragmentEntry sp84;
    unk_func_88500EE4* sp80;
    unk_func_885088F4* sp7C;
    unk_func_88509A2C* sp78;
    unk_func_88509E34* sp74;
    unk_func_88001300_000* sp70;

    ((func885007CC)Memmap_GetFragmentVaddr(WidgetTree_InitWidget))(arg0, sizeof(unk_func_8830867C));

    arg0->posX.unk_10.posX = arg1;
    arg0->posX.unk_10.posY = arg2;

    sp8C = mem_pool_alloc(arg3, sizeof(unk_func_88001300_000));
    ((func885031E8)Memmap_GetFragmentVaddr(WidgetTree_InitVisibilityGate))(sp8C, 0, 0, 0x280, 0x1E0);
    ((func8850068C)Memmap_GetFragmentVaddr(WidgetTree_AppendChild))(&arg0->posX.posX, &sp8C->posX);

    sp80 = mem_pool_alloc(arg3, sizeof(unk_func_88500EE4));
    ((func88500EE4)Memmap_GetFragmentVaddr(WidgetTree_InitTintedTexture))(sp80, 0, 0, 0x280, 0x1E0, gTitleScreenImage, D_88317354,
                                                           D_88317358);
    ((func8850068C)Memmap_GetFragmentVaddr(WidgetTree_AppendChild))(&sp8C->posX, &sp80->posX.posX);

    sp7C = mem_pool_alloc(arg3, sizeof(unk_func_885088F4));
    ((func885088F4)Memmap_GetFragmentVaddr(WidgetTree_InitSlideTransition))(sp7C, 0x41, 0x15C, 0xDC);
    sp7C->unk_2C = 5;
    ((func8850068C)Memmap_GetFragmentVaddr(WidgetTree_AppendChild))(&sp8C->posX, &sp7C->posX.posX);

    sp78 = mem_pool_alloc(arg3, sizeof(unk_func_88509A2C));
    ((func88509A2C)Memmap_GetFragmentVaddr(WidgetTree_InitSaveSlotLabel))(sp78, 0x38, 0x22, GbSave_GetActivePort(),
                                                           Text_GetString(NULL, 0, D_8831A4C0, 0));
    ((func8850068C)Memmap_GetFragmentVaddr(WidgetTree_AppendChild))(&sp7C->posX.posX, &sp78->posX.posX);

    sp74 = mem_pool_alloc(arg3, sizeof(unk_func_88509E34));
    ((func88509E34)Memmap_GetFragmentVaddr(WidgetTree_InitTextMessage))(sp74, 0, 0, Text_GetString(NULL, 0, gMoveListMessageTable, 0));
    ((func8850068C)Memmap_GetFragmentVaddr(WidgetTree_AppendChild))(&sp7C->posX.posX, &sp74->posX.posX);

    sp88 = mem_pool_alloc(arg3, sizeof(unk_func_88001300_000));
    ((func885031E8)Memmap_GetFragmentVaddr(WidgetTree_InitVisibilityGate))(sp88, 0, 0, 0x280, 0x1E0);
    ((func8850068C)Memmap_GetFragmentVaddr(WidgetTree_AppendChild))(&arg0->posX.posX, &sp88->posX);

    arg0->unk_30 = mem_pool_alloc(arg3, sizeof(unk_func_8830867C_030));
    BattleInfoWidget_InitDropdownMenu(arg0->unk_30, sp88, arg3);

    arg0->unk_34 = mem_pool_alloc(arg3, sizeof(unk_func_8830867C_034));
    BattleInfoWidget_Build(arg0->unk_34, 0x56, 0x78, sp88, arg3);

    arg0->unk_38 = mem_pool_alloc(arg3, sizeof(unk_func_8830867C_038));
    BattleInfoWidget_BuildStatusMenu(arg0->unk_38, 0x56, 0x96, sp88, arg3);

    arg0->unk_3C = mem_pool_alloc(arg3, sizeof(unk_func_8830867C_03C));
    BattleInfoWidget_BuildTypePanel(arg0->unk_3C, 0xAA, 0x78, sp88, arg3);

    arg0->unk_40 = mem_pool_alloc(arg3, sizeof(unk_func_8830867C_040));
    BattleInfoWidget_BuildMovePanel(arg0->unk_40, 0xAA, 0x78, sp88, arg3);

    arg0->unk_44 = mem_pool_alloc(arg3, sizeof(unk_func_8830867C_044));
    BattleInfoWidget_BuildLevelRangeMenu(arg0->unk_44, 0xAA, 0xF5, sp88, arg3);

    arg0->unk_48 = mem_pool_alloc(arg3, sizeof(unk_func_8830867C_048));
    BattleInfoWidget_BuildMoveDestinationMenu(arg0->unk_48, 0xAA, 0x78, sp88, arg3);

    arg0->unk_4C = mem_pool_alloc(arg3, sizeof(unk_func_8830867C_04C));
    BattleInfoWidget_BuildItemMenu(arg0->unk_4C, 0xE7, 0x94, sp88, arg3);

    arg0->unk_50 = mem_pool_alloc(arg3, sizeof(unk_func_889000C4));

    ((func889000C4)Memmap_GetFragmentVaddr(LabUI_BuildConfirmDialog))(arg0->unk_50, 0, 0, 0, arg5, arg3);

    sp84 = FRAGMENT_LOAD(fragment27);

    arg0->unk_54.rotation = arg3;
    // clang-format off
    arg0->unk_54.posX = 0x38; arg0->unk_54.posY = 0x4E;
    // clang-format on
    arg0->unk_54.unk_14 = sp88;
    arg0->unk_6C = 0;
    arg0->unk_70 = arg6;
    arg0->unk_74 = D_8831A4D0;
    arg0->unk_78 = gMoveNamesTable;
    arg0->unk_7C = gMessageBank_MoveNames;
    arg0->unk_80 = arg7;
    arg0->unk_84 = arg8;
    arg0->unk_88 = arg9;

    sp84(0, &arg0->unk_54);

    arg0->unk_2C = mem_pool_alloc(arg3, sizeof(unk_func_8830867C_02C));
    LabPCList_BuildListScreen(arg0->unk_2C, 0x2C, 0x48, sp8C, arg0->unk_30, arg0->unk_34, arg0->unk_38, arg0->unk_3C, arg0->unk_40,
                  arg0->unk_44, arg0->unk_48, arg0->unk_4C, arg0->unk_50, sp84, &arg0->unk_54, arg3, arg4);

    ((func8850068C)Memmap_GetFragmentVaddr(WidgetTree_AppendChild))(&sp88->posX, &arg0->unk_2C->unk_000.posX);

    sp70 = mem_pool_alloc(arg3, sizeof(unk_func_88001300_000));

    ((func885007CC)Memmap_GetFragmentVaddr(WidgetTree_InitWidget))(sp70, 0x2C);

    // clang-format off
    sp70->unk_10.posX = 0x2C; sp70->unk_10.posY = 0x7C;
    // clang-format on

    ((func8850068C)Memmap_GetFragmentVaddr(WidgetTree_AppendChild))(&arg0->posX.posX, &sp70->posX);
    ((func8850068C)Memmap_GetFragmentVaddr(WidgetTree_AppendChild))(&sp70->posX, &arg0->unk_30->posX.posX);
    ((func8850068C)Memmap_GetFragmentVaddr(WidgetTree_AppendChild))(&arg0->posX.posX, &arg0->unk_34->posX.posX);
    ((func8850068C)Memmap_GetFragmentVaddr(WidgetTree_AppendChild))(&arg0->posX.posX, &arg0->unk_38->posX.posX);
    ((func8850068C)Memmap_GetFragmentVaddr(WidgetTree_AppendChild))(&arg0->posX.posX, &arg0->unk_3C->posX.posX);
    ((func8850068C)Memmap_GetFragmentVaddr(WidgetTree_AppendChild))(&arg0->posX.posX, &arg0->unk_40->posX.posX);
    ((func8850068C)Memmap_GetFragmentVaddr(WidgetTree_AppendChild))(&arg0->posX.posX, &arg0->unk_44->posX.posX);
    ((func8850068C)Memmap_GetFragmentVaddr(WidgetTree_AppendChild))(&arg0->posX.posX, &arg0->unk_48->posX.posX);
    ((func8850068C)Memmap_GetFragmentVaddr(WidgetTree_AppendChild))(&arg0->posX.posX, &arg0->unk_4C->posX.posX);
    ((func8850068C)Memmap_GetFragmentVaddr(WidgetTree_AppendChild))(&arg0->posX.posX, &arg0->unk_50->posX.posX);
    ((func8850068C)Memmap_GetFragmentVaddr(WidgetTree_AppendChild))(&arg0->posX.posX, &arg0->unk_54.unk_08->posX);

    arg0->unk_50->posX.unk_10.posX =
        arg0->unk_2C->unk_000.unk_10.posX +
        ((arg0->unk_2C->unk_02C->posX.unk_14.posX - arg0->unk_50->unk_2C->posX.unk_14.posX) / 2);
    arg0->unk_50->posX.unk_10.posY =
        arg0->unk_2C->unk_000.unk_10.posY +
        ((arg0->unk_2C->unk_02C->posX.unk_14.posY - arg0->unk_50->unk_2C->posX.unk_14.posY) / 2);
}

void LabPCList_RunWidgetLoop(unk_func_8830867C* arg0) {
    s32 sp34 = 0;

    while (sp34 == 0) {
        BgStage_DrawFrame();

        ((func885008C4)Memmap_GetFragmentVaddr(WidgetTree_Update))(&arg0->posX);
        ((func88500828)Memmap_GetFragmentVaddr(WidgetTree_Draw))(&arg0->posX, 0, 0);

        BgStage_AdvanceFrame();
        Ui_ReceiveMessage(&sp34);
    }
}

void LabPCList_ScreenThreadEntry(unk_func_8830867C* arg0) {
    Input_SetRepeatController(gPlayer1Controller);
    LabPCList_RunPartySelectionModal(arg0->unk_2C, gPlayer1Controller);

    while (arg0->unk_2C->unk_02C->posX.unk_28 & 1) {
        Ui_SendMessageAndPollInput(NULL);
    }

    Ui_SendMessageAndPollInput(1);
    osStopThread(NULL);
}

s32 LabPCList_ShowListScreen(UNUSED s32 arg0, UNUSED s32 arg1) {
    TextObject* sp54;
    MemoryPool* sp50;
    void* sp4C;
    u8* sp48;
    TextObjectThreadData* sp44;
    char** sp40;
    char** sp3C;
    char** sp38;
    char** sp34;
    char** sp30;

    main_pool_push_state('PCHK');

    sp54 = Font_Init(0x1C, 0);

    ASSET_LOAD(D_04000000, fragment29_misc_1, 0);
    FRAGMENT_LOAD(fragment26);
    FRAGMENT_LOAD(fragment25);
    FRAGMENT_LOAD(fragment29);

    Text_InitStringTables();

    D_8831A4C0 = Text_GetStringTable(0x2A);
    gMoveNamesTable = Text_GetStringTable(0x25);
    D_8831A4D0 = Text_GetStringTable(0x24);
    gMessageBank_MoveNames = Text_GetStringTable(0x26);
    gMoveListMessageTable = Text_GetStringTable(5);
    gMsgBank_StatNames = Text_GetStringTable(0x27);
    gMsgBank_ItemNames = Text_GetStringTable(0xC);

    sp40 = Text_GetStringTable(7);
    sp3C = Text_GetStringTable(6);
    sp38 = Text_GetStringTable(0x28);
    sp34 = Text_GetStringTable(0x29);
    sp30 = Text_GetStringTable(0xB);

    sp48 = main_pool_alloc(0x1000, 0);

    sp50 = mem_pool_try_init(0x18000, 0);

    sp4C = mem_pool_alloc(sp50, sizeof(unk_func_8830867C));
    LabPCList_BuildWidget(sp4C, 0, 0, sp50, sp54, sp40, sp3C, sp38, sp34, sp30);

    sp44 = ALIGN16((u32)mem_pool_alloc(sp50, sizeof(TextObjectThreadData)));

    osCreateThread(&sp44->thread, 0x32, LabPCList_ScreenThreadEntry, sp4C, sp48 + 0x1000, osGetThreadPri(NULL) - 1);

    Ui_InitInputMessageQueue();

    osStartThread(&sp44->thread);

    StageLoader_UpdateSegments();
    LabPCList_RunWidgetLoop(sp4C);

    osDestroyThread(&sp44->thread);

    StageLoader_WaitForRetrace();

    main_pool_pop_state('PCHK');

    FRAGMENT_LOAD_AND_CALL2(fragment23, 4, 0);

    return 0x25;
}
