#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "bodyprog/memcard.h"
#include "bodyprog/player_logic.h"
#include "bodyprog/ranking.h"
#include "bodyprog/sound_system.h"
#include "main/rng.h"
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

INCLUDE_ASM("maps/map6_s02/nonmatchings/map6_s02_2", func_800CE88C);

#include "maps/shared/Map_RoomBgmInit_6_s00.h" // 0x800CEA88

void func_800CED6C(void) {}

void func_800CED74(s_SubCharacter* chara, bool arg1) // 0x800CED74
{
    VECTOR3 sp10;
    VECTOR3 sp20;
    bool    cond;
    q19_12  height;
    bool    vcPrsFViewFlag;
    bool    vcPrsFViewFlag2;
    bool    vcOldPrsFViewFlag;
    bool    warp;

    if (arg1)
    {
        D_800D3C84 = NO_VALUE;
    }

    if (chara->position_18.vy > Q12(3.2f))
    {
        cond = false;

        Math_Vector3Set(&sp10, Q12(-19.05f), Q12(1.41f), Q12(-18.46f));
        Math_Vector3Set(&sp20, Q12(-19.85f), Q12(3.46f), Q12(-21.8f));
    }
    else
    {
        cond   = true;
        height = MAX(chara->position_18.vy - Q12(3.56f), Q12(-9.65f));

        Math_Vector3Set(&sp10, Q12(-20.0f), height, Q12(-20.01f));
        Math_Vector3Set(&sp20, Q12(-20.0f), height + Q12(2.0f), Q12(-19.99f));
    }

    // TODO: These `VC_PRS_F_VIEW_F`/`VC_OLD_PRS_F_VIEW_F` checks have showed up a few times now.
    // With the same odd XOR pattern, and `VC_PRS_F_VIEW_F` check followed by `VC_OLD_PRS_F_VIEW_F`.
    // Inlines have been seen to change condition checks into XOR before, but no luck making an inline for this check yet though.
    vcPrsFViewFlag = (vcWork.flags_8 & VC_PRS_F_VIEW_F) == VC_PRS_F_VIEW_F;
    if (((g_GameWorkConst->config_0.optExtraViewCtrl_28 && (vcPrsFViewFlag ^ 1) != 0) ||
         (!g_GameWorkConst->config_0.optExtraViewCtrl_28 && vcPrsFViewFlag)) &&
        (g_GameWorkConst->config_0.optExtraViewMode_29 != 0))
    {
        vcPrsFViewFlag2 = (vcWork.flags_8 & VC_PRS_F_VIEW_F) == VC_PRS_F_VIEW_F;

        if ((g_GameWorkConst->config_0.optExtraViewCtrl_28 && (vcPrsFViewFlag2 ^ 1) != 0) ||
            (!g_GameWorkConst->config_0.optExtraViewCtrl_28 && vcPrsFViewFlag2))
        {
            vcOldPrsFViewFlag = (vcWork.flags_8 & VC_OLD_PRS_F_VIEW_F) == VC_OLD_PRS_F_VIEW_F;

            if ((g_GameWorkConst->config_0.optExtraViewCtrl_28 && (vcOldPrsFViewFlag ^ 1) == 0) ||
                (!g_GameWorkConst->config_0.optExtraViewCtrl_28 && !vcOldPrsFViewFlag))
            {
                vcReturnPreAutoCamWork(true);
            }
            else
            {
                vcReturnPreAutoCamWork(false);
            }
        }
        else
        {
            vcReturnPreAutoCamWork(false);
        }
    }
    else
    {
        warp = (cond != D_800D3C84);
        vcUserCamTarget(&sp10, NULL, warp);
        vcUserWatchTarget(&sp20, NULL, warp);

        if (warp)
        {
            vcExecCamera();
        }
    }

    D_800D3C84 = cond;
}

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

