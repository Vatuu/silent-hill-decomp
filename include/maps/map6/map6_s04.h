#ifndef _MAP6_S04_H
#define _MAP6_S04_H

extern s_AnimInfo g_Ai_Flauros_AnimInfo[];      // 0x800EAE80
extern s_AnimInfo g_Ai_Parasite_AnimInfo[];     // 0x800EAEC0
extern s_Model    g_Ai_MonsterCybil_ExtraModel; // 0x800ED540 - Some kind of attachment or another s_SubCharacter instance?

void Ai_MonsterCybil_Update(s_SubCharacter* chara, s32 arg1, s32 arg2);
void Ai_MonsterCybil_Init(s_SubCharacter*, s_Model*);
void func_800D8B14(s_SubCharacter*, s_Model*);
void func_800D8D7C(s_SubCharacter*, s_Model*, s32);
void func_800D9790(s_SubCharacter*, s_Model*);
void func_800D99E4(s_SubCharacter*, s_Model*, s32, s32);
void func_800D9AAC(s_SubCharacter*, s_Model*);
void func_800DB4CC(s_SubCharacter*, s_Model*, s32);

#endif