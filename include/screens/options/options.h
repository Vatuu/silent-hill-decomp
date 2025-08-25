#ifndef _OPTIONS_H
#define _OPTIONS_H

#include "common.h"

/** @brief Header for `OPTIONS.BIN` declarations. */

// ======
// ENUMS
// ======

/** @brief Options menu states.
 *
 * When the user navigates an options menu, this facilitates menu switching
 * via `s_GameWork::gameStateStep[0]`.
 */
typedef enum _OptionsMenuState
{
    OptionsMenuState_EnterMainOptions  = 0,  /** Entering main options menu. */
    OptionsMenuState_MainOptions       = 1,  /** In main options menu. */
    OptionsMenuState_ScreenPos         = 2,  /** In screen position menu. */
    OptionsMenuState_Brightness        = 3,  /** In brightness menu. */
    OptionsMenuState_Controller        = 4,  /** In controller config menu. */
    OptionsMenuState_Leave             = 5,  /** Leaving options menu back to gameplay. */
    OptionsMenuState_LeaveMainOptions  = 6,  /** Leaving main options menu. */
    OptionsMenuState_EnterScreenPos    = 7,  /** Entering screen position menu. */
    OptionsMenuState_EnterBrightness   = 8,  /** Entering brightness menu. */
    OptionsMenuState_EnterController   = 9,  /** Entering controller config menu. */
    OptionsMenuState_LeaveScreenPos    = 10, /** Leaving screen position menu. */
    OptionsMenuState_LeaveBrightness   = 11, /** Leaving brightness menu. */
    OptionsMenuState_LeaveController   = 12, /** Leaving controller config menu. */
    OptionsMenuState_EnterExtraOptions = 13, /** Entering extra options menu. */
    OptionsMenuState_ExtraOptions      = 14, /** In extra options menu. */
    OptionsMenuState_LeaveExtraOptions = 15  /** Leaving extra options menu. */
} e_OptionsMenuState;

/** @brief Brightness menu states.
 *
 * When the user navigates the brightness menu, this facilitates menu switching
 * via `s_GameWork::gameStateStep[1]`.
 */
typedef enum _BrightnessMenuState
{
    BrightnessMenuState_0     = 0,
    BrightnessMenuState_1     = 1,
    BrightnessMenuState_2     = 2,
    BrightnessMenuState_Leave = 3
} e_BrightnessMenuState;

/** @brief Controller config menu states. Also used as entries for the left presets pane.
 *
 * When the user navigates the controller config menu, this facilitates menu switching
 * via `s_GameWork::gameStateStep[1]`.
 */
typedef enum _ControllerMenuState
{
    ControllerMenuState_Leave   = -2,
    ControllerMenuState_Actions = -1,
    ControllerMenuState_Exit    = 0,
    ControllerMenuState_Type1   = 1,
    ControllerMenuState_Type2   = 2,
    ControllerMenuState_Type3   = 3,

    ControllerMenuState_Count   = 4
} e_ControllerMenuState;

/** @brief Screen position menu states.
 *
 * When the user navigates the screen position menu, this facilitates menu switching
 * via `s_GameWork::gameStateStep[1]`.
 */
typedef enum _ScreenPosMenuState
{
    ScreenPosMenuState_0     = 0,
    ScreenPosMenuState_1     = 1,
    ScreenPosMenuState_2     = 2,
    ScreenPosMenuState_Leave = 3
} e_ScreenPosMenuState;

/** @brief Main options menu entries. */
typedef enum _MainOptionsMenuEntry
{
    MainOptionsMenuEntry_Exit           = 0,
    MainOptionsMenuEntry_Brightness     = 1,
    MainOptionsMenuEntry_Controller     = 2,
    MainOptionsMenuEntry_ScreenPosition = 3,
    MainOptionsMenuEntry_Vibration      = 4,
    MainOptionsMenuEntry_AutoLoad       = 5,
    MainOptionsMenuEntry_Sound          = 6,
    MainOptionsMenuEntry_BgmVolume      = 7,
    MainOptionsMenuEntry_SfxVolume      = 8,

    MainOptionsMenuEntry_Count          = 9
} e_MainOptionsMenuEntry;

