#include "game.h"
#include "inline_no_dmpsx.h"
#include "gtemac.h"
#include "bodyprog/bodyprog.h"
#include "bodyprog/vw_system.h"
#include "bodyprog/math/math.h"

// Reference view transform?
extern MATRIX D_800C3868;

void vwRenewalXZVelocityToTargetPos(q19_12* velo_x, q19_12* velo_z, const VECTOR3* now_pos, const VECTOR3* tgt_pos, q19_12 tgt_r,
                                    q19_12 accel, q19_12 total_max_spd, q19_12 dec_forwd_lim_spd, q19_12 dec_accel_side) // 0x80048F28
{
// SH2 locals
#if 0
    /* 0x1d */ float vec_xz[4];//
    /* 0x1d */ float lim_spd;
    /* 0x1d */ float to_tgt_dist;
    /* 0x16 */ float to_tgt_ang_y;
    /* 0x18 */ float ang_y;
    /* 0x1d */ float spd;
    /* 0x2 */ float add_spd;
    /* 0x1d */ float cam2tgt_dir_vec[4];//
    /* 0x1d */ float cam_mv_ang_y;//
    /* 0x1d */ float cam2tgt_ang_y;
#endif

    SVECTOR unused; // `cam2tgt_dir_vec`?
    q3_12   cam2tgt_ang_y;
    q19_12  ang_y;
    q19_12  to_tgt_ang_y;
    q19_12  add_spd;
    q19_12  spd;
    q19_12  to_tgt_dist;
    q19_12  lim_spd;
    q19_12  deltaZ;
    q19_12  deltaX;

    cam2tgt_ang_y = ratan2(tgt_pos->vx - now_pos->vx, tgt_pos->vz - now_pos->vz);

    // `shSinCosV` is called in SH2 while SH just calls `Math_Sin`/`Math_Cos` and does nothing with result.
    unused.vx = Math_Sin(cam2tgt_ang_y);
    unused.vy = Math_Cos(cam2tgt_ang_y);

    ratan2(*velo_x, *velo_z);

    add_spd = Math_MulFixed(accel, g_DeltaTime0, Q12_SHIFT);
    *velo_x += FP_MULTIPLY(add_spd, Math_Sin(cam2tgt_ang_y), Q12_SHIFT);
    *velo_z += FP_MULTIPLY(add_spd, Math_Cos(cam2tgt_ang_y), Q12_SHIFT);

    lim_spd = Vc_VectorMagnitudeCalc(*velo_x, Q12(0.0f), *velo_z);
    if (total_max_spd < lim_spd)
    {
        spd      = lim_spd - total_max_spd;
        ang_y    = ratan2(*velo_x, *velo_z);
        *velo_x -= Math_MulFixed(spd, Math_Sin(ang_y), Q12_SHIFT);
        *velo_z -= Math_MulFixed(spd, Math_Cos(ang_y), Q12_SHIFT);
    }

    deltaX       = tgt_pos->vx - now_pos->vx;
    deltaZ       = tgt_pos->vz - now_pos->vz;
    to_tgt_ang_y = ratan2(deltaX, deltaZ);
    to_tgt_dist  = Math_MulFixed(dec_forwd_lim_spd, Vc_VectorMagnitudeCalc(deltaX, Q12(0.0f), deltaZ) - tgt_r, Q12_SHIFT);

    if (to_tgt_dist < Q12(0.0f))
    {
        to_tgt_dist = Q12(0.0f);
    }

    vwLimitOverLimVector(velo_x, velo_z, to_tgt_dist, to_tgt_ang_y);
    vwDecreaseSideOfVector(velo_x, velo_z, Math_MulFixed(dec_accel_side, g_DeltaTime0, Q12_SHIFT), to_tgt_dist >> 1, to_tgt_ang_y);
}

