#ifndef _OPTIONS_H
#define _OPTIONS_H

#include "common.h"

typedef struct
{
    DVECTOR field_0;
    DVECTOR field_4;
} s_LineVectors;

typedef struct
{
    DVECTOR field_0;
    DVECTOR field_4;
    DVECTOR field_8;
    DVECTOR field_C;
} s_ButtonVectors;

typedef struct
{
    DVECTOR field_0;
    DVECTOR field_4;
    DVECTOR field_8;
} s_ArrowVectors;

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

extern s32 D_801E72F4;

extern s32 D_801E72F8;

extern s32 D_801E72FC;

extern s32 D_801E7300;

extern DVECTOR D_801E73B4;

extern DVECTOR D_801E73B8;

extern DVECTOR D_801E73BC;

extern DVECTOR D_801E73C0;

extern DVECTOR D_801E73C4;

extern DVECTOR D_801E73C8;

extern DVECTOR D_801E73CC;

extern DVECTOR D_801E73D0;

extern s32 D_801E73E4;

extern s32 D_801E73E8;

extern s32 D_801E73EC;

extern s32 D_801E73F0;

void Gfx_BGMBarDraw();

void Gfx_SFXBarDraw();

void Gfx_BarDraw(s32 arg0, s32 arg1);

void Gfx_SettingsOptionsDraw();

void Gfx_BrightnessLevelTextDraw();

void Gfx_BrightnessLevelArrowsDraw();

void Gfx_ButtonDraw(s_ButtonVectors* vec, s32 arg1, s32 arg2);

void Gfx_LineDraw(s_LineVectors* vec, s32 arg1, s32 arg2);

void Gfx_ArrowDraw(s_ArrowVectors* arg0, s32 arg1, s32 arg2);

#endif
