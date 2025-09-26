#include "game.h"

#include "bodyprog/vw_system.h"
#include "bodyprog/math/math.h"

void vwInitViewInfo(void) // 0x80048A38
{
    vwViewPointInfo.rview.vp.vz = 0;
    vwViewPointInfo.rview.vp.vy = 0;
    vwViewPointInfo.rview.vp.vx = 0;
    vwViewPointInfo.rview.vr.vx = 0;
    vwViewPointInfo.rview.vr.vy = 0;
    vwViewPointInfo.rview.vr.vz = Q12(1.0f);
    vwViewPointInfo.rview.rz    = 0;
    vwViewPointInfo.rview.super = &vwViewPointInfo.vwcoord;
    GsInitCoordinate2(NULL, &vwViewPointInfo.vwcoord);
    vwSetViewInfo();
}

GsCOORDINATE2* vwGetViewCoord(void) // 0x80048A90
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

void Vw_SetLookAtMatrix(const VECTOR3* pos, const VECTOR3* lookAt) // 0x80048AF4
{
    q23_8   deltaX;
    q23_8   deltaY;
    q23_8   deltaZ;
    MATRIX  viewMat;
    SVECTOR rot; // Q3.12

    // Compute direction vector components.
    deltaX = Q12_TO_Q8(lookAt->vx - pos->vx);
    deltaY = Q12_TO_Q8(lookAt->vy - pos->vy);
    deltaZ = Q12_TO_Q8(lookAt->vz - pos->vz);

    // Compute camera rotation.
    rot.vz = FP_ANGLE(0.0f);
    rot.vy = ratan2(deltaX, deltaZ);
    rot.vx = ratan2(-deltaY, SquareRoot0(SQUARE(deltaX) + SQUARE(deltaZ)));

    // Compute view transform matrix and set global info.
    func_80096C94(&rot, &viewMat);
    viewMat.t[0] = Q12_TO_Q8(pos->vx);
    viewMat.t[1] = Q12_TO_Q8(pos->vy);
    viewMat.t[2] = Q12_TO_Q8(pos->vz);
    vwSetViewInfoDirectMatrix(NULL, &viewMat);
}

void vwSetCoordRefAndEntou(GsCOORDINATE2* parent_p, q19_12 ref_x, q19_12 ref_y, q19_12 ref_z, q3_12 cam_ang_y, q3_12 cam_ang_z, q19_12 cam_y, q19_12 cam_xz_r) // 0x80048BE0
{
    SVECTOR view_ang; // Q3.12
    MATRIX* view_mtx;

    view_mtx = &vwViewPointInfo.vwcoord.coord;

    vwViewPointInfo.vwcoord.flg   = false;
    vwViewPointInfo.vwcoord.super = parent_p;

    view_ang.vy = cam_ang_y;
    view_ang.vz = cam_ang_z;
    view_ang.vx = -ratan2(-cam_y, cam_xz_r);
    view_ang.vy = FP_ANGLE_NORM_U(view_ang.vy + FP_ANGLE(180.0f));

    func_80096E78(&view_ang, view_mtx);

    view_mtx->t[0] = Q12_TO_Q8(ref_x) + FP_MULTIPLY(Q12_TO_Q8(cam_xz_r), Math_Sin(cam_ang_y), Q12_SHIFT);
    view_mtx->t[1] = Q12_TO_Q8(ref_y) + Q12_TO_Q8(cam_y);
    view_mtx->t[2] = Q12_TO_Q8(ref_z) + FP_MULTIPLY(Q12_TO_Q8(cam_xz_r), Math_Cos(cam_ang_y), Q12_SHIFT);
}

void vwSetViewInfoDirectMatrix(GsCOORDINATE2* pcoord, const MATRIX* cammat) // 0x80048CF0
{
    vwViewPointInfo.vwcoord.flg   = false;
    vwViewPointInfo.vwcoord.super = pcoord;
    vwViewPointInfo.vwcoord.coord = *cammat;
}

/** @brief Converts a Q23.8 matrix transform to Q19.12, outputting the result to `pos`.
 *
 * Possible original name: `vwMatrixToPosition`.
 *
 * @param `pos` Output position (Q19.12).
 * @param `mat` Matrix to use for conversion.
 */
static inline void Math_MatrixToPosition(VECTOR3* pos, MATRIX* mat)
{
    pos->vx = Q8_TO_Q12(mat->t[0]);
    pos->vy = Q8_TO_Q12(mat->t[1]);
    pos->vz = Q8_TO_Q12(mat->t[2]);
}

void vwSetViewInfo(void) // 0x80048D48
{
    vbSetRefView(&vwViewPointInfo.rview);
    Math_MatrixToPosition(&vwViewPointInfo.worldpos, &vwViewPointInfo.vwcoord.workm);
    vwMatrixToAngleYXZ(&vwViewPointInfo.worldang, &vwViewPointInfo.vwcoord.workm);
}

void Vw_ClampAngleRange(q3_12* angleMin, q3_12* angleMax, q3_12 angleConstraintMin, q3_12 angleConstraintMax) // 0x80048DA8
{
    q19_12 prevAngleMax;
    q19_12 prevAngleMin;
    q19_12 rotToAngleMax;
    q3_12  rotToAngleConstraintMin;
    q3_12  rotToAngleConstraintMax;

    prevAngleMax = *angleMax;
    prevAngleMin = *angleMin;

    rotToAngleMax = prevAngleMax;
    rotToAngleMax = FP_ANGLE_NORM_U(prevAngleMax - prevAngleMin);

    rotToAngleConstraintMin = FP_ANGLE_NORM_U(angleConstraintMin - prevAngleMin);
    rotToAngleConstraintMax = FP_ANGLE_NORM_U(angleConstraintMax - prevAngleMin);

    prevAngleMax = FP_ANGLE(0.0f);
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

        if (rotToAngleMax < prevAngleMax)
        {
            prevAngleMax = rotToAngleMax;
        }
    }
    else if (rotToAngleConstraintMax > prevAngleMax)
    {
        if (rotToAngleConstraintMax < rotToAngleMax)
        {
            rotToAngleMax = rotToAngleConstraintMax;
        }
    }

    *angleMin = FP_ANGLE_NORM_U(prevAngleMax + prevAngleMin);
    *angleMax = FP_ANGLE_NORM_U(rotToAngleMax + prevAngleMin);
}

s16 func_80048E3C(s16 arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4) // 0x80048E3C
{
    s32   temp_a0;
    q3_12 temp_lo;

    if (arg1 > 0)
    {
        if (arg2 < 0)
        {
            return Q12(1.0f);
        }
    }
    else if (arg1 >= 0 || arg2 > 0)
    {
        return Q12(1.0f);
    }

    if (arg2 == 0)
    {
        if (arg3 <= 0 && arg4 >= 0)
        {
            return Q12(0.0f);
        }

        return Q12(1.0f);
    }

    if (ABS(arg2) > ABS(arg1))
    {
        return Q12(1.0f);
    }
    else
    {
        temp_lo = FP_FROM(arg2 << 16, Q4_SHIFT) / arg1;
        temp_a0 = FP_MULTIPLY(arg0, temp_lo, Q12_SHIFT);

        if (temp_a0 < arg3 || arg4 < temp_a0)
        {
            return Q12(1.0f);
        }
        else
        {
            return temp_lo;
        }
    }
}
