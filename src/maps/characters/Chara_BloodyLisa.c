#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "bodyprog/player_logic.h"
#include "main/rng.h"
#include "maps/shared.h"
#include "maps/characters/Chara_BloodyLisa.h"

/** AI code for `Chara_BloodyLisa`
 *
 * Included in:
 *  MAP7_S01
 *  MAP7_S02
 *  MAP7_S03
 */

 /** Addresses
 * MAP7_S01: 0x800D58E8
 * MAP7_S02: 0x800D6484
 * MAP7_S03: 0x800D4C50
 */
void Ai_BloodyLisa_Update(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* coords)
{
    if (chara->model_0.state_2 == 0)
    {
        Ai_BloodyLisa_Init(chara);
    }

    sharedFunc_800D5B3C_7_s01(chara, coords);
    sharedFunc_800D59A4_7_s01(chara, coords);
    sharedFunc_800D595C_7_s01(chara, anmHdr, coords);
}

 /** Addresses
 * MAP7_S01: 0x800D595C
 * MAP7_S02: 0x800D64F8
 * MAP7_S03: 0x800D4CC4
 */
void sharedFunc_800D595C_7_s01(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* coord)
{
    s_AnimInfo* animInfo;

    if (chara->properties_E4.player.field_F0 == 0)
    {
        animInfo = &BLOODY_LISA_ANIM_INFOS[chara->model_0.anim_4.status_0];
        animInfo->updateFunc_0(&chara->model_0, anmHdr, coord, animInfo);
    }
}

 /** Addresses
 * MAP7_S01: 0x800D59A4
 * MAP7_S02: 0x800D6540
 * MAP7_S03: 0x800D4D0C
 */
void sharedFunc_800D59A4_7_s01(s_SubCharacter* chara, GsCOORDINATE2* coord)
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
 * MAP7_S01: 0x800D5B3C
 * MAP7_S02: 0x800D66D8
 * MAP7_S03: 0x800D4EA4
 */
void sharedFunc_800D5B3C_7_s01(s_SubCharacter* chara, GsCOORDINATE2* coords)
{
    s_Collision coll;
    s32         sfx;
    s8          pitch0;
    s8          pitch1;

    #define dahliaProps (chara->properties_E4.dahlia)

    switch (dahliaProps.stateIdx0)
    {
        case 0:
            break;

        case 6:
            Model_AnimStatusSet(&chara->model_0, 1, false);
            Character_AnimStateReset(chara);
            break;
    }

    Collision_Get(&coll, chara->position_18.vx, chara->position_18.vz);
    func_8007FDE0(coll.field_8, &sfx, &pitch0, &pitch1);

    switch (dahliaProps.stateIdx0)
    {
        case 6:
            if (chara->model_0.anim_4.keyframeIdx_8 <= 12)
            {
                sharedFunc_800D908C_0_s00(3, chara, 12, 27, sfx, pitch0);
            }
            else if (chara->model_0.anim_4.keyframeIdx_8 <= 49)
            {
                sharedFunc_800D908C_0_s00(3, chara, 49, 27, sfx, pitch0);
            }
            else
            {
                sharedFunc_800D908C_0_s00(3, chara, 92, 69, sfx, pitch0);
            }
            break;
    }

    chara->rotation_24.vy  = FP_ANGLE_ABS(chara->rotation_24.vy + Q8_TO_Q4(sharedData_800E2C38_7_s01));
    chara->headingAngle_3C = chara->rotation_24.vy;
    chara->moveSpeed_38    = dahliaProps.moveDistance_126;
    chara->field_34       += g_DeltaTime2;

    coords->flg = false;
    Math_MatrixRotate1(&chara->rotation_24, &coords->coord);
}

 /** Addresses
 * MAP7_S01: 0x800D5CB4
 * MAP7_S02: 0x800D6850
 * MAP7_S03: 0x800D501C
 */
void Ai_BloodyLisa_Init(s_SubCharacter* chara)
{
    sharedFunc_800D923C_0_s00(chara);
    sharedData_800E2C38_7_s01 = 0;
}
