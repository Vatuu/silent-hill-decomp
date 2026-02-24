#include "bodyprog/bodyprog.h"
#include "bodyprog/item_screens.h"
#include "bodyprog/math/math.h"
#include "bodyprog/player_logic.h"
#include "main/rng.h"
#include "maps/map3/map3_s05.h"
#include "maps/particle.h"
#include "maps/characters/creeper.h"
#include "maps/characters/player.h"
#include "maps/characters/puppet_nurse.h"

#include "maps/shared/sharedFunc_800CAAD0_1_s05.h" // 0x800CB5F4

#include "maps/shared/sharedFunc_800CABF8_1_s05.h" // 0x800CB71C

#include "maps/shared/sharedFunc_800CB040_1_s05.h" // 0x800CBB64

#include "maps/shared/sharedFunc_800CB884_1_s05.h" // 0x800CC3A8

#include "../src/maps/particle.c"

#include "../src/maps/characters/player.c"

// TODO: Move this line into separate `Chara_Creeper` split.
#include "../src/maps/characters/creeper.c" // 0x800CFEAC

#include "maps/shared/sharedFunc_800CD6B0_3_s03.h" // 0x800D2120

#include "maps/shared/sharedFunc_800CD7F8_3_s03.h" // 0x800D2268

#include "maps/shared/sharedFunc_800CD920_3_s03.h" // 0x800D2390

#include "maps/shared/sharedFunc_800CD940_3_s03.h" // 0x800D23B0

#include "maps/shared/PuppetNurse_HurtSfxIdGet.h"

#include "maps/shared/Ai_PuppetNurse_SfxPlay.h"

#include "maps/shared/Ai_PuppetNurse_AnimSfxGet.h" // 0x800D24B4

#include "maps/shared/sharedFunc_800CDA88_3_s03.h" // 0x800D24F8

#include "maps/shared/Ai_PuppetNurse_UpdateMain.h" // 0x800D2528

#include "maps/shared/Ai_PuppetNurse_Init.h" // 0x800D25CC

#include "maps/shared/Ai_PuppetNurse_Update.h" // 0x800D27A0

#include "maps/shared/Ai_PuppetDoctor_Update.h" // 0x800D27FC

#include "maps/shared/Ai_PuppetNurse_SomeAngleCheck.h"

#include "maps/shared/Ai_PuppetNurse_DamageHandle.h" // 0x800D2994

#include "maps/shared/Ai_PuppetNurse_Move.h"

#include "maps/shared/sharedFunc_800CE398_3_s03.h" // 0x800D2E08

#include "maps/shared/Ai_PuppetNurse_Control1.h" // 0x800D2E3C

#include "maps/shared/Ai_PuppetNurse_Control2.h" // 0x800D2F70

#include "maps/shared/Ai_PuppetNurse_Control3_4.h" // 0x800D3054

#include "maps/shared/sharedFunc_800CE7C8_3_s03.h" // 0x800D3238

#include "maps/shared/Ai_PuppetNurse_Control5.h" // 0x800D34D4

#include "maps/shared/Ai_PuppetNurse_Control6_7.h" // 0x800D3600

#include "maps/shared/Ai_PuppetNurse_Control8.h" // 0x800D36F8

#include "maps/shared/sharedFunc_800CEEAC_3_s03.h" // 0x800D391C

#include "maps/shared/sharedFunc_800CEEE0_3_s03.h" // 0x800D3950

#include "maps/shared/sharedFunc_800CF0B4_3_s03.h" // 0x800D3B24

#include "maps/shared/sharedFunc_800CF294_3_s03.h" // 0x800D3D04

#include "maps/shared/Ai_PuppetNurse_Control9.h" // 0x800D3E1C

#include "maps/shared/sharedFunc_800CF600_3_s03.h" // 0x800D4070

#include "maps/shared/sharedFunc_800CF7F4_3_s03.h" // 0x800D4264

#include "maps/shared/sharedFunc_800CF90C_3_s03.h" // 0x800D437C

#include "maps/shared/Ai_PuppetNurse_Control12.h" // 0x800D4468

#include "maps/shared/Ai_PuppetNurse_Control10.h" // 0x800D4788

#include "maps/shared/Ai_PuppetNurse_Control11.h" // 0x800D4844

#include "maps/shared/Ai_PuppetNurse_Control13.h" // 0x800D4B80

INCLUDE_RODATA("maps/map3_s05/nonmatchings/map3_s05", g_NursePuppet_SfxOffsets);

INCLUDE_RODATA("maps/map3_s05/nonmatchings/map3_s05", g_PuppetNurse_ModelStates0);

#include "maps/shared/Ai_PuppetNurse_Control.h" // 0x800D4C40

#include "maps/shared/sharedFunc_800D02E4_3_s03.h" // 0x800D4D54

#include "maps/shared/sharedFunc_800D03E4_3_s03.h" // 0x800D4E54

#include "maps/shared/Ai_PuppetNurse_AnimUpdate.h" // 0x800D511C

#include "maps/shared/sharedFunc_800D0828_3_s03.h" // 0x800D5298

#include "maps/shared/sharedFunc_800D0968_3_s03.h" // 0x800D53D8

#include "maps/shared/sharedFunc_800D929C_0_s00.h" // 0x800D5434

#include "maps/shared/Map_RoomIdxGet.h" // 0x800D5444

#include "maps/shared/Map_RoomBgmInit_CheckCond.h" // 0x800D54DC

#include "maps/shared/Map_RoomBgmInit_3_s02_CondTrue.h" // 0x800D5510

