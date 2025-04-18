#ifndef _VW_SYSTEM_H
#define _VW_SYSTEM_H

#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>

// TODO:
// - Add doc comments above func delcarations.
// - Flags below are from SH2, most seem to match with SH but there might be some differences.
// - Code that accesses VC_ROAD_DATA & VC_NEAR_ROAD_DATA is odd, might need extra work.

struct _MapOverlayHeader; // `bodyprog.h` forward declaration.

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

/** @brief 2D camera-specific axis-aligned bounding box (AABB), with values in Q8.8 format.
 * 
 * Constrains the camera position to a limited area on the XZ plane.
 */
typedef struct _VC_LIMIT_AREA
{
    s16 min_hx;
    s16 max_hx;
    s16 min_hz;
    s16 max_hz;
} VC_LIMIT_AREA;
STATIC_ASSERT_SIZEOF(VC_LIMIT_AREA, 8);

typedef struct _VC_CAMERA_INTINFO
{
    u32 mode;
    u8  mv_smooth;
    s8  unk_5;
    s16 ev_cam_rate;
} VC_CAMERA_INTINFO;
STATIC_ASSERT_SIZEOF(VC_CAMERA_INTINFO, 8);

/** @brief Camera look-at rotation parameters. */
typedef struct _VC_WATCH_MV_PARAM
{
    s32 ang_accel_x;   /** Angular acceleration on the X axis. */
    s32 ang_accel_y;   /** Angular acceleration on the Y axis. */
    s16 max_ang_spd_x; /** Max angular speed on the X axis. */
    s16 max_ang_spd_y; /** Max angular speed on the Y axis. */
} VC_WATCH_MV_PARAM;
STATIC_ASSERT_SIZEOF(VC_WATCH_MV_PARAM, 12);

/** @brief Camera translation paremeters. */
typedef struct _VC_CAM_MV_PARAM
{
    s32 accel_xz;   /** Speed acceleration on the XZ plane. */
    s32 accel_y;    /** Speed acceleration on the Y axis. */
    s32 max_spd_xz; /** Max speed on the XZ plane. */
    s32 max_spd_y;  /** Max speed on the Y axis. */
} VC_CAM_MV_PARAM;
STATIC_ASSERT_SIZEOF(VC_CAM_MV_PARAM, 16);

// TODO: SH shifts cam_mv_type_14 around to access other data inside.
// Likely that mv_type is only a char and other fields are inside it too.
typedef struct _VC_ROAD_DATA
{
    VC_LIMIT_AREA     lim_sw_0;
    VC_LIMIT_AREA     lim_rd_8;
    VC_ROAD_FLAGS     flags_10          : 8;
    VC_AREA_SIZE_TYPE area_size_type_11 : 2;
    VC_ROAD_TYPE      rd_type_11        : 3;
    int               unk_11            : 19; // Unnamed fields may contain `mv_y_type`/`rd_dir_type`.
    int               unk_14            : 8;
    u32               field_15          : 4;
    int               cam_mv_type_14    : 4; /** `VC_CAM_MV_TYPE` */
} VC_ROAD_DATA;
STATIC_ASSERT_SIZEOF(VC_ROAD_DATA, 24);

/** @brief Rail camera parementers. */
typedef struct _VC_THROUGH_DOOR_CAM_PARAM
{
    u8      active_f_0;
    s8      unk_1[3];
    int     timer_4;
    u16     rail_ang_y_8;              /** The rail's Y angle. */
    s8      unk_A[2];
    VECTOR3 rail_sta_pos_C;            /** The rail's start position. */
    int     rail_sta_to_chara_dist_18; /** The distance from the rail's start position to a locked-on character's position. */
} VC_THROUGH_DOOR_CAM_PARAM;
STATIC_ASSERT_SIZEOF(VC_THROUGH_DOOR_CAM_PARAM, 28);

