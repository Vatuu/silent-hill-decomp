#ifndef _SCREENS_B_KONAMI_H
#define _SCREENS_B_KONAMI_H

#include "common.h"

// Used by both `GameState_KcetLogo_MemCardCheck` and `GameState_KcetLogo_Update`.
typedef enum
{
    KcetLogoStateStep_Init,
    KcetLogoStateStep_CheckMemCards,
    KcetLogoStateStep_NoMemCard,
    KcetLogoStateStep_NoMemCardFreeSpace,
    KcetLogoStateStep_NoSaveGame,
    KcetLogoStateStep_HasSaveGame,
    KcetLogoStateStep_LogoDelay,
    KcetLogoStateStep_FinishAfterFade,
} e_KcetLogoStateStep;

/** Displays the Konami logo and starts loading base hero animations. */
void GameState_KonamiLogo_Update(void);

/** Checks memory cards for free space & existing savegames. */
e_KcetLogoStateStep GameState_KcetLogo_MemCardCheck(void);

/** Displays the KCET logo and starts loading various things. */
void GameState_KcetLogo_Update(void);

/** Draws segments of Konami and KCET logos. */
void Gfx_BootScreenImageSegmentDraw(s_FsImageDesc* image, s32 otz, s32 vramX, s32 vramY, s32 w, s32 h, s32 x, s32 y);

void Gfx_KonamiScreenDraw(void);

void Gfx_KcetScreenDraw(void);

#endif
