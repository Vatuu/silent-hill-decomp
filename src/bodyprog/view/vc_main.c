#include "game.h"

#include "bodyprog/vw_system.h"
#include "bodyprog/math.h"

#define MIN_IN_ROAD_DIST TILE_UNIT(16.0f) // vcGetMinInRoadDist() in SH2, hardcoded to TILE_UNIT(16.0f) in SH1.

static inline s16 shAngleRegulate(s32 a)
{
    return (a << 0x14) >> 0x14;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/view/vc_main", vcInitVCSystem);

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
    // TODO: Bitfield access?
    return (vcWork.cur_near_road_2B8.road_p_0->cam_mv_type_14 >> 8) & 0xF;
}

void func_80080A30(s32 arg0) // 0x80080A30
{
    vcWork.field_2E4 = arg0;
}

s32 func_80080A3C() // 0x80080A3C
{
    return vcWork.field_2E4;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/view/vc_main", vcSetFirstCamWork);

void func_80080B58(GsCOORDINATE2* a1, SVECTOR* a2, VECTOR3* a3) // 0x80080B58
{
    MATRIX mat;

    vcWork.field_FC = 1;

    func_80049984(a1, &vcWork.field_DC);
    func_80096C94(a2, &mat);
    MulMatrix(&vcWork.field_DC, &mat);

    vcWork.field_DC.t[0] = FROM_FIXED(a3->vx, Q4_SHIFT);
    vcWork.field_DC.t[1] = FROM_FIXED(a3->vy, Q4_SHIFT);
    vcWork.field_DC.t[2] = FROM_FIXED(a3->vz, Q4_SHIFT);
}

void vcWorkSetFlags(VC_FLAGS enable, VC_FLAGS disable) // 0x80080BF8
{
    vcWork.flags_8 = (vcWork.flags_8 | enable) & ~disable;
}

s32 func_80080C18(s32 arg0) // 0x80080C18
{
    s32 prev_val              = vcWork.watch_tgt_max_y_88;
    vcWork.watch_tgt_max_y_88 = arg0;
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

INCLUDE_ASM("asm/bodyprog/nonmatchings/view/vc_main", vcExecCamera);

INCLUDE_ASM("asm/bodyprog/nonmatchings/view/vc_main", vcSetAllNpcDeadTimer);

INCLUDE_ASM("asm/bodyprog/nonmatchings/view/vc_main", vcRetSmoothCamMvF);

INCLUDE_ASM("asm/bodyprog/nonmatchings/view/vc_main", vcRetCurCamMvType);

INCLUDE_ASM("asm/bodyprog/nonmatchings/view/vc_main", func_8008150C);

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
    if (prm_p->timer_4 > TILE_UNIT(19.2f) && w_p->nearest_enemy_xz_dist_2E0 < TILE_UNIT(19.2f))
    {
        return 1;
    }

    if (rail2chara_dist > TILE_UNIT(36.8f))
    {
        return 1;
    }

    if (rail2chara_dist > TILE_UNIT(8.0f))
    {
        abs_ofs_ang_y = shAngleRegulate(w_p->chara_eye_ang_y_144 -
                        ratan2(w_p->chara_pos_114.vx - w_p->through_door_10.rail_sta_pos_C.vx, w_p->chara_pos_114.vz - w_p->through_door_10.rail_sta_pos_C.vz));

        if (abs_ofs_ang_y < 0)
        {
            abs_ofs_ang_y = -abs_ofs_ang_y;
        }

        if (abs_ofs_ang_y > DEG_TO_FPA(4.375f))
        {
            return 1;
        }
    }

    return 0;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/view/vc_main", vcRetFarWatchRate);

INCLUDE_ASM("asm/bodyprog/nonmatchings/view/vc_main", vcRetSelfViewEffectRate);

INCLUDE_ASM("asm/bodyprog/nonmatchings/view/vc_main", vcSetFlagsByCamMvType);

void vcPreSetDataInVC_WORK(VC_WORK* w_p, VC_ROAD_DATA* vc_road_ary_list) // 0x80081B6C
{
    if (g_DeltaTime != 0)
    {
        if (vcWork.flags_8 & VC_PRS_F_VIEW_F)
        {
            vcWork.flags_8 |= VC_OLD_PRS_F_VIEW_F;
        }
        else
        {
            vcWork.flags_8 &= ~VC_OLD_PRS_F_VIEW_F;
        }

        if (g_ControllerPtr0->btns_held_C & g_GameWorkPtr1->controllerBinds_0.view)
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
    vcSetNearRoadAryByCharaPos(w_p, vc_road_ary_list, 0x14000, 0, w_p->nearest_enemy_p_2DC != NULL);
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
            prm_p->rail_sta_pos_C.vy        = w_p->chara_grnd_y_12C - TILE_UNIT(31.2f);
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

                prm_p->timer_4 += g_DeltaTime;
            }
            break;
    }
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/view/vc_main", vcSetNearestEnemyDataInVC_WORK);

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
            return TILE_UNIT(5.6f);

        case VC_RD_TYPE_EVENT:
            return TILE_UNIT(2.4f);
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
            w_p->watch_tgt_pos_7C.vx += MUL_FIXED(far_watch_rate, far_watch_pos.vx - w_p->watch_tgt_pos_7C.vx, Q12_SHIFT);
            w_p->watch_tgt_pos_7C.vy += MUL_FIXED(far_watch_rate, far_watch_pos.vy - w_p->watch_tgt_pos_7C.vy, Q12_SHIFT);
            w_p->watch_tgt_pos_7C.vz += MUL_FIXED(far_watch_rate, far_watch_pos.vz - w_p->watch_tgt_pos_7C.vz, Q12_SHIFT);
        }
    }
    else
    {
        w_p->watch_tgt_pos_7C = far_watch_pos;
    }

    vcMixSelfViewEffectToWatchTgtPos(&w_p->watch_tgt_pos_7C, &w_p->watch_tgt_ang_z_8C, self_view_eff_rate,
                                     w_p, &g_SysWork.hero_neck_930.workm, g_SysWork.player_4C.character.animIdx_4);

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
    s16 max_cam_ang_x = ratan2(cam_pos->vy + TILE_UNIT(80.0f), TILE_UNIT(208.0f)) - ratan2(g_GameWork.gsScreenHeight_58A / 2, sy);
    s32 dist          = Math_VectorMagnitude(watch_pos->vx - cam_pos->vx, 0, watch_pos->vz - cam_pos->vz);
    s32 cam_ang_x     = ratan2(-watch_pos->vy + cam_pos->vy, dist) * FP_ANGLE_COUNT;

    if ((max_cam_ang_x * FP_ANGLE_COUNT) < cam_ang_x)
    {
        s32 ofs_y     = TO_FIXED(((FROM_FIXED(dist, Q4_SHIFT)) * shRsin(max_cam_ang_x)) / shRcos(max_cam_ang_x), Q4_SHIFT);
        watch_pos->vy = cam_pos->vy - ofs_y;
    }
}

