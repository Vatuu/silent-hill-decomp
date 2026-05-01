#include "bodyprog/bodyprog.h"
#include "bodyprog/events/bodyprog_data_800A99B4.h"
#include "bodyprog/gfx/map_effects.h"
#include "bodyprog/math/math.h"
#include "bodyprog/player.h"
#include "main/rng.h"
#include "maps/map2/map2_s00.h"
#include "maps/particle.h"
#include "maps/characters/player.h"

#include "maps/shared/sharedFunc_800D929C_0_s00.h" // 0x800E76B8

#include "maps/shared/Map_RoomIdxGet.h" // 0x800E76C8

#include "maps/shared/Map_RoomBgmInit_2_s00.h" // 0x800E7914

void GameBoot_LoadScreen_StageString(void) {}

#include "maps/shared/MapEvent_DoorJammed.h" // 0x800E7A24

#include "maps/shared/MapEvent_DoorLocked.h" // 0x800E7AB8

const char* MAP_MESSAGES[] = {
    #include "maps/shared/map_msg_common.h"
    /* 15 */ "\tThere_is_a_ ~C2 Steel_pipe ~C7 . ~N\n\tTake_it? ~S4 ",
    /* 16 */ "\tWhere_could_Cheryl_have_gone? ",
    /* 17 */ "\tI_guess_I'll_check ~N\n\tthat_alley_again. ~E ",
    /* 18 */ "~C3\tTo_school ~E ",
    /* 19 */ "~J1(2.5)\n\tIsn't_this ~N\n\tCheryl's_sketchbook? ",
    /* 20 */ "~J1(3.8)\n\tHmm... ~N\n\tShe's_at_the_school... ~E ",
    /* 21 */ "\tSketchbook_cover. ~N\n\tThis_picture..._it's_me. ",
    /* 22 */ "\tThe_first_picture_that_Cheryl ~N\n\tdrew_in_the_sketchbook_that_I ~N\n\tgave_on_her_5th_birthday. ~E ",
    /* 23 */ "~M ~C3\tDoghouse ~N\n\t\tLevin_st. ~E ",
    /* 24 */ "\tNothing_unusual. ~E ",
    /* 25 */ "\tProbably_a_doghouse, ~N\n\tthough_I'm_not_sure ~N\n\tsince_there's_no_dog_around. ",
    /* 26 */ "\tNothing_in_particular_around. ~E ",
    /* 27 */ "\t~C2 House_key ~C7 _was_hidden ~N\n\tin_the_dog_house._Take_it? ~S4 ",
    /* 28 */ "\tThere_is_a_ ~C2 Key_of_[Lion] ~C7 . ~N\n\tTake_it? ~S4 ",
    /* 29 */ "\tThere_is_a_ ~C2 Key_of_[Woodman] ~C7 . ~N\n\tTake_it? ~S4 ",
    /* 30 */ "\tThere_is_a_ ~C2 Key_of_[Scarecrow] ~C7 . ~N\n\tTake_it? ~S4 ",
    /* 31 */ "\tUsed_the_ ~C2 House_key ~C7 . ~E ",
    /* 32 */ "\tUsed_the_ ~C2 Key_of_[Lion] ~C7 . ~E ",
    /* 33 */ "\tUsed_the_ ~C2 Key_of_[Woodman] ~C7 . ~E ",
    /* 34 */ "\tUsed_the_ ~C2 Key_of_[Scarecrow] ~C7 . ~E ",
    /* 35 */ "~J0(20)\tWhat? ~E ",
    /* 36 */ "\tIt's_getting_dark_again? ",
    /* 37 */ "\tWhat's_going_on!? ~E ",
    /* 38 */ "\tA_dog's_head... ~E ",
    /* 39 */ "\tUsed_the_ ~C2 K._Gordon_key ~C7 . ~E ",
    /* 40 */ "~C3\tMidwich_Elementary_School ~E ",
    /* 41 */ "\tNo_reason_to_search ~N\n\tthe_school_anymore. ~E ",
    /* 42 */ "~C3\tOrridge_Bridge_Control_Room ~E ",
    /* 43 */ "\tThere's_a_keyhole ~N\n\ton_the_control_panel. ~E ",
    /* 44 */ "\tThe_machinery_is_running. ~N\n\tDo_you_want_to_press_the_switch? ~S4 ",
    /* 45 */ "\tThe_street_is_blocked. ~N\n\tCan't_get_out_of_town_through_here. ~E ",
    /* 46 */ "\tMy_car... ~N\n\ttoo_banged_up_to_drive. ",
    /* 47 */ "\tWhere's_Cheryl? ~N\n\tHope_she's_safe. ~E ",
    /* 48 */ "~C3\tOrridge_Bridge_Control_Room ~E ",
    /* 49 */ "~C3\tReservoir. ~N\n\t\tAuthorized_Personnel_only. ~E ",
    /* 50 */ "\tHmm..._the_lock_is_worn_out. ",
    /* 51 */ "\tI_may_be_able_to_break_it ~N\n\tif_I_hit_it_hard. ~E ",
    /* 52 */ "\tSomething_is_written_on_the_map ~N\n\thanging_on_the_wall. ",
    /* 53 */ "\tCopied_it_to_the_map. ~E ",
    /* 54 */ "\tSomething_is_written_on_the_map ~N\n\thanging_on_the_wall. ~E ",
    /* 55 */ " ",
    /* 56 */ "\tThere_are_three_locks. ~E ",
    /* 57 */ "\tThere_are_two_locks. ~E ",
    /* 58 */ "\tThere_is_one_lock. ~E ",
    /* 59 */ "\tIt's_unlocked. ~E ",
    /* 60 */ "~H\tThere_is_a_ ~C5 Shopping_district_map ~C7 . ~N\n\tTake_it? ~S4 ",
    /* 61 */ "\tNothing_special. ~E ",
    /* 62 */ "\tThe_drawbridge_is_operating. ~E ",
    /* 63 */ "\tThe_drawbridge_is_stopped. ~E ",
    /* 64 */ "\tThere's_a_TV_set. ~N\n\tThe_power_must_be_out. ~N\n\tIt_doesn't_work. ~E ",
    /* 65 */ "\tNothing_useful. ~E ",
    /* 66 */ "\tNothing_special. ~E ",
    /* 67 */ "\tThe_refrigerator_is_empty. ~E ",
    /* 68 */ "\tThe_garage_door_is_smeared ~N\n\twith_blood. ~E ",
    /* 69 */ "~C3\tK._Gordon ~E ",
    /* 70 */ "~C3\tBalkan_Church ~E ",
    /* 71 */ "\tThere_is_a_ ~C2 Rock_drill ~C7 . ",
    /* 72 */ "\tThere_is_no_gasoline. ~N\n\tCan't_use_it. ~E ",
    /* 73 */ "\tThere_is_a_ ~C2 Rock_drill ~C7 . ~N\n\tTake_it? ~S4 ",
    /* 74 */ "\tThere_is_a_ ~C2 Chainsaw ~C7 . ",
    /* 75 */ "\tThere_is_no_gasoline. ~N\n\tCan't_use_it. ~E ",
    /* 76 */ "\tThere_is_a_ ~C2 Chainsaw ~C7 . ~N\n\tTake_it? ~S4 ",
    /* 77 */ "\tUsed_the_gasoline. ~E ",
    /* 78 */ "\tThis_must_be_that_water_works ~N\n\tLisa_was_talking_about. ~E "
};

void func_800E7B74(void) // 0x800E7B74
{
    u32 pickupType;
    s32 eventFlagIdx;

    pickupType   = CommonPickupItemId_FirstAidKit;
    eventFlagIdx = 0;

    switch (g_MapEventData->pointOfInterestIdx)
    {
        case 139:
            pickupType   = CommonPickupItemId_FirstAidKit;
            eventFlagIdx = EventFlag_M2S00_FirstAidKit0;
            break;

        case 140:
            pickupType   = CommonPickupItemId_HandgunBullets;
            eventFlagIdx = EventFlag_M2S00_HandgunBullets0;
            break;

        case 141:
            pickupType   = CommonPickupItemId_HandgunBullets;
            eventFlagIdx = EventFlag_M2S00_HandgunBullets1;
            break;

        case 142:
            pickupType   = CommonPickupItemId_HealthDrink;
            eventFlagIdx = EventFlag_M2S00_HealthDrink0;
            break;

        case 143:
            pickupType   = CommonPickupItemId_HandgunBullets;
            eventFlagIdx = EventFlag_M2S00_HandgunBullets2;
            break;

        case 144:
            pickupType   = CommonPickupItemId_ShotgunShells;
            eventFlagIdx = EventFlag_M2S00_ShotgunShells0;
            break;

        case 145:
            pickupType   = CommonPickupItemId_HealthDrink;
            eventFlagIdx = EventFlag_M2S00_HealthDrink1;
            break;

        case 146:
            pickupType   = CommonPickupItemId_HandgunBullets;
            eventFlagIdx = EventFlag_M2S00_HandgunBullets3;
            break;

        case 147:
            pickupType   = CommonPickupItemId_HandgunBullets;
            eventFlagIdx = EventFlag_M2S00_HandgunBullets4;
            break;

        case 148:
            pickupType   = CommonPickupItemId_HandgunBullets;
            eventFlagIdx = EventFlag_M2S00_HandgunBullets5;
            break;

        case 149:
            pickupType   = CommonPickupItemId_HandgunBullets;
            eventFlagIdx = EventFlag_M2S00_HandgunBullets6;
            break;

        case 150:
            pickupType   = CommonPickupItemId_HandgunBullets;
            eventFlagIdx = EventFlag_M2S00_HandgunBullets7;
            break;

        case 151:
            pickupType   = CommonPickupItemId_HandgunBullets;
            eventFlagIdx = EventFlag_M2S00_HandgunBullets8;
            break;

        case 152:
            pickupType   = CommonPickupItemId_HealthDrink;
            eventFlagIdx = EventFlag_M2S00_HealthDrink2;
            break;

        case 153:
            pickupType   = CommonPickupItemId_HealthDrink;
            eventFlagIdx = EventFlag_M2S00_HealthDrink3;
            break;
        case 154:
            pickupType   = CommonPickupItemId_HealthDrink;
            eventFlagIdx = EventFlag_M2S00_HealthDrink4;
            break;

        case 155:
            pickupType   = CommonPickupItemId_HandgunBullets;
            eventFlagIdx = EventFlag_M2S00_HandgunBullets9;
            break;

        case 156:
            pickupType   = CommonPickupItemId_HealthDrink;
            eventFlagIdx = EventFlag_M2S00_HealthDrink5;
            break;

        case 157:
            pickupType   = CommonPickupItemId_HandgunBullets;
            eventFlagIdx = EventFlag_M2S00_HandgunBullets10;
            break;

        case 158:
            pickupType   = CommonPickupItemId_HealthDrink;
            eventFlagIdx = EventFlag_M2S00_HealthDrink6;
            break;

        case 159:
            pickupType   = CommonPickupItemId_HealthDrink;
            eventFlagIdx = EventFlag_M2S00_HealthDrink7;
            break;

        case 160:
            pickupType   = CommonPickupItemId_HealthDrink;
            eventFlagIdx = EventFlag_M2S00_HealthDrink8;
            break;

        case 161:
            pickupType   = CommonPickupItemId_HealthDrink;
            eventFlagIdx = EventFlag_M2S00_HealthDrink9;
            break;

        case 162:
            pickupType   = CommonPickupItemId_HealthDrink;
            eventFlagIdx = EventFlag_M2S00_HealthDrink10;
            break;

        case 163:
            pickupType   = CommonPickupItemId_HealthDrink;
            eventFlagIdx = EventFlag_M2S00_HealthDrink11;
            break;

        case 164:
            pickupType   = CommonPickupItemId_ShotgunShells;
            eventFlagIdx = EventFlag_M2S00_ShotgunShells1;
            break;

        case 165:
            pickupType   = CommonPickupItemId_FirstAidKit;
            eventFlagIdx = EventFlag_M2S00_FirstAidKit1;
            break;

        case 166:
            pickupType   = CommonPickupItemId_HandgunBullets;
            eventFlagIdx = EventFlag_M2S00_HandgunBullets11;
            break;

        case 167:
            pickupType   = CommonPickupItemId_HandgunBullets;
            eventFlagIdx = EventFlag_M2S00_HandgunBullets12;
            break;

        case 168:
            pickupType   = CommonPickupItemId_HandgunBullets;
            eventFlagIdx = EventFlag_M2S00_HandgunBullets13;
            break;

        case 169:
            pickupType   = CommonPickupItemId_HandgunBullets;
            eventFlagIdx = EventFlag_M2S00_HandgunBullets14;
            break;

        case 170:
            pickupType   = CommonPickupItemId_FirstAidKit;
            eventFlagIdx = EventFlag_M2S00_FirstAidKit2;
            break;
    }

    Event_CommonItemTake(pickupType, eventFlagIdx);
}

