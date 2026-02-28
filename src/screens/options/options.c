#include "game.h"

#include <memory.h>
#include <psyq/libetc.h>

#include "bodyprog/bodyprog.h"
#include "bodyprog/item_screens.h"
#include "bodyprog/math/math.h"
#include "bodyprog/screen/screen_data.h"
#include "bodyprog/screen/screen_draw.h"
#include "bodyprog/sound_system.h"
#include "bodyprog/text/text_debug_draw.h"
#include "bodyprog/text/text_draw.h"
#include "screens/options.h"
#include "screens/stream/stream.h"

#define LINE_CURSOR_TIMER_MAX 8

#define LAYER_24   24
#define LAYER_40   40
#define LAYER_36   36
#define LAYER_8148 8148

s32  g_MainOptionsMenu_SelectedEntry      = 0;
s32  g_ExtraOptionsMenu_SelectedEntry     = 0;
s32  g_MainOptionsMenu_PrevSelectedEntry  = 0;
s32  g_ExtraOptionsMenu_PrevSelectedEntry = 0;
bool g_ScreenPosMenu_InvertBackgroundFade = false;
bool g_ControllerMenu_IsOnActionsPane     = false;

/** @brief Tracks movement time of the cursor highlight. */
static s32 g_Options_SelectionHighlightTimer;
/** @brief Number of options to show in the extra options screen. Shows extra unlockable settings if they are unlocked. */
static s32 g_ExtraOptionsMenu_EntryCount;
static s32 g_ExtraOptionsMenu_SelectedBloodColorEntry;
static s32 g_ExtraOptionsMenu_BulletMultMax;

// ========================================
// MAIN AND EXTRA OPTION SCREEN
// ========================================

void GameState_Options_Update(void) // 0x801E2D44
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
        case OptionsMenuState_EnterMainOptions:
            DrawSync(SyncMode_Wait);

            if (g_GameWork.gameStatePrev_590 != GameState_InGame)
            {
                VSync(SyncMode_Wait8);
            }

            g_GameWork.background2dColor_58C.r = 0;
            g_GameWork.background2dColor_58C.g = 0;
            g_GameWork.background2dColor_58C.b = 0;

            ScreenFade_Start(false, true, false);
            g_IntervalVBlanks   = 1;

            if (g_GameWork.gameStatePrev_590 == GameState_InGame)
            {
                Game_RadioSoundStop();
            }

            g_MainOptionsMenu_SelectedEntry      = MainOptionsMenuEntry_Exit;
            g_MainOptionsMenu_PrevSelectedEntry  = 0;
            g_ExtraOptionsMenu_SelectedEntry     = 0;
            g_ExtraOptionsMenu_PrevSelectedEntry = 0;
            g_Options_SelectionHighlightTimer    = 0;
            g_ExtraOptionsMenu_BulletMultMax     = 1;
            unlockedOptFlags                     = g_GameWork.config_0.optExtraOptionsEnabled_27;

            // Set available bullet multiplier.
            for (i = 0; i < 5; i++)
            {
                if (unlockedOptFlags & (1 << i))
                {
                    g_ExtraOptionsMenu_BulletMultMax++;
                }
            }

            // Set selected blood color.
            switch (g_GameWork.config_0.optExtraBloodColor_24)
            {
                case BloodColor_Normal:
                    g_ExtraOptionsMenu_SelectedBloodColorEntry = BloodColorMenuEntry_Normal;
                    break;

                case BloodColor_Green:
                    g_ExtraOptionsMenu_SelectedBloodColorEntry = BloodColorMenuEntry_Green;
                    break;

                case BloodColor_Violet:
                    g_ExtraOptionsMenu_SelectedBloodColorEntry = BloodColorMenuEntry_Violet;
                    break;

                case BloodColor_Black:
                    g_ExtraOptionsMenu_SelectedBloodColorEntry = BloodColorMenuEntry_Black;
                    break;
            }

            g_ExtraOptionsMenu_EntryCount   = (g_GameWork.config_0.optExtraOptionsEnabled_27) ? 8 : 6;
            g_GameWork.gameStateStep_598[0] = OptionsMenuState_MainOptions;
            g_SysWork.counters_1C[1]              = 0;
            g_GameWork.gameStateStep_598[1] = 0;
            g_GameWork.gameStateStep_598[2] = 0;
            break;

        case OptionsMenuState_LeaveScreenPos:
        case OptionsMenuState_LeaveBrightness:
        case OptionsMenuState_LeaveController:
            g_GameWork.gameStateStep_598[0] = OptionsMenuState_MainOptions;
            g_SysWork.counters_1C[1]              = 0;
            g_GameWork.gameStateStep_598[1] = 0;
            g_GameWork.gameStateStep_598[2] = 0;
            break;

        case OptionsMenuState_EnterScreenPos:
            if (ScreenFade_IsFinished())
            {
                g_GameWork.gameStateStep_598[0] = OptionsMenuState_ScreenPos;
                g_SysWork.counters_1C[1]              = 0;
                g_GameWork.gameStateStep_598[1] = 0;
                g_GameWork.gameStateStep_598[2] = 0;
            }
            break;

        case OptionsMenuState_ScreenPos:
            Options_ScreenPosMenu_Control();
            break;

        case OptionsMenuState_EnterBrightness:
            if (ScreenFade_IsFinished())
            {
                Fs_QueueWaitForEmpty();

                g_GameWork.gameStateStep_598[0] = OptionsMenuState_Brightness;
                g_GameWork.gameStateStep_598[0] = OptionsMenuState_Brightness;
                g_SysWork.counters_1C[1]              = 0;
                g_GameWork.gameStateStep_598[1] = 0;
                g_GameWork.gameStateStep_598[2] = 0;
            }
            break;

        case OptionsMenuState_Brightness:
            Options_BrightnessMenu_Control();
            break;

        case OptionsMenuState_EnterController:
            // Switch to controller binding menu.
            if (ScreenFade_IsFinished())
            {
                g_GameWork.gameStateStep_598[0] = OptionsMenuState_Controller;
                g_GameWork.gameStateStep_598[0] = OptionsMenuState_Controller;
                g_SysWork.counters_1C[1]              = 0;
                g_GameWork.gameStateStep_598[1] = 0;
                g_GameWork.gameStateStep_598[2] = 0;
            }
            break;

        case OptionsMenuState_Controller:
            Options_ControllerMenu_Control();
            break;

        case OptionsMenuState_Leave:
            ScreenFade_Start(true, false, false);
            g_GameWork.gameStateStep_598[0] = OptionsMenuState_LeaveMainOptions;
            g_SysWork.counters_1C[1]              = 0;
            g_GameWork.gameStateStep_598[1] = 0;
            g_GameWork.gameStateStep_598[2] = 0;
            break;

        case OptionsMenuState_LeaveMainOptions:
            if (ScreenFade_IsFinished())
            {
                // TODO: Likely `Game_StateSetPrevious` inline, but `gameState_594`/`gameStatePrev_590` loads inside are switched?

                e_GameState prevGameState = g_GameWork.gameStatePrev_590;
                e_GameState gameState     = g_GameWork.gameState_594;

                g_SysWork.counters_1C[0]              = 0;
                g_SysWork.counters_1C[1]              = 0;
                g_GameWork.gameStateStep_598[1] = 0;
                g_GameWork.gameStateStep_598[2] = 0;

                SysWork_StateSetNext(SysState_Gameplay);

                g_GameWork.gameStateStep_598[0] = gameState;
                g_GameWork.gameState_594        = prevGameState;
                g_GameWork.gameStatePrev_590    = gameState;
                g_GameWork.gameStateStep_598[0] = OptionsMenuState_EnterMainOptions;
            }

            break;

        case OptionsMenuState_EnterExtraOptions:
            if (ScreenFade_IsFinished())
            {
                g_GameWork.gameStateStep_598[0]   = OptionsMenuState_ExtraOptions;
                g_SysWork.counters_1C[1]                = 0;
                ScreenFade_Start(false, true, false);
                g_GameWork.gameStateStep_598[1]   = 0;
                g_GameWork.gameStateStep_598[2]   = 0;
                g_Options_SelectionHighlightTimer = 0;
            }
            break;

        case OptionsMenuState_LeaveExtraOptions:
            if (ScreenFade_IsFinished())
            {
                g_GameWork.gameStateStep_598[0] = OptionsMenuState_EnterMainOptions;
                g_SysWork.counters_1C[1]              = 0;
                g_GameWork.gameStateStep_598[1] = 0;
                g_GameWork.gameStateStep_598[2] = 0;
                ScreenFade_Start(false, true, false);
            }
            break;
    }

    // Handle menu state.
    switch (g_GameWork.gameStateStep_598[0])
    {
        case OptionsMenuState_MainOptions:
        case OptionsMenuState_Leave:
        case OptionsMenuState_LeaveMainOptions:
        case OptionsMenuState_EnterScreenPos:
        case OptionsMenuState_EnterBrightness:
        case OptionsMenuState_EnterController:
        case OptionsMenuState_EnterExtraOptions:
            Options_MainOptionsMenu_Control();
            break;

        case OptionsMenuState_ExtraOptions:
        case OptionsMenuState_LeaveExtraOptions:
            Options_ExtraOptionsMenu_Control();
            break;
    }
}

