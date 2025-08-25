#ifndef _VW_SYSTEM_H
#define _VW_SYSTEM_H

#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>

struct _MapOverlayHeader;

/** @brief GLOSSARY OF ABBREVIATIONS
 *
 * ACCEL: Acceleration
 * ANG:   Angle
 * ARY:   Array
 * DEFLT: Default
 * EV:    ?
 * EXCL:  Exclusion
 * F:     Flag/flags
 * FIX:   Fixed in place
 * GRND:  Ground
 * H:     Height
 * LIM:   Limit
 * MV:    Movement
 * OFS:   Offset
 * PRIO:  Priority
 * R:     Radius
 * RD:    Road
 * SCR:   Screen
 * SPD:   Speed
 * STA:   Start
 * SV:    Swivel?
 * SW:    ?
 * TGT:   Target
 * VELO:  Velocity
 * VB:    ?
 * VC:    Virtual camera
 * VW:    View
*/

/** @brief GLOSSARY OF JAPANGLISH TERMS
 *
 * Area:         A camera path's spatial constraint defining its area of influence.
 * Entou:        "Cylinder" in Japanese. Refers to a 2D radius on the XZ plane.
 * Flipped:      ?
 * Limit area:   2D AABB parameters defining a camera path's spatial constraint.
 * Marge:        ?
 * Near road:    Nearby camera path collision containing info about a path's relation to the player in space (distance, priority, etc.).
 *               An array of these is kept to track which path should take effect.
 * Oresen hokan: Polyline interpolation, linear interpolation over an array of values.
 * Renewal:      Reset.
 * Road:         Camera path. A region which dictates specific camera behaviors while the player is inside.
 * Self view:    First-person view.
 * Suu:          "Count" in Japanese. Usually refers to the number of entries in an array or is included in enums to denote the number of entries it contains.
 * Through door: Rail camera.
 * Watch:        Camera look-at.
 */

// TODO:
// - Split into 4 separate headers.
// - Add doc comments above func declarations.
// - Flags below are from SH2, most seem to match with SH but there might be some differences.

#define CAMERA_PATH_COLL_COUNT_MAX 10

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

/** @brief Camera path type. */
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
//    VC_AREA_SUU     = 4 // Count. Disabled to remove size warning since it's unused.
} VC_AREA_SIZE_TYPE;
STATIC_ASSERT_SIZEOF(VC_AREA_SIZE_TYPE, 4);

typedef enum _THROUGH_DOOR_SET_CMD_TYPE
{
    VC_TDSC_START = 0,
    VC_TDSC_END   = 1,
    VC_TDSC_MAIN  = 2
} THROUGH_DOOR_SET_CMD_TYPE;
STATIC_ASSERT_SIZEOF(THROUGH_DOOR_SET_CMD_TYPE, 4);

/** @brief 2D camera-specific axis-aligned bounding box (AABB), with values in Q7.8 format.
 * 
 * Constrains the camera position to a limited area on the XZ plane.
 */
typedef struct _VC_LIMIT_AREA
{
    q7_8 min_hx;
    q7_8 max_hx;
    q7_8 min_hz;
    q7_8 max_hz;
} VC_LIMIT_AREA;
STATIC_ASSERT_SIZEOF(VC_LIMIT_AREA, 8);

/** @brief Camera internal info. */
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
    s32 ang_accel_x;   /** Angular acceleration on X axis. */
    s32 ang_accel_y;   /** Angular acceleration on Y axis. */
    s16 max_ang_spd_x; /** Max angular speed on X axis. */
    s16 max_ang_spd_y; /** Max angular speed on Y axis. */
} VC_WATCH_MV_PARAM;
STATIC_ASSERT_SIZEOF(VC_WATCH_MV_PARAM, 12);

/** @brief Camera translation parameters. */
typedef struct _VC_CAM_MV_PARAM
{
    s32 accel_xz;   /** Speed acceleration on XZ plane. */
    s32 accel_y;    /** Speed acceleration on Y axis. */
    s32 max_spd_xz; /** Max speed on XZ plane. */
    s32 max_spd_y;  /** Max speed on Y axis. */
} VC_CAM_MV_PARAM;
STATIC_ASSERT_SIZEOF(VC_CAM_MV_PARAM, 16);

/** @brief Camera path data.
 *
 * In SH2 the `.cam` files contain this struct, while in SH1 this is part of `s_MapOverlayHeader`.
 */
