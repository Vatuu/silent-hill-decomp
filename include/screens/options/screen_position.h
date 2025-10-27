#ifndef _SCREENS_OPTIONS_SCREENPOSITION_H
#define _SCREENS_OPTIONS_SCREENPOSITION_H

#include "common.h"

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

extern bool g_ScreenPosMenu_InvertBackgroundFade;
extern s32  g_ScreenPosMenu_BackgroundFade;
extern s16  g_ScreenPosMenu_PositionX;
extern s16  g_ScreenPosMenu_PositionY;

/** @brief Controller for the screen position options menu. Handles menu states, user input, SFX, and graphics drawing.
 * Scratch: https://decomp.me/scratch/5F9Gq
*/
void Options_ScreenPosMenu_Control(void);

/** @brief Draws the arrows at the edges of the screen indicating input directions in the screen position options menu.
 *
 * Called by `Options_ScreenPosMenu_Control`.
 * Scratch: https://decomp.me/scratch/vYoKG
 */
void Options_ScreenPosMenu_ArrowsDraw(void);

/** @brief Draws the screen position configuration string and its background box.
 * Scratch: https://decomp.me/scratch/TOnxP
 */
void Options_ScreenPosMenu_ConfigDraw(void);

#endif
