#ifndef _MAPS_MAP2_S04_H
#define _MAPS_MAP2_S04_H

// Config used by `Map_RoomIdxGet`.
#define MAP_ROOM_MIN_X    Q12(-200.0f)
#define MAP_ROOM_MAX_X    Q12(200.0f)
#define MAP_ROOM_MIN_Z    Q12(0.0f)
#define MAP_ROOM_MAX_Z    Q12(120.0f)
#define MAP_ROOM_STRIDE_Z 3

void func_800CCB30(s32 arg0);

void func_800CCF9C(void);

void func_800CD050(void);

void func_800CD088(void);

/** @brief Map pickup event. */
void func_800CD0D0(void);

void func_800CD0F8(void);

#endif