void Options_ExtraOptionsMenu_Control(void) // 0x801E318C
{
    Options_ExtraOptionsMenu_EntryStringsDraw();
    Options_ExtraOptionsMenu_ConfigDraw();
    Options_ExtraOptionsMenu_SelectionHighlightDraw();
    Options_Menu_VignetteDraw();
    Screen_BackgroundImgDraw(&g_ItemInspectionImg);

    if (g_GameWork.gameStateStep_598[0] != OptionsMenuState_ExtraOptions)
    {
        return;
    }

    // Increment line move timer.
    if ((LINE_CURSOR_TIMER_MAX - 1) < g_Options_SelectionHighlightTimer)
    {
        g_Options_SelectionHighlightTimer = LINE_CURSOR_TIMER_MAX;
    }
    else
    {
        g_Options_SelectionHighlightTimer++;
    }

    if (g_Options_SelectionHighlightTimer == LINE_CURSOR_TIMER_MAX)
    {
        g_ExtraOptionsMenu_PrevSelectedEntry = g_ExtraOptionsMenu_SelectedEntry;

        // Leave to gameplay (if options menu was accessed with `Option` input action).
        if (g_GameWork.gameStatePrev_590 == GameState_InGame &&
            !(g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.enter_0) &&
            (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.option_1A))
        {
            Sd_PlaySfx(Sfx_MenuCancel, 0, 64);

            g_GameWork.gameStateStep_598[0] = OptionsMenuState_Leave;
            g_SysWork.counters_1C[1]              = 0;
            g_GameWork.gameStateStep_598[1] = 0;
            g_GameWork.gameStateStep_598[2] = 0;
            return;
        }

        // Move selection cursor up/down.
        if (g_Controller0->btnsPulsed_18 & ControllerFlag_LStickUp)
        {
            s32 var = 1;
            Sd_PlaySfx(Sfx_MenuMove, 0, 64);
            g_ExtraOptionsMenu_SelectedEntry  = ((g_ExtraOptionsMenu_SelectedEntry - var) + g_ExtraOptionsMenu_EntryCount) % g_ExtraOptionsMenu_EntryCount;
            g_Options_SelectionHighlightTimer = 0;
        }
        if (g_Controller0->btnsPulsed_18 & ControllerFlag_LStickDown)
        {
            Sd_PlaySfx(Sfx_MenuMove, 0, 64);
            g_ExtraOptionsMenu_SelectedEntry++;
            g_ExtraOptionsMenu_SelectedEntry  = g_ExtraOptionsMenu_SelectedEntry % g_ExtraOptionsMenu_EntryCount;
            g_Options_SelectionHighlightTimer = 0;
        }

        // Handle config change.
        switch (g_ExtraOptionsMenu_SelectedEntry)
        {
            case ExtraOptionsMenuEntry_WeaponCtrl:
                // Scroll left/right.
                if (g_Controller0->btnsClicked_10 & (ControllerFlag_LStickRight | ControllerFlag_LStickLeft))
                {
                    Sd_PlaySfx(Sfx_MenuMove, 0, 64);
                    g_GameWork.config_0.optExtraWeaponCtrl_23 = !g_GameWork.config_0.optExtraWeaponCtrl_23;
                }
                break;

            case ExtraOptionsMenuEntry_Blood:
                // Scroll left/right.
                if (g_Controller0->btnsClicked_10 & ControllerFlag_LStickRight)
                {
                    Sd_PlaySfx(Sfx_MenuMove, 0, 64);
                    g_ExtraOptionsMenu_SelectedBloodColorEntry++;
                }
                if (g_Controller0->btnsClicked_10 & ControllerFlag_LStickLeft)
                {
                    Sd_PlaySfx(Sfx_MenuMove, 0, 64);
                    g_ExtraOptionsMenu_SelectedBloodColorEntry += 3;
                }

                // Set config.
                g_ExtraOptionsMenu_SelectedBloodColorEntry = g_ExtraOptionsMenu_SelectedBloodColorEntry % BloodColorMenuEntry_Count;
                switch (g_ExtraOptionsMenu_SelectedBloodColorEntry)
                {
                    case BloodColorMenuEntry_Normal:
                        g_GameWork.config_0.optExtraBloodColor_24 = BloodColor_Normal;
                        break;

                    case BloodColorMenuEntry_Green:
                        g_GameWork.config_0.optExtraBloodColor_24 = BloodColor_Green;
                        break;

                    case BloodColorMenuEntry_Violet:
                        g_GameWork.config_0.optExtraBloodColor_24 = BloodColor_Violet;
                        break;

                    case BloodColorMenuEntry_Black:
                        g_GameWork.config_0.optExtraBloodColor_24 = BloodColor_Black;
                        break;
                }
                break;

            case ExtraOptionsMenuEntry_ViewCtrl:
                // Scroll left/right.
                if (g_Controller0->btnsClicked_10 & (ControllerFlag_LStickRight | ControllerFlag_LStickLeft))
                {
                    Sd_PlaySfx(Sfx_MenuMove, 0, 64);

                    // Set config.
                    g_GameWork.config_0.optExtraViewCtrl_28 = !g_GameWork.config_0.optExtraViewCtrl_28;
                }
                break;

            case ExtraOptionsMenuEntry_RetreatTurn:
                // Scroll left/right.
                if (g_Controller0->btnsClicked_10 & (ControllerFlag_LStickRight | ControllerFlag_LStickLeft))
                {
                    Sd_PlaySfx(Sfx_MenuMove, 0, 64);

                    // Set config.
                    g_GameWork.config_0.optExtraRetreatTurn_2A = (s8)g_GameWork.config_0.optExtraRetreatTurn_2A == 0;
                }
                break;

            case ExtraOptionsMenuEntry_MovementCtrl:
                // Scroll left/right.
                if (g_Controller0->btnsClicked_10 & (ControllerFlag_LStickRight | ControllerFlag_LStickLeft))
                {
                    Sd_PlaySfx(Sfx_MenuMove, 0, 64);

                    // Set config.
                    g_GameWork.config_0.optExtraWalkRunCtrl_2B = (s8)g_GameWork.config_0.optExtraWalkRunCtrl_2B == 0;
                }
                break;

            case ExtraOptionsMenuEntry_AutoAiming:
                // Scroll left/right.
                if (g_Controller0->btnsClicked_10 & (ControllerFlag_LStickRight | ControllerFlag_LStickLeft))
                {
                    Sd_PlaySfx(Sfx_MenuMove, 0, 64);

                    // Set config.
                    g_GameWork.config_0.optExtraAutoAiming_2C = (s8)g_GameWork.config_0.optExtraAutoAiming_2C == 0;
                }
                break;

            case ExtraOptionsMenuEntry_ViewMode:
                // Scroll left/right.
                if (g_Controller0->btnsClicked_10 & (ControllerFlag_LStickRight | ControllerFlag_LStickLeft))
                {
                    Sd_PlaySfx(Sfx_MenuMove, 0, 64);

                    // Set config.
                    g_GameWork.config_0.optExtraViewMode_29 = !g_GameWork.config_0.optExtraViewMode_29;
                }
                break;

            case ExtraOptionsMenuEntry_BulletMult:
                // Scroll left/right.
                if (g_Controller0->btnsClicked_10 & ControllerFlag_LStickRight)
                {
                    Sd_PlaySfx(Sfx_MenuMove, 0, 64);

                    // Set config.
                    g_GameWork.config_0.optExtraBulletAdjust_2D++;
                }
                if (g_Controller0->btnsClicked_10 & ControllerFlag_LStickLeft)
                {
                    Sd_PlaySfx(Sfx_MenuMove, 0, 64);

                    // Set config.
                    g_GameWork.config_0.optExtraBulletAdjust_2D = g_GameWork.config_0.optExtraBulletAdjust_2D + (g_ExtraOptionsMenu_BulletMultMax - 1);
                }
                g_GameWork.config_0.optExtraBulletAdjust_2D = g_GameWork.config_0.optExtraBulletAdjust_2D % g_ExtraOptionsMenu_BulletMultMax;
                break;
        }
    }

    // Leave menu.
    if ((g_Controller0->btnsClicked_10 & (g_GameWorkPtr->config_0.controllerConfig_0.cancel_2 |
                                          (ControllerFlag_L2 | ControllerFlag_R2 | ControllerFlag_L1 | ControllerFlag_R1))) &&
        g_GameWork.gameStateStep_598[0] != OptionsMenuState_LeaveExtraOptions)
    {
        if (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.cancel_2)
        {
            Sd_PlaySfx(Sfx_MenuCancel, 0, 64);
        }
        else
        {
            Sd_PlaySfx(Sfx_MenuConfirm, 0, 64);
        }

        ScreenFade_Start(true, false, false);
        g_GameWork.gameStateStep_598[0] = OptionsMenuState_LeaveExtraOptions;
        g_SysWork.counters_1C[1]              = 0;
        g_GameWork.gameStateStep_598[1] = 0;
        g_GameWork.gameStateStep_598[2] = 0;
    }
}

