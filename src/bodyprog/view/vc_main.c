#include "game.h"

#include "bodyprog/bodyprog.h"
#include "bodyprog/math.h"
#include "bodyprog/vw_system.h"

#define MIN_IN_ROAD_DIST FP_METER(1.0f) // vcGetMinInRoadDist() in SH2, hardcoded to FP_METER(1.0f) in SH1.

void vcInitVCSystem(VC_ROAD_DATA* vc_road_ary_list) // 0x80080940
{
    vcWork.view_cam_active_f_0 = 0;

    if (vc_road_ary_list == NULL)
    {
        vcWork.vc_road_ary_list_4 = vcNullRoadArray;
    }
    else
    {
        vcWork.vc_road_ary_list_4 = vc_road_ary_list;
    }

    Vc_CurNearRoadSet(&vcWork, &vcNullNearRoad);

    vcWork.old_cam_excl_area_r_6C = NO_VALUE;
    vcWork.watch_tgt_max_y_88     = FP_METER(30.0f);
    vcWork.field_D8               = 0;
    vcWork.field_FC               = 0;
}

void vcStartCameraSystem() // 0x800809DC
{
    vcWork.view_cam_active_f_0 = 1;
    vcWork.field_D8            = 0;
    vcWork.field_FC            = 0;
    vcWork.geom_screen_dist_30 = g_GameWork.gsScreenHeight_58A;
}

void vcEndCameraSystem() // 0x80080A04
{
    vcWork.view_cam_active_f_0 = 0;
}

s32 func_80080A10() // 0x80080A10
{
    return vcWork.cur_near_road_2B8.road_p_0->field_15;
}

void func_80080A30(s32 arg0) // 0x80080A30
{
    vcWork.field_2E4 = arg0;
}

s32 func_80080A3C() // 0x80080A3C
{
    return vcWork.field_2E4;
}

void vcSetFirstCamWork(VECTOR3* cam_pos, s16 chara_eye_ang_y, s32 use_through_door_cam_f) // 0x80080A4C
{
    Math_SVectorZero(&vcWork.ofs_cam_ang_spd_C0);

    vcWork.flags_8 = VC_WARP_CAM_F | VC_WARP_WATCH_F | VC_WARP_CAM_TGT_F;

    vcWork.cam_pos_50      = *cam_pos;
    vcWork.cam_mv_ang_y_5C = 0;

    Math_Vector3Zero(&vcWork.cam_velo_60);

    vcWork.cam_tgt_pos_44 = *cam_pos;

    Math_Vector3Zero(&vcWork.cam_tgt_velo_100);

    vcWork.cam_mv_ang_y_5C = 0;
    vcWork.cam_tgt_spd_110 = 0;

    vcWork.cam_chara2ideal_ang_y_FE = shAngleRegulate(chara_eye_ang_y + FP_ANGLE(180.0f));

    Vc_CurNearRoadSet(&vcWork, &vcNullNearRoad);

    vcWork.through_door_activate_init_f_C = use_through_door_cam_f;
    vcSetTHROUGH_DOOR_CAM_PARAM_in_VC_WORK(&vcWork, VC_TDSC_END);
}

void func_80080B58(GsCOORDINATE2* a1, SVECTOR* a2, VECTOR3* a3) // 0x80080B58
{
    MATRIX mat;

    vcWork.field_FC = 1;

    Vw_CoordHierarchyMatrixCompute(a1, &vcWork.field_DC);
    func_80096C94(a2, &mat);
    MulMatrix(&vcWork.field_DC, &mat);

    vcWork.field_DC.t[0] = FP_FROM(a3->vx, Q4_SHIFT);
    vcWork.field_DC.t[1] = FP_FROM(a3->vy, Q4_SHIFT);
    vcWork.field_DC.t[2] = FP_FROM(a3->vz, Q4_SHIFT);
}

void vcWorkSetFlags(VC_FLAGS enable, VC_FLAGS disable) // 0x80080BF8
{
    vcWork.flags_8 = (vcWork.flags_8 | enable) & ~disable;
}

// An accurate guess might be `vcSetWatchTgtMaxY`.
s32 Vc_LookAtAngleYMaxSet(s32 lookAtAngleYMax) // 0x80080C18
{
    s32 prevVal;
    
    prevVal                   = vcWork.watch_tgt_max_y_88;
    vcWork.watch_tgt_max_y_88 = lookAtAngleYMax;
    return prevVal;
}

void vcUserWatchTarget(VECTOR3* watch_tgt_pos, VC_WATCH_MV_PARAM* watch_prm_p, s32 warp_watch_f) // 0x80080C2C
{
    vcWork.flags_8 = (vcWork.flags_8 & ~(VC_USER_WATCH_F | VC_VISIBLE_CHARA_F)) | VC_USER_WATCH_F;

    if (warp_watch_f != 0)
    {
        vcWork.flags_8 |= VC_WARP_WATCH_F;
    }

    vcWork.watch_tgt_pos_7C   = *watch_tgt_pos;
    vcWork.watch_tgt_ang_z_8C = 0;

    if (watch_prm_p == NULL)
    {
        vcWork.user_watch_mv_prm_70 = deflt_watch_mv_prm;
    }
    else
    {
        vcWork.user_watch_mv_prm_70 = *watch_prm_p;
    }
}

void vcUserCamTarget(VECTOR3* cam_tgt_pos, VC_CAM_MV_PARAM* cam_prm_p, s32 warp_cam_f) // 0x80080CBC
{
    vcWork.flags_8 = (vcWork.flags_8 & ~(VC_USER_CAM_F | VC_WARP_CAM_F)) | VC_USER_CAM_F;

    if (warp_cam_f != 0)
    {
        vcWork.flags_8 |= VC_WARP_CAM_F;
    }

    vcWork.cam_tgt_pos_44 = *cam_tgt_pos;

    if (cam_prm_p == NULL)
    {
        vcWork.user_cam_mv_prm_34 = cam_mv_prm_user;
    }
    else
    {
        vcWork.user_cam_mv_prm_34 = *cam_prm_p;
    }
}

void vcChangeProjectionValue(s16 scr_y) // 0x80080D5C
{
    vcWork.geom_screen_dist_30 = scr_y;
}

void func_80080D68() // 0x80080D68
{
    vcWork.field_D8 = 1;
}

void vcGetNowWatchPos(VECTOR3* watch_pos) // 0x80080D78
{
    s32 sin_y;
    s32 cos_y;
    s32 cos_x;
    s32 sin_x;
    s32 r;

    cos_x = shRcos(vcWork.cam_mat_ang_8E.vx);
    sin_x = shRsin(vcWork.cam_mat_ang_8E.vx);
    cos_y = shRcos(vcWork.cam_mat_ang_8E.vy);
    sin_y = shRsin(vcWork.cam_mat_ang_8E.vy);

    r = Vc_VectorMagnitudeCalc(vcWork.cam_pos_50.vx - vcWork.watch_tgt_pos_7C.vx,
                               vcWork.cam_pos_50.vy - vcWork.watch_tgt_pos_7C.vy,
                               vcWork.cam_pos_50.vz - vcWork.watch_tgt_pos_7C.vz);

    watch_pos->vx = Math_MulFixed(Math_MulFixed(r, sin_y, Q12_SHIFT), cos_x, Q12_SHIFT) + vcWork.cam_pos_50.vx;
    watch_pos->vz = Math_MulFixed(Math_MulFixed(r, cos_y, Q12_SHIFT), cos_x, Q12_SHIFT) + vcWork.cam_pos_50.vz;
    watch_pos->vy = vcWork.cam_pos_50.vy - Math_MulFixed(r, sin_x, Q12_SHIFT);
}

void vcGetNowCamPos(VECTOR3* cam_pos) // 0x80080EA8
{
    *cam_pos = vcWork.cam_pos_50;
}

void vcReturnPreAutoCamWork(int warp_f) // 0x80080ED0
{
    if (warp_f)
    {
        vcWork.flags_8 |= VC_WARP_CAM_F | VC_WARP_WATCH_F | VC_WARP_CAM_TGT_F;
    }

    vcWork.flags_8 &= ~(VC_USER_CAM_F | VC_USER_WATCH_F);
    vcWork.geom_screen_dist_30 = g_GameWork.gsScreenHeight_58A;
}

void vcSetSubjChara(VECTOR3* chara_pos, s32 chara_bottom_y, s32 chara_top_y, s32 chara_grnd_y, VECTOR3* chara_head_pos,
                    s16 chara_mv_spd, s32 chara_mv_ang_y, s16 chara_ang_spd_y, s16 chara_eye_ang_y, s16 chara_eye_ang_wy, s32 chara_watch_xz_r) // 0x80080F14
{
    vcWork.chara_pos_114        = *chara_pos;
    vcWork.chara_bottom_y_120   = chara_bottom_y;
    vcWork.chara_top_y_124      = chara_top_y;
    vcWork.chara_center_y_128   = (chara_bottom_y + chara_top_y) >> 1;
    vcWork.chara_grnd_y_12C     = chara_grnd_y;
    vcWork.chara_head_pos_130   = *chara_head_pos;
    vcWork.chara_mv_spd_13C     = chara_mv_spd;
    vcWork.chara_eye_ang_y_144  = chara_eye_ang_y;
    vcWork.chara_mv_ang_y_140   = chara_mv_ang_y;
    vcWork.chara_ang_spd_y_142  = chara_ang_spd_y;
    vcWork.chara_eye_ang_wy_146 = chara_eye_ang_wy;
    vcWork.chara_watch_xz_r_148 = chara_watch_xz_r;
}

s32 vcExecCamera() // 0x80080FBC
{
    VECTOR3            sv_old_cam_pos;
    SVECTOR            sv_old_cam_mat_ang;
    VC_WATCH_MV_PARAM* watch_mv_prm_p;
    VC_CAM_MV_PARAM*   cam_mv_prm_p;
    VC_AREA_SIZE_TYPE  cur_rd_area_size;
    VC_CAM_MV_TYPE     cur_cam_mv_type;
    s32                self_view_eff_rate;
    s32                warp_f;
    s32                far_watch_rate;
    VC_ROAD_FLAGS      cur_rd_flags;

    sv_old_cam_pos     = vcWork.cam_pos_50;
    sv_old_cam_mat_ang = vcWork.cam_mat_ang_8E;

    if (vcWork.view_cam_active_f_0 == 0)
    {
        return 0;
    }

    vcSetAllNpcDeadTimer();
    SetGeomScreen(vcWork.geom_screen_dist_30);
    vcPreSetDataInVC_WORK(&vcWork, vcWork.vc_road_ary_list_4);

    warp_f           = vcSetCurNearRoadInVC_WORK(&vcWork);
    cur_rd_flags     = vcWork.cur_near_road_2B8.road_p_0->flags_10;
    cur_rd_area_size = vcWork.cur_near_road_2B8.road_p_0->area_size_type_11;
    cur_cam_mv_type  = vcRetCurCamMvType(&vcWork);

    // TODO: This checks for `VC_PRS_F_VIEW_F` flag in a weird way.
    far_watch_rate     = vcRetFarWatchRate(((vcWork.flags_8 >> 9) & (1 << 0)) ^ (g_GameWorkConst->config_0.optExtraViewCtrl_28 != 0), cur_cam_mv_type, &vcWork);
    self_view_eff_rate = vcRetSelfViewEffectRate(cur_cam_mv_type, far_watch_rate, &vcWork);

    if (!(vcWork.flags_8 & (VC_USER_CAM_F | VC_USER_WATCH_F)))
    {
        vcSetFlagsByCamMvType(cur_cam_mv_type, far_watch_rate, warp_f);
    }

    if (vcWork.flags_8 & VC_WARP_CAM_TGT_F)
    {
        vcWork.old_cam_excl_area_r_6C = NO_VALUE;
    }

    vcGetUseWatchAndCamMvParam(&watch_mv_prm_p, &cam_mv_prm_p, self_view_eff_rate, &vcWork);

    if (!(vcWork.flags_8 & VC_USER_CAM_F))
    {
        vcAutoRenewalCamTgtPos(&vcWork, cur_cam_mv_type, cam_mv_prm_p, (s32)cur_rd_flags, cur_rd_area_size, far_watch_rate);
    }

    vcRenewalCamData(&vcWork, cam_mv_prm_p);

    if (!(vcWork.flags_8 & VC_USER_WATCH_F))
    {
        vcAutoRenewalWatchTgtPosAndAngZ(&vcWork, cur_cam_mv_type, cur_rd_area_size, far_watch_rate, self_view_eff_rate);
        if ((vcWork.cur_near_road_2B8.road_p_0->flags_10 & VC_RD_LIM_UP_FAR_VIEW_F) &&
            (vcWork.cur_near_road_2B8.road_p_0->cam_mv_type_14 == VC_MV_CHASE || cur_cam_mv_type == VC_MV_SELF_VIEW))
        {
            vcAdjustWatchYLimitHighWhenFarView(&vcWork.watch_tgt_pos_7C, &vcWork.cam_pos_50, vcWork.geom_screen_dist_30);
        }
    }

    vcRenewalCamMatAng(&vcWork, watch_mv_prm_p, cur_cam_mv_type, vcWork.flags_8 & VC_VISIBLE_CHARA_F);
    vcSetDataToVwSystem(&vcWork, cur_cam_mv_type);

    vcWork.through_door_activate_init_f_C = 0;
    vcWork.flags_8 &= ~(VC_WARP_CAM_F | VC_WARP_WATCH_F | VC_WARP_CAM_TGT_F);

    return vcRetSmoothCamMvF(&sv_old_cam_pos, &vcWork.cam_pos_50, &sv_old_cam_mat_ang, &vcWork.cam_mat_ang_8E);
}

void vcSetAllNpcDeadTimer() // 0x8008123C
{
    #define DEAD_TIMER_MAX 10

    s_SubCharacter* chara;

    for (chara = &g_SysWork.npcs_1A0[0]; chara < &g_SysWork.npcs_1A0[NPC_COUNT_MAX]; chara++)
    {
        if (chara->model_0.charaId_0 == 0)
        {
            continue;
        }

        if (chara->health_B0 <= 0)
        {
            chara->dead_timer_C4 += g_DeltaTime0;
        }
        else
        {
            chara->dead_timer_C4 = 0;
        }

        if (chara->dead_timer_C4 > FP_TO(DEAD_TIMER_MAX, Q12_SHIFT))
        {
            chara->dead_timer_C4 = FP_TO(DEAD_TIMER_MAX, Q12_SHIFT);
        }
    }
}

s32 vcRetSmoothCamMvF(VECTOR3* old_pos, VECTOR3* now_pos, SVECTOR* old_ang, SVECTOR* now_ang) // 0x800812CC
{
    #define MOVEMENT_METER_MAX 0.0125f
    #define ROT_X_ANGLE_MAX    20.0f
    #define ROT_Y_ANGLE_MAX    30.0f
    #define INTRPT_TIME_MIN    1.0f
    #define INTRPT_TIME_MAX    4.0f

    s32 intrpt; // Interpolation time (i.e. alpha)?
    s32 mv_vec;
    s32 rot_x;
    s32 rot_y;

    intrpt = FP_TO(g_DeltaTime0, Q12_SHIFT) / FP_FLOAT_TO(1.0f / TICKS_PER_SECOND, Q12_SHIFT);
    intrpt = CLAMP(intrpt, FP_FLOAT_TO(INTRPT_TIME_MIN, Q12_SHIFT), FP_FLOAT_TO(INTRPT_TIME_MAX, Q12_SHIFT));

    mv_vec = Vc_VectorMagnitudeCalc(FP_FROM(now_pos->vx - old_pos->vx, Q4_SHIFT),
                                    FP_FROM(now_pos->vy - old_pos->vy, Q4_SHIFT),
                                    FP_FROM(now_pos->vz - old_pos->vz, Q4_SHIFT));

    mv_vec = FP_TO(mv_vec, Q12_SHIFT) / intrpt;
    if (mv_vec > FP_METER(MOVEMENT_METER_MAX))
    {
        return 0;
    }

    rot_x = FP_TO(((now_ang->vx - old_ang->vx) >= 0) ? (now_ang->vx - old_ang->vx) : (old_ang->vx - now_ang->vx), Q12_SHIFT) / intrpt;
    if (rot_x > FP_ANGLE(ROT_X_ANGLE_MAX))
    {
        return 0;
    }

    rot_y = FP_TO(abs(shAngleRegulate(now_ang->vy - old_ang->vy)), Q12_SHIFT) / intrpt;

    // This (guessed) line is needed for regalloc match, but compiler just optimizes out since rot_x isn't used afterward.
    // BUG: Maybe the shRcos call below was meant to use the result of this, but was somehow left using now_ang->vx?
    rot_x = ((now_ang->vx - old_ang->vx) >= 0) ? now_ang->vx : old_ang->vx;

    rot_y = FP_MULTIPLY(rot_y, shRcos(now_ang->vx), Q12_SHIFT);
    return rot_y <= FP_ANGLE(ROT_Y_ANGLE_MAX);
}

