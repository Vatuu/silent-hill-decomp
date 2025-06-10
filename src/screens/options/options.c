#include "game.h"

#include "bodyprog/bodyprog.h"
#include "bodyprog/math.h"
#include "screens/options/options.h"
#include "screens/stream/stream.h"

// ========================================
// GENERAL, MAIN, AND EXTRA OPTION SCREENS
// ========================================

s32 g_MainSelectedOptionIdx = 0;

s32 g_ExtraSelectedOptionIdx = 0;

s32 g_PrevMainSelectedOptionIdx = 0;

s32 g_PrevExtraSelectedOptionIdx = 0;

s32 g_Gfx_ScreenPos_InvertColorBg = 0;

s32 g_ScreenCtrl_IsOverActions = 0;

void GameState_OptionScreen_Update() // 0x801E2D44
{
    s32 OptExtra_Unlockables;
    s32 i;

    if (g_GameWork.gameStatePrev_590 == GameState_InGame)
    {
        func_800363D0();
    }

    if (g_GameWork.gameStatePrev_590 != GameState_MainMenu)
    {
        func_8004C8DC();
    }

    switch (g_GameWork.gameStateStep_598[0])
    {
        case 0:
            DrawSync(0);

            if (g_GameWork.gameStatePrev_590 != GameState_InGame)
            {
                VSync(8);
            }

            g_GameWork.background2dColor_R_58C = 0;
            g_GameWork.background2dColor_G_58D = 0;
            g_GameWork.background2dColor_B_58E = 0;

            g_Gfx_ScreenFade  = 7;
            g_IntervalVBlanks = 1;

            if (g_GameWork.gameStatePrev_590 == GameState_InGame)
            {
                func_80037188();
            }

            g_MainSelectedOptionIdx      = 0;
            g_PrevMainSelectedOptionIdx  = 0;
            g_ExtraSelectedOptionIdx     = 0;
            g_PrevExtraSelectedOptionIdx = 0;
            g_Gfx_MoveLineTimer          = 0;
            g_OptExtra_BulletMultLimit   = 1;
            OptExtra_Unlockables         = g_GameWork.config_0.optExtraOptionsEnabled_27;
            
            // Defines the amount of bullet multiplier that will be available.
            for (i = 0; i < 5; i++)
            {
                if (OptExtra_Unlockables & (1 << i))
                {
                    g_OptExtra_BulletMultLimit++;
                }
            }

            switch (g_GameWork.config_0.optExtraBloodColor_24)
            {
                case 0:
                    g_OptExtra_BloodColorSelected = 0;
                    break;

                case 2:
                    g_OptExtra_BloodColorSelected = 1;
                    break;

                case 5:
                    g_OptExtra_BloodColorSelected = 2;
                    break;

                case 11:
                    g_OptExtra_BloodColorSelected = 3;
                    break;
            }

            g_OptExtra_ShowSettingsCount = (g_GameWork.config_0.optExtraOptionsEnabled_27 != 0) ? 8 : 6;
            g_GameWork.gameStateStep_598[0]    = 1;
            g_SysWork.timer_20                 = 0;
            g_GameWork.gameStateStep_598[1]    = 0;
            g_GameWork.gameStateStep_598[2]    = 0;
            break;

        case 10:
        case 11:
        case 12:
            g_GameWork.gameStateStep_598[0] = 1;
            g_SysWork.timer_20              = 0;
            g_GameWork.gameStateStep_598[1] = 0;
            g_GameWork.gameStateStep_598[2] = 0;
            break;

        case 7:
            if ((g_Gfx_ScreenFade & 7) == 5)
            {
                g_GameWork.gameStateStep_598[0] = 2;
                g_SysWork.timer_20              = 0;
                g_GameWork.gameStateStep_598[1] = 0;
                g_GameWork.gameStateStep_598[2] = 0;
            }
            break;

        case 2:
            Settings_PositionScreen();
            break;

        case 8:
            if ((g_Gfx_ScreenFade & 0x7) == 5)
            {
                Fs_QueueWaitForEmpty();

                g_GameWork.gameStateStep_598[0] = 3;
                g_GameWork.gameStateStep_598[0] = 3;
                g_SysWork.timer_20              = 0;
                g_GameWork.gameStateStep_598[1] = 0;
                g_GameWork.gameStateStep_598[2] = 0;
            }
            break;

        case 3:
            Settings_BrightnessScreen();
            break;

        case 9:
            if ((g_Gfx_ScreenFade & 0x7) == 5)
            {
                g_GameWork.gameStateStep_598[0] = 4;
                g_GameWork.gameStateStep_598[0] = 4;
                g_SysWork.timer_20              = 0;
                g_GameWork.gameStateStep_598[1] = 0;
                g_GameWork.gameStateStep_598[2] = 0;
            }
            break;

        case 4:
            Settings_ControllerScreen();
            break;

        case 5:
            g_Gfx_ScreenFade                = 2;
            g_GameWork.gameStateStep_598[0] = 6;
            g_SysWork.timer_20              = 0;
            g_GameWork.gameStateStep_598[1] = 0;
            g_GameWork.gameStateStep_598[2] = 0;
            break;

        case 6:
            if ((g_Gfx_ScreenFade & 0x7) == 0x5)
            {
                // TODO: Likely Game_StateSetPrevious inline, but `gameState_594`/`gameStatePrev_590` loads inside are switched?

                e_GameState prevPrevState = g_GameWork.gameStatePrev_590;
                e_GameState prevState     = g_GameWork.gameState_594;

                g_SysWork.timer_1C              = 0;
                g_SysWork.timer_20              = 0;
                g_GameWork.gameStateStep_598[1] = 0;
                g_GameWork.gameStateStep_598[2] = 0;

                SysWork_StateSetNext(SysState_Gameplay);

                g_GameWork.gameStateStep_598[0] = prevState;
                g_GameWork.gameState_594        = prevPrevState;
                g_GameWork.gameStatePrev_590    = prevState;
                g_GameWork.gameStateStep_598[0] = 0;
            }

            break;

        case 13:
            if ((g_Gfx_ScreenFade & 0x7) == 5)
            {
                g_GameWork.gameStateStep_598[0] = 14;
                g_SysWork.timer_20              = 0;
                g_Gfx_ScreenFade                = 7;
                g_GameWork.gameStateStep_598[1] = 0;
                g_GameWork.gameStateStep_598[2] = 0;
                g_Gfx_MoveLineTimer             = 0;
            }
            break;

        case 15:
            if ((g_Gfx_ScreenFade & 0x7) == 5)
            {
                g_GameWork.gameStateStep_598[0] = 0;
                g_SysWork.timer_20              = 0;
                g_GameWork.gameStateStep_598[1] = 0;
                g_GameWork.gameStateStep_598[2] = 0;
                g_Gfx_ScreenFade                = 7;
            }
            break;
    }

    switch (g_GameWork.gameStateStep_598[0])
    {
        case 1:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        case 13:
            Settings_MainScreen();
            break;

        case 14:
        case 15:
            Settings_ExtraScreen();
            break;
    }
}

void Settings_ExtraScreen() // 0x801E318C
{
    Gfx_OptionsStringsExtraDraw();
    Gfx_SettingsOptionsExtraDraw();
    Gfx_SelectedOptionExtra();
    Gfx_VignetteDraw();
    Gfx_BackgroundSpriteDraw(&D_800A902C);

    if (g_GameWork.gameStateStep_598[0] != 14)
    {
        return;
    }

    if (7 < g_Gfx_MoveLineTimer)
    {
        g_Gfx_MoveLineTimer = 8;
    }
    else
    {
        g_Gfx_MoveLineTimer++;
    }

    if (g_Gfx_MoveLineTimer == 8)
    {
        g_PrevExtraSelectedOptionIdx = g_ExtraSelectedOptionIdx;

        if (((g_GameWork.gameStatePrev_590 == GameState_InGame) && 
			((g_ControllerPtrConst->btns_new_10 & g_GameWorkPtr->config_0.controllerConfig_0.enter_0) == 0)) &&
            ((g_ControllerPtrConst->btns_new_10 & g_GameWorkPtr->config_0.controllerConfig_0.option_1A) != 0))
        {
            func_80046048(0x51A, 0, 64);

            g_GameWork.gameStateStep_598[0] = 5;
            g_SysWork.timer_20              = 0;
            g_GameWork.gameStateStep_598[1] = 0;
            g_GameWork.gameStateStep_598[2] = 0;
            return;
        }

        if (g_ControllerPtrConst->field_18 & ControllerFlag_LStickUp)
        {
            s32 var = 1;
            func_80046048(0x519, 0, 64);
            g_ExtraSelectedOptionIdx = ((g_ExtraSelectedOptionIdx - var) + g_OptExtra_ShowSettingsCount) % g_OptExtra_ShowSettingsCount;
            g_Gfx_MoveLineTimer      = 0;
        }

        if (g_ControllerPtrConst->field_18 & ControllerFlag_LStickDown)
        {
            func_80046048(0x519, 0, 64);
            g_ExtraSelectedOptionIdx++;
            g_ExtraSelectedOptionIdx = g_ExtraSelectedOptionIdx % g_OptExtra_ShowSettingsCount;
            g_Gfx_MoveLineTimer      = 0;
        }

        switch (g_ExtraSelectedOptionIdx)
        {
            case OptExtra_WeaponCtrl:
                if (g_ControllerPtrConst->btns_new_10 & (ControllerFlag_LStickRight | ControllerFlag_LStickLeft))
                {
                    func_80046048(0x519, 0, 64);
                    g_GameWork.config_0.optExtraWeaponCtrl_23 = !g_GameWork.config_0.optExtraWeaponCtrl_23;
                }
                break;

            case OptExtra_Blood:
                if (g_ControllerPtrConst->btns_new_10 & ControllerFlag_LStickRight)
                {
                    func_80046048(0x519, 0, 64);
                    g_OptExtra_BloodColorSelected++;
                }
                if (g_ControllerPtrConst->btns_new_10 & ControllerFlag_LStickLeft)
                {
                    func_80046048(0x519, 0, 64);
                    g_OptExtra_BloodColorSelected += 3;
                }

                g_OptExtra_BloodColorSelected = g_OptExtra_BloodColorSelected % 4;

                switch (g_OptExtra_BloodColorSelected)
                {
                    case 0: // Red
                        g_GameWork.config_0.optExtraBloodColor_24 = 0;
                        break;

                    case 1: // Green
                        g_GameWork.config_0.optExtraBloodColor_24 = 2;
                        break;

                    case 2: // Violet
                        g_GameWork.config_0.optExtraBloodColor_24 = 5;
                        break;

                    case 3: // Black
                        g_GameWork.config_0.optExtraBloodColor_24 = 11;
                        break;
                }
                break;

            case OptExtra_ViewCtrl:
                if (g_ControllerPtrConst->btns_new_10 & (ControllerFlag_LStickRight | ControllerFlag_LStickLeft))
                {
                    func_80046048(0x519, 0, 64);
                    g_GameWork.config_0.optExtraViewCtrl_28 = !g_GameWork.config_0.optExtraViewCtrl_28;
                }
                break;

            case OptExtra_RetreatTurn:
                if (g_ControllerPtrConst->btns_new_10 & (ControllerFlag_LStickRight | ControllerFlag_LStickLeft))
                {
                    func_80046048(0x519, 0, 64);
                    g_GameWork.config_0.optExtraRetreatTurn_2A = (s8)g_GameWork.config_0.optExtraRetreatTurn_2A == 0;
                }
                break;

            case OptExtra_MovementCtrl:
                if (g_ControllerPtrConst->btns_new_10 & (ControllerFlag_LStickRight | ControllerFlag_LStickLeft))
                {
                    func_80046048(0x519, 0, 64);
                    g_GameWork.config_0.optExtraWalkRunCtrl_2B = (s8)g_GameWork.config_0.optExtraWalkRunCtrl_2B == 0;
                }
                break;

            case OptExtra_AutoAiming:
                if (g_ControllerPtrConst->btns_new_10 & (ControllerFlag_LStickRight | ControllerFlag_LStickLeft))
                {
                    func_80046048(0x519, 0, 64);
                    g_GameWork.config_0.optExtraAutoAiming_2C = (s8)g_GameWork.config_0.optExtraAutoAiming_2C == 0;
                }
                break;

            case OptExtra_ViewMode:
                if (g_ControllerPtrConst->btns_new_10 & (ControllerFlag_LStickRight | ControllerFlag_LStickLeft))
                {
                    func_80046048(0x519, 0, 64);
                    g_GameWork.config_0.optExtraViewMode_29 = !g_GameWork.config_0.optExtraViewMode_29;
                }
                break;

            case OptExtra_BulletMult:
                if (g_ControllerPtrConst->btns_new_10 & ControllerFlag_LStickRight)
                {
                    func_80046048(0x519, 0, 64);
                    g_GameWork.config_0.optExtraBulletAdjust_2D++;
                }
                if (g_ControllerPtrConst->btns_new_10 & ControllerFlag_LStickLeft)
                {
                    func_80046048(0x519, 0, 64);
                    g_GameWork.config_0.optExtraBulletAdjust_2D = g_GameWork.config_0.optExtraBulletAdjust_2D + (g_OptExtra_BulletMultLimit - 1);
                }

                g_GameWork.config_0.optExtraBulletAdjust_2D = g_GameWork.config_0.optExtraBulletAdjust_2D % g_OptExtra_BulletMultLimit;
                break;
        }
    }

    if ((g_ControllerPtrConst->btns_new_10 & (g_GameWorkPtr->config_0.controllerConfig_0.cancel_2 | (ControllerFlag_L2 | ControllerFlag_R2 | ControllerFlag_L1 | ControllerFlag_R1))) &&
        g_GameWork.gameStateStep_598[0] != 15)
    {
        if (g_ControllerPtrConst->btns_new_10 & g_GameWorkPtr->config_0.controllerConfig_0.cancel_2)
        {
            func_80046048(0x51A, 0, 64);
        }
        else
        {
            func_80046048(0x51B, 0, 64);
        }

        g_Gfx_ScreenFade                = 2;
        g_GameWork.gameStateStep_598[0] = 15;
        g_SysWork.timer_20              = 0;
        g_GameWork.gameStateStep_598[1] = 0;
        g_GameWork.gameStateStep_598[2] = 0;
    }
}

