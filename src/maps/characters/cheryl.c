#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "bodyprog/player_logic.h"
#include "maps/shared.h"
#include "maps/characters/cheryl.h"

/** AI code for `Chara_Cheryl`
 *
 * Included in:
 *  MAP0_S00
 */

void Ai_Cheryl_Update(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* coords) // 0x800D7FB8
{
    if (chara->model_0.charaId_0 != Chara_Cheryl)
    {
        Ai_Cheryl_Init(chara);
    }

    Ai_Cheryl_AnimStateUpdate(chara, coords);
    Ai_Cheryl_MovementUpdate(chara, coords);
    Ai_Cheryl_AnimUpdate(chara, anmHdr, coords);
}

void Ai_Cheryl_AnimUpdate(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* coord) // 0x800D802C
{
    q19_12      moveSpeed;
    q19_12      animDur;
    s_AnimInfo* animInfo;

#define dahliaProps (chara->properties_E4.dahlia)

    if (dahliaProps.stateIdx0 == 1)
    {
        D_800DF1CC = Q12_MULT_PRECISE(chara->moveSpeed_38, Q12(30.2f));
    }

    moveSpeed           = MIN(chara->moveSpeed_38, Q12(2.5f));
    chara->moveSpeed_38 = moveSpeed;

    if (dahliaProps.stateIdx0 == 2)
    {
        animInfo = CHERYL_ANIM_INFOS;
        if (moveSpeed <= Q12(1.5f))
        {
            animDur = Q12_MULT_PRECISE(moveSpeed, Q12(18.6f));
        }
        else
        {
            animDur = Q12(27.9f) - 1;
        }

        animInfo[7].duration_8.constant = animDur;
    }

    if (dahliaProps.properties_F0.val32 == 0)
    {
        CHERYL_ANIM_INFOS[chara->model_0.anim_4.status_0].updateFunc_0(&chara->model_0, anmHdr, coord, &CHERYL_ANIM_INFOS[chara->model_0.anim_4.status_0]);
    }
}

void Ai_Cheryl_MovementUpdate(s_SubCharacter* chara, GsCOORDINATE2* coord) // 0x800D8124
{
    VECTOR3 pos;               // @hack Unused but required.
    VECTOR3 offset;
    q19_12  moveSpeed;
    q3_12   headingAngle;
    q19_12  moveAmt;
    s32     scaleRestoreShift;
    u32     scaleReduceShift;

    pos          = chara->position_18;
    moveSpeed    = chara->moveSpeed_38;
    headingAngle = chara->headingAngle_3C;
    moveAmt      = Q12_MULT_PRECISE(moveSpeed, g_DeltaTime0);

    scaleRestoreShift = OVERFLOW_GUARD(moveAmt);
    scaleReduceShift  = scaleRestoreShift >> 1;

    offset.vx = (u32)Q12_MULT_PRECISE(moveAmt >> scaleReduceShift, Math_Sin(headingAngle) >> scaleReduceShift) << scaleRestoreShift;
    offset.vz = (u32)Q12_MULT_PRECISE(moveAmt >> scaleReduceShift, Math_Cos(headingAngle) >> scaleReduceShift) << scaleRestoreShift;
    offset.vy = Q12_MULT_PRECISE(chara->fallSpeed_34, g_DeltaTime0);

    func_80069B24(&sharedData_800E39BC_0_s00, &offset, chara);

    chara->position_18.vx += offset.vx;
    chara->position_18.vy += sharedData_800E39BC_0_s00.offset_0.vy;
    chara->position_18.vz += offset.vz;

    if (chara->position_18.vy > sharedData_800E39BC_0_s00.field_C)
    {
        chara->position_18.vy = sharedData_800E39BC_0_s00.field_C;
        chara->fallSpeed_34   = Q12(0.0f);
    }

    coord->coord.t[0] = Q12_TO_Q8(chara->position_18.vx);
    coord->coord.t[1] = Q12_TO_Q8(chara->position_18.vy);
    coord->coord.t[2] = Q12_TO_Q8(chara->position_18.vz);
}