void vwLimitOverLimVector(q19_12* vec_x, q19_12* vec_z, q19_12 lim_vec_len, q3_12 lim_vec_ang_y) // 0x8004914C
{
    q19_12 over_spd;
    q19_12 lim_spd_dir_x;
    q19_12 lim_spd_dir_z;

    lim_spd_dir_x = Math_Sin(lim_vec_ang_y);
    lim_spd_dir_z = Math_Cos(lim_vec_ang_y);

    over_spd = (Math_MulFixed(*vec_x, lim_spd_dir_x, Q12_SHIFT) + Math_MulFixed(*vec_z, lim_spd_dir_z, Q12_SHIFT)) - lim_vec_len;
    if (over_spd > Q12(0.0f))
    {
        *vec_x -= Math_MulFixed(over_spd, lim_spd_dir_x, Q12_SHIFT);
        *vec_z -= Math_MulFixed(over_spd, lim_spd_dir_z, Q12_SHIFT);
    }
}

void vwDecreaseSideOfVector(q19_12* vec_x, q19_12* vec_z, q19_12 dec_val, q19_12 max_side_vec_len, q3_12 dir_ang_y)
{
    q19_12 temp_s1;
    q19_12 var_s1;

    var_s1 = Math_MulFixed(*vec_x, Math_Sin(dir_ang_y + FP_ANGLE(90.0f)), Q12_SHIFT) +
             Math_MulFixed(*vec_z, Math_Cos(dir_ang_y + FP_ANGLE(90.0f)), Q12_SHIFT);

    temp_s1 = var_s1;
    var_s1  = CLAMP(var_s1, -max_side_vec_len, max_side_vec_len);

    if (dec_val < var_s1)
    {
        var_s1 = var_s1 - dec_val;
    }
    else
    {
        if (var_s1 >= -dec_val)
        {
            var_s1 = Q12(0.0f);
        }
        else
        {
            var_s1 = var_s1 + dec_val;
        }
    }

    *vec_x += Math_MulFixed(var_s1 - temp_s1, Math_Sin(dir_ang_y + FP_ANGLE(90.0f)), Q12_SHIFT);
    *vec_z += Math_MulFixed(var_s1 - temp_s1, Math_Cos(dir_ang_y + FP_ANGLE(90.0f)), Q12_SHIFT);
}

q19_12 vwRetNewVelocityToTargetVal(q19_12 now_spd, q19_12 mv_pos, q19_12 tgt_pos, q19_12 accel, q19_12 total_max_spd, q19_12 dec_val_lim_spd)
{
    q19_12 pos_diff;
    q19_12 abs_pos_diff;
    q19_12 spd_lim;
    q19_12 new_spd;
    q19_12 result_spd;

    pos_diff = tgt_pos - mv_pos;

    if (pos_diff >= Q12(0.0f))
    {
        new_spd = Math_MulFixed(accel, g_DeltaTime0, Q12_SHIFT) + now_spd;
    }
    else
    {
        new_spd = now_spd - Math_MulFixed(accel, g_DeltaTime0, Q12_SHIFT);
    }

    new_spd      = CLAMP(new_spd, -total_max_spd, total_max_spd);
    abs_pos_diff = (pos_diff < Q12(0.0f)) ? -pos_diff : pos_diff;
    spd_lim      = Math_MulFixed(dec_val_lim_spd, abs_pos_diff, Q12_SHIFT);

    if (pos_diff >= Q12(0.0f))
    {
        result_spd = spd_lim;
        if (result_spd >= new_spd)
        {
            result_spd = new_spd;
        }
        new_spd = result_spd;
    }
    else
    {
        result_spd = -spd_lim;
        if (result_spd < new_spd)
        {
            result_spd = new_spd;
        }
        new_spd = result_spd;
    }

    return new_spd;
}

q19_12 vwRetNewAngSpdToTargetAng(q19_12 now_ang_spd, q3_12 now_ang, q3_12 tgt_ang, q19_12 accel_spd, q19_12 total_max_ang_spd, q19_12 dec_val_lim_spd) // 0x80049464
{
    return vwRetNewVelocityToTargetVal(now_ang_spd, Q12(0.0f), FP_ANGLE_NORM_S(tgt_ang - now_ang), accel_spd, total_max_ang_spd, dec_val_lim_spd);
}

