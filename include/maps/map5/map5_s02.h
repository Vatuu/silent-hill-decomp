#ifndef _MAPS_MAP5_S02_H
#define _MAPS_MAP5_S02_H

#define HAS_PlayerState_Unk51
#define HAS_PlayerState_Unk131
#define HAS_PlayerState_Unk52
#define HAS_PlayerState_Unk59
#define HAS_PlayerState_Unk60
#define HAS_PlayerState_Unk66
#define HAS_PlayerState_Unk70
#define HAS_PlayerState_Unk73
#define HAS_PlayerState_Unk153
#define HAS_PlayerState_Unk186
#define HAS_PlayerState_Unk164
#define HAS_PlayerState_Unk165
#define HAS_PlayerState_Unk166
#define KEYFRAME_PlayerState_Unk59  801
#define KEYFRAME_PlayerState_Unk60  816
#define KEYFRAME_PlayerState_Unk153 889

#define MAP_ROOM_MIN_X Q12(-200.0f)
#define MAP_ROOM_MAX_X Q12(200.0f)
#define MAP_ROOM_MIN_Z Q12(0.0f)
#define MAP_ROOM_MAX_Z Q12(120.0f)

extern u16 D_800D947C;

extern u8 D_800D94F4;

extern VECTOR3 D_800DA6CC;

extern VECTOR3 D_800DA6DC;

extern u8 D_800DA6E8;

extern s32 D_800DA6EC;

extern s16 D_800DA726;

extern s_WorldObjectDesc D_800DA72C;

void func_800D45B4(s32 arg0);

/** @brief Handles a Health Drink or Rifle Shells item pickup event. */
void MapEvent_CommonItemTake(void);

void func_800D4DF8(void);

void func_800D4E24(void);

void func_800D4E64(void);

void func_800D519C(void);

void func_800D5478(void);

void func_800D54A4(void);

void func_800D54D0(void);

void MapEvent_KaufmannBarFightCutscene(void);

#endif
