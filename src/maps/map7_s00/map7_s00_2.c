#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "bodyprog/player_logic.h"
#include "bodyprog/sound_system.h"
#include "main/rng.h"
#include "maps/map7/map7_s00.h"
#include "maps/characters/lisa.h"

#include "maps/shared/sharedFunc_800D88AC_0_s00.h" // 0x800CF538

#include "maps/shared/sharedFunc_800D88C0_0_s00.h" // 0x800CF54C

#include "maps/shared/sharedFunc_800D8904_0_s00.h" // 0x800CF590

#include "maps/shared/sharedFunc_800D891C_0_s00.h" // 0x800CF5A8

#include "maps/shared/sharedFunc_800D8928_0_s00.h" // 0x800CF5B4

#include "maps/shared/sharedFunc_800D893C_0_s00.h" // 0x800CF5C8

#include "maps/shared/sharedFunc_800D8950_0_s00.h" // 0x800CF5DC

#include "maps/shared/sharedFunc_800D8964_0_s00.h" // 0x800CF5F0

#include "maps/shared/sharedFunc_800D8A00_0_s00.h" // 0x800CF68C

#include "maps/shared/sharedFunc_800D9064_0_s00.h" // 0x800CFCF0

#include "maps/shared/sharedFunc_800D9078_0_s00.h" // 0x800CFD04

#include "maps/shared/sharedFunc_800D908C_0_s00.h" // 0x800CFD18

#include "maps/shared/sharedFunc_800D9188_0_s00.h" // 0x800CFE14

#include "maps/shared/Anim_StartKeyframeIdxGet.h" // 0x800CFEC0

#include "maps/shared/sharedFunc_800D923C_0_s00.h" // 0x800CFEE0

#include "maps/shared/sharedFunc_800D929C_0_s00.h" // 0x800CFF40

#include "maps/shared/Map_RoomIdxGet.h" // 0x800CFF50

void func_800CFFE8(s32 arg0) // 0x800CFFE8
{
    (arg0 != 0) ? func_800D0050() : sharedFunc_800D0110_7_s00();
}

void func_800D001C(s32 arg0) // 0x800D001C
{
    (arg0 != 0) ? func_800D00D0() : sharedFunc_800D0110_7_s00();
}

void func_800D0050(void) // 0x800D0050
{
    s32 var_a0;
    u32 temp_v1;

    if (g_SavegamePtr->mapRoomIdx_A5 == 3)
    {
        var_a0 = 15;
    }
    else if (Savegame_EventFlagGet(EventFlag_481))
    {
        if (!Savegame_EventFlagGet(EventFlag_574))
        {
            Savegame_EventFlagSet(EventFlag_574);
            var_a0 = 1;
        }
        else
        {
            var_a0 = 22;
        }
    }
    else
    {
        var_a0 = 14;
    }

    Bgm_TrackChange(var_a0);
}

void func_800D00D0(void) // 0x800D00D0
{
    Bgm_TrackChange(Savegame_EventFlagGet(EventFlag_391) ? 40 : 35);
}

#include "maps/shared/sharedFunc_800D0110_7_s00.h" // 0x800D0110

void func_800D0994(void) {}

#include "maps/shared/MapEvent_DoorJammed.h" // 0x800D099C

#include "maps/shared/MapEvent_DoorLocked.h" // 0x800D0A30

void func_800D0AC4(void) {}

#include "maps/shared/SysWork_StateStepIncrementAfterTime.h" // 0x800D0ACC

