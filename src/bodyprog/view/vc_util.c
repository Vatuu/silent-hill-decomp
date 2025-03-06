#include "game.h"

#include "bodyprog/vw_system.h"
#include "bodyprog/math.h"

extern s32 D_800B5C34; // sensitivity multiplier?

INCLUDE_ASM("asm/bodyprog/nonmatchings/view/vc_util", vcInitCamera);

void vcSetCameraUseWarp(VECTOR3 *chr_pos, s16 chr_ang_y) // 0x800400D4
{
    VECTOR3 cam_pos;
    SVECTOR cam_ang;

    cam_ang.vx = 0;
    cam_ang.vy = chr_ang_y;
    cam_ang.vz = 0;

    cam_pos.vx = chr_pos->vx - ((shRsin(chr_ang_y) * 0x1800) >> 0xC);
    cam_pos.vy = chr_pos->vy - 0x1B33;
    cam_pos.vz = chr_pos->vz - ((shRcos(chr_ang_y) * 0x1800) >> 0xC);

    vcSetFirstCamWork(&cam_pos, chr_ang_y, g_SysWork.field_22A4 & 0x40);
    g_SysWork.field_22A4 &= ~0x40;
}

int vcRetCamMvSmoothF() // 0x80040190
{
    return vcCameraInternalInfo.mv_smooth;
}

