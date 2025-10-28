#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "bodyprog/gfx/text_draw.h"
#include "main/rng.h"
#include "maps/shared.h"
#include "maps/map1/map1_s04.h"

INCLUDE_RODATA("asm/maps/map1_s04/nonmatchings/map1_s04", D_800C9578);

INCLUDE_RODATA("asm/maps/map1_s04/nonmatchings/map1_s04", g_MapOverlayHeader);

#include "maps/shared/sharedFunc_800CB6B0_0_s00.h" // 0x800CA95C

#include "maps/shared/sharedFunc_800D08B8_0_s00.h" // 0x800CAAC4

#include "maps/shared/sharedFunc_800D0A60_0_s00.h" // 0x800CAC44

#include "maps/shared/sharedFunc_800D0B18_0_s00.h" // 0x800CACFC

#include "maps/shared/sharedFunc_800D0E04_0_s00.h" // 0x800CAE60

#include "maps/shared/sharedFunc_800CFFD8_0_s01.h" // 0x800CAE80

#include "maps/shared/sharedFunc_800D0850_0_s01.h" // 0x800CB6F8

#include "maps/shared/sharedFunc_800CDAA8_0_s02.h" // 0x800CBAE4

#include "maps/shared/sharedFunc_800D1C38_0_s00.h" // 0x800CBDD8

#include "maps/shared/sharedFunc_800D209C_0_s00.h" // 0x800CC204

#include "maps/shared/sharedFunc_800D20D8_0_s00.h" // 0x800CC240

#include "maps/shared/sharedFunc_800D20E4_0_s00.h" // 0x800CC24C

#include "maps/shared/sharedFunc_800D2244_0_s00.h" // 0x800CC3AC

s32 func_800CC584()
{
    return 0;
}

#include "maps/shared/sharedFunc_800D2C7C_0_s00.h" // 0x800CC58C

#include "maps/shared/sharedFunc_800D2D2C_0_s00.h" // 0x800CC63C

#include "maps/shared/sharedFunc_800D2D44_0_s00.h" // 0x800CC654

#include "maps/shared/sharedFunc_800D2D6C_0_s00.h" // 0x800CC67C

#include "maps/shared/sharedFunc_800D2D84_0_s00.h" // 0x800CC694

#include "maps/shared/sharedFunc_800D2DAC_0_s00.h" // 0x800CC6BC

#include "maps/shared/sharedFunc_800D2E50_0_s00.h" // 0x800CC760

#include "maps/shared/sharedFunc_800D2E60_0_s00.h" // 0x800CC770

void func_800CC77C(void) {}

void func_800CC784(void) {}

void func_800CC78C(void) {}

void func_800CC794(void) {}

void func_800CC79C(void) {}

s32 func_800CC7A4()
{
    return 0;
}

void func_800CC7AC(void) {}

#include "maps/shared/sharedFunc_800D2EA4_0_s00.h" // 0x800CC7B4

#include "maps/shared/sharedFunc_800D2EB4_0_s00.h" // 0x800CC7C4

#include "maps/shared/sharedFunc_800D2EF4_0_s00.h" // 0x800CC804

#include "maps/shared/sharedFunc_800D929C_0_s00.h" // 0x800CC818

#include "maps/shared/Map_RoomIdxGet.h" // 0x800CC828

void func_800CC8C8(void) // 0x800CC8C8
{
    s32 var_a1;
    s32 mapRoomIdx;
    s32 var_a3;

    mapRoomIdx = g_SavegamePtr->mapRoomIdx_A5;
    var_a3     = D_800CCF5C[mapRoomIdx];
    var_a1     = Q12(0.1f);

    switch (mapRoomIdx)
    {
        case 23:
            var_a3 = 1;
            if (g_SavegamePtr->mapMarkingFlags_1D4[10] & (1 << 18))
            {
                var_a3 = 0x1FE;
                if (g_SavegamePtr->mapMarkingFlags_1D4[9] & (1 << 20 | 1 << 21))
                {
                    var_a3 = 0x10;
                }
            }
            break;

        case 38:
            if (Savegame_EventFlagGet(EventFlag_100) && !Savegame_EventFlagGet(EventFlag_107))
            {
                var_a3 = 1;
                var_a1 = Q12(0.3f);
            }
            break;

        case 5:
            if (g_SavegamePtr->eventFlags_168[3] & (1 << 25))
            {
                var_a1 = Q12(240.0f);
                if (g_SavegamePtr->eventFlags_168[3] & (1 << 0))
                {
                    var_a3 |= 8;
                }
                else
                {
                    var_a3 = 1;
                }
            }
            break;

        case 11:
            g_SavegamePtr->eventFlags_168[3] &= ~(1 << 25);
            break;

        case 7:
            if (!Savegame_EventFlagGet(EventFlag_98) && Savegame_EventFlagGet(EventFlag_122))
            {
                var_a1 = Q12(240.0f);
                var_a3 = 1;
            }
            break;
    }

    func_80035F4C(var_a3, var_a1, &D_800CCF54);
}