void Options_MainOptionsMenu_Control(void) // 0x801E3770
{
    #define SOUND_VOL_STEP 8

    s32 audioType;
    s32 vol;

    // Draw graphics.
    Options_MainOptionsMenu_EntryStringsDraw();
    Options_MainOptionsMenu_ConfigDraw();
    Options_MainOptionsMenu_SelectionHighlightDraw();
    Options_Menu_VignetteDraw();
    Screen_BackgroundImgDraw(&g_ItemInspectionImg);
    Options_MainOptionsMenu_BgmVolumeBarDraw();
    Options_MainOptionsMenu_SfxVolumeBarDraw();

    if (g_GameWork.gameStateStep_598[0] != OptionsMenuState_MainOptions)
    {
        return;
    }

    // Increment line move timer.
    if ((LINE_CURSOR_TIMER_MAX - 1) < g_Options_SelectionHighlightTimer)
    {
        g_Options_SelectionHighlightTimer = LINE_CURSOR_TIMER_MAX;
    }
    else
    {
        g_Options_SelectionHighlightTimer++;
    }

    if (g_Options_SelectionHighlightTimer != LINE_CURSOR_TIMER_MAX)
    {
        return;
    }

    g_MainOptionsMenu_PrevSelectedEntry = g_MainOptionsMenu_SelectedEntry;

    // Leave to gameplay (if options menu was accessed with `Option` input action).
    if (g_GameWork.gameStatePrev_590 == GameState_InGame &&
        !(g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.enter_0) &&
        (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.option_1A))
    {
        Sd_PlaySfx(Sfx_MenuCancel, 0, 64);

        g_GameWork.gameStateStep_598[0] = OptionsMenuState_Leave;
        g_SysWork.counters_1C[1]              = 0;
        g_GameWork.gameStateStep_598[1] = 0;
        g_GameWork.gameStateStep_598[2] = 0;
        return;
    }

    // Move selection cursor up/down.
    if (g_Controller0->btnsPulsed_18 & ControllerFlag_LStickUp)
    {
        Sd_PlaySfx(Sfx_MenuMove, 0, 64);

        g_Options_SelectionHighlightTimer = 0;
        g_MainOptionsMenu_SelectedEntry   = (g_MainOptionsMenu_SelectedEntry + (MainOptionsMenuEntry_Count - 1)) % MainOptionsMenuEntry_Count;
    }
    if (g_Controller0->btnsPulsed_18 & ControllerFlag_LStickDown)
    {
        Sd_PlaySfx(Sfx_MenuMove, 0, 64);

        g_Options_SelectionHighlightTimer = 0;
        g_MainOptionsMenu_SelectedEntry   = (g_MainOptionsMenu_SelectedEntry + 1) % MainOptionsMenuEntry_Count;
    }

    // Handle config change.
    switch (g_MainOptionsMenu_SelectedEntry)
    {
        case MainOptionsMenuEntry_Exit:
            // Exit menu to gameplay.
            if (g_Controller0->btnsClicked_10 & (g_GameWorkPtr->config_0.controllerConfig_0.enter_0 |
                                                 g_GameWorkPtr->config_0.controllerConfig_0.cancel_2))
            {
                Sd_PlaySfx(Sfx_MenuCancel, 0, 64);

                g_GameWork.gameStateStep_598[0] = OptionsMenuState_Leave;
                g_SysWork.counters_1C[1]              = 0;
                g_GameWork.gameStateStep_598[1] = 0;
                g_GameWork.gameStateStep_598[2] = 0;
            }
            break;

        case MainOptionsMenuEntry_Controller:
            // Enter controller screen.
            if (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.enter_0)
            {
                Sd_PlaySfx(Sfx_MenuConfirm, 0, 64);
                Fs_QueueStartReadTim(FILE_TIM_OPTION2_TIM, IMAGE_BUFFER_3, &g_ControllerButtonAtlasImg);

                ScreenFade_Start(true, false, false);
                g_GameWork.gameStateStep_598[0] = OptionsMenuState_EnterController;
                g_SysWork.counters_1C[1]              = 0;
                g_GameWork.gameStateStep_598[1] = 0;
                g_GameWork.gameStateStep_598[2] = 0;
            }
            break;

        case MainOptionsMenuEntry_ScreenPosition:
            // Enter screen position screen.
            if (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.enter_0)
            {
                Sd_PlaySfx(Sfx_MenuConfirm, 0, 64);

                ScreenFade_Start(true, false, false);
                g_GameWork.gameStateStep_598[0] = OptionsMenuState_EnterScreenPos;
                g_SysWork.counters_1C[1]              = 0;
                g_GameWork.gameStateStep_598[1] = 0;
                g_GameWork.gameStateStep_598[2] = 0;
            }
            break;

        case MainOptionsMenuEntry_Brightness:
            if (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.enter_0)
            {
                Sd_PlaySfx(Sfx_MenuConfirm, 0, 64);
                if (g_GameWork.gameStatePrev_590 == GameState_MainMenu)
                {
                    Fs_QueueStartReadTim(FILE_TIM_OP_BRT_E_TIM, IMAGE_BUFFER_3, &g_BrightnessScreenImg0);
                }
                else
                {
                    Fs_QueueStartReadTim(FILE_TIM_OP_BRT_E_TIM, IMAGE_BUFFER_3, &g_BrightnessScreenImg1);
                }

                ScreenFade_Start(true, false, false);
                g_GameWork.gameStateStep_598[0] = OptionsMenuState_EnterBrightness;
                g_SysWork.counters_1C[1]              = 0;
                g_GameWork.gameStateStep_598[1] = 0;
                g_GameWork.gameStateStep_598[2] = 0;
            }
            break;

        case MainOptionsMenuEntry_Vibration:
            if (g_Controller0->btnsClicked_10 & (ControllerFlag_LStickRight | ControllerFlag_LStickLeft))
            {
                Sd_PlaySfx(Sfx_MenuMove, 0, 64);
                g_GameWork.config_0.optVibrationEnabled_21 = !g_GameWork.config_0.optVibrationEnabled_21 << 7;
            }
            break;

        case MainOptionsMenuEntry_AutoLoad:
            if (g_Controller0->btnsClicked_10 & (ControllerFlag_LStickRight | ControllerFlag_LStickLeft))
            {
                Sd_PlaySfx(Sfx_MenuMove, 0, 64);
                g_GameWork.config_0.optAutoLoad_25 = (s8)g_GameWork.config_0.optAutoLoad_25 == 0;
            }
            break;

        case MainOptionsMenuEntry_Sound:
            if (g_Controller0->btnsClicked_10 & (ControllerFlag_LStickRight | ControllerFlag_LStickLeft))
            {
                Sd_PlaySfx(Sfx_MenuMove, 0, 64);

                // Set config.
                audioType                           = AUDIO_TYPE_STEREO;
                g_GameWork.config_0.optSoundType_1E = !g_GameWork.config_0.optSoundType_1E;
                if (g_GameWork.config_0.optSoundType_1E)
                {
                    audioType = AUDIO_TYPE_MONO;
                }
                SD_Call(audioType);
            }
            break;

        case MainOptionsMenuEntry_BgmVolume:
            vol = g_GameWork.config_0.optVolumeBgm_1F;

            if ((vol < OPT_SOUND_VOLUME_MAX && (g_Controller0->btnsPulsed_18 & ControllerFlag_LStickRight)) ||
                (vol > 0                    && (g_Controller0->btnsPulsed_18 & ControllerFlag_LStickLeft)))
            {
                SD_Call(Sfx_MenuMove);
            }
            if ((vol == OPT_SOUND_VOLUME_MAX && (g_Controller0->btnsClicked_10 & ControllerFlag_LStickRight)) ||
                (vol == 0                    && (g_Controller0->btnsClicked_10 & ControllerFlag_LStickLeft)))
            {
                SD_Call(Sfx_MenuError);
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

        case MainOptionsMenuEntry_SfxVolume:
            vol = g_GameWork.config_0.optVolumeSe_20;

            if ((vol < OPT_SOUND_VOLUME_MAX && (g_Controller0->btnsPulsed_18 & ControllerFlag_LStickRight)) ||
                (vol > 0                    && (g_Controller0->btnsPulsed_18 & ControllerFlag_LStickLeft)))
            {
                SD_Call(Sfx_MenuMove);
            }
            if ((vol == OPT_SOUND_VOLUME_MAX && (g_Controller0->btnsClicked_10 & ControllerFlag_LStickRight)) ||
                (vol == 0                    && (g_Controller0->btnsClicked_10 & ControllerFlag_LStickLeft)))
            {
                SD_Call(Sfx_MenuError);
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
        if (g_GameWork.gameStateStep_598[0] == OptionsMenuState_EnterExtraOptions)
        {
            return;
        }

        Sd_PlaySfx(Sfx_MenuConfirm, 0, 64);

        ScreenFade_Start(true, false, false);
        g_GameWork.gameStateStep_598[0] = OptionsMenuState_EnterExtraOptions;
        g_SysWork.counters_1C[1]              = 0;
        g_GameWork.gameStateStep_598[1] = 0;
        g_GameWork.gameStateStep_598[2] = 0;
    }

    // Reset selection cursor.
    if (((g_GameWork.gameStateStep_598[0] != OptionsMenuState_EnterExtraOptions && g_MainOptionsMenu_SelectedEntry != MainOptionsMenuEntry_Exit) &&
         !(g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.enter_0)) &&
        (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.cancel_2))
    {
        Sd_PlaySfx(Sfx_MenuCancel, 0, 64);

        g_Options_SelectionHighlightTimer = 0;
        g_MainOptionsMenu_SelectedEntry         = MainOptionsMenuEntry_Exit;
    }

    #undef SOUND_VOL_STEP
}

void Options_MainOptionsMenu_BgmVolumeBarDraw(void) // 0x801E3F68
{
    Options_MainOptionsMenu_VolumeBarDraw(false, g_GameWork.config_0.optVolumeBgm_1F);
}

void Options_MainOptionsMenu_SfxVolumeBarDraw(void) // 0x801E3F90
{
    Options_MainOptionsMenu_VolumeBarDraw(true, g_GameWork.config_0.optVolumeSe_20);
}

void Options_MainOptionsMenu_VolumeBarDraw(bool isSfx, u8 vol) // 0x801E3FB8
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

    ot       = &g_OrderingTable2[g_ActiveBufferIdx];
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
            addPrim((u8*)ot->org + LAYER_24, poly);
            GsOUT_PACKET_P = (u8*)poly + sizeof(POLY_F4);
        }
    }

    #undef STR_OFFSET_Y
    #undef NOTCH_SIZE_X
    #undef NOTCH_COUNT
}

