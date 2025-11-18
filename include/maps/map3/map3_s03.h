#ifndef _MAPS_MAP3_S03_H
#define _MAPS_MAP3_S03_H

#define HAS_PlayerState_Unk52
#define HAS_PlayerState_Unk59
#define HAS_PlayerState_Unk60
#define HAS_PlayerState_Unk146
#define HAS_PlayerState_Unk147
#define HAS_PlayerState_Unk154
#define KEYFRAME_PlayerState_Unk146 954
#define KEYFRAME_PlayerState_Unk147 988

#define MAP_ROOM_MIN_X Q12(-160.0f)
#define MAP_ROOM_MAX_X Q12(160.0f)
#define MAP_ROOM_MIN_Z Q12(-160.0f)
#define MAP_ROOM_MAX_Z Q12(160.0f)

extern u16 D_800D6B54;

extern u8 D_800D6BDA;

extern s_WorldObjectDescNoRot g_WorldObject_Dr[6];
extern s_WorldObjectDesc      g_WorldObject_Plate0;
extern s_WorldObjectDescNoRot g_WorldObject_Plate1;
extern s_WorldObjectDesc      g_WorldObject_Panel;
extern s_WorldObjectDesc      g_WorldObject_Blood0;
extern s_WorldObjectDesc      g_WorldObject_Lighter;
extern s_WorldObjectDescNoRot g_WorldObject_Alcohol;
extern s_WorldObjectDescNoRot g_WorldObject_Key;
extern s_WorldObject_0        g_WorldObject_Colors[4];
extern s_WorldObjectDesc      g_WorldObject_SavePad;
extern s8                     D_800D8428;
extern s_WorldObjectDesc      g_WorldObject_Blood1;
extern s_WorldObjectDescNoRot g_WorldObject_Blood2;
extern s_WorldObject_0        g_CommonWorldObjects[6];

s32 func_800CE398(s32 arg0);

void func_800D1210(s32 arg0);

void func_800D1244(void);

void func_800D151C(void);

void func_800D1774(void);

void func_800D17A0(void);

void func_800D17CC(void);

void func_800D26D0(void);

void func_800D2708(void);

void func_800D2740(void);

void func_800D2778(void);

void func_800D27F4(void);

void func_800D2C2C(void);

void func_800D2C58(void);

void func_800D2C84(void);

void func_800D2CB0(void);

void func_800D2CDC(void);

void func_800D30FC(void);

void func_800D3128(void);

void Map_WorldObjectsInit(void);

#endif
