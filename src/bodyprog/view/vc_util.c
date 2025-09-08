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

    g_SysWork.cameraAngleZ_237C   = FP_ANGLE(0.0f);
    g_SysWork.cameraRadiusXz_2380 = FP_METER(3.0f);
    g_SysWork.cameraY_2384        = FP_METER(0.0f);
}

void vcSetCameraUseWarp(const VECTOR3* chr_pos, s16 chr_ang_y) // 0x800400D4
{
    VECTOR3 cam_pos;
    SVECTOR cam_ang;

    cam_ang.vx = FP_ANGLE(0.0f);
    cam_ang.vy = chr_ang_y;
    cam_ang.vz = FP_ANGLE(0.0f);

    cam_pos.vx = chr_pos->vx - FP_MULTIPLY_FLOAT(Math_Sin(chr_ang_y), 1.5f, Q12_SHIFT);
    cam_pos.vy = chr_pos->vy - FP_METER(1.7f);
    cam_pos.vz = chr_pos->vz - FP_MULTIPLY_FLOAT(Math_Cos(chr_ang_y), 1.5f, Q12_SHIFT);

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
        D_800BCE18.vcCameraInternalInfo_1BDC.ev_cam_rate = FP_METER(1.0f);
    }
    else
    {
        D_800BCE18.vcCameraInternalInfo_1BDC.ev_cam_rate = FP_METER(0.0f);
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

            first_cam_pos.vy = FP_METER(-2.2f);
            first_cam_pos.vx = g_SysWork.player_4C.chara_0.position_18.vx + FP_METER(7.0f);
            first_cam_pos.vz = g_SysWork.player_4C.chara_0.position_18.vz;

            vcSetFirstCamWork(&first_cam_pos, g_SysWork.player_4C.chara_0.rotation_24.vy, 0);

        case 0:
            hr_p = &g_SysWork.player_4C.chara_0;

            if (in_connect_f != 0)
            {
                grnd_y = FP_METER(-2.0f);

                hr_head_pos.vx = hr_p->position_18.vx;
                hr_head_pos.vy = hr_p->position_18.vy - FP_METER(1.9f);
                hr_head_pos.vz = hr_p->position_18.vz;
            }
            else
            {
                func_800699F8(&sp50, hr_p->position_18.vx, hr_p->position_18.vz);
                grnd_y = sp50.groundHeight_0;

                vcMakeHeroHeadPos(&hr_head_pos);
            }

            hero_top_y = hr_p->position_18.vy - FP_METER(1.7f);

            // TODO: Not sure what this is doing, maybe some kind of `FP_MULTIPLY`.
            hero_bottom_y = hr_p->position_18.vy + ((s32)-(D_800BCE18.vcCameraInternalInfo_1BDC.ev_cam_rate * FP_METER(0.5f)) >> Q12_SHIFT);

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
                           FP_ANGLE(120.0f), FP_METER(11.0f));

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
            vwSetCoordRefAndEntou(&g_SysWork.playerBoneCoords_890[HarryBone_Head],
                                  FP_METER(0.0f), FP_METER(-0.15f), FP_METER(1.0f),
                                  FP_ANGLE(165.0f), FP_ANGLE(0.0f), FP_METER(-0.2f), FP_METER(1.0f));
            break;
    }

    vwSetViewInfo();
}

void vcMakeHeroHeadPos(VECTOR3* head_pos) // 0x8004047C
{
    MATRIX  neck_lwm; // Q23.8
    SVECTOR fpos;     // Q23.8
    VECTOR  vec;

    Vw_CoordHierarchyMatrixCompute(&g_SysWork.playerBoneCoords_890[HarryBone_Head], &neck_lwm);

    fpos.vx = FP_METER_GEO(0.0f);
    fpos.vy = FP_METER_GEO(-0.1f);
    fpos.vz = FP_METER_GEO(0.0f);
    ApplyMatrix(&neck_lwm, &fpos, &vec);

    head_pos->vx = FP_METER_FROM_GEO(vec.vx + neck_lwm.t[0]);
    head_pos->vy = FP_METER_FROM_GEO(vec.vy + neck_lwm.t[1]) - FP_METER(0.3f);
    head_pos->vz = FP_METER_FROM_GEO(vec.vz + neck_lwm.t[2]);
}

void vcAddOfsToPos(VECTOR3* out_pos, const VECTOR3* in_pos, s16 ofs_xz_r, s16 ang_y, s32 ofs_y) // 0x80040518
{
    out_pos->vx = in_pos->vx + FP_MULTIPLY(ofs_xz_r, Math_Sin(ang_y), Q12_SHIFT);
    out_pos->vz = in_pos->vz + FP_MULTIPLY(ofs_xz_r, Math_Cos(ang_y), Q12_SHIFT);
    out_pos->vy = in_pos->vy + ofs_y;
}

