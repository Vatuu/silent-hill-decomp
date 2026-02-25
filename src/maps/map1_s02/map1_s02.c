#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "bodyprog/player_logic.h"
#include "main/rng.h"
#include "maps/map1/map1_s02.h"
#include "maps/particle.h"
#include "maps/characters/creeper.h"
#include "maps/characters/player.h"
#include "maps/characters/stalker.h"

#include "maps/shared/sharedFunc_800CBA4C_1_s02.h" // 0x800CBA4C

#include "maps/shared/sharedFunc_800CBC98_1_s02.h" // 0x800CBC98

#include "maps/shared/sharedFunc_800CBD58_1_s02.h" // 0x800CBD58

#include "maps/shared/sharedFunc_800CBDA8_1_s02.h" // 0x800CBDA8

#include "maps/shared/sharedFunc_800CCE60_1_s02.h" // 0x800CCE60

#include "../src/maps/particle.c"

#include "../src/maps/characters/player.c"

// TODO: Move this line into separate `Chara_Stalker` split.
#include "../src/maps/characters/stalker.c" // 0x800D2948

// TODO: Move this line into separate `Chara_Creeper` split.
#include "../src/maps/characters/creeper.c" // 0x800D7B98

#include "maps/shared/sharedFunc_800D929C_0_s00.h" // 0x800D9E0C

#include "maps/shared/Map_RoomIdxGet.h" // 0x800D9E1C

#include "maps/shared/Map_RoomBgmInit_1_s02.h" // 0x800D9EBC

void Gfx_LoadingScreen_StageString(void) {}

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

    switch (g_MapEventData->pointOfInterestIdx_5)
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
    VECTOR3 sfxPos = { MAP_POINTS[g_MapEventData->pointOfInterestIdx_5].positionX_0, Q12(-1.2f), MAP_POINTS[g_MapEventData->pointOfInterestIdx_5].positionZ_8 };

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
            Savegame_EventFlagSet(EventFlag_MapMark_AltSchool1F_CourtyardQuestion);
            break;
    }

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            Player_ControlFreeze();
            Game_TurnFlashlightOn();
            sharedFunc_800D08B8_0_s00(6, 127);
            Particle_SystemUpdate(0, g_SavegamePtr->mapOverlayId_A4, 0);

            g_SysWork.playerWork_4C.player_0.position_18.vx = Q12(-13.3f);
            g_SysWork.playerWork_4C.player_0.position_18.vz = Q12(-68.1f);

            func_800865FC(true, 0, 0, Q12_ANGLE(-45.0f), Q12(-18.18f), Q12(-62.24f));
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
            func_80086C58(&g_SysWork.playerWork_4C.player_0, 74);
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
                g_SysWork.playerWork_4C.player_0.position_18.vx = Q12(-18.18f);
                g_SysWork.playerWork_4C.player_0.position_18.vy = Q12(0.0f);
                g_SysWork.playerWork_4C.player_0.position_18.vz = Q12(-62.24f);
                g_SysWork.playerWork_4C.player_0.rotation_24.vy = Q12_ANGLE(-45.0f);

                Player_ControlUnfreeze(true);
                SysWork_StateSetNext(SysState_Gameplay);
                vcReturnPreAutoCamWork(true);
            }
            else
            {
                Player_ControlUnfreeze(false);
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
            Player_ControlFreeze();
            SysWork_StateStepIncrement(0);

        case 1:
            func_80085DF0();
            break;

        case 2:
            MapMsg_DisplayAndHandleSelection(false, 0x12, 0, 0, 0, false);
            break;

        default:
            Player_ControlUnfreeze(false);
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

void MapEvent_GameTrialOver(void) // 0x800DAA2C
{
    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            Player_ControlFreeze();
            SysWork_StateStepIncrement(0);

        case 1:
            SysWork_StateStepIncrementAfterFade(0, true, 1, Q12(1.0f), false);
            func_800862F8(0, FILE_TIM_CONTINUE_TIM, false);
            SysWork_StateStepIncrement(0);

        case 2:
            SysWork_StateStepIncrementAfterFade(1, true, 0, Q12(0.0f), false);
            break;

        case 3:
            func_800862F8(1, FILE_1ST_2ZANKO80_TIM, false);
            break;

        case 4:
            SysWork_StateStepIncrementAfterFade(0, false, 1, Q12(1.0f), false);
            SysWork_StateStepIncrement(0);

        case 5:
            func_800862F8(2, FILE_1ST_2ZANKO80_TIM, false);
            if (g_Controller0->btnsClicked_10 & (g_GameWorkPtr->config_0.controllerConfig_0.enter_0 | g_GameWorkPtr->config_0.controllerConfig_0.cancel_2))
            {
                SysWork_StateStepIncrement(0);
            }

            SysWork_StateStepIncrementDelayed(Q12(4.0f), false);

            if (g_SysWork.sysStateStep_C[0] == 7)
            {
                g_SysWork.sysStateStep_C[0] = 6;
            }
            break;

        case 6:
            func_800862F8(2, FILE_1ST_2ZANKO80_TIM, false);
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(1.5f), false);
            break;

        case 7:
            func_800862F8(7, FILE_TIM_COMING2_TIM, false);
            break;

        case 8:
            SysWork_StateStepIncrementAfterFade(0, false, 0, Q12(1.5f), false);
            SysWork_StateStepIncrement(0);

        case 9:
            func_800862F8(2, FILE_1ST_2ZANKO80_TIM, false);

            if (g_Controller0->btnsClicked_10 & (g_GameWorkPtr->config_0.controllerConfig_0.enter_0 | g_GameWorkPtr->config_0.controllerConfig_0.cancel_2))
            {
                SysWork_StateStepIncrement(0);
            }

            SysWork_StateStepIncrementDelayed(Q12(4.0f), false);

            if (g_SysWork.sysStateStep_C[0] == 11)
            {
                g_SysWork.sysStateStep_C[0] = 10;
                break;
            }
            break;

        case 10:
            func_800862F8(2, FILE_1ST_2ZANKO80_TIM, false);
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(1.5f), false);
            break;

        default:
            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);
            Game_WarmBoot();

            g_SysWork.sysFlags_22A0 |= SysFlag_Freeze;
            break;
    }
}

extern s16 D_800E1FD0;

