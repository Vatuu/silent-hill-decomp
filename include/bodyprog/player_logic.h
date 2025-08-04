#ifndef _PLAYER_LOGIC_H
#define _PLAYER_LOGIC_H

/** @brief This header is used to declare any variable, struct, or
 * function part of `BODYPROG.BIN` identified to be related
 * to the player logic.
 */

// ========
// GLOBALS
// ========

/** @brief Used to define if player is transitioning from walking to run and vice-versa */
extern u8 g_Player_Walk2RunTransition; // 0x800AF214

/**
 * 0 = Player has control, 1 = Player do not have control
 */
extern u8 g_Player_EnableControl; // 0x800AF215

extern u8 D_800AF216; // 0x800AF216

// ==========
// FUNCTIONS
// ==========

void Player_Logic_Update(s_SubCharacter* chara, void* arg1, GsCOORDINATE2* coord);

#endif
