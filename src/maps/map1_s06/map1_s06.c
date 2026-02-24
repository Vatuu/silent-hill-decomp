#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "bodyprog/player_logic.h"
#include "main/rng.h"
#include "maps/map1/map1_s06.h"
#include "maps/particle.h"
#include "maps/characters/player.h"
#include "maps/characters/split_head.h"

#include "maps/shared/sharedFunc_800CBE7C_1_s05.h" // 0x800CAFC4

#include "maps/shared/sharedFunc_800CBF74_1_s05.h" // 0x800CB0BC

#include "maps/shared/sharedFunc_800CC618_1_s05.h" // 0x800CB760

#include "maps/shared/sharedFunc_800CCDD4_1_s05.h" // 0x800CBF1C

#include "maps/shared/sharedFunc_800CCE2C_1_s05.h" // 0x800CBF74

#include "maps/shared/sharedFunc_800CCF30_1_s05.h" // 0x800CC078

#include "../src/maps/particle.c"

#include "../src/maps/characters/player.c"

// TODO: Move this line into separate `Chara_SplitHead` split.
#include "../src/maps/characters/split_head.c" // 0x800D02CC

#include "maps/shared/sharedFunc_800D929C_0_s00.h" // 0x800D5350

#include "maps/shared/Map_RoomIdxGet.h" // 0x800D5360

void Map_RoomBgmInit(bool arg0) // 0x800D5400
{
    Bgm_Update(Savegame_EventFlagGet(EventFlag_133) ? 0xFE : 1, Q12(0.1f), D_800D71E8);
}

void func_800D5448(void) {}

#include "maps/shared/MapEvent_DoorJammed.h" // 0x800D5450

#include "maps/shared/MapEvent_DoorLocked.h" // 0x800D54E4

#include "maps/shared/MapEvent_DoorUnlocked.h" // 0x800D5578

void func_800D560C(void) {}

const char* MAP_MESSAGES[] = {
    #include "maps/shared/mapMsg_common.h"
    "~J0(1.3)\t",
    "~J2(1.5)\tWhat_was_that...? ~E ",
    "~J0(2.4)\tWho_in_the_hell_was_that? ~E ",
    "\tThere_is_a_ ~C2 K._Gordon_key ~C7 . ~N\n\tTake_it? ~S4 ",
    "\tThe_boiler_is_off. ~E ",
    "\tIt_appears_to_be_broken. ~E ",
    "\tThe_valve_is_tightly_shut. ~N\n\tCan't_move_it. ~E ",
    "~J0(2.0)\tI_hear_a_... ",
    "~J0(3.0)\tA_church_bell,_maybe? ~N\n\tWho_is_ringing_the_bell? ~E ",
    "\tMoore,_Ranaldo,_Gordon... ~N\n\tThis_must_be_the_list_of_teachers. ~E ",
    "\tList_of_teachers. ",
    "\tK._Gordon..._that's_it. ~N\n\tI'll_note_the_address_down ~N\n\ton_the_map. ~E ",
    "~H\tThere_is_a_ ~C5 School_map ~C7 . ~N\n\tTake_it? ~S4 ",
    "~J1(3.5)\tWhere_am_I? ",
    "~J1(3.0)\tThis_is..._a_boiler_room!? ",
    "~J1(3.5)\tWhat_is_going_on_here? ~E "
};

