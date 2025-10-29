#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "main/rng.h"
#include "maps/shared.h"
#include "maps/characters/Chara_Alessa.h"

/** AI code for `Chara_Alessa`
 *
 * Included in:
 *  MAP3_S02
 *  MAP6_S02
 *  MAP6_S04
 *  MAP7_S03
 */

/** Addresses
 * MAP3_S02: 0x800CEC88
 * MAP6_S02: 0x800CD734
 * MAP6_S04: 0x800DC2B4
 * MAP7_S03: 0x800D2F08
 */
void Ai_Alessa_Update(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* coords)
{
    if (chara->model_0.state_2 == 0)
    {
        Ai_Alessa_Init(chara);
    }

    sharedFunc_800CEEDC_3_s02(chara, coords);
    sharedFunc_800CED44_3_s02(chara, coords);
    sharedFunc_800CECFC_3_s02(chara, anmHdr, coords);
}

/** Addresses
 * MAP3_S02: 0x800CECFC
 * MAP6_S02: 0x800CD7A8
 * MAP6_S04: 0x800DC328
 * MAP7_S03: 0x800D2F7C
 */
void sharedFunc_800CECFC_3_s02(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* coord)
{
    if (chara->properties_E4.player.field_F0 == 0)
    {
        s_AnimInfo* animInfo = &ALESSA_ANIM_INFOS[chara->model_0.anim_4.status_0];
        animInfo->updateFunc_0(&chara->model_0, anmHdr, coord, animInfo);
    }
}

/** Addresses
 * MAP3_S02: 0x800CED44
 * MAP6_S02: 0x800CD7F0
 * MAP6_S04: 0x800DC370
 * MAP7_S03: 0x800D2FC4
 */
void sharedFunc_800CED44_3_s02(s_SubCharacter* chara, GsCOORDINATE2* coord)
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
    chara->position_18.vy = 0;
    chara->position_18.vz += vec.vz;

    coord->coord.t[0] = Q12_TO_Q8(chara->position_18.vx);
    coord->coord.t[1] = Q12_TO_Q8(chara->position_18.vy);
    coord->coord.t[2] = Q12_TO_Q8(chara->position_18.vz);
}

/** Addresses
 * MAP3_S02: 0x800CEEDC
 * MAP6_S02: 0x800CD988
 * MAP6_S04: 0x800DC508
 * MAP7_S03: 0x800D315C
 */
