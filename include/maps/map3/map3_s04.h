#ifndef _MAPS_MAP3_S04_H
#define _MAPS_MAP3_S04_H

#define HAS_PlayerState_Unk51
#define HAS_PlayerState_Unk131
#define HAS_PlayerState_Unk52
#define HAS_PlayerState_Unk59
#define HAS_PlayerState_Unk60
#define HAS_PlayerState_Unk125
#define KEYFRAME_PlayerState_Unk59 957
#define KEYFRAME_PlayerState_Unk60 972

#define HAS_Chara_Lisa
#define MAP_CHARA_COUNT 1

#define MAP_ROOM_MIN_X Q12(-160.0f)
#define MAP_ROOM_MAX_X Q12(160.0f)
#define MAP_ROOM_MIN_Z Q12(-160.0f)
#define MAP_ROOM_MAX_Z Q12(160.0f)

extern s_WorldObjectDescNoRot g_WorldObject_Dr[6];
extern s_WorldObjectDescNoRot g_WorldObject_Plate;
extern s_WorldObjectDesc      g_WorldObject_SavePad;
extern s_WorldObjectModel        g_CommonWorldObjects[6];
extern s_WorldObjectPose      g_CommonWorldObjectPoses[2];

extern u16 D_800D599C;
extern VECTOR3 D_800D5A20;
extern VECTOR3 D_800D5A30;
extern u8 D_800D5A3C;
extern s32 D_800D5A40;
extern s16 D_800D5A48[3];
extern s16 D_800D5A4E;

void func_800D2470(void);

void func_800D2668(void);

void func_800D2E58(void);

void Map_WorldObjectsInit(void);

void func_800D3DA4(void);

void func_800D43B8(void);

#endif
