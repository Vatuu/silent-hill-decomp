#ifndef _MAPS_MAP7_S02_H
#define _MAPS_MAP7_S02_H

#define HAS_PlayerState_Unk51
#define HAS_PlayerState_Unk131
#define HAS_PlayerState_Unk52
#define HAS_PlayerState_Unk59
#define HAS_PlayerState_Unk60
#define HAS_PlayerState_Unk72
#define HAS_PlayerState_Unk143
#define HAS_PlayerState_Unk144
#define HAS_PlayerState_Unk146
#define HAS_PlayerState_Unk147
#define HAS_PlayerState_Unk148
#define HAS_PlayerState_Unk155
#define HAS_PlayerState_Unk156
#define HAS_PlayerState_Unk157
#define HAS_PlayerState_Unk158
#define KEYFRAME_PlayerState_Unk59 862
#define KEYFRAME_PlayerState_Unk60 877

typedef struct
{
    u8  field_0;
    u8  unk_1[1];
    s16 field_2;
} s_800EA494;

extern VECTOR3 D_800E839C[]; // Assumed type. Pickup SFX positions?

extern u16 D_800E9CE4;

extern u16 D_800E9CFC;

extern VECTOR3 D_800E9D00;

extern u16 D_800E9D50;

extern u16 D_800E9D6C[];

extern s8 D_800E9ECC;
extern u8 D_800E9ECD;

/** Time. */
extern q3_12 D_800E9ED8;

extern s16 D_800E9EDA;

extern u8 D_800EA490;

extern s_800EA494 D_800EA494;

extern VECTOR3 D_800EB694;
extern VECTOR3 D_800EB6A4;

extern u8  D_800EB6B0;
extern s32 D_800EB6B4;

extern s_WorldObjectPose D_800EB6E0; // Assumed type.

extern s8 D_800EBAF4;

/** Timer. */
extern q3_12 D_800EBB94;

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

void func_800D97FC(s32 arg0);

void func_800D9830(s32 arg0);

void func_800D9864(void);

void func_800D98E4(void);

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

void func_800DCD00(void);

void func_800DD9E8(void);

void func_800DDEC8(void);

void func_800DF1F0(void);

void func_800DF21C(void);

void func_800DFA54(void);

void func_800DFA80(void);

void func_800DFAAC(void);

void func_800DFAE4(void);

void func_800DFB1C(void);

void func_800DFB48(void);

void func_800E0C30(void);

void func_800E0C5C(void);

void func_800E0C88(void);

void func_800E0CB4(void);

void func_800E0FF0(void);

void func_800E12E4(void);

void func_800E1398(void);

void func_800E1DAC(void);

void func_800E1FF4(void);

void func_800E2DC0(void);

#endif