void Ai_Cheryl_AnimStateUpdate(s_SubCharacter* chara, GsCOORDINATE2* coords) // 0x800D8310
{
    s_Collision coll;
    e_SfxId     sfx;
    s8          pitch0;
    s8          pitch1;
    s32         distSqr;

    D_800E3A30 = 0;

    #define dahliaProps (chara->properties_E4.dahlia)

    switch (dahliaProps.stateIdx0)
    {
        case 0:
            if (dahliaProps.moveDistance_126 != Q12(0.0f))
            {
                dahliaProps.moveDistance_126 -= TIMESTEP_SCALE_30_FPS(g_DeltaTime0, Q12(0.4f)) * 2;
                if (dahliaProps.moveDistance_126 < Q12(0.0f))
                {
                    dahliaProps.moveDistance_126 = Q12(0.0f);
                }
            }

            Model_AnimStatusSet(&chara->model_0, CherylAnim_1, false);
            Character_AnimStateReset(chara);

            dahliaProps.field_124 = Q12_ANGLE(0.0f);
            break;

        case 1:
            dahliaProps.moveDistance_126 = dahliaProps.field_124;

            Model_AnimStatusSet(&chara->model_0, CherylAnim_2, false);
            Character_AnimStateReset(chara);
            break;

        case 2:
            dahliaProps.moveDistance_126 = dahliaProps.field_124;

            Model_AnimStatusSet(&chara->model_0, CherylAnim_3, false);
            Character_AnimStateReset(chara);
            break;

        case 3:
            if (dahliaProps.moveDistance_126 != Q12(0.0f))
            {
                dahliaProps.moveDistance_126 -= TIMESTEP_SCALE_30_FPS(g_DeltaTime0, Q12(0.4f)) * 2;
                if (dahliaProps.moveDistance_126 < Q12(0.0f))
                {
                    dahliaProps.moveDistance_126 = Q12(0.0f);
                }
            }

            D_800E3A30 = g_DeltaTime0 * 7;

            Model_AnimStatusSet(&chara->model_0, CherylAnim_2, false);
            Character_AnimStateReset(chara);

            g_SysWork.playerWork_4C.player_0.properties_E4.player.headingAngle_124 = Q12_ANGLE(0.0f);
            dahliaProps.field_124                                        = Q12_ANGLE(0.0f);
            break;

        case 4:
            if (dahliaProps.moveDistance_126 != Q12(0.0f))
            {
                dahliaProps.moveDistance_126 -= TIMESTEP_SCALE_30_FPS(g_DeltaTime0, Q12(0.4f)) * 2;
                if (dahliaProps.moveDistance_126 < Q12(0.0f))
                {
                    dahliaProps.moveDistance_126 = Q12(0.0f);
                }
            }

            D_800E3A30 = g_DeltaTime0 * -7;

            Model_AnimStatusSet(&chara->model_0, CherylAnim_2, false);
            Character_AnimStateReset(chara);

            g_SysWork.playerWork_4C.player_0.properties_E4.player.headingAngle_124 = Q12_ANGLE(0.0f);
            dahliaProps.field_124                                        = Q12_ANGLE(0.0f);
            break;
    }

    Collision_Get(&coll, chara->position_18.vx, chara->position_18.vz);
    func_8007FDE0(coll.field_8, &sfx, &pitch0, &pitch1);

    distSqr = SQUARE(Q12_TO_Q8(chara->position_18.vx - g_SysWork.playerWork_4C.player_0.position_18.vx)) +
              SQUARE(Q12_TO_Q8(chara->position_18.vz - g_SysWork.playerWork_4C.player_0.position_18.vz));

    if (g_Player_DisableControl)
    {
        switch (dahliaProps.stateIdx0)
        {
            case 1:
                sharedFunc_800D908C_0_s00(ANIM_STATUS(CherylAnim_2, true), chara, 16, 28, Sfx_Unk1353, pitch0);
                break;

            case 2:
                sharedFunc_800D908C_0_s00(ANIM_STATUS(CherylAnim_3, true), chara, 53, 42, Sfx_Unk1353, pitch1);
                break;
        }
    }
    else
    {
        switch (dahliaProps.stateIdx0)
        {
            case 1:
                Ai_Cheryl_FootstepTrigger(ANIM_STATUS(CherylAnim_2, true), chara, 16, 28, distSqr, pitch0);
                break;

            case 2:
                Ai_Cheryl_FootstepTrigger(ANIM_STATUS(CherylAnim_3, true), chara, 53, 42, distSqr, pitch1);
                break;
        }
    }

    chara->rotation_24.vy  = Q12_ANGLE_ABS(chara->rotation_24.vy + Q8_TO_Q4(D_800E3A30));
    chara->headingAngle_3C = chara->rotation_24.vy;
    chara->moveSpeed_38    = dahliaProps.field_124;
    chara->fallSpeed_34   += g_DeltaTime2;

    coords->flg = false;
    Math_RotMatrixZxyNegGte(&chara->rotation_24, &coords->coord);
}

bool Ai_Cheryl_FootstepTrigger(s32 animStatus, s_SubCharacter* chara, s32 keyframeIdx0, s32 keyframeIdx1, s32 distSqr, s32 pitch) // 0x800D8748
{
    u32 var_a0;
    u32 vol;

    if (chara->model_0.anim_4.status_0 == animStatus)
    {
        if (distSqr >= 4000000)
        {
            if (distSqr <= 12000000)
            {
                var_a0 = distSqr;
            }
            else
            {
                var_a0 = 12000000;
            }
        }
        else
        {
            var_a0 = 4000000;
        }

        vol = (12000000 - var_a0) >> 16;
        if (chara->model_0.anim_4.keyframeIdx_8 >= keyframeIdx1)
        {
            if (!(chara->properties_E4.player.flags_11C & PlayerFlag_Unk4))
            {
                func_8005DD44(Sfx_Unk1353, &chara->position_18, vol & 0xFF, pitch);
                chara->properties_E4.player.flags_11C |= PlayerFlag_Unk4;
                return true;
            }
        }
        else
        {
            chara->properties_E4.player.flags_11C &= ~PlayerFlag_Unk4;
        }

        if (chara->model_0.anim_4.keyframeIdx_8 >= keyframeIdx0)
        {
            if (!(chara->properties_E4.player.flags_11C & PlayerFlag_Unk5))
            {
                func_8005DD44(Sfx_Unk1353, &chara->position_18, vol & 0xFF, pitch);
                chara->properties_E4.player.flags_11C |= PlayerFlag_Unk5;
                return true;
            }
        }
        else
        {
            chara->properties_E4.player.flags_11C &= ~PlayerFlag_Unk5;
        }
    }

    return false;
}

void Ai_Cheryl_Init(s_SubCharacter* chara) // 0x800D8888
{
    sharedFunc_800D923C_0_s00(chara);
    D_800E3A30 = Q12(0.0f);
}
