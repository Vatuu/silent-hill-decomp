#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "bodyprog/player_logic.h"
#include "maps/shared.h"
#include "maps/map0/map0_s00.h" // TODO: Needed for `D_800E39BC`, which should probably be sharedData.
#include "maps/characters/chara_cheryl.h"

// AI code for `Chara_GhostChildAlessa`
//
// Included in:
//  MAP0_S00

void Ai_Cheryl_Update(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* coords) // 0x800D7FB8
{
    if (chara->model_0.charaId_0 != Chara_Cheryl)
    {
        Ai_Cheryl_Init(chara);
    }

    func_800D8310(chara, coords);         // Control.
    func_800D8124(chara, coords);         // Translate + rotate.
    func_800D802C(chara, anmHdr, coords); // Modulate speed and something else?
}

void func_800D802C(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* coord) // 0x800D802C
{
    q19_12      moveSpeed;
    q19_12      animDur;
    s_AnimInfo* animInfo;

#define CHARA_PROPERTIES (chara->properties_E4.dahlia)

    if (CHARA_PROPERTIES.stateIdx0 == 1)
    {
        D_800DF1CC = FP_MULTIPLY_PRECISE(chara->moveSpeed_38, Q12(30.2f), Q12_SHIFT);
    }

    moveSpeed           = MIN(chara->moveSpeed_38, Q12(2.5f));
    chara->moveSpeed_38 = moveSpeed;

    if (CHARA_PROPERTIES.stateIdx0 == 2)
    {
        // TODO: KAUFMAN anim in map0_s00? This might be a different anim table after all.
        animInfo = KAUFMANN_ANIM_INFOS;
        if (moveSpeed <= Q12(1.5f))
        {
            animDur = FP_MULTIPLY_PRECISE(moveSpeed, Q12(18.6f), Q12_SHIFT);
        }
        else
        {
            animDur = Q12(27.9f) - 1;
        }

        animInfo[7].duration_8.constant = animDur;
    }

    if (CHARA_PROPERTIES.properties_F0.val32 == 0)
    {
        KAUFMANN_ANIM_INFOS[chara->model_0.anim_4.status_0].updateFunc_0(&chara->model_0, anmHdr, coord, &KAUFMANN_ANIM_INFOS[chara->model_0.anim_4.status_0]);
    }
}

void func_800D8124(s_SubCharacter* chara, GsCOORDINATE2* coord) // 0x800D8124
{
    VECTOR3 pos;               // @hack Unused but required.
    VECTOR3 offset;
    s32     moveSpeed;
    s16     headingAngle;
    s32     moveAmt;
    s32     scaleRestoreShift;
    u32     scaleReduceShift;

    pos          = chara->position_18;
    moveSpeed    = chara->moveSpeed_38;
    headingAngle = chara->headingAngle_3C;
    moveAmt      = FP_MULTIPLY_PRECISE(moveSpeed, g_DeltaTime0, Q12_SHIFT);

    scaleRestoreShift = OVERFLOW_GUARD(moveAmt);
    scaleReduceShift  = scaleRestoreShift >> 1;

    offset.vx = (u32)FP_MULTIPLY_PRECISE(moveAmt >> scaleReduceShift, Math_Sin(headingAngle) >> scaleReduceShift, Q12_SHIFT) << scaleRestoreShift;
    offset.vz = (u32)FP_MULTIPLY_PRECISE(moveAmt >> scaleReduceShift, Math_Cos(headingAngle) >> scaleReduceShift, Q12_SHIFT) << scaleRestoreShift;
    offset.vy = FP_MULTIPLY_PRECISE(chara->field_34, g_DeltaTime0, Q12_SHIFT);

    func_80069B24(&D_800E39BC, &offset, chara);

    chara->position_18.vx += offset.vx;
    chara->position_18.vy += D_800E39BC.offset_0.vy;
    chara->position_18.vz += offset.vz;

    if (chara->position_18.vy > D_800E39BC.field_C)
    {
        chara->position_18.vy = D_800E39BC.field_C;
        chara->field_34       = 0;
    }

    coord->coord.t[0] = Q12_TO_Q8(chara->position_18.vx);
    coord->coord.t[1] = Q12_TO_Q8(chara->position_18.vy);
    coord->coord.t[2] = Q12_TO_Q8(chara->position_18.vz);
}

