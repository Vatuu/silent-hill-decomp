#include "game.h"

#include <libetc.h>
#include <libds.h>
#include <libpress.h>

#include "bodyprog/bodyprog.h"
#include "bodyprog/gfx/screen_draw.h"
#include "bodyprog/gfx/text_draw.h"
#include "bodyprog/joy.h"
#include "bodyprog/libsd.h"
#include "bodyprog/math/math.h"
#include "main/fileinfo.h"
#include "screens/stream/stream.h"

void GameState_StartMovieIntro_Update() // 0x801E2654
{
    switch (g_GameWork.gameStateStep_598[0])
    {
        case 0:
            VSync(8);
            g_Gfx_ScreenFade = SCREEN_FADE_STATUS(ScreenFadeState_FadeInStart, false);
            GameFs_TitleGfxLoad();
            g_GameWork.gameStateStep_598[0]++;
            break;

        case 1:
            if (g_Controller0->btnsHeld_C != 0 || g_SysWork.timer_1C > 300)
            {
                g_Gfx_ScreenFade                = SCREEN_FADE_STATUS(ScreenFadeState_FadeOutSteps, false);
                g_GameWork.gameStateStep_598[0] = 2;
            }
            break;

        case 2:
            if (Gfx_IsScreenFadeComplete())
            {
                Fs_QueueWaitForEmpty();
                Game_StateSetNext(GameState_MovieIntro);
            }
            break;
    }

    Gfx_BackgroundSpriteDraw(D_800A900C);
}

void GameState_MovieIntro_Update() // 0x801E279C
{
    s32 fileIdx = FILE_XA_C1_20670;

    if (g_GameWorkConst->config_0.optExtraOptionsEnabled_27 & (1 << 0))
    {
        fileIdx = FILE_XA_C2_20670;
    }

    open_main(fileIdx, 0);
    Game_StateSetNext(GameState_MainMenu);

    g_ScreenFadeTimestep = FP_TIME(1.0f);
}

void GameState_MovieOpening_Update() // 0x801E2838
{
    open_main(FILE_XA_M1_03500, 0);
    Game_StateSetNext(GameState_MainLoadScreen);
}

void GameState_ExitMovie_Update() // 0x801E28B0
{
    Game_StateSetNext(GameState_InGame);
}

void GameState_DebugMoviePlayer_Update() // 0x801E2908
{
    static s32 g_Debug_MoviePlayerIdx = 0; // 0x801E3F3C

    if (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.cancel_2)
    {
        Game_StateSetNext(GameState_Unk16); // Changes to non-existent state 22 and crashes. Maybe removed debug menu.
    }

    if (g_Controller0->btnsPulsed_18 & ControllerFlag_LStickLeft)
    {
        g_Debug_MoviePlayerIdx--;
    }

    if (g_Controller0->btnsPulsed_18 & ControllerFlag_LStickRight)
    {
        g_Debug_MoviePlayerIdx++;
    }

    Gfx_DebugStringPosition(SCREEN_POSITION_X(12.5f), SCREEN_POSITION_Y(16.75f));

#ifdef DEBUG
    // Recreated code from pre-Jan17 builds which include calls to display these (though `Gfx_DebugStringDraw` was nullsub in those builds).
    Gfx_DebugStringDraw("MOVIE NO=");
    Gfx_DebugStringDraw(Math_IntegerToString(2, g_Debug_MoviePlayerIdx));
#endif

    if (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.enter_0)
    {
        open_main(FILE_XA_ZC_14392 - g_Debug_MoviePlayerIdx, 0);
    }
}

void GameState_MovieIntroAlternate_Update() // 0x801E2A24
{
    open_main(FILE_XA_C1_20670, 2060); // Second param looks like file ID for `FILE_XA_M6_02112`, but is actually frame count?
    Game_StateSetNext(GameState_MainMenu);

    g_ScreenFadeTimestep = FP_TIME(1.0f);
}

s32 max_frame = 0; // 0x801E3F40
s32 frame_cnt = 0; // 0x801E3F44

DISPENV disp =
{
    { 0, 256, 320, 240 }, // `disp`
    { 0, 8,   256, 208 }, // `screen`
    0,                    // `isinter`
    1,                    // `isrgb24`
    0,                    // `pad0`
    0                     // `pad1`
}; // 0x801E3F48

