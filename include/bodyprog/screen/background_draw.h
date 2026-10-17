#ifndef _BODYPROG_SCREEN_BACKGROUNDDRAW_H
#define _BODYPROG_SCREEN_BACKGROUNDDRAW_H

// ========
// GLOBALS
// ========

/** @brief Gamma intensity of background images. */
extern q0_8 g_Screen_BackgroundImgGamma;

// ==========
// FUNCTIONS
// ==========

/** @brief Draws a background image.
 *
 * Scratch: https://decomp.me/scratch/sYGPW
 *
 * @note Only applies to menus and the preview of maps when grabbing them.
 *
 * @param image Image to draw.
 */
void Screen_BackgroundImgDraw(s_FsImageDesc* image);

/** @brief Draws transition between images.
 *
 * Scratch: https://decomp.me/scratch/1MhOK
 *
 * @param imageIn Image previously being drawn.
 * @param imageOut Image to transition.
 * @param alpha Alpha streght between of the second image.
 */
void Screen_BackgroundImgTransition(s_FsImageDesc* imageIn, s_FsImageDesc* imageOut, q3_12 alpha);

/** @brief Set black background and slowly fade in a background image
 *
 * Scratch: https://decomp.me/scratch/IFpWU
 *
 * @note Most of the code is shared with `Screen_BackgroundImgTransition` code.
 *
 * @param image Image to draw.
 */
void Screen_BackgroundImgDrawBlackFadeIn(s_FsImageDesc* image);

/** @brief Applies motion blur to the background from the scene.
 *
 * Scratch: https://decomp.me/scratch/0T9qN
 *
 * @note Used only in the loading screen.
 *
 * @param vBlanks `e_SyncMode`.
 * @return Always return `false`.
 */
bool Screen_BackgroundMotionBlur(s32 vBlanks);

#endif
