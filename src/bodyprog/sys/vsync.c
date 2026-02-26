#include "game.h"

#include "bodyprog/demo.h"
#include "bodyprog/gamemain.h"
#include "bodyprog/screen/screen_draw.h"

void Screen_VSyncCallback(void) // 0x80032B80
{
    g_Demo_FrameCount++;
    g_WarmBootTimer++;

    g_SysWork.timer_1C++;
    g_SysWork.timer_20++;
    g_SysWork.timer_24++;
}
