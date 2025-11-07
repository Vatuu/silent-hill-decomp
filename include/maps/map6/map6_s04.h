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

#define HAS_Chara_MonsterCybil
#define HAS_Chara_Dahlia
#define HAS_Chara_Alessa
#define MAP_CHARA_COUNT 3

extern s_AnimInfo FLAUROS_ANIM_INFOS[];
extern s_AnimInfo PARASITE_ANIM_INFOS[];

extern s32 D_800EBA30;

extern VECTOR3 D_800ED590;

extern VECTOR3 D_800ED5A0;

extern u8 D_800ED5AC; // g_MapMsgSoundIdx

extern s32 D_800ED5B0;

extern s16 D_800ED5B6;

extern s_Model    g_Ai_MonsterCybil_ExtraModel; // Some kind of attachment or another `s_SubCharacter` instance?

extern s32 D_800ED588;
extern s32 D_800ED58C;

extern s_WorldObject_0 g_WorldObject0[2]; // 800ED600
extern s_WorldObject_0 g_WorldObject1[3]; // 800ED640
extern s_WorldObject_0 g_WorldObject2;    // 800ED6A0
extern s_WorldObject_0 g_WorldObject3;    // 800ED6C0
extern s_WorldObject_0 g_WorldObject4[2]; // 800ED6E0
extern s_WorldObject_0 g_WorldObject5;    // 800ED720
extern VECTOR3 D_800ED740;
extern s_WorldObject_0 g_WorldObject6[3]; // 800ED750
extern s_WorldObject_0 g_WorldObject7[2]; // 800ED7B0
extern s_WorldObject_0 g_WorldObject8;    // 800ED7F0
extern s_WorldObjectDesc g_WorldObject9;  // 800ED810
extern s8 D_800ED5AD;
extern s16 D_800ED5B4;
extern s8 D_800ED5B8;
extern s8 D_800ED5F0;
extern s8 D_800ED840;
extern s8 D_800ED841;
extern s8 D_800CC4C4;
extern s8 D_800CC4CC;
extern s8 D_800CC4D4;
extern s8 D_800CC4DC;
extern u16 D_800EBA34[23]; // g_MapMsgSounds
extern s16 D_800ED5B4;
extern s8 D_800ED5B8;
extern s32 D_800A9938;
extern s8 D_800CC4C4;
extern s8 D_800CC4CC;
extern s8 D_800CC4D4;

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

void func_800E5D44(void);

void func_800E3244(void);

void func_800E15FC(s_SubCharacter* player, s_SubCharacter* npc, s32);

void func_800E1CA0(void);

void func_800E1D50(void);
#endif
