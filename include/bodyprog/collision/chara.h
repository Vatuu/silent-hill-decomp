#ifndef _BODYPROG_COLLISION_CHARA_H
#define _BODYPROG_COLLISION_CHARA_H

#include "bodyprog/chara/chara.h"

bool func_80070320(void);

/** TODO: Return type uncertain. */
q19_12 func_80070360(s_SubCharacter* chara, q19_12 someDist, q3_12 arg2);

/** @brief Sets a character's interpolated collision shapes for the active animation frame.
 *
 * @param chara Character to update.
 * @param keyframe0 First keyframe.
 * @param keyframe1 Second keyframe.
 */
void Collision_CharaCollisionSet(s_SubCharacter* chara, s_Keyframe* keyframe0, s_Keyframe* keyframe1);

/** @brief Sets the scale of a character's model bone.
 *
 * @param boneCoords Character model bone coords.
 * @param boneIdx Index of the model bone to scale.
 * @param scaleX X scale.
 * @param scaleY Y scale.
 * @param scaleZ Z scale.
 */
void Chara_ModelBoneScaleSet(GsCOORDINATE2* boneCoords, s32 boneIdx, q19_12 scaleX, q19_12 scaleY, q19_12 scaleZ);

#endif