void func_800D8310(s_SubCharacter* chara, GsCOORDINATE2* coords) // 0x800D8310
{
    s_Collision coll;
    s32         unused;
    s8          pitch0;
    s8          pitch1;
    s32         distSqr;

    D_800E3A30 = 0;

#define CHARA_PROPERTIES (chara->properties_E4.dahlia)

    switch (CHARA_PROPERTIES.stateIdx0)
    {
        case 0:
            if (CHARA_PROPERTIES.moveDistance_126 != Q12(0.0f))
            {
                CHARA_PROPERTIES.moveDistance_126 -= TIME_STEP_SCALE(g_DeltaTime0, Q12(0.4f)) * 2;
                if (CHARA_PROPERTIES.moveDistance_126 < Q12(0.0f))
                {
                    CHARA_PROPERTIES.moveDistance_126 = Q12(0.0f);
                }
            }

            Model_AnimStatusSet(&chara->model_0, 1, false);
            Character_AnimStateTryReset(chara);

            CHARA_PROPERTIES.field_124 = FP_ANGLE(0.0f);
            break;

        case 1:
            CHARA_PROPERTIES.moveDistance_126 = CHARA_PROPERTIES.field_124;

            Model_AnimStatusSet(&chara->model_0, 2, false);
            Character_AnimStateTryReset(chara);
            break;

        case 2:
            CHARA_PROPERTIES.moveDistance_126 = CHARA_PROPERTIES.field_124;

            Model_AnimStatusSet(&chara->model_0, 3, false);
            Character_AnimStateTryReset(chara);
            break;

        case 3:
            if (CHARA_PROPERTIES.moveDistance_126 != Q12(0.0f))
            {
                CHARA_PROPERTIES.moveDistance_126 -= TIME_STEP_SCALE(g_DeltaTime0, Q12(0.4f)) * 2;
                if (CHARA_PROPERTIES.moveDistance_126 < Q12(0.0f))
                {
                    CHARA_PROPERTIES.moveDistance_126 = Q12(0.0f);
                }
            }

            D_800E3A30 = g_DeltaTime0 * 7;

            Model_AnimStatusSet(&chara->model_0, 2, false);
            Character_AnimStateTryReset(chara);

            g_SysWork.player_4C.chara_0.properties_E4.player.headingAngle_124 = FP_ANGLE(0.0f);
            CHARA_PROPERTIES.field_124                                        = FP_ANGLE(0.0f);
            break;

        case 4:
            if (CHARA_PROPERTIES.moveDistance_126 != Q12(0.0f))
            {
                CHARA_PROPERTIES.moveDistance_126 -= TIME_STEP_SCALE(g_DeltaTime0, Q12(0.4f)) * 2;
                if (CHARA_PROPERTIES.moveDistance_126 < Q12(0.0f))
                {
                    CHARA_PROPERTIES.moveDistance_126 = Q12(0.0f);
                }
            }

            D_800E3A30 = g_DeltaTime0 * -7;

            Model_AnimStatusSet(&chara->model_0, 2, false);
            Character_AnimStateTryReset(chara);

            g_SysWork.player_4C.chara_0.properties_E4.player.headingAngle_124 = FP_ANGLE(0.0f);
            CHARA_PROPERTIES.field_124                                        = FP_ANGLE(0.0f);
            break;
    }

    Collision_Get(&coll, chara->position_18.vx, chara->position_18.vz);
    func_8007FDE0(coll.field_8, &unused, &pitch0, &pitch1);

    distSqr = SQUARE(Q12_TO_Q8(chara->position_18.vx - g_SysWork.player_4C.chara_0.position_18.vx)) +
              SQUARE(Q12_TO_Q8(chara->position_18.vz - g_SysWork.player_4C.chara_0.position_18.vz));

    if (g_Player_DisableControl)
    {
        switch (CHARA_PROPERTIES.stateIdx0)
        {
            case 1:
                sharedFunc_800D908C_0_s00(ANIM_STATUS(2, true), chara, 16, 28, Sfx_Unk1353, pitch0);
                break;

            case 2:
                sharedFunc_800D908C_0_s00(ANIM_STATUS(3, true), chara, 53, 42, Sfx_Unk1353, pitch1);
                break;
        }
    }
    else
    {
        switch (CHARA_PROPERTIES.stateIdx0)
        {
            case 1:
                func_800D8748(ANIM_STATUS(2, true), chara, 16, 28, distSqr, pitch0);
                break;

            case 2:
                func_800D8748(ANIM_STATUS(3, true), chara, 53, 42, distSqr, pitch1);
                break;
        }
    }

    chara->rotation_24.vy  = ABS_ANGLE(chara->rotation_24.vy + Q8_TO_Q4(D_800E3A30));
    chara->headingAngle_3C = chara->rotation_24.vy;
    chara->moveSpeed_38    = CHARA_PROPERTIES.field_124;
    chara->field_34       += g_DeltaTime2;

    coords->flg = false;
    Math_MatrixRotate1(&chara->rotation_24, &coords->coord);
}

bool func_800D8748(s32 animStatus, s_SubCharacter* chara, s32 keyframeIdx0, s32 keyframeIdx1, s32 arg4, s32 pitch) // 0x800D8748
{
    u32 var_a0;
    u32 vol;

    if (chara->model_0.anim_4.status_0 == animStatus)
    {
        if (arg4 >= 4000000)
        {
            if (arg4 <= 12000000)
            {
                var_a0 = arg4;
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
