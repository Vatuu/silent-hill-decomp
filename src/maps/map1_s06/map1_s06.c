#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "bodyprog/player_logic.h"
#include "main/rng.h"
#include "maps/shared.h"
#include "maps/map1/map1_s06.h"

INCLUDE_RODATA("asm/maps/map1_s06/nonmatchings/map1_s06", D_800C9578);

INCLUDE_RODATA("asm/maps/map1_s06/nonmatchings/map1_s06", g_MapOverlayHeader);

INCLUDE_ASM("asm/maps/map1_s06/nonmatchings/map1_s06", func_800CAFC4);

INCLUDE_ASM("asm/maps/map1_s06/nonmatchings/map1_s06", func_800CB0BC);

INCLUDE_ASM("asm/maps/map1_s06/nonmatchings/map1_s06", func_800CB760);

INCLUDE_ASM("asm/maps/map1_s06/nonmatchings/map1_s06", func_800CBF1C);

INCLUDE_ASM("asm/maps/map1_s06/nonmatchings/map1_s06", func_800CBF74);

INCLUDE_ASM("asm/maps/map1_s06/nonmatchings/map1_s06", func_800CC078);

#include "maps/shared/sharedFunc_800CB6B0_0_s00.h" // 0x800CC734

#include "maps/shared/sharedFunc_800CBBBC_0_s00.h" // 0x800CCCE4

#include "maps/shared/sharedFunc_800CBC94_0_s00.h" // 0x800CCDBC

#include "maps/shared/Particle_Update.h" // 0x800CD0C0

#include "maps/shared/sharedFunc_800CEB24_0_s00.h" // 0x800CD684

#include "maps/shared/sharedFunc_800CF2A4_0_s01.h" // 0x800CDAFC

INCLUDE_ASM("asm/maps/map1_s06/nonmatchings/map1_s06", sharedFunc_800CEFD0_1_s02); // 0x800CDC4C

INCLUDE_ASM("asm/maps/map1_s06/nonmatchings/map1_s06", sharedFunc_800CFFF8_0_s00); // 0x800CDFE8

#include "maps/shared/sharedFunc_800CE954_7_s03.h" // 0x800CE114

#include "maps/shared/sharedFunc_800D01BC_0_s00.h" // 0x800CE11C

#include "maps/shared/sharedFunc_800CF9A8_0_s01.h" // 0x800CE1D4

#include "maps/shared/sharedFunc_800D0700_0_s00.h" // 0x800CE25C

#include "maps/shared/sharedFunc_800D08B8_0_s00.h" // 0x800CE414

#include "maps/shared/sharedFunc_800D0A60_0_s00.h" // 0x800CE594

#include "maps/shared/sharedFunc_800D0B18_0_s00.h" // 0x800CE64C

#include "maps/shared/sharedFunc_800D0E04_0_s00.h" // 0x800CE7E4

#include "maps/shared/sharedFunc_800CFFD8_0_s01.h" // 0x800CE804

#include "maps/shared/sharedFunc_800D0850_0_s01.h" // 0x800CF07C

#include "maps/shared/sharedFunc_800CDAA8_0_s02.h" // 0x800CF468

#include "maps/shared/sharedFunc_800D1C38_0_s00.h" // 0x800CF868

#include "maps/shared/sharedFunc_800D209C_0_s00.h" // 0x800CFCB8

#include "maps/shared/sharedFunc_800D20D8_0_s00.h" // 0x800CFCF4

#include "maps/shared/sharedFunc_800D20E4_0_s00.h" // 0x800CFD00

#include "maps/shared/sharedFunc_800D2244_0_s00.h" // 0x800CFE60

s32 func_800D0038(void) // 0x800D0038
{
    return 0;
}

#include "maps/shared/sharedFunc_800D2C7C_0_s00.h" // 0x800D0040

#include "maps/shared/sharedFunc_800D2D2C_0_s00.h" // 0x800D00F0

#include "maps/shared/sharedFunc_800D2D44_0_s00.h" // 0x800D0108

#include "maps/shared/sharedFunc_800D2D6C_0_s00.h" // 0x800D0130

#include "maps/shared/sharedFunc_800D2D84_0_s00.h" // 0x800D0148

#include "maps/shared/sharedFunc_800D2DAC_0_s00.h" // 0x800D0170

#include "maps/shared/sharedFunc_800D2E50_0_s00.h" // 0x800D0214

#include "maps/shared/sharedFunc_800D2E60_0_s00.h" // 0x800D0224

void func_800D0230(void) {}

