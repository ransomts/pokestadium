#ifndef _1CF30_H_
#define _1CF30_H_

#include "global.h"

extern TextObject* gFontManager;

void Gfx_DrawTextureRect(s16 arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5, s16 arg6, s16 arg7, s32 arg8);
void Gfx_DrawTextureRect2(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6);
void Gfx_FillRect(s16 arg0, s16 arg1, s16 arg2, s16 arg3, u8 arg4, u8 arg5, u8 arg6);
void Gfx_FillRectRGBA(s16 arg0, s16 arg1, s16 arg2, s16 arg3, u8 arg4, u8 arg5, u8 arg6, u8 arg7);
void Gfx_DrawSpriteRGBA16(s16 arg0, s16 arg1, s16 arg2, s16 arg3, u8* arg4, s16 arg5, s32 arg6);
void Gfx_DrawSpriteRGBA32(s16 arg0, s16 arg1, s16 arg2, s16 arg3, u8* arg4, s16 arg5, s32 arg6);
void Gfx_DrawSpriteIA8(s16 arg0, s16 arg1, s16 arg2, s16 arg3, u8* arg4, s16 arg5, s32 arg6);
void Gfx_DrawSpriteIA16(s16 arg0, s16 arg1, s16 arg2, s16 arg3, u8* arg4, s16 arg5, s32 arg6);
void Gfx_DrawSpriteI4(s16 arg0, s16 arg1, s16 arg2, s16 arg3, u8* arg4, s16 arg5, s32 arg6);
void Gfx_DrawSpriteI8(s16 arg0, s16 arg1, s16 arg2, s16 arg3, u8* arg4, s16 arg5, s32 arg6);
void Gfx_DrawSpriteI16(s16 arg0, s16 arg1, s16 arg2, s16 arg3, u8* arg4, s16 arg5, s32 arg6);
void func_8001D560(s16 arg0, s16 arg1, s16 arg2, s16 arg3, u8* arg4, u8* arg5, s16 arg6, s32 arg7);
void Gfx_DrawTextureAtlas(u8* arg0);
void Gfx_DrawClippedTextureRegion(u32 arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4);
void Gfx_DrawTileMap16x16(s16 arg0, s16 arg1, s16 arg2, f32 arg3, Vtx* arg4, u32 arg5);
Vtx* AllocateTileMapVertices(void);
void SetTileVertex(Vtx* arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4, s16 arg5, u8 arg6, u8 arg7, u8 arg8, u8 arg9);
void SetViewport(Vp* arg0, s16 arg1, s16 arg2);
u8 GetCharIndexFromFontTables(u16 arg0);
u8 Text_GetCharWidth(FontBankInfo* arg0, u16 arg1);
void func_8001E7C0(UNUSED s32 arg0, UNUSED s32 arg1);
void Text_UnloadFont(UNUSED s32 arg0, s32 arg1);
s32 GetFontBank(s32 arg0);
void LoadFontBank(s32 arg0, s32 arg1, s32 arg2);
TextObject* Text_Init(s32 arg0, s32 arg1);
void func_8001E9CC(void);
void LoadFontBanksFromMask(s32 arg0);
void FreeFontBanks(s32 arg0);
void Text_SetFont(s32 arg0, s32 arg1);
s32 GetFontBankInfo(s32 arg0, FontBankInfo* arg1);
s16 Text_DrawGlyph(s16 arg0, s16 arg1, s16 arg2);
char* func_8001F1C4(char* buffer, const char* data, u32 size);
void Text_Print(s32 x, s32 y, const char* fmt, ...);
void Text_PutChar(s32 arg0, s32 arg1, s32 arg2);
void Text_SetEnvColor(s32 r, s32 g, s32 b, s32 a);
void Text_SetPrimColor(s32 r, s32 g, s32 b, s32 a);
void Text_SetLineHeight(s32 arg0);
void Text_SetNoWordWrap(void);
void Text_EnableWordWrap(void);
void Text_ResetState(void);
void Text_SetupDL(void);
void Text_BeginRender(void);
void Text_EndRender(void);
void Text_DrawWindowRect(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7);
s32 MeasureTextWidth(s32 x, s32 y, const char* fmt, ...);
u8 MeasureCharWidth(s32 arg0, s32 arg1);

#endif // _1CF30_H_
