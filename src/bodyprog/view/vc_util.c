#include "game.h"

#include "bodyprog/vw_system.h"
#include "bodyprog/math.h"

INCLUDE_ASM("asm/bodyprog/nonmatchings/view/vc_util", vcInitCamera);

INCLUDE_ASM("asm/bodyprog/nonmatchings/view/vc_util", vcSetCameraUseWarp);

int vcRetCamMvSmoothF() // 0x80040190
{
    return vcCameraInternalInfo.mv_smooth;
}

void func_800401A0(s32 arg0) // 0x800401A0
{
    if (arg0)
    {
        vcCameraInternalInfo.ev_cam_rate = 4096;
    }
    else
    {
        vcCameraInternalInfo.ev_cam_rate = 0;
    }
}

void vcSetEvCamRate(s16 ev_cam_rate) // 0x800401C0
{
    vcCameraInternalInfo.ev_cam_rate = ev_cam_rate;
}

void func_800401CC() // 0x800401CC
{
    func_80080D68();
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/view/vc_util", vcMoveAndSetCamera);

INCLUDE_ASM("asm/bodyprog/nonmatchings/view/vc_util", vcMakeHeroHeadPos);

void vcAddOfsToPos(VECTOR3 *out_pos, VECTOR3 *in_pos, s16 ofs_xz_r, s16 ang_y,
                   s32 ofs_y) // 0x80040518
{
    out_pos->vx = in_pos->vx + ((ofs_xz_r * shRsin(ang_y)) >> 12);
    out_pos->vz = in_pos->vz + ((ofs_xz_r * shRcos(ang_y)) >> 12);
    out_pos->vy = in_pos->vy + ofs_y;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/view/vc_util", vcSetRefPosAndSysRef2CamParam);

INCLUDE_ASM("asm/bodyprog/nonmatchings/view/vc_util", vcSetRefPosAndCamPosAngByPad);
