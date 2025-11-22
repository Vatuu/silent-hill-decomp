#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "bodyprog/player_logic.h"
#include "main/rng.h"
#include "maps/shared.h"
#include "maps/map6/map6_s03.h"

INCLUDE_RODATA("asm/maps/map6_s03/nonmatchings/map6_s03", D_800C9578);

INCLUDE_RODATA("asm/maps/map6_s03/nonmatchings/map6_s03", g_MapOverlayHeader);

#include "maps/shared/sharedFunc_800CB6B0_0_s00.h" // 0x800CB26C

#include "maps/shared/sharedFunc_800CBBBC_0_s00.h" // 0x800CB660

#include "maps/shared/sharedFunc_800CBC94_0_s00.h" // 0x800CB738

#include "maps/shared/Particle_Update.h" // 0x800CBA54

INCLUDE_ASM("asm/maps/map6_s03/nonmatchings/map6_s03", sharedFunc_800CEFF4_0_s00); // 0x800CC07C

#include "maps/shared/sharedFunc_800CF2A4_0_s01.h" // 0x800CC790

#include "maps/shared/sharedFunc_800CEFD0_1_s02.h" // 0x800CC82C

#include "maps/shared/sharedFunc_800CFFF8_0_s00.h" // 0x800CCB00

INCLUDE_ASM("asm/maps/map6_s03/nonmatchings/map6_s03", sharedFunc_800D0690_1_s03); // 0x800CCBC0

#include "maps/shared/sharedFunc_800CE954_7_s03.h" // 0x800CCD0C

#include "maps/shared/sharedFunc_800D01BC_0_s00.h" // 0x800CCD14

#include "maps/shared/sharedFunc_800CF9A8_0_s01.h" // 0x800CCDCC

#include "maps/shared/Player.h"

#include "maps/shared/Ai_Stalker_Update.h" // 0x800CEFCC

#include "maps/shared/Ai_Stalker_Init.h" // 0x800CF160 - Differs to other maps `Ai_Stalker_Init`.

INCLUDE_ASM("asm/maps/map6_s03/nonmatchings/map6_s03", sharedFunc_800D3308_0_s00); // 0x800CF414

#include "maps/shared/sharedFunc_800D3B44_0_s00.h" // 0x800CFC50

void sharedFunc_800D3EF4_0_s00(s_SubCharacter* chara) {} // 0x800D0000

INCLUDE_ASM("asm/maps/map6_s03/nonmatchings/map6_s03", sharedFunc_800D4924_0_s00); // 0x800D0008

INCLUDE_ASM("asm/maps/map6_s03/nonmatchings/map6_s03", sharedFunc_800D492C_0_s00); // 0x800D0BD8

#include "maps/shared/sharedFunc_800D5098_0_s00.h" // 0x800D1344

INCLUDE_ASM("asm/maps/map6_s03/nonmatchings/map6_s03", sharedFunc_800D54A8_0_s00); // 0x800D1754

#include "maps/shared/sharedFunc_800D5B48_0_s00.h" // 0x800D1DF4

#include "maps/shared/sharedFunc_800D5C64_0_s00.h" // 0x800D1F10

#include "maps/shared/sharedFunc_800D5FCC_0_s00.h" // 0x800D2278

#include "maps/shared/sharedFunc_800D63D0_0_s00.h" // 0x800D267C

#include "maps/shared/sharedFunc_800D654C_0_s00.h" // 0x800D27F8

#include "maps/shared/sharedFunc_800D6554_0_s00.h" // 0x800D2800

#include "maps/shared/sharedFunc_800D670C_0_s00.h" // 0x800D29B8

#include "maps/shared/sharedFunc_800D67FC_0_s00.h" // 0x800D2AA8

INCLUDE_ASM("asm/maps/map6_s03/nonmatchings/map6_s03", sharedFunc_800D6970_0_s00); // 0x800D2C1C

INCLUDE_ASM("asm/maps/map6_s03/nonmatchings/map6_s03", sharedFunc_800D70C4_0_s00); // 0x800D3370

#include "maps/shared/sharedFunc_800D7BE8_0_s00.h" // 0x800D3E94

#include "maps/shared/sharedFunc_800D7E04_0_s00.h" // 0x800D40B0

#include "maps/shared/Ai_HangedScratcher_Update.h" // 0x800D4264

#include "maps/shared/Ai_HangedScratcher_Init.h" // 0x800D42E8

INCLUDE_ASM("asm/maps/map6_s03/nonmatchings/map6_s03", sharedFunc_800CFF74_5_s00); // 0x800D45B4