// TODO: Check if this struct is correct, some SH code seems to act like struct
// is only 16 bytes when iterating through it?
typedef struct _VC_NEAR_ROAD_DATA
{
    VC_ROAD_DATA* road_p_0;
    u8            rd_dir_type_4_mb; // Unsure.
    u8            use_priority_5;
    u8            unk_6[2];
    int           chara2road_sum_dist_8;
    int           chara2road_vec_x_C;
    int           chara2road_vec_z_10;
    VC_LIMIT_AREA rd_14;
    VC_LIMIT_AREA sw_1C;
} VC_NEAR_ROAD_DATA;
STATIC_ASSERT_SIZEOF(VC_NEAR_ROAD_DATA, 36);

typedef struct _VC_WORK
{
    u8                        view_cam_active_f_0;
    VC_ROAD_DATA*             vc_road_ary_list_4;
    VC_FLAGS                  flags_8;
    u8                        through_door_activate_init_f_C;
    s8                        unk_D[3];
    VC_THROUGH_DOOR_CAM_PARAM through_door_10;
    s16                       scr_half_ang_wy_2C;
    s16                       scr_half_ang_wx_2E;
    s16                       geom_screen_dist_30; // Related to `GsSetProjection`/`g_GameSys.gs_y_res_58A`.
    s16                       field_32;
    VC_CAM_MV_PARAM           user_cam_mv_prm_34;       /** Look parameters? */
    VECTOR3                   cam_tgt_pos_44;           /** Target position. */
    VECTOR3                   cam_pos_50;               /** Position. */
    s16                       cam_mv_ang_y_5C;          /** Angular velocity on the Y axis. */
    s8                        unk_5E[2];
    VECTOR3                   cam_velo_60;              /** Velocity. */
    int                       old_cam_excl_area_r_6C;   /** Previous exclusion area radius. */
    VC_WATCH_MV_PARAM         user_watch_mv_prm_70;
    VECTOR3                   watch_tgt_pos_7C;         /** Target look-at position. */
    int                       watch_tgt_max_y_88;       /** Max look-at Y angle. */
    s16                       watch_tgt_ang_z_8C;       /** Target look-at Z angle. */
    SVECTOR                   cam_mat_ang_8E;
    u8                        unk_96[2];
    MATRIX                    cam_mat_98;               /** Matrix. */
    SVECTOR                   ofs_cam_ang_B8;           /** Offset rotation. */
    SVECTOR                   ofs_cam_ang_spd_C0;       /** Offset rotational speed. */
    SVECTOR                   base_cam_ang_C8;          /** Base rotation. */
    s8                        unk_D0[8];
    u8                        field_D8;
    s8                        unk_D9[3];
    MATRIX                    field_DC;
    u8                        field_FC;
    u8                        field_FD;
    s16                       cam_chara2ideal_ang_y_FE;  
    VECTOR3                   cam_tgt_velo_100;          /** Target velocity. */
    s16                       cam_tgt_mv_ang_y_10C;      /** Target Y angles. */
    s8                        unk_10E[2];
    int                       cam_tgt_spd_110;           /** Target speed. */
    VECTOR3                   chara_pos_114;             /** Locked-on character's position. */
    int                       chara_bottom_y_120;        /** Locked-on character's bottom height. */
    int                       chara_top_y_124;           /** Locked-on character's top height. */
    int                       chara_center_y_128;        /** Locked-on character's center height. */
    int                       chara_grnd_y_12C;          /** Locked-on character's height from the ground? */
    VECTOR3                   chara_head_pos_130;        /** Locked-on character's head position. */
    int                       chara_mv_spd_13C;          /** Locked-on character's movement speed. */
    s16                       chara_mv_ang_y_140;        /** Locked-on character's heading angle. */
    s16                       chara_ang_spd_y_142;       /** Locked-on character's heading angle angular speed. */
    s16                       chara_eye_ang_y_144;       /** Locked-on character's look heading angle? */
    s16                       chara_eye_ang_wy_146;
    int                       chara_watch_xz_r_148;      /** Locked-on character's radius on the XZ plane. */
    VC_NEAR_ROAD_DATA         near_road_ary_14C[10];
    int                       near_road_suu_2B4;
    VC_NEAR_ROAD_DATA         cur_near_road_2B8;
    struct SubCharacter*      nearest_enemy_p_2DC;       /** Closest enemy. */
    int                       nearest_enemy_xz_dist_2E0; /** Distance to the closest enemy on the XZ plane. */
    int                       field_2E4;
} VC_WORK;
STATIC_ASSERT_SIZEOF(VC_WORK, 744);

