#ifndef _MAPS_MAP2_S00_H
#define _MAPS_MAP2_S00_H

#define HAS_PlayerState_Unk52
#define HAS_PlayerState_Unk59
#define HAS_PlayerState_Unk60
#define KEYFRAME_PlayerState_Unk59 946
#define KEYFRAME_PlayerState_Unk60 961

#define MAP_ROOM_MIN_X Q12(-320.0f)
#define MAP_ROOM_MAX_X Q12(240.0f)
#define MAP_ROOM_MIN_Z Q12(-240.0f)
#define MAP_ROOM_MAX_Z Q12(400.0f)
#define MAP_HAS_SECONDARY_GRID

extern u8 D_800F1CA8[3]; // = { 0, 1, 2 }

void func_800E7D54(void);

void func_800E7E60(void);

void func_800E816C(void);

void func_800E8198(void);

/** @brief Map pickup event. */
void func_800E81C4(void);

void func_800E81EC(void);

void func_800E9A0C(void);

void func_800E9CB4(void);

void func_800EB824(s32);

u8 func_800EE5A8(u32 arg0);

void func_800EB758(void);

void func_800EB79C(void);

void func_800EB7E0(void);

void func_800EA894(void);

s32 func_800EE518(void);

#endif
