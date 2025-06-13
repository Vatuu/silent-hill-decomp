#include "game.h"
#include "inline_no_dmpsx.h"
#include "gtemac.h"
#include "bodyprog/bodyprog.h"
#include "bodyprog/vw_system.h"
#include "bodyprog/math.h"

extern MATRIX D_800C3868;

void vwRenewalXZVelocityToTargetPos(s32* velo_x, s32* velo_z, VECTOR3* now_pos, VECTOR3* tgt_pos, s32 tgt_r,
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

    // `shSinCosV` is called in SH2 while SH just calls `shRsin`/`shRcos` and does nothing with result.
    unused.vx = shRsin(temp_v0);
    unused.vy = shRcos(temp_v0);

    ratan2(*velo_x, *velo_z);

    add_spd = Math_MulFixed(accel, g_DeltaTime0, Q12_SHIFT);
    *velo_x += FP_MULTIPLY(add_spd, shRsin(temp_v0), Q12_SHIFT);
    *velo_z += FP_MULTIPLY(add_spd, shRcos(temp_v0), Q12_SHIFT);

    temp_v0_2 = Math_VectorMagnitude(*velo_x, 0, *velo_z);
    if (total_max_spd < temp_v0_2)
    {
        temp_s1_2 = temp_v0_2 - total_max_spd;
        ang_y = ratan2(*velo_x, *velo_z);
        *velo_x -= Math_MulFixed(temp_s1_2, shRsin(ang_y), Q12_SHIFT);
        *velo_z -= Math_MulFixed(temp_s1_2, shRcos(ang_y), Q12_SHIFT);
    }

    temp_s1_3    = tgt_pos->vx - now_pos->vx;
    temp_s0      = tgt_pos->vz - now_pos->vz;
    to_tgt_ang_y = ratan2(temp_s1_3, temp_s0);
    var_s1       = Math_MulFixed(dec_forwd_lim_spd, Math_VectorMagnitude(temp_s1_3, 0, temp_s0) - tgt_r, Q12_SHIFT);

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

    lim_spd_dir_x = shRsin(lim_vec_ang_y);
    lim_spd_dir_z = shRcos(lim_vec_ang_y);

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

    var_s1 = Math_MulFixed(*vec_x, shRsin(dir_ang_y + 0x400), 0xC) +
             Math_MulFixed(*vec_z, shRcos(dir_ang_y + 0x400), 0xC);

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

    *vec_x += Math_MulFixed(var_s1 - temp_s1, shRsin(dir_ang_y + 0x400), 0xC);
    *vec_z += Math_MulFixed(var_s1 - temp_s1, shRcos(dir_ang_y + 0x400), 0xC);
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
    return vwRetNewVelocityToTargetVal(now_ang_spd, 0, ((tgt_ang - now_ang) << 20) >> 20, accel_spd, total_max_ang_spd, dec_val_lim_spd);
}

s32 func_800494B0(s32 arg0, s32 arg1, s32 arg2)
{
    s32 range  = FP_MULTIPLY((s64)arg2, (s64)g_DeltaTime0, Q12_SHIFT);
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
        "cfc2	    $12, $5;"
        "lw         $t5, 0x0(%0);"
        "mtc2	    $12, $2;"
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
        "mfc2	$12, $2;"
        "mfc2	$13, $3;"
        "mfc2	$14, $4;"
        "ctc2	$12, $5;"
        "ctc2	$13, $6;"
        "ctc2	$14, $7;"
        "mfc2	$v0, $19;"
        "nop;"
        "sra	$v0, $v0, 2;" ::: "$12", "$13", "$14");
}

void vwMatrixToAngleYXZ(SVECTOR* ang, MATRIX* mat) // 0x800495D4
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

