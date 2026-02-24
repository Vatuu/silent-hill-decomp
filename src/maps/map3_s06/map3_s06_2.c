#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "bodyprog/player_logic.h"
#include "main/rng.h"
#include "maps/map3/map3_s06.h"
#include "maps/characters/dahlia.h"

#include "maps/shared/sharedFunc_800D88AC_0_s00.h" // 0x800CFCD8

#include "maps/shared/sharedFunc_800D88C0_0_s00.h" // 0x800CFCEC

#include "maps/shared/sharedFunc_800D8904_0_s00.h" // 0x800CFD30

#include "maps/shared/sharedFunc_800D891C_0_s00.h" // 0x800CFD48

#include "maps/shared/sharedFunc_800D8928_0_s00.h" // 0x800CFD54

#include "maps/shared/sharedFunc_800D893C_0_s00.h" // 0x800CFD68

#include "maps/shared/sharedFunc_800D8950_0_s00.h" // 0x800CFD7C

#include "maps/shared/sharedFunc_800D8964_0_s00.h" // 0x800CFD90

#include "maps/shared/sharedFunc_800D8A00_0_s00.h" // 0x800CFE2C

#include "maps/shared/sharedFunc_800D9064_0_s00.h" // 0x800D0490

#include "maps/shared/sharedFunc_800D9078_0_s00.h" // 0x800D04A4

#include "maps/shared/sharedFunc_800D908C_0_s00.h" // 0x800D04B8

#include "maps/shared/sharedFunc_800D9188_0_s00.h" // 0x800D05B4

#include "maps/shared/Anim_StartKeyframeIdxGet.h" // 0x800D0668

#include "maps/shared/sharedFunc_800D923C_0_s00.h" // 0x800D0688

#include "maps/shared/sharedFunc_800D929C_0_s00.h" // 0x800D06E8

#include "maps/shared/Map_RoomIdxGet.h" // 0x800D06F8

#include "maps/shared/Map_RoomBgmInit_CheckCond.h" // 0x800D07A0

#include "maps/shared/Map_RoomBgmInit_3_s00_CondTrue.h" // 0x800D07D4

#include "maps/shared/Map_RoomBgmInit_3_s00_CondFalse.h" // 0x800D0814

void func_800D09B4(void) {}

#include "maps/shared/MapEvent_DoorJammed.h" // 0x800D09BC

#include "maps/shared/MapEvent_DoorLocked.h" // 0x800D0A50

void func_800D0AE4(void) {}

const char* MAP_MESSAGES[] = {
    #include "maps/shared/mapMsg_common.h"
    "~J0(1.5)\tWas_I_dreaming? ~E ",
    "~J0(2.6)\tYou_were_too_late. ~E ",
    "~J0(1.2)\tIt's_you... ~E ",
    "~J0(3.4)\tYes.__Dahlia_Gillespie. ~E ",
    "~J1(3.0)\tTell_me_everything_you_know. ~N\n\t\t\tWhat's_going_on? ",
    "~J1(1.5)\tDarkness. ",
    "~J1(3.9)\tThe_town_is_being_devoured ~N\n\t\t\tby_darkness. ",
    "~J1(5.8)\tStrength_must_overcome ~N\n\t\t\tpetty_desire. ~N\n\t\t\tChildish_sleep_talk. ",
    "~J1(3.4)\tI_knew_this_day_would_come. ",
    "~J1(4.0)\tWhat_are_you_talking_about? ~N\n\t\t\tI_don't_understand_a_word_of_this. ~E ",
    "~J0(3.8)\tBelieve_the_evidence ~N\n\t\t\tof_your_eyes. ",
    "~J0(5.3)\tThe_other_church_in_this_town. ~N\n\t\t\tThat_is_your_destination. ",
    "~J0(6.5)\tThis_is_beyond_my_abilities. ~N\n\t\t\tOnly_you_can_stop_it_now. ~E ",
    "~J0(5.0)\tHave_you_not_seen ~N\n\t\t\tthe_crest_marked ~N\n\t\t\ton_the_ground_all_over_town? ",
    "~J0(3.2)\tSo_that's_what_I_saw ~N\n\t\t\tin_the_schoolyard. ",
    "~J0(1.2)\tWhat_does_it_mean? ",
    "~J0(3.1)\tIt_is_the_mark_of_Samael... ",
    "~J0(2.8)\tDon't_let_it_be_completed. ~E ",
    "~J0(1.8)\tHey!__Wait! ~E ",
    "\tThe_elevator_doesn't ~N\n\tappear_to_be_working. ~E ",
    "~H\tThere_is_a_ ~C5 Hospital_map ~C7 . ~N\n\tTake_it? ~S4 ",
    "\tThere_is_an_ ~C2 Antique_shop_key ~C7 . ~N\n\tTake_it? ~S4 ",
    "\tThese_are_phones_and_phonebooks. ~N\n\tNo_need_to_examine_this. ~E ",
    "\tThese_are_phones_and_phonebooks. ",
    "\tI'll_copy_the_location_of ~N\n\tthe_antique_shop_to_the_map. ~E ",
    "\tThere's_a_vending_machine. ~N\n\tIt_doesn't_work. ~E ",
    "\tThere_is_a_newspaper. ",
    "\tThis_article's_been ~N\n\tclipped_out... ~E ",
    "\tNothing_unusual. ~E ",
    "\tThere's_a_white_board. ~N\n\tNothing_special_written_here. ~E ",
    "\tNothing_helpful. ~E ",
    "\tThe_phone's_out. ~N\n\tCan't_get_a_dial_tone. ~E "
};