void func_800DAD2C(void) // 0x800DAD2C
{
    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            Player_ControlFreeze();
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

        case 4:
            func_800862F8(2, 0, false);
            SysWork_StateStepIncrementAfterFade(2, false, 0, Q12(0.0f), false);
            break;

        case 5:
            func_800862F8(2, 0, false);

            if (Savegame_EventFlagGet(EventFlag_M1S02_SeenDoorWithHorizontalSlot))
            {
                MapMsg_DisplayAndHandleSelection(false, 25, false, false, 0, false); // "If I push it, it moves a bit."
            }
            else
            {
                MapMsg_DisplayAndHandleSelection(false, 23, false, false, 0, false); // "What? Is this a door?"
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
                MapMsg_DisplayAndHandleSelection(false, 26, false, false, 0, false); // "What's this?"
            }

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
            MapMsg_DisplayAndHandleSelection(false, 27, false, false, 0, false); // "In the center of the door is a horizontal slot.
            break;

        case 10:
            func_800862F8(5, 0, false);
            SysWork_StateStepIncrementAfterFade(2, 1, 0, Q12(0.0f), false);
            break;

        default:
            func_800862F8(6, 0, false);
            SysWork_StateStepIncrementAfterFade(0, false, 0, Q12(0.0f), false);

            Savegame_EventFlagSet(EventFlag_M1S02_SeenDoorWithHorizontalSlot);

            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);
            break;
        }
}

void func_800DB058(void) // 0x800DB058
{
    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            // Freeze player.
            Player_ControlFreeze();
            Player_MoveDistanceClear();

            g_SysWork.field_30 = 20;

            // Warp player.
            g_SysWork.playerWork_4C.player_0.position_18.vx = Q12(56.5f);
            g_SysWork.playerWork_4C.player_0.position_18.vz = Q12(19.3f);
            g_SysWork.playerWork_4C.player_0.rotation_24.vy = Q12(-0.25f);

            // Warp camera.
            Camera_PositionSet(NULL, Q12(60.59f), Q12(-0.83f), Q12(18.34f), 0, 0, 0, 0, true);
            Camera_LookAtSet(NULL, Q12(56.7698f), Q12(-1.45f), Q12(19.34f), 0, 0, 0, 0, true);

            func_8003D03C();
            sharedFunc_800D2EB4_0_s00();
            SysWork_StateStepIncrement(0);

        case 1:
            SysWork_StateStepIncrementAfterFade(1, false, 0, Q12(0.0f), false);
            break;

        case 2:
            SysWork_StateStepIncrementDelayed(Q12(0.2f), false);
            break;

        case 3:
            func_80086C58(&g_SysWork.playerWork_4C.player_0, 94);
            break;

        case 4:
            func_8005DC1C(Sfx_Unk1454, &QVECTOR3(55.85f, -1.1f, 19.3f), Q8_CLAMPED(0.5f), 0);
            SysWork_StateStepIncrement(0);

        case 5:
            MapMsg_DisplayAndHandleSelection(false, 30, 0, 0, 0, false); // "Slid the Picture card into the slot."
            break;

        case 6:
            func_8005DC1C(Sfx_Unk1343, &QVECTOR3(56.0f, -1.2f, 19.3f), Q8_CLAMPED(0.5f), 0);
            SysWork_StateStepIncrement(0);

        case 7:
            func_80086C58(&g_SysWork.playerWork_4C.player_0, 95);
            break;

        case 8:
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(0.0f), false);
            break;

        default:
            Player_ControlUnfreeze(true);
            SysWork_StateSetNext(SysState_Gameplay);
            SysWork_StateStepIncrementAfterFade(0, false, 2, Q12(0.0f), false);
            SysWork_StateStepIncrementAfterFade(0, false, 0, Q12(0.0f), false);
            vcReturnPreAutoCamWork(true);

            Savegame_EventFlagSet(EventFlag_MapMark_AltSchool1F_SecretDoorArrows);

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

