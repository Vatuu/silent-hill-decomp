#ifndef _MAPS_MAP7_S01_H
#define _MAPS_MAP7_S01_H

#define HAS_PlayerState_Unk51
#define HAS_PlayerState_Unk131
#define HAS_PlayerState_Unk52
#define HAS_PlayerState_Unk53
#define HAS_PlayerState_Unk54
#define HAS_PlayerState_Unk55
#define HAS_PlayerState_Unk56
#define HAS_PlayerState_Unk57
#define HAS_PlayerState_Unk59
#define HAS_PlayerState_Unk60
#define HAS_PlayerState_Unk72
#define HAS_PlayerState_Unk145
#define HAS_PlayerState_Unk148
#define HAS_PlayerState_Unk155
#define HAS_PlayerState_Unk156
#define HAS_PlayerState_Unk157
#define HAS_PlayerState_Unk158
#define HAS_PlayerState_Unk167

// Config used by `Map_RoomIdxGet`.
#define MAP_ROOM_MIN_X    Q12(-200.0f)
#define MAP_ROOM_MAX_X    Q12(200.0f)
#define MAP_ROOM_MIN_Z    Q12(-160.0f)
#define MAP_ROOM_MAX_Z    Q12(0.f)
#define MAP_ROOM_STRIDE_Z 4

typedef struct
{
    u8 field_0;
    u8 field_1;
} s_800E1510;

typedef struct
{
    u8  field_0;
    u8  unk_1[1];
    s16 field_2;
} s_800E1690;

/** Character ID. (TODO: Move to `bodyprog.h`)*/
extern s8 D_800A9945;

extern VECTOR3 D_800E00CC[]; // Assumed type.

extern u16 D_800E14E8;

extern u16     D_800E1500;
extern VECTOR3 D_800E1504;

extern s_800E1510 D_800E1510[26];

extern u8 D_800E1544[5];

extern u16 D_800E154C[];

extern u16 D_800E155C;

extern s16 D_800E1560[];

extern u8 D_800E156E;

extern u8 D_800E1688[5];

extern u8 D_800E1670;
extern u8 D_800E1671;

extern s16 D_800E1678[4];
extern u8  D_800E1680;

extern u8 D_800E168D;

extern u16 D_800E168E;

extern s_800E1690 D_800E1690;

extern VECTOR3 D_800E2C48;
extern VECTOR3 D_800E2C58;

extern u8  D_800E2C64;
extern s32 D_800E2C68;

extern s_WorldObjectPos D_800E2C94; // Assumed type.

extern s32 D_800E2CA8;
extern s32 D_800E2CAC;

extern VECTOR3 D_800E2CD4;

extern s_WorldObjectDesc D_800E2CB8;

/** Decrementing timer. */
extern q3_12 D_800E2CE8;

s32 func_800D1630();

bool func_800D238C(s32 arg0);

s32 func_800D2EA0(void);

void func_800D6810(s32 arg0);

void func_800D6844(s32 arg0);

void func_800D6878(void);

void func_800D68F8(void);

void func_800D725C(void);

void func_800D7A60(void);

void func_800D8230(void);

void func_800D82C4(void);

void func_800D8358(void);

void func_800D83EC(void);

void func_800D84AC(void);

void func_800D8540(void);

void func_800D85D4(void);

void func_800D8668(void);

void func_800D8724(void);

void func_800D87E0(void);

void func_800D889C(void);

void func_800D8958(void);

void func_800D8984(void);

void func_800D89D8(void);

void func_800D8A04(void);

void func_800D8A30(void);

void func_800D8A5C(void);

void func_800D8DB4(void);

void func_800D8FCC(void);

void func_800D8FF8(void);

void func_800D93BC(void);

void func_800D93E8(void);

void func_800D9414(void);

void func_800D9440(void);

void func_800D946C(void);

void func_800D94A4(void);

void func_800D94DC(void);

void func_800D99DC(void);

void func_800D9A08(void);

void func_800D9C9C(void);

void func_800DAB64(void);

void func_800DAD7C(void);

void func_800DADA8(void);

void func_800DADD4(void);

void func_800DAE00(void);

void func_800DB13C(void);

void func_800DB1F0(void);

void func_800DB31C(void);

void func_800DB3D0(void);

void func_800DBDE0(void);

void func_800DC028(void);

void func_800DC080(void);

void func_800DEDA4(void);

#endif
