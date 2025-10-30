#ifndef _MAPS_MAP3_S01_H
#define _MAPS_MAP3_S01_H

#define HAS_PlayerState_Unk52
#define HAS_PlayerState_Unk59
#define HAS_PlayerState_Unk60
#define KEYFRAME_PlayerState_Unk59 957
#define KEYFRAME_PlayerState_Unk60 972

#define MAP_ROOM_MIN_X Q12(-40.0f)
#define MAP_ROOM_MAX_X Q12(160.0f)
#define MAP_ROOM_MIN_Z Q12(-80.0f)
#define MAP_ROOM_MAX_Z Q12(160.0f)

extern s_WorldObjectDescNoRot g_WorldObject0[6]; // 800D8494
extern s_WorldObjectDescNoRot g_WorldObject1;    // 800D8594
extern s_WorldObjectDesc      g_WorldObject2;    // 800D85C4
extern s_WorldObjectDescNoRot g_WorldObject3[2]; // 800D85F4
extern s_WorldObjectDesc      g_WorldObject5;    // 800D864C
extern s_WorldObjectDesc      g_WorldObject6;    // 800D8674
extern s_WorldObjectDesc      g_WorldObject7;    // 800D86A4
extern s_WorldObjectDesc      g_WorldObject8;    // 800D86D4
extern s_WorldObjectDesc      g_WorldObject9;    // 800D8704
extern s_WorldObject_0        g_WorldObjectA;    // 800D8760
extern s_WorldObjectPose      g_WorldObjectAPos; // 800D4CF0
extern s_WorldObject_0        g_CommonWorldObjects[6]; //800D8744

extern VECTOR3 D_800D4CE4; // used by func_800D2E54 only. For some reason it's not in RODATA
extern u8 D_800D8584;
extern u8 D_800D8734;


void func_800D1178(s32 arg0);

void func_800D14BC(void);

void func_800D1500(void);

void func_800D2720(void);

/** @brief Map pickup event. */
void func_800D274C(void);

/** @brief Map pickup event. */
void func_800D2774(void);

void func_800D279C(void);

void func_800D29A4(void);

void func_800D2A88(void);

void func_800D2AF4(void);

void func_800D2E54(void);

void MapEvent_Generator0(void);

#endif
