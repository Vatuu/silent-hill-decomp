#ifndef _MAPS_MAP5_S01_H
#define _MAPS_MAP5_S01_H

#define HAS_PARTICLE_CASE_10
#define PARTICLE_CASE_COUNT 1

extern s_FsImageDesc D_800A907C;

void func_800CD818(void);

/** @brief Handles a First Aid Kit, Health Drink, Handgun Bullets, or Rifle Shells item pickup event. */
void MapEvent_CommonItemTake(void);

/** @brief Handles the ? map pickup event. */
void MapEvent_MapTake(void);

#endif
