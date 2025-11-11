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

extern u16 D_800E1EDC;

extern u8 D_800E1EE2;

extern s32 D_800E1EE4;

extern u16 D_800E1EE8;

extern s32 D_800E1FD4;

extern u8 D_800E1FD8;

extern s16 D_800E1FE4;

extern s_WorldObjectDesc D_800E57D8;      // "DOOR_HID", TODO: `g_WorldObject_Door`

extern s_WorldObjectDescNoRot D_800E58C8; // "BOX_HIDE", TODO: `g_WorldObject_Box`

/** @brief Lobby key use event. */
void MapEvent_LobbyKeyUse(void);

void func_800DA384(void);

void func_800DA8F8(void);

void func_800DA9D4(void);

void func_800DAA00(void);

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

#endif
