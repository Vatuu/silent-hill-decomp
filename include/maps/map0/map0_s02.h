#ifndef _MAPS_MAP0_S02_H
#define _MAPS_MAP0_S02_H

#include "types.h"

// Config used by `Map_RoomIdxGet`.
#define MAP_ROOM_MIN_X Q12(-200.0f)
#define MAP_ROOM_MAX_X Q12(200.0f)
#define MAP_ROOM_MIN_Z Q12(0.0f)
#define MAP_ROOM_MAX_Z Q12(120.0f)

s32 func_800CE548(void);

void func_800CE740(void);

void func_800CE748(void);

void func_800CE750(void);

void func_800CE758(void);

void func_800CE760(void);

s32 func_800CE768();

void func_800CE770(void);

void func_800CE884(s32 arg0);

void func_800CE8B8(void);

// TODO: Make shared function?
void Gfx_LoadingScreen_StageString();

/** @brief Handles a First Aid Kit, Health Drink, or Handgun Bullets item pickup event. */
void MapEvent_CommonItemTake(void);

void MapEvent_EmptyFunction();

/** @brief Handles the Gasoline Tank item pickup event. */
void MapEvent_GasolineTankItemTake(void);

/** @brief Handles the Katana item pickup event. */
void MapEvent_KatanaItemTake(void);

/** @brief Handles the Channeling Stone item pickup event. */
void MapEvent_ChannelingStoneItemTake(void);

void Map_WorldObjectsInit(void);

void Map_WorldObjectsUpdate(void);

#endif
