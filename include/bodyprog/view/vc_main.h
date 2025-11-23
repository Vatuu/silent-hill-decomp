#ifndef _BODYPROG_VIEW_VCMAIN_H
#define _BODYPROG_VIEW_VCMAIN_H

#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>

/** @brief Initializes the camera paths used in the active map.
 *
 * @param vc_road_ary_list Camera paths.
 */
void vcInitVCSystem(VC_ROAD_DATA* vc_road_ary_list);

void vcStartCameraSystem(void);

void vcEndCameraSystem(void);

s32 func_80080A10(void);

void func_80080A30(s32 arg0);

s32 func_80080A3C(void);

void vcSetFirstCamWork(VECTOR3* cam_pos, s16 chara_eye_ang_y, bool use_through_door_cam_f);

void func_80080B58(GsCOORDINATE2* arg0, SVECTOR* rot, VECTOR3* pos);

void vcWorkSetFlags(VC_FLAGS enable, VC_FLAGS disable);

s32  Vc_LookAtOffsetYMaxSet(s32 lookAtOffsetYMax);

void vcUserWatchTarget(VECTOR3* watch_tgt_pos, VC_WATCH_MV_PARAM* watch_prm_p, bool warp_watch_f);

void vcUserCamTarget(VECTOR3* cam_tgt_pos, VC_CAM_MV_PARAM* cam_prm_p, bool warp_cam_f);

void vcChangeProjectionValue(s16 scr_y);

void func_80080D68(void);

/** @brief Gets the current camera look-at position.
 *
 * @param watch_pos Output look-at position (Q19.12).
 */
void vcGetNowWatchPos(VECTOR3* watch_pos);

/** @brief Gets the current camera position.
 *
 * @param cam_pos Output camera position (Q19.12).
 */
void vcGetNowCamPos(VECTOR3* cam_pos);

/** @brief Sets camera flags to set up a warp? TODO: Unsure.
 *
 * @param warp_f Warp.
 */
void vcReturnPreAutoCamWork(bool warp_f);

void vcSetSubjChara(VECTOR3* chara_pos, q19_12 chara_bottom_y, q19_12 chara_top_y, q19_12 chara_grnd_y, VECTOR3* chara_head_pos,
                    q3_12 chara_mv_spd, q19_12 chara_mv_ang_y, q3_12 chara_ang_spd_y, q3_12 chara_eye_ang_y, q3_12 chara_eye_ang_wy, q19_12 chara_watch_xz_r);

s32 vcExecCamera(void);

void vcSetAllNpcDeadTimer(void);

s32 vcRetSmoothCamMvF(VECTOR3* old_pos, VECTOR3* now_pos, SVECTOR* old_ang, SVECTOR* now_ang);

VC_CAM_MV_TYPE vcRetCurCamMvType(VC_WORK* w_p);

bool func_8008150C(q19_12 posX, q19_12 posZ);

bool vcRetThroughDoorCamEndF(VC_WORK* w_p);

q19_12 vcRetFarWatchRate(s32 far_watch_button_prs_f, VC_CAM_MV_TYPE cur_cam_mv_type, VC_WORK* w_p);

s32 vcRetSelfViewEffectRate(VC_CAM_MV_TYPE cur_cam_mv_type, s32 far_watch_rate, VC_WORK* w_p);

void vcSetFlagsByCamMvType(VC_CAM_MV_TYPE cam_mv_type, s32 far_watch_rate, bool all_warp_f);

void vcPreSetDataInVC_WORK(VC_WORK* w_p, VC_ROAD_DATA* vc_road_ary_list);

void vcSetTHROUGH_DOOR_CAM_PARAM_in_VC_WORK(VC_WORK* w_p, THROUGH_DOOR_SET_CMD_TYPE set_cmd_type);

void vcSetNearestEnemyDataInVC_WORK(VC_WORK* w_p);

void vcSetNearRoadAryByCharaPos(VC_WORK* w_p, VC_ROAD_DATA* road_ary_list, s32 half_w, s32 unused, bool near_enemy_f);

s32  vcRetRoadUsePriority(VC_ROAD_TYPE rd_type, s32 unused);