typedef struct _VC_ROAD_DATA
{
    VC_LIMIT_AREA     lim_sw_0;
    VC_LIMIT_AREA     lim_rd_8;
    VC_ROAD_FLAGS     flags_10          : 8; /** `VC_ROAD_FLAGS` | Path flags. */
    VC_AREA_SIZE_TYPE area_size_type_11 : 2;
    VC_ROAD_TYPE      rd_type_11        : 3; /** Path type. */
    u32               mv_y_type_11      : 3; /** `VC_CAM_MV_TYPE`? */
    s32               lim_rd_max_hy_12  : 8; // In SH2 `max_hy/min_hy` are part of `VC_LIMIT_AREA`, in SH1 these are separate for some reason.
    s32               lim_rd_min_hy_13  : 8;
    s32               ofs_watch_hy_14   : 8;
    u32               field_15          : 4;
    s16               cam_mv_type_14    : 4; /** `VC_CAM_MV_TYPE` */
    s8                fix_ang_x_16;          /** NOTE: Part of union in SH2 `VC_ROAD_DATA`. */
    s8                fix_ang_y_17;
} VC_ROAD_DATA;
STATIC_ASSERT_SIZEOF(VC_ROAD_DATA, 24);

/** @brief Rail camera parementers. */
typedef struct _VC_THROUGH_DOOR_CAM_PARAM
{
    u8      active_f_0;                /** `bool` | Active flag. */
    s8      unk_1[3];
    s32     timer_4;
    s16     rail_ang_y_8;              /** Rail Y angle. */
    s8      unk_A[2];
    VECTOR3 rail_sta_pos_C;            /** Rail start position. */
    s32     rail_sta_to_chara_dist_18; /** Distance from rail start position to locked-on character position. */
} VC_THROUGH_DOOR_CAM_PARAM;
STATIC_ASSERT_SIZEOF(VC_THROUGH_DOOR_CAM_PARAM, 28);

/** @brief Nearby camera path collision. */
typedef struct _VC_NEAR_ROAD_DATA
{
    VC_ROAD_DATA* road_p_0;              /** Path. */
    u8            rd_dir_type_4;
    u8            use_priority_5;
    u8            unk_6[2];
    s32           chara2road_sum_dist_8; /** Character to path distance squared? */
    s32           chara2road_vec_x_C;    /** Character to path distance squared on X axis? */
    s32           chara2road_vec_z_10;   /** Character to path distance squared on Z axis? */
    VC_LIMIT_AREA rd_14;                 /** Path constraint on XZ plane. */
    VC_LIMIT_AREA sw_1C;                 /** Switch(?) path constraint on XZ plane. */
} VC_NEAR_ROAD_DATA;
STATIC_ASSERT_SIZEOF(VC_NEAR_ROAD_DATA, 36);

