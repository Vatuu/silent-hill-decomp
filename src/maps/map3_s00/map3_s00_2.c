#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "bodyprog/player_logic.h"
#include "main/rng.h"
#include "maps/map3/map3_s00.h"
#include "maps/characters/kaufmann.h"

#include "maps/shared/sharedFunc_800D88AC_0_s00.h" // 0x800CFE84

#include "maps/shared/sharedFunc_800D88C0_0_s00.h" // 0x800CFE98

#include "maps/shared/sharedFunc_800D8904_0_s00.h" // 0x800CFEDC

#include "maps/shared/sharedFunc_800D891C_0_s00.h" // 0x800CFEF4

#include "maps/shared/sharedFunc_800D8928_0_s00.h" // 0x800CFF00

#include "maps/shared/sharedFunc_800D893C_0_s00.h" // 0x800CFF14

#include "maps/shared/sharedFunc_800D8950_0_s00.h" // 0x800CFF28

#include "maps/shared/sharedFunc_800D8964_0_s00.h" // 0x800CFF3C

#include "maps/shared/sharedFunc_800D8A00_0_s00.h" // 0x800CFFD8

#include "maps/shared/sharedFunc_800D9064_0_s00.h" // 0x800D063C

#include "maps/shared/sharedFunc_800D9078_0_s00.h" // 0x800D0650

#include "maps/shared/sharedFunc_800D908C_0_s00.h" // 0x800D0664

#include "maps/shared/sharedFunc_800D9188_0_s00.h" // 0x800D0760

#include "maps/shared/Anim_StartKeyframeIdxGet.h" // 0x800D0828

#include "maps/shared/sharedFunc_800D923C_0_s00.h" // 0x800D0848

#include "maps/shared/sharedFunc_800D929C_0_s00.h" // 0x800D08A8

#include "maps/shared/Map_RoomIdxGet.h" // 0x800D08B8

#include "maps/shared/Map_RoomBgmInit_CheckCond.h" // 0x800D0960

#include "maps/shared/Map_RoomBgmInit_3_s00_CondTrue.h" // 0x800D0994

#include "maps/shared/Map_RoomBgmInit_3_s00_CondFalse.h" // 0x800D0994

void func_800D0B74(void) {}

#include "maps/shared/MapEvent_DoorJammed.h" // 0x800D0B7C

#include "maps/shared/MapEvent_DoorLocked.h" // 0x800D0C10

void func_800D0CA4(void) {}

void MapEvent_FirstAidKitTake(void) // 0x800D0CAC
{
    Event_CommonItemTake(CommonPickupItemId_FirstAidKit, EventFlag_M3S00_FirstAidKit);
}

void MapEvent_MapTake(void) // 0x800D0CD0
{
    Event_MapTake(17, EventFlag_M3S00_PickupMap, 48);
}

