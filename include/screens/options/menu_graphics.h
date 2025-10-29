#ifndef _SCREENS_OPTIONS_MENU_GRAPHICS_H
#define _SCREENS_OPTIONS_MENU_GRAPHICS_H

#include "common.h"

/** @brief Draws a BGM volume bar in the main options menu.
 * Scratch: https://decomp.me/scratch/Zao7J
 */
void Options_MainOptionsMenu_BgmVolumeBarDraw(void);

/** @brief Draws an SFX volume bar in the main options menu.
 * Scratch: https://decomp.me/scratch/bE2Uz
 */
void Options_MainOptionsMenu_SfxVolumeBarDraw(void);

/** @brief Draws a volume bar.
 *
 * Called by `Options_MainOptionsMenu_BgmVolumeBarDraw` and `Options_MainOptionsMenu_SfxVolumeBarDraw`.
 * Scratch: https://decomp.me/scratch/Hl65c
*/
void Options_MainOptionsMenu_VolumeBarDraw(bool isSfx, u8 vol);

/** @brief Draws the heading and all listed entry strings in the extra options menu.
 * Scratch: https://decomp.me/scratch/IYutD
 */
void Options_ExtraOptionsMenu_EntryStringsDraw(void);

/** @brief Draws the heading and all listed entry strings in the main options menu.
 * Scratch: https://decomp.me/scratch/cbqqU
 */
void Options_MainOptionsMenu_EntryStringsDraw(void);

/** @brief Draws gold bullet points next to the listed entries and a highlight indicating the
 * selected entry in the extra options menu.
 * Scratch: https://decomp.me/scratch/ghUNv
 */
void Options_ExtraOptionsMenu_SelectionHighlightDraw(void);

/** @brief Draws gold bullet points next to the listed entries and a highlight indicating the
 * selected entry in the main options menu.
 * Scratch: https://decomp.me/scratch/2gTWn
 */
void Options_MainOptionsMenu_SelectionHighlightDraw(void);

/** @brief Draws the background vignette of Harry in the main and extra options menus.
 * Scratch: https://decomp.me/scratch/F32M5
 */
void Options_Menu_VignetteDraw(void);

/** @brief Draws configuration strings and blue arrows to the right of the listed entries in the extra options menu.
 * Scratch: https://decomp.me/scratch/GW3Mi
 */
void Options_ExtraOptionsMenu_ConfigDraw(void);

/** @brief Draws configuration strings and blue arrows to the right of the listed entries in the main options menu.
 * Scratch: https://decomp.me/scratch/5fuLW
 */
void Options_MainOptionsMenu_ConfigDraw(void);

#endif
