#include "common.h"
#include "game.h"

#include <psyq/libapi.h>
#include <psyq/libetc.h>
#include <psyq/libcd.h>
#include <psyq/libsnd.h>
#include <psyq/libspu.h>

#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "main/fsqueue.h"

// @hack Explicit rodata here because these need to be referenced externally to end up in .rodata,
// otherwise they'll go into .sdata because they're small; can't wrap them in a struct either because
// `main` accesses them individually and not with a common base.

#ifdef VER_JAP0
    void* SECTION(".rodata") g_OvlDynamic = (void*)0x800CBAA8;
#else
    void* SECTION(".rodata") g_OvlDynamic = (void*)0x800C9578;
#endif

void* SECTION(".rodata") g_OvlBodyprog = (void*)0x80024B60;

s_FsImageDesc g_MainImg0 = {
    .tPage = { 1, 13 },
    .u     = 32,
    .v     = 0,
    .clutX = 768,
    .clutY = 480
};

s_FsImageDesc g_MainImg1 = {
    .tPage = { 0, 20 },
    .u     = 0,
    .v     = 240,
    .clutX = 0,
    .clutY = 0
};

s32 g_MainFbIdx = 0;

DISPENV g_MainDispEnv = {
    .disp   = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT  },
    .screen = { 0, 8, 256,          224            }
};

DRAWENV g_MainDrawEnv = {
    .clip = { 0, 0, SCREEN_WIDTH, 224 },
    .dtd  = true,
    .isbg = true
};

int main(void)
{
    s16 offsetY;
    s32 fbNext;
    s32 i;
    s32 sprtX;
    s32 fade;
    u8* prim;

    ResetCallback();
    CdInit();
    Fs_QueueInitialize();
    VSync(SyncMode_Wait);
    ResetGraph(3);

    // Clear framebuffer area of VRAM.
    // NOTE: This and some other GPU macros here are custom to ensure a match.
    setRECTFast((RECT*)PSX_SCRATCH, 0, 0, SCREEN_WIDTH * 2, 512);
    VSync(SyncMode_Wait);
    ClearImage2((RECT*)PSX_SCRATCH, 0, 0, 0);
    DrawSync(SyncMode_Wait);

    // Display area = (0, 0, SCREEN_WIDTH, SCREEN_HEIGHT)
    PutDispEnv(&g_MainDispEnv);

    // Initialize SPU.
    SpuInit();

    // Load `1ST/2ZANKO_E.TIM` ("There are violent and disturbing images...").
#if defined(VERSION_NTSCJ)
    Fs_QueueStartReadTim(FILE_1ST_2ZANKO80_TIM, FS_BUFFER_0, &g_MainImg0);
#else
    Fs_QueueStartReadTim(FILE_1ST_2ZANKO_E_TIM, FS_BUFFER_0, &g_MainImg0);
#endif
    while (Fs_QueueGetLength() > 0)
    {
        Fs_QueueUpdate();
        VSync(SyncMode_Wait);
    }

    // Start loading `1ST/BODYPROG.BIN` and `1ST\B_KONAMI.BIN`.
    Fs_QueueStartRead(FILE_1ST_BODYPROG_BIN, FS_BUFFER_0);
    Fs_QueueStartRead(FILE_1ST_B_KONAMI_BIN, FS_BUFFER_1);

    SetDispMask(1);

    // Fade in `1ST/2ZANKO_E.TIM` over 64 frames using `TILE` with subtractive blending.
    fade = 255;
    prim = PSX_SCRATCH;
    while (true)
    {
        g_MainDispEnv.disp.y = 256 - (g_MainFbIdx * 224);
        PutDispEnv(&g_MainDispEnv);

        // Finished fading.
        if (fade < 0)
        {
            break;
        }

        // Swap buffers.
        fbNext               = g_MainFbIdx == 0;
        offsetY              = 256 - (fbNext * 224);
        g_MainFbIdx          = fbNext;
        g_MainDrawEnv.ofs[1] = offsetY; // Draw Y offset.
        g_MainDrawEnv.clip.y = offsetY;
        PutDrawEnv(&g_MainDrawEnv);

        // Draw image as series of 128x256 `SPRT`s.
        for (i = 0, sprtX = -64; i < 3; sprtX += 128, i++)
        {
            setDrawTPage((DR_TPAGE*)prim, 0, 1, getTPageN(1, 0, i + 13, 0));
            DrawPrim((DR_TPAGE*)prim);
            setlen((SPRT*)prim, 4);
            setCodeWord((SPRT*)prim, PRIM_RECT | RECT_TEXTURE, 0x808080); // `setSprt(); setRGB0();`
            setWH((SPRT*)prim, 256, 256);
            setXY0Fast((SPRT*)prim, sprtX, -8);
            setUV0AndClut((SPRT*)prim, 0, 0, g_MainImg0.clutX, g_MainImg0.clutY);
            DrawPrim((SPRT*)prim);
        }

        // Subtractive blending.
        setDrawTPage((DR_TPAGE*)prim, 0, 1, getTPageN(0, 2, 0, 0));
        DrawPrim((DR_TPAGE*)prim);

        // Draw blended fullscreen tile.
        setlen((TILE*)prim, 3);
        setcode((TILE*)prim, PRIM_RECT | RECT_BLEND); // `setTile(); setSemiTrans();`
        setRGB0((TILE*)prim, fade, fade, fade);
        setWHFast((TILE*)prim, SCREEN_WIDTH * 2, SCREEN_HEIGHT);
        setXY0Fast((TILE*)prim, 0, 0);
        DrawPrim((TILE*)prim);

        fade -= 4;

        // Keep loading files in meantime.
        Fs_QueueUpdate();
        VSync(SyncMode_Wait);
    }

    // If files haven't loaded yet, wait until they do.
    while (Fs_QueueGetLength() > 0)
    {
        Fs_QueueUpdate();
        VSync(SyncMode_Wait);
    }

    // Decrypt `BODYPROG` and `B_KONAMI` into place.
    Fs_DecryptOverlay(g_OvlBodyprog, FS_BUFFER_0, Fs_GetFileSize(FILE_1ST_BODYPROG_BIN));
    Fs_DecryptOverlay(g_OvlDynamic, FS_BUFFER_1, Fs_GetFileSize(FILE_1ST_B_KONAMI_BIN));

    // Load `1ST/FONT8NOC.TIM` (8x8 font atlas).
    Fs_QueueStartReadTim(FILE_1ST_FONT8NOC_TIM, FS_BUFFER_1, &g_MainImg1);
    while (Fs_QueueGetLength() > 0)
    {
        Fs_QueueUpdate();
        VSync(SyncMode_Wait);
    }

    // Fade image back out?
    Gfx_BackgroundSpriteDraw(&g_MainImg0);

    // Run main loop.
    MainLoop();

    return 0;
}
