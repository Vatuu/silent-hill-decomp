#include "game.h"

#include "bodyprog/vw_system.h"
#include "bodyprog/math.h"

void vwInitViewInfo() // 0x80048A38
{
    vwViewPointInfo.rview.vp.vz = 0;
    vwViewPointInfo.rview.vp.vy = 0;
    vwViewPointInfo.rview.vp.vx = 0;
    vwViewPointInfo.rview.vr.vx = 0;
    vwViewPointInfo.rview.vr.vy = 0;
    vwViewPointInfo.rview.vr.vz = TILE_UNIT(16.0f);
    vwViewPointInfo.rview.rz    = 0;
    vwViewPointInfo.rview.super = &vwViewPointInfo.vwcoord;
    GsInitCoordinate2(NULL, &vwViewPointInfo.vwcoord);
    vwSetViewInfo();
}

GsCOORDINATE2* vwGetViewCoord() // 0x80048A90
{
    return &vwViewPointInfo.vwcoord;
}

void vwGetViewPosition(VECTOR3* pos) // 0x80048A9C
{
    *pos = vwViewPointInfo.worldpos;
}

void vwGetViewAngle(SVECTOR* ang) // 0x80048AC4
{
    *ang = vwViewPointInfo.worldang;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/view/vw_main", func_80048AF4);

void vwSetCoordRefAndEntou(GsCOORDINATE2* parent_p, s32 ref_x, s32 ref_y, s32 ref_z, s16 cam_ang_y, s16 cam_ang_z, s32 cam_y, s32 cam_xz_r) // 0x80048BE0
{
    SVECTOR view_ang;
    MATRIX* view_mtx = &vwViewPointInfo.vwcoord.coord;

    vwViewPointInfo.vwcoord.flg   = 0;
    vwViewPointInfo.vwcoord.super = parent_p;

    view_ang.vy = cam_ang_y;
    view_ang.vz = cam_ang_z;
    view_ang.vx = -ratan2(-cam_y, cam_xz_r);
    view_ang.vy = (view_ang.vy + FP_ANGLE(11.25f)) & 0xFFF;

    func_80096E78(&view_ang, view_mtx);

    view_mtx->t[0] = FROM_FIXED(ref_x, Q4_SHIFT) + FROM_FIXED(FROM_FIXED(cam_xz_r, Q4_SHIFT) * shRsin(cam_ang_y), Q12_SHIFT);
    view_mtx->t[1] = FROM_FIXED(ref_y, Q4_SHIFT) + FROM_FIXED(cam_y, Q4_SHIFT);
    view_mtx->t[2] = FROM_FIXED(ref_z, Q4_SHIFT) + FROM_FIXED(FROM_FIXED(cam_xz_r, Q4_SHIFT) * shRcos(cam_ang_y), Q12_SHIFT);
}

void vwSetViewInfoDirectMatrix(GsCOORDINATE2* pcoord, MATRIX* cammat) // 0x80048CF0
{
    vwViewPointInfo.vwcoord.flg   = 0;
    vwViewPointInfo.vwcoord.super = pcoord;
    vwViewPointInfo.vwcoord.coord = *cammat;
}

// Inlined into vwSetViewInfo, maybe vwMatrixToPosition?
static inline void Math_MatrixToPosition(VECTOR3* pos, MATRIX* workm)
{
    pos->vx = TO_FIXED(workm->t[0], Q4_SHIFT);
    pos->vy = TO_FIXED(workm->t[1], Q4_SHIFT);
    pos->vz = TO_FIXED(workm->t[2], Q4_SHIFT);
}

void vwSetViewInfo() // 0x80048D48
{
    vbSetRefView(&vwViewPointInfo.rview);
    Math_MatrixToPosition(&vwViewPointInfo.worldpos, &vwViewPointInfo.vwcoord.workm);
    vwMatrixToAngleYXZ(&vwViewPointInfo.worldang, &vwViewPointInfo.vwcoord.workm);
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/view/vw_main", func_80048DA8);

INCLUDE_ASM("asm/bodyprog/nonmatchings/view/vw_main", func_80048E3C);