void Settings_MainScreen() // 0x801E3770
{
    #define IMAGE_BUFFER_3 ((u_long*)0x801EB600)
    #define SOUND_VOL_STEP 8

    s32 sdCmd;
    s32 vol;

    Gfx_OptionsStringsMainDraw();
    Gfx_SettingsOptionsMainDraw();
    Gfx_SelectedOptionMain();
    Gfx_VignetteDraw();
    Gfx_BackgroundSpriteDraw(&D_800A902C);
    Gfx_BgmBarDraw();
    Gfx_SfxBarDraw();

    if (g_GameWork.gameStateStep_598[0] != 1)
    {
        return;
    }

    if (7 < g_Gfx_MoveLineTimer)
    {
        g_Gfx_MoveLineTimer = 8;
    }
    else
    {
        g_Gfx_MoveLineTimer++;
    }

    if (g_Gfx_MoveLineTimer != 8)
    {
        return;
    }

    g_PrevMainSelectedOptionIdx = g_MainSelectedOptionIdx;

    if (((g_GameWork.gameStatePrev_590 == GameState_InGame) && 
		((g_ControllerPtrConst->btns_new_10 & g_GameWorkPtr->config_0.controllerConfig_0.enter_0) == 0)) &&
        (g_ControllerPtrConst->btns_new_10 & g_GameWorkPtr->config_0.controllerConfig_0.option_1A))
    {
        func_80046048(0x51A, 0, 64);

        g_GameWork.gameStateStep_598[0] = 5;
        g_SysWork.timer_20              = 0;
        g_GameWork.gameStateStep_598[1] = 0;
        g_GameWork.gameStateStep_598[2] = 0;
        return;
    }

    if (g_ControllerPtrConst->field_18 & ControllerFlag_LStickUp)
    {
        func_80046048(0x519, 0, 64);

        g_Gfx_MoveLineTimer     = 0;
        g_MainSelectedOptionIdx = (g_MainSelectedOptionIdx + 8) % 9;
    }
    if (g_ControllerPtrConst->field_18 & ControllerFlag_LStickDown)
    {
        func_80046048(0x519, 0, 64);

        g_Gfx_MoveLineTimer     = 0;
        g_MainSelectedOptionIdx = (g_MainSelectedOptionIdx + 1) % 9;
    }

    switch (g_MainSelectedOptionIdx)
    {
        case OptMain_Exit:
            if (g_ControllerPtrConst->btns_new_10 & (g_GameWorkPtr->config_0.controllerConfig_0.enter_0 |
				g_GameWorkPtr->config_0.controllerConfig_0.cancel_2))
            {
                func_80046048(0x51A, 0, 64);

                g_GameWork.gameStateStep_598[0] = 5;
                g_SysWork.timer_20              = 0;
                g_GameWork.gameStateStep_598[1] = 0;
                g_GameWork.gameStateStep_598[2] = 0;
            }
            break;

        case OptMain_Controller:
            if (g_ControllerPtrConst->btns_new_10 & g_GameWorkPtr->config_0.controllerConfig_0.enter_0)
            {
                func_80046048(0x51B, 0, 64);
                Fs_QueueStartReadTim(FILE_TIM_OPTION2_TIM, IMAGE_BUFFER_3, &D_800A903C);

                g_Gfx_ScreenFade                = 2;
                g_GameWork.gameStateStep_598[0] = 9;
                g_SysWork.timer_20              = 0;
                g_GameWork.gameStateStep_598[1] = 0;
                g_GameWork.gameStateStep_598[2] = 0;
            }
            break;

        case OptMain_ScreenPos:
            if (g_ControllerPtrConst->btns_new_10 & g_GameWorkPtr->config_0.controllerConfig_0.enter_0)
            {
                func_80046048(0x51B, 0, 64);

                g_Gfx_ScreenFade                = 2;
                g_GameWork.gameStateStep_598[0] = 7;
                g_SysWork.timer_20              = 0;
                g_GameWork.gameStateStep_598[1] = 0;
                g_GameWork.gameStateStep_598[2] = 0;
            }
            break;

        case OptMain_Brightness:
            if (g_ControllerPtrConst->btns_new_10 & g_GameWorkPtr->config_0.controllerConfig_0.enter_0)
            {
                func_80046048(0x51B, 0, 64);
                if (g_GameWork.gameStatePrev_590 == GameState_MainMenu)
                {
                    Fs_QueueStartReadTim(FILE_TIM_OP_BRT_E_TIM, IMAGE_BUFFER_3, &D_800A9044);
                }
                else
                {
                    Fs_QueueStartReadTim(FILE_TIM_OP_BRT_E_TIM, IMAGE_BUFFER_3, &D_800A904C);
                }

                g_Gfx_ScreenFade                = 2;
                g_GameWork.gameStateStep_598[0] = 8;
                g_SysWork.timer_20              = 0;
                g_GameWork.gameStateStep_598[1] = 0;
                g_GameWork.gameStateStep_598[2] = 0;
            }
            break;

        case OptMain_Vibration:
            if (g_ControllerPtrConst->btns_new_10 & (ControllerFlag_LStickRight | ControllerFlag_LStickLeft))
            {
                func_80046048(0x519, 0, 64);
                g_GameWork.config_0.optVibrationEnabled_21 = !g_GameWork.config_0.optVibrationEnabled_21 << 7;
            }
            break;

        case OptMain_AutoLoad:
            if (g_ControllerPtrConst->btns_new_10 & (ControllerFlag_LStickRight | ControllerFlag_LStickLeft))
            {
                func_80046048(0x519, 0, 64);
                g_GameWork.config_0.optAutoLoad_25 = (s8)g_GameWork.config_0.optAutoLoad_25 == 0;
            }
            break;

        case OptMain_Sound:
            if (g_ControllerPtrConst->btns_new_10 & (ControllerFlag_LStickRight | ControllerFlag_LStickLeft))
            {
                func_80046048(0x519, 0, 64);

                sdCmd                               = 2;
                g_GameWork.config_0.optSoundType_1E = !g_GameWork.config_0.optSoundType_1E;
                if (g_GameWork.config_0.optSoundType_1E)
                {
                    sdCmd = 1;
                }
                Sd_EngineCmd(sdCmd);
            }
            break;

        case OptMain_BGMVol:
            vol = g_GameWork.config_0.optVolumeBgm_1F;
            if ((vol < OPT_SOUND_VOLUME_MAX && (g_ControllerPtrConst->field_18 & ControllerFlag_LStickRight)) ||
                (vol > 0 && (g_ControllerPtrConst->field_18 & ControllerFlag_LStickLeft)))
            {
                Sd_EngineCmd(0x519);
            }
            if ((vol == OPT_SOUND_VOLUME_MAX && (g_ControllerPtrConst->btns_new_10 & ControllerFlag_LStickRight)) ||
                (vol == 0 && (g_ControllerPtrConst->btns_new_10 & ControllerFlag_LStickLeft)))
            {
                Sd_EngineCmd(0x518);
            }
            if (g_ControllerPtrConst->field_18 & ControllerFlag_LStickRight)
            {
                vol = vol + SOUND_VOL_STEP;
            }
            if (g_ControllerPtrConst->field_18 & ControllerFlag_LStickLeft)
            {
                vol = vol - SOUND_VOL_STEP;
            }

            vol = CLAMP(vol, 0, OPT_SOUND_VOLUME_MAX);

            Sd_SetVolume(OPT_SOUND_VOLUME_MAX, vol, g_GameWork.config_0.optVolumeSe_20);
            g_GameWork.config_0.optVolumeBgm_1F = vol;
            break;

        case OptMain_SFXVol:
            vol = g_GameWork.config_0.optVolumeSe_20;
            if ((vol < OPT_SOUND_VOLUME_MAX && (g_ControllerPtrConst->field_18 & ControllerFlag_LStickRight)) ||
                (vol > 0 && (g_ControllerPtrConst->field_18 & ControllerFlag_LStickLeft)))
            {
                Sd_EngineCmd(0x519);
            }
            if ((vol == OPT_SOUND_VOLUME_MAX && (g_ControllerPtrConst->btns_new_10 & ControllerFlag_LStickRight)) ||
                (vol == 0 && (g_ControllerPtrConst->btns_new_10 & ControllerFlag_LStickLeft)))
            {
                Sd_EngineCmd(0x518);
            }
            if (g_ControllerPtrConst->field_18 & ControllerFlag_LStickRight)
            {
                vol = vol + SOUND_VOL_STEP;
            }
            if (g_ControllerPtrConst->field_18 & ControllerFlag_LStickLeft)
            {
                vol = vol - SOUND_VOL_STEP;
            }

            vol = CLAMP(vol, 0, OPT_SOUND_VOLUME_MAX);

            Sd_SetVolume(OPT_SOUND_VOLUME_MAX, vol, g_GameWork.config_0.optVolumeSe_20);
            g_GameWork.config_0.optVolumeSe_20 = vol;
            break;

        default:
            break;
    }

    vol = 0;

    if (g_ControllerPtrConst->btns_new_10 & (ControllerFlag_L2 | ControllerFlag_R2 | ControllerFlag_L1 | ControllerFlag_R1))
    {
        if (g_GameWork.gameStateStep_598[0] == 13)
        {
            return;
        }

        func_80046048(0x51B, 0, 64);
        g_Gfx_ScreenFade                = 2;
        g_GameWork.gameStateStep_598[0] = 13;
        g_SysWork.timer_20              = 0;
        g_GameWork.gameStateStep_598[1] = 0;
        g_GameWork.gameStateStep_598[2] = 0;
    }

    if (((g_GameWork.gameStateStep_598[0] != 13 && g_MainSelectedOptionIdx != 0) &&
         ((g_ControllerPtrConst->btns_new_10 & g_GameWorkPtr->config_0.controllerConfig_0.enter_0) == 0)) &&
        (g_ControllerPtrConst->btns_new_10 & g_GameWorkPtr->config_0.controllerConfig_0.cancel_2))
    {
        func_80046048(0x51A, 0, 64);
        g_Gfx_MoveLineTimer     = 0;
        g_MainSelectedOptionIdx = 0;
    }
}

