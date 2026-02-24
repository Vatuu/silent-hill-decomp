#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "bodyprog/player_logic.h"
#include "main/rng.h"
#include "maps/map7/map7_s03.h"

// TODO: Move to src/maps/characters/ once matched.

void Ai_BloodyIncubator_Update(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* coords) // 0x800D3684
{
    if (chara->model_0.charaId_0 != Chara_BloodyIncubator)
    {
        Ai_BloodyIncubator_Init(chara);
    }

    func_800D38D8(chara, coords);
    func_800D3740(chara, coords);
    Ai_BloodyIncubator_AnimUpdate(chara, anmHdr, coords);
}

void Ai_BloodyIncubator_AnimUpdate(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* coords) // 0x800D36F8
{
    s_AnimInfo* animInfo;

    // TODO: Wrong properties union.
    if (chara->properties_E4.player.field_F0 == 0)
    {
        animInfo = &BLOODY_INCUBATOR_ANIM_INFOS[chara->model_0.anim_4.status_0];
        animInfo->updateFunc_0(&chara->model_0, anmHdr, coords, animInfo);
    }
}

void func_800D3740(s_SubCharacter* chara, GsCOORDINATE2* coords) // 0x800D3740
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
    moveAmt      = Q12_MULT_PRECISE(moveSpeed, g_DeltaTime);

    scaleRestoreShift = OVERFLOW_GUARD(moveAmt);
    scaleReduceShift  = scaleRestoreShift >> 1;

    offset.vx = (u32)Q12_MULT_PRECISE(moveAmt >> scaleReduceShift, Math_Sin(headingAngle) >> scaleReduceShift) << scaleRestoreShift;
    offset.vz = (u32)Q12_MULT_PRECISE(moveAmt >> scaleReduceShift, Math_Cos(headingAngle) >> scaleReduceShift) << scaleRestoreShift;
    offset.vy = Q12_MULT_PRECISE(chara->fallSpeed_34, g_DeltaTime);

    chara->position_18.vx += offset.vx;
    chara->position_18.vy  = Q12(0.0f);
    chara->position_18.vz += offset.vz;

    coords->coord.t[0] = Q12_TO_Q8(chara->position_18.vx);
    coords->coord.t[1] = Q12_TO_Q8(chara->position_18.vy);
    coords->coord.t[2] = Q12_TO_Q8(chara->position_18.vz);
}

void func_800D38D8(s_SubCharacter* bloodyIncubator, GsCOORDINATE2* coords) // 0x800D38D8
{
    switch (bloodyIncubator->properties_E4.player.afkTimer_E8)
    {
        case 0:
            break;

        case 1:
            Model_AnimStatusKeyframeSet(bloodyIncubator->model_0, 9, true, BLOODY_INCUBATOR_ANIM_INFOS, 0);
            Character_AnimStateReset(bloodyIncubator);
            break;

        case 2:
            Model_AnimStatusKeyframeSet(bloodyIncubator->model_0, 1, true, BLOODY_INCUBATOR_ANIM_INFOS, 0);
            Character_AnimStateReset(bloodyIncubator);
            break;

        case 3:
            Model_AnimStatusKeyframeSet(bloodyIncubator->model_0, 2, true, BLOODY_INCUBATOR_ANIM_INFOS, 0);
            Character_AnimStateReset(bloodyIncubator);
            break;

        case 4:
            Model_AnimStatusKeyframeSet(bloodyIncubator->model_0, 3, true, BLOODY_INCUBATOR_ANIM_INFOS, 0);
            Character_AnimStateReset(bloodyIncubator);
            break;

        case 5:
            Model_AnimStatusSet(&bloodyIncubator->model_0, 10, false);
            Character_AnimStateReset(bloodyIncubator);
            break;

        case 6:
            Model_AnimStatusSet(&bloodyIncubator->model_0, 4, false);
            Character_AnimStateReset(bloodyIncubator);
            break;

        case 7:
            Model_AnimStatusSet(&bloodyIncubator->model_0, 5, false);
            Character_AnimStateReset(bloodyIncubator);
            break;

        case 8:
            Model_AnimStatusKeyframeSet(bloodyIncubator->model_0, 6, true, BLOODY_INCUBATOR_ANIM_INFOS, 0);
            Character_AnimStateReset(bloodyIncubator);
            break;

        case 9:
            Model_AnimStatusSet(&bloodyIncubator->model_0, 7, false);
            Character_AnimStateReset(bloodyIncubator);
            break;

        case 10:
            Model_AnimStatusSet(&bloodyIncubator->model_0, 8, false);
            Character_AnimStateReset(bloodyIncubator);
            break;

        case 11:
            Model_AnimStatusKeyframeSet(bloodyIncubator->model_0, 11, true, BLOODY_INCUBATOR_ANIM_INFOS, 0);
            Character_AnimStateReset(bloodyIncubator);
            break;

    }

    bloodyIncubator->headingAngle_3C = bloodyIncubator->rotation_24.vy;
    bloodyIncubator->moveSpeed_38    = bloodyIncubator->properties_E4.dahlia.moveDistance_126;
    bloodyIncubator->fallSpeed_34   += g_GravitySpeed;
    coords->flg                      = false;

    Math_RotMatrixZxyNegGte(&bloodyIncubator->rotation_24, &coords->coord);
}

void Ai_BloodyIncubator_Init(s_SubCharacter* chara) // 0x800D3BA4
{
    sharedFunc_800D923C_0_s00(chara);
}
