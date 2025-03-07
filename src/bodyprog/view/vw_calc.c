#include "game.h"

#include "bodyprog/vw_system.h"
#include "bodyprog/math.h"

extern MATRIX D_800C3868;
extern MATRIX D_800C6FC0; // Might be psyq GsWSMATRIX.

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

    SVECTOR unused; // cam2tgt_dir_vec?
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

    // shSinCosV is called in SH2 while SH just calls shRsin/shRcos and does nothing with result.
    unused.vx = shRsin(temp_v0);
    unused.vy = shRcos(temp_v0);

    ratan2(*velo_x, *velo_z);

    add_spd = Math_MulFixed(accel, g_CurDeltaTime, FP_SIN_Q);
    *velo_x += (add_spd * shRsin(temp_v0)) >> FP_SIN_Q;
    *velo_z += (add_spd * shRcos(temp_v0)) >> FP_SIN_Q;

    temp_v0_2 = Math_VectorMagnitude(*velo_x, 0, *velo_z);
    if (total_max_spd < temp_v0_2)
    {
        temp_s1_2 = temp_v0_2 - total_max_spd;
        ang_y     = ratan2(*velo_x, *velo_z);
        *velo_x -= Math_MulFixed(temp_s1_2, shRsin(ang_y), FP_SIN_Q);
        *velo_z -= Math_MulFixed(temp_s1_2, shRcos(ang_y), FP_SIN_Q);
    }

    temp_s1_3    = tgt_pos->vx - now_pos->vx;
    temp_s0      = tgt_pos->vz - now_pos->vz;
    to_tgt_ang_y = ratan2(temp_s1_3, temp_s0);
    var_s1       = Math_MulFixed(dec_forwd_lim_spd, Math_VectorMagnitude(temp_s1_3, 0, temp_s0) - tgt_r, FP_SIN_Q);

    if (var_s1 < 0)
        var_s1 = 0;

    vwLimitOverLimVector(velo_x, velo_z, var_s1, to_tgt_ang_y);
    vwDecreaseSideOfVector(velo_x, velo_z, Math_MulFixed(dec_accel_side, g_CurDeltaTime, FP_SIN_Q), var_s1 >> 1, to_tgt_ang_y);
}

