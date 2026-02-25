#ifndef _MAPS_MAP4_S01_H
#define _MAPS_MAP4_S01_H

#define HAS_PlayerState_Unk51
#define HAS_PlayerState_Unk131
#define HAS_PlayerState_Unk52
#define HAS_PlayerState_Unk53
#define HAS_PlayerState_Unk69
#define HAS_PlayerState_Unk105
#define HAS_PlayerState_Unk72
#define HAS_PlayerState_Unk116
#define HAS_PlayerState_Unk118
#define HAS_PlayerState_Unk119
#define HAS_PlayerState_Unk120
#define HAS_PlayerState_Unk121
#define HAS_PlayerState_Unk124
#define HAS_PlayerState_Unk130
#define HAS_PlayerState_Unk140
#define HAS_PlayerState_Unk142
#define HAS_PlayerState_Unk153
#define HAS_PlayerState_Unk186
#define KEYFRAME_PlayerState_Unk69 678

#define HAS_Chara_Cybil
#define MAP_CHARA_COUNT 1

// Config used by `Map_RoomIdxGet`.
#define MAP_ROOM_MIN_X Q12(-200.0f)
#define MAP_ROOM_MAX_X Q12(200.0f)
#define MAP_ROOM_MIN_Z Q12(0.0f)
#define MAP_ROOM_MAX_Z Q12(120.0f)

#define MAP_FIELD_4C_COUNT 450
#define MAP_BLOOD_SPLAT_COUNT_MAX 100

#include "maps/shared.h"

extern u16 g_MapMsgSounds[84];
extern u16 g_MapMsgSounds1[4];
extern u16 g_MapMsgSounds2[2];
extern u8 g_MapMsgSoundIdx;
extern u8 g_MapMsgSoundIdx1;
extern u8 g_MapMsgSoundIdx2;

extern u16 D_800D5ACC;

extern s32 g_Timer2;

extern u8 D_800D5AEB;

extern s32 g_Timer0;

extern u8 D_800D5AF0;

extern s32 g_Timer1;

extern u8 D_800D5AF8;

extern u8 D_800D5AF9;

extern s32 D_800D5AFC;

extern s32 D_800D5B00;

extern s16 D_800D5B04;

extern u8 D_800D5B06;

extern s16 D_800D7F30;

extern VECTOR3 g_CutsceneCameraPosition;
extern VECTOR3 g_CutsceneCameraLookAt;

extern s_WorldObjectDescNoRot WorldObject_D_800D7FF0;

extern u8 D_800D8018;

extern s_WorldObjectDesc      WorldObject_D_800D8020;
extern s_WorldObjectDesc      WorldObject_D_800D8050;
extern s_WorldObjectPose      WorldObject_D_800D8070;
extern s_WorldObjectPose      WorldObject_D_800D8090;
extern s_WorldObjectDesc      WorldObject_D_800D80B0;
extern s_WorldObjectDescNoRot WorldObject_D_800D80E0[2];

/** Time. */
extern s16 D_800D5AE8;

void func_800D1B78(s32 arg0);

void func_800D1FE8(void);

void func_800D1FF0(void);

void func_800D2F74(void);

void func_800D3420(void);

void func_800D496C(void);

void func_800D4998(void);

void Map_WorldObjectsInit(void);

void Map_WorldObjectsUpdate(void);

void func_800D2408(void);

void func_800D4410(void);

void func_800CC2C4(s32 arg0, s32 arg1);

#endif
