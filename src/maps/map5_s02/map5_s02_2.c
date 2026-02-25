#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "bodyprog/player_logic.h"
#include "main/rng.h"
#include "maps/map5/map5_s02.h"
#include "maps/characters/kaufmann.h"

#include "maps/shared/sharedFunc_800D88AC_0_s00.h" // 0x800D3AFC

#include "maps/shared/sharedFunc_800D88C0_0_s00.h" // 0x800D3B10

#include "maps/shared/sharedFunc_800D8904_0_s00.h" // 0x800D3B54

#include "maps/shared/sharedFunc_800D891C_0_s00.h" // 0x800D3B6C

#include "maps/shared/sharedFunc_800D8928_0_s00.h" // 0x800D3B78

#include "maps/shared/sharedFunc_800D893C_0_s00.h" // 0x800D3B8C

#include "maps/shared/sharedFunc_800D8950_0_s00.h" // 0x800D3BA0

#include "maps/shared/sharedFunc_800D8964_0_s00.h" // 0x800D3BB4

#include "maps/shared/sharedFunc_800D8A00_0_s00.h" // 0x800D3C50

#include "maps/shared/sharedFunc_800D9064_0_s00.h" // 0x800D42B4

#include "maps/shared/sharedFunc_800D9078_0_s00.h" // 0x800D42C8

#include "maps/shared/sharedFunc_800D908C_0_s00.h" // 0x800D42DC

#include "maps/shared/sharedFunc_800D9188_0_s00.h" // 0x800D43D8

#include "maps/shared/Anim_StartKeyframeIdxGet.h" // 0x800D44A0

#include "maps/shared/sharedFunc_800D923C_0_s00.h" // 0x800D44AC

#include "maps/shared/sharedFunc_800D929C_0_s00.h" // 0x800D450C

#include "maps/shared/Map_RoomIdxGet.h" // 0x800D451C

#include "maps/shared/Map_RoomBgmInit_CheckCond.h" // 0x800D45B4

#include "maps/shared/Map_RoomBgmInit_0_s02_CondTrue.h" // 0x800D45E8

#include "maps/shared/Map_RoomBgmInit_0_s02_CondFalse.h" // 0x800D4664

void Gfx_LoadingScreen_StageString(void) {}

#include "maps/shared/SysWork_StateStepIncrementAfterTime.h" // 0x800D48F8

#include "maps/shared/MapEvent_DoorJammed.h" // 0x800D4990

#include "maps/shared/MapEvent_DoorLocked.h" // 0x800D4A24

const char* MAP_MESSAGES[] = {
    #include "maps/shared/mapMsg_common.h"
    "~J0(8.7)\t~E ",
    "~J0(1.2)\tAre_you_OK? ~E ",
    "~J0(1.4)\tYeah,_I_guess_so. ",
    "~J0(3.0)\tBut_I'm_beat. ~N\n\t\t\tI_thought_I_was_a_goner_there. ~E ",
    "~J1(3.0)\tSo,_how'd_it_go? ~N\n\t\t\tDid_you_find_a_way_out? ",
    "~J1(2.4)\tNo._Not_yet. ",
    "~J1(1.1)\tHow_about_you? ",
    "~J1(1.0)\tZip. ",
    "~J1(1.8)\tBut_it's_too_soon_to_give_up. ",
    "~J1(2.8)\tThis_craziness_can't ~N\n\t\t\tgo_on_forever. ",
    "~J1(3.4)\tA_military_rescue_squad ~N\n\t\t\tshould_be_here_any_time_now. ",
    "~J1(2.8)\tIf_they_come_through_the_town, ~N\n\t\t\twe're_home_free. ",
    "~J1(1.7)\tI_hope_so. ",
    "~J1(1.4)\tI_better_get_going. ",
    "~J1(3.4)\tThis_isn't_the_time_to_stand ~N\n\t\t\taround_flapping_our_gums. ~E ",
    "~J0(2.0)\tDo_you_know ~N\n\t\t\ta_girl_called_Alessa? ~E ",
    "~J0(1.0)\tNo. ~E ",
    "\tKaufmann_must_have_dropped ~N\n\tthis. ",
    "\tLooks_like_it's_full_of_stuff... ~E ",
    "\tWhat_is_this? ~N\n\tDrugs? ~E ",
    "~C3\tAugust_20 ",
    "~C3\tHe_came_by._I_handed_over_the ~N\n\t\tpackage_that_the_woman_left_here. ",
    "~C3\tSeptember_12 ",
    "~C3\tHe_showed_up_at_Norman's,_too. ",
    "~C3\tDon't_want_to_be_involved_with ~N\n\t\tthe_likes_of_them_anymore,_but... ",
    "~C3\tI'm_getting_creeped_out ~N\n\t\teven_more_than_before. ",
    "~C3\tThought_of_leaving_town,_but ~N\n\t\tI'm_afraid_of_what_will_happen ~N\n\t\tif_I_do. ~E ",
    "~C3\t3_loaves_of_bread. ~N\n\t\t3_cartons_of_milk. ~N\n\t\t2_dozen_eggs. ",
    "~C3\tDeliver_to_back_door_daily_8_a.m. ~N\n\t\tRear_entrance_code_0886 ~N\n\t\t________________________Norman_Young ~E ",
    "~C3\tNorman's_Grand_Opening. ~E ",
    "\tThere_is_a_drawer. ~N\n\tDo_you_want_to_open_it? ~S4 ",
    "\tUsed_the_ ~C2 Safe_key ~C7 . ~E ",
    "\tThere_is_a_ ~C2 Safe_key ~C7 . ~N\n\tTake_it? ~S4 ",
    "\tIt's_locked. ~E ",
    "\tI've_got_a_ ~C2 Receipt ~C7 . ~E ",
    "\tI've_got_a_ ~C2 Kaufmann_key ~C7 . ~E "
};

