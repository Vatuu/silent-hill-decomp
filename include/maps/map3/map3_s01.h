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

extern s_WorldObjectDescNoRot g_WorldObject0[6];
extern s_WorldObjectDescNoRot g_WorldObject1;
extern s_WorldObjectDesc      g_WorldObject2;
extern s_WorldObjectDescNoRot g_WorldObject3[2];
extern s_WorldObjectDesc      g_WorldObject5;
extern s_WorldObjectDesc      g_WorldObject6;
extern s_WorldObjectDesc      g_WorldObject7;
extern s_WorldObjectDesc      g_WorldObject8;
extern s_WorldObjectDesc      g_WorldObject9;
extern s_WorldObject_0        g_WorldObjectA;
extern s_WorldObjectPose      g_WorldObjectAPos;
extern s_WorldObject_0        g_CommonWorldObjects[6];

extern VECTOR3 D_800D4CE4; // Used by `func_800D2E54` only. For some reason it's not in RODATA.
extern u8 g_GeneratorMakeNoise; /** `bool` */
extern u8 D_800D8734;

void func_800D1178(s32 arg0);

void func_800D14BC(void);

void func_800D1500(void);

void func_800D1524(void);

void MapEvent_UnknownLiquidInteract(void);

/** @brief Handles the Plastic Bottle pickup event. */
void MapEvent_PlasticBottleTake(void);

/** @brief Handles the ? map pickup event. */
void MapEvent_MapTake0(void);

/** @brief Handles the ? map pickup event. */
void MapEvent_MapTake1(void);

void func_800D279C(void);

void MapEvent_Generator0(void);

void func_800D29A4(void);

void func_800D2A88(void);

void func_800D2AF4(void);

void func_800D2E54(void);

void MapEvent_UseBottleOnLiquid(void);

#endif