void func_800E7D54(void) // 0x800E7D54
{
    s32 i;

    for (i = 0; i < ARRAY_SIZE(g_SysWork.npcs); i++)
    {
        // Breaks if there are any characters with IDs in range `[Chara_Harry, Chara_MonsterCybil]` with health above `Q12(0.0f)`.
        if (g_SysWork.npcs[i].model.charaId >= Chara_Harry &&
            g_SysWork.npcs[i].model.charaId <= Chara_MonsterCybil &&
            g_SysWork.npcs[i].health > Q12(0.0f))
        {
            break;
        }
    }

    if (i != ARRAY_SIZE(g_SysWork.npcs))
    {
        g_DeltaTime = Q12(0.0f);
    }

    switch (g_SysWork.sysStateSteps[0])
    {
        case 0:
            Player_ControlFreeze();
            SysWork_StateStepIncrement(0);

        case 1:
            MapMsg_DisplayAndHandleSelection(false, 46, 0, 0, 0, false);
            break;

        case 2:
            Event_ItemTake(InvItemId_HealthDrink, DEFAULT_PICKUP_ITEM_COUNT, EventFlag_M2S00_PickupHealthDrink, 6);
            break;
    }
}

void MapEvent_AtWaterWorks(void) // 0x800E7E60
{
    s32 sysState0;

    switch (g_SysWork.sysStateSteps[0])
    {
        case 0:
            Player_ControlFreeze();

            g_SysWork.playerWork.player.position.vx = Q12(-255.78f);
            g_SysWork.playerWork.player.position.vz = Q12(-107.46f);
            g_SysWork.playerWork.player.rotation.vy = Q12_ANGLE(-45.0f);

            ScreenFade_ResetTimestep();
            func_800867B4(0, 1);
            func_800EB824(1);
            SysWork_StateStepIncrement(0);

        case 1:
        case 2:
        case 3:
            func_800692A4(0, 120, Q12(0.5f));
            func_80068E0C(1, 1, 0, 0, 0, 120, Q12(0.5f));
            func_80067914(1, 0, 120, Q12(0.5f));

            sysState0 = g_SysWork.sysStateSteps[0];
            switch (sysState0)
            {
                case 2:
                    SysWork_StateStepIncrementDelayed(Q12(3.5f), false);

                    if (g_SysWork.sysStateSteps[0] == sysState0 &&
                        (g_Controller0->btnsClicked_10 & (g_GameWorkPtr->config.controllerConfig.enter |
                                                          g_GameWorkPtr->config.controllerConfig.cancel)))
                    {
                        SysWork_StateStepSet(0, 3);
                    }
                    break;

                case 3:
                    SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(1.0f), false);
                    break;

                case 1:
                    SysWork_StateStepIncrementAfterFade(2, false, 0, Q12(1.0f), false);
                    break;
            }
            break;

        case 4:
            g_SysWork.cutsceneBorderState = 20;

            func_800867B4(2, 0);
            Camera_PositionSet(NULL, Q12(-254.15f), Q12(-1.95f), Q12(-109.3f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);
            Camera_LookAtSet(NULL, Q12(-257.0398f), Q12(-1.94f), Q12(-106.54f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);
            SysWork_StateStepIncrement(0);

        case 5:
            SysWork_StateStepIncrementAfterFade(2, false, 0, Q12(1.0f), false);
            break;

        case 6:
            MapMsg_DisplayAndHandleSelection(false, 78, 0, 0, 0, false); // "This must be the water works."
            break;

        default:
            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);
            vcReturnPreAutoCamWork(false);
            SysWork_StateStepIncrementAfterFade(0, false, 2, Q12(0.0f), false);
            Savegame_EventFlagSet(EventFlag_M2S00_WaterWorksCutscene);

            g_SysWork.flags_22A4 &= ~UnkSysFlag_4;
            break;
    }
}

void func_800E816C(void) // 0x800E816C
{
    Event_ItemTake(InvItemId_RockDrill, DEFAULT_PICKUP_ITEM_COUNT, EventFlag_M2S00_PickupRockDrill, 73);
}

void func_800E8198(void) // 0x800E8198
{
    Event_ItemTake(InvItemId_Chainsaw, DEFAULT_PICKUP_ITEM_COUNT, EventFlag_M2S00_PickupChainsaw, 76);
}

void MapEvent_MapTake(void) // 0x800E81C4
{
    Event_MapTake(2, EventFlag_M2S00_PickupMap, 60);
}

void MapEvent_SteelPipeTake(void) // 0x800E81EC
{
    typedef enum _EventState
    {
        EventState_TakeSteelPipe     = 5,
        EventState_DontTakeSteelPipe = 6
    } e_EventState;

    switch (g_SysWork.sysStateSteps[0])
    {
        case 0:
            Player_ControlFreeze();
            func_80086470(0u, InvItemId_SteelPipe, 0, false);
            SysWork_StateStepIncrement(0);

        case 1:
            func_80085DF0();
            break;

        case 2:
            func_80086C58(&g_SysWork.playerWork.player, 59);
            break;

        case 3:
            func_80086470(1, InvItemId_SteelPipe, 0, false);
            break;

        case 4:
            Savegame_EventFlagSet(EventFlag_M2S00_PickupSteelPipe);

            if (Gfx_PickupItemAnimate(InvItemId_SteelPipe))
            {
                MapMsg_DisplayAndHandleSelection(true, 15, EventState_TakeSteelPipe, EventState_DontTakeSteelPipe, 0, false);
            }
            break;

        case EventState_TakeSteelPipe:
            func_80086470(3, InvItemId_SteelPipe, 1, false);
            SysWork_StateStepSet(0, 7);
            break;

        case EventState_DontTakeSteelPipe:
            Savegame_EventFlagClear(EventFlag_M2S00_PickupSteelPipe);
            SysWork_StateStepIncrement(0);

        case 7:
            func_80086C58(&g_SysWork.playerWork.player, 60);
            break;

        default:
            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);
            break;
    }
}

void MapEvent_CutsceneExitCafe(void) // 0x800E83C0
{
    s32 zoomX;
    s32 zoomZ;
    s32 zoomHuh;
    s16 curve;

    if (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config.controllerConfig.skip)
    {
        if (g_SysWork.sysStateSteps[0] == 2)
        {
            SysWork_StateStepSet(0, 13);
        }
        else
        {
            if (!D_800F228E && g_SysWork.sysStateSteps[0] > 5 && g_SysWork.sysStateSteps[0] < 11)
            {
                SysWork_StateStepIncrementAfterFade(0, true, 0, Q12(0.0f), false);
                D_800F228E = 1;
            }
        }
    }

    if (D_800F228E)
    {
        if (ScreenFade_IsFinished())
        {
            D_800F228E = 0;
            SysWork_StateStepSet(0, 12);
        }
    }

    switch (g_SysWork.sysStateSteps[0])
    {
        case 0:
            Player_ControlFreeze();
            g_SysWork.cutsceneBorderState = 20;
            D_800F228C = 0;
            g_Gfx_PaperMapMarkingAlpha = 0;

            Savegame_EventFlagSet(EventFlag_MapMark_OldTown_CofeArrowOnly);
            Savegame_EventFlagSet(EventFlag_MapMark_OldTown_CofeSignOnly);

            D_800F228E = 0;

            SysWork_StateStepIncrement(0);

        case 1:
            Camera_PositionSet(NULL, Q12(15.54f), Q12(-1.5f), Q12(55.64f), 0, 0, 0, 0, true);
            Camera_LookAtSet(NULL, Q12(19.42f), Q12(-1.75f), Q12(56.6f), 0, 0, 0, 0, true);
            SysWork_StateStepIncrement(0);

        case 2:
            MapMsg_DisplayAndHandleSelection(false, 16, 0, 0, 0, false); // "Where could Cheryl have gone?"
            break;

        case 3:
            Fs_QueueStartSeek(FILE_TIM_MP_0TOWN_TIM + D_800A99B5);
            SysWork_StateStepIncrement(0);

        case 4:
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(0.0f), false);
            break;

        case 5:
            func_800867B4(0, 1);
            SysWork_StateStepIncrement(0);

        case 6:
            func_800692A4(0, 0, Q12(1.0f));
            func_80068E0C(1, 1, 0, 0, 0, 0, Q12(1.0f));
            SysWork_StateStepIncrementAfterFade(2, false, 0, Q12(0.0f), false);
            break;

        case 7:
            func_800692A4(0, 0, Q12(1.0f));
            func_80068E0C(1, 1, 0, 0, 0, 0, Q12(1.0f));

            D_800F228C += 0x20;

            Map_BoxOutlineDraw(D_800F228C, -0xA0, -0xE0, 0x13F, 0x1BF, -0x58, -0xC0, 0x9F, 0xDF);

            if (D_800F228C == Q12(1.0f))
            {
                SysWork_StateStepIncrement(0);
            }
            break;

        case 8:
            // Decrement zoom counter.
            D_800F228C -= 0x40;

            func_800692A4(0x48 - Q12_MULT_PRECISE(D_800F228C, 0x48),
                          0x10 - Q12_MULT_PRECISE(D_800F228C, 0x10),
                          (D_800F228C >> 1) + Q12(0.5f));

            func_80068E0C(1, 1, 0, 0,
                          0x48 - Q12_MULT_PRECISE(D_800F228C, 0x48),
                          0x10 - Q12_MULT_PRECISE(D_800F228C, 0x10),
                          (D_800F228C >> 1) + Q12(0.5f));

            curve = (FP_TO(D_800F228C, 12) / (D_800F228C + Q12(1.0f))) * -1;

            Map_BoxOutlineDraw(curve, -0xA0, -0xE0, 0x13F, 0x1BF, -0x10, -0xA0, 0, 0);

            if (D_800F228C == 0)
            {
                SysWork_StateStepIncrement(0);
            }
            break;

        case 9:
            func_800692A4(0x48, 0x10, Q12(0.5f));
            func_80068E0C(1, 1, 0, 0, 72, 0x10, Q12(0.5f));
            SysWork_StateStepIncrementDelayed(Q12(1.0f), false);
            break;

        case 10:
            func_800692A4(0x48, 0x10, Q12(0.5f));
            func_80068E0C(1, 1, 0, 0, 72, 0x10, Q12(0.5f));
            func_80068E0C(2, 1, 0x36A, g_Gfx_PaperMapMarkingAlpha, 0x48, 0x10, Q12(0.5f));

            // Fade in map marking to half opacity.
            g_Gfx_PaperMapMarkingAlpha++;
            if (g_Gfx_PaperMapMarkingAlpha >= 128)
            {
                if (g_Controller0->btnsClicked_10 & (g_GameWorkPtr->config.controllerConfig.enter |
                                                     g_GameWorkPtr->config.controllerConfig.cancel))
                {
                    SysWork_StateStepIncrement(0);
                }

                SysWork_StateStepIncrementDelayed(Q12(1.5f), false);

                if (g_SysWork.sysStateSteps[0] > 11)
                {
                    g_SysWork.sysStateSteps[0] = 11;
                }

                // Clamp map marking fade.
                g_Gfx_PaperMapMarkingAlpha = 128;
            }
            break;

        case 11:
            func_800692A4(0x48, 0x10, Q12(0.5f));
            func_80068E0C(1, 1, 0, 0, 0x48, 0x10, Q12(0.5f));
            func_80068E0C(2, 1, 0x36A, 128, 0x48, 0x10, Q12(0.5f));
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(0.0f), false);
            break;

        case 12:
            func_800867B4(2, 0);
            D_800F228E = 0;
            SysWork_StateStepIncrement(0);

        case 13:
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(0.0f), false);
            break;

        case 14:
            SysWork_StateStepIncrementAfterFade(0, false, 0, Q12(0.0f), false);
            SysWork_StateStepIncrement(0);

        default:
            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);
            Savegame_EventFlagSet(EventFlag_MapMark_OldTown_CherylArrowAndSign);
            vcReturnPreAutoCamWork(false);
            SysWork_StateStepIncrementAfterFade(0, false, 2, Q12(0.0f), false);

            g_SysWork.flags_22A4 &= ~UnkSysFlag_4;

            func_8003A16C();
            break;
    }
}