void func_800DB368(void) // 0x800DB368
{
    if ((g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.skip_4) &&
        g_SysWork.sysStateStep_C[0] >= 2 && g_SysWork.sysStateStep_C[0] < 26)
    {
        if (g_SysWork.sysStateStep_C[0] < 5)
        {
            D_800E1FD8 = true;
        }

        SysWork_StateStepSet(0, 27);
    }

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            Player_ControlFreeze();
            Savegame_EventFlagSet(EventFlag_122);
            SD_Call(Sfx_XaAudio53);
            func_800865FC(true, 0, 0, Q12_ANGLE(-90.0f), Q12(20.3f), Q12(143.5f));

            func_800868DC(0);
            func_800868DC(3);

            D_800E1FD8 = false;
            SysWork_StateStepIncrement(0);

        case 1:
            func_80085DF0();
            break;

        case 2:
            SysWork_StateStepIncrementDelayed(Q12(1.5f), false);
            break;

        case 3:
            SysWork_StateStepIncrementAfterFade(2, true, 2, Q12(0.0f), false);
            break;

        case 4:
            func_800866D4(53, 1, false);
            SysWork_StateStepIncrementDelayed(Q12(2.0f), false);
            break;

        case 5:
            func_8003D03C();
            sharedFunc_800D2EB4_0_s00();
            Game_TurnFlashlightOn();
            Camera_PositionSet(NULL, Q12(18.06f), Q12(-1.99f), Q12(142.77f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);
            Camera_LookAtSet(NULL, Q12(20.95f), Q12(0.27f), Q12(144.37f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);
            SysWork_StateStepIncrement(0);

        case 6:
            func_800866D4(53, 1, false);
            break;

        case 7:
            func_80085EB8(0, &g_SysWork.playerWork_4C.player_0, 97, false);
            SysWork_StateStepIncrement(0);

        case 8:
            SysWork_StateStepIncrementDelayed(Q12(0.5f), false);
            break;

        case 9:
            Camera_PositionSet(NULL, g_SysWork.playerWork_4C.player_0.position_18.vx + Q12(4.0f), Q12(-1.5f), g_SysWork.playerWork_4C.player_0.position_18.vz, Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);
            Camera_LookAtSet(NULL, g_SysWork.playerWork_4C.player_0.position_18.vx, Q12(-1.0f), g_SysWork.playerWork_4C.player_0.position_18.vz, Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);

            SysWork_StateStepIncrement(0);

        case 10:
            SysWork_StateStepIncrementDelayed(Q12(3.5f), false);
            break;

        case 11:
            SD_Call(Sfx_Unk1456);
            SD_Call(19);

            D_800E1FD4 = WorldGfx_PlayerHeldItemSet(InventoryItemId_CutscenePhone);
            SysWork_StateStepIncrement(0);

        case 12:
            if (Fs_QueueIsEntryLoaded(D_800E1FD4))
            {
                func_8003D01C();
                Sd_XaPreLoadAudioPreTaskAdd(Sfx_XaAudio54);
                SysWork_StateStepIncrement(0);
            }
            break;

        case 13:
            func_80085EB8(1, &g_SysWork.playerWork_4C.player_0, 0, false);
            Sd_XaPreLoadAudioPreTaskAdd(Sfx_XaAudio54);
            break;

        case 14:
            SD_Call(Sfx_XaAudio54);
            SysWork_StateStepIncrement(0);

        case 15:
            MapMsg_DisplayAndHandleSelection(false, 31, 0, 0, 0, false);

            // Warp camera.
            Camera_PositionSet(NULL, g_SysWork.playerWork_4C.player_0.position_18.vx + Q12(4.0f) + func_800868F4(Q12(-2.8f), Q12(6.5f), 0), Q12(-1.5f), g_SysWork.playerWork_4C.player_0.position_18.vz, Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), false);
            Camera_LookAtSet(NULL, g_SysWork.playerWork_4C.player_0.position_18.vx + func_800868F4(Q12(-2.8f), Q12(6.5f), 3), Q12(-1.0f), g_SysWork.playerWork_4C.player_0.position_18.vz, Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), false);
            break;

        case 16:
            // Warp camera.
            Camera_PositionSet(NULL, Q12(17.51f), Q12(-3.18f), Q12(144.05f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);
            Camera_LookAtSet(NULL, Q12(20.28f), Q12(-0.42f), Q12(143.22f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);

            SysWork_StateStepIncrement(0);

        case 17:
            SysWork_StateStepIncrementDelayed(Q12(1.8f), false);
            break;

        case 18:
            func_80085EB8(0, &g_SysWork.playerWork_4C.player_0, 98, false);
            SysWork_StateStepIncrement(0);

        case 19:
            SysWork_StateStepIncrementDelayed(Q12(1.0f), false);
            break;

        case 20:
            func_80085EB8(2, &g_SysWork.playerWork_4C.player_0, 0, false);
            MapMsg_DisplayAndHandleSelection(false, 35, 0, 0, 0, false);
            break;

        case 21:
            func_80085EB8(3, &g_SysWork.playerWork_4C.player_0, 0, false);
            SysWork_StateStepIncrement(0);

        case 22:
            SysWork_StateStepIncrementDelayed(Q12(1.5f), false);
            break;

        case 23:
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(0.0f), false);
            break;

        case 24:
            sharedFunc_800D2EF4_0_s00();
            SD_Call(19);

            D_800E1FD4 = WorldGfx_PlayerPrevHeldItem(&g_SysWork.playerCombat_38);
            SysWork_StateStepIncrementAfterFade(0, false, 2, Q12(0.0f), false);

            SD_Call(Sfx_Unk1457);
            SysWork_StateStepIncrement(0);

        case 25:
            SysWork_StateStepIncrementDelayed(Q12(1.0f), false);
            break;

        case 26:
            if (Fs_QueueIsEntryLoaded(D_800E1FD4))
            {
                SysWork_StateStepReset();
            }
            break;

        case 27:
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(0.0f), false);
            break;

        case 28:
            SD_Call(19);
            func_80085EB8(3, &g_SysWork.playerWork_4C.player_0, 0, false);

            if (!D_800E1FD8)
            {
                sharedFunc_800D2EF4_0_s00();
            }

            WorldGfx_PlayerPrevHeldItem(&g_SysWork.playerCombat_38);
            func_8003D01C();

            // Warp camera.
            Camera_PositionSet(NULL, Q12(17.51f), Q12(-3.18f), Q12(144.05f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);
            Camera_LookAtSet(NULL, Q12(20.28f), Q12(-0.42f), Q12(143.22f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);

            // Warp player.
            g_SysWork.playerWork_4C.player_0.position_18.vx = Q12(20.3f);
            g_SysWork.playerWork_4C.player_0.position_18.vz = Q12(143.5f);
            g_SysWork.playerWork_4C.player_0.rotation_24.vy = Q12_ANGLE(-90.0f);

            Fs_QueueWaitForEmpty();
            g_SysWork.field_30 = 0;
            SysWork_StateStepIncrement(0);
            break;

        default:
            SysWork_StateStepIncrementAfterFade(0, false, 0, Q12(0.0f), false);
            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);

            Savegame_EventFlagSet(EventFlag_98);
            Savegame_EventFlagClear(EventFlag_99);

            vcReturnPreAutoCamWork(true);
            break;
    }
}

void func_800DBB7C(void) // 0x800DBB7C
{
    q3_12 angleAdd;

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            Player_ControlFreeze();
            Savegame_EventFlagSet(EventFlag_121);
            SD_Call(Sfx_XaAudio56);
            SysWork_StateStepIncrement(0);

        case 1:
            func_80085DF0();
            break;

        case 2:
            Model_AnimFlagsClear(&g_SysWork.playerWork_4C.player_0.model_0, 2);

            func_8008D438();

            func_800868DC(0);
            func_800868DC(1);

            // Warp camera.
            Camera_PositionSet(NULL, Q12(21.0f), Q12(-0.5f), Q12(60.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);
            Camera_LookAtSet(NULL, Q12(17.0f), Q12(-0.5f), Q12(60.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);

            SysWork_StateStepIncrementAfterFade(0, true, 2, Q12(0.0f), false);
            SysWork_StateStepIncrement(0);
            break;

        case 3:
            // Warp camera.
            if (D_800E1EE8 > Q12(1.0f))
            {
                Camera_PositionSet(NULL, func_800868F4(Q12(-1.5f), Q12(5.0f), 0) + Q12(21.0f), Q12(-0.5f), Q12(60.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), false);
                Camera_LookAtSet(NULL, func_800868F4(Q12(-1.5f), Q12(5.0f), 0) + Q12(17.0f), func_800868F4(Q12(-1.5f), Q12(5.0f), 1) - Q12(0.5f), Q12(60.0f), Q12(3.0f), Q12(0.0f), Q12(0.3f), Q12(0.0f), false);
            }

            D_800E1EE8 += g_DeltaTime;
            if (D_800E1EE8 < Q12(0.3f))
            {
                angleAdd = Q12_ANGLE(0.0f);
            }
            else if (D_800E1EE8 < Q12(0.5f))
            {
                angleAdd = Q12_ANGLE(-45.0f);
            }
            else if (D_800E1EE8 < Q12(1.0f))
            {
                angleAdd = Q12_ANGLE(5.0f);
            }
            else if (D_800E1EE8 < Q12(8.5f))
            {
                if (D_800E1EE8 - Q12(1.0f) <= Q12(6.0f))
                {
                    angleAdd = Q12_MULT_PRECISE(D_800E1EE8 - Q12(1.0f), Q12_ANGLE(5.0f)) - Q12_ANGLE(35.0f);
                }
                else
                {
                    angleAdd = Q12_ANGLE(-5.5f);
                }
            }
            else
            {
                angleAdd = Q12_ANGLE(0.0f);
                SysWork_StateStepIncrement(0);
            }

            g_WorldObject1.rotation_28.vy += Q12_MULT_PRECISE(g_DeltaTime, angleAdd);
            if (g_WorldObject1.rotation_28.vy < Q12_ANGLE(-112.5f))
            {
                g_WorldObject1.rotation_28.vy = Q12_ANGLE(-112.5f);
            }

            break;

        default:
            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);

            Model_AnimFlagsSet(&g_SysWork.playerWork_4C.player_0.model_0, 2);

            func_8008D448();

            SysWork_StateStepIncrementAfterFade(0, false, 2, Q12(0.0f), false);
            vcReturnPreAutoCamWork(true);

            Savegame_EventFlagSet(EventFlag_96);
            break;
    }
}

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
            Player_ControlFreeze();
            func_80086470(0, InventoryItemId_Shotgun, 0, false);
            SysWork_StateStepIncrement(0);

        case 1:
            func_80085DF0();
            break;

        case 2:
            func_80085EB8(0, &g_SysWork.playerWork_4C.player_0, 59, false);
            SysWork_StateStepIncrement(0);

        case 3:
            func_80086470(1, InventoryItemId_Shotgun, 0, false);
            break;

        case 4:
            func_80085EB8(1, &g_SysWork.playerWork_4C.player_0, 0, false);
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
            func_80086C58(&g_SysWork.playerWork_4C.player_0, 60);
            break;

        default:
            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);
            break;
    }
}

