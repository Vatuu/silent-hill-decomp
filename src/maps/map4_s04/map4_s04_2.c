#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "bodyprog/gfx/text_draw.h"
#include "bodyprog/sound_system.h"
#include "bodyprog/player_logic.h"
#include "main/rng.h"
#include "maps/map4/map4_s04.h"
#include "maps/characters/lisa.h"

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

#include "maps/shared/Map_RoomBgmInit_CheckCond.h" // 0x800D143C

#include "maps/shared/Map_RoomBgmInit_3_s02_CondTrue.h" // 0x800D1470

#include "maps/shared/Map_RoomBgmInit_3_s02_CondFalse.h" // 0x800D14B0

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

void func_800D1910(void) // 0x800D1910
{
    Gfx_DebugStringPosition(30, 30);
    ClearImage(&D_800D3720, 0, 0, 0);

    // GPU packet setup.
    {
        typedef struct
        {
            SPRT*      sprt_0;
            DR_TPAGE*  tpage_4;
            DR_STP*    stp_8;
            DR_AREA*   area_C;
            DR_OFFSET* offset_10;
        } s_ScratchData;

        s32            layer;
        s32            i;
        s_ScratchData* scratch;

        scratch = PSX_SCRATCH_ADDR(0);

        scratch->sprt_0 = (SPRT*)GsOUT_PACKET_P;
        for (layer = 0; layer < 4; layer++)
        {
            for (i = 0; i < 2; i++)
            {
                s32 colorVal;
                u8  tpageAbr;

                // @hack Might have been a switch instead?
                setXY0Fast(scratch->sprt_0,
                           (i * 256) - ((layer < 2) ? ((layer == 1) ? 159 : 161) : 160),
                           ((layer < 2) ? -112 : ((layer == 2) ? -111 : -113)));

                setUV0(scratch->sprt_0, 0, 0);

                switch (layer)
                {
                    case 0:
                        colorVal = 0x20;
                        tpageAbr = 1;
                        break;

                    case 1:
                        colorVal = 0x40;
                        tpageAbr = 0;
                        break;

                    default:
                        colorVal = 0x80;
                        tpageAbr = 0;
                }

                if (layer == 3)
                {
                    setRGBC0(scratch->sprt_0, 0x80, 0x80, 0x80, PRIM_RECT | RECT_TEXTURE);
                }
                else
                {
                    setRGBC0(scratch->sprt_0, colorVal, colorVal, colorVal, PRIM_RECT | RECT_TEXTURE | RECT_BLEND);
                }

                setWH(scratch->sprt_0, (i == 0) ? 256 : 64, 224);
                addPrimFast(&g_OrderingTable0[g_ActiveBufferIdx].org[2], scratch->sprt_0, 4);

                scratch->sprt_0++;
                scratch->tpage_4 = (DR_TPAGE*)scratch->sprt_0;

                setDrawTPage(scratch->tpage_4, 0, 0, getTPageN(2, tpageAbr, (i * 4) + 21, 1));

                addPrim(&g_OrderingTable0[g_ActiveBufferIdx].org[2], scratch->tpage_4);
                scratch->tpage_4++;
                scratch->sprt_0 = (SPRT*)scratch->tpage_4;
            }
        }

        // First `DR_AREA`.
        scratch->area_C = (DR_AREA*)scratch->sprt_0;
        SetDrawArea(scratch->area_C, &D_800D3710[g_ActiveBufferIdx == 0 ? 1 : 0]);
        addPrim(&g_OrderingTable0[g_ActiveBufferIdx].org[2], scratch->area_C);
        scratch->area_C++;

        // Second `DR_AREA`.
        SetDrawArea(scratch->area_C, &D_800D3720);
        addPrim(&g_OrderingTable0[g_ActiveBufferIdx].org[ORDERING_TABLE_SIZE - 1], scratch->area_C);
        scratch->area_C++;

        // First `DR_OFFSET`.
        scratch->offset_10 = (DR_OFFSET*)scratch->area_C;
        SetDrawOffset(scratch->offset_10, &D_800D3728[g_ActiveBufferIdx == 0 ? 1 : 0]);
        addPrim(&g_OrderingTable0[g_ActiveBufferIdx].org[2], scratch->offset_10);
        scratch->offset_10++;

        // Second `DR_OFFSET`.
        SetDrawOffset(scratch->offset_10, &D_800D3730);
        addPrim(&g_OrderingTable0[g_ActiveBufferIdx].org[ORDERING_TABLE_SIZE - 1], scratch->offset_10);
        scratch->offset_10++;

        // First `DR_STP` (disabled).
        scratch->stp_8 = (DR_STP*)scratch->offset_10;
        SetDrawStp(scratch->stp_8, 0);
        addPrim(&g_OrderingTable0[g_ActiveBufferIdx].org[2], scratch->stp_8);
        scratch->stp_8++;

        // Second `DR_STP` (enabled).
        SetDrawStp(scratch->stp_8, 1);
        addPrim(&g_OrderingTable0[g_ActiveBufferIdx].org[ORDERING_TABLE_SIZE - 1], scratch->stp_8);
        scratch->stp_8++;

        GsOUT_PACKET_P = (PACKET*)scratch->stp_8;
    }

    if (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.skip_4 &&
        g_SysWork.sysStateStep_C[0] > 0 && g_SysWork.sysStateStep_C[0] < 14)
    {
        SysWork_StateStepSet(0, 14);
    }

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            Player_ControlFreeze();
            D_800D6EF8 = 0;

            Fs_QueueStartRead(FILE_ANIM_HSPTL4_DMS, FS_BUFFER_15);
            Fs_QueueWaitForEmpty();
            DmsHeader_FixOffsets((s_DmsHeader*)FS_BUFFER_15);

            D_800D6EF4 = 0;

            Chara_Load(0, Chara_Lisa, &g_SysWork.npcCoords_FC0[0], CHARA_FORCE_FREE_ALL, NULL, NULL);
            Chara_ProcessLoads();
            Chara_Spawn(Chara_Lisa, 0, Q12(70.0f), Q12(150.0f), 0, 3);
            func_8003D03C();
            sharedFunc_800D2EB4_0_s00();

            D_800D6EF8 = 0;

            // TODO: Find correct order. Looking at other functions, seems to be random.
            g_SysWork.field_235C = NULL;
            g_SysWork.field_236C = NULL;
            g_SysWork.pointLightIntensity_2378 = Q12(1.0f);
            Math_Vector3Set(&g_SysWork.pointLightPosition_2360, Q12(57.0f), Q12(-3.0f), Q12(141.8f));

            // TODO: `Math_SetSVectorFast(&g_SysWork.pointLightRot_2370, Q12_ANGLE(-90.0f), 0, 0);` doesn't match.
            *(s32*)&g_SysWork.pointLightRot_2370.vx = 0xFC00; // `Q12_ANGLE(-90.0f)`
            (&g_SysWork.pointLightRot_2370)->vz     = 0;

            func_8008D438();

            g_SysWork.field_30 = 20;
            ScreenFade_ResetTimestep();
            g_SysWork.flags_22A4 |= SysFlag2_3;

            func_80085EB8(0, &g_SysWork.playerWork_4C.player_0, 117, false);
            D_800D37C0 = 0;

            Gfx_MapInitMapEffectsUpdate(15, 15);
            SysWork_StateStepIncrement(0);
            g_WorldObject0.position_1C.vz = Q12(141.0f);
            break;

        case 1:
            func_80085EB8(2, &g_SysWork.playerWork_4C.player_0, 0, false);
            func_80085EB8(0, &g_SysWork.npcs_1A0[0], 9, false);

            D_800D37C0 = 1;

            SysWork_StateStepIncrement(0);

        case 2:
            SysWork_StateStepIncrementAfterFade(2, false, 0, Q12(1.0f), false);
            break;

        case 3:
            func_80085EB8(3, &g_SysWork.playerWork_4C.player_0, 0, false);
            SysWork_StateStepIncrement(0);
            break;

        case 4:
            SysWork_StateStepIncrementDelayed(Q12(1.2f), false);
            SysWork_StateStepIncrementAfterTime(&D_800D6EF4, Q12(8.0f), Q12(0.0f), Q12(23.0f), true, false);
            break;

        case 5:
            Map_MessageWithAudio(15, &D_800D6EF8, &D_800D3734); // "Where am I?"
            SysWork_StateStepIncrementAfterTime(&D_800D6EF4, Q12(8.0f), Q12(0.0f), Q12(23.0f), true, false);
            break;

        case 6:
            D_800D6EF4                    = Q12(24.0f);
            g_WorldObject0.position_1C.vz = Q12(140.8f);

            func_80085EB8(0, &g_SysWork.playerWork_4C.player_0, 135, false);
            SysWork_StateStepIncrement(0);

        case 7:
            Map_MessageWithAudio(16, &D_800D6EF8, &D_800D3734); // "Harry. Lisa... Then I'm in the hospital."
            break;

        case 8:
            Map_MessageWithAudio(25, &D_800D6EF8, &D_800D3734);
            break;

        case 9:
            Map_MessageWithAudio(30, &D_800D6EF8, &D_800D3734);
            break;

        case 10:
            Map_MessageWithAudio(37, &D_800D6EF8, &D_800D3734);
            break;

        case 11:
            Map_MessageWithAudio(44, &D_800D6EF8, &D_800D3734);
            SysWork_StateStepIncrementAfterTime(&D_800D6EF4, Q12(10.0f), Q12(25.0f), Q12(46.0f), true, false);
            g_WorldObject0.position_1C.vz = Q12(140.95f);
            break;

        case 12:
            func_80086C58(&g_SysWork.npcs_1A0[0], 10);
            SysWork_StateStepIncrementAfterTime(&D_800D6EF4, Q12(10.0f), Q12(25.0f), Q12(46.0f), true, false);
            break;

        case 13:
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(0.8f), false);
            SysWork_StateStepIncrementAfterTime(&D_800D6EF4, Q12(10.0f), Q12(25.0f), Q12(46.0f), true, false);
            break;

        case 14:
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(0.0f), false);
            break;

        default:
            // Return to gameplay.
            func_80085EB8(3, &g_SysWork.playerWork_4C.player_0, 0, false);
            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);
            func_80088F94(&g_SysWork.npcs_1A0[0], 0, 0);

            Savegame_EventFlagSet(EventFlag_338);

            SD_Call(19);
            func_8003D01C();
            sharedFunc_800D2EF4_0_s00();
            break;
    }

    g_SysWork.npcs_1A0[0].position_18.vy = Q12(0.0f);

    if (D_800D6EF4 >= Q12(0.0f))
    {
        Dms_CharacterGetPosRot(&g_SysWork.playerWork_4C.player_0.position_18, &g_SysWork.playerWork_4C.player_0.rotation_24, "HERO", D_800D6EF4, (s_DmsHeader*)FS_BUFFER_15);

        if (D_800D37C0 != 0)
        {
            Dms_CharacterGetPosRot(&g_SysWork.npcs_1A0[0].position_18, &g_SysWork.npcs_1A0[0].rotation_24, "LISA", D_800D6EF4, (s_DmsHeader*)FS_BUFFER_15);
        }

        vcChangeProjectionValue(Dms_CameraGetTargetPos(&D_800D6ED8, &D_800D6EE8, NULL, D_800D6EF4, (s_DmsHeader*)FS_BUFFER_15));
        vcUserCamTarget(&D_800D6ED8, NULL, true);
        vcUserWatchTarget(&D_800D6EE8, NULL, true);
    }
}

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
            Chara_Spawn(Chara_Lisa, 0, Q12(60.0f), Q12(140.0f), Q12_ANGLE(0.0f), 3);

            func_8003D03C();
            sharedFunc_800D2EB4_0_s00();

            D_800D6EF8 = 0;

            g_SysWork.field_235C = NULL;
            g_SysWork.field_236C = NULL;
            g_SysWork.pointLightIntensity_2378 = Q12(1.2f);

            func_8008D438();

            g_SysWork.field_30 = 20;
            ScreenFade_ResetTimestep();

            D_800D37C1            = 0;
            g_SysWork.flags_22A4 |= SysFlag2_3;
            func_8005DC1C(Sfx_DoorClose0, &QVECTOR3(54.6f, -1.2f, 141.5f), Q8_CLAMPED(0.5f), 0);
            SysWork_StateStepIncrement(0);
            break;

        case 1:
            func_80085EB8(0, &g_SysWork.npcs_1A0[0], 11, false);
            func_80085EB8(0, &g_SysWork.playerWork_4C.player_0, 51, false);
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
            g_SysWork.pointLightIntensity_2378 = Q12(1.0f);
            SysWork_StateStepIncrement(0);

        case 7:
            Map_MessageWithAudio(49, &D_800D6EF8, &D_800D3778);
            SysWork_StateStepIncrementAfterTime(&D_800D6EF4, Q12(8.0f), Q12(21.0f), Q12(54.0f), true, false);

            if (D_800D6EF4 >= Q12(32.0f) && D_800D37C1 == 0)
            {
                func_80085EB8(0, &g_SysWork.playerWork_4C.player_0, 134, false);
                D_800D37C1++;
            }
            break;

        case 8:
            SysWork_StateStepIncrementAfterTime(&D_800D6EF4, Q12(8.0f), Q12(21.0f), Q12(54.0f), true, true);

            if (D_800D6EF4 >= Q12(32.0f) && D_800D37C1 == 0)
            {
                func_80085EB8(0, &g_SysWork.playerWork_4C.player_0, 134, false);
                D_800D37C1++;
            }
            break;

        case 9:
            func_80085EB8(0, &g_SysWork.playerWork_4C.player_0, 51, false);
            func_80085EB8(0, &g_SysWork.npcs_1A0[0], 5, false);

            g_SysWork.pointLightIntensity_2378 = Q12(1.2f);
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
            g_SysWork.pointLightIntensity_2378 = Q12(1.0f);
            Map_MessageWithAudio(70, &D_800D6EF8, &D_800D3778);
            break;

        case 17:
            func_80085EB8(0, &g_SysWork.npcs_1A0[0], 13, false);
            g_SysWork.pointLightIntensity_2378 = Q12(1.2f);
            SysWork_StateStepIncrement(0);

        case 18:
            Map_MessageWithAudio(79, &D_800D6EF8, &D_800D3778);
            SysWork_StateStepIncrementAfterTime(&D_800D6EF4, Q12(10.0f), Q12(58.0f), Q12(126.0f), true, false);
            break;

        case 19:
            SysWork_StateStepIncrementAfterTime(&D_800D6EF4, Q12(10.0f), Q12(58.0f), Q12(126.0f), true, true);
            break;

        case 20:
            Model_AnimFlagsClear(&g_SysWork.playerWork_4C.player_0.model_0, 2);
            func_80085EB8(0, &g_SysWork.playerWork_4C.player_0, 53, false);
            func_80085EB8(0, &g_SysWork.npcs_1A0[0], 21, false);
            SysWork_StateStepIncrement(0);

        case 21:
            SysWork_StateStepIncrementAfterTime(&D_800D6EF4, Q12(10.0f), Q12(127.0f), Q12(151.0f), false, true);
            break;

        case 22:
            func_8005DC1C(Sfx_DoorOpen0, &QVECTOR3(54.6f, -1.2f, 141.5f), Q8_CLAMPED(0.5f), 0);
            func_80085EB8(0, &g_SysWork.playerWork_4C.player_0, 51, false);
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

            SD_Call(19);

            Model_AnimFlagsSet(&g_SysWork.playerWork_4C.player_0.model_0, 2);

            func_8003D01C();
            func_80088F94(&g_SysWork.npcs_1A0[0], 0, 0);

            Savegame_EventFlagSet(EventFlag_MapMark_AltHospital1F_RightEntranceBroken);
            Savegame_EventFlagSet(EventFlag_340);

            SysWork_StateStepIncrementAfterFade(0, false, 2, Q12(0.0f), false);
            SysWork_StateStepIncrementAfterFade(0, false, 0, Q12(0.0f), false);

            func_8008D448();
            Game_FlashlightAttributesFix();

            g_SysWork.pointLightIntensity_2378 = Q12(1.0f);
            D_800D6EF4           = -1;

            vcReturnPreAutoCamWork(false);
            func_8003D01C();
            sharedFunc_800D2EF4_0_s00();
            break;
    }

    if (D_800D6EF4 >= Q12(0.0f))
    {
        Dms_CharacterGetPosRot(&g_SysWork.playerWork_4C.player_0.position_18, &g_SysWork.playerWork_4C.player_0.rotation_24, "HERO", D_800D6EF4, FS_BUFFER_15);
        Dms_CharacterGetPosRot(&g_SysWork.npcs_1A0[0].position_18, &g_SysWork.npcs_1A0[0].rotation_24, "LISA", D_800D6EF4, FS_BUFFER_15);
        vcChangeProjectionValue(Dms_CameraGetTargetPos(&D_800D6ED8, &D_800D6EE8, NULL, D_800D6EF4, FS_BUFFER_15));
        vcUserCamTarget(&D_800D6ED8, NULL, true);
        vcUserWatchTarget(&D_800D6EE8, NULL, true);

        // "LIGHT", cutscene light position?
        Dms_CharacterGetPosRot(&g_SysWork.pointLightPosition_2360, &unused, "LIGHT", D_800D6EF4, FS_BUFFER_15);

        // "L_INT", interior light or intersection point?
        Dms_CharacterGetPosRot(&lightIntPos, &unused, "L_INT", D_800D6EF4, FS_BUFFER_15);

        // Set light rotation.
        g_SysWork.pointLightRot_2370.vx = -ratan2(lightIntPos.vy - g_SysWork.pointLightPosition_2360.vy, Math_Vector2MagCalc(lightIntPos.vx - g_SysWork.pointLightPosition_2360.vx, lightIntPos.vz - g_SysWork.pointLightPosition_2360.vz));
        g_SysWork.pointLightRot_2370.vy =  ratan2(lightIntPos.vx - g_SysWork.pointLightPosition_2360.vx, lightIntPos.vz - g_SysWork.pointLightPosition_2360.vz);
        g_SysWork.pointLightRot_2370.vz = Q12_ANGLE(0.0f);
    }
}