const char* MAP_MESSAGES[] = {
    #include "maps/shared/mapMsg_common.h"
    "~J0(1.2)\t~E ",
    "~J1(1.2)\tLisa? ",
    "~J1(3.8)\tWhat_happened? ~N\n\t\t\tWhere's_Alessa_and_Dahlia? ",
    "~J1(1.6)\tHarry,_listen. ",
    "~J1(2.8)\tSomething_you_said_before ~N\n\t\t\thas_been_bothering_me. ",
    "~J1(2.6)\tI_just_can't_get_it_out_of_my_head. ",
    "~J1(1.6)\tWhat_is_it_Lisa? ",
    "~J1(2.5)\tSo_I_went_to_look ~N\n\t\t\tin_the_basement. ",
    "~J1(3.0)\tEven_though_I_was_scared ~N\n\t\t\tas_hell. ",
    "~J1(3.1)\tLike_you_said, ~N\n\t\t\tthere_were_these_creepy_rooms. ",
    "~J1(3.2) \tBut_nothing_really_unusual ~N\n\t\t\tdown_there. ",
    "~J1(3.6)\tBut_while_I_was_down_there, ~N\n\t\t\tI_got_this_weird_feeling. ",
    "~J1(2.2)\tLike_I'd_been_there_before. ",
    "~J1(5.0)\tLike_something_happened_there, ~N\n\t\t\tbut_I_can't_quite_remember ~N\n\t\t\tsomehow. ",
    "~J1(1.8)\tWhat_was_it? ~E ",
    "~J0(2.4)\tHarry..._help_me... ",
    "~J0(3.2)\tI'm_so_scared. ~N\n\t\t\tI_can't_take_this. ",
    "~J0(2.0)\tIt's_only_a_temporary_thing. ",
    "~J0(2.7)\tYou're_in_shock_from ~N\n\t\t\twhen_you_were_knocked_out. ",
    "~J0(2.7)\tDon't_fret_about_it, ~N\n\t\t\tyou'll_remember_after_a_while... ~E ",
    "~J0(1.5)\tNo. ",
    "~J0(2.0)\tYou_don't_understand... ~E ",
    "~J0(2.8)\tWait! ~N\n\t\t\tWhere_do_you_think ~N\n\t\t\tyou're_going? ~E ",
    "~J0(2.0)\tLisa... ",
    "~J0(3.0)\tDamn!__What's_that? ~E ",
    "~J0(2.0)\tThat_sound.... ",
    "~J0(4.0)\tFrom_down_there... ~N\n\t\t\tIt's_coming_from_the_basement... ~E ",
    "~J0(2.4)\tI'm_being_summoned... ~E ",
    "~J0(2.1)\tWhat_happened_in_this_town? ",
    "~J0(2.7)\tWhat_could_be_making_things ~N\n\t\t\tlike_this? ",
    "~J0(4.3)\tI_have_a_feeling_if_I_take ~N\n\t\t\tthe_elevator_down_I'll_find_it. ~E ",
    "~J0(1.5)\t_ ~E ",
    "\tNothing_unusual. ~E ",
    "\tNothing_helpful. ~E "
};