const VECTOR3 D_800CB934 = { 0x0003C800, 0xFFFFF4CD, 0xFFFC3000 };

const VECTOR3 D_800CB940 = { 0x0003C800, 0xFFFFF4CD, 0xFFFC5000 };

const VECTOR3 D_800CB94C = { 0x0003A666, 0xFFFFF000, 0xFFFC4000 };

void func_800DC1E0(void) // 0x800DC1E0
{
    q19_12 rotY0;
    q19_12 rotY1;

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            Player_ControlFreeze();

            D_800E1FE2 = 0;
            g_SysWork.field_28 = 0;
            g_SysWork.sysStateStep_C[1] = 0;
            g_SysWork.timer_2C = 0;
            g_SysWork.sysStateStep_C[2] = 0;
            g_SysWork.sysStateStep_C[0]++;

        case 1:
            MapMsg_DisplayAndHandleSelection(2, 41, 2, 4, NO_VALUE, false);

            D_800E1FE3 = 0;
            D_800E1FE0 = 0;
            D_800E1FDC.vy = 0;
            D_800E1FDC.vx = 0;
            break;

        case 2:
            D_800E1FE3 = 1;

        case 4:
            if (D_800E1FE2 == 0)
            {
                Camera_PositionSet(NULL, Q12(61.0f), Q12(-1.2f), Q12(-60.0f), Q12(2.5f), Q12(0.75f), Q12(1.5f), Q12(0.5f), false);
                SysWork_StateStepIncrementDelayed(Q12(2.0f), false);

                if (g_SysWork.sysStateStep_C[0] != 2 && g_SysWork.sysStateStep_C[0] != 4)
                {
                    g_SysWork.sysStateStep_C[0] = 5;
                    g_SysWork.field_28 = 0;
                    g_SysWork.sysStateStep_C[1] = 0;
                    g_SysWork.timer_2C = 0;
                    g_SysWork.sysStateStep_C[2] = 0;
                    D_800E1FE2++;
                }
            }
            else
            {
                g_SysWork.sysStateStep_C[0] = 5;
                g_SysWork.field_28 = 0;
                g_SysWork.sysStateStep_C[1] = 0;
                g_SysWork.timer_2C = 0;
                g_SysWork.sysStateStep_C[2] = 0;
            }
            break;

        case 5:
            if (Savegame_EventFlagGet(EventFlag_118))
            {
                func_8005DC1C(Sfx_Unk1452, &D_800CB934, Q8(0.5f), 0);
            }
            else
            {
                func_8005DC1C(Sfx_Unk1452, &D_800CB940, Q8(0.5f), 0);
            }

            g_SysWork.field_28 = 0;
            g_SysWork.sysStateStep_C[1] = 0;
            g_SysWork.timer_2C = 0;
            g_SysWork.sysStateStep_C[2] = 0;
            g_SysWork.sysStateStep_C[0]++;

        case 6:
            SysWork_StateStepIncrementDelayed(Q12(1.0f), false);
            break;

        case 7:
            if (D_800E1FDC.vx == 0)
            {
                SD_Call(Sfx_Unk1453);
            }

            if (D_800E1FDC.vx < Q12(0.25f))
            {
                D_800E1FE0 += Q12_MULT_PRECISE(g_DeltaTime, Q12(0.1666f));
            }
            else
            {
                D_800E1FE0 -= Q12_MULT_PRECISE(g_DeltaTime, Q12(0.1666f));
                D_800E1FE0 = MAX(D_800E1FE0, 170); // TODO: Float.
            }

            if (D_800E1FE3 != 0)
            {
                if (Savegame_EventFlagGet(EventFlag_118))
                {
                    rotY0 = -Q12_MULT_PRECISE(g_DeltaTime, MIN(D_800E1FE0, Q12_ANGLE(60.0f)));
                    if ((D_800E1FDC.vx - rotY0) > Q12_ANGLE(180.0f))
                    {
                        rotY0 = D_800E1FDC.vx - Q12_ANGLE(180.0f);
                        D_800E1FDC.vx = Q12_ANGLE(180.0f);
                    }
                    else
                    {
                        D_800E1FDC.vx -= rotY0;
                    }

                    rotY1 = -Q12_MULT_PRECISE(g_DeltaTime, MIN(D_800E1FE0, Q12_ANGLE(60.0f))) >> 1;
                    if ((D_800E1FDC.vy - rotY1) > Q12_ANGLE(90.0f))
                    {
                        rotY1 = D_800E1FDC.vy - Q12_ANGLE(90.0f);
                        D_800E1FDC.vy = Q12_ANGLE(90.0f);
                    }
                    else
                    {
                        D_800E1FDC.vy -= rotY1;
                    }
                }
                else
                {
                    rotY1 = -Q12_MULT_PRECISE(g_DeltaTime, MIN(D_800E1FE0, Q12_ANGLE(60.0f)));
                    if ((D_800E1FDC.vx - rotY1) > Q12_ANGLE(180.0f))
                    {
                        rotY1 = D_800E1FDC.vx - Q12_ANGLE(180.0f);
                        D_800E1FDC.vx = Q12_ANGLE(180.0f);
                    }
                    else
                    {
                        D_800E1FDC.vx -= rotY1;
                    }

                    rotY0 = -Q12_MULT_PRECISE(g_DeltaTime, MIN(D_800E1FE0, Q12_ANGLE(60.0f))) >> 1;
                    if ((D_800E1FDC.vy - rotY0) > Q12_ANGLE(90.0f))
                    {
                        rotY0 = D_800E1FDC.vy - Q12_ANGLE(90.0f);
                        D_800E1FDC.vy = Q12_ANGLE(90.0f);
                    }
                    else
                    {
                        D_800E1FDC.vy -= rotY0;
                    }
                }
            }
            else if (Savegame_EventFlagGet(EventFlag_118))
            {
                rotY0 = Q12_MULT_PRECISE(g_DeltaTime, MIN(D_800E1FE0, Q12_ANGLE(60.0f)));
                if ((D_800E1FDC.vx + rotY0) > Q12_ANGLE(180.0f))
                {
                    rotY0 = Q12_ANGLE(180.0f) - D_800E1FDC.vx;
                    D_800E1FDC.vx = Q12_ANGLE(180.0f);
                }
                else
                {
                    D_800E1FDC.vx += rotY0;
                }

                rotY1 = Q12_MULT_PRECISE(g_DeltaTime, MIN(D_800E1FE0, Q12_ANGLE(60.0f))) >> 1;
                if ((D_800E1FDC.vy + rotY1) > Q12_ANGLE(90.0f))
                {
                    rotY1 = Q12_ANGLE(90.0f) - D_800E1FDC.vy;
                    D_800E1FDC.vy = Q12_ANGLE(90.0f);
                }
                else
                {
                    D_800E1FDC.vy += rotY1;
                }
            }
            else
            {
                rotY1 = Q12_MULT_PRECISE(g_DeltaTime, MIN(D_800E1FE0, Q12_ANGLE(60.0f)));
                if ((D_800E1FDC.vx + rotY1) > Q12_ANGLE(180.0f))
                {
                    rotY1 = Q12_ANGLE(180.0f) - D_800E1FDC.vx;
                    D_800E1FDC.vx = Q12_ANGLE(180.0f);
                }
                else
                {
                    D_800E1FDC.vx += rotY1;
                }

                rotY0 = Q12_MULT_PRECISE(g_DeltaTime, MIN(D_800E1FE0, Q12_ANGLE(60.0f))) >> 1;
                if ((D_800E1FDC.vy + rotY0) > Q12_ANGLE(90.0f))
                {
                    rotY0 = Q12_ANGLE(90.0f) - D_800E1FDC.vy;
                    D_800E1FDC.vy = Q12_ANGLE(90.0f);
                }
                else
                {
                    D_800E1FDC.vy += rotY0;
                }
            }

            g_WorldObject6.rotation_28.vy += rotY0;
            g_WorldObject7.rotation_28.vy += rotY1;

            func_8005DE0C(Sfx_Unk1453, &D_800CB94C, D_800E1FE0 >> 3, Q12(18.0f), 0);

            if (D_800E1FDC.vx == Q12_ANGLE(180.0f) && D_800E1FDC.vy == Q12_ANGLE(90.0f))
            {
                // TODO: What are these angles?
                g_WorldObject6.rotation_28.vy = (g_WorldObject6.rotation_28.vy + 0x1040) & 0xC00;
                g_WorldObject7.rotation_28.vy = (g_WorldObject7.rotation_28.vy + 0x1040) & 0xC00;

                Sd_SfxStop(Sfx_Unk1453);

                g_SysWork.sysStateStep_C[0] = 1;
                g_SysWork.field_28 = 0;
                g_SysWork.sysStateStep_C[1] = 0;
                g_SysWork.timer_2C = 0;
                g_SysWork.sysStateStep_C[2] = 0;
            }
            break;

        default:
            Player_ControlUnfreeze(false);

            SysWork_StateSetNext(SysState_Gameplay);

            Savegame_EventFlagClear(EventFlag_119);
            Savegame_EventFlagClear(EventFlag_118);

            if (D_800E1FE2 != 0)
            {
                vcReturnPreAutoCamWork(false);
            }
            break;
    }
}

