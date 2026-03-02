#include "game.h"

#include "bodyprog/demo.h"
#include "bodyprog/screen/screen_draw.h"
#include "bodyprog/sys/game_main.h"

void Screen_VSyncCallback(void) // 0x80032B80
{
    g_Demo_FrameCount++;
    g_WarmBootTimer++;

    g_SysWork.counters_1C[0]++;
    g_SysWork.counters_1C[1]++;
    g_SysWork.counters_1C[2]++;
}
