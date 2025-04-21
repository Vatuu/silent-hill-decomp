#include "game.h"

#include "bodyprog/bodyprog.h"
#include "bodyprog/math.h"

extern s32 g_VBlanks;

void vcInitCamera(struct _MapOverlayHeader* map_overlay_ptr, VECTOR3* chr_pos)
{
    D_800BCE18.vcCameraInternalInfo_1BDC.mv_smooth   = 0;
    D_800BCE18.vcCameraInternalInfo_1BDC.ev_cam_rate = 0;
    D_800BCE18.vcCameraInternalInfo_1BDC.mode        = 0;

    vcSetCameraUseWarp(chr_pos, g_SysWork.cameraAngleY_237A);
    SetGeomScreen(g_GameWork.gsScreenHeight_58A);
    vwInitViewInfo();
    vcInitVCSystem(map_overlay_ptr->roadDataList_3CC);
    vcStartCameraSystem();

    g_SysWork.cameraAngleZ_237C   = 0;
    g_SysWork.cameraRadiusXz_2380 = FP_METER(48.0f);
    g_SysWork.cameraY_2384        = 0;
}

void vcSetCameraUseWarp(VECTOR3* chr_pos, s16 chr_ang_y) // 0x800400D4
{
    VECTOR3 cam_pos;
    SVECTOR cam_ang;

    cam_ang.vx = 0;
    cam_ang.vy = chr_ang_y;
    cam_ang.vz = 0;

    cam_pos.vx = chr_pos->vx - FP_MULTIPLY_FLOAT(shRsin(chr_ang_y), 1.5f, Q12_SHIFT);
    cam_pos.vy = chr_pos->vy - FP_METER(27.2f);
    cam_pos.vz = chr_pos->vz - FP_MULTIPLY_FLOAT(shRcos(chr_ang_y), 1.5f, Q12_SHIFT);

    vcSetFirstCamWork(&cam_pos, chr_ang_y, g_SysWork.flags_22A4 & (1 << 6));
    g_SysWork.flags_22A4 &= ~(1 << 6);
}

int vcRetCamMvSmoothF() // 0x80040190
{
    return D_800BCE18.vcCameraInternalInfo_1BDC.mv_smooth;
}

void func_800401A0(s32 arg0) // 0x800401A0
{
    if (arg0)
    {
        D_800BCE18.vcCameraInternalInfo_1BDC.ev_cam_rate = FP_METER(16.0f);
    }
    else
    {
        D_800BCE18.vcCameraInternalInfo_1BDC.ev_cam_rate = 0;
    }
}

void vcSetEvCamRate(s16 ev_cam_rate) // 0x800401C0
{
    D_800BCE18.vcCameraInternalInfo_1BDC.ev_cam_rate = ev_cam_rate;
}

void func_800401CC() // 0x800401CC
{
    func_80080D68();
}

