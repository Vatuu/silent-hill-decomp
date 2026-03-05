#include "game.h"

#include <psyq/libetc.h>
#include <psyq/libpad.h>
#include <psyq/strings.h>

#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "bodyprog/memcard.h"
#include "bodyprog/screen/screen_data.h"
#include "bodyprog/screen/screen_draw.h"
#include "bodyprog/sound_system.h"
#include "bodyprog/text/text_draw.h"
#include "main/fsqueue.h"
#include "main/rng.h"
#include "screens/stream/stream.h"

// ========================================
// UNKNOWN - IN-GAME RELATED
// ========================================

s32 Map_TypeGet(void) // 0x8003BD2C
{
    return g_WorldGfx.mapInfo_0 - MAP_INFOS;
}

void func_8003BD48(s_SubCharacter* chara) // 0x8003BD48
{
    u16 var_s0;

    D_800BCE14 = func_80069810();
    var_s0     = D_800BCE14;

    switch (Map_TypeGet())
    {
        case 0:
            if (chara->position_18.vx >= Q12(191.6f) && chara->position_18.vx <= Q12(198.8f) &&
                chara->position_18.vz >= Q12(-96.0f) && chara->position_18.vz <= Q12(-90.3f))
            {
                var_s0 = (var_s0 & ~0x2) | 0x4;
            }
            break;

        case 3:
        case 4:
            if (chara->position_18.vx >= Q12(-100.0f) && chara->position_18.vx <= Q12(-94.5f) &&
                chara->position_18.vz >= Q12(-70.3f) && chara->position_18.vz <= Q12(-62.0f))
            {
                var_s0 = (var_s0 & ~0x2) | 0x4;
            }
    }

    func_80069820(var_s0);
}

void func_8003BE28(void) // 0x8003BE28
{
    func_80069820(D_800BCE14);
}
