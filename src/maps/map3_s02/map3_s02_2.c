#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "bodyprog/player_logic.h"
#include "main/rng.h"
#include "maps/shared.h"
#include "maps/map3/map3_s02.h"

#include "maps/shared/sharedFunc_800D88AC_0_s00.h" // 0x800CF404

#include "maps/shared/sharedFunc_800D88C0_0_s00.h" // 0x800CF418

#include "maps/shared/sharedFunc_800D8904_0_s00.h" // 0x800CF45C

#include "maps/shared/sharedFunc_800D891C_0_s00.h" // 0x800CF474

#include "maps/shared/sharedFunc_800D8928_0_s00.h" // 0x800CF480

#include "maps/shared/sharedFunc_800D893C_0_s00.h" // 0x800CF494

#include "maps/shared/sharedFunc_800D8950_0_s00.h" // 0x800CF4A8

#include "maps/shared/sharedFunc_800D8964_0_s00.h" // 0x800CF4BC

#include "maps/shared/sharedFunc_800D8A00_0_s00.h" // 0x800CF548

#include "maps/shared/sharedFunc_800D9064_0_s00.h" // 0x800CFBAC

#include "maps/shared/sharedFunc_800D9078_0_s00.h" // 0x800CFBC0

#include "maps/shared/sharedFunc_800D908C_0_s00.h" // 0x800CFBD4

#include "maps/shared/sharedFunc_800D9188_0_s00.h" // 0x800CFCD0

#include "maps/shared/Anim_StartKeyframeIdxGet.h" // 0x800CFD64

#include "maps/shared/sharedFunc_800D923C_0_s00.h" // 0x800CFD70

#include "maps/shared/sharedFunc_800D929C_0_s00.h" // 0x800CFDD0

#include "maps/shared/Map_RoomIdxGet.h" // 0x800CFDE0

void func_800CFE78(s32 arg0) // 0x800CFE78
{
    (arg0 != 0) ? func_800CFEAC() : func_800CFEEC();
}

void func_800CFEAC(void) // 0x800CFEAC
{
    func_8003640C(!Savegame_EventFlagGet(EventFlag_237) ? 8 : 2);
}

INCLUDE_RODATA("asm/maps/map3_s02/nonmatchings/map3_s02_2", D_800CA70C);

INCLUDE_ASM("asm/maps/map3_s02/nonmatchings/map3_s02_2", func_800CFEEC);

void func_800D017C(void) {}

#include "maps/shared/MapEvent_DoorJammed.h" // 0x800D0184

#include "maps/shared/MapEvent_DoorLocked.h" // 0x800D0218
void func_800D02AC(void) {}

const char* MAP_MESSAGES[] = {
    #include "maps/shared/mapMsg_common.h"
    "\tNothing_happens_when_the ~N\n\televator_button_is_pressed. ~E ",
    "\tIt's_locked! ~E "
};

const VECTOR3 D_800CAAF8 = { Q12(100.0f), Q12(-1.199951171875f), Q12(-127.199951171875f) };

void func_800D02B4(void) // 0x800D02B4
{
    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            sharedFunc_800D20E4_0_s00();
            ScreenFade_ResetTimestep();
            SysWork_StateStepIncrement(0);
            break;

        case 1:
            SysWork_StateStepIncrementAfterFade(0, false, 0, 0, false);
            SysWork_StateStepIncrement(0);

        case 2:
            SysWork_StateStepIncrementDelayed(Q12(1.0f), false);
            break;

        case 3:
            func_8005DC1C(Sfx_Unk1523, &D_800CAAF8, 128, 0);
            SysWork_StateStepIncrement(0);

        case 4:
            SysWork_StateStepIncrementDelayed(Q12(0.3f), false);

        default:
            sharedFunc_800D2244_0_s00(false);
            SysWork_StateSetNext(SysState_Gameplay);
            return;
    }
}

void func_800D03FC(void) // 0x800D03FC
{
    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            sharedFunc_800D20E4_0_s00();

            D_800D1FBC = Q12(100.0f);

            ScreenFade_ResetTimestep();
            SysWork_StateStepIncrement(0);
            break;

        case 1:
            func_8003ED74(7, 4);

            D_800D3154 = 0;

            Game_TurnFlashlightOff();
            SysWork_StateStepIncrementAfterFade(0, false, 0, Q12(0.0f), false);
            SysWork_StateStepIncrement(0);
            break;

        case 2:
            SysWork_StateStepIncrementDelayed(Q12(0.6f), false);
            break;

        case 3:
            Game_TurnFlashlightOn();
            SysWork_StateStepIncrement(0);

        default:
            sharedFunc_800D2244_0_s00(false);
            SysWork_StateSetNext(SysState_Gameplay);
            Savegame_EventFlagSet(EventFlag_236);
            break;
    }
}

#include "maps/shared/SysWork_StateStepIncrementAfterTime.h" // 0x800D0570

INCLUDE_ASM("asm/maps/map3_s02/nonmatchings/map3_s02_2", func_800D0608);

void func_800D0F8C(void) // 0x800D0F8C
{
    D_800D3154 = 1;
}

INCLUDE_ASM("asm/maps/map3_s02/nonmatchings/map3_s02_2", func_800D0F9C);

s16 func_800D1354(void)
{
    s32 cos0;
    s32 tmp0;
    s32 x;
    s32 z;
    s32 var1;
    s32 var;
    s32 x6;
    s32 z6;
    x = (g_SysWork.player_4C.chara_0.position_18.vx - Q12(95.2f));
    z = (g_SysWork.player_4C.chara_0.position_18.vz + Q12(140.0f));

    cos0 = Math_Cos(func_8005BF38((ratan2(x, z) - ratan2(0x4CCD, 0xCCCD))));
    x6 = Q12_TO_Q6(g_SysWork.player_4C.chara_0.position_18.vx - Q12(95.2f));
    z6 = Q12_TO_Q6(g_SysWork.player_4C.chara_0.position_18.vz + Q12(140.0f));

    tmp0 = FP_FROM((cos0 * 
                        Q6_TO_Q12((SquareRoot0(SQUARE(x6) + SQUARE(z6))))
                        ), Q12_SHIFT);
    var1 = FP_TO(tmp0, Q12_SHIFT) / Q6_TO_Q12(SquareRoot0(0xBAC52));
    var = MIN(var1, Q8(16.0f));

    if (var >= 0)
    {
        if (var1 > Q8(16.0f))
        {
            var1 = Q8(16.0f);
        }
        return Q8(16.0f) - var1;
    }
    return Q8(16.0f);
}

INCLUDE_RODATA("asm/maps/map3_s02/nonmatchings/map3_s02_2", D_800CAB4C);
