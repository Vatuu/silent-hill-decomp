#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "bodyprog/player_logic.h"
#include "main/rng.h"
#include "maps/shared.h"
#include "maps/map4/map4_s04.h"
#include "maps/characters/Chara_Lisa.h"

#include "maps/shared/sharedFunc_800D88AC_0_s00.h" // 0x800D098C

#include "maps/shared/sharedFunc_800D88C0_0_s00.h" // 0x800D09A0

#include "maps/shared/sharedFunc_800D8904_0_s00.h" // 0x800D09E4

#include "maps/shared/sharedFunc_800D891C_0_s00.h" // 0x800D09FC

#include "maps/shared/sharedFunc_800D8928_0_s00.h" // 0x800D0A08

#include "maps/shared/sharedFunc_800D893C_0_s00.h" // 0x800D0A1C

#include "maps/shared/sharedFunc_800D8950_0_s00.h" // 0x800D0A30

#include "maps/shared/sharedFunc_800D8964_0_s00.h" // 0x800D0A44

#include "maps/shared/sharedFunc_800D8A00_0_s00.h" // 0x800D0AE0

#include "maps/shared/sharedFunc_800D9064_0_s00.h" // 0x800D1144

#include "maps/shared/sharedFunc_800D9078_0_s00.h" // 0x800D1158

#include "maps/shared/sharedFunc_800D908C_0_s00.h" // 0x800D116C

#include "maps/shared/sharedFunc_800D9188_0_s00.h" // 0x800D1268

#include "maps/shared/Anim_StartKeyframeIdxGet.h" // 0x800D1314

#include "maps/shared/sharedFunc_800D923C_0_s00.h" // 0x800D1334

#include "maps/shared/sharedFunc_800D929C_0_s00.h" // 0x800D1394

#include "maps/shared/Map_RoomIdxGet.h" // 0x800D13A4

void func_800D143C(s32 arg0) // 0x800D143C
{
    (arg0 != 0) ? func_800D1470() : func_800D14B0();
}

void func_800D1470(void) // 0x800D1470
{
    func_8003640C(!Savegame_EventFlagGet(EventFlag_237) ? (1 << 3) : (1 << 1));
}

//const u8 D_800CA964[8] = {0x80, 0x70, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00};
extern const u8 D_800CA964[];
INCLUDE_RODATA("asm/maps/map4_s04/nonmatchings/map4_s04_2", D_800CA964);