void func_800DCF00(void) // 0x800DCF00
{
    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            Player_ControlFreeze();
            SysWork_StateStepIncrementAfterFade(0, true, 2, Q12(0.0f), false);

            D_800E1FE4 = 0;

            SysWork_StateStepIncrement(0);

        case 1:
            func_80085DF0();
            break;

        case 2:
            SysWork_StateStepIncrementDelayed(Q12(0.3f), false);
            break;

        case 3:
            func_80085EB8(0, &g_SysWork.playerWork_4C.player_0, 106, false);
            SysWork_StateStepIncrement(0);

        case 4:
            SysWork_StateStepIncrementAfterFade(0, true, 0, Q12(0.03f), false);
            SysWork_StateStepIncrement(0);

        case 5:
            SysWork_StateStepIncrementAfterFade(1, true, 0, Q12(0.0f), false);

            g_ScreenFadeTimestep += Q12_MULT_FLOAT_PRECISE(g_DeltaTime, 0.1f);
            g_ScreenFadeTimestep  = MIN(g_ScreenFadeTimestep, Q12(3.0f));
            break;

        default:
            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);
            Savegame_EventFlagSet(EventFlag_120);
            Sd_SfxStop(Sfx_Unk1451);
            break;
    }

    if (g_SysWork.sysStateStep_C[0] >= 2 && g_SysWork.sysStateStep_C[0] < 6)
    {
        s32 var_t0;

        if (D_800E1FE4 == 0)
        {
            SD_Call(Sfx_Unk1451);
        }

        func_8005DE0C(Sfx_Unk1451, &g_WorldObject0.position_1C, (D_800E1FE4 + Q12(0.1f)) >> 4, Q12(32.0f), 0);

        var_t0     = D_800E1FE4 + Q12_MULT_FLOAT_PRECISE(g_DeltaTime, 1.0f);
        var_t0     = MIN(var_t0, Q12(0.4f));
        D_800E1FE4 = var_t0;

        g_SysWork.playerWork_4C.player_0.position_18.vy += Q12_MULT_PRECISE(g_DeltaTime, D_800E1FE4);
        g_WorldObject0.position_1C.vy                   += Q12_MULT_PRECISE(g_DeltaTime, D_800E1FE4);
    }
}

