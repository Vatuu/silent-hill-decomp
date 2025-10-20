#ifndef _MAPS_MAP6_S04_H
#define _MAPS_MAP6_S04_H

#define HAS_PlayerState_Unk51
#define HAS_PlayerState_Unk131
#define HAS_PlayerState_Unk52
#define HAS_PlayerState_Unk53
#define HAS_PlayerState_Unk70
#define HAS_PlayerState_Unk113
#define HAS_PlayerState_Unk123
#define HAS_PlayerState_Unk149
#define HAS_PlayerState_Unk150
#define HAS_PlayerState_Unk151
#define HAS_PlayerState_Unk152
#define HAS_PlayerState_Unk160
#define HAS_PlayerState_Unk161
#define HAS_PlayerState_Unk189
#define HAS_PlayerState_Unk162
#define HAS_PlayerState_Unk163
#define HAS_PlayerState_Unk167
#define HAS_PlayerState_Unk168
#define HAS_PlayerState_Unk185
#define HAS_PlayerState_Unk170
#define HAS_PlayerState_Unk188
#define KEYFRAME_PlayerState_Unk167 1347

extern s_AnimInfo FLAUROS_ANIM_INFOS[];
extern s_AnimInfo PARASITE_ANIM_INFOS[];

extern s32 D_800EBA30;

extern VECTOR3 D_800ED590;

extern VECTOR3 D_800ED5A0;

extern s8 D_800ED5AC;

extern s32 D_800ED5B0;

extern s16 D_800ED5B6;

extern s_800C4590 D_800ED4C0;

extern s_Model    g_Ai_MonsterCybil_ExtraModel; // Some kind of attachment or another `s_SubCharacter` instance?

extern s32 D_800ED588;
extern s32 D_800ED58C;

void Ai_MonsterCybil_Update(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* coords);
void Ai_MonsterCybil_Init(s_SubCharacter*, s_Model*);
void func_800D8B14(s_SubCharacter*, s_Model*);
void func_800D8D7C(s_SubCharacter*, s_Model*, GsCOORDINATE2*);
void func_800D9790(s_SubCharacter*, s_Model*);
void func_800D99E4(s_SubCharacter*, s_Model*, s_AnmHeader*, GsCOORDINATE2*);
void func_800D9AAC(s_SubCharacter*, s_Model*);
void func_800DB4CC(s_SubCharacter*, s_Model*, GsCOORDINATE2*);

void Ai_Flauros_Update(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* coords);
void Ai_Parasite_Update(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* coords);

void func_800DEA94(s32* arg0);

void func_800E01F4(void);

void func_800E02E0(void);

void func_800E10F8(void);

void func_800E1258(s32 arg0);

void func_800E1290(void);

void func_800E2CA0(void);

#endif
