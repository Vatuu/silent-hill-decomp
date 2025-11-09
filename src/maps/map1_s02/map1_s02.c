#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "bodyprog/player_logic.h"
#include "main/rng.h"
#include "maps/shared.h"
#include "maps/map1/map1_s02.h"

INCLUDE_RODATA("asm/maps/map1_s02/nonmatchings/map1_s02", D_800C9578);

INCLUDE_RODATA("asm/maps/map1_s02/nonmatchings/map1_s02", g_MapOverlayHeader);

INCLUDE_ASM("asm/maps/map1_s02/nonmatchings/map1_s02", sharedFunc_800CBA4C_1_s02); // 0x800CBA4C

#include "maps/shared/sharedFunc_800CBC98_1_s02.h" // 0x800CBC98

#include "maps/shared/sharedFunc_800CBD58_1_s02.h" // 0x800CBD58

INCLUDE_ASM("asm/maps/map1_s02/nonmatchings/map1_s02", func_800CBDA8);

INCLUDE_ASM("asm/maps/map1_s02/nonmatchings/map1_s02", func_800CCE60);

#include "maps/shared/sharedFunc_800CB6B0_0_s00.h" // 0x800CDA4C

#include "maps/shared/sharedFunc_800CBBBC_0_s00.h" // 0x800CDE40

#include "maps/shared/sharedFunc_800CBC94_0_s00.h" // 0x800CDF18

#include "maps/shared/Particle_Update.h" // 0x800CE234

INCLUDE_ASM("asm/maps/map1_s02/nonmatchings/map1_s02", sharedFunc_800CEFF4_0_s00); // 0x800CE844

#include "maps/shared/sharedFunc_800CF2A4_0_s01.h" // 0x800CEF34

#include "maps/shared/sharedFunc_800CEFD0_1_s02.h" // 0x800CEFD0

INCLUDE_ASM("asm/maps/map1_s02/nonmatchings/map1_s02", sharedFunc_800CFFF8_0_s00); // 0x800CF2B4

#include "maps/shared/sharedFunc_800CE954_7_s03.h" // 0x800CF374

#include "maps/shared/sharedFunc_800D01BC_0_s00.h" // 0x800CF37C

#include "maps/shared/sharedFunc_800CF9A8_0_s01.h" // 0x800CF434

#include "maps/shared/sharedFunc_800D08B8_0_s00.h" // 0x800CF4F4

#include "maps/shared/sharedFunc_800D0A60_0_s00.h" // 0x800CF69C

#include "maps/shared/sharedFunc_800D0B18_0_s00.h" // 0x800CF754

#include "maps/shared/sharedFunc_800D0CB8_0_s00.h" // 0x800CF8F4

#include "maps/shared/sharedFunc_800D0E04_0_s00.h" // 0x800CFA40

#include "maps/shared/sharedFunc_800CFFD8_0_s01.h" // 0x800CFA60

#include "maps/shared/sharedFunc_800D0850_0_s01.h" // 0x800D02D8

#include "maps/shared/sharedFunc_800CDAA8_0_s02.h" // 0x800D06C4

#include "maps/shared/sharedFunc_800D1C38_0_s00.h" // 0x800D1624

#include "maps/shared/sharedFunc_800D209C_0_s00.h" // 0x800D1AAC

#include "maps/shared/sharedFunc_800D20D8_0_s00.h" // 0x800D1AE8

#include "maps/shared/sharedFunc_800D20E4_0_s00.h" // 0x800D1AF4

#include "maps/shared/sharedFunc_800D2244_0_s00.h" // 0x800D1C54

INCLUDE_ASM("asm/maps/map1_s02/nonmatchings/map1_s02", func_800D1E2C);

#include "maps/shared/sharedFunc_800D2C7C_0_s00.h" // 0x800D26BC

#include "maps/shared/sharedFunc_800D2D2C_0_s00.h" // 0x800D276C

#include "maps/shared/sharedFunc_800D2D44_0_s00.h" // 0x800D2784

#include "maps/shared/sharedFunc_800D2D6C_0_s00.h" // 0x800D27AC

#include "maps/shared/sharedFunc_800D2D84_0_s00.h" // 0x800D27C4

