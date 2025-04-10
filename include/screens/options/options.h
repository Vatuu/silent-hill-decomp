#ifndef _OPTIONS_H
#define _OPTIONS_H

#include "common.h"

typedef struct
{
    s16 field_0;
    s16 field_2;
    s16 field_4;
    s16 field_6;
    s16 field_8;
    s16 field_A;
} s_sub_801E2C74;

typedef struct
{
    s_sub_801E2C74 field_0[2];
} s_801E2C74;
STATIC_ASSERT_SIZEOF(s_801E2C74, 24);

extern s_801E2C74 D_801E2C74;

extern s_801E2C74 D_801E2C8C;

void Gfx_BGMBarDraw();

void Gfx_SFXBarDraw();

void Gfx_BarDraw(s32 arg0, s32 arg1);

void Gfx_SettingsOptionsDraw();

void Gfx_BrightnessLevelTextDraw();

void Gfx_BrightnessLevelArrowsDraw();

#endif
