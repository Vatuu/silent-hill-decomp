#ifndef _MAPS_MAP7_S00_H
#define _MAPS_MAP7_S00_H

#define HAS_PlayerState_Unk52
#define HAS_PlayerState_Unk53
#define HAS_PlayerState_Unk54
#define HAS_PlayerState_Unk55
#define HAS_PlayerState_Unk56
#define HAS_PlayerState_Unk57
#define HAS_PlayerState_Unk135
#define HAS_PlayerState_Unk136
#define HAS_PlayerState_Unk137
#define HAS_PlayerState_Unk138
#define HAS_PlayerState_Unk139

#define HAS_Chara_Lisa
#define MAP_CHARA_COUNT 1

// Config used by `Map_RoomIdxGet`.
#define MAP_ROOM_MIN_X Q12(-200.0f)
#define MAP_ROOM_MAX_X Q12(200.0f)
#define MAP_ROOM_MIN_Z Q12(-160.0f)
#define MAP_ROOM_MAX_Z Q12(0.f)

#define MAP_FIELD_4C_COUNT 200
#define MAP_BLOOD_SPLAT_COUNT_MAX 150

#include "maps/shared.h"

extern s32 D_800D4370[4]; // Z position table?

extern SVECTOR3 D_800CB61C;
extern s16 D_800D4362;

extern s_WorldObjectModel   g_WorldObject0[6];
extern s_WorldObjectDesc g_WorldObject1;

extern s16 D_800D4362;
extern u8 g_MapMsgSoundIdx;
extern VECTOR3 g_CutsceneCameraPosition;
extern VECTOR3 g_CutsceneCameraLookAt;
extern s32 g_Timer0;
extern s8 D_800D31D8;

extern u16 g_MapMsgSounds[24];

extern u16 D_800D31C4;
extern s16 D_800D31DC[];

void func_800CFFE8(s32 arg0);

void func_800D001C(s32 arg0);

void func_800D0050(void);

void func_800D00D0(void);

void func_800D0994(void);

void func_800D0AC4(void);

void func_800D0B64(void);

void Map_WorldObjectsInit(void);

void Map_WorldObjectsUpdate(void);

#endif
