#include "game.h"

#include <libcd.h>
#include <libds.h>
#include <libgte.h>
#include <libgpu.h>
#include <libpress.h>

#include "bodyprog/bodyprog.h"
#include "main/fileinfo.h"
#include "screens/stream/stream.h"

// Old IDB name: MainLoopState3_StartMovieIntro_801E2654
void func_801E2654(void)
{
    s32 prev_594;

    switch (g_GameWork.field_598)
    {
        case 0:
            VSync(8);
            D_800BCD0C = 6;
            GameFS_TitleGfxLoad();
            g_GameWork.field_598++;
            break;

        case 1:
            if (g_pController1->btns_held_C != 0 || g_SysWork.field_1C >= 301)
            {
                D_800BCD0C           = 3;
                g_GameWork.field_598 = 2;
            }
            break;

        case 2:
            if ((D_800BCD0C & 7) == 5)
            {
                Fs_QueueWaitForEmpty();

                prev_594 = g_GameWork.field_594;

                g_GameWork.field_594 = 6;
                g_SysWork.field_1C   = 0;
                g_SysWork.field_20   = 0;
                g_GameWork.field_59C = 0;
                g_GameWork.field_5A0 = 0;
                g_SysWork.field_8    = 0;
                g_SysWork.field_24   = 0;
                g_SysWork.field_C    = 0;
                g_SysWork.field_28   = 0;
                g_SysWork.field_10   = 0;
                g_SysWork.field_2C   = 0;
                g_SysWork.field_14   = 0;
                g_GameWork.field_598 = prev_594;
                g_GameWork.field_590 = prev_594;
                g_GameWork.field_598 = 0;
            }
            break;
    }

    func_800314EC(D_800A900C);
}

// Old IDB name: MainLoopState6_Movie_PlayIntro_801E279C
// Old IDB name: MainLoopState6_Movie_PlayIntro_801E279C
void func_801E279C(void)
{
    s32 prev_594;
    s32 file_idx = 2053; // XA/C1_20670

    if (g_pGameWork->optExtraOptionsEnabled_27 & 1)
    {
        file_idx = 2054; // XA/C2_20670
    }

    open_main(file_idx, 0);

    prev_594 = g_GameWork.field_594;

    g_GameWork.field_594 = 7;
    g_SysWork.field_1C   = 0;
    g_SysWork.field_20   = 0;
    g_GameWork.field_59C = 0;
    g_GameWork.field_5A0 = 0;
    g_SysWork.field_8    = 0;
    g_SysWork.field_24   = 0;
    g_SysWork.field_C    = 0;
    g_SysWork.field_28   = 0;
    g_SysWork.field_10   = 0;
    g_SysWork.field_2C   = 0;
    g_SysWork.field_14   = 0;
    g_GameWork.field_598 = prev_594;
    g_GameWork.field_590 = prev_594;
    g_GameWork.field_598 = 0;
    D_800B5C30           = 0x1000;
}

// Old IDB name: MainLoopState9_Movie_PlayOpening_801E2838
// Old IDB name: MainLoopState9_Movie_PlayOpening_801E2838
void func_801E2838(void)
{
    s32 prev_594;

    open_main(2055, 0); // XA/M1_03500

    prev_594 = g_GameWork.field_594;

    g_GameWork.field_594 = 0xA;
    g_SysWork.field_1C   = 0;
    g_SysWork.field_20   = 0;
    g_GameWork.field_59C = 0;
    g_GameWork.field_5A0 = 0;
    g_SysWork.field_8    = 0;
    g_SysWork.field_24   = 0;
    g_SysWork.field_C    = 0;
    g_SysWork.field_28   = 0;
    g_SysWork.field_10   = 0;
    g_SysWork.field_2C   = 0;
    g_SysWork.field_14   = 0;
    g_GameWork.field_598 = prev_594;
    g_GameWork.field_590 = prev_594;
    g_GameWork.field_598 = 0;
}