s32 func_800494B0(s32 arg0, s32 arg1, s32 arg2)
{
    s32 range;
    s32 arange;

    range  = FP_MULTIPLY_PRECISE(arg2, g_DeltaTime0, Q12_SHIFT);
    arange = arg1 - arg0;
    arange = CLAMP(arange, -range, range);

    if (g_DeltaTime0 == Q12(0.0f))
    {
        return Q12(0.0f);
    }

    return FP_TO(arange, Q12_SHIFT) / g_DeltaTime0;
}

s32 func_80049530(VECTOR* arg0, VECTOR* arg1) // 0x80049530
{
    VECTOR sp10;
    s32    ret;

    ApplyRotMatrixLV(arg0, &sp10);

    // TODO: Make macros for there?

    __asm__ volatile(
        "cfc2        $12, $5;"
        "lw         $t5, 0x0(%0);"
        "mtc2        $12, $2;"
        "addu       $t5, $t5, $t4;"
        "ctc2       $t5, $5;"
        "cfc2       $t4, $6;"
        "lw         $t5, 0x4(%0);"
        "mtc2       $t4, $3;"
        "addu       $t5, $t5, $t4;"
        "ctc2       $t5, $6;"
        "cfc2       $t4, $7;"
        "lw         $t5, 0x8(%0);"
        "mtc2       $t4, $4;"
        "addu       $t5, $t5, $t4;"
        "ctc2       $t5, $7;"
        "mtc2       $zero, $0;"
        "mtc2       $zero, $1" ::"r"(&sp10) : "$12", "$13", "$14");

    gte_rtps();
    gte_stsxy(arg1);

    __asm__ volatile(
        "mfc2    $12, $2;"
        "mfc2    $13, $3;"
        "mfc2    $14, $4;"
        "ctc2    $12, $5;"
        "ctc2    $13, $6;"
        "ctc2    $14, $7;"
        "mfc2    $v0, $19;"
        "nop;"
        "sra    $v0, $v0, 2;" ::: "$12", "$13", "$14");
}

void vwMatrixToAngleYXZ(SVECTOR* ang, const MATRIX* mat) // 0x800495D4
{
    s32 r_xz;

    r_xz    = SquareRoot0((mat->m[0][2] * mat->m[0][2]) + (mat->m[2][2] * mat->m[2][2]));
    ang->vx = ratan2(-mat->m[1][2], r_xz);

    if (ang->vx == FP_ANGLE(90.0f))
    {
        ang->vz = FP_ANGLE(0.0f);
        ang->vy = ratan2(mat->m[0][1], mat->m[2][1]);
    }
    else if (ang->vx == FP_ANGLE(-90.0f))
    {
        ang->vz = FP_ANGLE(0.0f);
        ang->vy = ratan2(-mat->m[0][1], -mat->m[2][1]);
    }
    else
    {
        ang->vz = ratan2(mat->m[1][0], mat->m[1][1]);
        ang->vy = ratan2(mat->m[0][2], mat->m[2][2]);
    }
}

void Vw_MultiplyAndTransformMatrix(MATRIX* transformMat, MATRIX* inMat, MATRIX* outMat) // 0x800496AC
{
    gte_SetRotMatrix(transformMat);
    gte_SetTransMatrix(transformMat);
    gte_ldclmv(inMat);
    gte_rtir();
    gte_stclmv(outMat);
    gte_ldclmv((MATRIX*)(inMat->m[0] + 1));
    gte_rtir();
    gte_stclmv((MATRIX*)(outMat->m[0] + 1));
    gte_ldclmv((MATRIX*)(inMat->m[0] + 2));
    gte_rtir();
    gte_stclmv((MATRIX*)(outMat->m[0] + 2));
    gte_ldlvl((VECTOR*)inMat->t);
    gte_rtirtr();
    gte_stlvnl((VECTOR*)outMat->t);
}

