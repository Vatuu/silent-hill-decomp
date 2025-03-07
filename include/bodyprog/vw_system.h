#ifndef _VW_SYSTEM_H
#define _VW_SYSTEM_H

#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>

// TODO:
// - Update func prototypes to match 1:1 with C files (s32 instead of int, etc).
// - Flags below are from SH2, most seem to match with SH but might be some differences.
// - Code that accesses VC_ROAD_TYPE & VC_NEAR_ROAD_DATA is odd, might need extra work.

typedef enum _VC_ROAD_FLAGS
{
    VC_RD_NOFLAG            = 0,
    VC_RD_END_DATA_F        = 1 << 0,
    VC_RD_WARP_IN_F         = 1 << 1,
    VC_RD_WARP_OUT_F        = 1 << 2,
    VC_RD_WARP_IN_OUT_FS    = VC_RD_WARP_IN_F | VC_RD_WARP_OUT_F,
    VC_RD_NO_FRONT_FLIP_F   = 1 << 3,
    VC_RD_LIM_UP_FAR_VIEW_F = 1 << 4,
    VC_RD_USE_NO_ENEMY_F    = 1 << 5,
    VC_RD_USE_NEAR_ENEMY_F  = 1 << 6,
    VC_RD_MARGE_ROAD_F      = 1 << 7
} VC_ROAD_FLAGS;
STATIC_ASSERT_SIZEOF(VC_ROAD_FLAGS, 4);

typedef enum _VC_FLAGS
{
    VC_USER_CAM_F            = 1 << 0,
    VC_USER_WATCH_F          = 1 << 1,
    VC_WARP_CAM_F            = 1 << 2,
    VC_WARP_WATCH_F          = 1 << 3,
    VC_WARP_CAM_TGT_F        = 1 << 4,
    VC_SWITCH_NEAR_RD_DATA_F = 1 << 5,
    VC_PROJ_MOMENT_CHANGE_F  = 1 << 6,
    VC_VISIBLE_CHARA_F       = 1 << 7,
    VC_INHIBIT_FAR_WATCH_F   = 1 << 8,
    VC_PRS_F_VIEW_F          = 1 << 9,
    VC_OLD_PRS_F_VIEW_F      = 1 << 10
} VC_FLAGS;
STATIC_ASSERT_SIZEOF(VC_FLAGS, 4);

typedef enum _VC_CAM_MV_TYPE
{
    VC_MV_CHASE        = 0,
    VC_MV_SETTLE       = 1,
    VC_MV_FIX_ANG      = 2,
    VC_MV_SELF_VIEW    = 3,
    VC_MV_THROUGH_DOOR = 4,
    VC_MV_SUU          = 5
} VC_CAM_MV_TYPE;
STATIC_ASSERT_SIZEOF(VC_CAM_MV_TYPE, 4);

typedef enum _VC_CAM_CHK_TYPE
{
    VC_CHK_NEAREST_ROAD_TYPE   = 0,
    VC_CHK_NEAREST_SWITCH_TYPE = 1
} VC_CAM_CHK_TYPE;
STATIC_ASSERT_SIZEOF(VC_CAM_CHK_TYPE, 4);

typedef enum _VC_ROAD_TYPE
{
    VC_RD_TYPE_ROAD           = 0,
    VC_RD_TYPE_EFFECT         = 1,
    VC_RD_TYPE_EVENT          = 2,
    VC_RD_TYPE_ROAD_PRIO_LOW  = 3,
    VC_RD_TYPE_ROAD_PRIO_HIGH = 4,
    VC_RD_TYPE_SV_ONLY        = 5,
    VC_RD_TYPE_SUU            = 6
} VC_ROAD_TYPE;
STATIC_ASSERT_SIZEOF(VC_ROAD_TYPE, 4);

typedef enum _VC_AREA_SIZE_TYPE
{
    VC_AREA_TINY    = 0,
    VC_AREA_SMALL   = 1,
    VC_AREA_WIDE    = 2,
    VC_AREA_OUTDOOR = 3,
    VC_AREA_SUU     = 4
} VC_AREA_SIZE_TYPE;
STATIC_ASSERT_SIZEOF(VC_AREA_SIZE_TYPE, 4);

