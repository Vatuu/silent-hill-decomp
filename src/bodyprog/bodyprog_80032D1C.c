#include "game.h"

#include "bodyprog/bodyprog.h"
#include "bodyprog/text/text_draw.h"

void func_80032CE8(void) // 0x80032CE8
{
    Gfx_StringSetPosition(SCREEN_POSITION_X(33.75f), SCREEN_POSITION_Y(43.5f));
    Gfx_StringDraw("\x7Now_loading.", 100);
}
