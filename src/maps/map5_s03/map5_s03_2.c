#include "bodyprog/bodyprog.h"
#include "bodyprog/item_screens.h"
#include "bodyprog/math/math.h"
#include "bodyprog/player_logic.h"
#include "main/rng.h"
#include "maps/map5/map5_s03.h"
#include "maps/characters/kaufmann.h"

#include "maps/shared/sharedFunc_800D88AC_0_s00.h" // 0x800D054C

#include "maps/shared/sharedFunc_800D88C0_0_s00.h" // 0x800D0560

#include "maps/shared/sharedFunc_800D8904_0_s00.h" // 0x800D05A4

#include "maps/shared/sharedFunc_800D891C_0_s00.h" // 0x800D05BC

#include "maps/shared/sharedFunc_800D8928_0_s00.h" // 0x800D05C8

#include "maps/shared/sharedFunc_800D893C_0_s00.h" // 0x800D05DC

#include "maps/shared/sharedFunc_800D8950_0_s00.h" // 0x800D05F0

#include "maps/shared/sharedFunc_800D8964_0_s00.h" // 0x800D0604

#include "maps/shared/sharedFunc_800D8A00_0_s00.h" // 0x800D06A0

#include "maps/shared/sharedFunc_800D9064_0_s00.h" // 0x800D0D04

#include "maps/shared/sharedFunc_800D9078_0_s00.h" // 0x800D0D18

#include "maps/shared/sharedFunc_800D908C_0_s00.h" // 0x800D0D2C

#include "maps/shared/sharedFunc_800D9188_0_s00.h" // 0x800D0E28

#include "maps/shared/Anim_StartKeyframeIdxGet.h" // 0x800D0EF0

#include "maps/shared/sharedFunc_800D923C_0_s00.h" // 0x800D0EFC

#include "maps/shared/sharedFunc_800D929C_0_s00.h" // 0x800D0F5C

#include "maps/shared/Map_RoomIdxGet.h" // 0x800D0F6C

#include "maps/shared/Map_RoomBgmInit_CheckCond.h" // 0x800D1004

#include "maps/shared/Map_RoomBgmInit_0_s02_CondTrue.h" // 0x800D1038

#include "maps/shared/Map_RoomBgmInit_0_s02_CondFalse.h" // 0x800D10B4

void func_800D1340(void) {} // 0x800D1340

#include "maps/shared/SysWork_StateStepIncrementAfterTime.h" // 0x800D1348

#include "maps/shared/MapEvent_DoorJammed.h" // 0x800D13E0

#include "maps/shared/MapEvent_DoorLocked.h" // 0x800D1474

#include "maps/shared/MapEvent_DoorUnlocked.h" // 0x800D1508

