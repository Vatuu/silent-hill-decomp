#include "game.h"

#include "bodyprog/math.h"
#include "bodyprog/vw_system.h"

extern s32 D_800B5C34; // Sensitivity multiplier?

INCLUDE_ASM("asm/bodyprog/nonmatchings/view/vc_util", vcInitCamera);

void vcSetCameraUseWarp(VECTOR3* chr_pos, s16 chr_ang_y) // 0x800400D4
{
    VECTOR3 cam_pos;
    SVECTOR cam_ang;

    cam_ang.vx = 0;
    cam_ang.vy = chr_ang_y;
    cam_ang.vz = 0;

    cam_pos.vx = chr_pos->vx - MUL_FIXED(shRsin(chr_ang_y), 0x1800, Q12_SHIFT);
    cam_pos.vy = chr_pos->vy - TILE_UNIT(27.2f);
    cam_pos.vz = chr_pos->vz - MUL_FIXED(shRcos(chr_ang_y), 0x1800, Q12_SHIFT);

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
        vcCameraInternalInfo.ev_cam_rate = 4096; // TODO: If angle, replace magic value with DEG_TO_FPA(22.5f).
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

    fpos.vx = TILE_UNIT(0.0f);
    fpos.vy = TILE_UNIT(-0.1f);
    fpos.vz = TILE_UNIT(0.0f);
    ApplyMatrix(&neck_lwm, &fpos, &sp38);

    head_pos->vx = TO_FIXED(sp38.vx + neck_lwm.t[0], Q4_SHIFT);
    head_pos->vy = TO_FIXED(sp38.vy + neck_lwm.t[1], Q4_SHIFT) - TILE_UNIT(4.8f);
    head_pos->vz = TO_FIXED(sp38.vz + neck_lwm.t[2], Q4_SHIFT);
}

void vcAddOfsToPos(VECTOR3* out_pos, VECTOR3* in_pos, s16 ofs_xz_r, s16 ang_y, s32 ofs_y) // 0x80040518
{
    out_pos->vx = in_pos->vx + MUL_FIXED(ofs_xz_r, shRsin(ang_y), Q12_SHIFT);
    out_pos->vz = in_pos->vz + MUL_FIXED(ofs_xz_r, shRcos(ang_y), Q12_SHIFT);
    out_pos->vy = in_pos->vy + ofs_y;
}

void vcSetRefPosAndSysRef2CamParam(VECTOR3* ref_pos, s_SysWork* sys_p, s32 for_f, s32 back_f, s32 right_f, s32 left_f, s32 up_f, s32 down_f) // 0x800405C4
{
    if (for_f != 0)
    {
        sys_p->cam_r_xz_2380 -= TILE_UNIT(1.6f);
    }

    if (back_f != 0)
    {
        sys_p->cam_r_xz_2380 += TILE_UNIT(1.6f);
    }

    if (right_f != 0)
    {
        sys_p->cam_ang_y_237A = sys_p->cam_ang_y_237A - (D_800B5C34 * 11);
    }

    if (left_f != 0)
    {
        sys_p->cam_ang_y_237A = sys_p->cam_ang_y_237A + (D_800B5C34 * 11);
    }

    if (up_f != 0)
    {
        sys_p->cam_y_2384 -= TILE_UNIT(1.6f);
    }

    if (down_f != 0)
    {
        sys_p->cam_y_2384 += TILE_UNIT(1.6f);
    }

    if (sys_p->cam_r_xz_2380 < TILE_UNIT(16.0f))
    {
        sys_p->cam_r_xz_2380 = TILE_UNIT(16.0f);
    }

    vcAddOfsToPos(ref_pos, &g_SysWork.characters_4C.position_18, TILE_UNIT(8.0f), g_SysWork.characters_4C.rotation_24.vy, TILE_UNIT(-16.0f));
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

    sp18.vx = FROM_FIXED(cam_pos.vx, Q4_SHIFT);
    sp18.vy = FROM_FIXED(cam_pos.vy, Q4_SHIFT);
    sp18.vz = FROM_FIXED(cam_pos.vz, Q4_SHIFT);

    vwGetViewAngle(&cam_ang);

    if (!(g_ControllerPtr1->btns_held_C & Pad_BtnCircle))
    {
        if (g_ControllerPtr1->btns_held_C & Pad_LSDown)
        {
            cam_ang.vx = cam_ang.vx - (D_800B5C34 * 11);
        }

        if (g_ControllerPtr1->btns_held_C & Pad_LSUp)
        {
            cam_ang.vx = cam_ang.vx + (D_800B5C34 * 11);
        }

        if (g_ControllerPtr1->btns_held_C & Pad_LSRight)
        {
            cam_ang.vy = cam_ang.vy + (D_800B5C34 * 11);
        }

        if (g_ControllerPtr1->btns_held_C & Pad_LSLeft)
        {
            cam_ang.vy = cam_ang.vy - (D_800B5C34 * 11);
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

            sp18.vx += FROM_FIXED(var_v1, Q12_SHIFT);
            var_v1_4 = var_s0 * shRcos(cam_ang.vy);
            if (var_v1_4 < 0)
            {
                var_v1_4 += 0xFFF;
            }

            sp18.vz += FROM_FIXED(var_v1_4, Q12_SHIFT);
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

            var_v1 = var_s0 * shRsin(cam_ang.vy + DEG_TO_FPA(5.625f));
            if (var_v1 < 0)
            {
                var_v1 += 0xFFF;
            }

            sp18.vx += FROM_FIXED(var_v1, Q12_SHIFT);

            var_v1_4 = var_s0 * shRcos(cam_ang.vy + DEG_TO_FPA(5.625f));
            if (var_v1_4 < 0)
            {
                var_v1_4 += 0xFFF;
            }
            sp18.vz += FROM_FIXED(var_v1_4, Q12_SHIFT);
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

        vwAngleToVector(&sp58, &cam_ang, TILE_UNIT(5.0f));

        ref_pos->vx = TO_FIXED(sp18.vx + sp58.vx, Q4_SHIFT);
        ref_pos->vy = TO_FIXED(sp18.vy + sp58.vy, Q4_SHIFT);
        ref_pos->vz = TO_FIXED(sp18.vz + sp58.vz, Q4_SHIFT);

        sys_p->cam_ang_y_237A = ((cam_ang.vy + DEG_TO_FPA(11.25f)) << 0x14) >> 0x14;
        sys_p->cam_y_2384     = TO_FIXED(-sp58.vy, Q4_SHIFT);
        sys_p->cam_r_xz_2380  = TO_FIXED(SquareRoot0((sp58.vx * sp58.vx) + (sp58.vz * sp58.vz)), Q4_SHIFT);
    }
}
