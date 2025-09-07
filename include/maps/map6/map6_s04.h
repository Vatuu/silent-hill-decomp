#ifndef _MAP6_S04_H
#define _MAP6_S04_H

extern s_AnimInfo FLAUROS_ANIM_INFOS[];
extern s_AnimInfo PARASITE_ANIM_INFOS[];
extern s_Model    g_Ai_MonsterCybil_ExtraModel; // Some kind of attachment or another `s_SubCharacter` instance?

void Ai_MonsterCybil_Update(s_SubCharacter* chara, s32 arg1, GsCOORDINATE2* coords);
void Ai_MonsterCybil_Init(s_SubCharacter*, s_Model*);
void func_800D8B14(s_SubCharacter*, s_Model*);
void func_800D8D7C(s_SubCharacter*, s_Model*, GsCOORDINATE2*);
void func_800D9790(s_SubCharacter*, s_Model*);
void func_800D99E4(s_SubCharacter*, s_Model*, s32, GsCOORDINATE2*);
void func_800D9AAC(s_SubCharacter*, s_Model*);
void func_800DB4CC(s_SubCharacter*, s_Model*, GsCOORDINATE2*);

void Ai_Flauros_Update(s_SubCharacter* chara, s_AnmHeader* anmHeader, GsCOORDINATE2* coords);
void Ai_Parasite_Update(s_SubCharacter* chara, s_AnmHeader* anmHeader, GsCOORDINATE2* coords);

#endif