VC_CAM_MV_TYPE vcRetCurCamMvType(VC_WORK* w_p) // 0x80081428
{
    s32 hasViewFlag;

    if (g_GameWorkConst->config_0.optExtraViewMode_29 != 0)
    {
        hasViewFlag = (vcWork.flags_8 & VC_PRS_F_VIEW_F) == VC_PRS_F_VIEW_F;

        // TODO: Can this weird XOR be removed? (XOR 1) should be same as `hasViewFlag == 0`?
        if ((g_GameWorkConst->config_0.optExtraViewCtrl_28 && (hasViewFlag ^ 1) != 0) ||
            (!g_GameWorkConst->config_0.optExtraViewCtrl_28 && hasViewFlag))
        {
            if ((w_p->flags_8 & (VC_USER_CAM_F | VC_USER_WATCH_F | VC_INHIBIT_FAR_WATCH_F)) == 0 &&
                func_8008150C(w_p->chara_pos_114.vx, w_p->chara_pos_114.vz) == 0)
            {
                return VC_MV_SELF_VIEW;
            }
        }
    }

    if (w_p->through_door_10.active_f_0 != 0)
    {
        if (!vcRetThroughDoorCamEndF(w_p))
        {
            return VC_MV_THROUGH_DOOR;
        }

        vcSetTHROUGH_DOOR_CAM_PARAM_in_VC_WORK(w_p, VC_TDSC_END);
    }

    return w_p->cur_near_road_2B8.road_p_0->cam_mv_type_14;
}

s32 func_8008150C(s32 posX, s32 posZ)
{
    switch (func_8003BD2C())
    {
        case 0:
            if ((posX - FP_METER(201.8f)) > (u32)FP_METER(28.2002f))
            {
                return 0;
            }
            else if (posZ < FP_METER(-92.0f))
            {
                return 0;
            }
            else if (posZ <= FP_METER(-68.0f))
            {
                return 1;
            }
            break;

        case 3:
            if ((posX + FP_METER(230.0f)) > (u32)FP_METER(29.0f))
            {
                return 0;
            }
            else if (posZ < FP_METER(-12.0f))
            {
                return 0;
            }
            else if (posZ <= FP_METER(12.0f))
            {
                return 1;
            }
            break;
    }

    return 0;
}

s32 vcRetThroughDoorCamEndF(VC_WORK* w_p) // 0x800815F0
{
    VC_THROUGH_DOOR_CAM_PARAM* prm_p;
    s32                        rail2chara_dist;
    s32                        abs_ofs_ang_y;

    prm_p           = &w_p->through_door_10;
    rail2chara_dist = prm_p->rail_sta_to_chara_dist_18;

    if (!w_p->through_door_10.active_f_0)
    {
        return 1;
    }

    // TODO: Timer field treated as distance here? Maybe misnamed, need to check usages in SH2 against SH.
    if (prm_p->timer_4 > FP_METER(1.2f) && w_p->nearest_enemy_xz_dist_2E0 < FP_METER(1.2f))
    {
        return 1;
    }

    if (rail2chara_dist > FP_METER(2.3f))
    {
        return 1;
    }

    if (rail2chara_dist > FP_METER(0.5f))
    {
        abs_ofs_ang_y = shAngleRegulate(w_p->chara_eye_ang_y_144 -
                        ratan2(w_p->chara_pos_114.vx - w_p->through_door_10.rail_sta_pos_C.vx, w_p->chara_pos_114.vz - w_p->through_door_10.rail_sta_pos_C.vz));

        if (abs_ofs_ang_y < 0)
        {
            abs_ofs_ang_y = -abs_ofs_ang_y;
        }

        if (abs_ofs_ang_y > FP_ANGLE(70.0f))
        {
            return 1;
        }
    }

    return 0;
}

s32 vcRetFarWatchRate(s32 far_watch_button_prs_f, VC_CAM_MV_TYPE cur_cam_mv_type, VC_WORK* w_p) // 0x800816B0
{
    s32 dist;
    s32 far_watch_rate;
    s32 abs_ofs_ang_y;

    s32 railDistX;
    s32 railDistZ;
    s32 prsFViewFlag;

    if ((vcWork.flags_8 & (VC_USER_WATCH_F | VC_INHIBIT_FAR_WATCH_F)))
    {
        far_watch_rate = 0;
    }
    else
    {
        switch (cur_cam_mv_type)
        {
            case VC_MV_CHASE:
            case VC_MV_SETTLE:
                far_watch_rate = FP_TO(far_watch_button_prs_f != 0, Q12_SHIFT);
                break;

            case VC_MV_THROUGH_DOOR:
                far_watch_rate = FP_METER(1.0f); // FP_ANGLE(256.0f);
                if (!far_watch_button_prs_f)
                {
                    // TODO: Unsure if these should use `FP_METER` or `FP_ANGLE`.
                    // Gets multiplied by `dist`, so `FP_METER` fits,
                    // but then it gets subtracted by `abs_ofs_ang_y`, so `FP_ANGLE` would also fits?

                    dist           = w_p->through_door_10.rail_sta_to_chara_dist_18;
                    far_watch_rate = FP_METER(0.9f) - ((dist * FP_METER(0.9f)) / FP_METER(2.3f));
                    // far_watch_rate = FP_ANGLE(324.0f) - ((dist * FP_ANGLE(324.0f)) / FP_ANGLE(828.0f));
                    if (far_watch_rate < 0)
                    {
                        far_watch_rate = 0;
                    }

                    if (dist > FP_METER(0.5f))
                    {
                        railDistX = w_p->chara_pos_114.vx - w_p->through_door_10.rail_sta_pos_C.vx;
                        railDistZ = w_p->chara_pos_114.vz - w_p->through_door_10.rail_sta_pos_C.vz;
                        if (((w_p->chara_eye_ang_y_144 - ratan2(railDistX, railDistZ)) << 20) < 0)
                        {
                            abs_ofs_ang_y = -shAngleRegulate(w_p->chara_eye_ang_y_144 - ratan2(railDistX, railDistZ));
                        }
                        else
                        {
                            abs_ofs_ang_y = shAngleRegulate(w_p->chara_eye_ang_y_144 - ratan2(railDistX, railDistZ));
                        }

                        far_watch_rate = (far_watch_rate * (FP_METER(0.1945f) - abs_ofs_ang_y)) / FP_METER(0.1945f);
                        // far_watch_rate = (far_watch_rate * (FP_ANGLE(70.0f) - abs_ofs_ang_y)) / FP_ANGLE(70.0f);
                        if (far_watch_rate < 0)
                        {
                            far_watch_rate = 0;
                        }
                    }
                }
                break;

            default:
            case VC_MV_FIX_ANG:
            case VC_MV_SELF_VIEW:
                far_watch_rate = 0;
                break;
        }
    }

    if (g_GameWorkConst->config_0.optExtraViewMode_29 != 0)
    {
        prsFViewFlag = vcWork.flags_8 >> 9; /** `VC_PRS_F_VIEW_F` */
        prsFViewFlag = prsFViewFlag & (1 << 0);

        if ((g_GameWorkConst->config_0.optExtraViewCtrl_28 != 0 && (prsFViewFlag ^ 1) != 0) ||
            (g_GameWorkConst->config_0.optExtraViewCtrl_28 == 0 && prsFViewFlag != 0))
        {
            if (!(w_p->flags_8 & (VC_USER_CAM_F | VC_USER_WATCH_F | VC_INHIBIT_FAR_WATCH_F)) &&
                func_8008150C(w_p->chara_pos_114.vx, w_p->chara_pos_114.vz))
            {
                far_watch_rate = 0;
            }
        }
    }

    return far_watch_rate;
}

s32 vcRetSelfViewEffectRate(VC_CAM_MV_TYPE cur_cam_mv_type, s32 far_watch_rate, VC_WORK* w_p) // 0x800818D4
{
    s32 xyz_dist;
    s32 max_rate;
    s32 cam_max_rate;
    s32 mul_rate;
    s32 ret_eff_rate;

    if (cur_cam_mv_type > VC_MV_THROUGH_DOOR)
    {
        return 0;
    }

    if (cur_cam_mv_type < VC_MV_SELF_VIEW)
    {
        return 0;
    }

    cam_max_rate = (cur_cam_mv_type == VC_MV_SELF_VIEW) ? FP_METER(1.0f) : FP_METER(0.35f);

    xyz_dist = Vc_VectorMagnitudeCalc(FP_FROM(w_p->cam_pos_50.vx - w_p->chara_head_pos_130.vx, Q4_SHIFT),
                                      FP_FROM(w_p->cam_pos_50.vy - w_p->chara_head_pos_130.vy, Q4_SHIFT),
                                      FP_FROM(w_p->cam_pos_50.vz - w_p->chara_head_pos_130.vz, Q4_SHIFT));

    if (xyz_dist >= FP_METER(0.03125f))
    {
        if (xyz_dist > FP_METER(0.075f))
        {
            max_rate = 0;
        }
        else
        {
            max_rate = (cam_max_rate * (FP_METER(0.075f) - xyz_dist)) / FP_METER(0.04375f);
        }
    }
    else
    {
        max_rate = cam_max_rate;
    }

    if (w_p->nearest_enemy_xz_dist_2E0 > FP_METER(4.0f))
    {
        mul_rate = FP_METER(1.0f);
    }
    else
    {
        if (w_p->nearest_enemy_xz_dist_2E0 < FP_METER(2.0f))
        {
            mul_rate = 0;
        }
        else
        {
            mul_rate = (w_p->nearest_enemy_xz_dist_2E0 - FP_METER(2.0f)) / 2;
        }
    }

    max_rate = FP_MULTIPLY(max_rate, mul_rate, Q12_SHIFT);

    ret_eff_rate = cam_max_rate;

    if (max_rate >= 0)
    {
        if (max_rate <= ret_eff_rate)
        {
            ret_eff_rate = max_rate;
        }
    }
    else
    {
        ret_eff_rate = 0;
    }

    return ret_eff_rate;
}

void vcSetFlagsByCamMvType(VC_CAM_MV_TYPE cam_mv_type, s32 far_watch_rate, s32 all_warp_f) // 0x80081A0C
{
    s32 vcOldPrsFViewFlag;
    s32 vcPrsFViewFlag;

    if (!far_watch_rate)
    {
        switch (cam_mv_type)
        {
            case VC_MV_CHASE:
                Vc_FlagSet(VC_VISIBLE_CHARA_F);
                break;

            case VC_MV_SETTLE:
                Vc_FlagSet(VC_VISIBLE_CHARA_F);
                break;

            case VC_MV_FIX_ANG:
                Vc_FlagClear(VC_VISIBLE_CHARA_F);
                break;

            case VC_MV_SELF_VIEW:
                Vc_FlagClear(VC_VISIBLE_CHARA_F);
                break;

            case VC_MV_THROUGH_DOOR:
                Vc_FlagClear(VC_VISIBLE_CHARA_F);
                break;
        }
    }
    else
    {
        Vc_FlagClear(VC_VISIBLE_CHARA_F);
    }

    if (cam_mv_type == VC_MV_SELF_VIEW)
    {
        Vc_FlagSet(VC_WARP_CAM_F | VC_WARP_CAM_TGT_F);

        vcPrsFViewFlag = vcWork.flags_8 >> 9; /** `VC_PRS_F_VIEW_F` */
        vcPrsFViewFlag = vcPrsFViewFlag & 1;

        // `optExtraViewCtrl != 0 && vcPrsFViewFlag == 0` ||
        // `optExtraViewCtrl == 0 && vcPrsFViewFlag == 1`
        if ((g_GameWorkConst->config_0.optExtraViewCtrl_28 != 0 && (vcPrsFViewFlag ^ 1) != 0) ||
            (g_GameWorkConst->config_0.optExtraViewCtrl_28 == 0 && vcPrsFViewFlag != 0))
        {
            vcOldPrsFViewFlag = (vcWork.flags_8 >> 10); /** `VC_OLD_PRS_F_VIEW_F` */
            vcOldPrsFViewFlag = vcOldPrsFViewFlag & (1 << 0);

            // `(optExtraViewCtrl != 0 && vcOldPrsFViewFlag == 0) == false` A&&
            // `(optExtraViewCtrl == 0 && vcOldPrsFViewFlag == 1) == false`
            if (!(g_GameWorkConst->config_0.optExtraViewCtrl_28 != 0 && (vcOldPrsFViewFlag ^ 1) != 0) &&
                !(g_GameWorkConst->config_0.optExtraViewCtrl_28 == 0 && vcOldPrsFViewFlag != 0))
            {
                if (g_GameWorkConst->config_0.optExtraViewMode_29 != 0)
                {
                    Vc_FlagSet(VC_WARP_WATCH_F);
                }
            }
        }
    }

    if (all_warp_f != 0)
    {
        Vc_FlagSet(VC_WARP_CAM_F | VC_WARP_WATCH_F | VC_WARP_CAM_TGT_F);
    }

    if (far_watch_rate != 0)
    {
        Vc_FlagSet(VC_WARP_CAM_TGT_F);
    }
}

void vcPreSetDataInVC_WORK(VC_WORK* w_p, VC_ROAD_DATA* vc_road_ary_list) // 0x80081B6C
{
    if (g_DeltaTime0 != 0)
    {
        if (vcWork.flags_8 & VC_PRS_F_VIEW_F)
        {
            vcWork.flags_8 |= VC_OLD_PRS_F_VIEW_F;
        }
        else
        {
            vcWork.flags_8 &= ~VC_OLD_PRS_F_VIEW_F;
        }

        if (g_Controller0->btnsHeld_C & g_GameWorkPtr->config_0.controllerConfig_0.view_E)
        {
            vcWork.flags_8 |= VC_PRS_F_VIEW_F;
        }
        else
        {
            vcWork.flags_8 &= ~VC_PRS_F_VIEW_F;
        }
    }

    vcWork.scr_half_ang_wx_2E = (s16)(ratan2(g_GameWork.gsScreenWidth_588,  vcWork.geom_screen_dist_30) >> 1);
    vcWork.scr_half_ang_wy_2C = (s16)(ratan2(g_GameWork.gsScreenHeight_58A, vcWork.geom_screen_dist_30) >> 1);

    if (vcWork.through_door_activate_init_f_C != 0)
    {
        vcSetTHROUGH_DOOR_CAM_PARAM_in_VC_WORK(&vcWork, VC_TDSC_START);
    }

    vcSetTHROUGH_DOOR_CAM_PARAM_in_VC_WORK(&vcWork, VC_TDSC_MAIN);
    vcSetNearestEnemyDataInVC_WORK(w_p);
    vcSetNearRoadAryByCharaPos(w_p, vc_road_ary_list, FP_METER(20.0f), 0, w_p->nearest_enemy_2DC != NULL);
}