void func_800CF0B8(void) // 0x800CF0B8
{
    bool hasSkippedEarly;

    Savegame_EventFlagClear(EventFlag_412);

    hasSkippedEarly = false;
    if ((g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.skip_4) &&
        g_SysWork.sysStateStep_C[0] >= 2 && g_SysWork.sysStateStep_C[0] <= 19)
    {
        // Sets flag to `true` if player skipped before step 19.
        hasSkippedEarly = g_SysWork.sysStateStep_C[0] < 19;
        SysWork_StateStepSet(0, 20);
    }

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            Player_ControlFreeze();

            g_SysWork.field_30 = 20;
            ScreenFade_ResetTimestep();

            func_8003D03C();
            sharedFunc_800D2EB4_0_s00();

            Savegame_EventFlagClear(EventFlag_405);

            SysWork_StateStepIncrement(0);

            // Warp camera.
            Camera_PositionSet(NULL, Q12(57.09f), Q12(-3.23f), Q12(-20.41f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);
            Camera_LookAtSet(NULL, Q12(60.07f), Q12(-0.94f), Q12(-19.06f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);

            Savegame_EventFlagSet(EventFlag_412);

            // Warp player.
            g_SysWork.playerWork_4C.player_0.position_18.vx = Q12_MULT_FLOAT(Math_Sin(Q12_ANGLE(135.0f)), 0.9f) + Q12(60.0f);
            g_SysWork.playerWork_4C.player_0.position_18.vy = Q12(1.64f);
            g_SysWork.playerWork_4C.player_0.position_18.vz = Q12_MULT_FLOAT(Math_Cos(Q12_ANGLE(135.0f)), 0.9f) - Q12(20.0f);
            g_SysWork.playerWork_4C.player_0.rotation_24.vy = Q12_ANGLE(45.0f);

            D_800D4E09 = 1;
            break;

        case 1:
            SysWork_StateStepIncrementAfterFade(0, false, 0, Q12(0.0f), false);
            func_80085EB8(0, &g_SysWork.playerWork_4C.player_0, 53, false);
            Chara_Load(0, Chara_Alessa, &g_SysWork.npcCoords_FC0[0], CHARA_FORCE_FREE_ALL, NULL, NULL);
            SysWork_StateStepIncrement(0);

        case 2:
            g_SysWork.field_28 += g_DeltaTime;

            // Warp player.
            g_SysWork.playerWork_4C.player_0.position_18.vx = Q12_MULT_FLOAT(Math_Sin(Q12_ANGLE(135.0f) - (g_SysWork.field_28 >> 2)), 0.9f) + Q12(60.0f);
            g_SysWork.playerWork_4C.player_0.position_18.vz = Q12_MULT_FLOAT(Math_Cos(Q12_ANGLE(135.0f) - (g_SysWork.field_28 >> 2)), 0.9f) - Q12(20.0f);
            g_SysWork.playerWork_4C.player_0.rotation_24.vy = Q12_ANGLE(45.0f) - (g_SysWork.field_28 >> 2);

            if ((g_SysWork.field_28 >> 2) > Q12_ANGLE(140.7f))
            {
                SysWork_StateStepIncrement(0);
            }
            break;

        case 3:
            func_80085EB8(0, &g_SysWork.playerWork_4C.player_0, 52, false);
            SysWork_StateStepIncrement(0);

        case 4:
            MapMsg_DisplayAndHandleSelection(false, 15, 0, 0, 0, false);
            break;

        case 5:
            func_80085EB8(0, &g_SysWork.playerWork_4C.player_0, 71, false);
            SysWork_StateStepIncrement(0);

        case 6:
            SysWork_StateStepIncrementDelayed(Q12(1.5f), false);
            break;

        case 7:
            Chara_ProcessLoads();
            Chara_Spawn(Chara_Alessa, 0, Q12(60.0f), Q12(-23.0f), 0, 3);
            SysWork_StateStepIncrement(0);
            break;

        case 8:
            // Warp player.
            Camera_PositionSet(NULL, Q12(56.79f), Q12(-7.9f), Q12(-27.3f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);
            Camera_LookAtSet(NULL, Q12(57.96f), Q12(-5.03f), Q12(-24.77f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);

            // Warp player.
            g_SysWork.playerWork_4C.player_0.position_18.vx = Q12(59.6f);
            g_SysWork.playerWork_4C.player_0.position_18.vz = Q12(-19.0f);
            g_SysWork.playerWork_4C.player_0.rotation_24.vy = Q12_ANGLE(180.0f);

            func_80085EB8(0, &g_SysWork.playerWork_4C.player_0, 51, false);
            func_80085EB8(0, &g_SysWork.npcs_1A0[0], 1, false);

            Savegame_EventFlagSet(EventFlag_412);
            D_800D4E09 = 0;
            SysWork_StateStepIncrement(0);

        case 9:
            SysWork_StateStepIncrementDelayed(Q12(2.0f), false);
            break;

        case 10:
            // Warp camera.
            Camera_PositionSet(NULL, Q12(57.42f), Q12(-2.48f), Q12(-16.58f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);
            Camera_LookAtSet(NULL, Q12(59.23f), Q12(-1.24f), Q12(-19.93f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);

            // Warp player.
            g_SysWork.playerWork_4C.player_0.position_18.vx = Q12(59.0f);
            g_SysWork.playerWork_4C.player_0.position_18.vz = Q12(-19.5f);
            g_SysWork.playerWork_4C.player_0.rotation_24.vy = ratan2(g_SysWork.npcs_1A0[0].position_18.vx - g_SysWork.playerWork_4C.player_0.position_18.vx,
                                                                g_SysWork.npcs_1A0[0].position_18.vz - g_SysWork.playerWork_4C.player_0.position_18.vz);

            WorldGfx_CharaModelTransparentSet(Chara_Alessa, true);
            Savegame_EventFlagSet(EventFlag_412);
            SysWork_StateStepIncrement(0);

        case 11:
            SysWork_StateStepIncrementDelayed(Q12(0.5f), false);
            break;

        case 12:
            g_SysWork.npcs_1A0[0].timer_C6 += Q12_MULT_FLOAT_PRECISE(g_DeltaTime, 0.25f);
            SysWork_StateStepIncrementDelayed(Q12(0.3f), false);
            Map_MessageWithAudio(16, &D_800D4E08, &D_800D3B40);
            break;

        case 13:
            func_80085EB8(0, &g_SysWork.playerWork_4C.player_0, 111, false);
            SysWork_StateStepIncrement(0);

        case 14:
            Map_MessageWithAudio(16, &D_800D4E08, &D_800D3B40);

            g_SysWork.npcs_1A0[0].timer_C6 += Q12_MULT_FLOAT_PRECISE(g_DeltaTime, 0.25f);
            if (g_SysWork.npcs_1A0[0].timer_C6 > Q12(1.0f))
            {
                g_SysWork.npcs_1A0[0].timer_C6 = Q12(1.0f);
            }
            break;

        case 15:
            g_SysWork.npcs_1A0[0].timer_C6 += Q12_MULT_FLOAT_PRECISE(g_DeltaTime, 0.25f);
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
            func_80085EB8(1, &g_SysWork.playerWork_4C.player_0, 0, false);
            break;

        case 18:
            // Warp camera.
            Camera_PositionSet(NULL, Q12(64.87f), Q12(-5.4f), Q12(-14.82f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);
            Camera_LookAtSet(NULL, Q12(62.29f), Q12(-3.36f), Q12(-17.09f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);

            func_80085EB8(0, &g_SysWork.playerWork_4C.player_0, 51, false);
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

            // Warp player.
            g_SysWork.playerWork_4C.player_0.position_18.vx = Q12(59.0f);
            g_SysWork.playerWork_4C.player_0.position_18.vz = Q12(-19.5f);
            g_SysWork.playerWork_4C.player_0.rotation_24.vy = Q12_ANGLE(164.1f);

            func_80088F94(&g_SysWork.npcs_1A0[0], 0, 0);
            Player_ControlUnfreeze(true);

            SysWork_StateSetNext(SysState_Gameplay);
            SysWork_StateStepIncrementAfterFade(0, false, 0, Q12(0.0f), false);
            SysWork_StateStepIncrement(0);

        default:
            Player_ControlUnfreeze(false);
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

    D_800D3C90 += g_DeltaTime;
    D_800D3C90 += g_DeltaTime;

    pitchDiv512 = pitch >> 9; // `/ 512`

    if (g_SysWork.sysStateStep_C[0] == 11 || g_SysWork.sysStateStep_C[0] == 13)
    {
        D_800D3C94 -= Q12_MULT_FLOAT_PRECISE(g_DeltaTime, 0.5f);
        if (D_800D3C94 < 0)
        {
            D_800D3C94 = 0;
        }
        Sd_SfxAttributesUpdate(Sfx_Unk1467, 0, ~(D_800D3C94 >> 4), pitchDiv512);
    }
    else if (g_SysWork.sysStateStep_C[0] > 0)
    {
        D_800D3C94 += Q12_MULT_FLOAT_PRECISE(g_DeltaTime, 0.25f);
        if (D_800D3C94 > 4080)
        {
            D_800D3C94 = 4080;
        }
        Sd_SfxAttributesUpdate(Sfx_Unk1467, 0, ~(D_800D3C94 >> 4), pitchDiv512);
    }

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            Player_ControlFreeze();
            Sd_SfxStop(Sfx_Unk1611);

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

            SD_Call(Sfx_Unk1467);
            Sd_SfxAttributesUpdate(Sfx_Unk1467, 0, 255, 0);

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
            func_80080B58(&g_SysWork.playerBoneCoords_890[HarryBone_Head], &(SVECTOR) { 0, 0, 0, 0 }, &(VECTOR3) { Q12(5.39f), Q12(-19.0f), Q12(-16.34f) });

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
                Player_ControlUnfreeze(false);

                SysWork_StateSetNext(SysState_Gameplay);

                SD_Call(Sfx_Unk1611);
                Sd_SfxStop(Sfx_Unk1467);
            }
            break;
    }

    if (g_SysWork.sysStateStep_C[0] == 10 || g_SysWork.sysStateStep_C[0] == 12 || g_SysWork.sysStateStep_C[0] == 13)
    {
        D_800D3C8C += g_DeltaTime;

        for (i = 0; i < 15; i++)
        {
            if (Savegame_EventFlagGet(EventFlag_469) || D_800D3C8C < D_800D3C2C[i])
            {
                sharedFunc_800CE5D4_1_s03(&D_800D3B78[i], Q12(0.5f), Q12(0.05f), 0);

                if (D_800D3C8C > Q12(1.5f))
                {
                    D_800D3B78[i].vx += FP_MULTIPLY_FLOAT_PRECISE(g_DeltaTime, 3.5f, 12);
                    D_800D3B78[i].vy += FP_MULTIPLY_FLOAT_PRECISE(g_DeltaTime, 1.2f, 12);
                    D_800D3B78[i].vz += FP_MULTIPLY_FLOAT_PRECISE(g_DeltaTime, -0.2f, 12);
                }
            }
        }
    }

    if (D_800D4E28 >= 0)
    {
        // TODO: Remove null chars from "HERO" once later rodata is added.
        Dms_CharacterGetPosRot(&g_SysWork.playerWork_4C.player_0.position_18, &g_SysWork.playerWork_4C.player_0.rotation_24, "HERO\0\0\0\0", D_800D4E28, FS_BUFFER_13);
        vcChangeProjectionValue(Dms_CameraGetTargetPos(&D_800D4E0C, &D_800D4E1C, NULL, D_800D4E28, FS_BUFFER_13));
        vcUserCamTarget(&D_800D4E0C, NULL, true);
        vcUserWatchTarget(&D_800D4E1C, NULL, true);
    }
}

void func_800D0500(void) // 0x800D0500
{
    s32 temp_v0;
    s32 var_s2;
    s32 var_v0;
    s32 var_v0_2;
    s32 var_v1;

    g_SysWork.sysFlags_22A0 |= SysFlag_Freeze;

    var_s2 = 0;

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            D_800D3CA0 = 0;
            func_80087EDC(41);
            break;

        case 1:
            Sd_SfxStop(Sfx_Unk1467);
            Fs_QueueWaitForEmpty();
            Anim_CharaTypeAnimInfoClear();
            Fs_QueueStartReadTim(FILE_TIM_UFO2_TIM, FS_BUFFER_1, &D_800D3B44[2]);
            Fs_QueueStartReadTim(FILE_TIM_UFO3_TIM, FS_BUFFER_1, &D_800D3B44[3]);
            Fs_QueueStartReadTim(FILE_TIM_UFO7_TIM, FS_BUFFER_1, &D_800D3B44[4]);
            SysWork_StateStepIncrementAfterFade(0, false, 1, Q12(0.5f), false);

            D_800D3C9C = NO_VALUE;
            D_800D4E2C = 0;
            D_800D4E2D = 0;
            D_800D3C9E = 0;

            SD_Call(Sfx_Unk1613);

            D_800D3C98 = 0;

            SysWork_StateStepIncrement(0);

        case 2:
            SysWork_StateStepIncrementDelayed(Q12(5.0f), false);
            D_800D3C98 += g_DeltaTime;

            // TODO: Some kind of `Q12_ANGLE_ABS`?
            var_v0 = D_800D3C98;
            if (D_800D3C98 < 0)
            {
                var_v0 = D_800D3C98 + 0xFFF;
            }

            if (D_800D3C98 - FP_TO(FP_FROM(var_v0, Q12_SHIFT), Q12_SHIFT) > Q12_ANGLE(180.0f))
            {
                Gfx_BackgroundSpriteDraw_2(&D_800D3B44[1]);
            }
            else
            {
                Gfx_BackgroundSpriteDraw_2(&D_800D3B44[0]);
            }

            temp_v0 = D_800D3C9C - 3;
            var_v1  = 0;
            if (temp_v0 >= 0)
            {
                var_v1 = temp_v0;
            }
            D_800D3C9C = var_v1;

            Sd_SfxAttributesUpdate(Sfx_Unk1613, 0, D_800D3C9C, 0);
            break;

        case 3:
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(0.5f), false);

            D_800D3C98 += g_DeltaTime;
            var_v0_2    = D_800D3C98;
            if (D_800D3C98 < 0)
            {
                var_v0_2 = D_800D3C98 + 0xFFF;
            }

            if (D_800D3C98 - FP_TO(FP_FROM(var_v0_2, Q12_SHIFT), Q12_SHIFT) > Q12_ANGLE(180.0f))
            {
                Gfx_BackgroundSpriteDraw_2(&D_800D3B44[1]);
            }
            else
            {
                Gfx_BackgroundSpriteDraw_2(&D_800D3B44[0]);
            }

            var_v1 = D_800D3C9C + 3;
            if (var_v1 > 255)
            {
                var_v1 = 255;
            }
            D_800D3C9C = var_v1;

            Sd_SfxAttributesUpdate(Sfx_Unk1613, 0, D_800D3C9C, 0);
            break;

        case 4:
            Fs_QueueStartReadTim(FILE_TIM_UFO4_TIM, FS_BUFFER_1, D_800D3B44);
            Sd_SfxStop(Sfx_Unk1613);
            SD_Call(Sfx_Unk1612);
            Fs_QueueWaitForEmpty();
            SysWork_StateStepIncrement(0);
            Sd_XaPreLoadAudioPreTaskAdd(Sfx_XaAudio565);

        case 5:
            SysWork_StateStepIncrementDelayed(Q12(2.5f), false);
            break;

        case 6:
            SD_Call(Sfx_XaAudio565);
            SysWork_StateStepIncrement(0);

        case 7:
            if (Sd_AudioStreamingCheck() != 1)
            {
                break;
            }
            SysWork_StateStepIncrement(0);

        case 8:
            SysWork_StateStepIncrementDelayed(Q12(1.0f), false);
            break;

        case 9:
            SysWork_StateStepIncrementAfterFade(0, false, 0, Q12(2.0f), false);
            Savegame_EventFlagSet(EventFlag_418);
            SysWork_StateStepIncrement(0);

        case 10:
        case 11:
            if (g_SysWork.sysStateStep_C[0] == 10)
            {
                SysWork_StateStepIncrementDelayed(Q12(6.5f), false);
            }
            else
            {
                SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(2.0f), false);
            }

            Gfx_MapMsg_Draw(18);
            Gfx_BackgroundSpriteDraw_2(&D_800D3B44[2]);
            break;

        case 12:
            SysWork_StateStepIncrementDelayed(Q12(1.8f), false);
            break;

        case 13:
            SysWork_StateStepIncrementAfterFade(0, false, 0, Q12(2.0f), false);
            D_800D3C98 = 0;
            SysWork_StateStepIncrement(0);

        case 14:
        case 15:
            if (g_SysWork.sysStateStep_C[0] == 14)
            {
                SysWork_StateStepIncrementDelayed(Q12(4.2f), false);
            }
            else
            {
                SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(2.0f), false);
            }

            Gfx_BackgroundSpriteDraw_2(&D_800D3B44[3]);

            D_800D3C98 += g_DeltaTime;
            if (D_800D3C98 % Q12(0.2f) > Q12(0.1f))
            {
                func_800D1040(0);
            }
            else
            {
                func_800D1040(1);
            }

            func_800892A4(10);
            break;

        case 16:
            if (Sd_AudioStreamingCheck())
            {
                break;
            }

            SysWork_StateStepIncrement(0);

        case 17:
            Fs_QueueStartReadTim(FILE_TIM_UFO5_TIM, FS_BUFFER_1, &D_800D3B44[1]);
            Fs_QueueWaitForEmpty();
            GameFs_StfRollBinLoad();
            Fs_QueueWaitForEmpty();
            SD_Call(Sfx_XaAudio562);
            SysWork_StateStepIncrement(0);

        case 18:
            if (Sd_AudioStreamingCheck() != 1)
            {
                break;
            }

            SysWork_StateStepIncrement(0);

        case 19:
            SysWork_StateStepIncrementAfterFade(0, false, 0, Q12(2.0f), false);
            SysWork_StateStepIncrement(0);

        case 20:
        case 21:
            if (g_SysWork.sysStateStep_C[0] == 20)
            {
                SysWork_StateStepIncrementDelayed(Q12(4.0f), false);
            }
            else
            {
                SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(2.0f), false);
            }
            Gfx_BackgroundSpriteDraw_2(D_800D3B44);
            break;

        case 22:
            SysWork_StateStepIncrementDelayed(Q12(3.8f), false);
            break;

        case 23:
            SysWork_StateStepIncrementAfterFade(0, false, 0, Q12(2.0f), false);
            D_800D3C98 = 0;
            SysWork_StateStepIncrement(0);

        case 24:
            Gfx_BackgroundSpriteDraw_2(&D_800D3B44[1]);
            switch (FP_FROM(D_800D3C98, Q12_SHIFT))
            {
                case 0:
                case 1:
                case 2:
                case 3:
                    func_800D1330(D_800D3C98 >> 2);
                    break;

                case 6:
                    Savegame_EventFlagSet(EventFlag_419);

                case 4:
                case 5:
                    func_800D1040(2);
                    break;

                default:
                    func_801E386C();
                    D_800D3CA0 = 1;
                    D_800D3C98 = 0;
                    SysWork_StateStepIncrement(0);

                case 7:
                case 8:
                case 9:
                case 10:
                case 11:
                case 12:
                case 13:
                    func_800D1040(3);
                    break;
            }

            D_800D3C98 += g_DeltaTime;
            if (D_800D4E2C == 0 && D_800D4E2D == 0)
            {
                if (Rng_Rand16() % 0x100 == 0)
                {
                    D_800D4E2C = Rng_GenerateUInt(-8, 7);
                    D_800D4E2D = Rng_GenerateUInt(-8, 7);
                }
            }
            else
            {
                if (Rng_Rand16() % 0x20 == 0)
                {
                    D_800D4E2C = 0;
                    D_800D4E2D = 0;
                }
            }
            break;

        default:
            Gfx_BackgroundSpriteDraw_2(&D_800D3B44[1]);

            if (D_800D3C9E >= 0)
            {
                D_800D3C9E -= g_DeltaTime;
                if (D_800D3C9E < 0)
                {
                    D_800D3C9E = -Rng_Rand16() % Q12(0.4f);
                }
                else
                {
                    func_800D1040(3);
                }
            }
            else
            {
                D_800D3C9E += g_DeltaTime;
                if (D_800D3C9E >= 0)
                {
                    D_800D3C9E = Rng_GenerateInt(Q12(1.0f), Q12(3.4f) - 1);
                }
                else
                {
                    func_800D1040(2);
                }
            }

            if (D_800D4E2C == 0 && D_800D4E2D == 0)
            {
                if (Rng_Rand16() % 0x100 == 0)
                {
                    D_800D4E2C = Rng_GenerateUInt(-8, 7);
                    D_800D4E2D = Rng_GenerateUInt(-8, 7);
                }
            }
            else if (Rng_Rand16() % 0x20 == 0)
            {
                D_800D4E2C = 0;
                D_800D4E2D = 0;
            }
            break;
    }

    D_800C48F0 += g_VBlanks;

    if (D_800D3CA0 == 1)
    {
        var_s2 = func_801E3970(); // Movie player? Credits?
        if (var_s2)
        {
            func_800D1040(4);

            if (D_800D4E2C == 0 && D_800D4E2D == 0)
            {
                if (Rng_Rand16() % 0x100 == 0)
                {
                    D_800D4E2C = Rng_GenerateUInt(-8, 7);
                    D_800D4E2D = Rng_GenerateUInt(-8, 7);
                }
            }
            else if (Rng_Rand16() % 0x20 == 0)
            {
                D_800D4E2C = 0;
                D_800D4E2D = 0;
            }
        }
    }

    if (g_SysWork.sysStateStep_C[0] >= 25)
    {
        if (Sd_AudioStreamingCheck() || var_s2 == 0)
        {
            D_800D3C98 = 0;
            return;
        }

        switch (g_Screen_FadeStatus)
        {
            case ScreenFadeState_Reset:
            case ScreenFadeState_None:
                D_800D3C98 += g_DeltaTime;
                if (D_800D3C98 >= Q12(4.0f))
                {
                    ScreenFade_Start(true, false, false);
                }
                break;

            case ScreenFadeState_FadeOutComplete:
                Savegame_EventFlagSet(EventFlag_588);
                SysWork_StateSetNext(SysState_Gameplay);
                break;
        }
    }
}

INCLUDE_ASM("maps/map6_s02/nonmatchings/map6_s02_2", func_800D1040);

void func_800D1330(s16 arg0) // 0x800D1330
{
    POLY_FT4* poly;
    s32       temp_t8;
    s32       temp_v0_5;
    s32       var_t1;
    s32       var_t2;
    s32       var_t4;
    s32       i;
    s32       var_v1;
    s32       temp_v0;
    s32       temp_v0_2;
    s32       temp_v0_4;
    s32       var_a3;
    s32       temp;

    poly = GsOUT_PACKET_P;

    temp_v0   = Q12_MULT_PRECISE(arg0, 76) - 88;
    temp_t8   = D_800D4E2D + temp_v0;
    temp_v0_5 = D_800D4E2D - 8;

    for (i = 0; i < 2; i++)
    {
        if (i == 0)
        {
            temp_v0_2 = D_800D4E2C + 18;
            temp      = Q12_MULT_PRECISE(arg0, 167) - 160;
            var_t1    = D_800D4E2C + temp;
            var_v1    = temp_v0_2;
            var_a3    = D_800D3B44[4].tPage[1];
            var_t2    = 0;
            var_t4    = 0xB2;
        }
        else
        {
            temp_v0_4 = Q12_MULT_PRECISE(arg0, 135) - 160;
            var_t1    = D_800D4E2C + 18;
            var_v1    = D_800D4E2C - temp_v0_4;
            var_a3    = D_800D3B44[4].tPage[1] + 1;
            var_t2    = 50;
            var_t4    = 142;
        }

        setPolyFT4(poly);

        setXY0Fast(poly, var_t1, temp_t8);
        setXY1Fast(poly, var_v1, temp_t8);
        setXY2Fast(poly, var_t1, temp_v0_5);
        setXY3Fast(poly, var_v1, temp_v0_5);

        setUV0AndClutSum(poly, var_t2, 0, getClut(D_800D3B44[4].clutX, D_800D3B44[4].clutY));
        setUV1AndTPageSum(poly, var_t2 + var_t4, 0, getTPage(1, 0, var_a3 << 6, ((var_a3 >> 4) & 1) << 8));
        setUV2Sum(poly, var_t2, 80);
        setUV3Sum(poly, var_t2 + var_t4, 80);

        setSemiTrans(poly, 0);
        setRGB0Fast(poly, 0x80, 0x80, 0x80);

        addPrim(g_OrderingTable0[g_ActiveBufferIdx].org, poly);
        poly++;
    }

    GsOUT_PACKET_P = poly;
}

void Map_WorldObjectsInit(void) // 0x800D1658
{
    WorldObjectInit(&g_WorldObject_SavePad, D_800A99E4.savePadName_4, -18.85f, 3.06f, -21.16f, 0.0f, 111.6f, 0.0f);

    D_800D4E09 = 0;
    D_800D4E6C = 0;
    D_800D4E6D = 0;
    D_800D4E6E = 0;
    D_800D4E70 = 0;

    g_SysWork.field_235C = NULL;
    g_SysWork.field_236C = NULL;

    func_8008D438();
    Gfx_MapInitMapEffectsUpdate(4, 4);

    Savegame_EventFlagSet(EventFlag_428);
}

void Map_WorldObjectsUpdate(void) // 0x800D1718
{
    s32    flags;
    q19_12 mag;
    MAP_CHUNK_CHECK_VARIABLE_DECL();

    flags = 0;

    if (PLAYER_IN_MAP_CHUNK(vx, 1, -1, 0, 0) && PLAYER_IN_MAP_CHUNK(vz, 1, -1, 0, 0))
    {
        flags = func_800D1D40();
        WorldGfx_ObjectAdd(&g_WorldObject_SavePad.object_0, &g_WorldObject_SavePad.position_1C, &g_WorldObject_SavePad.rotation_28);
    }
    else
    {
        Savegame_EventFlagClear(EventFlag_405);
        Savegame_EventFlagClear(EventFlag_406);
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, 2, -1, 2) && PLAYER_IN_MAP_CHUNK(vz, 1, -1, 0, 0))
    {
        mag = Math_Vector2MagCalc(g_SysWork.playerWork_4C.player_0.position_18.vx - Q12(60.0f),
                                  g_SysWork.playerWork_4C.player_0.position_18.vz + Q12(20.0f));
        if (mag < Q12(1.4f))
        {
            if (ratan2(g_SysWork.playerWork_4C.player_0.position_18.vx - Q12(60.0f),
                       g_SysWork.playerWork_4C.player_0.position_18.vz + Q12(20.0f)) > Q12_ANGLE(67.5f))
            {
                Savegame_EventFlagSet(EventFlag_407);
                D_800D4E6C = 6;
            }
        }

        if (!D_800D4E6D)
        {
            g_SysWork.pointLightIntensity_2378 = Q12(2.8f);
            Math_Vector3Set(&g_SysWork.pointLightPosition_2360, Q12(60.0f), Q12(-2.5f), Q12(-20.0f));
            Math_SetSVectorFast(&g_SysWork.pointLightRot_2370, Q12_ANGLE(-90.0f), Q12_ANGLE(0.0f), Q12_ANGLE(0.0f));

            func_800D2170(false);
            SD_Call(Sfx_Unk1611);

            D_800D4E6D = 1;
        }
        else if (g_SysWork.sysFlags_22A0 & SysFlag_6)
        {
            func_800D2170(true);
            D_800D4E6D = 1;
        }
        else if (D_800D4E6D == 1)
        {
            D_800D4E6D++;
            D_800C4414 |= 1 << 5;
        }

        D_800D4E70 += Q12_MULT_PRECISE(Rng_GenerateUInt(0, 4095), g_DeltaTime);

        Sd_SfxAttributesUpdate(Sfx_Unk1611, 0, ((Math_Sin(D_800D4E70) >> 10) - 32), -64);
    }
    else
    {
        if (D_800D4E6D)
        {
            Sd_SfxStop(Sfx_Unk1611);
            D_800D4E6D = 0;
            D_800C4414 &= ~(1 << 5);
        }

        Savegame_EventFlagClear(EventFlag_407);
        Savegame_EventFlagClear(EventFlag_408);
    }

    func_80069844(0xFFFF);
    func_8006982C(flags);
}