void func_800401A0(s32 arg0) // 0x800401A0
{
    if (arg0)
        vcCameraInternalInfo.ev_cam_rate = 4096;
    else
        vcCameraInternalInfo.ev_cam_rate = 0;
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

void vcMakeHeroHeadPos(VECTOR3 *head_pos) // 0x8004047C
{
    MATRIX  neck_lwm;
    SVECTOR fpos;
    VECTOR  sp38;

    func_80049984(&g_SysWork.hero_neck_930, &neck_lwm);

    fpos.vx = 0;
    fpos.vy = -0x19;
    fpos.vz = 0;
    ApplyMatrix(&neck_lwm, &fpos, &sp38);

    head_pos->vx = (sp38.vx + neck_lwm.t[0]) * 0x10;
    head_pos->vy = ((sp38.vy + neck_lwm.t[1]) * 0x10) - 0x4CC;
    head_pos->vz = (sp38.vz + neck_lwm.t[2]) * 0x10;
}

void vcAddOfsToPos(VECTOR3 *out_pos, VECTOR3 *in_pos, s16 ofs_xz_r, s16 ang_y,
                   s32 ofs_y) // 0x80040518
{
    out_pos->vx = in_pos->vx + ((ofs_xz_r * shRsin(ang_y)) >> 12);
    out_pos->vz = in_pos->vz + ((ofs_xz_r * shRcos(ang_y)) >> 12);
    out_pos->vy = in_pos->vy + ofs_y;
}

void vcSetRefPosAndSysRef2CamParam(VECTOR3 *ref_pos, s_SysWork *sys_p,
                                   s32 for_f, s32 back_f, s32 right_f,
                                   s32 left_f, s32 up_f,
                                   s32 down_f) // 0x800405C4
{
    if (for_f != 0)
        sys_p->cam_r_xz_2380 -= 0x199;

    if (back_f != 0)
        sys_p->cam_r_xz_2380 += 0x199;

    if (right_f != 0)
        sys_p->cam_ang_y_237A = sys_p->cam_ang_y_237A - (D_800B5C34 * 0xB);

    if (left_f != 0)
        sys_p->cam_ang_y_237A = sys_p->cam_ang_y_237A + (D_800B5C34 * 0xB);

    if (up_f != 0)
        sys_p->cam_y_2384 -= 0x199;

    if (down_f != 0)
        sys_p->cam_y_2384 += 0x199;

    if (sys_p->cam_r_xz_2380 < 0x1000)
        sys_p->cam_r_xz_2380 = 0x1000;

    vcAddOfsToPos(ref_pos, &g_SysWork.player_4C.c.position_18, 0x800,
                  g_SysWork.player_4C.c.rotation_24.vy, -0x1000);
}

void vcSetRefPosAndCamPosAngByPad(VECTOR3   *ref_pos,
                                  s_SysWork *sys_p) // 0x800406D4
{
    SVECTOR cam_ang;
    VECTOR3 sp18;
    VECTOR3 cam_pos;
    MATRIX  sp38;
    s32     var_s0;
    s32     var_v1;
    s32     var_v1_4;

    vwGetViewPosition(&cam_pos);

    sp18.vx = (cam_pos.vx >> 4);
    sp18.vy = (cam_pos.vy >> 4);
    sp18.vz = (cam_pos.vz >> 4);

    vwGetViewAngle(&cam_ang);

    if (!(g_pController2->btns_held_C & Pad_BtnCircle))
    {
        if (g_pController2->btns_held_C & Pad_LSDown)
            cam_ang.vx = cam_ang.vx - (D_800B5C34 * 0xB);
        if (g_pController2->btns_held_C & Pad_LSUp)
            cam_ang.vx = cam_ang.vx + (D_800B5C34 * 0xB);
        if (g_pController2->btns_held_C & Pad_LSRight)
            cam_ang.vy = cam_ang.vy + (D_800B5C34 * 0xB);
        if (g_pController2->btns_held_C & Pad_LSLeft)
            cam_ang.vy = cam_ang.vy - (D_800B5C34 * 0xB);

        if (g_pController2->btns_held_C & (Pad_BtnTriangle | Pad_BtnCross))
        {
            var_s0 = 0;
            if (g_pController2->btns_held_C & Pad_BtnTriangle)
                var_s0 = 0x19;
            if (g_pController2->btns_held_C & Pad_BtnCross)
                var_s0 = -0x1A;

            var_v1 = var_s0 * shRsin(cam_ang.vy);
            if (var_v1 < 0)
                var_v1 += 0xFFF;

            sp18.vx += var_v1 >> 0xC;
            var_v1_4 = var_s0 * shRcos(cam_ang.vy);
            if (var_v1_4 < 0)
                var_v1_4 += 0xFFF;

            sp18.vz += var_v1_4 >> 0xC;
        }
    }
    else
    {
        if (g_pController2->btns_held_C & Pad_LSUp)
            sp18.vy -= 0x19;
        if (g_pController2->btns_held_C & Pad_LSDown)
            sp18.vy += 0x19;

        if (g_pController2->btns_held_C & (Pad_LSRight | Pad_LSLeft))
        {
            var_s0 = 0;
            if (g_pController2->btns_held_C & Pad_LSRight)
                var_s0 = 0x19;
            if (g_pController2->btns_held_C & Pad_LSLeft)
                var_s0 = -0x1A;

            var_v1 = var_s0 * shRsin(cam_ang.vy + 1024);
            if (var_v1 < 0)
            {
                var_v1 += 0xFFF;
            }

            sp18.vx += var_v1 >> 0xC;
            var_v1_4 = var_s0 * shRcos(cam_ang.vy + 1024);
            if (var_v1_4 < 0)
            {
                var_v1_4 += 0xFFF;
            }
            sp18.vz += var_v1_4 >> 0xC;
        }
    }

    func_80096E78(&cam_ang, &sp38);

    sp38.t[0] = sp18.vx;
    sp38.t[1] = sp18.vy;
    sp38.t[2] = sp18.vz;
    vwSetViewInfoDirectMatrix(NULL, &sp38);

    if (g_pController2->btns_held_C & 0x0F005000)
    {
        SVECTOR sp58;
        vwAngleToVector(&sp58, &cam_ang, 0x500);
        ref_pos->vx           = (sp18.vx + sp58.vx) * 0x10;
        ref_pos->vy           = (sp18.vy + sp58.vy) * 0x10;
        ref_pos->vz           = (sp18.vz + sp58.vz) * 0x10;
        sys_p->cam_ang_y_237A = ((cam_ang.vy + 0x800) << 0x14) >> 0x14;
        sys_p->cam_y_2384     = -sp58.vy * 0x10;
        sys_p->cam_r_xz_2380 =
            SquareRoot0((sp58.vx * sp58.vx) + (sp58.vz * sp58.vz)) * 0x10;
    }
}