void vcSetTHROUGH_DOOR_CAM_PARAM_in_VC_WORK(VC_WORK* w_p, enum _THROUGH_DOOR_SET_CMD_TYPE set_cmd_type) // 0x80081CBC
{
    VC_THROUGH_DOOR_CAM_PARAM* prm_p = &w_p->through_door_10;

    switch (set_cmd_type)
    {
        case VC_TDSC_START:
            w_p->through_door_10.active_f_0 = 1;
            prm_p->timer_4                  = 0;
            prm_p->rail_ang_y_8             = w_p->chara_eye_ang_y_144;
            prm_p->rail_sta_pos_C.vx        = w_p->chara_pos_114.vx;
            prm_p->rail_sta_pos_C.vy        = w_p->chara_grnd_y_12C - FP_METER(1.95f);
            prm_p->rail_sta_pos_C.vz        = w_p->chara_pos_114.vz;
            break;

        case VC_TDSC_END:
            w_p->through_door_10.active_f_0 = 0;
            prm_p->timer_4                  = 0;
            break;

        case VC_TDSC_MAIN:
            if (w_p->through_door_10.active_f_0 != 0)
            {
                prm_p->rail_sta_to_chara_dist_18 = Vc_VectorMagnitudeCalc(w_p->chara_pos_114.vx - w_p->through_door_10.rail_sta_pos_C.vx,
                                                                          0,
                                                                          w_p->chara_pos_114.vz - w_p->through_door_10.rail_sta_pos_C.vz);

                prm_p->timer_4 += g_DeltaTime0;
            }
            break;
    }
}

void vcSetNearestEnemyDataInVC_WORK(VC_WORK* w_p) // 0x80081D90
{
    #define ENEMY_DEAD_TIMER_MAX 1.5f
    #define ENEMY_METERS_MAX     15.0f

    s32             set_active_data_f;
    s32             xz_dist;
    s32             ofs_x;
    s32             ofs_z;
    s_SubCharacter* sc_p            = NULL;
    s_SubCharacter* all_min_sc_p    = NULL;
    s_SubCharacter* active_min_sc_p = NULL;
    s32             all_min_dist    = FP_METER(ENEMY_METERS_MAX);
    s32             active_min_dist = FP_METER(ENEMY_METERS_MAX);

    if (g_SysWork.flags_22A4 & (1 << 5)) // `sh2jms->player.battle(ShBattleInfo).status & 0x10` in SH2.
    {
        w_p->nearest_enemy_2DC         = NULL;
        w_p->nearest_enemy_xz_dist_2E0 = FP_METER(ENEMY_METERS_MAX);
        return;
    }

    for (sc_p = &g_SysWork.npcs_1A0[0]; sc_p < &g_SysWork.npcs_1A0[NPC_COUNT_MAX]; sc_p++)
    {
        if ((((u8)sc_p->model_0.charaId_0 - 2) < 23u) &&                                                     // `Chara_Unknown23`
            (sc_p->dead_timer_C4 <= FP_FLOAT_TO(ENEMY_DEAD_TIMER_MAX, Q12_SHIFT) || sc_p->health_B0 >= 0) &&
            !(sc_p->flags_3E & (1 << 4)))                                                                    // `sc_p->battle(ShBattleInfo).status & 0x20` in SH2.
        {
            ofs_x = sc_p->position_18.vx - w_p->chara_pos_114.vx;
            ofs_z = sc_p->position_18.vz - w_p->chara_pos_114.vz;

            if (abs(ofs_x) >= FP_METER(ENEMY_METERS_MAX) || abs(ofs_z) >= FP_METER(ENEMY_METERS_MAX))
            {
                continue;
            }

            xz_dist = Vc_VectorMagnitudeCalc(ofs_x, 0, ofs_z);
            ratan2(ofs_x, ofs_z); // Result unused?

            if (xz_dist < all_min_dist)
            {
                all_min_dist = xz_dist;
                all_min_sc_p = sc_p;
            }

            // TODO: Not sure how to move the `set_active_data_f = 1` part out of this if.
            if (sc_p->model_0.charaId_0 >= Chara_HangedScratcher ||
                (set_active_data_f = 1, (sc_p->model_0.charaId_0 < Chara_Stalker)))
            {
                set_active_data_f = 1;
                if (sc_p->flags_3E & (1 << 1)) // `sc_p->battle(ShBattleInfo).status & (1 << 2)` in SH2.
                {
                    set_active_data_f = 0;
                    if (sc_p == &g_SysWork.npcs_1A0[g_SysWork.field_2353])
                    {
                        set_active_data_f = g_SysWork.playerCombatInfo_38.isAiming_13 > 0;
                    }
                }
            }

            if (set_active_data_f && xz_dist < active_min_dist)
            {
                active_min_dist = xz_dist;
                active_min_sc_p = sc_p;
            }
        }
    }

    if (active_min_sc_p)
    {
        w_p->nearest_enemy_2DC         = active_min_sc_p;
        w_p->nearest_enemy_xz_dist_2E0 = active_min_dist;
    }
    else
    {
        w_p->nearest_enemy_2DC         = all_min_sc_p;
        w_p->nearest_enemy_xz_dist_2E0 = all_min_dist;
    }
}

void vcSetNearRoadAryByCharaPos(VC_WORK* w_p, VC_ROAD_DATA* road_ary_list, s32 half_w, s32 unused, s32 near_enemy_f) // 0x80081FBC
{
    s32                diff_pos_x;
    s32                sum_pos_x;
    s32                diff_pos_z;
    s32                sum_pos_z;
    s32                rd_max_hx;
    s32                rd_max_hz;
    VC_NEAR_ROAD_DATA* ptr;
    VC_ROAD_DATA*      road_data_ptr;
    s32                sw_min_hx;
    s32                sw_min_hz;
    s32                rd_min_hx;
    s32                rd_min_hz;
    s32                sw_max_hx;
    s32                sw_max_hz;
    s32                flag;
    s32                dir_type;
    s32                var;

    road_data_ptr          = road_ary_list;
    w_p->near_road_suu_2B4 = 0;

    diff_pos_x = w_p->chara_pos_114.vx - half_w;
    sum_pos_x  = w_p->chara_pos_114.vx + half_w;
    diff_pos_z = w_p->chara_pos_114.vz - half_w;
    sum_pos_z  = w_p->chara_pos_114.vz + half_w;

    while (!(road_data_ptr->flags_10 & 1))
    {
        if (near_enemy_f != 0)
        {
            flag = road_data_ptr->flags_10 & VC_RD_USE_NO_ENEMY_F;
        }
        else
        {
            flag = road_data_ptr->flags_10 & VC_RD_USE_NEAR_ENEMY_F;
        }

        if (!flag)
        {
            rd_min_hx = FP_TO(road_data_ptr->lim_rd_8.min_hx, Q8_SHIFT);
            rd_max_hx = FP_TO(road_data_ptr->lim_rd_8.max_hx, Q8_SHIFT);
            rd_min_hz = FP_TO(road_data_ptr->lim_rd_8.min_hz, Q8_SHIFT);
            rd_max_hz = FP_TO(road_data_ptr->lim_rd_8.max_hz, Q8_SHIFT);

            var = 0;

            sw_min_hx = FP_TO(road_data_ptr->lim_sw_0.min_hx, Q8_SHIFT);
            sw_max_hx = FP_TO(road_data_ptr->lim_sw_0.max_hx, Q8_SHIFT);
            sw_min_hz = FP_TO(road_data_ptr->lim_sw_0.min_hz, Q8_SHIFT);
            sw_max_hz = FP_TO(road_data_ptr->lim_sw_0.max_hz, Q8_SHIFT);

            if ((sum_pos_x >= sw_min_hx && sw_max_hx >= diff_pos_x && sum_pos_z >= sw_min_hz && sw_max_hz >= diff_pos_z) ||
                (sum_pos_x >= rd_min_hx && rd_max_hx >= diff_pos_x && sum_pos_z >= rd_min_hz && rd_max_hz >= diff_pos_z))
            {
                ptr           = &w_p->near_road_ary_14C[w_p->near_road_suu_2B4];
                dir_type      = (rd_max_hz - rd_min_hz) < (rd_max_hx - rd_min_hx);
                ptr->road_p_0 = road_data_ptr;

                ptr->chara2road_sum_dist_8 = vcGetXZSumDistFromLimArea(&ptr->chara2road_vec_x_C, &ptr->chara2road_vec_z_10, w_p->chara_pos_114.vx,
                                                                       w_p->chara_pos_114.vz, sw_min_hx, sw_max_hx, sw_min_hz, sw_max_hz,
                                                                       ptr->road_p_0->flags_10 & VC_RD_MARGE_ROAD_F);

                ptr->rd_dir_type_4_mb = dir_type;
                ptr->use_priority_5   = vcRetRoadUsePriority(road_data_ptr->rd_type_11, var);
                ptr->rd_14.min_hx     = FP_FROM(rd_min_hx, Q8_SHIFT);
                ptr->rd_14.max_hx     = FP_FROM(rd_max_hx, Q8_SHIFT);
                ptr->rd_14.min_hz     = FP_FROM(rd_min_hz, Q8_SHIFT);
                ptr->rd_14.max_hz     = FP_FROM(rd_max_hz, Q8_SHIFT);
                ptr->sw_1C.min_hx     = FP_FROM(sw_min_hx, Q8_SHIFT);
                ptr->sw_1C.max_hx     = FP_FROM(sw_max_hx, Q8_SHIFT);
                ptr->sw_1C.min_hz     = FP_FROM(sw_min_hz, Q8_SHIFT);
                ptr->sw_1C.max_hz     = FP_FROM(sw_max_hz, Q8_SHIFT);
                w_p->near_road_suu_2B4++;
            }
        }

        road_data_ptr++;
    }
}

s32 vcRetRoadUsePriority(VC_ROAD_TYPE rd_type, s32 arg1) // 0x8008227C
{
    switch (rd_type)
    {
        case VC_RD_TYPE_EVENT:
            return 2;

        case VC_RD_TYPE_EFFECT:
            return 1;

        case VC_RD_TYPE_ROAD:
            return 0;

        default:
            return 0;
    }
}

s32 vcSetCurNearRoadInVC_WORK(VC_WORK* w_p) // 0x800822B8
{
    VC_NEAR_ROAD_DATA* new_cur_p;
    VC_NEAR_ROAD_DATA* n_rd_p;
    VC_NEAR_ROAD_DATA* old_cur_p;
    s16                old_cur_rd_ang_y;
    s16                ofs_ang_y;
    s32                old_cur_sum_dist;
    s32                adv_old_cur_dist;
    s32                new_cur_sum_dist;
    s32                proj_frame;
    s32                ret_warp_f;

    ret_warp_f       = 0;
    new_cur_sum_dist = vcGetBestNewCurNearRoad(&new_cur_p, VC_CHK_NEAREST_SWITCH_TYPE, &w_p->chara_pos_114, w_p);
    old_cur_p        = NULL;

    for (n_rd_p = w_p->near_road_ary_14C; n_rd_p < &w_p->near_road_ary_14C[w_p->near_road_suu_2B4]; n_rd_p++)
    {
        if (n_rd_p->road_p_0 == w_p->cur_near_road_2B8.road_p_0)
        {
            old_cur_p = n_rd_p;
        }
    }

    if (old_cur_p == NULL)
    {
        if (new_cur_p->road_p_0->flags_10 & VC_RD_WARP_IN_F)
        {
            ret_warp_f = 1;
        }
        if (w_p->cur_near_road_2B8.road_p_0->flags_10 & VC_RD_WARP_OUT_F)
        {
            ret_warp_f = 1;
        }

        w_p->cur_near_road_2B8 = *new_cur_p;

        return ret_warp_f;
    }

    adv_old_cur_dist = vcAdvantageDistOfOldCurRoad(old_cur_p);

    if (new_cur_p->use_priority_5 < old_cur_p->use_priority_5 && old_cur_p->chara2road_sum_dist_8 < (adv_old_cur_dist * 2))
    {
        w_p->cur_near_road_2B8 = *old_cur_p;
    }
    else
    {
        if (old_cur_p->use_priority_5 < new_cur_p->use_priority_5 && new_cur_p->chara2road_sum_dist_8 <= 0)
        {
            if (new_cur_p->road_p_0->flags_10 & VC_RD_WARP_IN_F)
            {
                ret_warp_f = 1;
            }

            if (w_p->cur_near_road_2B8.road_p_0->flags_10 & VC_RD_WARP_OUT_F)
            {
                ret_warp_f = 1;
            }

            w_p->cur_near_road_2B8 = *new_cur_p;
            return ret_warp_f;
        }

        old_cur_sum_dist = old_cur_p->chara2road_sum_dist_8;

        switch (old_cur_p->rd_dir_type_4_mb)
        {
            case 0:
                old_cur_rd_ang_y = 0;
                break;

            case 1:
                old_cur_rd_ang_y = FP_ANGLE(90.0f);
                break;

            default:
                old_cur_rd_ang_y = 0;
                break;
        }

        ofs_ang_y = shAngleRegulate(w_p->chara_mv_ang_y_140 - old_cur_rd_ang_y);

        if (ofs_ang_y < 0)
        {
            ofs_ang_y += FP_ANGLE(180.0f);
        }

        if (ofs_ang_y > FP_ANGLE(90.0f))
        {
            ofs_ang_y = FP_ANGLE(180.0f) - ofs_ang_y;
        }

        proj_frame = old_cur_sum_dist - adv_old_cur_dist;

        if (new_cur_sum_dist >= proj_frame)
        {
            w_p->cur_near_road_2B8 = *old_cur_p;
        }
        else if (old_cur_sum_dist < 0 && ofs_ang_y < FP_ANGLE(20.0f))
        {
            w_p->cur_near_road_2B8 = *old_cur_p;
        }
        else
        {
            if (new_cur_p->road_p_0->flags_10 & VC_RD_WARP_IN_F)
            {
                ret_warp_f = 1;
            }

            if (w_p->cur_near_road_2B8.road_p_0->flags_10 & VC_RD_WARP_OUT_F)
            {
                ret_warp_f = 1;
            }

            w_p->cur_near_road_2B8 = *new_cur_p;
        }
    }

    return ret_warp_f;
}

s32 vcGetBestNewCurNearRoad(VC_NEAR_ROAD_DATA** new_cur_pp, VC_CAM_CHK_TYPE chk_type, VECTOR3* pos, VC_WORK* w_p) // 0x800826AC
{
    s32                dummy;
    VC_NEAR_ROAD_DATA* evnt_nearest_p;
    VC_NEAR_ROAD_DATA* eff_nearest_p;
    VC_NEAR_ROAD_DATA* road_nearest_p;
    VC_NEAR_ROAD_DATA* new_cur_p;
    s32                road_min_dist;
    s32                eff_min_dist;
    s32                evnt_min_dist;
    s32                renewal_f;
    s32                new_cur_dist;
    s32                new_cur_priority;

    new_cur_p    = NULL;
    new_cur_dist = INT_MAX;

    evnt_min_dist = vcGetNearestNEAR_ROAD_DATA(&evnt_nearest_p, chk_type, VC_RD_TYPE_EVENT,  pos, w_p, 0);
    eff_min_dist  = vcGetNearestNEAR_ROAD_DATA(&eff_nearest_p,  chk_type, VC_RD_TYPE_EFFECT, pos, w_p, 0);
    road_min_dist = vcGetNearestNEAR_ROAD_DATA(&road_nearest_p, chk_type, VC_RD_TYPE_ROAD,   pos, w_p, 0);

    new_cur_priority = 0;
    renewal_f        = 0;

    if (evnt_nearest_p != NULL)
    {
        if (new_cur_priority < evnt_nearest_p->use_priority_5)
        {
            if (evnt_min_dist <= 0 || evnt_min_dist < new_cur_dist)
            {
                renewal_f = 1;
            }
        }
        else if (evnt_nearest_p->use_priority_5 >= new_cur_priority)
        {
            if (evnt_min_dist < new_cur_dist)
            {
                renewal_f = 1;
            }
        }
        else if (new_cur_dist > 0 && evnt_min_dist < new_cur_dist)
        {
            renewal_f = 1;
        }
    }

    if (renewal_f != 0)
    {
        new_cur_p        = evnt_nearest_p;
        new_cur_dist     = evnt_min_dist;
        new_cur_priority = new_cur_p->use_priority_5;
    }

    renewal_f = 0;

    if (road_nearest_p != NULL)
    {
        if (new_cur_priority < road_nearest_p->use_priority_5)
        {
            if (road_min_dist <= 0 || road_min_dist < new_cur_dist)
            {
                renewal_f = 1;
            }
        }
        else if (road_nearest_p->use_priority_5 >= new_cur_priority)
        {
            if (road_min_dist < new_cur_dist)
            {
                renewal_f = 1;
            }
        }
        else if (new_cur_dist > 0 && road_min_dist < new_cur_dist)
        {
            renewal_f = 1;
        }
    }

    if (renewal_f != 0)
    {
        new_cur_p        = road_nearest_p;
        new_cur_dist     = road_min_dist;
        new_cur_priority = new_cur_p->use_priority_5;
    }

    renewal_f = 0;

    if (eff_nearest_p != NULL)
    {
        if (new_cur_priority < eff_nearest_p->use_priority_5)
        {
            if (eff_min_dist <= 0 || eff_min_dist < new_cur_dist)
            {
                renewal_f = 1;
            }
        }
        else if (eff_nearest_p->use_priority_5 >= new_cur_priority)
        {
            if (eff_min_dist < new_cur_dist)
            {
                renewal_f = 1;
            }
        }
        else if (new_cur_dist > 0 && eff_min_dist < new_cur_dist)
        {
            renewal_f = 1;
        }
    }

    if (renewal_f != 0)
    {
        new_cur_p    = eff_nearest_p;
        new_cur_dist = eff_min_dist;
    }

    if (new_cur_p == NULL)
    {
        new_cur_p    = &vcNullNearRoad;
        new_cur_dist = vcGetXZSumDistFromLimArea(&dummy, &dummy, pos->vx, pos->vz,
                                                 FP_TO(vcNullNearRoad.rd_14.min_hx, Q8_SHIFT), FP_TO(vcNullNearRoad.rd_14.max_hx, Q8_SHIFT),
                                                 FP_TO(vcNullNearRoad.rd_14.min_hz, Q8_SHIFT), FP_TO(vcNullNearRoad.rd_14.max_hz, Q8_SHIFT),
                                                 vcNullNearRoad.road_p_0->flags_10 & VC_RD_MARGE_ROAD_F);
    }

    *new_cur_pp = new_cur_p;
    return new_cur_dist;
}

