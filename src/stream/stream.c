#include "common.h"

#include <libcd.h>
#include <libds.h>
#include <libgte.h>
#include <libgpu.h>
#include <libpress.h>

extern int StCdIntrFlag; // not included in SDK docs/headers, but movie player sample code (and moviesys) uses it?

typedef struct
{
    /* 0x00 */ u_long *vlcbuf[2];
    /* 0x08 */ int vlcid;
    /* 0x0C */ u_short *imgbuf;
    /* 0x10 */ RECT rect[2];
    /* 0x20 */ int rectid;
    /* 0x24 */ RECT slice;
    /* 0x2C */ int isdone;
} DECENV;

typedef struct
{
    /* 0x00000 */ CdlLOC loc;
    /* 0x00004 */ DECENV dec;
    /* 0x00034 */ int Rewind_Switch; // or Clear_Flag
    /* 0x00038 */ int width;
    /* 0x0003C */ int height;
    /* 0x00040 */ u_short imgbuf0[5760];
    /* 0x02D40 */ u_short imgbuf1[5760];
    /* 0x05A40 */ u_long sect_buff[11776];
    /* 0x11240 */ u_long vlcbuf0[14336];
    /* 0x1F240 */ u_long vlcbuf1[14336];
} MOVIE_STR;

// customised StHEADER ?
typedef struct {
    u_short id;
    u_short type;
    u_short secCount;
    u_short nSectors;
    u_long frameCount;
    u_long frameSize;
    u_short width;
    u_short height;
    u_long headm;
    u_long headv;
    u_long user;
} CDSECTOR;

#define RING_SIZE 23
#define MOVIE_WAIT 2000
#define PPW 3/2

extern MOVIE_STR* m;
extern u_int frame_cnt;

void open_main(int file_idx, int num_frames);
void movie_main(char *file_name, int f_size, int sector);
void strSetDefDecEnv(DECENV *dec, int x0, int y0, int x1, int y1);
void strInit(CdlLOC *loc, void (*callback)());
void strCallback();
void strKickCD(CdlLOC *loc);
int strNextVlc(DECENV *dec);
u_long *strNext(DECENV *dec);
void strSync(DECENV *dec, int mode);

INCLUDE_ASM("asm/stream/nonmatchings/stream", func_801E2654);

INCLUDE_ASM("asm/stream/nonmatchings/stream", func_801E279C);

INCLUDE_ASM("asm/stream/nonmatchings/stream", func_801E2838);

INCLUDE_ASM("asm/stream/nonmatchings/stream", func_801E28B0);

INCLUDE_ASM("asm/stream/nonmatchings/stream", func_801E2908);

INCLUDE_ASM("asm/stream/nonmatchings/stream", func_801E2A24);

INCLUDE_ASM("asm/stream/nonmatchings/stream", open_main);

INCLUDE_ASM("asm/stream/nonmatchings/stream", movie_main);

void strSetDefDecEnv(DECENV* dec, int x0, int y0, int x1, int y1)
{
    dec->rect[0].w = 480;
    dec->rect[1].w = 480;
    dec->vlcid = 0;
    dec->rectid = 0;
    dec->isdone = 0;
    dec->rect[0].x = x0;
    dec->rect[0].y = y0;
    dec->rect[0].h = 240;
    dec->rect[1].x = x1;
    dec->rect[1].h = 240;
    dec->slice.x = x0;
    dec->slice.y = y0;
    dec->slice.w = 16*PPW;
    dec->slice.h = 240;
    dec->vlcbuf[0] = m->vlcbuf0;
    dec->vlcbuf[1] = m->vlcbuf1;
    dec->imgbuf = m->imgbuf0;
    dec->rect[1].y = y1;
}

void strInit(CdlLOC* loc, void (*callback)())
{
    DecDCTReset(0);
    DecDCToutCallback(callback);
    StSetRing(m->sect_buff, RING_SIZE);
    StSetStream(1, 1, 0xffffffff, 0, 0);
    strKickCD(loc);
}

void strCallback()
{
    RECT snap_rect;
    int id;
    u16* imgbuf;

    if (StCdIntrFlag)
    {
        StCdInterrupt();
        StCdIntrFlag = 0;
    }

    snap_rect = m->dec.slice;

    DrawSync(0);
    LoadImage(&snap_rect, (u_long *)m->dec.imgbuf);

    imgbuf = m->imgbuf0;
    m->dec.slice.x += m->dec.slice.w;
    
    if (m->dec.imgbuf == imgbuf)
    {
        imgbuf = m->imgbuf1;
    }
    
    m->dec.imgbuf = imgbuf;

    if (m->dec.slice.x < m->dec.rect[m->dec.rectid].x + m->dec.rect[m->dec.rectid].w)
    {
        DecDCTout((u_long *)m->dec.imgbuf, m->dec.slice.w*m->dec.slice.h/2);
    }
    else
    {
        DrawSync(0);
        m->dec.isdone = 1;

        m->dec.rectid = m->dec.rectid ^ 1;
        m->dec.slice.x = m->dec.rect[m->dec.rectid].x;
        m->dec.slice.y = m->dec.rect[m->dec.rectid].y;
    }

}

void strKickCD(CdlLOC* loc)
{
    char v2[8];
    u_char param;

    while (!CdControlB(CdlNop, 0, v2) || (v2[0] & 2) == 0)
    {
        CdControlB(CdlStandby, 0, 0);
        VSync(0);
    }
    param = 0x80;
    while (!CdControl(CdlSetmode, &param, 0));
    while (!CdControl(CdlSeekL, loc, 0))
        VSync(0);
    while (!CdRead2(CdlModeStream|CdlModeSpeed|CdlModeRT|CdlModeSize1))
        VSync(0);
}

int strNextVlc(DECENV *dec)
{
    u_long *next, *strNext();

    u_long cnt = 2000;
    while ((next = strNext(dec)) == 0)
    {
        cnt--;
        if (!cnt)
            return -1;
    }

    dec->vlcid = dec->vlcid ^ 1;
    DecDCTvlc(next, dec->vlcbuf[dec->vlcid]);

    StFreeRing(next);
    return 0;
}

u_long *strNext(DECENV *dec)
{
    u_long *addr;
    CDSECTOR *sector;
    int cnt = MOVIE_WAIT;

    while (StGetNext((u_long **)&addr,(u_long **)&sector))
    {
        if (--cnt == 0)
            return(0);
    }

    if (addr[0] != sector->headm || addr[1] != sector->headv)
    {
        StFreeRing(addr);
        return 0;
    }

    frame_cnt = sector->frameCount;

    if (m->width != sector->width || m->height != sector->height)
    {
        m->width = sector->width;
        m->height = sector->height;
    }

    dec->rect[0].w = dec->rect[1].w = m->width*PPW;
    dec->rect[0].h = dec->rect[1].h = m->height;
    dec->slice.h = m->height;
    return addr;
}

void strSync(DECENV *dec, int mode /* VOID */)
{
    volatile u_long cnt = WAIT_TIME;

    while (dec->isdone == 0)
    {
        if (--cnt == 0)
        {
            dec->isdone = 1;
            dec->rectid = dec->rectid ^ 1;
            dec->slice.x = dec->rect[dec->rectid].x;
            dec->slice.y = dec->rect[dec->rectid].y;
        }
    }
    dec->isdone = 0;
}

