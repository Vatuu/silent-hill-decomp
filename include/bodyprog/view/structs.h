#ifndef _BODYPROG_VIEW_STRUCTS_H
#define _BODYPROG_VIEW_STRUCTS_H

#include "bodyprog/view/enums.h"

#define CAMERA_PATH_COLL_COUNT_MAX 10

/** @brief 2D area constraint on the XZ plane. */
typedef struct _VC_LIMIT_AREA
{
    q11_4 min_hx;
    q11_4 max_hx;
    q11_4 min_hz;
    q11_4 max_hz;
} VC_LIMIT_AREA;
STATIC_ASSERT_SIZEOF(VC_LIMIT_AREA, 8);

/** @brief Camera internal info. */
typedef struct _VC_CAMERA_INTINFO
{
    u32   mode;      /** Mode state step. */
    u8    mv_smooth; /** `VC_CAM_MV_TYPE` */
    // 1 byte of padding.
    q3_12 ev_cam_rate;
} VC_CAMERA_INTINFO;
STATIC_ASSERT_SIZEOF(VC_CAMERA_INTINFO, 8);

/** @brief Camera look-at move parameters.
 * TODO: These don't seem to be angles like the names would suggest, but distances don't fit either.
 */
typedef struct _VC_WATCH_MV_PARAM
{
    q19_12 ang_accel_x;   /** Angle acceleration on X axis. */
    q19_12 ang_accel_y;   /** Angle acceleration on Y axis. */
    q3_12  max_ang_spd_x; /** Max angle speed on X axis. */
    q3_12  max_ang_spd_y; /** Max angle speed on Y axis. */
} VC_WATCH_MV_PARAM;
STATIC_ASSERT_SIZEOF(VC_WATCH_MV_PARAM, 12);

/** @brief Camera move parameters. */
typedef struct _VC_CAM_MV_PARAM
{
    q19_12 accel_xz;   /** Speed acceleration on XZ plane. */
    q19_12 accel_y;    /** Speed acceleration on Y axis. */
    q19_12 max_spd_xz; /** Max speed on XZ plane. */
    q19_12 max_spd_y;  /** Max speed on Y axis. */
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
    u32               mv_y_type_11      : 3; /** `VC_CAM_MV_TYPE` */
    q27_4             lim_rd_max_hy_12  : 8; /** In SH2, `max_hy` and `min_hy` are part of `VC_LIMIT_AREA`.In SH1, these are separate for some reason. */
    q27_4             lim_rd_min_hy_13  : 8;
    q27_4             ofs_watch_hy_14   : 8;
    u32               field_15          : 4;
    s16               cam_mv_type_14    : 4; /** `VC_CAM_MV_TYPE` */
    q0_7              fix_ang_x_16;          /** NOTE: Part of union in SH2 `VC_ROAD_DATA`. */
    q0_7              fix_ang_y_17;
} VC_ROAD_DATA;
STATIC_ASSERT_SIZEOF(VC_ROAD_DATA, 24);

/** @brief Rail camera parementers. */
typedef struct _VC_THROUGH_DOOR_CAM_PARAM
{
    u8      active_f_0;                /** `bool` | Active flag. */
    // 3 bytes of padding.
    q19_12  timer_4;
    q3_12   rail_ang_y_8;              /** Rail Y angle. */
    // 2 bytes of padding.
    VECTOR3 rail_sta_pos_C;            /** Rail start position. */
    s32     rail_sta_to_chara_dist_18; /** Distance from rail start position to locked-on character position. */
} VC_THROUGH_DOOR_CAM_PARAM;
STATIC_ASSERT_SIZEOF(VC_THROUGH_DOOR_CAM_PARAM, 28);

/** @brief Nearby camera path collision. */
typedef struct _VC_NEAR_ROAD_DATA
{
    VC_ROAD_DATA* road_p_0;              /** Path associated with the collision. */
    u8            rd_dir_type_4;         /** `VC_ROAD_DIR_TYPE` */
    u8            use_priority_5;        /** Usage priority in case of overlap. Higher values take precedence. */
    // 2 bytes of padding.
    s32           chara2road_sum_dist_8; /** Character to path distance. */
    q19_12        chara2road_vec_x_C;    /** Character to path distance on X axis. */
    q19_12        chara2road_vec_z_10;   /** Character to path distance on Z axis. */
    VC_LIMIT_AREA rd_14;                 /** Camera path constraint on XZ plane. */
    VC_LIMIT_AREA sw_1C;                 /** Switch constraint on XZ plane. */
} VC_NEAR_ROAD_DATA;
STATIC_ASSERT_SIZEOF(VC_NEAR_ROAD_DATA, 36);

