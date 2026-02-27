#ifndef _SCREENS_STREAM_H
#define _SCREENS_STREAM_H

#include "common.h"

#include <psyq/libcd.h>
#include <psyq/libgpu.h>

extern int StCdIntrFlag; // Not included in SDK docs/headers, but movie player sample code (and moviesys) uses it?

extern u8 D_800A900C[];

typedef struct
{
    u_long* vlcbuf[2]; /* 0x00 */
    s32     vlcid;     /* 0x08 */
    u16*    imgbuf;    /* 0x0C */
    RECT    rect[2];   /* 0x10 */
    s32     rectid;    /* 0x20 */
    RECT    slice;     /* 0x24 */
    s32     isdone;    /* 0x2C */
} DECENV;

typedef struct
{
    CdlLOC loc;              /* 0x00000 */
    DECENV dec;              /* 0x00004 */
    s32    Rewind_Switch;    /* 0x00034  / or Clear_Flag */
    s32    width;            /* 0x00038 */
    s32    height;           /* 0x0003C */
    u16    imgbuf0[5760];    /* 0x00040 */
    u16    imgbuf1[5760];    /* 0x02D40 */
    u_long sect_buff[11776]; /* 0x05A40 */
    u_long vlcbuf0[14336];   /* 0x11240 */
    u_long vlcbuf1[14336];   /* 0x1F240 */
} MOVIE_STR;

// Customized `StHEADER`?
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

// Handlers for movie-related GameStates

void GameState_MovieIntroFadeIn_Update(void);
void GameState_MovieIntro_Update(void);
void GameState_MovieOpening_Update(void);
void GameState_ExitMovie_Update(void);
void GameState_DebugMoviePlayer_Update(void); /** @unused debug movie player. Movie to play decided by `LStickLeft`/`LStickRight`. */
void GameState_MovieIntroAlternate_Update(void);

// MOVIESYS code

void    open_main(s32 file_idx, s16 num_frames);
void    movie_main(char* file_name, s32 f_size, s32 sector);
void    strSetDefDecEnv(DECENV* dec, s32 x0, s32 y0, s32 x1, s32 y1);
void    strInit(CdlLOC* loc, void (*callback)());
void    strCallback(void);
void    strKickCD(CdlLOC* loc);
s32     strNextVlc(DECENV* dec);
u_long* strNext(DECENV* dec);
void    strSync(DECENV* dec);

#endif
