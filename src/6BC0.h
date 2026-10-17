#ifndef _6BC0_H_
#define _6BC0_H_

#include "global.h"

// image size in bits
typedef enum IMAGE_SIZE_BITS {
	IMAGE_SIZE_BITS_4b  = 0,
	IMAGE_SIZE_BITS_8b  = 1,
	IMAGE_SIZE_BITS_16b = 2,
	IMAGE_SIZE_BITS_32b = 3,
} IMAGE_SIZE_BITS;

typedef enum IMAGE_FMT {
	IMAGE_FMT_RGBA = 0,
	IMAGE_FMT_YUV  = 1,
	IMAGE_FMT_CI   = 2,
	IMAGE_FMT_IA   = 3,
	IMAGE_FMT_I    = 4,
} IMAGE_FMT;

typedef struct FramebufferImage {
	/* 0x00 */ u16 fmt;
	/* 0x02 */ u16 size;
	/* 0x04 */ u16 width;
	/* 0x06 */ u16 height;
	/* 0x08 */ u8* img_p;
	/* 0x0C */ struct FramebufferImage* depth_p;
} FramebufferImage; // size = 0x10

ClipRect* Gfx_MakeClipRect(ClipRect* arg0, s16 x1, s16 y1, s16 x2, s16 y2);
s32 Gfx_IntersectClip(ClipRect* arg0);
void Gfx_SetScissorRect(Gfx** gfx_p, s16 x, s16 y, s16 width, s16 height);
void Gfx_RestoreScissor(Gfx** gfx_p);
void FramebufferImage_Init(FramebufferImage* arg0, s32 fmt, s32 size, s32 width, s32 height, u32 img_p);
FramebufferImage* FramebufferImage_Allocate(s32 fmt, s32 size, s32 width, s32 height, s32 side);
void FramebufferImage_AttachDepth(FramebufferImage* img, FramebufferImage* depth);
void Gfx_ResetFramebufferState(void);
FramebufferImage* Gfx_GetCurrentFramebuffer(void);
void Gfx_SetupFrameBuffer(Gfx** gfx_p, FramebufferImage* arg1);
void Gfx_FillRectangle(Gfx** gfx_p, s32 arg1, s32 arg2, s32 arg3, s32 arg4, u16 fill_colour);
void Gfx_FillDepthRectangle(Gfx** gfx_p, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void Gfx_FillScreen(Gfx** gfx_p, u16 fill_colour);


#endif // _6BC0_H_
