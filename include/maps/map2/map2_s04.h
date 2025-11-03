#ifndef _MAPS_MAP2_S04_H
#define _MAPS_MAP2_S04_H

// Config used by `Map_RoomIdxGet`.
#define MAP_ROOM_MIN_X Q12(-200.0f)
#define MAP_ROOM_MAX_X Q12(200.0f)
#define MAP_ROOM_MIN_Z Q12(0.0f)
#define MAP_ROOM_MAX_Z Q12(120.0f)

s32 func_800CC7F4();

s32 func_800CCA14();

void func_800CCB30(s32 arg0);

void func_800CCF9C(void);

void func_800CD050(void);

void func_800CD088(void);

/** @brief Handles the ? map pickup event. */
void MapEvent_MapTake(void);

/** @brief Handles the Shotgun item pickup event. */
void MapEvent_ShotgunTake(void);

#endif