const char* MAP_MESSAGES[] = {
    #include "maps/shared/mapMsg_common.h"
    "\tI've_got_a_ ~C2 Motorcycle_key ~C7 . ~E ",
    "\tThere's_a_crack. ~E ",
    "\tThere's_a_crack. ~N\n\tSomething_glints_inside. ",
    "\tThe_crack_is_too_small ~N\n\tto_reach_in. ~E ",
    "\tAn_old_motorcycle. ",
    "\tLooks_like_it's_been_sitting ~N\n\there_for_years. ",
    "\t~J1(1.5) ",
    "\tThat's_weird. ",
    "\tThe_dust_is_wiped_away ~N\n\tjust_around_the_gas_tank_cap. ~E ",
    "\tA_small_glass_vial, ~N\n\twrapped_in_a_plastic_bag. ",
    "\tWhat's_this? ~E ",
    "\tIt's_like_the_busted_vial ~N\n\tI_found_in_the_director's_office ~N\n\tat_the_hospital. ~E ",
    "~J0(1.3)\tGive_me_that! ",
    "~J0(1.2)\tWhat_is_this? ~E ",
    "~J1(2.0)\tThat's_none_of_your_business! ",
    "~J1(3.3)\tInstead_of_messing_with_that, ~N\n\t\t\thow_about_coming_up_with_a_way ~N\n\t\t\tto_get_out_of_here? ",
    "~J1(0.9)\tHumph. ~E ",
    "~J1(2.6)\tYou_shouldn't_be_hanging ~N\n\t\t\taround_here_goofing_off! ",
    "~J1(1.3)\tWhat_do_you_think ~N\n\t\t\tyou_are_doing? ",
    "~J1(3.0)\tYou_want_to_get_yourself_killed!? ~N\n\t\t\tGet_outta_here! ",
    "~J1(1.9)\tOkay,_take_it_easy. ~E ",
    "~J1(3.2)\tUnless_you_want_to_die, ~N\n\t\t\tkeep_your_mind_on_business. ",
    "~J1(0.8)\tGot_it? ~E ",
    "~J1(3.3)\tThat_guy's_gotta_be_involved ~N\n\t\t\tin_the_local_drug_racket. ",
    "~J1(3.1)\tMan,_was_he_pissed. ~N\n\t\t\tAnd_in_such_a_rush,_too. ",
    "~J1(1.8)\tThat_was_probably_dope ~N\n\t\t\tin_the_bottle. ",
    "~J1(3.9)\tAnyway,_better_let_him_do_as_he ~N\n\t\t\tpleases._There's_more_than ~N\n\t\t\tmy_life_at_stake. ~E ",
    "~J1(2.0)\tI_guess_I_wasted_my_time. ",
    "~J1(2.0)\tBetter_hurry.... ~N\n\t\t\tI'm_worried_about_Cheryl. ~E ",
    "~J1(3.1)\tMan,_was_he_pissed. ~N\n\t\t\tAnd_in_such_a_rush,_too. ~E ",
    "\tThere_is_a_newspaper. ~E ",
    "\tNewspaper. ",
    "\tIt's_the_same_date_as ~N\n\tthe_one_in_the_hospital... ~E ",
    "~L4 ~C3 Investigation_stalled. ~N\n\t[PTV]_dealers_still_at_large. ~N\n\t~N\n\tSuspicious_deaths_continue. ~N\n\tLike_the_anti-drug_mayor, ~N\n\ta_narcotics_officer_dies_of ~N\n\ta_sudden_heart_failure_of ~N\n\tunknown_origin. ~E ",
    "~C3\tSeptember_10 ",
    "~C3\tTook_package. ~N\n\t\tTold_to_sit_on_it_awhile. ",
    "~C3\tDon't_want_to_get_involved, ~N\n\t\tbut_can't_disobey... ",
    "~C3\tHe's_probably_linked_to_the_death ~N\n\t\tof_the_mayor_and_others. ~E ",
    "\tThere_is_a_ ~C2 Magnet ~C7 . ~N\n\tTake_it? ~S4 ",
    "\tUsed_the_ ~C2 Motorcycle_key ~C7 . ~E ",
    "\tBatteries,_oil_cans, ~N\n\tand_other_items_line_the_shelves. ",
    "\tA_fine_layer_of_~N\n\tdust_covers_everything, ~N\n\tas_if_long_abandoned. ~E ",
    "\tThere's_a_radio ~N\n\ton_top_of_the_cabinet. ",
    "\tIt's_completely_dead. ~N\n\tMaybe_it's_broken. ~E ",
    "\tA_poster_is_on_the_wall. ~N\n\tDon't_look_at_that_now,_though. ~E ",
    "\tThere's_a_TV_set. ",
    "\tThe_power_must_be_out. ~N\n\tIt_doesn't_work. ~E ",
    "\tThere's_a_guest_register. ~N\n\tNothing_special_written_here. ~E ",
    "\tNothing_special. ~E ",
    "\tThere's_a_vending_machine. ~N\n\tIt_doesn't_work. ~E ",
    "\tNobody_inside. ~E ",
    "\tDo_you_want_to_push ~N\n\tthe_shelf? ~S4 ",
    "\tAn_old_motorcycle. ~E "
};

void MapEvent_CommonItemTake(void) // 0x800D159C
{
    u32 pickupType;
    s32 eventFlagIdx;

    pickupType   = CommonPickupItemId_FirstAidKit;
    eventFlagIdx = 0;

    switch (g_MapEventData->pointOfInterestIdx_5)
    {
        case 37:
            pickupType   = CommonPickupItemId_HealthDrink;
            eventFlagIdx = EventFlag_M5S03_HealthDrink0;
            break;

        case 38:
            pickupType   = CommonPickupItemId_ShotgunShells;
            eventFlagIdx = EventFlag_M5S03_ShotgunShells;
            break;

        case 39:
            pickupType   = CommonPickupItemId_HealthDrink;
            eventFlagIdx = EventFlag_M5S03_HealthDrink1;
            break;
    }

    Event_CommonItemTake(pickupType, eventFlagIdx);
}