s32 vcGetNearestNEAR_ROAD_DATA(VC_NEAR_ROAD_DATA** out_nearest_p_addr, VC_CAM_CHK_TYPE chk_type, VC_ROAD_TYPE rd_type, VECTOR3* pos, VC_WORK* w_p, s32 chk_only_set_marge_f) // 0x80082908
{
    s32                dummy;
    VC_NEAR_ROAD_DATA* n_rd_p;
    VC_NEAR_ROAD_DATA* nearest_p;
    s32                min_x;
    s32                max_x;
    s32                min_z;
    s32                max_z;
    s32                dist;
    s32                min_sum_dist;

    nearest_p    = NULL;
    n_rd_p       = w_p->near_road_ary_14C;
    min_sum_dist = INT_MAX;

    for (n_rd_p = w_p->near_road_ary_14C; n_rd_p < &w_p->near_road_ary_14C[w_p->near_road_suu_2B4]; n_rd_p++)
    {
        if (n_rd_p->road_p_0->rd_type_11 == rd_type && (chk_only_set_marge_f == 0 || n_rd_p->road_p_0->flags_10 & VC_RD_MARGE_ROAD_F))
        {
            switch (chk_type)
            {
                case VC_CHK_NEAREST_ROAD_TYPE:
                    min_x = FP_TO(n_rd_p->rd_14.min_hx, Q8_SHIFT);
                    max_x = FP_TO(n_rd_p->rd_14.max_hx, Q8_SHIFT);
                    min_z = FP_TO(n_rd_p->rd_14.min_hz, Q8_SHIFT);
                    max_z = FP_TO(n_rd_p->rd_14.max_hz, Q8_SHIFT);
                    break;

                case VC_CHK_NEAREST_SWITCH_TYPE:
                    min_x = FP_TO(n_rd_p->sw_1C.min_hx, Q8_SHIFT);
                    max_x = FP_TO(n_rd_p->sw_1C.max_hx, Q8_SHIFT);
                    min_z = FP_TO(n_rd_p->sw_1C.min_hz, Q8_SHIFT);
                    max_z = FP_TO(n_rd_p->sw_1C.max_hz, Q8_SHIFT);
                    break;

                default:
                    continue;
            }

            dist = vcGetXZSumDistFromLimArea(&dummy, &dummy, pos->vx, pos->vz, min_x, max_x, min_z, max_z, n_rd_p->road_p_0->flags_10 & VC_RD_MARGE_ROAD_F);

            if (min_sum_dist >= dist)
            {
                min_sum_dist = dist;
                nearest_p    = n_rd_p;
            }
        }
    }

    *out_nearest_p_addr = nearest_p;
    return min_sum_dist;
}

s32 vcAdvantageDistOfOldCurRoad(VC_NEAR_ROAD_DATA* old_cur_p) // 0x80082AD0
{
    switch ((s32)old_cur_p->road_p_0->rd_type_11)
    {
        case VC_RD_TYPE_ROAD:
        case VC_RD_TYPE_EFFECT:
        default:
            return FP_METER(0.35f);

        case VC_RD_TYPE_EVENT:
            return FP_METER(0.15f);
    }
}

void vcAutoRenewalWatchTgtPosAndAngZ(VC_WORK* w_p, VC_CAM_MV_TYPE cam_mv_type, VC_AREA_SIZE_TYPE cur_rd_area_size, int far_watch_rate, int self_view_eff_rate) // 0x80082B10
{
    VECTOR3 far_watch_pos;

    vcMakeFarWatchTgtPos(&far_watch_pos, w_p, cur_rd_area_size);
    if (cam_mv_type != VC_MV_SELF_VIEW)
    {
        vcMakeNormalWatchTgtPos(&w_p->watch_tgt_pos_7C, &w_p->watch_tgt_ang_z_8C, w_p, cam_mv_type, cur_rd_area_size);
        if (far_watch_rate != 0)
        {
            w_p->watch_tgt_pos_7C.vx += FP_MULTIPLY(far_watch_rate, far_watch_pos.vx - w_p->watch_tgt_pos_7C.vx, Q12_SHIFT);
            w_p->watch_tgt_pos_7C.vy += FP_MULTIPLY(far_watch_rate, far_watch_pos.vy - w_p->watch_tgt_pos_7C.vy, Q12_SHIFT);
            w_p->watch_tgt_pos_7C.vz += FP_MULTIPLY(far_watch_rate, far_watch_pos.vz - w_p->watch_tgt_pos_7C.vz, Q12_SHIFT);
        }
    }
    else
    {
        w_p->watch_tgt_pos_7C = far_watch_pos;
    }

    vcMixSelfViewEffectToWatchTgtPos(&w_p->watch_tgt_pos_7C, &w_p->watch_tgt_ang_z_8C, self_view_eff_rate,
                                     w_p, &g_SysWork.playerBoneCoords_890[PlayerBone_Head].workm, g_SysWork.player_4C.chara_0.model_0.anim_4.animIdx_0);

    if (w_p->watch_tgt_pos_7C.vy > w_p->watch_tgt_max_y_88)
    {
        w_p->watch_tgt_pos_7C.vy = w_p->watch_tgt_max_y_88;
    }
}

void vcMakeNormalWatchTgtPos(VECTOR3* watch_tgt_pos, s16* watch_tgt_ang_z_p, VC_WORK* w_p, enum _VC_CAM_MV_TYPE cam_mv_type, enum _VC_AREA_SIZE_TYPE cur_rd_area_size) // 0x80082C58
{
    SVECTOR ang;                      // Guessed name.
    SVECTOR vec;                      // Guessed name.
    s32     chara_to_cam_dist;        // Guessed name.
    s32     watch_y;                  // Guessed name.
    s32     tgt_chara2watch_cir_dist; // Guessed name.
    s32     tgt_watch_cir_r;          // Guessed name.
    s32     tgt_watch_cir_r_ext;      // Guessed name.

    *watch_tgt_ang_z_p = 0;

    if (cam_mv_type == VC_MV_FIX_ANG)
    {
        ang.vx = shAngleRegulate(FP_TO((u8)w_p->cur_near_road_2B8.road_p_0->fix_ang_x_16, Q4_SHIFT));
        ang.vy = shAngleRegulate(FP_TO((u8)w_p->cur_near_road_2B8.road_p_0->fix_ang_y_17, Q4_SHIFT));
        ang.vz = 0;

        vwAngleToVector(&vec, &ang, FP_METER(0.25f));

        watch_tgt_pos->vx = (vec.vx * 16) + w_p->cam_pos_50.vx;
        watch_tgt_pos->vy = (vec.vy * 16) + w_p->cam_pos_50.vy;
        watch_tgt_pos->vz = (vec.vz * 16) + w_p->cam_pos_50.vz;
    }
    else
    {
        chara_to_cam_dist = Vc_VectorMagnitudeCalc(w_p->chara_pos_114.vx - w_p->cam_pos_50.vx,
                                                   0,
                                                   w_p->chara_pos_114.vz - w_p->cam_pos_50.vz);

        switch (cur_rd_area_size)
        {
            case VC_AREA_TINY:
                tgt_watch_cir_r     = FP_METER(1.0f);
                tgt_watch_cir_r_ext = FP_METER(3.0f);
                break;

            case VC_AREA_SMALL:
                tgt_watch_cir_r     = FP_METER(1.0f);
                tgt_watch_cir_r_ext = FP_METER(3.0f);
                break;

            default:
                tgt_watch_cir_r     = FP_METER(2.5f);
                tgt_watch_cir_r_ext = FP_METER(5.5f);
                break;
        }

        switch (cam_mv_type)
        {
            default:
            case VC_MV_SETTLE:
            case VC_MV_SELF_VIEW:
                tgt_chara2watch_cir_dist = 0;
                break;

            case VC_MV_CHASE:
            case VC_MV_THROUGH_DOOR:
                tgt_chara2watch_cir_dist = 0;
                if (chara_to_cam_dist < (tgt_watch_cir_r + tgt_watch_cir_r_ext))
                {
                    tgt_chara2watch_cir_dist = (tgt_watch_cir_r + tgt_watch_cir_r_ext) - chara_to_cam_dist;
                }
                break;
        }

        watch_y = FP_TO(vcWork.cur_near_road_2B8.road_p_0->ofs_watch_hy_14, Q8_SHIFT) + w_p->chara_bottom_y_120;
        vcSetWatchTgtXzPos(watch_tgt_pos, &w_p->chara_pos_114, &w_p->cam_pos_50, tgt_chara2watch_cir_dist, tgt_watch_cir_r, w_p->chara_eye_ang_y_144);
        vcSetWatchTgtYParam(watch_tgt_pos, w_p, cam_mv_type, watch_y);
    }
}

void vcMixSelfViewEffectToWatchTgtPos(VECTOR3* watch_tgt_pos, s16* watch_tgt_ang_z_p, s16 effect_rate, VC_WORK* w_p, MATRIX* head_mat, s32 anim_status) // 0x80082DF8
{
    // TODO: Most aren't original names. Try substituting with ones found in symbols.
    SVECTOR    cam_ang;       // Original name.
    s32        angle_delta_y;
    s32        delta_y;
    s32        new_y;
    s32        delta_z;
    s32        new_x;
    s32        delta_x;
    s32        new_z;
    s32        dist_to_target;
    s32        temp_dir;
    s32        vertical_angle;
    s32        abs_angle_delta_y;
    s32        corrected_angle_y;
    s_SysWork* sys_work;

    delta_x = watch_tgt_pos->vx - w_p->cam_pos_50.vx;
    delta_y = watch_tgt_pos->vy - w_p->cam_pos_50.vy;
    delta_z = watch_tgt_pos->vz - w_p->cam_pos_50.vz;

    dist_to_target = Vc_VectorMagnitudeCalc(delta_x, delta_y, delta_z);

    vertical_angle = ratan2(-delta_y, Vc_VectorMagnitudeCalc(delta_x, 0, delta_z));
    vertical_angle = (vertical_angle >= FP_ANGLE(-70.0f)) ? ((vertical_angle <= FP_ANGLE(70.0f)) ? vertical_angle : FP_ANGLE(70.0f)) : FP_ANGLE(-70.0f);

    ratan2(delta_x, delta_z);

    sys_work = &g_SysWork;

    vwMatrixToAngleYXZ(&cam_ang, head_mat);
    angle_delta_y = shAngleRegulate(cam_ang.vy - sys_work->player_4C.chara_0.rotation_24.vy);

    switch (anim_status)
    {
        case 6:
        case 7:
            break;

        case 34:
        case 35:
            if (w_p->nearest_enemy_2DC != NULL)
            {
                cam_ang.vz = FP_ANGLE(0.0f);
            }
            break;

        default:
            cam_ang.vz = cam_ang.vz >> 1;
            break;
    }

    switch (anim_status)
    {
        case 44:
        case 45:
        case 46:
        case 47:
            break;

        default:
            cam_ang.vy = g_SysWork.player_4C.chara_0.rotation_24.vy;
            break;

        case 34:
        case 35:
            if (w_p->nearest_enemy_2DC != NULL)
            {
                cam_ang.vy = g_SysWork.player_4C.chara_0.rotation_24.vy;
            }
            else
            {
                cam_ang.vy += FP_ANGLE(30.0f);
            }
            break;

        case 52:
        case 53:
            abs_angle_delta_y = angle_delta_y;
            if (angle_delta_y < FP_ANGLE(0.0f))
            {
                abs_angle_delta_y = -angle_delta_y;
            }

            if (abs_angle_delta_y > FP_ANGLE(4.0f))
            {
                corrected_angle_y = ((abs_angle_delta_y - FP_ANGLE(4.0f)) >> 3) + FP_ANGLE(4.0f);
                if (angle_delta_y < FP_ANGLE(0.0f))
                {
                    corrected_angle_y = -corrected_angle_y;
                }
            }
            else
            {
                corrected_angle_y = angle_delta_y;
            }

            cam_ang.vy = g_SysWork.player_4C.chara_0.rotation_24.vy + corrected_angle_y;
            break;

        case 4:
        case 5:
        case 6:
        case 7:
        case 24:
        case 25:
        case 26:
        case 27:
            angle_delta_y = angle_delta_y >> 3;
            if (angle_delta_y >= FP_ANGLE(-10.0f))
            {
                corrected_angle_y = angle_delta_y;
                if (corrected_angle_y > FP_ANGLE(10.0f))
                {
                    corrected_angle_y = FP_ANGLE(10.0f);
                }
            }
            else
            {
                corrected_angle_y = FP_ANGLE(-10.0f);
            }

            cam_ang.vy = g_SysWork.player_4C.chara_0.rotation_24.vy + corrected_angle_y;
            break;
    }

    switch (anim_status)
    {
        case 4:
            break;

        case 54:
        case 55:
            cam_ang.vx = cam_ang.vx >> 1;

        case 52:
        case 53:
            cam_ang.vx -= FP_ANGLE(8.0f);
            break;

        case 34:
        case 35:
            if (w_p->nearest_enemy_2DC != NULL)
            {
                cam_ang.vx = FP_ANGLE(-7.0f);
            }
            else
            {
                cam_ang.vx -= FP_ANGLE(8.0f);
            }
            break;

        case 24:
        case 25:
        case 26:
        case 27:
            temp_dir = (g_SysWork.player_4C.chara_0.rotation_24.vy >> 7) & 0xF;
            if (temp_dir == 0 || temp_dir == 5)
            {
                cam_ang.vx -= FP_ANGLE(1.0f);
            }

            cam_ang.vx -= FP_ANGLE(6.0f);
            break;
    }

    switch (anim_status)
    {
        default:
            cam_ang.vx = FP_MULTIPLY(vertical_angle, FP_ANGLE(252.0f), Q12_SHIFT);
            break;

        case 4:
        case 5:
        case 6:
        case 7:
        case 24:
        case 25:
        case 26:
        case 27:
        case 34:
        case 35:
        case 52:
        case 53:
            cam_ang.vx = cam_ang.vx + (vertical_angle >> 1);
            break;
    }

    limitRange(cam_ang.vx, FP_ANGLE(-80.0f), FP_ANGLE(80.0f));

    *watch_tgt_ang_z_p += Math_MulFixed(shAngleRegulate(cam_ang.vz - *watch_tgt_ang_z_p), effect_rate, Q12_SHIFT);

    new_x = w_p->cam_pos_50.vx + FP_MULTIPLY(shRcos(cam_ang.vx), FP_MULTIPLY(dist_to_target, shRsin(cam_ang.vy), Q12_SHIFT), Q12_SHIFT);
    new_z = w_p->cam_pos_50.vz + FP_MULTIPLY(shRcos(cam_ang.vx), FP_MULTIPLY(dist_to_target, shRcos(cam_ang.vy), Q12_SHIFT), Q12_SHIFT);
    new_y = w_p->cam_pos_50.vy - FP_MULTIPLY(dist_to_target, shRsin(cam_ang.vx), Q12_SHIFT);

    watch_tgt_pos->vx += Math_MulFixed(new_x - watch_tgt_pos->vx, effect_rate, Q12_SHIFT);
    watch_tgt_pos->vy += Math_MulFixed(new_y - watch_tgt_pos->vy, effect_rate, Q12_SHIFT);
    watch_tgt_pos->vz += Math_MulFixed(new_z - watch_tgt_pos->vz, effect_rate, Q12_SHIFT);
}