#include "maps/shared/Map_RoomBgmInit_3_s02_CondFalse.h" // 0x800D5550

void func_800D57E0(void) {}

void func_800D57E8(void) // 0x800D57E8
{
    VECTOR3 sfxPos = { MAP_POINTS[g_MapEventData->pointOfInterestIdx_5].positionX_0, Q12(-1.2f), MAP_POINTS[g_MapEventData->pointOfInterestIdx_5].positionZ_8 };

    if (g_MapEventData->pointOfInterestIdx_5 == 25)
    {
        Map_MessageWithSfx(11, Sfx_Unk1350, &sfxPos);
    }
    else
    {
        Map_MessageWithSfx(11, Sfx_DoorJammed, &sfxPos);
    }
}

#include "maps/shared/MapEvent_DoorLocked.h" // 0x800D58A0

const char* MAP_MESSAGES[] = {
    #include "maps/shared/mapMsg_common.h"
    "\tThere_is_a_ ~C2 Video_tape ~C7 . ~N\n\tTake_it? ~S4 ",
    "~C3\tAlessa ~E ",
    "\tAlessa...? ~E ",
    "~J0(1.2)\tWhat's_this? ~E ",
    "~J0(2.6)\tLooks_like_someone's_been_here... ~E ",
    "\t~J0(0.4) ~E ",
    "\tThere_is_an_ ~C2 Examination_room_key ~C7 . ~N\n\tTake_it? ~S4 ",
    "\tLooks_like_a_hallway ~N\n\tunder_the_grate. ",
    "\tCan't_move_it_since_the_vines ~N\n\thave_grown_around_it. ~E ",
    "\tNo. ~N\n\tThe_fire_goes_out_right_away ~N\n\twhen_I_light_the_vines. ~E ",
    "\tPoured_ ~C2 Disinfecting_alcohol ~C7  ~N\n\ton_the_vines. ~E ",
    "\tThe_vines_absorbed_the_alcohol. ~E ",
    "\tUsed_the_ ~C2 Basement_storeroom_key ~C7 . ~E ",
    "\tDo_you_want_to_push ~N\n\tthe_cabinet? ~S4 ",
    "\tThe_generator_is_on. ~E ",
    "\tThere_are_skid_marks_from ~N\n\tthe_cabinet_being_moved. ~E ",
    "\tThere_is_a_ ~C2 Hammer ~C7 . ~N\n\tTake_it? ~S4 ",
    "\tA_bed?_What's_it_doing_here? ~N\n\tWho_would... ~E ",
    "\tA_body_is_laid_out_on_the_bed. ~N\n\tDon't_feel_like_checking_this_out. ~E ",
    "\tNothing_helpful. ~E ",
    "\tNothing_useful_in_the_boxes. ~E ",
    "\tThere's_a_bottle_filled ~N\n\twith_some_kind_of_drug. ~N\n\tBetter_leave_it. ~E ",
    "\tThere_are_some_empty_bottles. ~E ",
    "\tNothing_special_in_the_box. ~N\n\tNothing_to_worry_about. ~E ",
    "\tNothing_inside. ~E "
};

void func_800D5934(void) // 0x800D5934
{
    u32 pickupType;
    s32 eventFlagIdx;

    pickupType   = CommonPickupItemId_FirstAidKit;
    eventFlagIdx = 0;

    switch (g_MapEventData->pointOfInterestIdx_5)
    {
        case 96:
            pickupType   = CommonPickupItemId_Ampoule;
            eventFlagIdx = EventFlag_M3S05_Ampoule;
            break;

        case 97:
            pickupType   = CommonPickupItemId_HealthDrink;
            eventFlagIdx = EventFlag_M3S05_HealthDrink;
            break;

        case 98:
            pickupType   = CommonPickupItemId_HandgunBullets;
            eventFlagIdx = EventFlag_M3S05_HandgunBullets;
            break;

        case 99:
            pickupType   = CommonPickupItemId_ShotgunShells;
            eventFlagIdx = EventFlag_M3S05_ShotgunShells;
            break;
    }

    Event_CommonItemTake(pickupType, eventFlagIdx);
}

void func_800D59D4(void) // 0x800D59D4
{
    VECTOR3 sfxPos = { MAP_POINTS[g_MapEventData->pointOfInterestIdx_5].positionX_0, Q12(-1.2f), MAP_POINTS[g_MapEventData->pointOfInterestIdx_5].positionZ_8 };

    Player_ItemRemove(InventoryItemId_BasementStoreroomKey, 1);
    Map_MessageWithSfx(27, Sfx_UseKey, &sfxPos);

    Savegame_MapMarkingSet(MapMarkFlag_FogHospital3F_NearElevatorBroken);
    Savegame_EventFlagSet(EventFlag_256);
}

void func_800D5A98(void) // 0x800D5A98
{
    g_BackgroundColor = 80;

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            Player_ControlFreeze();
            func_800862F8(0, FILE_TIM_IVIES_TIM, false);
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
            SD_Call(Sfx_Base);
            SysWork_StateStepIncrement(0);

        case 7:
            func_800862F8(2, FILE_1ST_2ZANKO80_TIM, false);
            MapMsg_DisplayAndHandleSelection(false, 22, 0, 0, 0, false);
            break;

        case 8:
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(0.0f), false);
            func_800862F8(2, FILE_1ST_2ZANKO80_TIM, false);
            break;

        case 9:
            SysWork_StateStepIncrementAfterFade(0, false, 0, Q12(0.0f), false);
            SysWork_StateStepIncrement(0);

        case 10:
            func_80086C58(&g_SysWork.playerWork_4C.player_0, 60);
            break;

        default:
            // Return to gameplay.
            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);
            break;
    }
}

