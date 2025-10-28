#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "bodyprog/player_logic.h"
#include "main/rng.h"
#include "maps/shared.h"
#include "maps/map1/map1_s01.h"

INCLUDE_RODATA("asm/maps/map1_s01/nonmatchings/map1_s01", D_800C9578);

INCLUDE_RODATA("asm/maps/map1_s01/nonmatchings/map1_s01", g_MapOverlayHeader);

INCLUDE_ASM("asm/maps/map1_s01/nonmatchings/map1_s01", func_800CB7F4);

INCLUDE_ASM("asm/maps/map1_s01/nonmatchings/map1_s01", func_800CB8A0);

INCLUDE_ASM("asm/maps/map1_s01/nonmatchings/map1_s01", func_800CBA38);

INCLUDE_ASM("asm/maps/map1_s01/nonmatchings/map1_s01", func_800CBB30);

INCLUDE_ASM("asm/maps/map1_s01/nonmatchings/map1_s01", func_800CC3C0);

#include "maps/shared/sharedFunc_800D08B8_0_s00.h" // 0x800CC528

#include "maps/shared/sharedFunc_800D0A60_0_s00.h" // 0x800CC6A8

#include "maps/shared/sharedFunc_800D0B18_0_s00.h" // 0x800CC760

#include "maps/shared/sharedFunc_800D0E04_0_s00.h" // 0x800CC8C4

#include "maps/shared/sharedFunc_800CFFD8_0_s01.h" // 0x800CC8E4

#include "maps/shared/sharedFunc_800D0850_0_s01.h" // 0x800CD15C

#include "maps/shared/sharedFunc_800CDAA8_0_s02.h" // 0x800CD548

#include "maps/shared/sharedFunc_800D1C38_0_s00.h" // 0x800CDBE4

#include "maps/shared/sharedFunc_800D209C_0_s00.h" // 0x800CE034

#include "maps/shared/sharedFunc_800D20D8_0_s00.h" // 0x800CE070

#include "maps/shared/sharedFunc_800D20E4_0_s00.h" // 0x800CE07C

#include "maps/shared/sharedFunc_800D2244_0_s00.h" // 0x800CE1DC

s32 func_800CE3B4()
{
    return 0;
}

#include "maps/shared/sharedFunc_800D2C7C_0_s00.h" // 0x800CE3BC

#include "maps/shared/sharedFunc_800D2D2C_0_s00.h" // 0x800CE46C

#include "maps/shared/sharedFunc_800D2D44_0_s00.h" // 0x800CE484

#include "maps/shared/sharedFunc_800D2D6C_0_s00.h" // 0x800CE4AC

#include "maps/shared/sharedFunc_800D2D84_0_s00.h" // 0x800CE4C4

#include "maps/shared/sharedFunc_800D2DAC_0_s00.h" // 0x800CE4EC

#include "maps/shared/sharedFunc_800D2E50_0_s00.h" // 0x800CE590

#include "maps/shared/sharedFunc_800D2E60_0_s00.h" // 0x800CE5A0

void func_800CE5AC(void) {}

void func_800CE5B4(void) {}

void func_800CE5BC(void) {}

void func_800CE5C4(void) {}

void func_800CE5CC(void) {}

s32 func_800CE5D4()
{
    return 0;
}

void func_800CE5DC(void) {}

#include "maps/shared/sharedFunc_800D2EA4_0_s00.h" // 0x800CE5E4

#include "maps/shared/sharedFunc_800D2EB4_0_s00.h" // 0x800CE5F4

#include "maps/shared/sharedFunc_800D2EF4_0_s00.h" // 0x800CE634

#include "maps/shared/Ai_LarvalStalker_Update.h" // 0x800CE648

INCLUDE_ASM("asm/maps/map1_s01/nonmatchings/map1_s01", sharedFunc_800CF168_1_s00); // 0x800CE760

#include "maps/shared/sharedFunc_800D140C_1_s00.h" // 0x800D0A04

#include "maps/shared/sharedFunc_800D1524_1_s00.h" // 0x800D0B1C