void vcMakeFarWatchTgtPos(VECTOR3* watch_tgt_pos, VC_WORK* w_p, VC_AREA_SIZE_TYPE cur_rd_area_size) // 0x800832B4
{
    s_func_800699F8 sp10;
    s32             dist;
    s32             ofs_y;
    s32             lim_y;
    s32             watch_y;
    s32             use_dist;
    s32             adj_dist;
    s_SubCharacter* sc_p;

    if (cur_rd_area_size == VC_AREA_TINY)
    {
        use_dist = FP_METER(2.8f);
    }
    else if (cur_rd_area_size == VC_AREA_SMALL)
    {
        use_dist = FP_METER(5.5f);
    }
    else
    {
        use_dist = FP_METER(10.0f);
    }

    watch_y = w_p->chara_pos_114.vy - FP_METER(0.8f);

    if (w_p->nearest_enemy_2DC != NULL)
    {
        sc_p = w_p->nearest_enemy_2DC;

        dist = w_p->nearest_enemy_xz_dist_2E0;

        if (dist < FP_METER(1.7f))
        {
            adj_dist = (dist * FP_METER(-0.7f)) / FP_METER(1.7f);
        }
        else
        {
            adj_dist = FP_METER(-0.7f);
        }

        dist += adj_dist;

        // TODO: CLAMP or MIN/MAX?
        if (dist < use_dist)
        {
            use_dist = dist;
        }

        if (use_dist < FP_METER(0.4f))
        {
            use_dist = FP_METER(0.4f);
        }

        ofs_y = g_Chara_FileInfo[sc_p->model_0.charaId_0].field_C_2 * 16;

        switch (g_Chara_FileInfo[sc_p->model_0.charaId_0].field_C_0)
        {
            default:
            case 0:
                watch_y = sc_p->position_18.vy + ofs_y;
                break;

            case 1:
                func_800699F8(&sp10, sc_p->position_18.vx, sc_p->position_18.vz);

                if (sp10.field_8 == 0)
                {
                    watch_y = sc_p->position_18.vy + ofs_y;
                }
                else
                {
                    watch_y = sp10.chara_grnd_0 + ofs_y;
                }
                break;

            case 2:
                watch_y = w_p->field_2E4 + ofs_y;
                break;
        }

        lim_y = (w_p->nearest_enemy_xz_dist_2E0 >> 1) - FP_METER(0.5f);

        if (w_p->chara_pos_114.vy + lim_y < watch_y)
        {
            watch_y = w_p->chara_pos_114.vy + lim_y;
        }
    }

    watch_tgt_pos->vx = w_p->chara_pos_114.vx + FP_MULTIPLY(use_dist, shRsin(w_p->chara_eye_ang_y_144), Q12_SHIFT);
    watch_tgt_pos->vy = watch_y;
    watch_tgt_pos->vz = w_p->chara_pos_114.vz + FP_MULTIPLY(use_dist, shRcos(w_p->chara_eye_ang_y_144), Q12_SHIFT);
}

void vcSetWatchTgtXzPos(VECTOR3* watch_pos, VECTOR3* center_pos, VECTOR3* cam_pos, s32 tgt_chara2watch_cir_dist, s32 tgt_watch_cir_r, s16 watch_cir_ang_y) // 0x800834A8
{
    s16 cam2chr_ang;
    s32 chr2watch_x;
    s32 chr2watch_z;

    cam2chr_ang = ratan2(center_pos->vx - cam_pos->vx, center_pos->vz - cam_pos->vz);

    chr2watch_x = Math_MulFixed(tgt_chara2watch_cir_dist, shRsin(cam2chr_ang),     Q12_SHIFT) +
                  Math_MulFixed(tgt_watch_cir_r,          shRsin(watch_cir_ang_y), Q12_SHIFT);
    chr2watch_z = Math_MulFixed(tgt_chara2watch_cir_dist, shRcos(cam2chr_ang),     Q12_SHIFT) +
                  Math_MulFixed(tgt_watch_cir_r,          shRcos(watch_cir_ang_y), Q12_SHIFT);

    watch_pos->vx = center_pos->vx + chr2watch_x;
    watch_pos->vz = center_pos->vz + chr2watch_z;
}

void vcSetWatchTgtYParam(VECTOR3* watch_pos, VC_WORK* w_p, s32 cam_mv_type, s32 watch_y) // 0x800835C0
{
    if (cam_mv_type == VC_MV_SELF_VIEW)
    {
        watch_pos->vy = w_p->chara_center_y_128;
    }
    else
    {
        watch_pos->vy = watch_y;
    }
}

void vcAdjustWatchYLimitHighWhenFarView(VECTOR3* watch_pos, VECTOR3* cam_pos, s16 sy) // 0x800835E0
{
    s16 max_cam_ang_x = ratan2(cam_pos->vy + FP_METER(5.0f), FP_METER(13.0f)) - ratan2(g_GameWork.gsScreenHeight_58A / 2, sy);
    s32 dist          = Vc_VectorMagnitudeCalc(watch_pos->vx - cam_pos->vx, 0, watch_pos->vz - cam_pos->vz);
    s16 cam_ang_x     = ratan2(-watch_pos->vy + cam_pos->vy, dist);

    if (cam_ang_x > max_cam_ang_x)
    {
        s32 ofs_y     = FP_TO(((FP_FROM(dist, Q4_SHIFT)) * shRsin(max_cam_ang_x)) / shRcos(max_cam_ang_x), Q4_SHIFT);
        watch_pos->vy = cam_pos->vy - ofs_y;
    }
}

void vcAutoRenewalCamTgtPos(VC_WORK* w_p, VC_CAM_MV_TYPE cam_mv_type, VC_CAM_MV_PARAM* cam_mv_prm_p, VC_ROAD_FLAGS cur_rd_flags, VC_AREA_SIZE_TYPE cur_rd_area_size, s32 far_watch_rate) // 0x800836E8
{
    VECTOR3 tgt_vec;
    VECTOR3 ideal_pos;
    s32     max_tgt_mv_xz_len;

    switch (cam_mv_type)
    {
        case VC_MV_SELF_VIEW:
            vcMakeIdealCamPosByHeadPos(&ideal_pos, w_p, cur_rd_area_size);
            break;

        case VC_MV_FIX_ANG:
            vcMakeIdealCamPosForFixAngCam(&ideal_pos, w_p);
            break;

        case VC_MV_THROUGH_DOOR:
            vcMakeIdealCamPosForThroughDoorCam(&ideal_pos, w_p);
            break;

        default:
            vcMakeIdealCamPosUseVC_ROAD_DATA(&ideal_pos, w_p, cur_rd_area_size);
            break;
    }

    if (vcWork.flags_8 & VC_WARP_CAM_TGT_F)
    {
        w_p->cam_tgt_pos_44 = ideal_pos;
    }

    // TODO: Not sure what's going on here, doesn't seem to work as if statement.
    switch (cam_mv_type == VC_MV_SELF_VIEW)
    {
        case 0:
            max_tgt_mv_xz_len = vcRetMaxTgtMvXzLen(w_p, cam_mv_prm_p);
            vcMakeBasicCamTgtMvVec(&tgt_vec, &ideal_pos, w_p, max_tgt_mv_xz_len);

            if (cam_mv_type == VC_MV_CHASE && !(cur_rd_flags & VC_RD_NO_FRONT_FLIP_F))
            {
                vcCamTgtMvVecIsFlipedFromCharaFront(&tgt_vec, w_p, max_tgt_mv_xz_len, cur_rd_area_size);
            }

            if (cam_mv_type != VC_MV_THROUGH_DOOR)
            {
                vcAdjTgtMvVecYByCurNearRoad(&tgt_vec, w_p);
            }
            break;

        case 1:
            vcMakeBasicCamTgtMvVec(&tgt_vec, &ideal_pos, w_p, FP_METER(1.0f));
            break;
    }

    w_p->cam_tgt_mv_ang_y_10C = ratan2(tgt_vec.vx, tgt_vec.vz);

    if (g_DeltaTime0 != 0 || vcWork.flags_8 & VC_WARP_CAM_TGT_F)
    {
        w_p->cam_tgt_pos_44.vx += tgt_vec.vx;
        w_p->cam_tgt_pos_44.vy += tgt_vec.vy;
        w_p->cam_tgt_pos_44.vz += tgt_vec.vz;

        w_p->cam_tgt_velo_100.vx = FP_TO(tgt_vec.vx, Q12_SHIFT) / g_DeltaTime0;
        w_p->cam_tgt_velo_100.vy = FP_TO(tgt_vec.vy, Q12_SHIFT) / g_DeltaTime0;
        w_p->cam_tgt_velo_100.vz = FP_TO(tgt_vec.vz, Q12_SHIFT) / g_DeltaTime0;

        w_p->cam_tgt_spd_110 = Vc_VectorMagnitudeCalc(w_p->cam_tgt_velo_100.vx, 0, w_p->cam_tgt_velo_100.vz);
        return;
    }

    w_p->cam_tgt_velo_100.vx = 0;
    w_p->cam_tgt_velo_100.vz = 0;
    w_p->cam_tgt_spd_110     = 0;
}

s32 vcRetMaxTgtMvXzLen(VC_WORK* w_p, VC_CAM_MV_PARAM* cam_mv_prm_p) // 0x8008395C
{
    s32 max_spd_xz;

    max_spd_xz = w_p->chara_mv_spd_13C + FP_METER(1.0f) + abs(w_p->chara_ang_spd_y_142 * 8);
    max_spd_xz = (max_spd_xz < FP_METER(2.2f)) ? FP_METER(2.2f) : max_spd_xz;
    max_spd_xz = (cam_mv_prm_p->max_spd_xz > max_spd_xz) ? max_spd_xz : cam_mv_prm_p->max_spd_xz;

    return Math_MulFixed(max_spd_xz, g_DeltaTime0, Q12_SHIFT);
}

void vcMakeIdealCamPosByHeadPos(VECTOR3* ideal_pos, VC_WORK* w_p, VC_AREA_SIZE_TYPE cur_rd_area_size) // 0x800839CC
{
    s32 chara2cam_ang_y;

    if (w_p->flags_8 & VC_WARP_WATCH_F)
    {
        ideal_pos->vx = w_p->chara_pos_114.vx;
        ideal_pos->vy = w_p->chara_top_y_124;
        ideal_pos->vz = w_p->chara_pos_114.vz;
        return;
    }

    if (g_GameWorkConst->config_0.optExtraViewMode_29)
    {
        chara2cam_ang_y = w_p->chara_eye_ang_y_144   + FP_ANGLE(140.0f);
        ideal_pos->vy   = w_p->chara_head_pos_130.vy + FP_METER(0.07f);
    }
    else
    {
        chara2cam_ang_y = w_p->chara_eye_ang_y_144   + FP_ANGLE(170.0f);
        ideal_pos->vy   = w_p->chara_head_pos_130.vy + FP_METER(0.1f);
    }

    ideal_pos->vx = w_p->chara_head_pos_130.vx + FP_MULTIPLY(shRsin(chara2cam_ang_y), FP_ANGLE(64.8f), Q12_SHIFT);
    ideal_pos->vz = w_p->chara_head_pos_130.vz + FP_MULTIPLY(shRcos(chara2cam_ang_y), FP_ANGLE(64.8f), Q12_SHIFT);
}

void vcMakeIdealCamPosForFixAngCam(VECTOR3* ideal_pos, VC_WORK* w_p) // 0x80083ADC
{
    SVECTOR3       cam_angle_vec;
    s32            dist_x_to_lim_area;
    s32            dist_z_to_lim_area;
    VC_LIMIT_AREA* limit_area;
    s32            offset_dist;
    s32            chara_to_cam_dist;
    s32            max_dist_to_lim_area;
    s32            cam_offset_forward;
    s32            abs_dist_z_to_lim_area;
    s32            abs_dist_x_to_lim_area;

    cam_angle_vec.vx = FP_TO(w_p->cur_near_road_2B8.road_p_0->fix_ang_x_16, Q4_SHIFT);
    cam_angle_vec.vy = FP_TO(w_p->cur_near_road_2B8.road_p_0->fix_ang_y_17, Q4_SHIFT);
    cam_angle_vec.vz = 0;

    limit_area = &w_p->cur_near_road_2B8.road_p_0->lim_rd_8;
    vcGetXZSumDistFromLimArea(&dist_x_to_lim_area, &dist_z_to_lim_area, w_p->chara_pos_114.vx, w_p->chara_pos_114.vz,
                              FP_TO(w_p->cur_near_road_2B8.rd_14.min_hx, Q8_SHIFT), FP_TO(w_p->cur_near_road_2B8.rd_14.max_hx, Q8_SHIFT),
                              FP_TO(w_p->cur_near_road_2B8.rd_14.min_hz, Q8_SHIFT), FP_TO(w_p->cur_near_road_2B8.rd_14.max_hz, Q8_SHIFT), 0);

    abs_dist_x_to_lim_area = dist_x_to_lim_area;
    if (abs_dist_x_to_lim_area < 0)
    {
        abs_dist_x_to_lim_area = -abs_dist_x_to_lim_area;
    }

    abs_dist_z_to_lim_area = dist_z_to_lim_area;
    dist_x_to_lim_area     = abs_dist_x_to_lim_area;
    if (abs_dist_z_to_lim_area < 0)
    {
        abs_dist_z_to_lim_area = -abs_dist_z_to_lim_area;
    }

    dist_z_to_lim_area   = abs_dist_z_to_lim_area;
    max_dist_to_lim_area = abs_dist_z_to_lim_area;
    if (max_dist_to_lim_area < abs_dist_x_to_lim_area)
    {
        max_dist_to_lim_area = abs_dist_x_to_lim_area;
    }

    offset_dist       = (max_dist_to_lim_area >> 1) + FP_METER(1.5f);
    chara_to_cam_dist = Vc_VectorMagnitudeCalc(w_p->chara_pos_114.vx - w_p->cam_pos_50.vx,
                                               0,
                                               w_p->chara_pos_114.vz - w_p->cam_pos_50.vz);

    if (chara_to_cam_dist >= FP_METER(7.0f))
    {
        cam_offset_forward = 0;
    }
    else if (chara_to_cam_dist > FP_METER(1.5f))
    {
        cam_offset_forward = FP_MULTIPLY(FP_TO((chara_to_cam_dist - FP_METER(7.0f)), Q12_SHIFT) / FP_METER(-5.5f), FP_METER(0.7f), Q12_SHIFT);
    }
    else
    {
        cam_offset_forward = FP_METER(0.7f);
    }

    ideal_pos->vx = w_p->chara_pos_114.vx +
                    FP_MULTIPLY(cam_offset_forward, shRsin(w_p->chara_eye_ang_y_144), Q12_SHIFT) +
                    FP_MULTIPLY(offset_dist, shRsin(cam_angle_vec.vy + FP_ANGLE(180.0f)), Q12_SHIFT);
    ideal_pos->vz = w_p->chara_pos_114.vz +
                    FP_MULTIPLY(cam_offset_forward, shRcos(w_p->chara_eye_ang_y_144), Q12_SHIFT) +
                    FP_MULTIPLY(offset_dist, shRcos(cam_angle_vec.vy + FP_ANGLE(180.0f)), Q12_SHIFT);
    ideal_pos->vy = w_p->chara_pos_114.vy;

    vcAdjustXzInLimAreaUsingMIN_IN_ROAD_DIST(&ideal_pos->vx, &ideal_pos->vz, limit_area);
}