void func_800D0B64(void) // 0x800D0B64
{
    typedef enum _EventState
    {
        EventState_Skip = 27
    } e_EventState;

    #define playerChara g_SysWork.playerWork_4C.player_0
    #define lisaChara g_SysWork.npcs_1A0[0]

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
            Savegame_EventFlagClear(EventFlag_476);
            func_8003A16C();

            g_MapMsgSoundIdx = 0;
            D_800D31D8 = 0;

            Savegame_EventFlagSet(EventFlag_476);
            Fs_QueueStartRead(FILE_ANIM_HSPTL6_DMS, FS_BUFFER_11);
            Fs_QueueWaitForEmpty();
            DmsHeader_FixOffsets((s_DmsHeader*)FS_BUFFER_11);

            g_Timer0 = Q12(0.0f);
            g_SysWork.field_235C = NULL;
            g_SysWork.field_236C = NULL;
            g_SysWork.pointLightIntensity_2378 = Q12(0.5f);

            Math_Vector3Set(&g_SysWork.pointLightPosition_2360, Q12(18.7f), Q12(-1.9f), Q12(-137.8f));
            Math_SetSVectorFast(&g_SysWork.pointLightRot_2370, Q12_ANGLE(-34.0f), Q12_ANGLE(-100.0f), 0);
            func_8008D438();

            g_SysWork.field_30 = 20;

            ScreenFade_ResetTimestep();

            g_SysWork.flags_22A4 |= SysFlag2_3;

            Chara_Spawn(Chara_Lisa, 0, Q12(17.4f), Q12(139.1f), 0, 3);
            SysWork_StateStepIncrement(0);

            SD_Call(Sfx_Unk1640);

            D_800D4362 = 0;

            func_8003D03C();
            sharedFunc_800D2EB4_0_s00();
            break;

        case 1:
            Map_MessageWithAudio(15, &g_MapMsgSoundIdx, &g_MapMsgSounds);
            break;

        case 2:
            SysWork_StateStepIncrementDelayed(Q12(1.5f), false);
            break;

        case 3:
            func_80085EB8(0, &playerChara, 135, false);
            func_80085EB8(0, &lisaChara, 9, false);
            SysWork_StateStepIncrement(0);

        case 4:
            SysWork_StateStepIncrementAfterFade(2, false, 0, Q12(0.8f), false);
            break;

        case 5:
            Map_MessageWithAudio(16, &g_MapMsgSoundIdx, &g_MapMsgSounds);
            break;

        case 6:
            func_80085EB8(0, &lisaChara, 14, false);
            SysWork_StateStepIncrement(0);

        case 7:
            Map_MessageWithAudio(30, &g_MapMsgSoundIdx, &g_MapMsgSounds);
            SysWork_StateStepIncrementAfterTime(&g_Timer0, Q12(2.5f), Q12(1.0f), Q12(44.0f), false, true);
            break;

        case 8:
            func_80085EB8(0, &playerChara, 136, false);
            SysWork_StateStepIncrement(0);

        case 9:
            Map_MessageWithAudio(30, &g_MapMsgSoundIdx, &g_MapMsgSounds);
            SysWork_StateStepIncrementAfterTime(&g_Timer0, Q12(2.5f), Q12(1.0f), Q12(62.0f), true, false);
            break;

        case 10:
            SysWork_StateStepIncrementDelayed(Q12(0.4f), false);
            SysWork_StateStepIncrementAfterTime(&g_Timer0, Q12(2.5f), Q12(1.0f), Q12(62.0f), true, false);
            break;

        case 11:
            func_80085EB8(0, &lisaChara, 15, false);
            Savegame_EventFlagSet(EventFlag_474);
            SysWork_StateStepIncrement(0);

        case 12:
            Map_MessageWithAudio(35, &g_MapMsgSoundIdx, &g_MapMsgSounds);
            SysWork_StateStepIncrementDelayed(Q12(0.5f), false);
            SysWork_StateStepIncrementAfterTime(&g_Timer0, Q12(2.5f), Q12(1.0f), Q12(65.0f), true, false);
            break;

        case 13:
            func_80085EB8(0, &playerChara, 137, false);
            SysWork_StateStepIncrement(0);

        case 14:
            Map_MessageWithAudio(35, &g_MapMsgSoundIdx, &g_MapMsgSounds);
            SysWork_StateStepIncrementAfterTime(&g_Timer0, Q12(2.5f), Q12(1.0f), Q12(65.0f), true, false);
            break;

        case 15:
            SysWork_StateStepIncrement(0);

        case 16:
            func_80085EB8(0, &playerChara, 138, false);
            func_80085EB8(0, &lisaChara, 16, false);
            SysWork_StateStepIncrement(0);

        case 17:
            SysWork_StateStepIncrementAfterTime(&g_Timer0, Q12(7.5f), Q12(65.0f), Q12(81.0f), true, true);
            Map_MessageWithAudio(37, &g_MapMsgSoundIdx, &g_MapMsgSounds);
            break;

        case 18:
            func_80088F94(&lisaChara, 0, 0);
            func_80085EB8(0, &playerChara, 139, false);

            Math_Vector3Set(&g_SysWork.pointLightPosition_2360, Q12(16.3f), Q12(-1.55f), Q12(-138.6f));

            // @hack This macro should work but must access `vz` by pointer for a match.
            //Math_SetSVectorFast(g_SysWork.pointLightRot_2370, 0xFF34, 0x2E3, 0);
            *(s32*)&g_SysWork.pointLightRot_2370.vx = 0x02E3FF34;
            (&g_SysWork.pointLightRot_2370)->vz = 0;

            func_8005DC1C(Sfx_DoorOpen0, &QVECTOR3(14.6f, -1.2f, -138.5f), Q8_CLAMPED(0.5f), 0);
            SysWork_StateStepIncrement(0);

        case 19:
            Map_MessageWithAudio(37, &g_MapMsgSoundIdx, &g_MapMsgSounds);
            SysWork_StateStepIncrementAfterTime(&g_Timer0, Q12(8.0f), Q12(82.0f), Q12(105.0f), true, false);
            break;

        case 20:
            func_8005DC1C(Sfx_DoorClose0, &QVECTOR3(14.6f, -1.2f, -138.5f), Q8_CLAMPED(0.5f), 0);
            SysWork_StateStepIncrement(0);

        case 21:
            SysWork_StateStepIncrementDelayed(Q12(2.5f), false);
            break;
        case 22:
            MapMsg_DisplayAndHandleSelection(false, 38, 0, 0, 0, false);
            SysWork_StateStepIncrementAfterTime(&g_Timer0, Q12(8.0f), Q12(82.0f), Q12(105.0f), true, false);
            break;

        case 23:
            SysWork_StateStepIncrementAfterTime(&g_Timer0, Q12(8.0f), Q12(82.0f), Q12(105.0f), true, true);
            break;

        case 24:
            func_80085EB8(0, &playerChara, 51, false);
            g_SysWork.pointLightIntensity_2378 = Q12(0.6f);
            SysWork_StateStepIncrement(0);

        case 25:
            MapMsg_DisplayAndHandleSelection(false, 40, 0, 0, 0, false);
            SysWork_StateStepIncrementAfterTime(&g_Timer0, Q12(6.0f), Q12(106.0f), Q12(150.0f), true, false);
            break;

        case 26:
            SysWork_StateStepIncrementAfterTime(&g_Timer0, Q12(6.0f), Q12(106.0f), Q12(150.0f), true, true);
            break;

        case EventState_Skip:
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(0.0f), false);
            break;

        case 28:
            g_Timer0 = Q12(150.0f);
            SysWork_StateStepIncrement(0);
            break;

        default:
            Player_ControlUnfreeze(true);
            SysWork_StateSetNext(SysState_Gameplay);

            vcReturnPreAutoCamWork(true);
            SysWork_StateStepIncrementAfterFade(0, false, 2, Q12(0.0f), false);
            SysWork_StateStepIncrementAfterFade(0, false, 0, Q12(0.0f), false);
            func_8008D448();
            Game_FlashlightAttributesFix();

            g_SysWork.pointLightIntensity_2378 = Q12(1.0f);

            Savegame_EventFlagSet(EventFlag_471);
            func_80088F94(&lisaChara, 0, 0);

            g_Timer0 = NO_VALUE;

            SD_Call(19);

            D_800D4362 = Q12(1.0f);

            func_8003D01C();
            sharedFunc_800D2EF4_0_s00();
            playerChara.position_18.vx = Q12(17.8f);
            playerChara.position_18.vz = Q12(-137.7f);
            break;
    }

    if (g_Timer0 >= Q12(0.0f))
    {
        Dms_CharacterGetPosRot(&playerChara.position_18, &playerChara.rotation_24, "HERO", g_Timer0, (s_DmsHeader*)FS_BUFFER_11);

        if (g_SysWork.sysStateStep_C[0] < 18)
        {
            Dms_CharacterGetPosRot(&lisaChara.position_18, &lisaChara.rotation_24, "LISA", g_Timer0, (s_DmsHeader*)FS_BUFFER_11);
        }

        vcChangeProjectionValue(Dms_CameraGetTargetPos(&g_CutsceneCameraPosition, &g_CutsceneCameraLookAt, NULL, g_Timer0, (s_DmsHeader*)FS_BUFFER_11));
        vcUserCamTarget(&g_CutsceneCameraPosition, NULL, true);
        vcUserWatchTarget(&g_CutsceneCameraLookAt, NULL, true);

        if (g_SysWork.sysStateStep_C[0] == 1 || g_SysWork.sysStateStep_C[0] == 2)
        {
            D_800D4362 += g_DeltaTime >> 1;
            if (D_800D4362 > Q12(0.25f))
            {
                D_800D4362 = Q12(0.25f);
            }
        }

        if (g_SysWork.sysStateStep_C[0] >= 10)
        {
            D_800D4362 += Q12_MULT_PRECISE(Rng_GenerateUInt(Q12(0.5f), Q12(1.0f) - 1), g_DeltaTime) >> 3;
            if (D_800D4362 > Q12(1.0f))
            {
                D_800D4362 = Q12(1.0f);
            }
        }

        func_8005DE0C(Sfx_Unk1640, &QVECTOR3(17.8f, 2.0f, -139.1f), D_800D4362 >> 5, Q12(32.0f), Rng_GenerateUInt(-8, 7));
    }
}