#include "maps/shared/sharedFunc_800D2DAC_0_s00.h" // 0x800D27EC

#include "maps/shared/sharedFunc_800D2E50_0_s00.h" // 0x800D2890

#include "maps/shared/sharedFunc_800D2E60_0_s00.h" // 0x800D28A0

void func_800D28AC(void) {}

void func_800D28B4(void) {}

void func_800D28BC(void) {}

void func_800D28C4(void) {}

void func_800D28CC(void) {}

s32 func_800D28D4(void) // 0x800D28D4
{
    return 0;
}

void func_800D28DC(void) {}

#include "maps/shared/sharedFunc_800D2EA4_0_s00.h" // 0x800D28E4

#include "maps/shared/sharedFunc_800D2EB4_0_s00.h" // 0x800D28F4

#include "maps/shared/sharedFunc_800D2EF4_0_s00.h" // 0x800D2934

#include "maps/shared/Ai_Stalker_Update.h" // 0x800D2948

#include "maps/shared/Ai_Stalker_Init.h" // 0x800D2ADC

INCLUDE_ASM("asm/maps/map1_s02/nonmatchings/map1_s02", sharedFunc_800D3308_0_s00); // 0x800D2D48

#include "maps/shared/sharedFunc_800D3B44_0_s00.h" // 0x800D3584

void sharedFunc_800D3EF4_0_s00(s_SubCharacter* chara) {} // 0x800D3934

INCLUDE_ASM("asm/maps/map1_s02/nonmatchings/map1_s02", sharedFunc_800D4924_0_s00); // 0x800D393C

INCLUDE_ASM("asm/maps/map1_s02/nonmatchings/map1_s02", sharedFunc_800D492C_0_s00); // 0x800D450C

#include "maps/shared/sharedFunc_800D5098_0_s00.h" // 0x800D4C78

INCLUDE_ASM("asm/maps/map1_s02/nonmatchings/map1_s02", sharedFunc_800D54A8_0_s00); // 0x800D5088

#include "maps/shared/sharedFunc_800D5B48_0_s00.h" // 0x800D5728

#include "maps/shared/sharedFunc_800D5C64_0_s00.h" // 0x800D5844

#include "maps/shared/sharedFunc_800D5FCC_0_s00.h" // 0x800D5BAC

#include "maps/shared/sharedFunc_800D63D0_0_s00.h" // 0x800D5FB0

#include "maps/shared/sharedFunc_800D654C_0_s00.h" // 0x800D612C

#include "maps/shared/sharedFunc_800D6554_0_s00.h" // 0x800D6134

#include "maps/shared/sharedFunc_800D670C_0_s00.h" // 0x800D62EC

#include "maps/shared/sharedFunc_800D67FC_0_s00.h" // 0x800D63DC

INCLUDE_ASM("asm/maps/map1_s02/nonmatchings/map1_s02", sharedFunc_800D6970_0_s00); // 0x800D6550

INCLUDE_ASM("asm/maps/map1_s02/nonmatchings/map1_s02", sharedFunc_800D70C4_0_s00); // 0x800D6CA4

#include "maps/shared/sharedFunc_800D7BE8_0_s00.h" // 0x800D77C8

#include "maps/shared/sharedFunc_800D7E04_0_s00.h" // 0x800D79E4

#include "maps/shared/Ai_Creaper_Update.h" // 0x800D7B98

#include "maps/shared/Ai_Creaper_Init.h" // 0x800D7C28

INCLUDE_ASM("asm/maps/map1_s02/nonmatchings/map1_s02", sharedFunc_800D7EE8_1_s02); // 0x800D7EE8

#include "maps/shared/sharedFunc_800D8244_1_s02.h" // 0x800D8244

INCLUDE_ASM("asm/maps/map1_s02/nonmatchings/map1_s02", sharedFunc_800D82F0_1_s02);

INCLUDE_ASM("asm/maps/map1_s02/nonmatchings/map1_s02", sharedFunc_800D8684_1_s02);

INCLUDE_ASM("asm/maps/map1_s02/nonmatchings/map1_s02", sharedFunc_800D8F30_1_s02);

