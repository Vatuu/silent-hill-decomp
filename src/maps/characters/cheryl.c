#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "bodyprog/player.h"
#include "maps/shared.h"
#include "maps/characters/cheryl.h"

/** AI code for `Chara_Cheryl`
 *
 * Included in:
 *  MAP0_S00
 */

void Cheryl_Update(s_SubCharacter* cheryl, s_AnmHeader* anmHdr, GsCOORDINATE2* coords) // 0x800D7FB8
{
    if (cheryl->model.charaId != Chara_Cheryl)
    {
        Cheryl_Init(cheryl);
    }

    Cheryl_ControlUpdate(cheryl, coords);
    Cheryl_MovementUpdate(cheryl, coords);
    Cheryl_AnimUpdate(cheryl, anmHdr, coords);
}

void Cheryl_AnimUpdate(s_SubCharacter* cheryl, s_AnmHeader* anmHdr, GsCOORDINATE2* coords) // 0x800D802C
{
    q19_12      moveSpeed;
    q19_12      duration;
    s_AnimInfo* animInfo;

    #define cherylProps cheryl->properties.cheryl

    if (cherylProps.controlState == 1)
    {
        D_800DF1CC = Q12_MULT_PRECISE(cheryl->moveSpeed, Q12(30.2f));
    }

    moveSpeed         = MIN(cheryl->moveSpeed, Q12(2.5f));
    cheryl->moveSpeed = moveSpeed;

    if (cherylProps.controlState == 2)
    {
        animInfo = CHERYL_ANIM_INFOS;

        if (moveSpeed <= Q12(1.5f))
        {
            duration = Q12_MULT_PRECISE(moveSpeed, Q12(18.6f));
        }
        else
        {
            duration = Q12(27.9f) - 1;
        }

        animInfo[ANIM_STATUS(CherylAnim_RunForward, true)].duration.constant = duration;
    }

    if (cherylProps.properties_F0.val32 == 0)
    {
        CHERYL_ANIM_INFOS[cheryl->model.anim.status].playbackFunc(&cheryl->model, anmHdr, coords, &CHERYL_ANIM_INFOS[cheryl->model.anim.status]);
    }

    #undef cherylProps
}

void Cheryl_MovementUpdate(s_SubCharacter* cheryl, GsCOORDINATE2* coords) // 0x800D8124
{
    VECTOR3 pos; // @hack Unused but required for match.
    VECTOR3 offset;
    q19_12  moveSpeed;
    q3_12   headingAngle;
    q19_12  moveDist;
    s32     scaleRestoreShift;
    u32     scaleReduceShift;

    pos          = cheryl->position;
    moveSpeed    = cheryl->moveSpeed;
    headingAngle = cheryl->headingAngle;
    moveDist     = Q12_MULT_PRECISE(moveSpeed, g_DeltaTime);

    scaleRestoreShift = OVERFLOW_GUARD(moveDist);
    scaleReduceShift  = scaleRestoreShift >> 1;

    offset.vx = (u32)Q12_MULT_PRECISE(moveDist >> scaleReduceShift, Math_Sin(headingAngle) >> scaleReduceShift) << scaleRestoreShift;
    offset.vz = (u32)Q12_MULT_PRECISE(moveDist >> scaleReduceShift, Math_Cos(headingAngle) >> scaleReduceShift) << scaleRestoreShift;
    offset.vy = Q12_MULT_PRECISE(cheryl->fallSpeed, g_DeltaTime);

    Collision_WallDetect(&sharedData_800E39BC_0_s00, &offset, cheryl);

    cheryl->position.vx += offset.vx;
    cheryl->position.vy += sharedData_800E39BC_0_s00.offset_0.vy;
    cheryl->position.vz += offset.vz;

    if (cheryl->position.vy > sharedData_800E39BC_0_s00.field_C)
    {
        cheryl->position.vy = sharedData_800E39BC_0_s00.field_C;
        cheryl->fallSpeed   = Q12(0.0f);
    }

    coords->coord.t[0] = Q12_TO_Q8(cheryl->position.vx);
    coords->coord.t[1] = Q12_TO_Q8(cheryl->position.vy);
    coords->coord.t[2] = Q12_TO_Q8(cheryl->position.vz);
}

