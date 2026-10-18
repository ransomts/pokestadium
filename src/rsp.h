#ifndef _RSP_H_
#define _RSP_H_

#include "PR/leo.h"

struct UnkStruct800006C4_2 {
    char unk0;
    char filler1[0x1B];
    s32 unk1C;
    void* vaddr;
    s32 size;
    s32 unk28;
};

struct UnkStruct80000A80 {
    LEOCmd cmd;
    union {
        u32 lba;
        struct {
            char filler0[0x3];
            LEOSpdlMode mode;
        };
    };
    void *addr;
};

struct UnkStruct80083BD0 {
    OSMesg unk0;
    u8 unk4[0x18];
    OSMesgQueue queue1;
    OSMesgQueue queue2;
};

s32 Rsp_CreateLeoManager(void);
OSPiHandle *Rsp_GetSramHandle(void);
s32 Rsp_ReadSram(struct UnkStruct800006C4_2* arg0);
s32 Rsp_WriteSram(struct UnkStruct800006C4_2* arg0);
s32 Rsp_ReadRom(struct UnkStruct800006C4_2* arg0, s32 arg1);
s32 Rsp_WriteRom(struct UnkStruct800006C4_2* arg0);
s32 Rsp_ReadFlash(struct UnkStruct800006C4_2* arg0);
s32 Rsp_WriteFlash(struct UnkStruct800006C4_2* arg0);
void *Rsp_RecvMessage(void);
void *Rsp_LeoRead(struct UnkStruct800006C4_2* arg0);
void *Rsp_LeoWrite(struct UnkStruct800006C4_2* arg0);
void *Rsp_LeoReadDiskID(struct UnkStruct80000A80* arg0);
void *Rsp_LeoSeek(struct UnkStruct80000A80* arg0);
void *Rsp_LeoSpdlMotor(struct UnkStruct80000A80* arg0);
void *Rsp_LeoReadRTC(struct UnkStruct80000A80* arg0);
void *Rsp_LeoSetRTC(struct UnkStruct80000A80* arg0);
void thread20_rsp(void *arg);
void rsp_init(void);
void Rsp_ResetLeo(void);
void Rsp_SendMessage(void* arg0, s32 arg1);

#endif // _RSP_H_