typedef struct _VC_WORK
{
    u8                        view_cam_active_f_0;
    VC_ROAD_DATA*             vc_road_ary_list_4;             /** Path array. */
    u32                       flags_8;                        /** `VC_FLAGS` */
    u8                        through_door_activate_init_f_C; /** `bool` */
    s8                        unk_D[3];
    VC_THROUGH_DOOR_CAM_PARAM through_door_10;
    s16                       scr_half_ang_wy_2C;
    s16                       scr_half_ang_wx_2E;
    s16                       geom_screen_dist_30;            /** Related to `GsSetProjection`/`g_GameSys.gs_y_res_58A`. */
    s16                       field_32;
    VC_CAM_MV_PARAM           user_cam_mv_prm_34;             /** Look parameters? */
    VECTOR3                   cam_tgt_pos_44;                 /** Target position. */
    VECTOR3                   cam_pos_50;                     /** Position. */
    s16                       cam_mv_ang_y_5C;                /** Angular velocity on the Y axis. */
    s8                        unk_5E[2];
    VECTOR3                   cam_velo_60;                    /** Velocity. */
    s32                       old_cam_excl_area_r_6C;         /** Previous exclusion area radius. */
    VC_WATCH_MV_PARAM         user_watch_mv_prm_70;
    VECTOR3                   watch_tgt_pos_7C;               /** Target look-at position. */
    s32                       watch_tgt_max_y_88;             /** Max look-at Y offset. */
    s16                       watch_tgt_ang_z_8C;             /** Target look-at Z angle. */
    SVECTOR                   cam_mat_ang_8E;                 /** Matrix rotation. */
    u8                        unk_96[2];
    MATRIX                    cam_mat_98;                     /** Matrix. */
    SVECTOR                   ofs_cam_ang_B8;                 /** Offset rotation. */
    SVECTOR                   ofs_cam_ang_spd_C0;             /** Offset rotational speed. */
    SVECTOR                   base_cam_ang_C8;                /** Base rotation. */
    s8                        unk_D0[8];
    u8                        field_D8;                       /** `bool` */
    s8                        unk_D9[3];
    MATRIX                    field_DC;
    u8                        field_FC;                       /** `bool` */
    u8                        field_FD;
    s16                       cam_chara2ideal_ang_y_FE;  
    VECTOR3                   cam_tgt_velo_100;               /** Target velocity. */
    s16                       cam_tgt_mv_ang_y_10C;           /** Target Y angles. */
    s8                        unk_10E[2];
    s32                       cam_tgt_spd_110;                               /** Target speed. */
    VECTOR3                   chara_pos_114;                                 /** Locked-on character position. */
    s32                       chara_bottom_y_120;                            /** Locked-on character bottom height. */
    s32                       chara_top_y_124;                               /** Locked-on character top height. */
    s32                       chara_center_y_128;                            /** Locked-on character center height. */
    s32                       chara_grnd_y_12C;                              /** Locked-on character height from the ground? */
    VECTOR3                   chara_head_pos_130;                            /** Locked-on character head position. */
    s32                       chara_mv_spd_13C;                              /** Locked-on character movement speed. */
    s16                       chara_mv_ang_y_140;                            /** Locked-on character heading angle. */
    s16                       chara_ang_spd_y_142;                           /** Locked-on character heading angle angular speed. */
    s16                       chara_eye_ang_y_144;                           /** Locked-on character look heading angle? */
    s16                       chara_eye_ang_wy_146;                          /** Locked-on character unknown Y angle */
    s32                       chara_watch_xz_r_148;                          /** Locked-on character radius on the XZ plane. */
    VC_NEAR_ROAD_DATA         near_road_ary_14C[CAMERA_PATH_COLL_COUNT_MAX]; /** Nearby camera path collisions. */
    s32                       near_road_suu_2B4;                             /** Count of valid `near_road_ary_14C` entries. */
    VC_NEAR_ROAD_DATA         cur_near_road_2B8;                             /** Closest camera path? */
    struct _SubCharacter*     nearest_enemy_2DC;                             /** Closest enemy character. */
    q19_12                    nearest_enemy_xz_dist_2E0;                     /** Distance to the closest enemy character on the XZ plane. */
    s32                       field_2E4;
} VC_WORK;
STATIC_ASSERT_SIZEOF(VC_WORK, 744);