void MapEvent_CherylsSketchbook(void) // 0x800E8C0C
{
    s16 curve;

    if (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config.controllerConfig.skip)
    {
        if (!D_800F2295)
        {
            if (g_SysWork.sysStateSteps[0] > 1 && g_SysWork.sysStateSteps[0] < 10)
            {
                SysWork_StateStepIncrementAfterFade(0, true, 0, Q12(0.0f), false);
                D_800F2295 = 1;
            }
            else if (g_SysWork.sysStateSteps[0] > 10 && g_SysWork.sysStateSteps[0] < 16)
            {
                SysWork_StateStepIncrementAfterFade(0, true, 0, Q12(0.0f), false);
                D_800F2295 = 2;
            }
        }
    }

    if (D_800F2295)
    {
        if (ScreenFade_IsFinished())
        {
            if (D_800F2295 == 1)
            {
                SysWork_StateStepSet(0, 21);
            }
            else
            {
                SysWork_StateStepSet(0, 22);
            }

            D_800F2295 = 0;
        }
    }

    switch (g_SysWork.sysStateSteps[0])
    {
        case 0:
            Player_ControlFreeze();
            Savegame_EventFlagSet(EventFlag_MapMark_11);
            func_800862F8(0, FILE_TIM_TOSCHOOL_TIM, false);

            g_Cutscene_MapMsgAudioIdx = 0;
            D_800F2298 = 0;
            D_800F229C = 0;

            SysWork_StateStepIncrement(0);

        case 1:
            func_80085DF0();
            break;

        case 2:
            func_80086C58(&g_SysWork.playerWork.player, 59);
            break;

        case 3:
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(0.0f), false);
            break;

        case 4:
            func_800862F8(1, 0, false);
            break;

        case 5:
            func_800862F8(2, 0, false);
            SysWork_StateStepIncrementAfterFade(2, false, 0, Q12(0.0f), false);
            break;

        case 6:
            func_800862F8(2, 0, false);
            MapMsg_DisplayAndHandleSelection(false, 18, 0, 0, 0, false); // "To school."
            break;

        case 7:
            g_Screen_BackgroundImgGamma = Q8(6.0f / 32.0f);

            func_800862F8(2, 0, false);
            Map_MessageWithAudio(19, &g_Cutscene_MapMsgAudioIdx, &g_Cutscene_MapMsgAudioCmds); // "Isn't this Cheryl's sketchbook?"
            break;

        case 8:
            Fs_QueueStartSeek(FILE_TIM_MP_0TOWN_TIM + D_800A99B5);
            SysWork_StateStepIncrement(0);

        case 9:
            g_Screen_BackgroundImgGamma = Q8(6.0f / 32.0f);

            func_800862F8(2, 0, false);
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(0.0f), false);
            break;

        case 10:
            func_800867B4(0, 1);
            Savegame_EventFlagSet(EventFlag_147);
            SysWork_StateStepIncrement(0);

        case 11:
            func_800692A4(0, 0, Q12(1.0f));
            func_80068E0C(1, 1, 0, 0, 0, 0, Q12(1.0f));
            SysWork_StateStepIncrementAfterFade(2, false, 0, Q12(0.0f), false);
            break;

        case 12:
            func_800692A4(0, 0, Q12(1.0f));
            func_80068E0C(1, 1, 0, 0, 0, 0, Q12(1.0f));
            D_800F229C += 0x20;
            Map_BoxOutlineDraw(D_800F229C, -0xA0, -0xE0, 0x13F, 0x1BF, -0xA0, 8, 0x9F, 0xDF);

            if (D_800F229C == Q12(1.0f))
            {
                SysWork_StateStepIncrement(0);
            }
            break;

        case 13:
            // Decrement zoom counter.
            D_800F229C -= 0x40;

            func_800692A4(0,
                          0x74 - FP_MULTIPLY_PRECISE(D_800F229C, 0x74, 12),
                          (D_800F229C >> 1) + Q12(0.5f));

            func_80068E0C(1, 1, 0, 0, 0,
                          0x74 - FP_MULTIPLY_PRECISE(D_800F229C, 0x74, 12),
                          (D_800F229C >> 1) + Q12(0.5f));

            curve = (FP_TO(D_800F229C, 12) / (D_800F229C + Q12(1.0f))) * -1;

            Map_BoxOutlineDraw(curve, -0xA0, -0xE0, 0x13F, 0x1BF, -0xA0, 0xF0, 0, 0);

            if (D_800F229C == 0)
            {
                SysWork_StateStepIncrement(0);
                break;
            }
            break;

        case 14:
            func_800692A4(0, 0x74, Q12(0.5f));
            func_80068E0C(1, 1, 0, 0, 0, 0x74, Q12(0.5f));
            SysWork_StateStepIncrementDelayed(Q12(1.0f), false);

            break;
        case 15:
            func_800692A4(0, 0x74, Q12(0.5f));
            func_80068E0C(1, 1, 0, 0, 0, 0x74, Q12(0.5f));
            func_80068E0C(2, 1, 0x3A2, D_800F2298, 0, 0x74, Q12(0.5f));

            D_800F2298++;
            if (D_800F2298 >= 0x80)
            {
                if (g_Controller0->btnsClicked_10 & (g_GameWorkPtr->config.controllerConfig.enter | g_GameWorkPtr->config.controllerConfig.cancel))
                {
                    SysWork_StateStepIncrement(0);
                }

                SysWork_StateStepIncrementDelayed(Q12(1.5f), false);

                if (g_SysWork.sysStateSteps[0] > 16)
                {
                    g_SysWork.sysStateSteps[0] = 16;
                }

                D_800F2298 = 0x80;
            }
            break;

        case 16:
            func_800692A4(0, 0x74, Q12(0.5f));
            func_80068E0C(1, 1, 0, 0, 0, 0x74, Q12(0.5f));
            func_80068E0C(2, 1, 0x3A2, 128, 0, 0x74, Q12(0.5f));
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(0.0f), false);
            break;

        case 17:
            func_800867B4(2, 0);
            Savegame_EventFlagSet(EventFlag_MapMark_OldTown_SchoolCircle);

            D_800F2295 = 0;

            SysWork_StateStepIncrement(0);

        case 18:
            SysWork_StateStepIncrementAfterFade(2, false, 0, Q12(0.0f), false);
            break;

        case 19:
            func_80086C58(&g_SysWork.playerWork.player, 60);
            break;

        case 22:
            func_800867B4(2, 0);

        case 21:
            Savegame_EventFlagSet(EventFlag_147);
            Savegame_EventFlagSet(EventFlag_MapMark_OldTown_SchoolCircle);
            SysWork_StateStepIncrementAfterFade(0, false, 0, Q12(0.0f), false);
            Player_ControlUnfreeze(true);
            SysWork_StateSetNext(SysState_Gameplay);

        default:
            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);
            func_80086470(3, InvItemId_NoteToSchool, 1, false);
            func_8003A16C();
            break;
    }
}

void func_800E9470(void) // 0x800E9470
{
    switch (g_SysWork.sysStateSteps[0])
    {
        case 0:
            Player_ControlFreeze();
            func_800862F8(0, FILE_TIM_SKETCHBK_TIM, false);
            SysWork_StateStepIncrement(0);

        case 1:
            func_80085DF0();
            break;

        case 2:
            func_80086C58(&g_SysWork.playerWork.player, 59);
            break;

        case 3:
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(0.0f), false);
            break;

        case 4:
            func_800862F8(1, FILE_1ST_2ZANKO80_TIM, false);
            break;

        case 5:
            func_800862F8(2, FILE_1ST_2ZANKO80_TIM, false);
            SysWork_StateStepIncrementAfterFade(2, false, 0, Q12(0.0f), false);
            break;

        case 6:
            func_800862F8(2, FILE_1ST_2ZANKO80_TIM, false);
            MapMsg_DisplayAndHandleSelection(false, 21, 0, 0, 0, false);
            break;

        case 7:
            SysWork_StateStepIncrementAfterFade(2, false, 0, Q12(0.0f), false);
            break;

        case 8:
            func_80086C58(&g_SysWork.playerWork.player, 60);
            break;

        default:
            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);
            break;
    }
}

void MapEvent_DoghouseNote(void) // 0x800E95F8
{
    switch (g_SysWork.sysStateSteps[0])
    {
        case 0:
            Player_ControlFreeze();
            func_800862F8(0, FILE_TIM_STKENNEL_TIM, false);
            SysWork_StateStepIncrement(0);

        case 1:
            func_80085DF0();
            break;

        case 2:
            func_80086C58(&g_SysWork.playerWork.player, 59);
            break;

        case 3:
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(0.0f), false);
            break;

        case 4:
            func_800862F8(1, 0, false);
            break;

        case 5:
            func_800862F8(2, 0, false);
            Savegame_EventFlagSet(EventFlag_M2S00_DogHouseNoteFound);
            SysWork_StateStepIncrementAfterFade(2, false, 0, Q12(0.0f), false);
            break;

        case 6:
            func_800862F8(2, 0, false);
            MapMsg_DisplayAndHandleSelection(false, 23, 0, 0, 0, false); // "Doghouse Levin St."
            break;

        case 7:
            func_800862F8(2, 0, false);
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(0.0f), false);
            break;

        case 8:
            SysWork_StateStepIncrementAfterFade(2, false, 0, Q12(0.0f), false);
            break;

        case 9:
            func_80086C58(&g_SysWork.playerWork.player, 60);
            break;

        default:
            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);
            func_80086470(3, InvItemId_NoteDoghouse, 1, false);
            break;
    }
}

void MapEvent_DoghouseKeyTake(void) // 0x800E97E4
{
    typedef enum _EventState
    {
        EventState_Initialize  = 0,

        EventState_Prompt      = 7,
        EventState_TakeKey     = 8,
        EventState_DontTakeKey = 9,

        EventState_Finish      = 12
    } e_EventState;

    // Handle event state.
    switch (g_SysWork.sysStateSteps[0])
    {
        case EventState_Initialize:
            Player_ControlFreeze();
            func_800862F8(0, FILE_TIM_INKENNEL_TIM, false);
            SysWork_StateStepIncrement(0);

        case 1:
            func_80085DF0();
            break;

        case 2:
            func_80086C58(&g_SysWork.playerWork.player, 59);
            break;

        case 3:
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(0.0f), false);
            break;

        case 4:
            func_800862F8(1, 0, false);
            break;

        case 5:
            func_800862F8(2, 0, false);
            SysWork_StateStepIncrementAfterFade(2, false, 0, Q12(0.0f), false);
            break;

        case 6:
            SysWork_StateStepIncrement(0);

        case EventState_Prompt:
            func_800862F8(2, 0, false);
            MapMsg_DisplayAndHandleSelection(true, 27, EventState_TakeKey, EventState_DontTakeKey, 0, false); // "House Key in doghouse. Take it?"
            break;

        case EventState_TakeKey:
            func_80086470(3, InvItemId_HouseKey, 1, false);
            Savegame_EventFlagSet(EventFlag_M2S00_PickupDogHouseKey);
            Player_ItemRemove(InvItemId_NoteDoghouse, 1);
            SysWork_StateStepIncrement(0);

        case EventState_DontTakeKey:
            func_800862F8(2, 0, false);
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(0.0f), false);
            break;

        case 10:
            SysWork_StateStepIncrementAfterFade(2, false, 0, Q12(0.0f), false);
            break;

        case 11:
            func_80086C58(&g_SysWork.playerWork.player, 60);
            break;

        default: // `EventState_Finish`
            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);
            break;
        }
}

void func_800E9A0C(void) // 0x800E9A0C
{
    Event_ItemTake(InvItemId_KeyOfLion, DEFAULT_PICKUP_ITEM_COUNT, EventFlag_M2S00_PickupKeyOfLion, 28);

    if (Savegame_EventFlagGet(EventFlag_M2S00_PickupKeyOfLion))
    {
        if (Savegame_EventFlagGet(EventFlag_MapMark_OldTown_FineyStRightKeyArrow))
        {
            Savegame_EventFlagSet(EventFlag_MapMark_53);
        }
    }
}

void func_800E9A74(void) // 0x800E9A74
{
    typedef enum _EventState
    {
        EventState_Initialize  = 0,
        EventState_1           = 1,
        EventState_2           = 2,
        EventState_3           = 3,
        EventState_4           = 4,
        EventState_Prompt      = 5,
        EventState_TakeKey     = 6,
        EventState_DontTakeKey = 7,
        EventState_8           = 8,
        EventState_Finish      = 9
    } e_EventState;

    // Handle event state.
    switch (g_SysWork.sysStateSteps[0])
    {
        case EventState_Initialize:
            Player_ControlFreeze();
            func_80086470(0, InvItemId_KeyOfWoodman, 0, false);
            SysWork_StateStepIncrement(0);

        case EventState_1:
            func_80085DF0();
            break;

        case EventState_2:
            func_80085EB8(0, &g_SysWork.playerWork.player, 59, false);
            SysWork_StateStepIncrement(0);

        case EventState_3:
            func_80086470(1, InvItemId_KeyOfWoodman, 0, false);
            break;

        case EventState_4:
            func_80085EB8(1, &g_SysWork.playerWork.player, 0, false);
            break;

        case EventState_Prompt:
            if (Gfx_PickupItemAnimate(InvItemId_KeyOfWoodman))
            {
                MapMsg_DisplayAndHandleSelection(true, 29, EventState_TakeKey, EventState_DontTakeKey, 0, false); // "Key of Woodman. Take it?"
            }

            Savegame_EventFlagSet(EventFlag_M2S00_PickupKeyOfWoodman);
            break;

        case EventState_TakeKey:
            func_80086470(3, InvItemId_KeyOfWoodman, 1, false);

            if (Savegame_EventFlagGet(EventFlag_MapMark_OldTown_DogYardKeyLine))
            {
                Savegame_EventFlagSet(EventFlag_MapMark_55);
            }

            SysWork_StateStepSet(0, 8);
            break;

        case EventState_DontTakeKey:
            Savegame_EventFlagClear(EventFlag_M2S00_PickupKeyOfWoodman);
            SysWork_StateStepIncrement(0);

        case EventState_8:
            func_80086C58(&g_SysWork.playerWork.player, 60);
            break;

        default: // `EventState_Finish`
            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);
            break;
        }
}