void vbSetWorldScreenMatrix(GsCOORDINATE2* coord) // 0x800497E4
{
    MATRIX work;
    VECTOR vec;

    Vw_CoordHierarchyMatrixCompute(coord, &D_800C3868);
    TransposeMatrix(&D_800C3868, &work);
    MulMatrix0(&work, &GsIDMATRIX2, &VbWvsMatrix);

    VbWvsMatrix.t[2] = Q8(0.0f);
    VbWvsMatrix.t[1] = Q8(0.0f);
    VbWvsMatrix.t[0] = Q8(0.0f);

    GsWSMATRIX.m[0][0] = VbWvsMatrix.m[0][0];
    GsWSMATRIX.m[0][1] = VbWvsMatrix.m[0][1];
    GsWSMATRIX.m[0][2] = VbWvsMatrix.m[0][2];
    GsWSMATRIX.m[1][0] = VbWvsMatrix.m[1][0];
    GsWSMATRIX.m[1][1] = VbWvsMatrix.m[1][1];
    GsWSMATRIX.m[1][2] = VbWvsMatrix.m[1][2];
    GsWSMATRIX.m[2][0] = VbWvsMatrix.m[2][0];
    GsWSMATRIX.m[2][1] = VbWvsMatrix.m[2][1];
    GsWSMATRIX.m[2][2] = VbWvsMatrix.m[2][2];

    vec.vx = -D_800C3868.t[0];
    vec.vy = -D_800C3868.t[1];
    vec.vz = -D_800C3868.t[2];
    ApplyMatrixLV(&VbWvsMatrix, &vec, (VECTOR*)&GsWSMATRIX.t);
}

void vbSetRefView(VbRVIEW* rview) // 0x800498D8
{
    GsCOORDINATE2 coord;
    SVECTOR       rot; // Q3.12
    SVECTOR       pos; // Q3.12

    coord.flg   = false;
    coord.super = rview->super;
    pos.vx      = rview->vr.vx - rview->vp.vx;
    pos.vy      = rview->vr.vy - rview->vp.vy;
    pos.vz      = rview->vr.vz - rview->vp.vz;
    vwVectorToAngle(&rot, &pos);
    Math_MatrixRotate1(&rot, &coord.coord);

    coord.coord.t[0] = rview->vp.vx;
    coord.coord.t[1] = rview->vp.vy;
    coord.coord.t[2] = rview->vp.vz;
    vbSetWorldScreenMatrix(&coord);
}

// Something to do with bone hierarchy?
void Vw_CoordHierarchyMatrixCompute(GsCOORDINATE2* rootCoord, MATRIX* outMat) // 0x80049984
{
    GsCOORDINATE2* prevCoord;
    GsCOORDINATE2* parentCoord;
    GsCOORDINATE2* curCoord;

    // If no root coord, set output matrix to identity.
    if (rootCoord == NULL)
    {
        *outMat = GsIDMATRIX;
    }

    curCoord  = rootCoord;
    prevCoord = NULL;

    // Traverse coord parent hierarchy upward.
    while (true)
    {
        parentCoord = curCoord->super;

        // Stop if node has already been processed.
        if (curCoord->flg)
        {
            break;
        }

        prevCoord = curCoord;

        // If parent node exists, link it downward for later traversal.
        if (parentCoord != NULL)
        {
            parentCoord->sub = curCoord;
            curCoord         = parentCoord;
        }
        else
        {
            break;
        }
    }

    // If at least one unprocessed node found, process coord hierarchy downward.
    if (prevCoord != NULL)
    {
        curCoord       = prevCoord;
        rootCoord->sub = NULL; // Detach child link to prevent cycles.
        do
        {
            prevCoord = curCoord->super;
            curCoord->flg++; // Mark node as processed.

            // Compute cumulative transformation matrix.
            if (prevCoord == NULL)
            {
                curCoord->workm = curCoord->coord;
            }
            else
            {
                Vw_MultiplyAndTransformMatrix(&prevCoord->workm, &curCoord->coord, &curCoord->workm);
            }

            curCoord = curCoord->sub;
        }
        while (curCoord != NULL);
    }

    // Set output.
    *outMat = rootCoord->workm;
}

void func_80049AF8(GsCOORDINATE2* rootCoord, MATRIX* outMat) // 0x80049AF8
{
    MATRIX localMat;

    Vw_CoordHierarchyMatrixCompute(rootCoord, &localMat);
    localMat.t[0] -= D_800C3868.t[0];
    localMat.t[1] -= D_800C3868.t[1];
    localMat.t[2] -= D_800C3868.t[2];
    Vw_MultiplyAndTransformMatrix(&VbWvsMatrix, &localMat, outMat);
}

