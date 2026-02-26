#include "game.h"

#include <psyq/libetc.h>
#include <psyq/libpad.h>
#include <psyq/strings.h>

#include "bodyprog/bodyprog.h"
#include "bodyprog/demo.h"
#include "bodyprog/screen/screen_data.h"
#include "bodyprog/screen/screen_draw.h"
#include "bodyprog/text/text_draw.h"
#include "bodyprog/item_screens.h"
#include "bodyprog/math/math.h"
#include "bodyprog/memcard.h"
#include "bodyprog/player_logic.h"
#include "bodyprog/ranking.h"
#include "bodyprog/sound_background.h"
#include "bodyprog/sound_system.h"
#include "main/fsqueue.h"
#include "main/mem.h"
#include "main/rng.h"
#include "screens/stream/stream.h"

void Game_NpcClear(void) // 0x80034EC8
{
    s32 i;

    g_SysWork.field_228C[0] = 0;
    g_SysWork.npcFlags_2290 = 0;

    bzero(g_SysWork.npcs_1A0, ARRAY_SIZE(g_SysWork.npcs_1A0) * sizeof(s_SubCharacter));

    for (i = 0; i < GROUP_CHARA_COUNT; i++)
    {
        g_SysWork.field_2284[i] = 0;
    }
}

void Game_NpcInit(void) // 0x80034F18
{
    vcSetCameraUseWarp(&g_SysWork.playerWork_4C.player_0.position_18, g_SysWork.cameraAngleY_237A);
    func_8005E70C();

    if (g_SysWork.field_234A)
    {
        g_MapOverlayHeader.enviromentSet_16C(g_SysWork.field_2349, 127);
        g_MapOverlayHeader.particlesUpdate_168(0, g_SavegamePtr->mapOverlayId_A4, 0);
    }

    Game_NpcClear();
    Game_NpcRoomInitSpawn(false);
    Game_PlayerHeightUpdate();
}

void Game_InGameInit(void) // 0x80034FB8
{
    s32 mapOvlId;

    mapOvlId = g_SavegamePtr->mapOverlayId_A4;

    vcInitCamera(&g_MapOverlayHeader, &g_SysWork.playerWork_4C.player_0.position_18);

    vcSetCameraUseWarp(&g_SysWork.playerWork_4C.player_0.position_18, g_SysWork.cameraAngleY_237A);
    func_80040004(&g_MapOverlayHeader);
    Gfx_MapEffectsSet(0);
    WorldGfx_CharaModelProcessAllLoads();
    Game_FlashlightAttributesFix();

    g_MapOverlayHeader.particlesUpdate_168(0, mapOvlId, NO_VALUE);

    Game_NpcClear();

    g_SysWork.npcId_2280 = 5;

    func_8005E650(mapOvlId);
    func_80037124();
    func_8007E8C0();
    Game_NpcRoomInitSpawn(false);
    Game_PlayerHeightUpdate();
    Fs_CharaAnimBoneInfoUpdate();
    GameFs_WeaponInfoUpdate();
    GameFs_Tim00TIMLoad();
    Fs_QueueWaitForEmpty();
    GameFs_MapItemsModelLoad(mapOvlId);
}
