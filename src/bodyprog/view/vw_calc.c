#include "game.h"
#include "inline_no_dmpsx.h"
#include "gtemac.h"
#include "bodyprog/bodyprog.h"
#include "bodyprog/vw_system.h"
#include "bodyprog/math/math.h"

// Reference view transform?
extern MATRIX D_800C3868;

void vwRenewalXZVelocityToTargetPos(s32* velo_x, s32* velo_z, const VECTOR3* now_pos, const VECTOR3* tgt_pos, s32 tgt_r,
                                    s32 accel, s32 total_max_spd, s32 dec_forwd_lim_spd, s32 dec_accel_side) // 0x80048F28
{
// SH2 locals
#if 0
    /* 0x1d */ float vec_xz[4];
    /* 0x1d */ float lim_spd;
    /* 0x1d */ float to_tgt_dist;
    /* 0x16 */ float to_tgt_ang_y;
    /* 0x18 */ float ang_y;
    /* 0x1d */ float spd;
    /* 0x2 */ float add_spd;
    /* 0x1d */ float cam2tgt_dir_vec[4];
    /* 0x1d */ float cam_mv_ang_y;
    /* 0x1d */ float cam2tgt_ang_y;
#endif

    SVECTOR unused; // `cam2tgt_dir_vec`?
    s16     temp_v0;
    s32     ang_y;
    s32     temp_s0;
    s32     to_tgt_ang_y;
    s32     add_spd;
    s32     temp_s1_2;
    s32     temp_s1_3;
    s32     temp_v0_2;
    s32     var_s1;

    temp_v0 = ratan2(tgt_pos->vx - now_pos->vx, tgt_pos->vz - now_pos->vz);

    // `shSinCosV` is called in SH2 while SH just calls `Math_Sin`/`Math_Cos` and does nothing with result.
    unused.vx = Math_Sin(temp_v0);
    unused.vy = Math_Cos(temp_v0);

    ratan2(*velo_x, *velo_z);

    add_spd = Math_MulFixed(accel, g_DeltaTime0, Q12_SHIFT);
    *velo_x += FP_MULTIPLY(add_spd, Math_Sin(temp_v0), Q12_SHIFT);
    *velo_z += FP_MULTIPLY(add_spd, Math_Cos(temp_v0), Q12_SHIFT);

    temp_v0_2 = Vc_VectorMagnitudeCalc(*velo_x, 0, *velo_z);
    if (total_max_spd < temp_v0_2)
    {
        temp_s1_2 = temp_v0_2 - total_max_spd;
        ang_y = ratan2(*velo_x, *velo_z);
        *velo_x -= Math_MulFixed(temp_s1_2, Math_Sin(ang_y), Q12_SHIFT);
        *velo_z -= Math_MulFixed(temp_s1_2, Math_Cos(ang_y), Q12_SHIFT);
    }

    temp_s1_3    = tgt_pos->vx - now_pos->vx;
    temp_s0      = tgt_pos->vz - now_pos->vz;
    to_tgt_ang_y = ratan2(temp_s1_3, temp_s0);
    var_s1       = Math_MulFixed(dec_forwd_lim_spd, Vc_VectorMagnitudeCalc(temp_s1_3, 0, temp_s0) - tgt_r, Q12_SHIFT);

    if (var_s1 < 0)
    {
        var_s1 = 0;
    }

    vwLimitOverLimVector(velo_x, velo_z, var_s1, to_tgt_ang_y);
    vwDecreaseSideOfVector(velo_x, velo_z, Math_MulFixed(dec_accel_side, g_DeltaTime0, Q12_SHIFT), var_s1 >> 1, to_tgt_ang_y);
}

void vwLimitOverLimVector(s32* vec_x, s32* vec_z, s32 lim_vec_len, s16 lim_vec_ang_y) // 0x8004914C
{
    s32 over_spd;
    s32 lim_spd_dir_x;
    s32 lim_spd_dir_z;

    lim_spd_dir_x = Math_Sin(lim_vec_ang_y);
    lim_spd_dir_z = Math_Cos(lim_vec_ang_y);

    over_spd = (Math_MulFixed(*vec_x, lim_spd_dir_x, Q12_SHIFT) + Math_MulFixed(*vec_z, lim_spd_dir_z, Q12_SHIFT)) - lim_vec_len;
    if (over_spd > 0)
    {
        *vec_x -= Math_MulFixed(over_spd, lim_spd_dir_x, Q12_SHIFT);
        *vec_z -= Math_MulFixed(over_spd, lim_spd_dir_z, Q12_SHIFT);
    }
}

void vwDecreaseSideOfVector(s32* vec_x, s32* vec_z, s32 dec_val, s32 max_side_vec_len, s16 dir_ang_y)
{
    s32 temp_s1;
    s32 var_s1;

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
            var_s1 = 0;
        }
        else
        {
            var_s1 = var_s1 + dec_val;
        }
    }

    *vec_x += Math_MulFixed(var_s1 - temp_s1, Math_Sin(dir_ang_y + FP_ANGLE(90.0f)), Q12_SHIFT);
    *vec_z += Math_MulFixed(var_s1 - temp_s1, Math_Cos(dir_ang_y + FP_ANGLE(90.0f)), Q12_SHIFT);
}