void Options_ExtraOptionsMenu_EntryStringsDraw(void) // 0x801E416C
{
    #define LINE_BASE_X   64
    #define LINE_BASE_Y   64
    #define LINE_OFFSET_X 16
    #define LINE_OFFSET_Y 16

    s32            i;
    static DVECTOR extraOptions_SelectionHighlightFrom_Unused;
    static DVECTOR extraOptions_SelectionHighlightTo_Unused;

    const DVECTOR STR_POS = { 86, 20 };

    const char* EXTRA_OPTIONS_STR = "EXTRA_OPTION_\x01\x01\x01\x01\x01S";

    const char* ENTRY_STRS[] = {
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

    // @unused Likely an older implementation for active highlight selection position reference setup found in `Options_ExtraOptionsMenu_SelectionHighlightDraw`.
    if (g_Options_SelectionHighlightTimer == 0)
    {
        extraOptions_SelectionHighlightFrom_Unused.vx = LINE_BASE_X - LINE_OFFSET_X;
        extraOptions_SelectionHighlightTo_Unused.vx   = LINE_BASE_X;
        extraOptions_SelectionHighlightFrom_Unused.vy = ((u16)g_MainOptionsMenu_PrevSelectedEntry * LINE_OFFSET_Y) + LINE_BASE_Y;
        extraOptions_SelectionHighlightTo_Unused.vy   = ((u16)g_MainOptionsMenu_SelectedEntry     * LINE_OFFSET_Y) + LINE_BASE_Y;
    }
    Math_Sin(g_Options_SelectionHighlightTimer << 7);

    // Draw heading string.
    Gfx_StringSetColor(StringColorId_White);
    Gfx_StringSetPosition(STR_POS.vx, STR_POS.vy);
    Gfx_Strings2dLayerIdxSet(8);
    Gfx_StringDraw(EXTRA_OPTIONS_STR, DEFAULT_MAP_MESSAGE_LENGTH);

    // Draw entry strings.
    for (i = 0; i < g_ExtraOptionsMenu_EntryCount; i++)
    {
        Gfx_StringSetPosition(LINE_BASE_X, LINE_BASE_Y + (i * LINE_OFFSET_Y));
        Gfx_Strings2dLayerIdxSet(8);
        Gfx_StringDraw(ENTRY_STRS[i], DEFAULT_MAP_MESSAGE_LENGTH);
    }

    #undef LINE_BASE_X
    #undef LINE_BASE_Y
    #undef LINE_OFFSET_X
    #undef LINE_OFFSET_Y
}

void Options_MainOptionsMenu_EntryStringsDraw(void) // 0x801E42EC
{
    #define LINE_BASE_X   64
    #define LINE_BASE_Y   56
    #define LINE_OFFSET_X 16
    #define LINE_OFFSET_Y 16

    s32            i;
    static DVECTOR mainOptions_SelectionHighlightFrom_Unused;
    static DVECTOR mainOptions_SelectionHighlightTo_Unused;

    DVECTOR strPos = { 121, 20 };

    const char* OPTIONS_STR = "OPTION_\x01\x01\x01\x01\x01S";

    const char* ENTRY_STRS[] = {
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

    // @unused Likely an older implementation for active highlight selection position reference setup found in `Options_MainOptionsMenu_SelectionHighlightDraw`.
    if (g_Options_SelectionHighlightTimer == 0)
    {
        mainOptions_SelectionHighlightFrom_Unused.vx = LINE_BASE_X - LINE_OFFSET_X;
        mainOptions_SelectionHighlightTo_Unused.vx   = LINE_BASE_X;
        mainOptions_SelectionHighlightFrom_Unused.vy = ((u16)g_MainOptionsMenu_PrevSelectedEntry * LINE_OFFSET_Y) + LINE_BASE_Y;
        mainOptions_SelectionHighlightTo_Unused.vy   = ((u16)g_MainOptionsMenu_SelectedEntry     * LINE_OFFSET_Y) + LINE_BASE_Y;
    }
    Math_Sin(g_Options_SelectionHighlightTimer << 7);

    // Draw heading string.
    Gfx_StringSetColor(StringColorId_White);
    Gfx_StringSetPosition(strPos.vx, strPos.vy);
    Gfx_Strings2dLayerIdxSet(8);
    Gfx_StringDraw(OPTIONS_STR, DEFAULT_MAP_MESSAGE_LENGTH);

    // Draw entry strings.
    for (i = 0; i < MainOptionsMenuEntry_Count; i++)
    {
        Gfx_StringSetPosition(LINE_BASE_X, LINE_BASE_Y + (i * LINE_OFFSET_Y));
        Gfx_Strings2dLayerIdxSet(8);
        Gfx_StringDraw(ENTRY_STRS[i], DEFAULT_MAP_MESSAGE_LENGTH);
    }

    Gfx_StringsReset2dLayerIdx();

    #undef LINE_BASE_X
    #undef LINE_BASE_Y
    #undef LINE_OFFSET_X
    #undef LINE_OFFSET_Y
}

void Options_ExtraOptionsMenu_SelectionHighlightDraw(void) // 0x801E4450
{
    #define BULLET_QUAD_COUNT  2
    #define LINE_BASE_X        64
    #define LINE_BASE_Y        56
    #define LINE_OFFSET_X      16
    #define LINE_OFFSET_Y      16
    #define HIGHLIGHT_OFFSET_X -121
    #define HIGHLIGHT_OFFSET_Y 50

    s32            i;
    s32            j;
    q3_12          interpAlpha;
    s_Line2d       highlightLine;
    s_Quad2d       bulletQuads[BULLET_QUAD_COUNT];
    DVECTOR*       quadVerts;
    static DVECTOR extraOptions_SelectionHighlightFrom;
    static DVECTOR extraOptions_SelectionHighlightTo;

    const u8 SELECTION_HIGHLIGHT_WIDTHS[] = {
        157, 126, 135, 135, 157, 130, 112, 134
    };

    // 12x12 quad.
    const DVECTOR FRONT_BULLET_QUAD[] = {
        { -120, -47 },
        { -120, -35 },
        { -108, -47 },
        { -108, -35 }
    };

    // 14x14 quad.
    const DVECTOR BACK_BULLET_QUAD[] = {
        { -121, -48 },
        { -121, -34 },
        { -107, -48 },
        { -107, -34 }
    };

    // Set active selection highlight position references.
    if (g_Options_SelectionHighlightTimer == 0)
    {
        extraOptions_SelectionHighlightFrom.vx = SELECTION_HIGHLIGHT_WIDTHS[g_ExtraOptionsMenu_PrevSelectedEntry] + (65536 + HIGHLIGHT_OFFSET_X); // TODO
        extraOptions_SelectionHighlightFrom.vy = ((u16)g_ExtraOptionsMenu_PrevSelectedEntry * LINE_OFFSET_Y)      - HIGHLIGHT_OFFSET_Y;
        extraOptions_SelectionHighlightTo.vx   = SELECTION_HIGHLIGHT_WIDTHS[g_ExtraOptionsMenu_SelectedEntry]     + (65536 + HIGHLIGHT_OFFSET_X); // TODO
        extraOptions_SelectionHighlightTo.vy   = ((u16)g_ExtraOptionsMenu_SelectedEntry * LINE_OFFSET_Y)          - HIGHLIGHT_OFFSET_Y;
    }

    // Compute sine-based interpolation alpha.
    interpAlpha = Math_Sin(g_Options_SelectionHighlightTimer << 7);

    // Draw active selection highlight.
    highlightLine.vertex0_0.vx = HIGHLIGHT_OFFSET_X;
    highlightLine.vertex1_4.vx = extraOptions_SelectionHighlightFrom.vx +
                                 Q12_MULT(extraOptions_SelectionHighlightTo.vx - extraOptions_SelectionHighlightFrom.vx, interpAlpha);
    highlightLine.vertex1_4.vy = extraOptions_SelectionHighlightFrom.vy +
                                 Q12_MULT(extraOptions_SelectionHighlightTo.vy - extraOptions_SelectionHighlightFrom.vy, interpAlpha) +
                                 LINE_OFFSET_Y;
    highlightLine.vertex0_0.vy = highlightLine.vertex1_4.vy;
    Options_Selection_HighlightDraw(&highlightLine, true, false);

    // Draw selection bullet points.
    for (i = 0; i < g_ExtraOptionsMenu_EntryCount; i++)
    {
        // Set bullet quads.
        quadVerts = (DVECTOR*)&bulletQuads;
        for (j = 0; j < RECT_VERT_COUNT; j++)
        {
            quadVerts[j].vx                   = FRONT_BULLET_QUAD[j].vx;
            quadVerts[j].vy                   = FRONT_BULLET_QUAD[j].vy + (i * LINE_OFFSET_Y);
            quadVerts[j + sizeof(DVECTOR)].vx = BACK_BULLET_QUAD[j].vx;
            quadVerts[j + sizeof(DVECTOR)].vy = BACK_BULLET_QUAD[j].vy + (i * LINE_OFFSET_Y);
        }

        // Active selection bullet point.
        if (i == g_ExtraOptionsMenu_SelectedEntry)
        {
            Options_Selection_BulletPointDraw(&bulletQuads[0], false, false);
            Options_Selection_BulletPointDraw(&bulletQuads[1], true,  false);
        }
        // Inactive selection bullet point.
        else
        {
            Options_Selection_BulletPointDraw(&bulletQuads[0], false, true);
            Options_Selection_BulletPointDraw(&bulletQuads[1], true,  true);
        }
    }

    #undef BULLET_QUAD_COUNT
    #undef LINE_BASE_X
    #undef LINE_BASE_Y
    #undef LINE_OFFSET_X
    #undef LINE_OFFSET_Y
    #undef HIGHLIGHT_OFFSET_X
    #undef HIGHLIGHT_OFFSET_Y
}

void Options_MainOptionsMenu_SelectionHighlightDraw(void) // 0x801E472C
{
    #define LINE_OFFSET_Y      16
    #define HIGHLIGHT_OFFSET_X -121
    #define HIGHLIGHT_OFFSET_Y 58

    s32            i;
    s32            j;
    s16            interpAlpha;
    s_Line2d       highlightLine;
    s_Quad2d       bulletQuads[2];
    DVECTOR*       quadVerts;
    static DVECTOR mainOptions_SelectionHighlightFrom;
    static DVECTOR mainOptions_SelectionHighlightTo;

    const u8 SELECTION_HIGHLIGHT_WIDTHS[] = {
        59, 169, 174, 156, 104, 112, 75, 129, 112
    };

    // 12x12 quad.
    const DVECTOR BULLET_QUAD_VERTS_FRONT[] = {
        { -120, -55 },
        { -120, -43 },
        { -108, -55 },
        { -108, -43 }
    };

    // 14x14 quad.
    const DVECTOR BULLET_QUAD_VERTS_BACK[] = {
        { -121, -56 },
        { -121, -42 },
        { -107, -56 },
        { -107, -42 }
    };

    // Set active selection highlight position references.
    if (g_Options_SelectionHighlightTimer == 0)
    {
        mainOptions_SelectionHighlightFrom.vx = SELECTION_HIGHLIGHT_WIDTHS[g_MainOptionsMenu_PrevSelectedEntry] + (65536 + HIGHLIGHT_OFFSET_X); // TODO
        mainOptions_SelectionHighlightFrom.vy = ((u16)g_MainOptionsMenu_PrevSelectedEntry * LINE_OFFSET_Y)    - HIGHLIGHT_OFFSET_Y;
        mainOptions_SelectionHighlightTo.vx   = SELECTION_HIGHLIGHT_WIDTHS[g_MainOptionsMenu_SelectedEntry]     + (65536 + HIGHLIGHT_OFFSET_X); // TODO
        mainOptions_SelectionHighlightTo.vy   = ((u16)g_MainOptionsMenu_SelectedEntry * LINE_OFFSET_Y)        - HIGHLIGHT_OFFSET_Y;
    }

    // Compute sine-based interpolation alpha.
    interpAlpha = Math_Sin(g_Options_SelectionHighlightTimer << 7);

    // Draw active selection highlight.
    highlightLine.vertex0_0.vx = HIGHLIGHT_OFFSET_X;
    highlightLine.vertex1_4.vx = mainOptions_SelectionHighlightFrom.vx +
                                 FP_FROM((mainOptions_SelectionHighlightTo.vx - mainOptions_SelectionHighlightFrom.vx) * interpAlpha, Q12_SHIFT);
    highlightLine.vertex1_4.vy = mainOptions_SelectionHighlightFrom.vy +
                                 FP_FROM((mainOptions_SelectionHighlightTo.vy - mainOptions_SelectionHighlightFrom.vy) * interpAlpha, Q12_SHIFT) +
                                 LINE_OFFSET_Y;
    highlightLine.vertex0_0.vy = highlightLine.vertex1_4.vy;
    Options_Selection_HighlightDraw(&highlightLine, true, false);

    // Draw selection bullet points.
    for (i = 0; i < MainOptionsMenuEntry_Count; i++)
    {
        // Set bullet quads.
        quadVerts = (DVECTOR*)&bulletQuads;
        for (j = 0; j < RECT_VERT_COUNT; j++)
        {
            quadVerts[j].vx                   = BULLET_QUAD_VERTS_FRONT[j].vx;
            quadVerts[j].vy                   = BULLET_QUAD_VERTS_FRONT[j].vy + (i * LINE_OFFSET_Y);
            quadVerts[j + sizeof(DVECTOR)].vx = BULLET_QUAD_VERTS_BACK[j].vx;
            quadVerts[j + sizeof(DVECTOR)].vy = BULLET_QUAD_VERTS_BACK[j].vy + (i * LINE_OFFSET_Y);
        }

        // Active selection bullet point.
        if (i == g_MainOptionsMenu_SelectedEntry)
        {
            Options_Selection_BulletPointDraw(&bulletQuads[0], false, false);
            Options_Selection_BulletPointDraw(&bulletQuads[1], true,  false);
        }
        // Inactive selection bullet point.
        else
        {
            Options_Selection_BulletPointDraw(&bulletQuads[0], false, true);
            Options_Selection_BulletPointDraw(&bulletQuads[1], true,  true);
        }
    }

    #undef LINE_OFFSET_Y
    #undef HIGHLIGHT_OFFSET_X
    #undef HIGHLIGHT_OFFSET_Y
}

void Options_Menu_VignetteDraw(void) // 0x801E49F0
{
    s32      y0;
    s32      y1;
    s32      xy2;
    s32      xy3;
    s32      i;
    GsOT*    ot;
    POLY_G4* poly;

    ot = &g_OrderingTable0[g_ActiveBufferIdx];

    xy3 = 160 + (0xFFA0 << 16); // TODO: -96
    xy2 = 160 + (0xFF90 << 16); // TODO: -112
    y1  = 0xFFA0 << 16;         // TODO: -96
    y0  = 0xFF90 << 16;         // TODO: -112

    for (i = 0; i < 2; i++)
    {
        poly = (POLY_G4*)GsOUT_PACKET_P;

        setPolyG4(poly);
        setSemiTrans(poly, true);

        setRGB0(poly, 0x60, 0x60, 0x60);
        setRGB1(poly, 0, 0, 0);
        setRGB2(poly, 0x60, 0x60, 0x60);
        setRGB3(poly, 0, 0, 0);

        *(u32*)(&poly->x0) = 0xFF60 + (y0 + ((0xE0 * i) << 16)); // TODO: -160
        *(u32*)(&poly->x1) = 0xFF60 + (y1 + ((0xA8 * i) << 16)); // TODO: -160
        *(u32*)(&poly->x2) = xy2    + ((0xE0 * i) << 16);
        *(u32*)(&poly->x3) = xy3    + ((0xA8 * i) << 16);

        addPrim((u8*)ot->org + LAYER_8148, poly);
        GsOUT_PACKET_P = (u8*)poly + sizeof(POLY_G4);
    }

    Gfx_Primitive2dTextureSet(0, 0, 2037, 6);
}

void Options_ExtraOptionsMenu_ConfigDraw(void) // 0x801E4B2C
{
    #define STR_BASE_Y   64
    #define STR_OFFSET_Y 16

    const s_Triangle2d FRONT_ARROWS[] = {
        { { 38,  -42 }, { 46,  -50 }, { 46,  -34 } },
        { { 120, -42 }, { 112, -50 }, { 112, -34 } },
        { { 38,  -26 }, { 46,  -34 }, { 46,  -18 } },
        { { 120, -26 }, { 112, -34 }, { 112, -18 } },
        { { 35,  -10 }, { 43,  -18 }, { 43,  -2  } },
        { { 123, -10 }, { 115, -18 }, { 115, -2  } },
        { { 35,   6  }, { 43,  -2  }, { 43,   14 } },
        { { 123,  6  }, { 115, -2  }, { 115,  14 } },
        { { 35,   22 }, { 43,   14 }, { 43,   30 } },
        { { 123,  22 }, { 115,  14 }, { 115,  30 } },
        { { 51,   38 }, { 59,   30 }, { 59,   46 } },
        { { 107,  38 }, { 99,   30 }, { 99,   46 } },
        { { 24,   54 }, { 32,   46 }, { 32,   62 } },
        { { 131,  54 }, { 123,  46 }, { 123,  62 } },
        { { 57,   70 }, { 65,   62 }, { 65,   78 } },
        { { 104,  70 }, { 96,   62 }, { 96,   78 } }
    };

    const s_Triangle2d BACK_ARROWS[] = {
        { { 37,  -42 }, { 47,  -52 }, { 47,  -32 } },
        { { 121, -42 }, { 111, -52 }, { 111, -32 } },
        { { 37,  -26 }, { 47,  -36 }, { 47,  -16 } },
        { { 121, -26 }, { 111, -36 }, { 111, -16 } },
        { { 34,  -10 }, { 44,  -20 }, { 44,   0  } },
        { { 124, -10 }, { 114, -20 }, { 114,  0  } },
        { { 34,   6  }, { 44,  -4  }, { 44,   16 } },
        { { 124,  6  }, { 114, -4  }, { 114,  16 } },
        { { 34,   22 }, { 44,   12 }, { 44,   32 } },
        { { 124,  22 }, { 114,  12 }, { 114,  32 } },
        { { 50,   38 }, { 60,   28 }, { 60,   48 } },
        { { 108,  38 }, { 98,   28 }, { 98,   48 } },
        { { 23,   54 }, { 33,   44 }, { 33,   64 } },
        { { 132,  54 }, { 122,  44 }, { 122,  64 } },
        { { 56,   70 }, { 66,   60 }, { 66,   80 } },
        { { 105,  70 }, { 95,   60 }, { 95,   80 } }
    };

    // TODO: Can this be split?
    const char* CONFIG_STRS[] = {
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

    s32 strPosX;
    s32 i;
    s32 j;

    Gfx_StringSetColor(StringColorId_White);

    // Draw left/right arrows for subset of options.
    if (g_ExtraOptionsMenu_SelectedEntry < (u32)ExtraOptionsMenuEntry_Count) // TODO: Cast suggests `g_ExtraOptionsMenu_SelectedEntry` type might be unsigned.
    {
        // Draw flashing left/right arrows.
        for (i = 0; i < 2; i++)
        {
            Options_Selection_ArrowDraw(&FRONT_ARROWS[(g_ExtraOptionsMenu_SelectedEntry * 2) + i], true, false);
        }

        // Draw border to highlight flashing left/right arrow corresponding to direction of UI navigation.
        if (g_Controller0->btnsHeld_C & ControllerFlag_LStickLeft)
        {
            Options_Selection_ArrowDraw(&BACK_ARROWS[g_ExtraOptionsMenu_SelectedEntry << 1], false, false);
        }
        if (g_Controller0->btnsHeld_C & ControllerFlag_LStickRight)
        {
            Options_Selection_ArrowDraw(&BACK_ARROWS[(g_ExtraOptionsMenu_SelectedEntry << 1) + 1], false, false);
        }
    }

    // Draw entry strings.
    for (j = 0; j < g_ExtraOptionsMenu_EntryCount; j++)
    {
        switch (j)
        {
            case ExtraOptionsMenuEntry_WeaponCtrl:
                strPosX = (g_GameWork.config_0.optExtraWeaponCtrl_23 != 0) ? 217 : 212;
                Gfx_StringSetPosition(strPosX, STR_BASE_Y + (STR_OFFSET_Y * ExtraOptionsMenuEntry_WeaponCtrl));
                Gfx_StringDraw(CONFIG_STRS[!g_GameWork.config_0.optExtraWeaponCtrl_23], 10);
                break;

            case ExtraOptionsMenuEntry_Blood:
                switch (g_ExtraOptionsMenu_SelectedBloodColorEntry)
                {
                    case BloodColorMenuEntry_Normal:
                        Gfx_StringSetPosition(210, STR_BASE_Y + (STR_OFFSET_Y * ExtraOptionsMenuEntry_Blood));
                        break;

                    case BloodColorMenuEntry_Green:
                        Gfx_StringSetPosition(214, STR_BASE_Y + (STR_OFFSET_Y * ExtraOptionsMenuEntry_Blood));
                        break;

                    case BloodColorMenuEntry_Violet:
                        Gfx_StringSetPosition(214, STR_BASE_Y + (STR_OFFSET_Y * ExtraOptionsMenuEntry_Blood));
                        break;

                    case BloodColorMenuEntry_Black:
                        Gfx_StringSetPosition(217, STR_BASE_Y + (STR_OFFSET_Y * ExtraOptionsMenuEntry_Blood));
                        break;
                }

                Gfx_StringDraw(CONFIG_STRS[g_ExtraOptionsMenu_SelectedBloodColorEntry + 2], 10);
                break;

            case ExtraOptionsMenuEntry_ViewCtrl:
                strPosX = !g_GameWork.config_0.optExtraViewCtrl_28 ? 210 : 206;
                Gfx_StringSetPosition(strPosX, STR_BASE_Y + (STR_OFFSET_Y * ExtraOptionsMenuEntry_ViewCtrl));
                Gfx_StringDraw(CONFIG_STRS[((g_GameWork.config_0.optExtraViewCtrl_28 != 0) ? 32 : 28) >> 2], 10);
                break;

            case ExtraOptionsMenuEntry_RetreatTurn:
                strPosX = !g_GameWork.config_0.optExtraRetreatTurn_2A ? 210 : 206;
                Gfx_StringSetPosition(strPosX, STR_BASE_Y + (STR_OFFSET_Y * ExtraOptionsMenuEntry_RetreatTurn));
                Gfx_StringDraw(CONFIG_STRS[((g_GameWork.config_0.optExtraRetreatTurn_2A != 0) ? 32 : 28) >> 2], 10);
                break;

            case ExtraOptionsMenuEntry_MovementCtrl:
                strPosX = !g_GameWork.config_0.optExtraWalkRunCtrl_2B ? 210 : 206;
                Gfx_StringSetPosition(strPosX, STR_BASE_Y + (STR_OFFSET_Y * ExtraOptionsMenuEntry_MovementCtrl));
                Gfx_StringDraw(CONFIG_STRS[((g_GameWork.config_0.optExtraWalkRunCtrl_2B != 0) ? 32 : 28) >> 2], 10);
                break;

            case ExtraOptionsMenuEntry_AutoAiming:
                strPosX = !g_GameWork.config_0.optExtraAutoAiming_2C ? 228 : 226;
                Gfx_StringSetPosition(strPosX, STR_BASE_Y + (STR_OFFSET_Y * ExtraOptionsMenuEntry_AutoAiming));
                Gfx_StringDraw(CONFIG_STRS[((g_GameWork.config_0.optExtraAutoAiming_2C != 0) ? 40 : 36) >> 2], 10);
                break;

            case ExtraOptionsMenuEntry_ViewMode:
                strPosX = !g_GameWork.config_0.optExtraViewMode_29 ? 210 : 200;
                Gfx_StringSetPosition(strPosX, STR_BASE_Y + (STR_OFFSET_Y * ExtraOptionsMenuEntry_ViewMode));
                Gfx_StringDraw(CONFIG_STRS[(g_GameWork.config_0.optExtraViewMode_29 ? 48 : 44) >> 2], 10);
                break;

            case ExtraOptionsMenuEntry_BulletMult:
                Gfx_StringSetPosition(230, STR_BASE_Y + (STR_OFFSET_Y * ExtraOptionsMenuEntry_BulletMult));
                Gfx_StringDraw(CONFIG_STRS[g_GameWork.config_0.optExtraBulletAdjust_2D + 13], 10);
                break;
        }
    }

    #undef STR_BASE_Y
    #undef STR_OFFSET_Y
}

void Options_MainOptionsMenu_ConfigDraw(void) // 0x801E4FFC
{
    const s_Triangle2d FRONT_ARROWS[] = {
        { { 40,  14 }, { 48,  6  }, { 48,  22 } },
        { { 96,  14 }, { 88,  6  }, { 88,  22 } },
        { { 40,  30 }, { 48,  22 }, { 48,  38 } },
        { { 96,  30 }, { 88,  22 }, { 88,  38 } },
        { { 19,  46 }, { 27,  38 }, { 27,  54 } },
        { { 124, 46 }, { 116, 38 }, { 116, 54 } },
        { { 12,  62 }, { 20,  54 }, { 20,  70 } },
        { { 131, 62 }, { 123, 54 }, { 123, 70 } },
        { { 12,  78 }, { 20,  70 }, { 20,  86 } },
        { { 131, 78 }, { 123, 70 }, { 123, 86 } }
    };

    const s_Triangle2d BACK_ARROWS[] = {
        { { 39,  14 }, { 49,  4  }, { 49,  24 } },
        { { 97,  14 }, { 87,  4  }, { 87,  24 } },
        { { 39,  30 }, { 49,  20 }, { 49,  40 } },
        { { 97,  30 }, { 87,  20 }, { 87,  40 } },
        { { 18,  46 }, { 28,  36 }, { 28,  56 } },
        { { 125, 46 }, { 115, 36 }, { 115, 56 } },
        { { 11,  62 }, { 21,  52 }, { 21,  72 } },
        { { 132, 62 }, { 122, 52 }, { 122, 72 } },
        { { 11,  78 }, { 21,  68 }, { 21,  88 } },
        { { 132, 78 }, { 122, 68 }, { 122, 88 } }
    };

    const char* CONFIG_STRS[] =
    {
        "On",
        "Off",
        "Stereo",
        "Monaural"
    };

    s32 strPosX;
    s32 strIdx;
    s32 i;

    Gfx_StringSetColor(StringColorId_White);

    // Draw left/right arrows for subset of options.
    if (g_MainOptionsMenu_SelectedEntry >= 4 && g_MainOptionsMenu_SelectedEntry < 9)
    {
        // Draw flashing left/right arrows.
        for (i = 0; i < 2; i++)
        {
            Options_Selection_ArrowDraw(&FRONT_ARROWS[(((g_MainOptionsMenu_SelectedEntry - 4) * 2) + i)], true, false);
        }

        // Draw border to highlight flashing left/right arrow corresponding to direction of UI navigation.
        if (g_Controller0->btnsHeld_C & ControllerFlag_LStickLeft)
        {
            Options_Selection_ArrowDraw(&BACK_ARROWS[(g_MainOptionsMenu_SelectedEntry - 4) << 1], false, false);
        }
        if (g_Controller0->btnsHeld_C & ControllerFlag_LStickRight)
        {
            Options_Selection_ArrowDraw(&BACK_ARROWS[((g_MainOptionsMenu_SelectedEntry - 4) << 1) + 1], false, false);
        }
    }

    for (i = 0; i < 3; i++)
    {
        switch (i)
        {
            case 0:
                strPosX = !g_GameWork.config_0.optVibrationEnabled_21 ? 214 : 216;
                Gfx_StringSetPosition(strPosX, 120);

                strIdx = !g_GameWork.config_0.optVibrationEnabled_21;
                Gfx_StringDraw(CONFIG_STRS[strIdx], 10);
                break;

            case 1:
                strPosX = !g_GameWork.config_0.optAutoLoad_25 ? 214 : 216;
                Gfx_StringSetPosition(strPosX, 136);

                strIdx = !g_GameWork.config_0.optAutoLoad_25;
                Gfx_StringDraw(CONFIG_STRS[strIdx], 10);
                break;

            case 2:
                strPosX = g_GameWork.config_0.optSoundType_1E ? 194 : 206;
                Gfx_StringSetPosition(strPosX, 152);

                strIdx = g_GameWork.config_0.optSoundType_1E + 2;
                Gfx_StringDraw(CONFIG_STRS[strIdx], 10);
                break;
        }
    }
}

// ========================================
// SCREEN POSITION OPTION SCREEN
// ========================================

void Options_ScreenPosMenu_Control(void) // 0x801E53A0
{
    #define OPT_SCREEN_POS_X_RANGE 11
    #define OPT_SCREEN_POS_Y_RANGE 8
    #define BG_FADE_STEP           16

    s32        i;
    s8         posX;
    TILE*      tile;
    PACKET*    packet;
    static s32 screenPosMenu_BackgroundFade;
    static s16 screenPosMenu_PositionX;
    static s16 screenPosMenu_PositionY;

    posX = g_GameWorkConst->config_0.optScreenPosX_1C;
    if (posX != screenPosMenu_PositionX || g_GameWorkConst->config_0.optScreenPosY_1D != screenPosMenu_PositionY)
    {
        Screen_XyPositionSet(posX, g_GameWorkConst->config_0.optScreenPosY_1D);
    }

    screenPosMenu_PositionX = g_GameWorkConst->config_0.optScreenPosX_1C;
    screenPosMenu_PositionY = g_GameWorkConst->config_0.optScreenPosY_1D;

    switch (g_GameWork.gameStateStep_598[1])
    {
        case ScreenPosMenuState_0:
            ScreenFade_Start(true, true, false);
            screenPosMenu_BackgroundFade  = 255;
            g_GameWork.gameStateStep_598[1] = ScreenPosMenuState_1;
            g_GameWork.gameStateStep_598[2] = 0;

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
            if (g_GameWorkConst->config_0.optScreenPosX_1C != screenPosMenu_PositionX ||
                g_GameWorkConst->config_0.optScreenPosY_1D != screenPosMenu_PositionY)
            {
                Sd_PlaySfx(Sfx_MenuMove, 0, 64);
            }

            // Start background color fade.
            if (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.enter_0)
            {
                if (screenPosMenu_BackgroundFade == 255)
                {
                    screenPosMenu_BackgroundFade       = 0;
                    g_ScreenPosMenu_InvertBackgroundFade = (g_ScreenPosMenu_InvertBackgroundFade + 1) & (1 << 0);
                }
            }

            // Leave menu.
            if (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.cancel_2)
            {
                Sd_PlaySfx(Sfx_MenuCancel, 0, 64);

                ScreenFade_Start(true, false, false);
                g_GameWork.gameStateStep_598[2] = 0;
                g_GameWork.gameStateStep_598[1]++;
            }
            break;

        case ScreenPosMenuState_Leave:
            // Switch to previous menu.
            if (ScreenFade_IsFinished())
            {
                ScreenFade_Start(true, true, false);
                g_GameWork.gameStateStep_598[0]    = OptionsMenuState_LeaveScreenPos;
                g_SysWork.counters_1C[1]                 = 0;
                g_GameWork.gameStateStep_598[1]    = 0;
                g_GameWork.gameStateStep_598[2]    = 0;
                g_GameWork.background2dColor_58C.r = 0;
                g_GameWork.background2dColor_58C.g = 0;
                g_GameWork.background2dColor_58C.b = 0;
                return;
            }
            break;
    }

    // Update background fade.
    screenPosMenu_BackgroundFade += BG_FADE_STEP;
    screenPosMenu_BackgroundFade  = CLAMP(screenPosMenu_BackgroundFade, 0, 255);
    switch (g_ScreenPosMenu_InvertBackgroundFade)
    {
        case false:
            g_GameWork.background2dColor_58C.r = ~screenPosMenu_BackgroundFade;
            g_GameWork.background2dColor_58C.g = ~screenPosMenu_BackgroundFade;
            g_GameWork.background2dColor_58C.b = ~screenPosMenu_BackgroundFade;
            break;

        case true:
            g_GameWork.background2dColor_58C.r = screenPosMenu_BackgroundFade;
            g_GameWork.background2dColor_58C.g = screenPosMenu_BackgroundFade;
            g_GameWork.background2dColor_58C.b = screenPosMenu_BackgroundFade;
            break;
    }

    packet = GsOUT_PACKET_P;

    for (i = 0; i < 6; i++)
    {
        tile = (TILE*)packet;

        setTile(tile);

        if (g_ScreenPosMenu_InvertBackgroundFade == 0)
        {
            setRGB0(tile, 0xFF, 0, 0);
        }
        else if (g_ScreenPosMenu_InvertBackgroundFade == 1)
        {
            setRGB0(tile, 0xFF, 0, 0);
        }

        if (i < 3)
        {
            setXY0(tile, -160, -97 + (96 * i));
            setWH(tile, 320, 2);
        }
        else
        {
            setXY0(tile, -577 + (144 * i), -120);
            setWH(tile, 2, 240);
        }

        addPrim(g_OrderingTable0[g_ActiveBufferIdx].org, (TILE*)packet);
        packet += sizeof(TILE);
    }

    for (i = 0; i < 28; i++)
    {
        tile = (TILE*)packet;

        setTile(tile);

        switch (g_ScreenPosMenu_InvertBackgroundFade)
        {
            case 0:
                setRGB0(tile, screenPosMenu_BackgroundFade, screenPosMenu_BackgroundFade, screenPosMenu_BackgroundFade);
                break;

            case 1:
                setRGB0(tile, ~screenPosMenu_BackgroundFade, ~screenPosMenu_BackgroundFade, ~screenPosMenu_BackgroundFade);
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

        addPrim(g_OrderingTable0[g_ActiveBufferIdx].org, (TILE*)packet);
        packet += sizeof(TILE);
    }

    GsOUT_PACKET_P = packet;

    Options_ScreenPosMenu_ArrowsDraw();
    Options_ScreenPosMenu_ConfigDraw();

    #undef OPT_SCREEN_POS_X_RANGE
    #undef OPT_SCREEN_POS_Y_RANGE
    #undef BG_FADE_STEP
}

void Options_ScreenPosMenu_ArrowsDraw(void) // 0x801E5A08
{
    #define DIR_COUNT 4

    const s_Triangle2d FRONT_ARROWS[] = {
        { {  0,  -100 }, { -8,   -92 }, {  8,  -92 } },
        { {  0,   100 }, { -8,    92 }, {  8,   92 } },
        { { -148, 0   }, { -140, -8  }, { -140, 8  } },
        { {  148, 0   }, {  140, -8  }, {  140, 8  } }
    };

    const s_Triangle2d BACK_ARROWS[] = {
        { {  0,  -101 }, { -10,  -91 }, {  9,  -91 } },
        { {  0,   101 }, { -10,   91 }, {  9,   91 } },
        { { -149, 0   }, { -139, -10 }, { -139, 10 } },
        { {  149, 0   }, {  139, -10 }, {  139, 10 } }
    };

    u8  dirs[DIR_COUNT]; // Booleans.
    s32 i;

    // Clear directions array for no reason.
    memset(dirs, 0, DIR_COUNT);

    // Draw flashing up/down/left/right arrows.
    for (i = 0; i < DIR_COUNT; i++)
    {
        Options_Selection_ArrowDraw(&FRONT_ARROWS[i], true, false);
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
            Options_Selection_ArrowDraw(&BACK_ARROWS[i], false, false);
        }
    }

    #undef DIR_COUNT
}

void Options_ScreenPosMenu_ConfigDraw(void) // 0x801E5CBC
{
    s32      i;
    LINE_F2* line;
    POLY_F4* poly;
    GsOT*    ot = &g_OrderingTable2[g_ActiveBufferIdx];

    const DVECTOR LINE_BASES[] = {
        { -60, 40 },
        { -60, 70 },
        { 60, 70 },
        { 60, 40 }
    };

    const char* AXIS_OFFSET_STRS[] = {
        "X:_",
        "Y:_"
    };

    for (i = 0; i < 4; i++)
    {
        line = (LINE_F2*)GsOUT_PACKET_P;

        setLineF2(line);
        setCodeWord(line, 0x40, (i < 2) ? PACKED_COLOR(240, 240, 240, 0) : PACKED_COLOR(128, 128, 128, 0));

        setXY0Fast(line, (u16)(LINE_BASES[i].vx             - g_GameWorkConst->config_0.optScreenPosX_1C), LINE_BASES[i].vy             - g_GameWorkConst->config_0.optScreenPosY_1D);
        setXY1Fast(line, (u16)(LINE_BASES[(i + 1) & 0x3].vx - g_GameWorkConst->config_0.optScreenPosX_1C), LINE_BASES[(i + 1) & 0x3].vy - g_GameWorkConst->config_0.optScreenPosY_1D);

        addPrim((u8*)ot->org + LAYER_40, line);
        GsOUT_PACKET_P = (u8*)line + sizeof(LINE_F2);
    }

    poly = (POLY_F4*)GsOUT_PACKET_P;
    setPolyF4(poly);

    setCodeWord(poly, 40, 0);
    setXY0Fast(poly, (u16)(LINE_BASES[0].vx - g_GameWorkConst->config_0.optScreenPosX_1C), LINE_BASES[0].vy - g_GameWorkConst->config_0.optScreenPosY_1D);
    setXY1Fast(poly, (u16)(LINE_BASES[1].vx - g_GameWorkConst->config_0.optScreenPosX_1C), LINE_BASES[1].vy - g_GameWorkConst->config_0.optScreenPosY_1D);
    setXY2Fast(poly, (u16)(LINE_BASES[3].vx - g_GameWorkConst->config_0.optScreenPosX_1C), LINE_BASES[3].vy - g_GameWorkConst->config_0.optScreenPosY_1D);
    setXY3Fast(poly, (u16)(LINE_BASES[2].vx - g_GameWorkConst->config_0.optScreenPosX_1C), LINE_BASES[2].vy - g_GameWorkConst->config_0.optScreenPosY_1D);

    addPrim((u8*)ot->org + LAYER_40, poly);
    GsOUT_PACKET_P = (u8*)poly + sizeof(POLY_F4);

    Gfx_StringSetPosition(108 - g_GameWorkConst->config_0.optScreenPosX_1C, 162 - g_GameWorkConst->config_0.optScreenPosY_1D);
    Gfx_StringDraw(AXIS_OFFSET_STRS[0], 10);
    Gfx_StringDrawInt(3, g_GameWorkConst->config_0.optScreenPosX_1C);

    Gfx_StringSetPosition(168 - g_GameWorkConst->config_0.optScreenPosX_1C, 162 - g_GameWorkConst->config_0.optScreenPosY_1D);
    Gfx_StringDraw(AXIS_OFFSET_STRS[1], 10);
    Gfx_StringDrawInt(3, g_GameWorkConst->config_0.optScreenPosY_1D);
}

// ========================================
// BRIGHTNESS OPTION SCREEN
// ========================================

void Options_BrightnessMenu_Control(void) // 0x801E6018
{
    // Handle menu state.
    switch (g_GameWork.gameStateStep_598[1])
    {
        case BrightnessMenuState_0:
            // Entry.
            g_GameWork.gameStateStep_598[1] = BrightnessMenuState_1;
            g_GameWork.gameStateStep_598[2] = 0;
            break;

        case BrightnessMenuState_1:
            // Set fade.
            ScreenFade_Start(true, true, false);
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
                    Sd_PlaySfx(Sfx_MenuMove, 0, Q8_CLAMPED(0.25f));
                }
            }
            if (g_Controller0->btnsPulsed_18 & ControllerFlag_LStickRight)
            {
                if (g_GameWork.config_0.optBrightness_22 < 7)
                {
                    g_GameWork.config_0.optBrightness_22++;
                    Sd_PlaySfx(Sfx_MenuMove, 0, Q8_CLAMPED(0.25f));
                }
            }

            // Fade screen and leave menu.
            if (g_Controller0->btnsClicked_10 & (g_GameWorkPtr->config_0.controllerConfig_0.enter_0 |
                                                 g_GameWorkPtr->config_0.controllerConfig_0.cancel_2))
            {
                if (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.enter_0)
                {
                    Sd_PlaySfx(Sfx_MenuConfirm, 0, Q8_CLAMPED(0.25f));
                }
                else
                {
                    Sd_PlaySfx(Sfx_MenuCancel, 0, Q8_CLAMPED(0.25f));
                }

                ScreenFade_Start(true, false, false);
                g_GameWork.gameStateStep_598[1]++;
                g_GameWork.gameStateStep_598[2] = 0;
            }
            break;

        case BrightnessMenuState_Leave:
            // Switch to previous menu.
            // TODO: Odd check for `ScreenFade_IsFinished()`.
            if (g_Screen_FadeStatus & (1 << 2) && !(g_Screen_FadeStatus & (1 << 1)) && g_Screen_FadeStatus & (1 << 0))
            {
                ScreenFade_Start(true, true, false);
                g_GameWork.gameStateStep_598[0]    = OptionsMenuState_LeaveBrightness;
                g_SysWork.counters_1C[1]                 = 0;
                g_GameWork.gameStateStep_598[1]    = 0;
                g_GameWork.gameStateStep_598[2]    = 0;
                g_GameWork.background2dColor_58C.r = 0;
                g_GameWork.background2dColor_58C.g = 0;
                g_GameWork.background2dColor_58C.b = 0;
            }
            break;
    }

    // Draw graphics.
    if (g_GameWork.gameStatePrev_590 == GameState_MainMenu)
    {
        Screen_BackgroundImgDraw(&g_BrightnessScreenImg0);
    }
    else
    {
        Screen_BackgroundImgDraw(&g_BrightnessScreenImg1);
    }

    Options_BrightnessMenu_LinesDraw(g_GameWork.config_0.optBrightness_22);
    Options_BrightnessMenu_ArrowsDraw();
    Options_BrightnessMenu_ConfigDraw();
}

void Options_BrightnessMenu_ConfigDraw(void) // 0x801E6238
{
    const char* LEVEL_STR = "LEVEL_________"; // 0x801E2C64

    Gfx_StringSetColor(StringColorId_White);
    Gfx_StringSetPosition(SCREEN_POSITION_X(25.0f), SCREEN_POSITION_Y(79.5f));
    Gfx_StringDraw(LEVEL_STR, 20);
    Gfx_StringDrawInt(1, g_GameWork.config_0.optBrightness_22);
}

void Options_BrightnessMenu_ArrowsDraw(void) // 0x801E628C
{
    const s_Triangle2d FRONT_ARROWS[] = {
        { { 8, 84  }, { 16, 76 }, { 16, 92 } },
        { { 64, 84 }, { 56, 76 }, { 56, 92 } }
    };

    const s_Triangle2d BORDER_ARROWS[] = {
        { { 7, 84  }, { 17, 74 }, { 17, 94 } },
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
        Options_Selection_ArrowDraw(&FRONT_ARROWS[i], true, false);
    }

    // Draw border to highlight flashing left/right arrow corresponding to direction of UI navigation.
    for (i = dir - 1; i < dir; i++)
    {
        Options_Selection_ArrowDraw(&BORDER_ARROWS[i], false, false);
    }
}

// ========================================
// DRAW OPTIONS FEATURES SCREEN
// ========================================

void Options_Selection_HighlightDraw(const s_Line2d* line, bool hasShadow, bool invertGradient) // 0x801E641C
{
    #define STR_OFFSET_Y 16

    s_Line2d* localLine;
    LINE_G2*  linePrim;
    POLY_G4*  poly;
    GsOT*     ot;

    ot        = &g_OrderingTable2[g_ActiveBufferIdx];
    linePrim  = (LINE_G2*)GsOUT_PACKET_P;
    localLine = line;

    // Draw underline.
    setLineG2(linePrim);

    // @unused Non-functioning line color gradient inversion? Gradient is unchanged regardless of `invertGradient`'s value,
    // which itself is always passed as `false`. Purpose is guessed based on a similar parameter in `Options_Selection_BulletPointDraw`.
    if (invertGradient)
    {
        setRGBC0(linePrim, 176, 176, 176, 0x50);
        setRGBC1(linePrim, 160, 128, 64,  0x50);
    }
    else
    {
        setRGBC0(linePrim, 176, 176, 176, 0x50);
        setRGBC1(linePrim, 160, 128, 64,  0x50);
    }

    setXY0Fast(linePrim, localLine->vertex0_0.vx, localLine->vertex0_0.vy);
    setXY1Fast(linePrim, localLine->vertex1_4.vx, localLine->vertex1_4.vy);
    addPrim((u8*)ot->org + (hasShadow ? LAYER_36 : LAYER_24), linePrim);
    GsOUT_PACKET_P = (u8*)linePrim + sizeof(LINE_G2);

    // Draw shadow gradient.
    if (hasShadow)
    {
        poly = (POLY_G4*)GsOUT_PACKET_P;
        setPolyG4(poly);
        setSemiTrans(poly, true);
        setRGB0(poly, 0, 0, 0);
        setRGB1(poly, Q8_COLOR(0.375f), Q8_COLOR(0.375f), Q8_COLOR(0.375f));
        setRGB2(poly, 0, 0, 0);
        setRGB3(poly, Q8_COLOR(0.375f), Q8_COLOR(0.375f), Q8_COLOR(0.375f));
        setXY4(poly,
               localLine->vertex0_0.vx, localLine->vertex0_0.vy - STR_OFFSET_Y, localLine->vertex0_0.vx, localLine->vertex0_0.vy,
               localLine->vertex1_4.vx, localLine->vertex1_4.vy - STR_OFFSET_Y, localLine->vertex1_4.vx, localLine->vertex1_4.vy);
        addPrim((u8*)ot->org + LAYER_36, poly);
        GsOUT_PACKET_P = (u8*)poly + sizeof(POLY_G4);

        Gfx_Primitive2dTextureSet(0, 0, 9, 2);
    }

    #undef STR_OFFSET_Y
}

void Options_Selection_ArrowDraw(const s_Triangle2d* arrow, bool isFlashing, bool resetColor) // 0x801E662C
{
    s32      colorFade;
    s32      colorStart;
    s32      colorEnd;
    POLY_G3* arrowPoly;
    GsOT*    ot;

    ot = &g_OrderingTable2[g_ActiveBufferIdx];

    // @unused `resetColor` doesn't serve any meaningful purpose.
    if (resetColor)
    {
        colorEnd   = 0;
        colorStart = 0;
    }

    colorFade = g_SysWork.counters_1C[0] & 0x7F;

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
        // Base color is blue. `* 0x700` Shifts green component into place.
        *((u32*)&arrowPoly->r0) = (colorEnd   * 0x700) + PACKED_COLOR(0, 0, 255, 0x30);
        *((u32*)&arrowPoly->r1) = (colorStart * 0x700) + PACKED_COLOR(0, 0, 255, 0x30);
        *((u32*)&arrowPoly->r2) = (colorStart * 0x700) + PACKED_COLOR(0, 0, 255, 0x30);
    }
    // Set solid cyan color.
    else
    {
        setRGBC0(arrowPoly, 0, 240, 240, 0x30);
        setRGBC1(arrowPoly, 0, 240, 240, 0x30);
        setRGBC2(arrowPoly, 0, 240, 240, 0x30);
    }

    setXY0Fast(arrowPoly, arrow->vertex0_0.vx, arrow->vertex0_0.vy);
    setXY1Fast(arrowPoly, arrow->vertex1_4.vx, arrow->vertex1_4.vy);
    setXY2Fast(arrowPoly, arrow->vertex2_8.vx, arrow->vertex2_8.vy);
    addPrim((u8*)ot->org + LAYER_40, arrowPoly);
    GsOUT_PACKET_P = (u8*)arrowPoly + sizeof(POLY_G3);
}

