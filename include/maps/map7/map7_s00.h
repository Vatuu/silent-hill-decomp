#ifndef _MAPS_MAP7_S00_H
#define _MAPS_MAP7_S00_H

#define HAS_PlayerState_Unk52
#define HAS_PlayerState_Unk53
#define HAS_PlayerState_Unk54
#define HAS_PlayerState_Unk55
#define HAS_PlayerState_Unk56
#define HAS_PlayerState_Unk57
#define HAS_PlayerState_Unk135
#define HAS_PlayerState_Unk136
#define HAS_PlayerState_Unk137
#define HAS_PlayerState_Unk138
#define HAS_PlayerState_Unk139

// Config used by `Map_RoomIdxGet`.
#define MAP_ROOM_MIN_X    Q12(-200.0f)
#define MAP_ROOM_MAX_X    Q12(200.0f)
#define MAP_ROOM_MIN_Z    Q12(-160.0f)
#define MAP_ROOM_MAX_Z    Q12(0.f)

extern s32 D_800D4370[4]; // Z pos table ?
extern s_WorldObject_0   g_WorldObject0[6]; // 800D4380
extern s_WorldObjectDesc g_WorldObject1;    // 800D4430
extern s16 D_800D4362;
extern u8 g_MapMsgSoundIdx;
extern VECTOR3 g_CutsceneCameraPosition;
extern VECTOR3 g_CutsceneCameraLookAt;
extern s32 g_Timer0;
extern s8 D_800D31D8;

extern u16 g_MapMsgSounds[24];

void func_800CFFE8(s32 arg0);

void func_800D001C(s32 arg0);

void func_800D0050(void);

void func_800D00D0(void);

#endif
