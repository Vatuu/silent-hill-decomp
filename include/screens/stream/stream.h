#ifndef _STREAM_H
#define _STREAM_H

#include "common.h"
#include <libcd.h>
#include <libgpu.h>

extern int StCdIntrFlag; // Not included in SDK docs/headers, but movie player sample code (and moviesys) uses it?

extern s32 D_800B5C30;

extern u8  D_800A900C[];

typedef struct
{
    /* 0x00 */ u_long* vlcbuf[2];
    /* 0x08 */ s32     vlcid;
    /* 0x0C */ u16*    imgbuf;
    /* 0x10 */ RECT    rect[2];
    /* 0x20 */ s32     rectid;
    /* 0x24 */ RECT    slice;
    /* 0x2C */ s32     isdone;
} DECENV;

typedef struct
{
    /* 0x00000 */ CdlLOC loc;
    /* 0x00004 */ DECENV dec;
    /* 0x00034 */ s32    Rewind_Switch; // or Clear_Flag
    /* 0x00038 */ s32    width;
    /* 0x0003C */ s32    height;
    /* 0x00040 */ u16    imgbuf0[5760];
    /* 0x02D40 */ u16    imgbuf1[5760];
    /* 0x05A40 */ u_long sect_buff[11776];
    /* 0x11240 */ u_long vlcbuf0[14336];
    /* 0x1F240 */ u_long vlcbuf1[14336];
} MOVIE_STR;

// Customised StHEADER?
typedef struct
{
    u16    id;
    u16    type;
    u16    secCount;
    u16    nSectors;
    u_long frameCount;
    u_long frameSize;
    u16    width;
    u16    height;
    u_long headm;
    u_long headv;
    u_long user;
} CDSECTOR;

#define RING_SIZE 23
#define MOVIE_WAIT 2000
#define PPW 3 / 2

extern MOVIE_STR* m;
extern s32        frame_cnt;
#ifdef NON_MATCHING
extern DISPENV	  disp;
extern s32 		  max_frame;
#endif

void    open_main(s32 file_idx, s16 num_frames);
void    movie_main(char* file_name, s32 f_size, s32 sector);
void    strSetDefDecEnv(DECENV* dec, s32 x0, s32 y0, s32 x1, s32 y1);
void    strInit(CdlLOC* loc, void (*callback)());
void    strCallback();
void    strKickCD(CdlLOC* loc);
s32     strNextVlc(DECENV* dec);
u_long* strNext(DECENV* dec);
void    strSync(DECENV* dec);

#endif
