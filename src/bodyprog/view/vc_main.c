#include "game.h"

#include <abs.h>

#include "bodyprog/bodyprog.h"
#include "bodyprog/screen/screen_data.h"
#include "bodyprog/screen/screen_draw.h"
#include "bodyprog/math/math.h"
#include "bodyprog/player_logic.h"
#include "bodyprog/view/vc_main.h"
#include "bodyprog/view/vw_system.h"

#define MIN_IN_ROAD_DIST Q12(1.0f) // `vcGetMinInRoadDist` in SH2, hardcoded to `Q12(1.0f)` in SH1.

VC_WATCH_MV_PARAM vcWatchMvPrmSt;
q19_12            vcSelfViewTimer;

/** @brief Fallback camera path collision. */
VC_NEAR_ROAD_DATA vcNullNearRoad = {
    .road_p_0              = vcNullRoadArray,
    .rd_dir_type_4         = VC_RD_DIR_Z,
    .use_priority_5        = 0,
    .chara2road_sum_dist_8 = Q12(0.0f),
    .chara2road_vec_x_C    = Q12(0.0f),
    .chara2road_vec_z_10   = Q12(0.0f),
    .rd_14                 = { Q4(3616.0f), Q4(480.0f), Q4(3616.0f), Q4(480.0f) },
    .sw_1C                 = { Q4(3616.0f), Q4(480.0f), Q4(3616.0f), Q4(480.0f) }
};

/** @brief Default look-at move parameters. */
VC_WATCH_MV_PARAM deflt_watch_mv_prm = {
    Q12(1.2f),
    Q12(2.2f),
    Q12(0.22f),
    Q12(0.7f)
};

/** @brief First-person look-at move parameters. */
VC_WATCH_MV_PARAM self_view_watch_mv_prm = {
    Q12(1.68f),
    Q12(3.08f),
    Q12(0.44f),
    Q12(1.4f)
};

/** @brief Camera move parameters for user? */
VC_CAM_MV_PARAM cam_mv_prm_user = {
    Q12(10.0f),
    Q12(3.0f),
    Q12(6.0f),
    Q12(2.0f)
};

/** @brief Boundary radii. */
q19_12 excl_r_ary[9] = {
    Q12(4.0f),
    Q12(4.0f),
    Q12(3.7f),
    Q12(3.2f),
    Q12(2.7f),
    Q12(2.3f),
    Q12(1.9f),
    Q12(1.5f),
    Q12(1.3f)
};

void vcInitVCSystem(VC_ROAD_DATA* vc_road_ary_list) // 0x80080940
{
    vcWork.view_cam_active_f_0 = false;

    // Fall back on default camera paths.
    if (vc_road_ary_list == NULL)
    {
        vcWork.vc_road_ary_list_4 = vcNullRoadArray;
    }
    // Use provided camera paths.
    else
    {
        vcWork.vc_road_ary_list_4 = vc_road_ary_list;
    }

    Vc_CurNearRoadSet(&vcWork, &vcNullNearRoad);

    vcWork.old_cam_excl_area_r_6C = NO_VALUE;
    vcWork.watch_tgt_max_y_88     = Q12(30.0f);
    vcWork.field_D8               = false;
    vcWork.field_FC               = false;
}

void vcStartCameraSystem(void) // 0x800809DC
{
    vcWork.view_cam_active_f_0 = true;
    vcWork.field_D8            = false;
    vcWork.field_FC            = false;
    vcWork.geom_screen_dist_30 = g_GameWork.gsScreenHeight_58A;
}

void vcEndCameraSystem(void) // 0x80080A04
{
    vcWork.view_cam_active_f_0 = false;
}

s32 func_80080A10(void) // 0x80080A10
{
    return vcWork.cur_near_road_2B8.road_p_0->field_15;
}

void Vc_LookAtPositionYSet(q19_12 lookAtPosY) // 0x80080A30
{
    vcWork.watch_pos_y_2E4 = lookAtPosY;
}

q19_12 Vc_LookAtPositionYGet(void) // 0x80080A3C
{
    return vcWork.watch_pos_y_2E4;
}

void vcSetFirstCamWork(VECTOR3* cam_pos, s16 chara_eye_ang_y, bool use_through_door_cam_f) // 0x80080A4C
{
    Math_SVectorZero(&vcWork.ofs_cam_ang_spd_C0);

    vcWork.flags_8 = VC_WARP_CAM_F | VC_WARP_WATCH_F | VC_WARP_CAM_TGT_F;

    vcWork.cam_pos_50      = *cam_pos;
    vcWork.cam_mv_ang_y_5C = Q12_ANGLE(0.0f);

    Math_Vector3Zero(&vcWork.cam_velo_60);

    vcWork.cam_tgt_pos_44 = *cam_pos;

    Math_Vector3Zero(&vcWork.cam_tgt_velo_100);

    vcWork.cam_mv_ang_y_5C = Q12_ANGLE(0.0f);
    vcWork.cam_tgt_spd_110 = Q12(0.0f);

    vcWork.cam_chara2ideal_ang_y_FE = Math_AngleNormalize(chara_eye_ang_y + Q12_ANGLE(180.0f));

    Vc_CurNearRoadSet(&vcWork, &vcNullNearRoad);

    vcWork.through_door_activate_init_f_C = use_through_door_cam_f;
    vcSetTHROUGH_DOOR_CAM_PARAM_in_VC_WORK(&vcWork, VC_TDSC_END);
}

void func_80080B58(GsCOORDINATE2* arg0, SVECTOR* rot, VECTOR3* pos) // 0x80080B58
{
    MATRIX mat;

    vcWork.field_FC = true;

    Vw_CoordHierarchyMatrixCompute(arg0, &vcWork.field_DC);
    Math_RotMatrixZxyNeg(rot, &mat);
    MulMatrix(&vcWork.field_DC, &mat);

    vcWork.field_DC.t[0] = Q12_TO_Q8(pos->vx);
    vcWork.field_DC.t[1] = Q12_TO_Q8(pos->vy);
    vcWork.field_DC.t[2] = Q12_TO_Q8(pos->vz);
}

void vcWorkSetFlags(VC_FLAGS enable, VC_FLAGS disable) // 0x80080BF8
{
    vcWork.flags_8 = (vcWork.flags_8 | enable) & ~disable;
}

s32 Vc_LookAtOffsetYMaxSet(s32 lookAtOffsetYMax) // 0x80080C18
{
    s32 prevVal;

    prevVal                   = vcWork.watch_tgt_max_y_88;
    vcWork.watch_tgt_max_y_88 = lookAtOffsetYMax;
    return prevVal;
}

void vcUserWatchTarget(VECTOR3* watch_tgt_pos, VC_WATCH_MV_PARAM* watch_prm_p, bool warp_watch_f) // 0x80080C2C
{
    vcWork.flags_8 = (vcWork.flags_8 & ~(VC_USER_WATCH_F | VC_VISIBLE_CHARA_F)) | VC_USER_WATCH_F;

    if (warp_watch_f)
    {
        vcWork.flags_8 |= VC_WARP_WATCH_F;
    }

    vcWork.watch_tgt_pos_7C   = *watch_tgt_pos;
    vcWork.watch_tgt_ang_z_8C = Q12_ANGLE(0.0f);

    if (watch_prm_p == NULL)
    {
        vcWork.user_watch_mv_prm_70 = deflt_watch_mv_prm;
    }
    else
    {
        vcWork.user_watch_mv_prm_70 = *watch_prm_p;
    }
}

