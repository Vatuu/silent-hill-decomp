#ifndef _SCREENS_OPTIONS_OPTIONS_H
#define _SCREENS_OPTIONS_OPTIONS_H

#include "common.h"
#include "screens/options/brightness.h"
#include "screens/options/controller.h"
#include "screens/options/menu_graphics.h"
#include "screens/options/screen_position.h"
#include "screens/options/selection_graphics.h"

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

typedef enum _BloodColor
{
    BloodColor_Normal = 0,
    BloodColor_Green  = 2,
    BloodColor_Violet = 5,
    BloodColor_Black  = 11
} e_BloodColor;

// ========
// GLOBALS
// ========

extern s32 g_MainOptionsMenu_SelectedEntry;
extern s32 g_ExtraOptionsMenu_SelectedEntry;
extern s32 g_MainOptionsMenu_PrevSelectedEntry;
extern s32 g_ExtraOptionsMenu_PrevSelectedEntry;

extern DVECTOR g_ExtraOptions_SelectionHighlightFrom_Unused;
extern DVECTOR g_ExtraOptions_SelectionHighlightTo_Unused;
extern DVECTOR g_MainOptions_SelectionHighlightFrom_Unused;
extern DVECTOR g_MainOptions_SelectionHighlightTo_Unused;

extern DVECTOR g_ExtraOptions_SelectionHighlightFrom;
extern DVECTOR g_ExtraOptions_SelectionHighlightTo;
extern DVECTOR g_MainOptions_SelectionHighlightFrom;
extern DVECTOR g_MainOptions_SelectionHighlightTo;

/** @brief Tracks movement time of the cursor highlight. */
extern s32 g_Options_SelectionHighlightTimer;

/** @brief Number of options to show in the extra options screen. Shows extra unlockable settings if they are unlocked. */
extern s32 g_ExtraOptionsMenu_EntryCount;

extern s32 g_ExtraOptionsMenu_SelectedBloodColorEntry;

extern s32 g_ExtraOptionsMenu_BulletMultMax;

// ==========
// FUNCTIONS
// ==========

/** @brief Options menu game state handler.
 * Scratch: https://decomp.me/scratch/n8GDJ
 */
void GameState_Options_Update(void);

/** @brief Controller for the extra options menu.
 * Scratch: https://decomp.me/scratch/HRrIM
 */
void Options_ExtraOptionsMenu_Control(void);

/** @brief Controller for the main options menu. Handles menu states, user input, and graphics draw calls.
 * Scratch: https://decomp.me/scratch/N0xvj
 */
void Options_MainOptionsMenu_Control(void);

#endif
