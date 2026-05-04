#include "game.h"

#include <psyq/libetc.h>
#include <psyq/libpad.h>
#include <psyq/strings.h>

#include "bodyprog/bodyprog.h"
#include "bodyprog/events/player_pos_update.h"
#include "bodyprog/math/math.h"

void Chara_PositionSet(s_MapPoint2d* mapPoint) // 0x800371E8
{
    q19_12 rotY;

    #define playerChara g_SysWork.playerWork.player

    rotY = Q12_ANGLE_FROM_Q8(mapPoint->triggerParam0);
    Math_SVectorSet(&playerChara.rotation, Q12_ANGLE(0.0f), rotY, Q12_ANGLE(0.0f));

    playerChara.position.vy = Q12(0.0f);
    playerChara.position.vx = mapPoint->positionX;
    playerChara.position.vz = mapPoint->positionZ;

    if (mapPoint->triggerParam1 >= 2)
    {
        playerChara.position.vx += Q12_MULT_FLOAT_PRECISE(Math_Sin(rotY), 0.4f);
        playerChara.position.vz += Q12_MULT_FLOAT_PRECISE(Math_Cos(rotY), 0.4f);
    }

    g_SysWork.loadingScreenIdx = mapPoint->loadingScreenId;

    if (mapPoint->mapIdx_4_0 == 24) // TODO: Demagic 24.
    {
        g_SavegamePtr->paperMapIdx = PaperMapIdx_OtherPlaces;
    }
    else if (mapPoint->mapIdx_4_0 != PaperMapIdx_OtherPlaces)
    {
        g_SavegamePtr->paperMapIdx = mapPoint->mapIdx_4_0;
    }

    g_SysWork.cameraAngleY = rotY;

    func_8007E9C4();
    Savegame_MapRoomIdxUpdate();

    #undef playerChara
}

void Game_PlayerHeightUpdate(void) // 0x80037334
{
    s_Collision coll;

    if (g_MapOverlayHeader.updateWorldObjects != NULL)
    {
        g_MapOverlayHeader.updateWorldObjects();
    }

    Collision_Get(&coll, g_SysWork.playerWork.player.position.vx, g_SysWork.playerWork.player.position.vz);
    g_SysWork.playerWork.player.position.vy = coll.groundHeight;
}
