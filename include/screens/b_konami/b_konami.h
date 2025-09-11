#ifndef _SCREENS_B_KONAMI_H
#define _SCREENS_B_KONAMI_H

#include "common.h"

typedef struct
{
    u8 field_0;
    u8 field_1;
    u8 field_2;
    u8 field_3;
} s_800CA4F0;

extern s_800CA4F0 D_800CA4F0;

extern u8* D_800CA4F4;

extern s32 D_800CA4F8;

extern s32 D_800CA4FC; // Boolean value

extern u8* D_800CA500;

extern u8* D_800CA504;

extern s32 D_800CA508;

extern u8* D_800CA50C;

extern s32 D_800CA510;

/** Displays the Konami logo and starts loading base hero animations. */
void GameState_KonamiLogo_Update();

s32 func_800C9874();

/** Displays the KCET logo and starts loading various things. */
void GameState_KcetLogo_Update();

/** Draws segments of Konami and KCET logos. */
void Gfx_BootScreenImageSegmentDraw(s_FsImageDesc* image, s32 otz, s32 vramX, s32 vramY, s32 w, s32 h, s32 x, s32 y);

void Gfx_KonamiScreenDraw();

void Gfx_KcetScreenDraw();

void func_800CA234();

s32 func_800CA240(s32* arg0);

void func_800CA24C(s32 arg0, s32 arg1, s32 arg2);

s32 func_800CA2B8();

void func_800CA2C8(s32 arg0);

#endif
