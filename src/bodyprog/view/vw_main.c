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
    vwViewPointInfo.rview.vr.vz = FP_METER(1.0f);
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

void Vw_SetLookAtMatrix(VECTOR3* pos, VECTOR3* lookAt) // 0x80048AF4
{
    s32     deltaX; // Q23.8
    s32     deltaY; // Q23.8
    s32     deltaZ; // Q23.8
    MATRIX  viewMat;
    SVECTOR rot;

    // Compute direction vector components.
    deltaX = Q19_12_TO_Q23_8(lookAt->vx - pos->vx);
    deltaY = Q19_12_TO_Q23_8(lookAt->vy - pos->vy);
    deltaZ = Q19_12_TO_Q23_8(lookAt->vz - pos->vz);

    // Compute camera rotation.
    rot.vz = FP_ANGLE(0.0f);
    rot.vy = ratan2(deltaX, deltaZ);
    rot.vx = ratan2(-deltaY, SquareRoot0(SQUARE(deltaX) + SQUARE(deltaZ)));

    // Compute view transform matrix and set global info.
    func_80096C94(&rot, &viewMat);
    viewMat.t[0] = Q19_12_TO_Q23_8(pos->vx);
    viewMat.t[1] = Q19_12_TO_Q23_8(pos->vy);
    viewMat.t[2] = Q19_12_TO_Q23_8(pos->vz);
    vwSetViewInfoDirectMatrix(NULL, &viewMat);
}

/* "Entou" means "cylinder" in Japanese. Refers to the radius on the XZ plane. */
void vwSetCoordRefAndEntou(GsCOORDINATE2* parent_p, s32 ref_x, s32 ref_y, s32 ref_z, s16 cam_ang_y, s16 cam_ang_z, s32 cam_y, s32 cam_xz_r) // 0x80048BE0
{
    SVECTOR view_ang;
    MATRIX* view_mtx;

    view_mtx = &vwViewPointInfo.vwcoord.coord;

    vwViewPointInfo.vwcoord.flg   = false;
    vwViewPointInfo.vwcoord.super = parent_p;

    view_ang.vy = cam_ang_y;
    view_ang.vz = cam_ang_z;
    view_ang.vx = -ratan2(-cam_y, cam_xz_r);
    view_ang.vy = FP_ANGLE_NORM_U(view_ang.vy + FP_ANGLE(180.0f));

    func_80096E78(&view_ang, view_mtx);

    // TODO: What's happening here?
    view_mtx->t[0] = (ref_x >> 4) + FP_MULTIPLY(cam_xz_r >> 4, Math_Sin(cam_ang_y), Q12_SHIFT);
    view_mtx->t[1] = (ref_y >> 4) + (cam_y >> 4);
    view_mtx->t[2] = (ref_z >> 4) + FP_MULTIPLY(cam_xz_r >> 4, Math_Cos(cam_ang_y), Q12_SHIFT);
}

void vwSetViewInfoDirectMatrix(GsCOORDINATE2* pcoord, MATRIX* cammat) // 0x80048CF0
{
    vwViewPointInfo.vwcoord.flg   = false;
    vwViewPointInfo.vwcoord.super = pcoord;
    vwViewPointInfo.vwcoord.coord = *cammat;
}

/** @brief Converts a matrix transform in Q23.8 to Q19.12, outputting the result to `pos`.
 *
 * Possible original name: `vwMatrixToPosition`.
 *
 * @param `pos` Output position.
 * @param `mat` Matrix to use for conversion.
 */
static inline void Math_MatrixToPosition(VECTOR3* pos, MATRIX* mat)
{
    pos->vx = Q23_8_TO_Q19_12(mat->t[0]);
    pos->vy = Q23_8_TO_Q19_12(mat->t[1]);
    pos->vz = Q23_8_TO_Q19_12(mat->t[2]);
}

void vwSetViewInfo() // 0x80048D48
{
    vbSetRefView(&vwViewPointInfo.rview);
    Math_MatrixToPosition(&vwViewPointInfo.worldpos, &vwViewPointInfo.vwcoord.workm);
    vwMatrixToAngleYXZ(&vwViewPointInfo.worldang, &vwViewPointInfo.vwcoord.workm);
}

void Vw_ClampAngleRange(s16* angleMin, s16* angleMax, s16 angleConstraintMin, s16 angleConstraintMax) // 0x80048DA8
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

    *angleMin = FP_ANGLE_NORM_U(newAngleMin);
    *angleMax = FP_ANGLE_NORM_U(rotToAngleMax + prevAngleMin);
}

s16 func_80048E3C(s16 arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4) // 0x80048E3C
{
    s16 var_v0;
    s32 var_v0_3;
    s32 temp_a0;
    s16 temp_lo;
    s32 temp_v0;
    s32 var_a1;
    s32 var_v0_2;
    s16 new_var;

    if (arg1 > 0)
    {
        if (arg2 < 0)
        {
            return FP_TO(1, Q12_SHIFT);
        }
    }
    else if (arg1 >= 0 || arg2 > 0)
    {
        return FP_TO(1, Q12_SHIFT);
    }

    if (arg2 == 0)
    {
        if (arg3 <= 0 && arg4 >= 0)
        {
            return 0;
        }

        return FP_TO(1, Q12_SHIFT);
    }

    if (ABS(arg2) > ABS(arg1))
    {
        return FP_TO(1, Q12_SHIFT);
    }
    else
    {
        temp_lo = FP_FROM(arg2 << 16, Q4_SHIFT) / arg1;
        temp_a0 = FP_MULTIPLY(arg0, temp_lo, Q12_SHIFT);

        if (temp_a0 < arg3 || arg4 < temp_a0)
        {
            return FP_TO(1, Q12_SHIFT);
        }
        else
        {
            return temp_lo;
        }
    }
}