void vcMoveAndSetCamera(s32 in_connect_f, s32 change_debug_mode, s32 for_f, s32 back_f, s32 right_f, s32 left_f, s32 up_f, s32 down_f) // 0x800401EC
{
    VECTOR3         first_cam_pos;
    VECTOR3         hr_head_pos;
    s32             hero_bottom_y;
    s32             hero_top_y;
    s32             grnd_y;
    s_SubCharacter* hr_p;
    s_func_800699F8 sp50; // Collision-related?

    if (change_debug_mode != 0)
    {
        D_800BCE18.vcCameraInternalInfo_1BDC.mode++;
    }

    switch (D_800BCE18.vcCameraInternalInfo_1BDC.mode)
    {
        default:
            D_800BCE18.vcCameraInternalInfo_1BDC.mode = 0;

            first_cam_pos.vy = FP_METER(-35.2f);
            first_cam_pos.vx = g_SysWork.player_4C.chara_0.position_18.vx + FP_METER(112.f);
            first_cam_pos.vz = g_SysWork.player_4C.chara_0.position_18.vz;

            vcSetFirstCamWork(&first_cam_pos, g_SysWork.player_4C.chara_0.rotation_24.vy, 0);

        case 0:
            hr_p = &g_SysWork.player_4C.chara_0;

            if (in_connect_f != 0)
            {
                grnd_y = FP_METER(-32.0f);

                hr_head_pos.vx = hr_p->position_18.vx;
                hr_head_pos.vy = hr_p->position_18.vy - FP_METER(30.4f);
                hr_head_pos.vz = hr_p->position_18.vz;
            }
            else
            {
                func_800699F8(&sp50, hr_p->position_18.vx, hr_p->position_18.vz);
                grnd_y = sp50.chara_grnd_0;

                vcMakeHeroHeadPos(&hr_head_pos);
            }

            hero_top_y = hr_p->position_18.vy - FP_METER(27.2f);

            // TODO: Not sure what this is doing, maybe some kind of `FP_MULTIPLY`.
            hero_bottom_y = hr_p->position_18.vy + ((s32)-(D_800BCE18.vcCameraInternalInfo_1BDC.ev_cam_rate * FP_METER(8.0f)) >> Q12_SHIFT);

            if (D_800BCE18.vcCameraInternalInfo_1BDC.ev_cam_rate > 0)
            {
                vcWorkSetFlags(VC_INHIBIT_FAR_WATCH_F, 0);
            }
            else
            {
                vcWorkSetFlags(0, VC_INHIBIT_FAR_WATCH_F);
            }

            vcSetSubjChara(&hr_p->position_18, hero_bottom_y, hero_top_y, grnd_y,
                           &hr_head_pos, hr_p->moveSpeed_38, hr_p->headingAngle_3C, hr_p->rotationSpeed_2C.vy, hr_p->rotation_24.vy,
                           FP_ANGLE(7.5f), FP_METER(176.0f));

            D_800BCE18.vcCameraInternalInfo_1BDC.mv_smooth = vcExecCamera();
            break;

        case 1:
            vcSetRefPosAndSysRef2CamParam(&vcRefPosSt, &g_SysWork, for_f, back_f, right_f, left_f, up_f, down_f);
            vwSetCoordRefAndEntou(NULL,
                                  vcRefPosSt.vx, vcRefPosSt.vy, vcRefPosSt.vz,
                                  g_SysWork.cameraAngleY_237A, g_SysWork.cameraAngleZ_237C, g_SysWork.cameraY_2384, g_SysWork.cameraRadiusXz_2380);
            break;

        case 2:
            vcSetRefPosAndCamPosAngByPad(&vcRefPosSt, &g_SysWork);
            break;

        case 3:
            vcSetRefPosAndSysRef2CamParam(&vcRefPosSt, &g_SysWork, for_f, back_f, right_f, left_f, up_f, down_f);
            vwSetCoordRefAndEntou(&g_SysWork.playerBoneCoords_890[PlayerBone_Head],
                                  FP_METER(0.0f), FP_METER(-2.4f), FP_METER(16.0f),
                                  FP_ANGLE(10.315f), FP_ANGLE(0.0f), FP_METER(-3.2f), FP_METER(16.0f));
            break;
    }

    vwSetViewInfo();
}

void vcMakeHeroHeadPos(VECTOR3* head_pos) // 0x8004047C
{
    MATRIX  neck_lwm;
    SVECTOR fpos;
    VECTOR  vec;

    func_80049984(&g_SysWork.playerBoneCoords_890[PlayerBone_Head], &neck_lwm);

    fpos.vx = FP_METER(0.0f);
    fpos.vy = FP_METER(-0.1f);
    fpos.vz = FP_METER(0.0f);
    ApplyMatrix(&neck_lwm, &fpos, &vec);

    head_pos->vx = FP_TO(vec.vx + neck_lwm.t[0], Q4_SHIFT);
    head_pos->vy = FP_TO(vec.vy + neck_lwm.t[1], Q4_SHIFT) - FP_METER(4.8f);
    head_pos->vz = FP_TO(vec.vz + neck_lwm.t[2], Q4_SHIFT);
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
        sys_p->cameraRadiusXz_2380 -= FP_METER(1.6f);
    }

    if (back_f != 0)
    {
        sys_p->cameraRadiusXz_2380 += FP_METER(1.6f);
    }

    if (right_f != 0)
    {
        sys_p->cameraAngleY_237A = sys_p->cameraAngleY_237A - (g_VBlanks * 11);
    }

    if (left_f != 0)
    {
        sys_p->cameraAngleY_237A = sys_p->cameraAngleY_237A + (g_VBlanks * 11);
    }

    if (up_f != 0)
    {
        sys_p->cameraY_2384 -= FP_METER(1.6f);
    }

    if (down_f != 0)
    {
        sys_p->cameraY_2384 += FP_METER(1.6f);
    }

    if (sys_p->cameraRadiusXz_2380 < FP_METER(16.0f))
    {
        sys_p->cameraRadiusXz_2380 = FP_METER(16.0f);
    }

    vcAddOfsToPos(ref_pos, &g_SysWork.player_4C.chara_0.position_18, FP_METER(8.0f), g_SysWork.player_4C.chara_0.rotation_24.vy, FP_METER(-16.0f));
}