void vcMakeIdealCamPosForThroughDoorCam(VECTOR3* ideal_pos, VC_WORK* w_p) // 0x80083D2C
{
    VC_THROUGH_DOOR_CAM_PARAM* through_door_param;
    s16                        delta_angle_clamped;
    s32                        angle_threshold;
    s32                        offset_lateral;
    s32                        offset_forward;
    s32                        offset_scale;
    s16                        angle_diff_abs;

    through_door_param = &w_p->through_door_10;

    if (w_p->through_door_10.active_f_0 != 0)
    {
        if (w_p->through_door_activate_init_f_C != 0)
        {
            offset_forward = FP_METER(-1.3f);
            offset_lateral = 0;
        }
        else
        {
            switch (func_8003BD2C())
            {
                case 10:
                case 13:
                case 14:
                    angle_threshold = FP_ANGLE(14.95f);
                    offset_forward  = FP_METER(0.85f);
                    offset_lateral  = FP_METER(0.6f);
                    offset_scale    = FP_METER(0.7f);
                    break;

                default:
                    angle_threshold = FP_ANGLE(45.0f);
                    offset_forward  = FP_METER(0.75f);
                    offset_lateral  = FP_METER(0.7f);
                    offset_scale    = FP_METER(0.6f);
                    break;
            }

            angle_diff_abs = shAngleRegulate(w_p->chara_eye_ang_y_144 - through_door_param->rail_ang_y_8);

            if (angle_diff_abs < 0)
            {
                angle_diff_abs = -angle_diff_abs;
            }

            if ((angle_diff_abs - angle_threshold) < 0)
            {
                delta_angle_clamped = 0;
            }
            else
            {
                delta_angle_clamped = angle_diff_abs - angle_threshold;
            }

            offset_forward = offset_forward +
                             FP_MULTIPLY(-offset_lateral,
                                          shRcos((delta_angle_clamped * (0x800000 / (FP_ANGLE(180.0f) - angle_threshold)) * 16) >> 16), Q12_SHIFT);
            offset_lateral = FP_MULTIPLY(-offset_scale, shRsin(w_p->chara_eye_ang_y_144 - through_door_param->rail_ang_y_8), Q12_SHIFT);
        }

        ideal_pos->vx = through_door_param->rail_sta_pos_C.vx +
                        FP_MULTIPLY(offset_forward, shRsin(through_door_param->rail_ang_y_8), Q12_SHIFT) +
                        FP_MULTIPLY(offset_lateral, shRcos(through_door_param->rail_ang_y_8), Q12_SHIFT);
        ideal_pos->vz = through_door_param->rail_sta_pos_C.vz +
                        FP_MULTIPLY(offset_forward, shRcos(through_door_param->rail_ang_y_8), Q12_SHIFT) +
                        FP_MULTIPLY(offset_lateral, -shRsin(through_door_param->rail_ang_y_8), Q12_SHIFT);
        ideal_pos->vy = through_door_param->rail_sta_pos_C.vy;
    }
}

void vcMakeIdealCamPosUseVC_ROAD_DATA(VECTOR3* ideal_pos, VC_WORK* w_p, enum _VC_AREA_SIZE_TYPE cur_rd_area_size) // 0x80083F34
{
    s32                temp_x;
    s32                temp_z;
    VC_NEAR_ROAD_DATA* near_road_data;
    VC_ROAD_DATA*      road_data;
    s16                base_angle;
    s32                chara_pos_y;
    s16                delta_angle;
    s32                cam_pos_y;
    s32                horizontal_distance_fp;
    s32                blend_max_dist;
    s32                blend_min_dist;
    s32                delta_y_clamped;
    s32                final_cam_dist;
    s32                default_cam_dist;

    base_angle  = w_p->chara_eye_ang_y_144 + FP_ANGLE(180.0f);
    delta_angle = shAngleRegulate(w_p->cam_chara2ideal_ang_y_FE - base_angle);

    if (abs(w_p->chara_ang_spd_y_142) > FP_ANGLE(20.0f))
    {
        delta_angle = CLAMP(delta_angle, FP_ANGLE(-12.0f), FP_ANGLE(12.0f));
    }
    else if (delta_angle >= 0)
    {
        delta_angle = FP_ANGLE(12.0f);
    }
    else
    {
        delta_angle = FP_ANGLE(-12.0f);
    }

    w_p->cam_chara2ideal_ang_y_FE = shAngleRegulate(delta_angle + base_angle);

    if (cur_rd_area_size == VC_AREA_TINY)
    {
        default_cam_dist = FP_METER(1.8f);
    }
    else if (cur_rd_area_size == VC_AREA_SMALL)
    {
        default_cam_dist = FP_METER(2.0f);
    }
    else
    {
        default_cam_dist = FP_METER(2.5f);
    }

    near_road_data = &w_p->cur_near_road_2B8;

    ideal_pos->vx = w_p->chara_pos_114.vx + FP_MULTIPLY(default_cam_dist, shRsin(w_p->cam_chara2ideal_ang_y_FE), Q12_SHIFT);
    ideal_pos->vy = w_p->chara_top_y_124  - FP_METER(0.4f);
    ideal_pos->vz = w_p->chara_pos_114.vz + FP_MULTIPLY(default_cam_dist, shRcos(w_p->cam_chara2ideal_ang_y_FE), Q12_SHIFT);

    cam_pos_y   = w_p->cam_pos_50.vy;
    chara_pos_y = w_p->chara_pos_114.vy;

    temp_x = 0;
    temp_z = 0;

    delta_y_clamped = cam_pos_y - chara_pos_y;
    if (delta_y_clamped < 0)
    {
        delta_y_clamped = chara_pos_y - cam_pos_y;
    }

    delta_y_clamped -= FP_METER(1.5f);
    if (delta_y_clamped < 0)
    {
        delta_y_clamped = 0;
    }

    road_data = w_p->cur_near_road_2B8.road_p_0;

    ideal_pos->vy = CLAMP(ideal_pos->vy, FP_TO(road_data->lim_rd_min_hy_13, Q8_SHIFT), FP_TO(road_data->lim_rd_max_hy_12, Q8_SHIFT));

    temp_x = w_p->chara_pos_114.vx;
    temp_z = w_p->chara_pos_114.vz;

    vcAdjustXzInLimAreaUsingMIN_IN_ROAD_DIST(&temp_x, &temp_z, &near_road_data->rd_14);

    horizontal_distance_fp = FP_FROM(Vc_VectorMagnitudeCalc(temp_x - w_p->chara_pos_114.vx,
                                                            delta_y_clamped,
                                                            temp_z - w_p->chara_pos_114.vz), Q4_SHIFT);

    if (cur_rd_area_size == VC_AREA_TINY)
    {
        blend_min_dist = FP_METER(0.04375f);
        blend_max_dist = FP_METER(0.125);
    }
    else if (cur_rd_area_size < 2)
    {
        blend_min_dist = FP_METER(0.04375f);
        blend_max_dist = FP_METER(0.1875);
    }
    else
    {
        blend_min_dist = FP_METER(0.125);
        blend_max_dist = FP_METER(0.3125);
    }

    if (blend_max_dist >= horizontal_distance_fp)
    {
        if (blend_min_dist < horizontal_distance_fp)
        {
            final_cam_dist = default_cam_dist +
                             ((FP_METER(0.4f) - default_cam_dist) * (horizontal_distance_fp - blend_min_dist)) / (blend_max_dist - blend_min_dist);
        }
        else
        {
            final_cam_dist = default_cam_dist;
        }
    }
    else
    {
        final_cam_dist = FP_METER(0.4f);
    }

    ideal_pos->vx = w_p->chara_pos_114.vx + Math_MulFixed(final_cam_dist, shRsin(w_p->cam_chara2ideal_ang_y_FE), Q12_SHIFT);
    ideal_pos->vz = w_p->chara_pos_114.vz + Math_MulFixed(final_cam_dist, shRcos(w_p->cam_chara2ideal_ang_y_FE), Q12_SHIFT);

    vcAdjustXzInLimAreaUsingMIN_IN_ROAD_DIST(&ideal_pos->vx, &ideal_pos->vz, &near_road_data->rd_14);
}

void vcAdjustXzInLimAreaUsingMIN_IN_ROAD_DIST(s32* x_p, s32* z_p, VC_LIMIT_AREA* lim_p) // 0x80084210
{
    s32 min_z;
    s32 min_x;
    s32 max_z;
    s32 max_x;

    s32 x = *x_p;
    s32 z = *z_p;

    min_x = FP_TO(lim_p->min_hx, Q8_SHIFT) + MIN_IN_ROAD_DIST;
    max_x = FP_TO(lim_p->max_hx, Q8_SHIFT) - MIN_IN_ROAD_DIST;
    min_z = FP_TO(lim_p->min_hz, Q8_SHIFT) + MIN_IN_ROAD_DIST;
    max_z = FP_TO(lim_p->max_hz, Q8_SHIFT) - MIN_IN_ROAD_DIST;

    if (max_x < min_x)
    {
        min_x = (min_x + max_x) >> 1;
        max_x = min_x;
    }
    if (max_z < min_z)
    {
        min_z = (min_z + max_z) >> 1;
        max_z = min_z;
    }

    x = CLAMP(x, min_x, max_x);
    z = CLAMP(z, min_z, max_z);

    *x_p = x;
    *z_p = z;
}

void vcMakeBasicCamTgtMvVec(VECTOR3* tgt_mv_vec, VECTOR3* ideal_pos, VC_WORK* w_p, s32 max_tgt_mv_xz_len) // 0x800842C0
{
    s32 now2ideal_tgt_dist;
    s16 now2ideal_tgt_ang_y;
    s32 temp_s0; // SH2: `float xz_vec[4];`
    s32 temp_s1;

    temp_s1 = ideal_pos->vx - w_p->cam_tgt_pos_44.vx;
    temp_s0 = ideal_pos->vz - w_p->cam_tgt_pos_44.vz;

    now2ideal_tgt_dist  = Vc_VectorMagnitudeCalc(temp_s1, 0, temp_s0);
    now2ideal_tgt_ang_y = ratan2(temp_s1, temp_s0);

    if (now2ideal_tgt_dist < max_tgt_mv_xz_len)
    {
        tgt_mv_vec->vx = ideal_pos->vx - w_p->cam_tgt_pos_44.vx;
        tgt_mv_vec->vz = ideal_pos->vz - w_p->cam_tgt_pos_44.vz;
    }
    else
    {
        tgt_mv_vec->vx = FP_MULTIPLY(max_tgt_mv_xz_len, shRsin(now2ideal_tgt_ang_y), Q12_SHIFT);
        tgt_mv_vec->vz = FP_MULTIPLY(max_tgt_mv_xz_len, shRcos(now2ideal_tgt_ang_y), Q12_SHIFT);
    }

    if (g_DeltaTime0 == 0 && !(vcWork.flags_8 & VC_WARP_CAM_TGT_F))
    {
        tgt_mv_vec->vy = 0;
    }
    else
    {
        tgt_mv_vec->vy = ideal_pos->vy - w_p->cam_tgt_pos_44.vy;
    }
}

void vcAdjTgtMvVecYByCurNearRoad(VECTOR3* tgt_mv_vec, VC_WORK* w_p) // 0x800843F4
{
    VC_ROAD_DATA* cur_rd_p;
    s32           tgt_y;
    s32           to_chara_dist;
    s32           abs_ofs_y;
    s32           max_tgt_y;
    s32           min_tgt_y;
    s32           dist;
    s32           near_ratio;

    cur_rd_p = w_p->cur_near_road_2B8.road_p_0;

    to_chara_dist = Vc_VectorMagnitudeCalc(w_p->chara_pos_114.vx - w_p->cam_tgt_pos_44.vx,
                                           0,
                                           w_p->chara_pos_114.vz - w_p->cam_tgt_pos_44.vz);

    dist = CLAMP(to_chara_dist, FP_METER(1.2f), FP_METER(7.0f));

    // TODO: Weird multiplier?
    near_ratio = FP_MULTIPLY_PRECISE(FP_METER(7.0f) - dist, 0.1724f, Q12_SHIFT);
    near_ratio = CLAMP(near_ratio, 0, FP_METER(1.0f));

    switch (w_p->cur_near_road_2B8.road_p_0->mv_y_type_11)
    {
        case 0:
        default:
            abs_ofs_y = (to_chara_dist - FP_METER(0.3f)) >> 2;
            if (abs_ofs_y < 0)
            {
                abs_ofs_y = 0;
            }

            max_tgt_y = (abs_ofs_y + w_p->chara_top_y_124) - FP_METER(0.25f);
            min_tgt_y = (w_p->chara_top_y_124 - abs_ofs_y) - FP_METER(0.25f);
            break;

        case 1:
            min_tgt_y = Math_MulFixed(FP_TO(cur_rd_p->lim_rd_max_hy_12, Q8_SHIFT),
                                      FP_METER(1.0f) - near_ratio, Q12_SHIFT) + Math_MulFixed(FP_TO(cur_rd_p->lim_rd_min_hy_13, Q8_SHIFT),
                                                                                              near_ratio,
                                                                                              Q12_SHIFT);
            max_tgt_y = min_tgt_y;
            break;

        case 2:
            min_tgt_y = Math_MulFixed(FP_TO(cur_rd_p->lim_rd_min_hy_13, Q8_SHIFT),
                                      FP_METER(1.0f) - near_ratio, Q12_SHIFT) + Math_MulFixed(FP_TO(cur_rd_p->lim_rd_max_hy_12, Q8_SHIFT),
                                                                                              near_ratio,
                                                                                              Q12_SHIFT);
            max_tgt_y = min_tgt_y;
            break;

        case 3:
            min_tgt_y = FP_TO(cur_rd_p->lim_rd_min_hy_13, Q8_SHIFT);
            max_tgt_y = FP_TO(cur_rd_p->lim_rd_max_hy_12, Q8_SHIFT);
            break;
    }

    tgt_y = w_p->cam_tgt_pos_44.vy + tgt_mv_vec->vy;
    tgt_y = CLAMP(tgt_y, min_tgt_y, max_tgt_y);

    tgt_mv_vec->vy = tgt_y - w_p->cam_tgt_pos_44.vy;
}

