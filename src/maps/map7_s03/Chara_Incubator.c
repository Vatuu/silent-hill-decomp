#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "bodyprog/player_logic.h"
#include "main/rng.h"
#include "maps/shared.h"
#include "maps/map7/map7_s03.h"

// TODO: Move to src/maps/characters/ once matched.

void Ai_Incubator_Update(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* coords) // 0x800D3BC4
{
    if (chara->model_0.charaId_0 != Chara_Incubator)
    {
        Ai_Incubator_Init(chara);
    }

    func_800D3E18(chara, coords);
    func_800D3C80(chara, coords);
    Ai_Incubator_AnimUpdate(chara, anmHdr, coords);
}

void Ai_Incubator_AnimUpdate(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* coords) // 0x800D3C38
{
    s_AnimInfo* animInfo;

    // TODO: Wrong properties union.
    if (chara->properties_E4.player.field_F0 == 0)
    {
        animInfo = &INCUBATOR_ANIM_INFOS[chara->model_0.anim_4.status_0];
        animInfo->updateFunc_0(&chara->model_0, anmHdr, coords, animInfo);
    }
}

void func_800D3C80(s_SubCharacter* chara, GsCOORDINATE2* coord)
{
    VECTOR3 unused;
    VECTOR3 offset;
    q19_12  moveSpeed;
    q3_12   headingAngle;
    q19_12  moveAmt;
    s32     scaleRestoreShift;
    u32     scaleReduceShift;

    unused       = chara->position_18;
    moveSpeed    = chara->moveSpeed_38;
    headingAngle = chara->headingAngle_3C;
    moveAmt      = FP_MULTIPLY_PRECISE(moveSpeed, g_DeltaTime0, Q12_SHIFT);

    scaleRestoreShift = OVERFLOW_GUARD(moveAmt);
    scaleReduceShift  = scaleRestoreShift >> 1;

    offset.vx = (u32)FP_MULTIPLY_PRECISE(moveAmt >> scaleReduceShift, Math_Sin(headingAngle) >> scaleReduceShift, Q12_SHIFT) << scaleRestoreShift;
    offset.vz = (u32)FP_MULTIPLY_PRECISE(moveAmt >> scaleReduceShift, Math_Cos(headingAngle) >> scaleReduceShift, Q12_SHIFT) << scaleRestoreShift;
    offset.vy = FP_MULTIPLY_PRECISE(chara->field_34, g_DeltaTime0, Q12_SHIFT);

    chara->position_18.vx += offset.vx;
    chara->position_18.vy  = Q12(0.0f);
    chara->position_18.vz += offset.vz;

    coord->coord.t[0] = Q12_TO_Q8(chara->position_18.vx);
    coord->coord.t[1] = Q12_TO_Q8(chara->position_18.vy);
    coord->coord.t[2] = Q12_TO_Q8(chara->position_18.vz);
}

void func_800D3E18(s_SubCharacter* chara, GsCOORDINATE2* arg1)
{
    switch (chara->properties_E4.dahlia.stateIdx0)
    {
        case 0:
            break;
        case 1:
            Model_AnimStatusSet(&chara->model_0, 2, false);
            if (chara->properties_E4.dahlia.resetStateIdx0_F8 != 0)
            {
                chara->properties_E4.dahlia.stateIdx0 = 0;
                chara->model_0.stateStep_3 = 0;
                chara->properties_E4.dahlia.resetStateIdx0_F8 = 0;
            }
            break;
        case 2:
            Model_AnimStatusKeyframeSet(chara->model_0, 3, true, INCUBATOR_ANIM_INFOS, 0);
            if (chara->properties_E4.dahlia.resetStateIdx0_F8) 
            {
                chara->properties_E4.dahlia.stateIdx0 = 0;
                chara->model_0.stateStep_3 = 0;
                chara->properties_E4.dahlia.resetStateIdx0_F8 = 0;
            }
            break;
        case 3:
            Model_AnimStatusSet(&chara->model_0, 1, false);
            if (chara->properties_E4.dahlia.resetStateIdx0_F8)
            {
                chara->properties_E4.dahlia.stateIdx0 = 0;
                chara->model_0.stateStep_3 = 0;
                chara->properties_E4.dahlia.resetStateIdx0_F8 = 0;
            }
            break;
    }
    
    chara->headingAngle_3C = chara->rotation_24.vy;
    chara->moveSpeed_38 = chara->properties_E4.splitHead.moveDistance_126;
    chara->field_34 += g_DeltaTime2;
    
    arg1->flg = 0;
    Math_RotMatrixZxyNegGte(&chara->rotation_24, &arg1->coord);
}

void Ai_Incubator_Init(s_SubCharacter* chara) // 0x800D3F38
{
    sharedFunc_800D923C_0_s00(chara);
}
