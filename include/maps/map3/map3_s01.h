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

extern VECTOR3 D_800CB170;

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

#endif
