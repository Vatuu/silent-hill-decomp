#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "bodyprog/player_logic.h"
#include "main/rng.h"
#include "maps/shared.h"
#include "maps/map6/map6_s02.h"

#include "maps/shared/sharedFunc_800D88AC_0_s00.h" // 0x800CDEB0

#include "maps/shared/sharedFunc_800D88C0_0_s00.h" // 0x800CDEC4

#include "maps/shared/sharedFunc_800D8904_0_s00.h" // 0x800CDF08

#include "maps/shared/sharedFunc_800D891C_0_s00.h" // 0x800CDF20

#include "maps/shared/sharedFunc_800D8928_0_s00.h" // 0x800CDF2C

#include "maps/shared/sharedFunc_800D893C_0_s00.h" // 0x800CDF40

#include "maps/shared/sharedFunc_800D8950_0_s00.h" // 0x800CDF54

#include "maps/shared/sharedFunc_800D8964_0_s00.h" // 0x800CDF68

#include "maps/shared/sharedFunc_800D8A00_0_s00.h" // 0x800CDFF4

#include "maps/shared/sharedFunc_800D9064_0_s00.h" // 0x800CE658

#include "maps/shared/sharedFunc_800D9078_0_s00.h" // 0x800CE66C

#include "maps/shared/sharedFunc_800D908C_0_s00.h" // 0x800CE680

#include "maps/shared/sharedFunc_800D9188_0_s00.h" // 0x800CE77C

#include "maps/shared/Anim_StartKeyframeIdxGet.h" // 0x800CE810

#include "maps/shared/sharedFunc_800D923C_0_s00.h" // 0x800CE81C

#include "maps/shared/sharedFunc_800D929C_0_s00.h" // 0x800CE87C

INCLUDE_ASM("asm/maps/map6_s02/nonmatchings/map6_s02_2", func_800CE88C);

INCLUDE_ASM("asm/maps/map6_s02/nonmatchings/map6_s02_2", func_800CEA88);

void func_800CED6C(void) {}

INCLUDE_ASM("asm/maps/map6_s02/nonmatchings/map6_s02_2", func_800CED74);

#include "maps/shared/MapEvent_DoorJammed.h" // 0x800CEF88

#include "maps/shared/MapEvent_DoorLocked.h" // 0x800CF01C

void func_800CF0B0(void) {}

const char* MAP_MESSAGES[] = {
    #include "maps/shared/mapMsg_common.h"
    "~J0(1.0)\t...! ~E ",
    "~J0(1.0)\tWait! ~E ",
    "~J0(1.7)\tDamn! ~N\n\t\t\tI_was_too_late? ~E ",
    "~J0(1.5)\tSorry... ",
    "~J0(0.6)\tAh... ",
    "~J0(1.5)\t_ ",
    "~J0(3.6)\tLet_me_ask_you,_have_you_seen ~N\n\t\t\ta_little_girl_around_here? ~E ",
    "~J0(2.8)\tShort,_black_hair... ~E ",
    "~J0(1.0)\tWhat? ~E ",
    "~J0(2.5)\tThat_light!? ~E "
};

