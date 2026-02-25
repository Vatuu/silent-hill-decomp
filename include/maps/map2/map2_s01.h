#ifndef _MAPS_MAP2_S01_H
#define _MAPS_MAP2_S01_H

#define HAS_PlayerState_Unk51
#define HAS_PlayerState_Unk131
#define HAS_PlayerState_Unk52
#define HAS_PlayerState_Unk111
#define HAS_PlayerState_Unk113
#define KEYFRAME_PlayerState_Unk113 723

#define HAS_Chara_Dahlia
#define MAP_CHARA_COUNT 1

// Config used by `Map_RoomIdxGet`.
#define MAP_ROOM_MIN_X    Q12(-200.0f)
#define MAP_ROOM_MAX_X    Q12(200.0f)
#define MAP_ROOM_MIN_Z    Q12(0.0f)
#define MAP_ROOM_MAX_Z    Q12(120.0f)

#define MAP_FIELD_4C_COUNT 200
#define MAP_BLOOD_SPLAT_COUNT_MAX 150

#include "maps/shared.h"

extern u16 g_MapMsgSounds[20];
extern q19_12 g_Timer0;
extern VECTOR3 g_CameraPositionTarget;
extern VECTOR3 g_CameraLookAtTarget;
extern u8 g_MapMsgSoundIdx;

void func_800CB010(s32 arg0, s32 arg1, s32 arg2);

void func_800CE858(s32 arg0);

void func_800CE88C(void);

void func_800CEB9C(void);

void func_800CEC30(void);

void func_800CED44(void);

void func_800CED88(void);

void func_800CF798(void);

void func_800CF7C4(void);

void Map_WorldObjectsInit(void);

void Map_WorldObjectsUpdate(void);

#endif