const VECTOR3 D_800CB35C = { 0x00015199, 0x00000000, 0xFFFEC000 };

void func_800D5C98(void) // 0x800D5C98
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
            // Warp player.
            g_SysWork.playerWork_4C.player_0.position_18.vx = Q12(20.4f);
            g_SysWork.playerWork_4C.player_0.position_18.vz = Q12(-20.0f);
            g_SysWork.playerWork_4C.player_0.rotation_24.vy = Q12_ANGLE(90.0f);
            g_SysWork.playerWork_4C.player_0.field_E1_0     = 5;

            // Warp camera.
            Camera_PositionSet(NULL, Q12(18.29f), Q12(-0.92f), Q12(-19.71f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);
            Camera_LookAtSet(NULL, Q12(22.24f), Q12(-0.76f), Q12(-20.32f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);

            SysWork_StateStepIncrement(0);

        case 3:
            func_80086C58(&g_SysWork.playerWork_4C.player_0, 59);
            break;

        case 4:
            SysWork_StateStepIncrementDelayed(Q12(0.6f), false);
            break;

        case 5:
            func_8005DC1C(Sfx_Unk1532, &D_800CB35C, Q8_CLAMPED(0.5f), 0);
            SysWork_StateStepIncrement(0);

        case 6:
            SysWork_StateStepIncrementDelayed(Q12(0.8f), false);
            break;

        case 7:
            func_8005DC1C(Sfx_Unk1532, &D_800CB35C, Q8_CLAMPED(0.5f), 0);
            SysWork_StateStepIncrement(0);

        case 8:
            SysWork_StateStepIncrementDelayed(Q12(0.5f), false);
            break;

        case 9:
            func_8005DC1C(Sfx_Unk1532, &D_800CB35C, Q8_CLAMPED(0.5f), 0);
            SysWork_StateStepIncrement(0);

        case 10:
            SysWork_StateStepIncrementDelayed(Q12(1.0f), false);
            break;

        case 11:
            MapMsg_DisplayAndHandleSelection(false, 24, 0, 0, 0, false);
            break;

        case 12:
            func_80086C58(&g_SysWork.playerWork_4C.player_0, 60);
            break;

        default:
            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);

            // Warp player.
            g_SysWork.playerWork_4C.player_0.position_18.vx = Q12(20.6f);
            g_SysWork.playerWork_4C.player_0.position_18.vz = Q12(-20.0f);
            g_SysWork.playerWork_4C.player_0.rotation_24.vy = Q12_ANGLE(90.0f);

            func_80086470(3U, InventoryItemId_Lighter, 1, false);
            g_SysWork.playerWork_4C.player_0.field_E1_0 = 3;

            SysWork_StateStepIncrementAfterFade(0, false, 2, Q12(0.0f), false);
            vcReturnPreAutoCamWork(true);
            break;
    }
}

void func_800D5FC4(void) // 0x800D5FC4
{
    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            Player_ControlFreeze();
            SysWork_StateStepIncrementAfterFade(0, true, 2, Q12(0.0f), false);

            D_800DACE8 = Q12(-0.3f);

            SysWork_StateStepIncrement(0);

        case 1:
            func_80085DF0();
            break;

        case 2:
            // Warp player.
            g_SysWork.playerWork_4C.player_0.position_18.vx = Q12(20.3f);
            g_SysWork.playerWork_4C.player_0.position_18.vz = Q12(-20.0f);
            g_SysWork.playerWork_4C.player_0.rotation_24.vy = Q12_ANGLE(90.0f);

            // Warp camera.
            Camera_PositionSet(NULL, Q12(19.5f), Q12(-1.09f), Q12(-20.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);
            Camera_LookAtSet(NULL, Q12(23.49f), Q12(-0.85f), Q12(-19.74f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);

            func_80085EB8(0, &g_SysWork.playerWork_4C.player_0, 141, false);
            SysWork_StateStepIncrement(0);

        case 3:
            SysWork_StateStepIncrementDelayed(Q12(1.05f), false);
            break;

        case 4:
            g_SysWork.field_28 += g_DeltaTime;
            if (g_SysWork.field_28 > Q12(3.8f))
            {
                SysWork_StateStepIncrement(0);
                break;
            }

            if (g_SysWork.field_28 < Q12(3.2f))
            {
                if (D_800DACE8 > 0)
                {
                    D_800DACE8 -= g_DeltaTime;
                    if (D_800DACE8 < 0)
                    {
                        D_800DACE8 = ((u16)D_800DACE8 - Q12(0.3f)) - (Rng_Rand16() % Q12(0.1f));
                        func_8005DC1C(Sfx_Unk1536, &QVECTOR3(21.6f, 0.0f, -20.0f), Q8_CLAMPED(0.5f), 0);
                        break;
                    }
                }
                else
                {
                    D_800DACE8 += g_DeltaTime;
                    if (D_800DACE8 >= 0)
                    {
                        D_800DACE8 += Q12(0.05f) + (Rng_Rand16() % Q12(0.05f));
                        func_8005DC1C(Sfx_Unk1531, &QVECTOR3(21.6f, 0.0f, -20.0f), Q8_CLAMPED(0.5f), 0);
                        break;
                    }
                }
            }
            else
            {
                break;
            }
            break;

        case 5:
            func_80085EB8(2, &g_SysWork.playerWork_4C.player_0, 0, false);
            MapMsg_DisplayAndHandleSelection(false, 25, 0, 0, 0, false); // "Poured Disinfecting alcohol on the vines."
            break;

        case 6:
            func_80085EB8(3, &g_SysWork.playerWork_4C.player_0, 0, false);
            SysWork_StateStepIncrement(0);

        case 7:
            func_80085EB8(1, &g_SysWork.playerWork_4C.player_0, 0, false);
            break;

        default:
            // Return to gameplay.
            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);

            Savegame_EventFlagSet(EventFlag_M3S05_AlcoholPouredOnVines);
            SysWork_StateStepIncrementAfterFade(0, false, 2, Q12(0.0f), false);
            vcReturnPreAutoCamWork(true);
            break;
    }
}

