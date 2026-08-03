#include "game.h"

#include "bodyprog/bodyprog.h"
#include "bodyprog/map/map.h"

s32 Map_TypeGet(void) // 0x8003BD2C
{
    return g_WorldGfxWork.mapInfo - MAP_INFOS;
}