s32 vwRetNewVelocityToTargetVal(s32 now_spd, s32 mv_pos, s32 tgt_pos, s32 accel, s32 total_max_spd, s32 dec_val_lim_spd)
{
    s32 pos_diff;
    s32 abs_pos_diff;
    s32 spd_lim;
    s32 new_spd;
    s32 result_spd;

    pos_diff = tgt_pos - mv_pos;

    if (pos_diff >= 0)
    {
        new_spd = Math_MulFixed(accel, g_DeltaTime0, Q12_SHIFT) + now_spd;
    }
    else
    {
        new_spd = now_spd - Math_MulFixed(accel, g_DeltaTime0, Q12_SHIFT);
    }

    new_spd      = CLAMP(new_spd, -total_max_spd, total_max_spd);
    abs_pos_diff = pos_diff < 0 ? -pos_diff : pos_diff;
    spd_lim      = Math_MulFixed(dec_val_lim_spd, abs_pos_diff, Q12_SHIFT);

    if (pos_diff >= 0)
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

s32 vwRetNewAngSpdToTargetAng(s32 now_ang_spd, s16 now_ang, s16 tgt_ang, s32 accel_spd, s32 total_max_ang_spd, s32 dec_val_lim_spd) // 0x80049464
{
    return vwRetNewVelocityToTargetVal(now_ang_spd, 0, FP_ANGLE_NORM_S(tgt_ang - now_ang), accel_spd, total_max_ang_spd, dec_val_lim_spd);
}

s32 func_800494B0(s32 arg0, s32 arg1, s32 arg2)
{
    s32 range  = FP_MULTIPLY_PRECISE(arg2, g_DeltaTime0, Q12_SHIFT);
    s32 arange = arg1 - arg0;
    arange     = CLAMP(arange, -range, range);

    if (g_DeltaTime0 == 0)
    {
        return 0;
    }

    return FP_TO(arange, Q12_SHIFT) / g_DeltaTime0;
}

s32 func_80049530(VECTOR* arg0, VECTOR* arg1) // 0x80049530
{
    VECTOR sp10;
    s32    ret;

    ApplyRotMatrixLV(arg0, &sp10);

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
    s32 r_xz = SquareRoot0((mat->m[0][2] * mat->m[0][2]) + (mat->m[2][2] * mat->m[2][2]));
    ang->vx  = ratan2(-mat->m[1][2], r_xz);

    if (ang->vx == FP_ANGLE(90.0f))
    {
        ang->vz = 0;
        ang->vy = ratan2(mat->m[0][1], mat->m[2][1]);
    }
    else if (ang->vx == FP_ANGLE(-90.0f))
    {
        ang->vz = 0;
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

    VbWvsMatrix.t[2] = 0;
    VbWvsMatrix.t[1] = 0;
    VbWvsMatrix.t[0] = 0;

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
    GsCOORDINATE2 sp10;
    SVECTOR       sp60;
    SVECTOR       sp68;

    sp10.flg   = false;
    sp10.super = rview->super;
    sp68.vx    = rview->vr.vx - rview->vp.vx;
    sp68.vy    = rview->vr.vy - rview->vp.vy;
    sp68.vz    = rview->vr.vz - rview->vp.vz;
    vwVectorToAngle(&sp60, &sp68);
    func_80096E78(&sp60, &sp10.coord);

    sp10.coord.t[0] = rview->vp.vx;
    sp10.coord.t[1] = rview->vp.vy;
    sp10.coord.t[2] = rview->vp.vz;
    vbSetWorldScreenMatrix(&sp10);
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
    VECTOR in;  // Q23.8
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
    
    screenMaxY = 0x80000000;
    screenMaxX = 0x80000000;
    screenMinY = 0x7FFFFFFF;
    screenMinX = 0x7FFFFFFF;

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

    if (screenMaxX == 0x7FFFFFFF)
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

    for (i = 0, pointsOutsideFarClipCount = 0, pointsOutsideNearPlaneCount = 0; i < 8; i++)
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
    s32 var_v1 = 0;
    s32 var_a1 = 0;
    s32 var_a2 = 0;
    s32 var_a3 = 0;

    if (arg0->field_0[1][1] != 0)
    {
        return true;
    }

    if (arg0->field_0[1][0] || (arg0->field_0[0][0] && arg0->field_0[2][0]))
    {
        var_v1 = 1;
    }
    if (arg0->field_0[1][2] || (arg0->field_0[0][2] && arg0->field_0[2][2]))
    {
        var_a1 = 1;
    }
    if (var_v1 && var_a1)
    {
        return true;
    }

    if (arg0->field_0[0][1] || (arg0->field_0[0][0] && arg0->field_0[0][2]))
    {
        var_a2 = 1;
    }
    if (arg0->field_0[2][1] || (arg0->field_0[2][0] && arg0->field_0[2][2]))
    {
        var_a3 = 1;
    }
    if (var_a2 && var_a3)
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

s32 vwVectorToAngle(SVECTOR* ang, const SVECTOR* vec) // 0x8004A714
{
    VECTOR localVec;
    s32    ret_r;

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
