#ifndef _MAPS_MAP0_S02_H
#define _MAPS_MAP0_S02_H

#include "types.h"

void func_800CD6BC(VECTOR3* vec0, VECTOR3* vec1);

s32 func_800CE548(void);

void func_800CE740(void);

void func_800CE748(void);

void func_800CE750(void);

void func_800CE758(void);

void func_800CE760(void);

s32 func_800CE768();

void func_800CE770(void);

/** @brief Gets the room index corresponding to the current 2D position.
 *
 * @param x X position in Q19.12.
 * @param z Z position in Q19.12.
 * @return Room index.
 */
u8 Map_RoomIdxGet(s32 x, s32 z);

void func_800CE884(s32 arg0);

void func_800CE8B8(void);

// TODO: Make shared function?
void Gfx_LoadingScreen_StageString();

/** @brief Handles a first aid kit, health drink, or handgun bullets pickup event. */
void MapEvent_CommonItemTake(void);

void MapEvent_EmptyFunction();

/** @brief Handles the gasoline tank pickup event. */
void MapEvent_GasolineTankItemTake(void);

/** @brief Handles the katana pickup event. */
void MapEvent_KatanaItemTake(void);

/** @brief Handles the channeling stone pickup event. */
void MapEvent_ChannelingStoneItemTake(void);

#endif
