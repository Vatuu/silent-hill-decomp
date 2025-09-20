#ifndef _MAPS_MAP7_S02_H
#define _MAPS_MAP7_S02_H

void Ai_GhostDoctor_Update(s_SubCharacter* chara, s_AnmHeader* anmHeader, GsCOORDINATE2* coords);

void func_800D8B64(s_SubCharacter*, s_AnmHeader*, GsCOORDINATE2*);

/** @brief Updates the transform of the `coord` matrix to the character's position, converting
 * from world space to geometry space.
 *
 * @param chara Reference character.
 * @param coord Output coord to update.
 */
void Character_CoordTransformUpdate(s_SubCharacter* chara, GsCOORDINATE2* coord);

void Ai_GhostDoctor_Init(s_SubCharacter* chara);

/** Likely takes Harry character based on property usage. */
void func_800D8C00(s_SubCharacter* chara, GsCOORDINATE2* coord);

void func_800D9864();

#endif