void func_800D1628(void) // 0x800D1628
{
    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            Player_ControlFreeze();
            func_80086470(0, InventoryItemId_MotorcycleKey, 0, false);
            SysWork_StateStepIncrementAfterFade(0, true, 2, Q12(0.0f), false);

            // Warp player.
            g_SysWork.playerWork_4C.player_0.position_18.vx = Q12(103.64f);
            g_SysWork.playerWork_4C.player_0.position_18.vz = Q12(59.49f);
            g_SysWork.playerWork_4C.player_0.rotation_24.vy = Q12_ANGLE(51.0f);

            // Warp camera.
            Camera_PositionSet(NULL, Q12(103.54f), Q12(-2.91f), Q12(59.2f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);
            Camera_LookAtSet(NULL, Q12(104.65f), Q12(0.72f), Q12(60.44f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);

            SysWork_StateStepIncrement(0);

        case 1:
            func_80085DF0();
            break;

        case 2:
            func_80085EB8(0, &g_SysWork.playerWork_4C.player_0, 187, false);
            SysWork_StateStepIncrement(0);

        case 3:
            SysWork_StateStepIncrementDelayed(Q12(3.8f), false);
            break;

        case 4:
            func_80085EB8(2, &g_SysWork.playerWork_4C.player_0, 0, false);
            func_8005DC1C(Sfx_Unk1598, &QVECTOR3(104.25f, 0.1f, 60.0f), Q8_CLAMPED(0.5f), 0);
            SysWork_StateStepIncrement(0);

        case 5:
            func_80086470(1, InventoryItemId_MotorcycleKey, 0, false);
            break;

        case 6:
            if (Gfx_PickupItemAnimate(InventoryItemId_MotorcycleKey))
            {
                MapMsg_DisplayAndHandleSelection(false, 15, 0, 0, 0, false);

                if (g_SysWork.sysStateStep_C[0] != 6)
                {
                    SD_Call(Sfx_MenuConfirm);
                }
            }
            break;

        case 7:
            func_80086D04(&g_SysWork.playerWork_4C.player_0);
            break;

        default:
            Player_ControlUnfreeze(false);

            SysWork_StateSetNext(SysState_Gameplay);
            vcReturnPreAutoCamWork(true);

            Player_ItemRemove(InventoryItemId_Magnet, 1);
            func_80086470(3, InventoryItemId_MotorcycleKey, 1, false);
            Savegame_EventFlagSet(EventFlag_390);

            SysWork_StateStepIncrementAfterFade(0, false, 2, Q12(0.0f), false);
            break;
    }
}

void func_800D1904(void) // 0x800D1904
{
    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            Player_ControlFreeze();
            func_800862F8(0, FILE_TIM_MOTELKEY_TIM, false);
            SysWork_StateStepIncrement(0);

        case 1:
            func_80085DF0();
            break;

        case 2:
            func_80086C58(&g_SysWork.playerWork_4C.player_0, 59);
            break;

        case 3:
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(0.0f), false);
            break;

        case 4:
            func_800862F8(1, FILE_1ST_2ZANKO80_TIM, false);
            break;

        case 5:
            SysWork_StateStepIncrementAfterFade(2, false, 0, Q12(0.0f), false);
            func_800862F8(2, FILE_1ST_2ZANKO80_TIM, false);
            break;

        case 6:
            MapMsg_DisplayAndHandleSelection(false, 17, 0, 0, 0, false);
            func_800862F8(2, FILE_1ST_2ZANKO80_TIM, false);
            break;

        case 7:
            SysWork_StateStepIncrementAfterFade(2, false, 0, Q12(0.0f), false);
            func_800862F8(2, FILE_1ST_2ZANKO80_TIM, false);
            break;

        case 8:
            SysWork_StateStepIncrementAfterFade(2, false, 0, Q12(0.0f), false);
            break;

        case 9:
            func_80086C58(&g_SysWork.playerWork_4C.player_0, 60);
            break;

        default:
            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);
            break;
    }
}

