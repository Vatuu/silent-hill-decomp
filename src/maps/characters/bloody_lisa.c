#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "bodyprog/player_logic.h"
#include "main/rng.h"
#include "maps/shared.h"
#include "maps/characters/bloody_lisa.h"

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
    if (chara->model_0.controlState_2 == ModelState_Uninitialized)
    {
        Ai_BloodyLisa_Init(chara);
    }

    Ai_BloodyLisa_AnimStateUpdate(chara, coords);
    Ai_BloodyLisa_MovementUpdate(chara, coords);
    Ai_BloodyLisa_AnimUpdate(chara, anmHdr, coords);
}

 /** Addresses
 * MAP7_S01: 0x800D595C
 * MAP7_S02: 0x800D64F8
 * MAP7_S03: 0x800D4CC4
 */
void Ai_BloodyLisa_AnimUpdate(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* coords)
{
    s_AnimInfo* animInfo;

    if (chara->properties_E4.player.field_F0 == 0)
    {
        animInfo = &BLOODY_LISA_ANIM_INFOS[chara->model_0.anim_4.status_0];
        animInfo->updateFunc_0(&chara->model_0, anmHdr, coords, animInfo);
    }
}

 /** Addresses
 * MAP7_S01: 0x800D59A4
 * MAP7_S02: 0x800D6540
 * MAP7_S03: 0x800D4D0C
 */
void Ai_BloodyLisa_MovementUpdate(s_SubCharacter* chara, GsCOORDINATE2* coords)
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

 /** Addresses
 * MAP7_S01: 0x800D5B3C
 * MAP7_S02: 0x800D66D8
 * MAP7_S03: 0x800D4EA4
 */
void Ai_BloodyLisa_AnimStateUpdate(s_SubCharacter* chara, GsCOORDINATE2* coords)
{
    s_Collision coll;
    e_SfxId     sfx;
    s8          pitch0;
    s8          pitch1;

    #define dahliaProps (chara->properties_E4.dahlia)

    switch (dahliaProps.stateIdx0)
    {
        case 0:
            break;

        case 6:
            Model_AnimStatusSet(&chara->model_0, BloodyLisaAnim_Walk, false);
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
                sharedFunc_800D908C_0_s00(ANIM_STATUS(BloodyLisaAnim_Walk, true), chara, 12, 27, sfx, pitch0);
            }
            else if (chara->model_0.anim_4.keyframeIdx_8 <= 49)
            {
                sharedFunc_800D908C_0_s00(ANIM_STATUS(BloodyLisaAnim_Walk, true), chara, 49, 27, sfx, pitch0);
            }
            else
            {
                sharedFunc_800D908C_0_s00(ANIM_STATUS(BloodyLisaAnim_Walk, true), chara, 92, 69, sfx, pitch0);
            }
            break;
    }

    chara->rotation_24.vy  = Q12_ANGLE_ABS(chara->rotation_24.vy + Q8_TO_Q4(sharedData_800E2C38_7_s01));
    chara->headingAngle_3C = chara->rotation_24.vy;
    chara->moveSpeed_38    = dahliaProps.moveDistance_126;
    chara->fallSpeed_34   += g_GravitySpeed;

    coords->flg = false;
    Math_RotMatrixZxyNegGte(&chara->rotation_24, &coords->coord);
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
