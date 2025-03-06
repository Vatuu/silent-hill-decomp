#include "game.h"

#include "bodyprog/vw_system.h"
#include "bodyprog/math.h"

INCLUDE_ASM("asm/bodyprog/nonmatchings/view/vw_calc", vwRenewalXZVelocityToTargetPos);

INCLUDE_ASM("asm/bodyprog/nonmatchings/view/vw_calc", vwLimitOverLimVector);

INCLUDE_ASM("asm/bodyprog/nonmatchings/view/vw_calc", vwDecreaseSideOfVector);

INCLUDE_ASM("asm/bodyprog/nonmatchings/view/vw_calc", vwRetNewVelocityToTargetVal);

s32 vwRetNewAngSpdToTargetAng(s32 now_ang_spd, s16 now_ang, s16 tgt_ang,
                              s32 accel_spd, s32 total_max_ang_spd,
                              s32 dec_val_lim_spd) // 0x80049464
{
    return vwRetNewVelocityToTargetVal(now_ang_spd, 0, ((tgt_ang - now_ang) << 0x14) >> 0x14, accel_spd, total_max_ang_spd, dec_val_lim_spd);
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/view/vw_calc", func_800494B0);

INCLUDE_ASM("asm/bodyprog/nonmatchings/view/vw_calc", func_80049530);

INCLUDE_ASM("asm/bodyprog/nonmatchings/view/vw_calc", vwMatrixToAngleYXZ);

INCLUDE_ASM("asm/bodyprog/nonmatchings/view/vw_calc", func_800496AC);

INCLUDE_ASM("asm/bodyprog/nonmatchings/view/vw_calc", vbSetWorldScreenMatrix);

void vbSetRefView(VbRVIEW *rview) // 0x800498D8
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

void vwAngleToVector(SVECTOR *vec, SVECTOR *ang, s32 r) // 0x8004A66C
{
    s32 entou_r = (r * shRcos(ang->vx)) >> 12;
    vec->vy = (-r * shRsin(ang->vx)) >> 12;
    vec->vx = (entou_r * shRsin(ang->vy)) >> 12;
    vec->vz = (entou_r * shRcos(ang->vy)) >> 12;
}

s32 vwVectorToAngle(SVECTOR *ang, SVECTOR *vec) // 0x8004A714
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