void vcCamTgtMvVecIsFlipedFromCharaFront(VECTOR3* tgt_mv_vec, VC_WORK* w_p, s32 max_tgt_mv_xz_len, VC_AREA_SIZE_TYPE cur_rd_area_size)
{
    VECTOR3            pre_tgt_pos;
    VECTOR3            chk_pos;
    VECTOR3            post_tgt_pos;
    s16                flip_ang_y;
    VC_NEAR_ROAD_DATA* use_nearest_p;
    s16                ang_y;
    s32                flip_dist; // TODO: Name maybe switched with `mv_len`.
    s32                chk_near_dist;
    s32                mv_len;
    s32                min_z;
    s32                min_x;
    s32                max_z;
    s32                max_x;

    pre_tgt_pos.vx = tgt_mv_vec->vx + w_p->cam_tgt_pos_44.vx;
    pre_tgt_pos.vz = tgt_mv_vec->vz + w_p->cam_tgt_pos_44.vz;
    flip_dist      = vcFlipFromCamExclusionArea(&flip_ang_y, &w_p->old_cam_excl_area_r_6C, &pre_tgt_pos, &w_p->chara_pos_114, w_p->chara_eye_ang_y_144, cur_rd_area_size);
    if (flip_dist > 0)
    {
        mv_len = flip_dist;
        if (flip_dist > FP_METER(0.5f))
        {
            mv_len = FP_METER(0.5f);
        }

        // `chk_pos` is unused?
        chk_pos.vx = pre_tgt_pos.vx + Math_MulFixed(mv_len, shRsin(flip_ang_y), Q12_SHIFT);
        chk_pos.vz = pre_tgt_pos.vz + Math_MulFixed(mv_len, shRcos(flip_ang_y), Q12_SHIFT);

        if (w_p->cur_near_road_2B8.road_p_0->flags_10 & VC_RD_MARGE_ROAD_F)
        {
            chk_near_dist = vcGetNearestNEAR_ROAD_DATA(&use_nearest_p, VC_CHK_NEAREST_ROAD_TYPE, w_p->cur_near_road_2B8.road_p_0->rd_type_11, &pre_tgt_pos, w_p, 1);
            if (use_nearest_p == NULL)
            {
                use_nearest_p = &vcNullNearRoad;
            }
            else if (chk_near_dist > 0)
            {
                use_nearest_p = &w_p->cur_near_road_2B8;
            }
        }
        else
        {
            use_nearest_p = &w_p->cur_near_road_2B8;
        }

        post_tgt_pos.vx = pre_tgt_pos.vx + FP_MULTIPLY(flip_dist, shRsin(flip_ang_y), Q12_SHIFT);
        post_tgt_pos.vz = pre_tgt_pos.vz + FP_MULTIPLY(flip_dist, shRcos(flip_ang_y), Q12_SHIFT);

        min_x = FP_TO(use_nearest_p->rd_14.min_hx, Q8_SHIFT) + MIN_IN_ROAD_DIST;
        max_x = FP_TO(use_nearest_p->rd_14.max_hx, Q8_SHIFT) - MIN_IN_ROAD_DIST;
        min_z = FP_TO(use_nearest_p->rd_14.min_hz, Q8_SHIFT) + MIN_IN_ROAD_DIST;
        max_z = FP_TO(use_nearest_p->rd_14.max_hz, Q8_SHIFT) - MIN_IN_ROAD_DIST;

        if (max_x < min_x)
        {
            min_x = (min_x + max_x) >> 1;
            max_x = min_x;
        }
        if (max_z < min_z)
        {
            min_z = (min_z + max_z) >> 1;
            max_z = min_z;
        }

        post_tgt_pos.vx = CLAMP(post_tgt_pos.vx, min_x, max_x);
        post_tgt_pos.vz = CLAMP(post_tgt_pos.vz, min_z, max_z);

        tgt_mv_vec->vx = post_tgt_pos.vx - w_p->cam_tgt_pos_44.vx;
        tgt_mv_vec->vz = post_tgt_pos.vz - w_p->cam_tgt_pos_44.vz;

        if (max_tgt_mv_xz_len < Vc_VectorMagnitudeCalc(tgt_mv_vec->vx, 0, tgt_mv_vec->vz))
        {
            ang_y          = ratan2(tgt_mv_vec->vx, tgt_mv_vec->vz);
            tgt_mv_vec->vx = Math_MulFixed(max_tgt_mv_xz_len, shRsin(ang_y), Q12_SHIFT);
            tgt_mv_vec->vz = Math_MulFixed(max_tgt_mv_xz_len, shRcos(ang_y), Q12_SHIFT);
        }
    }
}

s32 vcFlipFromCamExclusionArea(s16* flip_ang_y_p, s32* old_cam_excl_area_r_p, VECTOR3* in_pos, VECTOR3* chara_pos, s16 chara_eye_ang_y, VC_AREA_SIZE_TYPE cur_rd_area_size) // 0x800848B0
{
    s16 target_angle_y;
    s32 min_step;
    s32 distance_to_chara;
    s32 relative_angle_y;
    s32 delta_radius;
    s32 exclusion_overlap;
    s16 abs_relative_angle_y;
    s32 base_radius;
    s32 desired_radius;

    target_angle_y   = ratan2(in_pos->vx - chara_pos->vx, in_pos->vz - chara_pos->vz);
    relative_angle_y = shAngleRegulate(target_angle_y - chara_eye_ang_y);

    abs_relative_angle_y = relative_angle_y;

    if (relative_angle_y < 0)
    {
        abs_relative_angle_y = -relative_angle_y;
    }

    switch (cur_rd_area_size)
    {
        case VC_AREA_SMALL:
            base_radius = FP_METER(1.0f);
            break;

        case VC_AREA_TINY:
            base_radius = FP_METER(0.7f);
            break;

        case VC_AREA_WIDE:
            base_radius = FP_METER(1.0f);
            break;

        default:
            base_radius = FP_METER(0.7f);
            break;
    }

    desired_radius = FP_FROM(base_radius * vwOresenHokan(excl_r_ary, 9, abs_relative_angle_y, 0, FP_ANGLE(180.0f)), Q12_SHIFT);

    if (*old_cam_excl_area_r_p != NO_VALUE)
    {
        delta_radius = desired_radius - *old_cam_excl_area_r_p;
        min_step     = FP_MULTIPLY((s64)g_DeltaTime0, (s64)FP_ANGLE(-180.0f), Q12_SHIFT);

        if (delta_radius < min_step)
        {
            delta_radius = min_step;
        }

        desired_radius = *old_cam_excl_area_r_p + delta_radius;
    }

    *old_cam_excl_area_r_p = desired_radius;

    distance_to_chara = Vc_VectorMagnitudeCalc(in_pos->vx - chara_pos->vx, 0, in_pos->vz - chara_pos->vz);

    exclusion_overlap = 0;

    if (distance_to_chara < desired_radius)
    {
        exclusion_overlap = desired_radius - distance_to_chara;
    }

    *flip_ang_y_p = target_angle_y;

    return exclusion_overlap;
}

void vcGetUseWatchAndCamMvParam(VC_WATCH_MV_PARAM** watch_mv_prm_pp, VC_CAM_MV_PARAM** cam_mv_prm_pp, s32 self_view_eff_rate, VC_WORK* w_p) // 0x80084A34
{
    VC_CAM_MV_PARAM* cam_mv_prm_stg_p;
    s32              add_ang_accel_y;

    if (w_p->flags_8 & VC_USER_WATCH_F)
    {
        *watch_mv_prm_pp = &w_p->user_watch_mv_prm_70;
    }
    else
    {
        vcWatchMvPrmSt.ang_accel_x = Math_MulFixed(self_view_watch_mv_prm.ang_accel_x - deflt_watch_mv_prm.ang_accel_x, self_view_eff_rate, Q12_SHIFT) +
                                     deflt_watch_mv_prm.ang_accel_x;

        vcWatchMvPrmSt.ang_accel_y = Math_MulFixed(self_view_watch_mv_prm.ang_accel_y - deflt_watch_mv_prm.ang_accel_y, self_view_eff_rate, Q12_SHIFT) +
                                     deflt_watch_mv_prm.ang_accel_y;

        vcWatchMvPrmSt.max_ang_spd_x = deflt_watch_mv_prm.max_ang_spd_x +
                                       Math_MulFixed(self_view_watch_mv_prm.max_ang_spd_x - deflt_watch_mv_prm.max_ang_spd_x, self_view_eff_rate, Q12_SHIFT);

        vcWatchMvPrmSt.max_ang_spd_y = deflt_watch_mv_prm.max_ang_spd_y +
                                       Math_MulFixed(self_view_watch_mv_prm.max_ang_spd_y - deflt_watch_mv_prm.max_ang_spd_y, self_view_eff_rate, Q12_SHIFT);

        *watch_mv_prm_pp = &vcWatchMvPrmSt;

        add_ang_accel_y = FP_FROM((s64)w_p->chara_mv_spd_13C * FP_ANGLE(360.0f), Q12_SHIFT);
        add_ang_accel_y = CLAMP(add_ang_accel_y, 0, FP_ANGLE(720.0f));

        vcWatchMvPrmSt.ang_accel_y += add_ang_accel_y;
    }

    cam_mv_prm_stg_p = (w_p->flags_8 & VC_USER_CAM_F) ? &w_p->user_cam_mv_prm_34 : &cam_mv_prm_user;
    *cam_mv_prm_pp   = cam_mv_prm_stg_p;
}

void vcRenewalCamData(VC_WORK* w_p, VC_CAM_MV_PARAM* cam_mv_prm_p) // 0x80084BD8
{
    s32 dec_spd_per_dist_xz;
    s32 dec_spd_per_dist_y;

    if (w_p->flags_8 & VC_WARP_CAM_F)
    {
        w_p->cam_mv_ang_y_5C = ratan2(w_p->cam_tgt_pos_44.vx - w_p->cam_pos_50.vx, w_p->cam_tgt_pos_44.vz - w_p->cam_pos_50.vz);
        w_p->cam_pos_50      = w_p->cam_tgt_pos_44;
        w_p->cam_velo_60.vx  = 0;
        w_p->cam_velo_60.vy  = 0;
        w_p->cam_velo_60.vz  = 0;
        return;
    }

    // SH2 removes this multiply and uses `accel_y` directly. Maybe 0.4f/1.0f were tunable defines and compiler removed it.
    dec_spd_per_dist_xz = FP_MULTIPLY_PRECISE(cam_mv_prm_p->accel_xz, 0.4f, Q12_SHIFT);
    dec_spd_per_dist_y  = FP_MULTIPLY_PRECISE(cam_mv_prm_p->accel_y,  1.0f, Q12_SHIFT);

    vwRenewalXZVelocityToTargetPos(&w_p->cam_velo_60.vx, &w_p->cam_velo_60.vz, &w_p->cam_pos_50,
                                   &w_p->cam_tgt_pos_44, FP_METER(0.1f), cam_mv_prm_p->accel_xz,
                                   cam_mv_prm_p->max_spd_xz, dec_spd_per_dist_xz, FP_TO(12, Q12_SHIFT));

    w_p->cam_velo_60.vy  = vwRetNewVelocityToTargetVal(w_p->cam_velo_60.vy, w_p->cam_pos_50.vy, w_p->cam_tgt_pos_44.vy,
                                                       cam_mv_prm_p->accel_y, cam_mv_prm_p->max_spd_y, dec_spd_per_dist_y);
    w_p->cam_mv_ang_y_5C = ratan2(w_p->cam_velo_60.vx, w_p->cam_velo_60.vz);

    w_p->cam_pos_50.vx += Math_MulFixed(w_p->cam_velo_60.vx, g_DeltaTime0, Q12_SHIFT);
    w_p->cam_pos_50.vy += Math_MulFixed(w_p->cam_velo_60.vy, g_DeltaTime0, Q12_SHIFT);
    w_p->cam_pos_50.vz += Math_MulFixed(w_p->cam_velo_60.vz, g_DeltaTime0, Q12_SHIFT);
}

void vcRenewalCamMatAng(VC_WORK* w_p, VC_WATCH_MV_PARAM* watch_mv_prm_p, VC_CAM_MV_TYPE cam_mv_type, s32 visible_chara_f) // 0x80084D54
{
    SVECTOR ofs_tgt_ang;
    SVECTOR new_base_cam_ang;
    MATRIX  new_base_matT;
    SVECTOR ofs_cam2chara_btm_ang;
    SVECTOR ofs_cam2chara_top_ang;

    vcMakeNewBaseCamAng(&new_base_cam_ang, cam_mv_type, w_p);
    if (new_base_cam_ang.vx != w_p->base_cam_ang_C8.vx ||
        new_base_cam_ang.vy != w_p->base_cam_ang_C8.vy ||
        new_base_cam_ang.vz != w_p->base_cam_ang_C8.vz)
    {
        vcRenewalBaseCamAngAndAdjustOfsCamAng(w_p, &new_base_cam_ang);
    }

    func_80096C94(&w_p->base_cam_ang_C8, &new_base_matT);
    TransposeMatrix(&new_base_matT, &new_base_matT);
    vcMakeOfsCamTgtAng(&ofs_tgt_ang, &new_base_matT, w_p);
    if (visible_chara_f != 0)
    {
        vcMakeOfsCam2CharaBottomAndTopAngByBaseMatT(&ofs_cam2chara_btm_ang, &ofs_cam2chara_top_ang, &new_base_matT,
                                                    &w_p->cam_pos_50, &w_p->chara_pos_114, w_p->chara_bottom_y_120,
                                                    w_p->chara_top_y_124);
        vcAdjCamOfsAngByCharaInScreen(&ofs_tgt_ang, &ofs_cam2chara_btm_ang, &ofs_cam2chara_top_ang, w_p);
    }

    if (w_p->flags_8 & VC_WARP_WATCH_F)
    {
        w_p->ofs_cam_ang_B8        = ofs_tgt_ang;
        w_p->ofs_cam_ang_spd_C0.vx = 0;
        w_p->ofs_cam_ang_spd_C0.vy = 0;
        w_p->ofs_cam_ang_spd_C0.vz = 0;
    }
    else
    {
        vcAdjCamOfsAngByOfsAngSpd(&w_p->ofs_cam_ang_B8, &w_p->ofs_cam_ang_spd_C0, &ofs_tgt_ang, watch_mv_prm_p);
    }

    vcMakeCamMatAndCamAngByBaseAngAndOfsAng(&w_p->cam_mat_ang_8E, &w_p->cam_mat_98, &new_base_cam_ang, &w_p->ofs_cam_ang_B8, &w_p->cam_pos_50);
}

void vcMakeNewBaseCamAng(SVECTOR* new_base_ang, VC_CAM_MV_TYPE cam_mv_type, VC_WORK* w_p) // 0x80084EDC
{
    static const s32 D_8002AAE0[] = { 0, 170, 682, 1251, 1251, 0, 0 }; // Last 2 could be compiler-added padding, but is needed for match.

    s32        sp18[5];
    s16        temp_a0_3;
    s16        temp_v0;
    s16        new_base_ang_x;
    s16        new_base_ang_y;
    s16        var_v1_2;
    s16        temp_a0_2;
    s16        angle;
    s16        temp_t0;
    s16        temp_v0_2;
    s16        temp_v1;
    s16        temp_v1_2;
    s32        zDelta;
    s32        yDelta;
    s32        xDelta;

    xDelta = FP_FROM(w_p->watch_tgt_pos_7C.vx - w_p->cam_pos_50.vx, Q4_SHIFT);
    yDelta = FP_FROM(w_p->watch_tgt_pos_7C.vy - w_p->cam_pos_50.vy, Q4_SHIFT);
    zDelta = FP_FROM(w_p->watch_tgt_pos_7C.vz - w_p->cam_pos_50.vz, Q4_SHIFT);

    if (w_p->flags_8 & VC_USER_WATCH_F)
    {
        new_base_ang->vx = 0;
        new_base_ang->vy = 0;
        new_base_ang->vz = 0;
    }
    else if (cam_mv_type != VC_MV_SETTLE)
    {
        new_base_ang->vx = 0;
        new_base_ang->vy = 0;
        new_base_ang->vz = 0;
    }
    else
    {
        angle   = ratan2(-yDelta, Vc_VectorMagnitudeCalc(xDelta, 0, zDelta));
        temp_v0 = ratan2(xDelta, zDelta);

        temp_v1   = FP_TO(w_p->cur_near_road_2B8.road_p_0->fix_ang_x_16, Q4_SHIFT);
        temp_a0_2 = FP_TO(w_p->cur_near_road_2B8.road_p_0->fix_ang_y_17, Q4_SHIFT);

        temp_v1_2 = ((temp_v0 - temp_v1)   << 20) >> 20;
        temp_v0_2 = ((temp_v0 - temp_a0_2) << 20) >> 20;

        if (temp_v1_2 >= 0 && temp_v0_2 <= 0)
        {
            new_base_ang_y = temp_v0;
        }
        else if (ABS(temp_v1_2) < ABS(temp_v0_2))
        {
            new_base_ang_y = temp_v1;
        }
        else
        {
            new_base_ang_y = temp_a0_2;
        }

        if (!(w_p->flags_8 & VC_WARP_WATCH_F))
        {
            if (w_p->chara_mv_spd_13C != 0 && angle < FP_ANGLE(75.0f) && angle >= FP_ANGLE(-74.9f))
            {
                temp_t0        = ((new_base_ang_y - w_p->base_cam_ang_C8.vy) << 20) >> 20;
                temp_a0_3      = FP_MULTIPLY((s64)g_DeltaTime0, FP_ANGLE(120.0f), Q12_SHIFT);
                var_v1_2       = CLAMP(temp_t0, -temp_a0_3, temp_a0_3);
                new_base_ang_y = w_p->base_cam_ang_C8.vy + var_v1_2;
            }
            else
            {
                new_base_ang_y = w_p->base_cam_ang_C8.vy;
            }
        }

        new_base_ang_x = angle;
        if (new_base_ang_x < 0)
        {
            new_base_ang_x = -new_base_ang_x;
        }

        memcpy(sp18, D_8002AAE0, 5 * sizeof(s32));
        new_base_ang_x = vwOresenHokan(sp18, 5, new_base_ang_x, 0, FP_METER(0.25f));
        new_base_ang_x = CLAMP(new_base_ang_x, 0, FP_ANGLE(90.0f));

        if (angle < 0)
        {
            new_base_ang_x = -new_base_ang_x;
        }

        new_base_ang->vx = new_base_ang_x;
        new_base_ang->vy = new_base_ang_y;
        new_base_ang->vz = 0;
    }
}