INCLUDE_ASM("asm/maps/map6_s03/nonmatchings/map6_s03", sharedFunc_800D029C_5_s00); // 0x800D48DC

#include "maps/shared/sharedFunc_800D03F8_5_s00.h" // 0x800D4A38

#include "maps/shared/sharedFunc_800D041C_5_s00.h" // 0x800D4A5C

INCLUDE_ASM("asm/maps/map6_s03/nonmatchings/map6_s03", func_800D4B54);

INCLUDE_ASM("asm/maps/map6_s03/nonmatchings/map6_s03", func_800D4C7C);

INCLUDE_ASM("asm/maps/map6_s03/nonmatchings/map6_s03", func_800D5284);

INCLUDE_ASM("asm/maps/map6_s03/nonmatchings/map6_s03", func_800D5544);

INCLUDE_ASM("asm/maps/map6_s03/nonmatchings/map6_s03", func_800D56F8);

INCLUDE_ASM("asm/maps/map6_s03/nonmatchings/map6_s03", func_800D58B4);

INCLUDE_ASM("asm/maps/map6_s03/nonmatchings/map6_s03", func_800D5FEC);

INCLUDE_ASM("asm/maps/map6_s03/nonmatchings/map6_s03", func_800D6110);

INCLUDE_ASM("asm/maps/map6_s03/nonmatchings/map6_s03", func_800D624C);

INCLUDE_ASM("asm/maps/map6_s03/nonmatchings/map6_s03", func_800D6324);

INCLUDE_ASM("asm/maps/map6_s03/nonmatchings/map6_s03", func_800D64C4);

INCLUDE_ASM("asm/maps/map6_s03/nonmatchings/map6_s03", func_800D6680);

INCLUDE_ASM("asm/maps/map6_s03/nonmatchings/map6_s03", func_800D67C0);

INCLUDE_ASM("asm/maps/map6_s03/nonmatchings/map6_s03", func_800D6A20);

INCLUDE_ASM("asm/maps/map6_s03/nonmatchings/map6_s03", sharedFunc_800D26D8_5_s00); // 0x800D6D18

INCLUDE_ASM("asm/maps/map6_s03/nonmatchings/map6_s03", sharedFunc_800D2844_5_s00); // 0x800D6E84

INCLUDE_ASM("asm/maps/map6_s03/nonmatchings/map6_s03", sharedFunc_800D2C18_5_s00); // 0x800D7258

INCLUDE_ASM("asm/maps/map6_s03/nonmatchings/map6_s03", func_800D7854);

INCLUDE_ASM("asm/maps/map6_s03/nonmatchings/map6_s03", sharedFunc_800D3300_5_s00); // 0x800D7998

#include "maps/shared/sharedFunc_800D929C_0_s00.h" // 0x800D7F14

u8 Map_RoomIdxGet(s32 x, s32 z) // 0x800D7F24
{
    s32 ret;

    if (x < Q12(27.0f))
    {
        ret = 17;
        if (x <= Q12(13.0f)) 
        {
            ret = 15;
            if (x > Q12(-13.0f))
            {
                ret = 16;
            }
        }
    } 
    else if (x < Q12(56.0f))
    {
        ret = 18;
    }
    else
    {
        if (x < Q12(72.0f))
        {
            ret = 19;
        }
        else
        {
            ret = 20;
        }
    }

    return ret;
}

