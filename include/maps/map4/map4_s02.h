#ifndef _MAPS_MAP4_S02_H
#define _MAPS_MAP4_S02_H

#define MAP_ROOM_MIN_X Q12(-240.0f)
#define MAP_ROOM_MAX_X Q12(240.0f)
#define MAP_ROOM_MIN_Z Q12(-120.0f)
#define MAP_ROOM_MAX_Z Q12(240.0f)

extern s_WorldObjectDescNoRot g_WorldObject_Kidn04;

extern s_WorldObjectModel g_WorldObject_Fan0;

extern u8 D_800F13AC;

extern u16 D_800ED8B0[16];

extern s_Bgm_Update D_800ED418;

extern s32 D_800ED420;

extern s_Bgm_Update D_800ED424;

extern u16 D_800ED42C[];

extern s_Bgm_Update D_800ED458;

void Map_WorldObjectsInit(void);

void func_800EA3F0(void);

#endif