INCLUDE_ASM("maps/map7_s00/nonmatchings/map7_s00_2", func_800D1604);

void Map_WorldObjectsInit(void) // 0x800D2700
{
    s32    i;
    q19_12 z;

    WorldObject_ModelNameSet(&g_WorldObject0[0], "DR3R_HID");
    WorldObject_ModelNameSet(&g_WorldObject0[1], "DR3L_HID");
    WorldObject_ModelNameSet(&g_WorldObject0[2], "DR1R_HID");
    WorldObject_ModelNameSet(&g_WorldObject0[3], "DR1L_HID");
    WorldObject_ModelNameSet(&g_WorldObject0[4], "DR2R_HID");
    WorldObject_ModelNameSet(&g_WorldObject0[5], "DR2L_HID");

    z = Q12(-137.45f);

    for (i = 3; i >= 0; i--)
    {
        D_800D4370[i] = z;
    }

    WorldObjectInit(&g_WorldObject1, D_800A99E4.savePadName_4, 15.63f, -0.91f, -140.55f, 0.0f, -90.0f, 0.0f);

    if (Savegame_EventFlagGet(EventFlag_471))
    {
        SD_Call(Sfx_Unk1640);
        D_800D4362 = Q12(1.0f);
    }

    Savegame_EventFlagClear(EventFlag_219);

    if (Savegame_EventFlagGet(EventFlag_145) && Savegame_EventFlagGet(EventFlag_307))
    {
        Savegame_EventFlagSet(EventFlag_477);
    }
}