void Cheryl_ControlUpdate(s_SubCharacter* cheryl, GsCOORDINATE2* coords) // 0x800D8310
{
    s_Collision coll;
    e_SfxId     sfx;
    s8          pitch0;
    s8          pitch1;
    q23_8       distToPlayerSqr;

    #define cherylProps cheryl->properties.cheryl
    #define playerChara g_SysWork.playerWork.player
    #define playerProps playerChara.properties.player

    D_800E3A30 = Q12(0.0f);

    switch (cherylProps.controlState)
    {
        case CherylControl_Idle:
            if (cherylProps.moveDistance_126 != Q12(0.0f))
            {
                cherylProps.moveDistance_126 -= TIMESTEP_SCALE_30_FPS(g_DeltaTime, Q12(0.4f)) * 2;
                if (cherylProps.moveDistance_126 < Q12(0.0f))
                {
                    cherylProps.moveDistance_126 = Q12(0.0f);
                }
            }

            Model_AnimStatusSet(&cheryl->model, CherylAnim_Idle, false);
            Character_AnimStateReset(cheryl);

            cherylProps.moveDistance_124 = Q12(0.0f);
            break;

        case CherylControl_WalkForward:
            cherylProps.moveDistance_126 = cherylProps.moveDistance_124;

            Model_AnimStatusSet(&cheryl->model, CherylAnim_WalkForward, false);
            Character_AnimStateReset(cheryl);
            break;

        case CherylControl_RunForward:
            cherylProps.moveDistance_126 = cherylProps.moveDistance_124;

            Model_AnimStatusSet(&cheryl->model, CherylAnim_RunForward, false);
            Character_AnimStateReset(cheryl);
            break;

        case CherylControl_3:
            if (cherylProps.moveDistance_126 != Q12(0.0f))
            {
                cherylProps.moveDistance_126 -= TIMESTEP_SCALE_30_FPS(g_DeltaTime, Q12(0.4f)) * 2;
                if (cherylProps.moveDistance_126 < Q12(0.0f))
                {
                    cherylProps.moveDistance_126 = Q12(0.0f);
                }
            }

            D_800E3A30 = g_DeltaTime * 7;

            Model_AnimStatusSet(&cheryl->model, CherylAnim_WalkForward, false);
            Character_AnimStateReset(cheryl);

            playerProps.headingAngle_124 = Q12_ANGLE(0.0f);
            cherylProps.moveDistance_124 = Q12(0.0f);
            break;

        case CherylControl_4:
            if (cherylProps.moveDistance_126 != Q12(0.0f))
            {
                cherylProps.moveDistance_126 -= TIMESTEP_SCALE_30_FPS(g_DeltaTime, Q12(0.4f)) * 2;
                if (cherylProps.moveDistance_126 < Q12(0.0f))
                {
                    cherylProps.moveDistance_126 = Q12(0.0f);
                }
            }

            D_800E3A30 = g_DeltaTime * -7;

            Model_AnimStatusSet(&cheryl->model, CherylAnim_WalkForward, false);
            Character_AnimStateReset(cheryl);

            playerProps.headingAngle_124 = Q12_ANGLE(0.0f);
            cherylProps.moveDistance_124 = Q12(0.0f);
            break;
    }

    Collision_Get(&coll, cheryl->position.vx, cheryl->position.vz);
    func_8007FDE0(coll.field_8, &sfx, &pitch0, &pitch1);

    distToPlayerSqr = SQUARE(Q12_TO_Q8(cheryl->position.vx - playerChara.position.vx)) +
                      SQUARE(Q12_TO_Q8(cheryl->position.vz - playerChara.position.vz));

    if (g_Player_DisableControl)
    {
        switch (cherylProps.controlState)
        {
            case CherylControl_WalkForward:
                sharedFunc_800D908C_0_s00(ANIM_STATUS(CherylAnim_WalkForward, true), cheryl, 16, 28, Sfx_CherylFootstep, pitch0);
                break;

            case CherylControl_RunForward:
                sharedFunc_800D908C_0_s00(ANIM_STATUS(CherylAnim_RunForward, true), cheryl, 53, 42, Sfx_CherylFootstep, pitch1);
                break;
        }
    }
    else
    {
        switch (cherylProps.controlState)
        {
            case CherylControl_WalkForward:
                Cheryl_FootstepSfxPlay(ANIM_STATUS(CherylAnim_WalkForward, true), cheryl, 16, 28, distToPlayerSqr, pitch0);
                break;

            case CherylControl_RunForward:
                Cheryl_FootstepSfxPlay(ANIM_STATUS(CherylAnim_RunForward, true), cheryl, 53, 42, distToPlayerSqr, pitch1);
                break;
        }
    }

    cheryl->rotation.vy  = Q12_ANGLE_ABS(cheryl->rotation.vy + Q8_TO_Q4(D_800E3A30));
    cheryl->headingAngle = cheryl->rotation.vy;
    cheryl->moveSpeed    = cherylProps.moveDistance_124;
    cheryl->fallSpeed   += g_GravitySpeed;

    coords->flg = false;
    Math_RotMatrixZxyNegGte(&cheryl->rotation, &coords->coord);
}

bool Cheryl_FootstepSfxPlay(s32 animStatus, s_SubCharacter* cheryl,
                            s32 leftFootstepKeyframeIdx, s32 rightFootstepKeyframeIdx, q23_8 distToPlayerSqr, s32 pitch) // 0x800D8748
{
    q24_8 distSqr;
    u32   vol;

    #define cherylProps cheryl->properties.cheryl

    if (cheryl->model.anim.status == animStatus)
    {
        // Compute volume.
        if (distToPlayerSqr >= SQUARE(2000))
        {
            if (distToPlayerSqr <= 12000000)
            {
                distSqr = distToPlayerSqr;
            }
            else
            {
                distSqr = 12000000;
            }
        }
        else
        {
            distSqr = SQUARE(2000);
        }
        vol = (12000000 - distSqr) >> 16;

        // Play right footstep SFX.
        if (cheryl->model.anim.keyframeIdx >= rightFootstepKeyframeIdx)
        {
            if (!(cherylProps.flags & CherylFlag_FootstepRight))
            {
                func_8005DD44(Sfx_CherylFootstep, &cheryl->position, Q8_FRACT(vol), pitch);
                cherylProps.flags |= CherylFlag_FootstepRight;
                return true;
            }
        }
        else
        {
            cherylProps.flags &= ~CherylFlag_FootstepRight;
        }

        // Play left footstep SFX.
        if (cheryl->model.anim.keyframeIdx >= leftFootstepKeyframeIdx)
        {
            if (!(cherylProps.flags & CherylFlag_FootstepLeft))
            {
                func_8005DD44(Sfx_CherylFootstep, &cheryl->position, Q8_FRACT(vol), pitch);
                cherylProps.flags |= CherylFlag_FootstepLeft;
                return true;
            }
        }
        else
        {
            cherylProps.flags &= ~CherylFlag_FootstepLeft;
        }
    }

    return false;

    #undef cherylProps
}

void Cheryl_Init(s_SubCharacter* cheryl) // 0x800D8888
{
    sharedFunc_800D923C_0_s00(cheryl);
    D_800E3A30 = Q12(0.0f);
}
