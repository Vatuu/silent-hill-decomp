#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "bodyprog/player_logic.h"
#include "main/rng.h"
#include "maps/shared.h"
#include "maps/map3/map3_s03.h"

INCLUDE_RODATA("asm/maps/map3_s03/nonmatchings/map3_s03", D_800C9578);

INCLUDE_RODATA("asm/maps/map3_s03/nonmatchings/map3_s03", g_MapOverlayHeader);

#include "maps/shared/sharedFunc_800CB6B0_0_s00_noParticles.h" // 0x800CB460

#include "maps/shared/Player.h"

#include "maps/shared/sharedFunc_800CD6B0_3_s03.h" // 0x800CD6B0

#include "maps/shared/sharedFunc_800CD7F8_3_s03.h" // 0x800CD7F8

#include "maps/shared/sharedFunc_800CD920_3_s03.h" // 0x800CD920

#include "maps/shared/sharedFunc_800CD940_3_s03.h" // 0x800CD940

INCLUDE_ASM("asm/maps/map3_s03/nonmatchings/map3_s03", func_800CD980);

void func_800CD9F4(s_SubCharacter* arg0, s32 arg1)
{
    s_SfxPair* sfx;
    s32 idx;

    sfx = D_800D57F0;
    idx = (arg0->properties_E4.npc.field_124->idx_1C * 9) + arg1;
    func_8005DC1C(sfx[idx].sfxId, &arg0->position_18, sfx[idx].vol, 0);
}

INCLUDE_ASM("asm/maps/map3_s03/nonmatchings/map3_s03", func_800CDA44);

#include "maps/shared/sharedFunc_800CDA88_3_s03.h" // 0x800CDA88

#include "maps/shared/Ai_PuppetNurse_UpdateMain.h" // 0x800CDAB8

#include "maps/shared/Ai_PuppetNurse_Init.h" // 0x800CDB5C

#include "maps/shared/Ai_PuppetNurse_Update.h" // 0x800CDD30

#include "maps/shared/Ai_PuppetDoctor_Update.h" // 0x800CDD8C

INCLUDE_ASM("asm/maps/map3_s03/nonmatchings/map3_s03", func_800CDDE8);

INCLUDE_ASM("asm/maps/map3_s03/nonmatchings/map3_s03", sharedFunc_800CDF24_3_s03);

INCLUDE_ASM("asm/maps/map3_s03/nonmatchings/map3_s03", func_800CE0E4);

#include "maps/shared/sharedFunc_800CE398_3_s03.h" // 0x800CE398

INCLUDE_ASM("asm/maps/map3_s03/nonmatchings/map3_s03", sharedFunc_800CE3CC_3_s03);

INCLUDE_ASM("asm/maps/map3_s03/nonmatchings/map3_s03", sharedFunc_800CE500_3_s03);

INCLUDE_ASM("asm/maps/map3_s03/nonmatchings/map3_s03", sharedFunc_800CE5E4_3_s03);

INCLUDE_ASM("asm/maps/map3_s03/nonmatchings/map3_s03", func_800CE7C8);

INCLUDE_ASM("asm/maps/map3_s03/nonmatchings/map3_s03", sharedFunc_800CEA64_3_s03);

INCLUDE_ASM("asm/maps/map3_s03/nonmatchings/map3_s03", sharedFunc_800CEB90_3_s03);

INCLUDE_ASM("asm/maps/map3_s03/nonmatchings/map3_s03", sharedFunc_800CEC88_3_s03);

#include "maps/shared/sharedFunc_800CEEAC_3_s03.h" // 0x800CEEAC

INCLUDE_ASM("asm/maps/map3_s03/nonmatchings/map3_s03", func_800CEEE0);

INCLUDE_ASM("asm/maps/map3_s03/nonmatchings/map3_s03", func_800CF0B4);

INCLUDE_ASM("asm/maps/map3_s03/nonmatchings/map3_s03", func_800CF294);

INCLUDE_ASM("asm/maps/map3_s03/nonmatchings/map3_s03", sharedFunc_800CF3AC_3_s03);

INCLUDE_ASM("asm/maps/map3_s03/nonmatchings/map3_s03", func_800CF600);

void func_800CF7F4(s_SubCharacter* chara)
{
    int angle;
    if ((Rng_Rand16() & Q8_CLAMPED(1.0f)) >= Q8(0.5f))
    {
        chara->properties_E4.larvalStalker.properties_E8[0xD].val16[0] = 
            func_8006FAFC(chara, Q12(1.0f), 
                          g_SysWork.player_4C.chara_0.position_18.vx,
                          g_SysWork.player_4C.chara_0.position_18.vz, FP_ANGLE(360.0f), 1);
    }
    angle = func_8005BF38(chara->properties_E4.larvalStalker.properties_E8[13].val16[0] - chara->rotation_24.vy);
    if (ABS(angle) > FP_ANGLE(5.0f))
    {
        if (angle > 0)
        {
            chara->rotation_24.vy += FP_MULTIPLY_PRECISE(g_DeltaTime0, FP_ANGLE(90.0f), Q12_SHIFT);
        }
        else
        {
            chara->rotation_24.vy -= FP_MULTIPLY_PRECISE(g_DeltaTime0, FP_ANGLE(90.0f), Q12_SHIFT); 
        }
    }
}