void func_800D63C4(void) // 0x800D63C4
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
            MapMsg_DisplayAndHandleSelection(false, 26, 0, 0, 0, false);
            break;

        case 4:
            SysWork_StateStepIncrementDelayed(Q12(0.3f), false);
            break;

        case 5:
            func_80086C58(&g_SysWork.playerWork_4C.player_0, 60);
            break;

        default:
            // Return to gameplay.
            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);
            break;
    }
}

const VECTOR3 D_800CB3E0 = { 0x00015999, 0xFFFFFB34, 0xFFFEC000 };

const VECTOR3 D_800CB3EC = { 0x00015999, 0xFFFFF800, 0xFFFEC000 };

void func_800D64E0(void) // 0x800D64E0
{
    s32 i;

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            D_800DACEC = 0;
            Gfx_MapEffectsUpdate(7, 9, PrimitiveType_S32, &D_800DACEC, 0, 0x64000);
            break;

        case 5:
        case 7:
        case 9:
            D_800DACEC += Q12_MULT_PRECISE(g_DeltaTime, Q12(5.0f));
            break;

        case 11:
        case 12:
        case 13:
            D_800DACEC += Q12_MULT_PRECISE(g_DeltaTime, Q12(10.0f));
            break;

        case 14:
        case 15:
            D_800DACEC -= Q12_MULT_PRECISE(g_DeltaTime, Q12(20.0f));
            break;
    }

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            Player_ControlFreeze();
            SysWork_StateStepIncrementAfterFade(0, true, 2, 0, false);
            SysWork_StateStepIncrement(0);

        case 1:
            func_80085DF0();
            break;

        case 2:
            // Warp player.
            g_SysWork.playerWork_4C.player_0.position_18.vx = Q12(20.65f);
            g_SysWork.playerWork_4C.player_0.position_18.vz = Q12(-20.0f);
            g_SysWork.playerWork_4C.player_0.rotation_24.vy = Q12(0.25f);
            g_SysWork.playerWork_4C.player_0.field_E1_0 = 0;
            g_SysWork.playerWork_4C.player_0.field_E1_0 = 5;

            // Warp camera.
            Camera_PositionSet(NULL, Q12(17.15f), Q12(-1.32f), Q12(-18.71f), 0, 0, 0, 0, true);
            Camera_LookAtSet(NULL, Q12(20.96f), Q12(-1.13f), -Q12(19.93f), 0, 0, 0, 0, true);

            func_8003D03C();
            sharedFunc_800D2EB4_0_s00();
            SysWork_StateStepIncrement(0);

        case 3:
            func_80086C58(&g_SysWork.playerWork_4C.player_0, 59);
            break;

        case 4:
            func_8005DC1C(Sfx_Unk1532, &D_800CB35C, Q8(0.5f), 0);
            SysWork_StateStepIncrement(0);

        case 5:
            SysWork_StateStepIncrementDelayed(Q12(0.8f), false);
            break;

        case 6:
            func_8005DC1C(Sfx_Unk1532, &D_800CB35C, Q8(0.5f), 0);
            SysWork_StateStepIncrement(0);

        case 7:
            SysWork_StateStepIncrementDelayed(Q12(0.5f), false);
            break;

        case 8:
            func_8005DC1C(Sfx_Unk1532, &D_800CB35C, Q8(0.5f), 0);
            SysWork_StateStepIncrement(0);

        case 9:
            SysWork_StateStepIncrementDelayed(Q12(0.65f), false);
            break;

        case 10:
            sharedData_800D8568_1_s05.field_1  = 3;
            sharedData_800D8568_1_s05.flags_0  = 0x18;
            sharedData_800D8568_1_s05.field_C  = 0x12C;
            sharedData_800D8568_1_s05.field_12 = Q12(-0.2f);
            sharedData_800D8568_1_s05.field_14 = Q12(0.05f);
            sharedData_800D8568_1_s05.field_18 = Q12(0.6f);
            sharedData_800D8568_1_s05.field_1A = Q12(0.6f);
            sharedData_800D8568_1_s05.field_E  = Q12(-1.0f);
            sharedData_800D8568_1_s05.field_20 = Q12(21.6f);
            sharedData_800D8568_1_s05.field_24 = Q12(-20.0f);
            sharedData_800D8568_1_s05.field_3  = 0x20;
            sharedData_800D8568_1_s05.field_4  = 0x40;
            sharedData_800D8568_1_s05.field_6  = 0x2D;
            sharedData_800D8568_1_s05.field_5  = 0x20;
            sharedData_800D8568_1_s05.field_8  = 0x100;
            sharedData_800D8568_1_s05.field_A  = Q12(1.0f);
            sharedData_800D8568_1_s05.field_2  = 8;

            sharedFunc_800CAAD0_1_s05();
            SD_Call(Sfx_Unk1533);
            func_8008D438();
            SysWork_StateStepIncrement(0);

        case 11:
            func_80086C58(&g_SysWork.playerWork_4C.player_0, 60);
            break;

        case 12:
            func_80086C58(&g_SysWork.playerWork_4C.player_0, 81);

            // Warp camera.
            Camera_PositionSet(NULL, Q12(23.61f), Q12(-2.78f), Q12(-18.69f), 0, 0, 0, 0, true);
            Camera_LookAtSet(NULL, Q12(20.64f), Q12(-0.67f), Q12(-20.33f), 0, 0, 0, 0, true);
            break;

        case 13:
            SysWork_StateStepIncrementDelayed(Q12(3.0f), false);
            break;

        case 14:
            sharedData_800D8568_1_s05.field_1 = 1;
            sharedData_800D8568_1_s05.field_2 = 4;

            SysWork_StateStepIncrementDelayed(Q12(0.5f), false);
            break;

        case 15:
            SysWork_StateStepIncrementAfterFade(2, true, 0, 0, false);
            break;

        case 16:
            Sd_SfxStop(Sfx_Unk1533);
            SysWork_StateStepIncrement(0);

        case 17:
            SysWork_StateStepIncrementDelayed(Q12(1.0f), false);
            break;

        case 18:
            func_8005DC1C(Sfx_Unk1534, &D_800CB3E0, Q8(0.5f), 0);
            SysWork_StateStepIncrement(0);

        case 19:
            SysWork_StateStepIncrementDelayed(Q12(0.5f), false);
            break;

        default:
            // Return to gameplay.
            Player_ControlUnfreeze(true);
            SysWork_StateSetNext(SysState_Gameplay);

            for (i = 0; i < 450; i++)
            {
                if (sharedData_800DFB7C_0_s00[i].field_A == 8 || sharedData_800DFB7C_0_s00[i].field_A == 11)
                {
                    sharedData_800DFB7C_0_s00[i].field_A = 0;
                }
            }

            SysWork_StateStepIncrementAfterFade(0, false, 0, 0, false);
            Savegame_EventFlagSet(EventFlag_284);

            Gfx_MapInitMapEffectsUpdate(7, 4);
            func_8008D448();
            vcReturnPreAutoCamWork(true);

            g_SysWork.playerWork_4C.player_0.position_18.vx -= Q12(1.2f);

            SysWork_StateStepIncrementAfterFade(0, false, 2, 0, false);

            g_SysWork.playerWork_4C.player_0.field_E1_0 = 0;
            g_SysWork.playerWork_4C.player_0.field_E1_0 = 3;

            func_8003D01C();
            sharedFunc_800D2EF4_0_s00();
            break;
    }

    if (g_SysWork.sysStateStep_C[0] > 10 && g_SysWork.sysStateStep_C[0] < 16)
    {
        func_8005DE0C(Sfx_Unk1533, &D_800CB3EC, 0x80 - Q12_MULT_PRECISE(D_800DD190, 0x80), Q12(16.0f), 0);
    }
}