void vcSetRefPosAndCamPosAngByPad(VECTOR3* ref_pos, s_SysWork* sys_p) // 0x800406D4
{
    SVECTOR cam_ang;
    VECTOR3 vec0;
    VECTOR3 cam_pos;
    MATRIX  mat;
    s32     var0;
    s32     var1;
    s32     var2;

    vwGetViewPosition(&cam_pos);

    vec0.vx = FP_FROM(cam_pos.vx, Q4_SHIFT);
    vec0.vy = FP_FROM(cam_pos.vy, Q4_SHIFT);
    vec0.vz = FP_FROM(cam_pos.vz, Q4_SHIFT);

    vwGetViewAngle(&cam_ang);

    if (!(g_ControllerPtr1->btns_held_C & Pad_Circle))
    {
        if (g_ControllerPtr1->btns_held_C & Pad_LStickDown)
        {
            cam_ang.vx = cam_ang.vx - (g_VBlanks * 11);
        }

        if (g_ControllerPtr1->btns_held_C & Pad_LStickUp)
        {
            cam_ang.vx = cam_ang.vx + (g_VBlanks * 11);
        }

        if (g_ControllerPtr1->btns_held_C & Pad_LStickRight)
        {
            cam_ang.vy = cam_ang.vy + (g_VBlanks * 11);
        }

        if (g_ControllerPtr1->btns_held_C & Pad_LStickLeft)
        {
            cam_ang.vy = cam_ang.vy - (g_VBlanks * 11);
        }

        if (g_ControllerPtr1->btns_held_C & (Pad_Triangle | Pad_Cross))
        {
            var0 = 0;
            if (g_ControllerPtr1->btns_held_C & Pad_Triangle)
            {
                var0 = 0x19;
            }
            if (g_ControllerPtr1->btns_held_C & Pad_Cross)
            {
                var0 = -0x1A;
            }

            var1 = var0 * shRsin(cam_ang.vy);
            if (var1 < 0)
            {
                var1 += 0xFFF;
            }

            vec0.vx += FP_FROM(var1, Q12_SHIFT);
            var2 = var0 * shRcos(cam_ang.vy);
            if (var2 < 0)
            {
                var2 += 0xFFF;
            }

            vec0.vz += FP_FROM(var2, Q12_SHIFT);
        }
    }
    else
    {
        // TODO: Demagic hex values.

        if (g_ControllerPtr1->btns_held_C & Pad_LStickUp)
        {
            vec0.vy -= 0x19;
        }
        if (g_ControllerPtr1->btns_held_C & Pad_LStickDown)
        {
            vec0.vy += 0x19;
        }

        if (g_ControllerPtr1->btns_held_C & (Pad_LStickRight | Pad_LStickLeft))
        {
            var0 = 0;
            if (g_ControllerPtr1->btns_held_C & Pad_LStickRight)
            {
                var0 = 0x19;
            }
            if (g_ControllerPtr1->btns_held_C & Pad_LStickLeft)
            {
                var0 = -0x1A;
            }

            var1 = var0 * shRsin(cam_ang.vy + FP_ANGLE(5.625f));
            if (var1 < 0)
            {
                var1 += 0xFFF;
            }

            vec0.vx += FP_FROM(var1, Q12_SHIFT);

            var2 = var0 * shRcos(cam_ang.vy + FP_ANGLE(5.625f));
            if (var2 < 0)
            {
                var2 += 0xFFF;
            }
            vec0.vz += FP_FROM(var2, Q12_SHIFT);
        }
    }

    func_80096E78(&cam_ang, &mat);

    mat.t[0] = vec0.vx;
    mat.t[1] = vec0.vy;
    mat.t[2] = vec0.vz;
    vwSetViewInfoDirectMatrix(NULL, &mat);

    if (g_ControllerPtr1->btns_held_C & (Pad_LStickUp | Pad_LStickRight | Pad_LStickDown | Pad_LStickLeft | Pad_Cross | Pad_Triangle))
    {
        SVECTOR vec1;

        vwAngleToVector(&vec1, &cam_ang, FP_METER(5.0f));

        ref_pos->vx = FP_TO(vec0.vx + vec1.vx, Q4_SHIFT);
        ref_pos->vy = FP_TO(vec0.vy + vec1.vy, Q4_SHIFT);
        ref_pos->vz = FP_TO(vec0.vz + vec1.vz, Q4_SHIFT);

        sys_p->cameraAngleY_237A   = shAngleRegulate(cam_ang.vy + FP_ANGLE(11.25f));
        sys_p->cameraY_2384        = FP_TO(-vec1.vy, Q4_SHIFT);
        sys_p->cameraRadiusXz_2380 = FP_TO(SquareRoot0(SQUARE(vec1.vx) + SQUARE(vec1.vz)), Q4_SHIFT);
    }
}