void vcRenewalBaseCamAngAndAdjustOfsCamAng(VC_WORK* w_p, SVECTOR* new_base_cam_ang) // 0x800851B0
{
    MATRIX old_base_mat;
    MATRIX new_base_mat;
    MATRIX new_base_matT;

    // Names for these two might be switched.
    MATRIX ofs_mat;
    MATRIX adj_ofs_mat;

    ofs_mat = GsIDMATRIX;
    func_80096C94(&w_p->base_cam_ang_C8, &old_base_mat);
    func_80096C94(new_base_cam_ang, &new_base_mat);
    TransposeMatrix(&new_base_mat, &new_base_matT);
    func_80096C94(&w_p->ofs_cam_ang_B8, &adj_ofs_mat);
    MulMatrix0(&new_base_matT, &old_base_mat, &ofs_mat);
    MulMatrix2(&ofs_mat, &adj_ofs_mat);
    vwMatrixToAngleYXZ(&w_p->ofs_cam_ang_B8, &adj_ofs_mat);
    w_p->base_cam_ang_C8 = *new_base_cam_ang;
}

void vcMakeOfsCamTgtAng(SVECTOR* ofs_tgt_ang, MATRIX* base_matT, VC_WORK* w_p) // 0x800852C8
{
    SVECTOR vec;

    vec.vx = FP_FROM(w_p->watch_tgt_pos_7C.vx - w_p->cam_pos_50.vx, Q4_SHIFT);
    vec.vy = FP_FROM(w_p->watch_tgt_pos_7C.vy - w_p->cam_pos_50.vy, Q4_SHIFT);
    vec.vz = FP_FROM(w_p->watch_tgt_pos_7C.vz - w_p->cam_pos_50.vz, Q4_SHIFT);

    ApplyMatrixSV(base_matT, &vec, &vec);
    vwVectorToAngle(ofs_tgt_ang, &vec);
    ofs_tgt_ang->vz = w_p->watch_tgt_ang_z_8C;
}

void vcMakeOfsCam2CharaBottomAndTopAngByBaseMatT(SVECTOR* ofs_cam2chara_btm_ang, SVECTOR* ofs_cam2chara_top_ang,
                                                 MATRIX* base_matT, VECTOR3* cam_pos, VECTOR3* chara_pos,
                                                 s32 chara_bottom_y, s32 chara_top_y) // 0x80085358
{
    SVECTOR vec;

    vec.vx = FP_FROM(chara_pos->vx  - cam_pos->vx, Q4_SHIFT);
    vec.vy = FP_FROM(chara_bottom_y - cam_pos->vy, Q4_SHIFT);
    vec.vz = FP_FROM(chara_pos->vz  - cam_pos->vz, Q4_SHIFT);
    ApplyMatrixSV(base_matT, &vec, &vec);
    vwVectorToAngle(ofs_cam2chara_btm_ang, &vec);

    vec.vx = FP_FROM(chara_pos->vx - cam_pos->vx, Q4_SHIFT);
    vec.vy = FP_FROM(chara_top_y   - cam_pos->vy, Q4_SHIFT);
    vec.vz = FP_FROM(chara_pos->vz - cam_pos->vz, Q4_SHIFT);
    ApplyMatrixSV(base_matT, &vec, &vec);
    vwVectorToAngle(ofs_cam2chara_top_ang, &vec);
}

void vcAdjCamOfsAngByCharaInScreen(SVECTOR* cam_ang, SVECTOR* ofs_cam2chara_btm_ang, SVECTOR* ofs_cam2chara_top_ang, VC_WORK* w_p) // 0x80085460
{
    // SH2 dwarf names.
    s16 adj_cam_ang_x;
    s16 var_a1; // Probably temp for `adj_cam_ang_x`.
    s16 watch2chr_ofs_ang_y;
    s16 watch2chr_bottom_ofs_ang_x;
    s16 watch2chr_top_ofs_ang_x;
    s16 adj_cam_ang_y;

    watch2chr_bottom_ofs_ang_x = shAngleRegulate(ofs_cam2chara_btm_ang->vx - cam_ang->vx);
    watch2chr_top_ofs_ang_x    = shAngleRegulate(ofs_cam2chara_top_ang->vx - cam_ang->vx);
    watch2chr_ofs_ang_y        = shAngleRegulate(ofs_cam2chara_top_ang->vy - cam_ang->vy);

    adj_cam_ang_y = (watch2chr_ofs_ang_y > w_p->scr_half_ang_wx_2E) ?
                    (watch2chr_ofs_ang_y - w_p->scr_half_ang_wx_2E) :
                    ((-w_p->scr_half_ang_wx_2E > watch2chr_ofs_ang_y) ? (w_p->scr_half_ang_wx_2E + watch2chr_ofs_ang_y) : 0);

    /*
    var_a1 = watch2chr_bottom_ofs_ang_x + w_p->scr_half_ang_wy_2C;
    if (watch2chr_bottom_ofs_ang_x >= -w_p->scr_half_ang_wy_2C)
    {
        var_a1 = 0;
    }*/

    // TODO: var_a1 should probably be merged into adj_cam_ang_x somehow.
    var_a1 = (watch2chr_bottom_ofs_ang_x >= -w_p->scr_half_ang_wy_2C) ? 0 : (watch2chr_bottom_ofs_ang_x + w_p->scr_half_ang_wy_2C);

    if (w_p->scr_half_ang_wy_2C < (watch2chr_top_ofs_ang_x - var_a1))
    {
        var_a1 = watch2chr_top_ofs_ang_x - w_p->scr_half_ang_wy_2C;
    }

    if (var_a1 < FP_ANGLE(-30.0f))
    {
        adj_cam_ang_x = FP_ANGLE(-30.0f);
    }
    else
    {
        adj_cam_ang_x = var_a1;
        if (var_a1 > FP_ANGLE(30.0f))
        {
            adj_cam_ang_x = FP_ANGLE(30.0f);
        }
    }

    cam_ang->vy += adj_cam_ang_y;
    cam_ang->vx = adj_cam_ang_x + cam_ang->vx;
}

void vcAdjCamOfsAngByOfsAngSpd(SVECTOR* ofs_ang, SVECTOR* ofs_ang_spd, SVECTOR* ofs_tgt_ang, VC_WATCH_MV_PARAM* prm_p) // 0x8008555C
{
    SVECTOR unused;
    VECTOR3 max_spd_dec_per_dist;

    unused.vx = shAngleRegulate(ofs_tgt_ang->vx - ofs_ang->vx);
    unused.vy = shAngleRegulate(ofs_tgt_ang->vy - ofs_ang->vy);
    unused.vz = shAngleRegulate(ofs_tgt_ang->vz - ofs_ang->vz);

    max_spd_dec_per_dist.vx = FP_MULTIPLY_PRECISE(prm_p->ang_accel_x, 8.0f, Q12_SHIFT);
    max_spd_dec_per_dist.vy = FP_MULTIPLY_PRECISE(prm_p->ang_accel_y, 3.0f, Q12_SHIFT);
    max_spd_dec_per_dist.vz = FP_MULTIPLY_PRECISE(prm_p->ang_accel_y, 3.3f, Q12_SHIFT);

    ofs_ang_spd->vx = vwRetNewAngSpdToTargetAng(ofs_ang_spd->vx, ofs_ang->vx, ofs_tgt_ang->vx, prm_p->ang_accel_x, prm_p->max_ang_spd_x, max_spd_dec_per_dist.vx);
    ofs_ang_spd->vy = vwRetNewAngSpdToTargetAng(ofs_ang_spd->vy, ofs_ang->vy, ofs_tgt_ang->vy, prm_p->ang_accel_y, prm_p->max_ang_spd_y, max_spd_dec_per_dist.vy);
    ofs_ang_spd->vz = vwRetNewAngSpdToTargetAng(ofs_ang_spd->vz, ofs_ang->vz, ofs_tgt_ang->vz, FP_METER(0.4f), FP_ANGLE(144.0f), FP_METER(3.0f));

    ofs_ang->vx += FP_MULTIPLY(ofs_ang_spd->vx, (s64)g_DeltaTime0, Q12_SHIFT);
    ofs_ang->vy += FP_MULTIPLY(ofs_ang_spd->vy, (s64)g_DeltaTime0, Q12_SHIFT);
    ofs_ang->vz += FP_MULTIPLY(ofs_ang_spd->vz, (s64)g_DeltaTime0, Q12_SHIFT);
}

void vcMakeCamMatAndCamAngByBaseAngAndOfsAng(SVECTOR* cam_mat_ang, MATRIX* cam_mat, SVECTOR* base_cam_ang, SVECTOR* ofs_cam_ang, VECTOR3* cam_pos) // 0x800857EC
{
    MATRIX base_mat;
    MATRIX ofs_mat;

    cam_mat->t[0] = FP_FROM(cam_pos->vx, Q4_SHIFT);
    cam_mat->t[1] = FP_FROM(cam_pos->vy, Q4_SHIFT);
    cam_mat->t[2] = FP_FROM(cam_pos->vz, Q4_SHIFT);

    func_80096C94(base_cam_ang, &base_mat);
    func_80096C94(ofs_cam_ang, &ofs_mat);
    MulMatrix0(&base_mat, &ofs_mat, cam_mat);
    vwMatrixToAngleYXZ(cam_mat_ang, cam_mat);
}

void vcSetDataToVwSystem(VC_WORK* w_p, VC_CAM_MV_TYPE cam_mv_type) // 0x80085884
{
    MATRIX  noise_cam_mat;
    MATRIX  noise_mat;
    SVECTOR noise_ang;

    if (w_p->field_D8 != 0)
    {
        w_p->field_D8 = 0;
        vwSetCoordRefAndEntou(&g_SysWork.playerBoneCoords_890[PlayerBone_Head],
                              0, FP_METER(-0.05f), FP_METER(0.3f),
                              FP_ANGLE(180.0f), FP_ANGLE(0.0f), FP_METER(-0.2f), FP_METER(1.0f));
    }
    else if (w_p->field_FC != 0)
    {
        w_p->field_FC = 0;
        vwSetViewInfoDirectMatrix(NULL, &w_p->field_DC);
    }
    else if (cam_mv_type == VC_MV_SELF_VIEW)
    {
        vcSelfViewTimer += g_DeltaTime0;

        noise_ang.vx = vcCamMatNoise(4, FP_RADIAN((PI / 18.0f) * 5.0f), FP_RADIAN((PI / 9.0f) *  4.0f), vcSelfViewTimer); // Noise: 0.0034906585f
        noise_ang.vy = vcCamMatNoise(2, FP_RADIAN((PI / 9.0f)  * 2.0f), FP_RADIAN((PI / 9.0f) * -8.0f), vcSelfViewTimer); // Noise: 0.0021816615f
        noise_ang.vz = 0;
        func_80096C94(&noise_ang, &noise_mat);

        noise_mat.m[0][0] += vcCamMatNoise(12, FP_RADIAN((PI / 18.0f) * 7.0f),  FP_RADIAN(PI),                    vcSelfViewTimer); // Noise: 0.004f
        noise_mat.m[0][1] += vcCamMatNoise(12, FP_RADIAN(PI / 3.0f),            FP_RADIAN((PI / 9.0f)  * -8.0f),  vcSelfViewTimer); // Noise: 0.004f
        noise_mat.m[0][2] += vcCamMatNoise(12, FP_RADIAN(PI / 3.0f),            FP_RADIAN((PI / 9.0f)  *  4.0f),  vcSelfViewTimer); // Noise: 0.004f
        noise_mat.m[1][0] += vcCamMatNoise(12, FP_RADIAN((PI / 18.0f) * 5.0f),  FP_RADIAN((PI / 18.0f) *  5.0f),  vcSelfViewTimer); // Noise: 0.004f
        noise_mat.m[1][1] += vcCamMatNoise(12, FP_RADIAN(PI),                   FP_RADIAN((PI / 9.0f)  *  2.0f),  vcSelfViewTimer); // Noise: 0.004f
        noise_mat.m[1][2] += vcCamMatNoise(12, FP_RADIAN((PI / 36.0f) * 13.0f), FP_RADIAN((PI / 18.0f) * -17.0f), vcSelfViewTimer); // Noise: 0.004f
        MulMatrix0(&w_p->cam_mat_98, &noise_mat, &noise_cam_mat);

        noise_cam_mat.t[0] = w_p->cam_mat_98.t[0];
        noise_cam_mat.t[1] = w_p->cam_mat_98.t[1];
        noise_cam_mat.t[2] = w_p->cam_mat_98.t[2];
        vwSetViewInfoDirectMatrix(NULL, &noise_cam_mat);
    }
    else
    {
        vwSetViewInfoDirectMatrix(NULL, &w_p->cam_mat_98);
    }
}

s32 vcCamMatNoise(s32 noise_w, s32 ang_spd1, s32 ang_spd2, s32 vcSelfViewTimer) // 0x80085A7C
{
    s32 noise;

    noise = shRcos(FP_MULTIPLY(ang_spd1, (s64)vcSelfViewTimer, Q12_SHIFT)) + shRcos(FP_MULTIPLY(ang_spd2, (s64)vcSelfViewTimer, Q12_SHIFT));
    noise = noise >> 1;

    return FP_MULTIPLY(noise_w, noise, Q12_SHIFT);
}

s32 Vc_VectorMagnitudeCalc(s32 x, s32 y, s32 z) // 0x80085B1C
{
    s32 mag;
    s32 shift;

    mag   = MAX(MAX(ABS(x), ABS(y)), ABS(z));
    shift = Math_GetMagnitudeShift(mag);
    x >>= shift;
    y >>= shift;
    z >>= shift;
    return SquareRoot0(SQUARE(x) + SQUARE(y) + SQUARE(z)) << shift;
}

s32 vcGetXZSumDistFromLimArea(s32* out_vec_x_p, s32* out_vec_z_p, s32 chk_wld_x, s32 chk_wld_z,
                              s32 lim_min_x, s32 lim_max_x, s32 lim_min_z, s32 lim_max_z, s32 can_ret_minus_dist_f) // 0x80085C80
{
    s32 cntr_x;
    s32 cntr_z;
    s32 x_dist;
    s32 z_dist;
    s32 ret_dist;

    if (lim_max_x < chk_wld_x)
    {
        cntr_x       = lim_max_x - chk_wld_x;
        *out_vec_x_p = cntr_x;
        x_dist       = -cntr_x;
    }
    else if (chk_wld_x < lim_min_x)
    {
        x_dist       = lim_min_x - chk_wld_x;
        *out_vec_x_p = x_dist;
    }
    else
    {
        *out_vec_x_p = 0;
        if (chk_wld_x >= ((lim_max_x + lim_min_x) >> 1))
        {
            x_dist = chk_wld_x - lim_max_x;
        }
        else
        {
            x_dist = lim_min_x - chk_wld_x;
        }
    }

    if (lim_max_z < chk_wld_z)
    {
        cntr_z       = lim_max_z - chk_wld_z;
        *out_vec_z_p = cntr_z;
        z_dist       = -cntr_z;
    }
    else if (chk_wld_z < lim_min_z)
    {
        z_dist       = lim_min_z - chk_wld_z;
        *out_vec_z_p = z_dist;
    }
    else
    {
        *out_vec_z_p = 0;
        if (chk_wld_z >= ((lim_max_z + lim_min_z) >> 1))
        {
            z_dist = chk_wld_z - lim_max_z;
        }
        else
        {
            z_dist = lim_min_z - chk_wld_z;
        }
    }

    if (x_dist >= 0)
    {
        ret_dist = x_dist;
        if (z_dist >= 0)
        {
            ret_dist += z_dist;
        }
    }
    else
    {
        ret_dist = z_dist;
        if (ret_dist < 0 && ret_dist < x_dist)
        {
            ret_dist = x_dist;
        }
    }

    if (can_ret_minus_dist_f == 0 && ret_dist < 0)
    {
        ret_dist = 0;
    }

    return ret_dist;
}
