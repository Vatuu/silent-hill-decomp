#ifndef _OPTIONS_H
#define _OPTIONS_H

#include "common.h"

/** @brief This header is used to declare any variable, struct, or
 * function part of `OPTIONS.BIN`.
 */
 
// ============
// ENUMERATORS
// ============

typedef enum _BindingMenu
{
    BindingMenu_Exit    = 0,
    BindingMenu_Type_1  = 1,
    BindingMenu_Type_2  = 2,
    BindingMenu_Type_3  = 3,
    BindingMenu_Actions = -1,
    BindingMenu_Leave   = -2
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
    InputAction_Count  = 14
} e_InputAction;

typedef enum _OptionsMain
{
    OptMain_Exit       = 0,
    OptMain_Brightness = 1,
    OptMain_Controller = 2,
    OptMain_ScreenPos  = 3,
    OptMain_Vibration  = 4,
    OptMain_AutoLoad   = 5,
    OptMain_Sound      = 6,
    OptMain_BGMVol     = 7,
    OptMain_SFXVol     = 8
} e_OptionsMain;

typedef enum _OptionsExtra
{
    OptExtra_WeaponCtrl   = 0,
    OptExtra_Blood        = 1,
    OptExtra_ViewCtrl     = 2,
    OptExtra_RetreatTurn  = 3,
    OptExtra_MovementCtrl = 4,
    OptExtra_AutoAiming   = 5,
    OptExtra_ViewMode     = 6,
    OptExtra_BulletMult   = 7
} e_OptionsExtra;

// ========
// STRUCTS
// ========

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

typedef struct _ScreenCtrl_SelectedElement
{
    e_BindingMenu menuIdx_0;
    e_InputAction actionIdx_4;
} s_ScreenCtrl_SelectedElement;

// ========
// GLOBALS
// ========

extern s32 g_MainSelectedOptionIdx;

extern s32 g_ExtraSelectedOptionIdx;

/** @brief Both `g_PrevMainSelectedOptionIdx` and
`g_PrevExtraSelectedOptionIdx` are being constantly
updated so it may not appear at first glance that
they hold the previous selected option, but looking
at the way they are used and the fact that it updates
onces `Gfx_LineDraw` finish confirm this.
*/
extern s32 g_PrevMainSelectedOptionIdx;

extern s32 g_PrevExtraSelectedOptionIdx;

extern s32 g_Gfx_ScreenPos_InvertColorBg;

extern s32 g_ScreenCtrl_IsOverActions;

extern DR_MODE D_801E730C[2];

extern POLY_G4 D_801E7324[2];

extern char* g_ScreenCtrl_Options[];

extern char* g_ScreenCtrl_Actions[];

extern DVECTOR D_801E73B4;

extern DVECTOR D_801E73B8;

extern DVECTOR D_801E73BC;

extern DVECTOR D_801E73C0;

extern DVECTOR D_801E73C4;

extern DVECTOR D_801E73C8;

extern DVECTOR D_801E73CC;

extern DVECTOR D_801E73D0;

extern s32 g_Gfx_ScreenPos_InvertColorBg_TransitionCounter;

extern s16 g_ScreenPos_PosX;

extern s_ScreenCtrl_SelectedElement g_ScreenCtrl_SelectedElement;

extern s16 g_ScreenPos_PosY;

extern s32 g_Gfx_MoveLineTimer;

/** @brief Defines the amount of options to
show in the extra options screen.
Used to show extra unlockable settings in
case the player has them unlocked.
*/
extern s32 g_OptExtra_ShowSettingsCount;

extern s32 g_OptExtra_BloodColorSelected;

extern s32 g_OptExtra_BulletMultLimit;

// ==========
// FUNCTIONS
// ==========

void GameState_OptionScreen_Update();

void Settings_ExtraScreen();

void Settings_MainScreen();

void Gfx_BgmBarDraw();

void Gfx_SfxBarDraw();

/** @brief Generates and draws the bars used for SFX and BGM audio options. */
void Gfx_BarDraw(s32 arg0, u8 arg1);

/** @brief Draws the option strings in the extra options screen. */
void Gfx_OptionsStringsExtraDraw();

/** @brief Draws the option strings in the main options screen. */
void Gfx_OptionsStringsMainDraw();

/** @brief Draws the buttons next to options and lines indicating the
 * selected option in the extra options screen.
 */
void Gfx_SelectedOptionExtra();

/** @brief Draws the buttons next to options and lines indicating the
 * selected option in the main options screen.
 */
void Gfx_SelectedOptionMain();

/** @brief Draws the vignette for the main and extra options screens. */
void Gfx_VignetteDraw();

/** @brief Draws the options for each setting used in the main options screen. */
void Gfx_SettingsOptionsMainDraw();

void Settings_PositionScreen();

void Gfx_PositionArrowsDraw();

/** @brief Draws the box that indicates the screen position in the
 * position screen configuration.
 */
void Gfx_PositionIndicatorDraw();

void Settings_BrightnessScreen();

void Gfx_BrightnessLevelTextDraw();

void Gfx_BrightnessLevelArrowsDraw();

/** @brief Draws the line on the selected option in options screens. */
void Gfx_LineDraw(s_LineVectors* vec, s32 arg1, s32 arg2);

/** @brief Draws the arrows used in options screens. */
void Gfx_ArrowDraw(s_ArrowVectors* vec, s32 arg1, s32 arg2);

/** @brief Draws the button next to options in the main and extra option screens. */
void Gfx_ButtonDraw(s_ButtonVectors* vec, s32 arg1, s32 arg2);

void Settings_ControllerScreen();

/** @brief Changes the button mapping based on the input. */
s32 Settings_ButtonChange(s32 actionIdx);

void Gfx_ControllerScreenDraw(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

void Gfx_ControllerButtonsDraw(s32 arg0, s32 arg1, u16 arg2);

#endif