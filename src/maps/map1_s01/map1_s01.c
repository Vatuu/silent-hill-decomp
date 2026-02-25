#include "inline_no_dmpsx.h"

#include <psyq/gtemac.h>

#include "bodyprog/bodyprog.h"
#include "bodyprog/item_screens.h"
#include "bodyprog/math/math.h"
#include "bodyprog/player_logic.h"
#include "main/rng.h"
#include "maps/map1/map1_s01.h"
#include "maps/particle.h"
#include "maps/characters/larval_stalker.h"
#include "maps/characters/player.h"
#include "maps/characters/stalker.h"

#include "maps/shared/sharedFunc_800CB7F4_1_s01.h" // 0x800CB7F4

#include "maps/shared/sharedFunc_800CB8A0_1_s01.h" // 0x800CB8A0

#include "maps/shared/sharedFunc_800CBA38_1_s01.h" // 0x800CBA38

#include "maps/shared/sharedFunc_800CBB30_1_s01.h" // 0x800CBB30

#include "../src/maps/particle.c"

#include "../src/maps/characters/player.c"

// TODO: Move this line into separate `Chara_LarvalStalker` split.
#include "../src/maps/characters/larval_stalker.c" // 0x800CE648

// TODO: Move this line into separate `Chara_Stalker` split.
#include "../src/maps/characters/stalker.c" // 0x800D1AF0

void Ai_Cat_Update(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* coords) // 0x800D6D40
{
    s_AnimInfo* animInfo;
    bool        cond;

    if (chara->model_0.controlState_2 == ModelState_Uninitialized)
    {
        chara->model_0.controlState_2                                      = 1;
        chara->model_0.anim_4.status_0                              = ANIM_STATUS(3, true);
        chara->model_0.anim_4.time_4                                = Q12(7.0f);
        chara->model_0.anim_4.alpha_A                               = Q12(0.0f);
        chara->model_0.stateStep_3                                  = 0;
        chara->model_0.anim_4.keyframeIdx_8                         = 7;
        chara->position_18.vy                                       = 0;
        chara->properties_E4.dummy.properties_E8[0].val8[0] = 0;
    }

    if (chara->model_0.stateStep_3 == 0)
    {
        if (chara->model_0.controlState_2 == 2)
        {
            chara->model_0.anim_4.status_0      = ANIM_STATUS(1, true);
            chara->model_0.anim_4.time_4         = Q12(7.0f);
            chara->model_0.anim_4.keyframeIdx_8 = 7;
        }
        else if (chara->model_0.controlState_2 == 3)
        {
            chara->model_0.anim_4.status_0      = ANIM_STATUS(2, true);
            chara->model_0.anim_4.time_4         = Q12(23.0f);
            chara->model_0.anim_4.keyframeIdx_8 = 23;
        }

        chara->model_0.stateStep_3++;
    }

    Math_MatrixTransform(&chara->position_18, &chara->rotation_24, coords);

    animInfo = &CAT_ANIM_INFOS[chara->model_0.anim_4.status_0];
    animInfo->updateFunc_0(&chara->model_0, anmHdr, coords, animInfo);

    cond = false;
    if (chara->model_0.anim_4.status_0 == ANIM_STATUS(1, true))
    {
        if (((u8)chara->properties_E4.dummy.properties_E8[0].val8[0] == 0 &&
             (FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT) - 20) < 3u) ||
            ((u8)chara->properties_E4.dummy.properties_E8[0].val8[0] != 0 &&
             (FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT) - 25) < 3u))
        {
            cond = true;
        }
    }
    else
    {
        if (((u8)chara->properties_E4.dummy.properties_E8[0].val8[0] == 0 &&
             (FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT) - 29) < 3u) ||
            ((u8)chara->properties_E4.dummy.properties_E8[0].val8[0] != 0 &&
             (FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT) - 36) < 3u))
        {
            cond = true;
        }
    }

    if (cond)
    {
        func_8005DD44(1447, &chara->position_18, Q8_CLAMPED(0.5f), Rng_GenerateUInt(-7, 8));
        chara->properties_E4.dummy.properties_E8[0].val8[0] ^= 1;
    }
}

#include "maps/shared/sharedFunc_800D929C_0_s00.h" // 0x800D6F34

#include "maps/shared/Map_RoomIdxGet.h" // 0x800D6F44

void Map_RoomBgmInit(bool arg0) // 0x800D6FE4
{
    u16 flags;

    if (g_SavegamePtr->mapRoomIdx_A5 == 23)
    {
        flags = (1<<5);
        if (Savegame_EventFlagGet(EventFlag_71) && Savegame_EventFlagGet(EventFlag_72))
        {
            flags = 0x1FE;
        }
    }
    else
    {
        flags = D_800DCA04[g_SavegamePtr->mapRoomIdx_A5];
    }

    Bgm_Update(flags, Q12(0.1f), &D_800DC9FC);
}

void Gfx_LoadingScreen_StageString(void) {}

void MapEvent_DoorJammed(void) // 0x800D7058
{
    VECTOR3 sfxPos = { MAP_POINTS[g_MapEventData->pointOfInterestIdx_5].positionX_0, Q12(-1.2f), MAP_POINTS[g_MapEventData->pointOfInterestIdx_5].positionZ_8 };

    Map_MessageWithSfx(MapMsgIdx_DoorJammed, Sfx_DoorJammed, &sfxPos);
}

void MapEvent_DoorLocked(void) // 0x800D70EC
{
    VECTOR3 sfxPos = { MAP_POINTS[g_MapEventData->pointOfInterestIdx_5].positionX_0, Q12(-1.2f), MAP_POINTS[g_MapEventData->pointOfInterestIdx_5].positionZ_8 };

    Map_MessageWithSfx(MapMsgIdx_DoorLocked, Sfx_DoorLocked, &sfxPos);
}

void MapEvent_DoorUnlocked(void) // 0x800D7180
{
    VECTOR3 sfxPos = { MAP_POINTS[g_MapEventData->pointOfInterestIdx_5].positionX_0, Q12(-1.2f), MAP_POINTS[g_MapEventData->pointOfInterestIdx_5].positionZ_8 };

    Map_MessageWithSfx(MapMsgIdx_DoorUnlocked, Sfx_DoorUnlocked, &sfxPos);
}

