#include "game.h"
#include "main/fsqueue.h"
#include <LIBGTE.H>
#include <LIBGPU.H>

// @HACK: explicit rodata here because these need to be referenced externally to end up in .rodata,
// otherwise they'll go into .sdata because they're small; can't wrap them in a struct either because
// main() accesses them individually and not with a single base
void *const SECTION(".rodata") g_OvlDynamic = (void *)0x800C9578;
void *const SECTION(".rodata") g_OvlBodyprog = (void *)0x80024B60;

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

extern DISPENV g_MainDispEnv;
extern DRAWENV g_MainDrawEnv;

INCLUDE_ASM("asm/main/nonmatchings/main", main);
