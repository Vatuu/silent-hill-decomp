#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "main/rng.h"
#include "maps/shared.h"
#include "maps/characters/alessa.h"

/** AI code for `Chara_Alessa`
 *
 * Included in:
 *  MAP3_S02
 *  MAP6_S02
 *  MAP6_S04
 *  MAP7_S03
 */

#define alessaProps alessa->properties.alessa

/** Addresses
 * MAP3_S02: 0x800CEC88
 * MAP6_S02: 0x800CD734
 * MAP6_S04: 0x800DC2B4
 * MAP7_S03: 0x800D2F08
 */
void Ai_Alessa_Update(s_SubCharacter* alessa, s_AnmHeader* anmHdr, GsCOORDINATE2* boneCoords)
{
    if (alessa->model.controlState == 0)
    {
        Ai_Alessa_Init(alessa);
    }

    Ai_Alessa_AnimStateUpdate(alessa, boneCoords);
    Ai_Alessa_MovementUpdate(alessa, boneCoords);
    Ai_Alessa_AnimUpdate(alessa, anmHdr, boneCoords);
}

/** Addresses
 * MAP3_S02: 0x800CECFC
 * MAP6_S02: 0x800CD7A8
 * MAP6_S04: 0x800DC328
 * MAP7_S03: 0x800D2F7C
 */
void Ai_Alessa_AnimUpdate(s_SubCharacter* alessa, s_AnmHeader* anmHdr, GsCOORDINATE2* boneCoords)
{
    s_AnimInfo* animInfo;

    if (alessaProps.field_F0 == 0)
    {
        animInfo = &ALESSA_ANIM_INFOS[alessa->model.anim.status];
        animInfo->playbackFunc(&alessa->model, anmHdr, boneCoords, animInfo);
    }
}

/** Addresses
 * MAP3_S02: 0x800CED44
 * MAP6_S02: 0x800CD7F0
 * MAP6_S04: 0x800DC370
 * MAP7_S03: 0x800D2FC4
 */
void Ai_Alessa_MovementUpdate(s_SubCharacter* alessa, GsCOORDINATE2* boneCoords)
{
    VECTOR3 unused;
    VECTOR3 offset;
    q19_12  moveSpeed;
    q3_12   headingAngle;
    q19_12  moveDist;
    s32     scaleRestoreShift;
    u32     scaleReduceShift;

    unused       = alessa->position;
    moveSpeed    = alessa->moveSpeed;
    headingAngle = alessa->headingAngle;
    moveDist     = Q12_MULT_PRECISE(moveSpeed, g_DeltaTime);

    scaleRestoreShift = OVERFLOW_GUARD(moveDist);
    scaleReduceShift  = scaleRestoreShift >> 1;

    offset.vx = (u32)Q12_MULT_PRECISE(moveDist >> scaleReduceShift, Math_Sin(headingAngle) >> scaleReduceShift) << scaleRestoreShift;
    offset.vz = (u32)Q12_MULT_PRECISE(moveDist >> scaleReduceShift, Math_Cos(headingAngle) >> scaleReduceShift) << scaleRestoreShift;
    offset.vy = Q12_MULT_PRECISE(alessa->fallSpeed, g_DeltaTime);

    alessa->position.vx += offset.vx;
    alessa->position.vy = Q12(0.0f);
    alessa->position.vz += offset.vz;

    boneCoords->coord.t[0] = Q12_TO_Q8(alessa->position.vx);
    boneCoords->coord.t[1] = Q12_TO_Q8(alessa->position.vy);
    boneCoords->coord.t[2] = Q12_TO_Q8(alessa->position.vz);
}

/** Addresses
 * MAP3_S02: 0x800CEEDC
 * MAP6_S02: 0x800CD988
 * MAP6_S04: 0x800DC508
 * MAP7_S03: 0x800D315C
 */
