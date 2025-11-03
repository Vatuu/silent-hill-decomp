#ifndef _MAPS_MAP4_S03_H
#define _MAPS_MAP4_S03_H

#define HAS_PlayerState_Unk52
#define HAS_PlayerState_Unk123
#define HAS_PlayerState_Unk128
#define HAS_PlayerState_Unk129
#define KEYFRAME_PlayerState_Unk123 877

extern s_AnimInfo TWINFEELER_ANIM_INFOS[];

extern s32 D_800DB914; // } RNG related values?
extern s32 D_800DB918; // }

void func_800D0C50(SVECTOR* rot, MATRIX* mat);

void Ai_Twinfeeler_TextureLoad();
void func_800D354C(VECTOR3*);
u8   func_800D3B1C(void);
void func_800D3B44(s32);
void func_800D3B74(s_SubCharacter* chara);
void func_800D3CBC(s_SubCharacter* chara);
bool Ai_Twinfeeler_Init(s_SubCharacter* chara);
void func_800D3E58(s_SubCharacter*);
void func_800D4028(s_SubCharacter* chara);
void func_800D46E0(VECTOR3* vec0, VECTOR3* vec1);
u32  func_800D4DD8(void);
void func_800D53B0(s_SubCharacter* chara, GsCOORDINATE2* coords);
void func_800D54B4(s_SubCharacter*, GsCOORDINATE2*);
void func_800D55C8(s_SubCharacter*);
void func_800D5888(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* coords);
void func_800D59EC(s_SubCharacter*, GsCOORDINATE2*);
void func_800D5B6C(s_SubCharacter* chara, GsCOORDINATE2* coords);
void func_800D5BC8(s_SubCharacter* chara, GsCOORDINATE2* coords);
void func_800D5DF4(s_SubCharacter* chara, GsCOORDINATE2* coords);
void func_800D5E30(s_SubCharacter*, GsCOORDINATE2*);
void Ai_Twinfeeler_Update(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* coords);

/** @brief Handles a First Aid Kit or Rifle Shells item pickup event. */
void MapEvent_CommonItemTake(void);

void func_800D6704(void);

s32 func_800D7394(void);

#endif
