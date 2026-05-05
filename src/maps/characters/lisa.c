#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "bodyprog/player.h"
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
void Lisa_Update(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* boneCoords)
{
    if (chara->model.controlState == 0)
    {
        Lisa_Init(chara);
    }

    Lisa_AnimStateUpdate(chara, boneCoords);
    Lisa_MovementUpdate(chara, boneCoords);
    Lisa_AnimUpdate(chara, anmHdr, boneCoords);
}

/** Addresses
 * MAP3_S04: 0x800D08FC
 * MAP4_S04: 0x800CFF14
 * MAP7_S00: 0x800CEAAC
 * MAP7_S01: 0x800D4E70
 * MAP7_S02: 0x800D5A0C
 */
void Lisa_AnimUpdate(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* boneCoords)
{
    s_AnimInfo* animInfo;

    if (chara->properties.player.field_F0 != 0)
    {
        return;
    }

    animInfo = &LISA_ANIM_INFOS[chara->model.anim.status];
    animInfo->playbackFunc(&chara->model, anmHdr, boneCoords, animInfo);
}

/** Addresses
 * MAP3_S04: 0x800D0944
 * MAP4_S04: 0x800CFF5C
 * MAP7_S00: 0x800CEAF4
 * MAP7_S01: 0x800D4EB8
 * MAP7_S02: 0x800D5A54
 */
void Lisa_MovementUpdate(s_SubCharacter* chara, GsCOORDINATE2* boneCoords)
{
    VECTOR3 unused;
    VECTOR3 offset;
    q19_12  moveSpeed;
    q3_12   headingAngle;
    q19_12  moveDist;
    s32     scaleRestoreShift;
    u32     scaleReduceShift;

    unused       = chara->position;
    moveSpeed    = chara->moveSpeed;
    headingAngle = chara->headingAngle;
    moveDist      = Q12_MULT_PRECISE(moveSpeed, g_DeltaTime);

    scaleRestoreShift = OVERFLOW_GUARD(moveDist);
    scaleReduceShift  = scaleRestoreShift >> 1;

    offset.vx = (u32)Q12_MULT_PRECISE(moveDist >> scaleReduceShift, Math_Sin(headingAngle) >> scaleReduceShift) << scaleRestoreShift;
    offset.vz = (u32)Q12_MULT_PRECISE(moveDist >> scaleReduceShift, Math_Cos(headingAngle) >> scaleReduceShift) << scaleRestoreShift;
    offset.vy = Q12_MULT_PRECISE(chara->fallSpeed, g_DeltaTime);

    chara->position.vx += offset.vx;
    chara->position.vy  = Q12(0.0f);
    chara->position.vz += offset.vz;

    boneCoords->coord.t[0] = Q12_TO_Q8(chara->position.vx);
    boneCoords->coord.t[1] = Q12_TO_Q8(chara->position.vy);
    boneCoords->coord.t[2] = Q12_TO_Q8(chara->position.vz);
}

/** Addresses
 * MAP3_S04: 0x800D0ADC
 * MAP4_S04: 0x800D00F4
 * MAP7_S00: 0x800CEC8C
 * MAP7_S01: 0x800D5050
 * MAP7_S02: 0x800D5BEC
 */
