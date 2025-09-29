#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "main/rng.h"
#include "maps/shared.h"

INCLUDE_ASM("asm/maps/map0_s02/nonmatchings/map0_s02", func_800CACF0);

#include "maps/shared/sharedFunc_800CBBBC_0_s00.h" // 0x800CB17C

#include "maps/shared/sharedFunc_800CBC94_0_s00.h" // 0x800CB254

#include "maps/shared/Particle_Update.h" // 0x800CB560

INCLUDE_ASM("asm/maps/map0_s02/nonmatchings/map0_s02", sharedFunc_800CEB24_0_s00); // 0x800CBBF4

#include "maps/shared/sharedFunc_800CF2A4_0_s01.h" // 0x800CC110

INCLUDE_ASM("asm/maps/map0_s02/nonmatchings/map0_s02", sharedFunc_800CEFD0_1_s02); // 0x800CC260

#include "maps/shared/sharedFunc_800CFFF8_0_s00.h" // 0x800CC628

#include "maps/shared/sharedFunc_800CE954_7_s03.h" // 0x800CC754

#include "maps/shared/sharedFunc_800D01BC_0_s00.h" // 0x800CC75C

#include "maps/shared/sharedFunc_800CF9A8_0_s01.h" // 0x800CC814

#include "maps/shared/sharedFunc_800D0700_0_s00.h" // 0x800CC89C

#include "maps/shared/sharedFunc_800D08B8_0_s00.h" // 0x800CCA54

#include "maps/shared/sharedFunc_800D0A60_0_s00.h" // 0x800CCBD4

#include "maps/shared/sharedFunc_800D0B18_0_s00.h" // 0x800CCC8C

#include "maps/shared/sharedFunc_800D0E04_0_s00.h" // 0x800CCE24

INCLUDE_ASM("asm/maps/map0_s02/nonmatchings/map0_s02", func_800CCE44);

INCLUDE_ASM("asm/maps/map0_s02/nonmatchings/map0_s02", func_800CD6BC);

#include "maps/shared/sharedFunc_800CDAA8_0_s02.h" // 0x800CDAA8

INCLUDE_ASM("asm/maps/map0_s02/nonmatchings/map0_s02", func_800CDD9C);

#include "maps/shared/sharedFunc_800D209C_0_s00.h" // 0x800CE1C8

#include "maps/shared/sharedFunc_800D20D8_0_s00.h" // 0x800CE204

#include "maps/shared/sharedFunc_800D20E4_0_s00.h" // 0x800CE210

#include "maps/shared/sharedFunc_800D2244_0_s00.h" // 0x800CE370

s32 func_800CE548(void) // 0x800CE548
{
    return 0;
}

#include "maps/shared/sharedFunc_800D2C7C_0_s00.h" // 0x800CE550

#include "maps/shared/sharedFunc_800D2D2C_0_s00.h" // 0x800CE600

#include "maps/shared/sharedFunc_800D2D44_0_s00.h" // 0x800CE618

#include "maps/shared/sharedFunc_800D2D6C_0_s00.h" // 0x800CE640

#include "maps/shared/sharedFunc_800D2D84_0_s00.h" // 0x800CE658

#include "maps/shared/sharedFunc_800D2DAC_0_s00.h" // 0x800CE680

#include "maps/shared/sharedFunc_800D2E50_0_s00.h" // 0x800CE724

#include "maps/shared/sharedFunc_800D2E60_0_s00.h" // 0x800CE734

void func_800CE740(void) {}

void func_800CE748(void) {}

void func_800CE750(void) {}

void func_800CE758(void) {}

void func_800CE760(void) {}

s32 func_800CE768(void) // 0x800CE768
{
    return 0;
}

void func_800CE770(void) {}

#include "maps/shared/sharedFunc_800D2EA4_0_s00.h" // 0x800CE778

#include "maps/shared/sharedFunc_800D2EB4_0_s00.h" // 0x800CE788

#include "maps/shared/sharedFunc_800D2EF4_0_s00.h" // 0x800CE7C8

#include "maps/shared/sharedFunc_800D929C_0_s00.h" // 0x800CE7DC

INCLUDE_ASM("asm/maps/map0_s02/nonmatchings/map0_s02", Map_RoomIdxGet); // 0x800CE7EC

void func_800CE884(s32 arg0) // 0x800CE884
{
    if (arg0 != 0)
    {
        func_800CE8B8();
        return;
    }

    func_800CE934();
}

void func_800CE8B8(void) // 0x800CE8B8
{
    switch (g_SavegamePtr->mapRoomIdx_A5)
    {
        case 5:
            func_8003640C(6);
            break;

        case 18:
            func_8003640C(!Savegame_EventFlagGet(EventFlag_379) ? 29 : 7);
            break;

        case 17:
            func_8003640C(7);
            break;
    }
}

INCLUDE_ASM("asm/maps/map0_s02/nonmatchings/map0_s02", func_800CE934);

void Gfx_LoadingScreen_StageString(void) {}
