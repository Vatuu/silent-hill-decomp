#ifndef _MAPS_MAP1_S03_H
#define _MAPS_MAP1_S03_H

#include "maps/shared.h"
#define HAS_PlayerState_Unk52
#define HAS_PlayerState_Unk59
#define HAS_PlayerState_Unk60
#define HAS_PlayerState_Unk85
#define HAS_PlayerState_Unk86
#define HAS_PlayerState_Unk99
#define HAS_PlayerState_Unk100
#define HAS_PlayerState_Unk107
#define HAS_PlayerState_Unk108
#define HAS_PlayerState_Unk122
#define KEYFRAME_PlayerState_Unk59  903
#define KEYFRAME_PlayerState_Unk60  918
#define KEYFRAME_PlayerState_Unk122 1093

#define MAP_ROOM_MIN_X Q12(-160.0f)
#define MAP_ROOM_MAX_X Q12(160.0f)
#define MAP_ROOM_MIN_Z Q12(-80.0f)
#define MAP_ROOM_MAX_Z Q12(200.0f)

extern s_WorldObjectDesc g_WorldObject0; // 800E6180
extern s_WorldObjectDesc g_WorldObject1; // 800E61B0
extern s_WorldObjectDesc g_WorldObject2; // 800E61E0
extern s_WorldObjectDescNoRot g_WorldObject3; // 800E6210
extern s_WorldObjectDescNoRot g_WorldObject4; // 800E6240

extern SVECTOR3 D_800CBC04;
extern s32 D_800E20E8;
extern s16 D_800E20EC;
extern u8 D_800E20EE;


extern s_AnimInfo LOCKER_DEAD_BODY_ANIM_INFOS[8];

void Ai_LockerDeadBody_Update(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* coords);

void func_800DC2E4(void);

void func_800DC9A0(void);

void func_800DE828(void);

void func_800DE624(void);

#endif
