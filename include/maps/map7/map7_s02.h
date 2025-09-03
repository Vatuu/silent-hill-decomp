#ifndef _MAP7_S02_H
#define _MAP7_S02_H

void Ai_GhostDoctor_Update(s_SubCharacter* chara, s32 arg1, GsCOORDINATE2* coords);

void func_800D8B64(s_SubCharacter*, s32, GsCOORDINATE2*);

/** @brief Updates the transform of the `coord` matrix to the character's position, converting
 * from world space to geometry space.
 *
 * @param chara Reference character.
 * @param coord Output coord to update.
 */
void Character_CoordTransformUpdate(s_SubCharacter* chara, GsCOORDINATE2* coord);

void Ai_GhostDoctor_Init(s_SubCharacter* chara);

void func_800D8C00(s_SubCharacter*, GsCOORDINATE2*);

void func_800D9864();

#endif