void func_800D14B0(void) // same as `func_800CFEEC` in map3_s02
{
    u16    flags;
    q19_12 fArg1;
    u8*    dataPtr;
    u8     data[8];
    s32    roomIdx;

    dataPtr = D_800D335C;
    roomIdx = g_SavegamePtr->mapRoomIdx_A5;

    if (g_GameWork.soundCmd_5B2 == 8)
    {
        fArg1 = Q12(240.0f);
        flags = 0xFE;
    }
    else if (g_GameWork.soundCmd_5B2 == 32)
    {
        fArg1 = Q12(0.15f);
        if (Savegame_EventFlagGet(EventFlag_338))
        {
            flags = 4;
            if (!Savegame_EventFlagGet(EventFlag_340))
            {
                flags = 2;
                if (Savegame_EventFlagGet(EventFlag_339))
                {
                    flags = 0xE;
                }
            }
        }
        else
        {
            flags = 1;
        }
    }
    else
    {
        flags = D_800D3364[roomIdx];
        fArg1 = Q12(0.15f);
    
        switch (roomIdx)
        {
            case 23:
            case 26:
            case 38:
            case 45:
                if (!(Savegame_EventFlagGet(EventFlag_285) || Savegame_EventFlagGet(EventFlag_286)))
                {
                    flags = 0x1E;
                }
                else if (Savegame_EventFlagGet(EventFlag_285))
                {
                    Savegame_EventFlagSet(EventFlag_286);
                }
                break;
    
            case 5:
            case 25:
            case 37:
                if (!Savegame_EventFlagGet(EventFlag_285) && Savegame_EventFlagGet(EventFlag_286))
                {
                    Savegame_EventFlagSet(EventFlag_285);
                    Savegame_EventFlagClear(EventFlag_286);
                }
    
                if (!Savegame_EventFlagGet(EventFlag_285))
                {
                    flags = 0x1FE;
                }
                else if (!Savegame_EventFlagGet(EventFlag_286))
                {
                    flags = 0x13E;
                }
    
                break;
    
            case 4:
                if (!Player_ItemRemove(InventoryItemId_ExaminationRoomKey, 0))
                {
                    flags = 1 << 0;
                }

            case 6:
            case 7:
            case 10:
            case 11:
            case 12:
            case 13:
            case 14:
            case 15:
            case 21:
            case 22:
            case 24:
            case 27:
            case 28:
            case 29:
            case 30:
            case 31:
            case 32:
            case 34:
            case 35:
            case 36:
            case 39:
            case 40:
            case 41:
            case 42:
            case 43:
            case 44:
            case 46:
            case 47:
                Savegame_EventFlagSet(EventFlag_286);
                break;
    
            case 3:
                if (g_GameWork.soundCmd_5B2 == 31)
                {
                    memcpy(data, D_800CA964, 8);
                    dataPtr = data;
    
                    if (!Savegame_EventFlagGet(EventFlag_293))
                    {
                        fArg1 = Q12(240.0f);
                        flags = 1 << 2;
                    } 
                    else if (!Savegame_EventFlagGet(EventFlag_298))
                    {
                        fArg1 = Q12(0.25f);
                        flags = 1 << 1;
                    } 
                    else if (!Savegame_EventFlagGet(EventFlag_299))
                    {
                        fArg1 = Q12(0.125f);
                        flags = 1 << 3;
                    } 
                    else 
                    {
                        fArg1 = Q12(240.0f);
                        if (!Savegame_EventFlagGet(EventFlag_294))
                        {
                            fArg1 = Q12(0.5f);
                            flags = (1 << 0) | (1 << 9);
                        } 
                        else 
                        {
                            flags = 1 << 0;
                        }
                    }
                }
                else
                {
                    flags = (1 << 0) | (1 << 9);
                }
                break;
    
            case 58:
                if (!Savegame_EventFlagGet(EventFlag_260))
                {
                    flags = 1 << 0;
                }
                break;
        }
    }

    func_80035F4C(flags, fArg1, dataPtr);
}

void func_800D1740(void) {}

#include "maps/shared/MapEvent_DoorJammed.h" // 0x800D1748

#include "maps/shared/MapEvent_DoorLocked.h" // 0x800D17DC

void func_800D1870(void) {}

#include "maps/shared/SysWork_StateStepIncrementAfterTime.h" // 0x800D1878

