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
    s8          pitch;
    s8          sp2D; // Type asssumed.
    s32         tempVal;

    tempVal = chara->properties_E4.larvalStalker.properties_E8[0].val32;
    if (tempVal != 0 && chara->properties_E4.larvalStalker.properties_E8[0].val32 == 6)
    {
        if (chara->model_0.stateStep_3 == 0)
        {
            chara->model_0.anim_4.status_0 = ANIM_STATUS(1, false);
            chara->model_0.stateStep_3++;
        }

        if (chara->properties_E4.larvalStalker.properties_E8[4].val32 != 0)
        {
            chara->properties_E4.larvalStalker.properties_E8[0].val32 = 0;
            chara->model_0.stateStep_3 = 0;
            chara->properties_E4.larvalStalker.properties_E8[4].val32 = 0;
        }
    }

    Collision_Get(&coll, chara->position_18.vx, chara->position_18.vz);
    func_8007FDE0(coll.field_8, &sfx, &pitch, &sp2D);

    if (chara->properties_E4.larvalStalker.properties_E8[0].val32 == 6)
    {
        if (chara->model_0.anim_4.keyframeIdx_8 < 13)
        {
            sharedFunc_800D908C_0_s00(3, chara, 12, 27, sfx, pitch);
        }
        else if (chara->model_0.anim_4.keyframeIdx_8 < 50)
        {
            sharedFunc_800D908C_0_s00(3, chara, 49, 27, sfx, pitch);
        }
        else
        {
            sharedFunc_800D908C_0_s00(3, chara, 92, 69, sfx, pitch);
        }
    }

    chara->headingAngle_3C =
    chara->rotation_24.vy  = FP_ANGLE_NORM_U((chara->rotation_24.vy + (sharedData_800E2C38_7_s01 >> 4)) + FP_ANGLE(360.0f));

    chara->moveSpeed_38 = chara->properties_E4.larvalStalker.properties_E8[15].val16[1];
    chara->field_34    += g_DeltaTime2;

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