/** @brief Extra options menu entries. */
typedef enum _ExtraOptionsMenuEntry
{
    ExtraOptionsMenuEntry_WeaponCtrl   = 0,
    ExtraOptionsMenuEntry_Blood        = 1,
    ExtraOptionsMenuEntry_ViewCtrl     = 2,
    ExtraOptionsMenuEntry_RetreatTurn  = 3,
    ExtraOptionsMenuEntry_MovementCtrl = 4,
    ExtraOptionsMenuEntry_AutoAiming   = 5,
    ExtraOptionsMenuEntry_ViewMode     = 6,
    ExtraOptionsMenuEntry_BulletMult   = 7,

    ExtraOptionsMenuEntry_Count        = 8
} e_ExtraOptionsMenuEntry;

/** @brief Blood color menu entries. */
typedef enum _BloodColorMenuEntry
{
    BloodColorMenuEntry_Normal = 0,
    BloodColorMenuEntry_Green  = 1,
    BloodColorMenuEntry_Violet = 2,
    BloodColorMenuEntry_Black  = 3,

    BloodColorMenuEntry_Count  = 4
} e_BloodColorMenuEntry;

// TODO: Should be moved elsewhere, options only borrow this enum.
/** @brief Input actions. Also used as controller config menu entries for the right actions pane. */
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

typedef struct _ControllerMenu_SelectedEntries
{
    e_ControllerMenuState preset_0;
    e_InputAction         action_4;
} s_ControllerMenu_SelectedEntries;

// ========
// GLOBALS
// ========

extern s32 g_MainOptionsMenu_SelectedEntry;

extern s32 g_ExtraOptionsMenu_SelectedEntry;

extern s32 g_MainOptionsMenu_PrevSelectedEntry;

extern s32 g_ExtraOptionsMenu_PrevSelectedEntry;

extern bool g_ScreenPosMenu_InvertBackgroundFade;

extern bool g_ControllerMenu_IsOnActionsPane;

extern DR_MODE g_ControllerMenu_SelectionHighlightDrawModes[MEMORY_CARD_SLOT_COUNT];

extern POLY_G4 g_ControllerMenu_SelectionHighlightQuad[MEMORY_CARD_SLOT_COUNT];

extern DVECTOR g_ExtraOptions_SelectionHighlightFrom_Unused;
extern DVECTOR g_ExtraOptions_SelectionHighlightTo_Unused;
extern DVECTOR g_MainOptions_SelectionHighlightFrom_Unused;
extern DVECTOR g_MainOptions_SelectionHighlightTo_Unused;

extern DVECTOR g_ExtraOptions_SelectionHighlightFrom;
extern DVECTOR g_ExtraOptions_SelectionHighlightTo;

extern DVECTOR g_MainOptions_SelectionHighlightFrom;
extern DVECTOR g_MainOptions_SelectionHighlightTo;

extern s32 g_ScreenPosMenu_BackgroundFade;

extern s16 g_ScreenPosMenu_PositionX;
extern s16 g_ScreenPosMenu_PositionY;

extern s_ControllerMenu_SelectedEntries g_ControllerMenu_SelectedEntries;

/** @brief Tracks movement time of the cursor highlight. */
extern s32 g_Options_SelectionHighlightTimer;

/** @brief Defines the number of options to
 * show in the extra options screen.
 * Used to show extra unlockable settings if
 * the player has them unlocked.
 */
extern s32 g_ExtraOptionsMenu_EntryCount;

extern s32 g_ExtraOptionsMenu_SelectedBloodColorEntry;

extern s32 g_ExtraOptionsMenu_BulletMultMax;

// ==========
// FUNCTIONS
// ==========

// ============
// `options.c`
// ============

/** @brief Options menu game state handler.
 *
 * Scratch: https://decomp.me/scratch/n8GDJ
 */
void GameState_Options_Update(void);

/** @brief Controller for the extra options menu.
 *
 * Scratch: https://decomp.me/scratch/HRrIM
 */
void Options_ExtraOptionsMenu_Control(void);

/** @brief Controller for the main options menu.
 *
 * Handles menu states according to user input as well as graphics draw calls.
 *
 * Scratch: https://decomp.me/scratch/N0xvj
 */
void Options_MainOptionsMenu_Control(void);