bool vcSetCurNearRoadInVC_WORK(VC_WORK* w_p);

s32 vcGetBestNewCurNearRoad(VC_NEAR_ROAD_DATA** new_cur_pp, VC_CAM_CHK_TYPE chk_type, VECTOR3* pos, VC_WORK* w_p);

/** @brief Gets the closest camera path collision, outputting the result to `out_nearest_p_addr` and returning the distance to it.
 * TODO
 *
 * @param out_nearest_p_addr Output for the closest camera path collision.
 * @param chk_type 
 * @param rd_type 
 * @param pos 
 * @param w_p 
 * @param w_p 
 * @param chk_only_set_marge_f 
 * @return Distance to...?
 */
q19_12 vcGetNearestNEAR_ROAD_DATA(VC_NEAR_ROAD_DATA** out_nearest_p_addr, VC_CAM_CHK_TYPE chk_type, VC_ROAD_TYPE rd_type, VECTOR3* pos, VC_WORK* w_p, bool chk_only_set_marge_f);

s32  vcAdvantageDistOfOldCurRoad(VC_NEAR_ROAD_DATA* old_cur_p);

void vcAutoRenewalWatchTgtPosAndAngZ(VC_WORK* w_p, VC_CAM_MV_TYPE cam_mv_type, VC_AREA_SIZE_TYPE cur_rd_area_size, s32 far_watch_rate, s32 self_view_eff_rate);

void vcMakeNormalWatchTgtPos(VECTOR3* watch_tgt_pos, s16* watch_tgt_ang_z_p, VC_WORK* w_p, VC_CAM_MV_TYPE cam_mv_type, VC_AREA_SIZE_TYPE cur_rd_area_size);

void vcMixSelfViewEffectToWatchTgtPos(VECTOR3* watch_tgt_pos, s16* watch_tgt_ang_z_p, s16 effect_rate, VC_WORK* w_p, MATRIX* head_mat, s32 anim_status);

void vcMakeFarWatchTgtPos(VECTOR3* watch_tgt_pos, VC_WORK* w_p, VC_AREA_SIZE_TYPE cur_rd_area_size);

/** @brief Sets a camera look-at position. This is the top-level function which incorporates all camera sphere parameters.
 *
 * @param watch_pos Output look-at position (Q19.12).
 * @param center_pos Center reference position (Q19.12).
 * @param cam_pos Current position (Q19.12).
 * @param tgt_chara2watch_cir_dist Look-at offset radius.
 * @param tgt_watch_cir_r Camera position radius??? TODO
 * @param watch_cir_ang_y Y angle from the center to the look-at.
 */
void vcSetWatchTgtXzPos(VECTOR3* watch_pos, const VECTOR3* center_pos, const VECTOR3* cam_pos, q19_12 tgt_chara2watch_cir_dist, q19_12 tgt_watch_cir_r, q3_12 watch_cir_ang_y);

void vcSetWatchTgtYParam(VECTOR3* watch_pos, VC_WORK* w_p, s32 cam_mv_type, q19_12 watch_y);

void vcAdjustWatchYLimitHighWhenFarView(VECTOR3* watch_pos, VECTOR3* cam_pos, s16 sy);

void vcAutoRenewalCamTgtPos(VC_WORK* w_p, VC_CAM_MV_TYPE cam_mv_type, VC_CAM_MV_PARAM* cam_mv_prm_p, VC_ROAD_FLAGS cur_rd_flags, VC_AREA_SIZE_TYPE cur_rd_area_size, s32 far_watch_rate);

s32 vcRetMaxTgtMvXzLen(VC_WORK* w_p, VC_CAM_MV_PARAM* cam_mv_prm_p);

void vcMakeIdealCamPosByHeadPos(VECTOR3* ideal_pos, VC_WORK* w_p, VC_AREA_SIZE_TYPE cur_rd_area_size);

void vcMakeIdealCamPosForFixAngCam(VECTOR3* ideal_pos, VC_WORK* w_p);

void vcMakeIdealCamPosForThroughDoorCam(VECTOR3* ideal_pos, VC_WORK* w_p);