// Old IDB name: MainLoopStateD_ReturnToGame_801E28B0
// Old IDB name: MainLoopStateD_ReturnToGame_801E28B0
void func_801E28B0(void)
{
    s32 prev_594;

    prev_594 = g_GameWork.field_594;

    g_GameWork.field_594 = 11;
    g_SysWork.field_1C   = 0;
    g_SysWork.field_20   = 0;
    g_GameWork.field_59C = 0;
    g_GameWork.field_5A0 = 0;
    g_SysWork.field_8    = 0;
    g_SysWork.field_24   = 0;
    g_SysWork.field_C    = 0;
    g_SysWork.field_28   = 0;
    g_SysWork.field_10   = 0;
    g_SysWork.field_2C   = 0;
    g_SysWork.field_14   = 0;
    g_GameWork.field_598 = prev_594;
    g_GameWork.field_590 = prev_594;
    g_GameWork.field_598 = 0;
}

// Old IDB name: MainLoopState11_Movie_PlayEnding_801E2908
// Old IDB name: MainLoopState11_Movie_PlayEnding_801E2908
void func_801E2908(void)
{
    s_GameWork*       gameWork   = g_pGameWork0;
    s_ControllerData* controller = g_pController1;
    s32               prev_594;

    if (controller->btns_new_10 & gameWork->controllerBinds_0.cancel)
    {
        prev_594 = g_GameWork.field_594;

        g_GameWork.field_594 = 0x16;
        g_SysWork.field_1C   = 0;
        g_SysWork.field_20   = 0;
        g_GameWork.field_59C = 0;
        g_GameWork.field_5A0 = 0;
        g_SysWork.field_8    = 0;
        g_SysWork.field_24   = 0;
        g_SysWork.field_C    = 0;
        g_SysWork.field_28   = 0;
        g_SysWork.field_10   = 0;
        g_SysWork.field_2C   = 0;
        g_SysWork.field_14   = 0;
        g_GameWork.field_598 = prev_594;
        g_GameWork.field_590 = prev_594;
        g_GameWork.field_598 = 0;
    }

    if (controller->field_18 & 0x08000000)
    {
        D_801E3F3C--;
    }

    if (controller->field_18 & 0x02000000)
    {
        D_801E3F3C++;
    }

    func_80031EFC(0x28, 0x28);
    if (controller->btns_new_10 & gameWork->controllerBinds_0.enter)
    {
        open_main(2072 - D_801E3F3C, 0);
    }
}

// Old IDB name: MainLoopState5_Movie_PlayIntroAlternate_801E2A24
// Old IDB name: MainLoopState5_Movie_PlayIntroAlternate_801E2A24
void func_801E2A24(void)
{
    s32 prev_594;

    open_main(2053, 2060); // XA/C1_20670

    prev_594 = g_GameWork.field_594;

    g_GameWork.field_594 = 7;
    g_SysWork.field_1C   = 0;
    g_SysWork.field_20   = 0;
    g_GameWork.field_59C = 0;
    g_GameWork.field_5A0 = 0;
    g_SysWork.field_8    = 0;
    g_SysWork.field_24   = 0;
    g_SysWork.field_C    = 0;
    g_SysWork.field_28   = 0;
    g_SysWork.field_10   = 0;
    g_SysWork.field_2C   = 0;
    g_SysWork.field_14   = 0;
    g_GameWork.field_598 = prev_594;
    g_GameWork.field_590 = prev_594;
    g_GameWork.field_598 = 0;
    D_800B5C30           = 0x1000;
}

void open_main(s32 file_idx, s16 num_frames) // 0x801E2AA4
{
    Fs_QueueWaitForEmpty();
    if (!num_frames)
    {
        num_frames = g_FileTable[file_idx].blockCount - 7;
    }

    GFX_ClearRectInterlaced(0, 16, 480, 480, 0, 0, 0);
    movie_main(NULL, num_frames, g_FileTable[file_idx].startSector);
    GFX_ClearRectInterlaced(0, 16, 480, 480, 0, 0, 0);
    VSync(0);
    GsSwapDispBuff();
}

INCLUDE_ASM("asm/screens/stream/nonmatchings/stream", movie_main);

void strSetDefDecEnv(DECENV* dec, s32 x0, s32 y0, s32 x1, s32 y1) // 0x801E2F8C
{
    dec->rect[0].w = 480;
    dec->rect[1].w = 480;
    dec->vlcid     = 0;
    dec->rectid    = 0;
    dec->isdone    = 0;
    dec->rect[0].x = x0;
    dec->rect[0].y = y0;
    dec->rect[0].h = 240;
    dec->rect[1].x = x1;
    dec->rect[1].h = 240;
    dec->slice.x   = x0;
    dec->slice.y   = y0;
    dec->slice.w   = 16 * PPW;
    dec->slice.h   = 240;
    dec->vlcbuf[0] = m->vlcbuf0;
    dec->vlcbuf[1] = m->vlcbuf1;
    dec->imgbuf    = m->imgbuf0;
    dec->rect[1].y = y1;
}

