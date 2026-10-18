#ifndef _FRAGMENT48_H_
#define _FRAGMENT48_H_

#include "global.h"

void Gallery_Debugger_PostLoad(void);
void func_83900028(void);
void func_83900030(void);
void Gallery_Debugger_Init(void);
void Gallery_Debugger_WriteBankData(void);
void Gallery_Debugger_DrawMenu(void);
void Gallery_Debugger_Render(void);
s32 Gallery_Debugger_HandleInput(void);
s32 Gallery_Debugger_MainLoop(void);
void Gallery_Debugger_UpdateController(void);
void Gallery_Debugger_Run(void);
s32 Gallery_Debugger_Entry(s32 arg0, s32 arg1);

#endif // _FRAGMENT48_H_