typedef struct _VbRVIEW
{
    VECTOR3        vp;
    VECTOR3        vr;
    int            rz;
    GsCOORDINATE2* super;
} VbRVIEW;
STATIC_ASSERT_SIZEOF(VbRVIEW, 32);

typedef struct _VW_VIEW_WORK
{
    VbRVIEW       rview;
    GsCOORDINATE2 vwcoord;
    VECTOR3       worldpos;
    SVECTOR       worldang;
} VW_VIEW_WORK;
STATIC_ASSERT_SIZEOF(VW_VIEW_WORK, 132);

extern VC_ROAD_DATA      vcNullRoadArray[2];
extern VC_NEAR_ROAD_DATA vcNullNearRoad;
extern VC_WATCH_MV_PARAM deflt_watch_mv_prm;
extern VC_WATCH_MV_PARAM self_view_watch_mv_prm;
extern VC_CAM_MV_PARAM   cam_mv_prm_user;
extern int               excl_r_ary[9];
extern VC_WORK           vcWork;
extern VECTOR3           vcRefPosSt;
extern VW_VIEW_WORK      vwViewPointInfo;
extern MATRIX            VbWvsMatrix;
extern VC_WATCH_MV_PARAM vcWatchMvPrmSt;
extern int               vcSelfViewTimer;

// vc_util.c

void vcInitCamera(struct _MapOverlayHeader* map_overlay_ptr, VECTOR3* chr_pos);
void vcSetCameraUseWarp(VECTOR3* chr_pos, s16 chr_ang_y);
int  vcRetCamMvSmoothF();
void vcSetEvCamRate(s16 ev_cam_rate);
void vcMoveAndSetCamera(int in_connect_f, int change_debug_mode, int for_f, int back_f, int right_f, int left_f, int up_f, int down_f);
void vcMakeHeroHeadPos(VECTOR3* head_pos);
void vcAddOfsToPos(VECTOR3* out_pos, VECTOR3* in_pos, s16 ofs_xz_r, s16 ang_y, int ofs_y);
void vcSetRefPosAndSysRef2CamParam(VECTOR3* ref_pos, s_SysWork* sys_p, int for_f, int back_f, int right_f, int left_f, int up_f, int down_f);
void vcSetRefPosAndCamPosAngByPad(VECTOR3* ref_pos, s_SysWork* sys_p);

// vw_main.c

void           vwInitViewInfo();
GsCOORDINATE2* vwGetViewCoord();
void           vwGetViewPosition(VECTOR3* pos);
void           vwGetViewAngle(SVECTOR* ang);
void           func_80048AF4(VECTOR3* arg0, VECTOR3* arg1);
void           vwSetCoordRefAndEntou(GsCOORDINATE2* parent_p, int ref_x, int ref_y, int ref_z, s16 cam_ang_y, s16 cam_ang_z, int cam_y, int cam_xz_r);
void           vwSetViewInfoDirectMatrix(GsCOORDINATE2* pcoord, MATRIX* cammat);
void           vwSetViewInfo();

// vw_calc.c

void vwRenewalXZVelocityToTargetPos(int* velo_x, int* velo_z, VECTOR3* now_pos, VECTOR3* tgt_pos, int tgt_r,
                                    int accel, int total_max_spd, int dec_forwd_lim_spd, int dec_accel_side);
