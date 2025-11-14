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

extern s_WorldObjectDescNoRot       g_WorldObject0;               // D_800E58C8
extern s_WorldObjectDesc            g_WorldObject1;               // D_800E57D8
extern s_WorldObjectDesc            g_WorldObject2;               // D_800E5A68
extern s_WorldObjectDesc            g_WorldObject3;               // D_800E5948
extern s_WorldObjectDesc            g_WorldObject4;               // D_800E5808
extern s_WorldObjectDesc            g_WorldObject5;               // D_800E5838
extern s_WorldObjectDesc            g_WorldObject6;               // D_800E5868
extern s_WorldObjectDesc            g_WorldObject7;               // D_800E5898
extern s_WorldObjectDesc            g_WorldObject8;               // D_800E59A8
extern s_WorldObjectDesc            g_WorldObject9;               // D_800E59D8
extern s_WorldObjectDesc            g_WorldObjectA;               // D_800E5A08
extern s_WorldObjectDesc            g_WorldObjectB;               // D_800E5A38
extern s_WorldObject_0              g_WorldObjectC;               // D_800E58F8
extern s_WorldObjectDescNoRot       g_WorldObjectD;               // D_800E5978
extern s_WorldObject_0              g_CommonWorldObjects[6];      // D_800E5AA8
extern s_WorldObjectPose            g_CommonWorldObjectPoses[11]; // D_800E1EEC
extern VECTOR3 g_ObjPosC[2]; // 800E5918
extern SVECTOR g_ObjRotC[2]; // 800E5938
extern u8 D_800E5A98;
extern u8 D_800E5A99;
extern SVECTOR3 D_800CBA44;

extern u16 D_800E1EDC;

extern u8 D_800E1EE2;

extern s32 D_800E1EE4;

extern u16 D_800E1EE8;

extern s32 D_800E1FD4;

extern u8 D_800E1FD8;

extern q3_12 D_800E1FE4;

//extern s_WorldObjectDesc D_800E57D8;      // "DOOR_HID", TODO: `g_WorldObject_Door`

//extern s_WorldObjectDescNoRot D_800E58C8; // "BOX_HIDE", TODO: `g_WorldObject_Box`

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

void func_800DCF00(void);

void func_800DD208(void);

void func_800DD420(void);

void func_800DEC88(void);

void func_800DD494(void);

void func_800DDA84(void);

#endif
