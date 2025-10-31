#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "bodyprog/player_logic.h"
#include "main/rng.h"
#include "maps/shared.h"
#include "maps/map7/map7_s00.h"

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
    (arg0 != 0) ? func_800D0050() : func_800D0110();
}

void func_800D001C(s32 arg0) // 0x800D001C
{
    (arg0 != 0) ? func_800D00D0() : func_800D0110();
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

    func_8003640C(var_a0);
}

void func_800D00D0(void) // 0x800D00D0
{
    func_8003640C(Savegame_EventFlagGet(EventFlag_391) ? 40 : 35);
}

INCLUDE_ASM("asm/maps/map7_s00/nonmatchings/map7_s00_2", func_800D0110);

void func_800D0994() {}

#include "maps/shared/Event_DoorJammed.h" // 0x800D099C

#include "maps/shared/Event_DoorLocked.h" // 0x800D0A30

void func_800D0AC4() {}

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

void func_800D0B64(void)
{
    #define CUTSCENE_SKIP_STATE 27
    #define PLAYER_PTR g_SysWork.player_4C.chara_0
    #define LISA_PTR g_SysWork.npcs_1A0[0]
    if ((g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.skip_4) &&
        g_SysWork.sysStateStep_C[0] > 0 && g_SysWork.sysStateStep_C[0] < CUTSCENE_SKIP_STATE)
    {
        SysWork_StateStepSet(0, CUTSCENE_SKIP_STATE);
    }

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            sharedFunc_800D20E4_0_s00();
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
            g_SysWork.field_2378 = Q12(0.5f);
            Math_Vector3Set(&g_SysWork.field_2360, Q12(18.7f), Q12(-1.9f), Q12(-137.8f));
            Math_SetSVectorFast(g_SysWork.field_2370, FP_ANGLE(-34.0f), FP_ANGLE(-100.0f), 0);
            func_8008D438();
            g_SysWork.field_30 = 20;
            ScreenFade_ResetTimestep();
            g_SysWork.flags_22A4 |= (1<<3);
            Chara_Spawn(Chara_Lisa, 0, Q12(17.4f), Q12(139.1f), 0, 3);
            SysWork_StateStepIncrement(0);
    
            Sd_EngineCmd(Sfx_Unk1640);
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
            func_80085EB8(0, &PLAYER_PTR, 135, false);
            func_80085EB8(0, &LISA_PTR, 9, false);
            SysWork_StateStepIncrement(0);
            /* fallthrough */
        case 4:
            SysWork_StateStepIncrementAfterFade(2, false, 0, Q12(0.8f), false);
            break;
        case 5:
            Map_MessageWithAudio(16, &g_MapMsgSoundIdx, &g_MapMsgSounds);
            break;
        case 6:
            func_80085EB8(0, &LISA_PTR, 14, false);
            SysWork_StateStepIncrement(0);
            /* fallthrough */
        case 7:
            Map_MessageWithAudio(30, &g_MapMsgSoundIdx, &g_MapMsgSounds);
            SysWork_StateStepIncrementAfterTime(&g_Timer0, Q12(2.5f), Q12(1.0f), Q12(44.0f), false, true);
            break;
        case 8:
            func_80085EB8(0, &PLAYER_PTR, 136, false);
            SysWork_StateStepIncrement(0);
    
            /* fallthrough */
        case 9:
            Map_MessageWithAudio(30, &g_MapMsgSoundIdx, &g_MapMsgSounds);
            SysWork_StateStepIncrementAfterTime(&g_Timer0, Q12(2.5f), Q12(1.0f), Q12(62.0f), true, false);
            break;
        case 10:
            SysWork_StateStepIncrementDelayed(Q12(0.4f), false);
            SysWork_StateStepIncrementAfterTime(&g_Timer0, Q12(2.5f), Q12(1.0f), Q12(62.0f), true, false);
            break;
        case 11:
            func_80085EB8(0, &LISA_PTR, 15, false);
            Savegame_EventFlagSet(EventFlag_474);
            SysWork_StateStepIncrement(0);
            /* fallthrough */
        case 12:
            Map_MessageWithAudio(35, &g_MapMsgSoundIdx, &g_MapMsgSounds);
            SysWork_StateStepIncrementDelayed(Q12(0.5f), false);
            SysWork_StateStepIncrementAfterTime(&g_Timer0, Q12(2.5f), Q12(1.0f), Q12(65.0f), true, false);
            break;
        case 13:
            func_80085EB8(0, &PLAYER_PTR, 137, false);
            SysWork_StateStepIncrement(0);
            /* fallthrough */
        case 14:
            Map_MessageWithAudio(35, &g_MapMsgSoundIdx, &g_MapMsgSounds);
            SysWork_StateStepIncrementAfterTime(&g_Timer0, Q12(2.5f), Q12(1.0f), Q12(65.0f), true, false);
            break;
        case 15:
            SysWork_StateStepIncrement(0);
            /* fallthrough */
        case 16:
            func_80085EB8(0, &PLAYER_PTR, 138, false);
            func_80085EB8(0, &LISA_PTR, 16, false);
            SysWork_StateStepIncrement(0);
    
            /* fallthrough */
        case 17:
            SysWork_StateStepIncrementAfterTime(&g_Timer0, Q12(7.5f), Q12(65.0f), Q12(81.0f), true, true);
            Map_MessageWithAudio(37, &g_MapMsgSoundIdx, &g_MapMsgSounds);
            break;
        case 18:
            func_80088F94(&LISA_PTR, 0, 0);
            func_80085EB8(0, &PLAYER_PTR, 139, false);
    
            Math_Vector3Set(&g_SysWork.field_2360, Q12(16.3f), Q12(-1.55f), Q12(-138.6f));
            // @hack this macro should work but we have to access vz by pointer for a match.
            //Math_SetSVectorFast(g_SysWork.field_2370, 0xff34, 0x2e3, 0);
            *(s32*)&g_SysWork.field_2370.vx = 0x02E3FF34;
            (&g_SysWork.field_2370)->vz = 0;
            func_8005DC1C(Sfx_Unk1309, &QVECTOR3(14.6f, -1.2f, -138.5f), 128, 0);
            SysWork_StateStepIncrement(0);
            /* fallthrough */
        case 19:
            Map_MessageWithAudio(37, &g_MapMsgSoundIdx, &g_MapMsgSounds);
            SysWork_StateStepIncrementAfterTime(&g_Timer0, Q12(8.0f), Q12(82.0f), Q12(105.0f), true, false);
            break;
        case 20:
            func_8005DC1C(Sfx_Unk1310, &QVECTOR3(14.6f, -1.2f, -138.5f), 128, 0);
            SysWork_StateStepIncrement(0);
            /* fallthrough */
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
            func_80085EB8(0, &PLAYER_PTR, 51, false);
            g_SysWork.field_2378 = Q12(0.6f);
            SysWork_StateStepIncrement(0);
            /* fallthrough */
        case 25:
            MapMsg_DisplayAndHandleSelection(false, 40, 0, 0, 0, false);
            SysWork_StateStepIncrementAfterTime(&g_Timer0, Q12(6.0f), Q12(106.0f), Q12(150.0f), true, false);
            break;
        case 26:
            SysWork_StateStepIncrementAfterTime(&g_Timer0, Q12(6.0f), Q12(106.0f), Q12(150.0f), true, true);
            break;
        case CUTSCENE_SKIP_STATE:
            SysWork_StateStepIncrementAfterFade(2, true, 0, 0, false);
            break;
        case 28:
            g_Timer0 = Q12(150.0f);
            SysWork_StateStepIncrement(0);
            break;
        default:
            sharedFunc_800D2244_0_s00(true);
            SysWork_StateSetNext(SysState_Gameplay);
    
            vcReturnPreAutoCamWork(true);
            SysWork_StateStepIncrementAfterFade(0, false, 2, 0, false);
            SysWork_StateStepIncrementAfterFade(0, false, 0, 0, false);
            func_8008D448();
            func_8003EBA0();
            g_SysWork.field_2378 = Q12(1.0f);
            Savegame_EventFlagSet(EventFlag_471);
            func_80088F94(&LISA_PTR, 0, 0);
            g_Timer0 = -1;
            Sd_EngineCmd(19);
            D_800D4362 = Q12(1.0f);
            func_8003D01C();
            sharedFunc_800D2EF4_0_s00();
            PLAYER_PTR.position_18.vx = Q12(17.8f);
            PLAYER_PTR.position_18.vz = Q12(-137.7f);
            break;
    }
    if (g_Timer0 >= 0)
    {
        Dms_CharacterGetPosRot(&PLAYER_PTR.position_18, &PLAYER_PTR.rotation_24, "HERO", g_Timer0, (s_DmsHeader*)FS_BUFFER_11);
        if (g_SysWork.sysStateStep_C[0]< 18)
        {
            Dms_CharacterGetPosRot(&LISA_PTR.position_18, &LISA_PTR.rotation_24, "LISA", g_Timer0, (s_DmsHeader*)FS_BUFFER_11);
        }
        vcChangeProjectionValue(Dms_CameraGetTargetPos(&g_CutsceneCameraPosition, &g_CutsceneCameraLookAt, NULL, g_Timer0, (s_DmsHeader*)FS_BUFFER_11));
        vcUserCamTarget(&g_CutsceneCameraPosition, NULL, true);
        vcUserWatchTarget(&g_CutsceneCameraLookAt, NULL, true);
        if (g_SysWork.sysStateStep_C[0] == 1 || g_SysWork.sysStateStep_C[0] == 2)
        {
            D_800D4362 += g_DeltaTime0 >>1;
            if (D_800D4362 > Q12(0.25f))
            {
                D_800D4362 = Q12(0.25f);
            }
        }
        if (g_SysWork.sysStateStep_C[0] >= 10)
        {
            D_800D4362 += FP_MULTIPLY_PRECISE(((Rng_Rand16() & 0x7FF) + Q12(0.5f)), g_DeltaTime0, Q12_SHIFT) >> 3;
            if (D_800D4362 > Q12(1.0f))
            {
                D_800D4362 = Q12(1.0f);
            }
        }

        func_8005DE0C(Sfx_Unk1640, &QVECTOR3(17.8f, 2.0f, -139.1f), D_800D4362 >> 5, Q12(32.0f), (Rng_Rand16() & 0xF) -8);
    }
}

