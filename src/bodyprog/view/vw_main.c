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
    vwViewPointInfo.rview.vr.vz = FP_METER(16.0f);
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

void View_LookAtMatrixSet(VECTOR3* pos, VECTOR3* lookAt) // 0x80048AF4
{
    s32     deltaX;
    s32     deltaY;
    s32     deltaZ;
    MATRIX  viewMat;
    SVECTOR rot;

    // Compute direction vector components.
    deltaX = FP_FROM(lookAt->vx - pos->vx, Q4_SHIFT);
    deltaY = FP_FROM(lookAt->vy - pos->vy, Q4_SHIFT);
    deltaZ = FP_FROM(lookAt->vz - pos->vz, Q4_SHIFT);

    // Compute camera rotation.
    rot.vz = 0;
    rot.vy = ratan2(deltaX, deltaZ);
    rot.vx = ratan2(-deltaY, SquareRoot0(SQUARE(deltaX) + SQUARE(deltaZ)));

    // Compute view transform matrix and set global info.
    func_80096C94(&rot, &viewMat);
    viewMat.t[0] = FP_FROM(pos->vx, Q4_SHIFT);
    viewMat.t[1] = FP_FROM(pos->vy, Q4_SHIFT);
    viewMat.t[2] = FP_FROM(pos->vz, Q4_SHIFT);
    vwSetViewInfoDirectMatrix(NULL, &viewMat);
}

/* "Entou" means "cylinder" in Japanese. Refers to the radius on the XZ plane. */
void vwSetCoordRefAndEntou(GsCOORDINATE2* parent_p, s32 ref_x, s32 ref_y, s32 ref_z, s16 cam_ang_y, s16 cam_ang_z, s32 cam_y, s32 cam_xz_r) // 0x80048BE0
{
    SVECTOR view_ang;
    MATRIX* view_mtx = &vwViewPointInfo.vwcoord.coord;

    vwViewPointInfo.vwcoord.flg   = 0;
    vwViewPointInfo.vwcoord.super = parent_p;

    view_ang.vy = cam_ang_y;
    view_ang.vz = cam_ang_z;
    view_ang.vx = -ratan2(-cam_y, cam_xz_r);
    view_ang.vy = (view_ang.vy + FP_ANGLE(180.0f)) & 0xFFF;

    func_80096E78(&view_ang, view_mtx);

    view_mtx->t[0] = FP_FROM(ref_x, Q4_SHIFT) + FP_FROM(FP_FROM(cam_xz_r, Q4_SHIFT) * shRsin(cam_ang_y), Q12_SHIFT);
    view_mtx->t[1] = FP_FROM(ref_y, Q4_SHIFT) + FP_FROM(cam_y, Q4_SHIFT);
    view_mtx->t[2] = FP_FROM(ref_z, Q4_SHIFT) + FP_FROM(FP_FROM(cam_xz_r, Q4_SHIFT) * shRcos(cam_ang_y), Q12_SHIFT);
}

void vwSetViewInfoDirectMatrix(GsCOORDINATE2* pcoord, MATRIX* cammat) // 0x80048CF0
{
    vwViewPointInfo.vwcoord.flg   = 0;
    vwViewPointInfo.vwcoord.super = pcoord;
    vwViewPointInfo.vwcoord.coord = *cammat;
}

// Inlined into `vwSetViewInfo`, maybe `vwMatrixToPosition`?
static inline void Math_MatrixToPosition(VECTOR3* pos, MATRIX* workm)
{
    pos->vx = FP_TO(workm->t[0], Q4_SHIFT);
    pos->vy = FP_TO(workm->t[1], Q4_SHIFT);
    pos->vz = FP_TO(workm->t[2], Q4_SHIFT);
}

void vwSetViewInfo() // 0x80048D48
{
    vbSetRefView(&vwViewPointInfo.rview);
    Math_MatrixToPosition(&vwViewPointInfo.worldpos, &vwViewPointInfo.vwcoord.workm);
    vwMatrixToAngleYXZ(&vwViewPointInfo.worldang, &vwViewPointInfo.vwcoord.workm);
}

void View_ClampAngleRange(s16* angleMin, s16* angleMax, s16 angleConstraintMin, s16 angleConstraintMax) // 0x80048DA8
{
    s32 prevAngleMax;
    s32 prevAngleMin;
    s32 rotToAngleMax;
    s16 newAngleMin;
    s16 rotToAngleConstraintMin;
    s16 rotToAngleConstraintMax;

    prevAngleMax = *angleMax;
    prevAngleMin = *angleMin;

    rotToAngleMax = prevAngleMax;
    rotToAngleMax = (prevAngleMax - prevAngleMin) & 0xFFF;

    rotToAngleConstraintMin = (angleConstraintMin - prevAngleMin) & 0xFFF;
    rotToAngleConstraintMax = (angleConstraintMax - prevAngleMin) & 0xFFF;

    prevAngleMax = 0;

    if (rotToAngleConstraintMin <= rotToAngleConstraintMax)
    {
        if (rotToAngleConstraintMin > prevAngleMax)
        {
            prevAngleMax = rotToAngleConstraintMin;
        }

        if (rotToAngleConstraintMax < rotToAngleMax)
        {
            rotToAngleMax = rotToAngleConstraintMax;
        }

        newAngleMin = prevAngleMin + prevAngleMax;
        if (rotToAngleMax < prevAngleMax)
        {
            prevAngleMax = rotToAngleMax;
        }
    }
    else if (rotToAngleConstraintMax > prevAngleMax)
    {
        newAngleMin = prevAngleMin;

        if (rotToAngleConstraintMax < rotToAngleMax)
        {
            rotToAngleMax = rotToAngleConstraintMax;
        }
    }

    newAngleMin = prevAngleMax + prevAngleMin;

    *angleMin = newAngleMin & 0xFFF;
    *angleMax = (rotToAngleMax + prevAngleMin) & 0xFFF;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/view/vw_main", func_80048E3C);
