#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "bodyprog/player_logic.h"
#include "main/rng.h"
#include "maps/shared.h"
#include "maps/characters/lisa.h"

/** AI code for `Chara_Lisa`
 *
 * Included in:
 *  MAP3_S04
 *  MAP4_S04
 *  MAP7_S00
 *  MAP7_S01
 *  MAP7_S02
 */

/** Addresses
 * MAP3_S04: 0x800D0888
 * MAP4_S04: 0x800CFEA0
 * MAP7_S00: 0x800CEA38
 * MAP7_S01: 0x800D4DFC
 * MAP7_S02: 0x800D5998
 */
void Ai_Lisa_Update(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* coords)
{
    if (chara->model_0.controlState_2 == ModelState_Uninitialized)
    {
        Ai_Lisa_Init(chara);
    }

    Ai_Lisa_AnimStateUpdate(chara, coords);
    Ai_Lisa_MovementUpdate(chara, coords);
    Ai_Lisa_AnimUpdate(chara, anmHdr, coords);
}

/** Addresses
 * MAP3_S04: 0x800D08FC
 * MAP4_S04: 0x800CFF14
 * MAP7_S00: 0x800CEAAC
 * MAP7_S01: 0x800D4E70
 * MAP7_S02: 0x800D5A0C
 */
void Ai_Lisa_AnimUpdate(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* coords)
{
    s_AnimInfo* animInfo;

    if (chara->properties_E4.player.field_F0 != 0)
    {
        return;
    }

    animInfo = &LISA_ANIM_INFOS[chara->model_0.anim_4.status_0];
    animInfo->updateFunc_0(&chara->model_0, anmHdr, coords, animInfo);
}

/** Addresses
 * MAP3_S04: 0x800D0944
 * MAP4_S04: 0x800CFF5C
 * MAP7_S00: 0x800CEAF4
 * MAP7_S01: 0x800D4EB8
 * MAP7_S02: 0x800D5A54
 */
void Ai_Lisa_MovementUpdate(s_SubCharacter* chara, GsCOORDINATE2* coords)
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
 * MAP3_S04: 0x800D0ADC
 * MAP4_S04: 0x800D00F4
 * MAP7_S00: 0x800CEC8C
 * MAP7_S01: 0x800D5050
 * MAP7_S02: 0x800D5BEC
 */