void Options_Selection_BulletPointDraw(const s_Quad2d* quad, bool isBorder, bool isInactive) // 0x801E67B0
{
    #define TRI_COUNT 2

    GsOT*    ot = &g_OrderingTable2[g_ActiveBufferIdx];
    s32      i;
    POLY_G3* poly;

    // Draw quad as triangles to achieve diagonal gradient.
    for (i = 0; i < TRI_COUNT; i++)
    {
        poly = (POLY_G3*)GsOUT_PACKET_P;
        setPolyG3(poly);

        if (isBorder)
        {
            // Set color.
            switch (isInactive)
            {
                case false:
                    setRGBC0(poly, 255, 255, 255, 0x30);
                    setRGBC1(poly, 160, 128, 64,  0x30);
                    setRGBC2(poly, 64,  64,  64,  0x30);
                    break;

                case true:
                    setRGBC0(poly, 128, 128, 128, 0x30);
                    setRGBC1(poly, 40,  32,  16,  0x30);
                    setRGBC2(poly, 16,  16,  16,  0x30);
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
        else
        {
            // Set color.
            switch (isInactive)
            {
                case false:
                    setRGBC0(poly, 160, 128, 64,  0x30);
                    setRGBC1(poly, 255, 255, 255, 0x30);
                    setRGBC2(poly, 255, 255, 255, 0x30);
                    break;

                case true:
                    setRGBC0(poly, 80,  64,  32,  0x30);
                    setRGBC1(poly, 160, 160, 160, 0x30);
                    setRGBC2(poly, 160, 160, 160, 0x30);
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

        addPrim((u8*)ot->org + LAYER_24, poly);
        GsOUT_PACKET_P = (u8*)poly + sizeof(POLY_G3);
    }

    #undef TRI_COUNT
}

// ========================================
// CONTROLS OPTION SCREEN
// ========================================

void Options_ControllerMenu_Control(void) // 0x801E69BC
{
    s32                                     boundActionIdx = NO_VALUE;
    e_InputAction                           actionIdx;
    static s_ControllerMenu_SelectedEntries controllerMenu_SelectedEntries;

    // Handle controller config menu state.
    switch (g_GameWork.gameStateStep_598[1])
    {
        case ControllerMenuState_Exit:
            ScreenFade_Start(false, true, false);
            controllerMenu_SelectedEntries.preset_0 = ControllerMenuState_Exit;

            // Leave menu.
            if (g_Controller0->btnsClicked_10 & (g_GameWorkPtr->config_0.controllerConfig_0.enter_0 |
                                                 g_GameWorkPtr->config_0.controllerConfig_0.cancel_2))
            {
                SD_Call(Sfx_MenuCancel);

                ScreenFade_Start(false, false, false);
                g_GameWork.gameStateStep_598[1] = ControllerMenuState_Leave;
                g_GameWork.gameStateStep_598[2] = 0;
                break;
            }

            // Move selection cursor up/down.
            if (g_Controller0->btnsPulsedGui_1C & ControllerFlag_LStickUp)
            {
                g_GameWork.gameStateStep_598[1] = ControllerMenuState_Type3;
                g_GameWork.gameStateStep_598[2] = 0;
            }
            else if (g_Controller0->btnsPulsedGui_1C & ControllerFlag_LStickDown)
            {
                g_GameWork.gameStateStep_598[1] = ControllerMenuState_Type1;
                g_GameWork.gameStateStep_598[2] = 0;
            }
            // Move selection cursor left/right.
            else if (g_Controller0->btnsPulsedGui_1C & (ControllerFlag_LStickLeft | ControllerFlag_LStickRight))
            {
                g_GameWork.gameStateStep_598[1] = ControllerMenuState_Actions;
                g_GameWork.gameStateStep_598[2] = 0;
            }
            break;

        case ControllerMenuState_Type1:
        case ControllerMenuState_Type2:
        case ControllerMenuState_Type3:
            controllerMenu_SelectedEntries.preset_0 = g_GameWork.gameStateStep_598[1];

            // Set binding preset.
            if (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.enter_0)
            {
                SD_Call(Sfx_MenuConfirm);
                Settings_RestoreControlDefaults(g_GameWork.gameStateStep_598[1] - 1);
            }
            // Reset selection cursor.
            else if (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.cancel_2)
            {
                SD_Call(Sfx_MenuCancel);
                g_GameWork.gameStateStep_598[1] = ControllerMenuState_Exit;
                g_GameWork.gameStateStep_598[2] = 0;
            }
            // Move selection cursor.
            else
            {
                // Move selection cursor up/down.
                if (g_Controller0->btnsPulsedGui_1C & ControllerFlag_LStickUp)
                {
                    g_GameWork.gameStateStep_598[1] = (g_GameWork.gameStateStep_598[1] - 1) & 3;
                    g_GameWork.gameStateStep_598[2] = 0;
                }
                else if (g_Controller0->btnsPulsedGui_1C & ControllerFlag_LStickDown)
                {
                    g_GameWork.gameStateStep_598[1] = (g_GameWork.gameStateStep_598[1] + 1) & 3;
                    g_GameWork.gameStateStep_598[2] = 0;
                }
                // Move selection cursor left/right.
                else if (g_Controller0->btnsPulsedGui_1C & (ControllerFlag_LStickLeft | ControllerFlag_LStickRight))
                {
                    g_GameWork.gameStateStep_598[1] = ControllerMenuState_Actions;
                    g_GameWork.gameStateStep_598[2] = 0;
                }
            }
            break;

        case ControllerMenuState_Actions:
            actionIdx = controllerMenu_SelectedEntries.action_4;

            // Move selection cursor up/down.
            if (g_Controller0->btnsPulsedGui_1C & ControllerFlag_LStickUp)
            {
                if (actionIdx != InputAction_Enter)
                {
                    controllerMenu_SelectedEntries.action_4 = actionIdx - 1;
                }
                else
                {
                    controllerMenu_SelectedEntries.action_4 = InputAction_Option;
                }
            }
            else if (g_Controller0->btnsPulsedGui_1C & ControllerFlag_LStickDown)
            {
                if (actionIdx != InputAction_Option)
                {
                    controllerMenu_SelectedEntries.action_4 = actionIdx + 1;
                }
                else
                {
                    controllerMenu_SelectedEntries.action_4 = InputAction_Enter;
                }
            }
            // Move selection cursor left/right.
            else if (g_Controller0->btnsPulsedGui_1C & (ControllerFlag_LStickLeft | ControllerFlag_LStickRight))
            {
                g_GameWork.gameStateStep_598[2] = 0;
                g_GameWork.gameStateStep_598[1] = controllerMenu_SelectedEntries.preset_0;
            }
            // Bind button to input action.
            else
            {
                boundActionIdx = Options_ControllerMenu_ConfigUpdate(actionIdx);
            }
            break;

        case ControllerMenuState_Leave:
            // Switch to previous menu.
            if (ScreenFade_IsFinished())
            {
                ScreenFade_Start(true, true, false);
                g_GameWork.gameStateStep_598[0] = OptionsMenuState_LeaveController;
                g_SysWork.counters_1C[1]              = 0;
                g_GameWork.gameStateStep_598[1] = 0;
                g_GameWork.gameStateStep_598[2] = 0;
            }
            break;
    }

    if (g_GameWork.gameStateStep_598[1] == ControllerMenuState_Actions)
    {
        g_ControllerMenu_IsOnActionsPane = true;
    }
    else
    {
        g_ControllerMenu_IsOnActionsPane = false;
    }

    // Play cursor navigation SFX.
    if (g_Controller0->btnsPulsedGui_1C & (ControllerFlag_LStickUp | ControllerFlag_LStickRight | ControllerFlag_LStickDown | ControllerFlag_LStickLeft))
    {
        SD_Call(Sfx_MenuMove);
    }

    // Draw menu graphics.
    Options_ControllerMenu_EntriesDraw(g_ControllerMenu_IsOnActionsPane, controllerMenu_SelectedEntries.preset_0, controllerMenu_SelectedEntries.action_4, boundActionIdx);
}

s32 Options_ControllerMenu_ConfigUpdate(s32 actionIdx) // 0x801E6CF4
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
                SD_Call(Sfx_MenuError);
            }
            else
            {
                bindings[actionIdx] &= ~btnFlag;
                SD_Call(Sfx_MenuConfirm);
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
                            SD_Call(Sfx_MenuError);
                        }
                        else
                        {
                            bindings[curActionIdx] &= ~btnFlag;
                            bindings[actionIdx]    |= btnFlag;
                            SD_Call(Sfx_MenuConfirm);
                        }
                    }
                    else
                    {
                        bindings[actionIdx] = boundBtnFlag | btnFlag;
                        SD_Call(Sfx_MenuConfirm);
                    }
                    break;

                case 2:
                    bindings[InputAction_Skip] |= btnFlag;
                    SD_Call(Sfx_MenuConfirm);
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
                            SD_Call(Sfx_MenuError);
                            boundActionIdx = curActionIdx;
                        }
                        else
                        {
                            bindings[curActionIdx] &= ~btnFlag;
                            bindings[actionIdx]    |= btnFlag;
                            SD_Call(Sfx_MenuConfirm);
                        }
                    }
                    else
                    {
                        bindings[actionIdx] |= btnFlag;
                        SD_Call(Sfx_MenuConfirm);
                    }
                    break;
            }
        }
    }

    return boundActionIdx;
}


