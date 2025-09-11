#ifndef _MAPS_MAP4_S03_H
#define _MAPS_MAP4_S03_H

extern s_AnimInfo TWINFEELER_ANIM_INFOS[];

void Ai_Twinfeeler_TextureLoad();
void func_800D354C(VECTOR3*);
void func_800D3B44(s32);
void func_800D3B74(s_SubCharacter*);
void func_800D3CBC(s_SubCharacter*, s32, s32);
bool Ai_Twinfeeler_Init(s_SubCharacter* chara);
void func_800D3E58(s_SubCharacter*);
void func_800D53B0(s_SubCharacter*, GsCOORDINATE2*);
void func_800D54B4(s_SubCharacter*, GsCOORDINATE2*);
void func_800D55C8(s_SubCharacter*);
void func_800D5888(s_SubCharacter*, s32, GsCOORDINATE2*);
void func_800D59EC(s_SubCharacter*, GsCOORDINATE2*);
void func_800D5B6C(s_SubCharacter*, GsCOORDINATE2*);
void func_800D5BC8(s_SubCharacter*, GsCOORDINATE2*);
void func_800D5DF4(s_SubCharacter*, GsCOORDINATE2*);
void func_800D5E30(s_SubCharacter*, GsCOORDINATE2*);
void Ai_Twinfeeler_Update(s_SubCharacter* chara, s32 arg1, GsCOORDINATE2* coords);

#endif
