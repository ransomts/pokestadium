#include "fragment43.h"
#include "src/2E110.h"

static char** gMessageBank_2C;
static char** gMessageBank_1A;

void Text_LoadMessageBanks(void) {
    gMessageBank_2C = GetMessageBank(0x2C);
    gMessageBank_1A = GetMessageBank(0x1A);
}

char* Text_GetMessageString_Bank2C(s32 arg0) {
    return GetMessageString(NULL, 0, gMessageBank_2C, arg0);
}

char* Text_GetMessageString_Bank2C_Buffered(char* arg0, s32 arg1, s32 arg2) {
    return GetMessageString(arg0, arg1, gMessageBank_2C, arg2);
}

char* Text_GetMessageString_Bank1A(s32 arg0) {
    GetMessageString(NULL, 0, gMessageBank_1A, arg0);
}

char* Text_GetMessageString_Bank1A_Buffered(char* arg0, s32 arg1, u32 arg2) {
    GetMessageString(arg0, arg1, gMessageBank_1A, arg2);
}
