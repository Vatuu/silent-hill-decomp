#include "game.h"

#include <psyq/libetc.h>
#include <psyq/libpad.h>
#include <psyq/strings.h>

#include "bodyprog/bodyprog.h"
#include "bodyprog/events/radio.h"
#include "bodyprog/sound_system.h"

void func_80037154(void) // 0x80037154
{
    s32 i;

    for (i = 0; i < ARRAY_SIZE(D_800BCDA8); i++)
    {
        D_800BCDA8[i].field_2 = NO_VALUE;
        D_800BCDA8[i].field_1 = NO_VALUE;
        D_800BCDA8[i].field_3 = 0;
    }
}

void Game_RadioSoundStop(void) // 0x80037188
{
    s32 i;

    for (i = 0; i < ARRAY_SIZE(D_800BCDA8); i++)
    {
        D_800BCDA8[i].field_0 = NO_VALUE;
    }

    for (i = 0; i < ARRAY_SIZE(D_800BCDA8); i++)
    {
        Sd_SfxStop(Sfx_RadioInterferenceLoop + i);
    }
}