const char* MAP_MESSAGES[] = {
    #include "maps/shared/mapMsg_common.h"
    "\tStatue_of_an_old_man's_hand.",
    "\tThe_fist_shut_tight, ~N\n\tas_if_never_to_let_go. ~E ",
    "\tThere_is_a_ ~C2 Gold_medallion ~C7 . ~N\n\tTake_it? ~S4 ",
    "\tThere_is_a_ ~C2 Chemical ~C7 . ~N\n\tTake_it? ~S4 ",
    "\tNothing_unusual.~E ",
    "\tJust_the_melted_remains_of ~N\n\ta_statue_of_a_hand. ",
    "\tNothing_to_worry_about. ~E ",
    "\t",
    "~L4 ~M ~C3 [A_Tale_of_Birds_Without_a_Voice] ~N\n\t~N\n\tFirst_flew_the_greedy_Pelican, ~N\n\tEager_for_the_reward, ~N\n\tWhite_wings_flailing. ~N\n\t~N\n\tThen_came_a_silent_Dove, ~N\n\tFlying_beyond_the_Pelican, ~N\n\tAs_far_as_he_could. ",
    "~L4 ~M ~C3 A_Raven_flies_in, ~N\n\tFlying_higher_than_the_Dove, ~N\n\tJust_to_show_that_he_can. ~N\n\t~N\n\tA_Swan_glides_in, ~N\n\tTo_find_a_peaceful_spot, ~N\n\tNext_to_another_bird. ",
    "~L4 ~M ~C3 Finally_out_comes_a_Crow, ~N\n\tComing_quickly_to_a_stop, ~N\n\tYawning_and_then_napping. ~N\n\t~N\n\tWho_will_show_the_way, ~N\n\tWho_will_be_the_key, ~N\n\tWho_will_lead_to ~N\n\tThe_silver_reward. ~E ",
    "\tIt_won't_open._Odd, ~N\n\tdoesn't_look_locked,_though. ~E ",
    "\tThere's_some_blood ~N\n\ton_some_of_the_keys..... ",
    "\tDoes_this_mean_anything? ~E ",
    "\tCheck_the_piano? ~S4 ",
    "\tThere_is_a_ ~C2 Silver_medallion ~C7 . ~N\n\tTake_it? ~S4 ",
    "\tIt's_written_in_blood. ~E ",
    "\tNothing_inside. ~E ",
    "~J0(2.0)\tJust_a_cat... ~E ",
    "\tDistilled_water. ~N\n\tNo_reason_to_take_it. ~E ",
    "\tNothing_useful_on_the_shelf. ~E ",
    "\tNothing_useful ~N\n\tin_the_desk_drawer. ~E ",
    "\tNothing_helpful. ~E ",
    "\tGlucose. ~N\n\tNo_reason_to_take_it. ~E ",
    "\t~C3 Warning._Don't_forget_to ~N\n\ttake_all_of_your_possessions ~N\n\t_after_using_the_lockers. ",
    "\tNormal_elementary_school ~N\n\tbulletin_board. ~N\n\tNothing_in_particular_here. ~E ",
    "\t~C3 ~M NO ~N\n\tRUNNING_OR_PLAYING ~N\n\tIN_THE_LOCKER_ROOM ~E ",
    "\tNothing_useful_in_the_locker. ~E ",
    "\tNothing_useful ~N\n\tin_the_desk_drawer. ~E ",
    "\tNo_useful_books. ~E ",
    "\tNo_special_book_here. ~E ",
    "\tNo_need_to_read ~N\n\tany_of_these_books. ~E ",
    "\tThere's_some_blood ~N\n\ton_some_of_the_keys..... ~E "
};

void func_800D7214(void) // 0x800D7214
{
    u32 pickupType;
    s32 eventFlagIdx;

    pickupType   = CommonPickupItemId_FirstAidKit;
    eventFlagIdx = 0;

    switch (g_MapEventData->pointOfInterestIdx_5)
    {
        case 96:
            pickupType   = CommonPickupItemId_HandgunBullets;
            eventFlagIdx = EventFlag_M1S01_HandgunBullets0;
            break;

        case 97:
            pickupType   = CommonPickupItemId_FirstAidKit;
            eventFlagIdx = EventFlag_M1S01_FirstAidKit;
            break;

        case 98:
            pickupType   = CommonPickupItemId_HealthDrink;
            eventFlagIdx = EventFlag_M1S01_HealthDrink;
            break;

        case 99:
            pickupType   = CommonPickupItemId_HandgunBullets;
            eventFlagIdx = EventFlag_M1S01_HandgunBullets1;
            break;

        case 100:
            pickupType   = CommonPickupItemId_HandgunBullets;
            eventFlagIdx = EventFlag_M1S01_HandgunBullets2;
            break;
    }

    Event_CommonItemTake(pickupType, eventFlagIdx);
}

void func_800D72B0(void) // 0x800D72B0
{
    MapMsg_DisplayWithTexture(FILE_TIM_HAND_TIM, Q12(2.0f), Q12(1.5f), 15);
}

void func_800D72DC(void) // 0x800D72DC
{
    Event_ItemTake(InventoryItemId_Chemical, DEFAULT_PICKUP_ITEM_COUNT, EventFlag_M1S01_PickupChemical, 18);
}

