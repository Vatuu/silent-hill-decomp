#ifndef _OPTIONS_H
#define _OPTIONS_H

#include "common.h"

/** @brief Header for `OPTIONS.BIN` declarations. */

// ======
// ENUMS
// ======

/** @brief Master options menu states.
 *
 * When the user navigates an options menu, this facilitates menu switching
 * via `s_GameWork::gameStateStep[0]`.
 */
typedef enum _OptMenuState
{
    OptMenuState_EnterMain       = 0,  /** Entering main options menu. */
    OptMenuState_Main            = 1,  /** In main options menu. */
    OptMenuState_ScreenPos       = 2,  /** In screen position submenu. */
    OptMenuState_Brightness      = 3,  /** In brightness submenu. */
    OptMenuState_Controller      = 4,  /** In controller binding submenu. */
    OptMenuState_LeaveMenu       = 5,  /** Leaving menu back to gameplay. */
    OptMenuState_LeaveMain       = 6,  /** Leaving main options menu. */
    OptMenuState_EnterScreenPos  = 7,  /** Entering screen position submenu. */
    OptMenuState_EnterBrightness = 8,  /** Entering brightness submenu. */
    OptMenuState_EnterController = 9,  /** Entering controller binding submenu. */
    OptMenuState_LeaveScreenPos  = 10, /** Leaving screen position submenu. */
    OptMenuState_LeaveBrightness = 11, /** Leaving brightness submenu. */
    OptMenuState_LeaveController = 12, /** Leaving controller binding submenu. */
    OptMenuState_EnterExtra      = 13, /** Entering extra options menu. */
    OptMenuState_Extra           = 14, /** In extra options menu. */
    OptMenuState_LeaveExtra      = 15  /** Leaving extra options menu. */
} e_OptMenuState;

/** @brief Screen position options submenu states.
 *
 * When the user navigates the screen position options submenu, this facilitates menu switching
 * via `s_GameWork::gameStateStep[1]`.
 */
typedef enum _OptMenuScreenPosState
{
    ScreenPosMenuState_0     = 0,
    ScreenPosMenuState_1     = 1,
    ScreenPosMenuState_2     = 2,
    ScreenPosMenuState_Leave = 3
} e_OptMenuScreenPosState;

/** @brief Brightness options submenu states.
 *
 * When the user navigates the brightness options submenu, this facilitates menu switching
 * via `s_GameWork::gameStateStep[1]`.
 */
typedef enum _BrightnessMenuState
{
    BrightnessMenuState_0     = 0,
    BrightnessMenuState_1     = 1,
    BrightnessMenuState_2     = 2,
    BrightnessMenuState_Leave = 3
} e_BrightnessMenuState;

/** @brief Controller binding options submenu states.
 *
 * When the user navigates the controller binding options submenu, this facilitates menu switching
 * via `s_GameWork::gameStateStep[1]`. It is also used for submenu selections (left column).
 */
typedef enum _ContMenuState
{
    ContMenuState_Leave   = -2,
    ContMenuState_Actions = -1,
    ContMenuState_Exit    = 0,
    ContMenuState_Type1   = 1,
    ContMenuState_Type2   = 2,
    ContMenuState_Type3   = 3,

    ContMenuState_Count   = 4
} e_ContMenuState;

/** @brief Main options menu selections. */
typedef enum _OptionMain
{
    OptMain_Exit           = 0,
    OptMain_Brightness     = 1,
    OptMain_Controller     = 2,
    OptMain_ScreenPosition = 3,
    OptMain_Vibration      = 4,
    OptMain_AutoLoad       = 5,
    OptMain_Sound          = 6,
    OptMain_BgmVolume      = 7,
    OptMain_SfxVolume      = 8,

    OptMain_Count          = 9
} e_OptionMain;

/** @brief Extra options menu selections. */
typedef enum _OptionExtra
{
    OptExtra_WeaponCtrl   = 0,
    OptExtra_Blood        = 1,
    OptExtra_ViewCtrl     = 2,
    OptExtra_RetreatTurn  = 3,
    OptExtra_MovementCtrl = 4,
    OptExtra_AutoAiming   = 5,
    OptExtra_ViewMode     = 6,
    OptExtra_BulletMult   = 7,

    OptExtra_Count        = 8
} e_OptionExtra;

/** @brief Blood color options submenu selections. */
typedef enum _OptionBloodColor
{
    OptBloodColor_Normal = 0,
    OptBloodColor_Green  = 1,
    OptBloodColor_Violet = 2,
    OptBloodColor_Black  = 3,

    OptBloodColor_Count  = 4
} e_OptionBloodColor;

/** @brief Controller binding options submenu selections (right column). */
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

typedef enum _BloodColor
{
    BloodColor_Normal = 0,
    BloodColor_Green  = 2,
    BloodColor_Violet = 5,
    BloodColor_Black  = 11
} e_BloodColor;

// ========
// STRUCTS
// ========

typedef struct _ScreenCtrl_SelectedElement
{
    e_ContMenuState optionIdx_0;
    e_InputAction   actionIdx_4;
} s_ScreenCtrl_SelectedElement;

