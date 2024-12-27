#include "common.h"
#include "game.h"
#include "main/fsqueue.h"
#include "bodyprog/bodyprog.h"
#include "gpu.h"
#include <LIBAPI.H>
#include <LIBETC.H>
#include <LIBCD.H>
#include <LIBSND.H>

#define FILE_1ST_2ZANKO_E_TIM 1 // "\\1ST\\2ZANKO_E.TIM"
#define FILE_1ST_BODYPROG_BIN 3 // "\\1ST\\BODYPROG.BIN"
#define FILE_1ST_B_KONAMI_BIN 4 // "\\1ST\\B_KONAMI.BIN"
#define FILE_1ST_FONT8NOC_TIM 7 // "\\1ST\\FONT8NOC.TIM"

extern DISPENV g_MainDispEnv;
extern DRAWENV g_MainDrawEnv;

// @HACK: explicit rodata here because these need to be referenced externally to end up in .rodata,
// otherwise they'll go into .sdata because they're small; can't wrap them in a struct either because
// main() accesses them individually and not with a single base
void * SECTION(".rodata") g_OvlDynamic = (void *)0x800C9578;
void * SECTION(".rodata") g_OvlBodyprog = (void *)0x80024B60;

FsImageDesc g_MainImg0 = {
  .tpage = 0x0d01,
  .u = 32,
  .v = 0,
  .clut_x = 768,
  .clut_y = 480
};

FsImageDesc g_MainImg1 = {
  .tpage = 0x1400,
  .u = 0,
  .v = 240,
  .clut_x = 0,
  .clut_y = 0
};

s32 g_MainFbIdx = 0;

int main(void) {
  s16 ofs_y;
  s32 fb_next;
  s32 i;
  s32 sprt_x;
  s32 fade;
  DR_TPAGE *tpage;
  u8 *prim;

  ResetCallback();
  CdInit();
  fsQueueInit();
  VSync(0);
  ResetGraph(3);

  // clear framebuffer area of VRAM
  // @NOTE: this and other GPU macros here are custom to ensure a match
  SET_RECT(PSX_SCRATCH, 0, 0, 640, 512);
  VSync(0);
  ClearImage2(PSX_SCRATCH, 0, 0, 0);
  DrawSync(0);

  // display area = (0, 0, 320, 240)
  PutDispEnv(&g_MainDispEnv);

  // init SPU (should probably be called SpuInit because all it does is call _SpuInit)
  SsUtReverbOff();

  // load \1ST\2ZANKO_E.TIM ("There are violent and disturbing images...")
  fsQueueStartReadTim(FILE_1ST_2ZANKO_E_TIM, FS_BUFFER0, &g_MainImg0);
  while (fsQueueGetLength() > 0) {
    fsQueueUpdate();
    VSync(0);
  }

  // start loading \1ST\BODYPROG.BIN
  fsQueueStartRead(FILE_1ST_BODYPROG_BIN, FS_BUFFER0);
  // start loading \1ST\B_KONAMI.BIN
  fsQueueStartRead(FILE_1ST_B_KONAMI_BIN, FS_BUFFER1);

  SetDispMask(1);

  // fade in 2ZANKO_E.TIM over 64 frames using a TILE with subtractive blending
  fade = 0xFF;
  tpage = prim = PSX_SCRATCH;
  while (true) {
    g_MainDispEnv.disp.y = 256 - (g_MainFbIdx * 224);
    PutDispEnv(&g_MainDispEnv);

    if (fade < 0) {
      break;
    }

    // swap buffers
    fb_next = g_MainFbIdx == 0;
    ofs_y = 256 - (fb_next * 224);
    g_MainFbIdx = fb_next;
    g_MainDrawEnv.ofs[1] = ofs_y; // draw Y offset
    g_MainDrawEnv.clip.y = ofs_y;
    PutDrawEnv(&g_MainDrawEnv);

    // draw the image as a series of 128x256 SPRTs
    for (i = 0, sprt_x = -64; i < 3; sprt_x += 128, i++) {
      setlen(prim, 1);
      ((DR_TPAGE *)prim)->code[0] = (((i + 13) & 0xF) | 0xE1000280);
      DrawPrim(prim);
      setlen(prim, 4);
      *(u32*)(prim + 0x04) = 0x64808080;
      *(s16*)(prim + 0x10) = 0x100;
      *(s16*)(prim + 0x12) = 0x100;
      *(u32*)(prim + 0x08) = ((sprt_x & 0xFFFF) + 0xFFF80000);
      *(u32*)(prim + 0x0C) = (((g_MainImg0.clut_y << 6) | (((u16) g_MainImg0.clut_x >> 4) & 0x3F)) << 0x10);
      DrawPrim(prim);
    }

    // subtractive blending
    setlen(prim, 1);
    ((DR_TPAGE *)prim)->code[0] = 0xE1000240;
    DrawPrim(prim);

    // draw fullscreen tile
    setlen(prim, 3);
    setcode(prim, 0x62);
    *(u8* )(prim + 0x04) = fade;
    *(u8* )(prim + 0x05) = fade;
    *(u8* )(prim + 0x06) = fade;
    *(u32*)(prim + 0x0C) = 0xF00280; // 320x240
    *(u32*)(prim + 0x08) = 0;
    DrawPrim(prim);

    fade -= 4;

    // keep loading files in the meantime
    fsQueueUpdate();
    VSync(0);
  }

  // if files haven't loaded yet, wait until they do
  while (fsQueueGetLength() > 0) {
    fsQueueUpdate();
    VSync(0);
  }

  // decrypt BODYPROG and B_KONAMI into place
  fsDecryptOverlay(g_OvlBodyprog, FS_BUFFER0, fsFileGetSize(FILE_1ST_BODYPROG_BIN));
  fsDecryptOverlay(g_OvlDynamic, FS_BUFFER1, fsFileGetSize(FILE_1ST_B_KONAMI_BIN));

  // load 1ST\FONT8NOC.TIM (8x8 font)
  fsQueueStartReadTim(FILE_1ST_FONT8NOC_TIM, FS_BUFFER1, &g_MainImg1);
  while (fsQueueGetLength() > 0) {
    fsQueueUpdate();
    VSync(0);
  }

  // fade the image back out?
  func_800314EC(&g_MainImg0);

  // enter BODYPROG
  func_80032EE0();

  return 0;
}