void func_800D7308(void)
{
    typedef enum _EventState
    {
        EventState_Skip = 8
    } e_EventState;

    s32 i;

    g_SysWork.sysFlags_22A0 |= SysFlag_1;

    // Skip.
    if ((g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.skip_4) &&
        g_SysWork.sysStateStep_C[0] > 0 && g_SysWork.sysStateStep_C[0] < EventState_Skip)
    {
        SysWork_StateStepSet(0, EventState_Skip);
    }

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
            SysWork_StateStepIncrementAfterFade(1, true, 2, Q12(0.0f), false);
            break;

        case 3:
            g_SysWork.playerWork_4C.player_0.position_18.vx = Q12(-59.2f);
            g_SysWork.playerWork_4C.player_0.position_18.vz = Q12(98.9f);
            g_SysWork.playerWork_4C.player_0.rotation_24.vy = Q12_ANGLE(0.0f);

            Camera_PositionSet(NULL, Q12(-59.61f), Q12(-0.41f), Q12(97.48f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);
            Camera_LookAtSet(NULL, Q12(-58.6f), Q12(-2.29f), Q12(100.87f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);
            SysWork_StateStepIncrement(0);

        case 4:
            func_80085EB8(0, &g_SysWork.playerWork_4C.player_0, 83, false);
            SysWork_StateStepIncrement(0);

        case 5:
            SysWork_StateStepIncrementDelayed(Q12(2.5f), false);
            break;

        case 6:
            func_8005DC1C(Sfx_Unk1433, &QVECTOR3(-59.2f, -1.0f, 99.5f), Q8_CLAMPED(0.5f), 0);

            sharedData_800DEE50_1_s01.field_0  = 0;
            sharedData_800DEE50_1_s01.field_4  = 0x96;
            sharedData_800DEE50_1_s01.field_A  = 0x2E1;
            sharedData_800DEE50_1_s01.field_6  = Q12(-1.5f);
            sharedData_800DEE50_1_s01.field_8  = Q12(-1.0f);
            sharedData_800DEE50_1_s01.field_C  = Q12(-0.4f);
            sharedData_800DEE50_1_s01.field_E  = 0x51;
            sharedData_800DEE50_1_s01.field_1  = 0x20;
            sharedData_800DEE50_1_s01.field_2  = 0;
            sharedData_800DEE50_1_s01.field_14 = Q12(-59.2f);
            sharedData_800DEE50_1_s01.field_18 = Q12(99.5f);
            sharedData_800DEE50_1_s01.field_1C = Q12(3.0f);
            sharedData_800DEE50_1_s01.field_12 = 0;

            sharedFunc_800CB7F4_1_s01();
            SysWork_StateStepIncrement(0);

        case 7:
            SysWork_StateStepIncrementDelayed(Q12(6.0f), false);
            break;

        case 8:
            Sd_SfxStop(Sfx_Unk1433);
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(0.0f), false);
            break;

        case 9:
            for (i = 0; i < ARRAY_SIZE(sharedData_800DFB7C_0_s00); i++)
            {
                if (sharedData_800DFB7C_0_s00[i].field_A == 13 || sharedData_800DFB7C_0_s00[i].field_A == 14)
                {
                    sharedData_800DFB7C_0_s00[i].field_A = 0;
                }
            }

            SysWork_StateStepIncrement(0);

        default:
            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);
            vcReturnPreAutoCamWork(true);
            SysWork_StateStepIncrementAfterFade(0, false, 2, Q12(0.0f), false);

            if (ScreenFade_IsFinished())
            {
                SysWork_StateStepIncrementAfterFade(0, false, 0, Q12(0.0f), false);
            }

            Savegame_EventFlagSet(EventFlag_74);
            break;
    }
}

void func_800D76F4(void) // 0x800D76F4
{
    #define PICK_UP_MEDALLION_STATE      4
    #define DONT_PICK_UP_MEDALLION_STATE 5

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            Player_ControlFreeze();
            func_80086470(0, InventoryItemId_GoldMedallion, 0, false);

        case 1:
            func_80085DF0();
            break;

        case 2:
            func_80086470(1, InventoryItemId_GoldMedallion, 0, false);
            break;

        case 3:
            if (Gfx_PickupItemAnimate(InventoryItemId_GoldMedallion))
            {
                MapMsg_DisplayAndHandleSelection(true, 17,
                    PICK_UP_MEDALLION_STATE, DONT_PICK_UP_MEDALLION_STATE, 0, false); // Gold medalion. Take it ?
            }

            Savegame_EventFlagSet(EventFlag_M1S01_PickupGoldMedallion);
            break;

        case PICK_UP_MEDALLION_STATE:
            func_80086470(3, InventoryItemId_GoldMedallion, 1, false);

        default:
            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);
            break;

        case DONT_PICK_UP_MEDALLION_STATE:
            Savegame_EventFlagClear(EventFlag_M1S01_PickupGoldMedallion);
            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);
    }
}

void func_800D7830(void) // 0x800D7830
{
    MapMsg_DisplayWithTexture1(FILE_TIM_SCORE_TIM, Q12(2.0f), Q12(1.5f), 31, 23);
}