void func_800D5614(void) // 0x800D5614
{
    if ((g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.skip_4) &&
        g_SysWork.sysStateStep_C[0] >= 3 && g_SysWork.sysStateStep_C[0] < 13)
    {
        SysWork_StateStepSet(0, 14);
    }

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            Player_ControlFreeze();
            Gfx_MapInitMapEffectsUpdate(19, 4);

            g_SysWork.field_30 = 20;
            D_800D7760         = 0;

            // Warp player.
            g_SysWork.playerWork_4C.player_0.position_18.vx = Q12(21.55f);
            g_SysWork.playerWork_4C.player_0.position_18.vz = Q12(-14.6f);
            g_SysWork.playerWork_4C.player_0.rotation_24.vy = Q12_ANGLE(180.0f);
            Model_AnimFlagsClear(&g_SysWork.playerWork_4C.player_0.model_0, 2);

            // Warp camera.
            Camera_PositionSet(NULL, Q12(22.47f), Q12(-3.43f), Q12(-12.94f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);
            Camera_LookAtSet(NULL, Q12(21.59f), Q12(-1.52f), Q12(-16.34f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);

            Game_TurnFlashlightOff();

            SysWork_StateStepIncrementAfterFade(0, false, 0, Q12(1.0f), false);
            SysWork_StateStepIncrement(0);

        case 1:
            if (!Sd_AmbientSfxInit())
            {
                SysWork_StateStepIncrement(0);
            }
            else
            {
                break;
            }

        case 2:
            SysWork_StateStepIncrementAfterFade(1, false, 0, Q12(0.0f), false);
            break;

        case 3:
            Map_MessageWithAudio(15, &D_800D7760, &D_800D775C);
            break;

        case 4:
            Savegame_EventFlagSet(EventFlag_143);
            SysWork_StateStepIncrement(0);

        case 5:
            SysWork_StateStepIncrementDelayed(Q12(1.5f), false);
            D_800DAF78 += FP_MULTIPLY_FLOAT_PRECISE(g_DeltaTime, 0.1f, 12);
            break;

        case 6:
            Map_MessageWithAudio(17, &D_800D7760, &D_800D775C);
            break;

        case 7:
            // Warp player.
            g_SysWork.playerWork_4C.player_0.position_18.vx = Q12(21.45f);
            g_SysWork.playerWork_4C.player_0.position_18.vz = Q12(-15.26f);
            g_SysWork.playerWork_4C.player_0.rotation_24.vy = Q12_ANGLE(180.0f);
            Model_AnimFlagsSet(&g_SysWork.playerWork_4C.player_0.model_0, 2);

            // Warp camera.
            Camera_PositionSet(NULL, Q12(22.11f), Q12(-5.18f), Q12(-20.45f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);
            Camera_LookAtSet(NULL, Q12(21.24f), Q12(-2.4f), Q12(-17.71f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);

            SysWork_StateStepIncrement(0);

        case 8:
            SysWork_StateStepIncrementDelayed(Q12(1.0f), false);
            break;

        case 9:
            Game_TurnFlashlightOn();
            SysWork_StateStepIncrement(0);

        case 10:
            SysWork_StateStepIncrementDelayed(Q12(1.0f), false);
            break;

        case 11:
            MapMsg_DisplayAndHandleSelection(false, 28, 0, 0, 0, false);
            break;

        case 12:
            SysWork_StateStepIncrementDelayed(Q12(2.0f), false);
            break;

        case 13:
            SysWork_StateStepReset();
            break;

        case 14:
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(0.0f), false);
            break;

        case 15:
            SD_Call(19);
            SysWork_StateStepIncrementAfterFade(0, false, 0, Q12(0.0f), false);

            // Warp player.
            g_SysWork.playerWork_4C.player_0.position_18.vx = Q12(21.45f);
            g_SysWork.playerWork_4C.player_0.position_18.vz = Q12(-15.26f);
            g_SysWork.playerWork_4C.player_0.rotation_24.vy = Q12_ANGLE(180.0f);

            // Warp camera.
            Camera_PositionSet(NULL, Q12(22.11f), Q12(-5.18f), Q12(-20.45f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);
            Camera_LookAtSet(NULL, Q12(21.24f), Q12(-2.4f), Q12(-17.71f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);

            Model_AnimFlagsSet(&g_SysWork.playerWork_4C.player_0.model_0, 2);
            Game_TurnFlashlightOn();

            Savegame_EventFlagSet(EventFlag_143);

            D_800DAF78 = Q12(0.15f);
            SysWork_StateStepIncrement(0);
            break;

        default:
            Savegame_EventFlagSet(EventFlag_134);

            Gfx_MapInitMapEffectsUpdate(7, 4);

            vcReturnPreAutoCamWork(false);
            SysWork_StateStepIncrementAfterFade(0, false, 2, Q12(0.0f), false);

            Player_ControlUnfreeze(false);

            SysWork_StateSetNext(SysState_Gameplay);

            func_8003A16C();
            break;
    }
}

void func_800D5B98(void) // 0x800D5B98
{
    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            Player_ControlFreeze();
            func_80086470(0, InventoryItemId_KGordonKey, 0, false);
            SysWork_StateStepIncrement(0);

        case 1:
            func_80085DF0();
            break;

        case 2:
            func_80086C58(&g_SysWork.playerWork_4C.player_0, 59);
            break;

        case 3:
            func_80086470(1, InventoryItemId_KGordonKey, 0, false);
            break;

        case 4:
            Savegame_EventFlagSet(EventFlag_M1S06_PickupKGordonKey);

            if (Gfx_PickupItemAnimate(InventoryItemId_KGordonKey))
            {
                MapMsg_DisplayAndHandleSelection(true, 18, 5, 6, 0, false);
            }
            break;

        case 5:
            func_80086470(3, InventoryItemId_KGordonKey, 1, false);
            SysWork_StateStepSet(0, 7);
            break;

        case 6:
            Savegame_EventFlagClear(EventFlag_M1S06_PickupKGordonKey);
            SysWork_StateStepIncrement(0);

        case 7:
            func_80086C58(&g_SysWork.playerWork_4C.player_0, 60);
            break;

        default:
            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);
            break;
    }
}

void func_800D5D6C(u16 arg0) // 0x800D5D6C
{
    func_800692A4(arg0, 120, Q12(0.5f));
    func_80067914(1, arg0, 120, Q12(0.5f));
    func_80068E0C(1, 1, 0, 0, arg0, 120, Q12(0.5f));
}

void func_800D5DD8(void) // 0x800D5DD8
{
    typedef enum _EventState
    {
        EventState_Skip = 14
    } e_EventState;

    // Skip.
    if (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.skip_4)
    {
        if (g_SysWork.sysStateStep_C[0] > 0 && g_SysWork.sysStateStep_C[0] < 6)
        {
            SysWork_StateStepSet(0, EventState_Skip);
        }

        if (D_800D7790 == 0 && g_SysWork.sysStateStep_C[0] > 6 && g_SysWork.sysStateStep_C[0] < 12)
        {
            D_800D7790 = 1;
            SysWork_StateStepIncrementAfterFade(0, true, 0, Q12(0.0f), false);
        }
    }

    if (D_800D7790)
    {
        if (ScreenFade_IsFinished())
        {
            D_800D7790 = 0;
            SysWork_StateStepSet(0, 13);
        }
    }

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            Player_ControlFreeze();
            ScreenFade_ResetTimestep();

            g_SysWork.field_30 = 20;
            g_SysWork.playerWork_4C.player_0.position_18.vx = Q12(109.2f);
            g_SysWork.playerWork_4C.player_0.position_18.vz = Q12(43.2f);
            g_SysWork.playerWork_4C.player_0.rotation_24.vy = Q12(0.4553f);

            D_800D778E = g_SavegamePtr->paperMapIdx_A9;
            g_SavegamePtr->paperMapIdx_A9 = 1;
            D_800D7790 = 0;

            Camera_PositionSet(NULL, Q12(106.5799f), Q12(-3.6199f), Q12(45.23f), 0, 0, 0, 0, true);
            Camera_LookAtSet(NULL, Q12(109.19f), Q12(-1.3699f), Q12(43.2f), 0, 0, 0, 0, true);
            SysWork_StateStepIncrement(0);

        case 1:
            SysWork_StateStepIncrementAfterFade(2, false, 0, Q12(1.0f), false);
            break;

        case 2:
            SysWork_StateStepIncrementDelayed(Q12(1.0f), false);
            break;

        case 3:
            MapMsg_DisplayAndHandleSelection(false, 22, 0, 0, 0, false); // "I hear a church bell."
            break;

        case 4:
            Fs_QueueStartSeek(FILE_TIM_MP_0TOWN_TIM + D_800A99B5);
            SysWork_StateStepIncrement(0);

        case 5:
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(0.0f), false);
            break;

        case 6:
            func_800867B4(0, 1);

            D_800D778D = 0;
            D_800D778F = 0;

            SysWork_StateStepIncrement(0);

        case 7:
            func_800D5D6C(0);
            SysWork_StateStepIncrementAfterFade(2, false, 0, Q12(0.0f), false);
            break;

        case 8:
            func_800D5D6C(0);
            SysWork_StateStepIncrementDelayed(Q12(0.6f), false);
            break;

        case 9:
            D_800D778D++;

            func_800D5D6C(D_800D778D);

            if (D_800D778D == 122)
            {
                SysWork_StateStepIncrement(0);
            }
            break;

        case 10:
            func_800D5D6C(122);
            SysWork_StateStepIncrementDelayed(Q12(0.6f), false);
            break;

        case 11:
            func_800D5D6C(122);
            func_80068E0C(2, 1, 926, D_800D778F, 122, 120, Q12(0.5f));

            D_800D778F++;
            if (D_800D778F >= 0x80)
            {
                D_800D778F = 0x80;

                if (g_Controller0->btnsClicked_10 & (g_GameWorkPtr->config_0.controllerConfig_0.enter_0 |
                                                     g_GameWorkPtr->config_0.controllerConfig_0.cancel_2))
                {
                    SysWork_StateStepIncrement(0);
                }

                if (g_SysWork.sysStateStep_C[0] == 11)
                {
                    SysWork_StateStepIncrementDelayed(Q12(1.5f), false);
                }
            }
            break;

        case 12:
            func_800D5D6C(122);
            func_80068E0C(2, 1, 926, 128, 122, 120, Q12(0.5f));
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(0.0f), false);
            break;

        case 13:
            func_800867B4(2, 0);
            SysWork_StateStepIncrement(0);

        case EventState_Skip:
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(0.0f), false);
            break;

        default:
            SysWork_StateStepIncrementAfterFade(0, false, 2, Q12(0.0f), false);
            vcReturnPreAutoCamWork(true);
            SysWork_StateStepIncrementAfterFade(0, false, 0, Q12(0.0f), false);

            g_SavegamePtr->paperMapIdx_A9 = D_800D778E;

            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);

            Savegame_EventFlagSet(EventFlag_M1S06_ChurchMarkedOnMap);
            Savegame_MapMarkingSet(MapMarkFlag_OldTown_BalkanChurchCircle);
            break;
    }
}