void MapEvent_CommonItemTake(void) // 0x800D0AEC
{
    Event_CommonItemTake(CommonPickupItemId_FirstAidKit, EventFlag_M3S00_FirstAidKit);
}

void func_800D0B10(void) // 0x800D0B10
{
    const static VECTOR3 D_800CB21C = { Q12(61.72f), Q12(-0.8f), Q12(100.51f) };

    if (g_SysWork.sysStateStep_C[1] == 0)
    {
        func_8005DC1C(Sfx_MenuMap, &D_800CB21C, Q8_CLAMPED(0.5f), 0);
    }

    MapMsg_DisplayWithTexture(FILE_TIM_NEWSP1_TIM, Q12(0.0f), Q12(0.0f), 41);
    Savegame_EventFlagSet(EventFlag_203);
}

#include "maps/shared/SysWork_StateStepIncrementAfterTime.h" // 0x800D0B7C

void func_800D0C14(void) // 0x800D0C14
{
    // Skip.
    if ((g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.skip_4) &&
        g_SysWork.sysStateStep_C[0] >= 4 && g_SysWork.sysStateStep_C[0] < 30)
    {
        SysWork_StateStepSet(0, 30);
        Savegame_EventFlagSet(EventFlag_297);
    }

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            Player_ControlFreeze();
            g_SysWork.field_30 = 20;
            ScreenFade_ResetTimestep();
            g_SysWork.flags_22A4 |= SysFlag2_3;

            Sd_SfxStop(Sfx_Unk1522);

            Fs_QueueStartRead(FILE_ANIM_HSPTL2_DMS, FS_BUFFER_15);
            Fs_QueueWaitForEmpty();
            DmsHeader_FixOffsets(FS_BUFFER_15);

            g_CutsceneTimer = Q12(0.0f);
            D_800D2736 = 0;
            D_800D2737 = false;

            func_8003D03C();
            sharedFunc_800D2EB4_0_s00();

            D_800D2738 = 0;
            D_800D2734 = Q12(0.0f);

            SysWork_StateStepIncrement(0);
            break;

        case 1:
            SysWork_StateStepIncrementAfterFade(0, false, 0, Q12(0.0f), false);

            Chara_Load(0, Chara_Dahlia, &g_SysWork.npcCoords_FC0[0], CHARA_FORCE_FREE_ALL, NULL, NULL);
            func_80085EB8(0, &g_SysWork.playerWork_4C.player_0, 117, false);

            SysWork_StateStepIncrement(0);

        case 2:
            SysWork_StateStepIncrementAfterFade(1, false, 0, Q12(0.0f), false);
            func_80085EB8(2, &g_SysWork.playerWork_4C.player_0, 0, false);
            break;

        case 3:
            Chara_ProcessLoads();
            Chara_Spawn(Chara_Dahlia, 0, Q12(98.0f), Q12(100.0f), Q12_ANGLE(0.0f), 3);
            sharedFunc_800D88AC_0_s00(&g_SysWork.npcs_1A0[0]);

            D_800D2737 = true;
            SysWork_StateStepIncrement(0);

        case 4:
            Map_MessageWithAudio(15, &D_800D2736, &D_800D26D0);
            SysWork_StateStepIncrementAfterTime(&g_CutsceneTimer, Q12(6.0f), Q12(0.0f), Q12(39.0f), true, false);
            break;

        case 5:
            func_80085EB8(3, &g_SysWork.playerWork_4C.player_0, 0, false);
            D_800D2738 = 0;
            SysWork_StateStepIncrement(0);

        case 6:
            Map_MessageWithAudio(16, &D_800D2736, &D_800D26D0);
            SysWork_StateStepIncrementAfterTime(&g_CutsceneTimer, Q12(6.0f), Q12(0.0f), Q12(39.0f), true, false);

            if (D_800D2738 != 2)
            {
                g_SysWork.field_28 += g_DeltaTime;

                if (D_800D2738 == 0 && !(g_SysWork.field_28 <= Q12(0.3f)))
                {
                    func_8005DC1C(Sfx_DoorOpen0, &D_800D26F8, Q8_CLAMPED(0.5f), 0);
                    D_800D2738++;
                }
                else if (D_800D2738 == 1 && !(g_SysWork.field_28 <= Q12(1.6f)))
                {
                    func_8005DC1C(Sfx_DoorClose0, &D_800D26F8, Q8_CLAMPED(0.5f), 0);
                    D_800D2738++;
                }
            }
            break;

        case 7:
            if (!Sd_AmbientSfxInit())
            {
                SysWork_StateStepIncrement(0);
            }

        case 8:
            D_800D2734 += g_DeltaTime;
            if (D_800D2734 > Q12(2.0f) && g_SysWork.sysStateStep_C[0] == 8)
            {
                SysWork_StateStepSet(0, 9);
            }

            SysWork_StateStepIncrementAfterTime(&g_CutsceneTimer, Q12(6.0f), Q12(0.0f), Q12(39.0f), true, false);
            break;

        case 9:
            Map_MessageWithAudio(17, &D_800D2736, &D_800D26D0);
            break;

        case 10:
            SysWork_StateStepIncrementDelayed(Q12(1.5f), false);
            break;

        case 11:
            func_80085EB8(0, &g_SysWork.npcs_1A0[0], 11, false);
            SysWork_StateStepIncrement(0);

        case 12:
            Map_MessageWithAudio(18, &D_800D2736, &D_800D26D0);
            SysWork_StateStepIncrementAfterTime(&g_CutsceneTimer, Q12(6.5f), Q12(40.0f), Q12(60.0f), true, false);
            break;

        case 13:
            SysWork_StateStepIncrementAfterTime(&g_CutsceneTimer, Q12(6.5f), Q12(40.0f), Q12(60.0f), true, true);
            break;

        case 14:
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(0.0f), false);
            break;

        case 15:
            func_80085EB8(0, &g_SysWork.playerWork_4C.player_0, 51, false);
            func_80085EB8(0, &g_SysWork.npcs_1A0[0], 0, false);
            SysWork_StateStepIncrement(0);

        case 16:
            SysWork_StateStepIncrementAfterFade(2, false, 0, Q12(0.0f), false);
            g_CutsceneTimer = Q12(61.0f);
            break;

        case 17:
            SysWork_StateStepIncrementDelayed(Q12(2.0f), false);
            break;

        case 18:
            Map_MessageWithAudio(19, &D_800D2736, &D_800D26D0);
            SysWork_StateStepIncrementAfterTime(&g_CutsceneTimer, Q12(2.0f), Q12(61.0f), Q12(100.0f), true, false);
            break;

        case 19:
            func_80085EB8(0, &g_SysWork.npcs_1A0[0], 9, false);
            SysWork_StateStepIncrement(0);

        case 20:
            Map_MessageWithAudio(25, &D_800D2736, &D_800D26D0);
            SysWork_StateStepIncrementAfterTime(&g_CutsceneTimer, Q12(2.0f), Q12(61.0f), Q12(126.0f), true, false);

            if (g_CutsceneTimer >= Q12(120.0f))
            {
                Model_AnimFlagsClear(&g_SysWork.playerWork_4C.player_0.model_0, 2);
            }
            break;

        case 21:
            func_80085EB8(0, &g_SysWork.npcs_1A0[0], 10, false);
            Model_AnimFlagsSet(&g_SysWork.playerWork_4C.player_0.model_0, 2);
            SysWork_StateStepIncrement(0);

        case 22:
            Map_MessageWithAudio(28, &D_800D2736, &D_800D26D0);
            SysWork_StateStepIncrementAfterTime(&g_CutsceneTimer, Q12(10.0f), Q12(127.0f), Q12(177.0f), true, false);
            SysWork_StateStepIncrementDelayed(Q12(9.8f), false);
            break;

        case 23:
            func_80085EB8(0, &g_SysWork.npcs_1A0[0], 0, false);
            SysWork_StateStepIncrement(0);

        case 24:
            Map_MessageWithAudio(28, &D_800D2736, &D_800D26D0);
            SysWork_StateStepIncrementAfterTime(&g_CutsceneTimer, Q12(10.0f), Q12(127.0f), Q12(177.0f), true, false);
            break;

        case 25:
            Savegame_EventFlagSet(EventFlag_297);
            func_80085EB8(0, &g_SysWork.npcs_1A0[0], 11, false);
            SysWork_StateStepIncrement(0);

        case 26:
            SysWork_StateStepIncrementAfterTime(&g_CutsceneTimer, Q12(13.5f), Q12(178.0f), Q12(194.0f), true, true);
            break;

        case 27:
            func_80085EB8(0, &g_SysWork.playerWork_4C.player_0, 111, false);
            func_80088F94(&g_SysWork.npcs_1A0[0], 0, 0);
            D_800D2738 = 0;
            SysWork_StateStepIncrement(0);

        case 28:
            Map_MessageWithAudio(33, &D_800D2736, &D_800D26D0);

            if (D_800D2738 != 1)
            {
                g_SysWork.field_28 += g_DeltaTime;
                if (D_800D2738 == 0 && g_SysWork.field_28 > Q12(0.6f))
                {
                    func_8005DC1C(Sfx_DoorClose0, &D_800D26F8, Q8_CLAMPED(0.5f), 0);
                    D_800D2738++;
                }
            }

            SysWork_StateStepIncrementAfterTime(&g_CutsceneTimer, Q12(10.0f), Q12(199.0f), Q12(244.0f), true, false);
            break;

        case 29:
            SysWork_StateStepIncrementAfterTime(&g_CutsceneTimer, Q12(10.0f), Q12(199.0f), Q12(244.0f), true, true);
            break;

        case 30:
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(0.0f), false);
            break;

        case 31:
            g_CutsceneTimer = Q12(244.0f);
            D_800D2737 = false;
            SysWork_StateStepIncrement(0);
            break;

        case 32:
            if (Sd_AmbientSfxInit() == 0)
            {
                SysWork_StateStepIncrement(0);
            }
            else
            {
                break;
            }

        default:
            func_80085EB8(3, &g_SysWork.playerWork_4C.player_0, 0, false);

            // Return to gameplay.
            Player_ControlUnfreeze(true);
            SysWork_StateSetNext(SysState_Gameplay);
            vcReturnPreAutoCamWork(true);

            g_CutsceneTimer = NO_VALUE;

            func_8003D01C();
            sharedFunc_800D2EF4_0_s00();
            SysWork_StateStepIncrementAfterFade(0, false, 2, Q12(0.0f), false);
            SysWork_StateStepIncrementAfterFade(0, false, 0, Q12(0.0f), false);
            Savegame_EventFlagSet(EventFlag_295);
            SD_Call(19);

            func_80088F94(&g_SysWork.npcs_1A0[0], 0, 0);
            Model_AnimFlagsSet(&g_SysWork.playerWork_4C.player_0.model_0, 2);
            Game_TurnFlashlightOff();
            break;
    }

    if (g_CutsceneTimer >= Q12(0.0f))
    {
        Dms_CharacterGetPosRot(&g_SysWork.playerWork_4C.player_0.position_18, &g_SysWork.playerWork_4C.player_0.rotation_24, "HERO", g_CutsceneTimer, FS_BUFFER_15);
        if (D_800D2737)
        {
            Dms_CharacterGetPosRot(&g_SysWork.npcs_1A0[0].position_18, &g_SysWork.npcs_1A0[0].rotation_24, "DARIA", g_CutsceneTimer, FS_BUFFER_15);
        }

        vcChangeProjectionValue(Dms_CameraGetTargetPos(&D_800D2718, &D_800D2728, NULL, g_CutsceneTimer, FS_BUFFER_15));
        vcUserCamTarget(&D_800D2718, NULL, true);
        vcUserWatchTarget(&D_800D2728, NULL, true);
    }
}

