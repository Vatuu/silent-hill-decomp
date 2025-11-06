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

//const u8 D_800CA70C[8] = {0x80, 0x70, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00};
extern const u8 D_800CA70C[];
INCLUDE_RODATA("asm/maps/map3_s02/nonmatchings/map3_s02_2", D_800CA70C);

void func_800CFEEC(void)
{

    u16 flags;
    q19_12 f_arg1;
    u8* dataPtr;
    u8 data[8];
    s32 roomId;

    dataPtr = D_800D1D14;
    roomId = g_SavegamePtr->mapRoomIdx_A5;

    if (g_GameWork.soundCmd_5B2 == 8)
    {
        f_arg1 = Q12(240.0f);
        flags = 0xFe;
    }
    else if (g_GameWork.soundCmd_5B2 == 0x20)
    {
        f_arg1 = Q12(0.15f);
        if (Savegame_EventFlagGet(EventFlag_338))
        {
            flags = 4;
            if (!Savegame_EventFlagGet(EventFlag_340))
            {
                flags = 2;
                if (Savegame_EventFlagGet(EventFlag_339))
                {
                    flags = 0xE;
                }
            }
        }
        else
        {
            flags = 1;
        }
    }
    else
    {
        flags = D_800D1D1C[roomId];
        f_arg1 = Q12(0.15f);
    
        switch (roomId)
        {
            case 0x17:
            case 0x1A:
            case 0x26:
            case 0x2D:
                if (!(Savegame_EventFlagGet(EventFlag_285) || Savegame_EventFlagGet(EventFlag_286)))
                {
                    flags = 0x1E;
                }
                else if (Savegame_EventFlagGet(EventFlag_285))
                {
                    Savegame_EventFlagSet(EventFlag_286);
                }
                break;
    
            case 0x5:
            case 0x19:
            case 0x25:
                if (!Savegame_EventFlagGet(EventFlag_285) && Savegame_EventFlagGet(EventFlag_286))
                {
                    Savegame_EventFlagSet(EventFlag_285);
                    Savegame_EventFlagClear(EventFlag_286);
                }
    
                if (!Savegame_EventFlagGet(EventFlag_285))
                {
                    flags = 0x1FE;
                }
                else if (!Savegame_EventFlagGet(EventFlag_286))
                {
                    flags = 0x13E;
                }
    
                break;
    
            case 0x4:
                if (!Player_ItemRemove(InventoryItemId_ExaminationRoomKey, 0))
                {
                    flags = 1;
                }
                // fallthrough
            case 0x6:
            case 0x7:
            case 0xA:
            case 0xB:
            case 0xC:
            case 0xD:
            case 0xE:
            case 0xF:
            case 0x15:
            case 0x16:
            case 0x18:
            case 0x1B:
            case 0x1C:
            case 0x1D:
            case 0x1E:
            case 0x1F:
            case 0x20:
            case 0x22:
            case 0x23:
            case 0x24:
            case 0x27:
            case 0x28:
            case 0x29:
            case 0x2A:
            case 0x2B:
            case 0x2C:
            case 0x2E:
            case 0x2F:
                Savegame_EventFlagSet(EventFlag_286);
                break;
    
            case 0x3:
    
                if (g_GameWork.soundCmd_5B2 == 31)
                {
                    memcpy(data, D_800CA70C, 8);
                    dataPtr = data;
    
                    if (!Savegame_EventFlagGet(EventFlag_293))
                    {
                        f_arg1 = Q12(240.0f);
                        flags = 4;
                    } 
                    else if (!Savegame_EventFlagGet(EventFlag_298))
                    {
                        f_arg1 = Q12(0.25f);
                        flags = 2;
                    } 
                    else if (!Savegame_EventFlagGet(EventFlag_299))
                    {
                        f_arg1 = Q12(0.125f);
                        flags = 8;
                    } 
                    else 
                    {
                        f_arg1 = Q12(240.0f);
                        if (!Savegame_EventFlagGet(EventFlag_294))
                        {
                            f_arg1 = Q12(0.5f);
                            flags = 0x201;
                        } 
                        else 
                        {
                            flags = 1;
                        }
                    }
                }
                else
                {
                    flags = 0x201;
                }
                break;
    
            case 0x3A:
                if (!Savegame_EventFlagGet(EventFlag_260))
                {
                    flags = 1;
                }
                break;
    
            default:
    
                break;
        }
    }
    func_80035F4C(flags, f_arg1, dataPtr);
}

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
            func_8005DC1C(Sfx_Unk1523, &D_800CAAF8, Q8_CLAMPED(0.5f), 0);
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

s16 func_800D1354(void) // 0x800D1354
{
    s32 cos0;
    s32 tmp0;
    s32 x;
    s32 z;
    s32 var1;
    s32 var;
    s32 x6;
    s32 z6;

    // TODO: Use `Math_Vector2MagCalc`.
    x = (g_SysWork.player_4C.chara_0.position_18.vx - Q12(95.2f));
    z = (g_SysWork.player_4C.chara_0.position_18.vz + Q12(140.0f));
    cos0 = Math_Cos(func_8005BF38((ratan2(x, z) - ratan2(Q12(4.8f) + 1, Q12(12.8f) + 1))));

    x6 = Q12_TO_Q6(g_SysWork.player_4C.chara_0.position_18.vx - Q12(95.2f));
    z6 = Q12_TO_Q6(g_SysWork.player_4C.chara_0.position_18.vz + Q12(140.0f));

    tmp0 = FP_FROM((cos0 * Q6_TO_Q12((SquareRoot0(SQUARE(x6) + SQUARE(z6))))), Q12_SHIFT);
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