void Map_WorldObjectsUpdate(void) // 0x800D286C
{
    VECTOR3 pos;
    s32     i;

    MAP_CHUNK_CHECK_VARIABLE_DECL();

    if (PLAYER_IN_MAP_CHUNK(vx, 1, 2, -1, 2) && PLAYER_IN_MAP_CHUNK(vz, 1, -4, -1, -4))
    {
        for (i = 0; i < ARRAY_SIZE(g_WorldObject0); i++)
        {
            pos.vx = Q12(60.8f);
            pos.vy = Q12(0.0f);
            pos.vz = D_800D4370[(i >= 2) ? (i - 2) : i];

            WorldGfx_ObjectAdd(&g_WorldObject0[i], &pos, &D_800CB61C);
        }

        Sd_SfxAttributesUpdate(Sfx_Unk1640, 0, ((0xFF - (D_800D4362 >> 4)) >= 0x20) ? ~(D_800D4362 >> 4) : 0x20, Rng_GenerateUInt(-8, 7));
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 0, 0, -1, 1) && PLAYER_IN_MAP_CHUNK(vz, 1, -4, -1, -4))
    {
        WorldGfx_ObjectAdd(&g_WorldObject1.object_0, &g_WorldObject1.position_1C, &g_WorldObject1.rotation_28);

        if (Savegame_EventFlagGet(EventFlag_471))
        {
            Sd_SfxAttributesUpdate(Sfx_Unk1640, 0, ((0xFF - (D_800D4362 >> 4)) >= 0x20) ? ~(D_800D4362 >> 4) : 0x20, Rng_GenerateUInt(-8, 7));
        }
    }
}

INCLUDE_RODATA("maps/map7_s00/nonmatchings/map7_s00_2", D_800CB61C);