//INCLUDE_RODATA("asm/maps/map7_s00/nonmatchings/map7_s00_2", jtbl_800CB528);

INCLUDE_ASM("asm/maps/map7_s00/nonmatchings/map7_s00_2", func_800D1604);

void func_800D2700(void)
{
    s32 i;
    s32 z;

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
    WorldObjectPoseSet(&g_WorldObject1.position_1C, Q12(15.63f), Q12(-0.91f), Q12(-140.5498f), 0, 0xfc00, 0);
    WorldObject_ModelNameSet(&g_WorldObject1.object_0, D_800A99E4.savePadName_4);

    if (Savegame_EventFlagGet(EventFlag_471))
    {
        Sd_EngineCmd(Sfx_Unk1640);
        D_800D4362 = Q12(1.0f);
    }
    Savegame_EventFlagClear(EventFlag_219);
    if (Savegame_EventFlagGet(EventFlag_145) && Savegame_EventFlagGet(EventFlag_307))
    {
        Savegame_EventFlagSet(EventFlag_477);
    }
}

INCLUDE_ASM("asm/maps/map7_s00/nonmatchings/map7_s00_2", func_800D286C);

INCLUDE_RODATA("asm/maps/map7_s00/nonmatchings/map7_s00_2", D_800CB61C);
