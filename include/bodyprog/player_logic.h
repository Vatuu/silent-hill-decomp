#ifndef _PLAYER_LOGIC_H
#define _PLAYER_LOGIC_H

/** @brief This header is used to declare any variable, struct, or
 * function part of `BODYPROG.BIN` identified to be related
 * to the player logic.
 */

// ========
// GLOBALS
// ========

/** @brief Boolean. Used to define if the player is transitioning from walking to running and vice-versa. */
extern u8 g_Player_IsInWalkToRunTransition; // 0x800AF214

/** Boolean. */
extern u8 g_Player_DisableControl; // 0x800AF215

extern u8 D_800AF216; // 0x800AF216

/** `D_800C457C` could be related to animations that play during cutscenes.
 * 
 * Called by:
 * - 'func_800D2C7C' in map0_s00.c
 * - 'func_800D2D2C' in map0_s00.c
 * 
 * The value changes during cutscenes when the player does any of the following
 * actions:
 * * 0 - Nothing
 * * 1 - Walking
 * * 3 - Moves to the right?
 * * 4 - Moves to the left
 * 
 * This behaviour is irregular. After the first in-game dialogue
 * with Harry, the value is kept as 1 (even when he is not walking or in
 * a cutscene) until the next dialogue triggers (when Harry sees
 * Cheryl and the second FMV plays). Something similar happens on the
 * next overlay where the value is 1 during the first
 * cutscene and doesn't change until the player makes an input.
 */
extern u8 D_800C457C;

/** Boolean. */
extern u8 g_Player_DisableDamage; // 0x800C4562

extern VECTOR3 D_800C45F8;

// ==========
// FUNCTIONS
// ==========

void Player_Logic_Update(s_SubCharacter* chara, void* arg1, GsCOORDINATE2* coord);

void func_80073FC0(s_MainCharacterExtra* extra, s32 arg1, s32 arg2, s32 arg3);

bool func_80075504(s_SubCharacter* chara, s_MainCharacterExtra* extra);

void func_800771BC(s_SubCharacter* chara, s_MainCharacterExtra* extra);

void func_80077BB8(s_SubCharacter* chara, s32 arg1, s32 animIdx, s32 keyframeIdx, s32 arg4, s32 arg5, s32 arg6);

/** Player movement. */
void func_80077D00(s_SubCharacter* chara, s_MainCharacterExtra* extra);

/** Player function. */
void func_8007B924(s_SubCharacter* chara, s_MainCharacterExtra* extra);

/** @brief Checks for damage received by the player and handles the animations
 * for getting hurt or grabbed by monsters.
 *
 * @note SH2 symbols have a similar function named `PlayerCheckDamage`, but code-wise it has
 * no similarities.
 *
 * @bug During the transition from walking to running (and vice-versa), the player can't receive damage.
 */
void Player_ReceiveDamage(s_SubCharacter* chara, s_MainCharacterExtra* extra); // 0x8007C800

#endif
