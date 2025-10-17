#ifndef _MAPS_MAP1_S03_H
#define _MAPS_MAP1_S03_H

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

extern s_AnimInfo LOCKER_DEAD_BODY_ANIM_INFOS[8];

void Ai_LockerDeadBody_Update(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* coords);

void func_800DC2E4(void);

void func_800DC9A0(void);

#endif