MOVIE_STR* m;

void open_main(s32 file_idx, s16 num_frames) // 0x801E2AA4
{
    Fs_QueueWaitForEmpty();
    if (!num_frames)
    {
        num_frames = g_FileTable[file_idx].blockCount_0_19 - 7;
    }

    Screen_ClearRectInterlaced(0, 16, 480, 480, FP_COLOR(0.0f), FP_COLOR(0.0f), FP_COLOR(0.0f));
    movie_main(NULL, num_frames, g_FileTable[file_idx].startSector_0_0);
    Screen_ClearRectInterlaced(0, 16, 480, 480, FP_COLOR(0.0f), FP_COLOR(0.0f), FP_COLOR(0.0f));
    VSync(0);
    GsSwapDispBuff();
}

void movie_main(char* file_name, s32 f_size, s32 sector) // 0x801E2B9C
{
    #define SEARCH_COUNT_MAX 10000

    CdlFILE file;
    CdlLOC  loc;
    u8      param;
    s32     frame_no;
    s32     search_times;
    s32     prev_frame_no;

    frame_cnt = 0;
    max_frame = f_size;

    m         = (MOVIE_STR*)TEMP_MEMORY_ADDR;
    m->width  = SCREEN_WIDTH;
    m->height = SCREEN_HEIGHT;

    if (sector == 0)
    {
        search_times = 0;

        while (CdSearchFile(&file, file_name) == NULL)
        {
            if (search_times++ > SEARCH_COUNT_MAX)
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

    do
    {
        disp.disp.y   = 256 - (m->dec.rectid * SCREEN_HEIGHT);
        disp.screen.x = g_GameWorkConst->config_0.optScreenPosX_1C;
        disp.screen.y = (8 + ((224 - m->height) / 2)) + g_GameWorkConst->config_0.optScreenPosY_1D;
        disp.disp.y   = (disp.disp.y   <  16) ? 16 : ((disp.disp.y > 256)   ? 256 : disp.disp.y);
        disp.screen.h = (disp.screen.h <= 0)  ? 1  : ((disp.screen.h > 208) ? 208 : disp.screen.h);

        PutDispEnv(&disp);
        nullsub_800334C8();
        Joy_Update();
        DecDCTin(m->dec.vlcbuf[m->dec.vlcid], 3);
        DecDCTout((u_long*)m->dec.imgbuf, m->dec.slice.w * m->dec.slice.h / 2);

        while (strNextVlc(&m->dec) == NO_VALUE)
        {
            frame_no = StGetBackloc((DslLOC*)&loc);
            if (max_frame < frame_no || frame_no <= 0)
            {
                loc = file.pos;
            }

            strKickCD(&loc);
        }

        if (frame_cnt >= max_frame || prev_frame_no > frame_cnt)
        {
            break;
        }

        prev_frame_no = frame_cnt;

        strSync(&m->dec);
        VSync(0);
    }
    while (!(g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.skip_4) && MainLoop_ShouldWarmReset() <= 0);

    SsSetSerialVol(0, 0, 0);

    param = CdlModeSpeed;
    CdControlB(CdlSetmode, &param, 0);
    CdControlB(CdlPause, NULL, NULL);

    StUnSetRing();
    DecDCToutCallback(NULL);
}

void strSetDefDecEnv(DECENV* dec, s32 x0, s32 y0, s32 x1, s32 y1) // 0x801E2F8C
{
    dec->vlcbuf[0] = m->vlcbuf0;
    dec->vlcbuf[1] = m->vlcbuf1;
    dec->vlcid     = 0;
    dec->imgbuf    = m->imgbuf0;
    dec->rectid    = 0;
    dec->isdone    = 0;

    setRECT(&dec->rect[0], x0, y0, SCREEN_WIDTH * PPW, SCREEN_HEIGHT);
    setRECT(&dec->rect[1], x1, y1, SCREEN_WIDTH * PPW, SCREEN_HEIGHT);
    setRECT(&dec->slice, x0, y0, 16 * PPW, SCREEN_HEIGHT);
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

    while (!CdControlB(CdlNop, 0, v2) || (v2[0] & (1 << 1)) == 0)
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
    #define COUNT_MAX 2000

    u_long* next;

    u_long count = COUNT_MAX;
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