// ==================
// `menu_graphics.c`
// ==================

/** @brief Draws the BGM volume bar in the main options menu.
 *
 * Scratch: https://decomp.me/scratch/Zao7J
 */
void Options_MainOptionsMenu_BgmVolumeBarDraw(void);

/** @brief Draws the SFX volume bar in the main options menu.
 *
 * Scratch: https://decomp.me/scratch/bE2Uz
 */
void Options_MainOptionsMenu_SfxVolumeBarDraw(void);

/** @brief Draws a volume bar.
 *
 * Called by `Options_MainOptionsMenu_BgmVolumeBarDraw` and `Options_MainOptionsMenu_SfxVolumeBarDraw`.
 *
 * Scratch: https://decomp.me/scratch/Hl65c
*/
void Options_MainOptionsMenu_VolumeBarDraw(bool isSfx, u8 vol);

/** @brief Draws a heading and entry strings in the extra options menu.
 *
 * Scratch: https://decomp.me/scratch/IYutD
 */
void Options_ExtraOptionsMenu_EntryStringsDraw(void);

/** @brief Draws a heading entry strings in the main options menu.
 *
 * Scratch: https://decomp.me/scratch/cbqqU
 */
void Options_MainOptionsMenu_EntryStringsDraw(void);

/** @brief Draws bullet points next to entries and the highlight indicating the
 * selected entry in the extra options menu.
 * 
 * Scratch: https://decomp.me/scratch/ghUNv
 */
void Options_ExtraOptionsMenu_SelectionHighlightDraw(void);

/** @brief Draws bullet points next to entries and the highlight indicating the
 * selected entry in the main options menu.
 *
 * Scratch: https://decomp.me/scratch/2gTWn
 */
void Options_MainOptionsMenu_SelectionHighlightDraw(void);

/** @brief Draws the background vignette of Harry in the main and extra options menus.
 *
 * Scratch: https://decomp.me/scratch/F32M5
 */
void Options_Menu_VignetteDraw(void);

/** @brief Draws configuration strings and other visual elements in the extra options menu.
 *
 * Scratch: https://decomp.me/scratch/GW3Mi
 */
void Options_ExtraOptionsMenu_ConfigDraw(void);

/** @brief Draws configuration strings and other visual elements in the main options menu.
 *
 * Scratch: https://decomp.me/scratch/5fuLW
 */
void Options_MainOptionsMenu_ConfigDraw(void);

// ====================
// `screen_position.c`
// ====================

/** @brief Controller for the screen position options menu.
 *
 * Handles menu states, user input, SFX, and graphics drawing.
 *
 * Scratch: https://decomp.me/scratch/5F9Gq
*/
void Options_ScreenPosMenu_Control(void);

/** @brief Draws arrows in the screen position options menu.
 *
 * Draws the blue up, down, left, and right arrows with flowing color gradients at the edges of the screen.
 * Depending on the directional input from the user, it also draws a cyan border around the arrow
 * corresponding to the direction.
 * Called by `Options_ScreenPosMenu_Control`.
 *
 * Scratch: https://decomp.me/scratch/vYoKG
 */
void Options_ScreenPosMenu_ArrowsDraw(void);

/** @brief Draws the box containing the screen position configuration.
 *
 * Scratch: https://decomp.me/scratch/TOnxP
 */
void Options_ScreenPosMenu_IndicatorDraw(void);

// ===============
// `brightness.c`
// ===============

/** @brief Controller for the brightness options menu.
 *
 * Handles menu states, user input, SFX, and graphics drawing.
 *
 * Scratch: TODO
*/
void Options_BrightnessMenu_Control(void);

/** @brief Draws the string representing the light level in the brightness options menu. */
void Options_BrightnessMenu_LevelStringDraw(void);

/** @brief Draws arrows in the brightness options menu.
 *
 * Handles drawing of the blue left and right arrows with flowing color gradients at the sides of the screen.
 * Depending on the direction input from the user, it also draws a cyan border around the arrow
 * corresponding to the direction.
 *
 * Scratch: TODO
 *
 * Called by `Options_BrightnessMenu_Control`.
 */
void Options_BrightnessMenu_ArrowsDraw(void);

// =======================
// `selection_graphics.c`
// =======================

