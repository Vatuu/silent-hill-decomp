#include "game.h"

#include <memory.h>
#include <psyq/libetc.h>

#include "bodyprog/bodyprog.h"
#include "bodyprog/gamemain.h"
#include "bodyprog/demo.h"
#include "bodyprog/screen/screen_draw.h"
#include "bodyprog/joy.h"
#include "bodyprog/math/math.h"
#include "bodyprog/sound_system.h"

void SysWork_Clear(void) // 0x800340E0
{
    bzero(&g_SysWork, sizeof(s_SysWork));
}

s32 MainLoop_ShouldWarmReset(void) // 0x80034108
{
    #define WARM_BOOT_COMBO_HOLD      (ControllerFlag_Select | ControllerFlag_Start)
    #define WARM_BOOT_COMBO_PRESS     (ControllerFlag_Select | ControllerFlag_Start | \
                                       ControllerFlag_L2 | ControllerFlag_R2 | ControllerFlag_L1 | ControllerFlag_R1)
    #define WARM_BOOT_COMBO_PRESS_ALT (ControllerFlag_Start | ControllerFlag_Triangle | ControllerFlag_Square)

    if (g_GameWork.gameState_594 < GameState_MovieIntroAlternate)
    {
        return ResetType_None;
    }

    if (g_GameWork.gameState_594 == GameState_LoadSavegameScreen && g_GameWork.gameStateStep_598[0] == 4)
    {
        return ResetType_None;
    }

    if (g_GameWork.gameState_594 == GameState_SaveScreen &&
        (g_GameWork.gameStateStep_598[0] == 2 || g_GameWork.gameStateStep_598[0] == 3))
    {
        return ResetType_None;
    }

    if (g_SysWork.flags_22A4 & SysFlag2_1)
    {
        if (g_Demo_FrameCount > (TICKS_PER_SECOND * 30))
        {
            return ResetType_WarmBoot;
        }
    }
    else
    {
        g_Demo_FrameCount = ResetType_None;
    }

    if (g_GameWork.gameState_594 == GameState_MainMenu)
    {
        return ResetType_None;
    }

    // Reset frame counter if reset buttons not held.
    if ((g_Controller0->btnsHeld_C & WARM_BOOT_COMBO_HOLD) != WARM_BOOT_COMBO_HOLD)
    {
        g_WarmBootTimer = 0;
    }

    if (g_WarmBootTimer > (TICKS_PER_SECOND * 2))
    {
        return ResetType_WarmBoot;
    }
    else if (g_Controller0->btnsHeld_C == WARM_BOOT_COMBO_PRESS && (g_Controller0->btnsClicked_10 & WARM_BOOT_COMBO_PRESS))
    {
        return ResetType_WarmBoot;
    }
    else if (g_Controller0->btnsHeld_C == WARM_BOOT_COMBO_PRESS_ALT && (g_Controller0->btnsClicked_10 & ControllerFlag_Start))
    {
        return ResetType_WarmBoot;
    }

    return (g_SysWork.flags_22A4 & SysFlag2_8) ? ResetType_WarmBoot : ResetType_None;

    #undef WARM_BOOT_COMBO_HOLD
    #undef WARM_BOOT_COMBO_PRESS
    #undef WARM_BOOT_COMBO_PRESS_ALT
}

void Game_WarmBoot(void) // 0x80034264
{
    e_GameState prevState;

    DrawSync(SyncMode_Wait);
    Screen_RectInterlacedClear(0, 32, 512, 448, 0, 0, 0);
    func_800892A4(4);
    func_80089128();
    SD_Call(19);

    while (Sd_AudioStreamingCheck())
    {
        Sd_TaskPoolExecute();
        VSync(SyncMode_Wait);
    }

    SD_Call(20);

    while (Sd_AudioStreamingCheck())
    {
        Sd_TaskPoolExecute();
        VSync(SyncMode_Wait);
    }

    Fs_QueueReset();
    Fs_QueueWaitForEmpty();
    sd_work_init();
    Sd_AmbientSfxSet(1);

    while (Sd_AudioStreamingCheck())
    {
        Sd_TaskPoolExecute();
        VSync(SyncMode_Wait);
    }

    if (g_SysWork.flags_22A4 & SysFlag2_1)
    {
        Demo_Stop();
    }

    SysWork_Clear();
    Demo_SequenceAdvance(1);
    Demo_DemoDataRead();
    GameFs_TitleGfxLoad();
    Fs_QueueWaitForEmpty();
    Joy_Update();

    prevState                = g_GameWork.gameState_594;
    g_GameWork.gameState_594 = GameState_MainMenu;

    g_SysWork.timer_1C = 0;
    g_SysWork.timer_20 = 0;

    g_GameWork.gameStateStep_598[1] = 0;
    g_GameWork.gameStateStep_598[2] = 0;

    SysWork_StateSetNext(SysState_Gameplay);

    ScreenFade_Start(true, true, false);

    g_GameWork.gameStateStep_598[0] = prevState;
    g_GameWork.gameStatePrev_590    = prevState;
    g_GameWork.gameStateStep_598[0] = 0;

    g_ScreenFadeTimestep = Q12(0.0f);
}
