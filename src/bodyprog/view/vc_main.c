#include "game.h"

#include "bodyprog/vw_system.h"
#include "bodyprog/math.h"

#define MIN_IN_ROAD_DIST FP_METER(16.0f) // vcGetMinInRoadDist() in SH2, hardcoded to FP_METER(16.0f) in SH1.

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

    vcWork_CurNearRoadSet(&vcWork, &vcNullNearRoad);

    vcWork.old_cam_excl_area_r_6C = NO_VALUE;
    vcWork.watch_tgt_max_y_88     = FP_METER(480.0f);
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

    vcWork_CurNearRoadSet(&vcWork, &vcNullNearRoad);

    vcWork.through_door_activate_init_f_C = use_through_door_cam_f;
    vcSetTHROUGH_DOOR_CAM_PARAM_in_VC_WORK(&vcWork, VC_TDSC_END);
}

void func_80080B58(GsCOORDINATE2* a1, SVECTOR* a2, VECTOR3* a3) // 0x80080B58
{
    MATRIX mat;

    vcWork.field_FC = 1;

    func_80049984(a1, &vcWork.field_DC);
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

s32 func_80080C18(s32 lookAtAngleYMax) // 0x80080C18
{
    s32 prev_val              = vcWork.watch_tgt_max_y_88;
    vcWork.watch_tgt_max_y_88 = lookAtAngleYMax;
    return prev_val;
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

    r = Math_VectorMagnitude(vcWork.cam_pos_50.vx - vcWork.watch_tgt_pos_7C.vx,
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
    far_watch_rate     = vcRetFarWatchRate(((vcWork.flags_8 >> 9) & (1 << 0)) ^ (g_GameWorkPtr0->config_0.optViewCtrl_28 != 0), cur_cam_mv_type, &vcWork);
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
    #define MOVEMENT_MAX_METER 0.2f
    #define ROT_X_MAX_ANGLE 20.0f
    #define ROT_Y_MAX_ANGLE 30.0f
    #define INTRPT_MIN_TIME 1.0f
    #define INTRPT_MAX_TIME 4.0f

    s32 intrpt; // Interpolation time (i.e. alpha)?
    s32 mv_vec;
    s32 rot_x;
    s32 rot_y;

    intrpt = FP_TO(g_DeltaTime0, Q12_SHIFT) / FP_FLOAT_TO(1.0f / TICKS_PER_SECOND, Q12_SHIFT);
    intrpt = CLAMP(intrpt, FP_FLOAT_TO(INTRPT_MIN_TIME, Q12_SHIFT), FP_FLOAT_TO(INTRPT_MAX_TIME, Q12_SHIFT));

    mv_vec = Math_VectorMagnitude(FP_FROM(now_pos->vx - old_pos->vx, Q4_SHIFT),
                                  FP_FROM(now_pos->vy - old_pos->vy, Q4_SHIFT),
                                  FP_FROM(now_pos->vz - old_pos->vz, Q4_SHIFT));

    mv_vec = FP_TO(mv_vec, Q12_SHIFT) / intrpt;
    if (mv_vec > FP_METER(MOVEMENT_MAX_METER))
    {
        return 0;
    }

    rot_x = FP_TO(((now_ang->vx - old_ang->vx) >= 0) ? (now_ang->vx - old_ang->vx) : (old_ang->vx - now_ang->vx), Q12_SHIFT) / intrpt;
    if (rot_x > FP_ANGLE(ROT_X_MAX_ANGLE))
    {
        return 0;
    }

    rot_y = FP_TO(abs(shAngleRegulate(now_ang->vy - old_ang->vy)), Q12_SHIFT) / intrpt;

    // This (guessed) line is needed for regalloc match, but compiler just optimizes out since rot_x isn't used afterward.
    // BUG: Maybe the shRcos call below was meant to use the result of this, but was somehow left using now_ang->vx?
    rot_x = ((now_ang->vx - old_ang->vx) >= 0) ? now_ang->vx : old_ang->vx;

    rot_y = FP_MULTIPLY(rot_y, shRcos(now_ang->vx), Q12_SHIFT);
    return rot_y <= FP_ANGLE(ROT_Y_MAX_ANGLE);
}

VC_CAM_MV_TYPE vcRetCurCamMvType(VC_WORK* w_p) // 0x80081428
{
    s32 hasViewFlag;

    if (g_GameWorkPtr0->config_0.optViewMode_29 != 0)
    {
        hasViewFlag = (vcWork.flags_8 & VC_PRS_F_VIEW_F) == VC_PRS_F_VIEW_F;

        // TODO: Can this weird XOR be removed? (XOR 1) should be same as `hasViewFlag == 0`?
        if ((g_GameWorkPtr0->config_0.optViewCtrl_28 && (hasViewFlag ^ 1) != 0) ||
            (!g_GameWorkPtr0->config_0.optViewCtrl_28 && hasViewFlag))
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
            if ((posX - FP_METER(3228.8f)) > (u32)FP_METER(451.205f))
            {
                return 0;
            }
            else if (posZ < -FP_METER(1472.0f))
            {
                return 0;
            }
            else if (posZ <= -FP_METER(1088.0f))
            {
                return 1;
            }

            break;
        case 3:
            if ((posX + FP_METER(3680.0f)) > (u32)FP_METER(464.0f))
            {
                return 0;
            }
            else if (posZ < -FP_METER(192.0f))
            {
                return 0;
            }
            else if (posZ <= FP_METER(192.0f))
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
    if (prm_p->timer_4 > FP_METER(19.2f) && w_p->nearest_enemy_xz_dist_2E0 < FP_METER(19.2f))
    {
        return 1;
    }

    if (rail2chara_dist > FP_METER(36.8f))
    {
        return 1;
    }

    if (rail2chara_dist > FP_METER(8.0f))
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
                far_watch_rate = FP_METER(16.0f); // FP_ANGLE(256.0f);
                if (!far_watch_button_prs_f)
                {
                    // TODO: unsure if these should use FP_METER or FP_ANGLE
                    // gets multiplied by `dist` so FP_METER fits
                    // but then it gets subtracted by `abs_ofs_ang_y`, so FP_ANGLE would also fit?

                    dist           = w_p->through_door_10.rail_sta_to_chara_dist_18;
                    far_watch_rate = FP_METER(14.4f) - ((dist * FP_METER(14.4f)) / FP_METER(36.8f));
                    // far_watch_rate = FP_ANGLE(324.0f) - ((dist * FP_ANGLE(324.0f)) / FP_ANGLE(828.0f));
                    if (far_watch_rate < 0)
                    {
                        far_watch_rate = 0;
                    }

                    if (dist > FP_METER(8.0f))
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

                        far_watch_rate = (far_watch_rate * (FP_METER(3.11f) - abs_ofs_ang_y)) / FP_METER(3.11f);
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

    if (g_GameWorkPtr0->config_0.optViewMode_29 != 0)
    {
        prsFViewFlag = vcWork.flags_8 >> 9; /** `VC_PRS_F_VIEW_F` */
        prsFViewFlag = prsFViewFlag & (1 << 0);

        if ((g_GameWorkPtr0->config_0.optViewCtrl_28 != 0 && (prsFViewFlag ^ 1) != 0) ||
            (g_GameWorkPtr0->config_0.optViewCtrl_28 == 0 && prsFViewFlag != 0))
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

    cam_max_rate = (cur_cam_mv_type == VC_MV_SELF_VIEW) ? FP_METER(16.0f) : FP_METER(5.6f);

    xyz_dist = Math_VectorMagnitude(FP_FROM(w_p->cam_pos_50.vx - w_p->chara_head_pos_130.vx, Q4_SHIFT),
                                    FP_FROM(w_p->cam_pos_50.vy - w_p->chara_head_pos_130.vy, Q4_SHIFT),
                                    FP_FROM(w_p->cam_pos_50.vz - w_p->chara_head_pos_130.vz, Q4_SHIFT));

    if (xyz_dist >= FP_METER(0.5f))
    {
        if (xyz_dist > FP_METER(1.2f))
        {
            max_rate = 0;
        }
        else
        {
            max_rate = (cam_max_rate * (FP_METER(1.2f) - xyz_dist)) / FP_METER(0.7f);
        }
    }
    else
    {
        max_rate = cam_max_rate;
    }

    if (w_p->nearest_enemy_xz_dist_2E0 > FP_METER(64.0f))
    {
        mul_rate = FP_METER(16.0f);
    }
    else
    {
        if (w_p->nearest_enemy_xz_dist_2E0 < FP_METER(32.0f))
        {
            mul_rate = 0;
        }
        else
        {
            mul_rate = (w_p->nearest_enemy_xz_dist_2E0 - FP_METER(32.0f)) / 2;
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
                vcWork_FlagSet(VC_VISIBLE_CHARA_F);
                break;

            case VC_MV_SETTLE:
                vcWork_FlagSet(VC_VISIBLE_CHARA_F);
                break;

            case VC_MV_FIX_ANG:
                vcWork_FlagClear(VC_VISIBLE_CHARA_F);
                break;

            case VC_MV_SELF_VIEW:
                vcWork_FlagClear(VC_VISIBLE_CHARA_F);
                break;

            case VC_MV_THROUGH_DOOR:
                vcWork_FlagClear(VC_VISIBLE_CHARA_F);
                break;
        }
    }
    else
    {
        vcWork_FlagClear(VC_VISIBLE_CHARA_F);
    }

    if (cam_mv_type == VC_MV_SELF_VIEW)
    {
        vcWork_FlagSet(VC_WARP_CAM_F | VC_WARP_CAM_TGT_F);

        vcPrsFViewFlag = (vcWork.flags_8 >> 9); /** `VC_PRS_F_VIEW_F` */
        vcPrsFViewFlag = vcPrsFViewFlag & 1;

        // optViewCtrl != 0 && vcPrsFViewFlag == 0 OR
        // optViewCtrl == 0 && vcPrsFViewFlag == 1
        if ((g_GameWorkPtr0->config_0.optViewCtrl_28 != 0 && (vcPrsFViewFlag ^ 1) != 0) ||
            (g_GameWorkPtr0->config_0.optViewCtrl_28 == 0 && vcPrsFViewFlag != 0))
        {
            vcOldPrsFViewFlag = (vcWork.flags_8 >> 10); /** `VC_OLD_PRS_F_VIEW_F` */
            vcOldPrsFViewFlag = vcOldPrsFViewFlag & (1 << 0);

            // (optViewCtrl != 0 && vcOldPrsFViewFlag == 0) == false AND
            // (optViewCtrl == 0 && vcOldPrsFViewFlag == 1) == false
            if (!(g_GameWorkPtr0->config_0.optViewCtrl_28 != 0 && (vcOldPrsFViewFlag ^ 1) != 0) &&
                !(g_GameWorkPtr0->config_0.optViewCtrl_28 == 0 && vcOldPrsFViewFlag != 0))
            {
                if (g_GameWorkPtr0->config_0.optViewMode_29 != 0)
                {
                    vcWork_FlagSet(VC_WARP_WATCH_F);
                }
            }
        }
    }

    if (all_warp_f != 0)
    {
        vcWork_FlagSet(VC_WARP_CAM_F | VC_WARP_WATCH_F | VC_WARP_CAM_TGT_F);
    }

    if (far_watch_rate != 0)
    {
        vcWork_FlagSet(VC_WARP_CAM_TGT_F);
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

        if (g_ControllerPtr0->btns_held_C & g_GameWorkPtr1->config_0.controllerBinds_0.view)
        {
            vcWork.flags_8 |= VC_PRS_F_VIEW_F;
        }
        else
        {
            vcWork.flags_8 &= ~VC_PRS_F_VIEW_F;
        }
    }

    vcWork.scr_half_ang_wx_2E = (s16)(ratan2(g_GameWork.gsScreenWidth_588, vcWork.geom_screen_dist_30) >> 1);
    vcWork.scr_half_ang_wy_2C = (s16)(ratan2(g_GameWork.gsScreenHeight_58A, vcWork.geom_screen_dist_30) >> 1);

    if (vcWork.through_door_activate_init_f_C != 0)
    {
        vcSetTHROUGH_DOOR_CAM_PARAM_in_VC_WORK(&vcWork, VC_TDSC_START);
    }

    vcSetTHROUGH_DOOR_CAM_PARAM_in_VC_WORK(&vcWork, VC_TDSC_MAIN);
    vcSetNearestEnemyDataInVC_WORK(w_p);
    vcSetNearRoadAryByCharaPos(w_p, vc_road_ary_list, FP_METER(320.0f), 0, w_p->nearest_enemy_p_2DC != NULL);
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
            prm_p->rail_sta_pos_C.vy        = w_p->chara_grnd_y_12C - FP_METER(31.2f);
            prm_p->rail_sta_pos_C.vz        = w_p->chara_pos_114.vz;
            break;

        case VC_TDSC_END:
            w_p->through_door_10.active_f_0 = 0;
            prm_p->timer_4                  = 0;
            break;

        case VC_TDSC_MAIN:
            if (w_p->through_door_10.active_f_0 != 0)
            {
                prm_p->rail_sta_to_chara_dist_18 = Math_VectorMagnitude(w_p->chara_pos_114.vx - w_p->through_door_10.rail_sta_pos_C.vx,
                                                                        0,
                                                                        w_p->chara_pos_114.vz - w_p->through_door_10.rail_sta_pos_C.vz);

                prm_p->timer_4 += g_DeltaTime0;
            }
            break;
    }
}

void vcSetNearestEnemyDataInVC_WORK(VC_WORK* w_p) // 0x80081D90
{
    #define ENEMY_MAX_DEAD_TIMER 1.5f
    #define ENEMY_MAX_DISTANCE 240.0f

    s32             set_active_data_f;
    s32             xz_dist;
    s32             ofs_x;
    s32             ofs_z;
    s_SubCharacter* sc_p            = NULL;
    s_SubCharacter* all_min_sc_p    = NULL;
    s_SubCharacter* active_min_sc_p = NULL;
    s32             all_min_dist    = FP_METER(ENEMY_MAX_DISTANCE);
    s32             active_min_dist = FP_METER(ENEMY_MAX_DISTANCE);

    if (g_SysWork.flags_22A4 & (1 << 5)) // sh2jms->player.battle(ShBattleInfo).status & 0x10 in SH2
    {
        w_p->nearest_enemy_p_2DC       = NULL;
        w_p->nearest_enemy_xz_dist_2E0 = FP_METER(ENEMY_MAX_DISTANCE);
        return;
    }

    for (sc_p = &g_SysWork.npcs_1A0[0]; sc_p < &g_SysWork.npcs_1A0[NPC_COUNT_MAX]; sc_p++)
    {
        if ((((u8)sc_p->model_0.charaId_0 - 2) < 0x17U) &&
            (sc_p->dead_timer_C4 <= FP_FLOAT_TO(ENEMY_MAX_DEAD_TIMER, Q12_SHIFT) || sc_p->health_B0 >= 0) &&
            !(sc_p->field_3E & (1 << 4))) // sc_p->battle(ShBattleInfo).status & 0x20 in SH2
        {
            ofs_x = sc_p->position_18.vx - w_p->chara_pos_114.vx;
            ofs_z = sc_p->position_18.vz - w_p->chara_pos_114.vz;

            if (abs(ofs_x) >= FP_METER(ENEMY_MAX_DISTANCE) || abs(ofs_z) >= FP_METER(ENEMY_MAX_DISTANCE))
            {
                continue;
            }

            xz_dist = Math_VectorMagnitude(ofs_x, 0, ofs_z);
            ratan2(ofs_x, ofs_z); // result unused?

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
                if (sc_p->field_3E & (1 << 1)) // sc_p->battle(ShBattleInfo).status & 4 in SH2
                {
                    set_active_data_f = 0;
                    if (sc_p == &g_SysWork.npcs_1A0[g_SysWork.field_2353])
                    {
                        set_active_data_f = g_SysWork.isPlayerInCombatMode_4B > 0;
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
        w_p->nearest_enemy_p_2DC       = active_min_sc_p;
        w_p->nearest_enemy_xz_dist_2E0 = active_min_dist;
    }
    else
    {
        w_p->nearest_enemy_p_2DC       = all_min_sc_p;
        w_p->nearest_enemy_xz_dist_2E0 = all_min_dist;
    }
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/view/vc_main", vcSetNearRoadAryByCharaPos);

s32 vcRetRoadUsePriority(VC_ROAD_TYPE rd_type) // 0x8008227C
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

INCLUDE_ASM("asm/bodyprog/nonmatchings/view/vc_main", vcSetCurNearRoadInVC_WORK);

INCLUDE_ASM("asm/bodyprog/nonmatchings/view/vc_main", vcGetBestNewCurNearRoad);

INCLUDE_ASM("asm/bodyprog/nonmatchings/view/vc_main", vcGetNearestNEAR_ROAD_DATA);

s32 vcAdvantageDistOfOldCurRoad(VC_NEAR_ROAD_DATA* old_cur_p) // 0x80082AD0
{
    switch ((s32)old_cur_p->road_p_0->rd_type_11)
    {
        case VC_RD_TYPE_ROAD:
        case VC_RD_TYPE_EFFECT:
        default:
            return FP_METER(5.6f);

        case VC_RD_TYPE_EVENT:
            return FP_METER(2.4f);
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

INCLUDE_ASM("asm/bodyprog/nonmatchings/view/vc_main", vcMakeNormalWatchTgtPos);

INCLUDE_ASM("asm/bodyprog/nonmatchings/view/vc_main", vcMixSelfViewEffectToWatchTgtPos);

INCLUDE_ASM("asm/bodyprog/nonmatchings/view/vc_main", vcMakeFarWatchTgtPos);

void vcSetWatchTgtXzPos(VECTOR3* watch_pos, VECTOR3* center_pos, VECTOR3* cam_pos, s32 tgt_chara2watch_cir_dist, s32 tgt_watch_cir_r, s16 watch_cir_ang_y) // 0x800834A8
{
    s16 cam2chr_ang;
    s32 chr2watch_x;
    s32 chr2watch_z;

    cam2chr_ang = ratan2(center_pos->vx - cam_pos->vx, center_pos->vz - cam_pos->vz);

    chr2watch_x = Math_MulFixed(tgt_chara2watch_cir_dist, shRsin(cam2chr_ang), Q12_SHIFT) +
                  Math_MulFixed(tgt_watch_cir_r, shRsin(watch_cir_ang_y), Q12_SHIFT);
    chr2watch_z = Math_MulFixed(tgt_chara2watch_cir_dist, shRcos(cam2chr_ang), Q12_SHIFT) +
                  Math_MulFixed(tgt_watch_cir_r, shRcos(watch_cir_ang_y), Q12_SHIFT);

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
    s16 max_cam_ang_x = ratan2(cam_pos->vy + FP_METER(80.0f), FP_METER(208.0f)) - ratan2(g_GameWork.gsScreenHeight_58A / 2, sy);
    s32 dist          = Math_VectorMagnitude(watch_pos->vx - cam_pos->vx, 0, watch_pos->vz - cam_pos->vz);
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
            vcMakeBasicCamTgtMvVec(&tgt_vec, &ideal_pos, w_p, FP_METER(16.0f));
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

        w_p->cam_tgt_spd_110 = Math_VectorMagnitude(w_p->cam_tgt_velo_100.vx, 0, w_p->cam_tgt_velo_100.vz);
        return;
    }

    w_p->cam_tgt_velo_100.vx = 0;
    w_p->cam_tgt_velo_100.vz = 0;
    w_p->cam_tgt_spd_110     = 0;
}

s32 vcRetMaxTgtMvXzLen(VC_WORK* w_p, VC_CAM_MV_PARAM* cam_mv_prm_p) // 0x8008395C
{
    s32 max_spd_xz;

    max_spd_xz = w_p->chara_mv_spd_13C + FP_METER(16.0f) + abs(w_p->chara_ang_spd_y_142 * 8);
    max_spd_xz = (max_spd_xz < FP_METER(35.2f)) ? FP_METER(35.2f) : max_spd_xz;
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

    if (g_GameWorkPtr0->config_0.optViewMode_29)
    {
        chara2cam_ang_y = w_p->chara_eye_ang_y_144 + FP_ANGLE(140.0f);
        ideal_pos->vy   = w_p->chara_head_pos_130.vy + FP_METER(1.12f);
    }
    else
    {
        chara2cam_ang_y = w_p->chara_eye_ang_y_144 + FP_ANGLE(170.0f);
        ideal_pos->vy   = w_p->chara_head_pos_130.vy + FP_METER(1.6f);
    }

    ideal_pos->vx = w_p->chara_head_pos_130.vx + FP_MULTIPLY(shRsin(chara2cam_ang_y), FP_ANGLE(64.8f), Q12_SHIFT);
    ideal_pos->vz = w_p->chara_head_pos_130.vz + FP_MULTIPLY(shRcos(chara2cam_ang_y), FP_ANGLE(64.8f), Q12_SHIFT);
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/view/vc_main", vcMakeIdealCamPosForFixAngCam);

INCLUDE_ASM("asm/bodyprog/nonmatchings/view/vc_main", vcMakeIdealCamPosForThroughDoorCam);

INCLUDE_ASM("asm/bodyprog/nonmatchings/view/vc_main", vcMakeIdealCamPosUseVC_ROAD_DATA);

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
    s32 temp_s0; // SH2: float xz_vec[4];
    s32 temp_s1;

    temp_s1 = ideal_pos->vx - w_p->cam_tgt_pos_44.vx;
    temp_s0 = ideal_pos->vz - w_p->cam_tgt_pos_44.vz;

    now2ideal_tgt_dist  = Math_VectorMagnitude(temp_s1, 0, temp_s0);
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

INCLUDE_ASM("asm/bodyprog/nonmatchings/view/vc_main", vcAdjTgtMvVecYByCurNearRoad);

void vcCamTgtMvVecIsFlipedFromCharaFront(VECTOR3* tgt_mv_vec, VC_WORK* w_p, s32 max_tgt_mv_xz_len, VC_AREA_SIZE_TYPE cur_rd_area_size)
{
    VECTOR3            pre_tgt_pos;
    VECTOR3            chk_pos;
    VECTOR3            post_tgt_pos;
    s16                flip_ang_y;
    VC_NEAR_ROAD_DATA* use_nearest_p;
    s16                ang_y;
    s32                flip_dist; // TODO: Name maybe switched with mv_len.
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
        if (flip_dist > FP_METER(8.0f))
        {
            mv_len = FP_METER(8.0f);
        }

        // chk_pos is unused?
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

        if (max_tgt_mv_xz_len < Math_VectorMagnitude(tgt_mv_vec->vx, 0, tgt_mv_vec->vz))
        {
            ang_y          = ratan2(tgt_mv_vec->vx, tgt_mv_vec->vz);
            tgt_mv_vec->vx = Math_MulFixed(max_tgt_mv_xz_len, shRsin(ang_y), Q12_SHIFT);
            tgt_mv_vec->vz = Math_MulFixed(max_tgt_mv_xz_len, shRcos(ang_y), Q12_SHIFT);
        }
    }
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/view/vc_main", vcFlipFromCamExclusionArea);

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
    dec_spd_per_dist_y  = FP_MULTIPLY_PRECISE(cam_mv_prm_p->accel_y, 1.0f, Q12_SHIFT);

    vwRenewalXZVelocityToTargetPos(&w_p->cam_velo_60.vx, &w_p->cam_velo_60.vz, &w_p->cam_pos_50,
                                   &w_p->cam_tgt_pos_44, FP_METER(1.6f), cam_mv_prm_p->accel_xz,
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

INCLUDE_ASM("asm/bodyprog/nonmatchings/view/vc_main", vcMakeNewBaseCamAng);

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

    vec.vx = FP_FROM(chara_pos->vx - cam_pos->vx, Q4_SHIFT);
    vec.vy = FP_FROM(chara_bottom_y - cam_pos->vy, Q4_SHIFT);
    vec.vz = FP_FROM(chara_pos->vz - cam_pos->vz, Q4_SHIFT);
    ApplyMatrixSV(base_matT, &vec, &vec);
    vwVectorToAngle(ofs_cam2chara_btm_ang, &vec);

    vec.vx = FP_FROM(chara_pos->vx - cam_pos->vx, Q4_SHIFT);
    vec.vy = FP_FROM(chara_top_y - cam_pos->vy, Q4_SHIFT);
    vec.vz = FP_FROM(chara_pos->vz - cam_pos->vz, Q4_SHIFT);
    ApplyMatrixSV(base_matT, &vec, &vec);
    vwVectorToAngle(ofs_cam2chara_top_ang, &vec);
}

void vcAdjCamOfsAngByCharaInScreen(SVECTOR* cam_ang, SVECTOR* ofs_cam2chara_btm_ang, SVECTOR* ofs_cam2chara_top_ang, VC_WORK* w_p) // 0x80085460
{
    // sh2 dwarf names.
    s16 adj_cam_ang_x;
    s16 var_a1; // Probably temp for adj_cam_ang_x/
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
    ofs_ang_spd->vz = vwRetNewAngSpdToTargetAng(ofs_ang_spd->vz, ofs_ang->vz, ofs_tgt_ang->vz, FP_FLOAT_TO(0.4f, Q12_SHIFT), FP_FLOAT_TO(0.4f, Q12_SHIFT), FP_FLOAT_TO(3.0f, Q12_SHIFT));

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
                              0, FP_METER(-0.8f), FP_METER(4.8f),
                              FP_ANGLE(180.0f), FP_ANGLE(0.0f), FP_METER(-3.2f), FP_METER(16.0f));
    }
    else if (w_p->field_FC != 0)
    {
        w_p->field_FC = 0;
        vwSetViewInfoDirectMatrix(NULL, &w_p->field_DC);
    }
    else if (cam_mv_type == VC_MV_SELF_VIEW)
    {
        vcSelfViewTimer += g_DeltaTime0;

        // TODO: in SH2 these FP_ANGLEs are using radian float values, while rest of SH2 used degrees.
        // Maybe these are meant to be radians encoded as Q3.12 somehow, but haven't found a good way for it yet.
        noise_ang.vx = vcCamMatNoise(4, FP_ANGLE(500.0f), FP_ANGLE(800.0f), vcSelfViewTimer);
        noise_ang.vy = vcCamMatNoise(2, FP_ANGLE(400.0f), FP_ANGLE(1000.0f), vcSelfViewTimer);
        noise_ang.vz = 0;
        func_80096C94(&noise_ang, &noise_mat);

        noise_mat.m[0][0] += vcCamMatNoise(12, FP_ANGLE(700.0f), FP_ANGLE(900.0f), vcSelfViewTimer);
        noise_mat.m[0][1] += vcCamMatNoise(12, FP_ANGLE(600.0f), FP_ANGLE(1000.0f), vcSelfViewTimer);
        noise_mat.m[0][2] += vcCamMatNoise(12, FP_ANGLE(600.0f), FP_ANGLE(800.0f), vcSelfViewTimer);
        noise_mat.m[1][0] += vcCamMatNoise(12, FP_ANGLE(500.0f), FP_ANGLE(500.0f), vcSelfViewTimer);
        noise_mat.m[1][1] += vcCamMatNoise(12, FP_ANGLE(900.0f), FP_ANGLE(400.0f), vcSelfViewTimer);
        noise_mat.m[1][2] += vcCamMatNoise(12, FP_ANGLE(650.0f), FP_ANGLE(950.0f), vcSelfViewTimer);
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

INCLUDE_ASM("asm/bodyprog/nonmatchings/view/vc_main", Math_VectorMagnitude);

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
        ret_dist = 0;

    return ret_dist;
}
