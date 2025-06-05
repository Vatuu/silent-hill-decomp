#ifndef _MAP4_S03_H
#define _MAP4_S03_H

extern s_AnimInfo g_Ai_Twinfeeler_AnimInfo[]; // 0x800DAE90

void Ai_Twinfeeler_TextureLoad();
void func_800D354C(VECTOR3*);
void func_800D3B44(s32);
void func_800D3B74(s_SubCharacter*);
void func_800D3CBC(s_SubCharacter*, s32, s32);
s32  Ai_Twinfeeler_Init(s_SubCharacter*);
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