void func_80049B6C(GsCOORDINATE2* rootCoord, MATRIX* outMat0, MATRIX* outMat1) // 0x80049B6C
{
    Vw_CoordHierarchyMatrixCompute(rootCoord, outMat0);
    outMat0->t[0] -= D_800C3868.t[0];
    outMat0->t[1] -= D_800C3868.t[1];
    outMat0->t[2] -= D_800C3868.t[2];

    Vw_MultiplyAndTransformMatrix(&VbWvsMatrix, outMat0, outMat1);
    outMat0->t[0] += D_800C3868.t[0];
    outMat0->t[1] += D_800C3868.t[1];
    outMat0->t[2] += D_800C3868.t[2];
}

void func_80049C2C(MATRIX* outMat, s32 x, s32 y, s32 z) // 0x80049C2C
{
    VECTOR in; // Q23.8
    VECTOR out;

    in.vx = Q12_TO_Q8(x);
    in.vy = Q12_TO_Q8(y);
    in.vz = Q12_TO_Q8(z);
    ApplyMatrixLV(&GsWSMATRIX, &in, &out);

    // Copy matrix fields as 32-bit words. Maybe inlined `CopyMatrix` func?
    *(u32*)&outMat->m[0][0] = *(u32*)&GsWSMATRIX.m[0][0];
    *(u32*)&outMat->m[0][2] = *(u32*)&GsWSMATRIX.m[0][2];
    *(u32*)&outMat->m[1][1] = *(u32*)&GsWSMATRIX.m[1][1];
    *(u32*)&outMat->m[2][0] = *(u32*)&GsWSMATRIX.m[2][0];
    outMat->m[2][2]         = GsWSMATRIX.m[2][2];

    outMat->t[0] = out.vx + GsWSMATRIX.t[0];
    outMat->t[1] = out.vy + GsWSMATRIX.t[1];
    outMat->t[2] = out.vz + GsWSMATRIX.t[2];
}

