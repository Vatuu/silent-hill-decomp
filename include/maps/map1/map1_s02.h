#ifndef _MAPS_MAP1_S02_H
#define _MAPS_MAP1_S02_H

#define HAS_PlayerState_Unk52
#define HAS_PlayerState_Unk53
#define HAS_PlayerState_Unk54
#define HAS_PlayerState_Unk55
#define HAS_PlayerState_Unk56
#define HAS_PlayerState_Unk57
#define HAS_PlayerState_Unk59
#define HAS_PlayerState_Unk60
#define HAS_PlayerState_Unk74
#define HAS_PlayerState_Unk94
#define HAS_PlayerState_Unk95
#define HAS_PlayerState_Unk97
#define HAS_PlayerState_Unk98
#define HAS_PlayerState_Unk106
#define KEYFRAME_PlayerState_Unk59 903
#define KEYFRAME_PlayerState_Unk60 918

#define MAP_ROOM_MIN_X Q12(-160.0f)
#define MAP_ROOM_MAX_X Q12(160.0f)
#define MAP_ROOM_MIN_Z Q12(-80.0f)
#define MAP_ROOM_MAX_Z Q12(200.0f)

#define MAP_FIELD_4C_COUNT 200
#define MAP_BLOOD_SPLAT_COUNT_MAX 150

#include "maps/shared.h"

extern u16 D_800E1EDC;

extern u8 D_800E1EE2;

extern s32 D_800E1EE4;

extern u16 D_800E1EE8;

extern s_WorldObjectPose g_CommonWorldObjectPoses[11]; // 0x800E1EEC

extern s32 D_800E1FD4;

extern u8 D_800E1FD8;

extern DVECTOR D_800E1FDC; // Q19.12

extern q3_12 D_800E1FE0; // Y angle.

extern u8 D_800E1FE2;

extern u8 D_800E1FE3;

extern q3_12 D_800E1FE4;

extern s_WorldObjectDesc            g_WorldObject1; // 0x800E57D8 "DOOR_HID", TODO: `g_WorldObject_Door`
extern s_WorldObjectDesc            g_WorldObject4; // 0x800E5808
extern s_WorldObjectDesc            g_WorldObject5; // 0x800E5838
extern s_WorldObjectDesc            g_WorldObject6; // 0x800E5868
extern s_WorldObjectDesc            g_WorldObject7; // 0x800E5898
extern s_WorldObjectDescNoRot       g_WorldObject0; // 0x800E58C8 "BOX_HIDE", TODO: `g_WorldObject_Box`
extern s_WorldObjectModel              g_WorldObjectC; // 0x800E58F8
extern VECTOR3                      g_ObjPosC[2]; // 0x800E5918
extern SVECTOR                      g_ObjRotC[2]; // 0x800E5938
extern s_WorldObjectDesc            g_WorldObject3; // 0x800E5948
extern s_WorldObjectDescNoRot       g_WorldObjectD; // 0x800E5978
extern s_WorldObjectDesc            g_WorldObject8; // 0x800E59A8
extern s_WorldObjectDesc            g_WorldObject9; // 0x800E59D8
extern s_WorldObjectDesc            g_WorldObjectA; // 0x800E5A08
extern s_WorldObjectDesc            g_WorldObjectB; // 0x800E5A38
extern s_WorldObjectDesc            g_WorldObject2; // 0x800E5A68

extern u8 D_800E5A98;
extern u8 D_800E5A99;

extern s_WorldObjectModel              g_CommonWorldObjects[6]; // 0x800E5AA8

void func_800DA200(void);

/** @brief Lobby key use event. */
void MapEvent_LobbyKeyUse(void);

void func_800DA384(void);

void func_800DA8F8(void);

void func_800DA9D4(void);

void func_800DAA00(void);

/** @brief Game demo/trial end event. Shows "COMING SOON" image. */
void MapEvent_GameTrialOver(void);

void func_800DAD2C(void);

void func_800DB058(void);

void func_800DB310(void);

void func_800DB33C(void);

void func_800DB368(void);

void func_800DBB7C(void);

void func_800DBF88(void);

void func_800DBFC8(void);

void func_800DC1E0(void);

void func_800DCF00(void);

void func_800DD208(void);

void func_800DD420(void);

void Map_WorldObjectsInit(void);

void Map_WorldObjectsUpdate(void);

void func_800DEC88(void);

#endif