void MapEvent_CommonItemTake(void) // 0x800D4AB8
{
    u32 pickupType;
    s32 eventFlagIdx;

    pickupType   = CommonPickupItemId_FirstAidKit;
    eventFlagIdx = 0;

    switch (g_MapEventData->pointOfInterestIdx_5)
    {
        case 15:
            pickupType   = CommonPickupItemId_HealthDrink;
            eventFlagIdx = EventFlag_M5S02_HealthDrink0;
            break;

        case 16:
            pickupType   = CommonPickupItemId_HealthDrink;
            eventFlagIdx = EventFlag_M5S02_HealthDrink1;
            break;

        case 17:
            pickupType   = CommonPickupItemId_RifleShells;
            eventFlagIdx = EventFlag_M5S02_RifleShells;
            break;

        case 18:
            pickupType   = CommonPickupItemId_HealthDrink;
            eventFlagIdx = EventFlag_M5S02_HealthDrink2;
            break;
    }

    Event_CommonItemTake(pickupType, eventFlagIdx);
}

void func_800D4B58(void) // 0x800D4B58
{
    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            Player_ControlFreeze();
            SysWork_StateStepIncrement(0);

        case 1:
            func_80085DF0();
            break;

        case 2:
            MapMsg_DisplayAndHandleSelection(true, 45, 3, NO_VALUE, 0, false); // "There is a drawer. Do you want to open it?"
            break;

        case 3:
            func_80085EB8(0u, &g_SysWork.playerWork_4C.player_0, 66, false);
            g_SysWork.field_30 = 20;

            // Warp camera.
            Camera_PositionSet(NULL, Q12(135.17f), Q12(-3.3f), Q12(61.09f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);
            Camera_LookAtSet(NULL, Q12(134.29f), Q12(-0.21f), Q12(63.18f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);

            // Warp player.
            g_SysWork.playerWork_4C.player_0.position_18.vx = Q12(134.9f);
            g_SysWork.playerWork_4C.player_0.position_18.vz = Q12(62.45f);
            g_SysWork.playerWork_4C.player_0.rotation_24.vy = Q12_ANGLE(-90.0f);

            SysWork_StateStepIncrement(0);

        case 4:
            SysWork_StateStepIncrementDelayed(Q12(1.5f), false);
            break;

        case 5:
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(0.0f), false);
            break;

        case 6:
            func_8005DC1C(Sfx_Unk1593, &QVECTOR3(134.6f, -1.5f, 62.45f), Q8_CLAMPED(0.5f), 0);
            SysWork_StateStepIncrement(0);

        case 7:
            SysWork_StateStepIncrementDelayed(Q12(1.0f), false);
            break;

        case 8:
            vcReturnPreAutoCamWork(true);
            SysWork_StateStepIncrementAfterFade(0, false, 2, Q12(0.0f), false);
            SysWork_StateStepIncrementAfterFade(0, false, 0, Q12(0.0f), false);
            Savegame_EventFlagSet(EventFlag_375);

            // Warp player.
            g_SysWork.playerWork_4C.player_0.position_18.vx = Q12(135.15f);

            SysWork_StateStepIncrement(0);

        default:
            // Return to gameplay.
            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);
            break;
    }
}

void func_800D4DF8(void) // 0x800D4DF8
{
    Event_ItemTake(InventoryItemId_SafeKey, DEFAULT_PICKUP_ITEM_COUNT, EventFlag_M5S02_PickupSafeKey, 47);
}

void func_800D4E24(void) // 0x800D4E24
{
    Savegame_EventFlagSet(EventFlag_397);
    MapMsg_DisplayWithTexture(FILE_TIM_DIARYINR_TIM, Q12(0.0f), Q12(0.0f), 35);
}