void func_800D0238(void) {}

void func_800D0240(void) {}

void func_800D0248(void) {}

void func_800D0250(void) {}

s32 func_800D0258(void) // 0x800D0258
{
    return 0;
}

void func_800D0260(void) {}

#include "maps/shared/sharedFunc_800D2EA4_0_s00.h" // 0x800D0268

#include "maps/shared/sharedFunc_800D2EB4_0_s00.h" // 0x800D0278

#include "maps/shared/sharedFunc_800D2EF4_0_s00.h" // 0x800D02B8

#include "maps/shared/Ai_Splithead_Update.h" // 0x800D02CC

#include "maps/shared/Ai_Splithead_Init.h" // 0x800D038C

INCLUDE_ASM("asm/maps/map1_s06/nonmatchings/map1_s06", sharedFunc_800CF990_1_s05); // 0x800D0444

INCLUDE_ASM("asm/maps/map1_s06/nonmatchings/map1_s06", sharedFunc_800CFE94_1_s05); // 0x800D0948

#include "maps/shared/sharedFunc_800D0054_1_s05.h" // 0x800D0B08

INCLUDE_ASM("asm/maps/map1_s06/nonmatchings/map1_s06", func_800D0B84);

INCLUDE_ASM("asm/maps/map1_s06/nonmatchings/map1_s06", func_800D13FC);

INCLUDE_ASM("asm/maps/map1_s06/nonmatchings/map1_s06", func_800D1C54);

void func_800D2270(s_SubCharacter* chara) // 0x800D2270
{
    s16    timerDiv6;
    s32    vol;
    u16    timer;
    q19_12 newMoveSpeed;
    q19_12 moveSpeed;

    moveSpeed = chara->moveSpeed_38;
    if (moveSpeed > Q12(0.0f))
    {
        newMoveSpeed = moveSpeed - FP_MULTIPLY_PRECISE(g_DeltaTime0, Q12(1.59961f), Q12_SHIFT);
        if (newMoveSpeed < Q12(0.0f))
        {
            newMoveSpeed = Q12(0.0f);
        }
    }
    else
    {
        newMoveSpeed = moveSpeed + FP_MULTIPLY_PRECISE(g_DeltaTime0, Q12(1.59961f), Q12_SHIFT);
        if (newMoveSpeed > Q12(0.0f))
        {
            newMoveSpeed = Q12(0.0f);
        }
    }
    chara->moveSpeed_38 = newMoveSpeed;

    switch (chara->model_0.anim_4.status_0)
    {
        case ANIM_STATUS(11, false):
        case ANIM_STATUS(11, true):
            chara->properties_E4.splitHead.flags_E8 |= 8;
            if (!func_800D4FE4(chara, moveSpeed))
            {
                break;
            }

        case ANIM_STATUS(10, true):
            chara->model_0.anim_4.status_0 = ANIM_STATUS(1, false);
            Sd_EngineCmd(Sfx_Unk1477);
            break;

        case ANIM_STATUS(1, false):
        case ANIM_STATUS(1, true):
            timer = chara->properties_E4.splitHead.timer_F4;
            timerDiv6 = D_800D6E2E / 6;
            if (timer < timerDiv6)
            {
                vol = (timer << 7) / timerDiv6;
            }
            else if ((D_800D6E2E * 5) / 6 < timer) 
            {
                vol = ((D_800D6E2E - timer) << 7) / timerDiv6;
            }
            else
            {
                vol = 0x80;
            }

            func_8005DE0C(Sfx_Unk1477, &chara->position_18, vol, Q12(16.0f), 0);

            timer = chara->properties_E4.splitHead.timer_F4;
            if (D_800D6E2E < timer)
            {
                D_800D6E2E = 0x3CCC;
                chara->model_0.state_2 = 5;
                chara->properties_E4.splitHead.timer_F4 = 0;
                chara->model_0.anim_4.status_0 = ANIM_STATUS(11, false);

                func_8004690C(Sfx_Unk1477);
                break;
            }

            chara->properties_E4.splitHead.timer_F4 += g_DeltaTime0;
            break;
    }
}

INCLUDE_ASM("asm/maps/map1_s06/nonmatchings/map1_s06", func_800D246C);

