#include "game.h"

#include <psyq/libetc.h>

#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "main/fsqueue.h"

// ========================================
// NPC COLISIONS FLAGS UPDATE?
// ========================================
/** TODO - Remove later
 * This code looks weird. By testing in game it seems like collision flags are shared
 * between player and the NPCs so it could be possible that this code execute arbitrarily.
 */

s32 Map_TypeGet(void) // 0x8003BD2C
{
    return g_WorldGfxWork.mapInfo - MAP_INFOS;
}

void func_8003BD48(const s_SubCharacter* chara) // 0x8003BD48
{
    u16 collFlags;

    g_CollisionFlags = Collision_FlagsGet();
    collFlags        = g_CollisionFlags;

    switch (Map_TypeGet())
    {
        case MapType_THR:
            if (chara->position.vx >= Q12(191.6f) && chara->position.vx <= Q12(198.8f) &&
                chara->position.vz >= Q12(-96.0f) && chara->position.vz <= Q12(-90.3f))
            {
                collFlags = (collFlags & ~CollisionFlag_1) | CollisionFlag_2;
            }
            break;

        case MapType_SPR:
        case MapType_SPU:
            if (chara->position.vx >= Q12(-100.0f) && chara->position.vx <= Q12(-94.5f) &&
                chara->position.vz >= Q12(-70.3f)  && chara->position.vz <= Q12(-62.0f))
            {
                collFlags = (collFlags & ~CollisionFlag_1) | CollisionFlag_2;
            }
    }

    Collision_FlagsSet(collFlags);
}

void func_8003BE28(void) // 0x8003BE28
{
    Collision_FlagsSet(g_CollisionFlags);
}
