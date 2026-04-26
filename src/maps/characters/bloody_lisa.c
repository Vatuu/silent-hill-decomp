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
void Ai_BloodyLisa_Update(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* boneCoords)
{
    if (chara->model.controlState == 0)
    {
        Ai_BloodyLisa_Init(chara);
    }

    Ai_BloodyLisa_AnimStateUpdate(chara, boneCoords);
    Ai_BloodyLisa_MovementUpdate(chara, boneCoords);
    Ai_BloodyLisa_AnimUpdate(chara, anmHdr, boneCoords);
}

 /** Addresses
 * MAP7_S01: 0x800D595C
 * MAP7_S02: 0x800D64F8
 * MAP7_S03: 0x800D4CC4
 */
void Ai_BloodyLisa_AnimUpdate(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* boneCoords)
{
    s_AnimInfo* animInfo;

    if (chara->properties.player.field_F0 == 0)
    {
        animInfo = &BLOODY_LISA_ANIM_INFOS[chara->model.anim.status];
        animInfo->playbackFunc(&chara->model, anmHdr, boneCoords, animInfo);
    }
}

 /** Addresses
 * MAP7_S01: 0x800D59A4
 * MAP7_S02: 0x800D6540
 * MAP7_S03: 0x800D4D0C
 */
void Ai_BloodyLisa_MovementUpdate(s_SubCharacter* chara, GsCOORDINATE2* boneCoords)
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
 * MAP7_S01: 0x800D5B3C
 * MAP7_S02: 0x800D66D8
 * MAP7_S03: 0x800D4EA4
 */
void Ai_BloodyLisa_AnimStateUpdate(s_SubCharacter* chara, GsCOORDINATE2* boneCoords)
{
    s_Collision coll;
    e_SfxId     sfx;
    s8          pitch0;
    s8          pitch1;

    #define dahliaProps (chara->properties.dahlia)

    switch (dahliaProps.stateIdx0)
    {
        case 0:
            break;

        case 6:
            Model_AnimStatusSet(&chara->model, BloodyLisaAnim_Walk, false);
            Character_AnimStateReset(chara);
            break;
    }

    Collision_Get(&coll, chara->position.vx, chara->position.vz);
    func_8007FDE0(coll.field_8, &sfx, &pitch0, &pitch1);

    switch (dahliaProps.stateIdx0)
    {
        case 6:
            if (chara->model.anim.keyframeIdx <= 12)
            {
                sharedFunc_800D908C_0_s00(ANIM_STATUS(BloodyLisaAnim_Walk, true), chara, 12, 27, sfx, pitch0);
            }
            else if (chara->model.anim.keyframeIdx <= 49)
            {
                sharedFunc_800D908C_0_s00(ANIM_STATUS(BloodyLisaAnim_Walk, true), chara, 49, 27, sfx, pitch0);
            }
            else
            {
                sharedFunc_800D908C_0_s00(ANIM_STATUS(BloodyLisaAnim_Walk, true), chara, 92, 69, sfx, pitch0);
            }
            break;
    }

    chara->rotation.vy  = Q12_ANGLE_ABS(chara->rotation.vy + Q8_TO_Q4(sharedData_800E2C38_7_s01));
    chara->headingAngle = chara->rotation.vy;
    chara->moveSpeed    = dahliaProps.moveDistance_126;
    chara->fallSpeed   += g_GravitySpeed;

    boneCoords->flg = false;
    Math_RotMatrixZxyNegGte(&chara->rotation, &boneCoords->coord);
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
