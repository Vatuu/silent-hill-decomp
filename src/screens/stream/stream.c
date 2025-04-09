#include "game.h"

#include <libds.h>
#include <libpress.h>

#include "bodyprog/libsd.h"

#include "bodyprog/bodyprog.h"
#include "main/fileinfo.h"
#include "screens/stream/stream.h"

#define SCRN_WIDTH 320
#define SCRN_HEIGHT 240

// Old IDB name: MainLoopState3_StartMovieIntro_801E2654
void func_801E2654()
{
    switch (g_GameWork.gameStateStep_598[0])
    {
        case 0:
            VSync(8);
            D_800BCD0C = 6;
            GameFs_TitleGfxLoad();
            g_GameWork.gameStateStep_598[0]++;
            break;

        case 1:
            if (g_ControllerPtr0->btns_held_C != 0 || g_SysWork.field_1C >= 301)
            {
                D_800BCD0C           = 3;
                g_GameWork.gameStateStep_598[0] = 2;
            }
            break;

        case 2:
            if ((D_800BCD0C & 7) == 5)
            {
                Fs_QueueWaitForEmpty();

                Game_StateSetNext(GameState_MovieIntro);
            }
            break;
    }

    func_800314EC(D_800A900C);
}

// Old IDB name: MainLoopState6_Movie_PlayIntro_801E279C
void func_801E279C()
{
    s32 fileIdx = FILE_XA_C1_20670;

    if (g_GameWorkPtr0->optExtraOptionsEnabled_27 & 1)
    {
        fileIdx = FILE_XA_C2_20670;
    }

    open_main(fileIdx, 0);
    Game_StateSetNext(GameState_MainMenu);

    D_800B5C30 = 0x1000;
}

// Old IDB name: MainLoopState9_Movie_PlayOpening_801E2838
void func_801E2838()
{
    open_main(FILE_XA_M1_03500, 0);
    Game_StateSetNext(GameState_LoadScreen);
}

// Old IDB name: MainLoopStateD_ReturnToGame_801E28B0
void func_801E28B0()
{
    Game_StateSetNext(GameState_InGame);
}

// Old IDB name: MainLoopState11_Movie_PlayEnding_801E2908
// Movie to play seems decided by LStickLeft/LStickRight, possibly debug movie player?
void func_801E2908()
{
    extern s32 g_Debug_MoviePlayerIndex; // Only used in this func, maybe a static.

    s_GameWork*       gameWork;
    s_ControllerData* controller;

    gameWork   = g_GameWorkPtr1;
    controller = g_ControllerPtr0;

    if (controller->btns_new_10 & gameWork->controllerBinds_0.cancel)
    {
        Game_StateSetNext(GameState_Unk16); // Changes to nonexistent state 0x16 (22) and crashes, maybe removed debug menu.
    }

    if (controller->field_18 & Pad_LStickLeft)
    {
        g_Debug_MoviePlayerIndex--;
    }

    if (controller->field_18 & Pad_LStickRight)
    {
        g_Debug_MoviePlayerIndex++;
    }

    Gfx_DebugStringPosition(40, 40);

#ifdef DEBUG
    // Recreated code from pre-Jan17 builds which include calls to display these (though DebugStringDraw was nullsub in those builds...)
    Gfx_DebugStringDraw("MOVIE NO=");
    Gfx_DebugStringDraw(Math_IntegerToString(2, g_Debug_MoviePlayerIndex));
#endif

    if (controller->btns_new_10 & gameWork->controllerBinds_0.enter)
    {
        open_main(FILE_XA_ZC_14392 - g_Debug_MoviePlayerIndex, 0);
    }
}

// Old IDB name: MainLoopState5_Movie_PlayIntroAlternate_801E2A24
void func_801E2A24(void)
{
    open_main(FILE_XA_C1_20670, 2060); // Second param looks like file ID for FILE_XA_M6_02112, but is actually frame count?
    Game_StateSetNext(GameState_MainMenu);

    D_800B5C30 = 0x1000;
}

void open_main(s32 file_idx, s16 num_frames) // 0x801E2AA4
{
    Fs_QueueWaitForEmpty();
    if (!num_frames)
    {
        num_frames = g_FileTable[file_idx].blockCount - 7;
    }

    Gfx_ClearRectInterlaced(0, 16, 480, 480, 0, 0, 0);
    movie_main(NULL, num_frames, g_FileTable[file_idx].startSector);
    Gfx_ClearRectInterlaced(0, 16, 480, 480, 0, 0, 0);
    VSync(0);
    GsSwapDispBuff();
}