void sharedFunc_800CEEDC_3_s02(s_SubCharacter* chara, GsCOORDINATE2* coords)
{
    s_Collision coll;
    s32         sfx;
    s8          pitch0;
    s8          pitch1;

#define CHARA_PROPERTIES (chara->properties_E4.dahlia)

    switch (CHARA_PROPERTIES.stateIdx0)
    {
        case 0:
            break;

        case 2:
            if (CHARA_PROPERTIES.moveDistance_126 > Q12(1.25f))
            {
                CHARA_PROPERTIES.moveDistance_126 -= TIMESTEP_SCALE(g_DeltaTime0, Q12(0.5f));
                if (CHARA_PROPERTIES.moveDistance_126 < Q12(1.25f))
                {
                    CHARA_PROPERTIES.moveDistance_126 = Q12(1.25f);
                }
            }
            else if (CHARA_PROPERTIES.moveDistance_126 < Q12(1.25f))
            {
                CHARA_PROPERTIES.moveDistance_126 += TIMESTEP_SCALE(g_DeltaTime0, Q12(0.4f));
                CHARA_PROPERTIES.moveDistance_126  = CLAMP(CHARA_PROPERTIES.moveDistance_126, 0, Q12(1.25f));
            }

            Model_AnimStatusSet(&chara->model_0, 2, false);
            Character_AnimStateReset(chara);
            break;

        case 1:
            if (CHARA_PROPERTIES.moveDistance_126)
            {
                CHARA_PROPERTIES.moveDistance_126 -= TIMESTEP_SCALE(g_DeltaTime0, Q12(0.4f)) * 2;
                if (CHARA_PROPERTIES.moveDistance_126 < 0)
                {
                    CHARA_PROPERTIES.moveDistance_126 = 0;
                }
            }

            Model_AnimStatusKeyframeSet(chara->model_0, 1, true, ALESSA_ANIM_INFOS, 0);
            Character_AnimStateReset(chara);
            break;

        case 4:
            Model_AnimStatusSet(&chara->model_0, 4, false);
            Character_AnimStateReset(chara);
            break;

        case 3:
            Model_AnimStatusSet(&chara->model_0, 3, false);
            Character_AnimStateReset(chara);
            break;

        case 5:
            Model_AnimStatusSet(&chara->model_0, 5, false);
            Character_AnimStateReset(chara);
            break;

        case 6:
            Model_AnimStatusSet(&chara->model_0, 6, false);
            Character_AnimStateReset(chara);
            break;

        case 7:
            Model_AnimStatusSet(&chara->model_0, 7, false);
            Character_AnimStateReset(chara);
            break;

        case 8:
            Model_AnimStatusSet(&chara->model_0, 8, false);
            Character_AnimStateReset(chara);
            break;

        case 9:
            Model_AnimStatusSet(&chara->model_0, 9, false);
            Character_AnimStateReset(chara);
            break;

        case 10:
            Model_AnimStatusSet(&chara->model_0, 10, false);
            Character_AnimStateReset(chara);
            break;
    }

    Collision_Get(&coll, chara->position_18.vx, chara->position_18.vz);
    func_8007FDE0(coll.field_8, &sfx, &pitch0, &pitch1);

    switch (CHARA_PROPERTIES.stateIdx0)
    {
        case 2:
            sharedFunc_800D908C_0_s00(5, chara, 24, 37, sfx, pitch0);
            break;

        case 3:
            if (chara->model_0.anim_4.keyframeIdx_8 < 90)
            {
                if (chara->model_0.anim_4.keyframeIdx_8 <= 60)
                {
                    sharedFunc_800D908C_0_s00(7, chara, 60, 71, sfx, pitch0);
                }
                else if (chara->model_0.anim_4.keyframeIdx_8 <= 81)
                {
                    sharedFunc_800D908C_0_s00(7, chara, 81, 71, sfx, pitch0);
                }
                else
                {
                    sharedFunc_800D908C_0_s00(7, chara, 89, 89, sfx, pitch0);
                }
            }
            else
            {
                if (chara->model_0.anim_4.keyframeIdx_8 <= 111)
                {
                    sharedFunc_800D908C_0_s00(7, chara, 121, 111, sfx, pitch1);
                }
                else
                {
                    sharedFunc_800D908C_0_s00(7, chara, 121, 128, sfx, pitch1);
                }
            }
            break;

        case 5:
            sharedFunc_800D9188_0_s00(chara->model_0.anim_4.status_0, chara, 210, Sfx_Unk1638);
            if (chara->model_0.anim_4.keyframeIdx_8 <= 173)
            {
                sharedFunc_800D908C_0_s00(11, chara, 182, 173, sfx, pitch0);
            }
            else
            {
                sharedFunc_800D908C_0_s00(11, chara, 182, 199, sfx, pitch0);
            }
            break;

        case 8:
            sharedFunc_800D908C_0_s00(17, chara, 298, 298, sfx, pitch0);
            break;
    }

    chara->rotation_24.vy  = FP_ANGLE_ABS(chara->rotation_24.vy + Q8_TO_Q4(sharedData_800D3150_3_s02));
    chara->headingAngle_3C = chara->rotation_24.vy;
    chara->moveSpeed_38    = CHARA_PROPERTIES.moveDistance_126;
    chara->field_34       += g_DeltaTime2;

    coords->flg = 0;
    Math_MatrixRotate1(&chara->rotation_24, &coords->coord);
}

/** Addresses
 * MAP3_S02: 0x800CF3E0
 * MAP6_S02: 0x800CDE8C
 * MAP6_S04: 0x800DCA0C
 * MAP7_S03: 0x800D3660
 */
void Ai_Alessa_Init(s_SubCharacter* chara)
{
    sharedFunc_800D923C_0_s00(chara);
    sharedData_800D3150_3_s02 = 0;
}