void MapEvent_MapTake(void) // 0x800D17B0
{
    Event_MapTake(17, EventFlag_M3S00_PickupMap, 35);
}

void func_800D17D8(void) // 0x800D17D8
{
    Event_ItemTake(InventoryItemId_AntiqueShopKey, DEFAULT_PICKUP_ITEM_COUNT, EventFlag_M3S06_PickupAntiqueShopKey, 36);
}

void Map_WorldObjectsInit(void) // 0x800D1804
{
    WorldObjectInit(&g_WorldObject_SavePad, D_800A99E4.savePadName_4, 26.0f, -1.02f, 144.55f, 0.0f, 163.8f, 0.0f);

    WorldObjectInit(&g_WorldObject_Map, "MAP_HIDE", 24.6f, -1.56f, 143.16f, 0.0f, 180.0f, 0.0f);

    WorldObjectInit(&g_WorldObject_Map2, "MAP2_HID", 24.6f, -1.56f, 143.16f, 0.0f, 180.0f, 0.0f);

    WorldObjectInit(&g_WorldObject_Key, "KEY_HIDE", 95.734f, -0.8062f, 99.8885f, 0.0f, -35.9f, 0.0f);

    WorldObjectInit(&g_WorldObject_FirstAidKit, D_800A99E4.firstAidKitName_8, 27.6f, -0.45f, 143.6f, 0.0f, -90.0f, 0.0f);
}