void func_800D2CC8(s_SubCharacter* chara) // 0x800D2CC8
{
    q19_12 newMoveSpeed0;
    q19_12 newMoveSpeed1;
    q19_12 moveSpeed;

    switch (chara->model_0.anim_4.status_0)
    {
        case 23:
            moveSpeed = chara->moveSpeed_38;
            if (moveSpeed > Q12(0.0f))
            {
                newMoveSpeed0 = moveSpeed - FP_MULTIPLY_PRECISE(g_DeltaTime0, Q12(0.5f), Q12_SHIFT);
                if (newMoveSpeed0 < Q12(0.0f))
                {
                    newMoveSpeed0 = Q12(0.0f);
                }
            }
            else
            {
                newMoveSpeed0 = moveSpeed + FP_MULTIPLY_PRECISE(g_DeltaTime0, Q12(0.5f), Q12_SHIFT);
                if (newMoveSpeed0 > Q12(0.0f))
                {
                    newMoveSpeed0 = Q12(0.0f);
                }
            }
            chara->moveSpeed_38 = newMoveSpeed0;

            if (!func_800D4FE4(chara, moveSpeed))
            {
                break;
            }

        case 2:
        case 3:
        case 20:
        case 21:
        case 22:
            chara->model_0.anim_4.status_0 = ANIM_STATUS(7, false);

            moveSpeed = chara->moveSpeed_38;
            if (moveSpeed > Q12(0.0f))
            {
                newMoveSpeed0 = moveSpeed - FP_MULTIPLY_PRECISE(g_DeltaTime0, Q12(1.0f), Q12_SHIFT);
                if (newMoveSpeed0 < Q12(0.0f))
                {
                    newMoveSpeed0 = Q12(0.0f);
                }
            }
            else
            {
                newMoveSpeed0 = moveSpeed + FP_MULTIPLY_PRECISE(g_DeltaTime0, Q12(1.0f), Q12_SHIFT);
                if (newMoveSpeed0 > Q12(0.0f))
                {
                    newMoveSpeed0 = Q12(0.0f);
                }
            }
            chara->moveSpeed_38 = newMoveSpeed0;
            break;

        default:
            break;

        case 14:
        case 15:
        case 16:
        case 17:
        case 24:
        case 25:
        case 26:
        case 27:
            if (chara->moveSpeed_38 > Q12(0.0f))
            {
                newMoveSpeed1 = chara->moveSpeed_38 - FP_MULTIPLY_PRECISE(g_DeltaTime0, Q12(1.0f), Q12_SHIFT);
                if (newMoveSpeed1 < Q12(0.0f))
                {
                    newMoveSpeed1 = Q12(0.0f);
                }
            }
            else
            {
                newMoveSpeed1 = chara->moveSpeed_38 + FP_MULTIPLY_PRECISE(g_DeltaTime0, Q12(1.0f), Q12_SHIFT);
                if (newMoveSpeed1 > Q12(0.0f))
                {
                    newMoveSpeed1 = Q12(0.0f);
                }
            }
            chara->moveSpeed_38 = newMoveSpeed1;

            if (!Savegame_EventFlagGet(EventFlag_131))
            {
                func_8005DC1C(Sfx_Unk1479, &chara->position_18, Q8_CLAMPED(0.5f), 0);
            }

            Savegame_EventFlagSet(EventFlag_131);
            break;
    }
}

INCLUDE_ASM("asm/maps/map1_s06/nonmatchings/map1_s06", func_800D2EF8);

void func_800D30F0(s_SubCharacter* chara) // 0x800D30F0
{
    if (Savegame_EventFlagGet(EventFlag_130))
    {
        chara->model_0.state_2 = 2;
        chara->model_0.anim_4.status_0 = ANIM_STATUS(11, false);
        chara->properties_E4.splitHead.flags_E8 |= CharaUnk0Flag_Unk8;
    }
}

INCLUDE_ASM("asm/maps/map1_s06/nonmatchings/map1_s06", sharedFunc_800D267C_1_s05); // 0x800D3130

INCLUDE_ASM("asm/maps/map1_s06/nonmatchings/map1_s06", sharedFunc_800D274C_1_s05); // 0x800D3200

INCLUDE_ASM("asm/maps/map1_s06/nonmatchings/map1_s06", sharedFunc_800D2D74_1_s05); // 0x800D3828

INCLUDE_ASM("asm/maps/map1_s06/nonmatchings/map1_s06", func_800D3E3C);

INCLUDE_ASM("asm/maps/map1_s06/nonmatchings/map1_s06", sharedFunc_800D3AFC_1_s05); // 0x800D45B0

INCLUDE_ASM("asm/maps/map1_s06/nonmatchings/map1_s06", sharedFunc_800D3B30_1_s05); // 0x800D45E4