#include "maps/shared/sharedFunc_800CF90C_3_s03.h" // 0x800CF90C

INCLUDE_ASM("asm/maps/map3_s03/nonmatchings/map3_s03", sharedFunc_800CF9F8_3_s03);

INCLUDE_ASM("asm/maps/map3_s03/nonmatchings/map3_s03", sharedFunc_800CFD18_3_s03);

INCLUDE_ASM("asm/maps/map3_s03/nonmatchings/map3_s03", sharedFunc_800CFDD4_3_s03);

INCLUDE_ASM("asm/maps/map3_s03/nonmatchings/map3_s03", sharedFunc_800D0110_3_s03);

INCLUDE_RODATA("asm/maps/map3_s03/nonmatchings/map3_s03", D_800CA6A8);

INCLUDE_RODATA("asm/maps/map3_s03/nonmatchings/map3_s03", D_800CA6AC);

#include "maps/shared/Ai_PuppetNurse_Control.h" // 0x800D01D0

INCLUDE_ASM("asm/maps/map3_s03/nonmatchings/map3_s03", sharedFunc_800D02E4_3_s03);

INCLUDE_ASM("asm/maps/map3_s03/nonmatchings/map3_s03", sharedFunc_800D03E4_3_s03);

INCLUDE_ASM("asm/maps/map3_s03/nonmatchings/map3_s03", sharedFunc_800D06AC_3_s03);

#include "maps/shared/sharedFunc_800D0828_3_s03.h" // 0x800D0828

#include "maps/shared/sharedFunc_800D0968_3_s03.h" // 0x800D0968

#include "maps/shared/Ai_Bloodsucker_Update.h" // 0x800D09C4

#include "maps/shared/Ai_Bloodsucker_Init.h" // 0x800D0CDC

#include "maps/shared/sharedFunc_800D0E20_3_s03.h" // 0x800D0E20

#include "maps/shared/sharedSymbol_800D0E38_3_s03.h" // 0x800D0E38

#include "maps/shared/sharedFunc_800D0E80_3_s03.h" // 0x800D0E80

#include "maps/shared/sharedSymbol_800D0ECC_3_s03.h" // 0x800D0ECC

INCLUDE_ASM("asm/maps/map3_s03/nonmatchings/map3_s03", sharedFunc_800D0F28_3_s03); // 0x800D0F28

#include "maps/shared/sharedFunc_800D929C_0_s00.h" // 0x800D1168

#include "maps/shared/Map_RoomIdxGet.h" // 0x800D1178

void func_800D1210(s32 arg0) // 0x800D1210
{
    (arg0 != 0) ? func_800D1244() : func_800D1284();
}

void func_800D1244(void) // 0x800D1244
{
    func_8003640C(!Savegame_EventFlagGet(EventFlag_237) ? 8 : 2);
}

INCLUDE_RODATA("asm/maps/map3_s03/nonmatchings/map3_s03", D_800CA6F4);

INCLUDE_ASM("asm/maps/map3_s03/nonmatchings/map3_s03", func_800D1284);

void func_800D1514(void) {}