void func_800D7864(void) // 0x800D7864
{
    // TODO: Mode these to an enum and fill out the rest.
    #define CHECK_PIANO_STATE        5
    #define MEDALLION_CUTSCENE_START 10
    #define SKIP_CUTSCENE_STATE      17
    #define MEDALLION_CUTSCENE_END   19
    #define DONT_CHECK_PIANO_STATE   21

    g_SysWork.sysFlags_22A0 |= SysFlag_1;

    if ((g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.skip_4) &&
        g_SysWork.sysStateStep_C[0] >= MEDALLION_CUTSCENE_START && g_SysWork.sysStateStep_C[0] < MEDALLION_CUTSCENE_END)
    {
        ScreenFade_ResetTimestep();
        SysWork_StateStepSet(0, SKIP_CUTSCENE_STATE);

        g_WorldObject0.rotation_28.vx = Q12_ANGLE(-90.0f);
        g_WorldObject0.position_1C.vx = Q12(-98.8f);
        g_WorldObject0.position_1C.vy = Q12(0.0f);
        g_WorldObject0.position_1C.vz = Q12(22.8f);
        g_WorldObject0.rotation_28.vy = Q12_ANGLE(28.5f);
    }

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            Player_ControlFreeze();
            SysWork_StateStepIncrement(0);

        case 1:
            func_80086DA8(FILE_TIM_PIANO1_TIM, Q12(2.5f));
            break;

        case 2:
            SysWork_StateStepIncrementAfterFade(0, false, 0, Q12(2.0f), false);
            SysWork_StateStepIncrement(0);

        case 3:
            func_800862F8(2, 0, false);
            MapMsg_DisplayAndHandleSelection(false, 27, false, false, 0, false); // "There's some blood on some of the keys."
            break;

        case 4:
            func_800862F8(2, 0, false);
            MapMsg_DisplayAndHandleSelection(true, 29, CHECK_PIANO_STATE, DONT_CHECK_PIANO_STATE, 0, false); // "Check the piano?"
            break;

        case CHECK_PIANO_STATE:
            func_800862F8(2, 0, false);
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(1.5f), false);
            break;

        case 6:
            func_800862F8(7, FILE_TIM_PIANO2_TIM, false);
            break;

        case 7:
            SysWork_StateStepIncrementAfterFade(0, false, 0, Q12(1.5f), false);
            MapEvent_PianoPuzzle(false);
            SysWork_StateStepIncrement(0);

        case 8:
            func_800862F8(2, 0, false);
            MapEvent_PianoPuzzle(true);
            break;

        case 9:
            func_800862F8(2, 0, false);
            func_8008605C(EventFlag_M1S01_PianoPuzzleSolved, MEDALLION_CUTSCENE_START, MEDALLION_CUTSCENE_END, false);
            break;

        case MEDALLION_CUTSCENE_START:
            SysWork_StateStepIncrementAfterFade(0, true, 2, Q12(0.0f), false);
            SysWork_StateStepIncrement(0);

        case 11:
            g_SysWork.playerWork_4C.player_0.position_18.vx = Q12(-100.0f);
            g_SysWork.playerWork_4C.player_0.position_18.vz = Q12(20.1f);
            g_SysWork.playerWork_4C.player_0.rotation_24.vy = Q12_ANGLE(-22.5f);

            SysWork_StateStepIncrementDelayed(Q12(1.5f), false);
            Camera_PositionSet(NULL, Q12(-97.3f), Q12(-2.3699f), Q12(21.97f), 0, 0, 0, 0, true);
            Camera_LookAtSet(NULL, Q12(-100.37f), Q12(-2.2f), Q12(24.53f), 0, 0, 0, 0, true);
            break;

        case 12:
            SysWork_StateStepIncrementDelayed(Q12(0.5f), false);

            g_WorldObject0.rotation_28.vx += Q12_MULT_PRECISE(g_DeltaTime, Q12(0.0555f));
            g_WorldObject0.position_1C.vy = FP_FROM((Math_Cos(g_WorldObject0.rotation_28.vx) * Q12_ANGLE(-43.2f)), Q12_SHIFT) - Q12(2.5601f);
            g_WorldObject0.position_1C.vz = FP_FROM((Math_Sin(g_WorldObject0.rotation_28.vx) * Q12_ANGLE(-43.2f)), Q12_SHIFT) + Q12(23.73f);
            break;

        case 13:
            D_800DD4FC                    += g_GravitySpeed;
            g_WorldObject0.rotation_28.vx += Q12_MULT_PRECISE(g_DeltaTime, Q12(0.75f));
            g_WorldObject0.position_1C.vy += Q12_MULT_PRECISE(g_DeltaTime, D_800DD4FC);
            g_WorldObject0.position_1C.vz += Q12_MULT_PRECISE(g_DeltaTime, Q12(-0.5f));

            if (g_WorldObject0.position_1C.vy >= Q12(0.0f))
            {
                SD_Call(Sfx_Unk1417);
                SysWork_StateStepIncrement(0);
            }
            break;

        case 14:
            SysWork_StateStepIncrementDelayed(Q12(1.0f), false);
            break;

        case 15:
            SysWork_StateStepIncrementDelayed(Q12(2.0f), false);

            g_WorldObject0.position_1C.vx = Q12(-98.8f);
            g_WorldObject0.rotation_28.vx = Q12_ANGLE(-90.0f);
            g_WorldObject0.position_1C.vy = Q12(0.0f);
            g_WorldObject0.position_1C.vz = Q12(22.8f);
            g_WorldObject0.rotation_28.vy = Q12_ANGLE(28.5f);

            Camera_PositionSet(NULL, Q12(-101.39f), Q12(-2.6099f), Q12(22.13f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);
            Camera_LookAtSet(NULL, Q12(-98.4f), Q12(-0.14f), Q12(23.1f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);
            break;

        case SKIP_CUTSCENE_STATE:
            SysWork_StateStepIncrementAfterFade(2, false, 2, Q12(0.0f), false);
            break;

        case 18:
        case 20:
            SysWork_StateStepReset();
            break;

        case MEDALLION_CUTSCENE_END:
        case DONT_CHECK_PIANO_STATE:
            func_800862F8(2, 0, false);

        case 16:
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(2.0f), false);
            break;

        default:
            SysWork_StateStepIncrementAfterFade(0, false, 0, Q12(2.5f), false);
            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);
            vcReturnPreAutoCamWork(true);
            break;
    }
}

void func_800D7EEC(void) // 0x800D7EEC
{
    MapMsg_DisplayWithTexture(FILE_TIM_PIANO1_TIM, Q12(0.0f), Q12(0.0f), 47);
}