void Lisa_AnimStateUpdate(s_SubCharacter* chara, GsCOORDINATE2* boneCoords)
{
    s_Collision coll;
    e_SfxId     sfxId;
    s8          pitch0;
    s8          pitch1;

    #define dahliaProps (chara->properties.dahlia)

    switch (dahliaProps.controlState)
    {
        case LisaControl_None:
            break;

        case LisaControl_1:
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

            Model_AnimStatusSet(&chara->model, LisaAnim_2, false);
            Chara_AnimStateReset(chara);
            break;

        case LisaControl_5:
        case LisaControl_20:
            if (dahliaProps.moveDistance_126)
            {
                dahliaProps.moveDistance_126 -= TIMESTEP_SCALE_30_FPS(g_DeltaTime, Q12(0.4f)) * 2;
                if (dahliaProps.moveDistance_126 < Q12(0.0f))
                {
                    dahliaProps.moveDistance_126 = Q12(0.0f);
                }
            }

            if (dahliaProps.controlState == 5)
            {
                Model_AnimStatusKeyframeSet(chara->model, LisaAnim_1, true, LISA_ANIM_INFOS, 0);
            }
            else
            {
                Model_AnimStatusSet(&chara->model, LisaAnim_1, true);
            }

            Chara_AnimStateReset(chara);
            break;

        case LisaControl_6:
            Model_AnimStatusSet(&chara->model, LisaAnim_3, false);
            Chara_AnimStateReset(chara);
            break;

        case LisaControl_7:
            Model_AnimStatusSet(&chara->model, LisaAnim_4, false);

            if (chara->model.anim.keyframeIdx == 72)
            {
                dahliaProps.controlState = 20;
                chara->model.stateStep = 0;
            }
            break;

        case LisaControl_8:
            Model_AnimStatusSet(&chara->model, LisaAnim_5, false);
            Chara_AnimStateReset(chara);
            break;

        case LisaControl_9:
            Model_AnimStatusKeyframeSet(chara->model, LisaAnim_6, true, LISA_ANIM_INFOS, 0);
            Chara_AnimStateReset(chara);
            break;

        case LisaControl_10:
            Model_AnimStatusSet(&chara->model, LisaAnim_7, false);
            Chara_AnimStateReset(chara);
            break;

        case LisaControl_11:
            Model_AnimStatusKeyframeSet(chara->model, LisaAnim_8, true, LISA_ANIM_INFOS, 0);
            Chara_AnimStateReset(chara);
            break;

        case LisaControl_12:
            Model_AnimStatusKeyframeSet(chara->model, LisaAnim_9, true, LISA_ANIM_INFOS, 0);
            Chara_AnimStateReset(chara);
            break;

        case LisaControl_13:
            Model_AnimStatusSet(&chara->model, LisaAnim_10, false);
            Chara_AnimStateReset(chara);
            break;

        case LisaControl_14:
            Model_AnimStatusKeyframeSet(chara->model, LisaAnim_11, true, LISA_ANIM_INFOS, 0);
            break;

        case LisaControl_15:
            Model_AnimStatusSet(&chara->model, LisaAnim_12, false);
            break;

        case LisaControl_16:
            Model_AnimStatusSet(&chara->model, LisaAnim_13, false);
            Chara_AnimStateReset(chara);
            break;

        case LisaControl_17:
            Model_AnimStatusKeyframeSet(chara->model, LisaAnim_14, true, LISA_ANIM_INFOS, 0);
            Chara_AnimStateReset(chara);
            break;

        case LisaControl_18:
            Model_AnimStatusKeyframeSet(chara->model, LisaAnim_15, true, LISA_ANIM_INFOS, 0);
            Chara_AnimStateReset(chara);
            break;

        case LisaControl_19:
            Model_AnimStatusSet(&chara->model, LisaAnim_16, false);
            Chara_AnimStateReset(chara);
            break;

        case LisaControl_21:
            Model_AnimStatusSet(&chara->model, LisaAnim_17, false);
            Chara_AnimStateReset(chara);
            break;
    }

    Collision_Get(&coll, chara->position.vx, chara->position.vz);

    func_8007FDE0(coll.field_8, &sfxId, &pitch0, &pitch1);
    sfxId = Sfx_Unk1529;

    switch (dahliaProps.controlState)
    {
        case LisaControl_1:
            sharedFunc_800D908C_0_s00(ANIM_STATUS(LisaAnim_2, true), chara, 14, 31, sfxId, pitch0);
            break;

        case LisaControl_8:
            if (chara->model.anim.keyframeIdx <= 125)
            {
                sharedFunc_800D908C_0_s00(ANIM_STATUS(LisaAnim_5, true), chara, 125, 138, sfxId, pitch0);
            }
            else if (chara->model.anim.keyframeIdx <= 153)
            {
                sharedFunc_800D908C_0_s00(ANIM_STATUS(LisaAnim_5, true), chara, 153, 138, sfxId, pitch0);
            }
            else
            {
                sharedFunc_800D908C_0_s00(ANIM_STATUS(LisaAnim_5, true), chara, 189, 184, sfxId, pitch0);
            }
            break;

        case LisaControl_12:
            if (chara->model.anim.keyframeIdx <= 258)
            {
                // @bug From the other `keyframeIdx` checks here, should this be 258 instead of 263?
                sharedFunc_800D908C_0_s00(ANIM_STATUS(LisaAnim_9, true), chara, 263, 258, sfxId, pitch1);
            }
            else
            {
                sharedFunc_800D908C_0_s00(ANIM_STATUS(LisaAnim_9, true), chara, 263, 266, sfxId, pitch1);
            }
            break;

        case LisaControl_13:
            if (chara->model.anim.keyframeIdx <= 332)
            {
                sharedFunc_800D908C_0_s00(ANIM_STATUS(LisaAnim_10, true), chara, 332, 337, sfxId, pitch0);
            }
            else if (chara->model.anim.keyframeIdx <= 344)
            {
                sharedFunc_800D908C_0_s00(ANIM_STATUS(LisaAnim_10, true), chara, 344, 337, sfxId, pitch0);
            }
            else
            {
                sharedFunc_800D908C_0_s00(ANIM_STATUS(LisaAnim_10, true), chara, 352, 348, sfxId, pitch0);
            }
            break;

        case LisaControl_11:
            sharedFunc_800D908C_0_s00(ANIM_STATUS(LisaAnim_8, true), chara, 240, 240, sfxId, pitch0);
            break;

        case LisaControl_15:
#if defined(MAP7_S00)
            sharedFunc_800D9188_0_s00(ANIM_STATUS(LisaAnim_12, true), chara, 408, Sfx_Unk1639);
#endif
            sharedFunc_800D908C_0_s00(ANIM_STATUS(LisaAnim_12, true), chara, 406, 406, sfxId, pitch0);
            break;

        case LisaControl_16:
            if (chara->model.anim.keyframeIdx <= 423)
            {
                sharedFunc_800D908C_0_s00(ANIM_STATUS(LisaAnim_13, true), chara, 423, 425, sfxId, pitch0);
            }
            else if (chara->model.anim.keyframeIdx <= 429)
            {
                sharedFunc_800D908C_0_s00(ANIM_STATUS(LisaAnim_13, true), chara, 429, 425, sfxId, pitch0);
            }
            else
            {
                sharedFunc_800D908C_0_s00(ANIM_STATUS(LisaAnim_13, true), chara, 435, 432, sfxId, pitch0);
            }
            break;

        case LisaControl_17:
            if (chara->model.anim.keyframeIdx <= 460)
            {
                sharedFunc_800D908C_0_s00(ANIM_STATUS(LisaAnim_14, true), chara, 460, 477, sfxId, pitch0);
            }
            else if (chara->model.anim.keyframeIdx <= 497)
            {
                sharedFunc_800D908C_0_s00(ANIM_STATUS(LisaAnim_14, true), chara, 497, 477, sfxId, pitch0);
            }
            else
            {
                sharedFunc_800D908C_0_s00(ANIM_STATUS(LisaAnim_14, true), chara, 536, 516, sfxId, pitch0);
            }
            break;

        case LisaControl_18:
            if (chara->model.anim.keyframeIdx <= 551)
            {
                sharedFunc_800D908C_0_s00(ANIM_STATUS(LisaAnim_15, true), chara, 551, 555, sfxId, pitch0);
            }
            else if (chara->model.anim.keyframeIdx <= 559)
            {
                sharedFunc_800D908C_0_s00(ANIM_STATUS(LisaAnim_15, true), chara, 559, 555, sfxId, pitch0);
            }
            else
            {
                sharedFunc_800D908C_0_s00(ANIM_STATUS(LisaAnim_15, true), chara, 564, 564, sfxId, pitch0);
            }
            break;
    }

    chara->rotation.vy  = Q12_ANGLE_ABS(chara->rotation.vy + Q8_TO_Q4(sharedData_800D6BB8_3_s04));
    chara->headingAngle = chara->rotation.vy;
    chara->moveSpeed    = dahliaProps.moveDistance_126;
    chara->fallSpeed   += g_GravitySpeed;

    boneCoords->flg = false;
    Math_RotMatrixZxyNegGte(&chara->rotation, &boneCoords->coord);
}

/** Addresses
 * MAP3_S04: 0x800D1350
 * MAP4_S04: 0x800D0968
 * MAP7_S00: 0x800CF514
 * MAP7_S01: 0x800D58C4
 * MAP7_S02: 0x800D6460
 */
void Lisa_Init(s_SubCharacter* chara)
{
    Chara_CollisionReset(chara);
    sharedData_800D6BB8_3_s04 = 0;
}
