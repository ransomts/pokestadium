#include "src/fragments/gallery_backgrounds/gallery_backgrounds.h"
#include "src/2E110.h"

static char** gMessageBank_2C;
static char** gMessageBank_1A;

void Gallery_InitStringTables(void) {
    gMessageBank_2C = Text_GetStringTable(0x2C);
    gMessageBank_1A = Text_GetStringTable(0x1A);
}

char* Gallery_GetUiString(s32 arg0) {
    return Text_GetString(NULL, 0, gMessageBank_2C, arg0);
}

char* Gallery_CopyUiString(char* arg0, s32 arg1, s32 arg2) {
    return Text_GetString(arg0, arg1, gMessageBank_2C, arg2);
}

char* Gallery_GetCommonUiString(s32 arg0) {
    Text_GetString(NULL, 0, gMessageBank_1A, arg0);
}

char* Gallery_CopyCommonUiString(char* arg0, s32 arg1, u32 arg2) {
    Text_GetString(arg0, arg1, gMessageBank_1A, arg2);
}
