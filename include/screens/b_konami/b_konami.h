#ifndef _SCREENS_B_KONAMI_H
#define _SCREENS_B_KONAMI_H

#include "common.h"

/** @brief KCET logo state steps.
 * Used by `GameState_KcetLogo_MemCardCheck` and `GameState_KcetLogo_Update`.
 */
typedef enum _KcetLogoStateStep
{
    KcetLogoStateStep_Init,
    KcetLogoStateStep_CheckMemCards,
    KcetLogoStateStep_NoMemCard,
    KcetLogoStateStep_NoMemCardFreeSpace,
    KcetLogoStateStep_NoSaveGame,
    KcetLogoStateStep_HasSavegame,
    KcetLogoStateStep_LogoDelay,
    KcetLogoStateStep_FinishAfterFade
} e_KcetLogoStateStep;

/** @brief Konami logo state steps. */
typedef enum _KonamiLogoStateStep
{
    KonamiLogoStateStep_Init,
    KonamiLogoStateStep_WaitForFade,
    KonamiLogoStateStep_LogoDelay,
    KonamiLogoStateStep_FinishAfterFade
} e_KonamiLogoStateStep;

/** Displays the Konami logo and loads base hero animations in the background. */
void GameState_KonamiLogo_Update(void);

/** @brief Checks memory cards for free space and existing savegames.
 *
 * @return `e_KcetLogoStateStep`.
 */
s32 GameState_KcetLogo_MemCardCheck(void);

/** Displays the KCET logo and loads game data in the background. */
void GameState_KcetLogo_Update(void);

/** Draws segments for Konami and KCET logos in the boot screen. */
void BootScreen_ImageSegmentDraw(s_FsImageDesc* image, s32 otz, s32 vramX, s32 vramY, s32 w, s32 h, s32 x, s32 y);

/** @brief Draws the Konami logo in the boot screen. */
void BootScreen_KonamiScreenDraw(void);

/** @brief Draws the KCET logo in the boot screen. */
void BootScreen_KcetScreenDraw(void);

#endif