void func_800D4E64(void) // 0x800D4E64
{
    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            Player_ControlFreeze();

            Savegame_EventFlagSet(EventFlag_396);

            // Warp player.
            g_SysWork.playerWork_4C.player_0.position_18.vx = Q12(135.05f);
            g_SysWork.playerWork_4C.player_0.position_18.vz = Q12(59.75f);
            g_SysWork.playerWork_4C.player_0.rotation_24.vy = Q12_ANGLE(180.0f);

            SysWork_StateStepIncrementAfterFade(0, true, 2, Q12(0.0f), false);
            SysWork_StateStepIncrement(0);

        case 1:
            func_80085DF0();
            break;

        case 2:
            func_80086C58(&g_SysWork.playerWork_4C.player_0, 59);
            break;

        case 3:
            func_8005DC1C(Sfx_Unk1592, &QVECTOR3(134.9f, -0.5f, 59.5f), Q8_CLAMPED(0.5f), 0);
            SysWork_StateStepIncrement(0);

        case 4:
            MapMsg_DisplayAndHandleSelection(false, 46, 0, 0, 0, false); // "Used the Safe Key."
            break;

        case 5:
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(0.0f), false);
            break;

        case 6:
            Savegame_EventFlagSet(EventFlag_M5S02_UsedSafeKey);
            func_8005DC1C(Sfx_Unk1591, &QVECTOR3(134.7f, -0.5f, 59.5f), Q8_CLAMPED(0.5f), 0);

            // Warp camera.
            Camera_PositionSet(NULL, Q12(135.26f), Q12(-1.61f), Q12(60.22f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);
            Camera_LookAtSet(NULL, Q12(133.36f), Q12(1.12f), Q12(58.01f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);

            g_WorldObject_BDoor1.rotation_28.vy = Q12_ANGLE(-142.21f);
            SysWork_StateStepIncrement(0);

        case 7:
            SysWork_StateStepIncrementDelayed(Q12(0.5f), false);
            break;

        case 8:
            SysWork_StateStepIncrementAfterFade(2, false, 0, Q12(0.0f), false);
            break;

        case 9:
            MapMsg_DisplayAndHandleSelection(false, 34, 0, 0, 0, false); // "What is this? Drugs?""
            break;

        case 10:
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(0.0f), false);
            break;

        case 11:
            vcReturnPreAutoCamWork(true);
            g_WorldObject_BDoor1.rotation_28.vy = Q12_ANGLE(-7.5f);
            SysWork_StateStepIncrement(0);

        case 12:
            SysWork_StateStepIncrementDelayed(Q12(0.5f), false);
            break;

        case 13:
            SysWork_StateStepIncrementAfterFade(0, false, 0, Q12(0.0f), false);
            SysWork_StateStepIncrement(0);

        case 14:
            func_80086C58(&g_SysWork.playerWork_4C.player_0, 60);
            break;

        default:
            // Return to gameplay.
            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);
            SysWork_StateStepIncrementAfterFade(0, false, 2, Q12(0.0f), false);
            vcReturnPreAutoCamWork(true);
            break;
    }
}

void func_800D519C(void) // 0x800D519C
{
    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            Player_ControlFreeze();
            SysWork_StateStepIncrementAfterFade(0, true, 2, Q12(0.0f), false);
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
            Savegame_EventFlagSet(EventFlag_M5S02_UsedSafeKey);
            func_8005DC1C(Sfx_Unk1591, &QVECTOR3(134.7f, -0.5f, 59.5f), Q8_CLAMPED(0.5f), 0);
            Camera_PositionSet(NULL, Q12(135.26f), Q12(-1.61f), Q12(60.22f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);
            Camera_LookAtSet(NULL, Q12(133.36f), Q12(1.12f), Q12(58.01f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);

            g_WorldObject_BDoor1.rotation_28.vy = Q12_ANGLE(-142.21f);

            g_SysWork.playerWork_4C.player_0.position_18.vx = Q12(135.05f);
            g_SysWork.playerWork_4C.player_0.position_18.vz = Q12(59.75f);
            g_SysWork.playerWork_4C.player_0.rotation_24.vy = Q12_ANGLE(180.f);
            SysWork_StateStepIncrement(0);

        case 5:
            SysWork_StateStepIncrementDelayed(Q12(0.5f), false);
            break;

        case 6:
            SysWork_StateStepIncrementAfterFade(2, false, 0, Q12(0.0f), false);
            break;

        case 7:
            MapMsg_DisplayAndHandleSelection(false, 34, 0, 0, 0, false); // "What is this? Drugs?""
            break;

        case 8:
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(0.0f), false);
            break;

        case 9:
            vcReturnPreAutoCamWork(true);
            g_WorldObject_BDoor1.rotation_28.vy = Q12_ANGLE(-7.5f);
            SysWork_StateStepIncrement(0);

        case 10:
            SysWork_StateStepIncrementDelayed(Q12(0.5f), false);
            break;

        case 11:
            SysWork_StateStepIncrementAfterFade(0, false, 0, Q12(0.0f), false);
            SysWork_StateStepIncrement(0);

        case 12:
            func_80086C58(&g_SysWork.playerWork_4C.player_0, 60);
            break;

        default:
            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);
            SysWork_StateStepIncrementAfterFade(0, false, 2, Q12(0.0f), false);
            vcReturnPreAutoCamWork(true);
            break;
    }
}

void func_800D5478(void) // 0x800D5478
{
    MapMsg_DisplayWithTexture(FILE_TIM_PICT_INR_TIM, Q12(0.0f), Q12(0.0f), 44);
}

