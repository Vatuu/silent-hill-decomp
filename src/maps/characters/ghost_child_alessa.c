#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "maps/shared.h"
#include "maps/characters/ghost_child_alessa.h"

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
void GhostChildAlessa_Update(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* boneCoords)
{
    if (chara->model.charaId != Chara_GhostChildAlessa)
    {
        GhostChildAlessa_Init(chara);
    }

    GhostChildAlessa_AnimStateUpdate(chara, boneCoords);
    GhostChildAlessa_MovementUpdate(chara, boneCoords);
    GhostChildAlessa_AnimUpdate(chara, anmHdr, boneCoords);
}

/** Addresses
 * MAP7_S01: 0x800D4A2C
 * MAP7_S02: 0x800D7ADC
 */
void GhostChildAlessa_AnimUpdate(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* boneCoords)
{
    s_AnimInfo* animInfo;

    if (chara->properties.player.field_F0 != 0)
    {
        return;
    }

    animInfo = &GHOST_CHILD_ALESSA_ANIM_INFOS[chara->model.anim.status];
    animInfo->playbackFunc(&chara->model, anmHdr, boneCoords, animInfo);
}

/** Addresses
 * MAP7_S01: 0x800D4A74
 * MAP7_S02: 0x800D7B24
 */
void GhostChildAlessa_MovementUpdate(s_SubCharacter* chara, GsCOORDINATE2* boneCoords)
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
 * MAP7_S01: 0x800D4C0C
 * MAP7_S02: 0x800D7CBC
 */
void GhostChildAlessa_AnimStateUpdate(s_SubCharacter* chara, GsCOORDINATE2* boneCoords)
{
    #define dahliaProps (chara->properties.dahlia)

    switch (dahliaProps.stateIdx0)
    {
        case 0:
            break;

        case 1:
            dahliaProps.moveDistance_126 = dahliaProps.field_124;
            Model_AnimStatusSet(&chara->model, GhostChildAlessaAnim_1, false);
            Character_AnimStateReset(chara);
            break;

        case 2:
            dahliaProps.moveDistance_126 = dahliaProps.field_124;
            Model_AnimStatusSet(&chara->model, GhostChildAlessaAnim_2, false);
            Character_AnimStateReset(chara);
            break;

        case 6:
            Model_AnimStatusSet(&chara->model, GhostChildAlessaAnim_3, false);
            if (chara->model.anim.keyframeIdx == 63)
            {
                dahliaProps.stateIdx0 = 7;
                chara->model.stateStep = 0;
            }
            break;

        case 7:
            Model_AnimStatusSet(&chara->model, GhostChildAlessaAnim_4, false);
            Character_AnimStateReset(chara);
            break;

        case 8:
            Model_AnimStatusSet(&chara->model, GhostChildAlessaAnim_5, false);
            Character_AnimStateReset(chara);
            break;

        case 9:
            Model_AnimStatusSet(&chara->model, GhostChildAlessaAnim_6, false);
            Character_AnimStateReset(chara);
            break;

        case 10:
            Model_AnimStatusSet(&chara->model, GhostChildAlessaAnim_7, false);
            Character_AnimStateReset(chara);
            break;

        case 11:
            Model_AnimStatusSet(&chara->model, GhostChildAlessaAnim_8, false);
            Character_AnimStateReset(chara);
            break;
    }

    chara->rotation.vy  = Q12_ANGLE_ABS(chara->rotation.vy + Q8_TO_Q4(sharedData_800E39D8_0_s00));
    chara->headingAngle = chara->rotation.vy;
    chara->moveSpeed    = dahliaProps.moveDistance_126;
    chara->fallSpeed   += g_GravitySpeed;

    boneCoords->flg = false;
    Math_RotMatrixZxyNegGte(&chara->rotation, &boneCoords->coord);
}

/** Addresses
 * MAP7_S01: 0x800D4DD8
 * MAP7_S02: 0x800D7E88
 */
void GhostChildAlessa_Init(s_SubCharacter* chara)
{
    sharedFunc_800D923C_0_s00(chara);
    sharedData_800E39D8_0_s00 = 0;
}