void func_800D1A84(void) // 0x800D1A84
{
    MapMsg_DisplayWithTexture(FILE_TIM_DIARYMTL_TIM, Q12(2.5f), Q12(2.0f), 49);
    Savegame_EventFlagSet(EventFlag_398);
}

void func_800D1ACC(void) // 0x800D1ACC
{
    Event_ItemTake(InventoryItemId_Magnet, DEFAULT_PICKUP_ITEM_COUNT, EventFlag_M5S03_PickupMagnet, 53);
}

void func_800D1AF8(void) // 0x800D1AF8
{
    SVECTOR3 unused;
    VECTOR3  lightIntPos;

    if ((g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.skip_4) &&
        g_SysWork.sysStateStep_C[0] >= 14 && g_SysWork.sysStateStep_C[0] < 29)
    {
        SysWork_StateStepSet(0, 32);
    }

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            Player_ControlFreeze();

            D_800D6F54 = 0;
            D_800D6F58 = NO_VALUE;

            func_8003D03C();
            sharedFunc_800D2EB4_0_s00();

            WorldGfx_PlayerHeldItemSet(InventoryItemId_CutsceneAglaophotis);

            D_800D3C40 = Fs_QueueStartReadTim(FILE_TIM_BICITEM_TIM, FS_BUFFER_1, &g_ItemInspectionImg);
            Fs_QueueStartRead(FILE_ANIM_GARAGE1_DMS, FS_BUFFER_17);

            Chara_Load(0, Chara_Kaufmann, g_SysWork.npcCoords_FC0, CHARA_FORCE_FREE_ALL, NULL, NULL);
            func_8005DC1C(Sfx_Unk1597, &QVECTOR3(101.706f, -0.889f, 19.7684f), Q8_CLAMPED(0.5f), 0);

            SysWork_StateStepIncrement(0);

        case 1:
            MapMsg_DisplayAndHandleSelection(false, 54, 0, 0, 0, false); // "Used the Motorcycle Key."
            break;

        case 2:
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(0.0f), false);
            break;

        case 3:
            func_8005DC1C(Sfx_Unk1596, &QVECTOR3(101.706f, -0.889f, 19.7684f), Q8_CLAMPED(0.5f), 0);
            SysWork_StateStepIncrement(0);

        case 4:
            if (Fs_QueueIsEntryLoaded(D_800D3C40))
            {
                SysWork_StateStepIncrement(0);
                func_8003D01C();
            }
            break;

        case 5:
            func_800862F8(2, FILE_1ST_2ZANKO80_TIM, false);
            SysWork_StateStepIncrementAfterFade(2, false, 0, Q12(0.0f), false);
            break;

        case 6:
            func_800862F8(2, FILE_1ST_2ZANKO80_TIM, false);
            MapMsg_DisplayAndHandleSelection(false, 24, 0, 0, 0, false); // "A small glass vial, wrapped in a plastic bag."

            if (g_SysWork.sysStateStep_C[0] != 6 && !Savegame_EventFlagGet(EventFlag_204))
            {
                // Skip next step if event flag not set.
                SysWork_StateStepSet(0, 8);
            }
            break;

        case 7:
            func_800862F8(2, FILE_1ST_2ZANKO80_TIM, false);
            MapMsg_DisplayAndHandleSelection(false, 26, 0, 0, 0, false); // "It's like the busted vial I found in the director's office at the hospital."
            break;

        case 8:
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(0.0f), false);
            func_800862F8(2, FILE_1ST_2ZANKO80_TIM, false);
            break;

        case 9:
            Chara_ProcessLoads();
            DmsHeader_FixOffsets(FS_BUFFER_17);
            SysWork_StateStepIncrement(0);

        case 10:
            func_80087EDC(34);
            break;

        case 11:
            g_SysWork.field_30    = 20;
            g_SysWork.flags_22A4 |= SysFlag2_3;

            func_8008D438();

            g_SysWork.pointLightIntensity_2378 = Q12(1.0f);
            g_SysWork.field_235C = NULL;
            g_SysWork.field_236C = NULL;

            D_800D6F58 = 0;

            func_80085EB8(0, &g_SysWork.playerWork_4C.player_0, 159, false);

            SysWork_StateStepIncrement(0);
            break;

        case 12:
            SysWork_StateStepIncrementAfterFade(2, false, 0, Q12(0.0f), false);
            func_80085EB8(2, &g_SysWork.playerWork_4C.player_0, 0, false);
            break;

        case 13:
            Chara_Spawn(Chara_Kaufmann, 0, Q12(140.5f), Q12(23.0f), Q12_ANGLE(0.0f), 3);

            func_8005DC1C(Sfx_Unk1595, &QVECTOR3(103.0f, -1.2f, 17.6f), Q8_CLAMPED(0.5f), 0);

            func_80085EB8(3, &g_SysWork.playerWork_4C.player_0, 0, false);

            Savegame_EventFlagSet(EventFlag_395);
            SysWork_StateStepIncrement(0);

        case 14:
            SysWork_StateStepIncrementAfterTime(&D_800D6F58, Q12(10.0f), Q12(0.0f), Q12(17.0f), true, true);
            Model_AnimFlagsClear(&g_SysWork.npcs_1A0[0].model_0, 2);
            break;

        case 15:
            func_80086C58(&g_SysWork.npcs_1A0[0], 16);
            Model_AnimFlagsSet(&g_SysWork.npcs_1A0[0].model_0, 2);
            SysWork_StateStepIncrementAfterTime(&D_800D6F58, Q12(10.0f), Q12(18.0f), Q12(38.0f), true, false);
            break;

        case 16:
            Map_MessageWithAudio(27, &D_800D6F54, &D_800D3BDC);
            SysWork_StateStepIncrementAfterTime(&D_800D6F58, Q12(10.0f), Q12(18.0f), Q12(38.0f), true, false);
            break;

        case 17:
            func_80085EB8(0, &g_SysWork.playerWork_4C.player_0, 169, false);
            func_80085EB8(0, &g_SysWork.npcs_1A0[0], 15, false);
            SysWork_StateStepIncrement(0);

        case 18:
            SysWork_StateStepIncrementAfterTime(&D_800D6F58, Q12(10.0f), Q12(39.0f), Q12(75.0f), true, true);
            break;

        case 19:
            func_80085EB8(0, &g_SysWork.playerWork_4C.player_0, 51, false);
            func_80085EB8(0, &g_SysWork.npcs_1A0[0], 5, false);
            func_8003D03C();

            D_800D6F58 = Q12(76.0f);

            SysWork_StateStepIncrement(0);

        case 20:
            Map_MessageWithAudio(29, &D_800D6F54, &D_800D3BDC);
            break;

        case 21:
            Map_MessageWithAudio(32, &D_800D6F54, &D_800D3BDC);
            D_800D6F58 = Q12(77.0f);
            break;

        case 22:
            D_800D6F58 = Q12(78.0f);
            Map_MessageWithAudio(36, &D_800D6F54, &D_800D3BDC);
            break;

        case 23:
            func_80085EB8(0, &g_SysWork.playerWork_4C.player_0, 72, false);
            SysWork_StateStepIncrement(0);

        case 24:
            SysWork_StateStepIncrementAfterTime(&D_800D6F58, Q12(10.0f), Q12(78.0f), Q12(98.0f), true, true);
            break;

        case 25:
            func_80085EB8(0, &g_SysWork.npcs_1A0[0], 1, false);
            sharedFunc_800D2EF4_0_s00();
            WorldGfx_PlayerPrevHeldItem(&g_SysWork.playerCombat_38);
            sharedFunc_800D2EB4_0_s00();
            SysWork_StateStepIncrement(0);

        case 26:
            SysWork_StateStepIncrementAfterTime(&D_800D6F58, Q12(10.0f), Q12(99.0f), Q12(121.0f), true, true);
            break;

        case 27:
            func_80088F94(&g_SysWork.npcs_1A0[0], 0, 0);
            func_8005DC1C(Sfx_Unk1595, &QVECTOR3(103.0f, -1.2f, 17.6f), Q8_CLAMPED(0.5f), 0);

            Savegame_EventFlagClear(EventFlag_395);

            D_800D6F58 = Q12(122.0f);

            SysWork_StateStepIncrement(0);

        case 28:
            if (Savegame_EventFlagGet(EventFlag_396) &&
                Savegame_EventFlagGet(EventFlag_397) &&
                Savegame_EventFlagGet(EventFlag_398))
            {
                MapMsg_DisplayAndHandleSelection(false, 38, 0, 0, 0, false); // "That guy's gotta be involved in the local drug racket."
            }
            else
            {
                MapMsg_DisplayAndHandleSelection(false, 44, 0, 0, 0, false); // "Man, was he pissed. And in such a rush, too."
            }
            break;

        case 29:
            vcReturnPreAutoCamWork(true);

            D_800D6F58 = NO_VALUE;

            sharedFunc_800D2EF4_0_s00();
            func_8003D01C();
            func_8008D448();
            Game_FlashlightAttributesFix();

            g_SysWork.pointLightIntensity_2378 = Q12(1.0f);

            SysWork_StateStepIncrement(0);

        case 30:
            MapMsg_DisplayAndHandleSelection(false, 42, 0, 0, 0, false); // "I guess I wasted my time."
            break;

        case 31:
            SysWork_StateStepReset();
            break;

        case 32:
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(0.0f), false);
            break;

        case 33:
            sharedFunc_800D2EF4_0_s00();

            WorldGfx_PlayerPrevHeldItem(&g_SysWork.playerCombat_38);
            func_80088F94(&g_SysWork.npcs_1A0[0], 0, 0);

            Fs_QueueWaitForEmpty();

            vcReturnPreAutoCamWork(true);
            SysWork_StateStepIncrementAfterFade(0, false, 0, Q12(0.0f), false);

            D_800D6F58 = Q12(122.0f);

            SysWork_StateStepIncrement(0);
            break;

        default:
            Player_ControlUnfreeze(false);

            SysWork_StateSetNext(SysState_Gameplay);

            vcReturnPreAutoCamWork(true);

            Savegame_EventFlagSet(EventFlag_391);

            SysWork_StateStepIncrementAfterFade(0, false, 2, Q12(0.0f), false);

            D_800D6F58 = NO_VALUE;

            func_8008D448();
            Game_FlashlightAttributesFix();

            g_SysWork.pointLightIntensity_2378 = Q12(1.0f);

            SD_Call(19);
            sharedFunc_800D2EF4_0_s00();
            func_8003D01C();
            break;
    }

    if (D_800D6F58 >= 0)
    {
        Dms_CharacterGetPosRot(&g_SysWork.playerWork_4C.player_0.position_18, &g_SysWork.playerWork_4C.player_0.rotation_24, "HERO", D_800D6F58, FS_BUFFER_17);
        Dms_CharacterGetPosRot(&g_SysWork.npcs_1A0[0].position_18, &g_SysWork.npcs_1A0[0].rotation_24, "KAU", D_800D6F58, FS_BUFFER_17);
        vcChangeProjectionValue(Dms_CameraGetTargetPos(&D_800D6F38, &D_800D6F48, NULL, D_800D6F58, FS_BUFFER_17));
        vcUserCamTarget(&D_800D6F38, NULL, true);
        vcUserWatchTarget(&D_800D6F48, NULL, true);

        // "LIGHT", cutscene light position?
        Dms_CharacterGetPosRot(&g_SysWork.pointLightPosition_2360, &unused, "LIGHT", D_800D6F58, FS_BUFFER_17);

        // "L_INT", interior light or intersection point?
        Dms_CharacterGetPosRot(&lightIntPos, &unused, "L_INT", D_800D6F58, FS_BUFFER_17);

        // Set light rotation.
        g_SysWork.pointLightRot_2370.vx = -ratan2(lightIntPos.vy - g_SysWork.pointLightPosition_2360.vy, Math_Vector2MagCalc(lightIntPos.vx - g_SysWork.pointLightPosition_2360.vx, lightIntPos.vz - g_SysWork.pointLightPosition_2360.vz));
        g_SysWork.pointLightRot_2370.vy =  ratan2(lightIntPos.vx - g_SysWork.pointLightPosition_2360.vx, lightIntPos.vz - g_SysWork.pointLightPosition_2360.vz);
        g_SysWork.pointLightRot_2370.vz = Q12_ANGLE(0.0f);
    }
}

