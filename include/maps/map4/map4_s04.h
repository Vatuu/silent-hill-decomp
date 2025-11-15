#ifndef _MAPS_MAP4_S04_H
#define _MAPS_MAP4_S04_H

#define HAS_PlayerState_Unk51
#define HAS_PlayerState_Unk131
#define HAS_PlayerState_Unk52
#define HAS_PlayerState_Unk53
#define HAS_PlayerState_Unk117
#define HAS_PlayerState_Unk134
#define HAS_PlayerState_Unk135
#define KEYFRAME_PlayerState_Unk117 678

#define HAS_Chara_Lisa
#define MAP_CHARA_COUNT 1

#define MAP_ROOM_MIN_X Q12(-160.0f)
#define MAP_ROOM_MAX_X Q12(160.0f)
#define MAP_ROOM_MIN_Z Q12(-160.0f)
#define MAP_ROOM_MAX_Z Q12(160.0f)

extern u16 D_800D3778;

extern u8 D_800D37C1;

extern VECTOR3 D_800D6ED8;

extern VECTOR3 D_800D6EE8;

/** Time. */
extern q19_12 D_800D6EF4;

extern u8 D_800D6EF8;

extern s_WorldObjectDesc      g_WorldObjectSavepad; // 0x800D6F38
extern s_WorldObjectDescNoRot g_WorldObject0;       // 0x800D6F08
extern u8 D_800D335C[8];
extern u16 D_800D3364[60];

void func_800D143C(s32 arg0);

void func_800D1470(void);

void func_800D23E4(void);

void func_800D2D6C(void);

void func_800D2DF4(void);

void func_800D14B0(void);

#endif