void func_800D1AE4(void) // 0x800D1AE4
{
    s32      temp_s2;
    q19_12   angle;
    VECTOR3* vec;
    SVECTOR* svec;
    MAP_CHUNK_CHECK_VARIABLE_DECL();

    if (PLAYER_IN_MAP_CHUNK(vx, 1, -1, -1, -1) && PLAYER_IN_MAP_CHUNK(vz, 1, -1, -1, -1))
    {
        if (D_800D4E6E == 0)
        {
            Game_TurnFlashlightOn();
            func_800CED74(&g_SysWork.playerWork_4C.player_0, true);

            D_800D4E6E = 1;
        }

        g_SysWork.pointLightIntensity_2378 = Q12(0.7f);

        if (g_SysWork.playerWork_4C.player_0.position_18.vy > Q12(2.84f))
        {
            angle                             = Q12_ANGLE(0.0f);
            g_SysWork.pointLightIntensity_2378 = (((g_SysWork.playerWork_4C.player_0.position_18.vy - Q12(2.84f)) * Q12(0.4f)) / (Q12(1.16f) + 1)) + Q12(0.7f);
        }
        else
        {
            angle = ratan2(g_SysWork.playerWork_4C.player_0.position_18.vx + Q12(20.0f),
                           g_SysWork.playerWork_4C.player_0.position_18.vz + Q12(20.0f));
        }

        func_800CED74(&g_SysWork.playerWork_4C.player_0, false);

        temp_s2 = angle + Q12_ANGLE(70.0f);

        vec = &g_SysWork.pointLightPosition_2360;

        vec->vx = Q12_MULT(Math_Sin(temp_s2), Q12(0.55f)) - Q12(20.0f);
        vec->vy = MIN(g_SysWork.playerWork_4C.player_0.position_18.vy - Q12(1.6f), Q12(0.5f));
        vec->vz = Q12_MULT(Math_Cos(temp_s2), Q12(0.55f)) - Q12(20.0f);

        svec = &g_SysWork.pointLightRot_2370;

        Math_SetSVectorFast(svec, Q12_ANGLE(-40.0f), angle - Q12_ANGLE(150.0f), 0);
    }
    else
    {
        D_800D4E6E = 0;
    }
}

