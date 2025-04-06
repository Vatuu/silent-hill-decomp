#ifndef _B_KONAMI_H
#define _B_KONAMI_H

#include "common.h"

#define BOOT_ADDR_0 ((u8*)0x801E09E0)
#define BOOT_ADDR_1 ((u8*)0x801E1430)

extern s32 D_800CA4F4;

extern s32 D_800CA4FC;

extern s32 D_800CA500;

extern s32 D_800CA504;

extern s32 D_800CA508;

extern s32 D_800CA50C;

extern s32 D_800CA510;

void func_800C9E6C(s_FsImageDesc* image, s32 otz, s16 vramX, s16 vramY, s16 w, s16 h, s16 x, s16 y);

/** Display Konami logo and start loading base hero animations. */
void func_800C95AC();

s32 func_800C9874();

void func_800C9FB8();

void func_800CA120();

void func_800CA234();

s32  func_800CA240(s32* arg0);

void func_800CA24C(s32 arg0, s32 arg1, s32 arg2);

s32  func_800CA2B8();

#endif