const char* MAP_MESSAGES[] = {
    #include "maps/shared/mapMsg_common.h"
    "~J0(1.0)\tHold_it... ~E ",
    "~J0(0.6)\t~E ",
    "~J0(1.7)\tStop! ~N\n\t\t\tDon't_shoot! ",
    "~J0(2.4)\tWait..._I'm_not_here_to_fight. ",
    "~J0(3.4)\tMy_name_is_Harry_Mason. ~N\n\t\t\tI'm_in_town_on_vacation. ~E ",
    "~J1(2.8)\tThank_God. ~N\n\t\t\tAnother_human_being. ",
    "~J1(1.5)\tDo_you_work_here? ",
    "~J1(3.6)\tI'm_Dr._Michael_Kaufmann. ~N\n\t\t\tI_work_at_this_hospital. ~E ",
    "~J1(2.5)\tSo_maybe_you_can_tell_me ~N\n\t\t\twhat's_going_on? ",
    "~J1(1.5)\tI_really_can't_say. ",
    "~J1(4.5)\tI_was_taking_a_nap ~N\n\t\t\tin_the_staff_room. ~N\n\t\t\tWhen_I_woke_up,_it_was_like_this. ",
    "~J1(2.3)\tEveryone_seems_to ~N\n\t\t\thave_disappeared. ",
    "~J1(3.0)\tAnd_it's_snowing_out. ~N\n\t\t\tThis_time_of_year. ",
    "~J1(2.6)\tSomething's_gone ~N\n\t\t\tseriously_wrong. ",
    "~J1(2.2)\tDid_you_see_those_monsters? ",
    "~J1(2.4)\tHave_you_ever_seen ~N\n\t\t\tsuch_aberrations? ",
    "~J1(2.0)\tEver_even_heard_of_such_things? ",
    "~J1(3.5)\tYou_and_I_both_know, ~N\n\t\t\tcreatures_like_that_don't_exist! ",
    "~J1(1.5)\tYeah... ~E ",
    "~J1(2.4)\tHave_you_seen ~N\n\t\t\ta_little_girl_anywhere? ",
    "~J1(1.6)\tI'm_looking_for_my_daughter. ",
    "~J1(3.0)\tShe's_only_seven. ~N\n\t\t\tShort,_black_hair. ",
    "~J1(2.8)\tShe's_missing? ~N\n\t\t\tI'm_sorry. ",
    "~J1(4.0)\tBut_with_all_those ~N\n\t\t\tmonsters_around, ~N\n\t\t\tI_highly_doubt_that_she's... ",
    "~J1(1.7)\t",
    "~J1(2.8)\tSorry, ~N\n\t\t\tI_didn't_mean_to_alarm_you. ~E ",
    "~J0(2.6)\tYour_wife,_she's_here_with_you? ",
    "~J0(5.0)\tShe_died_four_years_ago. ~N\n\t\t\tNow,_it's_just_me_and_my_daughter. ",
    "~J0(2.6)\tI_see... ~N\n\t\t\tI'm_sorry. ~E ",
    "~J0(2.3)\tWell,_I'd_better_be_going. ",
    "~J0(2.7)\tI_can't_just_sit ~N\n\t\t\taround_here_doing_nothing. ",
    "~J0(2.8)\tSo_long. ~N\n\t\t\tGood_luck_out_there. ~E ",
    "\tI_should_search_the_hospital. ~E ",
    "~H\tThere_is_a_ ~C5 Hospital_map ~C7 . ~N\n\tTake_it? ~S4 ",
    "\tThese_are_phones_and_phonebooks. ~N\n\tNo_need_to_examine_this. ~E ",
    "\tNothing_unusual. ~E ",
    "\tNothing_helpful. ~E "
};