const char* MAP_MESSAGES[] = {
    #include "maps/shared/mapMsg_common.h"
    "~J0(1.8)\tWhere_am_I? ~E ",
    "~J1(1.0)\tHarry. ",
    "~J1(1.2)\tLisa... ",
    "~J1(1.5)\tThen_I'm_in_the_hospital. ",
    "~J1(2.4)\tYou_were_having_a_bad_dream. ",
    "~J1(0.8)\tWas_I? ",
    "~J1(4.2)\tHey,_you_don't_look_too_good. ~N\n\t\t\tAre_you_OK? ",
    "~J1(1.3)\tI'm_fine. ",
    "~J1(2.2)\tNothing_you_need_to ~N\n\t\t\tworry_about. ",
    "~J1(2.2)\tWell,_if_you're_sure... ~E ",
    "~J1(4.3)\tLisa... ~N\n\t\t\tDo_you_know_a_woman ~N\n\t\t\tnamed_Dahlia_Gillespie? ",
    "~J1(3.2)\tOh_yeah, ~N\n\t\t\tthat_crazy_Gillespie_lady. ",
    "~J1(2.3)\tShe's_kinda'_famous_around_here. ",
    "~J1(4.0)\tShe_never_sees_anybody, ~N\n\t\t\tso_I_don't_know ~N\n\t\t\tthat_much_about_her. ",
    "~J1(5.2)\tI_heard_her_kid_died_in_a_fire, ~N\n\t\t\tand_supposedly_she's_been_crazy ~N\n\t\t\tever_since. ~E ",
    "~J1(5.1)\tWell,_she_says_the_town_is_being ~N\n\t\t\tdevoured_by_the_darkness. ",
    "~J1(2.7)\tDo_you_have_any_idea ~N\n\t\t\twhat_she's_talking_about? ",
    "~J1(3.5)\tThe_town..._devoured ~N\n\t\t\tby_the_darkness. ",
    "~J1(2.1)\tYes,_I_think_I_do. ",
    "~J1(2.9)\tBefore_this_place_was_turned ~N\n\t\t\tinto_a_resort, ",
    "~J1(3.4)\tthe_townspeople_here_were ~N\n\t\t\ton_the_quiet_side. ",
    "~J1(4.1)\tEverybody_followed ~N\n\t\t\tsome_kind_of_queer_religion. ~E ",
    "~J1(4.8)\tWeird_occult_stuff... ~N\n\t\t\tBlack_magic,_that_kind_of_thing. ",
    "~J1(5.0)\tAs_young_people_moved_away, ~N\n\t\t\tthe_people_figured_they'd_been ~N\n\t\t\tsummoned_by_the_gods. ",
    "~J1(3.7)\tEvidently,_things_like_that ~N\n\t\t\tused_to_happen_around_here ~N\n\t\t\tall_the_time. ",
    "~J1(3.5)\tBefore_the_resort, ~N\n\t\t\tthere_really_wasn't ~N\n\t\t\tanything_else_out_here. ",
    "~J1(4.5)\tEveryone_was_so_flipped_out. ~N\n\t\t\tGotta_blame_it_on_something. ",
    "~J1(3.8)\tThen_a_lot_of_new_people ~N\n\t\t\tcame_in_and_everybody ~N\n\t\t\tclammed_up_about_it. ",
    "~J0(1.8)\tA_cult... ~E ",
    "~J0(4.8)\tLast_time_I_heard_anything ~N\n\t\t\tabout_it_was,_gosh,_years_ago... ",
    "~J1(4.4)\tWhen_several_people_connected ~N\n\t\t\twith_developing_the_town ~N\n\t\t\tdied_in_accidents. ",
    "~J1(2.0)\tPeople_said_it_was_a_curse. ",
    "~J1(4.2)\tI'm_sorry,_I'm_rambling... ~N\n\t\t\tI'll_shut_up. ~E ",
    "~J0(1.1)\tHarry! ~E ",
    "~J0(1.6)\tGlad_you're_OK. ~E ",
    "~J0(4.6)\tThank_God_you_came_back. ~N\n\t\t\tI_was_scared_to_be_here_all_alone. ",
    "~J0(2.5)\tI'm_here_now. ~N\n\t\t\tI_was_worried,_too. ",
    "~J0(1.6)\tI'm_real_happy_to_see_you. ~E ",
    "~J1(3.3)\tLisa,_can_you_tell_me ~N\n\t\t\thow_to_get_to_the_lake? ",
    "~J1(3.0)\tThe_lake? ~N\n\t\t\tYou_take_Bachman_Road. ",
    "~J1(1.5)\tThe_road's_blocked. ",
    "~J1(2.3)\tWell,_that's ~N\n\t\t\tthe_only_way_out_there. ",
    "~J1(1.3)\tAre_you_sure? ",
    "~J1(2.7)\tThere's_gotta_be_another_way. ~E ",
    "~J1(3.0)\tWait, ~N\n\t\t\tI_just_remembered_something. ",
    "~J1(0.6)\tWhat? ",
    "~J1(3.3)\tThere's_a_water_works_over_by ~N\n\t\t\tmy_old_elementary_school. ",
    "~J1(2.3)\tIt's_been_abandoned_for_years. ",
    "~J1(4.2)\tThere's_an_underground_tunnel ~N\n\t\t\tout_there_used_for_inspections, ~N\n\t\t\tor_something! ",
    "~J1(3.2)\tI_remember_hearing_it_runs ~N\n\t\t\tall_the_way_to_the_lake! ~E ",
    "~J1(0.9)\tReally?! ",
    "~J1(2.3)\tYou_think_I_can_get_to_the_lake ~N\n\t\t\tfrom_there? ",
    "~J1(3.1)\tI've_never_been_down ~N\n\t\t\tin_there_myself, ~N\n\t\t\tso_I'm_not_positive. ",
    "~J1(2.8)\tBesides,_it's_all_fenced_off ~N\n\t\t\tto_keep_people_out. ",
    "~J1(2.3)\tIf_there's_a_chance, ~N\n\t\t\tI've_got_to_try. ~E  ",
    "~J1(2.0)\tHarry,_don't_go! ",
    "~J1(4.2)\tI_don't_want_to_be_alone. ~N\n\t\t\tIt's_so_scary._I_can't_stand_it. ",
    "~J1(1.6)\tHow_about_coming_with_me? ",
    "~J1(2.6)\tThis_may_not_be_the_safest_place ~N\n\t\t\tin_the_world_either. ",
    "~J1(3.6)\tI_can't_promise_you_anything, ~N\n\t\t\tbut_I'll_do_my_best ~N\n\t\t\tto_protect_you. ",
    "~J1(4.2)\tNo... ~N\n\t\t\tsomehow_I_feel_I'm_not_supposed ~N\n\t\t\tto_leave_this_place. ",
    "~J1(4.0)\tOh,_Harry,_I'm_so_scared... ~N\n\t\t\tI'm_cold. ",
    "~J1(3.8)\tLook,_just_wait_here ~N\n\t\t\ta_little_longer. ",
    "~J1(3.0)\tI'll_be_back_as_soon_as ~N\n\t\t\tI_find_my_daughter. ~E ",
    "~J0(1.5)\tHarry... ~E ",
    "\tNothing_unusual. ~E ",
    "\tNothing_helpful. ~E "
};

