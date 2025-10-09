#ifndef _MAPS_MAP7_S02_H
#define _MAPS_MAP7_S02_H

void Ai_GhostDoctor_Update(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* coords);

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

void func_800DC120(void);

void func_800DF1F0(void);

void func_800DFA54(void);

void func_800DFA80(void);

void func_800DFAAC(void);

void func_800DFAE4(void);

void func_800DFB1C(void);

void func_800E0C30(void);

void func_800E0C5C(void);

void func_800E0C88(void);

void func_800E2DC0(void);

#endif