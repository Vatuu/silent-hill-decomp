#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "main/rng.h"
#include "maps/shared.h"
#include "maps/map2/map2_s03.h"

#include "maps/shared/sharedFunc_800CB6B0_0_s00_noParticles.h" // 0x800CA904

#include "maps/shared/sharedFunc_800D08B8_0_s00.h" // 0x800CAA6C

#include "maps/shared/sharedFunc_800D0A60_0_s00.h" // 0x800CABEC

#include "maps/shared/sharedFunc_800D0B18_0_s00.h" // 0x800CACA4

#include "maps/shared/sharedFunc_800D0E04_0_s00.h" // 0x800CAE08

#include "maps/shared/sharedFunc_800CFFD8_0_s01.h" // 0x800CAE28

#include "maps/shared/sharedFunc_800D0850_0_s01.h" // 0x800CB6A0

#include "maps/shared/sharedFunc_800CDAA8_0_s02.h" // 0x800CBA8C

#include "maps/shared/sharedFunc_800D1C38_0_s00.h" // 0x800CBD80

#include "maps/shared/sharedFunc_800D209C_0_s00.h" // 0x800CC1AC

#include "maps/shared/sharedFunc_800D20D8_0_s00.h" // 0x800CC1E8

#include "maps/shared/Player_ControlFreeze.h" // 0x800CC1F4

#include "maps/shared/Player_ControlUnfreeze.h" // 0x800CC354

#include "maps/shared/sharedFunc_800D23EC_0_s00.h" // 0x800CC52C

#include "maps/shared/sharedFunc_800D2C7C_0_s00.h" // 0x800CC534

#include "maps/shared/sharedFunc_800D2D2C_0_s00.h" // 0x800CC5E4

#include "maps/shared/sharedFunc_800D2D44_0_s00.h" // 0x800CC5FC

#include "maps/shared/sharedFunc_800D2D6C_0_s00.h" // 0x800CC624

#include "maps/shared/sharedFunc_800D2D84_0_s00.h" // 0x800CC63C

#include "maps/shared/sharedFunc_800D2DAC_0_s00.h" // 0x800CC664

#include "maps/shared/sharedFunc_800D2E50_0_s00.h" // 0x800CC708

#include "maps/shared/sharedFunc_800D2E60_0_s00.h" // 0x800CC718

void func_800CC724(void) {} // 0x800CC724

void func_800CC72C(void) {} // 0x800CC72C

void func_800CC734(void) {} // 0x800CC734

void func_800CC73C(void) {} // 0x800CC73C

void func_800CC744(void) {} // 0x800CC744

s32 func_800CC74C(void) // 0x800CC74C
{
    return 0;
}

void func_800CC754(void) {} // 0x800CC754

#include "maps/shared/sharedFunc_800D2EA4_0_s00.h" // 0x800CC75C

#include "maps/shared/sharedFunc_800D2EB4_0_s00.h" // 0x800CC76C

#include "maps/shared/sharedFunc_800D2EF4_0_s00.h" // 0x800CC7AC

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