void func_800D54A4(void) // 0x800D54A4
{
    MapMsg_DisplayWithTexture(FILE_TIM_MEMO_INR_TIM, Q12(0.0f), Q12(0.0f), 42);
}

void func_800D54D0(void) // 0x800D54D0
{
    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            Player_ControlFreeze();
            SysWork_StateStepIncrement(0);

        case 1:
            func_80085DF0();
            break;

        case 2:
            func_80086C58(&g_SysWork.playerWork_4C.player_0, 59);
            break;

        case 3:
            func_80086470(0, InventoryItemId_KaufmannKey, 0, false);
            SysWork_StateStepIncrement(0);

        case 4:
            MapMsg_DisplayAndHandleSelection(false, 32, 0, 0, 0, false);
            break;

        case 5:
            func_80086470(1, InventoryItemId_KaufmannKey, 0, false);
            break;

        case 6:
            Savegame_EventFlagSet(EventFlag_380);

            if (Gfx_PickupItemAnimate(InventoryItemId_KaufmannKey))
            {
                MapMsg_DisplayAndHandleSelection(false, 50, 0, 0, 0, false);

                if (g_SysWork.sysStateStep_C[0] != 6)
                {
                    SD_Call(Sfx_MenuConfirm);
                }
            }
            break;

        case 7:
            func_80086470(0, InventoryItemId_Receipt, 0, false);
            SysWork_StateStepIncrement(0);

        case 8:
            func_80086470(1, InventoryItemId_Receipt, 0, false);
            break;

        case 9:
            if (Gfx_PickupItemAnimate(InventoryItemId_Receipt))
            {
                MapMsg_DisplayAndHandleSelection(false, 49, 0, 0, 0, false);

                if (g_SysWork.sysStateStep_C[0] != 9)
                {
                    SD_Call(Sfx_MenuConfirm);
                }
            }
            break;

        case 10:
            func_80086C58(&g_SysWork.playerWork_4C.player_0, 60);
            break;

        default:
            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);
            Savegame_EventFlagSet(EventFlag_380);
            func_80086470(3, InventoryItemId_KaufmannKey, 1, false);
            func_80086470(3, InventoryItemId_Receipt, 1, false);
            break;
    }
}