void func_800E9CB4(void) // 0x800E9CB4
{
    Event_ItemTake(InvItemId_KeyOfScarecrow, DEFAULT_PICKUP_ITEM_COUNT, EventFlag_M2S00_PickupKeyOfScarecrow, 30);

    if (Savegame_EventFlagGet(EventFlag_M2S00_PickupKeyOfScarecrow))
    {
        if (Savegame_EventFlagGet(EventFlag_MapMark_OldTown_EllroyStKeyCircle))
        {
            Savegame_EventFlagSet(EventFlag_MapMark_57);
        }
    }
}

void MapEvent_HouseKeyUse(void) // 0x800E9D1C
{
    VECTOR3 sfxPos = { MAP_POINTS[g_MapEventData->pointOfInterestIdx].positionX, Q12(-1.2f), MAP_POINTS[g_MapEventData->pointOfInterestIdx].positionZ };

    Player_ItemRemove(InvItemId_HouseKey, 1);
    Map_MessageWithSfx(31, Sfx_UseKey, &sfxPos); // "Used the House Key."
    Savegame_EventFlagSet(EventFlag_MapMark_OldTown_DoghouseDotOnly);
}

void func_800E9DD8(void) // 0x800E9DD8
{
    typedef enum _EventState
    {
        EventState_Initialize = 0,
        EventState_UseKey     = 4
    } e_EventState;

    s32  idx;
    s32  tim;
    s32  tim2;
    s32  tmp0;
    s32  locksLeft;
    s16* timPtr;

    // Handle event state.
    switch (g_SysWork.sysStateSteps[0])
    {
        case EventState_Initialize:
            Player_ControlFreeze();
            D_800F22A0 = &g_ItemInspectionImg;
            D_800F22A4 = &D_800A9A04;
            D_800F22A8 = &g_ItemInspectionImg;

            Fs_QueueStartReadTim(g_Gfx_LockTimFileIdxs[(Savegame_EventFlagGet(EventFlag_M2S00_LockOfLionOpen)      ? 4 : 0) +
                                                       (Savegame_EventFlagGet(EventFlag_M2S00_LockOfWoodmanOpen)   ? 2 : 0) +
                                                       (Savegame_EventFlagGet(EventFlag_M2S00_LockOfScarecrowOpen) ? 1 : 0)],
                                 FS_BUFFER_1,
                                 D_800F22A8);

            SysWork_StateStepIncrement(0);

        case 1:
            SysWork_StateStepIncrementAfterFade(2, true, false, false, false);
            break;

        case 2:
            func_800862F8(3, 0, false);
            Fs_QueueWaitForEmpty();
            SysWork_StateStepIncrement(0);

            D_800F22A8 = D_800F22A4;
            break;

        case 3:
            SysWork_StateStepIncrementAfterFade(2, false, false, false, false);
            Screen_BackgroundImgDrawAlt(D_800F22A0);
            break;

        case EventState_UseKey:
            Screen_BackgroundImgDrawAlt(D_800F22A0);

            if (Savegame_EventFlagGet(EventFlag_M2S00_PickupKeyOfLion) && !Savegame_EventFlagGet(EventFlag_M2S00_LockOfLionOpen))
            {
                Savegame_EventFlagSet(EventFlag_M2S00_LockOfLionOpen);
                g_DoorOfEclypse_MapMsgIdx = 32; // "Used the Key of "Lion"."
                Player_ItemRemove(InvItemId_KeyOfLion, 1);
                SysWork_StateStepSet(0, 5);
            }
            else if (Savegame_EventFlagGet(EventFlag_M2S00_PickupKeyOfWoodman) && !Savegame_EventFlagGet(EventFlag_M2S00_LockOfWoodmanOpen))
            {
                Savegame_EventFlagSet(EventFlag_M2S00_LockOfWoodmanOpen);
                g_DoorOfEclypse_MapMsgIdx = 33; // "Used the Key of "Woodman"."

                Player_ItemRemove(InvItemId_KeyOfWoodman, 1);
                SysWork_StateStepSet(0, 5);
            }
            else if (Savegame_EventFlagGet(EventFlag_M2S00_PickupKeyOfScarecrow) && !Savegame_EventFlagGet(EventFlag_M2S00_LockOfScarecrowOpen))
            {
                Savegame_EventFlagSet(EventFlag_M2S00_LockOfScarecrowOpen);
                g_DoorOfEclypse_MapMsgIdx = 34; // "Used the Key of "Scarecrow"."

                Player_ItemRemove(InvItemId_KeyOfScarecrow, 1);
                SysWork_StateStepSet(0, 5);
            }
            else
            {
                // Count locks.
                locksLeft = 3;
                if (Savegame_EventFlagGet(EventFlag_M2S00_LockOfLionOpen))
                {
                    locksLeft = 2;
                }
                if (Savegame_EventFlagGet(EventFlag_M2S00_LockOfWoodmanOpen))
                {
                    locksLeft--;
                }
                if (Savegame_EventFlagGet(EventFlag_M2S00_LockOfScarecrowOpen))
                {
                    locksLeft--;
                }

                // Get remaining locks message index.
                switch (locksLeft)
                {
                    case 0:
                        g_DoorOfEclypse_MapMsgIdx = 13; // "It's unlocked."
                        Savegame_EventFlagSet(EventFlag_M2S00_DoorOfEclypseOpen);
                        Savegame_EventFlagSet(EventFlag_MapMark_OldTown_DoghouseArrowsOnly);
                        break;

                    case 1:
                        g_DoorOfEclypse_MapMsgIdx = 58; // "There is one lock."
                        break;

                    case 2:
                        g_DoorOfEclypse_MapMsgIdx = 57; // "There are two locks."
                        break;

                    case 3:
                        g_DoorOfEclypse_MapMsgIdx = 56; // "There are three locks."
                        break;
                }

                SysWork_StateStepSet(0, 11);
            }
            break;

        case 5:
            MapMsg_DisplayAndHandleSelection(false, g_DoorOfEclypse_MapMsgIdx, 0, 0, 0, false);
            Screen_BackgroundImgDrawAlt(D_800F22A0);
            Sd_PlaySfx(Sfx_Unk1390, 0, 0x80);
            SysWork_StateStepIncrement(0);
            break;

        case 6:
            Fs_QueueStartReadTim(g_Gfx_LockTimFileIdxs[(Savegame_EventFlagGet(EventFlag_M2S00_LockOfLionOpen)      ? 4 : 0) +
                                                       (Savegame_EventFlagGet(EventFlag_M2S00_LockOfWoodmanOpen)   ? 2 : 0) +
                                                       (Savegame_EventFlagGet(EventFlag_M2S00_LockOfScarecrowOpen) ? 1 : 0)],
                                 FS_BUFFER_1,
                                 D_800F22A8);
            SysWork_StateStepIncrement(0);

        case 7:
            Screen_BackgroundImgDrawAlt(D_800F22A0);
            MapMsg_DisplayAndHandleSelection(false, g_DoorOfEclypse_MapMsgIdx, 0, 0, 0, false);
            break;

        case 8:
            Screen_BackgroundImgDrawAlt(D_800F22A0);
            func_800862F8(1, 0, false);
            break;

        case 9:
            Screen_BackgroundImgTransition(D_800F22A0, D_800F22A4, g_SysWork.field_28);

            g_SysWork.field_28 += Q12(1.0f / 32.0f);
            if (g_SysWork.field_28 > Q12(1.0f))
            {
                tmp0 = D_800F22A0;
                D_800F22A8 = tmp0;
                D_800F22A0 = D_800F22A4;
                D_800F22A4 = tmp0;

                SysWork_StateStepIncrement(0);
            }
            break;

        case 10:
            Screen_BackgroundImgDrawAlt(D_800F22A0);
            SysWork_StateStepIncrementDelayed(Q12(1.0f), false);

            if (g_Controller0->btnsClicked_10 & (g_GameWorkPtr->config.controllerConfig.enter |
                                                 g_GameWorkPtr->config.controllerConfig.cancel))
            {
                SysWork_StateStepIncrement(0);
            }

            if (g_SysWork.sysStateSteps[0] != 10)
            {
                SysWork_StateStepSet(0, 4);
            }
            break;

        case 11:
            Screen_BackgroundImgDrawAlt(D_800F22A0);
            MapMsg_DisplayAndHandleSelection(false, g_DoorOfEclypse_MapMsgIdx, 0, 0, 0, false);
            break;

        case 12:
            Screen_BackgroundImgDrawAlt(D_800F22A0);
            SysWork_StateStepIncrementAfterFade(2, true, false, false, false);
            break;

        default:
            func_800862F8(6, 0, false);
            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);
            SysWork_StateStepIncrementAfterFade(0, false, false, false, false);
            break;
        }
}

void MapEvent_DoorOfEclipseEnter(void) // 0x800EA444
{
    s32 tmp;

    switch (g_SysWork.sysStateSteps[0])
    {
        case 0:
            Player_ControlFreeze();
            Gfx_MapInitMapEffectsUpdate(1, 1);
            Gfx_MapEffectsUpdate(6, 6, PrimitiveType_S32, &D_800F1A24, 0, Q12(100.0f));

            g_SysWork.playerWork.player.position.vx = Q12(147.7f);
            g_SysWork.playerWork.player.position.vz = Q12(376.5f);
            g_SysWork.playerWork.player.rotation.vy = Q12(-0.25f);
            g_SysWork.cutsceneBorderState = 20;
            g_SysWork.flags_22A4 |= UnkSysFlag_3;

            SysWork_StateStepIncrementAfterFade(0, false, 0, Q12(0.0f), false);
            SysWork_StateStepIncrement(0);

        case 1:
            g_SysWork.field_28 += g_DeltaTime;
            tmp = Q12(1.0f) - Math_Cos(g_SysWork.field_28/12);
            D_800F1A24 = Q12_MULT_PRECISE(tmp, Q12(60.0f)) + Q12(40.0f);

            if (g_SysWork.field_28 > Q12(1.5f) && g_SysWork.field_28 < Q12(4.5f))
            {
                MapMsg_DisplayAndHandleSelection(false, 35, 0, 0, 0, false); // "What? It's getting dark again?"
            }

            SysWork_StateStepIncrementDelayed(Q12(6.0f), false);
            break;

        case 2:
            D_800F1A24 = Q12(100.0f);

            Game_TurnFlashlightOff();
            SysWork_StateStepIncrementDelayed(Q12(0.2f), false);
            break;

        case 3:
            MapMsg_DisplayAndHandleSelection(false, 36, 0, 0, 0, false);
            break;

        case 4:
            Gfx_MapInitMapEffectsUpdate(6, 3);
            Game_TurnFlashlightOn();
            SysWork_StateStepIncrement(0);

        case 5:
            SysWork_StateStepIncrementDelayed(Q12(1.2f), false);
            break;

        default:
            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);
            SysWork_StateStepIncrementAfterFade(0, false, 2, Q12(0.0f), false);
            Savegame_EventFlagSet(EventFlag_159);

            vcReturnPreAutoCamWork(false);
            break;
    }
}