const char* MAP_MESSAGES[] = {
    #include "maps/shared/mapMsg_common.h"
    "\tThere_is_a_ ~C2 Plate_of_[Hatter] ~C7 . ~N\n\tTake_it? ~S4 ",
    "\tThere_is_a_ ~C2 Plate_of_[Cat] ~C7 . ~N\n\tTake_it? ~S4 ",
    "\tThere_is_a_ ~C2 Plate_of_[Turtle] ~C7 . ~N\n\tTake_it? ~S4 ",
    "~D ~C3 Clouds_flowing_over_a_hill. ",
    "~D ~C3 Sky_on_a_sunny_day. ",
    "~D ~C3 Tangerines_that_are_bitter. ",
    "~D ~C3 Lucky_four-leaf-clover. ",
    "~D ~C3 Violets_in_the_garden. ",
    "~D ~C3 Dandelions_along_a_path. ",
    "~D ~C3 Unavoidable_sleeping_time. ",
    "~D ~C3 Liquid_flowing ~N\n\t\tfrom_a_slashed_wrist. ~E ",
    "\tThe_VCR_seems_broken. ~N\n\tIt_doesn't_play. ~E ",
    "~J0(0.7)\t_ ",
    "~J2(1.5)\t======= ",
    "~J2(2.7)\tStill_=====_unusua== ~N\n\t\t\t====fever... ",
    "~J2(2.6)\t===_don't_===== ~N\n\t\t\tget====_puls== ",
    "~J2(2.8)\t===_just_bare========= ",
    "~J2(2.3)\t===_skin_is_======== ",
    "~J2(1.2)\tEven_when_I_ch=== ~N\n\t\t\t======== ",
    "~J2(3.8)\t===================== ~N\n\t\t\t==zing_thro=== ",
    "~J2(5.9)\tWhy= ~N\n\t\t\t================_chil===== ",
    "~J2(2.8)\t============ ~N\n\t\t\t========= ",
    "~J2(3.3)\t==won't_tell_==== ~N\n\t\t\t======= ",
    "~J2(2.0)\t==please... ",
    "~J2(0.5)\t_ ~E ",
    "\tThere_is_a_ ~C2 Blood_pack ~C7 . ~N\n\tTake_it? ~S4 ",
    "\tThere_is_a_ ~C2 Disinfecting_alcohol ~C7 . ~N\n\tTake_it? ~S4 ",
    "\tThere_is_a_ ~C2 Lighter ~C7 . ~N\n\tTake_it? ~S4 ",
    "\tThere_is_a ~N\n\t ~C2 Basement_storeroom_key ~C7 . ~N\n\tTake_it? ~S4 ",
    "\t_ ~E ",
    "\tSlate._Nothing_more_than_that. ~E ",
    "\tAlcohol_bottle. ~N\n\tLooks_empty. ~E ",
    "\tWhere_do_you_want_to ~N\n\tset_the_plate? ~E ",
    "\tCan't_set_the_plate_there. ~E ",
    "\tWhich_plate_do_you ~N\n\twant_to_remove? ~E ",
    "\tCan't_remove_that_plate. ~E ",
    "\tThere_are_4_square_indentations ~N\n\ton_the_door. ~E ",
    "\t",
    "\tBird_cage._It's_empty. ~E ",
    "\tVCR._It's_old_but_usable. ~E ",
    "\tA_steel_plate ~N\n\tis_screwed_to_the_wall. ~E ",
    "\tNothing_unusual. ~E ",
    "\tHere_are_some_dryers. ~N\n\tUseless_now. ~E ",
    "\tNothing_helpful. ~E ",
    "\tNothing_useful_in_the_boxes. ~E ",
    "\tThere's_a_bottle_filled ~N\n\twith_some_kind_of_drug. ~N\n\tBetter_leave_it. ~E ",
    "\tThere_are_some_empty_bottles. ~E ",
    "\tNothing_special_in_the_box. ~N\n\tNothing_to_worry_about. ~E "
};

void func_800D151C(void) // 0x800D151C
{
    u32 pickupType;
    s32 eventFlagIdx;

    pickupType   = CommonPickupItemId_FirstAidKit;
    eventFlagIdx = 0;

    switch (g_MapEventParam->field_5)
    {
        case 126:
            pickupType   = CommonPickupItemId_FirstAidKit;
            eventFlagIdx = EventFlag_M3S03_FirstAidKit0;
            break;

        case 127:
            pickupType   = CommonPickupItemId_HealthDrink;
            eventFlagIdx = EventFlag_M3S03_HealthDrink;
            break;

        case 128:
            pickupType   = CommonPickupItemId_HandgunBullets;
            eventFlagIdx = EventFlag_M3S03_HandgunBullets;
            break;

        case 129:
            pickupType   = CommonPickupItemId_FirstAidKit;
            eventFlagIdx = EventFlag_M3S03_FirstAidKit1;
            break;

        case 130:
            pickupType   = CommonPickupItemId_ShotgunShells;
            eventFlagIdx = EventFlag_M3S03_ShotgunShells;
            break;
    }

    Event_CommonItemTake(pickupType, eventFlagIdx);
}

#include "maps/shared/MapEvent_DoorJammed.h" // 0x800D15B8

#include "maps/shared/MapEvent_DoorLocked.h" // 0x800D164C

#include "maps/shared/MapEvent_DoorUnlocked.h" // 0x800D16E0

void func_800D1774(void) // 0x800D1774
{
    Event_ItemTake(InventoryItemId_PlateOfHatter, DEFAULT_PICKUP_ITEM_COUNT, EventFlag_M3S03_PickupPlateOfHatter, 15);
}

void func_800D17A0(void) // 0x800D17A0
{
    Event_ItemTake(InventoryItemId_PlateOfCat, DEFAULT_PICKUP_ITEM_COUNT, EventFlag_M3S03_PickupPlateOfCat, 16);
}

void func_800D17CC(void) // 0x800D17CC
{
    Event_ItemTake(InventoryItemId_PlateOfTurtle, DEFAULT_PICKUP_ITEM_COUNT, EventFlag_M3S03_PickupPlateOfTurtle, 17);
}

INCLUDE_ASM("asm/maps/map3_s03/nonmatchings/map3_s03", func_800D17F8);

INCLUDE_ASM("asm/maps/map3_s03/nonmatchings/map3_s03", func_800D1A58);

void func_800D26D0(void) // 0x800D26D0
{
    g_BackgroundColor = 104;
    MapMsg_DisplayWithTexture(FILE_TIM_PLATECLR_TIM, Q12(0.0f), Q12(0.0f), 18);
}

void func_800D2708(void) // 0x800D2708
{
    g_BackgroundColor = 104;
    MapMsg_DisplayWithTexture(FILE_TIM_LITHGRPH_TIM, Q12(0.0f), Q12(0.0f), 44);
}

void func_800D2740(void) // 0x800D2740
{
    g_BackgroundColor = 96;
    MapMsg_DisplayWithTexture(FILE_TIM_LITHGR_2_TIM, Q12(0.0f), Q12(0.0f), 45);
}