void Map_WorldObjectsUpdate(void) // 0x800D197C
{
    MAP_CHUNK_CHECK_VARIABLE_DECL();

    if (PLAYER_IN_MAP_CHUNK(vx, 1, 1, -1, 1))
    {
        if (PLAYER_IN_MAP_CHUNK(vz, 1, 4, -1, 4))
        {
            WorldGfx_ObjectAdd(&g_WorldObject_SavePad.object_0, &g_WorldObject_SavePad.position_1C, &g_WorldObject_SavePad.rotation_28);

            if (!(Savegame_EventFlagGet(EventFlag_M3S00_PickupMap)))
            {
                WorldGfx_ObjectAdd(&g_WorldObject_Map.object_0, &g_WorldObject_Map.position_1C, &g_WorldObject_Map.rotation_28);
            }
            else
            {
                WorldGfx_ObjectAdd(&g_WorldObject_Map2.object_0, &g_WorldObject_Map2.position_1C, &g_WorldObject_Map2.rotation_28);
            }

            if (!(Savegame_EventFlagGet(EventFlag_M3S00_FirstAidKit)))
            {
                WorldGfx_ObjectAdd(&g_WorldObject_FirstAidKit.object_0, &g_WorldObject_FirstAidKit.position_1C, &g_WorldObject_FirstAidKit.rotation_28);
            }
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, 3, -1, 3))
    {
        if (PLAYER_IN_MAP_CHUNK(vz, 1, 3, -1, 3))
        {
            if (!Savegame_EventFlagGet(EventFlag_M3S06_PickupAntiqueShopKey) && Savegame_EventFlagGet(EventFlag_297))
            {
                WorldGfx_ObjectAdd(&g_WorldObject_Key.object_0, &g_WorldObject_Key.position_1C, &g_WorldObject_Key.rotation_28);
            }
        }
    }

    if (Savegame_EventFlagGet(EventFlag_M3S06_PickupAntiqueShopKey) && Savegame_EventFlagGet(EventFlag_M2S00_PickupMap))
    {
        Savegame_EventFlagSet(EventFlag_317);
    }
}
