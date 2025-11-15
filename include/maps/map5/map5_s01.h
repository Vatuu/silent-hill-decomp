#ifndef _MAPS_MAP5_S01_H
#define _MAPS_MAP5_S01_H

#define HAS_PARTICLE_CASE_10
#define PARTICLE_CASE_COUNT 1

extern s_800F0158 D_800F0158[12];

extern u8 D_800F0170[4];

extern u8 D_800F0350[4];

extern s32 D_800F0354;

extern s32 D_800F0358;

void func_800CD818(void);

/** @brief Handles a First Aid Kit, Health Drink, Handgun Bullets, or Rifle Shells item pickup event. */
void MapEvent_CommonItemTake(void);

/** @brief Puzzle event? Similar to M7S01 `func_800D94DC`. */
void func_800EBA40(void);

/** @brief Handles the ? map pickup event. */
void MapEvent_MapTake(void);

#endif
