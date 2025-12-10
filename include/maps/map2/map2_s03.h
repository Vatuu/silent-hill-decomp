#ifndef _MAPS_MAP2_S03_H
#define _MAPS_MAP2_S03_H

#define MAP_ROOM_MIN_X Q12(-320.0f)
#define MAP_ROOM_MAX_X Q12(240.0f)
#define MAP_ROOM_MIN_Z Q12(-240.0f)
#define MAP_ROOM_MAX_Z Q12(400.0f)
#define MAP_HAS_SECONDARY_GRID

void Gfx_LoadingScreen_StageString(void);

void Map_WorldObjectsInit(void);

void Map_WorldObjectsUpdate(void);

#endif
