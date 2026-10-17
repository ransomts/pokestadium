#ifndef _2E110_H_
#define _2E110_H_

#include "global.h"

void MessageBank_Init(void);
char** GetMessageBank(s32 file_number);
void MessageBank_SetPointer_0x14_0x2A(u32 arg0, u32 arg1);
void MessageBank_SetPointer_1_9(u32 arg0, u32 arg1);
void DecompressString(char* arg0, u32 arg1, s8* arg2);
char* GetMessageString(char* arg0, s32 arg1, char** arg2, u32 file_number);
s32 CountTextLines(s8* arg0);

#endif // _2E110_H_