void func_800D6338(void) // 0x800D6338
{
    g_BackgroundColor = 112;

    if (Savegame_EventFlagGet(EventFlag_M1S06_PickupKGordonKey))
    {
        MapMsg_DisplayWithTexture(FILE_TIM_RSCBOOK_TIM, Q12(0.0f), Q12(0.0f), 25);
        Savegame_MapMarkingSet(MapMarkFlag_OldTown_KGordonDotAndSignOnly);
    }
    else
    {
        MapMsg_DisplayWithTexture(FILE_TIM_RSCBOOK_TIM, Q12(0.0f), Q12(0.0f), 24);
    }
}

void MapEvent_MapTake(void) // 0x800D63B0
{
    Event_MapTake(6, EventFlag_M1S00_PickupMap, 27);
}

void Map_WorldObjectsInit(void) // 0x800D63D8
{
    WorldObjectNoRotInit(&D_800DAF84, "REDX_HID", 20.4568f, -0.8345f, -17.97f);
    WorldObjectInit(&D_800DAFB4, "KEY_HIDE", 20.9021f, -0.002f, -17.26f, 0.0f, -37.45f, 0.0f);

    D_800D7761 = 0;
    D_800DAFE4 = 0;
    D_800DAF78 = 0;

    WorldObjectInit(&D_800DAFF4, D_800A99E4.savePadName_4, 61.8531f, -0.805f, 140.61f, 0, 92.9f, 0.0f);
    WorldObjectInit(&D_800DB024, "PICT00_H", 133.294f, -0.8614f, 19.04f, 0.0f, 162.6f, 0.0f);
    WorldObjectInit(&D_800DB064, "MAP_HIDE", 96.9405f, -0.3365f, 21.092f, 0.0f, 66.8f, 0.0f);

    if (!Savegame_EventFlagGet(EventFlag_143))
    {
        Sd_SfxStop(Sfx_Unk1359);
    }
}