bool Vw_AabbVisibleInScreenCheck(s32 xMin, s32 xMax, s32 yMin, s32 yMax, s32 zMin, s32 zMax) // 0x80049D04
{
    s32     i;
    MATRIX  worldMat;
    SVECTOR vertOffset; // Q23.8
    DVECTOR screenPos;
    s32     depthDmy;
    s32     screenMinY;
    s32     screenMaxY;
    s32     screenMinX;
    s32     screenMaxX;
    s32     temp;
    s32     screenCenterX;
    s32     screenCenterY;
    u32     screenDepth;

    func_80049C2C(&worldMat, xMin, yMin, zMin);
    SetRotMatrix(&worldMat);
    SetTransMatrix(&worldMat);
    
    screenMaxY = INT_MAX + 1;
    screenMaxX = INT_MAX + 1;
    screenMinY = INT_MAX;
    screenMinX = INT_MAX;

    for (i = 0; i < BOX_VERT_COUNT; i++)
    {
        vertOffset.vx = (i & (1 << 0)) ? Q12_TO_Q8(xMax - xMin) : Q8(0.0f);
        vertOffset.vy = (i & (1 << 1)) ? Q12_TO_Q8(yMax - yMin) : Q8(0.0f);
        vertOffset.vz = (i & (1 << 2)) ? Q12_TO_Q8(zMax - zMin) : Q8(0.0f);

        screenDepth = RotTransPers(&vertOffset, &screenPos, &depthDmy, &depthDmy) - 1;

        if (screenDepth < 0x3FFE)
        {
            temp = screenPos.vx;
            if (temp < screenMaxX)
            {
                temp = screenMaxX;
            }
            screenMaxX = temp;

            temp = screenMinX;
            if (screenPos.vx < temp)
            {
                temp = screenPos.vx;
            }
            screenMinX = temp;

            temp = screenPos.vy;
            if (temp < screenMaxY)
            {
                temp = screenMaxY;
            }
            screenMaxY = temp;

            temp = screenMinY;
            if (screenPos.vy < temp)
            {
                temp = screenPos.vy;
            }
            screenMinY = temp;
        }
    }

    if (screenMaxX == INT_MAX)
    {
        return false;
    }

    screenCenterX = (g_GameWork.gsScreenWidth_588  / 2) + 2;
    screenCenterY = (g_GameWork.gsScreenHeight_58A / 2) + 2;

    if (screenMaxX < -screenCenterX || screenCenterX < screenMinX ||
        screenMaxY < -screenCenterY || screenCenterY < screenMinY)
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool Vw_AabbVisibleInFrustumCheck(MATRIX* modelMat, s16 minX, s16 minY, s16 minZ, s32 maxX, s32 maxY, s32 maxZ, u16 nearPlane, u16 farPlane) // 0x80049F38
{
    u8                              flags0[3];
    u8                              flags1[3];
    s_func_8004A54C                 sp20;
    DVECTOR                         screenPos;
    s32                             distToNearPlane;
    s32                             distToFarPlane;
    s32                             interpAlpha;
    s32                             transformedZ;
    s32                             flag1Idx;
    s32                             flag0Idx;
    s32                             pointsOutsideNearPlaneCount;
    s32                             i;
    s32                             pointsOutsideFarClipCount;
    s32                             var_v1;
    DVECTOR*                        screenPoints;
    u8*                             var_t1_2;
    SVECTOR*                        temp_a1_3;
    SVECTOR*                        temp_a2;
    SVECTOR*                        temp_a3;
    s_Vw_AabbVisibleInFrustumCheck* cullData;

    static u8 D_800AD480[24] =
    {
        0, 1, 1, 2, 2, 3, 3, 0,
        4, 5, 5, 6, 6, 7, 7, 4,
        0, 4, 1, 5, 2, 6, 3, 7
    };

    flags0[2] = 0;
    flags0[1] = 0;
    flags0[0] = 0;
    flags1[2] = 0;
    flags1[1] = 0;
    flags1[0] = 0;

    sp20.field_0[2][2] = 0;

    cullData          = (s_Vw_AabbVisibleInFrustumCheck*)PSX_SCRATCH;
    cullData->field_0 = *modelMat;

    ((u32*)&sp20)[1] = 0;
    ((u32*)&sp20)[0] = 0;

    GsSetLsMatrix(&cullData->field_0);

    cullData->field_20[0].vx = minX;
    cullData->field_20[0].vy = minY;
    cullData->field_20[0].vz = minZ;

    cullData->field_20[1].vx = maxX;
    cullData->field_20[1].vy = minY;
    cullData->field_20[1].vz = minZ;

    cullData->field_20[2].vx = maxX;
    cullData->field_20[2].vy = maxY;
    cullData->field_20[2].vz = minZ;

    cullData->field_20[3].vx = minX;
    cullData->field_20[3].vy = maxY;
    cullData->field_20[3].vz = minZ;

    cullData->field_20[4].vx = minX;
    cullData->field_20[4].vy = minY;
    cullData->field_20[4].vz = maxZ;

    cullData->field_20[5].vx = maxX;
    cullData->field_20[5].vy = minY;
    cullData->field_20[5].vz = maxZ;

    cullData->field_20[6].vx = maxX;
    cullData->field_20[6].vy = maxY;
    cullData->field_20[6].vz = maxZ;

    cullData->field_20[7].vx = minX;
    cullData->field_20[7].vy = maxY;
    cullData->field_20[7].vz = maxZ;

    cullData->field_C0  = 0;
    cullData->field_114 = 0;

    for (i = 0, pointsOutsideFarClipCount = 0, pointsOutsideNearPlaneCount = 0;
         i < 8;
         i++)
    {
        transformedZ = 4;
        transformedZ = RotTransPers(&cullData->field_20[i], &screenPos, &cullData->field_178, &cullData->field_178) * transformedZ;

        if (nearPlane < transformedZ)
        {
            pointsOutsideNearPlaneCount++;
        }

        if (transformedZ < farPlane)
        {
            pointsOutsideFarClipCount++;
        }
        else
        {
            cullData->field_118[cullData->field_114++] = screenPos;

            if (screenPos.vx >= -(g_GameWork.gsScreenWidth_588 >> 1))
            {
                if ((g_GameWork.gsScreenWidth_588 >> 1) < screenPos.vx)
                {
                    flag0Idx = 2;
                }
                else
                {
                    flag0Idx = 1;
                }
            }
            else
            {
                flag0Idx = 0;
            }

            if (screenPos.vy >= -(g_GameWork.gsScreenHeight_58A >> 1))
            {
                if ((g_GameWork.gsScreenHeight_58A >> 1) < screenPos.vy)
                {
                    flag1Idx = 2;
                }
                else
                {
                    flag1Idx = 1;
                }
            }
            else
            {
                flag1Idx = 0;
            }

            flags0[flag0Idx]                 |= 1 << 0;
            flags1[flag1Idx]                 |= 1 << 0;
            sp20.field_0[flag1Idx][flag0Idx] |= 1 << 0;
        }
    }

    if (pointsOutsideFarClipCount == 8)
    {
        return false;
    }

    if (pointsOutsideNearPlaneCount == 8)
    {
        return false;
    }

    if (sp20.field_0[1][1] != 0)
    {
        return true;
    }

    if (func_8004A54C(&sp20) != 1)
    {
        for (i = 0; i < 8; i++)
        {
            RotTrans(&cullData->field_20[i], &cullData->field_60[i], &cullData->field_178);
        }

        for (var_t1_2 = D_800AD480; (u32)var_t1_2 < ((u32)D_800AD480 + 24); var_t1_2 += 2)
        {
            distToFarPlane  = cullData->field_60[*var_t1_2].vz;
            distToNearPlane = cullData->field_60[*(var_t1_2 + 1)].vz;

            var_v1 = 0;

            if (distToFarPlane != distToNearPlane)
            {
                if (farPlane < distToFarPlane)
                {
                    var_v1 = (farPlane < distToNearPlane) ^ 1;
                }
                else if (farPlane < distToNearPlane)
                {
                    var_v1 = 1;
                }

                if (var_v1 == 1)
                {
                    interpAlpha = FP_TO(farPlane - distToFarPlane, Q8_SHIFT) / (distToNearPlane - distToFarPlane);

                    temp_a3   = &cullData->field_20[*var_t1_2];
                    temp_a1_3 = &cullData->field_20[*(var_t1_2 + 1)];

                    temp_a2 = &cullData->field_C4[cullData->field_C0];

                    temp_a2->vx = temp_a3->vx + FP_FROM(interpAlpha * (temp_a1_3->vx - temp_a3->vx), Q8_SHIFT);
                    temp_a2->vy = temp_a3->vy + FP_FROM(interpAlpha * (temp_a1_3->vy - temp_a3->vy), Q8_SHIFT);
                    temp_a2->vz = temp_a3->vz + FP_FROM(interpAlpha * (temp_a1_3->vz - temp_a3->vz), Q8_SHIFT);

                    cullData->field_C0++;
                }
            }
        }

        for (screenPoints = &cullData->field_118[cullData->field_114], i = 0; i < cullData->field_C0; i++, screenPoints++)
        {
            RotTransPers(&cullData->field_C4[i], screenPoints, &cullData->field_178, &cullData->field_178);

            if (screenPoints->vx >= -(g_GameWork.gsScreenWidth_588 >> 1))
            {
                if ((g_GameWork.gsScreenWidth_588 >> 1) < screenPoints->vx)
                {
                    flag0Idx = 2;
                }
                else
                {
                    flag0Idx = 1;
                }
            }
            else
            {
                flag0Idx = 0;
            }

            if (screenPoints->vy >= -(g_GameWork.gsScreenHeight_58A >> 1))
            {
                if ((g_GameWork.gsScreenHeight_58A >> 1) < screenPoints->vy)
                {
                    flag1Idx = 2;
                }
                else
                {
                    flag1Idx = 1;
                }
            }
            else
            {
                flag1Idx = 0;
            }

            flags0[flag0Idx] |= 1 << 0;
            flags1[flag1Idx] |= 1 << 0;

            cullData->field_114++;
        }

        if (flags0[0] == 0 && flags0[1] == 0)
        {
            return false;
        }
        else if (flags0[2] == 0 && flags0[1] == 0)
        {
            return false;
        }
        else if (flags1[0] == 0 && flags1[1] == 0)
        {
            return false;
        }
        else if (flags1[2] != 0)
        {
            return true;
        }
        else if (flags1[1] == 0)
        {
            return false;
        }
    }

    return true;
}

bool func_8004A54C(s_func_8004A54C* arg0) // 0x8004A54C
{
    bool cond0;
    bool cond1;
    bool cond2;
    bool cond3;

    cond0 = false;
    cond1 = false;
    cond2 = false;
    cond3 = false;

    if (arg0->field_0[1][1] != 0)
    {
        return true;
    }

    if (arg0->field_0[1][0] || (arg0->field_0[0][0] && arg0->field_0[2][0]))
    {
        cond0 = true;
    }
    if (arg0->field_0[1][2] || (arg0->field_0[0][2] && arg0->field_0[2][2]))
    {
        cond1 = true;
    }
    if (cond0 && cond1)
    {
        return true;
    }

    if (arg0->field_0[0][1] || (arg0->field_0[0][0] && arg0->field_0[0][2]))
    {
        cond2 = true;
    }
    if (arg0->field_0[2][1] || (arg0->field_0[2][0] && arg0->field_0[2][2]))
    {
        cond3 = true;
    }
    if (cond2 && cond3)
    {
        return true;
    }

    return false;
}

void vwAngleToVector(SVECTOR* vec, const SVECTOR* ang, s32 r) // 0x8004A66C
{
    s32 entou_r; // "Entou" means "cylinder" in Japanese. Refers to 2D radius on XZ plane.
    
    entou_r = FP_MULTIPLY(r, Math_Cos(ang->vx), Q12_SHIFT);
    vec->vy = FP_MULTIPLY(-r, Math_Sin(ang->vx), Q12_SHIFT);
    vec->vx = FP_MULTIPLY(entou_r, Math_Sin(ang->vy), Q12_SHIFT);
    vec->vz = FP_MULTIPLY(entou_r, Math_Cos(ang->vy), Q12_SHIFT);
}

q19_12 vwVectorToAngle(SVECTOR* ang, const SVECTOR* vec) // 0x8004A714
{
    VECTOR localVec;
    q19_12 ret_r;

    localVec.vx = vec->vx;
    localVec.vy = vec->vy;
    localVec.vz = vec->vz;
    Square0(&localVec, &localVec);
    ret_r = SquareRoot0(localVec.vx + localVec.vy + localVec.vz);

    ang->vx = ratan2(-vec->vy, SquareRoot0(localVec.vx + localVec.vz));
    ang->vy = ratan2(vec->vx, vec->vz);
    ang->vz = FP_ANGLE(0.0f);
    return ret_r;
}

s32 vwOresenHokan(const s32* y_ary, s32 y_suu, s32 input_x, s32 min_x, s32 max_x) // 0x8004A7C8
{
    // `y_ary` = array of Y values.
    // `y_suu` = `y_ary` size.

    s32 amari;    // Remainder when calculating position within interval.
    s32 kukan_w;  // Width of each interval between Y values.
    s32 kukan_no; // Index of the interval containing `input_x` angle.
    s32 output_y; // Interpolated output Y value.

    if (input_x >= max_x)
    {
        output_y = y_ary[y_suu - 1];
    }
    else
    {
        if (input_x < min_x)
        {
            output_y = y_ary[0];
        }
        else
        {
            kukan_w  = (max_x - min_x) / (y_suu - 1);
            amari    = (input_x - min_x) % kukan_w;
            kukan_no = (input_x - min_x) / kukan_w;
            if (kukan_no >= (y_suu - 1))
            {
                output_y = y_ary[y_suu - 1];
            }
            else
            {
                if (kukan_no < 0)
                {
                    output_y = y_ary[0];
                }
                else
                {
                    output_y = ((y_ary[kukan_no] * (kukan_w - amari)) + (y_ary[kukan_no + 1] * amari)) / kukan_w;
                }
            }
        }
    }

    return output_y;
}
