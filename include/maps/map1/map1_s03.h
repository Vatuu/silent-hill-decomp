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

#define MAP_ROOM_MIN_X Q12(-160.0f)
#define MAP_ROOM_MAX_X Q12(160.0f)
#define MAP_ROOM_MIN_Z Q12(-80.0f)
#define MAP_ROOM_MAX_Z Q12(200.0f)

#define MAP_FIELD_4C_COUNT 300
#define MAP_BLOOD_SPLAT_COUNT_MAX 150

#include "maps/shared.h"

extern s_AnimInfo LOCKER_DEAD_BODY_ANIM_INFOS[8]; // 0x800E1410

extern SVECTOR D_800E1F74;
extern u16     D_800E1F7C[];

extern VECTOR3 D_800E1F88[];
extern VECTOR3 D_800E1FC4[];

extern u16 D_800E2000[1]; // g_MapMsgSounds
extern s_FsImageDesc D_800E2004;
extern VECTOR3 D_800E200C;
extern s16 D_800E2018;
extern q19_12 D_800E201C; // Time.
extern s_WorldObjectPose  g_CommonWorldObjectPoses[10]; // 0x800E2020
extern s32 D_800E20E8; // Angle.
extern s16 D_800E20EC;
extern u8 D_800E20EE;

extern u16 D_800E20F8;
extern u16 D_800E20FA;
extern s16 D_800E20FC;
extern s16 D_800E20FE;
extern u8  D_800E2100;
extern u8  D_800E2101;
extern u8 D_800E2102; // g_MapMsgSoundIdx

extern s_WorldObjectDesc g_WorldObject5; // 0x800E6130
extern VECTOR3 D_800E6160;
extern VECTOR3 D_800E6170;
extern s32 D_800E617C;
extern s_WorldObjectDesc g_WorldObject0; // 0x800E6180
extern s_WorldObjectDesc g_WorldObject1; // 0x800E61B0
extern s_WorldObjectDesc g_WorldObject2; // 0x800E61E0
extern s_WorldObjectDescNoRot g_WorldObject3; // 0x800E6210
extern s_WorldObjectDescNoRot g_WorldObject4; // 0x800E6240
extern s_WorldObjectDescNoRot g_WorldObject6; // 0x800E6270
extern s_WorldObjectDesc g_WorldObject7; // 0x800E62A0
extern u8 D_800E62D0;
extern s_WorldObjectModel   g_CommonWorldObjects[6]; // 0x800E62E0

extern u8 D_800E6388;
extern q19_12 D_800E638C; // Time?


typedef struct
{
    s32 vx_0;
    s32 vz_4;
    u16 field_8;
    s16 field_A;
    s16 field_C;
    s16 field_E;
    s16 field_10;
    s16 field_12;
    u8  idx_14;
    u8  unk_15;
    u8  unk_16;
} s_800E3A40;
extern s_800E3A40 D_800E3A40[];

void func_800CDCE0(s32 arg0, s32 arg1, s32 arg2);

void func_800CE0CC(s32 arg0);

bool func_800CE164(POLY_FT4** poly, s32 idx);

void Ai_LockerDeadBody_Update(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* coords);

void func_800DA7F4(void);

void func_800DA8B0(void);

void func_800DA950(void);

void func_800DAA28(void);

void func_800DABC4(void);

void func_800DAF18(void);

// `MapEvent_TheMonsterLurksBookRead`
void func_800DBEC8(void);

void func_800DC0F8(void);

void func_800DC2E4(void);

void func_800DC310(void);

void func_800DC780(void);

void func_800DC9A0(void);

void func_800DCB54(void);

void func_800DCDDC(void);

void Map_WorldObjectsInit(void);

void Map_WorldObjectsUpdate(void);

void func_800DE624(void);

void func_800DE828(void);

#endif
