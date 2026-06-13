#ifndef _BODYPROG_COLLISION_LOS_H
#define _BODYPROG_COLLISION_LOS_H

#include "bodyprog/chara/chara.h"

// Returns angle.
q19_12 func_8006F99C(s_SubCharacter* chara, q19_12 dist, q3_12 headingAngle);

/** Angle getter. Something to do with the direction from a character to a target position, probably for NPC AI.
 * Unsure if `spanAngle` is an angle.
 */
q19_12 Los_CharaHeadingAngleGet(s_SubCharacter* chara, q19_12 dist, q19_12 toX, q19_12 toZ, q3_12 spanAngle, bool cond);

bool func_8006FD90(s_SubCharacter* chara, s32 count, q19_12 baseDistMax, q19_12 distStep);

/** @brief Checks if there's an obstructed target-based line of sight between a character and a target position.
 *
 * @note `fromChara` is excluded.
 *
 * @param fromChara Origin character.
 * @param toX Target X position.
 * @param toY Target Y position.
 * @param toZ Target Z position.
 * @return `true` if there's an obstruction, `false` otherwise.
 */
bool Los_CharaToTargetHitCheck(s_SubCharacter* fromChara, q19_12 toX, q19_12 toY, q19_12 toZ);

/** @brief Checks if there's an unobstructed target-based line of sight between a character and any other character.
 *
 * @note `fromChara` is excluded.
 *
 * @param fromChara Origin character.
 * @param toX Target X position.
 * @param toY Target Y position.
 * @param toZ Target Z position.
 * @return `true` if there's no obstruction, `false` otherwise.
 */
bool Los_CharaToCharaTargetCheck(s_SubCharacter* fromChara, q19_12 toX, q19_12 toY, q19_12 toZ);

/** @brief Checks if there's an unobstructed line of sight between an NPC and a player.
 *
 * @param fromNpc Origin NPC character.
 * @param toPlayer Target player character.
 * @return `true` if there's no obstruction, `false` otherwise.
 */
bool Los_NpcToPlayerHitCheck(s_SubCharacter* fromNpc, s_SubCharacter* toPlayer);

/** @brief Checks if there's an unobstructed distance-based line of sight between a character and any other character.
 *
 * @note `fromChara` is excluded.
 *
 * @param fromChara Origin character.
 * @param dist Ray distance.
 * @param headingAngle Ray heading angle on the XZ plane.
 * @return `true` if there's no obstruction, `false` otherwise.
 */
bool Los_CharaToCharaDistCheck(s_SubCharacter* fromChara, q19_12 dist, q3_12 headingAngle);

/** @brief @unused Checks if there's another character obstructing the distance-based line of sight in front of a
 * character.
 *
 * @note `fromChara` is excluded.
 *
 * @param fromChara Origin character.
 * @param dist Ray distance.
 * @return `true` if there's another character in front, `false` otherwise.
 */
bool Los_CharaToCharaFrontHitCheck(s_SubCharacter* fromChara, q19_12 dist);

/** @brief Checks if there's an obstructed distance-based line of sight from a character.
 *
 * @note `fromChara` is excluded.
 *
 * @param fromChara Origin character.
 * @param dist Ray distance.
 * @param headingAngle Ray heading angle on the XZ plane.
 * @return `true` if there's an obstruction, `false` otherwise.
 */
bool Los_CharaHitCheck(s_SubCharacter* fromChara, q19_12 dist, q3_12 headingAngle);

#endif
