#include "game.h"
#include "inline_no_dmpsx.h"

#include <psyq/gtemac.h>

#include "bodyprog/bodyprog.h"
#include "bodyprog/screen/screen_data.h"
#include "bodyprog/item_screens.h"
#include "bodyprog/math/math.h"


GsCOORD2PARAM D_800C3928;
s8 g_Player_WeaponAttack;
s8 pad_bss_800C3951[3];
s32 D_800C3954;
s32 D_800C3958;
s32 D_800C395C;

void func_8004BB10(void) // 0x8004BB10
{
    GsFCALL4.g3[GsDivMODE_NDIV][GsLMODE_FOG]  = GsTMDfastG3LFG;
    GsFCALL4.tg3[GsDivMODE_NDIV][GsLMODE_FOG] = GsTMDfastTG3LFG;
    GsFCALL4.g4[GsDivMODE_NDIV][GsLMODE_FOG]  = GsTMDfastG4LFG;
    GsFCALL4.tg4[GsDivMODE_NDIV][GsLMODE_FOG] = GsTMDfastTG4LFG;
}

void ItemScreen_CamSet(VbRVIEW* view, GsCOORDINATE2* coord, SVECTOR3* vec, s32 arg3) // 0x8004BB4C
{
    view->vr.vz = 10;
    view->vp.vx = 0;
    view->vp.vy = 0;
    view->vp.vz = 0;
    view->vr.vx = 0;
    view->vr.vy = 0;

    view->rz = 0;

    view->super       = coord;
    coord->coord.t[2] = -0x2800;
    coord->super      = NULL;
    coord->coord.t[0] = 0;
    coord->coord.t[1] = 0;

    vec->vx = 0;
    vec->vy = 0;
    vec->vz = 0;

    D_800C3928.scale.vz  = Q12(1.0f);
    D_800C3928.scale.vy  = Q12(1.0f);
    D_800C3928.scale.vx  = Q12(1.0f);
    D_800C3928.rotate.vz = 0;
    D_800C3928.rotate.vy = 0;
    D_800C3928.rotate.vx = 0;
    D_800C3928.trans.vz  = 0;
    D_800C3928.trans.vy  = 0;
    D_800C3928.trans.vx  = 0;

    coord->param = &D_800C3928;

    ItemScreen_ItemRotate((SVECTOR*)vec, coord);
    vbSetRefView(view);
}

void func_8004BBF4(VbRVIEW* arg0, GsCOORDINATE2* arg1, SVECTOR* arg2) // 0x8004BBF4
{
    u16     vx;
    VECTOR  vec;
    SVECTOR sVec;

    vx  = arg2->vx;
    arg2->vx = 0;

    ItemScreen_ItemRotate(arg2, arg1);

    arg2->vx = vx;

    ItemScreen_ItemRotate(arg2, arg1);

    sVec.vx = 0;
    sVec.vy = 0;
    sVec.vz = 0;

    gte_ApplyMatrix(&arg1->coord, &sVec, &vec);
    vbSetRefView(arg0);
}

void GameFs_TmdDataAlloc(s32* buf) // 0x8004BCBC
{
    GsMapModelingData((unsigned long*)&buf[1]);
}

void ItemScreen_ItemRotate(SVECTOR* arg0, GsCOORDINATE2* arg1) // 0x8004BCDC
{
    MATRIX mat;

    mat.t[0] = arg1->coord.t[0];
    mat.t[1] = arg1->coord.t[1];
    mat.t[2] = arg1->coord.t[2];

    Math_RotMatrixZxyNegGte(arg0, &mat);

    arg1->coord = mat;

    ScaleMatrix(&arg1->coord, &arg1->param->scale);

    arg1->flg = false;
}

void func_8004BD74(s32 displayItemIdx, GsDOBJ2* arg1, s32 arg2)  // 0x8004BD74
{
    MATRIX sp10;
    MATRIX sp30;
    MATRIX sp50;
    s32 j;
    s32 i;

    func_80049B6C(arg1->coord2, &sp50, &sp10);

    sp30 = sp10;

    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            sp10.m[i][j] = Q12(sp10.m[i][j]) / g_Items_Transforms[displayItemIdx].scale.vx;
        }
    }

    if (arg2 != 3 && displayItemIdx < 7)
    {
        for (i = 0; i < 3; i++)
        {
            for (j = 0; j < 3; j++)
            {
                sp10.m[i][j] -= Q12_MULT(sp10.m[i][j], Math_Sin((g_Items_Coords[displayItemIdx].coord.t[2] + 0x400) >> 2));
            }
        }
    }

    GsSetLightMatrix(&sp10);
    GsSetLsMatrix(&sp30);

    if (arg2 == 2)
    {
        GsClearOt(0, 0, &g_OrderingTable1[g_ActiveBufferIdx]);
        GsSortOt(&g_OrderingTable1[g_ActiveBufferIdx], &g_OrderingTable0[g_ActiveBufferIdx]);
        GsSortObject4J(arg1, &g_OrderingTable1[g_ActiveBufferIdx], 1, (u32*)PSX_SCRATCH);
    }
    else
    {
        GsSortObject4J(arg1, &g_OrderingTable0[g_ActiveBufferIdx], 1, (u32*)PSX_SCRATCH);
    }
}

/** Removing this causes the models of items to appear farther from the camera.
 * `Gfx_Items_ViewPointAdjustment`?
 */
void func_8004BFE8(void) // 0x8004BFE8
{
    // Save constant rotation matrix in stack.
    PushMatrix();

    // Read distance from viewpoint to screen.
    D_800C3954 = ReadGeomScreen();

    // Read GTE offset value.
    ReadGeomOffset(&D_800C3958, &D_800C395C);

    // Set distance between projection plane and viewpoint. Results in FOV change.
    GsSetProjection(1000);

    g_Player_WeaponAttack = g_SysWork.playerCombat_38.weaponAttack_F;
}

/** Possible failsafe?
 * Used when exiting the inventory screen or going into options and map menus
 * through the inventory.
 *
 * Removing it doesn't affect the game.
 *
 * @note From a member of the PS Decomp Discord:
 * "[The function] essentially just tries to restore projection/offset settings
 * and the transform matrix to what they were in the main game, but I'm guessing
 * the game sets them at the start of every frame anyway, so it doesn't really
 * achieve anything."
 */
void func_8004C040(void) // 0x8004C040
{
    // Reset constant rotation matrix from stack.
    PopMatrix();

    GsSetProjection(D_800C3954);
    SetGeomOffset(D_800C3958, D_800C395C);
}