void Map_WorldObjectsInit(void) // 0x800D2D6C
{
    WorldObjectInit(&g_WorldObjectSavepad, D_800A99E4.savePadName_4, 106.687f, -1.02f, 144.601f, 0.0f, 163.0f, 0.0f);

    WorldObjectNoRotInit(&g_WorldObject0, "ISU_HIDE", 57.8f, 0.0f, 0.0f);
}

void Map_WorldObjectsUpdate(void) // 0x800D2DF4
{
    MAP_CHUNK_CHECK_VARIABLE_DECL();

    if (PLAYER_IN_MAP_CHUNK(vx, 1, 3, -1, 3) && PLAYER_IN_MAP_CHUNK(vz, 1, 4, -1, 4))
    {
        WorldGfx_ObjectAdd(&g_WorldObjectSavepad.object_0, &g_WorldObjectSavepad.position_1C, &g_WorldObjectSavepad.rotation_28);
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, 2, -1, 2) && PLAYER_IN_MAP_CHUNK(vz, 1, 4, -1, 4))
    {
        if (Savegame_EventFlagGet(EventFlag_337) && !Savegame_EventFlagGet(EventFlag_338))
        {
            WorldGfx_ObjectAdd(&g_WorldObject0.object_0, &g_WorldObject0.position_1C, &(SVECTOR3){ 0, 0, 0 });
        }
    }
}
