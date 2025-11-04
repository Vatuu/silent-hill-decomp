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

#define MAP_ROOM_MIN_X Q12(-200.0f)
#define MAP_ROOM_MAX_X Q12(200.0f)
#define MAP_ROOM_MIN_Z Q12(0.0f)
#define MAP_ROOM_MAX_Z Q12(120.0f)

void func_800D1004(s32 arg0);

/** @brief Handles a Health Drink or Shotgun Shells item pickup event. */
void MapEvent_CommonItemTake(void);

void func_800D1A84(void);

void func_800D1ACC(void);

void func_800D2640(void);

#endif
