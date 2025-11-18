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
extern SVECTOR3 D_800CC938; // Empty `SVECTOR3`, remove after all functions that use it are decompiled.
extern u16 D_800F0174;
extern s_FsImageDesc D_800F0178;
extern VECTOR3 D_800F0180;
extern u8 D_800F035C;
extern u8 D_800F035D;
extern q3_12 D_800F035E; // Time.
extern q19_12 D_800F0360;
extern VECTOR3 D_800F3DF0;
extern VECTOR3 D_800F3E00;
extern q19_12 D_800F3E0C; // Time.

void func_800CD818(void);

void func_800E9F08(s_SubCharacter* chara);

/** @brief Handles a First Aid Kit, Health Drink, Handgun Bullets, or Rifle Shells item pickup event. */
void MapEvent_CommonItemTake(void);

/** @brief Puzzle event? Similar to M7S01 `func_800D94DC`. */
void func_800EBA40(void);

/** @brief Handles the ? map pickup event. */
void MapEvent_MapTake(void);

void func_800EC2D8(void);

void func_800EC42C(void);

void func_800ECB58(void);

void func_800ECC8C(void);

#endif
