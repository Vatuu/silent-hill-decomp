#ifndef _OPTIONS_H
#define _OPTIONS_H

#include "common.h"

typedef enum _BindingMenu
{
    BindingMenu_Exit = 0,
    BindingMenu_Type_1,
    BindingMenu_Type_2,
    BindingMenu_Type_3
} e_BindingMenu;

typedef enum _BindingAction
{
    BindingAction_Enter = 0,
    BindingAction_Cancel,
    BindingAction_Skip,
    BindingAction_Action,
    BindingAction_Aim,
    BindingAction_Light,
    BindingAction_Run,
    BindingAction_View,
    BindingAction_Step_L,
    BindingAction_Step_R,
    BindingAction_Pause,
    BindingAction_Item,
    BindingAction_Map,
    BindingAction_Option
} e_BindingAction;

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
    e_BindingMenu   field_0;
    e_BindingAction field_4;
} s_801E73DC;

extern s32 D_801E72F4;

extern s32 D_801E72F8;

extern s32 D_801E72FC;

extern s32 D_801E7300;

extern s32 D_801E7304;

extern s32 D_801E7308;

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

void Gfx_BarDraw(s32 arg0, s32 arg1);

void Gfx_SettingsOptionsDraw();

void Gfx_BrightnessLevelTextDraw();

void Gfx_BrightnessLevelArrowsDraw();

void Gfx_ButtonDraw(s_ButtonVectors* vec, s32 arg1, s32 arg2);

void Gfx_LineDraw(s_LineVectors* vec, s32 arg1, s32 arg2);

void Gfx_ArrowDraw(s_ArrowVectors* arg0, s32 arg1, s32 arg2);

#endif