void func_800D6BB4(void) // 0x800D6BB4
{
    Event_ItemTake(InventoryItemId_VideoTape, DEFAULT_PICKUP_ITEM_COUNT, EventFlag_M3S05_PickupVideoTape, 15);
}

void func_800D6BE0(void) // 0x800D6BE0
{
    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            Player_ControlFreeze();
            SysWork_StateStepIncrement(0);

        case 1:
            func_80086E50(FILE_TIM_ALESSA_TIM, 0, 0);
            break;

        case 2:
            func_800862F8(2, 0, false);
            MapMsg_DisplayAndHandleSelection(false, 16, 0, 0, 0, false);
            break;

        case 3:
            func_80086F44(0, 0);
            break;

        default:
            // Return to gameplay.
            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);
            break;
    }
}

void func_800D6CF0(void) // 0x800D6CF0
{
    Event_ItemTake(InventoryItemId_ExaminationRoomKey, DEFAULT_PICKUP_ITEM_COUNT, EventFlag_M3S05_PickupExaminationRoomKey, 21);
}

void func_800D6D1C(void) // 0x800D6D1C
{
    if ((g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.skip_4) &&
        g_SysWork.sysStateStep_C[0] > 0 && g_SysWork.sysStateStep_C[0] < 11)
    {
        SysWork_StateStepSet(0, 15);
    }

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            Player_ControlFreeze();
            g_SysWork.field_30 = 20;

            // Warp camera.
            Camera_PositionSet(NULL, Q12(18.1f), Q12(-1.71f), Q12(-97.34f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);
            Camera_LookAtSet(NULL, Q12(20.04f), Q12(-0.74f), Q12(-100.7f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);

            D_800DAC74 = 0;
            func_8003D03C();
            sharedFunc_800D2EB4_0_s00();
            Game_TurnFlashlightOn();

            SysWork_StateStepIncrement(0);

        case 1:
            Map_MessageWithAudio(18, &D_800DAC74, &D_800DAC70);
            break;

        case 2:
            func_80086C58(&g_SysWork.playerWork_4C.player_0, 116);
            break;

        case 3:
            Map_MessageWithAudio(19, &D_800DAC74, &D_800DAC70);
            break;

        case 4:
            func_800865FC(true, 0, 0, Q12_ANGLE(0.0f), Q12(21.7f), Q12(-100.9f));
            func_800865FC(true, 0, 1, Q12_ANGLE(0.0f), Q12(21.9f), Q12(-100.3f));
            func_800865FC(true, 0, 2, Q12_ANGLE(0.0f), Q12(21.0f), Q12(-99.4f));
            SysWork_StateStepIncrement(0);

        case 5:
            func_800866D4(53, 3, false);
            SysWork_StateStepIncrementDelayed(Q12(2.0f), false);
            break;

        case 6:
            // Warp camera.
            Camera_PositionSet(NULL, Q12(18.44f), Q12(-4.54f), Q12(-100.98f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);
            Camera_LookAtSet(NULL, Q12(20.54f), Q12(-1.58f), Q12(-99.3f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);
            SysWork_StateStepIncrement(0);

        case 7:
            func_800866D4(53, 3, false);
            break;

        case 8:
            MapMsg_DisplayAndHandleSelection(false, 20, 0, 0, 0, false);
            break;

        case 9:
            func_80086E50(FILE_TIM_ALESSA_TIM, 0, 0);
            break;

        case 10:
            func_800862F8(2, FILE_1ST_2ZANKO80_TIM, false);
            MapMsg_DisplayAndHandleSelection(false, 16, 0, 0, 0, false);
            break;

        case 11:
            vcReturnPreAutoCamWork(true);
            SysWork_StateStepIncrement(0);

        case 12:
            func_80086F44(0, 0);
            break;

        case 13:
            MapMsg_DisplayAndHandleSelection(false, 17, 0, 0, 0, false);
            break;

        case 15:
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(0.0f), false);
            break;

        case 16:
            vcReturnPreAutoCamWork(true);

            // Warp player.
            g_SysWork.playerWork_4C.player_0.position_18.vx = Q12(21.0f);
            g_SysWork.playerWork_4C.player_0.position_18.vz = Q12(-99.4f);
            g_SysWork.playerWork_4C.player_0.rotation_24.vy = Q12_ANGLE(0.0f);

            SysWork_StateStepIncrementAfterFade(0, false, 0, Q12(0.0f), false);

        default:
            // Return to gameplay.
            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);

            func_8003D01C();
            sharedFunc_800D2EF4_0_s00();

            SysWork_StateStepIncrementAfterFade(0, false, 2, Q12(0.0f), false);

            Savegame_EventFlagSet(EventFlag_260);
            break;
    }
}

void func_800D719C(void) // 0x800D719C
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
            MapMsg_DisplayAndHandleSelection(false, 29, 0, 0, 0, false);
            break;

        default:
            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);
            break;
    }

    func_800894B8(0x60); // Hex?
}

