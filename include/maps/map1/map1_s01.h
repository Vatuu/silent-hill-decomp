#ifndef _MAPS_MAP1_S01_H
#define _MAPS_MAP1_S01_H

#define HAS_PlayerState_Unk52
#define HAS_PlayerState_Unk59
#define HAS_PlayerState_Unk60
#define HAS_PlayerState_Unk83
#define HAS_PlayerState_Unk85
#define HAS_PlayerState_Unk122
#define KEYFRAME_PlayerState_Unk59 873
#define KEYFRAME_PlayerState_Unk60 888

extern s_AnimInfo CAT_ANIM_INFOS[];

extern SVECTOR3 D_800CB7D4; // Empty
extern VECTOR3 D_800CB7DC;
extern VECTOR3 D_800CB7E8;

extern s32 D_800DD57C;
extern s_WorldObjectPos g_CommonWorldObjectsPos[5]; // 0x800DD518
extern s_WorldObjectDesc g_WorldObj0;
extern s_WorldObjectDesc g_WorldObj1;
extern s_WorldObjectDesc g_WorldObj2;
extern s_WorldObjectDesc g_WorldObj3;
extern VECTOR3 D_800DF000;
extern VECTOR3 D_800DF010;
extern s_WorldObject_0 g_WorldObj4;
extern s_WorldObject_0 g_WorldObj5;
extern s_WorldObject_0 g_WorldObj6;
extern VECTOR3         D_800DF080;
extern s_WorldObjectDesc g_WorldObj7;
extern s_WorldObjectDesc g_WorldObj8;
extern s_WorldObjectDesc g_WorldObj9;
extern s_WorldObject_0   g_CommonWorldObjects[6]; // 800DF120

void Ai_Cat_Update(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* coords);

void func_800D72B0(void);

void func_800D72DC(void);

void func_800D7830(void);

void func_800D7EEC(void);

void func_800D857C(void);

void func_800D8794(void);

void func_800D9EC4(void);
#endif
