#ifndef _OPTIONS_H
#define _OPTIONS_H

#include "common.h"

typedef struct _sub_801E2C74 {
    s8 field_0;
    s8 field_1;
    s8 field_2;
    s8 field_3;
    s8 field_4;
    s8 field_5;
    s8 field_6;
    s8 field_7;
    s8 field_8;
    s8 field_9;
    s8 field_A;
    s8 field_B;
} s_sub_801E2C74;

typedef struct _801E2C74
{
    s_sub_801E2C74 field_0[2];
} s_801E2C74;
STATIC_ASSERT_SIZEOF(s_801E2C74, 0x18);

extern s_801E2C74 D_801E2C74;

extern s_801E2C74 D_801E2C8C;

/** BGM Volume bar related. */
void func_801E3F68();

/** SFX Volume bar related. */
void func_801E3F90();

void func_801E3FB8(s32 arg0, s32 arg1);

void Gfx_DrawBrightnessLevelText();

void Gfx_DrawBrightnessLevelArrows();

extern char* D_801E2C64[]; // String: "LEVEL_________"

#endif