void func_800D7280(void) // 0x800D7280
{
    Event_ItemTake(InventoryItemId_Hammer, DEFAULT_PICKUP_ITEM_COUNT, EventFlag_M3S05_PickupHammer, 31);
}

void func_800D72AC(void) // 0x800D72AC
{
    typedef enum _EventState
    {
        EventState_DontPushCabinet = 3,
        EventState_PushCabinet     = 4
    } e_EventState;

    s32    tmp0;
    q19_12 distAdd;

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            Player_ControlFreeze();
            D_800DACF0 = 0;
            SysWork_StateStepIncrement(0);

        case 1:
            func_80085DF0();
            break;

        case 2:
            MapMsg_DisplayAndHandleSelection(true, 28, EventState_PushCabinet, EventState_DontPushCabinet, 0, false); // "Do you want to push the cabinet?"
            break;

        case EventState_DontPushCabinet:
            // Return to gameplay.
            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);
            break;

        case EventState_PushCabinet:
            SysWork_StateStepIncrement(0);

        case 5:
            // Warp camera.
            Camera_PositionSet(NULL, Q12(57.86f), Q12(-3.62f), Q12(-21.1f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);
            Camera_LookAtSet(NULL, Q12(58.37f), Q12(-0.4f), Q12(-23.42f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);

            SysWork_StateStepIncrementAfterFade(0, true, 2, Q12(0.0f), false);
            func_80085EB8(0, &g_SysWork.playerWork_4C.player_0, 105, false);

            g_SysWork.playerWork_4C.player_0.position_18.vx = Q12(57.15f);
            g_SysWork.playerWork_4C.player_0.position_18.vz = Q12(-22.8f);
            g_SysWork.playerWork_4C.player_0.rotation_24.vy = Q12_ANGLE(90.0f);

            SD_Call(Sfx_Unk1535);
            SysWork_StateStepIncrement(0);

        case 6:
            tmp0 = Q12_MULT_PRECISE(g_DeltaTime, Q12(0.23f));
            distAdd = tmp0;
            g_SysWork.playerWork_4C.player_0.position_18.vx += distAdd;
            g_WorldObject0.position_1C.vx += distAdd;

            if (g_WorldObject0.position_1C.vx > Q12(61.0f))
            {
                SysWork_StateStepIncrement(0);

            }

            D_800DACF0 += ((u16) g_DeltaTime * 2);
            if (D_800DACF0 > Q12(1.0f))
            {
                D_800DACF0 = Q12(1.0f);
            }

            func_8005DE0C(Sfx_Unk1535, &g_WorldObject0.position_1C, D_800DACF0 >> 5, Q12(16.0f), 0);
            break;

        case 7:
            tmp0 = Q12_MULT_PRECISE(g_DeltaTime, Q12(0.23f));
            distAdd = tmp0;
            g_SysWork.playerWork_4C.player_0.position_18.vx += distAdd;
            g_WorldObject0.position_1C.vx += distAdd;

            if (g_WorldObject0.position_1C.vx > Q12(61.25f))
            {
                tmp0 = g_WorldObject0.position_1C.vx - Q12(61.25f);
                g_SysWork.playerWork_4C.player_0.position_18.vx -= tmp0;
                g_WorldObject0.position_1C.vx -= tmp0;
            }

            D_800DACF0 -= ((u16) g_DeltaTime * 2);
            if (D_800DACF0 < 0)
            {
                D_800DACF0 = 0;
            }

            func_8005DE0C(Sfx_Unk1535, &g_WorldObject0.position_1C, D_800DACF0 >> 5, Q12(16.0f), 0);
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(0.0f), false);

            if (g_SysWork.sysStateStep_C[0] != 7)
            {
                Savegame_EventFlagSet(EventFlag_M3S05_CabinetPushed);
            }
            break;

        default:
            // Return to gameplay.
            Player_ControlUnfreeze(true);
            SysWork_StateSetNext(SysState_Gameplay);

            SysWork_StateStepIncrementAfterFade(0, false, 2, Q12(0.0f), false);
            vcReturnPreAutoCamWork(true);
            SysWork_StateStepIncrementAfterFade(0, false, 0, Q12(0.0f), false);
            Sd_SfxStop(Sfx_Unk1535);
            break;
    }
}

