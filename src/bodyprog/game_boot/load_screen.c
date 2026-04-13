#include "game.h"

#include <psyq/libetc.h>
#include <psyq/libpad.h>
#include <psyq/strings.h>

#include "bodyprog/bodyprog.h"
#include "bodyprog/game_boot/game_boot.h"
#include "bodyprog/gfx/map_effects.h"
#include "bodyprog/view/vc_main.h"
#include "bodyprog/math/math.h"

/** @brief Updates the translation and rotation of a matrix in a coordinate.
 *
 * @param pos Translation to apply.
 * @param rot Rotation to apply.
 * @param coord Coordinate to update.
 */
static void Math_MatrixTransform(VECTOR3* pos, SVECTOR* rot, GsCOORDINATE2* coord) // 0x80035B04
{
    coord->flg        = false;
    coord->coord.t[0] = Q12_TO_Q8(pos->vx);
    coord->coord.t[1] = Q12_TO_Q8(pos->vy);
    coord->coord.t[2] = Q12_TO_Q8(pos->vz);

    Math_RotMatrixZxyNegGte(rot, (MATRIX*)&coord->coord);
}

void Gfx_MapEffectsSet(s32 unused) // 0x80035B58
{
    Gfx_MapEffectsAssign(&g_MapOverlayHeader);
    g_MapOverlayHeader.enviromentSet_16C(g_MapOverlayHeader.field_17, g_MapOverlayHeader.field_16);
}

void func_80035B98(void) // 0x80035B98
{
    Screen_BackgroundImgDraw(&g_ItemInspectionImg);
}

void GameBoot_LoadScreen_BackgroundImg(void) // 0x80035BBC
{
    Screen_BackgroundImgDraw(&g_LoadingScreenImg);
}

void GameBoot_LoadScreen_PlayerRun(void) // 0x80035BE0
{
    VECTOR3        camLookAt; // Q19.12
    s32            temp;
    s_Model*       model;
    GsCOORDINATE2* boneCoords;

    boneCoords = g_SysWork.playerBoneCoords_890;
    model      = &g_SysWork.playerWork.player.model;

    if (g_SysWork.sysState_8 == SysState_Gameplay)
    {
        if (g_SysWork.processFlags_2298 == SysWorkProcessFlag_OverlayTransition)
        {
            AreaLoad_UpdatePlayerPosition();
        }

        vcInitCamera(&g_MapOverlayHeader, &g_SysWork.playerWork.player.position);
        func_80040004(&g_MapOverlayHeader);

        camLookAt.vy = Q12(-0.6f);
        camLookAt.vx = g_SysWork.playerWork.player.position.vx;
        camLookAt.vz = g_SysWork.playerWork.player.position.vz;

        vcUserWatchTarget(&camLookAt, NULL, true);

        camLookAt.vx -= Math_Sin(g_SysWork.playerWork.player.rotation.vy - Q12_ANGLE(22.5f)) * 2;
        temp          = Math_Cos(g_SysWork.playerWork.player.rotation.vy - Q12_ANGLE(22.5f));
        camLookAt.vy  = Q12(-1.0f);
        camLookAt.vz -= temp * 2;

        vcUserCamTarget(&camLookAt, NULL, true);
        Game_SpotlightLoadScreenAttribsFix();
        Gfx_LoadScreenMapEffectsUpdate(0, 0);

        model->anim.flags                                 |= AnimFlag_Visible;
        g_SysWork.playerWork.extra.disabledAnimBones = 0;
        model->anim.flags                                 |= AnimFlag_Unlocked | AnimFlag_Visible;
        model->anim.time                                   = Q12(26.0f);
        g_SysWork.playerWork.player.position.vy        = Q12(0.2f);

        D_800A998C.status = model->anim.status;

        Math_MatrixTransform(&g_SysWork.playerWork.player.position, &g_SysWork.playerWork.player.rotation, boneCoords);
        g_SysWork.sysState_8++;
    }

    Anim_PlaybackLoop(model, (s_Skeleton*)FS_BUFFER_0, boneCoords, &D_800A998C);
    vcMoveAndSetCamera(true, false, false, false, false, false, false, false);
    Gfx_FlashlightUpdate();
    func_8003DA9C(Chara_Harry, boneCoords, 1, g_SysWork.playerWork.player.timer_C6, 0);
}