void func_800D2640(void) // 0x800D2640
{
    MapMsg_DisplayWithTexture1(FILE_TIM_NEWSP2_TIM, Q12(0.0f), Q12(0.0f), 46, 48);

    // @bug NTSC-U release is missing code to set `EventFlag_M5S03_SeenSecondNewspaper` here,
    // causing later newspaper in `M7S01` & `M7S02` not to appear.
#if defined(VERSION_NTSCJ) || defined(VERSION_PAL)
    Savegame_EventFlagSet(EventFlag_M5S03_SeenSecondNewspaper);
#endif
}

void func_800D2674(void) // 0x800D2674
{
    s32 moveAmt;

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            Player_ControlFreeze();
            SysWork_StateStepIncrement(0);

        case 1:
            func_80085DF0();
            break;

        case 2:
            MapMsg_DisplayAndHandleSelection(true, 66, 4, 3, 0, false); // "Do you want to push the shelf?"
            break;

        case 3:
            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);
            break;

        case 4:
            SysWork_StateStepIncrementAfterFade(0, true, 2, Q12(0.0f), false);

            g_SysWork.playerWork_4C.player_0.position_18.vx = Q12(104.17f);
            g_SysWork.playerWork_4C.player_0.position_18.vz = Q12(59.5f);
            g_SysWork.playerWork_4C.player_0.rotation_24.vy = Q12_ANGLE(0.0f);

            Camera_PositionSet(NULL, Q12(102.07f), Q12(-1.42f), Q12(58.77f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);
            Camera_LookAtSet(NULL, Q12(105.14f), Q12(0.37f), Q12(60.61f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);

            func_80085EB8(0U, &g_SysWork.playerWork_4C.player_0, 105, false);
            SD_Call(Sfx_Unk1520);
            SysWork_StateStepIncrement(0);

        case 5:
        case 6:
            moveAmt                                          = Q12_MULT_FLOAT_PRECISE(g_DeltaTime, 0.14f);
            g_SysWork.playerWork_4C.player_0.position_18.vz += moveAmt;
            g_WorldObject_Movaches.position_1C.vz      += moveAmt;

            if (g_SysWork.sysStateStep_C[0] == 5)
            {
                if (g_WorldObject_Movaches.position_1C.vz > Q12(60.35f))
                {
                    SysWork_StateStepSet(0, 6);
                }

                D_800D3C44 = MIN(D_800D3C44 + (g_DeltaTime * 2), Q12(1.0f));
            }
            else
            {
                if (g_WorldObject_Movaches.position_1C.vz > Q12(60.44f))
                {
                    moveAmt = g_WorldObject_Movaches.position_1C.vz - Q12(60.44f);

                    g_SysWork.playerWork_4C.player_0.position_18.vz -= moveAmt;
                    g_WorldObject_Movaches.position_1C.vz      -= moveAmt;
                }

                // `D_800D3C44 = MAX(D_800D3C44 - (g_DeltaTime * 2), 0);`?
                D_800D3C44 = (D_800D3C44 - (g_DeltaTime * 2)) >= 0 ? (D_800D3C44 - ((u16)g_DeltaTime * 2)) : 0;

                SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(0.0f), false);
            }

            func_8005DE0C(Sfx_Unk1538, &g_WorldObject_Movaches.position_1C, D_800D3C44 >> 5, Q12(12.0f), 0);
            break;

        default:
            Savegame_EventFlagSet(EventFlag_389);

            SysWork_StateStepIncrementAfterFade(0, false, 2, Q12(0.0f), false);
            SysWork_StateStepIncrementAfterFade(0, false, 0, Q12(0.0f), false);
            Player_ControlUnfreeze(true);
            SysWork_StateSetNext(SysState_Gameplay);

            vcReturnPreAutoCamWork(true);
            Sd_SfxStop(Sfx_Unk1520);
            break;
    }
}