s32 func_800D1D40(void) // 0x800D1D40
{
    q19_12 angle;

    angle = ratan2(g_SysWork.playerWork_4C.player_0.position_18.vx + Q12(20.0f),
                   g_SysWork.playerWork_4C.player_0.position_18.vz + Q12(20.0f));

    if (D_800D4E6C == 0)
    {
        Savegame_EventFlagSet(EventFlag_416);

        if (angle > Q12_ANGLE(0.0f) && angle < Q12_ANGLE(90.0f))
        {
            D_800D4E6C = 1;
        }

        return 258;
    }

    if (D_800D4E6C & (1 << 0))
    {
        if (angle < Q12_ANGLE(-78.8f))
        {
            D_800D4E6C++;
        }
        else
        {
            if ((D_800D4E6C == 1 && angle > Q12_ANGLE(90.0f)) || angle > Q12_ANGLE(78.8f))
            {
                D_800D4E6C--;
            }
        }
    }
    else
    {
        if (angle < Q12_ANGLE(0.0f) && angle > Q12_ANGLE(-78.8f))
        {
            D_800D4E6C--;
        }
        else if (angle > Q12_ANGLE(0.0f) && angle < Q12_ANGLE(78.8f))
        {
            D_800D4E6C++;
        }

        if (D_800D4E6C == 6 && angle < Q12_ANGLE(-157.5f))
        {
            Savegame_EventFlagSet(EventFlag_405);
        }
    }

    Savegame_EventFlagClear(EventFlag_416);
    return (1 << D_800D4E6C) + 0x80;
}