void func_800EA6E0(void) // 0x800EA6E0
{
    // TODO: Probably inaccurate. Need to figure out what the unknown functions are doing.
    typedef enum _EventState
    {
        EventState_Initialize  = 0,
        EventState_FadeOutGame = 1,
        EventState_Load        = 2, // TODO: Something else?
        EventState_FadeInMap   = 3,
        EventState_Msg         = 4,
        EventState_FadeOutMap  = 5,
        EventState_Finish      = 6
    } e_EventState;

    g_Screen_BackgroundImgGamma = Q8(9.0f / 32.0f);

    switch (g_SysWork.sysStateSteps[0])
    {
        case EventState_Initialize:
            Player_ControlFreeze();
            func_800862F8(0, FILE_TIM_KEYMAP_TIM, false);
            SysWork_StateStepIncrement(0);

        case EventState_FadeOutGame:
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(0.0f), false);
            break;

        case EventState_Load:
            func_800862F8(1, FILE_1ST_2ZANKO80_TIM, false);
            break;

        case EventState_FadeInMap:
            func_800862F8(2, FILE_1ST_2ZANKO80_TIM, false);
            SysWork_StateStepIncrementAfterFade(2, false, 0, Q12(0.0f), false);
            break;

        case EventState_Msg:
            if (Savegame_EventFlagGet(EventFlag_MapMark_OldTown_FineyStRightKeyArrow))
            {
                MapMsg_DisplayAndHandleSelection(false, 54, 0, 0, 0, false); // "Something is written on the map on the wall.{E}"
            }
            else
            {
                MapMsg_DisplayAndHandleSelection(false, 52, 0, 0, 0, false); // "... Copied it to the map."
            }

            func_800862F8(2, FILE_1ST_2ZANKO80_TIM, false);
            break;

        case EventState_FadeOutMap:
            func_800862F8(2, FILE_1ST_2ZANKO80_TIM, false);
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(0.0f), false);
            break;

        default: // `EventState_Finish`
            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);
            SysWork_StateStepIncrementAfterFade(0, false, 0, Q12(0.0f), false);

            Savegame_EventFlagSet(EventFlag_MapMark_OldTown_FineyStRightKeyArrow);
            Savegame_EventFlagSet(EventFlag_MapMark_OldTown_DogYardKeyLine);
            Savegame_EventFlagSet(EventFlag_MapMark_OldTown_EllroyStKeyCircle);
            break;
        }
}

void MapEvent_KGordonKeyUse(void) // 0x800EA894
{
    VECTOR3 sfxPos = {
        MAP_POINTS[g_MapEventData->pointOfInterestIdx].positionX,
        Q12(-1.2f),
        MAP_POINTS[g_MapEventData->pointOfInterestIdx].positionZ
    };

    Player_ItemRemove(InvItemId_KGordonKey, 1);
    Map_MessageWithSfx(39, Sfx_UseKey, &sfxPos); // "Used the K. Gordon key."

    Savegame_EventFlagSet(EventFlag_M2S00_KGordonDoorOpen);
    Savegame_EventFlagSet(EventFlag_MapMark_OldTown_KGordonArrowsOnly);
}

void func_800EA960(void) // 0x800EA960
{
    typedef enum _EventState
    {
        EventState_PressSwitch     = 5,
        EventState_DontPressSwitch = NO_VALUE
    } e_EventState;

    s32 vol;
    s32 balance;
    s16 time;

    switch (g_SysWork.sysStateSteps[0])
    {
        case 0:
            Player_ControlFreeze();
            SysWork_StateStepIncrementAfterFade(0, true, 3, Q12(0.0f), false);
            SysWork_StateStepIncrement(0);

        case 1:
            func_80085DF0();
            break;

        case 2:
            func_8005DC1C(Sfx_Unk1481, &QVECTOR3(-41.576f, -3.619f, 345.992f), Q8(0.5f), 0);
            Savegame_EventFlagSet(EventFlag_164);
            SD_Call(Sfx_Unk1482);

            D_800F534C = NO_VALUE;

            SysWork_StateStepIncrement(0);

        case 3:
            SysWork_StateStepIncrementDelayed(Q12(2.0f), false);
            break;

        case 4:
            g_SysWork.silentYesSelection = true;

            // "The machinery is running. Do you want to press the switch?"
            MapMsg_DisplayAndHandleSelection(true, 44, EventState_PressSwitch, EventState_DontPressSwitch, 0, false);
            break;

        case EventState_PressSwitch:
            func_8005DC1C(Sfx_Unk1483, &QVECTOR3(-41.576f, -3.619f, 345.992f), Q8(0.5f), 0);
            SysWork_StateStepIncrement(0);

        case 6:
            SysWork_StateStepIncrementDelayed(Q12(0.5f), false);
            break;
        case 7:
            SD_Call(Sfx_Unk1484);
            D_800F534E = Q12(0.0f);
            SysWork_StateStepIncrement(0);

        case 8:
            D_800F534E += ((u16)g_DeltaTime * 4);
            if (D_800F534E > Q12(1.0f))
            {
                D_800F534E = Q12(1.0f);
            }

            balance = Vc_StereoBalanceGet(&QVECTOR3(-35.0f, 0.0f, 352.0f));
            if ((Q8_CLAMPED(1.0f) - (D_800F534E >> 4)) >= Q8(0.0f))
            {
                vol = ~(D_800F534E >> 4) & Q8_CLAMPED(1.0f);
            }
            else
            {
                vol = 0;
            }

            Sd_SfxAttributesUpdate(Sfx_Unk1484, balance, vol, 0);

            D_800F5344.vz += Q12_MULT_PRECISE(g_DeltaTime, 0x88);
            if (D_800F5344.vz > 0)
            {
                D_800F5344.vz = 0;

                Sd_SfxStop(Sfx_Unk1484);
                Sd_PlaySfx(Sfx_Unk1485, Vc_StereoBalanceGet(&QVECTOR3(-35.0f, 0.0f, 352.0f)), 0);
                SysWork_StateStepIncrement(0);
            }
            break;

        case 9:
            Savegame_EventFlagSet(EventFlag_165);
            Savegame_EventFlagSet(EventFlag_166);

            if (Savegame_EventFlagGet(EventFlag_MapMark_OldTown_BotBridgeCross))
            {
                Savegame_EventFlagSet(EventFlag_MapMark_OldTown_BotBridgeCorrection);
                Savegame_EventFlagSet(EventFlag_MapMark_OldTown_BotBridgeArrow);
            }

            SysWork_StateStepIncrement(0);

        default:
            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);
            SysWork_StateStepIncrementAfterFade(0, false, 2, Q12(0.0f), false);
            break;
    }

    if (Savegame_EventFlagGet(EventFlag_164))
    {
        if (g_SysWork.sysStateSteps[0] > 4)
        {
            func_800894B8(0x90);
        }
        else
        {
            func_800894B8(0x70);
        }
    }
}

void func_800EAD2C(void) // 0x800EAD2C
{
    typedef enum _EventState
    {
        EventState_PressSwitch     = 3,
        EventState_DontPressSwitch = NO_VALUE
    } e_EventState;

    s32 vol;
    s32 balance;

    switch (g_SysWork.sysStateSteps[0])
    {
        case 0:
            Player_ControlFreeze();
            SysWork_StateStepIncrement(0);

        case 1:
            func_80085DF0();
            break;

        case 2:
            g_SysWork.silentYesSelection = true;

            // "The machinery is running. Do you want to press the switch?"
            MapMsg_DisplayAndHandleSelection(true, 44, EventState_PressSwitch, EventState_DontPressSwitch, 0, false);
            break;

        case EventState_PressSwitch:
            SysWork_StateStepIncrementAfterFade(0, true, 3, Q12(0.0f), false);
            SysWork_StateStepIncrement(0);

        case 4:
            func_8005DC1C(Sfx_Unk1483, &QVECTOR3(-41.576f, -3.619f, 345.992f), Q8(0.5f), 0);
            SysWork_StateStepIncrement(0);

        case 5:
            SysWork_StateStepIncrementDelayed(Q12(0.5f), false);
            break;

        case 6:
            SD_Call(Sfx_Unk1484);
            D_800F534E = Q12(0.0f);
            SysWork_StateStepIncrement(0);

        case 7:
            D_800F534E += g_DeltaTime;
            if (D_800F534E > Q12(1.0f))
            {
                D_800F534E = Q12(1.0f);
            }

            balance = Vc_StereoBalanceGet(&QVECTOR3(-35.0f, 0.0f, 352.0f));
            if ((Q8_CLAMPED(1.0f) - (D_800F534E >> 4)) >= Q8(0.0f))
            {
                vol = ~(D_800F534E >> 4) & Q8_CLAMPED(1.0f);
            }
            else
            {
                vol = 0;
            }

            Sd_SfxAttributesUpdate(Sfx_Unk1484, balance, vol, 0);

            D_800F5344.vz += Q12_MULT_PRECISE(g_DeltaTime, Q12(0.1f / 3.0f));
            if (D_800F5344.vz > 0)
            {
                D_800F5344.vz = 0;
                Sd_SfxStop(Sfx_Unk1484);
                Sd_PlaySfx(Sfx_Unk1485, Vc_StereoBalanceGet(&QVECTOR3(-35.0f, 0.0f, 352.0f)), 0);
                SysWork_StateStepIncrement(0);
            }
            break;

        case 8:
            Savegame_EventFlagSet(EventFlag_165);
            Savegame_EventFlagSet(EventFlag_166);

            if (Savegame_EventFlagGet(EventFlag_MapMark_OldTown_BotBridgeCross))
            {
                Savegame_EventFlagSet(EventFlag_MapMark_OldTown_BotBridgeCorrection);
                Savegame_EventFlagSet(EventFlag_MapMark_OldTown_BotBridgeArrow);
            }

            SysWork_StateStepIncrementAfterFade(0, false, 2, Q12(0.0f), false);
            SysWork_StateStepIncrement(0);

        default:
            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);
            break;
    }

    if (g_SysWork.sysStateSteps[0] > 3)
    {
        func_800894B8(0x90);
    }
    else
    {
        func_800894B8(0x70);
    }
}

void func_800EB090(void) // 0x800EB090
{
    switch (g_SysWork.sysStateSteps[0])
    {
        case 0:
            Player_ControlFreeze();
            SysWork_StateStepIncrement(0);

        case 1:
            func_80085DF0();
            break;

        case 2:
            MapMsg_DisplayAndHandleSelection(false, 61, 0, 0, 0, false); // "Nothing special."
            break;

        default:
            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);
            break;
    }

    func_800894B8(96);
}