void func_800D0CF8(void) // 0x800D0CF8
{
    // TODO: Fill this out.
    typedef enum _EventState
    {
        EventState_CutsceneStart = 4,
        EventState_CutsceneEnd   = 32,
        EventState_CutsceneSkip  = 36
    } e_EventState;

    if ((g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.skip_4) &&
        g_SysWork.sysStateStep_C[0] >= EventState_CutsceneStart && g_SysWork.sysStateStep_C[0] < EventState_CutsceneEnd)
    {
        SysWork_StateStepSet(0, EventState_CutsceneSkip);
    }

    if (g_SysWork.sysStateStep_C[0] >= 24 && g_SysWork.sysStateStep_C[0] < 28)
    {
        g_DeltaTime = Q12_MULT_PRECISE(g_DeltaTime, Q12(1.5f));
    }

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            Player_ControlFreeze();
            func_8005DC1C(Sfx_DoorClose0, &QVECTOR3(94.6f, -1.2f, 101.5f), Q8_CLAMPED(0.5f), 0);
            Savegame_MapMarkingSet(MapMarkFlag_FogHospital1F_StairsLocked);

            Fs_QueueStartRead(FILE_ANIM_HP1F03_DMS, FS_BUFFER_15);
            Fs_QueueWaitForEmpty();
            DmsHeader_FixOffsets((s_DmsHeader*)FS_BUFFER_15);
            Chara_Spawn(Chara_Kaufmann, 0, Q12(100.0f), Q12(100.0f), 0, 3);
            sharedFunc_800D88AC_0_s00(&g_SysWork.npcs_1A0[0]);

            g_SysWork.field_30 = 20;
            D_800D253C = 0;
            D_800D256C = 0;
            g_SysWork.flags_22A4 |= SysFlag2_3;

            func_800625F4(&QVECTOR3(95.8f, 0.0f, 101.27f), 0x48, 2, 1);
            func_800625F4(&QVECTOR3(96.05f, 0.0f, 101.07f), 0x48, 2, 1);
            func_800625F4(&QVECTOR3(96.1f, 0.0f, 100.68f), 0x48, 2, 1);
            func_8003D03C();
            sharedFunc_800D2EB4_0_s00();
            SysWork_StateStepIncrement(0);
            break;

        case 1:
            func_80085EB8(0, g_SysWork.npcs_1A0, 6, false);
            SysWork_StateStepIncrement(0);
            break;

        case 2:
            func_80085EB8(2, g_SysWork.npcs_1A0, 0, false);
            SysWork_StateStepIncrementAfterFade(2, false, 0, Q12(0.0f), false);
            break;

        case 3:
            func_80085EB8(3, g_SysWork.npcs_1A0, 0, false);
            SysWork_StateStepIncrement(0);

        case EventState_CutsceneStart:
            D_800D253C += Q12_MULT_PRECISE(g_DeltaTime, Q12(12.0f));
            if (D_800D253C > Q12(10.0f))
            {
                D_800D253C = Q12(10.0f);
                SysWork_StateStepIncrement(0);
            }
            break;

        case 5:
            func_80085EB8(1, g_SysWork.npcs_1A0, 0, false);

            if (D_800D253C < Q12(11.0f))
            {
                D_800D253C = Q12(11.0f);
            }
            else
            {
                D_800D253C += Q12_MULT_PRECISE(g_DeltaTime, Q12(10.0f));
                if (D_800D253C > Q12(25.0f))
                {
                    D_800D253C = Q12(25.0f);
                }
            }

            Map_MessageWithAudio(15, &D_800D256C, &D_800D24F0);
            break;

        case 6:
            func_80085EB8(0, &g_SysWork.npcs_1A0[0], 7, false);
            func_80085EB8(0, &g_SysWork.playerWork_4C.player_0, 0x73, false);
            SysWork_StateStepIncrement(0);

        case 7:
            Map_MessageWithAudio(15, &D_800D256C, &D_800D24F0);

            D_800D253C += Q12_MULT_PRECISE(g_DeltaTime, Q12(10.0f));
            if (D_800D253C > Q12(25.0f))
            {
                D_800D253C = Q12(25.0f);
                SysWork_StateStepIncrement(0);
            }
            break;

        case 8:
            SysWork_StateStepIncrement(0);

        case 9:
            Map_MessageWithAudio(15, &D_800D256C, &D_800D24F0);

            D_800D253C += Q12_MULT_PRECISE(g_DeltaTime, Q12(10.0f));
            if (D_800D253C > Q12(109.0f))
            {
                D_800D253C = Q12(109.0f);
            }
            break;

        case 10:
            Map_MessageWithAudio(16, &D_800D256C, &D_800D24F0);

            D_800D253C += Q12_MULT_PRECISE(g_DeltaTime, Q12(10.0f));
            if (D_800D253C > Q12(109.0f))
            {
                D_800D253C = Q12(109.0f);
            }
            break;

        case 11:
            Map_MessageWithAudio(17, &D_800D256C, &D_800D24F0);
            SysWork_StateStepIncrementDelayed(0x7000, false);

            D_800D253C += Q12_MULT_PRECISE(g_DeltaTime, Q12(10.0f));
            if (D_800D253C > Q12(109.0f))
            {
                D_800D253C = Q12(109.0f);
            }
            break;

        case 12:
            func_80085EB8(0, &g_SysWork.npcs_1A0[0], 8, false);
            SysWork_StateStepIncrement(0);

        case 13:
            Map_MessageWithAudio(17, &D_800D256C, &D_800D24F0);

            D_800D253C += Q12_MULT_PRECISE(g_DeltaTime, Q12(10.0f));
            if (D_800D253C > Q12(109.0f))
            {
                D_800D253C = Q12(109.0f);
            }
            break;

        case 14:
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(0.0f), false);
            break;

        case 15:
            D_800D253C = Q12(110.0f);

            func_80085EB8(0, &g_SysWork.playerWork_4C.player_0, 51, false);
            func_80085EB8(0, &g_SysWork.npcs_1A0[0], 5, false);
            SysWork_StateStepIncrement(0);

        case 16:
            SysWork_StateStepIncrementAfterFade(2, false, 0, Q12(0.0f), false);
            break;

        case 17:
            Map_MessageWithAudio(20, &D_800D256C, &D_800D24F0);
            break;

        case 18:
            D_800D253C = Q12(111.0f);
            Map_MessageWithAudio(23, &D_800D256C, &D_800D24F0);
            break;

        case 19:
            SysWork_StateStepIncrementDelayed(Q12(1.5f), false);
            break;

        case 20:
            Map_MessageWithAudio(34, &D_800D256C, &D_800D24F0);
            break;

        case 21:
            func_80085EB8(0, g_SysWork.npcs_1A0, 9, false);
            SysWork_StateStepIncrement(0);

        case 22:
            if (D_800D253C < Q12(112.0f))
            {
                D_800D253C = Q12(112.0f);
            }
            else
            {
                D_800D253C += Q12_MULT_PRECISE(g_DeltaTime, Q12(10.0f));
                if (D_800D253C > Q12(174.0f))
                {
                    D_800D253C = Q12(174.0f);
                }
            }

            SysWork_StateStepIncrementDelayed(Q12(1.5f), false);
            break;

        case 23:
            Map_MessageWithAudio(41, &D_800D256C, &D_800D24F0);

            D_800D253C += Q12_MULT_PRECISE(g_DeltaTime, Q12(10.0f));
            if (D_800D253C > Q12(174.0f))
            {
                D_800D253C = Q12(174.0f);
            }
            break;

        case 24:
            func_80085EB8(0, &g_SysWork.npcs_1A0[0], 1, false);
            SysWork_StateStepIncrement(0);

        case 25:
            if (D_800D253C >= Q12(175.0f))
            {
                D_800D253C += Q12_MULT_PRECISE(g_DeltaTime, Q12(15.0f));
                if (D_800D253C > Q12(182.0f))
                {
                    D_800D253C = Q12(182.0f);
                    SysWork_StateStepIncrement(0);
                }
            }
            else
            {
                D_800D253C = Q12(175.0f);
            }
            break;

        case 26:
            func_80085EB8(0, &g_SysWork.playerWork_4C.player_0, 0x48, false);
            SysWork_StateStepIncrement(0);

        case 27:
            if (D_800D253C < Q12(175.0f))
            {
                D_800D253C = Q12(175.0f);
            }
            else
            {
                D_800D253C += Q12_MULT_PRECISE(g_DeltaTime, Q12(15.0f));
                if (D_800D253C > Q12(220.0f))
                {
                    D_800D253C = Q12(220.0f);
                    SysWork_StateStepIncrement(0);
                }
            }
            break;

        case 28:
            func_80085EB8(0, &g_SysWork.npcs_1A0[0], 10, false);
            func_80085EB8(0u, &g_SysWork.playerWork_4C.player_0, 51, false);
            SysWork_StateStepIncrement(0);

        case 29:
            if (D_800D253C < Q12(221.0f))
            {
                D_800D253C = Q12(221.0f);
            }
            else
            {
                D_800D253C += Q12_MULT_PRECISE(g_DeltaTime, Q12(10.0f));
                if (D_800D253C > Q12(242.0f))
                {
                    D_800D253C = Q12(242.0f);
                }
            }

            Map_MessageWithAudio(0x2c, &D_800D256C, &D_800D24F0);
            break;

        case 30:
            func_80088F94(&g_SysWork.npcs_1A0[0], 0, 0);
            D_800D253C = Q12(243.0f);
            SysWork_StateStepIncrement(0);

        case 31:
            SysWork_StateStepIncrementDelayed(Q12(0.2f), false);
            break;

        case EventState_CutsceneEnd:
            func_8005DC1C(Sfx_DoorOpen0, &D_800D2530, Q8_CLAMPED(0.5f), 0);
            SysWork_StateStepIncrement(0);

        case 33:
            SysWork_StateStepIncrementDelayed(Q12(1.2f), false);
            break;

        case 34:
            func_8005DC1C(Sfx_DoorClose0, &D_800D2530, Q8_CLAMPED(0.5f), 0);
            SysWork_StateStepIncrement(0);

        case 35:
            SysWork_StateStepIncrementDelayed(Q12(0.7f), false);
            break;

        case EventState_CutsceneSkip:
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(0.0f), false);
            break;

        case 37:
            D_800D253C = Q12(243.0f);
            func_80088F94(&g_SysWork.npcs_1A0[0], 0, 0);
            SysWork_StateStepIncrement(0);
            break;

        default:
            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);

            SysWork_StateStepIncrementAfterFade(0, false, 0, Q12(0.0f), false);
            SysWork_StateStepIncrementAfterFade(0, false, 2, Q12(0.0f), false);
            vcReturnPreAutoCamWork(true);
            SD_Call(0x13);

            D_800D253C = NO_VALUE;

            Savegame_EventFlagSet(EventFlag_197);
            Savegame_EventFlagSet(EventFlag_198);
            func_8003D01C();
            sharedFunc_800D2EF4_0_s00();
            break;
    }

    if (D_800D253C >= 0)
    {
        Dms_CharacterGetPosRot(&g_SysWork.playerWork_4C.player_0.position_18, &g_SysWork.playerWork_4C.player_0.rotation_24, "HERO", D_800D253C, (s_DmsHeader* )FS_BUFFER_15);
        Dms_CharacterGetPosRot(&g_SysWork.npcs_1A0[0].position_18, &g_SysWork.npcs_1A0[0].rotation_24, "KAU", D_800D253C, (s_DmsHeader*)FS_BUFFER_15);
        vcChangeProjectionValue(Dms_CameraGetTargetPos(&D_800D2550, &D_800D2560, NULL, D_800D253C, (s_DmsHeader*)FS_BUFFER_15));
        vcUserCamTarget(&D_800D2550, NULL, true);
        vcUserWatchTarget(&D_800D2560, NULL, true);
    }
}