void Gfx_BgmBarDraw() // 0x801E3F68
{
    Gfx_BarDraw(0, g_GameWork.config_0.optVolumeBgm_1F);
}

void Gfx_SfxBarDraw() // 0x801E3F90
{
    Gfx_BarDraw(1, g_GameWork.config_0.optVolumeSe_20);
}

void Gfx_BarDraw(s32 arg0, u8 arg1) // 0x801E3FB8
{
    GsOT* ot;
    s32   x0Offset;
    s32   x0;
    s32   offset;
    s32   yOffset;
    s32   value;
    s32   i;
    s32   j;
    u32   colorComp;
    s32   xOffset;
    s32   color0, color1, color2;

    POLY_F4* poly;

    ot    = &g_ObjectTable1[g_ObjectTableIdx];
    value = arg1;

    for (i = 0; i < 16; i++)
    {
        colorComp = value & 7;
        colorComp = (colorComp * 12) + 64;

        for (j = 1; j >= 0; j--)
        {
            poly = (POLY_F4*)GsOUT_PACKET_P;
            setPolyF4(poly);

            if (i < (arg1 / 8))
            {
                color0 = 0xA0 + (0x40 * j);
                setRGBC0(poly, color0, color0, color0, 0x28);
            }
            else if (i > (arg1 / 8))
            {
                color1 = 0x40 + (0x40 * j);
                setRGBC0(poly, color1, color1, color1, 0x28);
            }
            else
            {
                color2 = colorComp + (0x40 * j);
                setRGBC0(poly, color2, color2, color2, 0x28);
            }

            xOffset = 24 + i * 6;
            offset  = -69;

            x0Offset = (j + 24);
            x0       = (x0Offset + (i * 6)) & 0xFFFF;
            yOffset  = (j + 56);

            setXY0Fast(poly, x0, (arg0 * 16) + yOffset);
            setXY1Fast(poly, x0, (arg0 * 16) - (j + offset));
            setXY2Fast(poly, (xOffset - j) + 5, (arg0 * 16) + yOffset);
            setXY3Fast(poly, (xOffset - j) + 5, (arg0 * 16) - (j + offset));

            addPrim((u8*)ot->org + 0x18, poly);

            GsOUT_PACKET_P = (u8*)poly + sizeof(POLY_F4);
        }
    }
}

void Gfx_OptionsStringsExtraDraw() // 0x801E416C
{
    s32 i;

    DVECTOR textPos =
    {
        .vx = 0x56,
        .vy = 0x14,
    };

    char* EXTRA_OPTION_str = "EXTRA_OPTION_\x01\x01\x01\x01\x01S";

    char* SettingsExtra_str[] =
    {
        "Weapon_Control",
        "Blood_Color",
        "View_Control",
        "Retreat_Turn",
        "\x01W"
        "\x01"
        "a\x01l\x01k/R\x01\x01u\x01n_\x01\x01\x01\x01"
        "Co\x01n\x01t\x01ro\x01l",
        "Auto_Aiming",
        "View_Mode",
        "Bullet_Adjust"
    };

    if (g_Gfx_MoveLineTimer == 0)
    {
        D_801E73B4.vx = 48;
        D_801E73B8.vx = 64;
        D_801E73B4.vy = ((u16)g_PrevMainSelectedOptionIdx * 16) + 64;
        D_801E73B8.vy = ((u16)g_MainSelectedOptionIdx * 16) + 64;
    }

    shRsin(g_Gfx_MoveLineTimer << 7);
    Gfx_StringSetColor(ColorId_White);
    Gfx_StringSetPosition(textPos.vx, textPos.vy);
    func_8004A8C0(8);
    Gfx_StringDraw(EXTRA_OPTION_str, 0x63);

    for (i = 0; i < g_OptExtra_ShowSettingsCount; i++)
    {
        Gfx_StringSetPosition(64, 64 + (i * 16));
        func_8004A8C0(8);
        Gfx_StringDraw(SettingsExtra_str[i], 99);
    }
}

void Gfx_OptionsStringsMainDraw() // 0x801E42EC
{
    s32 i;

    DVECTOR textPos =
    {
        .vx = 0x79,
        .vy = 0x14,
    };

    char* OPTION_str = "OPTION_\x01\x01\x01\x01\x01S";

    char* Settings_str[] =
    {
        "Exit",
        "Brightness_Level",
        "Controller_Config",
        "Screen_Position",
        "Vibration",
        "Auto_Load",
        "Sound",
        "BGM_Volume",
        "SE_Volume"
    };

    if (g_Gfx_MoveLineTimer == 0)
    {
        D_801E73BC.vx = 48;
        D_801E73C0.vx = 64;
        D_801E73BC.vy = ((u16)g_PrevMainSelectedOptionIdx * 16) + 56;
        D_801E73C0.vy = ((u16)g_MainSelectedOptionIdx * 16) + 56;
    }

    shRsin(g_Gfx_MoveLineTimer << 7);
    Gfx_StringSetColor(ColorId_White);
    Gfx_StringSetPosition(textPos.vx, textPos.vy);
    func_8004A8C0(8);
    Gfx_StringDraw(OPTION_str, 99);

    for (i = 0; i < 9; i++)
    {
        Gfx_StringSetPosition(64, 56 + (i * 16));
        func_8004A8C0(8);
        Gfx_StringDraw(Settings_str[i], 99);
    }

    func_8004A8CC();
}

void Gfx_SelectedOptionExtra() // 0x801E4450
{
    DVECTOR* vecPtrOut;
    s16      sin;
    s32      j;
    s32      i;
    s_Line2d line;
    s_Quad2d quads[2];

    u8 D_801E2830[] =
    {
        0x9D, 0x7E, 0x87, 0x87, 0x9D, 0x82, 0x70, 0x86
    };

    DVECTOR D_801E2838[] =
    {
        {
            .vx = 0xFF88,
            .vy = 0xFFD1
        },
        {
            .vx = 0xFF88,
            .vy = 0xFFDD
        },
        {
            .vx = 0xFF94,
            .vy = 0xFFD1
        },
        {
            .vx = 0xFF94,
            .vy = 0xFFDD
        }
    };

    DVECTOR D_801E2848[] =
    {
        {
            .vx = 0xFF87,
            .vy = 0xFFD0
        },
        {
            .vx = 0xFF87,
            .vy = 0xFFDE
        },
        {
            .vx = 0xFF95,
            .vy = 0xFFD0
        },
        {
            .vx = 0xFF95,
            .vy = 0xFFDE
        }
    };

    if (g_Gfx_MoveLineTimer == 0)
    {
        D_801E73C4.vx = D_801E2830[g_PrevExtraSelectedOptionIdx] + 0xFF87;
        D_801E73C4.vy = ((u16)g_PrevExtraSelectedOptionIdx * 16) - 50;

        D_801E73C8.vx = D_801E2830[g_ExtraSelectedOptionIdx] + 0xFF87;
        D_801E73C8.vy = ((u16)g_ExtraSelectedOptionIdx * 16) - 50;
    }

    sin = shRsin(g_Gfx_MoveLineTimer << 7);

    line.vertex0_0.vx = -121;
    line.vertex1_4.vx = D_801E73C4.vx + FP_FROM((D_801E73C8.vx - D_801E73C4.vx) * sin, Q12_SHIFT);
    line.vertex1_4.vy = D_801E73C4.vy + FP_FROM((D_801E73C8.vy - D_801E73C4.vy) * sin, Q12_SHIFT) + 16;
    line.vertex0_0.vy = line.vertex1_4.vy;

    Gfx_LineDraw(&line, 1, 0);

    for (i = 0; i < g_OptExtra_ShowSettingsCount; i++)
    {
        vecPtrOut = (DVECTOR*)&quads;

        for (j = 0; j < 4; j++)
        {
            vecPtrOut[j].vx     = D_801E2838[j].vx;
            vecPtrOut[j].vy     = D_801E2838[j].vy + (i * 16);
            vecPtrOut[j + 4].vx = D_801E2848[j].vx;
            vecPtrOut[j + 4].vy = D_801E2848[j].vy + (i * 16);
        }

        if (i == g_ExtraSelectedOptionIdx)
        {
            Gfx_ButtonDraw(&quads[0], 0, 0);
            Gfx_ButtonDraw(&quads[1], 1, 0);
        }
        else
        {
            Gfx_ButtonDraw(&quads[0], 0, 1);
            Gfx_ButtonDraw(&quads[1], 1, 1);
        }
    }
}

void Gfx_SelectedOptionMain() // 0x801E472C
{
    DVECTOR* vecPtrOut;
    s16      sin;
    s32      j;
    s32      i;
    s_Line2d line;
    s_Quad2d quads[2];

    u8 D_801E2858[] =
    {
        0x3B, 0xA9, 0xAE, 0x9C, 0x68, 0x70, 0x4B, 0x81, 0x70
    };

    DVECTOR D_801E2864[] =
    {
        {
            .vx = 0xFF88,
            .vy = 0xFFC9
        },
        {
            .vx = 0xFF88,
            .vy = 0xFFD5
        },
        {
            .vx = 0xFF94,
            .vy = 0xFFC9
        },
        {
            .vx = 0xFF94,
            .vy = 0xFFD5
        },
    };

    DVECTOR D_801E2874[] =
    {
        {
            .vx = 0xFF87,
            .vy = 0xFFC8
        },
        {
            .vx = 0xFF87,
            .vy = 0xFFD6
        },
        {
            .vx = 0xFF95,
            .vy = 0xFFC8
        },
        {
            .vx = 0xFF95,
            .vy = 0xFFD6
        },
    };

    if (g_Gfx_MoveLineTimer == 0)
    {
        D_801E73CC.vx = D_801E2858[g_PrevMainSelectedOptionIdx] + 0xFF87;
        D_801E73CC.vy = ((u16)g_PrevMainSelectedOptionIdx * 16) - 58;

        D_801E73D0.vx = D_801E2858[g_MainSelectedOptionIdx] + 0xFF87;
        D_801E73D0.vy = ((u16)g_MainSelectedOptionIdx * 16) - 58;
    }

    sin = shRsin(g_Gfx_MoveLineTimer << 7);

    line.vertex0_0.vx = -121;
    line.vertex1_4.vx = D_801E73CC.vx + FP_FROM((D_801E73D0.vx - D_801E73CC.vx) * sin, Q12_SHIFT);
    line.vertex1_4.vy = D_801E73CC.vy + FP_FROM((D_801E73D0.vy - D_801E73CC.vy) * sin, Q12_SHIFT) + 16;
    line.vertex0_0.vy = line.vertex1_4.vy;

    Gfx_LineDraw(&line, 1, 0);

    for (i = 0; i < 9; i++)
    {
        vecPtrOut = (DVECTOR*)&quads;

        for (j = 0; j < 4; j++)
        {
            vecPtrOut[j].vx     = D_801E2864[j].vx;
            vecPtrOut[j].vy     = D_801E2864[j].vy + (i * 16);
            vecPtrOut[j + 4].vx = D_801E2874[j].vx;
            vecPtrOut[j + 4].vy = D_801E2874[j].vy + (i * 16);
        }

        if (i == g_MainSelectedOptionIdx)
        {
            Gfx_ButtonDraw(&quads[0], 0, 0);
            Gfx_ButtonDraw(&quads[1], 1, 0);
        }
        else
        {
            Gfx_ButtonDraw(&quads[0], 0, 1);
            Gfx_ButtonDraw(&quads[1], 1, 1);
        }
    }
}

