#ifndef _MAPS_MAP3_S00_H
#define _MAPS_MAP3_S00_H

#define HAS_PlayerState_Unk51
#define HAS_PlayerState_Unk131
#define HAS_PlayerState_Unk52
#define HAS_PlayerState_Unk72
#define HAS_PlayerState_Unk115

#define MAP_ROOM_MIN_X Q12(-40.0f)
#define MAP_ROOM_MAX_X Q12(160.0f)
#define MAP_ROOM_MIN_Z Q12(-80.0f)
#define MAP_ROOM_MAX_Z Q12(160.0f)

extern s_WorldObjectDescNoRot g_WorldObject0; // 800D5D00
extern s_WorldObjectDescNoRot g_WorldObject1[2]; // 800D5D30
extern s_WorldObjectDesc g_WorldObject2; // 800D5D80
extern s_WorldObjectDesc g_WorldObject3; // 800D5DB0
extern s_WorldObjectDesc g_WorldObject4; // 800D5DE0
extern s_WorldObjectDesc g_WorldObject5; // 800D5E10

void func_800CCE88();

s32 func_800CEF88();

void func_800CF180();

void func_800CF188();

void func_800CF190();

void func_800CF198();

void func_800CF1A0();

s32 func_800CF1A8();

void func_800CF1B0();

void func_800D0960(s32 arg0);

void func_800D0994();

void func_800D09D4();

void func_800D0B74();

void func_800D0CA4();

/** @brief Map pickup event. */
void func_800D0CD0(void);

#endif