void Map_WorldObjectsUpdate(void) // 0x800D6578
{
    VECTOR3 soundPos;
    s32     vol;

    MAP_CHUNK_CHECK_VARIABLE_DECL();
    if (PLAYER_IN_MAP_CHUNK(vx, 1, 3, -1, 3) && PLAYER_IN_MAP_CHUNK(vz, 0, 0, -1, 1))
    {
        if (!Savegame_EventFlagGet(EventFlag_M1S00_PickupMap))
        {
            WorldGfx_ObjectAdd(&D_800DB064.object_0, &D_800DB064.position_1C, &D_800DB064.rotation_28);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, 2, -1, 2) && PLAYER_IN_MAP_CHUNK(vz, 1, 4, -1, 4))
    {
       WorldGfx_ObjectAdd(&D_800DAFF4.object_0, &D_800DAFF4.position_1C, &D_800DAFF4.rotation_28);
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 0, 0, -1, 1) && PLAYER_IN_MAP_CHUNK(vz, 1, -1, 0, 0))
    {
        WorldGfx_ObjectAdd(&D_800DAF84.object_0, &D_800DAF84.position_1C, &(SVECTOR3){ 0, 0, 0 });

        if (!Savegame_EventFlagGet(EventFlag_M1S06_PickupKGordonKey))
        {
            WorldGfx_ObjectAdd(&D_800DAFB4.object_0, &D_800DAFB4.position_1C, &D_800DAFB4.rotation_28);
        }

        if (D_800D7761 != 1)
        {
            Gfx_MapInitMapEffectsUpdate(7, 4);
            D_800D7761 = 1;
        }

        if (Savegame_EventFlagGet(EventFlag_134))
        {
            D_800DAF78 = Q12(0.15f);
        }
    }
    else if (PLAYER_IN_MAP_CHUNK(vx, 1, 2, -1, 2) && PLAYER_IN_MAP_CHUNK(vz, 1, -1, 0, 0))
    {
        if (D_800D7761 != 0)
        {
            Gfx_MapInitMapEffectsUpdate(2, 2);
            Game_TurnFlashlightOff();
            D_800D7761 = 0;
        }

        if (!Savegame_EventFlagGet(EventFlag_142))
        {
            D_800DAF78 = Q12_MULT_FLOAT_PRECISE(g_SysWork.playerWork_4C.player_0.position_18.vy, -0.2f) + Q12(0.25f);
        }
    }
    else
    {
        if (PLAYER_IN_MAP_CHUNK(vx, 1, 3, -1, 3) && PLAYER_IN_MAP_CHUNK(vz, 0, 0, -1, 1))
        {
            if (Savegame_MapMarkingGet(MapMarkFlag_OldTown_SchoolCircle))
            {
                Savegame_MapMarkingSet(MapMarkFlag_OldTown_SchoolCheck);
            }

            Savegame_EventFlagSet(EventFlag_142);
        }

        if (Savegame_EventFlagGet(EventFlag_142))
        {
            D_800DAF78 -= Q12_MULT_FLOAT_PRECISE(g_DeltaTime, 0.2f);
            if (D_800DAF78 < Q12(0.0f))
            {
                D_800DAF78 = Q12(0.0f);
                D_800DAFE4 = 0;
            }
        }
        else
        {
            D_800DAF78 = Q12(0.45f);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, 4, -1, 4) && PLAYER_IN_MAP_CHUNK(vz, 0, 0, -1, 1))
    {
        WorldGfx_ObjectAdd(&D_800DB024.object_0, &D_800DB024.position_1C, &D_800DB024.rotation_28);
    }

    if (!D_800DAFE4)
    {
        if (!Savegame_EventFlagGet(EventFlag_142) && Savegame_EventFlagGet(EventFlag_143))
        {
            SD_Call(Sfx_Unk1480);
            D_800DAFE4 = 1;
        }

        if (!D_800DAFE4)
        {
            return;
        }
    }

    // Set sound position.
    soundPos.vx = g_SysWork.playerWork_4C.player_0.position_18.vx;
    soundPos.vy = g_SysWork.playerWork_4C.player_0.position_18.vy;
    soundPos.vz = g_SysWork.playerWork_4C.player_0.position_18.vz - Q12(16.0f);

    D_800DB055 = Sound_StereoBalanceGet(&soundPos);
    if (D_800DB054 < D_800DB055)
    {
        D_800DB054 = MIN((D_800DB054 + (g_DeltaTime >> 6)), 127);
    }

    if (D_800DB055 < D_800DB054)
    {
        // TODO: `MAX` macro doesnt match.
        D_800DB054 = ((D_800DB054 - (g_DeltaTime >> 6)) < -127) ? -127 : D_800DB054 - (g_DeltaTime >> 6);
    }

    vol = MAX(255 - (D_800DAF78 >> 4), 0);
    Sd_SfxAttributesUpdate(Sfx_Unk1480, D_800DB054, vol & 255, 0);
}

void func_800D6C88(void) // 0x800D6C88
{
    if (g_SysWork.playerWork_4C.player_0.position_18.vx == Q12(21.45f) && g_SysWork.playerWork_4C.player_0.position_18.vz == Q12(-15.26f))
    {
        Camera_PositionSet(NULL, Q12(21.69f), Q12(-2.38f), Q12(-19.16f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);
        Camera_LookAtSet(NULL, Q12(21.08f), Q12(-0.45f), Q12(-15.71f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);
        vcExecCamera();
        vcReturnPreAutoCamWork(false);
    }
}
