#include "game.h"

#include <psyq/libetc.h>
#include <psyq/libpad.h>
#include <psyq/strings.h>

#include "bodyprog/bodyprog.h"
#include "bodyprog/events/map_msg.h"
#include "bodyprog/screen/screen_data.h"
#include "bodyprog/screen/screen_draw.h"
#include "bodyprog/text/text_draw.h"

void func_8003652C(void) // 0x8003652C
{
    RECT rect;

    const u32 VALS[] = {
        0xFFFF0000, 0xBBEEE318, 0xFFEC9304, 0x83FFE30C,
        0x001F8318, 0x90840018, 0x90808080, 0x80048084
    };

    rect.x = 304;
    rect.y = 510;
    rect.w = 16;
    rect.h = 1;

    LoadImage(&rect, VALS);
}

static const s32 __pad = 0;