void func_800D1EB8(s32 arg0, s32* arg1, s32* arg2) // 0x800D1EB8
{
    typedef struct
    {
        RECT field_0;
        u8   field_8[128];
        u8   field_88[128];
        u8   field_108[128];
    } s_func_800D1EB8;

    s32              var_a0;
    s32              j;
    s32              i;
    s32              var_t2;
    s32              var_t3;
    s32              var_t6;
    s32*             ptr0;
    s32*             ptr1;
    s_func_800D1EB8* basePtr;

    basePtr = PSX_SCRATCH;

    ptr0 = basePtr->field_8;

    for (i = 31; i >= 0; i--, ptr0++)
    {
        *ptr0 = 0;
    }

    ptr1 = arg1;

    for (i = 0; i < 64; i++, ptr0++, ptr1++)
    {
        *ptr0 = *ptr1;
    }

    var_t6 = 0;

    for (i = 0; i < 256; i++)
    {
        ptr0 = arg2 + (i << 5);

        for (j = 0, var_t3 = 1, var_t2 = -1; j < 256; var_t3++, j++, var_t2++)
        {
            var_a0 = 0;

            if (j > 0)
            {
                var_a0 = (basePtr->field_88[var_t2 >> 1] >> (var_t2 & 0x1) * 4) & 0xF;
            }

            if (j < 255)
            {
                var_a0 += (basePtr->field_88[var_t3 >> 1] >> (var_t3 & 0x1) * 4) & 0xF;
            }

            if (i > 0)
            {
                var_a0 += (basePtr->field_8[j >> 1] >> (j & 0x1) * 4) & 0xF;

                if (j > 0)
                {
                    var_a0 += (basePtr->field_8[var_t2 >> 1] >> (var_t2 & 0x1) * 4) & 0xF;
                }
                if (j < 255)
                {
                    var_a0 += (basePtr->field_8[var_t3 >> 1] >> (var_t3 & 0x1) * 4) & 0xF;
                }
            }

            if (i < 255)
            {
                var_a0 += (basePtr->field_108[j >> 1] >> (j & 0x1) * 4) & 0xF;

                if (j > 0)
                {
                    var_a0 += (basePtr->field_108[var_t2 >> 1] >> (var_t2 & 0x1) * 4) & 0xF;
                }

                if (j < 255)
                {
                    var_a0 += (basePtr->field_108[var_t3 >> 1] >> (var_t3 & 0x1) * 4) & 0xF;
                }
            }

            var_t6 |= ((var_a0 + 7) >> 3) << (j & 0x7) * 4;

            if ((j & 7) == 7)
            {
                *ptr0  = var_t6;
                var_t6 = 0;
                ptr0++;
            }
        }

        ptr0 = basePtr->field_8;

        if (i != 255)
        {
            ptr1 = basePtr->field_88;

            for (j = 0; j < 64; j++, ptr0++, ptr1++)
            {
                *ptr0 = *ptr1;
            }

            if (i == 254)
            {
                for (j = 31; j >= 0; j--, ptr0++)
                {
                    *ptr0 = 0;
                }
            }
            else
            {
                ptr1 = arg1 + ((i + 2) << 5);

                for (j = 0; j < 32; j++, ptr0++, ptr1++)
                {
                    *ptr0 = *ptr1;
                }
            }
        }
    }

    basePtr->field_0.x = (arg0 & 0xF) << 6;
    basePtr->field_0.y = (arg0 * 16) & 0x100;
    basePtr->field_0.w = 64;
    basePtr->field_0.h = 256;

    LoadImage(&basePtr->field_0, arg2);
    DrawSync(0);
}