void vwLimitOverLimVector(int* vec_x, int* vec_z, int lim_vec_len, s16 lim_vec_ang_y);
void vwDecreaseSideOfVector(int* vec_x, int* vec_z, int dec_val, int max_side_vec_len, s16 dir_ang_y);
int  vwRetNewVelocityToTargetVal(int now_spd, int mv_pos, int tgt_pos, int accel, int total_max_spd, int dec_val_lim_spd);
int  vwRetNewAngSpdToTargetAng(int now_ang_spd, s16 now_ang, s16 tgt_ang, int accel_spd, int total_max_ang_spd, int dec_val_lim_spd);
void vwMatrixToAngleYXZ(SVECTOR* ang, MATRIX* mat);
void func_800496AC(MATRIX* mat0, MATRIX* mat1, SVECTOR* vec);
void vbSetWorldScreenMatrix(GsCOORDINATE2* coord);
void vbSetRefView(VbRVIEW* rview);
void func_80049984(GsCOORDINATE2*, MATRIX*);
void func_80049AF8(GsCOORDINATE2* coord, SVECTOR* vec);
void func_80049B6C(GsCOORDINATE2* coord, MATRIX* mat, SVECTOR* vec);
void func_80049C2C(MATRIX* mat, int x, int y, int z);
void vwAngleToVector(SVECTOR* vec, SVECTOR* ang, int r);
int  vwVectorToAngle(SVECTOR* ang, SVECTOR* vec);

/** Performs linear interpolation between Y values based on an input X within the given range. */
int vwOresenHokan(int* y_ary, int y_suu, int input_x, int min_x, int max_x);

int Math_MulFixed(int x, int y, s8 fractionalBits);

// vc_main.c

void vcInitVCSystem(VC_ROAD_DATA* vc_road_ary_list);
void vcStartCameraSystem();
void vcEndCameraSystem();
void vcSetFirstCamWork(VECTOR3* cam_pos, s16 chara_eye_ang_y, int use_through_door_cam_f);
void vcWorkSetFlags(VC_FLAGS enable, VC_FLAGS disable);
s32  func_80080C18(s32 lookAtAngleYMax);
void vcUserWatchTarget(VECTOR3* watch_tgt_pos, VC_WATCH_MV_PARAM* watch_prm_p, int warp_watch_f);
void vcUserCamTarget(VECTOR3* cam_tgt_pos, VC_CAM_MV_PARAM* cam_prm_p, int warp_cam_f);
void vcChangeProjectionValue(s16 scr_y);
void func_80080D68();
void vcGetNowWatchPos(VECTOR3* watch_pos);
void vcGetNowCamPos(VECTOR3* cam_pos);
void vcReturnPreAutoCamWork(int warp_f);
void vcSetSubjChara(VECTOR3* chara_pos, int chara_bottom_y, int chara_top_y, int chara_grnd_y, VECTOR3* chara_head_pos,
                    s16 chara_mv_spd, int chara_mv_ang_y, s16 chara_ang_spd_y, s16 chara_eye_ang_y, s16 chara_eye_ang_wy, int chara_watch_xz_r);