#include "maps/shared/Ai_LarvalStalker_Init.h" // 0x800D0CF4

#include "maps/shared/sharedFunc_800D17BC_1_s00.h" // 0x800D0DB4

INCLUDE_ASM("asm/maps/map1_s01/nonmatchings/map1_s01", sharedFunc_800D1DBC_1_s00); // 0x800D13B4

#include "maps/shared/Ai_Stalker_Update.h" // 0x800D1AF0

#include "maps/shared/Ai_Stalker_Init.h" // 0x800D1C84

INCLUDE_ASM("asm/maps/map1_s01/nonmatchings/map1_s01", sharedFunc_800D3308_0_s00); // 0x800D1EF0

#include "maps/shared/sharedFunc_800D3B44_0_s00.h" // 0x800D272C

void sharedFunc_800D3EF4_0_s00(s_SubCharacter* chara) {} // 0x800D2ADC

INCLUDE_ASM("asm/maps/map1_s01/nonmatchings/map1_s01", sharedFunc_800D4924_0_s00); // 0x800D2AE4

INCLUDE_ASM("asm/maps/map1_s01/nonmatchings/map1_s01", sharedFunc_800D492C_0_s00); // 0x800D36B4

#include "maps/shared/sharedFunc_800D5098_0_s00.h" // 0x800D3E20

INCLUDE_ASM("asm/maps/map1_s01/nonmatchings/map1_s01", sharedFunc_800D54A8_0_s00); // 0x800D4230

#include "maps/shared/sharedFunc_800D5B48_0_s00.h" // 0x800D48D0

INCLUDE_ASM("asm/maps/map1_s01/nonmatchings/map1_s01", sharedFunc_800D5C64_0_s00); // 0x800D49EC

#include "maps/shared/sharedFunc_800D5FCC_0_s00.h" // 0x800D4D54

#include "maps/shared/sharedFunc_800D63D0_0_s00.h" // 0x800D5158

#include "maps/shared/sharedFunc_800D654C_0_s00.h" // 0x800D52D4

#include "maps/shared/sharedFunc_800D6554_0_s00.h" // 0x800D52DC

#include "maps/shared/sharedFunc_800D670C_0_s00.h" // 0x800D5494

#include "maps/shared/sharedFunc_800D67FC_0_s00.h" // 0x800D5584

INCLUDE_ASM("asm/maps/map1_s01/nonmatchings/map1_s01", sharedFunc_800D6970_0_s00); // 0x800D56F8

INCLUDE_ASM("asm/maps/map1_s01/nonmatchings/map1_s01", sharedFunc_800D70C4_0_s00); // 0x800D5E4C

#include "maps/shared/sharedFunc_800D7BE8_0_s00.h" // 0x800D6970

#include "maps/shared/sharedFunc_800D7E04_0_s00.h" // 0x800D6B8C

void Ai_Cat_Update(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* coords) // 0x800D6D40
{
    s_AnimInfo* animInfo;
    bool        cond;

    if (chara->model_0.state_2 == 0)
    {
        chara->model_0.state_2                                      = 1;
        chara->model_0.anim_4.status_0                              = ANIM_STATUS(3, true);
        chara->model_0.anim_4.time_4                                = Q12(7.0f);
        chara->model_0.anim_4.alpha_A                               = Q12(0.0f);
        chara->model_0.stateStep_3                                  = 0;
        chara->model_0.anim_4.keyframeIdx_8                         = 7;
        chara->position_18.vy                                       = 0;
        chara->properties_E4.larvalStalker.properties_E8[0].val8[0] = 0;
    }

    if (chara->model_0.stateStep_3 == 0)
    {
        if (chara->model_0.state_2 == 2)
        {
            chara->model_0.anim_4.status_0      = ANIM_STATUS(1, true);
            chara->model_0.anim_4.time_4         = Q12(7.0f);
            chara->model_0.anim_4.keyframeIdx_8 = 7;
        }
        else if (chara->model_0.state_2 == 3)
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
        if (((u8)chara->properties_E4.larvalStalker.properties_E8[0].val8[0] == 0 &&
             (FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT) - 20) < 3u) ||
            ((u8)chara->properties_E4.larvalStalker.properties_E8[0].val8[0] != 0 &&
             (FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT) - 25) < 3u))
        {
            cond = true;
        }
    }
    else
    {
        if (((u8)chara->properties_E4.larvalStalker.properties_E8[0].val8[0] == 0 &&
             (FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT) - 29) < 3u) ||
            ((u8)chara->properties_E4.larvalStalker.properties_E8[0].val8[0] != 0 &&
             (FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT) - 36) < 3u))
        {
            cond = true;
        }
    }

    if (cond)
    {
        func_8005DD44(1447, &chara->position_18, Q8_CLAMPED(0.5f), Rng_GenerateInt(Rng_Rand16(), -7, 8u));
        chara->properties_E4.larvalStalker.properties_E8[0].val8[0] ^= 1;
    }
}

