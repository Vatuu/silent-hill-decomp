#ifndef _MAPS_MAP3_S05_H
#define _MAPS_MAP3_S05_H

#define HAS_PlayerState_Unk52
#define HAS_PlayerState_Unk53
#define HAS_PlayerState_Unk54
#define HAS_PlayerState_Unk55
#define HAS_PlayerState_Unk56
#define HAS_PlayerState_Unk57
#define HAS_PlayerState_Unk59
#define HAS_PlayerState_Unk60
#define HAS_PlayerState_Unk69
#define HAS_PlayerState_Unk105
#define HAS_PlayerState_Unk81
#define HAS_PlayerState_Unk116
#define HAS_PlayerState_Unk141
#define KEYFRAME_PlayerState_Unk59 957
#define KEYFRAME_PlayerState_Unk60 972

#define MAP_ROOM_MIN_X Q12(-160.0f)
#define MAP_ROOM_MAX_X Q12(160.0f)
#define MAP_ROOM_MIN_Z Q12(-160.0f)
#define MAP_ROOM_MAX_Z Q12(160.0f)

extern u8 D_800DD528;
extern s16 D_800DD52A; // Time.
extern s16 D_800DACF0;
extern s16 D_800DACE8;
extern VECTOR3 D_800DD420;
extern VECTOR3 D_800DD430;
extern SVECTOR3 D_800DD440;
extern SVECTOR3 D_800DD448;
extern s16 D_800DD52A;
extern s_WorldObjectDesc      g_WorldObject0;
extern s_WorldObjectDescNoRot g_WorldObject1[6];
extern s_WorldObjectDesc      g_WorldObject2;
extern s_WorldObjectDesc      g_WorldObject3;
extern s_WorldObjectDesc      g_WorldObject4;
extern s_WorldObject_0        g_WorldObject5;
extern s_WorldObject_0        g_WorldObject6;
extern s_WorldObjectDesc      g_WorldObject7;
extern s_WorldObject_0   g_CommonWorldObjects[6];
extern s_WorldObjectPose g_CommonWorldObjectPoses[5];

s32 func_800D2E08(s32 arg0);

/** Puppet Nurse/Doctor related. */
bool func_800D437C(s_SubCharacter* chara);

void func_800D54DC(s32 arg0);

void func_800D5510(void);

void func_800D5934(void);

void func_800D5FC4(void);

void func_800D63C4(void);

void func_800D6BB4(void);

void func_800D6BE0(void);

void func_800D6CF0(void);

void func_800D719C(void);

void func_800D7280(void);

void func_800D8424(void);

void func_800D87AC(void);

void func_800D72AC(void);

#endif