#ifdef NON_MATCHING
void movie_main(char* file_name, s32 f_size, s32 sector)
{
    CdlFILE file;
    CdlLOC loc;
    u8 param;
    s32 frame_no;
    s32 search_times;
    s_GameWork* temp_s2;
    s32 prev_frame_no;

    frame_cnt = 0;
    max_frame = f_size;
    
    m = (MOVIE_STR*)0x801A2600; // probably some kind of TEMP_MEMORY_ADDR define. Also used by b_konami.
    m->width  = SCRN_WIDTH;
    m->height = SCRN_HEIGHT;

    if (sector == 0)
    {
        search_times = 0;
        while (CdSearchFile(&file, file_name) == NULL)
		{
			if (search_times++ > 10000)
			{
				return;
			}
		}
		m->loc.minute = file.pos.minute;
		m->loc.second = file.pos.second;
		m->loc.sector = file.pos.sector;
    }
    else
    {
        CdIntToPos(sector, &m->loc);
	}

    strSetDefDecEnv(&m->dec, 0, 16, 0, 256);
    VSync(0);
    strInit(&m->loc, strCallback);

    while (strNextVlc(&m->dec) == NO_VALUE)
    {
        loc = file.pos;
        strKickCD(&loc);
    }

    SsSetSerialAttr(0, 0, 1);
    SsSetSerialVol(0, 80, 80);
    VSync(0);

    prev_frame_no = 0;
    temp_s2 = g_GameWorkPtr0;

    while (true)
    {
        // TODO: maybe this disp setup code is part of some inlined func? custom SetDefDispEnv?
        // DISPENV *SetDefDispEnv(DISPENV *env, int x, int y, int w, int h);
        // making a static inline setupDispEnv(DISPENV*, MOVIE_STR*, s_GameWork**) func got it very close
        // but still had register differences

        disp.disp.y   = 256 - (m->dec.rectid * SCRN_HEIGHT);
        disp.screen.x = temp_s2->field_1C;
        disp.screen.y = 8 + ((224 - m->height) / 2) + (temp_s2->field_1D);

        disp.disp.y = (disp.disp.y < 16) ? 16 : (disp.disp.y > 256) ? 256 : disp.disp.y;
        disp.screen.h = (disp.screen.h <= 0) ? 1 : (disp.screen.h > 208) ? 208 : disp.screen.h;
        
        PutDispEnv(&disp);
        nullsub_800334C8();
        JOY_Update();
        DecDCTin(m->dec.vlcbuf[m->dec.vlcid], 3);
        DecDCTout((u_long* ) m->dec.imgbuf, m->dec.slice.w * m->dec.slice.h / 2);

        while (strNextVlc(&m->dec) == NO_VALUE)
        {
            frame_no = StGetBackloc(&loc);
            if (max_frame < frame_no || frame_no <= 0)
            {
                loc = file.pos;
            }
            strKickCD(&loc);
        }

        if (frame_cnt >= max_frame)
            break;

        if (prev_frame_no > frame_cnt)
            break;
        
        prev_frame_no = frame_cnt;

        strSync(&m->dec);
        VSync(0);
        
        if ((g_ControllerPtr0->btns_new_10 & g_GameWorkPtr1->controllerBinds_0.skip))
            break;
        if (MainLoop_ShouldWarmReset() > 0)
            break;
    }
    SsSetSerialVol(0, 0, 0);
    param = 0x80;
    CdControlB(CdlSetmode, &param, NULL);
    CdControlB(CdlPause, NULL, NULL);
    StUnSetRing();
    DecDCToutCallback(NULL);
}
#else
INCLUDE_ASM("asm/screens/stream/nonmatchings/stream", movie_main);
#endif

void strSetDefDecEnv(DECENV* dec, s32 x0, s32 y0, s32 x1, s32 y1) // 0x801E2F8C
{
    dec->vlcbuf[0] = m->vlcbuf0;
    dec->vlcbuf[1] = m->vlcbuf1;
    dec->vlcid     = 0;
    dec->imgbuf    = m->imgbuf0;
    dec->rectid    = 0;
    dec->isdone    = 0;

    setRECT(&dec->rect[0], x0, y0, SCRN_WIDTH * PPW, SCRN_HEIGHT);
    setRECT(&dec->rect[1], x1, y1, SCRN_WIDTH * PPW, SCRN_HEIGHT);
    setRECT(&dec->slice, x0, y0, 16 * PPW, SCRN_HEIGHT);
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
        ;
    }

    while (!CdControl(CdlSeekL, loc, 0))
    {
        VSync(0);
    }

    while (!CdRead2(CdlModeStream | CdlModeSpeed | CdlModeRT | CdlModeSize1))
    {
        VSync(0);
    }
}

int strNextVlc(DECENV* dec) // 0x801E3298
{
    u_long* next, *strNext();

    u_long count = 2000;
    while ((next = strNext(dec)) == 0)
    {
        count--;
        if (!count)
        {
            return NO_VALUE;
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
    int       count = MOVIE_WAIT;

    while (StGetNext((u_long**)&addr, (u_long**)&sector))
    {
        if (--count == 0)
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
    volatile u_long count = WAIT_TIME;

    while (dec->isdone == 0)
    {
        if (--count == 0)
        {
            dec->isdone  = 1;
            dec->rectid  = dec->rectid ^ 1;
            dec->slice.x = dec->rect[dec->rectid].x;
            dec->slice.y = dec->rect[dec->rectid].y;
        }
    }

    dec->isdone = 0;
}
