#include "game.h"

#include "bodyprog/bodyprog.h"
#include "bodyprog/sound_system.h"
#include "bodyprog/screen/screen_draw.h"

void Settings_ScreenAndVolUpdate(void) // 0x800333CC
{
    Screen_XyPositionSet(g_GameWork.config_0.optScreenPosX_1C, g_GameWork.config_0.optScreenPosY_1D);
    SD_Call((g_GameWork.config_0.optSoundType_1E != 0) ? AUDIO_TYPE_MONO : AUDIO_TYPE_STEREO);
    Sd_SetVolume(OPT_SOUND_VOLUME_MAX, g_GameWork.config_0.optVolumeBgm_1F, g_GameWork.config_0.optVolumeSe_20);
}

void Settings_RestoreDefaults(void) // 0x8003342C
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

void Settings_RestoreControlDefaults(s32 configIdx) // 0x80033480
{
    u32  i;
    u16* ptr;

    static const s_ControllerConfig DEFAULT_CONTROLLER_CONFIGS[3] = {
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

    for (i = 0, ptr = &g_GameWorkPtr->config_0.controllerConfig_0; i < INPUT_ACTION_COUNT; i++, ptr++)
    {
        *ptr = (&DEFAULT_CONTROLLER_CONFIGS[configIdx].enter_0)[i];
    }
}

const s32 pad_rodata_80025170[2] = {};

void nullsub_800334C8(void) {} // 0x800334C8

void func_800334D0(void) {} // 0x800334D0
