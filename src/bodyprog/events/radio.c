#include "game.h"

#include <psyq/libetc.h>
#include <psyq/libpad.h>
#include <psyq/strings.h>

#include "bodyprog/bodyprog.h"
#include "bodyprog/events/radio.h"
#include "bodyprog/sound/sound_system.h"

void func_80037154(void) // 0x80037154
{
    s32 i;

    for (i = 0; i < ARRAY_SIZE(g_RadioNpcInfos); i++)
    {
        g_RadioNpcInfos[i].closeNpcInfoIdx = NO_VALUE;
        g_RadioNpcInfos[i].idx             = NO_VALUE;
        g_RadioNpcInfos[i].field_3         = 0;
    }
}

void Game_RadioSoundStop(void) // 0x80037188
{
    s32 i;

    for (i = 0; i < ARRAY_SIZE(g_RadioNpcInfos); i++)
    {
        g_RadioNpcInfos[i].prevIdx = NO_VALUE;
    }

    for (i = 0; i < ARRAY_SIZE(g_RadioNpcInfos); i++)
    {
        Sd_SfxStop(Sfx_RadioInterferenceLoop + i);
    }
}