void func_800D2170(s32 arg0) // 0x800D2170
{
    TIM_IMAGE img;
    s32*      buffers[2];
    s32       temp_a0;
    s32       rng15;
    s32       rng0;
    s32       i;
    s32       j;
    s32       k;
    u32*      rowPtr;
    u_int*    s6 = FS_BUFFER_22;
    u_int*    s3 = FS_BUFFER_23;

    if (!arg0)
    {
        k = 0;

        func_8008D438();
        Fs_QueueStartReadTim(FILE_TIM_LHEFFECT_TIM, FS_BUFFER_1, &D_800CAB90);
        Fs_QueueWaitForEmpty();
        OpenTIM(FS_BUFFER_1);
        ReadTIM(&img);

        buffers[0] = (s32*)img.paddr;
        buffers[1] = buffers[0] + 0x2000;
    }
    else
    {
        memset(s6, 0, 0x2400);
        StoreImage(&D_800CAB98, FS_BUFFER_1);
        DrawSync(0);

        buffers[0] = FS_BUFFER_1;
        buffers[1] = FS_BUFFER_10;
        k = 2;
    }

    for (; k < (ARRAY_SIZE(D_800D3C74) - 1); k++)
    {
        func_800D1EB8(D_800D3C74[k + 1], buffers[k & 1], buffers[(k & 0x1) == 0]);
    }

    for (k = 0, rowPtr = s3; k < 16; k++, rowPtr++)
    {
        for (i = 0, j = 0; i < 16; j++, i++)
        {
            rng0 = Rng_Rand16();
            rng15 = rng0 & 0xF;

            if (rng15 < 8)
            {
                temp_a0 = (rng0 >> 4) & 0x7FFFF;
                (&(&s6[(rng15) << 8])[k])[j * 16] = temp_a0;

                if (rng15 > 0)
                {
                    (&(&s6[(rng15 - 1) << 8])[k])[j * 16] = temp_a0 + 0x80000;
                }
            }

            rowPtr[j * 16] = 0x100000;
        }
    }
}