void func_800D2778(void) // 0x800D2778
{
    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            Player_ControlFreeze();
            SysWork_StateStepIncrement(0);

        default:
            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);
            break;
    }
}

void func_800D27F4(void) // 0x800D27F4
{
    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            Player_ControlFreeze();
            func_800862F8(0, FILE_TIM_LISAVTR2_TIM, false);
            D_800D6BDA = 0;
            SysWork_StateStepIncrement(0);

        case 1:
            func_80085DF0();
            break;

        case 2:
            func_80085EB8(0, &g_SysWork.player_4C.chara_0, 146, false);
            SysWork_StateStepIncrementAfterFade(0, true, 2, Q12(0.0f), false);

            // Warp player.
            g_SysWork.player_4C.chara_0.position_18.vx = Q12(-62.38f);
            g_SysWork.player_4C.chara_0.position_18.vz = Q12(-59.66f);
            g_SysWork.player_4C.chara_0.rotation_24.vy = FP_ANGLE(320.9f);

            // Warp camera.
            Camera_PositionSet(NULL, Q12(-61.03f), Q12(-2.14f), Q12(-62.3f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);
            Camera_LookAtSet(NULL, Q12(-62.93f), Q12(-0.95f), Q12(-58.99f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);

            SysWork_StateStepIncrement(0);

        case 3:
            SysWork_StateStepIncrementDelayed(Q12(2.5f), false);
            break;

        case 4:
            func_8005DC1C(Sfx_Unk1526, &QVECTOR3(-62.6f, -0.5f, -59.0f), Q8_CLAMPED(0.5f), 0);
            SysWork_StateStepIncrement(0);

        case 5:
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(0.0f), false);
            break;

        case 6:
            func_800862F8(1, FILE_1ST_2ZANKO80_TIM, false);
            break;

        case 7:
            SysWork_StateStepIncrementAfterFade(2, false, 0, Q12(0.0f), false);
            func_800862F8(2, FILE_1ST_2ZANKO80_TIM, false);
            break;

        case 8:
            SysWork_StateStepIncrement(0);

        case 9:
            Map_MessageWithAudio(27, &D_800D6BDA, &D_800D6B54);
            func_800862F8(2, FILE_1ST_2ZANKO80_TIM, false);

            if (g_SysWork.sysStateStep_C[0] == 9 &&
                (g_Controller0->btnsClicked_10 & (g_GameWorkPtr->config_0.controllerConfig_0.skip_4 | g_GameWorkPtr->config_0.controllerConfig_0.cancel_2)))
            {
                Sd_EngineCmd(19);
                SysWork_StateStepIncrement(0);
            }
            break;

        case 10:
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(0.0f), false);
            func_800862F8(2, FILE_1ST_2ZANKO80_TIM, false);
            break;

        case 11:
            func_80085EB8(0, &g_SysWork.player_4C.chara_0, 147, false);
            SysWork_StateStepIncrement(0);
            break;

        case 12:
            func_80085EB8(2, &g_SysWork.player_4C.chara_0, 0, false);
            SysWork_StateStepIncrementAfterFade(0, false, 0, Q12(0.0f), false);
            SysWork_StateStepIncrement(0);

        case 13:
            SysWork_StateStepIncrementDelayed(Q12(0.5f), false);
            break;

        case 14:
            func_8005DC1C(Sfx_Unk1526, &QVECTOR3(-62.6f, -0.5f, -59.0f), Q8_CLAMPED(0.5f), 0);
            SysWork_StateStepIncrement(0);

        case 15:
            func_80086D04(&g_SysWork.player_4C.chara_0);
            break;

        default:
            Player_ControlUnfreeze(false);

            SysWork_StateSetNext(SysState_Gameplay);
            Savegame_EventFlagSet(EventFlag_254);

            vcReturnPreAutoCamWork(false);
            SysWork_StateStepIncrementAfterFade(0, false, 2, Q12(0.0f), false);

            func_80086470(3, InventoryItemId_VideoTape, 1, false);
            break;
    }
}

void func_800D2C2C(void) // 0x800D2C2C
{
    Event_ItemTake(InventoryItemId_BloodPack, DEFAULT_PICKUP_ITEM_COUNT, EventFlag_M3S03_PickupBloodPack, 40);
}

void func_800D2C58(void) // 0x800D2C58
{
    Event_ItemTake(InventoryItemId_DisinfectingAlcohol, DEFAULT_PICKUP_ITEM_COUNT, EventFlag_M3S03_PickupDisinfectingAlcohol, 41);
}

void func_800D2C84(void) // 0x800D2C84
{
    Event_ItemTake(InventoryItemId_Lighter, DEFAULT_PICKUP_ITEM_COUNT, EventFlag_M3S03_PickupLighter, 42);
}

void func_800D2CB0(void) // 0x800D2CB0
{
    Event_ItemTake(InventoryItemId_BasementStoreroomKey, DEFAULT_PICKUP_ITEM_COUNT, EventFlag_M3S03_PickupBasementStoreroomKey, 43);
}