void func_800EB174(void) // 0x800EB174
{
    VECTOR3 sfxPos;

    switch (g_SysWork.sysStateSteps[0])
    {
        case 0:
            Player_ControlFreeze();
            sfxPos.vx = MAP_POINTS[g_MapEventData->pointOfInterestIdx].positionX;
            sfxPos.vy = Q12(-1.2f);
            sfxPos.vz = MAP_POINTS[g_MapEventData->pointOfInterestIdx].positionZ;

            func_8005DC1C(Sfx_Unk1349, &sfxPos, Q8(0.5f), 0);
            SysWork_StateStepIncrement(0);

        case 1:
            SysWork_StateStepIncrementDelayed(Q12(0.2f), false);
            break;

        case 2:
            func_80085DF0();
            break;

        case 3:
            MapMsg_DisplayAndHandleSelection(false, MapMsgIdx_DoorLocked, false, false, 0, false);
            break;

        case 4:
            Camera_PositionSet(NULL, Q12(-261.27f), Q12(-2.11f), Q12(-105.46f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);
            Camera_LookAtSet(NULL, Q12(-262.74f), Q12(0.07f), Q12(-102.45f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);

            g_SysWork.playerWork.player.position.vx = Q12(-262.39f);
            g_SysWork.playerWork.player.position.vz = Q12(-104.33f);
            g_SysWork.playerWork.player.rotation.vy = Q12_ANGLE(45.0f);

            func_8003D03C();
            sharedFunc_800D2EB4_0_s00();
            SysWork_StateStepIncrement(0);

        case 5:
            SysWork_StateStepIncrementAfterFade(2, true, 2, false, false);
            break;

        case 6:
            SysWork_StateStepIncrementDelayed(Q12(1.0f), false);
            break;

        case 7:
            MapMsg_DisplayAndHandleSelection(false, 50, false, false, 0, false); // "Hmm... the lock is worn out."
            break;

        case 8:
            SysWork_StateStepIncrementDelayed(Q12(0.5f), false);
            break;

        default:
            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);
            vcReturnPreAutoCamWork(true);
            func_8003D01C();
            sharedFunc_800D2EF4_0_s00();

            Savegame_EventFlagSet(EventFlag_167);
            SysWork_StateStepIncrementAfterFade(0, false, 2, Q12(0.0f), false);
            break;
    }
}

void func_800EB3F4(void) // 0x800EB3F4
{
    const static VECTOR3 D_800CD45C = { Q12(-261.977f), Q12(-0.1f),  Q12(-104.286f) };
    const static VECTOR3 D_800CD468 = { Q12(-263.0f),   Q12(-1.25f), Q12(-104.0f)   };

    switch (g_SysWork.sysStateSteps[0])
    {
        case 0:
            Player_ControlFreeze();
            func_8005DC1C(Sfx_Unk1393, &D_800CD45C, Q8(0.5f), 0);
            SysWork_StateStepIncrement(0);

        case 1:
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(0.0f), false);
            break;

        case 2:
            func_80085DF0();
            break;

        case 3:
            Camera_PositionSet(NULL, Q12(-263.03f), Q12(-3.43f), Q12(-105.37f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);
            Camera_LookAtSet(NULL, Q12(-261.58f), Q12(-0.08f), Q12(-103.73f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);

            D_800F22AE = 0;

            Savegame_EventFlagSet(EventFlag_169);

            g_SysWork.cutsceneBorderState = 20;
            Model_AnimFlagsClear(&g_SysWork.playerWork.player.model, AnimFlag_Visible);
            SysWork_StateStepIncrement(0);

        case 4:
            SysWork_StateStepIncrementAfterFade(2, false, 0, Q12(0.0f), false);
            break;

        case 5:
            SysWork_StateStepIncrementDelayed(Q12(0.8f), false);
            break;

        case 6:
            func_8005DC1C(Sfx_Unk1394, &D_800CD468, Q8(0.5f), 0);
            SysWork_StateStepIncrement(0);

        case 7:
            SysWork_StateStepIncrementDelayed(Q12(2.0f), false);

            // TODO: Odd float values, maybe using different Q format for `s16`?
            D_800F22AE += Q12_MULT_PRECISE(g_DeltaTime, Q12(-0.0277f));
            D_800F22AE  = MAX(Q12(-0.0137f), D_800F22AE);

            D_800F538C.vy += Q12_MULT_PRECISE(g_DeltaTime, D_800F22AE);
            if (D_800F538C.vy < Q12(-0.02222f)) // TODO: `MAX`? Currently doesn't match.
            {
                D_800F538C.vy = Q12(-0.02222f);
            }
            break;

        default:
            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);
            SysWork_StateStepIncrementAfterFade(0, false, 2, Q12(0.0f), false);
            Model_AnimFlagsSet(&g_SysWork.playerWork.player.model, AnimFlag_Visible);

            if (g_SysWork.playerCombat.weaponAttack < WEAPON_ATTACK(EquippedWeaponId_Handgun, AttackInputType_Tap))
            {
                g_SysWork.playerCombat.weaponAttack = WEAPON_ATTACK_ID_GET(g_SysWork.playerCombat.weaponAttack);
            }

            vcReturnPreAutoCamWork(true);
            break;
    }
}

void func_800EB758(void) // 0x800EB758
{
    func_800EB824(0);
    SysWork_StateSetNext(SysState_Gameplay);
}

void func_800EB79C(void) // 0x800EB79C
{
    func_800EB824(1);
    SysWork_StateSetNext(SysState_Gameplay);
}

void func_800EB7E0(void) // 0x800EB7E0
{
    func_800EB824(2);
    SysWork_StateSetNext(SysState_Gameplay);
}

void func_800EB824(s32 arg0) // 0x800EB824
{
    if (arg0 == 0)
    {
        Savegame_EventFlagSet(EventFlag_172);
    }
    else
    {
        Savegame_EventFlagClear(EventFlag_172);
    }

    if (arg0 == 1)
    {
        Savegame_EventFlagSet(EventFlag_173);
    }
    else
    {
        Savegame_EventFlagClear(EventFlag_173);
    }

    if (arg0 == 2)
    {
        Savegame_EventFlagSet(EventFlag_174);
    }
    else
    {
        Savegame_EventFlagClear(EventFlag_174);
    }

    func_800EE5D0();
}

void Map_WorldObjectsInit(void) // 0x800EB908
{
    D_800F534C = 0;

    WorldObjectInit(&g_WorldObject_RockDrill, "DRILL_NE", 236.7151f, -0.281f, 345.046f, 2.8f, 7.5f, -180.5f);
    WorldObjectInit(&g_WorldObject_Chainsaw, "CHAINSAW", -82.3f, -0.7f, -91.6f, -17.0f, 18.1f, -7.22f);
    WorldObjectInit(&g_WorldObject_IronPipe, "IRONPIPE", -187.591f, -0.093f, 300.271f, 4.4f, 36.8f, 2.9f);
    WorldObjectInit(&g_WorldObject1, "SKB2_NEA", -186.68f, -0.483f, 300.829f, 4.1f, -74.05f, -9.5f);
    WorldObjectInit(&g_WorldObject2, "PPR1_NEA", -154.56f, 0.0f, 1.78f, 0.0f, -51.7f, 0.0f);
    WorldObjectInit(&g_WorldObject3, "PPR2_NEA", -154.6f, 0.0f, 2.22f, 0.0f, 74.3f, 0.0f);
    WorldObjectPlacementInit(&g_WorldObjectB[0], "JO0A_HID", 111.94f, -0.81f, 216.25f);
    WorldObjectPlacementInit(&g_WorldObjectB[1], "JO0B_HID", 111.94f, -0.57f, 216.25f);
    WorldObjectPlacementInit(&g_WorldObjectB[2], "JO0C_HID", 111.94f, -0.32f, 216.25f);
    WorldObjectInit(&g_WorldObject4[0], "KEY_HIDE", 185.76f, -0.59f, 116.12f, 0.0f, 0.0f, 0.0f);
    WorldObjectInit(&g_WorldObject4[1], "KEY_NEAR", -190.42f, 0.0f, 376.63f, 0.0f, 58.5f, 0.0f);
    WorldObjectInit(&g_WorldObject4[2], "KEY_NEAR", 99.4f, -0.35f, -33.26f, 1.6f, 0.0f, 0.9f);

    WorldObject_ModelNameSet(&g_WorldObject5[0], "AXIS1_HI");
    WorldObject_ModelNameSet(&g_WorldObject5[1], "AXIS2_BA");
    WorldObject_ModelNameSet(&g_WorldObject5[2], "AXIS1_HI");
    WorldObject_ModelNameSet(&g_WorldObject5[3], "AXIS2_BA");

    Math_Vector3Set(&D_800F55DC[0], Q12(205.0f), Q12(0.0f), Q12(-80.0f));
    Math_Vector3Set(&D_800F55DC[1], Q12(-35.0f), Q12(0.0f), Q12(360.0f));

    Math_SetSVectorFast(&D_800F5344, 0, 0, 0);

    WorldObject_ModelNameSet(&g_WorldObject6[0], "CHAIN1_1");
    WorldObject_ModelNameSet(&g_WorldObject6[1], "CHAIN1_2");
    WorldObject_ModelNameSet(&g_WorldObject6[2], "CHAIN1_3");
    WorldObject_ModelNameSet(&g_WorldObject7[0], "CHAIN2_1");
    WorldObject_ModelNameSet(&g_WorldObject7[1], "CHAIN2_2");
    WorldObject_ModelNameSet(&g_WorldObject7[2], "CHAIN2_3");
    WorldObject_ModelNameSet(&g_WorldObject7[3], "CHAIN2_4");

    Math_Vector3Set(&D_800F56CC[0], Q12(-262.0f), Q12(0.0f), Q12(-104.0f));
    Math_Vector3Set(&D_800F56CC[1], Q12(-263.0f), Q12(0.0f), Q12(-104.0f));

    WorldObject_ModelNameSet(&D_800F535C, "DOOR1_BA");
    Math_Vector3Set(&D_800F537C, Q12(-263.0f), Q12(0.0f), Q12(-104.0f));

    Math_SetSVectorFast(&D_800F538C, 0, 0, 0);
    WorldObject_ModelNameSet(&D_800F56EC, D_800A99E4[1]);

    WorldObjectPoseInit(&D_800F570C, 117.681641f, -1.01f, 216.263f, 0.0f, 193.51f, 0.0f);
    WorldObjectPoseInit(&D_800F572C, 116.3013f, -0.905f, 299.1139f, 0.0f, 84.56f, 0.0f);
    WorldObjectPoseInit(&D_800F574C, -44.234f, -3.453f, 345.2f, 0.0f, 180.0f, 0.0f);

    WorldObjectInit(&g_WorldObject8, "MAP_NEAR", -43.694f, -3.1824f, 345.764f, 6.7f, 6.1f, 0.0f);

    D_800F56E4 = 0;

    if (!Savegame_EventFlagGet(EventFlag_146) ||
        (Savegame_EventFlagGet(EventFlag_193) &&  !Savegame_EventFlagGet(EventFlag_M2S00_WaterWorksCutscene)))
    {
        g_SysWork.flags_22A4 |= UnkSysFlag_4;
    }

    if (Savegame_EventFlagGet(EventFlag_159))
    {
        D_800F1A24 = Q12(100.0f);
    }

    if (!Savegame_EventFlagGet(EventFlag_166))
    {
        D_800F5344.vz = Q12_ANGLE(-49.94f);
    }

    if (Savegame_EventFlagGet(EventFlag_168))
    {
        D_800F538C.vy = Q12_ANGLE(8.0f);
    }

    func_800EE5D0();

    if (Savegame_EventFlagGet(EventFlag_132) && !Savegame_EventFlagGet(EventFlag_M2S00_KGordonDoorOpen))
    {
        // TODO: Should be `~((1 << 8) | (1 << 6) | (1 << 7));`.
        g_SavegamePtr->ovlEnemyStates[10] &= 0xF3FFFEFF;
    }

    if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Easy)
    {
        g_SysWork.npcFlagsId = 2;
    }
    else if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Normal)
    {
        g_SysWork.npcFlagsId = 3;
    }
    else
    {
        g_SysWork.npcFlagsId = 4;
    }

    g_SysWork.npcFlagsId++;
    SysWork_NpcFlagSet(g_SysWork.npcFlagsId - 1);

    WorldObject_ModelNameSet(&g_CommonWorldObjects[0], D_800A99E4[2]);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[1], D_800A99E4[3]);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[2], D_800A99E4[4]);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[3], D_800A99E4[5]);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[4], D_800A99E4[6]);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[5], D_800A99E4[7]);
}