void MapEvent_PianoPuzzle(bool playNote) // 0x800D7F18
{
    s16    cursorX;
    s16    cursorY;
    q19_12 curCursorX;
    s32    keyIdx;
    s32    i;

    if (!playNote)
    {
        g_PianoKeyCounter = 0;
        g_PianoCursorY    = 0;
        g_PianoCursorX    = 0;
        D_800DD594        = false;
        return;
    }

    if (g_SysWork.sysStateStep_C[1] & 1)
    {
        if (g_SysWork.sysStateStep_C[1] == 1)
        {
            SysWork_StateStepIncrementDelayed(Q12(0.3f), true);
        }
        if (g_SysWork.sysStateStep_C[1] == 3)
        {
            SysWork_StateStepIncrementDelayed(Q12(0.2f), true);
        }
        if (g_SysWork.sysStateStep_C[1] == 5)
        {
            SysWork_StateStepIncrementDelayed(Q12(0.3f), true);
        }
        return;
    }

    if (g_SysWork.sysStateStep_C[1] == 4)
    {
        SD_Call(Sfx_Unk1421);
        SysWork_StateStepSet(1, 5);
        return;
    }

    g_SysWork.sysStateStep_C[1] = 0;

    if (g_PianoKeyCounter == 5)
    {
        Savegame_EventFlagSet(EventFlag_M1S01_PianoPuzzleSolved);
        SysWork_StateStepIncrement(0);
        return;
    }

    if (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.cancel_2)
    {
        SysWork_StateStepIncrement(0);
        return;
    }

    g_PianoCursorX += (g_Controller0->sticks_24.sticks_0.leftX * 16384) / 75;
    g_PianoCursorX  = CLAMP_RANGE(g_PianoCursorX, Q12(-89.0f), Q12(85.0f));

    g_PianoCursorY += (g_Controller0->sticks_24.sticks_0.leftY * 16384) / 75;
    g_PianoCursorY  = CLAMP_RANGE(g_PianoCursorY, Q12(-71.0f), Q12(84.0f));

    Game_TimerUpdate();

    cursorX = FP_FROM(g_PianoCursorX, Q12_SHIFT) + 8;
    cursorY = FP_FROM(g_PianoCursorY, Q12_SHIFT) + 8;
    Gfx_CursorDraw(cursorX, cursorY, 8, 8, 0, 64, 32, 32, 128, 192, 0, 12);

    if (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.enter_0)
    {
        if (FP_FROM(g_PianoCursorY, Q12_SHIFT) >= 34)
        {
            curCursorX = FP_FROM(g_PianoCursorX, Q12_SHIFT);
            if (curCursorX < -64)
            {
                keyIdx = 0;
            }
            else if (curCursorX < -39)
            {
                keyIdx = 2;
            }
            else if (curCursorX < -14)
            {
                keyIdx = 4;
            }
            else if (curCursorX < 11)
            {
                keyIdx = 5;
            }
            else if (curCursorX < 36)
            {
                keyIdx = 7;
            }
            else if (curCursorX < 61)
            {
                keyIdx = 9;
            }
            else
            {
                keyIdx = ARRAY_SIZE(g_PianoKeys);
            }
        }
        else
        {
            for (i = 0; i < ARRAY_SIZE(g_PianoKeys); i++)
            {
                if (FP_FROM(g_PianoCursorX, Q12_SHIFT) < g_PianoKeys[i])
                {
                    break;
                }
            }

            keyIdx = i;
        }

        switch (keyIdx)
        {
            case 0:
                SysWork_StateStepSet(1, 1);
                SD_Call(Sfx_Unk1438);
                g_PianoCursorX = Q12(-77.0f);
                break;

            case 1:
                SysWork_StateStepSet(1, 3);
                SD_Call(Sfx_Unk1445);
                g_PianoCursorX = Q12(-64.0f);
                break;

            case 2:
                SysWork_StateStepSet(1, 3);
                SD_Call(Sfx_Unk1445);
                g_PianoCursorX = Q12(-52.0f);
                break;

            case 3:
                SysWork_StateStepSet(1, 1);
                SD_Call(Sfx_Unk1439);
                g_PianoCursorX = Q12(-39.0f);
                break;

            case 4:
                SysWork_StateStepSet(1, 1);
                SD_Call(Sfx_Unk1440);
                g_PianoCursorX = Q12(-27.0f);
                break;

            case 5:
                SysWork_StateStepSet(1, 1);
                SD_Call(Sfx_Unk1441);
                g_PianoCursorX = Q12(-2.0f);
                break;

            case 6:
                SysWork_StateStepSet(1, 1);
                SD_Call(Sfx_Unk1442);
                g_PianoCursorX = Q12(8.0f);
                break;

            case 7:
                SysWork_StateStepSet(1, 3);
                SD_Call(Sfx_Unk1445);
                g_PianoCursorX = Q12(23.0f);
                break;

            case 8:
                SysWork_StateStepSet(1, 1);
                SD_Call(Sfx_Unk1443);
                g_PianoCursorX = Q12(36.0f);
                break;

            case 9:
                SysWork_StateStepSet(1, 3);
                SD_Call(Sfx_Unk1445);
                g_PianoCursorX = Q12(48.0f);
                break;

            case 10:
                SysWork_StateStepSet(1, 3);
                SD_Call(Sfx_Unk1445);
                g_PianoCursorX = Q12(64.0f);
                break;

            case 11:
                SysWork_StateStepSet(1, 1);
                SD_Call(Sfx_Unk1444);
                g_PianoCursorX = Q12(73.0f);
                break;
        }

        switch (keyIdx)
        {
            case 0:
            case 3:
            case 4:
            case 5:
            case 6:
            case 8:
            case 11:
                g_PianoKeyCounter = 0;
                return;

            default:
                if (keyIdx == g_PianoKeySequence[0])
                {
                    g_PianoKeyCounter = 1;
                    return;
                }

                if (g_PianoKeySequence[g_PianoKeyCounter] == keyIdx)
                {
                    g_PianoKeyCounter++;
                    return;
                }

                g_PianoKeyCounter = 0;
                break;
        }
    }
}