void func_800DD208(void) // 0x800DD208
{
    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            Player_ControlFreeze();
            func_80086470(0, InventoryItemId_ClassroomKey, 0, false);
            SysWork_StateStepIncrement(0);

        case 1:
            func_80085DF0();
            break;

        case 2:
            func_80085EB8(0, &g_SysWork.playerWork_4C.player_0, 59, false);
            SysWork_StateStepIncrement(0);

        case 3:
            func_80086470(1, InventoryItemId_ClassroomKey, 0, false);
            break;

        case 4:
            func_80085EB8(1, &g_SysWork.playerWork_4C.player_0, 0, false);
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
            func_80086C58(&g_SysWork.playerWork_4C.player_0, 60);
            break;

        default:
            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);
            break;
    }
}
void func_800DD420(void) // 0x800DD420
{
    sharedFunc_800D08B8_0_s00(6, 127);

    Particle_SystemUpdate(0, g_SavegamePtr->mapOverlayId_A4, 0);

    Savegame_EventFlagClear(EventFlag_225);

    SysWork_StateSetNext(SysState_Gameplay);
}

void Map_WorldObjectsInit(void) // 0x800DD494
{
    s32 idx;

    WorldObject_ModelNameSet(&g_WorldObjectC, "FAN_HIDE");

    Math_Vector3Set(&g_ObjPosC[0], Q12(100.0f), Q12(-1.6f), Q12(142.9f));
    Math_SetSVectorFast(&g_ObjRotC[0], 0, 0, 0);
    Math_Vector3Set(&g_ObjPosC[1], Q12(100.0f), Q12(-1.6f), Q12(145.25f));
    Math_SetSVectorFast(&g_ObjRotC[1], 0, 0, 0);
    Math_Vector3Set(&g_ObjPosC[1], Q12(100.0f), Q12(-1.6f), Q12(145.25f)); // Set again?

    WorldObjectInit(&g_WorldObject1, "DOOR_HID", 18.37f, -0.8f, 59.51f, 0.0f, 0.0f, 0.0f);

    WorldObjectInit(&g_WorldObject3, "GUN_HIDE", 17.8643f, -0.04f, 59.5135f, 0.0f, -215.3f, 0.0f);

    WorldObjectInit(&g_WorldObject4, "RING1_HI", 60.5f, -1.04f, -61.0f, 0.0f, 0.0f, 0.0f);

    WorldObjectInit(&g_WorldObject5, "RING2_HI", 60.5f, -1.04f, -59.0f, 0.0f, 0.0f, 0.0f);

    WorldObjectInit(&g_WorldObject6, "DOOR2_HI", 58.4f, 0.0f, -60.4f, 0.0f, 0.0f, 0.0f);

    WorldObjectInit(&g_WorldObject7, "DOOR1_HI", 58.4f, 0.0f, -59.6f, 0.0f, 0.0f, 0.0f);

    WorldObjectNoRotInit(&g_WorldObject0, "BOX_HIDE", 54.47f, 0.0f, -60.0f);

    WorldObjectInit(&g_WorldObject8, "KEY_HIDE", 139.199f, -0.8753f, 99.3733f, 0.0f, 46.2f, 0.0f);

    WorldObjectInit(&g_WorldObject9, "PHONE3_H", 18.974f, -0.9f, 143.515f, 0.0f, -78.3f, 0.0f);

    WorldObjectInit(&g_WorldObjectA, "PHONE2_H", 18.974f, -0.9f, 143.515f, 0.0f, -78.3f, 0.0f);

    WorldObjectInit(&g_WorldObject2, "KEY_HIDE", -16.51f, -0.11f, -51.54f, 0.0f, -19.3f, 0.0f);

    WorldObjectNoRotInit(&g_WorldObjectD, "BOLL_HID", 100.124f, -1.08f, 101.166f);

    WorldObjectInit(&g_WorldObjectB, D_800A99E4.savePadName_4, 60.14f, -0.902f, 141.763f, 0.0f, 92.4f, 0.0f);

    if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Easy)
    {
        func_80088FF4(Chara_GreyChild, 1, 0);
        func_80088FF4(Chara_GreyChild, 3, 0);
        func_80088FF4(Chara_GreyChild, 8, 0);
        func_80088FF4(Chara_Creeper, 1, 0);
    }
    else if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Hard)
    {
        func_80088FF4(Chara_GreyChild, 11, 11);
        func_80088FF4(Chara_GreyChild, 13, 11);
        func_80088FF4(Chara_GreyChild, 14, 3);
        func_80088FF4(Chara_GreyChild, 15, 3);
        func_80088FF4(Chara_Creeper, 0, 13);
        func_80088FF4(Chara_Creeper, 2, 13);
        func_80088FF4(Chara_Creeper, 4, 13);
        func_80088FF4(Chara_Creeper, 6, 13);
        func_80088FF4(Chara_Creeper, 9, 3);
    }

    sharedData_800E30C8_1_s02.field_0[0]  = -0x10666;
    sharedData_800E30C8_1_s02.field_10[0] = 0x199;
    sharedData_800E30C8_1_s02.field_18[0] = -0x33333;
    sharedData_800E30C8_1_s02.field_28[0] = 0x1999;
    sharedData_800E30C8_1_s02.field_34[0] = 0x400;
    sharedData_800E30C8_1_s02.field_30[0] = 0;
    sharedData_800E30C8_1_s02.field_3C[0] = 0x666;
    sharedData_800E30C8_1_s02.field_44[0] = 0x800;
    sharedData_800E30C8_1_s02.field_4C[0] = 0xCC;
    sharedData_800E30C8_1_s02.field_5C[0] = 0x666;
    sharedData_800E30C8_1_s02.field_64[0] = 0x800;
    sharedData_800E30C8_1_s02.field_6c[0] = 0xCC;

    sharedData_800E30C8_1_s02.field_0[1]  = -0xECCC;
    sharedData_800E30C8_1_s02.field_10[1] = 0x199;
    sharedData_800E30C8_1_s02.field_18[1] = -0x33333;
    sharedData_800E30C8_1_s02.field_34[1] = 0xC00;
    sharedData_800E30C8_1_s02.field_28[1] = 0x1999;
    sharedData_800E30C8_1_s02.field_30[1] = 0;
    sharedData_800E30C8_1_s02.field_3C[1] = 0x666;
    sharedData_800E30C8_1_s02.field_44[1] = 0x800;
    sharedData_800E30C8_1_s02.field_4C[1] = 0xCC;
    sharedData_800E30C8_1_s02.field_5C[1] = 0x666;
    sharedData_800E30C8_1_s02.field_74 = 10;
    sharedData_800E30C8_1_s02.field_64[1] = 0x800;
    sharedData_800E30C8_1_s02.field_6c[1] = 0xCC;
    sharedData_800E30C8_1_s02.field_78 = 2;

    idx = 2;
    sharedData_800E30C8_1_s02.field_28[idx] = 0;
    sharedData_800E30C8_1_s02.field_10[idx] = 0x199;
    sharedData_800E30C8_1_s02.field_3C[idx] = 0x666;
    sharedData_800E30C8_1_s02.field_5C[idx] = 0x666;
    sharedData_800E30C8_1_s02.field_64[idx] = 0x800;

    D_800E5A98 = 0;
    D_800E5A99 = 0;

    WorldObject_ModelNameSet(&g_CommonWorldObjects[0], D_800A99E4.firstAidKitName_8);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[1], D_800A99E4.healthDrinkName_C);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[2], D_800A99E4.ampouleName_10);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[3], D_800A99E4.handgunBulletsName_14);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[4], D_800A99E4.shotgunShellsName_18);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[5], D_800A99E4.rifleShellsName_1C);
}