void Ai_Lisa_AnimStateUpdate(s_SubCharacter* chara, GsCOORDINATE2* coords)
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

        case 1:
            if (dahliaProps.moveDistance_126 > Q12(1.25f))
            {
                dahliaProps.moveDistance_126 -= TIMESTEP_SCALE_30_FPS(g_DeltaTime, Q12(0.5f));
                if (dahliaProps.moveDistance_126 < Q12(1.25f))
                {
                    dahliaProps.moveDistance_126 = Q12(1.25f);
                }
            }
            else if (dahliaProps.moveDistance_126 < Q12(1.25f))
            {
                dahliaProps.moveDistance_126 += TIMESTEP_SCALE_30_FPS(g_DeltaTime, Q12(0.4f));
                dahliaProps.moveDistance_126  = CLAMP(dahliaProps.moveDistance_126, 0, Q12(1.25f));
            }

            Model_AnimStatusSet(&chara->model_0, LisaAnim_2, false);
            Character_AnimStateReset(chara);
            break;

        case 5:
        case 20:
            if (dahliaProps.moveDistance_126)
            {
                dahliaProps.moveDistance_126 -= TIMESTEP_SCALE_30_FPS(g_DeltaTime, Q12(0.4f)) * 2;
                if (dahliaProps.moveDistance_126 < Q12(0.0f))
                {
                    dahliaProps.moveDistance_126 = Q12(0.0f);
                }
            }

            if (dahliaProps.stateIdx0 == 5)
            {
                Model_AnimStatusKeyframeSet(chara->model_0, LisaAnim_1, true, LISA_ANIM_INFOS, 0);
            }
            else
            {
                Model_AnimStatusSet(&chara->model_0, LisaAnim_1, true);
            }

            Character_AnimStateReset(chara);
            break;

        case 6:
            Model_AnimStatusSet(&chara->model_0, LisaAnim_3, false);
            Character_AnimStateReset(chara);
            break;

        case 7:
            Model_AnimStatusSet(&chara->model_0, LisaAnim_4, false);

            if (chara->model_0.anim_4.keyframeIdx_8 == 72)
            {
                dahliaProps.stateIdx0 = 20;
                chara->model_0.stateStep_3 = 0;
            }
            break;

        case 8:
            Model_AnimStatusSet(&chara->model_0, LisaAnim_5, false);
            Character_AnimStateReset(chara);
            break;

        case 9:
            Model_AnimStatusKeyframeSet(chara->model_0, LisaAnim_6, true, LISA_ANIM_INFOS, 0);
            Character_AnimStateReset(chara);
            break;

        case 10:
            Model_AnimStatusSet(&chara->model_0, LisaAnim_7, false);
            Character_AnimStateReset(chara);
            break;

        case 11:
            Model_AnimStatusKeyframeSet(chara->model_0, LisaAnim_8, true, LISA_ANIM_INFOS, 0);
            Character_AnimStateReset(chara);
            break;

        case 12:
            Model_AnimStatusKeyframeSet(chara->model_0, LisaAnim_9, true, LISA_ANIM_INFOS, 0);
            Character_AnimStateReset(chara);
            break;

        case 13:
            Model_AnimStatusSet(&chara->model_0, LisaAnim_10, false);
            Character_AnimStateReset(chara);
            break;

        case 14:
            Model_AnimStatusKeyframeSet(chara->model_0, LisaAnim_11, true, LISA_ANIM_INFOS, 0);
            break;

        case 15:
            Model_AnimStatusSet(&chara->model_0, LisaAnim_12, false);
            break;

        case 16:
            Model_AnimStatusSet(&chara->model_0, LisaAnim_13, false);
            Character_AnimStateReset(chara);
            break;

        case 17:
            Model_AnimStatusKeyframeSet(chara->model_0, LisaAnim_14, true, LISA_ANIM_INFOS, 0);
            Character_AnimStateReset(chara);
            break;

        case 18:
            Model_AnimStatusKeyframeSet(chara->model_0, LisaAnim_15, true, LISA_ANIM_INFOS, 0);
            Character_AnimStateReset(chara);
            break;

        case 19:
            Model_AnimStatusSet(&chara->model_0, LisaAnim_16, false);
            Character_AnimStateReset(chara);
            break;

        case 21:
            Model_AnimStatusSet(&chara->model_0, LisaAnim_17, false);
            Character_AnimStateReset(chara);
            break;
    }

    Collision_Get(&coll, chara->position_18.vx, chara->position_18.vz);

    func_8007FDE0(coll.field_8, &sfx, &pitch0, &pitch1);
    sfx = Sfx_Unk1529;

    switch (dahliaProps.stateIdx0)
    {
        case 1:
            sharedFunc_800D908C_0_s00(ANIM_STATUS(LisaAnim_2, true), chara, 14, 31, sfx, pitch0);
            break;

        case 8:
            if (chara->model_0.anim_4.keyframeIdx_8 <= 125)
            {
                sharedFunc_800D908C_0_s00(ANIM_STATUS(LisaAnim_5, true), chara, 125, 138, sfx, pitch0);
            }
            else if (chara->model_0.anim_4.keyframeIdx_8 <= 153)
            {
                sharedFunc_800D908C_0_s00(ANIM_STATUS(LisaAnim_5, true), chara, 153, 138, sfx, pitch0);
            }
            else
            {
                sharedFunc_800D908C_0_s00(ANIM_STATUS(LisaAnim_5, true), chara, 189, 184, sfx, pitch0);
            }
            break;

        case 12:
            if (chara->model_0.anim_4.keyframeIdx_8 <= 258)
            {
                // @bug From the other `keyframeIdx_8` checks here, should this be 258 instead of 263?
                sharedFunc_800D908C_0_s00(ANIM_STATUS(LisaAnim_9, true), chara, 263, 258, sfx, pitch1);
            }
            else
            {
                sharedFunc_800D908C_0_s00(ANIM_STATUS(LisaAnim_9, true), chara, 263, 266, sfx, pitch1);
            }
            break;

        case 13:
            if (chara->model_0.anim_4.keyframeIdx_8 <= 332)
            {
                sharedFunc_800D908C_0_s00(ANIM_STATUS(LisaAnim_10, true), chara, 332, 337, sfx, pitch0);
            }
            else if (chara->model_0.anim_4.keyframeIdx_8 <= 344)
            {
                sharedFunc_800D908C_0_s00(ANIM_STATUS(LisaAnim_10, true), chara, 344, 337, sfx, pitch0);
            }
            else
            {
                sharedFunc_800D908C_0_s00(ANIM_STATUS(LisaAnim_10, true), chara, 352, 348, sfx, pitch0);
            }
            break;

        case 11:
            sharedFunc_800D908C_0_s00(ANIM_STATUS(LisaAnim_8, true), chara, 240, 240, sfx, pitch0);
            break;

        case 15:
#if defined(MAP7_S00)
            sharedFunc_800D9188_0_s00(ANIM_STATUS(LisaAnim_12, true), chara, 408, Sfx_Unk1639);
#endif
            sharedFunc_800D908C_0_s00(ANIM_STATUS(LisaAnim_12, true), chara, 406, 406, sfx, pitch0);
            break;

        case 16:
            if (chara->model_0.anim_4.keyframeIdx_8 <= 423)
            {
                sharedFunc_800D908C_0_s00(ANIM_STATUS(LisaAnim_13, true), chara, 423, 425, sfx, pitch0);
            }
            else if (chara->model_0.anim_4.keyframeIdx_8 <= 429)
            {
                sharedFunc_800D908C_0_s00(ANIM_STATUS(LisaAnim_13, true), chara, 429, 425, sfx, pitch0);
            }
            else
            {
                sharedFunc_800D908C_0_s00(ANIM_STATUS(LisaAnim_13, true), chara, 435, 432, sfx, pitch0);
            }
            break;

        case 17:
            if (chara->model_0.anim_4.keyframeIdx_8 <= 460)
            {
                sharedFunc_800D908C_0_s00(ANIM_STATUS(LisaAnim_14, true), chara, 460, 477, sfx, pitch0);
            }
            else if (chara->model_0.anim_4.keyframeIdx_8 <= 497)
            {
                sharedFunc_800D908C_0_s00(ANIM_STATUS(LisaAnim_14, true), chara, 497, 477, sfx, pitch0);
            }
            else
            {
                sharedFunc_800D908C_0_s00(ANIM_STATUS(LisaAnim_14, true), chara, 536, 516, sfx, pitch0);
            }
            break;

        case 18:
            if (chara->model_0.anim_4.keyframeIdx_8 <= 551)
            {
                sharedFunc_800D908C_0_s00(ANIM_STATUS(LisaAnim_15, true), chara, 551, 555, sfx, pitch0);
            }
            else if (chara->model_0.anim_4.keyframeIdx_8 <= 559)
            {
                sharedFunc_800D908C_0_s00(ANIM_STATUS(LisaAnim_15, true), chara, 559, 555, sfx, pitch0);
            }
            else
            {
                sharedFunc_800D908C_0_s00(ANIM_STATUS(LisaAnim_15, true), chara, 564, 564, sfx, pitch0);
            }
            break;
    }

    chara->rotation_24.vy  = Q12_ANGLE_ABS(chara->rotation_24.vy + Q8_TO_Q4(sharedData_800D6BB8_3_s04));
    chara->headingAngle_3C = chara->rotation_24.vy;
    chara->moveSpeed_38    = dahliaProps.moveDistance_126;
    chara->fallSpeed_34   += g_GravitySpeed;

    coords->flg = false;
    Math_RotMatrixZxyNegGte(&chara->rotation_24, &coords->coord);
}

/** Addresses
 * MAP3_S04: 0x800D1350
 * MAP4_S04: 0x800D0968
 * MAP7_S00: 0x800CF514
 * MAP7_S01: 0x800D58C4
 * MAP7_S02: 0x800D6460
 */
void Ai_Lisa_Init(s_SubCharacter* chara)
{
    sharedFunc_800D923C_0_s00(chara);
    sharedData_800D6BB8_3_s04 = 0;
}