void func_800D857C(void) // 0x800D857C
{
    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            Player_ControlFreeze();
            func_80086470(0, InventoryItemId_SilverMedallion, 0, false);
            SysWork_StateStepIncrement(0);

        case 1:
            func_80085DF0();
            break;

        case 2:
            func_80085EB8(0, &g_SysWork.playerWork_4C.player_0, 59, false);
            SysWork_StateStepIncrement(0);

        case 3:
            func_80086470(1, InventoryItemId_SilverMedallion, 0, false);
            break;

        case 4:
            func_80085EB8(1, &g_SysWork.playerWork_4C.player_0, 0, false);
            break;

        case 5:
            if (Gfx_PickupItemAnimate(InventoryItemId_SilverMedallion))
            {
                MapMsg_DisplayAndHandleSelection(true, 30, 6, 7, 0, false);
            }

            Savegame_EventFlagSet(EventFlag_M1S01_PickupSilverMedallion);
            break;

        case 6:
            func_80086470(3, InventoryItemId_SilverMedallion, 1, false);
            SysWork_StateStepSet(0, 8);
            break;

        case 7:
            Savegame_EventFlagClear(EventFlag_M1S01_PickupSilverMedallion);
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

void func_800D8794(void) // 0x800D8794
{
    MapMsg_DisplayWithTexture(FILE_TIM_LOCKER0_TIM, Q12(0.0f), Q12(0.0f), 32);
}

extern s32 g_Timer0; // Cutscene timer.
extern u8 D_800DD598;
extern VECTOR3 g_CameraPositionTarget;
extern VECTOR3 g_CameraLookAtTarget;

void func_800D87C0(void) // 0x800D87C0
{
    typedef enum _EventState
    {
        EventState_Skip = 20
    } e_EventState;

    s32                tmp0;
    s_WorldObjectDesc* obj;

    // Skip.
    if ((g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.skip_4) &&
        g_SysWork.sysStateStep_C[0] > 0 && g_SysWork.sysStateStep_C[0] < EventState_Skip)
    {
        if ( g_SysWork.sysStateStep_C[0]  < 4)
        {
            D_800DD598 = 1;
        }

        SysWork_StateStepSet(0, EventState_Skip);
    }

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            Player_ControlFreeze();
            SysWork_StateStepIncrementAfterFade(0, true, 3, Q12(0.0f), false);
            Fs_QueueStartRead(FILE_ANIM_LOCKER_DMS, FS_BUFFER_16);

            D_800DD598 = 0;

            SysWork_StateStepIncrement(0);

        case 1:
            func_80085DF0();
            break;

        case 2:
            if (Fs_QueueDoThingWhenEmpty())
            {
                SysWork_StateStepIncrement(0);
            }

            if (g_SysWork.sysStateStep_C[0] != 2)
            {
                Chara_Load(2, Chara_Cat, g_SysWork.npcCoords_FC0, 4, NULL, NULL);
            }
            break;

        case 3:
            SysWork_StateStepIncrementAfterFade(1, true, 2, Q12(0.0f), false);
            break;

        case 4:
            DmsHeader_FixOffsets((s_DmsHeader* )FS_BUFFER_16);

            g_Timer0 = Q12(0.0f);

            func_80085EB8(0u, &g_SysWork.playerWork_4C.player_0, 85, false);
            func_8003D03C();
            sharedFunc_800D2EB4_0_s00();
            SysWork_StateStepIncrement(0);

        case 5:
            g_Timer0 = MIN((g_Timer0 + Q12_MULT_PRECISE(g_DeltaTime, Q12(12.0f))), Q12(8.0f));
            SysWork_StateStepIncrement(0);

        case 6:
            Chara_ProcessLoads();
            Chara_Spawn(Chara_Cat, 0, Q12(-60.0f), Q12(18.0f), Q12(0.0f), 3);
            SysWork_StateStepIncrement(0);

        case 7:
            g_Timer0 = MIN((g_Timer0 + Q12_MULT_PRECISE(g_DeltaTime, Q12(12.0f))), Q12(8.0f));
            if (g_Timer0 >= Q12(8.0f))
            {
                SysWork_StateStepIncrement(0);
            }
            break;

        case 8:
            g_SysWork.npcs_1A0[0].model_0.stateStep_3 = 0;
            g_SysWork.npcs_1A0[0].model_0.controlState_2++;

            Savegame_EventFlagSet(EventFlag_76);

            func_80085EB8(0u, &g_SysWork.playerWork_4C.player_0, 122, false);
            func_800892DC(18, 96);
            func_8005DC1C(Sfx_Unk1437, &QVECTOR3(-59.0f, -0.5f, 18.6f), Q8_CLAMPED(0.5f), 0);
            func_8005DC1C(Sfx_Unk1436, &QVECTOR3(-58.8f, -1.2f, 18.8f), Q8_CLAMPED(0.5f), 0);
            SysWork_StateStepIncrement(0);

        case 9:
            g_Timer0 = MIN((g_Timer0 + Q12_MULT_PRECISE(g_DeltaTime, Q12(18.0f))), Q12(33.0f));
            if (g_Timer0 >= Q12(33.0f))
            {
                SysWork_StateStepIncrement(0);
            }

            g_Timer0 = MAX(g_Timer0, Q12(16.0f));
            break;

        case 10:
            g_SysWork.npcs_1A0[0].model_0.stateStep_3 = 0;
            g_SysWork.npcs_1A0[0].model_0.controlState_2++;

            SysWork_StateStepIncrement(0);

        case 11:
            g_Timer0 = MIN((Q12_MULT_PRECISE(g_DeltaTime, Q12(21.0f)) + g_Timer0), Q12(48.0f));
            if (g_Timer0 >= Q12(48.0f))
            {
                SysWork_StateStepIncrement(0);
            }

            g_Timer0 = MAX(g_Timer0, Q12(34.0f));
            break;

        case 12:
            MapMsg_DisplayAndHandleSelection(false, 33, 0, 0, 0, false); // "Just a cat..."

            g_Timer0 = MIN((Q12_MULT_PRECISE(g_DeltaTime, Q12(20.0f)) + g_Timer0), Q12(121.0f));
            g_Timer0 = MAX(g_Timer0, Q12(49.0f));
            break;

        case 13:
            g_Timer0 = MIN((Q12_MULT_PRECISE(g_DeltaTime, Q12(20.0f)) + g_Timer0), Q12(121.0f));
            if (g_Timer0 >= Q12(121.0f))
            {
                SysWork_StateStepIncrement(0);
            }

            g_Timer0 = MAX(g_Timer0, Q12(49.0f));
            break;

        case 14:
            func_8005DC1C(Sfx_Unk1448, &QVECTOR3(-56.4f, -0.8f, 16.8f), Q8_CLAMPED(0.5f), 0);
            func_80088F94(&g_SysWork.npcs_1A0[0], 0, 0);
            SysWork_StateStepIncrement(0);

        case 15:
            SysWork_StateStepIncrementDelayed(Q12(1.0f), false);
            break;

        case 16:
            func_8005DC1C(Sfx_Unk1449, &QVECTOR3(-56.4f, -0.8f, 16.8f), Q8_CLAMPED(0.5f), 0);
            SysWork_StateStepIncrement(0);

        case 17:
            SysWork_StateStepIncrementDelayed(Q12(2.0f), false);
            break;

        case 18:
            func_8005DC1C(Sfx_Unk1446, &QVECTOR3(-57.6f, 0.0f, 16.0f), Q8_CLAMPED(0.5f), 0);
            func_8005DC1C(Sfx_Unk1364, &QVECTOR3(-57.6f, 0.0f, 16.0f), Q8_CLAMPED(0.25f), 0);
            SysWork_StateStepIncrement(0);

        case 19:
            SysWork_StateStepIncrementDelayed(Q12(3.0f), false);
            break;

        case 20:
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(0.0f), false);
            break;

        default:
            g_Timer0 = NO_VALUE;
            g_SysWork.playerWork_4C.player_0.position_18.vx += FP_FROM((Math_Sin(g_SysWork.playerWork_4C.player_0.rotation_24.vy + Q12_ANGLE(180.0f)) * Q12(1.1f)), Q12_SHIFT);
            g_SysWork.playerWork_4C.player_0.position_18.vz += FP_FROM((Math_Cos(g_SysWork.playerWork_4C.player_0.rotation_24.vy + Q12_ANGLE(180.0f)) * Q12(1.1f)), Q12_SHIFT);

            vcReturnPreAutoCamWork(true);
            SysWork_StateStepIncrementAfterFade(0, false, 2, Q12(0.0f), false);
            SysWork_StateStepIncrementAfterFade(0, false, 0, Q12(0.0f), false);

            Savegame_EventFlagSet(EventFlag_77);
            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);
            func_80088D34(0);

            Savegame_EventFlagSet(EventFlag_76);
            func_80088F94(&g_SysWork.npcs_1A0[0], 0, 0);
            func_8003D01C();

            if (D_800DD598 == 0)
            {
                sharedFunc_800D2EF4_0_s00();
            }
            break;
    }

    if (g_Timer0 >= Q12(0.0f))
    {
        Dms_CharacterGetPosRot(&g_SysWork.playerWork_4C.player_0.position_18, &g_SysWork.playerWork_4C.player_0.rotation_24, "HERO", g_Timer0, (s_DmsHeader*)FS_BUFFER_16);

        if (g_Timer0 >= Q12(16.0f))
        {
            Dms_CharacterGetPosRot(&g_SysWork.npcs_1A0[0].position_18, &g_SysWork.npcs_1A0[0].rotation_24, "CAT", g_Timer0, (s_DmsHeader*)FS_BUFFER_16);
        }

        vcChangeProjectionValue(Dms_CameraGetTargetPos(&g_CameraPositionTarget, &g_CameraLookAtTarget, NULL, g_Timer0, (s_DmsHeader*)FS_BUFFER_16));
        vcUserCamTarget(&g_CameraPositionTarget, NULL, true);
        vcUserWatchTarget(&g_CameraLookAtTarget, NULL, true);
    }

    if (Savegame_EventFlagGet(EventFlag_76) && !Savegame_EventFlagGet(EventFlag_77))
    {
        obj = &g_WorldObject1;
        tmp0 = MIN((g_Timer0 - Q12(16.0f)), Q12(2.0f));

        obj->rotation_28.vy = Q12_MULT_PRECISE(tmp0, Q12_ANGLE(-4.1f)) - Q12_ANGLE(42.05f);
    }
}

