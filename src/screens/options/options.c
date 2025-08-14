#include "game.h"

#include <libetc.h>

#include "bodyprog/bodyprog.h"
#include "bodyprog/item_screens.h"
#include "bodyprog/math.h"
#include "screens/options/options.h"
#include "screens/stream/stream.h"

// ==================================
// MAIN, EXTRA, AND SUB OPTION MENUS
// ==================================

#define MENU_FADE_STEP        16
#define LINE_CURSOR_TIMER_MAX 8

s32  g_MainMenu_SelectedIdx               = 0;
s32  g_ExtraMenu_SelectedIdx              = 0;
s32  g_MainMenu_PrevSelectedIdx           = 0;
s32  g_ExtraMenu_PrevSelectedIdx          = 0;
s32  g_Gfx_ScreenPos_InvertColorBg        = 0;
bool g_ControllerSubmenu_IsOnActionColumn = false;

void GameState_OptionScreen_Update() // 0x801E2D44
{
    s32 unlockedOptFlags;
    s32 i;

    if (g_GameWork.gameStatePrev_590 == GameState_InGame)
    {
        func_800363D0();
    }

    if (g_GameWork.gameStatePrev_590 != GameState_MainMenu)
    {
        Game_TimerUpdate();
    }

    // Handle options menu state.
    switch (g_GameWork.gameStateStep_598[0])
    {
        case OptMenuState_EnterMain:
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

            g_MainMenu_SelectedIdx         = 0;
            g_MainMenu_PrevSelectedIdx     = 0;
            g_ExtraMenu_SelectedIdx        = 0;
            g_ExtraMenu_PrevSelectedIdx    = 0;
            g_Options_SelectionCursorTimer = 0;
            g_OptExtra_BulletMultLimit     = 1;
            unlockedOptFlags               = g_GameWork.config_0.optExtraOptionsEnabled_27;
            
            // Set bullet multiplier available.
            for (i = 0; i < 5; i++)
            {
                if (unlockedOptFlags & (1 << i))
                {
                    g_OptExtra_BulletMultLimit++;
                }
            }

            // Set selected blood color.
            switch (g_GameWork.config_0.optExtraBloodColor_24)
            {
                case BloodColor_Normal:
                    g_OptExtra_BloodColorSelected = OptBloodColor_Normal;
                    break;

                case BloodColor_Green:
                    g_OptExtra_BloodColorSelected = OptBloodColor_Green;
                    break;

                case BloodColor_Violet:
                    g_OptExtra_BloodColorSelected = OptBloodColor_Violet;
                    break;

                case BloodColor_Black:
                    g_OptExtra_BloodColorSelected = OptBloodColor_Black;
                    break;
            }

            g_OptExtra_ShowSettingsCount    = (g_GameWork.config_0.optExtraOptionsEnabled_27 != 0) ? 8 : 6;
            g_GameWork.gameStateStep_598[0] = OptMenuState_Main;
            g_SysWork.timer_20              = 0;
            g_GameWork.gameStateStep_598[1] = 0;
            g_GameWork.gameStateStep_598[2] = 0;
            break;

        case OptMenuState_LeaveScreenPos:
        case OptMenuState_LeaveBrightness:
        case OptMenuState_LeaveController:
            g_GameWork.gameStateStep_598[0] = OptMenuState_Main;
            g_SysWork.timer_20              = 0;
            g_GameWork.gameStateStep_598[1] = 0;
            g_GameWork.gameStateStep_598[2] = 0;
            break;

        case OptMenuState_EnterScreenPos:
            if ((g_Gfx_ScreenFade & 0x7) == 5)
            {
                g_GameWork.gameStateStep_598[0] = OptMenuState_ScreenPos;
                g_SysWork.timer_20              = 0;
                g_GameWork.gameStateStep_598[1] = 0;
                g_GameWork.gameStateStep_598[2] = 0;
            }
            break;

        case OptMenuState_ScreenPos:
            Settings_PositionScreen();
            break;

        case OptMenuState_EnterBrightness:
            if ((g_Gfx_ScreenFade & 0x7) == 5)
            {
                Fs_QueueWaitForEmpty();

                g_GameWork.gameStateStep_598[0] = OptMenuState_Brightness;
                g_GameWork.gameStateStep_598[0] = OptMenuState_Brightness;
                g_SysWork.timer_20              = 0;
                g_GameWork.gameStateStep_598[1] = 0;
                g_GameWork.gameStateStep_598[2] = 0;
            }
            break;

        case OptMenuState_Brightness:
            Settings_BrightnessScreen();
            break;

        case OptMenuState_EnterController:
            // Switch to controller binding submenu.
            if ((g_Gfx_ScreenFade & 0x7) == 5)
            {
                g_GameWork.gameStateStep_598[0] = OptMenuState_Controller;
                g_GameWork.gameStateStep_598[0] = OptMenuState_Controller;
                g_SysWork.timer_20              = 0;
                g_GameWork.gameStateStep_598[1] = 0;
                g_GameWork.gameStateStep_598[2] = 0;
            }
            break;

        case OptMenuState_Controller:
            Settings_ControllerScreen();
            break;

        case OptMenuState_LeaveMenu:
            g_Gfx_ScreenFade                = 2;
            g_GameWork.gameStateStep_598[0] = OptMenuState_LeaveMain;
            g_SysWork.timer_20              = 0;
            g_GameWork.gameStateStep_598[1] = 0;
            g_GameWork.gameStateStep_598[2] = 0;
            break;

        case OptMenuState_LeaveMain:
            if ((g_Gfx_ScreenFade & 0x7) == 0x5)
            {
                // TODO: Likely `Game_StateSetPrevious` inline, but `gameState_594`/`gameStatePrev_590` loads inside are switched?

                e_GameState prevGameState = g_GameWork.gameStatePrev_590;
                e_GameState gameState     = g_GameWork.gameState_594;

                g_SysWork.timer_1C              = 0;
                g_SysWork.timer_20              = 0;
                g_GameWork.gameStateStep_598[1] = 0;
                g_GameWork.gameStateStep_598[2] = 0;

                SysWork_StateSetNext(SysState_Gameplay);

                g_GameWork.gameStateStep_598[0] = gameState;
                g_GameWork.gameState_594        = prevGameState;
                g_GameWork.gameStatePrev_590    = gameState;
                g_GameWork.gameStateStep_598[0] = OptMenuState_EnterMain;
            }

            break;

        case OptMenuState_EnterExtra:
            if ((g_Gfx_ScreenFade & 0x7) == 5)
            {
                g_GameWork.gameStateStep_598[0] = OptMenuState_Extra;
                g_SysWork.timer_20              = 0;
                g_Gfx_ScreenFade                = 7;
                g_GameWork.gameStateStep_598[1] = 0;
                g_GameWork.gameStateStep_598[2] = 0;
                g_Options_SelectionCursorTimer  = 0;
            }
            break;

        case OptMenuState_LeaveExtra:
            if ((g_Gfx_ScreenFade & 0x7) == 5)
            {
                g_GameWork.gameStateStep_598[0] = OptMenuState_EnterMain;
                g_SysWork.timer_20              = 0;
                g_GameWork.gameStateStep_598[1] = 0;
                g_GameWork.gameStateStep_598[2] = 0;
                g_Gfx_ScreenFade                = 7;
            }
            break;
    }

    // Handle menu state.
    switch (g_GameWork.gameStateStep_598[0])
    {
        case OptMenuState_Main:
        case OptMenuState_LeaveMenu:
        case OptMenuState_LeaveMain:
        case OptMenuState_EnterScreenPos:
        case OptMenuState_EnterBrightness:
        case OptMenuState_EnterController:
        case OptMenuState_EnterExtra:
            Settings_MainScreen();
            break;

        case OptMenuState_Extra:
        case OptMenuState_LeaveExtra:
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
    Gfx_BackgroundSpriteDraw(&g_ItemInspectionImg);

    if (g_GameWork.gameStateStep_598[0] != OptMenuState_Extra)
    {
        return;
    }

    // Increment line move timer.
    if ((LINE_CURSOR_TIMER_MAX - 1) < g_Options_SelectionCursorTimer)
    {
        g_Options_SelectionCursorTimer = LINE_CURSOR_TIMER_MAX;
    }
    else
    {
        g_Options_SelectionCursorTimer++;
    }

    if (g_Options_SelectionCursorTimer == LINE_CURSOR_TIMER_MAX)
    {
        g_ExtraMenu_PrevSelectedIdx = g_ExtraMenu_SelectedIdx;

        // Leave to gameplay (if options menu was accessed with `Option` input action).
        if (g_GameWork.gameStatePrev_590 == GameState_InGame && 
            !(g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.enter_0) &&
            (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.option_1A))
        {
            Sd_PlaySfx(Sfx_Cancel, 0, 64);

            g_GameWork.gameStateStep_598[0] = OptMenuState_LeaveMenu;
            g_SysWork.timer_20              = 0;
            g_GameWork.gameStateStep_598[1] = 0;
            g_GameWork.gameStateStep_598[2] = 0;
            return;
        }

        // Move selection cursor up/down.
        if (g_Controller0->btnsPulsed_18 & ControllerFlag_LStickUp)
        {
            s32 var = 1;
            Sd_PlaySfx(Sfx_Back, 0, 64);
            g_ExtraMenu_SelectedIdx       = ((g_ExtraMenu_SelectedIdx - var) + g_OptExtra_ShowSettingsCount) % g_OptExtra_ShowSettingsCount;
            g_Options_SelectionCursorTimer = 0;
        }
        if (g_Controller0->btnsPulsed_18 & ControllerFlag_LStickDown)
        {
            Sd_PlaySfx(Sfx_Back, 0, 64);
            g_ExtraMenu_SelectedIdx++;
            g_ExtraMenu_SelectedIdx       = g_ExtraMenu_SelectedIdx % g_OptExtra_ShowSettingsCount;
            g_Options_SelectionCursorTimer = 0;
        }

        // Handle config change.
        switch (g_ExtraMenu_SelectedIdx)
        {
            case OptExtra_WeaponCtrl:
                // Scroll left/right.
                if (g_Controller0->btnsClicked_10 & (ControllerFlag_LStickRight | ControllerFlag_LStickLeft))
                {
                    Sd_PlaySfx(Sfx_Back, 0, 64);
                    g_GameWork.config_0.optExtraWeaponCtrl_23 = !g_GameWork.config_0.optExtraWeaponCtrl_23;
                }
                break;

            case OptExtra_Blood:
                // Scroll left/right.
                if (g_Controller0->btnsClicked_10 & ControllerFlag_LStickRight)
                {
                    Sd_PlaySfx(Sfx_Back, 0, 64);
                    g_OptExtra_BloodColorSelected++;
                }
                if (g_Controller0->btnsClicked_10 & ControllerFlag_LStickLeft)
                {
                    Sd_PlaySfx(Sfx_Back, 0, 64);
                    g_OptExtra_BloodColorSelected += 3;
                }

                // Set config.
                g_OptExtra_BloodColorSelected = g_OptExtra_BloodColorSelected % OptBloodColor_Count;
                switch (g_OptExtra_BloodColorSelected)
                {
                    case OptBloodColor_Normal:
                        g_GameWork.config_0.optExtraBloodColor_24 = BloodColor_Normal;
                        break;

                    case OptBloodColor_Green:
                        g_GameWork.config_0.optExtraBloodColor_24 = BloodColor_Green;
                        break;

                    case OptBloodColor_Violet:
                        g_GameWork.config_0.optExtraBloodColor_24 = BloodColor_Violet;
                        break;

                    case OptBloodColor_Black:
                        g_GameWork.config_0.optExtraBloodColor_24 = BloodColor_Black;
                        break;
                }
                break;

            case OptExtra_ViewCtrl:
                // Scroll left/right.
                if (g_Controller0->btnsClicked_10 & (ControllerFlag_LStickRight | ControllerFlag_LStickLeft))
                {
                    Sd_PlaySfx(Sfx_Back, 0, 64);

                    // Set config.
                    g_GameWork.config_0.optExtraViewCtrl_28 = !g_GameWork.config_0.optExtraViewCtrl_28;
                }
                break;

            case OptExtra_RetreatTurn:
                // Scroll left/right.
                if (g_Controller0->btnsClicked_10 & (ControllerFlag_LStickRight | ControllerFlag_LStickLeft))
                {
                    Sd_PlaySfx(Sfx_Back, 0, 64);

                    // Set config.
                    g_GameWork.config_0.optExtraRetreatTurn_2A = (s8)g_GameWork.config_0.optExtraRetreatTurn_2A == 0;
                }
                break;

            case OptExtra_MovementCtrl:
                // Scroll left/right.
                if (g_Controller0->btnsClicked_10 & (ControllerFlag_LStickRight | ControllerFlag_LStickLeft))
                {
                    Sd_PlaySfx(Sfx_Back, 0, 64);

                    // Set config.
                    g_GameWork.config_0.optExtraWalkRunCtrl_2B = (s8)g_GameWork.config_0.optExtraWalkRunCtrl_2B == 0;
                }
                break;

            case OptExtra_AutoAiming:
                // Scroll left/right.
                if (g_Controller0->btnsClicked_10 & (ControllerFlag_LStickRight | ControllerFlag_LStickLeft))
                {
                    Sd_PlaySfx(Sfx_Back, 0, 64);

                    // Set config.
                    g_GameWork.config_0.optExtraAutoAiming_2C = (s8)g_GameWork.config_0.optExtraAutoAiming_2C == 0;
                }
                break;

            case OptExtra_ViewMode:
                // Scroll left/right.
                if (g_Controller0->btnsClicked_10 & (ControllerFlag_LStickRight | ControllerFlag_LStickLeft))
                {
                    Sd_PlaySfx(Sfx_Back, 0, 64);

                    // Set config.
                    g_GameWork.config_0.optExtraViewMode_29 = !g_GameWork.config_0.optExtraViewMode_29;
                }
                break;

            case OptExtra_BulletMult:
                // Scroll left/right.
                if (g_Controller0->btnsClicked_10 & ControllerFlag_LStickRight)
                {
                    Sd_PlaySfx(Sfx_Back, 0, 64);

                    // Set config.
                    g_GameWork.config_0.optExtraBulletAdjust_2D++;
                }
                if (g_Controller0->btnsClicked_10 & ControllerFlag_LStickLeft)
                {
                    Sd_PlaySfx(Sfx_Back, 0, 64);

                    // Set config.
                    g_GameWork.config_0.optExtraBulletAdjust_2D = g_GameWork.config_0.optExtraBulletAdjust_2D + (g_OptExtra_BulletMultLimit - 1);
                }
                g_GameWork.config_0.optExtraBulletAdjust_2D = g_GameWork.config_0.optExtraBulletAdjust_2D % g_OptExtra_BulletMultLimit;
                break;
        }
    }

    // Leave menu.
    if ((g_Controller0->btnsClicked_10 & (g_GameWorkPtr->config_0.controllerConfig_0.cancel_2 |
                                          (ControllerFlag_L2 | ControllerFlag_R2 | ControllerFlag_L1 | ControllerFlag_R1))) &&
        g_GameWork.gameStateStep_598[0] != OptMenuState_LeaveExtra)
    {
        if (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.cancel_2)
        {
            Sd_PlaySfx(Sfx_Cancel, 0, 64);
        }
        else
        {
            Sd_PlaySfx(Sfx_Confirm, 0, 64);
        }

        g_Gfx_ScreenFade                = 2;
        g_GameWork.gameStateStep_598[0] = OptMenuState_LeaveExtra;
        g_SysWork.timer_20              = 0;
        g_GameWork.gameStateStep_598[1] = 0;
        g_GameWork.gameStateStep_598[2] = 0;
    }
}

void Settings_MainScreen() // 0x801E3770
{
    #define SOUND_VOL_STEP 8

    s32 cmd;
    s32 vol;

    // Draw menu graphics.
    Gfx_OptionsStringsMainDraw();
    Gfx_SettingsOptionsMainDraw();
    Gfx_SelectedOptionMain();
    Gfx_VignetteDraw();
    Gfx_BackgroundSpriteDraw(&g_ItemInspectionImg);
    Gfx_BgmBarDraw();
    Gfx_SfxBarDraw();

    if (g_GameWork.gameStateStep_598[0] != OptMenuState_Main)
    {
        return;
    }

    // Increment line move timer.
    if ((LINE_CURSOR_TIMER_MAX - 1) < g_Options_SelectionCursorTimer)
    {
        g_Options_SelectionCursorTimer = LINE_CURSOR_TIMER_MAX;
    }
    else
    {
        g_Options_SelectionCursorTimer++;
    }

    if (g_Options_SelectionCursorTimer != LINE_CURSOR_TIMER_MAX)
    {
        return;
    }

    g_MainMenu_PrevSelectedIdx = g_MainMenu_SelectedIdx;

    // Leave to gameplay (if options menu was accessed with `Option` input action).
    if (g_GameWork.gameStatePrev_590 == GameState_InGame && 
        !(g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.enter_0) &&
        (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.option_1A))
    {
        Sd_PlaySfx(Sfx_Cancel, 0, 64);

        g_GameWork.gameStateStep_598[0] = OptMenuState_LeaveMenu;
        g_SysWork.timer_20              = 0;
        g_GameWork.gameStateStep_598[1] = 0;
        g_GameWork.gameStateStep_598[2] = 0;
        return;
    }

    // Move selection cursor up/down.
    if (g_Controller0->btnsPulsed_18 & ControllerFlag_LStickUp)
    {
        Sd_PlaySfx(Sfx_Back, 0, 64);

        g_Options_SelectionCursorTimer = 0;
        g_MainMenu_SelectedIdx        = (g_MainMenu_SelectedIdx + (OptMain_Count - 1)) % OptMain_Count;
    }
    if (g_Controller0->btnsPulsed_18 & ControllerFlag_LStickDown)
    {
        Sd_PlaySfx(Sfx_Back, 0, 64);

        g_Options_SelectionCursorTimer = 0;
        g_MainMenu_SelectedIdx         = (g_MainMenu_SelectedIdx + 1) % OptMain_Count;
    }

    // Handle config change.
    switch (g_MainMenu_SelectedIdx)
    {
        case OptMain_Exit:
            // Exit menu to gameplay.
            if (g_Controller0->btnsClicked_10 & (g_GameWorkPtr->config_0.controllerConfig_0.enter_0 |
                                                 g_GameWorkPtr->config_0.controllerConfig_0.cancel_2))
            {
                Sd_PlaySfx(Sfx_Cancel, 0, 64);

                g_GameWork.gameStateStep_598[0] = OptMenuState_LeaveMenu;
                g_SysWork.timer_20              = 0;
                g_GameWork.gameStateStep_598[1] = 0;
                g_GameWork.gameStateStep_598[2] = 0;
            }
            break;

        case OptMain_Controller:
            // Enter controller screen.
            if (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.enter_0)
            {
                Sd_PlaySfx(Sfx_Confirm, 0, 64);
                Fs_QueueStartReadTim(FILE_TIM_OPTION2_TIM, IMAGE_BUFFER_3, &g_ControllerButtonAtlasImg);

                g_Gfx_ScreenFade                = 2;
                g_GameWork.gameStateStep_598[0] = OptMenuState_EnterController;
                g_SysWork.timer_20              = 0;
                g_GameWork.gameStateStep_598[1] = 0;
                g_GameWork.gameStateStep_598[2] = 0;
            }
            break;

        case OptMain_ScreenPosition:
            // Enter screen position screen.
            if (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.enter_0)
            {
                Sd_PlaySfx(Sfx_Confirm, 0, 64);

                g_Gfx_ScreenFade                = 2;
                g_GameWork.gameStateStep_598[0] = OptMenuState_EnterScreenPos;
                g_SysWork.timer_20              = 0;
                g_GameWork.gameStateStep_598[1] = 0;
                g_GameWork.gameStateStep_598[2] = 0;
            }
            break;

        case OptMain_Brightness:
            if (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.enter_0)
            {
                Sd_PlaySfx(Sfx_Confirm, 0, 64);
                if (g_GameWork.gameStatePrev_590 == GameState_MainMenu)
                {
                    Fs_QueueStartReadTim(FILE_TIM_OP_BRT_E_TIM, IMAGE_BUFFER_3, &g_BrightnessScreenImg0);
                }
                else
                {
                    Fs_QueueStartReadTim(FILE_TIM_OP_BRT_E_TIM, IMAGE_BUFFER_3, &g_BrightnessScreenImg1);
                }

                g_Gfx_ScreenFade                = 2;
                g_GameWork.gameStateStep_598[0] = OptMenuState_EnterBrightness;
                g_SysWork.timer_20              = 0;
                g_GameWork.gameStateStep_598[1] = 0;
                g_GameWork.gameStateStep_598[2] = 0;
            }
            break;

        case OptMain_Vibration:
            if (g_Controller0->btnsClicked_10 & (ControllerFlag_LStickRight | ControllerFlag_LStickLeft))
            {
                Sd_PlaySfx(Sfx_Back, 0, 64);
                g_GameWork.config_0.optVibrationEnabled_21 = !g_GameWork.config_0.optVibrationEnabled_21 << 7;
            }
            break;

        case OptMain_AutoLoad:
            if (g_Controller0->btnsClicked_10 & (ControllerFlag_LStickRight | ControllerFlag_LStickLeft))
            {
                Sd_PlaySfx(Sfx_Back, 0, 64);
                g_GameWork.config_0.optAutoLoad_25 = (s8)g_GameWork.config_0.optAutoLoad_25 == 0;
            }
            break;

        case OptMain_Sound:
            if (g_Controller0->btnsClicked_10 & (ControllerFlag_LStickRight | ControllerFlag_LStickLeft))
            {
                Sd_PlaySfx(Sfx_Back, 0, 64);

                // Set config.
                cmd                                 = 2;
                g_GameWork.config_0.optSoundType_1E = !g_GameWork.config_0.optSoundType_1E;
                if (g_GameWork.config_0.optSoundType_1E)
                {
                    cmd = 1;
                }
                Sd_EngineCmd(cmd);
            }
            break;

        case OptMain_BgmVolume:
            vol = g_GameWork.config_0.optVolumeBgm_1F;

            if ((vol < OPT_SOUND_VOLUME_MAX && (g_Controller0->btnsPulsed_18 & ControllerFlag_LStickRight)) ||
                (vol > 0                    && (g_Controller0->btnsPulsed_18 & ControllerFlag_LStickLeft)))
            {
                Sd_EngineCmd(Sfx_Back);
            }
            if ((vol == OPT_SOUND_VOLUME_MAX && (g_Controller0->btnsClicked_10 & ControllerFlag_LStickRight)) ||
                (vol == 0                    && (g_Controller0->btnsClicked_10 & ControllerFlag_LStickLeft)))
            {
                Sd_EngineCmd(Sfx_Denied);
            }

            // Scroll left/right.
            if (g_Controller0->btnsPulsed_18 & ControllerFlag_LStickRight)
            {
                vol = vol + SOUND_VOL_STEP;
            }
            if (g_Controller0->btnsPulsed_18 & ControllerFlag_LStickLeft)
            {
                vol = vol - SOUND_VOL_STEP;
            }

            // Set config.
            vol = CLAMP(vol, 0, OPT_SOUND_VOLUME_MAX);
            Sd_SetVolume(OPT_SOUND_VOLUME_MAX, vol, g_GameWork.config_0.optVolumeSe_20);
            g_GameWork.config_0.optVolumeBgm_1F = vol;
            break;

        case OptMain_SfxVolume:
            vol = g_GameWork.config_0.optVolumeSe_20;

            if ((vol < OPT_SOUND_VOLUME_MAX && (g_Controller0->btnsPulsed_18 & ControllerFlag_LStickRight)) ||
                (vol > 0                    && (g_Controller0->btnsPulsed_18 & ControllerFlag_LStickLeft)))
            {
                Sd_EngineCmd(Sfx_Back);
            }
            if ((vol == OPT_SOUND_VOLUME_MAX && (g_Controller0->btnsClicked_10 & ControllerFlag_LStickRight)) ||
                (vol == 0                    && (g_Controller0->btnsClicked_10 & ControllerFlag_LStickLeft)))
            {
                Sd_EngineCmd(Sfx_Denied);
            }

            if (g_Controller0->btnsPulsed_18 & ControllerFlag_LStickRight)
            {
                vol = vol + SOUND_VOL_STEP;
            }
            if (g_Controller0->btnsPulsed_18 & ControllerFlag_LStickLeft)
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

    if (g_Controller0->btnsClicked_10 & (ControllerFlag_L2 | ControllerFlag_R2 | ControllerFlag_L1 | ControllerFlag_R1))
    {
        if (g_GameWork.gameStateStep_598[0] == OptMenuState_EnterExtra)
        {
            return;
        }

        Sd_PlaySfx(Sfx_Confirm, 0, 64);

        g_Gfx_ScreenFade                = 2;
        g_GameWork.gameStateStep_598[0] = OptMenuState_EnterExtra;
        g_SysWork.timer_20              = 0;
        g_GameWork.gameStateStep_598[1] = 0;
        g_GameWork.gameStateStep_598[2] = 0;
    }

    // Reset selection cursor.
    if (((g_GameWork.gameStateStep_598[0] != OptMenuState_EnterExtra && g_MainMenu_SelectedIdx != OptMain_Exit) &&
         !(g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.enter_0)) &&
        (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.cancel_2))
    {
        Sd_PlaySfx(Sfx_Cancel, 0, 64);

        g_Options_SelectionCursorTimer = 0;
        g_MainMenu_SelectedIdx         = OptMain_Exit;
    }
}

void Gfx_BgmBarDraw() // 0x801E3F68
{
    Gfx_BarDraw(false, g_GameWork.config_0.optVolumeBgm_1F);
}

void Gfx_SfxBarDraw() // 0x801E3F90
{
    Gfx_BarDraw(true, g_GameWork.config_0.optVolumeSe_20);
}

void Gfx_BarDraw(bool isSfx, u8 vol) // 0x801E3FB8
{
    #define STR_OFFSET_Y 16
    #define NOTCH_SIZE_X 5
    #define NOTCH_COUNT  16

    s32      x0Offset;
    s32      x0;
    s32      offset;
    s32      yOffset;
    s32      localVol;
    s32      i;
    s32      j;
    u32      colorComp;
    s32      xOffset;
    s32      color0;
    s32      color1;
    s32      color2;
    GsOT*    ot;
    POLY_F4* poly;

    ot       = &g_ObjectTable1[g_ObjectTableIdx];
    localVol = vol;

    // Draw bar notches.
    for (i = 0; i < NOTCH_COUNT; i++)
    {
        colorComp = localVol & 0x7;
        colorComp = (colorComp * 12) + 64;

        for (j = 1; j >= 0; j--)
        {
            poly = (POLY_F4*)GsOUT_PACKET_P;
            setPolyF4(poly);

            if (i < (vol / 8))
            {
                color0 = 0xA0 + (0x40 * j);
                setRGBC0(poly, color0, color0, color0, 0x28);
            }
            else if (i > (vol / 8))
            {
                color1 = 0x40 + (0x40 * j);
                setRGBC0(poly, color1, color1, color1, 0x28);
            }
            else
            {
                color2 = colorComp + (0x40 * j);
                setRGBC0(poly, color2, color2, color2, 0x28);
            }

            xOffset = 24 + (i * 6);
            offset  = -69;

            x0Offset = j + 24;
            x0       = (x0Offset + (i * 6)) & 0xFFFF;
            yOffset  = j + 56;

            setXY0Fast(poly, x0,                           (isSfx * STR_OFFSET_Y) + yOffset);
            setXY1Fast(poly, x0,                           (isSfx * STR_OFFSET_Y) - (j + offset));
            setXY2Fast(poly, (xOffset - j) + NOTCH_SIZE_X, (isSfx * STR_OFFSET_Y) + yOffset);
            setXY3Fast(poly, (xOffset - j) + NOTCH_SIZE_X, (isSfx * STR_OFFSET_Y) - (j + offset));
            addPrim((u8*)ot->org + 24, poly);
            GsOUT_PACKET_P = (u8*)poly + sizeof(POLY_F4);
        }
    }
}

void Gfx_OptionsStringsExtraDraw() // 0x801E416C
{
    #define LINE_BASE_X   64
    #define LINE_BASE_Y   64
    #define LINE_OFFSET_X 16
    #define LINE_OFFSET_Y 16

    s32 i;

    DVECTOR strPos = { 86, 20 };

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

    // @unused: Likely older implementation for active highlight selection position reference setup found in `Options_ExtraGraphicsDraw`.
    if (g_Options_SelectionCursorTimer == 0)
    {
        g_Options_Extra_SelectionHighlightFrom_Unused.vx = LINE_BASE_X - LINE_OFFSET_X;
        g_Options_Extra_SelectionHighlightTo_Unused.vx   = LINE_BASE_X;
        g_Options_Extra_SelectionHighlightFrom_Unused.vy = ((u16)g_MainMenu_PrevSelectedIdx * LINE_OFFSET_Y) + LINE_BASE_Y;
        g_Options_Extra_SelectionHighlightTo_Unused.vy   = ((u16)g_MainMenu_SelectedIdx     * LINE_OFFSET_Y) + LINE_BASE_Y;
    }
    shRsin(g_Options_SelectionCursorTimer << 7);

    // Draw heading string.
    Gfx_StringSetColor(ColorId_White);
    Gfx_StringSetPosition(strPos.vx, strPos.vy);
    func_8004A8C0(8);
    Gfx_StringDraw(EXTRA_OPTION_str, 99);

    // Draw selection strings.
    for (i = 0; i < g_OptExtra_ShowSettingsCount; i++)
    {
        Gfx_StringSetPosition(LINE_BASE_X, LINE_BASE_Y + (i * LINE_OFFSET_Y));
        func_8004A8C0(8);
        Gfx_StringDraw(SettingsExtra_str[i], 99);
    }
}

void Gfx_OptionsStringsMainDraw() // 0x801E42EC
{
    #define LINE_BASE_X   64
    #define LINE_BASE_Y   56
    #define LINE_OFFSET_X 16
    #define LINE_OFFSET_Y 16

    s32 i;

    DVECTOR strPos = { 121, 20 };

    char* headingStr      = "OPTION_\x01\x01\x01\x01\x01S";
    char* selectionStrs[] =
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

    // @unused: Likely older implementation for active highlight selection position reference setup found in `Options_MainGraphicsDraw`.
    if (g_Options_SelectionCursorTimer == 0)
    {
        g_Options_Main_SelectionHighlightFrom_Unused.vx = LINE_BASE_X - LINE_OFFSET_X;
        g_Options_Main_SelectionHighlightTo_Unused.vx   = LINE_BASE_X;
        g_Options_Main_SelectionHighlightFrom_Unused.vy = ((u16)g_MainMenu_PrevSelectedIdx * LINE_OFFSET_Y) + LINE_BASE_Y;
        g_Options_Main_SelectionHighlightTo_Unused.vy   = ((u16)g_MainMenu_SelectedIdx     * LINE_OFFSET_Y) + LINE_BASE_Y;
    }
    shRsin(g_Options_SelectionCursorTimer << 7);

    // Draw heading string.
    Gfx_StringSetColor(ColorId_White);
    Gfx_StringSetPosition(strPos.vx, strPos.vy);
    func_8004A8C0(8);
    Gfx_StringDraw(headingStr, 99);

    // Draw selection strings.
    for (i = 0; i < OptMain_Count; i++)
    {
        Gfx_StringSetPosition(LINE_BASE_X, LINE_BASE_Y + (i * LINE_OFFSET_Y));
        func_8004A8C0(8);
        Gfx_StringDraw(selectionStrs[i], 99);
    }

    func_8004A8CC();
}

void Gfx_SelectedOptionExtra() // 0x801E4450
{
    #define LINE_BASE_X        64
    #define LINE_BASE_Y        56
    #define LINE_OFFSET_X      16
    #define LINE_OFFSET_Y      16
    #define HIGHLIGHT_OFFSET_X -121
    #define HIGHLIGHT_OFFSET_Y 50

    s32      i;
    s32      j;
    s16      interpAlpha;
    s_Line2d highlightLine;
    s_Quad2d bulletQuads[2];
    DVECTOR* quadVerts;

    u8 selectionHighlightWidths[] = // 0x801E2830
    {
        157, 126, 135, 135, 157, 130, 112, 134
    };

    // 12x12 quad.
    DVECTOR bulletQuadVertsFront[] = // 0x801E2838
    {
        { -120, -47 },
        { -120, -35 },
        { -108, -47 },
        { -108, -35 }
    };

    // 14x14 quad.
    DVECTOR bulletQuadVertsBack[] = // 0x801E2848
    {
        { -121, -48 },
        { -121, -34 },
        { -107, -48 },
        { -107, -34 }
    };

    // Set active selection highlight position references.
    if (g_Options_SelectionCursorTimer == 0)
    {
        g_Options_Extra_SelectionHighlightFrom.vx = selectionHighlightWidths[g_ExtraMenu_PrevSelectedIdx] + (65536 + HIGHLIGHT_OFFSET_X); // TODO
        g_Options_Extra_SelectionHighlightFrom.vy = ((u16)g_ExtraMenu_PrevSelectedIdx * LINE_OFFSET_Y)    - HIGHLIGHT_OFFSET_Y;
        g_Options_Extra_SelectionHighlightTo.vx   = selectionHighlightWidths[g_ExtraMenu_SelectedIdx]     + (65536 + HIGHLIGHT_OFFSET_X); // TODO
        g_Options_Extra_SelectionHighlightTo.vy   = ((u16)g_ExtraMenu_SelectedIdx * LINE_OFFSET_Y)        - HIGHLIGHT_OFFSET_Y;
    }

    // Compute sine-based interpolation alpha.
    interpAlpha = shRsin(g_Options_SelectionCursorTimer << 7);

    // Draw active selection highlight.
    highlightLine.vertex0_0.vx = HIGHLIGHT_OFFSET_X;
    highlightLine.vertex1_4.vx = g_Options_Extra_SelectionHighlightFrom.vx +
                                 FP_MULTIPLY(g_Options_Extra_SelectionHighlightTo.vx - g_Options_Extra_SelectionHighlightFrom.vx, interpAlpha, Q12_SHIFT);
    highlightLine.vertex1_4.vy = g_Options_Extra_SelectionHighlightFrom.vy +
                                 FP_MULTIPLY(g_Options_Extra_SelectionHighlightTo.vy - g_Options_Extra_SelectionHighlightFrom.vy, interpAlpha, Q12_SHIFT) +
                                 LINE_OFFSET_Y;
    highlightLine.vertex0_0.vy = highlightLine.vertex1_4.vy;
    Gfx_LineDraw(&highlightLine, true, false);

    // Draw selection bullet points.
    for (i = 0; i < g_OptExtra_ShowSettingsCount; i++)
    {
        // Set bullet quads.
        quadVerts = (DVECTOR*)&bulletQuads;
        for (j = 0; j < RECT_VERT_COUNT; j++)
        {
            quadVerts[j].vx                   = bulletQuadVertsFront[j].vx;
            quadVerts[j].vy                   = bulletQuadVertsFront[j].vy + (i * LINE_OFFSET_Y);
            quadVerts[j + sizeof(DVECTOR)].vx = bulletQuadVertsBack[j].vx;
            quadVerts[j + sizeof(DVECTOR)].vy = bulletQuadVertsBack[j].vy + (i * LINE_OFFSET_Y);
        }

        // Active selection bullet point.
        if (i == g_ExtraMenu_SelectedIdx)
        {
            Gfx_ButtonDraw(&bulletQuads[0], false, false);
            Gfx_ButtonDraw(&bulletQuads[1], true,  false);
        }
        // Inactive selection bullet point.
        else
        {
            Gfx_ButtonDraw(&bulletQuads[0], false, true);
            Gfx_ButtonDraw(&bulletQuads[1], true,  true);
        }
    }
}

void Gfx_SelectedOptionMain() // 0x801E472C
{
    #define LINE_OFFSET_Y      16
    #define HIGHLIGHT_OFFSET_X -121
    #define HIGHLIGHT_OFFSET_Y 58

    s32      i;
    s32      j;
    s16      interpAlpha;
    s_Line2d highlightLine;
    s_Quad2d bulletQuads[2];
    DVECTOR* quadVerts;

    u8 selectionHighlightWidths[] = // 0x801E2858
    {
        59, 169, 174, 156, 104, 112, 75, 129, 112
    };

    // 12x12 quad.
    DVECTOR bulletQuadVertsFront[] = // 0x801E2864
    {
        { -120, -55 },
        { -120, -43 },
        { -108, -55 },
        { -108, -43 }
    };

    // 14x14 quad.
    DVECTOR bulletQuadVertsBack[] = // 801E2874
    {
        { -121, -56 },
        { -121, -42 },
        { -107, -56 },
        { -107, -42 }
    };

    // Set active selection highlight position references.
    if (g_Options_SelectionCursorTimer == 0)
    {
        g_Options_Main_SelectionHighlightFrom.vx = selectionHighlightWidths[g_MainMenu_PrevSelectedIdx] + (65536 + HIGHLIGHT_OFFSET_X); // TODO
        g_Options_Main_SelectionHighlightFrom.vy = ((u16)g_MainMenu_PrevSelectedIdx * LINE_OFFSET_Y)    - HIGHLIGHT_OFFSET_Y;
        g_Options_Main_SelectionHighlightTo.vx   = selectionHighlightWidths[g_MainMenu_SelectedIdx]     + (65536 + HIGHLIGHT_OFFSET_X); // TODO
        g_Options_Main_SelectionHighlightTo.vy   = ((u16)g_MainMenu_SelectedIdx * LINE_OFFSET_Y)        - HIGHLIGHT_OFFSET_Y;
    }

    // Compute sine-based interpolation alpha.
    interpAlpha = shRsin(g_Options_SelectionCursorTimer << 7);

    // Draw active selection highlight.
    highlightLine.vertex0_0.vx = HIGHLIGHT_OFFSET_X;
    highlightLine.vertex1_4.vx = g_Options_Main_SelectionHighlightFrom.vx +
                                 FP_FROM((g_Options_Main_SelectionHighlightTo.vx - g_Options_Main_SelectionHighlightFrom.vx) * interpAlpha, Q12_SHIFT);
    highlightLine.vertex1_4.vy = g_Options_Main_SelectionHighlightFrom.vy +
                                 FP_FROM((g_Options_Main_SelectionHighlightTo.vy - g_Options_Main_SelectionHighlightFrom.vy) * interpAlpha, Q12_SHIFT) +
                                 LINE_OFFSET_Y;
    highlightLine.vertex0_0.vy = highlightLine.vertex1_4.vy;
    Gfx_LineDraw(&highlightLine, true, false);

    // Draw selection bullet points.
    for (i = 0; i < OptMain_Count; i++)
    {
        // Set bullet quads.
        quadVerts = (DVECTOR*)&bulletQuads;
        for (j = 0; j < RECT_VERT_COUNT; j++)
        {
            quadVerts[j].vx                   = bulletQuadVertsFront[j].vx;
            quadVerts[j].vy                   = bulletQuadVertsFront[j].vy + (i * LINE_OFFSET_Y);
            quadVerts[j + sizeof(DVECTOR)].vx = bulletQuadVertsBack[j].vx;
            quadVerts[j + sizeof(DVECTOR)].vy = bulletQuadVertsBack[j].vy + (i * LINE_OFFSET_Y);
        }

        // Active selection bullet point.
        if (i == g_MainMenu_SelectedIdx)
        {
            Gfx_ButtonDraw(&bulletQuads[0], false, false);
            Gfx_ButtonDraw(&bulletQuads[1], true,  false);
        }
        // Inactive selection bullet point.
        else
        {
            Gfx_ButtonDraw(&bulletQuads[0], false, true);
            Gfx_ButtonDraw(&bulletQuads[1], true,  true);
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

    xy3 = 160 + (0xFFA0 << 16); // TODO: -96
    xy2 = 160 + (0xFF90 << 16); // TODO: -112
    y1  = 0xFFA0 << 16;         // TODO: -96
    y0  = 0xFF90 << 16;         // TODO: -112

    for (i = 0; i < 2; i++)
    {
        poly = (POLY_G4*)GsOUT_PACKET_P;

        setPolyG4(poly);
        setSemiTrans(poly, 1);

        setRGB0(poly, 0x60, 0x60, 0x60);
        setRGB1(poly, 0, 0, 0);
        setRGB2(poly, 0x60, 0x60, 0x60);
        setRGB3(poly, 0, 0, 0);

        *(u32*)(&poly->x0) = 0xFF60 + (y0 + ((0xE0 * i) << 16)); // TODO: -160
        *(u32*)(&poly->x1) = 0xFF60 + (y1 + ((0xA8 * i) << 16)); // TODO: -160
        *(u32*)(&poly->x2) = xy2    + ((0xE0 * i) << 16);
        *(u32*)(&poly->x3) = xy3    + ((0xA8 * i) << 16);

        addPrim((u8*)ot->org + 8148, poly);
        GsOUT_PACKET_P = (u8*)poly + sizeof(POLY_G4);
    }

    Gfx_Primitive2dTextureSet(0, 0, 2037, 6);
}

void Gfx_SettingsOptionsExtraDraw() // 0x801E4B2C
{
    #define STR_BASE_Y   64
    #define STR_OFFSET_Y 16

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
    if (g_ExtraMenu_SelectedIdx < (u32)OptExtra_Count) // TODO: Cast suggests `g_ExtraMenu_SelectedIdx` type might be unsigned.
    {
        // Draw flashing left/right arrows.
        for (i = 0; i < 2; i++)
        {
            Gfx_Options_BlueArrowDraw(&flashArrows[(g_ExtraMenu_SelectedIdx * 2) + i], 1, 0);
        }

        // Draw border to highlight flashing left/right arrow corresponding to direction of UI navigation.
        if (g_Controller0->btnsHeld_C & ControllerFlag_LStickLeft)
        {
            Gfx_Options_BlueArrowDraw(&borderArrows[g_ExtraMenu_SelectedIdx << 1], 0, 0);
        }
        if (g_Controller0->btnsHeld_C & ControllerFlag_LStickRight)
        {
            Gfx_Options_BlueArrowDraw(&borderArrows[(g_ExtraMenu_SelectedIdx << 1) + 1], 0, 0);
        }
    }

    // Draw selection strings.
    for (j = 0; j < g_OptExtra_ShowSettingsCount; j++)
    {
        switch (j)
        {
            case OptExtra_WeaponCtrl:
                strPosX = (g_GameWork.config_0.optExtraWeaponCtrl_23 != 0) ? 217 : 212;
                Gfx_StringSetPosition(strPosX, STR_BASE_Y + (STR_OFFSET_Y * OptExtra_WeaponCtrl));
                Gfx_StringDraw(SettingsExtraOptions_str[!g_GameWork.config_0.optExtraWeaponCtrl_23], 10);
                break;

            case OptExtra_Blood:
                switch (g_OptExtra_BloodColorSelected)
                {
                    case OptBloodColor_Normal:
                        Gfx_StringSetPosition(210, STR_BASE_Y + (STR_OFFSET_Y * OptExtra_Blood));
                        break;

                    case OptBloodColor_Green:
                        Gfx_StringSetPosition(214, STR_BASE_Y + (STR_OFFSET_Y * OptExtra_Blood));
                        break;

                    case OptBloodColor_Violet:
                        Gfx_StringSetPosition(214, STR_BASE_Y + (STR_OFFSET_Y * OptExtra_Blood));
                        break;

                    case OptBloodColor_Black:
                        Gfx_StringSetPosition(217, STR_BASE_Y + (STR_OFFSET_Y * OptExtra_Blood));
                        break;
                }

                Gfx_StringDraw(SettingsExtraOptions_str[g_OptExtra_BloodColorSelected + 2], 10);
                break;

            case OptExtra_ViewCtrl:
                strPosX = !g_GameWork.config_0.optExtraViewCtrl_28 ? 210 : 206;
                Gfx_StringSetPosition(strPosX, STR_BASE_Y + (STR_OFFSET_Y * OptExtra_ViewCtrl));
                Gfx_StringDraw(SettingsExtraOptions_str[((g_GameWork.config_0.optExtraViewCtrl_28 != 0) ? 32 : 28) >> 2], 10);
                break;

            case OptExtra_RetreatTurn:
                strPosX = !g_GameWork.config_0.optExtraRetreatTurn_2A ? 210 : 206;
                Gfx_StringSetPosition(strPosX, STR_BASE_Y + (STR_OFFSET_Y * OptExtra_RetreatTurn));
                Gfx_StringDraw(SettingsExtraOptions_str[((g_GameWork.config_0.optExtraRetreatTurn_2A != 0) ? 32 : 28) >> 2], 10);
                break;

            case OptExtra_MovementCtrl:
                strPosX = !g_GameWork.config_0.optExtraWalkRunCtrl_2B ? 210 : 206;
                Gfx_StringSetPosition(strPosX, STR_BASE_Y + (STR_OFFSET_Y * OptExtra_MovementCtrl));
                Gfx_StringDraw(SettingsExtraOptions_str[((g_GameWork.config_0.optExtraWalkRunCtrl_2B != 0) ? 32 : 28) >> 2], 10);
                break;

            case OptExtra_AutoAiming:
                strPosX = !g_GameWork.config_0.optExtraAutoAiming_2C ? 228 : 226;
                Gfx_StringSetPosition(strPosX, STR_BASE_Y + (STR_OFFSET_Y * OptExtra_AutoAiming));
                Gfx_StringDraw(SettingsExtraOptions_str[((g_GameWork.config_0.optExtraAutoAiming_2C != 0) ? 40 : 36) >> 2], 10);
                break;

            case OptExtra_ViewMode:
                strPosX = !g_GameWork.config_0.optExtraViewMode_29 ? 210 : 200;
                Gfx_StringSetPosition(strPosX, STR_BASE_Y + (STR_OFFSET_Y * OptExtra_ViewMode));
                Gfx_StringDraw(SettingsExtraOptions_str[(g_GameWork.config_0.optExtraViewMode_29 ? 48 : 44) >> 2], 10);
                break;

            case OptExtra_BulletMult:
                Gfx_StringSetPosition(230, STR_BASE_Y + (STR_OFFSET_Y * OptExtra_BulletMult));
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
    if (g_MainMenu_SelectedIdx >= 4 && g_MainMenu_SelectedIdx < 9)
    {
        // Draw flashing left/right arrows.
        for (i = 0; i < 2; i++)
        {
            Gfx_Options_BlueArrowDraw(&flashArrows[(((g_MainMenu_SelectedIdx - 4) * 2) + i)], 1, 0);
        }

        // Draw border to highlight flashing left/right arrow corresponding to direction of UI navigation.
        if (g_Controller0->btnsHeld_C & ControllerFlag_LStickLeft)
        {
            Gfx_Options_BlueArrowDraw(&borderArrows[(g_MainMenu_SelectedIdx - 4) << 1], 0, 0);
        }
        if (g_Controller0->btnsHeld_C & ControllerFlag_LStickRight)
        {
            Gfx_Options_BlueArrowDraw(&borderArrows[((g_MainMenu_SelectedIdx - 4) << 1) + 1], 0, 0);
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
    #define OPT_SCREEN_POS_X_RANGE 11
    #define OPT_SCREEN_POS_Y_RANGE 8

    s32     i;
    s8      posX;
    TILE*   tile;
    PACKET* packet;

    posX = g_GameWorkConst->config_0.optScreenPosX_1C;
    if (posX != g_ScreenPos_PosX || g_GameWorkConst->config_0.optScreenPosY_1D != g_ScreenPos_PosY)
    {
        Settings_ScreenXYSet(posX, g_GameWorkConst->config_0.optScreenPosY_1D);
    }

    g_ScreenPos_PosX = g_GameWorkConst->config_0.optScreenPosX_1C;
    g_ScreenPos_PosY = g_GameWorkConst->config_0.optScreenPosY_1D;

    switch (g_GameWork.gameStateStep_598[1])
    {
        case ScreenPosMenuState_0:
            g_Gfx_ScreenFade                                = 6;
            g_Gfx_ScreenPos_InvertColorBg_TransitionCounter = 255;
            g_GameWork.gameStateStep_598[1]                 = ScreenPosMenuState_1;
            g_GameWork.gameStateStep_598[2]                 = 0;

        case ScreenPosMenuState_1:
            g_GameWork.gameStateStep_598[2] = 0;
            g_GameWork.gameStateStep_598[1]++;
            break;

        case ScreenPosMenuState_2:
            // Set config.
            if (g_Controller0->btnsPulsed_18 & ControllerFlag_LStickUp)
            {
                g_GameWorkConst->config_0.optScreenPosY_1D--;
            }
            if (g_Controller0->btnsPulsed_18 & ControllerFlag_LStickDown)
            {
                g_GameWorkConst->config_0.optScreenPosY_1D++;
            }
            if (g_Controller0->btnsPulsed_18 & ControllerFlag_LStickLeft)
            {
                g_GameWorkConst->config_0.optScreenPosX_1C--;
            }
            if (g_Controller0->btnsPulsed_18 & ControllerFlag_LStickRight)
            {
                g_GameWorkConst->config_0.optScreenPosX_1C++;
            }
            g_GameWorkConst->config_0.optScreenPosX_1C = CLAMP(g_GameWorkConst->config_0.optScreenPosX_1C, -OPT_SCREEN_POS_X_RANGE, OPT_SCREEN_POS_X_RANGE);
            g_GameWorkConst->config_0.optScreenPosY_1D = CLAMP(g_GameWorkConst->config_0.optScreenPosY_1D, -OPT_SCREEN_POS_Y_RANGE, OPT_SCREEN_POS_Y_RANGE);

            // Play sound.
            if (g_GameWorkConst->config_0.optScreenPosX_1C != g_ScreenPos_PosX ||
                g_GameWorkConst->config_0.optScreenPosY_1D != g_ScreenPos_PosY)
            {
                Sd_PlaySfx(Sfx_Back, 0, 64);
            }

            // Fade screen.
            if (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.enter_0)
            {
                if (g_Gfx_ScreenPos_InvertColorBg_TransitionCounter == 255)
                {
                    g_Gfx_ScreenPos_InvertColorBg_TransitionCounter = 0;
                    g_Gfx_ScreenPos_InvertColorBg                   = (g_Gfx_ScreenPos_InvertColorBg + 1) & (1 << 0);
                }
            }

            // Leave submenu.
            if (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.cancel_2)
            {
                Sd_PlaySfx(Sfx_Cancel, 0, 64);

                g_Gfx_ScreenFade                = 2;
                g_GameWork.gameStateStep_598[2] = 0;
                g_GameWork.gameStateStep_598[1]++;
            }
            break;

        case ScreenPosMenuState_Leave:
            // Switch to previous menu.
            if ((g_Gfx_ScreenFade & 0x7) == 5)
            {
                g_Gfx_ScreenFade                   = 6;
                g_GameWork.gameStateStep_598[0]    = OptMenuState_LeaveScreenPos;
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

    // Update fade.
    g_Gfx_ScreenPos_InvertColorBg_TransitionCounter += MENU_FADE_STEP;
    g_Gfx_ScreenPos_InvertColorBg_TransitionCounter  = CLAMP(g_Gfx_ScreenPos_InvertColorBg_TransitionCounter, 0, 255);
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
            setXY0(tile, -160, -97 + (96 * i));
            setWH(tile, 0x140, 2);
        }
        else
        {
            setXY0(tile, -577 + (144 * i), -120);
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
            setXY0(tile, -160, -81 + (16 * i));
            setWH(tile, 0x140, 2);
        }
        else
        {
            setXY0(tile, -305 + (16 * i), -120);
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
    #define DIR_COUNT 4

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

    u8  dirs[DIR_COUNT]; // Booleans.
    s32 i;

    // Clear directions array for no reason.
    memset(dirs, 0, DIR_COUNT);

    // Draw flashing up/down/left/right arrows.
    for (i = 0; i < DIR_COUNT; i++)
    {
        Gfx_Options_BlueArrowDraw(&flashArrows[i], 1, 0);
    }

    if ((g_Controller0->btnsClicked_10 & ControllerFlag_LStickUp) ||
        (g_Controller0->btnsHeld_C & ControllerFlag_LStickUp))
    {
        dirs[0] = true;
    }
    if ((g_Controller0->btnsClicked_10 & ControllerFlag_LStickDown) ||
        (g_Controller0->btnsHeld_C & ControllerFlag_LStickDown))
    {
        dirs[1] = true;
    }
    if ((g_Controller0->btnsClicked_10 & ControllerFlag_LStickLeft) ||
        (g_Controller0->btnsHeld_C & ControllerFlag_LStickLeft))
    {
        dirs[2] = true;
    }
    if ((g_Controller0->btnsClicked_10 & ControllerFlag_LStickRight) ||
        (g_Controller0->btnsHeld_C & ControllerFlag_LStickRight))
    {
        dirs[3] = true;
    }

    // Draw border to highlight flashing up/down/left/right arrow corresponding to direction of UI navigation.
    for (i = 0; i < DIR_COUNT; i++)
    {
        if (dirs[i])
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
    // Handle submenu state.
    switch (g_GameWork.gameStateStep_598[1])
    {
        case BrightnessMenuState_0:
            // Entry.
            g_GameWork.gameStateStep_598[1] = BrightnessMenuState_1;
            g_GameWork.gameStateStep_598[2] = 0;
            break;

        case BrightnessMenuState_1:
            // Set fade.
            g_Gfx_ScreenFade                = 6;
            g_GameWork.gameStateStep_598[1] = BrightnessMenuState_2;
            g_GameWork.gameStateStep_598[2] = 0;
            break;

        case BrightnessMenuState_2:
            // Set config.
            if (g_Controller0->btnsPulsed_18 & ControllerFlag_LStickLeft)
            {
                if (g_GameWork.config_0.optBrightness_22 != 0)
                {
                    g_GameWork.config_0.optBrightness_22--;
                    Sd_PlaySfx(Sfx_Back, 0, 64);
                }
            }
            if (g_Controller0->btnsPulsed_18 & ControllerFlag_LStickRight)
            {
                if (g_GameWork.config_0.optBrightness_22 < 7)
                {
                    g_GameWork.config_0.optBrightness_22++;
                    Sd_PlaySfx(Sfx_Back, 0, 64);
                }
            }

            // Fade screen and leave submenu.
            if (g_Controller0->btnsClicked_10 & (g_GameWorkPtr->config_0.controllerConfig_0.enter_0 |
                                                 g_GameWorkPtr->config_0.controllerConfig_0.cancel_2))
            {
                if (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.enter_0)
                {
                    Sd_PlaySfx(Sfx_Confirm, 0, 64);
                }
                else
                {
                    Sd_PlaySfx(Sfx_Cancel, 0, 64);
                }

                g_Gfx_ScreenFade                = 2;
                g_GameWork.gameStateStep_598[1]++;
                g_GameWork.gameStateStep_598[2] = 0;
            }
            break;

        case BrightnessMenuState_Leave:
            // Switch to previous menu.
            if (g_Gfx_ScreenFade & (1 << 2) &&
                !(g_Gfx_ScreenFade & (1 << 1)) &&
                g_Gfx_ScreenFade & (1 << 0))
            {
                g_Gfx_ScreenFade                   = 6;
                g_GameWork.gameStateStep_598[0]    = OptMenuState_LeaveBrightness;
                g_SysWork.timer_20                 = 0;
                g_GameWork.gameStateStep_598[1]    = 0;
                g_GameWork.gameStateStep_598[2]    = 0;
                g_GameWork.background2dColor_R_58C = 0;
                g_GameWork.background2dColor_G_58D = 0;
                g_GameWork.background2dColor_B_58E = 0;
            }
            break;
    }

    if (g_GameWork.gameStatePrev_590 == GameState_MainMenu)
    {
        Gfx_BackgroundSpriteDraw(&g_BrightnessScreenImg0);
    }
    else
    {
        Gfx_BackgroundSpriteDraw(&g_BrightnessScreenImg1);
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
    btnInput = g_Controller0->btnsHeld_C;
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

    // Draw border to highlight flashing left/right arrow corresponding to direction of UI navigation.
    for (i = dir - 1; i < dir; i++)
    {
        Gfx_Options_BlueArrowDraw(&borderArrows[i], 0, 0);
    }
}

// ========================================
// DRAW OPTIONS FEATURES SCREEN
// ========================================

void Gfx_LineDraw(s_Line2d* line, bool hasShadow, bool invertGradient) // 0x801E641C
{
    #define STR_OFFSET_Y 16

    s_Line2d* localLine;
    LINE_G2*  linePrim;
    POLY_G4*  poly;
    GsOT*     ot;

    ot        = &g_ObjectTable1[g_ObjectTableIdx];
    linePrim  = (LINE_G2*)GsOUT_PACKET_P;
    localLine = line;

    // Draw underline.
    setLineG2(linePrim);

    // @unused: Non-functioning line color gradient inversion? Gradient is unchanged regardless of `invertGradient`'s value,
    // which itself is always passed as `false`. Purpose is guessed based on a similar parameter in `Options_Selection_BulletPointDraw`.
    if (invertGradient)
    {
        setRGBC0(linePrim, 0xB0, 0xB0, 0xB0, 0x50);
        setRGBC1(linePrim, 0xA0, 0x80, 0x40, 0x50);
    }
    else
    {
        setRGBC0(linePrim, 0xB0, 0xB0, 0xB0, 0x50);
        setRGBC1(linePrim, 0xA0, 0x80, 0x40, 0x50);
    }

    setXY0Fast(linePrim, localLine->vertex0_0.vx, localLine->vertex0_0.vy);
    setXY1Fast(linePrim, localLine->vertex1_4.vx, localLine->vertex1_4.vy);
    addPrim((u8*)ot->org + (hasShadow ? 36 : 24), linePrim);
    GsOUT_PACKET_P = (u8*)linePrim + sizeof(LINE_G2);

    // Draw shadow gradient.
    // @unused: Though a line can be drawn independently without a shadow, `hasShadow` is always passed as `true`.
    if (hasShadow)
    {
        poly = (POLY_G4*)GsOUT_PACKET_P;
        setPolyG4(poly);
        setSemiTrans(poly, 1);
        setRGB0(poly, 0, 0, 0);
        setRGB1(poly, 0x60, 0x60, 0x60);
        setRGB2(poly, 0, 0, 0);
        setRGB3(poly, 0x60, 0x60, 0x60);
        setXY4(poly,
               localLine->vertex0_0.vx, localLine->vertex0_0.vy - STR_OFFSET_Y, localLine->vertex0_0.vx, localLine->vertex0_0.vy,
               localLine->vertex1_4.vx, localLine->vertex1_4.vy - STR_OFFSET_Y, localLine->vertex1_4.vx, localLine->vertex1_4.vy);
        addPrim((u8*)ot->org + 36, poly);
        GsOUT_PACKET_P = (u8*)poly + sizeof(POLY_G4);

        Gfx_Primitive2dTextureSet(0, 0, 9, 2);
    }
}

void Gfx_Options_BlueArrowDraw(s_Triangle2d* arrow, bool isFlashing, bool resetColor) // 0x801E662C
{
    s32      colorFade;
    s32      colorStart;
    s32      colorEnd;
    POLY_G3* arrowPoly;
    GsOT*    ot;
    
    ot = &g_ObjectTable1[g_ObjectTableIdx];

    // @unused: `resetColor` doesn't serve any meaningful purpose.
    if (resetColor)
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
    if (isFlashing)
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

void Gfx_ButtonDraw(s_Quad2d* quad, bool isCenter, bool invertGradient) // 0x801E67B0
{
    #define QUAD_COUNT 2

    GsOT*    ot = &g_ObjectTable1[g_ObjectTableIdx];
    s32      i;
    POLY_G3* poly;

    // Draw quads as triangles with diagonal gradient.
    for (i = 0; i < QUAD_COUNT; i++)
    {
        poly = (POLY_G3*)GsOUT_PACKET_P;
        setPolyG3(poly);

        // Center quad.
        if (isCenter)
        {
            // Set color.
            switch (invertGradient)
            {
                case false:
                    setRGBC0(poly, 0xFF, 0xFF, 0xFF, 0x30);
                    setRGBC1(poly, 0xA0, 0x80, 0x40, 0x30);
                    setRGBC2(poly, 0x40, 0x40, 0x40, 0x30);
                    break;

                case true:
                    setRGBC0(poly, 0x80, 0x80, 0x80, 0x30);
                    setRGBC1(poly, 0x28, 0x20, 0x10, 0x30);
                    setRGBC2(poly, 0x10, 0x10, 0x10, 0x30);
                    break;
            }

            // Draw triangle.
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
        // Backing quad.
        else
        {
            // Set color.
            switch (invertGradient)
            {
                case false:
                    setRGBC0(poly, 0xA0, 0x80, 0x40, 0x30);
                    setRGBC1(poly, 0xFF, 0xFF, 0xFF, 0x30);
                    setRGBC2(poly, 0xFF, 0xFF, 0xFF, 0x30);
                    break;

                case true:
                    setRGBC0(poly, 0x50, 0x40, 0x20, 0x30);
                    setRGBC1(poly, 0xA0, 0xA0, 0xA0, 0x30);
                    setRGBC2(poly, 0xA0, 0xA0, 0xA0, 0x30);
                    break;
            }

            // Draw triangle.
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

        addPrim((u8*)ot->org + 24, poly);
        GsOUT_PACKET_P = (u8*)poly + sizeof(POLY_G3);
    }
}

// ========================================
// CONTROLS OPTION SCREEN
// ========================================

void Settings_ControllerScreen() // 0x801E69BC
{
    s32           boundActionIdx = NO_VALUE;
    e_InputAction actionIdx;

    // Handle submenu state.
    switch (g_GameWork.gameStateStep_598[1])
    {
        case ContMenuState_Exit:
            g_Gfx_ScreenFade                         = 7;
            g_ScreenCtrl_SelectedElement.optionIdx_0 = ContMenuState_Exit;

            // Leave submenu.
            if (g_Controller0->btnsClicked_10 & (g_GameWorkPtr->config_0.controllerConfig_0.enter_0 |
                                                 g_GameWorkPtr->config_0.controllerConfig_0.cancel_2))
            {
                Sd_EngineCmd(Sfx_Cancel);

                g_Gfx_ScreenFade                = 3;
                g_GameWork.gameStateStep_598[1] = ContMenuState_Leave;
                g_GameWork.gameStateStep_598[2] = 0;
                break;
            }

            // Move selection cursor up/down.
            if (g_Controller0->btnsPulsedGui_1C & ControllerFlag_LStickUp)
            {
                g_GameWork.gameStateStep_598[1] = ContMenuState_Type3;
                g_GameWork.gameStateStep_598[2] = 0;
            }
            else if (g_Controller0->btnsPulsedGui_1C & ControllerFlag_LStickDown)
            {
                g_GameWork.gameStateStep_598[1] = ContMenuState_Type1;
                g_GameWork.gameStateStep_598[2] = 0;
            }
            // Move selection cursor left/right.
            else if (g_Controller0->btnsPulsedGui_1C & (ControllerFlag_LStickLeft | ControllerFlag_LStickRight))
            {
                g_GameWork.gameStateStep_598[1] = ContMenuState_Actions;
                g_GameWork.gameStateStep_598[2] = 0;
            }
            break;

        case ContMenuState_Type1:
        case ContMenuState_Type2:
        case ContMenuState_Type3:
            g_ScreenCtrl_SelectedElement.optionIdx_0 = g_GameWork.gameStateStep_598[1];

            // Set binding preset.
            if (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.enter_0)
            {
                Sd_EngineCmd(Sfx_Confirm);
                Settings_RestoreControlDefaults(g_GameWork.gameStateStep_598[1] - 1);
            }
            // Reset selection cursor.
            else if (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.cancel_2)
            {
                Sd_EngineCmd(Sfx_Cancel);
                g_GameWork.gameStateStep_598[1] = ContMenuState_Exit;
                g_GameWork.gameStateStep_598[2] = 0;
            }
            // Move selection cursor.
            else
            {
                // Move selection cursor up/down.
                if (g_Controller0->btnsPulsedGui_1C & ControllerFlag_LStickUp)
                {
                    g_GameWork.gameStateStep_598[1] = (g_GameWork.gameStateStep_598[1] - 1) & 0x3;
                    g_GameWork.gameStateStep_598[2] = 0;
                }
                else if (g_Controller0->btnsPulsedGui_1C & ControllerFlag_LStickDown)
                {
                    g_GameWork.gameStateStep_598[1] = (g_GameWork.gameStateStep_598[1] + 1) & 0x3;
                    g_GameWork.gameStateStep_598[2] = 0;
                }
                // Move selection cursor left/right.
                else if (g_Controller0->btnsPulsedGui_1C & (ControllerFlag_LStickLeft | ControllerFlag_LStickRight))
                {
                    g_GameWork.gameStateStep_598[1] = ContMenuState_Actions;
                    g_GameWork.gameStateStep_598[2] = 0;
                }
            }
            break;

        case ContMenuState_Actions:
            actionIdx = g_ScreenCtrl_SelectedElement.actionIdx_4;

            // Move selection cursor up/down.
            if (g_Controller0->btnsPulsedGui_1C & ControllerFlag_LStickUp)
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
            else if (g_Controller0->btnsPulsedGui_1C & ControllerFlag_LStickDown)
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
            // Move selection cursor left/right.
            else if (g_Controller0->btnsPulsedGui_1C & (ControllerFlag_LStickLeft | ControllerFlag_LStickRight))
            {
                g_GameWork.gameStateStep_598[2] = 0;
                g_GameWork.gameStateStep_598[1] = g_ScreenCtrl_SelectedElement.optionIdx_0;
            }
            // Bind button to input action.
            else
            {
                boundActionIdx = Settings_ButtonChange(actionIdx);
            }
            break;

        case ContMenuState_Leave:
            // Switch to previous menu.
            if ((g_Gfx_ScreenFade & 0x7) == 5)
            {
                g_Gfx_ScreenFade                = 6;
                g_GameWork.gameStateStep_598[0] = OptMenuState_LeaveController;
                g_SysWork.timer_20              = 0;
                g_GameWork.gameStateStep_598[1] = 0;
                g_GameWork.gameStateStep_598[2] = 0;
            }
            break;
    }

    if (g_GameWork.gameStateStep_598[1] == ContMenuState_Actions)
    {
        g_ControllerSubmenu_IsOnActionColumn = true;
    }
    else
    {
        g_ControllerSubmenu_IsOnActionColumn = false;
    }

    // Play cursor navigation SFX.
    if (g_Controller0->btnsPulsedGui_1C & (ControllerFlag_LStickUp | ControllerFlag_LStickRight | ControllerFlag_LStickDown | ControllerFlag_LStickLeft))
    {
        Sd_EngineCmd(Sfx_Back);
    }

    // Draw submenu graphics.
    Gfx_ControllerScreenDraw(g_ControllerSubmenu_IsOnActionColumn, g_ScreenCtrl_SelectedElement.optionIdx_0, g_ScreenCtrl_SelectedElement.actionIdx_4, boundActionIdx);
}

s32 Settings_ButtonChange(s32 actionIdx) // 0x801E6CF4
{
    u16* bindings;
    u16  boundBtnFlag;
    u16  btnFlag;
    s32  curActionIdx;
    s32  boundActionIdx;
    s32  i;
    u32  j;

    boundActionIdx = NO_VALUE;
    bindings       = (u16*)&g_GameWorkPtr->config_0.controllerConfig_0;

    // Run through all controller flags, excluding stick axes.
    for (i = 0; i < 16; i++)
    {
        btnFlag = 1 << i;

        if ((btnFlag & (ControllerFlag_DpadUp | ControllerFlag_DpadRight | ControllerFlag_DpadDown | ControllerFlag_DpadLeft)) ||
            !(btnFlag & g_Controller0->btnsClicked_10))
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
                boundActionIdx = actionIdx;
                Sd_EngineCmd(Sfx_Denied);
            }
            else
            {
                bindings[actionIdx] &= ~btnFlag;
                Sd_EngineCmd(Sfx_Confirm);
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
                            boundActionIdx = curActionIdx;
                            Sd_EngineCmd(Sfx_Denied);
                        }
                        else
                        {
                            bindings[curActionIdx] &= ~btnFlag;
                            bindings[actionIdx]    |= btnFlag;
                            Sd_EngineCmd(Sfx_Confirm);
                        }
                    }
                    else
                    {
                        bindings[actionIdx] = boundBtnFlag | btnFlag;
                        Sd_EngineCmd(Sfx_Confirm);
                    }
                    break;

                case 2:
                    bindings[InputAction_Skip] |= btnFlag;
                    Sd_EngineCmd(Sfx_Confirm);
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
                            Sd_EngineCmd(Sfx_Denied);
                            boundActionIdx = curActionIdx;
                        }
                        else
                        {
                            bindings[curActionIdx] &= ~btnFlag;
                            bindings[actionIdx]    |= btnFlag;
                            Sd_EngineCmd(Sfx_Confirm);
                        }
                    }
                    else
                    {
                        bindings[actionIdx] |= btnFlag;
                        Sd_EngineCmd(Sfx_Confirm);
                    }
                    break;
            }
        }
    }

    return boundActionIdx;
}

DR_MODE D_801E730C[2] =
{
    {
        .tag  = 0x03000000,
        .code = { 0xE1000200, 0 }
    },
    {
        .tag  = 0x03000000,
        .code = { 0xE1000200, 0 }
    }
};

POLY_G4 D_801E7324[2] =
{
    {
        .tag = 0x08000000,
        .r0   = 0xFF,
        .g0   = 0xFF,
        .b0   = 0xFF,
        .code = 0x3A,
        .r3   = 0xFF,
        .g3   = 0xFF,
        .b3   = 0xFF
    },
    {
        .tag  = 0x08000000,
        .code = 0x3A,
        .r1   = 0xFF,
        .g1   = 0xFF,
        .b1   = 0xFF,
        .r2   = 0xFF,
        .g2   = 0xFF,
        .b2   = 0xFF
    },
};

char* g_ControllerSubmenu_OptionStrings[] =
{
    "EXIT",
    "TYPE_1",
    "TYPE_2",
    "TYPE_3"
};

char* g_ControllerSubmenu_ActionStrings[] =
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

/** Unknown .rodata values.
 * The types are assumed. It is unknown where
 * are this applied, they could be also some
 * sort of value defined with an macro.
 */
static const u16 D_801E2D42 = 4160;

DVECTOR g_Options_Extra_SelectionHighlightFrom_Unused = { 0, 0 };

DVECTOR g_Options_Extra_SelectionHighlightTo_Unused = { 0, 0 };

DVECTOR g_Options_Main_SelectionHighlightFrom_Unused = { 0, 0 };

DVECTOR g_Options_Main_SelectionHighlightTo_Unused = { 0, 0 };

DVECTOR g_Options_Extra_SelectionHighlightFrom = { 0, 0 };

DVECTOR g_Options_Extra_SelectionHighlightTo = { 0, 0 };

DVECTOR g_Options_Main_SelectionHighlightFrom = { 0, 0 };

DVECTOR g_Options_Main_SelectionHighlightTo = { 0, 0 };

s32 g_Gfx_ScreenPos_InvertColorBg_TransitionCounter = 0;

s16 g_ScreenPos_PosX = 0;

s16 g_ScreenPos_PosY = 0;

s_ScreenCtrl_SelectedElement g_ScreenCtrl_SelectedElement = { ContMenuState_Exit, InputAction_Enter };

s32 g_Options_SelectionCursorTimer = 0;

s32 g_OptExtra_ShowSettingsCount = 0;

s32 g_OptExtra_BloodColorSelected = 0;

s32 g_OptExtra_BulletMultLimit = 0;

void Gfx_ControllerScreenDraw(bool isOnActionColumn, s32 optionIdx, s32 actionIdx, s32 boundActionIdx) // 0x801E6F60
{
    #define STR_BASE_Y    22
    #define STR_OFFSET_Y  20
    #define ICON_SIZE_Y   12
    #define ICON_OFFSET_X -12

    s16      y0;
    s16      y1;
    s32      strYPos;
    s32      i;
    u16*     contConfig;
    DR_MODE* drMode;
    POLY_G4* poly;
    GsOT*    ot;

    ot     = (GsOT*)((g_ObjectTableIdx << 6) + (u8*)&D_800B5C7C);
    poly   = &D_801E7324[g_ObjectTableIdx];
    drMode = &D_801E730C[g_ObjectTableIdx];

    // Draw selection strings.
    for (i = 0; i < ContMenuState_Count; i++)
    {
        Gfx_StringSetPosition(24, STR_BASE_Y + (i * STR_OFFSET_Y));
        Gfx_StringDraw(g_ControllerSubmenu_OptionStrings[i], 20);
    }

    if (!isOnActionColumn)
    {
        y1 = optionIdx * STR_OFFSET_Y;
        y0 = y1 - 91;
        setXY4(poly,
               -137, y0,
               -76,  y0,
               -137, y1 - 76,
               -76,  y1 - 76);
    }

    strYPos = STR_BASE_Y;
    y0      = -300;

    // Draw controller bindings.
    for (i = 0, contConfig = (u16*)&g_GameWorkPtr->config_0.controllerConfig_0; i < (u32)InputAction_Count; i++, contConfig++)
    {
        // Draw action string.
        Gfx_DebugStringPosition(96, strYPos);
        Gfx_DebugStringDraw(g_ControllerSubmenu_ActionStrings[i]);

        // Draw button icon.
        if (i != boundActionIdx)
        {
            Gfx_ControllerButtonsDraw(ICON_OFFSET_X, strYPos - 114, *contConfig);
        }

        if (i == actionIdx)
        {
            y0 = strYPos - 113;
        }

        strYPos = (strYPos + ICON_SIZE_Y) + ((i == 2) ? ICON_SIZE_Y : 0);
    }

    if (isOnActionColumn == true)
    {
        setXY4(poly,
               -65, y0,
               -15, y0,
               -65, y0 + 10,
               -15, y0 + 10);
    }

    AddPrim(ot, poly);
    AddPrim(ot, drMode);
}

void Gfx_ControllerButtonsDraw(s32 baseX, s32 baseY, u16 contConfig) // 0x801E716C
{
    #define ICON_SIZE_X   12
    #define ICON_SIZE_Y   12
    #define ICON_OFFSET_X 14

    s32            i;
    s32            posX;
    u16            clutX;
    u32            clutY;
    int            temp;
    int            v0;
    GsOT*          ot;
    SPRT*          prim;
    DR_TPAGE*      tpage;
    PACKET*        packet;
    s_FsImageDesc* image = &g_ControllerButtonAtlasImg;

    ot     = &D_800B5D04[g_ObjectTableIdx];
    packet = GsOUT_PACKET_P;

    // Draw button sprites.
    for (posX = baseX, i = ICON_SIZE_X; i < 28; i++)
    {
        temp = i & 0xF;
        v0   = ((temp + 8) & 0xF) << 4;

        if ((contConfig >> temp) & (1 << 0))
        {
            prim = (SPRT*)packet;
            addPrimFast(ot, prim, 4);
            setCodeWord(prim, PRIM_RECT | RECT_TEXTURE, 0x808080);
            setWH(prim, ICON_SIZE_X, ICON_SIZE_Y);

            clutY = image->clutY;
            clutX = image->clutX;

            setXY0Fast(prim, posX, baseY);
            posX += ICON_OFFSET_X;

            // setUV0AndClut(prim, 0xF4, v0, clutY, clutX);
            *(u32*)(&prim->u0) = 244 + (v0 << 8) + (((clutY << 6) | ((clutX >> 4) & 0x3F)) << 16);

            packet = (u8*)prim + sizeof(SPRT);
            tpage  = (DR_TPAGE*)packet;

            setDrawTPage(tpage, 0, 1, 7);
            AddPrim(ot, tpage);
            packet = (u8*)tpage + sizeof(DR_TPAGE);
        }
    }

    GsOUT_PACKET_P = packet;
}