void vcAutoRenewalCamTgtPos(VC_WORK* w_p, VC_CAM_MV_TYPE cam_mv_type, VC_CAM_MV_PARAM* cam_mv_prm_p, VC_ROAD_FLAGS cur_rd_flags, VC_AREA_SIZE_TYPE cur_rd_area_size) // 0x800836E8
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
                vcCamTgtMvVecIsFlipedFromCharaFront(
                    &tgt_vec, w_p, max_tgt_mv_xz_len, cur_rd_area_size);
            }

            if (cam_mv_type != VC_MV_THROUGH_DOOR)
            {
                vcAdjTgtMvVecYByCurNearRoad(&tgt_vec, w_p);
            }
            break;

        case 1:
            vcMakeBasicCamTgtMvVec(&tgt_vec, &ideal_pos, w_p, TILE_UNIT(16.0f));
            break;
    }

    w_p->cam_tgt_mv_ang_y_10C = ratan2(tgt_vec.vx, tgt_vec.vz);

    if (g_DeltaTime != 0 || vcWork.flags_8 & VC_WARP_CAM_TGT_F)
    {
        w_p->cam_tgt_pos_44.vx += tgt_vec.vx;
        w_p->cam_tgt_pos_44.vy += tgt_vec.vy;
        w_p->cam_tgt_pos_44.vz += tgt_vec.vz;

        w_p->cam_tgt_velo_100.vx = TO_FIXED(tgt_vec.vx, Q12_SHIFT) / g_DeltaTime;
        w_p->cam_tgt_velo_100.vy = TO_FIXED(tgt_vec.vy, Q12_SHIFT) / g_DeltaTime;
        w_p->cam_tgt_velo_100.vz = TO_FIXED(tgt_vec.vz, Q12_SHIFT) / g_DeltaTime;

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

    max_spd_xz = w_p->chara_mv_spd_13C + TILE_UNIT(16.0f) + abs(w_p->chara_ang_spd_y_142 * 8);
    max_spd_xz = (max_spd_xz < TILE_UNIT(35.2f)) ? TILE_UNIT(35.2f) : max_spd_xz;
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

    if (g_GameWorkPtr0->optViewMode_29)
    {
        chara2cam_ang_y = w_p->chara_eye_ang_y_144 + DEG_TO_FPA(8.75f);
        ideal_pos->vy   = w_p->chara_head_pos_130.vy + TILE_UNIT(1.12f);
    }
    else
    {
        chara2cam_ang_y = w_p->chara_eye_ang_y_144 + DEG_TO_FPA(10.625f);
        ideal_pos->vy   = w_p->chara_head_pos_130.vy + TILE_UNIT(1.6f);
    }

    ideal_pos->vx = w_p->chara_head_pos_130.vx + MUL_FIXED(shRsin(chara2cam_ang_y), DEG_TO_FPA(4.05f), Q12_SHIFT);
    ideal_pos->vz = w_p->chara_head_pos_130.vz + MUL_FIXED(shRcos(chara2cam_ang_y), DEG_TO_FPA(4.05f), Q12_SHIFT);
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

    min_x = TO_FIXED(lim_p->min_hx, Q8_SHIFT) + MIN_IN_ROAD_DIST;
    max_x = TO_FIXED(lim_p->max_hx, Q8_SHIFT) - MIN_IN_ROAD_DIST;
    min_z = TO_FIXED(lim_p->min_hz, Q8_SHIFT) + MIN_IN_ROAD_DIST;
    max_z = TO_FIXED(lim_p->max_hz, Q8_SHIFT) - MIN_IN_ROAD_DIST;

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
        tgt_mv_vec->vx = MUL_FIXED(max_tgt_mv_xz_len, shRsin(now2ideal_tgt_ang_y), Q12_SHIFT);
        tgt_mv_vec->vz = MUL_FIXED(max_tgt_mv_xz_len, shRcos(now2ideal_tgt_ang_y), Q12_SHIFT);
    }

    if (g_DeltaTime == 0 && !(vcWork.flags_8 & VC_WARP_CAM_TGT_F))
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
        if (flip_dist > TILE_UNIT(8.0f))
        {
            mv_len = TILE_UNIT(8.0f);
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

        post_tgt_pos.vx = pre_tgt_pos.vx + MUL_FIXED(flip_dist, shRsin(flip_ang_y), Q12_SHIFT);
        post_tgt_pos.vz = pre_tgt_pos.vz + MUL_FIXED(flip_dist, shRcos(flip_ang_y), Q12_SHIFT);

        min_x = TO_FIXED(use_nearest_p->rd_14.min_hx, Q8_SHIFT) + MIN_IN_ROAD_DIST;
        max_x = TO_FIXED(use_nearest_p->rd_14.max_hx, Q8_SHIFT) - MIN_IN_ROAD_DIST;
        min_z = TO_FIXED(use_nearest_p->rd_14.min_hz, Q8_SHIFT) + MIN_IN_ROAD_DIST;
        max_z = TO_FIXED(use_nearest_p->rd_14.max_hz, Q8_SHIFT) - MIN_IN_ROAD_DIST;

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

        add_ang_accel_y = FROM_FIXED((s64)w_p->chara_mv_spd_13C * DEG_TO_FPA(22.5f), Q12_SHIFT);
        add_ang_accel_y = CLAMP(add_ang_accel_y, 0, DEG_TO_FPA(45.0f));

        vcWatchMvPrmSt.ang_accel_y += add_ang_accel_y;
    }

    cam_mv_prm_stg_p = (w_p->flags_8 & VC_USER_CAM_F) ? &w_p->user_cam_mv_prm_34 : &cam_mv_prm_user;
    *cam_mv_prm_pp   = cam_mv_prm_stg_p;
}

