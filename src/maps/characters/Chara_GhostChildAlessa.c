#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "maps/shared.h"
#include "maps/characters/Chara_GhostChildAlessa.h"

/** AI code for `Chara_GhostChildAlessa`
 *
 * Included in:
 *  MAP7_S01
 *  MAP7_S02
 */

/** Addresses
 * MAP7_S01: 0x800D49B8
 * MAP7_S02: 0x800D7A68
 */
void Ai_GhostChildAlessa_Update(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* coords)
{
    if (chara->model_0.charaId_0 != Chara_GhostChildAlessa)
    {
        Ai_GhostChildAlessa_Init(chara);
    }

    sharedFunc_800D4C0C_7_s01(chara, coords);
    sharedFunc_800D4A74_7_s01(chara, coords);
    sharedFunc_800D4A2C_7_s01(chara, anmHdr, coords);
}

/** Addresses
 * MAP7_S01: 0x800D4A2C
 * MAP7_S02: 0x800D7ADC
 */
void sharedFunc_800D4A2C_7_s01(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* coords)
{
    s_AnimInfo* animInfo;

    if (chara->properties_E4.player.field_F0 != 0)
    {
        return;
    }

    animInfo = &GHOST_CHILD_ALESSA_ANIM_INFOS[chara->model_0.anim_4.status_0];
    animInfo->updateFunc_0(&chara->model_0, anmHdr, coords, animInfo);
}

/** Addresses
 * MAP7_S01: 0x800D4A74
 * MAP7_S02: 0x800D7B24
 */
void sharedFunc_800D4A74_7_s01(s_SubCharacter* chara, GsCOORDINATE2* coord)
{
    VECTOR3 unused;
    VECTOR3 vec;
    s32     moveSpeed;
    s16     headingAngle;
    s32     moveAmt;
    s32     scaleRestoreShift;
    u32     scaleReduceShift;

    unused       = chara->position_18;
    moveSpeed    = chara->moveSpeed_38;
    headingAngle = chara->headingAngle_3C;
    moveAmt      = FP_MULTIPLY_PRECISE(moveSpeed, g_DeltaTime0, Q12_SHIFT);

    scaleRestoreShift = OVERFLOW_GUARD(moveAmt);
    scaleReduceShift  = scaleRestoreShift >> 1;

    vec.vx = (u32)FP_MULTIPLY_PRECISE(moveAmt >> scaleReduceShift, Math_Sin(headingAngle) >> scaleReduceShift, Q12_SHIFT) << scaleRestoreShift;
    vec.vz = (u32)FP_MULTIPLY_PRECISE(moveAmt >> scaleReduceShift, Math_Cos(headingAngle) >> scaleReduceShift, Q12_SHIFT) << scaleRestoreShift;
    vec.vy = FP_MULTIPLY_PRECISE(chara->field_34, g_DeltaTime0, Q12_SHIFT);

    chara->position_18.vx += vec.vx;
    chara->position_18.vy  = 0;
    chara->position_18.vz += vec.vz;

    coord->coord.t[0] = Q12_TO_Q8(chara->position_18.vx);
    coord->coord.t[1] = Q12_TO_Q8(chara->position_18.vy);
    coord->coord.t[2] = Q12_TO_Q8(chara->position_18.vz);
}

/** Addresses
 * MAP7_S01: 0x800D4C0C
 * MAP7_S02: 0x800D7CBC
 */
void sharedFunc_800D4C0C_7_s01(s_SubCharacter* chara, GsCOORDINATE2* coords)
{
#define CHARA_PROPERTIES (chara->properties_E4.dahlia)

    switch (CHARA_PROPERTIES.stateIdx0)
    {
        case 0:
            break;

        case 1:
            CHARA_PROPERTIES.moveDistance_126 = CHARA_PROPERTIES.field_124;
            Model_AnimStatusSet(&chara->model_0, 1, false);
            Character_AnimStateTryReset(chara);
            break;

        case 2:
            CHARA_PROPERTIES.moveDistance_126 = CHARA_PROPERTIES.field_124;
            Model_AnimStatusSet(&chara->model_0, 2, false);
            Character_AnimStateTryReset(chara);
            break;

        case 6:
            Model_AnimStatusSet(&chara->model_0, 3, false);
            if (chara->model_0.anim_4.keyframeIdx_8 == 63)
            {
                CHARA_PROPERTIES.stateIdx0 = 7;
                chara->model_0.stateStep_3 = 0;
            }
            break;

        case 7:
            Model_AnimStatusSet(&chara->model_0, 4, false);
            Character_AnimStateTryReset(chara);
            break;

        case 8:
            Model_AnimStatusSet(&chara->model_0, 5, false);
            Character_AnimStateTryReset(chara);
            break;

        case 9:
            Model_AnimStatusSet(&chara->model_0, 6, false);
            Character_AnimStateTryReset(chara);
            break;

        case 10:
            Model_AnimStatusSet(&chara->model_0, 7, false);
            Character_AnimStateTryReset(chara);
            break;

        case 11:
            Model_AnimStatusSet(&chara->model_0, 8, false);
            Character_AnimStateTryReset(chara);
            break;
    }

    chara->rotation_24.vy  = ABS_ANGLE(chara->rotation_24.vy + Q8_TO_Q4(sharedData_800E39D8_0_s00));
    chara->headingAngle_3C = chara->rotation_24.vy;
    chara->moveSpeed_38    = CHARA_PROPERTIES.moveDistance_126;
    chara->field_34       += g_DeltaTime2;

    coords->flg = 0;
    Math_MatrixRotate1(&chara->rotation_24, &coords->coord);
}

/** Addresses
 * MAP7_S01: 0x800D4DD8
 * MAP7_S02: 0x800D7E88
 */
void Ai_GhostChildAlessa_Init(s_SubCharacter* chara)
{
    sharedFunc_800D923C_0_s00(chara);
    sharedData_800E39D8_0_s00 = 0;
}