void Gfx_VignetteDraw() // 0x801E49F0
{
    GsOT*    ot = &g_ObjectTable0[g_ObjectTableIdx];
    s32      y0;
    s32      y1;
    s32      xy2;
    s32      xy3;
    s32      i;
    POLY_G4* poly;

    xy3 = 0x00A0 + (0xFFA0 << 16);
    xy2 = 0x00A0 + (0xFF90 << 16);
    y1  = 0xFFA0 << 16;
    y0  = 0xFF90 << 16;

    for (i = 0; i < 2; i++)
    {
        poly = (POLY_G4*)GsOUT_PACKET_P;

        setPolyG4(poly);
        setSemiTrans(poly, 1);

        setRGB0(poly, 0x60, 0x60, 0x60);
        setRGB1(poly, 0, 0, 0);
        setRGB2(poly, 0x60, 0x60, 0x60);
        setRGB3(poly, 0, 0, 0);

        *(u32*)(&poly->x0) = 0xFF60 + (y0 + (0xE0 * i << 16));
        *(u32*)(&poly->x1) = 0xFF60 + (y1 + (0xA8 * i << 16));
        *(u32*)(&poly->x2) = xy2 + (0xE0 * i << 16);
        *(u32*)(&poly->x3) = xy3 + (0xA8 * i << 16);

        addPrim((u8*)ot->org + 0x1FD4, poly);
        GsOUT_PACKET_P = (u8*)poly + sizeof(POLY_G4);
    }

    func_80052088(0, 0, 0x7F5, 6);
}

void Gfx_SettingsOptionsExtraDraw() // 0x801E4B2C
{
    s32 strPosX;
    s32 i;
    s32 j;

    s_Triangle2d flashArrows[] =
    {
        { { 0x0026, 0xFFD6 }, { 0x002E, 0xFFCE }, { 0x002E, 0xFFDE } },
        { { 0x0078, 0xFFD6 }, { 0x0070, 0xFFCE }, { 0x0070, 0xFFDE } },
        { { 0x0026, 0xFFE6 }, { 0x002E, 0xFFDE }, { 0x002E, 0xFFEE } },
        { { 0x0078, 0xFFE6 }, { 0x0070, 0xFFDE }, { 0x0070, 0xFFEE } },
        { { 0x0023, 0xFFF6 }, { 0x002B, 0xFFEE }, { 0x002B, 0xFFFE } },
        { { 0x007B, 0xFFF6 }, { 0x0073, 0xFFEE }, { 0x0073, 0xFFFE } },
        { { 0x0023, 0x0006 }, { 0x002B, 0xFFFE }, { 0x002B, 0x000E } },
        { { 0x007B, 0x0006 }, { 0x0073, 0xFFFE }, { 0x0073, 0x000E } },
        { { 0x0023, 0x0016 }, { 0x002B, 0x000E }, { 0x002B, 0x001E } },
        { { 0x007B, 0x0016 }, { 0x0073, 0x000E }, { 0x0073, 0x001E } },
        { { 0x0033, 0x0026 }, { 0x003B, 0x001E }, { 0x003B, 0x002E } },
        { { 0x006B, 0x0026 }, { 0x0063, 0x001E }, { 0x0063, 0x002E } },
        { { 0x0018, 0x0036 }, { 0x0020, 0x002E }, { 0x0020, 0x003E } },
        { { 0x0083, 0x0036 }, { 0x007B, 0x002E }, { 0x007B, 0x003E } },
        { { 0x0039, 0x0046 }, { 0x0041, 0x003E }, { 0x0041, 0x004E } },
        { { 0x0068, 0x0046 }, { 0x0060, 0x003E }, { 0x0060, 0x004E } }
    };

    s_Triangle2d borderArrows[] =
    {
        { { 0x0025, 0xFFD6 }, { 0x002F, 0xFFCC }, { 0x002F, 0xFFE0 } },
        { { 0x0079, 0xFFD6 }, { 0x006F, 0xFFCC }, { 0x006F, 0xFFE0 } },
        { { 0x0025, 0xFFE6 }, { 0x002F, 0xFFDC }, { 0x002F, 0xFFF0 } },
        { { 0x0079, 0xFFE6 }, { 0x006F, 0xFFDC }, { 0x006F, 0xFFF0 } },
        { { 0x0022, 0xFFF6 }, { 0x002C, 0xFFEC }, { 0x002C, 0x0000 } },
        { { 0x007C, 0xFFF6 }, { 0x0072, 0xFFEC }, { 0x0072, 0x0000 } },
        { { 0x0022, 0x0006 }, { 0x002C, 0xFFFC }, { 0x002C, 0x0010 } },
        { { 0x007C, 0x0006 }, { 0x0072, 0xFFFC }, { 0x0072, 0x0010 } },
        { { 0x0022, 0x0016 }, { 0x002C, 0x000C }, { 0x002C, 0x0020 } },
        { { 0x007C, 0x0016 }, { 0x0072, 0x000C }, { 0x0072, 0x0020 } },
        { { 0x0032, 0x0026 }, { 0x003C, 0x001C }, { 0x003C, 0x0030 } },
        { { 0x006C, 0x0026 }, { 0x0062, 0x001C }, { 0x0062, 0x0030 } },
        { { 0x0017, 0x0036 }, { 0x0021, 0x002C }, { 0x0021, 0x0040 } },
        { { 0x0084, 0x0036 }, { 0x007A, 0x002C }, { 0x007A, 0x0040 } },
        { { 0x0038, 0x0046 }, { 0x0042, 0x003C }, { 0x0042, 0x0050 } },
        { { 0x0069, 0x0046 }, { 0x005F, 0x003C }, { 0x005F, 0x0050 } }
    };

    char* SettingsExtraOptions_str[] =
    {
        "Press",
        "Switch",
        "Normal",
        "Green",
        "Violet",
        "Black",
        "_",
        "Normal",
        "Reverse",
        "On",
        "Off",
        "Normal",
        "Self_View",
        "x1",
        "x2",
        "x3",
        "x4",
        "x5",
        "x6"
    };

    Gfx_StringSetColor(ColorId_White);

    // Draw left/right arrows for subset of options.
    if (g_ExtraSelectedOptionIdx < 8u)
    {
        // Draw flashing left/right arrows.
        for (i = 0; i < 2; i++)
        {
            Gfx_Options_BlueArrowDraw(&flashArrows[(g_ExtraSelectedOptionIdx * 2) + i], 1, 0);
        }

        // Draw border to highlight flashing left/right arrow corresponding to direction of UI movement.
        if (g_ControllerPtrConst->btns_held_C & ControllerFlag_LStickLeft)
        {
            Gfx_Options_BlueArrowDraw(&borderArrows[g_ExtraSelectedOptionIdx << 1], 0, 0);
        }
        if (g_ControllerPtrConst->btns_held_C & ControllerFlag_LStickRight)
        {
            Gfx_Options_BlueArrowDraw(&borderArrows[(g_ExtraSelectedOptionIdx << 1) + 1], 0, 0);
        }
    }

    for (j = 0; j < g_OptExtra_ShowSettingsCount; j++)
    {
        switch (j)
        {
            case 0:
                strPosX = (g_GameWork.config_0.optExtraWeaponCtrl_23 != 0) ? 217 : 212;
                Gfx_StringSetPosition(strPosX, 64);
                Gfx_StringDraw(SettingsExtraOptions_str[!g_GameWork.config_0.optExtraWeaponCtrl_23], 10);
                break;

            case 1:
                switch (g_OptExtra_BloodColorSelected)
                {
                    case 0:
                        Gfx_StringSetPosition(210, 80);
                        break;

                    case 1:
                        Gfx_StringSetPosition(214, 80);
                        break;

                    case 2:
                        Gfx_StringSetPosition(214, 80);
                        break;

                    case 3:
                        Gfx_StringSetPosition(217, 80);
                        break;
                }

                Gfx_StringDraw(SettingsExtraOptions_str[g_OptExtra_BloodColorSelected + 2], 10);
                break;

            case 2:
                strPosX = (g_GameWork.config_0.optExtraViewCtrl_28 == 0) ? 210 : 206;
                Gfx_StringSetPosition(strPosX, 96);
                Gfx_StringDraw(SettingsExtraOptions_str[((g_GameWork.config_0.optExtraViewCtrl_28 != 0) ? 32 : 28) >> 2], 10);
                break;

            case 3:
                strPosX = (g_GameWork.config_0.optExtraRetreatTurn_2A == 0) ? 210 : 206;
                Gfx_StringSetPosition(strPosX, 112);
                Gfx_StringDraw(SettingsExtraOptions_str[((g_GameWork.config_0.optExtraRetreatTurn_2A != 0) ? 32 : 28) >> 2], 10);
                break;

            case 4:
                strPosX = (g_GameWork.config_0.optExtraWalkRunCtrl_2B == 0) ? 210 : 206;
                Gfx_StringSetPosition(strPosX, 128);
                Gfx_StringDraw(SettingsExtraOptions_str[((g_GameWork.config_0.optExtraWalkRunCtrl_2B != 0) ? 32 : 28) >> 2], 10);
                break;

            case 5:
                strPosX = (g_GameWork.config_0.optExtraAutoAiming_2C == 0) ? 228 : 226;
                Gfx_StringSetPosition(strPosX, 144);
                Gfx_StringDraw(SettingsExtraOptions_str[((g_GameWork.config_0.optExtraAutoAiming_2C != 0) ? 40 : 36) >> 2], 10);
                break;

            case 6:
                strPosX = (g_GameWork.config_0.optExtraViewMode_29 == 0) ? 210 : 200;
                Gfx_StringSetPosition(strPosX, 160);
                Gfx_StringDraw(SettingsExtraOptions_str[(g_GameWork.config_0.optExtraViewMode_29 ? 48 : 44) >> 2], 10);
                break;

            case 7:
                Gfx_StringSetPosition(230, 176);
                Gfx_StringDraw(SettingsExtraOptions_str[g_GameWork.config_0.optExtraBulletAdjust_2D + 13], 10);
                break;
        }
    }
}