INCLUDE_ASM("asm/maps/map1_s02/nonmatchings/map1_s02", sharedFunc_800D9528_1_s02);

#include "maps/shared/sharedFunc_800D9774_1_s02.h" // 0x800D9774

#include "maps/shared/sharedFunc_800D983C_1_s02.h" // 0x800D983C

#include "maps/shared/sharedFunc_800D9960_1_s02.h" // 0x800D9960

INCLUDE_ASM("asm/maps/map1_s02/nonmatchings/map1_s02", sharedFunc_800D99D0_1_s02); // 0x800D99D0

#include "maps/shared/sharedFunc_800D929C_0_s00.h" // 0x800D9E0C

#include "maps/shared/Map_RoomIdxGet.h" // 0x800D9E1C

INCLUDE_ASM("asm/maps/map1_s02/nonmatchings/map1_s02", func_800D9EBC);

void func_800DA018(void) {}

#include "maps/shared/MapEvent_DoorJammed.h" // 0x800DA020

#include "maps/shared/MapEvent_DoorLocked.h" // 0x800DA0B4

#include "maps/shared/MapEvent_DoorUnlocked.h" // 0x800DA16C

const char* MAP_MESSAGES[] = {
    #include "maps/shared/mapMsg_common.h"
    "~J0(1.2)\tWhere_am_I? ~E ",
    "~J0(2.0)\tHave_I_been_here_before? ~E ",
    "~J0(3.8)\tI_don't_remember ~N\n\t\t\tthis_being_here_before... ~E ",
    "\tThe_tower_door_is_locked. ~E ",
    "\t",
    "\t",
    "\t~C5 A_Golden_Sun ~C7 ~E ",
    "\t~C5 A_Silver_Moon ~C7 ~E ",
    "\tWhat? ~N\n\tIs_this_a_door? ",
    "\tIf_it_is,_there's_no_keyhole, ~N\n\tor_even_a_knob... ",
    "\tIf_I_push_it,_it_moves_a_bit, ~N\n\tbut_it_certainly_won't_open. ~E ",
    "\tWhat's_this? ~E ",
    "\tIn_the_center_of_the_door_is ~N\n\ta_horizontal_slot. ",
    "\tWhat_is_it_for? ~E ",
    "\tThere_is_a_ ~C2 Picture_card ~C7 . ~N\n\tTake_it? ~S4 ",
    "\tSlid_the_ ~C2 Picture_card ~C7 ~N\n\tinto_the_slot. ~E ",
    "~J0(0.9)\t_ ",
    "~J0(3.0)\tDaddy==_help_me=== ",
    "~J0(3.0)\t==Daddy==where_are_you==? ",
    "~D ~J0(2.0)\n\tCheryl! ~E ",
    "~J1(2.4)\n\tThat_was_Cheryl's_voice. ~N\n\tI_know_it. ",
    "~J1(2.0)\n\tWhere_is_she? ~N\n\tCheryl... ~E ",
    "\tThere_is_a_ ~C2 Rubber_ball ~C7 . ~N\n\tTake_it? ~S4 ",
    "\t~C5 Leonard_Rhine ~N\n\tThe_Monster_Lurks ~C7 ",
    "\tThe_monster_lurks... ~N\n\tWhat's_that_supposed_to_mean? ~E ",
    "\tThere_is_a_ ~C2 Shotgun ~C7 . ~N\n\tTake_it? ~S4 ",
    "\t_ ~S3 ",
    "\tTurn_the_valve_left. ",
    "\tTurn_the_valve_right. ",
    "\tStop_turning_the_valve. ",
    "\tCards_are_scattered... ~E ",
    "\tA_wheelchair? ~N\n\tAt_an_elementary_school? ~E ",
    "\tLocker_is_locked. ~E ",
    "\tA_huge_fan_is_rotating. ",
    "\tIf_approached_carelessly, ~N\n\tI_may_be_sucked_in. ~E ",
    "\tCan't_use_the_phone. ~E ",
    "\tThere_is_a_ ~C2 Classroom_key ~C7 . ~N\n\tTake_it? ~S4 ",
    "\tA_hanging_body... ~N\n\tWhy_would_somebody... ~E ",
    "\tA_doll_is_on_the_floor. ~E ",
    "\tA_headless_doll_is_stuck ~N\n\tto_the_wall. ~E "
};

