#ifndef _MAPS_MAP5_S01_H
#define _MAPS_MAP5_S01_H

#define HAS_PARTICLE_CASE_10
#define PARTICLE_CASE_COUNT 1

extern s_800F0158 D_800F0158[12];

extern u8 D_800F0170[4];

extern u8 D_800F0350[4];

extern s32 D_800F0354;

extern s32 D_800F0358;

extern s_WorldObject_0   g_CommonWorldObjects[6]; // D_800F3E70
extern s_WorldObjectDescNoRot g_WorldObject0; // D_800F3E10
extern s_WorldObjectDesc g_WorldObject1; // D_800F3E40
extern s_WorldObjectPose  g_CommonWorldObjectPoses[5]; // 0x800F018C
extern u8 D_800CCA84[]; // "HOOK_HID" + garbage after null byte
extern SVECTOR3 D_800CC938; // empty SVECTOR3, remove after all functions that use it are decompiled.

void func_800CD818(void);

/** @brief Handles a First Aid Kit, Health Drink, Handgun Bullets, or Rifle Shells item pickup event. */
void MapEvent_CommonItemTake(void);

/** @brief Puzzle event? Similar to M7S01 `func_800D94DC`. */
void func_800EBA40(void);

/** @brief Handles the ? map pickup event. */
void MapEvent_MapTake(void);

void func_800ECB58(void);

void func_800ECC8C(void);

#endif