int  vcExecCamera();
void vcSetAllNpcDeadTimer();
int  vcRetSmoothCamMvF(VECTOR3* old_pos, VECTOR3* now_pos, SVECTOR* old_ang, SVECTOR* now_ang);
VC_CAM_MV_TYPE vcRetCurCamMvType(VC_WORK* w_p);
int  func_8008150C(int arg0, int arg1);
int  vcRetThroughDoorCamEndF(VC_WORK* w_p);
int  vcRetFarWatchRate(int far_watch_button_prs_f, VC_CAM_MV_TYPE cur_cam_mv_type, VC_WORK* w_p);
int  vcRetSelfViewEffectRate(VC_CAM_MV_TYPE cur_cam_mv_type, int far_watch_rate, VC_WORK* w_p);
void vcSetFlagsByCamMvType(VC_CAM_MV_TYPE cam_mv_type, int far_watch_rate, int all_warp_f);
void vcPreSetDataInVC_WORK(VC_WORK* w_p, VC_ROAD_DATA* vc_road_ary_list);
void vcSetTHROUGH_DOOR_CAM_PARAM_in_VC_WORK(VC_WORK* w_p, THROUGH_DOOR_SET_CMD_TYPE set_cmd_type);
void vcSetNearestEnemyDataInVC_WORK(VC_WORK* w_p);
void vcSetNearRoadAryByCharaPos(VC_WORK* w_p, VC_ROAD_DATA* road_ary_list, int half_w, int unused, int near_enemy_f);
int  vcRetRoadUsePriority(VC_ROAD_TYPE rd_type);
int  vcSetCurNearRoadInVC_WORK(VC_WORK* w_p);
int  vcGetBestNewCurNearRoad(VC_NEAR_ROAD_DATA** new_cur_pp, VC_CAM_CHK_TYPE chk_type, VECTOR3* pos, VC_WORK* w_p);
int  vcGetNearestNEAR_ROAD_DATA(VC_NEAR_ROAD_DATA** out_nearest_p_addr, VC_CAM_CHK_TYPE chk_type, VC_ROAD_TYPE rd_type, VECTOR3* pos, VC_WORK* w_p, int chk_only_set_marge_f);
int  vcAdvantageDistOfOldCurRoad(VC_NEAR_ROAD_DATA* old_cur_p);
void vcAutoRenewalWatchTgtPosAndAngZ(VC_WORK* w_p, VC_CAM_MV_TYPE cam_mv_type, VC_AREA_SIZE_TYPE cur_rd_area_size, int far_watch_rate, int self_view_eff_rate);
void vcMakeNormalWatchTgtPos(VECTOR3* watch_tgt_pos, s16* watch_tgt_ang_z_p, VC_WORK* w_p, VC_CAM_MV_TYPE cam_mv_type, VC_AREA_SIZE_TYPE cur_rd_area_size);
void vcMixSelfViewEffectToWatchTgtPos(VECTOR3* watch_tgt_pos, s16* watch_tgt_ang_z_p, s16 effect_rate, VC_WORK* w_p, MATRIX* head_mat, int anim_status);
void vcMakeFarWatchTgtPos(VECTOR3* watch_tgt_pos, VC_WORK* w_p, VC_AREA_SIZE_TYPE cur_rd_area_size);
void vcSetWatchTgtXzPos(VECTOR3* watch_pos, VECTOR3* center_pos, VECTOR3* cam_pos, int tgt_chara2watch_cir_dist, int tgt_watch_cir_r, s16 watch_cir_ang_y);
void vcSetWatchTgtYParam(VECTOR3* watch_pos, VC_WORK* w_p, int cam_mv_type, int watch_y);
void vcAdjustWatchYLimitHighWhenFarView(VECTOR3* watch_pos, VECTOR3* cam_pos, s16 sy);
void vcAutoRenewalCamTgtPos(VC_WORK* w_p, VC_CAM_MV_TYPE cam_mv_type, VC_CAM_MV_PARAM* cam_mv_prm_p, VC_ROAD_FLAGS cur_rd_flags, VC_AREA_SIZE_TYPE cur_rd_area_size, int far_watch_rate);
int  vcRetMaxTgtMvXzLen(VC_WORK* w_p, VC_CAM_MV_PARAM* cam_mv_prm_p);
void vcMakeIdealCamPosByHeadPos(VECTOR3* ideal_pos, VC_WORK* w_p, VC_AREA_SIZE_TYPE cur_rd_area_size);
void vcMakeIdealCamPosForFixAngCam(VECTOR3* ideal_pos, VC_WORK* w_p);
void vcMakeIdealCamPosForThroughDoorCam(VECTOR3* ideal_pos, VC_WORK* w_p);
void vcMakeIdealCamPosUseVC_ROAD_DATA(VECTOR3* ideal_pos, VC_WORK* w_p, VC_AREA_SIZE_TYPE cur_rd_area_size);
void vcAdjustXzInLimAreaUsingMIN_IN_ROAD_DIST(int* x_p, int* z_p, VC_LIMIT_AREA* lim_p);
void vcMakeBasicCamTgtMvVec(VECTOR3* tgt_mv_vec, VECTOR3* ideal_pos, VC_WORK* w_p, int max_tgt_mv_xz_len);
void vcAdjTgtMvVecYByCurNearRoad(VECTOR3* tgt_mv_vec, VC_WORK* w_p);
void vcCamTgtMvVecIsFlipedFromCharaFront(VECTOR3*  tgt_mv_vec, VC_WORK* w_p, int max_tgt_mv_xz_len, VC_AREA_SIZE_TYPE cur_rd_area_size);
int  vcFlipFromCamExclusionArea(s16* flip_ang_y_p, int* old_cam_excl_area_r_p, VECTOR3* in_pos, VECTOR3* chara_pos, s16 chara_eye_ang_y, VC_AREA_SIZE_TYPE cur_rd_area_size);
void vcGetUseWatchAndCamMvParam(VC_WATCH_MV_PARAM** watch_mv_prm_pp, VC_CAM_MV_PARAM** cam_mv_prm_pp, int self_view_eff_rate, VC_WORK* w_p);
void vcRenewalCamData(VC_WORK* w_p, VC_CAM_MV_PARAM* cam_mv_prm_p);
void vcRenewalCamMatAng(VC_WORK* w_p, VC_WATCH_MV_PARAM* watch_mv_prm_p, VC_CAM_MV_TYPE cam_mv_type, int visible_chara_f);
void vcMakeNewBaseCamAng(SVECTOR* new_base_ang, VC_CAM_MV_TYPE cam_mv_type, VC_WORK* w_p);
void vcRenewalBaseCamAngAndAdjustOfsCamAng(VC_WORK* w_p, SVECTOR* new_base_cam_ang);
void vcMakeOfsCamTgtAng(SVECTOR* ofs_tgt_ang, MATRIX* base_matT, VC_WORK* w_p);
void vcMakeOfsCam2CharaBottomAndTopAngByBaseMatT(SVECTOR* ofs_cam2chara_btm_ang, SVECTOR* ofs_cam2chara_top_ang,
                                                 MATRIX* base_matT, VECTOR3* cam_pos, VECTOR3* chara_pos,
                                                 int chara_bottom_y, int chara_top_y);