void func_800CCA24(void) {}

void func_800CCA2C(void) // 0x800CCA2C
{
    s32 temp_s0;

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            sharedFunc_800D20E4_0_s00();
            g_SysWork.field_30 = 20;
            SysWork_StateStepIncrement();

        case 1:
            if (g_Controller0->btnsClicked_10 & ControllerFlag_R3)
            {
                D_800CD768 = 0;
                D_800CD76C = 0;
            }

            if (g_Controller0->btnsPulsed_18 & ControllerFlag_LStickDown)
            {
                if (D_800CD768 == 0)
                {
                    D_800CD768 = 23;
                }
                D_800CD768--;
            }

            if (g_Controller0->btnsPulsed_18 & ControllerFlag_LStickUp)
            {
                D_800CD768++;
                if (D_800CD768 == 23)
                {
                    D_800CD768 = 0;
                }
            }

            if (g_Controller0->btnsPulsed_18 & ControllerFlag_LStickLeft)
            {
                if (D_800CD76C != 0)
                {
                    D_800CD76C--;
                }
            }

            if (g_Controller0->btnsPulsed_18 & ControllerFlag_LStickRight)
            {
                if (D_800CD76C != 39 && D_800CD038[D_800CD768][D_800CD76C + 1] != 0)
                {
                    D_800CD76C++;
                }
            }

            if (g_Controller0->btnsClicked_10 & ControllerFlag_Circle)
            {
                Sd_EngineCmd(D_800CD038[D_800CD768][D_800CD76C]);
                D_800CD770 = 0;
                D_800CD774 = 1;
            }

            temp_s0 = D_800CD774;
            if (temp_s0 == 1 && func_80045B28() != temp_s0)
            {
                D_800CD774 = 2;
            }

            if (D_800CD774 == 2 && func_80045B28() == 1)
            {
                D_800CD770 += g_DeltaTime0;

                if (g_Controller0->btnsClicked_10 & ControllerFlag_Cross)
                {
                    D_800CD774 = 0;
                }
            }

            Gfx_DebugStringPosition(50, 50);

            if (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.skip_4)
            {
                SysWork_StateStepIncrement();
            }
            break;

        case 2:
            if (g_Controller0->btnsClicked_10 & ControllerFlag_Circle)
            {
                Sd_EngineCmd(D_800CD768_tbl[D_800CD768]);
            }

            if (g_Controller0->btnsClicked_10 & ControllerFlag_Cross)
            {
                func_8004690C(D_800CD768_tbl[D_800CD768]);
            }

            if (g_Controller0->btnsPulsed_18 & ControllerFlag_LStickDown)
            {
                if (D_800CD768 == 0)
                {
                    D_800CD768 = 4;
                }
                D_800CD768--;
            }

            if (g_Controller0->btnsPulsed_18 & ControllerFlag_LStickUp)
            {
                D_800CD768++;
                if (D_800CD768 == 4)
                {
                    D_800CD768 = 0;
                }
            }
            break;
    }
}

void func_800CCE30(void) {}

void func_800CCE38(void) // 0x800CCE38
{
    if (g_Controller0->btnsClicked_10 & ControllerFlag_R1)
    {
        Sd_EngineCmd(Sfx_Unk1335);
    }

    if (g_Controller0->btnsClicked_10 & ControllerFlag_R2)
    {
        Sd_EngineCmd(Sfx_Unk1342);
    }

    if (g_Controller0->btnsClicked_10 & ControllerFlag_R3)
    {
        Sd_EngineCmd(Sfx_Unk1343);
    }
}

INCLUDE_RODATA("asm/maps/map1_s04/nonmatchings/map1_s04", D_800CA6A0);
