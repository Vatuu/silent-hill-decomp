#ifndef _OPTIONS_H
#define _OPTIONS_H

#include "common.h"

typedef struct _LineVectors
{
    DVECTOR field_0;
    DVECTOR field_4;
} s_LineVectors;

typedef struct _ButtonVectors
{
    DVECTOR field_0;
    DVECTOR field_4;
    DVECTOR field_8;
    DVECTOR field_C;
} s_ButtonVectors;

typedef struct _ArrowVectors
{
    DVECTOR field_0;
    DVECTOR field_4;
    DVECTOR field_8;
} s_ArrowVectors;

extern s32 D_801E72F4;

extern s32 D_801E72F8;

extern s32 D_801E72FC;

extern s32 D_801E7300;

extern DR_MODE D_801E730C[];

extern POLY_G4 D_801E7324[];

extern char* D_801E736C[];

extern char* D_801E737C[];

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
