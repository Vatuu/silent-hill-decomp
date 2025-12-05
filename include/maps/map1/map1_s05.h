#ifndef _MAPS_MAP1_S05_H
#define _MAPS_MAP1_S05_H

#define MAP_ROOM_MIN_X Q12(-160.0f)
#define MAP_ROOM_MAX_X Q12(160.0f)
#define MAP_ROOM_MIN_Z Q12(-80.0f)
#define MAP_ROOM_MAX_Z Q12(200.0f)

extern s32 D_800D587C;

extern s_MapHeader_field_5C D_800D8568; // TODO: `sharedData_800DD180_3_s05`?

extern u16 D_800D86F8[2];
extern u8  D_800D86FC[2];

extern u8 D_800D5C3C;

extern u8 D_800D5D11;

extern s8 D_800D86FE;

extern s_WorldObjectDesc g_WorldObject0; //800D8698
extern s_WorldObjectDesc g_WorldObject1; //800D86C8

void func_800CAAD0(void);

void func_800D494C(void);

void func_800D49AC(void);

void func_800D4D1C(void);

void func_800D525C(void);

#endif