void vcRenewalCamData(VC_WORK* w_p, VC_CAM_MV_PARAM* cam_mv_prm_p) // 0x80084BD8
{
    s32 dec_spd_per_dist_xz;
    s32 dec_spd_per_dist_y;

    if (w_p->flags_8 & VC_WARP_CAM_F) // & 4
    {
        w_p->cam_mv_ang_y_5C = ratan2(w_p->cam_tgt_pos_44.vx - w_p->cam_pos_50.vx, w_p->cam_tgt_pos_44.vz - w_p->cam_pos_50.vz);
        w_p->cam_pos_50      = w_p->cam_tgt_pos_44;
        w_p->cam_velo_60.vx  = 0;
        w_p->cam_velo_60.vy  = 0;
        w_p->cam_velo_60.vz  = 0;
        return;
    }

    dec_spd_per_dist_xz = Math_MulFixed(cam_mv_prm_p->accel_xz, 0x666, Q12_SHIFT);
    dec_spd_per_dist_y  = Math_MulFixed(cam_mv_prm_p->accel_y, 0x1000, Q12_SHIFT);

    vwRenewalXZVelocityToTargetPos(&w_p->cam_velo_60.vx, &w_p->cam_velo_60.vz, &w_p->cam_pos_50,
                                   &w_p->cam_tgt_pos_44, 0x199, cam_mv_prm_p->accel_xz,
                                   cam_mv_prm_p->max_spd_xz, dec_spd_per_dist_xz, 0xC000);

    w_p->cam_velo_60.vy  = vwRetNewVelocityToTargetVal(w_p->cam_velo_60.vy, w_p->cam_pos_50.vy, w_p->cam_tgt_pos_44.vy,
                                                       cam_mv_prm_p->accel_y, cam_mv_prm_p->max_spd_y, dec_spd_per_dist_y);
    w_p->cam_mv_ang_y_5C = ratan2(w_p->cam_velo_60.vx, w_p->cam_velo_60.vz);

    w_p->cam_pos_50.vx += Math_MulFixed(w_p->cam_velo_60.vx, g_DeltaTime, Q12_SHIFT);
    w_p->cam_pos_50.vy += Math_MulFixed(w_p->cam_velo_60.vy, g_DeltaTime, Q12_SHIFT);
    w_p->cam_pos_50.vz += Math_MulFixed(w_p->cam_velo_60.vz, g_DeltaTime, Q12_SHIFT);
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

    vec.vx = FROM_FIXED(w_p->watch_tgt_pos_7C.vx - w_p->cam_pos_50.vx, Q4_SHIFT);
    vec.vy = FROM_FIXED(w_p->watch_tgt_pos_7C.vy - w_p->cam_pos_50.vy, Q4_SHIFT);
    vec.vz = FROM_FIXED(w_p->watch_tgt_pos_7C.vz - w_p->cam_pos_50.vz, Q4_SHIFT);

    ApplyMatrixSV(base_matT, &vec, &vec);
    vwVectorToAngle(ofs_tgt_ang, &vec);
    ofs_tgt_ang->vz = w_p->watch_tgt_ang_z_8C;
}