void Gfx_SettingsOptionsMainDraw() // 0x801E4FFC
{
    s32 strPosX;
    s32 strIdx;
    s32 i;

    s_Triangle2d flashArrows[] =
    {
        { { 0x0028, 0x000E }, { 0x0030, 0x0006 }, { 0x0030, 0x0016 } },
        { { 0x0060, 0x000E }, { 0x0058, 0x0006 }, { 0x0058, 0x0016 } },
        { { 0x0028, 0x001E }, { 0x0030, 0x0016 }, { 0x0030, 0x0026 } },
        { { 0x0060, 0x001E }, { 0x0058, 0x0016 }, { 0x0058, 0x0026 } },
        { { 0x0013, 0x002E }, { 0x001B, 0x0026 }, { 0x001B, 0x0036 } },
        { { 0x007C, 0x002E }, { 0x0074, 0x0026 }, { 0x0074, 0x0036 } },
        { { 0x000C, 0x003E }, { 0x0014, 0x0036 }, { 0x0014, 0x0046 } },
        { { 0x0083, 0x003E }, { 0x007B, 0x0036 }, { 0x007B, 0x0046 } },
        { { 0x000C, 0x004E }, { 0x0014, 0x0046 }, { 0x0014, 0x0056 } },
        { { 0x0083, 0x004E }, { 0x007B, 0x0046 }, { 0x007B, 0x0056 } }
    };

    s_Triangle2d borderArrows[] =
    {
        { { 0x0027, 0x000E }, { 0x0031, 0x0004 }, { 0x0031, 0x0018 } },
        { { 0x0061, 0x000E }, { 0x0057, 0x0004 }, { 0x0057, 0x0018 } },
        { { 0x0027, 0x001E }, { 0x0031, 0x0014 }, { 0x0031, 0x0028 } },
        { { 0x0061, 0x001E }, { 0x0057, 0x0014 }, { 0x0057, 0x0028 } },
        { { 0x0012, 0x002E }, { 0x001C, 0x0024 }, { 0x001C, 0x0038 } },
        { { 0x007D, 0x002E }, { 0x0073, 0x0024 }, { 0x0073, 0x0038 } },
        { { 0x000B, 0x003E }, { 0x0015, 0x0034 }, { 0x0015, 0x0048 } },
        { { 0x0084, 0x003E }, { 0x007A, 0x0034 }, { 0x007A, 0x0048 } },
        { { 0x000B, 0x004E }, { 0x0015, 0x0044 }, { 0x0015, 0x0058 } },
        { { 0x0084, 0x004E }, { 0x007A, 0x0044 }, { 0x007A, 0x0058 } }
    };

    char* D_801E2BDC[] =
    {
        "On",
        "Off",
        "Stereo",
        "Monaural"
    };

    Gfx_StringSetColor(ColorId_White);

    // Draw left/right arrows for subset of options.
    if (g_MainSelectedOptionIdx >= 4 && g_MainSelectedOptionIdx < 9)
    {
        // Draw flashing left/right arrows.
        for (i = 0; i < 2; i++)
        {
            Gfx_Options_BlueArrowDraw(&flashArrows[(((g_MainSelectedOptionIdx - 4) * 2) + i)], 1, 0);
        }

        // Draw border to highlight flashing left/right arrow corresponding to direction of UI movement.
        if (g_ControllerPtrConst->btns_held_C & ControllerFlag_LStickLeft)
        {
            Gfx_Options_BlueArrowDraw(&borderArrows[(g_MainSelectedOptionIdx - 4) << 1], 0, 0);
        }
        if (g_ControllerPtrConst->btns_held_C & ControllerFlag_LStickRight)
        {
            Gfx_Options_BlueArrowDraw(&borderArrows[((g_MainSelectedOptionIdx - 4) << 1) + 1], 0, 0);
        }
    }

    for (i = 0; i < 3; i++)
    {
        switch (i)
        {
            case 0:
                strPosX = (g_GameWork.config_0.optVibrationEnabled_21 == 0) ? 214 : 216;
                Gfx_StringSetPosition(strPosX, 120);
                strIdx = g_GameWork.config_0.optVibrationEnabled_21 == 0;
                Gfx_StringDraw(D_801E2BDC[strIdx], 10);
                break;

            case 1:
                strPosX = (g_GameWork.config_0.optAutoLoad_25 == 0) ? 214 : 216;
                Gfx_StringSetPosition(strPosX, 136);
                strIdx = g_GameWork.config_0.optAutoLoad_25 == 0;
                Gfx_StringDraw(D_801E2BDC[strIdx], 10);
                break;

            case 2:
                strPosX = (g_GameWork.config_0.optSoundType_1E != 0) ? 194 : 206;
                Gfx_StringSetPosition(strPosX, 152);
                strIdx = g_GameWork.config_0.optSoundType_1E + 2;
                Gfx_StringDraw(D_801E2BDC[strIdx], 10);
                break;
        }
    }
}

// ==============================
// SCREEN POSITION OPTION SCREEN
// ==============================

void Settings_PositionScreen() // 0x801E53A0
{
    s32     i;
    s8      posX;
    TILE*   tile;
    PACKET* packet;

    posX = g_GameWorkConst->config_0.optScreenPosX_1C;
    if ((posX != g_ScreenPos_PosX) || (g_GameWorkConst->config_0.optScreenPosY_1D != g_ScreenPos_PosY))
    {
        Settings_ScreenXYSet(posX, g_GameWorkConst->config_0.optScreenPosY_1D);
    }

    g_ScreenPos_PosX = g_GameWorkConst->config_0.optScreenPosX_1C;
    g_ScreenPos_PosY = g_GameWorkConst->config_0.optScreenPosY_1D;

    switch (g_GameWork.gameStateStep_598[1])
    {
        case 0:
            g_Gfx_ScreenFade                                = 6;
            g_Gfx_ScreenPos_InvertColorBg_TransitionCounter = 0xFF;
            g_GameWork.gameStateStep_598[1]                 = 1;
            g_GameWork.gameStateStep_598[2]                 = 0;

        case 1:
            g_GameWork.gameStateStep_598[2] = 0;
            g_GameWork.gameStateStep_598[1] += 1;
            break;

        case 2:
            if (g_ControllerPtrConst->field_18 & ControllerFlag_LStickUp)
            {
                g_GameWorkConst->config_0.optScreenPosY_1D--;
            }
            if (g_ControllerPtrConst->field_18 & ControllerFlag_LStickDown)
            {
                g_GameWorkConst->config_0.optScreenPosY_1D++;
            }
            if (g_ControllerPtrConst->field_18 & ControllerFlag_LStickLeft)
            {
                g_GameWorkConst->config_0.optScreenPosX_1C--;
            }
            if (g_ControllerPtrConst->field_18 & ControllerFlag_LStickRight)
            {
                g_GameWorkConst->config_0.optScreenPosX_1C++;
            }

            g_GameWorkConst->config_0.optScreenPosX_1C = CLAMP(g_GameWorkConst->config_0.optScreenPosX_1C, -11, 11);
            g_GameWorkConst->config_0.optScreenPosY_1D = CLAMP(g_GameWorkConst->config_0.optScreenPosY_1D, -8, 8);

            if ((g_GameWorkConst->config_0.optScreenPosX_1C != g_ScreenPos_PosX) || (g_GameWorkConst->config_0.optScreenPosY_1D != g_ScreenPos_PosY))
            {
                func_80046048(0x519U, 0, 64);
            }
            if (g_ControllerPtrConst->btns_new_10 & g_GameWorkPtr->config_0.controllerConfig_0.enter_0)
            {
                if (g_Gfx_ScreenPos_InvertColorBg_TransitionCounter == 0xFF)
                {
                    g_Gfx_ScreenPos_InvertColorBg_TransitionCounter = 0;
                    g_Gfx_ScreenPos_InvertColorBg = (g_Gfx_ScreenPos_InvertColorBg + 1) & 1;
                }
            }
            if (g_ControllerPtrConst->btns_new_10 & g_GameWorkPtr->config_0.controllerConfig_0.cancel_2)
            {
                func_80046048(0x51AU, 0, 64);
                g_Gfx_ScreenFade                 = 2;
                g_GameWork.gameStateStep_598[2]  = 0;
                g_GameWork.gameStateStep_598[1] += 1;
            }
            break;

        case 3:
            if ((g_Gfx_ScreenFade & 0x7) == 5)
            {
                g_Gfx_ScreenFade                   = 6;
                g_GameWork.gameStateStep_598[0]    = 10;
                g_SysWork.timer_20                 = 0;
                g_GameWork.gameStateStep_598[1]    = 0;
                g_GameWork.gameStateStep_598[2]    = 0;
                g_GameWork.background2dColor_R_58C = 0;
                g_GameWork.background2dColor_G_58D = 0;
                g_GameWork.background2dColor_B_58E = 0;
                return;
            }
            break;
    }

    g_Gfx_ScreenPos_InvertColorBg_TransitionCounter += 16;
    g_Gfx_ScreenPos_InvertColorBg_TransitionCounter = CLAMP(g_Gfx_ScreenPos_InvertColorBg_TransitionCounter, 0, 0xFF);

    switch (g_Gfx_ScreenPos_InvertColorBg)
    {
        case 0:
            g_GameWork.background2dColor_R_58C = ~g_Gfx_ScreenPos_InvertColorBg_TransitionCounter;
            g_GameWork.background2dColor_G_58D = ~g_Gfx_ScreenPos_InvertColorBg_TransitionCounter;
            g_GameWork.background2dColor_B_58E = ~g_Gfx_ScreenPos_InvertColorBg_TransitionCounter;
            break;

        case 1:
            g_GameWork.background2dColor_R_58C = g_Gfx_ScreenPos_InvertColorBg_TransitionCounter;
            g_GameWork.background2dColor_G_58D = g_Gfx_ScreenPos_InvertColorBg_TransitionCounter;
            g_GameWork.background2dColor_B_58E = g_Gfx_ScreenPos_InvertColorBg_TransitionCounter;
            break;
    }

    packet = GsOUT_PACKET_P;

    for (i = 0; i < 6; i++)
    {
        tile = (TILE*)packet;

        setTile(tile);

        if (g_Gfx_ScreenPos_InvertColorBg == 0)
        {
            setRGB0(tile, 0xFF, 0, 0);
        }
        else if (g_Gfx_ScreenPos_InvertColorBg == 1)
        {
            setRGB0(tile, 0xFF, 0, 0);
        }

        if (i < 3)
        {
            setXY0(tile, -0xA0, (-0x61 + (0x60 * i)));
            setWH(tile, 0x140, 2);
        }
        else
        {
            setXY0(tile, (-0x241 + (0x90 * i)), -0x78);
            setWH(tile, 2, 0xF0);
        }

        addPrim(g_ObjectTable0[g_ObjectTableIdx].org, (TILE*)packet);
        packet += sizeof(TILE);
    }

    for (i = 0; i < 28; i++)
    {
        tile = (TILE*)packet;

        setTile(tile);

        switch (g_Gfx_ScreenPos_InvertColorBg)
        {
            case 0:
                setRGB0(tile, g_Gfx_ScreenPos_InvertColorBg_TransitionCounter, g_Gfx_ScreenPos_InvertColorBg_TransitionCounter, g_Gfx_ScreenPos_InvertColorBg_TransitionCounter);
                break;

            case 1:
                setRGB0(tile, ~g_Gfx_ScreenPos_InvertColorBg_TransitionCounter, ~g_Gfx_ScreenPos_InvertColorBg_TransitionCounter, ~g_Gfx_ScreenPos_InvertColorBg_TransitionCounter);
                break;
        }

        if (i < 11)
        {
            setXY0(tile, -0xA0, (-0x51 + (16 * i)));
            setWH(tile, 0x140, 2);
        }
        else
        {
            setXY0(tile, (-0x131 + (16 * i)), -0x78);
            setWH(tile, 2, 0xF0);
        }

        addPrim(g_ObjectTable0[g_ObjectTableIdx].org, (TILE*)packet);
        packet += sizeof(TILE);
    }

    GsOUT_PACKET_P = packet;

    Gfx_PositionArrowsDraw();
    Gfx_PositionIndicatorDraw();
}