void Map_WorldObjectsUpdate(void) // 0x800DDA84
{
    s32 rng0;
    s32 rng1;
    s32 flags;
    MAP_CHUNK_CHECK_VARIABLE_DECL();

    flags = 0;

    if (PLAYER_IN_MAP_CHUNK(vx, 1, -1, 0, 0) && PLAYER_IN_MAP_CHUNK(vz, 1, -2, -1, -2))
    {
        if (!D_800E5A99 && Savegame_EventFlagGet(EventFlag_M1S03_KeyDownTheDrain))
        {
            sharedFunc_800CBC98_1_s02();
            D_800E5A99 = 1;
        }

        if (Savegame_EventFlagGet(EventFlag_M1S03_KeyDownTheDrain) && !Savegame_EventFlagGet(EventFlag_M1S02_PickupClassroomKey))
        {
            WorldGfx_ObjectAdd(&g_WorldObject2.object_0, &g_WorldObject2.position_1C, &g_WorldObject2.rotation_28);
        }
    }
    else
    {
        if (D_800E5A99)
        {
            sharedFunc_800CBD58_1_s02();
            D_800E5A99 = 0;
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, 3, -1, 3) && PLAYER_IN_MAP_CHUNK(vz, 1, 4, -1, 4))
    {
        rng0 = -0x800 - (Rng_Rand16() & 0x1FF);
        g_ObjRotC[0].vz += Q12_MULT_PRECISE(g_DeltaTime, rng0);

        WorldGfx_ObjectAdd(&g_WorldObjectC, g_ObjPosC, (SVECTOR3* ) g_ObjRotC);

        rng1 = -0x91C - (Rng_Rand16() & 0x1FF);
        g_ObjRotC[1].vz += Q12_MULT_PRECISE(g_DeltaTime, rng1);

        WorldGfx_ObjectAdd(&g_WorldObjectC, &g_ObjPosC[1], (SVECTOR3* ) &g_ObjRotC[1]);

        if (!D_800E5A98)
        {
            SD_Call(Sfx_Unk1455);
            D_800E5A98 = 1;
        }

        func_8005DE0C(Sfx_Unk1455, &g_ObjPosC[0], Q8(0.766f), Q12(16.0f), Q8(-0.25f));
    }
    else
    {
        if (D_800E5A98)
        {
            D_800E5A98 = 0;
            Sd_SfxStop(Sfx_Unk1455);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, 3, -1, 3) && PLAYER_IN_MAP_CHUNK(vz, 1, 3, -1, 3))
    {
        if (!Savegame_EventFlagGet(EventFlag_M1S02_PickupRubberBall))
        {
            WorldGfx_ObjectAdd(&g_WorldObjectD.object_0, &g_WorldObjectD.position_1C, &(SVECTOR3){ 0, 0, 0 });
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 0, 0, -1, 1) && PLAYER_IN_MAP_CHUNK(vz, 1, 2, -1, 2))
    {
        if (!Savegame_EventFlagGet(EventFlag_M1S02_PickupShotgun))
        {
            WorldGfx_ObjectAdd(&g_WorldObject3.object_0, &g_WorldObject3.position_1C, &g_WorldObject3.rotation_28);
        }

        if (Savegame_EventFlagGet(EventFlag_96))
        {
            g_WorldObject1.rotation_28.vy = Q12_ANGLE(-112.5f);
        }
        else
        {
            flags = 1 << 1;
        }

        WorldGfx_ObjectAdd(&g_WorldObject1.object_0, &g_WorldObject1.position_1C, &g_WorldObject1.rotation_28);
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, 2, -1, 2) && PLAYER_IN_MAP_CHUNK(vz, 1, -2, -1, -2))
    {
        WorldGfx_ObjectAdd(&g_WorldObject4.object_0, &g_WorldObject4.position_1C, &g_WorldObject4.rotation_28);
        WorldGfx_ObjectAdd(&g_WorldObject5.object_0, &g_WorldObject5.position_1C, &g_WorldObject5.rotation_28);
        WorldGfx_ObjectAdd(&g_WorldObject6.object_0, &g_WorldObject6.position_1C, &g_WorldObject6.rotation_28);
        WorldGfx_ObjectAdd(&g_WorldObject7.object_0, &g_WorldObject7.position_1C, &g_WorldObject7.rotation_28);
        WorldGfx_ObjectAdd(&g_WorldObject0.object_0, &g_WorldObject0.position_1C, &(SVECTOR3){ 0, 0, 0 });

        if (g_WorldObject6.rotation_28.vy != Q12_ANGLE(180.0f) ||
            g_WorldObject7.rotation_28.vy != g_WorldObject6.rotation_28.vy)
        {
            flags |= 1 << 2;
            Savegame_EventFlagClear(EventFlag_362);
        }
        else
        {
            Savegame_EventFlagSet(EventFlag_362);
        }

        flags |= 1 << 1;
    }
    else
    {
        if (Savegame_EventFlagGet(EventFlag_362))
        {
            g_WorldObject7.rotation_28.vy = Q12_ANGLE(180.0f);
        }
        else
        {
            g_WorldObject7.rotation_28.vy = Q12_ANGLE(90.0f);
        }

        g_WorldObject6.rotation_28.vy = Q12_ANGLE(180.0f);
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, 4, -1, 4) && PLAYER_IN_MAP_CHUNK(vz, 1, 3, -1, 3))
    {
        if (!Savegame_EventFlagGet(EventFlag_M1S02_PickupPictureCard))
        {
            WorldGfx_ObjectAdd(&g_WorldObject8.object_0, &g_WorldObject8.position_1C, &g_WorldObject8.rotation_28);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 0, 0, -1, 1) && PLAYER_IN_MAP_CHUNK(vz, 1, 4, -1, 4))
    {
        if (!Savegame_EventFlagGet(EventFlag_99))
        {
            WorldGfx_ObjectAdd(&g_WorldObject9.object_0, &g_WorldObject9.position_1C, &g_WorldObject9.rotation_28);
            WorldGfx_ObjectAdd(&g_WorldObjectA.object_0, &g_WorldObjectA.position_1C, &g_WorldObjectA.rotation_28);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, 2, -1, 2) && PLAYER_IN_MAP_CHUNK(vz, 1, 4, -1, 4))
    {
        WorldGfx_ObjectAdd(&g_WorldObjectB.object_0, &g_WorldObjectB.position_1C, &g_WorldObjectB.rotation_28);
    }

    func_80069844(0xFFFF);

    if (flags != 0)
    {
        func_8006982C(flags);
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 0, 0, -1, 1) && PLAYER_IN_MAP_CHUNK(vz, 1, -2, -1, -2))
    {
        if (!Savegame_EventFlagGet(EventFlag_M1S02_Ampoule0))
        {
            WorldGfx_ObjectAdd(&g_CommonWorldObjects[2], &g_CommonWorldObjectPoses->position_0, &g_CommonWorldObjectPoses->rotation_C);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 0, 0, -1, 1) && PLAYER_IN_MAP_CHUNK(vz, 1, -2, -1, -2))
    {
        if (!Savegame_EventFlagGet(EventFlag_M1S02_ShotgunShells0))
        {
            WorldGfx_ObjectAdd(&g_CommonWorldObjects[5], &g_CommonWorldObjectPoses[1].position_0, &g_CommonWorldObjectPoses[1].rotation_C);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 0, 0, -1, 1) && PLAYER_IN_MAP_CHUNK(vz, 1, -2, -1, -2))
    {
        if (!Savegame_EventFlagGet(EventFlag_M1S02_ShotgunShells1))
        {
            WorldGfx_ObjectAdd(&g_CommonWorldObjects[5], &g_CommonWorldObjectPoses[2].position_0, &g_CommonWorldObjectPoses[2].rotation_C);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, 3, -1, 3) && PLAYER_IN_MAP_CHUNK(vz, 1, 4, -1, 4))
    {
        if (!Savegame_EventFlagGet(EventFlag_M1S02_FirstAidKit0))
        {
            WorldGfx_ObjectAdd(g_CommonWorldObjects, &g_CommonWorldObjectPoses[3].position_0, &g_CommonWorldObjectPoses[3].rotation_C);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, 3, -1, 3) && PLAYER_IN_MAP_CHUNK(vz, 1, 4, -1, 4))
    {
        if (!Savegame_EventFlagGet(EventFlag_M1S02_HandgunBullets0))
        {
            WorldGfx_ObjectAdd(&g_CommonWorldObjects[3], &g_CommonWorldObjectPoses[4].position_0, &g_CommonWorldObjectPoses[4].rotation_C);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 0, 0, -1, 1) && PLAYER_IN_MAP_CHUNK(vz, 1, 4, -1, 4))
    {
        if (!Savegame_EventFlagGet(EventFlag_M1S02_HandgunBullets1))
        {
            WorldGfx_ObjectAdd(&g_CommonWorldObjects[3], &g_CommonWorldObjectPoses[5].position_0, &g_CommonWorldObjectPoses[5].rotation_C);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, 2, -1, 2) && PLAYER_IN_MAP_CHUNK(vz, 0, 0, -1, 1))
    {
        if (!Savegame_EventFlagGet(EventFlag_M1S02_HandgunBullets2))
        {
            WorldGfx_ObjectAdd(&g_CommonWorldObjects[3], &g_CommonWorldObjectPoses[6].position_0, &g_CommonWorldObjectPoses[6].rotation_C);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, 3, -1, 3) && PLAYER_IN_MAP_CHUNK(vz, 0, 0, -1, 1))
    {
        if (!Savegame_EventFlagGet(EventFlag_M1S02_Ampoule1))
        {
            WorldGfx_ObjectAdd(&g_CommonWorldObjects[2], &g_CommonWorldObjectPoses[7].position_0, &g_CommonWorldObjectPoses[7].rotation_C);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, 2, -1, 2) && PLAYER_IN_MAP_CHUNK(vz, 1, 4, -1, 4))
    {
        if (!Savegame_EventFlagGet(EventFlag_M1S02_HealthDrink0))
        {
            WorldGfx_ObjectAdd(&g_CommonWorldObjects[1], &g_CommonWorldObjectPoses[8].position_0, &g_CommonWorldObjectPoses[8].rotation_C);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, 2, -1, 2) && PLAYER_IN_MAP_CHUNK(vz, 1, 4, -1, 4))
    {
        if (!Savegame_EventFlagGet(EventFlag_M1S02_FirstAidKit1))
        {
            WorldGfx_ObjectAdd(g_CommonWorldObjects, &g_CommonWorldObjectPoses[9].position_0, &g_CommonWorldObjectPoses[9].rotation_C);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, 3, -1, 3) && PLAYER_IN_MAP_CHUNK(vz, 1, 2, -1, 2))
    {
        if (!Savegame_EventFlagGet(EventFlag_M1S02_HealthDrink1))
        {
            WorldGfx_ObjectAdd(&g_CommonWorldObjects[1], &g_CommonWorldObjectPoses[10].position_0, &g_CommonWorldObjectPoses[10].rotation_C);
        }
    }
}

void func_800DEC88(void) // 0x800DEC88
{
    if (Savegame_EventFlagGet(EventFlag_MapMark_AltSchool1F_ReceptionArrows))
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
        func_80088FF4(Chara_Creeper, 7, 12);
        func_80088FF4(Chara_Creeper, 8, 12);
        if (g_SavegamePtr->gameDifficulty_260 == 1)
        {
            func_80088FF4(Chara_Creeper, 9, 12);
        }
    }
}