void func_800D2CDC(void) // 0x800D2CDC
{
    s32 i;
    s32 state;

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            Player_ControlFreeze();
            SysWork_StateStepIncrementAfterFade(false, true, 2, false, false);
            ScreenFade_ResetTimestep();

        case 1:
            func_80085DF0();
            break;

        case 2:
            // Warp player.
            g_SysWork.player_4C.chara_0.position_18.vx = Q12(-139.7f);
            g_SysWork.player_4C.chara_0.position_18.vy = Q12(0.0f);
            g_SysWork.player_4C.chara_0.position_18.vz = Q12(61.4f);
            g_SysWork.player_4C.chara_0.rotation_24.vy = ratan2(Q12(-2.0f), Q12(-1.2f));

            WorldGfx_PlayerHeldItemSet(InventoryItemId_CutsceneBloodPack);
            Fs_QueueWaitForEmpty();

            func_8003D01C();
            func_80085EB8(0, &g_SysWork.player_4C.chara_0, 154, false);

            // Warp camera.
            Camera_PositionSet(NULL, Q12(-139.3f), Q12(-2.9f), Q12(65.22f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);
            Camera_LookAtSet(NULL, Q12(-140.67f), Q12(-1.26f), Q12(61.83f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);

            SysWork_StateStepIncrement(0);
            break;

        case 3:
            func_80085EB8(2, &g_SysWork.player_4C.chara_0, 0, false);
            SysWork_StateStepIncrement(0);

        case 4:
            SysWork_StateStepIncrementAfterFade(2, false, 0, Q12(0.0f), false);
            break;

        case 5:
            func_80085EB8(3, &g_SysWork.player_4C.chara_0, 0, false);
            SysWork_StateStepIncrement(0);

        case 6:
            SysWork_StateStepIncrementDelayed(Q12(1.5f), false);
            break;

        case 7:
            state = 4; // @hack Needed to match reg order.
            i     = 2;
            for (i = 2; i >= 0; i--)
            {
                g_SysWork.npcs_1A0[i].model_0.state_2 = state;
            }

            func_80085EB8(0, &g_SysWork.player_4C.chara_0, 51, false);

            func_800625F4(&QVECTOR3(-141.7f, 0.0f, 60.2f), 110, 15, 0);
            func_800625F4(&QVECTOR3(-141.7f, 0.0f, 60.2f), 100, 15, 0);
            func_8003D03C();
            func_8003CD6C(&g_SysWork.playerCombatInfo_38);

            // Warp camera.
            Camera_PositionSet(NULL, Q12(-140.45f), Q12(0.03f), Q12(59.45f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);
            Camera_LookAtSet(NULL, Q12(-143.07f), Q12(-1.65f), Q12(61.97f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);

            SysWork_StateStepIncrement(0);

        case 8:
            SysWork_StateStepIncrementDelayed(Q12(1.5f), false);
            break;

        case 9:
            Savegame_EventFlagSet(EventFlag_250);

            // Warp camera.
            Camera_PositionSet(NULL, Q12(-140.05f), Q12(-3.09f), Q12(63.46f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);
            Camera_LookAtSet(NULL, Q12(-142.08f), Q12(-0.92f), Q12(60.79f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);

            SysWork_StateStepIncrement(0);

        case 10:
            SysWork_StateStepIncrementDelayed(Q12(2.0f), false);
            break;

        default:
            Fs_QueueWaitForEmpty();
            Player_ControlUnfreeze(true);
            SysWork_StateSetNext(SysState_Gameplay);
            func_8003D01C();
            vcReturnPreAutoCamWork(true);
            SysWork_StateStepIncrementAfterFade(false, false, 2, Q12(0.0f), false);
            break;
    }
}

void func_800D30FC(void) // 0x800D30FC
{
    MapMsg_DisplayWithTexture(FILE_TIM_CAGEEMPT_TIM, Q12(0.0f), Q12(0.0f), 53);
}

void func_800D3128(void) // 0x800D3128
{
    g_BackgroundColor = 112;
    MapMsg_DisplayWithTexture(FILE_TIM_ELCWIRE0_TIM, Q12(0.0f), Q12(0.0f), 55);
}

INCLUDE_RODATA("asm/maps/map3_s03/nonmatchings/map3_s03", D_800CB304);

INCLUDE_RODATA("asm/maps/map3_s03/nonmatchings/map3_s03", D_800CB310);

INCLUDE_ASM("asm/maps/map3_s03/nonmatchings/map3_s03", func_800D3160);

void Map_WorldObjectsInit(void) // 0x800D3EAC
{
    D_800D8428 = 0;

    WorldObjectNoRotInit(&g_WorldObject_Dr[0], "DR1L_HID", 19.1f, 0.0f, 59.1f);
    WorldObjectNoRotInit(&g_WorldObject_Dr[1], "DR1R_HID", 19.1f, 0.0f, 59.1f);
    WorldObjectNoRotInit(&g_WorldObject_Dr[2], "DR3L_HID", 19.1f, 0.0f, 59.1f);
    WorldObjectNoRotInit(&g_WorldObject_Dr[3], "DR3R_HID", 19.1f, 0.0f, 59.1f);
    WorldObjectNoRotInit(&g_WorldObject_Dr[4], "DR2L_HID", 19.1f, 0.0f, 59.1f);
    WorldObjectNoRotInit(&g_WorldObject_Dr[5], "DR2R_HID", 19.1f, 0.0f, 59.1f);

    WorldObject_ModelNameSet(&g_WorldObject_Colors[0], "BLUE_HID");
    WorldObject_ModelNameSet(&g_WorldObject_Colors[1], "GREEN_HI");
    WorldObject_ModelNameSet(&g_WorldObject_Colors[2], "YELLOW_H");
    WorldObject_ModelNameSet(&g_WorldObject_Colors[3], "RED_HIDE");

    WorldObjectInit(&g_WorldObject_Plate0, "PLATE_HI", -140.15f, 0.0f, 59.75f, 0.0f, 180.0f, 0.0f);

    WorldObjectNoRotInit(&g_WorldObject_Plate1, "PLATE_HI", -20.0f, 0.0f, -19.2f);

    WorldObjectInit(&g_WorldObject_Panel, "PANEL_HI", -140.0f, 0.0f, -20.0f, 0.0f, 90.0f, 0.0f);

    WorldObjectInit(&g_WorldObject_Blood0, "BLOOD_NE", -57.45f, -0.9f, -21.05f, 0.0f, 90.0f, 0.0f);

    WorldObjectInit(&g_WorldObject_Lighter, "LIGHTER_", -100.7f, 0.0f, 57.95f, 0.0f, 180.0f, 0.0f);

    WorldObjectNoRotInit(&g_WorldObject_Alcohol, "ALCOHOL_", -60.8f, 0.0f, 21.6f);

    WorldObjectNoRotInit(&g_WorldObject_Key, "KEY_HIDE", -99.2f, 0.0f, 22.55f);

    WorldObjectInit(&g_WorldObject_SavePad, D_800A99E4.savePadName_4, -58.6104f, -1.0f, -59.1241f, 0.0f, 9.0f, 0.0f);

    WorldObjectInit(&g_WorldObject_Blood1, "BLOOD_HI", -141.5f, 0.0f, 61.4f, 0.0f, -41.0f, 0.0f);

    WorldObjectNoRotInit(&g_WorldObject_Blood2, "BLOOD_HI", -141.7f, -0.05f, 60.2f);

    WorldObject_ModelNameSet(&g_CommonWorldObjects[0], D_800A99E4.firstAidKitName_8);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[1], D_800A99E4.healthDrinkName_C);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[2], D_800A99E4.ampouleName_10);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[3], D_800A99E4.handgunBulletsName_14);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[4], D_800A99E4.shotgunShellsName_18);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[5], D_800A99E4.rifleShellsName_1C);
}