void Map_WorldObjectsInit(void) // 0x800D2A04
{
    WorldObjectNoRotInit(&g_WorldObject_Movaches, "MOVACHES", 104.2225f, -0.1683f, 60.0667f);

    WorldObject_ModelNameSet(&g_WorldObject_SavePad, D_800A99E4.savePadName_4);

    WorldObjectPoseInit(&g_WorldObjectPose_SavePad[0], 58.1048f, -0.9f, 62.5574f, 0.0f, 17.41f, 0.0f);
    WorldObjectPoseInit(&g_WorldObjectPose_SavePad[1], 57.905f, -0.9f, 22.5574f, 0.0f, 17.41f, 0.0f);

    WorldObjectInit(&g_WorldObject_Mag, "MAG_HIDE", 61.1727f, 0.43f, 18.6243f, 0.0f, 60.3f, 0.0f);

    WorldObject_ModelNameSet(&g_CommonWorldObjects[0], D_800A99E4.firstAidKitName_8);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[1], D_800A99E4.healthDrinkName_C);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[2], D_800A99E4.ampouleName_10);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[3], D_800A99E4.handgunBulletsName_14);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[4], D_800A99E4.shotgunShellsName_18);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[5], D_800A99E4.rifleShellsName_1C);
}

void Map_WorldObjectsUpdate(void) // 0x800D2B68
{
    s32 flags;
    MAP_CHUNK_CHECK_VARIABLE_DECL();

    flags = 0;

    if (PLAYER_IN_MAP_CHUNK(vx, 1, 3, -1, 3) && PLAYER_IN_MAP_CHUNK(vz, 1, 2, -1, 2))
    {
        if (Savegame_EventFlagGet(EventFlag_389))
        {
            D_800D6F8C = 0x3C720; // TODO: `Q12(60.4454f)`? Weird number.
        }
        else
        {
            flags = 1 << 1;
        }

        WorldGfx_ObjectAdd(&g_WorldObject_Movaches.object_0, &g_WorldObject_Movaches.position_1C, &(SVECTOR3){ 0, 0, 0 });
    }
    else
    {
        func_80069844(0xFFFF);
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, 2, -1, 2) && PLAYER_IN_MAP_CHUNK(vz, 1, 2, -1, 2))
    {
        WorldGfx_ObjectAdd(&g_WorldObject_SavePad, &g_WorldObjectPose_SavePad[0].position_0, &g_WorldObjectPose_SavePad[0].rotation_C);
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, 2, -1, 2) && PLAYER_IN_MAP_CHUNK(vz, 0, 0, -1, 1))
    {
        WorldGfx_ObjectAdd(&g_WorldObject_SavePad, &g_WorldObjectPose_SavePad[1].position_0, &g_WorldObjectPose_SavePad[1].rotation_C);

        if (!Savegame_EventFlagGet(EventFlag_M5S03_PickupMagnet))
        {
            WorldGfx_ObjectAdd(&g_WorldObject_Mag.object_0, &g_WorldObject_Mag.position_1C, &g_WorldObject_Mag.rotation_28);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, 3, -1, 3) && PLAYER_IN_MAP_CHUNK(vz, 1, 2, -1, 2))
    {
        if (!Savegame_EventFlagGet(EventFlag_M5S03_HealthDrink0))
        {
            WorldGfx_ObjectAdd(&g_WorldObject_HealthDrink, &g_WorldObjectPose_HealthDrink0.position_0, &g_WorldObjectPose_HealthDrink0.rotation_C);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, 3, -1, 3) && PLAYER_IN_MAP_CHUNK(vz, 0, 0, -1, 1))
    {
        if (!Savegame_EventFlagGet(EventFlag_M5S03_ShotgunShells))
        {
            WorldGfx_ObjectAdd(&g_WorldObject_ShotgunShells, &g_WorldObjectPose_ShotgunShells.position_0, &g_WorldObjectPose_ShotgunShells.rotation_C);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, 3, -1, 3) && PLAYER_IN_MAP_CHUNK(vz, 0, 0, -1, 1))
    {
        if (!Savegame_EventFlagGet(EventFlag_M5S03_HealthDrink1))
        {
            WorldGfx_ObjectAdd(&g_WorldObject_HealthDrink, &g_WorldObjectPose_HealthDrink1.position_0, &g_WorldObjectPose_HealthDrink1.rotation_C);
        }
    }

    func_80069844(0xFFFF);
    func_8006982C(flags);
}