#include "maps/shared/sharedFunc_800D929C_0_s00.h" // 0x800D6F34

#include "maps/shared/Map_RoomIdxGet.h" // 0x800D6F44

void func_800D6FE4(void) // NOTE: The same function in map1_s00: func_800D77F8
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
    func_80035F4C(flags, Q12(0.1f), &D_800DC9FC);

}

void func_800D7050(void) {
}

void func_800D7058(void)
{
    VECTOR3 vec = { MAP_POINTS[g_MapEventParam->field_5].positionX_0, Q12(-1.2f), MAP_POINTS[g_MapEventParam->field_5].positionZ_8 };

    func_80086FE8(11, Sfx_Unk1334, &vec); // Lock is jammed.
}

void func_800D70EC(void)
{
    VECTOR3 vec = { MAP_POINTS[g_MapEventParam->field_5].positionX_0, Q12(-1.2f), MAP_POINTS[g_MapEventParam->field_5].positionZ_8 };

    func_80086FE8(12, Sfx_Unk1344, &vec); // It's locked.
}

void func_800D7180(void)
{
    VECTOR3 vec = { MAP_POINTS[g_MapEventParam->field_5].positionX_0, Q12(-1.2f), MAP_POINTS[g_MapEventParam->field_5].positionZ_8 };

    func_80086FE8(13, Sfx_Unk1342, &vec); // It's unlocked.
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

    switch (g_MapEventParam->field_5)
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
    func_80087360(FILE_TIM_HAND_TIM, Q12(2.0f), Q12(1.5f), 15);
}

void func_800D72DC(void) // 0x800D72DC
{
    Event_ItemTake(InventoryItemId_Chemical, DEFAULT_PICKUP_ITEM_COUNT, EventFlag_M1S01_PickupChemical, 18);
}

INCLUDE_RODATA("asm/maps/map1_s01/nonmatchings/map1_s01", D_800CB5A4);

INCLUDE_ASM("asm/maps/map1_s01/nonmatchings/map1_s01", func_800D7308);

INCLUDE_ASM("asm/maps/map1_s01/nonmatchings/map1_s01", func_800D76F4);

void func_800D7830(void) // 0x800D7830
{
    func_80087540(FILE_TIM_SCORE_TIM, Q12(2.0f), Q12(1.5f), 31, 23);
}

INCLUDE_ASM("asm/maps/map1_s01/nonmatchings/map1_s01", func_800D7864);

void func_800D7EEC(void) // 0x800D7EEC
{
    func_80087360(FILE_TIM_PIANO1_TIM, Q12(0.0f), Q12(0.0f), 47);
}

INCLUDE_ASM("asm/maps/map1_s01/nonmatchings/map1_s01", func_800D7F18);

