#ifndef _MAPS_MAPUTIL_H
#define _MAPS_MAPUTIL_H

/** @unused Map header `func_C` points to this, but nothing seems to call into it. */
s32 sharedFunc_800D929C_0_s00(void);

/** @brief Gets the room index corresponding to the current 2D position.
 *
 * @param x X position in Q19.12.
 * @param z Z position in Q19.12.
 * @return Room index.
 */
u8 Map_RoomIdxGet(s32 x, s32 z);

#endif