void vcAdjCamOfsAngByCharaInScreen(SVECTOR* cam_ang, SVECTOR* ofs_cam2chara_btm_ang, SVECTOR* ofs_cam2chara_top_ang, VC_WORK* w_p);
void vcAdjCamOfsAngByOfsAngSpd(SVECTOR* ofs_ang, SVECTOR* ofs_ang_spd, SVECTOR* ofs_tgt_ang, VC_WATCH_MV_PARAM* prm_p);
void vcMakeCamMatAndCamAngByBaseAngAndOfsAng(SVECTOR* cam_mat_ang, MATRIX* cam_mat, SVECTOR* base_cam_ang, SVECTOR* ofs_cam_ang, VECTOR3* cam_pos);
void vcSetDataToVwSystem(VC_WORK* w_p, VC_CAM_MV_TYPE cam_mv_type);
int  vcCamMatNoise(int noise_w, int ang_spd1, int ang_spd2, int vcSelfViewTimer);

int Math_VectorMagnitude(int x, int y, int z);

int vcGetXZSumDistFromLimArea(int* out_vec_x_p, int* out_vec_z_p, int chk_wld_x, int chk_wld_z,
                              int lim_min_x, int lim_max_x, int lim_min_z, int lim_max_z, int can_ret_minus_dist_f);

static inline void vcWork_CurNearRoadSet(VC_WORK* work, VC_NEAR_ROAD_DATA* road)
{
    memcpy(&work->cur_near_road_2B8, road, sizeof(VC_NEAR_ROAD_DATA));
}

#endif /* _VW_SYSTEM_H */
