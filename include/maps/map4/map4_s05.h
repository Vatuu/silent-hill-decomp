#ifndef _MAP4_S05_H
#define _MAP4_S05_H

extern s32 D_800D7858;

extern q3_12 D_800D785C;

extern s_AnimInfo FLOATSTINGER_ANIM_INFOS[];

extern s16 D_800DB898;

extern s16 D_800DB89C;

extern s16 D_800DB8A8[];

extern GsCOORDINATE2* D_800DB928;

void Ai_Floatstinger_Update(s_SubCharacter* chara, s32 arg1, GsCOORDINATE2* coords);
void Ai_Floatstinger_Init(s_SubCharacter* chara);
void func_800D1968(s_SubCharacter*);
void func_800D1B98(s_SubCharacter*);
void func_800D35F0(s_SubCharacter*);
void func_800D37E8(s_SubCharacter*, s32);
void func_800D3AD4(s_SubCharacter*);

#endif
