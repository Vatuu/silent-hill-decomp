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

#define MAP_ROOM_MIN_X Q12(-200.0f)
#define MAP_ROOM_MAX_X Q12(200.0f)
#define MAP_ROOM_MIN_Z Q12(0.0f)
#define MAP_ROOM_MAX_Z Q12(120.0f)

typedef struct
{
    s32 field_0;
    s32 field_4;
    s16 field_8;
    u8  unk_A;
    u8  field_B;
    u16 field_C;
    u16 field_E;
    s32 unk_10;
} s_800D41D4;

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

extern s32 D_800D41B4;

extern s_800D41D4 D_800D41D4[];

extern s8 D_800D5345;

extern VECTOR3 D_800D5354;

extern VECTOR3 D_800D5364;

extern u8 D_800D5370;

void func_800CBB60(VECTOR3* arg0, u16 arg1, u16 arg2, u32 arg3);

void func_800D0E78(s32 arg0);

void func_800D0EAC(void);

void func_800D13D8(void);

void func_800D236C(void);

void func_800D2658(void);

#endif