void vcSetRefPosAndSysRef2CamParam(VECTOR3* ref_pos, s_SysWork* sys_p, s32 for_f, s32 back_f, s32 right_f, s32 left_f, s32 up_f, s32 down_f) // 0x800405C4
{
    if (for_f != 0)
    {
        sys_p->cameraRadiusXz_2380 -= FP_METER(0.1f);
    }

    if (back_f != 0)
    {
        sys_p->cameraRadiusXz_2380 += FP_METER(0.1f);
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
        sys_p->cameraY_2384 -= FP_METER(0.1f);
    }

    if (down_f != 0)
    {
        sys_p->cameraY_2384 += FP_METER(0.1f);
    }

    if (sys_p->cameraRadiusXz_2380 < FP_METER(1.0f))
    {
        sys_p->cameraRadiusXz_2380 = FP_METER(1.0f);
    }

    vcAddOfsToPos(ref_pos, &g_SysWork.player_4C.chara_0.position_18, FP_METER(0.5f), g_SysWork.player_4C.chara_0.rotation_24.vy, FP_METER(-1.0f));
}

void vcSetRefPosAndCamPosAngByPad(VECTOR3* ref_pos, s_SysWork* sys_p) // 0x800406D4
{
    SVECTOR cam_ang; // Q3.12
    VECTOR3 vec0;    // Q23.8
    VECTOR3 cam_pos; // Q19.12
    MATRIX  mat;
    s32     var0;
    s32     var1;
    s32     var2;

    vwGetViewPosition(&cam_pos);

    vec0.vx = FP_METER_TO_GEO(cam_pos.vx);
    vec0.vy = FP_METER_TO_GEO(cam_pos.vy);
    vec0.vz = FP_METER_TO_GEO(cam_pos.vz);

    vwGetViewAngle(&cam_ang);

    // TODO: Demagic hex values. What Q format is being used?
    if (!(g_Controller1->btnsHeld_C & ControllerFlag_Circle))
    {
        if (g_Controller1->btnsHeld_C & ControllerFlag_LStickDown)
        {
            cam_ang.vx = cam_ang.vx - (g_VBlanks * 11);
        }

        if (g_Controller1->btnsHeld_C & ControllerFlag_LStickUp)
        {
            cam_ang.vx = cam_ang.vx + (g_VBlanks * 11);
        }

        if (g_Controller1->btnsHeld_C & ControllerFlag_LStickRight)
        {
            cam_ang.vy = cam_ang.vy + (g_VBlanks * 11);
        }

        if (g_Controller1->btnsHeld_C & ControllerFlag_LStickLeft)
        {
            cam_ang.vy = cam_ang.vy - (g_VBlanks * 11);
        }

        if (g_Controller1->btnsHeld_C & (ControllerFlag_Triangle | ControllerFlag_Cross))
        {
            var0 = 0;
            if (g_Controller1->btnsHeld_C & ControllerFlag_Triangle)
            {
                var0 = 0x19;
            }
            if (g_Controller1->btnsHeld_C & ControllerFlag_Cross)
            {
                var0 = -0x1A;
            }

            var1 = var0 * Math_Sin(cam_ang.vy);
            if (var1 < 0)
            {
                var1 += 0xFFF;
            }

            vec0.vx += FP_FROM(var1, Q12_SHIFT);
            var2 = var0 * Math_Cos(cam_ang.vy);
            if (var2 < 0)
            {
                var2 += 0xFFF;
            }

            vec0.vz += FP_FROM(var2, Q12_SHIFT);
        }
    }
    else
    {
        if (g_Controller1->btnsHeld_C & ControllerFlag_LStickUp)
        {
            vec0.vy -= FP_METER_GEO(0.1f);
        }
        if (g_Controller1->btnsHeld_C & ControllerFlag_LStickDown)
        {
            vec0.vy += FP_METER_GEO(0.1f);
        }

        if (g_Controller1->btnsHeld_C & (ControllerFlag_LStickRight | ControllerFlag_LStickLeft))
        {
            var0 = 0;
            if (g_Controller1->btnsHeld_C & ControllerFlag_LStickRight)
            {
                var0 = 0x19;
            }
            if (g_Controller1->btnsHeld_C & ControllerFlag_LStickLeft)
            {
                var0 = -0x1A;
            }

            var1 = var0 * Math_Sin(cam_ang.vy + FP_ANGLE(90.0f));
            if (var1 < 0)
            {
                var1 += 0xFFF;
            }

            vec0.vx += FP_FROM(var1, Q12_SHIFT);

            var2 = var0 * Math_Cos(cam_ang.vy + FP_ANGLE(90.0f));
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

    if (g_Controller1->btnsHeld_C & (ControllerFlag_LStickUp |
                                     ControllerFlag_LStickRight |
                                     ControllerFlag_LStickDown |
                                     ControllerFlag_LStickLeft |
                                     ControllerFlag_Cross |
                                     ControllerFlag_Triangle))
    {
        SVECTOR vec1;

        // TODO: `FP_METER_GEO(5.0f)`? But `vwAngleToVector` expects `FP_METER`. Maybe an error by TS.
        vwAngleToVector(&vec1, &cam_ang, FP_METER(0.3125f));

        ref_pos->vx = FP_METER_FROM_GEO(vec0.vx + vec1.vx);
        ref_pos->vy = FP_METER_FROM_GEO(vec0.vy + vec1.vy);
        ref_pos->vz = FP_METER_FROM_GEO(vec0.vz + vec1.vz);

        sys_p->cameraAngleY_237A   = Math_AngleNormalize(cam_ang.vy + FP_ANGLE(180.0f));
        sys_p->cameraY_2384        = FP_METER_FROM_GEO(-vec1.vy);
        sys_p->cameraRadiusXz_2380 = FP_METER_FROM_GEO(SquareRoot0(SQUARE(vec1.vx) + SQUARE(vec1.vz)));
    }
}