void Gfx_PositionArrowsDraw() // 0x801E5A08
{
    s_Triangle2d flashArrows[] =
    {
        { { 0x0000, 0xFF9C }, { 0xFFF8, 0xFFA4 }, { 0x0008, 0xFFA4 } },
        { { 0x0000, 0x0064 }, { 0xFFF8, 0x005C }, { 0x0008, 0x005C } },
        { { 0xFF6C, 0x0000 }, { 0xFF74, 0xFFF8 }, { 0xFF74, 0x0008 } },
        { { 0x0094, 0x0000 }, { 0x008C, 0xFFF8 }, { 0x008C, 0x0008 } },
    };

    s_Triangle2d borderArrows[] =
    {
        { { 0x0000, 0xFF9B }, { 0xFFF6, 0xFFA5 }, { 0x0009, 0xFFA5 } },
        { { 0x0000, 0x0065 }, { 0xFFF6, 0x005B }, { 0x0009, 0x005B } },
        { { 0xFF6B, 0x0000 }, { 0xFF75, 0xFFF6 }, { 0xFF75, 0x000A } },
        { { 0x0095, 0x0000 }, { 0x008B, 0xFFF6 }, { 0x008B, 0x000A } },
    };

    u8  dir[4];
    s32 i;

    // Clear directions array for no reason.
    memset(dir, 0, 4);

    // Draw flashing up/down/left/right arrows.
    for (i = 0; i < 4; i++)
    {
        Gfx_Options_BlueArrowDraw(&flashArrows[i], 1, 0);
    }

    if ((g_ControllerPtrConst->btns_new_10 & ControllerFlag_LStickUp) ||
        (g_ControllerPtrConst->btns_held_C & ControllerFlag_LStickUp))
    {
        dir[0] = 1;
    }
    if ((g_ControllerPtrConst->btns_new_10 & ControllerFlag_LStickDown) ||
        (g_ControllerPtrConst->btns_held_C & ControllerFlag_LStickDown))
    {
        dir[1] = 1;
    }
    if ((g_ControllerPtrConst->btns_new_10 & ControllerFlag_LStickLeft) ||
        (g_ControllerPtrConst->btns_held_C & ControllerFlag_LStickLeft))
    {
        dir[2] = 1;
    }
    if ((g_ControllerPtrConst->btns_new_10 & ControllerFlag_LStickRight) ||
        (g_ControllerPtrConst->btns_held_C & ControllerFlag_LStickRight))
    {
        dir[3] = 1;
    }

    // Draw border to highlight flashing up/down/left/right arrow corresponding to direction of UI movement.
    for (i = 0; i < 4; i++)
    {
        if (dir[i] != 0)
        {
            Gfx_Options_BlueArrowDraw(&borderArrows[i], 0, 0);
        }
    }
}

void Gfx_PositionIndicatorDraw() // 0x801E5CBC
{
    GsOT*    ot = &g_ObjectTable1[g_ObjectTableIdx];
    s32      i;
    LINE_F2* line;
    POLY_F4* poly;

    DVECTOR D_801E2C4C[] =
    {
        { 0xFFC4, 0x0028 },
        { 0xFFC4, 0x0046 },
        { 0x003C, 0x0046 },
        { 0x003C, 0x0028 }
    };

    char* offsetStr[] =
    {
        "X:_",
        "Y:_"
    };

    for (i = 0; i < 4; i++)
    {
        line = (LINE_F2*)GsOUT_PACKET_P;

        setLineF2(line);
        setCodeWord(line, 0x40, (i < 2) ? 0xF0F0F0 : 0x808080);

        setXY0Fast(line, (u16)(D_801E2C4C[i].vx - g_GameWorkConst->config_0.optScreenPosX_1C), D_801E2C4C[i].vy - g_GameWorkConst->config_0.optScreenPosY_1D);
        setXY1Fast(line, (u16)(D_801E2C4C[(i + 1) & 3].vx - g_GameWorkConst->config_0.optScreenPosX_1C), D_801E2C4C[(i + 1) & 3].vy - g_GameWorkConst->config_0.optScreenPosY_1D);

        addPrim((u8*)ot->org + 0x28, line);
        GsOUT_PACKET_P = (u8*)line + sizeof(LINE_F2);
    }

    poly = (POLY_F4*)GsOUT_PACKET_P;
    setPolyF4(poly);

    setCodeWord(poly, 0x28, 0);
    setXY0Fast(poly, (u16)(D_801E2C4C[0].vx - g_GameWorkConst->config_0.optScreenPosX_1C), D_801E2C4C[0].vy - g_GameWorkConst->config_0.optScreenPosY_1D);
    setXY1Fast(poly, (u16)(D_801E2C4C[1].vx - g_GameWorkConst->config_0.optScreenPosX_1C), D_801E2C4C[1].vy - g_GameWorkConst->config_0.optScreenPosY_1D);
    setXY2Fast(poly, (u16)(D_801E2C4C[3].vx - g_GameWorkConst->config_0.optScreenPosX_1C), D_801E2C4C[3].vy - g_GameWorkConst->config_0.optScreenPosY_1D);
    setXY3Fast(poly, (u16)(D_801E2C4C[2].vx - g_GameWorkConst->config_0.optScreenPosX_1C), D_801E2C4C[2].vy - g_GameWorkConst->config_0.optScreenPosY_1D);

    addPrim((u8*)ot->org + 0x28, poly);
    GsOUT_PACKET_P = (u8*)poly + sizeof(POLY_F4);

    Gfx_StringSetPosition(108 - g_GameWorkConst->config_0.optScreenPosX_1C, 162 - g_GameWorkConst->config_0.optScreenPosY_1D);
    Gfx_StringDraw(offsetStr[0], 10);
    Gfx_StringDrawInt(3, g_GameWorkConst->config_0.optScreenPosX_1C);
    Gfx_StringSetPosition(168 - g_GameWorkConst->config_0.optScreenPosX_1C, 162 - g_GameWorkConst->config_0.optScreenPosY_1D);
    Gfx_StringDraw(offsetStr[1], 10);
    Gfx_StringDrawInt(3, g_GameWorkConst->config_0.optScreenPosY_1D);
}

// ========================
// BRIGHTNESS OPTION SCREEN
// ========================

void Settings_BrightnessScreen() // 0x801E6018
{
    switch (g_GameWork.gameStateStep_598[1])
    {
        case 0:
            g_GameWork.gameStateStep_598[1] = 1;
            g_GameWork.gameStateStep_598[2] = 0;
            break;

        case 1:
            g_Gfx_ScreenFade                = 6;
            g_GameWork.gameStateStep_598[1] = 2;
            g_GameWork.gameStateStep_598[2] = 0;
            break;

        case 2:
            if (g_ControllerPtrConst->field_18 & ControllerFlag_LStickLeft)
            {
                if (g_GameWork.config_0.optBrightness_22 != 0)
                {
                    g_GameWork.config_0.optBrightness_22--;
                    func_80046048(0x519, 0, 64);
                }
            }

            if (g_ControllerPtrConst->field_18 & ControllerFlag_LStickRight)
            {
                if (g_GameWork.config_0.optBrightness_22 < 7)
                {
                    g_GameWork.config_0.optBrightness_22++;
                    func_80046048(0x519, 0, 64);
                }
            }

            if (g_ControllerPtrConst->btns_new_10 & (g_GameWorkPtr->config_0.controllerConfig_0.enter_0 | g_GameWorkPtr->config_0.controllerConfig_0.cancel_2))
            {
                if (g_ControllerPtrConst->btns_new_10 & g_GameWorkPtr->config_0.controllerConfig_0.enter_0)
                {
                    func_80046048(0x51B, 0, 64);
                }
                else
                {
                    func_80046048(0x51A, 0, 64);
                }

                g_Gfx_ScreenFade                = 2;
                g_GameWork.gameStateStep_598[1]++;
                g_GameWork.gameStateStep_598[2] = 0;
            }
            break;

        case 3:
            if (g_Gfx_ScreenFade & (1 << 2) && (g_Gfx_ScreenFade & (1 << 1)) == 0 && g_Gfx_ScreenFade & (1 << 0))
            {
                g_Gfx_ScreenFade                   = (1 << 2) | (1 << 1);
                g_GameWork.gameStateStep_598[0]    = 11;
                g_SysWork.timer_20                 = 0;
                g_GameWork.gameStateStep_598[1]    = 0;
                g_GameWork.gameStateStep_598[2]    = 0;
                g_GameWork.background2dColor_R_58C = 0;
                g_GameWork.background2dColor_G_58D = 0;
                g_GameWork.background2dColor_B_58E = 0;
            }
            break;

        default:
            break;
    }

    if (g_GameWork.gameStatePrev_590 == GameState_MainMenu)
    {
        Gfx_BackgroundSpriteDraw(&D_800A9044);
    }
    else
    {
        Gfx_BackgroundSpriteDraw(&D_800A904C);
    }

    func_8003E5E8(g_GameWork.config_0.optBrightness_22);
    Gfx_BrightnessLevelArrowsDraw();
    Gfx_BrightnessLevelTextDraw();
}

void Gfx_BrightnessLevelTextDraw() // 0x801E6238
{
    char* D_801E2C64 = "LEVEL_________";

    Gfx_StringSetColor(ColorId_White);
    Gfx_StringSetPosition(SCREEN_POSITION_X(25.0f), SCREEN_POSITION_Y(79.5f));
    Gfx_StringDraw(D_801E2C64, 20);
    Gfx_StringDrawInt(1, g_GameWork.config_0.optBrightness_22);
}

void Gfx_BrightnessLevelArrowsDraw() // 0x801E628C
{
    s_Triangle2d flashArrows[] =
    {
        { { 8, 84 }, {  16, 76 }, { 16, 92 } },
        { { 64, 84 }, { 56, 76 }, { 56, 92 } }
    };

    s_Triangle2d borderArrows[] =
    {
        { { 7, 84 },  { 17, 74 }, { 17, 94 } },
        { { 65, 84 }, { 55, 74 }, { 55, 94 } }
    };

    s32 btnInput;
    s32 i;
    s32 dir;

    // Determine UI movement direction.
    btnInput = g_ControllerPtrConst->btns_held_C;
    if (btnInput & ControllerFlag_LStickLeft)
    {
        dir = 1;
    }
    else if (btnInput & ControllerFlag_LStickRight)
    {
        dir = 2;
    }
    else
    {
        dir = 0;
    }

    // Draw flashing left/right arrows.
    for (i = 0; i < 2; i++)
    {
        Gfx_Options_BlueArrowDraw(&flashArrows[i], 1, 0);
    }

    // Draw border to highlight flashing left/right arrow corresponding to direction of UI movement.
    for (i = dir - 1; i < dir; i++)
    {
        Gfx_Options_BlueArrowDraw(&borderArrows[i], 0, 0);
    }
}

// ========================================
// DRAW OPTIONS FEATURES SCREEN
// ========================================

