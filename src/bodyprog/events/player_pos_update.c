#include "game.h"

#include <psyq/libetc.h>
#include <psyq/libpad.h>
#include <psyq/strings.h>

#include "bodyprog/bodyprog.h"
#include "bodyprog/events/player_pos_update.h"
#include "bodyprog/math/math.h"

void Chara_PositionSet(s_MapPoint2d* mapPoint) // 0x800371E8
{
    q19_12 headingAngle;

    #define playerChara g_SysWork.playerWork.player

    headingAngle = Q12_ANGLE_FROM_Q8(mapPoint->triggerParam0);
    Math_SVectorSet(&playerChara.rotation, Q12_ANGLE(0.0f), headingAngle, Q12_ANGLE(0.0f));

    playerChara.position.vy = Q12(0.0f);
    playerChara.position.vx = mapPoint->positionX;
    playerChara.position.vz = mapPoint->positionZ;

    if (mapPoint->triggerParam1 >= 2)
    {
        playerChara.position.vx += Q12_MULT_FLOAT_PRECISE(Math_Sin(headingAngle), 0.4f);
        playerChara.position.vz += Q12_MULT_FLOAT_PRECISE(Math_Cos(headingAngle), 0.4f);
    }

    g_SysWork.loadingScreenIdx = mapPoint->loadingScreenId;

    if (mapPoint->paperMapIdx == PaperMapIdx_24)
    {
        g_SavegamePtr->paperMapIdx = PaperMapIdx_OtherPlaces;
    }
    else if (mapPoint->paperMapIdx != PaperMapIdx_OtherPlaces)
    {
        g_SavegamePtr->paperMapIdx = mapPoint->paperMapIdx;
    }

    g_SysWork.cameraAngleY = headingAngle;

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