void Ai_Alessa_AnimStateUpdate(s_SubCharacter* alessa, GsCOORDINATE2* boneCoords)
{
    s_Collision coll;
    e_SfxId     sfx;
    s8          pitch0;
    s8          pitch1;

    switch (alessaProps.stateIdx0)
    {
        case 0:
            break;

        case 2:
            if (alessaProps.moveSpeed_126 > Q12(1.25f))
            {
                alessaProps.moveSpeed_126 -= TIMESTEP_SCALE_30_FPS(g_DeltaTime, Q12(0.5f));
                if (alessaProps.moveSpeed_126 < Q12(1.25f))
                {
                    alessaProps.moveSpeed_126 = Q12(1.25f);
                }
            }
            else if (alessaProps.moveSpeed_126 < Q12(1.25f))
            {
                alessaProps.moveSpeed_126 += TIMESTEP_SCALE_30_FPS(g_DeltaTime, Q12(0.4f));
                alessaProps.moveSpeed_126  = CLAMP(alessaProps.moveSpeed_126, Q12(0.0f), Q12(1.25f));
            }

            Model_AnimStatusSet(&alessa->model, AlessaAnim_WalkForward, false);
            Character_AnimStateReset(alessa);
            break;

        case 1:
            if (alessaProps.moveSpeed_126 != Q12(0.0f))
            {
                alessaProps.moveSpeed_126 -= TIMESTEP_SCALE_30_FPS(g_DeltaTime, Q12(0.4f)) * 2;
                if (alessaProps.moveSpeed_126 < Q12(0.0f))
                {
                    alessaProps.moveSpeed_126 = Q12(0.0f);
                }
            }

            Model_AnimStatusKeyframeSet(alessa->model, AlessaAnim_StandIdle, true, ALESSA_ANIM_INFOS, 0);
            Character_AnimStateReset(alessa);
            break;

        case 4:
            Model_AnimStatusSet(&alessa->model, AlessaAnim_ForcePush, false);
            Character_AnimStateReset(alessa);
            break;

        case 3:
            Model_AnimStatusSet(&alessa->model, AlessaAnim_WalkForwardTurnStumble, false);
            Character_AnimStateReset(alessa);
            break;

        case 5:
            Model_AnimStatusSet(&alessa->model, AlessaAnim_StumbleForwardCrumple, false);
            Character_AnimStateReset(alessa);
            break;

        case 6:
            Model_AnimStatusSet(&alessa->model, AlessaAnim_CrumpleLookUp, false);
            Character_AnimStateReset(alessa);
            break;

        case 7:
            Model_AnimStatusSet(&alessa->model, AlessaAnim_CrumpleShakeHead, false);
            Character_AnimStateReset(alessa);
            break;

        case 8:
            Model_AnimStatusSet(&alessa->model, AlessaAnim_StandLookRight, false);
            Character_AnimStateReset(alessa);
            break;

        case 9:
            Model_AnimStatusSet(&alessa->model, AlessaAnim_CrumpleIdle, false);
            Character_AnimStateReset(alessa);
            break;

        case 10:
            Model_AnimStatusSet(&alessa->model, AlessaAnim_Kneel, false);
            Character_AnimStateReset(alessa);
            break;
    }

    Collision_Get(&coll, alessa->position.vx, alessa->position.vz);
    func_8007FDE0(coll.field_8, &sfx, &pitch0, &pitch1);

    switch (alessaProps.stateIdx0)
    {
        case 2:
            sharedFunc_800D908C_0_s00(ANIM_STATUS(AlessaAnim_WalkForward, true), alessa, 24, 37, sfx, pitch0);
            break;

        case 3:
            if (alessa->model.anim.keyframeIdx < 90)
            {
                if (alessa->model.anim.keyframeIdx <= 60)
                {
                    sharedFunc_800D908C_0_s00(ANIM_STATUS(AlessaAnim_WalkForwardTurnStumble, true), alessa, 60, 71, sfx, pitch0);
                }
                else if (alessa->model.anim.keyframeIdx <= 81)
                {
                    sharedFunc_800D908C_0_s00(ANIM_STATUS(AlessaAnim_WalkForwardTurnStumble, true), alessa, 81, 71, sfx, pitch0);
                }
                else
                {
                    sharedFunc_800D908C_0_s00(ANIM_STATUS(AlessaAnim_WalkForwardTurnStumble, true), alessa, 89, 89, sfx, pitch0);
                }
            }
            else
            {
                if (alessa->model.anim.keyframeIdx <= 111)
                {
                    sharedFunc_800D908C_0_s00(ANIM_STATUS(AlessaAnim_WalkForwardTurnStumble, true), alessa, 121, 111, sfx, pitch1);
                }
                else
                {
                    sharedFunc_800D908C_0_s00(ANIM_STATUS(AlessaAnim_WalkForwardTurnStumble, true), alessa, 121, 128, sfx, pitch1);
                }
            }
            break;

        case 5:
            sharedFunc_800D9188_0_s00(alessa->model.anim.status, alessa, 210, Sfx_Unk1638);

            if (alessa->model.anim.keyframeIdx <= 173)
            {
                sharedFunc_800D908C_0_s00(ANIM_STATUS(AlessaAnim_StumbleForwardCrumple, true), alessa, 182, 173, sfx, pitch0);
            }
            else
            {
                sharedFunc_800D908C_0_s00(ANIM_STATUS(AlessaAnim_StumbleForwardCrumple, true), alessa, 182, 199, sfx, pitch0);
            }
            break;

        case 8:
            sharedFunc_800D908C_0_s00(ANIM_STATUS(AlessaAnim_StandLookRight, true), alessa, 298, 298, sfx, pitch0);
            break;
    }

    alessa->rotation.vy  = Q12_ANGLE_ABS(alessa->rotation.vy + (sharedData_800D3150_3_s02 >> 4));
    alessa->headingAngle = alessa->rotation.vy;
    alessa->moveSpeed    = alessaProps.moveSpeed_126;
    alessa->fallSpeed   += g_GravitySpeed;

    boneCoords->flg = false;
    Math_RotMatrixZxyNegGte(&alessa->rotation, &boneCoords->coord);
}

/** Addresses
 * MAP3_S02: 0x800CF3E0
 * MAP6_S02: 0x800CDE8C
 * MAP6_S04: 0x800DCA0C
 * MAP7_S03: 0x800D3660
 */
void Ai_Alessa_Init(s_SubCharacter* alessa)
{
    sharedFunc_800D923C_0_s00(alessa);
    sharedData_800D3150_3_s02 = 0;
}

#undef darliaProps