void func_800D7F98(void) // 0x800D7F98
{
    q19_12 dist0;
    q19_12 dist1;
    q19_12 dist2;
    s32    fArg1;
    s32    roomIdx;
    s32    flags;

    roomIdx = g_SavegamePtr->mapRoomIdx_A5;
    fArg1 = 0x400;

    if (Savegame_EventFlagGet(EventFlag_435))
    {
        flags = 1 << 0;
        if (Savegame_EventFlagGet(EventFlag_437)) 
        {
            fArg1 = 0x547;
        }
        else
        {
            flags = D_800DBCE4[roomIdx];

            switch (roomIdx)
            {
                case 15:
                case 16:
                    D_800DBCDC[5] = 0;
                    D_800DBCDC[6] = 0;
                    D_800DBCDC[7] = 0;
                    break;

                case 17:
                    // VECTOR3 D_800DBD10 = VECTOR3(23.0f, 0.0f, 20.0f); // in .data
                    dist0 = Math_Distance2dGet(&g_SysWork.player_4C.chara_0.position_18, &D_800DBD10);
                    if (dist0 < Q12(5.0f))
                    {
                        dist0 = Q8(0.313f);
                    }
                    else
                    {
                        dist0 = Q8(0.313f) - FP_MULTIPLY_PRECISE((dist0 - Q12(5.0f)), 3, Q12_SHIFT); 
                        if (dist0 < Q12(0.0f)) 
                        {
                            dist0 = Q12(0.0f);
                        }
                    }

                    D_800DBCDC[5] = dist0;
                    D_800DBCDC[6] = Q12(0.0f);
                    D_800DBCDC[7] = Q12(0.0f);
                    break;

                case 18:
                case 19:
                case 20:
                    D_800DBCDC[5] = Q8(0.313f);

                    dist1 = Q12(64.0f) - g_SysWork.player_4C.chara_0.position_18.vx;
                    if (dist1 < Q12(0.0f))
                    {
                        dist1 = Q8(0.313f);
                    }
                    else
                    {
                        dist1 = Q8(0.313f) - FP_MULTIPLY_PRECISE(dist1, 3, Q12_SHIFT);
                        if (dist1 < Q12(0.0f))
                        {
                            dist1 = Q12(0.0f);
                        }
                    }

                    D_800DBCDC[6] = dist1;

                    dist2 = Q12(80.0f) - g_SysWork.player_4C.chara_0.position_18.vx;
                    if (dist2 < Q12(0.0f))
                    {
                        dist2 = Q8(0.313f);
                    }
                    else
                    {
                        dist2 = Q8(0.313f) - FP_MULTIPLY_PRECISE(dist2, 5, Q12_SHIFT);
                        if (dist2 < Q12(0.0f))
                        {
                            dist2 = Q12(0.0f);
                        }
                    }

                    D_800DBCDC[7] = dist2;
                    break;
            }
        }
    } 
    else
    {
        flags = (1 << 1) | (1 << 2);
        if (!Savegame_EventFlagGet(EventFlag_431))
        {
            fArg1 = 0x547;
            flags = 1 << 1;
        }
    }

    func_80035F4C(flags, fArg1, &D_800DBCDC);
}

void func_800D81A4(void) {}

const char* MAP_MESSAGES[] = {
    #include "maps/shared/mapMsg_common.h"
    "~H\tThere_is_a_ ~C5 Sewer_map ~N\n\t(connecting_to_amusement_park) ~C7 . ~N\n\tTake_it? ~S4 ",
    "\tGotta'_go_find_Cybil! ~N\n\tNo_time_to_go_back. ~E "
};

void MapEvent_CommonItemTake(void) // 0x800D81AC
{
    u32 pickupType;
    s32 eventFlagIdx;

    pickupType   = CommonPickupItemId_FirstAidKit;
    eventFlagIdx = 0;

    switch (g_MapEventParam->field_5)
    {
        case 10:
            pickupType   = CommonPickupItemId_HealthDrink;
            eventFlagIdx = EventFlag_M6S03_HealthDrink0;
            break;

        case 11:
            pickupType   = CommonPickupItemId_HandgunBullets;
            eventFlagIdx = EventFlag_M6S03_HandgunBullets;
            break;

        case 12:
            pickupType   = CommonPickupItemId_HealthDrink;
            eventFlagIdx = EventFlag_M6S03_HealthDrink1;
            break;
    }

    Event_CommonItemTake(pickupType, eventFlagIdx);
}

void func_800D822C(void) // 0x800D822C
{
    if (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.skip_4)
    {
        if (g_SysWork.sysStateStep_C[0] == 3)
        {
            SysWork_StateStepSet(0, 4);
        }
    }

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            Player_ControlFreeze();
            ScreenFade_ResetTimestep();
            SysWork_StateStepIncrement(0);

        case 1:
            func_80085DF0();
            break;

        case 2:
            // Warp player.
            g_SysWork.player_4C.chara_0.position_18.vx = Q12(-20.0486f);
            g_SysWork.player_4C.chara_0.position_18.vy = Q12(-4.07f);
            g_SysWork.player_4C.chara_0.position_18.vz = Q12(24.7134f);
            g_SysWork.player_4C.chara_0.rotation_24.vy = FP_ANGLE(180.0f);

            // Turn on flashlight.
            Game_TurnFlashlightOn();

            // Warp camera.
            Camera_PositionSet(NULL, Q12(-19.66f), Q12(0.17f), Q12(26.3f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);
            Camera_LookAtSet(NULL, Q12(-20.49f), Q12(-3.23f), Q12(24.37f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);

            func_80085EB8(0, &g_SysWork.player_4C.chara_0, 88, false);
            SysWork_StateStepIncrementAfterFade(0, false, 0, Q12(1.5f), false);
            SysWork_StateStepIncrement(0);

        case 3:
            g_SysWork.player_4C.chara_0.position_18.vy += FP_MULTIPLY_FLOAT_PRECISE(g_DeltaTime0, 0.4f, Q12_SHIFT);
            SysWork_StateStepIncrementDelayed(Q12(3.8f), false);
            break;

        case 4:
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(1.5f), false);
            g_SysWork.player_4C.chara_0.position_18.vy += FP_MULTIPLY_FLOAT_PRECISE(g_DeltaTime0, 0.4f, Q12_SHIFT);
            break;

        default:
            Player_ControlUnfreeze(true);
            SysWork_StateSetNext(SysState_Gameplay);
            Savegame_EventFlagSet(EventFlag_431);
            func_8003A16C();
            break;
    }
}