INCLUDE_RODATA("maps/map3_s05/nonmatchings/map3_s05", sharedData_800CB088_3_s01);

INCLUDE_RODATA("maps/map3_s05/nonmatchings/map3_s05", sharedData_800CB094_3_s01);

#include "maps/shared/sharedFunc_800D15F0_3_s01.h" // 0x800D76D8

void Map_WorldObjectsInit(void) // 0x800D8424
{
    D_800DD528 = 0;
    D_800DD52A = 0;

    WorldObjectInit(&g_WorldObject7, "HAMMER_H", 140.4485f, -0.5f, -18.9f, -87.05f, -73.2f, 0.0f);

    WorldObjectInit(&g_WorldObject2, "TAPE_HID", 59.64f, -0.85f, -100.27f, 0.0f, 7.5f, 0.0f);

    WorldObjectInit(&g_WorldObject3, "BED3_HID", 19.6f, 0.0f, -99.6f, 0.0f, 90.0f, 0.0f);

    WorldObjectInit(&g_WorldObject4, "KEY_HIDE", 20.6587f, -0.81055f, -98.93555f, 0.0f, -31.7f, 0.0f);

    WorldObjectInit(&g_WorldObject0, "TANA_HID", 60.0f, 0.0f, -21.6f, 0.0f, 180.0f, 0.0f);

    if (Savegame_EventFlagGet(EventFlag_M3S05_CabinetPushed))
    {
        g_WorldObject0.position_1C.vx = Q12(61.25f);
    }

    WorldObject_ModelNameSet(&g_WorldObject5, "DOR1_HID");
    WorldObject_ModelNameSet(&g_WorldObject6, "DOR2_HID");

    Math_Vector3Set(&D_800DD420, Q12(20.0f), Q12(0.0f), Q12(-20.0f));
    Math_Vector3Set(&D_800DD430, Q12(19.9998f), Q12(-0.682f), Q12(-21.05005f));
    Math_SetSVectorFast(&D_800DD440, Q12_ANGLE(0.0f), Q12_ANGLE(180.0f), Q12_ANGLE(0.0f));
    Math_SetSVectorFast(&D_800DD448, Q12_ANGLE(58.05f), Q12_ANGLE(180.0f), Q12_ANGLE(0.0f));

    WorldObjectNoRotInit(&g_WorldObject_Dr[0], "DR1L_HID", 19.1f, 0.0f, 59.1f);

    WorldObjectNoRotInit(&g_WorldObject_Dr[1], "DR1R_HID", 19.1f, 0.0f, 59.1f);

    WorldObjectNoRotInit(&g_WorldObject_Dr[2], "DR3L_HID", 19.1f, 0.0f, 59.1f);

    WorldObjectNoRotInit(&g_WorldObject_Dr[3], "DR3R_HID", 19.1f, 0.0f, 59.1f);

    WorldObjectNoRotInit(&g_WorldObject_Dr[4], "DR2L_HID", 19.1f, 0.0f, 59.1f);

    WorldObjectNoRotInit(&g_WorldObject_Dr[5], "DR2R_HID", 19.1f, 0.0f, 59.1f);

    WorldObject_ModelNameSet(&g_CommonWorldObjects[0], D_800A99E4.firstAidKitName_8);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[1], D_800A99E4.healthDrinkName_C);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[2], D_800A99E4.ampouleName_10);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[3], D_800A99E4.handgunBulletsName_14);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[4], D_800A99E4.shotgunShellsName_18);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[5], D_800A99E4.rifleShellsName_1C);
}

