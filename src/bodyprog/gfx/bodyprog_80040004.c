#include "game.h"

#include <psyq/libetc.h>
#include <psyq/libpad.h>
#include <psyq/strings.h>

#include "bodyprog/bodyprog.h"
#include "bodyprog/memcard.h"
#include "bodyprog/screen/screen_draw.h"
#include "bodyprog/text/text_draw.h"
#include "bodyprog/math/math.h"
#include "bodyprog/sound_system.h"
#include "main/fsqueue.h"
#include "main/rng.h"
#include "screens/stream/stream.h"

// ========================================
// UNKNOWN
// ========================================

void func_80040004(s_MapOverlayHeader* overlayHeader) // 0x80040004
{
    g_WorldGfx.field_1BD8 = &overlayHeader->field_D2C[0];
}

void func_80040014(void) // 0x80040014
{
    func_80069860(g_SysWork.playerWork_4C.player_0.position_18.vx, g_SysWork.playerWork_4C.player_0.position_18.vz, g_WorldGfx.field_1BD8);
};

INCLUDE_RODATA("bodyprog/nonmatchings/gfx/bodyprog_80040004", D_80025BE4);