void MapEvent_KaufmannBarFightCutscene(void) // 0x800D5744
{
    VECTOR3  lightIntPos;
    SVECTOR3 unused;
    s32      i;

    if ((g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.skip_4) &&
        g_SysWork.sysStateStep_C[0] >= 3 && g_SysWork.sysStateStep_C[0] < 41)
    {
        SysWork_StateStepSet(0, 43);
    }

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            Player_ControlFreeze();
            D_800DA6E8 = 0;
            ScreenFade_ResetTimestep();
            g_SysWork.field_30    = 20;
            g_SysWork.flags_22A4 |= SysFlag2_3;

            func_8008D438();

            g_SysWork.field_235C = NULL;
            g_SysWork.field_236C = NULL;
            g_SysWork.pointLightIntensity_2378 = Q12(1.0f);

            Fs_QueueStartRead(FILE_ANIM_POOL1_DMS, FS_BUFFER_17);
            Fs_QueueWaitForEmpty();
            DmsHeader_FixOffsets(FS_BUFFER_17);

            D_800DA6EC                                 = 0;
            g_SysWork.playerWork_4C.player_0.position_18.vy = Q12(0.0f);

            Chara_Load(0, Chara_Kaufmann, &g_SysWork.npcCoords_FC0[0], CHARA_FORCE_FREE_ALL, NULL, NULL);
            Chara_Load(1, Chara_Mumbler, &g_SysWork.npcCoords_FC0[30], 0, NULL, NULL);

            func_8007F14C(32);
            func_8003D03C();
            sharedFunc_800D2EB4_0_s00();

            WorldGfx_PlayerHeldItemSet(InventoryItemId_Handgun);
            g_SysWork.playerWork_4C.player_0.field_E1_0 = 5;
            func_80085EB8(0, &g_SysWork.playerWork_4C.player_0, 153, false);
            D_800D94F4 = 0;
            SysWork_StateStepIncrement(0);
            break;

        case 1:
            func_80085EB8(2, &g_SysWork.playerWork_4C.player_0, 0, false);
            SysWork_StateStepIncrementAfterFade(2, false, 0, Q12(0.0f), false);
            break;

        case 2:
            func_80085EB8(3, &g_SysWork.playerWork_4C.player_0, 0, false);
            SysWork_StateStepIncrement(0);

        case 3:
            SysWork_StateStepIncrementAfterTime(&D_800DA6EC, Q12(8.0f), Q12(0.0f), Q12(20.0f), true, true);
            break;

        case 4:
            func_80085EB8(0, &g_SysWork.playerWork_4C.player_0, 70, false);
            Savegame_EventFlagSet(EventFlag_381);
            SysWork_StateStepIncrement(0);

        case 5:
            SysWork_StateStepIncrementAfterTime(&D_800DA6EC, Q12(8.0f), Q12(21.0f), Q12(31.0f), true, true);
            break;

        case 6:
            Chara_ProcessLoads();
            Chara_Spawn(Chara_Kaufmann, 0, Q12(140.5f), Q12(23.0f), Q12_ANGLE(0.0f), 3);
            SysWork_StateStepIncrement(0);
            break;

        case 7:
            Chara_Spawn(Chara_Mumbler, 0, Q12(140.5f), Q12(23.0f), Q12_ANGLE(0.0f), 17);
            D_800D94F4 = 1;
            func_80085EB8(0, &g_SysWork.npcs_1A0[0], 12, false);
            SysWork_StateStepIncrement(0);

        case 8:
            SysWork_StateStepIncrementAfterTime(&D_800DA6EC, Q12(10.0f), Q12(32.0f), Q12(43.0f), true, true);
            break;

        case 9:
            func_80085EB8(0, &g_SysWork.playerWork_4C.player_0, 186, false);
            SysWork_StateStepIncrement(0);

        case 10:
            SysWork_StateStepIncrementAfterTime(&D_800DA6EC, Q12(10.0f), Q12(44.0f), Q12(56.0f), true, true);
            break;

        case 11:
            func_8003D01C();
            SysWork_StateStepIncrement(0);

        case 12:
            func_80085EB8(0, &g_SysWork.playerWork_4C.player_0, 164, false);
            func_80085EB8(0, &g_SysWork.npcs_1A0[0], 11, false);

            ModelAnim_StatusDecrement(&g_SysWork.npcs_1A0[1].model_0.anim_4);
            SysWork_StateStepIncrement(0);

        case 13:
            SysWork_StateStepIncrementAfterTime(&D_800DA6EC, Q12(10.0f), Q12(63.0f), Q12(93.0f), true, true);
            break;

        case 14:
            func_80086C58(&g_SysWork.playerWork_4C.player_0, 165);
            SysWork_StateStepIncrementAfterTime(&D_800DA6EC, Q12(10.0f), Q12(94.0f), Q12(150.0f), false, false);
            break;

        case 15:
            func_80085EB8(0, &g_SysWork.playerWork_4C.player_0, 166, false);
            SysWork_StateStepIncrement(0);

        case 16:
            SysWork_StateStepIncrementAfterTime(&D_800DA6EC, Q12(10.0f), Q12(94.0f), Q12(150.0f), true, true);
            break;

        case 17:
            func_80085EB8(0, &g_SysWork.npcs_1A0[0], 14, false);
            SysWork_StateStepIncrement(0);

        case 18:
            SysWork_StateStepIncrementAfterTime(&D_800DA6EC, Q12(10.0f), Q12(151.0f), Q12(175.0f), true, true);
            break;

        case 19:
            func_80085EB8(0, &g_SysWork.npcs_1A0[0], 13, false);
            func_8003D03C();
            Savegame_EventFlagClear(EventFlag_381);
            g_SysWork.npcs_1A0[1].model_0.stateStep_3++;
            SysWork_StateStepIncrement(0);

        case 20:
            SysWork_StateStepIncrementAfterTime(&D_800DA6EC, Q12(10.0f), Q12(176.0f), Q12(206.0f), false, true);
            break;

        case 21:
            func_80085EB8(0, &g_SysWork.playerWork_4C.player_0, 51, false);
            func_80085EB8(0, &g_SysWork.npcs_1A0[0], 5, false);
            func_800625F4(&QVECTOR3(139.3f, 0.0f, 23.6f), 120, 3, 1);
            D_800D94F4 = 2;
            D_800DA6EC = Q12(207.0f);
            SysWork_StateStepIncrement(0);

        case 22:
            Map_MessageWithAudio(16, &D_800DA6E8, &D_800D947C);
            break;

        case 23:
            func_80085EB8(0, &g_SysWork.npcs_1A0[0], 10, false);
            SysWork_StateStepIncrement(0);

        case 24:
            Map_MessageWithAudio(17, &D_800DA6E8, &D_800D947C);
            SysWork_StateStepIncrementAfterTime(&D_800DA6EC, Q12(10.0f), Q12(207.0f), Q12(227.0f), true, false);
            break;

        case 25:
            func_80085EB8(0, &g_SysWork.npcs_1A0[0], 5, false);
            D_800DA6EC = Q12(228.0f);
            SysWork_StateStepIncrement(0);

        case 26:
            Map_MessageWithAudio(19, &D_800DA6E8, &D_800D947C);
            break;

        case 27:
            func_80085EB8(0, &g_SysWork.npcs_1A0[0], 9, false);
            Model_AnimFlagsClear(&g_SysWork.playerWork_4C.player_0.model_0, 2);
            SysWork_StateStepIncrement(0);

        case 28:
            SysWork_StateStepIncrementDelayed(Q12(1.8f), false);
            SysWork_StateStepIncrementAfterTime(&D_800DA6EC, Q12(10.0f), Q12(229.0f), Q12(294.0f), true, false);
            break;

        case 29:
            Map_MessageWithAudio(30, &D_800DA6E8, &D_800D947C);
            SysWork_StateStepIncrementAfterTime(&D_800DA6EC, Q12(10.0f), Q12(229.0f), Q12(294.0f), true, false);
            break;

        case 30:
            SysWork_StateStepIncrement(0);

        case 31:
            SysWork_StateStepIncrementDelayed(Q12(0.4f), false);
            break;

        case 32:
            func_80085EB8(0, &g_SysWork.npcs_1A0[0], 1, false);
            func_80085EB8(0, &g_SysWork.playerWork_4C.player_0, 73, false);
            Model_AnimFlagsSet(&g_SysWork.playerWork_4C.player_0.model_0, 2);
            SysWork_StateStepIncrement(0);

        case 33:
            Map_MessageWithAudio(31, &D_800DA6E8, &D_800D947C);

        case 34:
            SysWork_StateStepIncrementAfterTime(&D_800DA6EC, Q12(8.0f), Q12(295.0f), Q12(315.0f), true, true);
            break;

        case 35:
            func_80088F94(&g_SysWork.npcs_1A0[0], 0, 0);
            func_80085EB8(0, &g_SysWork.playerWork_4C.player_0, 51, false);

            D_800DA6EC = Q12(316.0f);

            sharedFunc_800D2EF4_0_s00();
            WorldGfx_PlayerPrevHeldItem(&g_SysWork.playerCombat_38);
            sharedFunc_800D2EB4_0_s00();
            SysWork_StateStepIncrement(0);

        case 36:
            SysWork_StateStepIncrementDelayed(Q12(0.5f), false);
            break;

        case 37:
            func_8005DC1C(Sfx_DoorOpen0, &QVECTOR3(134.5f, -1.2f, 17.9f), Q8_CLAMPED(0.5f), 0);
            SysWork_StateStepIncrement(0);

        case 38:
            SysWork_StateStepIncrementDelayed(Q12(1.0f), false);
            break;

        case 39:
            func_8005DC1C(Sfx_DoorClose0, &QVECTOR3(134.5f, -1.2f, 17.9f), Q8_CLAMPED(0.5f), 0);
            SysWork_StateStepIncrement(0);

        case 40:
            SysWork_StateStepIncrementDelayed(Q12(0.6f), false);
            break;

        case 41:
            if (Fs_QueueDoThingWhenEmpty())
            {
                SysWork_StateStepIncrement(0);
            }
            break;

        case 42:
            SysWork_StateStepReset();
            break;

        case 43:
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(0.0f), false);
            break;

        case 44:
            if (!D_800D94F4)
            {
                Chara_ProcessLoads();
                g_SysWork.npcs_1A0[0].model_0.charaId_0 = Chara_Kaufmann;
                Chara_Spawn(Chara_Mumbler, 0, Q12(140.5f), Q12(23.0f), Q12_ANGLE(0.0f), 17);
                D_800D94F4 = 1;
            }

            func_80088F94(&g_SysWork.npcs_1A0[0], 0, 0);
            sharedFunc_800D2EF4_0_s00();
            WorldGfx_PlayerPrevHeldItem(&g_SysWork.playerCombat_38);

            D_800DA6EC = Q12(316.0f);
            SysWork_StateStepIncrement(0);
            break;

        case 45:
            if (D_800D94F4 == 1)
            {
                g_SysWork.npcs_1A0[1].model_0.stateStep_3 = 3;
                func_800625F4(&QVECTOR3(139.3f, 0.0f, 23.6f), 120, 3, 1);
            }

            Fs_QueueWaitForEmpty();
            SysWork_StateStepIncrement(0);
            break;

        case 46:
            for (i = 0; i < ARRAY_SIZE(sharedData_800DFB7C_0_s00); i++)
            {
                if (sharedData_800DFB7C_0_s00[i].field_A == 1)
                {
                    sharedData_800DFB7C_0_s00[i].field_A = 0;
                }
            }

            SysWork_StateStepIncrementAfterFade(0, false, 0, Q12(0.0f), false);
            SysWork_StateStepIncrement(0);

        default:
            Player_ControlUnfreeze(true);
            SysWork_StateSetNext(SysState_Gameplay);
            g_SysWork.playerWork_4C.player_0.position_18.vy = 0;
            func_8003D01C();
            sharedFunc_800D2EF4_0_s00();
            func_8007F14C((u8)g_SysWork.playerCombat_38.weaponAttack_F);

            Model_AnimFlagsSet(&g_SysWork.playerWork_4C.player_0.model_0, 2);
            vcReturnPreAutoCamWork(true);

            D_800DA6EC = NO_VALUE;

            Savegame_EventFlagSet(EventFlag_379);
            func_8008D448();
            Game_FlashlightAttributesFix();
            g_SysWork.pointLightIntensity_2378 = Q12(1.0f);
            SysWork_StateStepIncrementAfterFade(0, false, 2, Q12(0.0f), false);
            g_SysWork.playerWork_4C.player_0.field_E1_0 = 3;
            SD_Call(19);
            break;
    }

    if (g_SysWork.sysStateStep_C[0] < 27)
    {
        WorldGfx_ObjectAdd(&g_WorldObject_06LBag.object_0, &g_WorldObject_06LBag.position_1C, &g_WorldObject_06LBag.rotation_28);
    }

    if (D_800DA6EC >= 0)
    {
        Dms_CharacterGetPosRot(&g_SysWork.playerWork_4C.player_0.position_18, &g_SysWork.playerWork_4C.player_0.rotation_24, "HERO", D_800DA6EC, FS_BUFFER_17);
        Dms_CharacterGetPosRot(&g_SysWork.npcs_1A0[0].position_18, &g_SysWork.npcs_1A0[0].rotation_24, "KAU", D_800DA6EC, FS_BUFFER_17);
        Dms_CharacterGetPosRot(&g_SysWork.npcs_1A0[1].position_18, &g_SysWork.npcs_1A0[1].rotation_24, "CLD4", D_800DA6EC, FS_BUFFER_17);
        vcChangeProjectionValue(Dms_CameraGetTargetPos(&D_800DA6CC, &D_800DA6DC, NULL, D_800DA6EC, FS_BUFFER_17));
        vcUserCamTarget(&D_800DA6CC, NULL, true);
        vcUserWatchTarget(&D_800DA6DC, NULL, true);

        // "LIGHT", cutscene light position?
        Dms_CharacterGetPosRot(&g_SysWork.pointLightPosition_2360, &unused, "LIGHT", D_800DA6EC, FS_BUFFER_17);

        // "L_INT", interior light or intersection point?
        Dms_CharacterGetPosRot(&lightIntPos, &unused, "L_INT", D_800DA6EC, FS_BUFFER_17);

        // Set light rotation.
        g_SysWork.pointLightRot_2370.vx = -ratan2(lightIntPos.vy - g_SysWork.pointLightPosition_2360.vy, Math_Vector2MagCalc(lightIntPos.vx - g_SysWork.pointLightPosition_2360.vx, lightIntPos.vz - g_SysWork.pointLightPosition_2360.vz));
        g_SysWork.pointLightRot_2370.vy =  ratan2(lightIntPos.vx - g_SysWork.pointLightPosition_2360.vx, lightIntPos.vz - g_SysWork.pointLightPosition_2360.vz);
        g_SysWork.pointLightRot_2370.vz = Q12_ANGLE(0.0f);
    }
}

