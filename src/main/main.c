#include "common.h"
#include "game.h"
#include "main/fsqueue.h"
#include "bodyprog/bodyprog.h"
#include "gpu.h"

#include <libapi.h>
#include <libetc.h>
#include <libcd.h>
#include <libsnd.h>

#define FILE_1ST_2ZANKO_E_TIM 1 // "\\1ST\\2ZANKO_E.TIM"
#define FILE_1ST_BODYPROG_BIN 3 // "\\1ST\\BODYPROG.BIN"
#define FILE_1ST_B_KONAMI_BIN 4 // "\\1ST\\B_KONAMI.BIN"
#define FILE_1ST_FONT8NOC_TIM 7 // "\\1ST\\FONT8NOC.TIM"

// @HACK: Explicit rodata here because these need to be referenced externally to end up in .rodata,
// otherwise they'll go into .sdata because they're small; can't wrap them in a struct either because
// main() accesses them individually and not with a common base.
void* SECTION(".rodata") g_OvlDynamic = (void*)0x800C9578;
void* SECTION(".rodata") g_OvlBodyprog = (void*)0x80024B60;

s_FsImageDesc g_MainImg0 =
{
    .tPage = 0x0d01,
    .u     = 32,
    .v     = 0,
    .clutX = 768,
    .clutY = 480
};

s_FsImageDesc g_MainImg1 =
{
    .tPage = 0x1400,
    .u     = 0,
    .v     = 240,
    .clutX = 0,
    .clutY = 0
};

s32 g_MainFbIdx = 0;

DISPENV g_MainDispEnv =
{
    .disp   = { 0, 0, 320, 240 },
    .screen = { 0, 8, 256, 224 }
};

DRAWENV g_MainDrawEnv =
{
    .clip = { 0, 0, 320, 224 },
    .dtd  = 1,
    .isbg = 1
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
    Fs_InitializeQueue();
    VSync(0);
    ResetGraph(3);

    // Clear framebuffer area of VRAM.
    // @NOTE: This and some other GPU macros here are custom to ensure a match.
    setRECTFast((RECT*)PSX_SCRATCH, 0, 0, 640, 512);
    VSync(0);
    ClearImage2((RECT*)PSX_SCRATCH, 0, 0, 0);
    DrawSync(0);

    // Display area = (0, 0, 320, 240)
    PutDispEnv(&g_MainDispEnv);

    // Initialize SPU (should probably be called SpuInit because all it does is call _SpuInit).
    SsUtReverbOff();

    // Load \1ST\2ZANKO_E.TIM ("There are violent and disturbing images...").
    Fs_StartQueueReadTim(FILE_1ST_2ZANKO_E_TIM, FS_BUFFER0, &g_MainImg0);
    while (Fs_GetQueueLength() > 0)
    {
        Fs_UpdateQueue();
        VSync(0);
    }

    // Start loading \1ST\BODYPROG.BIN and \1ST\B_KONAMI.BIN.
    Fs_StartQueueRead(FILE_1ST_BODYPROG_BIN, FS_BUFFER0);
    Fs_StartQueueRead(FILE_1ST_B_KONAMI_BIN, FS_BUFFER1);

    SetDispMask(1);

    // Fade in 2ZANKO_E.TIM over 64 frames using TILE with subtractive blending.
    fade = 0xFF;
    prim = PSX_SCRATCH;
    while (true)
    {
        g_MainDispEnv.disp.y = 256 - (g_MainFbIdx * 224);
        PutDispEnv(&g_MainDispEnv);

        if (fade < 0)
        {
            break;
        }

        // Swap buffers.
        fbNext = (g_MainFbIdx == 0);
        offsetY = 256 - (fbNext * 224);
        g_MainFbIdx = fbNext;
        g_MainDrawEnv.ofs[1] = offsetY; // Draw Y offset.
        g_MainDrawEnv.clip.y = offsetY;
        PutDrawEnv(&g_MainDrawEnv);

        // Draw image as series of 128x256 SPRTs.
        for (i = 0, sprtX = -64; i < 3; sprtX += 128, i++)
        {
            setDrawTPage((DR_TPAGE*)prim, 0, 1, getTPageN(1, 0, i + 13, 0));
            DrawPrim((DR_TPAGE*)prim);
            setlen((SPRT*)prim, 4);
            setCodeWord((SPRT*)prim, PRIM_RECT | RECT_TEXTURE, 0x808080); // setSprt(); setRGB0();
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
        setcode((TILE*)prim, PRIM_RECT | RECT_BLEND); // setTile(); setSemiTrans();
        setRGB0((TILE*)prim, fade, fade, fade);
        setWHFast((TILE*)prim, 640, 240);
        setXY0Fast((TILE*)prim, 0, 0);
        DrawPrim((TILE*)prim);

        fade -= 4;

        // Keep loading files in meantime.
        Fs_UpdateQueue();
        VSync(0);
    }

    // If files haven't loaded yet, wait until they do.
    while (Fs_GetQueueLength() > 0)
    {
        Fs_UpdateQueue();
        VSync(0);
    }

    // Decrypt BODYPROG and B_KONAMI into place.
    Fs_DecryptOverlay(g_OvlBodyprog, FS_BUFFER0, Fs_GetFileSize(FILE_1ST_BODYPROG_BIN));
    Fs_DecryptOverlay(g_OvlDynamic, FS_BUFFER1, Fs_GetFileSize(FILE_1ST_B_KONAMI_BIN));

    // Load 1ST\FONT8NOC.TIM (8x8 font).
    Fs_StartQueueReadTim(FILE_1ST_FONT8NOC_TIM, FS_BUFFER1, &g_MainImg1);
    while (Fs_GetQueueLength() > 0)
    {
        Fs_UpdateQueue();
        VSync(0);
    }

    // Fade image back out?
    func_800314EC(&g_MainImg0);

    // Enter BODYPROG.
    func_80032EE0();

    return 0;
}