void func_800D429C(void)
{
    VECTOR3 colorsPos;
    s32 cellZ0;
    s32 cellX0;
    s32 flags;
    s32 projCellZ0;
    s32 projCellX0;
    s32 drZ;
    s32 i;
    MAP_CHUNK_CHECK_VARIABLE_DECL();

    flags = 0;

    if (PLAYER_NOT_IN_MAP_CHUNK(vx, 1, -4, -1, -4) || PLAYER_NOT_IN_MAP_CHUNK(vz, 1, 2, -1, 2))
    {
        D_800D8428 = 0;
    }

    cellZ0 = g_SysWork.player_4C.chara_0.position_18.vz / CHUNK_CELL_SIZE;
    cellX0 = g_SysWork.player_4C.chara_0.position_18.vx / CHUNK_CELL_SIZE;

    if (g_SysWork.player_4C.chara_0.position_18.vx > Q12(0.0f))
    {
        projCellX0 = cellX0 + 17;
    }
    else
    {
        projCellX0 = cellX0 + 15;
    } 

    if (g_SysWork.player_4C.chara_0.position_18.vz > Q12(0.0f))
    {
        projCellZ0 = cellZ0 + 17;
    }
    else
    {
        projCellZ0 = cellZ0 + 15;
    }

    switch (PACKED_CELL_XZ(projCellX0, projCellZ0))
    {
    case PACKED_CELL_XZ(17, 18):
        if ((g_SysWork.sysState_8 == SysState_Gameplay) && (g_WorldObject_Dr->position_1C.vz != Q12(59.1f)))
        {
            drZ = Q12(59.1f);
            for (i = 5; i >= 0; i--)
            {
                g_WorldObject_Dr[i].position_1C.vz = drZ;
            }
        }
        for (i = 0; i < 6; i++)
        {
            g_WorldGfx_ObjectAdd(&g_WorldObject_Dr[i].object_0, &g_WorldObject_Dr[i].position_1C, &(SVECTOR3){});
        }
        break;
    case PACKED_CELL_XZ(15, 20):
        colorsPos.vz = Q12(140.0f);
        if (Savegame_EventFlagGet(EventFlag_265) ||
            Savegame_EventFlagGet(EventFlag_266) ||
            Savegame_EventFlagGet(EventFlag_267) ||
            Savegame_EventFlagGet(EventFlag_268))
        {
            if (Savegame_EventFlagGet(EventFlag_265) || Savegame_EventFlagGet(EventFlag_266))
            {
                colorsPos.vx = Q12(-20.0f);
            }
            else
            {
                colorsPos.vx = Q12(-19.6f);
            }
            if (Savegame_EventFlagGet(EventFlag_265) || Savegame_EventFlagGet(EventFlag_268))
            {
                colorsPos.vy = Q12(0.0f);
            }
            else
            {
                colorsPos.vy = Q12(0.4f);
            }
            g_WorldGfx_ObjectAdd(&g_WorldObject_Colors[0], &colorsPos, &(SVECTOR3){});
        }
        if (Savegame_EventFlagGet(EventFlag_269) ||
            Savegame_EventFlagGet(EventFlag_270) ||
            Savegame_EventFlagGet(EventFlag_271) ||
            Savegame_EventFlagGet(EventFlag_272))
        {
            if (Savegame_EventFlagGet(EventFlag_269) || Savegame_EventFlagGet(EventFlag_270))
            {
                colorsPos.vx = Q12(-20.0f);
            }
            else
            {
                colorsPos.vx = Q12(-19.6f);
            }
            if (Savegame_EventFlagGet(EventFlag_270) || Savegame_EventFlagGet(EventFlag_271))
            {
                colorsPos.vy = Q12(0.0f);
            }
            else
            {
                colorsPos.vy = Q12(-0.4f);
            }
            g_WorldGfx_ObjectAdd(&g_WorldObject_Colors[1], &colorsPos, &(SVECTOR3){});
        }
        if (Savegame_EventFlagGet(EventFlag_273) ||
            Savegame_EventFlagGet(EventFlag_274) ||
            Savegame_EventFlagGet(EventFlag_275) ||
            Savegame_EventFlagGet(EventFlag_276))
        {
            if (Savegame_EventFlagGet(EventFlag_275) || Savegame_EventFlagGet(EventFlag_276))
            {
                colorsPos.vx = Q12(-20.0f);
            }
            else
            {
                colorsPos.vx = Q12(-20.4f);
            }
            if (Savegame_EventFlagGet(EventFlag_274) || Savegame_EventFlagGet(EventFlag_275))
            {
                colorsPos.vy = Q12(0.0f);
            }
            else
            {
                colorsPos.vy = Q12(-0.4f);
            }
            g_WorldGfx_ObjectAdd(&g_WorldObject_Colors[2], &colorsPos, &(SVECTOR3){});
        }
        if (Savegame_EventFlagGet(EventFlag_277) ||
            Savegame_EventFlagGet(EventFlag_278) ||
            Savegame_EventFlagGet(EventFlag_279) ||
            Savegame_EventFlagGet(EventFlag_280))
        {
            if (Savegame_EventFlagGet(EventFlag_279) || Savegame_EventFlagGet(EventFlag_280))
            {
                colorsPos.vx = Q12(-20.0f);
            }
            else
            {
                colorsPos.vx = Q12(-20.4f);
            }
            if (Savegame_EventFlagGet(EventFlag_277) || Savegame_EventFlagGet(EventFlag_280))
            {
                colorsPos.vy = Q12(0.0f);
            }
            else
            {
                colorsPos.vy = Q12(0.4f);
            }
            g_WorldGfx_ObjectAdd(&g_WorldObject_Colors[3], &colorsPos, &(SVECTOR3){});
        }
        break;
    case PACKED_CELL_XZ(12, 18):
        if (Savegame_EventFlagGet(EventFlag_250))
        {
            flags |= (1<<2);
        }
        else
        {
            flags |= (1<<1);
        }
        if (!Savegame_EventFlagGet(EventFlag_M3S03_PickupPlateOfHatter))
        {
            g_WorldGfx_ObjectAdd(&g_WorldObject_Plate0.object_0, &g_WorldObject_Plate0.position_1C, &g_WorldObject_Plate0.rotation_28);
        }
        if (Savegame_EventFlagGet(EventFlag_250))
        {
            g_WorldGfx_ObjectAdd(&g_WorldObject_Blood2.object_0, &g_WorldObject_Blood2.position_1C, &(SVECTOR3){});
        }
        if (!D_800D8428)
        {
            D_800D8428++;
            func_800625F4(&QVECTOR3(-141.5f, 0.0f, 61.4f), 0x48, 15, 1);
            func_800625F4(&QVECTOR3(-141.5f, 0.0f, 61.35f), 0x28, 15, 1);
            if (Savegame_EventFlagGet(EventFlag_250))
            {
                func_800625F4(&QVECTOR3(-141.7f, 0.0f, 60.2f), 0x6E, 15, 1);
                func_800625F4(&QVECTOR3(-141.7f, 0.0f, 60.2f), 0x64, 15, 1);
            }
        }
        break;
    case PACKED_CELL_XZ(15, 15):
        if (!Savegame_EventFlagGet(EventFlag_M3S03_PickupPlateOfCat))
        {
            g_WorldGfx_ObjectAdd(&g_WorldObject_Plate1.object_0, &g_WorldObject_Plate1.position_1C, &(SVECTOR3){});
        }
        break;
    case PACKED_CELL_XZ(12, 15):
        if (!Savegame_EventFlagGet(EventFlag_M3S03_PickupPlateOfTurtle))
        {
            g_WorldGfx_ObjectAdd(&g_WorldObject_Panel.object_0, &g_WorldObject_Panel.position_1C, &g_WorldObject_Panel.rotation_28);
        }
        if (!Savegame_EventFlagGet(EventFlag_239) &&
             Savegame_EventFlagGet(EventFlag_M3S03_PickupPlateOfTurtle) &&
             g_SysWork.player_4C.chara_0.position_18.vz > Q12(-18.2f))
        {
            func_8005DC1C(Sfx_Unk1528, &QVECTOR3(-140.0f, -1.2f, -23.5f), Q8_CLAMPED(1.0f), 2);
            Savegame_EventFlagSet(EventFlag_239);
        }
        break;
    case PACKED_CELL_XZ(13, 18):
        if (!Savegame_EventFlagGet(EventFlag_M3S03_PickupLighter))
        {
            g_WorldGfx_ObjectAdd(&g_WorldObject_Lighter.object_0, &g_WorldObject_Lighter.position_1C, &g_WorldObject_Lighter.rotation_28);
        }
        break;
    case PACKED_CELL_XZ(14, 17):
        if (!Savegame_EventFlagGet(EventFlag_M3S03_PickupDisinfectingAlcohol))
        {
            g_WorldGfx_ObjectAdd(&g_WorldObject_Alcohol.object_0, &g_WorldObject_Alcohol.position_1C, &(SVECTOR3){});
        }
        break;
    case PACKED_CELL_XZ(13, 17):
        if (!Savegame_EventFlagGet(EventFlag_M3S03_PickupBasementStoreroomKey))
        {
            g_WorldGfx_ObjectAdd(&g_WorldObject_Key.object_0, &g_WorldObject_Key.position_1C, &(SVECTOR3){});
        }
        break;
    case PACKED_CELL_XZ(14, 15):
        if (!Savegame_EventFlagGet(EventFlag_M3S03_PickupBloodPack))
        {
            g_WorldGfx_ObjectAdd(&g_WorldObject_Blood0.object_0, &g_WorldObject_Blood0.position_1C, &g_WorldObject_Blood0.rotation_28);
        }
        break;
    case PACKED_CELL_XZ(14, 14):
        g_WorldGfx_ObjectAdd(&g_WorldObject_SavePad.object_0, &g_WorldObject_SavePad.position_1C, &g_WorldObject_SavePad.rotation_28);
        break;
    }

    func_80069844(0xFFFF);
    func_8006982C(flags);
    if (PLAYER_IN_MAP_CHUNK(vx, 1, -4, -1, -4) && PLAYER_IN_MAP_CHUNK(vz, 1, 2, -1, 2))
    {
        D_800D8490 = 1;
    }
    else
    {
        if (D_800D8490 != 0)
        {
            func_8004690C(Sfx_Unk1525);
            func_8004690C(Sfx_Unk1527);
            D_800D8490 = 0;
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, -1, 0, 0) && PLAYER_IN_MAP_CHUNK(vz, 0, 0, -1, 1))
    {
        if (!Savegame_EventFlagGet(EventFlag_M3S03_FirstAidKit0))
        {
            g_WorldGfx_ObjectAdd(&g_CommonWorldObjects[0], &g_CommonWorldObjectPoses[0].position_0, &g_CommonWorldObjectPoses[0].rotation_C);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, -3, -1, -3) && PLAYER_IN_MAP_CHUNK(vz, 1, -2, -1, -2))
    {
        if (!Savegame_EventFlagGet(EventFlag_M3S03_HealthDrink))
        {
            g_WorldGfx_ObjectAdd(&g_CommonWorldObjects[1], &g_CommonWorldObjectPoses[1].position_0, &g_CommonWorldObjectPoses[1].rotation_C);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, -2, -1, -2) && PLAYER_IN_MAP_CHUNK(vz, 1, -1, 0, 0))
    {
        if (!Savegame_EventFlagGet(EventFlag_M3S03_HandgunBullets))
        {
            g_WorldGfx_ObjectAdd(&g_CommonWorldObjects[3], &g_CommonWorldObjectPoses[2].position_0, &g_CommonWorldObjectPoses[2].rotation_C);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, -2, -1, -2) && PLAYER_IN_MAP_CHUNK(vz, 1, -1, 0, 0))
    {
        if (!Savegame_EventFlagGet(EventFlag_M3S03_FirstAidKit1))
        {
            g_WorldGfx_ObjectAdd(&g_CommonWorldObjects[0], &g_CommonWorldObjectPoses[3].position_0, &g_CommonWorldObjectPoses[3].rotation_C);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, -2, -1, -2) && PLAYER_IN_MAP_CHUNK(vz, 1, -2, -1, -2))
    {
        if (!Savegame_EventFlagGet(EventFlag_M3S03_ShotgunShells))
        {
            g_WorldGfx_ObjectAdd(&g_CommonWorldObjects[5], &g_CommonWorldObjectPoses[4].position_0, &g_CommonWorldObjectPoses[4].rotation_C);
        }
    }
}