void Gfx_LineDraw(s_Line2d* line, s32 arg1, s32 arg2) // 0x801E641C
{
    GsOT*     ot = &g_ObjectTable1[g_ObjectTableIdx];
    LINE_G2*  linePrim;
    s_Line2d* linePtr;

    linePrim = (LINE_G2*)GsOUT_PACKET_P;
    linePtr  = line;

    setLineG2(linePrim);

    // BUG(?): Same color regardless of `arg2`.
    if (arg2)
    {
        setRGBC0(linePrim, 0xB0, 0xB0, 0xB0, 0x50);
        setRGBC1(linePrim, 0xA0, 0x80, 0x40, 0x50);
    }
    else
    {
        setRGBC0(linePrim, 0xB0, 0xB0, 0xB0, 0x50);
        setRGBC1(linePrim, 0xA0, 0x80, 0x40, 0x50);
    }

    setXY0Fast(linePrim, linePtr->vertex0_0.vx, linePtr->vertex0_0.vy);
    setXY1Fast(linePrim, linePtr->vertex1_4.vx, linePtr->vertex1_4.vy);

    addPrim((u8*)ot->org + (arg1 ? 36 : 24), linePrim);
    GsOUT_PACKET_P = (u8*)linePrim + sizeof(LINE_G2);

    if (arg1 != 0)
    {
        POLY_G4* poly = (POLY_G4*)GsOUT_PACKET_P;
        setPolyG4(poly);
        setSemiTrans(poly, 1);

        setRGB0(poly, 0, 0, 0);
        setRGB1(poly, 0x60, 0x60, 0x60);
        setRGB2(poly, 0, 0, 0);
        setRGB3(poly, 0x60, 0x60, 0x60);

        setXY4(poly,
               linePtr->vertex0_0.vx, linePtr->vertex0_0.vy - 16, linePtr->vertex0_0.vx, linePtr->vertex0_0.vy,
               linePtr->vertex1_4.vx, linePtr->vertex1_4.vy - 16, linePtr->vertex1_4.vx, linePtr->vertex1_4.vy);

        addPrim((u8*)ot->org + 36, poly);
        GsOUT_PACKET_P = (u8*)poly + sizeof(POLY_G4);

        func_80052088(0, 0, 9, 2);
    }
}

void Gfx_Options_BlueArrowDraw(s_Triangle2d* arrow, s32 isFlashing, s32 isColorReset) // 0x801E662C
{
    GsOT*    ot = &g_ObjectTable1[g_ObjectTableIdx];
    POLY_G3* arrowPoly;
    s32      colorFade;
    s32      colorStart;
    s32      colorEnd;

    // Leftover or oversight? `isColorReset` doesn't serve any meaningful purpose.
    if (isColorReset)
    {
        colorEnd   = 0;
        colorStart = 0;
    }

    colorFade = g_SysWork.timer_1C & 0x7F;

    // Fade start color.
    if (colorFade >= 32)
    {
        colorStart = 32;
        if (colorFade < 64)
        {
            colorStart = 32;
        }
        else if (colorFade < 96)
        {
            colorStart = 96 - colorFade;
        }
        else
        {
            colorStart = 0;
        }
    }
    else
    {
        colorStart = colorFade;
    }

    // Fade end color.
    if (colorFade >= 32)
    {
        if (colorFade < 64)
        {
            colorEnd = colorFade - 32;
        }
        else if (colorFade >= 96)
        {
            colorEnd = 128 - colorFade;
        }
        else
        {
            colorEnd = 32;
        }
    }
    else
    {
        colorEnd = 0;
    }


    // Draw blue arrow.
    arrowPoly = (POLY_G3*)GsOUT_PACKET_P;
    setPolyG3(arrowPoly);

    // Flash color from blue to cyan.
    if (isFlashing != 0)
    {
        // Base color is blue. `* 0x700` applies color shift somehow.
        *((u32*)&arrowPoly->r0) = (colorEnd   * 0x700) + 0x30FF0000;
        *((u32*)&arrowPoly->r1) = (colorStart * 0x700) + 0x30FF0000;
        *((u32*)&arrowPoly->r2) = (colorStart * 0x700) + 0x30FF0000;
    }
    // Set solid cyan color.
    else
    {
        setRGBC0(arrowPoly, 0x00, 0xF0, 0xF0, 0x30);
        setRGBC1(arrowPoly, 0x00, 0xF0, 0xF0, 0x30);
        setRGBC2(arrowPoly, 0x00, 0xF0, 0xF0, 0x30);
    }

    setXY0Fast(arrowPoly, arrow->vertex0_0.vx, arrow->vertex0_0.vy);
    setXY1Fast(arrowPoly, arrow->vertex1_4.vx, arrow->vertex1_4.vy);
    setXY2Fast(arrowPoly, arrow->vertex2_8.vx, arrow->vertex2_8.vy);

    addPrim((u8*)ot->org + 40, arrowPoly);
    GsOUT_PACKET_P = (u8*)arrowPoly + sizeof(POLY_G3);
}

void Gfx_ButtonDraw(s_Quad2d* quad, s32 arg1, s32 arg2) // 0x801E67B0
{
    GsOT*    ot = &g_ObjectTable1[g_ObjectTableIdx];
    s32      i;
    POLY_G3* poly;

    for (i = 0; i < 2; i++)
    {
        poly = (POLY_G3*)GsOUT_PACKET_P;
        setPolyG3(poly);

        if (arg1 != 0)
        {
            switch (arg2)
            {
                case 0:
                    setRGBC0(poly, 0xFF, 0xFF, 0xFF, 0x30);
                    setRGBC1(poly, 0xA0, 0x80, 0x40, 0x30);
                    setRGBC2(poly, 0x40, 0x40, 0x40, 0x30);
                    break;

                case 1:
                    setRGBC0(poly, 0x80, 0x80, 0x80, 0x30);
                    setRGBC1(poly, 0x28, 0x20, 0x10, 0x30);
                    setRGBC2(poly, 0x10, 0x10, 0x10, 0x30);
                    break;
            }

            if (i != 0)
            {
                setXY0Fast(poly, quad->vertex0_0.vx, quad->vertex0_0.vy);
                setXY1Fast(poly, quad->vertex1_4.vx, quad->vertex1_4.vy);
                setXY2Fast(poly, quad->vertex3_C.vx, quad->vertex3_C.vy);
            }
            else
            {
                setXY0Fast(poly, quad->vertex0_0.vx, quad->vertex0_0.vy);
                setXY1Fast(poly, quad->vertex2_8.vx, quad->vertex2_8.vy);
                setXY2Fast(poly, quad->vertex3_C.vx, quad->vertex3_C.vy);
            }
        }
        else
        {
            switch (arg2)
            {
                case 0:
                    setRGBC0(poly, 0xA0, 0x80, 0x40, 0x30);
                    setRGBC1(poly, 0xFF, 0xFF, 0xFF, 0x30);
                    setRGBC2(poly, 0xFF, 0xFF, 0xFF, 0x30);
                    break;

                case 1:
                    setRGBC0(poly, 0x50, 0x40, 0x20, 0x30);
                    setRGBC1(poly, 0xA0, 0xA0, 0xA0, 0x30);
                    setRGBC2(poly, 0xA0, 0xA0, 0xA0, 0x30);
                    break;
            }

            if (i != 0)
            {
                setXY0Fast(poly, quad->vertex3_C.vx, quad->vertex3_C.vy);
                setXY1Fast(poly, quad->vertex1_4.vx, quad->vertex1_4.vy);
                setXY2Fast(poly, quad->vertex2_8.vx, quad->vertex2_8.vy);
            }
            else
            {
                setXY0Fast(poly, quad->vertex0_0.vx, quad->vertex0_0.vy);
                setXY1Fast(poly, quad->vertex1_4.vx, quad->vertex1_4.vy);
                setXY2Fast(poly, quad->vertex2_8.vx, quad->vertex2_8.vy);
            }
        }

        addPrim((u8*)ot->org + 0x18, poly);
        GsOUT_PACKET_P = (u8*)poly + sizeof(POLY_G3);
    }
}

// ========================================
// CONTROLS OPTION SCREEN
// ========================================

void Settings_ControllerScreen() // 0x801E69BC
{
    s32           bindResult = -1;
    e_InputAction actionIdx;

    switch (g_GameWork.gameStateStep_598[1])
    {
        case BindingMenu_Exit:
            g_Gfx_ScreenFade                       = 7;
            g_ScreenCtrl_SelectedElement.menuIdx_0 = BindingMenu_Exit;

            if (g_ControllerPtrConst->btns_new_10 & (g_GameWorkPtr->config_0.controllerConfig_0.enter_0 | g_GameWorkPtr->config_0.controllerConfig_0.cancel_2))
            {
                Sd_EngineCmd(0x51A);
                g_Gfx_ScreenFade                = 3;
                g_GameWork.gameStateStep_598[1] = -2;
                g_GameWork.gameStateStep_598[2] = 0;
                break;
            }
            if (g_ControllerPtrConst->field_1C & ControllerFlag_LStickUp)
            {
                g_GameWork.gameStateStep_598[1] = 3;
                g_GameWork.gameStateStep_598[2] = 0;
            }
            else if (g_ControllerPtrConst->field_1C & ControllerFlag_LStickDown)
            {
                g_GameWork.gameStateStep_598[1] = 1;
                g_GameWork.gameStateStep_598[2] = 0;
            }
            else if (g_ControllerPtrConst->field_1C & (ControllerFlag_LStickLeft | ControllerFlag_LStickRight))
            {
                g_GameWork.gameStateStep_598[1] = -1;
                g_GameWork.gameStateStep_598[2] = 0;
            }
            break;

        case BindingMenu_Type_1:
        case BindingMenu_Type_2:
        case BindingMenu_Type_3:
            g_ScreenCtrl_SelectedElement.menuIdx_0 = g_GameWork.gameStateStep_598[1];
            if (g_ControllerPtrConst->btns_new_10 & g_GameWorkPtr->config_0.controllerConfig_0.enter_0)
            {
                Sd_EngineCmd(0x51B);
                Settings_RestoreControlDefaults(g_GameWork.gameStateStep_598[1] - 1);
            }
            else if (g_ControllerPtrConst->btns_new_10 & g_GameWorkPtr->config_0.controllerConfig_0.cancel_2)
            {
                Sd_EngineCmd(0x51A);
                g_GameWork.gameStateStep_598[1] = 0;
                g_GameWork.gameStateStep_598[2] = 0;
            }
            else
            {
                if (g_ControllerPtrConst->field_1C & ControllerFlag_LStickUp)
                {
                    g_GameWork.gameStateStep_598[1] = (g_GameWork.gameStateStep_598[1] - 1) & 0x3;
                    g_GameWork.gameStateStep_598[2] = 0;
                }
                else if (g_ControllerPtrConst->field_1C & ControllerFlag_LStickDown)
                {
                    g_GameWork.gameStateStep_598[1] = (g_GameWork.gameStateStep_598[1] + 1) & 0x3;
                    g_GameWork.gameStateStep_598[2] = 0;
                }
                else if (g_ControllerPtrConst->field_1C & (ControllerFlag_LStickLeft | ControllerFlag_LStickRight))
                {
                    g_GameWork.gameStateStep_598[1] = -1;
                    g_GameWork.gameStateStep_598[2] = 0;
                }
            }
            break;

        case BindingMenu_Actions:
            actionIdx = g_ScreenCtrl_SelectedElement.actionIdx_4;
            if (g_ControllerPtrConst->field_1C & ControllerFlag_LStickUp)
            {
                if (actionIdx != InputAction_Enter)
                {
                    g_ScreenCtrl_SelectedElement.actionIdx_4 = actionIdx - 1;
                }
                else
                {
                    g_ScreenCtrl_SelectedElement.actionIdx_4 = InputAction_Option;
                }
            }
            else if (g_ControllerPtrConst->field_1C & ControllerFlag_LStickDown)
            {
                if (actionIdx != InputAction_Option)
                {
                    g_ScreenCtrl_SelectedElement.actionIdx_4 = actionIdx + 1;
                }
                else
                {
                    g_ScreenCtrl_SelectedElement.actionIdx_4 = InputAction_Enter;
                }
            }
            else if (g_ControllerPtrConst->field_1C & (ControllerFlag_LStickLeft | ControllerFlag_LStickRight))
            {
                g_GameWork.gameStateStep_598[2] = 0;
                g_GameWork.gameStateStep_598[1] = g_ScreenCtrl_SelectedElement.menuIdx_0;
            }
            else
            {
                bindResult = Settings_ButtonChange(actionIdx);
            }
            break;

        case BindingMenu_Leave:
            if ((g_Gfx_ScreenFade & 0x7) == 5)
            {
                g_Gfx_ScreenFade                = 6;
                g_GameWork.gameStateStep_598[0] = 12;
                g_SysWork.timer_20              = 0;
                g_GameWork.gameStateStep_598[1] = 0;
                g_GameWork.gameStateStep_598[2] = 0;
            }
            break;

        default:
            break;
    }

    if (g_GameWork.gameStateStep_598[1] == -1)
    {
        g_ScreenCtrl_IsOverActions = 1;
    }
    else
    {
        g_ScreenCtrl_IsOverActions = 0;
    }

    if (g_ControllerPtrConst->field_1C & (ControllerFlag_LStickUp | ControllerFlag_LStickRight | ControllerFlag_LStickDown | ControllerFlag_LStickLeft))
    {
        Sd_EngineCmd(0x519);
    }

    Gfx_ControllerScreenDraw(g_ScreenCtrl_IsOverActions, g_ScreenCtrl_SelectedElement.menuIdx_0, g_ScreenCtrl_SelectedElement.actionIdx_4, bindResult);
}

