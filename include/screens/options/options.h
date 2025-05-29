#ifndef _OPTIONS_H
#define _OPTIONS_H

#include "common.h"

typedef enum _BindingMenu
{
    BindingMenu_Exit   = 0,
    BindingMenu_Type_1 = 1,
    BindingMenu_Type_2 = 2,
    BindingMenu_Type_3 = 3
} e_BindingMenu;

typedef enum _InputAction
{
    InputAction_Enter  = 0,
    InputAction_Cancel = 1,
    InputAction_Skip   = 2,
    InputAction_Action = 3,
    InputAction_Aim    = 4,
    InputAction_Light  = 5,
    InputAction_Run    = 6,
    InputAction_View   = 7,
    InputAction_StepL  = 8,
    InputAction_StepR  = 9,
    InputAction_Pause  = 10,
    InputAction_Item   = 11,
    InputAction_Map    = 12,
    InputAction_Option = 13,

    InputAction_Count = 14
} e_InputAction;

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

typedef struct
{
    e_BindingMenu menuIdx_0;
    e_InputAction actionIdx_4;
} s_801E73DC;

extern s32 D_801E72F4;

extern s32 D_801E72F8;

extern s32 D_801E72FC;

extern s32 D_801E7300;

extern s32 D_801E7304;

extern s32 D_801E7308;

extern DR_MODE D_801E730C[2];

extern POLY_G4 D_801E7324[2];

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

extern s32 D_801E73D4;

extern s16 D_801E73D8;

extern s_801E73DC D_801E73DC;

extern s16 D_801E73DA;

extern s32 D_801E73E4;

extern s32 D_801E73E8;

extern s32 D_801E73EC;

extern s32 D_801E73F0;

void Gfx_BGMBarDraw();

void Gfx_SFXBarDraw();

void Gfx_BarDraw(s32 arg0, u8 arg1);

void Gfx_SettingsOptionsDraw();

void Gfx_BrightnessLevelTextDraw();

void Gfx_BrightnessLevelArrowsDraw();

void Gfx_ButtonDraw(s_ButtonVectors* vec, s32 arg1, s32 arg2);

void Gfx_LineDraw(s_LineVectors* vec, s32 arg1, s32 arg2);

void Gfx_ArrowDraw(s_ArrowVectors* arg0, s32 arg1, s32 arg2);

#endif