void Map_WorldObjectsInit(void) // 0x800D91EC
{
    WorldObjectInit(&g_WorldObject1, "TOBIRA00", -58.81f, -1.3f, 18.0198f, 0.0f, 0.0f, 0.0f);

    WorldObjectInit(&g_WorldObject2, "TOBIRA01", -58.81f, -1.3f, 18.0198f, 0.0f, 0.0f, 0.0f);

    WorldObjectNoRotInit(&g_WorldObject3, "HAKO_HID", -58.81f, -1.4f, 18.0198f);
    WorldObject_ModelNameSet(&g_WorldObject4, "HAND_HID");
    WorldObject_ModelNameSet(&g_WorldObject5, "HAND2_HI");
    WorldObject_ModelNameSet(&g_WorldObject6, "PANELG_H");

    Math_Vector3Set(&D_800DF080, Q12(-59.2f), Q12(-1.0f), Q12(99.5f));

    WorldObjectNoRotInit(&g_WorldObject7, "ACID_HID", -101.2f, -1.3f, 100.3f);

    WorldObjectNoRotInit(&g_WorldObject8, "FUTA1_HI", -98.2798f, -0.58f, 19.93f);

    WorldObjectNoRotInit(&g_WorldObject9, "FUTA2_HI", -99.44f, -0.85f, 19.93f);

    if (!Savegame_EventFlagGet(EventFlag_M1S01_PianoPuzzleSolved))
    {
        WorldObjectInit(&g_WorldObject0, "SILVER_H", -99.0f, -2.68f, 23.73f, 0.0f, 0.0f, 0.0f);
    }
    else
    {
        WorldObjectInit(&g_WorldObject0, "SILVER_H", -98.8f, 0.0f, 22.8f, -90.0f, 28.5f, 0);
    }

    if (g_SavegamePtr->gameDifficulty_260 == -1)
    {
        func_80088FF4(Chara_GreyChild, 10, 0);
    }
    else if (g_SavegamePtr->gameDifficulty_260 == 1)
    {
        func_80088FF4(Chara_GreyChild, 0, 3);
        func_80088FF4(Chara_GreyChild, 1, 3);
        func_80088FF4(Chara_GreyChild, 2, 3);
    }

    WorldObject_ModelNameSet(&g_CommonWorldObjects[0], D_800A99E4.firstAidKitName_8);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[1], D_800A99E4.healthDrinkName_C);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[2], D_800A99E4.ampouleName_10);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[3], D_800A99E4.handgunBulletsName_14);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[4], D_800A99E4.shotgunShellsName_18);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[5], D_800A99E4.rifleShellsName_1C);
}

