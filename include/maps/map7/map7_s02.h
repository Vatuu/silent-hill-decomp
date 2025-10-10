#ifndef _MAPS_MAP7_S02_H
#define _MAPS_MAP7_S02_H

typedef struct
{
    u8  field_0;
    u8  unk_1[1];
    s16 field_2;
} s_800EA494;

extern VECTOR3 D_800E839C[]; // Assumed type.

extern u16 D_800E9CE4;

extern u16 D_800E9CFC;

extern s8 D_800E9ECC;
extern u8 D_800E9ECD;

extern s_800EA494 D_800EA494;

extern VECTOR3 D_800EB694;
extern VECTOR3 D_800EB6A4;

extern u8  D_800EB6B0;
extern s32 D_800EB6B4;

extern s_WorldObjectPos D_800EB6E0; // Assumed type.

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

void func_800D9864(void);

void func_800DA248(void);

void func_800DAA4C(void);

void func_800DB21C(void);

void func_800DB2B0(void);

void func_800DB344(void);

void func_800DB498(void);

void func_800DB52C(void);

void func_800DB5C0(void);

void func_800DB67C(void);

void func_800DB738(void);

void func_800DBB34(void);

void func_800DC120(void);

void func_800DC778(void);

void func_800DF1F0(void);

void func_800DFA54(void);

void func_800DFA80(void);

void func_800DFAAC(void);

void func_800DFAE4(void);

void func_800DFB1C(void);

void func_800E0C30(void);

void func_800E0C5C(void);

void func_800E0C88(void);

void func_800E0CB4(void);

void func_800E2DC0(void);

#endif