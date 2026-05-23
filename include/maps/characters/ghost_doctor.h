#ifndef _MAPS_CHARACTERS_GHOSTDOCTOR_H
#define _MAPS_CHARACTERS_GHOSTDOCTOR_H

extern s_AnimInfo GHOST_DOCTOR_ANIM_INFOS[];

/*s_AnimInfo GHOST_DOCTOR_ANIM_INFOS[] = {
    { Anim_BlendLinear, ANIM_STATUS(0, false), false, ANIM_STATUS(0, false), { Q12(0) }, NO_VALUE, 0 },
    { Anim_PlaybackLoop, ANIM_STATUS(0, true), false, NO_VALUE, { Q12(30) }, NO_VALUE, 1 },
    { Anim_BlendLinear, ANIM_STATUS(1, false), false, ANIM_STATUS(1, true), { Q12(5) }, NO_VALUE, 0 },
    { Anim_PlaybackLoop, ANIM_STATUS(1, true), false, NO_VALUE, { Q12(15) }, 0, 15 }
};*/

void GhostDoctor_Update(s_SubCharacter* ghostDoc, s_AnmHeader* anmHdr, GsCOORDINATE2* boneCoords);

void GhostDoctor_AnimUpdate(s_SubCharacter* ghostDoc, s_AnmHeader* anmHdr, GsCOORDINATE2* boneCoords);

/** @brief Updates the transform of the `coord` matrix to the character's position, converting
 * from world-space to geometry space.
 *
 * @param chara Reference character.
 * @param coord Output coord to update.
 */
void Character_CoordTransformUpdate(s_SubCharacter* ghostDoc, GsCOORDINATE2* boneCoords);

void GhostDoctor_Init(s_SubCharacter* ghostDoc);

void func_800D8C00(s_SubCharacter* ghostDoc, GsCOORDINATE2* boneCoords);

#endif
