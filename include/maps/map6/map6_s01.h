#ifndef _MAPS_MAP6_S01_H
#define _MAPS_MAP6_S01_H

#define HAS_PlayerState_Unk51
#define HAS_PlayerState_Unk131
#define HAS_PlayerState_Unk52
#define HAS_PlayerState_Unk70
#define HAS_PlayerState_Unk71
#define HAS_PlayerState_Unk132
#define HAS_PlayerState_Unk113
#define KEYFRAME_PlayerState_Unk113 700

#define HAS_Chara_Cybil
#define HAS_Chara_Dahlia
#define MAP_CHARA_COUNT 2

#define MAP_ROOM_MIN_X Q12(-200.0f)
#define MAP_ROOM_MAX_X Q12(200.0f)
#define MAP_ROOM_MIN_Z Q12(0.0f)
#define MAP_ROOM_MAX_Z Q12(120.0f)

extern s32 D_800D4070;

extern u16 D_800D4074;

extern u16 D_800D4100;

extern u16 D_800D4108;

extern s_FsImageDesc D_800D410C;

extern DVECTOR D_800D4114[];

extern u8 D_800D416C;

extern u8 D_800D416D;

extern u8 D_800D416E;

extern VECTOR3 D_800D4174[];

extern s16 D_800D41B0;

/** Time. */
extern q19_12 D_800D41B4;

extern u8 D_800D5345;

extern VECTOR3 D_800D5354;

extern VECTOR3 D_800D5364;

extern u8 D_800D5370;

extern s8 D_800CBB54;

extern s_WorldObjectDesc D_800D5374;

extern s_WorldObjectDesc D_800D53A4[7];

extern s_WorldObject_0 g_CommonWorldObjects[6];
extern s_WorldObjectPose  g_CommonWorldObjectPoses[3]; // 0x800D4128

void func_800D0E78(s32 arg0);

void func_800D0EAC(void);

/** @brief Handles a Health Drink, Handgun Bullets, or Rifle Shells item pickup event. */
void MapEvent_CommonItemTake(void);

void func_800D13D8(void);

void func_800D236C(void);

void func_800D2658(void);

void func_800D2E6C(void);

void func_800D30DC(void);

#endif