void func_800DA200(void) // 0x800DA200
{
    u32 pickupType;
    s32 eventFlagIdx;

    pickupType   = CommonPickupItemId_FirstAidKit;
    eventFlagIdx = 0;

    switch (g_MapEventParam->field_5)
    {
        case 107:
            pickupType   = CommonPickupItemId_Ampoule;
            eventFlagIdx = EventFlag_M1S02_Ampoule0;
            break;

        case 108:
            pickupType   = CommonPickupItemId_ShotgunShells;
            eventFlagIdx = EventFlag_M1S02_ShotgunShells0;
            break;

        case 109:
            pickupType   = CommonPickupItemId_ShotgunShells;
            eventFlagIdx = EventFlag_M1S02_ShotgunShells1;
            break;

        case 110:
            pickupType   = CommonPickupItemId_FirstAidKit;
            eventFlagIdx = EventFlag_M1S02_FirstAidKit0;
            break;

        case 111:
            pickupType   = CommonPickupItemId_HandgunBullets;
            eventFlagIdx = EventFlag_M1S02_HandgunBullets0;
            break;

        case 112:
            pickupType   = CommonPickupItemId_HandgunBullets;
            eventFlagIdx = EventFlag_M1S02_HandgunBullets1;
            break;

        case 113:
            pickupType   = CommonPickupItemId_HandgunBullets;
            eventFlagIdx = EventFlag_M1S02_HandgunBullets2;
            break;

        case 114:
            pickupType   = CommonPickupItemId_Ampoule;
            eventFlagIdx = EventFlag_M1S02_Ampoule1;
            break;

        case 115:
            pickupType   = CommonPickupItemId_HealthDrink;
            eventFlagIdx = EventFlag_M1S02_HealthDrink0;
            break;

        case 116:
            pickupType   = CommonPickupItemId_FirstAidKit;
            eventFlagIdx = EventFlag_M1S02_FirstAidKit1;
            break;

        case 117:
            pickupType   = CommonPickupItemId_HealthDrink;
            eventFlagIdx = EventFlag_M1S02_HealthDrink1;
            break;
    }

    Event_CommonItemTake(pickupType, eventFlagIdx);
}

void MapEvent_LobbyKeyUse(void) // 0x800DA2E4
{
    VECTOR3 sfxPos = { MAP_POINTS[g_MapEventParam->field_5].positionX_0, Q12(-1.2f), MAP_POINTS[g_MapEventParam->field_5].positionZ_8 };

    Player_ItemRemove(InventoryItemId_LobbyKey, 1);
    Map_MessageWithSfx(19, Sfx_DoorUnlocked, &sfxPos); // Empty message?
}