void strInit(CdlLOC* loc, void (*callback)()) // 0x801E300C
{
    DecDCTReset(0);
    DecDCToutCallback(callback);
    StSetRing(m->sect_buff, RING_SIZE);
    StSetStream(1, 1, 0xFFFFFFFF, 0, 0);
    strKickCD(loc);
}

void strCallback() // 0x801E307C
{
    RECT snap_rect;
    s32  id;
    u16* imgbuf;

    if (StCdIntrFlag)
    {
        StCdInterrupt();
        StCdIntrFlag = 0;
    }

    snap_rect = m->dec.slice;

    DrawSync(0);
    LoadImage(&snap_rect, (u_long*)m->dec.imgbuf);

    imgbuf = m->imgbuf0;
    m->dec.slice.x += m->dec.slice.w;

    if (m->dec.imgbuf == imgbuf)
    {
        imgbuf = m->imgbuf1;
    }

    m->dec.imgbuf = imgbuf;

    if (m->dec.slice.x < (m->dec.rect[m->dec.rectid].x + m->dec.rect[m->dec.rectid].w))
    {
        DecDCTout((u_long*)m->dec.imgbuf, m->dec.slice.w * m->dec.slice.h / 2);
    }
    else
    {
        DrawSync(0);
        m->dec.isdone = 1;

        m->dec.rectid  = m->dec.rectid ^ 1;
        m->dec.slice.x = m->dec.rect[m->dec.rectid].x;
        m->dec.slice.y = m->dec.rect[m->dec.rectid].y;
    }
}

void strKickCD(CdlLOC* loc) // 0x801E31CC
{
    s8 v2[8];
    u8 param;

    while (!CdControlB(CdlNop, 0, v2) || (v2[0] & 2) == 0)
    {
        CdControlB(CdlStandby, 0, 0);
        VSync(0);
    }

    param = 0x80;
    while (!CdControl(CdlSetmode, &param, 0))
    {
    {
        ;
    }
    }

    while (!CdControl(CdlSeekL, loc, 0))
    {
    {
        VSync(0);
    }
    }

    while (!CdRead2(CdlModeStream | CdlModeSpeed | CdlModeRT | CdlModeSize1))
    {
    {
        VSync(0);
    }
    }
}

int strNextVlc(DECENV* dec) // 0x801E3298
{
    u_long* next, *strNext();

    u_long cnt = 2000;
    while ((next = strNext(dec)) == 0)
    {
        cnt--;
        if (!cnt)
        {
        {
            return -1;
        }
        }
    }

    dec->vlcid = dec->vlcid ^ 1;
    DecDCTvlc(next, dec->vlcbuf[dec->vlcid]);

    StFreeRing(next);
    return 0;
}

u_long* strNext(DECENV* dec) // 0x801E331C
{
    u_long*   addr;
    CDSECTOR* sector;
    int       cnt = MOVIE_WAIT;

    while (StGetNext((u_long**)&addr, (u_long**)&sector))
    {
        if (--cnt == 0)
        {
            return 0;
        }
    }

    if (addr[0] != sector->headm || addr[1] != sector->headv)
    {
        StFreeRing(addr);
        return 0;
    }

    frame_cnt = sector->frameCount;

    if (m->width != sector->width || m->height != sector->height)
    {
        m->width  = sector->width;
        m->height = sector->height;
    }

    dec->rect[0].w = dec->rect[1].w = m->width * PPW;
    dec->rect[0].h = dec->rect[1].h = m->height;
    dec->slice.h                    = m->height;
    return addr;
}

void strSync(DECENV* dec) // 0x801E3438
{
    volatile u_long cnt = WAIT_TIME;

    while (dec->isdone == 0)
    {
        if (--cnt == 0)
        {
            dec->isdone  = 1;
            dec->rectid  = dec->rectid ^ 1;
            dec->slice.x = dec->rect[dec->rectid].x;
            dec->slice.y = dec->rect[dec->rectid].y;
        }
    }

    dec->isdone = 0;
}
