#include "game.h"
#include "inline_no_dmpsx.h"

#include <libapi.h>
#include <strings.h>

#include "bodyprog/bodyprog.h"
#include "bodyprog/math.h"
#include "bodyprog/item_screens.h"
#include "bodyprog/player_logic.h"
#include "main/rng.h"

extern s_800C4168 D_800C4168;

void Items_AmmoReloadCalculation(s32* currentAmmo, s32* availableAmmo, u8 gunIdx) // 0x80054FC0
{
    s32 missingAmmo;

    missingAmmo = g_Items_GunsMaxLoadAmmo[gunIdx] - *currentAmmo;
    if (missingAmmo == 0)
    {
        return;
    }

    if (*availableAmmo >= missingAmmo)
    {
        *currentAmmo   += missingAmmo;
        *availableAmmo -= missingAmmo;
        return;
    }
	else
	{
		*currentAmmo  += *availableAmmo;
		*availableAmmo = 0;
		return;
	}
}