void Map_WorldObjectsInit(void) // 0x800D6598
{
    WorldObject_ModelNameSet(&g_WorldObject_SavePad, D_800A99E4.savePadName_4);

    WorldObjectPoseInit(&g_WorldObject_UnkPose0, 135.5022f, -1.3f, 21.71f, 0.0f, 11.4f, 0.0f);

    WorldObjectInit(&g_WorldObject_BDoor1, "BDOOR1_H", 134.5318f, 0.0f, 59.471f, 0.0f, 0.0f, 0.0f);

    WorldObject_ModelNameSet(&g_WorldObject_Box[0], "BOX091_H");
    WorldObject_ModelNameSet(&g_WorldObject_Box[1], "BOX191_H");

    Math_Vector3Set(&g_WorldObject_UnkPos[0], Q12(134.3162f), Q12(-0.504f), Q12(62.472f));

    WorldObject_ModelNameSet(&g_WorldObject_Box[2], "BOX092_H");
    WorldObject_ModelNameSet(&g_WorldObject_Box[3], "BOX192_H");

    Math_Vector3Set(&g_WorldObject_UnkPos[1], Q12(134.5752f), Q12(0.0f), Q12(62.4656f));

    WorldObjectInit(&g_WorldObject_Key, "KEY_HIDE", 134.5752f, -0.1067f, 62.4656f, 0.0f, -27.51f, 0.0f);

    WorldObjectInit(&g_WorldObject_Daly, "DALY_HID", 135.9241f, -1.1517f, 60.315f, 0.0f, 9.8f, 0.0f);

    WorldObject_ModelNameSet(&g_WorldObject_Drug, "DRUG_HID");

    WorldObjectPoseInit(&g_WorldObject_UnkPose1[0], 134.6792f, -0.1561f, 59.1995f, 0.0f, -6.4f, 0.0f);
    WorldObjectPoseInit(&g_WorldObject_UnkPose1[1], 134.8038f, -0.1561f, 59.29f, 0.0f, 170.7f, 0.0f);
    WorldObjectPoseInit(&g_WorldObject_UnkPose1[2], 134.8704f, -0.2054f, 59.25f, 0.0f, -3.0f, 20.4f);

    WorldObjectInit(&g_WorldObject_06LBag, "06LBAG_H", 138.8426f, 0.0f, 20.2635f, 0.0f, 180.0f, 0.0f);

    WorldObjectInit(&g_WorldObject_Obj00, "OBJ00_HI", 139.2938f, 0.0f, 25.4083f, 0.0f, 33.5f, 0.0f);

    if (Savegame_EventFlagGet(EventFlag_M5S02_UsedSafeKey))
    {
        g_WorldObject_BDoor1.rotation_28.vy = Q12_ANGLE(-7.5f);
    }

    WorldObject_ModelNameSet(&g_CommonWorldObjects[0], D_800A99E4.firstAidKitName_8);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[1], D_800A99E4.healthDrinkName_C);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[2], D_800A99E4.ampouleName_10);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[3], D_800A99E4.handgunBulletsName_14);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[4], D_800A99E4.shotgunShellsName_18);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[5], D_800A99E4.rifleShellsName_1C);
}

