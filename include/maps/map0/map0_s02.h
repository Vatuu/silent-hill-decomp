#ifndef _MAP0_S02_H
#define _MAP0_S02_H

s32 func_800CE548(void);

s32 func_800CE768(void);

/** @brief Gets the room index corresponding to the current 2D position on the XZ plane.
 *
 * @param x X position in Q19.12.
 * @param z Z position in Q19.12.
 * @return Room index.
 */
u8 Map_RoomIdxGet(s32 x, s32 z);

void func_800CE884(s32 arg0);

/** Handles a first aid kit, health drink, or handgun bullets pickup event. */
void Event_HealthOrAmmoItemTake(void);

/** @brief Handles the gasoline tank pickup event. */
void Event_GasolineTankItemTake(void);

#endif