INCLUDE_ASM("asm/maps/map1_s06/nonmatchings/map1_s06", sharedFunc_800D4070_1_s05); // 0x800D4B24

INCLUDE_ASM("asm/maps/map1_s06/nonmatchings/map1_s06", func_800D4EBC);

void func_800D4FC0(s32 arg0, s32 arg1) // 0x800D4FC0
{
    sharedData_800D8614_1_s05 += arg0;
    sharedData_800D8616_1_s05 += arg1;
}

INCLUDE_ASM("asm/maps/map1_s06/nonmatchings/map1_s06", func_800D4FE4);

INCLUDE_ASM("asm/maps/map1_s06/nonmatchings/map1_s06", func_800D5048);

#include "maps/shared/sharedFunc_800D929C_0_s00.h" // 0x800D5350

#include "maps/shared/Map_RoomIdxGet.h" // 0x800D5360

void func_800D5400(void) // 0x800D5400
{
    func_80035F4C(Savegame_EventFlagGet(EventFlag_133) ? 0xFE : 1, Q12(0.1f), D_800D71E8);
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

INCLUDE_ASM("asm/maps/map1_s06/nonmatchings/map1_s06", func_800D5614);

void func_800D5B98(void) // 0x800D5B98
{
    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            sharedFunc_800D20E4_0_s00();
            func_80086470(0, InventoryItemId_KGordonKey, 0, false);
            SysWork_StateStepIncrement(0);

        case 1:
            func_80085DF0();
            break;

        case 2:
            func_80086C58(&g_SysWork.player_4C.chara_0, 59);
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
            func_80086C58(&g_SysWork.player_4C.chara_0, 60);
            break;

        default:
            sharedFunc_800D2244_0_s00(false);
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
    #define CUTSCENE_SKIP_STATE 14

    if (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.skip_4)
    {
        if (g_SysWork.sysStateStep_C[0] > 0 && g_SysWork.sysStateStep_C[0] < 6)
        {
            SysWork_StateStepSet(0, CUTSCENE_SKIP_STATE);
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
            sharedFunc_800D20E4_0_s00();
            ScreenFade_ResetTimestep();

            g_SysWork.field_30 = 20;
            g_SysWork.player_4C.chara_0.position_18.vx = Q12(109.2f);
            g_SysWork.player_4C.chara_0.position_18.vz = Q12(43.2f);
            g_SysWork.player_4C.chara_0.rotation_24.vy = Q12(0.4553f);

            D_800D778E = g_SavegamePtr->current2dMapIdx_A9;
            g_SavegamePtr->current2dMapIdx_A9 = 1;
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

                if (g_Controller0->btnsClicked_10 & (g_GameWorkPtr->config_0.controllerConfig_0.enter_0 | g_GameWorkPtr->config_0.controllerConfig_0.cancel_2))
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

        case CUTSCENE_SKIP_STATE:
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(0.0f), false);
            break;

        default:
            SysWork_StateStepIncrementAfterFade(0, false, 2, Q12(0.0f), false);
            vcReturnPreAutoCamWork(true);
            SysWork_StateStepIncrementAfterFade(0, false, 0, Q12(0.0f), false);

            g_SavegamePtr->current2dMapIdx_A9 = D_800D778E;

            sharedFunc_800D2244_0_s00(false);
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
    Math_Vector3Set(&D_800DAF84.position_1C.position_0, Q12(20.4568f), Q12(-0.8345f), Q12(-17.97f));
    WorldObject_ModelNameSet(&D_800DAF84.object_0, "REDX_HID");

    WorldObjectPoseInit(&D_800DAFB4.position_1C, 20.9021f, -0.002f, -17.26f, 0.0f, -37.45f, 0.0f);
    WorldObject_ModelNameSet(&D_800DAFB4.object_0, "KEY_HIDE");

    D_800D7761 = 0;
    D_800DAFE4 = 0;
    D_800DAF78 = 0;

    WorldObjectPoseInit(&D_800DAFF4.position_1C, 61.8531f, -0.805f, 140.61f, 0, 92.9f, 0.0f);
    WorldObject_ModelNameSet(&D_800DAFF4.object_0, D_800A99E4.savePadName_4);

    WorldObjectPoseInit(&D_800DB024.position_1C, 133.294f, -0.8614f, 19.04f, 0.0f, 162.6f, 0.0f);
    WorldObject_ModelNameSet(&D_800DB024.object_0, "PICT00_H");

    WorldObjectPoseInit(&D_800DB064.position_1C, 96.9405f, -0.3365f, 21.092f, 0.0f, 66.8f, 0.0f);
    WorldObject_ModelNameSet(&D_800DB064.object_0, "MAP_HIDE");

    if (!Savegame_EventFlagGet(EventFlag_143))
    {
        func_8004690C(Sfx_Unk1359);
    }
}

void func_800D6578(void) // 0x800D6578
{
    VECTOR3 soundPos;
    s32     vol;

    MAP_CHUNK_CHECK_VARIABLE_DECL();
    if (PLAYER_IN_MAP_CHUNK(vx, 1, 3, -1, 3) && PLAYER_IN_MAP_CHUNK(vz, 0, 0, -1, 1))
    {
        if (!Savegame_EventFlagGet(EventFlag_M1S00_PickupMap))
        {
            g_WorldGfx_ObjectAdd(&D_800DB064.object_0, &D_800DB064.position_1C.position_0, &D_800DB064.position_1C.rotation_C);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, 2, -1, 2) && PLAYER_IN_MAP_CHUNK(vz, 1, 4, -1, 4))
    {
       g_WorldGfx_ObjectAdd(&D_800DAFF4.object_0, &D_800DAFF4.position_1C.position_0, &D_800DAFF4.position_1C.rotation_C);
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 0, 0, -1, 1) && PLAYER_IN_MAP_CHUNK(vz, 1, -1, 0, 0))
    {
        g_WorldGfx_ObjectAdd(&D_800DAF84.object_0, &D_800DAF84.position_1C.position_0, &(SVECTOR3){});

        if (!Savegame_EventFlagGet(EventFlag_M1S06_PickupKGordonKey))
        {
            g_WorldGfx_ObjectAdd(&D_800DAFB4.object_0, &D_800DAFB4.position_1C.position_0, &D_800DAFB4.position_1C.rotation_C);
        }

        if (D_800D7761 != 1)
        {
            func_8003ED74(7, 4);
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
            func_8003ED74(2, 2);
            Game_TurnFlashlightOff();
            D_800D7761 = 0;
        }

        if (!Savegame_EventFlagGet(EventFlag_142))
        {
            D_800DAF78 = FP_MULTIPLY_FLOAT_PRECISE(g_SysWork.player_4C.chara_0.position_18.vy, -0.2f, Q12_SHIFT) + Q12(0.25f);
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
            D_800DAF78 -= FP_MULTIPLY_FLOAT_PRECISE(g_DeltaTime0, 0.2f, Q12_SHIFT);
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
        g_WorldGfx_ObjectAdd(&D_800DB024.object_0, &D_800DB024.position_1C.position_0, &D_800DB024.position_1C.rotation_C);
    }

    if (!D_800DAFE4)
    {
        if (!Savegame_EventFlagGet(EventFlag_142) && Savegame_EventFlagGet(EventFlag_143))
        {
            Sd_EngineCmd(Sfx_Unk1480);
            D_800DAFE4 = 1;
        }

        if (!D_800DAFE4)
        {
            return;
        }
    }

    soundPos.vx = g_SysWork.player_4C.chara_0.position_18.vx;
    soundPos.vy = g_SysWork.player_4C.chara_0.position_18.vy;
    soundPos.vz = g_SysWork.player_4C.chara_0.position_18.vz - Q12(16.0f);

    D_800DB055 = Sound_StereoBalanceGet(&soundPos);
    if (D_800DB054 < D_800DB055)
    {
        D_800DB054 = MIN((D_800DB054 + (g_DeltaTime0 >> 6)), 127);
    }

    if (D_800DB055 < D_800DB054)
    {
        // TODO: `MAX` macro doesnt match.
        D_800DB054 = ((D_800DB054 - (g_DeltaTime0 >> 6)) < -127) ? -127 : D_800DB054 - (g_DeltaTime0 >> 6);
    }

    vol = MAX(255 - (D_800DAF78 >> 4), 0);
    func_800463C0(Sfx_Unk1480, D_800DB054, vol & 255, 0);
}

void func_800D6C88(void) // 0x800D6C88
{
    if (g_SysWork.player_4C.chara_0.position_18.vx == Q12(21.45f) && g_SysWork.player_4C.chara_0.position_18.vz == Q12(-15.26f))
    {
        Camera_PositionSet(NULL, Q12(21.69f), Q12(-2.38f), Q12(-19.16f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);
        Camera_LookAtSet(NULL, Q12(21.08f), Q12(-0.45f), Q12(-15.71f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);
        vcExecCamera();
        vcReturnPreAutoCamWork(false);
    }
}
