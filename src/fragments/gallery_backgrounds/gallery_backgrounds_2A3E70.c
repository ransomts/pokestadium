#include "src/fragments/gallery_backgrounds/gallery_backgrounds.h"
#include "src/text_system.h"

static char** gMessageBankGalleryUiStrings;
static char** gMessageBankTeamSelectionLabels;

void Gallery_InitStringTables(void) {
    gMessageBankGalleryUiStrings = Text_GetStringTable(0x2C);
    gMessageBankTeamSelectionLabels = Text_GetStringTable(0x1A);
}

char* Gallery_GetUiString(s32 arg0) {
    return Text_GetString(NULL, 0, gMessageBankGalleryUiStrings, arg0);
}

char* Gallery_CopyUiString(char* arg0, s32 arg1, s32 arg2) {
    return Text_GetString(arg0, arg1, gMessageBankGalleryUiStrings, arg2);
}

char* Gallery_GetCommonUiString(s32 arg0) {
    Text_GetString(NULL, 0, gMessageBankTeamSelectionLabels, arg0);
}

char* Gallery_CopyCommonUiString(char* arg0, s32 arg1, u32 arg2) {
    Text_GetString(arg0, arg1, gMessageBankTeamSelectionLabels, arg2);
}