void func_800DA384(void) // 0x800DA384
{
    VECTOR3 viewPos;
    bool    isSkipped;

    isSkipped = false;

    if ((g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.skip_4) &&
        g_SysWork.sysStateStep_C[0] > 0 && g_SysWork.sysStateStep_C[0] < 10)
    {
        isSkipped = true;
        SysWork_StateStepReset();
    }

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            Camera_PositionSet(NULL, Q12(-19.96f), Q12(-1.4f), Q12(-61.45f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);
            Camera_LookAtSet(NULL, Q12(-17.14f), Q12(-1.49f), Q12(-64.27f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);
            break;

        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
            break;

        case 7:
        case 8:
        case 9:
        case 10:
            if (D_800E1EE4 == 0)
            {
                Camera_PositionSet(NULL, Q12(-21.2f), Q12(-2.28f), Q12(-59.23f), Q12(0.0f), Q12(0.0f), cam_mv_prm_user.max_spd_xz >> 3, cam_mv_prm_user.max_spd_y >> 3, false);
                Camera_LookAtSet(NULL, Q12(-13.1f), Q12(-1.2f), Q12(-68.3f), Q12(0.0f), Q12(0.0f), deflt_watch_mv_prm.max_ang_spd_x >> 3, deflt_watch_mv_prm.max_ang_spd_y >> 3, false);
                vwGetViewPosition(&viewPos);

                if (ABS(viewPos.vx - Q12(-21.2f)) < Q12(0.3f) && ABS(viewPos.vz - Q12(-59.23f)) < Q12(0.3f))
                {
                    D_800E1EE4 = 1;
                }
            }
            else
            {
                Camera_PositionSet(NULL, Q12(-17.79f), Q12(-5.03f), Q12(-54.09f), Q12(0.0f), Q12(0.0f), cam_mv_prm_user.max_spd_xz >> 3, cam_mv_prm_user.max_spd_y >> 3, false);
                Camera_LookAtSet(NULL, Q12(-19.57f), Q12(0.0f), Q12(-61.21f), Q12(0.0f), Q12(0.0f), deflt_watch_mv_prm.max_ang_spd_x >> 3, deflt_watch_mv_prm.max_ang_spd_y >> 3, false);
            }
            break;

        default:
            Savegame_MapMarkingSet(MapMarkFlag_AltSchool1F_CourtyardQuestion);
            break;
    }

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            sharedFunc_800D20E4_0_s00();
            Game_TurnFlashlightOn();
            sharedFunc_800D08B8_0_s00(6, 127);
            sharedFunc_800CB6B0_0_s00(0, g_SavegamePtr->mapOverlayId_A4, 0);

            g_SysWork.player_4C.chara_0.position_18.vx = Q12(-13.3f);
            g_SysWork.player_4C.chara_0.position_18.vz = Q12(-68.1f);

            func_800865FC(true, 0, 0, FP_ANGLE(-45.0f), Q12(-18.18f), Q12(-62.24f));
            Savegame_EventFlagClear(EventFlag_92);

            D_800E1EE2 = 0;

            SysWork_StateStepIncrement(0);

        case 1:
            SysWork_StateStepIncrementAfterFade(2, true, 2, Q12(0.0f), false);
            break;

        case 2:
            SysWork_StateStepIncrementDelayed(Q12(1.5f), false);
            break;

        case 3:
            func_80085DF0();
            break;

        case 4:
            Map_MessageWithAudio(15, &D_800E1EE2, &D_800E1EDC); // "Where am I?"
            break;

        case 5:
            func_80086C58(&g_SysWork.player_4C.chara_0, 74);
            break;

        case 6:
            Map_MessageWithAudio(16, &D_800E1EE2, &D_800E1EDC); // "Have I been here before?"
            break;

        case 7:
            Savegame_EventFlagSet(EventFlag_92);
            func_800866D4(53, 1, false);
            break;

        case 8:
            SysWork_StateStepIncrementDelayed(Q12(2.2f), false);
            break;

        case 9:
            Map_MessageWithAudio(17, &D_800E1EE2, &D_800E1EDC); // "I don't remember this being here before..."
            break;

        case 10:
            SysWork_StateStepIncrementDelayed(Q12(1.0f), false);
            break;

        default:
            if (isSkipped)
            {
                g_SysWork.player_4C.chara_0.position_18.vx = Q12(-18.18f);
                g_SysWork.player_4C.chara_0.position_18.vy = Q12(0.0f);
                g_SysWork.player_4C.chara_0.position_18.vz = Q12(-62.24f);
                g_SysWork.player_4C.chara_0.rotation_24.vy = FP_ANGLE(-45.0f);

                sharedFunc_800D2244_0_s00(true);
                SysWork_StateSetNext(SysState_Gameplay);
                vcReturnPreAutoCamWork(true);
            }
            else
            {
                sharedFunc_800D2244_0_s00(false);
                SysWork_StateSetNext(SysState_Gameplay);
                vcReturnPreAutoCamWork(false);
            }

            SysWork_StateStepIncrementAfterFade(0, false, 2, Q12(0.0f), false);

            // Sets `EventFlag_225` temporarily for function call and clears afterward?
            Savegame_EventFlagSet(EventFlag_225);
            func_8003A16C();
            Savegame_EventFlagClear(EventFlag_225);
            break;
    }
}

void func_800DA8F8(void) // 0x800DA8F8
{
    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            sharedFunc_800D20E4_0_s00();
            SysWork_StateStepIncrement(0);

        case 1:
            func_80085DF0();
            break;

        case 2:
            MapMsg_DisplayAndHandleSelection(false, 0x12, 0, 0, 0, false);
            break;

        default:
            sharedFunc_800D2244_0_s00(false);
            SysWork_StateSetNext(SysState_Gameplay);
            break;
    }
}