void Options_ControllerMenu_EntriesDraw(bool isOnRightPane, s32 presetsEntryIdx, s32 actionsEntryIdx, s32 boundActionIdx) // 0x801E6F60
{
    #define STR_BASE_Y    22
    #define STR_OFFSET_Y  20
    #define ICON_SIZE_Y   12
    #define ICON_OFFSET_X -12

    s16      highlightY0;
    s16      highlightY1;
    s32      strYPos;
    s32      i;
    u16*     contConfig;
    DR_MODE* drMode;
    POLY_G4* poly;
    GsOT*    ot;

    /** @brief Draw modes for textured entry selection highlights in the controller config menu.
     * 0 corresponds to the presets pane on the left,
     * 1 corresponds to the actions pane on the right.
     */
    static DR_MODE controllerMenu_SelectionHighlightDrawModes[2] = {
        {
            .tag  = 0x03000000,
            .code = { 0xE1000200, 0 }
        },
        {
            .tag  = 0x03000000,
            .code = { 0xE1000200, 0 }
        }
    };

    /** @brief Quads for textured entry selection highlights in the controller config menu.
     * 0 corresponds to the presets pane on the left,
     * 1 corresponds to the actions pane on the right.
     */
    static POLY_G4 controllerMenu_SelectionHighlightQuads[2] = {
        {
            .tag  = 0x08000000,
            .r0   = 255,
            .g0   = 255,
            .b0   = 255,
            .code = 0x3A,
            .r3   = 255,
            .g3   = 255,
            .b3   = 255
        },
        {
            .tag  = 0x08000000,
            .code = 0x3A,
            .r1   = 255,
            .g1   = 255,
            .b1   = 255,
            .r2   = 255,
            .g2   = 255,
            .b2   = 255
        },
    };

    /** @brief Controller menu entry strings for the presets pane on the left. */
    static const char* CONTROLLER_MENU_PRESETS_PANE_ENTRY_STRINGS[] = {
        "EXIT",
        "TYPE_1",
        "TYPE_2",
        "TYPE_3"
    };

    /** @brief Controller menu entry strings for the actions pane on the right. */
    static const char* CONTROLLER_MENU_ACTIONS_PANE_ENTRY_STRINGS[] = {
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


    ot     = &g_OtTags0[g_ActiveBufferIdx][15];
    poly   = &controllerMenu_SelectionHighlightQuads[g_ActiveBufferIdx];
    drMode = &controllerMenu_SelectionHighlightDrawModes[g_ActiveBufferIdx];

    // Draw entry strings.
    for (i = 0; i < ControllerMenuState_Count; i++)
    {
        Gfx_StringSetPosition(24, STR_BASE_Y + (i * STR_OFFSET_Y));
        Gfx_StringDraw(CONTROLLER_MENU_PRESETS_PANE_ENTRY_STRINGS[i], 20);
    }

    if (!isOnRightPane)
    {
        highlightY1 = presetsEntryIdx * STR_OFFSET_Y;
        highlightY0 = highlightY1 - 91;
        setXY4(poly,
               -137, highlightY0,
               -76,  highlightY0,
               -137, highlightY1 - 76,
               -76,  highlightY1 - 76);
    }

    strYPos     = STR_BASE_Y;
    highlightY0 = -300;

    // Draw controller config.
    for (i = 0, contConfig = (u16*)&g_GameWorkPtr->config_0.controllerConfig_0; i < (u32)InputAction_Count; i++, contConfig++)
    {
        // Draw action string.
        Text_Debug_PositionSet(96, strYPos);
        Text_Debug_Draw(CONTROLLER_MENU_ACTIONS_PANE_ENTRY_STRINGS[i]);

        // Draw button icon.
        if (i != boundActionIdx)
        {
            Options_ControllerMenu_ButtonIconsDraw(ICON_OFFSET_X, strYPos - 114, *contConfig);
        }

        if (i == actionsEntryIdx)
        {
            highlightY0 = strYPos - 113;
        }

        strYPos = (strYPos + ICON_SIZE_Y) + ((i == 2) ? ICON_SIZE_Y : 0);
    }

    if (isOnRightPane == true)
    {
        setXY4(poly,
               -65, highlightY0,
               -15, highlightY0,
               -65, highlightY0 + 10,
               -15, highlightY0 + 10);
    }

    AddPrim(ot, poly);
    AddPrim(ot, drMode);

    #undef STR_BASE_Y
    #undef STR_OFFSET_Y
    #undef ICON_SIZE_Y
    #undef ICON_OFFSET_X
}

void Options_ControllerMenu_ButtonIconsDraw(s32 baseX, s32 baseY, u16 config) // 0x801E716C
{
    #define ICON_SIZE_X   12
    #define ICON_SIZE_Y   12
    #define ICON_OFFSET_X 14

    s32            i;
    s32            posX;
    u16            clutX;
    u32            clutY;
    s32            temp;
    s32            v0;
    GsOT*          ot;
    SPRT*          prim;
    DR_TPAGE*      tpage;
    PACKET*        packet;
    s_FsImageDesc* image;

    image = &g_ControllerButtonAtlasImg;

    ot     = &g_OtTags1[g_ActiveBufferIdx][16];
    packet = GsOUT_PACKET_P;

    // Draw button sprites.
    for (posX = baseX, i = ICON_SIZE_X; i < 28; i++)
    {
        temp = i & 0xF;
        v0   = ((temp + 8) & 0xF) << 4;

        if (!((config >> temp) & (1 << 0)))
        {
            continue;
        }

        prim = (SPRT*)packet;
        addPrimFast(ot, prim, 4);
        setCodeWord(prim, PRIM_RECT | RECT_TEXTURE, PACKED_COLOR(128, 128, 128, 0));
        setWH(prim, ICON_SIZE_X, ICON_SIZE_Y);

        clutY = image->clutY;
        clutX = image->clutX;

        setXY0Fast(prim, posX, baseY);
        posX += ICON_OFFSET_X;

        // setUV0AndClut(prim, 0xF4, v0, clutY, clutX);
        *(u32*)(&prim->u0) = 244 + (v0 << 8) + (((clutY << 6) | ((clutX >> 4) & 0x3F)) << 16);

        packet = (u8*)prim + sizeof(SPRT);
        tpage  = (DR_TPAGE*)packet;

        setDrawTPage(tpage, 0, 1, getTPageN(0, 0, 7, 0));
        AddPrim(ot, tpage);
        packet = (u8*)tpage + sizeof(DR_TPAGE);
    }

    GsOUT_PACKET_P = packet;

    #undef ICON_SIZE_X
    #undef ICON_SIZE_Y
    #undef ICON_OFFSET_X
}


/** @brief Unknown .rodata value.
 * The type is assumed. It is unknown where this is used and
 * could be something defined by a macro.
 */
static const u16 D_801E2D42 = 4160;
