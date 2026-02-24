#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "bodyprog/player_logic.h"
#include "main/rng.h"
#include "maps/map7/map7_s03.h"

// TODO: Move to src/maps/characters/ once matched.

void Ai_Incubator_Update(s_SubCharacter* incubator, s_AnmHeader* anmHdr, GsCOORDINATE2* coords) // 0x800D3BC4
{
    if (incubator->model_0.charaId_0 != Chara_Incubator)
    {
        Ai_Incubator_Init(incubator);
    }

    func_800D3E18(incubator, coords);
    func_800D3C80(incubator, coords);
    Ai_Incubator_AnimUpdate(incubator, anmHdr, coords);
}

void Ai_Incubator_AnimUpdate(s_SubCharacter* incubator, s_AnmHeader* anmHdr, GsCOORDINATE2* coords) // 0x800D3C38
{
    s_AnimInfo* animInfo;

    // TODO: Wrong properties union.
    if (incubator->properties_E4.player.field_F0 == 0)
    {
        animInfo = &INCUBATOR_ANIM_INFOS[incubator->model_0.anim_4.status_0];
        animInfo->updateFunc_0(&incubator->model_0, anmHdr, coords, animInfo);
    }
}

void func_800D3C80(s_SubCharacter* incubator, GsCOORDINATE2* coords)
{
    VECTOR3 unused;
    VECTOR3 offset;
    q19_12  moveSpeed;
    q3_12   headingAngle;
    q19_12  moveAmt;
    s32     scaleRestoreShift;
    u32     scaleReduceShift;

    unused       = incubator->position_18;
    moveSpeed    = incubator->moveSpeed_38;
    headingAngle = incubator->headingAngle_3C;
    moveAmt      = Q12_MULT_PRECISE(moveSpeed, g_DeltaTime);

    scaleRestoreShift = OVERFLOW_GUARD(moveAmt);
    scaleReduceShift  = scaleRestoreShift >> 1;

    offset.vx = (u32)Q12_MULT_PRECISE(moveAmt >> scaleReduceShift, Math_Sin(headingAngle) >> scaleReduceShift) << scaleRestoreShift;
    offset.vz = (u32)Q12_MULT_PRECISE(moveAmt >> scaleReduceShift, Math_Cos(headingAngle) >> scaleReduceShift) << scaleRestoreShift;
    offset.vy = Q12_MULT_PRECISE(incubator->fallSpeed_34, g_DeltaTime);

    incubator->position_18.vx += offset.vx;
    incubator->position_18.vy  = Q12(0.0f);
    incubator->position_18.vz += offset.vz;

    coords->coord.t[0] = Q12_TO_Q8(incubator->position_18.vx);
    coords->coord.t[1] = Q12_TO_Q8(incubator->position_18.vy);
    coords->coord.t[2] = Q12_TO_Q8(incubator->position_18.vz);
}

void func_800D3E18(s_SubCharacter* incubator, GsCOORDINATE2* coords) // 0x800D3E18
{
    switch (incubator->properties_E4.dahlia.stateIdx0)
    {
        case 0:
            break;

        case 1:
            Model_AnimStatusSet(&incubator->model_0, 2, false);

            if (incubator->properties_E4.dahlia.resetStateIdx0_F8 != 0)
            {
                incubator->properties_E4.dahlia.stateIdx0 = 0;
                incubator->model_0.stateStep_3 = 0;
                incubator->properties_E4.dahlia.resetStateIdx0_F8 = 0;
            }
            break;

        case 2:
            Model_AnimStatusKeyframeSet(incubator->model_0, 3, true, INCUBATOR_ANIM_INFOS, 0);

            if (incubator->properties_E4.dahlia.resetStateIdx0_F8)
            {
                incubator->properties_E4.dahlia.stateIdx0 = 0;
                incubator->model_0.stateStep_3 = 0;
                incubator->properties_E4.dahlia.resetStateIdx0_F8 = 0;
            }
            break;

        case 3:
            Model_AnimStatusSet(&incubator->model_0, 1, false);

            if (incubator->properties_E4.dahlia.resetStateIdx0_F8)
            {
                incubator->properties_E4.dahlia.stateIdx0 = 0;
                incubator->model_0.stateStep_3 = 0;
                incubator->properties_E4.dahlia.resetStateIdx0_F8 = 0;
            }
            break;
    }

    incubator->headingAngle_3C = incubator->rotation_24.vy;
    incubator->moveSpeed_38 = incubator->properties_E4.splitHead.moveDistance_126;
    incubator->fallSpeed_34   += g_GravitySpeed;

    coords->flg = false;
    Math_RotMatrixZxyNegGte(&incubator->rotation_24, &coords->coord);
}

void Ai_Incubator_Init(s_SubCharacter* incubator) // 0x800D3F38
{
    sharedFunc_800D923C_0_s00(incubator);
}