typedef enum _THROUGH_DOOR_SET_CMD_TYPE
{
    VC_TDSC_START = 0,
    VC_TDSC_END   = 1,
    VC_TDSC_MAIN  = 2
} THROUGH_DOOR_SET_CMD_TYPE;
STATIC_ASSERT_SIZEOF(THROUGH_DOOR_SET_CMD_TYPE, 4);

typedef struct _VC_LIMIT_AREA
{
    short min_hx;
    short max_hx;
    short min_hz;
    short max_hz;
} VC_LIMIT_AREA;
STATIC_ASSERT_SIZEOF(VC_LIMIT_AREA, 8);

typedef struct _VC_CAMERA_INTINFO
{
    int    mode;
    u_char mv_smooth;
    char   unk_5;
    short  ev_cam_rate;
} VC_CAMERA_INTINFO;
STATIC_ASSERT_SIZEOF(VC_CAMERA_INTINFO, 8);

typedef struct _VC_WATCH_MV_PARAM
{
    int   ang_accel_x;
    int   ang_accel_y;
    short max_ang_spd_x;
    short max_ang_spd_y;
} VC_WATCH_MV_PARAM;
STATIC_ASSERT_SIZEOF(VC_WATCH_MV_PARAM, 0xC);

typedef struct _VC_CAM_MV_PARAM
{
    int accel_xz;
    int accel_y;
    int max_spd_xz;
    int max_spd_y;
} VC_CAM_MV_PARAM;
STATIC_ASSERT_SIZEOF(VC_CAM_MV_PARAM, 0x10);

// TODO: SH shifts cam_mv_type_14 around to access other data inside
// likely that mv_type is only a char and other fields are inside it too
typedef struct _VC_ROAD_DATA
{
    VC_LIMIT_AREA lim_sw_0;
    VC_LIMIT_AREA lim_rd_8;
    char          flags_10; // _VC_ROAD_FLAGS
    char          area_size_type_11;
    char          min_hy_12;
    char          max_hy_13;
    u_int         cam_mv_type_14;
} VC_ROAD_DATA;
STATIC_ASSERT_SIZEOF(VC_ROAD_DATA, 0x18);

typedef struct _VC_THROUGH_DOOR_CAM_PARAM
{
    u_char  active_f_0;
    char    unk_1[3];
    int     timer_4;
    u_short rail_ang_y_8;
    char    unk_A[2];
    VECTOR3 rail_sta_pos_C;
    int     rail_sta_to_chara_dist_18;
} VC_THROUGH_DOOR_CAM_PARAM;
STATIC_ASSERT_SIZEOF(VC_THROUGH_DOOR_CAM_PARAM, 0x1C);

// TODO: check if this struct is correct, some SH code seems to act like struct
// is only 0x10 bytes when iterating through it?
typedef struct _VC_NEAR_ROAD_DATA
{
    VC_ROAD_DATA *road_p_0;
    u_char        rd_dir_type_4_mb; // unsure
    u_char        use_priority_5;
    u_char        unk_6[2];
    int           chara2road_sum_dist_8;
    int           chara2road_vec_x_C;
    int           chara2road_vec_z_10;
    VC_LIMIT_AREA rd_14;
    VC_LIMIT_AREA sw_1C;
} VC_NEAR_ROAD_DATA;
STATIC_ASSERT_SIZEOF(VC_NEAR_ROAD_DATA, 0x24);

