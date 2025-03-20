#include "game.h"

#include "bodyprog/math.h"
#include "bodyprog/vw_system.h"

extern s32 g_VBlanks;

INCLUDE_ASM("asm/bodyprog/nonmatchings/view/vc_util", vcInitCamera);

void vcSetCameraUseWarp(VECTOR3* chr_pos, s16 chr_ang_y) // 0x800400D4
{
    VECTOR3 cam_pos;
    SVECTOR cam_ang;

    cam_ang.vx = 0;
    cam_ang.vy = chr_ang_y;
    cam_ang.vz = 0;

    cam_pos.vx = chr_pos->vx - FP_MULTIPLY(shRsin(chr_ang_y), 0x1800, Q12_SHIFT);
    cam_pos.vy = chr_pos->vy - FP_TILE(27.2f);
    cam_pos.vz = chr_pos->vz - FP_MULTIPLY(shRcos(chr_ang_y), 0x1800, Q12_SHIFT);

    vcSetFirstCamWork(&cam_pos, chr_ang_y, g_SysWork.flags_22A4 & 0x40);
    g_SysWork.flags_22A4 &= ~0x40;
}

int vcRetCamMvSmoothF() // 0x80040190
{
    return vcCameraInternalInfo.mv_smooth;
}

void func_800401A0(s32 arg0) // 0x800401A0
{
    if (arg0)
    {
        vcCameraInternalInfo.ev_cam_rate = 4096; // TODO: If angle, replace magic value with FP_ANGLE(22.5f).
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

void vcMakeHeroHeadPos(VECTOR3* head_pos) // 0x8004047C
{
    MATRIX  neck_lwm;
    SVECTOR fpos;
    VECTOR  sp38;

    func_80049984(&g_SysWork.hero_neck_930, &neck_lwm);

    fpos.vx = FP_TILE(0.0f);
    fpos.vy = FP_TILE(-0.1f);
    fpos.vz = FP_TILE(0.0f);
    ApplyMatrix(&neck_lwm, &fpos, &sp38);

    head_pos->vx = FP_TO(sp38.vx + neck_lwm.t[0], Q4_SHIFT);
    head_pos->vy = FP_TO(sp38.vy + neck_lwm.t[1], Q4_SHIFT) - FP_TILE(4.8f);
    head_pos->vz = FP_TO(sp38.vz + neck_lwm.t[2], Q4_SHIFT);
}

void vcAddOfsToPos(VECTOR3* out_pos, VECTOR3* in_pos, s16 ofs_xz_r, s16 ang_y, s32 ofs_y) // 0x80040518
{
    out_pos->vx = in_pos->vx + FP_MULTIPLY(ofs_xz_r, shRsin(ang_y), Q12_SHIFT);
    out_pos->vz = in_pos->vz + FP_MULTIPLY(ofs_xz_r, shRcos(ang_y), Q12_SHIFT);
    out_pos->vy = in_pos->vy + ofs_y;
}

void vcSetRefPosAndSysRef2CamParam(VECTOR3* ref_pos, s_SysWork* sys_p, s32 for_f, s32 back_f, s32 right_f, s32 left_f, s32 up_f, s32 down_f) // 0x800405C4
{
    if (for_f != 0)
    {
        sys_p->cam_r_xz_2380 -= FP_TILE(1.6f);
    }

    if (back_f != 0)
    {
        sys_p->cam_r_xz_2380 += FP_TILE(1.6f);
    }

    if (right_f != 0)
    {
        sys_p->cam_ang_y_237A = sys_p->cam_ang_y_237A - (g_VBlanks * 11);
    }

    if (left_f != 0)
    {
        sys_p->cam_ang_y_237A = sys_p->cam_ang_y_237A + (g_VBlanks * 11);
    }

    if (up_f != 0)
    {
        sys_p->cam_y_2384 -= FP_TILE(1.6f);
    }

    if (down_f != 0)
    {
        sys_p->cam_y_2384 += FP_TILE(1.6f);
    }

    if (sys_p->cam_r_xz_2380 < FP_TILE(16.0f))
    {
        sys_p->cam_r_xz_2380 = FP_TILE(16.0f);
    }

    vcAddOfsToPos(ref_pos, &g_SysWork.player_4C.chara_0.position_18, FP_TILE(8.0f), g_SysWork.player_4C.chara_0.rotation_24.vy, FP_TILE(-16.0f));
}

void vcSetRefPosAndCamPosAngByPad(VECTOR3* ref_pos, s_SysWork* sys_p) // 0x800406D4
{
    SVECTOR cam_ang;
    VECTOR3 sp18;
    VECTOR3 cam_pos;
    MATRIX  sp38;
    s32     var_s0;
    s32     var_v1;
    s32     var_v1_4;

    vwGetViewPosition(&cam_pos);

    sp18.vx = FP_FROM(cam_pos.vx, Q4_SHIFT);
    sp18.vy = FP_FROM(cam_pos.vy, Q4_SHIFT);
    sp18.vz = FP_FROM(cam_pos.vz, Q4_SHIFT);

    vwGetViewAngle(&cam_ang);

    if (!(g_ControllerPtr1->btns_held_C & Pad_BtnCircle))
    {
        if (g_ControllerPtr1->btns_held_C & Pad_LSDown)
        {
            cam_ang.vx = cam_ang.vx - (g_VBlanks * 11);
        }

        if (g_ControllerPtr1->btns_held_C & Pad_LSUp)
        {
            cam_ang.vx = cam_ang.vx + (g_VBlanks * 11);
        }

        if (g_ControllerPtr1->btns_held_C & Pad_LSRight)
        {
            cam_ang.vy = cam_ang.vy + (g_VBlanks * 11);
        }

        if (g_ControllerPtr1->btns_held_C & Pad_LSLeft)
        {
            cam_ang.vy = cam_ang.vy - (g_VBlanks * 11);
        }

        if (g_ControllerPtr1->btns_held_C & (Pad_BtnTriangle | Pad_BtnCross))
        {
            var_s0 = 0;
            if (g_ControllerPtr1->btns_held_C & Pad_BtnTriangle)
            {
                var_s0 = 0x19;
            }
            if (g_ControllerPtr1->btns_held_C & Pad_BtnCross)
            {
                var_s0 = -0x1A;
            }

            var_v1 = var_s0 * shRsin(cam_ang.vy);
            if (var_v1 < 0)
            {
                var_v1 += 0xFFF;
            }

            sp18.vx += FP_FROM(var_v1, Q12_SHIFT);
            var_v1_4 = var_s0 * shRcos(cam_ang.vy);
            if (var_v1_4 < 0)
            {
                var_v1_4 += 0xFFF;
            }

            sp18.vz += FP_FROM(var_v1_4, Q12_SHIFT);
        }
    }
    else
    {
        if (g_ControllerPtr1->btns_held_C & Pad_LSUp)
        {
            sp18.vy -= 0x19;
        }
        if (g_ControllerPtr1->btns_held_C & Pad_LSDown)
        {
            sp18.vy += 0x19;
        }

        if (g_ControllerPtr1->btns_held_C & (Pad_LSRight | Pad_LSLeft))
        {
            var_s0 = 0;
            if (g_ControllerPtr1->btns_held_C & Pad_LSRight)
            {
                var_s0 = 0x19;
            }
            if (g_ControllerPtr1->btns_held_C & Pad_LSLeft)
            {
                var_s0 = -0x1A;
            }

            var_v1 = var_s0 * shRsin(cam_ang.vy + FP_ANGLE(5.625f));
            if (var_v1 < 0)
            {
                var_v1 += 0xFFF;
            }

            sp18.vx += FP_FROM(var_v1, Q12_SHIFT);

            var_v1_4 = var_s0 * shRcos(cam_ang.vy + FP_ANGLE(5.625f));
            if (var_v1_4 < 0)
            {
                var_v1_4 += 0xFFF;
            }
            sp18.vz += FP_FROM(var_v1_4, Q12_SHIFT);
        }
    }

    func_80096E78(&cam_ang, &sp38);

    sp38.t[0] = sp18.vx;
    sp38.t[1] = sp18.vy;
    sp38.t[2] = sp18.vz;
    vwSetViewInfoDirectMatrix(NULL, &sp38);

    if (g_ControllerPtr1->btns_held_C & (Pad_LSUp | Pad_LSRight | Pad_LSDown | Pad_LSLeft | Pad_BtnCross | Pad_BtnTriangle))
    {
        SVECTOR sp58;

        vwAngleToVector(&sp58, &cam_ang, FP_TILE(5.0f));

        ref_pos->vx = FP_TO(sp18.vx + sp58.vx, Q4_SHIFT);
        ref_pos->vy = FP_TO(sp18.vy + sp58.vy, Q4_SHIFT);
        ref_pos->vz = FP_TO(sp18.vz + sp58.vz, Q4_SHIFT);

        sys_p->cam_ang_y_237A = ((cam_ang.vy + FP_ANGLE(11.25f)) << 0x14) >> 0x14;
        sys_p->cam_y_2384     = FP_TO(-sp58.vy, Q4_SHIFT);
        sys_p->cam_r_xz_2380  = FP_TO(SquareRoot0((sp58.vx * sp58.vx) + (sp58.vz * sp58.vz)), Q4_SHIFT);
    }
}