void vcMakeIdealCamPosUseVC_ROAD_DATA(VECTOR3* ideal_pos, VC_WORK* w_p, VC_AREA_SIZE_TYPE cur_rd_area_size);

void vcAdjustXzInLimAreaUsingMIN_IN_ROAD_DIST(s32* x_p, s32* z_p, VC_LIMIT_AREA* lim_p);

void vcMakeBasicCamTgtMvVec(VECTOR3* tgt_mv_vec, VECTOR3* ideal_pos, VC_WORK* w_p, s32 max_tgt_mv_xz_len);

void vcAdjTgtMvVecYByCurNearRoad(VECTOR3* tgt_mv_vec, VC_WORK* w_p);

void vcCamTgtMvVecIsFlipedFromCharaFront(VECTOR3*  tgt_mv_vec, VC_WORK* w_p, s32 max_tgt_mv_xz_len, VC_AREA_SIZE_TYPE cur_rd_area_size);

s32 vcFlipFromCamExclusionArea(s16* flip_ang_y_p, s32* old_cam_excl_area_r_p, VECTOR3* in_pos, VECTOR3* chara_pos, s16 chara_eye_ang_y, VC_AREA_SIZE_TYPE cur_rd_area_size);

void vcGetUseWatchAndCamMvParam(VC_WATCH_MV_PARAM** watch_mv_prm_pp, VC_CAM_MV_PARAM** cam_mv_prm_pp, s32 self_view_eff_rate, VC_WORK* w_p);

void vcRenewalCamData(VC_WORK* w_p, VC_CAM_MV_PARAM* cam_mv_prm_p);

void vcRenewalCamMatAng(VC_WORK* w_p, VC_WATCH_MV_PARAM* watch_mv_prm_p, VC_CAM_MV_TYPE cam_mv_type, bool visible_chara_f);

void vcMakeNewBaseCamAng(SVECTOR* new_base_ang, VC_CAM_MV_TYPE cam_mv_type, VC_WORK* w_p);

void vcRenewalBaseCamAngAndAdjustOfsCamAng(VC_WORK* w_p, SVECTOR* new_base_cam_ang);

void vcMakeOfsCamTgtAng(SVECTOR* ofs_tgt_ang, MATRIX* base_matT, VC_WORK* w_p);

void vcMakeOfsCam2CharaBottomAndTopAngByBaseMatT(SVECTOR* ofs_cam2chara_btm_ang, SVECTOR* ofs_cam2chara_top_ang,
                                                 MATRIX* base_matT, VECTOR3* cam_pos, VECTOR3* chara_pos,
                                                 s32 chara_bottom_y, s32 chara_top_y);

void vcAdjCamOfsAngByCharaInScreen(SVECTOR* cam_ang, SVECTOR* ofs_cam2chara_btm_ang, SVECTOR* ofs_cam2chara_top_ang, VC_WORK* w_p);

void vcAdjCamOfsAngByOfsAngSpd(SVECTOR* ofs_ang, SVECTOR* ofs_ang_spd, SVECTOR* ofs_tgt_ang, VC_WATCH_MV_PARAM* prm_p);

void vcMakeCamMatAndCamAngByBaseAngAndOfsAng(SVECTOR* cam_mat_ang, MATRIX* cam_mat, SVECTOR* base_cam_ang, SVECTOR* ofs_cam_ang, VECTOR3* cam_pos);

void vcSetDataToVwSystem(VC_WORK* w_p, VC_CAM_MV_TYPE cam_mv_type);

s32 vcCamMatNoise(s32 noise_w, s32 ang_spd1, s32 ang_spd2, q19_12 vcSelfViewTimer);

s32 Vc_VectorMagnitudeCalc(s32 x, s32 y, s32 z); // Q19.12

q19_12 vcGetXZSumDistFromLimArea(s32* out_vec_x_p, s32* out_vec_z_p, q19_12 chk_wld_x, q19_12 chk_wld_z,
                                 q19_12 lim_min_x, q19_12 lim_max_x, q19_12 lim_min_z, q19_12 lim_max_z, bool can_ret_minus_dist_f);

#endif
