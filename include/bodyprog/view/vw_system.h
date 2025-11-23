#ifndef _BODYPROG_VIEW_VWSYSTEM_H
#define _BODYPROG_VIEW_VWSYSTEM_H

#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>

#include "bodyprog/view/enums.h"
#include "bodyprog/view/structs.h"
#include "bodyprog/view/vc_main.h"
#include "bodyprog/view/vc_util.h"
#include "bodyprog/view/vw_calc.h"
#include "bodyprog/view/vw_main.h"

// TODO:
// - Split into 4 separate headers.
// - Add doc comments above func declarations.
// - Flags below are from SH2, most seem to match with SH but there might be some differences.

/** @brief GLOSSARY OF ABBREVIATIONS
 *
 * ACCEL: Acceleration
 * ANG:   Angle
 * ARY:   Array
 * CIR:   Circle
 * DEFLT: Default
 * EFF:   Effective?
 * EV:    Elevation?
 * EXCL:  Exclusion
 * F:     Boolean or bit flag
 * FIX:   Fixed in place
 * FS:    Bit flags
 * GRND:  Ground
 * H:     Height
 * LIM:   Limit
 * MV:    Move
 * OFS:   Offset
 * P:     Pointer
 * PRIO:  Priority
 * PRM:   Parameter/parameters
 * R:     Radius
 * RD:    Road
 * SCR:   Screen
 * SPD:   Speed
 * STA:   Start
 * SV:    Swivel?
 * SW:    Switch
 * TGT:   Target
 * VELO:  Velocity
 * VB:    ?
 * VB:    ?
 * VC:    Virtual camera
 * VW:    View
 */

/** @brief GLOSSARY OF JAPANGLISH TERMS
 *
 * Area:         A camera path's spatial constraint defining its area of influence.
 * Entou:        "Cylinder" in Japanese. Refers to a 2D radius on the XZ plane.
 * Exclusion:    Threshold or boundary. Used in the context of a camera sphere.
 * Eye:          ?
 * Flipped:      ?
 * Limit area:   2D AABB parameters defining a camera path's spatial constraint.
 * Marge:        Merge.
 * Near road:    Nearby camera path collision containing info about a path's relation to the player in space (distance, priority, etc.).
 *               An array of these is kept to track which path should take effect.
 * Oresen hokan: Polyline interpolation, linear interpolation over an array of values.
 * Renewal:      Reset.
 * Road:         Camera path. A region which dictates specific camera behaviors while the player is inside.
 * Self view:    First-person view.
 * Suu:          "Count" in Japanese. Usually refers to the number of entries in an array or is included in enums to denote the number of entries it contains.
 * Switch:       ?
 * Through door: Rail camera.
 * Watch:        Camera look-at.
 */

extern VC_ROAD_DATA      vcNullRoadArray[2];
extern VC_NEAR_ROAD_DATA vcNullNearRoad;
extern VC_WATCH_MV_PARAM deflt_watch_mv_prm;
extern VC_WATCH_MV_PARAM self_view_watch_mv_prm;
extern VC_CAM_MV_PARAM   cam_mv_prm_user;
extern q19_12            excl_r_ary[9];
extern VC_WORK           vcWork;
extern VECTOR3           vcRefPosSt; /** Q19.12 */
extern VW_VIEW_WORK      vwViewPointInfo;
extern MATRIX            VbWvsMatrix;
extern VC_WATCH_MV_PARAM vcWatchMvPrmSt;
extern q19_12            vcSelfViewTimer;

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