void vwLimitOverLimVector(s32* vec_x, s32* vec_z, s32 lim_vec_len, s16 lim_vec_ang_y) // 0x8004914C
{
    s32 over_spd;
    s32 lim_spd_dir_x;
    s32 lim_spd_dir_z;

    lim_spd_dir_x = shRsin(lim_vec_ang_y);
    lim_spd_dir_z = shRcos(lim_vec_ang_y);

    over_spd = (Math_MulFixed(*vec_x, lim_spd_dir_x, FP_SIN_Q) + Math_MulFixed(*vec_z, lim_spd_dir_z, FP_SIN_Q)) - lim_vec_len;
    if (over_spd > 0)
    {
        *vec_x -= Math_MulFixed(over_spd, lim_spd_dir_x, FP_SIN_Q);
        *vec_z -= Math_MulFixed(over_spd, lim_spd_dir_z, FP_SIN_Q);
    }
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/view/vw_calc", vwDecreaseSideOfVector);

INCLUDE_ASM("asm/bodyprog/nonmatchings/view/vw_calc", vwRetNewVelocityToTargetVal);

s32 vwRetNewAngSpdToTargetAng(s32 now_ang_spd, s16 now_ang, s16 tgt_ang, s32 accel_spd, s32 total_max_ang_spd, s32 dec_val_lim_spd) // 0x80049464
{
    return vwRetNewVelocityToTargetVal(now_ang_spd, 0, ((tgt_ang - now_ang) << 0x14) >> 0x14, accel_spd, total_max_ang_spd, dec_val_lim_spd);
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/view/vw_calc", func_800494B0);

INCLUDE_ASM("asm/bodyprog/nonmatchings/view/vw_calc", func_80049530);

void vwMatrixToAngleYXZ(SVECTOR* ang, MATRIX* mat) // 0x800495D4
{
    s32 r_xz = SquareRoot0((mat->m[0][2] * mat->m[0][2]) + (mat->m[2][2] * mat->m[2][2]));
    ang->vx  = ratan2(-mat->m[1][2], r_xz);

    if (ang->vx == 1024)
    {
        ang->vz = 0;
        ang->vy = ratan2(mat->m[0][1], mat->m[2][1]);
    }
    else if (ang->vx == -1024)
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

INCLUDE_ASM("asm/bodyprog/nonmatchings/view/vw_calc", func_800496AC);

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

    D_800C6FC0.m[0][0] = VbWvsMatrix.m[0][0];
    D_800C6FC0.m[0][1] = VbWvsMatrix.m[0][1];
    D_800C6FC0.m[0][2] = VbWvsMatrix.m[0][2];
    D_800C6FC0.m[1][0] = VbWvsMatrix.m[1][0];
    D_800C6FC0.m[1][1] = VbWvsMatrix.m[1][1];
    D_800C6FC0.m[1][2] = VbWvsMatrix.m[1][2];
    D_800C6FC0.m[2][0] = VbWvsMatrix.m[2][0];
    D_800C6FC0.m[2][1] = VbWvsMatrix.m[2][1];
    D_800C6FC0.m[2][2] = VbWvsMatrix.m[2][2];

    sp30.vx = -D_800C3868.t[0];
    sp30.vy = -D_800C3868.t[1];
    sp30.vz = -D_800C3868.t[2];
    ApplyMatrixLV(&VbWvsMatrix, &sp30, (VECTOR*)&D_800C6FC0.t);
}

void vbSetRefView(VbRVIEW* rview) // 0x800498D8
{
    GsCOORDINATE2 sp10;
    SVECTOR sp60;
    SVECTOR sp68;

    sp10.flg = 0;
    sp10.super = rview->super;
    sp68.vx = rview->vr.vx - rview->vp.vx;
    sp68.vy = rview->vr.vy - rview->vp.vy;
    sp68.vz = rview->vr.vz - rview->vp.vz;
    vwVectorToAngle(&sp60, &sp68);
    func_80096E78(&sp60, &sp10.coord);
    
    sp10.coord.t[0] = rview->vp.vx;
    sp10.coord.t[1] = rview->vp.vy;
    sp10.coord.t[2] = rview->vp.vz;
    vbSetWorldScreenMatrix(&sp10);
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/view/vw_calc", func_80049984);

INCLUDE_ASM("asm/bodyprog/nonmatchings/view/vw_calc", func_80049AF8);

INCLUDE_ASM("asm/bodyprog/nonmatchings/view/vw_calc", func_80049B6C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/view/vw_calc", func_80049C2C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/view/vw_calc", func_80049D04);

INCLUDE_ASM("asm/bodyprog/nonmatchings/view/vw_calc", func_80049F38);

INCLUDE_ASM("asm/bodyprog/nonmatchings/view/vw_calc", func_8004A54C);

void vwAngleToVector(SVECTOR* vec, SVECTOR* ang, s32 r) // 0x8004A66C
{
    s32 entou_r = (r * shRcos(ang->vx)) >> FP_SIN_Q;
    vec->vy = (-r * shRsin(ang->vx)) >> FP_SIN_Q;
    vec->vx = (entou_r * shRsin(ang->vy)) >> FP_SIN_Q;
    vec->vz = (entou_r * shRcos(ang->vy)) >> FP_SIN_Q;
}

s32 vwVectorToAngle(SVECTOR* ang, SVECTOR* vec) // 0x8004A714
{
    VECTOR sp10;
    s32    ret_r;

    sp10.vx = vec->vx;
    sp10.vy = vec->vy;
    sp10.vz = vec->vz;
    Square0(&sp10, &sp10);
    ret_r = SquareRoot0(sp10.vx + sp10.vy + sp10.vz);

    ang->vx = ratan2(-vec->vy, SquareRoot0(sp10.vx + sp10.vz));
    ang->vy = ratan2(vec->vx, vec->vz);
    ang->vz = 0;
    return ret_r;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/view/vw_calc", vwOresenHokan);