/** @brief Draws a UI selection highlight.
 *
 * Handles drawing of the underline and upward shadow gradient used to highlight the selected entry
 * in the main and extra options menus.
 * Called by `Options_MainOptionsMenu_SelectionHighlightDraw` and `Options_ExtraOptionsMenu_SelectionHighlightDraw`.
 *
 * Scratch: https://decomp.me/scratch/zHeCb
 *
 * @param line Reference line for the position and width of the highlight.
 * @param hasShadow If a shadow is to be drawn along with an underline.
 *                  `true` for a shadow,
 *                  `false` for no shadow.
 * @param invertGradient Whether to invert the color gradient of the underline. Non-functional.
 */
void Options_Selection_HighlightDraw(s_Line2d* line, bool hasShadow, bool invertGradient);

/** @brief Draws a UI arrow.
 *
 * Handles drawing of elements for the blue arrows used to indicate possible directions of navigation
 * for certain selected entries in the main and extra options menus.
 *
 * @note Called twice if the arrow requires a border, with `isFlashing` passed as `false` in the second call.
 *
 * Scratch: TODO
 *
 * @param arrow 2D polygon of the arrow element.
 * @param isFlashing Whether to draw the arrow element with a flowing color gradient.
 *                   `true` for a dark blue and cyan gradient drawn in front,
 *                   `false` for a solid cyan color drawn behind.
 * @param resetColor @unused No meaningful purpose.
*/
void Options_Selection_ArrowDraw(s_Triangle2d* arrow, bool isFlashing, bool resetColor);

/** @brief Draws a UI bullet point.
 *
 * Handles drawing of elements of the gold bullet points placed next to entries in the main and extra options menus.
 * 
 * @note Called twice to build a whole bullet point, with `isCenter` passed as `true` and `false` on consecutive calls.
 *
 * Scratch: https://decomp.me/scratch/A88oo
 *
 * @param quad 2D polygon of the bullet point element to draw.
 * @param isCenter If this is the center element of the bullet point.
 *                 `true` for a smaller element at the center drawn in front,
 *                 `false` for a larger one serving as the border with an inverted gradient drawn behind.
 * @param isInactive If the entry for which the bullet point is being drawn is unselected.
 *                   `true` for an unselected entry (draws darker bullet point),
 *                   `false` for a selected entry (draws darker bullet point).
 */
void Options_Selection_BulletPointDraw(s_Quad2d* quad, bool isCenter, bool isInactive);

// ===============
// `controller.c'
// ===============

/** @brief Controller for the controller config options menu.
 *
 * Handles the menu state, user input, SFX, and graphics drawing.
 *
 * Scratch: https://decomp.me/scratch/uAay2
*/
void Options_Controller_Control(void);

/** @brief Changes the button mapping based on the input and updates the configuration.
 *
 * Scratch: https://decomp.me/scratch/GZGwV
 *
 * @param actionIdx Index of the input action for which to update the controller configuration.
 */
s32 Options_ControllerMenu_ConfigUpdate(s32 actionIdx);

/** @brief Draws entry strings and icons in the controller config options menu.
 *
 * Scratch: https://decomp.me/scratch/0U6fb
 *
 * @param isOnActionsPane If the user is navigating the right actions pane.
 *                        `true` for the right actions pane,
 *                        `false` for the left presets pane.
 * @param presetsEntryIdx Selected presets pane entry index
 * @param actionsEntryIdx Selected actions pane entry index.
 * @param boundActionIdx Index of a newly bound input action.
 */
void Options_ControllerMenu_EntriesDraw(bool isOnActionsPane, s32 presetsEntryIdx, s32 actionsEntryIdx, s32 boundActionIdx);

/** @brief Draws the button icons in the controller config options menu.
 *
 * Handles drawing of a single row of 2D sprites representing a button mapping.
 * Called by `Options_ControllerMenu_EntriesDraw`.
 *
 * Scratch: https://decomp.me/scratch/rRQjd
 *
 * @param baseX Base X position at which to begin drawing.
 * @param baseY Base Y position at which to begin drawing.
 * @param config Controller configuration flags.
 */
void Options_ControllerMenu_ButtonIconsDraw(s32 baseX, s32 baseY, u16 config);

#endif