void func_800D857C(void) // 0x800D857C
{
    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            sharedFunc_800D20E4_0_s00();
            func_80086470(0, InventoryItemId_SilverMedallion, 0, false);
            SysWork_StateStepIncrement();

        case 1:
            func_80085DF0();
            break;

        case 2:
            func_80085EB8(0, &g_SysWork.player_4C.chara_0, 59, false);
            SysWork_StateStepIncrement();

        case 3:
            func_80086470(1, InventoryItemId_SilverMedallion, 0, false);
            break;

        case 4:
            func_80085EB8(1, &g_SysWork.player_4C.chara_0, 0, false);
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
            SysWork_NextStateStepSet(8);
            break;

        case 7:
            Savegame_EventFlagClear(EventFlag_M1S01_PickupSilverMedallion);
            SysWork_StateStepIncrement();

        case 8:
            func_80086C58(&g_SysWork.player_4C.chara_0, 60);
            break;

        default:
            sharedFunc_800D2244_0_s00(false);
            SysWork_StateSetNext(SysState_Gameplay);
            break;
    }
}

void func_800D8794(void) // 0x800D8794
{
    func_80087360(FILE_TIM_LOCKER0_TIM, Q12(0.0f), Q12(0.0f), 32);
}

extern s32 g_Timer0;
extern u8 D_800DD598;
extern VECTOR3 g_CamPosTarget;
extern VECTOR3 g_CamLookAtTarget;