void Map_WorldObjectsUpdate(void) // 0x800EC080
{
    s32 cellX0;
    s32 cellX1;
    s32 cellX2;
    s32 cellZ0;
    s32 cellZ1;
    s32 cellZ2;
    s32 projCellX0;
    s32 projCellX1;
    s32 projCellX2;
    s32 projCellZ0;
    s32 projCellZ1;
    s32 projCellZ2;
    s32 flags;
    MAP_CHUNK_CHECK_VARIABLE_DECL();

    flags = 0;

    cellZ0 = g_SysWork.playerWork.player.position.vz / CHUNK_CELL_SIZE;
    cellX0 = g_SysWork.playerWork.player.position.vx / CHUNK_CELL_SIZE;

    if (g_SysWork.playerWork.player.position.vx > Q12(0.0f))
    {
        projCellX0 = cellX0 + 17;
    }
    else
    {
        projCellX0 = cellX0 + 15;
    }

    if (g_SysWork.playerWork.player.position.vz > Q12(0.0f))
    {
        projCellZ0 = cellZ0 + 17;
    }
    else
    {
        projCellZ0 = cellZ0 + 15;
    }

    switch (CELL_XZ(projCellX0, projCellZ0))
    {
        case CELL_XZ(11, 24):
            if (!Savegame_EventFlagGet(EventFlag_147))
            {
                WorldGfx_ObjectAdd(&g_WorldObject1.object_0, &g_WorldObject1.position, &g_WorldObject1.rotation);
            }

            if (!Savegame_EventFlagGet(EventFlag_M2S00_PickupSteelPipe))
            {
                WorldGfx_ObjectAdd(&g_WorldObject_IronPipe.object_0, &g_WorldObject_IronPipe.position, &g_WorldObject_IronPipe.rotation);
            }
            break;

        case CELL_XZ(12, 17):
        case CELL_XZ(12, 15):
            if (!Savegame_EventFlagGet(EventFlag_M2S00_DogHouseNoteFound))
            {
                WorldGfx_ObjectAdd(&g_WorldObject2.object_0, &g_WorldObject2.position, &g_WorldObject2.rotation);
                WorldGfx_ObjectAdd(&g_WorldObject3.object_0, &g_WorldObject3.position, &g_WorldObject3.rotation);
            }
            break;

        case CELL_XZ(14, 25):
            WorldGfx_ObjectAdd(&g_WorldObject5[2], &D_800F55DC[1], &D_800F5344);
            WorldGfx_ObjectAdd(&g_WorldObject5[3], &D_800F55DC[1], &D_800F5344);

            if (!Savegame_EventFlagGet(EventFlag_M2S00_PickupMap))
            {
                WorldGfx_ObjectAdd(&g_WorldObject8.object_0, &g_WorldObject8.position, &g_WorldObject8.rotation);
            }

            WorldGfx_ObjectAdd(&D_800F56EC, &D_800F574C.position, &D_800F574C.rotation);
            break;

        case CELL_XZ(21, 13):
            if (Savegame_EventFlagGet(EventFlag_163))
            {
                flags |= 1 << 2;
                if (g_SysWork.playerWork.player.position.vx > Q12(198.0f))
                {
                    Savegame_EventFlagClear(EventFlag_163);
                }
            }
            else
            {
                flags |= 1 << 1;
            }

        case CELL_XZ(21, 14):
        case CELL_XZ(22, 14):
        case CELL_XZ(22, 13):
            WorldGfx_ObjectAdd(&g_WorldObject5[0], &D_800F55DC[0], &D_800F5344);
            WorldGfx_ObjectAdd(&g_WorldObject5[1], &D_800F55DC[0], &D_800F5344);

            if (!Savegame_EventFlagGet(EventFlag_166))
            {
                flags |= 1 << 3;
            }

            if (Savegame_EventFlagGet(EventFlag_MapMark_OldTown_BotBridgeCorrection))
            {
                Savegame_EventFlagClear(EventFlag_MapMark_61);
            }
            else
            {
                Savegame_EventFlagSet(EventFlag_MapMark_61);
            }
            break;

        case CELL_XZ(9, 13):
            WorldGfx_ObjectAdd(&D_800F535C, &D_800F537C, &D_800F538C);

            if (!Savegame_EventFlagGet(EventFlag_170))
            {
                // Chain 1.
                if (!Savegame_EventFlagGet(EventFlag_169))
                {
                    WorldGfx_ObjectAdd(&g_WorldObject6[0], &D_800F56CC[0], &(SVECTOR3){ 0, 0, 0 });
                    WorldGfx_ObjectAdd(&g_WorldObject6[1], &D_800F56CC[0], &(SVECTOR3){ 0, 0, 0 });
                    WorldGfx_ObjectAdd(&g_WorldObject6[2], &D_800F56CC[0], &(SVECTOR3){ 0, 0, 0 });
                }
                // Chain 2.
                else
                {
                    WorldGfx_ObjectAdd(&g_WorldObject7[0], &D_800F56CC[1], &D_800F538C);
                    WorldGfx_ObjectAdd(&g_WorldObject7[1], &D_800F56CC[1], &D_800F538C);
                    WorldGfx_ObjectAdd(&g_WorldObject7[2], &D_800F56CC[0], &(SVECTOR3){ 0, 0, 0 });
                    WorldGfx_ObjectAdd(&g_WorldObject7[3], &D_800F56CC[0], &(SVECTOR3){ 0, 0, 0 });
                }
            }
            break;

        case CELL_XZ(19, 22):
        case CELL_XZ(20, 22):
            if (!Savegame_EventFlagGet(EventFlag_M2S00_LockOfLionOpen))
            {
                WorldGfx_ObjectAdd(&g_WorldObjectB->object_0, &g_WorldObjectB->position, &(SVECTOR3){ 0, 0, 0 });
            }

            if (!Savegame_EventFlagGet(EventFlag_M2S00_LockOfWoodmanOpen))
            {
                WorldGfx_ObjectAdd(&g_WorldObjectB[1].object_0, &g_WorldObjectB[1].position, &(SVECTOR3){ 0, 0, 0 });
            }

            if (!Savegame_EventFlagGet(EventFlag_M2S00_LockOfScarecrowOpen))
            {
                WorldGfx_ObjectAdd(&g_WorldObjectB[2].object_0, &g_WorldObjectB[2].position, &(SVECTOR3){ 0, 0, 0 });
            }

            WorldGfx_ObjectAdd(&D_800F56EC, &D_800F570C.position, &D_800F570C.rotation);
            break;

        case CELL_XZ(21, 19):
            if (!Savegame_EventFlagGet(EventFlag_M2S00_PickupKeyOfLion))
            {
                WorldGfx_ObjectAdd(&g_WorldObject4[0].object_0, &g_WorldObject4[0].position, &g_WorldObject4[0].rotation);
            }
            break;

        case CELL_XZ(11, 26):
            if (!Savegame_EventFlagGet(EventFlag_M2S00_PickupKeyOfWoodman))
            {
                WorldGfx_ObjectAdd(&g_WorldObject4[1].object_0, &g_WorldObject4[1].position, &g_WorldObject4[1].rotation);
            }
            break;

        case CELL_XZ(19, 15):
            if (!Savegame_EventFlagGet(EventFlag_M2S00_PickupKeyOfScarecrow))
            {
                WorldGfx_ObjectAdd(&g_WorldObject4[2].object_0, &g_WorldObject4[2].position, &g_WorldObject4[2].rotation);
            }
            break;

        case CELL_XZ(19, 24):
        case CELL_XZ(20, 24):
            WorldGfx_ObjectAdd(&D_800F56EC, &D_800F572C.position, &D_800F572C.rotation);
            break;

        default:
            break;
    }

    cellZ1 = g_SysWork.playerWork.player.position.vz / CHUNK_CELL_SIZE;
    cellX1 = g_SysWork.playerWork.player.position.vx / CHUNK_CELL_SIZE;

    if (g_SysWork.playerWork.player.position.vx > Q12(0.0f))
    {
        projCellX1 = cellX1 + 17;
    }
    else
    {
        projCellX1 = cellX1 + 15;
    }

    if (g_SysWork.playerWork.player.position.vz > Q12(0.0f))
    {
        projCellZ1 = cellZ1 + 17;
    }
    else
    {
        projCellZ1 = cellZ1 + 15;
    }

    switch (CELL_XZ(projCellX1, projCellZ1))
    {
        case CELL_XZ(14, 25):
            if (Savegame_EventFlagGet(EventFlag_164))
            {
                if (D_800F534C == 0)
                {
                    D_800F534C = 1;
                    SD_Call(Sfx_Unk1482);
                    D_800F5350 = Q12(0.75f);
                }
                else if (D_800F534C == NO_VALUE)
                {
                    D_800F5350 += Q12_MULT_PRECISE(g_DeltaTime, Q12(0.25f));
                    if (D_800F5350 > Q12(0.75f))
                    {
                        D_800F5350 = Q12(0.75f);
                        D_800F534C = 1;
                    }
                }

                func_8005DE0C(Sfx_Unk1482, &QVECTOR3(-43.0f, -1.0f, 346.0f), D_800F5350 >> 5, Q12(32.0f), 0);
            }
            break;

        case CELL_XZ(22, 25):
            if (Savegame_EventFlagGet(EventFlag_164))
            {
                if (D_800F534C == 0)
                {
                    D_800F534C++;
                    SD_Call(Sfx_Unk1482);
                }

                func_8005DE0C(Sfx_Unk1482, &QVECTOR3(237.0f, -1.0f, 346.0f), Q8(0.5f), Q12(16.0f), 0);
            }

            if (!Savegame_EventFlagGet(EventFlag_M2S00_PickupRockDrill))
            {
                WorldGfx_ObjectAdd(&g_WorldObject_RockDrill.object_0, &g_WorldObject_RockDrill.position, &g_WorldObject_RockDrill.rotation);
                Savegame_EventFlagSet(EventFlag_66);
            }
            else
            {
                Savegame_EventFlagClear(EventFlag_66);
            }
            break;

        default:
            if (D_800F534C != 0)
            {
                D_800F534C = 0;
                Sd_SfxStop(Sfx_Unk1482);
            }
            break;
    }

    cellZ2 = g_SysWork.playerWork.player.position.vz / CHUNK_CELL_SIZE;
    cellX2 = g_SysWork.playerWork.player.position.vx / CHUNK_CELL_SIZE;

    if (g_SysWork.playerWork.player.position.vx > Q12(0.0f))
    {
        projCellX2 = cellX2 + 17;
    }
    else
    {
        projCellX2 = cellX2 + 15;
    }

    if (g_SysWork.playerWork.player.position.vz > Q12(0.0f))
    {
        projCellZ2 = cellZ2 + 17;
    }
    else
    {
        projCellZ2 = cellZ2 + 15;
    }

    switch (CELL_XZ(projCellX2, projCellZ2))
    {
        case CELL_XZ(22, 25):
            if (D_800F56E4 != 2)
            {
                Gfx_MapInitMapEffectsUpdate(6, 3);
                D_800F56E4 = 2;
                Game_TurnFlashlightOff();
            }
            break;

        case CELL_XZ(19, 22):
        case CELL_XZ(20, 22):
            if (!Savegame_EventFlagGet(EventFlag_134) && Savegame_EventFlagGet(EventFlag_159))
            {
                if (D_800F56E4 != 1)
                {
                    Gfx_MapInitMapEffectsUpdate(6, 3);
                    D_800F56E4 = 1;
                }
            }
            else
            {
                if (D_800F56E4 != 3)
                {
                    Gfx_MapInitMapEffectsUpdate(13, 13);
                    D_800F56E4 = 3;
                }
            }
            break;

        case CELL_XZ(19, 24):
        case CELL_XZ(20, 24):
            if (D_800F56E4 != 3)
            {
                Gfx_MapInitMapEffectsUpdate(13, 13);
                D_800F56E4 = 3;
            }
            break;

        case CELL_XZ(13, 13):
        case CELL_XZ(14, 13):
            if (!Savegame_EventFlagGet(EventFlag_M2S00_PickupChainsaw))
            {
                WorldGfx_ObjectAdd(&g_WorldObject_Chainsaw.object_0, &g_WorldObject_Chainsaw.position, &g_WorldObject_Chainsaw.rotation);
                Savegame_EventFlagSet(EventFlag_65);
            }
            else
            {
                Savegame_EventFlagClear(EventFlag_65);
            }
            break;

        default:
            if (D_800F56E4 != 1)
            {
                if (Savegame_EventFlagGet(EventFlag_134) || !Savegame_EventFlagGet(EventFlag_159))
                {
                    Gfx_MapInitMapEffectsUpdate(1, 1);
                    Game_TurnFlashlightOff();
                }
                else
                {
                    Gfx_MapInitMapEffectsUpdate(6, 3);
                }

                D_800F56E4 = 1;
            }
            break;

    }

    if (Savegame_EventFlagGet(EventFlag_MapMark_OldTown_BradburyStLeftCross) &&
        Savegame_EventFlagGet(EventFlag_MapMark_OldTown_BachmanRdBotCross)   &&
        Savegame_EventFlagGet(EventFlag_MapMark_OldTown_ElroyStBotCross))
    {
        Savegame_EventFlagSet(EventFlag_MapMark_OldTown_BotRightHugeComboCross);
    }

    if (Savegame_EventFlagGet(EventFlag_MapMark_OldTown_BlochStLeftCross)  &&
        Savegame_EventFlagGet(EventFlag_MapMark_OldTown_LevinStTopCross)   &&
        Savegame_EventFlagGet(EventFlag_MapMark_OldTown_BlochStRightCross) &&
        Savegame_EventFlagGet(EventFlag_MapMark_OldTown_LevinStBotCross))
    {
        Savegame_EventFlagSet(EventFlag_MapMark_OldTown_LevinBlochBigCombo);
    }

    func_800EE660();
    func_80069844(CollisionFlag_All);
    Collision_FlagBitsSet(flags);

    if (PLAYER_IN_MAP_CHUNK(vx, 1, -2, -1, -2) && PLAYER_IN_MAP_CHUNK(vz, 1, -1, 0, 0))
    {
        if (!Savegame_EventFlagGet(EventFlag_M2S00_FirstAidKit0))
        {
            WorldGfx_ObjectAdd(&g_CommonWorldObjects[0], &g_CommonWorldObjectPoses[0].position, &g_CommonWorldObjectPoses[0].rotation);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, 2, -1, 2) && PLAYER_IN_MAP_CHUNK(vz, 1, -1, 0, 0))
    {
        if (!Savegame_EventFlagGet(EventFlag_M2S00_HandgunBullets0))
        {
            WorldGfx_ObjectAdd(&g_CommonWorldObjects[3], &g_CommonWorldObjectPoses[1].position, &g_CommonWorldObjectPoses[1].rotation);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, 2, -1, 2) && PLAYER_IN_MAP_CHUNK(vz, 1, -1, 0, 0))
    {
        if (!Savegame_EventFlagGet(EventFlag_M2S00_HandgunBullets1))
        {
            WorldGfx_ObjectAdd(&g_CommonWorldObjects[3], &g_CommonWorldObjectPoses[2].position, &g_CommonWorldObjectPoses[2].rotation);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, 3, -1, 3) && PLAYER_IN_MAP_CHUNK(vz, 1, -1, 0, 0))
    {
        if (!Savegame_EventFlagGet(EventFlag_M2S00_HealthDrink0))
        {
            WorldGfx_ObjectAdd(&g_CommonWorldObjects[1], &g_CommonWorldObjectPoses[3].position, &g_CommonWorldObjectPoses[3].rotation);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, 3, -1, 3) && PLAYER_IN_MAP_CHUNK(vz, 1, -4, -1, -4))
    {
        if (!Savegame_EventFlagGet(EventFlag_M2S00_HandgunBullets2))
        {
            WorldGfx_ObjectAdd(&g_CommonWorldObjects[3], &g_CommonWorldObjectPoses[4].position, &g_CommonWorldObjectPoses[4].rotation);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, 3, -1, 3) && PLAYER_IN_MAP_CHUNK(vz, 1, -4, -1, -4))
    {
        if (!Savegame_EventFlagGet(EventFlag_M2S00_ShotgunShells0))
        {
            WorldGfx_ObjectAdd(&g_CommonWorldObjects[5], &g_CommonWorldObjectPoses[5].position, &g_CommonWorldObjectPoses[5].rotation);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, 3, -1, 3) && PLAYER_IN_MAP_CHUNK(vz, 1, 6, -1, 6))
    {
        if (!Savegame_EventFlagGet(EventFlag_M2S00_HealthDrink1))
        {
            WorldGfx_ObjectAdd(&g_CommonWorldObjects[1], &g_CommonWorldObjectPoses[6].position, &g_CommonWorldObjectPoses[6].rotation);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, 3, -1, 3) && PLAYER_IN_MAP_CHUNK(vz, 1, 6, -1, 6))
    {
        if (!Savegame_EventFlagGet(EventFlag_M2S00_HandgunBullets3))
        {
            WorldGfx_ObjectAdd(&g_CommonWorldObjects[3], &g_CommonWorldObjectPoses[7].position, &g_CommonWorldObjectPoses[7].rotation);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, 3, -1, 3) && PLAYER_IN_MAP_CHUNK(vz, 1, 6, -1, 6))
    {
        if (!Savegame_EventFlagGet(EventFlag_M2S00_HandgunBullets4))
        {
            WorldGfx_ObjectAdd(&g_CommonWorldObjects[3], &g_CommonWorldObjectPoses[8].position, &g_CommonWorldObjectPoses[8].rotation);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, 3, -1, 3) && PLAYER_IN_MAP_CHUNK(vz, 1, 8, -1, 8))
    {
        if (!Savegame_EventFlagGet(EventFlag_M2S00_HandgunBullets5))
        {
            WorldGfx_ObjectAdd(&g_CommonWorldObjects[3], &g_CommonWorldObjectPoses[9].position, &g_CommonWorldObjectPoses[9].rotation);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, 3, -1, 3) && PLAYER_IN_MAP_CHUNK(vz, 1, 8, -1, 8))
    {
        if (!Savegame_EventFlagGet(EventFlag_M2S00_HandgunBullets6))
        {
            WorldGfx_ObjectAdd(&g_CommonWorldObjects[3], &g_CommonWorldObjectPoses[10].position, &g_CommonWorldObjectPoses[10].rotation);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, -7, -1, -7) && PLAYER_IN_MAP_CHUNK(vz, 1, 4, -1, 4))
    {
        if (!Savegame_EventFlagGet(EventFlag_M2S00_HandgunBullets7))
        {
            WorldGfx_ObjectAdd(&g_CommonWorldObjects[3], &g_CommonWorldObjectPoses[11].position, &g_CommonWorldObjectPoses[11].rotation);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, 5, -1, 5) && PLAYER_IN_MAP_CHUNK(vz, 1, 3, -1, 3))
    {
        if (!Savegame_EventFlagGet(EventFlag_M2S00_HandgunBullets8))
        {
            WorldGfx_ObjectAdd(&g_CommonWorldObjects[3], &g_CommonWorldObjectPoses[12].position, &g_CommonWorldObjectPoses[12].rotation);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, -2, -1, -2) && PLAYER_IN_MAP_CHUNK(vz, 1, 9, -1, 9))
    {
        if (!Savegame_EventFlagGet(EventFlag_M2S00_HealthDrink2))
        {
            WorldGfx_ObjectAdd(&g_CommonWorldObjects[1], &g_CommonWorldObjectPoses[13].position, &g_CommonWorldObjectPoses[13].rotation);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, -7, -1, -7) && PLAYER_IN_MAP_CHUNK(vz, 1, 4, -1, 4))
    {
        if (!Savegame_EventFlagGet(EventFlag_M2S00_HealthDrink3))
        {
            WorldGfx_ObjectAdd(&g_CommonWorldObjects[1], &g_CommonWorldObjectPoses[14].position, &g_CommonWorldObjectPoses[14].rotation);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, -5, -1, -5) && PLAYER_IN_MAP_CHUNK(vz, 1, -1, 0, 0))
    {
        if (!Savegame_EventFlagGet(EventFlag_M2S00_HealthDrink4))
        {
            WorldGfx_ObjectAdd(&g_CommonWorldObjects[1], &g_CommonWorldObjectPoses[15].position, &g_CommonWorldObjectPoses[15].rotation);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, -5, -1, -5) && PLAYER_IN_MAP_CHUNK(vz, 1, -2, -1, -2))
    {
        if (!Savegame_EventFlagGet(EventFlag_M2S00_HandgunBullets9))
        {
            WorldGfx_ObjectAdd(&g_CommonWorldObjects[3], &g_CommonWorldObjectPoses[16].position, &g_CommonWorldObjectPoses[16].rotation);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, -2, -1, -2) && PLAYER_IN_MAP_CHUNK(vz, 1, -5, -1, -5))
    {
        if (!Savegame_EventFlagGet(EventFlag_M2S00_HealthDrink5))
        {
            WorldGfx_ObjectAdd(&g_CommonWorldObjects[1], &g_CommonWorldObjectPoses[17].position, &g_CommonWorldObjectPoses[17].rotation);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, -2, -1, -2) && PLAYER_IN_MAP_CHUNK(vz, 1, -4, -1, -4))
    {
        if (!Savegame_EventFlagGet(EventFlag_M2S00_HandgunBullets10))
        {
            WorldGfx_ObjectAdd(&g_CommonWorldObjects[3], &g_CommonWorldObjectPoses[18].position, &g_CommonWorldObjectPoses[18].rotation);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, -3, -1, -3) && PLAYER_IN_MAP_CHUNK(vz, 1, -2, -1, -2))
    {
        if (!Savegame_EventFlagGet(EventFlag_M2S00_HealthDrink6))
        {
            WorldGfx_ObjectAdd(&g_CommonWorldObjects[1], &g_CommonWorldObjectPoses[19].position, &g_CommonWorldObjectPoses[19].rotation);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, -3, -1, -3) && PLAYER_IN_MAP_CHUNK(vz, 1, -4, -1, -4))
    {
        if (!Savegame_EventFlagGet(EventFlag_M2S00_HealthDrink7))
        {
            WorldGfx_ObjectAdd(&g_CommonWorldObjects[1], &g_CommonWorldObjectPoses[20].position, &g_CommonWorldObjectPoses[20].rotation);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, 4, -1, 4) && PLAYER_IN_MAP_CHUNK(vz, 1, 10, -1, 10))
    {
        if (!Savegame_EventFlagGet(EventFlag_M2S00_HealthDrink8))
        {
            WorldGfx_ObjectAdd(&g_CommonWorldObjects[1], &g_CommonWorldObjectPoses[21].position, &g_CommonWorldObjectPoses[21].rotation);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, 4, -1, 4) && PLAYER_IN_MAP_CHUNK(vz, 1, 10, -1, 10))
    {
        if (!Savegame_EventFlagGet(EventFlag_M2S00_HealthDrink9))
        {
            WorldGfx_ObjectAdd(&g_CommonWorldObjects[1], &g_CommonWorldObjectPoses[22].position, &g_CommonWorldObjectPoses[22].rotation);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, -5, -1, -5) && PLAYER_IN_MAP_CHUNK(vz, 1, 10, -1, 10))
    {
        if (!Savegame_EventFlagGet(EventFlag_M2S00_HealthDrink10))
        {
            WorldGfx_ObjectAdd(&g_CommonWorldObjects[1], &g_CommonWorldObjectPoses[23].position, &g_CommonWorldObjectPoses[23].rotation);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 0, 0, -1, 1) && PLAYER_IN_MAP_CHUNK(vz, 0, 0, -1, 1))
    {
        if (!Savegame_EventFlagGet(EventFlag_M2S00_HealthDrink11))
        {
            WorldGfx_ObjectAdd(&g_CommonWorldObjects[1], &g_CommonWorldObjectPoses[24].position, &g_CommonWorldObjectPoses[24].rotation);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, 4, -1, 4) && PLAYER_IN_MAP_CHUNK(vz, 1, -3, -1, -3))
    {
        if (!Savegame_EventFlagGet(EventFlag_M2S00_ShotgunShells1))
        {
            WorldGfx_ObjectAdd(&g_CommonWorldObjects[5], &g_CommonWorldObjectPoses[25].position, &g_CommonWorldObjectPoses[25].rotation);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, 4, -1, 4) && PLAYER_IN_MAP_CHUNK(vz, 1, -3, -1, -3))
    {
        if (!Savegame_EventFlagGet(EventFlag_M2S00_FirstAidKit1))
        {
            WorldGfx_ObjectAdd(&g_CommonWorldObjects[0], &g_CommonWorldObjectPoses[26].position, &g_CommonWorldObjectPoses[26].rotation);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 0, 0, -1, 1) && PLAYER_IN_MAP_CHUNK(vz, 1, 2, -1, 2))
    {
        if (!Savegame_EventFlagGet(EventFlag_M2S00_HandgunBullets11))
        {
            WorldGfx_ObjectAdd(&g_CommonWorldObjects[3], &g_CommonWorldObjectPoses[27].position, &g_CommonWorldObjectPoses[27].rotation);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 0, 0, -1, 1) && PLAYER_IN_MAP_CHUNK(vz, 1, 2, -1, 2))
    {
        if (!Savegame_EventFlagGet(EventFlag_M2S00_HandgunBullets12))
        {
            WorldGfx_ObjectAdd(&g_CommonWorldObjects[3], &g_CommonWorldObjectPoses[28].position, &g_CommonWorldObjectPoses[28].rotation);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, -5, -1, -5) && PLAYER_IN_MAP_CHUNK(vz, 1, 8, -1, 8))
    {
        if (!Savegame_EventFlagGet(EventFlag_M2S00_HandgunBullets13))
        {
            WorldGfx_ObjectAdd(&g_CommonWorldObjects[3], &g_CommonWorldObjectPoses[29].position, &g_CommonWorldObjectPoses[29].rotation);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, -5, -1, -5) && PLAYER_IN_MAP_CHUNK(vz, 1, 8, -1, 8))
    {
        if (!Savegame_EventFlagGet(EventFlag_M2S00_HandgunBullets14))
        {
            WorldGfx_ObjectAdd(&g_CommonWorldObjects[3], &g_CommonWorldObjectPoses[30].position, &g_CommonWorldObjectPoses[30].rotation);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, 4, -1, 4) && PLAYER_IN_MAP_CHUNK(vz, 1, 6, -1, 6))
    {
        if (!Savegame_EventFlagGet(EventFlag_M2S00_FirstAidKit2))
        {
            WorldGfx_ObjectAdd(&g_CommonWorldObjects[0], &g_CommonWorldObjectPoses[31].position, &g_CommonWorldObjectPoses[31].rotation);
        }
    }
}

