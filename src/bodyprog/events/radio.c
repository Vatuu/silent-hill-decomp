#include "game.h"

#include <psyq/libetc.h>
#include <psyq/libpad.h>
#include <psyq/strings.h>

#include "bodyprog/bodyprog.h"
#include "bodyprog/demo.h"
#include "bodyprog/screen/screen_draw.h"
#include "bodyprog/text/text_draw.h"
#include "bodyprog/item_screens.h"
#include "bodyprog/math/math.h"
#include "bodyprog/memcard.h"
#include "bodyprog/player_logic.h"
#include "bodyprog/ranking.h"
#include "bodyprog/sound_system.h"
#include "main/fsqueue.h"
#include "main/mem.h"
#include "main/rng.h"
#include "screens/stream/stream.h"

// ========================================
// RADIO SFX
// ========================================

void func_80037154(void) // 0x80037154
{
    s32 i;

    for (i = 0; i < 2; i++)
    {
        D_800BCDA8[i].field_2 = NO_VALUE;
        D_800BCDA8[i].field_1 = NO_VALUE;
        D_800BCDA8[i].field_3 = 0;
    }
}

void Game_RadioSoundStop(void) // 0x80037188
{
    s32 i;

    for (i = 0; i < 2; i++)
    {
        D_800BCDA8[i].field_0 = NO_VALUE;
    }

    for (i = 0; i < 2; i++)
    {
        Sd_SfxStop(Sfx_RadioInterferenceLoop + i);
    }
}