INCLUDE_ASM("maps/map6_s02/nonmatchings/map6_s02_2", func_800D2364);

void func_800D32D0(void) // 0x800D32D0
{
    g_Screen_FadeStatus = 5;

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            Player_ControlFreeze();
            func_80085EB8(2, &g_SysWork.playerWork_4C.player_0, 0, false);

            g_SysWork.sysStateStep_C[0]++;
            break;

        case 1:
            func_80087EDC(5);
            break;

        case 2:
            g_SavegamePtr->clearGameCount_24A++;
            g_SavegamePtr->clearGameCount_24A                    = CLAMP(g_SavegamePtr->clearGameCount_24A, 1, 99);
            g_SavegamePtr->field_27A                             = 1 << 4;
            g_SavegamePtr->clearGameEndings_24B                 |= 1 << 4;
            g_GameWorkConst->config_0.optExtraOptionsEnabled_27 |= 1 << 4;
            g_SavegamePtr->locationId_A8                         = SaveLocationId_NextFear;

            SysWork_StateSetNext(SysState_StatusMenu);
            break;
    }
}

INCLUDE_RODATA("maps/map6_s02/nonmatchings/map6_s02_2", D_800CAB90);

INCLUDE_RODATA("maps/map6_s02/nonmatchings/map6_s02_2", D_800CAB98);