// ========
// GLOBALS
// ========

extern s32 g_MainMenu_SelectedIdx;

extern s32 g_ExtraMenu_SelectedIdx;

extern s32 g_MainMenu_PrevSelectedIdx;

extern s32 g_ExtraMenu_PrevSelectedIdx;

extern s32 g_Gfx_ScreenPos_InvertColorBg;

extern bool g_ControllerSubmenu_IsOnActionColumn;

extern DR_MODE D_801E730C[MEMORY_CARD_SLOT_COUNT];

extern POLY_G4 D_801E7324[MEMORY_CARD_SLOT_COUNT];

extern char* g_ControllerSubmenu_OptionStrings[];

extern char* g_ControllerSubmenu_ActionStrings[];

// TODO: `s_Line2d` doesn't match for these.

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

/** @brief Tracks movement time of the cursor highlight. */
extern s32 g_Options_SelectionCursorTimer;

/** @brief Defines the number of options to
 * show in the extra options screen.
 * Used to show extra unlockable settings if
 * the player has them unlocked.
 */
extern s32 g_OptExtra_ShowSettingsCount;

extern s32 g_OptExtra_BloodColorSelected;

extern s32 g_OptExtra_BulletMultLimit;

// ==========
// FUNCTIONS
// ==========

// ============
// `options.c`
// ============

// `GameState_Options_Update`
void GameState_OptionScreen_Update();

// `Options_ExtraConfigUpdate`
void Settings_ExtraScreen();

// `Options_MainConfigUpdate`
void Settings_MainScreen();

// ==================
// `menu_graphics.c`
// ==================

// `Options_BgmVolumeBarDraw`
void Gfx_BgmBarDraw();

// `Options_SfxVolumeBarDraw`
void Gfx_SfxBarDraw();

/** @brief Draws the bars used for SFX and BGM audio options. */
// `Options_VolumeBarDraw`
void Gfx_BarDraw(s32 arg0, u8 arg1);

/** @brief Draws the option strings in the extra options screen. */
// `Options_ExtraSelectionStringsDraw`
void Gfx_OptionsStringsExtraDraw();

/** @brief Draws the option strings in the main options screen. */
// `Options_MainSelectionStringsDraw`
void Gfx_OptionsStringsMainDraw();

/** @brief Draws the bullets next to options and highlight indicating the
 * selected option in the extra options screen.
 */
// `Options_ExtraGraphicsDraw`
void Gfx_SelectedOptionExtra();

/** @brief Draws the bullets next to options and highlight indicating the
 * selected option in the main options screen.
 */
// `Options_MainGraphicsDraw`
void Gfx_SelectedOptionMain();

/** @brief Draws the vignette for the main and extra options screens. */
// `Options_VignetteDraw`
void Gfx_VignetteDraw();

// `Options_ExtraSettingsDraw`
void Gfx_SettingsOptionsExtraDraw();

/** @brief Draws the options for each setting used in the main options screen. */
// `Options_MainSettingsDraw`
void Gfx_SettingsOptionsMainDraw();

// ====================
// `screen_position.c`
// ====================

// `Options_ScreenPosition_Control`
void Settings_PositionScreen();

// `Options_ScreenPosition_ArrowsDraw`
void Gfx_PositionArrowsDraw();

/** @brief Draws the box that indicates the screen position in the position screen configuration. */
// `Options_ScreenPoisition_IndicatorDraw`
void Gfx_PositionIndicatorDraw();

// ===============
// `brightness.c`
// ===============

// `Options_Brightness_Control`
void Settings_BrightnessScreen();

// `Options_Brightness_LevelStringDraw`
void Gfx_BrightnessLevelTextDraw();

// `Options_Brightness_ArrowsDraw`
void Gfx_BrightnessLevelArrowsDraw();

// =======================
// `selection_graphics.c`
// =======================

/** @brief Draws the line and shadow on the selected option in options screens. */
// `Options_Selection_HighlightDraw`
void Gfx_LineDraw(s_Line2d* line, bool hasShadow, bool isRegular);

/** @brief Draws the arrows used in options screens. */
// `Options_Selection_ArrowDraw`
void Gfx_Options_BlueArrowDraw(s_Triangle2d* arrow, s32 isFlashing, s32 isColorReset);

/** @brief Draws the button next to options in the main and extra option screens. */
// `Options_Selection_BulletPointDraw`
void Gfx_ButtonDraw(s_Quad2d* quad, bool isCenter, bool isRegular);

// ===============
// `controller.c'
// ===============

// `Options_Controller_Control`
void Settings_ControllerScreen();

/** @brief Changes the button mapping based on the input. */
// `Options_Controller_BindingSet`
s32 Settings_ButtonChange(s32 actionIdx);

// `Options_Controller_SelectionTextDraw`
void Gfx_ControllerScreenDraw(bool isOnActionColumn, s32 optionIdx, s32 actionIdx, s32 boundActionIdx);

// `Options_Controller_ButtonIconsDraw`
void Gfx_ControllerButtonsDraw(s32 baseX, s32 baseY, u16 contConfig);

#endif
