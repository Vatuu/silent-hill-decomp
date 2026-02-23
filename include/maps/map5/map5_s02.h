#ifndef _MAPS_MAP5_S02_H
#define _MAPS_MAP5_S02_H

#define HAS_PlayerState_Unk51
#define HAS_PlayerState_Unk131
#define HAS_PlayerState_Unk52
#define HAS_PlayerState_Unk59
#define HAS_PlayerState_Unk60
#define HAS_PlayerState_Unk66
#define HAS_PlayerState_Unk70
#define HAS_PlayerState_Unk73
#define HAS_PlayerState_Unk153
#define HAS_PlayerState_Unk186
#define HAS_PlayerState_Unk164
#define HAS_PlayerState_Unk165
#define HAS_PlayerState_Unk166
#define KEYFRAME_PlayerState_Unk59  801
#define KEYFRAME_PlayerState_Unk60  816
#define KEYFRAME_PlayerState_Unk153 889

#define HAS_Chara_Kaufmann
#define MAP_CHARA_COUNT 1

#define MAP_ROOM_MIN_X Q12(-200.0f)
#define MAP_ROOM_MAX_X Q12(200.0f)
#define MAP_ROOM_MIN_Z Q12(0.0f)
#define MAP_ROOM_MAX_Z Q12(120.0f)

#define MAP_FIELD_4C_COUNT 200
#define MAP_BLOOD_SPLAT_COUNT_MAX 150

#include "maps/shared.h"

extern u16 D_800D947C;

extern u8 D_800D94F4;

extern VECTOR3 D_800DA6CC;

extern VECTOR3 D_800DA6DC;

extern u8 D_800DA6E8;

extern s32 D_800DA6EC;

extern s_WorldObjectDesc g_WorldObject_BDoor1;
extern s_WorldObjectDesc g_WorldObject_06LBag;
extern s_WorldObjectModel   g_WorldObject_SavePad;
extern s_WorldObjectPose g_WorldObject_UnkPose0;
extern s_WorldObjectModel   g_WorldObject_Box[4];
extern VECTOR3           g_WorldObject_UnkPos[2];
extern s_WorldObjectDesc g_WorldObject_Key;
extern s_WorldObjectDesc g_WorldObject_Daly;
extern s_WorldObjectModel   g_WorldObject_Drug;
extern s_WorldObjectPose g_WorldObject_UnkPose1[3];
extern s_WorldObjectDesc g_WorldObject_Obj00;
extern s_WorldObjectModel   g_CommonWorldObjects[6];
extern s_WorldObjectPose  g_CommonWorldObjectPoses[4]; // 0x800D949C

void func_800D45B4(s32 arg0);

/** @brief Handles a Health Drink or Rifle Shells item pickup event. */
void MapEvent_CommonItemTake(void);

void func_800D4B58(void);

void func_800D4DF8(void);

void func_800D4E24(void);

void func_800D4E64(void);

void func_800D519C(void);

void func_800D5478(void);

void func_800D54A4(void);

void func_800D54D0(void);

void MapEvent_KaufmannBarFightCutscene(void);

void Map_WorldObjectsInit(void);

void Map_WorldObjectsUpdate(void);

#endif