void func_800DA9D4(void) // 0x800DA9D4
{
    MapMsg_DisplayWithTexture(FILE_TIM_GOLD2_TIM, Q12(3.0f), Q12(2.5f), 21);
}

void func_800DAA00(void) // 0x800DAA00
{
    MapMsg_DisplayWithTexture(FILE_TIM_SILVER2_TIM, Q12(3.0f), Q12(2.5f), 22);
}

INCLUDE_ASM("asm/maps/map1_s02/nonmatchings/map1_s02", func_800DAA2C);

extern s16 D_800E1FD0;

void func_800DAD2C(void)
{
    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            sharedFunc_800D20E4_0_s00();
            SysWork_StateStepIncrementAfterFade(0, true, 0, Q12(0.0f), false);
            func_800862F8(0, FILE_TIM_RECEPDR1_TIM, false);
            D_800E1FD0 = 0;
            SysWork_StateStepIncrement(0);
        case 1:
            func_800862F8(1, 0, false);
            break;
        case 2:
            SysWork_StateStepIncrementAfterFade(1, true, 0, Q12(0.0f), false);
            break;
        case 3:
            func_800862F8(3, 0, false);
            func_800862F8(4, FILE_TIM_RECEPDR2_TIM, false);
            SysWork_StateStepIncrement(0);
            /* fallthrough */
        case 4:
            func_800862F8(2, 0, false);
            SysWork_StateStepIncrementAfterFade(2, false, 0, Q12(0.0f), false);
            break;
        case 5:
            func_800862F8(2, 0, false);
            if (Savegame_EventFlagGet(EventFlag_M1S02_SeenDoorWithHorizontalSlot))
            {
                MapMsg_DisplayAndHandleSelection(false, 25, false, false, 0, false); // If I push it, it moves a bit.
            }
            else
            {
                MapMsg_DisplayAndHandleSelection(false, 23, false, false, 0, false); //What? Is this a door?
            }
            break;
        case 6:
            func_800862F8(2, 0, false);
            func_800862F8(1, 0, false);
            break;
        case 7:
            if (Savegame_EventFlagGet(EventFlag_M1S02_SeenDoorWithHorizontalSlot))
            {
                SysWork_StateStepIncrement(0);
            }
            else
            {
                MapMsg_DisplayAndHandleSelection(false, 26, false, false, 0, false); // What's this? 
            }
            /* fallthrough */
        case 8:
            Gfx_BackgroundSpritesTransition(&g_ItemInspectionImg, &D_800A9A04, D_800E1FD0);
            D_800E1FD0 += Q12(0.0313f);
            if (D_800E1FD0 > Q12(1.0f))
            {
                if (g_SysWork.sysStateStep_C[0] == 8)
                {
                    SysWork_StateStepSet(0, 9);
                    break;
                }
                D_800E1FD0 = Q12(1.0f);
                break;
            }
            break;
        case 9:
            func_800862F8(5, 0, false);
            MapMsg_DisplayAndHandleSelection(false, 27, false, false, 0, false); // In the center of the door is a horizontal slot.
            break;
        case 10:
            func_800862F8(5, 0, false);
            SysWork_StateStepIncrementAfterFade(2, 1, 0, Q12(0.0f), false);
            break;
        default:
            func_800862F8(6, 0, false);
            SysWork_StateStepIncrementAfterFade(0, false, 0, Q12(0.0f), false);
            Savegame_EventFlagSet(EventFlag_M1S02_SeenDoorWithHorizontalSlot);
            sharedFunc_800D2244_0_s00(false);
            SysWork_StateSetNext(SysState_Gameplay);
            break;
        }
}