void Map_WorldObjectsUpdate(void) // 0x800D68FC
{
    MAP_CHUNK_CHECK_VARIABLE_DECL();

    func_80069844(0xFFFF);

    if (PLAYER_IN_MAP_CHUNK(vx, 1, 4, -1, 4) && PLAYER_IN_MAP_CHUNK(vz, 1, 2, -1, 2))
    {
        if (!Savegame_EventFlagGet(EventFlag_375))
        {
            WorldGfx_ObjectAdd(g_WorldObject_Box, g_WorldObject_UnkPos, &(SVECTOR3){ 0, 0, 0 });
            WorldGfx_ObjectAdd(&g_WorldObject_Box[1], g_WorldObject_UnkPos, &(SVECTOR3){ 0, 0, 0 });
        }
        else
        {
            WorldGfx_ObjectAdd(&g_WorldObject_Box[2], &g_WorldObject_UnkPos[1], &(SVECTOR3){ 0, 0, 0 });
            WorldGfx_ObjectAdd(&(&g_WorldObject_Box[2])[1], &g_WorldObject_UnkPos[1], &(SVECTOR3){ 0, 0, 0 });

            if (!Savegame_EventFlagGet(EventFlag_M5S02_PickupSafeKey))
            {
                WorldGfx_ObjectAdd(&g_WorldObject_Key.object_0, &g_WorldObject_Key.position_1C, &g_WorldObject_Key.rotation_28);
            }

            func_8006982C(2);
        }

        if (Savegame_EventFlagGet(EventFlag_M5S02_UsedSafeKey))
        {
            WorldGfx_ObjectAdd(&g_WorldObject_Drug, &g_WorldObject_UnkPose1->position_0, &g_WorldObject_UnkPose1->rotation_C);
            WorldGfx_ObjectAdd(&g_WorldObject_Drug, &g_WorldObject_UnkPose1[1].position_0, &g_WorldObject_UnkPose1[1].rotation_C);
            WorldGfx_ObjectAdd(&g_WorldObject_Drug, &g_WorldObject_UnkPose1[2].position_0, &g_WorldObject_UnkPose1[2].rotation_C);
        }

        WorldGfx_ObjectAdd(&g_WorldObject_BDoor1.object_0, &g_WorldObject_BDoor1.position_1C, &g_WorldObject_BDoor1.rotation_28);
        WorldGfx_ObjectAdd(&g_WorldObject_Daly.object_0, &g_WorldObject_Daly.position_1C, &g_WorldObject_Daly.rotation_28);
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, 4, -1, 4) && PLAYER_IN_MAP_CHUNK(vz, 0, 0, -1, 1))
    {
        WorldGfx_ObjectAdd(&g_WorldObject_SavePad, &g_WorldObject_UnkPose0.position_0, &g_WorldObject_UnkPose0.rotation_C);

        if (!Savegame_EventFlagGet(EventFlag_380))
        {
            WorldGfx_ObjectAdd(&g_WorldObject_Obj00.object_0, &g_WorldObject_Obj00.position_1C, &g_WorldObject_Obj00.rotation_28);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, 4, -1, 4) && PLAYER_IN_MAP_CHUNK(vz, 0, 0, -1, 1))
    {
        if (!Savegame_EventFlagGet(EventFlag_M5S02_HealthDrink0))
        {
            WorldGfx_ObjectAdd(&g_CommonWorldObjects[1], &g_CommonWorldObjectPoses[0].position_0, &g_CommonWorldObjectPoses[0].rotation_C);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, 4, -1, 4) && PLAYER_IN_MAP_CHUNK(vz, 0, 0, -1, 1))
    {
        if (!Savegame_EventFlagGet(EventFlag_M5S02_HealthDrink1))
        {
            WorldGfx_ObjectAdd(&g_CommonWorldObjects[1], &g_CommonWorldObjectPoses[1].position_0, &g_CommonWorldObjectPoses[1].rotation_C);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, 4, -1, 4) && PLAYER_IN_MAP_CHUNK(vz, 1, 2, -1, 2))
    {
        if (!Savegame_EventFlagGet(EventFlag_M5S02_RifleShells))
        {
            WorldGfx_ObjectAdd(&g_CommonWorldObjects[4], &g_CommonWorldObjectPoses[2].position_0, &g_CommonWorldObjectPoses[2].rotation_C);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, 4, -1, 4) && PLAYER_IN_MAP_CHUNK(vz, 1, 2, -1, 2))
    {
        if (!Savegame_EventFlagGet(EventFlag_M5S02_HealthDrink2))
        {
            WorldGfx_ObjectAdd(&g_CommonWorldObjects[1], &g_CommonWorldObjectPoses[3].position_0, &g_CommonWorldObjectPoses[3].rotation_C);
        }
    }
}
