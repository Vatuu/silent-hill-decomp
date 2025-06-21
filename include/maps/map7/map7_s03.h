#ifndef _MAP7_S03_H
#define _MAP7_S03_H

extern s32 D_800EDA00;

extern s_AnimInfo g_Ai_LittleIncubus_AnimInfo[]; // 0x800EAFA8
extern s_AnimInfo g_Ai_Incubus_AnimInfo[];       // 0x800EC808
extern s_AnimInfo g_Ai_Unknown23_AnimInfo[];     // 0x800ECE50

void Ai_BloodyIncubator_Update(s_SubCharacter* chara, s32 arg1, GsCOORDINATE2* coords);
void func_800D36F8(s_SubCharacter*, s32, GsCOORDINATE2*);
void func_800D3740(s_SubCharacter*, GsCOORDINATE2*);
void func_800D38D8(s_SubCharacter*, GsCOORDINATE2*);
void Ai_BloodyIncubator_Init(s_SubCharacter* chara);

void Ai_Incubator_Update(s_SubCharacter* chara, s32 arg1, GsCOORDINATE2* coords);
void func_800D3C38(s_SubCharacter*, s32, GsCOORDINATE2*);
void func_800D3C80(s_SubCharacter* chara, GsCOORDINATE2* coord);
void func_800D3E18(s_SubCharacter*, GsCOORDINATE2*);
void Ai_Incubator_Init(s_SubCharacter* chara);

void func_800DB608();
void func_800DD67C(VECTOR3*, s_SubCharacter*, GsCOORDINATE2*);
void func_800DD98C(s32);
s32  Ai_Incubus_Init(s_SubCharacter* chara, GsCOORDINATE2* coords);
void func_800DDBBC(s_SubCharacter*);
void func_800DEC74(s_SubCharacter*, GsCOORDINATE2*);
void func_800DED68(s_SubCharacter*, GsCOORDINATE2*);
void func_800DEE44(s_SubCharacter*);
void func_800DEE90(s_SubCharacter*, s32, GsCOORDINATE2*);
void func_800DEFE8(s_SubCharacter* chara, GsCOORDINATE2* coord);
void func_800DF044(s_SubCharacter*, GsCOORDINATE2*);
void func_800DF074(s_SubCharacter*);
void Ai_Incubus_Update(s_SubCharacter* chara, s32 arg1, GsCOORDINATE2* coords);

void func_800DFA14();
void func_800DFB2C(s32);
s32  Ai_Unknown23_Init(s_SubCharacter* chara, GsCOORDINATE2* coords);
void func_800DFCE4(s_SubCharacter*);
void func_800E05DC(s_SubCharacter*, GsCOORDINATE2*);
void func_800E0670(s_SubCharacter* chara, GsCOORDINATE2* coord);
void func_800E0728(s_SubCharacter*);
void func_800E0774(s_SubCharacter*, s32, GsCOORDINATE2*);
void func_800E0888(s_SubCharacter*, GsCOORDINATE2*);
void func_800E08E4(s_SubCharacter* chara, GsCOORDINATE2* coord);
void func_800E0914(s_SubCharacter* chara);
void Ai_Unknown23_Update(s_SubCharacter* chara, s32 arg1, GsCOORDINATE2* coords);

#endif
