#ifndef _MAP7_S03_H
#define _MAP7_S03_H

extern s32 D_800EDA00;

extern s_AnimInfo g_Ai_LittleIncubus_AnimInfo[]; // 0x800EAFA8
extern s_AnimInfo g_Ai_Incubus_AnimInfo[];       // 0x800EC808

void func_800DB608();
void func_800DD98C(s32);
s32  Ai_Incubus_Init(s_SubCharacter*, s32);
void func_800DDBBC(s_SubCharacter*);
void func_800DEC74(s_SubCharacter*, s32);
void func_800DED68(s_SubCharacter*, s32);
void func_800DEE44(s_SubCharacter*);
void func_800DEE90(s_SubCharacter*, s32, s32);
void func_800DEFE8(s_SubCharacter*, s32);
void func_800DF044(s_SubCharacter*, s32);
void func_800DF074(s_SubCharacter*);
void Ai_Incubus_Update(s_SubCharacter* chara, s32 arg1, s32 arg2);

#endif
