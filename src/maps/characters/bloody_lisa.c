#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "bodyprog/player.h"
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
void BloodyLisa_Update(s_SubCharacter* bloodyLisa, s_AnmHeader* anmHdr, GsCOORDINATE2* boneCoords)
{
    if (bloodyLisa->model.controlState == BloodyLisaControl_None)
    {
        BloodyLisa_Init(bloodyLisa);
    }

    BloodyLisa_AnimStateUpdate(bloodyLisa, boneCoords);
    BloodyLisa_MovementUpdate(bloodyLisa, boneCoords);
    BloodyLisa_AnimUpdate(bloodyLisa, anmHdr, boneCoords);
}

 /** Addresses
  * MAP7_S01: 0x800D595C
  * MAP7_S02: 0x800D64F8
  * MAP7_S03: 0x800D4CC4
  */
void BloodyLisa_AnimUpdate(s_SubCharacter* bloodyLisa, s_AnmHeader* anmHdr, GsCOORDINATE2* boneCoords)
{
    s_AnimInfo* animInfo;

    if (bloodyLisa->properties.player.field_F0 == 0)
    {
        animInfo = &BLOODY_LISA_ANIM_INFOS[bloodyLisa->model.anim.status];
        animInfo->playbackFunc(&bloodyLisa->model, anmHdr, boneCoords, animInfo);
    }
}

 /** Addresses
  * MAP7_S01: 0x800D59A4
  * MAP7_S02: 0x800D6540
  * MAP7_S03: 0x800D4D0C
  */
void BloodyLisa_MovementUpdate(s_SubCharacter* bloodyLisa, GsCOORDINATE2* boneCoords)
{
    VECTOR3 unused;
    VECTOR3 offset;
    q19_12  moveSpeed;
    q3_12   headingAngle;
    q19_12  moveDist;
    s32     scaleRestoreShift;
    u32     scaleReduceShift;

    unused       = bloodyLisa->position;
    moveSpeed    = bloodyLisa->moveSpeed;
    headingAngle = bloodyLisa->headingAngle;
    moveDist      = Q12_MULT_PRECISE(moveSpeed, g_DeltaTime);

    scaleRestoreShift = OVERFLOW_GUARD(moveDist);
    scaleReduceShift  = scaleRestoreShift >> 1;

    offset.vx = (u32)Q12_MULT_PRECISE(moveDist >> scaleReduceShift, Math_Sin(headingAngle) >> scaleReduceShift) << scaleRestoreShift;
    offset.vz = (u32)Q12_MULT_PRECISE(moveDist >> scaleReduceShift, Math_Cos(headingAngle) >> scaleReduceShift) << scaleRestoreShift;
    offset.vy = Q12_MULT_PRECISE(bloodyLisa->fallSpeed, g_DeltaTime);

    bloodyLisa->position.vx += offset.vx;
    bloodyLisa->position.vy  = Q12(0.0f);
    bloodyLisa->position.vz += offset.vz;

    boneCoords->coord.t[0] = Q12_TO_Q8(bloodyLisa->position.vx);
    boneCoords->coord.t[1] = Q12_TO_Q8(bloodyLisa->position.vy);
    boneCoords->coord.t[2] = Q12_TO_Q8(bloodyLisa->position.vz);
}

 /** Addresses
  * MAP7_S01: 0x800D5B3C
  * MAP7_S02: 0x800D66D8
  * MAP7_S03: 0x800D4EA4
  */
void BloodyLisa_AnimStateUpdate(s_SubCharacter* bloodyLisa, GsCOORDINATE2* boneCoords)
{
    s_Collision coll;
    e_SfxId     sfx;
    s8          pitch0;
    s8          pitch1;

    #define dahliaProps (bloodyLisa->properties.dahlia)

    switch (dahliaProps.controlState)
    {
        case BloodyLisaControl_None:
            break;

        case BloodyLisaControl_6:
            Model_AnimStatusSet(&bloodyLisa->model, BloodyLisaAnim_Walk, false);
            Chara_AnimStateReset(bloodyLisa);
            break;
    }

    Collision_Get(&coll, bloodyLisa->position.vx, bloodyLisa->position.vz);
    func_8007FDE0(coll.field_8, &sfx, &pitch0, &pitch1);

    switch (dahliaProps.controlState)
    {
        case BloodyLisaControl_6:
            if (bloodyLisa->model.anim.keyframeIdx <= 12)
            {
                sharedFunc_800D908C_0_s00(ANIM_STATUS(BloodyLisaAnim_Walk, true), bloodyLisa, 12, 27, sfx, pitch0);
            }
            else if (bloodyLisa->model.anim.keyframeIdx <= 49)
            {
                sharedFunc_800D908C_0_s00(ANIM_STATUS(BloodyLisaAnim_Walk, true), bloodyLisa, 49, 27, sfx, pitch0);
            }
            else
            {
                sharedFunc_800D908C_0_s00(ANIM_STATUS(BloodyLisaAnim_Walk, true), bloodyLisa, 92, 69, sfx, pitch0);
            }
            break;
    }

    bloodyLisa->rotation.vy  = Q12_ANGLE_ABS(bloodyLisa->rotation.vy + Q8_TO_Q4(sharedData_800E2C38_7_s01));
    bloodyLisa->headingAngle = bloodyLisa->rotation.vy;
    bloodyLisa->moveSpeed    = dahliaProps.moveDistance_126;
    bloodyLisa->fallSpeed   += g_GravitySpeed;

    boneCoords->flg = false;
    Math_RotMatrixZxyNegGte(&bloodyLisa->rotation, &boneCoords->coord);
}

 /** Addresses
  * MAP7_S01: 0x800D5CB4
  * MAP7_S02: 0x800D6850
  * MAP7_S03: 0x800D501C
  */
void BloodyLisa_Init(s_SubCharacter* bloodyLisa)
{
    Chara_CollisionReset(bloodyLisa);
    sharedData_800E2C38_7_s01 = 0;
}