typedef struct _VC_WORK
{
    u_char                    view_cam_active_f_0;
    VC_ROAD_DATA             *vc_road_ary_list_4;
    VC_FLAGS                  flags_8;
    u_char                    through_door_activate_init_f_C;
    u_char                    unk_D[3];
    VC_THROUGH_DOOR_CAM_PARAM through_door_10;
    s16                       scr_half_ang_wy_2C;
    s16                       scr_half_ang_wx_2E;
    short geom_screen_dist_30; // related to GsSetProjection /
                               // g_GameSys.gs_y_res_58A
    short                field_32;
    VC_CAM_MV_PARAM      user_cam_mv_prm_34;
    VECTOR3              cam_tgt_pos_44;
    VECTOR3              cam_pos_50;
    short                cam_mv_ang_y_5C;
    u_char               unk_5E[2];
    VECTOR3              cam_velo_60;
    int                  old_cam_excl_area_r_6C;
    VC_WATCH_MV_PARAM    user_watch_mv_prm_70;
    VECTOR3              watch_tgt_pos_7C;
    int                  watch_tgt_max_y_88;
    short                watch_tgt_ang_z_8C;
    SVECTOR              cam_mat_ang_8E;
    u_char               unk_96[2];
    MATRIX               cam_mat_98;
    SVECTOR              ofs_cam_ang_B8;
    SVECTOR              ofs_cam_ang_spd_C0;
    SVECTOR              base_cam_ang_C8;
    u_char               unk_D0[8];
    u_char               field_D8;
    u_char               unk_D9[3];
    MATRIX               field_DC;
    u_char               field_FC;
    u_char               field_FD;
    short                cam_chara2ideal_ang_y_FE;
    VECTOR3              cam_tgt_velo_100;
    short                cam_tgt_mv_ang_y_10C;
    u_char               unk_10E[2];
    int                  cam_tgt_spd_110;
    VECTOR3              chara_pos_114;
    int                  chara_bottom_y_120;
    int                  chara_top_y_124;
    int                  chara_center_y_128;
    int                  chara_grnd_y_12C;
    VECTOR3              chara_head_pos_130;
    int                  chara_mv_spd_13C;
    short                chara_mv_ang_y_140;
    short                chara_ang_spd_y_142;
    short                chara_eye_ang_y_144;
    short                chara_eye_ang_wy_146;
    int                  chara_watch_xz_r_148;
    VC_NEAR_ROAD_DATA    near_road_ary_14C[10];
    int                  near_road_suu_2B4;
    VC_NEAR_ROAD_DATA    cur_near_road_2B8;
    struct SubCharacter *nearest_enemy_p_2DC;
    int                  nearest_enemy_xz_dist_2E0;
    int                  field_2E4;
} VC_WORK;
STATIC_ASSERT_SIZEOF(VC_WORK, 0x2E8);

typedef struct _VbRVIEW
{
    VECTOR3        vp;
    VECTOR3        vr;
    int            rz;
    GsCOORDINATE2 *super;
} VbRVIEW;
STATIC_ASSERT_SIZEOF(VbRVIEW, 0x20);

typedef struct _VW_VIEW_WORK
{
    VbRVIEW       rview;
    GsCOORDINATE2 vwcoord;
    VECTOR3       worldpos;
    SVECTOR       worldang;
} VW_VIEW_WORK;
STATIC_ASSERT_SIZEOF(VW_VIEW_WORK, 0x84);

extern VC_ROAD_DATA      vcNullRoadArray[2];
extern VC_NEAR_ROAD_DATA vcNullNearRoad;
extern VC_WATCH_MV_PARAM deflt_watch_mv_prm;
extern VC_WATCH_MV_PARAM self_view_watch_mv_prm;
extern VC_CAM_MV_PARAM   cam_mv_prm_user;
extern int               excl_r_ary[9];
extern VC_WORK           vcWork;
extern VECTOR3           vcRefPosSt;
extern VC_CAMERA_INTINFO vcCameraInternalInfo; // debug camera info
extern VW_VIEW_WORK      vwViewPointInfo;
extern MATRIX            VbWvsMatrix;
extern VC_WATCH_MV_PARAM vcWatchMvPrmSt;
extern int               vcSelfViewTimer;

// Function declarations
// vc_util
void vcInitCamera(void *map_overlay_ptr, VECTOR3 *chr_pos);
void vcSetCameraUseWarp(VECTOR3 *chr_pos, short chr_ang_y);
int  vcRetCamMvSmoothF();
void vcSetEvCamRate(short ev_cam_rate);
void vcMoveAndSetCamera(int in_connect_f, int change_debug_mode, int for_f,
                        int back_f, int right_f, int left_f, int up_f,
                        int down_f);
void vcMakeHeroHeadPos(VECTOR3 *head_pos);
void vcAddOfsToPos(VECTOR3 *out_pos, VECTOR3 *in_pos, short ofs_xz_r,
                   short ang_y, int ofs_y);
void vcSetRefPosAndSysRef2CamParam(VECTOR3 *ref_pos, s_SysWork *sys_p,
                                   int for_f, int back_f, int right_f,
                                   int left_f, int up_f, int down_f);