void vcMakeOfsCam2CharaBottomAndTopAngByBaseMatT(SVECTOR* ofs_cam2chara_btm_ang, SVECTOR* ofs_cam2chara_top_ang,
                                                 MATRIX* base_matT, VECTOR3* cam_pos, VECTOR3* chara_pos,
                                                 s32 chara_bottom_y, s32 chara_top_y) // 0x80085358
{
    SVECTOR vec;

    vec.vx = FROM_FIXED(chara_pos->vx - cam_pos->vx, Q4_SHIFT);
    vec.vy = FROM_FIXED(chara_bottom_y - cam_pos->vy, Q4_SHIFT);
    vec.vz = FROM_FIXED(chara_pos->vz - cam_pos->vz, Q4_SHIFT);
    ApplyMatrixSV(base_matT, &vec, &vec);
    vwVectorToAngle(ofs_cam2chara_btm_ang, &vec);

    vec.vx = FROM_FIXED(chara_pos->vx - cam_pos->vx, Q4_SHIFT);
    vec.vy = FROM_FIXED(chara_top_y - cam_pos->vy, Q4_SHIFT);
    vec.vz = FROM_FIXED(chara_pos->vz - cam_pos->vz, Q4_SHIFT);
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

    adj_cam_ang_y = (watch2chr_ofs_ang_y > w_p->scr_half_ang_wx_2E) ? (watch2chr_ofs_ang_y - w_p->scr_half_ang_wx_2E) : ((-w_p->scr_half_ang_wx_2E > watch2chr_ofs_ang_y) ? (w_p->scr_half_ang_wx_2E + watch2chr_ofs_ang_y) : 0);

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

    // SH2 uses similar checks with 0.52359879 / 30 degrees.
    if (var_a1 < DEG_TO_FPA(-1.875f))
    {
        adj_cam_ang_x = DEG_TO_FPA(-1.875f);
    }
    else
    {
        adj_cam_ang_x = var_a1;
        if (var_a1 > DEG_TO_FPA(1.875f))
        {
            adj_cam_ang_x = DEG_TO_FPA(1.875f);
        }
    }

    cam_ang->vy += adj_cam_ang_y;
    cam_ang->vx = adj_cam_ang_x + cam_ang->vx;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/view/vc_main", vcAdjCamOfsAngByOfsAngSpd);

void vcMakeCamMatAndCamAngByBaseAngAndOfsAng(SVECTOR* cam_mat_ang, MATRIX* cam_mat, SVECTOR* base_cam_ang, SVECTOR* ofs_cam_ang, VECTOR3* cam_pos) // 0x800857EC
{
    MATRIX base_mat;
    MATRIX ofs_mat;

    cam_mat->t[0] = FROM_FIXED(cam_pos->vx, Q4_SHIFT);
    cam_mat->t[1] = FROM_FIXED(cam_pos->vy, Q4_SHIFT);
    cam_mat->t[2] = FROM_FIXED(cam_pos->vz, Q4_SHIFT);

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
        vwSetCoordRefAndEntou(&g_SysWork.hero_neck_930, 0, TILE_UNIT(-0.8f), TILE_UNIT(4.8f), DEG_TO_FPA(11.25f), DEG_TO_FPA(0.0f), TILE_UNIT(-3.2f), 0x1000);
    }
    else if (w_p->field_FC != 0)
    {
        w_p->field_FC = 0;
        vwSetViewInfoDirectMatrix(NULL, &w_p->field_DC);
    }
    else if (cam_mv_type == VC_MV_SELF_VIEW)
    {
        vcSelfViewTimer += g_DeltaTime;

        noise_ang.vx = vcCamMatNoise(4, DEG_TO_FPA(31.25f), DEG_TO_FPA(50.0f), vcSelfViewTimer);
        noise_ang.vy = vcCamMatNoise(2, DEG_TO_FPA(25.0f), DEG_TO_FPA(62.5f), vcSelfViewTimer);
        noise_ang.vz = 0;
        func_80096C94(&noise_ang, &noise_mat);

        noise_mat.m[0][0] += vcCamMatNoise(12, DEG_TO_FPA(43.75f), DEG_TO_FPA(56.25f), vcSelfViewTimer);
        noise_mat.m[0][1] += vcCamMatNoise(12, DEG_TO_FPA(37.5f), DEG_TO_FPA(62.5f), vcSelfViewTimer);
        noise_mat.m[0][2] += vcCamMatNoise(12, DEG_TO_FPA(37.5f), DEG_TO_FPA(50.0f), vcSelfViewTimer);
        noise_mat.m[1][0] += vcCamMatNoise(12, DEG_TO_FPA(31.25f), DEG_TO_FPA(31.25f), vcSelfViewTimer);
        noise_mat.m[1][1] += vcCamMatNoise(12, DEG_TO_FPA(56.25f), DEG_TO_FPA(25.0f), vcSelfViewTimer);
        noise_mat.m[1][2] += vcCamMatNoise(12, DEG_TO_FPA(40.625f), DEG_TO_FPA(59.375f), vcSelfViewTimer);
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

    noise = shRcos(MUL_FIXED(ang_spd1, (s64)vcSelfViewTimer, Q12_SHIFT)) + shRcos(MUL_FIXED(ang_spd2, (s64)vcSelfViewTimer, Q12_SHIFT));
    noise = noise >> 1;

    return MUL_FIXED(noise_w, noise, Q12_SHIFT);
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