void vcUserCamTarget(VECTOR3* cam_tgt_pos, VC_CAM_MV_PARAM* cam_prm_p, bool warp_cam_f) // 0x80080CBC
{
    // Set flags.
    vcWork.flags_8 = (vcWork.flags_8 & ~(VC_USER_CAM_F | VC_WARP_CAM_F)) | VC_USER_CAM_F;
    if (warp_cam_f)
    {
        vcWork.flags_8 |= VC_WARP_CAM_F;
    }

    // Set target position.
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

void func_80080D68(void) // 0x80080D68
{
    vcWork.field_D8 = true;
}

void vcGetNowWatchPos(VECTOR3* watch_pos) // 0x80080D78
{
    s32 sin_y;
    s32 cos_y;
    s32 cos_x;
    s32 sin_x;
    s32 r;

    cos_x = Math_Cos(vcWork.cam_mat_ang_8E.vx);
    sin_x = Math_Sin(vcWork.cam_mat_ang_8E.vx);
    cos_y = Math_Cos(vcWork.cam_mat_ang_8E.vy);
    sin_y = Math_Sin(vcWork.cam_mat_ang_8E.vy);

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

void vcReturnPreAutoCamWork(bool warp_f) // 0x80080ED0
{
    // Set warp flags if warping.
    if (warp_f)
    {
        vcWork.flags_8 |= VC_WARP_CAM_F | VC_WARP_WATCH_F | VC_WARP_CAM_TGT_F;
    }

    vcWork.flags_8            &= ~(VC_USER_CAM_F | VC_USER_WATCH_F);
    vcWork.geom_screen_dist_30 = g_GameWork.gsScreenHeight_58A;
}

void vcSetSubjChara(VECTOR3* chara_pos, q19_12 chara_bottom_y, q19_12 chara_top_y, q19_12 chara_grnd_y, VECTOR3* chara_head_pos,
                    q3_12 chara_mv_spd, q19_12 chara_mv_ang_y, q3_12 chara_ang_spd_y, q3_12 chara_eye_ang_y, q3_12 chara_eye_ang_wy, q19_12 chara_watch_xz_r) // 0x80080F14
{
    vcWork.chara_pos_114        = *chara_pos;
    vcWork.chara_bottom_y_120   = chara_bottom_y;
    vcWork.chara_top_y_124      = chara_top_y;
    vcWork.chara_center_y_128   = (chara_bottom_y + chara_top_y) >> 1; // `/ 2`.
    vcWork.chara_grnd_y_12C     = chara_grnd_y;
    vcWork.chara_head_pos_130   = *chara_head_pos;
    vcWork.chara_mv_spd_13C     = chara_mv_spd;
    vcWork.chara_eye_ang_y_144  = chara_eye_ang_y;
    vcWork.chara_mv_ang_y_140   = chara_mv_ang_y;
    vcWork.chara_ang_spd_y_142  = chara_ang_spd_y;
    vcWork.chara_eye_ang_wy_146 = chara_eye_ang_wy;
    vcWork.chara_watch_xz_r_148 = chara_watch_xz_r;
}

s32 vcExecCamera(void) // 0x80080FBC
{
    VECTOR3            sv_old_cam_pos;
    SVECTOR            sv_old_cam_mat_ang;
    VC_WATCH_MV_PARAM* watch_mv_prm_p;
    VC_CAM_MV_PARAM*   cam_mv_prm_p;
    VC_AREA_SIZE_TYPE  cur_rd_area_size;
    VC_CAM_MV_TYPE     cur_cam_mv_type;
    s32                self_view_eff_rate;
    bool               warp_f;
    s32                far_watch_rate;
    VC_ROAD_FLAGS      cur_rd_flags;

    sv_old_cam_pos     = vcWork.cam_pos_50;
    sv_old_cam_mat_ang = vcWork.cam_mat_ang_8E;

    if (!vcWork.view_cam_active_f_0)
    {
        return VC_MV_CHASE;
    }

    vcSetAllNpcDeadTimer();
    SetGeomScreen(vcWork.geom_screen_dist_30);
    vcPreSetDataInVC_WORK(&vcWork, vcWork.vc_road_ary_list_4);

    warp_f           = vcSetCurNearRoadInVC_WORK(&vcWork);
    cur_rd_flags     = vcWork.cur_near_road_2B8.road_p_0->flags_10;
    cur_rd_area_size = vcWork.cur_near_road_2B8.road_p_0->area_size_type_11;
    cur_cam_mv_type  = vcRetCurCamMvType(&vcWork);

    far_watch_rate     = vcRetFarWatchRate(CHECK_FLAG(vcWork.flags_8, VC_PRS_F_VIEW_F, !g_GameWorkConst->config_0.optExtraViewCtrl_28), cur_cam_mv_type, &vcWork);
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

    vcWork.through_door_activate_init_f_C = false;
    vcWork.flags_8                       &= ~(VC_WARP_CAM_F | VC_WARP_WATCH_F | VC_WARP_CAM_TGT_F);

    return vcRetSmoothCamMvF(&sv_old_cam_pos, &vcWork.cam_pos_50, &sv_old_cam_mat_ang, &vcWork.cam_mat_ang_8E);
}

void vcSetAllNpcDeadTimer(void) // 0x8008123C
{
    #define DEATH_TIME_MAX Q12(10.0f)

    s_SubCharacter* curChara;

    // Run through NPCs.
    for (curChara = &g_SysWork.npcs_1A0[0]; curChara < &g_SysWork.npcs_1A0[ARRAY_SIZE(g_SysWork.npcs_1A0)]; curChara++)
    {
        // Continue if invalid character.
        if (curChara->model_0.charaId_0 == Chara_None)
        {
            continue;
        }

        // Increment and clamp death timer.
        if (curChara->health_B0 <= Q12(0.0f))
        {
            curChara->deathTimer_C4 += g_DeltaTime;
        }
        else
        {
            curChara->deathTimer_C4 = Q12(0.0f);
        }
        if (curChara->deathTimer_C4 > DEATH_TIME_MAX)
        {
            curChara->deathTimer_C4 = DEATH_TIME_MAX;
        }
    }
}

s32 vcRetSmoothCamMvF(VECTOR3* old_pos, VECTOR3* now_pos, SVECTOR* old_ang, SVECTOR* now_ang) // 0x800812CC
{
    #define MOVE_DIST_MAX   Q12(0.0125f)
    #define ROT_X_ANGLE_MAX Q12_ANGLE(20.0f)
    #define ROT_Y_ANGLE_MAX Q12_ANGLE(30.0f)
    #define INTRPT_TIME_MIN Q12(1.0f)
    #define INTRPT_TIME_MAX Q12(4.0f)

    s32 intrpt; // Interpolation time (i.e. alpha)?
    s32 mv_vec; // Movement vector magnitude.
    s32 rot_x;
    s32 rot_y;

    intrpt = Q12(g_DeltaTime) / TIMESTEP_60_FPS;
    intrpt = CLAMP(intrpt, INTRPT_TIME_MIN, INTRPT_TIME_MAX);

    mv_vec = Vc_VectorMagnitudeCalc(Q12_TO_Q8(now_pos->vx - old_pos->vx),
                                    Q12_TO_Q8(now_pos->vy - old_pos->vy),
                                    Q12_TO_Q8(now_pos->vz - old_pos->vz));

    mv_vec = Q12(mv_vec) / intrpt;
    if (mv_vec > MOVE_DIST_MAX)
    {
        return VC_MV_CHASE;
    }

    rot_x = Q12(((now_ang->vx - old_ang->vx) >= Q12_ANGLE(0.0f)) ? (now_ang->vx - old_ang->vx) : (old_ang->vx - now_ang->vx)) / intrpt;
    if (rot_x > ROT_X_ANGLE_MAX)
    {
        return VC_MV_CHASE;
    }

    rot_y = Q12(abs(Math_AngleNormalize(now_ang->vy - old_ang->vy))) / intrpt;

    // This (guessed) line is needed for regalloc match, but compiler just optimizes out since `rot_x` isn't used afterward.
    // @bug Maybe the `Math_Cos` call below was meant to use the result of this, but was somehow left using `now_ang->vx`?
    rot_x = ((now_ang->vx - old_ang->vx) >= Q12_ANGLE(0.0f)) ? now_ang->vx : old_ang->vx;

    rot_y = Q12_MULT(rot_y, Math_Cos(now_ang->vx));
    return (rot_y <= ROT_Y_ANGLE_MAX) ? VC_MV_SETTLE : VC_MV_CHASE;
}

VC_CAM_MV_TYPE vcRetCurCamMvType(VC_WORK* w_p) // 0x80081428
{
    bool hasViewFlag;

    if (g_GameWorkConst->config_0.optExtraViewMode_29)
    {
        hasViewFlag = (vcWork.flags_8 & VC_PRS_F_VIEW_F) == VC_PRS_F_VIEW_F;

        // TODO: Can this weird XOR be removed? (XOR 1) should be same as `!hasViewFlag`?
        if ((g_GameWorkConst->config_0.optExtraViewCtrl_28 && (hasViewFlag ^ 1) != 0) ||
            (!g_GameWorkConst->config_0.optExtraViewCtrl_28 && hasViewFlag))
        {
            if (!(w_p->flags_8 & (VC_USER_CAM_F | VC_USER_WATCH_F | VC_INHIBIT_FAR_WATCH_F)) &&
                !func_8008150C(w_p->chara_pos_114.vx, w_p->chara_pos_114.vz))
            {
                return VC_MV_SELF_VIEW;
            }
        }
    }

    if (w_p->through_door_10.active_f_0)
    {
        if (!vcRetThroughDoorCamEndF(w_p))
        {
            return VC_MV_THROUGH_DOOR;
        }

        vcSetTHROUGH_DOOR_CAM_PARAM_in_VC_WORK(w_p, VC_TDSC_END);
    }

    return w_p->cur_near_road_2B8.road_p_0->cam_mv_type_14;
}

bool func_8008150C(q19_12 posX, q19_12 posZ)
{
    switch (Map_TypeGet())
    {
        case 0:
            if ((posX - Q12(201.8f)) > (u32)(Q12(28.2f) + 1))
            {
                return false;
            }
            else if (posZ < Q12(-92.0f))
            {
                return false;
            }
            else if (posZ <= Q12(-68.0f))
            {
                return true;
            }
            break;

        case 3:
            if ((posX + Q12(230.0f)) > (u32)Q12(29.0f))
            {
                return false;
            }
            else if (posZ < Q12(-12.0f))
            {
                return false;
            }
            else if (posZ <= Q12(12.0f))
            {
                return true;
            }
            break;
    }

    return false;
}

bool vcRetThroughDoorCamEndF(VC_WORK* w_p) // 0x800815F0
{
    VC_THROUGH_DOOR_CAM_PARAM* prm_p;
    q19_12                     rail2chara_dist;
    q19_12                     abs_ofs_ang_y;

    prm_p           = &w_p->through_door_10;
    rail2chara_dist = prm_p->rail_sta_to_chara_dist_18;

    if (!w_p->through_door_10.active_f_0)
    {
        return true;
    }

    if (prm_p->timer_4 > Q12(1.2f) && w_p->nearest_enemy_xz_dist_2E0 < Q12(1.2f))
    {
        return true;
    }

    if (rail2chara_dist > Q12(2.3f))
    {
        return true;
    }

    if (rail2chara_dist > Q12(0.5f))
    {
        abs_ofs_ang_y = Math_AngleNormalize(w_p->chara_eye_ang_y_144 - ratan2(w_p->chara_pos_114.vx - w_p->through_door_10.rail_sta_pos_C.vx,
                                                                              w_p->chara_pos_114.vz - w_p->through_door_10.rail_sta_pos_C.vz));
        if (abs_ofs_ang_y < Q12_ANGLE(0.0f))
        {
            abs_ofs_ang_y = -abs_ofs_ang_y;
        }

        if (abs_ofs_ang_y > Q12_ANGLE(70.0f))
        {
            return true;
        }
    }

    return false;
}

q19_12 vcRetFarWatchRate(s32 far_watch_button_prs_f, VC_CAM_MV_TYPE cur_cam_mv_type, VC_WORK* w_p) // 0x800816B0
{
    q19_12 dist;
    q19_12 far_watch_rate;
    q19_12 abs_ofs_ang_y;
    q19_12 railDistX;
    q19_12 railDistZ;
    s32    prsFViewFlag;

    if ((vcWork.flags_8 & (VC_USER_WATCH_F | VC_INHIBIT_FAR_WATCH_F)))
    {
        far_watch_rate = Q12(0.0f);
    }
    else
    {
        switch (cur_cam_mv_type)
        {
            case VC_MV_CHASE:
            case VC_MV_SETTLE:
                far_watch_rate = Q12(far_watch_button_prs_f != 0);
                break;

            case VC_MV_THROUGH_DOOR:
                far_watch_rate = Q12(1.0f); // Q12_ANGLE(256.0f);
                if (!far_watch_button_prs_f)
                {
                    // TODO: Unsure if these should use `Q12` or `Q12_ANGLE`.
                    // Gets multiplied by `dist`, so `Q12` fits,
                    // but then it gets subtracted by `abs_ofs_ang_y`, so `Q12_ANGLE` would also fits?

                    dist           = w_p->through_door_10.rail_sta_to_chara_dist_18;
                    far_watch_rate = Q12(0.9f) - ((dist * Q12(0.9f)) / Q12(2.3f));
                    // far_watch_rate = Q12_ANGLE(324.0f) - ((dist * Q12_ANGLE(324.0f)) / Q12_ANGLE(828.0f));
                    if (far_watch_rate < Q12(0.0f))
                    {
                        far_watch_rate = Q12(0.0f);
                    }

                    if (dist > Q12(0.5f))
                    {
                        railDistX = w_p->chara_pos_114.vx - w_p->through_door_10.rail_sta_pos_C.vx;
                        railDistZ = w_p->chara_pos_114.vz - w_p->through_door_10.rail_sta_pos_C.vz;
                        if (((w_p->chara_eye_ang_y_144 - ratan2(railDistX, railDistZ)) << 20) < 0)
                        {
                            abs_ofs_ang_y = -Math_AngleNormalize(w_p->chara_eye_ang_y_144 - ratan2(railDistX, railDistZ));
                        }
                        else
                        {
                            abs_ofs_ang_y = Math_AngleNormalize(w_p->chara_eye_ang_y_144 - ratan2(railDistX, railDistZ));
                        }

                        far_watch_rate = (far_watch_rate * (Q12(0.1945f) - abs_ofs_ang_y)) / Q12(0.1945f);
                        // far_watch_rate = (far_watch_rate * (Q12_ANGLE(70.0f) - abs_ofs_ang_y)) / Q12_ANGLE(70.0f);
                        if (far_watch_rate < Q12(0.0f))
                        {
                            far_watch_rate = Q12(0.0f);
                        }
                    }
                }
                break;

            default:
            case VC_MV_FIX_ANG:
            case VC_MV_SELF_VIEW:
                far_watch_rate = Q12(0.0f);
                break;
        }
    }

    if (g_GameWorkConst->config_0.optExtraViewMode_29)
    {
        // Awkward `VC_PRS_F_VIEW_F` flag check. TODO: Use `CHECK_FLAG`? It's possible this was originally typed manually.
        prsFViewFlag = vcWork.flags_8 >> 9;
        prsFViewFlag = prsFViewFlag & (1 << 0);

        if ((g_GameWorkConst->config_0.optExtraViewCtrl_28 && (prsFViewFlag ^ 1) != 0) ||
            (!g_GameWorkConst->config_0.optExtraViewCtrl_28 && prsFViewFlag))
        {
            if (!(w_p->flags_8 & (VC_USER_CAM_F | VC_USER_WATCH_F | VC_INHIBIT_FAR_WATCH_F)) &&
                func_8008150C(w_p->chara_pos_114.vx, w_p->chara_pos_114.vz))
            {
                far_watch_rate = Q12(0.0f);
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

    cam_max_rate = (cur_cam_mv_type == VC_MV_SELF_VIEW) ? Q8(16.0f) : Q8(5.6f);

    xyz_dist = Vc_VectorMagnitudeCalc(Q12_TO_Q8(w_p->cam_pos_50.vx - w_p->chara_head_pos_130.vx),
                                      Q12_TO_Q8(w_p->cam_pos_50.vy - w_p->chara_head_pos_130.vy),
                                      Q12_TO_Q8(w_p->cam_pos_50.vz - w_p->chara_head_pos_130.vz));

    if (xyz_dist >= Q8(0.5f))
    {
        if (xyz_dist > Q8(1.2f))
        {
            max_rate = 0;
        }
        else
        {
            max_rate = (cam_max_rate * (Q8(1.2f) - xyz_dist)) / Q8(0.7);
        }
    }
    else
    {
        max_rate = cam_max_rate;
    }

    if (w_p->nearest_enemy_xz_dist_2E0 > Q12(4.0f))
    {
        mul_rate = Q12(1.0f);
    }
    else
    {
        if (w_p->nearest_enemy_xz_dist_2E0 < Q12(2.0f))
        {
            mul_rate = Q12(0.0f);
        }
        else
        {
            mul_rate = (w_p->nearest_enemy_xz_dist_2E0 - Q12(2.0f)) / 2;
        }
    }

    max_rate = Q12_MULT(max_rate, mul_rate);

    ret_eff_rate = cam_max_rate;
    if (max_rate >= Q12(0.0f))
    {
        if (max_rate <= ret_eff_rate)
        {
            ret_eff_rate = max_rate;
        }
    }
    else
    {
        ret_eff_rate = Q12(0.0f);
    }

    return ret_eff_rate;
}

void vcSetFlagsByCamMvType(VC_CAM_MV_TYPE cam_mv_type, s32 far_watch_rate, bool all_warp_f) // 0x80081A0C
{
    s32 vcOldPrsFViewFlag;
    s32 vcPrsFViewFlag;

    if (far_watch_rate == 0)
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

        // Awkward `VC_PRS_F_VIEW_F` flag check.
        vcPrsFViewFlag = vcWork.flags_8 >> 9;
        vcPrsFViewFlag = vcPrsFViewFlag & 0x1;

        // `optExtraViewCtrl && !vcPrsFViewFlag` ||
        // `!optExtraViewCtrl && vcPrsFViewFlag`
        if ((g_GameWorkConst->config_0.optExtraViewCtrl_28 && (vcPrsFViewFlag ^ 1) != 0) ||
            (!g_GameWorkConst->config_0.optExtraViewCtrl_28 && vcPrsFViewFlag))
        {
            // Awkward `VC_OLD_PRS_F_VIEW_F` flag check.
            vcOldPrsFViewFlag = vcWork.flags_8 >> 10;
            vcOldPrsFViewFlag = vcOldPrsFViewFlag & 0x1;

            // `!(optExtraViewCtrl && !vcOldPrsFViewFlag)` &&
            // `!(!optExtraViewCtrl && vcOldPrsFViewFlag)`
            if (!(g_GameWorkConst->config_0.optExtraViewCtrl_28 && (vcOldPrsFViewFlag ^ 1) != 0) &&
                !(!g_GameWorkConst->config_0.optExtraViewCtrl_28 && vcOldPrsFViewFlag))
            {
                if (g_GameWorkConst->config_0.optExtraViewMode_29)
                {
                    Vc_FlagSet(VC_WARP_WATCH_F);
                }
            }
        }
    }

    if (all_warp_f)
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
    if (g_DeltaTime != Q12(0.0f))
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

    if (vcWork.through_door_activate_init_f_C)
    {
        vcSetTHROUGH_DOOR_CAM_PARAM_in_VC_WORK(&vcWork, VC_TDSC_START);
    }

    vcSetTHROUGH_DOOR_CAM_PARAM_in_VC_WORK(&vcWork, VC_TDSC_MAIN);
    vcSetNearestEnemyDataInVC_WORK(w_p);
    vcSetNearRoadAryByCharaPos(w_p, vc_road_ary_list, Q12(20.0f), 0, w_p->nearest_enemy_2DC != NULL);
}

void vcSetTHROUGH_DOOR_CAM_PARAM_in_VC_WORK(VC_WORK* w_p, enum _THROUGH_DOOR_SET_CMD_TYPE set_cmd_type) // 0x80081CBC
{
    VC_THROUGH_DOOR_CAM_PARAM* prm_p;

    prm_p = &w_p->through_door_10;

    switch (set_cmd_type)
    {
        case VC_TDSC_START:
            w_p->through_door_10.active_f_0 = true;
            prm_p->timer_4                  = Q12(0.0f);
            prm_p->rail_ang_y_8             = w_p->chara_eye_ang_y_144;
            prm_p->rail_sta_pos_C.vx        = w_p->chara_pos_114.vx;
            prm_p->rail_sta_pos_C.vy        = w_p->chara_grnd_y_12C - Q12(1.95f);
            prm_p->rail_sta_pos_C.vz        = w_p->chara_pos_114.vz;
            break;

        case VC_TDSC_END:
            w_p->through_door_10.active_f_0 = false;
            prm_p->timer_4                  = Q12(0.0f);
            break;

        case VC_TDSC_MAIN:
            if (w_p->through_door_10.active_f_0)
            {
                prm_p->rail_sta_to_chara_dist_18 = Vc_VectorMagnitudeCalc(w_p->chara_pos_114.vx - w_p->through_door_10.rail_sta_pos_C.vx,
                                                                          Q12(0.0f),
                                                                          w_p->chara_pos_114.vz - w_p->through_door_10.rail_sta_pos_C.vz);

                prm_p->timer_4 += g_DeltaTime;
            }
            break;
    }
}

void vcSetNearestEnemyDataInVC_WORK(VC_WORK* w_p) // 0x80081D90
{
    #define ENEMY_DEATH_TIME_MAX Q12(1.5f)
    #define ENEMY_DIST_MAX       Q12(15.0f)

    bool            set_active_data_f;
    q19_12          xz_dist;
    q19_12          ofs_x;
    q19_12          ofs_z;
    q19_12          all_min_dist;
    q19_12          active_min_dist;
    s_SubCharacter* sc_p;
    s_SubCharacter* all_min_sc_p;
    s_SubCharacter* active_min_sc_p;

    sc_p            = NULL;
    all_min_sc_p    = NULL;
    active_min_sc_p = NULL;
    all_min_dist    = ENEMY_DIST_MAX;
    active_min_dist = ENEMY_DIST_MAX;

    if (g_SysWork.flags_22A4 & SysFlag2_5) // `sh2jms->player.battle(ShBattleInfo).status & (1 << 4)` in SH2.
    {
        w_p->nearest_enemy_2DC         = NULL;
        w_p->nearest_enemy_xz_dist_2E0 = ENEMY_DIST_MAX;
        return;
    }

    for (sc_p = &g_SysWork.npcs_1A0[0]; sc_p < &g_SysWork.npcs_1A0[ARRAY_SIZE(g_SysWork.npcs_1A0)]; sc_p++)
    {
        if (sc_p->model_0.charaId_0 >= Chara_AirScreamer &&
            sc_p->model_0.charaId_0 <= Chara_MonsterCybil &&
            (sc_p->deathTimer_C4 <= ENEMY_DEATH_TIME_MAX || sc_p->health_B0 >= Q12(0.0f)) &&
            !(sc_p->flags_3E & CharaFlag_Unk5)) // `sc_p->battle(ShBattleInfo).status & (1 << 5)` in SH2.
        {
            ofs_x = sc_p->position_18.vx - w_p->chara_pos_114.vx;
            ofs_z = sc_p->position_18.vz - w_p->chara_pos_114.vz;

            if (abs(ofs_x) >= ENEMY_DIST_MAX ||
                abs(ofs_z) >= ENEMY_DIST_MAX)
            {
                continue;
            }

            xz_dist = Vc_VectorMagnitudeCalc(ofs_x, 0, ofs_z);
            ratan2(ofs_x, ofs_z); // @unused Result unused?

            if (xz_dist < all_min_dist)
            {
                all_min_dist = xz_dist;
                all_min_sc_p = sc_p;
            }

            // TODO: Not sure how to move the `set_active_data_f = true` part out of this if.
            if (sc_p->model_0.charaId_0 >= Chara_HangedScratcher ||
                (set_active_data_f = true, (sc_p->model_0.charaId_0 < Chara_Stalker)))
            {
                set_active_data_f = true;
                if (sc_p->flags_3E & CharaFlag_Unk2) // `sc_p->battle(ShBattleInfo).status & (1 << 2)` in SH2.
                {
                    set_active_data_f = false;
                    if (sc_p == &g_SysWork.npcs_1A0[g_SysWork.targetNpcIdx_2353])
                    {
                        set_active_data_f = g_SysWork.playerCombat_38.isAiming_13 > false;
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

void vcSetNearRoadAryByCharaPos(VC_WORK* w_p, VC_ROAD_DATA* road_ary_list, s32 half_w, s32 unused, bool near_enemy_f) // 0x80081FBC
{
    q19_12             diff_pos_x;
    q19_12             sum_pos_x;
    q19_12             diff_pos_z;
    q19_12             sum_pos_z;
    q19_12             rd_max_hx;
    q19_12             rd_max_hz;
    q19_12             sw_min_hx;
    q19_12             sw_min_hz;
    q19_12             rd_min_hx;
    q19_12             rd_min_hz;
    q19_12             sw_max_hx;
    q19_12             sw_max_hz;
    s32                flag;
    s32                dir_type;
    s32                unused2;
    VC_NEAR_ROAD_DATA* ptr;
    VC_ROAD_DATA*      road_data_ptr;

    road_data_ptr          = road_ary_list;
    w_p->near_road_suu_2B4 = 0;

    diff_pos_x = w_p->chara_pos_114.vx - half_w;
    sum_pos_x  = w_p->chara_pos_114.vx + half_w;
    diff_pos_z = w_p->chara_pos_114.vz - half_w;
    sum_pos_z  = w_p->chara_pos_114.vz + half_w;

    while (!(road_data_ptr->flags_10 & VC_RD_END_DATA_F))
    {
        if (near_enemy_f)
        {
            flag = road_data_ptr->flags_10 & VC_RD_USE_NO_ENEMY_F;
        }
        else
        {
            flag = road_data_ptr->flags_10 & VC_RD_USE_NEAR_ENEMY_F;
        }

        if (!flag)
        {
            rd_min_hx = Q4_TO_Q12(road_data_ptr->lim_rd_8.min_hx);
            rd_max_hx = Q4_TO_Q12(road_data_ptr->lim_rd_8.max_hx);
            rd_min_hz = Q4_TO_Q12(road_data_ptr->lim_rd_8.min_hz);
            rd_max_hz = Q4_TO_Q12(road_data_ptr->lim_rd_8.max_hz);

            unused2 = 0;

            sw_min_hx = Q4_TO_Q12(road_data_ptr->lim_sw_0.min_hx);
            sw_max_hx = Q4_TO_Q12(road_data_ptr->lim_sw_0.max_hx);
            sw_min_hz = Q4_TO_Q12(road_data_ptr->lim_sw_0.min_hz);
            sw_max_hz = Q4_TO_Q12(road_data_ptr->lim_sw_0.max_hz);

            if ((sum_pos_x >= sw_min_hx && sw_max_hx >= diff_pos_x && sum_pos_z >= sw_min_hz && sw_max_hz >= diff_pos_z) ||
                (sum_pos_x >= rd_min_hx && rd_max_hx >= diff_pos_x && sum_pos_z >= rd_min_hz && rd_max_hz >= diff_pos_z))
            {
                ptr           = &w_p->near_road_ary_14C[w_p->near_road_suu_2B4];
                dir_type      = (rd_max_hz - rd_min_hz) < (rd_max_hx - rd_min_hx);
                ptr->road_p_0 = road_data_ptr;

                ptr->chara2road_sum_dist_8 = vcGetXZSumDistFromLimArea(&ptr->chara2road_vec_x_C, &ptr->chara2road_vec_z_10,
                                                                       w_p->chara_pos_114.vx, w_p->chara_pos_114.vz,
                                                                       sw_min_hx, sw_max_hx, sw_min_hz, sw_max_hz,
                                                                       ptr->road_p_0->flags_10 & VC_RD_MARGE_ROAD_F);

                ptr->rd_dir_type_4  = dir_type;
                ptr->use_priority_5 = vcRetRoadUsePriority(road_data_ptr->rd_type_11, unused2);
                ptr->rd_14.min_hx   = Q12_TO_Q4(rd_min_hx);
                ptr->rd_14.max_hx   = Q12_TO_Q4(rd_max_hx);
                ptr->rd_14.min_hz   = Q12_TO_Q4(rd_min_hz);
                ptr->rd_14.max_hz   = Q12_TO_Q4(rd_max_hz);
                ptr->sw_1C.min_hx   = Q12_TO_Q4(sw_min_hx);
                ptr->sw_1C.max_hx   = Q12_TO_Q4(sw_max_hx);
                ptr->sw_1C.min_hz   = Q12_TO_Q4(sw_min_hz);
                ptr->sw_1C.max_hz   = Q12_TO_Q4(sw_max_hz);
                w_p->near_road_suu_2B4++;
            }
        }

        road_data_ptr++;
    }
}

s32 vcRetRoadUsePriority(VC_ROAD_TYPE rd_type, s32 unused) // 0x8008227C
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

bool vcSetCurNearRoadInVC_WORK(VC_WORK* w_p) // 0x800822B8
{
    VC_NEAR_ROAD_DATA* new_cur_p;
    VC_NEAR_ROAD_DATA* n_rd_p;
    VC_NEAR_ROAD_DATA* old_cur_p;
    q3_12              old_cur_rd_ang_y;
    q3_12              ofs_ang_y;
    q19_12             old_cur_sum_dist;
    q19_12             adv_old_cur_dist;
    q19_12             new_cur_sum_dist;
    q19_12             proj_frame;
    bool               ret_warp_f;

    ret_warp_f       = false;
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
            ret_warp_f = true;
        }
        if (w_p->cur_near_road_2B8.road_p_0->flags_10 & VC_RD_WARP_OUT_F)
        {
            ret_warp_f = true;
        }

        w_p->cur_near_road_2B8 = *new_cur_p;

        return ret_warp_f;
    }

    adv_old_cur_dist = vcAdvantageDistOfOldCurRoad(old_cur_p);

    if (new_cur_p->use_priority_5        < old_cur_p->use_priority_5 &&
        old_cur_p->chara2road_sum_dist_8 < (adv_old_cur_dist * 2))
    {
        w_p->cur_near_road_2B8 = *old_cur_p;
    }
    else
    {
        if (old_cur_p->use_priority_5        < new_cur_p->use_priority_5 &&
            new_cur_p->chara2road_sum_dist_8 <= Q12(0.0f))
        {
            if (new_cur_p->road_p_0->flags_10 & VC_RD_WARP_IN_F)
            {
                ret_warp_f = true;
            }

            if (w_p->cur_near_road_2B8.road_p_0->flags_10 & VC_RD_WARP_OUT_F)
            {
                ret_warp_f = true;
            }

            w_p->cur_near_road_2B8 = *new_cur_p;
            return ret_warp_f;
        }

        old_cur_sum_dist = old_cur_p->chara2road_sum_dist_8;

        switch (old_cur_p->rd_dir_type_4)
        {
            case VC_RD_DIR_Z:
                old_cur_rd_ang_y = Q12_ANGLE(0.0f);
                break;

            case VC_RD_DIR_X:
                old_cur_rd_ang_y = Q12_ANGLE(90.0f);
                break;

            default:
                old_cur_rd_ang_y = Q12_ANGLE(0.0f);
                break;
        }

        ofs_ang_y = Math_AngleNormalize(w_p->chara_mv_ang_y_140 - old_cur_rd_ang_y);
        if (ofs_ang_y < Q12_ANGLE(0.0f))
        {
            ofs_ang_y += Q12_ANGLE(180.0f);
        }
        if (ofs_ang_y > Q12_ANGLE(90.0f))
        {
            ofs_ang_y = Q12_ANGLE(180.0f) - ofs_ang_y;
        }

        proj_frame = old_cur_sum_dist - adv_old_cur_dist;
        if (new_cur_sum_dist >= proj_frame)
        {
            w_p->cur_near_road_2B8 = *old_cur_p;
        }
        else if (old_cur_sum_dist < Q12(0.0f) && ofs_ang_y < Q12_ANGLE(20.0f))
        {
            w_p->cur_near_road_2B8 = *old_cur_p;
        }
        else
        {
            if (new_cur_p->road_p_0->flags_10 & VC_RD_WARP_IN_F)
            {
                ret_warp_f = true;
            }
            if (w_p->cur_near_road_2B8.road_p_0->flags_10 & VC_RD_WARP_OUT_F)
            {
                ret_warp_f = true;
            }

            w_p->cur_near_road_2B8 = *new_cur_p;
        }
    }

    return ret_warp_f;
}

s32 vcGetBestNewCurNearRoad(VC_NEAR_ROAD_DATA** new_cur_pp, VC_CAM_CHK_TYPE chk_type, VECTOR3* pos, VC_WORK* w_p) // 0x800826AC
{
    s32                dummy;
    q19_12             road_min_dist;
    q19_12             eff_min_dist;
    q19_12             evnt_min_dist;
    bool               renewal_f;
    q19_12             new_cur_dist;
    s32                new_cur_priority;
    VC_NEAR_ROAD_DATA* evnt_nearest_p;
    VC_NEAR_ROAD_DATA* eff_nearest_p;
    VC_NEAR_ROAD_DATA* road_nearest_p;
    VC_NEAR_ROAD_DATA* new_cur_p;

    new_cur_p    = NULL;
    new_cur_dist = INT_MAX;

    evnt_min_dist = vcGetNearestNEAR_ROAD_DATA(&evnt_nearest_p, chk_type, VC_RD_TYPE_EVENT,  pos, w_p, false);
    eff_min_dist  = vcGetNearestNEAR_ROAD_DATA(&eff_nearest_p,  chk_type, VC_RD_TYPE_EFFECT, pos, w_p, false);
    road_min_dist = vcGetNearestNEAR_ROAD_DATA(&road_nearest_p, chk_type, VC_RD_TYPE_ROAD,   pos, w_p, false);

    new_cur_priority = 0;
    renewal_f        = false;

    if (evnt_nearest_p != NULL)
    {
        if (new_cur_priority < evnt_nearest_p->use_priority_5)
        {
            if (evnt_min_dist <= Q12(0.0f) || evnt_min_dist < new_cur_dist)
            {
                renewal_f = true;
            }
        }
        else if (evnt_nearest_p->use_priority_5 >= new_cur_priority)
        {
            if (evnt_min_dist < new_cur_dist)
            {
                renewal_f = true;
            }
        }
        else if (new_cur_dist > Q12(0.0f) && evnt_min_dist < new_cur_dist)
        {
            renewal_f = true;
        }
    }

    if (renewal_f)
    {
        new_cur_p        = evnt_nearest_p;
        new_cur_dist     = evnt_min_dist;
        new_cur_priority = new_cur_p->use_priority_5;
    }

    renewal_f = false;

    if (road_nearest_p != NULL)
    {
        if (new_cur_priority < road_nearest_p->use_priority_5)
        {
            if (road_min_dist <= Q12(0.0f) || road_min_dist < new_cur_dist)
            {
                renewal_f = true;
            }
        }
        else if (road_nearest_p->use_priority_5 >= new_cur_priority)
        {
            if (road_min_dist < new_cur_dist)
            {
                renewal_f = true;
            }
        }
        else if (new_cur_dist > Q12(0.0f) && road_min_dist < new_cur_dist)
        {
            renewal_f = true;
        }
    }

    if (renewal_f)
    {
        new_cur_p        = road_nearest_p;
        new_cur_dist     = road_min_dist;
        new_cur_priority = new_cur_p->use_priority_5;
    }

    renewal_f = false;

    if (eff_nearest_p != NULL)
    {
        if (new_cur_priority < eff_nearest_p->use_priority_5)
        {
            if (eff_min_dist <= Q12(0.0f) || eff_min_dist < new_cur_dist)
            {
                renewal_f = true;
            }
        }
        else if (eff_nearest_p->use_priority_5 >= new_cur_priority)
        {
            if (eff_min_dist < new_cur_dist)
            {
                renewal_f = true;
            }
        }
        else if (new_cur_dist > Q12(0.0f) && eff_min_dist < new_cur_dist)
        {
            renewal_f = true;
        }
    }

    if (renewal_f)
    {
        new_cur_p    = eff_nearest_p;
        new_cur_dist = eff_min_dist;
    }

    if (new_cur_p == NULL)
    {
        new_cur_p    = &vcNullNearRoad;
        new_cur_dist = vcGetXZSumDistFromLimArea(&dummy, &dummy, pos->vx, pos->vz,
                                                 Q4_TO_Q12(vcNullNearRoad.rd_14.min_hx), Q4_TO_Q12(vcNullNearRoad.rd_14.max_hx),
                                                 Q4_TO_Q12(vcNullNearRoad.rd_14.min_hz), Q4_TO_Q12(vcNullNearRoad.rd_14.max_hz),
                                                 vcNullNearRoad.road_p_0->flags_10 & VC_RD_MARGE_ROAD_F);
    }

    *new_cur_pp = new_cur_p;
    return new_cur_dist;
}

q19_12 vcGetNearestNEAR_ROAD_DATA(VC_NEAR_ROAD_DATA** out_nearest_p_addr, VC_CAM_CHK_TYPE chk_type, VC_ROAD_TYPE rd_type, VECTOR3* pos, VC_WORK* w_p, bool chk_only_set_marge_f) // 0x80082908
{
    s32                dummy;
    q19_12             min_x;
    q19_12             max_x;
    q19_12             min_z;
    q19_12             max_z;
    q19_12             dist;         // Current dustaince.
    q19_12             min_sum_dist; // Closest distance.
    VC_NEAR_ROAD_DATA* n_rd_p;       // Current camera path collision.
    VC_NEAR_ROAD_DATA* nearest_p;    // Closest camera path collision.

    nearest_p    = NULL;
    n_rd_p       = w_p->near_road_ary_14C;
    min_sum_dist = INT_MAX;

    // Run through camera path collisions.
    for (n_rd_p = w_p->near_road_ary_14C; n_rd_p < &w_p->near_road_ary_14C[w_p->near_road_suu_2B4]; n_rd_p++)
    {
        if (n_rd_p->road_p_0->rd_type_11 == rd_type && (!chk_only_set_marge_f || n_rd_p->road_p_0->flags_10 & VC_RD_MARGE_ROAD_F))
        {
            switch (chk_type)
            {
                case VC_CHK_NEAREST_ROAD_TYPE:
                    min_x = Q4_TO_Q12(n_rd_p->rd_14.min_hx);
                    max_x = Q4_TO_Q12(n_rd_p->rd_14.max_hx);
                    min_z = Q4_TO_Q12(n_rd_p->rd_14.min_hz);
                    max_z = Q4_TO_Q12(n_rd_p->rd_14.max_hz);
                    break;

                case VC_CHK_NEAREST_SWITCH_TYPE:
                    min_x = Q4_TO_Q12(n_rd_p->sw_1C.min_hx);
                    max_x = Q4_TO_Q12(n_rd_p->sw_1C.max_hx);
                    min_z = Q4_TO_Q12(n_rd_p->sw_1C.min_hz);
                    max_z = Q4_TO_Q12(n_rd_p->sw_1C.max_hz);
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
            return Q12(0.35f);

        case VC_RD_TYPE_EVENT:
            return Q12(0.15f);
    }
}

void vcAutoRenewalWatchTgtPosAndAngZ(VC_WORK* w_p, VC_CAM_MV_TYPE cam_mv_type, VC_AREA_SIZE_TYPE cur_rd_area_size, s32 far_watch_rate, s32 self_view_eff_rate) // 0x80082B10
{
    VECTOR3 far_watch_pos;

    vcMakeFarWatchTgtPos(&far_watch_pos, w_p, cur_rd_area_size);
    if (cam_mv_type != VC_MV_SELF_VIEW)
    {
        vcMakeNormalWatchTgtPos(&w_p->watch_tgt_pos_7C, &w_p->watch_tgt_ang_z_8C, w_p, cam_mv_type, cur_rd_area_size);
        if (far_watch_rate != 0)
        {
            w_p->watch_tgt_pos_7C.vx += Q12_MULT(far_watch_rate, far_watch_pos.vx - w_p->watch_tgt_pos_7C.vx);
            w_p->watch_tgt_pos_7C.vy += Q12_MULT(far_watch_rate, far_watch_pos.vy - w_p->watch_tgt_pos_7C.vy);
            w_p->watch_tgt_pos_7C.vz += Q12_MULT(far_watch_rate, far_watch_pos.vz - w_p->watch_tgt_pos_7C.vz);
        }
    }
    else
    {
        w_p->watch_tgt_pos_7C = far_watch_pos;
    }

    vcMixSelfViewEffectToWatchTgtPos(&w_p->watch_tgt_pos_7C, &w_p->watch_tgt_ang_z_8C, self_view_eff_rate,
                                     w_p, &g_SysWork.playerBoneCoords_890[HarryBone_Head].workm, g_SysWork.playerWork_4C.player_0.model_0.anim_4.status_0);

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
        ang.vx = Math_AngleNormalize(Q12_ANGLE_FROM_Q8(w_p->cur_near_road_2B8.road_p_0->fix_ang_x_16));
        ang.vy = Math_AngleNormalize(Q12_ANGLE_FROM_Q8(w_p->cur_near_road_2B8.road_p_0->fix_ang_y_17));
        ang.vz = Q12_ANGLE(0.0f);

        vwAngleToVector(&vec, &ang, Q12(0.25f));

        // TODO: `<< 4`?
        watch_tgt_pos->vx = (vec.vx * 16) + w_p->cam_pos_50.vx;
        watch_tgt_pos->vy = (vec.vy * 16) + w_p->cam_pos_50.vy;
        watch_tgt_pos->vz = (vec.vz * 16) + w_p->cam_pos_50.vz;
    }
    else
    {
        chara_to_cam_dist = Vc_VectorMagnitudeCalc(w_p->chara_pos_114.vx - w_p->cam_pos_50.vx,
                                                   Q12(0.0f),
                                                   w_p->chara_pos_114.vz - w_p->cam_pos_50.vz);

        switch (cur_rd_area_size)
        {
            case VC_AREA_TINY:
                tgt_watch_cir_r     = Q12(1.0f);
                tgt_watch_cir_r_ext = Q12(3.0f);
                break;

            case VC_AREA_SMALL:
                tgt_watch_cir_r     = Q12(1.0f);
                tgt_watch_cir_r_ext = Q12(3.0f);
                break;

            default:
                tgt_watch_cir_r     = Q12(2.5f);
                tgt_watch_cir_r_ext = Q12(5.5f);
                break;
        }

        switch (cam_mv_type)
        {
            default:
            case VC_MV_SETTLE:
            case VC_MV_SELF_VIEW:
                tgt_chara2watch_cir_dist = Q12(0.0f);
                break;

            case VC_MV_CHASE:
            case VC_MV_THROUGH_DOOR:
                tgt_chara2watch_cir_dist = Q12(0.0f);
                if (chara_to_cam_dist < (tgt_watch_cir_r + tgt_watch_cir_r_ext))
                {
                    tgt_chara2watch_cir_dist = (tgt_watch_cir_r + tgt_watch_cir_r_ext) - chara_to_cam_dist;
                }
                break;
        }

        watch_y = Q4_TO_Q12(vcWork.cur_near_road_2B8.road_p_0->ofs_watch_hy_14) + w_p->chara_bottom_y_120;
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
    vertical_angle = (vertical_angle >= Q12_ANGLE(-70.0f)) ? ((vertical_angle <= Q12_ANGLE(70.0f)) ? vertical_angle : Q12_ANGLE(70.0f)) : Q12_ANGLE(-70.0f);

    ratan2(delta_x, delta_z);

    sys_work = &g_SysWork;

    vwMatrixToAngleYXZ(&cam_ang, head_mat);
    angle_delta_y = Math_AngleNormalize(cam_ang.vy - sys_work->playerWork_4C.player_0.rotation_24.vy);

    // 4-step angle adjustment based on hardcoded anim statuses.

    switch (anim_status)
    {
        case ANIM_STATUS(HarryAnim_RunForward, false):
        case ANIM_STATUS(HarryAnim_RunForward, true):
            break;

        case ANIM_STATUS(HarryAnim_LookAround, false):
        case ANIM_STATUS(HarryAnim_LookAround, true):
            if (w_p->nearest_enemy_2DC != NULL)
            {
                cam_ang.vz = Q12_ANGLE(0.0f);
            }
            break;

        default:
            cam_ang.vz >>= 1;
            break;
    }

    switch (anim_status)
    {
        case ANIM_STATUS(HarryAnim_FallForward, false):
        case ANIM_STATUS(HarryAnim_FallForward, true):
        case ANIM_STATUS(HarryAnim_FallBackward, false):
        case ANIM_STATUS(HarryAnim_FallBackward, true):
            break;

        default:
            cam_ang.vy = g_SysWork.playerWork_4C.player_0.rotation_24.vy;
            break;

        case ANIM_STATUS(HarryAnim_LookAround, false):
        case ANIM_STATUS(HarryAnim_LookAround, true):
            if (w_p->nearest_enemy_2DC != NULL)
            {
                cam_ang.vy = g_SysWork.playerWork_4C.player_0.rotation_24.vy;
            }
            else
            {
                cam_ang.vy += Q12_ANGLE(30.0f);
            }
            break;

        case ANIM_STATUS(HarryAnim_Idle, false):
        case ANIM_STATUS(HarryAnim_Idle, true):
            abs_angle_delta_y = angle_delta_y;
            if (angle_delta_y < Q12_ANGLE(0.0f))
            {
                abs_angle_delta_y = -angle_delta_y;
            }

            if (abs_angle_delta_y > Q12_ANGLE(4.0f))
            {
                corrected_angle_y = ((abs_angle_delta_y - Q12_ANGLE(4.0f)) >> 3) + Q12_ANGLE(4.0f);
                if (angle_delta_y < Q12_ANGLE(0.0f))
                {
                    corrected_angle_y = -corrected_angle_y;
                }
            }
            else
            {
                corrected_angle_y = angle_delta_y;
            }

            cam_ang.vy = g_SysWork.playerWork_4C.player_0.rotation_24.vy + corrected_angle_y;
            break;

        case ANIM_STATUS(HarryAnim_WalkForward, false):
        case ANIM_STATUS(HarryAnim_WalkForward, true):
        case ANIM_STATUS(HarryAnim_RunForward, false):
        case ANIM_STATUS(HarryAnim_RunForward, true):
        case ANIM_STATUS(HarryAnim_TurnLeft, false):
        case ANIM_STATUS(HarryAnim_TurnLeft, true):
        case ANIM_STATUS(HarryAnim_TurnRight, false):
        case ANIM_STATUS(HarryAnim_TurnRight, true):
            angle_delta_y = angle_delta_y >> 3;
            if (angle_delta_y >= Q12_ANGLE(-10.0f))
            {
                corrected_angle_y = angle_delta_y;
                if (corrected_angle_y > Q12_ANGLE(10.0f))
                {
                    corrected_angle_y = Q12_ANGLE(10.0f);
                }
            }
            else
            {
                corrected_angle_y = Q12_ANGLE(-10.0f);
            }

            cam_ang.vy = g_SysWork.playerWork_4C.player_0.rotation_24.vy + corrected_angle_y;
            break;
    }

    switch (anim_status)
    {
        case ANIM_STATUS(HarryAnim_WalkForward, false):
            break;

        case ANIM_STATUS(HarryAnim_IdleExhausted, false):
        case ANIM_STATUS(HarryAnim_IdleExhausted, true):
            cam_ang.vx = cam_ang.vx >> 1;

        case ANIM_STATUS(HarryAnim_Idle, false):
        case ANIM_STATUS(HarryAnim_Idle, true):
            cam_ang.vx -= Q12_ANGLE(8.0f);
            break;

        case ANIM_STATUS(HarryAnim_LookAround, false):
        case ANIM_STATUS(HarryAnim_LookAround, true):
            if (w_p->nearest_enemy_2DC != NULL)
            {
                cam_ang.vx = Q12_ANGLE(-7.0f);
            }
            else
            {
                cam_ang.vx -= Q12_ANGLE(8.0f);
            }
            break;

        case ANIM_STATUS(HarryAnim_TurnLeft, false):
        case ANIM_STATUS(HarryAnim_TurnLeft, true):
        case ANIM_STATUS(HarryAnim_TurnRight, false):
        case ANIM_STATUS(HarryAnim_TurnRight, true):
            temp_dir = (g_SysWork.playerWork_4C.player_0.rotation_24.vy >> 7) & 0xF;
            if (temp_dir == 0 || temp_dir == 5)
            {
                cam_ang.vx -= Q12_ANGLE(1.0f);
            }

            cam_ang.vx -= Q12_ANGLE(6.0f);
            break;
    }

    switch (anim_status)
    {
        default:
            cam_ang.vx = Q12_MULT(vertical_angle, Q12_ANGLE(252.0f));
            break;

        case ANIM_STATUS(HarryAnim_WalkForward, false):
        case ANIM_STATUS(HarryAnim_WalkForward, true):
        case ANIM_STATUS(HarryAnim_RunForward, false):
        case ANIM_STATUS(HarryAnim_RunForward, true):
        case ANIM_STATUS(HarryAnim_TurnLeft, false):
        case ANIM_STATUS(HarryAnim_TurnLeft, true):
        case ANIM_STATUS(HarryAnim_TurnRight, false):
        case ANIM_STATUS(HarryAnim_TurnRight, true):
        case ANIM_STATUS(HarryAnim_LookAround, false):
        case ANIM_STATUS(HarryAnim_LookAround, true):
        case ANIM_STATUS(HarryAnim_Idle, false):
        case ANIM_STATUS(HarryAnim_Idle, true):
            cam_ang.vx = cam_ang.vx + (vertical_angle >> 1);
            break;
    }

    limitRange(cam_ang.vx, Q12_ANGLE(-80.0f), Q12_ANGLE(80.0f));

    *watch_tgt_ang_z_p += Math_MulFixed(Math_AngleNormalize(cam_ang.vz - *watch_tgt_ang_z_p), effect_rate, Q12_SHIFT);

    new_x = w_p->cam_pos_50.vx + Q12_MULT(Math_Cos(cam_ang.vx), Q12_MULT(dist_to_target, Math_Sin(cam_ang.vy)));
    new_z = w_p->cam_pos_50.vz + Q12_MULT(Math_Cos(cam_ang.vx), Q12_MULT(dist_to_target, Math_Cos(cam_ang.vy)));
    new_y = w_p->cam_pos_50.vy - Q12_MULT(dist_to_target, Math_Sin(cam_ang.vx));

    watch_tgt_pos->vx += Math_MulFixed(new_x - watch_tgt_pos->vx, effect_rate, Q12_SHIFT);
    watch_tgt_pos->vy += Math_MulFixed(new_y - watch_tgt_pos->vy, effect_rate, Q12_SHIFT);
    watch_tgt_pos->vz += Math_MulFixed(new_z - watch_tgt_pos->vz, effect_rate, Q12_SHIFT);
}

void vcMakeFarWatchTgtPos(VECTOR3* watch_tgt_pos, VC_WORK* w_p, VC_AREA_SIZE_TYPE cur_rd_area_size) // 0x800832B4
{
    s_Collision     coll;
    q19_12          dist;
    q19_12          ofs_y;
    q19_12          lim_y;
    q19_12          watch_y;
    q19_12          use_dist;
    q19_12          adj_dist;
    s_SubCharacter* sc_p;

    if (cur_rd_area_size == VC_AREA_TINY)
    {
        use_dist = Q12(2.8f);
    }
    else if (cur_rd_area_size == VC_AREA_SMALL)
    {
        use_dist = Q12(5.5f);
    }
    else
    {
        use_dist = Q12(10.0f);
    }

    watch_y = w_p->chara_pos_114.vy - Q12(0.8f);

    if (w_p->nearest_enemy_2DC != NULL)
    {
        sc_p = w_p->nearest_enemy_2DC;

        dist = w_p->nearest_enemy_xz_dist_2E0;

        if (dist < Q12(1.7f))
        {
            adj_dist = (dist * Q12(-0.7f)) / Q12(1.7f);
        }
        else
        {
            adj_dist = Q12(-0.7f);
        }

        dist += adj_dist;

        // TODO: `CLAMP` or `MIN`/`MAX`?
        if (dist < use_dist)
        {
            use_dist = dist;
        }

        if (use_dist < Q12(0.4f))
        {
            use_dist = Q12(0.4f);
        }

        // Compute look-at Y anchor.
        ofs_y = Q8_TO_Q12(CHARA_FILE_INFOS[sc_p->model_0.charaId_0].cameraOffsetY_C_2);
        switch (CHARA_FILE_INFOS[sc_p->model_0.charaId_0].cameraAnchor_C_0)
        {
            default:
            case CameraAnchor_Character:
                watch_y = sc_p->position_18.vy + ofs_y;
                break;

            case CameraAnchor_Ground:
                Collision_Get(&coll, sc_p->position_18.vx, sc_p->position_18.vz);

                // If no valid ground, fall back on character Y position.
                if (coll.field_8 == 0)
                {
                    watch_y = sc_p->position_18.vy + ofs_y;
                }
                // Otherwise, use ground height.
                else
                {
                    watch_y = coll.groundHeight_0 + ofs_y;
                }
                break;

            case CameraAnchor_Camera:
                watch_y = w_p->watch_pos_y_2E4 + ofs_y;
                break;
        }

        lim_y = (w_p->nearest_enemy_xz_dist_2E0 >> 1) - Q12(0.5f);

        if ((w_p->chara_pos_114.vy + lim_y) < watch_y)
        {
            watch_y = w_p->chara_pos_114.vy + lim_y;
        }
    }

    watch_tgt_pos->vx = w_p->chara_pos_114.vx + Q12_MULT(use_dist, Math_Sin(w_p->chara_eye_ang_y_144));
    watch_tgt_pos->vy = watch_y;
    watch_tgt_pos->vz = w_p->chara_pos_114.vz + Q12_MULT(use_dist, Math_Cos(w_p->chara_eye_ang_y_144));
}

void vcSetWatchTgtXzPos(VECTOR3* watch_pos, const VECTOR3* center_pos, const VECTOR3* cam_pos, q19_12 tgt_chara2watch_cir_dist, q19_12 tgt_watch_cir_r, q3_12 watch_cir_ang_y) // 0x800834A8
{
    q3_12  cam2chr_ang;
    q19_12 chr2watch_x;
    q19_12 chr2watch_z;

    cam2chr_ang = ratan2(center_pos->vx - cam_pos->vx, center_pos->vz - cam_pos->vz);

    chr2watch_x = Math_MulFixed(tgt_chara2watch_cir_dist, Math_Sin(cam2chr_ang),     Q12_SHIFT) +
                  Math_MulFixed(tgt_watch_cir_r,          Math_Sin(watch_cir_ang_y), Q12_SHIFT);
    chr2watch_z = Math_MulFixed(tgt_chara2watch_cir_dist, Math_Cos(cam2chr_ang),     Q12_SHIFT) +
                  Math_MulFixed(tgt_watch_cir_r,          Math_Cos(watch_cir_ang_y), Q12_SHIFT);

    watch_pos->vx = center_pos->vx + chr2watch_x;
    watch_pos->vz = center_pos->vz + chr2watch_z;
}

void vcSetWatchTgtYParam(VECTOR3* watch_pos, VC_WORK* w_p, s32 cam_mv_type, q19_12 watch_y) // 0x800835C0
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
    s16 max_cam_ang_x;
    s32 dist;
    s16 cam_ang_x;

    max_cam_ang_x = ratan2(cam_pos->vy + Q12(5.0f), Q12(13.0f)) - ratan2(g_GameWork.gsScreenHeight_58A / 2, sy);
    dist          = Vc_VectorMagnitudeCalc(watch_pos->vx - cam_pos->vx, 0, watch_pos->vz - cam_pos->vz);
    cam_ang_x     = ratan2(-watch_pos->vy + cam_pos->vy, dist);

    if (cam_ang_x > max_cam_ang_x)
    {
        // TODO: What Q format?
        s32 ofs_y     = Q4(((FP_FROM(dist, Q4_SHIFT)) * Math_Sin(max_cam_ang_x)) / Math_Cos(max_cam_ang_x));
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

    // @hack Not sure what's going on here, doesn't seem to work as if statement.
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
            vcMakeBasicCamTgtMvVec(&tgt_vec, &ideal_pos, w_p, Q12(1.0f));
            break;
    }

    w_p->cam_tgt_mv_ang_y_10C = ratan2(tgt_vec.vx, tgt_vec.vz);

    if (g_DeltaTime != Q12(0.0f) || vcWork.flags_8 & VC_WARP_CAM_TGT_F)
    {
        w_p->cam_tgt_pos_44.vx += tgt_vec.vx;
        w_p->cam_tgt_pos_44.vy += tgt_vec.vy;
        w_p->cam_tgt_pos_44.vz += tgt_vec.vz;

        w_p->cam_tgt_velo_100.vx = Q12(tgt_vec.vx) / g_DeltaTime;
        w_p->cam_tgt_velo_100.vy = Q12(tgt_vec.vy) / g_DeltaTime;
        w_p->cam_tgt_velo_100.vz = Q12(tgt_vec.vz) / g_DeltaTime;

        w_p->cam_tgt_spd_110 = Vc_VectorMagnitudeCalc(w_p->cam_tgt_velo_100.vx, 0, w_p->cam_tgt_velo_100.vz);
        return;
    }

    w_p->cam_tgt_velo_100.vx = Q12(0.0f);
    w_p->cam_tgt_velo_100.vz = Q12(0.0f);
    w_p->cam_tgt_spd_110     = Q12(0.0f);
}

s32 vcRetMaxTgtMvXzLen(VC_WORK* w_p, VC_CAM_MV_PARAM* cam_mv_prm_p) // 0x8008395C
{
    #define SPEED_XZ_MIN Q12(2.2f)

    s32 max_spd_xz;

    max_spd_xz = (w_p->chara_mv_spd_13C + Q12(1.0f)) + abs(w_p->chara_ang_spd_y_142 * 8);
    max_spd_xz = (max_spd_xz < SPEED_XZ_MIN) ? SPEED_XZ_MIN : max_spd_xz;
    max_spd_xz = (cam_mv_prm_p->max_spd_xz > max_spd_xz) ? max_spd_xz : cam_mv_prm_p->max_spd_xz;

    return Math_MulFixed(max_spd_xz, g_DeltaTime, Q12_SHIFT);
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
        chara2cam_ang_y = w_p->chara_eye_ang_y_144   + Q12_ANGLE(140.0f);
        ideal_pos->vy   = w_p->chara_head_pos_130.vy + Q12(0.07f);
    }
    else
    {
        chara2cam_ang_y = w_p->chara_eye_ang_y_144   + Q12_ANGLE(170.0f);
        ideal_pos->vy   = w_p->chara_head_pos_130.vy + Q12(0.1f);
    }

    ideal_pos->vx = w_p->chara_head_pos_130.vx + Q12_MULT(Math_Sin(chara2cam_ang_y), Q12_ANGLE(64.8f));
    ideal_pos->vz = w_p->chara_head_pos_130.vz + Q12_MULT(Math_Cos(chara2cam_ang_y), Q12_ANGLE(64.8f));
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

    cam_angle_vec.vx = Q12_ANGLE_FROM_Q8(w_p->cur_near_road_2B8.road_p_0->fix_ang_x_16);
    cam_angle_vec.vy = Q12_ANGLE_FROM_Q8(w_p->cur_near_road_2B8.road_p_0->fix_ang_y_17);
    cam_angle_vec.vz = Q12_ANGLE(0.0f);

    // Not `Q12` distances ahead? Could be different Q format.

    limit_area = &w_p->cur_near_road_2B8.road_p_0->lim_rd_8;
    vcGetXZSumDistFromLimArea(&dist_x_to_lim_area, &dist_z_to_lim_area, w_p->chara_pos_114.vx, w_p->chara_pos_114.vz,
                              Q4_TO_Q12(w_p->cur_near_road_2B8.rd_14.min_hx), Q4_TO_Q12(w_p->cur_near_road_2B8.rd_14.max_hx),
                              Q4_TO_Q12(w_p->cur_near_road_2B8.rd_14.min_hz), Q4_TO_Q12(w_p->cur_near_road_2B8.rd_14.max_hz), 0);

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

    offset_dist       = (max_dist_to_lim_area >> 1) + Q12(1.5f);
    chara_to_cam_dist = Vc_VectorMagnitudeCalc(w_p->chara_pos_114.vx - w_p->cam_pos_50.vx,
                                               Q12(0.0f),
                                               w_p->chara_pos_114.vz - w_p->cam_pos_50.vz);

    if (chara_to_cam_dist >= Q12(7.0f))
    {
        cam_offset_forward = Q12(0.0f);
    }
    else if (chara_to_cam_dist > Q12(1.5f))
    {
        cam_offset_forward = Q12_MULT(Q12((chara_to_cam_dist - Q12(7.0f))) / Q12(-5.5f), Q12(0.7f));
    }
    else
    {
        cam_offset_forward = Q12(0.7f);
    }

    ideal_pos->vx = w_p->chara_pos_114.vx +
                    Q12_MULT(cam_offset_forward, Math_Sin(w_p->chara_eye_ang_y_144)) +
                    Q12_MULT(offset_dist, Math_Sin(cam_angle_vec.vy + Q12_ANGLE(180.0f)));
    ideal_pos->vz = w_p->chara_pos_114.vz +
                    Q12_MULT(cam_offset_forward, Math_Cos(w_p->chara_eye_ang_y_144)) +
                    Q12_MULT(offset_dist, Math_Cos(cam_angle_vec.vy + Q12_ANGLE(180.0f)));
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

    if (w_p->through_door_10.active_f_0)
    {
        if (w_p->through_door_activate_init_f_C)
        {
            offset_forward = Q12(-1.3f);
            offset_lateral = Q12(0.0f);
        }
        else
        {
            switch (Map_TypeGet())
            {
                case 10:
                case 13:
                case 14:
                    angle_threshold = Q12_ANGLE(15.0f);
                    offset_forward  = Q12(0.85f);
                    offset_lateral  = Q12(0.6f);
                    offset_scale    = Q12(0.7f);
                    break;

                default:
                    angle_threshold = Q12_ANGLE(45.0f);
                    offset_forward  = Q12(0.75f);
                    offset_lateral  = Q12(0.7f);
                    offset_scale    = Q12(0.6f);
                    break;
            }

            angle_diff_abs = Math_AngleNormalize(w_p->chara_eye_ang_y_144 - through_door_param->rail_ang_y_8);
            if (angle_diff_abs < Q12_ANGLE(0.0f))
            {
                angle_diff_abs = -angle_diff_abs;
            }

            if ((angle_diff_abs - angle_threshold) < Q12_ANGLE(0.0f))
            {
                delta_angle_clamped = Q12_ANGLE(0.0f);
            }
            else
            {
                delta_angle_clamped = angle_diff_abs - angle_threshold;
            }

            // TODO: Demagic angle math.
            offset_forward = offset_forward +
                             FP_MULTIPLY(-offset_lateral,
                                          Math_Cos(((delta_angle_clamped * (0x800000 / (Q12_ANGLE(180.0f) - angle_threshold))) * 16) >> 16), Q12_SHIFT);
            offset_lateral = Q12_MULT(-offset_scale, Math_Sin(w_p->chara_eye_ang_y_144 - through_door_param->rail_ang_y_8));
        }

        ideal_pos->vx = through_door_param->rail_sta_pos_C.vx +
                        Q12_MULT(offset_forward, Math_Sin(through_door_param->rail_ang_y_8)) +
                        Q12_MULT(offset_lateral, Math_Cos(through_door_param->rail_ang_y_8));
        ideal_pos->vz = through_door_param->rail_sta_pos_C.vz +
                        Q12_MULT(offset_forward, Math_Cos(through_door_param->rail_ang_y_8)) +
                        Q12_MULT(offset_lateral, -Math_Sin(through_door_param->rail_ang_y_8));
        ideal_pos->vy = through_door_param->rail_sta_pos_C.vy;
    }
}

void vcMakeIdealCamPosUseVC_ROAD_DATA(VECTOR3* ideal_pos, VC_WORK* w_p, enum _VC_AREA_SIZE_TYPE cur_rd_area_size) // 0x80083F34
{
    #define ANGLE_DELTA_RANGE Q12_ANGLE(12.0f)

    q19_12             temp_x;
    q19_12             temp_z;
    q3_12              base_angle;
    q19_12             chara_pos_y;
    q3_12              delta_angle;
    q19_12             cam_pos_y;
    q23_8              horizontal_distance_fp;
    q23_8              blend_max_dist;
    q23_8              blend_min_dist;
    q19_12             delta_y_clamped;
    q19_12             final_cam_dist;
    q19_12             default_cam_dist;
    VC_NEAR_ROAD_DATA* near_road_data;
    VC_ROAD_DATA*      road_data;

    base_angle  = w_p->chara_eye_ang_y_144 + Q12_ANGLE(180.0f);
    delta_angle = Math_AngleNormalize(w_p->cam_chara2ideal_ang_y_FE - base_angle);

    if (abs(w_p->chara_ang_spd_y_142) > Q12_ANGLE(20.0f))
    {
        delta_angle = CLAMP(delta_angle, -ANGLE_DELTA_RANGE, ANGLE_DELTA_RANGE);
    }
    else if (delta_angle >= Q12_ANGLE(0.0f))
    {
        delta_angle = ANGLE_DELTA_RANGE;
    }
    else
    {
        delta_angle = -ANGLE_DELTA_RANGE;
    }

    w_p->cam_chara2ideal_ang_y_FE = Math_AngleNormalize(delta_angle + base_angle);

    if (cur_rd_area_size == VC_AREA_TINY)
    {
        default_cam_dist = Q12(1.8f);
    }
    else if (cur_rd_area_size == VC_AREA_SMALL)
    {
        default_cam_dist = Q12(2.0f);
    }
    else
    {
        default_cam_dist = Q12(2.5f);
    }

    near_road_data = &w_p->cur_near_road_2B8;

    ideal_pos->vx = w_p->chara_pos_114.vx + Q12_MULT(default_cam_dist, Math_Sin(w_p->cam_chara2ideal_ang_y_FE));
    ideal_pos->vy = w_p->chara_top_y_124  - Q12(0.4f);
    ideal_pos->vz = w_p->chara_pos_114.vz + Q12_MULT(default_cam_dist, Math_Cos(w_p->cam_chara2ideal_ang_y_FE));

    cam_pos_y   = w_p->cam_pos_50.vy;
    chara_pos_y = w_p->chara_pos_114.vy;

    temp_x = Q12(0.0f);
    temp_z = Q12(0.0f);

    delta_y_clamped = cam_pos_y - chara_pos_y;
    if (delta_y_clamped < Q12(0.0f))
    {
        delta_y_clamped = chara_pos_y - cam_pos_y;
    }

    delta_y_clamped -= Q12(1.5f);
    if (delta_y_clamped < Q12(0.0f))
    {
        delta_y_clamped = Q12(0.0f);
    }

    road_data = w_p->cur_near_road_2B8.road_p_0;

    ideal_pos->vy = CLAMP(ideal_pos->vy, Q4_TO_Q12(road_data->lim_rd_min_hy_13), Q4_TO_Q12(road_data->lim_rd_max_hy_12));

    temp_x = w_p->chara_pos_114.vx;
    temp_z = w_p->chara_pos_114.vz;

    vcAdjustXzInLimAreaUsingMIN_IN_ROAD_DIST(&temp_x, &temp_z, &near_road_data->rd_14);

    horizontal_distance_fp = Q12_TO_Q8(Vc_VectorMagnitudeCalc(temp_x - w_p->chara_pos_114.vx,
                                                                    delta_y_clamped,
                                                                    temp_z - w_p->chara_pos_114.vz));

    if (cur_rd_area_size == VC_AREA_TINY)
    {
        blend_min_dist = Q8(0.7f);
        blend_max_dist = Q8(2.0f);
    }
    else if (cur_rd_area_size < VC_AREA_WIDE)
    {
        blend_min_dist = Q8(0.7f);
        blend_max_dist = Q8(3.0f);
    }
    else
    {
        blend_min_dist = Q8(2.0f);
        blend_max_dist = Q8(5.0f);
    }

    if (blend_max_dist >= horizontal_distance_fp)
    {
        if (blend_min_dist < horizontal_distance_fp)
        {
            final_cam_dist = default_cam_dist + (((Q8(6.4f) - default_cam_dist) * (horizontal_distance_fp - blend_min_dist)) / (blend_max_dist - blend_min_dist));
        }
        else
        {
            final_cam_dist = default_cam_dist;
        }
    }
    else
    {
        final_cam_dist = Q12(0.4f);
    }

    ideal_pos->vx = w_p->chara_pos_114.vx + Math_MulFixed(final_cam_dist, Math_Sin(w_p->cam_chara2ideal_ang_y_FE), Q12_SHIFT);
    ideal_pos->vz = w_p->chara_pos_114.vz + Math_MulFixed(final_cam_dist, Math_Cos(w_p->cam_chara2ideal_ang_y_FE), Q12_SHIFT);

    vcAdjustXzInLimAreaUsingMIN_IN_ROAD_DIST(&ideal_pos->vx, &ideal_pos->vz, &near_road_data->rd_14);
}

void vcAdjustXzInLimAreaUsingMIN_IN_ROAD_DIST(s32* x_p, s32* z_p, VC_LIMIT_AREA* lim_p) // 0x80084210
{
    q19_12 min_z;
    q19_12 min_x;
    q19_12 max_z;
    q19_12 max_x;
    q19_12 x = *x_p;
    q19_12 z = *z_p;

    min_x = Q4_TO_Q12(lim_p->min_hx) + MIN_IN_ROAD_DIST;
    max_x = Q4_TO_Q12(lim_p->max_hx) - MIN_IN_ROAD_DIST;
    min_z = Q4_TO_Q12(lim_p->min_hz) + MIN_IN_ROAD_DIST;
    max_z = Q4_TO_Q12(lim_p->max_hz) - MIN_IN_ROAD_DIST;

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

    now2ideal_tgt_dist  = Vc_VectorMagnitudeCalc(temp_s1, Q12(0.0f), temp_s0);
    now2ideal_tgt_ang_y = ratan2(temp_s1, temp_s0);

    if (now2ideal_tgt_dist < max_tgt_mv_xz_len)
    {
        tgt_mv_vec->vx = ideal_pos->vx - w_p->cam_tgt_pos_44.vx;
        tgt_mv_vec->vz = ideal_pos->vz - w_p->cam_tgt_pos_44.vz;
    }
    else
    {
        tgt_mv_vec->vx = Q12_MULT(max_tgt_mv_xz_len, Math_Sin(now2ideal_tgt_ang_y));
        tgt_mv_vec->vz = Q12_MULT(max_tgt_mv_xz_len, Math_Cos(now2ideal_tgt_ang_y));
    }

    if (g_DeltaTime == Q12(0.0f) && !(vcWork.flags_8 & VC_WARP_CAM_TGT_F))
    {
        tgt_mv_vec->vy = Q12(0.0f);
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
                                           Q12(0.0f),
                                           w_p->chara_pos_114.vz - w_p->cam_tgt_pos_44.vz);

    dist = CLAMP(to_chara_dist, Q12(1.2f), Q12(7.0f));

    // TODO: Weird multiplier?
    near_ratio = Math_MultiplyFloatPrecise(Q12(7.0f) - dist, 0.1724f, Q12_SHIFT);
    near_ratio = CLAMP(near_ratio, Q12(0.0f), Q12(1.0f));

    switch (w_p->cur_near_road_2B8.road_p_0->mv_y_type_11)
    {
        case VC_MV_CHASE:
        default:
            abs_ofs_y = (to_chara_dist - Q12(0.3f)) >> 2;
            if (abs_ofs_y < Q12(0.0f))
            {
                abs_ofs_y = Q12(0.0f);
            }

            max_tgt_y = (abs_ofs_y + w_p->chara_top_y_124) - Q12(0.25f);
            min_tgt_y = (w_p->chara_top_y_124 - abs_ofs_y) - Q12(0.25f);
            break;

        case VC_MV_SETTLE:
            min_tgt_y = Math_MulFixed(Q4_TO_Q12(cur_rd_p->lim_rd_max_hy_12),
                                      Q12(1.0f) - near_ratio,
                                      Q12_SHIFT) +
                        Math_MulFixed(Q4_TO_Q12(cur_rd_p->lim_rd_min_hy_13),
                                      near_ratio,
                                      Q12_SHIFT);
            max_tgt_y = min_tgt_y;
            break;

        case VC_MV_FIX_ANG:
            min_tgt_y = Math_MulFixed(Q4_TO_Q12(cur_rd_p->lim_rd_min_hy_13),
                                      Q12(1.0f) - near_ratio,
                                      Q12_SHIFT) +
                        Math_MulFixed(Q4_TO_Q12(cur_rd_p->lim_rd_max_hy_12),
                                      near_ratio,
                                      Q12_SHIFT);
            max_tgt_y = min_tgt_y;
            break;

        case VC_MV_SELF_VIEW:
            min_tgt_y = Q4_TO_Q12(cur_rd_p->lim_rd_min_hy_13);
            max_tgt_y = Q4_TO_Q12(cur_rd_p->lim_rd_max_hy_12);
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
    if (flip_dist > Q12(0.0f))
    {
        mv_len = flip_dist;
        if (flip_dist > Q12(0.5f))
        {
            mv_len = Q12(0.5f);
        }

        // `chk_pos` is unused?
        chk_pos.vx = pre_tgt_pos.vx + Math_MulFixed(mv_len, Math_Sin(flip_ang_y), Q12_SHIFT);
        chk_pos.vz = pre_tgt_pos.vz + Math_MulFixed(mv_len, Math_Cos(flip_ang_y), Q12_SHIFT);

        if (w_p->cur_near_road_2B8.road_p_0->flags_10 & VC_RD_MARGE_ROAD_F)
        {
            chk_near_dist = vcGetNearestNEAR_ROAD_DATA(&use_nearest_p, VC_CHK_NEAREST_ROAD_TYPE, w_p->cur_near_road_2B8.road_p_0->rd_type_11, &pre_tgt_pos, w_p, true);
            if (use_nearest_p == NULL)
            {
                use_nearest_p = &vcNullNearRoad;
            }
            else if (chk_near_dist > Q12(0.0f))
            {
                use_nearest_p = &w_p->cur_near_road_2B8;
            }
        }
        else
        {
            use_nearest_p = &w_p->cur_near_road_2B8;
        }

        post_tgt_pos.vx = pre_tgt_pos.vx + Q12_MULT(flip_dist, Math_Sin(flip_ang_y));
        post_tgt_pos.vz = pre_tgt_pos.vz + Q12_MULT(flip_dist, Math_Cos(flip_ang_y));

        min_x = Q4_TO_Q12(use_nearest_p->rd_14.min_hx) + MIN_IN_ROAD_DIST;
        max_x = Q4_TO_Q12(use_nearest_p->rd_14.max_hx) - MIN_IN_ROAD_DIST;
        min_z = Q4_TO_Q12(use_nearest_p->rd_14.min_hz) + MIN_IN_ROAD_DIST;
        max_z = Q4_TO_Q12(use_nearest_p->rd_14.max_hz) - MIN_IN_ROAD_DIST;

        if (max_x < min_x)
        {
            min_x = (min_x + max_x) >> 1; // `/ 2`.
            max_x = min_x;
        }
        if (max_z < min_z)
        {
            min_z = (min_z + max_z) >> 1; // `/ 2`.
            max_z = min_z;
        }

        post_tgt_pos.vx = CLAMP(post_tgt_pos.vx, min_x, max_x);
        post_tgt_pos.vz = CLAMP(post_tgt_pos.vz, min_z, max_z);

        tgt_mv_vec->vx = post_tgt_pos.vx - w_p->cam_tgt_pos_44.vx;
        tgt_mv_vec->vz = post_tgt_pos.vz - w_p->cam_tgt_pos_44.vz;

        if (max_tgt_mv_xz_len < Vc_VectorMagnitudeCalc(tgt_mv_vec->vx, Q12(0.0f), tgt_mv_vec->vz))
        {
            ang_y          = ratan2(tgt_mv_vec->vx, tgt_mv_vec->vz);
            tgt_mv_vec->vx = Math_MulFixed(max_tgt_mv_xz_len, Math_Sin(ang_y), Q12_SHIFT);
            tgt_mv_vec->vz = Math_MulFixed(max_tgt_mv_xz_len, Math_Cos(ang_y), Q12_SHIFT);
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
    relative_angle_y = Math_AngleNormalize(target_angle_y - chara_eye_ang_y);

    abs_relative_angle_y = relative_angle_y;
    if (relative_angle_y < Q12_ANGLE(0.0f))
    {
        abs_relative_angle_y = -relative_angle_y;
    }

    switch (cur_rd_area_size)
    {
        case VC_AREA_SMALL:
            base_radius = Q12(1.0f);
            break;

        case VC_AREA_TINY:
            base_radius = Q12(0.7f);
            break;

        case VC_AREA_WIDE:
            base_radius = Q12(1.0f);
            break;

        default:
            base_radius = Q12(0.7f);
            break;
    }

    desired_radius = FP_FROM(base_radius * vwOresenHokan(excl_r_ary, ARRAY_SIZE(excl_r_ary), abs_relative_angle_y, 0, Q12_ANGLE(180.0f)), Q12_SHIFT);

    if (*old_cam_excl_area_r_p != NO_VALUE)
    {
        delta_radius = desired_radius - *old_cam_excl_area_r_p;
        min_step     = Q12_MULT_PRECISE(g_DeltaTime, Q12_ANGLE(-180.0f));
        if (delta_radius < min_step)
        {
            delta_radius = min_step;
        }

        desired_radius = *old_cam_excl_area_r_p + delta_radius;
    }

    *old_cam_excl_area_r_p = desired_radius;

    distance_to_chara = Vc_VectorMagnitudeCalc(in_pos->vx - chara_pos->vx, Q12(0.0f), in_pos->vz - chara_pos->vz);

    exclusion_overlap = Q12(0.0f);
    if (distance_to_chara < desired_radius)
    {
        exclusion_overlap = desired_radius - distance_to_chara;
    }

    *flip_ang_y_p = target_angle_y;
    return exclusion_overlap;
}

void vcGetUseWatchAndCamMvParam(VC_WATCH_MV_PARAM** watch_mv_prm_pp, VC_CAM_MV_PARAM** cam_mv_prm_pp, s32 self_view_eff_rate, VC_WORK* w_p) // 0x80084A34
{
    s32              add_ang_accel_y;
    VC_CAM_MV_PARAM* cam_mv_prm_stg_p;

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

        add_ang_accel_y = Q12_MULT_PRECISE(w_p->chara_mv_spd_13C, Q12_ANGLE(360.0f));
        add_ang_accel_y = CLAMP(add_ang_accel_y, Q12_ANGLE(0.0f), Q12_ANGLE(720.0f));

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
        w_p->cam_velo_60.vx  = Q12(0.0f);
        w_p->cam_velo_60.vy  = Q12(0.0f);
        w_p->cam_velo_60.vz  = Q12(0.0f);
        return;
    }

    // SH2 removes this multiply and uses `accel_y` directly. Maybe 0.4f/1.0f were tunable defines and compiler removed them.
    dec_spd_per_dist_xz = Math_MultiplyFloatPrecise(cam_mv_prm_p->accel_xz, 0.4f, Q12_SHIFT);
    dec_spd_per_dist_y  = Math_MultiplyFloatPrecise(cam_mv_prm_p->accel_y,  1.0f, Q12_SHIFT);

    vwRenewalXZVelocityToTargetPos(&w_p->cam_velo_60.vx, &w_p->cam_velo_60.vz, &w_p->cam_pos_50,
                                   &w_p->cam_tgt_pos_44, Q12(0.1f), cam_mv_prm_p->accel_xz,
                                   cam_mv_prm_p->max_spd_xz, dec_spd_per_dist_xz, Q12(12.0f));

    w_p->cam_velo_60.vy  = vwRetNewVelocityToTargetVal(w_p->cam_velo_60.vy, w_p->cam_pos_50.vy, w_p->cam_tgt_pos_44.vy,
                                                       cam_mv_prm_p->accel_y, cam_mv_prm_p->max_spd_y, dec_spd_per_dist_y);
    w_p->cam_mv_ang_y_5C = ratan2(w_p->cam_velo_60.vx, w_p->cam_velo_60.vz);

    w_p->cam_pos_50.vx += Math_MulFixed(w_p->cam_velo_60.vx, g_DeltaTime, Q12_SHIFT);
    w_p->cam_pos_50.vy += Math_MulFixed(w_p->cam_velo_60.vy, g_DeltaTime, Q12_SHIFT);
    w_p->cam_pos_50.vz += Math_MulFixed(w_p->cam_velo_60.vz, g_DeltaTime, Q12_SHIFT);
}

void vcRenewalCamMatAng(VC_WORK* w_p, VC_WATCH_MV_PARAM* watch_mv_prm_p, VC_CAM_MV_TYPE cam_mv_type, bool visible_chara_f) // 0x80084D54
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

    Math_RotMatrixZxyNeg(&w_p->base_cam_ang_C8, &new_base_matT);
    TransposeMatrix(&new_base_matT, &new_base_matT);
    vcMakeOfsCamTgtAng(&ofs_tgt_ang, &new_base_matT, w_p);
    if (visible_chara_f)
    {
        vcMakeOfsCam2CharaBottomAndTopAngByBaseMatT(&ofs_cam2chara_btm_ang, &ofs_cam2chara_top_ang, &new_base_matT,
                                                    &w_p->cam_pos_50, &w_p->chara_pos_114, w_p->chara_bottom_y_120,
                                                    w_p->chara_top_y_124);
        vcAdjCamOfsAngByCharaInScreen(&ofs_tgt_ang, &ofs_cam2chara_btm_ang, &ofs_cam2chara_top_ang, w_p);
    }

    if (w_p->flags_8 & VC_WARP_WATCH_F)
    {
        w_p->ofs_cam_ang_B8        = ofs_tgt_ang;
        w_p->ofs_cam_ang_spd_C0.vx = Q12(0.0f);
        w_p->ofs_cam_ang_spd_C0.vy = Q12(0.0f);
        w_p->ofs_cam_ang_spd_C0.vz = Q12(0.0f);
    }
    else
    {
        vcAdjCamOfsAngByOfsAngSpd(&w_p->ofs_cam_ang_B8, &w_p->ofs_cam_ang_spd_C0, &ofs_tgt_ang, watch_mv_prm_p);
    }

    vcMakeCamMatAndCamAngByBaseAngAndOfsAng(&w_p->cam_mat_ang_8E, &w_p->cam_mat_98, &new_base_cam_ang, &w_p->ofs_cam_ang_B8, &w_p->cam_pos_50);
}

void vcMakeNewBaseCamAng(SVECTOR* new_base_ang, VC_CAM_MV_TYPE cam_mv_type, VC_WORK* w_p) // 0x80084EDC
{
    static const s32 D_8002AAE0[] = { 0, 170, 682, 1251, 1251, 0, 0 }; // Last 2 could be compiler-added padding, but are needed for match.

    s32 sp18[5];
    s16 temp_a0_3;
    s16 temp_v0;
    s16 new_base_ang_x;
    s16 new_base_ang_y;
    s16 var_v1_2;
    s16 temp_a0_2;
    s16 angle;
    s16 temp_t0;
    s16 temp_v0_2;
    s16 temp_v1;
    s16 temp_v1_2;
    s32 deltaZ;
    s32 deltaY;
    s32 deltaX;

    deltaX = Q12_TO_Q8(w_p->watch_tgt_pos_7C.vx - w_p->cam_pos_50.vx);
    deltaY = Q12_TO_Q8(w_p->watch_tgt_pos_7C.vy - w_p->cam_pos_50.vy);
    deltaZ = Q12_TO_Q8(w_p->watch_tgt_pos_7C.vz - w_p->cam_pos_50.vz);

    if (w_p->flags_8 & VC_USER_WATCH_F)
    {
        new_base_ang->vx = Q12_ANGLE(0.0f);
        new_base_ang->vy = Q12_ANGLE(0.0f);
        new_base_ang->vz = Q12_ANGLE(0.0f);
    }
    else if (cam_mv_type != VC_MV_SETTLE)
    {
        new_base_ang->vx = Q12_ANGLE(0.0f);
        new_base_ang->vy = Q12_ANGLE(0.0f);
        new_base_ang->vz = Q12_ANGLE(0.0f);
    }
    else
    {
        angle   = ratan2(-deltaY, Vc_VectorMagnitudeCalc(deltaX, Q12(0.0f), deltaZ));
        temp_v0 = ratan2(deltaX, deltaZ);

        temp_v1   = Q12_ANGLE_FROM_Q8(w_p->cur_near_road_2B8.road_p_0->fix_ang_x_16);
        temp_a0_2 = Q12_ANGLE_FROM_Q8(w_p->cur_near_road_2B8.road_p_0->fix_ang_y_17);

        temp_v1_2 = Q12_ANGLE_NORM_S(temp_v0 - temp_v1);
        temp_v0_2 = Q12_ANGLE_NORM_S(temp_v0 - temp_a0_2);

        if (temp_v1_2 >= Q12_ANGLE(0.0f) &&
            temp_v0_2 <= Q12_ANGLE(0.0f))
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
            if (w_p->chara_mv_spd_13C != Q12(0.0f) &&
                angle < Q12_ANGLE(75.0f) &&
                angle > Q12_ANGLE(-75.0f))
            {
                temp_t0        = Q12_ANGLE_NORM_S(new_base_ang_y - w_p->base_cam_ang_C8.vy);
                temp_a0_3      = Q12_MULT_PRECISE(g_DeltaTime, Q12_ANGLE(120.0f));
                var_v1_2       = CLAMP(temp_t0, -temp_a0_3, temp_a0_3);
                new_base_ang_y = w_p->base_cam_ang_C8.vy + var_v1_2;
            }
            else
            {
                new_base_ang_y = w_p->base_cam_ang_C8.vy;
            }
        }

        new_base_ang_x = angle;
        if (new_base_ang_x < Q12_ANGLE(0.0f))
        {
            new_base_ang_x = -new_base_ang_x;
        }

        memcpy(sp18, D_8002AAE0, ARRAY_SIZE(sp18) * sizeof(s32));
        new_base_ang_x = vwOresenHokan(sp18, ARRAY_SIZE(sp18), new_base_ang_x, 0, Q12(0.25f));
        new_base_ang_x = CLAMP(new_base_ang_x, Q12_ANGLE(0.0f), Q12_ANGLE(90.0f));

        if (angle < Q12_ANGLE(0.0f))
        {
            new_base_ang_x = -new_base_ang_x;
        }

        new_base_ang->vx = new_base_ang_x;
        new_base_ang->vy = new_base_ang_y;
        new_base_ang->vz = Q12_ANGLE(0.0f);
    }
}

void vcRenewalBaseCamAngAndAdjustOfsCamAng(VC_WORK* w_p, SVECTOR* new_base_cam_ang) // 0x800851B0
{
    MATRIX old_base_mat;
    MATRIX new_base_mat;
    MATRIX new_base_matT;
    MATRIX ofs_mat;     // } Names for these two might be switched.
    MATRIX adj_ofs_mat; // }

    ofs_mat = GsIDMATRIX;
    Math_RotMatrixZxyNeg(&w_p->base_cam_ang_C8, &old_base_mat);
    Math_RotMatrixZxyNeg(new_base_cam_ang, &new_base_mat);
    TransposeMatrix(&new_base_mat, &new_base_matT);
    Math_RotMatrixZxyNeg(&w_p->ofs_cam_ang_B8, &adj_ofs_mat);
    MulMatrix0(&new_base_matT, &old_base_mat, &ofs_mat);
    MulMatrix2(&ofs_mat, &adj_ofs_mat);
    vwMatrixToAngleYXZ(&w_p->ofs_cam_ang_B8, &adj_ofs_mat);
    w_p->base_cam_ang_C8 = *new_base_cam_ang;
}

void vcMakeOfsCamTgtAng(SVECTOR* ofs_tgt_ang, MATRIX* base_matT, VC_WORK* w_p) // 0x800852C8
{
    SVECTOR vec;

    vec.vx = Q12_TO_Q8(w_p->watch_tgt_pos_7C.vx - w_p->cam_pos_50.vx);
    vec.vy = Q12_TO_Q8(w_p->watch_tgt_pos_7C.vy - w_p->cam_pos_50.vy);
    vec.vz = Q12_TO_Q8(w_p->watch_tgt_pos_7C.vz - w_p->cam_pos_50.vz);

    ApplyMatrixSV(base_matT, &vec, &vec);
    vwVectorToAngle(ofs_tgt_ang, &vec);
    ofs_tgt_ang->vz = w_p->watch_tgt_ang_z_8C;
}

void vcMakeOfsCam2CharaBottomAndTopAngByBaseMatT(SVECTOR* ofs_cam2chara_btm_ang, SVECTOR* ofs_cam2chara_top_ang,
                                                 MATRIX* base_matT, VECTOR3* cam_pos, VECTOR3* chara_pos,
                                                 s32 chara_bottom_y, s32 chara_top_y) // 0x80085358
{
    SVECTOR vec;

    vec.vx = Q12_TO_Q8(chara_pos->vx  - cam_pos->vx);
    vec.vy = Q12_TO_Q8(chara_bottom_y - cam_pos->vy);
    vec.vz = Q12_TO_Q8(chara_pos->vz  - cam_pos->vz);
    ApplyMatrixSV(base_matT, &vec, &vec);
    vwVectorToAngle(ofs_cam2chara_btm_ang, &vec);

    vec.vx = Q12_TO_Q8(chara_pos->vx - cam_pos->vx);
    vec.vy = Q12_TO_Q8(chara_top_y   - cam_pos->vy);
    vec.vz = Q12_TO_Q8(chara_pos->vz - cam_pos->vz);
    ApplyMatrixSV(base_matT, &vec, &vec);
    vwVectorToAngle(ofs_cam2chara_top_ang, &vec);
}

void vcAdjCamOfsAngByCharaInScreen(SVECTOR* cam_ang, SVECTOR* ofs_cam2chara_btm_ang, SVECTOR* ofs_cam2chara_top_ang, VC_WORK* w_p) // 0x80085460
{
    // SH2 dwarf names.
    q3_12 adj_cam_ang_x;
    q3_12 var_a1; // Probably temp for `adj_cam_ang_x`.
    q3_12 watch2chr_ofs_ang_y;
    q3_12 watch2chr_bottom_ofs_ang_x;
    q3_12 watch2chr_top_ofs_ang_x;
    q3_12 adj_cam_ang_y;

    watch2chr_bottom_ofs_ang_x = Math_AngleNormalize(ofs_cam2chara_btm_ang->vx - cam_ang->vx);
    watch2chr_top_ofs_ang_x    = Math_AngleNormalize(ofs_cam2chara_top_ang->vx - cam_ang->vx);
    watch2chr_ofs_ang_y        = Math_AngleNormalize(ofs_cam2chara_top_ang->vy - cam_ang->vy);

    adj_cam_ang_y = (watch2chr_ofs_ang_y > w_p->scr_half_ang_wx_2E) ?
                    (watch2chr_ofs_ang_y - w_p->scr_half_ang_wx_2E) :
                    ((-w_p->scr_half_ang_wx_2E > watch2chr_ofs_ang_y) ? (w_p->scr_half_ang_wx_2E + watch2chr_ofs_ang_y) : Q12_ANGLE(0.0f));

    /*
    var_a1 = watch2chr_bottom_ofs_ang_x + w_p->scr_half_ang_wy_2C;
    if (watch2chr_bottom_ofs_ang_x >= -w_p->scr_half_ang_wy_2C)
    {
        var_a1 = 0;
    }*/

    // TODO: var_a1 should probably be merged into adj_cam_ang_x somehow.
    var_a1 = (watch2chr_bottom_ofs_ang_x >= -w_p->scr_half_ang_wy_2C) ? Q12_ANGLE(0.0f) : (watch2chr_bottom_ofs_ang_x + w_p->scr_half_ang_wy_2C);

    if (w_p->scr_half_ang_wy_2C < (watch2chr_top_ofs_ang_x - var_a1))
    {
        var_a1 = watch2chr_top_ofs_ang_x - w_p->scr_half_ang_wy_2C;
    }

    if (var_a1 < Q12_ANGLE(-30.0f))
    {
        adj_cam_ang_x = Q12_ANGLE(-30.0f);
    }
    else
    {
        adj_cam_ang_x = var_a1;
        if (var_a1 > Q12_ANGLE(30.0f))
        {
            adj_cam_ang_x = Q12_ANGLE(30.0f);
        }
    }

    cam_ang->vy += adj_cam_ang_y;
    cam_ang->vx  = adj_cam_ang_x + cam_ang->vx;
}

void vcAdjCamOfsAngByOfsAngSpd(SVECTOR* ofs_ang, SVECTOR* ofs_ang_spd, SVECTOR* ofs_tgt_ang, VC_WATCH_MV_PARAM* prm_p) // 0x8008555C
{
    SVECTOR unused;
    VECTOR3 max_spd_dec_per_dist;

    unused.vx = Math_AngleNormalize(ofs_tgt_ang->vx - ofs_ang->vx);
    unused.vy = Math_AngleNormalize(ofs_tgt_ang->vy - ofs_ang->vy);
    unused.vz = Math_AngleNormalize(ofs_tgt_ang->vz - ofs_ang->vz);

    max_spd_dec_per_dist.vx = Math_MultiplyFloatPrecise(prm_p->ang_accel_x, 8.0f, Q12_SHIFT);
    max_spd_dec_per_dist.vy = Math_MultiplyFloatPrecise(prm_p->ang_accel_y, 3.0f, Q12_SHIFT);
    max_spd_dec_per_dist.vz = Math_MultiplyFloatPrecise(prm_p->ang_accel_y, 3.3f, Q12_SHIFT);

    ofs_ang_spd->vx = vwRetNewAngSpdToTargetAng(ofs_ang_spd->vx, ofs_ang->vx, ofs_tgt_ang->vx, prm_p->ang_accel_x, prm_p->max_ang_spd_x, max_spd_dec_per_dist.vx);
    ofs_ang_spd->vy = vwRetNewAngSpdToTargetAng(ofs_ang_spd->vy, ofs_ang->vy, ofs_tgt_ang->vy, prm_p->ang_accel_y, prm_p->max_ang_spd_y, max_spd_dec_per_dist.vy);
    ofs_ang_spd->vz = vwRetNewAngSpdToTargetAng(ofs_ang_spd->vz, ofs_ang->vz, ofs_tgt_ang->vz, Q12(0.4f), Q12_ANGLE(144.0f), Q12(3.0f));

    ofs_ang->vx += Q12_MULT_PRECISE(ofs_ang_spd->vx, g_DeltaTime);
    ofs_ang->vy += Q12_MULT_PRECISE(ofs_ang_spd->vy, g_DeltaTime);
    ofs_ang->vz += Q12_MULT_PRECISE(ofs_ang_spd->vz, g_DeltaTime);
}

void vcMakeCamMatAndCamAngByBaseAngAndOfsAng(SVECTOR* cam_mat_ang, MATRIX* cam_mat, SVECTOR* base_cam_ang, SVECTOR* ofs_cam_ang, VECTOR3* cam_pos) // 0x800857EC
{
    MATRIX base_mat;
    MATRIX ofs_mat;

    cam_mat->t[0] = Q12_TO_Q8(cam_pos->vx);
    cam_mat->t[1] = Q12_TO_Q8(cam_pos->vy);
    cam_mat->t[2] = Q12_TO_Q8(cam_pos->vz);

    Math_RotMatrixZxyNeg(base_cam_ang, &base_mat);
    Math_RotMatrixZxyNeg(ofs_cam_ang, &ofs_mat);
    MulMatrix0(&base_mat, &ofs_mat, cam_mat);
    vwMatrixToAngleYXZ(cam_mat_ang, cam_mat);
}

void vcSetDataToVwSystem(VC_WORK* w_p, VC_CAM_MV_TYPE cam_mv_type) // 0x80085884
{
    MATRIX  noise_cam_mat;
    MATRIX  noise_mat;
    SVECTOR noise_ang;

    if (w_p->field_D8)
    {
        w_p->field_D8 = false;
        vwSetCoordRefAndEntou(&g_SysWork.playerBoneCoords_890[HarryBone_Head],
                              Q12(0.0f), Q12(-0.05f), Q12(0.3f),
                              Q12_ANGLE(180.0f), Q12_ANGLE(0.0f), Q12(-0.2f), Q12(1.0f));
    }
    else if (w_p->field_FC)
    {
        w_p->field_FC = false;
        vwSetViewInfoDirectMatrix(NULL, &w_p->field_DC);
    }
    else if (cam_mv_type == VC_MV_SELF_VIEW)
    {
        vcSelfViewTimer += g_DeltaTime;

        noise_ang.vx = vcCamMatNoise(4, FP_RADIAN((PI / 18.0f) * 5.0f), FP_RADIAN((PI / 9.0f) *  4.0f), vcSelfViewTimer);
        noise_ang.vy = vcCamMatNoise(2, FP_RADIAN((PI / 9.0f)  * 2.0f), FP_RADIAN((PI / 9.0f) * -8.0f), vcSelfViewTimer);
        noise_ang.vz = Q12_ANGLE(0.0f);
        Math_RotMatrixZxyNeg(&noise_ang, &noise_mat);

        noise_mat.m[0][0] += vcCamMatNoise(12, FP_RADIAN((PI / 18.0f) * 7.0f),  FP_RADIAN(PI),                    vcSelfViewTimer);
        noise_mat.m[0][1] += vcCamMatNoise(12, FP_RADIAN(PI / 3.0f),            FP_RADIAN((PI / 9.0f)  * -8.0f),  vcSelfViewTimer);
        noise_mat.m[0][2] += vcCamMatNoise(12, FP_RADIAN(PI / 3.0f),            FP_RADIAN((PI / 9.0f)  *  4.0f),  vcSelfViewTimer);
        noise_mat.m[1][0] += vcCamMatNoise(12, FP_RADIAN((PI / 18.0f) * 5.0f),  FP_RADIAN((PI / 18.0f) *  5.0f),  vcSelfViewTimer);
        noise_mat.m[1][1] += vcCamMatNoise(12, FP_RADIAN(PI),                   FP_RADIAN((PI / 9.0f)  *  2.0f),  vcSelfViewTimer);
        noise_mat.m[1][2] += vcCamMatNoise(12, FP_RADIAN((PI / 36.0f) * 13.0f), FP_RADIAN((PI / 18.0f) * -17.0f), vcSelfViewTimer);
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

s32 vcCamMatNoise(s32 noise_w, s32 ang_spd1, s32 ang_spd2, q19_12 vcSelfViewTimer) // 0x80085A7C
{
    s32 noise;

    noise = Math_Cos(Q12_MULT_PRECISE(ang_spd1, vcSelfViewTimer)) + Math_Cos(Q12_MULT_PRECISE(ang_spd2, vcSelfViewTimer));
    noise = noise >> 1;

    return Q12_MULT(noise_w, noise);
}

s32 Vc_VectorMagnitudeCalc(q19_12 posX, q19_12 posY, q19_12 posZ) // 0x80085B1C
{
    q19_12 mag;
    s32    shift;

    mag   = MAX(MAX(ABS(posX), ABS(posY)), ABS(posZ));
    shift = Math_MagnitudeShiftGet(mag);
    posX   >>= shift;
    posY   >>= shift;
    posZ   >>= shift;
    return SquareRoot0(SQUARE(posX) + SQUARE(posY) + SQUARE(posZ)) << shift;
}

q19_12 vcGetXZSumDistFromLimArea(s32* out_vec_x_p, s32* out_vec_z_p, q19_12 chk_wld_x, q19_12 chk_wld_z,
                                 q19_12 lim_min_x, q19_12 lim_max_x, q19_12 lim_min_z, q19_12 lim_max_z, bool can_ret_minus_dist_f) // 0x80085C80
{
    q19_12 cntr_x;
    q19_12 cntr_z;
    q19_12 x_dist;
    q19_12 z_dist;
    q19_12 ret_dist;

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
        *out_vec_x_p = Q12(0.0f);
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
        *out_vec_z_p = Q12(0.0f);
        if (chk_wld_z >= ((lim_max_z + lim_min_z) >> 1))
        {
            z_dist = chk_wld_z - lim_max_z;
        }
        else
        {
            z_dist = lim_min_z - chk_wld_z;
        }
    }

    if (x_dist >= Q12(0.0f))
    {
        ret_dist = x_dist;
        if (z_dist >= Q12(0.0f))
        {
            ret_dist += z_dist;
        }
    }
    else
    {
        ret_dist = z_dist;
        if (ret_dist < Q12(0.0f) && ret_dist < x_dist)
        {
            ret_dist = x_dist;
        }
    }

    if (!can_ret_minus_dist_f && ret_dist < Q12(0.0f))
    {
        ret_dist = Q12(0.0f);
    }

    return ret_dist;
}
