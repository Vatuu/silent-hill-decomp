#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "main/rng.h"
#include "maps/shared.h"
#include "maps/map2/map2_s03.h"

#include "maps/shared/sharedFunc_800CB6B0_0_s00_noParticles.h" // 0x800CA904

#include "maps/shared/Player.h"

#include "maps/shared/sharedFunc_800D929C_0_s00.h" // 0x800CC7C0

#include "maps/shared/Map_RoomIdxGet.h" // 0x800CC7D0

void func_800CCA1C(void) // 0x800CCA1C
{
    s32 flags;
    s32 mapRoomIdx;

    mapRoomIdx = g_SavegamePtr->mapRoomIdx_A5;
    flags      = (g_SysWork.field_2388.field_154.field_0.field_0.s_field_0.field_0 & (1 << 1)) ? (1 << 2) : (1 << 1);

    switch (mapRoomIdx)
    {
        case 33:
            if (!Savegame_EventFlagGet(EventFlag_195))
            {
                if (Savegame_EventFlagGet(EventFlag_165))
                {
                    flags |= 1 << 4;
                }
            }
            break;

        case 37:
        case 38:
            flags = (g_SysWork.field_2388.field_154.field_0.field_0.s_field_0.field_0 & (1 << 1)) ? (1 << 1) : (1 << 0);
            break;

        case 27:
        case 30:
            flags |= 1 << 1;
            break;

        case 35:
            flags = (1 << 1) | (1 << 2);
            break;
    }

    if (flags & 8)
    {
        s8 temp_v0 = func_800364BC();
        D_800CCCAF = temp_v0;
    }

    func_80035F4C(flags, Q12(0.1f), &D_800CCCAC);
}

void func_800CCB24(void) {} // 0x800CCB24

void func_800CCB2C(void) {} // 0x800CCB2C

void func_800CCB34(void) {} // 0x800CCB34

const char* MAP_MESSAGES[] = {
#include "maps/shared/mapMsg_common.h"
    "\tNO_STAGE! ~E "
};