typedef struct _VbRVIEW
{
    VECTOR3        vp;
    VECTOR3        vr;
    s32            rz;
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

typedef struct _s_Vw_AabbVisibleInFrustumCheck
{
    MATRIX  field_0;
    SVECTOR field_20[8];
    VECTOR3 field_60[8];
    s32     field_C0;
    SVECTOR field_C4[10];
    s32     field_114;
    DVECTOR field_118[24];
    s32     field_178;
} s_Vw_AabbVisibleInFrustumCheck;
STATIC_ASSERT_SIZEOF(s_Vw_AabbVisibleInFrustumCheck, 380);

typedef struct _s_func_8004A54C
{
    u8 field_0[3][3];
} s_func_8004A54C;
STATIC_ASSERT_SIZEOF(s_func_8004A54C, 9);

extern VC_ROAD_DATA      vcNullRoadArray[2];
extern VC_NEAR_ROAD_DATA vcNullNearRoad;
extern VC_WATCH_MV_PARAM deflt_watch_mv_prm;
extern VC_WATCH_MV_PARAM self_view_watch_mv_prm;
extern VC_CAM_MV_PARAM   cam_mv_prm_user;
extern s32               excl_r_ary[9];
extern VC_WORK           vcWork;
extern VECTOR3           vcRefPosSt;
extern VW_VIEW_WORK      vwViewPointInfo;
extern MATRIX            VbWvsMatrix;
extern VC_WATCH_MV_PARAM vcWatchMvPrmSt;
extern s32               vcSelfViewTimer;

// vc_util.c

void vcInitCamera(struct _MapOverlayHeader* map_overlay_ptr, VECTOR3* chr_pos);
void vcSetCameraUseWarp(VECTOR3* chr_pos, s16 chr_ang_y);
s32  vcRetCamMvSmoothF();
void vcSetEvCamRate(s16 ev_cam_rate);
void vcMoveAndSetCamera(s32 in_connect_f, s32 change_debug_mode, s32 for_f, s32 back_f, s32 right_f, s32 left_f, s32 up_f, s32 down_f);
void vcMakeHeroHeadPos(VECTOR3* head_pos);
void vcAddOfsToPos(VECTOR3* out_pos, VECTOR3* in_pos, s16 ofs_xz_r, s16 ang_y, s32 ofs_y);
void vcSetRefPosAndSysRef2CamParam(VECTOR3* ref_pos, s_SysWork* sys_p, s32 for_f, s32 back_f, s32 right_f, s32 left_f, s32 up_f, s32 down_f);
void vcSetRefPosAndCamPosAngByPad(VECTOR3* ref_pos, s_SysWork* sys_p);

// vw_main.c

void           vwInitViewInfo();
GsCOORDINATE2* vwGetViewCoord();
void           vwGetViewPosition(VECTOR3* pos);
void           vwGetViewAngle(SVECTOR* ang);
void           Vw_SetLookAtMatrix(VECTOR3* pos, VECTOR3* lookAt);
void           vwSetCoordRefAndEntou(GsCOORDINATE2* parent_p, s32 ref_x, s32 ref_y, s32 ref_z, s16 cam_ang_y, s16 cam_ang_z, s32 cam_y, s32 cam_xz_r);
void           vwSetViewInfoDirectMatrix(GsCOORDINATE2* pcoord, MATRIX* cammat);
void           vwSetViewInfo();
void           Vw_ClampAngleRange(s16* angleMin, s16* angleMax, s16 angleConstraintMin, s16 angleConstraintMax);

// vw_calc.c

void vwRenewalXZVelocityToTargetPos(s32* velo_x, s32* velo_z, VECTOR3* now_pos, VECTOR3* tgt_pos, s32 tgt_r,
                                    s32 accel, s32 total_max_spd, s32 dec_forwd_lim_spd, s32 dec_accel_side);
void vwLimitOverLimVector(s32* vec_x, s32* vec_z, s32 lim_vec_len, s16 lim_vec_ang_y);
void vwDecreaseSideOfVector(s32* vec_x, s32* vec_z, s32 dec_val, s32 max_side_vec_len, s16 dir_ang_y);
s32  vwRetNewVelocityToTargetVal(s32 now_spd, s32 mv_pos, s32 tgt_pos, s32 accel, s32 total_max_spd, s32 dec_val_lim_spd);
s32  vwRetNewAngSpdToTargetAng(s32 now_ang_spd, s16 now_ang, s16 tgt_ang, s32 accel_spd, s32 total_max_ang_spd, s32 dec_val_lim_spd);
void vwMatrixToAngleYXZ(SVECTOR* ang, MATRIX* mat);
void Vw_MultiplyAndTransformMatrix(MATRIX* transformMat, MATRIX* inMat, MATRIX* outMat);
void vbSetWorldScreenMatrix(GsCOORDINATE2* coord);
void vbSetRefView(VbRVIEW* rview);
void Vw_CoordHierarchyMatrixCompute(GsCOORDINATE2* rootCoord, MATRIX* outMat);
void func_80049AF8(GsCOORDINATE2* rootCoord, MATRIX* outMat);
void func_80049B6C(GsCOORDINATE2* rootCoord, MATRIX* outMat0, MATRIX* outMat1);
void func_80049C2C(MATRIX* mat, s32 x, s32 y, s32 z);
bool Vw_AabbVisibleInScreenCheck(s32 xMin, s32 xMax, s32 yMin, s32 yMax, s32 zMin, s32 zMax);
bool Vw_AabbVisibleInFrustumCheck(MATRIX* modelMat, s16 minX, s16 minY, s16 minZ, s32 maxX, s32 maxY, s32 maxZ, u16 nearPlane, u16 farPlane);
bool func_8004A54C(s_func_8004A54C* arg0);
void vwAngleToVector(SVECTOR* vec, SVECTOR* ang, s32 r);
s32  vwVectorToAngle(SVECTOR* ang, SVECTOR* vec);

/** Performs linear interpolation between Y values based on an input X within the given range. */
s32 vwOresenHokan(s32* y_ary, s32 y_suu, s32 input_x, s32 min_x, s32 max_x);

// vc_main.c

void vcInitVCSystem(VC_ROAD_DATA* vc_road_ary_list);
void vcStartCameraSystem();
void vcEndCameraSystem();
void vcSetFirstCamWork(VECTOR3* cam_pos, s16 chara_eye_ang_y, s32 use_through_door_cam_f);
void vcWorkSetFlags(VC_FLAGS enable, VC_FLAGS disable);
s32  Vc_LookAtOffsetYMaxSet(s32 lookAtOffsetYMax);
void vcUserWatchTarget(VECTOR3* watch_tgt_pos, VC_WATCH_MV_PARAM* watch_prm_p, bool warp_watch_f);
void vcUserCamTarget(VECTOR3* cam_tgt_pos, VC_CAM_MV_PARAM* cam_prm_p, bool warp_cam_f);
void vcChangeProjectionValue(s16 scr_y);
void func_80080D68();
void vcGetNowWatchPos(VECTOR3* watch_pos);
void vcGetNowCamPos(VECTOR3* cam_pos);
void vcReturnPreAutoCamWork(bool warp_f);
void vcSetSubjChara(VECTOR3* chara_pos, s32 chara_bottom_y, s32 chara_top_y, s32 chara_grnd_y, VECTOR3* chara_head_pos,
                    s16 chara_mv_spd, s32 chara_mv_ang_y, s16 chara_ang_spd_y, s16 chara_eye_ang_y, s16 chara_eye_ang_wy, s32 chara_watch_xz_r);
s32  vcExecCamera();
void vcSetAllNpcDeadTimer();
s32  vcRetSmoothCamMvF(VECTOR3* old_pos, VECTOR3* now_pos, SVECTOR* old_ang, SVECTOR* now_ang);
VC_CAM_MV_TYPE vcRetCurCamMvType(VC_WORK* w_p);
bool func_8008150C(s32 posX, s32 posZ);
bool vcRetThroughDoorCamEndF(VC_WORK* w_p);
s32  vcRetFarWatchRate(s32 far_watch_button_prs_f, VC_CAM_MV_TYPE cur_cam_mv_type, VC_WORK* w_p);
s32  vcRetSelfViewEffectRate(VC_CAM_MV_TYPE cur_cam_mv_type, s32 far_watch_rate, VC_WORK* w_p);
void vcSetFlagsByCamMvType(VC_CAM_MV_TYPE cam_mv_type, s32 far_watch_rate, bool all_warp_f);
void vcPreSetDataInVC_WORK(VC_WORK* w_p, VC_ROAD_DATA* vc_road_ary_list);
void vcSetTHROUGH_DOOR_CAM_PARAM_in_VC_WORK(VC_WORK* w_p, THROUGH_DOOR_SET_CMD_TYPE set_cmd_type);
void vcSetNearestEnemyDataInVC_WORK(VC_WORK* w_p);
void vcSetNearRoadAryByCharaPos(VC_WORK* w_p, VC_ROAD_DATA* road_ary_list, s32 half_w, s32 unused, bool near_enemy_f);
s32  vcRetRoadUsePriority(VC_ROAD_TYPE rd_type, s32 unused);
bool vcSetCurNearRoadInVC_WORK(VC_WORK* w_p);
s32  vcGetBestNewCurNearRoad(VC_NEAR_ROAD_DATA** new_cur_pp, VC_CAM_CHK_TYPE chk_type, VECTOR3* pos, VC_WORK* w_p);
s32  vcGetNearestNEAR_ROAD_DATA(VC_NEAR_ROAD_DATA** out_nearest_p_addr, VC_CAM_CHK_TYPE chk_type, VC_ROAD_TYPE rd_type, VECTOR3* pos, VC_WORK* w_p, bool chk_only_set_marge_f);
s32  vcAdvantageDistOfOldCurRoad(VC_NEAR_ROAD_DATA* old_cur_p);
void vcAutoRenewalWatchTgtPosAndAngZ(VC_WORK* w_p, VC_CAM_MV_TYPE cam_mv_type, VC_AREA_SIZE_TYPE cur_rd_area_size, s32 far_watch_rate, s32 self_view_eff_rate);
void vcMakeNormalWatchTgtPos(VECTOR3* watch_tgt_pos, s16* watch_tgt_ang_z_p, VC_WORK* w_p, VC_CAM_MV_TYPE cam_mv_type, VC_AREA_SIZE_TYPE cur_rd_area_size);
void vcMixSelfViewEffectToWatchTgtPos(VECTOR3* watch_tgt_pos, s16* watch_tgt_ang_z_p, s16 effect_rate, VC_WORK* w_p, MATRIX* head_mat, s32 anim_status);
void vcMakeFarWatchTgtPos(VECTOR3* watch_tgt_pos, VC_WORK* w_p, VC_AREA_SIZE_TYPE cur_rd_area_size);
void vcSetWatchTgtXzPos(VECTOR3* watch_pos, VECTOR3* center_pos, VECTOR3* cam_pos, s32 tgt_chara2watch_cir_dist, s32 tgt_watch_cir_r, s16 watch_cir_ang_y);
void vcSetWatchTgtYParam(VECTOR3* watch_pos, VC_WORK* w_p, s32 cam_mv_type, s32 watch_y);
void vcAdjustWatchYLimitHighWhenFarView(VECTOR3* watch_pos, VECTOR3* cam_pos, s16 sy);
void vcAutoRenewalCamTgtPos(VC_WORK* w_p, VC_CAM_MV_TYPE cam_mv_type, VC_CAM_MV_PARAM* cam_mv_prm_p, VC_ROAD_FLAGS cur_rd_flags, VC_AREA_SIZE_TYPE cur_rd_area_size, s32 far_watch_rate);
s32  vcRetMaxTgtMvXzLen(VC_WORK* w_p, VC_CAM_MV_PARAM* cam_mv_prm_p);
void vcMakeIdealCamPosByHeadPos(VECTOR3* ideal_pos, VC_WORK* w_p, VC_AREA_SIZE_TYPE cur_rd_area_size);
void vcMakeIdealCamPosForFixAngCam(VECTOR3* ideal_pos, VC_WORK* w_p);
void vcMakeIdealCamPosForThroughDoorCam(VECTOR3* ideal_pos, VC_WORK* w_p);
void vcMakeIdealCamPosUseVC_ROAD_DATA(VECTOR3* ideal_pos, VC_WORK* w_p, VC_AREA_SIZE_TYPE cur_rd_area_size);
void vcAdjustXzInLimAreaUsingMIN_IN_ROAD_DIST(s32* x_p, s32* z_p, VC_LIMIT_AREA* lim_p);
void vcMakeBasicCamTgtMvVec(VECTOR3* tgt_mv_vec, VECTOR3* ideal_pos, VC_WORK* w_p, s32 max_tgt_mv_xz_len);
void vcAdjTgtMvVecYByCurNearRoad(VECTOR3* tgt_mv_vec, VC_WORK* w_p);
void vcCamTgtMvVecIsFlipedFromCharaFront(VECTOR3*  tgt_mv_vec, VC_WORK* w_p, s32 max_tgt_mv_xz_len, VC_AREA_SIZE_TYPE cur_rd_area_size);
s32  vcFlipFromCamExclusionArea(s16* flip_ang_y_p, s32* old_cam_excl_area_r_p, VECTOR3* in_pos, VECTOR3* chara_pos, s16 chara_eye_ang_y, VC_AREA_SIZE_TYPE cur_rd_area_size);
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
s32  vcCamMatNoise(s32 noise_w, s32 ang_spd1, s32 ang_spd2, s32 vcSelfViewTimer);
s32  Vc_VectorMagnitudeCalc(s32 x, s32 y, s32 z);
s32  vcGetXZSumDistFromLimArea(s32* out_vec_x_p, s32* out_vec_z_p, s32 chk_wld_x, s32 chk_wld_z,
                               s32 lim_min_x, s32 lim_max_x, s32 lim_min_z, s32 lim_max_z, s32 can_ret_minus_dist_f);

static inline void Vc_CurNearRoadSet(VC_WORK* work, VC_NEAR_ROAD_DATA* road)
{
    memcpy(&work->cur_near_road_2B8, road, sizeof(VC_NEAR_ROAD_DATA));
}

static inline void Vc_FlagClear(s32 flag)
{
    vcWork.flags_8 &= ~flag;
}

static inline void Vc_FlagSet(s32 flag)
{
    vcWork.flags_8 |= flag;
}

#endif