void func_800D87C0(void)
{
    s32 tmp0;
    s_WorldObjectDesc* obj;
    #define CUTSCENE_SKIP_STATE 0x14

    if (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.skip_4 &&
        g_SysWork.sysStateStep_C[0] > 0 && g_SysWork.sysStateStep_C[0] < CUTSCENE_SKIP_STATE)
    {
        if ( g_SysWork.sysStateStep_C[0]  < 4)
        {
            D_800DD598 = 1;
        }
        SysWork_NextStateStepSet(CUTSCENE_SKIP_STATE);
    }

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            sharedFunc_800D20E4_0_s00();
            func_8008616C(false, true, 3, 0, false);
            Fs_QueueStartRead(FILE_ANIM_LOCKER_DMS, FS_BUFFER_16);
            D_800DD598 = 0;
            SysWork_StateStepIncrement();
            /* fallthrough */
        case 1:
            func_80085DF0();
            break;
        case 2:
            if (Fs_QueueDoThingWhenEmpty())
            {
                SysWork_StateStepIncrement();
            }
            if (g_SysWork.sysStateStep_C[0] != 2) {
                Chara_Load(2, Chara_Cat, g_SysWork.npcCoords_FC0, 4, NULL, NULL);
            }
            break;
        case 3:
            func_8008616C(true, true, 2, 0, false);
            break;
        case 4:
            DmsHeader_FixOffsets((s_DmsHeader* )FS_BUFFER_16);
            g_Timer0 = 0;
            func_80085EB8(0U, &g_SysWork.player_4C.chara_0, 0x55, false);
            func_8003D03C();
            sharedFunc_800D2EB4_0_s00();
            SysWork_StateStepIncrement();
            /* fallthrough */
        case 5:
            g_Timer0 = MIN((g_Timer0 + FP_MULTIPLY_PRECISE(g_DeltaTime0, Q12(12.0f), Q12_SHIFT)), Q12(8.0f));
            SysWork_StateStepIncrement();
            /* fallthrough */
        case 6:
            func_80088D0C();
            Chara_Spawn(Chara_Cat, 0, Q12(-60.0f), Q12(18.0f), Q12(0.0f), 3);
            SysWork_StateStepIncrement();

            /* fallthrough */
        case 7:
            g_Timer0 = MIN((g_Timer0 + FP_MULTIPLY_PRECISE(g_DeltaTime0, Q12(12.0f), Q12_SHIFT)), Q12(8.0f));
            if (g_Timer0 >= Q12(8.0f))
            {
                SysWork_StateStepIncrement();
            }
            break;
        case 8:
            g_SysWork.npcs_1A0[0].model_0.stateStep_3 = 0;
            g_SysWork.npcs_1A0[0].model_0.state_2 += 1;
            g_SavegamePtr->eventFlags_168[2] |= Q12(1.0f);
            func_80085EB8(0U, &g_SysWork.player_4C.chara_0, 0x7A, false);
            func_800892DC(0x12, 0x60);
            func_8005DC1C(Sfx_Unk1437, &QV3(-59.0f, -0.5f, 18.6f), 0x80, 0);
            func_8005DC1C(Sfx_Unk1436, &QV3(-58.8f, -1.2f, 18.8f), 0x80, 0);
            SysWork_StateStepIncrement();
            /* fallthrough */
        case 9:
            g_Timer0 = MIN((g_Timer0 + FP_MULTIPLY_PRECISE(g_DeltaTime0, Q12(18.0f), Q12_SHIFT)), Q12(33.0f));
            if (g_Timer0 >= Q12(33.0f))
            {
                SysWork_StateStepIncrement();
            }
            g_Timer0 = MAX(g_Timer0, Q12(16.0f));
            break;
        case 10:
            g_SysWork.npcs_1A0[0].model_0.stateStep_3 = 0;
            g_SysWork.npcs_1A0[0].model_0.state_2++;
            SysWork_StateStepIncrement();
            /* fallthrough */
        case 11:
            g_Timer0 = MIN((FP_MULTIPLY_PRECISE(g_DeltaTime0, Q12(21.0f), Q12_SHIFT) + g_Timer0), Q12(48.0f));
            if (g_Timer0 >= Q12(48.0f))
            {
                SysWork_StateStepIncrement();
            }
            g_Timer0 = MAX(g_Timer0, Q12(34.0f));
            break;
        case 12:
            MapMsg_DisplayAndHandleSelection(false, 33, 0, 0, 0, false); // Just a cat...
            g_Timer0 = MIN((FP_MULTIPLY_PRECISE(g_DeltaTime0, Q12(20.0f), Q12_SHIFT) + g_Timer0), Q12(121.0f));
            g_Timer0 = MAX(g_Timer0, Q12(49.0f));
            break;
        case 13:
            g_Timer0 = MIN((FP_MULTIPLY_PRECISE(g_DeltaTime0, Q12(20.0f), Q12_SHIFT) + g_Timer0), Q12(121.0f));
            if (g_Timer0 >= Q12(121.0f))
            {
                SysWork_StateStepIncrement();
            }
            g_Timer0 = MAX(g_Timer0, Q12(49.0f));
            break;
        case 14:
            func_8005DC1C(Sfx_Unk1448, &QV3(-56.4f, -0.8f, 16.8f) , 0x80, 0);
            func_80088F94(&g_SysWork.npcs_1A0[0], 0, 0);
            SysWork_StateStepIncrement();
            /* fallthrough */
        case 15:
            func_80085E6C(Q12(1.0f), false);
            break;
        case 16:
            func_8005DC1C(Sfx_Unk1449, &QV3(-56.4f, -0.8f, 16.8f) , 0x80, 0);
            SysWork_StateStepIncrement();
            /* fallthrough */
        case 17:
            func_80085E6C(Q12(2.0f), false);
            break;
        case 18:
            func_8005DC1C(Sfx_Unk1446, &QV3(-57.6f, 0.0f, 16.0f), 0x80, 0);
            func_8005DC1C(Sfx_Unk1364, &QV3(-57.6f, 0.0f, 16.0f), 0x40, 0);
            SysWork_StateStepIncrement();
            /* fallthrough */
        case 19:
            func_80085E6C(Q12(3.0f), false);
            break;
        case 20:
            func_8008616C(2, true, 0, 0, false);
            break;
        default:
            g_Timer0 = -1;
            g_SysWork.player_4C.chara_0.position_18.vx += FP_FROM((
                Math_Sin(g_SysWork.player_4C.chara_0.rotation_24.vy + FP_ANGLE(180.0f)) * Q12(1.1f)), Q12_SHIFT);
            g_SysWork.player_4C.chara_0.position_18.vz += FP_FROM((
                Math_Cos(g_SysWork.player_4C.chara_0.rotation_24.vy + FP_ANGLE(180.0f)) * Q12(1.1f)), Q12_SHIFT);
            vcReturnPreAutoCamWork(true);
            func_8008616C(false, false, 2, 0, false);
            func_8008616C(false, false, 0, 0, false);
            Savegame_EventFlagSet(EventFlag_77);
            sharedFunc_800D2244_0_s00(false);
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
    if (g_Timer0 >= 0)
    {
        Dms_CharacterGetPosRot(&g_SysWork.player_4C.chara_0.position_18, &g_SysWork.player_4C.chara_0.rotation_24, "HERO", g_Timer0, (s_DmsHeader*)FS_BUFFER_16);
        if (g_Timer0 >= Q12(16.0f))
        {
            Dms_CharacterGetPosRot(&g_SysWork.npcs_1A0[0].position_18, &g_SysWork.npcs_1A0[0].rotation_24, "CAT", g_Timer0, (s_DmsHeader*)FS_BUFFER_16);
        }
        vcChangeProjectionValue(Dms_CameraGetTargetPos(&g_CamPosTarget, &g_CamLookAtTarget, NULL, g_Timer0, (s_DmsHeader*)FS_BUFFER_16));
        vcUserCamTarget(&g_CamPosTarget, NULL, true);
        vcUserWatchTarget(&g_CamLookAtTarget, NULL, true);
    }

    if (Savegame_EventFlagGet(EventFlag_76) && !Savegame_EventFlagGet(EventFlag_77))
    {
        obj = &g_WorldObj1;
        tmp0 = MIN((g_Timer0 - Q12(16.0f)), Q12(2.0f));

        obj->position_1C.rotation_C.vy = FP_MULTIPLY_PRECISE(tmp0, FP_ANGLE(-4.1f), Q12_SHIFT) - FP_ANGLE(42.05f);
    }
}

