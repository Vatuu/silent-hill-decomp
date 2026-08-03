#include "game.h"

#include <psyq/libetc.h>

#include "bodyprog/bodyprog.h"
#include "bodyprog/collision/collision.h"
#include "bodyprog/map/map.h"
#include "bodyprog/math/math.h"
#include "main/fsqueue.h"

u16 g_CollisionTriggerFlags;

void Collision_FlagsLocationUpdate(const s_SubCharacter* chara) // 0x8003BD48
{
    u16 collFlags;

    g_CollisionTriggerFlags = Collision_FlagsGet();
    collFlags               = g_CollisionTriggerFlags;

    switch (Map_TypeGet())
    {
        case MapType_THR:
            if (chara->position.vx >= Q12(191.6f) && chara->position.vx <= Q12(198.8f) &&
                chara->position.vz >= Q12(-96.0f) && chara->position.vz <= Q12(-90.3f))
            {
                collFlags = (collFlags & ~CollisionTriggerFlag_1) | CollisionTriggerFlag_2;
            }
            break;

        case MapType_SPR:
        case MapType_SPU:
            if (chara->position.vx >= Q12(-100.0f) && chara->position.vx <= Q12(-94.5f) &&
                chara->position.vz >= Q12(-70.3f)  && chara->position.vz <= Q12(-62.0f))
            {
                collFlags = (collFlags & ~CollisionTriggerFlag_1) | CollisionTriggerFlag_2;
            }
    }

    Collision_FlagsSet(collFlags);
}

void Collision_FlagsUpdate(void) // 0x8003BE28
{
    Collision_FlagsSet(g_CollisionTriggerFlags);
}