void Map_WorldObjectsUpdate(void) // 0x800D9514
{
    MAP_CHUNK_CHECK_VARIABLE_DECL();
    if (PLAYER_IN_MAP_CHUNK(vx, 1, -2, -1, -2) && PLAYER_IN_MAP_CHUNK(vz, 1, 3, -1, 3))
    {
        if (Savegame_EventFlagGet(EventFlag_74))
        {
            if (!Savegame_EventFlagGet(EventFlag_M1S01_PickupGoldMedallion))
            {
                WorldGfx_ObjectAdd(&g_WorldObject6, &D_800DF080, &(SVECTOR3){ 0, 0, 0 });
            }
            WorldGfx_ObjectAdd(&g_WorldObject5, &D_800DF080, &(SVECTOR3){ 0, 0, 0 });
        }
        else
        {
            WorldGfx_ObjectAdd(&g_WorldObject4, &D_800DF080, &(SVECTOR3){ 0, 0, 0 });
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, -3, -1, -3) && PLAYER_IN_MAP_CHUNK(vz, 1, 3, -1, 3))
    {
        if (!Savegame_EventFlagGet(EventFlag_M1S01_PickupChemical))
        {
            WorldGfx_ObjectAdd(&g_WorldObject7.object_0, &g_WorldObject7.position_1C, &(SVECTOR3){ 0, 0, 0 });
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, -2, -1, -2) && PLAYER_IN_MAP_CHUNK(vz, 0, 0, -1, 1))
    {
        func_800D9EC4();
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, -3, -1, -3) && PLAYER_IN_MAP_CHUNK(vz, 0, 0, -1, 1))
    {
        if (Savegame_EventFlagGet(EventFlag_71))
        {
            WorldGfx_ObjectAdd(&g_WorldObject8.object_0, &g_WorldObject8.position_1C, &(SVECTOR3){ 0, 0, 0 });
        }
        else
        {
            WorldGfx_ObjectAdd(&g_WorldObject9.object_0, &g_WorldObject9.position_1C, &(SVECTOR3){ 0, 0, 0 });
        }

        if (!Savegame_EventFlagGet(EventFlag_M1S01_PickupSilverMedallion))
        {
            WorldGfx_ObjectAdd(&g_WorldObject0.object_0, &g_WorldObject0.position_1C, &g_WorldObject0.rotation_28);
        }
    }

    if (!Savegame_EventFlagGet(EventFlag_240))
    {
        if (PLAYER_IN_MAP_CHUNK(vx, 1, -4, -1, -4) && PLAYER_IN_MAP_CHUNK(vz, 1, 2, -1, 2))
        {
            if (g_SysWork.playerWork_4C.player_0.position_18.vx < Q12(-138.5999f))
            {
                if (vcRetCamMvSmoothF() == VC_MV_CHASE)
                {
                    func_8005DC1C(0x5AA, &QVECTOR3(142.6f, -0.4f, 58.8f), Q8_CLAMPED(1.0f), 2);
                    Savegame_EventFlagSet(EventFlag_240);
                }
            }
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, -2, -1, -2) && PLAYER_IN_MAP_CHUNK(vz, 1, 3, -1, 3))
    {
        if (!Savegame_EventFlagGet(EventFlag_M1S01_HandgunBullets0))
        {
            WorldGfx_ObjectAdd(&g_CommonWorldObjects[3], &g_CommonWorldObjectPoses[0].position_0, &g_CommonWorldObjectPoses[0].rotation_C);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, -2, -1, -2) && PLAYER_IN_MAP_CHUNK(vz, 1, 4, -1, 4))
    {

        if (!Savegame_EventFlagGet(EventFlag_M1S01_FirstAidKit))
        {
            WorldGfx_ObjectAdd(&g_CommonWorldObjects[0], &g_CommonWorldObjectPoses[1].position_0, &g_CommonWorldObjectPoses[1].rotation_C);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, -4, -1, -4) && PLAYER_IN_MAP_CHUNK(vz, 1, 4, -1, 4))
    {
        if (!Savegame_EventFlagGet(EventFlag_M1S01_HealthDrink))
        {
            WorldGfx_ObjectAdd(&g_CommonWorldObjects[1], &g_CommonWorldObjectPoses[2].position_0, &g_CommonWorldObjectPoses[2].rotation_C);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, -4, -1, -4) && PLAYER_IN_MAP_CHUNK(vz, 0, 0, -1, 1))
    {
        if (!Savegame_EventFlagGet(EventFlag_M1S01_HandgunBullets1))
        {
            WorldGfx_ObjectAdd(&g_CommonWorldObjects[3], &g_CommonWorldObjectPoses[3].position_0, &g_CommonWorldObjectPoses[3].rotation_C);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, -1, 0, 0) && PLAYER_IN_MAP_CHUNK(vz, 1, 2, -1, 2))
    {
        if (!Savegame_EventFlagGet(EventFlag_M1S01_HandgunBullets2))
        {
            WorldGfx_ObjectAdd(&g_CommonWorldObjects[3], &g_CommonWorldObjectPoses[4].position_0, &g_CommonWorldObjectPoses[4].rotation_C);
        }
    }
}

void func_800D9DDC(void) // 0x800D9DDC
{
    if (g_SavegamePtr->gameDifficulty_260 != GameDifficulty_Hard)
    {
        if (Savegame_EventFlagGet(EventFlag_M1S01_PickupChemical))
        {
            func_80088FF4(Chara_GreyChild, 0, 3);
        }

        if (Savegame_EventFlagGet(EventFlag_M1S01_PickupGoldMedallion))
        {
            func_80088FF4(Chara_GreyChild, 1, 3);

            if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Normal)
            {
                func_80088FF4(Chara_GreyChild, 2, 7);
            }
        }
    }

    if (Savegame_EventFlagGet(EventFlag_77))
    {
        func_80088FF4(Chara_GreyChild, 3, 3);

        if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Easy)
        {
            func_80088FF4(Chara_GreyChild, 7, 0);
        }
    }
}

void func_800D9EC4(void) // 0x800D9EC4
{
    static const VECTOR3 soundPos = VECTOR3(-58.81f, -1.4f, 18.0198f);

    if (!Savegame_EventFlagGet(EventFlag_76))
    {
        if (D_800DD57C == 0)
        {
            if (Rng_GenerateUInt(0, 31) == 0) // 1 in 32 chance.
            {
                D_800DD57C = -Rng_GenerateUInt(2, 9);
            }
        }

        if (D_800DD57C != 0)
        {
            if (ABS(D_800DD57C) == 1)
            {
                g_WorldObject1.rotation_28.vy += D_800DD57C;
            }
            g_WorldObject1.rotation_28.vy += D_800DD57C;

            if (D_800DD57C > 0)
            {
                if (g_WorldObject1.rotation_28.vy > 0)
                {
                    func_8005DC1C(Sfx_Unk1435, &soundPos, Q8_CLAMPED(0.5f), 0);
                    g_WorldObject1.rotation_28.vy = 0;

                    if (D_800DD57C >= 8 && Rng_GenerateUInt(0, 3) == 0) // 1 in 4 chance.
                    {
                        D_800DD57C = 0;
                    }
                    else
                    {
                        D_800DD57C = (Rng_GenerateUInt(0, 3) - D_800DD57C) + 1;
                    }
                    D_800DD57C = MIN(D_800DD57C, 0);
                }
            }
            else if (g_WorldObject1.rotation_28.vy < Q12_ANGLE(-1.8f))
            {
                func_8005DC1C(Sfx_Unk1435, &soundPos, Q8_CLAMPED(0.5f), 0);

                D_800DD57C = ~Rng_GenerateUInt(0, 3) - D_800DD57C;
                D_800DD57C = MAX(D_800DD57C, 1);
            }
        }
    }
    else if (!Savegame_EventFlagGet(EventFlag_77))
    {
        WorldGfx_ObjectAdd(&g_WorldObject3.object_0, &g_WorldObject3.position_1C, &(SVECTOR3){ 0, 0, 0 });
    }
    else
    {
        g_WorldObject1.rotation_28.vy = Q12_ANGLE(-2.9f);
    }

    WorldGfx_ObjectAdd(&g_WorldObject1.object_0, &g_WorldObject1.position_1C, &g_WorldObject1.rotation_28);
    g_WorldObject2.rotation_28.vy = g_WorldObject1.rotation_28.vy;
    WorldGfx_ObjectAdd(&g_WorldObject2.object_0, &g_WorldObject2.position_1C, &g_WorldObject2.rotation_28);
}