s32 Settings_ButtonChange(s32 actionIdx) // 0x801E6CF4
{
    u16* bindings;
    u16  boundBtnFlag;
    u16  btnFlag;
    s32  curActionIdx;
    s32  res;
    s32  i;
    u32  j;

    res      = NO_VALUE;
    bindings = (u16*)&g_GameWorkPtr->config_0.controllerConfig_0;

    // Loop through all controller flags, excluding stick axes.
    for (i = 0; i < 16; i++)
    {
        btnFlag = 1 << i;

        if ((btnFlag & (ControllerFlag_DpadUp | ControllerFlag_DpadRight | ControllerFlag_DpadDown | ControllerFlag_DpadLeft)) ||
            !(btnFlag & g_ControllerPtrConst->btns_new_10))
        {
            continue;
        }

        boundBtnFlag = bindings[actionIdx];

        // Remove binding.
        if (boundBtnFlag & btnFlag)
        {
            if ((actionIdx < InputAction_Skip ||
                 actionIdx == InputAction_Action ||
                 actionIdx == InputAction_Aim ||
                 actionIdx == InputAction_Item) &&
                !(bindings[actionIdx] & ~btnFlag))
            {
                res = actionIdx;
                Sd_EngineCmd(0x518);
            }
            else
            {
                bindings[actionIdx] &= ~btnFlag;
                Sd_EngineCmd(0x51B);
            }
        }
        else
        {
            curActionIdx = NO_VALUE;
            switch (actionIdx)
            {
                case 0:
                case 1:
                    curActionIdx = actionIdx == 0;
                    if (bindings[curActionIdx] & btnFlag)
                    {
                        if (!(bindings[curActionIdx] & ~btnFlag))
                        {
                            res = curActionIdx;
                            Sd_EngineCmd(0x518);
                        }
                        else
                        {
                            bindings[curActionIdx] &= ~btnFlag;
                            bindings[actionIdx]    |= btnFlag;
                            Sd_EngineCmd(0x51B);
                        }
                    }
                    else
                    {
                        bindings[actionIdx] = boundBtnFlag | btnFlag;
                        Sd_EngineCmd(0x51B);
                    }
                    break;

                case 2:
                    bindings[InputAction_Skip] |= btnFlag;
                    Sd_EngineCmd(0x51B);
                    break;

                default:
                    curActionIdx = NO_VALUE;
                    for (j = InputAction_Action; j < InputAction_Count; j++)
                    {
                        if (bindings[j] & btnFlag)
                        {
                            curActionIdx = j;
                            break;
                        }
                    }

                    if (curActionIdx != NO_VALUE)
                    {
                        if ((curActionIdx < InputAction_Skip ||
                             curActionIdx == InputAction_Action ||
                             curActionIdx == InputAction_Aim ||
                             curActionIdx == InputAction_Item) &&
                            !(bindings[curActionIdx] & ~btnFlag))
                        {
                            Sd_EngineCmd(0x518);
                            res = curActionIdx;
                        }
                        else
                        {
                            bindings[curActionIdx] &= ~btnFlag;
                            bindings[actionIdx]    |= btnFlag;
                            Sd_EngineCmd(0x51B);
                        }
                    }
                    else
                    {
                        bindings[actionIdx] |= btnFlag;
                        Sd_EngineCmd(0x51B);
                    }
                    break;
            }
        }
    }

    return res;
}

DR_MODE D_801E730C[2] =
{
    { .tag = 0x03000000, .code = { 0xE1000200, 0 } },
    { .tag = 0x03000000, .code = { 0xE1000200, 0 } }
};

POLY_G4 D_801E7324[2] =
{
    { .tag = 0x08000000, .r0 = 0xFF, .g0 = 0xFF, .b0 = 0xFF, .code = 0x3A, .r3 = 0xFF, .g3 = 0xFF, .b3 = 0xFF },
    { .tag = 0x08000000, .code = 0x3A, .r1 = 0xFF, .g1 = 0xFF, .b1 = 0xFF, .r2 = 0xFF, .g2 = 0xFF, .b2 = 0xFF },
};

char* g_ScreenCtrl_Options[] =
{
    "EXIT",
    "TYPE_1",
    "TYPE_2",
    "TYPE_3"
};

char* g_ScreenCtrl_Actions[] =
{
    "ENTER",
    "CANCEL",
    "SKIP",
    "ACTION",
    "AIM",
    "LIGHT",
    "RUN",
    "VIEW",
    "STEP L",
    "STEP R",
    "PAUSE",
    "ITEM",
    "MAP",
    "OPTION"
};

/** Unknown Rodata values.
 * The types are assumed. It is unknown where
 * are this applied, they could be also some
 * sort of value defined with an macro.
 */
static const u16 D_801E2D42 = 4160;

DVECTOR D_801E73B4 = { 0, 0 };

DVECTOR D_801E73B8 = { 0, 0 };

DVECTOR D_801E73BC = { 0, 0 };

DVECTOR D_801E73C0 = { 0, 0 };

DVECTOR D_801E73C4 = { 0, 0 };

DVECTOR D_801E73C8 = { 0, 0 };

DVECTOR D_801E73CC = { 0, 0 };

DVECTOR D_801E73D0 = { 0, 0 };

s32 g_Gfx_ScreenPos_InvertColorBg_TransitionCounter = 0;

s16 g_ScreenPos_PosX = 0;

s16 g_ScreenPos_PosY = 0;

s_ScreenCtrl_SelectedElement g_ScreenCtrl_SelectedElement = { BindingMenu_Exit, InputAction_Enter };

s32 g_Gfx_MoveLineTimer = 0;

s32 g_OptExtra_ShowSettingsCount = 0;

s32 g_OptExtra_BloodColorSelected = 0;

s32 g_OptExtra_BulletMultLimit = 0;

void Gfx_ControllerScreenDraw(s32 arg0, s32 arg1, s32 arg2, s32 arg3) // 0x801E6F60
{
    s16      y0;
    s16      y1;
    u16*     bindPtr;
    POLY_G4* poly;
    GsOT*    ot;
    DR_MODE* drMode;
    s32      strYPos;
    s32      i;

    ot     = (GsOT*)((g_ObjectTableIdx << 6) + (u8*)&D_800B5C7C);
    poly   = &D_801E7324[g_ObjectTableIdx];
    drMode = &D_801E730C[g_ObjectTableIdx];

    for (i = 0; i < 4; i++)
    {
        Gfx_StringSetPosition(24, 22 + (i * 20));
        Gfx_StringDraw(g_ScreenCtrl_Options[i], 0x14);
    }

    if (arg0 == 0)
    {
        y1 = arg1 * 0x14;
        y0 = y1 - 0x5B;
        setXY4(poly, -0x89, y0, -0x4C, y0, -0x89, y1 - 0x4C, -0x4C, y1 - 0x4C);
    }

    strYPos = 22;
    y0      = -300;

    for (i = 0, bindPtr = (u16*)&g_GameWorkPtr->config_0.controllerConfig_0; i < (u32)0xE; i++, bindPtr++)
    {
        Gfx_DebugStringPosition(96, strYPos);
        Gfx_DebugStringDraw(g_ScreenCtrl_Actions[i]);

        if (i != arg3)
        {
            Gfx_ControllerButtonsDraw(-12, strYPos - 114, *bindPtr);
        }

        if (i == arg2)
        {
            y0 = strYPos - 113;
        }

        strYPos = strYPos + 12 + ((i == 2) ? 12 : 0);
    }

    if (arg0 == 1)
    {
        setXY4(poly, -65, y0, -15, y0, -65, y0 + 10, -15, y0 + 10);
    }

    AddPrim(ot, poly);
    AddPrim(ot, drMode);
}

void Gfx_ControllerButtonsDraw(s32 arg0, s32 arg1, u16 arg2) // 0x801E716C
{
    s32            i;
    s32            x0;
    u16            clutX;
    u32            clutY;
    int            temp;
    GsOT*          ot;
    SPRT*          prim;
    DR_TPAGE*      tpage;
    int            v0;
    PACKET*        packet;
    s_FsImageDesc* image = &D_800A903C;

    ot     = &D_800B5D04[g_ObjectTableIdx];
    packet = GsOUT_PACKET_P;

    for (x0 = arg0, i = 12; i < 28; i++)
    {
        temp = i & 0xF;
        v0   = ((temp + 8) & 0xF) << 4;

        if ((arg2 >> temp) & 1)
        {
            prim = (SPRT*)packet;
            addPrimFast(ot, prim, 4);
            setCodeWord(prim, PRIM_RECT | RECT_TEXTURE, 0x808080);
            setWH(prim, 12, 12);

            clutY = image->clutY;
            clutX = image->clutX;

            setXY0Fast(prim, x0, arg1);
            x0 += 0xE;

            // setUV0AndClut(prim, 0xF4, v0, clutY, clutX);
            *(u32*)(&prim->u0) = 0xF4 + (v0 << 8) + (((clutY << 6) | ((clutX >> 4) & 0x3F)) << 0x10);

            packet = (u8*)prim + sizeof(SPRT);
            tpage  = (DR_TPAGE*)packet;

            setDrawTPage(tpage, 0, 1, 7);
            AddPrim(ot, tpage);
            packet = (u8*)tpage + sizeof(DR_TPAGE);
        }
    }

    GsOUT_PACKET_P = packet;
}