INCLUDE_RODATA("asm/maps/map4_s04/nonmatchings/map4_s04_2", D_800CBB78);

INCLUDE_RODATA("asm/maps/map4_s04/nonmatchings/map4_s04_2", D_800CBB80);

INCLUDE_ASM("asm/maps/map4_s04/nonmatchings/map4_s04_2", func_800D1910);

// TODO: Move rodata into funcs once above is decomped.
extern s8 D_800CBB78[];
extern s8 D_800CBB80[];

void func_800D23E4(void) // 0x800D23E4
{
    VECTOR3  lightIntPos;
    SVECTOR3 unused;

    if ((g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.skip_4) &&
        g_SysWork.sysStateStep_C[0] > 0 && g_SysWork.sysStateStep_C[0] < 22)
    {
        SysWork_StateStepSet(0, 26);
    }

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            Player_ControlFreeze();
            Game_TurnFlashlightOn();
            D_800D6EF8 = 0;

            Fs_QueueStartRead(FILE_ANIM_HSPTL5_DMS, FS_BUFFER_15);
            Fs_QueueWaitForEmpty();
            DmsHeader_FixOffsets(FS_BUFFER_15);

            D_800D6EF4 = 0;

            // Load Lisa character.
            Chara_Load(0, Chara_Lisa, &g_SysWork.npcCoords_FC0[0], CHARA_FORCE_FREE_ALL, NULL, NULL);
            Chara_ProcessLoads();
            Chara_Spawn(Chara_Lisa, 0, Q12(60.0f), Q12(140.0f), FP_ANGLE(0.0f), 3);

            func_8003D03C();
            sharedFunc_800D2EB4_0_s00();

            D_800D6EF8 = 0;

            g_SysWork.field_235C = NULL;
            g_SysWork.field_236C = NULL;
            g_SysWork.field_2378 = Q12(1.2f);

            func_8008D438();

            g_SysWork.field_30 = 20;
            ScreenFade_ResetTimestep();

            D_800D37C1            = 0;
            g_SysWork.flags_22A4 |= 8;
            func_8005DC1C(Sfx_DoorClose0, &QVECTOR3(54.6f, -1.2f, 141.5f), Q8_CLAMPED(0.5f), 0);
            SysWork_StateStepIncrement(0);
            break;

        case 1:
            func_80085EB8(0, &g_SysWork.npcs_1A0[0], 11, false);
            func_80085EB8(0, &g_SysWork.player_4C.chara_0, 51, false);
            SysWork_StateStepIncrement(0);
            break;

        case 2:
            func_80085EB8(2, &g_SysWork.npcs_1A0[0], 0, false);
            SysWork_StateStepIncrementAfterFade(2, false, 0, Q12(0.0f), false);
            break;

        case 3:
            func_80085EB8(3, &g_SysWork.npcs_1A0[0], 0, false);
            SysWork_StateStepIncrement(0);

        case 4:
            Map_MessageWithAudio(48, &D_800D6EF8, &D_800D3778);
            SysWork_StateStepIncrementAfterTime(&D_800D6EF4, Q12(6.5f), Q12(0.0f), Q12(20.0f), true, false);
            break;

        case 5:
            SysWork_StateStepIncrementAfterTime(&D_800D6EF4, Q12(6.5f), Q12(0.0f), Q12(20.0f), true, true);
            break;

        case 6:
            func_80085EB8(0, &g_SysWork.npcs_1A0[0], 12, false);
            g_SysWork.field_2378 = Q12(1.0f);
            SysWork_StateStepIncrement(0);

        case 7:
            Map_MessageWithAudio(49, &D_800D6EF8, &D_800D3778);
            SysWork_StateStepIncrementAfterTime(&D_800D6EF4, Q12(8.0f), Q12(21.0f), Q12(54.0f), true, false);

            if (D_800D6EF4 >= Q12(32.0f) && D_800D37C1 == 0)
            {
                func_80085EB8(0, &g_SysWork.player_4C.chara_0, 134, false);
                D_800D37C1++;
            }
            break;

        case 8:
            SysWork_StateStepIncrementAfterTime(&D_800D6EF4, Q12(8.0f), Q12(21.0f), Q12(54.0f), true, true);

            if (D_800D6EF4 >= Q12(32.0f) && D_800D37C1 == 0)
            {
                func_80085EB8(0, &g_SysWork.player_4C.chara_0, 134, false);
                D_800D37C1++;
            }
            break;

        case 9:
            func_80085EB8(0, &g_SysWork.player_4C.chara_0, 51, false);
            func_80085EB8(0, &g_SysWork.npcs_1A0[0], 5, false);

            g_SysWork.field_2378 = Q12(1.2f);
            D_800D6EF4           = Q12(55.0f);

            SysWork_StateStepIncrement(0);

        case 10:
            Map_MessageWithAudio(50, &D_800D6EF8, &D_800D3778);
            break;

        case 11:
            D_800D6EF4 = Q12(56.0f);
            SysWork_StateStepIncrement(0);

        case 12:
            Map_MessageWithAudio(53, &D_800D6EF8, &D_800D3778);
            break;

        case 13:
            SysWork_StateStepIncrementDelayed(Q12(2.0f), false);
            break;

        case 14:
            Map_MessageWithAudio(59, &D_800D6EF8, &D_800D3778);
            break;

        case 15:
            Map_MessageWithAudio(65, &D_800D6EF8, &D_800D3778);
            break;

        case 16:
            D_800D6EF4           = Q12(57.0f);
            g_SysWork.field_2378 = Q12(1.0f);
            Map_MessageWithAudio(70, &D_800D6EF8, &D_800D3778);
            break;

        case 17:
            func_80085EB8(0, &g_SysWork.npcs_1A0[0], 13, false);
            g_SysWork.field_2378 = Q12(1.2f);
            SysWork_StateStepIncrement(0);

        case 18:
            Map_MessageWithAudio(79, &D_800D6EF8, &D_800D3778);
            SysWork_StateStepIncrementAfterTime(&D_800D6EF4, Q12(10.0f), Q12(58.0f), Q12(126.0f), true, false);
            break;

        case 19:
            SysWork_StateStepIncrementAfterTime(&D_800D6EF4, Q12(10.0f), Q12(58.0f), Q12(126.0f), true, true);
            break;

        case 20:
            Model_AnimFlagsClear(&g_SysWork.player_4C.chara_0.model_0, 2);
            func_80085EB8(0, &g_SysWork.player_4C.chara_0, 53, false);
            func_80085EB8(0, &g_SysWork.npcs_1A0[0], 21, false);
            SysWork_StateStepIncrement(0);

        case 21:
            SysWork_StateStepIncrementAfterTime(&D_800D6EF4, Q12(10.0f), Q12(127.0f), Q12(151.0f), false, true);
            break;

        case 22:
            func_8005DC1C(Sfx_DoorOpen0, &QVECTOR3(54.6f, -1.2f, 141.5f), Q8_CLAMPED(0.5f), 0);
            func_80085EB8(0, &g_SysWork.player_4C.chara_0, 51, false);
            SysWork_StateStepIncrement(0);

        case 23:
            SysWork_StateStepIncrementAfterTime(&D_800D6EF4, Q12(10.0f), Q12(127.0f), Q12(160.0f), false, true);
            break;

        case 24:
            func_8005DC1C(Sfx_DoorClose0, &QVECTOR3(54.6f, -1.2f, 141.5f), Q8_CLAMPED(0.5f), 0);
            SysWork_StateStepIncrement(0);

        case 25:
            SysWork_StateStepIncrementAfterTime(&D_800D6EF4, Q12(10.0f), Q12(127.0f), Q12(200.0f), true, true);
            break;

        case 26:
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(0.0f), false);
            break;

        default:
            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);

            Sd_EngineCmd(19);

            Model_AnimFlagsSet(&g_SysWork.player_4C.chara_0.model_0, 2);

            func_8003D01C();
            func_80088F94(&g_SysWork.npcs_1A0[0], 0, 0);

            Savegame_MapMarkingSet(MapMarkFlag_AltHospital1F_RightEntranceBroken);
            Savegame_EventFlagSet(EventFlag_340);

            SysWork_StateStepIncrementAfterFade(0, false, 2, Q12(0.0f), false);
            SysWork_StateStepIncrementAfterFade(0, false, 0, Q12(0.0f), false);

            func_8008D448();
            func_8003EBA0();

            g_SysWork.field_2378 = Q12(1.0f);
            D_800D6EF4           = -1;

            vcReturnPreAutoCamWork(false);
            func_8003D01C();
            sharedFunc_800D2EF4_0_s00();
            break;
    }

    if (D_800D6EF4 >= Q12(0.0f))
    {
        Dms_CharacterGetPosRot(&g_SysWork.player_4C.chara_0.position_18, &g_SysWork.player_4C.chara_0.rotation_24, D_800CBB78, D_800D6EF4, FS_BUFFER_15);
        Dms_CharacterGetPosRot(&g_SysWork.npcs_1A0[0].position_18, &g_SysWork.npcs_1A0[0].rotation_24, D_800CBB80, D_800D6EF4, FS_BUFFER_15);
        vcChangeProjectionValue(Dms_CameraGetTargetPos(&D_800D6ED8, &D_800D6EE8, NULL, D_800D6EF4, FS_BUFFER_15));
        vcUserCamTarget(&D_800D6ED8, NULL, true);
        vcUserWatchTarget(&D_800D6EE8, NULL, true);

        // "LIGHT", cutscene light position? (TODO: Rename `g_SysWork.field_2360`?)
        Dms_CharacterGetPosRot(&g_SysWork.field_2360, &unused, "LIGHT", D_800D6EF4, FS_BUFFER_15);

        // "L_INT", interior light or intersection point?
        Dms_CharacterGetPosRot(&lightIntPos, &unused, "L_INT", D_800D6EF4, FS_BUFFER_15);

        // Light angle? (TODO: Rename `g_SysWork.field_2370`?)
        g_SysWork.field_2370.vx = -ratan2(lightIntPos.vy - g_SysWork.field_2360.vy, Math_Vector2MagCalc(lightIntPos.vx - g_SysWork.field_2360.vx, lightIntPos.vz - g_SysWork.field_2360.vz));
        g_SysWork.field_2370.vy = ratan2(lightIntPos.vx - g_SysWork.field_2360.vx, lightIntPos.vz - g_SysWork.field_2360.vz);
        g_SysWork.field_2370.vz = FP_ANGLE(0.0f);
    }
}

