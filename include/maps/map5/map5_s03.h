#ifndef _MAPS_MAP5_S03_H
#define _MAPS_MAP5_S03_H

#define HAS_PlayerState_Unk51
#define HAS_PlayerState_Unk131
#define HAS_PlayerState_Unk52
#define HAS_PlayerState_Unk59
#define HAS_PlayerState_Unk60
#define HAS_PlayerState_Unk69
#define HAS_PlayerState_Unk105
#define HAS_PlayerState_Unk159
#define HAS_PlayerState_Unk169
#define HAS_PlayerState_Unk187
#define KEYFRAME_PlayerState_Unk59 801
#define KEYFRAME_PlayerState_Unk60 816
#define KEYFRAME_PlayerState_Unk69 828

#define HAS_Chara_Kaufmann
#define MAP_CHARA_COUNT 1

#define MAP_ROOM_MIN_X Q12(-200.0f)
#define MAP_ROOM_MAX_X Q12(200.0f)
#define MAP_ROOM_MIN_Z Q12(0.0f)
#define MAP_ROOM_MAX_Z Q12(120.0f)

extern s_WorldObjectDescNoRot g_WorldObject_Movaches;
extern s_WorldObject_0        g_WorldObject_SavePad;
extern s_WorldObject_0        g_CommonWorldObjects[6];
extern s_WorldObjectDesc      g_WorldObject_Mag;
extern s_WorldObjectPose      g_WorldObjectPose_SavePad[];

extern u16 D_800D3BDC;

extern s32 D_800D3C40;

extern s16 D_800D3C44; // Time.

extern VECTOR3 D_800D6F38;

extern VECTOR3 D_800D6F48;

extern u8 D_800D6F54;

extern s32 D_800D6F58;

void func_800D1004(s32 arg0);

void func_800D1340(void);

/** @brief Handles a Health Drink or Shotgun Shells item pickup event. */
void MapEvent_CommonItemTake(void);

void func_800D1628(void);

void func_800D1904(void);

void func_800D1A84(void);

void func_800D1ACC(void);

void func_800D1AF8(void);

void func_800D2640(void);

void func_800D2674(void);

void Map_WorldObjectsInit(void);

#endif