void Map_WorldObjectsUpdate(void) // 0x800D87AC
{
    VECTOR3 soundPos;
    s32     cellX;
    s32     cellZ;
    s32     projCellX;
    s32     projCellZ;
    s32     flags;
    s32     i;
    s32     newZ;
    MAP_CHUNK_CHECK_VARIABLE_DECL();

    cellX = g_SysWork.playerWork_4C.player_0.position_18.vx / CHUNK_CELL_SIZE;
    projCellX = (g_SysWork.playerWork_4C.player_0.position_18.vx > Q12(0.0f)) ? (cellX + 1) : (cellX - 1);

    cellZ = g_SysWork.playerWork_4C.player_0.position_18.vz / CHUNK_CELL_SIZE;
    projCellZ = (g_SysWork.playerWork_4C.player_0.position_18.vz > Q12(0.0f)) ? (cellZ + 1) : (cellZ - 1);

    flags = 0;
    func_80069844(0xFFFF);

    if (projCellX == 2 && projCellZ == -3 && !Savegame_EventFlagGet(EventFlag_M3S05_PickupVideoTape))
    {
        WorldGfx_ObjectAdd(&g_WorldObject2.object_0, &g_WorldObject2.position_1C, &g_WorldObject2.rotation_28);
    }

    if (projCellX == 1 && projCellZ == -3)
    {
        WorldGfx_ObjectAdd(&g_WorldObject3.object_0, &g_WorldObject3.position_1C, &g_WorldObject3.rotation_28);

        if (!Savegame_EventFlagGet(EventFlag_M3S05_PickupExaminationRoomKey))
        {
            WorldGfx_ObjectAdd(&g_WorldObject4.object_0, &g_WorldObject4.position_1C, &g_WorldObject4.rotation_28);
        }
    }

    if (projCellX == 2 && projCellZ == -1)
    {
        if (!Savegame_EventFlagGet(EventFlag_M3S05_CabinetPushed))
        {
            flags |= 1 << 1;
            Savegame_EventFlagSet(EventFlag_288);
        }
        else
        {
            flags |= 1 << 2;
            Savegame_EventFlagClear(EventFlag_288);
        }

        WorldGfx_ObjectAdd(&g_WorldObject0.object_0, &g_WorldObject0.position_1C, &g_WorldObject0.rotation_28);
    }

    if (projCellX == 1 && projCellZ == -1)
    {
        if (!Savegame_EventFlagGet(EventFlag_284))
        {
            WorldGfx_ObjectAdd(&g_WorldObject5, &D_800DD420, &D_800DD440);
            WorldGfx_ObjectAdd(&g_WorldObject6, &D_800DD420, &D_800DD440);
        }
        else
        {
            WorldGfx_ObjectAdd(&g_WorldObject6, &D_800DD430, &D_800DD448);
        }
    }

    if (projCellX == 4 && projCellZ == -1)
    {
        if (!Savegame_EventFlagGet(EventFlag_M3S05_PickupHammer))
        {
            WorldGfx_ObjectAdd(&g_WorldObject7.object_0, &g_WorldObject7.position_1C, &g_WorldObject7.rotation_28);
        }

        if (D_800DD528 == 0)
        {
            SD_Call(Sfx_Unk1503);
            D_800DD528++;
        }

        func_8005DE0C(Sfx_Unk1503, &D_800DACD4, Q8_CLAMPED(0.5f), Q12(16.0f), 0);
    }
    else if (D_800DD528)
    {
        Sd_SfxStop(Sfx_Unk1503);
        D_800DD528 = 0;
    }

    func_8006982C(flags);

    if (projCellX == 4 && projCellZ == -2)
    {
        if (D_800DD52A > Q12(0.0f))
        {
            D_800DD52A = CLAMP_LOW(D_800DD52A - g_DeltaTime, Q12(0.0f));
        }

        if (D_800DD52A == Q12(0.0f) && Rng_GenerateUInt(0, 63) == 0) // 1 in 64 chance.
        {
            D_800DD52A = Q12(0.8f);
            soundPos.vx = Rng_GenerateInt(Q12(137.5f), Q12(142.5f) - 1);
            soundPos.vy = -Rng_GenerateInt(0, 8191);
            soundPos.vx = Q12(-56.8f) - Rng_GenerateInt(0, Q12(6.4f) - 1);
            func_8005DC1C(Sfx_Unk1537, &soundPos, Rng_GenerateUInt(192, 255), 2);
        }
    }

    if (projCellX == 1 && projCellZ == 2)
    {
        if (g_SysWork.sysState_8 == SysState_Gameplay && g_WorldObject_Dr->position_1C.vz != Q12(59.1f))
        {
            newZ = Q12(59.1f);
            for (i = 5; i >= 0; i--)
            {
                g_WorldObject_Dr[i].position_1C.vz = newZ;
            }
        }

        for (i = 0; i < ARRAY_SIZE(g_WorldObject_Dr); i++)
        {
            WorldGfx_ObjectAdd(&g_WorldObject_Dr[i].object_0, &g_WorldObject_Dr[i].position_1C, &(SVECTOR3){ 0, 0, 0 });
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 0, 0, -1, 1) && PLAYER_IN_MAP_CHUNK(vz, 1, -2, -1, -2))
    {
        if (!Savegame_EventFlagGet(EventFlag_M3S05_Ampoule))
        {
            WorldGfx_ObjectAdd(&g_CommonWorldObjects[2], &g_CommonWorldObjectPoses[0].position_0, &g_CommonWorldObjectPoses[0].rotation_C);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 0, 0, -1, 1) && PLAYER_IN_MAP_CHUNK(vz, 1, -2, -1, -2))
    {
        if (!Savegame_EventFlagGet(EventFlag_M3S05_HealthDrink))
        {
            WorldGfx_ObjectAdd(&g_CommonWorldObjects[1], &g_CommonWorldObjectPoses[1].position_0, &g_CommonWorldObjectPoses[1].rotation_C);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, 2, -1, 2) && PLAYER_IN_MAP_CHUNK(vz, 1, -1, 0, 0))
    {
        if (!Savegame_EventFlagGet(EventFlag_M3S05_HandgunBullets))
        {
            WorldGfx_ObjectAdd(&g_CommonWorldObjects[3], &g_CommonWorldObjectPoses[2].position_0, &g_CommonWorldObjectPoses[2].rotation_C);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, 2, -1, 2) && PLAYER_IN_MAP_CHUNK(vz, 1, -1, 0, 0))
    {
        if (!Savegame_EventFlagGet(EventFlag_M3S05_ShotgunShells))
        {
            WorldGfx_ObjectAdd(&g_CommonWorldObjects[5], &g_CommonWorldObjectPoses[3].position_0, &g_CommonWorldObjectPoses[3].rotation_C);
        }
    }
}
