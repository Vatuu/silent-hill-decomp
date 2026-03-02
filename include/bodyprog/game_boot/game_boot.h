#ifndef _BODYPROG_GAMEBOOT_GAMEBOOT_H
#define _BODYPROG_GAMEBOOT_GAMEBOOT_H

#include "bodyprog/game_boot/background_sound_init.h"
#include "bodyprog/game_boot/chara_init.h"
#include "bodyprog/game_boot/game_load.h"
#include "bodyprog/game_boot/load_screen.h"

void GameBoot_SavegameInitialize(s8 overlayId, s32 difficulty);

/** @brief Initializes the player character model. */
void GameBoot_PlayerInit(void);

/** Loads a map file into `g_OvlDynamic`. */
void GameBoot_MapLoad(s32 mapIdx);

#endif