typedef struct _VC_WORK
{
    u8                        view_cam_active_f_0;            /** `bool` */
    VC_ROAD_DATA*             vc_road_ary_list_4;             /** Camera paths for the active map. */
    u32                       flags_8;                        /** `VC_FLAGS` */
    u8                        through_door_activate_init_f_C; /** `bool` */
    // 3 bytes of padding.
    VC_THROUGH_DOOR_CAM_PARAM through_door_10;                /** Active rail camera data? */
    q3_12                     scr_half_ang_wy_2C;
    q3_12                     scr_half_ang_wx_2E;
    s16                       geom_screen_dist_30;            /** Related to `GsSetProjection`/`g_GameSys.gs_y_res_58A`. */
    s16                       field_32; // Padding? Not used.
    VC_CAM_MV_PARAM           user_cam_mv_prm_34;             /** Look parameters? */
    VECTOR3                   cam_tgt_pos_44;                 /** Target camera position. */
    VECTOR3                   cam_pos_50;                     /** Q19.12 | Camera position. */
    q3_12                     cam_mv_ang_y_5C;                /** Angular velocity on the Y axis. */
    // 2 bytes of padding.
    VECTOR3                   cam_velo_60;                    /** Q19.12 | Camera velocity. */
    s32                       old_cam_excl_area_r_6C;         /** Previous exclusion area radius. */
    VC_WATCH_MV_PARAM         user_watch_mv_prm_70;
    VECTOR3                   watch_tgt_pos_7C;               /** Q19.12 | Target look-at position. */
    s32                       watch_tgt_max_y_88;             /** Max look-at Y offset. */
    s16                       watch_tgt_ang_z_8C;             /** Target look-at Z angle. */
    SVECTOR                   cam_mat_ang_8E;                 /** Matrix rotation. */
    // 2 bytes of padding.
    MATRIX                    cam_mat_98;                     /** Matrix. */
    SVECTOR                   ofs_cam_ang_B8;                 /** Offset rotation. */
    SVECTOR                   ofs_cam_ang_spd_C0;             /** Offset rotational speed. */
    SVECTOR                   base_cam_ang_C8;                /** Base rotation. */
    s8                        unk_D0[8];                      // TODO: Possibly unused or debug data?
    u8                        field_D8;                       /** `bool` */
    // 3 bytes of padding.
    MATRIX                    field_DC;
    u8                        field_FC;                       /** `bool` */
    u8                        field_FD; // Padding?
    q3_12                     cam_chara2ideal_ang_y_FE;
    VECTOR3                   cam_tgt_velo_100;               /** Target velocity. */
    q3_12                     cam_tgt_mv_ang_y_10C;           /** Target Y angles. */
    // 2 bytes of padding.
    q19_12                    cam_tgt_spd_110;                               /** Target speed. */
    VECTOR3                   chara_pos_114;                                 /** Locked-on character position. */
    q19_12                    chara_bottom_y_120;                            /** Locked-on character bottom height. */
    q19_12                    chara_top_y_124;                               /** Locked-on character top height. */
    q19_12                    chara_center_y_128;                            /** Locked-on character center height. */
    q19_12                    chara_grnd_y_12C;                              /** Locked-on character height from the ground? */
    VECTOR3                   chara_head_pos_130;                            /** Q19.12 | Locked-on character head position. */
    q19_12                    chara_mv_spd_13C;                              /** Locked-on character movement speed. */
    q3_12                     chara_mv_ang_y_140;                            /** Locked-on character heading angle. */
    q3_12                     chara_ang_spd_y_142;                           /** Locked-on character heading angle angular speed. */
    q3_12                     chara_eye_ang_y_144;                           /** Locked-on character look heading angle? */
    q3_12                     chara_eye_ang_wy_146;                          /** Locked-on character unknown Y angle */
    q19_12                    chara_watch_xz_r_148;                          /** Locked-on character radius on the XZ plane. */
    VC_NEAR_ROAD_DATA         near_road_ary_14C[CAMERA_PATH_COLL_COUNT_MAX]; /** Nearby camera path collisions. */
    q19_12                    near_road_suu_2B4;                             /** Count of valid `near_road_ary_14C` entries. */
    VC_NEAR_ROAD_DATA         cur_near_road_2B8;                             /** Closest camera path? */
    struct _SubCharacter*     nearest_enemy_2DC;                             /** Closest enemy character. */
    q19_12                    nearest_enemy_xz_dist_2E0;                     /** Distance to the closest enemy character on the XZ plane. */
    q19_12                    watch_pos_y_2E4;                               /** Guessed name. Camera look-at Y position base? Combined with another value later. */
} VC_WORK;
STATIC_ASSERT_SIZEOF(VC_WORK, 744);

/** @brief Camera view matrix. */
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
    VECTOR3       worldpos; /** Q19.12 | Camera world position. */
    SVECTOR       worldang; /** Q3.12 | Camera world rotation. */
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

#endif