void func_800CF0B8(void)
{
    bool hasSkippedEarly;

    Savegame_EventFlagClear(EventFlag_412);

    hasSkippedEarly = false;
    if (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.skip_4 && g_SysWork.sysStateStep_C[0] >= 2)
    {
        if (g_SysWork.sysStateStep_C[0] <= 19)
        {
            // Sets flag to true if player skipped before step 19.
            hasSkippedEarly = g_SysWork.sysStateStep_C[0] < 19;
            SysWork_StateStepSet(0, 20);
        }
    }

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            sharedFunc_800D20E4_0_s00();

            g_SysWork.field_30 = 20;
            ScreenFade_ResetTimestep();

            func_8003D03C();
            sharedFunc_800D2EB4_0_s00();

            Savegame_EventFlagClear(EventFlag_405);

            SysWork_StateStepIncrement(0);

            Camera_PositionSet(NULL, Q12(57.09f), Q12(-3.23f), Q12(-20.41f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);
            Camera_LookAtSet(NULL, Q12(60.07f), Q12(-0.94f), Q12(-19.06f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);

            Savegame_EventFlagSet(EventFlag_412);

            g_SysWork.player_4C.chara_0.position_18.vx = FP_MULTIPLY_FLOAT(Math_Sin(FP_ANGLE(135.0f)), 0.9f, Q12_SHIFT) + Q12(60.0f);
            g_SysWork.player_4C.chara_0.position_18.vy = Q12(1.64f);
            g_SysWork.player_4C.chara_0.position_18.vz = FP_MULTIPLY_FLOAT(Math_Cos(FP_ANGLE(135.0f)), 0.9f, Q12_SHIFT) - Q12(20.0f);
            g_SysWork.player_4C.chara_0.rotation_24.vy = FP_ANGLE(45.0f);

            D_800D4E09 = 1;
            break;

        case 1:
            SysWork_StateStepIncrementAfterFade(0, false, 0, Q12(0.0f), false);
            func_80085EB8(0, &g_SysWork.player_4C.chara_0, 53, false);
            Chara_Load(0, Chara_Alessa, &g_SysWork.npcCoords_FC0[0], CHARA_FORCE_FREE_ALL, NULL, NULL);
            SysWork_StateStepIncrement(0);

        case 2:
            g_SysWork.field_28 += g_DeltaTime0;

            g_SysWork.player_4C.chara_0.position_18.vx = FP_MULTIPLY_FLOAT(Math_Sin(FP_ANGLE(135.0f) - (g_SysWork.field_28 >> 2)), 0.9f, Q12_SHIFT) + Q12(60.0f);
            g_SysWork.player_4C.chara_0.position_18.vz = FP_MULTIPLY_FLOAT(Math_Cos(FP_ANGLE(135.0f) - (g_SysWork.field_28 >> 2)), 0.9f, Q12_SHIFT) - Q12(20.0f);
            g_SysWork.player_4C.chara_0.rotation_24.vy = FP_ANGLE(45.0f) - (g_SysWork.field_28 >> 2);

            if ((g_SysWork.field_28 >> 2) > FP_ANGLE(140.7f))
            {
                SysWork_StateStepIncrement(0);
            }
            break;

        case 3:
            func_80085EB8(0, &g_SysWork.player_4C.chara_0, 52, false);
            SysWork_StateStepIncrement(0);

        case 4:
            MapMsg_DisplayAndHandleSelection(false, 15, 0, 0, 0, false);
            break;

        case 5:
            func_80085EB8(0, &g_SysWork.player_4C.chara_0, 71, false);
            SysWork_StateStepIncrement(0);

        case 6:
            SysWork_StateStepIncrementDelayed(Q12(1.5f), false);
            break;

        case 7:
            func_80088D0C();
            Chara_Spawn(Chara_Alessa, 0, Q12(60.0f), Q12(-23.0f), 0, 3);
            SysWork_StateStepIncrement(0);
            break;

        case 8:
            Camera_PositionSet(NULL, Q12(56.79f), Q12(-7.9f), Q12(-27.3f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);
            Camera_LookAtSet(NULL, Q12(57.96f), Q12(-5.03f), Q12(-24.77f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);

            g_SysWork.player_4C.chara_0.position_18.vx = Q12(59.6f);
            g_SysWork.player_4C.chara_0.position_18.vz = Q12(-19.0f);
            g_SysWork.player_4C.chara_0.rotation_24.vy = FP_ANGLE(180.0f);

            func_80085EB8(0, &g_SysWork.player_4C.chara_0, 51, false);
            func_80085EB8(0, &g_SysWork.npcs_1A0[0], 1, false);

            Savegame_EventFlagSet(EventFlag_412);
            D_800D4E09 = 0;
            SysWork_StateStepIncrement(0);

        case 9:
            SysWork_StateStepIncrementDelayed(Q12(2.0f), false);
            break;

        case 10:
            Camera_PositionSet(NULL, Q12(57.42f), Q12(-2.48f), Q12(-16.58f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);
            Camera_LookAtSet(NULL, Q12(59.23f), Q12(-1.24f), Q12(-19.93f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);
            g_SysWork.player_4C.chara_0.position_18.vx = Q12(59.0f);
            g_SysWork.player_4C.chara_0.position_18.vz = Q12(-19.5f);
            g_SysWork.player_4C.chara_0.rotation_24.vy = ratan2(
                g_SysWork.npcs_1A0[0].position_18.vx - g_SysWork.player_4C.chara_0.position_18.vx,
                g_SysWork.npcs_1A0[0].position_18.vz - g_SysWork.player_4C.chara_0.position_18.vz);

            func_8003D468(34, true);
            Savegame_EventFlagSet(EventFlag_412);
            SysWork_StateStepIncrement(0);

        case 11:
            SysWork_StateStepIncrementDelayed(Q12(0.5f), false);
            break;

        case 12:
            g_SysWork.npcs_1A0[0].timer_C6 += FP_MULTIPLY_FLOAT_PRECISE(g_DeltaTime0, 0.25f, Q12_SHIFT);
            SysWork_StateStepIncrementDelayed(Q12(0.3f), false);
            Map_MessageWithAudio(16, &D_800D4E08, &D_800D3B40);
            break;

        case 13:
            func_80085EB8(0, &g_SysWork.player_4C.chara_0, 111, false);
            SysWork_StateStepIncrement(0);

        case 14:
            Map_MessageWithAudio(16, &D_800D4E08, &D_800D3B40);
            g_SysWork.npcs_1A0[0].timer_C6 += FP_MULTIPLY_FLOAT_PRECISE(g_DeltaTime0, 0.25f, Q12_SHIFT);
            if (g_SysWork.npcs_1A0[0].timer_C6 > Q12(1.0f))
            {
                g_SysWork.npcs_1A0[0].timer_C6 = Q12(1.0f);
            }
            break;

        case 15:
            g_SysWork.npcs_1A0[0].timer_C6 += FP_MULTIPLY_FLOAT_PRECISE(g_DeltaTime0, 0.25f, Q12_SHIFT);
            if (g_SysWork.npcs_1A0[0].timer_C6 > Q12(1.0f))
            {
                g_SysWork.npcs_1A0[0].timer_C6 = Q12(1.0f);
                SysWork_StateStepIncrement(0);
            }
            break;

        case 16:
            func_80088F94(&g_SysWork.npcs_1A0[0], 0, 0);
            SysWork_StateStepIncrement(0);

        case 17:
            func_80085EB8(1, &g_SysWork.player_4C.chara_0, 0, false);
            break;

        case 18:
            Camera_PositionSet(NULL, Q12(64.87f), Q12(-5.4f), Q12(-14.82f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);
            Camera_LookAtSet(NULL, Q12(62.29f), Q12(-3.36f), Q12(-17.09f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);

            func_80085EB8(0, &g_SysWork.player_4C.chara_0, 51, false);
            func_8003D01C();
            sharedFunc_800D2EF4_0_s00();

            Savegame_EventFlagSet(EventFlag_412);
            SysWork_StateStepIncrement(0);

        case 19:
            Map_MessageWithAudio(17, &D_800D4E08, &D_800D3B40);
            if (g_SysWork.sysStateStep_C[0] != 19)
            {
                SysWork_StateStepReset();
            }
            break;

        case 20:
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(0.0f), false);
            break;

        case 21:
            Fs_QueueWaitForEmpty();
            vcReturnPreAutoCamWork(true);

            if (!hasSkippedEarly)
            {
                func_8003D01C();
                sharedFunc_800D2EF4_0_s00();
            }

            g_SysWork.player_4C.chara_0.position_18.vx = Q12(59.0f);
            g_SysWork.player_4C.chara_0.position_18.vz = Q12(-19.5f);
            g_SysWork.player_4C.chara_0.rotation_24.vy = FP_ANGLE(164.1f);

            func_80088F94(&g_SysWork.npcs_1A0[0], 0, 0);
            sharedFunc_800D2244_0_s00(true);

            SysWork_StateSetNext(SysState_Gameplay);

            SysWork_StateStepIncrementAfterFade(0, false, 0, Q12(0.0f), false);
            SysWork_StateStepIncrement(0);

        default:
            sharedFunc_800D2244_0_s00(false);
            SysWork_StateSetNext(SysState_Gameplay);

            Savegame_EventFlagSet(EventFlag_410);
            Savegame_EventFlagClear(EventFlag_407);
            Savegame_MapMarkingSet(MapMarkFlag_ResortTown_LighthouseCheck);

            SysWork_StateStepIncrementAfterFade(0, false, 2, Q12(0.0f), false);
            vcReturnPreAutoCamWork(false);
            D_800D4E09 = 0;
            break;
    }
}

#include "maps/shared/SysWork_StateStepIncrementAfterTime.h" // 0x800CFB9C

void func_800CFC34(void) // 0x800CFC34
{
    s32 i;
    s32 curTimerVal;
    s32 pitch;
    s32 pitchDiv512;

    curTimerVal = D_800D3C90;
    pitch       = (Math_Sin(curTimerVal >> 3) * 2) + Math_Cos(curTimerVal >> 4) + Math_Sin(Math_Cos(curTimerVal >> 4));

    D_800D3C90 += g_DeltaTime0;
    D_800D3C90 += g_DeltaTime0;

    pitchDiv512 = pitch >> 9; // `/ 512`

    if (g_SysWork.sysStateStep_C[0] == 11 || g_SysWork.sysStateStep_C[0] == 13)
    {
        D_800D3C94 -= FP_MULTIPLY_FLOAT_PRECISE(g_DeltaTime0, 0.5f, Q12_SHIFT);
        if (D_800D3C94 < 0)
        {
            D_800D3C94 = 0;
        }
        func_800463C0(Sfx_Unk1467, 0, ~(D_800D3C94 >> 4), pitchDiv512);
    }
    else if (g_SysWork.sysStateStep_C[0] > 0)
    {
        D_800D3C94 += FP_MULTIPLY_FLOAT_PRECISE(g_DeltaTime0, 0.25f, Q12_SHIFT);
        if (D_800D3C94 > 4080)
        {
            D_800D3C94 = 4080;
        }
        func_800463C0(Sfx_Unk1467, 0, ~(D_800D3C94 >> 4), pitchDiv512);
    }

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            sharedFunc_800D20E4_0_s00();
            func_8004690C(Sfx_Unk1611);

            if (Savegame_EventFlagGet(EventFlag_456) && Savegame_EventFlagGet(EventFlag_457) &&
                Savegame_EventFlagGet(EventFlag_458) && Savegame_EventFlagGet(EventFlag_459))
            {
                Savegame_EventFlagSet(EventFlag_469);
            }

            D_800D3C88 = 0;
            Fs_QueueStartReadTim(FILE_TIM_ENBAN_TIM, FS_BUFFER_1, &D_800D3B70);
            Fs_QueueStartRead(FILE_ANIM_UFO5_DMS, FS_BUFFER_13);

            D_800D4E28 = NO_VALUE;

            ScreenFade_ResetTimestep();

            Sd_EngineCmd(Sfx_Unk1467);
            func_800463C0(Sfx_Unk1467, 0, 255, 0);

            D_800D3C94 = 0;
            D_800D3C90 = 0;
            Savegame_EventFlagSet(EventFlag_417);

            D_800D3C8C = 0;
            SysWork_StateStepIncrement(0);

        case 1:
            func_80085DF0();
            break;

        case 2:
            if (Fs_QueueDoThingWhenEmpty())
            {
                SysWork_StateStepIncrement(0);
            }
            break;

        case 3:
            D_800D4E28 = 0;
            SysWork_StateStepIncrementAfterFade(0, true, 3, Q12(0.0f), false);
            DmsHeader_FixOffsets(FS_BUFFER_13);
            func_8003D03C();
            sharedFunc_800D2EB4_0_s00();
            Game_TurnFlashlightOn();
            SysWork_StateStepIncrement(0);

        case 4:
            SysWork_StateStepIncrementAfterFade(2, false, 0, Q12(0.0f), false);

        case 5:
            Map_MessageWithAudio(23, &D_800D3C88, &D_800D3B6C);
            break;

        case 6:
            SysWork_StateStepIncrementAfterTime(&D_800D4E28, Q12(40.0f), Q12(0.0f), Q12(30.0f), true, true);

            for (i = 0; i < 15; i++)
            {
                sharedFunc_800CE5D4_1_s03(&D_800D3B78[i], Q12(0.5f), Q12(0.05f), 0);
            }
            break;

        case 7:
            if (Savegame_EventFlagGet(EventFlag_469))
            {
                Fs_QueueStartReadTim(FILE_TIM_UFO1_TIM, FS_BUFFER_1, &D_800D3B44[0]);
                Fs_QueueStartReadTim(FILE_TIM_UFO6_TIM, FS_BUFFER_1, &D_800D3B44[1]);
            }
            SysWork_StateStepIncrement(0);

        case 8:
            MapMsg_DisplayAndHandleSelection(false, 24, 0, 0, 0, false);
            for (i = 0; i < 15; i++)
            {
                sharedFunc_800CE5D4_1_s03(&D_800D3B78[i], Q12(0.5f), Q12(0.05f), 0);
            }
            break;

        case 9:
            func_80080B58(&g_SysWork.playerBoneCoords_890[HarryBone_Head], &(SVECTOR){}, &(VECTOR3) { Q12(5.39f), Q12(-19.0f), Q12(-16.34f) });

            for (i = 0; i < 15; i++)
            {
                sharedFunc_800CE5D4_1_s03(&D_800D3B78[i], Q12(0.5f), Q12(0.15f), 0);
            }

            SysWork_StateStepIncrementDelayed(Q12(2.5f), false);

            if (g_SysWork.sysStateStep_C[0] != 9)
            {
                Savegame_EventFlagSet(EventFlag_412);
            }
            break;

        case 10:
            if (D_800D3C8C > Q12(8.0f))
            {
                if (Savegame_EventFlagGet(EventFlag_469))
                {
                    SysWork_StateStepSet(0, 12);
                }
                else
                {
                    SysWork_StateStepSet(0, 11);
                }
            }
            break;

        case 11:
            SysWork_StateStepIncrementDelayed(Q12(2.5f), false);

            if (g_SysWork.sysStateStep_C[0] != 11)
            {
                SysWork_StateStepReset();
            }
            break;

        case 12:
            SysWork_StateStepIncrementDelayed(Q12(4.0f), false);

            if (g_SysWork.sysStateStep_C[0] != 12)
            {
                SysWork_StateStepIncrementAfterFade(0, false, 2, Q12(0.0f), false);
            }
            break;

        case 13:
            SysWork_StateStepIncrementAfterFade(2, true, 1, Q12(1.0f), false);
            break;

        default:
            vcReturnPreAutoCamWork(true);
            Savegame_EventFlagSet(EventFlag_460);
            func_80086470(3, InventoryItemId_ChannelingStone, 1, false);
            func_8003D01C();
            sharedFunc_800D2EF4_0_s00();
            D_800D4E28 = NO_VALUE;

            if (Savegame_EventFlagGet(EventFlag_469))
            {
                SysWork_StateSetNext(SysState_Gameplay);
                D_800C4414 &= ~(1 << 5);
            }
            else
            {
                SysWork_StateStepIncrementAfterFade(0, false, 2, Q12(0.0f), false);
                sharedFunc_800D2244_0_s00(false);

                SysWork_StateSetNext(SysState_Gameplay);

                Sd_EngineCmd(Sfx_Unk1611);
                func_8004690C(Sfx_Unk1467);
            }
            break;
    }

    if (g_SysWork.sysStateStep_C[0] == 10 || g_SysWork.sysStateStep_C[0] == 12 || g_SysWork.sysStateStep_C[0] == 13)
    {
        D_800D3C8C += g_DeltaTime0;

        for (i = 0; i < 15; i++)
        {
            if (Savegame_EventFlagGet(EventFlag_469) || D_800D3C8C < D_800D3C2C[i])
            {
                sharedFunc_800CE5D4_1_s03(&D_800D3B78[i], Q12(0.5f), Q12(0.05f), 0);

                if (D_800D3C8C > Q12(1.5f))
                {
                    D_800D3B78[i].vx += FP_MULTIPLY_FLOAT_PRECISE(g_DeltaTime0, 3.5f, 12);
                    D_800D3B78[i].vy += FP_MULTIPLY_FLOAT_PRECISE(g_DeltaTime0, 1.2f, 12);
                    D_800D3B78[i].vz += FP_MULTIPLY_FLOAT_PRECISE(g_DeltaTime0, -0.2f, 12);
                }
            }
        }
    }

    if (D_800D4E28 >= 0)
    {
        // TODO: Remove null chars from "HERO" once later rodata is added.
        Dms_CharacterGetPosRot(&g_SysWork.player_4C.chara_0.position_18, &g_SysWork.player_4C.chara_0.rotation_24, "HERO\0\0\0\0", D_800D4E28, FS_BUFFER_13);
        vcChangeProjectionValue(Dms_CameraGetTargetPos(&D_800D4E0C, &D_800D4E1C, NULL, D_800D4E28, FS_BUFFER_13));
        vcUserCamTarget(&D_800D4E0C, NULL, true);
        vcUserWatchTarget(&D_800D4E1C, NULL, true);
    }
}

INCLUDE_ASM("asm/maps/map6_s02/nonmatchings/map6_s02_2", func_800D0500);

INCLUDE_ASM("asm/maps/map6_s02/nonmatchings/map6_s02_2", func_800D1040);

INCLUDE_ASM("asm/maps/map6_s02/nonmatchings/map6_s02_2", func_800D1330);

INCLUDE_ASM("asm/maps/map6_s02/nonmatchings/map6_s02_2", func_800D1658);

INCLUDE_ASM("asm/maps/map6_s02/nonmatchings/map6_s02_2", func_800D1718);

INCLUDE_ASM("asm/maps/map6_s02/nonmatchings/map6_s02_2", func_800D1AE4);

INCLUDE_ASM("asm/maps/map6_s02/nonmatchings/map6_s02_2", func_800D1D40);

INCLUDE_ASM("asm/maps/map6_s02/nonmatchings/map6_s02_2", func_800D1EB8);

INCLUDE_ASM("asm/maps/map6_s02/nonmatchings/map6_s02_2", func_800D2170);

INCLUDE_ASM("asm/maps/map6_s02/nonmatchings/map6_s02_2", func_800D2364);

INCLUDE_ASM("asm/maps/map6_s02/nonmatchings/map6_s02_2", func_800D32D0);

INCLUDE_RODATA("asm/maps/map6_s02/nonmatchings/map6_s02_2", D_800CAB90);

INCLUDE_RODATA("asm/maps/map6_s02/nonmatchings/map6_s02_2", D_800CAB98);
