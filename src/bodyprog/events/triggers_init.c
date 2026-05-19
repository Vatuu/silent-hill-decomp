#include "game.h"

#include <psyq/libetc.h>
#include <psyq/libpad.h>
#include <psyq/strings.h>

#include "bodyprog/bodyprog.h"
#include "bodyprog/memcard.h"
#include "bodyprog/screen/screen_draw.h"
#include "bodyprog/text/text_draw.h"
#include "bodyprog/math/math.h"
#include "bodyprog/sound/sound_system.h"
#include "main/fsqueue.h"
#include "main/rng.h"
#include "screens/stream/stream.h"

void World_TriggerZonesSet(s_MapOverlayHeader* overlayHeader) // 0x80040004
{
    g_WorldGfxWork.triggerZones = &overlayHeader->triggerZones;
}

void World_PlayerTriggerZonesGet(void) // 0x80040014
{
    #define playerChara g_SysWork.playerWork.player

    Collision_TriggerZonesGet(playerChara.position.vx, playerChara.position.vz, g_WorldGfxWork.triggerZones);

    #undef playerChara
};
