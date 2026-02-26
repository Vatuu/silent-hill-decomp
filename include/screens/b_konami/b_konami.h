#ifndef _SCREENS_B_KONAMI_H
#define _SCREENS_B_KONAMI_H

#include "common.h"

// Used by both `GameState_KcetLogo_MemCardCheck` and `GameState_KcetLogo_Update`.
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

typedef enum _KonamiLogoStateStep
{
    KonamiLogoStateStep_Init,
    KonamiLogoStateStep_WaitForFade,
    KonamiLogoStateStep_LogoDelay,
    KonamiLogoStateStep_FinishAfterFade
} e_KonamiLogoStateStep;

/** Displays the Konami logo and starts loading base hero animations. */
void GameState_KonamiLogo_Update(void);

/** @brief Checks memory cards for free space & existing savegames.
 @return `e_KcetLogoStateStep`
 */
s32 GameState_KcetLogo_MemCardCheck(void);

/** Displays the KCET logo and starts loading various things. */
void GameState_KcetLogo_Update(void);

/** Draws segments of Konami and KCET logos. */
void BootScreen_ImageSegmentDraw(s_FsImageDesc* image, s32 otz, s32 vramX, s32 vramY, s32 w, s32 h, s32 x, s32 y);

void BootScreen_KonamiScreenDraw(void);

void BootScreen_KcetScreenDraw(void);

#endif
