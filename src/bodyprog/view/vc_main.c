#include "common.h"

#include "bodyprog/vw_system.h"
#include "bodyprog/math.h"

INCLUDE_ASM("asm/bodyprog/nonmatchings/view/vc_main", vcInitVCSystem);

INCLUDE_ASM("asm/bodyprog/nonmatchings/view/vc_main", vcStartCameraSystem);

void vcEndCameraSystem(void) // 0x80080A04
{
    vcWork.view_cam_active_f_0 = 0;
}

s32 func_80080A10(void) // 0x80080A10
{
    // TODO: bitfield access?
    return (vcWork.cur_near_road_2B8.road_p_0->cam_mv_type_14 >> 8) & 0xF;
}

void func_80080A30(s32 arg0) // 0x80080A30
{
    vcWork.field_2E4 = arg0;
}

s32 func_80080A3C(void) // 0x80080A3C
{
    return vcWork.field_2E4;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/view/vc_main", vcSetFirstCamWork);

INCLUDE_ASM("asm/bodyprog/nonmatchings/view/vc_main", func_80080B58);

void vcWorkSetFlags(VC_FLAGS enable, VC_FLAGS disable) // 0x80080BF8
{
    vcWork.flags_8 = (vcWork.flags_8 | enable) & ~disable;
}

s32 func_80080C18(s32 arg0) // 0x80080C18
{
    s32 prev_val = vcWork.watch_tgt_max_y_88;
    vcWork.watch_tgt_max_y_88 = arg0;
    return prev_val;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/view/vc_main", vcUserWatchTarget);

INCLUDE_ASM("asm/bodyprog/nonmatchings/view/vc_main", vcUserCamTarget);

void vcChangeProjectionValue(s16 scr_y) // 0x80080D5C
{
    vcWork.geom_screen_dist_30 = scr_y;
}

void func_80080D68(void) // 0x80080D68
{
    vcWork.field_D8 = 1;
}

void vcGetNowWatchPos(VECTOR3 *watch_pos) // 0x80080D78
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
    watch_pos->vx = Math_MulFixed(Math_MulFixed(r, sin_y, 0xC), cos_x, 0xC) +
                    vcWork.cam_pos_50.vx;
    watch_pos->vz = Math_MulFixed(Math_MulFixed(r, cos_y, 0xC), cos_x, 0xC) +
                    vcWork.cam_pos_50.vz;
    watch_pos->vy = vcWork.cam_pos_50.vy - Math_MulFixed(r, sin_x, 0xC);
}

void vcGetNowCamPos(VECTOR3 *cam_pos) // 0x80080EA8
{
    *cam_pos = vcWork.cam_pos_50;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/view/vc_main", vcReturnPreAutoCamWork);

INCLUDE_ASM("asm/bodyprog/nonmatchings/view/vc_main", vcSetSubjChara);

INCLUDE_ASM("asm/bodyprog/nonmatchings/view/vc_main", vcExecCamera);

INCLUDE_ASM("asm/bodyprog/nonmatchings/view/vc_main", vcSetAllNpcDeadTimer);

INCLUDE_ASM("asm/bodyprog/nonmatchings/view/vc_main", vcRetSmoothCamMvF);

INCLUDE_ASM("asm/bodyprog/nonmatchings/view/vc_main", vcRetCurCamMvType);

INCLUDE_ASM("asm/bodyprog/nonmatchings/view/vc_main", func_8008150C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/view/vc_main", vcRetThroughDoorCamEndF);

INCLUDE_ASM("asm/bodyprog/nonmatchings/view/vc_main", vcRetFarWatchRate);

INCLUDE_ASM("asm/bodyprog/nonmatchings/view/vc_main", vcRetSelfViewEffectRate);

INCLUDE_ASM("asm/bodyprog/nonmatchings/view/vc_main", vcSetFlagsByCamMvType);

INCLUDE_ASM("asm/bodyprog/nonmatchings/view/vc_main", vcPreSetDataInVC_WORK);

INCLUDE_ASM("asm/bodyprog/nonmatchings/view/vc_main", vcSetTHROUGH_DOOR_CAM_PARAM_in_VC_WORK);

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

INCLUDE_ASM("asm/bodyprog/nonmatchings/view/vc_main", vcAdvantageDistOfOldCurRoad);

INCLUDE_ASM("asm/bodyprog/nonmatchings/view/vc_main", vcAutoRenewalWatchTgtPosAndAngZ);

INCLUDE_ASM("asm/bodyprog/nonmatchings/view/vc_main", vcMakeNormalWatchTgtPos);

INCLUDE_ASM("asm/bodyprog/nonmatchings/view/vc_main", vcMixSelfViewEffectToWatchTgtPos);

INCLUDE_ASM("asm/bodyprog/nonmatchings/view/vc_main", vcMakeFarWatchTgtPos);

INCLUDE_ASM("asm/bodyprog/nonmatchings/view/vc_main", vcSetWatchTgtXzPos);

void vcSetWatchTgtYParam(VECTOR3 *watch_pos, VC_WORK *w_p, s32 cam_mv_type,
                         s32 watch_y) // 0x800835C0
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

INCLUDE_ASM("asm/bodyprog/nonmatchings/view/vc_main", vcAdjustWatchYLimitHighWhenFarView);

INCLUDE_ASM("asm/bodyprog/nonmatchings/view/vc_main", vcAutoRenewalCamTgtPos);

INCLUDE_ASM("asm/bodyprog/nonmatchings/view/vc_main", vcRetMaxTgtMvXzLen);

INCLUDE_ASM("asm/bodyprog/nonmatchings/view/vc_main", vcMakeIdealCamPosByHeadPos);

INCLUDE_ASM("asm/bodyprog/nonmatchings/view/vc_main", vcMakeIdealCamPosForFixAngCam);

INCLUDE_ASM("asm/bodyprog/nonmatchings/view/vc_main", vcMakeIdealCamPosForThroughDoorCam);

INCLUDE_ASM("asm/bodyprog/nonmatchings/view/vc_main", vcMakeIdealCamPosUseVC_ROAD_DATA);

INCLUDE_ASM("asm/bodyprog/nonmatchings/view/vc_main", vcAdjustXzInLimAreaUsingMIN_IN_ROAD_DIST);

INCLUDE_ASM("asm/bodyprog/nonmatchings/view/vc_main", vcMakeBasicCamTgtMvVec);

INCLUDE_ASM("asm/bodyprog/nonmatchings/view/vc_main", vcAdjTgtMvVecYByCurNearRoad);

INCLUDE_ASM("asm/bodyprog/nonmatchings/view/vc_main", vcCamTgtMvVecIsFlipedFromCharaFront);

INCLUDE_ASM("asm/bodyprog/nonmatchings/view/vc_main", vcFlipFromCamExclusionArea);

INCLUDE_ASM("asm/bodyprog/nonmatchings/view/vc_main", vcGetUseWatchAndCamMvParam);

INCLUDE_ASM("asm/bodyprog/nonmatchings/view/vc_main", vcRenewalCamData);

INCLUDE_ASM("asm/bodyprog/nonmatchings/view/vc_main", vcRenewalCamMatAng);

INCLUDE_ASM("asm/bodyprog/nonmatchings/view/vc_main", vcMakeNewBaseCamAng);

INCLUDE_ASM("asm/bodyprog/nonmatchings/view/vc_main", vcRenewalBaseCamAngAndAdjustOfsCamAng);

void vcMakeOfsCamTgtAng(SVECTOR *ofs_tgt_ang, MATRIX *base_matT,
                        VC_WORK *w_p) // 0x800852C8
{
    SVECTOR vec;

    vec.vx = (w_p->watch_tgt_pos_7C.vx - w_p->cam_pos_50.vx) >> 4;
    vec.vy = (w_p->watch_tgt_pos_7C.vy - w_p->cam_pos_50.vy) >> 4;
    vec.vz = (w_p->watch_tgt_pos_7C.vz - w_p->cam_pos_50.vz) >> 4;
    ApplyMatrixSV(base_matT, &vec, &vec);
    vwVectorToAngle(ofs_tgt_ang, &vec);
    ofs_tgt_ang->vz = w_p->watch_tgt_ang_z_8C;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/view/vc_main", vcMakeOfsCam2CharaBottomAndTopAngByBaseMatT);

INCLUDE_ASM("asm/bodyprog/nonmatchings/view/vc_main", vcAdjCamOfsAngByCharaInScreen);

INCLUDE_ASM("asm/bodyprog/nonmatchings/view/vc_main", vcAdjCamOfsAngByOfsAngSpd);

void vcMakeCamMatAndCamAngByBaseAngAndOfsAng(SVECTOR *cam_mat_ang,
                                             MATRIX  *cam_mat,
                                             SVECTOR *base_cam_ang,
                                             SVECTOR *ofs_cam_ang,
                                             VECTOR3 *cam_pos) // 0x800857EC
{
    MATRIX base_mat;
    MATRIX ofs_mat;

    cam_mat->t[0] = cam_pos->vx >> 4;
    cam_mat->t[1] = cam_pos->vy >> 4;
    cam_mat->t[2] = cam_pos->vz >> 4;
    func_80096C94(base_cam_ang, &base_mat);
    func_80096C94(ofs_cam_ang, &ofs_mat);
    MulMatrix0(&base_mat, &ofs_mat, cam_mat);
    vwMatrixToAngleYXZ(cam_mat_ang, cam_mat);
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/view/vc_main", vcSetDataToVwSystem);

INCLUDE_ASM("asm/bodyprog/nonmatchings/view/vc_main", vcCamMatNoise);

INCLUDE_ASM("asm/bodyprog/nonmatchings/view/vc_main", Math_VectorMagnitude);

INCLUDE_ASM("asm/bodyprog/nonmatchings/view/vc_main", vcGetXZSumDistFromLimArea);