void func_800496AC(MATRIX* mat0, MATRIX* mat1, MATRIX* mat2) // 0x800496AC
{
    gte_SetRotMatrix(mat0);
    gte_SetTransMatrix(mat0);
    gte_ldclmv(mat1);
    gte_rtir();
    gte_stclmv(mat2);
    gte_ldclmv((MATRIX*)(mat1->m[0] + 1));
    gte_rtir();
    gte_stclmv((MATRIX*)(mat2->m[0] + 1));
    gte_ldclmv((MATRIX*)(mat1->m[0] + 2));
    gte_rtir();
    gte_stclmv((MATRIX*)(mat2->m[0] + 2));
    gte_ldlvl((VECTOR*)mat1->t);
    gte_rtirtr();
    gte_stlvnl((VECTOR*)mat2->t);
}

void vbSetWorldScreenMatrix(GsCOORDINATE2* coord) // 0x800497E4
{
    MATRIX work;
    VECTOR sp30;

    func_80049984(coord, &D_800C3868);
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

    sp30.vx = -D_800C3868.t[0];
    sp30.vy = -D_800C3868.t[1];
    sp30.vz = -D_800C3868.t[2];
    ApplyMatrixLV(&VbWvsMatrix, &sp30, (VECTOR*)&GsWSMATRIX.t);
}