void vcSetRefPosAndCamPosAngByPad(VECTOR3 *ref_pos, s_SysWork *sys_p);

// vw_main
void           vwInitViewInfo();
GsCOORDINATE2 *vwGetViewCoord();
void           vwGetViewPosition(VECTOR3 *pos);
void           vwGetViewAngle(SVECTOR *ang);
void vwSetCoordRefAndEntou(GsCOORDINATE2 *parent_p, int ref_x, int ref_y,
                           int ref_z, short cam_ang_y, short cam_ang_z,
                           int cam_y, int cam_xz_r);
void vwSetViewInfoDirectMatrix(GsCOORDINATE2 *pcoord, MATRIX *cammat);
void vwSetViewInfo();

// vw_calc
void vwRenewalXZVelocityToTargetPos(int *velo_x, int *velo_z, VECTOR3 *now_pos,
                                    VECTOR3 *tgt_pos, int tgt_r, int accel,
                                    int total_max_spd, int dec_forwd_lim_spd,
                                    int dec_accel_side);
void vwLimitOverLimVector(int *vec_x, int *vec_z, int lim_vec_len,
                          short lim_vec_ang_y);
void vwDecreaseSideOfVector(int *vec_x, int *vec_z, int dec_val,
                            int max_side_vec_len, short dir_ang_y);
int vwRetNewVelocityToTargetVal(int now_spd, int mv_pos, int tgt_pos, int accel,
                                int total_max_spd, int dec_val_lim_spd);
int vwRetNewAngSpdToTargetAng(int now_ang_spd, short now_ang, short tgt_ang,
                              int accel_spd, int total_max_ang_spd,
                              int dec_val_lim_spd);
void vwMatrixToAngleYXZ(SVECTOR *ang, MATRIX *mat);
void vbSetWorldScreenMatrix(GsCOORDINATE2 *coord);
void vbSetRefView(VbRVIEW *rview);
void vwAngleToVector(SVECTOR *vec, SVECTOR *ang, int r);
int  vwVectorToAngle(SVECTOR *ang, SVECTOR *vec);
int  vwOresenHokan(int *y_ary, int y_suu, int input_x, int min_x, int max_x);

int Math_MulFixed(int x, int y, char fractionalBits);

// vc_main
void vcInitVCSystem(VC_ROAD_DATA *vc_road_ary_list);
void vcStartCameraSystem();
void vcEndCameraSystem();
void vcSetFirstCamWork(VECTOR3 *cam_pos, short chara_eye_ang_y,
                       int use_through_door_cam_f);
void vcWorkSetFlags(VC_FLAGS enable, VC_FLAGS disable);
void vcUserWatchTarget(VECTOR3 *watch_tgt_pos, VC_WATCH_MV_PARAM *watch_prm_p,
                       int warp_watch_f);
void vcUserCamTarget(VECTOR3 *cam_tgt_pos, VC_CAM_MV_PARAM *cam_prm_p,
                     int warp_cam_f);
void vcChangeProjectionValue(short scr_y);
void func_80080D68();
void vcGetNowWatchPos(VECTOR3 *watch_pos);
void vcGetNowCamPos(VECTOR3 *cam_pos);
void vcReturnPreAutoCamWork(int warp_f);
void vcSetSubjChara(VECTOR3 *chara_pos, int chara_bottom_y, int chara_top_y,
                    int chara_grnd_y, VECTOR3 *chara_head_pos,
                    short chara_mv_spd, int chara_mv_ang_y,
                    short chara_ang_spd_y, short chara_eye_ang_y,
                    short chara_eye_ang_wy, int chara_watch_xz_r);
int  vcExecCamera();
void vcSetAllNpcDeadTimer();
int  vcRetSmoothCamMvF(VECTOR3 *old_pos, VECTOR3 *now_pos, SVECTOR *old_ang,
                       SVECTOR *now_ang);
VC_CAM_MV_TYPE vcRetCurCamMvType(VC_WORK *w_p);
int            vcRetThroughDoorCamEndF(VC_WORK *w_p);
int            vcRetFarWatchRate(int            far_watch_button_prs_f,
                                 VC_CAM_MV_TYPE cur_cam_mv_type, VC_WORK *w_p);