void func_800DB058(void)
{
    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            sharedFunc_800D20E4_0_s00();
            sharedFunc_800D2E60_0_s00();
            g_SysWork.field_30 = 20;
            g_SysWork.player_4C.chara_0.position_18.vx = Q12(56.5f);
            g_SysWork.player_4C.chara_0.position_18.vz = Q12(19.3f);
            g_SysWork.player_4C.chara_0.rotation_24.vy = Q12(-0.25f);
            Camera_PositionSet(NULL, Q12(60.59f), Q12(-0.83f), Q12(18.34f), 0, 0, 0, 0, true);
            Camera_LookAtSet(NULL, Q12(56.7698f), Q12(-1.45f), Q12(19.34f), 0, 0, 0, 0, true);
            func_8003D03C();
            sharedFunc_800D2EB4_0_s00();
            SysWork_StateStepIncrement(0);
            /* fallthrough */
        case 1:
            SysWork_StateStepIncrementAfterFade(1, false, 0, Q12(0.0f), false);
            break;
        case 2:
            SysWork_StateStepIncrementDelayed(Q12(0.2f), false);
            break;
        case 3:
            func_80086C58(&g_SysWork.player_4C.chara_0, 94);
            break;
        case 4:
            func_8005DC1C(Sfx_Unk1454, &QVECTOR3(55.85f, -1.1f, 19.3f), Q8_CLAMPED(0.5f), 0);
            SysWork_StateStepIncrement(0);
            /* fallthrough */
        case 5:
            MapMsg_DisplayAndHandleSelection(false, 30, 0, 0, 0, false); // Slid the Picture card into the slot.
            break;
        case 6:
            func_8005DC1C(Sfx_Unk1343, &QVECTOR3(56.0f, -1.2f, 19.3f), Q8_CLAMPED(0.5f), 0);
            SysWork_StateStepIncrement(0);
            /* fallthrough */
        case 7:
            func_80086C58(&g_SysWork.player_4C.chara_0, 95);
            break;
        case 8:
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(0.0f), false);
            break;
        default:
            sharedFunc_800D2244_0_s00(true);
            SysWork_StateSetNext(SysState_Gameplay);
            SysWork_StateStepIncrementAfterFade(0, false, 2, Q12(0.0f), false);
            SysWork_StateStepIncrementAfterFade(0, false, 0, Q12(0.0f), false);
            vcReturnPreAutoCamWork(true);
            Savegame_MapMarkingSet(MapMarkFlag_AltSchool1F_SecretDoorArrows);
            func_8003D01C();
            sharedFunc_800D2EF4_0_s00();
            break;
    }
}

void func_800DB310(void) // 0x800DB310
{
    Event_ItemTake(InventoryItemId_PictureCard, DEFAULT_PICKUP_ITEM_COUNT, EventFlag_M1S02_PickupPictureCard, 29);
}

void func_800DB33C(void) // 0x800DB33C
{
    Event_ItemTake(InventoryItemId_RubberBall, DEFAULT_PICKUP_ITEM_COUNT, EventFlag_M1S02_PickupRubberBall, 37);
}

INCLUDE_ASM("asm/maps/map1_s02/nonmatchings/map1_s02", func_800DB368);

INCLUDE_ASM("asm/maps/map1_s02/nonmatchings/map1_s02", func_800DBB7C);

void func_800DBF88(void) // 0x800DBF88
{
    Savegame_EventFlagSet(EventFlag_97);
    MapMsg_DisplayWithTexture(FILE_TIM_LVTRYMSG_TIM, Q12(0.0f), Q12(0.0f), 38);
}

void func_800DBFC8(void) // 0x800DBFC8
{
    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            sharedFunc_800D20E4_0_s00();
            func_80086470(0, InventoryItemId_Shotgun, 0, false);
            SysWork_StateStepIncrement(0);

        case 1:
            func_80085DF0();
            break;

        case 2:
            func_80085EB8(0, &g_SysWork.player_4C.chara_0, 59, false);
            SysWork_StateStepIncrement(0);

        case 3:
            func_80086470(1, InventoryItemId_Shotgun, 0, false);
            break;

        case 4:
            func_80085EB8(1, &g_SysWork.player_4C.chara_0, 0, false);
            break;

        case 5:
            if (Gfx_PickupItemAnimate(InventoryItemId_Shotgun))
            {
                MapMsg_DisplayAndHandleSelection(true, 40, 6, 7, 0, false);
            }

            Savegame_EventFlagSet(EventFlag_M1S02_PickupShotgun);
            break;

        case 6:
            func_80086470(3, InventoryItemId_Shotgun, SHOTGUN_AMMO_PICKUP_ITEM_COUNT, false);
            SysWork_StateStepSet(0, 8);
            break;

        case 7:
            Savegame_EventFlagClear(EventFlag_M1S02_PickupShotgun);
            SysWork_StateStepIncrement(0);

        case 8:
            func_80086C58(&g_SysWork.player_4C.chara_0, 60);
            break;

        default:
            sharedFunc_800D2244_0_s00(false);
            SysWork_StateSetNext(SysState_Gameplay);
            break;
    }
}

