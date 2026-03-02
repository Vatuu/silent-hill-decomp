#ifndef _BODYPROG_GAMEMAIN_H
#define _BODYPROG_GAMEMAIN_H

// ======
// ENUMS
// ======

/** @brief Reset types used in `MainLoop_ShouldWarmReset`. */
typedef enum _ResetType
{
    ResetType_None     = 0,
    ResetType_WarmBoot = 2
} e_ResetType;

// ========
// GLOBALS
// ========

extern s32 g_WarmBootTimer;

// ==========
// FUNCTIONS
// ==========

/** @brief Checks for a specific combination of inputs to determine if a soft reboot should take place.
 *
 * @return `ResetType_WarmBoot` if a soft reboot should take place, `ResetType_None` otherwise.
 * @note OPM counterpart of this function also returns `4` which is used to kill game's process.
 */
s32 MainLoop_ShouldWarmReset(void);

#endif
