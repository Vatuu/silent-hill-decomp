#include "game.h"

#include "bodyprog/bodyprog.h"
#include "bodyprog/math.h"
#include "screens/options/options.h"
#include "screens/stream/stream.h"

// ========================================
// GENERAL, MAIN, AND EXTRA OPTION SCREENS
// ========================================

void GameState_OptionScreen_Update() // 0x801E2D44
{
    s32 extraOptions;
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

            g_GameWork.field_58C = 0;
            g_GameWork.field_58D = 0;
            g_GameWork.field_58E = 0;

            D_800BCD0C        = 7;
            g_IntervalVBlanks = 1;

            if (g_GameWork.gameStatePrev_590 == GameState_InGame)
            {
                func_80037188();
            }

            D_801E72F4   = 0;
            D_801E72FC   = 0;
            D_801E72F8   = 0;
            D_801E7300   = 0;
            D_801E73E4   = 0;
            D_801E73F0   = 1;
            extraOptions = g_GameWork.config_0.optExtraOptionsEnabled_27;

            for (i = 0; i < 5; i++)
            {
                if ((extraOptions >> i) & 1)
                {
                    D_801E73F0++;
                }
            }

            switch (g_GameWork.config_0.optBloodColor_24)
            {
                case 0:
                    D_801E73EC = 0;
                    break;

                case 2:
                    D_801E73EC = 1;
                    break;

                case 5:
                    D_801E73EC = 2;
                    break;

                case 11:
                    D_801E73EC = 3;
                    break;
            }

            D_801E73E8                      = g_GameWork.config_0.optExtraOptionsEnabled_27 != 0 ? 8 : 6;
            g_GameWork.gameStateStep_598[0] = 1;
            g_SysWork.timer_20              = 0;
            g_GameWork.gameStateStep_598[1] = 0;
            g_GameWork.gameStateStep_598[2] = 0;
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
            if ((D_800BCD0C & 7) == 5)
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
            if ((D_800BCD0C & 7) == 5)
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
            if ((D_800BCD0C & 7) == 5)
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
            D_800BCD0C                      = 2;
            g_GameWork.gameStateStep_598[0] = 6;
            g_SysWork.timer_20              = 0;
            g_GameWork.gameStateStep_598[1] = 0;
            g_GameWork.gameStateStep_598[2] = 0;
            break;

        case 6:
            if ((D_800BCD0C & 7) == 5)
            {
                // TODO: this is likely Game_StateSetPrevious inline
                // but the gameState_594 / gameStatePrev_590 loads inside are switched?

                e_GameState prevPrevState       = g_GameWork.gameStatePrev_590;
                e_GameState prevState           = g_GameWork.gameState_594;
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
            if ((D_800BCD0C & 7) == 5)
            {
                g_GameWork.gameStateStep_598[0] = 0xe;
                g_SysWork.timer_20              = 0;
                D_800BCD0C                      = 7;
                g_GameWork.gameStateStep_598[1] = 0;
                g_GameWork.gameStateStep_598[2] = 0;
                D_801E73E4                      = 0;
            }
            break;

        case 15:
            if ((D_800BCD0C & 7) == 5)
            {
                g_GameWork.gameStateStep_598[0] = 0;
                g_SysWork.timer_20              = 0;
                g_GameWork.gameStateStep_598[1] = 0;
                g_GameWork.gameStateStep_598[2] = 0;
                D_800BCD0C                      = 7;
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
        case 0xd:
            Settings_MainScreen();
            break;
        case 0xe:
        case 0xf:
            Settings_ExtraScreen();
            break;
    }
}

void Settings_ExtraScreen() // 0x801E318C
{
    s_ControllerData* controllerPtr;

    Gfx_OptionsStringsExtraDraw();
    Gfx_SettingsOptionsExtraDraw();
    Gfx_SelectedOptionExtra();
    Gfx_VignetteDraw();
    Gfx_BackgroundSpriteDraw(&D_800A902C);

    if (g_GameWork.gameStateStep_598[0] != 0xe)
    {
        return;
    }

    if (7 < D_801E73E4)
    {
        D_801E73E4 = 8;
    }
    else
    {
        D_801E73E4++;
    }

    if (D_801E73E4 == 8)
    {
        D_801E7300 = D_801E72F8;
        if (((g_GameWork.gameStatePrev_590 == GameState_InGame) && 
			((g_ControllerPtr0->btns_new_10 & g_GameWorkPtr1->config_0.controllerBinds_0.enter) == 0)) &&
            ((g_ControllerPtr0->btns_new_10 & g_GameWorkPtr1->config_0.controllerBinds_0.option) != 0))
        {
            func_80046048(0x51A, 0, 0x40);
            g_GameWork.gameStateStep_598[0] = 5;
            g_SysWork.timer_20              = 0;
            g_GameWork.gameStateStep_598[1] = 0;
            g_GameWork.gameStateStep_598[2] = 0;
            return;
        }
        controllerPtr = g_ControllerPtr0;
        if (controllerPtr->field_18 & Pad_LStickUp)
        {
            s32 var = 1;
            func_80046048(0x519, 0, 0x40);
            D_801E72F8 = ((D_801E72F8 - var) + D_801E73E8) % D_801E73E8;
            D_801E73E4 = 0;
        }
        if (controllerPtr->field_18 & Pad_LStickDown)
        {
            func_80046048(0x519, 0, 0x40);
            D_801E72F8++;
            D_801E72F8 = D_801E72F8 % D_801E73E8;
            D_801E73E4 = 0;
        }

        switch (D_801E72F8)
        {
            case 0:
                if (g_ControllerPtr0->btns_new_10 & (Pad_LStickRight | Pad_LStickLeft))
                {
                    func_80046048(0x519, 0, 0x40);
                    g_GameWork.config_0.optWeaponCtrl_23 = !g_GameWork.config_0.optWeaponCtrl_23;
                }
                break;

            case 1:
                controllerPtr = g_ControllerPtr0;
                if (controllerPtr->btns_new_10 & Pad_LStickRight)
                {
                    func_80046048(0x519, 0, 0x40);
                    D_801E73EC++;
                }
                if (controllerPtr->btns_new_10 & Pad_LStickLeft)
                {
                    func_80046048(0x519, 0, 0x40);
                    D_801E73EC += 3;
                }

                D_801E73EC = D_801E73EC % 4;

                switch (D_801E73EC)
                {
                    case 0:
                        g_GameWork.config_0.optBloodColor_24 = 0;
                        break;

                    case 1:
                        g_GameWork.config_0.optBloodColor_24 = 2;
                        break;

                    case 2:
                        g_GameWork.config_0.optBloodColor_24 = 5;
                        break;

                    case 3:
                        g_GameWork.config_0.optBloodColor_24 = 11;
                        break;
                }
                break;

            case 2:
                if (g_ControllerPtr0->btns_new_10 & (Pad_LStickRight | Pad_LStickLeft))
                {
                    func_80046048(0x519, 0, 0x40);
                    g_GameWork.config_0.optViewCtrl_28 = !g_GameWork.config_0.optViewCtrl_28;
                }
                break;

            case 3:
                if (g_ControllerPtr0->btns_new_10 & (Pad_LStickRight | Pad_LStickLeft))
                {
                    func_80046048(0x519, 0, 0x40);
                    g_GameWork.config_0.optRetreatTurn_2A = (s8)g_GameWork.config_0.optRetreatTurn_2A == 0;
                }
                break;

            case 4:
                if (g_ControllerPtr0->btns_new_10 & (Pad_LStickRight | Pad_LStickLeft))
                {
                    func_80046048(0x519, 0, 0x40);
                    g_GameWork.config_0.optWalkRunCtrl_2B = (s8)g_GameWork.config_0.optWalkRunCtrl_2B == 0;
                }
                break;

            case 5:
                if (g_ControllerPtr0->btns_new_10 & (Pad_LStickRight | Pad_LStickLeft))
                {
                    func_80046048(0x519, 0, 0x40);
                    g_GameWork.config_0.optAutoAiming_2C = (s8)g_GameWork.config_0.optAutoAiming_2C == 0;
                }
                break;

            case 6:
                if (g_ControllerPtr0->btns_new_10 & (Pad_LStickRight | Pad_LStickLeft))
                {
                    func_80046048(0x519, 0, 0x40);
                    g_GameWork.config_0.optViewMode_29 = !g_GameWork.config_0.optViewMode_29;
                }
                break;

            case 7:
                controllerPtr = g_ControllerPtr0;
                if (controllerPtr->btns_new_10 & Pad_LStickRight)
                {
                    func_80046048(0x519, 0, 0x40);
                    g_GameWork.config_0.optBulletAdjust_2D++;
                }
                if (controllerPtr->btns_new_10 & Pad_LStickLeft)
                {
                    func_80046048(0x519, 0, 0x40);
                    g_GameWork.config_0.optBulletAdjust_2D = g_GameWork.config_0.optBulletAdjust_2D + (D_801E73F0 - 1);
                }
                g_GameWork.config_0.optBulletAdjust_2D = g_GameWork.config_0.optBulletAdjust_2D % D_801E73F0;
                break;
        }
    }

    if ((g_ControllerPtr0->btns_new_10 & (g_GameWorkPtr1->config_0.controllerBinds_0.cancel |
		(Pad_L2 | Pad_R2 | Pad_L1 | Pad_R1))) &&
        (g_GameWork.gameStateStep_598[0] != 0xf))
    {
        if (g_ControllerPtr0->btns_new_10 & g_GameWorkPtr1->config_0.controllerBinds_0.cancel)
        {
            func_80046048(0x51A, 0, 0x40);
        }
        else
        {
            func_80046048(0x51B, 0, 0x40);
        }
        D_800BCD0C                      = 2;
        g_GameWork.gameStateStep_598[0] = 0xf;
        g_SysWork.timer_20              = 0;
        g_GameWork.gameStateStep_598[1] = 0;
        g_GameWork.gameStateStep_598[2] = 0;
    }
}

void Settings_MainScreen() // 0x801E3770
{
#define IMAGE_BUFFER_3 ((u_long*)0x801EB600)

    s32               sdCmd;
    s32               newVolume;
    s32               currentVolume;
    s_ControllerData* controllerPtr;
    s_ControllerData* controllerPtr2;

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

    if (7 < D_801E73E4)
    {
        D_801E73E4 = 8;
    }
    else
    {
        D_801E73E4++;
    }

    if (D_801E73E4 != 8)
    {
        return;
    }

    D_801E72FC = D_801E72F4;

    if (((g_GameWork.gameStatePrev_590 == GameState_InGame) && 
		((g_ControllerPtr0->btns_new_10 & g_GameWorkPtr1->config_0.controllerBinds_0.enter) == 0)) &&
        (g_ControllerPtr0->btns_new_10 & g_GameWorkPtr1->config_0.controllerBinds_0.option))
    {
        func_80046048(0x51A, 0, 0x40);
        g_GameWork.gameStateStep_598[0] = 5;
        g_SysWork.timer_20              = 0;
        g_GameWork.gameStateStep_598[1] = 0;
        g_GameWork.gameStateStep_598[2] = 0;
        return;
    }

    controllerPtr = g_ControllerPtr0;
    if (controllerPtr->field_18 & Pad_LStickUp)
    {
        func_80046048(0x519, 0, 0x40);
        D_801E73E4 = 0;
        D_801E72F4 = (D_801E72F4 + 8) % 9;
    }
    if (controllerPtr->field_18 & Pad_LStickDown)
    {
        func_80046048(0x519, 0, 0x40);
        D_801E73E4 = 0;
        D_801E72F4 = (D_801E72F4 + 1) % 9;
    }

    switch (D_801E72F4)
    {
        case 0:
            if (g_ControllerPtr0->btns_new_10 & (g_GameWorkPtr1->config_0.controllerBinds_0.enter |
				g_GameWorkPtr1->config_0.controllerBinds_0.cancel))
            {
                func_80046048(0x51A, 0, 0x40);
                g_GameWork.gameStateStep_598[0] = 5;
                g_SysWork.timer_20              = 0;
                g_GameWork.gameStateStep_598[1] = 0;
                g_GameWork.gameStateStep_598[2] = 0;
            }
            break;

        case 2:
            if (g_ControllerPtr0->btns_new_10 & g_GameWorkPtr1->config_0.controllerBinds_0.enter)
            {
                func_80046048(0x51B, 0, 0x40);
                Fs_QueueStartReadTim(FILE_TIM_OPTION2_TIM, IMAGE_BUFFER_3, &D_800A903C);
                D_800BCD0C                      = 2;
                g_GameWork.gameStateStep_598[0] = 9;
                g_SysWork.timer_20              = 0;
                g_GameWork.gameStateStep_598[1] = 0;
                g_GameWork.gameStateStep_598[2] = 0;
            }
            break;

        case 3:
            if (g_ControllerPtr0->btns_new_10 & g_GameWorkPtr1->config_0.controllerBinds_0.enter)
            {
                func_80046048(0x51B, 0, 0x40);
                D_800BCD0C                      = 2;
                g_GameWork.gameStateStep_598[0] = 7;
                g_SysWork.timer_20              = 0;
                g_GameWork.gameStateStep_598[1] = 0;
                g_GameWork.gameStateStep_598[2] = 0;
            }
            break;

        case 1:
            if (g_ControllerPtr0->btns_new_10 & g_GameWorkPtr1->config_0.controllerBinds_0.enter)
            {
                func_80046048(0x51B, 0, 0x40);
                if (g_GameWork.gameStatePrev_590 == GameState_MainMenu)
                {
                    Fs_QueueStartReadTim(FILE_TIM_OP_BRT_E_TIM, IMAGE_BUFFER_3, &D_800A9044);
                }
                else
                {
                    Fs_QueueStartReadTim(FILE_TIM_OP_BRT_E_TIM, IMAGE_BUFFER_3, &D_800A904C);
                }
                D_800BCD0C                      = 2;
                g_GameWork.gameStateStep_598[0] = 8;
                g_SysWork.timer_20              = 0;
                g_GameWork.gameStateStep_598[1] = 0;
                g_GameWork.gameStateStep_598[2] = 0;
            }
            break;

        case 4:
            if (g_ControllerPtr0->btns_new_10 & (Pad_LStickRight | Pad_LStickLeft))
            {
                func_80046048(0x519, 0, 0x40);
                g_GameWork.config_0.optVibrationEnabled_21 = !g_GameWork.config_0.optVibrationEnabled_21 << 7;
            }
            break;

        case 5:
            if (g_ControllerPtr0->btns_new_10 & (Pad_LStickRight | Pad_LStickLeft))
            {
                func_80046048(0x519, 0, 0x40);
                g_GameWork.config_0.optAutoLoad_25 = (s8)g_GameWork.config_0.optAutoLoad_25 == 0;
            }
            break;

        case 6:
            if (g_ControllerPtr0->btns_new_10 & (Pad_LStickRight | Pad_LStickLeft))
            {
                func_80046048(0x519, 0, 0x40);
                sdCmd                               = 2;
                g_GameWork.config_0.optSoundType_1E = !g_GameWork.config_0.optSoundType_1E;
                if (g_GameWork.config_0.optSoundType_1E)
                {
                    sdCmd = 1;
                }
                Sd_EngineCmd(sdCmd);
            }
            break;

        case 7:
            currentVolume = g_GameWork.config_0.optVolumeBgm_1F;
            if ((currentVolume < 128 && (g_ControllerPtr0->field_18 & Pad_LStickRight)) ||
                (currentVolume > 0 && (g_ControllerPtr0->field_18 & Pad_LStickLeft)))
            {
                Sd_EngineCmd(0x519);
            }
            if ((currentVolume == 128 && (g_ControllerPtr0->btns_new_10 & Pad_LStickRight)) ||
                (currentVolume == 0 && (g_ControllerPtr0->btns_new_10 & Pad_LStickLeft)))
            {
                Sd_EngineCmd(0x518);
            }
            if (g_ControllerPtr0->field_18 & Pad_LStickRight)
            {
                currentVolume = currentVolume + 8;
            }
            if (g_ControllerPtr0->field_18 & Pad_LStickLeft)
            {
                currentVolume = currentVolume - 8;
            }

            currentVolume = currentVolume < 0 ? 0 : (currentVolume > 128 ? 128 : currentVolume);
            newVolume     = currentVolume;

            Sd_SetVolume(128, newVolume, g_GameWork.config_0.optVolumeSe_20);
            g_GameWork.config_0.optVolumeBgm_1F = newVolume;
            break;

        case 8:
            currentVolume = g_GameWork.config_0.optVolumeSe_20;
            if ((currentVolume < 128 && (g_ControllerPtr0->field_18 & Pad_LStickRight)) ||
                (currentVolume > 0 && (g_ControllerPtr0->field_18 & Pad_LStickLeft)))
            {
                Sd_EngineCmd(0x519);
            }
            if ((currentVolume == 128 && (g_ControllerPtr0->btns_new_10 & Pad_LStickRight)) ||
                (currentVolume == 0 && (g_ControllerPtr0->btns_new_10 & Pad_LStickLeft)))
            {
                Sd_EngineCmd(0x518);
            }
            if (g_ControllerPtr0->field_18 & Pad_LStickRight)
            {
                currentVolume = currentVolume + 8;
            }
            if (g_ControllerPtr0->field_18 & Pad_LStickLeft)
            {
                currentVolume = currentVolume - 8;
            }

            currentVolume = currentVolume < 0 ? 0 : (currentVolume > 128 ? 128 : currentVolume);
            newVolume     = currentVolume;

            Sd_SetVolume(128, newVolume, g_GameWork.config_0.optVolumeSe_20);
            g_GameWork.config_0.optVolumeSe_20 = newVolume;
            break;

        default:
            break;
    }

    currentVolume  = 0;
    controllerPtr2 = g_ControllerPtr0;

    if (g_ControllerPtr0->btns_new_10 & (Pad_L2 | Pad_R2 | Pad_L1 | Pad_R1))
    {
        if (g_GameWork.gameStateStep_598[0] == 0xd)
        {
            return;
        }
        func_80046048(0x51B, 0, 0x40);
        D_800BCD0C                      = 2;
        g_GameWork.gameStateStep_598[0] = 0xd;
        g_SysWork.timer_20              = 0;
        g_GameWork.gameStateStep_598[1] = 0;
        g_GameWork.gameStateStep_598[2] = 0;
    }

    if ((((g_GameWork.gameStateStep_598[0] != 0xd) && (D_801E72F4 != 0)) &&
         ((controllerPtr2->btns_new_10 & g_GameWorkPtr1->config_0.controllerBinds_0.enter) == 0)) &&
        (controllerPtr2->btns_new_10 & g_GameWorkPtr1->config_0.controllerBinds_0.cancel))
    {
        func_80046048(0x51A, 0, 0x40);
        D_801E73E4 = 0;
        D_801E72F4 = 0;
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

/** Related to drawing strings.
Generates and draws the bars used for SFX and BGM audio options.
*/
INCLUDE_ASM("asm/screens/options/nonmatchings/options", Gfx_BarDraw); // 0x801E3FB8

/** Related to drawing strings.
Draws the option strings in the extra options screen.
*/
void Gfx_OptionsStringsExtraDraw() // 0x801E416C
{
    s32 i;

    DVECTOR textPos =
        {
            .vx = 0x56,
            .vy = 0x14,
        };

    char* D_801E26CC = "EXTRA_OPTION_\x01\x01\x01\x01\x01S";

    char* D_801E2764[] =
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
            "Bullet_Adjust"};

    if (D_801E73E4 == 0)
    {
        D_801E73B4.vx = 0x30;
        D_801E73B8.vx = 0x40;
        D_801E73B4.vy = ((u16)D_801E72FC * 0x10) + 0x40;
        D_801E73B8.vy = ((u16)D_801E72F4 * 0x10) + 0x40;
    }

    shRsin(D_801E73E4 << 7);
    Gfx_StringSetColor(ColorId_White);
    Gfx_StringSetPosition(textPos.vx, textPos.vy);
    func_8004A8C0(8);
    Gfx_StringDraw(D_801E26CC, 0x63);

    for (i = 0; i < D_801E73E8; i++)
    {
        Gfx_StringSetPosition(0x40, 0x40 + i * 16);
        func_8004A8C0(8);
        Gfx_StringDraw(D_801E2764[i], 0x63);
    }
}

/** Related to drawing strings.
Draws the option strings in the main options screen.
*/
void Gfx_OptionsStringsMainDraw() // 0x801E42EC
{
    s32 i;

    DVECTOR textPos =
        {
            .vx = 0x79,
            .vy = 0x14,
        };

    char* OPTION_ = "OPTION_\x01\x01\x01\x01\x01S";

    char* D_801E280C[] =
        {
            "Exit",
            "Brightness_Level",
            "Controller_Config",
            "Screen_Position",
            "Vibration",
            "Auto_Load",
            "Sound",
            "BGM_Volume",
            "SE_Volume"};

    if (D_801E73E4 == 0)
    {
        D_801E73BC.vx = 0x30;
        D_801E73C0.vx = 0x40;
        D_801E73BC.vy = ((u16)D_801E72FC * 0x10) + 0x38;
        D_801E73C0.vy = ((u16)D_801E72F4 * 0x10) + 0x38;
    }

    shRsin(D_801E73E4 << 7);
    Gfx_StringSetColor(ColorId_White);
    Gfx_StringSetPosition(textPos.vx, textPos.vy);
    func_8004A8C0(8);
    Gfx_StringDraw(OPTION_, 0x63);

    for (i = 0; i < 9; i++)
    {
        Gfx_StringSetPosition(0x40, 0x38 + i * 16);
        func_8004A8C0(8);
        Gfx_StringDraw(D_801E280C[i], 0x63);
    }

    func_8004A8CC();
}

/** Related to drawing.
Draws the buttons next to options and lines indicating the
selected option in the extra options screen.
*/
void Gfx_SelectedOptionExtra() // 0x801E4450
{
    DVECTOR*        vecPtrOut;
    s16             sin;
    s32             j;
    s32             i;
    s_LineVectors   lineVec;
    s_ButtonVectors buttonVec[2];

    u8 D_801E2830[] =
        {
            0x9D, 0x7E, 0x87, 0x87, 0x9D, 0x82, 0x70, 0x86};

    DVECTOR D_801E2838[] =
        {
            {.vx = 0xFF88,
             .vy = 0xFFD1},
            {.vx = 0xFF88,
             .vy = 0xFFDD},
            {.vx = 0xFF94,
             .vy = 0xFFD1},
            {.vx = 0xFF94,
             .vy = 0xFFDD},
        };

    DVECTOR D_801E2848[] =
        {
            {.vx = 0xFF87,
             .vy = 0xFFD0},
            {.vx = 0xFF87,
             .vy = 0xFFDE},
            {.vx = 0xFF95,
             .vy = 0xFFD0},
            {.vx = 0xFF95,
             .vy = 0xFFDE},
        };

    if (D_801E73E4 == 0)
    {
        D_801E73C4.vx = D_801E2830[D_801E7300] + 0xFF87;
        D_801E73C4.vy = (u16)D_801E7300 * 0x10 - 0x32;

        D_801E73C8.vx = D_801E2830[D_801E72F8] + 0xFF87;
        D_801E73C8.vy = (u16)D_801E72F8 * 0x10 - 0x32;
    }

    sin = shRsin(D_801E73E4 << 7);

    lineVec.field_0.vx = -0x79;
    lineVec.field_4.vx = D_801E73C4.vx + FP_FROM((D_801E73C8.vx - D_801E73C4.vx) * sin, Q12_SHIFT);
    lineVec.field_4.vy = D_801E73C4.vy + FP_FROM((D_801E73C8.vy - D_801E73C4.vy) * sin, Q12_SHIFT) + 0x10;
    lineVec.field_0.vy = lineVec.field_4.vy;

    Gfx_LineDraw(&lineVec, 1, 0);

    for (i = 0; i < D_801E73E8; i++)
    {
        vecPtrOut = (DVECTOR*)&buttonVec;

        for (j = 0; j < 4; j++)
        {
            vecPtrOut[j].vx     = D_801E2838[j].vx;
            vecPtrOut[j].vy     = D_801E2838[j].vy + i * 0x10;
            vecPtrOut[j + 4].vx = D_801E2848[j].vx;
            vecPtrOut[j + 4].vy = D_801E2848[j].vy + i * 0x10;
        }

        if (i == D_801E72F8)
        {
            Gfx_ButtonDraw(&buttonVec[0], 0, 0);
            Gfx_ButtonDraw(&buttonVec[1], 1, 0);
        }
        else
        {
            Gfx_ButtonDraw(&buttonVec[0], 0, 1);
            Gfx_ButtonDraw(&buttonVec[1], 1, 1);
        }
    }
}

/** Related to drawing.
Draws the buttons next to options and lines indicating the
selected option in the main options screen.
*/
void Gfx_SelectedOptionMain() // 0x801E472C
{
    DVECTOR*        vecPtrOut;
    s16             sin;
    s32             j;
    s32             i;
    s_LineVectors   lineVec;
    s_ButtonVectors buttonVec[2];

    u8 D_801E2858[] =
        {
            0x3B, 0xA9, 0xAE, 0x9C, 0x68, 0x70, 0x4B, 0x81, 0x70};

    DVECTOR D_801E2864[] =
        {
            {.vx = 0xFF88,
             .vy = 0xFFC9},
            {.vx = 0xFF88,
             .vy = 0xFFD5},
            {.vx = 0xFF94,
             .vy = 0xFFC9},
            {.vx = 0xFF94,
             .vy = 0xFFD5},
        };

    DVECTOR D_801E2874[] =
        {
            {.vx = 0xFF87,
             .vy = 0xFFC8},
            {.vx = 0xFF87,
             .vy = 0xFFD6},
            {.vx = 0xFF95,
             .vy = 0xFFC8},
            {.vx = 0xFF95,
             .vy = 0xFFD6},
        };

    if (D_801E73E4 == 0)
    {
        D_801E73CC.vx = D_801E2858[D_801E72FC] + 0xFF87;
        D_801E73CC.vy = (u16)D_801E72FC * 0x10 - 0x3A;

        D_801E73D0.vx = D_801E2858[D_801E72F4] + 0xFF87;
        D_801E73D0.vy = (u16)D_801E72F4 * 0x10 - 0x3A;
    }

    sin = shRsin(D_801E73E4 << 7);

    lineVec.field_0.vx = -0x79;
    lineVec.field_4.vx = D_801E73CC.vx + FP_FROM((D_801E73D0.vx - D_801E73CC.vx) * sin, Q12_SHIFT);
    lineVec.field_4.vy = D_801E73CC.vy + FP_FROM((D_801E73D0.vy - D_801E73CC.vy) * sin, Q12_SHIFT) + 0x10;
    lineVec.field_0.vy = lineVec.field_4.vy;

    Gfx_LineDraw(&lineVec, 1, 0);

    for (i = 0; i < 9; i++)
    {
        vecPtrOut = (DVECTOR*)&buttonVec;

        for (j = 0; j < 4; j++)
        {
            vecPtrOut[j].vx     = D_801E2864[j].vx;
            vecPtrOut[j].vy     = D_801E2864[j].vy + i * 0x10;
            vecPtrOut[j + 4].vx = D_801E2874[j].vx;
            vecPtrOut[j + 4].vy = D_801E2874[j].vy + i * 0x10;
        }

        if (i == D_801E72F4)
        {
            Gfx_ButtonDraw(&buttonVec[0], 0, 0);
            Gfx_ButtonDraw(&buttonVec[1], 1, 0);
        }
        else
        {
            Gfx_ButtonDraw(&buttonVec[0], 0, 1);
            Gfx_ButtonDraw(&buttonVec[1], 1, 1);
        }
    }
}

/** Related to drawing.
Draws the vignette for the main and extra options screens.
*/
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

        setlen(poly, 8);
        setcode(poly, 0x3A);

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

/** Related to drawing.
Draws the options for each setting used in the extra options screen.
*/
void Gfx_SettingsOptionsExtraDraw() // 0x801E4B2C
{
    s32               textPosX;
    s32               i;
    s32               j;
    s_ControllerData* controllerPtr;

    s_ArrowVectors D_801E2884[] =
        {
            {{0x0026, 0xFFD6}, {0x002E, 0xFFCE}, {0x002E, 0xFFDE}},
            {{0x0078, 0xFFD6}, {0x0070, 0xFFCE}, {0x0070, 0xFFDE}},
            {{0x0026, 0xFFE6}, {0x002E, 0xFFDE}, {0x002E, 0xFFEE}},
            {{0x0078, 0xFFE6}, {0x0070, 0xFFDE}, {0x0070, 0xFFEE}},
            {{0x0023, 0xFFF6}, {0x002B, 0xFFEE}, {0x002B, 0xFFFE}},
            {{0x007B, 0xFFF6}, {0x0073, 0xFFEE}, {0x0073, 0xFFFE}},
            {{0x0023, 0x0006}, {0x002B, 0xFFFE}, {0x002B, 0x000E}},
            {{0x007B, 0x0006}, {0x0073, 0xFFFE}, {0x0073, 0x000E}},
            {{0x0023, 0x0016}, {0x002B, 0x000E}, {0x002B, 0x001E}},
            {{0x007B, 0x0016}, {0x0073, 0x000E}, {0x0073, 0x001E}},
            {{0x0033, 0x0026}, {0x003B, 0x001E}, {0x003B, 0x002E}},
            {{0x006B, 0x0026}, {0x0063, 0x001E}, {0x0063, 0x002E}},
            {{0x0018, 0x0036}, {0x0020, 0x002E}, {0x0020, 0x003E}},
            {{0x0083, 0x0036}, {0x007B, 0x002E}, {0x007B, 0x003E}},
            {{0x0039, 0x0046}, {0x0041, 0x003E}, {0x0041, 0x004E}},
            {{0x0068, 0x0046}, {0x0060, 0x003E}, {0x0060, 0x004E}}};

    s_ArrowVectors D_801E2944[] =
        {
            {{0x0025, 0xFFD6}, {0x002F, 0xFFCC}, {0x002F, 0xFFE0}},
            {{0x0079, 0xFFD6}, {0x006F, 0xFFCC}, {0x006F, 0xFFE0}},
            {{0x0025, 0xFFE6}, {0x002F, 0xFFDC}, {0x002F, 0xFFF0}},
            {{0x0079, 0xFFE6}, {0x006F, 0xFFDC}, {0x006F, 0xFFF0}},
            {{0x0022, 0xFFF6}, {0x002C, 0xFFEC}, {0x002C, 0x0000}},
            {{0x007C, 0xFFF6}, {0x0072, 0xFFEC}, {0x0072, 0x0000}},
            {{0x0022, 0x0006}, {0x002C, 0xFFFC}, {0x002C, 0x0010}},
            {{0x007C, 0x0006}, {0x0072, 0xFFFC}, {0x0072, 0x0010}},
            {{0x0022, 0x0016}, {0x002C, 0x000C}, {0x002C, 0x0020}},
            {{0x007C, 0x0016}, {0x0072, 0x000C}, {0x0072, 0x0020}},
            {{0x0032, 0x0026}, {0x003C, 0x001C}, {0x003C, 0x0030}},
            {{0x006C, 0x0026}, {0x0062, 0x001C}, {0x0062, 0x0030}},
            {{0x0017, 0x0036}, {0x0021, 0x002C}, {0x0021, 0x0040}},
            {{0x0084, 0x0036}, {0x007A, 0x002C}, {0x007A, 0x0040}},
            {{0x0038, 0x0046}, {0x0042, 0x003C}, {0x0042, 0x0050}},
            {{0x0069, 0x0046}, {0x005F, 0x003C}, {0x005F, 0x0050}}};

    char* D_801E2A6C[] =
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
            "x6"};

    Gfx_StringSetColor(ColorId_White);

    if (D_801E72F8 < 8U)
    {
        for (i = 0; i < 2; i++)
        {
            Gfx_ArrowDraw(&D_801E2884[D_801E72F8 * 2 + i], 1, 0);
        }

        controllerPtr = g_ControllerPtr0;
        if (controllerPtr->btns_held_C & Pad_LStickLeft)
        {
            Gfx_ArrowDraw(&D_801E2944[D_801E72F8 << 1], 0, 0);
        }
        if (controllerPtr->btns_held_C & Pad_LStickRight)
        {
            Gfx_ArrowDraw(&D_801E2944[(D_801E72F8 << 1) + 1], 0, 0);
        }
    }

    for (j = 0; j < D_801E73E8; j++)
    {
        switch (j)
        {
            case 0:
                textPosX = g_GameWork.config_0.optWeaponCtrl_23 != 0 ? 0xD9 : 0xD4;
                Gfx_StringSetPosition(textPosX, 0x40);
                Gfx_StringDraw(D_801E2A6C[!g_GameWork.config_0.optWeaponCtrl_23], 0xA);
                break;

            case 1:
                switch (D_801E73EC)
                {
                    case 0:
                        Gfx_StringSetPosition(0xD2, 0x50);
                        break;

                    case 1:
                        Gfx_StringSetPosition(0xD6, 0x50);
                        break;

                    case 2:
                        Gfx_StringSetPosition(0xD6, 0x50);
                        break;

                    case 3:
                        Gfx_StringSetPosition(0xD9, 0x50);
                        break;
                }
                Gfx_StringDraw(D_801E2A6C[D_801E73EC + 2], 0xA);
                break;

            case 2:
                textPosX = g_GameWork.config_0.optViewCtrl_28 == 0 ? 0xD2 : 0xCE;
                Gfx_StringSetPosition(textPosX, 0x60);
                Gfx_StringDraw(D_801E2A6C[(g_GameWork.config_0.optViewCtrl_28 != 0 ? 0x20 : 0x1C) >> 2], 0xA);
                break;

            case 3:
                textPosX = g_GameWork.config_0.optRetreatTurn_2A == 0 ? 0xD2 : 0xCE;
                Gfx_StringSetPosition(textPosX, 0x70);
                Gfx_StringDraw(D_801E2A6C[(g_GameWork.config_0.optRetreatTurn_2A != 0 ? 0x20 : 0x1C) >> 2], 0xA);
                break;

            case 4:
                textPosX = g_GameWork.config_0.optWalkRunCtrl_2B == 0 ? 0xD2 : 0xCE;
                Gfx_StringSetPosition(textPosX, 0x80);
                Gfx_StringDraw(D_801E2A6C[(g_GameWork.config_0.optWalkRunCtrl_2B != 0 ? 0x20 : 0x1C) >> 2], 0xA);
                break;

            case 5:
                textPosX = g_GameWork.config_0.optAutoAiming_2C == 0 ? 0xE4 : 0xE2;
                Gfx_StringSetPosition(textPosX, 0x90);
                Gfx_StringDraw(D_801E2A6C[(g_GameWork.config_0.optAutoAiming_2C != 0 ? 0x28 : 0x24) >> 2], 0xA);
                break;

            case 6:
                textPosX = g_GameWork.config_0.optViewMode_29 == 0 ? 0xD2 : 0xC8;
                Gfx_StringSetPosition(textPosX, 0xA0);
                Gfx_StringDraw(D_801E2A6C[(g_GameWork.config_0.optViewMode_29 ? 0x30 : 0x2C) >> 2], 0xA);
                break;

            case 7:
                Gfx_StringSetPosition(0xE6, 0xB0);
                Gfx_StringDraw(D_801E2A6C[g_GameWork.config_0.optBulletAdjust_2D + 0xD], 0xA);
                break;
        }
    }
}

/** Related to drawing.
Draws the options for each setting used in the main options screen.
*/
void Gfx_SettingsOptionsMainDraw() // 0x801E4FFC
{
    s32               textPosX;
    s32               i;
    s32               stringIdx;
    s_ControllerData* controllerPtr;

    s_ArrowVectors D_801E2AD8[] =
        {
            {{0x0028, 0x000E}, {0x0030, 0x0006}, {0x0030, 0x0016}},
            {{0x0060, 0x000E}, {0x0058, 0x0006}, {0x0058, 0x0016}},
            {{0x0028, 0x001E}, {0x0030, 0x0016}, {0x0030, 0x0026}},
            {{0x0060, 0x001E}, {0x0058, 0x0016}, {0x0058, 0x0026}},
            {{0x0013, 0x002E}, {0x001B, 0x0026}, {0x001B, 0x0036}},
            {{0x007C, 0x002E}, {0x0074, 0x0026}, {0x0074, 0x0036}},
            {{0x000C, 0x003E}, {0x0014, 0x0036}, {0x0014, 0x0046}},
            {{0x0083, 0x003E}, {0x007B, 0x0036}, {0x007B, 0x0046}},
            {{0x000C, 0x004E}, {0x0014, 0x0046}, {0x0014, 0x0056}},
            {{0x0083, 0x004E}, {0x007B, 0x0046}, {0x007B, 0x0056}},
        };

    s_ArrowVectors D_801E2B50[] =
        {
            {{0x0027, 0x000E}, {0x0031, 0x0004}, {0x0031, 0x0018}},
            {{0x0061, 0x000E}, {0x0057, 0x0004}, {0x0057, 0x0018}},
            {{0x0027, 0x001E}, {0x0031, 0x0014}, {0x0031, 0x0028}},
            {{0x0061, 0x001E}, {0x0057, 0x0014}, {0x0057, 0x0028}},
            {{0x0012, 0x002E}, {0x001C, 0x0024}, {0x001C, 0x0038}},
            {{0x007D, 0x002E}, {0x0073, 0x0024}, {0x0073, 0x0038}},
            {{0x000B, 0x003E}, {0x0015, 0x0034}, {0x0015, 0x0048}},
            {{0x0084, 0x003E}, {0x007A, 0x0034}, {0x007A, 0x0048}},
            {{0x000B, 0x004E}, {0x0015, 0x0044}, {0x0015, 0x0058}},
            {{0x0084, 0x004E}, {0x007A, 0x0044}, {0x007A, 0x0058}},
        };

    char* D_801E2BDC[] =
        {
            "On",
            "Off",
            "Stereo",
            "Monaural",
        };

    Gfx_StringSetColor(ColorId_White);

    if ((D_801E72F4 - 4) < 5U)
    {
        for (i = 0; i < 2; i++)
        {
            Gfx_ArrowDraw(&D_801E2AD8[(((D_801E72F4 - 4) * 2) + i)], 1, 0);
        }

        controllerPtr = g_ControllerPtr0;
        if (controllerPtr->btns_held_C & Pad_LStickLeft)
        {
            Gfx_ArrowDraw(&D_801E2B50[(D_801E72F4 - 4) << 1], 0, 0);
        }
        if (controllerPtr->btns_held_C & Pad_LStickRight)
        {
            Gfx_ArrowDraw(&D_801E2B50[((D_801E72F4 - 4) << 1) + 1], 0, 0);
        }
    }

    for (i = 0; i < 3; i++)
    {
        switch (i)
        {
            case 0:
                textPosX = g_GameWork.config_0.optVibrationEnabled_21 == 0 ? 0xD6 : 0xD8;
                Gfx_StringSetPosition(textPosX, 0x78);
                stringIdx = g_GameWork.config_0.optVibrationEnabled_21 == 0;
                Gfx_StringDraw(D_801E2BDC[stringIdx], 0xA);
                break;

            case 1:
                textPosX = g_GameWork.config_0.optAutoLoad_25 == 0 ? 0xD6 : 0xD8;
                Gfx_StringSetPosition(textPosX, 0x88);
                stringIdx = g_GameWork.config_0.optAutoLoad_25 == 0;
                Gfx_StringDraw(D_801E2BDC[stringIdx], 0xA);
                break;

            case 2:
                textPosX = g_GameWork.config_0.optSoundType_1E != 0 ? 0xC2 : 0xCE;
                Gfx_StringSetPosition(textPosX, 0x98);
                stringIdx = g_GameWork.config_0.optSoundType_1E + 2;
                Gfx_StringDraw(D_801E2BDC[stringIdx], 0xA);
                break;
        }
    }
}

// ==============================
// SCREEN POSITION OPTION SCREEN
// ==============================

INCLUDE_ASM("asm/screens/options/nonmatchings/options", Settings_PositionScreen); // 0x801E53A0 

INCLUDE_ASM("asm/screens/options/nonmatchings/options", Gfx_PositionArrowsDraw); // 0x801E5A08

/** Related to drawing.
Draws the box that indicates the screen position in the
position screen configuration.
*/
INCLUDE_ASM("asm/screens/options/nonmatchings/options", Gfx_PositionIndicatorDraw); // 0x801E5CBC

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
            D_800BCD0C = 6;
            g_GameWork.gameStateStep_598[1] = 2;
            g_GameWork.gameStateStep_598[2] = 0;
            break;

        case 2:
            if (g_ControllerPtr0->field_18 & Pad_LStickLeft)
            {
                if (g_GameWork.config_0.optBrightness_22 != 0)
                {
                    g_GameWork.config_0.optBrightness_22--;
                    func_80046048(0x519, 0, 0x40);
                }
            }

            if (g_ControllerPtr0->field_18 & Pad_LStickRight)
            {
                if (g_GameWork.config_0.optBrightness_22 < 7)
                {
                    g_GameWork.config_0.optBrightness_22++;
                    func_80046048(0x519, 0, 0x40);
                }
            }

            if (g_ControllerPtr0->btns_new_10 & (g_GameWorkPtr1->config_0.controllerBinds_0.enter | g_GameWorkPtr1->config_0.controllerBinds_0.cancel))
            {
                if (g_ControllerPtr0->btns_new_10 & g_GameWorkPtr1->config_0.controllerBinds_0.enter)
                {
                    func_80046048(0x51B, 0, 0x40);
                }
                else
                {
                    func_80046048(0x51A, 0, 0x40);
                }

                D_800BCD0C = 2;
                g_GameWork.gameStateStep_598[1]++;
                g_GameWork.gameStateStep_598[2] = 0;
            }
            break;

        case 3:
            if (D_800BCD0C & (1 << 2) && (D_800BCD0C & (1 << 1)) == 0 && D_800BCD0C & (1 << 0))
            {
                D_800BCD0C = (1 << 2) | (1 << 1);
                g_GameWork.gameStateStep_598[0] = 11;
                g_SysWork.timer_20 = 0;
                g_GameWork.gameStateStep_598[1] = 0;
                g_GameWork.gameStateStep_598[2] = 0;
                g_GameWork.field_58C = 0;
                g_GameWork.field_58D = 0;
                g_GameWork.field_58E = 0;
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

// TODO: Matched but .rodata needs to be redefined.
INCLUDE_ASM("asm/screens/options/nonmatchings/options", Gfx_BrightnessLevelTextDraw);
/*void Gfx_BrightnessLevelTextDraw() // 0x801E6238
{
    char* D_801E2C64 = "LEVEL_________";

    Gfx_StringSetColor(ColorId_White);
    Gfx_StringSetPosition(SCREEN_POSITION_X(25.0f), SCREEN_POSITION_Y(79.5f));
    Gfx_StringDraw(D_801E2C64, 20);
    Gfx_StringDrawInt(1, g_GameWork.config_0.optBrightness_22);
}*/

// TODO: Matched but .rodata needs to be redefined.
INCLUDE_ASM("asm/screens/options/nonmatchings/options", Gfx_BrightnessLevelArrowsDraw);
/*void Gfx_BrightnessLevelArrowsDraw() // 0x801E628C
{
    // D_801E2C74
    s_801E2C74 var0 =
    {
        {
            8, 84,
            16, 76,
            16, 92,

            64, 84,
            56, 76,
            56, 92,
        }
    };

    // D_801E2C8C
    s_801E2C74 var1 =
    {
        {
            7, 84,
            17, 74,
            17, 94,

            65, 84,
            55, 74,
            55, 94,
        }
    };

    s32 btnInput;
    s32 i;
    s32 dir;

    btnInput = g_ControllerPtr0->btns_held_C;

    // Determine direction.
    if (btnInput & Pad_LStickLeft)
    {
        dir = 1;
    }
    else if (btnInput & Pad_LStickRight)
    {
        dir = 2;
    }
    else
    {
        dir = 0;
    }

    for (i = 0; i < 2; i++)
    {
        Gfx_ArrowDraw(&var0.field_0[i], 1, 0);
    }

    for (i = dir - 1; i < dir; i++)
    {
        Gfx_ArrowDraw(&var1.field_0[i], 0, 0);
    }
}*/

// ========================================
// DRAW OPTIONS FEATURES SCREEN
// ========================================

/** Related to drawing.
Draws the line on the selected option in options screens.
*/
void Gfx_LineDraw(s_LineVectors* vec, s32 arg1, s32 arg2) // 0x801E641C
{
    GsOT*          ot = &g_ObjectTable1[g_ObjectTableIdx];
    LINE_G2*       line;
    s_LineVectors* vecPtr;

    line   = (LINE_G2*)GsOUT_PACKET_P;
    vecPtr = vec;

    setLineG2(line);

    if (arg2)
    {
        *((u32*)&line->r0) = 0x50B0B0B0;
        *((u32*)&line->r1) = 0x504080A0;
    }
    else
    {
        *((u32*)&line->r0) = 0x50B0B0B0;
        *((u32*)&line->r1) = 0x504080A0;
    }

    setXY0Fast(line, vecPtr->field_0.vx, vecPtr->field_0.vy);
    setXY1Fast(line, vecPtr->field_4.vx, vecPtr->field_4.vy);

    addPrim((u8*)ot->org + (arg1 ? 0x24 : 0x18), line);

    GsOUT_PACKET_P = (u8*)line + sizeof(LINE_G2);

    if (arg1 != 0)
    {
        POLY_G4* poly = (POLY_G4*)GsOUT_PACKET_P;

        setlen(poly, 8);
        setcode(poly, 0x3A);
        setRGB0(poly, 0, 0, 0);
        setRGB1(poly, 0x60, 0x60, 0x60);
        setRGB2(poly, 0, 0, 0);
        setRGB3(poly, 0x60, 0x60, 0x60);
        setXY4(poly, vecPtr->field_0.vx, vecPtr->field_0.vy - 0x10, vecPtr->field_0.vx, vecPtr->field_0.vy,
               vecPtr->field_4.vx, vecPtr->field_4.vy - 0x10, vecPtr->field_4.vx, vecPtr->field_4.vy);

        addPrim((u8*)ot->org + 0x24, poly);

        GsOUT_PACKET_P = (u8*)poly + sizeof(POLY_G4);

        func_80052088(0, 0, 9, 2);
    }
}

/** Related to drawing.
Draws the arrows used in options screens.
*/
void Gfx_ArrowDraw(s_ArrowVectors* vec, s32 arg1, s32 arg2) // 0x801E662C
{
    GsOT*    ot = &g_ObjectTable1[g_ObjectTableIdx];
    s32      timerCount;
    s32      colorMod0;
    s32      colorMod1;
    POLY_G3* poly;

    if (arg2)
    {
        do
        {
        } while (0); // HACK: probably some unused code related to arg2
    }

    timerCount = g_SysWork.timer_1C & 0x7F;

    if (timerCount >= 0x20)
    {
        if (timerCount < 0x40)
        {
            colorMod1 = 0x20;
        }
        else if (timerCount < 0x60)
        {
            colorMod1 = 0x60 - timerCount;
        }
        else
        {
            colorMod1 = 0;
        }
    }
    else
    {
        colorMod1 = timerCount;
    }

    if (timerCount >= 0x20)
    {
        if (timerCount < 0x40)
        {
            colorMod0 = timerCount - 0x20;
        }
        else if (timerCount >= 0x60)
        {
            colorMod0 = 0x80 - timerCount;
        }
        else
        {
            colorMod0 = 0x20;
        }
    }
    else
    {
        colorMod0 = 0;
    }

    poly = (POLY_G3*)GsOUT_PACKET_P;
    setPolyG3(poly);

    if (arg1 != 0)
    {
        *((u32*)&poly->r0) = (colorMod0 * 0x700) + 0x30FF0000;
        *((u32*)&poly->r1) = (colorMod1 * 0x700) + 0x30FF0000;
        *((u32*)&poly->r2) = (colorMod1 * 0x700) + 0x30FF0000;
    }
    else
    {
        *((u32*)&poly->r0) = 0x30F0F000;
        *((u32*)&poly->r1) = 0x30F0F000;
        *((u32*)&poly->r2) = 0x30F0F000;
    }

    setXY0Fast(poly, vec->field_0.vx, vec->field_0.vy);
    setXY1Fast(poly, vec->field_4.vx, vec->field_4.vy);
    setXY2Fast(poly, vec->field_8.vx, vec->field_8.vy);

    addPrim((u8*)ot->org + 0x28, poly);
    GsOUT_PACKET_P = (u8*)poly + sizeof(POLY_G3);
}

/** Related to drawing.
Draws the button next to options in the main and extra option screens.
*/
void Gfx_ButtonDraw(s_ButtonVectors* vec, s32 arg1, s32 arg2) // 0x801E67B0
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
                    *((u32*)&poly->r0) = 0x30FFFFFF;
                    *((u32*)&poly->r1) = 0x304080A0;
                    *((u32*)&poly->r2) = 0x30404040;
                    break;

                case 1:
                    *((u32*)&poly->r0) = 0x30808080;
                    *((u32*)&poly->r1) = 0x30102028;
                    *((u32*)&poly->r2) = 0x30101010;
                    break;
            }

            if (i != 0)
            {
                setXY0Fast(poly, vec->field_0.vx, vec->field_0.vy);
                setXY1Fast(poly, vec->field_4.vx, vec->field_4.vy);
                setXY2Fast(poly, vec->field_C.vx, vec->field_C.vy);
            }
            else
            {
                setXY0Fast(poly, vec->field_0.vx, vec->field_0.vy);
                setXY1Fast(poly, vec->field_8.vx, vec->field_8.vy);
                setXY2Fast(poly, vec->field_C.vx, vec->field_C.vy);
            }
        }
        else
        {
            switch (arg2)
            {
                case 0:
                    *((u32*)&poly->r0) = 0x304080A0;
                    *((u32*)&poly->r1) = 0x30FFFFFF;
                    *((u32*)&poly->r2) = 0x30FFFFFF;
                    break;

                case 1:
                    *((u32*)&poly->r0) = 0x30204050;
                    *((u32*)&poly->r1) = 0x30A0A0A0;
                    *((u32*)&poly->r2) = 0x30A0A0A0;
                    break;
            }

            if (i != 0)
            {
                setXY0Fast(poly, vec->field_C.vx, vec->field_C.vy);
                setXY1Fast(poly, vec->field_4.vx, vec->field_4.vy);
                setXY2Fast(poly, vec->field_8.vx, vec->field_8.vy);
            }
            else
            {
                setXY0Fast(poly, vec->field_0.vx, vec->field_0.vy);
                setXY1Fast(poly, vec->field_4.vx, vec->field_4.vy);
                setXY2Fast(poly, vec->field_8.vx, vec->field_8.vy);
            }
        }

        addPrim((u8*)ot->org + 0x18, poly);
        GsOUT_PACKET_P = (u8*)poly + sizeof(POLY_G3);
    }
}

// ========================================
// CONTROLS OPTION SCREEN
// ========================================

INCLUDE_ASM("asm/screens/options/nonmatchings/options", Settings_ControllerScreen); // 0x801E69BC

/** Related to controller mapping.
Changes the button mapping based on the input.
*/
INCLUDE_ASM("asm/screens/options/nonmatchings/options", Settings_ButtonChange); // 0x801E6CF4

INCLUDE_ASM("asm/screens/options/nonmatchings/options", Gfx_ControllerScreenDraw); // 0x801E6F60

INCLUDE_ASM("asm/screens/options/nonmatchings/options", Gfx_ControllerButtonsDraw); // 0x801E716C