void func_800D84EC(void) // 0x800D84EC
{
    if (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.skip_4)
    {
        if (g_SysWork.sysStateStep_C[0] == 4)
        {
            SysWork_StateStepSet(0, 5);
        }
    }

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            Player_ControlFreeze();
            SysWork_StateStepIncrementAfterFade(0, true, 0, Q12(0.0f), false);
            Savegame_EventFlagSet(EventFlag_437);
            SysWork_StateStepIncrement(0);

        case 1:
            func_80085DF0();
            break;

        case 2:
            SysWork_StateStepIncrementAfterFade(1, true, 0, Q12(0.0f), false);
            break;

        case 3:
            g_SysWork.player_4C.chara_0.position_18.vx = Q12(89.9092f);
            g_SysWork.player_4C.chara_0.position_18.vy = Q12(-0.0733f);
            g_SysWork.player_4C.chara_0.position_18.vz = Q12(18.8875f);
            g_SysWork.player_4C.chara_0.rotation_24.vy = FP_ANGLE(90.0f);
            Game_TurnFlashlightOn();
            Camera_PositionSet(NULL, Q12(88.92f), Q12(-1.64f), Q12(20.16f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);
            Camera_LookAtSet(NULL, Q12(90.98f), Q12(-4.45f), Q12(18.2f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);
            func_80085EB8(0U, &g_SysWork.player_4C.chara_0, 87, false);
            SysWork_StateStepIncrementAfterFade(0, false, 0, Q12(1.5f), false);
            SysWork_StateStepIncrement(0);

        case 4:
            g_SysWork.player_4C.chara_0.position_18.vy -= FP_MULTIPLY_FLOAT_PRECISE(g_DeltaTime0, 0.415f, 12);
            SysWork_StateStepIncrementDelayed(Q12(5.0f), false);
            break;

        case 5:
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(1.5f), false);
            g_SysWork.player_4C.chara_0.position_18.vy -= FP_MULTIPLY_FLOAT_PRECISE(g_DeltaTime0, 0.41f, 12);
            break;

        default:
            Player_ControlUnfreeze(true);
            SysWork_StateSetNext(SysState_Gameplay);
            Savegame_EventFlagSet(EventFlag_433);
            break;
    }
}

void MapEvent_MapTake(void) // 0x800D87F0
{
    Event_MapTake(15, EventFlag_M6S03_PickupMap, 15);
}

void func_800D8818(void) // 0x800D8818
{
    D_800DFEF5 = 0;
    D_800DFEF4 = 0;
    D_800DFEF2 = 0;
    D_800DFEF0 = 0;

    WorldObject_ModelNameSet(&g_WorldObject0[0], "YUKABFO1");
    WorldObject_ModelNameSet(&g_WorldObject0[1], "YUKAAFT1");
    Math_Vector3Set(&g_WorldObjectPos0, Q12(-20.0f), Q12(0.0f), Q12(34.0f));

    WorldObjectInit(&g_WorldObject1, "SITAI_NE", 75.0f, 0.5f, 19.7f, 0.0f, 180.0f, 0.0f);

    WorldObjectNoRotInit(&g_WorldObject2, "MP_DRNBK", -22.0f, 0.0f, 26.4f);

    if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Easy)
    {
        g_SysWork.npcId_2280 = 3;
    }

    WorldObject_ModelNameSet(&g_CommonWorldObjects[0], D_800A99E4.firstAidKitName_8);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[1], D_800A99E4.healthDrinkName_C);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[2], D_800A99E4.ampouleName_10);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[3], D_800A99E4.handgunBulletsName_14);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[4], D_800A99E4.shotgunShellsName_18);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[5], D_800A99E4.rifleShellsName_1C);
}

INCLUDE_ASM("asm/maps/map6_s03/nonmatchings/map6_s03", func_800D89A0);

void func_800D936C(void) {}

INCLUDE_RODATA("asm/maps/map6_s03/nonmatchings/map6_s03", D_800CB258);

INCLUDE_RODATA("asm/maps/map6_s03/nonmatchings/map6_s03", D_800CB260);
