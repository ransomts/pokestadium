#ifndef _2E110_H_
#define _2E110_H_

#include "global.h"

void func_8002D510(void);
char** GetMessageBank(s32 file_number);
void func_8002D5D4(u32 arg0, u32 arg1);
void func_8002D600(u32 arg0, u32 arg1);
void DecompressString(char* arg0, u32 arg1, s8* arg2);
char* GetMessageString(char* arg0, s32 arg1, char** arg2, u32 file_number);
s32 CountTextLines(s8* arg0);

#endif // _2E110_H_
