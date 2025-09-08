#include "game.h"

#include "bodyprog/bodyprog.h"
#include "bodyprog/gfx/screen_draw.h"

void Settings_ScreenAndVolUpdate() // 0x800333CC
{
    Screen_XyPositionSet(g_GameWork.config_0.optScreenPosX_1C, g_GameWork.config_0.optScreenPosY_1D);
    Sd_EngineCmd((g_GameWork.config_0.optSoundType_1E != 0) ? 1 : 2);
    Sd_SetVolume(OPT_SOUND_VOLUME_MAX, g_GameWork.config_0.optVolumeBgm_1F, g_GameWork.config_0.optVolumeSe_20);
}

void Settings_RestoreDefaults() // 0x8003342C
{
    g_GameWork.config_0.optExtraWeaponCtrl_23 = 1;
    g_GameWork.config_0.optBrightness_22      = 3;

    Settings_RestoreControlDefaults(0);

    g_GameWork.config_0.optVibrationEnabled_21 = OPT_VIBRATION_ENABLED;
    g_GameWork.config_0.optVolumeBgm_1F        = OPT_SOUND_VOLUME_MAX;
    g_GameWork.config_0.optVolumeSe_20         = OPT_SOUND_VOLUME_MAX;

    Settings_ScreenAndVolUpdate();

    g_GameWork.config_0.optExtraBloodColor_24 = 0;
}

void Settings_RestoreControlDefaults(s32 arg0) // 0x80033480
{
    u32  i;
    u16* ptr;

    static const s_ControllerConfig DEFAULT_CONTROLLER_CONFIGS[3] =
    {
        {
            .enter_0      = ControllerFlag_Start | ControllerFlag_Cross,
            .cancel_2     = ControllerFlag_Triangle | ControllerFlag_Circle | ControllerFlag_Square,
            .skip_4       = ControllerFlag_Start,
            .action_6     = ControllerFlag_Cross,
            .aim_8        = ControllerFlag_R2,
            .light_A      = ControllerFlag_Circle,
            .run_C        = ControllerFlag_Square,
            .view_E       = ControllerFlag_L2,
            .stepLeft_10  = ControllerFlag_L1,
            .stepRight_12 = ControllerFlag_R1,
            .pause_14     = ControllerFlag_Start,
            .item_16      = ControllerFlag_Select,
            .map_18       = ControllerFlag_Triangle,
            .option_1A    = ControllerFlag_None
        },
        {
            .enter_0      = ControllerFlag_Start | ControllerFlag_Cross,
            .cancel_2     = ControllerFlag_Triangle | ControllerFlag_Circle | ControllerFlag_Square,
            .skip_4       = ControllerFlag_Start,
            .action_6     = ControllerFlag_Cross,
            .aim_8        = ControllerFlag_R1,
            .light_A      = ControllerFlag_Circle,
            .run_C        = ControllerFlag_Square,
            .view_E       = ControllerFlag_L1,
            .stepLeft_10  = ControllerFlag_L2,
            .stepRight_12 = ControllerFlag_R2,
            .pause_14     = ControllerFlag_Start,
            .item_16      = ControllerFlag_Select,
            .map_18       = ControllerFlag_Triangle,
            .option_1A    = ControllerFlag_None
        },
        {
            .enter_0      = ControllerFlag_Start | ControllerFlag_Cross,
            .cancel_2     = ControllerFlag_Triangle | ControllerFlag_Circle | ControllerFlag_Square,
            .skip_4       = ControllerFlag_Start,
            .action_6     = ControllerFlag_Cross,
            .aim_8        = ControllerFlag_R2,
            .light_A      = ControllerFlag_Circle,
            .run_C        = ControllerFlag_Square,
            .view_E       = ControllerFlag_L2,
            .stepLeft_10  = ControllerFlag_L1,
            .stepRight_12 = ControllerFlag_R1,
            .pause_14     = ControllerFlag_Start,
            .item_16      = ControllerFlag_Triangle,
            .map_18       = ControllerFlag_Select,
            .option_1A    = ControllerFlag_None
        }
    };

    static const u8 __PAD[8] = {};

    for (i = 0, ptr = &g_GameWorkPtr->config_0.controllerConfig_0; i < INPUT_ACTION_COUNT; i++, ptr++)
    {
        *ptr = (&DEFAULT_CONTROLLER_CONFIGS[arg0].enter_0)[i];
    }
}

void nullsub_800334C8() {}

void func_800334D0() {}
