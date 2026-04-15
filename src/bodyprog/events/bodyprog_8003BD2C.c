#include "game.h"

#include <psyq/libetc.h>

#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "main/fsqueue.h"

// ========================================
// NPC COLISIONS FLAGS UPDATE?
// ========================================

s32 Map_TypeGet(void) // 0x8003BD2C
{
    return g_WorldGfxWork.mapInfo_0 - MAP_INFOS;
}

void func_8003BD48(const s_SubCharacter* chara) // 0x8003BD48
{
    u16 collFlags;

    g_CollisionFlags = Collision_FlagsGet();
    collFlags        = g_CollisionFlags;

    switch (Map_TypeGet())
    {
        case 0:
            if (chara->position.vx >= Q12(191.6f) && chara->position.vx <= Q12(198.8f) &&
                chara->position.vz >= Q12(-96.0f) && chara->position.vz <= Q12(-90.3f))
            {
                collFlags = (collFlags & ~CollisionFlag_1) | CollisionFlag_2;
            }
            break;

        case 3:
        case 4:
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