s32 func_800EE518(void) // 0x800EE518
{
    s32 ret;

    if (!Savegame_EventFlagGet(EventFlag_172))
    {
        if (Savegame_EventFlagGet(EventFlag_173))
        {
            ret = 1;
        }
        else if (Savegame_EventFlagGet(EventFlag_174))
        {
            ret = 2;
        }
        else
        {
            Savegame_EventFlagSet(EventFlag_172);
            ret = 0;
        }
    }
    else
    {
        ret = 0;
    }

    if (Savegame_EventFlagGet(EventFlag_131) && !Savegame_EventFlagGet(EventFlag_181) && ret == 1)
    {
        ret = 2;
    }

    return ret;
}

s32 func_800EE5A8(u32 arg0) // 0x800EE5A8
{
    if (arg0 < 3)
    {
        return D_800F1CA8[arg0];
    }

    return 10;
}

void func_800EE5D0(void) // 0x800EE5D0
{
    s32 idx;

    idx = func_800EE518();
    memcpy(g_MapOverlayHeader.charaSpawns_24C, D_800F1CAC[idx], sizeof(D_800F1CAC[idx]));
    g_SavegamePtr->ovlEnemyStates[10] = g_SavegamePtr->ovlEnemyStates[idx];
}

void func_800EE660(void) // 0x800EE660
{
    s32 val;
    s32 idx;

    idx = func_800EE518();
    val = g_SavegamePtr->ovlEnemyStates[10];
    g_SavegamePtr->ovlEnemyStates[func_800EE5A8(idx)] = val;
}