void vbSetRefView(VbRVIEW* rview) // 0x800498D8
{
    GsCOORDINATE2 sp10;
    SVECTOR       sp60;
    SVECTOR       sp68;

    sp10.flg   = 0;
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

void func_80049984(GsCOORDINATE2* coord, MATRIX* mat) // 0x80049984
{
    GsCOORDINATE2* coord0;
    GsCOORDINATE2* coord1;
    GsCOORDINATE2* coord2;

    if (coord == NULL)
    {
        *mat = GsIDMATRIX;
    }

    coord2 = coord;
    coord0 = NULL;

    while (true)
    {
        coord1 = coord2->super;
        if (coord2->flg != 0)
        {
            break;
        }

        coord0 = coord2;
        if (coord1 != NULL)
        {
            coord1->sub = coord2;
            coord2      = coord1;
        }
        else
        {
            break;
        }
    }

    if (coord0 != NULL)
    {
        coord2     = coord0;
        coord->sub = NULL;
        do
        {
            coord0 = coord2->super;
            coord2->flg++;
            if (coord0 == NULL)
            {
                coord2->workm = coord2->coord;
            }
            else
            {
                func_800496AC(&coord0->workm, &coord2->coord, &coord2->workm);
            }

            coord2 = coord2->sub;
        } while (coord2 != NULL);
    }

    *mat = coord->workm;
}

void func_80049AF8(GsCOORDINATE2* coord, MATRIX* mat)
{
    MATRIX localmat;

    func_80049984(coord, &localmat);

    localmat.t[0] -= D_800C3868.t[0];
    localmat.t[1] -= D_800C3868.t[1];
    localmat.t[2] -= D_800C3868.t[2];

    func_800496AC(&VbWvsMatrix, &localmat, mat);
}

void func_80049B6C(GsCOORDINATE2* coord, MATRIX* mat0, MATRIX* mat1)
{
    func_80049984(coord, mat0);
    mat0->t[0] -= D_800C3868.t[0];
    mat0->t[1] -= D_800C3868.t[1];
    mat0->t[2] -= D_800C3868.t[2];

    func_800496AC(&VbWvsMatrix, mat0, mat1);
    mat0->t[0] += D_800C3868.t[0];
    mat0->t[1] += D_800C3868.t[1];
    mat0->t[2] += D_800C3868.t[2];
}

void func_80049C2C(MATRIX* mat, s32 x, s32 y, s32 z)
{
    VECTOR input;
    VECTOR output;

    input.vx = FP_FROM(x, Q4_SHIFT);
    input.vy = FP_FROM(y, Q4_SHIFT);
    input.vz = FP_FROM(z, Q4_SHIFT);
    ApplyMatrixLV(&GsWSMATRIX, &input, &output);

    // Copies matrix fields as 32-bit words, maybe an inlined CopyMatrix func?
    *(u32*)&mat->m[0][0] = *(u32*)&GsWSMATRIX.m[0][0];
    *(u32*)&mat->m[0][2] = *(u32*)&GsWSMATRIX.m[0][2];
    *(u32*)&mat->m[1][1] = *(u32*)&GsWSMATRIX.m[1][1];
    *(u32*)&mat->m[2][0] = *(u32*)&GsWSMATRIX.m[2][0];
    mat->m[2][2]         = GsWSMATRIX.m[2][2];

    mat->t[0] = output.vx + GsWSMATRIX.t[0];
    mat->t[1] = output.vy + GsWSMATRIX.t[1];
    mat->t[2] = output.vz + GsWSMATRIX.t[2];
}

s32 func_80049D04(s32 x0, s32 x1, s32 y0, s32 y1, s32 z0, s32 z1) // 0x80049D04
{
    s32     i;
    MATRIX  mat;
    SVECTOR rot;
    DVECTOR sxy;
    s32     dmy;
    s32     sp44;
    s32     var_fp;
    s32     var_s5;
    s32     var_s7;
    s32     temp;
    s32     posX;
    s32     poxY;
    u32     otz;

    func_80049C2C(&mat, x0, y0, z0);
    SetRotMatrix(&mat);
    SetTransMatrix(&mat);

    var_fp = 0x80000000;
    var_s7 = 0x80000000;
    sp44   = 0x7FFFFFFF;
    var_s5 = 0x7FFFFFFF;

    for (i = 0; i < 8; i++)
    {
        if (i & 1 != 0)
        {
            rot.vx = (x1 - x0) >> 4;
        }
        else
        {
            rot.vx = 0;
        }

        if (i & 2)
        {
            rot.vy = (y1 - y0) >> 4;
        }
        else
        {
            rot.vy = 0;
        }

        if (i & 4)
        {
            rot.vz = (z1 - z0) >> 4;
        }
        else
        {
            rot.vz = 0;
        }

        otz = RotTransPers(&rot, &sxy, &dmy, &dmy) - 1;

        if (otz < 0x3FFE)
        {
            temp = sxy.vx;
            if (temp < var_s7)
            {
                temp = var_s7;
            }
            var_s7 = temp;

            temp = var_s5;
            if (sxy.vx < temp)
            {
                temp = sxy.vx;
            }
            var_s5 = temp;

            temp = sxy.vy;
            if (temp < var_fp)
            {
                temp = var_fp;
            }
            var_fp = temp;

            temp = sp44;
            if (sxy.vy < temp)
            {
                temp = sxy.vy;
            }
            sp44 = temp;
        }
    }

    if (var_s7 == 0x7FFFFFFF)
    {
        return 0;
    }

    posX = (g_GameWork.gsScreenWidth_588 / 2) + 2;
    poxY = (g_GameWork.gsScreenHeight_58A / 2) + 2;

    if (var_s7 < -posX || posX < var_s5 || var_fp < -poxY || poxY < sp44)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

s32 func_80049F38(MATRIX* arg0, s16 arg1, s16 arg2, s16 arg3, s32 arg4, s32 arg5, s32 arg6, u16 arg7, u16 arg8) // 0x80049F38
{
    u8               sp10[3];
    u8               sp18[3];
    s_func_8004A54C  sp20;
    DVECTOR          sxy;
    s32              temp_a0_2;
    s32              temp_a1_2;
    s32              temp_lo;
    s32              otz;
    s32              var_a0_2;
    s32              var_a2;
    s32              var_fp;
    s32              i;
    s32              var_t0;
    s32              var_v1;
    DVECTOR*         var_s0_2;
    u8*              var_t1_2;
    SVECTOR*         temp_a1_3;
    SVECTOR*         temp_a2;
    SVECTOR*         temp_a3;
    s_func_80049F38* ptr;

    sp10[2] = 0;
    sp10[1] = 0;
    sp10[0] = 0;
    sp18[2] = 0;
    sp18[1] = 0;
    sp18[0] = 0;

    sp20.field_0[2][2] = 0;

    ptr          = (s_func_80049F38*)PSX_SCRATCH;
    ptr->field_0 = *arg0;

    ((u32*)&sp20)[1] = 0;
    ((u32*)&sp20)[0] = 0;

    GsSetLsMatrix(&ptr->field_0);

    ptr->field_20[0].vx = arg1;
    ptr->field_20[0].vy = arg2;
    ptr->field_20[0].vz = arg3;

    ptr->field_20[1].vx = arg4;
    ptr->field_20[1].vy = arg2;
    ptr->field_20[1].vz = arg3;

    ptr->field_20[2].vx = arg4;
    ptr->field_20[2].vy = arg5;
    ptr->field_20[2].vz = arg3;

    ptr->field_20[3].vx = arg1;
    ptr->field_20[3].vy = arg5;
    ptr->field_20[3].vz = arg3;

    ptr->field_20[4].vx = arg1;
    ptr->field_20[4].vy = arg2;
    ptr->field_20[4].vz = arg6;

    ptr->field_20[5].vx = arg4;
    ptr->field_20[5].vy = arg2;
    ptr->field_20[5].vz = arg6;

    ptr->field_20[6].vx = arg4;
    ptr->field_20[6].vy = arg5;
    ptr->field_20[6].vz = arg6;

    ptr->field_20[7].vx = arg1;
    ptr->field_20[7].vy = arg5;
    ptr->field_20[7].vz = arg6;

    ptr->field_C0  = 0;
    ptr->field_114 = 0;

    for (i = 0, var_t0 = 0, var_fp = 0; i < 8; i++)
    {
        otz = 4;
        otz = RotTransPers(&ptr->field_20[i], &sxy, &ptr->field_178, &ptr->field_178) * otz;

        if (arg7 < otz)
        {
            var_fp++;
        }

        if (otz < arg8)
        {
            var_t0++;
        }
        else
        {
            ptr->field_118[ptr->field_114++] = sxy;

            if (sxy.vx >= -(g_GameWork.gsScreenWidth_588 >> 1))
            {
                if ((g_GameWork.gsScreenWidth_588 >> 1) < sxy.vx)
                {
                    var_a2 = 2;
                }
                else
                {
                    var_a2 = 1;
                }
            }
            else
            {
                var_a2 = 0;
            }

            if (sxy.vy >= -(g_GameWork.gsScreenHeight_58A >> 1))
            {
                if ((g_GameWork.gsScreenHeight_58A >> 1) < sxy.vy)
                {
                    var_a0_2 = 2;
                }
                else
                {
                    var_a0_2 = 1;
                }
            }
            else
            {
                var_a0_2 = 0;
            }

            sp10[var_a2] |= 1;
            sp18[var_a0_2] |= 1;
            sp20.field_0[var_a0_2][var_a2] |= 1;
        }
    }

    if (var_t0 == 8)
    {
        return 0;
    }

    if (var_fp == 8)
    {
        return 0;
    }

    if (sp20.field_0[1][1] != 0)
    {
        return 1;
    }

    if (func_8004A54C(&sp20) != 1)
    {
        for (i = 0; i < 8; i++)
        {
            RotTrans(&ptr->field_20[i], &ptr->field_60[i], &ptr->field_178);
        }

        for (var_t1_2 = D_800AD480; (u32)var_t1_2 < (u32)D_800AD480 + 24; var_t1_2 += 2)
        {
            temp_a1_2 = ptr->field_60[*var_t1_2].vz;
            temp_a0_2 = ptr->field_60[*(var_t1_2 + 1)].vz;

            var_v1 = 0;

            if (temp_a1_2 != temp_a0_2)
            {
                if (arg8 < temp_a1_2)
                {
                    var_v1 = (arg8 < temp_a0_2) ^ 1;
                }
                else if (arg8 < temp_a0_2)
                {
                    var_v1 = 1;
                }

                if (var_v1 == 1)
                {
                    temp_lo = ((arg8 - temp_a1_2) << 8) / (temp_a0_2 - temp_a1_2);

                    temp_a3   = &ptr->field_20[*var_t1_2];
                    temp_a1_3 = &ptr->field_20[*(var_t1_2 + 1)];

                    temp_a2 = &ptr->field_C4[ptr->field_C0];

                    temp_a2->vx = temp_a3->vx + ((temp_lo * (temp_a1_3->vx - temp_a3->vx)) >> 8);
                    temp_a2->vy = temp_a3->vy + ((temp_lo * (temp_a1_3->vy - temp_a3->vy)) >> 8);
                    temp_a2->vz = temp_a3->vz + ((temp_lo * (temp_a1_3->vz - temp_a3->vz)) >> 8);

                    ptr->field_C0++;
                }
            }
        }

        for (var_s0_2 = &ptr->field_118[ptr->field_114], i = 0; i < ptr->field_C0; i++, var_s0_2++)
        {
            RotTransPers(&ptr->field_C4[i], var_s0_2, &ptr->field_178, &ptr->field_178);

            if (var_s0_2->vx >= -(g_GameWork.gsScreenWidth_588 >> 1))
            {
                if ((g_GameWork.gsScreenWidth_588 >> 1) < var_s0_2->vx)
                {
                    var_a2 = 2;
                }
                else
                {
                    var_a2 = 1;
                }
            }
            else
            {
                var_a2 = 0;
            }

            if (var_s0_2->vy >= -(g_GameWork.gsScreenHeight_58A >> 1))
            {
                if ((g_GameWork.gsScreenHeight_58A >> 1) < var_s0_2->vy)
                {
                    var_a0_2 = 2;
                }
                else
                {
                    var_a0_2 = 1;
                }
            }
            else
            {
                var_a0_2 = 0;
            }

            sp10[var_a2] |= 1;
            sp18[var_a0_2] |= 1;

            ptr->field_114++;
        }

        if ((sp10[0] == 0) && (sp10[1] == 0))
        {
            return 0;
        }
        else if ((sp10[2] == 0) && (sp10[1] == 0))
        {
            return 0;
        }
        else if ((sp18[0] == 0) && (sp18[1] == 0))
        {
            return 0;
        }
        else if (sp18[2] != 0)
        {
            return 1;
        }
        else if (sp18[1] == 0)
        {
            return 0;
        }
    }
    return 1;
}

s32 func_8004A54C(s_func_8004A54C* arg0) // 0x8004A54C
{
    s32 var_v1 = 0;
    s32 var_a1 = 0;
    s32 var_a2 = 0;
    s32 var_a3 = 0;

    if (arg0->field_0[1][1] != 0)
    {
        return 1;
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
        return 1;
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
        return 1;
    }

    return 0;
}

void vwAngleToVector(SVECTOR* vec, SVECTOR* ang, s32 r) // 0x8004A66C
{
    s32 entou_r;
    
    entou_r = FP_MULTIPLY(r, shRcos(ang->vx), Q12_SHIFT);
    vec->vy = FP_MULTIPLY(-r, shRsin(ang->vx), Q12_SHIFT);
    vec->vx = FP_MULTIPLY(entou_r, shRsin(ang->vy), Q12_SHIFT);
    vec->vz = FP_MULTIPLY(entou_r, shRcos(ang->vy), Q12_SHIFT);
}

s32 vwVectorToAngle(SVECTOR* ang, SVECTOR* vec) // 0x8004A714
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
    ang->vz = 0;
    return ret_r;
}

s32 vwOresenHokan(s32* y_ary, s32 y_suu, s32 input_x, s32 min_x, s32 max_x) // 0x8004A7C8
{
    s32 amari;    // Remainder when calculating position within interval.
    s32 kukan_w;  // Width of each interval between Y values.
    s32 kukan_no; // Index of the interval containing input_x.
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
