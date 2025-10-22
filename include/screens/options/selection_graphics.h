#ifndef _SCREENS_OPTIONS_SELECTION_GRAPHICS_H
#define _SCREENS_OPTIONS_SELECTION_GRAPHICS_H

#include "common.h"

/** @brief Draws a scaling entry selection highlight in the main and extra options menus.
 *
 * Called by `Options_MainOptionsMenu_SelectionHighlightDraw` and `Options_ExtraOptionsMenu_SelectionHighlightDraw`.
 * Scratch: https://decomp.me/scratch/zHeCb
 *
 * @param line Reference line for the highlight position and width.
 * @param hasShadow `true` if drawing the highlight with a shadow and a line, `false` for the line only.
 * @param invertGradient @unused `true` to invert the line gradient, `false` to not invert. Non-functional.
 */
void Options_Selection_HighlightDraw(s_Line2d* line, bool hasShadow, bool invertGradient);

/** @brief Draws a blue arrow element used for certain listed entries in the main and extra options menus.
 *
 * @note Called twice if the arrow requires a border with `isFlashing` passed as `false` in the second call.
 * Scratch: TODO
 *
 * @param arrow 2D polygon of the arrow element.
 * @param isFlashing `true` if drawing the flashing element with a gradient, `false` if drawing the border.
 * @param resetColor @unused No meaningful purpose.
*/
void Options_Selection_ArrowDraw(s_Triangle2d* arrow, bool isFlashing, bool resetColor);

/** @brief Draws a gold bullet point element used next to listed entries in the main and extra options menus.
 *
 * @note Called twice to build a whole bullet point with `isCenter` passed as `true` and `false` on consecutive calls.
 * Scratch: https://decomp.me/scratch/A88oo
 *
 * @param quad 2D polygon of the bullet point element.
 * @param isCenter `true` if drawing the center element, `false` if drawing the border element.
 * @param isInactive `true` if the entry is unselected, `false` if selected.
 */
void Options_Selection_BulletPointDraw(s_Quad2d* quad, bool isCenter, bool isInactive);

#endif
