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

#define MAP_ROOM_MIN_X Q12(-160.0f)
#define MAP_ROOM_MAX_X Q12(160.0f)
#define MAP_ROOM_MIN_Z Q12(-80.0f)
#define MAP_ROOM_MAX_Z Q12(200.0f)

extern s_AnimInfo CAT_ANIM_INFOS[];

extern SVECTOR3 D_800CB7D4; // Empty
extern VECTOR3 D_800CB7DC;
extern VECTOR3 D_800CB7E8;
extern u8 D_800DC9FC;
extern u16 D_800DCA04[42];
extern s32 D_800DD4FC;
extern s32 D_800DD57C;
extern s_WorldObjectPos g_CommonWorldObjectPoses[5]; // 0x800DD518
extern s_WorldObjectDesc g_WorldObject0;
extern s_WorldObjectDesc g_WorldObject1;
extern s_WorldObjectDesc g_WorldObject2;
extern s_WorldObjectDesc g_WorldObject3;
extern VECTOR3 D_800DF000;
extern VECTOR3 D_800DF010;
extern s_WorldObject_0 g_WorldObject4;
extern s_WorldObject_0 g_WorldObject5;
extern s_WorldObject_0 g_WorldObject6;
extern VECTOR3         D_800DF080;
extern s_WorldObjectDesc g_WorldObject7;
extern s_WorldObjectDesc g_WorldObject8;
extern s_WorldObjectDesc g_WorldObject9;
extern s_WorldObject_0   g_CommonWorldObjects[6]; // 800DF120
extern s_MapHdr_field_4C D_800DD5B0[300];
extern s_MapOverlayHeader_7C D_800DEE50;

void Ai_Cat_Update(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* coords);

void func_800D72B0(void);

void func_800D72DC(void);

void func_800D7830(void);

void func_800D7EEC(void);

void func_800D857C(void);

void func_800D8794(void);

void func_800D9EC4(void);

void func_800D7F18(bool);

void func_800D7864(void);

void func_800D76F4(void);

void func_800CB7F4(void);
#endif
