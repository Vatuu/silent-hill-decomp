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
    g_WorldGfxWork.triggerZone = &overlayHeader->triggerZones_D2C[0];
}

void func_80040014(void) // 0x80040014
{
    Collision_TriggerZonesUpdate(g_SysWork.playerWork.player.position.vx, g_SysWork.playerWork.player.position.vz, g_WorldGfxWork.triggerZone);
};

