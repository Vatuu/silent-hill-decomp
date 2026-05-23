#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "maps/characters/bloody_incubator.h"

#define bloodyIncubatorProps bloodyIncubator->properties.npc

void BloodyIncubator_Update(s_SubCharacter* bloodyIncubator, s_AnmHeader* anmHdr, GsCOORDINATE2* boneCoords) // 0x800D3684
{
    if (bloodyIncubator->model.charaId != Chara_BloodyIncubator)
    {
        BloodyIncubator_Init(bloodyIncubator);
    }

    func_800D38D8(bloodyIncubator, boneCoords);
    func_800D3740(bloodyIncubator, boneCoords);
    BloodyIncubator_AnimUpdate(bloodyIncubator, anmHdr, boneCoords);
}

void BloodyIncubator_AnimUpdate(s_SubCharacter* bloodyIncubator, s_AnmHeader* anmHdr, GsCOORDINATE2* boneCoords) // 0x800D36F8
{
    Chara_AnimUpdate(bloodyIncubator, anmHdr, boneCoords, BLOODY_INCUBATOR_ANIM_INFOS);
}

void func_800D3740(s_SubCharacter* bloodyIncubator, GsCOORDINATE2* boneCoords) // 0x800D3740
{
    VECTOR3 unused;
    VECTOR3 offset;
    q19_12  moveSpeed;
    q3_12   headingAngle;
    q19_12  moveDist;
    s32     scaleRestoreShift;
    u32     scaleReduceShift;

    unused       = bloodyIncubator->position;
    moveSpeed    = bloodyIncubator->moveSpeed;
    headingAngle = bloodyIncubator->headingAngle;
    moveDist     = Q12_MULT_PRECISE(moveSpeed, g_DeltaTime);

    scaleRestoreShift = OVERFLOW_GUARD(moveDist);
    scaleReduceShift  = scaleRestoreShift >> 1;

    offset.vx = (u32)Q12_MULT_PRECISE(moveDist >> scaleReduceShift, Math_Sin(headingAngle) >> scaleReduceShift) << scaleRestoreShift;
    offset.vz = (u32)Q12_MULT_PRECISE(moveDist >> scaleReduceShift, Math_Cos(headingAngle) >> scaleReduceShift) << scaleRestoreShift;
    offset.vy = Q12_MULT_PRECISE(bloodyIncubator->fallSpeed, g_DeltaTime);

    bloodyIncubator->position.vx += offset.vx;
    bloodyIncubator->position.vy  = Q12(0.0f);
    bloodyIncubator->position.vz += offset.vz;

    boneCoords[0].coord.t[0] = Q12_TO_Q8(bloodyIncubator->position.vx);
    boneCoords[0].coord.t[1] = Q12_TO_Q8(bloodyIncubator->position.vy);
    boneCoords[0].coord.t[2] = Q12_TO_Q8(bloodyIncubator->position.vz);
}

void func_800D38D8(s_SubCharacter* bloodyIncubator, GsCOORDINATE2* boneCoords) // 0x800D38D8
{
    switch (bloodyIncubatorProps.controlState)
    {
        case 0:
            break;

        case 1:
            Model_AnimStatusKeyframeSet(bloodyIncubator->model, 9, true, BLOODY_INCUBATOR_ANIM_INFOS, 0);
            Chara_AnimStateReset(bloodyIncubator);
            break;

        case 2:
            Model_AnimStatusKeyframeSet(bloodyIncubator->model, 1, true, BLOODY_INCUBATOR_ANIM_INFOS, 0);
            Chara_AnimStateReset(bloodyIncubator);
            break;

        case 3:
            Model_AnimStatusKeyframeSet(bloodyIncubator->model, 2, true, BLOODY_INCUBATOR_ANIM_INFOS, 0);
            Chara_AnimStateReset(bloodyIncubator);
            break;

        case 4:
            Model_AnimStatusKeyframeSet(bloodyIncubator->model, 3, true, BLOODY_INCUBATOR_ANIM_INFOS, 0);
            Chara_AnimStateReset(bloodyIncubator);
            break;

        case 5:
            Model_AnimStatusSet(&bloodyIncubator->model, 10, false);
            Chara_AnimStateReset(bloodyIncubator);
            break;

        case 6:
            Model_AnimStatusSet(&bloodyIncubator->model, 4, false);
            Chara_AnimStateReset(bloodyIncubator);
            break;

        case 7:
            Model_AnimStatusSet(&bloodyIncubator->model, 5, false);
            Chara_AnimStateReset(bloodyIncubator);
            break;

        case 8:
            Model_AnimStatusKeyframeSet(bloodyIncubator->model, 6, true, BLOODY_INCUBATOR_ANIM_INFOS, 0);
            Chara_AnimStateReset(bloodyIncubator);
            break;

        case 9:
            Model_AnimStatusSet(&bloodyIncubator->model, 7, false);
            Chara_AnimStateReset(bloodyIncubator);
            break;

        case 10:
            Model_AnimStatusSet(&bloodyIncubator->model, 8, false);
            Chara_AnimStateReset(bloodyIncubator);
            break;

        case 11:
            Model_AnimStatusKeyframeSet(bloodyIncubator->model, 11, true, BLOODY_INCUBATOR_ANIM_INFOS, 0);
            Chara_AnimStateReset(bloodyIncubator);
            break;

    }

    bloodyIncubator->headingAngle = bloodyIncubator->rotation.vy;
    bloodyIncubator->moveSpeed    = bloodyIncubatorProps.moveSpeed;
    bloodyIncubator->fallSpeed   += g_GravitySpeed;
    boneCoords->flg               = false;

    Math_RotMatrixZxyNegGte(&bloodyIncubator->rotation, &boneCoords->coord);
}

void BloodyIncubator_Init(s_SubCharacter* bloodyIncubator) // 0x800D3BA4
{
    Chara_CollisionReset(bloodyIncubator);
}