void func_800D2D6C(void)
{
    WorldObjectInit(&g_WorldObjectSavepad, 106.687f, -1.02f, 144.601f, 0.0f, 163.0f, 0.0f);
    WorldObject_ModelNameSet(&g_WorldObjectSavepad.object_0, D_800A99E4.savePadName_4);

    Math_Vector3Set(&g_WorldObject0.position_1C, Q12(57.8f), Q12(0.0f), Q12(0.0f));
    WorldObject_ModelNameSet(&g_WorldObject0.object_0, "ISU_HIDE");
}

void func_800D2DF4(void)
{
    MAP_CHUNK_CHECK_VARIABLE_DECL();

    if (PLAYER_IN_MAP_CHUNK(vx, 1, 3, -1, 3) && PLAYER_IN_MAP_CHUNK(vz, 1, 4, -1, 4))
    {
        g_WorldGfx_ObjectAdd(&g_WorldObjectSavepad.object_0, &g_WorldObjectSavepad.position_1C, &g_WorldObjectSavepad.rotation_28);
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, 2, -1, 2) && PLAYER_IN_MAP_CHUNK(vz, 1, 4, -1, 4))
    {
        if (Savegame_EventFlagGet(EventFlag_337) && !Savegame_EventFlagGet(EventFlag_338))
        {
            g_WorldGfx_ObjectAdd(&g_WorldObject0.object_0, &g_WorldObject0.position_1C, &(SVECTOR3){});
        }
    }
}
