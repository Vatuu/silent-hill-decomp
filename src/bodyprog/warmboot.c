#include "game.h"

#include <libetc.h>
#include <memory.h>

#include "bodyprog/bodyprog.h"
#include "bodyprog/demo.h"
#include "bodyprog/gfx/screen_draw.h"
#include "bodyprog/joy.h"
#include "bodyprog/math/math.h"

void SysWork_Clear() // 0x800340E0
{
    bzero(&g_SysWork, sizeof(s_SysWork));
}

s32 MainLoop_ShouldWarmReset() // 0x80034108
{
    #define RESET_BTN_FLAGS (ControllerFlag_Select | ControllerFlag_Start)
    #define UNK_BTN_FLAGS_0 (ControllerFlag_Select | ControllerFlag_Start | ControllerFlag_L2 | ControllerFlag_R2 | ControllerFlag_L1 | ControllerFlag_R1)
    #define UNK_BTN_FLAGS_1 (ControllerFlag_Start | ControllerFlag_Triangle | ControllerFlag_Square)

    if (g_GameWork.gameState_594 < GameState_MovieIntroAlternate)
    {
        return 0;
    }

    if (g_GameWork.gameState_594 == GameState_SaveScreen && g_GameWork.gameStateStep_598[0] == 4)
    {
        return 0;
    }

    if (g_GameWork.gameState_594 == GameState_Unk10 && (g_GameWork.gameStateStep_598[0] == 2 || g_GameWork.gameStateStep_598[0] == 3))
    {
        return 0;
    }

    if (g_SysWork.flags_22A4 & (1 << 1))
    {
        if (g_Demo_FrameCount > (TICKS_PER_SECOND * 30))
        {
            return 2;
        }
    }
    else
    {
        g_Demo_FrameCount = 0;
    }

    if (g_GameWork.gameState_594 == GameState_MainMenu)
    {
        return 0;
    }

    // Reset something.
    if ((g_Controller0->btnsHeld_C & RESET_BTN_FLAGS) != RESET_BTN_FLAGS)
    {
        g_UnknownFrameCounter = 0;
    }

    if (g_UnknownFrameCounter >= 121)
    {
        return 2; 
    }
    else if (g_Controller0->btnsHeld_C == UNK_BTN_FLAGS_0 && (g_Controller0->btnsClicked_10 & UNK_BTN_FLAGS_0))
    {
        return 2; 
    }
    else if (g_Controller0->btnsHeld_C == UNK_BTN_FLAGS_1 && (g_Controller0->btnsClicked_10 & ControllerFlag_Start))
    {
        return 2; 
    }

    return (g_SysWork.flags_22A4 & (1 << 8)) ? 2 : 0;
}

void Game_WarmBoot() // 0x80034264
{
    e_GameState prevState;

    DrawSync(0);
    Screen_RectInterlacedClear(0, 32, 512, 448, 0, 0, 0);
    func_800892A4(4);
    func_80089128();
    Sd_EngineCmd(19);

    while (func_80045B28())
    {
        func_800485D8();
        VSync(0);
    }

    Sd_EngineCmd(20);

    while (func_80045B28())
    {
        func_800485D8();
        VSync(0);
    }

    Fs_QueueReset();
    Fs_QueueWaitForEmpty();
    sd_work_init();
    func_80035AC8(1);

    while (func_80045B28())
    {
        func_800485D8();
        VSync(0);
    }

    if (g_SysWork.flags_22A4 & (1 << 1))
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

    g_Screen_FadeStatus = SCREEN_FADE_STATUS(ScreenFadeState_FadeInStart, false);

    g_GameWork.gameStateStep_598[0] = prevState;
    g_GameWork.gameStatePrev_590    = prevState;
    g_GameWork.gameStateStep_598[0] = 0;

    g_ScreenFadeTimestep = FP_TIME(0.0f);
}
