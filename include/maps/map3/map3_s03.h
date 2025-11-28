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
extern u8                     D_800D8428;
extern u8                     D_800D8490;
extern s_WorldObjectDesc      g_WorldObject_Blood1;
extern s_WorldObjectDescNoRot g_WorldObject_Blood2;
extern s_WorldObject_0        g_CommonWorldObjects[6];
extern s_WorldObjectPose      g_CommonWorldObjectPoses[5];

typedef struct {
    u16 sfxId;
    u16 vol;
} s_SfxPair;

extern s32 D_800D57E0[4];
extern s_SfxPair D_800D57F0[18];

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

void func_800CF7F4(s_SubCharacter* chara);

void func_800D429C(void);

void func_800CD9F4(s_SubCharacter*, s32);

s32 func_800CD980(s_SubCharacter* chara);

bool func_800CDDE8(s_SubCharacter* chara);

#endif
