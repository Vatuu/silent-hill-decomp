#ifndef _BODYPROG_GAMEBOOT_CHARA_INIT_H
#define _BODYPROG_GAMEBOOT_CHARA_INIT_H

void GameBoot_NpcInit(void);

/** Crucial for getting in-game.
 * Removing it breaks the camera, inventory's 3D elements, effects
 * (lighting, fog, lens flare, etc.), NPCs don't spawn, and
 * doing any action unrelated to aiming a weapon or interacting
 * with the environment crashes the game.
 */
void GameBoot_InGameInit(void);

#endif