INCLUDE_RODATA("asm/maps/map1_s02/nonmatchings/map1_s02", D_800CB934);

INCLUDE_RODATA("asm/maps/map1_s02/nonmatchings/map1_s02", D_800CB940);

INCLUDE_RODATA("asm/maps/map1_s02/nonmatchings/map1_s02", D_800CB94C);

INCLUDE_ASM("asm/maps/map1_s02/nonmatchings/map1_s02", func_800DC1E0);

INCLUDE_ASM("asm/maps/map1_s02/nonmatchings/map1_s02", func_800DCF00);

void func_800DD208(void) // 0x800DD208
{
    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            sharedFunc_800D20E4_0_s00();
            func_80086470(0, InventoryItemId_ClassroomKey, 0, false);
            SysWork_StateStepIncrement(0);

        case 1:
            func_80085DF0();
            break;

        case 2:
            func_80085EB8(0, &g_SysWork.player_4C.chara_0, 59, false);
            SysWork_StateStepIncrement(0);

        case 3:
            func_80086470(1, InventoryItemId_ClassroomKey, 0, false);
            break;

        case 4:
            func_80085EB8(1, &g_SysWork.player_4C.chara_0, 0, false);
            break;

        case 5:
            if (Gfx_PickupItemAnimate(InventoryItemId_ClassroomKey))
            {
                MapMsg_DisplayAndHandleSelection(true, 51, 6, 7, 0, false);
            }

            Savegame_EventFlagSet(EventFlag_M1S02_PickupClassroomKey);
            break;

        case 6:
            func_80086470(3, InventoryItemId_ClassroomKey, 1, false);
            SysWork_StateStepSet(0, 8);
            break;

        case 7:
            Savegame_EventFlagClear(EventFlag_M1S02_PickupClassroomKey);
            SysWork_StateStepIncrement(0);

        case 8:
            func_80086C58(&g_SysWork.player_4C.chara_0, 60);
            break;

        default:
            sharedFunc_800D2244_0_s00(false);
            SysWork_StateSetNext(SysState_Gameplay);
            break;
    }
}
void func_800DD420(void) // 0x800DD420
{
    sharedFunc_800D08B8_0_s00(6, 127);

    sharedFunc_800CB6B0_0_s00(0, g_SavegamePtr->mapOverlayId_A4, 0);

    Savegame_EventFlagClear(EventFlag_225);

    SysWork_StateSetNext(SysState_Gameplay);
}

INCLUDE_ASM("asm/maps/map1_s02/nonmatchings/map1_s02", func_800DD494);

INCLUDE_ASM("asm/maps/map1_s02/nonmatchings/map1_s02", func_800DDA84);

void func_800DEC88(void)
{
    if (Savegame_MapMarkingGet(MapMarkFlag_AltSchool1F_ReceptionArrows))
    {
        if (g_SavegamePtr->gameDifficulty_260 == 1)
        {
            func_80089034(Chara_GreyChild, 12, Q12(134.1f), Q12(21.3f));
        }
        else
        {
            func_80088FF4(Chara_GreyChild, 12, 0);
        }
    }

    if (Savegame_EventFlagGet(EventFlag_98))
    {
        func_80088FF4(Chara_Creaper, 7, 12);
        func_80088FF4(Chara_Creaper, 8, 12);
        if (g_SavegamePtr->gameDifficulty_260 == 1)
        {
            func_80088FF4(Chara_Creaper, 9, 12);
        }
    }
}

INCLUDE_RODATA("asm/maps/map1_s02/nonmatchings/map1_s02", D_800CBA44);