void func_800D91EC(void)
{
    WorldObjectPositionInit(&g_WorldObj1.position_1C, -58.81f, -1.3f, 18.0198f, 0.0f, 0.0f, 0.0f);
    WorldObject_ModelNameSet(&g_WorldObj1.object_0, "TOBIRA00");

    WorldObjectPositionInit(&g_WorldObj2.position_1C, -58.81f, -1.3f, 18.0198f, 0.0f, 0.0f, 0.0f);
    WorldObject_ModelNameSet(&g_WorldObj2.object_0, "TOBIRA01");

    Math_Vector3Set(&g_WorldObj3.position_1C.position_0, Q12(-58.81f), -0x1666, Q12(18.0198f));
    WorldObject_ModelNameSet(&g_WorldObj3.object_0, "HAKO_HID");
    WorldObject_ModelNameSet(&g_WorldObj4, "HAND_HID");
    WorldObject_ModelNameSet(&g_WorldObj5, "HAND2_HI");
    WorldObject_ModelNameSet(&g_WorldObj6, "PANELG_H");

    Math_Vector3Set(&D_800DF080, Q12(-59.2f), Q12(-1.0f), Q12(99.5f));

    Math_Vector3Set(&g_WorldObj7.position_1C.position_0, Q12(-101.2f), Q12(-1.3f), Q12(100.3f));
    WorldObject_ModelNameSet(&g_WorldObj7.object_0, "ACID_HID");

    Math_Vector3Set(&g_WorldObj8.position_1C.position_0, Q12(-98.2798f), Q12(-0.58f), Q12(19.93f));
    WorldObject_ModelNameSet(&g_WorldObj8.object_0, "FUTA1_HI");

    Math_Vector3Set(&g_WorldObj9.position_1C.position_0, Q12(-99.44f), Q12(-0.85f), Q12(19.93f));
    WorldObject_ModelNameSet(&g_WorldObj9.object_0, "FUTA2_HI");

    if (!Savegame_EventFlagGet(EventFlag_75))
    {
        WorldObjectPositionInit(&g_WorldObj0.position_1C, -99.0f, -2.68f, 23.73f, 0.0f, 0.0f, 0.0f);
        WorldObject_ModelNameSet(&g_WorldObj0.object_0, "SILVER_H");
    }
    else
    {
        WorldObjectPositionInit(&g_WorldObj0.position_1C, -98.8f, 0.0f, 22.8f, -90.0f, 28.5f, 0);
        WorldObject_ModelNameSet(&g_WorldObj0.object_0, "SILVER_H");
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

void func_800D9514(void)
{
    MAP_CHUNK_CHECK_VARIABLE_DECL();
    if (PLAYER_IN_MAP_CHUNK(vx, 1, -2, -1, -2) && PLAYER_IN_MAP_CHUNK(vz, 1, 3, -1, 3))
    {
        if (Savegame_EventFlagGet(EventFlag_74))
        {
            if (!Savegame_EventFlagGet(EventFlag_69))
            {
                g_WorldGfx_ObjectAdd(&g_WorldObj6, &D_800DF080, &(SVECTOR3){});
            } 
            g_WorldGfx_ObjectAdd(&g_WorldObj5, &D_800DF080, &(SVECTOR3){});
        }
        else
        {
            g_WorldGfx_ObjectAdd(&g_WorldObj4, &D_800DF080, &(SVECTOR3){});
        }
    }
    if (PLAYER_IN_MAP_CHUNK(vx, 1, -3, -1, -3) && PLAYER_IN_MAP_CHUNK(vz, 1, 3, -1, 3))
    {
        if (!(g_SavegamePtr->eventFlags_168[2] & 0x10))
        {
            g_WorldGfx_ObjectAdd(&g_WorldObj7.object_0, &g_WorldObj7.position_1C.position_0, &(SVECTOR3){});
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
            g_WorldGfx_ObjectAdd(&g_WorldObj8.object_0, &g_WorldObj8.position_1C.position_0, &(SVECTOR3){});
        }
        else
        {
            g_WorldGfx_ObjectAdd(&g_WorldObj9.object_0, &g_WorldObj9.position_1C.position_0, &(SVECTOR3){});
        }
        if (!Savegame_EventFlagGet(EventFlag_M1S01_PickupSilverMedallion))
        {
            g_WorldGfx_ObjectAdd(&g_WorldObj0.object_0, &g_WorldObj0.position_1C.position_0, &g_WorldObj0.position_1C.rotation_C);
        }
    }

    if (!Savegame_EventFlagGet(EventFlag_240))
    {
        if (PLAYER_IN_MAP_CHUNK(vx, 1, -4, -1, -4) && PLAYER_IN_MAP_CHUNK(vz, 1, 2, -1, 2))
        {
            if (g_SysWork.player_4C.chara_0.position_18.vx < Q12(-138.5999f))
            {
                if (vcRetCamMvSmoothF() == 0)
                {
                    func_8005DC1C(0x5AA, &QV3(142.6f, -0.4f, 58.8f), 0xFF, 2);
                    Savegame_EventFlagSet(EventFlag_240);
                }
            }
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, -2, -1, -2) && PLAYER_IN_MAP_CHUNK(vz, 1, 3, -1, 3))
    {
        if (!Savegame_EventFlagGet(EventFlag_M1S01_HandgunBullets0))
        {
            g_WorldGfx_ObjectAdd(&g_CommonWorldObjects[3], &g_CommonWorldObjectsPos[0].position_0, &g_CommonWorldObjectsPos[0].rotation_C);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, -2, -1, -2) && PLAYER_IN_MAP_CHUNK(vz, 1, 4, -1, 4))
    {

        if (!Savegame_EventFlagGet(EventFlag_M1S01_FirstAidKit))
        {
            g_WorldGfx_ObjectAdd(&g_CommonWorldObjects[0], &g_CommonWorldObjectsPos[1].position_0, &g_CommonWorldObjectsPos[1].rotation_C);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, -4, -1, -4) && PLAYER_IN_MAP_CHUNK(vz, 1, 4, -1, 4))
    {
        if (!Savegame_EventFlagGet(EventFlag_M1S01_HealthDrink))
        {
            g_WorldGfx_ObjectAdd(&g_CommonWorldObjects[1], &g_CommonWorldObjectsPos[2].position_0, &g_CommonWorldObjectsPos[2].rotation_C);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, -4, -1, -4) && PLAYER_IN_MAP_CHUNK(vz, 0, 0, -1, 1))
    {
        if (!Savegame_EventFlagGet(EventFlag_M1S01_HandgunBullets1))
        {
            g_WorldGfx_ObjectAdd(&g_CommonWorldObjects[3], &g_CommonWorldObjectsPos[3].position_0, &g_CommonWorldObjectsPos[3].rotation_C);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, -1, 0, 0) && PLAYER_IN_MAP_CHUNK(vz, 1, 2, -1, 2))
    {
        if (!Savegame_EventFlagGet(EventFlag_M1S01_HandgunBullets2))
        {
            g_WorldGfx_ObjectAdd(&g_CommonWorldObjects[3], &g_CommonWorldObjectsPos[4].position_0, &g_CommonWorldObjectsPos[4].rotation_C);
        }
    }
}

void func_800D9DDC(void)
{
    if (g_SavegamePtr->gameDifficulty_260 != 1)
    {
        if (Savegame_EventFlagGet(EventFlag_M1S01_PickupChemical))
        {
            func_80088FF4(Chara_GreyChild, 0, 3);
        }
        if (Savegame_EventFlagGet(EventFlag_69))
        {
            func_80088FF4(Chara_GreyChild, 1, 3);
            if (g_SavegamePtr->gameDifficulty_260 == 0)
            {
                func_80088FF4(Chara_GreyChild, 2, 7);
            }
        }
    }

    if (Savegame_EventFlagGet(EventFlag_77))
    {
        func_80088FF4(Chara_GreyChild, 3, 3);
        if (g_SavegamePtr->gameDifficulty_260 == -1)
        {
            func_80088FF4(Chara_GreyChild, 7, 0);
        }
    }
}

void func_800D9EC4(void)
{
    static const VECTOR3 soundPos = VECTOR3(-58.81f, -1.4f, 18.0198f);
    if (!Savegame_EventFlagGet(EventFlag_76))
    {
        if (D_800DD57C == 0)
        {
            if (!(Rng_Rand16() & 0x1F))
            {
                D_800DD57C = -((Rng_Rand16() & 7) + 2);
            }
        }

        if (D_800DD57C != 0)
        {
            if (ABS(D_800DD57C) == 1)
            {
                g_WorldObj1.position_1C.rotation_C.vy += D_800DD57C;
            }

            g_WorldObj1.position_1C.rotation_C.vy += D_800DD57C;
            if (D_800DD57C > 0)
            {
                if (g_WorldObj1.position_1C.rotation_C.vy > 0)
                {
                    func_8005DC1C(Sfx_Unk1435, &soundPos, 0x80, 0);
                    g_WorldObj1.position_1C.rotation_C.vy = 0;
                    if ((D_800DD57C >= 8) && !(Rng_Rand16() & 3))
                    {
                        D_800DD57C = 0;
                    }
                    else
                    {
                        D_800DD57C = ((Rng_Rand16() & 3) - D_800DD57C) + 1;
                    }
                    D_800DD57C = MIN(D_800DD57C, 0);
                }
            }
            else if (g_WorldObj1.position_1C.rotation_C.vy < -FP_ANGLE(1.8f))
            {
                func_8005DC1C(Sfx_Unk1435, &soundPos, 0x80, 0);
                D_800DD57C = ~(Rng_Rand16() & 3) - D_800DD57C;
                D_800DD57C = MAX(D_800DD57C, 1);
            }
        }
    }
    else if (!Savegame_EventFlagGet(EventFlag_77))
    {
        g_WorldGfx_ObjectAdd(&g_WorldObj3.object_0, &g_WorldObj3.position_1C.position_0, &(SVECTOR3){});
    }
    else
    {
        g_WorldObj1.position_1C.rotation_C.vy = -FP_ANGLE(2.9f);
    }

    g_WorldGfx_ObjectAdd(&g_WorldObj1.object_0, &g_WorldObj1.position_1C.position_0, &g_WorldObj1.position_1C.rotation_C);
    g_WorldObj2.position_1C.rotation_C.vy = g_WorldObj1.position_1C.rotation_C.vy;
    g_WorldGfx_ObjectAdd(&g_WorldObj2.object_0, &g_WorldObj2.position_1C.position_0, &g_WorldObj2.position_1C.rotation_C);
}