void Map_WorldObjectsInit(void) // 0x800D18DC
{
    WorldObjectNoRotInit(&g_WorldObject0, "TRUNK_HI", 97.2496f, 0.0f, 100.3428f);

    WorldObjectNoRotInit(&g_WorldObject1[0], "BIRD_HID", 98.4512f, 0.0f, 101.087f);

    WorldObjectNoRotInit(&g_WorldObject1[1], "BIRD2_HI", 98.4512f, 0.0f, 101.087f);

    WorldObjectInit(&g_WorldObject2, D_800A99E4.savePadName_4, 26.0f, -1.0198f, 144.5498f, 0.0f, 163.8f, 0.0f);

    WorldObjectInit(&g_WorldObject3, "MAP_HIDE", 24.6f, -1.56f, 143.16f, 0.0f, 180.0f, 0.0f);

    WorldObjectInit(&g_WorldObject4, "MAP2_HID", 24.6f, -1.56f, 143.16f, 0.0f, 180.0f, 0.0f);

    WorldObjectInit(&g_WorldObject5, D_800A99E4.firstAidKitName_8, 27.6f, -0.45f, 143.6f, 0.0f, -90.0f, 0.0f);
}

void Map_WorldObjectsUpdate(void) // 0x800D1A98
{
    static const SVECTOR3 EMPTY_ROT = {};
    static const VECTOR3  SOUND_POS = VECTOR3(22.5f, -1.5f, 137.0f);

    s32 x;
    s32 tmp;
    s32 rand0;
    s32 diff;
    MAP_CHUNK_CHECK_VARIABLE_DECL();

    if (PLAYER_IN_MAP_CHUNK(vx, 1, 3, -1, 3) && PLAYER_IN_MAP_CHUNK(vz, 1, 3, -1, 3))
    {
        if (!Savegame_EventFlagGet(EventFlag_198))
        {
            WorldGfx_ObjectAdd(&g_WorldObject0.object_0, &g_WorldObject0.position_1C, &EMPTY_ROT);
        }
        WorldGfx_ObjectAdd(&g_WorldObject1[0].object_0, &g_WorldObject1[0].position_1C, &EMPTY_ROT);
        WorldGfx_ObjectAdd(&g_WorldObject1[1].object_0, &g_WorldObject1[1].position_1C, &EMPTY_ROT);
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 0, 0, -1, 1) && PLAYER_IN_MAP_CHUNK(vz, 1, 4, -1, 4))
    {
        WorldGfx_ObjectAdd(&g_WorldObject2.object_0, &g_WorldObject2.position_1C, &g_WorldObject2.rotation_28);

        if (Savegame_EventFlagGet(EventFlag_M3S00_PickupMap))
        {
            WorldGfx_ObjectAdd(&g_WorldObject4.object_0, &g_WorldObject4.position_1C, &g_WorldObject4.rotation_28);
        }
        else
        {
            WorldGfx_ObjectAdd(&g_WorldObject3.object_0, &g_WorldObject3.position_1C, &g_WorldObject3.rotation_28);
        }

        if (!Savegame_EventFlagGet(EventFlag_M3S00_FirstAidKit))
        {
            WorldGfx_ObjectAdd(&g_WorldObject5.object_0, &g_WorldObject5.position_1C, &g_WorldObject5.rotation_28);
        }

        if (!Savegame_EventFlagGet(EventFlag_200) && (g_SysWork.playerWork_4C.player_0.position_18.vx < Q12(24.0f)))
        {
            tmp = Rng_Rand16() % Q12(3.0f);
            rand0 = tmp;
            diff = g_SysWork.playerWork_4C.player_0.position_18.vx - Q12(24.0f);

            if (diff >= 0)
            {
                x = diff / 3;
            }
            else
            {
                x = (Q12(24.0f) - g_SysWork.playerWork_4C.player_0.position_18.vx) / 3;
            }

            if (rand0 < Math_Sin(x))
            {
                func_8005DC1C(Sfx_Unk1492, &SOUND_POS, Q8_CLAMPED(0.875f), 2);
                Savegame_EventFlagSet(EventFlag_200);
            }
        }
    }
}