int  vcRetSelfViewEffectRate(VC_CAM_MV_TYPE cur_cam_mv_type, int far_watch_rate,
                             VC_WORK *w_p);
void vcSetFlagsByCamMvType(VC_CAM_MV_TYPE cam_mv_type, int far_watch_rate,
                           int all_warp_f);
void vcPreSetDataInVC_WORK(VC_WORK *w_p, VC_ROAD_DATA *vc_road_ary_list);
void vcSetTHROUGH_DOOR_CAM_PARAM_in_VC_WORK(
    VC_WORK *w_p, THROUGH_DOOR_SET_CMD_TYPE set_cmd_type);
void vcSetNearestEnemyDataInVC_WORK(VC_WORK *w_p);
void vcSetNearRoadAryByCharaPos(VC_WORK *w_p, VC_ROAD_DATA *road_ary_list,
                                int half_w, int unused, int near_enemy_f);
int  vcRetRoadUsePriority(VC_ROAD_TYPE rd_type);
int  vcSetCurNearRoadInVC_WORK(VC_WORK *w_p);
int  vcGetBestNewCurNearRoad(VC_NEAR_ROAD_DATA **new_cur_pp,
                             VC_CAM_CHK_TYPE chk_type, VECTOR3 *pos,
                             VC_WORK *w_p);
int  vcGetNearestNEAR_ROAD_DATA(VC_NEAR_ROAD_DATA **out_nearest_p_addr,
                                VC_CAM_CHK_TYPE chk_type, VC_ROAD_TYPE rd_type,
                                VECTOR3 *pos, VC_WORK *w_p,
                                int chk_only_set_marge_f);
int  vcAdvantageDistOfOldCurRoad(VC_NEAR_ROAD_DATA *old_cur_p);
void vcAutoRenewalWatchTgtPosAndAngZ(VC_WORK *w_p, VC_CAM_MV_TYPE cam_mv_type,
                                     VC_AREA_SIZE_TYPE cur_rd_area_size,
                                     int               far_watch_rate,
                                     int               self_view_eff_rate);
void vcMakeNormalWatchTgtPos(VECTOR3 *watch_tgt_pos, short *watch_tgt_ang_z_p,
                             VC_WORK *w_p, VC_CAM_MV_TYPE cam_mv_type,
                             VC_AREA_SIZE_TYPE cur_rd_area_size);
void vcMixSelfViewEffectToWatchTgtPos(VECTOR3 *watch_tgt_pos,
                                      short   *watch_tgt_ang_z_p,
                                      short effect_rate, VC_WORK *w_p,
                                      MATRIX *head_mat, int anim_status);
void vcMakeFarWatchTgtPos(VECTOR3 *watch_tgt_pos, VC_WORK *w_p,
                          VC_AREA_SIZE_TYPE cur_rd_area_size);
void vcSetWatchTgtXzPos(VECTOR3 *watch_pos, VECTOR3 *center_pos,
                        VECTOR3 *cam_pos, int tgt_chara2watch_cir_dist,
                        int tgt_watch_cir_r, short watch_cir_ang_y);
void vcSetWatchTgtYParam(VECTOR3 *watch_pos, VC_WORK *w_p, int cam_mv_type,
                         int watch_y);
void vcAdjustWatchYLimitHighWhenFarView(VECTOR3 *watch_pos, VECTOR3 *cam_pos,
                                        short sy);
void vcAutoRenewalCamTgtPos(VC_WORK *w_p, VC_CAM_MV_TYPE cam_mv_type,
                            VC_CAM_MV_PARAM  *cam_mv_prm_p,
                            VC_ROAD_FLAGS     cur_rd_flags,
                            VC_AREA_SIZE_TYPE cur_rd_area_size);
int  vcRetMaxTgtMvXzLen(VC_WORK *w_p, VC_CAM_MV_PARAM *cam_mv_prm_p);
void vcMakeIdealCamPosByHeadPos(VECTOR3 *ideal_pos, VC_WORK *w_p,
                                VC_AREA_SIZE_TYPE cur_rd_area_size);
void vcMakeIdealCamPosForFixAngCam(VECTOR3 *ideal_pos, VC_WORK *w_p);
void vcMakeIdealCamPosForThroughDoorCam(VECTOR3 *ideal_pos, VC_WORK *w_p);
void vcMakeIdealCamPosUseVC_ROAD_DATA(VECTOR3 *ideal_pos, VC_WORK *w_p,
                                      VC_AREA_SIZE_TYPE cur_rd_area_size);
void vcAdjustXzInLimAreaUsingMIN_IN_ROAD_DIST(int *x_p, int *z_p,
                                              VC_LIMIT_AREA *lim_p);
void vcMakeBasicCamTgtMvVec(VECTOR3 *tgt_mv_vec, VECTOR3 *ideal_pos,
                            VC_WORK *w_p, int max_tgt_mv_xz_len);
void vcAdjTgtMvVecYByCurNearRoad(VECTOR3 *tgt_mv_vec, VC_WORK *w_p);
void vcCamTgtMvVecIsFlipedFromCharaFront(VECTOR3 *tgt_mv_vec, VC_WORK *w_p,
                                         int               max_tgt_mv_xz_len,
                                         VC_AREA_SIZE_TYPE cur_rd_area_size);
int  vcFlipFromCamExclusionArea(short *flip_ang_y_p, int *old_cam_excl_area_r_p,
                                VECTOR3 *in_pos, VECTOR3 *chara_pos,
                                short             chara_eye_ang_y,
                                VC_AREA_SIZE_TYPE cur_rd_area_size);
void vcGetUseWatchAndCamMvParam(VC_WATCH_MV_PARAM **watch_mv_prm_pp,
                                VC_CAM_MV_PARAM   **cam_mv_prm_pp,
                                int self_view_eff_rate, VC_WORK *w_p);
void vcRenewalCamData(VC_WORK *w_p, VC_CAM_MV_PARAM *cam_mv_prm_p);
void vcRenewalCamMatAng(VC_WORK *w_p, VC_WATCH_MV_PARAM *watch_mv_prm_p,
                        VC_CAM_MV_TYPE cam_mv_type, int visible_chara_f);
void vcMakeNewBaseCamAng(SVECTOR *new_base_ang, VC_CAM_MV_TYPE cam_mv_type,
                         VC_WORK *w_p);
void vcRenewalBaseCamAngAndAdjustOfsCamAng(VC_WORK *w_p,
                                           SVECTOR *new_base_cam_ang);
void vcMakeOfsCamTgtAng(SVECTOR *ofs_tgt_ang, MATRIX *base_matT, VC_WORK *w_p);
void vcMakeOfsCam2CharaBottomAndTopAngByBaseMatT(
    SVECTOR *ofs_cam2chara_btm_ang, SVECTOR *ofs_cam2chara_top_ang,
    MATRIX *base_matT, VECTOR3 *cam_pos, VECTOR3 *chara_pos, int chara_bottom_y,
    int chara_top_y);
void vcAdjCamOfsAngByCharaInScreen(SVECTOR *cam_ang,
                                   SVECTOR *ofs_cam2chara_btm_ang,
                                   SVECTOR *ofs_cam2chara_top_ang,
                                   VC_WORK *w_p);
void vcAdjCamOfsAngByOfsAngSpd(SVECTOR *ofs_ang, SVECTOR *ofs_ang_spd,
                               SVECTOR *ofs_tgt_ang, VC_WATCH_MV_PARAM *prm_p);
void vcMakeCamMatAndCamAngByBaseAngAndOfsAng(SVECTOR *cam_mat_ang,
                                             MATRIX  *cam_mat,
                                             SVECTOR *base_cam_ang,
                                             SVECTOR *ofs_cam_ang,
                                             VECTOR3 *cam_pos);
void vcSetDataToVwSystem(VC_WORK *w_p, VC_CAM_MV_TYPE cam_mv_type);
int vcCamMatNoise(int noise_w, int ang_spd1, int ang_spd2, int vcSelfViewTimer);
int Math_VectorMagnitude(int x, int y, int z);
int vcGetXZSumDistFromLimArea(int *out_vec_x_p, int *out_vec_z_p, int chk_wld_x,
                              int chk_wld_z, int lim_min_x, int lim_max_x,
                              int lim_min_z, int lim_max_z,
                              int can_ret_minus_dist_f);

#endif /* _VW_SYSTEM_H */
